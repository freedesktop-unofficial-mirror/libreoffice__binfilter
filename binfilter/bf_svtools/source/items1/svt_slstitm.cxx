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

#include <bf_svtools/slstitm.hxx>

#include <bf_svtools/poolitem.hxx>

#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Sequence.hxx>

#include <tools/stream.hxx>

namespace binfilter
{

// -----------------------------------------------------------------------

TYPEINIT1_AUTOFACTORY(SfxStringListItem, SfxPoolItem);

class SfxImpStringList
{
public:
    USHORT  nRefCount;
    List    aList;

            SfxImpStringList() { nRefCount = 1; }
            ~SfxImpStringList();
};

//------------------------------------------------------------------------

SfxImpStringList::~SfxImpStringList()
{
    DBG_ASSERT(nRefCount!=0xffff,"ImpList already deleted");
    String* pStr = (String*)aList.First();
    while( pStr )
    {
        delete pStr;
        pStr = (String*)aList.Next();
    }
    nRefCount = 0xffff;
}

// class SfxStringListItem -----------------------------------------------

SfxStringListItem::SfxStringListItem() :
    pImp(NULL)
{
}

//------------------------------------------------------------------------

SfxStringListItem::SfxStringListItem( USHORT which, SvStream& rStream ) :
    SfxPoolItem( which ),
    pImp(NULL)
{
    long nEntryCount;
    rStream >> nEntryCount;

    if( nEntryCount )
        pImp = new SfxImpStringList;

    long   i;
    String*  pStr;
    for( i=0; i < nEntryCount; i++ )
    {
        pStr = new String;
        readByteString(rStream, *pStr);
        pImp->aList.Insert( pStr, LIST_APPEND );
    }
}

//------------------------------------------------------------------------

SfxStringListItem::SfxStringListItem( const SfxStringListItem& rItem ) :
    SfxPoolItem( rItem ),
    pImp(NULL)
{
    pImp = rItem.pImp;

    if( pImp )
    {
        DBG_ASSERT(pImp->nRefCount!=0xffff,"ImpList not valid");
        pImp->nRefCount++;
    }
}

//------------------------------------------------------------------------

SfxStringListItem::~SfxStringListItem()
{
    if( pImp )
    {
        DBG_ASSERT(pImp->nRefCount!=0xffff,"ImpList not valid");
        if( pImp->nRefCount > 1 )
            pImp->nRefCount--;
        else
            delete pImp;
    }
}

//------------------------------------------------------------------------

int SfxStringListItem::operator==( const SfxPoolItem& rItem ) const
{
    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );

    SfxStringListItem* pItem = (SfxStringListItem*)&rItem;

    if( pImp == pItem->pImp )
        return TRUE;
    else
        return FALSE;
}

//------------------------------------------------------------------------

SfxItemPresentation SfxStringListItem::GetPresentation
(
    SfxItemPresentation     /*ePresentation*/,
    SfxMapUnit              /*eCoreMetric*/,
    SfxMapUnit              /*ePresentationMetric*/,
    XubString&              rText,
    const ::IntlWrapper *
)   const
{
    rText.AssignAscii(RTL_CONSTASCII_STRINGPARAM("(List)"));
    return SFX_ITEM_PRESENTATION_NONE;
}

//------------------------------------------------------------------------

SfxPoolItem* SfxStringListItem::Clone( SfxItemPool *) const
{
    return new SfxStringListItem( *this );
    /*
    if( pImp )
        return new SfxStringListItem( Which(), &(pImp->aList) );
    else
        return new SfxStringListItem( Which(), NULL );
    */

}

//------------------------------------------------------------------------

SfxPoolItem* SfxStringListItem::Create( SvStream & rStream, USHORT ) const
{
    return new SfxStringListItem( Which(), rStream );
}

void SfxStringListItem::SetString( const XubString& rStr )
{
    DBG_ASSERT(GetRefCount()==0,"SetString:RefCount!=0");

    if ( pImp && (pImp->nRefCount == 1) )
        delete pImp;
    else
    if( pImp )
        pImp->nRefCount--;
    pImp = new SfxImpStringList;

    xub_StrLen nStart = 0;
    xub_StrLen nDelimPos;
    XubString aStr(convertLineEnd(rStr, LINEEND_CR));
    do
    {
        nDelimPos = aStr.Search( _CR, nStart );
        xub_StrLen nLen;
        if ( nDelimPos == STRING_NOTFOUND )
            nLen = 0xffff;
        else
            nLen = nDelimPos - nStart;

        XubString* pStr = new XubString(aStr.Copy(nStart, nLen));
        // String gehoert der Liste
        pImp->aList.Insert( pStr, LIST_APPEND );

        nStart += nLen + 1 ;    // delimiter ueberspringen
    } while( nDelimPos != STRING_NOTFOUND );

    // Kein Leerstring am Ende
    if( pImp->aList.Last() &&
        !((XubString*)pImp->aList.Last())->Len() )
        delete (XubString*)pImp->aList.Remove( pImp->aList.Count()-1 );
}

//------------------------------------------------------------------------

XubString SfxStringListItem::GetString()
{
    XubString aStr;
    if ( pImp )
    {
        DBG_ASSERT(pImp->nRefCount!=0xffff,"ImpList not valid");
        XubString* pStr = (XubString*)(pImp->aList.First());
        while( pStr )
        {
            aStr += *pStr;
            pStr = (XubString*)(pImp->aList.Next());
            if ( pStr )
                aStr += '\r';
        }
    }
    return convertLineEnd(aStr, GetSystemLineEnd());
}

//------------------------------------------------------------------------

#ifndef TF_POOLABLE

int SfxStringListItem::IsPoolable() const
{
    return FALSE;
}

#endif

//------------------------------------------------------------------------

void SfxStringListItem::SetStringList( const com::sun::star::uno::Sequence< rtl::OUString >& rList )
{
    DBG_ASSERT(GetRefCount()==0,"SetString:RefCount!=0");

    if ( pImp && (pImp->nRefCount == 1) )
        delete pImp;
    else
    if( pImp )
        pImp->nRefCount--;
    pImp = new SfxImpStringList;

    for ( sal_Int32 n = 0; n < rList.getLength(); n++ )
    {
        XubString* pStr = new XubString( rList[n] );
        // String gehoert der Liste
        pImp->aList.Insert( pStr, LIST_APPEND );
    }
}

//----------------------------------------------------------------------------
void SfxStringListItem::GetStringList( com::sun::star::uno::Sequence< rtl::OUString >& rList ) const
{
    long nCount = pImp->aList.Count();

    rList.realloc( nCount );
    for( long i=0; i < nCount; i++ )
        rList[i] = *(String*)(pImp->aList.GetObject( i ));
}

//----------------------------------------------------------------------------
// virtual
bool SfxStringListItem::PutValue( const com::sun::star::uno::Any& rVal,BYTE )
{
    com::sun::star::uno::Sequence< rtl::OUString > aValue;
    if ( rVal >>= aValue )
    {
        SetStringList( aValue );
        return true;
    }

    OSL_FAIL( "SfxStringListItem::PutValue - Wrong type!" );
    return false;
}

//----------------------------------------------------------------------------
// virtual
bool SfxStringListItem::QueryValue( com::sun::star::uno::Any& rVal,BYTE ) const
{
    // GetString() is not const!!!
    SfxStringListItem* pThis = const_cast< SfxStringListItem * >( this );

    com::sun::star::uno::Sequence< rtl::OUString > aStringList;
    pThis->GetStringList( aStringList );
    rVal = ::com::sun::star::uno::makeAny( aStringList );
    return true;
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
