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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "svxids.hrc"

#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST    SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST       SID_HATCH_LIST
#define ITEMID_BITMAP_LIST      SID_BITMAP_LIST
#define ITEMID_DASH_LIST        SID_DASH_LIST
#define ITEMID_LINEEND_LIST     SID_LINEEND_LIST


#include <bf_svtools/poolitem.hxx>

#include "drawitem.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY( SvxColorTableItem, SfxPoolItem );
/*N*/ TYPEINIT1_AUTOFACTORY( SvxGradientListItem, SfxPoolItem );
/*N*/ TYPEINIT1_AUTOFACTORY( SvxHatchListItem, SfxPoolItem );
/*N*/ TYPEINIT1_AUTOFACTORY( SvxBitmapListItem, SfxPoolItem );
/*N*/ TYPEINIT1_AUTOFACTORY( SvxDashListItem, SfxPoolItem );
/*N*/ TYPEINIT1_AUTOFACTORY( SvxLineEndListItem, SfxPoolItem );

//==================================================================
//
//  SvxColorTableItem
//
//==================================================================

/*?*/ SvxColorTableItem::SvxColorTableItem()
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxColorTableItem::SvxColorTableItem( XColorTable* pTable, sal_uInt16 nW ) :
/*N*/   SfxPoolItem( nW ),
/*N*/   pColorTable( pTable )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxColorTableItem::SvxColorTableItem( const SvxColorTableItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   pColorTable( rItem.pColorTable )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxColorTableItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxColorTableItem( *this );
/*N*/ }

//==================================================================
//
//  SvxGradientListItem
//
//==================================================================

/*?*/ SvxGradientListItem::SvxGradientListItem()
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxGradientListItem::SvxGradientListItem( XGradientList* pList, sal_uInt16 nW ) :
/*N*/   SfxPoolItem( nW ),
/*N*/   pGradientList( pList )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxGradientListItem::SvxGradientListItem( const SvxGradientListItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   pGradientList( rItem.pGradientList )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxGradientListItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxGradientListItem( *this );
/*N*/ }

//==================================================================
//
//  SvxHatchListItem
//
//==================================================================

/*?*/ SvxHatchListItem::SvxHatchListItem()
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxHatchListItem::SvxHatchListItem( XHatchList* pList, sal_uInt16 nW ) :
/*N*/   SfxPoolItem( nW ),
/*N*/   pHatchList( pList )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxHatchListItem::SvxHatchListItem( const SvxHatchListItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   pHatchList( rItem.pHatchList )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxHatchListItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxHatchListItem( *this );
/*N*/ }

//==================================================================
//
//  SvxBitmapListItem
//
//==================================================================

/*?*/ SvxBitmapListItem::SvxBitmapListItem()
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBitmapListItem::SvxBitmapListItem( XBitmapList* pList, sal_uInt16 nW ) :
/*N*/   SfxPoolItem( nW ),
/*N*/   pBitmapList( pList )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBitmapListItem::SvxBitmapListItem( const SvxBitmapListItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   pBitmapList( rItem.pBitmapList )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBitmapListItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxBitmapListItem( *this );
/*N*/ }

//==================================================================
//
//  SvxDashListItem
//
//==================================================================

/*?*/ SvxDashListItem::SvxDashListItem()
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxDashListItem::SvxDashListItem( XDashList* pList, sal_uInt16 nW ) :
/*N*/   SfxPoolItem( nW ),
/*N*/   pDashList( pList )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxDashListItem::SvxDashListItem( const SvxDashListItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   pDashList( rItem.pDashList )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxDashListItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxDashListItem( *this );
/*N*/ }

//==================================================================
//
//  SvxLineEndListItem
//
//==================================================================

/*?*/ SvxLineEndListItem::SvxLineEndListItem()
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxLineEndListItem::SvxLineEndListItem( XLineEndList* pList, sal_uInt16 nW ) :
/*N*/   SfxPoolItem( nW ),
/*N*/   pLineEndList( pList )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxLineEndListItem::SvxLineEndListItem( const SvxLineEndListItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   pLineEndList( rItem.pLineEndList )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxLineEndListItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*N*/   return ( ( SvxLineEndListItem& ) rItem).pLineEndList == pLineEndList;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLineEndListItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxLineEndListItem( *this );
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
