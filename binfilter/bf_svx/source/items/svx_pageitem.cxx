/*************************************************************************
 *
 *  $RCSfile: svx_pageitem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:04:21 $
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

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#pragma hdrstop

// Erstmal definieren, damit die Klassendeklarionen angezogen werden.
#define  ITEMID_PAGE        0
#define  ITEMID_SETITEM     0

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

#include "pageitem.hxx"
#include "itemtype.hxx"
#include <unomid.hxx>

#ifndef _COM_SUN_STAR_STYLE_PAGESTYLELAYOUT_HPP_
#include <com/sun/star/style/PageStyleLayout.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_STYLE_BREAKTYPE_HPP_
// auto strip #include <com/sun/star/style/BreakType.hpp>
// auto strip #endif

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY( SvxPageItem, SfxPoolItem );

/*--------------------------------------------------------------------
    Beschreibung: Konstruktor
 --------------------------------------------------------------------*/

/*N*/ SvxPageItem::SvxPageItem( const USHORT nId ) : SfxPoolItem( nId ),
/*N*/
/*N*/   eNumType    ( SVX_ARABIC ),
/*N*/   bLandscape  ( sal_False ),
/*N*/   eUse        ( SVX_PAGE_ALL )
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Copy-Konstruktor
 --------------------------------------------------------------------*/

/*N*/ SvxPageItem::SvxPageItem( const SvxPageItem& rItem )
/*N*/   : SfxPoolItem( rItem )
/*N*/ {
/*N*/   eNumType    = rItem.eNumType;
/*N*/   bLandscape  = rItem.bLandscape;
/*N*/   eUse        = rItem.eUse;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Clonen
 --------------------------------------------------------------------*/

/*N*/ SfxPoolItem* SvxPageItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SvxPageItem( *this );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Abfrage auf Gleichheit
 --------------------------------------------------------------------*/

/*N*/ int SvxPageItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/   const SvxPageItem& rItem = (SvxPageItem&)rAttr;
/*N*/   return ( eNumType   == rItem.eNumType   &&
/*N*/            bLandscape == rItem.bLandscape &&
/*N*/            eUse       == rItem.eUse );
/*N*/ }

/*?*/ inline XubString GetUsageText( const USHORT eU )
/*?*/ {
/*?*/   if ( eU & SVX_PAGE_LEFT )
/*?*/       return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_LEFT);
/*?*/   if ( eU & SVX_PAGE_RIGHT )
/*?*/       return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_RIGHT);
/*?*/   if ( eU & SVX_PAGE_ALL )
/*?*/       return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_ALL);
/*?*/   if ( eU & SVX_PAGE_MIRROR )
/*?*/       return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_MIRROR);
/*?*/   return String();
/*?*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPageItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      {
//STRIP001          if ( aDescName.Len() )
//STRIP001          {
//STRIP001              rText = aDescName;
//STRIP001              rText += cpDelim;
//STRIP001          }
//STRIP001          DBG_ASSERT( eNumType <= SVX_NUMBER_NONE, "enum overflow" );
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_PAGE_NUM_BEGIN + eNumType);
//STRIP001          rText += cpDelim;
//STRIP001          if ( bLandscape )
//STRIP001              rText += SVX_RESSTR(RID_SVXITEMS_PAGE_LAND_TRUE);
//STRIP001          else
//STRIP001              rText += SVX_RESSTR(RID_SVXITEMS_PAGE_LAND_FALSE);
//STRIP001          rText += GetUsageText( eUse );
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      }
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_PAGE_COMPLETE);
//STRIP001          if ( aDescName.Len() )
//STRIP001          {
//STRIP001              rText += aDescName;
//STRIP001              rText += cpDelim;
//STRIP001          }
//STRIP001          DBG_ASSERT( eNumType <= SVX_NUMBER_NONE, "enum overflow" );
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_PAGE_NUM_BEGIN + eNumType);
//STRIP001          rText += cpDelim;
//STRIP001          if ( bLandscape )
//STRIP001              rText += SVX_RESSTR(RID_SVXITEMS_PAGE_LAND_TRUE);
//STRIP001          else
//STRIP001              rText += SVX_RESSTR(RID_SVXITEMS_PAGE_LAND_FALSE);
//STRIP001          rText += GetUsageText( eUse );
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//------------------------------------------------------------------------
/*N*/ sal_Bool SvxPageItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       case MID_PAGE_NUMTYPE:
/*N*/       {
/*N*/           //! die Konstanten sind nicht mehr in den IDLs ?!?
/*N*/           rVal <<= (sal_Int16)( eNumType );
/*N*/       }
/*N*/       break;
/*N*/       case MID_PAGE_ORIENTATION:
/*N*/           //Landscape= sal_True
/*N*/           rVal = Bool2Any(bLandscape);
/*N*/       break;
/*N*/       case MID_PAGE_LAYOUT     :
/*N*/       {
/*N*/           style::PageStyleLayout eRet;
/*N*/           switch(eUse & 0x0f)
/*N*/           {
/*N*/               case SVX_PAGE_LEFT  : eRet = style::PageStyleLayout_LEFT;      break;
/*N*/               case SVX_PAGE_RIGHT : eRet = style::PageStyleLayout_RIGHT;     break;
/*N*/               case SVX_PAGE_ALL   : eRet = style::PageStyleLayout_ALL;       break;
/*N*/               case SVX_PAGE_MIRROR: eRet = style::PageStyleLayout_MIRRORED; break;
/*N*/               default:
/*N*/                   DBG_ERROR("was fuer ein Layout ist das?");
/*N*/                   return sal_False;
/*N*/           }
/*N*/           rVal <<= eRet;
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   return sal_True;
/*N*/ }
//------------------------------------------------------------------------
/*N*/ sal_Bool SvxPageItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       case MID_PAGE_NUMTYPE:
/*N*/       {
/*N*/           sal_Int32 nValue;
/*N*/           if(!(rVal >>= nValue))
/*N*/               return sal_False;
/*N*/
/*N*/           eNumType = (SvxNumType)nValue;
/*N*/       }
/*N*/       break;
/*N*/       case MID_PAGE_ORIENTATION:
/*N*/           bLandscape = Any2Bool(rVal);
/*N*/       break;
/*N*/       case MID_PAGE_LAYOUT     :
/*N*/       {
/*N*/           style::PageStyleLayout eLayout;
/*N*/           if(!(rVal >>= eLayout))
/*N*/           {
/*N*/               sal_Int32 nValue;
/*?*/               if(!(rVal >>= nValue))
/*?*/                   return sal_False;
/*?*/               eLayout = (style::PageStyleLayout)nValue;
/*N*/           }
/*N*/           eUse &= 0xfff0;
/*N*/           switch( eLayout )
/*N*/           {
/*N*/               case style::PageStyleLayout_LEFT     : eUse |= SVX_PAGE_LEFT ; break;
/*N*/               case style::PageStyleLayout_RIGHT   : eUse |= SVX_PAGE_RIGHT; break;
/*?*/               case style::PageStyleLayout_ALL     : eUse |= SVX_PAGE_ALL  ; break;
/*N*/               case style::PageStyleLayout_MIRRORED: eUse |= SVX_PAGE_MIRROR;break;
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPageItem::Create( SvStream& rStream, USHORT ) const
/*N*/ {
/*N*/   XubString sStr;
/*N*/   BYTE eType;
/*N*/   sal_Bool bLand;
/*N*/   USHORT nUse;
/*N*/
/*N*/   // UNICODE: rStream >> sStr;
/*N*/   rStream.ReadByteString( sStr );
/*N*/
/*N*/   rStream >> eType;
/*N*/   rStream >> bLand;
/*N*/   rStream >> nUse;
/*N*/
/*N*/   SvxPageItem* pPage = new SvxPageItem( Which() );
/*N*/   pPage->SetDescName( sStr );
/*N*/   pPage->SetNumType( (SvxNumType)eType );
/*N*/   pPage->SetLandscape( bLand );
/*N*/   pPage->SetPageUsage( nUse );
/*N*/   return pPage;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvStream& SvxPageItem::Store( SvStream &rStrm, USHORT nItemVersion ) const
/*N*/ {
/*N*/   // UNICODE: rStrm << aDescName;
/*N*/   rStrm.WriteByteString(aDescName);
/*N*/
/*N*/   rStrm << (BYTE)eNumType << bLandscape << eUse;
/*N*/   return rStrm;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   HeaderFooterSet
 --------------------------------------------------------------------*/

/*N*/ SvxSetItem::SvxSetItem( const USHORT nId, const SfxItemSet& rSet ) :
/*N*/
/*N*/   SfxSetItem( nId, rSet )
/*N*/ {
/*N*/ }

/*N*/ SvxSetItem::SvxSetItem( const SvxSetItem& rItem ) :
/*N*/
/*N*/   SfxSetItem( rItem )
/*N*/ {
/*N*/ }

//STRIP001 SvxSetItem::SvxSetItem( const USHORT nId, SfxItemSet* pSet ) :
//STRIP001
//STRIP001  SfxSetItem( nId, pSet )
//STRIP001 {
//STRIP001 }

/*N*/ SfxPoolItem* SvxSetItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SvxSetItem(*this);
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxSetItem::GetPresentation
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

/*N*/ SfxPoolItem* SvxSetItem::Create(SvStream &rStrm, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet* pSet = new SfxItemSet( *GetItemSet().GetPool(),
/*N*/                                      GetItemSet().GetRanges() );
/*N*/
/*N*/   pSet->Load( rStrm );
/*N*/
/*N*/   return new SvxSetItem( Which(), *pSet );
/*N*/ }

/*N*/ SvStream& SvxSetItem::Store(SvStream &rStrm, USHORT nItemVersion) const
/*N*/ {
/*N*/   GetItemSet().Store( rStrm, nItemVersion );
/*N*/
/*N*/   return rStrm;
/*N*/ }


}
