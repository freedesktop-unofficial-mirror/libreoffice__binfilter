/*************************************************************************
 *
 *  $RCSfile: sw_trvlreg.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:02:25 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
// auto strip #ifndef _SWCRSR_HXX
// auto strip #include <swcrsr.hxx>
// auto strip #endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCNTNT_HXX //autogen
// auto strip #include <fmtcntnt.hxx>
// auto strip #endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
// auto strip #ifndef _CALLNK_HXX
// auto strip #include <callnk.hxx>
// auto strip #endif
// auto strip #ifndef _PAMTYP_HXX
// auto strip #include <pamtyp.hxx>
// auto strip #endif
// auto strip #ifndef _SECTION_HXX
// auto strip #include <section.hxx>
// auto strip #endif
namespace binfilter {



/*N*/ FASTBOOL GotoPrevRegion( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwNodeIndex aIdx( rCurCrsr.GetPoint()->nNode );
//STRIP001  SwSectionNode* pNd = aIdx.GetNode().FindSectionNode();
//STRIP001  if( pNd )
//STRIP001      aIdx.Assign( *pNd, - 1 );
//STRIP001
//STRIP001  do {
//STRIP001      while( aIdx.GetIndex() &&
//STRIP001          0 == ( pNd = aIdx.GetNode().FindStartNode()->GetSectionNode()) )
//STRIP001          aIdx--;
//STRIP001
//STRIP001      if( pNd )       // gibt einen weiteren SectionNode ?
//STRIP001      {
//STRIP001          if( pNd->GetSection().IsHiddenFlag() ||
//STRIP001              ( !bInReadOnly &&
//STRIP001                pNd->GetSection().IsProtectFlag() ))
//STRIP001          {
//STRIP001              // geschuetzte/versteckte ueberspringen wir
//STRIP001              aIdx.Assign( *pNd, - 1 );
//STRIP001          }
//STRIP001          else if( fnPosRegion == fnMoveForward )
//STRIP001          {
//STRIP001              aIdx = *pNd;
//STRIP001              SwCntntNode* pCNd = pNd->GetNodes().GoNextSection( &aIdx,
//STRIP001                                              TRUE, !bInReadOnly );
//STRIP001              if( !pCNd )
//STRIP001              {
//STRIP001                  aIdx--;
//STRIP001                  continue;
//STRIP001              }
//STRIP001              rCurCrsr.GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aIdx = *pNd->EndOfSectionNode();
//STRIP001              SwCntntNode* pCNd = pNd->GetNodes().GoPrevSection( &aIdx,
//STRIP001                                              TRUE, !bInReadOnly );
//STRIP001              if( !pCNd )
//STRIP001              {
//STRIP001                  aIdx.Assign( *pNd, - 1 );
//STRIP001                  continue;
//STRIP001              }
//STRIP001              rCurCrsr.GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001          }
//STRIP001
//STRIP001          rCurCrsr.GetPoint()->nNode = aIdx;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  } while( pNd );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GotoNextRegion( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwNodeIndex aIdx( rCurCrsr.GetPoint()->nNode );
//STRIP001  SwSectionNode* pNd = aIdx.GetNode().FindSectionNode();
//STRIP001  if( pNd )
//STRIP001      aIdx.Assign( *pNd->EndOfSectionNode(), - 1 );
//STRIP001
//STRIP001  ULONG nEndCount = aIdx.GetNode().GetNodes().Count()-1;
//STRIP001  do {
//STRIP001      while( aIdx.GetIndex() < nEndCount &&
//STRIP001              0 == ( pNd = aIdx.GetNode().GetSectionNode()) )
//STRIP001          aIdx++;
//STRIP001
//STRIP001      if( pNd )       // gibt einen weiteren SectionNode ?
//STRIP001      {
//STRIP001          if( pNd->GetSection().IsHiddenFlag() ||
//STRIP001              ( !bInReadOnly &&
//STRIP001                pNd->GetSection().IsProtectFlag() ))
//STRIP001          {
//STRIP001              // geschuetzte/versteckte ueberspringen wir
//STRIP001              aIdx.Assign( *pNd->EndOfSectionNode(), +1 );
//STRIP001          }
//STRIP001          else if( fnPosRegion == fnMoveForward )
//STRIP001          {
//STRIP001              aIdx = *pNd;
//STRIP001              SwCntntNode* pCNd = pNd->GetNodes().GoNextSection( &aIdx,
//STRIP001                                              TRUE, !bInReadOnly );
//STRIP001              if( !pCNd )
//STRIP001              {
//STRIP001                  aIdx.Assign( *pNd->EndOfSectionNode(), +1 );
//STRIP001                  continue;
//STRIP001              }
//STRIP001              rCurCrsr.GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aIdx = *pNd->EndOfSectionNode();
//STRIP001              SwCntntNode* pCNd = pNd->GetNodes().GoPrevSection( &aIdx,
//STRIP001                                              TRUE, !bInReadOnly );
//STRIP001              if( !pCNd )
//STRIP001              {
//STRIP001                  aIdx++;
//STRIP001                  continue;
//STRIP001              }
//STRIP001              rCurCrsr.GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001          }
//STRIP001
//STRIP001          rCurCrsr.GetPoint()->nNode = aIdx;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  } while( pNd );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GotoCurrRegion( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001
//STRIP001  SwSectionNode* pNd = rCurCrsr.GetNode()->FindSectionNode();
//STRIP001  if( !pNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwPosition* pPos = rCurCrsr.GetPoint();
//STRIP001  FASTBOOL bMoveBackward = fnPosRegion == fnMoveBackward;
//STRIP001
//STRIP001  SwCntntNode* pCNd;
//STRIP001  if( bMoveBackward )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *pNd->EndOfSectionNode() );
//STRIP001      pCNd = pNd->GetNodes().GoPrevSection( &aIdx, TRUE, !bInReadOnly );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *pNd );
//STRIP001      pCNd = pNd->GetNodes().GoNextSection( &aIdx, TRUE, !bInReadOnly );
//STRIP001  }
//STRIP001
//STRIP001  if( pCNd )
//STRIP001  {
//STRIP001      pPos->nNode = *pCNd;
//STRIP001      xub_StrLen nTmpPos = bMoveBackward ? pCNd->Len() : 0;
//STRIP001      pPos->nContent.Assign( pCNd, nTmpPos );
//STRIP001  }
//STRIP001  return 0 != pCNd;
/*N*/ }


/*N*/ FASTBOOL GotoCurrRegionAndSkip( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                               FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwNode* pCurrNd = rCurCrsr.GetNode();
//STRIP001  SwSectionNode* pNd = pCurrNd->FindSectionNode();
//STRIP001  if( !pNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwPosition* pPos = rCurCrsr.GetPoint();
//STRIP001  xub_StrLen nCurrCnt = pPos->nContent.GetIndex();
//STRIP001  FASTBOOL bMoveBackward = fnPosRegion == fnMoveBackward;
//STRIP001
//STRIP001  do {
//STRIP001      SwCntntNode* pCNd;
//STRIP001      if( bMoveBackward ) // ans Ende vom Bereich
//STRIP001      {
//STRIP001          SwNodeIndex aIdx( *pNd->EndOfSectionNode() );
//STRIP001          pCNd = pNd->GetNodes().GoPrevSection( &aIdx, TRUE, !bInReadOnly );
//STRIP001          if( !pCNd )
//STRIP001              return FALSE;
//STRIP001          pPos->nNode = aIdx;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwNodeIndex aIdx( *pNd );
//STRIP001          pCNd = pNd->GetNodes().GoNextSection( &aIdx, TRUE, !bInReadOnly );
//STRIP001          if( !pCNd )
//STRIP001              return FALSE;
//STRIP001          pPos->nNode = aIdx;
//STRIP001      }
//STRIP001
//STRIP001      xub_StrLen nTmpPos = bMoveBackward ? pCNd->Len() : 0;
//STRIP001      pPos->nContent.Assign( pCNd, nTmpPos );
//STRIP001
//STRIP001      if( &pPos->nNode.GetNode() != pCurrNd ||
//STRIP001          pPos->nContent.GetIndex() != nCurrCnt )
//STRIP001          // es gab eine Veraenderung
//STRIP001          return TRUE;
//STRIP001
//STRIP001      // dann versuche mal den "Parent" dieser Section
//STRIP001      SwSection* pParent = pNd->GetSection().GetParent();
//STRIP001      pNd = pParent ? pParent->GetFmt()->GetSectionNode() : 0;
//STRIP001  } while( pNd );
/*N*/   return FALSE;
/*N*/ }



/*N*/ FASTBOOL SwCursor::MoveRegion( SwWhichRegion fnWhichRegion, SwPosRegion fnPosRegion )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP");  return FALSE;//STRIP001 SwCrsrSaveState aSaveState( *this );
//STRIP001  return !(SwTableCursor*)*this &&
//STRIP001          (*fnWhichRegion)( *this, fnPosRegion, IsReadOnlyAvailable()  ) &&
//STRIP001          !IsSelOvr() &&
//STRIP001          ( GetPoint()->nNode.GetIndex() != pSavePos->nNode ||
//STRIP001              GetPoint()->nContent.GetIndex() != pSavePos->nCntnt );
/*N*/ }

//STRIP001 FASTBOOL SwCrsrShell::MoveRegion( SwWhichRegion fnWhichRegion, SwPosRegion fnPosRegion )
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  FASTBOOL bRet = !pTblCrsr && pCurCrsr->MoveRegion( fnWhichRegion, fnPosRegion );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr();
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCursor::GotoRegion( const String& rName )
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  const SwSectionFmts& rFmts = GetDoc()->GetSections();
//STRIP001  for( USHORT n = rFmts.Count(); n; )
//STRIP001  {
//STRIP001      const SwSectionFmt* pFmt = rFmts[ --n ];
//STRIP001      const SwNodeIndex* pIdx;
//STRIP001      const SwSection* pSect;
//STRIP001      if( 0 != ( pSect = pFmt->GetSection() ) &&
//STRIP001          pSect->GetName() == rName &&
//STRIP001          0 != ( pIdx = pFmt->GetCntnt().GetCntntIdx() ) &&
//STRIP001          pIdx->GetNode().GetNodes().IsDocNodes() )
//STRIP001      {
//STRIP001          // ein Bereich im normalen NodesArr
//STRIP001          SwCrsrSaveState aSaveState( *this );
//STRIP001
//STRIP001          GetPoint()->nNode = *pIdx;
//STRIP001          Move( fnMoveForward, fnGoCntnt );
//STRIP001          bRet = !IsSelOvr();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SwCrsrShell::GotoRegion( const String& rName )
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001  FASTBOOL bRet = !pTblCrsr && pCurCrsr->GotoRegion( rName );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr( SwCrsrShell::SCROLLWIN | SwCrsrShell::CHKRANGE |
//STRIP001                  SwCrsrShell::READONLY ); // und den akt. Updaten
//STRIP001  return bRet;
//STRIP001 }



}
