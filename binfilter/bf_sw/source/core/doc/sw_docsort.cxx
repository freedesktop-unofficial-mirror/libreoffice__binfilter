/*************************************************************************
 *
 *  $RCSfile: sw_docsort.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:10:52 $
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

#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif
#ifndef _UNOTOOLS_COLLATORWRAPPER_HXX
#include <unotools/collatorwrapper.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_COLLATOROPTIONS_HPP_
#include <com/sun/star/i18n/CollatorOptions.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif

#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FMTANCHR_HXX
#include <fmtanchr.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _SORTOPT_HXX
#include <sortopt.hxx>
#endif
#ifndef _DOCSORT_HXX
#include <docsort.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#if OSL_DEBUG_LEVEL > 1
//nur zum debugen
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#endif

using namespace ::com::sun::star::lang;

//STRIP001 SwSortOptions*       SwSortElement::pOptions = 0;
//STRIP001 SwDoc*               SwSortElement::pDoc = 0;
//STRIP001 const FlatFndBox*    SwSortElement::pBox = 0;
//STRIP001 CollatorWrapper*     SwSortElement::pSortCollator = 0;
//STRIP001 Locale*          SwSortElement::pLocale = 0;
//STRIP001 String*          SwSortElement::pLastAlgorithm = 0;
//STRIP001 LocaleDataWrapper*   SwSortElement::pLclData = 0;

//STRIP001 SV_IMPL_OP_PTRARR_SORT( SwSortElements, SwSortElementPtr );


/*--------------------------------------------------------------------
    Beschreibung: Ein Sortierelement fuers Sort konstruieren
 --------------------------------------------------------------------*/


//STRIP001 void SwSortElement::Init( SwDoc* pD, const SwSortOptions& rOpt,
//STRIP001                          FlatFndBox* pFltBx )
//STRIP001 {
//STRIP001  ASSERT( !pDoc && !pOptions && !pBox, "wer hat das Finit vergessen?" );
//STRIP001  pDoc = pD;
//STRIP001  pOptions = new SwSortOptions( rOpt );
//STRIP001  pBox = pFltBx;
//STRIP001
//STRIP001  LanguageType nLang = rOpt.nLanguage;
//STRIP001  switch ( nLang )
//STRIP001  {
//STRIP001  case LANGUAGE_NONE:
//STRIP001  case LANGUAGE_DONTKNOW:
//STRIP001      nLang = (LanguageType)GetAppLanguage();
//STRIP001      break;
//STRIP001  }
//STRIP001  pLocale = new Locale( SvxCreateLocale( nLang ) );
//STRIP001
//STRIP001  pSortCollator = new CollatorWrapper(
//STRIP001                              ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001 //   pSortCollator->loadCollatorAlgorithm( sAlgorithm, aLocale,
//STRIP001 //                       rOpt.bIgnoreCase ? SW_COLLATOR_IGNORES : 0 );
//STRIP001 }


//STRIP001 void SwSortElement::Finit()
//STRIP001 {
//STRIP001  delete pOptions, pOptions = 0;
//STRIP001  delete pLocale, pLocale = 0;
//STRIP001  delete pLastAlgorithm, pLastAlgorithm = 0;
//STRIP001  delete pSortCollator, pSortCollator = 0;
//STRIP001  delete pLclData, pLclData = 0;
//STRIP001  pDoc = 0;
//STRIP001  pBox = 0;
//STRIP001 }


//STRIP001 SwSortElement::~SwSortElement()
//STRIP001 {
//STRIP001 }


//STRIP001 double SwSortElement::StrToDouble( const String& rStr ) const
//STRIP001 {
//STRIP001  if( !pLclData )
//STRIP001      pLclData = new LocaleDataWrapper(
//STRIP001                  ::legacy_binfilters::getLegacyProcessServiceFactory(), *pLocale );
//STRIP001
//STRIP001     rtl_math_ConversionStatus eStatus;
//STRIP001     sal_Int32 nEnd;
//STRIP001  double nRet = ::rtl::math::stringToDouble( rStr,
//STRIP001                                  pLclData->getNumDecimalSep().GetChar(0),
//STRIP001                                  pLclData->getNumThousandSep().GetChar(0),
//STRIP001                                  &eStatus, &nEnd );
//STRIP001
//STRIP001  if( rtl_math_ConversionStatus_Ok != eStatus || nEnd == 0 )
//STRIP001      nRet = 0.0;
//STRIP001  return nRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Operatoren zum Vergleichen
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwSortElement::operator==(const SwSortElement& rCmp)
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Kleiner-Operator fuers sortieren
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwSortElement::operator<(const SwSortElement& rCmp)
//STRIP001 {
//STRIP001
//STRIP001  // der eigentliche Vergleich
//STRIP001  //
//STRIP001  for(USHORT nKey = 0; nKey < pOptions->aKeys.Count(); ++nKey)
//STRIP001  {
//STRIP001      const SwSortElement *pOrig, *pCmp;
//STRIP001
//STRIP001      const SwSortKey* pSrtKey = pOptions->aKeys[ nKey ];
//STRIP001      if( pSrtKey->eSortOrder == SRT_ASCENDING )
//STRIP001          pOrig = this, pCmp = &rCmp;
//STRIP001      else
//STRIP001          pOrig = &rCmp, pCmp = this;
//STRIP001
//STRIP001      if( pSrtKey->bIsNumeric )
//STRIP001      {
//STRIP001          double n1 = pOrig->GetValue( nKey );
//STRIP001          double n2 = pCmp->GetValue( nKey );
//STRIP001
//STRIP001          if( n1 == n2 )
//STRIP001              continue;
//STRIP001
//STRIP001          return n1 < n2;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !pLastAlgorithm || *pLastAlgorithm != pSrtKey->sSortType )
//STRIP001          {
//STRIP001              if( pLastAlgorithm )
//STRIP001                  *pLastAlgorithm = pSrtKey->sSortType;
//STRIP001              else
//STRIP001                  pLastAlgorithm = new String( pSrtKey->sSortType );
//STRIP001              pSortCollator->loadCollatorAlgorithm( *pLastAlgorithm,
//STRIP001                      *pLocale,
//STRIP001                      pOptions->bIgnoreCase ? SW_COLLATOR_IGNORES : 0 );
//STRIP001          }
//STRIP001
//STRIP001          sal_Int32 nCmp = pSortCollator->compareString(
//STRIP001                      pOrig->GetKey( nKey ), pCmp->GetKey( nKey ));
//STRIP001          if( 0 == nCmp )
//STRIP001              continue;
//STRIP001
//STRIP001          return -1 == nCmp;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 double SwSortElement::GetValue( USHORT nKey ) const
//STRIP001 {
//STRIP001  return StrToDouble( GetKey( nKey ));
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: SortierElemente fuer Text
 --------------------------------------------------------------------*/


//STRIP001 SwSortTxtElement::SwSortTxtElement( const SwNodeIndex& rPos )
//STRIP001  : aPos( rPos ),
//STRIP001  nOrg( rPos.GetIndex() )
//STRIP001 {
//STRIP001 }


//STRIP001 SwSortTxtElement::~SwSortTxtElement()
//STRIP001 {
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: Key ermitteln
 --------------------------------------------------------------------*/


//STRIP001 String SwSortTxtElement::GetKey(USHORT nId) const
//STRIP001 {
//STRIP001  SwTxtNode* pTxtNd = aPos.GetNode().GetTxtNode();
//STRIP001  if( !pTxtNd )
//STRIP001      return aEmptyStr;
//STRIP001
//STRIP001  // fuer TextNodes
//STRIP001  const String& rStr = pTxtNd->GetTxt();
//STRIP001
//STRIP001  sal_Unicode nDeli = pOptions->cDeli;
//STRIP001  USHORT nDCount = pOptions->aKeys[nId]->nColumnId, i = 1;
//STRIP001  xub_StrLen nStart = 0;
//STRIP001
//STRIP001  // Den Delimitter suchen
//STRIP001  while( nStart != STRING_NOTFOUND && i < nDCount)
//STRIP001      if( STRING_NOTFOUND != ( nStart = rStr.Search( nDeli, nStart ) ) )
//STRIP001      {
//STRIP001          nStart++;
//STRIP001          i++;
//STRIP001      }
//STRIP001
//STRIP001  // naechsten Delimitter gefunden oder Ende des Strings und Kopieren
//STRIP001  xub_StrLen nEnd = rStr.Search( nDeli, nStart+1 );
//STRIP001  return rStr.Copy( nStart, nEnd-nStart );
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: Sortier-Elemente fuer Tabellen
 --------------------------------------------------------------------*/

//STRIP001 SwSortBoxElement::SwSortBoxElement( USHORT nRC )
//STRIP001  : nRow( nRC )
//STRIP001 {
//STRIP001 }


//STRIP001 SwSortBoxElement::~SwSortBoxElement()
//STRIP001 {
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Schluessel zu einer Zelle ermitteln
 --------------------------------------------------------------------*/


//STRIP001 String SwSortBoxElement::GetKey(USHORT nKey) const
//STRIP001 {
//STRIP001  const _FndBox* pFndBox;
//STRIP001  USHORT nCol = pOptions->aKeys[nKey]->nColumnId-1;
//STRIP001
//STRIP001  if( SRT_ROWS == pOptions->eDirection )
//STRIP001      pFndBox = pBox->GetBox(nCol, nRow);         // Zeilen sortieren
//STRIP001  else
//STRIP001      pFndBox = pBox->GetBox(nRow, nCol);         // Spalten sortieren
//STRIP001
//STRIP001  // Den Text rausfieseln
//STRIP001  String aRetStr;
//STRIP001  if( pFndBox )
//STRIP001  {   // StartNode holen und ueberlesen
//STRIP001      const SwTableBox* pBox = pFndBox->GetBox();
//STRIP001      ASSERT(pBox, "Keine atomare Box");
//STRIP001
//STRIP001      if( pBox->GetSttNd() )
//STRIP001      {
//STRIP001          // ueber alle TextNodes der Box
//STRIP001          const SwNode *pNd = 0, *pEndNd = pBox->GetSttNd()->EndOfSectionNode();
//STRIP001          for( ULONG nIdx = pBox->GetSttIdx() + 1; pNd != pEndNd; ++nIdx )
//STRIP001              if( ( pNd = pDoc->GetNodes()[ nIdx ])->IsTxtNode() )
//STRIP001                  aRetStr += ((SwTxtNode*)pNd)->GetTxt();
//STRIP001      }
//STRIP001  }
//STRIP001  return aRetStr;
//STRIP001 }

//STRIP001 double SwSortBoxElement::GetValue( USHORT nKey ) const
//STRIP001 {
//STRIP001  const _FndBox* pFndBox;
//STRIP001  USHORT nCol = pOptions->aKeys[nKey]->nColumnId-1;
//STRIP001
//STRIP001  if( SRT_ROWS == pOptions->eDirection )
//STRIP001      pFndBox = pBox->GetBox(nCol, nRow);         // Zeilen sortieren
//STRIP001  else
//STRIP001      pFndBox = pBox->GetBox(nRow, nCol);         // Spalten sortieren
//STRIP001
//STRIP001  double aVal;
//STRIP001  if( pFndBox )
//STRIP001      aVal = pFndBox->GetBox()->GetFrmFmt()->GetTblBoxValue().GetValue();
//STRIP001  else
//STRIP001      aVal = 0;
//STRIP001
//STRIP001  return aVal;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Text sortieren im Document
 --------------------------------------------------------------------*/


/*N*/ BOOL SwDoc::SortText(const SwPaM& rPaM, const SwSortOptions& rOpt)
/*N*/ {
/*N*/   DBG_ASSERT(0, "STRIP"); //STRIP001 // pruefen ob Rahmen im Text
//STRIP001  const SwPosition *pStart = rPaM.Start(), *pEnd = rPaM.End();
//STRIP001  // Index auf den Start der Selektion
//STRIP001
//STRIP001  SwFrmFmt* pFmt;
//STRIP001  const SwFmtAnchor* pAnchor;
//STRIP001  const SwPosition* pAPos;
//STRIP001
//STRIP001  for( USHORT n = 0; n < GetSpzFrmFmts()->Count(); ++n )
//STRIP001  {
//STRIP001      pFmt = (SwFrmFmt*)(*GetSpzFrmFmts())[n];
//STRIP001      pAnchor = &pFmt->GetAnchor();
//STRIP001
//STRIP001      if( FLY_AT_CNTNT == pAnchor->GetAnchorId() &&
//STRIP001          0 != (pAPos = pAnchor->GetCntntAnchor() ) &&
//STRIP001          pStart->nNode <= pAPos->nNode && pAPos->nNode <= pEnd->nNode )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  // pruefe ob nur TextNodes in der Selection liegen
//STRIP001  {
//STRIP001      register ULONG nStart = pStart->nNode.GetIndex(),
//STRIP001                      nEnd = pEnd->nNode.GetIndex();
//STRIP001      while( nStart <= nEnd )
//STRIP001          // Iterieren ueber einen selektierten Bereich
//STRIP001          if( !GetNodes()[ nStart++ ]->IsTxtNode() )
//STRIP001              return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bUndo = DoesUndo();
//STRIP001  if( bUndo )
//STRIP001      StartUndo( UNDO_START );
//STRIP001
//STRIP001  SwPaM* pRedlPam = 0;
//STRIP001  SwUndoRedlineSort* pRedlUndo = 0;
//STRIP001  SwUndoSort* pUndoSort = 0;
//STRIP001
//STRIP001  if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
//STRIP001  {
//STRIP001      pRedlPam = new SwPaM( pStart->nNode, pEnd->nNode, -1, 1 );
//STRIP001      SwCntntNode* pCNd = pRedlPam->GetCntntNode( FALSE );
//STRIP001      if( pCNd )
//STRIP001          pRedlPam->GetMark()->nContent = pCNd->Len();
//STRIP001
//STRIP001      if( IsRedlineOn() && !IsShowOriginal( GetRedlineMode() ) )
//STRIP001      {
//STRIP001          if( bUndo )
//STRIP001          {
//STRIP001              pRedlUndo = new SwUndoRedlineSort( rPaM, rOpt );
//STRIP001              DoUndo( FALSE );
//STRIP001          }
//STRIP001          // erst den Bereich kopieren, dann
//STRIP001          SwNodeIndex aEndIdx( pEnd->nNode, 1 );
//STRIP001          SwNodeRange aRg( pStart->nNode, aEndIdx );
//STRIP001          GetNodes()._Copy( aRg, aEndIdx );
//STRIP001
//STRIP001          // Bereich neu ist von pEnd->nNode+1 bis aEndIdx
//STRIP001          DeleteRedline( *pRedlPam );
//STRIP001
//STRIP001          pRedlPam->GetMark()->nNode.Assign( pEnd->nNode.GetNode(), 1 );
//STRIP001          pCNd = pRedlPam->GetCntntNode( FALSE );
//STRIP001          pRedlPam->GetMark()->nContent.Assign( pCNd, 0 );
//STRIP001
//STRIP001          pRedlPam->GetPoint()->nNode.Assign( aEndIdx.GetNode() );
//STRIP001          pCNd = pRedlPam->GetCntntNode( TRUE );
//STRIP001          xub_StrLen nCLen = 0;
//STRIP001          if( !pCNd &&
//STRIP001              0 != (pCNd = GetNodes()[ aEndIdx.GetIndex()-1 ]->GetCntntNode()))
//STRIP001          {
//STRIP001              nCLen = pCNd->Len();
//STRIP001              pRedlPam->GetPoint()->nNode.Assign( *pCNd );
//STRIP001          }
//STRIP001          pRedlPam->GetPoint()->nContent.Assign( pCNd, nCLen );
//STRIP001
//STRIP001          if( pRedlUndo )
//STRIP001              pRedlUndo->SetValues( rPaM );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          DeleteRedline( *pRedlPam );
//STRIP001          delete pRedlPam, pRedlPam = 0;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SwNodeIndex aStart(pStart->nNode);
//STRIP001  SwSortElement::Init( this, rOpt );
//STRIP001  SwSortElements aSortArr;
//STRIP001  while( aStart <= pEnd->nNode )
//STRIP001  {
//STRIP001      // Iterieren ueber einen selektierten Bereich
//STRIP001      SwSortTxtElement* pSE = new SwSortTxtElement( aStart );
//STRIP001      aSortArr.Insert(pSE);
//STRIP001      aStart++;
//STRIP001  }
//STRIP001
//STRIP001  // Und jetzt der Akt: Verschieben von Nodes und immer schoen auf UNDO
//STRIP001  // achten
//STRIP001  //
//STRIP001  ULONG nBeg = pStart->nNode.GetIndex(), nEnd = aStart.GetIndex();
//STRIP001  SwNodeRange aRg( aStart, aStart );
//STRIP001
//STRIP001  if( bUndo && !pRedlUndo )
//STRIP001      AppendUndo( pUndoSort = new SwUndoSort( rPaM, rOpt ) );
//STRIP001
//STRIP001  DoUndo( FALSE );
//STRIP001
//STRIP001  for( n = 0; n < aSortArr.Count(); ++n )
//STRIP001  {
//STRIP001      SwSortTxtElement* pBox = (SwSortTxtElement*)aSortArr[n];
//STRIP001      aStart      = nBeg + n;
//STRIP001      aRg.aStart  = pBox->aPos.GetIndex();
//STRIP001      aRg.aEnd    = aRg.aStart.GetIndex() + 1;
//STRIP001
//STRIP001      // Nodes verschieben
//STRIP001      Move( aRg, aStart );
//STRIP001
//STRIP001      // Undo Verschiebungen einpflegen
//STRIP001      if(pUndoSort)
//STRIP001          pUndoSort->Insert(pBox->nOrg, nBeg + n);
//STRIP001  }
//STRIP001  // Alle Elemente aus dem SortArray loeschen
//STRIP001  aSortArr.DeleteAndDestroy(0, aSortArr.Count());
//STRIP001  SwSortElement::Finit();
//STRIP001
//STRIP001  if( pRedlPam )
//STRIP001  {
//STRIP001      if( pRedlUndo )
//STRIP001      {
//STRIP001          pRedlUndo->SetSaveRange( *pRedlPam );
//STRIP001          AppendUndo( pRedlUndo );
//STRIP001      }
//STRIP001
//STRIP001      // nBeg ist der Start vom sortierten Bereich
//STRIP001      SwNodeIndex aSttIdx( GetNodes(), nBeg );
//STRIP001
//STRIP001      // der Kopierte Bereich ist das Geloeschte
//STRIP001      AppendRedline( new SwRedline( REDLINE_DELETE, *pRedlPam ));
//STRIP001
//STRIP001      // das sortierte ist das Eingefuegte
//STRIP001      pRedlPam->GetPoint()->nNode = aSttIdx;
//STRIP001      SwCntntNode* pCNd = aSttIdx.GetNode().GetCntntNode();
//STRIP001      pRedlPam->GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001
//STRIP001      AppendRedline( new SwRedline( REDLINE_INSERT, *pRedlPam ));
//STRIP001
//STRIP001      if( pRedlUndo )
//STRIP001          pRedlUndo->SetOffset( aSttIdx );
//STRIP001
//STRIP001      delete pRedlPam, pRedlPam = 0;
//STRIP001  }
//STRIP001  DoUndo( bUndo );
//STRIP001  if( bUndo )
//STRIP001      EndUndo( UNDO_END );
//STRIP001
/*N*/  return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Tabelle sortieren im Document
 --------------------------------------------------------------------*/

/*N*/ BOOL SwDoc::SortTbl(const SwSelBoxes& rBoxes, const SwSortOptions& rOpt)
/*N*/ {
/*N*/   DBG_ASSERT(0, "STRIP"); //STRIP001 // uebers SwDoc fuer Undo !!
//STRIP001  ASSERT( rBoxes.Count(), "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // Auf gehts sortieren
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      pTblNd->GetTable().GetTabLines().ForEach( &_FndLineCopyCol, &aPara );;
//STRIP001  }
//STRIP001
//STRIP001  if(!aFndBox.GetLines().Count())
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( !IsIgnoreRedline() && GetRedlineTbl().Count() )
//STRIP001      DeleteRedline( *pTblNd );
//STRIP001
//STRIP001  USHORT nStart = 0;
//STRIP001  if(pTblNd->GetTable().IsHeadlineRepeat() && rOpt.eDirection == SRT_ROWS)
//STRIP001  {
//STRIP001      // Das ist die Kopfzeile
//STRIP001      SwTableLine * pHeadLine = pTblNd->GetTable().GetTabLines()[0];
//STRIP001
//STRIP001      // Oberste seleketierte Zeile
//STRIP001      _FndLines& rLines = aFndBox.GetLines();
//STRIP001
//STRIP001      while(nStart < rLines.Count() )
//STRIP001      {
//STRIP001          // Verschachtelung durch Split Merge beachten,
//STRIP001          // die oberste rausholen
//STRIP001          SwTableLine* pLine = rLines[nStart]->GetLine();
//STRIP001          while ( pLine->GetUpper() )
//STRIP001              pLine = pLine->GetUpper()->GetUpper();
//STRIP001
//STRIP001          if( pLine == pHeadLine)
//STRIP001              nStart++;
//STRIP001          else
//STRIP001              break;
//STRIP001      }
//STRIP001      // Alle selektierten in der HeaderLine ?  -> kein Offset
//STRIP001      if(nStart == rLines.Count())
//STRIP001          nStart = 0;
//STRIP001  }
//STRIP001
//STRIP001  // umschalten auf relative Formeln
//STRIP001  SwTableFmlUpdate aMsgHnt( &pTblNd->GetTable() );
//STRIP001  aMsgHnt.eFlags = TBL_RELBOXNAME;
//STRIP001  UpdateTblFlds( &aMsgHnt );
//STRIP001
//STRIP001  // Tabelle als flache Array-Struktur
//STRIP001  FlatFndBox aFlatBox(this, aFndBox);
//STRIP001
//STRIP001  if(!aFlatBox.IsSymmetric())
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // MIB 9.7.97: HTML-Layout loeschen
//STRIP001  pTblNd->GetTable().SetHTMLTableLayout( 0 );
//STRIP001
//STRIP001  // loesche die Frames der Tabelle
//STRIP001  pTblNd->DelFrms();
//STRIP001  // und dann noch fuers Chart die Daten sichern
//STRIP001  aFndBox.SaveChartData( pTblNd->GetTable() );
//STRIP001
//STRIP001  // Redo loeschen bevor Undo
//STRIP001  BOOL bUndo = DoesUndo();
//STRIP001  SwUndoSort* pUndoSort = 0;
//STRIP001  if(bUndo)
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndoSort = new SwUndoSort( rBoxes[0]->GetSttIdx(),
//STRIP001                                  rBoxes[rBoxes.Count()-1]->GetSttIdx(),
//STRIP001                                 *pTblNd, rOpt, aFlatBox.HasItemSets() );
//STRIP001      AppendUndo(pUndoSort);
//STRIP001      DoUndo(FALSE);
//STRIP001  }
//STRIP001
//STRIP001  // SchluesselElemente einsortieren
//STRIP001  USHORT nCount = (rOpt.eDirection == SRT_ROWS) ?
//STRIP001                  aFlatBox.GetRows() : aFlatBox.GetCols();
//STRIP001
//STRIP001  // SortList nach Schluessel sortieren
//STRIP001  SwSortElement::Init( this, rOpt, &aFlatBox );
//STRIP001  SwSortElements aSortList;
//STRIP001
//STRIP001  // wenn die HeaderLine wiederholt wird und die
//STRIP001  // Zeilen sortiert werden 1.Zeile nicht mitsortieren
//STRIP001
//STRIP001  for(USHORT i=nStart; i < nCount; ++i)
//STRIP001  {
//STRIP001      SwSortBoxElement* pEle = new SwSortBoxElement( i );
//STRIP001      aSortList.Insert(pEle);
//STRIP001  }
//STRIP001
//STRIP001  SwNodeIndex aBehindIdx( *pTblNd->EndOfSectionNode());
//STRIP001  GetNodes().GoNext( &aBehindIdx );           // Index in Cntnt, hinter der Tabelle
//STRIP001
//STRIP001  // nach Sortierung verschieben
//STRIP001  SwMovedBoxes aMovedList;
//STRIP001  for(i=0; i < aSortList.Count(); ++i)
//STRIP001  {
//STRIP001      SwSortBoxElement* pBox = (SwSortBoxElement*)aSortList[i];
//STRIP001      if(rOpt.eDirection == SRT_ROWS)
//STRIP001          MoveRow(this, aFlatBox, pBox->nRow, i + nStart, aMovedList, pUndoSort);
//STRIP001      else
//STRIP001          MoveCol(this, aFlatBox, pBox->nRow, i + nStart, aMovedList, pUndoSort);
//STRIP001  }
//STRIP001
//STRIP001  // Neue Frames erzeugen
//STRIP001  pTblNd->MakeFrms( &aBehindIdx );
//STRIP001  aFndBox.RestoreChartData( pTblNd->GetTable() );
//STRIP001
//STRIP001  // Alle Elemente aus dem SortArray loeschen
//STRIP001  aSortList.DeleteAndDestroy( 0, aSortList.Count() );
//STRIP001  SwSortElement::Finit();
//STRIP001
//STRIP001  // Undo wieder aktivieren
//STRIP001  DoUndo(bUndo);
//STRIP001
//STRIP001  SetModified();
/*N*/   return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Zeilenweise verschieben
 --------------------------------------------------------------------*/


//STRIP001 void MoveRow(SwDoc* pDoc, const FlatFndBox& rBox, USHORT nS, USHORT nT,
//STRIP001           SwMovedBoxes& rMovedList, SwUndoSort* pUD)
//STRIP001 {
//STRIP001  for( USHORT i=0; i < rBox.GetCols(); ++i )
//STRIP001  {   // Alte Zellen-Pos bestimmen und merken
//STRIP001      const _FndBox* pSource = rBox.GetBox(i, nS);
//STRIP001
//STRIP001      // neue Zellen-Pos
//STRIP001      const _FndBox* pTarget = rBox.GetBox(i, nT);
//STRIP001
//STRIP001      const SwTableBox* pT = pTarget->GetBox();
//STRIP001      const SwTableBox* pS = pSource->GetBox();
//STRIP001
//STRIP001      BOOL bMoved = rMovedList.GetPos(pT) != USHRT_MAX;
//STRIP001
//STRIP001      // und verschieben
//STRIP001      MoveCell(pDoc, pS, pT, bMoved, pUD);
//STRIP001
//STRIP001      rMovedList.Insert(pS, rMovedList.Count() );
//STRIP001
//STRIP001      if( pS != pT )
//STRIP001      {
//STRIP001          SwFrmFmt* pTFmt = (SwFrmFmt*)pT->GetFrmFmt();
//STRIP001          const SfxItemSet* pSSet = rBox.GetItemSet( i, nS );
//STRIP001
//STRIP001          if( pSSet ||
//STRIP001              SFX_ITEM_SET == pTFmt->GetItemState( RES_BOXATR_FORMAT ) ||
//STRIP001              SFX_ITEM_SET == pTFmt->GetItemState( RES_BOXATR_FORMULA ) ||
//STRIP001              SFX_ITEM_SET == pTFmt->GetItemState( RES_BOXATR_VALUE ) )
//STRIP001          {
//STRIP001              pTFmt = ((SwTableBox*)pT)->ClaimFrmFmt();
//STRIP001              pTFmt->LockModify();
//STRIP001              if( pTFmt->ResetAttr( RES_BOXATR_FORMAT, RES_BOXATR_VALUE ) )
//STRIP001                  pTFmt->ResetAttr( RES_VERT_ORIENT );
//STRIP001
//STRIP001              if( pSSet )
//STRIP001                  pTFmt->SetAttr( *pSSet );
//STRIP001              pTFmt->UnlockModify();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Spaltenweise verschieben
 --------------------------------------------------------------------*/


//STRIP001 void MoveCol(SwDoc* pDoc, const FlatFndBox& rBox, USHORT nS, USHORT nT,
//STRIP001           SwMovedBoxes& rMovedList, SwUndoSort* pUD)
//STRIP001 {
//STRIP001  for(USHORT i=0; i < rBox.GetRows(); ++i)
//STRIP001  {   // Alte Zellen-Pos bestimmen und merken
//STRIP001      const _FndBox* pSource = rBox.GetBox(nS, i);
//STRIP001
//STRIP001      // neue Zellen-Pos
//STRIP001      const _FndBox* pTarget = rBox.GetBox(nT, i);
//STRIP001
//STRIP001      // und verschieben
//STRIP001      const SwTableBox* pT = pTarget->GetBox();
//STRIP001      const SwTableBox* pS = pSource->GetBox();
//STRIP001
//STRIP001      // und verschieben
//STRIP001      BOOL bMoved = rMovedList.GetPos(pT) != USHRT_MAX;
//STRIP001      MoveCell(pDoc, pS, pT, bMoved, pUD);
//STRIP001
//STRIP001      rMovedList.Insert(pS, rMovedList.Count() );
//STRIP001
//STRIP001      if( pS != pT )
//STRIP001      {
//STRIP001          SwFrmFmt* pTFmt = (SwFrmFmt*)pT->GetFrmFmt();
//STRIP001          const SfxItemSet* pSSet = rBox.GetItemSet( nS, i );
//STRIP001
//STRIP001          if( pSSet ||
//STRIP001              SFX_ITEM_SET == pTFmt->GetItemState( RES_BOXATR_FORMAT ) ||
//STRIP001              SFX_ITEM_SET == pTFmt->GetItemState( RES_BOXATR_FORMULA ) ||
//STRIP001              SFX_ITEM_SET == pTFmt->GetItemState( RES_BOXATR_VALUE ) )
//STRIP001          {
//STRIP001              pTFmt = ((SwTableBox*)pT)->ClaimFrmFmt();
//STRIP001              pTFmt->LockModify();
//STRIP001              if( pTFmt->ResetAttr( RES_BOXATR_FORMAT, RES_BOXATR_VALUE ) )
//STRIP001                  pTFmt->ResetAttr( RES_VERT_ORIENT );
//STRIP001
//STRIP001              if( pSSet )
//STRIP001                  pTFmt->SetAttr( *pSSet );
//STRIP001              pTFmt->UnlockModify();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Eine einzelne Zelle verschieben
 --------------------------------------------------------------------*/


//STRIP001 void MoveCell(SwDoc* pDoc, const SwTableBox* pSource, const SwTableBox* pTar,
//STRIP001            BOOL bMovedBefore, SwUndoSort* pUD)
//STRIP001 {
//STRIP001  ASSERT(pSource && pTar,"Fehlende Quelle oder Ziel");
//STRIP001
//STRIP001  if(pSource == pTar)
//STRIP001      return;
//STRIP001
//STRIP001  if(pUD)
//STRIP001      pUD->Insert( pSource->GetName(), pTar->GetName() );
//STRIP001
//STRIP001  // Pam Quelle auf den ersten ContentNode setzen
//STRIP001  SwNodeRange aRg( *pSource->GetSttNd(), 0, *pSource->GetSttNd() );
//STRIP001  SwNode* pNd = pDoc->GetNodes().GoNext( &aRg.aStart );
//STRIP001
//STRIP001  // wurde die Zelle (Source) nicht verschoben
//STRIP001  // -> einen Leer-Node einfuegen und den Rest verschieben
//STRIP001  // ansonsten steht der Mark auf dem ersten Content-Node
//STRIP001  if( pNd->StartOfSectionNode() == pSource->GetSttNd() )
//STRIP001      pNd = pDoc->GetNodes().MakeTxtNode( aRg.aStart,
//STRIP001              (SwTxtFmtColl*)pDoc->GetDfltTxtFmtColl() );
//STRIP001  aRg.aEnd = *pNd->EndOfSectionNode();
//STRIP001
//STRIP001  // Ist das Ziel leer(1 leerer Node vorhanden)
//STRIP001  // -> diesen loeschen und move
//STRIP001  // Ziel
//STRIP001  SwNodeIndex aTar( *pTar->GetSttNd() );
//STRIP001  pNd = pDoc->GetNodes().GoNext( &aTar );     // naechsten ContentNode
//STRIP001  ULONG nCount = pNd->EndOfSectionIndex() - pNd->StartOfSectionIndex();
//STRIP001
//STRIP001  BOOL bDelFirst = FALSE;
//STRIP001  if( nCount == 2 )
//STRIP001  {
//STRIP001      ASSERT( pNd->GetCntntNode(), "Kein ContentNode");
//STRIP001      bDelFirst = !pNd->GetCntntNode()->Len() && bMovedBefore;
//STRIP001  }
//STRIP001
//STRIP001  if(!bDelFirst)
//STRIP001  {   // Es besteht schon Inhalt -> alter I n h a l t  Section Down
//STRIP001      SwNodeRange aRgTar( aTar.GetNode(), 0, *pNd->EndOfSectionNode() );
//STRIP001      pDoc->GetNodes().SectionDown( &aRgTar );
//STRIP001  }
//STRIP001
//STRIP001  // Einfuegen der Source
//STRIP001  SwNodeIndex aIns( *pTar->GetSttNd()->EndOfSectionNode() );
//STRIP001  pDoc->Move( aRg, aIns );
//STRIP001
//STRIP001  // Falls erster Node leer -> weg damit
//STRIP001  if(bDelFirst)
//STRIP001      pDoc->GetNodes().Delete( aTar, 1 );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Zweidimensionales Array aus FndBoxes generieren
 --------------------------------------------------------------------*/


//STRIP001 FlatFndBox::FlatFndBox(SwDoc* pDocPtr, const _FndBox& rBox) :
//STRIP001  pDoc(pDocPtr),
//STRIP001  pArr(0),
//STRIP001  ppItemSets( 0 ),
//STRIP001  rBoxRef(rBox),
//STRIP001  nRow(0),
//STRIP001  nCol(0)
//STRIP001 { // Ist das Array symmetrisch
//STRIP001  if((bSym = CheckLineSymmetry(rBoxRef)) != 0)
//STRIP001  {
//STRIP001      // Spalten/Reihen-Anzahl ermitteln
//STRIP001      nCols = GetColCount(rBoxRef);
//STRIP001      nRows = GetRowCount(rBoxRef);
//STRIP001
//STRIP001      // lineares Array anlegen
//STRIP001      pArr = new _FndBoxPtr[ nRows * nCols ];
//STRIP001      _FndBox** ppTmp = (_FndBox**)pArr;
//STRIP001      memset( ppTmp, 0, sizeof(_FndBoxPtr) * nRows * nCols );
//STRIP001
//STRIP001
//STRIP001      FillFlat( rBoxRef );
//STRIP001  }
//STRIP001 }


//STRIP001 FlatFndBox::~FlatFndBox()
//STRIP001 {
//STRIP001  _FndBox** ppTmp = (_FndBox**)pArr;
//STRIP001  __DELETE(nRows * nCols * sizeof(_FndBoxPtr)) ppTmp;
//STRIP001
//STRIP001  if( ppItemSets )
//STRIP001      __DELETE(nRows * nCols * sizeof(SfxItemSet*)) ppItemSets;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Alle Lines einer Box muessen gleichviel Boxen haben
 --------------------------------------------------------------------*/


//STRIP001 BOOL FlatFndBox::CheckLineSymmetry(const _FndBox& rBox)
//STRIP001 {
//STRIP001  const _FndLines&    rLines = rBox.GetLines();
//STRIP001  USHORT              nBoxes;
//STRIP001
//STRIP001  // UeberLines iterieren
//STRIP001  for(USHORT i=0; i < rLines.Count(); ++i)
//STRIP001  {   // Die Boxen einer Line
//STRIP001      _FndLine* pLn = rLines[i];
//STRIP001      const _FndBoxes& rBoxes = pLn->GetBoxes();
//STRIP001
//STRIP001      // Anzahl der Boxen aller Lines ungleich -> keine Symmetrie
//STRIP001      if( i  && nBoxes != rBoxes.Count())
//STRIP001          return FALSE;
//STRIP001
//STRIP001      nBoxes = rBoxes.Count();
//STRIP001      if( !CheckBoxSymmetry( *pLn ) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Box auf Symmetrie pruefen
                    Alle Boxen einer Line muessen gleichviele Lines haben
 --------------------------------------------------------------------*/


//STRIP001 BOOL FlatFndBox::CheckBoxSymmetry(const _FndLine& rLn)
//STRIP001 {
//STRIP001  const _FndBoxes&    rBoxes = rLn.GetBoxes();
//STRIP001  USHORT              nLines;
//STRIP001
//STRIP001  // Ueber Boxes iterieren
//STRIP001  for(USHORT i=0; i < rBoxes.Count(); ++i)
//STRIP001  {   // Die Boxen einer Line
//STRIP001      _FndBox* pBox = rBoxes[i];
//STRIP001      const _FndLines& rLines = pBox->GetLines();
//STRIP001
//STRIP001      // Anzahl der Boxen aller Lines ungleich -> keine Symmetrie
//STRIP001      if( i && nLines != rLines.Count() )
//STRIP001          return FALSE;
//STRIP001
//STRIP001      nLines = rLines.Count();
//STRIP001      if( nLines && !CheckLineSymmetry( *pBox ) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: max Anzahl der Spalten (Boxes)
 --------------------------------------------------------------------*/


//STRIP001 USHORT FlatFndBox::GetColCount(const _FndBox& rBox)
//STRIP001 {
//STRIP001  const _FndLines& rLines = rBox.GetLines();
//STRIP001  // Ueber Lines iterieren
//STRIP001  if( !rLines.Count() )
//STRIP001      return 1;
//STRIP001
//STRIP001  USHORT nSum = 0;
//STRIP001  for( USHORT i=0; i < rLines.Count(); ++i )
//STRIP001  {
//STRIP001      // Die Boxen einer Line
//STRIP001      USHORT nCount = 0;
//STRIP001      const _FndBoxes& rBoxes = rLines[i]->GetBoxes();
//STRIP001      for( USHORT j=0; j < rBoxes.Count(); ++j )
//STRIP001              //  Rekursiv wirder ueber die Lines Iterieren
//STRIP001          nCount += rBoxes[j]->GetLines().Count()
//STRIP001                      ? GetColCount(*rBoxes[j]) : 1;
//STRIP001
//STRIP001      if( nSum < nCount )
//STRIP001          nSum = nCount;
//STRIP001  }
//STRIP001  return nSum;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: max Anzahl der Zeilen (Lines)
 --------------------------------------------------------------------*/


//STRIP001 USHORT FlatFndBox::GetRowCount(const _FndBox& rBox)
//STRIP001 {
//STRIP001  const _FndLines& rLines = rBox.GetLines();
//STRIP001  if( !rLines.Count() )
//STRIP001      return 1;
//STRIP001
//STRIP001  USHORT nLines = 0;
//STRIP001  for(USHORT i=0; i < rLines.Count(); ++i)
//STRIP001  {   // Die Boxen einer Line
//STRIP001      const _FndBoxes& rBoxes = rLines[i]->GetBoxes();
//STRIP001      USHORT nLn = 1;
//STRIP001      for(USHORT j=0; j < rBoxes.Count(); ++j)
//STRIP001          if( rBoxes[j]->GetLines().Count() )
//STRIP001              //  Rekursiv ueber die Lines Iterieren
//STRIP001              nLn = Max(GetRowCount(*rBoxes[j]), nLn);
//STRIP001
//STRIP001      nLines += nLn;
//STRIP001  }
//STRIP001  return nLines;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: lineares Array aus atomaren FndBoxes erzeugen
 --------------------------------------------------------------------*/


//STRIP001 void FlatFndBox::FillFlat(const _FndBox& rBox, BOOL bLastBox)
//STRIP001 {
//STRIP001  BOOL bModRow = FALSE;
//STRIP001  const _FndLines& rLines = rBox.GetLines();
//STRIP001
//STRIP001  // Ueber Lines iterieren
//STRIP001  USHORT nOldRow = nRow;
//STRIP001  for( USHORT i=0; i < rLines.Count(); ++i )
//STRIP001  {
//STRIP001      // Die Boxen einer Line
//STRIP001      const _FndBoxes& rBoxes = rLines[i]->GetBoxes();
//STRIP001      USHORT nOldCol = nCol;
//STRIP001      for( USHORT j = 0; j < rBoxes.Count(); ++j )
//STRIP001      {
//STRIP001          // Die Box pruefen ob es eine atomare Box ist
//STRIP001          const _FndBox*   pBox   = rBoxes[ j ];
//STRIP001
//STRIP001          if( !pBox->GetLines().Count() )
//STRIP001          {
//STRIP001              // peichern
//STRIP001              USHORT nOff = nRow * nCols + nCol;
//STRIP001              *(pArr + nOff) = pBox;
//STRIP001
//STRIP001              // sicher die Formel/Format/Value Werte
//STRIP001              const SwFrmFmt* pFmt = pBox->GetBox()->GetFrmFmt();
//STRIP001              if( SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_FORMAT ) ||
//STRIP001                  SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_FORMULA ) ||
//STRIP001                  SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_VALUE ) )
//STRIP001              {
//STRIP001                  SfxItemSet* pSet = new SfxItemSet( pDoc->GetAttrPool(),
//STRIP001                                  RES_BOXATR_FORMAT, RES_BOXATR_VALUE,
//STRIP001                                  RES_VERT_ORIENT, RES_VERT_ORIENT, 0 );
//STRIP001                  pSet->Put( pFmt->GetAttrSet() );
//STRIP001                  if( !ppItemSets )
//STRIP001                  {
//STRIP001                      ppItemSets = new SfxItemSet*[ nRows * nCols ];
//STRIP001                      memset( ppItemSets, 0, sizeof(SfxItemSet*) * nRows * nCols );
//STRIP001                  }
//STRIP001                  *(ppItemSets + nOff ) = pSet;
//STRIP001              }
//STRIP001
//STRIP001              bModRow = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Rekursiv wieder ueber die Lines einer Box Iterieren
//STRIP001              FillFlat( *pBox, ( j == rBoxes.Count()-1 ) );
//STRIP001          }
//STRIP001          nCol++;
//STRIP001      }
//STRIP001      if(bModRow)
//STRIP001          nRow++;
//STRIP001      nCol = nOldCol;
//STRIP001  }
//STRIP001  if(!bLastBox)
//STRIP001      nRow = nOldRow;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Zugriff auf eine bestimmte Zelle
 --------------------------------------------------------------------*/


//STRIP001 const _FndBox* FlatFndBox::GetBox(USHORT nCol, USHORT nRow) const
//STRIP001 {
//STRIP001  USHORT nOff = nRow * nCols + nCol;
//STRIP001  const _FndBox* pTmp = *(pArr + nOff);
//STRIP001
//STRIP001  ASSERT(nCol < nCols && nRow < nRows && pTmp, "unzulaessiger Array-Zugriff");
//STRIP001  return pTmp;
//STRIP001 }

//STRIP001 const SfxItemSet* FlatFndBox::GetItemSet(USHORT nCol, USHORT nRow) const
//STRIP001 {
//STRIP001  ASSERT( !ppItemSets || ( nCol < nCols && nRow < nRows), "unzulaessiger Array-Zugriff");
//STRIP001
//STRIP001  return ppItemSets ? *(ppItemSets + (nRow * nCols + nCol )) : 0;
//STRIP001 }


