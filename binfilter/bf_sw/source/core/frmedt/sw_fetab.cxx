/*************************************************************************
 *
 *  $RCSfile: sw_fetab.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:19:49 $
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

#define ITEMID_BOXINFO SID_ATTR_BORDER_INNER
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef __RSC //autogen
#include <tools/errinf.hxx>
#endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif

#ifndef _RULER_HXX
#include <svtools/ruler.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWDDETBL_HXX
#include <swddetbl.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
#ifndef _TABCOL_HXX
#include <tabcol.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif

//siehe auch swtable.cxx
#define COLFUZZY 20L

//STRIP001 inline BOOL IsSame( long nA, long nB ) { return  Abs(nA-nB) <= COLFUZZY; }

/*N*/ SwTabCols *pLastCols   = 0;
//STRIP001 const SwTable   *pLastTable  = 0;
//STRIP001 const SwTabFrm  *pLastTabFrm = 0;
//STRIP001 const SwFrm  *pLastCellFrm = 0;

//STRIP001 class TblWait
//STRIP001 {
//STRIP001  SwWait *pWait;
//STRIP001 public:
//STRIP001  TblWait( USHORT nCnt, SwFrm *pFrm, SwDocShell &rDocShell, USHORT nCnt2 = 0);
//STRIP001  ~TblWait() { delete pWait; }
//STRIP001 };

//STRIP001 TblWait::TblWait( USHORT nCnt, SwFrm *pFrm, SwDocShell &rDocShell, USHORT nCnt2):
//STRIP001  pWait( 0 )
//STRIP001 {
//STRIP001  BOOL bWait = 20 < nCnt || 20 < nCnt2 || (pFrm &&
//STRIP001               20 < pFrm->ImplFindTabFrm()->GetTable()->GetTabLines().Count());
//STRIP001  if( bWait )
//STRIP001      pWait = new SwWait( rDocShell, TRUE );
//STRIP001 }

/*N*/ inline const SwCursor& GetShellCursor( const SwCrsrShell& rShell )
/*N*/ {
/*N*/   const SwShellCrsr *pCrsr = rShell.GetTableCrsr();
/*N*/   if( !pCrsr )
/*N*/       pCrsr = (SwShellCrsr*)*rShell.GetSwCrsr( FALSE );
/*N*/   return *pCrsr;
/*N*/ }

//STRIP001 void SwFEShell::ParkCursorInTab()
//STRIP001 {
//STRIP001     SwCursor * pSwCrsr = GetSwCrsr();
//STRIP001
//STRIP001     ASSERT(pSwCrsr, "no SwCursor");
//STRIP001
//STRIP001     SwPosition aStartPos = *pSwCrsr->GetPoint(), aEndPos = aStartPos;
//STRIP001
//STRIP001     SwCursor * pTmpCrsr = (SwCursor *) pSwCrsr;
//STRIP001
//STRIP001     /* Search least and greatest position in current cursor ring.
//STRIP001      */
//STRIP001     do
//STRIP001     {
//STRIP001         const SwPosition * pPt = pTmpCrsr->GetPoint(),
//STRIP001             * pMk = pTmpCrsr->GetMark();
//STRIP001
//STRIP001         if (*pPt < aStartPos)
//STRIP001             aStartPos = *pPt;
//STRIP001
//STRIP001         if (*pPt > aEndPos)
//STRIP001             aEndPos = *pPt;
//STRIP001
//STRIP001         if (*pMk < aStartPos)
//STRIP001             aStartPos = *pMk;
//STRIP001
//STRIP001         if (*pMk > aEndPos)
//STRIP001             aEndPos = *pMk;
//STRIP001
//STRIP001         pTmpCrsr = (SwCursor *) pTmpCrsr->GetNext();
//STRIP001     }
//STRIP001     while (pTmpCrsr != pSwCrsr);
//STRIP001
//STRIP001     KillPams();
//STRIP001
//STRIP001     /* Set cursor to end of selection to ensure IsLastCellInRow works
//STRIP001        properly. */
//STRIP001     {
//STRIP001         SwCursor aTmpCrsr(aEndPos);
//STRIP001         *pSwCrsr = aTmpCrsr;
//STRIP001     }
//STRIP001
//STRIP001     /* Move the cursor out of the columns to delete and stay in the
//STRIP001        same row. If the table has only one column the cursor will
//STRIP001        stay in the row and the shell will take care of it. */
//STRIP001     if (IsLastCellInRow())
//STRIP001     {
//STRIP001         /* If the cursor is in the last row of the table, first
//STRIP001            try to move it to the previous cell. If that fails move
//STRIP001            it to the next cell. */
//STRIP001
//STRIP001         {
//STRIP001             SwCursor aTmpCrsr(aStartPos);
//STRIP001             *pSwCrsr = aTmpCrsr;
//STRIP001         }
//STRIP001
//STRIP001         if (! pSwCrsr->GoPrevCell())
//STRIP001         {
//STRIP001             SwCursor aTmpCrsr(aEndPos);
//STRIP001             *pSwCrsr = aTmpCrsr;
//STRIP001             pSwCrsr->GoNextCell();
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         /* If the cursor is not in the last row of the table, first
//STRIP001            try to move it to the next cell. If that fails move it
//STRIP001            to the previous cell. */
//STRIP001
//STRIP001         {
//STRIP001             SwCursor aTmpCrsr(aEndPos);
//STRIP001             *pSwCrsr = aTmpCrsr;
//STRIP001         }
//STRIP001
//STRIP001         if (! pSwCrsr->GoNextCell())
//STRIP001         {
//STRIP001             SwCursor aTmpCrsr(aStartPos);
//STRIP001             *pSwCrsr = aTmpCrsr;
//STRIP001             pSwCrsr->GoPrevCell();
//STRIP001         }
//STRIP001     }
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  GetStartEndCell
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 23. May. 95
#***********************************************************************/
//STRIP001 void SwFEShell::GetStartEndCell( SwLayoutFrm *&prStart, SwLayoutFrm *&prEnd )
//STRIP001 {
//STRIP001  SwPaM* pPam = IsTableMode() ? GetTblCrs() : GetCrsr();
//STRIP001  SwShellCrsr *pICr = (SwShellCrsr*)*((SwCursor*)pPam);
//STRIP001
//STRIP001  ASSERT( pICr->GetCntntNode() && pICr->GetCntntNode( FALSE ),
//STRIP001          "Tabselection nicht auf Cnt." );
//STRIP001
//STRIP001  prStart = pICr->GetCntntNode()->GetFrm( &pICr->GetPtPos() )->GetUpper(),
//STRIP001  prEnd   = pICr->GetCntntNode(FALSE)->GetFrm( &pICr->GetMkPos() )->GetUpper();
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  InsertRow(), InsertCol
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/
//STRIP001 BOOL SwFEShell::InsertRow( USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der Point/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( *this, aBoxes, TBLSEARCH_ROW );
//STRIP001
//STRIP001  TblWait( nCnt, pFrm, *GetDoc()->GetDocShell(), aBoxes.Count() );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if ( aBoxes.Count() )
//STRIP001      bRet = GetDoc()->InsertRow( aBoxes, nCnt, bBehind );
//STRIP001
//STRIP001  EndAllActionAndCall();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::InsertCol( USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der Point/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  if( !CheckSplitCells( *this, nCnt + 1, TBLSEARCH_COL ) )
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLINSCOL_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( *this, aBoxes, TBLSEARCH_COL );
//STRIP001
//STRIP001  TblWait( nCnt, pFrm, *GetDoc()->GetDocShell(), aBoxes.Count() );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( aBoxes.Count() )
//STRIP001      bRet = GetDoc()->InsertCol( aBoxes, nCnt, bBehind );
//STRIP001
//STRIP001  EndAllActionAndCall();
//STRIP001  return bRet;
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  DeleteRow(), DeleteCol()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/

/**
   Determines if the current cursor is in the last row of the table.
*/
//STRIP001 BOOL SwFEShell::IsLastCellInRow() const
//STRIP001 {
//STRIP001     SwTabCols aTabCols;
//STRIP001     GetTabCols( aTabCols );
//STRIP001     BOOL bResult = FALSE;
//STRIP001
//STRIP001     if (IsTableRightToLeft())
//STRIP001         /* If the table is right-to-left the last row is the most left one. */
//STRIP001         bResult = 0 == GetCurTabColNum();
//STRIP001     else
//STRIP001         /* If the table is left-to-right the last row is the most right one. */
//STRIP001         bResult = aTabCols.Count() == GetCurTabColNum();
//STRIP001
//STRIP001     return bResult;
//STRIP001 }

//STRIP001 BOOL SwFEShell::DeleteCol()
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  BOOL bRet;
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( *this, aBoxes, TBLSEARCH_COL );
//STRIP001  if ( aBoxes.Count() )
//STRIP001  {
//STRIP001      TblWait( aBoxes.Count(), pFrm, *GetDoc()->GetDocShell() );
//STRIP001
//STRIP001      // die Crsr muessen noch aus dem Loesch Bereich entfernt
//STRIP001      // werden. Setze sie immer hinter/auf die Tabelle; ueber die
//STRIP001      // Dokument-Position werden sie dann immer an die alte Position gesetzt.
//STRIP001      while( !pFrm->IsCellFrm() )
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001
//STRIP001         ParkCursorInTab();
//STRIP001
//STRIP001      // dann loesche doch die Spalten
//STRIP001      bRet = GetDoc()->DeleteRowCol( aBoxes );
//STRIP001
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001
//STRIP001  EndAllActionAndCall();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::DeleteRow()
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  BOOL bRet;
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( *this, aBoxes, TBLSEARCH_ROW );
//STRIP001
//STRIP001  if( aBoxes.Count() )
//STRIP001  {
//STRIP001      TblWait( aBoxes.Count(), pFrm, *GetDoc()->GetDocShell() );
//STRIP001
//STRIP001      // die Crsr aus dem Loeschbereich entfernen.
//STRIP001      // Der Cursor steht danach:
//STRIP001      //  - es folgt noch eine Zeile, in dieser
//STRIP001      //  - vorher steht noch eine Zeile, in dieser
//STRIP001      //  - sonst immer dahinter
//STRIP001      {
//STRIP001          SwTableNode* pTblNd = ((SwCntntFrm*)pFrm)->GetNode()->FindTableNode();
//STRIP001
//STRIP001          // suche alle Boxen / Lines
//STRIP001          _FndBox aFndBox( 0, 0 );
//STRIP001          {
//STRIP001              _FndPara aPara( aBoxes, &aFndBox );
//STRIP001              pTblNd->GetTable().GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001          }
//STRIP001
//STRIP001          if( !aFndBox.GetLines().Count() )
//STRIP001          {
//STRIP001              EndAllActionAndCall();
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001
//STRIP001          KillPams();
//STRIP001
//STRIP001          _FndBox* pFndBox = &aFndBox;
//STRIP001          while( 1 == pFndBox->GetLines().Count() &&
//STRIP001                  1 == pFndBox->GetLines()[0]->GetBoxes().Count() )
//STRIP001          {
//STRIP001              _FndBox* pTmp = pFndBox->GetLines()[0]->GetBoxes()[0];
//STRIP001              if( pTmp->GetBox()->GetSttNd() )
//STRIP001                  break;      // das ist sonst zu weit
//STRIP001              pFndBox = pTmp;
//STRIP001          }
//STRIP001
//STRIP001          SwTableLine* pDelLine = pFndBox->GetLines()[
//STRIP001                          pFndBox->GetLines().Count()-1 ]->GetLine();
//STRIP001          SwTableBox* pDelBox = pDelLine->GetTabBoxes()[
//STRIP001                              pDelLine->GetTabBoxes().Count() - 1 ];
//STRIP001          while( !pDelBox->GetSttNd() )
//STRIP001          {
//STRIP001              SwTableLine* pLn = pDelBox->GetTabLines()[
//STRIP001                          pDelBox->GetTabLines().Count()-1 ];
//STRIP001              pDelBox = pLn->GetTabBoxes()[ pLn->GetTabBoxes().Count() - 1 ];
//STRIP001          }
//STRIP001          SwTableBox* pNextBox = pDelLine->FindNextBox( pTblNd->GetTable(),
//STRIP001                                                          pDelBox, TRUE );
//STRIP001          while( pNextBox &&
//STRIP001                  pNextBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001              pNextBox = pNextBox->FindNextBox( pTblNd->GetTable(), pNextBox );
//STRIP001
//STRIP001          if( !pNextBox )         // keine nachfolgende? dann die vorhergehende
//STRIP001          {
//STRIP001              pDelLine = pFndBox->GetLines()[ 0 ]->GetLine();
//STRIP001              pDelBox = pDelLine->GetTabBoxes()[ 0 ];
//STRIP001              while( !pDelBox->GetSttNd() )
//STRIP001                  pDelBox = pDelBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001              pNextBox = pDelLine->FindPreviousBox( pTblNd->GetTable(),
//STRIP001                                                          pDelBox, TRUE );
//STRIP001              while( pNextBox &&
//STRIP001                      pNextBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001                  pNextBox = pNextBox->FindPreviousBox( pTblNd->GetTable(), pNextBox );
//STRIP001          }
//STRIP001
//STRIP001          ULONG nIdx;
//STRIP001          if( pNextBox )      // dann den Cursor hier hinein
//STRIP001              nIdx = pNextBox->GetSttIdx() + 1;
//STRIP001          else                // ansonsten hinter die Tabelle
//STRIP001              nIdx = pTblNd->EndOfSectionIndex() + 1;
//STRIP001
//STRIP001          SwNodeIndex aIdx( GetDoc()->GetNodes(), nIdx );
//STRIP001          SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
//STRIP001          if( !pCNd )
//STRIP001              pCNd = GetDoc()->GetNodes().GoNext( &aIdx );
//STRIP001
//STRIP001          if( pCNd )
//STRIP001          {
//STRIP001              SwPaM* pPam = GetCrsr();
//STRIP001              pPam->GetPoint()->nNode = aIdx;
//STRIP001              pPam->GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001              pPam->SetMark();            // beide wollen etwas davon haben
//STRIP001              pPam->DeleteMark();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // dann loesche doch die Zeilen
//STRIP001      bRet = GetDoc()->DeleteRowCol( aBoxes );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001
//STRIP001  EndAllActionAndCall();
//STRIP001  return bRet;
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  MergeTab(), SplitTab()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/

//STRIP001 USHORT SwFEShell::MergeTab()
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  USHORT nRet = TBLMERGE_NOSELECTION;
//STRIP001  if( IsTableMode() )
//STRIP001  {
//STRIP001      SwShellTableCrsr* pTblCrsr = GetTableCrsr();
//STRIP001      const SwTableNode* pTblNd = pTblCrsr->GetNode()->FindTableNode();
//STRIP001      if( pTblNd->GetTable().ISA( SwDDETable ))
//STRIP001      {
//STRIP001          ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                          ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SET_CURR_SHELL( this );
//STRIP001          StartAllAction();
//STRIP001
//STRIP001          TblWait( pTblCrsr->GetBoxesCount(), 0, *GetDoc()->GetDocShell(),
//STRIP001                   pTblNd->GetTable().GetTabLines().Count() );
//STRIP001
//STRIP001          nRet = GetDoc()->MergeTbl( *pTblCrsr );
//STRIP001
//STRIP001          KillPams();
//STRIP001
//STRIP001          EndAllActionAndCall();
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::SplitTab( BOOL bVert, USHORT nCnt, BOOL bSameHeight )
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  if( bVert && !CheckSplitCells( *this, nCnt + 1 ) )
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLSPLIT_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  StartAllAction();
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  BOOL bRet;
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( *this, aBoxes );
//STRIP001  if( aBoxes.Count() )
//STRIP001  {
//STRIP001      TblWait( nCnt, pFrm, *GetDoc()->GetDocShell(), aBoxes.Count() );
//STRIP001
//STRIP001      // dann loesche doch die Spalten
//STRIP001         bRet = GetDoc()->SplitTbl( aBoxes, bVert, nCnt, bSameHeight );
//STRIP001
//STRIP001      DELETEZ( pLastCols );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001  EndAllActionAndCall();
//STRIP001  return bRet;
//STRIP001 }


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  _GetTabCols
#*  Datum      :  MA 30. Nov. 95
#*  Update     :  MA 08. Jan. 97
#***********************************************************************/
//STRIP001 void SwFEShell::_GetTabCols( SwTabCols &rToFill, const SwFrm *pBox ) const
//STRIP001 {
//STRIP001  const SwTabFrm *pTab = pBox->FindTabFrm();
//STRIP001  if ( pLastCols )
//STRIP001  {
//STRIP001      //Paar Kleinigkeiten muessen wir schon noch sicherstellen
//STRIP001      FASTBOOL bDel = TRUE;
//STRIP001      if ( pLastTable == pTab->GetTable() )
//STRIP001      {
//STRIP001          bDel = FALSE;
//STRIP001             SWRECTFN( pTab )
//STRIP001
//STRIP001             const SwPageFrm* pPage = pTab->FindPageFrm();
//STRIP001             const ULONG nLeftMin = (pTab->Frm().*fnRect->fnGetLeft)() -
//STRIP001                                    (pPage->Frm().*fnRect->fnGetLeft)() +
//STRIP001                                    DOCUMENTBORDER;
//STRIP001             const ULONG nRightMax = (pTab->Frm().*fnRect->fnGetRight)() -
//STRIP001                                     (pPage->Frm().*fnRect->fnGetLeft)() +
//STRIP001                                    DOCUMENTBORDER;
//STRIP001
//STRIP001             if ( pLastTabFrm != pTab )
//STRIP001          {
//STRIP001              //Wenn der TabFrm gewechselt hat, brauchen wir bei gleicher
//STRIP001              //Breite nur ein wenig shiften.
//STRIP001                 SWRECTFNX( pLastTabFrm )
//STRIP001                 if( (pLastTabFrm->Frm().*fnRect->fnGetWidth)() ==
//STRIP001                     (pTab->Frm().*fnRect->fnGetWidth)() )
//STRIP001              {
//STRIP001                     pLastCols->SetLeftMin( nLeftMin );
//STRIP001
//STRIP001                     ASSERT( bVert ||
//STRIP001                             pLastCols->GetLeftMin() == (pTab->Frm().*fnRect->fnGetLeft)(),
//STRIP001                             "GetTabCols: wrong result" )
//STRIP001
//STRIP001                  pLastTabFrm = pTab;
//STRIP001              }
//STRIP001              else
//STRIP001                  bDel = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          if ( !bDel &&
//STRIP001                  pLastCols->GetLeftMin () == (USHORT)nLeftMin &&
//STRIP001                  pLastCols->GetLeft    () == (USHORT)(pTab->Prt().*fnRect->fnGetLeft)() &&
//STRIP001                  pLastCols->GetRight   () == (USHORT)(pTab->Prt().*fnRect->fnGetRight)()&&
//STRIP001                  pLastCols->GetRightMax() == (USHORT)nRightMax - pLastCols->GetLeftMin() )
//STRIP001          {
//STRIP001              if ( pLastCellFrm != pBox )
//STRIP001              {
//STRIP001                  pTab->GetTable()->GetTabCols( *pLastCols,
//STRIP001                                      ((SwCellFrm*)pBox)->GetTabBox(), TRUE);
//STRIP001                  pLastCellFrm = pBox;
//STRIP001              }
//STRIP001              rToFill = *pLastCols;
//STRIP001          }
//STRIP001          else
//STRIP001              bDel = TRUE;
//STRIP001      }
//STRIP001      if ( bDel )
//STRIP001          DELETEZ(pLastCols);
//STRIP001  }
//STRIP001  if ( !pLastCols )
//STRIP001  {
//STRIP001      GetDoc()->GetTabCols( rToFill, 0, (SwCellFrm*)pBox );
//STRIP001
//STRIP001      pLastCols   = new SwTabCols( rToFill );
//STRIP001      pLastTable  = pTab->GetTable();
//STRIP001      pLastTabFrm = pTab;
//STRIP001      pLastCellFrm= pBox;
//STRIP001  }
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetTabCols(), GetTabCols()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 18. May. 93
#***********************************************************************/
//STRIP001 void SwFEShell::SetTabCols( const SwTabCols &rNew, BOOL bCurRowOnly )
//STRIP001 {
//STRIP001  SwFrm *pBox = GetCurrFrm();
//STRIP001  if( !pBox->IsInTab() )
//STRIP001      return;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  do {
//STRIP001      pBox = pBox->GetUpper();
//STRIP001  } while ( !pBox->IsCellFrm() );
//STRIP001
//STRIP001  GetDoc()->SetTabCols( rNew, bCurRowOnly, 0, (SwCellFrm*)pBox );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

//STRIP001 void SwFEShell::GetTabCols( SwTabCols &rToFill ) const
//STRIP001 {
//STRIP001  const SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return;
//STRIP001  do
//STRIP001  {   pFrm = pFrm->GetUpper();
//STRIP001  } while ( !pFrm->IsCellFrm() );
//STRIP001
//STRIP001  _GetTabCols( rToFill, pFrm );
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetRowHeight(), GetRowHeight()
#*  Datum      :  MA 17. May. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/

//STRIP001 void SwFEShell::SetRowHeight( const SwFmtFrmSize &rNew )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetRowHeight( GetShellCursor( *this ), rNew );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

/******************************************************************************
 *               SwTwips SwFEShell::GetRowHeight() const
 ******************************************************************************/
//STRIP001 void SwFEShell::GetRowHeight( SwFmtFrmSize *& rpSz ) const
//STRIP001 {
//STRIP001  GetDoc()->GetRowHeight( GetShellCursor( *this ), rpSz );
//STRIP001 }

/*N*/ BOOL SwFEShell::BalanceRowHeight( BOOL bTstOnly )
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   if( !bTstOnly )
/*?*/       StartAllAction();
/*N*/   BOOL bRet = GetDoc()->BalanceRowHeight( GetShellCursor( *this ), bTstOnly );
/*N*/   if( !bTstOnly )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    EndAllActionAndCall();
/*N*/   return bRet;
/*N*/ }

/******************************************************************************
 *              void SwFEShell::SetRowBackground()
 ******************************************************************************/
//STRIP001 void SwFEShell::SetRowBackground( const SvxBrushItem &rNew )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetRowBackground( GetShellCursor( *this ), rNew );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

/******************************************************************************
 *               SwTwips SwFEShell::GetRowBackground() const
 ******************************************************************************/
//STRIP001 BOOL SwFEShell::GetRowBackground( SvxBrushItem &rToFill ) const
//STRIP001 {
//STRIP001  return GetDoc()->GetRowBackground( GetShellCursor( *this ), rToFill );
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetTabBorders(), GetTabBorders()
#*  Datum      :  MA 18. May. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/

//STRIP001 void SwFEShell::SetTabBorders( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetTabBorders( GetShellCursor( *this ), rSet );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

//STRIP001 void SwFEShell::SetTabLineStyle( const Color* pColor, BOOL bSetLine,
//STRIP001                               const SvxBorderLine* pBorderLine )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetTabLineStyle( GetShellCursor( *this ),
//STRIP001                              pColor, bSetLine, pBorderLine );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

/*N*/ void SwFEShell::GetTabBorders( SfxItemSet& rSet ) const
/*N*/ {
/*N*/   GetDoc()->GetTabBorders( GetShellCursor( *this ), rSet );
/*N*/ }


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetBoxBackground(), GetBoxBackground()
#*  Datum      :  MA 01. Jun. 93
#*  Update     :  MA 03. Jul. 96
#***********************************************************************/
//STRIP001 void SwFEShell::SetBoxBackground( const SvxBrushItem &rNew )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetBoxAttr( GetShellCursor( *this ), rNew );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

//STRIP001 BOOL SwFEShell::GetBoxBackground( SvxBrushItem &rToFill ) const
//STRIP001 {
//STRIP001  return GetDoc()->GetBoxBackground( GetShellCursor( *this ), rToFill );
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetBoxAlign, SetBoxAlign
#*  Datum      :  MA 18. Dec. 96
#*  Update     :  JP 29.04.98
#***********************************************************************/
//STRIP001 void SwFEShell::SetBoxAlign( USHORT nAlign )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetBoxAlign( GetShellCursor( *this ), nAlign );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

/*N*/ USHORT SwFEShell::GetBoxAlign() const
/*N*/ {
/*N*/   return GetDoc()->GetBoxAlign( GetShellCursor( *this ) );
/*N*/ }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetTabBackground(), GetTabBackground()
#*  Datum      :  MA 08. Jul. 96
#*  Update     :  MA 08. Jul. 96
#***********************************************************************/
//STRIP001 void SwFEShell::SetTabBackground( const SvxBrushItem &rNew )
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetAttr( rNew, *pFrm->ImplFindTabFrm()->GetFmt() );
//STRIP001  EndAllAction(); //Kein Call, denn es veraendert sich nichts!
//STRIP001  GetDoc()->SetModified();
//STRIP001 }

//STRIP001 void SwFEShell::GetTabBackground( SvxBrushItem &rToFill ) const
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( pFrm->IsInTab() )
//STRIP001      rToFill = pFrm->ImplFindTabFrm()->GetFmt()->GetBackground();
//STRIP001 }


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  HasWholeTabSelection()
#*  Datum      :  MA 18. May. 93
#*  Update     :  MA 20. Jul. 93
#***********************************************************************/
//STRIP001 BOOL SwFEShell::HasWholeTabSelection() const
//STRIP001 {
//STRIP001  //Ist die ganze Tabelle Selektiert?
//STRIP001  if ( IsTableMode() )
//STRIP001  {
//STRIP001      SwSelBoxes aBoxes;
//STRIP001      ::GetTblSelCrs( *this, aBoxes );
//STRIP001      if( aBoxes.Count() )
//STRIP001      {
//STRIP001          const SwTableNode *pTblNd = IsCrsrInTbl();
//STRIP001          return ( aBoxes[0]->GetSttIdx()-1 == pTblNd->
//STRIP001              EndOfSectionNode()->StartOfSectionIndex() &&
//STRIP001              aBoxes[aBoxes.Count()-1]->GetSttNd()->EndOfSectionIndex()+1
//STRIP001              ==  pTblNd->EndOfSectionIndex() );
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL SwFEShell::HasBoxSelection() const
//STRIP001 {
//STRIP001  if(!IsCrsrInTbl())
//STRIP001      return FALSE;
//STRIP001  //Ist die ganze Tabelle Selektiert?
//STRIP001  if( IsTableMode() )
//STRIP001      return TRUE;
//STRIP001  SwPaM* pPam = GetCrsr();
//STRIP001      // leere Boxen gelten auch ohne Selektion als selektiert
//STRIP001 //   if( !pPam->HasMark() )
//STRIP001 //       return FALSE;
//STRIP001  BOOL bChg = FALSE;
//STRIP001  if( pPam->GetPoint() == pPam->End())
//STRIP001  {
//STRIP001      bChg = TRUE;
//STRIP001      pPam->Exchange();
//STRIP001  }
//STRIP001  SwNode* pNd;
//STRIP001  if( pPam->GetPoint()->nNode.GetIndex() -1 ==
//STRIP001      ( pNd = pPam->GetNode())->StartOfSectionIndex() &&
//STRIP001      !pPam->GetPoint()->nContent.GetIndex() &&
//STRIP001      pPam->GetMark()->nNode.GetIndex() + 1 ==
//STRIP001      pNd->EndOfSectionIndex())
//STRIP001  {
//STRIP001          SwNodeIndex aIdx( *pNd->EndOfSectionNode(), -1 );
//STRIP001          SwCntntNode* pCNd = GetDoc()->GetNodes()[ aIdx ]->GetCntntNode();
//STRIP001          if( !pCNd )
//STRIP001          {
//STRIP001              pCNd = GetDoc()->GetNodes().GoPrevious( &aIdx );
//STRIP001              ASSERT( pCNd, "kein ContentNode in der Box ??" );
//STRIP001          }
//STRIP001          if( pPam->GetMark()->nContent == pCNd->Len() )
//STRIP001          {
//STRIP001              if( bChg )
//STRIP001                  pPam->Exchange();
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001  }
//STRIP001  if( bChg )
//STRIP001      pPam->Exchange();
//STRIP001  return FALSE;
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  ProtectCells(), UnProtectCells()
#*  Datum      :  MA 20. Jul. 93
#*  Update     :  JP 25. Sep. 93
#***********************************************************************/
//STRIP001 void SwFEShell::ProtectCells()
//STRIP001 {
//STRIP001  SvxProtectItem aProt;
//STRIP001  aProt.SetCntntProtect( TRUE );
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  GetDoc()->SetBoxAttr( GetShellCursor( *this ), aProt );
//STRIP001
//STRIP001  if( !IsCrsrReadonly() )
//STRIP001  {
//STRIP001      if( IsTableMode() )
//STRIP001          ClearMark();
//STRIP001      ParkCursorInTab();
//STRIP001  }
//STRIP001  EndAllActionAndCall();
//STRIP001 }

//STRIP001 void SwFEShell::UnProtectCells( const String& rTblName )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->UnProtectCells( rTblName );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

// die Tabellenselektion aufheben
//STRIP001 void SwFEShell::UnProtectCells()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  if( IsTableMode() )
//STRIP001      ::GetTblSelCrs( *this, aBoxes );
//STRIP001  else
//STRIP001  {
//STRIP001      SwFrm *pFrm = GetCurrFrm();
//STRIP001      do {
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      } while ( pFrm && !pFrm->IsCellFrm() );
//STRIP001      if( pFrm )
//STRIP001      {
//STRIP001          SwTableBox *pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
//STRIP001          aBoxes.Insert( pBox );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( aBoxes.Count() )
//STRIP001      GetDoc()->UnProtectCells( aBoxes );
//STRIP001
//STRIP001  EndAllActionAndCall();
//STRIP001 }

//STRIP001 void SwFEShell::UnProtectTbls()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->UnProtectTbls( *GetCrsr() );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

//STRIP001 BOOL SwFEShell::HasTblAnyProtection( const String* pTblName,
//STRIP001                                  BOOL* pFullTblProtection )
//STRIP001 {
//STRIP001  return GetDoc()->HasTblAnyProtection( GetCrsr()->GetPoint(), pTblName,
//STRIP001                                      pFullTblProtection );
//STRIP001 }

//STRIP001 BOOL SwFEShell::CanUnProtectCells() const
//STRIP001 {
//STRIP001  BOOL bUnProtectAvailable = FALSE;
//STRIP001  const SwTableNode *pTblNd = IsCrsrInTbl();
//STRIP001  if( pTblNd && !pTblNd->IsProtect() )
//STRIP001  {
//STRIP001      SwSelBoxes aBoxes;
//STRIP001      if( IsTableMode() )
//STRIP001          ::GetTblSelCrs( *this, aBoxes );
//STRIP001      else
//STRIP001      {
//STRIP001          SwFrm *pFrm = GetCurrFrm();
//STRIP001          do {
//STRIP001              pFrm = pFrm->GetUpper();
//STRIP001          } while ( pFrm && !pFrm->IsCellFrm() );
//STRIP001          if( pFrm )
//STRIP001          {
//STRIP001              SwTableBox *pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
//STRIP001              aBoxes.Insert( pBox );
//STRIP001          }
//STRIP001      }
//STRIP001      if( aBoxes.Count() )
//STRIP001          bUnProtectAvailable = ::HasProtectedCells( aBoxes );
//STRIP001  }
//STRIP001  return bUnProtectAvailable;
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  IsHeadlineRepeat(), SetHeadlineRepeat()
#*  Datum      :  MA 02. Feb. 94
#*  Update     :  MA 27. Jul. 95
#***********************************************************************/
//STRIP001 BOOL SwFEShell::IsHeadlineRepeat() const
//STRIP001 {
//STRIP001  const SwFrm *pFrm = GetCurrFrm();
//STRIP001  const SwTabFrm *pTab = pFrm->FindTabFrm();
//STRIP001  if( pTab )
//STRIP001      return pTab->GetTable()->IsHeadlineRepeat();
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SwFEShell::SetHeadlineRepeat( BOOL bSet )
//STRIP001 {
//STRIP001  SwFrm    *pFrm = GetCurrFrm();
//STRIP001  SwTabFrm *pTab = pFrm->FindTabFrm();
//STRIP001  if( pTab && pTab->GetTable()->IsHeadlineRepeat() != bSet )
//STRIP001  {
//STRIP001      SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      StartAllAction();
//STRIP001      GetDoc()->SetHeadlineRepeat( *pTab->GetTable(), bSet );
//STRIP001      EndAllActionAndCall();
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwFEShell::IsInHeadline() const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if ( !IsTableMode() )
//STRIP001  {
//STRIP001      SwFrm *pFrm = GetCurrFrm();
//STRIP001      if ( pFrm->IsInTab() && ((SwLayoutFrm*)pFrm->FindTabFrm()->Lower())->IsAnLower( pFrm))
//STRIP001          bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL SwFEShell::IsInRepeatedHeadline() const
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   if ( !IsTableMode() )
/*N*/   {
/*N*/       SwFrm *pFrm = GetCurrFrm();
/*N*/       if ( pFrm->IsInTab() )
/*N*/       {
/*N*/           SwTabFrm *pTab = pFrm->FindTabFrm();
/*N*/           if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() &&
/*N*/                ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pFrm ) )
/*N*/           {
/*?*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  AdjustCellWidth()
#*  Datum      :  MA 20. Feb. 95
#*  Update     :  MA 27. Jul. 95
#***********************************************************************/

//STRIP001 void SwFEShell::AdjustCellWidth( BOOL bBalance )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  //WarteCrsr immer einschalten, weil sich im vorraus nicht so recht
//STRIP001  //ermitteln laesst wieviel Inhalt betroffen ist.
//STRIP001  TblWait aWait( USHRT_MAX, 0, *GetDoc()->GetDocShell() );
//STRIP001
//STRIP001  GetDoc()->AdjustCellWidth( GetShellCursor( *this ), bBalance );
//STRIP001  EndAllActionAndCall();
//STRIP001 }

/*N*/ BOOL SwFEShell::IsAdjustCellWidthAllowed( BOOL bBalance ) const
/*N*/ {
/*N*/   //Es muss mindestens eine Zelle mit Inhalt in der Selektion enthalten
/*N*/   //sein.
/*N*/
/*N*/   SwFrm *pFrm = GetCurrFrm();
/*N*/   if( !pFrm->IsInTab() )
/*?*/       return FALSE;
/*N*/
/*N*/   SwSelBoxes aBoxes;
/*N*/   ::GetTblSelCrs( *this, aBoxes );
/*N*/
/*N*/   if ( bBalance )
/*N*/       return aBoxes.Count() > 1;
/*N*/
/*N*/   if ( !aBoxes.Count() )
/*N*/   {
/*N*/       do
/*N*/       {   pFrm = pFrm->GetUpper();
/*N*/       } while ( !pFrm->IsCellFrm() );
/*N*/       SwTableBox *pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
/*N*/       aBoxes.Insert( pBox );
/*N*/   }
/*N*/
/*N*/   for ( USHORT i = 0; i < aBoxes.Count(); ++i )
/*N*/   {
/*N*/       SwTableBox *pBox = aBoxes[i];
/*N*/       if ( pBox->GetSttNd() )
/*N*/       {
/*N*/           SwNodeIndex aIdx( *pBox->GetSttNd(), 1 );
/*N*/           SwTxtNode* pCNd = aIdx.GetNode().GetTxtNode();
/*N*/           if( !pCNd )
/*?*/               pCNd = (SwTxtNode*)GetDoc()->GetNodes().GoNext( &aIdx );
/*N*/
/*N*/           while ( pCNd )
/*N*/           {
/*N*/               if ( pCNd->GetTxt().Len() )
/*N*/                   return TRUE;
/*N*/               ++aIdx;
/*N*/               pCNd = GetDoc()->GetNodes()[ aIdx ]->GetTxtNode();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

    // AutoFormat fuer die Tabelle/TabellenSelection
//STRIP001 BOOL SwFEShell::SetTableAutoFmt( const SwTableAutoFmt& rNew )
//STRIP001 {
//STRIP001  SwTableNode *pTblNd = (SwTableNode*)IsCrsrInTbl();
//STRIP001  if( !pTblNd || pTblNd->GetTable().IsTblComplex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwSelBoxes aBoxes;
//STRIP001
//STRIP001  if ( !IsTableMode() )       // falls Crsr noch nicht akt. sind
//STRIP001      GetCrsr();
//STRIP001
//STRIP001  // gesamte Tabelle oder nur auf die akt. Selektion
//STRIP001  if( IsTableMode() )
//STRIP001      ::GetTblSelCrs( *this, aBoxes );
//STRIP001  else
//STRIP001  {
//STRIP001      const SwTableSortBoxes& rTBoxes = pTblNd->GetTable().GetTabSortBoxes();
//STRIP001      for( USHORT n = 0; n < rTBoxes.Count(); ++n )
//STRIP001      {
//STRIP001          SwTableBox* pBox = rTBoxes[ n ];
//STRIP001          aBoxes.Insert( pBox );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet;
//STRIP001  if( aBoxes.Count() )
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      StartAllAction();
//STRIP001      bRet = GetDoc()->SetTableAutoFmt( aBoxes, rNew );
//STRIP001      DELETEZ( pLastCols );
//STRIP001      EndAllActionAndCall();
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::GetTableAutoFmt( SwTableAutoFmt& rGet )
//STRIP001 {
//STRIP001  const SwTableNode *pTblNd = IsCrsrInTbl();
//STRIP001  if( !pTblNd || pTblNd->GetTable().IsTblComplex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwSelBoxes aBoxes;
//STRIP001
//STRIP001  if ( !IsTableMode() )       // falls Crsr noch nicht akt. sind
//STRIP001      GetCrsr();
//STRIP001
//STRIP001  // gesamte Tabelle oder nur auf die akt. Selektion
//STRIP001  if( IsTableMode() )
//STRIP001      ::GetTblSelCrs( *this, aBoxes );
//STRIP001  else
//STRIP001  {
//STRIP001      const SwTableSortBoxes& rTBoxes = pTblNd->GetTable().GetTabSortBoxes();
//STRIP001      for( USHORT n = 0; n < rTBoxes.Count(); ++n )
//STRIP001      {
//STRIP001          SwTableBox* pBox = rTBoxes[ n ];
//STRIP001          aBoxes.Insert( pBox );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return GetDoc()->GetTableAutoFmt( aBoxes, rGet );
//STRIP001 }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  DeleteTblSel()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/
//STRIP001 BOOL SwFEShell::DeleteTblSel()
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  BOOL bRet;
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSelCrs( *this, aBoxes );
//STRIP001  if( aBoxes.Count() )
//STRIP001  {
//STRIP001      TblWait( aBoxes.Count(), pFrm, *GetDoc()->GetDocShell() );
//STRIP001
//STRIP001      // die Crsr muessen noch aus dem Loesch Bereich entfernt
//STRIP001      // werden. Setze sie immer hinter/auf die Tabelle; ueber die
//STRIP001      // Dokument-Position werden sie dann immer an die alte Position gesetzt.
//STRIP001      while( !pFrm->IsCellFrm() )
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      ParkCrsr( SwNodeIndex( *((SwCellFrm*)pFrm)->GetTabBox()->GetSttNd() ));
//STRIP001
//STRIP001      bRet = GetDoc()->DeleteRowCol( aBoxes );
//STRIP001
//STRIP001      DELETEZ( pLastCols );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001  EndAllActionAndCall();
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetCurTabColNum()
|*
|*  Ersterstellung      MA 03. Feb. 95
|*  Letzte Aenderung    MA 21. May. 95
|
|*************************************************************************/
//STRIP001 USHORT SwFEShell::GetCurTabColNum() const
//STRIP001 {
//STRIP001  //!!!GetCurMouseTabColNum() mitpflegen!!!!
//STRIP001  USHORT nRet = 0;
//STRIP001
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  ASSERT( pFrm, "Crsr geparkt?" );
//STRIP001
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  if( pFrm->IsInTab() )
//STRIP001  {
//STRIP001      do {            // JP 26.09.95: warum mit dem CntntFrame und nicht mit
//STRIP001                      //              dem CellFrame vergleichen????
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      } while ( !pFrm->IsCellFrm() );
//STRIP001         SWRECTFN( pFrm )
//STRIP001         const long nX = (pFrm->Frm().*fnRect->fnGetLeft)();
//STRIP001
//STRIP001      //TabCols besorgen, den nur ueber diese erreichen wir die Position.
//STRIP001      SwTabCols aTabCols;
//STRIP001      GetTabCols( aTabCols );
//STRIP001
//STRIP001         if( pFrm->FindTabFrm()->IsRightToLeft() )
//STRIP001      {
//STRIP001          long nX = (pFrm->Frm().*fnRect->fnGetRight)();
//STRIP001          const long nRight = aTabCols.GetLeftMin() + aTabCols.GetRight();;
//STRIP001
//STRIP001          if ( !::IsSame( nX, nRight ) )
//STRIP001          {
//STRIP001              nX = nRight - nX + aTabCols.GetLeft();
//STRIP001              for ( USHORT i = 0; i < aTabCols.Count(); ++i )
//STRIP001                  if ( ::IsSame( nX, aTabCols[i] ) )
//STRIP001                  {
//STRIP001                      nRet = i + 1;
//STRIP001                      break;
//STRIP001                  }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          const long nX = (pFrm->Frm().*fnRect->fnGetLeft)();
//STRIP001          const long nLeft = aTabCols.GetLeftMin();
//STRIP001
//STRIP001          if ( !::IsSame( nX, nLeft + aTabCols.GetLeft() ) )
//STRIP001          {
//STRIP001              for ( USHORT i = 0; i < aTabCols.Count(); ++i )
//STRIP001                  if ( ::IsSame( nX, nLeft + aTabCols[i] ) )
//STRIP001                  {
//STRIP001                      nRet = i + 1;
//STRIP001                      break;
//STRIP001                  }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetBox()
|*
|*  Ersterstellung      MA 22. Jun. 95
|*  Letzte Aenderung    MA 21. Nov. 96
|*
|*************************************************************************/

//STRIP001 const SwFrm *lcl_FindFrmInTab( const SwLayoutFrm *pLay, const Point &rPt, SwTwips nFuzzy )
//STRIP001 {
//STRIP001  const SwFrm *pFrm = pLay->Lower();
//STRIP001  do
//STRIP001  {   if ( pFrm->Frm().IsNear( rPt, nFuzzy ) )
//STRIP001      {
//STRIP001          if ( pFrm->IsCellFrm() && ( !((SwCellFrm*)pFrm)->Lower()->IsLayoutFrm() ||
//STRIP001              ((SwCellFrm*)pFrm)->Lower()->IsSctFrm() ) )
//STRIP001              return pFrm;
//STRIP001          if ( pFrm->IsLayoutFrm() )
//STRIP001          {
//STRIP001              const SwFrm *pTmp = ::lcl_FindFrmInTab( (SwLayoutFrm*)pFrm, rPt, nFuzzy);
//STRIP001              if ( pTmp )
//STRIP001                  return pTmp;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      pFrm = pFrm->FindNext();
//STRIP001  } while ( pFrm && pLay->IsAnLower( pFrm ) );
//STRIP001
//STRIP001  return 0;
//STRIP001 }

//STRIP001 const SwFrm *lcl_FindFrm( const SwLayoutFrm *pLay, const Point &rPt, SwTwips nFuzzy )
//STRIP001 {
//STRIP001  const SwFrm *pFrm = pLay->ContainsCntnt();
//STRIP001  if ( pFrm )
//STRIP001  {
//STRIP001      do
//STRIP001      {
//STRIP001          if ( pFrm->IsInTab() )
//STRIP001              pFrm = ((SwFrm*)pFrm)->ImplFindTabFrm();
//STRIP001          if ( pFrm->IsTabFrm() )
//STRIP001          {
//STRIP001              const SwFrm *pTmp = ::lcl_FindFrmInTab( (SwLayoutFrm*)pFrm, rPt, nFuzzy );
//STRIP001              if ( pTmp )
//STRIP001              {
//STRIP001                  pFrm = pTmp;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001          pFrm = pFrm->FindNextCnt();
//STRIP001
//STRIP001      } while ( pFrm && pLay->IsAnLower( pFrm ) );
//STRIP001  }
//STRIP001  if ( pFrm && pFrm->IsInTab() && pLay->IsAnLower( pFrm ) )
//STRIP001  {
//STRIP001      do
//STRIP001      {   while ( pFrm && !pFrm->IsCellFrm() )
//STRIP001              pFrm = pFrm->GetUpper();
//STRIP001          if ( pFrm )
//STRIP001          {
//STRIP001                 if( pFrm->IsVertical() )
//STRIP001                 {
//STRIP001                     if ( ::IsSame(pFrm->Frm().Top(), rPt.Y()) ||
//STRIP001                          ::IsSame(pFrm->Frm().Bottom(),rPt.Y()) )
//STRIP001                         return pFrm;
//STRIP001              }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if ( ::IsSame(pFrm->Frm().Left(), rPt.X()) ||
//STRIP001                          ::IsSame(pFrm->Frm().Right(),rPt.X()) )
//STRIP001                         return pFrm;
//STRIP001              }
//STRIP001              pFrm = pFrm->GetUpper();
//STRIP001          }
//STRIP001      } while ( pFrm );
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 const SwFrm *SwFEShell::GetBox( const Point &rPt ) const
//STRIP001 {
//STRIP001  const SwPageFrm *pPage = (SwPageFrm*)GetLayout()->Lower();
//STRIP001  Window* pOutWin = GetWin();
//STRIP001  SwTwips nFuzzy = COLFUZZY;
//STRIP001  if(pOutWin)
//STRIP001  {
//STRIP001      Size aTmp(RULER_MOUSE_MARGINWIDTH, RULER_MOUSE_MARGINWIDTH);
//STRIP001      aTmp = pOutWin->PixelToLogic(aTmp);
//STRIP001      nFuzzy = aTmp.Width();
//STRIP001  }
//STRIP001  while ( pPage && !pPage->Frm().IsNear( rPt, nFuzzy ) )
//STRIP001      pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001
//STRIP001  const SwFrm *pFrm = 0;
//STRIP001  if ( pPage )
//STRIP001  {
//STRIP001      //Per GetCrsrOfst oder GetCntntPos koennen wir hier die Box leider
//STRIP001      //nicht suchen. Das wuerde zu einem Performance-Zusammenbruch bei
//STRIP001      //Dokumenten mit vielen Absaetzen/Tabellen auf einer Seite fuehren
//STRIP001      //(BrowseMode!)
//STRIP001
//STRIP001      //Erst die Flys checken.
//STRIP001      if ( pPage->GetSortedObjs() )
//STRIP001      {
//STRIP001          for ( USHORT i = 0; !pFrm && i < pPage->GetSortedObjs()->Count(); ++i )
//STRIP001          {
//STRIP001              const SdrObject *pObj = (*pPage->GetSortedObjs())[i];
//STRIP001              if ( pObj->IsWriterFlyFrame() )
//STRIP001              {
//STRIP001                  pFrm = lcl_FindFrm( ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm(),
//STRIP001                                      rPt, nFuzzy );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      const SwLayoutFrm *pLay = (SwLayoutFrm*)pPage->Lower();
//STRIP001      while ( pLay && !pFrm )
//STRIP001      {
//STRIP001          pFrm = lcl_FindFrm( pLay, rPt, nFuzzy );
//STRIP001          pLay = (SwLayoutFrm*)pLay->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001  return pFrm;
//STRIP001 }


/*************************************************************************
|*
|*  SwFEShell::WhichMouseTabCol()
|*
|*  Ersterstellung      MA 22. Jun. 95
|*  Last change         AMA 12. Jun. 02
|
|*************************************************************************/
//STRIP001 BYTE SwFEShell::WhichMouseTabCol( const Point &rPt ) const
//STRIP001 {
//STRIP001  SwCellFrm* pFrm = (SwCellFrm*)GetBox( rPt );
//STRIP001  if( pFrm )
//STRIP001  {
//STRIP001      while( pFrm->Lower()->IsRowFrm() )
//STRIP001          pFrm = (SwCellFrm*)((SwLayoutFrm*)pFrm->Lower())->Lower();
//STRIP001      if( pFrm && pFrm->GetTabBox()->GetSttNd() &&
//STRIP001          pFrm->GetTabBox()->GetSttNd()->IsInProtectSect() )
//STRIP001          pFrm = 0;
//STRIP001  }
//STRIP001     if( pFrm )
//STRIP001         return pFrm->IsVertical() ? SW_TABCOL_VERT : SW_TABCOL_HORI;
//STRIP001     return SW_TABCOL_NONE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetMouseTabCols()
|*
|*  Ersterstellung      MA 22. Jun. 95
|*  Letzte Aenderung    MA 27. Aug. 96
|
|*************************************************************************/
//STRIP001 void SwFEShell::GetMouseTabCols( SwTabCols &rToFill, const Point &rPt ) const
//STRIP001 {
//STRIP001  const SwFrm *pBox = GetBox( rPt );
//STRIP001  if ( pBox )
//STRIP001      _GetTabCols( rToFill, pBox );
//STRIP001 }

//STRIP001 void SwFEShell::SetMouseTabCols( const SwTabCols &rNew, BOOL bCurRowOnly,
//STRIP001                               const Point &rPt )
//STRIP001 {
//STRIP001  const SwFrm *pBox = GetBox( rPt );
//STRIP001  if( pBox )
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      StartAllAction();
//STRIP001      GetDoc()->SetTabCols( rNew, bCurRowOnly, 0, (SwCellFrm*)pBox );
//STRIP001      EndAllActionAndCall();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetMouseColNum(), GetMouseTabColNum()
|*
|*  Ersterstellung      MA 04. Jul. 95
|*  Letzte Aenderung    MA 04. Jul. 95
|
|*************************************************************************/
//STRIP001 USHORT SwFEShell::GetCurMouseColNum( const Point &rPt,
//STRIP001                                  SwGetCurColNumPara* pPara ) const
//STRIP001 {
//STRIP001  return _GetCurColNum( GetBox( rPt ), pPara );
//STRIP001 }

//STRIP001 USHORT SwFEShell::GetCurMouseTabColNum( const Point &rPt ) const
//STRIP001 {
//STRIP001  //!!!GetCurTabColNum() mitpflegen!!!!
//STRIP001  USHORT nRet = 0;
//STRIP001
//STRIP001  const SwFrm *pFrm = GetBox( rPt );
//STRIP001  ASSERT( pFrm, "Table not found" );
//STRIP001  if( pFrm )
//STRIP001  {
//STRIP001      const long nX = pFrm->Frm().Left();
//STRIP001
//STRIP001      //TabCols besorgen, den nur ueber diese erreichen wir die Position.
//STRIP001      SwTabCols aTabCols;
//STRIP001      GetMouseTabCols( aTabCols, rPt );
//STRIP001
//STRIP001      const long nLeft = aTabCols.GetLeftMin();
//STRIP001
//STRIP001      if ( !::IsSame( nX, nLeft + aTabCols.GetLeft() ) )
//STRIP001      {
//STRIP001          for ( USHORT i = 0; i < aTabCols.Count(); ++i )
//STRIP001              if ( ::IsSame( nX, nLeft + aTabCols[i] ) )
//STRIP001              {
//STRIP001                  nRet = i + 1;
//STRIP001                  break;
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/*N*/ void ClearFEShellTabCols()
/*N*/ {
/*N*/   DELETEZ( pLastCols );
/*N*/ }

/*************************************************************************
|*
|*  SwFEShell::GetTblAttr(), SetTblAttr()
|*
|*  Ersterstellung      MA 09. Dec. 96
|*  Letzte Aenderung    MA 09. Dec. 96
|
|*************************************************************************/
//STRIP001 void SwFEShell::GetTblAttr( SfxItemSet &rSet ) const
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( pFrm->IsInTab() )
//STRIP001      rSet.Put( pFrm->ImplFindTabFrm()->GetFmt()->GetAttrSet() );
//STRIP001 }

//STRIP001 void SwFEShell::SetTblAttr( const SfxItemSet &rNew )
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( pFrm->IsInTab() )
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      StartAllAction();
//STRIP001      SwTabFrm *pTab = pFrm->FindTabFrm();
//STRIP001      pTab->GetTable()->SetHTMLTableLayout( 0 );
//STRIP001      GetDoc()->SetAttr( rNew, *pTab->GetFmt() );
//STRIP001      GetDoc()->SetModified();
//STRIP001      EndAllActionAndCall();
//STRIP001  }
//STRIP001 }

/** move cursor within a table into previous/next row (same column)
 * @param pShell cursor shell whose cursor is to be moved
 * @param bUp true: move up, false: move down
 * @returns true if successful
 */
//STRIP001 bool lcl_GoTableRow( SwCrsrShell* pShell, bool bUp )
//STRIP001 {
//STRIP001     ASSERT( pShell != NULL, "need shell" );
//STRIP001
//STRIP001     bool bRet = false;
//STRIP001
//STRIP001     SwPaM* pPam = pShell->GetCrsr();
//STRIP001     const SwStartNode* pTableBox = pPam->GetNode()->FindTableBoxStartNode();
//STRIP001     ASSERT( pTableBox != NULL, "I'm living in a box... NOT!" );
//STRIP001
//STRIP001     // move cursor to start node of table box
//STRIP001     pPam->GetPoint()->nNode = pTableBox->GetIndex();
//STRIP001     pPam->GetPoint()->nContent.Assign( NULL, 0 );
//STRIP001     GoInCntnt( *pPam, fnMoveForward );
//STRIP001
//STRIP001     // go to beginning end of table box
//STRIP001     SwPosSection fnPosSect = bUp ? fnSectionStart : fnSectionEnd;
//STRIP001     pShell->MoveSection( fnSectionCurr, fnPosSect );
//STRIP001
//STRIP001     // and go up/down into next content
//STRIP001     bRet = bUp ? pShell->Up() : pShell->Down();
//STRIP001
//STRIP001     return bRet;
//STRIP001 }

    // aender eine  Zellenbreite/-Hoehe/Spaltenbreite/Zeilenhoehe
//STRIP001 BOOL SwFEShell::SetColRowWidthHeight( USHORT eType, USHORT nDiff )
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if( !pFrm->IsInTab() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( WH_FLAG_INSDEL & eType &&
//STRIP001      pFrm->ImplFindTabFrm()->GetTable()->ISA( SwDDETable ))
//STRIP001  {
//STRIP001      ErrorHandler::HandleError( ERR_TBLDDECHG_ERROR,
//STRIP001                      ERRCODE_MSG_INFO | ERRCODE_BUTTON_DEF_OK );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  do {
//STRIP001      pFrm = pFrm->GetUpper();
//STRIP001  } while( !pFrm->IsCellFrm() );
//STRIP001
//STRIP001  SwTabFrm *pTab = pFrm->ImplFindTabFrm();
//STRIP001
//STRIP001  // sollte die Tabelle noch auf relativen Werten (USHRT_MAX) stehen
//STRIP001  // dann muss es jetzt auf absolute umgerechnet werden.
//STRIP001  const SwFmtFrmSize& rTblFrmSz = pTab->GetFmt()->GetFrmSize();
//STRIP001     SWRECTFN( pTab )
//STRIP001     long nPrtWidth = (pTab->Prt().*fnRect->fnGetWidth)();
//STRIP001  if( TBLVAR_CHGABS == pTab->GetTable()->GetTblChgMode() &&
//STRIP001      ( eType & WH_COL_LEFT || eType & WH_COL_RIGHT ) &&
//STRIP001         HORI_NONE == pTab->GetFmt()->GetHoriOrient().GetHoriOrient() &&
//STRIP001         nPrtWidth != rTblFrmSz.GetWidth() )
//STRIP001     {
//STRIP001         SwFmtFrmSize aSz( rTblFrmSz );
//STRIP001         aSz.SetWidth( pTab->Prt().Width() );
//STRIP001         pTab->GetFmt()->SetAttr( aSz );
//STRIP001  }
//STRIP001
//STRIP001  if( (eType & (WH_FLAG_BIGGER | WH_FLAG_INSDEL)) ==
//STRIP001      (WH_FLAG_BIGGER | WH_FLAG_INSDEL) )
//STRIP001     {
//STRIP001         nDiff = USHORT((pFrm->Frm().*fnRect->fnGetWidth)());
//STRIP001
//STRIP001         // we must move the cursor outside the current cell before
//STRIP001         // deleting the cells.
//STRIP001         TblChgWidthHeightType eTmp =
//STRIP001             static_cast<TblChgWidthHeightType>( eType & 0xfff );
//STRIP001         switch( eTmp )
//STRIP001         {
//STRIP001         case WH_ROW_TOP:
//STRIP001             lcl_GoTableRow( this, true );
//STRIP001             break;
//STRIP001         case WH_ROW_BOTTOM:
//STRIP001             lcl_GoTableRow( this, false );
//STRIP001             break;
//STRIP001         case WH_COL_LEFT:
//STRIP001             GoPrevCell();
//STRIP001             break;
//STRIP001         case WH_COL_RIGHT:
//STRIP001             GoNextCell();
//STRIP001             break;
//STRIP001         default:
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  SwTwips nLogDiff = nDiff;
//STRIP001  nLogDiff *= pTab->GetFmt()->GetFrmSize().GetWidth();
//STRIP001     nLogDiff /= nPrtWidth;
//STRIP001
//STRIP001     /** The cells are destroyed in here */
//STRIP001  BOOL bRet = GetDoc()->SetColRowWidthHeight(
//STRIP001                  *(SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox(),
//STRIP001                  eType, nDiff, nLogDiff );
//STRIP001
//STRIP001  delete pLastCols, pLastCols = 0;
//STRIP001  EndAllActionAndCall();
//STRIP001
//STRIP001  if( bRet && (eType & (WH_FLAG_BIGGER | WH_FLAG_INSDEL)) == WH_FLAG_INSDEL )
//STRIP001  {
//STRIP001      switch(eType & ~(WH_FLAG_BIGGER | WH_FLAG_INSDEL))
//STRIP001      {
//STRIP001      case WH_CELL_LEFT:
//STRIP001      case WH_COL_LEFT:
//STRIP001              GoPrevCell();
//STRIP001              break;
//STRIP001
//STRIP001      case WH_CELL_RIGHT:
//STRIP001      case WH_COL_RIGHT:
//STRIP001              GoNextCell();
//STRIP001              break;
//STRIP001
//STRIP001      case WH_CELL_TOP:
//STRIP001      case WH_ROW_TOP:
//STRIP001                 lcl_GoTableRow( this, true );
//STRIP001              break;
//STRIP001
//STRIP001      case WH_CELL_BOTTOM:
//STRIP001      case WH_ROW_BOTTOM:
//STRIP001                 lcl_GoTableRow( this, false );
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_IsFormulaSelBoxes( const SwTable& rTbl, const SwTblBoxFormula& rFml,
//STRIP001                          SwCellFrms& rCells )
//STRIP001 {
//STRIP001  SwTblBoxFormula aTmp( rFml );
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  for( USHORT nSelBoxes = aTmp.GetBoxesOfFormula( rTbl,aBoxes ); nSelBoxes; )
//STRIP001  {
//STRIP001      SwTableBox* pBox = aBoxes[ --nSelBoxes ];
//STRIP001      for( USHORT i = 0; i < rCells.Count(); ++i )
//STRIP001          if( rCells[ i ]->GetTabBox() == pBox )
//STRIP001              break;      // gefunden
//STRIP001
//STRIP001      if( i == rCells.Count() )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

    // erfrage die Formel fuer die Autosumme
//STRIP001 BOOL SwFEShell::GetAutoSum( String& rFml ) const
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  SwTabFrm *pTab = pFrm->ImplFindTabFrm();
//STRIP001  if( !pTab )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  rFml = String::CreateFromAscii( sCalc_Sum );
//STRIP001
//STRIP001  SwCellFrms aCells;
//STRIP001  if( ::GetAutoSumSel( *this, aCells ))
//STRIP001  {
//STRIP001      USHORT nW = 0, nInsPos = 0;
//STRIP001      for( USHORT n = aCells.Count(); n; )
//STRIP001      {
//STRIP001          SwCellFrm* pCFrm = aCells[ --n ];
//STRIP001          USHORT nBoxW = pCFrm->GetTabBox()->IsFormulaOrValueBox();
//STRIP001          if( !nBoxW )
//STRIP001              break;
//STRIP001
//STRIP001          if( !nW )
//STRIP001          {
//STRIP001              if( USHRT_MAX == nBoxW )
//STRIP001                  continue;       // leere am Anfang ueberspringen
//STRIP001
//STRIP001              rFml += '(';
//STRIP001              nInsPos = rFml.Len();
//STRIP001
//STRIP001              // Formeln nur wenn diese Boxen enthalten
//STRIP001              if( RES_BOXATR_FORMULA == nBoxW &&
//STRIP001                  !::lcl_IsFormulaSelBoxes( *pTab->GetTable(), pCFrm->
//STRIP001                  GetTabBox()->GetFrmFmt()->GetTblBoxFormula(), aCells))
//STRIP001              {
//STRIP001                  nW = RES_BOXATR_VALUE;
//STRIP001                  // alle vorhierigen Leere wieder mit aufnehmen !
//STRIP001                  for( USHORT i = aCells.Count(); n+1 < i; )
//STRIP001                  {
//STRIP001                      String sTmp( String::CreateFromAscii(
//STRIP001                              RTL_CONSTASCII_STRINGPARAM( "|<" )) );
//STRIP001                      sTmp += aCells[ --i ]->GetTabBox()->GetName();
//STRIP001                      sTmp += '>';
//STRIP001                      rFml.Insert( sTmp, nInsPos );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  nW = nBoxW;
//STRIP001          }
//STRIP001          else if( RES_BOXATR_VALUE == nW )
//STRIP001          {
//STRIP001              // values werden gesucht, Value/Formel/Text gefunden -> aufn.
//STRIP001              if( RES_BOXATR_FORMULA == nBoxW &&
//STRIP001                  ::lcl_IsFormulaSelBoxes( *pTab->GetTable(), pCFrm->
//STRIP001                      GetTabBox()->GetFrmFmt()->GetTblBoxFormula(), aCells ))
//STRIP001                  break;
//STRIP001              else if( USHRT_MAX != nBoxW )
//STRIP001                  rFml.Insert( cListDelim, nInsPos );
//STRIP001              else
//STRIP001                  break;
//STRIP001          }
//STRIP001          else if( RES_BOXATR_FORMULA == nW )
//STRIP001          {
//STRIP001              // bei Formeln nur weiter suchen, wenn die akt. Formel auf
//STRIP001              // alle Boxen verweist, die sich in der Selektion befinden
//STRIP001              if( RES_BOXATR_FORMULA == nBoxW )
//STRIP001              {
//STRIP001                  if( !::lcl_IsFormulaSelBoxes( *pTab->GetTable(), pCFrm->
//STRIP001                      GetTabBox()->GetFrmFmt()->GetTblBoxFormula(), aCells ))
//STRIP001                  {
//STRIP001                      // dann noch mal von vorne und nur die Values!
//STRIP001
//STRIP001                      nW = RES_BOXATR_VALUE;
//STRIP001                      rFml.Erase( nInsPos );
//STRIP001                      // alle vorhierigen Leere wieder mit aufnehmen !
//STRIP001                      for( USHORT i = aCells.Count(); n+1 < i; )
//STRIP001                      {
//STRIP001                          String sTmp( String::CreateFromAscii(
//STRIP001                                  RTL_CONSTASCII_STRINGPARAM( "|<" )) );
//STRIP001                          sTmp += aCells[ --i ]->GetTabBox()->GetName();
//STRIP001                          sTmp += '>';
//STRIP001                          rFml.Insert( sTmp, nInsPos );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                      rFml.Insert( cListDelim, nInsPos );
//STRIP001              }
//STRIP001              else if( USHRT_MAX == nBoxW )
//STRIP001                  break;
//STRIP001              else
//STRIP001                  continue;       // diese Boxen ignorieren
//STRIP001          }
//STRIP001          else
//STRIP001              // alles andere beendet die Schleife
//STRIP001 // evt. Texte noch zu lassen??
//STRIP001              break;
//STRIP001
//STRIP001          String sTmp( '<' );
//STRIP001          sTmp += pCFrm->GetTabBox()->GetName();
//STRIP001          sTmp += '>';
//STRIP001          rFml.Insert( sTmp, nInsPos );
//STRIP001      }
//STRIP001      if( nW )
//STRIP001      {
//STRIP001          rFml += ')';
//STRIP001
//STRIP001 /*
//STRIP001          // TabellenSelektion erzeugen??
//STRIP001          SwTblBoxFormula aTmp( rFml );
//STRIP001          SwSelBoxes aBoxes;
//STRIP001          for( USHORT nSelBoxes = aTmp.GetBoxesOfFormula( rTbl,aBoxes );
//STRIP001                  nSelBoxes; )
//STRIP001          {
//STRIP001          }
//STRIP001 */
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }
/* -----------------------------22.08.2002 12:50------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ BOOL SwFEShell::IsTableRightToLeft() const
/*M*/ {
/*M*/   SwFrm *pFrm = GetCurrFrm();
/*M*/   if( !pFrm->IsInTab() )
/*M*/       return FALSE;
/*M*/
/*M*/     return pFrm->ImplFindTabFrm()->IsRightToLeft();
/*M*/ }
/* -----------------------------22.08.2002 12:50------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ BOOL SwFEShell::IsMouseTableRightToLeft(const Point &rPt) const
/*M*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001 /*?*/     SwFrm *pFrm = (SwFrm *)GetBox( rPt );
//STRIP001 /*?*/     const SwTabFrm*  pTabFrm = pFrm ? pFrm->ImplFindTabFrm() : 0;
//STRIP001 /*?*/     ASSERT( pTabFrm, "Table not found" );
//STRIP001 /*?*/     return pTabFrm ? pTabFrm->IsRightToLeft() : FALSE;
/*M*/ }

