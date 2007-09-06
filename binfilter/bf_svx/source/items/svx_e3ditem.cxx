/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_e3ditem.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:41:56 $
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

#ifndef _COM_SUN_STAR_DRAWING_DIRECTION3D_HPP_
#include <com/sun/star/drawing/Direction3D.hpp>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "e3ditem.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

/*N*/ DBG_NAME(SvxVector3DItem)

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxVector3DItem, SfxPoolItem);

// -----------------------------------------------------------------------

/*?*/ SvxVector3DItem::SvxVector3DItem()
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/   DBG_CTOR(SvxVector3DItem, 0);
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxVector3DItem::SvxVector3DItem( USHORT nWhich, const Vector3D& rVal ) :
/*N*/   SfxPoolItem( nWhich ),
/*N*/   aVal( rVal )
/*N*/ {
/*N*/   DBG_CTOR(SvxVector3DItem, 0);
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ SvxVector3DItem::SvxVector3DItem( const SvxVector3DItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   aVal( rItem.aVal )
/*N*/ {
/*N*/   DBG_CTOR(SvxVector3DItem, 0);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxVector3DItem::operator==( const SfxPoolItem &rItem ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*N*/   return ((SvxVector3DItem&)rItem).aVal == aVal;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxVector3DItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/   return new SvxVector3DItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxVector3DItem::Create(SvStream &rStream, USHORT nVersion) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/   Vector3D aStr;
/*N*/   rStream >> aStr;
/*N*/   return new SvxVector3DItem(Which(), aStr);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxVector3DItem::Store(SvStream &rStream, USHORT nItemVersion) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/
/*N*/   // ## if (nItemVersion)
/*N*/   rStream << aVal;
/*N*/
/*N*/   return rStream;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxVector3DItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   drawing::Direction3D aDirection;
/*N*/
/*N*/   // Werte eintragen
/*N*/   aDirection.DirectionX = aVal.X();
/*N*/   aDirection.DirectionY = aVal.Y();
/*N*/   aDirection.DirectionZ = aVal.Z();
/*N*/
/*N*/   rVal <<= aDirection;
/*N*/   return( sal_True );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxVector3DItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::Direction3D aDirection;
/*N*/   if(!(rVal >>= aDirection))
/*N*/       return sal_False;
/*N*/
/*N*/   aVal.X() = aDirection.DirectionX;
/*N*/   aVal.Y() = aDirection.DirectionY;
/*N*/   aVal.Z() = aDirection.DirectionZ;
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT SvxVector3DItem::GetVersion (USHORT nFileFormatVersion) const
/*N*/ {
/*N*/   return (nFileFormatVersion == SOFFICE_FILEFORMAT_31) ? USHRT_MAX : 0;
/*N*/ }


}
