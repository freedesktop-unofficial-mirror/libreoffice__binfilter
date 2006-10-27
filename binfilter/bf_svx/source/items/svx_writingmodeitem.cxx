/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_writingmodeitem.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:19:28 $
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

// include ---------------------------------------------------------------


#ifndef _XDEF_HXX
#include <bf_svx/xdef.hxx>
#endif

#ifndef _SVX_WRITINGMODEITEM_HXX
#include "writingmodeitem.hxx"
#endif


#ifndef _SVXITEMS_HRC
#include "svxitems.hrc"
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;

// class SvxWritingModeItem -------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxWritingModeItem, SfxUInt16Item);

/*N*/ SvxWritingModeItem::SvxWritingModeItem( WritingMode eValue, USHORT nWhich )
/*N*/   : SfxUInt16Item( nWhich, (sal_uInt16)eValue )
/*N*/ {
/*N*/ }

/*N*/ SvxWritingModeItem::~SvxWritingModeItem()
/*N*/ {
/*N*/ }

/*N*/ int SvxWritingModeItem::operator==( const SfxPoolItem& rCmp ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rCmp), "unequal types" );
/*N*/
/*N*/   return GetValue() == ((SvxWritingModeItem&)rCmp).GetValue();
/*N*/ }

/*N*/ SfxPoolItem* SvxWritingModeItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxWritingModeItem( *this );
/*N*/ }



/*N*/ USHORT SvxWritingModeItem::GetVersion( USHORT nFVer ) const
/*N*/ {
/*N*/   return USHRT_MAX;
/*N*/ }



/*N*/ sal_Bool SvxWritingModeItem::QueryValue( ::com::sun::star::uno::Any& rVal,
/*N*/                                           BYTE ) const
/*N*/ {
/*N*/   rVal <<= (WritingMode)GetValue();
/*N*/   return true;
/*N*/ }

/*N*/ SvxWritingModeItem& SvxWritingModeItem::operator=( const SvxWritingModeItem& rItem )
/*N*/ {
/*N*/   SetValue( rItem.GetValue() );
/*N*/   return *this;
/*N*/ }
}
