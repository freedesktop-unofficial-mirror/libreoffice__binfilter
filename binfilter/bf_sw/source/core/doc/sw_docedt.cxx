/*************************************************************************
 *
 *  $RCSfile: sw_docedt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:11:03 $
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

#include <string.h>         // fuer strchr()

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SOUND_HXX //autogen
#include <vcl/sound.hxx>
#endif
#ifndef _SVX_CSCOITEM_HXX //autogen
#include <bf_svx/cscoitem.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _LINGUISTIC_LNGPROPS_HHX_
#include <bf_linguistic/lngprops.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _ACORRECT_HXX
#include <acorrect.hxx>     // Autokorrektur
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>      // fuer SwBookmark
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>           // fuers Spell
#endif
#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _CRSTATE_HXX
#include <crstate.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>       // beim Move: Verzeichnisse korrigieren
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _FTNINFO_HXX
#include <ftninfo.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>       // Statusanzeige
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>       // Strukturen zum Sichern beim Move/Delete
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>          // fuers UpdateFtn
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _SPLARGS_HXX
#include <splargs.hxx>      // fuer Spell
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>       // fuer die UndoIds
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#include "comcore.hrc"
#include "editsh.hxx"

using namespace ::com::sun::star;
using namespace ::com::sun::star::linguistic2;
using namespace ::rtl;
using namespace ::com::sun::star::i18n;
//using namespace ::utl;

#define S2U(rString) OUString::createFromAscii(rString)


//STRIP001 struct _SaveRedline
//STRIP001 {
//STRIP001  SwRedline* pRedl;
//STRIP001  sal_uInt32 nStt, nEnd;
//STRIP001  xub_StrLen nSttCnt, nEndCnt;
//STRIP001
//STRIP001  _SaveRedline( SwRedline* pR, const SwNodeIndex& rSttIdx )
//STRIP001      : pRedl( pR )
//STRIP001  {
//STRIP001      const SwPosition* pStt = pR->Start(),
//STRIP001          * pEnd = pR->GetMark() == pStt ? pR->GetPoint() : pR->GetMark();
//STRIP001      sal_uInt32 nSttIdx = rSttIdx.GetIndex();
//STRIP001      nStt = pStt->nNode.GetIndex() - nSttIdx;
//STRIP001      nSttCnt = pStt->nContent.GetIndex();
//STRIP001      if( pR->HasMark() )
//STRIP001      {
//STRIP001          nEnd = pEnd->nNode.GetIndex() - nSttIdx;
//STRIP001          nEndCnt = pEnd->nContent.GetIndex();
//STRIP001      }
//STRIP001
//STRIP001      pRedl->GetPoint()->nNode = 0;
//STRIP001      pRedl->GetPoint()->nContent.Assign( 0, 0 );
//STRIP001      pRedl->GetMark()->nNode = 0;
//STRIP001      pRedl->GetMark()->nContent.Assign( 0, 0 );
//STRIP001  }
//STRIP001
//STRIP001  void SetPos( sal_uInt32 nInsPos )
//STRIP001  {
//STRIP001      pRedl->GetPoint()->nNode = nInsPos + nStt;
//STRIP001      pRedl->GetPoint()->nContent.Assign( pRedl->GetCntntNode(), nSttCnt );
//STRIP001      if( pRedl->HasMark() )
//STRIP001      {
//STRIP001          pRedl->GetMark()->nNode = nInsPos + nEnd;
//STRIP001          pRedl->GetMark()->nContent.Assign( pRedl->GetCntntNode(sal_False), nEndCnt );
//STRIP001      }
//STRIP001  }
//STRIP001 };

//STRIP001 SV_DECL_PTRARR_DEL( _SaveRedlines, _SaveRedline*, 0, 4 )
//STRIP001
//STRIP001 SV_IMPL_VARARR( _SaveFlyArr, _SaveFly )
SV_IMPL_PTRARR( SaveBookmarks, SaveBookmark* )
//STRIP001 SV_IMPL_PTRARR( _SaveRedlines, _SaveRedline* )

//STRIP001 sal_Bool lcl_MayOverwrite( const SwTxtNode *pNode, const xub_StrLen nPos )
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_True;
//STRIP001  const SwTxtAttr *pHt;
//STRIP001  sal_Unicode cChr = pNode->GetTxt().GetChar( nPos );
//STRIP001  if( ( CH_TXTATR_BREAKWORD == cChr || CH_TXTATR_INWORD == cChr ) &&
//STRIP001      0 != (pHt = pNode->GetTxtAttr( nPos )) )
//STRIP001          switch( pHt->Which() )
//STRIP001          {
//STRIP001              case RES_TXTATR_FLYCNT:
//STRIP001              case RES_TXTATR_FTN:
//STRIP001              case RES_TXTATR_FIELD:
//STRIP001              case RES_TXTATR_REFMARK:
//STRIP001              case RES_TXTATR_TOXMARK:
//STRIP001                  bRet = sal_False;
//STRIP001                  break;
//STRIP001          }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void lcl_SkipAttr( const SwTxtNode *pNode, SwIndex &rIdx, xub_StrLen &rStart )
//STRIP001 {
//STRIP001  if( !lcl_MayOverwrite( pNode, rStart ) )
//STRIP001  {
//STRIP001      // ueberspringe alle SonderAttribute
//STRIP001      do {
//STRIP001          // "Beep" bei jedem ausgelassenen
//STRIP001          Sound::Beep(SOUND_ERROR);
//STRIP001          rIdx++;
//STRIP001      } while( (rStart = rIdx.GetIndex()) < pNode->GetTxt().Len()
//STRIP001             && !lcl_MayOverwrite(pNode, rStart) );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------

//STRIP001 void _RestFlyInRange( _SaveFlyArr & rArr, const SwNodeIndex& rSttIdx,
//STRIP001                       const SwNodeIndex* pInsertPos )
//STRIP001 {
//STRIP001  SwPosition aPos( rSttIdx );
//STRIP001  for( sal_uInt16 n = 0; n < rArr.Count(); ++n )
//STRIP001  {
//STRIP001      // neuen Anker anlegen
//STRIP001      _SaveFly& rSave = rArr[n];
//STRIP001      SwFrmFmt* pFmt = rSave.pFrmFmt;
//STRIP001
//STRIP001         if( rSave.bInsertPosition )
//STRIP001         {
//STRIP001             if( pInsertPos != NULL )
//STRIP001                 aPos.nNode = *pInsertPos;
//STRIP001             else
//STRIP001                 aPos.nNode = rSttIdx.GetIndex();
//STRIP001         }
//STRIP001         else
//STRIP001             aPos.nNode = rSttIdx.GetIndex() + rSave.nNdDiff;
//STRIP001
//STRIP001      aPos.nContent.Assign( 0, 0 );
//STRIP001      SwFmtAnchor aAnchor( pFmt->GetAnchor() );
//STRIP001      aAnchor.SetAnchor( &aPos );
//STRIP001      pFmt->GetDoc()->GetSpzFrmFmts()->Insert(
//STRIP001              pFmt, pFmt->GetDoc()->GetSpzFrmFmts()->Count() );
//STRIP001      pFmt->SetAttr( aAnchor );
//STRIP001      SwCntntNode* pCNd = aPos.nNode.GetNode().GetCntntNode();
//STRIP001      if( pCNd && pCNd->GetFrm( 0, 0, sal_False ) )
//STRIP001          pFmt->MakeFrms();
//STRIP001  }
//STRIP001 }

//STRIP001 void _SaveFlyInRange( const SwNodeRange& rRg, _SaveFlyArr& rArr )
//STRIP001 {
//STRIP001  SwFrmFmt* pFmt;
//STRIP001  const SwFmtAnchor* pAnchor;
//STRIP001  const SwPosition* pAPos;
//STRIP001  SwSpzFrmFmts& rFmts = *rRg.aStart.GetNode().GetDoc()->GetSpzFrmFmts();
//STRIP001  for( sal_uInt16 n = 0; n < rFmts.Count(); ++n )
//STRIP001  {
//STRIP001      pFmt = (SwFrmFmt*)rFmts[n];
//STRIP001      pAnchor = &pFmt->GetAnchor();
//STRIP001      if( ( FLY_AT_CNTNT == pAnchor->GetAnchorId() ||
//STRIP001            FLY_AUTO_CNTNT == pAnchor->GetAnchorId() ) &&
//STRIP001          0 != ( pAPos = pAnchor->GetCntntAnchor() ) &&
//STRIP001          rRg.aStart <= pAPos->nNode && pAPos->nNode < rRg.aEnd )
//STRIP001      {
//STRIP001          ASSERT( pAnchor->GetAnchorId() != FLY_AUTO_CNTNT, "FLY-AUTO-Baustelle!" );
//STRIP001          _SaveFly aSave( pAPos->nNode.GetIndex() - rRg.aStart.GetIndex(),
//STRIP001                             pFmt, sal_False );
//STRIP001          rArr.Insert( aSave, rArr.Count());
//STRIP001          pFmt->DelFrms();
//STRIP001          rFmts.Remove( n--, 1 );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void _SaveFlyInRange( const SwPaM& rPam, const SwNodeIndex& rInsPos,
//STRIP001                     _SaveFlyArr& rArr, sal_Bool bMoveAllFlys )
//STRIP001 {
//STRIP001  SwSpzFrmFmts& rFmts = *rPam.GetPoint()->nNode.GetNode().GetDoc()->GetSpzFrmFmts();
//STRIP001  SwFrmFmt* pFmt;
//STRIP001  const SwFmtAnchor* pAnchor;
//STRIP001
//STRIP001  const SwPosition* pPos = rPam.Start();
//STRIP001  const SwNodeIndex& rSttNdIdx = pPos->nNode;
//STRIP001  short nSttOff = (!bMoveAllFlys && rSttNdIdx.GetNode().IsCntntNode() &&
//STRIP001                  pPos->nContent.GetIndex()) ? 1 : 0;
//STRIP001
//STRIP001  pPos = rPam.GetPoint() == pPos ? rPam.GetMark() : rPam.GetPoint();
//STRIP001  const SwNodeIndex& rEndNdIdx = pPos->nNode;
//STRIP001  short nOff = ( bMoveAllFlys || ( rEndNdIdx.GetNode().IsCntntNode() &&
//STRIP001              pPos->nContent == rEndNdIdx.GetNode().GetCntntNode()->Len() ))
//STRIP001                  ? 0 : 1;
//STRIP001
//STRIP001  const SwPosition* pAPos;
//STRIP001  const SwNodeIndex* pCntntIdx;
//STRIP001
//STRIP001  for( sal_uInt16 n = 0; n < rFmts.Count(); ++n )
//STRIP001  {
//STRIP001      sal_Bool bInsPos = sal_False;
//STRIP001      pFmt = (SwFrmFmt*)rFmts[n];
//STRIP001      pAnchor = &pFmt->GetAnchor();
//STRIP001      if( ( FLY_AT_CNTNT == pAnchor->GetAnchorId() ||
//STRIP001            FLY_AUTO_CNTNT == pAnchor->GetAnchorId() ) &&
//STRIP001          0 != ( pAPos = pAnchor->GetCntntAnchor() ) &&
//STRIP001          // nicht verschieben, wenn die InsPos im CntntBereich vom Fly ist
//STRIP001          ( 0 == ( pCntntIdx = pFmt->GetCntnt().GetCntntIdx() ) ||
//STRIP001            !( *pCntntIdx < rInsPos &&
//STRIP001              rInsPos < pCntntIdx->GetNode().EndOfSectionIndex() )) )
//STRIP001      {
//STRIP001          ASSERT( pAnchor->GetAnchorId() != FLY_AUTO_CNTNT, "FLY-AUTO-Baustelle!" );
//STRIP001          if( !bMoveAllFlys && rEndNdIdx == pAPos->nNode )
//STRIP001          {
//STRIP001              // wenn nur teil vom EndNode oder der EndNode und SttNode
//STRIP001              // identisch sind, chaos::Anchor nicht anfassen
//STRIP001              if( rSttNdIdx != pAPos->nNode )
//STRIP001              {
//STRIP001                  // Anker nur an Anfang/Ende haengen
//STRIP001                  SwPosition aPos( rSttNdIdx );
//STRIP001                  SwFmtAnchor aAnchor( *pAnchor );
//STRIP001                  aAnchor.SetAnchor( &aPos );
//STRIP001                  pFmt->SetAttr( aAnchor );
//STRIP001 //                   ((SwFmtAnchor*)pAnchor)->SetAnchor( &aPos );
//STRIP001              }
//STRIP001          }
//STRIP001          else if( ( rSttNdIdx.GetIndex() + nSttOff <= pAPos->nNode.GetIndex()
//STRIP001                  && pAPos->nNode.GetIndex() <= rEndNdIdx.GetIndex() - nOff ) ||
//STRIP001                      0 != ( bInsPos = rInsPos == pAPos->nNode ))
//STRIP001
//STRIP001          {
//STRIP001              _SaveFly aSave( pAPos->nNode.GetIndex() - rSttNdIdx.GetIndex(),
//STRIP001                                 pFmt, bInsPos );
//STRIP001              rArr.Insert( aSave, rArr.Count());
//STRIP001              pFmt->DelFrms();
//STRIP001              rFmts.Remove( n--, 1 );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------

// loesche und verschiebe alle "Fly's am Absatz", die in der SSelection
// liegen. Steht am SPoint ein Fly, wird dieser auf den Mark verschoben.

/*N*/ void DelFlyInRange( const SwNodeIndex& rMkNdIdx,
/*N*/                   const SwNodeIndex& rPtNdIdx )
/*N*/ {
/*N*/   const sal_Bool bDelFwrd = rMkNdIdx.GetIndex() <= rPtNdIdx.GetIndex();
/*N*/
/*N*/   SwDoc* pDoc = rMkNdIdx.GetNode().GetDoc();
/*N*/   SwSpzFrmFmts& rTbl = *pDoc->GetSpzFrmFmts();
/*N*/   const SwPosition* pAPos;
/*N*/   for ( sal_uInt16 i = rTbl.Count(); i; )
/*N*/   {
/*N*/       SwFrmFmt *pFmt = rTbl[--i];
/*N*/       const SwFmtAnchor &rAnch = pFmt->GetAnchor();
/*N*/       if( ( rAnch.GetAnchorId() == FLY_AT_CNTNT ||
/*N*/             rAnch.GetAnchorId() == FLY_AUTO_CNTNT ) &&
/*N*/           0 != ( pAPos = rAnch.GetCntntAnchor() ) &&
/*N*/           ( bDelFwrd
/*N*/               ? rMkNdIdx < pAPos->nNode && pAPos->nNode <= rPtNdIdx
/*N*/               : rPtNdIdx <= pAPos->nNode && pAPos->nNode < rMkNdIdx ))
/*N*/       {
/*N*/           ASSERT( rAnch.GetAnchorId() != FLY_AUTO_CNTNT, "FLY-AUTO-Baustelle!" );
/*N*/           // nur den Anker verchieben ??
/*N*/           if( rPtNdIdx == pAPos->nNode )
/*N*/           {
/*?*/               SwFmtAnchor aAnch( pFmt->GetAnchor() );
/*?*/               SwPosition aPos( rMkNdIdx );
/*?*/               aAnch.SetAnchor( &aPos );
/*?*/               pFmt->SetAttr( aAnch );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // wird der Fly geloescht muss auch im seinem Inhalt alle
/*N*/               // Flys geloescht werden !!
/*N*/               const SwFmtCntnt &rCntnt = pFmt->GetCntnt();
/*N*/               if( rCntnt.GetCntntIdx() )
/*N*/               {
/*N*/                   DelFlyInRange( *rCntnt.GetCntntIdx(),
/*N*/                                   SwNodeIndex( *rCntnt.GetCntntIdx()->
/*N*/                                           GetNode().EndOfSectionNode() ));
/*N*/                   // Position kann sich verschoben haben !
/*N*/                   if( i > rTbl.Count() )
/*?*/                       i = rTbl.Count();
/*N*/                   else if( pFmt != rTbl[i] )
/*?*/                       i = rTbl.GetPos( pFmt );
/*N*/               }
/*N*/
/*N*/               pDoc->DelLayoutFmt( pFmt );
/*N*/ //                i++;    // keinen auslassen
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


//STRIP001 int lcl_SaveFtn( const SwNodeIndex& rSttNd, const SwNodeIndex& rEndNd,
//STRIP001               const SwNodeIndex& rInsPos,
//STRIP001               SwFtnIdxs& rFtnArr, SwFtnIdxs& rSaveArr,
//STRIP001               const SwIndex* pSttCnt = 0, const SwIndex* pEndCnt = 0 )
//STRIP001 {
//STRIP001  int bUpdateFtn = sal_False;
//STRIP001  if( rFtnArr.Count() )
//STRIP001  {
//STRIP001      const SwNodes& rNds = rInsPos.GetNodes();
//STRIP001      int bDelFtn = rInsPos.GetIndex() < rNds.GetEndOfAutotext().GetIndex() &&
//STRIP001                  rSttNd.GetIndex() >= rNds.GetEndOfAutotext().GetIndex();
//STRIP001      int bSaveFtn = !bDelFtn &&
//STRIP001                      rInsPos.GetIndex() >= rNds.GetEndOfExtras().GetIndex();
//STRIP001
//STRIP001      sal_uInt16 nPos;
//STRIP001      rFtnArr.SeekEntry( rSttNd, &nPos );
//STRIP001      SwTxtFtn* pSrch;
//STRIP001      const SwNode* pFtnNd;
//STRIP001
//STRIP001      // loesche/sicher erstmal alle, die dahinter stehen
//STRIP001      while( nPos < rFtnArr.Count() && ( pFtnNd =
//STRIP001          &( pSrch = rFtnArr[ nPos ] )->GetTxtNode())->GetIndex()
//STRIP001                  <= rEndNd.GetIndex() )
//STRIP001      {
//STRIP001          xub_StrLen nFtnSttIdx = *pSrch->GetStart();
//STRIP001          if( ( pEndCnt && pSttCnt )
//STRIP001              ? (( &rSttNd.GetNode() == pFtnNd &&
//STRIP001                   pSttCnt->GetIndex() > nFtnSttIdx) ||
//STRIP001                 ( &rEndNd.GetNode() == pFtnNd &&
//STRIP001                  nFtnSttIdx >= pEndCnt->GetIndex() ))
//STRIP001              : ( &rEndNd.GetNode() == pFtnNd ))
//STRIP001          {
//STRIP001              ++nPos;     // weiter suchen
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // dann weg damit
//STRIP001              if( bDelFtn )
//STRIP001              {
//STRIP001                  SwTxtNode& rTxtNd = (SwTxtNode&)pSrch->GetTxtNode();
//STRIP001                  SwIndex aIdx( &rTxtNd, nFtnSttIdx );
//STRIP001                  rTxtNd.Erase( aIdx, 1 );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pSrch->DelFrms();
//STRIP001                  rFtnArr.Remove( nPos );
//STRIP001                  if( bSaveFtn )
//STRIP001                      rSaveArr.Insert( pSrch );
//STRIP001              }
//STRIP001              bUpdateFtn = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      while( nPos-- && ( pFtnNd = &( pSrch = rFtnArr[ nPos ] )->
//STRIP001              GetTxtNode())->GetIndex() >= rSttNd.GetIndex() )
//STRIP001      {
//STRIP001          xub_StrLen nFtnSttIdx = *pSrch->GetStart();
//STRIP001          if( !pEndCnt || !pSttCnt ||
//STRIP001              !( (( &rSttNd.GetNode() == pFtnNd &&
//STRIP001                  pSttCnt->GetIndex() > nFtnSttIdx ) ||
//STRIP001                 ( &rEndNd.GetNode() == pFtnNd &&
//STRIP001                  nFtnSttIdx >= pEndCnt->GetIndex() )) ))
//STRIP001          {
//STRIP001              if( bDelFtn )
//STRIP001              {
//STRIP001                  // dann weg damit
//STRIP001                  SwTxtNode& rTxtNd = (SwTxtNode&)pSrch->GetTxtNode();
//STRIP001                  SwIndex aIdx( &rTxtNd, nFtnSttIdx );
//STRIP001                  rTxtNd.Erase( aIdx, 1 );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pSrch->DelFrms();
//STRIP001                  rFtnArr.Remove( nPos );
//STRIP001                  if( bSaveFtn )
//STRIP001                      rSaveArr.Insert( pSrch );
//STRIP001              }
//STRIP001              bUpdateFtn = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bUpdateFtn;
//STRIP001 }

//STRIP001 void lcl_SaveRedlines( const SwNodeRange& rRg, _SaveRedlines& rArr )
//STRIP001 {
//STRIP001  SwDoc* pDoc = rRg.aStart.GetNode().GetDoc();
//STRIP001  sal_uInt16 nRedlPos;
//STRIP001  SwPosition aSrchPos( rRg.aStart ); aSrchPos.nNode--;
//STRIP001  aSrchPos.nContent.Assign( aSrchPos.nNode.GetNode().GetCntntNode(), 0 );
//STRIP001  if( pDoc->GetRedline( aSrchPos, &nRedlPos ) && nRedlPos )
//STRIP001      --nRedlPos;
//STRIP001  else if( nRedlPos >= pDoc->GetRedlineTbl().Count() )
//STRIP001      return ;
//STRIP001
//STRIP001  SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001  pDoc->SetRedlineMode_intern( ( eOld & ~REDLINE_IGNORE) | REDLINE_ON );
//STRIP001  SwRedlineTbl& rRedlTbl = (SwRedlineTbl&)pDoc->GetRedlineTbl();
//STRIP001
//STRIP001  do {
//STRIP001      SwRedline* pTmp = rRedlTbl[ nRedlPos ];
//STRIP001
//STRIP001      const SwPosition* pRStt = pTmp->Start(),
//STRIP001                      * pREnd = pTmp->GetMark() == pRStt
//STRIP001                          ? pTmp->GetPoint() : pTmp->GetMark();
//STRIP001
//STRIP001      if( pRStt->nNode < rRg.aStart )
//STRIP001      {
//STRIP001          if( pREnd->nNode > rRg.aStart && pREnd->nNode < rRg.aEnd )
//STRIP001          {
//STRIP001              // Kopie erzeugen und Ende vom Original ans Ende des
//STRIP001              // MoveBereiches setzen. Die Kopie wird mit verschoben
//STRIP001              SwRedline* pNewRedl = new SwRedline( *pTmp );
//STRIP001              SwPosition* pTmpPos = pNewRedl->Start();
//STRIP001              pTmpPos->nNode = rRg.aStart;
//STRIP001              pTmpPos->nContent.Assign(
//STRIP001                          pTmpPos->nNode.GetNode().GetCntntNode(), 0 );
//STRIP001
//STRIP001              _SaveRedline* pSave = new _SaveRedline( pNewRedl, rRg.aStart );
//STRIP001 //               rArr.Insert( pSave, rArr.Count() );
//STRIP001              rArr.C40_INSERT( _SaveRedline, pSave, rArr.Count() );
//STRIP001
//STRIP001              pTmpPos = pTmp->End();
//STRIP001              pTmpPos->nNode = rRg.aEnd;
//STRIP001              pTmpPos->nContent.Assign(
//STRIP001                          pTmpPos->nNode.GetNode().GetCntntNode(), 0 );
//STRIP001          }
//STRIP001          else if( pREnd->nNode == rRg.aStart )
//STRIP001          {
//STRIP001              SwPosition* pTmpPos = pTmp->End();
//STRIP001              pTmpPos->nNode = rRg.aEnd;
//STRIP001              pTmpPos->nContent.Assign(
//STRIP001                          pTmpPos->nNode.GetNode().GetCntntNode(), 0 );
//STRIP001          }
//STRIP001      }
//STRIP001      else if( pRStt->nNode < rRg.aEnd )
//STRIP001      {
//STRIP001          rRedlTbl.Remove( nRedlPos-- );
//STRIP001          if( pREnd->nNode < rRg.aEnd ||
//STRIP001              ( pREnd->nNode == rRg.aEnd && !pREnd->nContent.GetIndex()) )
//STRIP001          {
//STRIP001              // gesamt verschieben
//STRIP001              _SaveRedline* pSave = new _SaveRedline( pTmp, rRg.aStart );
//STRIP001 //               rArr.Insert( pSave, rArr.Count() );
//STRIP001              rArr.C40_INSERT( _SaveRedline, pSave, rArr.Count() );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // aufsplitten
//STRIP001              SwRedline* pNewRedl = new SwRedline( *pTmp );
//STRIP001              SwPosition* pTmpPos = pNewRedl->End();
//STRIP001              pTmpPos->nNode = rRg.aEnd;
//STRIP001              pTmpPos->nContent.Assign(
//STRIP001                          pTmpPos->nNode.GetNode().GetCntntNode(), 0 );
//STRIP001
//STRIP001              _SaveRedline* pSave = new _SaveRedline( pNewRedl, rRg.aStart );
//STRIP001 //               rArr.Insert( pSave, rArr.Count() );
//STRIP001              rArr.C40_INSERT( _SaveRedline, pSave, rArr.Count() );
//STRIP001
//STRIP001              pTmpPos = pTmp->Start();
//STRIP001              pTmpPos->nNode = rRg.aEnd;
//STRIP001              pTmpPos->nContent.Assign(
//STRIP001                          pTmpPos->nNode.GetNode().GetCntntNode(), 0 );
//STRIP001              pDoc->AppendRedline( pTmp );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          break;
//STRIP001
//STRIP001  } while( ++nRedlPos < pDoc->GetRedlineTbl().Count() );
//STRIP001  pDoc->SetRedlineMode_intern( eOld );
//STRIP001 }

//STRIP001 void lcl_RestoreRedlines( SwDoc* pDoc, sal_uInt32 nInsPos, _SaveRedlines& rArr )
//STRIP001 {
//STRIP001  SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001  pDoc->SetRedlineMode_intern( ( eOld & ~REDLINE_IGNORE) | REDLINE_ON );
//STRIP001
//STRIP001  for( sal_uInt16 n = 0; n < rArr.Count(); ++n )
//STRIP001  {
//STRIP001      _SaveRedline* pSave = rArr[ n ];
//STRIP001      pSave->SetPos( nInsPos );
//STRIP001      pDoc->AppendRedline( pSave->pRedl );
//STRIP001  }
//STRIP001
//STRIP001  pDoc->SetRedlineMode_intern( eOld );
//STRIP001 }

// ------------------------------------------------------------------------

/*N*/ _SaveRedlEndPosForRestore::_SaveRedlEndPosForRestore( const SwNodeIndex& rInsIdx )
/*N*/   : pSavArr( 0 ), pSavIdx( 0 )
/*N*/ {
/*N*/   SwNode& rNd = rInsIdx.GetNode();
/*N*/   SwDoc* pDest = rNd.GetDoc();
/*N*/   if( pDest->GetRedlineTbl().Count() )
/*N*/   {
/*N*/       sal_uInt16 nFndPos;
/*N*/       const SwPosition* pEnd;
/*N*/       SwPosition aSrcPos( rInsIdx, SwIndex( rNd.GetCntntNode(), 0 ));
/*N*/       const SwRedline* pRedl = pDest->GetRedline( aSrcPos, &nFndPos );
/*N*/       while( nFndPos-- && *( pEnd = ( pRedl =
/*N*/           pDest->GetRedlineTbl()[ nFndPos ] )->End() ) == aSrcPos &&
/*N*/           *pRedl->Start() != aSrcPos )
/*N*/       {
/*N*/           if( !pSavArr )
/*N*/           {
/*N*/               pSavArr = new SvPtrarr( 2, 2 );
/*N*/               pSavIdx = new SwNodeIndex( rInsIdx, -1 );
/*N*/           }
/*N*/           void* p = (void*)pEnd;
/*N*/           pSavArr->Insert( p, pSavArr->Count() );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ _SaveRedlEndPosForRestore::~_SaveRedlEndPosForRestore()
/*N*/ {
/*N*/   if( pSavArr )
/*N*/   {
/*N*/       delete pSavArr;
/*N*/       delete pSavIdx;
/*N*/   }
/*N*/ }

/*N*/ void _SaveRedlEndPosForRestore::_Restore()
/*N*/ {
/*N*/   (*pSavIdx)++;
/*N*/   SwPosition aPos( *pSavIdx, SwIndex( pSavIdx->GetNode().GetCntntNode(), 0 ));
/*N*/   for( sal_uInt16 n = pSavArr->Count(); n; )
/*N*/       *((SwPosition*)pSavArr->GetObject( --n )) = aPos;
/*N*/ }


// ------------------------------------------------------------------------

// Loeschen einer vollstaendigen Section des NodesArray.
// Der uebergebene Node steht irgendwo in der gewuenschten Section
/*N*/ void SwDoc::DeleteSection( SwNode *pNode )
/*N*/ {
/*N*/   ASSERT( pNode, "Kein Node uebergeben." );
/*N*/   SwStartNode* pSttNd = pNode->IsStartNode() ? (SwStartNode*)pNode
/*N*/                                              : pNode->StartOfSectionNode();
/*N*/   SwNodeIndex aSttIdx( *pSttNd ), aEndIdx( *pNode->EndOfSectionNode() );
/*N*/
/*N*/   // dann loesche mal alle Fly's, text::Bookmarks, ...
/*N*/   DelFlyInRange( aSttIdx, aEndIdx );
/*N*/   DeleteRedline( *pSttNd );
/*N*/   _DelBookmarks( aSttIdx, aEndIdx );
/*N*/
/*N*/   {
/*N*/       // alle Crsr/StkCrsr/UnoCrsr aus dem Loeschbereich verschieben
/*N*/       SwNodeIndex aMvStt( aSttIdx, 1 );
/*N*/       CorrAbs( aMvStt, aEndIdx, SwPosition( aSttIdx ), sal_True );
/*N*/   }
/*N*/
/*N*/   GetNodes().DelNodes( aSttIdx, aEndIdx.GetIndex() - aSttIdx.GetIndex() + 1 );
/*N*/ }



/*************************************************************************
|*                SwDoc::Insert(char)
|*    Beschreibung      Zeichen einfuegen
*************************************************************************/

/*N*/ sal_Bool SwDoc::Insert( const SwPaM &rRg, sal_Unicode c )
/*N*/ {
/*N*/   if( DoesUndo() )
/*N*/       ClearRedo();
/*N*/
/*N*/   const SwPosition & rPos = *rRg.GetPoint();
/*N*/
/*N*/   if( pACEWord )                  // Aufnahme in die Autokorrektur
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  if( pACEWord->IsDeleted() )
//STRIP001 /*?*/            pACEWord->CheckChar( rPos, c );
//STRIP001 /*?*/        delete pACEWord, pACEWord = 0;
/*N*/   }
/*N*/   SwTxtNode *pNode = rPos.nNode.GetNode().GetTxtNode();
/*N*/   if(!pNode)
/*?*/       return sal_False;
/*N*/   sal_Bool bInsOneChar = sal_True;
/*N*/
/*N*/   SwDataChanged aTmp( rRg, 0 );
/*N*/
/*N*/   pNode->Insert( c, rPos.nContent );
/*N*/
/*N*/   if ( DoesUndo() )
/*N*/   {
/*N*/       sal_uInt16 nUndoSize = pUndos->Count();
/*N*/       SwUndo * pUndo;
/*N*/       if( DoesGroupUndo() && bInsOneChar && nUndoSize-- &&
/*N*/           UNDO_INSERT == ( pUndo = (*pUndos)[ nUndoSize ])->GetId() &&
/*N*/           ((SwUndoInsert*)pUndo)->CanGrouping( rPos, c ))
/*N*/           ; // wenn CanGrouping() sal_True returnt, ist schon alles erledigt
/*N*/       else
/*N*/           AppendUndo( new SwUndoInsert( rPos.nNode,
/*N*/                                       rPos.nContent.GetIndex(), 1,
/*N*/                                       !GetAppCharClass().isLetterNumeric(
/*N*/                                           pNode->GetTxt(),
/*N*/                                           rPos.nContent.GetIndex() - 1 )));
/*N*/   }
/*N*/
/*N*/   if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  SwPaM aPam( rPos.nNode, rPos.nContent.GetIndex() - 1,
//STRIP001 /*?*/                    rPos.nNode, rPos.nContent.GetIndex() );
//STRIP001 /*?*/        if( IsRedlineOn() )
//STRIP001 /*?*/            AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/        else
//STRIP001 /*?*/            SplitRedline( aPam );
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return sal_True;
/*N*/ }


/*************************************************************************
|*                SwDoc::Overwrite(char)
|*    Beschreibung      Zeichen ueberschreiben
*************************************************************************/

//STRIP001 sal_Bool SwDoc::Overwrite( const SwPaM &rRg, sal_Unicode c )
//STRIP001 {
//STRIP001  SwPosition& rPt = *(SwPosition*)rRg.GetPoint();
//STRIP001  if( pACEWord )                  // Aufnahme in die Autokorrektur
//STRIP001  {
//STRIP001      pACEWord->CheckChar( rPt, c );
//STRIP001      delete pACEWord, pACEWord = 0;
//STRIP001  }
//STRIP001
//STRIP001  SwTxtNode *pNode = rPt.nNode.GetNode().GetTxtNode();
//STRIP001  if(!pNode)
//STRIP001      return sal_False;
//STRIP001
//STRIP001  sal_uInt16 nOldAttrCnt = pNode->GetpSwpHints()
//STRIP001                              ? pNode->GetpSwpHints()->Count() : 0;
//STRIP001  SwDataChanged aTmp( rRg, 0 );
//STRIP001  SwIndex& rIdx = rPt.nContent;
//STRIP001  xub_StrLen nStart = rIdx.GetIndex();
//STRIP001
//STRIP001  // hinter das Zeichen (zum aufspannen der Attribute !!)
//STRIP001  if( nStart < pNode->GetTxt().Len() )
//STRIP001      lcl_SkipAttr( pNode, rIdx, nStart );
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      sal_uInt16 nUndoSize = pUndos->Count();
//STRIP001      SwUndo * pUndo;
//STRIP001      if( DoesGroupUndo() && nUndoSize-- &&
//STRIP001          UNDO_OVERWRITE == ( pUndo = (*pUndos)[ nUndoSize ])->GetId() &&
//STRIP001          ((SwUndoOverwrite*)pUndo)->CanGrouping( this, rPt, c ))
//STRIP001          ;// wenn CanGrouping() sal_True returnt, ist schon alles erledigt
//STRIP001      else
//STRIP001          AppendUndo( new SwUndoOverwrite( this, rPt, c ));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      BOOL bOldExpFlg = pNode->IsIgnoreDontExpand();
//STRIP001      pNode->SetIgnoreDontExpand( TRUE );
//STRIP001
//STRIP001      // hinter das Zeichen (zum aufspannen der Attribute !!)
//STRIP001      if( nStart < pNode->GetTxt().Len() )
//STRIP001          rIdx++;
//STRIP001      pNode->Insert( c, rIdx );
//STRIP001      if( nStart+1 < rIdx.GetIndex() )
//STRIP001      {
//STRIP001          rIdx = nStart;
//STRIP001          pNode->Erase( rIdx, 1 );
//STRIP001          rIdx++;
//STRIP001      }
//STRIP001      pNode->SetIgnoreDontExpand( bOldExpFlg );
//STRIP001  }
//STRIP001
//STRIP001  sal_uInt16 nNewAttrCnt = pNode->GetpSwpHints()
//STRIP001                              ? pNode->GetpSwpHints()->Count() : 0;
//STRIP001  if( nOldAttrCnt != nNewAttrCnt )
//STRIP001  {
//STRIP001      SwUpdateAttr aHint( 0, 0, 0 );
//STRIP001      SwClientIter aIter( *pNode );
//STRIP001      SwClient* pGTO = aIter.First(TYPE( SwCrsrShell ));
//STRIP001      while( pGTO )
//STRIP001      {
//STRIP001          pGTO->Modify( 0, &aHint );
//STRIP001          pGTO = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !DoesUndo() && !IsIgnoreRedline() && GetRedlineTbl().Count() )
//STRIP001  {
//STRIP001      SwPaM aPam( rPt.nNode, nStart, rPt.nNode, rPt.nContent.GetIndex() );
//STRIP001      DeleteRedline( aPam );
//STRIP001  }
//STRIP001  else if( IsRedlineOn() )
//STRIP001  {
//STRIP001      SwPaM aPam( rPt.nNode, nStart, rPt.nNode, rPt.nContent.GetIndex() );
//STRIP001      AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SwDoc::Overwrite( const SwPaM &rRg, const String &rStr )
//STRIP001 {
//STRIP001  SwPosition& rPt = *(SwPosition*)rRg.GetPoint();
//STRIP001  if( pACEWord )                  // Aufnahme in die Autokorrektur
//STRIP001  {
//STRIP001      if( 1 == rStr.Len() )
//STRIP001          pACEWord->CheckChar( rPt, rStr.GetChar( 0 ) );
//STRIP001      delete pACEWord, pACEWord = 0;
//STRIP001  }
//STRIP001
//STRIP001  SwTxtNode *pNode = rPt.nNode.GetNode().GetTxtNode();
//STRIP001  if(!pNode)
//STRIP001      return sal_False;
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001      ClearRedo();
//STRIP001
//STRIP001  sal_uInt16 nOldAttrCnt = pNode->GetpSwpHints()
//STRIP001                              ? pNode->GetpSwpHints()->Count() : 0;
//STRIP001  SwDataChanged aTmp( rRg, 0 );
//STRIP001  SwIndex& rIdx = rPt.nContent;
//STRIP001  xub_StrLen nStart;
//STRIP001
//STRIP001  sal_uInt16 nUndoSize = pUndos->Count();
//STRIP001  SwUndo * pUndo;
//STRIP001  sal_Unicode c;
//STRIP001  String aStr;
//STRIP001
//STRIP001  BOOL bOldExpFlg = pNode->IsIgnoreDontExpand();
//STRIP001  pNode->SetIgnoreDontExpand( TRUE );
//STRIP001
//STRIP001  for( xub_StrLen nCnt = 0; nCnt < rStr.Len(); ++nCnt )
//STRIP001  {
//STRIP001      // hinter das Zeichen (zum aufspannen der Attribute !!)
//STRIP001      if( (nStart = rIdx.GetIndex()) < pNode->GetTxt().Len() )
//STRIP001          lcl_SkipAttr( pNode, rIdx, nStart );
//STRIP001      c = rStr.GetChar( nCnt );
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          if( DoesGroupUndo() && nUndoSize &&
//STRIP001              UNDO_OVERWRITE == ( pUndo = (*pUndos)[ nUndoSize-1 ])->GetId() &&
//STRIP001              ((SwUndoOverwrite*)pUndo)->CanGrouping( this, rPt, c ))
//STRIP001              ;// wenn CanGrouping() sal_True returnt, ist schon alles erledigt
//STRIP001          else
//STRIP001          {
//STRIP001              AppendUndo( new SwUndoOverwrite( this, rPt, c ));
//STRIP001              nUndoSize = pUndos->Count();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // hinter das Zeichen (zum Aufspannen der Attribute !!)
//STRIP001          if( nStart < pNode->GetTxt().Len() )
//STRIP001              rIdx++;
//STRIP001          pNode->Insert( c, rIdx );
//STRIP001          if( nStart+1 < rIdx.GetIndex() )
//STRIP001          {
//STRIP001              rIdx = nStart;
//STRIP001              pNode->Erase( rIdx, 1 );
//STRIP001              rIdx++;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pNode->SetIgnoreDontExpand( bOldExpFlg );
//STRIP001
//STRIP001  sal_uInt16 nNewAttrCnt = pNode->GetpSwpHints()
//STRIP001                              ? pNode->GetpSwpHints()->Count() : 0;
//STRIP001  if( nOldAttrCnt != nNewAttrCnt )
//STRIP001  {
//STRIP001      SwUpdateAttr aHint( 0, 0, 0 );
//STRIP001      SwClientIter aIter( *pNode );
//STRIP001      SwClient* pGTO = aIter.First(TYPE( SwCrsrShell ));
//STRIP001      while( pGTO )
//STRIP001      {
//STRIP001          pGTO->Modify( 0, &aHint );
//STRIP001          pGTO = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !DoesUndo() && !IsIgnoreRedline() && GetRedlineTbl().Count() )
//STRIP001  {
//STRIP001      SwPaM aPam( rPt.nNode, nStart, rPt.nNode, rPt.nContent.GetIndex() );
//STRIP001      DeleteRedline( aPam );
//STRIP001  }
//STRIP001  else if( IsRedlineOn() )
//STRIP001  {
//STRIP001      SwPaM aPam( rPt.nNode, nStart, rPt.nNode, rPt.nContent.GetIndex() );
//STRIP001      AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  return sal_True;
//STRIP001 }


//STRIP001 sal_Bool SwDoc::MoveAndJoin( SwPaM& rPaM, SwPosition& rPos, SwMoveFlags eMvFlags )
//STRIP001 {
//STRIP001  SwNodeIndex aIdx( rPaM.Start()->nNode );
//STRIP001  sal_Bool bJoinTxt = aIdx.GetNode().IsTxtNode();
//STRIP001  sal_Bool bOneNode = rPaM.GetPoint()->nNode == rPaM.GetMark()->nNode;
//STRIP001  aIdx--;             // vor den Move Bereich !!
//STRIP001
//STRIP001  sal_Bool bRet = Move( rPaM, rPos, eMvFlags );
//STRIP001  if( bRet && !bOneNode )
//STRIP001  {
//STRIP001      if( bJoinTxt )
//STRIP001          aIdx++;
//STRIP001      SwTxtNode * pTxtNd = aIdx.GetNode().GetTxtNode();
//STRIP001      SwNodeIndex aNxtIdx( aIdx );
//STRIP001      if( pTxtNd && pTxtNd->CanJoinNext( &aNxtIdx ) )
//STRIP001      {
//STRIP001          {   // Block wegen SwIndex in den Node !!
//STRIP001              CorrRel( aNxtIdx, SwPosition( aIdx, SwIndex( pTxtNd,
//STRIP001                          pTxtNd->GetTxt().Len() ) ), 0, sal_True );
//STRIP001          }
//STRIP001          pTxtNd->JoinNext();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 sal_Bool SwDoc::Move( SwPaM& rPaM, SwPosition& rPos, SwMoveFlags eMvFlags )
//STRIP001 {
//STRIP001  // keine Moves-Abfangen
//STRIP001  const SwPosition *pStt = rPaM.Start(), *pEnd = rPaM.End();
//STRIP001  if( !rPaM.HasMark() || *pStt >= *pEnd || (*pStt <= rPos && rPos < *pEnd))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  // sicher die absatzgebundenen Flys, damit sie verschoben werden koennen.
//STRIP001  _SaveFlyArr aSaveFlyArr;
//STRIP001  _SaveFlyInRange( rPaM, rPos.nNode, aSaveFlyArr, DOC_MOVEALLFLYS & eMvFlags );
//STRIP001
//STRIP001  int bUpdateFtn = sal_False;
//STRIP001  SwFtnIdxs aTmpFntIdx;
//STRIP001
//STRIP001  // falls Undo eingeschaltet, erzeuge das UndoMove-Objekt
//STRIP001  SwUndoMove * pUndoMove = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndoMove = new SwUndoMove( rPaM, rPos );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      bUpdateFtn = lcl_SaveFtn( pStt->nNode, pEnd->nNode, rPos.nNode,
//STRIP001                                  GetFtnIdxs(), aTmpFntIdx,
//STRIP001                                  &pStt->nContent, &pEnd->nContent );
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool bSplit = sal_False;
//STRIP001  SwPaM * pSavePam = new SwPaM( rPos, rPos );
//STRIP001
//STRIP001  // stelle den SPoint an den Anfang vom Bereich (Definition)
//STRIP001  if( rPaM.GetPoint() == pEnd )
//STRIP001      rPaM.Exchange();
//STRIP001
//STRIP001  // in der EditShell wird nach dem Move ein JoinNext erzeugt, wenn
//STRIP001  // vor und nach dem Move ein Text-Node steht.
//STRIP001  SwTxtNode* pSrcNd = rPaM.GetPoint()->nNode.GetNode().GetTxtNode();
//STRIP001  sal_Bool bCorrSavePam = pSrcNd && pStt->nNode != pEnd->nNode;
//STRIP001
//STRIP001  // werden ein oder mehr TextNodes bewegt, so wird
//STRIP001  // im SwNodes::Move ein SplitNode erzeugt. Dieser Updated aber nicht
//STRIP001  // den Cursor. Um das zu verhindern, wird hier ein TextNode angelegt,
//STRIP001  // um die Updaterei der Indizies zu erhalten. Nach dem Move wird
//STRIP001  // evt. der Node geloescht.
//STRIP001
//STRIP001  SwTxtNode * pTNd = rPos.nNode.GetNode().GetTxtNode();
//STRIP001  if( pTNd && rPaM.GetPoint()->nNode != rPaM.GetMark()->nNode &&
//STRIP001      ( rPos.nContent.GetIndex() || ( pTNd->Len() && bCorrSavePam  )) )
//STRIP001  {
//STRIP001      bSplit = sal_True;
//STRIP001      xub_StrLen nMkCntnt = rPaM.GetMark()->nContent.GetIndex();
//STRIP001
//STRIP001      SvULongs aBkmkArr( 15, 15 );
//STRIP001      _SaveCntntIdx( this, rPos.nNode.GetIndex(), rPos.nContent.GetIndex(),
//STRIP001                      aBkmkArr, SAVEFLY_SPLIT );
//STRIP001
//STRIP001      pTNd = (SwTxtNode*)pTNd->SplitNode( rPos );
//STRIP001
//STRIP001      if( aBkmkArr.Count() )
//STRIP001          _RestoreCntntIdx( this, aBkmkArr, rPos.nNode.GetIndex()-1, 0, sal_True );
//STRIP001
//STRIP001      // jetzt noch den Pam berichtigen !!
//STRIP001      if( rPos.nNode == rPaM.GetMark()->nNode )
//STRIP001      {
//STRIP001          rPaM.GetMark()->nNode = rPos.nNode.GetIndex()-1;
//STRIP001          rPaM.GetMark()->nContent.Assign( pTNd, nMkCntnt );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // setze den Pam um einen "Inhalt" zurueck; dadurch steht er immer
//STRIP001  // ausserhalb des manipulierten Bereiches. Falls kein Inhalt mehr vor-
//STRIP001  // handen, dann auf den StartNode (es ist immer einer vorhanden !!!)
//STRIP001  sal_Bool bNullCntnt = !pSavePam->Move( fnMoveBackward, fnGoCntnt );
//STRIP001  if( bNullCntnt )
//STRIP001      pSavePam->GetPoint()->nNode--;
//STRIP001
//STRIP001  // kopiere alle Bookmarks, die im Move Bereich stehen in ein
//STRIP001  // Array, das alle Angaben auf die Position als Offset speichert.
//STRIP001  // Die neue Zuordung erfolgt nach dem Moven.
//STRIP001  SaveBookmarks aSaveBkmk;
//STRIP001  _DelBookmarks( pStt->nNode, pEnd->nNode, &aSaveBkmk,
//STRIP001                 &pStt->nContent, &pEnd->nContent );
//STRIP001
//STRIP001  // falls durch die vorherigen Loeschungen (z.B. der Fussnoten) kein
//STRIP001  // Bereich mehr existiert, ist das immernoch ein gueltiger Move!
//STRIP001  if( *rPaM.GetPoint() != *rPaM.GetMark() )
//STRIP001  {
//STRIP001      // jetzt kommt das eigentliche Verschieben
//STRIP001      GetNodes().Move( rPaM, rPos, GetNodes() );
//STRIP001
//STRIP001      if( rPaM.HasMark() )        // es wurde kein Move ausgefuehrt !!
//STRIP001      {
//STRIP001          delete pSavePam;
//STRIP001          delete pUndoMove;
//STRIP001          return sal_False;           // Nach einem Move() ist der GetMark geloescht
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rPaM.DeleteMark();
//STRIP001
//STRIP001      ASSERT( *pSavePam->GetMark() == rPos ||
//STRIP001          ( pSavePam->GetMark()->nNode.GetNode().GetCntntNode() == NULL ),
//STRIP001          "PaM wurde nicht verschoben, am Anfang/Ende keine ContentNodes?" );
//STRIP001  *pSavePam->GetMark() = rPos;
//STRIP001
//STRIP001  rPaM.SetMark();         // um den neuen Bereich eine Sel. aufspannen
//STRIP001  pTNd = pSavePam->GetNode()->GetTxtNode();
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      // korrigiere erstmal den Content vom SavePam
//STRIP001      if( bNullCntnt )
//STRIP001          pSavePam->GetPoint()->nContent = 0;
//STRIP001
//STRIP001      // die Methode SwEditShell::Move() fuegt nach dem Move den Text-Node
//STRIP001      // zusammen, in dem der rPaM steht. Wurde der Inhalt nach hinten
//STRIP001      // geschoben und liegt der SPoint vom SavePam im naechsten Node, so
//STRIP001      // muss beim Speichern vom Undo-Object das beachtet werden !!
//STRIP001      SwTxtNode * pPamTxtNd;
//STRIP001
//STRIP001      // wird ans SwUndoMove weitergegeben, das dann beim Undo JoinNext
//STRIP001      // aufruft. (falls es hier nicht moeglich ist).
//STRIP001      sal_Bool bJoin = bSplit && pTNd;
//STRIP001      bCorrSavePam = bCorrSavePam &&
//STRIP001                      0 != ( pPamTxtNd = rPaM.GetNode()->GetTxtNode() )
//STRIP001                      && pPamTxtNd->CanJoinNext()
//STRIP001                      && *rPaM.GetPoint() <= *pSavePam->GetPoint();
//STRIP001
//STRIP001      // muessen am SavePam 2 Nodes zusammengefasst werden ??
//STRIP001      if( bJoin && pTNd->CanJoinNext() )
//STRIP001      {
//STRIP001          pTNd->JoinNext();
//STRIP001          // kein temp. sdbcx::Index bei &&
//STRIP001          // es sollten wohl nur die Indexwerte verglichen werden.
//STRIP001          if( bCorrSavePam && rPaM.GetPoint()->nNode.GetIndex()+1 ==
//STRIP001                              pSavePam->GetPoint()->nNode.GetIndex() )
//STRIP001              pSavePam->GetPoint()->nContent += pPamTxtNd->Len();
//STRIP001          bJoin = sal_False;
//STRIP001      }
//STRIP001 //       else if( !bCorrSavePam && !pSavePam->Move( fnMoveForward, fnGoCntnt ))
//STRIP001      else if( !pSavePam->Move( fnMoveForward, fnGoCntnt ))
//STRIP001          pSavePam->GetPoint()->nNode++;
//STRIP001
//STRIP001      // zwischen SPoint und GetMark steht jetzt der neu eingefuegte Bereich
//STRIP001      pUndoMove->SetDestRange( *pSavePam, *rPaM.GetPoint(),
//STRIP001                                  bJoin, bCorrSavePam );
//STRIP001      AppendUndo( pUndoMove );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // muessen am SavePam 2 Nodes zusammengefasst werden ??
//STRIP001      if( bSplit && pTNd )
//STRIP001      {
//STRIP001          if( pTNd->CanJoinNext())
//STRIP001              pTNd->JoinNext();
//STRIP001      }
//STRIP001      if( bNullCntnt )
//STRIP001      {
//STRIP001          pSavePam->GetPoint()->nNode++;
//STRIP001          pSavePam->GetPoint()->nContent.Assign( pSavePam->GetCntntNode(), 0 );
//STRIP001      }
//STRIP001      else
//STRIP001          pSavePam->Move( fnMoveForward, fnGoCntnt );
//STRIP001  }
//STRIP001
//STRIP001  // setze jetzt wieder die text::Bookmarks in das Dokument
//STRIP001  *rPaM.GetMark() = *pSavePam->Start();
//STRIP001  for( sal_uInt16 n = 0; n < aSaveBkmk.Count(); ++n )
//STRIP001      aSaveBkmk[n]->SetInDoc( this, rPaM.GetMark()->nNode,
//STRIP001                                  &rPaM.GetMark()->nContent );
//STRIP001  *rPaM.GetPoint() = *pSavePam->End();
//STRIP001  delete pSavePam;
//STRIP001
//STRIP001  // verschiebe die Flys an die neue Position
//STRIP001  _RestFlyInRange( aSaveFlyArr, rPaM.Start()->nNode, &(rPos.nNode) );
//STRIP001
//STRIP001  if( bUpdateFtn )
//STRIP001  {
//STRIP001      if( aTmpFntIdx.Count() )
//STRIP001      {
//STRIP001          GetFtnIdxs().Insert( &aTmpFntIdx );
//STRIP001          aTmpFntIdx.Remove( sal_uInt16( 0 ), aTmpFntIdx.Count() );
//STRIP001      }
//STRIP001
//STRIP001      GetFtnIdxs().UpdateAllFtn();
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SwDoc::Move( SwNodeRange& rRange, SwNodeIndex& rPos, SwMoveFlags eMvFlags )
//STRIP001 {
//STRIP001  // bewegt alle Nodes an die neue Position. Dabei werden die
//STRIP001  // text::Bookmarks mit verschoben !! (zur Zeit ohne Undo)
//STRIP001
//STRIP001  // falls durchs Move Fussnoten in den Sonderbereich kommen sollten,
//STRIP001  // dann entferne sie jetzt.
//STRIP001  //JP 13.07.95:
//STRIP001  // ansonsten bei allen Fussnoten, die verschoben werden, die Frames
//STRIP001  // loeschen und nach dem Move wieder aufbauen lassen (Fussnoten koennen
//STRIP001  // die Seite wechseln). Zusaetzlich muss natuerlich die Sortierung
//STRIP001  // der FtnIdx-Array wieder korrigiert werden.
//STRIP001
//STRIP001  int bUpdateFtn = sal_False;
//STRIP001  SwFtnIdxs aTmpFntIdx;
//STRIP001
//STRIP001  SwUndoMove* pUndo = 0;
//STRIP001  if( (DOC_CREATEUNDOOBJ & eMvFlags ) && DoesUndo() )
//STRIP001      pUndo = new SwUndoMove( this, rRange, rPos );
//STRIP001  else
//STRIP001      bUpdateFtn = lcl_SaveFtn( rRange.aStart, rRange.aEnd, rPos,
//STRIP001                                  GetFtnIdxs(), aTmpFntIdx );
//STRIP001
//STRIP001  _SaveRedlines aSaveRedl( 0, 4 );
//STRIP001  SvPtrarr aSavRedlInsPosArr( 0, 4 );
//STRIP001  if( DOC_MOVEREDLINES & eMvFlags && GetRedlineTbl().Count() )
//STRIP001  {
//STRIP001      lcl_SaveRedlines( rRange, aSaveRedl );
//STRIP001
//STRIP001      // suche alle Redlines, die an der InsPos aufhoeren. Diese muessen
//STRIP001      // nach dem Move wieder an die "alte" Position verschoben werden
//STRIP001      sal_uInt16 nRedlPos = GetRedlinePos( rPos.GetNode() );
//STRIP001      if( USHRT_MAX != nRedlPos )
//STRIP001      {
//STRIP001          const SwPosition *pRStt, *pREnd;
//STRIP001          do {
//STRIP001              SwRedline* pTmp = GetRedlineTbl()[ nRedlPos ];
//STRIP001              pRStt = pTmp->Start();
//STRIP001              pREnd = pTmp->End();
//STRIP001              if( pREnd->nNode == rPos && pRStt->nNode < rPos )
//STRIP001              {
//STRIP001                  void* p = pTmp;
//STRIP001                  aSavRedlInsPosArr.Insert( p, aSavRedlInsPosArr.Count() );
//STRIP001              }
//STRIP001          } while( pRStt->nNode < rPos && ++nRedlPos < GetRedlineTbl().Count());
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // kopiere alle Bookmarks, die im Move Bereich stehen in ein
//STRIP001  // Array, das alle Angaben auf die Position als Offset speichert.
//STRIP001  // Die neue Zuordung erfolgt nach dem Moven.
//STRIP001  SaveBookmarks aSaveBkmk;
//STRIP001  _DelBookmarks( rRange.aStart, rRange.aEnd, &aSaveBkmk );
//STRIP001
//STRIP001  // sicher die absatzgebundenen Flys, damit verschoben werden koennen.
//STRIP001  _SaveFlyArr aSaveFlyArr;
//STRIP001  if( GetSpzFrmFmts()->Count() )
//STRIP001      _SaveFlyInRange( rRange, aSaveFlyArr );
//STRIP001
//STRIP001  // vor die Position setzen, damit er nicht weitergeschoben wird
//STRIP001  SwNodeIndex aIdx( rPos, -1 );
//STRIP001
//STRIP001  SwNodeIndex* pSaveInsPos = 0;
//STRIP001  if( pUndo )
//STRIP001      pSaveInsPos = new SwNodeIndex( rRange.aStart, -1 );
//STRIP001
//STRIP001  // verschiebe die Nodes
//STRIP001  if( GetNodes()._MoveNodes( rRange, GetNodes(), rPos ) )
//STRIP001  {
//STRIP001      aIdx++;     // wieder auf alte Position
//STRIP001      if( pSaveInsPos )
//STRIP001          (*pSaveInsPos)++;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aIdx = rRange.aStart;
//STRIP001      delete pUndo, pUndo = 0;
//STRIP001  }
//STRIP001
//STRIP001  // verschiebe die Flys an die neue Position
//STRIP001  if( aSaveFlyArr.Count() )
//STRIP001      _RestFlyInRange( aSaveFlyArr, aIdx, NULL );
//STRIP001
//STRIP001  // setze jetzt wieder die text::Bookmarks in das Dokument
//STRIP001  for( sal_uInt16 nCnt = 0; nCnt < aSaveBkmk.Count(); ++nCnt )
//STRIP001      aSaveBkmk[nCnt]->SetInDoc( this, aIdx );
//STRIP001
//STRIP001  if( aSavRedlInsPosArr.Count() )
//STRIP001  {
//STRIP001      SwNode* pNewNd = &aIdx.GetNode();
//STRIP001      for( sal_uInt16 n = 0; n < aSavRedlInsPosArr.Count(); ++n )
//STRIP001      {
//STRIP001          SwRedline* pTmp = (SwRedline*)aSavRedlInsPosArr[ n ];
//STRIP001          if( USHRT_MAX != GetRedlineTbl().GetPos( pTmp ) )
//STRIP001          {
//STRIP001              SwPosition* pEnd = pTmp->End();
//STRIP001              pEnd->nNode = aIdx;
//STRIP001              pEnd->nContent.Assign( pNewNd->GetCntntNode(), 0 );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( aSaveRedl.Count() )
//STRIP001      lcl_RestoreRedlines( this, aIdx.GetIndex(), aSaveRedl );
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndo->SetDestRange( aIdx, rPos, *pSaveInsPos );
//STRIP001      AppendUndo( pUndo );
//STRIP001  }
//STRIP001
//STRIP001  if( pSaveInsPos )
//STRIP001      delete pSaveInsPos;
//STRIP001
//STRIP001  if( bUpdateFtn )
//STRIP001  {
//STRIP001      if( aTmpFntIdx.Count() )
//STRIP001      {
//STRIP001          GetFtnIdxs().Insert( &aTmpFntIdx );
//STRIP001          aTmpFntIdx.Remove( sal_uInt16( 0 ), aTmpFntIdx.Count() );
//STRIP001      }
//STRIP001
//STRIP001      GetFtnIdxs().UpdateAllFtn();
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  return sal_True;
//STRIP001 }

/* #107318# Convert list of ranges of whichIds to a corresponding list
    of whichIds*/
//STRIP001 SvUShorts * lcl_RangesToUShorts(USHORT * pRanges)
//STRIP001 {
//STRIP001     SvUShorts * pResult = new SvUShorts();
//STRIP001
//STRIP001     int i = 0;
//STRIP001     while (pRanges[i] != 0)
//STRIP001     {
//STRIP001         ASSERT(pRanges[i+1] != 0, "malformed ranges");
//STRIP001
//STRIP001         for (USHORT j = pRanges[i]; j < pRanges[i+1]; j++)
//STRIP001             pResult->Insert(j, pResult->Count());
//STRIP001
//STRIP001         i += 2;
//STRIP001     }
//STRIP001
//STRIP001     return pResult;
//STRIP001 }

/*N*/ void lcl_GetJoinFlags( SwPaM& rPam, sal_Bool& rJoinTxt, sal_Bool& rJoinPrev )
/*N*/ {
/*N*/   if( rPam.GetPoint()->nNode != rPam.GetMark()->nNode )
/*N*/   {
/*N*/       const SwPosition* pStt = rPam.Start(), *pEnd = rPam.End();
/*N*/       SwTxtNode* pTxtNd = pStt->nNode.GetNode().GetTxtNode();
/*N*/       rJoinTxt = (0 != pTxtNd) && pEnd->nNode.GetNode().IsTxtNode();
/*N*/
/*N*/       if( rJoinTxt && pStt == rPam.GetPoint() &&
/*N*/           0 != ( pTxtNd = pEnd->nNode.GetNode().GetTxtNode() ) &&
/*N*/           pTxtNd->GetTxt().Len() == pEnd->nContent.GetIndex() )
/*N*/       {
/*?*/           rPam.Exchange();
/*?*/           rJoinPrev = sal_False;
/*N*/       }
/*N*/       else
/*N*/           rJoinPrev = rJoinTxt && rPam.GetPoint() == pStt;
/*N*/   }
/*N*/   else
/*N*/       rJoinTxt = sal_False, rJoinPrev = sal_False;
/*N*/ }

/*N*/ void lcl_JoinText( SwPaM& rPam, sal_Bool bJoinPrev )
/*N*/ {
/*N*/   SwNodeIndex aIdx( rPam.GetPoint()->nNode );
/*N*/   SwTxtNode *pTxtNd = aIdx.GetNode().GetTxtNode();
/*N*/   SwNodeIndex aOldIdx( aIdx );
/*N*/   SwTxtNode *pOldTxtNd = pTxtNd;
/*N*/
/*N*/   if( pTxtNd && pTxtNd->CanJoinNext( &aIdx ) )
/*N*/   {
/*N*/       SwDoc* pDoc = rPam.GetDoc();
/*N*/       if( bJoinPrev )
/*N*/       {
/*N*/           {
/*N*/               // falls PageBreaks geloescht / gesetzt werden, darf das
/*N*/               // nicht in die Undo-History aufgenommen werden !!
/*N*/               // (das loeschen vom Node geht auch am Undo vorbei !!!)
/*N*/               sal_Bool bDoUndo = pDoc->DoesUndo();
/*N*/               pDoc->DoUndo( sal_False );
/*N*/
/*N*/               /* PageBreaks, PageDesc, ColumnBreaks */
/*N*/               // Sollte an der Logik zum Kopieren der PageBreak's ...
/*N*/               // etwas geaendert werden, muss es auch im SwUndoDelete
/*N*/               // geandert werden. Dort wird sich das AUTO-PageBreak
/*N*/               // aus dem GetMarkNode kopiert.!!!
/*N*/
/*N*/               /* Der GetMarkNode */
/*N*/               if( ( pTxtNd = aIdx.GetNode().GetTxtNode())->GetpSwAttrSet() )
/*N*/               {
/*?*/                   const SfxPoolItem* pItem;
/*?*/                   if( SFX_ITEM_SET == pTxtNd->GetpSwAttrSet()->GetItemState(
/*?*/                       RES_BREAK, sal_False, &pItem ) )
/*?*/                       pTxtNd->ResetAttr( RES_BREAK );
/*?*/                   if( pTxtNd->GetpSwAttrSet() &&
/*?*/                       SFX_ITEM_SET == pTxtNd->GetpSwAttrSet()->GetItemState(
/*?*/                       RES_PAGEDESC, sal_False, &pItem ) )
/*?*/                       pTxtNd->ResetAttr( RES_PAGEDESC );
/*N*/               }
/*N*/
/*N*/               /* Der PointNode */
/*N*/               if( pOldTxtNd->GetpSwAttrSet() )
/*N*/               {
/*?*/                   const SfxPoolItem* pItem;
/*?*/                   SfxItemSet aSet( pDoc->GetAttrPool(), aBreakSetRange );
/*?*/                   SfxItemSet* pSet = pOldTxtNd->GetpSwAttrSet();
/*?*/                   if( SFX_ITEM_SET == pSet->GetItemState( RES_BREAK,
/*?*/                       sal_False, &pItem ) )
/*?*/                       aSet.Put( *pItem );
/*?*/                   if( SFX_ITEM_SET == pSet->GetItemState( RES_PAGEDESC,
/*?*/                       sal_False, &pItem ) )
/*?*/                       aSet.Put( *pItem );
/*?*/                   if( aSet.Count() )
/*?*/                       pTxtNd->SwCntntNode::SetAttr( aSet );
/*N*/               }
/*N*/               pOldTxtNd->FmtToTxtAttr( pTxtNd );
/*N*/
/*N*/               SvULongs aBkmkArr( 15, 15 );
/*N*/               ::_SaveCntntIdx( pDoc, aOldIdx.GetIndex(),
/*N*/                                   pOldTxtNd->Len(), aBkmkArr );
/*N*/
/*N*/               SwIndex aAlphaIdx(pTxtNd);
/*N*/               pOldTxtNd->Cut( pTxtNd, aAlphaIdx, SwIndex(pOldTxtNd),
/*N*/                                   pOldTxtNd->Len() );
/*N*/               SwPosition aAlphaPos( aIdx, aAlphaIdx );
/*N*/               pDoc->CorrRel( rPam.GetPoint()->nNode, aAlphaPos, 0, sal_True );
/*N*/
/*N*/               // verschiebe noch alle Bookmarks/TOXMarks
/*N*/               if( aBkmkArr.Count() )
/*?*/                   {DBG_ASSERT(0, "STRIP");} //STRIP001 ::_RestoreCntntIdx( pDoc, aBkmkArr, aIdx.GetIndex() );
/*N*/
/*N*/               pDoc->DoUndo( bDoUndo );
/*N*/
/*N*/               // falls der uebergebene PaM nicht im Crsr-Ring steht,
/*N*/               // gesondert behandeln (z.B. Aufruf aus dem Auto-Format)
/*N*/               if( pOldTxtNd == rPam.GetBound( sal_True ).nContent.GetIdxReg() )
/*?*/                   rPam.GetBound( sal_True ) = aAlphaPos;
/*N*/               if( pOldTxtNd == rPam.GetBound( sal_False ).nContent.GetIdxReg() )
/*?*/                   rPam.GetBound( sal_False ) = aAlphaPos;
/*N*/           }
/*N*/           // jetzt nur noch den Node loeschen
/*N*/           pDoc->GetNodes().Delete( aOldIdx, 1 );
/*N*/       }
/*N*/       else
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            SwTxtNode* pDelNd = aIdx.GetNode().GetTxtNode();
//STRIP001 /*?*/            if( pTxtNd->Len() )
//STRIP001 /*?*/                pDelNd->FmtToTxtAttr( pTxtNd );
//STRIP001 /*?*/            else
//STRIP001 /*?*/           {
//STRIP001                 /* #107318# This case was missed:
//STRIP001
//STRIP001                     <something></something>   <-- pTxtNd
//STRIP001                     <other>ccc</other>        <-- pDelNd
//STRIP001
//STRIP001                    <something> and <other> are paragraph
//STRIP001                    attributes. The attribute <something> stayed if not
//STRIP001                    overwritten by an attribute in "ccc". Fixed by
//STRIP001                    first resetting all character attributes in first
//STRIP001                    paragraph (pTxtNd).
//STRIP001                 */
//STRIP001 /*?*/                 SvUShorts * pShorts =
//STRIP001 /*?*/                     lcl_RangesToUShorts(aCharFmtSetRange);
//STRIP001 /*?*/                 pTxtNd->ResetAttr(*pShorts);
//STRIP001 /*?*/                 delete pShorts;
//STRIP001 /*?*/
//STRIP001 /*?*/               if( pDelNd->GetpSwAttrSet() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                // nur die Zeichenattribute kopieren
//STRIP001 /*?*/                SfxItemSet aTmpSet( pDoc->GetAttrPool(), aCharFmtSetRange );
//STRIP001 /*?*/                aTmpSet.Put( *pDelNd->GetpSwAttrSet() );
//STRIP001 /*?*/                pTxtNd->SwCntntNode::SetAttr( aTmpSet );
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/                pDoc->CorrRel( aIdx, *rPam.GetPoint(), 0, sal_True );
//STRIP001 /*?*/                pTxtNd->JoinNext();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ sal_Bool SwDoc::DeleteAndJoin( SwPaM & rPam )
/*N*/ {
/*N*/   if( IsRedlineOn() )
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  sal_uInt16 nUndoSize = 0;
//STRIP001 /*?*/        SwUndoRedlineDelete* pUndo = 0;
//STRIP001 /*?*/        SwRedlineMode eOld = GetRedlineMode();
//STRIP001      checkRedlining(eOld);
//STRIP001 /*?*/        if( DoesUndo() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ClearRedo();
//STRIP001 /*?*/
//STRIP001 /*?*/ //JP 06.01.98: MUSS noch optimiert werden!!!
//STRIP001 /*?*/ SetRedlineMode( REDLINE_ON | REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE );
//STRIP001 /*?*/
//STRIP001 /*?*/            nUndoSize = pUndos->Count();
//STRIP001 /*?*/            StartUndo();
//STRIP001 /*?*/            AppendUndo( pUndo = new SwUndoRedlineDelete( rPam, UNDO_DELETE ));
//STRIP001 /*?*/        }
//STRIP001 /*?*/        AppendRedline( new SwRedline( REDLINE_DELETE, rPam ));
//STRIP001 /*?*/        SetModified();
//STRIP001 /*?*/
//STRIP001 /*?*/        if( pUndo )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            EndUndo();
//STRIP001 /*?*/            SwUndo* pPrevUndo;
//STRIP001 /*?*/            if( nUndoSize && DoesGroupUndo() &&
//STRIP001 /*?*/                nUndoSize + 1 == pUndos->Count() &&
//STRIP001 /*?*/                UNDO_REDLINE == ( pPrevUndo = (*pUndos)[ nUndoSize-1 ])->GetId() &&
//STRIP001 /*?*/                UNDO_DELETE == ((SwUndoRedline*)pPrevUndo)->GetUserId() &&
//STRIP001 /*?*/                ((SwUndoRedlineDelete*)pPrevUndo)->CanGrouping( *pUndo ))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                DoUndo( sal_False );
//STRIP001 /*?*/                pUndos->DeleteAndDestroy( nUndoSize, 1 );
//STRIP001 /*?*/                --nUndoPos, --nUndoCnt;
//STRIP001 /*?*/                DoUndo( sal_True );
//STRIP001 /*?*/            }
//STRIP001 /*?*/ //JP 06.01.98: MUSS noch optimiert werden!!!
//STRIP001 /*?*/ SetRedlineMode( eOld );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        return sal_True;
/*N*/   }
/*N*/
/*N*/   sal_Bool bJoinTxt, bJoinPrev;
/*N*/   lcl_GetJoinFlags( rPam, bJoinTxt, bJoinPrev );
/*N*/
/*N*/   {
/*N*/       // dann eine Kopie vom Cursor erzeugen um alle Pams aus den
/*N*/       // anderen Sichten aus dem Loeschbereich zu verschieben
/*N*/       // ABER NICHT SICH SELBST !!
/*N*/       SwPaM aDelPam( *rPam.GetMark(), *rPam.GetPoint() );
/*N*/       ::PaMCorrAbs( aDelPam, *aDelPam.GetPoint() );
/*N*/
/*N*/       if( !Delete( aDelPam ) )
/*N*/           return sal_False;
/*N*/
/*N*/       *rPam.GetPoint() = *aDelPam.GetPoint();
/*N*/   }
/*N*/
/*N*/   if( bJoinTxt )
/*N*/       lcl_JoinText( rPam, bJoinPrev );
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SwDoc::Delete( SwPaM & rPam )
/*N*/ {
/*N*/   SwPosition *pStt = (SwPosition*)rPam.Start(), *pEnd = (SwPosition*)rPam.End();
/*N*/
/*N*/   if( !rPam.HasMark() || *pStt >= *pEnd )
/*N*/       return sal_False;
/*N*/
/*N*/   if( pACEWord )
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  // ggfs. das gesicherte Word fuer die Ausnahme
//STRIP001 /*?*/        if( pACEWord->IsDeleted() ||  pStt->nNode != pEnd->nNode ||
//STRIP001 /*?*/            pStt->nContent.GetIndex() + 1 != pEnd->nContent.GetIndex() ||
//STRIP001 /*?*/            !pACEWord->CheckDelChar( *pStt ))
//STRIP001 /*?*/            delete pACEWord, pACEWord = 0;
/*N*/   }
/*N*/
/*N*/   {
/*N*/       // loesche alle leeren TextHints an der Mark-Position
/*N*/       SwTxtNode* pTxtNd = rPam.GetMark()->nNode.GetNode().GetTxtNode();
/*N*/       SwpHints* pHts;
/*N*/       if( pTxtNd &&  0 != ( pHts = pTxtNd->GetpSwpHints()) && pHts->Count() )
/*N*/       {
/*N*/           const xub_StrLen *pEndIdx;
/*N*/           xub_StrLen nMkCntPos = rPam.GetMark()->nContent.GetIndex();
/*N*/           for( sal_uInt16 n = pHts->Count(); n; )
/*N*/           {
/*N*/               const SwTxtAttr* pAttr = (*pHts)[ --n ];
/*N*/               if( nMkCntPos > *pAttr->GetStart() )
/*N*/                   break;
/*N*/
/*N*/               if( nMkCntPos == *pAttr->GetStart() &&
/*N*/                   0 != (pEndIdx = pAttr->GetEnd()) &&
/*N*/                   *pEndIdx == *pAttr->GetStart() )
/*?*/                   pTxtNd->DestroyAttr( pHts->Cut( n ) );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   {
/*N*/       // Bug 26675:   DataChanged vorm loeschen verschicken, dann bekommt
/*N*/       //          man noch mit, welche Objecte sich im Bereich befinden.
/*N*/       //          Danach koennen sie vor/hinter der Position befinden.
/*N*/       SwDataChanged aTmp( rPam, 0 );
/*N*/   }
/*N*/
/*N*/
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       sal_uInt16 nUndoSize = pUndos->Count();
/*N*/       SwUndo * pUndo;
/*N*/       if( DoesGroupUndo() && nUndoSize-- &&
/*N*/           UNDO_DELETE == ( pUndo = (*pUndos)[ nUndoSize ])->GetId() &&
/*N*/           ((SwUndoDelete*)pUndo)->CanGrouping( this, rPam ))
/*N*/           ;// wenn CanGrouping() sal_True returnt, ist schon alles erledigt
/*N*/       else
/*N*/           AppendUndo( new SwUndoDelete( rPam ) );
/*N*/
/*N*/       SetModified();
/*N*/
/*N*/       return sal_True;
/*N*/   }
/*N*/
/*?*/   if( !IsIgnoreRedline() && GetRedlineTbl().Count() )
/*?*/       DeleteRedline( rPam );
/*?*/
/*?*/   // loesche und verschiebe erstmal alle "Fly's am Absatz", die in der
/*?*/   // SSelection liegen
/*?*/   DelFlyInRange( rPam.GetMark()->nNode, rPam.GetPoint()->nNode );
/*?*/   _DelBookmarks( pStt->nNode, pEnd->nNode, 0,
/*?*/                   &pStt->nContent, &pEnd->nContent );
/*?*/
/*?*/   SwNodeIndex aSttIdx( pStt->nNode );
/*?*/   SwCntntNode * pCNd = aSttIdx.GetNode().GetCntntNode();
/*?*/
/*?*/   do {        // middle checked loop!
/*?*/       if( pCNd )
/*?*/       {
/*?*/           if( pCNd->GetTxtNode() )
/*?*/           {
/*?*/               // verschiebe jetzt noch den Inhalt in den neuen Node
/*?*/               sal_Bool bOneNd = pStt->nNode == pEnd->nNode;
/*?*/               xub_StrLen nLen = ( bOneNd ? pEnd->nContent.GetIndex()
/*?*/                                          : pCNd->Len() )
/*?*/                                       - pStt->nContent.GetIndex();
/*?*/
/*?*/               // falls schon leer, dann nicht noch aufrufen
/*?*/               if( nLen )
/*?*/                   ((SwTxtNode*)pCNd)->Erase( pStt->nContent, nLen );
/*?*/
/*?*/               if( bOneNd )        // das wars schon
/*?*/                   break;
/*?*/
/*?*/               aSttIdx++;
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               // damit beim loeschen keine Indizies mehr angemeldet sind,
/*?*/               // wird hier der SwPaM aus dem Content entfernt !!
/*?*/               pStt->nContent.Assign( 0, 0 );
/*?*/           }
/*?*/       }
/*?*/
/*?*/       sal_uInt32 nEnde = pEnd->nNode.GetIndex();
/*?*/       pCNd = pEnd->nNode.GetNode().GetCntntNode();
/*?*/       if( pCNd )
/*?*/       {
/*?*/           if( pCNd->GetTxtNode() )
/*?*/           {
/*?*/               // falls schon leer, dann nicht noch aufrufen
/*?*/               if( pEnd->nContent.GetIndex() )
/*?*/               {
/*?*/                   SwIndex aIdx( pCNd, 0 );
/*?*/                   ((SwTxtNode*)pCNd)->Erase( aIdx, pEnd->nContent.GetIndex() );
/*?*/               }
/*?*/               nEnde--;
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               // damit beim Loeschen keine Indizies mehr angemeldet sind,
/*?*/               // wird hier der SwPaM aus dem Content entfernt !!
/*?*/               pEnd->nContent.Assign( 0, 0 );
/*?*/               nEnde--;
/*?*/           }
/*?*/       }
/*?*/
/*?*/       nEnde++;
/*?*/       if( aSttIdx != nEnde )
/*?*/       {
/*?*/           // loesche jetzt die Nodes in das NodesArary
/*?*/           GetNodes().Delete( aSttIdx, nEnde - aSttIdx.GetIndex() );
/*?*/       }
/*?*/
/*?*/       // falls der Node geloescht wurde, in dem der Cursor stand, so
/*?*/       // muss der Content im akt. Content angemeldet werden !!!
/*?*/       pStt->nContent.Assign( pStt->nNode.GetNode().GetCntntNode(),
/*?*/                               pStt->nContent.GetIndex() );
/*?*/
/*?*/       // der PaM wird korrigiert, denn falls ueber Nodegrenzen geloescht
/*?*/       // wurde, so stehen sie in unterschieden Nodes. Auch die Selektion
/*?*/       // wird aufgehoben !
/*?*/       *pEnd = *pStt;
/*?*/       rPam.DeleteMark();
/*?*/
/*?*/   } while( sal_False );
/*?*/
/*?*/   if( !IsIgnoreRedline() && GetRedlineTbl().Count() )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    CompressRedlines();
/*?*/   SetModified();
/*?*/
/*?*/   return sal_True;
/*N*/ }


//STRIP001 uno::Any SwDoc::Spell( SwPaM& rPaM,
//STRIP001                  uno::Reference< XSpellChecker1 >  &xSpeller,
//STRIP001                     sal_uInt16* pPageCnt, sal_uInt16* pPageSt,
//STRIP001                     sal_Bool bIsConversion ) const
//STRIP001 {
//STRIP001  SwPosition* pSttPos = rPaM.Start(), *pEndPos = rPaM.End();
//STRIP001  uno::Reference< beans::XPropertySet >  xProp( ::GetLinguPropertySet() );
//STRIP001     sal_Bool bReverse = (!bIsConversion && xProp.is()) ?
//STRIP001          *(sal_Bool*)xProp->getPropertyValue( S2U(UPN_IS_WRAP_REVERSE) ).getValue() : sal_False;
//STRIP001
//STRIP001     SwSpellArgs      *pSpellArgs = 0;
//STRIP001     SwConversionArgs *pConvArgs  = 0;
//STRIP001     if (bIsConversion)
//STRIP001         pConvArgs =  new SwConversionArgs(
//STRIP001                             pSttPos->nNode.GetNode().GetTxtNode(), pSttPos->nContent,
//STRIP001                             pEndPos->nNode.GetNode().GetTxtNode(), pEndPos->nContent );
//STRIP001     else
//STRIP001         pSpellArgs = new SwSpellArgs( xSpeller,
//STRIP001                             pSttPos->nNode.GetNode().GetTxtNode(), pSttPos->nContent,
//STRIP001                             pEndPos->nNode.GetNode().GetTxtNode(), pEndPos->nContent );
//STRIP001
//STRIP001  sal_uInt32 nCurrNd = pSttPos->nNode.GetIndex();
//STRIP001  sal_uInt32 nEndNd = pEndPos->nNode.GetIndex();
//STRIP001
//STRIP001  if( nCurrNd <= nEndNd )
//STRIP001  {
//STRIP001      SwCntntFrm* pCntFrm;
//STRIP001      sal_uInt32 nCount = nEndNd - nCurrNd;
//STRIP001      if( bReverse )
//STRIP001      {
//STRIP001          nCurrNd = nEndNd;
//STRIP001          nEndNd = nCurrNd - nCount;
//STRIP001      }
//STRIP001      sal_Bool bGoOn = sal_True;
//STRIP001      while( bGoOn )
//STRIP001      {
//STRIP001          SwNode* pNd = GetNodes()[ nCurrNd ];
//STRIP001          switch( pNd->GetNodeType() )
//STRIP001          {
//STRIP001          case ND_TEXTNODE:
//STRIP001              if( 0 != ( pCntFrm = ((SwTxtNode*)pNd)->GetFrm()) )
//STRIP001              {
//STRIP001                  // geschutze Cellen/Flys ueberspringen, ausgeblendete
//STRIP001                  //ebenfalls
//STRIP001                  if( pCntFrm->IsProtected() )
//STRIP001                  {
//STRIP001                      nCurrNd = bReverse ? pNd->StartOfSectionIndex()
//STRIP001                                         : pNd->EndOfSectionIndex();
//STRIP001                  }
//STRIP001                  else if( !((SwTxtFrm*)pCntFrm)->IsHiddenNow() )
//STRIP001                  {
//STRIP001                      if( pPageCnt && *pPageCnt && pPageSt )
//STRIP001                      {
//STRIP001                          sal_uInt16 nPageNr = pCntFrm->GetPhyPageNum();
//STRIP001                          if( !*pPageSt )
//STRIP001                          {
//STRIP001                              *pPageSt = nPageNr;
//STRIP001                              if( *pPageCnt < *pPageSt )
//STRIP001                                  *pPageCnt = *pPageSt;
//STRIP001                          }
//STRIP001                          long nStat;
//STRIP001                          if( nPageNr >= *pPageSt )
//STRIP001                              nStat = bReverse ?
//STRIP001                                  *pPageCnt - nPageNr + *pPageSt + 1 :
//STRIP001                                  nPageNr - *pPageSt + 1;
//STRIP001                          else
//STRIP001                              nStat = bReverse ?
//STRIP001                                  *pPageSt - nPageNr + 1 :
//STRIP001                                  nPageNr + *pPageCnt - *pPageSt + 1;
//STRIP001                          ::SetProgressState( nStat, (SwDocShell*)GetDocShell() );
//STRIP001                      }
//STRIP001                         if( (!bIsConversion &&
//STRIP001                                 ((SwTxtNode*)pNd)->Spell( pSpellArgs )) ||
//STRIP001                             ( bIsConversion &&
//STRIP001                                 ((SwTxtNode*)pNd)->Convert( *pConvArgs )))
//STRIP001                      {
//STRIP001                          // Abbrechen und Position merken
//STRIP001                          pSttPos->nNode = nCurrNd;
//STRIP001                          pEndPos->nNode = nCurrNd;
//STRIP001                          nCurrNd = nEndNd;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          case ND_SECTIONNODE:
//STRIP001              if( !bReverse &&
//STRIP001                  ( ((SwSectionNode*)pNd)->GetSection().IsProtect() ||
//STRIP001                  ((SwSectionNode*)pNd)->GetSection().IsHidden() ) )
//STRIP001                  nCurrNd = pNd->EndOfSectionIndex();
//STRIP001              break;
//STRIP001          case ND_ENDNODE:
//STRIP001              {
//STRIP001                  SwNode* pTmp;
//STRIP001                  if( bReverse && 0 != (pTmp = pNd->StartOfSectionNode() ) &&
//STRIP001                      ND_SECTIONNODE == pTmp->GetNodeType() &&
//STRIP001                      ( ((SwSectionNode*)pTmp)->GetSection().IsProtect() ||
//STRIP001                          ((SwSectionNode*)pTmp)->GetSection().IsHidden() ) )
//STRIP001                      nCurrNd = pNd->StartOfSectionIndex();
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( bReverse )
//STRIP001          {
//STRIP001              bGoOn = nCurrNd > nEndNd;
//STRIP001              if( bGoOn )
//STRIP001                  --nCurrNd;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              bGoOn = nCurrNd < nEndNd;
//STRIP001              ++nCurrNd;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     uno::Any aRes;
//STRIP001     if (bIsConversion)
//STRIP001         aRes <<= pConvArgs->aConvText;
//STRIP001     else
//STRIP001         aRes <<= pSpellArgs->xSpellAlt;
//STRIP001     delete pSpellArgs;
//STRIP001     delete pConvArgs;
//STRIP001
//STRIP001     return aRes;
//STRIP001 }

//STRIP001 class SwHyphArgs : public SwInterHyphInfo
//STRIP001 {
//STRIP001  const SwNode *pStart;
//STRIP001  const SwNode *pEnd;
//STRIP001        SwNode *pNode;
//STRIP001  sal_uInt16 *pPageCnt;
//STRIP001  sal_uInt16 *pPageSt;
//STRIP001
//STRIP001  sal_uInt32 nNode;
//STRIP001  xub_StrLen nPamStart;
//STRIP001  xub_StrLen nPamLen;
//STRIP001
//STRIP001 public:
//STRIP001       SwHyphArgs( const SwPaM *pPam, const Point &rPoint,
//STRIP001                       sal_uInt16* pPageCount, sal_uInt16* pPageStart );
//STRIP001  void SetPam( SwPaM *pPam ) const;
//STRIP001  inline void SetNode( SwNode *pNew ) { pNode = pNew; }
//STRIP001  inline const SwNode *GetNode() const { return pNode; }
//STRIP001  inline void SetRange( const SwNode *pNew );
//STRIP001  inline void NextNode() { ++nNode; }
//STRIP001  inline sal_uInt16 *GetPageCnt() { return pPageCnt; }
//STRIP001  inline sal_uInt16 *GetPageSt() { return pPageSt; }
//STRIP001 };

//STRIP001 SwHyphArgs::SwHyphArgs( const SwPaM *pPam, const Point &rCrsrPos,
//STRIP001                       sal_uInt16* pPageCount, sal_uInt16* pPageStart )
//STRIP001   : SwInterHyphInfo( rCrsrPos ), pNode(0),
//STRIP001   pPageCnt( pPageCount ), pPageSt( pPageStart )
//STRIP001 {
//STRIP001  // Folgende Bedingungen muessen eingehalten werden:
//STRIP001  // 1) es gibt mindestens eine Selektion
//STRIP001  // 2) SPoint() == Start()
//STRIP001  ASSERT( pPam->HasMark(), "SwDoc::Hyphenate: blowing in the wind");
//STRIP001  ASSERT( *pPam->GetPoint() <= *pPam->GetMark(),
//STRIP001          "SwDoc::Hyphenate: New York, New York");
//STRIP001
//STRIP001  const SwNodes &rNds = pPam->GetDoc()->GetNodes();
//STRIP001  const SwPosition *pPoint = pPam->GetPoint();
//STRIP001  nNode = pPoint->nNode.GetIndex();
//STRIP001
//STRIP001  // Start einstellen
//STRIP001  pStart = pPoint->nNode.GetNode().GetTxtNode();
//STRIP001  nPamStart = pPoint->nContent.GetIndex();
//STRIP001
//STRIP001  // Ende und Laenge einstellen.
//STRIP001  const SwPosition *pMark = pPam->GetMark();
//STRIP001  pEnd = pMark->nNode.GetNode().GetTxtNode();
//STRIP001  nPamLen = pMark->nContent.GetIndex();
//STRIP001  if( pPoint->nNode == pMark->nNode )
//STRIP001      nPamLen -= pPoint->nContent.GetIndex();
//STRIP001 }

//STRIP001 inline void SwHyphArgs::SetRange( const SwNode *pNew )
//STRIP001 {
//STRIP001  nStart = pStart == pNew ? nPamStart : 0;
//STRIP001  nLen   = pEnd   == pNew ? nPamLen : STRING_NOTFOUND;
//STRIP001 }

//STRIP001 void SwHyphArgs::SetPam( SwPaM *pPam ) const
//STRIP001 {
//STRIP001  if( !pNode )
//STRIP001      *pPam->GetPoint() = *pPam->GetMark();
//STRIP001  else
//STRIP001  {
//STRIP001      pPam->GetPoint()->nNode = nNode;
//STRIP001      pPam->GetPoint()->nContent.Assign( pNode->GetCntntNode(), nWordStart );
//STRIP001      pPam->GetMark()->nNode = nNode;
//STRIP001      pPam->GetMark()->nContent.Assign( pNode->GetCntntNode(),
//STRIP001                                        nWordStart + nWordLen );
//STRIP001      ASSERT( nNode == pNode->GetIndex(),
//STRIP001              "SwHyphArgs::SetPam: Pam desaster" );
//STRIP001  }
//STRIP001 }

// liefert sal_True zurueck, wenn es weitergehen soll.
//STRIP001 sal_Bool lcl_HyphenateNode( const SwNodePtr& rpNd, void* pArgs )
//STRIP001 {
//STRIP001  // Hyphenate liefert sal_True zurueck, wenn eine Trennstelle anliegt
//STRIP001  // und stellt pPam ein.
//STRIP001  SwTxtNode *pNode = rpNd->GetTxtNode();
//STRIP001  SwHyphArgs *pHyphArgs = (SwHyphArgs*)pArgs;
//STRIP001  if( pNode )
//STRIP001  {
//STRIP001      SwCntntFrm* pCntFrm = pNode->GetFrm();
//STRIP001      if( pCntFrm && !((SwTxtFrm*)pCntFrm)->IsHiddenNow() )
//STRIP001      {
//STRIP001          sal_uInt16 *pPageSt = pHyphArgs->GetPageSt();
//STRIP001          sal_uInt16 *pPageCnt = pHyphArgs->GetPageCnt();
//STRIP001          if( pPageCnt && *pPageCnt && pPageSt )
//STRIP001          {
//STRIP001              sal_uInt16 nPageNr = pCntFrm->GetPhyPageNum();
//STRIP001              if( !*pPageSt )
//STRIP001              {
//STRIP001                  *pPageSt = nPageNr;
//STRIP001                  if( *pPageCnt < *pPageSt )
//STRIP001                      *pPageCnt = *pPageSt;
//STRIP001              }
//STRIP001              long nStat = nPageNr >= *pPageSt ? nPageNr - *pPageSt + 1
//STRIP001                                       : nPageNr + *pPageCnt - *pPageSt + 1;
//STRIP001              ::SetProgressState( nStat, (SwDocShell*)pNode->GetDoc()->GetDocShell() );
//STRIP001          }
//STRIP001          pHyphArgs->SetRange( rpNd );
//STRIP001          if( pNode->Hyphenate( *pHyphArgs ) )
//STRIP001          {
//STRIP001              pHyphArgs->SetNode( rpNd );
//STRIP001              return sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pHyphArgs->NextNode();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 uno::Reference< XHyphenatedWord >  SwDoc::Hyphenate(
//STRIP001                          SwPaM *pPam, const Point &rCrsrPos,
//STRIP001                          sal_uInt16* pPageCnt, sal_uInt16* pPageSt )
//STRIP001 {
//STRIP001  ASSERT(this == pPam->GetDoc(), "SwDoc::Hyphenate: strangers in the night");
//STRIP001
//STRIP001  if( *pPam->GetPoint() > *pPam->GetMark() )
//STRIP001      pPam->Exchange();
//STRIP001
//STRIP001  SwHyphArgs aHyphArg( pPam, rCrsrPos, pPageCnt, pPageSt );
//STRIP001  SwNodeIndex aTmpIdx( pPam->GetMark()->nNode, 1 );
//STRIP001  GetNodes().ForEach( pPam->GetPoint()->nNode, aTmpIdx,
//STRIP001                  lcl_HyphenateNode, &aHyphArg );
//STRIP001  aHyphArg.SetPam( pPam );
//STRIP001  return aHyphArg.GetHyphWord();  // will be set by lcl_HyphenateNode
//STRIP001 }

//STRIP001 void ReplaceTabsStr( String& rStr, const String& rSrch, const String& rRepl )
//STRIP001 {
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  while( STRING_NOTFOUND != ( nPos = rStr.Search( rSrch, nPos )) )
//STRIP001  {
//STRIP001      // wurde das escaped?
//STRIP001      if( nPos && '\\' == rStr.GetChar( nPos-1 ))
//STRIP001      {
//STRIP001          // noch nicht am Ende ??
//STRIP001          rStr.Erase( nPos-1, 1 );        // den \\ noch loeschen
//STRIP001          if( nPos >= rStr.Len() )
//STRIP001              break;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rStr.Erase( nPos, rSrch.Len() );
//STRIP001          rStr.Insert( rRepl, nPos );
//STRIP001          nPos += rRepl.Len();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 sal_Bool lcl_GetTokenToParaBreak( String& rStr, String& rRet, sal_Bool bRegExpRplc )
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  if( bRegExpRplc )
//STRIP001  {
//STRIP001      xub_StrLen nPos = 0;
//STRIP001      String sPara( String::CreateFromAscii(
//STRIP001                                  RTL_CONSTASCII_STRINGPARAM( "\\n" )));
//STRIP001      while( STRING_NOTFOUND != ( nPos = rStr.Search( sPara, nPos )) )
//STRIP001      {
//STRIP001          // wurde das escaped?
//STRIP001          if( nPos && '\\' == rStr.GetChar( nPos-1 ))
//STRIP001          {
//STRIP001              if( ++nPos >= rStr.Len() )
//STRIP001                  break;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rRet = rStr.Copy( 0, nPos );
//STRIP001              rStr.Erase( 0, nPos + sPara.Len() );
//STRIP001              bRet = sal_True;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( !bRet )
//STRIP001  {
//STRIP001      rRet = rStr;
//STRIP001      rStr.Erase();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ sal_Bool SwDoc::Replace( SwPaM& rPam, const String& rStr, sal_Bool bRegExpRplc )
/*N*/ {
DBG_ASSERT(0, "STRIP");  //STRIP001     if( !rPam.HasMark() || *rPam.GetPoint() == *rPam.GetMark() )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  sal_Bool bJoinTxt, bJoinPrev;
//STRIP001  lcl_GetJoinFlags( rPam, bJoinTxt, bJoinPrev );
//STRIP001
//STRIP001  {
//STRIP001      // dann eine Kopie vom Cursor erzeugen um alle Pams aus den
//STRIP001      // anderen Sichten aus dem Loeschbereich zu verschieben
//STRIP001      // ABER NICHT SICH SELBST !!
//STRIP001      SwPaM aDelPam( *rPam.GetMark(), *rPam.GetPoint() );
//STRIP001      ::PaMCorrAbs( aDelPam, *aDelPam.GetPoint() );
//STRIP001
//STRIP001      SwPosition *pStt = (SwPosition*)aDelPam.Start(),
//STRIP001                 *pEnd = (SwPosition*)aDelPam.End();
//STRIP001      ASSERT( pStt->nNode == pEnd->nNode ||
//STRIP001              ( pStt->nNode.GetIndex() + 1 == pEnd->nNode.GetIndex() &&
//STRIP001                  !pEnd->nContent.GetIndex() ),
//STRIP001              "Point & Mark zeigen auf verschiedene Nodes" );
//STRIP001      sal_Bool bOneNode = pStt->nNode == pEnd->nNode;
//STRIP001
//STRIP001      // eigenes Undo ????
//STRIP001      String sRepl( rStr );
//STRIP001      SwTxtNode* pTxtNd = pStt->nNode.GetNode().GetTxtNode();
//STRIP001      xub_StrLen nStt = pStt->nContent.GetIndex(),
//STRIP001              nEnd = bOneNode ? pEnd->nContent.GetIndex()
//STRIP001                              : pTxtNd->GetTxt().Len();
//STRIP001      if( bRegExpRplc )       // regulaer suchen ??
//STRIP001      {
//STRIP001          String sFndStr( pTxtNd->GetTxt().Copy( nStt, nEnd - nStt ));
//STRIP001
//STRIP001 //JP 31.03.99: was ist, wenn im gefundenem anderer Inhalt als Text ist,
//STRIP001 //               wie z.B. Rahmen, Felder, Fussnoten, ... ???
//STRIP001 //           Die aktuelle Implementierung entfernt diese Inhalte einfach.
//STRIP001 //           Eigentlich muss der Inhalt immer kopiert werden!
//STRIP001          sFndStr.EraseAllChars( CH_TXTATR_BREAKWORD );
//STRIP001          sFndStr.EraseAllChars( CH_TXTATR_INWORD );
//STRIP001
//STRIP001          String sTmp( String::CreateFromAscii(
//STRIP001                                  RTL_CONSTASCII_STRINGPARAM( "\\t" )));
//STRIP001          ReplaceTabsStr( sRepl, String( '&' ), sFndStr );
//STRIP001          ReplaceTabsStr( sRepl, sTmp, String( '\t' ) );
//STRIP001      }
//STRIP001
//STRIP001      SwDataChanged aTmp( aDelPam, 0 );
//STRIP001
//STRIP001      if( IsRedlineOn() )
//STRIP001      {
//STRIP001          SwRedlineMode eOld = GetRedlineMode();
//STRIP001          checkRedlining(eOld);
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              StartUndo();
//STRIP001
//STRIP001              // Bug 68584 - if any Redline will change (split!) the node
//STRIP001              String sNm; sNm = String::CreateFromInt32( (long)&aDelPam );
//STRIP001              SwBookmark* pBkmk = MakeBookmark( aDelPam,
//STRIP001                              KeyCode(), sNm, sNm, UNO_BOOKMARK );
//STRIP001
//STRIP001 //JP 06.01.98: MUSS noch optimiert werden!!!
//STRIP001 SetRedlineMode( REDLINE_ON | REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE );
//STRIP001
//STRIP001              *aDelPam.GetPoint() = pBkmk->GetPos();
//STRIP001              *aDelPam.GetMark() = *pBkmk->GetOtherPos();
//STRIP001              DelBookmark( GetBookmarks().GetPos( pBkmk ));
//STRIP001              pStt = aDelPam.Start();
//STRIP001              pTxtNd = pStt->nNode.GetNode().GetTxtNode();
//STRIP001              nStt = pStt->nContent.GetIndex();
//STRIP001          }
//STRIP001
//STRIP001          if( sRepl.Len() )
//STRIP001          {
//STRIP001              // Attribute des 1. Zeichens ueber den ReplaceText setzen
//STRIP001              SfxItemSet aSet( GetAttrPool(),
//STRIP001                          RES_CHRATR_BEGIN,     RES_TXTATR_WITHEND_END - 1,
//STRIP001                          RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
//STRIP001                          0 );
//STRIP001              pTxtNd->GetAttr( aSet, nStt+1, nStt+1 );
//STRIP001
//STRIP001              aSet.ClearItem( RES_TXTATR_REFMARK );
//STRIP001              aSet.ClearItem( RES_TXTATR_TOXMARK );
//STRIP001
//STRIP001              if( aDelPam.GetPoint() != aDelPam.End() )
//STRIP001                  aDelPam.Exchange();
//STRIP001
//STRIP001              // das Ende merken
//STRIP001              SwNodeIndex aPtNd( aDelPam.GetPoint()->nNode, -1 );
//STRIP001              xub_StrLen nPtCnt = aDelPam.GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001              sal_Bool bFirst = sal_True;
//STRIP001              String sIns;
//STRIP001              while( lcl_GetTokenToParaBreak( sRepl, sIns, bRegExpRplc ))
//STRIP001              {
//STRIP001                  Insert( aDelPam, sIns );
//STRIP001                  if( bFirst )
//STRIP001                  {
//STRIP001                      SwNodeIndex aMkNd( aDelPam.GetMark()->nNode, -1 );
//STRIP001                      xub_StrLen nMkCnt = aDelPam.GetMark()->nContent.GetIndex();
//STRIP001
//STRIP001                      SplitNode( *aDelPam.GetPoint() );
//STRIP001
//STRIP001                      aMkNd++;
//STRIP001                      aDelPam.GetMark()->nNode = aMkNd;
//STRIP001                      aDelPam.GetMark()->nContent.Assign(
//STRIP001                                  aMkNd.GetNode().GetCntntNode(), nMkCnt );
//STRIP001                      bFirst = sal_False;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      SplitNode( *aDelPam.GetPoint() );
//STRIP001              }
//STRIP001              if( sIns.Len() )
//STRIP001                  Insert( aDelPam, sIns );
//STRIP001
//STRIP001              SwPaM aTmpRange( *aDelPam.GetPoint() );
//STRIP001              aTmpRange.SetMark();
//STRIP001
//STRIP001              aPtNd++;
//STRIP001              aDelPam.GetPoint()->nNode = aPtNd;
//STRIP001              aDelPam.GetPoint()->nContent.Assign( aPtNd.GetNode().GetCntntNode(),
//STRIP001                                                  nPtCnt);
//STRIP001              *aTmpRange.GetMark() = *aDelPam.GetPoint();
//STRIP001
//STRIP001              RstTxtAttr( aTmpRange );
//STRIP001              Insert( aTmpRange, aSet );
//STRIP001          }
//STRIP001
//STRIP001          if( DoesUndo() )
//STRIP001              AppendUndo( new SwUndoRedlineDelete( aDelPam, UNDO_REPLACE ));
//STRIP001          AppendRedline( new SwRedline( REDLINE_DELETE, aDelPam ));
//STRIP001
//STRIP001          *rPam.GetMark() = *aDelPam.GetMark();
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              *aDelPam.GetPoint() = *rPam.GetPoint();
//STRIP001              EndUndo();
//STRIP001
//STRIP001              // Bug 68584 - if any Redline will change (split!) the node
//STRIP001              String sNm; sNm = String::CreateFromInt32( (long)&aDelPam );
//STRIP001              SwBookmark* pBkmk = MakeBookmark( aDelPam,
//STRIP001                              KeyCode(), sNm, sNm, UNO_BOOKMARK );
//STRIP001
//STRIP001              SwIndex& rIdx = aDelPam.GetPoint()->nContent;
//STRIP001              rIdx.Assign( 0, 0 );
//STRIP001              aDelPam.GetMark()->nContent = rIdx;
//STRIP001              rPam.GetPoint()->nNode = 0;
//STRIP001              rPam.GetPoint()->nContent = rIdx;
//STRIP001              *rPam.GetMark() = *rPam.GetPoint();
//STRIP001 //JP 06.01.98: MUSS noch optimiert werden!!!
//STRIP001 SetRedlineMode( eOld );
//STRIP001
//STRIP001              *rPam.GetPoint() = pBkmk->GetPos();
//STRIP001              *rPam.GetMark() = *pBkmk->GetOtherPos();
//STRIP001              DelBookmark( GetBookmarks().GetPos( pBkmk ));
//STRIP001          }
//STRIP001          bJoinTxt = sal_False;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !IsIgnoreRedline() && GetRedlineTbl().Count() )
//STRIP001              DeleteRedline( aDelPam );
//STRIP001
//STRIP001          SwUndoReplace* pUndoRpl = 0;
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001              ClearRedo();
//STRIP001              SwUndo* pU;
//STRIP001
//STRIP001              if( !pUndos->Count() ||
//STRIP001                  UNDO_REPLACE != ( pU = (*pUndos)[ pUndos->Count()-1 ])->GetId() ||
//STRIP001                  ( pUndoRpl = (SwUndoReplace*)pU )->IsFull() )
//STRIP001              {
//STRIP001                  pUndoRpl = new SwUndoReplace();
//STRIP001                  AppendUndo( pUndoRpl );
//STRIP001              }
//STRIP001              pUndoRpl->AddEntry( aDelPam, sRepl, bRegExpRplc );
//STRIP001              DoUndo( sal_False );
//STRIP001          }
//STRIP001
//STRIP001          if( aDelPam.GetPoint() != pStt )
//STRIP001              aDelPam.Exchange();
//STRIP001
//STRIP001          SwNodeIndex aPtNd( pStt->nNode, -1 );
//STRIP001          xub_StrLen nPtCnt = pStt->nContent.GetIndex();
//STRIP001
//STRIP001          // die Werte nochmal setzen, falls schohn Rahmen oder Fussnoten
//STRIP001          // auf dem Text entfernt wurden!
//STRIP001          nStt = nPtCnt;
//STRIP001          nEnd = bOneNode ? pEnd->nContent.GetIndex()
//STRIP001                          : pTxtNd->GetTxt().Len();
//STRIP001
//STRIP001          sal_Bool bFirst = sal_True;
//STRIP001          String sIns;
//STRIP001          while( lcl_GetTokenToParaBreak( sRepl, sIns, bRegExpRplc ))
//STRIP001          {
//STRIP001              if( !bFirst || nStt == pTxtNd->GetTxt().Len() )
//STRIP001                  Insert( aDelPam, sIns );
//STRIP001              else if( nStt < nEnd || sIns.Len() )
//STRIP001                  pTxtNd->Replace( pStt->nContent, nEnd - nStt, sIns );
//STRIP001              SplitNode( *pStt );
//STRIP001              bFirst = sal_False;
//STRIP001          }
//STRIP001
//STRIP001          if( bFirst || sIns.Len() )
//STRIP001          {
//STRIP001              if( !bFirst || nStt == pTxtNd->GetTxt().Len() )
//STRIP001                  Insert( aDelPam, sIns );
//STRIP001              else if( nStt < nEnd || sIns.Len() )
//STRIP001                  pTxtNd->Replace( pStt->nContent, nEnd - nStt, sIns );
//STRIP001          }
//STRIP001
//STRIP001          *rPam.GetMark() = *aDelPam.GetMark();
//STRIP001
//STRIP001          aPtNd++;
//STRIP001          rPam.GetMark()->nNode = aPtNd;
//STRIP001          rPam.GetMark()->nContent.Assign( aPtNd.GetNode().GetCntntNode(),
//STRIP001                                              nPtCnt );
//STRIP001          if( bJoinTxt )
//STRIP001              rPam.Move( fnMoveBackward );
//STRIP001
//STRIP001          if( pUndoRpl )
//STRIP001          {
//STRIP001              pUndoRpl->SetEntryEnd( rPam );
//STRIP001              DoUndo( sal_True );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bJoinTxt )
//STRIP001      lcl_JoinText( rPam, bJoinPrev );
//STRIP001
//STRIP001  SetModified();
/*N*/   return sal_True;
/*N*/ }

    // speicher die akt. Werte fuer die automatische Aufnahme von Ausnahmen
    // in die Autokorrektur
//STRIP001 void SwDoc::SetAutoCorrExceptWord( SwAutoCorrExceptWord* pNew )
//STRIP001 {
//STRIP001  if( pACEWord && pNew != pACEWord )
//STRIP001      delete pACEWord;
//STRIP001  pACEWord = pNew;
//STRIP001 }

/*N*/ sal_Bool SwDoc::DelFullPara( SwPaM& rPam )
/*N*/ {
/*N*/   const SwPosition &rStt = *rPam.Start(), &rEnd = *rPam.End();
/*N*/   const SwNode* pNd = &rStt.nNode.GetNode();
/*N*/   sal_uInt32 nSectDiff = pNd->FindStartNode()->EndOfSectionIndex() -
/*N*/                       pNd->StartOfSectionIndex();
/*N*/   sal_uInt32 nNodeDiff = rEnd.nNode.GetIndex() - rStt.nNode.GetIndex();
/*N*/
/*N*/       if ( nSectDiff-2 <= nNodeDiff || IsRedlineOn() ||
/*N*/        /* #i9185# Prevent getting the node after the end node (see below) */
/*N*/       rEnd.nNode.GetIndex() + 1 == aNodes.Count() )
/*N*/       return sal_False;
/*N*/
/*N*/   // harte SeitenUmbrueche am nachfolgenden Node verschieben
/*N*/   sal_Bool bSavePageBreak = sal_False, bSavePageDesc = sal_False;
/*N*/
    /* #i9185# This whould lead to a segmentation fault if not catched
       above. */
/*N*/   sal_uInt32 nNextNd = rEnd.nNode.GetIndex() + 1;
/*N*/   SwTableNode* pTblNd = aNodes[ nNextNd ]->GetTableNode();
/*N*/
/*N*/   if( pTblNd && pNd->IsCntntNode() )
/*N*/   {
/*?*/       SwFrmFmt* pTableFmt = pTblNd->GetTable().GetFrmFmt();
/*?*/ //JP 24.08.98: will man wirklich den PageDesc/Break vom
/*?*/ //                nachfolgen Absatz ueberbuegeln?
/*?*/ //        const SwAttrSet& rAttrSet = pTableFmt->GetAttrSet();
/*?*/ //        if( SFX_ITEM_SET != rAttrSet.GetItemState( RES_PAGEDESC ) &&
/*?*/ //            SFX_ITEM_SET != rAttrSet.GetItemState( RES_BREAK ))
/*?*/       {
/*?*/           const SfxPoolItem *pItem;
/*?*/           const SfxItemSet* pSet = ((SwCntntNode*)pNd)->GetpSwAttrSet();
/*?*/           if( pSet && SFX_ITEM_SET == pSet->GetItemState( RES_PAGEDESC,
/*?*/               sal_False, &pItem ) )
/*?*/           {
/*?*/               pTableFmt->SetAttr( *pItem );
/*?*/               bSavePageDesc = sal_True;
/*?*/           }
/*?*/
/*?*/           if( pSet && SFX_ITEM_SET == pSet->GetItemState( RES_BREAK,
/*?*/               sal_False, &pItem ) )
/*?*/           {
/*?*/               pTableFmt->SetAttr( *pItem );
/*?*/               bSavePageBreak = sal_True;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   sal_Bool bDoesUndo = DoesUndo();
/*N*/   if( bDoesUndo )
/*N*/   {
/*N*/       if( !rPam.HasMark() )
/*N*/           rPam.SetMark();
/*N*/       else if( rPam.GetPoint() == &rStt )
/*?*/           rPam.Exchange();
/*N*/       rPam.GetPoint()->nNode++;
/*N*/
/*N*/       rPam.GetPoint()->nContent.Assign( 0, 0 );
/*N*/       rPam.GetMark()->nContent.Assign( 0, 0 );
/*N*/
/*N*/       ClearRedo();
/*N*/       SwUndoDelete* pUndo = new SwUndoDelete( rPam, sal_True );
/*N*/       pUndo->SetPgBrkFlags( bSavePageBreak, bSavePageDesc );
/*N*/       AppendUndo( pUndo );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwNodeRange aRg( rStt.nNode, rEnd.nNode );
/*N*/       if( rPam.GetPoint() != &rEnd )
/*?*/           rPam.Exchange();
/*N*/
/*N*/       // versuche hinters Ende zu verschieben
/*N*/       if( !rPam.Move( fnMoveForward, fnGoNode ) )
/*N*/       {
/*N*/           // na gut, dann an den Anfang
/*N*/           rPam.Exchange();
/*N*/           if( !rPam.Move( fnMoveBackward, fnGoNode ))
/*N*/           {
/*N*/               ASSERT( sal_False, "kein Node mehr vorhanden" );
/*N*/               return sal_False;
/*N*/           }
/*N*/       }
/*N*/           // text::Bookmarks usw. verschieben
/*N*/       CorrAbs( aRg.aStart, aRg.aEnd, *rPam.GetPoint(), sal_True );
/*N*/
/*N*/           // was ist mit Fly's ??
/*N*/       {
/*N*/           // stehen noch FlyFrames rum, loesche auch diese
/*N*/           const SwPosition* pAPos;
/*N*/           for( sal_uInt16 n = 0; n < GetSpzFrmFmts()->Count(); ++n )
/*N*/           {
/*N*/               SwFrmFmt* pFly = (*GetSpzFrmFmts())[n];
/*N*/               const SwFmtAnchor* pAnchor = &pFly->GetAnchor();
/*N*/               if( ( FLY_AT_CNTNT == pAnchor->GetAnchorId() ||
/*N*/                     FLY_AUTO_CNTNT == pAnchor->GetAnchorId() ) &&
/*N*/                   0 != ( pAPos = pAnchor->GetCntntAnchor() ) &&
/*N*/                   aRg.aStart <= pAPos->nNode && pAPos->nNode <= aRg.aEnd )
/*N*/               {
/*?*/                   DelLayoutFmt( pFly );
/*?*/                   --n;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       rPam.GetBound( TRUE ).nContent.Assign( 0, 0 );
/*N*/       rPam.GetBound( FALSE ).nContent.Assign( 0, 0 );
/*N*/       GetNodes().Delete( aRg.aStart, nNodeDiff+1 );
/*N*/   }
/*N*/   rPam.DeleteMark();
/*N*/   SetModified();
/*N*/
/*N*/   return sal_True;
/*N*/ }


//STRIP001 void SwDoc::TransliterateText( const SwPaM& rPaM,
//STRIP001                              utl::TransliterationWrapper& rTrans )
//STRIP001 {
//STRIP001  SwUndoTransliterate* pUndo;
//STRIP001  if( DoesUndo() )
//STRIP001      pUndo = new SwUndoTransliterate( rPaM, rTrans );
//STRIP001  else
//STRIP001      pUndo = 0;
//STRIP001
//STRIP001  const SwPosition* pStt = rPaM.Start(),
//STRIP001                  * pEnd = pStt == rPaM.GetPoint() ? rPaM.GetMark()
//STRIP001                                                   : rPaM.GetPoint();
//STRIP001  ULONG nSttNd = pStt->nNode.GetIndex(), nEndNd = pEnd->nNode.GetIndex();
//STRIP001  xub_StrLen nSttCnt = pStt->nContent.GetIndex(),
//STRIP001             nEndCnt = pEnd->nContent.GetIndex();
//STRIP001
//STRIP001  SwTxtNode* pTNd = pStt->nNode.GetNode().GetTxtNode();
//STRIP001  if( pStt == pEnd && pTNd )                  // no region ?
//STRIP001  {
//STRIP001      Boundary aBndry;
//STRIP001      if( pBreakIt->xBreak.is() )
//STRIP001          aBndry = pBreakIt->xBreak->getWordBoundary(
//STRIP001                      pTNd->GetTxt(), nSttCnt,
//STRIP001                      pBreakIt->GetLocale( pTNd->GetLang( nSttCnt ) ),
//STRIP001                      WordType::ANY_WORD /*ANYWORD_IGNOREWHITESPACES*/,
//STRIP001                      TRUE );
//STRIP001
//STRIP001      if( aBndry.startPos < nSttCnt && nSttCnt < aBndry.endPos )
//STRIP001      {
//STRIP001          nSttCnt = (xub_StrLen)aBndry.startPos;
//STRIP001          nEndCnt = (xub_StrLen)aBndry.endPos;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( nSttNd != nEndNd )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( pStt->nNode );
//STRIP001      if( nSttCnt )
//STRIP001      {
//STRIP001          aIdx++;
//STRIP001          if( pTNd )
//STRIP001              pTNd->TransliterateText( rTrans, nSttCnt,
//STRIP001                                          pTNd->GetTxt().Len(), pUndo );
//STRIP001      }
//STRIP001
//STRIP001      for( ; aIdx.GetIndex() < nEndNd; aIdx++ )
//STRIP001          if( 0 != ( pTNd = aIdx.GetNode().GetTxtNode() ))
//STRIP001              pTNd->TransliterateText( rTrans, 0, pTNd->GetTxt().Len(),
//STRIP001                                      pUndo );
//STRIP001
//STRIP001      if( nEndCnt && 0 != ( pTNd = pEnd->nNode.GetNode().GetTxtNode() ))
//STRIP001          pTNd->TransliterateText( rTrans, 0, nEndCnt, pUndo );
//STRIP001  }
//STRIP001  else if( pTNd && nSttCnt < nEndCnt )
//STRIP001      pTNd->TransliterateText( rTrans, nSttCnt, nEndCnt, pUndo );
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      if( pUndo->HasData() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001      else
//STRIP001          delete pUndo;
//STRIP001  }
//STRIP001 }
#define MAX_REDLINE_COUNT   250
// -----------------------------------------------------------------------------
//STRIP001 void SwDoc::checkRedlining(SwRedlineMode& _rReadlineMode)
//STRIP001 {
//STRIP001  const SwRedlineTbl& rRedlineTbl = GetRedlineTbl();
//STRIP001  SwEditShell* pEditShell = GetEditShell();
//STRIP001  Window* pParent = pEditShell ? pEditShell->GetWin() : NULL;
//STRIP001  if ( pParent && !bReadlineChecked && rRedlineTbl.Count() > MAX_REDLINE_COUNT
//STRIP001      && !((_rReadlineMode & REDLINE_SHOW_DELETE) == REDLINE_SHOW_DELETE) )
//STRIP001  {
//STRIP001      WarningBox aWarning( pParent,SW_RES(MSG_DISABLE_READLINE_QUESTION));
//STRIP001      USHORT nResult = aWarning.Execute();
//STRIP001      bReadlineChecked = sal_True;
//STRIP001      if ( nResult == RET_YES )
//STRIP001      {
//STRIP001          sal_Int32 nMode = (sal_Int32)_rReadlineMode;
//STRIP001          nMode |= REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE;
//STRIP001          _rReadlineMode = (SwRedlineMode)nMode;
//STRIP001      }
//STRIP001  }
//STRIP001 }
// -----------------------------------------------------------------------------

