/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_objitem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 03:14:53 $
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
