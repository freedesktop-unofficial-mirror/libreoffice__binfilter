/*************************************************************************
 *
 *  $RCSfile: sw_ndtbl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:22:58 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif


#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTFORDR_HXX //autogen
#include <fmtfordr.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTLSPLT_HXX
#include <fmtlsplt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _CELLFRM_HXX //autogen
#include <cellfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _TABCOL_HXX //autogen
#include <tabcol.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _TBLAFMT_HXX
#include <tblafmt.hxx>
#endif
#ifndef _SWCACHE_HXX
#include <swcache.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _FRMINF_HXX
#include <frminf.hxx>
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
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _ROLBCK_HXX
#include <rolbck.hxx>
#endif
#ifndef _TBLRWCL_HXX
#include <tblrwcl.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _FTNFRM_HXX
#include <ftnfrm.hxx>
#endif
#ifndef _ITABENUM_HXX
#include <itabenum.hxx>
#endif
#ifndef _SECTION_HXX //autogen
#include <section.hxx>
#endif
#ifndef _FRMTOOL_HXX //autogen
#include <frmtool.hxx>
#endif

#ifndef _NODE2LAY_HXX
#include <node2lay.hxx>
#endif

#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif

#ifndef _DOCSH_HXX
#include "docsh.hxx"
#endif

#ifdef _MSAVE_HXX
#include "msave.hxx"
#endif

#ifdef LINUX
#ifndef _TABCOL_HXX
#include <tabcol.hxx>
#endif
#endif

#include <node.hxx>
#include <ndtxt.hxx>
namespace binfilter {

const sal_Unicode T2T_PARA = 0x0a;

//STRIP001 extern void ClearFEShellTabCols();

// steht im gctable.cxx
//STRIP001 extern BOOL lcl_GC_Line_Border( const SwTableLine*& , void* pPara );

//STRIP001 class lcl_DelRedlines
//STRIP001 {
//STRIP001  SwDoc* pDoc;
//STRIP001 public:
//STRIP001  lcl_DelRedlines( const SwTableNode& rNd, BOOL bCheckForOwnRedline );
//STRIP001  lcl_DelRedlines( SwPaM& rPam );
//STRIP001
//STRIP001  ~lcl_DelRedlines() { pDoc->EndUndo(); }
//STRIP001 };
//STRIP001
//STRIP001 lcl_DelRedlines::lcl_DelRedlines( SwPaM & rPam) : pDoc( rPam.GetDoc() )
//STRIP001 {
//STRIP001  pDoc->StartUndo();
//STRIP001  if( !pDoc->IsIgnoreRedline() && pDoc->GetRedlineTbl().Count() )
//STRIP001      pDoc->AcceptRedline( rPam );
//STRIP001 }

/*N*/ void lcl_SetDfltBoxAttr( SwFrmFmt& rFmt, BYTE nId )
/*N*/ {
/*N*/   BOOL bTop = FALSE, bBottom = FALSE, bLeft = FALSE, bRight = FALSE;
/*N*/   switch ( nId )
/*N*/   {
/*?*/   case 0: bTop = bBottom = bLeft = TRUE;          break;
/*N*/   case 1: bTop = bBottom = bLeft = bRight = TRUE; break;
/*?*/   case 2: bBottom = bLeft = TRUE;                 break;
/*?*/   case 3: bBottom = bLeft = bRight = TRUE;        break;
/*N*/   }
/*N*/
/*N*/   const BOOL bHTML = rFmt.GetDoc()->IsHTMLMode();
/*N*/   Color aCol( bHTML ? COL_GRAY : COL_BLACK );
/*N*/   SvxBorderLine aLine( &aCol, DEF_LINE_WIDTH_0 );
/*N*/   if ( bHTML )
/*N*/   {
/*?*/       aLine.SetOutWidth( DEF_DOUBLE_LINE7_OUT );
/*?*/       aLine.SetInWidth ( DEF_DOUBLE_LINE7_IN  );
/*?*/       aLine.SetDistance( DEF_DOUBLE_LINE7_DIST);
/*N*/   }
/*N*/   SvxBoxItem aBox; aBox.SetDistance( 55 );
/*N*/   if ( bTop )
/*N*/       aBox.SetLine( &aLine, BOX_LINE_TOP );
/*N*/   if ( bBottom )
/*N*/       aBox.SetLine( &aLine, BOX_LINE_BOTTOM );
/*N*/   if ( bLeft )
/*N*/       aBox.SetLine( &aLine, BOX_LINE_LEFT );
/*N*/   if ( bRight )
/*N*/       aBox.SetLine( &aLine, BOX_LINE_RIGHT );
/*N*/   rFmt.SetAttr( aBox );
/*N*/ }

//STRIP001 void lcl_SetDfltBoxAttr( SwTableBox& rBox, SvPtrarr &rBoxFmtArr, BYTE nId,
//STRIP001                          const SwTableAutoFmt* pAutoFmt = 0 )
//STRIP001 {
//STRIP001  SvPtrarr* pArr = (SvPtrarr*)rBoxFmtArr[ nId ];
//STRIP001  if( !pArr )
//STRIP001  {
//STRIP001      pArr = new SvPtrarr;
//STRIP001      rBoxFmtArr.Replace( pArr, nId );
//STRIP001  }
//STRIP001
//STRIP001  SwTableBoxFmt* pNewBoxFmt = 0;
//STRIP001  SwFrmFmt* pBoxFmt = rBox.GetFrmFmt();
//STRIP001  for( USHORT n = 0; n < pArr->Count(); n += 2 )
//STRIP001      if( pArr->GetObject( n ) == pBoxFmt )
//STRIP001      {
//STRIP001          pNewBoxFmt = (SwTableBoxFmt*)pArr->GetObject( n + 1 );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001  if( !pNewBoxFmt )
//STRIP001  {
//STRIP001      SwDoc* pDoc = pBoxFmt->GetDoc();
//STRIP001      // das Format ist also nicht vorhanden, also neu erzeugen
//STRIP001      pNewBoxFmt = pDoc->MakeTableBoxFmt();
//STRIP001      pNewBoxFmt->SetAttr( pBoxFmt->GetAttrSet().Get( RES_FRM_SIZE ) );
//STRIP001
//STRIP001      if( pAutoFmt )
//STRIP001          pAutoFmt->UpdateToSet( nId, (SfxItemSet&)pNewBoxFmt->GetAttrSet(),
//STRIP001                                  SwTableAutoFmt::UPDATE_BOX,
//STRIP001                                  pDoc->GetNumberFormatter( TRUE ) );
//STRIP001      else
//STRIP001          ::lcl_SetDfltBoxAttr( *pNewBoxFmt, nId );
//STRIP001
//STRIP001      void* p = pBoxFmt;
//STRIP001      pArr->Insert( p, pArr->Count() );
//STRIP001      p = pNewBoxFmt;
//STRIP001      pArr->Insert( p, pArr->Count() );
//STRIP001  }
//STRIP001  rBox.ChgFrmFmt( pNewBoxFmt );
//STRIP001 }

/* --> #109161# */
static bool lcl_IsItemSet(const SwCntntNode & rNode, USHORT which)
{
    bool bResult = false;

    if (SFX_ITEM_SET == rNode.GetSwAttrSet().GetItemState(which))
        bResult = true;

    return bResult;
}

static bool lcl_IsItemSet(const SwFmt & rFmt, USHORT which)
{
    bool bResult = false;

    if (SFX_ITEM_SET == rFmt.GetAttrSet().GetItemState(which))
        bResult = true;

    return bResult;
}
/* <-- #109161# */

/*N*/ SwTableBoxFmt *lcl_CreateDfltBoxFmt( SwDoc &rDoc, SvPtrarr &rBoxFmtArr,
/*N*/                                   USHORT nCols, BYTE nId )
/*N*/ {
/*N*/   if ( !rBoxFmtArr[nId] )
/*N*/   {
/*N*/       SwTableBoxFmt* pBoxFmt = rDoc.MakeTableBoxFmt();
/*N*/       if( USHRT_MAX != nCols )
/*N*/           pBoxFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE,
/*N*/                                           USHRT_MAX / nCols, 0 ));
/*N*/       ::binfilter::lcl_SetDfltBoxAttr( *pBoxFmt, nId );
/*N*/       rBoxFmtArr.Replace( pBoxFmt, nId );
/*N*/   }
/*N*/   return (SwTableBoxFmt*)rBoxFmtArr[nId];
/*N*/ }

//STRIP001 SwTableBoxFmt *lcl_CreateAFmtBoxFmt( SwDoc &rDoc, SvPtrarr &rBoxFmtArr,
//STRIP001                                  const SwTableAutoFmt& rAutoFmt,
//STRIP001                                  USHORT nCols, BYTE nId )
//STRIP001 {
//STRIP001  if( !rBoxFmtArr[nId] )
//STRIP001  {
//STRIP001      SwTableBoxFmt* pBoxFmt = rDoc.MakeTableBoxFmt();
//STRIP001      rAutoFmt.UpdateToSet( nId, (SfxItemSet&)pBoxFmt->GetAttrSet(),
//STRIP001                              SwTableAutoFmt::UPDATE_BOX,
//STRIP001                              rDoc.GetNumberFormatter( TRUE ) );
//STRIP001      if( USHRT_MAX != nCols )
//STRIP001          pBoxFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE,
//STRIP001                                          USHRT_MAX / nCols, 0 ));
//STRIP001      rBoxFmtArr.Replace( pBoxFmt, nId );
//STRIP001  }
//STRIP001  return (SwTableBoxFmt*)rBoxFmtArr[nId];
//STRIP001 }

/*N*/ SwTableNode* SwDoc::IsIdxInTbl(const SwNodeIndex& rIdx)
/*N*/ {
/*N*/   SwTableNode* pTableNd = 0;
/*N*/   ULONG nIndex = rIdx.GetIndex();
/*N*/   do {
/*N*/       SwNode* pNd = (SwNode*)GetNodes()[ nIndex ]->StartOfSectionNode();
/*N*/       if( 0 != ( pTableNd = pNd->GetTableNode() ) )
/*?*/           break;
/*N*/
/*N*/       nIndex = pNd->GetIndex();
/*N*/   } while ( nIndex );
/*N*/   return pTableNd;
/*N*/ }


// --------------- einfuegen einer neuen Box --------------

    // fuege in der Line, vor der InsPos eine neue Box ein.

//STRIP001 BOOL SwNodes::InsBoxen( SwTableNode* pTblNd,
//STRIP001                      SwTableLine* pLine,
//STRIP001                      SwTableBoxFmt* pBoxFmt,
//STRIP001                      SwTxtFmtColl* pTxtColl,
//STRIP001                      SwAttrSet* pAutoAttr,
//STRIP001                      USHORT nInsPos,
//STRIP001                      USHORT nCnt )
//STRIP001 {
//STRIP001  if( !nCnt )
//STRIP001      return FALSE;
//STRIP001  ASSERT( pLine, "keine gueltige Zeile" );
//STRIP001
//STRIP001  // Index hinter die letzte Box der Line
//STRIP001  ULONG nIdxPos;
//STRIP001  SwTableBox *pPrvBox = 0, *pNxtBox = 0;
//STRIP001  if( pLine->GetTabBoxes().Count() )
//STRIP001  {
//STRIP001      if( nInsPos < pLine->GetTabBoxes().Count() )
//STRIP001      {
//STRIP001          if( 0 == (pPrvBox = pLine->FindPreviousBox( pTblNd->GetTable(),
//STRIP001                          pLine->GetTabBoxes()[ nInsPos ] )))
//STRIP001              pPrvBox = pLine->FindPreviousBox( pTblNd->GetTable() );
//STRIP001      }
//STRIP001      else if( 0 == ( pNxtBox = pLine->FindNextBox( pTblNd->GetTable(),
//STRIP001                          pLine->GetTabBoxes()[ nInsPos-1 ] )))
//STRIP001              pNxtBox = pLine->FindNextBox( pTblNd->GetTable() );
//STRIP001  }
//STRIP001  else if( 0 == ( pNxtBox = pLine->FindNextBox( pTblNd->GetTable() )))
//STRIP001      pPrvBox = pLine->FindPreviousBox( pTblNd->GetTable() );
//STRIP001
//STRIP001  if( !pPrvBox && !pNxtBox )
//STRIP001  {
//STRIP001      BOOL bSetIdxPos = TRUE;
//STRIP001      if( pTblNd->GetTable().GetTabLines().Count() && !nInsPos )
//STRIP001      {
//STRIP001          const SwTableLine* pTblLn = pLine;
//STRIP001          while( pTblLn->GetUpper() )
//STRIP001              pTblLn = pTblLn->GetUpper()->GetUpper();
//STRIP001
//STRIP001          if( pTblNd->GetTable().GetTabLines()[ 0 ] == pTblLn )
//STRIP001          {
//STRIP001              // also vor die erste Box der Tabelle
//STRIP001              while( ( pNxtBox = pLine->GetTabBoxes()[0])->GetTabLines().Count() )
//STRIP001                  pLine = pNxtBox->GetTabLines()[0];
//STRIP001              nIdxPos = pNxtBox->GetSttIdx();
//STRIP001              bSetIdxPos = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      if( bSetIdxPos )
//STRIP001          // Tabelle ohne irgendeinen Inhalt oder am Ende, also vors Ende
//STRIP001          nIdxPos = pTblNd->EndOfSectionIndex();
//STRIP001  }
//STRIP001  else if( pNxtBox )          // es gibt einen Nachfolger
//STRIP001      nIdxPos = pNxtBox->GetSttIdx();
//STRIP001  else                        // es gibt einen Vorgaenger
//STRIP001      nIdxPos = pPrvBox->GetSttNd()->EndOfSectionIndex() + 1;
//STRIP001
//STRIP001  SwNodeIndex aEndIdx( *this, nIdxPos );
//STRIP001  for( USHORT n = 0; n < nCnt; ++n )
//STRIP001  {
//STRIP001      SwStartNode* pSttNd = new SwStartNode( aEndIdx, ND_STARTNODE,
//STRIP001                                              SwTableBoxStartNode );
//STRIP001      pSttNd->pStartOfSection = pTblNd;
//STRIP001      SwEndNode* pEndNd = new SwEndNode( aEndIdx, *pSttNd );
//STRIP001
//STRIP001      pPrvBox = new SwTableBox( pBoxFmt, *pSttNd, pLine );
//STRIP001      pLine->GetTabBoxes().C40_INSERT( SwTableBox, pPrvBox, nInsPos + n );
//STRIP001
//STRIP001      if( NO_NUMBERING == pTxtColl->GetOutlineLevel()
//STRIP001 //FEATURE::CONDCOLL
//STRIP001          && RES_CONDTXTFMTCOLL != pTxtColl->Which()
//STRIP001 //FEATURE::CONDCOLL
//STRIP001      )
//STRIP001          new SwTxtNode( SwNodeIndex( *pSttNd->EndOfSectionNode() ),
//STRIP001                              pTxtColl, pAutoAttr );
//STRIP001      else
//STRIP001      {
//STRIP001          // Outline-Numerierung richtig behandeln !!!
//STRIP001          SwTxtNode* pTNd = new SwTxtNode(
//STRIP001                          SwNodeIndex( *pSttNd->EndOfSectionNode() ),
//STRIP001                          (SwTxtFmtColl*)GetDoc()->GetDfltTxtFmtColl(),
//STRIP001                          pAutoAttr );
//STRIP001          pTNd->ChgFmtColl( pTxtColl );
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

// --------------- einfuegen einer neuen Tabelle --------------

/*N*/ const SwTable* SwDoc::InsertTable( const SwPosition& rPos, USHORT nRows,
/*N*/                                   USHORT nCols, SwHoriOrient eAdjust,
/*N*/                                   USHORT nInsTblFlags,
/*N*/                                   const SwTableAutoFmt* pTAFmt,
/*N*/                                    const SvUShorts* pColArr,
/*N*/                                    BOOL bCalledFromShell )
/*N*/ {
/*N*/   ASSERT( nRows, "Tabelle ohne Zeile?" );
/*N*/   ASSERT( nCols, "Tabelle ohne Spalten?" );
/*N*/
/*N*/   {
/*N*/       // nicht in Fussnoten kopieren !!
/*N*/       if( rPos.nNode < GetNodes().GetEndOfInserts().GetIndex() &&
/*N*/           rPos.nNode >= GetNodes().GetEndOfInserts().StartOfSectionIndex() )
/*?*/           return 0;
/*N*/
/*N*/       // sollte das ColumnArray die falsche Anzahl haben wird es ignoriert!
/*N*/       if( pColArr &&
/*N*/           (nCols + ( HORI_NONE == eAdjust ? 2 : 1 )) != pColArr->Count() )
/*?*/           pColArr = 0;
/*N*/   }
/*N*/
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       AppendUndo( new SwUndoInsTbl( rPos, nCols, nRows, eAdjust,
/*N*/                                       nInsTblFlags, pTAFmt, pColArr ));
/*N*/   }
/*N*/
/*N*/   // fuege erstmal die Nodes ein
/*N*/   // hole das Auto-Format fuer die Tabelle
/*N*/   SwTxtFmtColl *pBodyColl = GetTxtCollFromPool( RES_POOLCOLL_TABLE ),
/*N*/                *pHeadColl = pBodyColl;
/*N*/
/*N*/   BOOL bDfltBorders = nInsTblFlags & DEFAULT_BORDER;
/*N*/
/*N*/   if( (nInsTblFlags & HEADLINE) && (1 != nRows || !bDfltBorders) )
/*?*/       pHeadColl = GetTxtCollFromPool( RES_POOLCOLL_TABLE_HDLN );
/*N*/
/*N*/   /* #106283# Save content node to extract FRAMEDIR from. */
/*N*/   const SwCntntNode * pCntntNd = rPos.nNode.GetNode().GetCntntNode();
/*N*/
    /* #109161# If we are called from a shell pass the attrset from
        pCntntNd (aka the node the table is inserted at) thus causing
        SwNodes::InsertTable to propagate an adjust item if
        necessary. */
/*N*/   SwTableNode *pTblNd = GetNodes().InsertTable
/*N*/         ( rPos.nNode, nCols, pBodyColl, nRows, pHeadColl,
/*N*/           bCalledFromShell ? &pCntntNd->GetSwAttrSet() : 0 );
/*N*/
/*N*/   // dann erstelle die Box/Line/Table-Struktur
/*N*/   SwTableLineFmt* pLineFmt = MakeTableLineFmt();
/*N*/   SwTableFmt* pTableFmt = MakeTblFrmFmt( GetUniqueTblName(), GetDfltFrmFmt() );
/*N*/
    /* #106283# If the node to insert the table at is a context node and has a
       non-default FRAMEDIR propagate it to the table. */
/*N*/   if (pCntntNd)
/*N*/   {
/*N*/       const SwAttrSet & aNdSet = pCntntNd->GetSwAttrSet();
/*N*/       const SfxPoolItem *pItem = NULL;
/*N*/
/*N*/       if (SFX_ITEM_SET == aNdSet.GetItemState( RES_FRAMEDIR, TRUE, &pItem )
/*N*/           && pItem != NULL)
/*N*/       {
/*N*/           pTableFmt->SetAttr( *pItem );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //Orientation am Fmt der Table setzen
/*N*/   pTableFmt->SetAttr( SwFmtHoriOrient( 0, eAdjust ) );
/*N*/   // alle Zeilen haben die Fill-Order von links nach rechts !
/*N*/   pLineFmt->SetAttr( SwFmtFillOrder( ATT_LEFT_TO_RIGHT ));
/*N*/
/*N*/   // die Tabelle bekommt USHRT_MAX als default SSize
/*N*/   SwTwips nWidth = USHRT_MAX;
/*N*/   if( pColArr )
/*N*/   {
/*?*/       USHORT nSttPos = (*pColArr)[ 0 ];
/*?*/       USHORT nLastPos = (*pColArr)[ USHORT(pColArr->Count()-1)];
/*?*/       if( HORI_NONE == eAdjust )
/*?*/       {
/*?*/           USHORT nFrmWidth = nLastPos;
/*?*/           nLastPos = (*pColArr)[ USHORT(pColArr->Count()-2)];
/*?*/           pTableFmt->SetAttr( SvxLRSpaceItem( nSttPos, nFrmWidth - nLastPos ) );
/*?*/       }
/*?*/       nWidth = nLastPos - nSttPos;
/*N*/   }
/*N*/   pTableFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nWidth ));
/*N*/   if( !(nInsTblFlags & SPLIT_LAYOUT) )
/*?*/       pTableFmt->SetAttr( SwFmtLayoutSplit( FALSE ));
/*N*/
/*N*/   // verschiebe ggfs. die harten PageDesc/PageBreak Attribute:
/*N*/   SwCntntNode* pNextNd = GetNodes()[ pTblNd->EndOfSectionIndex()+1 ]
/*N*/                           ->GetCntntNode();
/*N*/   if( pNextNd && pNextNd->GetpSwAttrSet() )
/*N*/   {
/*?*/       SwAttrSet* pNdSet = pNextNd->GetpSwAttrSet();
/*?*/       const SfxPoolItem *pItem;
/*?*/       if( SFX_ITEM_SET == pNdSet->GetItemState( RES_PAGEDESC, FALSE,
/*?*/           &pItem ) )
/*?*/       {
/*?*/           pTableFmt->SetAttr( *pItem );
/*?*/           pNextNd->ResetAttr( RES_PAGEDESC );
/*?*/           pNdSet = pNextNd->GetpSwAttrSet();
/*?*/       }
/*?*/       if( pNdSet && SFX_ITEM_SET == pNdSet->GetItemState( RES_BREAK, FALSE,
/*?*/            &pItem ) )
/*?*/       {
/*?*/           pTableFmt->SetAttr( *pItem );
/*?*/           pNextNd->ResetAttr( RES_BREAK );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   SwTable * pNdTbl = &pTblNd->GetTable();
/*N*/   pTableFmt->Add( pNdTbl );       // das Frame-Format setzen
/*N*/
/*N*/   pNdTbl->SetHeadlineRepeat( HEADLINE_REPEAT == (nInsTblFlags & HEADLINE_REPEAT) );
/*N*/
/*N*/   SvPtrarr aBoxFmtArr( 0, 16 );
/*N*/   SwTableBoxFmt* pBoxFmt = 0;
/*N*/   if( !bDfltBorders && !pTAFmt )
/*N*/   {
/*?*/       pBoxFmt = MakeTableBoxFmt();
/*?*/       pBoxFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, USHRT_MAX / nCols, 0 ));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       const USHORT nBoxArrLen = pTAFmt ? 16 : 4;
/*N*/       for( USHORT i = 0; i < nBoxArrLen; ++i )
/*N*/           aBoxFmtArr.Insert( (void*)0, i );
/*N*/   }
/*N*/   SfxItemSet aCharSet( GetAttrPool(), RES_CHRATR_BEGIN, RES_PARATR_END-1 );
/*N*/
/*N*/   SwNodeIndex aNdIdx( *pTblNd, 1 );   // auf den ersten Box-StartNode
/*N*/   SwTableLines& rLines = pNdTbl->GetTabLines();
/*N*/   for( USHORT n = 0; n < nRows; ++n )
/*N*/   {
/*N*/       SwTableLine* pLine = new SwTableLine( pLineFmt, nCols, 0 );
/*N*/       rLines.C40_INSERT( SwTableLine, pLine, n );
/*N*/       SwTableBoxes& rBoxes = pLine->GetTabBoxes();
/*N*/       for( USHORT i = 0; i < nCols; ++i )
/*N*/       {
/*N*/           SwTableBoxFmt *pBoxF;
/*N*/           if( pTAFmt )
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 BYTE nId = !n ? 0 : (( n+1 == nRows )
//STRIP001 /*?*/                                        ? 12 : (4 * (1 + ((n-1) & 1 ))));
//STRIP001 /*?*/                nId += !i ? 0 : ( i+1 == nCols ? 3 : (1 + ((i-1) & 1)));
//STRIP001 /*?*/                pBoxF = ::lcl_CreateAFmtBoxFmt( *this, aBoxFmtArr, *pTAFmt,
//STRIP001 /*?*/                                                nCols, nId );
//STRIP001 /*?*/
//STRIP001 /*?*/                // ggfs. noch die Absatz/ZeichenAttribute setzen
//STRIP001 /*?*/                if( pTAFmt->IsFont() || pTAFmt->IsJustify() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    aCharSet.ClearItem();
//STRIP001 /*?*/                    pTAFmt->UpdateToSet( nId, aCharSet,
//STRIP001 /*?*/                                        SwTableAutoFmt::UPDATE_CHAR, 0 );
//STRIP001 /*?*/                    if( aCharSet.Count() )
//STRIP001 /*?*/                        GetNodes()[ aNdIdx.GetIndex()+1 ]->GetCntntNode()->
//STRIP001 /*?*/                            SetAttr( aCharSet );
//STRIP001 /*?*/                }
/*N*/           }
/*N*/           else if( bDfltBorders )
/*N*/           {
/*N*/               BYTE nBoxId = (i < nCols - 1 ? 0 : 1) + (n ? 2 : 0 );
/*N*/               pBoxF = ::binfilter::lcl_CreateDfltBoxFmt( *this, aBoxFmtArr, nCols, nBoxId);
/*N*/           }
/*N*/           else
/*?*/               pBoxF = pBoxFmt;
/*N*/
/*N*/           // fuer AutoFormat bei der Eingabe: beim Einfuegen der Tabelle
/*N*/           // werden gleich die Spalten gesetzt. Im Array stehen die
/*N*/           // Positionen der Spalten!! (nicht deren Breite!)
/*N*/           if( pColArr )
/*N*/           {
/*?*/               nWidth = (*pColArr)[ USHORT(i + 1) ] - (*pColArr)[ i ];
/*?*/               if( pBoxF->GetFrmSize().GetWidth() != nWidth )
/*?*/               {
/*?*/                   if( pBoxF->GetDepends() )       // neues Format erzeugen!
/*?*/                   {
/*?*/                       SwTableBoxFmt *pNewFmt = MakeTableBoxFmt();
/*?*/                       *pNewFmt = *pBoxF;
/*?*/                       pBoxF = pNewFmt;
/*?*/                   }
/*?*/                   pBoxF->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nWidth ));
/*?*/               }
/*N*/           }
/*N*/
/*N*/           SwTableBox *pBox = new SwTableBox( pBoxF, aNdIdx, pLine);
/*N*/           rBoxes.C40_INSERT( SwTableBox, pBox, i );
/*N*/           aNdIdx += 3;        // StartNode, TextNode, EndNode  == 3 Nodes
/*N*/       }
/*N*/   }
/*N*/   // und Frms einfuegen.
/*N*/   GetNodes().GoNext( &aNdIdx );      // zum naechsten ContentNode
/*N*/   pTblNd->MakeFrms( &aNdIdx );
/*N*/
/*N*/   if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SwPaM aPam( *pTblNd->EndOfSectionNode(), *pTblNd, 1 );
//STRIP001 /*?*/        if( IsRedlineOn() )
//STRIP001 /*?*/            AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/        else
//STRIP001 /*?*/            SplitRedline( aPam );
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return pNdTbl;
/*N*/ }

/*N*/ SwTableNode* SwNodes::InsertTable( const SwNodeIndex& rNdIdx,
/*N*/                                   USHORT nBoxes,
/*N*/                                   SwTxtFmtColl* pCntntTxtColl,
/*N*/                                   USHORT nLines,
/*N*/                                  SwTxtFmtColl* pHeadlineTxtColl,
/*N*/                                    const SwAttrSet * pAttrSet)
/*N*/ {
/*N*/   if( !nBoxes )
/*?*/       return 0;
/*N*/
/*N*/   // wenn Lines angegeben, erzeuge die Matrix aus Lines & Boxen
/*N*/   if( !pHeadlineTxtColl || !nLines )
/*N*/       pHeadlineTxtColl = pCntntTxtColl;
/*N*/
/*N*/   SwTableNode * pTblNd = new SwTableNode( rNdIdx );
/*N*/   SwEndNode* pEndNd = new SwEndNode( rNdIdx, *pTblNd );
/*N*/
/*N*/   if( !nLines )       // fuer die FOR-Schleife
/*N*/       ++nLines;
/*N*/
/*N*/   SwNodeIndex aIdx( *pEndNd );
/*N*/   register SwTxtFmtColl* pTxtColl = pHeadlineTxtColl;
/*N*/   for( register USHORT nL = 0; nL < nLines; ++nL )
/*N*/   {
/*N*/       for( register USHORT nB = 0; nB < nBoxes; ++nB )
/*N*/       {
/*N*/           SwStartNode* pSttNd = new SwStartNode( aIdx, ND_STARTNODE,
/*N*/                                                   SwTableBoxStartNode );
/*N*/           pSttNd->pStartOfSection = pTblNd;

            /** #109161# If there is no adjust item in pTxtColl
                 propagate any existing adjust item in pAttrSet to the
                 newly created context node in the new cell.
             */
/*N*/           SwTxtNode * pTmpNd = new SwTxtNode( aIdx, pTxtColl );
/*N*/
/*N*/             const SfxPoolItem * pItem = NULL;
/*N*/
/*N*/             if (! lcl_IsItemSet(*pTmpNd, RES_PARATR_ADJUST) &&
/*N*/                 pAttrSet != NULL &&
/*N*/                 SFX_ITEM_SET == pAttrSet->GetItemState( RES_PARATR_ADJUST, TRUE,
/*N*/                                                         &pItem)
/*N*/                 )
/*N*/             {
/*N*/                 static_cast<SwCntntNode *>(pTmpNd)->SetAttr(*pItem);
/*N*/             }
/*N*/
/*N*/           new SwEndNode( aIdx, *pSttNd );
/*N*/       }
/*N*/       pTxtColl = pCntntTxtColl;
/*N*/   }
/*N*/   return pTblNd;
/*N*/ }


//---------------- Text -> Tabelle -----------------------

//STRIP001 const SwTable* SwDoc::TextToTable( const SwPaM& rRange, sal_Unicode cCh,
//STRIP001                                  SwHoriOrient eAdjust,
//STRIP001                                  USHORT nInsTblFlags,
//STRIP001                                  const SwTableAutoFmt* pTAFmt )
//STRIP001 {
//STRIP001  // pruefe ob in der Selection eine Tabelle liegt
//STRIP001  const SwPosition *pStt = rRange.Start(), *pEnd = rRange.End();
//STRIP001  {
//STRIP001      ULONG nCnt = pStt->nNode.GetIndex();
//STRIP001      for( ; nCnt <= pEnd->nNode.GetIndex(); ++nCnt )
//STRIP001          if( !GetNodes()[ nCnt ]->IsTxtNode() )
//STRIP001              return 0;
//STRIP001  }
//STRIP001
//STRIP001  /* #106283# Save first node in the selection if it is a context node. */
//STRIP001  SwCntntNode * pSttCntntNd = pStt->nNode.GetNode().GetCntntNode();
//STRIP001
//STRIP001  SwPaM aOriginal( *pStt, *pEnd );
//STRIP001  pStt = aOriginal.GetMark();
//STRIP001  pEnd = aOriginal.GetPoint();
//STRIP001
//STRIP001  lcl_DelRedlines aDelRedl( aOriginal );
//STRIP001
//STRIP001  SwUndoTxtToTbl* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      StartUndo( UNDO_TEXTTOTABLE );
//STRIP001      pUndo = new SwUndoTxtToTbl( aOriginal, cCh, eAdjust, nInsTblFlags, pTAFmt );
//STRIP001      AppendUndo( pUndo );
//STRIP001
//STRIP001      // das Splitten vom TextNode nicht in die Undohistory aufnehmen
//STRIP001      DoUndo( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  // die Bookmarks loeschen und die Cursor der CrsrShell verschieben
//STRIP001  _DelBookmarks( pStt->nNode, pEnd->nNode, 0,
//STRIP001                  &pStt->nContent, &pEnd->nContent );
//STRIP001  ::PaMCorrAbs( aOriginal, *pEnd );
//STRIP001
//STRIP001  // sorge dafuer, das der Bereich auf Node-Grenzen liegt
//STRIP001  SwNodeRange aRg( pStt->nNode, pEnd->nNode );
//STRIP001  if( pStt->nContent.GetIndex() )
//STRIP001      SplitNode( *pStt );
//STRIP001
//STRIP001  BOOL bEndCntnt = 0 != pEnd->nContent.GetIndex();
//STRIP001  // nicht splitten am Ende der Zeile (aber am Ende vom Doc!!)
//STRIP001  if( bEndCntnt )
//STRIP001  {
//STRIP001      if( pEnd->nNode.GetNode().GetCntntNode()->Len() != pEnd->nContent.GetIndex()
//STRIP001          || pEnd->nNode.GetIndex() >= GetNodes().GetEndOfContent().GetIndex()-1 )
//STRIP001      {
//STRIP001          SplitNode( *pEnd );
//STRIP001          ((SwNodeIndex&)pEnd->nNode)--;
//STRIP001          ((SwIndex&)pEnd->nContent).Assign(
//STRIP001                              pEnd->nNode.GetNode().GetCntntNode(), 0 );
//STRIP001          // ein Node und am Ende ??
//STRIP001          if( pStt->nNode.GetIndex() >= pEnd->nNode.GetIndex() )
//STRIP001              aRg.aStart--;
//STRIP001      }
//STRIP001      else
//STRIP001          aRg.aEnd++;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  if( aRg.aEnd.GetIndex() == aRg.aStart.GetIndex() )
//STRIP001  {
//STRIP001      ASSERT( FALSE, "Kein Bereich" );
//STRIP001      aRg.aEnd++;
//STRIP001  }
//STRIP001
//STRIP001  // Wir gehen jetzt immer ueber die Upper, um die Tabelle einzufuegen:
//STRIP001  SwNode2Layout aNode2Layout( aRg.aStart.GetNode() );
//STRIP001
//STRIP001  DoUndo( 0 != pUndo );
//STRIP001
//STRIP001  // dann erstelle die Box/Line/Table-Struktur
//STRIP001  SwTableBoxFmt* pBoxFmt = MakeTableBoxFmt();
//STRIP001  SwTableLineFmt* pLineFmt = MakeTableLineFmt();
//STRIP001  SwTableFmt* pTableFmt = MakeTblFrmFmt( GetUniqueTblName(), GetDfltFrmFmt() );
//STRIP001
//STRIP001  // alle Zeilen haben die Fill-Order von links nach rechts !
//STRIP001  pLineFmt->SetAttr( SwFmtFillOrder( ATT_LEFT_TO_RIGHT ));
//STRIP001  // die Tabelle bekommt USHRT_MAX als default SSize
//STRIP001  pTableFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, USHRT_MAX ));
//STRIP001  if( !(nInsTblFlags & SPLIT_LAYOUT) )
//STRIP001      pTableFmt->SetAttr( SwFmtLayoutSplit( FALSE ));
//STRIP001
//STRIP001  /* #106283# If the first node in the selection is a context node and if it
//STRIP001        has an item FRAMEDIR set (no default) propagate the item to the
//STRIP001        replacing table. */
//STRIP001  if (pSttCntntNd)
//STRIP001  {
//STRIP001      const SwAttrSet & aNdSet = pSttCntntNd->GetSwAttrSet();
//STRIP001      const SfxPoolItem *pItem = NULL;
//STRIP001
//STRIP001      if (SFX_ITEM_SET == aNdSet.GetItemState( RES_FRAMEDIR, TRUE, &pItem )
//STRIP001          && pItem != NULL)
//STRIP001      {
//STRIP001          pTableFmt->SetAttr( *pItem );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SwTableNode* pTblNd = GetNodes().TextToTable( aRg, cCh, pTableFmt,
//STRIP001                                  pLineFmt, pBoxFmt,
//STRIP001                              GetTxtCollFromPool( RES_POOLCOLL_STANDARD ),
//STRIP001                              pUndo );
//STRIP001
//STRIP001  SwTable * pNdTbl = &pTblNd->GetTable();
//STRIP001  ASSERT( pNdTbl, "kein Tabellen-Node angelegt."  )
//STRIP001
//STRIP001  pNdTbl->SetHeadlineRepeat( HEADLINE_REPEAT == (nInsTblFlags & HEADLINE_REPEAT) );
//STRIP001
//STRIP001  BOOL bUseBoxFmt = FALSE;
//STRIP001  if( !pBoxFmt->GetDepends() )
//STRIP001  {
//STRIP001      // die Formate an den Boxen haben schon die richtige Size, es darf
//STRIP001      // also nur noch die richtige Umrandung/AutoFmt gesetzt werden.
//STRIP001      bUseBoxFmt = TRUE;
//STRIP001      pTableFmt->SetAttr( pBoxFmt->GetFrmSize() );
//STRIP001      delete pBoxFmt;
//STRIP001      eAdjust = HORI_NONE;
//STRIP001  }
//STRIP001
//STRIP001  //Orientation am Fmt der Table setzen
//STRIP001  pTableFmt->SetAttr( SwFmtHoriOrient( 0, eAdjust ) );
//STRIP001  pTableFmt->Add( pNdTbl );       // das Frame-Format setzen
//STRIP001
//STRIP001  if( pTAFmt || (nInsTblFlags & DEFAULT_BORDER) )
//STRIP001  {
//STRIP001      SwTableBoxFmt* pBoxFmt = 0;
//STRIP001
//STRIP001      BYTE nBoxArrLen = pTAFmt ? 16 : 4;
//STRIP001      SvPtrarr aBoxFmtArr( nBoxArrLen, 0 );
//STRIP001      {
//STRIP001          for( BYTE i = 0; i < nBoxArrLen; ++i )
//STRIP001              aBoxFmtArr.Insert( (void*)0, i );
//STRIP001      }
//STRIP001
//STRIP001      SfxItemSet aCharSet( GetAttrPool(), RES_CHRATR_BEGIN, RES_PARATR_END-1 );
//STRIP001      SwHistory* pHistory = pUndo ? &pUndo->GetHistory() : 0;
//STRIP001
//STRIP001      SwTableBoxFmt *pBoxF;
//STRIP001      SwTableLines& rLines = pNdTbl->GetTabLines();
//STRIP001      USHORT nRows = rLines.Count();
//STRIP001      for( USHORT n = 0; n < nRows; ++n )
//STRIP001      {
//STRIP001          SwTableBoxes& rBoxes = rLines[ n ]->GetTabBoxes();
//STRIP001          USHORT nCols = rBoxes.Count();
//STRIP001          for( USHORT i = 0; i < nCols; ++i )
//STRIP001          {
//STRIP001              SwTableBox* pBox = rBoxes[ i ];
//STRIP001              BOOL bChgSz = FALSE;
//STRIP001
//STRIP001              if( pTAFmt )
//STRIP001              {
//STRIP001                  BYTE nId = !n ? 0 : (( n+1 == nRows )
//STRIP001                                          ? 12 : (4 * (1 + ((n-1) & 1 ))));
//STRIP001                  nId += !i ? 0 : ( i+1 == nCols ? 3 : (1 + ((i-1) & 1)));
//STRIP001                  if( bUseBoxFmt )
//STRIP001                      ::lcl_SetDfltBoxAttr( *pBox, aBoxFmtArr, nId, pTAFmt );
//STRIP001                  else
//STRIP001                  {
//STRIP001                      bChgSz = 0 == aBoxFmtArr[ nId ];
//STRIP001                      pBoxF = ::lcl_CreateAFmtBoxFmt( *this, aBoxFmtArr,
//STRIP001                                              *pTAFmt, USHRT_MAX, nId );
//STRIP001                  }
//STRIP001
//STRIP001                  // ggfs. noch die Absatz/ZeichenAttribute setzen
//STRIP001                  if( pTAFmt->IsFont() || pTAFmt->IsJustify() )
//STRIP001                  {
//STRIP001                      aCharSet.ClearItem();
//STRIP001                      pTAFmt->UpdateToSet( nId, aCharSet,
//STRIP001                                          SwTableAutoFmt::UPDATE_CHAR, 0 );
//STRIP001                      if( aCharSet.Count() )
//STRIP001                      {
//STRIP001                          ULONG nSttNd = pBox->GetSttIdx()+1;
//STRIP001                          ULONG nEndNd = pBox->GetSttNd()->EndOfSectionIndex();
//STRIP001                          for( ; nSttNd < nEndNd; ++nSttNd )
//STRIP001                          {
//STRIP001                              SwCntntNode* pNd = GetNodes()[ nSttNd ]->GetCntntNode();
//STRIP001                              if( pNd )
//STRIP001                              {
//STRIP001                                  if( pHistory )
//STRIP001                                  {
//STRIP001                                      SwRegHistory aReg( pNd, *pNd, pHistory );
//STRIP001                                      pNd->SetAttr( aCharSet );
//STRIP001                                  }
//STRIP001                                  else
//STRIP001                                      pNd->SetAttr( aCharSet );
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  BYTE nId = (i < nCols - 1 ? 0 : 1) + (n ? 2 : 0 );
//STRIP001                  if( bUseBoxFmt )
//STRIP001                      ::lcl_SetDfltBoxAttr( *pBox, aBoxFmtArr, nId );
//STRIP001                  else
//STRIP001                  {
//STRIP001                      bChgSz = 0 == aBoxFmtArr[ nId ];
//STRIP001                      pBoxF = ::lcl_CreateDfltBoxFmt( *this, aBoxFmtArr,
//STRIP001                                                      USHRT_MAX, nId );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( !bUseBoxFmt )
//STRIP001              {
//STRIP001                  if( bChgSz )
//STRIP001                      pBoxF->SetAttr( pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001                  pBox->ChgFrmFmt( pBoxF );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bUseBoxFmt )
//STRIP001      {
//STRIP001          for( BYTE i = 0; i < nBoxArrLen; ++i )
//STRIP001          {
//STRIP001              SvPtrarr* pArr = (SvPtrarr*)aBoxFmtArr[ i ];
//STRIP001              delete pArr;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // JP 03.04.97: Inhalt der Boxen auf Zahlen abpruefen
//STRIP001  if( IsInsTblFormatNum() )
//STRIP001  {
//STRIP001      for( USHORT nBoxes = pNdTbl->GetTabSortBoxes().Count(); nBoxes; )
//STRIP001          ChkBoxNumFmt( *pNdTbl->GetTabSortBoxes()[ --nBoxes ], FALSE );
//STRIP001  }
//STRIP001
//STRIP001  ULONG nIdx = pTblNd->GetIndex();
//STRIP001  aNode2Layout.RestoreUpperFrms( GetNodes(), nIdx, nIdx + 1 );
//STRIP001
//STRIP001  {
//STRIP001      SwPaM& rTmp = (SwPaM&)rRange;   // Point immer an den Anfang
//STRIP001      rTmp.DeleteMark();
//STRIP001      rTmp.GetPoint()->nNode = *pTblNd;
//STRIP001      SwCntntNode* pCNd = GetNodes().GoNext( &rTmp.GetPoint()->nNode );
//STRIP001      rTmp.GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001      EndUndo( UNDO_TEXTTOTABLE );
//STRIP001
//STRIP001  SetModified();
//STRIP001  SetFieldsDirty( TRUE );
//STRIP001  return pNdTbl;
//STRIP001 }

//STRIP001 SwTableNode* SwNodes::TextToTable( const SwNodeRange& rRange, sal_Unicode cCh,
//STRIP001                                  SwTableFmt* pTblFmt,
//STRIP001                                  SwTableLineFmt* pLineFmt,
//STRIP001                                  SwTableBoxFmt* pBoxFmt,
//STRIP001                                  SwTxtFmtColl* pTxtColl,
//STRIP001                                  SwUndoTxtToTbl* pUndo )
//STRIP001 {
//STRIP001  if( rRange.aStart >= rRange.aEnd )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwTableNode * pTblNd = new SwTableNode( rRange.aStart );
//STRIP001  SwEndNode* pEndNd = new SwEndNode( rRange.aEnd, *pTblNd );
//STRIP001
//STRIP001  SwDoc* pDoc = GetDoc();
//STRIP001  SvUShorts aPosArr( 0, 16 );
//STRIP001  SwTable * pTable = &pTblNd->GetTable();
//STRIP001  SwTableLine* pLine;
//STRIP001  SwTableBox* pBox;
//STRIP001  USHORT nBoxes, nLines, nMaxBoxes = 0;
//STRIP001
//STRIP001  SwHistory* pHistory = pUndo ? &pUndo->GetHistory() : 0;
//STRIP001
//STRIP001  SwNodeIndex aSttIdx( *pTblNd, 1 );
//STRIP001  SwNodeIndex aEndIdx( rRange.aEnd, -1 );
//STRIP001  for( nLines = 0, nBoxes = 0;
//STRIP001      aSttIdx.GetIndex() < aEndIdx.GetIndex();
//STRIP001      aSttIdx += 2, nLines++, nBoxes = 0 )
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd = aSttIdx.GetNode().GetTxtNode();
//STRIP001      ASSERT( pTxtNd, "nur TextNodes in der Tabelle aufnehmen" );
//STRIP001
//STRIP001      if( !nLines && 0x0b == cCh )
//STRIP001      {
//STRIP001          cCh = 0x09;
//STRIP001
//STRIP001          // JP 28.10.96: vom 1. Node die Positionen des Trenners besorgen,
//STRIP001          //              damit die Boxen entsprechend eingestellt werden
//STRIP001          SwTxtFrmInfo aFInfo( (SwTxtFrm*)pTxtNd->GetFrm() );
//STRIP001          if( aFInfo.IsOneLine() )        // nur dann sinnvoll!
//STRIP001          {
//STRIP001              const sal_Unicode* pTxt = pTxtNd->GetTxt().GetBuffer();
//STRIP001              for( xub_StrLen nChPos = 0; *pTxt; ++nChPos, ++pTxt )
//STRIP001              {
//STRIP001                  if( *pTxt == cCh )
//STRIP001                  {
//STRIP001                      aPosArr.Insert( aFInfo.GetCharPos( nChPos+1, FALSE ),
//STRIP001                                      aPosArr.Count() );
//STRIP001                  }
//STRIP001               }
//STRIP001
//STRIP001              aPosArr.Insert( /*aFInfo.GetFrm()->Frm().Left() +*/
//STRIP001                                 aFInfo.GetFrm()->IsVertical() ?
//STRIP001                                 aFInfo.GetFrm()->Prt().Bottom() :
//STRIP001                                 aFInfo.GetFrm()->Prt().Right(),
//STRIP001                              aPosArr.Count() );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // die alten Frames loeschen, es werden neue erzeugt
//STRIP001      pTxtNd->DelFrms();
//STRIP001
//STRIP001      // PageBreaks/PageDesc/ColBreak rausschmeissen.
//STRIP001      SwAttrSet* pSet = pTxtNd->GetpSwAttrSet();
//STRIP001      if( pSet )
//STRIP001      {
//STRIP001 // das entfernen der PageBreaks erst nach dem erzeugen der Tabelle
//STRIP001 // erfolgen, denn sonst stehen sie falsch in der History !!!
//STRIP001 //           SwRegHistory aRegH( pTxtNd, *pTxtNd, pHistory );
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == pSet->GetItemState( RES_BREAK, FALSE, &pItem ) )
//STRIP001          {
//STRIP001              if( !nLines )
//STRIP001                  pTblFmt->SetAttr( *pItem );
//STRIP001              pTxtNd->SwCntntNode::ResetAttr( RES_BREAK );
//STRIP001              pSet = pTxtNd->GetpSwAttrSet();
//STRIP001          }
//STRIP001
//STRIP001          if( pSet && SFX_ITEM_SET == pSet->GetItemState(
//STRIP001              RES_PAGEDESC, FALSE, &pItem ) &&
//STRIP001              ((SwFmtPageDesc*)pItem)->GetPageDesc() )
//STRIP001          {
//STRIP001              if( !nLines )
//STRIP001                  pTblFmt->SetAttr( *pItem );
//STRIP001              pTxtNd->SwCntntNode::ResetAttr( RES_PAGEDESC );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // setze den bei allen TextNode in der Tabelle den TableNode
//STRIP001      // als StartNode
//STRIP001      pTxtNd->pStartOfSection = pTblNd;
//STRIP001
//STRIP001      pLine = new SwTableLine( pLineFmt, 1, 0 );
//STRIP001      pTable->GetTabLines().C40_INSERT( SwTableLine, pLine, nLines );
//STRIP001
//STRIP001      SwStartNode* pSttNd;
//STRIP001      SwPosition aCntPos( aSttIdx, SwIndex( pTxtNd ));
//STRIP001
//STRIP001      SvULongs aBkmkArr( 15, 15 );
//STRIP001      _SaveCntntIdx( pDoc, aSttIdx.GetIndex(), pTxtNd->GetTxt().Len(), aBkmkArr );
//STRIP001
//STRIP001      const sal_Unicode* pTxt = pTxtNd->GetTxt().GetBuffer();
//STRIP001
//STRIP001      if( T2T_PARA != cCh )
//STRIP001          for( xub_StrLen nChPos = 0; *pTxt; ++nChPos, ++pTxt )
//STRIP001              if( *pTxt == cCh )
//STRIP001              {
//STRIP001                  aCntPos.nContent = nChPos;
//STRIP001                  SwCntntNode* pNewNd = pTxtNd->SplitNode( aCntPos );
//STRIP001
//STRIP001                  if( aBkmkArr.Count() )
//STRIP001                      _RestoreCntntIdx( aBkmkArr, *pNewNd, nChPos,
//STRIP001                                          nChPos + 1 );
//STRIP001
//STRIP001                  // Trennzeichen loeschen und SuchString korrigieren
//STRIP001                  pTxtNd->Erase( aCntPos.nContent, 1 );
//STRIP001                  pTxt = pTxtNd->GetTxt().GetBuffer();
//STRIP001                  nChPos = 0;
//STRIP001                  --nChPos, --pTxt;           // for the ++ in the for loop !!!
//STRIP001
//STRIP001                  // setze bei allen TextNodes in der Tabelle den TableNode
//STRIP001                  // als StartNode
//STRIP001                  const SwNodeIndex aTmpIdx( aCntPos.nNode, -1 );
//STRIP001                  pSttNd = new SwStartNode( aTmpIdx, ND_STARTNODE,
//STRIP001                                              SwTableBoxStartNode );
//STRIP001                  new SwEndNode( aCntPos.nNode, *pSttNd );
//STRIP001                  pNewNd->pStartOfSection = pSttNd;
//STRIP001
//STRIP001                  // Section der Box zuweisen
//STRIP001                  pBox = new SwTableBox( pBoxFmt, *pSttNd, pLine );
//STRIP001                  pLine->GetTabBoxes().C40_INSERT( SwTableBox, pBox, nBoxes++ );
//STRIP001              }
//STRIP001
//STRIP001      // und jetzt den letzten Teil-String
//STRIP001      if( aBkmkArr.Count() )
//STRIP001          _RestoreCntntIdx( aBkmkArr, *pTxtNd, pTxtNd->GetTxt().Len(),
//STRIP001                              pTxtNd->GetTxt().Len()+1 );
//STRIP001
//STRIP001      pSttNd = new SwStartNode( aCntPos.nNode, ND_STARTNODE, SwTableBoxStartNode );
//STRIP001      const SwNodeIndex aTmpIdx( aCntPos.nNode, 1 );
//STRIP001      new SwEndNode( aTmpIdx, *pSttNd  );
//STRIP001      pTxtNd->pStartOfSection = pSttNd;
//STRIP001
//STRIP001      pBox = new SwTableBox( pBoxFmt, *pSttNd, pLine );
//STRIP001      pLine->GetTabBoxes().C40_INSERT( SwTableBox, pBox, nBoxes++ );
//STRIP001      if( nMaxBoxes < nBoxes )
//STRIP001          nMaxBoxes = nBoxes;
//STRIP001  }
//STRIP001
//STRIP001  // die Tabelle ausgleichen, leere Sections einfuegen
//STRIP001  for( USHORT n = 0; n < pTable->GetTabLines().Count(); ++n )
//STRIP001  {
//STRIP001      SwTableLine* pLine = pTable->GetTabLines()[ n ];
//STRIP001      if( nMaxBoxes != ( nBoxes = pLine->GetTabBoxes().Count() ))
//STRIP001      {
//STRIP001          InsBoxen( pTblNd, pLine, pBoxFmt, pTxtColl, 0,
//STRIP001                      nBoxes, nMaxBoxes - nBoxes );
//STRIP001
//STRIP001          if( pUndo )
//STRIP001              for( USHORT i = nBoxes; i < nMaxBoxes; ++i )
//STRIP001                  pUndo->AddFillBox( *pLine->GetTabBoxes()[ i ] );
//STRIP001
//STRIP001          // fehlen der 1. Line Boxen, dann kann man das Breiten Array
//STRIP001          // vergessen!
//STRIP001          if( !n )
//STRIP001              aPosArr.Remove( 0, aPosArr.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( aPosArr.Count() )
//STRIP001  {
//STRIP001      SwTableLines& rLns = pTable->GetTabLines();
//STRIP001      USHORT nLastPos = 0;
//STRIP001      for( n = 0; n < aPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          SwTableBoxFmt *pNewFmt = pDoc->MakeTableBoxFmt();
//STRIP001          pNewFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE,
//STRIP001                                              aPosArr[ n ] - nLastPos ));
//STRIP001          for( USHORT nLines = 0; nLines < rLns.Count(); ++nLines )
//STRIP001              //JP 24.06.98: hier muss ein Add erfolgen, da das BoxFormat
//STRIP001              //              von der rufenden Methode noch gebraucht wird!
//STRIP001              pNewFmt->Add( rLns[ nLines ]->GetTabBoxes()[ n ] );
//STRIP001
//STRIP001          nLastPos = aPosArr[ n ];
//STRIP001      }
//STRIP001
//STRIP001      // damit die Tabelle die richtige Groesse bekommt, im BoxFormat die
//STRIP001      // Groesse nach "oben" transportieren.
//STRIP001      ASSERT( !pBoxFmt->GetDepends(), "wer ist in dem Format noch angemeldet" );
//STRIP001      pBoxFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nLastPos ));
//STRIP001  }
//STRIP001  else
//STRIP001      pBoxFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, USHRT_MAX / nMaxBoxes ));
//STRIP001
//STRIP001  // das wars doch wohl ??
//STRIP001  return pTblNd;
//STRIP001 }

//---------------- Tabelle -> Text -----------------------


//STRIP001 BOOL SwDoc::TableToText( const SwTableNode* pTblNd, sal_Unicode cCh )
//STRIP001 {
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  lcl_DelRedlines aDelRedl( *pTblNd, FALSE );
//STRIP001
//STRIP001  SwNodeRange aRg( *pTblNd, 0, *pTblNd->EndOfSectionNode() );
//STRIP001  SwUndoTblToTxt* pUndo = 0;
//STRIP001  SwNodeRange* pUndoRg = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndoRg = new SwNodeRange( aRg.aStart, -1, aRg.aEnd, +1 );
//STRIP001      pUndo = new SwUndoTblToTxt( pTblNd->GetTable(), cCh );
//STRIP001  }
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &pTblNd->GetTable() );
//STRIP001  aMsgHnt.eFlags = TBL_BOXNAME;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  BOOL bRet = GetNodes().TableToText( aRg, cCh, pUndo );
//STRIP001  if( pUndoRg )
//STRIP001  {
//STRIP001      pUndoRg->aStart++;
//STRIP001      pUndoRg->aEnd--;
//STRIP001      pUndo->SetRange( *pUndoRg );
//STRIP001      AppendUndo( pUndo );
//STRIP001      delete pUndoRg;
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001      SetModified();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

// -- benutze die ForEach Methode vom PtrArray um aus einer Tabelle wieder
//      Text zuerzeugen. (Die Boxen koennen auch noch Lines enthalten !!)
//STRIP001 struct _DelTabPara
//STRIP001 {
//STRIP001  SwTxtNode* pLastNd;
//STRIP001  SwNodes& rNds;
//STRIP001  SwUndoTblToTxt* pUndo;
//STRIP001  sal_Unicode cCh;
//STRIP001
//STRIP001  _DelTabPara( SwNodes& rNodes, sal_Unicode cChar, SwUndoTblToTxt* pU ) :
//STRIP001      rNds( rNodes ), pLastNd(0), cCh( cChar ), pUndo( pU ) {}
//STRIP001  _DelTabPara( const _DelTabPara& rPara ) :
//STRIP001      rNds( rPara.rNds ), cCh( rPara.cCh ), pLastNd(rPara.pLastNd),
//STRIP001      pUndo( rPara.pUndo ) {}
//STRIP001 };

// forward deklarieren damit sich die Lines und Boxen rekursiv aufrufen
// koennen.
//STRIP001 BOOL lcl_DelBox( const SwTableBox*&, void *pPara );

//STRIP001 BOOL lcl_DelLine( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  ASSERT( pPara, "die Parameter fehlen" );
//STRIP001  _DelTabPara aPara( *(_DelTabPara*)pPara );
//STRIP001  ((SwTableLine*&)rpLine)->GetTabBoxes().ForEach( &lcl_DelBox, &aPara );
//STRIP001  if( rpLine->GetUpper() )        // gibt es noch eine uebergeordnete Box ??
//STRIP001      // dann gebe den letzten TextNode zurueck
//STRIP001      ((_DelTabPara*)pPara)->pLastNd = aPara.pLastNd;
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL lcl_DelBox( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  ASSERT( pPara, "die Parameter fehlen" );
//STRIP001
//STRIP001  // loesche erstmal die Lines der Box
//STRIP001  _DelTabPara* pDelPara = (_DelTabPara*)pPara;
//STRIP001  if( rpBox->GetTabLines().Count() )
//STRIP001      ((SwTableBox*&)rpBox)->GetTabLines().ForEach( &lcl_DelLine, pDelPara );
//STRIP001  else
//STRIP001  {
//STRIP001      SwDoc* pDoc = pDelPara->rNds.GetDoc();
//STRIP001      SwNodeRange aDelRg( *rpBox->GetSttNd(), 0,
//STRIP001                          *rpBox->GetSttNd()->EndOfSectionNode() );
//STRIP001      // loesche die Section
//STRIP001      pDelPara->rNds.SectionUp( &aDelRg );
//STRIP001      const SwTxtNode* pCurTxtNd;
//STRIP001      if( T2T_PARA != pDelPara->cCh && pDelPara->pLastNd &&
//STRIP001          0 != ( pCurTxtNd = aDelRg.aStart.GetNode().GetTxtNode() ))
//STRIP001      {
//STRIP001          // den Trenner einfuegen
//STRIP001          SwIndex aCntIdx( pDelPara->pLastNd, pDelPara->pLastNd->GetTxt().Len());
//STRIP001          pDelPara->pLastNd->Insert( pDelPara->cCh, aCntIdx );
//STRIP001          // verbinde den akt. TextNode mit dem aus der vorherigen Box
//STRIP001          aDelRg.aStart--;
//STRIP001          ULONG nNdIdx = aDelRg.aStart.GetIndex();
//STRIP001          if( pDelPara->pLastNd == &aDelRg.aStart.GetNode() )
//STRIP001          {
//STRIP001              if( pDelPara->pUndo )
//STRIP001                  pDelPara->pUndo->AddBoxPos( *pDoc, nNdIdx,
//STRIP001                                              aCntIdx.GetIndex() );
//STRIP001
//STRIP001              SvULongs aBkmkArr( 4, 4 );
//STRIP001              xub_StrLen nOldTxtLen = aCntIdx.GetIndex();
//STRIP001              _SaveCntntIdx( pDoc, nNdIdx + 1, pCurTxtNd->GetTxt().Len(),
//STRIP001                              aBkmkArr );
//STRIP001
//STRIP001              pDelPara->pLastNd->JoinNext();
//STRIP001
//STRIP001              if( aBkmkArr.Count() )
//STRIP001                  _RestoreCntntIdx( pDoc, aBkmkArr,
//STRIP001                                      pDelPara->pLastNd->GetIndex(),
//STRIP001                                      nOldTxtLen );
//STRIP001          }
//STRIP001          else if( pDelPara->pUndo )
//STRIP001              pDelPara->pUndo->AddBoxPos( *pDoc, nNdIdx );
//STRIP001      }
//STRIP001      else if( pDelPara->pUndo )
//STRIP001          pDelPara->pUndo->AddBoxPos( *pDoc, aDelRg.aStart.GetIndex() );
//STRIP001      aDelRg.aEnd--;
//STRIP001      pDelPara->pLastNd = aDelRg.aEnd.GetNode().GetTxtNode();
//STRIP001
//STRIP001      //JP 03.04.97: die Ausrichtung der ZahlenFormatierung auf
//STRIP001      //              keinen Fall uebernehmen
//STRIP001      if( pDelPara->pLastNd && pDelPara->pLastNd->GetpSwAttrSet() )
//STRIP001          pDelPara->pLastNd->ResetAttr( RES_PARATR_ADJUST );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL SwNodes::TableToText( const SwNodeRange& rRange, sal_Unicode cCh,
//STRIP001                          SwUndoTblToTxt* pUndo )
//STRIP001 {
//STRIP001  // ist eine Tabelle selektiert ?
//STRIP001  SwTableNode* pTblNd;
//STRIP001  if( rRange.aStart.GetIndex() >= rRange.aEnd.GetIndex() ||
//STRIP001      0 == ( pTblNd = (*this)[ rRange.aStart ]->GetTableNode()) ||
//STRIP001      &rRange.aEnd.GetNode() != pTblNd->EndOfSectionNode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // stand die Tabelle ganz alleine in einer Section ?
//STRIP001  // dann ueber den Upper der Tabelle die Frames anlegen
//STRIP001  SwNode2Layout* pNode2Layout = 0;
//STRIP001  SwNodeIndex aFrmIdx( rRange.aStart );
//STRIP001  SwNode* pFrmNd = FindPrvNxtFrmNode( aFrmIdx, &rRange.aEnd.GetNode() );
//STRIP001  if( !pFrmNd )
//STRIP001      // dann sammel mal alle Uppers ein
//STRIP001      pNode2Layout = new SwNode2Layout( *pTblNd );
//STRIP001
//STRIP001  // loesche schon mal die Frames
//STRIP001  pTblNd->DelFrms();
//STRIP001
//STRIP001  // dann "loeschen" die Tabellen und fasse alle Lines/Boxen zusammen
//STRIP001  _DelTabPara aDelPara( *this, cCh, pUndo );
//STRIP001  pTblNd->pTable->GetTabLines().ForEach( &lcl_DelLine, &aDelPara );
//STRIP001
//STRIP001  // jetzt ist aus jeder TableLine ein TextNode mit dem entsprechenden
//STRIP001  // Trenner erzeugt worden. Es braucht nur noch die Table-Section
//STRIP001  // geloescht und fuer die neuen TextNode die Frames erzeugt werden.
//STRIP001  SwNodeRange aDelRg( rRange.aStart, rRange.aEnd );
//STRIP001
//STRIP001  // JP 14.01.97: hat die Tabelle PageDesc-/Break-Attribute? Dann in den
//STRIP001  //              ersten TextNode uebernehmen
//STRIP001  {
//STRIP001 // was ist mit UNDO???
//STRIP001      const SfxItemSet& rTblSet = pTblNd->pTable->GetFrmFmt()->GetAttrSet();
//STRIP001      const SfxPoolItem *pBreak, *pDesc;
//STRIP001      if( SFX_ITEM_SET != rTblSet.GetItemState( RES_PAGEDESC, FALSE, &pDesc ))
//STRIP001          pDesc = 0;
//STRIP001      if( SFX_ITEM_SET != rTblSet.GetItemState( RES_BREAK, FALSE, &pBreak ))
//STRIP001          pBreak = 0;
//STRIP001
//STRIP001      if( pBreak || pDesc )
//STRIP001      {
//STRIP001          SwNodeIndex aIdx( *pTblNd  );
//STRIP001          SwCntntNode* pCNd = GoNext( &aIdx );
//STRIP001          if( pBreak )
//STRIP001              pCNd->SetAttr( *pBreak );
//STRIP001          if( pDesc )
//STRIP001              pCNd->SetAttr( *pDesc );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SectionUp( &aDelRg );       // loesche die Section und damit die Tabelle
//STRIP001  if( !pFrmNd )
//STRIP001  {
//STRIP001      pNode2Layout->RestoreUpperFrms( *this,
//STRIP001                      aDelRg.aStart.GetIndex(), aDelRg.aEnd.GetIndex() );
//STRIP001      delete pNode2Layout;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwCntntNode *pCNd;
//STRIP001      SwSectionNode *pSNd;
//STRIP001      ULONG nStt = aDelRg.aStart.GetIndex(), nEnd = aDelRg.aEnd.GetIndex();
//STRIP001      while( aDelRg.aStart.GetIndex() < nEnd )
//STRIP001      {
//STRIP001          if( 0 != ( pCNd = aDelRg.aStart.GetNode().GetCntntNode()))
//STRIP001          {
//STRIP001              if( pFrmNd->IsCntntNode() )
//STRIP001                  ((SwCntntNode*)pFrmNd)->MakeFrms( *pCNd );
//STRIP001              else if( pFrmNd->IsTableNode() )
//STRIP001                  ((SwTableNode*)pFrmNd)->MakeFrms( aDelRg.aStart );
//STRIP001              else if( pFrmNd->IsSectionNode() )
//STRIP001                  ((SwSectionNode*)pFrmNd)->MakeFrms( aDelRg.aStart );
//STRIP001              pFrmNd = pCNd;
//STRIP001          }
//STRIP001          else if( 0 != ( pSNd = aDelRg.aStart.GetNode().GetSectionNode()))
//STRIP001          {
//STRIP001              if( !pSNd->GetSection().IsHidden() && !pSNd->IsCntntHidden() )
//STRIP001              {
//STRIP001                  pSNd->MakeFrms( &aFrmIdx, &aDelRg.aEnd );
//STRIP001                  pFrmNd = pSNd;
//STRIP001                  break;
//STRIP001              }
//STRIP001              aDelRg.aStart = *pSNd->EndOfSectionNode();
//STRIP001          }
//STRIP001          aDelRg.aStart++;
//STRIP001      }
//STRIP001
//STRIP001      const SwSpzFrmFmts& rFlyArr = *GetDoc()->GetSpzFrmFmts();
//STRIP001      const SwPosition* pAPos;
//STRIP001      for( USHORT n = 0; n < rFlyArr.Count(); ++n )
//STRIP001      {
//STRIP001          SwFrmFmt* pFmt = (SwFrmFmt*)rFlyArr[n];
//STRIP001          const SwFmtAnchor& rAnchor = pFmt->GetAnchor();
//STRIP001          if( ( FLY_AT_CNTNT == rAnchor.GetAnchorId() ||
//STRIP001                FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ) &&
//STRIP001              0 != ( pAPos = rAnchor.GetCntntAnchor() ) &&
//STRIP001              nStt <= pAPos->nNode.GetIndex() &&
//STRIP001              pAPos->nNode.GetIndex() < nEnd )
//STRIP001              pFmt->MakeFrms();
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


// ----- einfuegen von Spalten/Zeilen ------------------------

//STRIP001 BOOL SwDoc::InsertCol( const SwCursor& rCursor, USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  if( !::CheckSplitCells( rCursor, nCnt + 1, TBLSEARCH_COL ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  ::binfilter::GetTblSel( rCursor, aBoxes, TBLSEARCH_COL );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( aBoxes.Count() )
//STRIP001      bRet = InsertCol( aBoxes, nCnt, bBehind );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::InsertCol( const SwSelBoxes& rBoxes, USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  // uebers SwDoc fuer Undo !!
//STRIP001  ASSERT( rBoxes.Count(), "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTable& rTbl = pTblNd->GetTable();
//STRIP001  if( rTbl.ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  lcl_DelRedlines aDelRedl( *pTblNd, TRUE );
//STRIP001
//STRIP001  SwTableSortBoxes aTmpLst( 0, 5 );
//STRIP001  SwUndoTblNdsChg* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      DoUndo( FALSE );
//STRIP001      pUndo = new SwUndoTblNdsChg( UNDO_TABLE_INSCOL, rBoxes, *pTblNd, nCnt, bBehind );
//STRIP001      aTmpLst.Insert( &rTbl.GetTabSortBoxes(), 0, rTbl.GetTabSortBoxes().Count() );
//STRIP001  }
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &rTbl );
//STRIP001  aMsgHnt.eFlags = TBL_BOXPTR;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  BOOL bRet = rTbl.InsertCol( this, rBoxes, nCnt, bBehind );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      ::ClearFEShellTabCols();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      DoUndo( TRUE );
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          pUndo->SaveNewBoxes( *pTblNd, aTmpLst );
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001          delete pUndo;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::InsertRow( const SwCursor& rCursor, USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( rCursor, aBoxes, TBLSEARCH_ROW );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( aBoxes.Count() )
//STRIP001      bRet = InsertRow( aBoxes, nCnt, bBehind );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::InsertRow( const SwSelBoxes& rBoxes, USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  // uebers SwDoc fuer Undo !!
//STRIP001  ASSERT( rBoxes.Count(), "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTable& rTbl = pTblNd->GetTable();
//STRIP001  if( rTbl.ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  lcl_DelRedlines aDelRedl( *pTblNd, TRUE );
//STRIP001
//STRIP001  SwTableSortBoxes aTmpLst( 0, 5 );
//STRIP001  SwUndoTblNdsChg* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      DoUndo( FALSE );
//STRIP001      pUndo = new SwUndoTblNdsChg( UNDO_TABLE_INSROW,rBoxes, *pTblNd,
//STRIP001                                      nCnt, bBehind );
//STRIP001      aTmpLst.Insert( &rTbl.GetTabSortBoxes(), 0, rTbl.GetTabSortBoxes().Count() );
//STRIP001  }
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &rTbl );
//STRIP001  aMsgHnt.eFlags = TBL_BOXPTR;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  BOOL bRet = rTbl.InsertRow( this, rBoxes, nCnt, bBehind );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      ::ClearFEShellTabCols();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      DoUndo( TRUE );
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          pUndo->SaveNewBoxes( *pTblNd, aTmpLst );
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001          delete pUndo;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001
//STRIP001 }

// ----- loeschen von Spalten/Zeilen ------------------------

//STRIP001 BOOL SwDoc::DeleteRow( const SwCursor& rCursor )
//STRIP001 {
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( rCursor, aBoxes, TBLSEARCH_ROW );
//STRIP001  if( ::binfilter::HasProtectedCells( aBoxes ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // die Crsr aus dem Loeschbereich entfernen.
//STRIP001  // Der Cursor steht danach:
//STRIP001  //  - es folgt noch eine Zeile, in dieser
//STRIP001  //  - vorher steht noch eine Zeile, in dieser
//STRIP001  //  - sonst immer dahinter
//STRIP001  {
//STRIP001      SwTableNode* pTblNd = rCursor.GetNode()->FindTableNode();
//STRIP001
//STRIP001      if( pTblNd->GetTable().ISA( SwDDETable ))
//STRIP001          return FALSE;
//STRIP001
//STRIP001      // suche alle Boxen / Lines
//STRIP001      _FndBox aFndBox( 0, 0 );
//STRIP001      {
//STRIP001          _FndPara aPara( aBoxes, &aFndBox );
//STRIP001          pTblNd->GetTable().GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001      }
//STRIP001
//STRIP001      if( !aFndBox.GetLines().Count() )
//STRIP001          return FALSE;
//STRIP001
//STRIP001      SwEditShell* pESh = GetEditShell();
//STRIP001      if( pESh )
//STRIP001      {
//STRIP001          pESh->KillPams();
//STRIP001          // JP: eigentlich sollte man ueber alle Shells iterieren!!
//STRIP001      }
//STRIP001
//STRIP001      _FndBox* pFndBox = &aFndBox;
//STRIP001      while( 1 == pFndBox->GetLines().Count() &&
//STRIP001              1 == pFndBox->GetLines()[0]->GetBoxes().Count() )
//STRIP001      {
//STRIP001          _FndBox* pTmp = pFndBox->GetLines()[0]->GetBoxes()[0];
//STRIP001          if( pTmp->GetBox()->GetSttNd() )
//STRIP001              break;      // das ist sonst zu weit
//STRIP001          pFndBox = pTmp;
//STRIP001      }
//STRIP001
//STRIP001      SwTableLine* pDelLine = pFndBox->GetLines()[
//STRIP001                      pFndBox->GetLines().Count()-1 ]->GetLine();
//STRIP001      SwTableBox* pDelBox = pDelLine->GetTabBoxes()[
//STRIP001                          pDelLine->GetTabBoxes().Count() - 1 ];
//STRIP001      while( !pDelBox->GetSttNd() )
//STRIP001      {
//STRIP001          SwTableLine* pLn = pDelBox->GetTabLines()[
//STRIP001                      pDelBox->GetTabLines().Count()-1 ];
//STRIP001          pDelBox = pLn->GetTabBoxes()[ pLn->GetTabBoxes().Count() - 1 ];
//STRIP001      }
//STRIP001      SwTableBox* pNextBox = pDelLine->FindNextBox( pTblNd->GetTable(),
//STRIP001                                                      pDelBox, TRUE );
//STRIP001      while( pNextBox &&
//STRIP001              pNextBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001          pNextBox = pNextBox->FindNextBox( pTblNd->GetTable(), pNextBox );
//STRIP001
//STRIP001      if( !pNextBox )         // keine nachfolgende? dann die vorhergehende
//STRIP001      {
//STRIP001          pDelLine = pFndBox->GetLines()[ 0 ]->GetLine();
//STRIP001          pDelBox = pDelLine->GetTabBoxes()[ 0 ];
//STRIP001          while( !pDelBox->GetSttNd() )
//STRIP001              pDelBox = pDelBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001          pNextBox = pDelLine->FindPreviousBox( pTblNd->GetTable(),
//STRIP001                                                      pDelBox, TRUE );
//STRIP001          while( pNextBox &&
//STRIP001                  pNextBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001              pNextBox = pNextBox->FindPreviousBox( pTblNd->GetTable(), pNextBox );
//STRIP001      }
//STRIP001
//STRIP001      ULONG nIdx;
//STRIP001      if( pNextBox )      // dann den Cursor hier hinein
//STRIP001          nIdx = pNextBox->GetSttIdx() + 1;
//STRIP001      else                // ansonsten hinter die Tabelle
//STRIP001          nIdx = pTblNd->EndOfSectionIndex() + 1;
//STRIP001
//STRIP001      SwNodeIndex aIdx( GetNodes(), nIdx );
//STRIP001      SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
//STRIP001      if( !pCNd )
//STRIP001          pCNd = GetNodes().GoNext( &aIdx );
//STRIP001
//STRIP001      if( pCNd )
//STRIP001      {
//STRIP001          // die Cursor von der Shell oder den uebergebenen Cursor aendern?
//STRIP001          SwPaM* pPam = (SwPaM*)&rCursor;
//STRIP001          pPam->GetPoint()->nNode = aIdx;
//STRIP001          pPam->GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001          pPam->SetMark();            // beide wollen etwas davon haben
//STRIP001          pPam->DeleteMark();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // dann loesche doch die Zeilen
//STRIP001  return DeleteRowCol( aBoxes );
//STRIP001 }

//STRIP001 BOOL SwDoc::DeleteCol( const SwCursor& rCursor )
//STRIP001 {
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  GetTblSel( rCursor, aBoxes, TBLSEARCH_COL );
//STRIP001  if( ::binfilter::HasProtectedCells( aBoxes ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // die Crsr muessen noch aus dem Loesch Bereich entfernt
//STRIP001  // werden. Setze sie immer hinter/auf die Tabelle; ueber die
//STRIP001  // Dokument-Position werden sie dann immer an die alte Position gesetzt.
//STRIP001  SwEditShell* pESh = GetEditShell();
//STRIP001  if( pESh )
//STRIP001  {
//STRIP001      const SwNode* pNd = rCursor.GetNode()->FindTableBoxStartNode();
//STRIP001      pESh->ParkCrsr( SwNodeIndex( *pNd ) );
//STRIP001  }
//STRIP001
//STRIP001  // dann loesche doch die Spalten
//STRIP001  return DeleteRowCol( aBoxes );
//STRIP001 }

//STRIP001 BOOL SwDoc::DeleteRowCol( const SwSelBoxes& rBoxes )
//STRIP001 {
//STRIP001  if( ::binfilter::HasProtectedCells( rBoxes ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // uebers SwDoc fuer Undo !!
//STRIP001  ASSERT( rBoxes.Count(), "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pTblNd->GetTable().ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ::ClearFEShellTabCols();
//STRIP001
//STRIP001  lcl_DelRedlines aDelRedl( *pTblNd, TRUE );
//STRIP001
//STRIP001  // soll die gesamte Tabelle geloescht werden ??
//STRIP001  const ULONG nTmpIdx1 = pTblNd->GetIndex();
//STRIP001  const ULONG nTmpIdx2 = rBoxes[ rBoxes.Count()-1 ]->GetSttNd()->
//STRIP001                              EndOfSectionIndex()+1;
//STRIP001  if( pTblNd->GetTable().GetTabSortBoxes().Count() == rBoxes.Count() &&
//STRIP001      rBoxes[0]->GetSttIdx()-1 == nTmpIdx1 &&
//STRIP001      nTmpIdx2 == pTblNd->EndOfSectionIndex() )
//STRIP001  {
//STRIP001      BOOL bNewTxtNd = FALSE;
//STRIP001      // steht diese auch noch alleine in einem FlyFrame ?
//STRIP001      SwNodeIndex aIdx( *pTblNd, -1 );
//STRIP001      const SwStartNode* pSttNd = aIdx.GetNode().GetStartNode();
//STRIP001      if( pSttNd )
//STRIP001      {
//STRIP001          const ULONG nTblEnd = pTblNd->EndOfSectionIndex() + 1;
//STRIP001          const ULONG nSectEnd = pSttNd->EndOfSectionIndex();
//STRIP001          if( nTblEnd == nSectEnd )
//STRIP001          {
//STRIP001              if( SwFlyStartNode == pSttNd->GetStartNodeType() )
//STRIP001              {
//STRIP001                  SwFrmFmt* pFmt = pSttNd->GetFlyFmt();
//STRIP001                  if( pFmt )
//STRIP001                  {
//STRIP001                      // Ok, das ist das gesuchte FlyFormat
//STRIP001                      DelLayoutFmt( pFmt );
//STRIP001                      return TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001              // kein Fly ?? also Kopf- oder Fusszeile: dann immer einen
//STRIP001              // TextNode ueberig lassen.
//STRIP001              // Undo koennen wir dann vergessen !!
//STRIP001              bNewTxtNd = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // kein Fly ?? also Kopf- oder Fusszeile: dann immer einen
//STRIP001      // TextNode ueberig lassen.
//STRIP001      aIdx++;
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          SwPaM aPaM( *pTblNd->EndOfSectionNode(), aIdx.GetNode() );
//STRIP001
//STRIP001          if( bNewTxtNd )
//STRIP001          {
//STRIP001              const SwNodeIndex aTmpIdx( *pTblNd->EndOfSectionNode(), 1 );
//STRIP001              GetNodes().MakeTxtNode( aTmpIdx,
//STRIP001                          GetTxtCollFromPool( RES_POOLCOLL_STANDARD ) );
//STRIP001          }
//STRIP001
//STRIP001             // save the cursors (UNO and otherwise)
//STRIP001             SwPaM aSavePaM( SwNodeIndex( *pTblNd->EndOfSectionNode() ) );
//STRIP001             if( ! aSavePaM.Move( fnMoveForward, fnGoNode ) )
//STRIP001             {
//STRIP001                 *aSavePaM.GetMark() = SwPosition( *pTblNd );
//STRIP001                 aSavePaM.Move( fnMoveBackward, fnGoNode );
//STRIP001             }
//STRIP001             ::PaMCorrAbs( SwNodeIndex( *pTblNd ),
//STRIP001                           SwNodeIndex( *pTblNd->EndOfSectionNode() ),
//STRIP001                           *aSavePaM.GetMark() );
//STRIP001
//STRIP001          // harte SeitenUmbrueche am nachfolgenden Node verschieben
//STRIP001          BOOL bSavePageBreak = FALSE, bSavePageDesc = FALSE;
//STRIP001          ULONG nNextNd = pTblNd->EndOfSectionIndex()+1;
//STRIP001          SwCntntNode* pNextNd = GetNodes()[ nNextNd ]->GetCntntNode();
//STRIP001          if( pNextNd )
//STRIP001          {
//STRIP001 //JP 24.08.98: will man wirklich den PageDesc/Break vom
//STRIP001 //               nachfolgen Absatz ueberbuegeln?
//STRIP001 //               const SwAttrSet& rAttrSet = pNextNd->GetSwAttrSet();
//STRIP001 //               if( SFX_ITEM_SET != rAttrSet.GetItemState( RES_PAGEDESC ) &&
//STRIP001 //                   SFX_ITEM_SET != rAttrSet.GetItemState( RES_BREAK ))
//STRIP001              {
//STRIP001                  SwFrmFmt* pTableFmt = pTblNd->GetTable().GetFrmFmt();
//STRIP001                  const SfxPoolItem *pItem;
//STRIP001                  if( SFX_ITEM_SET == pTableFmt->GetItemState( RES_PAGEDESC,
//STRIP001                      FALSE, &pItem ) )
//STRIP001                  {
//STRIP001                      pNextNd->SetAttr( *pItem );
//STRIP001                      bSavePageDesc = TRUE;
//STRIP001                  }
//STRIP001
//STRIP001                  if( SFX_ITEM_SET == pTableFmt->GetItemState( RES_BREAK,
//STRIP001                      FALSE, &pItem ) )
//STRIP001                  {
//STRIP001                      pNextNd->SetAttr( *pItem );
//STRIP001                      bSavePageBreak = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          SwUndoDelete* pUndo = new SwUndoDelete( aPaM );
//STRIP001          if( bNewTxtNd )
//STRIP001              pUndo->SetTblDelLastNd();
//STRIP001          pUndo->SetPgBrkFlags( bSavePageBreak, bSavePageDesc );
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( bNewTxtNd )
//STRIP001          {
//STRIP001              const SwNodeIndex aTmpIdx( *pTblNd->EndOfSectionNode(), 1 );
//STRIP001              GetNodes().MakeTxtNode( aTmpIdx,
//STRIP001                          GetTxtCollFromPool( RES_POOLCOLL_STANDARD ) );
//STRIP001          }
//STRIP001
//STRIP001             // save the cursors (UNO and otherwise)
//STRIP001             SwPaM aSavePaM( SwNodeIndex( *pTblNd->EndOfSectionNode() ) );
//STRIP001             if( ! aSavePaM.Move( fnMoveForward, fnGoNode ) )
//STRIP001             {
//STRIP001                 *aSavePaM.GetMark() = SwPosition( *pTblNd );
//STRIP001                 aSavePaM.Move( fnMoveBackward, fnGoNode );
//STRIP001             }
//STRIP001             ::PaMCorrAbs( SwNodeIndex( *pTblNd ),
//STRIP001                           SwNodeIndex( *pTblNd->EndOfSectionNode() ),
//STRIP001                           *aSavePaM.GetMark() );
//STRIP001
//STRIP001          // harte SeitenUmbrueche am nachfolgenden Node verschieben
//STRIP001          SwCntntNode* pNextNd = GetNodes()[ pTblNd->EndOfSectionIndex()+1 ]->GetCntntNode();
//STRIP001          if( pNextNd )
//STRIP001          {
//STRIP001              SwFrmFmt* pTableFmt = pTblNd->GetTable().GetFrmFmt();
//STRIP001              const SfxPoolItem *pItem;
//STRIP001              if( SFX_ITEM_SET == pTableFmt->GetItemState( RES_PAGEDESC,
//STRIP001                  FALSE, &pItem ) )
//STRIP001                  pNextNd->SetAttr( *pItem );
//STRIP001
//STRIP001              if( SFX_ITEM_SET == pTableFmt->GetItemState( RES_BREAK,
//STRIP001                  FALSE, &pItem ) )
//STRIP001                  pNextNd->SetAttr( *pItem );
//STRIP001          }
//STRIP001
//STRIP001          pTblNd->DelFrms();
//STRIP001          DeleteSection( pTblNd );
//STRIP001      }
//STRIP001      SetModified();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  SwUndoTblNdsChg* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      DoUndo( FALSE );
//STRIP001      pUndo = new SwUndoTblNdsChg( UNDO_TABLE_DELBOX, rBoxes, *pTblNd, 0, FALSE );
//STRIP001  }
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &pTblNd->GetTable() );
//STRIP001  aMsgHnt.eFlags = TBL_BOXPTR;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  BOOL bRet = pTblNd->GetTable().DeleteSel( this, rBoxes, pUndo, TRUE );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      DoUndo( TRUE );
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001          delete pUndo;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }


// ---------- teilen / zusammenfassen von Boxen in der Tabelle --------

/*N*/ BOOL SwDoc::SplitTbl( const SwSelBoxes& rBoxes, sal_Bool bVert, USHORT nCnt,
/*N*/                       sal_Bool bSameHeight )
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  // uebers SwDoc fuer Undo !!
//STRIP001  ASSERT( rBoxes.Count() && nCnt, "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTable& rTbl = pTblNd->GetTable();
//STRIP001  if( rTbl.ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  lcl_DelRedlines aDelRedl( *pTblNd, TRUE );
//STRIP001
//STRIP001  SvULongs aNdsCnts;
//STRIP001  SwTableSortBoxes aTmpLst( 0, 5 );
//STRIP001  SwUndoTblNdsChg* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      DoUndo( FALSE );
//STRIP001         pUndo = new SwUndoTblNdsChg( UNDO_TABLE_SPLIT, rBoxes, *pTblNd, nCnt,
//STRIP001                                      bVert, bSameHeight );
//STRIP001      aTmpLst.Insert( &rTbl.GetTabSortBoxes(), 0, rTbl.GetTabSortBoxes().Count() );
//STRIP001      if( !bVert )
//STRIP001      {
//STRIP001          for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001          {
//STRIP001              const SwStartNode* pSttNd = rBoxes[ n ]->GetSttNd();
//STRIP001              aNdsCnts.Insert( pSttNd->EndOfSectionIndex() -
//STRIP001                               pSttNd->GetIndex(), n );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &rTbl );
//STRIP001  aMsgHnt.eFlags = TBL_BOXPTR;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  BOOL bRet;
//STRIP001  if( bVert )
//STRIP001      bRet = rTbl.SplitCol( this, rBoxes, nCnt );
//STRIP001  else
//STRIP001         bRet = rTbl.SplitRow( this, rBoxes, nCnt, bSameHeight );
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      DoUndo( TRUE );
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          if( bVert )
//STRIP001              pUndo->SaveNewBoxes( *pTblNd, aTmpLst );
//STRIP001          else
//STRIP001              pUndo->SaveNewBoxes( *pTblNd, aTmpLst, rBoxes, aNdsCnts );
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001          delete pUndo;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
/*N*/ }


//STRIP001 USHORT SwDoc::MergeTbl( SwPaM& rPam )
//STRIP001 {
//STRIP001  // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001  SwTableNode* pTblNd = rPam.GetNode()->FindTableNode();
//STRIP001  if( !pTblNd || pTblNd->GetTable().ISA( SwDDETable ))
//STRIP001      return TBLMERGE_NOSELECTION;
//STRIP001
//STRIP001  USHORT nRet = ::CheckMergeSel( rPam );
//STRIP001  if( TBLMERGE_OK != nRet )
//STRIP001      return nRet;
//STRIP001
//STRIP001  nRet = TBLMERGE_NOSELECTION;
//STRIP001
//STRIP001  StartUndo();
//STRIP001  if( !IsIgnoreRedline() && GetRedlineTbl().Count() )
//STRIP001      DeleteRedline( *pTblNd );
//STRIP001  SwRedlineMode eOld = GetRedlineMode();
//STRIP001  SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001
//STRIP001  SwUndoTblMerge* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001      pUndo = new SwUndoTblMerge( rPam );
//STRIP001
//STRIP001  // lasse ueber das Layout die Boxen suchen
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  SwTableBox* pMergeBox;
//STRIP001  ::GetMergeSel( rPam, aBoxes, &pMergeBox, pUndo );
//STRIP001
//STRIP001  if( 2 > aBoxes.Count() )        // keine gueltigen Boxen gefunden
//STRIP001  {
//STRIP001      SetRedlineMode_intern( eOld );
//STRIP001      if( pUndo )
//STRIP001      {
//STRIP001          delete pUndo;
//STRIP001          if( UNDO_REDLINE == GetUndoIds() )
//STRIP001          {
//STRIP001              SwUndoRedline* pU = (SwUndoRedline*)RemoveLastUndo( UNDO_REDLINE );
//STRIP001              if( pU->GetRedlSaveCount() )
//STRIP001              {
//STRIP001                  SwUndoIter aUndoIter( &rPam, UNDO_REDLINE );
//STRIP001                  pU->Undo( aUndoIter );
//STRIP001              }
//STRIP001              delete pU;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // die PaMs muessen noch aus dem Loesch Bereich entfernt
//STRIP001      // werden. Setze sie immer hinter/auf die Tabelle; ueber die
//STRIP001      // Dokument-Position werden sie dann immer an die alte Position gesetzt.
//STRIP001      // Erstmal einen Index auf die Parkposition merken, denn nach GetMergeSel
//STRIP001      // komme ich nicht mehr dran.
//STRIP001      {
//STRIP001          rPam.DeleteMark();
//STRIP001          rPam.GetPoint()->nNode = *pMergeBox->GetSttNd();
//STRIP001          rPam.GetPoint()->nContent.Assign( 0, 0 );
//STRIP001          rPam.SetMark();
//STRIP001          rPam.DeleteMark();
//STRIP001
//STRIP001          SwPaM* pTmp = &rPam;
//STRIP001          while( &rPam != ( pTmp = (SwPaM*)pTmp->GetNext() ))
//STRIP001              for( int i = 0; i < 2; ++i )
//STRIP001                  pTmp->GetBound( (BOOL)i ) = *rPam.GetPoint();
//STRIP001      }
//STRIP001
//STRIP001      // dann fuege sie zusammen
//STRIP001      SwTableFmlUpdate aMsgHnt( &pTblNd->GetTable() );
//STRIP001      aMsgHnt.eFlags = TBL_BOXPTR;
//STRIP001      UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001      if( pTblNd->GetTable().Merge( this, aBoxes, pMergeBox, pUndo ))
//STRIP001      {
//STRIP001          nRet = TBLMERGE_OK;
//STRIP001          SetModified();
//STRIP001          SetFieldsDirty( TRUE );
//STRIP001          if( pUndo )
//STRIP001              AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else if( pUndo )
//STRIP001          delete pUndo;
//STRIP001
//STRIP001      rPam.GetPoint()->nNode = *pMergeBox->GetSttNd();
//STRIP001      rPam.Move();
//STRIP001
//STRIP001      ::ClearFEShellTabCols();
//STRIP001      SetRedlineMode_intern( eOld );
//STRIP001  }
//STRIP001  EndUndo();
//STRIP001  return nRet;
//STRIP001 }



// -------------------------------------------------------

//---------
// SwTableNode
//---------

/*N*/ SwTableNode::SwTableNode( const SwNodeIndex& rIdx )
/*N*/   : SwStartNode( rIdx, ND_TABLENODE )
/*N*/ {
/*N*/   pTable = new SwTable( 0 );
/*N*/ }

/*M*/ SwTableNode::~SwTableNode()
/*M*/ {
/*M*/   //don't forget to notify uno wrappers
/*M*/   SwFrmFmt* pTblFmt = GetTable().GetFrmFmt();
/*M*/   SwPtrMsgPoolItem aMsgHint( RES_REMOVE_UNO_OBJECT,
/*M*/                               pTblFmt );
/*M*/   pTblFmt->Modify( &aMsgHint, &aMsgHint );
/*M*/   DelFrms();
/*M*/   delete pTable;
/*M*/ }

/*N*/ SwTabFrm *SwTableNode::MakeFrm()
/*N*/ {
/*N*/   return new SwTabFrm( *pTable );
/*N*/ }

//Methode erzeugt fuer den vorhergehenden Node alle Ansichten vom
//Dokument. Die erzeugten Contentframes werden in das entsprechende
//Layout gehaengt.
//STRIP001 void SwTableNode::MakeFrms(const SwNodeIndex & rIdx )
//STRIP001 {
//STRIP001  if( !GetTable().GetFrmFmt()->GetDepends())//gibt es ueberhaupt Frames ??
//STRIP001      return;
//STRIP001
//STRIP001  SwFrm *pFrm, *pNew;
//STRIP001  SwCntntNode * pNode = rIdx.GetNode().GetCntntNode();
//STRIP001
//STRIP001  ASSERT( pNode, "Kein Contentnode oder Copy-Node und neuer Node identisch.");
//STRIP001
//STRIP001  BOOL bBefore = rIdx < GetIndex();
//STRIP001
//STRIP001  SwNode2Layout aNode2Layout( *this, rIdx.GetIndex() );
//STRIP001
//STRIP001  while( 0 != (pFrm = aNode2Layout.NextFrm()) )
//STRIP001  {
//STRIP001      pNew = pNode->MakeFrm();
//STRIP001      // wird ein Node vorher oder nachher mit Frames versehen
//STRIP001      if ( bBefore )
//STRIP001          // der neue liegt vor mir
//STRIP001          pNew->Paste( pFrm->GetUpper(), pFrm );
//STRIP001      else
//STRIP001          // der neue liegt hinter mir
//STRIP001          pNew->Paste( pFrm->GetUpper(), pFrm->GetNext() );
//STRIP001  }
//STRIP001 }

//Fuer jede Shell einen TblFrm anlegen und vor den entsprechenden
//CntntFrm pasten.

/*N*/ void SwTableNode::MakeFrms( SwNodeIndex* pIdxBehind )
/*N*/ {
/*N*/   ASSERT( pIdxBehind, "kein Index" );
/*N*/   *pIdxBehind = *this;
/*N*/   SwNode *pNd = GetNodes().FindPrvNxtFrmNode( *pIdxBehind, EndOfSectionNode() );
/*N*/   if( !pNd )
/*N*/       return ;
/*N*/
/*N*/   // liegt der gefundene ContentNode vor oder hinter der Tabelle ?
/*N*/   BOOL bBehind = EndOfSectionIndex() < pIdxBehind->GetIndex();
/*N*/
/*N*/   SwFrm *pFrm, *pNew;
/*N*/
/*N*/   SwNode2Layout aNode2Layout( *pNd, GetIndex() );
/*N*/   while( 0 != (pFrm = aNode2Layout.NextFrm()) )
/*N*/   {
/*N*/       pNew = MakeFrm();
/*N*/       pNew->Paste( pFrm->GetUpper(),  bBehind ? pFrm : pFrm->GetNext() );
/*N*/       ((SwTabFrm*)pNew)->RegistFlys();
/*N*/   }
/*N*/ }

/*N*/ void SwTableNode::DelFrms()
/*N*/ {
/*N*/   //Erstmal die TabFrms ausschneiden und deleten, die Columns und Rows
/*N*/   //nehmen sie mit in's Grab.
/*N*/   //Die TabFrms haengen am FrmFmt des SwTable.
/*N*/   //Sie muessen etwas umstaendlich zerstort werden, damit die Master
/*N*/   //die Follows mit in's Grab nehmen.
/*N*/
/*N*/   SwClientIter aIter( *(pTable->GetFrmFmt()) );
/*N*/   SwClient *pLast = aIter.GoStart();
/*N*/   while ( pLast )
/*N*/   {
/*N*/       BOOL bAgain = FALSE;
/*N*/       if ( pLast->IsA( TYPE(SwFrm) ) )
/*N*/       {
/*N*/           SwTabFrm *pFrm = (SwTabFrm*)pLast;
/*N*/           if ( !pFrm->IsFollow() )
/*N*/           {
/*N*/               while ( pFrm->HasFollow() )
/*?*/               {DBG_ASSERT(0, "STRIP");} //STRIP001    pFrm->JoinAndDelFollows();
/*N*/               pFrm->Cut();
/*N*/               delete pFrm;
/*N*/               bAgain = TRUE;
/*N*/           }
/*N*/       }
/*N*/       pLast = bAgain ? aIter.GoStart() : aIter++;
/*N*/   }
/*N*/ }


/*N*/ void SwTableNode::SetNewTable( SwTable* pNewTable, BOOL bNewFrames )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   DelFrms();
//STRIP001  delete pTable;
//STRIP001  pTable = pNewTable;
//STRIP001  if( bNewFrames )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *EndOfSectionNode());
//STRIP001      GetNodes().GoNext( &aIdx );
//STRIP001      MakeFrms( &aIdx );
//STRIP001  }
/*N*/ }

    // setze das TabelleAttribut Undo auf:
//STRIP001 void SwDoc::AppendUndoForAttrTable( const SwTable& rTbl )
//STRIP001 {
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoAttrTbl( *rTbl.GetTableNode() ));
//STRIP001  }
//STRIP001 }

//STRIP001 void SwDoc::GetTabCols( SwTabCols &rFill, const SwCursor* pCrsr,
//STRIP001                      const SwCellFrm* pBoxFrm ) const
//STRIP001 {
//STRIP001  const SwTableBox* pBox;
//STRIP001  SwTabFrm *pTab;
//STRIP001
//STRIP001  if( pBoxFrm )
//STRIP001  {
//STRIP001      pTab = ((SwFrm*)pBoxFrm)->ImplFindTabFrm();
//STRIP001      pBox = pBoxFrm->GetTabBox();
//STRIP001  }
//STRIP001  else if( pCrsr )
//STRIP001  {
//STRIP001      const SwCntntNode* pCNd = pCrsr->GetCntntNode();
//STRIP001      if( !pCNd )
//STRIP001          return ;
//STRIP001
//STRIP001      Point aPt;
//STRIP001      const SwShellCrsr *pShCrsr = *pCrsr;
//STRIP001      if( pShCrsr )
//STRIP001          aPt = pShCrsr->GetPtPos();
//STRIP001
//STRIP001      const SwFrm* pTmpFrm = pCNd->GetFrm( &aPt, 0, FALSE );
//STRIP001      do {
//STRIP001          pTmpFrm = pTmpFrm->GetUpper();
//STRIP001      } while ( !pTmpFrm->IsCellFrm() );
//STRIP001
//STRIP001      pBoxFrm = (SwCellFrm*)pTmpFrm;
//STRIP001      pTab = ((SwFrm*)pBoxFrm)->ImplFindTabFrm();
//STRIP001      pBox = pBoxFrm->GetTabBox();
//STRIP001  }
//STRIP001  else if( !pCrsr && !pBoxFrm )
//STRIP001  {
//STRIP001      ASSERT( !this, "einer von beiden muss angegeben werden!" );
//STRIP001      return ;
//STRIP001  }
//STRIP001
//STRIP001  //Fix-Punkte setzen, LeftMin in Dokumentkoordinaten die anderen relativ.
//STRIP001     SWRECTFN( pTab )
//STRIP001     const SwPageFrm* pPage = pTab->FindPageFrm();
//STRIP001     const ULONG nLeftMin = (pTab->Frm().*fnRect->fnGetLeft)() -
//STRIP001                            (pPage->Frm().*fnRect->fnGetLeft)() +
//STRIP001                            DOCUMENTBORDER;
//STRIP001     const ULONG nRightMax = (pTab->Frm().*fnRect->fnGetRight)() -
//STRIP001                             (pPage->Frm().*fnRect->fnGetLeft)() +
//STRIP001                             DOCUMENTBORDER;
//STRIP001
//STRIP001     rFill.SetLeftMin ( nLeftMin );
//STRIP001     rFill.SetLeft    ( (pTab->Prt().*fnRect->fnGetLeft)() );
//STRIP001     rFill.SetRight   ( (pTab->Prt().*fnRect->fnGetRight)());
//STRIP001     rFill.SetRightMax( nRightMax - nLeftMin );
//STRIP001
//STRIP001  pTab->GetTable()->GetTabCols( rFill, pBox );
//STRIP001 }

//STRIP001 void SwDoc::SetTabCols( const SwTabCols &rNew, BOOL bCurRowOnly,
//STRIP001                      const SwCursor* pCrsr, const SwCellFrm* pBoxFrm )
//STRIP001 {
//STRIP001  const SwTableBox* pBox;
//STRIP001  SwTabFrm *pTab;
//STRIP001
//STRIP001  if( pBoxFrm )
//STRIP001  {
//STRIP001      pTab = ((SwFrm*)pBoxFrm)->ImplFindTabFrm();
//STRIP001      pBox = pBoxFrm->GetTabBox();
//STRIP001  }
//STRIP001  else if( pCrsr )
//STRIP001  {
//STRIP001      const SwCntntNode* pCNd = pCrsr->GetCntntNode();
//STRIP001      if( !pCNd )
//STRIP001          return ;
//STRIP001
//STRIP001      Point aPt;
//STRIP001      const SwShellCrsr *pShCrsr = *pCrsr;
//STRIP001      if( pShCrsr )
//STRIP001          aPt = pShCrsr->GetPtPos();
//STRIP001
//STRIP001      const SwFrm* pTmpFrm = pCNd->GetFrm( &aPt, 0, FALSE );
//STRIP001      do {
//STRIP001          pTmpFrm = pTmpFrm->GetUpper();
//STRIP001      } while ( !pTmpFrm->IsCellFrm() );
//STRIP001
//STRIP001      pBoxFrm = (SwCellFrm*)pTmpFrm;
//STRIP001      pTab = ((SwFrm*)pBoxFrm)->ImplFindTabFrm();
//STRIP001      pBox = pBoxFrm->GetTabBox();
//STRIP001  }
//STRIP001  else if( !pCrsr && !pBoxFrm )
//STRIP001  {
//STRIP001      ASSERT( !this, "einer von beiden muss angegeben werden!" );
//STRIP001      return ;
//STRIP001  }
//STRIP001
//STRIP001  // sollte die Tabelle noch auf relativen Werten (USHRT_MAX) stehen
//STRIP001  // dann muss es jetzt auf absolute umgerechnet werden.
//STRIP001  SwTable& rTab = *pTab->GetTable();
//STRIP001  const SwFmtFrmSize& rTblFrmSz = rTab.GetFrmFmt()->GetFrmSize();
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001     SWRECTFN( pTab )
//STRIP001     long nPrtWidth = (pTab->Prt().*fnRect->fnGetWidth)();
//STRIP001 #else
//STRIP001     long nPrtWidth = pTab->Prt().Width();
//STRIP001 #endif
//STRIP001     if( nPrtWidth != rTblFrmSz.GetWidth() )
//STRIP001  {
//STRIP001      SwFmtFrmSize aSz( rTblFrmSz );
//STRIP001         aSz.SetWidth( nPrtWidth );
//STRIP001      rTab.GetFrmFmt()->SetAttr( aSz );
//STRIP001  }
//STRIP001
//STRIP001  SwTabCols aOld( rNew.Count() );
//STRIP001
//STRIP001     const SwPageFrm* pPage = pTab->FindPageFrm();
//STRIP001     const ULONG nLeftMin = (pTab->Frm().*fnRect->fnGetLeft)() -
//STRIP001                            (pPage->Frm().*fnRect->fnGetLeft)() +
//STRIP001                            DOCUMENTBORDER;
//STRIP001     const ULONG nRightMax = (pTab->Frm().*fnRect->fnGetRight)() -
//STRIP001                             (pPage->Frm().*fnRect->fnGetLeft)() +
//STRIP001                             DOCUMENTBORDER;
//STRIP001
//STRIP001     //Fix-Punkte setzen, LeftMin in Dokumentkoordinaten die anderen relativ.
//STRIP001     aOld.SetLeftMin ( nLeftMin );
//STRIP001     aOld.SetLeft    ( (pTab->Prt().*fnRect->fnGetLeft)() );
//STRIP001     aOld.SetRight   ( (pTab->Prt().*fnRect->fnGetRight)());
//STRIP001     aOld.SetRightMax( nRightMax - nLeftMin );
//STRIP001
//STRIP001 /*   if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoAttrTbl(
//STRIP001              *rTab.GetTableNode(),
//STRIP001              TRUE ));
//STRIP001  }
//STRIP001
//STRIP001  rTab.SetTabCols( rNew, aOld, pBox, bCurRowOnly );
//STRIP001
//STRIP001  SetModified();*/
//STRIP001  SetTabCols(rTab, rNew, aOld, pBox, bCurRowOnly );
//STRIP001  ::ClearFEShellTabCols();
//STRIP001 }

/* -----------------18.07.98 11:45-------------------
 *  Direktzugriff fuer UNO
 * --------------------------------------------------*/
//STRIP001 void SwDoc::SetTabCols(SwTable& rTab, const SwTabCols &rNew, SwTabCols &rOld,
//STRIP001                              const SwTableBox *pStart, BOOL bCurRowOnly )
//STRIP001 {
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoAttrTbl( *rTab.GetTableNode(), TRUE ));
//STRIP001  }
//STRIP001  rTab.SetTabCols( rNew, rOld, pStart, bCurRowOnly );
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 void SwDoc::SetHeadlineRepeat( SwTable &rTable, BOOL bSet )
//STRIP001 {
//STRIP001  if( bSet == rTable.IsHeadlineRepeat() )
//STRIP001      return;
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoTblHeadline( rTable, !bSet ) );
//STRIP001  }
//STRIP001
//STRIP001  rTable.SetHeadlineRepeat( bSet );
//STRIP001  SwMsgPoolItem aChg( RES_TBLHEADLINECHG );
//STRIP001  rTable.GetFrmFmt()->Modify( &aChg, &aChg );
//STRIP001  SetModified();
//STRIP001 }



// Splittet eine Tabelle in der Grund-Zeile, in der der Index steht.
// Alle GrundZeilen dahinter wandern in eine neue Tabelle/-Node.
// Ist das Flag bCalcNewSize auf TRUE, wird fuer beide neuen Tabellen
// die neue Size aus dem Max der Boxen errechnet; vorrausgesetzt,
// die Size ist "absolut" gesetzt (USHRT_MAX)

//STRIP001 void SwCollectTblLineBoxes::AddToUndoHistory( const SwCntntNode& rNd )
//STRIP001 {
//STRIP001  if( pHst )
//STRIP001      pHst->Add( rNd.GetFmtColl(), rNd.GetIndex(), ND_TEXTNODE );
//STRIP001 }

//STRIP001 void SwCollectTblLineBoxes::AddBox( const SwTableBox& rBox )
//STRIP001 {
//STRIP001  aPosArr.Insert( nWidth, aPosArr.Count() );
//STRIP001  SwTableBox* p = (SwTableBox*)&rBox;
//STRIP001  aBoxes.Insert( p, aBoxes.Count() );
//STRIP001  nWidth += (USHORT)rBox.GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001 }

//STRIP001 const SwTableBox* SwCollectTblLineBoxes::GetBoxOfPos( const SwTableBox& rBox )
//STRIP001 {
//STRIP001  const SwTableBox* pRet = 0;
//STRIP001  if( aPosArr.Count() )
//STRIP001  {
//STRIP001      for( USHORT n = 0; n < aPosArr.Count(); ++n )
//STRIP001          if( aPosArr[ n ] == nWidth )
//STRIP001              break;
//STRIP001          else if( aPosArr[ n ] > nWidth )
//STRIP001          {
//STRIP001              if( n )
//STRIP001                  --n;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001      if( n >= aPosArr.Count() )
//STRIP001          --n;
//STRIP001
//STRIP001      nWidth += (USHORT)rBox.GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      pRet = aBoxes[ n ];
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 FASTBOOL SwCollectTblLineBoxes::Resize( USHORT nOffset, USHORT nOldWidth )
//STRIP001 {
//STRIP001  if( aPosArr.Count() )
//STRIP001  {
//STRIP001      for( USHORT n = 0; n < aPosArr.Count(); ++n )
//STRIP001          if( aPosArr[ n ] == nOffset )
//STRIP001              break;
//STRIP001          else if( aPosArr[ n ] > nOffset )
//STRIP001          {
//STRIP001              if( n )
//STRIP001                  --n;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001      aPosArr.Remove( 0, n );
//STRIP001      aBoxes.Remove( 0, n );
//STRIP001
//STRIP001      // dann die Positionen der neuen Size anpassen
//STRIP001      for( n = 0; n < aPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          ULONG nSize = nWidth;
//STRIP001          nSize *= ( aPosArr[ n ] - nOffset );
//STRIP001          nSize /= nOldWidth;
//STRIP001          aPosArr[ n ] = USHORT( nSize );
//STRIP001      }
//STRIP001  }
//STRIP001  return 0 != aPosArr.Count();
//STRIP001 }

//STRIP001 BOOL lcl_Line_CollectBox( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  SwCollectTblLineBoxes* pSplPara = (SwCollectTblLineBoxes*)pPara;
//STRIP001  if( pSplPara->IsGetValues() )
//STRIP001      ((SwTableLine*)rpLine)->GetTabBoxes().ForEach( &lcl_Box_CollectBox, pPara );
//STRIP001  else
//STRIP001      ((SwTableLine*)rpLine)->GetTabBoxes().ForEach( &lcl_BoxSetSplitBoxFmts, pPara );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_Box_CollectBox( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  SwCollectTblLineBoxes* pSplPara = (SwCollectTblLineBoxes*)pPara;
//STRIP001  USHORT nLen = rpBox->GetTabLines().Count();
//STRIP001  if( nLen )
//STRIP001  {
//STRIP001      // dann mit der richtigen Line weitermachen
//STRIP001      if( pSplPara->IsGetFromTop() )
//STRIP001          nLen = 0;
//STRIP001      else
//STRIP001          --nLen;
//STRIP001
//STRIP001      const SwTableLine* pLn = rpBox->GetTabLines()[ nLen ];
//STRIP001      lcl_Line_CollectBox( pLn, pPara );
//STRIP001  }
//STRIP001  else
//STRIP001      pSplPara->AddBox( *rpBox );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_BoxSetSplitBoxFmts( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  SwCollectTblLineBoxes* pSplPara = (SwCollectTblLineBoxes*)pPara;
//STRIP001  USHORT nLen = rpBox->GetTabLines().Count();
//STRIP001  if( nLen )
//STRIP001  {
//STRIP001      // dann mit der richtigen Line weitermachen
//STRIP001      if( pSplPara->IsGetFromTop() )
//STRIP001          nLen = 0;
//STRIP001      else
//STRIP001          --nLen;
//STRIP001
//STRIP001      const SwTableLine* pLn = rpBox->GetTabLines()[ nLen ];
//STRIP001      lcl_Line_CollectBox( pLn, pPara );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SwTableBox* pSrcBox = pSplPara->GetBoxOfPos( *rpBox );
//STRIP001      SwFrmFmt* pFmt = pSrcBox->GetFrmFmt();
//STRIP001      SwTableBox* pBox = (SwTableBox*)rpBox;
//STRIP001
//STRIP001      if( HEADLINE_BORDERCOPY == pSplPara->GetMode() )
//STRIP001      {
//STRIP001          const SvxBoxItem& rBoxItem = pBox->GetFrmFmt()->GetBox();
//STRIP001          if( !rBoxItem.GetTop() )
//STRIP001          {
//STRIP001              SvxBoxItem aNew( rBoxItem );
//STRIP001              aNew.SetLine( pFmt->GetBox().GetBottom(), BOX_LINE_TOP );
//STRIP001              if( aNew != rBoxItem )
//STRIP001                  pBox->ClaimFrmFmt()->SetAttr( aNew );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001 USHORT __FAR_DATA aTableSplitBoxSetRange[] = {
//STRIP001  RES_LR_SPACE,       RES_UL_SPACE,
//STRIP001  RES_BACKGROUND,     RES_SHADOW,
//STRIP001  RES_PROTECT,        RES_PROTECT,
//STRIP001  RES_VERT_ORIENT,    RES_VERT_ORIENT,
//STRIP001  0 };
//STRIP001          SfxItemSet aTmpSet( pFmt->GetDoc()->GetAttrPool(),
//STRIP001                              aTableSplitBoxSetRange );
//STRIP001          aTmpSet.Put( pFmt->GetAttrSet() );
//STRIP001          if( aTmpSet.Count() )
//STRIP001              pBox->ClaimFrmFmt()->SetAttr( aTmpSet );
//STRIP001
//STRIP001          if( HEADLINE_BOXATRCOLLCOPY == pSplPara->GetMode() )
//STRIP001          {
//STRIP001              SwNodeIndex aIdx( *pSrcBox->GetSttNd(), 1 );
//STRIP001              SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
//STRIP001              if( !pCNd )
//STRIP001                  pCNd = aIdx.GetNodes().GoNext( &aIdx );
//STRIP001              aIdx = *pBox->GetSttNd();
//STRIP001              SwCntntNode* pDNd = aIdx.GetNodes().GoNext( &aIdx );
//STRIP001
//STRIP001              // nur wenn der Node alleine in der Section steht
//STRIP001              if( 2 == pDNd->EndOfSectionIndex() -
//STRIP001                      pDNd->StartOfSectionIndex() )
//STRIP001              {
//STRIP001                  pSplPara->AddToUndoHistory( *pDNd );
//STRIP001                  pDNd->ChgFmtColl( pCNd->GetFmtColl() );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // bedingte Vorlage beachten
//STRIP001          pBox->GetSttNd()->CheckSectionCondColl();
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL SwDoc::SplitTable( const SwPosition& rPos, USHORT eHdlnMode,
//STRIP001                      BOOL bCalcNewSize )
//STRIP001 {
//STRIP001  SwNode* pNd = &rPos.nNode.GetNode();
//STRIP001  SwTableNode* pTNd = pNd->FindTableNode();
//STRIP001  if( !pTNd || pNd->IsTableNode() )
//STRIP001      return 0;
//STRIP001
//STRIP001  if( pTNd->GetTable().ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTable& rTbl = pTNd->GetTable();
//STRIP001  rTbl.SetHTMLTableLayout( 0 );   // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &rTbl );
//STRIP001
//STRIP001  SwHistory aHistory;
//STRIP001  if( DoesUndo() )
//STRIP001      aMsgHnt.pHistory = &aHistory;
//STRIP001
//STRIP001  {
//STRIP001      ULONG nSttIdx = pNd->FindTableBoxStartNode()->GetIndex();
//STRIP001
//STRIP001      // Suche die Grund-Line dieser Box:
//STRIP001      SwTableBox* pBox = rTbl.GetTblBox( nSttIdx );
//STRIP001      if( pBox )
//STRIP001      {
//STRIP001          SwTableLine* pLine = pBox->GetUpper();
//STRIP001          while( pLine->GetUpper() )
//STRIP001              pLine = pLine->GetUpper()->GetUpper();
//STRIP001
//STRIP001          // in pLine steht jetzt die GrundLine.
//STRIP001          aMsgHnt.nSplitLine = rTbl.GetTabLines().C40_GETPOS( SwTableLine, pLine );
//STRIP001      }
//STRIP001
//STRIP001      String sNewTblNm( GetUniqueTblName() );
//STRIP001      aMsgHnt.DATA.pNewTblNm = &sNewTblNm;
//STRIP001      aMsgHnt.eFlags = TBL_SPLITTBL;
//STRIP001      UpdateTblFlds( &aMsgHnt );
//STRIP001  }
//STRIP001
//STRIP001  //Lines fuer das Layout-Update heraussuchen.
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  aFndBox.SetTableLines( rTbl );
//STRIP001  aFndBox.DelFrms( rTbl );
//STRIP001  aFndBox.SaveChartData( rTbl );
//STRIP001
//STRIP001  SwTableNode* pNew = GetNodes().SplitTable( rPos.nNode, FALSE, bCalcNewSize );
//STRIP001
//STRIP001  if( pNew )
//STRIP001  {
//STRIP001      SwUndoSplitTbl* pUndo = 0;
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( pUndo = new SwUndoSplitTbl( *pNew, eHdlnMode, bCalcNewSize ));
//STRIP001          if( aHistory.Count() )
//STRIP001              pUndo->SaveFormula( aHistory );
//STRIP001      }
//STRIP001
//STRIP001      switch( eHdlnMode )
//STRIP001      {
//STRIP001          // setze die untere Border der vorherige Line,
//STRIP001          // an der aktuellen als obere
//STRIP001      case HEADLINE_BORDERCOPY:
//STRIP001          {
//STRIP001              SwCollectTblLineBoxes aPara( FALSE, eHdlnMode );
//STRIP001              SwTableLine* pLn = rTbl.GetTabLines()[
//STRIP001                          rTbl.GetTabLines().Count() - 1 ];
//STRIP001              pLn->GetTabBoxes().ForEach( &lcl_Box_CollectBox, &aPara );
//STRIP001
//STRIP001              aPara.SetValues( TRUE );
//STRIP001              pLn = pNew->GetTable().GetTabLines()[ 0 ];
//STRIP001              pLn->GetTabBoxes().ForEach( &lcl_BoxSetSplitBoxFmts, &aPara );
//STRIP001
//STRIP001              // Kopfzeile wiederholen abschalten
//STRIP001              pNew->GetTable().SetHeadlineRepeat( FALSE );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          // setze die Attributierung der ersten Line an der neuen ersten
//STRIP001      case HEADLINE_BOXATTRCOPY:
//STRIP001      case HEADLINE_BOXATRCOLLCOPY:
//STRIP001          {
//STRIP001              SwHistory* pHst = 0;
//STRIP001              if( HEADLINE_BOXATRCOLLCOPY == eHdlnMode && pUndo )
//STRIP001                  pHst = pUndo->GetHistory();
//STRIP001
//STRIP001              SwCollectTblLineBoxes aPara( TRUE, eHdlnMode, pHst );
//STRIP001              SwTableLine* pLn = rTbl.GetTabLines()[ 0 ];
//STRIP001              pLn->GetTabBoxes().ForEach( &lcl_Box_CollectBox, &aPara );
//STRIP001
//STRIP001              aPara.SetValues( TRUE );
//STRIP001              pLn = pNew->GetTable().GetTabLines()[ 0 ];
//STRIP001              pLn->GetTabBoxes().ForEach( &lcl_BoxSetSplitBoxFmts, &aPara );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case HEADLINE_CNTNTCOPY:
//STRIP001          rTbl.CopyHeadlineIntoTable( *pNew );
//STRIP001          if( pUndo )
//STRIP001              pUndo->SetTblNodeOffset( pNew->GetIndex() );
//STRIP001          break;
//STRIP001
//STRIP001      case HEADLINE_NONE:
//STRIP001          // Kopfzeile wiederholen abschalten
//STRIP001          pNew->GetTable().SetHeadlineRepeat( FALSE );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // und Frms einfuegen.
//STRIP001      SwNodeIndex aNdIdx( *pNew->EndOfSectionNode() );
//STRIP001      GetNodes().GoNext( &aNdIdx );      // zum naechsten ContentNode
//STRIP001      pNew->MakeFrms( &aNdIdx );
//STRIP001
//STRIP001      //Zwischen die Tabellen wird ein Absatz geschoben
//STRIP001      GetNodes().MakeTxtNode( SwNodeIndex( *pNew ),
//STRIP001                              GetTxtCollFromPool( RES_POOLCOLL_TEXT ) );
//STRIP001  }
//STRIP001
//STRIP001  //Layout updaten
//STRIP001  aFndBox.MakeFrms( rTbl );
//STRIP001  aFndBox.RestoreChartData( rTbl );
//STRIP001  SetFieldsDirty( TRUE );
//STRIP001
//STRIP001  return 0 != pNew;
//STRIP001 }

//STRIP001 BOOL lcl_ChgTblSize( SwTable& rTbl )
//STRIP001 {
//STRIP001  // das Attribut darf nicht ueber das Modify an der
//STRIP001  // Tabelle gesetzt werden, denn sonst werden alle
//STRIP001  // Boxen wieder auf 0 zurueck gesetzt. Also locke das Format
//STRIP001  SwFrmFmt* pFmt = rTbl.GetFrmFmt();
//STRIP001  SwFmtFrmSize aTblMaxSz( pFmt->GetFrmSize() );
//STRIP001
//STRIP001  if( USHRT_MAX == aTblMaxSz.GetWidth() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bLocked = pFmt->IsModifyLocked();
//STRIP001  pFmt->LockModify();
//STRIP001
//STRIP001  aTblMaxSz.SetWidth( 0 );
//STRIP001
//STRIP001  SwTableLines& rLns = rTbl.GetTabLines();
//STRIP001  for( USHORT nLns = 0; nLns < rLns.Count(); ++nLns )
//STRIP001  {
//STRIP001      SwTwips nMaxLnWidth = 0;
//STRIP001      SwTableBoxes& rBoxes = rLns[ nLns ]->GetTabBoxes();
//STRIP001      for( USHORT nBox = 0; nBox < rBoxes.Count(); ++nBox )
//STRIP001          nMaxLnWidth += rBoxes[nBox]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001      if( nMaxLnWidth > aTblMaxSz.GetWidth() )
//STRIP001          aTblMaxSz.SetWidth( nMaxLnWidth );
//STRIP001  }
//STRIP001  pFmt->SetAttr( aTblMaxSz );
//STRIP001  if( !bLocked )          // und gegebenenfalls Lock wieder freigeben
//STRIP001      pFmt->UnlockModify();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 class _SplitTable_Para
//STRIP001 {
//STRIP001  SvPtrarr aSrc, aDest;
//STRIP001  SwTableNode* pNewTblNd;
//STRIP001  SwTable& rOldTbl;
//STRIP001
//STRIP001 public:
//STRIP001  _SplitTable_Para( SwTableNode* pNew, SwTable& rOld )
//STRIP001      : pNewTblNd( pNew ), aSrc( 16, 16 ), aDest( 16, 16 ), rOldTbl( rOld )
//STRIP001  {}
//STRIP001  USHORT SrcFmt_GetPos( void* pFmt ) const
//STRIP001          { return aSrc.GetPos( pFmt ); }
//STRIP001
//STRIP001  void DestFmt_Insert( void* pFmt )
//STRIP001          { aDest.Insert( pFmt, aDest.Count() ); }
//STRIP001
//STRIP001  void SrcFmt_Insert( void* pFmt )
//STRIP001          { aSrc.Insert( pFmt, aSrc.Count() ); }
//STRIP001
//STRIP001  SwFrmFmt* DestFmt_Get( USHORT nPos ) const
//STRIP001          { return (SwFrmFmt*)aDest[ nPos ]; }
//STRIP001
//STRIP001  void ChgBox( SwTableBox* pBox )
//STRIP001  {
//STRIP001      rOldTbl.GetTabSortBoxes().Remove( pBox );
//STRIP001      pNewTblNd->GetTable().GetTabSortBoxes().Insert( pBox );
//STRIP001  }
//STRIP001 };


//STRIP001 BOOL lcl_SplitTable_CpyBox( const SwTableBox*& rpBox, void* pPara );

//STRIP001 BOOL lcl_SplitTable_CpyLine( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  SwTableLine* pLn = (SwTableLine*)rpLine;
//STRIP001  _SplitTable_Para& rPara = *(_SplitTable_Para*)pPara;
//STRIP001
//STRIP001  SwFrmFmt *pSrcFmt = pLn->GetFrmFmt();
//STRIP001  USHORT nPos = rPara.SrcFmt_GetPos( pSrcFmt );
//STRIP001  if( USHRT_MAX == nPos )
//STRIP001  {
//STRIP001      rPara.DestFmt_Insert( pLn->ClaimFrmFmt() );
//STRIP001      rPara.SrcFmt_Insert( pSrcFmt );
//STRIP001  }
//STRIP001  else
//STRIP001      pLn->ChgFrmFmt( (SwTableLineFmt*)rPara.DestFmt_Get( nPos ) );
//STRIP001
//STRIP001  pLn->GetTabBoxes().ForEach( &lcl_SplitTable_CpyBox, pPara );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_SplitTable_CpyBox( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  SwTableBox* pBox = (SwTableBox*)rpBox;
//STRIP001  _SplitTable_Para& rPara = *(_SplitTable_Para*)pPara;
//STRIP001
//STRIP001  SwFrmFmt *pSrcFmt = pBox->GetFrmFmt();
//STRIP001  USHORT nPos = rPara.SrcFmt_GetPos( pSrcFmt );
//STRIP001  if( USHRT_MAX == nPos )
//STRIP001  {
//STRIP001      rPara.DestFmt_Insert( pBox->ClaimFrmFmt() );
//STRIP001      rPara.SrcFmt_Insert( pSrcFmt );
//STRIP001  }
//STRIP001  else
//STRIP001      pBox->ChgFrmFmt( (SwTableBoxFmt*)rPara.DestFmt_Get( nPos ) );
//STRIP001
//STRIP001  if( pBox->GetSttNd() )
//STRIP001      rPara.ChgBox( pBox );
//STRIP001  else
//STRIP001      pBox->GetTabLines().ForEach( &lcl_SplitTable_CpyLine, pPara );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 SwTableNode* SwNodes::SplitTable( const SwNodeIndex& rPos, BOOL bAfter,
//STRIP001                                  BOOL bCalcNewSize )
//STRIP001 {
//STRIP001  SwNode* pNd = &rPos.GetNode();
//STRIP001  SwTableNode* pTNd = pNd->FindTableNode();
//STRIP001  if( !pTNd || pNd->IsTableNode() )
//STRIP001      return 0;
//STRIP001
//STRIP001  ULONG nSttIdx = pNd->FindTableBoxStartNode()->GetIndex();
//STRIP001
//STRIP001  // Suche die Grund-Line dieser Box:
//STRIP001  SwTable& rTbl = pTNd->GetTable();
//STRIP001  SwTableBox* pBox = rTbl.GetTblBox( nSttIdx );
//STRIP001  if( !pBox )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwTableLine* pLine = pBox->GetUpper();
//STRIP001  while( pLine->GetUpper() )
//STRIP001      pLine = pLine->GetUpper()->GetUpper();
//STRIP001
//STRIP001  // in pLine steht jetzt die GrundLine.
//STRIP001  USHORT nLinePos = rTbl.GetTabLines().C40_GETPOS( SwTableLine, pLine );
//STRIP001  if( USHRT_MAX == nLinePos ||
//STRIP001      ( bAfter ? ++nLinePos >= rTbl.GetTabLines().Count() : !nLinePos ))
//STRIP001      return 0;       // nicht gefunden oder letze Line !!
//STRIP001
//STRIP001  // Suche jetzt die 1. Box der nachfolgenden Line
//STRIP001  SwTableLine* pNextLine = rTbl.GetTabLines()[ nLinePos ];
//STRIP001  pBox = pNextLine->GetTabBoxes()[0];
//STRIP001  while( !pBox->GetSttNd() )
//STRIP001      pBox = pBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001
//STRIP001  // dann fuege mal einen End- und TabelleNode ins Nodes-Array ein.
//STRIP001  SwTableNode * pNewTblNd;
//STRIP001  {
//STRIP001      SwEndNode* pOldTblEndNd = (SwEndNode*)pTNd->EndOfSectionNode()->GetEndNode();
//STRIP001      ASSERT( pOldTblEndNd, "wo ist der EndNode?" )
//STRIP001
//STRIP001      SwNodeIndex aIdx( *pBox->GetSttNd() );
//STRIP001      new SwEndNode( aIdx, *pTNd );
//STRIP001      pNewTblNd = new SwTableNode( aIdx );
//STRIP001
//STRIP001      pOldTblEndNd->pStartOfSection = pNewTblNd;
//STRIP001      pNewTblNd->pEndOfSection = pOldTblEndNd;
//STRIP001
//STRIP001      SwNode* pBoxNd = aIdx.GetNode().GetStartNode();
//STRIP001      do {
//STRIP001          ASSERT( pBoxNd->IsStartNode(), "das muss ein StartNode sein!" );
//STRIP001          pBoxNd->pStartOfSection = pNewTblNd;
//STRIP001          pBoxNd = (*this)[ pBoxNd->EndOfSectionIndex() + 1 ];
//STRIP001      } while( pBoxNd != pOldTblEndNd );
//STRIP001  }
//STRIP001
//STRIP001  {
//STRIP001      // die Lines ruebermoven
//STRIP001      SwTable& rNewTbl = pNewTblNd->GetTable();
//STRIP001      rNewTbl.GetTabLines().Insert( &rTbl.GetTabLines(), 0, nLinePos );
//STRIP001      // und loeschen
//STRIP001      rTbl.GetTabLines().Remove( nLinePos,
//STRIP001                                  rTbl.GetTabLines().Count() - nLinePos );
//STRIP001
//STRIP001      // und die betr. Boxen verschieben. Dabei die Formate eindeutig
//STRIP001      // machen und die StartNodes korrigieren
//STRIP001      _SplitTable_Para aPara( pNewTblNd, rTbl );
//STRIP001      rNewTbl.GetTabLines().ForEach( &lcl_SplitTable_CpyLine, &aPara );
//STRIP001  }
//STRIP001
//STRIP001  {
//STRIP001      // Das Tabellen-FrmFormat kopieren
//STRIP001      SwFrmFmt* pOldTblFmt = rTbl.GetFrmFmt();
//STRIP001      SwFrmFmt* pNewTblFmt = pOldTblFmt->GetDoc()->MakeTblFrmFmt(
//STRIP001                              pOldTblFmt->GetDoc()->GetUniqueTblName(),
//STRIP001                              pOldTblFmt->GetDoc()->GetDfltFrmFmt() );
//STRIP001
//STRIP001      *pNewTblFmt = *pOldTblFmt;
//STRIP001      pNewTblFmt->Add( &pNewTblNd->GetTable() );
//STRIP001
//STRIP001      // neue Size errechnen ? (lcl_ChgTblSize nur das 2. aufrufen, wenn es
//STRIP001      // beim 1. schon geklappt hat; also absolute Groesse hat)
//STRIP001      if( bCalcNewSize && lcl_ChgTblSize( rTbl ) )
//STRIP001          lcl_ChgTblSize( pNewTblNd->GetTable() );
//STRIP001  }
//STRIP001
//STRIP001  return pNewTblNd;       // das wars
//STRIP001 }

// und die Umkehrung davon. rPos muss in der Tabelle stehen, die bestehen
// bleibt. Das Flag besagt ob die aktuelle mit der davor oder dahinter
// stehenden vereint wird.
//STRIP001 BOOL SwDoc::MergeTable( const SwPosition& rPos, BOOL bWithPrev, USHORT nMode )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = rPos.nNode.GetNode().FindTableNode(), *pDelTblNd;
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwNodes& rNds = GetNodes();
//STRIP001  if( bWithPrev )
//STRIP001      pDelTblNd = rNds[ pTblNd->GetIndex() - 1 ]->FindTableNode();
//STRIP001  else
//STRIP001      pDelTblNd = rNds[ pTblNd->EndOfSectionIndex() + 1 ]->GetTableNode();
//STRIP001  if( !pDelTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pTblNd->GetTable().ISA( SwDDETable ) ||
//STRIP001      pDelTblNd->GetTable().ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // MIB 9.7.97: HTML-Layout loeschen
//STRIP001  pTblNd->GetTable().SetHTMLTableLayout( 0 );
//STRIP001  pDelTblNd->GetTable().SetHTMLTableLayout( 0 );
//STRIP001
//STRIP001  // beide Tabellen vorhanden, also kanns losgehen
//STRIP001  SwUndoMergeTbl* pUndo = 0;
//STRIP001  SwHistory* pHistory = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( pUndo = new SwUndoMergeTbl( *pTblNd, *pDelTblNd,
//STRIP001                                              bWithPrev, nMode ));
//STRIP001      pHistory = new SwHistory;
//STRIP001  }
//STRIP001
//STRIP001  // alle "Tabellenformeln" anpassen
//STRIP001  SwTableFmlUpdate aMsgHnt( &pTblNd->GetTable() );
//STRIP001  aMsgHnt.DATA.pDelTbl = &pDelTblNd->GetTable();
//STRIP001  aMsgHnt.eFlags = TBL_MERGETBL;
//STRIP001  aMsgHnt.pHistory = pHistory;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  // das eigentliche Mergen
//STRIP001  SwNodeIndex aIdx( bWithPrev ? *pTblNd : *pDelTblNd );
//STRIP001  BOOL bRet = rNds.MergeTable( aIdx, !bWithPrev, nMode, pHistory );
//STRIP001
//STRIP001  if( pHistory )
//STRIP001  {
//STRIP001      if( pHistory->Count() )
//STRIP001          pUndo->SaveFormula( *pHistory );
//STRIP001      delete pHistory;
//STRIP001  }
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwNodes::MergeTable( const SwNodeIndex& rPos, BOOL bWithPrev,
//STRIP001                          USHORT nMode, SwHistory* pHistory )
//STRIP001 {
//STRIP001  SwTableNode* pDelTblNd = rPos.GetNode().GetTableNode();
//STRIP001  ASSERT( pDelTblNd, "wo ist der TableNode geblieben?" );
//STRIP001
//STRIP001  SwTableNode* pTblNd = (*this)[ rPos.GetIndex() - 1]->FindTableNode();
//STRIP001  ASSERT( pTblNd, "wo ist der TableNode geblieben?" );
//STRIP001
//STRIP001  if( !pDelTblNd || !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pDelTblNd->DelFrms();
//STRIP001
//STRIP001  SwTable& rDelTbl = pDelTblNd->GetTable();
//STRIP001  SwTable& rTbl = pTblNd->GetTable();
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  aFndBox.SetTableLines( rTbl );
//STRIP001  aFndBox.DelFrms( rTbl );
//STRIP001  aFndBox.SaveChartData( rTbl );
//STRIP001
//STRIP001  // die Breite der TabellenFormate abgleichen:
//STRIP001  {
//STRIP001      const SwFmtFrmSize& rTblSz = rTbl.GetFrmFmt()->GetFrmSize();
//STRIP001      const SwFmtFrmSize& rDelTblSz = rDelTbl.GetFrmFmt()->GetFrmSize();
//STRIP001      if( rTblSz != rDelTblSz )
//STRIP001      {
//STRIP001          // dann sollten die mal schleunigst korrigiert werden
//STRIP001          if( bWithPrev )
//STRIP001              rDelTbl.GetFrmFmt()->SetAttr( rTblSz );
//STRIP001          else
//STRIP001              rTbl.GetFrmFmt()->SetAttr( rDelTblSz );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bWithPrev )
//STRIP001  {
//STRIP001      // dann mussen alle Attruibute der hinteren Tabelle auf die
//STRIP001      // vordere uebertragen werden, weil die hintere ueber das loeschen
//STRIP001      // des Node geloescht wird.
//STRIP001      rTbl.SetHeadlineRepeat( rDelTbl.IsHeadlineRepeat() );
//STRIP001      rTbl.SetTblChgMode( rDelTbl.GetTblChgMode() );
//STRIP001
//STRIP001      rTbl.GetFrmFmt()->LockModify();
//STRIP001      *rTbl.GetFrmFmt() = *rDelTbl.GetFrmFmt();
//STRIP001      // auch den Namen umsetzen!
//STRIP001      rTbl.GetFrmFmt()->SetName( rDelTbl.GetFrmFmt()->GetName() );
//STRIP001      rTbl.GetFrmFmt()->UnlockModify();
//STRIP001  }
//STRIP001
//STRIP001  // die Lines und Boxen ruebermoven
//STRIP001  USHORT nOldSize = rTbl.GetTabLines().Count();
//STRIP001  rTbl.GetTabLines().Insert( &rDelTbl.GetTabLines(), nOldSize );
//STRIP001  rDelTbl.GetTabLines().Remove( 0, rDelTbl.GetTabLines().Count() );
//STRIP001
//STRIP001  rTbl.GetTabSortBoxes().Insert( &rDelTbl.GetTabSortBoxes() );
//STRIP001  rDelTbl.GetTabSortBoxes().Remove( (USHORT)0, rDelTbl.GetTabSortBoxes().Count() );
//STRIP001
//STRIP001  // die vordere Tabelle bleibt immer stehen, die hintere wird geloescht
//STRIP001  SwEndNode* pTblEndNd = pDelTblNd->EndOfSectionNode();
//STRIP001  pTblNd->pEndOfSection = pTblEndNd;
//STRIP001
//STRIP001  SwNodeIndex aIdx( *pDelTblNd, 1 );
//STRIP001
//STRIP001  SwNode* pBoxNd = aIdx.GetNode().GetStartNode();
//STRIP001  do {
//STRIP001      ASSERT( pBoxNd->IsStartNode(), "das muss ein StartNode sein!" );
//STRIP001      pBoxNd->pStartOfSection = pTblNd;
//STRIP001      pBoxNd = (*this)[ pBoxNd->EndOfSectionIndex() + 1 ];
//STRIP001  } while( pBoxNd != pTblEndNd );
//STRIP001  pBoxNd->pStartOfSection = pTblNd;
//STRIP001
//STRIP001  aIdx -= 2;
//STRIP001  DelNodes( aIdx, 2 );
//STRIP001
//STRIP001  // jetzt an der 1. eingefuegten Line die bedingten Vorlagen umschubsen
//STRIP001  const SwTableLine* pFirstLn = rTbl.GetTabLines()[ nOldSize ];
//STRIP001  if( 1 == nMode )        //
//STRIP001  {
//STRIP001      // Header-Vorlagen in der Zeile setzen
//STRIP001      // und ggfs. in der History speichern fuers Undo!!!
//STRIP001  }
//STRIP001  lcl_LineSetHeadCondColl( pFirstLn, 0 );
//STRIP001
//STRIP001  // und die Borders "aufrauemen"
//STRIP001  if( nOldSize )
//STRIP001  {
//STRIP001      _SwGCLineBorder aPara( rTbl );
//STRIP001      aPara.nLinePos = --nOldSize;
//STRIP001      pFirstLn = rTbl.GetTabLines()[ nOldSize ];
//STRIP001      lcl_GC_Line_Border( pFirstLn, &aPara );
//STRIP001  }
//STRIP001
//STRIP001  //Layout updaten
//STRIP001  aFndBox.MakeFrms( rTbl );
//STRIP001  aFndBox.RestoreChartData( rTbl );
//STRIP001  return TRUE;
//STRIP001 }

// -------------------------------------------------------------------


// -- benutze die ForEach Methode vom PtrArray
//STRIP001 struct _SetAFmtTabPara
//STRIP001 {
//STRIP001  SwTableAutoFmt& rTblFmt;
//STRIP001  SwUndoTblAutoFmt* pUndo;
//STRIP001  USHORT nEndBox, nCurBox;
//STRIP001  BYTE nAFmtLine, nAFmtBox;
//STRIP001
//STRIP001  _SetAFmtTabPara( const SwTableAutoFmt& rNew )
//STRIP001      : rTblFmt( (SwTableAutoFmt&)rNew ),
//STRIP001      nEndBox( 0 ), nCurBox( 0 ), nAFmtLine( 0 ), nAFmtBox( 0 ), pUndo( 0 )
//STRIP001  {}
//STRIP001 };

// forward deklarieren damit sich die Lines und Boxen rekursiv aufrufen
// koennen.
//STRIP001 BOOL lcl_SetAFmtBox( const _FndBox*&, void *pPara );
//STRIP001 BOOL lcl_SetAFmtLine( const _FndLine*&, void *pPara );

//STRIP001 BOOL lcl_SetAFmtLine( const _FndLine*& rpLine, void *pPara )
//STRIP001 {
//STRIP001  ((_FndLine*&)rpLine)->GetBoxes().ForEach( &lcl_SetAFmtBox, pPara );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_SetAFmtBox( const _FndBox*& rpBox, void *pPara )
//STRIP001 {
//STRIP001  _SetAFmtTabPara* pSetPara = (_SetAFmtTabPara*)pPara;
//STRIP001
//STRIP001  if( !rpBox->GetUpper()->GetUpper() )    // Box auf 1. Ebene ?
//STRIP001  {
//STRIP001      if( !pSetPara->nCurBox )
//STRIP001          pSetPara->nAFmtBox = 0;
//STRIP001      else if( pSetPara->nCurBox == pSetPara->nEndBox )
//STRIP001          pSetPara->nAFmtBox = 3;
//STRIP001      else
//STRIP001          pSetPara->nAFmtBox = (BYTE)(1 + ((pSetPara->nCurBox-1) & 1));
//STRIP001  }
//STRIP001
//STRIP001  if( rpBox->GetBox()->GetSttNd() )
//STRIP001  {
//STRIP001      SwTableBox* pSetBox = (SwTableBox*)rpBox->GetBox();
//STRIP001      SwDoc* pDoc = pSetBox->GetFrmFmt()->GetDoc();
//STRIP001      SfxItemSet aCharSet( pDoc->GetAttrPool(), RES_CHRATR_BEGIN, RES_PARATR_END-1 );
//STRIP001      SfxItemSet aBoxSet( pDoc->GetAttrPool(), aTableBoxSetRange );
//STRIP001      BYTE nPos = pSetPara->nAFmtLine * 4 + pSetPara->nAFmtBox;
//STRIP001      pSetPara->rTblFmt.UpdateToSet( nPos, aCharSet,
//STRIP001                                      SwTableAutoFmt::UPDATE_CHAR, 0 );
//STRIP001      pSetPara->rTblFmt.UpdateToSet( nPos, aBoxSet,
//STRIP001                                      SwTableAutoFmt::UPDATE_BOX,
//STRIP001                                      pDoc->GetNumberFormatter( TRUE ) );
//STRIP001      if( aCharSet.Count() )
//STRIP001      {
//STRIP001          ULONG nSttNd = pSetBox->GetSttIdx()+1;
//STRIP001          ULONG nEndNd = pSetBox->GetSttNd()->EndOfSectionIndex();
//STRIP001          for( ; nSttNd < nEndNd; ++nSttNd )
//STRIP001          {
//STRIP001              SwCntntNode* pNd = pDoc->GetNodes()[ nSttNd ]->GetCntntNode();
//STRIP001              if( pNd )
//STRIP001                  pNd->SetAttr( aCharSet );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( aBoxSet.Count() )
//STRIP001      {
//STRIP001          if( pSetPara->pUndo &&
//STRIP001              SFX_ITEM_SET == aBoxSet.GetItemState( RES_BOXATR_FORMAT ))
//STRIP001              pSetPara->pUndo->SaveBoxCntnt( *pSetBox );
//STRIP001
//STRIP001          pSetBox->ClaimFrmFmt()->SetAttr( aBoxSet );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      ((_FndBox*&)rpBox)->GetLines().ForEach( &lcl_SetAFmtLine, pPara );
//STRIP001
//STRIP001  if( !rpBox->GetUpper()->GetUpper() )        // eine BaseLine
//STRIP001      ++pSetPara->nCurBox;
//STRIP001  return TRUE;
//STRIP001 }


        // AutoFormat fuer die Tabelle/TabellenSelection
//STRIP001 BOOL SwDoc::SetTableAutoFmt( const SwSelBoxes& rBoxes, const SwTableAutoFmt& rNew )
//STRIP001 {
//STRIP001  ASSERT( rBoxes.Count(), "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      pTblNd->GetTable().GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pTblNd->GetTable().SetHTMLTableLayout( 0 );
//STRIP001
//STRIP001  _FndBox* pFndBox = &aFndBox;
//STRIP001  while( 1 == pFndBox->GetLines().Count() &&
//STRIP001          1 == pFndBox->GetLines()[0]->GetBoxes().Count() )
//STRIP001      pFndBox = pFndBox->GetLines()[0]->GetBoxes()[0];
//STRIP001
//STRIP001  if( !pFndBox->GetLines().Count() )      // eine zu weit? (nur 1 sel.Box)
//STRIP001      pFndBox = pFndBox->GetUpper()->GetUpper();
//STRIP001
//STRIP001
//STRIP001  // Undo abschalten, Attribute werden sich vorher gemerkt
//STRIP001  SwUndoTblAutoFmt* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( pUndo = new SwUndoTblAutoFmt( *pTblNd, rNew ) );
//STRIP001      DoUndo( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  _SetAFmtTabPara aPara( rNew );
//STRIP001  _FndLines& rFLns = pFndBox->GetLines();
//STRIP001  _FndLine* pLine;
//STRIP001
//STRIP001  for( USHORT n = 0; n < rFLns.Count(); ++n )
//STRIP001  {
//STRIP001      pLine = rFLns[n];
//STRIP001
//STRIP001      // Upper auf 0 setzen (Base-Line simulieren!)
//STRIP001      _FndBox* pSaveBox = pLine->GetUpper();
//STRIP001      pLine->SetUpper( 0 );
//STRIP001
//STRIP001      if( !n )
//STRIP001          aPara.nAFmtLine = 0;
//STRIP001      else if( n+1 == rFLns.Count() )
//STRIP001          aPara.nAFmtLine = 3;
//STRIP001      else
//STRIP001          aPara.nAFmtLine = (BYTE)(1 + ((n-1) & 1 ));
//STRIP001
//STRIP001      aPara.nAFmtBox = 0;
//STRIP001      aPara.nCurBox = 0;
//STRIP001      aPara.nEndBox = pLine->GetBoxes().Count()-1;
//STRIP001      aPara.pUndo = pUndo;
//STRIP001      pLine->GetBoxes().ForEach( &lcl_SetAFmtBox, &aPara );
//STRIP001
//STRIP001      pLine->SetUpper( pSaveBox );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001      DoUndo( TRUE );
//STRIP001
//STRIP001  SetModified();
//STRIP001  SetFieldsDirty( TRUE );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


        // Erfrage wie attributiert ist
//STRIP001 BOOL SwDoc::GetTableAutoFmt( const SwSelBoxes& rBoxes, SwTableAutoFmt& rGet )
//STRIP001 {
//STRIP001  ASSERT( rBoxes.Count(), "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      pTblNd->GetTable().GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  _FndBox* pFndBox = &aFndBox;
//STRIP001  while( 1 == pFndBox->GetLines().Count() &&
//STRIP001          1 == pFndBox->GetLines()[0]->GetBoxes().Count() )
//STRIP001      pFndBox = pFndBox->GetLines()[0]->GetBoxes()[0];
//STRIP001
//STRIP001  if( !pFndBox->GetLines().Count() )      // eine zu weit? (nur 1 sel.Box)
//STRIP001      pFndBox = pFndBox->GetUpper()->GetUpper();
//STRIP001
//STRIP001  _FndLines& rFLns = pFndBox->GetLines();
//STRIP001
//STRIP001  USHORT aLnArr[4];
//STRIP001  aLnArr[0] = 0;
//STRIP001  aLnArr[1] = 1 < rFLns.Count() ? 1 : 0;
//STRIP001  aLnArr[2] = 2 < rFLns.Count() ? 2 : aLnArr[1];
//STRIP001  aLnArr[3] = rFLns.Count() - 1;
//STRIP001
//STRIP001  for( BYTE nLine = 0; nLine < 4; ++nLine )
//STRIP001  {
//STRIP001      _FndLine& rLine = *rFLns[ aLnArr[ nLine ] ];
//STRIP001
//STRIP001      USHORT aBoxArr[4];
//STRIP001      aBoxArr[0] = 0;
//STRIP001      aBoxArr[1] = 1 < rLine.GetBoxes().Count() ? 1 : 0;
//STRIP001      aBoxArr[2] = 2 < rLine.GetBoxes().Count() ? 2 : aBoxArr[1];
//STRIP001      aBoxArr[3] = rLine.GetBoxes().Count() - 1;
//STRIP001
//STRIP001      for( BYTE nBox = 0; nBox < 4; ++nBox )
//STRIP001      {
//STRIP001          SwTableBox* pFBox = rLine.GetBoxes()[ aBoxArr[ nBox ] ]->GetBox();
//STRIP001          // immer auf die 1. runterfallen
//STRIP001          while( !pFBox->GetSttNd() )
//STRIP001              pFBox = pFBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001
//STRIP001          BYTE nPos = nLine * 4 + nBox;
//STRIP001          SwNodeIndex aIdx( *pFBox->GetSttNd(), 1 );
//STRIP001          SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
//STRIP001          if( !pCNd )
//STRIP001              pCNd = GetNodes().GoNext( &aIdx );
//STRIP001
//STRIP001          if( pCNd )
//STRIP001              rGet.UpdateFromSet( nPos, pCNd->GetSwAttrSet(),
//STRIP001                                  SwTableAutoFmt::UPDATE_CHAR, 0 );
//STRIP001          rGet.UpdateFromSet( nPos, pFBox->GetFrmFmt()->GetAttrSet(),
//STRIP001                              SwTableAutoFmt::UPDATE_BOX,
//STRIP001                              GetNumberFormatter( TRUE ) );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ String SwDoc::GetUniqueTblName() const
/*N*/ {
/*N*/   ResId aId( STR_TABLE_DEFNAME, pSwResMgr );
/*N*/   String aName( aId );
/*N*/   xub_StrLen nNmLen = aName.Len();
/*N*/
/*N*/   USHORT nNum, nTmp, nFlagSize = ( pTblFrmFmtTbl->Count() / 8 ) +2;
/*N*/   BYTE* pSetFlags = new BYTE[ nFlagSize ];
/*N*/   memset( pSetFlags, 0, nFlagSize );
/*N*/
        USHORT n=0;
/*N*/   for( n = 0; n < pTblFrmFmtTbl->Count(); ++n )
/*N*/   {
/*N*/       const SwFrmFmt* pFmt = (*pTblFrmFmtTbl)[ n ];
/*N*/       if( !pFmt->IsDefault() && IsUsed( *pFmt )  &&
/*N*/           pFmt->GetName().Match( aName ) == nNmLen )
/*N*/       {
/*N*/           // Nummer bestimmen und das Flag setzen
/*N*/           nNum = pFmt->GetName().Copy( nNmLen ).ToInt32();
/*N*/           if( nNum-- && nNum < pTblFrmFmtTbl->Count() )
/*N*/               pSetFlags[ nNum / 8 ] |= (0x01 << ( nNum & 0x07 ));
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/   nNum = pTblFrmFmtTbl->Count();
/*N*/   for( n = 0; n < nFlagSize; ++n )
/*N*/       if( 0xff != ( nTmp = pSetFlags[ n ] ))
/*N*/       {
/*N*/           // also die Nummer bestimmen
/*N*/           nNum = n * 8;
/*N*/           while( nTmp & 1 )
/*N*/               ++nNum, nTmp >>= 1;
/*N*/           break;
/*N*/       }
/*N*/
/*N*/   __DELETE( nFlagSize ) pSetFlags;
/*N*/   return aName += String::CreateFromInt32( ++nNum );
/*N*/ }

/*N*/ SwTableFmt* SwDoc::FindTblFmtByName( const String& rName, BOOL bAll ) const
/*N*/ {
/*N*/   const SwFmt* pRet = 0;
/*N*/   if( bAll )
/*?*/       pRet = FindFmtByName( (SvPtrarr&)*pTblFrmFmtTbl, rName );
/*N*/   else
/*N*/   {
/*N*/       // dann nur die, die im Doc gesetzt sind
/*N*/       for( USHORT n = 0; n < pTblFrmFmtTbl->Count(); ++n )
/*N*/       {
/*N*/           const SwFrmFmt* pFmt = (*pTblFrmFmtTbl)[ n ];
/*N*/           if( !pFmt->IsDefault() && IsUsed( *pFmt ) &&
/*N*/               pFmt->GetName() == rName )
/*N*/           {
/*?*/               pRet = pFmt;
/*?*/               break;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return (SwTableFmt*)pRet;
/*N*/ }

//STRIP001 BOOL SwDoc::SetColRowWidthHeight( SwTableBox& rAktBox, USHORT eType,
//STRIP001                                  SwTwips nAbsDiff, SwTwips nRelDiff )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rAktBox.GetSttNd()->FindTableNode();
//STRIP001  SwUndo* pUndo = 0;
//STRIP001
//STRIP001  if( WH_FLAG_INSDEL & eType && pTblNd->GetTable().ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTableFmlUpdate aMsgHnt( &pTblNd->GetTable() );
//STRIP001  aMsgHnt.eFlags = TBL_BOXPTR;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  switch( eType & 0xff )
//STRIP001  {
//STRIP001  case WH_COL_LEFT:
//STRIP001  case WH_COL_RIGHT:
//STRIP001  case WH_CELL_LEFT:
//STRIP001  case WH_CELL_RIGHT:
//STRIP001      {
//STRIP001           bRet = pTblNd->GetTable().SetColWidth( rAktBox,
//STRIP001                              eType, nAbsDiff, nRelDiff,
//STRIP001                              DoesUndo() ? &pUndo : 0 );
//STRIP001      }
//STRIP001      break;
//STRIP001  case WH_ROW_TOP:
//STRIP001  case WH_ROW_BOTTOM:
//STRIP001  case WH_CELL_TOP:
//STRIP001  case WH_CELL_BOTTOM:
//STRIP001      bRet = pTblNd->GetTable().SetRowHeight( rAktBox,
//STRIP001                          eType, nAbsDiff, nRelDiff,
//STRIP001                          DoesUndo() ? &pUndo : 0 );
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( pUndo );
//STRIP001      DoUndo( TRUE );     // im SetColWidth kann es abgeschaltet werden!
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      if( WH_FLAG_INSDEL & eType )
//STRIP001          SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 void SwDoc::ChkBoxNumFmt( SwTableBox& rBox, BOOL bCallUpdate )
//STRIP001 {
//STRIP001  //JP 09.07.97: Optimierung: wenn die Box schon sagt, das es Text
//STRIP001  //                          sein soll, dann bleibt das auch Text!
//STRIP001  const SfxPoolItem* pNumFmtItem = 0;
//STRIP001  if( SFX_ITEM_SET == rBox.GetFrmFmt()->GetItemState( RES_BOXATR_FORMAT,
//STRIP001      FALSE, &pNumFmtItem ) && GetNumberFormatter()->IsTextFormat(
//STRIP001          ((SwTblBoxNumFormat*)pNumFmtItem)->GetValue() ))
//STRIP001      return ;
//STRIP001
//STRIP001  SwUndoTblNumFmt* pUndo = 0;
//STRIP001
//STRIP001  BOOL bIsEmptyTxtNd, bChgd = TRUE;
//STRIP001  ULONG nFmtIdx;
//STRIP001  double fNumber;
//STRIP001  if( rBox.HasNumCntnt( fNumber, nFmtIdx, bIsEmptyTxtNd ) )
//STRIP001  {
//STRIP001      if( !rBox.IsNumberChanged() )
//STRIP001          bChgd = FALSE;
//STRIP001      else
//STRIP001      {
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              StartUndo( UNDO_TABLE_AUTOFMT );
//STRIP001              pUndo = new SwUndoTblNumFmt( rBox );
//STRIP001              pUndo->SetNumFmt( nFmtIdx, fNumber );
//STRIP001          }
//STRIP001
//STRIP001          SwTableBoxFmt* pBoxFmt = (SwTableBoxFmt*)rBox.GetFrmFmt();
//STRIP001          SfxItemSet aBoxSet( GetAttrPool(), RES_BOXATR_FORMAT, RES_BOXATR_VALUE );
//STRIP001
//STRIP001          BOOL bSetNumFmt = IsInsTblFormatNum(), bLockModify = TRUE;
//STRIP001          if( bSetNumFmt )
//STRIP001          {
//STRIP001              if( !IsInsTblChangeNumFormat() )
//STRIP001              {
//STRIP001                  if( !pNumFmtItem )
//STRIP001                      bSetNumFmt = FALSE;
//STRIP001                  else
//STRIP001                  {
//STRIP001                      ULONG nOldNumFmt = ((SwTblBoxNumFormat*)pNumFmtItem)->
//STRIP001                                          GetValue();
//STRIP001                      SvNumberFormatter* pNumFmtr = GetNumberFormatter();
//STRIP001
//STRIP001                      short nFmtType = pNumFmtr->GetType( nFmtIdx );
//STRIP001                      if( nFmtType == pNumFmtr->GetType( nOldNumFmt ) ||
//STRIP001                          NUMBERFORMAT_NUMBER == nFmtType )
//STRIP001                          // eingstelltes und vorgegebenes NumFormat
//STRIP001                          // stimmen ueberein -> altes Format beibehalten
//STRIP001                          nFmtIdx = nOldNumFmt;
//STRIP001                      else
//STRIP001                          // eingstelltes und vorgegebenes NumFormat
//STRIP001                          // stimmen nicht ueberein -> als Text einfuegen
//STRIP001                          bLockModify = bSetNumFmt = FALSE;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( bSetNumFmt )
//STRIP001              {
//STRIP001                  pBoxFmt = (SwTableBoxFmt*)rBox.ClaimFrmFmt();
//STRIP001
//STRIP001                  aBoxSet.Put( SwTblBoxValue( fNumber ));
//STRIP001                  aBoxSet.Put( SwTblBoxNumFormat( nFmtIdx ));
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // JP 28.04.98: Nur Formel zuruecksetzen reicht nicht.
//STRIP001          //              Sorge dafuer, das der Text auch entsprechend
//STRIP001          //              formatiert wird!
//STRIP001
//STRIP001          if( !bSetNumFmt && !bIsEmptyTxtNd && pNumFmtItem )
//STRIP001          {
//STRIP001              // JP 15.01.99: Nur Attribute zuruecksetzen reicht nicht.
//STRIP001              //              Sorge dafuer, das der Text auch entsprechend
//STRIP001              //              formatiert wird!
//STRIP001              pBoxFmt->SetAttr( *GetDfltAttr( RES_BOXATR_FORMAT ));
//STRIP001          }
//STRIP001
//STRIP001          if( bLockModify ) pBoxFmt->LockModify();
//STRIP001          pBoxFmt->ResetAttr( RES_BOXATR_FORMAT, RES_BOXATR_VALUE );
//STRIP001          if( bLockModify ) pBoxFmt->UnlockModify();
//STRIP001
//STRIP001          if( bSetNumFmt )
//STRIP001              pBoxFmt->SetAttr( aBoxSet );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // es ist keine Zahl
//STRIP001      const SfxPoolItem* pValueItem = 0, *pFmtItem = 0;
//STRIP001      SwTableBoxFmt* pBoxFmt = (SwTableBoxFmt*)rBox.GetFrmFmt();
//STRIP001      if( SFX_ITEM_SET == pBoxFmt->GetItemState( RES_BOXATR_FORMAT,
//STRIP001              FALSE, &pFmtItem ) ||
//STRIP001          SFX_ITEM_SET == pBoxFmt->GetItemState( RES_BOXATR_VALUE,
//STRIP001              FALSE, &pValueItem ))
//STRIP001      {
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              StartUndo( UNDO_TABLE_AUTOFMT );
//STRIP001              pUndo = new SwUndoTblNumFmt( rBox );
//STRIP001          }
//STRIP001
//STRIP001          pBoxFmt = (SwTableBoxFmt*)rBox.ClaimFrmFmt();
//STRIP001
//STRIP001          // alle Zahlenformate entfernen
//STRIP001          USHORT nWhich1 = RES_BOXATR_FORMULA;
//STRIP001          if( !bIsEmptyTxtNd )
//STRIP001              //JP 15.01.99: dieser Teil wurde doch schon oben abgeprueft!
//STRIP001              /* && pFmtItem && !GetNumberFormatter()->
//STRIP001              IsTextFormat( ((SwTblBoxNumFormat*)pFmtItem)->GetValue() ) )*/
//STRIP001          {
//STRIP001              nWhich1 = RES_BOXATR_FORMAT;
//STRIP001
//STRIP001              // JP 15.01.99: Nur Attribute zuruecksetzen reicht nicht.
//STRIP001              //              Sorge dafuer, das der Text auch entsprechend
//STRIP001              //              formatiert wird!
//STRIP001              pBoxFmt->SetAttr( *GetDfltAttr( nWhich1 ));
//STRIP001          }
//STRIP001          pBoxFmt->ResetAttr( nWhich1, RES_BOXATR_VALUE );
//STRIP001      }
//STRIP001      else
//STRIP001          bChgd = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( bChgd )
//STRIP001  {
//STRIP001      if( pUndo )
//STRIP001      {
//STRIP001          pUndo->SetBox( rBox );
//STRIP001          AppendUndo( pUndo );
//STRIP001          EndUndo( UNDO_END );
//STRIP001      }
//STRIP001
//STRIP001      if( bCallUpdate )
//STRIP001      {
//STRIP001          const SwTableNode* pTblNd = rBox.GetSttNd()->FindTableNode();
//STRIP001          SwTableFmlUpdate aTblUpdate( &pTblNd->GetTable() );
//STRIP001          UpdateTblFlds( &aTblUpdate );
//STRIP001      }
//STRIP001      SetModified();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwDoc::SetTblBoxFormulaAttrs( SwTableBox& rBox, const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoTblNumFmt( rBox, &rSet ) );
//STRIP001  }
//STRIP001
//STRIP001  SwFrmFmt* pBoxFmt = rBox.ClaimFrmFmt();
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_FORMULA ))
//STRIP001  {
//STRIP001      pBoxFmt->LockModify();
//STRIP001      pBoxFmt->ResetAttr( RES_BOXATR_VALUE );
//STRIP001      pBoxFmt->UnlockModify();
//STRIP001  }
//STRIP001  else if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_VALUE ))
//STRIP001  {
//STRIP001      pBoxFmt->LockModify();
//STRIP001      pBoxFmt->ResetAttr( RES_BOXATR_FORMULA );
//STRIP001      pBoxFmt->UnlockModify();
//STRIP001  }
//STRIP001  pBoxFmt->SetAttr( rSet );
//STRIP001  SetModified();
//STRIP001 }

/*N*/ void SwDoc::ClearBoxNumAttrs( const SwNodeIndex& rNode )
/*N*/ {
/*N*/   SwStartNode* pSttNd;
/*N*/   if( 0 != ( pSttNd = GetNodes()[ rNode ]->
/*N*/                               FindSttNodeByType( SwTableBoxStartNode )) &&
/*N*/       2 == pSttNd->EndOfSectionIndex() - pSttNd->GetIndex() )
/*N*/   {
/*N*/       SwTableBox* pBox = pSttNd->FindTableNode()->GetTable().
/*N*/                           GetTblBox( pSttNd->GetIndex() );
/*N*/
/*N*/       const SfxPoolItem* pFmtItem = 0;
/*N*/       const SfxItemSet& rSet = pBox->GetFrmFmt()->GetAttrSet();
/*N*/       if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_FORMAT, FALSE, &pFmtItem ) ||
/*N*/           SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_FORMULA, FALSE ) ||
/*N*/           SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_VALUE, FALSE ))
/*N*/       {
/*?*/           if( DoesUndo() )
/*?*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 ClearRedo();
//STRIP001 /*?*/                AppendUndo( new SwUndoTblNumFmt( *pBox ) );
/*?*/           }
/*?*/
/*?*/           SwFrmFmt* pBoxFmt = pBox->ClaimFrmFmt();
/*?*/
/*?*/           //JP 01.09.97: TextFormate bleiben erhalten!
/*?*/           USHORT nWhich1 = RES_BOXATR_FORMAT;
/*?*/           if( pFmtItem && GetNumberFormatter()->IsTextFormat(
/*?*/                   ((SwTblBoxNumFormat*)pFmtItem)->GetValue() ))
/*?*/               nWhich1 = RES_BOXATR_FORMULA;
/*?*/           else
/*?*/               // JP 15.01.99: Nur Attribute zuruecksetzen reicht nicht.
/*?*/               //              Sorge dafuer, das der Text auch entsprechend
/*?*/               //              formatiert wird!
/*?*/               pBoxFmt->SetAttr( *GetDfltAttr( RES_BOXATR_FORMAT ));
/*?*/
/*?*/           pBoxFmt->ResetAttr( nWhich1, RES_BOXATR_VALUE );
/*?*/           SetModified();
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 BOOL SwDoc::CopyTblInTbl( const SwTable& rSrcTable, SwTable& rDestTable,
//STRIP001                          const SwNodeIndex& rBoxIdx )
//STRIP001 {
//STRIP001  SwUndoTblCpyTbl* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndo = new SwUndoTblCpyTbl;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet;
//STRIP001  if( rSrcTable.IsTblComplex() )
//STRIP001      bRet = rDestTable.InsTable( rSrcTable, rBoxIdx, pUndo );
//STRIP001  else
//STRIP001  {
//STRIP001      SwSelBoxes aBoxes;
//STRIP001      SwTableBox* pBox = rDestTable.GetTblBox( rBoxIdx.GetIndex() );
//STRIP001      aBoxes.Insert( pBox );
//STRIP001
//STRIP001      bRet = rDestTable.InsTable( rSrcTable, aBoxes, pUndo );
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      if( pUndo )
//STRIP001          AppendUndo( pUndo );
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001  else if( pUndo )
//STRIP001      delete pUndo;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }


// kopiert eine Tabelle aus dem selben oder einem anderen Doc in sich
// selbst. Dabei wird eine neue Tabelle angelegt oder eine bestehende
// mit dem Inhalt gefuellt; wobei entweder der Inhalt ab einer Box oder
// in eine bestehende TblSelektion gefuellt wird.
// Gerufen wird es von: edglss.cxx/fecopy.cxx

//STRIP001 BOOL SwDoc::InsCopyOfTbl( SwPosition& rInsPos, const SwSelBoxes& rBoxes,
//STRIP001                      const SwTable* pCpyTbl, BOOL bCpyName, BOOL bCorrPos )
//STRIP001 {
//STRIP001  BOOL bRet;
//STRIP001
//STRIP001  const SwTableNode* pSrcTblNd = pCpyTbl
//STRIP001          ? pCpyTbl->GetTableNode()
//STRIP001          : rBoxes[ 0 ]->GetSttNd()->FindTableNode();
//STRIP001
//STRIP001  SwTableNode* pInsTblNd = GetNodes()[ rInsPos.nNode ]->FindTableNode();
//STRIP001
//STRIP001  if( !pCpyTbl && !pInsTblNd )
//STRIP001  {
//STRIP001      SwUndoCpyTbl* pUndo = 0;
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          pUndo = new SwUndoCpyTbl;
//STRIP001          DoUndo( FALSE );
//STRIP001      }
//STRIP001
//STRIP001      bRet = pSrcTblNd->GetTable().MakeCopy( this, rInsPos, rBoxes,
//STRIP001                                              TRUE, bCpyName );
//STRIP001      if( pUndo )
//STRIP001      {
//STRIP001          if( !bRet )
//STRIP001              delete pUndo;
//STRIP001          else
//STRIP001          {
//STRIP001              pInsTblNd = GetNodes()[ rInsPos.nNode.GetIndex() - 1 ]->FindTableNode();
//STRIP001
//STRIP001              pUndo->SetTableSttIdx( pInsTblNd->GetIndex() );
//STRIP001              AppendUndo( pUndo );
//STRIP001          }
//STRIP001          DoUndo( TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwUndoTblCpyTbl* pUndo = 0;
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          pUndo = new SwUndoTblCpyTbl;
//STRIP001          DoUndo( FALSE );
//STRIP001      }
//STRIP001
//STRIP001      SwDoc* pCpyDoc = (SwDoc*)pSrcTblNd->GetDoc();
//STRIP001      SvEmbeddedObjectRef* pRefForDocSh;
//STRIP001      BOOL bDelCpyDoc = pCpyDoc == this;
//STRIP001
//STRIP001      if( bDelCpyDoc )
//STRIP001      {
//STRIP001          // kopiere die Tabelle erstmal in ein temp. Doc
//STRIP001          pCpyDoc = new SwDoc;
//STRIP001             pCpyDoc->AddLink();
//STRIP001             pRefForDocSh = new SvEmbeddedObjectRef();
//STRIP001             pCpyDoc->SetRefForDocShell( pRefForDocSh );
//STRIP001
//STRIP001          SwPosition aPos( SwNodeIndex( pCpyDoc->GetNodes().GetEndOfContent() ));
//STRIP001          if( !pSrcTblNd->GetTable().MakeCopy( pCpyDoc, aPos, rBoxes, TRUE, TRUE ))
//STRIP001          {
//STRIP001                 delete pRefForDocSh;
//STRIP001                 if( pCpyDoc->RemoveLink() == 0 )
//STRIP001                     delete pCpyDoc;
//STRIP001
//STRIP001              if( pUndo )
//STRIP001              {
//STRIP001                  DoUndo( TRUE );
//STRIP001                  delete pUndo;
//STRIP001              }
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001          aPos.nNode -= 1;        // auf den EndNode der Tabelle
//STRIP001          pSrcTblNd = aPos.nNode.GetNode().FindTableNode();
//STRIP001
//STRIP001             pCpyDoc->SetRefForDocShell( NULL );
//STRIP001      }
//STRIP001
//STRIP001      const SwStartNode* pSttNd = rInsPos.nNode.GetNode().FindTableBoxStartNode();
//STRIP001
//STRIP001      rInsPos.nContent.Assign( 0, 0 );
//STRIP001
//STRIP001      // keine complexe Tabelle ??
//STRIP001      if( !pSrcTblNd->GetTable().IsTblComplex() &&
//STRIP001          (bDelCpyDoc || rBoxes.Count() ))
//STRIP001      {
//STRIP001          // dann die Tabelle "relativ" kopieren
//STRIP001          const SwSelBoxes* pBoxes;
//STRIP001          SwSelBoxes aBoxes;
//STRIP001
//STRIP001          if( bDelCpyDoc )
//STRIP001          {
//STRIP001              SwTableBox* pBox = pInsTblNd->GetTable().GetTblBox(
//STRIP001                                      pSttNd->GetIndex() );
//STRIP001              ASSERT( pBox, "Box steht nicht in dieser Tabelle" );
//STRIP001              aBoxes.Insert( pBox );
//STRIP001              pBoxes = &aBoxes;
//STRIP001          }
//STRIP001          else
//STRIP001              pBoxes = &rBoxes;
//STRIP001
//STRIP001          // kopiere die Tabelle in die selktierten Zellen.
//STRIP001          bRet = pInsTblNd->GetTable().InsTable( pSrcTblNd->GetTable(),
//STRIP001                                                      *pBoxes, pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwNodeIndex aNdIdx( *pSttNd, 1 );
//STRIP001          bRet = pInsTblNd->GetTable().InsTable( pSrcTblNd->GetTable(),
//STRIP001                                                  aNdIdx, pUndo );
//STRIP001      }
//STRIP001
//STRIP001      if( bDelCpyDoc )
//STRIP001         {
//STRIP001             delete pRefForDocSh;
//STRIP001             if( pCpyDoc->RemoveLink() == 0 )
//STRIP001                 delete pCpyDoc;
//STRIP001         }
//STRIP001
//STRIP001      if( pUndo )
//STRIP001      {
//STRIP001          // falls die Tabelle nicht kopiert werden konnte, das Undo-Object
//STRIP001          // wieder loeschen
//STRIP001          if( !bRet && pUndo->IsEmpty() )
//STRIP001              delete pUndo;
//STRIP001          else
//STRIP001              AppendUndo( pUndo );
//STRIP001          DoUndo( TRUE );
//STRIP001      }
//STRIP001
//STRIP001      if( bCorrPos )
//STRIP001      {
//STRIP001          rInsPos.nNode = *pSttNd;
//STRIP001          rInsPos.nContent.Assign( GetNodes().GoNext( &rInsPos.nNode ), 0 );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SetModified();
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }



//STRIP001 BOOL SwDoc::_UnProtectTblCells( SwTable& rTbl )
//STRIP001 {
//STRIP001  BOOL bChgd = FALSE;
//STRIP001  SwUndoAttrTbl* pUndo = DoesUndo() ? new SwUndoAttrTbl( *rTbl.GetTableNode() )
//STRIP001                                    : 0;
//STRIP001
//STRIP001  SwTableSortBoxes& rSrtBox = rTbl.GetTabSortBoxes();
//STRIP001  for( USHORT i = rSrtBox.Count(); i; )
//STRIP001  {
//STRIP001      SwFrmFmt *pBoxFmt = rSrtBox[ --i ]->GetFrmFmt();
//STRIP001      if( pBoxFmt->GetProtect().IsCntntProtected() )
//STRIP001      {
//STRIP001          pBoxFmt->ResetAttr( RES_PROTECT );
//STRIP001          bChgd = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      if( bChgd )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001          delete pUndo;
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }


//STRIP001 BOOL SwDoc::UnProtectCells( const String& rName )
//STRIP001 {
//STRIP001  BOOL bChgd = FALSE;
//STRIP001  SwTableFmt* pFmt = FindTblFmtByName( rName );
//STRIP001  if( pFmt )
//STRIP001  {
//STRIP001      bChgd = _UnProtectTblCells( *SwTable::FindTable( pFmt ) );
//STRIP001      if( bChgd )
//STRIP001          SetModified();
//STRIP001  }
//STRIP001
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 BOOL SwDoc::UnProtectCells( const SwSelBoxes& rBoxes )
//STRIP001 {
//STRIP001  BOOL bChgd = FALSE;
//STRIP001  if( rBoxes.Count() )
//STRIP001  {
//STRIP001      SwUndoAttrTbl* pUndo = DoesUndo()
//STRIP001              ? new SwUndoAttrTbl( *rBoxes[0]->GetSttNd()->FindTableNode() )
//STRIP001              : 0;
//STRIP001
//STRIP001      SvPtrarr aFmts( 16 ), aNewFmts( 16 );
//STRIP001      for( USHORT i = rBoxes.Count(); i; )
//STRIP001      {
//STRIP001          SwTableBox* pBox = rBoxes[ --i ];
//STRIP001          SwFrmFmt* pBoxFmt = pBox->GetFrmFmt();
//STRIP001          if( pBoxFmt->GetProtect().IsCntntProtected() )
//STRIP001          {
//STRIP001              USHORT nFnd = aFmts.GetPos( pBoxFmt );
//STRIP001              if( USHRT_MAX != nFnd )
//STRIP001                  pBox->ChgFrmFmt( (SwTableBoxFmt*)aNewFmts[ nFnd ] );
//STRIP001              else
//STRIP001              {
//STRIP001                  aFmts.Insert( pBoxFmt, aFmts.Count() );
//STRIP001                  pBoxFmt = pBox->ClaimFrmFmt();
//STRIP001                  pBoxFmt->ResetAttr( RES_PROTECT );
//STRIP001                  aNewFmts.Insert( pBoxFmt, aNewFmts.Count() );
//STRIP001              }
//STRIP001              bChgd = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( pUndo )
//STRIP001      {
//STRIP001          if( bChgd )
//STRIP001          {
//STRIP001              ClearRedo();
//STRIP001              AppendUndo( pUndo );
//STRIP001          }
//STRIP001          else
//STRIP001              delete pUndo;
//STRIP001      }
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 BOOL SwDoc::UnProtectTbls( const SwPaM& rPam )
//STRIP001 {
//STRIP001  StartUndo();
//STRIP001
//STRIP001  BOOL bChgd = FALSE, bHasSel = rPam.HasMark() ||
//STRIP001                                  rPam.GetNext() != (SwPaM*)&rPam;
//STRIP001  SwFrmFmts& rFmts = *GetTblFrmFmts();
//STRIP001  SwTable* pTbl;
//STRIP001  const SwTableNode* pTblNd;
//STRIP001  for( USHORT n = rFmts.Count(); n ; )
//STRIP001      if( 0 != (pTbl = SwTable::FindTable( rFmts[ --n ] )) &&
//STRIP001          0 != (pTblNd = pTbl->GetTableNode() ) &&
//STRIP001          pTblNd->GetNodes().IsDocNodes() )
//STRIP001      {
//STRIP001          ULONG nTblIdx = pTblNd->GetIndex();
//STRIP001
//STRIP001          // dann ueberpruefe ob Tabelle in der Selection liegt
//STRIP001          if( bHasSel )
//STRIP001          {
//STRIP001              int bFound = FALSE;
//STRIP001              SwPaM* pTmp = (SwPaM*)&rPam;
//STRIP001              do {
//STRIP001                  const SwPosition *pStt = pTmp->Start(),
//STRIP001                                  *pEnd = pTmp->End();
//STRIP001                  bFound = pStt->nNode.GetIndex() < nTblIdx &&
//STRIP001                          nTblIdx < pEnd->nNode.GetIndex();
//STRIP001
//STRIP001              } while( !bFound && &rPam != ( pTmp = (SwPaM*)pTmp->GetNext() ) );
//STRIP001              if( !bFound )
//STRIP001                  continue;       // weitersuchen
//STRIP001          }
//STRIP001
//STRIP001          // dann mal den Schutz aufheben
//STRIP001          bChgd |= _UnProtectTblCells( *pTbl );
//STRIP001      }
//STRIP001
//STRIP001  EndUndo();
//STRIP001  if( bChgd )
//STRIP001      SetModified();
//STRIP001
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 BOOL SwDoc::HasTblAnyProtection( const SwPosition* pPos,
//STRIP001                               const String* pTblName,
//STRIP001                               BOOL* pFullTblProtection )
//STRIP001 {
//STRIP001  BOOL bHasProtection = FALSE;
//STRIP001  SwTable* pTbl = 0;
//STRIP001  if( pTblName )
//STRIP001      pTbl = SwTable::FindTable( FindTblFmtByName( *pTblName ) );
//STRIP001  else if( pPos )
//STRIP001  {
//STRIP001      SwTableNode* pTblNd = pPos->nNode.GetNode().FindTableNode();
//STRIP001      if( pTblNd )
//STRIP001          pTbl = &pTblNd->GetTable();
//STRIP001  }
//STRIP001
//STRIP001  if( pTbl )
//STRIP001  {
//STRIP001      SwTableSortBoxes& rSrtBox = pTbl->GetTabSortBoxes();
//STRIP001      for( USHORT i = rSrtBox.Count(); i; )
//STRIP001      {
//STRIP001          SwFrmFmt *pBoxFmt = rSrtBox[ --i ]->GetFrmFmt();
//STRIP001          if( pBoxFmt->GetProtect().IsCntntProtected() )
//STRIP001          {
//STRIP001              if( !bHasProtection )
//STRIP001              {
//STRIP001                  bHasProtection = TRUE;
//STRIP001                  if( !pFullTblProtection )
//STRIP001                      break;
//STRIP001                  *pFullTblProtection = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          else if( bHasProtection && pFullTblProtection )
//STRIP001          {
//STRIP001              *pFullTblProtection = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bHasProtection;
//STRIP001 }

//STRIP001 BOOL SwDoc::GCTableBorder( const SwPosition& rPos )
//STRIP001 {
//STRIP001  SwNode* pNd = &rPos.nNode.GetNode();
//STRIP001  SwTableNode* pTNd = pNd->FindTableNode();
//STRIP001  if( !pTNd || pNd->IsTableNode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( pTNd->GetTable().ISA( SwDDETable ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTable& rTbl = pTNd->GetTable();
//STRIP001  rTbl.SetHTMLTableLayout( 0 );   // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoAttrTbl( *pTNd ));
//STRIP001  }
//STRIP001
//STRIP001  rTbl.GCBorderLines();
//STRIP001  SetModified();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 lcl_DelRedlines::lcl_DelRedlines( const SwTableNode& rNd,
//STRIP001                                  BOOL bCheckForOwnRedline )
//STRIP001  : pDoc( (SwDoc*)rNd.GetNodes().GetDoc() )
//STRIP001 {
//STRIP001  pDoc->StartUndo();
//STRIP001  const SwRedlineTbl& rTbl = pDoc->GetRedlineTbl();
//STRIP001  if( !pDoc->IsIgnoreRedline() && rTbl.Count() )
//STRIP001  {
//STRIP001      BOOL bDelete = TRUE;
//STRIP001      if( bCheckForOwnRedline )
//STRIP001      {
//STRIP001          sal_uInt16 nRedlPos = pDoc->GetRedlinePos( rNd );
//STRIP001          sal_uInt32 nSttNd = rNd.GetIndex(),
//STRIP001                     nEndNd = rNd.EndOfSectionIndex();
//STRIP001
//STRIP001          for ( ; nRedlPos < rTbl.Count(); ++nRedlPos )
//STRIP001          {
//STRIP001              const SwRedline* pRedline = rTbl[ nRedlPos ];
//STRIP001              const SwPosition* pStt = pRedline->Start(),
//STRIP001                              * pEnd = pStt == pRedline->GetPoint()
//STRIP001                                                  ? pRedline->GetMark()
//STRIP001                                                  : pRedline->GetPoint();
//STRIP001              if( pStt->nNode <= nSttNd )
//STRIP001              {
//STRIP001                  if( pEnd->nNode >= nEndNd &&
//STRIP001                      pRedline->GetAuthor() == pDoc->GetRedlineAuthor() )
//STRIP001                  {
//STRIP001                      bDelete = FALSE;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001      if( bDelete )
//STRIP001      {
//STRIP001          SwPaM aPam(*rNd.EndOfSectionNode(), rNd);
//STRIP001          pDoc->AcceptRedline( aPam );
//STRIP001      }
//STRIP001   }
//STRIP001 }


}
