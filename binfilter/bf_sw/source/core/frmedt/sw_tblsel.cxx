/*************************************************************************
 *
 *  $RCSfile: sw_tblsel.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:43 $
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

#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SCH_DLL_HXX //autogen
#include <bf_sch/schdll.hxx>
#endif
#ifndef _SCH_MEMCHRT_HXX
#include <bf_sch/memchrt.hxx>
#endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _ROWFRM_HXX
#include <rowfrm.hxx>
#endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
namespace binfilter {

//siehe auch swtable.cxx
#define COLFUZZY 20L

// defines, die bestimmen, wie Tabellen Boxen gemergt werden:
//  - 1. alle leeren Zeilen entfernen, alle Boxen werden mit Blank,
//      alle Lines mit ParaBreak getrennt
//  - 2. alle leeren Zeilen und alle leeren Boxen am Anfang und Ende
//      entfernen, alle Boxen werden mit Blank,
//      alle Lines mit ParaBreak getrennt
//  - 3. alle leeren Boxen entfernen, alle Boxen werden mit Blank,
//      alle Lines mit ParaBreak getrennt

#undef      DEL_ONLY_EMPTY_LINES
#undef      DEL_EMPTY_BOXES_AT_START_AND_END
#define     DEL_ALL_EMPTY_BOXES


/*N*/ _SV_IMPL_SORTAR_ALG( SwSelBoxes, SwTableBoxPtr )
/*N*/ BOOL SwSelBoxes::Seek_Entry( const SwTableBoxPtr rSrch, USHORT* pFndPos ) const
/*N*/ {
/*N*/   ULONG nIdx = rSrch->GetSttIdx();
/*N*/
/*N*/   register USHORT nO = Count(), nM, nU = 0;
/*N*/   if( nO > 0 )
/*N*/   {
/*N*/       nO--;
/*N*/       while( nU <= nO )
/*N*/       {
/*N*/           nM = nU + ( nO - nU ) / 2;
/*N*/           if( (*this)[ nM ]->GetSttNd() == rSrch->GetSttNd() )
/*N*/           {
/*N*/               if( pFndPos )
/*N*/                   *pFndPos = nM;
/*N*/               return TRUE;
/*N*/           }
/*N*/           else if( (*this)[ nM ]->GetSttIdx() < nIdx )
/*N*/               nU = nM + 1;
/*N*/           else if( nM == 0 )
/*N*/           {
/*N*/               if( pFndPos )
/*N*/                   *pFndPos = nU;
/*N*/               return FALSE;
/*N*/           }
/*N*/           else
/*N*/               nO = nM - 1;
/*N*/       }
/*N*/   }
/*N*/   if( pFndPos )
/*N*/       *pFndPos = nU;
/*N*/   return FALSE;
/*N*/ }


//STRIP001 SV_IMPL_PTRARR( SwCellFrms, SwCellFrm* )

//STRIP001 struct _CmpLPt
//STRIP001 {
//STRIP001     Point aPos;
//STRIP001  const SwTableBox* pSelBox;
//STRIP001     BOOL bVert;
//STRIP001
//STRIP001     _CmpLPt( const Point& rPt, const SwTableBox* pBox, BOOL bVertical );
//STRIP001
//STRIP001     BOOL operator==( const _CmpLPt& rCmp ) const
//STRIP001  {   return X() == rCmp.X() && Y() == rCmp.Y() ? TRUE : FALSE; }
//STRIP001
//STRIP001     BOOL operator<( const _CmpLPt& rCmp ) const
//STRIP001     {
//STRIP001         if ( bVert )
//STRIP001             return X() > rCmp.X() || ( X() == rCmp.X() && Y() < rCmp.Y() )
//STRIP001                     ? TRUE : FALSE;
//STRIP001         else
//STRIP001             return Y() < rCmp.Y() || ( Y() == rCmp.Y() && X() < rCmp.X() )
//STRIP001                     ? TRUE : FALSE;
//STRIP001     }
//STRIP001
//STRIP001  long X() const { return aPos.X(); }
//STRIP001  long Y() const { return aPos.Y(); }
//STRIP001 };


//STRIP001 SV_DECL_VARARR_SORT( _MergePos, _CmpLPt, 0, 40 )
//STRIP001 SV_IMPL_VARARR_SORT( _MergePos, _CmpLPt )

/*N*/ SV_IMPL_PTRARR( _FndBoxes, _FndBox* )
/*N*/ SV_IMPL_PTRARR( _FndLines, _FndLine* )


/*N*/ struct _Sort_CellFrm
/*N*/ {
/*N*/   const SwCellFrm* pFrm;
/*N*/
/*N*/     _Sort_CellFrm( const SwCellFrm& rCFrm )
/*N*/         : pFrm( &rCFrm ) {}
/*N*/ };

/*N*/ SV_DECL_VARARR( _Sort_CellFrms, _Sort_CellFrm, 16, 16 )
/*N*/ SV_IMPL_VARARR( _Sort_CellFrms, _Sort_CellFrm )

/*N*/ SV_IMPL_PTRARR( SwChartBoxes, SwTableBoxPtr );
/*N*/ SV_IMPL_PTRARR( SwChartLines, SwChartBoxes* );

/*N*/ const SwLayoutFrm *lcl_FindCellFrm( const SwLayoutFrm *pLay )
/*N*/ {
/*N*/   while ( pLay && !pLay->IsCellFrm() )
/*?*/       pLay = pLay->GetUpper();
/*N*/   return pLay;
/*N*/ }

/*N*/ const SwLayoutFrm *lcl_FindNextCellFrm( const SwLayoutFrm *pLay )
/*N*/ {
/*N*/   //Dafuer sorgen, dass die Zelle auch verlassen wird (Bereiche)
/*N*/   const SwLayoutFrm *pTmp = pLay;
/*N*/   do {
/*N*/       pTmp = pTmp->GetNextLayoutLeaf();
/*N*/   } while( pLay->IsAnLower( pTmp ) );
/*N*/
/*N*/   while( pTmp && !pTmp->IsCellFrm() )
/*N*/       pTmp = pTmp->GetUpper();
/*N*/   return pTmp;
/*N*/ }

/*N*/ void GetTblSelCrs( const SwCrsrShell &rShell, SwSelBoxes& rBoxes )
/*N*/ {
/*N*/   if( rBoxes.Count() )
/*?*/       rBoxes.Remove( USHORT(0), rBoxes.Count() );
/*N*/   if( rShell.IsTableMode() && 1 ) //STRIP001 ((SwCrsrShell&)rShell).UpdateTblSelBoxes())
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    rBoxes.Insert( &rShell.GetTableCrsr()->GetBoxes() );
/*N*/ }

/*N*/ void GetTblSelCrs( const SwTableCursor& rTblCrsr, SwSelBoxes& rBoxes )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( rBoxes.Count() )
//STRIP001      rBoxes.Remove( USHORT(0), rBoxes.Count() );
//STRIP001
//STRIP001  if( rTblCrsr.IsChgd() || !rTblCrsr.GetBoxesCount() )
//STRIP001  {
//STRIP001      SwTableCursor* pTCrsr = (SwTableCursor*)&rTblCrsr;
//STRIP001      pTCrsr->GetDoc()->GetRootFrm()->MakeTblCrsrs( *pTCrsr );
//STRIP001  }
//STRIP001
//STRIP001  if( rTblCrsr.GetBoxesCount() )
//STRIP001      rBoxes.Insert( &rTblCrsr.GetBoxes() );
/*N*/ }

/*N*/ void GetTblSel( const SwCrsrShell& rShell, SwSelBoxes& rBoxes,
/*N*/               const SwTblSearchType eSearchType )
/*N*/ {
/*N*/   //Start- und Endzelle besorgen und den naechsten fragen.
/*N*/   if ( !rShell.IsTableMode() )
/*N*/       rShell.GetCrsr();
/*N*/
/*N*/   const SwShellCrsr *pCrsr = rShell.GetTableCrsr();
/*N*/   if( !pCrsr )
/*N*/       pCrsr = (SwShellCrsr*)*rShell.GetSwCrsr( FALSE );
/*N*/
/*N*/   GetTblSel( *pCrsr, rBoxes, eSearchType );
/*N*/ }

/*N*/ void GetTblSel( const SwCursor& rCrsr, SwSelBoxes& rBoxes,
/*N*/               const SwTblSearchType eSearchType )
/*N*/ {
/*N*/   //Start- und Endzelle besorgen und den naechsten fragen.
/*N*/   ASSERT( rCrsr.GetCntntNode() && rCrsr.GetCntntNode( FALSE ),
/*N*/           "Tabselection nicht auf Cnt." );
/*N*/
/*N*/   // Zeilen-Selektion:
/*N*/   // teste ob Tabelle komplex ist. Wenn ja, dann immer uebers Layout
/*N*/   // die selektierten Boxen zusammen suchen. Andernfalls ueber die
/*N*/   // Tabellen-Struktur (fuer Makros !!)
/*N*/   const SwTableNode* pTblNd;
/*N*/   if( TBLSEARCH_ROW == ((~TBLSEARCH_PROTECT ) & eSearchType ) &&
/*N*/       0 != ( pTblNd = rCrsr.GetNode()->FindTableNode() ) &&
/*N*/       !pTblNd->GetTable().IsTblComplex() )
/*N*/   {
/*N*/       const SwTable& rTbl = pTblNd->GetTable();
/*N*/       const SwTableLines& rLines = rTbl.GetTabLines();
/*N*/       const SwTableLine* pLine = rTbl.GetTblBox(  rCrsr.GetNode(
/*N*/                   FALSE )->StartOfSectionIndex() )->GetUpper();
/*N*/       USHORT nSttPos = rLines.GetPos( pLine );
/*N*/       ASSERT( USHRT_MAX != nSttPos, "Wo ist meine Zeile in der Tabelle?" );
/*N*/
/*N*/       pLine = rTbl.GetTblBox( rCrsr.GetNode( TRUE )->StartOfSectionIndex() )
/*N*/                               ->GetUpper();
/*N*/       USHORT nEndPos = rLines.GetPos( pLine );
/*N*/       ASSERT( USHRT_MAX != nEndPos, "Wo ist meine Zeile in der Tabelle?" );
/*N*/
/*N*/       if( nEndPos < nSttPos )     // vertauschen
/*N*/       {
/*?*/           USHORT nTmp = nSttPos; nSttPos = nEndPos; nEndPos = nTmp;
/*N*/       }
/*N*/
/*N*/       int bChkProtected = TBLSEARCH_PROTECT & eSearchType;
/*N*/       for( ; nSttPos <= nEndPos; ++nSttPos )
/*N*/       {
/*N*/           pLine = rLines[ nSttPos ];
/*N*/           for( USHORT n = pLine->GetTabBoxes().Count(); n ; )
/*N*/           {
/*N*/               SwTableBox* pBox = pLine->GetTabBoxes()[ --n ];
/*N*/               // Zellenschutzt beachten ??
/*N*/               if( !bChkProtected ||
/*N*/                   !pBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
/*N*/                   rBoxes.Insert( pBox );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       Point aPtPos, aMkPos;
/*N*/       const SwShellCrsr* pShCrsr = rCrsr;
/*N*/       if( pShCrsr )
/*N*/       {
/*N*/           aPtPos = pShCrsr->GetPtPos();
/*N*/           aMkPos = pShCrsr->GetMkPos();
/*N*/       }
/*N*/       const SwLayoutFrm *pStart = rCrsr.GetCntntNode()->GetFrm(
/*N*/                                   &aPtPos )->GetUpper(),
/*N*/                         *pEnd   = rCrsr.GetCntntNode(FALSE)->GetFrm(
/*N*/                                   &aMkPos )->GetUpper();
/*N*/       GetTblSel( pStart, pEnd, rBoxes, eSearchType );
/*N*/   }
/*N*/ }

/*N*/ void GetTblSel( const SwLayoutFrm* pStart, const SwLayoutFrm* pEnd,
/*N*/               SwSelBoxes& rBoxes, const SwTblSearchType eSearchType )
/*N*/ {
/*N*/   //Muss ein HeadlineRepeat beachtet werden?
/*N*/   const BOOL bRepeat = pStart->FindTabFrm()->GetTable()->IsHeadlineRepeat();
/*N*/   int bChkProtected = TBLSEARCH_PROTECT & eSearchType;
/*N*/
/*N*/   BOOL bTblIsValid;
/*N*/   int nLoopMax = 100;     //JP 28.06.99: max 100 loops - Bug 67292
/*N*/   do {
/*N*/       bTblIsValid = TRUE;
/*N*/
/*N*/       //Zuerst lassen wir uns die Tabellen und die Rechtecke heraussuchen.
/*N*/       SwSelUnions aUnions;
/*N*/       ::binfilter::MakeSelUnions( aUnions, pStart, pEnd, eSearchType );
/*N*/
/*N*/       //Jetzt zu jedem Eintrag die Boxen herausfischen und uebertragen.
/*N*/       for( USHORT i = 0; i < aUnions.Count() && bTblIsValid; ++i )
/*N*/       {
/*N*/           SwSelUnion *pUnion = aUnions[i];
/*N*/           const SwTabFrm *pTable = pUnion->GetTable();
/*N*/           if( !pTable->IsValid() && nLoopMax )
/*N*/           {
/*?*/               bTblIsValid = FALSE;
/*?*/               break;
/*N*/           }
/*N*/
/*N*/           const SwLayoutFrm *pRow = (const SwLayoutFrm*)pTable->Lower();
/*N*/           //Wenn die Row eine wiederholte Headline ist wird sie nicht
/*N*/           //beachtet.
/*N*/           if( bRepeat && pTable->IsFollow() )
/*?*/               pRow = (const SwLayoutFrm*)pRow->GetNext();
/*N*/
/*N*/           while( pRow && bTblIsValid )
/*N*/           {
/*N*/               if( !pRow->IsValid() && nLoopMax )
/*N*/               {
/*?*/                   bTblIsValid = FALSE;
/*?*/                   break;
/*N*/               }
/*N*/
/*N*/               if ( pRow->Frm().IsOver( pUnion->GetUnion() ) )
/*N*/               {
/*N*/                   const SwLayoutFrm *pCell = pRow->FirstCell();
/*N*/
/*N*/                   while( bTblIsValid && pCell && pRow->IsAnLower( pCell ) )
/*N*/                   {
/*N*/                       if( !pCell->IsValid() && nLoopMax )
/*N*/                       {
/*?*/                           bTblIsValid = FALSE;
/*?*/                           break;
/*N*/                       }
/*N*/
/*N*/                       ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
/*N*/                       if( ::binfilter::IsFrmInTblSel( pUnion->GetUnion(), pCell ) )
/*N*/                       {
/*N*/                           SwTableBox* pBox = (SwTableBox*)
/*N*/                               ((SwCellFrm*)pCell)->GetTabBox();
/*N*/                           // Zellenschutzt beachten ??
/*N*/                           if( !bChkProtected ||
/*N*/                               !pBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
/*N*/                               rBoxes.Insert( pBox );
/*N*/                       }
/*N*/                       if ( pCell->GetNext() )
/*N*/                       {
/*N*/                           pCell = (const SwLayoutFrm*)pCell->GetNext();
/*N*/                           if ( pCell->Lower()->IsRowFrm() )
/*?*/                               pCell = pCell->FirstCell();
/*N*/                       }
/*N*/                       else
/*N*/                           pCell = ::binfilter::lcl_FindNextCellFrm( pCell );
/*N*/                   }
/*N*/               }
/*N*/               pRow = (const SwLayoutFrm*)pRow->GetNext();
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if( bTblIsValid )
/*N*/           break;
/*N*/
/*N*/       // ansonsten das Layout der Tabelle kurz "kalkulieren" lassen
/*N*/       // und nochmals neu aufsetzen
/*?*/       SwTabFrm *pTable = aUnions[0]->GetTable();
/*?*/       for( i = 0; i < aUnions.Count(); ++i )
/*?*/       {
/*?*/           if( pTable->IsValid() )
/*?*/               pTable->InvalidatePos();
/*?*/           pTable->SetONECalcLowers();
/*?*/           pTable->Calc();
/*?*/           pTable->SetCompletePaint();
/*?*/           if( 0 == (pTable = pTable->GetFollow()) )
/*?*/               break;
/*?*/       }
/*?*/       i = 0;
/*?*/       rBoxes.Remove( i, rBoxes.Count() );
/*?*/       --nLoopMax;
/*?*/
/*?*/   } while( TRUE );
/*N*/   ASSERT( nLoopMax, "das Layout der Tabelle wurde nicht valide!" );
/*N*/ }



/*N*/ BOOL ChkChartSel( const SwNode& rSttNd, const SwNode& rEndNd,
/*N*/                   SwChartLines* pGetCLines )
/*N*/ {
/*N*/   const SwTableNode* pTNd = rSttNd.FindTableNode();
/*N*/   if( !pTNd )
/*N*/       return FALSE;
/*N*/
/*N*/   Point aNullPos;
/*N*/   SwNodeIndex aIdx( rSttNd );
/*N*/   const SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
/*N*/   if( !pCNd )
/*N*/       pCNd = aIdx.GetNodes().GoNextSection( &aIdx, FALSE, FALSE );
/*N*/
/*N*/     // #109394# if table is invisible, return
/*N*/     // (layout needed for forming table selection further down, so we can't
/*N*/     //  continue with invisible tables)
/*N*/     if( pCNd->GetFrm() == NULL )
/*N*/             return FALSE;
/*N*/
/*N*/   const SwLayoutFrm *pStart = pCNd ? pCNd->GetFrm( &aNullPos )->GetUpper() : 0;
/*N*/   ASSERT( pStart, "ohne Frame geht gar nichts" );
/*N*/
/*N*/   aIdx = rEndNd;
/*N*/   pCNd = aIdx.GetNode().GetCntntNode();
/*N*/   if( !pCNd )
/*N*/       pCNd = aIdx.GetNodes().GoNextSection( &aIdx, FALSE, FALSE );
/*N*/
/*N*/   const SwLayoutFrm *pEnd = pCNd ? pCNd->GetFrm( &aNullPos )->GetUpper() : 0;
/*N*/   ASSERT( pEnd, "ohne Frame geht gar nichts" );
/*N*/
/*N*/
/*N*/   //Muss ein HeadlineRepeat beachtet werden?
/*N*/   const BOOL bRepeat = pTNd->GetTable().IsHeadlineRepeat();
/*N*/
/*N*/   BOOL bTblIsValid, bValidChartSel;
/*N*/   int nLoopMax = 100;     //JP 28.06.99: max 100 loops - Bug 67292
/*N*/   do {
/*N*/       bTblIsValid = TRUE;
/*N*/       bValidChartSel = TRUE;
/*N*/
/*N*/       USHORT nRowCells = USHRT_MAX;
/*N*/
/*N*/       //Zuerst lassen wir uns die Tabellen und die Rechtecke heraussuchen.
/*N*/       SwSelUnions aUnions;
/*N*/       ::binfilter::MakeSelUnions( aUnions, pStart, pEnd, TBLSEARCH_NO_UNION_CORRECT );
/*N*/
/*N*/       //Jetzt zu jedem Eintrag die Boxen herausfischen und uebertragen.
/*N*/       for( USHORT i = 0; i < aUnions.Count() && bTblIsValid &&
/*N*/                                   bValidChartSel; ++i )
/*N*/       {
/*N*/           SwSelUnion *pUnion = aUnions[i];
/*N*/           const SwTabFrm *pTable = pUnion->GetTable();
/*N*/
/*N*/           SWRECTFN( pTable )
/*N*/ #ifdef BIDI
/*N*/             sal_Bool bRTL = pTable->IsRightToLeft();
/*N*/ #endif
/*N*/
/*N*/           if( !pTable->IsValid() && nLoopMax  )
/*N*/           {
/*N*/               bTblIsValid = FALSE;
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           _Sort_CellFrms aCellFrms;
/*N*/
/*N*/           const SwLayoutFrm *pRow = (const SwLayoutFrm*)pTable->Lower();
/*N*/           //Wenn die Row eine wiederholte Headline ist wird sie nicht
/*N*/           //beachtet.
/*N*/           if( bRepeat && pTable->IsFollow() )
/*N*/               pRow = (const SwLayoutFrm*)pRow->GetNext();
/*N*/
/*N*/           while( pRow && bTblIsValid && bValidChartSel )
/*N*/           {
/*N*/               if( !pRow->IsValid() && nLoopMax )
/*N*/               {
/*N*/                   bTblIsValid = FALSE;
/*N*/                   break;
/*N*/               }
/*N*/
/*N*/               if( pRow->Frm().IsOver( pUnion->GetUnion() ) )
/*N*/               {
/*N*/                   const SwLayoutFrm *pCell = pRow->FirstCell();
/*N*/
/*N*/                   while( bValidChartSel && bTblIsValid && pCell &&
/*N*/                           pRow->IsAnLower( pCell ) )
/*N*/                   {
/*N*/                       if( !pCell->IsValid() && nLoopMax  )
/*N*/                       {
/*N*/                           bTblIsValid = FALSE;
/*N*/                           break;
/*N*/                       }
/*N*/
/*N*/                       ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
/*N*/                       const SwRect& rUnion = pUnion->GetUnion(),
/*N*/                                   & rFrmRect = pCell->Frm();
/*N*/
/*N*/                       const long nUnionRight = rUnion.Right();
/*N*/                       const long nUnionBottom = rUnion.Bottom();
/*N*/                       const long nFrmRight = rFrmRect.Right();
/*N*/                       const long nFrmBottom = rFrmRect.Bottom();
/*N*/
/*N*/                       // liegt das FrmRect ausserhalb der Union, kann es
/*N*/                       // ignoriert werden.
/*N*/
/*N*/                       const long nXFuzzy = bVert ? 0 : 20;
/*N*/                       const long nYFuzzy = bVert ? 20 : 0;
/*N*/
/*N*/                       if( !(  rUnion.Top()  + nYFuzzy > nFrmBottom ||
/*N*/                               nUnionBottom < rFrmRect.Top() + nYFuzzy ||
/*N*/                               rUnion.Left() + nXFuzzy > nFrmRight ||
/*N*/                               nUnionRight < rFrmRect.Left() + nXFuzzy ))
/*N*/                       {
/*N*/                           // ok, rUnion is _not_ completely outside of rFrmRect
/*N*/
/*N*/                           // wenn es aber nicht komplett in der Union liegt,
/*N*/                           // dann ist es fuers Chart eine ungueltige
/*N*/                           // Selektion.
/*N*/                           if( rUnion.Left()   <= rFrmRect.Left() + nXFuzzy &&
/*N*/                               rFrmRect.Left() <= nUnionRight &&
/*N*/                               rUnion.Left()   <= nFrmRight &&
/*N*/                               nFrmRight       <= nUnionRight + nXFuzzy &&
/*N*/                               rUnion.Top()    <= rFrmRect.Top() + nYFuzzy &&
/*N*/                               rFrmRect.Top()  <= nUnionBottom &&
/*N*/                               rUnion.Top()    <= nFrmBottom &&
/*N*/                               nFrmBottom      <= nUnionBottom+ nYFuzzy )
/*N*/
/*N*/                               aCellFrms.Insert(
/*N*/                                         _Sort_CellFrm( *(SwCellFrm*)pCell ),
/*N*/                                       aCellFrms.Count() );
/*N*/                           else
/*N*/                           {
/*N*/                               bValidChartSel = FALSE;
/*N*/                               break;
/*N*/                           }
/*N*/                       }
/*N*/                       if ( pCell->GetNext() )
/*N*/                       {
/*N*/                           pCell = (const SwLayoutFrm*)pCell->GetNext();
/*N*/                           if ( pCell->Lower()->IsRowFrm() )
/*N*/                               pCell = pCell->FirstCell();
/*N*/                       }
/*N*/                       else
/*N*/                           pCell = ::binfilter::lcl_FindNextCellFrm( pCell );
/*N*/                   }
/*N*/               }
/*N*/               pRow = (const SwLayoutFrm*)pRow->GetNext();
/*N*/           }
/*N*/
/*N*/           if( !bValidChartSel )
/*N*/               break;
/*N*/
/*N*/           // alle Zellen der (Teil-)Tabelle zusammen. Dann teste mal ob
/*N*/           // all huebsch nebeneinander liegen.
/*N*/           USHORT n, nEnd, nCellCnt = 0;
/*N*/           long nYPos = LONG_MAX, nXPos, nHeight;
/*N*/
/*N*/           for( n = 0, nEnd = aCellFrms.Count(); n < nEnd; ++n )
/*N*/           {
/*N*/               const _Sort_CellFrm& rCF = aCellFrms[ n ];
/*N*/               if( (rCF.pFrm->Frm().*fnRect->fnGetTop)() != nYPos )
/*N*/               {
/*N*/                   // neue Zeile
/*N*/                   if( n )
/*N*/                   {
/*N*/                       if( USHRT_MAX == nRowCells )        // 1. Zeilenwechsel
/*N*/                           nRowCells = nCellCnt;
/*N*/                       else if( nRowCells != nCellCnt )
/*N*/                       {
/*N*/                           bValidChartSel = FALSE;
/*N*/                           break;
/*N*/                       }
/*N*/                   }
/*N*/                   nCellCnt = 1;
/*N*/                   nYPos = (rCF.pFrm->Frm().*fnRect->fnGetTop)();
/*N*/                   nHeight = (rCF.pFrm->Frm().*fnRect->fnGetHeight)();
/*N*/
/*N*/ #ifdef BIDI
/*N*/                     nXPos = bRTL ?
/*N*/                             (rCF.pFrm->Frm().*fnRect->fnGetLeft)() :
/*N*/                             (rCF.pFrm->Frm().*fnRect->fnGetRight)();
/*N*/                 }
/*N*/                 else if( nXPos == ( bRTL ?
/*N*/                                     (rCF.pFrm->Frm().*fnRect->fnGetRight)() :
/*N*/                                     (rCF.pFrm->Frm().*fnRect->fnGetLeft)() ) &&
/*N*/                          nHeight == (rCF.pFrm->Frm().*fnRect->fnGetHeight)() )
/*N*/                 {
/*N*/                     nXPos += ( bRTL ? (-1) : 1 ) *
/*N*/                              (rCF.pFrm->Frm().*fnRect->fnGetWidth)();
/*N*/                     ++nCellCnt;
/*N*/                 }
/*N*/
/*N*/ #else
/*N*/                     nXPos = (rCF.pFrm->Frm().*fnRect->fnGetRight)();
/*N*/                 }
/*N*/                 else if( nXPos == (rCF.pFrm->Frm().*fnRect->fnGetLeft)() &&
/*N*/                          nHeight == (rCF.pFrm->Frm().*fnRect->fnGetHeight)() )
/*N*/                 {
/*N*/                     nXPos += (rCF.pFrm->Frm().*fnRect->fnGetWidth)();
/*N*/                     ++nCellCnt;
/*N*/                 }
/*N*/ #endif
/*N*/               else
/*N*/               {
/*N*/                   bValidChartSel = FALSE;
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/           if( bValidChartSel )
/*N*/           {
/*N*/               if( USHRT_MAX == nRowCells )
/*N*/                   nRowCells = nCellCnt;
/*N*/               else if( nRowCells != nCellCnt )
/*N*/                   bValidChartSel = FALSE;
/*N*/           }
/*N*/
/*N*/           if( bValidChartSel && pGetCLines )
/*N*/           {
/*N*/               nYPos = LONG_MAX;
/*N*/               SwChartBoxes* pBoxes;
/*N*/               for( n = 0, nEnd = aCellFrms.Count(); n < nEnd; ++n )
/*N*/               {
/*N*/                   const _Sort_CellFrm& rCF = aCellFrms[ n ];
/*N*/                   if( (rCF.pFrm->Frm().*fnRect->fnGetTop)() != nYPos )
/*N*/                   {
/*N*/                       pBoxes = new SwChartBoxes( 255 < nRowCells
/*N*/                                                   ? 255 : (BYTE)nRowCells);
/*N*/                       pGetCLines->C40_INSERT( SwChartBoxes, pBoxes, pGetCLines->Count() );
/*N*/                         nYPos = (rCF.pFrm->Frm().*fnRect->fnGetTop)();
/*N*/                   }
/*N*/                   SwTableBoxPtr pBox = (SwTableBox*)rCF.pFrm->GetTabBox();
/*N*/                   pBoxes->Insert( pBox, pBoxes->Count() );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if( bTblIsValid )
/*N*/           break;
/*N*/
/*N*/       // ansonsten das Layout der Tabelle kurz "kalkulieren" lassen
/*N*/       // und nochmals neu aufsetzen
/*N*/       SwTabFrm *pTable = aUnions[0]->GetTable();
/*N*/       for( i = 0; i < aUnions.Count(); ++i )
/*N*/       {
/*N*/           if( pTable->IsValid() )
/*N*/               pTable->InvalidatePos();
/*N*/           pTable->SetONECalcLowers();
/*N*/           pTable->Calc();
/*N*/           pTable->SetCompletePaint();
/*N*/           if( 0 == (pTable = pTable->GetFollow()) )
/*N*/               break;
/*N*/       }
/*N*/       --nLoopMax;
/*N*/       if( pGetCLines )
/*N*/           pGetCLines->DeleteAndDestroy( 0, pGetCLines->Count() );
/*N*/   } while( TRUE );
/*N*/
/*N*/   ASSERT( nLoopMax, "das Layout der Tabelle wurde nicht valide!" );
/*N*/
/*N*/   if( !bValidChartSel && pGetCLines )
/*N*/       pGetCLines->DeleteAndDestroy( 0, pGetCLines->Count() );
/*N*/
/*N*/   return bValidChartSel;
/*N*/ }


/*N*/ BOOL IsFrmInTblSel( const SwRect& rUnion, const SwFrm* pCell )
/*N*/ {
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/     if( pCell->IsVertical() )
/*?*/         return ( rUnion.Right() >= pCell->Frm().Right() &&
/*?*/             rUnion.Left() <= pCell->Frm().Left() &&
/*?*/             (( rUnion.Top() <= pCell->Frm().Top()+20 &&
/*?*/                rUnion.Bottom() > pCell->Frm().Top() ) ||
/*?*/              ( rUnion.Top() >= pCell->Frm().Top() &&
/*?*/                rUnion.Bottom() < pCell->Frm().Bottom() )) ? TRUE : FALSE );
/*N*/ #endif
/*N*/   return (
/*N*/       rUnion.Top() <= pCell->Frm().Top() &&
/*N*/       rUnion.Bottom() >= pCell->Frm().Bottom() &&
/*N*/
/*N*/       (( rUnion.Left() <= pCell->Frm().Left()+20 &&
/*N*/          rUnion.Right() > pCell->Frm().Left() ) ||
/*N*/
/*N*/        ( rUnion.Left() >= pCell->Frm().Left() &&
/*N*/          rUnion.Right() < pCell->Frm().Right() )) ? TRUE : FALSE );
/*N*/ }

//STRIP001 BOOL GetAutoSumSel( const SwCrsrShell& rShell, SwCellFrms& rBoxes )
//STRIP001 {
//STRIP001  SwShellCrsr *pCrsr = (SwShellCrsr*) rShell.IsTableMode() ?
//STRIP001                        rShell.pTblCrsr : rShell.pCurCrsr;
//STRIP001
//STRIP001  const SwLayoutFrm *pStart = pCrsr->GetCntntNode()->GetFrm(
//STRIP001                    &pCrsr->GetPtPos() )->GetUpper(),
//STRIP001                    *pEnd   = pCrsr->GetCntntNode(FALSE)->GetFrm(
//STRIP001                    &pCrsr->GetMkPos() )->GetUpper();
//STRIP001
//STRIP001  //Muss ein HeadlineRepeat beachtet werden?
//STRIP001  const BOOL bRepeat = pStart->FindTabFrm()->GetTable()->IsHeadlineRepeat();
//STRIP001
//STRIP001  const SwLayoutFrm* pSttCell = pStart;
//STRIP001  while( pSttCell && !pSttCell->IsCellFrm() )
//STRIP001      pSttCell = pSttCell->GetUpper();
//STRIP001
//STRIP001  //Zuerst lassen wir uns die Tabellen und die Rechtecke heraussuchen.
//STRIP001  SwSelUnions aUnions;
//STRIP001
//STRIP001  // default erstmal nach oben testen, dann nach links
//STRIP001  ::MakeSelUnions( aUnions, pStart, pEnd, TBLSEARCH_COL );
//STRIP001
//STRIP001  BOOL bTstRow = TRUE, bFound = FALSE;
//STRIP001  USHORT i;
//STRIP001
//STRIP001  // 1. teste ob die darueber liegende Box Value/Formel enhaelt:
//STRIP001  for( i = 0; i < aUnions.Count(); ++i )
//STRIP001  {
//STRIP001      SwSelUnion *pUnion = aUnions[i];
//STRIP001      const SwTabFrm *pTable = pUnion->GetTable();
//STRIP001
//STRIP001      const SwLayoutFrm *pRow = (const SwLayoutFrm*)pTable->Lower();
//STRIP001      //Wenn die Row eine wiederholte Headline ist wird sie nicht
//STRIP001      //beachtet.
//STRIP001      if( bRepeat && pTable->IsFollow() )
//STRIP001          pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001
//STRIP001      while( pRow )
//STRIP001      {
//STRIP001          if( pRow->Frm().IsOver( pUnion->GetUnion() ) )
//STRIP001          {
//STRIP001              const SwCellFrm* pUpperCell = 0;
//STRIP001              const SwLayoutFrm *pCell = pRow->FirstCell();
//STRIP001
//STRIP001              while( pCell && pRow->IsAnLower( pCell ) )
//STRIP001              {
//STRIP001                  if( pCell == pSttCell )
//STRIP001                  {
//STRIP001                      USHORT nWhichId = 0;
//STRIP001                      for( USHORT n = rBoxes.Count(); n; )
//STRIP001                          if( USHRT_MAX != ( nWhichId = rBoxes[ --n ]
//STRIP001                              ->GetTabBox()->IsFormulaOrValueBox() ))
//STRIP001                              break;
//STRIP001
//STRIP001                      // alle Boxen zusammen, nicht mehr die Zeile
//STRIP001                      // pruefen, wenn eine Formel oder Value gefunden wurde
//STRIP001                      bTstRow = 0 == nWhichId || USHRT_MAX == nWhichId;
//STRIP001                      bFound = TRUE;
//STRIP001                      break;
//STRIP001                  }
//STRIP001
//STRIP001                  ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
//STRIP001                  if( ::IsFrmInTblSel( pUnion->GetUnion(), pCell ) )
//STRIP001                      pUpperCell = (SwCellFrm*)pCell;
//STRIP001
//STRIP001                  if( pCell->GetNext() )
//STRIP001                  {
//STRIP001                      pCell = (const SwLayoutFrm*)pCell->GetNext();
//STRIP001                      if ( pCell->Lower()->IsRowFrm() )
//STRIP001                          pCell = pCell->FirstCell();
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pCell = ::lcl_FindNextCellFrm( pCell );
//STRIP001              }
//STRIP001
//STRIP001              if( pUpperCell )
//STRIP001                  rBoxes.Insert( pUpperCell, rBoxes.Count() );
//STRIP001          }
//STRIP001          if( bFound )
//STRIP001          {
//STRIP001              i = aUnions.Count();
//STRIP001              break;
//STRIP001          }
//STRIP001          pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  // 2. teste ob die links liegende Box Value/Formel enhaelt:
//STRIP001  if( bTstRow )
//STRIP001  {
//STRIP001      bFound = FALSE;
//STRIP001
//STRIP001      rBoxes.Remove( 0, rBoxes.Count() );
//STRIP001      aUnions.DeleteAndDestroy( 0, aUnions.Count() );
//STRIP001      ::MakeSelUnions( aUnions, pStart, pEnd, TBLSEARCH_ROW );
//STRIP001
//STRIP001      for( i = 0; i < aUnions.Count(); ++i )
//STRIP001      {
//STRIP001          SwSelUnion *pUnion = aUnions[i];
//STRIP001          const SwTabFrm *pTable = pUnion->GetTable();
//STRIP001
//STRIP001          const SwLayoutFrm *pRow = (const SwLayoutFrm*)pTable->Lower();
//STRIP001          //Wenn die Row eine wiederholte Headline ist wird sie nicht
//STRIP001          //beachtet.
//STRIP001          if( bRepeat && pTable->IsFollow() )
//STRIP001              pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001
//STRIP001          while( pRow )
//STRIP001          {
//STRIP001              if( pRow->Frm().IsOver( pUnion->GetUnion() ) )
//STRIP001              {
//STRIP001                  const SwLayoutFrm *pCell = pRow->FirstCell();
//STRIP001
//STRIP001                  while( pCell && pRow->IsAnLower( pCell ) )
//STRIP001                  {
//STRIP001                      if( pCell == pSttCell )
//STRIP001                      {
//STRIP001                          USHORT nWhichId = 0;
//STRIP001                          for( USHORT n = rBoxes.Count(); n; )
//STRIP001                              if( USHRT_MAX != ( nWhichId = rBoxes[ --n ]
//STRIP001                                  ->GetTabBox()->IsFormulaOrValueBox() ))
//STRIP001                                  break;
//STRIP001
//STRIP001                          // alle Boxen zusammen, nicht mehr die Zeile
//STRIP001                          // pruefen, wenn eine Formel oder Value gefunden wurde
//STRIP001                          bFound = 0 != nWhichId && USHRT_MAX != nWhichId;
//STRIP001                          bTstRow = FALSE;
//STRIP001                          break;
//STRIP001                      }
//STRIP001
//STRIP001                      ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
//STRIP001                      if( ::IsFrmInTblSel( pUnion->GetUnion(), pCell ) )
//STRIP001                      {
//STRIP001                          const SwCellFrm* pC = (SwCellFrm*)pCell;
//STRIP001                          rBoxes.Insert( pC, rBoxes.Count() );
//STRIP001                      }
//STRIP001                      if( pCell->GetNext() )
//STRIP001                      {
//STRIP001                          pCell = (const SwLayoutFrm*)pCell->GetNext();
//STRIP001                          if ( pCell->Lower()->IsRowFrm() )
//STRIP001                              pCell = pCell->FirstCell();
//STRIP001                      }
//STRIP001                      else
//STRIP001                          pCell = ::lcl_FindNextCellFrm( pCell );
//STRIP001                  }
//STRIP001              }
//STRIP001              if( !bTstRow )
//STRIP001              {
//STRIP001                  i = aUnions.Count();
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

/*N*/ BOOL HasProtectedCells( const SwSelBoxes& rBoxes )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   for( USHORT n = 0, nCnt = rBoxes.Count(); n < nCnt; ++n )
/*N*/       if( rBoxes[ n ]->GetFrmFmt()->GetProtect().IsCntntProtected() )
/*N*/       {
/*?*/           bRet = TRUE;
/*?*/           break;
/*N*/       }
/*N*/   return bRet;
/*N*/ }


//STRIP001 _CmpLPt::_CmpLPt( const Point& rPt, const SwTableBox* pBox, BOOL bVertical )
//STRIP001     : aPos( rPt ), pSelBox( pBox ), bVert( bVertical )
//STRIP001 {}

//STRIP001 void lcl_InsTblBox( SwTableNode* pTblNd, SwDoc* pDoc, SwTableBox* pBox,
//STRIP001                      USHORT nInsPos, USHORT nCnt = 1 )
//STRIP001 {
//STRIP001  ASSERT( pBox->GetSttNd(), "Box ohne Start-Node" );
//STRIP001  SwCntntNode* pCNd = pDoc->GetNodes()[ pBox->GetSttIdx() + 1 ]
//STRIP001                              ->GetCntntNode();
//STRIP001  if( pCNd && pCNd->IsTxtNode() )
//STRIP001      pDoc->GetNodes().InsBoxen( pTblNd, pBox->GetUpper(),
//STRIP001              (SwTableBoxFmt*)pBox->GetFrmFmt(),
//STRIP001              ((SwTxtNode*)pCNd)->GetTxtColl(),
//STRIP001              pCNd->GetpSwAttrSet(),
//STRIP001              nInsPos, nCnt );
//STRIP001  else
//STRIP001      pDoc->GetNodes().InsBoxen( pTblNd, pBox->GetUpper(),
//STRIP001              (SwTableBoxFmt*)pBox->GetFrmFmt(),
//STRIP001              (SwTxtFmtColl*)pDoc->GetDfltTxtFmtColl(), 0,
//STRIP001              nInsPos, nCnt );
//STRIP001 }

//STRIP001 BOOL IsEmptyBox( const SwTableBox& rBox, SwPaM& rPam )
//STRIP001 {
//STRIP001  rPam.GetPoint()->nNode = *rBox.GetSttNd()->EndOfSectionNode();
//STRIP001  rPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001  rPam.SetMark();
//STRIP001  rPam.GetPoint()->nNode = *rBox.GetSttNd();
//STRIP001  rPam.Move( fnMoveForward, fnGoCntnt );
//STRIP001
//STRIP001  BOOL bRet = *rPam.GetMark() == *rPam.GetPoint();
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      // dann teste mal auf absatzgebundenen Flys
//STRIP001      const SwSpzFrmFmts& rFmts = *rPam.GetDoc()->GetSpzFrmFmts();
//STRIP001      ULONG nSttIdx = rPam.GetPoint()->nNode.GetIndex(),
//STRIP001            nEndIdx = rBox.GetSttNd()->EndOfSectionIndex(),
//STRIP001            nIdx;
//STRIP001
//STRIP001      for( USHORT n = 0; n < rFmts.Count(); ++n )
//STRIP001      {
//STRIP001          const SwPosition* pAPos;
//STRIP001          const SwFmtAnchor& rAnchor = rFmts[n]->GetAnchor();
//STRIP001          if( ( FLY_AT_CNTNT == rAnchor.GetAnchorId() ||
//STRIP001                FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ) &&
//STRIP001              0 != ( pAPos = rAnchor.GetCntntAnchor() ) &&
//STRIP001              nSttIdx <= ( nIdx = pAPos->nNode.GetIndex() ) &&
//STRIP001              nIdx < nEndIdx )
//STRIP001          {
//STRIP001              bRet = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 void GetMergeSel( const SwPaM& rPam, SwSelBoxes& rBoxes,
//STRIP001              SwTableBox** ppMergeBox, SwUndoTblMerge* pUndo )
//STRIP001 {
//STRIP001  if( rBoxes.Count() )
//STRIP001      rBoxes.Remove( USHORT(0), rBoxes.Count() );
//STRIP001
//STRIP001  //Zuerst lassen wir uns die Tabellen und die Rechtecke heraussuchen.
//STRIP001  ASSERT( rPam.GetCntntNode() && rPam.GetCntntNode( FALSE ),
//STRIP001          "Tabselection nicht auf Cnt." );
//STRIP001
//STRIP001 //JP 24.09.96: Merge mit wiederholenden TabellenHeadline funktioniert nicht
//STRIP001 //               richtig. Warum nicht Point 0,0 benutzen? Dann ist garantiert,
//STRIP001 //               das die 1. Headline mit drin ist.
//STRIP001 //   Point aPt( rShell.GetCharRect().Pos() );
//STRIP001  Point aPt( 0, 0 );
//STRIP001  const SwLayoutFrm *pStart = rPam.GetCntntNode()->GetFrm(
//STRIP001                                                      &aPt )->GetUpper(),
//STRIP001                    *pEnd = rPam.GetCntntNode(FALSE)->GetFrm(
//STRIP001                                                      &aPt )->GetUpper();
//STRIP001
//STRIP001  SwSelUnions aUnions;
//STRIP001  ::MakeSelUnions( aUnions, pStart, pEnd );
//STRIP001  if( !aUnions.Count() )
//STRIP001      return;
//STRIP001
//STRIP001  const SwTable *pTable = aUnions[0]->GetTable()->GetTable();
//STRIP001  SwDoc* pDoc = (SwDoc*)pStart->GetFmt()->GetDoc();
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)pTable->GetTabSortBoxes()[ 0 ]->
//STRIP001                                      GetSttNd()->FindTableNode();
//STRIP001
//STRIP001  _MergePos aPosArr;      // Sort-Array mit den Positionen der Frames
//STRIP001  long nWidth;
//STRIP001  SwTableBox* pLastBox = 0;
//STRIP001
//STRIP001     SWRECTFN( pStart )
//STRIP001
//STRIP001  for ( USHORT i = 0; i < aUnions.Count(); ++i )
//STRIP001  {
//STRIP001      const SwTabFrm *pTabFrm = aUnions[i]->GetTable();
//STRIP001
//STRIP001      SwRect &rUnion = aUnions[i]->GetUnion();
//STRIP001      const SwLayoutFrm *pRow = (const SwLayoutFrm*)pTabFrm->Lower();
//STRIP001      if ( pRow && pTabFrm->IsFollow() && pTable->IsHeadlineRepeat() )
//STRIP001          pRow = (SwLayoutFrm*)pRow->GetNext();
//STRIP001
//STRIP001      while ( pRow )
//STRIP001      {
//STRIP001          if ( pRow->Frm().IsOver( rUnion ) )
//STRIP001          {
//STRIP001              const SwLayoutFrm *pCell = pRow->FirstCell();
//STRIP001 //               while ( !pCell->IsCellFrm() )
//STRIP001 //                   pCell = pCell->GetUpper();
//STRIP001
//STRIP001              while ( pCell && pRow->IsAnLower( pCell ) )
//STRIP001              {
//STRIP001                  ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
//STRIP001                      // in der vollen Breite ueberlappend ?
//STRIP001                  if( rUnion.Top() <= pCell->Frm().Top() &&
//STRIP001                      rUnion.Bottom() >= pCell->Frm().Bottom() )
//STRIP001                  {
//STRIP001                      SwTableBox* pBox =(SwTableBox*)((SwCellFrm*)pCell)->GetTabBox();
//STRIP001
//STRIP001                      // nur nach rechts ueberlappend
//STRIP001                      if( ( rUnion.Left() - COLFUZZY ) <= pCell->Frm().Left() &&
//STRIP001                          ( rUnion.Right() - COLFUZZY ) > pCell->Frm().Left() )
//STRIP001                      {
//STRIP001                          if( ( rUnion.Right() + COLFUZZY ) < pCell->Frm().Right() )
//STRIP001                          {
//STRIP001                              USHORT nInsPos = pBox->GetUpper()->
//STRIP001                                                  GetTabBoxes().C40_GETPOS( SwTableBox, pBox )+1;
//STRIP001                              lcl_InsTblBox( pTblNd, pDoc, pBox, nInsPos );
//STRIP001                              pBox->ClaimFrmFmt();
//STRIP001                              SwFmtFrmSize aNew(
//STRIP001                                      pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001                              nWidth = rUnion.Right() - pCell->Frm().Left();
//STRIP001                              nWidth = nWidth * aNew.GetWidth() /
//STRIP001                                       pCell->Frm().Width();
//STRIP001                              long nTmpWidth = aNew.GetWidth() - nWidth;
//STRIP001                              aNew.SetWidth( nWidth );
//STRIP001                              pBox->GetFrmFmt()->SetAttr( aNew );
//STRIP001                              // diese Box ist selektiert
//STRIP001                              pLastBox = pBox;
//STRIP001                              rBoxes.Insert( pBox );
//STRIP001                                 aPosArr.Insert(
//STRIP001                                     _CmpLPt( (pCell->Frm().*fnRect->fnGetPos)(),
//STRIP001                                     pBox, bVert ) );
//STRIP001
//STRIP001                              pBox = pBox->GetUpper()->GetTabBoxes()[ nInsPos ];
//STRIP001                              aNew.SetWidth( nTmpWidth );
//STRIP001                              pBox->ClaimFrmFmt();
//STRIP001                              pBox->GetFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001                              if( pUndo )
//STRIP001                                  pUndo->AddNewBox( pBox->GetSttIdx() );
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              // diese Box ist selektiert
//STRIP001                              pLastBox = pBox;
//STRIP001                              rBoxes.Insert( pBox );
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001                                 Point aInsPoint( (pCell->Frm().*fnRect->fnGetPos)() );
//STRIP001 #endif
//STRIP001                                 aPosArr.Insert(
//STRIP001                                     _CmpLPt( (pCell->Frm().*fnRect->fnGetPos)(),
//STRIP001                                  pBox, bVert ) );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      // oder rechts und links ueberlappend
//STRIP001                      else if( ( rUnion.Left() - COLFUZZY ) >= pCell->Frm().Left() &&
//STRIP001                              ( rUnion.Right() + COLFUZZY ) < pCell->Frm().Right() )
//STRIP001                      {
//STRIP001                          USHORT nInsPos = pBox->GetUpper()->GetTabBoxes().
//STRIP001                                          C40_GETPOS( SwTableBox, pBox )+1;
//STRIP001                          lcl_InsTblBox( pTblNd, pDoc, pBox, nInsPos, 2 );
//STRIP001                          pBox->ClaimFrmFmt();
//STRIP001                          SwFmtFrmSize aNew(
//STRIP001                                      pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001                          long nLeft = rUnion.Left() - pCell->Frm().Left();
//STRIP001                          nLeft = nLeft * aNew.GetWidth() /
//STRIP001                                  pCell->Frm().Width();
//STRIP001                          long nRight = pCell->Frm().Right() - rUnion.Right();
//STRIP001                          nRight = nRight * aNew.GetWidth() /
//STRIP001                                   pCell->Frm().Width();
//STRIP001                          nWidth = aNew.GetWidth() - nLeft - nRight;
//STRIP001
//STRIP001                          aNew.SetWidth( nLeft );
//STRIP001                          pBox->GetFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001                          {
//STRIP001                          const SfxPoolItem* pItem;
//STRIP001                          if( SFX_ITEM_SET == pBox->GetFrmFmt()->GetAttrSet()
//STRIP001                                      .GetItemState( RES_BOX, FALSE, &pItem ))
//STRIP001                          {
//STRIP001                              SvxBoxItem aBox( *(SvxBoxItem*)pItem );
//STRIP001                              aBox.SetLine( 0, BOX_LINE_RIGHT );
//STRIP001                              pBox->GetFrmFmt()->SetAttr( aBox );
//STRIP001                          }
//STRIP001                          }
//STRIP001
//STRIP001                          pBox = pBox->GetUpper()->GetTabBoxes()[ nInsPos ];
//STRIP001                          aNew.SetWidth( nWidth );
//STRIP001                          pBox->ClaimFrmFmt();
//STRIP001                          pBox->GetFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001                          if( pUndo )
//STRIP001                              pUndo->AddNewBox( pBox->GetSttIdx() );
//STRIP001
//STRIP001                          // diese Box ist selektiert
//STRIP001                          pLastBox = pBox;
//STRIP001                          rBoxes.Insert( pBox );
//STRIP001                             aPosArr.Insert(
//STRIP001                                 _CmpLPt( (pCell->Frm().*fnRect->fnGetPos)(),
//STRIP001                                 pBox, bVert ) );
//STRIP001
//STRIP001                          pBox = pBox->GetUpper()->GetTabBoxes()[ nInsPos+1 ];
//STRIP001                          aNew.SetWidth( nRight );
//STRIP001                          pBox->ClaimFrmFmt();
//STRIP001                          pBox->GetFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001                          if( pUndo )
//STRIP001                              pUndo->AddNewBox( pBox->GetSttIdx() );
//STRIP001                      }
//STRIP001                      // oder reicht die rechte Kante der Box in den
//STRIP001                      // selektierten Bereich?
//STRIP001                      else if( ( pCell->Frm().Right() - COLFUZZY ) < rUnion.Right() &&
//STRIP001                               ( pCell->Frm().Right() - COLFUZZY ) > rUnion.Left() &&
//STRIP001                               ( pCell->Frm().Left() + COLFUZZY ) < rUnion.Left() )
//STRIP001                      {
//STRIP001                          // dann muss eine neue Box einfuegt und die
//STRIP001                          // Breiten angepasst werden
//STRIP001                          USHORT nInsPos = pBox->GetUpper()->GetTabBoxes().
//STRIP001                                          C40_GETPOS( SwTableBox, pBox )+1;
//STRIP001                          lcl_InsTblBox( pTblNd, pDoc, pBox, nInsPos, 1 );
//STRIP001
//STRIP001                          SwFmtFrmSize aNew(pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001                          long nLeft = rUnion.Left() - pCell->Frm().Left(),
//STRIP001                              nRight = pCell->Frm().Right() - rUnion.Left();
//STRIP001
//STRIP001                          nLeft = nLeft * aNew.GetWidth() /
//STRIP001                                  pCell->Frm().Width();
//STRIP001                          nRight = nRight * aNew.GetWidth() /
//STRIP001                                  pCell->Frm().Width();
//STRIP001
//STRIP001                          aNew.SetWidth( nLeft );
//STRIP001                          pBox->ClaimFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001                              // diese Box ist selektiert
//STRIP001                          pBox = pBox->GetUpper()->GetTabBoxes()[ nInsPos ];
//STRIP001                          aNew.SetWidth( nRight );
//STRIP001                          pBox->ClaimFrmFmt();
//STRIP001                          pBox->GetFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001                          pLastBox = pBox;
//STRIP001                          rBoxes.Insert( pBox );
//STRIP001                             aPosArr.Insert( _CmpLPt( Point( rUnion.Left(),
//STRIP001                                                 pCell->Frm().Top()), pBox, bVert ));
//STRIP001
//STRIP001                          if( pUndo )
//STRIP001                              pUndo->AddNewBox( pBox->GetSttIdx() );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( pCell->GetNext() )
//STRIP001                  {
//STRIP001                      pCell = (const SwLayoutFrm*)pCell->GetNext();
//STRIP001                      if ( pCell->Lower()->IsRowFrm() )
//STRIP001                          pCell = pCell->FirstCell();
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pCell = ::lcl_FindNextCellFrm( pCell );
//STRIP001              }
//STRIP001          }
//STRIP001          pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // keine SSelection / keine gefundenen Boxen
//STRIP001  if( 1 >= rBoxes.Count() )
//STRIP001      return;
//STRIP001
//STRIP001  // dann suche mal alle Boxen, die nebeneinander liegen, und verbinde
//STRIP001  // deren Inhalte mit Blanks. Alle untereinander liegende werden als
//STRIP001  // Absaetze zusammengefasst
//STRIP001
//STRIP001  // 1. Loesung: gehe ueber das Array und
//STRIP001  //      alle auf der gleichen Y-Ebene werden mit Blanks getrennt
//STRIP001  //      alle anderen werden als Absaetze getrennt.
//STRIP001  BOOL bCalcWidth = TRUE;
//STRIP001  const SwTableBox* pFirstBox = aPosArr[ 0 ].pSelBox;
//STRIP001
//STRIP001  // JP 27.03.98:  Optimierung - falls die Boxen einer Line leer sind,
//STRIP001  //              dann werden jetzt dafuer keine Blanks und
//STRIP001  //              kein Umbruch mehr eingefuegt.
//STRIP001  //Block damit SwPaM, SwPosition vom Stack geloescht werden
//STRIP001  {
//STRIP001      SwPaM aPam( pDoc->GetNodes() );
//STRIP001
//STRIP001 #if defined( DEL_ONLY_EMPTY_LINES )
//STRIP001      nWidth = pFirstBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      BOOL bEmptyLine = TRUE;
//STRIP001      USHORT n, nSttPos = 0;
//STRIP001
//STRIP001      for( n = 0; n < aPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          const _CmpLPt& rPt = aPosArr[ n ];
//STRIP001          if( n && aPosArr[ n - 1 ].Y() == rPt.Y() )  // gleiche Ebene ?
//STRIP001          {
//STRIP001              if( bEmptyLine && !IsEmptyBox( *rPt.pSelBox, aPam ))
//STRIP001                  bEmptyLine = FALSE;
//STRIP001              if( bCalcWidth )
//STRIP001                  nWidth += rPt.pSelBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( bCalcWidth && n )
//STRIP001                  bCalcWidth = FALSE;     // eine Zeile fertig
//STRIP001
//STRIP001              if( bEmptyLine && nSttPos < n )
//STRIP001              {
//STRIP001                  // dann ist die gesamte Line leer und braucht
//STRIP001                  // nicht mit Blanks aufgefuellt und als Absatz
//STRIP001                  // eingefuegt werden.
//STRIP001                  if( pUndo )
//STRIP001                      for( USHORT i = nSttPos; i < n; ++i )
//STRIP001                          pUndo->SaveCollection( *aPosArr[ i ].pSelBox );
//STRIP001
//STRIP001                  aPosArr.Remove( nSttPos, n - nSttPos );
//STRIP001                  n = nSttPos;
//STRIP001              }
//STRIP001              else
//STRIP001                  nSttPos = n;
//STRIP001
//STRIP001              bEmptyLine = IsEmptyBox( *aPosArr[n].pSelBox, aPam );
//STRIP001          }
//STRIP001      }
//STRIP001      if( bEmptyLine && nSttPos < n )
//STRIP001      {
//STRIP001          if( pUndo )
//STRIP001              for( USHORT i = nSttPos; i < n; ++i )
//STRIP001                  pUndo->SaveCollection( *aPosArr[ i ].pSelBox );
//STRIP001          aPosArr.Remove( nSttPos, n - nSttPos );
//STRIP001      }
//STRIP001 #elsif defined( DEL_EMPTY_BOXES_AT_START_AND_END )
//STRIP001
//STRIP001      nWidth = pFirstBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      USHORT n, nSttPos = 0, nSEndPos = 0, nESttPos = 0;
//STRIP001
//STRIP001      for( n = 0; n < aPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          const _CmpLPt& rPt = aPosArr[ n ];
//STRIP001          if( n && aPosArr[ n - 1 ].Y() == rPt.Y() )  // gleiche Ebene ?
//STRIP001          {
//STRIP001              BOOL bEmptyBox = IsEmptyBox( *rPt.pSelBox, aPam );
//STRIP001              if( bEmptyBox )
//STRIP001              {
//STRIP001                  if( nSEndPos == n )     // der Anfang ist leer
//STRIP001                      nESttPos = ++nSEndPos;
//STRIP001              }
//STRIP001              else                        // das Ende kann leer sein
//STRIP001                  nESttPos = n+1;
//STRIP001
//STRIP001              if( bCalcWidth )
//STRIP001                  nWidth += rPt.pSelBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( bCalcWidth && n )
//STRIP001                  bCalcWidth = FALSE;     // eine Zeile fertig
//STRIP001
//STRIP001              // zuerst die vom Anfang
//STRIP001              if( nSttPos < nSEndPos )
//STRIP001              {
//STRIP001                  // dann ist der vorder Teil der Line leer und braucht
//STRIP001                  // nicht mit Blanks aufgefuellt werden.
//STRIP001                  if( pUndo )
//STRIP001                      for( USHORT i = nSttPos; i < nSEndPos; ++i )
//STRIP001                          pUndo->SaveCollection( *aPosArr[ i ].pSelBox );
//STRIP001
//STRIP001                  USHORT nCnt = nSEndPos - nSttPos;
//STRIP001                  aPosArr.Remove( nSttPos, nCnt );
//STRIP001                  nESttPos -= nCnt;
//STRIP001                  n -= nCnt;
//STRIP001              }
//STRIP001
//STRIP001              if( nESttPos < n )
//STRIP001              {
//STRIP001                  // dann ist der vorder Teil der Line leer und braucht
//STRIP001                  // nicht mit Blanks aufgefuellt werden.
//STRIP001                  if( pUndo )
//STRIP001                      for( USHORT i = nESttPos; i < n; ++i )
//STRIP001                          pUndo->SaveCollection( *aPosArr[ i ].pSelBox );
//STRIP001
//STRIP001                  USHORT nCnt = n - nESttPos;
//STRIP001                  aPosArr.Remove( nESttPos, nCnt );
//STRIP001                  n -= nCnt;
//STRIP001              }
//STRIP001
//STRIP001              nSttPos = nSEndPos = nESttPos = n;
//STRIP001              if( IsEmptyBox( *aPosArr[n].pSelBox, aPam ))
//STRIP001                  ++nSEndPos;
//STRIP001              else
//STRIP001                  ++nESttPos;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // zuerst die vom Anfang
//STRIP001      if( nSttPos < nSEndPos )
//STRIP001      {
//STRIP001          // dann ist der vorder Teil der Line leer und braucht
//STRIP001          // nicht mit Blanks aufgefuellt werden.
//STRIP001          if( pUndo )
//STRIP001              for( USHORT i = nSttPos; i < nSEndPos; ++i )
//STRIP001                  pUndo->SaveCollection( *aPosArr[ i ].pSelBox );
//STRIP001
//STRIP001          USHORT nCnt = nSEndPos - nSttPos;
//STRIP001          aPosArr.Remove( nSttPos, nCnt );
//STRIP001          nESttPos -= nCnt;
//STRIP001          n -= nCnt;
//STRIP001      }
//STRIP001      if( nESttPos < n )
//STRIP001      {
//STRIP001          // dann ist der vorder Teil der Line leer und braucht
//STRIP001          // nicht mit Blanks aufgefuellt werden.
//STRIP001          if( pUndo )
//STRIP001              for( USHORT i = nESttPos; i < n; ++i )
//STRIP001                  pUndo->SaveCollection( *aPosArr[ i ].pSelBox );
//STRIP001
//STRIP001          USHORT nCnt = n - nESttPos;
//STRIP001          aPosArr.Remove( nESttPos, nCnt );
//STRIP001      }
//STRIP001 #else
//STRIP001 // DEL_ALL_EMPTY_BOXES
//STRIP001
//STRIP001      nWidth = 0;
//STRIP001      long nY = aPosArr.Count() ?
//STRIP001                     ( bVert ?
//STRIP001                    aPosArr[ 0 ].X() :
//STRIP001                    aPosArr[ 0 ].Y() ) :
//STRIP001                0;
//STRIP001
//STRIP001      for( USHORT n = 0; n < aPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          const _CmpLPt& rPt = aPosArr[ n ];
//STRIP001             if( bCalcWidth )
//STRIP001          {
//STRIP001                 if( nY == ( bVert ? rPt.X() : rPt.Y() ) )            // gleiche Ebene ?
//STRIP001                  nWidth += rPt.pSelBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001              else
//STRIP001                  bCalcWidth = FALSE;     // eine Zeile fertig
//STRIP001          }
//STRIP001
//STRIP001          if( IsEmptyBox( *rPt.pSelBox, aPam ) )
//STRIP001          {
//STRIP001              if( pUndo )
//STRIP001                  pUndo->SaveCollection( *rPt.pSelBox );
//STRIP001
//STRIP001              aPosArr.Remove( n, 1 );
//STRIP001              --n;
//STRIP001          }
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  // lege schon mal die neue Box an
//STRIP001  {
//STRIP001      SwTableBox* pTmpBox = rBoxes[0];
//STRIP001      SwTableLine* pInsLine = pTmpBox->GetUpper();
//STRIP001      USHORT nInsPos = pInsLine->GetTabBoxes().C40_GETPOS( SwTableBox, pTmpBox );
//STRIP001
//STRIP001      lcl_InsTblBox( pTblNd, pDoc, pTmpBox, nInsPos );
//STRIP001      (*ppMergeBox) = pInsLine->GetTabBoxes()[ nInsPos ];
//STRIP001      pInsLine->GetTabBoxes().Remove( nInsPos );      // wieder austragen
//STRIP001      (*ppMergeBox)->SetUpper( 0 );
//STRIP001      (*ppMergeBox)->ClaimFrmFmt();
//STRIP001
//STRIP001      // setze die Umrandung: von der 1. Box die linke/obere von der
//STRIP001      // letzten Box die rechte/untere Kante:
//STRIP001      if( pLastBox && pFirstBox )
//STRIP001      {
//STRIP001          SvxBoxItem aBox( pFirstBox->GetFrmFmt()->GetBox() );
//STRIP001          const SvxBoxItem& rBox = pLastBox->GetFrmFmt()->GetBox();
//STRIP001          aBox.SetLine( rBox.GetRight(), BOX_LINE_RIGHT );
//STRIP001          aBox.SetLine( rBox.GetBottom(), BOX_LINE_BOTTOM );
//STRIP001          if( aBox.GetLeft() || aBox.GetTop() ||
//STRIP001              aBox.GetRight() || aBox.GetBottom() )
//STRIP001              (*ppMergeBox)->GetFrmFmt()->SetAttr( aBox );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Block damit SwPaM, SwPosition vom Stack geloescht werden
//STRIP001  if( aPosArr.Count() )
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd;
//STRIP001      SwPosition aInsPos( *(*ppMergeBox)->GetSttNd() );
//STRIP001      SwNodeIndex& rInsPosNd = aInsPos.nNode;
//STRIP001
//STRIP001      SwPaM aPam( aInsPos );
//STRIP001
//STRIP001      for( USHORT n = 0; n < aPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          const _CmpLPt& rPt = aPosArr[ n ];
//STRIP001          aPam.GetPoint()->nNode.Assign( *rPt.pSelBox->GetSttNd()->
//STRIP001                                          EndOfSectionNode(), -1 );
//STRIP001          SwCntntNode* pCNd = aPam.GetCntntNode();
//STRIP001          USHORT nL = pCNd ? pCNd->Len() : 0;
//STRIP001          aPam.GetPoint()->nContent.Assign( pCNd, nL );
//STRIP001
//STRIP001          SwNodeIndex aSttNdIdx( *rPt.pSelBox->GetSttNd(), 1 );
//STRIP001
//STRIP001             const bool bSameLevel = n && ( bVert ?
//STRIP001                                            aPosArr[n-1].Y() == rPt.Y() :
//STRIP001                                            aPosArr[n-1].X() == rPt.X() );
//STRIP001
//STRIP001             if( bSameLevel && pTxtNd && aSttNdIdx.GetNode().IsTxtNode() )
//STRIP001          {
//STRIP001              pTxtNd->Insert( '\x20', aInsPos.nContent );
//STRIP001              aPam.SetMark();
//STRIP001              aPam.GetPoint()->nNode = aSttNdIdx;
//STRIP001              aPam.GetPoint()->nContent.Assign(
//STRIP001                              aSttNdIdx.GetNode().GetCntntNode(), 0 );
//STRIP001
//STRIP001              // alle absatzgebundenen Flys mitnehmen!
//STRIP001              _SaveFlyArr aSaveFlyArr;
//STRIP001              SwNodeIndex aIdx( rInsPosNd, -1 );
//STRIP001              {
//STRIP001                  SwNodeRange aRg( aPam.GetPoint()->nNode.GetNode(), 0,
//STRIP001                              *rPt.pSelBox->GetSttNd()->EndOfSectionNode() );
//STRIP001                  _SaveFlyInRange( aRg, aSaveFlyArr );
//STRIP001              }
//STRIP001
//STRIP001              if( pUndo )
//STRIP001                  pUndo->MoveBoxCntnt( aPam, aInsPos, aSaveFlyArr );
//STRIP001              else
//STRIP001                  pDoc->Move( aPam, aInsPos );
//STRIP001              aPam.DeleteMark();
//STRIP001              if( bCalcWidth )
//STRIP001                  nWidth += rPt.pSelBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001              if( aSaveFlyArr.Count() )
//STRIP001              {
//STRIP001                  aIdx++;
//STRIP001                  _RestFlyInRange( aSaveFlyArr, aIdx, NULL );
//STRIP001              }
//STRIP001          }
//STRIP001          else                                // Nodes moven
//STRIP001          {
//STRIP001              // ein Node muss in der Box erhalten bleiben (sonst wird beim
//STRIP001              // Move die gesamte Section geloescht)
//STRIP001              if( pUndo )
//STRIP001                  pDoc->DoUndo( FALSE );
//STRIP001              pDoc->AppendTxtNode( *aPam.GetPoint() );
//STRIP001              if( pUndo )
//STRIP001                  pDoc->DoUndo( TRUE );
//STRIP001              SwNodeRange aRg( aSttNdIdx, aPam.GetPoint()->nNode );
//STRIP001              rInsPosNd++;
//STRIP001              if( pUndo )
//STRIP001                  pUndo->MoveBoxCntnt( pDoc, aRg, rInsPosNd );
//STRIP001              else
//STRIP001                  pDoc->Move( aRg, rInsPosNd );
//STRIP001              // wo steht jetzt aInsPos ??
//STRIP001
//STRIP001              if( bCalcWidth )
//STRIP001                  bCalcWidth = FALSE;     // eine Zeile fertig
//STRIP001          }
//STRIP001
//STRIP001          // den initialen TextNode ueberspringen
//STRIP001          rInsPosNd.Assign( pDoc->GetNodes(),
//STRIP001                          rInsPosNd.GetNode().EndOfSectionIndex() - 2 );
//STRIP001          pTxtNd = rInsPosNd.GetNode().GetTxtNode();
//STRIP001          if( pTxtNd )
//STRIP001              aInsPos.nContent.Assign( pTxtNd, pTxtNd->GetTxt().Len() );
//STRIP001      }
//STRIP001
//STRIP001      // in der MergeBox sollte jetzt der gesamte Text stehen
//STRIP001      // loesche jetzt noch den initialen TextNode
//STRIP001      ASSERT( (*ppMergeBox)->GetSttIdx()+2 <
//STRIP001              (*ppMergeBox)->GetSttNd()->EndOfSectionIndex(),
//STRIP001                  "leere Box" );
//STRIP001      SwNodeIndex aIdx( *(*ppMergeBox)->GetSttNd()->EndOfSectionNode(), -1 );
//STRIP001      pDoc->GetNodes().Delete( aIdx, 1 );
//STRIP001  }
//STRIP001
//STRIP001  // setze die Breite der Box
//STRIP001  (*ppMergeBox)->GetFrmFmt()->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nWidth, 0 ));
//STRIP001  if( pUndo )
//STRIP001      pUndo->AddNewBox( (*ppMergeBox)->GetSttIdx() );
//STRIP001 }


//STRIP001 BOOL lcl_CheckCol( const _FndBox*& rpFndBox, void* pPara );

//STRIP001 BOOL lcl_CheckRow( const _FndLine*& rpFndLine, void* pPara )
//STRIP001 {
//STRIP001  ((_FndLine*)rpFndLine)->GetBoxes().ForEach( &lcl_CheckCol, pPara );
//STRIP001  return *(BOOL*)pPara;
//STRIP001 }

//STRIP001 BOOL lcl_CheckCol( const _FndBox*& rpFndBox, void* pPara )
//STRIP001 {
//STRIP001  if( !rpFndBox->GetBox()->GetSttNd() )
//STRIP001  {
//STRIP001      if( rpFndBox->GetLines().Count() !=
//STRIP001          rpFndBox->GetBox()->GetTabLines().Count() )
//STRIP001          *((BOOL*)pPara) = FALSE;
//STRIP001      else
//STRIP001          ((_FndBox*)rpFndBox)->GetLines().ForEach( &lcl_CheckRow, pPara );
//STRIP001  }
//STRIP001  // Box geschuetzt ??
//STRIP001  else if( rpFndBox->GetBox()->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001      *((BOOL*)pPara) = FALSE;
//STRIP001  return *(BOOL*)pPara;
//STRIP001 }


//STRIP001 USHORT CheckMergeSel( const SwPaM& rPam )
//STRIP001 {
//STRIP001  SwSelBoxes aBoxes;
//STRIP001 //JP 24.09.96: Merge mit wiederholenden TabellenHeadline funktioniert nicht
//STRIP001 //               richtig. Warum nicht Point 0,0 benutzen? Dann ist garantiert,
//STRIP001 //               das die 1. Headline mit drin ist.
//STRIP001  Point aPt;
//STRIP001  const SwLayoutFrm *pStart = rPam.GetCntntNode()->GetFrm(
//STRIP001                                                  &aPt )->GetUpper(),
//STRIP001                      *pEnd = rPam.GetCntntNode(FALSE)->GetFrm(
//STRIP001                                                  &aPt )->GetUpper();
//STRIP001  GetTblSel( pStart, pEnd, aBoxes );
//STRIP001  return CheckMergeSel( aBoxes );
//STRIP001 }

//STRIP001 USHORT CheckMergeSel( const SwSelBoxes& rBoxes )
//STRIP001 {
//STRIP001  USHORT eRet = TBLMERGE_NOSELECTION;
//STRIP001  if( rBoxes.Count() )
//STRIP001  {
//STRIP001      eRet = TBLMERGE_OK;
//STRIP001
//STRIP001      _FndBox aFndBox( 0, 0 );
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      const SwTableNode* pTblNd = aPara.rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001      ((SwTable&)pTblNd->GetTable()).GetTabLines().ForEach(
//STRIP001                  &_FndLineCopyCol, &aPara );
//STRIP001      if( aFndBox.GetLines().Count() )
//STRIP001      {
//STRIP001          BOOL bMergeSelOk = TRUE;
//STRIP001          _FndBox* pFndBox = &aFndBox;
//STRIP001          _FndLine* pFndLine = 0;
//STRIP001          while( pFndBox && 1 == pFndBox->GetLines().Count() )
//STRIP001          {
//STRIP001              pFndLine = pFndBox->GetLines()[0];
//STRIP001              if( 1 == pFndLine->GetBoxes().Count() )
//STRIP001                  pFndBox = pFndLine->GetBoxes()[0];
//STRIP001              else
//STRIP001                  pFndBox = 0;
//STRIP001          }
//STRIP001          if( pFndBox )
//STRIP001              pFndBox->GetLines().ForEach( &lcl_CheckRow, &bMergeSelOk );
//STRIP001          else if( pFndLine )
//STRIP001              pFndLine->GetBoxes().ForEach( &lcl_CheckCol, &bMergeSelOk );
//STRIP001          if( !bMergeSelOk )
//STRIP001              eRet = TBLMERGE_TOOCOMPLEX;
//STRIP001      }
//STRIP001      else
//STRIP001          eRet = TBLMERGE_NOSELECTION;
//STRIP001  }
//STRIP001  return eRet;
//STRIP001 }

//Ermittelt die von einer Tabellenselektion betroffenen Tabellen und die
//Union-Rechteckte der Selektionen - auch fuer aufgespaltene Tabellen.
/*N*/ SV_IMPL_PTRARR( SwSelUnions, SwSelUnion* );

/*M*/ SwTwips lcl_CalcWish( const SwLayoutFrm *pCell, long nWish,
/*M*/                                               const long nAct )
/*M*/ {
/*M*/   const SwLayoutFrm *pTmp = pCell;
/*M*/   if ( !nWish )
/*M*/       nWish = 1;
/*M*/
/*M*/ #ifdef BIDI
/*M*/   const sal_Bool bRTL = pCell->IsRightToLeft();
/*M*/   SwTwips nRet = bRTL ?
/*M*/                          nAct - pCell->Frm().Width() :
/*M*/                  0;
/*M*/ #else
/*M*/     SwTwips nRet = 0;
/*M*/ #endif
/*M*/
/*M*/
/*M*/   while ( pTmp )
/*M*/   {
/*M*/       while ( pTmp->GetPrev() )
/*M*/       {
/*M*/           pTmp = (SwLayoutFrm*)pTmp->GetPrev();
/*M*/           long nTmp = pTmp->GetFmt()->GetFrmSize().GetWidth();
/*M*/ #ifdef BIDI
/*M*/             nRet += ( bRTL ? ( -1 ) : 1 ) * nTmp * nAct / nWish;
/*M*/ #else
/*M*/             nRet += nTmp * nAct / nWish;
/*M*/ #endif
/*M*/       }
/*M*/       pTmp = pTmp->GetUpper()->GetUpper();
/*M*/       if ( pTmp && !pTmp->IsCellFrm() )
/*M*/           pTmp = 0;
/*M*/   }
/*M*/   return nRet;
/*M*/ }

/*  MA: 20. Sep. 93 wird nicht mehr gebraucht.
static const SwLayoutFrm *GetPrevCell( const SwLayoutFrm *pCell )
{
    const SwLayoutFrm *pLay = pCell->GetPrevLayoutLeaf();
    if ( pLay && pLay->IsLayoutFrm() && !pLay->IsTab() )
    {
        //GetPrevLayoutLeaf() liefert ggf. auch die Umgebung einer Tab zurueck
        //(naehmlich genau dann, wenn die Zelle noch Vorgaenger hat).
        const SwFrm *pFrm = pLay->Lower();
        while ( pFrm->GetNext() )
            pFrm = pFrm->GetNext();
        pLay = pFrm->IsTabFrm() ? (SwLayoutFrm*)pFrm : 0;
    }
    if ( pLay && pLay->IsTabFrm() )
    {
        //GetPrevLayoutLeaf() liefert ggf. auch Tabellen zurueck die letzte
        //Zelle dieser Tabelle ist das das gesuchte Blatt.
        pLay = ((SwTabFrm*)pLay)->FindLastCntnt()->GetUpper();
        while ( !pLay->IsCellFrm() )
            pLay = pLay->GetUpper();
    }
    return pLay;
}
*/

/*N*/ void lcl_FindStartEndRow( const SwLayoutFrm *&rpStart,
/*N*/                            const SwLayoutFrm *&rpEnd,
/*N*/                            const int bChkProtected )
/*N*/ {
/*N*/   //Start an den Anfang seiner Zeile setzen.
/*N*/   //End an das Ende seiner Zeile setzen.
/*N*/   rpStart = (SwLayoutFrm*)rpStart->GetUpper()->Lower();
/*N*/   while ( rpEnd->GetNext() )
/*?*/       rpEnd = (SwLayoutFrm*)rpEnd->GetNext();
/*N*/
/*N*/   SvPtrarr aSttArr( 8, 8 ), aEndArr( 8, 8 );
/*N*/   const SwLayoutFrm *pTmp;
/*N*/   for( pTmp = rpStart; (FRM_CELL|FRM_ROW) & pTmp->GetType();
/*N*/               pTmp = pTmp->GetUpper() )
/*N*/   {
/*N*/       void* p = (void*)pTmp;
/*N*/       aSttArr.Insert( p, 0 );
/*N*/   }
/*N*/   for( pTmp = rpEnd; (FRM_CELL|FRM_ROW) & pTmp->GetType();
/*N*/               pTmp = pTmp->GetUpper() )
/*N*/   {
/*N*/       void* p = (void*)pTmp;
/*N*/       aEndArr.Insert( p, 0 );
/*N*/   }
/*N*/
/*N*/   for( USHORT n = 0; n < aEndArr.Count() && n < aSttArr.Count(); ++n )
/*N*/       if( aSttArr[ n ] != aEndArr[ n ] )
/*N*/       {
/*?*/           // first unequal line or box - all odds are
/*?*/           if( n & 1 )                 // 1, 3, 5, ... are boxes
/*?*/           {
/*?*/               rpStart = (SwLayoutFrm*)aSttArr[ n ];
/*?*/               rpEnd = (SwLayoutFrm*)aEndArr[ n ];
/*?*/           }
/*?*/           else                                // 0, 2, 4, ... are lines
/*?*/           {
/*?*/               // check if start & end line are the first & last Line of the
/*?*/               // box. If not return these cells.
/*?*/               // Else the hole line with all Boxes has to be deleted.
/*?*/               rpStart = (SwLayoutFrm*)aSttArr[ n+1 ];
/*?*/               rpEnd = (SwLayoutFrm*)aEndArr[ n+1 ];
/*?*/               if( n )
/*?*/               {
/*?*/                   const SwCellFrm* pCellFrm = (SwCellFrm*)aSttArr[ n-1 ];
/*?*/                   const SwTableLines& rLns = pCellFrm->
/*?*/                                               GetTabBox()->GetTabLines();
/*?*/                   if( rLns[ 0 ] == ((SwRowFrm*)aSttArr[ n ])->GetTabLine() &&
/*?*/                       rLns[ rLns.Count() - 1 ] ==
/*?*/                                   ((SwRowFrm*)aEndArr[ n ])->GetTabLine() )
/*?*/                   {
/*?*/                       rpStart = rpEnd = pCellFrm;
/*?*/                       while ( rpStart->GetPrev() )
/*?*/                           rpStart = (SwLayoutFrm*)rpStart->GetPrev();
/*?*/                       while ( rpEnd->GetNext() )
/*?*/                           rpEnd = (SwLayoutFrm*)rpEnd->GetNext();
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           break;
/*N*/       }
/*N*/
/*N*/   if( !bChkProtected )    // geschuetzte Zellen beachten ?
/*N*/       return;
/*N*/
/*N*/
/*?*/   //Anfang und Ende duerfen nicht auf geschuetzten Zellen liegen.
/*?*/   while ( rpStart->GetFmt()->GetProtect().IsCntntProtected() )
/*?*/       rpStart = (SwLayoutFrm*)rpStart->GetNext();
/*?*/   while ( rpEnd->GetFmt()->GetProtect().IsCntntProtected() )
/*?*/       rpEnd = (SwLayoutFrm*)rpEnd->GetPrev();
/*N*/ }


/*M*/ void lcl_FindStartEndCol( const SwLayoutFrm *&rpStart,
/*M*/                            const SwLayoutFrm *&rpEnd,
/*M*/                            const int bChkProtected )
/*M*/ {
/*M*/   //Start und End senkrecht bis an den Rand der Tabelle denken; es muss
/*M*/   //die Gesamttabelle betrachtet werden, also inklusive Masters und
/*M*/   //Follows.
/*M*/   //Fuer den Start brauchen wir den Mutter-TabellenFrm.
/*M*/     if( !rpStart )
/*M*/         return;
/*M*/   const SwTabFrm *pOrg = rpStart->FindTabFrm();
/*M*/   const SwTabFrm *pTab = pOrg;
/*M*/
/*M*/   SWRECTFN( pTab )
/*M*/
/*M*/ #ifdef BIDI
/*M*/     sal_Bool bRTL = pTab->IsRightToLeft();
/*M*/ #endif
/*M*/
/*M*/   const long nWish = pOrg->GetFmt()->GetFrmSize().GetWidth();
/*M*/   while ( pTab->IsFollow() )
/*M*/   {
/*M*/       const SwFrm *pTmp = pTab->FindPrev();
/*M*/       ASSERT( pTmp->IsTabFrm(), "Vorgaenger vom Follow nicht der Master." );
/*M*/       pTab = (const SwTabFrm*)pTmp;
/*M*/   }
/*M*/
/*M*/     SwTwips nPrtWidth = (pTab->Prt().*fnRect->fnGetWidth)();
/*M*/     const SwTwips nSX = ::binfilter::lcl_CalcWish( rpStart, nWish, nPrtWidth ) +
/*M*/                       (pTab->*fnRect->fnGetPrtLeft)();
/*M*/
/*M*/   const SwTwips nSX2= nSX + (rpStart->GetFmt()->GetFrmSize().GetWidth() *
/*M*/                                           nPrtWidth / nWish);
/*M*/
/*M*/   const SwLayoutFrm *pTmp = pTab->FirstCell();
/*M*/
/*M*/ #ifdef BIDI
/*M*/   while ( pTmp &&
/*M*/           (!pTmp->IsCellFrm() ||
/*M*/              ( ( ! bRTL && (pTmp->Frm().*fnRect->fnGetLeft)() < nSX &&
/*M*/                            (pTmp->Frm().*fnRect->fnGetRight)()< nSX2 ) ||
/*M*/                    bRTL && (pTmp->Frm().*fnRect->fnGetLeft)() > nSX &&
/*M*/                            (pTmp->Frm().*fnRect->fnGetRight)()> nSX2 ) ) )
/*M*/ #else
/*M*/     while ( pTmp &&
/*M*/             (!pTmp->IsCellFrm() ||
/*M*/              ( (pTmp->Frm().*fnRect->fnGetLeft)() < nSX &&
/*M*/                (pTmp->Frm().*fnRect->fnGetRight)()< nSX2 ) ) )
/*M*/ #endif
/*M*/         pTmp = pTmp->GetNextLayoutLeaf();
/*M*/
/*M*/   if ( pTmp )
/*M*/       rpStart = pTmp;
/*M*/
/*M*/   pTab = pOrg;
/*M*/   while ( pTab->GetFollow() )
/*M*/       pTab = pTab->GetFollow();
/*M*/
/*M*/   nPrtWidth = (pTab->Prt().*fnRect->fnGetWidth)();
/*M*/   const SwTwips nEX = ::binfilter::lcl_CalcWish( rpEnd, nWish, nPrtWidth ) +
/*M*/                         (pTab->*fnRect->fnGetPrtLeft)();
/*M*/   rpEnd = pTab->FindLastCntnt()->GetUpper();
/*M*/   while( !rpEnd->IsCellFrm() )
/*M*/       rpEnd = rpEnd->GetUpper();
/*M*/
/*M*/ #ifdef BIDI
/*M*/     while ( (   bRTL && (rpEnd->Frm().*fnRect->fnGetLeft)() < nEX ) ||
/*M*/             ( ! bRTL && (rpEnd->Frm().*fnRect->fnGetLeft)() > nEX ) )
/*M*/ #else
/*M*/     while ( (rpEnd->Frm().*fnRect->fnGetLeft)() > nEX ) )
/*M*/ #endif
/*M*/     {
/*M*/         const SwLayoutFrm* pTmp = rpEnd->GetPrevLayoutLeaf();
/*M*/         if( !pTmp || !pTab->IsAnLower( pTmp ) )
/*M*/             break;
/*M*/         rpEnd = pTmp;
/*M*/     }
/*M*/
/*M*/   if( !bChkProtected )    // geschuetzte Zellen beachten ?
/*M*/       return;
/*M*/
/*M*/   //Anfang und Ende duerfen nicht auf geschuetzten Zellen liegen.
/*M*/   //Also muss ggf. nocheinmal rueckwaerts gesucht werden.
/*M*/   while ( rpStart->GetFmt()->GetProtect().IsCntntProtected() )
/*M*/   {
/*M*/       const SwLayoutFrm *pTmp = rpStart;
/*M*/       pTmp = pTmp->GetNextLayoutLeaf();
/*M*/       while ( pTmp && (pTmp->Frm().*fnRect->fnGetLeft)() > nEX )//erstmal die Zeile ueberspr.
/*M*/           pTmp = pTmp->GetNextLayoutLeaf();
/*M*/       while ( pTmp && (pTmp->Frm().*fnRect->fnGetLeft)() < nSX &&
/*M*/                       (pTmp->Frm().*fnRect->fnGetRight)()< nSX2 )
/*M*/           pTmp = pTmp->GetNextLayoutLeaf();
/*M*/       const SwTabFrm *pTab = rpStart->FindTabFrm();
/*M*/       if ( !pTab->IsAnLower( pTmp ) )
/*M*/       {
/*M*/           pTab = pTab->GetFollow();
/*M*/           rpStart = pTab->FirstCell();
/*M*/           while ( (rpStart->Frm().*fnRect->fnGetLeft)() < nSX &&
/*M*/                   (rpStart->Frm().*fnRect->fnGetRight)()< nSX2 )
/*M*/               rpStart = rpStart->GetNextLayoutLeaf();
/*M*/       }
/*M*/       else
/*M*/           rpStart = pTmp;
/*M*/   }
/*M*/   while ( rpEnd->GetFmt()->GetProtect().IsCntntProtected() )
/*M*/   {
/*M*/       const SwLayoutFrm *pTmp = rpEnd;
/*M*/       pTmp = pTmp->GetPrevLayoutLeaf();
/*M*/       while ( pTmp && (pTmp->Frm().*fnRect->fnGetLeft)() < nEX )//erstmal die Zeile ueberspr.
/*M*/           pTmp = pTmp->GetPrevLayoutLeaf();
/*M*/       while ( pTmp && (pTmp->Frm().*fnRect->fnGetLeft)() > nEX )
/*M*/           pTmp = pTmp->GetPrevLayoutLeaf();
/*M*/       const SwTabFrm *pTab = rpEnd->FindTabFrm();
/*M*/       if ( !pTmp || !pTab->IsAnLower( pTmp ) )
/*M*/       {
/*M*/           pTab = (const SwTabFrm*)pTab->FindPrev();
/*M*/           ASSERT( pTab->IsTabFrm(), "Vorgaenger vom Follow nicht der Master.");
/*M*/           rpEnd = pTab->FindLastCntnt()->GetUpper();
/*M*/           while( !rpEnd->IsCellFrm() )
/*M*/               rpEnd = rpEnd->GetUpper();
/*M*/           while ( (rpEnd->Frm().*fnRect->fnGetLeft)() > nEX )
/*M*/               rpEnd = rpEnd->GetPrevLayoutLeaf();
/*M*/       }
/*M*/       else
/*M*/           rpEnd = pTmp;
/*M*/   }
/*M*/ }


/*M*/ void MakeSelUnions( SwSelUnions& rUnions, const SwLayoutFrm *pStart,
/*M*/                   const SwLayoutFrm *pEnd, const SwTblSearchType eSearchType )
/*M*/ {
/*M*/   while ( !pStart->IsCellFrm() )
/*M*/       pStart = pStart->GetUpper();
/*M*/   while ( !pEnd->IsCellFrm() )
/*M*/       pEnd = pEnd->GetUpper();
/*M*/
/*M*/   const SwTabFrm *pTable = pStart->FindTabFrm();
/*M*/   const SwTabFrm *pEndTable = pEnd->FindTabFrm();
/*M*/     if( !pTable || !pEndTable )
/*M*/         return;
/*M*/   BOOL bExchange = FALSE;
/*M*/
/*M*/   if ( pTable != pEndTable )
/*M*/   {
/*M*/       if ( !pTable->IsAnFollow( pEndTable ) )
/*M*/       {
/*M*/           ASSERT( pEndTable->IsAnFollow( pTable ), "Tabkette verknotet." );
/*M*/           bExchange = TRUE;
/*M*/       }
/*M*/   }
/*M*/ #ifdef VERTICAL_LAYOUT
/*M*/     else
/*M*/     {
/*M*/         SWRECTFN( pStart )
/*M*/         long nSttTop = (pStart->Frm().*fnRect->fnGetTop)();
/*M*/         long nEndTop = (pEnd->Frm().*fnRect->fnGetTop)();
/*M*/         if( nSttTop == nEndTop )
/*M*/         {
/*M*/             if( (pStart->Frm().*fnRect->fnGetLeft)() >
/*M*/                 (pEnd->Frm().*fnRect->fnGetLeft)() )
/*M*/                 bExchange = TRUE;
/*M*/         }
/*M*/         else if( bVert == ( nSttTop < nEndTop ) )
/*M*/             bExchange = TRUE;
/*M*/     }
/*M*/ #else
/*M*/   else if ( pStart->Frm().Top() > pEnd->Frm().Top() ||
/*M*/            (pStart->Frm().Top() == pEnd->Frm().Top() &&
/*M*/             pStart->Frm().Left() > pEnd->Frm().Left()) )
/*M*/       bExchange = TRUE;
/*M*/ #endif
/*M*/   if ( bExchange )
/*M*/   {
/*M*/       const SwLayoutFrm *pTmp = pStart;
/*M*/       pStart = pEnd;
/*M*/       pEnd = pTmp;
/*M*/       //pTable und pEndTable nicht umsortieren, werden unten neu gesetzt.
/*M*/       //MA: 28. Dec. 93 Bug: 5190
/*M*/   }
/*M*/
/*M*/   //Start und End sind jetzt huebsch sortiert, jetzt muessen sie falls
/*M*/   //erwuenscht noch versetzt werden.
/*M*/   if( TBLSEARCH_ROW == ((~TBLSEARCH_PROTECT ) & eSearchType ) )
/*M*/       ::binfilter::lcl_FindStartEndRow( pStart, pEnd, TBLSEARCH_PROTECT & eSearchType );
/*M*/   else if( TBLSEARCH_COL == ((~TBLSEARCH_PROTECT ) & eSearchType ) )
/*M*/       ::binfilter::lcl_FindStartEndCol( pStart, pEnd, TBLSEARCH_PROTECT & eSearchType );
/*M*/
/*M*/   //neu besorgen, da sie jetzt verschoben sind. MA: 28. Dec. 93 Bug 5190
/*M*/   pTable = pStart->FindTabFrm();
/*M*/   pEndTable = pEnd->FindTabFrm();
/*M*/
/*M*/   const FASTBOOL bRepeat = pTable->GetTable()->IsHeadlineRepeat();
/*M*/
/*M*/   const long nStSz = pStart->GetFmt()->GetFrmSize().GetWidth();
/*M*/   const long nEdSz = pEnd->GetFmt()->GetFrmSize().GetWidth();
/*M*/   const long nWish = Max( 1L, pTable->GetFmt()->GetFrmSize().GetWidth() );
/*M*/   while ( pTable )
/*M*/   {
/*M*/ #ifdef VERTICAL_LAYOUT
/*M*/         SWRECTFN( pTable )
/*M*/         const long nOfst = (pTable->*fnRect->fnGetPrtLeft)();
/*M*/         const long nPrtWidth = (pTable->Prt().*fnRect->fnGetWidth)();
/*M*/         long nSt1 = ::binfilter::lcl_CalcWish( pStart, nWish, nPrtWidth ) + nOfst;
/*M*/         long nEd1 = ::binfilter::lcl_CalcWish( pEnd,   nWish, nPrtWidth ) + nOfst;
/*M*/
/*M*/         if ( nSt1 <= nEd1 )
/*M*/             nEd1 += (long)((nEdSz * nPrtWidth) / nWish) - 1;
/*M*/       else
/*M*/             nSt1 += (long)((nStSz * nPrtWidth) / nWish) - 1;
/*M*/
/*M*/         long nSt2;
/*M*/         long nEd2;
/*M*/         if( pTable->IsAnLower( pStart ) )
/*M*/             nSt2 = (pStart->Frm().*fnRect->fnGetTop)();
/*M*/         else
/*M*/             nSt2 = (pTable->Frm().*fnRect->fnGetTop)();
/*M*/         if( pTable->IsAnLower( pEnd ) )
/*M*/             nEd2 = (pEnd->Frm().*fnRect->fnGetBottom)();
/*M*/         else
/*M*/             nEd2 = (pTable->Frm().*fnRect->fnGetBottom)();
/*M*/         Point aSt, aEd;
/*M*/         if( nSt1 > nEd1 )
/*M*/         {
/*M*/             long nTmp = nSt1;
/*M*/             nSt1 = nEd1;
/*M*/             nEd1 = nTmp;
/*M*/         }
/*M*/         if( nSt2 > nEd2 )
/*M*/         {
/*M*/             long nTmp = nSt2;
/*M*/             nSt2 = nEd2;
/*M*/             nEd2 = nTmp;
/*M*/         }
/*M*/         if( bVert )
/*M*/         {
/*M*/             aSt = Point( nSt2, nSt1 );
/*M*/             aEd = Point( nEd2, nEd1 );
/*M*/         }
/*M*/         else
/*M*/         {
/*M*/             aSt = Point( nSt1, nSt2 );
/*M*/             aEd = Point( nEd1, nEd2 );
/*M*/         }
/*M*/ #else
/*M*/       const long nOfst = pTable->Frm().Left() + pTable->Prt().Left();
/*M*/       long nSt = ::binfilter::lcl_CalcWish( pStart, nWish, pTable->Prt().Width() ) + nOfst;
/*M*/       long nEd = ::binfilter::lcl_CalcWish( pEnd,   nWish, pTable->Prt().Width() ) + nOfst;
/*M*/
/*M*/       if ( nSt <= nEd )
/*M*/           nEd += (long)((nEdSz * pTable->Prt().Width()) / nWish) - 1;
/*M*/       else
/*M*/           nSt += (long)((nStSz * pTable->Prt().Width()) / nWish) - 1;
/*M*/
/*M*/       Point aSt( nSt, pStart->Frm().Top() ),
/*M*/             aEd( nEd, pEnd->Frm().Bottom() );
/*M*/
/*M*/       if ( !pTable->IsAnLower( pStart ) )
/*M*/           aSt.Y() = pTable->Frm().Top();
/*M*/       if ( !pTable->IsAnLower( pEnd ) )
/*M*/           aEd.Y() = pTable->Frm().Bottom();
/*M*/ #endif
/*M*/
/*M*/       SwRect aUnion( aSt, aEd );
/*M*/       aUnion.Justify();
/*M*/
/*M*/       // fuers
/*M*/       if( !(TBLSEARCH_NO_UNION_CORRECT & eSearchType ))
/*M*/       {
/*M*/           //Leider ist die Union jetzt mit Rundungsfehlern behaftet und dadurch
/*M*/           //wuerden beim Split/Merge fehlertraechtige Umstaende entstehen.
/*M*/           //Um dies zu vermeiden werden jetzt fuer die Table die erste und
/*M*/           //letzte Zelle innerhalb der Union ermittelt und aus genau deren
/*M*/           //Werten wird die Union neu gebildet.
/*M*/           const SwLayoutFrm *pRow = (SwLayoutFrm*)pTable->Lower();
/*M*/           if ( bRepeat && pRow && pTable->IsFollow() )
/*M*/               pRow = (SwLayoutFrm*)pRow->GetNext();
/*M*/           while ( pRow && !pRow->Frm().IsOver( aUnion ) )
/*M*/               pRow = (SwLayoutFrm*)pRow->GetNext();
/*M*/           const SwLayoutFrm *pFirst = pRow ? pRow->FirstCell() : 0;
/*M*/           while ( pFirst && !::binfilter::IsFrmInTblSel( aUnion, pFirst ) )
/*M*/           {
/*M*/               if ( pFirst->GetNext() )
/*M*/               {
/*M*/                   pFirst = (const SwLayoutFrm*)pFirst->GetNext();
/*M*/                   if ( pFirst->Lower()->IsRowFrm() )
/*M*/                       pFirst = pFirst->FirstCell();
/*M*/               }
/*M*/               else
/*M*/                   pFirst = ::binfilter::lcl_FindNextCellFrm( pFirst );
/*M*/           }
/*M*/           const SwLayoutFrm *pLast = ::binfilter::lcl_FindCellFrm( pTable->FindLastCntnt()->GetUpper());
/*M*/           while ( pLast && !::binfilter::IsFrmInTblSel( aUnion, pLast ) )
/*M*/               pLast = ::binfilter::lcl_FindCellFrm( pLast->GetPrevLayoutLeaf() );
/*M*/
/*M*/           if ( pFirst && pLast ) //Robust
/*M*/ #ifdef VERTICAL_LAYOUT
/*M*/             {
/*M*/                 aUnion = pFirst->Frm();
/*M*/                 aUnion.Union( pLast->Frm() );
/*M*/             }
/*M*/ #else
/*M*/               aUnion = SwRect( pFirst->Frm().Pos(),
/*M*/                                Point( pLast->Frm().Right(),
/*M*/                                        pLast->Frm().Bottom() ) );
/*M*/ #endif
/*M*/           else
/*M*/               aUnion.Width( 0 );
/*M*/       }
/*M*/
/*M*/       if( (aUnion.*fnRect->fnGetWidth)() )
/*M*/       {
/*M*/           SwSelUnion *pTmp = new SwSelUnion( aUnion, (SwTabFrm*)pTable );
/*M*/           rUnions.C40_INSERT( SwSelUnion, pTmp, rUnions.Count() );
/*M*/       }
/*M*/
/*M*/       pTable = pTable->GetFollow();
/*M*/       if ( pTable != pEndTable && pEndTable->IsAnFollow( pTable ) )
/*M*/           pTable = 0;
/*M*/   }
/*M*/ }

//STRIP001 BOOL CheckSplitCells( const SwCrsrShell& rShell, USHORT nDiv,
//STRIP001                      const SwTblSearchType eSearchType )
//STRIP001 {
//STRIP001  if( !rShell.IsTableMode() )
//STRIP001      rShell.GetCrsr();
//STRIP001
//STRIP001  const SwShellCrsr *pCrsr = rShell.GetTableCrsr();
//STRIP001  if( !pCrsr )
//STRIP001      pCrsr = (SwShellCrsr*)*rShell.GetSwCrsr( FALSE );
//STRIP001
//STRIP001  return CheckSplitCells( *pCrsr, nDiv, eSearchType );
//STRIP001 }

//STRIP001 BOOL CheckSplitCells( const SwCursor& rCrsr, USHORT nDiv,
//STRIP001                      const SwTblSearchType eSearchType )
//STRIP001 {
//STRIP001  if( 1 >= nDiv )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nMinValue = nDiv * MINLAY;
//STRIP001
//STRIP001  //Start- und Endzelle besorgen und den naechsten fragen.
//STRIP001  Point aPtPos, aMkPos;
//STRIP001  const SwShellCrsr* pShCrsr = rCrsr;
//STRIP001  if( pShCrsr )
//STRIP001  {
//STRIP001      aPtPos = pShCrsr->GetPtPos();
//STRIP001      aMkPos = pShCrsr->GetMkPos();
//STRIP001  }
//STRIP001  const SwLayoutFrm *pStart = rCrsr.GetCntntNode()->GetFrm(
//STRIP001                              &aPtPos )->GetUpper(),
//STRIP001                    *pEnd   = rCrsr.GetCntntNode(FALSE)->GetFrm(
//STRIP001                              &aMkPos )->GetUpper();
//STRIP001
//STRIP001  SWRECTFN( pStart )
//STRIP001
//STRIP001  //Zuerst lassen wir uns die Tabellen und die Rechtecke heraussuchen.
//STRIP001  SwSelUnions aUnions;
//STRIP001
//STRIP001  ::MakeSelUnions( aUnions, pStart, pEnd, eSearchType );
//STRIP001
//STRIP001  //Muss ein HeadlineRepeat beachtet werden?
//STRIP001  const BOOL bRepeat = pStart->FindTabFrm()->GetTable()->IsHeadlineRepeat();
//STRIP001
//STRIP001  //Jetzt zu jedem Eintrag die Boxen herausfischen und uebertragen.
//STRIP001  for ( USHORT i = 0; i < aUnions.Count(); ++i )
//STRIP001  {
//STRIP001      SwSelUnion *pUnion = aUnions[i];
//STRIP001      const SwTabFrm *pTable = pUnion->GetTable();
//STRIP001
//STRIP001      const SwLayoutFrm *pRow = (const SwLayoutFrm*)pTable->Lower();
//STRIP001      //Wenn die Row eine wiederholte Headline ist wird sie nicht
//STRIP001      //beachtet.
//STRIP001      if ( bRepeat && pTable->IsFollow() )
//STRIP001          pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001
//STRIP001      while ( pRow )
//STRIP001      {
//STRIP001          if ( pRow->Frm().IsOver( pUnion->GetUnion() ) )
//STRIP001          {
//STRIP001              const SwLayoutFrm *pCell = pRow->FirstCell();
//STRIP001
//STRIP001              while ( pCell && pRow->IsAnLower( pCell ) )
//STRIP001              {
//STRIP001                  ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
//STRIP001                  if( ::IsFrmInTblSel( pUnion->GetUnion(), pCell ) )
//STRIP001                  {
//STRIP001                         if( (pCell->Frm().*fnRect->fnGetWidth)() < nMinValue )
//STRIP001                          return FALSE;
//STRIP001                  }
//STRIP001
//STRIP001                  if ( pCell->GetNext() )
//STRIP001                  {
//STRIP001                      pCell = (const SwLayoutFrm*)pCell->GetNext();
//STRIP001                      if ( pCell->Lower()->IsRowFrm() )
//STRIP001                          pCell = pCell->FirstCell();
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pCell = ::lcl_FindNextCellFrm( pCell );
//STRIP001              }
//STRIP001          }
//STRIP001          pRow = (const SwLayoutFrm*)pRow->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

// -------------------------------------------------------------------
// Diese Klassen kopieren die aktuelle Tabellen-Selektion (rBoxes)
// unter Beibehaltung der Tabellen-Struktur in eine eigene Struktur
// neu: SS zum gezielten Loeschen/Retaurieren des Layouts.

//STRIP001 void lcl_InsertRow( SwTableLine &rLine, SwLayoutFrm *pUpper, SwFrm *pSibling )
//STRIP001 {
//STRIP001  SwRowFrm *pRow = new SwRowFrm( rLine );
//STRIP001  if ( pUpper->IsTabFrm() && ((SwTabFrm*)pUpper)->IsFollow() )
//STRIP001  {
//STRIP001      ((SwTabFrm*)pUpper)->FindMaster()->InvalidatePos(); //kann die Zeile vielleicht aufnehmen
//STRIP001      if ( ((SwTabFrm*)pUpper)->GetTable()->IsHeadlineRepeat() &&
//STRIP001           pSibling && !pSibling->GetPrev() )
//STRIP001      {
//STRIP001          //Nicht vor die Headline-Wiederholung pasten.
//STRIP001          pSibling = pSibling->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001  pRow->Paste( pUpper, pSibling );
//STRIP001  pRow->RegistFlys();
//STRIP001 }


//STRIP001 BOOL _FndBoxCopyCol( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  _FndPara* pFndPara = (_FndPara*)pPara;
//STRIP001  _FndBox* pFndBox = new _FndBox( (SwTableBox*)rpBox, pFndPara->pFndLine );
//STRIP001  if( rpBox->GetTabLines().Count() )
//STRIP001  {
//STRIP001      _FndPara aPara( *pFndPara, pFndBox );
//STRIP001      pFndBox->GetBox()->GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001      if( !pFndBox->GetLines().Count() )
//STRIP001      {
//STRIP001          delete pFndBox;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwTableBoxPtr pSrch = (SwTableBoxPtr)rpBox;
//STRIP001      USHORT nFndPos;
//STRIP001      if( !pFndPara->rBoxes.Seek_Entry( pSrch, &nFndPos ))
//STRIP001      {
//STRIP001          delete pFndBox;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  pFndPara->pFndLine->GetBoxes().C40_INSERT( _FndBox, pFndBox,
//STRIP001                  pFndPara->pFndLine->GetBoxes().Count() );
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ BOOL _FndLineCopyCol( const SwTableLine*& rpLine, void* pPara )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  _FndPara* pFndPara = (_FndPara*)pPara;
//STRIP001  _FndLine* pFndLine = new _FndLine( (SwTableLine*)rpLine, pFndPara->pFndBox );
//STRIP001  _FndPara aPara( *pFndPara, pFndLine );
//STRIP001  pFndLine->GetLine()->GetTabBoxes().ForEach( &_FndBoxCopyCol, &aPara );
//STRIP001  if( pFndLine->GetBoxes().Count() )
//STRIP001  {
//STRIP001      pFndPara->pFndBox->GetLines().C40_INSERT( _FndLine, pFndLine,
//STRIP001              pFndPara->pFndBox->GetLines().Count() );
//STRIP001  }
//STRIP001  else
//STRIP001      delete pFndLine;
/*N*/   return TRUE;
/*N*/ }

//STRIP001 void _FndBox::SetTableLines( const SwSelBoxes &rBoxes, const SwTable &rTable )
//STRIP001 {
//STRIP001  //Pointer auf die Lines vor und hinter den zu verarbeitenden Bereich
//STRIP001  //setzen. Wenn die erste/letzte Zeile in den Bereich eingeschlossen
//STRIP001  //sind, so bleiben die Pointer eben einfach 0.
//STRIP001  //Gesucht werden zunachst die Positionen der ersten/letzten betroffenen
//STRIP001  //Line im Array der SwTable. Damit die 0 fuer 'keine Line' verwand werden
//STRIP001  //kann werden die Positionen um 1 nach oben versetzt!
//STRIP001
//STRIP001  USHORT nStPos = USHRT_MAX;
//STRIP001  USHORT nEndPos= 0;
//STRIP001
//STRIP001  for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001  {
//STRIP001      SwTableLine *pLine = rBoxes[i]->GetUpper();
//STRIP001      while ( pLine->GetUpper() )
//STRIP001          pLine = pLine->GetUpper()->GetUpper();
//STRIP001      const USHORT nPos = rTable.GetTabLines().GetPos(
//STRIP001                  (const SwTableLine*&)pLine ) + 1;
//STRIP001
//STRIP001      ASSERT( nPos != USHRT_MAX, "TableLine not found." );
//STRIP001
//STRIP001      if( nStPos > nPos )
//STRIP001          nStPos = nPos;
//STRIP001
//STRIP001      if( nEndPos < nPos )
//STRIP001          nEndPos = nPos;
//STRIP001  }
//STRIP001  if ( nStPos > 1 )
//STRIP001      pLineBefore = rTable.GetTabLines()[nStPos - 2];
//STRIP001  if ( nEndPos < rTable.GetTabLines().Count() )
//STRIP001      pLineBehind = rTable.GetTabLines()[nEndPos];
//STRIP001 }

//STRIP001 void _FndBox::SetTableLines( const SwTable &rTable )
//STRIP001 {
//STRIP001  // Pointer auf die Lines vor und hinter den zu verarbeitenden Bereich
//STRIP001  // setzen. Wenn die erste/letzte Zeile in den Bereich eingeschlossen
//STRIP001  // sind, so bleiben die Pointer eben einfach 0.
//STRIP001  // Die Positionen der ersten/letzten betroffenen Line im Array der
//STRIP001  // SwTable steht in der FndBox. Damit die 0 fuer 'keine Line' verwand
//STRIP001  // werdenkann werden die Positionen um 1 nach oben versetzt!
//STRIP001
//STRIP001  if( !GetLines().Count() )
//STRIP001      return;
//STRIP001
//STRIP001  SwTableLine* pTmpLine = GetLines()[0]->GetLine();
//STRIP001  USHORT nPos = rTable.GetTabLines().C40_GETPOS( SwTableLine, pTmpLine );
//STRIP001  ASSERT( USHRT_MAX != nPos, "Line steht nicht in der Tabelle" );
//STRIP001  if( nPos )
//STRIP001      pLineBefore = rTable.GetTabLines()[ nPos - 1 ];
//STRIP001
//STRIP001  pTmpLine = GetLines()[GetLines().Count()-1]->GetLine();
//STRIP001  nPos = rTable.GetTabLines().C40_GETPOS( SwTableLine, pTmpLine );
//STRIP001  ASSERT( USHRT_MAX != nPos, "Line steht nicht in der Tabelle" );
//STRIP001  if( ++nPos < rTable.GetTabLines().Count() )
//STRIP001      pLineBehind = rTable.GetTabLines()[nPos];
//STRIP001 }

//STRIP001 inline void UnsetFollow( SwFlowFrm *pTab )
//STRIP001 {
//STRIP001  pTab->bIsFollow = FALSE;
//STRIP001 }

//STRIP001 void _FndBox::DelFrms( SwTable &rTable )
//STRIP001 {
//STRIP001  //Alle Lines zwischen pLineBefore und pLineBehind muessen aus dem
//STRIP001  //Layout ausgeschnitten und geloescht werden.
//STRIP001  //Entstehen dabei leere Follows so muessen diese vernichtet werden.
//STRIP001  //Wird ein Master vernichtet, so muss der Follow Master werden.
//STRIP001  //Ein TabFrm muss immer uebrigbleiben.
//STRIP001
//STRIP001  USHORT nStPos = 0;
//STRIP001  USHORT nEndPos= rTable.GetTabLines().Count() - 1;
//STRIP001  if ( pLineBefore )
//STRIP001  {
//STRIP001      nStPos = rTable.GetTabLines().GetPos(
//STRIP001                      (const SwTableLine*&)pLineBefore );
//STRIP001      ASSERT( nStPos != USHRT_MAX, "Fuchs Du hast die Line gestohlen!" );
//STRIP001      ++nStPos;
//STRIP001  }
//STRIP001  if ( pLineBehind )
//STRIP001  {
//STRIP001      nEndPos = rTable.GetTabLines().GetPos(
//STRIP001                      (const SwTableLine*&)pLineBehind );
//STRIP001      ASSERT( nEndPos != USHRT_MAX, "Fuchs Du hast die Line gestohlen!" );
//STRIP001      --nEndPos;
//STRIP001  }
//STRIP001  for ( USHORT i = nStPos; i <= nEndPos; ++i)
//STRIP001  {
//STRIP001      SwFrmFmt *pFmt = rTable.GetTabLines()[i]->GetFrmFmt();
//STRIP001      SwClientIter aIter( *pFmt );
//STRIP001      SwClient* pLast = aIter.GoStart();
//STRIP001      if( pLast )
//STRIP001      {
//STRIP001          do {
//STRIP001              SwFrm *pFrm = PTR_CAST( SwFrm, pLast );
//STRIP001              if ( pFrm &&
//STRIP001                   ((SwRowFrm*)pFrm)->GetTabLine() == rTable.GetTabLines()[i] )
//STRIP001              {
//STRIP001                  BOOL bDel = TRUE;
//STRIP001                  SwTabFrm *pUp = !pFrm->GetPrev() && !pFrm->GetNext() ?
//STRIP001                                          (SwTabFrm*)pFrm->GetUpper() : 0;
//STRIP001                  if ( !pUp )
//STRIP001                  {
//STRIP001                      if ( ((SwTabFrm*)pFrm->GetUpper())->GetTable()->IsHeadlineRepeat() &&
//STRIP001                           ((SwTabFrm*)pFrm->GetUpper())->IsFollow() )
//STRIP001                      {
//STRIP001                          if ( !pFrm->GetNext() && pFrm->GetPrev() &&
//STRIP001                               !pFrm->GetPrev()->GetPrev() )
//STRIP001                          {
//STRIP001                              pUp = (SwTabFrm*)pFrm->GetUpper();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( pUp )
//STRIP001                  {
//STRIP001                      SwTabFrm *pFollow = pUp->GetFollow();
//STRIP001                      SwTabFrm *pPrev   = pUp->IsFollow() ? pUp : 0;
//STRIP001                      if ( pPrev )
//STRIP001                      {
//STRIP001                          SwFrm *pTmp = pPrev->FindPrev();
//STRIP001                          ASSERT( pTmp->IsTabFrm(),
//STRIP001                                  "Vorgaenger vom Follow kein Master.");
//STRIP001                          pPrev = (SwTabFrm*)pTmp;
//STRIP001                      }
//STRIP001                      if ( pPrev )
//STRIP001                          pPrev->SetFollow( pFollow );
//STRIP001                      else if ( pFollow )
//STRIP001                          ::UnsetFollow( pFollow );
//STRIP001
//STRIP001                      //Ein TabellenFrm muss immer stehenbleiben!
//STRIP001                      if ( pPrev || pFollow )
//STRIP001                      {
//STRIP001                          pUp->Cut();
//STRIP001                          delete pUp;
//STRIP001                          bDel = FALSE;//Die Row wird mit in den Abgrund
//STRIP001                                       //gerissen.
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( bDel )
//STRIP001                  {
//STRIP001                      pFrm->Cut();
//STRIP001                      delete pFrm;
//STRIP001                  }
//STRIP001              }
//STRIP001          } while( 0 != ( pLast = aIter++ ));
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_IsLineOfTblFrm( const SwTabFrm& rTable, const SwFrm& rChk )
//STRIP001 {
//STRIP001  const SwTabFrm* pTblFrm = rChk.FindTabFrm();
//STRIP001  while( pTblFrm->IsFollow() )
//STRIP001      pTblFrm = pTblFrm->FindMaster();
//STRIP001  return &rTable == pTblFrm;
//STRIP001 }

//STRIP001 void _FndBox::MakeFrms( SwTable &rTable )
//STRIP001 {
//STRIP001  //Alle Lines zwischen pLineBefore und pLineBehind muessen im Layout
//STRIP001  //wieder neu erzeugt werden.
//STRIP001  //Und Zwar fuer alle Auspraegungen der Tabelle (mehrere z.B. im Kopf/Fuss).
//STRIP001
//STRIP001  USHORT nStPos = 0;
//STRIP001  USHORT nEndPos= rTable.GetTabLines().Count() - 1;
//STRIP001  if ( pLineBefore )
//STRIP001  {
//STRIP001      nStPos = rTable.GetTabLines().GetPos(
//STRIP001                      (const SwTableLine*&)pLineBefore );
//STRIP001      ASSERT( nStPos != USHRT_MAX, "Fuchs Du hast die Line gestohlen!" );
//STRIP001      ++nStPos;
//STRIP001
//STRIP001  }
//STRIP001  if ( pLineBehind )
//STRIP001  {
//STRIP001      nEndPos = rTable.GetTabLines().GetPos(
//STRIP001                      (const SwTableLine*&)pLineBehind );
//STRIP001      ASSERT( nEndPos != USHRT_MAX, "Fuchs Du hast die Line gestohlen!" );
//STRIP001      --nEndPos;
//STRIP001  }
//STRIP001  //Jetzt die grosse Einfuegeoperation fuer alle Tabllen.
//STRIP001  SwClientIter aTabIter( *rTable.GetFrmFmt() );
//STRIP001  for ( SwTabFrm *pTable = (SwTabFrm*)aTabIter.First( TYPE(SwFrm) ); pTable;
//STRIP001        pTable = (SwTabFrm*)aTabIter.Next() )
//STRIP001  {
//STRIP001      if ( !pTable->IsFollow() )
//STRIP001      {
//STRIP001          SwFrm  *pSibling = 0;
//STRIP001          SwFrm  *pUpper   = 0;
//STRIP001          int i;
//STRIP001          for ( i = rTable.GetTabLines().Count()-1;
//STRIP001                  i >= 0 && !pSibling; --i )
//STRIP001          {
//STRIP001              SwTableLine *pLine = pLineBehind ? pLineBehind :
//STRIP001                                                  rTable.GetTabLines()[i];
//STRIP001              SwClientIter aIter( *pLine->GetFrmFmt() );
//STRIP001              for ( pSibling = (SwFrm*)aIter.First( TYPE(SwFrm) );
//STRIP001                    pSibling && (
//STRIP001                      ((SwRowFrm*)pSibling)->GetTabLine() != pLine ||
//STRIP001                      !lcl_IsLineOfTblFrm( *pTable, *pSibling ) );
//STRIP001                    pSibling = (SwFrm*)aIter.Next() )
//STRIP001                  /* do nothing */;
//STRIP001          }
//STRIP001          if ( pSibling )
//STRIP001          {
//STRIP001              pUpper = pSibling->GetUpper();
//STRIP001              if ( !pLineBehind )
//STRIP001                  pSibling = 0;
//STRIP001          }
//STRIP001          else
//STRIP001 // ???? oder das der Letzte Follow der Tabelle ????
//STRIP001              pUpper = pTable;
//STRIP001
//STRIP001          for ( i = nStPos; (USHORT)i <= nEndPos; ++i )
//STRIP001              ::lcl_InsertRow( *rTable.GetTabLines()[i],
//STRIP001                              (SwLayoutFrm*)pUpper, pSibling );
//STRIP001          if ( pUpper->IsTabFrm() )
//STRIP001              ((SwTabFrm*)pUpper)->SetCalcLowers();
//STRIP001      }
//STRIP001      else if ( nStPos == 0 && rTable.IsHeadlineRepeat() )
//STRIP001      {
//STRIP001          //Headline in den Follow einsetzen
//STRIP001          SwRowFrm *pRow = new SwRowFrm( *rTable.GetTabLines()[0] );
//STRIP001          pRow->Paste( pTable, pTable->Lower() );
//STRIP001          pRow->RegistFlys();
//STRIP001          pTable->SetCalcLowers();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void _FndBox::MakeNewFrms( SwTable &rTable, const USHORT nNumber,
//STRIP001                                          const BOOL bBehind )
//STRIP001 {
//STRIP001  //Frms fuer neu eingefuege Zeilen erzeugen.
//STRIP001  //bBehind == TRUE:  vor     pLineBehind
//STRIP001  //        == FALSE: hinter  pLineBefore
//STRIP001  const USHORT nBfPos = pLineBefore ?
//STRIP001      rTable.GetTabLines().GetPos( (const SwTableLine*&)pLineBefore ) :
//STRIP001      USHRT_MAX;
//STRIP001  const USHORT nBhPos = pLineBehind ?
//STRIP001      rTable.GetTabLines().GetPos( (const SwTableLine*&)pLineBehind ) :
//STRIP001      USHRT_MAX;
//STRIP001
//STRIP001  //nNumber: wie oft ist eingefuegt worden.
//STRIP001  //nCnt:    wieviele sind nNumber mal eingefuegt worden.
//STRIP001
//STRIP001  const USHORT nCnt =
//STRIP001      ((nBhPos != USHRT_MAX ? nBhPos : rTable.GetTabLines().Count()) -
//STRIP001       (nBfPos != USHRT_MAX ? nBfPos + 1 : 0)) / (nNumber + 1);
//STRIP001
//STRIP001  //Den Master-TabFrm suchen
//STRIP001  SwClientIter aTabIter( *rTable.GetFrmFmt() );
//STRIP001  SwTabFrm *pTable;
//STRIP001  for ( pTable = (SwTabFrm*)aTabIter.First( TYPE(SwFrm) ); pTable;
//STRIP001        pTable = (SwTabFrm*)aTabIter.Next() )
//STRIP001     {
//STRIP001      if( !pTable->IsFollow() )
//STRIP001      {
//STRIP001          SwFrm       *pSibling = 0;
//STRIP001          SwLayoutFrm *pUpper   = 0;
//STRIP001          if ( bBehind )
//STRIP001          {
//STRIP001              if ( pLineBehind )
//STRIP001              {
//STRIP001                  SwClientIter aIter( *pLineBehind->GetFrmFmt() );
//STRIP001                  for ( pSibling = (SwFrm*)aIter.First( TYPE(SwFrm) );
//STRIP001                        pSibling && (
//STRIP001                          ((SwRowFrm*)pSibling)->GetTabLine() != pLineBehind ||
//STRIP001                          !lcl_IsLineOfTblFrm( *pTable, *pSibling ) );
//STRIP001                        pSibling = (SwFrm*)aIter.Next() )
//STRIP001                      /* do nothing */;
//STRIP001              }
//STRIP001              if ( pSibling )
//STRIP001                  pUpper = pSibling->GetUpper();
//STRIP001              else
//STRIP001              {
//STRIP001                  while( pTable->GetFollow() )
//STRIP001                      pTable = pTable->GetFollow();
//STRIP001                  pUpper = pTable;
//STRIP001              }
//STRIP001              const USHORT nMax = nBhPos != USHRT_MAX ?
//STRIP001                                  nBhPos : rTable.GetTabLines().Count();
//STRIP001
//STRIP001              USHORT i = nBfPos != USHRT_MAX ? nBfPos + 1 + nCnt : nCnt;
//STRIP001
//STRIP001              for ( ; i < nMax; ++i )
//STRIP001                  ::lcl_InsertRow( *rTable.GetTabLines()[i], pUpper, pSibling );
//STRIP001              if ( pUpper->IsTabFrm() )
//STRIP001                  ((SwTabFrm*)pUpper)->SetCalcLowers();
//STRIP001          }
//STRIP001          else //davor einfuegen
//STRIP001          {
//STRIP001              USHORT i;
//STRIP001              for ( i = 0; !pSibling; ++i )
//STRIP001              {
//STRIP001                  SwTableLine *pLine = pLineBefore ? pLineBefore :
//STRIP001                                                  rTable.GetTabLines()[i];
//STRIP001
//STRIP001                  SwClientIter aIter( *pLine->GetFrmFmt() );
//STRIP001                  for ( pSibling = (SwFrm*)aIter.First( TYPE(SwFrm) );
//STRIP001                        pSibling && (
//STRIP001                          ((SwRowFrm*)pSibling)->GetTabLine() != pLine ||
//STRIP001                          !lcl_IsLineOfTblFrm( *pTable, *pSibling ) ||
//STRIP001                          ((!pLineBefore || pLine == rTable.GetTabLines()[0]) &&
//STRIP001                           pSibling->FindTabFrm() != pTable)); // Master finden!
//STRIP001                        pSibling = (SwFrm*)aIter.Next() )
//STRIP001                      /* do nothing */;
//STRIP001              }
//STRIP001              pUpper = pSibling->GetUpper();
//STRIP001              if ( pLineBefore )
//STRIP001                  pSibling = pSibling->GetNext();
//STRIP001
//STRIP001              USHORT nMax = nBhPos != USHRT_MAX ?
//STRIP001                                  nBhPos - nCnt :
//STRIP001                                  rTable.GetTabLines().Count() - nCnt;
//STRIP001
//STRIP001              i = nBfPos != USHRT_MAX ? nBfPos + 1 : 0;
//STRIP001              for ( ; i < nMax; ++i )
//STRIP001                  ::lcl_InsertRow( *rTable.GetTabLines()[i],
//STRIP001                              pUpper, pSibling );
//STRIP001              if ( pUpper->IsTabFrm() )
//STRIP001                  ((SwTabFrm*)pUpper)->SetCalcLowers();
//STRIP001          }
//STRIP001      }
//STRIP001     }
//STRIP001
//STRIP001  //Die Headlines mussen ggf. auch verarbeitet werden. Um gut arbeitenden
//STRIP001  //Code nicht zu zerfasern wird hier nochmals iteriert.
//STRIP001  if ( !bBehind && nBfPos == USHRT_MAX && rTable.IsHeadlineRepeat() )
//STRIP001  {
//STRIP001         for ( pTable = (SwTabFrm*)aTabIter.First( TYPE(SwFrm) ); pTable;
//STRIP001               pTable = (SwTabFrm*)aTabIter.Next() )
//STRIP001         {
//STRIP001             if ( pTable->Lower() )
//STRIP001             {
//STRIP001                 if ( pTable->IsFollow() )
//STRIP001                 {
//STRIP001                     //Alte Headline vernichten
//STRIP001                     SwFrm *pLow = pTable->Lower();
//STRIP001                     pLow->Cut();
//STRIP001                     delete pLow;
//STRIP001                 }
//STRIP001                 if ( ((SwRowFrm*)pTable->Lower())->GetTabLine() !=
//STRIP001                      rTable.GetTabLines()[0] )
//STRIP001                 {
//STRIP001                     //Neue Headline einsetzen
//STRIP001                     SwRowFrm *pRow = new SwRowFrm( *rTable.GetTabLines()[0]);
//STRIP001                     pRow->Paste( pTable, pTable->Lower() );
//STRIP001                     pRow->RegistFlys();
//STRIP001                     pTable->SetCalcLowers();
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL _FndBox::AreLinesToRestore( const SwTable &rTable ) const
//STRIP001 {
//STRIP001  //Lohnt es sich MakeFrms zu rufen?
//STRIP001
//STRIP001  if ( !pLineBefore && !pLineBehind && rTable.GetTabLines().Count() )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  USHORT nBfPos;
//STRIP001  if(pLineBefore)
//STRIP001  {
//STRIP001      const SwTableLine* rLBefore = (const SwTableLine*)pLineBefore;
//STRIP001      nBfPos = rTable.GetTabLines().GetPos( rLBefore );
//STRIP001  }
//STRIP001  else
//STRIP001      nBfPos = USHRT_MAX;
//STRIP001
//STRIP001  USHORT nBhPos;
//STRIP001  if(pLineBehind)
//STRIP001  {
//STRIP001      const SwTableLine* rLBehind = (const SwTableLine*)pLineBehind;
//STRIP001      nBhPos = rTable.GetTabLines().GetPos( rLBehind );
//STRIP001  }
//STRIP001  else
//STRIP001      nBhPos = USHRT_MAX;
//STRIP001
//STRIP001  if ( nBfPos == nBhPos ) //Duerfte eigentlich nie vorkommen.
//STRIP001  {
//STRIP001      ASSERT( FALSE, "Table, Loeschen auf keinem Bereich !?!" );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if ( nBfPos == USHRT_MAX && nBhPos == 0 )
//STRIP001  {
//STRIP001      // ups. sollte unsere zu wiederholende Kopfzeile geloescht worden
//STRIP001      // sein??
//STRIP001      if( rTable.IsHeadlineRepeat() )
//STRIP001      {
//STRIP001          SwClientIter aIter( *rTable.GetFrmFmt() );
//STRIP001          for( SwTabFrm* pTable = (SwTabFrm*)aIter.First( TYPE( SwFrm ));
//STRIP001                  pTable; pTable = (SwTabFrm*)aIter.Next() )
//STRIP001              if( pTable->IsFollow() )
//STRIP001              {
//STRIP001                  //Headline in den Follow einsetzen
//STRIP001                  SwRowFrm *pRow = new SwRowFrm( *rTable.GetTabLines()[0] );
//STRIP001                  pRow->Paste( pTable, pTable->Lower() );
//STRIP001                  pRow->RegistFlys();
//STRIP001              }
//STRIP001      }
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if ( nBhPos == USHRT_MAX && nBfPos == (rTable.GetTabLines().Count() - 1) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( nBfPos != USHRT_MAX && nBhPos != USHRT_MAX && (nBfPos + 1) == nBhPos )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//Save- und RestoreChartData:
//Zu der Tabelle werden alle Charts gesucht. Die Namentliche Addressierung der
//Boxen in der Tabelle (etwa: <A1:C3>) wird ausgelesen. Die Addressen der
//Boxen werden im Chart festgehalten. Im Restore wird versucht zu den Pointern
//die Boxen wiederzufinden. Wenn dies gelingt, wird die neue Addressierung
//wieder in das Chart geschrieben. Wenn sie nicht gefunden werden gibt es
//einen FallBack auf die erste/letzte Box.

//STRIP001 const SwTableBox *lcl_FindFirstBox( const SwTable &rTable )
//STRIP001 {
//STRIP001  const SwTableLines *pLines = &rTable.GetTabLines();
//STRIP001  const SwTableBox *pBox;
//STRIP001  do
//STRIP001  {   pBox = (*pLines)[0]->GetTabBoxes()[0];
//STRIP001      if ( pBox->GetSttNd() )
//STRIP001          pLines = 0;
//STRIP001      else
//STRIP001          pLines = &pBox->GetTabLines();
//STRIP001
//STRIP001  } while ( pLines );
//STRIP001  return pBox;
//STRIP001 }

//STRIP001 const SwTableBox *lcl_FindLastBox( const SwTable &rTable )
//STRIP001 {
//STRIP001  const SwTableLines *pLines = &rTable.GetTabLines();
//STRIP001  const SwTableBox *pBox;
//STRIP001  do
//STRIP001  {   const SwTableBoxes &rBoxes = (*pLines)[pLines->Count()-1]->GetTabBoxes();
//STRIP001      pBox = rBoxes[rBoxes.Count()-1];
//STRIP001      if ( pBox->GetSttNd() )
//STRIP001          pLines = 0;
//STRIP001      else
//STRIP001          pLines = &pBox->GetTabLines();
//STRIP001
//STRIP001  } while ( pLines );
//STRIP001
//STRIP001  return pBox;
//STRIP001 }


//GPF bei Tab in letzer Zelle mit MSC4
//STRIP001 #pragma optimize("",off)

//STRIP001 void _FndBox::SaveChartData( const SwTable &rTable )
//STRIP001 {
//STRIP001  SwDoc *pDoc = rTable.GetFrmFmt()->GetDoc();
//STRIP001  SwClientIter aIter( *(SwModify*)pDoc->GetDfltGrfFmtColl() );
//STRIP001  SwClient *pCli;
//STRIP001  if ( 0 != (pCli = aIter.First( TYPE(SwCntntNode) )) )
//STRIP001      do
//STRIP001      {   if ( !((SwCntntNode*)pCli)->GetOLENode() )
//STRIP001              continue;
//STRIP001          SwOLENode *pONd = (SwOLENode*)pCli;
//STRIP001          if ( rTable.GetFrmFmt()->GetName() == pONd->GetChartTblName() )
//STRIP001          {
//STRIP001              SwOLEObj& rOObj = pONd->GetOLEObj();
//STRIP001              SchMemChart *pData = SchDLL::GetChartData( rOObj.GetOleRef() );
//STRIP001              if ( pData )
//STRIP001              {
//STRIP001                  String &rStr = pData->SomeData1();
//STRIP001                  xub_StrLen nTmp = rStr.Search( ':' );
//STRIP001                  String aBox( rStr.Copy( 1, nTmp - 1 ) );
//STRIP001                  //const this, weil Borland so dumm ist!
//STRIP001                  const SwTableBox *pSttBox = rTable.GetTblBox( aBox );
//STRIP001                  if ( !pSttBox )
//STRIP001                      pSttBox = rTable.GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001                  aBox = rStr.Copy( nTmp + 1, rStr.Len()-2 - nTmp);
//STRIP001                  const SwTableBox *pEndBox = rTable.GetTblBox( aBox );
//STRIP001                  if ( !pEndBox )
//STRIP001                  {
//STRIP001                      SwTableLine *pLine =
//STRIP001                          rTable.GetTabLines()[rTable.GetTabLines().Count()-1];
//STRIP001                      pEndBox = pLine->GetTabBoxes()[pLine->GetTabBoxes().Count()-1];
//STRIP001                  }
//STRIP001                  pData->SomeData3() = String::CreateFromInt32(
//STRIP001                                      pSttBox != ::lcl_FindFirstBox(rTable)
//STRIP001                                          ? long(pSttBox)
//STRIP001                                          : LONG_MAX );
//STRIP001                  pData->SomeData4() = String::CreateFromInt32(
//STRIP001                                      pEndBox != ::lcl_FindLastBox(rTable)
//STRIP001                                          ? long(pEndBox)
//STRIP001                                          : LONG_MAX );
//STRIP001              }
//STRIP001          }
//STRIP001      } while ( 0 != (pCli = aIter.Next()) );
//STRIP001 }

//STRIP001 void _FndBox::RestoreChartData( const SwTable &rTable )
//STRIP001 {
//STRIP001  SwDoc *pDoc = rTable.GetFrmFmt()->GetDoc();
//STRIP001  SwClientIter aIter( *(SwModify*)pDoc->GetDfltGrfFmtColl() );
//STRIP001  SwClient *pCli;
//STRIP001  if ( 0 != (pCli = aIter.First( TYPE(SwCntntNode) )) )
//STRIP001      do
//STRIP001      {   if ( !((SwCntntNode*)pCli)->GetOLENode() )
//STRIP001              continue;
//STRIP001          SwOLENode *pONd = (SwOLENode*)pCli;
//STRIP001          if ( rTable.GetFrmFmt()->GetName() == pONd->GetChartTblName() )
//STRIP001          {
//STRIP001              SwOLEObj& rOObj = pONd->GetOLEObj();
//STRIP001              SchMemChart *pData = SchDLL::GetChartData( rOObj.GetOleRef() );
//STRIP001              if ( pData )
//STRIP001              {
//STRIP001                  const SwTableBox *pSttBox = (SwTableBox*)
//STRIP001                                              pData->SomeData3().ToInt32();
//STRIP001                  if ( long(pSttBox) == LONG_MAX )
//STRIP001                      pSttBox = ::lcl_FindFirstBox( rTable );
//STRIP001                  const SwTableBox *pEndBox = (SwTableBox*)
//STRIP001                                              pData->SomeData4().ToInt32();
//STRIP001                  if ( long(pEndBox) == LONG_MAX )
//STRIP001                      pEndBox = ::lcl_FindLastBox( rTable );
//STRIP001                  FASTBOOL bSttFound = FALSE, bEndFound = FALSE;
//STRIP001                  const SwTableSortBoxes &rBoxes = rTable.GetTabSortBoxes();
//STRIP001                  for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001                  {
//STRIP001                      const SwTableBox *pTmp = rBoxes[i];
//STRIP001                      if ( pTmp == pSttBox )
//STRIP001                          bSttFound = TRUE;
//STRIP001                      if ( pTmp == pEndBox )
//STRIP001                          bEndFound = TRUE;
//STRIP001                  }
//STRIP001                  if ( !bSttFound )
//STRIP001                      pSttBox = rTable.GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001                  if ( !bEndFound )
//STRIP001                  {
//STRIP001                      SwTableLine *pLine =
//STRIP001                          rTable.GetTabLines()[rTable.GetTabLines().Count()-1];
//STRIP001                      pEndBox = pLine->GetTabBoxes()[pLine->GetTabBoxes().Count()-1];
//STRIP001                  }
//STRIP001                  String &rStr = pData->SomeData1();
//STRIP001                  rStr = '<'; rStr += pSttBox->GetName(); rStr += ':';
//STRIP001                  rStr += pEndBox->GetName(); rStr += '>';
//STRIP001                  pData->SomeData3().Erase(); pData->SomeData4().Erase();
//STRIP001                  SchDLL::Update( rOObj.GetOleRef(), pData );
//STRIP001              }
//STRIP001          }
//STRIP001      } while ( 0 != (pCli = aIter.Next()) );
//STRIP001 }

//STRIP001 #pragma optimize("",on)

}
