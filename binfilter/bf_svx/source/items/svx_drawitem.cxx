/*************************************************************************
 *
 *  $RCSfile: svx_drawitem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:45:06 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

// include ---------------------------------------------------------------

#pragma hdrstop

#include "svxids.hrc"

#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST    SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST       SID_HATCH_LIST
#define ITEMID_BITMAP_LIST      SID_BITMAP_LIST
#define ITEMID_DASH_LIST        SID_DASH_LIST
#define ITEMID_LINEEND_LIST     SID_LINEEND_LIST

#include "xoutx.hxx"
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

//STRIP001 SfxItemPresentation SvxColorTableItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ int SvxColorTableItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001  return ( ( SvxColorTableItem& ) rItem).pColorTable == pColorTable;
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

//STRIP001 SfxItemPresentation SvxGradientListItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ int SvxGradientListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001  return ( ( SvxGradientListItem& ) rItem).pGradientList == pGradientList;
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

//STRIP001 SfxItemPresentation SvxHatchListItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ int SvxHatchListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001  return ( ( SvxHatchListItem& ) rItem).pHatchList == pHatchList;
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

//STRIP001 SfxItemPresentation SvxBitmapListItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ int SvxBitmapListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001  return ( ( SvxBitmapListItem& ) rItem).pBitmapList == pBitmapList;
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

//STRIP001 SfxItemPresentation SvxDashListItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ int SvxDashListItem::operator==( const SfxPoolItem& rItem ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001  return ( ( SvxDashListItem& ) rItem).pDashList == pDashList;
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

//STRIP001 SfxItemPresentation SvxLineEndListItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

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
