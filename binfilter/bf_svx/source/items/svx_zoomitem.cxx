/*************************************************************************
 *
 *  $RCSfile: svx_zoomitem.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:03 $
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

#ifndef _ARGS_HXX //autogen
#include <svtools/args.hxx>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifndef __SBX_SBXVARIABLE_HXX
#include <svtools/sbxvar.hxx>
#endif
#pragma hdrstop

#include "zoomitem.hxx"

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

//STRIP001 sal_Bool SvxZoomItem::QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
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

//STRIP001 sal_Bool SvxZoomItem::PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId )
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
