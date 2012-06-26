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
#include <horiornt.hxx>
#include <doc.hxx>
#include <cntfrm.hxx>
#include <crsrsh.hxx>
#include <frmfmt.hxx>
#include <viscrs.hxx>
#include <ndtxt.hxx>
#include <shellres.hxx>
#include <cellfrm.hxx>

namespace binfilter {

// setze Crsr in die naechsten/vorherigen Celle

// suche die naechste nicht geschuetzte Zelle innerhalb der Tabelle
// Parameter:
//      rIdx    - steht auf dem TabellenNode
//      SwDoc   -
//  return:
//      0   - Idx steht auf/in einer nicht geschuetzten Zelle
//      !0  - Node hinter der Tabelle

// suche die vorherige nicht geschuetzte Zelle innerhalb der Tabelle
// Parameter:
//      rIdx    - steht auf dem EndNode der Tabelle
//      SwDoc   -
//  return:
//      0   - Idx steht auf/in einer nicht geschuetzten Zelle
//      !0  - Node hinter der Tabelle

bool GotoCurrTable( SwPaM&, SwPosTable, bool ) { return true; } // DBG_BF_ASSERT
bool SwCursor::MoveTable( SwWhichTable, SwPosTable ) { return false; } // DBG_BF_ASSERT

/*N*/ bool SwCrsrShell::CheckTblBoxCntnt( const SwPosition* pPos )
/*N*/ {
/*N*/   if( !pBoxIdx || !pBoxPtr || IsSelTblCells() || !IsAutoUpdateCells() )
/*N*/       return FALSE;

    // ueberpruefe, ob der Box Inhalt mit dem angegebenen Format der Box
    // ueber einstimmt. Wenn nicht, setze neu
/*?*/   SwTableBox* pChkBox = 0;
/*?*/   SwStartNode* pSttNd;
/*?*/   if( !pPos )
/*?*/   {
/*?*/       // gesicherte Position heraus holen.
/*?*/       if( pBoxIdx && pBoxPtr &&
/*?*/           0 != ( pSttNd = pBoxIdx->GetNode().GetStartNode() ) &&
/*?*/           SwTableBoxStartNode == pSttNd->GetStartNodeType() &&
/*?*/           pBoxPtr == pSttNd->FindTableNode()->GetTable().
/*?*/                       GetTblBox( pBoxIdx->GetIndex() ) )
/*?*/           pChkBox = pBoxPtr;
/*?*/   }
/*?*/   else if( 0 != ( pSttNd = pPos->nNode.GetNode().
/*?*/                               FindSttNodeByType( SwTableBoxStartNode )) )
/*?*/   {
/*?*/       pChkBox = pSttNd->FindTableNode()->GetTable().GetTblBox( pSttNd->GetIndex() );
/*?*/   }
/*?*/
/*?*/
/*?*/   // Box mehr als 1 Absatz?
/*?*/   if( pChkBox && pSttNd->GetIndex() + 2 != pSttNd->EndOfSectionIndex() )
/*?*/       pChkBox = 0;
/*?*/
/*?*/   // jetzt sollten wir mal die Pointer zerstoeren, bevor eine erneute
/*?*/   // Actionklammerung kommt.
/*?*/   if( !pPos && !pChkBox )
/*?*/       ClearTblBoxCntnt();
/*?*/
/*?*/   // liegt der Cursor nicht mehr in dem Bereich ?
/*?*/   if( pChkBox && !pPos &&
/*?*/       ( pCurCrsr->HasMark() || pCurCrsr->GetNext() != pCurCrsr ||
/*?*/         pSttNd->GetIndex() + 1 == pCurCrsr->GetPoint()->nNode.GetIndex() ))
/*?*/       pChkBox = 0;
/*?*/
/*?*/   //JP 12.01.99: hat sich der Inhalt der Box ueberhaupt veraendert?
/*?*/   // Ist wichtig, wenn z.B. Undo nicht den richtigen Inhalt wieder
/*?*/   // herstellen konnte.
/*?*/   if( pChkBox )
/*?*/   {
/*?*/       const SwTxtNode* pNd = GetDoc()->GetNodes()[
/*?*/                                   pSttNd->GetIndex() + 1 ]->GetTxtNode();
/*?*/       if( !pNd ||
/*?*/           ( pNd->GetTxt() == ViewShell::GetShellRes()->aCalc_Error &&
/*?*/             SFX_ITEM_SET == pChkBox->GetFrmFmt()->
/*?*/                           GetItemState( RES_BOXATR_FORMULA )) )
/*?*/           pChkBox = 0;
/*?*/   }
/*?*/
/*?*/   return 0 != pChkBox;
/*N*/ }

/*N*/ void SwCrsrShell::ClearTblBoxCntnt()
/*N*/ {
/*N*/   delete pBoxIdx, pBoxIdx = 0;
/*N*/   pBoxPtr = 0;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
