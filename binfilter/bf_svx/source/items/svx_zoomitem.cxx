/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_zoomitem.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:22:34 $
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

// auto strip #ifndef _ARGS_HXX //autogen
// auto strip #include <svtools/args.hxx>
// auto strip #endif
// auto strip #ifndef _STREAM_HXX
// auto strip #include <tools/stream.hxx>
// auto strip #endif
// auto strip #ifndef __SBX_SBXVARIABLE_HXX
// auto strip #include <svtools/sbxvar.hxx>
// auto strip #endif
#pragma hdrstop

#include "zoomitem.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxZoomItem,SfxUInt16Item);

// -----------------------------------------------------------------------

/*N*/ SvxZoomItem::SvxZoomItem
/*N*/ (
/*N*/   SvxZoomType eZoomType,
/*N*/   sal_uInt16      nVal,
/*N*/   sal_uInt16      nWhich
/*N*/ )
/*N*/ : SfxUInt16Item( nWhich, nVal ),
/*N*/   nValueSet( SVX_ZOOM_ENABLE_ALL ),
/*N*/   eType( eZoomType )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxZoomItem::SvxZoomItem( const SvxZoomItem& rOrig )
/*N*/ : SfxUInt16Item( rOrig.Which(), rOrig.GetValue() ),
/*N*/   nValueSet( rOrig.GetValueSet() ),
/*N*/   eType( rOrig.GetType() )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxZoomItem::~SvxZoomItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxZoomItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SvxZoomItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxZoomItem::Create( SvStream& rStrm, sal_uInt16 nVersion ) const
//STRIP001 {
//STRIP001  sal_uInt16 nValue;
//STRIP001  sal_uInt16 nValSet;
//STRIP001  sal_Int8 nType;
//STRIP001  rStrm >> nValue >> nValSet >> nType;
//STRIP001  SvxZoomItem* pNew = new SvxZoomItem( (SvxZoomType)nType, nValue, Which() );
//STRIP001  pNew->SetValueSet( nValSet );
//STRIP001  return pNew;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvStream& SvxZoomItem::Store( SvStream& rStrm, sal_uInt16 nItemVersion ) const
//STRIP001 {
//STRIP001  rStrm << (sal_uInt16)GetValue()
//STRIP001        << nValueSet
//STRIP001        << (sal_Int8)eType;
//STRIP001  return rStrm;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ int SvxZoomItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   SvxZoomItem& rItem = (SvxZoomItem&)rAttr;
/*N*/
/*N*/   return ( GetValue() == rItem.GetValue()     &&
/*N*/            nValueSet  == rItem.GetValueSet()  &&
/*N*/            eType      == rItem.GetType()          );
/*N*/ }

//STRIP001 sal_Bool SvxZoomItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001     switch ( nMemberId )
//STRIP001     {
//STRIP001         case 0 :
//STRIP001         case MID_VALUE: rVal <<= (sal_Int32) GetValue(); break;
//STRIP001         case MID_VALUESET: rVal <<= (sal_Int16) nValueSet; break;
//STRIP001         case MID_TYPE: rVal <<= (sal_Int16) eType; break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001     }
//STRIP001
//STRIP001     return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SvxZoomItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001     sal_Int32 nVal;
//STRIP001     if ( rVal >>= nVal )
//STRIP001     {
//STRIP001         switch ( nMemberId )
//STRIP001         {
//STRIP001             case MID_VALUE: SetValue( nVal ); break;
//STRIP001             case MID_VALUESET: nValueSet = (sal_Int16) nVal; break;
//STRIP001             case MID_TYPE: eType = SvxZoomType( (sal_Int16) nVal ); break;
//STRIP001             default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return sal_True;
//STRIP001 }
}
