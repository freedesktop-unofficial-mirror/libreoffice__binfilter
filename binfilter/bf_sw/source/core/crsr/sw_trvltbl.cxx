/*************************************************************************
 *
 *  $RCSfile: sw_trvltbl.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:08:50 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif

#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>       //EndAllAction gibts nur an der EditShell
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _CALLNK_HXX
#include <callnk.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _CELLFRM_HXX //autogen
#include <cellfrm.hxx>
#endif

// setze Crsr in die naechsten/vorherigen Celle
//STRIP001 FASTBOOL SwCrsrShell::GoNextCell( BOOL bAppendLine )
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  const SwTableNode* pTblNd;
//STRIP001  if( IsTableMode() || 0 != ( pTblNd = IsCrsrInTbl() ))
//STRIP001  {
//STRIP001      SwCursor* pCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001      SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001      bRet = TRUE;
//STRIP001
//STRIP001      // folgt nach dem EndNode der Cell ein weiterer StartNode, dann
//STRIP001      // gibt es auch eine naechste Celle
//STRIP001      SwNodeIndex aCellStt( *pCrsr->GetNode()->FindTableBoxStartNode()->
//STRIP001                              EndOfSectionNode(), 1 );
//STRIP001      if( !aCellStt.GetNode().IsStartNode() )
//STRIP001      {
//STRIP001          if( pCrsr->HasMark() ||
//STRIP001              (!bAppendLine /*&& IsCrsrReadonly()*/ ))
//STRIP001              bRet = FALSE;
//STRIP001          else
//STRIP001          {
//STRIP001              // auf besonderen Wunsch: keine Line mehr vorhanden, dann
//STRIP001              // mache doch eine neue:
//STRIP001              const SwTableBox* pBox = pTblNd->GetTable().GetTblBox(
//STRIP001                                  pCrsr->GetPoint()->nNode.GetNode().
//STRIP001                                  StartOfSectionIndex() );
//STRIP001              ASSERT( pBox, "Box steht nicht in dieser Tabelle" );
//STRIP001              SwSelBoxes aBoxes;
//STRIP001
//STRIP001              //Das Dokument veraendert sich evtl. ohne Action wuerden die Sichten
//STRIP001              //nichts mitbekommen.
//STRIP001              ((SwEditShell*)this)->StartAllAction();
//STRIP001              bRet = pDoc->InsertRow( pTblNd->GetTable().
//STRIP001                                  SelLineFromBox( pBox, aBoxes, FALSE ));
//STRIP001              ((SwEditShell*)this)->EndAllAction();
//STRIP001          }
//STRIP001      }
//STRIP001      if( bRet && 0 != ( bRet = pCrsr->GoNextCell() ))
//STRIP001          UpdateCrsr();                 // und den akt. Updaten
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::GoPrevCell()
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  const SwTableNode* pTblNd;
//STRIP001  if( IsTableMode() || 0 != ( pTblNd = IsCrsrInTbl() ))
//STRIP001  {
//STRIP001      SwCursor* pCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001      SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001      bRet = pCrsr->GoPrevCell();
//STRIP001      if( bRet )
//STRIP001          UpdateCrsr();                 // und den akt. Updaten
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::GotoTblBox( const String& rName )
//STRIP001 {
//STRIP001  SwShellCrsr* pCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001
//STRIP001  FASTBOOL bRet = pCrsr->GotoTblBox( rName );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      //JP 28.10.97: Bug 45028 - die "oberste" Position setzen fuer
//STRIP001      //              wiederholte Kopfzeilen
//STRIP001      pCrsr->GetPtPos() = Point();
//STRIP001      UpdateCrsr( SwCrsrShell::SCROLLWIN | SwCrsrShell::CHKRANGE |
//STRIP001                  SwCrsrShell::READONLY ); // und den akt. Updaten
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::SelTblRow()
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwTabFrm *pTblFrm = pFrm->ImplFindTabFrm();
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001
//STRIP001  SwTblSearchType eType = TBLSEARCH_ROW;
//STRIP001  if( !IsReadOnlyAvailable() )
//STRIP001      eType = (SwTblSearchType)(eType | TBLSEARCH_PROTECT);
//STRIP001  GetTblSel( *this, aBoxes, eType );
//STRIP001
//STRIP001  if( !aBoxes.Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // noch kein Tabellen-Cursor vorhanden, dann erzeuge einen
//STRIP001  if( !pTblCrsr )
//STRIP001  {
//STRIP001      pTblCrsr = new SwShellTableCrsr( *this, *pCurCrsr->GetPoint() );
//STRIP001      pCurCrsr->DeleteMark();
//STRIP001      pCurCrsr->SwSelPaintRects::Hide();
//STRIP001  }
//STRIP001
//STRIP001 //   SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001  pTblCrsr->DeleteMark();
//STRIP001  // dann setze mal Anfang und Ende der Spalte
//STRIP001  pTblCrsr->GetPoint()->nNode = *aBoxes[0]->GetSttNd();
//STRIP001  pTblCrsr->Move( fnMoveForward, fnGoCntnt );
//STRIP001  pTblCrsr->SetMark();
//STRIP001  pTblCrsr->GetPoint()->nNode = *aBoxes[aBoxes.Count()-1]->GetSttNd();
//STRIP001  pTblCrsr->Move( fnMoveForward, fnGoCntnt );
//STRIP001  UpdateCrsr();                 // und den akt. Updaten
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::SelTblCol()
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwTabFrm *pTblFrm = pFrm->ImplFindTabFrm();
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  SwTblSearchType eType = TBLSEARCH_COL;
//STRIP001  if( !IsReadOnlyAvailable() )
//STRIP001      eType = (SwTblSearchType)(eType | TBLSEARCH_PROTECT);
//STRIP001  GetTblSel( *this, aBoxes, eType );
//STRIP001
//STRIP001  if( !aBoxes.Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // noch kein Tabellen-Cursor vorhanden, dann erzeuge einen
//STRIP001  if( !pTblCrsr )
//STRIP001  {
//STRIP001      pTblCrsr = new SwShellTableCrsr( *this, *pCurCrsr->GetPoint() );
//STRIP001      pCurCrsr->DeleteMark();
//STRIP001      pCurCrsr->SwSelPaintRects::Hide();
//STRIP001  }
//STRIP001
//STRIP001 //   SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001  pTblCrsr->DeleteMark();
//STRIP001  // dann setze mal Anfang und Ende der Spalte
//STRIP001  pTblCrsr->GetPoint()->nNode = *aBoxes[0]->GetSttNd();
//STRIP001  pTblCrsr->Move( fnMoveForward, fnGoCntnt );
//STRIP001  pTblCrsr->SetMark();
//STRIP001  pTblCrsr->GetPoint()->nNode = *aBoxes[aBoxes.Count()-1]->GetSttNd();
//STRIP001  pTblCrsr->Move( fnMoveForward, fnGoCntnt );
//STRIP001  UpdateCrsr();                 // und den akt. Updaten
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::SelTblBox()
//STRIP001 {
//STRIP001     // if we're in a table, create a table cursor, and select the cell
//STRIP001     // that the current cursor's point resides in
//STRIP001
//STRIP001     // search for start node of our table box. If not found, exit realy
//STRIP001     const SwStartNode* pStartNode =
//STRIP001         pCurCrsr->GetPoint()->nNode.GetNode().FindTableBoxStartNode();
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001     // the old code checks whether we're in a table by asking the
//STRIP001     // frame. This should yield the same result as searching for the
//STRIP001     // table box start node, right?
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  DBG_ASSERT( !pFrm->IsInTab() == !(pStartNode != NULL),
//STRIP001                 "Schroedinger's table: We're in a box, and also we aren't." )
//STRIP001 #endif
//STRIP001
//STRIP001     if( pStartNode == NULL )
//STRIP001         return FALSE;
//STRIP001
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001     // create a table cursor, if there isn't one already
//STRIP001  if( !pTblCrsr )
//STRIP001  {
//STRIP001      pTblCrsr = new SwShellTableCrsr( *this, *pCurCrsr->GetPoint() );
//STRIP001      pCurCrsr->DeleteMark();
//STRIP001      pCurCrsr->SwSelPaintRects::Hide();
//STRIP001  }
//STRIP001
//STRIP001     // select the complete box with our shiny new pTblCrsr
//STRIP001     // 1. delete mark, and move point to first content node in box
//STRIP001     // 2. set mark, and move point to last content node in box
//STRIP001     // 3. exchange
//STRIP001
//STRIP001  pTblCrsr->DeleteMark();
//STRIP001     *(pTblCrsr->GetPoint()) = SwPosition( *pStartNode );
//STRIP001     pTblCrsr->Move( fnMoveForward, fnGoNode );
//STRIP001
//STRIP001     pTblCrsr->SetMark();
//STRIP001     *(pTblCrsr->GetPoint()) = SwPosition( *(pStartNode->EndOfSectionNode()) );
//STRIP001     pTblCrsr->Move( fnMoveBackward, fnGoNode );
//STRIP001
//STRIP001     pTblCrsr->Exchange();
//STRIP001
//STRIP001     // with some luck, UpdateCrsr() will now update everything that
//STRIP001     // needs updateing
//STRIP001  UpdateCrsr();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


// suche die naechste nicht geschuetzte Zelle innerhalb der Tabelle
// Parameter:
//      rIdx    - steht auf dem TabellenNode
//      SwDoc   -
//  return:
//      0   - Idx steht auf/in einer nicht geschuetzten Zelle
//      !0  - Node hinter der Tabelle


//STRIP001 SwNode* lcl_FindNextCell( SwNodeIndex& rIdx, FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  // ueberpruefe geschuetzte Zellen
//STRIP001  SwCntntFrm* pFrm;
//STRIP001  SwNodeIndex aTmp( rIdx, 2 );        // TableNode + StartNode
//STRIP001  SwNodes& rNds = aTmp.GetNode().GetNodes();
//STRIP001  SwCntntNode* pCNd = aTmp.GetNode().GetCntntNode();
//STRIP001  if( !pCNd )
//STRIP001      pCNd = rNds.GoNext( &aTmp );
//STRIP001
//STRIP001  if( 0 == ( pFrm = pCNd->GetFrm()) ||
//STRIP001      (!bInReadOnly && pFrm->IsProtected() ))
//STRIP001  {
//STRIP001      aTmp.Assign( *pCNd->EndOfSectionNode(), 1 );
//STRIP001      SwNode* pNd;
//STRIP001      for( ;; )
//STRIP001      {
//STRIP001          if( !( pNd = &aTmp.GetNode())->IsStartNode() )
//STRIP001              return pNd;
//STRIP001          aTmp++;
//STRIP001          if( 0 == (pCNd = aTmp.GetNode().GetCntntNode()) )
//STRIP001              pCNd = rNds.GoNext( &aTmp );
//STRIP001
//STRIP001          if( 0 != ( pFrm = pCNd->GetFrm()) &&
//STRIP001              (bInReadOnly || !pFrm->IsProtected() ))
//STRIP001          {
//STRIP001              rIdx = *pNd;
//STRIP001              return 0;       // Ok, nicht geschuetzt
//STRIP001          }
//STRIP001          aTmp.Assign( *pCNd->EndOfSectionNode(), +1 );
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

// suche die vorherige nicht geschuetzte Zelle innerhalb der Tabelle
// Parameter:
//      rIdx    - steht auf dem EndNode der Tabelle
//      SwDoc   -
//  return:
//      0   - Idx steht auf/in einer nicht geschuetzten Zelle
//      !0  - Node hinter der Tabelle


//STRIP001 SwNode* lcl_FindPrevCell( SwNodeIndex& rIdx, FASTBOOL bInReadOnly  )
//STRIP001 {
//STRIP001  // ueberpruefe geschuetzte Zellen
//STRIP001  SwCntntFrm* pFrm;
//STRIP001  SwNodeIndex aTmp( rIdx, -2 );       // TableNode + EndNode
//STRIP001  SwNodes& rNds = aTmp.GetNode().GetNodes();
//STRIP001  SwCntntNode* pCNd = aTmp.GetNode().GetCntntNode();
//STRIP001  if( !pCNd )
//STRIP001      pCNd = rNds.GoNext( &aTmp );
//STRIP001
//STRIP001  if( 0 == ( pFrm = pCNd->GetFrm()) ||
//STRIP001      (!bInReadOnly && pFrm->IsProtected() ))
//STRIP001  {
//STRIP001      aTmp.Assign( *pCNd->StartOfSectionNode(), -1 );
//STRIP001      SwNode* pNd;
//STRIP001      for( ;; )
//STRIP001      {
//STRIP001          if( !( pNd = &aTmp.GetNode())->IsEndNode() )
//STRIP001              return pNd;
//STRIP001          aTmp--;
//STRIP001          if( 0 == (pCNd = aTmp.GetNode().GetCntntNode()) )
//STRIP001              pCNd = rNds.GoPrevious( &aTmp );
//STRIP001
//STRIP001          if( 0 != ( pFrm = pCNd->GetFrm()) &&
//STRIP001              (bInReadOnly || !pFrm->IsProtected() ))
//STRIP001          {
//STRIP001              rIdx = *pNd;
//STRIP001              return 0;       // Ok, nicht geschuetzt
//STRIP001          }
//STRIP001          aTmp.Assign( *pCNd->StartOfSectionNode(), - 1 );
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }



/*N*/ FASTBOOL GotoPrevTable( SwPaM& rCurCrsr, SwPosTable fnPosTbl,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwNodeIndex aIdx( rCurCrsr.GetPoint()->nNode );
//STRIP001  SwTableNode* pTblNd = aIdx.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001      aIdx.Assign( *pTblNd, - 1 );
//STRIP001
//STRIP001  do {
//STRIP001      while( aIdx.GetIndex() &&
//STRIP001          0 == ( pTblNd = aIdx.GetNode().FindStartNode()->GetTableNode()) )
//STRIP001          aIdx--;
//STRIP001
//STRIP001      if( pTblNd )        // gibt einen weiteren TableNode ?
//STRIP001      {
//STRIP001          if( fnPosTbl == fnMoveForward )         // an Anfang ?
//STRIP001          {
//STRIP001              aIdx = *aIdx.GetNode().StartOfSectionNode();
//STRIP001              if( lcl_FindNextCell( aIdx, bInReadOnly ))
//STRIP001              {
//STRIP001                  // Tabelle ueberspringen
//STRIP001                  aIdx.Assign( *pTblNd, -1 );
//STRIP001                  continue;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // ueberpruefe geschuetzte Zellen
//STRIP001              if( lcl_FindNextCell( aIdx, bInReadOnly ))
//STRIP001              {
//STRIP001                  // Tabelle ueberspringen
//STRIP001                  aIdx.Assign( *pTblNd, -1 );
//STRIP001                  continue;
//STRIP001              }
//STRIP001          }
//STRIP001          rCurCrsr.GetPoint()->nNode = aIdx;
//STRIP001          rCurCrsr.Move( fnPosTbl, fnGoCntnt );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  } while( pTblNd );
//STRIP001
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GotoNextTable( SwPaM& rCurCrsr, SwPosTable fnPosTbl,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwNodeIndex aIdx( rCurCrsr.GetPoint()->nNode );
//STRIP001  SwTableNode* pTblNd = aIdx.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001      aIdx.Assign( *pTblNd->EndOfSectionNode(), 1 );
//STRIP001
//STRIP001  ULONG nLastNd = rCurCrsr.GetDoc()->GetNodes().Count() - 1;
//STRIP001  do {
//STRIP001      while( aIdx.GetIndex() < nLastNd &&
//STRIP001              0 == ( pTblNd = aIdx.GetNode().GetTableNode()) )
//STRIP001          aIdx++;
//STRIP001      if( pTblNd )        // gibt einen weiteren TableNode ?
//STRIP001      {
//STRIP001          if( fnPosTbl == fnMoveForward )         // an Anfang ?
//STRIP001          {
//STRIP001              if( lcl_FindNextCell( aIdx, bInReadOnly ))
//STRIP001              {
//STRIP001                  // Tabelle ueberspringen
//STRIP001                  aIdx.Assign( *pTblNd->EndOfSectionNode(), + 1 );
//STRIP001                  continue;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aIdx = *aIdx.GetNode().EndOfSectionNode();
//STRIP001              // ueberpruefe geschuetzte Zellen
//STRIP001              if( lcl_FindNextCell( aIdx, bInReadOnly ))
//STRIP001              {
//STRIP001                  // Tabelle ueberspringen
//STRIP001                  aIdx.Assign( *pTblNd->EndOfSectionNode(), + 1 );
//STRIP001                  continue;
//STRIP001              }
//STRIP001          }
//STRIP001          rCurCrsr.GetPoint()->nNode = aIdx;
//STRIP001          rCurCrsr.Move( fnPosTbl, fnGoCntnt );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  } while( pTblNd );
//STRIP001
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GotoCurrTable( SwPaM& rCurCrsr, SwPosTable fnPosTbl,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwTableNode* pTblNd = rCurCrsr.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( fnPosTbl == fnMoveBackward )    // ans Ende der Tabelle
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *pTblNd->EndOfSectionNode() );
//STRIP001      if( lcl_FindPrevCell( aIdx, bInReadOnly ))
//STRIP001          return FALSE;
//STRIP001      rCurCrsr.GetPoint()->nNode = aIdx;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *pTblNd );
//STRIP001      if( lcl_FindNextCell( aIdx, bInReadOnly ))
//STRIP001          return FALSE;
//STRIP001      rCurCrsr.GetPoint()->nNode = aIdx;
//STRIP001  }
//STRIP001  rCurCrsr.Move( fnPosTbl, fnGoCntnt );
/*N*/   return TRUE;
/*N*/ }


/*N*/ FASTBOOL SwCursor::MoveTable( SwWhichTable fnWhichTbl, SwPosTable fnPosTbl )
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwTableCursor* pTblCrsr = (SwTableCursor*)*this;
//STRIP001
//STRIP001  if( pTblCrsr || !HasMark() )    // nur wenn kein Mark oder ein TblCrsr
//STRIP001  {
//STRIP001      SwCrsrSaveState aSaveState( *this );
//STRIP001      bRet = (*fnWhichTbl)( *this, fnPosTbl, IsReadOnlyAvailable() ) &&
//STRIP001                      !IsSelOvr( SELOVER_CHECKNODESSECTION | SELOVER_TOGGLE );
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

//STRIP001 FASTBOOL SwCrsrShell::MoveTable( SwWhichTable fnWhichTbl, SwPosTable fnPosTbl )
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001
//STRIP001  SwShellCrsr* pCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001  FASTBOOL bCheckPos, bRet;
//STRIP001  ULONG nPtNd;
//STRIP001  xub_StrLen nPtCnt;
//STRIP001
//STRIP001  if( !pTblCrsr && pCurCrsr->HasMark() )      // wenn Mark und kein TblCrsr,
//STRIP001  {
//STRIP001      // dann auf jedenfall in den Tabellen-Modus schalten
//STRIP001      pTblCrsr = new SwShellTableCrsr( *this, *pCurCrsr->GetPoint() );
//STRIP001      pCurCrsr->DeleteMark();
//STRIP001      pCurCrsr->SwSelPaintRects::Hide();
//STRIP001      pTblCrsr->SetMark();
//STRIP001      pCrsr = pTblCrsr;
//STRIP001      bCheckPos = FALSE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      bCheckPos = TRUE;
//STRIP001      nPtNd = pCrsr->GetPoint()->nNode.GetIndex();
//STRIP001      nPtCnt = pCrsr->GetPoint()->nContent.GetIndex();
//STRIP001  }
//STRIP001
//STRIP001  bRet = pCrsr->MoveTable( fnWhichTbl, fnPosTbl );
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      //JP 28.10.97: Bug 45028 - die "oberste" Position setzen fuer
//STRIP001      //              wiederholte Kopfzeilen
//STRIP001      pCrsr->GetPtPos() = Point();
//STRIP001
//STRIP001      UpdateCrsr(SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE|SwCrsrShell::READONLY);
//STRIP001
//STRIP001      if( bCheckPos &&
//STRIP001          pCrsr->GetPoint()->nNode.GetIndex() == nPtNd &&
//STRIP001          pCrsr->GetPoint()->nContent.GetIndex() == nPtCnt )
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::IsTblComplex() const
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm( FALSE );
//STRIP001  if ( pFrm && pFrm->IsInTab() )
//STRIP001      return pFrm->FindTabFrm()->GetTable()->IsTblComplex();
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::IsTblComplexForChart()
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001
//STRIP001     StartAction();   // IsTblComplexForChart() may trigger table formatting
//STRIP001                     // we better do that inside an action
//STRIP001
//STRIP001  const SwTableNode* pTNd = pCurCrsr->GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( pTNd )
//STRIP001  {
//STRIP001      // wir stehen in der Tabelle, dann teste mal, ob die Tabelle oder die
//STRIP001      // Selektion ausgeglichen ist.
//STRIP001      String sSel;
//STRIP001      if( pTblCrsr )
//STRIP001          sSel = GetBoxNms();
//STRIP001      bRet = pTNd->GetTable().IsTblComplexForChart( sSel );
//STRIP001  }
//STRIP001
//STRIP001  EndAction();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ String SwCrsrShell::GetBoxNms() const
/*N*/ {
/*N*/   String sNm;
/*N*/   const SwPosition* pPos;
/*N*/   SwFrm* pFrm;
/*N*/
/*N*/   if( IsTableMode() )
/*N*/   {
/*?*/       pFrm = pTblCrsr->Start()->nNode.GetNode().GetCntntNode()->GetFrm();
/*?*/
/*?*/       do {
/*?*/           pFrm = pFrm->GetUpper();
/*?*/       } while ( pFrm && !pFrm->IsCellFrm() );
/*?*/
/*?*/       ASSERT( pFrm, "kein Frame zur Box" );
/*?*/       sNm = ((SwCellFrm*)pFrm)->GetTabBox()->GetName();
/*?*/       sNm += ':';
/*?*/       pPos = pTblCrsr->End();
/*?*/   }
/*N*/   else
/*N*/   {
/*N*/       const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/       if( !pTblNd )
/*?*/           return sNm;
/*N*/       pPos = GetCrsr()->GetPoint();
/*N*/   }
/*N*/
/*N*/   pFrm = pPos->nNode.GetNode().GetCntntNode()->GetFrm();
/*N*/
/*N*/   do {
/*N*/       pFrm = pFrm->GetUpper();
/*N*/   } while ( pFrm && !pFrm->IsCellFrm() );
/*N*/
/*N*/   if( pFrm )
/*N*/       sNm += ((SwCellFrm*)pFrm)->GetTabBox()->GetName();
/*N*/
/*N*/   return sNm;
/*N*/ }


/*N*/ FASTBOOL SwCrsrShell::GotoTable( const String& rName )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return FALSE; //STRIP001 SwCallLink aLk( *this );       // Crsr-Moves ueberwachen,
//STRIP001 /*?*/    FASTBOOL bRet = !pTblCrsr && pCurCrsr->GotoTable( rName );
//STRIP001 /*?*/    if( bRet )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pCurCrsr->GetPtPos() = Point();
//STRIP001 /*?*/        UpdateCrsr( SwCrsrShell::SCROLLWIN | SwCrsrShell::CHKRANGE |
//STRIP001 /*?*/                    SwCrsrShell::READONLY ); // und den akt. Updaten
//STRIP001 /*?*/    }
//STRIP001 /*?*/    return bRet;
/*N*/ }


/*N*/ FASTBOOL SwCrsrShell::CheckTblBoxCntnt( const SwPosition* pPos )
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
/*?*/   if( pChkBox )
/*?*/   {
/*?*/       // jetzt sollten wir mal die Pointer zerstoeren, bevor ein weiterer
/*?*/       // aufruf kommt.
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ClearTblBoxCntnt();
//STRIP001 /*?*/        StartAction();
//STRIP001 /*?*/        GetDoc()->ChkBoxNumFmt( *pChkBox, TRUE );
//STRIP001 /*?*/        EndAction();
/*?*/   }
/*?*/
/*?*/   return 0 != pChkBox;
/*N*/ }


/*N*/ void SwCrsrShell::SaveTblBoxCntnt( const SwPosition* pPos )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  if( IsSelTblCells() || !IsAutoUpdateCells() )
//STRIP001      return ;
//STRIP001
//STRIP001  if( !pPos )
//STRIP001      pPos = pCurCrsr->GetPoint();
//STRIP001
//STRIP001  SwStartNode* pSttNd = pPos->nNode.GetNode().FindSttNodeByType( SwTableBoxStartNode );
//STRIP001
//STRIP001  BOOL bCheckBox = FALSE;
//STRIP001  if( pSttNd && pBoxIdx )
//STRIP001  {
//STRIP001      if( pSttNd == &pBoxIdx->GetNode() )
//STRIP001          pSttNd = 0;     // die haben wir schon
//STRIP001      else
//STRIP001          bCheckBox = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      bCheckBox = 0 != pBoxIdx;
//STRIP001
//STRIP001  if( bCheckBox )
//STRIP001  {
//STRIP001      // pBoxIdx Checken
//STRIP001      SwPosition aPos( *pBoxIdx );
//STRIP001      CheckTblBoxCntnt( &aPos );
//STRIP001  }
//STRIP001
//STRIP001  if( pSttNd )
//STRIP001  {
//STRIP001      pBoxPtr = pSttNd->FindTableNode()->GetTable().GetTblBox( pSttNd->GetIndex() );
//STRIP001
//STRIP001      if( pBoxIdx )
//STRIP001          *pBoxIdx = *pSttNd;
//STRIP001      else
//STRIP001          pBoxIdx = new SwNodeIndex( *pSttNd );
//STRIP001  }
/*N*/ }


/*N*/ void SwCrsrShell::ClearTblBoxCntnt()
/*N*/ {
/*N*/   delete pBoxIdx, pBoxIdx = 0;
/*N*/   pBoxPtr = 0;
/*N*/ }

/*N*/ FASTBOOL SwCrsrShell::EndAllTblBoxEdit()
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;
/*N*/   ViewShell *pSh = this;
/*N*/   do {
/*N*/       if( pSh->IsA( TYPE( SwCrsrShell ) ) )
/*N*/           bRet |= ((SwCrsrShell*)pSh)->CheckTblBoxCntnt(
/*N*/                       ((SwCrsrShell*)pSh)->pCurCrsr->GetPoint() );
/*N*/
/*N*/   } while( this != (pSh = (ViewShell *)pSh->GetNext()) );
/*N*/   return bRet;
/*N*/ }




