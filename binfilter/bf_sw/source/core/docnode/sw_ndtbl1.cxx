/*************************************************************************
 *
 *  $RCSfile: sw_ndtbl1.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:19 $
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
#ifdef WTC
#define private public
#endif

#include "hintids.hxx"

#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif

#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _TABCOL_HXX //autogen
#include <tabcol.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _CELLFRM_HXX //autogen
#include <cellfrm.hxx>
#endif
#ifndef _TABFRM_HXX //autogen
#include <tabfrm.hxx>
#endif
#ifndef _CNTFRM_HXX //autogen
#include <cntfrm.hxx>
#endif
#ifndef _TXTFRM_HXX //autogen
#include <txtfrm.hxx>
#endif

#include "doc.hxx"
#include "pam.hxx"
#include "swcrsr.hxx"
#include "viscrs.hxx"
#include "swtable.hxx"
#include "htmltbl.hxx"
#include "tblsel.hxx"
#include "swtblfmt.hxx"
#include "docary.hxx"
#include "ndindex.hxx"
#include "undobj.hxx"
namespace binfilter {


extern void ClearFEShellTabCols();

//siehe auch swtable.cxx
#define COLFUZZY 20L

//STRIP001 inline BOOL IsSame( long nA, long nB ) { return  Abs(nA-nB) <= COLFUZZY; }

//STRIP001 class SwTblFmtCmp
//STRIP001 {
//STRIP001 public:
//STRIP001  SwFrmFmt *pOld,
//STRIP001           *pNew;
//STRIP001  INT16     nType;
//STRIP001
//STRIP001  SwTblFmtCmp( SwFrmFmt *pOld, SwFrmFmt *pNew, INT16 nType );
//STRIP001
//STRIP001  static SwFrmFmt *FindNewFmt( SvPtrarr &rArr, SwFrmFmt*pOld, INT16 nType );
//STRIP001  static void Delete( SvPtrarr &rArr );
//STRIP001 };


//STRIP001 SwTblFmtCmp::SwTblFmtCmp( SwFrmFmt *pO, SwFrmFmt *pN, INT16 nT )
//STRIP001  : pOld ( pO ), pNew ( pN ), nType( nT )
//STRIP001 {
//STRIP001 }

//STRIP001 SwFrmFmt *SwTblFmtCmp::FindNewFmt( SvPtrarr &rArr, SwFrmFmt *pOld, INT16 nType )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < rArr.Count(); ++i )
//STRIP001  {
//STRIP001      SwTblFmtCmp *pCmp = (SwTblFmtCmp*)rArr[i];
//STRIP001      if ( pCmp->pOld == pOld && pCmp->nType == nType )
//STRIP001          return pCmp->pNew;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SwTblFmtCmp::Delete( SvPtrarr &rArr )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < rArr.Count(); ++i )
//STRIP001      delete (SwTblFmtCmp*)rArr[i];
//STRIP001 }

/*N*/ void lcl_GetStartEndCell( const SwCursor& rCrsr,
/*N*/                       SwLayoutFrm *&prStart, SwLayoutFrm *&prEnd )
/*N*/ {
/*N*/   ASSERT( rCrsr.GetCntntNode() && rCrsr.GetCntntNode( FALSE ),
/*N*/           "Tabselection nicht auf Cnt." );
/*N*/
/*N*/   Point aPtPos, aMkPos;
/*N*/   const SwShellCrsr* pShCrsr = rCrsr;
/*N*/   if( pShCrsr )
/*N*/   {
/*N*/       aPtPos = pShCrsr->GetPtPos();
/*N*/       aMkPos = pShCrsr->GetMkPos();
/*N*/   }
/*N*/
/*N*/   prStart = rCrsr.GetCntntNode()->GetFrm( &aPtPos )->GetUpper();
/*N*/   prEnd   = rCrsr.GetCntntNode(FALSE)->GetFrm( &aMkPos )->GetUpper();
/*N*/ }

/*N*/ BOOL lcl_GetBoxSel( const SwCursor& rCursor, SwSelBoxes& rBoxes,
/*N*/                   BOOL bAllCrsr = FALSE )
/*N*/ {
/*N*/   const SwTableCursor* pTblCrsr = rCursor;
/*N*/   if( pTblCrsr )
/*?*/       ::binfilter::GetTblSelCrs( *pTblCrsr, rBoxes );
/*N*/   else
/*N*/   {
/*N*/       const SwPaM *pCurPam = &rCursor, *pSttPam = pCurPam;
/*N*/       do {
/*N*/           const SwNode* pNd = pCurPam->GetNode()->FindTableBoxStartNode();
/*N*/           if( pNd )
/*N*/           {
/*N*/               SwTableBox* pBox = (SwTableBox*)pNd->FindTableNode()->GetTable().
/*N*/                                           GetTblBox( pNd->GetIndex() );
/*N*/               rBoxes.Insert( pBox );
/*N*/           }
/*N*/       } while( bAllCrsr &&
/*N*/               pSttPam != ( pCurPam = (SwPaM*)pCurPam->GetNext()) );
/*N*/   }
/*N*/   return 0 != rBoxes.Count();
/*N*/ }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetRowHeight(), GetRowHeight()
#*  Datum      :  MA 17. May. 93
#*  Update     :  JP 28.04.98
#***********************************************************************/
//Die Zeilenhoehe wird ausgehend von der Selektion ermittelt/gesetzt.
//Ausgehend von jeder Zelle innerhalb der Selektion werden nach oben alle
//Zeilen abgeklappert, die oberste Zeile erhaelt den gewuenschten Wert alle
//tieferliegenden Zeilen einen entsprechenden Wert der sich aus der
//Relation der alten und neuen Groesse der obersten Zeile und ihrer
//eigenen Groesse ergiebt.
//Alle veraenderten Zeilen erhalten ggf. ein eigenes FrmFmt.
//Natuerlich darf jede Zeile nur einmal angefasst werden.

/*N*/ inline void InsertLine( SvPtrarr& rLineArr, SwTableLine* pLine )
/*N*/ {
/*N*/   if( USHRT_MAX == rLineArr.GetPos( (void*&)pLine ) )
/*N*/       rLineArr.Insert( (void*&)pLine, rLineArr.Count() );
/*N*/ }

//-----------------------------------------------------------------------------

//STRIP001 BOOL lcl_IsAnLower( const SwTableLine *pLine, const SwTableLine *pAssumed )
//STRIP001 {
//STRIP001  const SwTableLine *pTmp = pAssumed->GetUpper() ?
//STRIP001                                  pAssumed->GetUpper()->GetUpper() : 0;
//STRIP001  while ( pTmp )
//STRIP001  {
//STRIP001      if ( pTmp == pLine )
//STRIP001          return TRUE;
//STRIP001      pTmp = pTmp->GetUpper() ? pTmp->GetUpper()->GetUpper() : 0;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }
//-----------------------------------------------------------------------------

/*N*/ struct LinesAndTable
/*N*/ {
/*N*/         SvPtrarr &rLines;
/*N*/   const SwTable  &rTable;
/*N*/         BOOL      bInsertLines;
/*N*/
/*N*/   LinesAndTable( SvPtrarr &rL, const SwTable &rTbl ) :
/*N*/         rLines( rL ), rTable( rTbl ), bInsertLines( TRUE ) {}
/*N*/ };


/*N*/ BOOL _FindLine( const _FndLine*& rpLine, void* pPara );

/*N*/ BOOL _FindBox( const _FndBox*& rpBox, void* pPara )
/*N*/ {
/*N*/   if ( rpBox->GetLines().Count() )
/*N*/   {
/*N*/       ((LinesAndTable*)pPara)->bInsertLines = TRUE;
/*N*/       ((_FndBox*)rpBox)->GetLines().ForEach( _FindLine, pPara );
/*N*/       if ( ((LinesAndTable*)pPara)->bInsertLines )
/*N*/       {
/*N*/           const SwTableLines &rLines = rpBox->GetBox()
/*N*/                                   ? rpBox->GetBox()->GetTabLines()
/*N*/                                   : ((LinesAndTable*)pPara)->rTable.GetTabLines();
/*N*/           if ( rpBox->GetLines().Count() == rLines.Count() )
/*N*/           {
/*N*/               for ( USHORT i = 0; i < rLines.Count(); ++i )
/*N*/                   ::binfilter::InsertLine( ((LinesAndTable*)pPara)->rLines,
/*N*/                                 (SwTableLine*)rLines[i] );
/*N*/           }
/*N*/           else
/*N*/               ((LinesAndTable*)pPara)->bInsertLines = FALSE;
/*N*/       }
/*N*/   }
/*N*/   else if ( rpBox->GetBox() )
/*N*/       ::binfilter::InsertLine( ((LinesAndTable*)pPara)->rLines,
/*N*/                     (SwTableLine*)rpBox->GetBox()->GetUpper() );
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL _FindLine( const _FndLine*& rpLine, void* pPara )
/*N*/ {
/*N*/   ((_FndLine*)rpLine)->GetBoxes().ForEach( _FindBox, pPara );
/*N*/   return TRUE;
/*N*/ }

/*N*/ void lcl_CollectLines( SvPtrarr &rArr, const SwCursor& rCursor )
/*N*/ {
/*N*/   //Zuerst die selektierten Boxen einsammeln.
/*N*/   SwSelBoxes aBoxes;
/*N*/   if( !::binfilter::lcl_GetBoxSel( rCursor, aBoxes ))
/*?*/       return ;
/*N*/
/*N*/   //Die selektierte Struktur kopieren.
/*N*/   const SwTable &rTable = aBoxes[0]->GetSttNd()->FindTableNode()->GetTable();
/*N*/   LinesAndTable aPara( rArr, rTable );
/*N*/   _FndBox aFndBox( 0, 0 );
/*N*/   {
/*N*/       _FndPara aPara( aBoxes, &aFndBox );
/*N*/       ((SwTableLines&)rTable.GetTabLines()).ForEach( &_FndLineCopyCol, &aPara );
/*N*/   }
/*N*/
/*N*/   //Diejenigen Lines einsammeln, die nur selektierte Boxen enthalten.
/*N*/   const _FndBox *pTmp = &aFndBox;
/*N*/   ::binfilter::_FindBox( pTmp, &aPara );
/*N*/
/*N*/   //Jetzt die Lines entfernen, die von einer gemeinsamen uebergeordneten Line
/*N*/   //erfasst werden.
/*N*/   for ( USHORT i = 0; i < rArr.Count(); ++i )
/*N*/   {
/*N*/       SwTableLine *pUpLine = (SwTableLine*)rArr[i];
/*N*/       for ( USHORT k = 0; k < rArr.Count(); ++k )
/*N*/       {
/*N*/           if ( k != i && 1) //STRIP001 ::lcl_IsAnLower( pUpLine, (SwTableLine*)rArr[k] ) )
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 rArr.Remove( k );
//STRIP001 /*?*/                if ( k <= i )
//STRIP001 /*?*/                    --i;
//STRIP001 /*?*/                --k;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//-----------------------------------------------------------------------------

//STRIP001 void lcl_ProcessBoxSize( SvPtrarr &rFmtCmp, SwTableBox *pBox, const SwFmtFrmSize &rNew );

//STRIP001 void lcl_ProcessRowSize( SvPtrarr &rFmtCmp, SwTableLine *pLine, const SwFmtFrmSize &rNew )
//STRIP001 {
//STRIP001  SwFrmFmt *pNewFmt;
//STRIP001  if ( 0 != (pNewFmt = SwTblFmtCmp::FindNewFmt( rFmtCmp, pLine->GetFrmFmt(), 0 )))
//STRIP001      pLine->ChgFrmFmt( (SwTableLineFmt*)pNewFmt );
//STRIP001  else
//STRIP001  {
//STRIP001      SwFrmFmt *pOld = pLine->GetFrmFmt();
//STRIP001      SwFrmFmt *pNew = pLine->ClaimFrmFmt();
//STRIP001      pNew->SetAttr( rNew );
//STRIP001      rFmtCmp.Insert( new SwTblFmtCmp( pOld, pNew, 0 ), rFmtCmp.Count());
//STRIP001  }
//STRIP001  SwTableBoxes &rBoxes = pLine->GetTabBoxes();
//STRIP001  for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001      ::lcl_ProcessBoxSize( rFmtCmp, rBoxes[i], rNew );
//STRIP001 }

//-----------------------------------------------------------------------------

//STRIP001 void lcl_ProcessBoxSize( SvPtrarr &rFmtCmp, SwTableBox *pBox, const SwFmtFrmSize &rNew )
//STRIP001 {
//STRIP001  SwTableLines &rLines = pBox->GetTabLines();
//STRIP001  if ( rLines.Count() )
//STRIP001  {
//STRIP001      SwFmtFrmSize aSz( rNew );
//STRIP001      aSz.SetHeight( rNew.GetHeight() ? rNew.GetHeight() / rLines.Count() : 0 );
//STRIP001      for ( USHORT i = 0; i < rLines.Count(); ++i )
//STRIP001          ::lcl_ProcessRowSize( rFmtCmp, rLines[i], aSz );
//STRIP001  }
//STRIP001 }

/******************************************************************************
 *              void SwDoc::SetRowHeight( SwTwips nNew )
 ******************************************************************************/
//STRIP001 void SwDoc::SetRowHeight( const SwCursor& rCursor, const SwFmtFrmSize &rNew )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001  {
//STRIP001      SvPtrarr aRowArr( 25, 50 ); //Zum sammeln Lines.
//STRIP001      ::lcl_CollectLines( aRowArr, rCursor );
//STRIP001
//STRIP001      if( aRowArr.Count() )
//STRIP001      {
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              ClearRedo();
//STRIP001              AppendUndo( new SwUndoAttrTbl( *pTblNd ));
//STRIP001          }
//STRIP001
//STRIP001          SvPtrarr aFmtCmp( Max( BYTE(255), BYTE(aRowArr.Count()) ), 255 );
//STRIP001          for ( USHORT i = 0; i < aRowArr.Count(); ++i )
//STRIP001              ::lcl_ProcessRowSize( aFmtCmp, (SwTableLine*)aRowArr[i], rNew );
//STRIP001          SwTblFmtCmp::Delete( aFmtCmp );
//STRIP001
//STRIP001          SetModified();
//STRIP001      }
//STRIP001  }
//STRIP001 }


/******************************************************************************
 *               SwTwips SwDoc::GetRowHeight() const
 ******************************************************************************/
//STRIP001 void SwDoc::GetRowHeight( const SwCursor& rCursor, SwFmtFrmSize *& rpSz ) const
//STRIP001 {
//STRIP001  rpSz = 0;
//STRIP001
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001  {
//STRIP001      SvPtrarr aRowArr( 25, 50 ); //Zum sammeln der Lines.
//STRIP001      ::lcl_CollectLines( aRowArr, rCursor );
//STRIP001
//STRIP001      if( aRowArr.Count() )
//STRIP001      {
//STRIP001          rpSz = &(SwFmtFrmSize&)((SwTableLine*)aRowArr[0])->
//STRIP001                                              GetFrmFmt()->GetFrmSize();
//STRIP001
//STRIP001          for ( USHORT i = 1; i < aRowArr.Count() && rpSz; ++i )
//STRIP001          {
//STRIP001              if ( *rpSz != ((SwTableLine*)aRowArr[i])->GetFrmFmt()->GetFrmSize() )
//STRIP001                  rpSz = 0;
//STRIP001          }
//STRIP001          if ( rpSz )
//STRIP001              rpSz = new SwFmtFrmSize( *rpSz );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ BOOL SwDoc::BalanceRowHeight( const SwCursor& rCursor, BOOL bTstOnly )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
/*N*/   if( pTblNd )
/*N*/   {
/*N*/       SvPtrarr aRowArr( 25, 50 ); //Zum sammeln der Lines.
/*N*/       ::binfilter::lcl_CollectLines( aRowArr, rCursor );
/*N*/
/*N*/       if( 1 < aRowArr.Count() )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 if( !bTstOnly )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                long nHeight = 0;
//STRIP001 /*?*/                for ( USHORT i = 0; i < aRowArr.Count(); ++i )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwClientIter aIter( *((SwTableLine*)aRowArr[i])->GetFrmFmt() );
//STRIP001 /*?*/                    SwFrm* pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) );
//STRIP001 /*?*/                    while ( pFrm )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        nHeight = Max( nHeight, pFrm->Frm().Height() );
//STRIP001 /*?*/                        pFrm = (SwFrm*)aIter.Next();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                SwFmtFrmSize aNew( ATT_MIN_SIZE, 0, nHeight );
//STRIP001 /*?*/
//STRIP001 /*?*/                if( DoesUndo() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ClearRedo();
//STRIP001 /*?*/                    AppendUndo( new SwUndoAttrTbl( *pTblNd ));
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                SvPtrarr aFmtCmp( Max( BYTE(255), BYTE(aRowArr.Count()) ), 255 );
//STRIP001 /*?*/                for( i = 0; i < aRowArr.Count(); ++i )
//STRIP001 /*?*/                    ::lcl_ProcessRowSize( aFmtCmp, (SwTableLine*)aRowArr[i], aNew );
//STRIP001 /*?*/                SwTblFmtCmp::Delete( aFmtCmp );
//STRIP001 /*?*/
//STRIP001 /*?*/                SetModified();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            bRet = TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/******************************************************************************
 *              void SwDoc::SetRowBackground()
 ******************************************************************************/
//STRIP001 void SwDoc::SetRowBackground( const SwCursor& rCursor, const SvxBrushItem &rNew )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001  {
//STRIP001      SvPtrarr aRowArr( 25, 50 ); //Zum sammeln Lines.
//STRIP001      ::lcl_CollectLines( aRowArr, rCursor );
//STRIP001
//STRIP001      if( aRowArr.Count() )
//STRIP001      {
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              ClearRedo();
//STRIP001              AppendUndo( new SwUndoAttrTbl( *pTblNd ));
//STRIP001          }
//STRIP001
//STRIP001          SvPtrarr aFmtCmp( Max( BYTE(255), BYTE(aRowArr.Count()) ), 255 );
//STRIP001
//STRIP001          for( USHORT i = 0; i < aRowArr.Count(); ++i )
//STRIP001          {
//STRIP001              SwTableLine *pLine = (SwTableLine*)aRowArr[i];
//STRIP001
//STRIP001              SwFrmFmt *pNewFmt;
//STRIP001              if( 0 != (pNewFmt = SwTblFmtCmp::FindNewFmt( aFmtCmp,
//STRIP001                                              pLine->GetFrmFmt(), 0 )))
//STRIP001                  pLine->ChgFrmFmt( (SwTableLineFmt*)pNewFmt );
//STRIP001              else
//STRIP001              {
//STRIP001                  SwFrmFmt *pOld = pLine->GetFrmFmt();
//STRIP001                  SwFrmFmt *pNew = pLine->ClaimFrmFmt();
//STRIP001                  pNew->SetAttr( rNew );
//STRIP001                  aFmtCmp.Insert( new SwTblFmtCmp( pOld, pNew, 0 ), aFmtCmp.Count());
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          SwTblFmtCmp::Delete( aFmtCmp );
//STRIP001          SetModified();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/******************************************************************************
 *               SwTwips SwDoc::GetRowBackground() const
 ******************************************************************************/
//STRIP001 BOOL SwDoc::GetRowBackground( const SwCursor& rCursor, SvxBrushItem &rToFill ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001  {
//STRIP001      SvPtrarr aRowArr( 25, 50 ); //Zum sammeln Lines.
//STRIP001      ::lcl_CollectLines( aRowArr, rCursor );
//STRIP001
//STRIP001      if( aRowArr.Count() )
//STRIP001      {
//STRIP001          rToFill = ((SwTableLine*)aRowArr[0])->GetFrmFmt()->GetBackground();
//STRIP001
//STRIP001          bRet = TRUE;
//STRIP001          for ( USHORT i = 1; i < aRowArr.Count(); ++i )
//STRIP001              if ( rToFill != ((SwTableLine*)aRowArr[i])->GetFrmFmt()->GetBackground() )
//STRIP001              {
//STRIP001                  bRet = FALSE;
//STRIP001                  break;
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetTabBorders(), GetTabBorders()
#*  Datum      :  MA 18. May. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/
/*N*/ inline void InsertCell( SvPtrarr& rCellArr, SwCellFrm* pCellFrm )
/*N*/ {
/*N*/   if( USHRT_MAX == rCellArr.GetPos( (void*&)pCellFrm ) )
/*N*/       rCellArr.Insert( (void*&)pCellFrm, rCellArr.Count() );
/*N*/ }

//-----------------------------------------------------------------------------
/*N*/ void lcl_CollectCells( SvPtrarr &rArr, const SwRect &rUnion,
/*N*/                         SwTabFrm *pTab )
/*N*/ {
/*N*/   SwLayoutFrm *pCell = pTab->FirstCell();
/*N*/   do
/*N*/   {
/*N*/       // Wenn in der Zelle ein spaltiger Bereich sitzt, muessen wir
/*N*/       // uns erst wieder zur Zelle hochhangeln
/*N*/       while ( !pCell->IsCellFrm() )
/*?*/           pCell = pCell->GetUpper();
/*N*/       ASSERT( pCell, "Frame ist keine Zelle." );
/*N*/       if ( rUnion.IsOver( pCell->Frm() ) )
/*N*/           ::binfilter::InsertCell( rArr, (SwCellFrm*)pCell );
/*N*/       //Dafuer sorgen, dass die Zelle auch verlassen wird (Bereiche)
/*N*/       SwLayoutFrm *pTmp = pCell;
/*N*/       do
/*N*/       {   pTmp = pTmp->GetNextLayoutLeaf();
/*N*/       } while ( pCell->IsAnLower( pTmp ) );
/*N*/       pCell = pTmp;
/*N*/   } while( pCell && pTab->IsAnLower( pCell ) );
/*N*/ }

//STRIP001 void SwDoc::SetTabBorders( const SwCursor& rCursor, const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return ;
//STRIP001
//STRIP001  SwLayoutFrm *pStart, *pEnd;
//STRIP001  ::lcl_GetStartEndCell( rCursor, pStart, pEnd );
//STRIP001
//STRIP001  SwSelUnions aUnions;
//STRIP001  ::MakeSelUnions( aUnions, pStart, pEnd );
//STRIP001
//STRIP001  if( aUnions.Count() )
//STRIP001  {
//STRIP001      SwTable& rTable = pTblNd->GetTable();
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoAttrTbl( *pTblNd ));
//STRIP001      }
//STRIP001
//STRIP001      SvPtrarr aFmtCmp( 255, 255 );
//STRIP001      const SvxBoxItem* pSetBox;
//STRIP001      const SvxBoxInfoItem *pSetBoxInfo;
//STRIP001
//STRIP001      const SvxBorderLine* pLeft = 0;
//STRIP001      const SvxBorderLine* pRight = 0;
//STRIP001      const SvxBorderLine* pTop = 0;
//STRIP001      const SvxBorderLine* pBottom = 0;
//STRIP001      const SvxBorderLine* pHori = 0;
//STRIP001      const SvxBorderLine* pVert = 0;
//STRIP001      BOOL bHoriValid = TRUE, bVertValid = TRUE,
//STRIP001           bTopValid = TRUE, bBottomValid = TRUE,
//STRIP001           bLeftValid = TRUE, bRightValid = TRUE;
//STRIP001
//STRIP001      // JP 21.07.95: die Flags im BoxInfo-Item entscheiden, wann eine
//STRIP001      //              BorderLine gueltig ist!!
//STRIP001      if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_BORDER_INNER, FALSE,
//STRIP001          (const SfxPoolItem**)&pSetBoxInfo) )
//STRIP001      {
//STRIP001          pHori = pSetBoxInfo->GetHori();
//STRIP001          pVert = pSetBoxInfo->GetVert();
//STRIP001
//STRIP001          bHoriValid = pSetBoxInfo->IsValid(VALID_HORI);
//STRIP001          bVertValid = pSetBoxInfo->IsValid(VALID_VERT);
//STRIP001
//STRIP001          // wollen wir die auswerten ??
//STRIP001          bTopValid = pSetBoxInfo->IsValid(VALID_TOP);
//STRIP001          bBottomValid = pSetBoxInfo->IsValid(VALID_BOTTOM);
//STRIP001          bLeftValid = pSetBoxInfo->IsValid(VALID_LEFT);
//STRIP001          bRightValid = pSetBoxInfo->IsValid(VALID_RIGHT);
//STRIP001      }
//STRIP001
//STRIP001      if( SFX_ITEM_SET == rSet.GetItemState( RES_BOX, FALSE,
//STRIP001          (const SfxPoolItem**)&pSetBox) )
//STRIP001      {
//STRIP001          pLeft = pSetBox->GetLeft();
//STRIP001          pRight = pSetBox->GetRight();
//STRIP001          pTop = pSetBox->GetTop();
//STRIP001          pBottom = pSetBox->GetBottom();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // nicht gesetzt, also keine gueltigen Werte
//STRIP001          bTopValid = bBottomValid = bLeftValid = bRightValid = FALSE;
//STRIP001          pSetBox = 0;
//STRIP001      }
//STRIP001
//STRIP001      BOOL bFirst = TRUE;
//STRIP001      for ( USHORT i = 0; i < aUnions.Count(); ++i )
//STRIP001      {
//STRIP001          SwSelUnion *pUnion = aUnions[i];
//STRIP001          SwTabFrm *pTab = pUnion->GetTable();
//STRIP001          const SwRect &rUnion = pUnion->GetUnion();
//STRIP001          const BOOL bLast  = i == aUnions.Count() - 1 ? TRUE : FALSE;
//STRIP001
//STRIP001          SvPtrarr aCellArr( 255, 255 );
//STRIP001          ::lcl_CollectCells( aCellArr, pUnion->GetUnion(), pTab );
//STRIP001
//STRIP001          //Alle Zellenkanten, die mit dem UnionRect uebereinstimmen oder
//STRIP001          //darueber hinausragen sind Aussenkanten. Alle anderen sind
//STRIP001          //Innenkanten.
//STRIP001          //neu: Die Aussenkanten koennen abhaengig davon, ob es sich um eine
//STRIP001          //Start/Mittlere/Folge -Tabelle (bei Selektionen ueber FollowTabs)
//STRIP001          //handelt doch keine Aussenkanten sein.
//STRIP001          //Aussenkanten werden links, rechts, oben und unten gesetzt.
//STRIP001          //Innenkanten werden nur oben und links gesetzt.
//STRIP001          for ( USHORT j = 0; j < aCellArr.Count(); ++j )
//STRIP001          {
//STRIP001              SwCellFrm *pCell = (SwCellFrm*)aCellArr[j];
//STRIP001                 const sal_Bool bVert = pCell->IsVertical();
//STRIP001                 const sal_Bool bRTL = pCell->IsRightToLeft();
//STRIP001                 sal_Bool bTopOver, bLeftOver, bRightOver, bBottomOver;
//STRIP001                 if ( bVert )
//STRIP001                 {
//STRIP001                     bTopOver = pCell->Frm().Right() >= rUnion.Right();
//STRIP001                     bLeftOver = pCell->Frm().Top() <= rUnion.Top();
//STRIP001                     bRightOver = pCell->Frm().Bottom() >= rUnion.Bottom();
//STRIP001                     bBottomOver = pCell->Frm().Left() <= rUnion.Left();
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     bTopOver = pCell->Frm().Top() <= rUnion.Top();
//STRIP001                     bLeftOver = pCell->Frm().Left() <= rUnion.Left();
//STRIP001                     bRightOver = pCell->Frm().Right() >= rUnion.Right();
//STRIP001                     bBottomOver = pCell->Frm().Bottom() >= rUnion.Bottom();
//STRIP001                 }
//STRIP001
//STRIP001                 if ( bRTL )
//STRIP001                 {
//STRIP001                     sal_Bool bTmp = bRightOver;
//STRIP001                     bRightOver = bLeftOver;
//STRIP001                     bLeftOver = bTmp;
//STRIP001                 }
//STRIP001
//STRIP001              //Grundsaetzlich nichts setzen in HeadlineRepeats.
//STRIP001              if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() &&
//STRIP001                   ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pCell ) )
//STRIP001                  continue;
//STRIP001
//STRIP001              SvxBoxItem aBox( pCell->GetFmt()->GetBox() );
//STRIP001
//STRIP001              INT16 nType = 0;
//STRIP001
//STRIP001              //Obere Kante
//STRIP001              if( bTopValid )
//STRIP001              {
//STRIP001                  if ( bFirst && bTopOver )
//STRIP001                  {
//STRIP001                      aBox.SetLine( pTop, BOX_LINE_TOP );
//STRIP001                      nType |= 0x0001;
//STRIP001                  }
//STRIP001                  else if ( bHoriValid )
//STRIP001                  {
//STRIP001                      aBox.SetLine( 0, BOX_LINE_TOP );
//STRIP001                      nType |= 0x0002;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              //Linke Kante
//STRIP001              if ( bLeftOver )
//STRIP001              {
//STRIP001                  if( bLeftValid )
//STRIP001                  {
//STRIP001                      aBox.SetLine( pLeft, BOX_LINE_LEFT );
//STRIP001                      nType |= 0x0004;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( bVertValid )
//STRIP001              {
//STRIP001                  aBox.SetLine( pVert, BOX_LINE_LEFT );
//STRIP001                  nType |= 0x0008;
//STRIP001              }
//STRIP001
//STRIP001              //Rechte Kante
//STRIP001              if( bRightValid )
//STRIP001              {
//STRIP001                  if ( bRightOver )
//STRIP001                  {
//STRIP001                      aBox.SetLine( pRight, BOX_LINE_RIGHT );
//STRIP001                      nType |= 0x0010;
//STRIP001                  }
//STRIP001                  else if ( bVertValid )
//STRIP001                  {
//STRIP001                      aBox.SetLine( 0, BOX_LINE_RIGHT );
//STRIP001                      nType |= 0x0020;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              //Untere Kante
//STRIP001              if ( bLast && bBottomOver )
//STRIP001              {
//STRIP001                  if( bBottomValid )
//STRIP001                  {
//STRIP001                      aBox.SetLine( pBottom, BOX_LINE_BOTTOM );
//STRIP001                      nType |= 0x0040;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( bHoriValid )
//STRIP001              {
//STRIP001                  aBox.SetLine( pHori, BOX_LINE_BOTTOM );
//STRIP001                  nType |= 0x0080;
//STRIP001              }
//STRIP001
//STRIP001              if( pSetBox )
//STRIP001              {
//STRIP001                  static USHORT __READONLY_DATA aBorders[] = {
//STRIP001                      BOX_LINE_BOTTOM, BOX_LINE_TOP,
//STRIP001                      BOX_LINE_RIGHT, BOX_LINE_LEFT };
//STRIP001                  const USHORT* pBrd = aBorders;
//STRIP001                  for( int i = 0; i < 4; ++i, ++pBrd )
//STRIP001                      aBox.SetDistance( pSetBox->GetDistance( *pBrd ), *pBrd );
//STRIP001              }
//STRIP001
//STRIP001              SwTableBox *pBox = (SwTableBox*)pCell->GetTabBox();
//STRIP001              SwFrmFmt *pNewFmt;
//STRIP001              if ( 0 != (pNewFmt = SwTblFmtCmp::FindNewFmt( aFmtCmp, pBox->GetFrmFmt(), nType )))
//STRIP001                  pBox->ChgFrmFmt( (SwTableBoxFmt*)pNewFmt );
//STRIP001              else
//STRIP001              {
//STRIP001                  SwFrmFmt *pOld = pBox->GetFrmFmt();
//STRIP001                  SwFrmFmt *pNew = pBox->ClaimFrmFmt();
//STRIP001                  pNew->SetAttr( aBox );
//STRIP001                  aFmtCmp.Insert( new SwTblFmtCmp( pOld, pNew, nType ), aFmtCmp.Count());
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          bFirst = FALSE;
//STRIP001      }
//STRIP001
//STRIP001      SwHTMLTableLayout *pLayout = rTable.GetHTMLTableLayout();
//STRIP001      if( pLayout )
//STRIP001      {
//STRIP001          SwCntntFrm* pFrm = rCursor.GetCntntNode()->GetFrm();
//STRIP001          SwTabFrm* pTabFrm = pFrm->ImplFindTabFrm();
//STRIP001
//STRIP001          pLayout->BordersChanged(
//STRIP001              pLayout->GetBrowseWidthByTabFrm( *pTabFrm ), TRUE );
//STRIP001      }
//STRIP001      SwTblFmtCmp::Delete( aFmtCmp );
//STRIP001      ::ClearFEShellTabCols();
//STRIP001      SetModified();
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_SetLineStyle( SvxBorderLine *pToSet,
//STRIP001                        const Color *pColor, const SvxBorderLine *pBorderLine)
//STRIP001 {
//STRIP001  if ( pBorderLine )
//STRIP001  {
//STRIP001      if ( !pColor )
//STRIP001      {
//STRIP001          Color aTmp( pToSet->GetColor() );
//STRIP001          *pToSet = *pBorderLine;
//STRIP001          pToSet->SetColor( aTmp );
//STRIP001      }
//STRIP001      else
//STRIP001          *pToSet = *pBorderLine;
//STRIP001  }
//STRIP001  if ( pColor )
//STRIP001      pToSet->SetColor( *pColor );
//STRIP001 }

//STRIP001 void SwDoc::SetTabLineStyle( const SwCursor& rCursor,
//STRIP001                           const Color* pColor, BOOL bSetLine,
//STRIP001                           const SvxBorderLine* pBorderLine )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return ;
//STRIP001
//STRIP001  SwLayoutFrm *pStart, *pEnd;
//STRIP001  ::lcl_GetStartEndCell( rCursor, pStart, pEnd );
//STRIP001
//STRIP001  SwSelUnions aUnions;
//STRIP001  ::MakeSelUnions( aUnions, pStart, pEnd );
//STRIP001
//STRIP001  if( aUnions.Count() )
//STRIP001  {
//STRIP001      SwTable& rTable = pTblNd->GetTable();
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoAttrTbl( *pTblNd ));
//STRIP001      }
//STRIP001
//STRIP001      for( USHORT i = 0; i < aUnions.Count(); ++i )
//STRIP001      {
//STRIP001          SwSelUnion *pUnion = aUnions[i];
//STRIP001          SwTabFrm *pTab = pUnion->GetTable();
//STRIP001          SvPtrarr aCellArr( 255, 255 );
//STRIP001          ::lcl_CollectCells( aCellArr, pUnion->GetUnion(), pTab );
//STRIP001
//STRIP001          for ( USHORT j = 0; j < aCellArr.Count(); ++j )
//STRIP001          {
//STRIP001              SwCellFrm *pCell = ( SwCellFrm* )aCellArr[j];
//STRIP001
//STRIP001              //Grundsaetzlich nichts setzen in HeadlineRepeats.
//STRIP001              if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() &&
//STRIP001                   ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pCell ) )
//STRIP001                  continue;
//STRIP001
//STRIP001              ((SwTableBox*)pCell->GetTabBox())->ClaimFrmFmt();
//STRIP001              SwFrmFmt *pFmt = pCell->GetFmt();
//STRIP001              SvxBoxItem aBox( pFmt->GetBox() );
//STRIP001
//STRIP001              if ( !pBorderLine && bSetLine )
//STRIP001                  aBox = *(SvxBoxItem*)::GetDfltAttr( RES_BOX );
//STRIP001              else
//STRIP001              {
//STRIP001                  if ( aBox.GetTop() )
//STRIP001                      ::lcl_SetLineStyle( (SvxBorderLine*)aBox.GetTop(),
//STRIP001                                      pColor, pBorderLine );
//STRIP001                  if ( aBox.GetBottom() )
//STRIP001                      ::lcl_SetLineStyle( (SvxBorderLine*)aBox.GetBottom(),
//STRIP001                                      pColor, pBorderLine );
//STRIP001                  if ( aBox.GetLeft() )
//STRIP001                      ::lcl_SetLineStyle( (SvxBorderLine*)aBox.GetLeft(),
//STRIP001                                      pColor, pBorderLine );
//STRIP001                  if ( aBox.GetRight() )
//STRIP001                      ::lcl_SetLineStyle( (SvxBorderLine*)aBox.GetRight(),
//STRIP001                                      pColor, pBorderLine );
//STRIP001              }
//STRIP001              pFmt->SetAttr( aBox );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      SwHTMLTableLayout *pLayout = rTable.GetHTMLTableLayout();
//STRIP001      if( pLayout )
//STRIP001      {
//STRIP001          SwCntntFrm* pFrm = rCursor.GetCntntNode()->GetFrm();
//STRIP001          SwTabFrm* pTabFrm = pFrm->ImplFindTabFrm();
//STRIP001
//STRIP001          pLayout->BordersChanged(
//STRIP001              pLayout->GetBrowseWidthByTabFrm( *pTabFrm ), TRUE );
//STRIP001      }
//STRIP001      ::ClearFEShellTabCols();
//STRIP001      SetModified();
//STRIP001  }
//STRIP001 }

/*N*/ void SwDoc::GetTabBorders( const SwCursor& rCursor, SfxItemSet& rSet ) const
/*N*/ {
/*N*/   SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
/*N*/   if( !pTblNd )
/*?*/       return ;
/*N*/
/*N*/   SwLayoutFrm *pStart, *pEnd;
/*N*/   ::binfilter::lcl_GetStartEndCell( rCursor, pStart, pEnd );
/*N*/
/*N*/   SwSelUnions aUnions;
/*N*/   ::binfilter::MakeSelUnions( aUnions, pStart, pEnd );
/*N*/
/*N*/   if( aUnions.Count() )
/*N*/   {
/*N*/       SvxBoxItem     aSetBox    ((const SvxBoxItem    &) rSet.Get(RES_BOX    ));
/*N*/       SvxBoxInfoItem aSetBoxInfo((const SvxBoxInfoItem&) rSet.Get(SID_ATTR_BORDER_INNER));
/*N*/
/*N*/       BOOL bTopSet      = FALSE,
/*N*/            bBottomSet   = FALSE,
/*N*/            bLeftSet     = FALSE,
/*N*/            bRightSet    = FALSE,
/*N*/            bHoriSet     = FALSE,
/*N*/            bVertSet     = FALSE,
/*N*/            bDistanceSet = FALSE;
/*N*/
/*N*/       aSetBoxInfo.ResetFlags();
/*N*/
/*N*/       for ( USHORT i = 0; i < aUnions.Count(); ++i )
/*N*/       {
/*N*/           SwSelUnion *pUnion = aUnions[i];
/*N*/           const SwTabFrm *pTab = pUnion->GetTable();
/*N*/           const SwRect &rUnion = pUnion->GetUnion();
/*N*/           const BOOL bFirst = i == 0 ? TRUE : FALSE;
/*N*/           const BOOL bLast  = i == aUnions.Count() - 1 ? TRUE : FALSE;
/*N*/
/*N*/           SvPtrarr aCellArr( 255, 255 );
/*N*/           ::binfilter::lcl_CollectCells( aCellArr, rUnion, (SwTabFrm*)pTab );
/*N*/
/*N*/           for ( USHORT j = 0; j < aCellArr.Count(); ++j )
/*N*/           {
/*N*/               const SwCellFrm *pCell = (const SwCellFrm*)aCellArr[j];
/*N*/                 const sal_Bool bVert = pCell->IsVertical();
/*N*/                 const sal_Bool bRTL = pCell->IsRightToLeft();
/*N*/                 sal_Bool bTopOver, bLeftOver, bRightOver, bBottomOver;
/*N*/                 if ( bVert )
/*N*/                 {
/*N*/                     bTopOver = pCell->Frm().Right() >= rUnion.Right();
/*N*/                     bLeftOver = pCell->Frm().Top() <= rUnion.Top();
/*N*/                     bRightOver = pCell->Frm().Bottom() >= rUnion.Bottom();
/*N*/                     bBottomOver = pCell->Frm().Left() <= rUnion.Left();
/*N*/                 }
/*N*/                 else
/*N*/                 {
/*N*/                     bTopOver = pCell->Frm().Top() <= rUnion.Top();
/*N*/                     bLeftOver = pCell->Frm().Left() <= rUnion.Left();
/*N*/                     bRightOver = pCell->Frm().Right() >= rUnion.Right();
/*N*/                     bBottomOver = pCell->Frm().Bottom() >= rUnion.Bottom();
/*N*/                 }
/*N*/
/*N*/                 if ( bRTL )
/*N*/                 {
/*N*/                     sal_Bool bTmp = bRightOver;
/*N*/                     bRightOver = bLeftOver;
/*N*/                     bLeftOver = bTmp;
/*N*/                 }
/*N*/
/*N*/               const SwFrmFmt  *pFmt  = pCell->GetFmt();
/*N*/               const SvxBoxItem  &rBox  = pFmt->GetBox();
/*N*/
/*N*/               //Obere Kante
/*N*/               if ( bFirst && bTopOver )
/*N*/               {
/*N*/                   if (aSetBoxInfo.IsValid(VALID_TOP))
/*N*/                   {
/*N*/                       if ( !bTopSet )
/*N*/                       {   bTopSet = TRUE;
/*N*/                           aSetBox.SetLine( rBox.GetTop(), BOX_LINE_TOP );
/*N*/                       }
/*?*/                       else if ((aSetBox.GetTop() && rBox.GetTop() &&
/*?*/                                !(*aSetBox.GetTop() == *rBox.GetTop())) ||
/*?*/                                ((!aSetBox.GetTop()) ^ (!rBox.GetTop()))) // XOR-Ausdruck ist TRUE, wenn genau einer der beiden Pointer 0 ist
/*?*/                       {
/*?*/                           aSetBoxInfo.SetValid(VALID_TOP, FALSE );
/*?*/                           aSetBox.SetLine( 0, BOX_LINE_TOP );
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               //Linke Kante
/*N*/               if ( bLeftOver )
/*N*/               {
/*N*/                   if (aSetBoxInfo.IsValid(VALID_LEFT))
/*N*/                   {
/*N*/                       if ( !bLeftSet )
/*N*/                       {   bLeftSet = TRUE;
/*N*/                           aSetBox.SetLine( rBox.GetLeft(), BOX_LINE_LEFT );
/*N*/                       }
/*N*/                       else if ((aSetBox.GetLeft() && rBox.GetLeft() &&
/*?*/                                !(*aSetBox.GetLeft() == *rBox.GetLeft())) ||
/*?*/                                ((!aSetBox.GetLeft()) ^ (!rBox.GetLeft())))
/*?*/                       {
/*?*/                           aSetBoxInfo.SetValid(VALID_LEFT, FALSE );
/*?*/                           aSetBox.SetLine( 0, BOX_LINE_LEFT );
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   if (aSetBoxInfo.IsValid(VALID_VERT))
/*?*/                   {
/*?*/                       if ( !bVertSet )
/*?*/                       {   bVertSet = TRUE;
/*?*/                           aSetBoxInfo.SetLine( rBox.GetLeft(), BOXINFO_LINE_VERT );
/*?*/                       }
/*?*/                       else if ((aSetBoxInfo.GetVert() && rBox.GetLeft() &&
/*?*/                                !(*aSetBoxInfo.GetVert() == *rBox.GetLeft())) ||
/*?*/                                ((!aSetBoxInfo.GetVert()) ^ (!rBox.GetLeft())))
/*?*/                       {   aSetBoxInfo.SetValid( VALID_VERT, FALSE );
/*?*/                           aSetBoxInfo.SetLine( 0, BOXINFO_LINE_VERT );
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               //Rechte Kante
/*N*/               if ( aSetBoxInfo.IsValid(VALID_RIGHT) && bRightOver )
/*N*/               {
/*N*/                   if ( !bRightSet )
/*N*/                   {   bRightSet = TRUE;
/*N*/                       aSetBox.SetLine( rBox.GetRight(), BOX_LINE_RIGHT );
/*N*/                   }
/*N*/                   else if ((aSetBox.GetRight() && rBox.GetRight() &&
/*?*/                            !(*aSetBox.GetRight() == *rBox.GetRight())) ||
/*?*/                            (!aSetBox.GetRight() ^ !rBox.GetRight()))
/*?*/                   {   aSetBoxInfo.SetValid( VALID_RIGHT, FALSE );
/*?*/                       aSetBox.SetLine( 0, BOX_LINE_RIGHT );
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               //Untere Kante
/*N*/               if ( bLast && bBottomOver )
/*N*/               {
/*N*/                   if ( aSetBoxInfo.IsValid(VALID_BOTTOM) )
/*N*/                   {
/*N*/                       if ( !bBottomSet )
/*N*/                       {   bBottomSet = TRUE;
/*N*/                           aSetBox.SetLine( rBox.GetBottom(), BOX_LINE_BOTTOM );
/*N*/                       }
/*N*/                       else if ((aSetBox.GetBottom() && rBox.GetBottom() &&
/*?*/                                !(*aSetBox.GetBottom() == *rBox.GetBottom())) ||
/*?*/                                (!aSetBox.GetBottom() ^ !rBox.GetBottom()))
/*?*/                       {   aSetBoxInfo.SetValid( VALID_BOTTOM, FALSE );
/*?*/                           aSetBox.SetLine( 0, BOX_LINE_BOTTOM );
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/               //in allen Zeilen ausser der letzten werden die
/*N*/               // horiz. Linien aus der Bottom-Linie entnommen
/*N*/               else
/*N*/               {
/*?*/                   if (aSetBoxInfo.IsValid(VALID_HORI))
/*?*/                   {
/*?*/                       if ( !bHoriSet )
/*?*/                       {   bHoriSet = TRUE;
/*?*/                           aSetBoxInfo.SetLine( rBox.GetBottom(), BOXINFO_LINE_HORI );
/*?*/                       }
/*?*/                       else if ((aSetBoxInfo.GetHori() && rBox.GetBottom() &&
/*?*/                                !(*aSetBoxInfo.GetHori() == *rBox.GetBottom())) ||
/*?*/                                ((!aSetBoxInfo.GetHori()) ^ (!rBox.GetBottom())))
/*?*/                       {
/*?*/                           aSetBoxInfo.SetValid( VALID_HORI, FALSE );
/*?*/                           aSetBoxInfo.SetLine( 0, BOXINFO_LINE_HORI );
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               // Abstand zum Text
/*N*/               if (aSetBoxInfo.IsValid(VALID_DISTANCE))
/*N*/               {
/*N*/                   static USHORT __READONLY_DATA aBorders[] = {
/*N*/                       BOX_LINE_BOTTOM, BOX_LINE_TOP,
/*N*/                       BOX_LINE_RIGHT, BOX_LINE_LEFT };
/*N*/                   const USHORT* pBrd = aBorders;
/*N*/
/*N*/                   if( !bDistanceSet )     // bei 1. Durchlauf erstmal setzen
/*N*/                   {
/*N*/                       bDistanceSet = TRUE;
/*N*/                       for( int i = 0; i < 4; ++i, ++pBrd )
/*N*/                           aSetBox.SetDistance( rBox.GetDistance( *pBrd ),
/*N*/                                               *pBrd );
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       for( int i = 0; i < 4; ++i, ++pBrd )
/*?*/                           if( aSetBox.GetDistance( *pBrd ) !=
/*?*/                               rBox.GetDistance( *pBrd ) )
/*?*/                           {
/*?*/                               aSetBoxInfo.SetValid( VALID_DISTANCE, FALSE );
/*?*/                               aSetBox.SetDistance( (USHORT) 0 );
/*?*/                               break;
/*?*/                           }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       rSet.Put( aSetBox );
/*N*/       rSet.Put( aSetBoxInfo );
/*N*/   }
/*N*/ }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetBoxAttr
#*  Datum      :  MA 18. Dec. 96
#*  Update     :  JP 29.04.98
#***********************************************************************/
//STRIP001 void SwDoc::SetBoxAttr( const SwCursor& rCursor, const SfxPoolItem &rNew )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  if( pTblNd && ::lcl_GetBoxSel( rCursor, aBoxes, TRUE ) )
//STRIP001  {
//STRIP001      SwTable& rTable = pTblNd->GetTable();
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoAttrTbl( *pTblNd ));
//STRIP001      }
//STRIP001
//STRIP001      SvPtrarr aFmtCmp( Max( BYTE(255), BYTE(aBoxes.Count()) ), 255 );
//STRIP001      for ( USHORT i = 0; i < aBoxes.Count(); ++i )
//STRIP001      {
//STRIP001          SwTableBox *pBox = aBoxes[i];
//STRIP001
//STRIP001          SwFrmFmt *pNewFmt;
//STRIP001          if ( 0 != (pNewFmt = SwTblFmtCmp::FindNewFmt( aFmtCmp, pBox->GetFrmFmt(), 0 )))
//STRIP001              pBox->ChgFrmFmt( (SwTableBoxFmt*)pNewFmt );
//STRIP001          else
//STRIP001          {
//STRIP001              SwFrmFmt *pOld = pBox->GetFrmFmt();
//STRIP001              SwFrmFmt *pNew = pBox->ClaimFrmFmt();
//STRIP001              pNew->SetAttr( rNew );
//STRIP001              aFmtCmp.Insert( new SwTblFmtCmp( pOld, pNew, 0 ), aFmtCmp.Count());
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      SwHTMLTableLayout *pLayout = rTable.GetHTMLTableLayout();
//STRIP001      if( pLayout )
//STRIP001      {
//STRIP001          SwCntntFrm* pFrm = rCursor.GetCntntNode()->GetFrm();
//STRIP001          SwTabFrm* pTabFrm = pFrm->ImplFindTabFrm();
//STRIP001
//STRIP001          pLayout->Resize(
//STRIP001              pLayout->GetBrowseWidthByTabFrm( *pTabFrm ), TRUE );
//STRIP001      }
//STRIP001      SwTblFmtCmp::Delete( aFmtCmp );
//STRIP001      SetModified();
//STRIP001  }
//STRIP001 }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  GetBoxBackground()
#*  Datum      :  MA 01. Jun. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/

//STRIP001 BOOL SwDoc::GetBoxBackground( const SwCursor& rCursor, SvxBrushItem &rToFill ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  if( pTblNd && lcl_GetBoxSel( rCursor, aBoxes ))
//STRIP001  {
//STRIP001      bRet = TRUE;
//STRIP001      BOOL bOneFound = FALSE;
//STRIP001      for( USHORT i = 0; i < aBoxes.Count(); ++i )
//STRIP001      {
//STRIP001          const SvxBrushItem &rBack =
//STRIP001                          aBoxes[i]->GetFrmFmt()->GetBackground();
//STRIP001          if( !bOneFound )
//STRIP001          {
//STRIP001              rToFill = rBack;
//STRIP001              bOneFound = TRUE;
//STRIP001          }
//STRIP001          else if( rToFill != rBack )
//STRIP001          {
//STRIP001              bRet = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetBoxAlign, SetBoxAlign
#*  Datum      :  MA 18. Dec. 96
#*  Update     :  JP 29.04.98
#***********************************************************************/
//STRIP001 void SwDoc::SetBoxAlign( const SwCursor& rCursor, USHORT nAlign )
//STRIP001 {
//STRIP001  ASSERT( nAlign == VERT_NONE   ||
//STRIP001          nAlign == VERT_CENTER ||
//STRIP001          nAlign == VERT_BOTTOM, "wrong alignment" );
//STRIP001  SwFmtVertOrient aVertOri( 0, SwVertOrient(nAlign) );
//STRIP001  SetBoxAttr( rCursor, aVertOri );
//STRIP001 }

/*N*/ USHORT SwDoc::GetBoxAlign( const SwCursor& rCursor ) const
/*N*/ {
/*N*/   USHORT nAlign = USHRT_MAX;
/*N*/   SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
/*N*/   SwSelBoxes aBoxes;
/*N*/   if( pTblNd && ::binfilter::lcl_GetBoxSel( rCursor, aBoxes ))
/*N*/       for( USHORT i = 0; i < aBoxes.Count(); ++i )
/*N*/       {
/*N*/           const SwFmtVertOrient &rOri =
/*N*/                           aBoxes[i]->GetFrmFmt()->GetVertOrient();
/*N*/           if( USHRT_MAX == nAlign )
/*N*/               nAlign = rOri.GetVertOrient();
/*N*/           else if( rOri.GetVertOrient() != nAlign )
/*N*/           {
/*?*/               nAlign = USHRT_MAX;
/*?*/               break;
/*N*/           }
/*N*/       }
/*N*/   return nAlign;
/*N*/ }


/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  AdjustCellWidth()
#*  Datum      :  MA 20. Feb. 95
#*  Update     :  JP 29.04.98
#***********************************************************************/
//STRIP001 USHORT lcl_CalcCellFit( const SwLayoutFrm *pCell )
//STRIP001 {
//STRIP001  SwTwips nRet = 0;
//STRIP001  const SwFrm *pFrm = pCell->Lower(); //Die ganze Zelle.
//STRIP001  SWRECTFN( pCell )
//STRIP001  while ( pFrm )
//STRIP001  {
//STRIP001      const SwTwips nAdd = (pFrm->Frm().*fnRect->fnGetWidth)() -
//STRIP001                           (pFrm->Prt().*fnRect->fnGetWidth)();
//STRIP001      #ifdef HPUX
//STRIP001      nRet = Max( nRet, ((long)((SwTxtFrm*)pFrm)->CalcFitToContent() + nAdd) );
//STRIP001      #else
//STRIP001      nRet = Max( nRet, (((SwTxtFrm*)pFrm)->CalcFitToContent() + nAdd) );
//STRIP001      #endif
//STRIP001      pFrm = pFrm->GetNext();
//STRIP001  }
//STRIP001  //Umrandung und linker/rechter Rand wollen mit kalkuliert werden.
//STRIP001  nRet += (pCell->Frm().*fnRect->fnGetWidth)() -
//STRIP001          (pCell->Prt().*fnRect->fnGetWidth)();
//STRIP001
//STRIP001  //Um Rechenungenauikeiten, die spaeter bei SwTable::SetTabCols enstehen,
//STRIP001  //auszugleichen, addieren wir noch ein bischen.
//STRIP001  nRet += COLFUZZY;
//STRIP001  return (USHORT)Max( long(MINLAY), nRet );
//STRIP001 }

/*Die Zelle ist in der Selektion, wird aber nicht von den TabCols beschrieben.
 *Das bedeutet, dass die Zelle aufgrund der zweidimensionalen Darstellung von
 *anderen Zellen "geteilt" wurde. Wir muessen also den Wunsch- bzw. Minimalwert
 *der Zelle auf die Spalten, durch die sie geteilt wurde verteilen.
 *
 *Dazu sammeln wir zuerst die Spalten - nicht die Spaltentrenner! - ein, die
 *sich mit der Zelle ueberschneiden. Den Wunschwert der Zelle verteilen wir
 *dann anhand des Betrages der Ueberschneidung auf die Zellen.
 *Wenn eine Zelle bereits einen groesseren Wunschwert angemeldet hat, so bleibt
 *dieser erhalten, kleinere Wuensche werden ueberschrieben.
 */

//STRIP001 void lcl_CalcSubColValues( SvUShorts &rToFill, const SwTabCols &rCols,
//STRIP001                            const SwLayoutFrm *pCell, const SwLayoutFrm *pTab,
//STRIP001                            BOOL bWishValues )
//STRIP001 {
//STRIP001  const USHORT nWish = bWishValues ?
//STRIP001                  ::lcl_CalcCellFit( pCell ) :
//STRIP001                  MINLAY + USHORT(pCell->Frm().Width() - pCell->Prt().Width());
//STRIP001
//STRIP001     SWRECTFN( pTab )
//STRIP001
//STRIP001  for ( USHORT i = 0 ; i <= rCols.Count(); ++i )
//STRIP001  {
//STRIP001      long nColLeft  = i == 0             ? rCols.GetLeft()  : rCols[i-1];
//STRIP001      long nColRight = i == rCols.Count() ? rCols.GetRight() : rCols[i];
//STRIP001      nColLeft  += rCols.GetLeftMin();
//STRIP001      nColRight += rCols.GetLeftMin();
//STRIP001
//STRIP001      //Werte auf die Verhaeltnisse der Tabelle (Follows) anpassen.
//STRIP001         if ( rCols.GetLeftMin() !=  USHORT((pTab->Frm().*fnRect->fnGetLeft)()) )
//STRIP001      {
//STRIP001             const long nDiff = (pTab->Frm().*fnRect->fnGetLeft)() - rCols.GetLeftMin();
//STRIP001          nColLeft  += nDiff;
//STRIP001          nColRight += nDiff;
//STRIP001      }
//STRIP001         const long nCellLeft  = (pCell->Frm().*fnRect->fnGetLeft)();
//STRIP001         const long nCellRight = (pCell->Frm().*fnRect->fnGetRight)();
//STRIP001
//STRIP001      //Ueberschneidungsbetrag ermitteln.
//STRIP001      long nWidth = 0;
//STRIP001      if ( nColLeft <= nCellLeft && nColRight >= (nCellLeft+COLFUZZY) )
//STRIP001          nWidth = nColRight - nCellLeft;
//STRIP001      else if ( nColLeft <= (nCellRight-COLFUZZY) && nColRight >= nCellRight )
//STRIP001          nWidth = nCellRight - nColLeft;
//STRIP001      else if ( nColLeft >= nCellLeft && nColRight <= nCellRight )
//STRIP001          nWidth = nColRight - nColLeft;
//STRIP001      if ( nWidth )
//STRIP001      {
//STRIP001          long nTmp = nWidth * nWish / pCell->Frm().Width();
//STRIP001          if ( USHORT(nTmp) > rToFill[i] )
//STRIP001              rToFill[i] = USHORT(nTmp);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*Besorgt neue Werte zu Einstellung der TabCols.
 *Es wird nicht ueber die Eintrage in den TabCols itereriert, sondern
 *quasi ueber die Zwischenraeume, die ja die Zellen beschreiben.
 *
 *bWishValues == TRUE:  Es werden zur aktuellen Selektion bzw. zur aktuellen
 *                      Zelle die Wunschwerte aller betroffen Zellen ermittelt.
 *                      Sind mehrere Zellen in einer Spalte, so wird der
 *                      groesste Wunschwert als Ergebnis geliefert.
 *                      Fuer die TabCol-Eintraege, zu denen keine Zellen
 *                      ermittelt wurden, werden 0-en eingetragen.
 *
 *bWishValues == FALSE: Die Selektion wird senkrecht ausgedehnt. Zu jeder
 *                      Spalte in den TabCols, die sich mit der Selektion
 *                      schneidet wird der Minimalwert ermittelt.
 */

//STRIP001 void lcl_CalcColValues( SvUShorts &rToFill, const SwTabCols &rCols,
//STRIP001                         const SwLayoutFrm *pStart, const SwLayoutFrm *pEnd,
//STRIP001                         BOOL bWishValues )
//STRIP001 {
//STRIP001  SwSelUnions aUnions;
//STRIP001  ::MakeSelUnions( aUnions, pStart, pEnd,
//STRIP001                  bWishValues ? TBLSEARCH_NONE : TBLSEARCH_COL );
//STRIP001
//STRIP001  for ( USHORT i2 = 0; i2 < aUnions.Count(); ++i2 )
//STRIP001  {
//STRIP001      SwSelUnion *pSelUnion = aUnions[i2];
//STRIP001      const SwTabFrm *pTab = pSelUnion->GetTable();
//STRIP001      const SwRect &rUnion = pSelUnion->GetUnion();
//STRIP001
//STRIP001      SWRECTFN( pTab )
//STRIP001 #ifdef BIDI
//STRIP001         sal_Bool bRTL = pTab->IsRightToLeft();
//STRIP001 #endif
//STRIP001
//STRIP001      const SwLayoutFrm *pCell = pTab->FirstCell();
//STRIP001      do
//STRIP001      {   if ( ::IsFrmInTblSel( rUnion, pCell ) )
//STRIP001          {
//STRIP001              const long nCLeft  = (pCell->Frm().*fnRect->fnGetLeft)();
//STRIP001              const long nCRight = (pCell->Frm().*fnRect->fnGetRight)();
//STRIP001
//STRIP001              BOOL bNotInCols = TRUE;
//STRIP001
//STRIP001              for ( USHORT i = 0; i <= rCols.Count(); ++i )
//STRIP001              {
//STRIP001                  USHORT nFit = rToFill[i];
//STRIP001                  long nColLeft  = i == 0             ? rCols.GetLeft()  : rCols[i-1];
//STRIP001                  long nColRight = i == rCols.Count() ? rCols.GetRight() : rCols[i];
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001                     if ( bRTL )
//STRIP001                     {
//STRIP001                      long nTmpRight = nColRight;
//STRIP001                         nColRight = rCols.GetRight() - nColLeft;
//STRIP001                         nColLeft = rCols.GetRight() - nTmpRight;
//STRIP001                     }
//STRIP001 #endif
//STRIP001                     nColLeft  += rCols.GetLeftMin();
//STRIP001                     nColRight += rCols.GetLeftMin();
//STRIP001
//STRIP001                  //Werte auf die Verhaeltnisse der Tabelle (Follows) anpassen.
//STRIP001                  long nLeftA  = nColLeft;
//STRIP001                  long nRightA = nColRight;
//STRIP001                  if ( rCols.GetLeftMin() !=  USHORT((pTab->Frm().*fnRect->fnGetLeft)()) )
//STRIP001                  {
//STRIP001                      const long nDiff = (pTab->Frm().*fnRect->fnGetLeft)() - rCols.GetLeftMin();
//STRIP001                      nLeftA  += nDiff;
//STRIP001                      nRightA += nDiff;
//STRIP001                  }
//STRIP001
//STRIP001                  //Wir wollen nicht allzu genau hinsehen.
//STRIP001                  if ( ::IsSame(nCLeft, nLeftA) && ::IsSame(nCRight, nRightA))
//STRIP001                  {
//STRIP001                      bNotInCols = FALSE;
//STRIP001                      if ( bWishValues )
//STRIP001                      {
//STRIP001                          const USHORT nWish = ::lcl_CalcCellFit( pCell );
//STRIP001                          if ( nWish > nFit )
//STRIP001                              nFit = nWish;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {   const USHORT nMin = MINLAY + USHORT(pCell->Frm().Width() -
//STRIP001                                                              pCell->Prt().Width());
//STRIP001                          if ( !nFit || nMin < nFit )
//STRIP001                              nFit = nMin;
//STRIP001                      }
//STRIP001                      if ( rToFill[i] < nFit )
//STRIP001                          rToFill[i] = nFit;
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( bNotInCols )
//STRIP001                  ::lcl_CalcSubColValues( rToFill, rCols, pCell, pTab, bWishValues );
//STRIP001          }
//STRIP001          pCell = pCell->GetNextLayoutLeaf();
//STRIP001
//STRIP001      } while ( pCell && ((SwCellFrm*)pCell)->ImplFindTabFrm() == pTab );
//STRIP001  }
//STRIP001 }


//STRIP001 void SwDoc::AdjustCellWidth( const SwCursor& rCursor, BOOL bBalance )
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der Point/Mark in einer Tabelle stehen
//STRIP001  SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return ;
//STRIP001
//STRIP001  SwLayoutFrm *pStart, *pEnd;
//STRIP001  ::lcl_GetStartEndCell( rCursor, pStart, pEnd );
//STRIP001
//STRIP001  //TabCols besorgen, den ueber diese stellen wir die Tabelle neu ein.
//STRIP001  SwFrm* pBoxFrm = pStart;
//STRIP001  while( !pBoxFrm->IsCellFrm() )
//STRIP001      pBoxFrm = pBoxFrm->GetUpper();
//STRIP001
//STRIP001  SwTabCols aTabCols;
//STRIP001  GetTabCols( aTabCols, 0, (SwCellFrm*)pBoxFrm );
//STRIP001
//STRIP001     if ( ! aTabCols.Count() )
//STRIP001         return;
//STRIP001
//STRIP001  const BYTE nTmp = (BYTE)Max( USHORT(255), USHORT(aTabCols.Count() + 1) );
//STRIP001  SvUShorts aWish( nTmp, nTmp ),
//STRIP001            aMins( nTmp, nTmp );
//STRIP001  for ( USHORT i = 0; i <= aTabCols.Count(); ++i )
//STRIP001  {
//STRIP001      aWish.Insert( USHORT(0), aWish.Count() );
//STRIP001      aMins.Insert( USHORT(0), aMins.Count() );
//STRIP001  }
//STRIP001  ::lcl_CalcColValues( aWish, aTabCols, pStart, pEnd, TRUE  );
//STRIP001
//STRIP001  //Es ist Robuster wenn wir die Min-Werte fuer die ganze Tabelle berechnen.
//STRIP001  const SwTabFrm *pTab = pStart->ImplFindTabFrm();
//STRIP001  pStart = (SwLayoutFrm*)pTab->FirstCell();
//STRIP001  pEnd   = (SwLayoutFrm*)pTab->FindLastCntnt()->GetUpper();
//STRIP001  while( !pEnd->IsCellFrm() )
//STRIP001      pEnd = pEnd->GetUpper();
//STRIP001  ::lcl_CalcColValues( aMins, aTabCols, pStart, pEnd, FALSE );
//STRIP001
//STRIP001  if( bBalance )
//STRIP001  {
//STRIP001      //Alle Spalten, die makiert sind haben jetzt einen Wunschwert
//STRIP001      //eingtragen. Wir addieren die aktuellen Werte, teilen das Ergebnis
//STRIP001      //durch die Anzahl und haben eine Wunschwert fuer den ausgleich.
//STRIP001      USHORT nWish = 0, nCnt = 0;
//STRIP001      for ( i = 0; i <= aTabCols.Count(); ++i )
//STRIP001      {
//STRIP001          int nDiff = aWish[i];
//STRIP001          if ( nDiff )
//STRIP001          {
//STRIP001              if ( i == 0 )
//STRIP001                  nWish += aTabCols[i] - aTabCols.GetLeft();
//STRIP001              else if ( i == aTabCols.Count() )
//STRIP001                  nWish += aTabCols.GetRight() - aTabCols[i-1];
//STRIP001              else
//STRIP001                  nWish += aTabCols[i] - aTabCols[i-1];
//STRIP001              ++nCnt;
//STRIP001          }
//STRIP001      }
//STRIP001      nWish /= nCnt;
//STRIP001      for ( i = 0; i < aWish.Count(); ++i )
//STRIP001          if ( aWish[i] )
//STRIP001              aWish[i] = nWish;
//STRIP001  }
//STRIP001
//STRIP001  const USHORT nOldRight = aTabCols.GetRight();
//STRIP001
//STRIP001  //Um die Impl. einfach zu gestalten, aber trotzdem in den meissten Faellen
//STRIP001  //den Platz richtig auszunutzen laufen wir zweimal.
//STRIP001  //Problem: Erste Spalte wird breiter, die anderen aber erst danach
//STRIP001  //schmaler. Die Wunschbreite der ersten Spalte wuerde abgelehnt, weil
//STRIP001  //mit ihr die max. Breite der Tabelle ueberschritten wuerde.
//STRIP001  for ( USHORT k= 0; k < 2; ++k )
//STRIP001  {
//STRIP001      for ( i = 0; i <= aTabCols.Count(); ++i )
//STRIP001      {
//STRIP001          int nDiff = aWish[i];
//STRIP001          if ( nDiff )
//STRIP001          {
//STRIP001              int nMin = aMins[i];
//STRIP001              if ( nMin > nDiff )
//STRIP001                  nDiff = nMin;
//STRIP001
//STRIP001              if ( i == 0 )
//STRIP001              {
//STRIP001                  if( aTabCols.Count() )
//STRIP001                      nDiff -= aTabCols[0] - aTabCols.GetLeft();
//STRIP001                  else
//STRIP001                      nDiff -= aTabCols.GetRight() - aTabCols.GetLeft();
//STRIP001              }
//STRIP001              else if ( i == aTabCols.Count() )
//STRIP001                  nDiff -= aTabCols.GetRight() - aTabCols[i-1];
//STRIP001              else
//STRIP001                  nDiff -= aTabCols[i] - aTabCols[i-1];
//STRIP001
//STRIP001              long nTabRight = aTabCols.GetRight() + nDiff;
//STRIP001
//STRIP001              //Wenn die Tabelle zu breit wuerde begrenzen wir die Anpassung
//STRIP001              //auf das erlaubte Maximum.
//STRIP001              if ( !bBalance && nTabRight > aTabCols.GetRightMax() )
//STRIP001              {
//STRIP001                  const long nTmp = nTabRight - aTabCols.GetRightMax();
//STRIP001                  nDiff     -= nTmp;
//STRIP001                  nTabRight -= nTmp;
//STRIP001              }
//STRIP001              for ( USHORT i2 = i; i2 < aTabCols.Count(); ++i2 )
//STRIP001                  aTabCols[i2] += nDiff;
//STRIP001              aTabCols.SetRight( nTabRight );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  const USHORT nNewRight = aTabCols.GetRight();
//STRIP001
//STRIP001  //So, die richtige Arbeit koennen wir jetzt der SwTable ueberlassen.
//STRIP001  SetTabCols( aTabCols, FALSE, 0, (SwCellFrm*)pBoxFrm );
//STRIP001
//STRIP001  //Ggf. Ausrichtung der Tabelle Aendern.
//STRIP001  //Bei Automatischer Breite wird auf Linksbuendig umgeschaltet.
//STRIP001  //Bei Randattributen wird der Rechte Rand angepasst.
//STRIP001  if( !bBalance && nNewRight < nOldRight )
//STRIP001  {
//STRIP001      SwFrmFmt *pFmt = pTblNd->GetTable().GetFrmFmt();
//STRIP001      const SwFmtHoriOrient &rHori = pFmt->GetHoriOrient();
//STRIP001      if( rHori.GetHoriOrient() == HORI_FULL )
//STRIP001      {
//STRIP001          SwFmtHoriOrient aHori( rHori );
//STRIP001          aHori.SetHoriOrient( HORI_LEFT );
//STRIP001          pFmt->SetAttr( aHori );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001 }

}
