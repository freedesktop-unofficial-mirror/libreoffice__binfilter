/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_shell.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:04:32 $
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

#include <bf_svtools/itempool.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "app.hxx"

namespace binfilter {

//====================================================================

/*N*/ TYPEINIT0(SfxShell);

//====================================================================
/*N*/ SV_IMPL_PTRARR( SfxItemPtrArray, SfxPoolItemPtr);

/*N*/ struct SfxShell_Impl: public SfxBroadcaster
/*N*/ {
/*N*/   String                      aObjectName;// Name des Sbx-Objects
/*N*/   SfxItemArray_Impl           aItems;     // Datenaustausch auf Item-Basis
/*N*/ };

/*N*/ SfxShell::SfxShell()
/*N*/ :   pPool(0),
/*N*/   pImp(0)
/*N*/ {
/*N*/   pImp = new SfxShell_Impl;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxShell::~SfxShell()
/*N*/ {
/*N*/         delete pImp;
/*N*/ }
//--------------------------------------------------------------------

/*N*/ const SfxPoolItem* SfxShell::GetItem
/*N*/ (
/*N*/   USHORT  nSlotId         // Slot-Id des zu erfragenden <SfxPoolItem>s
/*N*/ )   const
/*N*/ {
/*N*/   for ( USHORT nPos = 0; nPos < pImp->aItems.Count(); ++nPos )
/*N*/       if ( pImp->aItems.GetObject(nPos)->Which() == nSlotId )
/*N*/           return pImp->aItems.GetObject(nPos);
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::RemoveItem
/*N*/ (
/*N*/   USHORT  nSlotId         // Slot-Id des zu l"oschenden <SfxPoolItem>s
/*N*/ )
/*N*/ {
/*N*/   for ( USHORT nPos = 0; nPos < pImp->aItems.Count(); ++nPos )
/*?*/       if ( pImp->aItems.GetObject(nPos)->Which() == nSlotId )
/*?*/       {
/*?*/           // Item entfernen und l"oschen
/*?*/           SfxPoolItem *pItem = pImp->aItems.GetObject(nPos);
/*?*/           delete pItem;
/*?*/           pImp->aItems.Remove(nPos);
/*?*/
/*N*/       }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::PutItem
/*N*/ (
/*N*/   const SfxPoolItem&  rItem   /*  Instanz, von der eine Kopie erstellt wird,
                                    die in der SfxShell in einer Liste
                                    gespeichert wird. */
/*N*/ )
/*N*/ {
/*N*/   DBG_ASSERT( !rItem.ISA(SfxSetItem), "SetItems aren't allowed here" );
/*N*/   DBG_ASSERT( SfxItemPool::IsSlot( rItem.Which() ),
/*N*/               "items with Which-Ids aren't allowed here" );
/*N*/
/*N*/   // MSC auf WNT/W95 machte hier Mist, Vorsicht bei Umstellungen
/*N*/   const SfxPoolItem *pItem = rItem.Clone();
/*N*/   SfxPoolItemHint aItemHint( (SfxPoolItem*) pItem );
/*N*/   const USHORT nWhich = rItem.Which();
/*N*/   SfxPoolItem **ppLoopItem = (SfxPoolItem**) pImp->aItems.GetData();
/*N*/   USHORT nPos;
/*N*/   for ( nPos = 0; nPos < pImp->aItems.Count(); ++nPos, ++ppLoopItem )
/*N*/   {
/*N*/       if ( (*ppLoopItem)->Which() == nWhich )
/*N*/       {
/*N*/           // Item austauschen
/*N*/           delete *ppLoopItem;
/*N*/           pImp->aItems.Remove(nPos);
/*N*/           pImp->aItems.Insert( (SfxPoolItemPtr) pItem, nPos );
/*N*/
/*N*/           return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   Broadcast( aItemHint );
/*N*/   pImp->aItems.Insert((SfxPoolItemPtr)pItem, nPos );
/*N*/ }
}
