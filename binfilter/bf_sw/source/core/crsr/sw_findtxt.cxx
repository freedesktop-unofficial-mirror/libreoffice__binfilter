/*************************************************************************
 *
 *  $RCSfile: sw_findtxt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:08:46 $
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

#ifndef _COM_SUN_STAR_UTIL_SEARCHOPTIONS_HPP_
#include <com/sun/star/util/SearchOptions.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SEARCHFLAGS_HPP_
#include <com/sun/star/util/SearchFlags.hpp>
#endif


#pragma hdrstop

#define _SVSTDARR_ULONGS
#include <svtools/svstdarr.hxx>

#ifndef _SV_SVAPP_HXX //autogen wg. Application
#include <vcl/svapp.hxx>
#endif

#ifndef _TXATRITR_HXX
#include <txatritr.hxx>
#endif
#ifndef _FLDBAS_HXX //autogen
#include <fldbas.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTATR_HXX //autogen
#include <txtatr.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif

using namespace com::sun::star;
using namespace com::sun::star::util;


//STRIP001 String& lcl_CleanStr( const SwTxtNode& rNd, xub_StrLen nStart,
//STRIP001                      xub_StrLen& rEnde, SvULongs& rArr, String& rRet )
//STRIP001 {
//STRIP001  rRet = rNd.GetTxt();
//STRIP001  if( rArr.Count() )
//STRIP001      rArr.Remove( 0, rArr.Count() );
//STRIP001
//STRIP001  const SwpHints *pHts = rNd.GetpSwpHints();
//STRIP001  if( pHts )
//STRIP001  {
//STRIP001      SvULongs aReplaced;
//STRIP001
//STRIP001      for( USHORT n = 0; n < pHts->Count(); ++n )
//STRIP001      {
//STRIP001          const SwTxtAttr *pHt = (*pHts)[n];
//STRIP001
//STRIP001          if( pHt->GetEnd() )         // nur Attribute ohne Ende
//STRIP001              continue;
//STRIP001
//STRIP001          register xub_StrLen nStt = *pHt->GetStart();
//STRIP001          if(  nStt < nStart )
//STRIP001              continue;
//STRIP001
//STRIP001          const xub_StrLen nAkt = nStt - rArr.Count();
//STRIP001
//STRIP001          //JP 17.05.00: Task 75806 ask for ">=" and not for ">"
//STRIP001          if( nAkt >= rEnde )         // uebers Ende hinaus =
//STRIP001              break;                  // das wars
//STRIP001
//STRIP001          switch( pHt->Which() )
//STRIP001          {
//STRIP001          case RES_TXTATR_FLYCNT:
//STRIP001          case RES_TXTATR_FTN:
//STRIP001          case RES_TXTATR_FIELD:
//STRIP001          case RES_TXTATR_REFMARK:
//STRIP001          case RES_TXTATR_TOXMARK:
//STRIP001              {
//STRIP001 // JP 06.05.98: mit Bug 50100 werden sie als Trenner erwuenscht und nicht
//STRIP001 //               mehr zum Wort dazu gehoerend.
//STRIP001 // MA 23.06.98: mit Bug 51215 sollen sie konsequenterweise auch am
//STRIP001 //               Satzanfang und -ende ignoriert werden wenn sie Leer sind.
//STRIP001 //               Dazu werden sie schlicht entfernt. Fuer den Anfang entfernen
//STRIP001 //               wir sie einfach.
//STRIP001 //               Fuer das Ende merken wir uns die Ersetzungen und entferenen
//STRIP001 //               hinterher alle am Stringende (koenten ja 'normale' 0x7f drinstehen
//STRIP001                  BOOL bEmpty = RES_TXTATR_FIELD != pHt->Which() ||
//STRIP001                      !((SwTxtFld*)pHt)->GetFld().GetFld()->Expand().Len();
//STRIP001                  if ( bEmpty && nStart == nAkt )
//STRIP001                  {
//STRIP001                      rArr.Insert( nAkt, rArr.Count() );
//STRIP001                      --rEnde;
//STRIP001                      rRet.Erase( nAkt, 1 );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if ( bEmpty )
//STRIP001                          aReplaced.Insert( nAkt, aReplaced.Count() );
//STRIP001                      rRet.SetChar( nAkt, '\x7f' );
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case RES_TXTATR_HARDBLANK:
//STRIP001                  rRet.SetChar( nAkt, ((SwTxtHardBlank*)pHt)->GetChar() );
//STRIP001                  break;
//STRIP001              default:
//STRIP001                  {
//STRIP001                      rArr.Insert( nAkt, rArr.Count() );
//STRIP001                      --rEnde;
//STRIP001                      rRet.Erase( nAkt, 1 );
//STRIP001                  }
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001      for( USHORT i = aReplaced.Count(); i; )
//STRIP001      {
//STRIP001          const xub_StrLen nTmp = aReplaced[ --i ];
//STRIP001          if( nTmp == rRet.Len()-1 )
//STRIP001          {
//STRIP001              rRet.Erase( nTmp );
//STRIP001              rArr.Insert( nTmp, rArr.Count() );
//STRIP001              --rEnde;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return rRet;
//STRIP001 }



//STRIP001 BYTE SwPaM::Find( const SearchOptions& rSearchOpt, utl::TextSearch& rSTxt,
//STRIP001                  SwMoveFn fnMove, const SwPaM * pRegion,
//STRIP001                  FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  if( !rSearchOpt.searchString.getLength() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwPaM* pPam = MakeRegion( fnMove, pRegion );
//STRIP001  FASTBOOL bSrchForward = fnMove == fnMoveForward;
//STRIP001  SwNodeIndex& rNdIdx = pPam->GetPoint()->nNode;
//STRIP001  SwIndex& rCntntIdx = pPam->GetPoint()->nContent;
//STRIP001
//STRIP001  // Wenn am Anfang/Ende, aus dem Node moven
//STRIP001  // beim leeren Node nicht weiter
//STRIP001  if( bSrchForward
//STRIP001      ? ( rCntntIdx.GetIndex() == pPam->GetCntntNode()->Len() &&
//STRIP001          rCntntIdx.GetIndex() )
//STRIP001      : !rCntntIdx.GetIndex() && pPam->GetCntntNode()->Len() )
//STRIP001  {
//STRIP001      if( !(*fnMove->fnNds)( &rNdIdx, FALSE ))
//STRIP001         {
//STRIP001          delete pPam;
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      SwCntntNode *pNd = rNdIdx.GetNode().GetCntntNode();
//STRIP001      xub_StrLen nTmpPos = bSrchForward ? 0 : pNd->Len();
//STRIP001      rCntntIdx.Assign( pNd, nTmpPos );
//STRIP001  }
//STRIP001
//STRIP001  /*
//STRIP001   * Ist bFound == TRUE, dann wurde der String gefunden und in
//STRIP001   * nStart und nEnde steht der gefundenen String
//STRIP001   */
//STRIP001  BOOL bFound = FALSE;
//STRIP001  /*
//STRIP001   * StartPostion im Text oder Anfangsposition
//STRIP001   */
//STRIP001  FASTBOOL bFirst = TRUE;
//STRIP001  SwCntntNode * pNode;
//STRIP001  String sCleanStr;
//STRIP001  SvULongs aFltArr;
//STRIP001
//STRIP001  xub_StrLen nStart, nEnde, nTxtLen;
//STRIP001  const SwNode* pSttNd = &rNdIdx.GetNode();
//STRIP001  xub_StrLen nSttCnt = rCntntIdx.GetIndex();
//STRIP001
//STRIP001  BOOL bRegSearch = SearchAlgorithms_REGEXP == rSearchOpt.algorithmType;
//STRIP001  BOOL bChkEmptyPara = bRegSearch && 2 == rSearchOpt.searchString.getLength() &&
//STRIP001                      ( !rSearchOpt.searchString.compareToAscii( "^$" ) ||
//STRIP001                        !rSearchOpt.searchString.compareToAscii( "$^" ) );
//STRIP001     BOOL bChkParaEnd = bRegSearch && 1 == rSearchOpt.searchString.getLength() &&
//STRIP001                       !rSearchOpt.searchString.compareToAscii( "$" );
//STRIP001
//STRIP001     LanguageType eLastLang = 0;
//STRIP001  while( 0 != ( pNode = ::GetNode( *pPam, bFirst, fnMove, bInReadOnly ) ))
//STRIP001  {
//STRIP001      if( pNode->IsTxtNode() )
//STRIP001      {
//STRIP001          nTxtLen = ((SwTxtNode*)pNode)->GetTxt().Len();
//STRIP001          if( rNdIdx == pPam->GetMark()->nNode )
//STRIP001              nEnde = pPam->GetMark()->nContent.GetIndex();
//STRIP001          else
//STRIP001              nEnde = bSrchForward ? nTxtLen : 0;
//STRIP001          nStart = rCntntIdx.GetIndex();
//STRIP001
//STRIP001             if( bSrchForward )
//STRIP001              lcl_CleanStr( *(SwTxtNode*)pNode, nStart, nEnde,
//STRIP001                              aFltArr, sCleanStr );
//STRIP001          else
//STRIP001              lcl_CleanStr( *(SwTxtNode*)pNode, nEnde, nStart,
//STRIP001                              aFltArr, sCleanStr );
//STRIP001
//STRIP001             SwScriptIterator* pScriptIter = 0;
//STRIP001             USHORT nSearchScript = 0;
//STRIP001             USHORT nCurrScript = 0;
//STRIP001
//STRIP001             if ( SearchAlgorithms_APPROXIMATE == rSearchOpt.algorithmType &&
//STRIP001                  pBreakIt->xBreak.is() )
//STRIP001             {
//STRIP001                 pScriptIter = new SwScriptIterator( sCleanStr, nStart, bSrchForward );
//STRIP001                 nSearchScript = pBreakIt->GetRealScriptOfText( rSearchOpt.searchString, 0 );
//STRIP001             }
//STRIP001
//STRIP001             xub_StrLen nStringEnd = nEnde;
//STRIP001             while ( bSrchForward && nStart < nStringEnd ||
//STRIP001                     ! bSrchForward && nStart > nStringEnd )
//STRIP001             {
//STRIP001                 // SearchAlgorithms_APPROXIMATE works on a per word base
//STRIP001                 // so we have to provide the text searcher with the correct
//STRIP001                 // locale, because it uses the breakiterator
//STRIP001                 if ( pScriptIter )
//STRIP001                 {
//STRIP001                     nEnde = pScriptIter->GetScriptChgPos();
//STRIP001                     nCurrScript = pScriptIter->GetCurrScript();
//STRIP001                     if ( nSearchScript == nCurrScript )
//STRIP001                     {
//STRIP001                         const LanguageType eCurrLang =
//STRIP001                                 ((SwTxtNode*)pNode)->GetLang( bSrchForward ?
//STRIP001                                                               nStart :
//STRIP001                                                               nEnde );
//STRIP001
//STRIP001                         if ( eCurrLang != eLastLang )
//STRIP001                         {
//STRIP001                             const ::com::sun::star::lang::Locale aLocale(
//STRIP001                                     pBreakIt->GetLocale( eCurrLang ) );
//STRIP001                             rSTxt.SetLocale( rSearchOpt, aLocale );
//STRIP001                             eLastLang = eCurrLang;
//STRIP001                         }
//STRIP001                     }
//STRIP001                  pScriptIter->Next();
//STRIP001                 }
//STRIP001
//STRIP001                 if( nSearchScript == nCurrScript &&
//STRIP001                  (rSTxt.*fnMove->fnSearch)( sCleanStr, &nStart, &nEnde, 0 ))
//STRIP001                 {
//STRIP001                     // setze den Bereich richtig
//STRIP001                     *GetPoint() = *pPam->GetPoint();
//STRIP001                     SetMark();
//STRIP001
//STRIP001                     // Start und Ende wieder korrigieren !!
//STRIP001                     if( aFltArr.Count() )
//STRIP001                     {
//STRIP001                         xub_StrLen n, nNew;
//STRIP001                         // bei Rueckwaertssuche die Positionen temp. vertauschen
//STRIP001                         if( !bSrchForward ) { n = nStart; nStart = nEnde; nEnde = n; }
//STRIP001
//STRIP001                         for( n = 0, nNew = nStart;
//STRIP001                             n < aFltArr.Count() && aFltArr[ n ] <= nStart;
//STRIP001                             ++n, ++nNew )
//STRIP001                             ;
//STRIP001                         nStart = nNew;
//STRIP001                         for( n = 0, nNew = nEnde;
//STRIP001                             n < aFltArr.Count() && aFltArr[ n ] < nEnde;
//STRIP001                             ++n, ++nNew )
//STRIP001                             ;
//STRIP001                         nEnde = nNew;
//STRIP001
//STRIP001                         // bei Rueckwaertssuche die Positionen temp. vertauschen
//STRIP001                         if( !bSrchForward ) { n = nStart; nStart = nEnde; nEnde = n; }
//STRIP001                     }
//STRIP001                     GetMark()->nContent = nStart;       // Startposition setzen
//STRIP001                     GetPoint()->nContent = nEnde;
//STRIP001
//STRIP001                     if( !bSrchForward )         // rueckwaerts Suche?
//STRIP001                         Exchange();             // Point und Mark tauschen
//STRIP001                     bFound = TRUE;
//STRIP001                     break;
//STRIP001                 }
//STRIP001
//STRIP001              nStart = nEnde;
//STRIP001             } // end of script while
//STRIP001
//STRIP001             delete pScriptIter;
//STRIP001
//STRIP001             if ( bFound )
//STRIP001                 break;
//STRIP001             else if( ( bChkEmptyPara && !nStart && !nTxtLen ) || bChkParaEnd )
//STRIP001             {
//STRIP001                 *GetPoint() = *pPam->GetPoint();
//STRIP001                 GetPoint()->nContent = bChkParaEnd ? nTxtLen : 0;
//STRIP001                 SetMark();
//STRIP001                 if( (bSrchForward || pSttNd != &rNdIdx.GetNode()) &&
//STRIP001                     Move( fnMoveForward, fnGoCntnt ) &&
//STRIP001                     (!bSrchForward || pSttNd != &GetPoint()->nNode.GetNode()) &&
//STRIP001                     1 == Abs( (int)( GetPoint()->nNode.GetIndex() -
//STRIP001                                     GetMark()->nNode.GetIndex()) ) )
//STRIP001                 {
//STRIP001                     if( !bSrchForward )         // rueckwaerts Suche?
//STRIP001                         Exchange();             // Point und Mark tauschen
//STRIP001                     bFound = TRUE;
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001  }
//STRIP001  delete pPam;
//STRIP001  return bFound;
//STRIP001 }


// Parameter fuers Suchen und Ersetzen von Text
//STRIP001 struct SwFindParaText : public SwFindParas
//STRIP001 {
//STRIP001  const SearchOptions& rSearchOpt;
//STRIP001  SwCursor& rCursor;
//STRIP001  utl::TextSearch aSTxt;
//STRIP001  BOOL bReplace;
//STRIP001
//STRIP001  SwFindParaText( const SearchOptions& rOpt, int bRepl, SwCursor& rCrsr )
//STRIP001      : rCursor( rCrsr ), bReplace( bRepl ),
//STRIP001      rSearchOpt( rOpt ), aSTxt( rOpt )
//STRIP001  {}
//STRIP001  virtual int Find( SwPaM* , SwMoveFn , const SwPaM*, FASTBOOL bInReadOnly );
//STRIP001  virtual int IsReplaceMode() const;
//STRIP001 };


//STRIP001 int SwFindParaText::Find( SwPaM* pCrsr, SwMoveFn fnMove,
//STRIP001                          const SwPaM* pRegion, FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  if( bInReadOnly && bReplace )
//STRIP001      bInReadOnly = FALSE;
//STRIP001
//STRIP001  BOOL bFnd = (BOOL)pCrsr->Find( rSearchOpt, aSTxt, fnMove, pRegion, bInReadOnly );
//STRIP001  // kein Bereich ??
//STRIP001  if( bFnd && *pCrsr->GetMark() == *pCrsr->GetPoint() )
//STRIP001      return FIND_NOT_FOUND;
//STRIP001
//STRIP001  if( bFnd && bReplace )          // String ersetzen ??
//STRIP001  {
//STRIP001      // Replace-Methode vom SwDoc benutzen
//STRIP001      int bRegExp = SearchAlgorithms_REGEXP == rSearchOpt.algorithmType;
//STRIP001      SwIndex& rSttCntIdx = pCrsr->Start()->nContent;
//STRIP001      xub_StrLen nSttCnt = rSttCntIdx.GetIndex();
//STRIP001      // damit die Region auch verschoben wird, in den Shell-Cursr-Ring
//STRIP001      // mit aufnehmen !!
//STRIP001      Ring *pPrev;
//STRIP001      if( bRegExp )
//STRIP001      {
//STRIP001          pPrev = pRegion->GetPrev();
//STRIP001          ((Ring*)pRegion)->MoveRingTo( &rCursor );
//STRIP001      }
//STRIP001
//STRIP001      rCursor.GetDoc()->Replace( *pCrsr, rSearchOpt.replaceString, bRegExp );
//STRIP001      rCursor.SaveTblBoxCntnt( pCrsr->GetPoint() );
//STRIP001
//STRIP001      if( bRegExp )
//STRIP001      {
//STRIP001          // und die Region wieder herausnehmen:
//STRIP001          Ring *p, *pNext = (Ring*)pRegion;
//STRIP001          do {
//STRIP001              p = pNext;
//STRIP001              pNext = p->GetNext();
//STRIP001              p->MoveTo( (Ring*)pRegion );
//STRIP001          } while( p != pPrev );
//STRIP001      }
//STRIP001      rSttCntIdx = nSttCnt;
//STRIP001      return FIND_NO_RING;
//STRIP001  }
//STRIP001  return bFnd ? FIND_FOUND : FIND_NOT_FOUND;
//STRIP001 }


//STRIP001 int SwFindParaText::IsReplaceMode() const
//STRIP001 {
//STRIP001  return bReplace;
//STRIP001 }


/*M*/ ULONG SwCursor::Find( const SearchOptions& rSearchOpt,
/*M*/                       SwDocPositions nStart, SwDocPositions nEnde,
/*M*/                         BOOL& bCancel,
/*M*/                       FindRanges eFndRngs, int bReplace )
/*M*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001 /*?*/    // OLE-Benachrichtigung abschalten !!
//STRIP001 /*?*/    SwDoc* pDoc = GetDoc();
//STRIP001 /*?*/    Link aLnk( pDoc->GetOle2Link() );
//STRIP001 /*?*/    pDoc->SetOle2Link( Link() );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSttUndo = pDoc->DoesUndo() && bReplace;
//STRIP001 /*?*/    if( bSttUndo )
//STRIP001 /*?*/        pDoc->StartUndo( UNDO_REPLACE );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSearchSel = 0 != (rSearchOpt.searchFlag & SearchFlags::REG_NOT_BEGINOFLINE);
//STRIP001 /*?*/    if( bSearchSel )
//STRIP001 /*?*/        eFndRngs = (FindRanges)(eFndRngs | FND_IN_SEL);
//STRIP001 /*?*/    SwFindParaText aSwFindParaText( rSearchOpt, bReplace, *this );
//STRIP001 /*?*/     ULONG nRet = FindAll( aSwFindParaText, nStart, nEnde, eFndRngs, bCancel );
//STRIP001 /*?*/    pDoc->SetOle2Link( aLnk );
//STRIP001 /*?*/    if( nRet && bReplace )
//STRIP001 /*?*/        pDoc->SetModified();
//STRIP001 /*?*/
//STRIP001 /*?*/    if( bSttUndo )
//STRIP001 /*?*/        pDoc->EndUndo( UNDO_REPLACE );
//STRIP001 /*?*/    return nRet;
/*M*/ }



