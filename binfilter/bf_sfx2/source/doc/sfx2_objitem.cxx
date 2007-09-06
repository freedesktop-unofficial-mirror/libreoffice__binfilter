/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_objitem.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:30:22 $
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

#include "objsh.hxx"
//#include "objshimp.hxx"
#include "objitem.hxx"
namespace binfilter {

//====================================================================

/*N*/ TYPEINIT1(SfxObjectShellItem,SfxPoolItem)
/*N*/ TYPEINIT1_AUTOFACTORY(SfxObjectItem,SfxPoolItem)

//=========================================================================

/*N*/ int SfxObjectShellItem::operator==( const SfxPoolItem &rItem ) const
/*N*/ {
/*N*/    return PTR_CAST(SfxObjectShellItem, &rItem)->pObjSh == pObjSh;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ String SfxObjectShellItem::GetValueText() const
/*N*/ {
/*N*/   return String();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPoolItem* SfxObjectShellItem::Clone( SfxItemPool *) const
/*N*/ {
/*N*/   return new SfxObjectShellItem( Which(), pObjSh );
/*N*/ }

//=========================================================================

/*N*/ SfxObjectItem::SfxObjectItem( USHORT nWhich, SfxShell *pSh )
/*N*/ : SfxPoolItem( nWhich ),
/*N*/     _pSh( pSh )
/*N*/ {}

//--------------------------------------------------------------------

/*N*/ int SfxObjectItem::operator==( const SfxPoolItem &rItem ) const
/*N*/ {
/*N*/    SfxObjectItem *pOther = PTR_CAST(SfxObjectItem, &rItem);
/*N*/      return pOther->_pSh == _pSh;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPoolItem* SfxObjectItem::Clone( SfxItemPool *) const
/*N*/ {
/*N*/     return new SfxObjectItem( Which(), _pSh );
/*N*/ }


}
