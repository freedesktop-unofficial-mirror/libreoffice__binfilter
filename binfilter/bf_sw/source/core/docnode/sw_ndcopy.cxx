/*************************************************************************
 *
 *  $RCSfile: sw_ndcopy.cxx,v $
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

#define _ZFORLIST_DECLARE_TABLE
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif


#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif

#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
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
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _FMTCNCT_HXX
#include <fmtcnct.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
namespace binfilter {

// Struktur fuer das Mappen von alten und neuen Frame-Formaten an den
// Boxen und Lines einer Tabelle

/*N*/ struct _MapTblFrmFmt
/*N*/ {
/*N*/   const SwFrmFmt *pOld, *pNew;
/*N*/   _MapTblFrmFmt( const SwFrmFmt *pOldFmt, const SwFrmFmt*pNewFmt )
/*N*/       : pOld( pOldFmt ), pNew( pNewFmt )
/*N*/   {}
/*N*/ };

/*N*/ SV_DECL_VARARR( _MapTblFrmFmts, _MapTblFrmFmt, 0, 10 )//STRIP008 ;
/*N*/ SV_IMPL_VARARR( _MapTblFrmFmts, _MapTblFrmFmt );

/*N*/ SwCntntNode* SwTxtNode::MakeCopy( SwDoc* pDoc, const SwNodeIndex& rIdx ) const
/*N*/ {
/*N*/   // the Copy-Textnode is the Node with the Text, the Copy-Attrnode is the
/*N*/   // node with the collection and hard attributes. Normally ist the same
/*N*/   // node, but if insert a glossary without formatting, then the Attrnode
/*N*/   // is the prev node of the destionation position in dest. document.
/*N*/   SwTxtNode* pCpyTxtNd = (SwTxtNode*)this;
/*N*/   SwTxtNode* pCpyAttrNd = pCpyTxtNd;
/*N*/
/*N*/   // kopiere die Formate in das andere Dokument:
/*N*/   SwTxtFmtColl* pColl = 0;
/*N*/   if( pDoc->IsInsOnlyTextGlossary() )
/*N*/   {
/*?*/       SwNodeIndex aIdx( rIdx, -1 );
/*?*/       if( aIdx.GetNode().IsTxtNode() )
/*?*/       {
/*?*/           pCpyAttrNd = aIdx.GetNode().GetTxtNode();
/*?*/           pColl = &pCpyAttrNd->GetTxtColl()->GetNextTxtFmtColl();
/*?*/       }
/*N*/   }
/*N*/   if( !pColl )
/*N*/       pColl = pDoc->CopyTxtColl( *GetTxtColl() );
/*N*/
/*N*/   SwTxtNode* pTxtNd = pDoc->GetNodes().MakeTxtNode( rIdx, pColl );
/*N*/
/*N*/   // kopiere Attribute/Text
/*N*/   if( !pCpyAttrNd->GetpSwAttrSet() )
/*N*/       // wurde ein AttrSet fuer die Numerierung angelegt, so loesche diesen!
/*N*/       pTxtNd->ResetAllAttr();
/*N*/
/*N*/   // if Copy-Textnode unequal to Copy-Attrnode, then copy first
/*N*/   // the attributes into the new Node.
/*N*/   if( pCpyAttrNd != pCpyTxtNd )
/*N*/   {
/*?*/       pCpyAttrNd->CopyAttr( pTxtNd, 0, 0 );
/*?*/       if( pCpyAttrNd->GetpSwAttrSet() )
/*?*/       {
/*?*/           SwAttrSet aSet( *pCpyAttrNd->GetpSwAttrSet() );
/*?*/           aSet.ClearItem( RES_PAGEDESC );
/*?*/           aSet.ClearItem( RES_BREAK );
/*?*/           aSet.CopyToModify( *pTxtNd );
/*?*/       }
/*N*/   }
/*N*/
/*N*/       // ??? reicht das ??? was ist mit PostIts/Feldern/FeldTypen ???
/*N*/   pCpyTxtNd->Copy( pTxtNd, SwIndex( pCpyTxtNd ), pCpyTxtNd->GetTxt().Len() );
/*N*/
/*N*/   if( pCpyAttrNd->GetNum() )
/*N*/       pTxtNd->UpdateNum( *pCpyAttrNd->GetNum() );
/*N*/
/*N*/ //FEATURE::CONDCOLL
/*N*/   if( RES_CONDTXTFMTCOLL == pColl->Which() )
/*N*/       pTxtNd->ChkCondColl();
/*N*/ //FEATURE::CONDCOLL
/*N*/
/*N*/   return pTxtNd;
/*N*/ }


/*N*/ BOOL lcl_SrchNew( const _MapTblFrmFmt& rMap, void * pPara )
/*N*/ {
/*N*/   if( rMap.pOld != *(const SwFrmFmt**)pPara )
/*N*/       return TRUE;
/*N*/   *((const SwFrmFmt**)pPara) = rMap.pNew;
/*N*/   return FALSE;       // abbrechen, Pointer gefunden
/*N*/ }


/*N*/ struct _CopyTable
/*N*/ {
/*N*/   SwDoc* pDoc;
/*N*/   ULONG nOldTblSttIdx;
/*N*/   _MapTblFrmFmts& rMapArr;
/*N*/   SwTableLine* pInsLine;
/*N*/   SwTableBox* pInsBox;
/*N*/   SwTableNode *pTblNd;
/*N*/   const SwTable *pOldTable;
/*N*/
/*N*/   _CopyTable( SwDoc* pDc, _MapTblFrmFmts& rArr, ULONG nOldStt,
/*N*/               SwTableNode& rTblNd, const SwTable* pOldTbl )
/*N*/       : pDoc(pDc), pTblNd(&rTblNd), nOldTblSttIdx(nOldStt),
/*N*/       rMapArr(rArr), pOldTable( pOldTbl ), pInsLine(0), pInsBox(0)
/*N*/   {}
/*N*/ };

/*N*/ BOOL lcl_CopyTblBox( const SwTableBox*& rpBox, void* pPara );

/*N*/ BOOL lcl_CopyTblLine( const SwTableLine*& rpLine, void* pPara );

/*N*/ BOOL lcl_CopyTblBox( const SwTableBox*& rpBox, void* pPara )
/*N*/ {
/*N*/   _CopyTable* pCT = (_CopyTable*)pPara;
/*N*/
/*N*/   SwTableBoxFmt* pBoxFmt = (SwTableBoxFmt*)rpBox->GetFrmFmt();
/*N*/   pCT->rMapArr.ForEach( lcl_SrchNew, &pBoxFmt );
/*N*/   if( pBoxFmt == rpBox->GetFrmFmt() ) // ein neues anlegen ??
/*N*/   {
/*N*/       const SfxPoolItem* pItem;
/*N*/       if( SFX_ITEM_SET == pBoxFmt->GetItemState( RES_BOXATR_FORMULA, FALSE,
/*N*/           &pItem ) && ((SwTblBoxFormula*)pItem)->IsIntrnlName() )
/*N*/       {
/*?*/           ((SwTblBoxFormula*)pItem)->PtrToBoxNm( pCT->pOldTable );
/*N*/       }
/*N*/
/*N*/       pBoxFmt = pCT->pDoc->MakeTableBoxFmt();
/*N*/       pBoxFmt->CopyAttrs( *rpBox->GetFrmFmt() );
/*N*/
/*N*/       if( rpBox->GetSttIdx() )
/*N*/       {
/*N*/           SvNumberFormatter* pN = pCT->pDoc->GetNumberFormatter( FALSE );
/*N*/           if( pN && pN->HasMergeFmtTbl() && SFX_ITEM_SET == pBoxFmt->
/*N*/               GetItemState( RES_BOXATR_FORMAT, FALSE, &pItem ) )
/*N*/           {
/*?*/               ULONG nOldIdx = ((SwTblBoxNumFormat*)pItem)->GetValue();
/*?*/               ULONG nNewIdx = pN->GetMergeFmtIndex( nOldIdx );
/*?*/               if( nNewIdx != nOldIdx )
/*?*/                   pBoxFmt->SetAttr( SwTblBoxNumFormat( nNewIdx ));
/*?*/
/*N*/           }
/*N*/       }
/*N*/
/*N*/       pCT->rMapArr.Insert( _MapTblFrmFmt( rpBox->GetFrmFmt(), pBoxFmt ),
/*N*/                               pCT->rMapArr.Count() );
/*N*/   }
/*N*/
/*N*/   USHORT nLines = rpBox->GetTabLines().Count();
/*N*/   SwTableBox* pNewBox;
/*N*/   if( nLines )
/*?*/       pNewBox = new SwTableBox( pBoxFmt, nLines, pCT->pInsLine );
/*N*/   else
/*N*/   {
/*N*/       SwNodeIndex aNewIdx( *pCT->pTblNd,
/*N*/                           rpBox->GetSttIdx() - pCT->nOldTblSttIdx );
/*N*/       ASSERT( aNewIdx.GetNode().IsStartNode(), "Index nicht auf einem StartNode" );
/*N*/       pNewBox = new SwTableBox( pBoxFmt, aNewIdx, pCT->pInsLine );
/*N*/   }
/*N*/
/*N*/   pCT->pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pNewBox,
/*N*/                   pCT->pInsLine->GetTabBoxes().Count() );
/*N*/
/*N*/   if( nLines )
/*N*/   {
/*?*/       _CopyTable aPara( *pCT );
/*?*/       aPara.pInsBox = pNewBox;
/*?*/       ((SwTableBox*)rpBox)->GetTabLines().ForEach( &lcl_CopyTblLine, &aPara );
/*N*/   }
/*N*/   else if( pNewBox->IsInHeadline( &pCT->pTblNd->GetTable() ))
/*N*/       // in der HeadLine sind die Absaetze mit BedingtenVorlage anzupassen
/*N*/       pNewBox->GetSttNd()->CheckSectionCondColl();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL lcl_CopyTblLine( const SwTableLine*& rpLine, void* pPara )
/*N*/ {
/*N*/   _CopyTable* pCT = (_CopyTable*)pPara;
/*N*/   SwTableLineFmt* pLineFmt = (SwTableLineFmt*)rpLine->GetFrmFmt();
/*N*/   pCT->rMapArr.ForEach( lcl_SrchNew, &pLineFmt );
/*N*/   if( pLineFmt == rpLine->GetFrmFmt() )   // ein neues anlegen ??
/*N*/   {
/*N*/       pLineFmt = pCT->pDoc->MakeTableLineFmt();
/*N*/       pLineFmt->CopyAttrs( *rpLine->GetFrmFmt() );
/*N*/       pCT->rMapArr.Insert( _MapTblFrmFmt( rpLine->GetFrmFmt(), pLineFmt ),
/*N*/                               pCT->rMapArr.Count());
/*N*/   }
/*N*/   SwTableLine* pNewLine = new SwTableLine( pLineFmt,
/*N*/                           rpLine->GetTabBoxes().Count(), pCT->pInsBox );
/*N*/   // die neue Zeile in die Tabelle eintragen
/*N*/   if( pCT->pInsBox )
/*N*/   {
/*?*/       pCT->pInsBox->GetTabLines().C40_INSERT( SwTableLine, pNewLine,
/*?*/               pCT->pInsBox->GetTabLines().Count() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pCT->pTblNd->GetTable().GetTabLines().C40_INSERT( SwTableLine, pNewLine,
/*N*/               pCT->pTblNd->GetTable().GetTabLines().Count() );
/*N*/   }
/*N*/   pCT->pInsLine = pNewLine;
/*N*/   ((SwTableLine*)rpLine)->GetTabBoxes().ForEach( &lcl_CopyTblBox, pCT );
/*N*/   return TRUE;
/*N*/ }

/*N*/ SwTableNode* SwTableNode::MakeCopy( SwDoc* pDoc, const SwNodeIndex& rIdx ) const
/*N*/ {
/*N*/   // in welchen Array steht ich denn Nodes, UndoNodes ??
/*N*/   SwNodes& rNds = (SwNodes&)GetNodes();
/*N*/
/*N*/   if( pDoc->IsIdxInTbl( rIdx ) )
/*N*/       // zur Zeit keine Tabelle in Tabelle kopieren unterstuetzen
/*N*/       // (sprich: Text + Tabelle + Text )
/*?*/       return 0;
/*N*/
/*N*/   {
/*N*/       // nicht in Fussnoten kopieren !!
/*
!! Mal ohne Frames
        SwCntntNode* pCNd = pDoc->GetNodes()[ rIdx ]->GetCntntNode();
        SwFrm* pFrm;
        if( (pCNd && 0 != ( pFrm = pCNd->GetFrm()))
                ? pFrm->FindFtnFrm()
                : rIdx < pDoc->GetNodes().EndOfInserts &&
                    pDoc->GetNodes()[pDoc->GetNodes().EndOfInserts]->StartOfSection()
                    < rIdx )
*/
/*N*/       if( rIdx < pDoc->GetNodes().GetEndOfInserts().GetIndex() &&
/*N*/           rIdx >= pDoc->GetNodes().GetEndOfInserts().StartOfSectionIndex() )
/*?*/           return 0;
/*N*/   }
/*N*/
/*N*/   // das TableFrmFmt kopieren
/*N*/   String sTblName( GetTable().GetFrmFmt()->GetName() );
/*N*/   if( !pDoc->IsCopyIsMove() )
/*N*/   {
/*N*/       const SwFrmFmts& rTblFmts = *pDoc->GetTblFrmFmts();
/*N*/       for( USHORT n = rTblFmts.Count(); n; )
/*N*/           if( rTblFmts[ --n ]->GetName() == sTblName )
/*N*/           {
/*N*/               sTblName = pDoc->GetUniqueTblName();
/*N*/               break;
/*N*/           }
/*N*/   }
/*N*/
/*N*/   SwFrmFmt* pTblFmt = pDoc->MakeTblFrmFmt( sTblName, pDoc->GetDfltFrmFmt() );
/*N*/   pTblFmt->CopyAttrs( *GetTable().GetFrmFmt() );
/*N*/   SwTableNode* pTblNd = new SwTableNode( rIdx );
/*N*/   SwEndNode* pEndNd = new SwEndNode( rIdx, *pTblNd );
/*N*/   SwNodeIndex aInsPos( *pEndNd );
/*N*/
/*N*/   SwTable& rTbl = (SwTable&)pTblNd->GetTable();
/*N*/   pTblFmt->Add( &rTbl );      // das Frame-Format setzen
/*N*/
/*N*/   rTbl.SetHeadlineRepeat( GetTable().IsHeadlineRepeat() );
/*N*/   rTbl.SetTblChgMode( GetTable().GetTblChgMode() );
/*N*/
/*N*/   SwDDEFieldType* pDDEType = 0;
/*N*/   if( IS_TYPE( SwDDETable, &GetTable() ))
/*N*/   {
/*?*/       // es wird eine DDE-Tabelle kopiert
/*?*/       // ist im neuen Dokument ueberhaupt der FeldTyp vorhanden ?
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pDDEType = ((SwDDETable&)GetTable()).GetDDEFldType();
//STRIP001 /*?*/        if( pDDEType->IsDeleted() )
//STRIP001 /*?*/            pDoc->InsDeletedFldType( *pDDEType );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pDDEType = (SwDDEFieldType*)pDoc->InsertFldType( *pDDEType );
//STRIP001 /*?*/        ASSERT( pDDEType, "unbekannter FieldType" );
//STRIP001 /*?*/
//STRIP001 /*?*/        // tauschen am Node den Tabellen-Pointer aus
//STRIP001 /*?*/        SwDDETable* pNewTable = new SwDDETable( pTblNd->GetTable(), pDDEType );
//STRIP001 /*?*/        pTblNd->SetNewTable( pNewTable, FALSE );
/*N*/   }
/*N*/   // dann kopiere erstmal den Inhalt der Tabelle, die Zuordnung der
/*N*/   // Boxen/Lines und das anlegen der Frames erfolgt spaeter
/*N*/   SwNodeRange aRg( *this, +1, *EndOfSectionNode() );  // (wo stehe in denn nun ??)
/*N*/   rNds._Copy( aRg, aInsPos, FALSE );
/*N*/
/*N*/   // Sonderbehandlung fuer eine einzelne Box
/*N*/   if( 1 == GetTable().GetTabSortBoxes().Count() )
/*N*/   {
/*?*/       aRg.aStart.Assign( *pTblNd, 1 );
/*?*/       aRg.aEnd.Assign( *pTblNd->EndOfSectionNode() );
/*?*/       pDoc->GetNodes().SectionDown( &aRg, SwTableBoxStartNode );
/*N*/   }
/*N*/
/*N*/   // loesche alle Frames vom kopierten Bereich, diese werden beim
/*N*/   // erzeugen des TableFrames angelegt !
/*N*/   pTblNd->DelFrms();
/*N*/
/*N*/   _MapTblFrmFmts aMapArr;
/*N*/   _CopyTable aPara( pDoc, aMapArr, GetIndex(), *pTblNd, &GetTable() );
/*N*/
/*N*/   ((SwTable&)GetTable()).GetTabLines().ForEach( &lcl_CopyTblLine, &aPara );
/*N*/
/*N*/   if( pDDEType && pDoc->GetRootFrm() )
/*?*/       pDDEType->IncRefCnt();
/*N*/
/*N*/   return pTblNd;
/*N*/ }

//STRIP001 void SwTxtNode::CopyCollFmt( SwTxtNode& rDestNd )
//STRIP001 {
//STRIP001  // kopiere die Formate in das andere Dokument:
//STRIP001
//STRIP001  // Sonderbehandlung fuer PageBreak/PageDesc/ColBrk
//STRIP001  SwDoc* pDestDoc = rDestNd.GetDoc();
//STRIP001  SwAttrSet aPgBrkSet( pDestDoc->GetAttrPool(), aBreakSetRange );
//STRIP001  SwAttrSet* pSet;
//STRIP001
//STRIP001  if( 0 != ( pSet = rDestNd.GetpSwAttrSet() ) )
//STRIP001  {
//STRIP001      // Sonderbehandlung fuer unsere Break-Attribute
//STRIP001      const SfxPoolItem* pAttr;
//STRIP001      if( SFX_ITEM_SET == pSet->GetItemState( RES_BREAK, FALSE, &pAttr ) )
//STRIP001          aPgBrkSet.Put( *pAttr );
//STRIP001
//STRIP001      if( SFX_ITEM_SET == pSet->GetItemState( RES_PAGEDESC, FALSE, &pAttr ) )
//STRIP001          aPgBrkSet.Put( *pAttr );
//STRIP001  }
//STRIP001
//STRIP001  rDestNd.ChgFmtColl( pDestDoc->CopyTxtColl( *GetTxtColl() ));
//STRIP001  if( 0 != ( pSet = GetpSwAttrSet() ) )
//STRIP001      pSet->CopyToModify( rDestNd );
//STRIP001
//STRIP001  if( aPgBrkSet.Count() )
//STRIP001      rDestNd.SwCntntNode::SetAttr( aPgBrkSet );
//STRIP001 }


//  ----- Copy-Methode vom SwDoc ------

    // verhinder das Kopieren in Fly's, die im Bereich verankert sind.
//STRIP001 BOOL lcl_ChkFlyFly( SwDoc* pDoc, ULONG nSttNd, ULONG nEndNd,
//STRIP001                      ULONG nInsNd )
//STRIP001 {
//STRIP001  const SwFrmFmt* pFmt;
//STRIP001  const SwFmtAnchor* pAnchor;
//STRIP001  const SwPosition* pAPos;
//STRIP001  const SwSpzFrmFmts& rFrmFmtTbl = *pDoc->GetSpzFrmFmts();
//STRIP001
//STRIP001  for( USHORT n = 0; n < rFrmFmtTbl.Count(); ++n )
//STRIP001  {
//STRIP001      pFmt = rFrmFmtTbl[n];
//STRIP001      pAnchor = &pFmt->GetAnchor();
//STRIP001      if( 0 != ( pAPos = pAnchor->GetCntntAnchor()) &&
//STRIP001          ( FLY_IN_CNTNT == pAnchor->GetAnchorId() ||
//STRIP001            FLY_AUTO_CNTNT == pAnchor->GetAnchorId() ||
//STRIP001            FLY_AT_FLY == pAnchor->GetAnchorId() ||
//STRIP001            FLY_AT_CNTNT == pAnchor->GetAnchorId() ) &&
//STRIP001          nSttNd <= pAPos->nNode.GetIndex() &&
//STRIP001          pAPos->nNode.GetIndex() < nEndNd )
//STRIP001      {
//STRIP001          const SwFmtCntnt& rCntnt = pFmt->GetCntnt();
//STRIP001          SwStartNode* pSNd;
//STRIP001          if( !rCntnt.GetCntntIdx() ||
//STRIP001              0 == ( pSNd = rCntnt.GetCntntIdx()->GetNode().GetStartNode() ))
//STRIP001              continue;
//STRIP001
//STRIP001          if( pSNd->GetIndex() < nInsNd &&
//STRIP001              nInsNd < pSNd->EndOfSectionIndex() )
//STRIP001              return TRUE;        // nicht kopieren !!
//STRIP001
//STRIP001          if( lcl_ChkFlyFly( pDoc, pSNd->GetIndex(),
//STRIP001                      pSNd->EndOfSectionIndex(), nInsNd ) )
//STRIP001              return TRUE;        // nicht kopieren !!
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void lcl_SetCpyPos( const SwPosition& rOrigPos,
//STRIP001                  const SwPosition& rOrigStt,
//STRIP001                  const SwPosition& rCpyStt,
//STRIP001                  SwPosition& rChgPos )
//STRIP001 {
//STRIP001  ULONG nNdOff = rOrigPos.nNode.GetIndex();
//STRIP001  nNdOff -= rOrigStt.nNode.GetIndex();
//STRIP001  xub_StrLen nCntntPos = rOrigPos.nContent.GetIndex();
//STRIP001
//STRIP001  if( nNdOff )
//STRIP001      rChgPos.nNode = nNdOff + rCpyStt.nNode.GetIndex();
//STRIP001  else
//STRIP001  {
//STRIP001      // dann nur den Content anpassen
//STRIP001      if( nCntntPos > rOrigStt.nContent.GetIndex() )
//STRIP001          nCntntPos -= rOrigStt.nContent.GetIndex();
//STRIP001      else
//STRIP001          nCntntPos = 0;
//STRIP001      nCntntPos += rCpyStt.nContent.GetIndex();
//STRIP001  }
//STRIP001  rChgPos.nContent.Assign( rChgPos.nNode.GetNode().GetCntntNode(), nCntntPos );
//STRIP001 }

//STRIP001 void lcl_CopyBookmarks( const SwPaM& rPam, SwPaM& rCpyPam )
//STRIP001 {
//STRIP001  const SwDoc* pSrcDoc = rPam.GetDoc();
//STRIP001  SwDoc* pDestDoc =  rCpyPam.GetDoc();
//STRIP001  BOOL bDoesUndo = pDestDoc->DoesUndo();
//STRIP001  pDestDoc->DoUndo( FALSE );
//STRIP001
//STRIP001  const SwPosition &rStt = *rPam.Start(), &rEnd = *rPam.End();
//STRIP001  SwPosition* pCpyStt = rCpyPam.Start();
//STRIP001
//STRIP001  const SwBookmark* pBkmk;
//STRIP001  for( USHORT nCnt = pSrcDoc->GetBookmarks().Count(); nCnt; )
//STRIP001  {
//STRIP001      // liegt auf der Position ??
//STRIP001      if( ( pBkmk = pSrcDoc->GetBookmarks()[ --nCnt ])->GetPos() < rStt
//STRIP001          || pBkmk->GetPos() >= rEnd )
//STRIP001          continue;
//STRIP001
//STRIP001      int bHasOtherPos = 0 != pBkmk->GetOtherPos();
//STRIP001      if( bHasOtherPos && ( *pBkmk->GetOtherPos() < rStt ||
//STRIP001          *pBkmk->GetOtherPos() >= rEnd ) )
//STRIP001          continue;
//STRIP001
//STRIP001      SwPaM aTmpPam( *pCpyStt );
//STRIP001      lcl_SetCpyPos( pBkmk->GetPos(), rStt, *pCpyStt, *aTmpPam.GetPoint() );
//STRIP001      if( bHasOtherPos )
//STRIP001      {
//STRIP001          aTmpPam.SetMark();
//STRIP001          lcl_SetCpyPos( *pBkmk->GetOtherPos(), rStt, *pCpyStt,
//STRIP001                          *aTmpPam.GetMark() );
//STRIP001      }
//STRIP001
//STRIP001      String sNewNm( pBkmk->GetName() );
//STRIP001      if( !pDestDoc->IsCopyIsMove() &&
//STRIP001          USHRT_MAX != pDestDoc->FindBookmark( sNewNm ) )
//STRIP001          pDestDoc->MakeUniqueBookmarkName( sNewNm );
//STRIP001      pDestDoc->MakeBookmark( aTmpPam, pBkmk->GetKeyCode(), sNewNm,
//STRIP001                              pBkmk->GetShortName(), pBkmk->GetType() );
//STRIP001  }
//STRIP001  pDestDoc->DoUndo( bDoesUndo );
//STRIP001 }

//STRIP001 void lcl_DeleteRedlines( const SwPaM& rPam, SwPaM& rCpyPam )
//STRIP001 {
//STRIP001  const SwDoc* pSrcDoc = rPam.GetDoc();
//STRIP001  const SwRedlineTbl& rTbl = pSrcDoc->GetRedlineTbl();
//STRIP001  if( rTbl.Count() )
//STRIP001  {
//STRIP001      SwDoc* pDestDoc = rCpyPam.GetDoc();
//STRIP001      SwPosition* pCpyStt = rCpyPam.Start(), *pCpyEnd = rCpyPam.End();
//STRIP001      SwPaM* pDelPam = 0;
//STRIP001      const SwPosition *pStt = rPam.Start(), *pEnd = rPam.End();
//STRIP001      USHORT n = 0;
//STRIP001      pSrcDoc->GetRedline( *pStt, &n );
//STRIP001      for( ; n < rTbl.Count(); ++n )
//STRIP001      {
//STRIP001          const SwRedline* pRedl = rTbl[ n ];
//STRIP001          if( REDLINE_DELETE == pRedl->GetType() && pRedl->IsVisible() )
//STRIP001          {
//STRIP001              const SwPosition *pRStt = pRedl->Start(), *pREnd = pRedl->End();
//STRIP001
//STRIP001              SwComparePosition eCmpPos = ComparePosition( *pStt, *pEnd, *pRStt, *pREnd );
//STRIP001              switch( eCmpPos )
//STRIP001              {
//STRIP001              case POS_COLLIDE_END:
//STRIP001              case POS_BEFORE:                // Pos1 liegt vor Pos2
//STRIP001                  break;
//STRIP001
//STRIP001              case POS_COLLIDE_START:
//STRIP001              case POS_BEHIND:                // Pos1 liegt hinter Pos2
//STRIP001                  n = rTbl.Count();
//STRIP001                  break;
//STRIP001
//STRIP001              default:
//STRIP001                  {
//STRIP001                      pDelPam = new SwPaM( *pCpyStt, pDelPam );
//STRIP001                      if( *pStt < *pRStt )
//STRIP001                          lcl_SetCpyPos( *pRStt, *pStt, *pCpyStt,
//STRIP001                                          *pDelPam->GetPoint() );
//STRIP001                      pDelPam->SetMark();
//STRIP001
//STRIP001                      if( *pEnd < *pREnd )
//STRIP001                          *pDelPam->GetPoint() = *pCpyEnd;
//STRIP001                      else
//STRIP001                          lcl_SetCpyPos( *pREnd, *pStt, *pCpyStt,
//STRIP001                                          *pDelPam->GetPoint() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( pDelPam )
//STRIP001      {
//STRIP001          SwRedlineMode eOld = pDestDoc->GetRedlineMode();
//STRIP001          pDestDoc->SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001
//STRIP001          BOOL bDoesUndo = pDestDoc->DoesUndo();
//STRIP001          pDestDoc->DoUndo( FALSE );
//STRIP001
//STRIP001          do {
//STRIP001              pDestDoc->DeleteAndJoin( *(SwPaM*)pDelPam->GetNext() );
//STRIP001              if( pDelPam->GetNext() == pDelPam )
//STRIP001                  break;
//STRIP001              delete pDelPam->GetNext();
//STRIP001          } while( TRUE );
//STRIP001          delete pDelPam;
//STRIP001
//STRIP001          pDestDoc->DoUndo( bDoesUndo );
//STRIP001          pDestDoc->SetRedlineMode_intern( eOld );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_DeleteRedlines( const SwNodeRange& rRg, SwNodeRange& rCpyRg )
//STRIP001 {
//STRIP001  SwDoc* pSrcDoc = rRg.aStart.GetNode().GetDoc();
//STRIP001  if( pSrcDoc->GetRedlineTbl().Count() )
//STRIP001  {
//STRIP001      SwPaM aRgTmp( rRg.aStart, rRg.aEnd );
//STRIP001      SwPaM aCpyTmp( rCpyRg.aStart, rCpyRg.aEnd );
//STRIP001      lcl_DeleteRedlines( aRgTmp, aCpyTmp );
//STRIP001  }
//STRIP001 }

// Kopieren eines Bereiches im oder in ein anderes Dokument !

/*N*/ BOOL SwDoc::Copy( SwPaM& rPam, SwPosition& rPos ) const
/*N*/ {
/*N*/   const SwPosition *pStt = rPam.Start(), *pEnd = rPam.End();
/*N*/   // kein Copy abfangen.
/*N*/   if( !rPam.HasMark() || *pStt >= *pEnd )
/*N*/       return FALSE;
/*N*/
/*N*/   SwDoc* pDoc = rPos.nNode.GetNode().GetDoc();
/*N*/
/*N*/   // verhinder das Kopieren in Fly's, die im Bereich verankert sind.
/*N*/   if( pDoc == this )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 // Start-/EndNode noch korrigieren
//STRIP001 /*?*/        ULONG nStt = pStt->nNode.GetIndex(),
//STRIP001 /*?*/                nEnd = pEnd->nNode.GetIndex(),
//STRIP001 /*?*/                nDiff = nEnd - nStt +1;
//STRIP001 /*?*/        SwNode* pNd = GetNodes()[ nStt ];
//STRIP001 /*?*/        if( pNd->IsCntntNode() && pStt->nContent.GetIndex() )
//STRIP001 /*?*/            ++nStt, --nDiff;
//STRIP001 /*?*/        if( (pNd = GetNodes()[ nEnd ])->IsCntntNode() &&
//STRIP001 /*?*/            ((SwCntntNode*)pNd)->Len() != pEnd->nContent.GetIndex() )
//STRIP001 /*?*/            --nEnd, --nDiff;
//STRIP001 /*?*/        if( nDiff &&
//STRIP001 /*?*/            lcl_ChkFlyFly( pDoc, nStt, nEnd, rPos.nNode.GetIndex() ) )
//STRIP001 /*?*/            return FALSE;
/*N*/   }
/*N*/
/*N*/   SwPaM* pRedlineRange = 0;
/*N*/   if( pDoc->IsRedlineOn() ||
/*N*/       (!pDoc->IsIgnoreRedline() && pDoc->GetRedlineTbl().Count() ) )
/*N*/       pRedlineRange = new SwPaM( rPos );
/*N*/
/*N*/   SwRedlineMode eOld = pDoc->GetRedlineMode();
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   if( pDoc && pDoc != this )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    bRet = _Copy( rPam, rPos, TRUE, pRedlineRange );    // nur normales Kopieren
/*N*/   // Copy in sich selbst (ueber mehrere Nodes wird hier gesondert
/*N*/   // behandelt; in einem TextNode wird normal behandelt)
/*N*/   else if( ! ( *pStt <= rPos && rPos < *pEnd &&
/*N*/           ( pStt->nNode != pEnd->nNode ||
/*N*/             !pStt->nNode.GetNode().IsTxtNode() )) )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    bRet = _Copy( rPam, rPos, TRUE, pRedlineRange );    // nur normales Kopieren
/*N*/
/*N*/   else
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ASSERT( this == pDoc, " falscher Copy-Zweig!" );
//STRIP001 /*?*/        pDoc->SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001 /*?*/
//STRIP001 /*?*/        BOOL bDoUndo = pDoc->DoesUndo();
//STRIP001 /*?*/        pDoc->DoUndo( FALSE );  // Auf jedenfall Undo abschalten
//STRIP001 /*?*/        // dann kopiere den Bereich im unteren DokumentBereich,
//STRIP001 /*?*/        // (mit Start/End-Nodes geklammert) und verschiebe diese
//STRIP001 /*?*/        // dann an die gewuenschte Stelle.
//STRIP001 /*?*/
//STRIP001 /*?*/        SwUndoCpyDoc* pUndo;
//STRIP001 /*?*/        SwPaM aPam( rPos );         // UndoBereich sichern
//STRIP001 /*?*/        if( bDoUndo )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pDoc->ClearRedo();
//STRIP001 /*?*/            pUndo = new SwUndoCpyDoc( aPam );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        SwStartNode* pSttNd = pDoc->GetNodes().MakeEmptySection(
//STRIP001 /*?*/                                SwNodeIndex( GetNodes().GetEndOfAutotext() ));
//STRIP001 /*?*/        aPam.GetPoint()->nNode = *pSttNd->EndOfSectionNode();
//STRIP001 /*?*/        pDoc->_Copy( rPam, *aPam.GetPoint(), FALSE );       // kopieren ohne Frames
//STRIP001 /*?*/
//STRIP001 /*?*/        aPam.GetPoint()->nNode = pDoc->GetNodes().GetEndOfAutotext();
//STRIP001 /*?*/        aPam.SetMark();
//STRIP001 /*?*/        SwCntntNode* pNode = pDoc->GetNodes().GoPrevious( &aPam.GetMark()->nNode );
//STRIP001 /*?*/        pNode->MakeEndIndex( &aPam.GetMark()->nContent );
//STRIP001 /*?*/
//STRIP001 /*?*/        aPam.GetPoint()->nNode = *aPam.GetNode()->StartOfSectionNode();
//STRIP001 /*?*/        pNode = pDoc->GetNodes().GoNext( &aPam.GetPoint()->nNode );
//STRIP001 /*?*/        pNode->MakeStartIndex( &aPam.GetPoint()->nContent );
//STRIP001 /*?*/        pDoc->Move( aPam, rPos );               // auf gewuenschte Position moven
//STRIP001 /*?*/
//STRIP001 /*?*/        pNode = aPam.GetCntntNode();
//STRIP001 /*?*/        *aPam.GetPoint() = rPos;        // Cursor umsetzen fuers Undo !
//STRIP001 /*?*/        aPam.SetMark();                 // auch den Mark umsetzen !!
//STRIP001 /*?*/        aPam.DeleteMark();              // aber keinen Bereich makieren !!
//STRIP001 /*?*/        pDoc->DeleteSection( pNode );           // Bereich wieder loeschen
//STRIP001 /*?*/
//STRIP001 /*?*/        // falls Undo eingeschaltet ist, so speicher den eingefuegten Bereich
//STRIP001 /*?*/        pDoc->DoUndo( bDoUndo );
//STRIP001 /*?*/        if( bDoUndo )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndo->SetInsertRange( aPam );
//STRIP001 /*?*/            pDoc->AppendUndo( pUndo );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( pRedlineRange )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pRedlineRange->SetMark();
//STRIP001 /*?*/            *pRedlineRange->GetPoint() = *aPam.GetPoint();
//STRIP001 /*?*/            *pRedlineRange->GetMark() = *aPam.GetMark();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->SetModified();
//STRIP001 /*?*/        bRet = TRUE;
/*N*/   }
/*N*/
/*N*/   pDoc->SetRedlineMode_intern( eOld );
/*N*/   if( pRedlineRange )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 if( pDoc->IsRedlineOn() )
//STRIP001 /*?*/            pDoc->AppendRedline( new SwRedline( REDLINE_INSERT, *pRedlineRange ));
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pDoc->SplitRedline( *pRedlineRange );
//STRIP001 /*?*/        delete pRedlineRange;
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

// Kopieren eines Bereiches im oder in ein anderes Dokument !
// Die Position darf nicht im Bereich liegen !!

//STRIP001 BOOL SwDoc::_Copy( SwPaM& rPam, SwPosition& rPos,
//STRIP001                  BOOL bMakeNewFrms, SwPaM* pCpyRange ) const
//STRIP001 {
//STRIP001  SwDoc* pDoc = rPos.nNode.GetNode().GetDoc();
//STRIP001
//STRIP001  SwPosition *pStt = rPam.Start(), *pEnd = rPam.End();
//STRIP001  // kein Copy abfangen.
//STRIP001  if( !rPam.HasMark() || *pStt >= *pEnd ||
//STRIP001      //JP 29.6.2001: 88963 - dont copy if inspos is in region of start to end
//STRIP001      //JP 15.11.2001: don't test inclusive the end, ever exclusive
//STRIP001      ( pDoc == this && *pStt <= rPos && rPos < *pEnd ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bEndEqualIns = pDoc == this && rPos == *pEnd;
//STRIP001
//STRIP001  // falls Undo eingeschaltet, erzeuge das UndoCopy-Objekt
//STRIP001  SwUndoCpyDoc* pUndo;
//STRIP001  SwPaM aCpyPam( rPos );
//STRIP001
//STRIP001  SwTblNumFmtMerge aTNFM( *this, *pDoc );
//STRIP001
//STRIP001  if( pDoc->DoesUndo() )
//STRIP001  {
//STRIP001      pDoc->ClearRedo();
//STRIP001      pUndo = new SwUndoCpyDoc( aCpyPam );
//STRIP001      pDoc->AppendUndo( pUndo );
//STRIP001  }
//STRIP001
//STRIP001  SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001  pDoc->SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001
//STRIP001
//STRIP001  // bewege den Pam von der Insert-Position ein zurueck, dadurch wird
//STRIP001  // die Position nicht "verschoben"
//STRIP001  aCpyPam.SetMark();
//STRIP001  BOOL bCanMoveBack = aCpyPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001  if( !bCanMoveBack )
//STRIP001      aCpyPam.GetPoint()->nNode--;
//STRIP001
//STRIP001  SwNodeRange aRg( pStt->nNode, pEnd->nNode );
//STRIP001  SwNodeIndex aInsPos( rPos.nNode );
//STRIP001  BOOL bOneNode = pStt->nNode == pEnd->nNode;
//STRIP001  SwTxtNode* pSttNd = pStt->nNode.GetNode().GetTxtNode();
//STRIP001  SwTxtNode* pEndNd = pEnd->nNode.GetNode().GetTxtNode();
//STRIP001  SwTxtNode* pDestNd = aInsPos.GetNode().GetTxtNode();
//STRIP001  BOOL bCopyCollFmt = !pDoc->IsInsOnlyTextGlossary() && (
//STRIP001                      ( pDestNd && !pDestNd->GetTxt().Len() ) ||
//STRIP001                      ( !bOneNode && !rPos.nContent.GetIndex() ));
//STRIP001  BOOL bCopyBookmarks = TRUE;
//STRIP001  BOOL bStartIsTxtNode = 0 != pSttNd;
//STRIP001
//STRIP001  // Block, damit aus diesem gesprungen werden kann !!
//STRIP001  do {
//STRIP001      if( pSttNd )
//STRIP001      {
//STRIP001          // den Anfang nicht komplett kopieren ?
//STRIP001          if( !bCopyCollFmt || pStt->nContent.GetIndex() )
//STRIP001          {
//STRIP001              SwIndex aDestIdx( rPos.nContent );
//STRIP001              BOOL bCopyOk = FALSE;
//STRIP001              if( !pDestNd )
//STRIP001              {
//STRIP001                  if( pStt->nContent.GetIndex() || bOneNode )
//STRIP001                      pDestNd = pDoc->GetNodes().MakeTxtNode( aInsPos,
//STRIP001                          pDoc->GetTxtCollFromPool(RES_POOLCOLL_STANDARD));
//STRIP001                  else
//STRIP001                  {
//STRIP001                      pDestNd = (SwTxtNode*)pSttNd->MakeCopy( pDoc, aInsPos );
//STRIP001                      bCopyOk = TRUE;
//STRIP001                  }
//STRIP001                  aDestIdx.Assign( pDestNd, 0 );
//STRIP001                  bCopyCollFmt = TRUE;
//STRIP001              }
//STRIP001              else if( !bOneNode )
//STRIP001              {
//STRIP001                  BYTE nNumLevel = !pDestNd->GetNum() ? 0
//STRIP001                                          : pDestNd->GetNum()->GetLevel();
//STRIP001
//STRIP001                  xub_StrLen nCntntEnd = pEnd->nContent.GetIndex();
//STRIP001                  BOOL bDoesUndo = pDoc->DoesUndo();
//STRIP001                  pDoc->DoUndo( FALSE );
//STRIP001                  pDoc->SplitNode( rPos );
//STRIP001                  pDoc->DoUndo( bDoesUndo );
//STRIP001
//STRIP001                  // Nummerierung korrigieren, SplitNode erzeugt immer einen
//STRIP001                  // neuen Level
//STRIP001                  if( NO_NUMLEVEL & nNumLevel )
//STRIP001                      pDestNd->UpdateNum( SwNodeNum( nNumLevel ));
//STRIP001
//STRIP001                  if( bCanMoveBack && rPos == *aCpyPam.GetPoint() )
//STRIP001                  {
//STRIP001                      // nach dem SplitNode, den CpyPam wieder richtig aufspannen
//STRIP001                      aCpyPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001                      aCpyPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001                  }
//STRIP001
//STRIP001                  pDestNd = pDoc->GetNodes()[ aInsPos.GetIndex()-1 ]->GetTxtNode();
//STRIP001                  aDestIdx.Assign( pDestNd, pDestNd->GetTxt().Len() );
//STRIP001
//STRIP001                  // korrigiere den Bereich wieder !!
//STRIP001                  if( bEndEqualIns )
//STRIP001                  {
//STRIP001                      BOOL bChg = pEnd != rPam.GetPoint();
//STRIP001                      if( bChg )
//STRIP001                          rPam.Exchange();
//STRIP001                      rPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001                      if( bChg )
//STRIP001                          rPam.Exchange();
//STRIP001
//STRIP001                      aRg.aEnd = pEnd->nNode;
//STRIP001                      pEndNd = pEnd->nNode.GetNode().GetTxtNode();
//STRIP001                  }
//STRIP001                  else if( rPos == *pEnd )        // Wurde das Ende auch verschoben
//STRIP001                  {
//STRIP001                      pEnd->nNode--;
//STRIP001                      pEnd->nContent.Assign( pDestNd, nCntntEnd );
//STRIP001                      aRg.aEnd = pEnd->nNode;
//STRIP001                      pEndNd = pEnd->nNode.GetNode().GetTxtNode();
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              const SfxPoolItem * pItem = NULL;
//STRIP001              SwAttrSet * pAttrSet = pDestNd->GetpSwAttrSet();
//STRIP001
//STRIP001              /* #107213#: Safe numrule item at destination. */
//STRIP001              int aState = SFX_ITEM_UNKNOWN;
//STRIP001              SwNumRuleItem aNumRuleItem;
//STRIP001
//STRIP001              if (pAttrSet != NULL)
//STRIP001              {
//STRIP001                  aState = pAttrSet->GetItemState
//STRIP001                      (RES_PARATR_NUMRULE, FALSE, &pItem);
//STRIP001
//STRIP001                  if (SFX_ITEM_SET == aState)
//STRIP001                      aNumRuleItem = *((SwNumRuleItem *) pItem);
//STRIP001              }
//STRIP001              /* #107213# */
//STRIP001
//STRIP001              if( !bCopyOk )
//STRIP001              {
//STRIP001                  xub_StrLen nCpyLen = ( bOneNode ? pEnd->nContent.GetIndex()
//STRIP001                                          : pSttNd->GetTxt().Len() )
//STRIP001                                  - pStt->nContent.GetIndex();
//STRIP001                  pSttNd->Copy( pDestNd, aDestIdx, pStt->nContent, nCpyLen );
//STRIP001                  if( bEndEqualIns )
//STRIP001                      pEnd->nContent -= nCpyLen;
//STRIP001              }
//STRIP001
//STRIP001              if( bOneNode )
//STRIP001              {
//STRIP001                  // ist der DestinationNode leer, kopiere die Vorlage mit
//STRIP001                  if( bCopyCollFmt )
//STRIP001                  {
//STRIP001                      pSttNd->CopyCollFmt( *pDestNd );
//STRIP001
//STRIP001                      if (pSttNd->GetNum())
//STRIP001                              pDestNd->UpdateNum(*pSttNd->GetNum());
//STRIP001
//STRIP001                      /* #107213# If only a part of one paragraph is copied
//STRIP001                            restore the numrule at the destination. */
//STRIP001                      if (SFX_ITEM_SET == aState)
//STRIP001                          pDestNd->SwCntntNode::SetAttr(aNumRuleItem);
//STRIP001                      else
//STRIP001                          pDestNd->ResetAttr(RES_PARATR_NUMRULE);
//STRIP001                  }
//STRIP001
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              aRg.aStart++;
//STRIP001          }
//STRIP001      }
//STRIP001      else if( pDestNd )
//STRIP001      {
//STRIP001          if( rPos.nContent.GetIndex() == pDestNd->Len() )
//STRIP001          {
//STRIP001              aInsPos++;
//STRIP001              bStartIsTxtNode = TRUE;
//STRIP001          }
//STRIP001          else if( rPos.nContent.GetIndex() )
//STRIP001          {
//STRIP001              // splitte den TextNode, bei dem Eingefuegt wird.
//STRIP001              BYTE nNumLevel = !pDestNd->GetNum() ? 0
//STRIP001                                      : pDestNd->GetNum()->GetLevel();
//STRIP001
//STRIP001              xub_StrLen nCntntEnd = pEnd->nContent.GetIndex();
//STRIP001              BOOL bDoesUndo = pDoc->DoesUndo();
//STRIP001              pDoc->DoUndo( FALSE );
//STRIP001              pDoc->SplitNode( rPos );
//STRIP001              pDoc->DoUndo( bDoesUndo );
//STRIP001
//STRIP001              // Nummerierung korrigieren, SplitNode erzeugt immer einen
//STRIP001              // neuen Level
//STRIP001              if( NO_NUMLEVEL & nNumLevel )
//STRIP001                  pDestNd->UpdateNum( SwNodeNum( nNumLevel ));
//STRIP001
//STRIP001              if( bCanMoveBack && rPos == *aCpyPam.GetPoint() )
//STRIP001              {
//STRIP001                  // nach dem SplitNode, den CpyPam wieder richtig aufspannen
//STRIP001                  aCpyPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001                  aCpyPam.Move( fnMoveBackward, fnGoCntnt );
//STRIP001              }
//STRIP001
//STRIP001              // korrigiere den Bereich wieder !!
//STRIP001              if( bEndEqualIns )
//STRIP001                  aRg.aEnd--;
//STRIP001              else if( rPos == *pEnd )        // Wurde das Ende auch verschoben
//STRIP001              {
//STRIP001                  rPos.nNode-=2;
//STRIP001                  rPos.nContent.Assign( rPos.nNode.GetNode().GetCntntNode(),
//STRIP001                                          nCntntEnd );
//STRIP001                  rPos.nNode++;
//STRIP001                  aRg.aEnd--;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pDestNd = aInsPos.GetNode().GetTxtNode();
//STRIP001      if( pEndNd )
//STRIP001      {
//STRIP001          SwIndex aDestIdx( rPos.nContent );
//STRIP001          if( !pDestNd )
//STRIP001          {
//STRIP001              pDestNd = pDoc->GetNodes().MakeTxtNode( aInsPos,
//STRIP001                          pDoc->GetTxtCollFromPool(RES_POOLCOLL_STANDARD));
//STRIP001              aDestIdx.Assign( pDestNd, 0  );
//STRIP001              aInsPos--;
//STRIP001          }
//STRIP001
//STRIP001          const SfxPoolItem * pItem = NULL;
//STRIP001          SwAttrSet * pAttrSet = pDestNd->GetpSwAttrSet();
//STRIP001
//STRIP001          /* #107213# Save numrule at destination */
//STRIP001          int aState = SFX_ITEM_UNKNOWN;
//STRIP001          SwNumRuleItem aNumRuleItem;
//STRIP001
//STRIP001          if (pAttrSet != NULL)
//STRIP001          {
//STRIP001              aState = pAttrSet->GetItemState
//STRIP001                  (RES_PARATR_NUMRULE, FALSE, &pItem);
//STRIP001
//STRIP001              if (SFX_ITEM_SET == aState)
//STRIP001                  aNumRuleItem = *((SwNumRuleItem *) pItem);
//STRIP001          }
//STRIP001          /* #107213# */
//STRIP001
//STRIP001          BOOL bEmptyDestNd = 0 == pDestNd->GetTxt().Len();
//STRIP001          pEndNd->Copy( pDestNd, aDestIdx, SwIndex( pEndNd ),
//STRIP001                          pEnd->nContent.GetIndex() );
//STRIP001
//STRIP001          // auch alle FormatVorlagen kopieren
//STRIP001          if( bCopyCollFmt && ( bOneNode || bEmptyDestNd ))
//STRIP001          {
//STRIP001              pEndNd->CopyCollFmt( *pDestNd );
//STRIP001
//STRIP001              if (pEndNd->GetNum())
//STRIP001                  pDestNd->UpdateNum( *pEndNd->GetNum() );
//STRIP001
//STRIP001              if (bOneNode)
//STRIP001              {
//STRIP001                  /* #107213# If only a part of one paragraph is copied
//STRIP001                        restore the numrule at the destination. */
//STRIP001                  if (SFX_ITEM_SET == aState)
//STRIP001                      pDestNd->SwCntntNode::SetAttr(aNumRuleItem);
//STRIP001                  else
//STRIP001                      pDestNd->ResetAttr(RES_PARATR_NUMRULE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( aRg.aStart != aRg.aEnd )
//STRIP001      {
//STRIP001          SfxItemSet aBrkSet( pDoc->GetAttrPool(), aBreakSetRange );
//STRIP001          if( pSttNd && bCopyCollFmt && pDestNd->GetpSwAttrSet() )
//STRIP001          {
//STRIP001              aBrkSet.Put( *pDestNd->GetpSwAttrSet() );
//STRIP001              if( SFX_ITEM_SET == aBrkSet.GetItemState( RES_BREAK, FALSE ) )
//STRIP001                  pDestNd->ResetAttr( RES_BREAK );
//STRIP001              if( SFX_ITEM_SET == aBrkSet.GetItemState( RES_PAGEDESC, FALSE ) )
//STRIP001                  pDestNd->ResetAttr( RES_PAGEDESC );
//STRIP001          }
//STRIP001
//STRIP001          if( aInsPos == pEnd->nNode )
//STRIP001          {
//STRIP001              SwNodeIndex aSaveIdx( aInsPos, -1 );
//STRIP001              CopyWithFlyInFly( aRg, aInsPos, bMakeNewFrms, FALSE );
//STRIP001              aSaveIdx++;
//STRIP001              pEnd->nNode = aSaveIdx;
//STRIP001              pEnd->nContent.Assign( aSaveIdx.GetNode().GetTxtNode(), 0 );
//STRIP001          }
//STRIP001          else
//STRIP001              CopyWithFlyInFly( aRg, aInsPos, bMakeNewFrms, FALSE );
//STRIP001
//STRIP001          bCopyBookmarks = FALSE;
//STRIP001
//STRIP001          // harte Umbrueche wieder in den ersten Node setzen
//STRIP001          if( aBrkSet.Count() && 0 != ( pDestNd = pDoc->GetNodes()[
//STRIP001                  aCpyPam.GetPoint()->nNode.GetIndex()+1 ]->GetTxtNode() ) )
//STRIP001          {
//STRIP001              pDestNd->SwCntntNode::SetAttr( aBrkSet );
//STRIP001          }
//STRIP001      }
//STRIP001  } while( FALSE );
//STRIP001
//STRIP001  // Position ummelden ( falls verschoben / im anderen Node )
//STRIP001  rPos.nContent.Assign( rPos.nNode.GetNode().GetCntntNode(),
//STRIP001                          rPos.nContent.GetIndex() );
//STRIP001
//STRIP001  if( rPos.nNode != aInsPos )
//STRIP001  {
//STRIP001      aCpyPam.GetMark()->nNode = aInsPos;
//STRIP001      aCpyPam.GetMark()->nContent.Assign( aCpyPam.GetCntntNode(FALSE), 0 );
//STRIP001      rPos = *aCpyPam.GetMark();
//STRIP001  }
//STRIP001  else
//STRIP001      *aCpyPam.GetMark() = rPos;
//STRIP001
//STRIP001  aCpyPam.Move( fnMoveForward, bCanMoveBack ? fnGoCntnt : fnGoNode );
//STRIP001  aCpyPam.Exchange();
//STRIP001
//STRIP001  // dann kopiere noch alle Bookmarks
//STRIP001  if( bCopyBookmarks && GetBookmarks().Count() )
//STRIP001      lcl_CopyBookmarks( rPam, aCpyPam );
//STRIP001
//STRIP001  if( REDLINE_DELETE_REDLINES & eOld )
//STRIP001      lcl_DeleteRedlines( rPam, aCpyPam );
//STRIP001
//STRIP001  // falls Undo eingeschaltet ist, so speicher den eingefuegten Bereich
//STRIP001  if( pDoc->DoesUndo() )
//STRIP001      pUndo->SetInsertRange( aCpyPam, TRUE, bStartIsTxtNode );
//STRIP001
//STRIP001  if( pCpyRange )
//STRIP001  {
//STRIP001      pCpyRange->SetMark();
//STRIP001      *pCpyRange->GetPoint() = *aCpyPam.GetPoint();
//STRIP001      *pCpyRange->GetMark() = *aCpyPam.GetMark();
//STRIP001  }
//STRIP001  pDoc->SetRedlineMode_intern( eOld );
//STRIP001  pDoc->SetModified();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//  ----- Copy-Methode vom SwDoc - "kopiere Fly's in Fly's" ------

/*N*/ void SwDoc::CopyWithFlyInFly( const SwNodeRange& rRg,
/*N*/                           const SwNodeIndex& rInsPos, BOOL bMakeNewFrms,
/*N*/                           BOOL bDelRedlines, BOOL bCopyFlyAtFly ) const
/*N*/ {
/*N*/   SwDoc* pDest = rInsPos.GetNode().GetDoc();
/*N*/
/*N*/   _SaveRedlEndPosForRestore aRedlRest( rInsPos );
/*N*/
/*N*/   SwNodeIndex aSavePos( rInsPos, -1 );
/*N*/   BOOL bEndIsEqualEndPos = rInsPos == rRg.aEnd;
/*N*/   GetNodes()._CopyNodes( rRg, rInsPos, bMakeNewFrms, TRUE );
/*N*/   aSavePos++;
/*N*/   if( bEndIsEqualEndPos )
/*N*/       ((SwNodeIndex&)rRg.aEnd) = aSavePos;
/*N*/
/*N*/   aRedlRest.Restore();
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   {
/*N*/       //JP 17.06.99: Bug 66973 - check count only if the selection is in
/*N*/       //              the same (or no) section. Becaus not full selected
/*N*/       //              section are not copied.
/*N*/       const SwSectionNode* pSSectNd = rRg.aStart.GetNode().FindSectionNode();
/*N*/       SwNodeIndex aTmpI( rRg.aEnd, -1 );
/*N*/       const SwSectionNode* pESectNd = aTmpI.GetNode().FindSectionNode();
/*N*/       if( pSSectNd == pESectNd &&
/*N*/           !rRg.aStart.GetNode().IsSectionNode() &&
/*N*/           !aTmpI.GetNode().IsEndNode() )
/*N*/       {
/*N*/           ASSERT( rInsPos.GetIndex() - aSavePos.GetIndex() ==
/*N*/                   rRg.aEnd.GetIndex() - rRg.aStart.GetIndex(),
/*N*/                   "Es wurden zu wenig Nodes kopiert!" )
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   // Undo abschalten
/*N*/   BOOL bUndo = pDest->DoesUndo();
/*N*/   pDest->DoUndo( FALSE );
/*N*/   _CopyFlyInFly( rRg, aSavePos, bCopyFlyAtFly );
/*N*/   pDest->DoUndo( bUndo );
/*N*/
/*N*/   SwNodeRange aCpyRange( aSavePos, rInsPos );
/*N*/
/*N*/   // dann kopiere noch alle Bookmarks
/*N*/   if( GetBookmarks().Count() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SwPaM aRgTmp( rRg.aStart, rRg.aEnd );
//STRIP001 /*?*/        SwPaM aCpyTmp( aCpyRange.aStart, aCpyRange.aEnd );
//STRIP001 /*?*/
//STRIP001 /*?*/        lcl_CopyBookmarks( aRgTmp, aCpyTmp );
/*N*/   }
/*N*/
/*N*/   if( bDelRedlines && ( REDLINE_DELETE_REDLINES & pDest->GetRedlineMode() ))
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    lcl_DeleteRedlines( rRg, aCpyRange );
/*N*/
/*N*/   pDest->GetNodes()._DelDummyNodes( aCpyRange );
/*N*/ }

//STRIP001 void lcl_ChainFmts( SwFlyFrmFmt *pSrc, SwFlyFrmFmt *pDest )
//STRIP001 {
//STRIP001  SwFmtChain aSrc( pSrc->GetChain() );
//STRIP001  if ( !aSrc.GetNext() )
//STRIP001  {
//STRIP001      aSrc.SetNext( pDest );
//STRIP001      pSrc->SetAttr( aSrc );
//STRIP001  }
//STRIP001  SwFmtChain aDest( pDest->GetChain() );
//STRIP001  if ( !aDest.GetPrev() )
//STRIP001  {
//STRIP001      aDest.SetPrev( pSrc );
//STRIP001      pDest->SetAttr( aDest );
//STRIP001  }
//STRIP001 }

/*N*/ void SwDoc::_CopyFlyInFly( const SwNodeRange& rRg, const SwNodeIndex& rSttIdx,
/*N*/                           BOOL bCopyFlyAtFly ) const
/*N*/ {
/*N*/   // Bug 22727: suche erst mal alle Flys zusammen, sortiere sie entsprechend
/*N*/   //            ihrer Ordnungsnummer und kopiere sie erst dann. Damit wird
/*N*/   //            die Ordnungsnummer (wird nur im DrawModel verwaltet)
/*N*/   //            beibehalten.
/*N*/   SwDoc* pDest = rSttIdx.GetNode().GetDoc();
/*N*/   _ZSortFlys aArr;
/*N*/   USHORT nArrLen = GetSpzFrmFmts()->Count();
        USHORT n=0;
/*N*/   for( n = 0; n < nArrLen; ++n )
/*N*/   {
/*N*/       const SwFrmFmt* pFmt = (*GetSpzFrmFmts())[n];
/*N*/       const SwFmtAnchor* pAnchor = &pFmt->GetAnchor();
/*N*/       const SwPosition* pAPos;
/*N*/       if ( ( pAnchor->GetAnchorId() == FLY_AT_CNTNT ||
/*N*/              pAnchor->GetAnchorId() == FLY_AT_FLY ||
/*N*/              pAnchor->GetAnchorId() == FLY_AUTO_CNTNT ) &&
/*N*/            0 != ( pAPos = pAnchor->GetCntntAnchor()) &&
/*N*/            (( bCopyFlyAtFly && FLY_AT_FLY == pAnchor->GetAnchorId() )
/*N*/                   ? rRg.aStart <= pAPos->nNode.GetIndex() + 1
/*N*/                   : ( IsRedlineMove()
/*N*/                           ? rRg.aStart < pAPos->nNode
/*N*/                           : rRg.aStart <= pAPos->nNode )) &&
/*N*/            pAPos->nNode < rRg.aEnd )
/*N*/       {
/*N*/           aArr.Insert( _ZSortFly( pFmt, pAnchor, nArrLen + aArr.Count() ));
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //Alle kopierten (also die neu erzeugten) Rahmen in ein weiteres Array
/*N*/   //stopfen. Dort sizten sie passend zu den Originalen, damit hinterher
/*N*/   //die Chains entsprechend aufgebaut werden koennen.
/*N*/   SvPtrarr aNewArr( 10, 10 );
/*N*/
/*N*/   for( n = 0; n < aArr.Count(); ++n )
/*N*/   {
/*N*/       // neuen Anker anlegen
/*N*/       const _ZSortFly& rZSortFly = aArr[ n ];
/*N*/       SwFmtAnchor aAnchor( *rZSortFly.GetAnchor() );
/*N*/       SwPosition *pNewPos = (SwPosition*)aAnchor.GetCntntAnchor();
/*N*/       long nOffset = pNewPos->nNode.GetIndex() -
/*N*/                           rRg.aStart.GetIndex();
/*N*/       SwNodeIndex aIdx( rSttIdx, nOffset );
/*N*/       pNewPos->nNode = aIdx;
/*N*/       // die am Zeichen Flys wieder ans das vorgegebene Zeichen setzen
/*N*/       if( FLY_AUTO_CNTNT == aAnchor.GetAnchorId() &&
/*N*/           aIdx.GetNode().IsTxtNode() )
/*?*/           pNewPos->nContent.Assign( (SwTxtNode*)&aIdx.GetNode(),
/*?*/                                       pNewPos->nContent.GetIndex() );
/*N*/       else
/*N*/           pNewPos->nContent.Assign( 0, 0 );
/*N*/
/*N*/       // ueberpruefe Rekursion: Inhalt in "seinen eigenen" Frame
/*N*/       // kopieren. Dann nicht kopieren
/*N*/       FASTBOOL bMakeCpy = TRUE;
/*N*/       if( pDest == this )
/*N*/       {
/*N*/           const SwFmtCntnt& rCntnt = rZSortFly.GetFmt()->GetCntnt();
/*N*/           const SwStartNode* pSNd;
/*N*/           if( rCntnt.GetCntntIdx() &&
/*N*/               0 != ( pSNd = rCntnt.GetCntntIdx()->GetNode().GetStartNode() ) &&
/*N*/               pSNd->GetIndex() < rSttIdx.GetIndex() &&
/*N*/               rSttIdx.GetIndex() < pSNd->EndOfSectionIndex() )
/*N*/           {
/*?*/               bMakeCpy = FALSE;
/*?*/               aArr.Remove( n, 1 );
/*?*/               --n;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Format kopieren und den neuen Anker setzen
/*N*/       if( bMakeCpy )
/*N*/           aNewArr.Insert( pDest->CopyLayoutFmt( *rZSortFly.GetFmt(),
/*N*/                       aAnchor, FALSE, TRUE/*FALSE*/ ), aNewArr.Count() );
/*N*/   }
/*N*/
/*N*/   //Alle chains, die im Original vorhanden sind, soweit wie moeglich wieder
/*N*/   //aufbauen.
/*N*/   ASSERT( aArr.Count() == aNewArr.Count(), "Missing new Flys" );
/*N*/   if ( aArr.Count() == aNewArr.Count() )
/*N*/   {
/*N*/       for ( n = 0; n < aArr.Count(); ++n )
/*N*/       {
/*N*/           const SwFrmFmt *pFmt = aArr[n].GetFmt();
/*N*/           const SwFmtChain &rChain = pFmt->GetChain();
/*N*/           int nCnt = 0 != rChain.GetPrev();
/*N*/           nCnt += rChain.GetNext() ? 1: 0;
/*N*/           for ( USHORT k = 0; nCnt && k < aArr.Count(); ++k )
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 const _ZSortFly &rTmp = aArr[k];
//STRIP001 /*?*/                const SwFrmFmt *pTmp = rTmp.GetFmt();
//STRIP001 /*?*/                if ( rChain.GetPrev() == pTmp )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ::lcl_ChainFmts( (SwFlyFrmFmt*)aNewArr[k],
//STRIP001 /*?*/                                     (SwFlyFrmFmt*)aNewArr[n] );
//STRIP001 /*?*/                    --nCnt;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if ( rChain.GetNext() == pTmp )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ::lcl_ChainFmts( (SwFlyFrmFmt*)aNewArr[n],
//STRIP001 /*?*/                                     (SwFlyFrmFmt*)aNewArr[k] );
//STRIP001 /*?*/                    --nCnt;
//STRIP001 /*?*/                }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }




}
