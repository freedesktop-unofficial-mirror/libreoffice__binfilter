/*************************************************************************
 *
 *  $RCSfile: svx_frmitems.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:04 $
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

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif

#ifndef _COM_SUN_STAR_SCRIPT_XTYPECONVERTER_HPP_
#include <com/sun/star/script/XTypeConverter.hpp>
#endif

#include <limits.h>
#include <comphelper/processfactory.hxx>

#pragma hdrstop

#define ITEMID_PAPERBIN 0
#define ITEMID_SIZE     0
#define ITEMID_LRSPACE  0
#define ITEMID_ULSPACE  0
#define ITEMID_PRINT    0
#define ITEMID_OPAQUE   0
#define ITEMID_PROTECT  0
#define ITEMID_SHADOW   0
#define ITEMID_BOX      0
#define ITEMID_BOXINFO  0
#define ITEMID_FMTBREAK 0
#define ITEMID_FMTKEEP  0
#define ITEMID_LINE     0
#define ITEMID_BRUSH    0
#define ITEMID_FRAMEDIR 0


#ifndef _ARGS_HXX //autogen
#include <svtools/args.hxx>
#endif
#ifndef _GRFMGR_HXX //autogen
#include <goodies/grfmgr.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef SVX_LIGHT
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#endif // !SVX_LIGHT
#include <svtools/sbx.hxx>
#define GLOBALOVERFLOW3

#define _SVX_FRMITEMS_CXX

#include <svtools/memberid.hrc>

#ifndef _WALLITEM_HXX
#include <svtools/wallitem.hxx>
#endif
#ifndef _CNTWALL_HXX
#include <svtools/cntwall.hxx>
#endif

#include <rtl/ustring>
#include <rtl/ustrbuf.hxx>

#include <impgrf.hxx>
#include "svxids.hrc"
#include "svxitems.hrc"
#include "dialogs.hrc"

#include "pbinitem.hxx"
#include "sizeitem.hxx"
#include "lrspitem.hxx"
#include "ulspitem.hxx"
#include "prntitem.hxx"
#include "opaqitem.hxx"
#include "protitem.hxx"
#include "shaditem.hxx"
#include "boxitem.hxx"
#include "brkitem.hxx"
#include "keepitem.hxx"
#include "bolnitem.hxx"
#include "brshitem.hxx"
#include "backgrnd.hxx"
#include "frmdiritem.hxx"

#include "itemtype.hxx"
#include "dialmgr.hxx"
#include "svxerr.hxx"
#ifndef _SVX_UNOPRNMS_HXX
#include "unoprnms.hxx"
#endif

#ifndef _COM_SUN_STAR_TABLE_BORDERLINE_HPP_
#include <com/sun/star/table/BorderLine.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLVERTJUSTIFY_HPP_
#include <com/sun/star/table/CellVertJustify.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_SHADOWLOCATION_HPP_
#include <com/sun/star/table/ShadowLocation.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_TABLEBORDER_HPP_
#include <com/sun/star/table/TableBorder.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_SHADOWFORMAT_HPP_
#include <com/sun/star/table/ShadowFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLRANGEADDRESS_HPP_
#include <com/sun/star/table/CellRangeAddress.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLCONTENTTYPE_HPP_
#include <com/sun/star/table/CellContentType.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_TABLEORIENTATION_HPP_
#include <com/sun/star/table/TableOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLHORIJUSTIFY_HPP_
#include <com/sun/star/table/CellHoriJustify.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SORTFIELD_HPP_
#include <com/sun/star/util/SortField.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SORTFIELDTYPE_HPP_
#include <com/sun/star/util/SortFieldType.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLORIENTATION_HPP_
#include <com/sun/star/table/CellOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLADDRESS_HPP_
#include <com/sun/star/table/CellAddress.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_PAGESTYLELAYOUT_HPP_
#include <com/sun/star/style/PageStyleLayout.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_BREAKTYPE_HPP_
#include <com/sun/star/style/BreakType.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_GRAPHICLOCATION_HPP_
#include <com/sun/star/style/GraphicLocation.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HPP_
#include <com/sun/star/awt/Rectangle.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_SELECTION_HPP_
#include <com/sun/star/awt/Selection.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_SIZE_HPP_
#include <com/sun/star/awt/Size.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE2_HPP_
#include <com/sun/star/text/WritingMode2.hpp>
#endif

#include <comphelper/types.hxx>

#ifndef _SVX_UNOMID_HXX
#include <unomid.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::rtl;
using namespace ::com::sun::star;


// Konvertierung fuer UNO
#define TWIP_TO_MM100(TWIP)     ((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
#define MM100_TO_TWIP(MM100)    ((MM100) >= 0 ? (((MM100)*72L+63L)/127L) : (((MM100)*72L-63L)/127L))

// STATIC DATA -----------------------------------------------------------


/*?*/ inline void SetValueProp( XubString& rStr, const sal_uInt16 nValue,
/*?*/                         const sal_uInt16 nProp )
/*?*/ {
/*?*/   if( 100 == nProp )
/*?*/       rStr += String::CreateFromInt32( nValue );
/*?*/   else
/*?*/       ( rStr += String::CreateFromInt32( nProp )) += sal_Unicode('%');
/*?*/ }

/*?*/ inline void SetValueProp( XubString& rStr, const short nValue,
/*?*/                         const sal_uInt16 nProp )
/*?*/ {
/*?*/   if( 100 == nProp )
/*?*/       rStr += String::CreateFromInt32( nValue );
/*?*/   else
/*?*/       ( rStr += String::CreateFromInt32( nProp )) += sal_Unicode('%');
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxPaperBinItem, SfxByteItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxSizeItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxLRSpaceItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxULSpaceItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPrintItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxOpaqueItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxProtectItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxBrushItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxShadowItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxBoxItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxBoxInfoItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxFmtBreakItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxFmtKeepItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxLineItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxFrameDirectionItem, SfxUInt16Item);


// class SvxPaperBinItem ------------------------------------------------

/*N*/ SfxPoolItem* SvxPaperBinItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxPaperBinItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxPaperBinItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << GetValue();
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPaperBinItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 nBin;
/*N*/   rStrm >> nBin;
/*N*/   return new SvxPaperBinItem( Which(), nBin );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPaperBinItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          rText = String::CreateFromInt32( GetValue() );
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          sal_Int8 nValue = GetValue();
//STRIP001
//STRIP001          if ( PAPERBIN_PRINTER_SETTINGS == nValue )
//STRIP001              rText = SVX_RESSTR(RID_SVXSTR_PAPERBIN_SETTINGS);
//STRIP001          else
//STRIP001          {
//STRIP001              rText = SVX_RESSTR(RID_SVXSTR_PAPERBIN);
//STRIP001              rText += sal_Unicode(' ');
//STRIP001              rText += String::CreateFromInt32( nValue );
//STRIP001          }
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxSizeItem -----------------------------------------------------

/*N*/ SvxSizeItem::SvxSizeItem( const sal_uInt16 nId, const Size& rSize ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   aSize( rSize )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxSizeItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/
/*N*/   awt::Size aTmp(aSize.Width(), aSize.Height());
/*N*/     if( bConvert )
/*N*/   {
/*N*/       aTmp.Height = TWIP_TO_MM100(aTmp.Height);
/*N*/       aTmp.Width = TWIP_TO_MM100(aTmp.Width);
/*N*/   }
/*N*/
/*N*/     switch( nMemberId )
/*N*/   {
/*N*/       case MID_SIZE_SIZE:  rVal <<= aTmp; break;
/*N*/       case MID_SIZE_WIDTH: rVal <<= aTmp.Width; break;
/*N*/       case MID_SIZE_HEIGHT: rVal <<= aTmp.Height;  break;
/*N*/         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
/*N*/   }
/*N*/
/*N*/   return sal_True;
/*N*/ }
// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxSizeItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/
/*N*/     switch( nMemberId )
/*N*/   {
/*N*/       case MID_SIZE_SIZE:
/*N*/       {
/*?*/           awt::Size aTmp;
/*?*/           if( rVal >>= aTmp )
/*?*/           {
/*?*/               if(bConvert)
/*?*/               {
/*?*/                   aTmp.Height = MM100_TO_TWIP(aTmp.Height);
/*?*/                   aTmp.Width = MM100_TO_TWIP(aTmp.Width);
/*?*/               }
/*?*/               aSize = Size( aTmp.Width, aTmp.Height );
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               return sal_False;
/*?*/           }
/*N*/       }
/*N*/       break;
/*N*/       case MID_SIZE_WIDTH:
/*N*/       {
/*N*/           sal_Int32 nVal;
/*N*/           if(!(rVal >>= nVal ))
/*N*/               return sal_False;
/*N*/
/*N*/           aSize.Width() = bConvert ? MM100_TO_TWIP(nVal) : nVal;
/*N*/       }
/*N*/       break;
/*N*/       case MID_SIZE_HEIGHT:
/*N*/       {
/*N*/           sal_Int32 nVal;
/*N*/           if(!(rVal >>= nVal))
/*N*/               return sal_True;
/*N*/
/*N*/           aSize.Height() = bConvert ? MM100_TO_TWIP(nVal) : nVal;
/*N*/       }
/*N*/       break;
/*N*/         default: DBG_ERROR("Wrong MemberId!");
/*N*/           return sal_False;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxSizeItem::SvxSizeItem( const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxSizeItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return ( aSize == ( (SvxSizeItem&)rAttr ).GetSize() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxSizeItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxSizeItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxSizeItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001             rText = GetMetricText( aSize.Width(), eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += cpDelim;
//STRIP001             rText += GetMetricText( aSize.Height(), eCoreUnit, ePresUnit, pIntl );
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_SIZE_WIDTH);
//STRIP001             rText += GetMetricText( aSize.Width(), eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          rText += cpDelim;
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_SIZE_HEIGHT);
//STRIP001             rText += GetMetricText( aSize.Height(), eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxSizeItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << aSize.Width();
/*N*/   rStrm << aSize.Height();
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxSizeItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  aSize.Width() = Scale( aSize.Width(), nMult, nDiv );
//STRIP001  aSize.Height() = Scale( aSize.Height(), nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxSizeItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------


/*N*/ SfxPoolItem* SvxSizeItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   long nWidth, nHeight;
/*N*/   rStrm >> nWidth >> nHeight;
/*N*/
/*N*/   SvxSizeItem* pAttr = new SvxSizeItem( Which() );
/*N*/   pAttr->SetSize(Size(nWidth, nHeight));
/*N*/
/*N*/   return pAttr;
/*N*/ }

// class SvxLRSpaceItem --------------------------------------------------

/*N*/ SvxLRSpaceItem::SvxLRSpaceItem( const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   nFirstLineOfst  ( 0 ), nPropFirstLineOfst( 100 ),
/*N*/   nTxtLeft        ( 0 ),
/*N*/   nLeftMargin     ( 0 ), nPropLeftMargin( 100 ),
/*N*/   nRightMargin    ( 0 ), nPropRightMargin( 100 ),
/*N*/   bBulletFI       ( 0 ),
/*N*/   bAutoFirst      ( 0 )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxLRSpaceItem::SvxLRSpaceItem( const sal_Int32 nLeft, const sal_Int32 nRight,
/*N*/                               const sal_Int32 nTLeft, const short nOfset,
/*N*/                               const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   nFirstLineOfst  ( nOfset ), nPropFirstLineOfst( 100 ),
/*N*/   nTxtLeft        ( nTLeft ),
/*N*/   nLeftMargin     ( nLeft ), nPropLeftMargin( 100 ),
/*N*/   nRightMargin    ( nRight ), nPropRightMargin( 100 ),
/*N*/   bBulletFI       ( 0 ),
/*N*/   bAutoFirst      ( 0 )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxLRSpaceItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   sal_Bool bRet = sal_True;
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       //  jetzt alles signed
/*N*/       case MID_L_MARGIN:
/*N*/           rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nLeftMargin) : nLeftMargin);
/*N*/           break;
/*N*/
/*N*/       case MID_TXT_LMARGIN :
/*N*/           rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nTxtLeft) : nTxtLeft);
/*N*/       break;
/*N*/       case MID_R_MARGIN:
/*N*/           rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nRightMargin) : nRightMargin);
/*N*/           break;
/*N*/       case MID_L_REL_MARGIN:
/*N*/           rVal <<= (sal_Int16)nPropLeftMargin;
/*N*/       break;
/*N*/       case MID_R_REL_MARGIN:
/*N*/           rVal <<= (sal_Int16)nPropRightMargin;
/*N*/       break;
/*N*/
/*N*/       case MID_FIRST_LINE_INDENT:
/*N*/           rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nFirstLineOfst) : nFirstLineOfst);
/*N*/           break;
/*N*/
/*N*/       case MID_FIRST_LINE_REL_INDENT:
/*N*/           rVal <<= (sal_Int16)(nPropFirstLineOfst);
/*N*/           break;
/*N*/
/*N*/       case MID_FIRST_AUTO:
/*N*/           rVal = Bool2Any(IsAutoFirst());
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           bRet = sal_False;
/*N*/           DBG_ERROR("unknown MemberId");
/*N*/   }
/*N*/   return bRet;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxLRSpaceItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   sal_Int32 nMaxVal = bConvert ? TWIP_TO_MM100(USHRT_MAX) : USHRT_MAX;
/*N*/   sal_Int32 nVal;
/*N*/   if( nMemberId != MID_FIRST_AUTO &&
/*N*/           nMemberId != MID_L_REL_MARGIN && nMemberId != MID_R_REL_MARGIN)
/*N*/       if(!(rVal >>= nVal))
/*N*/           return sal_False;
/*N*/
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       case MID_L_MARGIN:
/*N*/           SetLeft((sal_Int32)bConvert ? MM100_TO_TWIP(nVal) : nVal);
/*N*/           break;
/*N*/
/*N*/       case MID_TXT_LMARGIN :
/*N*/           SetTxtLeft((sal_Int32)bConvert ? MM100_TO_TWIP(nVal) : nVal);
/*N*/       break;
/*N*/
/*N*/       case MID_R_MARGIN:
/*N*/           SetRight((sal_Int32)    bConvert ? MM100_TO_TWIP(nVal) : nVal);
/*N*/           break;
/*N*/       case MID_L_REL_MARGIN:
/*N*/       case MID_R_REL_MARGIN:
/*N*/       {
/*N*/           sal_Int32 nRel;
/*N*/             if((rVal >>= nRel) && nRel >= 0 && nRel < USHRT_MAX)
/*N*/           {
/*N*/               if(MID_L_REL_MARGIN== nMemberId)
/*N*/                     nPropLeftMargin = (USHORT)nRel;
/*N*/               else
/*N*/                     nPropRightMargin = (USHORT)nRel;
/*N*/           }
/*N*/           else
/*N*/               return FALSE;
/*N*/       }
/*N*/       break;
/*N*/       case MID_FIRST_LINE_INDENT     :
/*N*/             SetTxtFirstLineOfst((short)(bConvert ?  MM100_TO_TWIP(nVal) : nVal));
/*N*/           break;
/*N*/
/*N*/       case MID_FIRST_LINE_REL_INDENT:
/*?*/           SetPropTxtFirstLineOfst ( nVal );
/*N*/           break;
/*N*/
/*N*/       case MID_FIRST_AUTO:
/*N*/           SetAutoFirst( Any2Bool(rVal) );
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           DBG_ERROR("unknown MemberId");
/*N*/           return sal_False;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

// nLeftMargin und nTxtLeft anpassen.

/*N*/ void SvxLRSpaceItem::AdjustLeft()
/*N*/ {
/*N*/   if ( 0 > nFirstLineOfst )
/*N*/       nLeftMargin = nTxtLeft + nFirstLineOfst;
/*N*/   else
/*N*/       nLeftMargin = nTxtLeft;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxLRSpaceItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return (
/*N*/       nLeftMargin == ((SvxLRSpaceItem&)rAttr).GetLeft()  &&
/*N*/       nRightMargin == ((SvxLRSpaceItem&)rAttr).GetRight() &&
/*N*/       nFirstLineOfst == ((SvxLRSpaceItem&)rAttr).GetTxtFirstLineOfst() &&
/*N*/       nPropLeftMargin == ((SvxLRSpaceItem&)rAttr).GetPropLeft()  &&
/*N*/       nPropRightMargin == ((SvxLRSpaceItem&)rAttr).GetPropRight() &&
/*N*/       nPropFirstLineOfst == ((SvxLRSpaceItem&)rAttr).GetPropTxtFirstLineOfst() &&
/*N*/       bBulletFI == ((SvxLRSpaceItem&)rAttr).IsBulletFI() &&
/*N*/       bAutoFirst == ((SvxLRSpaceItem&)rAttr).IsAutoFirst() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLRSpaceItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxLRSpaceItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxLRSpaceItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper* pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      {
//STRIP001          if ( 100 != nPropLeftMargin )
//STRIP001              ( rText = String::CreateFromInt32( nPropLeftMargin )) += sal_Unicode('%');
//STRIP001          else
//STRIP001              rText = GetMetricText( (long)nLeftMargin,
//STRIP001                                        eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += cpDelim;
//STRIP001          if ( 100 != nPropFirstLineOfst )
//STRIP001              ( rText += String::CreateFromInt32( nPropFirstLineOfst )) += sal_Unicode('%');
//STRIP001          else
//STRIP001              rText += GetMetricText( (long)nFirstLineOfst,
//STRIP001                                         eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += cpDelim;
//STRIP001          if ( 100 != nRightMargin )
//STRIP001              ( rText += String::CreateFromInt32( nRightMargin )) += sal_Unicode('%');
//STRIP001          else
//STRIP001              rText += GetMetricText( (long)nRightMargin,
//STRIP001                                         eCoreUnit, ePresUnit, pIntl );
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      }
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_LRSPACE_LEFT);
//STRIP001          if ( 100 != nPropLeftMargin )
//STRIP001              ( rText += String::CreateFromInt32( nPropLeftMargin )) += sal_Unicode('%');
//STRIP001          else
//STRIP001          {
//STRIP001              rText += GetMetricText( (long)nLeftMargin,
//STRIP001                                        eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          }
//STRIP001          rText += cpDelim;
//STRIP001          if ( 100 != nPropFirstLineOfst || nFirstLineOfst )
//STRIP001          {
//STRIP001              rText += SVX_RESSTR(RID_SVXITEMS_LRSPACE_FLINE);
//STRIP001              if ( 100 != nPropFirstLineOfst )
//STRIP001                  ( rText += String::CreateFromInt32( nPropFirstLineOfst ))
//STRIP001                          += sal_Unicode('%');
//STRIP001              else
//STRIP001              {
//STRIP001                  rText += GetMetricText( (long)nFirstLineOfst,
//STRIP001                                             eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001              }
//STRIP001              rText += cpDelim;
//STRIP001          }
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_LRSPACE_RIGHT);
//STRIP001          if ( 100 != nPropRightMargin )
//STRIP001              ( rText += String::CreateFromInt32( nPropRightMargin )) += sal_Unicode('%');
//STRIP001          else
//STRIP001          {
//STRIP001              rText += GetMetricText( (long)nRightMargin,
//STRIP001                                         eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          }
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

// MT: BulletFI: Vor 501 wurde im Outliner das Bullet nicht auf der Position des
// FI positioniert, deshalb muss in aelteren Dokumenten der FI auf 0 stehen.

#define BULLETLR_MARKER 0x599401FE

/*N*/ SvStream& SvxLRSpaceItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   short nSaveFI = nFirstLineOfst;
/*N*/   if ( IsBulletFI() )
/*N*/       ((SvxLRSpaceItem*)this)->SetTxtFirstLineOfst( 0 );  // nLeftMargin wird mitmanipuliert, siehe Create()
/*N*/
/*N*/   sal_uInt16 nMargin = 0;
/*N*/   if( nLeftMargin > 0 )
/*N*/       nMargin = sal_uInt16( nLeftMargin );
/*N*/   rStrm << nMargin;
/*N*/   rStrm << nPropLeftMargin;
/*N*/   if( nRightMargin > 0 )
/*N*/       nMargin = sal_uInt16( nRightMargin );
/*N*/   else
/*N*/       nMargin = 0;
/*N*/   rStrm << nMargin;
/*N*/   rStrm << nPropRightMargin;
/*N*/   rStrm << nFirstLineOfst;
/*N*/   rStrm << nPropFirstLineOfst;
/*N*/   if( nTxtLeft > 0 )
/*N*/       nMargin = sal_uInt16( nTxtLeft );
/*N*/   else
/*N*/       nMargin = 0;
/*N*/   rStrm << nMargin;
/*N*/   if( nItemVersion >= LRSPACE_AUTOFIRST_VERSION )
/*N*/   {
/*N*/       sal_Int8 nAutoFirst = bAutoFirst ? 1 : 0;
/*N*/       if( nItemVersion >= LRSPACE_NEGATIVE_VERSION &&
/*N*/           ( nLeftMargin < 0 || nRightMargin < 0 || nTxtLeft < 0 ) )
/*N*/           nAutoFirst |= 0x80;
/*N*/       rStrm << nAutoFirst;
/*N*/
/*N*/       if ( IsBulletFI() )
/*N*/       {
/*N*/           // Ab 6.0 keine Magicnumber schreiben...
/*N*/           DBG_ASSERT( rStrm.GetVersion() <= SOFFICE_FILEFORMAT_50, "MT: Fileformat SvxLRSpaceItem aendern!" );
/*N*/           rStrm << (sal_uInt32) BULLETLR_MARKER;
/*N*/           rStrm << nSaveFI;
/*N*/       }
/*N*/       if( 0x80 & nAutoFirst )
/*N*/       {
/*N*/           rStrm << nLeftMargin;
/*N*/           rStrm << nRightMargin;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( IsBulletFI() )
/*N*/       ((SvxLRSpaceItem*)this)->SetTxtFirstLineOfst( nSaveFI );
/*N*/
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLRSpaceItem::Create( SvStream& rStrm, sal_uInt16 nVersion ) const
/*N*/ {
/*N*/   sal_uInt16 left, prpleft, right, prpright, prpfirstline, txtleft;
/*N*/   short firstline;
/*N*/   sal_Int8 autofirst = 0;
/*N*/
/*N*/   if ( nVersion >= LRSPACE_AUTOFIRST_VERSION )
/*N*/   {
/*N*/       rStrm >> left >> prpleft >> right >> prpright >> firstline >>
/*N*/                prpfirstline >> txtleft >> autofirst;
/*N*/
/*N*/       sal_uInt32 nPos = rStrm.Tell();
/*N*/       sal_uInt32 nMarker;
/*N*/       rStrm >> nMarker;
/*N*/       if ( nMarker == BULLETLR_MARKER )
/*N*/       {
/*N*/           rStrm >> firstline;
/*N*/           if ( firstline < 0 )
/*N*/               left += firstline;  // s.u.: txtleft = ...
/*N*/       }
/*N*/       else
/*N*/           rStrm.Seek( nPos );
/*N*/   }
/*N*/   else if ( nVersion == LRSPACE_TXTLEFT_VERSION )
/*N*/   {
/*N*/       rStrm >> left >> prpleft >> right >> prpright >> firstline >>
/*N*/                prpfirstline >> txtleft;
/*N*/   }
/*N*/   else if ( nVersion == LRSPACE_16_VERSION )
/*N*/   {
/*N*/       rStrm >> left >> prpleft >> right >> prpright >> firstline >>
/*N*/                prpfirstline;
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       sal_Int8 nL, nR, nFL;
/*?*/       rStrm >> left >> nL >> right >> nR >> firstline >> nFL;
/*?*/       prpleft = (sal_uInt16)nL;
/*?*/       prpright = (sal_uInt16)nR;
/*?*/       prpfirstline = (sal_uInt16)nFL;
/*N*/   }
/*N*/
/*N*/   txtleft = firstline >= 0 ? left : left - firstline;
/*N*/   SvxLRSpaceItem* pAttr = new SvxLRSpaceItem( Which() );
/*N*/
/*N*/   pAttr->nLeftMargin = left;
/*N*/   pAttr->nPropLeftMargin = prpleft;
/*N*/   pAttr->nRightMargin = right;
/*N*/   pAttr->nPropRightMargin = prpright;
/*N*/   pAttr->nFirstLineOfst = firstline;
/*N*/   pAttr->nPropFirstLineOfst = prpfirstline;
/*N*/   pAttr->nTxtLeft = txtleft;
/*N*/   pAttr->bAutoFirst = autofirst & 0x01;
/*N*/   if( nVersion >= LRSPACE_NEGATIVE_VERSION && ( autofirst & 0x80 ) )
/*N*/   {
/*N*/       sal_Int32 nMargin;
/*N*/       rStrm >> nMargin;
/*N*/       pAttr->nLeftMargin = nMargin;
/*N*/       pAttr->nTxtLeft = firstline >= 0 ? nMargin : nMargin - firstline;
/*N*/       rStrm >> nMargin;
/*N*/       pAttr->nRightMargin = nMargin;
/*N*/   }
/*N*/   return pAttr;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxLRSpaceItem::GetVersion( sal_uInt16 nFileVersion ) const
/*N*/ {
/*N*/   return (nFileVersion == SOFFICE_FILEFORMAT_31)
/*N*/              ? LRSPACE_TXTLEFT_VERSION
/*N*/              : LRSPACE_NEGATIVE_VERSION;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxLRSpaceItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  nFirstLineOfst = (short)Scale( nFirstLineOfst, nMult, nDiv );
//STRIP001  nTxtLeft = Scale( nTxtLeft, nMult, nDiv );
//STRIP001  nLeftMargin = Scale( nLeftMargin, nMult, nDiv );
//STRIP001  nRightMargin = Scale( nRightMargin, nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxLRSpaceItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }

// class SvxULSpaceItem --------------------------------------------------

/*N*/ SvxULSpaceItem::SvxULSpaceItem( const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   nUpper( 0 ), nPropUpper( 100 ),
/*N*/   nLower( 0 ), nPropLower( 100 )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxULSpaceItem::SvxULSpaceItem( const sal_uInt16 nUp, const sal_uInt16 nLow,
/*N*/                               const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   nUpper( nUp  ), nPropUpper( 100 ),
/*N*/   nLower( nLow ), nPropLower( 100 )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool    SvxULSpaceItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       //  jetzt alles signed
/*N*/       case  MID_UP_MARGIN:    rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nUpper) : nUpper); break;
/*N*/       case  MID_LO_MARGIN:    rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nLower) : nLower); break;
/*N*/       case MID_UP_REL_MARGIN: rVal <<= (sal_Int16) nPropUpper; break;
/*N*/       case MID_LO_REL_MARGIN: rVal <<= (sal_Int16) nPropLower; break;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxULSpaceItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   sal_Int32 nVal;
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       case MID_UP_MARGIN :
/*N*/           if(!(rVal >>= nVal) || nVal < 0)
/*N*/               return sal_False;
/*N*/           SetUpper((sal_uInt16)bConvert ? MM100_TO_TWIP(nVal) : nVal);
/*N*/           break;
/*N*/       case MID_LO_MARGIN :
/*N*/           if(!(rVal >>= nVal) || nVal < 0)
/*N*/               return sal_False;
/*N*/           SetLower((sal_uInt16)bConvert ? MM100_TO_TWIP(nVal) : nVal);
/*N*/           break;
/*N*/       case MID_UP_REL_MARGIN:
/*N*/       case MID_LO_REL_MARGIN:
/*N*/       {
/*N*/           sal_Int32 nRel;
/*?*/           if((rVal >>= nRel) && nRel > 1 )
/*?*/           {
/*?*/               if(MID_UP_REL_MARGIN == nMemberId)
/*?*/                   nPropUpper = nRel;
/*?*/               else
/*?*/                   nPropLower = nRel;
/*?*/           }
/*?*/           else
/*?*/               return FALSE;
/*?*/       }
/*?*/       break;
/*N*/
/*N*/
/*N*/       default:
/*N*/           DBG_ERROR("unknown MemberId");
/*N*/           return sal_False;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxULSpaceItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return ( nUpper == ( (SvxULSpaceItem&)rAttr ).nUpper &&
/*N*/            nLower == ( (SvxULSpaceItem&)rAttr ).nLower &&
/*N*/            nPropUpper == ( (SvxULSpaceItem&)rAttr ).nPropUpper &&
/*N*/            nPropLower == ( (SvxULSpaceItem&)rAttr ).nPropLower );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxULSpaceItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxULSpaceItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxULSpaceItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      {
//STRIP001          if ( 100 != nPropUpper )
//STRIP001              ( rText = String::CreateFromInt32( nPropUpper )) += sal_Unicode('%');
//STRIP001          else
//STRIP001                 rText = GetMetricText( (long)nUpper, eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += cpDelim;
//STRIP001          if ( 100 != nPropLower )
//STRIP001              ( rText += String::CreateFromInt32( nPropLower )) += sal_Unicode('%');
//STRIP001          else
//STRIP001                 rText += GetMetricText( (long)nLower, eCoreUnit, ePresUnit, pIntl );
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      }
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_ULSPACE_UPPER);
//STRIP001          if ( 100 != nPropUpper )
//STRIP001              ( rText += String::CreateFromInt32( nPropUpper )) += sal_Unicode('%');
//STRIP001          else
//STRIP001          {
//STRIP001                 rText += GetMetricText( (long)nUpper, eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          }
//STRIP001          rText += cpDelim;
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_ULSPACE_LOWER);
//STRIP001          if ( 100 != nPropLower )
//STRIP001              ( rText += String::CreateFromInt32( nPropLower )) += sal_Unicode('%');
//STRIP001          else
//STRIP001          {
//STRIP001                 rText += GetMetricText( (long)nLower, eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          }
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxULSpaceItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << GetUpper()
/*N*/         << GetPropUpper()
/*N*/         << GetLower()
/*N*/         << GetPropLower();
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxULSpaceItem::Create( SvStream& rStrm, sal_uInt16 nVersion ) const
/*N*/ {
/*N*/   sal_uInt16 upper, lower, nPL = 0, nPU = 0;
/*N*/
/*N*/   if ( nVersion == ULSPACE_16_VERSION )
/*N*/       rStrm >> upper >> nPU >> lower >> nPL;
/*N*/   else
/*N*/   {
/*?*/       sal_Int8 nU, nL;
/*?*/       rStrm >> upper >> nU >> lower >> nL;
/*?*/       nPL = (sal_uInt16)nL;
/*?*/       nPU = (sal_uInt16)nU;
/*N*/   }
/*N*/
/*N*/   SvxULSpaceItem* pAttr = new SvxULSpaceItem( Which() );
/*N*/   pAttr->SetUpperValue( upper );
/*N*/   pAttr->SetLowerValue( lower );
/*N*/   pAttr->SetPropUpper( nPU );
/*N*/   pAttr->SetPropLower( nPL );
/*N*/   return pAttr;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxULSpaceItem::GetVersion( sal_uInt16 nFileVersion ) const
/*N*/ {
/*N*/   return ULSPACE_16_VERSION;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxULSpaceItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  nUpper = (sal_uInt16)Scale( nUpper, nMult, nDiv );
//STRIP001  nLower = (sal_uInt16)Scale( nLower, nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxULSpaceItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }


// class SvxPrintItem ----------------------------------------------------

/*N*/ SfxPoolItem* SvxPrintItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxPrintItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxPrintItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << (sal_Int8)GetValue();
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPrintItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 bIsPrint;
/*N*/   rStrm >> bIsPrint;
/*N*/   return new SvxPrintItem( Which(), sal_Bool( bIsPrint != 0 ) );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPrintItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          sal_uInt16 nId = RID_SVXITEMS_PRINT_FALSE;
//STRIP001
//STRIP001          if ( GetValue() )
//STRIP001              nId = RID_SVXITEMS_PRINT_TRUE;
//STRIP001          rText = SVX_RESSTR(nId);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxOpaqueItem ---------------------------------------------------

/*N*/ SfxPoolItem* SvxOpaqueItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxOpaqueItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxOpaqueItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << (sal_Int8)GetValue();
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxOpaqueItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 bIsOpaque;
/*N*/   rStrm >> bIsOpaque;
/*N*/   return new SvxOpaqueItem( Which(), sal_Bool( bIsOpaque != 0 ) );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxOpaqueItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          sal_uInt16 nId = RID_SVXITEMS_OPAQUE_FALSE;
//STRIP001
//STRIP001          if ( GetValue() )
//STRIP001              nId = RID_SVXITEMS_OPAQUE_TRUE;
//STRIP001          rText = SVX_RESSTR(nId);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxProtectItem --------------------------------------------------

/*N*/ int SvxProtectItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return ( bCntnt == ( (SvxProtectItem&)rAttr ).bCntnt &&
/*N*/            bSize  == ( (SvxProtectItem&)rAttr ).bSize  &&
/*N*/            bPos   == ( (SvxProtectItem&)rAttr ).bPos );
/*N*/ }

/*-----------------16.03.98 12:42-------------------
--------------------------------------------------*/
/*N*/ sal_Bool SvxProtectItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   sal_Bool bValue;
/*N*/   switch(nMemberId)
/*N*/   {
/*N*/       case MID_PROTECT_CONTENT :  bValue = bCntnt; break;
/*N*/       case MID_PROTECT_SIZE    :  bValue = bSize; break;
/*N*/       case MID_PROTECT_POSITION:  bValue = bPos; break;
/*N*/       default:
/*N*/           DBG_ERROR("falsche MemberId");
/*N*/           return sal_False;
/*N*/   }
/*N*/
/*N*/   rVal = Bool2Any( bValue );
/*N*/   return sal_True;
/*N*/ }
/*-----------------16.03.98 12:42-------------------

--------------------------------------------------*/
/*N*/ sal_Bool  SvxProtectItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   sal_Bool bVal( Any2Bool(rVal) );
/*N*/   switch(nMemberId)
/*N*/   {
/*N*/       case MID_PROTECT_CONTENT :  bCntnt = bVal;  break;
/*N*/       case MID_PROTECT_SIZE    :  bSize  = bVal;  break;
/*N*/       case MID_PROTECT_POSITION:  bPos   = bVal;  break;
/*N*/       default:
/*N*/           DBG_ERROR("falsche MemberId");
/*N*/           return sal_False;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxProtectItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxProtectItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxProtectItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          sal_uInt16 nId = RID_SVXITEMS_PROT_CONTENT_FALSE;
//STRIP001
//STRIP001          if ( bCntnt )
//STRIP001              nId = RID_SVXITEMS_PROT_CONTENT_TRUE;
//STRIP001          rText = SVX_RESSTR(nId);
//STRIP001          rText += cpDelim;
//STRIP001          nId = RID_SVXITEMS_PROT_SIZE_FALSE;
//STRIP001
//STRIP001          if ( bSize )
//STRIP001              nId = RID_SVXITEMS_PROT_SIZE_TRUE;
//STRIP001          rText += SVX_RESSTR(nId);
//STRIP001          rText += cpDelim;
//STRIP001          nId = RID_SVXITEMS_PROT_POS_FALSE;
//STRIP001
//STRIP001          if ( bPos )
//STRIP001              nId = RID_SVXITEMS_PROT_POS_TRUE;
//STRIP001          rText += SVX_RESSTR(nId);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxProtectItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   sal_Int8 cProt = 0;
/*N*/   if( IsPosProtected() )   cProt |= 0x01;
/*N*/   if( IsSizeProtected() )  cProt |= 0x02;
/*N*/   if( IsCntntProtected() ) cProt |= 0x04;
/*N*/   rStrm << (sal_Int8) cProt;
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxProtectItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 cFlags;
/*N*/   rStrm >> cFlags;
/*N*/   SvxProtectItem* pAttr = new SvxProtectItem( Which() );
/*N*/   pAttr->SetPosProtect( sal_Bool( ( cFlags & 0x01 ) != 0 ) );
/*N*/   pAttr->SetSizeProtect( sal_Bool(  ( cFlags & 0x02 ) != 0 ) );
/*N*/   pAttr->SetCntntProtect( sal_Bool(  ( cFlags & 0x04 ) != 0 ) );
/*N*/   return pAttr;
/*N*/ }

// class SvxShadowItem ---------------------------------------------------

/*N*/ SvxShadowItem::SvxShadowItem( const USHORT nId,
/*N*/                const Color *pColor, const USHORT nW,
/*N*/                const SvxShadowLocation eLoc ) :
/*N*/   SfxEnumItemInterface( nId ),
/*N*/   aShadowColor(COL_GRAY),
/*N*/   nWidth      ( nW ),
/*N*/   eLocation   ( eLoc )
/*N*/ {
/*N*/   if ( pColor )
/*N*/       aShadowColor = *pColor;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxShadowItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/
/*N*/   table::ShadowFormat aShadow;
/*N*/   table::ShadowLocation eSet = table::ShadowLocation_NONE;
/*N*/   switch( eLocation )
/*N*/   {
/*N*/       case SVX_SHADOW_TOPLEFT    : eSet = table::ShadowLocation_TOP_LEFT    ; break;
/*N*/       case SVX_SHADOW_TOPRIGHT   : eSet = table::ShadowLocation_TOP_RIGHT   ; break;
/*N*/       case SVX_SHADOW_BOTTOMLEFT : eSet = table::ShadowLocation_BOTTOM_LEFT ; break;
/*N*/       case SVX_SHADOW_BOTTOMRIGHT: eSet = table::ShadowLocation_BOTTOM_RIGHT; break;
/*N*/   }
/*N*/   aShadow.Location = eSet;
/*N*/     aShadow.ShadowWidth =   bConvert ? TWIP_TO_MM100(nWidth) : nWidth;
/*N*/   aShadow.IsTransparent = aShadowColor.GetTransparency() > 0;
/*N*/   aShadow.Color = aShadowColor.GetRGBColor();
/*N*/
/*N*/     switch ( nMemberId )
/*N*/     {
/*?*/         case MID_LOCATION: rVal <<= aShadow.Location; break;
/*?*/         case MID_WIDTH: rVal <<= aShadow.ShadowWidth; break;
/*?*/         case MID_TRANSPARENT: rVal <<= aShadow.IsTransparent; break;
/*?*/         case MID_BG_COLOR: rVal <<= aShadow.Color; break;
/*N*/         case 0: rVal <<= aShadow; break;
/*N*/         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
/*N*/     }
/*N*/
/*N*/   return sal_True;
/*N*/ }
// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxShadowItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/
/*N*/     table::ShadowFormat aShadow;
/*N*/     uno::Any aAny;
/*N*/     sal_Bool bRet = QueryValue( aAny, bConvert ? CONVERT_TWIPS : 0 ) && ( aAny >>= aShadow );
/*N*/     switch ( nMemberId )
/*N*/     {
/*N*/         case MID_LOCATION:
/*N*/       {
/*?*/           bRet = (rVal >>= aShadow.Location);
/*?*/           if ( !bRet )
/*?*/           {
/*?*/               sal_Int16 nVal;
/*?*/               bRet = (rVal >>= nVal);
/*?*/               aShadow.Location = (table::ShadowLocation) nVal;
/*?*/           }
/*?*/
/*?*/           break;
/*N*/       }
/*N*/
/*N*/         case MID_WIDTH: rVal >>= aShadow.ShadowWidth; break;
/*?*/         case MID_TRANSPARENT: rVal >>= aShadow.IsTransparent; break;
/*?*/         case MID_BG_COLOR: rVal >>= aShadow.Color; break;
/*N*/         case 0: rVal >>= aShadow; break;
/*N*/         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
/*N*/     }
/*N*/
/*N*/     if ( bRet )
/*N*/     {
/*N*/       SvxShadowLocation eSet = SVX_SHADOW_NONE;
/*N*/       switch( aShadow.Location )
/*N*/       {
/*N*/           case table::ShadowLocation_TOP_LEFT    : eLocation = SVX_SHADOW_TOPLEFT; break;
/*N*/           case table::ShadowLocation_TOP_RIGHT   : eLocation = SVX_SHADOW_TOPRIGHT; break;
/*N*/           case table::ShadowLocation_BOTTOM_LEFT : eLocation = SVX_SHADOW_BOTTOMLEFT ; break;
/*N*/           case table::ShadowLocation_BOTTOM_RIGHT: eLocation = SVX_SHADOW_BOTTOMRIGHT; break;
/*N*/       }
/*N*/
/*N*/         nWidth = bConvert ? MM100_TO_TWIP(aShadow.ShadowWidth) : aShadow.ShadowWidth;
/*N*/       Color aSet(aShadow.Color);
/*N*/       aSet.SetTransparency(aShadow.IsTransparent ? 0xff : 0);
/*N*/       aShadowColor = aSet;
/*N*/   }
/*N*/
/*N*/     return bRet;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxShadowItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return ( ( aShadowColor == ( (SvxShadowItem&)rAttr ).aShadowColor ) &&
/*N*/            ( nWidth    == ( (SvxShadowItem&)rAttr ).GetWidth() ) &&
/*N*/            ( eLocation == ( (SvxShadowItem&)rAttr ).GetLocation() ) );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxShadowItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxShadowItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxShadowItem::CalcShadowSpace( sal_uInt16 nShadow ) const
/*N*/ {
/*N*/   sal_uInt16 nSpace = 0;
/*N*/
/*N*/   switch ( nShadow )
/*N*/   {
/*N*/       case SHADOW_TOP:
/*N*/           if ( eLocation == SVX_SHADOW_TOPLEFT ||
/*N*/                eLocation == SVX_SHADOW_TOPRIGHT  )
/*N*/               nSpace = nWidth;
/*N*/           break;
/*N*/
/*N*/       case SHADOW_BOTTOM:
/*N*/           if ( eLocation == SVX_SHADOW_BOTTOMLEFT ||
/*N*/                eLocation == SVX_SHADOW_BOTTOMRIGHT  )
/*N*/               nSpace = nWidth;
/*N*/           break;
/*N*/
/*N*/       case SHADOW_LEFT:
/*N*/           if ( eLocation == SVX_SHADOW_TOPLEFT ||
/*N*/                eLocation == SVX_SHADOW_BOTTOMLEFT )
/*N*/               nSpace = nWidth;
/*N*/           break;
/*N*/
/*N*/       case SHADOW_RIGHT:
/*N*/           if ( eLocation == SVX_SHADOW_TOPRIGHT ||
/*N*/                eLocation == SVX_SHADOW_BOTTOMRIGHT )
/*N*/               nSpace = nWidth;
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           DBG_ERROR( "wrong shadow" );
/*N*/   }
/*N*/   return nSpace;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxShadowItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      {
//STRIP001          rText = ::GetColorString( aShadowColor );
//STRIP001          rText += cpDelim;
//STRIP001          sal_uInt16 nId = RID_SVXITEMS_TRANSPARENT_FALSE;
//STRIP001
//STRIP001          if ( aShadowColor.GetTransparency() )
//STRIP001              nId = RID_SVXITEMS_TRANSPARENT_TRUE;
//STRIP001          rText += SVX_RESSTR(nId);
//STRIP001          rText += cpDelim;
//STRIP001             rText += GetMetricText( (long)nWidth, eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += cpDelim;
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_SHADOW_BEGIN + eLocation);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_SHADOW_COMPLETE);
//STRIP001          rText += ::GetColorString( aShadowColor );
//STRIP001          rText += cpDelim;
//STRIP001
//STRIP001          sal_uInt16 nId = RID_SVXITEMS_TRANSPARENT_FALSE;
//STRIP001          if ( aShadowColor.GetTransparency() )
//STRIP001              nId = RID_SVXITEMS_TRANSPARENT_TRUE;
//STRIP001          rText += SVX_RESSTR(nId);
//STRIP001          rText += cpDelim;
//STRIP001             rText += GetMetricText( (long)nWidth, eCoreUnit, ePresUnit, pIntl );
//STRIP001          rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          rText += cpDelim;
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_SHADOW_BEGIN + eLocation);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxShadowItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << (sal_Int8) GetLocation()
/*N*/         << (sal_uInt16) GetWidth()
/*N*/         << (sal_Bool)(aShadowColor.GetTransparency() > 0)
/*N*/         << GetColor()
/*N*/         << GetColor()
/*N*/         << (sal_Int8)(aShadowColor.GetTransparency() > 0 ? 0 : 1); //BRUSH_NULL : BRUSH_SOLID
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxShadowItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  nWidth = (sal_uInt16)Scale( nWidth, nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxShadowItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxShadowItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 cLoc;
/*N*/   sal_uInt16 nWidth;
/*N*/   sal_Bool bTrans;
/*N*/   Color aColor;
/*N*/   Color aFillColor;
/*N*/   sal_Int8 nStyle;
/*N*/   rStrm >> cLoc >> nWidth
/*N*/         >> bTrans >> aColor >> aFillColor >> nStyle;
/*N*/   aColor.SetTransparency(bTrans ? 0xff : 0);
/*N*/   return new SvxShadowItem( Which(), &aColor, nWidth, (SvxShadowLocation)cLoc );
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ sal_uInt16 SvxShadowItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   return SVX_SHADOW_END;  // SVX_SHADOW_BOTTOMRIGHT + 1
/*?*/ }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxShadowItem::GetValueTextByPos( sal_uInt16 nPos ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( nPos < SVX_SHADOW_END, "enum overflow!" );
//STRIP001  return XubString( SVX_RES( RID_SVXITEMS_SHADOW_BEGIN + nPos ) );
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ sal_uInt16 SvxShadowItem::GetEnumValue() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   return GetLocation();
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ void SvxShadowItem::SetEnumValue( sal_uInt16 nVal )
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); //STRIP001    SetLocation( (const SvxShadowLocation)nVal );
/*?*/ }

// class SvxBorderLine  --------------------------------------------------

/*N*/ SvxBorderLine::SvxBorderLine( const Color *pCol, sal_uInt16 nOut, sal_uInt16 nIn,
/*N*/                             sal_uInt16 nDist ) :
/*N*/
/*N*/   nOutWidth( nOut ),
/*N*/   nInWidth ( nIn ),
/*N*/   nDistance( nDist )
/*N*/
/*N*/ {
/*N*/   if ( pCol )
/*N*/       aColor = *pCol;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxBorderLine::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  nOutWidth = (sal_uInt16)Scale( nOutWidth, nMult, nDiv );
//STRIP001  nInWidth = (sal_uInt16)Scale( nInWidth, nMult, nDiv );
//STRIP001  nDistance = (sal_uInt16)Scale( nDistance, nMult, nDiv );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxBorderLine::operator==( const SvxBorderLine& rCmp ) const
/*N*/ {
/*N*/   return ( ( aColor    == rCmp.GetColor() )    &&
/*N*/            ( nInWidth  == rCmp.GetInWidth() )  &&
/*N*/            ( nOutWidth == rCmp.GetOutWidth() ) &&
/*N*/            ( nDistance == rCmp.GetDistance() ) );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxBorderLine::GetValueString( SfxMapUnit eSrcUnit,
//STRIP001                                    SfxMapUnit eDestUnit,
//STRIP001                                       const IntlWrapper* pIntl,
//STRIP001                                    sal_Bool bMetricStr) const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  sal_uInt16 nResId = 0;
//STRIP001
//STRIP001  if ( 0 == nDistance )
//STRIP001  {
//STRIP001      // einfach Linie
//STRIP001      if ( DEF_LINE_WIDTH_0 == nOutWidth )
//STRIP001          nResId = RID_SINGLE_LINE0;
//STRIP001      else if ( DEF_LINE_WIDTH_1 == nOutWidth )
//STRIP001          nResId = RID_SINGLE_LINE1;
//STRIP001      else if ( DEF_LINE_WIDTH_2 == nOutWidth )
//STRIP001          nResId = RID_SINGLE_LINE2;
//STRIP001      else if ( DEF_LINE_WIDTH_3 == nOutWidth )
//STRIP001          nResId = RID_SINGLE_LINE3;
//STRIP001      else if ( DEF_LINE_WIDTH_4 == nOutWidth )
//STRIP001          nResId = RID_SINGLE_LINE4;
//STRIP001  }
//STRIP001  else if ( DEF_LINE_WIDTH_1 == nDistance )
//STRIP001  {
//STRIP001      // doppelte Linie, kleiner Abstand
//STRIP001      if ( DEF_LINE_WIDTH_0 == nOutWidth && DEF_LINE_WIDTH_0 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE0;
//STRIP001      else if ( DEF_LINE_WIDTH_1 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_1 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE2;
//STRIP001      else if ( DEF_LINE_WIDTH_1 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_2 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE8;
//STRIP001  }
//STRIP001  else if ( DEF_LINE_WIDTH_2 == nDistance )
//STRIP001  {
//STRIP001      // doppelte Linie, gro\ser Abstand
//STRIP001      if ( DEF_LINE_WIDTH_0 == nOutWidth && DEF_LINE_WIDTH_0 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE1;
//STRIP001      else if ( DEF_LINE_WIDTH_2 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_2 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE3;
//STRIP001      else if ( DEF_LINE_WIDTH_1 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_0 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE4;
//STRIP001      else if ( DEF_LINE_WIDTH_2 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_0 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE5;
//STRIP001      else if ( DEF_LINE_WIDTH_3 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_0 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE6;
//STRIP001      else if ( DEF_LINE_WIDTH_2 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_1 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE7;
//STRIP001      else if ( DEF_LINE_WIDTH_3 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_2 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE9;
//STRIP001      else if ( DEF_LINE_WIDTH_2 == nOutWidth &&
//STRIP001                DEF_LINE_WIDTH_3 == nInWidth )
//STRIP001          nResId = RID_DOUBLE_LINE10;
//STRIP001  }
//STRIP001  String aStr;
//STRIP001  aStr += sal_Unicode('(');
//STRIP001  aStr += ::GetColorString( aColor );
//STRIP001  aStr += cpDelim;
//STRIP001
//STRIP001  if ( nResId )
//STRIP001      aStr += SVX_RESSTR(nResId);
//STRIP001  else
//STRIP001  {
//STRIP001      String sMetric = SVX_RESSTR(GetMetricId( eDestUnit ));
//STRIP001         aStr += GetMetricText( (long)nInWidth, eSrcUnit, eDestUnit, pIntl );
//STRIP001      if ( bMetricStr )
//STRIP001          aStr += sMetric;
//STRIP001      aStr += cpDelim;
//STRIP001         aStr += GetMetricText( (long)nOutWidth, eSrcUnit, eDestUnit, pIntl );
//STRIP001      if ( bMetricStr )
//STRIP001          aStr += sMetric;
//STRIP001      aStr += cpDelim;
//STRIP001         aStr += GetMetricText( (long)nDistance, eSrcUnit, eDestUnit, pIntl );
//STRIP001      if ( bMetricStr )
//STRIP001          aStr += sMetric;
//STRIP001  }
//STRIP001  aStr += sal_Unicode(')');
//STRIP001  return aStr;
//STRIP001 #else
//STRIP001  return UniString();
//STRIP001 #endif
//STRIP001 }

// class SvxBoxItem ------------------------------------------------------

/*N*/ SvxBoxItem::SvxBoxItem( const SvxBoxItem& rCpy ) :
/*N*/
/*N*/   SfxPoolItem ( rCpy ),
/*N*/   nTopDist    ( rCpy.nTopDist ),
/*N*/   nBottomDist ( rCpy.nBottomDist ),
/*N*/   nLeftDist   ( rCpy.nLeftDist ),
/*N*/   nRightDist  ( rCpy.nRightDist )
/*N*/
/*N*/ {
/*N*/   pTop    = rCpy.GetTop()     ? new SvxBorderLine( *rCpy.GetTop() )    : 0;
/*N*/   pBottom = rCpy.GetBottom()  ? new SvxBorderLine( *rCpy.GetBottom() ) : 0;
/*N*/   pLeft   = rCpy.GetLeft()    ? new SvxBorderLine( *rCpy.GetLeft() )   : 0;
/*N*/   pRight  = rCpy.GetRight()   ? new SvxBorderLine( *rCpy.GetRight() )  : 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBoxItem::SvxBoxItem( const sal_uInt16 nId ) :
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   pTop        ( 0 ),
/*N*/   pBottom     ( 0 ),
/*N*/   pLeft       ( 0 ),
/*N*/   pRight      ( 0 ),
/*N*/   nTopDist    ( 0 ),
/*N*/   nBottomDist ( 0 ),
/*N*/   nLeftDist   ( 0 ),
/*N*/   nRightDist  ( 0 )
/*N*/
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBoxItem::~SvxBoxItem()
/*N*/ {
/*N*/   delete pTop;
/*N*/   delete pBottom;
/*N*/   delete pLeft;
/*N*/   delete pRight;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBoxItem& SvxBoxItem::operator=( const SvxBoxItem& rBox )
/*N*/ {DBG_ASSERT(0, "STRIP"); return *this;//STRIP001
//STRIP001  nTopDist = rBox.nTopDist;
//STRIP001  nBottomDist = rBox.nBottomDist;
//STRIP001  nLeftDist = rBox.nLeftDist;
//STRIP001  nRightDist = rBox.nRightDist;
//STRIP001  SetLine( rBox.GetTop(), BOX_LINE_TOP );
//STRIP001  SetLine( rBox.GetBottom(), BOX_LINE_BOTTOM );
//STRIP001  SetLine( rBox.GetLeft(), BOX_LINE_LEFT );
//STRIP001  SetLine( rBox.GetRight(), BOX_LINE_RIGHT );
//STRIP001  return *this;
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ inline sal_Bool CmpBrdLn( const SvxBorderLine* pBrd1, const SvxBorderLine* pBrd2 )
/*?*/ {
/*?*/   sal_Bool bRet;
/*?*/   if( 0 != pBrd1 ?  0 == pBrd2 : 0 != pBrd2 )
/*?*/       bRet = sal_False;
/*?*/   else
/*?*/       if( !pBrd1 )
/*?*/           bRet = sal_True;
/*?*/       else
/*?*/           bRet = (*pBrd1 == *pBrd2);
/*?*/   return bRet;
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxBoxItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return (
/*N*/       ( nTopDist == ( (SvxBoxItem&)rAttr ).nTopDist ) &&
/*N*/       ( nBottomDist == ( (SvxBoxItem&)rAttr ).nBottomDist )   &&
/*N*/       ( nLeftDist == ( (SvxBoxItem&)rAttr ).nLeftDist )   &&
/*N*/       ( nRightDist == ( (SvxBoxItem&)rAttr ).nRightDist ) &&
/*N*/       CmpBrdLn( pTop, ( (SvxBoxItem&)rAttr ).GetTop() )           &&
/*N*/       CmpBrdLn( pBottom, ( (SvxBoxItem&)rAttr ).GetBottom() )     &&
/*N*/       CmpBrdLn( pLeft, ( (SvxBoxItem&)rAttr ).GetLeft() )         &&
/*N*/       CmpBrdLn( pRight, ( (SvxBoxItem&)rAttr ).GetRight() ) );
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ table::BorderLine lcl_SvxLineToLine(const SvxBorderLine* pLine, sal_Bool bConvert)
/*N*/ {
/*N*/   table::BorderLine aLine;
/*N*/   if(pLine)
/*N*/   {
/*N*/       aLine.Color          = pLine->GetColor().GetColor() ;
/*N*/       aLine.InnerLineWidth = bConvert ? TWIP_TO_MM100(pLine->GetInWidth() ): pLine->GetInWidth()  ;
/*N*/       aLine.OuterLineWidth = bConvert ? TWIP_TO_MM100(pLine->GetOutWidth()): pLine->GetOutWidth() ;
/*N*/       aLine.LineDistance   = bConvert ? TWIP_TO_MM100(pLine->GetDistance()): pLine->GetDistance() ;
/*N*/   }
/*N*/   else
/*N*/       aLine.Color          = aLine.InnerLineWidth = aLine.OuterLineWidth = aLine.LineDistance  = 0;
/*N*/   return aLine;
/*N*/ }
// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxBoxItem::QueryValue( uno::Any& rVal, BYTE nMemberId  ) const
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   table::BorderLine aRetLine;
/*N*/   sal_uInt16 nDist;
/*N*/   sal_Bool bDistMember = sal_False;
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/     sal_Bool bSerialize = sal_False;
/*N*/   switch(nMemberId)
/*N*/   {
/*N*/         case MID_LEFT_BORDER:
/*N*/             bSerialize = sal_True;      // intentionally no break!
/*N*/       case LEFT_BORDER:
/*N*/           aRetLine = lcl_SvxLineToLine(GetLeft(), bConvert);
/*N*/           break;
/*N*/         case MID_RIGHT_BORDER:
/*N*/             bSerialize = sal_True;      // intentionally no break!
/*N*/       case RIGHT_BORDER:
/*N*/           aRetLine = lcl_SvxLineToLine(GetRight(), bConvert);
/*N*/           break;
/*N*/         case MID_BOTTOM_BORDER:
/*N*/             bSerialize = sal_True;      // intentionally no break!
/*N*/       case BOTTOM_BORDER:
/*N*/           aRetLine = lcl_SvxLineToLine(GetBottom(), bConvert);
/*N*/           break;
/*N*/         case MID_TOP_BORDER:
/*N*/             bSerialize = sal_True;      // intentionally no break!
/*N*/       case TOP_BORDER:
/*N*/           aRetLine = lcl_SvxLineToLine(GetTop(), bConvert);
/*N*/           break;
/*N*/       case BORDER_DISTANCE:
/*?*/           nDist = GetDistance();
/*?*/           bDistMember = sal_True;
/*?*/           break;
/*N*/       case TOP_BORDER_DISTANCE:
/*N*/           nDist = nTopDist;
/*N*/           bDistMember = sal_True;
/*N*/           break;
/*N*/       case BOTTOM_BORDER_DISTANCE:
/*N*/           nDist = nBottomDist;
/*N*/           bDistMember = sal_True;
/*N*/           break;
/*N*/       case LEFT_BORDER_DISTANCE:
/*N*/           nDist = nLeftDist;
/*N*/           bDistMember = sal_True;
/*N*/           break;
/*N*/       case RIGHT_BORDER_DISTANCE:
/*N*/           nDist = nRightDist;
/*N*/           bDistMember = sal_True;
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   if( bDistMember )
/*N*/       rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(nDist) : nDist);
/*N*/   else
/*N*/     {
/*
        if ( bSerialize )
        {
            ::com::sun::star::uno::Sequence < ::com::sun::star::uno::Any > aSeq(4);
            aSeq[0] <<= aRetLine.Color;
            aSeq[1] <<= aRetLine.InnerLineWidth;
            aSeq[2] <<= aRetLine.OuterLineWidth;
            aSeq[3] <<= aRetLine.LineDistance;
            rVal <<= aSeq;
        }
        else
*/
/*N*/             rVal <<= aRetLine;
/*N*/     }
/*N*/
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool lcl_LineToSvxLine(const ::com::sun::star::table::BorderLine& rLine, SvxBorderLine& rSvxLine, sal_Bool bConvert)
/*N*/ {
/*N*/   rSvxLine.SetColor(   Color(rLine.Color));
/*N*/   rSvxLine.SetInWidth( bConvert ? MM100_TO_TWIP(rLine.InnerLineWidth) : rLine.InnerLineWidth  );
/*N*/   rSvxLine.SetOutWidth(bConvert ? MM100_TO_TWIP(rLine.OuterLineWidth) : rLine.OuterLineWidth  );
/*N*/   rSvxLine.SetDistance(bConvert ? MM100_TO_TWIP(rLine.LineDistance    )  : rLine.LineDistance  );
/*N*/   sal_Bool bRet = rLine.InnerLineWidth > 0 || rLine.OuterLineWidth > 0;
/*N*/   return bRet;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxBoxItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/   sal_uInt16 nLine = BOX_LINE_TOP;
/*N*/   sal_Bool bDistMember = sal_False;
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch(nMemberId)
/*N*/   {
/*N*/       case LEFT_BORDER_DISTANCE:
/*N*/           bDistMember = sal_True;
/*N*/       case LEFT_BORDER:
/*N*/         case MID_LEFT_BORDER:
/*N*/           nLine = BOX_LINE_LEFT;
/*N*/           break;
/*N*/       case RIGHT_BORDER_DISTANCE:
/*N*/           bDistMember = sal_True;
/*N*/       case RIGHT_BORDER:
/*N*/         case MID_RIGHT_BORDER:
/*N*/           nLine = BOX_LINE_RIGHT;
/*N*/           break;
/*N*/       case BOTTOM_BORDER_DISTANCE:
/*N*/           bDistMember = sal_True;
/*N*/       case BOTTOM_BORDER:
/*N*/         case MID_BOTTOM_BORDER:
/*N*/           nLine = BOX_LINE_BOTTOM;
/*N*/           break;
/*N*/       case TOP_BORDER_DISTANCE:
/*N*/           bDistMember = sal_True;
/*N*/       case TOP_BORDER:
/*N*/         case MID_TOP_BORDER:
/*N*/           nLine = BOX_LINE_TOP;
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   if( bDistMember || nMemberId == BORDER_DISTANCE )
/*N*/   {
/*N*/       sal_Int32 nDist;
/*N*/       if(!(rVal >>= nDist))
/*N*/           return sal_False;
/*N*/
/*N*/       if(nDist >= 0)
/*N*/       {
/*N*/           if( bConvert )
/*N*/               nDist = MM100_TO_TWIP(nDist);
/*N*/           if( nMemberId == BORDER_DISTANCE )
/*?*/               SetDistance( nDist );
/*N*/           else
/*N*/               SetDistance( nDist, nLine );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SvxBorderLine aLine;
/*N*/         if( !rVal.hasValue() )
/*N*/           return sal_False;
/*N*/
/*N*/         table::BorderLine aBorderLine;
/*N*/         if( rVal >>= aBorderLine )
/*N*/         {
/*N*/             // usual struct
/*N*/         }
/*N*/         else if (rVal.getValueTypeClass() == uno::TypeClass_SEQUENCE )
/*N*/         {
/*N*/             // serialization for basic macro recording
/*?*/             uno::Reference < script::XTypeConverter > xConverter
/*?*/                     ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.script.Converter")),
/*?*/                     uno::UNO_QUERY );
/*?*/             uno::Sequence < uno::Any > aSeq;
/*?*/             uno::Any aNew;
/*?*/             try { aNew = xConverter->convertTo( rVal, ::getCppuType((const uno::Sequence < uno::Any >*)0) ); }
/*?*/             catch (uno::Exception&) {}
/*?*/
/*?*/             aNew >>= aSeq;
/*?*/             if ( aSeq.getLength() == 4 )
/*?*/             {
/*?*/                 sal_Int32 nVal;
/*?*/                 if ( aSeq[0] >>= nVal )
/*?*/                     aBorderLine.Color = nVal;
/*?*/                 if ( aSeq[1] >>= nVal )
/*?*/                     aBorderLine.InnerLineWidth = (sal_Int16) nVal;
/*?*/                 if ( aSeq[2] >>= nVal )
/*?*/                     aBorderLine.OuterLineWidth = (sal_Int16) nVal;
/*?*/                 if ( aSeq[3] >>= nVal )
/*?*/                     aBorderLine.LineDistance = (sal_Int16) nVal;
/*?*/             }
/*?*/             else
/*N*/                 return sal_False;
/*N*/         }
/*N*/         else
/*N*/             return sal_False;
/*N*/
/*N*/         sal_Bool bSet = lcl_LineToSvxLine(aBorderLine, aLine, bConvert);
/*N*/       SetLine(bSet ? &aLine : 0, nLine);
/*N*/   }
/*N*/
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBoxItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxBoxItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxBoxItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      {
//STRIP001          rText.Erase();
//STRIP001
//STRIP001          if ( pTop )
//STRIP001          {
//STRIP001                 rText = pTop->GetValueString( eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += cpDelim;
//STRIP001          }
//STRIP001          if( !(pTop && pBottom && pLeft && pRight &&
//STRIP001                *pTop == *pBottom && *pTop == *pLeft && *pTop == *pRight) )
//STRIP001          {
//STRIP001              if ( pBottom )
//STRIP001              {
//STRIP001                     rText += pBottom->GetValueString( eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += cpDelim;
//STRIP001              }
//STRIP001              if ( pLeft )
//STRIP001              {
//STRIP001                     rText += pLeft->GetValueString( eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += cpDelim;
//STRIP001              }
//STRIP001              if ( pRight )
//STRIP001              {
//STRIP001                     rText += pRight->GetValueString( eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += cpDelim;
//STRIP001              }
//STRIP001          }
//STRIP001             rText += GetMetricText( (long)nTopDist, eCoreUnit, ePresUnit, pIntl );
//STRIP001          if( nTopDist != nBottomDist || nTopDist != nLeftDist ||
//STRIP001              nTopDist != nRightDist )
//STRIP001          {
//STRIP001              (((((rText += cpDelim)
//STRIP001                    += GetMetricText( (long)nBottomDist, eCoreUnit,
//STRIP001                                         ePresUnit, pIntl ))
//STRIP001                    += cpDelim)
//STRIP001                       += GetMetricText( (long)nLeftDist, eCoreUnit, ePresUnit, pIntl ))
//STRIP001                    += cpDelim)
//STRIP001                    += GetMetricText( (long)nRightDist, eCoreUnit,
//STRIP001                                         ePresUnit, pIntl );
//STRIP001          }
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      }
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if( !(pTop || pBottom || pLeft || pRight) )
//STRIP001          {
//STRIP001              rText = SVX_RESSTR(RID_SVXITEMS_BORDER_NONE);
//STRIP001              rText += cpDelim;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rText = SVX_RESSTR(RID_SVXITEMS_BORDER_COMPLETE);
//STRIP001              if( pTop && pBottom && pLeft && pRight &&
//STRIP001                  *pTop == *pBottom && *pTop == *pLeft && *pTop == *pRight )
//STRIP001              {
//STRIP001                     rText += pTop->GetValueString( eCoreUnit, ePresUnit, pIntl, sal_True );
//STRIP001                  rText += cpDelim;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if ( pTop )
//STRIP001                  {
//STRIP001                      rText += SVX_RESSTR(RID_SVXITEMS_BORDER_TOP);
//STRIP001                         rText += pTop->GetValueString( eCoreUnit, ePresUnit, pIntl, sal_True );
//STRIP001                      rText += cpDelim;
//STRIP001                  }
//STRIP001                  if ( pBottom )
//STRIP001                  {
//STRIP001                      rText += SVX_RESSTR(RID_SVXITEMS_BORDER_BOTTOM);
//STRIP001                         rText += pBottom->GetValueString( eCoreUnit, ePresUnit, pIntl, sal_True );
//STRIP001                      rText += cpDelim;
//STRIP001                  }
//STRIP001                  if ( pLeft )
//STRIP001                  {
//STRIP001                      rText += SVX_RESSTR(RID_SVXITEMS_BORDER_LEFT);
//STRIP001                         rText += pLeft->GetValueString( eCoreUnit, ePresUnit, pIntl, sal_True );
//STRIP001                      rText += cpDelim;
//STRIP001                  }
//STRIP001                  if ( pRight )
//STRIP001                  {
//STRIP001                      rText += SVX_RESSTR(RID_SVXITEMS_BORDER_RIGHT);
//STRIP001                         rText += pRight->GetValueString( eCoreUnit, ePresUnit, pIntl, sal_True );
//STRIP001                      rText += cpDelim;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          rText += SVX_RESSTR(RID_SVXITEMS_BORDER_DISTANCE);
//STRIP001          if( nTopDist == nBottomDist && nTopDist == nLeftDist &&
//STRIP001              nTopDist == nRightDist )
//STRIP001          {
//STRIP001              rText += GetMetricText( (long)nTopDist, eCoreUnit,
//STRIP001                                             ePresUnit, pIntl );
//STRIP001              rText += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              (((rText += SVX_RESSTR(RID_SVXITEMS_BORDER_TOP))
//STRIP001                    += GetMetricText( (long)nTopDist, eCoreUnit,
//STRIP001                                         ePresUnit, pIntl ))
//STRIP001                    += SVX_RESSTR(GetMetricId(ePresUnit)))
//STRIP001                    += cpDelim;
//STRIP001              (((rText += SVX_RESSTR(RID_SVXITEMS_BORDER_BOTTOM))
//STRIP001                    += GetMetricText( (long)nBottomDist, eCoreUnit,
//STRIP001                                         ePresUnit, pIntl ))
//STRIP001                    += SVX_RESSTR(GetMetricId(ePresUnit)))
//STRIP001                    += cpDelim;
//STRIP001              (((rText += SVX_RESSTR(RID_SVXITEMS_BORDER_LEFT))
//STRIP001                    += GetMetricText( (long)nLeftDist, eCoreUnit,
//STRIP001                                         ePresUnit, pIntl ))
//STRIP001                    += SVX_RESSTR(GetMetricId(ePresUnit)))
//STRIP001                    += cpDelim;
//STRIP001              ((rText += SVX_RESSTR(RID_SVXITEMS_BORDER_RIGHT))
//STRIP001                    += GetMetricText( (long)nRightDist, eCoreUnit,
//STRIP001                                         ePresUnit, pIntl ))
//STRIP001                    += SVX_RESSTR(GetMetricId(ePresUnit));
//STRIP001          }
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxBoxItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << (sal_uInt16) GetDistance();
/*N*/   const SvxBorderLine* pLine[ 4 ];    // top, left, right, bottom
/*N*/   pLine[ 0 ] = GetTop();
/*N*/   pLine[ 1 ] = GetLeft();
/*N*/   pLine[ 2 ] = GetRight();
/*N*/   pLine[ 3 ] = GetBottom();
/*N*/
/*N*/   for( int i = 0; i < 4; i++ )
/*N*/   {
/*N*/       const SvxBorderLine* l = pLine[ i ];
/*N*/       if( l )
/*N*/       {
/*N*/           rStrm << (sal_Int8) i
/*N*/                 << l->GetColor()
/*N*/                 << (sal_uInt16) l->GetOutWidth()
/*N*/                 << (sal_uInt16) l->GetInWidth()
/*N*/                 << (sal_uInt16) l->GetDistance();
/*N*/       }
/*N*/   }
/*N*/   sal_Int8 cLine = 4;
/*N*/   if( nItemVersion >= BOX_4DISTS_VERSION &&
/*N*/       !(nTopDist == nLeftDist &&
/*N*/         nTopDist == nRightDist &&
/*N*/         nTopDist == nBottomDist) )
/*N*/   {
/*?*/       cLine |= 0x10;
/*N*/   }
/*N*/
/*N*/   rStrm << cLine;
/*N*/
/*N*/   if( nItemVersion >= BOX_4DISTS_VERSION && (cLine & 0x10) != 0 )
/*N*/   {
/*N*/       rStrm << (sal_uInt16)nTopDist
/*N*/             << (sal_uInt16)nLeftDist
/*N*/             << (sal_uInt16)nRightDist
/*?*/             << (sal_uInt16)nBottomDist;
/*N*/   }
/*N*/
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxBoxItem::GetVersion( sal_uInt16 nFFVer ) const
/*N*/ {
/*N*/   DBG_ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/           SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/           SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/           "SvxBoxItem: Gibt es ein neues Fileformat?" );
/*N*/   return SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/          SOFFICE_FILEFORMAT_40==nFFVer ? 0 : BOX_4DISTS_VERSION;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxBoxItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  if ( pTop )     pTop->ScaleMetrics( nMult, nDiv );
//STRIP001  if ( pBottom )  pBottom->ScaleMetrics( nMult, nDiv );
//STRIP001  if ( pLeft )    pLeft->ScaleMetrics( nMult, nDiv );
//STRIP001  if ( pRight )   pBottom->ScaleMetrics( nMult, nDiv );
//STRIP001  nTopDist = (sal_uInt16)Scale( nTopDist, nMult, nDiv );
//STRIP001  nBottomDist = (sal_uInt16)Scale( nBottomDist, nMult, nDiv );
//STRIP001  nLeftDist = (sal_uInt16)Scale( nLeftDist, nMult, nDiv );
//STRIP001  nRightDist = (sal_uInt16)Scale( nRightDist, nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxBoxItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBoxItem::Create( SvStream& rStrm, sal_uInt16 nIVersion ) const
/*N*/ {
/*N*/   sal_uInt16 nDistance;
/*N*/   rStrm >> nDistance;
/*N*/   SvxBoxItem* pAttr = new SvxBoxItem( Which() );
/*N*/
/*N*/   sal_uInt16 aLineMap[4] = { BOX_LINE_TOP, BOX_LINE_LEFT,
/*N*/                          BOX_LINE_RIGHT, BOX_LINE_BOTTOM };
/*N*/
/*N*/   sal_Int8 cLine;
/*N*/   while( sal_True )
/*N*/   {
/*N*/       rStrm >> cLine;
/*N*/
/*N*/       if( cLine > 3 )
/*N*/           break;
/*N*/       sal_uInt16 nOutline, nInline, nDistance;
/*N*/       Color aColor;
/*N*/       rStrm >> aColor >> nOutline >> nInline >> nDistance;
/*N*/       SvxBorderLine aBorder( &aColor, nOutline, nInline, nDistance );
/*N*/
/*N*/       pAttr->SetLine( &aBorder, aLineMap[cLine] );
/*N*/   }
/*N*/
/*N*/   if( nIVersion >= BOX_4DISTS_VERSION && (cLine&0x10) != 0 )
/*N*/   {
/*N*/       for( sal_uInt16 i=0; i < 4; i++ )
/*N*/       {
/*?*/           sal_uInt16 nDist;
/*?*/           rStrm >> nDist;
/*?*/           pAttr->SetDistance( nDist, aLineMap[i] );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pAttr->SetDistance( nDistance );
/*N*/   }
/*N*/
/*N*/   return pAttr;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 const SvxBorderLine *SvxBoxItem::GetLine( sal_uInt16 nLine ) const
//STRIP001 {
//STRIP001  const SvxBorderLine *pRet = 0;
//STRIP001
//STRIP001  switch ( nLine )
//STRIP001  {
//STRIP001      case BOX_LINE_TOP:
//STRIP001          pRet = pTop;
//STRIP001          break;
//STRIP001      case BOX_LINE_BOTTOM:
//STRIP001          pRet = pBottom;
//STRIP001          break;
//STRIP001      case BOX_LINE_LEFT:
//STRIP001          pRet = pLeft;
//STRIP001          break;
//STRIP001      case BOX_LINE_RIGHT:
//STRIP001          pRet = pRight;
//STRIP001          break;
//STRIP001      default:
//STRIP001          DBG_ERROR( "wrong line" );
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void SvxBoxItem::SetLine( const SvxBorderLine* pNew, sal_uInt16 nLine )
/*N*/ {
/*N*/   SvxBorderLine* pTmp = pNew ? new SvxBorderLine( *pNew ) : 0;
/*N*/
/*N*/   switch ( nLine )
/*N*/   {
/*N*/       case BOX_LINE_TOP:
/*N*/           delete pTop;
/*N*/           pTop = pTmp;
/*N*/           break;
/*N*/       case BOX_LINE_BOTTOM:
/*N*/           delete pBottom;
/*N*/           pBottom = pTmp;
/*N*/           break;
/*N*/       case BOX_LINE_LEFT:
/*N*/           delete pLeft;
/*N*/           pLeft = pTmp;
/*N*/           break;
/*N*/       case BOX_LINE_RIGHT:
/*N*/           delete pRight;
/*N*/           pRight = pTmp;
/*N*/           break;
/*N*/       default:
/*N*/           DBG_ERROR( "wrong line" );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxBoxItem::GetDistance() const
/*N*/ {
/*N*/   // The smallest distance that is not 0 will be returned.
/*N*/   sal_uInt16 nDist = nTopDist;
/*N*/   if( nBottomDist && (!nDist || nBottomDist < nDist) )
/*N*/       nDist = nBottomDist;
/*N*/   if( nLeftDist && (!nDist || nLeftDist < nDist) )
/*N*/       nDist = nLeftDist;
/*N*/   if( nRightDist && (!nDist || nRightDist < nDist) )
/*N*/       nDist = nRightDist;
/*N*/
/*N*/   return nDist;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxBoxItem::GetDistance( sal_uInt16 nLine ) const
/*N*/ {
/*N*/   sal_uInt16 nDist = 0;
/*N*/   switch ( nLine )
/*N*/   {
/*N*/       case BOX_LINE_TOP:
/*N*/           nDist = nTopDist;
/*N*/           break;
/*N*/       case BOX_LINE_BOTTOM:
/*N*/           nDist = nBottomDist;
/*N*/           break;
/*N*/       case BOX_LINE_LEFT:
/*N*/           nDist = nLeftDist;
/*N*/           break;
/*N*/       case BOX_LINE_RIGHT:
/*N*/           nDist = nRightDist;
/*N*/           break;
/*N*/       default:
/*N*/           DBG_ERROR( "wrong line" );
/*N*/   }
/*N*/
/*N*/   return nDist;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBoxItem::SetDistance( sal_uInt16 nNew, sal_uInt16 nLine )
/*N*/ {
/*N*/   switch ( nLine )
/*N*/   {
/*N*/       case BOX_LINE_TOP:
/*N*/           nTopDist = nNew;
/*N*/           break;
/*N*/       case BOX_LINE_BOTTOM:
/*N*/           nBottomDist = nNew;
/*N*/           break;
/*N*/       case BOX_LINE_LEFT:
/*N*/           nLeftDist = nNew;
/*N*/           break;
/*N*/       case BOX_LINE_RIGHT:
/*N*/           nRightDist = nNew;
/*N*/           break;
/*N*/       default:
/*N*/           DBG_ERROR( "wrong line" );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxBoxItem::CalcLineSpace( sal_uInt16 nLine, sal_Bool bIgnoreLine ) const
/*N*/ {
/*N*/   SvxBorderLine* pTmp = 0;
/*N*/   sal_uInt16 nDist = 0;
/*N*/   switch ( nLine )
/*N*/   {
/*N*/   case BOX_LINE_TOP:
/*N*/       pTmp = pTop;
/*N*/       nDist = nTopDist;
/*N*/       break;
/*N*/   case BOX_LINE_BOTTOM:
/*N*/       pTmp = pBottom;
/*N*/       nDist = nBottomDist;
/*N*/       break;
/*N*/   case BOX_LINE_LEFT:
/*N*/       pTmp = pLeft;
/*N*/       nDist = nLeftDist;
/*N*/       break;
/*N*/   case BOX_LINE_RIGHT:
/*N*/       pTmp = pRight;
/*N*/       nDist = nRightDist;
/*N*/       break;
/*N*/   default:
/*N*/       DBG_ERROR( "wrong line" );
/*N*/   }
/*N*/
/*N*/   if( pTmp )
/*N*/   {
/*N*/       nDist += pTmp->GetOutWidth();
/*N*/       nDist += pTmp->GetInWidth();
/*N*/       nDist += pTmp->GetDistance();
/*N*/   }
/*N*/   else if( !bIgnoreLine )
/*N*/       nDist = 0;
/*N*/   return nDist;
/*N*/ }

// class SvxBoxInfoItem --------------------------------------------------

/*N*/ SvxBoxInfoItem::SvxBoxInfoItem( const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/
/*N*/   pHori   ( 0 ),
/*N*/   pVert   ( 0 ),
/*N*/   nDefDist( 0 )
/*N*/
/*N*/ {
/*N*/   bTable = bDist = bMinDist = sal_False;
/*N*/   ResetFlags();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBoxInfoItem::SvxBoxInfoItem( const SvxBoxInfoItem& rCpy ) :
/*N*/
/*N*/   SfxPoolItem( rCpy )
/*N*/
/*N*/ {
/*N*/   pHori       = rCpy.GetHori() ? new SvxBorderLine( *rCpy.GetHori() ) : 0;
/*N*/   pVert       = rCpy.GetVert() ? new SvxBorderLine( *rCpy.GetVert() ) : 0;
/*N*/   bTable      = rCpy.IsTable();
/*N*/   bDist       = rCpy.IsDist();
/*N*/   bMinDist    = rCpy.IsMinDist();
/*N*/   nValidFlags = rCpy.nValidFlags;
/*N*/   nDefDist    = rCpy.GetDefDist();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBoxInfoItem::~SvxBoxInfoItem()
/*N*/ {
/*N*/   delete pHori;
/*N*/   delete pVert;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SvxBoxInfoItem &SvxBoxInfoItem::operator=( const SvxBoxInfoItem& rCpy )
//STRIP001 {
//STRIP001  delete pHori;
//STRIP001  delete pVert;
//STRIP001  pHori       = rCpy.GetHori() ? new SvxBorderLine( *rCpy.GetHori() ) : 0;
//STRIP001  pVert       = rCpy.GetVert() ? new SvxBorderLine( *rCpy.GetVert() ) : 0;
//STRIP001  bTable      = rCpy.IsTable();
//STRIP001  bDist       = rCpy.IsDist();
//STRIP001  bMinDist    = rCpy.IsMinDist();
//STRIP001  nValidFlags = rCpy.nValidFlags;
//STRIP001  nDefDist    = rCpy.GetDefDist();
//STRIP001  return *this;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ int SvxBoxInfoItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   SvxBoxInfoItem& rBoxInfo = (SvxBoxInfoItem&)rAttr;
/*N*/
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return (   bTable                    == rBoxInfo.IsTable()
/*N*/           && bDist                     == rBoxInfo.IsDist()
/*N*/           && bMinDist                  == rBoxInfo.IsMinDist()
/*N*/           && nValidFlags               == rBoxInfo.nValidFlags
/*N*/           && nDefDist                  == rBoxInfo.GetDefDist()
/*N*/           && CmpBrdLn( pHori, rBoxInfo.GetHori() )
/*N*/           && CmpBrdLn( pVert, rBoxInfo.GetVert() )
/*N*/          );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBoxInfoItem::SetLine( const SvxBorderLine* pNew, sal_uInt16 nLine )
/*N*/ {
/*N*/   SvxBorderLine* pTmp = pNew ? new SvxBorderLine( *pNew ) : 0;
/*N*/
/*N*/   if ( BOXINFO_LINE_HORI == nLine )
/*N*/   {
/*N*/       delete pHori;
/*N*/       pHori = pTmp;
/*N*/   }
/*N*/   else if ( BOXINFO_LINE_VERT == nLine )
/*N*/   {
/*N*/       delete pVert;
/*N*/       pVert = pTmp;
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR( "wrong line" );
/*N*/ }


// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBoxInfoItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxBoxInfoItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxBoxInfoItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 /*!!!
//STRIP001  ResMgr* pMgr = DIALOG_MGR();
//STRIP001  if ( pHori )
//STRIP001  {
//STRIP001      rText += pHori->GetValueString();
//STRIP001      rText += cpDelim;
//STRIP001  }
//STRIP001  if ( pVert )
//STRIP001  {
//STRIP001      rText += pVert->GetValueString();
//STRIP001      rText += cpDelim;
//STRIP001  }
//STRIP001  if ( bTable )
//STRIP001      rText += String( ResId( RID_SVXITEMS_BOXINF_TABLE_TRUE, pMgr ) );
//STRIP001  else
//STRIP001      rText += String( ResId( RID_SVXITEMS_BOXINF_TABLE_FALSE, pMgr ) );
//STRIP001  rText += cpDelim;
//STRIP001  if ( bDist )
//STRIP001      rText += String( ResId( RID_SVXITEMS_BOXINF_DIST_TRUE, pMgr ) );
//STRIP001  else
//STRIP001      rText += String( ResId( RID_SVXITEMS_BOXINF_DIST_FALSE, pMgr ) );
//STRIP001  rText += cpDelim;
//STRIP001  if ( bMinDist )
//STRIP001      rText += String( ResId( RID_SVXITEMS_BOXINF_MDIST_TRUE, pMgr ) );
//STRIP001  else
//STRIP001      rText += String( ResId( RID_SVXITEMS_BOXINF_MDIST_FALSE, pMgr ) );
//STRIP001  rText += cpDelim;
//STRIP001  rText += nDefDist;
//STRIP001  return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001 */
//STRIP001  rText.Erase();
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxBoxInfoItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   sal_Int8 cFlags = 0;
/*N*/
/*N*/   if ( IsTable() )
/*N*/       cFlags |= 0x01;
/*N*/   if ( IsDist() )
/*N*/       cFlags |= 0x02;
/*N*/   if ( IsMinDist() )
/*N*/       cFlags |= 0x04;
/*N*/   rStrm << (sal_Int8)   cFlags
/*N*/         << (sal_uInt16) GetDefDist();
/*N*/   const SvxBorderLine* pLine[ 2 ];
/*N*/   pLine[ 0 ] = GetHori();
/*N*/   pLine[ 1 ] = GetVert();
/*N*/
/*N*/   for( int i = 0; i < 2; i++ )
/*N*/   {
/*N*/       const SvxBorderLine* l = pLine[ i ];
/*N*/       if( l )
/*N*/       {
/*N*/           rStrm << (char) i
/*N*/                 << l->GetColor()
/*N*/                 << (short) l->GetOutWidth()
/*N*/                 << (short) l->GetInWidth()
/*?*/                 << (short) l->GetDistance();
/*N*/       }
/*N*/   }
/*N*/   rStrm << (char) 2;
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxBoxInfoItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  if ( pHori ) pHori->ScaleMetrics( nMult, nDiv );
//STRIP001  if ( pVert ) pVert->ScaleMetrics( nMult, nDiv );
//STRIP001  nDefDist = (sal_uInt16)Scale( nDefDist, nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxBoxInfoItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBoxInfoItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 cFlags;
/*N*/   sal_uInt16 nDefDist;
/*N*/   rStrm >> cFlags >> nDefDist;
/*N*/
/*N*/   SvxBoxInfoItem* pAttr = new SvxBoxInfoItem( Which() );
/*N*/
/*N*/   pAttr->SetTable  ( ( cFlags & 0x01 ) != 0 );
/*N*/   pAttr->SetDist   ( ( cFlags & 0x02 ) != 0 );
/*N*/   pAttr->SetMinDist( ( cFlags & 0x04 ) != 0 );
/*N*/   pAttr->SetDefDist( nDefDist );
/*N*/
/*N*/   while( sal_True )
/*N*/   {
/*N*/       sal_Int8 cLine;
/*N*/       rStrm >> cLine;
/*N*/
/*N*/       if( cLine > 1 )
/*N*/           break;
/*?*/       short nOutline, nInline, nDistance;
/*?*/       Color aColor;
/*?*/       rStrm >> aColor >> nOutline >> nInline >> nDistance;
/*?*/       SvxBorderLine aBorder( &aColor, nOutline, nInline, nDistance );
/*?*/
/*?*/       switch( cLine )
/*?*/       {
/*?*/           case 0: pAttr->SetLine( &aBorder, BOXINFO_LINE_HORI ); break;
/*?*/           case 1: pAttr->SetLine( &aBorder, BOXINFO_LINE_VERT ); break;
/*?*/       }
/*N*/   }
/*N*/   return pAttr;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBoxInfoItem::ResetFlags()
/*N*/ {
/*N*/   nValidFlags = 0x7F; // alles g"ultig au/ser Disable
/*N*/ }

//STRIP001 sal_Bool SvxBoxInfoItem::QueryValue( uno::Any& rVal, BYTE nMemberId  ) const
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  table::BorderLine aRetLine;
//STRIP001     sal_Int16 nVal=0;
//STRIP001     sal_Bool bIntMember = sal_False;
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001     sal_Bool bSerialize = sal_False;
//STRIP001  switch(nMemberId)
//STRIP001  {
//STRIP001         case MID_HORIZONTAL:
//STRIP001             bSerialize = sal_True;
//STRIP001             aRetLine = lcl_SvxLineToLine( pHori, bConvert);
//STRIP001          break;
//STRIP001         case MID_VERTICAL:
//STRIP001             bSerialize = sal_True;
//STRIP001             aRetLine = lcl_SvxLineToLine( pVert, bConvert);
//STRIP001          break;
//STRIP001         case MID_FLAGS:
//STRIP001             bIntMember = sal_True;
//STRIP001             if ( IsTable() )
//STRIP001                 nVal |= 0x01;
//STRIP001             if ( IsDist() )
//STRIP001                 nVal |= 0x02;
//STRIP001             if ( IsMinDist() )
//STRIP001                 nVal |= 0x04;
//STRIP001             rVal <<= nVal;
//STRIP001             break;
//STRIP001         case MID_VALIDFLAGS:
//STRIP001             bIntMember = sal_True;
//STRIP001             nVal = nValidFlags;
//STRIP001             rVal <<= nVal;
//STRIP001             break;
//STRIP001         case MID_DISTANCE:
//STRIP001             bIntMember = sal_True;
//STRIP001             rVal <<= (sal_Int32)(bConvert ? TWIP_TO_MM100(GetDefDist()) : GetDefDist());
//STRIP001             break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001  }
//STRIP001
//STRIP001     if( !bIntMember )
//STRIP001     {
//STRIP001 /*
//STRIP001         if ( bSerialize )
//STRIP001         {
//STRIP001             ::com::sun::star::uno::Sequence < ::com::sun::star::uno::Any > aSeq(4);
//STRIP001             aSeq[0] <<= aRetLine.Color;
//STRIP001             aSeq[1] <<= aRetLine.InnerLineWidth;
//STRIP001             aSeq[2] <<= aRetLine.OuterLineWidth;
//STRIP001             aSeq[3] <<= aRetLine.LineDistance;
//STRIP001             rVal <<= aSeq;
//STRIP001         }
//STRIP001         else
//STRIP001  */
//STRIP001             rVal <<= aRetLine;
//STRIP001     }
//STRIP001
//STRIP001  return sal_True;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SvxBoxInfoItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  sal_uInt16 nLine = BOX_LINE_TOP;
//STRIP001  sal_Bool bDistMember = sal_False;
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001     sal_Bool bRet;
//STRIP001  switch(nMemberId)
//STRIP001  {
//STRIP001         case MID_HORIZONTAL:
//STRIP001         case MID_VERTICAL:
//STRIP001         {
//STRIP001             if( !rVal.hasValue() )
//STRIP001                 return sal_False;
//STRIP001
//STRIP001             table::BorderLine aBorderLine;
//STRIP001             if( rVal >>= aBorderLine )
//STRIP001             {
//STRIP001                 // usual struct
//STRIP001             }
//STRIP001             else if (rVal.getValueTypeClass() == uno::TypeClass_SEQUENCE )
//STRIP001             {
//STRIP001                 // serialization for basic macro recording
//STRIP001                 uno::Reference < script::XTypeConverter > xConverter
//STRIP001                         ( ::legacy_binfilters::getLegacyProcessServiceFactory())->createInstance(::rtl::OUString::createFromAscii("com.sun.star.script.Converter")),
//STRIP001                         uno::UNO_QUERY );
//STRIP001                 uno::Any aNew;
//STRIP001                 uno::Sequence < uno::Any > aSeq;
//STRIP001                 try { aNew = xConverter->convertTo( rVal, ::getCppuType((const uno::Sequence < uno::Any >*)0) ); }
//STRIP001                 catch (uno::Exception&) {}
//STRIP001
//STRIP001                 if( (aNew >>= aSeq) && aSeq.getLength() == 4 )
//STRIP001                 {
//STRIP001                     sal_Int32 nVal;
//STRIP001                     if ( aSeq[0] >>= nVal )
//STRIP001                         aBorderLine.Color = nVal;
//STRIP001                     if ( aSeq[1] >>= nVal )
//STRIP001                         aBorderLine.InnerLineWidth = (sal_Int16) nVal;
//STRIP001                     if ( aSeq[2] >>= nVal )
//STRIP001                         aBorderLine.OuterLineWidth = (sal_Int16) nVal;
//STRIP001                     if ( aSeq[3] >>= nVal )
//STRIP001                         aBorderLine.LineDistance = (sal_Int16) nVal;
//STRIP001                 }
//STRIP001                 else
//STRIP001                     return sal_False;
//STRIP001             }
//STRIP001             else if (rVal.getValueType() == ::getCppuType((const ::com::sun::star::uno::Sequence < sal_Int16 >*)0) )
//STRIP001             {
//STRIP001                 // serialization for basic macro recording
//STRIP001                 ::com::sun::star::uno::Sequence < sal_Int16 > aSeq;
//STRIP001                 rVal >>= aSeq;
//STRIP001                 if ( aSeq.getLength() == 4 )
//STRIP001                 {
//STRIP001                     aBorderLine.Color = aSeq[0];
//STRIP001                     aBorderLine.InnerLineWidth = aSeq[1];
//STRIP001                     aBorderLine.OuterLineWidth = aSeq[2];
//STRIP001                     aBorderLine.LineDistance = aSeq[3];
//STRIP001                 }
//STRIP001                 else
//STRIP001                     return sal_False;
//STRIP001             }
//STRIP001             else
//STRIP001                 return sal_False;
//STRIP001
//STRIP001             SvxBorderLine aLine;
//STRIP001             sal_Bool bSet = lcl_LineToSvxLine(aBorderLine, aLine, bConvert);
//STRIP001             if ( bSet )
//STRIP001                 SetLine( &aLine, nMemberId == MID_HORIZONTAL ? BOXINFO_LINE_HORI : BOXINFO_LINE_VERT );
//STRIP001             break;
//STRIP001         }
//STRIP001         case MID_FLAGS:
//STRIP001         {
//STRIP001             sal_Int16 nFlags;
//STRIP001             bRet = (rVal >>= nFlags);
//STRIP001             if ( bRet )
//STRIP001             {
//STRIP001                 SetTable  ( ( nFlags & 0x01 ) != 0 );
//STRIP001                 SetDist   ( ( nFlags & 0x02 ) != 0 );
//STRIP001                 SetMinDist( ( nFlags & 0x04 ) != 0 );
//STRIP001             }
//STRIP001
//STRIP001             break;
//STRIP001         }
//STRIP001         case MID_VALIDFLAGS:
//STRIP001         {
//STRIP001             sal_Int16 nFlags;
//STRIP001             bRet = (rVal >>= nFlags);
//STRIP001             if ( bRet )
//STRIP001                 nValidFlags = nFlags;
//STRIP001             break;
//STRIP001         }
//STRIP001         case MID_DISTANCE:
//STRIP001         {
//STRIP001             sal_Int32 nVal;
//STRIP001             bRet = (rVal >>= nVal);
//STRIP001             if ( bRet && nVal>=0 )
//STRIP001             {
//STRIP001                 if( bConvert )
//STRIP001                     nVal = MM100_TO_TWIP(nVal);
//STRIP001                 SetDist( nVal );
//STRIP001             }
//STRIP001             break;
//STRIP001         }
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001  }
//STRIP001
//STRIP001  return sal_True;
//STRIP001 }

// class SvxFmtBreakItem -------------------------------------------------

/*N*/ int SvxFmtBreakItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rAttr ), "unequal types" );
/*N*/
/*N*/   return GetValue() == ( (SvxFmtBreakItem&)rAttr ).GetValue();
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxFmtBreakItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = GetValueTextByPos( GetValue() );
//STRIP001          return ePres;
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxFmtBreakItem::GetValueTextByPos( sal_uInt16 nPos ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( nPos < SVX_BREAK_END, "enum overflow!" );
//STRIP001  XubString aStr( SVX_RES( RID_SVXITEMS_BREAK_BEGIN + nPos ) );
//STRIP001  return aStr;
//STRIP001 }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxFmtBreakItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   style::BreakType eBreak = style::BreakType_NONE;
/*N*/   switch ( (SvxBreak)GetValue() )
/*N*/   {
/*N*/   case SVX_BREAK_COLUMN_BEFORE:   eBreak = style::BreakType_COLUMN_BEFORE; break;
/*N*/   case SVX_BREAK_COLUMN_AFTER:    eBreak = style::BreakType_COLUMN_AFTER ; break;
/*N*/   case SVX_BREAK_COLUMN_BOTH:     eBreak = style::BreakType_COLUMN_BOTH  ; break;
/*N*/   case SVX_BREAK_PAGE_BEFORE:     eBreak = style::BreakType_PAGE_BEFORE  ; break;
/*N*/   case SVX_BREAK_PAGE_AFTER:      eBreak = style::BreakType_PAGE_AFTER   ; break;
/*N*/   case SVX_BREAK_PAGE_BOTH:       eBreak = style::BreakType_PAGE_BOTH    ; break;
/*N*/   }
/*N*/   rVal <<= eBreak;
/*N*/   return sal_True;
/*N*/ }
// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxFmtBreakItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   style::BreakType nBreak;
/*N*/
/*N*/   if(!(rVal >>= nBreak))
/*N*/   {
/*N*/       sal_Int32 nValue;
/*?*/       if(!(rVal >>= nValue))
/*?*/           return sal_False;
/*?*/
/*?*/       nBreak = (style::BreakType) nValue;
/*N*/   }
/*N*/
/*N*/   SvxBreak eBreak = SVX_BREAK_NONE;
/*N*/   switch( nBreak )
/*N*/   {
/*N*/       case style::BreakType_COLUMN_BEFORE:    eBreak = SVX_BREAK_COLUMN_BEFORE; break;
/*?*/       case style::BreakType_COLUMN_AFTER: eBreak = SVX_BREAK_COLUMN_AFTER;  break;
/*?*/       case style::BreakType_COLUMN_BOTH:      eBreak = SVX_BREAK_COLUMN_BOTH;   break;
/*N*/       case style::BreakType_PAGE_BEFORE:      eBreak = SVX_BREAK_PAGE_BEFORE;   break;
/*?*/       case style::BreakType_PAGE_AFTER:       eBreak = SVX_BREAK_PAGE_AFTER;    break;
/*?*/       case style::BreakType_PAGE_BOTH:        eBreak = SVX_BREAK_PAGE_BOTH;     break;
/*N*/   }
/*N*/   SetValue((sal_uInt16) eBreak);
/*N*/
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFmtBreakItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxFmtBreakItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxFmtBreakItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << (sal_Int8)GetValue();
/*N*/   if( FMTBREAK_NOAUTO > nItemVersion )
/*N*/       rStrm << (sal_Int8)0x01;
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxFmtBreakItem::GetVersion( sal_uInt16 nFFVer ) const
/*N*/ {
/*N*/   DBG_ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/           SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/           SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/           "SvxFmtBreakItem: Gibt es ein neues Fileformat?" );
/*N*/   return SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/          SOFFICE_FILEFORMAT_40==nFFVer ? 0 : FMTBREAK_NOAUTO;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFmtBreakItem::Create( SvStream& rStrm, sal_uInt16 nVersion ) const
/*N*/ {
/*N*/   sal_Int8 eBreak, bDummy;
/*N*/   rStrm >> eBreak;
/*N*/   if( FMTBREAK_NOAUTO > nVersion )
/*N*/       rStrm >> bDummy;
/*N*/   return new SvxFmtBreakItem( (const SvxBreak)eBreak, Which() );
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ sal_uInt16 SvxFmtBreakItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   return SVX_BREAK_END;   // SVX_BREAK_PAGE_BOTH + 1
/*?*/ }

// class SvxFmtKeepItem -------------------------------------------------

/*N*/ SfxPoolItem* SvxFmtKeepItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxFmtKeepItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxFmtKeepItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStrm << (sal_Int8)GetValue();
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFmtKeepItem::Create( SvStream& rStrm, sal_uInt16 ) const
/*N*/ {
/*N*/   sal_Int8 bIsKeep;
/*N*/   rStrm >> bIsKeep;
/*N*/   return new SvxFmtKeepItem( sal_Bool( bIsKeep != 0 ), Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxFmtKeepItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          sal_uInt16 nId = RID_SVXITEMS_FMTKEEP_FALSE;
//STRIP001
//STRIP001          if ( GetValue() )
//STRIP001              nId = RID_SVXITEMS_FMTKEEP_TRUE;
//STRIP001          rText = SVX_RESSTR(nId);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxLineItem ------------------------------------------------------

/*?*/ SvxLineItem::SvxLineItem( const sal_uInt16 nId ) :
/*?*/
/*?*/   SfxPoolItem ( nId ),
/*?*/
/*?*/   pLine( NULL )
/*?*/ {
/*?*/ }

// -----------------------------------------------------------------------

//STRIP001 SvxLineItem::SvxLineItem( const SvxLineItem& rCpy ) :
//STRIP001
//STRIP001  SfxPoolItem ( rCpy )
//STRIP001 {
//STRIP001  pLine = rCpy.GetLine() ? new SvxBorderLine( *rCpy.GetLine() ) : 0;
//STRIP001 }


// -----------------------------------------------------------------------

//STRIP001 SvxLineItem::~SvxLineItem()
//STRIP001 {
//STRIP001  delete pLine;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxLineItem& SvxLineItem::operator=( const SvxLineItem& rLine )
//STRIP001 {
//STRIP001  SetLine( rLine.GetLine() );
//STRIP001
//STRIP001  return *this;
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ int SvxLineItem::operator==( const SfxPoolItem& rAttr ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*?*/
//STRIP001  return CmpBrdLn( pLine, ((SvxLineItem&)rAttr).GetLine() );
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ SfxPoolItem* SvxLineItem::Clone( SfxItemPool* ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001    return new SvxLineItem( *this );
/*?*/ }

//STRIP001 sal_Bool SvxLineItem::QueryValue( uno::Any& rVal, BYTE nMemId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemId&CONVERT_TWIPS);
//STRIP001     nMemId &= ~CONVERT_TWIPS;
//STRIP001     sal_Int32 nVal = 0;
//STRIP001     if( pLine )
//STRIP001  {
//STRIP001      switch ( nMemId )
//STRIP001      {
//STRIP001             case MID_FG_COLOR:      nVal = pLine->GetColor().GetColor(); break;
//STRIP001          case MID_OUTER_WIDTH:   nVal = pLine->GetOutWidth();    break;
//STRIP001          case MID_INNER_WIDTH:   nVal = pLine->GetInWidth( );    break;
//STRIP001          case MID_DISTANCE:      nVal = pLine->GetDistance();    break;
//STRIP001          default:
//STRIP001                 DBG_ERROR( "Wrong MemberId" );
//STRIP001                 return sal_False;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     rVal <<= nVal;
//STRIP001     return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SvxLineItem::PutValue( const uno::Any& rVal, BYTE nMemId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemId&CONVERT_TWIPS);
//STRIP001     nMemId &= ~CONVERT_TWIPS;
//STRIP001     sal_Int32 nVal;
//STRIP001     if ( rVal >>= nVal )
//STRIP001     {
//STRIP001         if ( !pLine )
//STRIP001             pLine = new SvxBorderLine;
//STRIP001         switch ( nMemId )
//STRIP001         {
//STRIP001             case MID_FG_COLOR:      pLine->SetColor( Color(nVal) ); break;
//STRIP001             case MID_OUTER_WIDTH:   pLine->SetOutWidth(nVal);   break;
//STRIP001             case MID_INNER_WIDTH:   pLine->SetInWidth( nVal);   break;
//STRIP001             case MID_DISTANCE:      pLine->SetDistance(nVal);   break;
//STRIP001             default:
//STRIP001                 DBG_ERROR( "Wrong MemberId" );
//STRIP001                 return sal_False;
//STRIP001         }
//STRIP001
//STRIP001         return sal_True;
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxLineItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  rText.Erase();
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( pLine )
//STRIP001                 rText = pLine->GetValueString( eCoreUnit, ePresUnit, pIntl,
//STRIP001                  (SFX_ITEM_PRESENTATION_COMPLETE == ePres) );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvStream& SvxLineItem::Store( SvStream& rStrm , sal_uInt16 nItemVersion ) const
//STRIP001 {
//STRIP001  if( pLine )
//STRIP001  {
//STRIP001      rStrm << pLine->GetColor()
//STRIP001            << (short)pLine->GetOutWidth()
//STRIP001            << (short)pLine->GetInWidth()
//STRIP001            << (short)pLine->GetDistance();
//STRIP001  }
//STRIP001  return rStrm;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxLineItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001  if ( pLine ) pLine->ScaleMetrics( nMult, nDiv );
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxLineItem::HasMetrics() const
//STRIP001 {
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxLineItem::Create( SvStream& rStrm, sal_uInt16 ) const
//STRIP001 {
//STRIP001  SvxLineItem* pLine = new SvxLineItem( Which() );
//STRIP001  short        nOutline, nInline, nDistance;
//STRIP001  Color        aColor;
//STRIP001
//STRIP001  rStrm >> aColor >> nOutline >> nInline >> nDistance;
//STRIP001  SvxBorderLine aLine( &aColor, nOutline, nInline, nDistance );
//STRIP001  pLine->SetLine( &aLine );
//STRIP001  return pLine;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void SvxLineItem::SetLine( const SvxBorderLine* pNew )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  delete pLine;
//STRIP001  pLine = pNew ? new SvxBorderLine( *pNew ) : 0;
/*N*/ }

#ifdef WNT
#pragma optimize ( "", off )
#endif

// class SvxBrushItem ----------------------------------------------------

#define LOAD_GRAPHIC    ((sal_uInt16)0x0001)
#define LOAD_LINK       ((sal_uInt16)0x0002)
#define LOAD_FILTER     ((sal_uInt16)0x0004)

// class SvxBrushItem_Impl -----------------------------------------------

class SvxBrushItem_Impl
{
public:
    GraphicObject*  pGraphicObject;
    sal_Int8        nGraphicTransparency; //contains a percentage value which is
                                          //copied to the GraphicObject when necessary
#ifndef SVX_LIGHT
    SfxMediumRef    xMedium;
#endif
    Link            aDoneLink;

    SvxBrushItem_Impl( GraphicObject* p ) : pGraphicObject( p ), nGraphicTransparency(0) {}
};

// class SvxBrushItemLink_Impl -------------------------------------------

class SvxBrushItemLink_Impl : public SfxBrushItemLink
{
    virtual Graphic                     GetGraphic( const String& rLink, const String& rFilter );
    virtual CreateSvxBrushTabPage       GetBackgroundTabpageCreateFunc();
    virtual GetSvxBrushTabPageRanges    GetBackgroundTabpageRanges();
};

// -----------------------------------------------------------------------

/*?*/ Graphic SvxBrushItemLink_Impl::GetGraphic( const String& rLink, const String& rFilter)
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); Graphic aResult; return aResult;//STRIP001 Graphic aResult;
//STRIP001  SvxBrushItem aItem( rLink, rFilter, GPOS_TILED );
//STRIP001  const Graphic* pGraph = aItem.GetGraphic();
//STRIP001  if( pGraph )
//STRIP001      aResult = *pGraph;
//STRIP001  return aResult;
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ CreateSvxBrushTabPage SvxBrushItemLink_Impl::GetBackgroundTabpageCreateFunc()
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 #ifndef SVX_LIGHT
//STRIP001  return (CreateSvxBrushTabPage)SvxBackgroundTabPage::Create;
//STRIP001 #else
//STRIP001  return CreateSvxBrushTabPage();
//STRIP001 #endif
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ GetSvxBrushTabPageRanges SvxBrushItemLink_Impl::GetBackgroundTabpageRanges()
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 #ifndef SVX_LIGHT
//STRIP001  return (GetSvxBrushTabPageRanges)SvxBackgroundTabPage::GetRanges;
//STRIP001 #else
//STRIP001  return GetSvxBrushTabPageRanges();
//STRIP001 #endif
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBrushItem::InitSfxLink()
/*N*/ {
/*N*/   SfxBrushItemLink::Set( new SvxBrushItemLink_Impl );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxBrushItem::SetDoneLink( const Link& rLink )
//STRIP001 {
//STRIP001  pImpl->aDoneLink = rLink;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem( sal_uInt16 nWhich ) :
/*N*/
/*N*/   SfxPoolItem( nWhich ),
/*N*/
/*N*/   aColor      ( COL_TRANSPARENT ),
/*N*/   pImpl       ( new SvxBrushItem_Impl( 0 ) ),
/*N*/   pStrLink    ( NULL ),
/*N*/   pStrFilter  ( NULL ),
/*N*/   eGraphicPos ( GPOS_NONE ),
/*N*/   bLoadAgain  ( sal_True )
/*N*/
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem( const Color& rColor, sal_uInt16 nWhich) :
/*N*/
/*N*/   SfxPoolItem( nWhich ),
/*N*/
/*N*/   aColor      ( rColor ),
/*N*/   pImpl       ( new SvxBrushItem_Impl( 0 ) ),
/*N*/   pStrLink    ( NULL ),
/*N*/   pStrFilter  ( NULL ),
/*N*/   eGraphicPos ( GPOS_NONE ),
/*N*/   bLoadAgain  ( sal_True )
/*N*/
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem( const Graphic& rGraphic, SvxGraphicPosition ePos,
/*N*/                           sal_uInt16 nWhich ) :
/*N*/
/*N*/   SfxPoolItem( nWhich ),
/*N*/
/*N*/   aColor      ( COL_TRANSPARENT ),
/*N*/   pImpl       ( new SvxBrushItem_Impl( new GraphicObject( rGraphic ) ) ),
/*N*/   pStrLink    ( NULL ),
/*N*/   pStrFilter  ( NULL ),
/*N*/   eGraphicPos ( ( GPOS_NONE != ePos ) ? ePos : GPOS_MM ),
/*N*/   bLoadAgain  ( sal_True )
/*N*/
/*N*/ {
/*N*/   DBG_ASSERT( GPOS_NONE != ePos, "SvxBrushItem-Ctor with GPOS_NONE == ePos" );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem( const GraphicObject& rGraphicObj,
/*N*/                           SvxGraphicPosition ePos, sal_uInt16 nWhich ) :
/*N*/
/*N*/   SfxPoolItem( nWhich ),
/*N*/
/*N*/   aColor      ( COL_TRANSPARENT ),
/*N*/   pImpl       ( new SvxBrushItem_Impl( new GraphicObject( rGraphicObj ) ) ),
/*N*/   pStrLink    ( NULL ),
/*N*/   pStrFilter  ( NULL ),
/*N*/   eGraphicPos ( ( GPOS_NONE != ePos ) ? ePos : GPOS_MM ),
/*N*/   bLoadAgain  ( sal_True )
/*N*/
/*N*/ {
/*N*/   DBG_ASSERT( GPOS_NONE != ePos, "SvxBrushItem-Ctor with GPOS_NONE == ePos" );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem(
/*N*/   const String& rLink, const String& rFilter,
/*N*/   SvxGraphicPosition ePos, sal_uInt16 nWhich ) :
/*N*/
/*N*/   SfxPoolItem( nWhich ),
/*N*/
/*N*/   aColor      ( COL_TRANSPARENT ),
/*N*/   pImpl       ( new SvxBrushItem_Impl( NULL ) ),
/*N*/   pStrLink    ( new String( rLink ) ),
/*N*/   pStrFilter  ( new String( rFilter ) ),
/*N*/   eGraphicPos ( ( GPOS_NONE != ePos ) ? ePos : GPOS_MM ),
/*N*/   bLoadAgain  ( sal_True )
/*N*/
/*N*/ {
/*N*/   DBG_ASSERT( GPOS_NONE != ePos, "SvxBrushItem-Ctor with GPOS_NONE == ePos" );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem( SvStream& rStream, sal_uInt16 nVersion,
/*N*/                           sal_uInt16 nWhich ) :
/*N*/
/*N*/   SfxPoolItem( nWhich ),
/*N*/
/*N*/   aColor      ( COL_TRANSPARENT ),
/*N*/   pImpl       ( new SvxBrushItem_Impl( NULL ) ),
/*N*/   pStrLink    ( NULL ),
/*N*/   pStrFilter  ( NULL ),
/*N*/   eGraphicPos ( GPOS_NONE )
/*N*/
/*N*/ {
/*N*/   sal_Bool bTrans;
/*N*/   Color aTempColor;
/*N*/   Color aTempFillColor;
/*N*/   sal_Int8 nStyle;
/*N*/
/*N*/   rStream >> bTrans;
/*N*/   rStream >> aTempColor;
/*N*/   rStream >> aTempFillColor;
/*N*/   rStream >> nStyle;
/*N*/
/*N*/   switch ( nStyle )
/*N*/   {
/*N*/       case 8://BRUSH_25:
/*N*/       {
/*N*/           sal_uInt32  nRed    = aTempColor.GetRed();
/*N*/           sal_uInt32  nGreen  = aTempColor.GetGreen();
/*N*/           sal_uInt32  nBlue   = aTempColor.GetBlue();
/*N*/           nRed   += (sal_uInt32)(aTempFillColor.GetRed())*2;
/*N*/           nGreen += (sal_uInt32)(aTempFillColor.GetGreen())*2;
/*N*/           nBlue  += (sal_uInt32)(aTempFillColor.GetBlue())*2;
/*N*/           aColor = Color( (sal_Int8)(nRed/3), (sal_Int8)(nGreen/3), (sal_Int8)(nBlue/3) );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case 9://BRUSH_50:
/*N*/       {
/*N*/           sal_uInt32  nRed    = aTempColor.GetRed();
/*N*/           sal_uInt32  nGreen  = aTempColor.GetGreen();
/*N*/           sal_uInt32  nBlue   = aTempColor.GetBlue();
/*N*/           nRed   += (sal_uInt32)(aTempFillColor.GetRed());
/*N*/           nGreen += (sal_uInt32)(aTempFillColor.GetGreen());
/*N*/           nBlue  += (sal_uInt32)(aTempFillColor.GetBlue());
/*N*/           aColor = Color( (sal_Int8)(nRed/2), (sal_Int8)(nGreen/2), (sal_Int8)(nBlue/2) );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case 10://BRUSH_75:
/*N*/       {
/*N*/           sal_uInt32  nRed    = aTempColor.GetRed()*2;
/*N*/           sal_uInt32  nGreen  = aTempColor.GetGreen()*2;
/*N*/           sal_uInt32  nBlue   = aTempColor.GetBlue()*2;
/*N*/           nRed   += (sal_uInt32)(aTempFillColor.GetRed());
/*N*/           nGreen += (sal_uInt32)(aTempFillColor.GetGreen());
/*N*/           nBlue  += (sal_uInt32)(aTempFillColor.GetBlue());
/*N*/           aColor = Color( (sal_Int8)(nRed/3), (sal_Int8)(nGreen/3), (sal_Int8)(nBlue/3) );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case 0://BRUSH_NULL:
/*N*/           aColor = Color( COL_TRANSPARENT );
/*N*/       break;
/*N*/
/*N*/       default:
/*N*/           aColor = aTempColor;
/*N*/   }
/*N*/
/*N*/   if ( nVersion >= BRUSH_GRAPHIC_VERSION )
/*N*/   {
/*N*/       sal_uInt16 nDoLoad = 0;
/*N*/       sal_Int8 nPos;
/*N*/
/*N*/       rStream >> nDoLoad;
/*N*/
/*N*/       if ( nDoLoad & LOAD_GRAPHIC )
/*N*/       {
/*N*/           Graphic aGraphic;
/*N*/
/*N*/           rStream >> aGraphic;
/*N*/           pImpl->pGraphicObject = new GraphicObject( aGraphic );
/*N*/
/*N*/           if( SVSTREAM_FILEFORMAT_ERROR == rStream.GetError() )
/*N*/           {
/*?*/               rStream.ResetError();
/*?*/               rStream.SetError( ERRCODE_SVX_GRAPHIC_WRONG_FILEFORMAT|
/*?*/                                 ERRCODE_WARNING_MASK  );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( nDoLoad & LOAD_LINK )
/*N*/       {
/*N*/           String aRel;
/*N*/           // UNICODE: rStream >> aRel;
/*N*/           rStream.ReadByteString(aRel);
/*N*/
/*N*/           String aAbs = INetURLObject::RelToAbs( aRel );
/*N*/           pStrLink = new String( aAbs );
/*N*/       }
/*N*/
/*N*/       if ( nDoLoad & LOAD_FILTER )
/*N*/       {
/*N*/           pStrFilter = new String;
/*N*/           // UNICODE: rStream >> *pStrFilter;
/*N*/           rStream.ReadByteString(*pStrFilter);
/*N*/       }
/*N*/
/*N*/       rStream >> nPos;
/*N*/
/*N*/       eGraphicPos = (SvxGraphicPosition)nPos;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::SvxBrushItem( const SvxBrushItem& rItem ) :
/*N*/
/*N*/   SfxPoolItem( rItem.Which() ),
/*N*/
/*N*/   pImpl       ( new SvxBrushItem_Impl( NULL ) ),
/*N*/   pStrLink    ( NULL ),
/*N*/   pStrFilter  ( NULL ),
/*N*/   eGraphicPos ( GPOS_NONE ),
/*N*/   bLoadAgain  ( sal_True )
/*N*/
/*N*/ {
/*N*/   *this = rItem;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem::~SvxBrushItem()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if( pImpl->xMedium.Is() )
/*?*/       pImpl->xMedium->SetDoneLink( Link() );
/*N*/ #endif
/*N*/   delete pImpl->pGraphicObject;
/*N*/   delete pImpl;
/*N*/   delete pStrLink;
/*N*/   delete pStrFilter;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_uInt16 SvxBrushItem::GetVersion( sal_uInt16 nFileVersion ) const
/*N*/ {
/*N*/   return BRUSH_GRAPHIC_VERSION;
/*N*/ }

// -----------------------------------------------------------------------
/*?*/ inline sal_Int8 lcl_PercentToTransparency(long nPercent)
/*?*/ {
/*?*/     //0xff must not be returned!
/*?*/     return sal_Int8(nPercent ? (50 + 0xfe * nPercent) / 100 : 0);
/*?*/ }
/*?*/ inline sal_Int8 lcl_TransparencyToPercent(sal_Int32 nTrans)
/*?*/ {
/*?*/     return (nTrans * 100 + 127) / 254;
/*?*/ }

/*N*/ sal_Bool SvxBrushItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch( nMemberId)
/*N*/   {
/*N*/       case MID_BACK_COLOR:
/*N*/           rVal <<= (sal_Int32)( aColor.GetColor() );
/*N*/       break;
/*N*/         case MID_BACK_COLOR_R_G_B:
/*N*/             rVal <<= (sal_Int32)( aColor.GetRGBColor() );
/*N*/         break;
/*N*/         case MID_BACK_COLOR_TRANSPARENCY:
/*N*/             rVal <<= lcl_TransparencyToPercent(aColor.GetTransparency());
/*N*/         break;
/*N*/         case MID_GRAPHIC_POSITION:
/*N*/             rVal <<= (style::GraphicLocation)(sal_Int16)eGraphicPos;
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC:
/*N*/           DBG_ERRORFILE( "not implemented" );
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC_TRANSPARENT:
/*N*/             rVal = Bool2Any( aColor.GetTransparency() == 0xff );
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC_URL:
/*N*/       {
/*N*/           OUString sLink;
/*N*/           if ( pStrLink )
/*N*/               sLink = *pStrLink;
/*N*/           else if( pImpl->pGraphicObject )
/*N*/           {
/*N*/               OUString sPrefix(RTL_CONSTASCII_USTRINGPARAM(UNO_NAME_GRAPHOBJ_URLPREFIX));
/*N*/               String sId( pImpl->pGraphicObject->GetUniqueID(),
/*N*/                           RTL_TEXTENCODING_ASCII_US );
/*N*/               sLink = sPrefix;
/*N*/               sLink += OUString(sId);
/*N*/           }
/*N*/           rVal <<= sLink;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC_FILTER:
/*N*/       {
/*N*/           OUString sFilter;
/*N*/           if ( pStrFilter )
/*N*/               sFilter = *pStrFilter;
/*N*/           rVal <<= sFilter;
/*N*/       }
/*N*/       break;
/*N*/         case MID_GRAPHIC_TRANSPARENCY :
/*N*/             rVal <<= pImpl->nGraphicTransparency;
/*N*/         break;
/*N*/   }
/*N*/
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxBrushItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch( nMemberId)
/*N*/   {
/*N*/       case MID_BACK_COLOR:
/*N*/         case MID_BACK_COLOR_R_G_B:
/*N*/         {
/*N*/           sal_Int32 nCol;
/*N*/           if ( !( rVal >>= nCol ) )
/*N*/               return sal_False;
/*N*/             if(MID_BACK_COLOR_R_G_B == nMemberId)
/*N*/             {
/*N*/                 nCol = COLORDATA_RGB( nCol );
/*N*/                 nCol += aColor.GetColor() & 0xff000000;
/*N*/             }
/*N*/             aColor = Color( nCol );
/*N*/       }
/*N*/       break;
/*N*/         case MID_BACK_COLOR_TRANSPARENCY:
/*N*/         {
/*N*/             sal_Int32 nTrans;
/*N*/             if ( !( rVal >>= nTrans ) || nTrans < 0 || nTrans > 100 )
/*N*/               return sal_False;
/*N*/             aColor.SetTransparency(lcl_PercentToTransparency(nTrans));
/*N*/         }
/*N*/         break;
/*N*/
/*N*/       case MID_GRAPHIC_POSITION:
/*N*/       {
/*N*/           style::GraphicLocation eLocation;
/*N*/           if ( !( rVal>>=eLocation ) )
/*N*/           {
/*N*/               sal_Int32 nValue;
/*?*/               if ( !( rVal >>= nValue ) )
/*?*/                   return sal_False;
/*?*/               eLocation = (style::GraphicLocation)nValue;
/*N*/           }
/*N*/           SetGraphicPos( (SvxGraphicPosition)(sal_uInt16)eLocation );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC:
/*N*/           DBG_ERRORFILE( "not implemented" );
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC_TRANSPARENT:
/*N*/           aColor.SetTransparency( Any2Bool( rVal ) ? 0xff : 0 );
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC_URL:
/*N*/       {
/*N*/           if ( rVal.getValueType() == ::getCppuType( (OUString*)0 ) )
/*N*/           {
/*N*/               OUString sLink;
/*N*/               rVal >>= sLink;
/*N*/               if( 0 == sLink.compareToAscii( UNO_NAME_GRAPHOBJ_URLPKGPREFIX,
/*N*/                                 sizeof(UNO_NAME_GRAPHOBJ_URLPKGPREFIX)-1 ) )
/*N*/               {
/*N*/                   DBG_ERROR( "package urls aren't implemented" );
/*N*/               }
/*N*/               else if( 0 == sLink.compareToAscii( UNO_NAME_GRAPHOBJ_URLPREFIX,
/*N*/                                  sizeof(UNO_NAME_GRAPHOBJ_URLPREFIX)-1 ) )
/*N*/               {
/*N*/                   DELETEZ( pStrLink );
/*N*/                   String sTmp( sLink );
/*N*/                   ByteString sId( sTmp.Copy(
/*N*/                                       sizeof(UNO_NAME_GRAPHOBJ_URLPREFIX)-1),
/*N*/                                   RTL_TEXTENCODING_ASCII_US );
/*N*/                   GraphicObject *pOldGrfObj = pImpl->pGraphicObject;
/*N*/                   pImpl->pGraphicObject = new GraphicObject( sId );
/*N*/                     ApplyGraphicTransparency_Impl();
/*N*/                     delete pOldGrfObj;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   SetGraphicLink(sLink);
/*N*/               }
/*N*/               if ( sLink.getLength() && eGraphicPos == GPOS_NONE )
/*N*/                   eGraphicPos = GPOS_MM;
/*N*/               else if( !sLink.getLength() )
/*N*/                   eGraphicPos = GPOS_NONE;
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case MID_GRAPHIC_FILTER:
/*N*/       {
/*N*/           if( rVal.getValueType() == ::getCppuType( (OUString*)0 ) )
/*N*/           {
/*N*/               OUString sLink;
/*N*/               rVal >>= sLink;
/*N*/               SetGraphicFilter( sLink );
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/         case MID_GRAPHIC_TRANSPARENCY :
/*N*/         {
/*N*/             sal_Int32 nTmp;
/*N*/             rVal >>= nTmp;
/*N*/             if(nTmp >= 0 && nTmp <= 100)
/*N*/             {
/*N*/                 pImpl->nGraphicTransparency = sal_Int8(nTmp);
/*N*/                 if(pImpl->pGraphicObject)
/*N*/                     ApplyGraphicTransparency_Impl();
/*N*/             }
/*N*/         }
/*N*/         break;
/*N*/     }
/*N*/
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxBrushItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( GPOS_NONE  == eGraphicPos )
//STRIP001          {
//STRIP001              rText = ::GetColorString( aColor );
//STRIP001              rText += cpDelim;
//STRIP001              sal_uInt16 nId = RID_SVXITEMS_TRANSPARENT_FALSE;
//STRIP001
//STRIP001              if ( aColor.GetTransparency() )
//STRIP001                  nId = RID_SVXITEMS_TRANSPARENT_TRUE;
//STRIP001              rText += SVX_RESSTR(nId);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rText = SVX_RESSTR(RID_SVXITEMS_GRAPHIC);
//STRIP001          }
//STRIP001
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxBrushItem& SvxBrushItem::operator=( const SvxBrushItem& rItem )
/*N*/ {
/*N*/   aColor = rItem.aColor;
/*N*/   eGraphicPos = rItem.eGraphicPos;
/*N*/
/*N*/   DELETEZ( pImpl->pGraphicObject );
/*N*/   DELETEZ( pStrLink );
/*N*/   DELETEZ( pStrFilter );
/*N*/
/*N*/   if ( GPOS_NONE != eGraphicPos )
/*N*/   {
/*N*/       if ( rItem.pStrLink )
/*N*/           pStrLink = new String( *rItem.pStrLink );
/*N*/       if ( rItem.pStrFilter )
/*N*/           pStrFilter = new String( *rItem.pStrFilter );
/*N*/       if ( rItem.pImpl->pGraphicObject )
/*N*/         {
/*N*/           pImpl->pGraphicObject = new GraphicObject( *rItem.pImpl->pGraphicObject );
/*N*/         }
/*N*/   }
/*N*/     pImpl->nGraphicTransparency = rItem.pImpl->nGraphicTransparency;
/*N*/   return *this;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxBrushItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   SvxBrushItem& rCmp = (SvxBrushItem&)rAttr;
/*N*/     sal_Bool bEqual = ( aColor == rCmp.aColor && eGraphicPos == rCmp.eGraphicPos &&
/*N*/         pImpl->nGraphicTransparency == rCmp.pImpl->nGraphicTransparency);
/*N*/
/*N*/   if ( bEqual )
/*N*/   {
/*N*/       if ( GPOS_NONE != eGraphicPos )
/*N*/       {
/*N*/           if ( !rCmp.pStrLink )
/*N*/               bEqual = !pStrLink;
/*N*/           else
/*N*/               bEqual = pStrLink && ( *pStrLink == *rCmp.pStrLink );
/*N*/
/*N*/           if ( bEqual )
/*N*/           {
/*N*/               if ( !rCmp.pStrFilter )
/*N*/                   bEqual = !pStrFilter;
/*N*/               else
/*N*/                   bEqual = pStrFilter && ( *pStrFilter == *rCmp.pStrFilter );
/*N*/           }
/*N*/
/*N*/           if ( bEqual && !rCmp.pStrLink )
/*N*/           {
/*N*/               if ( !rCmp.pImpl->pGraphicObject )
/*?*/                   bEqual = !pImpl->pGraphicObject;
/*N*/               else
/*N*/                   bEqual = pImpl->pGraphicObject &&
/*N*/                              ( *pImpl->pGraphicObject == *rCmp.pImpl->pGraphicObject );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bEqual;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBrushItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxBrushItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBrushItem::Create( SvStream& rStream, sal_uInt16 nVersion ) const
/*N*/ {
/*N*/   return new SvxBrushItem( rStream, nVersion, Which() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxBrushItem::Store( SvStream& rStream , sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   rStream << (sal_Bool)sal_False;
/*N*/   rStream << aColor;
/*N*/   rStream << aColor;
/*N*/   rStream << (sal_Int8)(aColor.GetTransparency() > 0 ? 0 : 1); //BRUSH_NULL : BRUSH_SOLID
/*N*/
/*N*/   sal_uInt16 nDoLoad = 0;
/*N*/
/*N*/   if ( pImpl->pGraphicObject && !pStrLink )
/*N*/       nDoLoad |= LOAD_GRAPHIC;
/*N*/   if ( pStrLink )
/*N*/       nDoLoad |= LOAD_LINK;
/*N*/   if ( pStrFilter )
/*N*/       nDoLoad |= LOAD_FILTER;
/*N*/   rStream << nDoLoad;
/*N*/
/*N*/   if ( pImpl->pGraphicObject && !pStrLink )
/*N*/       rStream << pImpl->pGraphicObject->GetGraphic();
/*N*/   if ( pStrLink )
/*N*/   {
/*N*/       String aRel = INetURLObject::AbsToRel( *pStrLink );
/*N*/       // UNICODE: rStream << aRel;
/*N*/       rStream.WriteByteString(aRel);
/*N*/   }
/*N*/   if ( pStrFilter )
/*N*/   {
/*N*/       // UNICODE: rStream << *pStrFilter;
/*?*/       rStream.WriteByteString(*pStrFilter);
/*N*/   }
/*N*/   rStream << (sal_Int8)eGraphicPos;
/*N*/   return rStream;
/*N*/ }

// -----------------------------------------------------------------------
// const wegcasten, da const als logisches const zu verstehen ist
// wenn GetGraphic() gerufen wird, soll sich das Item darum kuemmern,
// eine gelinkte Grafik zu holen.

GraphicFilter* GetGrfFilter();

//STRIP001 IMPL_STATIC_LINK( SvxBrushItem, DoneHdl_Impl, void*, EMPTYARG )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  pThis->pImpl->pGraphicObject = new GraphicObject;
//STRIP001  SvStream* pStream = pThis->pImpl->xMedium->GetInStream();
//STRIP001  if( pStream && !pStream->GetError() )
//STRIP001  {
//STRIP001      Graphic aGraphic;
//STRIP001      int nRes;
//STRIP001      pStream->Seek( STREAM_SEEK_TO_BEGIN );
//STRIP001      nRes = GetGrfFilter()->
//STRIP001          ImportGraphic( aGraphic, *pThis->pStrLink, *pStream,
//STRIP001                         GRFILTER_FORMAT_DONTKNOW, NULL, GRFILTER_I_FLAGS_DONT_SET_LOGSIZE_FOR_JPEG );
//STRIP001
//STRIP001      if( nRes != GRFILTER_OK )
//STRIP001      {
//STRIP001          DELETEZ( pThis->pImpl->pGraphicObject );
//STRIP001          pThis->bLoadAgain = sal_False;
//STRIP001      }
//STRIP001      else
//STRIP001         {
//STRIP001          pThis->pImpl->pGraphicObject->SetGraphic( aGraphic );
//STRIP001             pThis->ApplyGraphicTransparency_Impl();
//STRIP001         }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      DELETEZ( pThis->pImpl->pGraphicObject );
//STRIP001      pThis->bLoadAgain = sal_False;
//STRIP001  }
//STRIP001
//STRIP001  pThis->pImpl->xMedium.Clear();
//STRIP001  pThis->pImpl->aDoneLink.Call( pThis );
//STRIP001 #endif
//STRIP001  return 0;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SvxBrushItem::PurgeGraphic() const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  PurgeMedium();
//STRIP001  DELETEZ( pImpl->pGraphicObject );
//STRIP001  ((SvxBrushItem*)this)->bLoadAgain = sal_True;
//STRIP001 #endif
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SvxBrushItem::PurgeMedium() const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  pImpl->xMedium.Clear();
//STRIP001 #endif
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ const GraphicObject* SvxBrushItem::GetGraphicObject( SfxObjectShell* pSh ) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( bLoadAgain && pStrLink && !pImpl->pGraphicObject && !pImpl->xMedium.Is() )
/*N*/   // wenn Grafik schon geladen, als Cache benutzen
/*N*/   {
/*?*/       if( pSh && pSh->IsAbortingImport() )
/*?*/       {
/*?*/           SvxBrushItem* pThis = (SvxBrushItem*)this;
/*?*/           pThis->bLoadAgain = sal_False;
/*?*/           return 0;
/*?*/       }
/*?*/       //JP 29.6.2001: only with "valid" names - empty names now allowed
/*?*/       if( pStrLink->Len() )
/*?*/       {
/*?*/           pImpl->xMedium = new SfxMedium(
/*?*/               *pStrLink, STREAM_STD_READ, sal_False );
/*?*/
/*?*/           pImpl->xMedium->SetTransferPriority( SFX_TFPRIO_VISIBLE_LOWRES_GRAPHIC );
/*?*/           if( pImpl->xMedium->IsRemote() )
/*?*/           {
/*?*/               if( pSh )
/*?*/                   pSh->RegisterTransfer( *pImpl->xMedium );
/*?*/               else
/*?*/                   DBG_WARNING( "SvxBrushItem::GetGraphic ohne DocShell" );
/*?*/           }
/*?*/
/*?*/           SfxMediumRef xRef( pImpl->xMedium );
/*?*/           // Ref halten wg. synchr. DoneCallback
/*?*/           if( pImpl->aDoneLink.IsSet() )
/*?*/           {
/*?*/               // Auf besonderen Wunsch des Writers wird der synchrone und der
/*?*/               // asynchrone Fall was die Benachrichtigung angeht unterschiedlich
/*?*/               // behandelt. Der Callback erfolgt nur bei asynchronem Eintreffen
/*?*/               // der Daten
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/
//STRIP001 /*?*/                Link aTmp = pImpl->aDoneLink;
//STRIP001 /*?*/                pImpl->aDoneLink = Link();
//STRIP001 /*?*/                pImpl->xMedium->DownLoad(
//STRIP001 /*?*/                    STATIC_LINK( this, SvxBrushItem, DoneHdl_Impl ) );
//STRIP001 /*?*/                pImpl->aDoneLink = aTmp;
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/                pImpl->xMedium->DownLoad( );
//STRIP001 /*?*/                DoneHdl_Impl( (SvxBrushItem*)this, 0 );
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/   return pImpl->pGraphicObject;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ const Graphic* SvxBrushItem::GetGraphic( SfxObjectShell* pSh ) const
/*N*/ {
/*N*/   const GraphicObject* pGrafObj = GetGraphicObject( pSh );
/*N*/   return( pGrafObj ? &( pGrafObj->GetGraphic() ) : NULL );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBrushItem::SetGraphicPos( SvxGraphicPosition eNew )
/*N*/ {
/*N*/   eGraphicPos = eNew;
/*N*/
/*N*/   if ( GPOS_NONE == eGraphicPos )
/*N*/   {
/*N*/       DELETEZ( pImpl->pGraphicObject );
/*N*/       DELETEZ( pStrLink );
/*N*/       DELETEZ( pStrFilter );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( !pImpl->pGraphicObject && !pStrLink )
/*N*/       {
/*N*/           pImpl->pGraphicObject = new GraphicObject; // dummy anlegen
/*N*/       }
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBrushItem::SetGraphic( const Graphic& rNew )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( !pStrLink )
//STRIP001  {
//STRIP001      if ( pImpl->pGraphicObject )
//STRIP001          pImpl->pGraphicObject->SetGraphic( rNew );
//STRIP001      else
//STRIP001          pImpl->pGraphicObject = new GraphicObject( rNew );
//STRIP001
//STRIP001         ApplyGraphicTransparency_Impl();
//STRIP001
//STRIP001         if ( GPOS_NONE == eGraphicPos )
//STRIP001          eGraphicPos = GPOS_MM; // None waere Brush, also Default: Mitte
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR( "SetGraphic() on linked graphic! :-/" );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxBrushItem::SetGraphicObject( const GraphicObject& rNewObj )
//STRIP001 {
//STRIP001  if ( !pStrLink )
//STRIP001  {
//STRIP001      if ( pImpl->pGraphicObject )
//STRIP001          *pImpl->pGraphicObject = rNewObj;
//STRIP001      else
//STRIP001          pImpl->pGraphicObject = new GraphicObject( rNewObj );
//STRIP001
//STRIP001         ApplyGraphicTransparency_Impl();
//STRIP001
//STRIP001         if ( GPOS_NONE == eGraphicPos )
//STRIP001          eGraphicPos = GPOS_MM; // None waere Brush, also Default: Mitte
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR( "SetGraphic() on linked graphic! :-/" );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void SvxBrushItem::SetGraphicLink( const String& rNew )
/*N*/ {
/*N*/   if ( !rNew.Len() )
/*N*/       DELETEZ( pStrLink );
/*N*/   else
/*N*/   {
/*N*/       if ( pStrLink )
/*N*/           *pStrLink = rNew;
/*N*/       else
/*N*/           pStrLink = new String( rNew );
/*N*/
/*N*/       DELETEZ( pImpl->pGraphicObject );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBrushItem::SetGraphicFilter( const String& rNew )
/*N*/ {
/*N*/   if ( !rNew.Len() )
/*N*/       DELETEZ( pStrFilter );
/*N*/   else
/*N*/   {
/*?*/       if ( pStrFilter )
/*?*/           *pStrFilter = rNew;
/*?*/       else
/*?*/           pStrFilter = new String( rNew );
/*N*/   }
/*N*/ }

//static
//STRIP001 SvxGraphicPosition SvxBrushItem::WallpaperStyle2GraphicPos( WallpaperStyle eStyle )
//STRIP001 {
//STRIP001  SvxGraphicPosition eResult;
//STRIP001  // der Switch ist nicht der schnellste, dafuer aber am sichersten
//STRIP001  switch( eStyle )
//STRIP001  {
//STRIP001      case WALLPAPER_NULL: eResult = GPOS_NONE; break;
//STRIP001      case WALLPAPER_TILE: eResult = GPOS_TILED; break;
//STRIP001      case WALLPAPER_CENTER: eResult = GPOS_MM; break;
//STRIP001      case WALLPAPER_SCALE: eResult = GPOS_AREA; break;
//STRIP001      case WALLPAPER_TOPLEFT: eResult = GPOS_LT; break;
//STRIP001      case WALLPAPER_TOP: eResult = GPOS_MT; break;
//STRIP001      case WALLPAPER_TOPRIGHT: eResult = GPOS_RT; break;
//STRIP001      case WALLPAPER_LEFT: eResult = GPOS_LM; break;
//STRIP001      case WALLPAPER_RIGHT: eResult = GPOS_RM; break;
//STRIP001      case WALLPAPER_BOTTOMLEFT: eResult = GPOS_LB; break;
//STRIP001      case WALLPAPER_BOTTOM: eResult = GPOS_MB; break;
//STRIP001      case WALLPAPER_BOTTOMRIGHT: eResult = GPOS_RB; break;
//STRIP001      default: eResult = GPOS_NONE;
//STRIP001  }
//STRIP001  return eResult;
//STRIP001 };

//static
//STRIP001 WallpaperStyle SvxBrushItem::GraphicPos2WallpaperStyle( SvxGraphicPosition ePos )
//STRIP001 {
//STRIP001  WallpaperStyle eResult;
//STRIP001  switch( ePos )
//STRIP001  {
//STRIP001      case GPOS_NONE: eResult = WALLPAPER_NULL; break;
//STRIP001      case GPOS_TILED: eResult = WALLPAPER_TILE; break;
//STRIP001      case GPOS_MM: eResult = WALLPAPER_CENTER; break;
//STRIP001      case GPOS_AREA: eResult = WALLPAPER_SCALE; break;
//STRIP001      case GPOS_LT: eResult = WALLPAPER_TOPLEFT; break;
//STRIP001      case GPOS_MT: eResult = WALLPAPER_TOP; break;
//STRIP001      case GPOS_RT: eResult = WALLPAPER_TOPRIGHT; break;
//STRIP001      case GPOS_LM: eResult = WALLPAPER_LEFT; break;
//STRIP001      case GPOS_RM: eResult = WALLPAPER_RIGHT; break;
//STRIP001      case GPOS_LB: eResult = WALLPAPER_BOTTOMLEFT; break;
//STRIP001      case GPOS_MB: eResult = WALLPAPER_BOTTOM; break;
//STRIP001      case GPOS_RB: eResult = WALLPAPER_BOTTOMRIGHT; break;
//STRIP001      default: eResult = WALLPAPER_NULL;
//STRIP001  }
//STRIP001  return eResult;
//STRIP001 }


/*N*/ SvxBrushItem::SvxBrushItem( const CntWallpaperItem& rItem, sal_uInt16 nWhich ) :
/*N*/   SfxPoolItem( nWhich ),
/*N*/   pImpl( new SvxBrushItem_Impl( 0 ) ),
/*N*/   bLoadAgain( sal_True ),
/*N*/   pStrLink(0),
/*N*/   pStrFilter(0)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  aColor = rItem.GetColor();
//STRIP001
//STRIP001  if( rItem.GetBitmapURL().Len() )
//STRIP001  {
//STRIP001      pStrLink    = new String( rItem.GetBitmapURL() );
//STRIP001      SetGraphicPos( WallpaperStyle2GraphicPos((WallpaperStyle)rItem.GetStyle() ) );
//STRIP001  }
/*N*/ }

//STRIP001 CntWallpaperItem* SvxBrushItem::CreateCntWallpaperItem() const
//STRIP001 {
//STRIP001  CntWallpaperItem* pItem = new CntWallpaperItem( 0 );
//STRIP001  pItem->SetColor( aColor.GetColor() );
//STRIP001  pItem->SetStyle( GraphicPos2WallpaperStyle( GetGraphicPos() ) );
//STRIP001  sal_Bool bLink = (pStrLink != 0);
//STRIP001  if( bLink )
//STRIP001  {
//STRIP001      String aURL = *pStrLink;
//STRIP001      pItem->SetBitmapURL( aURL );
//STRIP001  }
//STRIP001  if( pImpl->pGraphicObject )
//STRIP001      DBG_ERRORFILE( "Don't know what to do with a graphic" );
//STRIP001 //       pItem->SetGraphic( *pImpl->pGraphic, bLink );
//STRIP001
//STRIP001  return pItem;
//STRIP001 }

#ifdef WNT
#pragma optimize ( "", on )
#endif
/* -----------------------------16.08.2002 09:18------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void  SvxBrushItem::ApplyGraphicTransparency_Impl()
/*N*/ {
/*N*/     DBG_ASSERT(pImpl->pGraphicObject, "no GraphicObject available" )
/*N*/     if(pImpl->pGraphicObject)
/*N*/     {
/*N*/         GraphicAttr aAttr(pImpl->pGraphicObject->GetAttr());
/*N*/         aAttr.SetTransparency(lcl_PercentToTransparency(
/*N*/                             pImpl->nGraphicTransparency));
/*N*/         pImpl->pGraphicObject->SetAttr(aAttr);
/*N*/     }
/*N*/ }
// class SvxFrameDirectionItem ----------------------------------------------

/*N*/ SvxFrameDirectionItem::SvxFrameDirectionItem( SvxFrameDirection nValue ,
/*N*/                                           USHORT nWhich )
/*N*/   : SfxUInt16Item( nWhich, nValue )
/*N*/ {
/*N*/ }

/*N*/ SvxFrameDirectionItem::~SvxFrameDirectionItem()
/*N*/ {
/*N*/ }

/*N*/ int SvxFrameDirectionItem::operator==( const SfxPoolItem& rCmp ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rCmp), "unequal types" );
/*N*/
/*N*/   return GetValue() == ((SvxFrameDirectionItem&)rCmp).GetValue();
/*N*/ }

/*N*/ SfxPoolItem* SvxFrameDirectionItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxFrameDirectionItem( *this );
/*N*/ }

//STRIP001 SfxPoolItem* SvxFrameDirectionItem::Create( SvStream & rStrm, USHORT nVer ) const
//STRIP001 {
//STRIP001  sal_uInt16 nValue;
//STRIP001  rStrm >> nValue;
//STRIP001  return new SvxFrameDirectionItem( (SvxFrameDirection)nValue, Which() );
//STRIP001 }

/*N*/ SvStream& SvxFrameDirectionItem::Store( SvStream & rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/   sal_uInt16 nValue = GetValue();
/*N*/   rStrm << nValue;
/*N*/   return rStrm;
/*N*/ }

/*N*/ USHORT SvxFrameDirectionItem::GetVersion( USHORT nFVer ) const
/*N*/ {
/*N*/   return SOFFICE_FILEFORMAT_50 > nFVer ? USHRT_MAX : 0;
/*N*/ }

//STRIP001 SfxItemPresentation SvxFrameDirectionItem::GetPresentation(
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit eCoreMetric,
//STRIP001  SfxMapUnit ePresMetric,
//STRIP001  String &rText,
//STRIP001     const IntlWrapper* pIntl ) const
//STRIP001 {
//STRIP001  SfxItemPresentation eRet = ePres;
//STRIP001     switch( ePres )
//STRIP001     {
//STRIP001     case SFX_ITEM_PRESENTATION_NONE:
//STRIP001         rText.Erase();
//STRIP001      break;
//STRIP001
//STRIP001     case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001     case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      rText = SVX_RESSTR( RID_SVXITEMS_FRMDIR_BEGIN + GetValue() );
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      eRet = SFX_ITEM_PRESENTATION_NONE;
//STRIP001     }
//STRIP001     return eRet;
//STRIP001 }

/*N*/ sal_Bool SvxFrameDirectionItem::PutValue( const com::sun::star::uno::Any& rVal,
/*N*/                                           BYTE )
/*N*/ {
/*N*/     sal_Int16 nVal;
/*N*/     sal_Bool bRet = ( rVal >>= nVal );
/*N*/     if( bRet )
/*N*/     {
/*N*/         // translate WritingDirection2 constants into SvxFrameDirection
/*N*/         switch( nVal )
/*N*/         {
/*N*/             case text::WritingMode2::LR_TB:
/*N*/                 SetValue( FRMDIR_HORI_LEFT_TOP );
/*N*/                 break;
/*N*/             case text::WritingMode2::RL_TB:
/*?*/                 SetValue( FRMDIR_HORI_RIGHT_TOP );
/*?*/                 break;
/*?*/             case text::WritingMode2::TB_RL:
/*?*/                 SetValue( FRMDIR_VERT_TOP_RIGHT );
/*?*/                 break;
/*?*/             case text::WritingMode2::TB_LR:
/*?*/                 SetValue( FRMDIR_VERT_TOP_LEFT );
/*?*/                 break;
/*?*/             case text::WritingMode2::PAGE:
/*?*/                 SetValue( FRMDIR_ENVIRONMENT );
/*?*/                 break;
/*?*/             default:
/*?*/                 bRet = sal_False;
/*N*/                 break;
/*N*/         }
/*N*/     }
/*N*/
/*N*/   return bRet;
/*N*/ }

/*N*/ sal_Bool SvxFrameDirectionItem::QueryValue( com::sun::star::uno::Any& rVal,
/*N*/                                           BYTE ) const
/*N*/ {
/*N*/     // translate SvxFrameDirection into WritingDirection2
/*N*/     sal_Int16 nVal;
/*N*/     sal_Bool bRet = sal_True;
/*N*/     switch( GetValue() )
/*N*/     {
/*N*/         case FRMDIR_HORI_LEFT_TOP:
/*N*/             nVal = text::WritingMode2::LR_TB;
/*N*/             break;
/*?*/         case FRMDIR_HORI_RIGHT_TOP:
/*?*/             nVal = text::WritingMode2::RL_TB;
/*?*/             break;
/*?*/         case FRMDIR_VERT_TOP_RIGHT:
/*?*/             nVal = text::WritingMode2::TB_RL;
/*?*/             break;
/*?*/         case FRMDIR_VERT_TOP_LEFT:
/*?*/             nVal = text::WritingMode2::TB_LR;
/*?*/             break;
/*?*/         case FRMDIR_ENVIRONMENT:
/*?*/             nVal = text::WritingMode2::PAGE;
/*?*/             break;
/*?*/         default:
/*?*/             DBG_ERROR("Unknown SvxFrameDirection value!");
/*?*/             bRet = sal_False;
/*?*/             break;
/*N*/     }
/*N*/
/*N*/     // return value + error state
/*N*/     if( bRet )
/*N*/     {
/*N*/         rVal <<= nVal;
/*N*/     }
/*N*/   return bRet;
/*N*/ }

