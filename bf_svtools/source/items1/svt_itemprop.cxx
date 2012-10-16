/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <string.h>

#include <bf_svtools/itemprop.hxx>
#include <bf_svtools/itempool.hxx>
#include <bf_svtools/itemset.hxx>
#include <com/sun/star/beans/PropertyAttribute.hpp>

/*************************************************************************
    UNO III Implementation
*************************************************************************/
using namespace com::sun::star::beans;
using namespace com::sun::star::lang;
using namespace com::sun::star::uno;
using namespace ::rtl;

namespace binfilter
{



const SfxItemPropertyMap*   SfxItemPropertyMap::GetByName(
    const SfxItemPropertyMap *pMap, const OUString &rName )
{
    while ( pMap->pName )
    {
        if( rName.equalsAsciiL( pMap->pName, pMap->nNameLen ) )
            return pMap;
        ++pMap;
    }
    return 0;
}


BOOL SfxItemPropertySet::FillItem(SfxItemSet&, USHORT, BOOL) const
{
    return FALSE;
}


void SfxItemPropertySet::getPropertyValue( const SfxItemPropertyMap& rMap,
            const SfxItemSet& rSet, Any& rAny ) const
                        throw(RuntimeException)
{
    // item holen
    const SfxPoolItem* pItem = 0;
    SfxItemState eState = rSet.GetItemState( rMap.nWID, TRUE, &pItem );
    if(SFX_ITEM_SET != eState && SFX_WHICH_MAX > rMap.nWID )
        pItem = &rSet.GetPool()->GetDefaultItem(rMap.nWID);
    // item-Wert als UnoAny zurueckgeben
    if(eState >= SFX_ITEM_DEFAULT && pItem)
    {
        pItem->QueryValue( rAny, rMap.nMemberId );
    }
    else
    {
        SfxItemSet aSet(*rSet.GetPool(), rMap.nWID, rMap.nWID);
        if(FillItem(aSet, rMap.nWID, TRUE))
        {
            const SfxPoolItem& rItem = aSet.Get(rMap.nWID);
            rItem.QueryValue( rAny, rMap.nMemberId );
        }
        else if(0 == (rMap.nFlags & PropertyAttribute::MAYBEVOID))
            throw RuntimeException();
    }


    // allgemeine SfxEnumItem Values in konkrete wandeln
    if( rMap.pType && TypeClass_ENUM == rMap.pType->getTypeClass() &&
         rAny.getValueTypeClass() == TypeClass_LONG )
    {
        INT32 nTmp = *(INT32*)rAny.getValue();
        rAny.setValue( &nTmp, *rMap.pType );
    }
}




Any SfxItemPropertySet::getPropertyValue( const SfxItemPropertyMap& rMap,
            const SfxItemSet& rSet ) const
                        throw(RuntimeException)
{
    Any aAny;
    getPropertyValue(rMap, rSet, aAny);
    return aAny;
}



void SfxItemPropertySet::getPropertyValue( const OUString &rName,
            const SfxItemSet& rSet, Any& rAny ) const
                        throw(RuntimeException, UnknownPropertyException)
{
    // which-id ermitteln
    const SfxItemPropertyMap* pMap = SfxItemPropertyMap::GetByName( _pMap, rName );
    if ( !pMap )
        throw UnknownPropertyException();
    getPropertyValue( *pMap,rSet, rAny );
}


Any SfxItemPropertySet::getPropertyValue( const OUString &rName,
            const SfxItemSet& rSet ) const
                        throw(RuntimeException, UnknownPropertyException)
{
    Any aVal;
    getPropertyValue( rName,rSet, aVal );
    return aVal;
}


void SfxItemPropertySet::setPropertyValue( const SfxItemPropertyMap& rMap,
                                            const Any& aVal,
                                            SfxItemSet& rSet ) const
                                            throw(RuntimeException,
                                                    IllegalArgumentException)
{
    // item holen
    const SfxPoolItem* pItem = 0;
    SfxPoolItem *pNewItem = 0;
    SfxItemState eState = rSet.GetItemState( rMap.nWID, TRUE, &pItem );
    if(SFX_ITEM_SET != eState && SFX_WHICH_MAX > rMap.nWID )
        pItem = &rSet.GetPool()->GetDefaultItem(rMap.nWID);
    //maybe there's another way to find an Item
    if(eState < SFX_ITEM_DEFAULT)
    {
        SfxItemSet aSet(*rSet.GetPool(), rMap.nWID, rMap.nWID);
        if(FillItem(aSet, rMap.nWID, FALSE))
        {
            const SfxPoolItem &rItem = aSet.Get(rMap.nWID);
            pNewItem = rItem.Clone();
        }
    }
    if(!pNewItem && pItem)
    {
        pNewItem = pItem->Clone();
    }
    if(pNewItem)
    {
        if( !pNewItem->PutValue( aVal, rMap.nMemberId ) )
        {
            DELETEZ(pNewItem);
            throw IllegalArgumentException();
        }
        // neues item in itemset setzen
        rSet.Put( *pNewItem, rMap.nWID );
        delete pNewItem;
    }
}


void SfxItemPropertySet::setPropertyValue( const OUString &rName,
                                            const Any& aVal,
                                            SfxItemSet& rSet ) const
                                            throw(RuntimeException,
                                                    IllegalArgumentException,
                                                    UnknownPropertyException)
{
    const SfxItemPropertyMap* pMap = SfxItemPropertyMap::GetByName( _pMap, rName );
    if ( !pMap )
    {
        throw UnknownPropertyException();
    }
    setPropertyValue(*pMap, aVal, rSet);
}


PropertyState SfxItemPropertySet::getPropertyState(const SfxItemPropertyMap& rMap, const SfxItemSet& rSet)
                                    throw()
{
    PropertyState eRet = PropertyState_DIRECT_VALUE;
    USHORT nWhich = rMap.nWID;

    // item state holen
    SfxItemState eState = rSet.GetItemState( nWhich, FALSE );
    // item-Wert als UnoAny zurueckgeben
    if(eState == SFX_ITEM_DEFAULT)
        eRet = PropertyState_DEFAULT_VALUE;
    else if(eState < SFX_ITEM_DEFAULT)
        eRet = PropertyState_AMBIGUOUS_VALUE;
    return eRet;
}

PropertyState   SfxItemPropertySet::getPropertyState(
                                const OUString& rName, const SfxItemSet& rSet)
                                    throw(UnknownPropertyException)
{
    PropertyState eRet = PropertyState_DIRECT_VALUE;

    // which-id ermitteln
    const SfxItemPropertyMap* pMap = SfxItemPropertyMap::GetByName( _pMap, rName );
    USHORT nWhich = pMap ? pMap->nWID : 0;
    if ( !nWhich )
    {
        throw UnknownPropertyException();
    }

    // item holen
    const SfxPoolItem* pItem = 0;
    SfxItemState eState = rSet.GetItemState( nWhich, FALSE, &pItem );
    if(!pItem && nWhich != rSet.GetPool()->GetSlotId(nWhich))
        pItem = &rSet.GetPool()->GetDefaultItem(nWhich);
    // item-Wert als UnoAny zurueckgeben
    if(eState == SFX_ITEM_DEFAULT)
        eRet = PropertyState_DEFAULT_VALUE;
    else if(eState < SFX_ITEM_DEFAULT)
        eRet = PropertyState_AMBIGUOUS_VALUE;
    return eRet;
}


Reference<XPropertySetInfo>
    SfxItemPropertySet::getPropertySetInfo() const
{
    Reference<XPropertySetInfo> aRef(new SfxItemPropertySetInfo( _pMap ));
    return aRef;
}



Sequence< Property > SAL_CALL
        SfxItemPropertySetInfo::getProperties(  )
            throw(RuntimeException)
{
    USHORT n = 0;
    {
        for ( const SfxItemPropertyMap *pMap = _pMap; pMap->pName; ++pMap )
            ++n;
    }

    Sequence<Property> aPropSeq( n );
    n = 0;
    for ( const SfxItemPropertyMap *pMap = _pMap; pMap->pName; ++pMap )
    {
        aPropSeq.getArray()[n].Name = OUString::createFromAscii( pMap->pName );
        aPropSeq.getArray()[n].Handle = pMap->nWID;
        if(pMap->pType)
            aPropSeq.getArray()[n].Type = *pMap->pType;
        aPropSeq.getArray()[n].Attributes =
            sal::static_int_cast< sal_Int16 >(pMap->nFlags);
        n++;
    }

    return aPropSeq;
}


Property SAL_CALL
        SfxItemPropertySetInfo::getPropertyByName( const ::rtl::OUString& rName )
            throw(UnknownPropertyException, RuntimeException)
{
    Property aProp;
    for( const SfxItemPropertyMap *pMap = _pMap; pMap->pName; ++pMap )
    {
        if( rName.equalsAsciiL( pMap->pName, pMap->nNameLen ))
        {
            aProp.Name = rName;
            aProp.Handle = pMap->nWID;
            if(pMap->pType)
                aProp.Type = *pMap->pType;
            aProp.Attributes = sal::static_int_cast< sal_Int16 >(pMap->nFlags);
            break;
        }
    }
    if(!aProp.Name.getLength())
        throw UnknownPropertyException();
    return aProp;
}


sal_Bool SAL_CALL
        SfxItemPropertySetInfo::hasPropertyByName( const ::rtl::OUString& rName )
            throw(RuntimeException)
{
    for ( const SfxItemPropertyMap *pMap = _pMap; pMap->pName; ++pMap )
    {
        if( rName.equalsAsciiL( pMap->pName, pMap->nNameLen ))
            return TRUE;
    }
    return FALSE;
}


SfxExtItemPropertySetInfo::SfxExtItemPropertySetInfo(
                                const SfxItemPropertyMap *pMap,
                                const Sequence<Property>& rPropSeq ) :
                _pExtMap(pMap)
{
    long nLen = rPropSeq.getLength();
    long nExtLen = 0;
    while(pMap[nExtLen].pName)
        nExtLen++;
    aPropertySeq.realloc(nExtLen + nLen);


    long nNewLen = aPropertySeq.getLength();
    Property* pNewArr = aPropertySeq.getArray();
    long nCount1 = 0;//map
    long nCount2 = 0;//sequence
    long nDouble = 0;//Anzahl gleicher Property-Namen
    BOOL bFromMap, bZero = FALSE;

    const Property* pPropSeqArr = rPropSeq.getConstArray();
    for( long i = 0; i < nNewLen; i++)
    {
        bFromMap = FALSE;
        if(nCount1 < nExtLen && nCount2 < nLen)
        {
//          int nDiff = strcmp(pMap[nCount1].pName, OUStringToString(rPropSeq.getConstArray()[nCount2].Name, CHARSET_SYSTEM ));
            sal_Int32 nDiff = pPropSeqArr[nCount2].Name.compareToAscii(pMap[nCount1].pName, pMap[nCount1].nNameLen );
            if(nDiff > 0)
            {
                bFromMap = TRUE;
            }
            else if(0 == nDiff)
            {
                nDouble++;
                bFromMap = TRUE;
                nCount2++;
            }
        }
        else
        {
            if(nCount1 < nExtLen)
                bFromMap = TRUE;
            else if(nCount2>= nLen)
                bZero = TRUE;
        }
        if(bFromMap)
        {
            pNewArr[i].Name = OUString::createFromAscii( pMap[nCount1].pName );
            pNewArr[i].Handle = pMap[nCount1].nWID;
            if(pMap[nCount1].pType)
                pNewArr[i].Type = *pMap[nCount1].pType;
            pNewArr[i].Attributes = sal::static_int_cast< sal_Int16 >(
                pMap[nCount1].nFlags);
            nCount1++;
        }
        else if(!bZero)
        {
            pNewArr[i] = pPropSeqArr[nCount2];
            nCount2++;
        }
    }
    if(nDouble)
        aPropertySeq.realloc(nExtLen + nLen - nDouble);
}


Sequence< Property > SAL_CALL
        SfxExtItemPropertySetInfo::getProperties(  ) throw(RuntimeException)
{
    return aPropertySeq;
}


Property SAL_CALL
        SfxExtItemPropertySetInfo::getPropertyByName( const OUString& aPropertyName )
            throw(UnknownPropertyException, RuntimeException)
{
    const Property* pPropArr = aPropertySeq.getConstArray();
    long nLen = aPropertySeq.getLength();
    for( long i = 0; i < nLen; i++)
    {
        if(aPropertyName == pPropArr[i].Name)
            return pPropArr[i];
    }
    return Property();
}


sal_Bool SAL_CALL
        SfxExtItemPropertySetInfo::hasPropertyByName( const OUString& aPropertyName )
            throw(RuntimeException)
{
    const Property* pPropArr = aPropertySeq.getConstArray();
    long nLen = aPropertySeq.getLength();
    for( long i = 0; i < nLen; i++)
    {
        if(aPropertyName == pPropArr[i].Name)
            return TRUE;
    }
    return FALSE;
}

// --------------------------------------------------------------------
// SfxItemPropertySetInfo
// --------------------------------------------------------------------

::com::sun::star::uno::Any SAL_CALL SfxItemPropertySetInfo::queryInterface( const ::com::sun::star::uno::Type& aType ) throw (::com::sun::star::uno::RuntimeException)
{
    return cppu::WeakImplHelper1<com::sun::star::beans::XPropertySetInfo>::queryInterface( aType );
}

// --------------------------------------------------------------------

void SAL_CALL SfxItemPropertySetInfo::acquire(  ) throw ()
{
    cppu::WeakImplHelper1<com::sun::star::beans::XPropertySetInfo>::release();
}

// --------------------------------------------------------------------

void SAL_CALL SfxItemPropertySetInfo::release(  ) throw ()
{
    cppu::WeakImplHelper1<com::sun::star::beans::XPropertySetInfo>::release();
}

// --------------------------------------------------------------------
// SfxExtItemPropertySetInfo
// --------------------------------------------------------------------

::com::sun::star::uno::Any SAL_CALL SfxExtItemPropertySetInfo::queryInterface( const ::com::sun::star::uno::Type& aType ) throw (::com::sun::star::uno::RuntimeException)
{
    return cppu::WeakImplHelper1<com::sun::star::beans::XPropertySetInfo>::queryInterface( aType );
}

// --------------------------------------------------------------------

void SAL_CALL SfxExtItemPropertySetInfo::acquire(  ) throw ()
{
    cppu::WeakImplHelper1<com::sun::star::beans::XPropertySetInfo>::release();
}

// --------------------------------------------------------------------

void SAL_CALL SfxExtItemPropertySetInfo::release(  ) throw ()
{
    cppu::WeakImplHelper1<com::sun::star::beans::XPropertySetInfo>::release();
}

// --------------------------------------------------------------------
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
