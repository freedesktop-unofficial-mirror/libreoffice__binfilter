/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_rotmodit.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:43:36 $
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
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _COM_SUN_STAR_TABLE_CELLVERTJUSTIFY_HPP_
#include <com/sun/star/table/CellVertJustify.hpp>
#endif

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
