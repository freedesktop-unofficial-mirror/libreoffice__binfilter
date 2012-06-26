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

#include <com/sun/star/uno/Any.hxx>

#include <tools/stream.hxx>
#include <tools/debug.hxx>
#include <bf_tools/string.hxx>

#include <bf_svtools/tfrmitem.hxx>

namespace binfilter
{

DBG_NAME( SfxTargetFrameItem )
TYPEINIT1( SfxTargetFrameItem, SfxPoolItem );

// -----------------------------------------------------------------------

SfxTargetFrameItem::SfxTargetFrameItem( USHORT which ) :
    SfxPoolItem( which )
{
    DBG_CTOR( SfxTargetFrameItem, 0 );
}

// -----------------------------------------------------------------------

SfxTargetFrameItem::SfxTargetFrameItem( const SfxTargetFrameItem& rItem ) :
    SfxPoolItem( rItem )
{
    DBG_CTOR( SfxTargetFrameItem, 0 );
    for( USHORT nCur = 0; nCur <= (USHORT)SfxOpenModeLast; nCur++ )
        _aFrames[nCur] = rItem._aFrames[nCur];
}

// -----------------------------------------------------------------------

SfxTargetFrameItem::~SfxTargetFrameItem()
{
    DBG_DTOR(SfxTargetFrameItem, 0);
}

// -----------------------------------------------------------------------

int SfxTargetFrameItem::operator==( const SfxPoolItem& rItem ) const
{
    DBG_CHKTHIS( SfxTargetFrameItem, 0 );
    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );

    for( USHORT nCur = 0; nCur <= (USHORT)SfxOpenModeLast; nCur++ )
    {
        if( _aFrames[nCur] != ((const SfxTargetFrameItem&)rItem)._aFrames[nCur] )
            return 0;
    }
    return 1;
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxTargetFrameItem::Create( SvStream& rStream, USHORT ) const
{
    DBG_CHKTHIS(SfxTargetFrameItem, 0);
    SfxTargetFrameItem* pItem = new SfxTargetFrameItem( Which() );
    USHORT nCount = 0;
    rStream >> nCount;
    for(USHORT nCur=0; nCur<= (USHORT)SfxOpenModeLast && nCount; nCur++,nCount--)
    {
        readByteString(rStream, pItem->_aFrames[ nCur ]);
    }
    // die uebriggebliebenen ueberspringen
    String aTemp;
    while( nCount )
    {
        readByteString(rStream, aTemp);
        nCount--;
    }
    return pItem;
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxTargetFrameItem::Clone( SfxItemPool* ) const
{
    DBG_CHKTHIS( SfxTargetFrameItem, 0 );
    return new SfxTargetFrameItem( *this );
}

// -----------------------------------------------------------------------
// virtual
bool SfxTargetFrameItem::QueryValue( com::sun::star::uno::Any& rVal,BYTE ) const
{
    String aVal;
    for ( int i = 0; i <= SfxOpenModeLast; i++ )
    {
        aVal += _aFrames[ i ];
        aVal += ';' ;
    }

    rVal <<= rtl::OUString( aVal );
    return true;
}

// -----------------------------------------------------------------------
// virtual
bool SfxTargetFrameItem::PutValue( const com::sun::star::uno::Any& rVal,BYTE )
{
    rtl::OUString aValue;
    if ( rVal >>= aValue )
    {
        const String aVal( aValue );

        for ( USHORT i = 0; i <= SfxOpenModeLast; i++ )
            _aFrames[ i ] = aVal.GetToken( i );

        return true;
    }

    OSL_FAIL( "SfxTargetFrameItem::PutValue - Wrong type!" );
    return false;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
