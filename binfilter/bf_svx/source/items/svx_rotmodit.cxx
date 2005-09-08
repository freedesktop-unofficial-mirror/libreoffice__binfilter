/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_rotmodit.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:19:28 $
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

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#pragma hdrstop

// auto strip #ifndef _COM_SUN_STAR_TABLE_BORDERLINE_HPP_
// auto strip #include <com/sun/star/table/BorderLine.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_TABLE_CELLVERTJUSTIFY_HPP_
#include <com/sun/star/table/CellVertJustify.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_SHADOWLOCATION_HPP_
// auto strip #include <com/sun/star/table/ShadowLocation.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_TABLEBORDER_HPP_
// auto strip #include <com/sun/star/table/TableBorder.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_SHADOWFORMAT_HPP_
// auto strip #include <com/sun/star/table/ShadowFormat.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_CELLRANGEADDRESS_HPP_
// auto strip #include <com/sun/star/table/CellRangeAddress.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_CELLCONTENTTYPE_HPP_
// auto strip #include <com/sun/star/table/CellContentType.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_TABLEORIENTATION_HPP_
// auto strip #include <com/sun/star/table/TableOrientation.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_CELLHORIJUSTIFY_HPP_
// auto strip #include <com/sun/star/table/CellHoriJustify.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UTIL_SORTFIELD_HPP_
// auto strip #include <com/sun/star/util/SortField.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UTIL_SORTFIELDTYPE_HPP_
// auto strip #include <com/sun/star/util/SortFieldType.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_CELLORIENTATION_HPP_
// auto strip #include <com/sun/star/table/CellOrientation.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TABLE_CELLADDRESS_HPP_
// auto strip #include <com/sun/star/table/CellAddress.hpp>
// auto strip #endif

#include "rotmodit.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxRotateModeItem,        SfxEnumItem);


//-----------------------------------------------------------------------
//  SvxRotateModeItem - Ausrichtung bei gedrehtem Text
//-----------------------------------------------------------------------

/*N*/ SvxRotateModeItem::SvxRotateModeItem( SvxRotateMode eMode, USHORT nWhich )
/*N*/   : SfxEnumItem( nWhich, eMode )
/*N*/ {
/*N*/ }

/*N*/ SvxRotateModeItem::SvxRotateModeItem( const SvxRotateModeItem& rItem )
/*N*/   : SfxEnumItem( rItem )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT SvxRotateModeItem::~SvxRotateModeItem()
/*N*/ {
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SvxRotateModeItem::Create( SvStream& rStream, USHORT ) const
/*N*/ {
/*N*/   USHORT nVal;
/*N*/   rStream >> nVal;
/*N*/   return new SvxRotateModeItem( (SvxRotateMode) nVal,Which() );
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SvxRotateModeItem::GetPresentation(
//STRIP001                              SfxItemPresentation ePres,
//STRIP001                              SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001                                 String& rText, const IntlWrapper * )  const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText.AppendAscii("...");
//STRIP001          rText.AppendAscii(": ");
//STRIP001 //           break; // DURCHFALLEN!!!
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          rText += UniString::CreateFromInt32( GetValue() );
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 String __EXPORT SvxRotateModeItem::GetValueText( USHORT nVal ) const
//STRIP001 {
//STRIP001  String aText;
//STRIP001
//STRIP001  switch ( nVal )
//STRIP001  {
//STRIP001      case SVX_ROTATE_MODE_STANDARD:
//STRIP001      case SVX_ROTATE_MODE_TOP:
//STRIP001      case SVX_ROTATE_MODE_CENTER:
//STRIP001      case SVX_ROTATE_MODE_BOTTOM:
//STRIP001          aText.AppendAscii("...");
//STRIP001          break;
//STRIP001      default:
//STRIP001          DBG_ERROR("SvxRotateModeItem: falscher enum");
//STRIP001          break;
//STRIP001  }
//STRIP001  return aText;
//STRIP001 }

/*?*/ USHORT __EXPORT SvxRotateModeItem::GetValueCount() const
/*?*/ {
/*?*/   return 4;       // STANDARD, TOP, CENTER, BOTTOM
/*?*/ }

/*N*/ SfxPoolItem* __EXPORT SvxRotateModeItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxRotateModeItem( *this );
/*N*/ }

/*N*/ USHORT __EXPORT SvxRotateModeItem::GetVersion( USHORT nFileVersion ) const
/*N*/ {
/*N*/   return 0;
/*N*/ }

//  QueryValue/PutValue: Der ::com::sun::star::table::CellVertJustify enum wird mitbenutzt...

/*N*/ sal_Bool SvxRotateModeItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   table::CellVertJustify eUno = table::CellVertJustify_STANDARD;
/*N*/   switch ( (SvxRotateMode)GetValue() )
/*N*/   {
/*N*/       case SVX_ROTATE_MODE_STANDARD: eUno = table::CellVertJustify_STANDARD; break;
/*N*/       case SVX_ROTATE_MODE_TOP:      eUno = table::CellVertJustify_TOP;       break;
/*N*/       case SVX_ROTATE_MODE_CENTER:   eUno = table::CellVertJustify_CENTER;    break;
/*N*/       case SVX_ROTATE_MODE_BOTTOM:   eUno = table::CellVertJustify_BOTTOM;    break;
/*N*/   }
/*N*/   rVal <<= eUno;
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SvxRotateModeItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   table::CellVertJustify eUno;
/*N*/   if(!(rVal >>= eUno))
/*N*/   {
/*N*/       sal_Int32 nValue;
/*?*/       if(!(rVal >>= nValue))
/*?*/           return sal_False;
/*?*/       eUno = (table::CellVertJustify)nValue;
/*N*/   }
/*N*/
/*N*/   SvxRotateMode eSvx = SVX_ROTATE_MODE_STANDARD;
/*N*/   switch (eUno)
/*N*/   {
/*N*/       case table::CellVertJustify_STANDARD: eSvx = SVX_ROTATE_MODE_STANDARD; break;
/*?*/       case table::CellVertJustify_TOP:       eSvx = SVX_ROTATE_MODE_TOP;      break;
/*?*/       case table::CellVertJustify_CENTER:   eSvx = SVX_ROTATE_MODE_CENTER;    break;
/*N*/       case table::CellVertJustify_BOTTOM:   eSvx = SVX_ROTATE_MODE_BOTTOM;    break;
/*N*/   }
/*N*/   SetValue( eSvx );
/*N*/   return sal_True;
/*N*/ }



}
