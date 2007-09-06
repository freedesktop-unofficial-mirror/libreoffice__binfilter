/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_drawitem.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:41:44 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

// include ---------------------------------------------------------------

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


#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

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


// -----------------------------------------------------------------------

/*?*/ int SvxColorTableItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*?*/ }

// -----------------------------------------------------------------------

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


// -----------------------------------------------------------------------

/*?*/ int SvxGradientListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*?*/ }

// -----------------------------------------------------------------------

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


// -----------------------------------------------------------------------

/*?*/ int SvxHatchListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*?*/ }

// -----------------------------------------------------------------------

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


// -----------------------------------------------------------------------

/*?*/ int SvxBitmapListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*?*/ }

// -----------------------------------------------------------------------

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


// -----------------------------------------------------------------------

/*?*/ int SvxDashListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*?*/ }

// -----------------------------------------------------------------------

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

//------------------------------------------------------------------------


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
