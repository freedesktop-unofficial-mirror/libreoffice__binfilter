/*************************************************************************
 *
 *  $RCSfile: sc_bcaslot.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:35:44 $
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

// System - Includes -----------------------------------------------------

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

#include <bf_sfx2/objsh.hxx>
#include <svtools/lstner.hxx>

// INCLUDE ---------------------------------------------------------------

#include "document.hxx"
#include "brdcst.hxx"
#include "bcaslot.hxx"
#include "scerrors.hxx"
#include "docoptio.hxx"
#include "refupdat.hxx"
#include "table.hxx"

// Anzahl der Slots je Dimension
// muessen ganzzahlige Teiler von MAXCOL+1 bzw. MAXROW+1 sein
#define BCA_SLOTS_COL 16
#define BCA_SLOTS_ROW 256
#define BCA_SLOT_COLS ((MAXCOL+1) / BCA_SLOTS_COL)
#define BCA_SLOT_ROWS ((MAXROW+1) / BCA_SLOTS_ROW)
// vielfaches?
#if (BCA_SLOT_COLS * BCA_SLOTS_COL) != (MAXCOL+1)
#error bad BCA_SLOTS_COL value!
#endif
#if (BCA_SLOT_ROWS * BCA_SLOTS_ROW) != (MAXROW+1)
#error bad BCA_SLOTS_ROW value!
#endif
// Groesse des Slot-Arrays
#define BCA_SLOTS (BCA_SLOTS_COL * BCA_SLOTS_ROW)
#if BCA_SLOTS > 16350
#error BCA_SLOTS DOOMed!
#endif

DECLARE_LIST( ScBroadcastAreaList, ScBroadcastArea* );

// STATIC DATA -----------------------------------------------------------

#ifdef erDEBUG
ULONG erCountBCAInserts = 0;
ULONG erCountBCAFinds = 0;
#endif

/*N*/ SV_IMPL_OP_PTRARR_SORT( ScBroadcastAreas, ScBroadcastAreaPtr );
/*N*/ TYPEINIT1( ScHint, SfxSimpleHint );
TYPEINIT1( ScAreaChangedHint, SfxHint );


/*N*/ ScBroadcastAreaSlot::ScBroadcastAreaSlot( ScDocument* pDocument,
/*N*/       ScBroadcastAreaSlotMachine* pBASMa ) :
/*N*/   pDoc( pDocument ),
/*N*/   pBASM( pBASMa )
/*N*/ {
/*N*/   pBroadcastAreaTbl = new ScBroadcastAreas( BCA_INITGROWSIZE, BCA_INITGROWSIZE );
/*N*/   pTmpSeekBroadcastArea = new ScBroadcastArea( ScRange() );
/*N*/ }


/*N*/ ScBroadcastAreaSlot::~ScBroadcastAreaSlot()
/*N*/ {
/*N*/   USHORT nPos = pBroadcastAreaTbl->Count();
/*N*/   if ( nPos )
/*N*/   {
/*N*/       ScBroadcastArea** ppArea =
/*N*/           ((ScBroadcastArea**) pBroadcastAreaTbl->GetData()) + nPos - 1;
/*N*/       for ( ; nPos-- >0; ppArea-- )
/*N*/       {
/*N*/           if ( !(*ppArea)->DecRef() )
/*N*/               delete *ppArea;
/*N*/       }
/*N*/   }
/*N*/   delete pBroadcastAreaTbl;
/*N*/   delete pTmpSeekBroadcastArea;
/*N*/ }


// nur hier werden neue BroadcastAreas angelegt, wodurch keine doppelten entstehen.
// Ist rpArea != NULL werden keine Listener gestartet sondern nur die Area
// eingetragen und der RefCount erhoeht
/*N*/ void ScBroadcastAreaSlot::StartListeningArea( const ScRange& rRange,
/*N*/       SfxListener* pListener, ScBroadcastArea*& rpArea
/*N*/   )
/*N*/ {
/*N*/   DBG_ASSERT(pListener, "StartListeningArea: pListener Null");
/*N*/   if ( pDoc->GetHardRecalcState() )
/*N*/       return;
/*N*/   if ( (long)( (pBroadcastAreaTbl->Count() + 1 + BCA_INITGROWSIZE)
/*N*/           * sizeof(ScBroadcastArea*) ) >= USHRT_MAX
/*N*/       )
/*N*/   {
/*?*/       if ( !pDoc->GetHardRecalcState() )
/*?*/       {
/*?*/           pDoc->SetHardRecalcState( 1 );
/*?*/
/*?*/           SfxObjectShell* pShell = pDoc->GetDocumentShell();
/*?*/           DBG_ASSERT( pShell, "Missing DocShell :-/" );
/*?*/
/*?*/           if ( pShell )
/*?*/               pShell->SetError( SCWARN_CORE_HARD_RECALC );
/*?*/
/*?*/           pDoc->SetAutoCalc( FALSE );
/*?*/           pDoc->SetHardRecalcState( 2 );
/*?*/       }
/*?*/       return;
/*N*/   }
/*N*/   if ( !rpArea )
/*N*/   {
/*N*/       rpArea = new ScBroadcastArea( rRange );
/*N*/       // meistens existiert die Area noch nicht, der Versuch sofort zu inserten
/*N*/       // erspart in diesen Faellen ein doppeltes Seek_Entry
/*N*/       if ( pBroadcastAreaTbl->Insert( rpArea ) )
/*N*/           rpArea->IncRef();
/*N*/       else
/*N*/       {
/*N*/           delete rpArea;
/*N*/           rpArea = GetBroadcastArea( rRange );
/*N*/       }
/*N*/       pListener->StartListening( *rpArea, TRUE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( pBroadcastAreaTbl->Insert( rpArea ) )
/*N*/           rpArea->IncRef();
/*N*/   }
/*N*/ }


/*N*/ // Ist rpArea != NULL werden keine Listener gestopt sondern nur die Area
/*N*/ // ausgetragen und der RefCount vermindert
/*N*/ void ScBroadcastAreaSlot::EndListeningArea( const ScRange& rRange,
/*N*/       SfxListener* pListener, ScBroadcastArea*& rpArea
/*N*/   )
/*N*/ {
/*N*/   DBG_ASSERT(pListener, "EndListeningArea: pListener Null");
/*N*/   if ( !rpArea )
/*N*/   {
/*N*/       USHORT nPos;
/*N*/       if ( (nPos = FindBroadcastArea( rRange )) == USHRT_MAX )
/*N*/           return;
/*N*/       rpArea = (*pBroadcastAreaTbl)[ nPos ];
/*N*/       pListener->EndListening( *rpArea );
/*N*/       if ( !rpArea->HasListeners() )
/*N*/       {   // wenn keiner mehr zuhoert ist die Area ueberfluessig
/*N*/           pBroadcastAreaTbl->Remove( nPos );
/*N*/           if ( !rpArea->DecRef() )
/*N*/           {
/*N*/               delete rpArea;
/*N*/               rpArea = NULL;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( !rpArea->HasListeners() )
/*N*/       {
/*N*/           USHORT nPos;
/*N*/           if ( (nPos = FindBroadcastArea( rRange )) == USHRT_MAX )
/*N*/               return;
/*N*/           pBroadcastAreaTbl->Remove( nPos );
/*N*/           if ( !rpArea->DecRef() )
/*N*/           {
/*N*/               delete rpArea;
/*N*/               rpArea = NULL;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
/*N*/
/*N*/ USHORT ScBroadcastAreaSlot::FindBroadcastArea( const ScRange& rRange ) const
/*N*/ {
/*N*/   USHORT nPos;
/*N*/   pTmpSeekBroadcastArea->UpdateRange( rRange );
/*N*/   if ( pBroadcastAreaTbl->Seek_Entry( pTmpSeekBroadcastArea, &nPos ) )
/*N*/       return nPos;
/*N*/   return USHRT_MAX;
/*N*/ }


/*N*/ ScBroadcastArea* ScBroadcastAreaSlot::GetBroadcastArea(
/*N*/       const ScRange& rRange ) const
/*N*/ {
/*N*/   USHORT nPos;
/*N*/   if ( (nPos = FindBroadcastArea( rRange )) != USHRT_MAX )
/*N*/       return (*pBroadcastAreaTbl)[ nPos ];
/*N*/   return 0;
/*N*/ }


/*N*/ BOOL ScBroadcastAreaSlot::AreaBroadcast( const ScHint& rHint) const
/*N*/ {
/*N*/   USHORT nCount = pBroadcastAreaTbl->Count();
/*N*/   if ( nCount == 0 )
/*N*/       return FALSE;
/*N*/   const ScBroadcastArea** ppArea =
/*N*/       (const ScBroadcastArea**) pBroadcastAreaTbl->GetData();
/*N*/   BOOL bIsBroadcasted = FALSE;
/*N*/   // leider laesst sich nicht nach dem erstmoeglichen suchen
/*N*/   USHORT nPos = 0;
/*N*/   // den letztmoeglichen suchen, Seek_Entry liefert naechst groesseren
/*N*/   // oder freie Position wenn nicht gefunden
/*N*/   USHORT nPosEnd;
/*N*/     const ScAddress& rAddress = rHint.GetAddress();
/*N*/   pTmpSeekBroadcastArea->UpdateRange( ScRange( rAddress,
/*N*/       ScAddress( MAXCOL, MAXROW, MAXTAB ) ) );
/*N*/   if ( !pBroadcastAreaTbl->Seek_Entry( pTmpSeekBroadcastArea, &nPosEnd )
/*N*/     && nPosEnd > 0 )
/*N*/       --nPosEnd;
/*N*/   for ( ; nPos <= nPosEnd; ++nPos, ppArea++ )
/*N*/   {
/*N*/       if ( ((ScBroadcastArea*)*ppArea)->In( rAddress ) )
/*N*/       {
/*N*/           ((ScBroadcastArea*)*ppArea)->Broadcast( rHint );
/*N*/           bIsBroadcasted = TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bIsBroadcasted;
/*N*/ }


//STRIP001 BOOL ScBroadcastAreaSlot::AreaBroadcastInRange( const ScRange& rRange,
//STRIP001         const ScHint& rHint) const
//STRIP001 {
//STRIP001  USHORT nCount = pBroadcastAreaTbl->Count();
//STRIP001  if ( nCount == 0 )
//STRIP001      return FALSE;
//STRIP001  const ScBroadcastArea** ppArea =
//STRIP001      (const ScBroadcastArea**) pBroadcastAreaTbl->GetData();
//STRIP001  BOOL bIsBroadcasted = FALSE;
//STRIP001  // unfortunately we can't search for the first matching entry
//STRIP001  USHORT nPos = 0;
//STRIP001     // search the last matching entry, Seek_Entry returns the next being
//STRIP001     // greater, or a free position if not found
//STRIP001  USHORT nPosEnd;
//STRIP001  pTmpSeekBroadcastArea->UpdateRange( rRange );
//STRIP001     if ( !pBroadcastAreaTbl->Seek_Entry( pTmpSeekBroadcastArea, &nPosEnd ) &&
//STRIP001             nPosEnd > 0 )
//STRIP001         --nPosEnd;
//STRIP001  for ( ; nPos <= nPosEnd; ++nPos, ppArea++ )
//STRIP001  {
//STRIP001      if ( ((ScBroadcastArea*)*ppArea)->Intersects( rRange ) )
//STRIP001      {
//STRIP001          ((ScBroadcastArea*)*ppArea)->Broadcast( rHint );
//STRIP001          bIsBroadcasted = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bIsBroadcasted;
//STRIP001 }


//  DelBroadcastAreasInRange wird unter Windows (16 Bit) kaputtoptimiert

#ifdef WIN
#pragma optimize("",off)
#endif

//STRIP001 void ScBroadcastAreaSlot::DelBroadcastAreasInRange( const ScRange& rRange )
//STRIP001 {
//STRIP001  ScBroadcastArea* pArea;
//STRIP001  ScAddress aStart( rRange.aStart );
//STRIP001  USHORT nPos = pBroadcastAreaTbl->Count();
//STRIP001  const ScBroadcastArea** ppArea =
//STRIP001      (const ScBroadcastArea**) pBroadcastAreaTbl->GetData() + nPos - 1;
//STRIP001  for ( ; nPos-- >0; ppArea-- )
//STRIP001  {   // rueckwaerts wg. Pointer-Aufrueckerei im Array
//STRIP001      pArea = (ScBroadcastArea*)*ppArea;
//STRIP001      if ( pArea->aStart < aStart )
//STRIP001          return;     // davor nur noch niedrigere
//STRIP001          // gesuchte muessen komplett innerhalb von rRange liegen
//STRIP001      if ( rRange.In( pArea->aStart ) && rRange.In( pArea->aEnd ) )
//STRIP001      {
//STRIP001          pBroadcastAreaTbl->Remove( nPos );
//STRIP001          ppArea = (const ScBroadcastArea**) pBroadcastAreaTbl->GetData()
//STRIP001              + nPos;
//STRIP001          if ( !pArea->DecRef() )
//STRIP001              delete pArea;
//STRIP001      }
//STRIP001  }
//STRIP001 }

#ifdef WIN
#pragma optimize("",on)
#endif

//STRIP001 void ScBroadcastAreaSlot::UpdateRemove( UpdateRefMode eUpdateRefMode,
//STRIP001      const ScRange& rRange, short nDx, short nDy, short nDz
//STRIP001  )
//STRIP001 {
//STRIP001  USHORT nPos = pBroadcastAreaTbl->Count();
//STRIP001  if ( nPos )
//STRIP001  {
//STRIP001      USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
//STRIP001      USHORT theCol1, theRow1, theTab1, theCol2, theRow2, theTab2;
//STRIP001      nCol1 = rRange.aStart.Col();
//STRIP001      nRow1 = rRange.aStart.Row();
//STRIP001      nTab1 = rRange.aStart.Tab();
//STRIP001      nCol2 = rRange.aEnd.Col();
//STRIP001      nRow2 = rRange.aEnd.Row();
//STRIP001      nTab2 = rRange.aEnd.Tab();
//STRIP001      ScAddress aAdr;
//STRIP001      const ScBroadcastArea** ppArea =
//STRIP001          ((const ScBroadcastArea**) pBroadcastAreaTbl->GetData()) + nPos - 1;
//STRIP001      for ( ; nPos-- >0; ppArea-- )
//STRIP001      {   // rueckwaerts wg. Pointer-Aufrueckerei im Array
//STRIP001          ScBroadcastArea* pArea = (ScBroadcastArea*) *ppArea;
//STRIP001          if ( pArea->IsInUpdateChain() )
//STRIP001          {
//STRIP001              pBroadcastAreaTbl->Remove( nPos );
//STRIP001              // Remove kann pData veraendern
//STRIP001              ppArea = (const ScBroadcastArea**)
//STRIP001                  pBroadcastAreaTbl->GetData() + nPos;
//STRIP001              pArea->DecRef();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aAdr = pArea->GetStart();
//STRIP001              theCol1 = aAdr.Col();
//STRIP001              theRow1 = aAdr.Row();
//STRIP001              theTab1 = aAdr.Tab();
//STRIP001              aAdr = pArea->GetEnd();
//STRIP001              theCol2 = aAdr.Col();
//STRIP001              theRow2 = aAdr.Row();
//STRIP001              theTab2 = aAdr.Tab();
//STRIP001              if ( ScRefUpdate::Update( pDoc, eUpdateRefMode,
//STRIP001                      nCol1,nRow1,nTab1, nCol2,nRow2,nTab2, nDx,nDy,nDz,
//STRIP001                      theCol1,theRow1,theTab1, theCol2,theRow2,theTab2 )
//STRIP001                  )
//STRIP001              {
//STRIP001                  pBroadcastAreaTbl->Remove( nPos );
//STRIP001                  // Remove kann pData veraendern
//STRIP001                  ppArea = (const ScBroadcastArea**)
//STRIP001                      pBroadcastAreaTbl->GetData() + nPos;
//STRIP001                  pArea->DecRef();
//STRIP001                  pArea->SetInUpdateChain( TRUE );
//STRIP001                  ScBroadcastArea* pUC = pBASM->GetEOUpdateChain();
//STRIP001                  if ( pUC )
//STRIP001                      pUC->SetUpdateChainNext( pArea );
//STRIP001                  else    // kein Ende kein Anfang
//STRIP001                      pBASM->SetUpdateChain( pArea );
//STRIP001                  pBASM->SetEOUpdateChain( pArea );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScBroadcastAreaSlot::UpdateInsert( ScBroadcastArea* pArea )
//STRIP001 {
//STRIP001  if ( pBroadcastAreaTbl->Insert( pArea ) )
//STRIP001      pArea->IncRef();
//STRIP001 }


// --- ScBroadcastAreaSlotMachine -------------------------------------

/*N*/ ScBroadcastAreaSlotMachine::ScBroadcastAreaSlotMachine(
/*N*/       ScDocument* pDocument ) :
/*N*/   pDoc( pDocument ),
/*N*/   pBCAlwaysList( new ScBroadcastAreaList ),
/*N*/   pUpdateChain( NULL ),
/*N*/   pEOUpdateChain( NULL )
/*N*/ {
/*N*/   ppSlots = new ScBroadcastAreaSlot* [ BCA_SLOTS ];
/*N*/   memset( ppSlots, 0 , sizeof( ScBroadcastAreaSlot* ) * BCA_SLOTS );
/*N*/ }


/*N*/ ScBroadcastAreaSlotMachine::~ScBroadcastAreaSlotMachine()
/*N*/ {
/*N*/
/*N*/   ScBroadcastAreaSlot** pp = ppSlots;
/*N*/   for ( USHORT j=0; j < BCA_SLOTS; ++j, ++pp )
/*N*/   {
/*N*/       if ( *pp )
/*N*/           delete *pp;
/*N*/   }
/*N*/   delete[] ppSlots;
/*N*/
/*N*/   for ( ScBroadcastArea* pBCA = pBCAlwaysList->First(); pBCA; pBCA = pBCAlwaysList->Next() )
/*N*/   {
/*N*/       delete pBCA;
/*N*/   }
/*N*/   delete pBCAlwaysList;
/*N*/ }


/*N*/ inline USHORT ScBroadcastAreaSlotMachine::ComputeSlotOffset(
/*N*/       const ScAddress& rAddress ) const
/*N*/ {
/*N*/  USHORT nRow = rAddress.Row();
/*N*/  USHORT nCol = rAddress.Col();
/*N*/  if ( nRow > MAXROW || nCol > MAXCOL )
/*N*/  {
/*N*/   DBG_ASSERT( FALSE, "Row/Col ungueltig!" );
/*N*/   return 0;
/*N*/  }
/*N*/  else
/*N*/   return
/*N*/       nRow / BCA_SLOT_ROWS +
/*N*/       nCol / BCA_SLOT_COLS * BCA_SLOTS_ROW;
/*N*/ }


/*N*/ void ScBroadcastAreaSlotMachine::ComputeAreaPoints( const ScRange& rRange,
/*N*/       USHORT& rStart, USHORT& rEnd, USHORT& rRowBreak
/*N*/   ) const
/*N*/ {
/*N*/   rStart = ComputeSlotOffset( rRange.aStart );
/*N*/   rEnd = ComputeSlotOffset( rRange.aEnd );
/*N*/   // Anzahl Zeilen-Slots pro Spalte minus eins
/*N*/   rRowBreak = ComputeSlotOffset(
/*N*/       ScAddress( rRange.aStart.Col(), rRange.aEnd.Row(), 0 ) ) - rStart;
/*N*/ }


/*N*/ void ScBroadcastAreaSlotMachine::StartListeningArea( const ScRange& rRange,
/*N*/       SfxListener* pListener
/*N*/   )
/*N*/ {
/*N*/   if ( rRange == BCA_LISTEN_ALWAYS  )
/*N*/   {
/*N*/       ScBroadcastArea* pBCA;
/*N*/       if ( !pBCAlwaysList->Count() )
/*N*/       {
/*N*/           pBCA = new ScBroadcastArea( rRange );
/*N*/           pListener->StartListening( *pBCA, FALSE );  // kein PreventDupes
/*N*/           pBCAlwaysList->Insert( pBCA, LIST_APPEND );
/*N*/           return ;
/*N*/       }
/*N*/       ScBroadcastArea* pLast;
/*N*/       for ( pBCA = pBCAlwaysList->First(); pBCA; pBCA = pBCAlwaysList->Next() )
/*N*/       {
/*N*/           if ( pListener->IsListening( *pBCA ) )
/*N*/               return ;        // keine Dupes
/*N*/           pLast = pBCA;
/*N*/       }
/*?*/       pBCA = pLast;
/*?*/       //! ListenerArrays don't shrink!
/*?*/       if ( pBCA->GetListenerCount() > ((USHRT_MAX / 2) / sizeof(SfxBroadcaster*)) )
/*?*/       {   // Arrays nicht zu gross werden lassen
/*?*/           pBCA = new ScBroadcastArea( rRange );
/*?*/           pBCAlwaysList->Insert( pBCA, LIST_APPEND );
/*?*/       }
/*?*/       pListener->StartListening( *pBCA, FALSE );  // kein PreventDupes
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       USHORT nStart, nEnd, nRowBreak;
/*N*/       ComputeAreaPoints( rRange, nStart, nEnd, nRowBreak );
/*N*/       USHORT nOff = nStart;
/*N*/       USHORT nBreak = nOff + nRowBreak;
/*N*/       ScBroadcastAreaSlot** pp = ppSlots + nOff;
/*N*/       ScBroadcastArea* pArea = NULL;
/*N*/       while ( nOff <= nEnd )
/*N*/       {
/*N*/           if ( !*pp )
/*N*/               *pp = new ScBroadcastAreaSlot( pDoc, this );
/*N*/           // der erste erzeugt ggbf. die BroadcastArea
/*N*/           (*pp)->StartListeningArea( rRange, pListener, pArea );
/*N*/           if ( nOff < nBreak )
/*N*/           {
/*N*/               ++nOff;
/*N*/               ++pp;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               nStart += BCA_SLOTS_ROW;
/*N*/               nOff = nStart;
/*N*/               pp = ppSlots + nOff;
/*N*/               nBreak = nOff + nRowBreak;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void ScBroadcastAreaSlotMachine::EndListeningArea( const ScRange& rRange,
/*N*/       SfxListener* pListener
/*N*/   )
/*N*/ {
/*N*/   if ( rRange == BCA_LISTEN_ALWAYS  )
/*N*/   {
/*?*/       if ( pBCAlwaysList->Count() )
/*?*/       {
/*?*/           for ( ScBroadcastArea* pBCA = pBCAlwaysList->First(); pBCA; pBCA = pBCAlwaysList->Next() )
/*?*/           {
/*?*/               // EndListening liefert FALSE wenn !IsListening, keine Dupes
/*?*/               if ( pListener->EndListening( *pBCA, FALSE ) )
/*?*/               {
/*?*/                   if ( !pBCA->HasListeners() )
/*?*/                   {
/*?*/                       pBCAlwaysList->Remove();
/*?*/                       delete pBCA;
/*?*/                   }
/*?*/                   return ;
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       USHORT nStart, nEnd, nRowBreak;
/*N*/       ComputeAreaPoints( rRange, nStart, nEnd, nRowBreak );
/*N*/       USHORT nOff = nStart;
/*N*/       USHORT nBreak = nOff + nRowBreak;
/*N*/       ScBroadcastAreaSlot** pp = ppSlots + nOff;
/*N*/       ScBroadcastArea* pArea = NULL;
/*N*/       while ( nOff <= nEnd )
/*N*/       {
/*N*/           if ( *pp )
/*N*/               (*pp)->EndListeningArea( rRange, pListener, pArea );
/*N*/           if ( nOff < nBreak )
/*N*/           {
/*N*/               ++nOff;
/*N*/               ++pp;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               nStart += BCA_SLOTS_ROW;
/*N*/               nOff = nStart;
/*N*/               pp = ppSlots + nOff;
/*N*/               nBreak = nOff + nRowBreak;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
/*N*/
/*N*/ BOOL ScBroadcastAreaSlotMachine::AreaBroadcast( const ScHint& rHint ) const
/*N*/ {
/*N*/     const ScAddress& rAddress = rHint.GetAddress();
/*N*/   if ( rAddress == BCA_BRDCST_ALWAYS )
/*N*/   {
/*N*/       if ( pBCAlwaysList->Count() )
/*N*/       {
/*N*/           for ( ScBroadcastArea* pBCA = pBCAlwaysList->First(); pBCA; pBCA = pBCAlwaysList->Next() )
/*N*/           {
/*N*/               pBCA->Broadcast( rHint );
/*N*/           }
/*N*/           return TRUE;
/*N*/       }
/*N*/       else
/*N*/           return FALSE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       ScBroadcastAreaSlot* pSlot = ppSlots[ ComputeSlotOffset( rAddress ) ];
/*N*/       if ( pSlot )
/*N*/           return pSlot->AreaBroadcast( rHint );
/*N*/       else
/*N*/           return FALSE;
/*N*/   }
/*N*/ }


//STRIP001 BOOL ScBroadcastAreaSlotMachine::AreaBroadcastInRange( const ScRange& rRange,
//STRIP001         const ScHint& rHint ) const
//STRIP001 {
//STRIP001     BOOL bBroadcasted = FALSE;
//STRIP001  USHORT nStart, nEnd, nRowBreak;
//STRIP001  ComputeAreaPoints( rRange, nStart, nEnd, nRowBreak );
//STRIP001  USHORT nOff = nStart;
//STRIP001  USHORT nBreak = nOff + nRowBreak;
//STRIP001  ScBroadcastAreaSlot** pp = ppSlots + nOff;
//STRIP001  while ( nOff <= nEnd )
//STRIP001  {
//STRIP001      if ( *pp )
//STRIP001          bBroadcasted |= (*pp)->AreaBroadcastInRange( rRange, rHint );
//STRIP001      if ( nOff < nBreak )
//STRIP001      {
//STRIP001          ++nOff;
//STRIP001          ++pp;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nStart += BCA_SLOTS_ROW;
//STRIP001          nOff = nStart;
//STRIP001          pp = ppSlots + nOff;
//STRIP001          nBreak = nOff + nRowBreak;
//STRIP001      }
//STRIP001  }
//STRIP001     return bBroadcasted;
//STRIP001 }


//STRIP001 void ScBroadcastAreaSlotMachine::DelBroadcastAreasInRange(
//STRIP001      const ScRange& rRange
//STRIP001  )
//STRIP001 {
//STRIP001  USHORT nStart, nEnd, nRowBreak;
//STRIP001  ComputeAreaPoints( rRange, nStart, nEnd, nRowBreak );
//STRIP001  USHORT nOff = nStart;
//STRIP001  USHORT nBreak = nOff + nRowBreak;
//STRIP001  ScBroadcastAreaSlot** pp = ppSlots + nOff;
//STRIP001  while ( nOff <= nEnd )
//STRIP001  {
//STRIP001      if ( *pp )
//STRIP001          (*pp)->DelBroadcastAreasInRange( rRange );
//STRIP001      if ( nOff < nBreak )
//STRIP001      {
//STRIP001          ++nOff;
//STRIP001          ++pp;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nStart += BCA_SLOTS_ROW;
//STRIP001          nOff = nStart;
//STRIP001          pp = ppSlots + nOff;
//STRIP001          nBreak = nOff + nRowBreak;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 // alle Betroffenen austragen, verketten, Range anpassen, neu eintragen
//STRIP001 void ScBroadcastAreaSlotMachine::UpdateBroadcastAreas(
//STRIP001      UpdateRefMode eUpdateRefMode,
//STRIP001      const ScRange& rRange, short nDx, short nDy, short nDz
//STRIP001  )
//STRIP001 {
//STRIP001  USHORT nStart, nEnd, nRowBreak;
//STRIP001  // Betroffene austragen und verketten
//STRIP001  ComputeAreaPoints( rRange, nStart, nEnd, nRowBreak );
//STRIP001  USHORT nOff = nStart;
//STRIP001  USHORT nBreak = nOff + nRowBreak;
//STRIP001  ScBroadcastAreaSlot** pp = ppSlots + nOff;
//STRIP001  while ( nOff <= nEnd )
//STRIP001  {
//STRIP001      if ( *pp )
//STRIP001          (*pp)->UpdateRemove( eUpdateRefMode, rRange, nDx, nDy, nDz );
//STRIP001      if ( nOff < nBreak )
//STRIP001      {
//STRIP001          ++nOff;
//STRIP001          ++pp;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nStart += BCA_SLOTS_ROW;
//STRIP001          nOff = nStart;
//STRIP001          pp = ppSlots + nOff;
//STRIP001          nBreak = nOff + nRowBreak;
//STRIP001      }
//STRIP001  }
//STRIP001  // Verkettung abarbeiten
//STRIP001  USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
//STRIP001  USHORT theCol1, theRow1, theTab1, theCol2, theRow2, theTab2;
//STRIP001  nCol1 = rRange.aStart.Col();
//STRIP001  nRow1 = rRange.aStart.Row();
//STRIP001  nTab1 = rRange.aStart.Tab();
//STRIP001  nCol2 = rRange.aEnd.Col();
//STRIP001  nRow2 = rRange.aEnd.Row();
//STRIP001  nTab2 = rRange.aEnd.Tab();
//STRIP001  while ( pUpdateChain )
//STRIP001  {
//STRIP001      ScAddress aAdr;
//STRIP001      ScRange aRange;
//STRIP001      ScBroadcastArea* pArea = pUpdateChain;
//STRIP001      pUpdateChain = pArea->GetUpdateChainNext();
//STRIP001
//STRIP001      // Range anpassen
//STRIP001      aAdr = pArea->GetStart();
//STRIP001      theCol1 = aAdr.Col();
//STRIP001      theRow1 = aAdr.Row();
//STRIP001      theTab1 = aAdr.Tab();
//STRIP001      aAdr = pArea->GetEnd();
//STRIP001      theCol2 = aAdr.Col();
//STRIP001      theRow2 = aAdr.Row();
//STRIP001      theTab2 = aAdr.Tab();
//STRIP001      if ( ScRefUpdate::Update( pDoc, eUpdateRefMode,
//STRIP001              nCol1,nRow1,nTab1, nCol2,nRow2,nTab2, nDx,nDy,nDz,
//STRIP001              theCol1,theRow1,theTab1, theCol2,theRow2,theTab2 )
//STRIP001          )
//STRIP001      {
//STRIP001          aRange = ScRange( ScAddress( theCol1,theRow1,theTab1 ),
//STRIP001                              ScAddress( theCol2,theRow2,theTab2 ) );
//STRIP001          pArea->UpdateRange( aRange );
//STRIP001          pArea->Broadcast( ScAreaChangedHint( aRange ) );    // fuer DDE
//STRIP001      }
//STRIP001
//STRIP001      // in die Slots eintragen
//STRIP001      ComputeAreaPoints( aRange, nStart, nEnd, nRowBreak );
//STRIP001      nOff = nStart;
//STRIP001      nBreak = nOff + nRowBreak;
//STRIP001      pp = ppSlots + nOff;
//STRIP001      while ( nOff <= nEnd )
//STRIP001      {
//STRIP001          if ( *pp )
//STRIP001              (*pp)->UpdateInsert( pArea );
//STRIP001          if ( nOff < nBreak )
//STRIP001          {
//STRIP001              ++nOff;
//STRIP001              ++pp;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nStart += BCA_SLOTS_ROW;
//STRIP001              nOff = nStart;
//STRIP001              pp = ppSlots + nOff;
//STRIP001              nBreak = nOff + nRowBreak;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Verkettung loesen
//STRIP001      pArea->SetUpdateChainNext( NULL );
//STRIP001      pArea->SetInUpdateChain( FALSE );
//STRIP001  }
//STRIP001  pEOUpdateChain = NULL;
//STRIP001 }

