/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_tblsel.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:40:43 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
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
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _ROWFRM_HXX
#include <rowfrm.hxx>
#endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
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
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     rBoxes.Insert( &rShell.GetTableCrsr()->GetBoxes() );
/*N*/ }

/*N*/ void GetTblSelCrs( const SwTableCursor& rTblCrsr, SwSelBoxes& rBoxes )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
            USHORT i=0;
/*N*/       for( i = 0; i < aUnions.Count() && bTblIsValid; ++i )
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
            USHORT i=0;
/*N*/       for( i = 0; i < aUnions.Count() && bTblIsValid &&
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



// -------------------------------------------------------------------
// Diese Klassen kopieren die aktuelle Tabellen-Selektion (rBoxes)
// unter Beibehaltung der Tabellen-Struktur in eine eigene Struktur
// neu: SS zum gezielten Loeschen/Retaurieren des Layouts.




/*N*/ BOOL _FndLineCopyCol( const SwTableLine*& rpLine, void* pPara )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return TRUE;
/*N*/ }










//Save- und RestoreChartData:
//Zu der Tabelle werden alle Charts gesucht. Die Namentliche Addressierung der
//Boxen in der Tabelle (etwa: <A1:C3>) wird ausgelesen. Die Addressen der
//Boxen werden im Chart festgehalten. Im Restore wird versucht zu den Pointern
//die Boxen wiederzufinden. Wenn dies gelingt, wird die neue Addressierung
//wieder in das Chart geschrieben. Wenn sie nicht gefunden werden gibt es
//einen FallBack auf die erste/letzte Box.




//GPF bei Tab in letzer Zelle mit MSC4




}
