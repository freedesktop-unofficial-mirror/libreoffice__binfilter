/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */



#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <hintids.hxx>


#ifdef BIDI
#include <bf_svx/frmdiritem.hxx>
#endif

#include <horiornt.hxx>

#include <doc.hxx>
#include <rootfrm.hxx>
#include <pagefrm.hxx>
#include <viewimp.hxx>
#include <flyfrm.hxx>
#include <dview.hxx>
#include <viewopt.hxx>
#include <crsrsh.hxx>
#include <txtfrm.hxx>
#include <viscrs.hxx>
#include <section.hxx>
#include <globdoc.hxx>
#include <fmteiro.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::util;

/*N*/ TYPEINIT2(SwCrsrShell,ViewShell,SwModify);

// -------------- Methoden von der SwCrsrShell -------------

// gebe den aktuellen zurueck

/*N*/ SwPaM* SwCrsrShell::GetCrsr( bool /*bMakeTblCrsr*/ ) const
/*N*/ {
/*N*/   return pCurCrsr;
/*N*/ }

// alle Attribut/Format-Aenderungen am akt. Node werden an den
// Link weitergeleitet.

/*N*/ void SwCrsrShell::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   USHORT nWhich = pOld ? pOld->Which()
/*N*/                        : pNew ? pNew->Which()
/*N*/                               : sal::static_int_cast<USHORT>(RES_MSG_BEGIN);
/*N*/   if( bCallChgLnk &&
/*N*/       ( nWhich < RES_MSG_BEGIN || nWhich >= RES_MSG_END ||
/*N*/           nWhich == RES_FMT_CHG || nWhich == RES_UPDATE_ATTR ||
/*N*/           nWhich == RES_ATTRSET_CHG ))
/*N*/       // die Messages werden nicht weitergemeldet
/*N*/       //MA 07. Apr. 94 fix(6681): RES_UPDATE_ATTR wird implizit vom
/*N*/       //SwTxtNode::Insert(SwTxtHint*, USHORT) abgesetzt; hier wird reagiert und
/*N*/       //vom Insert brauch nicht mehr die Keule RES_FMT_CHG versandt werden.
/*N*/       CallChgLnk();
/*N*/
/*N*/   if( aGrfArrivedLnk.IsSet() &&
/*N*/       ( RES_GRAPHIC_ARRIVED == nWhich || RES_GRAPHIC_SWAPIN == nWhich ))
/*?*/       aGrfArrivedLnk.Call( this );
/*N*/ }

/*N*/ void SwCrsrShell::CallChgLnk()
/*N*/ {
/*N*/   // innerhalb von Start-/End-Action kein Call, sondern nur merken,
/*N*/   // das sich etwas geaendert hat. Wird bei EndAction beachtet.
/*N*/   if( BasicActionPend() )
/*N*/       bChgCallFlag = TRUE;        // das Change merken
/*N*/   else if( aChgLnk.IsSet() )
/*N*/   {
/*N*/       if( bCallChgLnk )
/*N*/           aChgLnk.Call( this );
/*N*/       bChgCallFlag = FALSE;       // Flag zuruecksetzen
/*N*/   }
/*N*/ }

// loesche alle erzeugten Crsr, setze den Tabellen-Crsr und den letzten
// Cursor auf seinen TextNode (oder StartNode?).
// Beim naechsten ::GetCrsr werden sie wieder alle erzeugt
// Wird fuers Drag&Drop / ClipBorad-Paste in Tabellen benoetigt.

/*N*/ SwCrsrShell::~SwCrsrShell()
/*N*/ {
/*N*/   // wenn es nicht die letzte View so sollte zu mindest das
/*N*/   // Feld noch geupdatet werden.
/*N*/   if( GetNext() != this )
/*?*/       CheckTblBoxCntnt( pCurCrsr->GetPoint() );
/*N*/   else
/*N*/       ClearTblBoxCntnt();
/*N*/
/*N*/   delete pVisCrsr;
/*N*/   delete pTblCrsr;
/*N*/
     /*
     * Freigabe der Cursor
      */
/*N*/   while(pCurCrsr->GetNext() != pCurCrsr)
/*?*/       delete pCurCrsr->GetNext();
/*N*/   delete pCurCrsr;
/*N*/
/*N*/   // Stack freigeben
/*N*/   if( pCrsrStk )
/*N*/   {
/*?*/       while( pCrsrStk->GetNext() != pCrsrStk )
/*?*/           delete pCrsrStk->GetNext();
/*?*/       delete pCrsrStk;
/*N*/   }

    // JP 27.07.98: Bug 54025 - ggfs. den HTML-Parser, der als Client in
    //              der CursorShell haengt keine Chance geben, sich an den
    //              TextNode zu haengen.
/*N*/   if( GetRegisteredIn() )
/*N*/       pRegisteredIn->Remove( this );
/*N*/ }

// SwCursor - Methode !!!!
/*N*/ bool SwCursor::IsReadOnlyAvailable() const
/*N*/ {
/*N*/   const SwShellCrsr* pShCrsr = *this;
/*N*/   const SwUnoCrsr* pUnoCrsr = *this;
/*N*/   return pShCrsr ? pShCrsr->GetShell()->IsReadOnlyAvailable() :
/*N*/       pUnoCrsr ? TRUE : FALSE;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
