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

#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <cppuhelper/implbase2.hxx>

#include <bf_svtools/itempool.hxx>

#include <bf_svtools/itemset.hxx>

#include <bf_svtools/svarray.hxx>

#include "eeitem.hxx"
#include "numitem.hxx"
#include "unonrule.hxx"

#include "svdmodel.hxx"
#include "xdef.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

SV_DECL_PTRARR( ItemSetArray_Impl, SfxItemSet*, 5, 5 )

class SvxUnoNumberingRuleTable : public WeakImplHelper2< container::XNameContainer, lang::XServiceInfo >
{
private:
    XGradientList*  mpGradientList;
    SdrModel*       mpModel;
    SfxItemPool*    mpPool;

    ItemSetArray_Impl   aItemSetArray;

    void CreateName( OUString& rStrName);

public:
    SvxUnoNumberingRuleTable( SdrModel* pModel ) throw();
    virtual ~SvxUnoNumberingRuleTable() throw();

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const  OUString& ServiceName ) throw( uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    static OUString getImplementationName_Static() throw()
    {
        return OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.SvxUnoNumberingRuleTable"));
    }

    static uno::Sequence< OUString >  getSupportedServiceNames_Static(void) throw();


    // XNameContainer
    virtual void SAL_CALL insertByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException);
    virtual void SAL_CALL removeByName( const  OUString& Name ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameReplace
    virtual void SAL_CALL replaceByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameAccess
    virtual uno::Any SAL_CALL getByName( const  OUString& aName ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getElementNames(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const  OUString& aName ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements(  ) throw( uno::RuntimeException);
};

SvxUnoNumberingRuleTable::SvxUnoNumberingRuleTable( SdrModel* pModel ) throw()
: mpModel( pModel ), mpPool( pModel ? &pModel->GetItemPool() : (SfxItemPool*)NULL )
{
}

SvxUnoNumberingRuleTable::~SvxUnoNumberingRuleTable() throw()
{
    for( int i = 0; i<aItemSetArray.Count(); i++ )
        delete (SfxItemSet*)aItemSetArray.GetObject( i );
}

sal_Bool SAL_CALL SvxUnoNumberingRuleTable::supportsService( const OUString& ServiceName ) throw(uno::RuntimeException)
{
    uno::Sequence< OUString > aSNL( getSupportedServiceNames() );
    const OUString * pArray = aSNL.getConstArray();

    for( INT32 i = 0; i < aSNL.getLength(); i++ )
        if( pArray[i] == ServiceName )
            return sal_True;

    return sal_False;
}

OUString SAL_CALL SvxUnoNumberingRuleTable::getImplementationName() throw( uno::RuntimeException )
{
    return getImplementationName_Static();
}

uno::Sequence< OUString > SAL_CALL SvxUnoNumberingRuleTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    return getSupportedServiceNames_Static();
}

uno::Sequence< OUString > SvxUnoNumberingRuleTable::getSupportedServiceNames_Static(void) throw()
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.text.NumberingRulesTable" ));
    return aSNS;
}


// XNameContainer
void SAL_CALL SvxUnoNumberingRuleTable::insertByName( const OUString& aName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException )
{
    SfxItemSet* mpInSet = new SfxItemSet( *mpPool, EE_PARA_NUMBULLET, EE_PARA_NUMBULLET );
    aItemSetArray.C40_INSERT( ItemSetArray_Impl, mpInSet, aItemSetArray.Count() );

    uno::Reference< container::XIndexReplace > xNumRule;
    if(aElement >>= xNumRule)
    {
        SvxUnoNumberingRules *pNumRules = SvxUnoNumberingRules::getImplementation( xNumRule );

        if( pNumRules )
        {
            mpInSet->Put( *(pNumRules->GetNumBulletItem()), EE_PARA_NUMBULLET );
            return;
        }
    }

    throw lang::IllegalArgumentException();
}



void SAL_CALL SvxUnoNumberingRuleTable::removeByName( const OUString& Name )
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
}

// XNameReplace
void SAL_CALL SvxUnoNumberingRuleTable::replaceByName( const OUString& aName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
}

SvxNumBulletItem* SvxGetNumBulletItemByName( SfxItemPool* pPool, const OUString& aName ) throw()
{
    if( pPool )
    {
        const USHORT nCount = pPool->GetItemCount(EE_PARA_NUMBULLET);
        SvxNumBulletItem *pItem = NULL, *pSearchItem;

        for( USHORT nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
        {
            pSearchItem = (SvxNumBulletItem*)pPool->GetItem(EE_PARA_NUMBULLET, nSurrogate);

            if( pSearchItem && pSearchItem->GetNumRule() && pSearchItem->GetNumRule()->GetLevelCount() && ( pSearchItem->getName() == aName ) )
            {
                return pSearchItem;
            }
        }
    }

    return NULL;
}

// XNameAccess
uno::Any SAL_CALL SvxUnoNumberingRuleTable::getByName( const  OUString& aName )
    throw( container::NoSuchElementException,  lang::WrappedTargetException, uno::RuntimeException)
{
    uno::Any aAny;

    SvxNumBulletItem *pItem = SvxGetNumBulletItemByName( mpPool, aName );
    if( pItem == NULL )
        throw container::NoSuchElementException();

    aAny <<= pItem->getUnoNumRule();
    return aAny;
}

uno::Sequence< OUString > SAL_CALL SvxUnoNumberingRuleTable::getElementNames(  )
    throw( uno::RuntimeException )
{
    const USHORT nCount = mpPool ? mpPool->GetItemCount(EE_PARA_NUMBULLET) : 0;
    uno::Sequence< OUString > aSeq( nCount );
    OUString* pStrings = aSeq.getArray();
    SvxNumBulletItem *pItem;

    USHORT nRealCount = 0;

    for( USHORT nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
    {
        pItem = (SvxNumBulletItem*)mpPool->GetItem(EE_PARA_NUMBULLET, nSurrogate);

        if( pItem && pItem->GetNumRule() && pItem->GetNumRule()->GetLevelCount() )
        {
            *pStrings = pItem->getName();

            if( !(*pStrings).getLength() )
            {
                CreateName( *pStrings );
                pItem->setName( String( *pStrings ) );
            }

            pStrings++;
            nRealCount++;
        }
    }

    if( nRealCount != nCount )
        aSeq.realloc( nRealCount );

    return aSeq;
}

sal_Bool SAL_CALL SvxUnoNumberingRuleTable::hasByName( const OUString& aName )
    throw( uno::RuntimeException )
{
    const USHORT nCount = mpPool ? mpPool->GetItemCount(EE_PARA_NUMBULLET) : 0;
    uno::Sequence< OUString > aSeq( nCount );
    OUString* pStrings = aSeq.getArray();
    const SvxNumBulletItem *pItem;

    for( USHORT nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
    {
        pItem = (SvxNumBulletItem*)mpPool->GetItem(EE_PARA_NUMBULLET, nSurrogate);
        if( pItem && pItem->GetNumRule() && pItem->GetNumRule()->GetLevelCount() && pItem->getName() == aName )
            return sal_True;
    }

    return sal_False;
}

// XElementAccess
uno::Type SAL_CALL SvxUnoNumberingRuleTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType((const uno::Reference< container::XIndexAccess >*)0);
}

sal_Bool SAL_CALL SvxUnoNumberingRuleTable::hasElements(  )
    throw( uno::RuntimeException )
{
    return mpPool && mpPool->GetItemCount(EE_PARA_NUMBULLET) != 0;
}

void SvxUnoNumberingRuleTable::CreateName( OUString& rStrName)
{
    const USHORT nCount = mpPool ? mpPool->GetItemCount(EE_PARA_NUMBULLET) : 0;
    sal_Bool bFound = sal_True;

    for( sal_Int32 nPostfix = 1; nPostfix<= nCount && bFound; nPostfix++ )
    {
        rStrName = OUString( RTL_CONSTASCII_USTRINGPARAM( "Standard " ));
        rStrName += OUString::valueOf( nPostfix );
        bFound = hasByName( rStrName );
    }
}

/**
 * Create a numbering rule table
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoNumberingRuleTable_createInstance( SdrModel* pModel )
{
    return *new SvxUnoNumberingRuleTable(pModel);
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
