/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdattr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 23:23:28 $
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

#pragma hdrstop

#include "sdattr.hxx"
namespace binfilter {

using namespace ::com::sun::star;

/*************************************************************************
|*
|*  DiaEffectItem
|*
*************************************************************************/
/*N*/ TYPEINIT1( DiaEffectItem, SfxEnumItem );


//STRIP001 DiaEffectItem::DiaEffectItem( presentation::FadeEffect eFE ) :
//STRIP001  SfxEnumItem( ATTR_DIA_EFFECT, eFE )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 DiaEffectItem::DiaEffectItem( SvStream& rIn ) :
//STRIP001  SfxEnumItem( ATTR_DIA_EFFECT, rIn )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaEffectItem::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001  return new DiaEffectItem( *this );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaEffectItem::Create( SvStream& rIn, USHORT nVer ) const
//STRIP001 {
//STRIP001  return new DiaEffectItem( rIn );
//STRIP001 }

/*************************************************************************
|*
|*  DiaSpeedItem
|*
*************************************************************************/
/*N*/ TYPEINIT1( DiaSpeedItem, SfxEnumItem );


//STRIP001 DiaSpeedItem::DiaSpeedItem( FadeSpeed eFS ) :
//STRIP001  SfxEnumItem( ATTR_DIA_SPEED, eFS )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 DiaSpeedItem::DiaSpeedItem( SvStream& rIn ) :
//STRIP001  SfxEnumItem( ATTR_DIA_SPEED, rIn )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaSpeedItem::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001  return new DiaSpeedItem( *this );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaSpeedItem::Create( SvStream& rIn, USHORT nVer ) const
//STRIP001 {
//STRIP001  return new DiaSpeedItem( rIn );
//STRIP001 }

/*************************************************************************
|*
|*  DiaAutoItem
|*
*************************************************************************/
/*N*/ TYPEINIT1( DiaAutoItem, SfxEnumItem );

//STRIP001 DiaAutoItem::DiaAutoItem( PresChange eChange ) :
//STRIP001  SfxEnumItem( ATTR_DIA_AUTO, eChange )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 DiaAutoItem::DiaAutoItem( SvStream& rIn ) :
//STRIP001  SfxEnumItem( ATTR_DIA_AUTO, rIn )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaAutoItem::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001  return new DiaAutoItem( *this );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaAutoItem::Create( SvStream& rIn, USHORT nVer ) const
//STRIP001 {
//STRIP001  return new DiaAutoItem( rIn );
//STRIP001 }

/*************************************************************************
|*
|*  DiaTimeItem
|*
*************************************************************************/
/*N*/ TYPEINIT1( DiaTimeItem, SfxUInt32Item );


//STRIP001 DiaTimeItem::DiaTimeItem( UINT32 nValue ) :
//STRIP001      SfxUInt32Item( ATTR_DIA_TIME, nValue )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SfxPoolItem* DiaTimeItem::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001  return new DiaTimeItem( *this );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 int DiaTimeItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  return( ( (DiaTimeItem&) rItem ).GetValue() == GetValue() );
//STRIP001 }



}
