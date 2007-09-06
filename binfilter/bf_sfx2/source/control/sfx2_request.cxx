/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_request.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:27:44 $
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

#include <svtools/itempool.hxx>
#include <svtools/itemset.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "request.hxx"

namespace binfilter {

/*N*/ const SfxPoolItem* SfxRequest::GetItem
/*N*/ (
/*N*/   const SfxItemSet* pArgs,
/*N*/   USHORT          nSlotId,    // Slot-Id oder Which-Id des Parameters
/*N*/   FASTBOOL        bDeep,      // FALSE: nicht in Parent-ItemSets suchen
/*N*/   TypeId          aType       // != 0:  RTTI Pruefung mit Assertion
/*N*/ )
/*N*/ {
/*N*/   if ( pArgs )
/*N*/   {
/*N*/       // ggf. in Which-Id umrechnen
/*N*/       USHORT nWhich = pArgs->GetPool()->GetWhich(nSlotId);
/*N*/
/*N*/       // ist das Item gesetzt oder bei bDeep==TRUE verf"ugbar?
/*N*/       const SfxPoolItem *pItem = 0;
/*N*/       if ( ( bDeep ? SFX_ITEM_AVAILABLE : SFX_ITEM_SET )
/*N*/            <= pArgs->GetItemState( nWhich, bDeep, &pItem ) )
/*N*/       {
/*N*/           // stimmt der Typ "uberein?
/*N*/           if ( !pItem || pItem->IsA(aType) )
/*N*/               return pItem;
/*N*/
/*N*/           // Item da aber falsch => Programmierfehler
/*N*/           DBG_ERROR(  "invalid argument type" );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // keine Parameter, nicht gefunden oder falschen Typ gefunden
/*N*/   return 0;
/*N*/ }
}