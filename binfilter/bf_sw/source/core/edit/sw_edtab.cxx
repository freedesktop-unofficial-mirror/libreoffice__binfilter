/*************************************************************************
 *
 *  $RCSfile: sw_edtab.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:30 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#define _SVSTDARR_ULONGS
#include <svtools/svstdarr.hxx>

#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif

#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _LAYFRM_HXX
#include <layfrm.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _EDIMP_HXX
#include <edimp.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
#ifndef _SWDDETBL_HXX
#include <swddetbl.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
namespace binfilter {

//STRIP001 extern void ClearFEShellTabCols();

//STRIP001 const SwTable& SwEditShell::InsertTable( USHORT nRows, USHORT nCols,
//STRIP001                                      SwHoriOrient eAdj,
//STRIP001                                      USHORT nInsTblFlags,
//STRIP001                                      const SwTableAutoFmt* pTAFmt )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  SwPosition* pPos = GetCrsr()->GetPoint();
//STRIP001
//STRIP001  BOOL bEndUndo = 0 != pPos->nContent.GetIndex();
//STRIP001  if( bEndUndo )
//STRIP001  {
//STRIP001      StartUndo( UNDO_START );
//STRIP001      GetDoc()->SplitNode( *pPos );
//STRIP001  }
//STRIP001
//STRIP001     /* #109161# If called from a shell the adjust item is propagated
//STRIP001         from pPos to the new content nodes in the table.
//STRIP001      */
//STRIP001  const SwTable *pTable = GetDoc()->InsertTable( *pPos, nRows, nCols,
//STRIP001                                                    eAdj, nInsTblFlags, pTAFmt,
//STRIP001                                                    0, TRUE );
//STRIP001  if( bEndUndo )
//STRIP001      EndUndo( UNDO_END );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001  return *pTable;
//STRIP001 }

//STRIP001 BOOL SwEditShell::TextToTable( sal_Unicode cCh, SwHoriOrient eAdj,
//STRIP001                              USHORT nInsTblFlags,
//STRIP001                              const SwTableAutoFmt* pTAFmt )
//STRIP001 {
//STRIP001  SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
//STRIP001  BOOL bRet = FALSE;
//STRIP001  StartAllAction();
//STRIP001  FOREACHPAM_START(this)
//STRIP001      if( PCURCRSR->HasMark() )
//STRIP001          bRet |= 0 != GetDoc()->TextToTable( *PCURCRSR, cCh, eAdj,
//STRIP001                                              nInsTblFlags, pTAFmt );
//STRIP001  FOREACHPAM_END()
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::TableToText( sal_Unicode cCh )
//STRIP001 {
//STRIP001  SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  const SwTableNode* pTblNd =
//STRIP001          GetDoc()->IsIdxInTbl( pCrsr->GetPoint()->nNode );
//STRIP001  if( IsTableMode() )
//STRIP001  {
//STRIP001      ClearMark();
//STRIP001      pCrsr = GetCrsr();
//STRIP001  }
//STRIP001  else if( !pTblNd || pCrsr->GetNext() != pCrsr )
//STRIP001      return bRet;
//STRIP001
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  // verschiebe den akt. Cursor aus dem Tabellen Bereich
//STRIP001  // angemeldet ist
//STRIP001 #ifdef USED
//STRIP001  SwNodeIndex aTabIdx( pCrsr->GetPoint()->nNode );
//STRIP001 #else
//STRIP001  SwNodeIndex aTabIdx( *pTblNd );
//STRIP001 #endif
//STRIP001  pCrsr->DeleteMark();
//STRIP001  pCrsr->GetPoint()->nNode = *pTblNd->EndOfSectionNode();
//STRIP001  pCrsr->GetPoint()->nContent.Assign( 0, 0 );
//STRIP001  // SPoint und Mark aus dem Bereich verschieben !!!
//STRIP001  pCrsr->SetMark();
//STRIP001  pCrsr->DeleteMark();
//STRIP001
//STRIP001  bRet = GetDoc()->TableToText( pTblNd, cCh );
//STRIP001  pCrsr->GetPoint()->nNode = aTabIdx;
//STRIP001 #ifdef USED
//STRIP001  pCrsr->Move( fnMoveBackward, fnGoNode );
//STRIP001 #else
//STRIP001  SwCntntNode* pCNd = pCrsr->GetCntntNode();
//STRIP001  if( !pCNd )
//STRIP001      pCrsr->Move( fnMoveForward, fnGoCntnt );
//STRIP001  else
//STRIP001      pCrsr->GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001 #endif
//STRIP001
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SwEditShell::IsTextToTableAvailable() const
//STRIP001 {
//STRIP001  FASTBOOL bOnlyText = FALSE;
//STRIP001  FOREACHPAM_START(this)
//STRIP001      if( PCURCRSR->HasMark() && *PCURCRSR->GetPoint() != *PCURCRSR->GetMark() )
//STRIP001      {
//STRIP001          bOnlyText = TRUE;
//STRIP001
//STRIP001          // pruefe ob in der Selection eine Tabelle liegt
//STRIP001          ULONG nStt = PCURCRSR->GetMark()->nNode.GetIndex(),
//STRIP001                nEnd = PCURCRSR->GetPoint()->nNode.GetIndex();
//STRIP001          if( nStt > nEnd )   { ULONG n = nStt; nStt = nEnd; nEnd = n; }
//STRIP001
//STRIP001          for( ; nStt <= nEnd; ++nStt )
//STRIP001              if( !GetDoc()->GetNodes()[ nStt ]->IsTxtNode() )
//STRIP001              {
//STRIP001                  bOnlyText = FALSE;
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001          if( !bOnlyText )
//STRIP001              break;
//STRIP001      }
//STRIP001  FOREACHPAM_END()
//STRIP001
//STRIP001  return bOnlyText;
//STRIP001 }


//STRIP001 void SwEditShell::InsertDDETable( SwDDEFieldType* pDDEType,
//STRIP001                                          USHORT nRows, USHORT nCols,
//STRIP001                                          SwHoriOrient eAdj,
//STRIP001                                          USHORT nInsTblFlags )
//STRIP001 {
//STRIP001  SwPosition* pPos = GetCrsr()->GetPoint();
//STRIP001
//STRIP001  ASSERT( !GetDoc()->IsIdxInTbl( pPos->nNode ),
//STRIP001          "Tabelle in Tabelle nicht erlaubt" );
//STRIP001
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  BOOL bEndUndo = 0 != pPos->nContent.GetIndex();
//STRIP001  if( bEndUndo )
//STRIP001  {
//STRIP001      StartUndo( UNDO_START );
//STRIP001      GetDoc()->SplitNode( *pPos );
//STRIP001  }
//STRIP001
//STRIP001  SwTable* pTbl = (SwTable*)GetDoc()->InsertTable( *pPos, nRows, nCols, eAdj,
//STRIP001                                                  nInsTblFlags|DEFAULT_BORDER );
//STRIP001  SwTableNode* pTblNode = (SwTableNode*)pTbl->GetTabSortBoxes()[ 0 ]->
//STRIP001                                              GetSttNd()->FindTableNode();
//STRIP001  SwDDETable* pDDETbl = new SwDDETable( *pTbl, pDDEType );
//STRIP001  pTblNode->SetNewTable( pDDETbl );       // setze die DDE-Tabelle
//STRIP001
//STRIP001  if( bEndUndo )
//STRIP001      EndUndo( UNDO_END );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Tabellenfelder einer Tabelle updaten
 --------------------------------------------------------------------*/
/*N*/ void SwEditShell::UpdateTable()
/*N*/ {
/*N*/   const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/
/*N*/   // Keine Arme keine Kekse
/*N*/   if( pTblNd )
/*N*/   {
/*N*/       StartAllAction();
/*N*/       StartUndo();
/*N*/       EndAllTblBoxEdit();
/*N*/       SwTableFmlUpdate aTblUpdate( (SwTable*)&pTblNd->GetTable() );
/*N*/       GetDoc()->UpdateTblFlds( &aTblUpdate );
/*N*/       EndUndo();
/*N*/       EndAllAction();
/*N*/   }
/*N*/ }

    // Change Modus erfragen/setzen
/*N*/ USHORT SwEditShell::GetTblChgMode() const
/*N*/ {
/*N*/   USHORT nMode;
/*N*/   const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/   if( pTblNd )
/*N*/       nMode = pTblNd->GetTable().GetTblChgMode();
/*N*/   else
/*?*/       nMode = GetTblChgDefaultMode();
/*N*/   return nMode;
/*N*/ }

//STRIP001 void SwEditShell::SetTblChgMode( USHORT eMode )
//STRIP001 {
//STRIP001  const SwTableNode* pTblNd = IsCrsrInTbl();
//STRIP001
//STRIP001  // Keine Arme keine Kekse
//STRIP001  if( pTblNd )
//STRIP001  {
//STRIP001      ((SwTable&)pTblNd->GetTable()).SetTblChgMode( (TblChgMode)eMode );
//STRIP001      if( !GetDoc()->IsModified() )   // Bug 57028
//STRIP001          GetDoc()->SetUndoNoResetModified();
//STRIP001      GetDoc()->SetModified();
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwEditShell::GetTblBoxFormulaAttrs( SfxItemSet& rSet ) const
//STRIP001 {
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  if( IsTableMode() )
//STRIP001      ::binfilter::GetTblSelCrs( *this, aBoxes );
//STRIP001  else
//STRIP001  {
//STRIP001      SwPaM *pCrsr = GetCrsr();
//STRIP001      do {
//STRIP001          SwFrm *pFrm = GetCurrFrm();
//STRIP001          do {
//STRIP001              pFrm = pFrm->GetUpper();
//STRIP001          } while ( pFrm && !pFrm->IsCellFrm() );
//STRIP001          if ( pFrm )
//STRIP001          {
//STRIP001              SwTableBox *pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
//STRIP001              aBoxes.Insert( pBox );
//STRIP001          }
//STRIP001      } while( FALSE
//STRIP001              // JP 24.01.97: dann nur die akt. Zelle!!
//STRIP001          /*((SwEditShell*)this)->GoNextCrsr() && pCrsr != GetCrsr()*/ );
//STRIP001  }
//STRIP001
//STRIP001  for( USHORT n = 0; n < aBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      const SwTableBox* pSelBox = aBoxes[ n ];
//STRIP001      const SwTableBoxFmt* pTblFmt = (SwTableBoxFmt*)pSelBox->GetFrmFmt();
//STRIP001      if( !n )
//STRIP001      {
//STRIP001          // Formeln in die externe Darstellung bringen!
//STRIP001          const SwTable& rTbl = pSelBox->GetSttNd()->FindTableNode()->GetTable();
//STRIP001
//STRIP001          SwTableFmlUpdate aTblUpdate( (SwTable*)&rTbl );
//STRIP001          aTblUpdate.eFlags = TBL_BOXNAME;
//STRIP001          ((SwDoc*)GetDoc())->UpdateTblFlds( &aTblUpdate );
//STRIP001
//STRIP001          rSet.Put( pTblFmt->GetAttrSet() );
//STRIP001      }
//STRIP001      else
//STRIP001          rSet.MergeValues( pTblFmt->GetAttrSet() );
//STRIP001  }
//STRIP001  return 0 != rSet.Count();
//STRIP001 }

//STRIP001 void SwEditShell::SetTblBoxFormulaAttrs( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  if( IsTableMode() )
//STRIP001      ::binfilter::GetTblSelCrs( *this, aBoxes );
//STRIP001  else
//STRIP001  {
//STRIP001      SwPaM *pCrsr = GetCrsr();
//STRIP001      do {
//STRIP001          SwFrm *pFrm = GetCurrFrm();
//STRIP001          do {
//STRIP001              pFrm = pFrm->GetUpper();
//STRIP001          } while ( pFrm && !pFrm->IsCellFrm() );
//STRIP001          if ( pFrm )
//STRIP001          {
//STRIP001              SwTableBox *pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
//STRIP001              aBoxes.Insert( pBox );
//STRIP001          }
//STRIP001      } while( FALSE
//STRIP001              // JP 24.01.97: dann nur die akt. Zelle!!
//STRIP001          /*GoNextCrsr() && pCrsr != GetCrsr()*/ );
//STRIP001  }
//STRIP001
//STRIP001  // beim setzen einer Formel keine Ueberpruefung mehr vornehmen!
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_FORMULA ))
//STRIP001      ClearTblBoxCntnt();
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->StartUndo( UNDO_START );
//STRIP001  for( USHORT n = 0; n < aBoxes.Count(); ++n )
//STRIP001      GetDoc()->SetTblBoxFormulaAttrs( *aBoxes[ n ], rSet );
//STRIP001  GetDoc()->EndUndo( UNDO_END );
//STRIP001  EndAllAction();
//STRIP001 }

    // Zellenbreiten ueber Min/Max Berechnung an Tabellenbreite anpassen
//STRIP001 void SwEditShell::OptimizeTblBoxWidthMinMax()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  SwPaM *pCrsr = GetCrsr();
//STRIP001  SwTableNode* pTblNd = pCrsr->GetNode()->FindTableNode();
//STRIP001  if( pTblNd && !pTblNd->GetTable().IsTblComplex() )
//STRIP001  {
//STRIP001      SwTabFrm* pTabFrm = 0;
//STRIP001      SvULongs aMinArr( 16, 16 ), aMaxArr( 16, 16 );
//STRIP001
//STRIP001      // ueber alle Spalten aller Zeilen und die Min/Max Breiten einsammeln
//STRIP001      SwTableLines& rTblLns = pTblNd->GetTable().GetTabLines();
//STRIP001      for( USHORT n = rTblLns.Count(); n; )
//STRIP001      {
//STRIP001          SwTableBoxes& rTblBxs = rTblLns[ --n ]->GetTabBoxes();
//STRIP001          for( USHORT i = 0; i < rTblBxs.Count(); ++i )
//STRIP001          {
//STRIP001              SwTableBox* pBox = rTblBxs[ i ];
//STRIP001
//STRIP001              ULONG nMinCell = 0;
//STRIP001              ULONG nMaxCell = 0;
//STRIP001
//STRIP001              // ueber alle Absaetze und die Min/Maxbreiten berechnen
//STRIP001              const SwStartNode* pSttNd = pBox->GetSttNd();
//STRIP001              SwNodeIndex aIdx( *pSttNd, 1 );
//STRIP001              SwNodeIndex aEnd( *pSttNd->EndOfSectionNode() );
//STRIP001              while( aIdx < aEnd )
//STRIP001              {
//STRIP001                  SwTxtNode *pTxtNd = aIdx.GetNode().GetTxtNode();
//STRIP001                  if( pTxtNd )
//STRIP001                  {
//STRIP001                      ULONG nMinCnts;
//STRIP001                      ULONG nMaxCnts;
//STRIP001                      ULONG nAbsMinCnts;
//STRIP001                      pTxtNd->GetMinMaxSize( aIdx.GetIndex(), nMinCnts,
//STRIP001                                             nMaxCnts, nAbsMinCnts );
//STRIP001
//STRIP001                      if( nMinCnts > nMinCell )
//STRIP001                          nMinCell = nMinCnts;
//STRIP001                      if( nMaxCnts > nMaxCell )
//STRIP001                          nMaxCell = nMaxCnts;
//STRIP001
//STRIP001                      if( !pTabFrm )
//STRIP001                      {
//STRIP001                          SwCntntFrm* pCFrm = pTxtNd->GetFrm( 0, 0, FALSE );
//STRIP001                          if( pCFrm )
//STRIP001                              pTabFrm = pCFrm->FindTabFrm();
//STRIP001                      }
//STRIP001                  }
//STRIP001                  aIdx++;
//STRIP001              }
//STRIP001
//STRIP001              // Mindestbreite fuer Inhalt einhalten
//STRIP001              if( nMinCell < MINLAY )
//STRIP001                  nMinCell = MINLAY;
//STRIP001              if( nMaxCell < MINLAY )
//STRIP001                  nMaxCell = MINLAY;
//STRIP001
//STRIP001              // Umrandung und Abstand zum Inhalt beachten
//STRIP001              const SvxBoxItem& rBoxItem = pBox->GetFrmFmt()->GetBox();
//STRIP001              USHORT nBrdDist = 0;
//STRIP001              if( rBoxItem.GetLeft() )
//STRIP001              {
//STRIP001                  USHORT nWidth = rBoxItem.GetLeft()->GetOutWidth() +
//STRIP001                                  rBoxItem.GetLeft()->GetInWidth();
//STRIP001                  if( !nBrdDist )
//STRIP001                      nBrdDist = rBoxItem.GetLeft()->GetDistance();
//STRIP001
//STRIP001                  nMinCell += nWidth;
//STRIP001                  nMaxCell += nWidth;
//STRIP001              }
//STRIP001              if( rBoxItem.GetRight() )
//STRIP001              {
//STRIP001                  USHORT nWidth = rBoxItem.GetRight()->GetOutWidth() +
//STRIP001                                  rBoxItem.GetRight()->GetInWidth();
//STRIP001                  if( !nBrdDist )
//STRIP001                      nBrdDist = rBoxItem.GetRight()->GetDistance();
//STRIP001
//STRIP001                  nMinCell += nWidth;
//STRIP001                  nMaxCell += nWidth;
//STRIP001              }
//STRIP001              if( !nBrdDist )
//STRIP001                  nBrdDist = MIN_BORDER_DIST;
//STRIP001              nMinCell += 2 * nBrdDist;
//STRIP001              nMaxCell += 2 * nBrdDist;
//STRIP001
//STRIP001              // Max/Min-Werte in den Arrays merken
//STRIP001              if( i >= aMinArr.Count() )
//STRIP001                  aMinArr.Insert( nMinCell, i );
//STRIP001              else if( nMinCell > aMinArr[ i ] )
//STRIP001                  aMinArr.Replace( nMinCell, i );
//STRIP001
//STRIP001              if( i >= aMaxArr.Count() )
//STRIP001                  aMaxArr.Insert( nMaxCell, i );
//STRIP001              else if( nMaxCell > aMaxArr[ i ] )
//STRIP001                  aMaxArr.Replace( nMaxCell, i );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      ASSERT( pTabFrm, "ohne TabFrm kann nichts berechnet werden" );
//STRIP001      if( pTabFrm )
//STRIP001      {
//STRIP001          // 2. Teil die Zellen an die Breiten anpassen
//STRIP001          ULONG nTableMin = 0;
//STRIP001          ULONG nTableMax = 0;
//STRIP001          for( n = aMinArr.Count(); n; )
//STRIP001          {
//STRIP001              nTableMin += aMinArr[ --n ];
//STRIP001              nTableMax += aMaxArr[   n ];
//STRIP001          }
//STRIP001
//STRIP001          // Dann errechne mal die Breiten fuer die Spalten. Die Werte
//STRIP001          // werden im MinArray gesammelt!
//STRIP001
//STRIP001          // die MinBreite ist schon groesser als der vorgesehene Platz
//STRIP001          ULONG nAbsTabWidth = pTabFrm->Prt().Width();
//STRIP001          if( nTableMin > nAbsTabWidth )
//STRIP001          {
//STRIP001              for( n = aMinArr.Count(); n; )
//STRIP001              {
//STRIP001                  ULONG nColMin = aMinArr[ --n ];
//STRIP001                  nColMin *= nAbsTabWidth;
//STRIP001                  nColMin /= nTableMin;
//STRIP001                  aMinArr.Replace( nColMin, n );
//STRIP001              }
//STRIP001          }
//STRIP001          // die MaxBreite ist kleiner als der vorgesehene Platz
//STRIP001          else if( nTableMax < nAbsTabWidth )
//STRIP001          {
//STRIP001              for( n = aMinArr.Count(); n; )
//STRIP001              {
//STRIP001                  ULONG nColMax = aMaxArr[ --n ];
//STRIP001                  nColMax *= nAbsTabWidth;
//STRIP001                  nColMax /= nTableMax;
//STRIP001                  aMinArr.Replace( nColMax, n );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              double nW = nAbsTabWidth - nTableMin;
//STRIP001              double nD = nTableMax == nTableMin ? 1 : nTableMax - nTableMin;
//STRIP001              for( n = 0; n < aMinArr.Count(); ++n )
//STRIP001              {
//STRIP001                  double nd = aMaxArr[ n ] - aMinArr[ n ];
//STRIP001                  ULONG nAbsColWidth = aMinArr[ n ] + (ULONG)(( nd * nW ) / nD );
//STRIP001                  aMinArr.Replace( nAbsColWidth, n );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          StartAllAction();
//STRIP001          GetDoc()->AppendUndoForAttrTable( pTblNd->GetTable() );
//STRIP001
//STRIP001          for( n = 0; n < rTblLns.Count(); ++n )
//STRIP001          {
//STRIP001              SwTableBoxes& rTblBxs = rTblLns[ n ]->GetTabBoxes();
//STRIP001              for( USHORT i = rTblBxs.Count(); i; )
//STRIP001              {
//STRIP001                  SwTableBox* pBox = rTblBxs[ --i ];
//STRIP001                  pBox->ClaimFrmFmt()->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE,
//STRIP001                                                  aMinArr[ i ] ));
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          SwTableFmt* pFmt = (SwTableFmt*)pTblNd->GetTable().GetFrmFmt();
//STRIP001          pFmt->LockModify();
//STRIP001          pFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nAbsTabWidth ));
//STRIP001          pFmt->UnlockModify();
//STRIP001
//STRIP001          EndAllAction();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwEditShell::IsTableBoxTextFormat() const
//STRIP001 {
//STRIP001  if( IsTableMode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTableBox *pBox = 0;
//STRIP001  SwPaM *pCrsr = GetCrsr();
//STRIP001  {
//STRIP001      SwFrm *pFrm = GetCurrFrm();
//STRIP001      do {
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      } while ( pFrm && !pFrm->IsCellFrm() );
//STRIP001      if ( pFrm )
//STRIP001          pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
//STRIP001  }
//STRIP001
//STRIP001  if( !pBox )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ULONG nFmt;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  if( SFX_ITEM_SET == pBox->GetFrmFmt()->GetAttrSet().GetItemState(
//STRIP001      RES_BOXATR_FORMAT, TRUE, &pItem ))
//STRIP001  {
//STRIP001      nFmt = ((SwTblBoxNumFormat*)pItem)->GetValue();
//STRIP001      return GetDoc()->GetNumberFormatter()->IsTextFormat( nFmt ) ||
//STRIP001              NUMBERFORMAT_TEXT == nFmt;
//STRIP001  }
//STRIP001
//STRIP001  ULONG nNd = pBox->IsValidNumTxtNd();
//STRIP001  if( ULONG_MAX == nNd )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  const String& rTxt = GetDoc()->GetNodes()[ nNd ]->GetTxtNode()->GetTxt();
//STRIP001  if( !rTxt.Len() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  double fVal;
//STRIP001  return !GetDoc()->GetNumberFormatter()->IsNumberFormat( rTxt, nFmt, fVal );
//STRIP001 }

//STRIP001 String SwEditShell::GetTableBoxText() const
//STRIP001 {
//STRIP001  String sRet;
//STRIP001  if( !IsTableMode() )
//STRIP001  {
//STRIP001      SwTableBox *pBox = 0;
//STRIP001      SwPaM *pCrsr = GetCrsr();
//STRIP001      {
//STRIP001          SwFrm *pFrm = GetCurrFrm();
//STRIP001          do {
//STRIP001              pFrm = pFrm->GetUpper();
//STRIP001          } while ( pFrm && !pFrm->IsCellFrm() );
//STRIP001          if ( pFrm )
//STRIP001              pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
//STRIP001      }
//STRIP001
//STRIP001      ULONG nNd;
//STRIP001      if( pBox && ULONG_MAX != ( nNd = pBox->IsValidNumTxtNd() ) )
//STRIP001          sRet = GetDoc()->GetNodes()[ nNd ]->GetTxtNode()->GetTxt();
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::SplitTable( USHORT eMode )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwPaM *pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNode()->FindTableNode() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      GetDoc()->StartUndo();
//STRIP001
//STRIP001      bRet = GetDoc()->SplitTable( *pCrsr->GetPoint(), eMode, TRUE );
//STRIP001
//STRIP001      GetDoc()->EndUndo();
//STRIP001      ClearFEShellTabCols();
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::MergeTable( BOOL bWithPrev, USHORT nMode )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwPaM *pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNode()->FindTableNode() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      GetDoc()->StartUndo();
//STRIP001
//STRIP001      bRet = GetDoc()->MergeTable( *pCrsr->GetPoint(), bWithPrev, nMode );
//STRIP001
//STRIP001      GetDoc()->EndUndo();
//STRIP001      ClearFEShellTabCols();
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::CanMergeTable( BOOL bWithPrev, BOOL* pChkNxtPrv ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwPaM *pCrsr = GetCrsr();
//STRIP001  const SwTableNode* pTblNd = pCrsr->GetNode()->FindTableNode();
//STRIP001  if( pTblNd && !pTblNd->GetTable().ISA( SwDDETable ))
//STRIP001  {
//STRIP001      const SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001      if( pChkNxtPrv )
//STRIP001      {
//STRIP001          const SwTableNode* pChkNd = rNds[ pTblNd->GetIndex() - 1 ]->FindTableNode();
//STRIP001          if( pChkNd && !pChkNd->GetTable().ISA( SwDDETable ) )
//STRIP001              *pChkNxtPrv = TRUE, bRet = TRUE;        // mit Prev ist moeglich
//STRIP001          else
//STRIP001          {
//STRIP001              pChkNd = rNds[ pTblNd->EndOfSectionIndex() + 1 ]->GetTableNode();
//STRIP001              if( pChkNd && !pChkNd->GetTable().ISA( SwDDETable ) )
//STRIP001                  *pChkNxtPrv = FALSE, bRet = TRUE;       // mit Next ist moeglich
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( bWithPrev )
//STRIP001              pTblNd = rNds[ pTblNd->GetIndex() - 1 ]->FindTableNode();
//STRIP001          else
//STRIP001              pTblNd = rNds[ pTblNd->EndOfSectionIndex() + 1 ]->GetTableNode();
//STRIP001
//STRIP001          bRet = pTblNd && !pTblNd->GetTable().ISA( SwDDETable );
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

        // setze das InsertDB als Tabelle Undo auf:
//STRIP001 void SwEditShell::AppendUndoForInsertFromDB( BOOL bIsTable )
//STRIP001 {
//STRIP001  GetDoc()->AppendUndoForInsertFromDB( *GetCrsr(), bIsTable );
//STRIP001 }

}
