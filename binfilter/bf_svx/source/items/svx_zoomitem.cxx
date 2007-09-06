/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_zoomitem.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:44:25 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

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


// -----------------------------------------------------------------------


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


}
