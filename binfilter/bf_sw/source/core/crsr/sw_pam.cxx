/*************************************************************************
 *
 *  $RCSfile: sw_pam.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:01:24 $
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

#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif

// auto strip #ifndef _CNTFRM_HXX
// auto strip #include <cntfrm.hxx>
// auto strip #endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif
namespace binfilter {


// fuer den dummen ?MSC-? Compiler
/*N*/inline xub_StrLen GetSttOrEnd( BOOL bCondition, const SwCntntNode& rNd )
/*N*/{
/*N*/   return bCondition ? 0 : rNd.Len();
/*N*/}

/*************************************************************************
|*
|*  SwPosition
|*
|*  Beschreibung        PAM.DOC
|*  Ersterstellung      VB  4.3.91
|*  Letzte Aenderung    VB  4.3.91
|*
*************************************************************************/


/*N*/ SwPosition::SwPosition(const SwPosition &rPos)
/*N*/   : nNode(rPos.nNode),nContent(rPos.nContent)
/*N*/ {
/*N*/ }


/*N*/ SwPosition::SwPosition( const SwNodeIndex &rNode, const SwIndex &rCntnt )
/*N*/   : nNode( rNode ),nContent( rCntnt )
/*N*/ {
/*N*/ }

/*N*/ SwPosition::SwPosition( const SwNodeIndex &rNode )
/*N*/   : nNode( rNode ), nContent( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwPosition::SwPosition( const SwNode& rNode )
/*N*/   : nNode( rNode ), nContent( 0 )
/*N*/ {
/*N*/ }


/*N*/ SwPosition &SwPosition::operator=(const SwPosition &rPos)
/*N*/ {
/*N*/   nNode = rPos.nNode;
/*N*/   nContent = rPos.nContent;
/*N*/   return *this;
/*N*/ }


/*N*/ FASTBOOL SwPosition::operator<(const SwPosition &rPos) const
/*N*/ {
/*N*/   if( nNode < rPos.nNode )
/*N*/       return TRUE;
/*N*/   if( nNode == rPos.nNode )
/*N*/       return ( nContent < rPos.nContent );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL SwPosition::operator>(const SwPosition &rPos) const
/*N*/ {
/*N*/   if(nNode > rPos.nNode )
/*N*/       return TRUE;
/*N*/   if( nNode == rPos.nNode )
/*N*/       return ( nContent > rPos.nContent );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL SwPosition::operator<=(const SwPosition &rPos) const
/*N*/ {
/*N*/   if(nNode < rPos.nNode )
/*N*/       return TRUE;
/*N*/   if( nNode == rPos.nNode )
/*N*/       return ( nContent <= rPos.nContent );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL SwPosition::operator>=(const SwPosition &rPos) const
/*N*/ {
/*N*/   if(nNode > rPos.nNode )
/*N*/       return TRUE;
/*N*/   if( nNode == rPos.nNode )
/*N*/       return ( nContent >= rPos.nContent );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL SwPosition::operator==(const SwPosition &rPos) const
/*N*/ {
/*N*/   return
/*N*/       ( ( nNode == rPos.nNode ) && ( nContent == rPos.nContent ) ?
/*N*/           TRUE: FALSE);
/*N*/ }


/*N*/ FASTBOOL SwPosition::operator!=(const SwPosition &rPos) const
/*N*/ {
/*N*/   if( nNode != rPos.nNode )
/*N*/       return TRUE;
/*N*/   return ( nContent != rPos.nContent );
/*N*/ }

SwComparePosition ComparePosition(
            const SwPosition& rStt1, const SwPosition& rEnd1,
            const SwPosition& rStt2, const SwPosition& rEnd2 )
{
    SwComparePosition nRet;
    if( rStt1 < rStt2 )
    {
        if( rEnd1 > rStt2 )
        {
            if( rEnd1 >= rEnd2 )
                nRet = POS_OUTSIDE;
            else
                nRet = POS_OVERLAP_BEFORE;

        }
        else if( rEnd1 == rStt2 )
            nRet = POS_COLLIDE_END;
        else
            nRet = POS_BEFORE;
    }
    else if( rEnd2 > rStt1 )
    {
        if( rEnd2 >= rEnd1 )
        {
            if( rEnd2 == rEnd1 && rStt2 == rStt1 )
                nRet = POS_EQUAL;
            else
                nRet = POS_INSIDE;
        }
        else
            nRet = POS_OVERLAP_BEHIND;
    }
    else if( rEnd2 == rStt1 )
        nRet = POS_COLLIDE_START;
    else
        nRet = POS_BEHIND;
    return nRet;
}

//STRIP001 SwComparePosition ComparePosition(
//STRIP001          const unsigned long nStt1, const unsigned long nEnd1,
//STRIP001          const unsigned long nStt2, const unsigned long nEnd2 )
//STRIP001 {
//STRIP001  SwComparePosition nRet;
//STRIP001  if( nStt1 < nStt2 )
//STRIP001  {
//STRIP001      if( nEnd1 > nStt2 )
//STRIP001      {
//STRIP001          if( nEnd1 >= nEnd2 )
//STRIP001              nRet = POS_OUTSIDE;
//STRIP001          else
//STRIP001              nRet = POS_OVERLAP_BEFORE;
//STRIP001
//STRIP001      }
//STRIP001      else if( nEnd1 == nStt2 )
//STRIP001          nRet = POS_COLLIDE_END;
//STRIP001      else
//STRIP001          nRet = POS_BEFORE;
//STRIP001  }
//STRIP001  else if( nEnd2 > nStt1 )
//STRIP001  {
//STRIP001      if( nEnd2 >= nEnd1 )
//STRIP001      {
//STRIP001          if( nEnd2 == nEnd1 && nStt2 == nStt1 )
//STRIP001              nRet = POS_EQUAL;
//STRIP001          else
//STRIP001              nRet = POS_INSIDE;
//STRIP001      }
//STRIP001      else
//STRIP001          nRet = POS_OVERLAP_BEHIND;
//STRIP001  }
//STRIP001  else if( nEnd2 == nStt1 )
//STRIP001      nRet = POS_COLLIDE_START;
//STRIP001  else
//STRIP001      nRet = POS_BEHIND;
//STRIP001  return nRet;
//STRIP001 }

/*  */

enum CHKSECTION { Chk_Both, Chk_One, Chk_None };


/*N*/ CHKSECTION lcl_TstIdx( ULONG nSttIdx, ULONG nEndIdx, const SwNode& rEndNd )
/*N*/ {
/*N*/   ULONG nStt = rEndNd.StartOfSectionIndex(), nEnd = rEndNd.GetIndex();
/*N*/   CHKSECTION eSec = nStt < nSttIdx && nEnd >= nSttIdx ? Chk_One : Chk_None;
/*N*/   if( nStt < nEndIdx && nEnd >= nEndIdx )
/*N*/       return( eSec == Chk_One ? Chk_Both : Chk_One );
/*N*/   return eSec;
/*N*/ }


/*N*/ FASTBOOL lcl_ChkOneRange( CHKSECTION eSec, BOOL bChkSections,
/*N*/                   const SwNode& rBaseEnd, ULONG nStt, ULONG nEnd )
/*N*/ {
/*N*/   if( eSec != Chk_Both )
/*N*/       return FALSE;
/*N*/
/*N*/   if( !bChkSections )
/*N*/       return TRUE;
/*N*/
/*N*/   // suche die umspannende Section
/*N*/   const SwNodes& rNds = rBaseEnd.GetNodes();
/*N*/   const SwNode *pTmp, *pNd = rNds[ nStt ];
/*N*/   if( !pNd->IsStartNode() )
/*N*/       pNd = pNd->StartOfSectionNode();
/*N*/
/*N*/   if( pNd == rNds[ nEnd ]->StartOfSectionNode() )
/*N*/       return TRUE;        // der gleiche StartNode, die selbe Section
/*N*/
/*N*/   // steht schon auf einem GrundSection Node ? Fehler !!!
/*N*/   if( !pNd->StartOfSectionIndex() )
/*N*/       return FALSE;
/*N*/
/*N*/   while( ( pTmp = pNd->StartOfSectionNode())->EndOfSectionNode() !=
/*N*/           &rBaseEnd )
/*N*/       pNd = pTmp;
/*N*/
/*N*/   ULONG nSttIdx = pNd->GetIndex(), nEndIdx = pNd->EndOfSectionIndex();
/*N*/   return nSttIdx <= nStt && nStt <= nEndIdx &&
/*N*/          nSttIdx <= nEnd && nEnd <= nEndIdx ? TRUE : FALSE;
/*N*/ }


/*N*/ FASTBOOL CheckNodesRange( const SwNodeIndex& rStt,
/*N*/                       const SwNodeIndex& rEnd, FASTBOOL bChkSection )
/*N*/ {
/*N*/   const SwNodes& rNds = rStt.GetNodes();
/*N*/   ULONG nStt = rStt.GetIndex(), nEnd = rEnd.GetIndex();
/*N*/   CHKSECTION eSec = lcl_TstIdx( nStt, nEnd, rNds.GetEndOfContent() );
/*N*/   if( Chk_None != eSec ) return eSec == Chk_Both ? TRUE : FALSE;
/*N*/
/*N*/   eSec = lcl_TstIdx( nStt, nEnd, rNds.GetEndOfAutotext() );
/*N*/   if( Chk_None != eSec )
/*N*/       return lcl_ChkOneRange( eSec, bChkSection,
/*N*/                           rNds.GetEndOfAutotext(), nStt, nEnd );
/*N*/
/*N*/   eSec = lcl_TstIdx( nStt, nEnd, rNds.GetEndOfPostIts() );
/*N*/   if( Chk_None != eSec )
/*N*/       return lcl_ChkOneRange( eSec, bChkSection,
/*N*/                           rNds.GetEndOfPostIts(), nStt, nEnd );
/*N*/
/*?*/   eSec = lcl_TstIdx( nStt, nEnd, rNds.GetEndOfInserts() );
/*?*/   if( Chk_None != eSec )
/*?*/       return lcl_ChkOneRange( eSec, bChkSection,
/*?*/                           rNds.GetEndOfInserts(), nStt, nEnd );
/*?*/
/*?*/   eSec = lcl_TstIdx( nStt, nEnd, rNds.GetEndOfRedlines() );
/*?*/   if( Chk_None != eSec )
/*?*/       return lcl_ChkOneRange( eSec, bChkSection,
/*?*/                           rNds.GetEndOfRedlines(), nStt, nEnd );
/*?*/
/*?*/   return FALSE;       // liegt irgendwo dazwischen, FEHLER
/*N*/ }


/*N*/ FASTBOOL GoNext(SwNode* pNd, SwIndex * pIdx, USHORT nMode )
/*N*/ {
/*N*/   if( pNd->IsCntntNode() )
/*N*/       return ((SwCntntNode*)pNd)->GoNext( pIdx, nMode );
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GoPrevious( SwNode* pNd, SwIndex * pIdx, USHORT nMode )
/*N*/ {
/*N*/   if( pNd->IsCntntNode() )
/*N*/       return ((SwCntntNode*)pNd)->GoPrevious( pIdx, nMode );
/*N*/   return FALSE;
/*N*/ }


/*N*/ SwCntntNode* GoNextNds( SwNodeIndex* pIdx, FASTBOOL bChk )
/*N*/ {
/*N*/   SwNodeIndex aIdx( *pIdx );
/*N*/   SwCntntNode* pNd = aIdx.GetNodes().GoNext( &aIdx );
/*N*/   if( pNd )
/*N*/   {
/*N*/       if( bChk && 1 != aIdx.GetIndex() - pIdx->GetIndex() &&
/*N*/           !CheckNodesRange( *pIdx, aIdx, TRUE ) )
/*N*/               pNd = 0;
/*N*/       else
/*N*/           *pIdx = aIdx;
/*N*/   }
/*N*/   return pNd;
/*N*/ }


/*N*/ SwCntntNode* GoPreviousNds( SwNodeIndex * pIdx, FASTBOOL bChk )
/*N*/ {
/*N*/   SwNodeIndex aIdx( *pIdx );
/*N*/   SwCntntNode* pNd = aIdx.GetNodes().GoPrevious( &aIdx );
/*N*/   if( pNd )
/*N*/   {
/*N*/       if( bChk && 1 != pIdx->GetIndex() - aIdx.GetIndex() &&
/*N*/           !CheckNodesRange( *pIdx, aIdx, TRUE ) )
/*N*/               pNd = 0;
/*N*/       else
/*N*/           *pIdx = aIdx;
/*N*/   }
/*N*/   return pNd;
/*N*/ }

// ----------------------------------------------------------------------

/*************************************************************************
|*
|*  SwPointAndMark
|*
|*  Beschreibung        PAM.DOC
|*  Ersterstellung      VB  4.3.91
|*  Letzte Aenderung    JP  6.5.91
|*
*************************************************************************/

/*N*/ SwPaM::SwPaM( const SwPosition& rPos, SwPaM* pRing )
/*N*/   : aBound1( rPos ), aBound2( rPos ), Ring( pRing )
/*N*/ {
/*N*/   pPoint = pMark = &aBound1;
/*N*/ }

/*N*/ SwPaM::SwPaM( const SwPosition& rMk, const SwPosition& rPt, SwPaM* pRing )
/*N*/   : aBound1( rMk ), aBound2( rPt ), Ring( pRing )
/*N*/ {
/*N*/   pMark = &aBound1;
/*N*/   pPoint = &aBound2;
/*N*/ }

//STRIP001 SwPaM::SwPaM( const SwNodeIndex& rMk, const SwNodeIndex& rPt,
//STRIP001              long nMkOffset, long nPtOffset, SwPaM* pRing )
//STRIP001  : aBound1( rMk ), aBound2( rPt ), Ring( pRing )
//STRIP001 {
//STRIP001  if( nMkOffset )
//STRIP001      aBound1.nNode += nMkOffset;
//STRIP001  if( nPtOffset )
//STRIP001      aBound2.nNode += nPtOffset;
//STRIP001
//STRIP001  aBound1.nContent.Assign( aBound1.nNode.GetNode().GetCntntNode(), 0 );
//STRIP001  aBound2.nContent.Assign( aBound2.nNode.GetNode().GetCntntNode(), 0 );
//STRIP001  pMark = &aBound1;
//STRIP001  pPoint = &aBound2;
//STRIP001 }

/*N*/ SwPaM::SwPaM( const SwNode& rMk, const SwNode& rPt,
/*N*/               long nMkOffset, long nPtOffset, SwPaM* pRing )
/*N*/   : aBound1( rMk ), aBound2( rPt ), Ring( pRing )
/*N*/ {
/*N*/   if( nMkOffset )
/*N*/       aBound1.nNode += nMkOffset;
/*N*/   if( nPtOffset )
/*N*/       aBound2.nNode += nPtOffset;
/*N*/
/*N*/   aBound1.nContent.Assign( aBound1.nNode.GetNode().GetCntntNode(), 0 );
/*N*/   aBound2.nContent.Assign( aBound2.nNode.GetNode().GetCntntNode(), 0 );
/*N*/   pMark = &aBound1;
/*N*/   pPoint = &aBound2;
/*N*/ }

//STRIP001 SwPaM::SwPaM( const SwNodeIndex& rMk, xub_StrLen nMkCntnt,
//STRIP001            const SwNodeIndex& rPt, xub_StrLen nPtCntnt, SwPaM* pRing )
//STRIP001  : aBound1( rMk ), aBound2( rPt ), Ring( pRing )
//STRIP001 {
//STRIP001  aBound1.nContent.Assign( rMk.GetNode().GetCntntNode(), nMkCntnt );
//STRIP001  aBound2.nContent.Assign( rPt.GetNode().GetCntntNode(), nPtCntnt );
//STRIP001  pMark = &aBound1;
//STRIP001  pPoint = &aBound2;
//STRIP001 }

/*N*/ SwPaM::SwPaM( const SwNode& rMk, xub_StrLen nMkCntnt,
/*N*/             const SwNode& rPt, xub_StrLen nPtCntnt, SwPaM* pRing )
/*N*/   : aBound1( rMk ), aBound2( rPt ), Ring( pRing )
/*N*/ {
/*N*/   aBound1.nContent.Assign( aBound1.nNode.GetNode().GetCntntNode(), nMkCntnt );
/*N*/   aBound2.nContent.Assign( aBound2.nNode.GetNode().GetCntntNode(), nPtCntnt );
/*N*/   pMark = &aBound1;
/*N*/   pPoint = &aBound2;
/*N*/ }

/*N*/ SwPaM::SwPaM( SwPaM &rPam )
/*N*/   : aBound1( *(rPam.pPoint) ), aBound2( *(rPam.pMark) ), Ring( &rPam )
/*N*/ {
/*N*/   pPoint = &aBound1;
/*N*/   pMark  = rPam.HasMark() ? &aBound2 : pPoint;
/*N*/ }

/*N*/ SwPaM::SwPaM( const SwNode& rNd, xub_StrLen nCntnt, SwPaM* pRing )
/*N*/   : aBound1( rNd ), aBound2( rNd ), Ring( pRing )
/*N*/ {
/*N*/   aBound1.nContent.Assign( aBound1.nNode.GetNode().GetCntntNode(), nCntnt );
/*N*/   aBound2.nContent = aBound1.nContent;
/*N*/   pPoint = pMark = &aBound1;
/*N*/ }

/*N*/ SwPaM::SwPaM( const SwNodeIndex& rNd, xub_StrLen nCntnt, SwPaM* pRing )
/*N*/   : aBound1( rNd ), aBound2( rNd ), Ring( pRing )
/*N*/ {
/*N*/   aBound1.nContent.Assign( rNd.GetNode().GetCntntNode(), nCntnt );
/*N*/   aBound2.nContent = aBound1.nContent;
/*N*/   pPoint = pMark = &aBound1;
/*N*/ }

/*N*/ SwPaM::~SwPaM() {}

/*N*/ void SwPaM::SetMark()
/*N*/ {
/*N*/   if(pPoint == &aBound1)
/*N*/       pMark = &aBound2;
/*N*/   else
/*N*/       pMark = &aBound1;
/*N*/   (*pMark) = (*pPoint);
/*N*/ }

/*N*/ #ifndef PRODUCT

/*N*/ void SwPaM::Exchange()
/*N*/ {
/*N*/   if(pPoint != pMark)
/*N*/   {
/*N*/       SwPosition *pTmp = pPoint;
/*N*/       pPoint = pMark;
/*N*/       pMark = pTmp;
/*N*/   }
/*N*/ }
/*N*/ #endif


/*?*/SwPaM &SwPaM::operator=( SwPaM &rPam )
/*?*/{
/*?*/   *pPoint = *( rPam.pPoint );
/*?*/   if( rPam.HasMark() )
/*?*/   {
/*?*/       SetMark();
/*?*/       *pMark = *( rPam.pMark );
/*?*/   }
/*?*/   else
/*?*/       DeleteMark();
/*?*/   return *this;
/*?*/}

// Bewegen des Cursors


/*N*/ FASTBOOL SwPaM::Move( SwMoveFn fnMove, SwGoInDoc fnGo )
/*N*/ {
/*N*/   return (*fnGo)( *this, fnMove );
/*N*/ }


/*************************************************************************
|*
|*    void SwPaM::MakeRegion( SwMoveFn, SwPaM*, const SwPaM* )
|*
|*    Beschreibung      Setzt den 1. SwPaM auf den uebergebenen SwPaM
|*                      oder setzt auf den Anfang oder Ende vom Document.
|*                      SPoint bleibt auf der Position stehen, GetMark aendert
|*                      sich entsprechend !
|*
|*    Parameter         SwDirection     gibt an, ob an Anfang / Ende
|*                      SwPaM *         der zu setzende Bereich
|*                      const SwPaM&    der enventuell vorgegeben Bereich
|*    Return-Werte      SwPaM*          der entsprehend neu gesetzte Bereich
|*
|*    Ersterstellung    JP 26.04.91
|*    Letzte Aenderung  JP 26.04.91
|*
*************************************************************************/


//STRIP001 SwPaM* SwPaM::MakeRegion( SwMoveFn fnMove, const SwPaM * pOrigRg )
//STRIP001 {
//STRIP001  SwPaM* pPam;
//STRIP001  if( pOrigRg == 0 )
//STRIP001  {
//STRIP001      pPam = new SwPaM( *pPoint );
//STRIP001      pPam->SetMark();                    // setze Anfang fest
//STRIP001      pPam->Move( fnMove, fnGoSection);       // an Anfang / Ende vom Node
//STRIP001
//STRIP001      // stelle SPoint wieder auf alte Position, GetMark auf das "Ende"
//STRIP001      pPam->Exchange();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pPam = new SwPaM( *(SwPaM*)pOrigRg );   // die Suchregion ist vorgegeben
//STRIP001      // sorge dafuer, dass SPoint auf dem "echten" StartPunkt steht
//STRIP001      // FORWARD  --> SPoint immer kleiner  als GetMark
//STRIP001      // BACKWARD --> SPoint immer groesser als GetMark
//STRIP001      if( (pPam->GetMark()->*fnMove->fnCmpOp)( *pPam->GetPoint() ) )
//STRIP001          pPam->Exchange();
//STRIP001  }
//STRIP001  return pPam;
//STRIP001 }

//STRIP001 SwPaM & SwPaM::Normalize(BOOL bPointFirst)
//STRIP001 {
//STRIP001     if (HasMark())
//STRIP001         if ((bPointFirst && *pPoint > *pMark) ||
//STRIP001             (! bPointFirst && *pPoint < *pMark))
//STRIP001             Exchange();
//STRIP001
//STRIP001     return *this;
//STRIP001 }

/*N*/ USHORT SwPaM::GetPageNum( BOOL bAtPoint, const Point* pLayPos )
/*N*/ {
/*N*/   // return die Seitennummer am Cursor
/*N*/   // (fuer Reader + Seitengebundene Rahmen)
/*N*/   const SwCntntFrm* pCFrm;
/*N*/   const SwPageFrm *pPg;
/*N*/   const SwCntntNode *pNd ;
/*N*/   const SwPosition* pPos = bAtPoint ? pPoint : pMark;
/*N*/
/*N*/   if( 0 != ( pNd = pPos->nNode.GetNode().GetCntntNode() ) &&
/*N*/       0 != ( pCFrm = pNd->GetFrm( pLayPos, pPos, FALSE )) &&
/*N*/       0 != ( pPg = pCFrm->FindPageFrm() ))
/*N*/       return pPg->GetPhyPageNum();
/*N*/   return 0;
/*N*/ }

// steht in etwas geschuetztem oder in die Selektion umspannt
// etwas geschuetztes.
/*N*/ FASTBOOL SwPaM::HasReadonlySel() const
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;
/*N*/   Point aTmpPt;
/*N*/   const SwCntntNode *pNd;
/*N*/   const SwCntntFrm *pFrm;
/*N*/
/*N*/   if( 0 != ( pNd = GetPoint()->nNode.GetNode().GetCntntNode() ))
/*N*/       pFrm = pNd->GetFrm( &aTmpPt, GetPoint(), FALSE );
/*N*/   else
/*N*/       pFrm = 0;
/*N*/
/*N*/   if( pFrm && pFrm->IsProtected() )
/*N*/       bRet = TRUE;
/*N*/   else if( pNd )
/*N*/   {
/*N*/       const SwSectionNode* pSNd = pNd->GetSectionNode();
/*N*/       if( pSNd && pSNd->GetSection().IsProtectFlag() )
/*N*/           bRet = TRUE;
/*N*/   }
/*N*/
/*N*/   if( !bRet && HasMark() && GetPoint()->nNode != GetMark()->nNode )
/*N*/   {
/*?*/       if( 0 != ( pNd = GetMark()->nNode.GetNode().GetCntntNode() ))
/*?*/           pFrm = pNd->GetFrm( &aTmpPt, GetMark(), FALSE );
/*?*/       else
/*?*/           pFrm = 0;
/*?*/
/*?*/       if( pFrm && pFrm->IsProtected() )
/*?*/           bRet = TRUE;
/*?*/       else if( pNd )
/*?*/       {
/*?*/           const SwSectionNode* pSNd = pNd->GetSectionNode();
/*?*/           if( pSNd && pSNd->GetSection().IsProtectFlag() )
/*?*/               bRet = TRUE;
/*?*/       }
/*?*/
/*?*/       // oder sollte eine geschuetzte Section innerhalb der
/*?*/       // Selektion liegen?
/*?*/       if( !bRet )
/*?*/       {
/*?*/           ULONG nSttIdx = GetMark()->nNode.GetIndex(),
/*?*/                   nEndIdx = GetPoint()->nNode.GetIndex();
/*?*/           if( nEndIdx <= nSttIdx )
/*?*/           {
/*?*/               ULONG nTmp = nSttIdx;
/*?*/               nSttIdx = nEndIdx;
/*?*/               nEndIdx = nTmp;
/*?*/           }
/*?*/
/*?*/           // wenn ein geschuetzter Bereich zwischen den Nodes stehen soll,
/*?*/           // muss die Selektion selbst schon x Nodes umfassen.
/*?*/           // (TxtNd, SectNd, TxtNd, EndNd, TxtNd )
/*?*/           if( nSttIdx + 3 < nEndIdx )
/*?*/           {
/*?*/               const SwSectionFmts& rFmts = GetDoc()->GetSections();
/*?*/               for( USHORT n = rFmts.Count(); n;  )
/*?*/               {
/*?*/                   const SwSectionFmt* pFmt = rFmts[ --n ];
/*?*/                   if( pFmt->GetProtect().IsCntntProtected() )
/*?*/                   {
/*?*/                       const SwFmtCntnt& rCntnt = pFmt->GetCntnt(FALSE);
/*?*/                       ASSERT( rCntnt.GetCntntIdx(), "wo ist der SectionNode?" );
/*?*/                       ULONG nIdx = rCntnt.GetCntntIdx()->GetIndex();
/*?*/                       if( nSttIdx <= nIdx && nEndIdx >= nIdx &&
/*?*/                           rCntnt.GetCntntIdx()->GetNode().GetNodes().IsDocNodes() )
/*?*/                       {
/*                          // ist es keine gelinkte Section, dann kann sie auch
                            // nicht mitselektiert werden
                            const SwSection& rSect = *pFmt->GetSection();
                            if( CONTENT_SECTION == rSect.GetType() )
                            {
                                RestoreSavePos();
                                return TRUE;
                            }
*/
/*?*/                           bRet = TRUE;
/*?*/                           break;
/*?*/                       }
/*?*/                   }
/*?*/               }

#ifdef CHECK_CELL_READONLY
//JP 22.01.99: bisher wurden Tabelle, die in der Text-Selektion standen
//              nicht beachtet. Wollte man das haben, dann muss dieser
//              Code freigeschaltet werden

/*?*/               if( !bRet )
/*?*/               {
/*?*/                   // dann noch ueber alle Tabellen
/*?*/                   const SwFrmFmts& rFmts = *GetDoc()->GetTblFrmFmts();
/*?*/                   for( n = rFmts.Count(); n ;  )
/*?*/                   {
/*?*/                       SwFrmFmt* pFmt = (SwFrmFmt*)rFmts[ --n ];
/*?*/                       const SwTable* pTbl = SwTable::FindTable( pFmt );
/*?*/                       ULONG nIdx = pTbl ? pTbl->GetTabSortBoxes()[0]->GetSttIdx()
/*?*/                                         : 0;
/*?*/                       if( nSttIdx <= nIdx && nEndIdx >= nIdx )
/*?*/                       {
/*?*/                           // dann teste mal alle Boxen
/*?*/                           const SwTableSortBoxes& rBoxes = pTbl->GetTabSortBoxes();
/*?*/
/*?*/                           for( USHORT i =  rBoxes.Count(); i; )
/*?*/                               if( rBoxes[ --i ]->GetFrmFmt()->GetProtect().
/*?*/                                   IsCntntProtected() )
/*?*/                               {
/*?*/                                   bRet = TRUE;
/*?*/                                   break;
/*?*/                               }
/*?*/
/*?*/                           if( bRet )
/*?*/                               break;
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/ #endif
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//--------------------  Suche nach Formaten( FormatNamen ) -----------------

// die Funktion gibt in Suchrichtung den folgenden Node zurueck.
// Ist in der Richtung keiner mehr vorhanden oder ist dieser ausserhalb
// des Bereiches, wird ein 0 Pointer returnt.
// Das rbFirst gibt an, ob es man zu erstenmal einen Node holt. Ist das der
// Fall, darf die Position vom Pam nicht veraendert werden!


//STRIP001 SwCntntNode* GetNode( SwPaM & rPam, FASTBOOL& rbFirst, SwMoveFn fnMove,
//STRIP001                      FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  SwCntntNode * pNd = 0;
//STRIP001  SwCntntFrm* pFrm;
//STRIP001  if( ((*rPam.GetPoint()).*fnMove->fnCmpOp)( *rPam.GetMark() ) ||
//STRIP001      ( *rPam.GetPoint() == *rPam.GetMark() && rbFirst ) )
//STRIP001  {
//STRIP001      if( rbFirst )
//STRIP001      {
//STRIP001          rbFirst = FALSE;
//STRIP001          pNd = rPam.GetCntntNode();
//STRIP001          if( pNd &&
//STRIP001              ( 0 == ( pFrm = pNd->GetFrm()) ||
//STRIP001                ( !bInReadOnly && pFrm->IsProtected() ) ||
//STRIP001                (pFrm->IsTxtFrm() && ((SwTxtFrm*)pFrm)->IsHiddenNow()) ) ||
//STRIP001              ( !bInReadOnly && pNd->FindSectionNode() &&
//STRIP001                pNd->FindSectionNode()->GetSection().IsProtect() ))
//STRIP001              pNd = 0;
//STRIP001      }
//STRIP001
//STRIP001      if( !pNd )          // steht Cursor auf keinem ContentNode ?
//STRIP001      {
//STRIP001          SwPosition aPos( *rPam.GetPoint() );
//STRIP001          FASTBOOL bSrchForward = fnMove == fnMoveForward;
//STRIP001          SwNodes& rNodes = aPos.nNode.GetNodes();
//STRIP001
//STRIP001          // zum naechsten / vorherigen ContentNode
//STRIP001 // Funktioniert noch alles, wenn die Uerbpruefung vom ueberspringen der
//STRIP001 // Sektions herausgenommen wird ??
//STRIP001 //           if( (*fnMove->fnNds)( rNodes, &aPos.nNode ) )
//STRIP001          while( TRUE )
//STRIP001          {
//STRIP001              pNd = bSrchForward
//STRIP001                      ? rNodes.GoNextSection( &aPos.nNode, TRUE, !bInReadOnly )
//STRIP001                      : rNodes.GoPrevSection( &aPos.nNode, TRUE, !bInReadOnly );
//STRIP001              if( pNd )
//STRIP001              {
//STRIP001                  aPos.nContent.Assign( pNd, ::GetSttOrEnd( bSrchForward,*pNd ));
//STRIP001                  // liegt Position immer noch im Bereich ?
//STRIP001                  if( (aPos.*fnMove->fnCmpOp)( *rPam.GetMark() ) )
//STRIP001                  {
//STRIP001                      // nur in der AutoTextSection koennen Node stehen, die
//STRIP001                      // nicht angezeigt werden !!
//STRIP001                      if( 0 == ( pFrm = pNd->GetFrm()) ||
//STRIP001                          ( !bInReadOnly && pFrm->IsProtected() ) ||
//STRIP001                          ( pFrm->IsTxtFrm() &&
//STRIP001                              ((SwTxtFrm*)pFrm)->IsHiddenNow() ) )
//STRIP001
//STRIP001 //                           rNodes[ rNodes.EndOfAutotext ]->StartOfSection().GetIndex()
//STRIP001 //                           < aPos.nNode.GetIndex() && aPos.nNode.GetIndex()
//STRIP001 //                           < rNodes.EndOfAutotext.GetIndex() &&
//STRIP001 //                           0 == ( pFrm = pNd->GetFrm()) &&
//STRIP001 //                           pFrm->IsProtected() )
//STRIP001                      {
//STRIP001                          pNd = 0;
//STRIP001                          continue;       // suche weiter
//STRIP001                      }
//STRIP001                      *(SwPosition*)rPam.GetPoint() = aPos;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pNd = 0;            // kein gueltiger Node
//STRIP001                  break;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pNd;
//STRIP001 }

// ----------------------------------------------------------------------

// hier folgen die Move-Methoden ( Foward, Backward; Content, Node, Doc )


/*N*/ void GoStartDoc( SwPosition * pPos )
/*N*/ {
/*N*/   SwNodes& rNodes = pPos->nNode.GetNodes();
/*N*/   pPos->nNode = *rNodes.GetEndOfContent().StartOfSectionNode();
/*N*/   // es muss immer ein ContentNode gefunden werden !!
/*N*/   SwCntntNode* pCNd = rNodes.GoNext( &pPos->nNode );
/*N*/   if( pCNd )
/*N*/       pCNd->MakeStartIndex( &pPos->nContent );
/*N*/ }


/*N*/ void GoEndDoc( SwPosition * pPos )
/*N*/ {
/*N*/   SwNodes& rNodes = pPos->nNode.GetNodes();
/*N*/   pPos->nNode = rNodes.GetEndOfContent();
/*N*/   SwCntntNode* pCNd = GoPreviousNds( &pPos->nNode, TRUE );
/*N*/   if( pCNd )
/*N*/       pCNd->MakeEndIndex( &pPos->nContent );
/*N*/ }


/*N*/ void GoStartSection( SwPosition * pPos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // springe zum Anfang der Section
//STRIP001  SwNodes& rNodes = pPos->nNode.GetNodes();
//STRIP001  USHORT nLevel = rNodes.GetSectionLevel( pPos->nNode );
//STRIP001  if( pPos->nNode < rNodes.GetEndOfContent().StartOfSectionIndex() )
//STRIP001      nLevel--;
//STRIP001  do { rNodes.GoStartOfSection( &pPos->nNode ); } while( nLevel-- );
//STRIP001
//STRIP001  // steht jetzt schon auf einem CntntNode
//STRIP001  pPos->nNode.GetNode().GetCntntNode()->MakeStartIndex( &pPos->nContent );
/*N*/ }

// gehe an das Ende der akt. Grund-Section


/*N*/ void GoEndSection( SwPosition * pPos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // springe zum Anfang/Ende der Section
//STRIP001  SwNodes& rNodes = pPos->nNode.GetNodes();
//STRIP001  USHORT nLevel = rNodes.GetSectionLevel( pPos->nNode );
//STRIP001  if( pPos->nNode < rNodes.GetEndOfContent().StartOfSectionIndex() )
//STRIP001      nLevel--;
//STRIP001  do { rNodes.GoEndOfSection( &pPos->nNode ); } while( nLevel-- );
//STRIP001
//STRIP001  // steht jetzt auf einem EndNode, also zum vorherigen CntntNode
//STRIP001  if( GoPreviousNds( &pPos->nNode, TRUE ) )
//STRIP001      pPos->nNode.GetNode().GetCntntNode()->MakeEndIndex( &pPos->nContent );
/*N*/ }



/*N*/ FASTBOOL GoInDoc( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {
/*N*/   (*fnMove->fnDoc)( rPam.GetPoint() );
/*N*/   return TRUE;
/*N*/ }


/*N*/ FASTBOOL GoInSection( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  (*fnMove->fnSections)( (SwPosition*)rPam.GetPoint() );
/*N*/   return TRUE;
/*N*/ }


/*N*/ FASTBOOL GoInNode( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {
/*N*/   SwCntntNode *pNd = (*fnMove->fnNds)( &rPam.GetPoint()->nNode, TRUE );
/*N*/   if( pNd )
/*N*/       rPam.GetPoint()->nContent.Assign( pNd,
/*N*/                       ::binfilter::GetSttOrEnd( fnMove == fnMoveForward, *pNd ) );
/*N*/   return 0 != pNd;
/*N*/ }


/*N*/ FASTBOOL GoInCntnt( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {
/*N*/   if( (*fnMove->fnNd)( &rPam.GetPoint()->nNode.GetNode(),
/*N*/                       &rPam.GetPoint()->nContent, CRSR_SKIP_CHARS ))
/*N*/       return TRUE;
/*N*/   return GoInNode( rPam, fnMove );
/*N*/ }

/*N*/ FASTBOOL GoInCntntCells( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  if( (*fnMove->fnNd)( &rPam.GetPoint()->nNode.GetNode(),
//STRIP001                       &rPam.GetPoint()->nContent, CRSR_SKIP_CELLS ))
//STRIP001      return TRUE;
//STRIP001  return GoInNode( rPam, fnMove );
/*N*/ }

// --------- Funktionsdefinitionen fuer die SwCrsrShell --------------


/*N*/ FASTBOOL GoPrevPara( SwPaM & rPam, SwPosPara aPosPara )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( rPam.Move( fnMoveBackward, fnGoNode ) )
//STRIP001  {
//STRIP001      // steht immer auf einem ContentNode !
//STRIP001      SwPosition& rPos = *rPam.GetPoint();
//STRIP001      SwCntntNode * pNd = rPos.nNode.GetNode().GetCntntNode();
//STRIP001      rPos.nContent.Assign( pNd,
//STRIP001                          ::GetSttOrEnd( aPosPara == fnMoveForward, *pNd ) );
//STRIP001      return TRUE;
//STRIP001  }
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GoCurrPara( SwPaM & rPam, SwPosPara aPosPara )
/*N*/ {
/*N*/   SwPosition& rPos = *rPam.GetPoint();
/*N*/   SwCntntNode * pNd = rPos.nNode.GetNode().GetCntntNode();
/*N*/   if( pNd )
/*N*/   {
/*N*/       xub_StrLen nOld = rPos.nContent.GetIndex(),
/*N*/                  nNew = aPosPara == fnMoveForward ? 0 : pNd->Len();
/*N*/       // stand er schon auf dem Anfang/Ende dann zum naechsten/vorherigen
/*N*/       if( nOld != nNew )
/*N*/       {
/*N*/           rPos.nContent.Assign( pNd, nNew );
/*N*/           return TRUE;
/*N*/       }
/*N*/   }
/*N*/   // den Node noch etwas bewegen ( auf den naechsten/vorh. CntntNode)
/*N*/   if( ( aPosPara==fnParaStart && 0 != ( pNd =
/*N*/           GoPreviousNds( &rPos.nNode, TRUE ))) ||
/*N*/       ( aPosPara==fnParaEnd && 0 != ( pNd =
/*N*/           GoNextNds( &rPos.nNode, TRUE ))) )
/*N*/   {
/*N*/       rPos.nContent.Assign( pNd,
/*N*/                       ::binfilter::GetSttOrEnd( aPosPara == fnMoveForward, *pNd ));
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GoNextPara( SwPaM & rPam, SwPosPara aPosPara )
/*N*/ {
/*N*/   if( rPam.Move( fnMoveForward, fnGoNode ) )
/*N*/   {
/*N*/       // steht immer auf einem ContentNode !
/*N*/       SwPosition& rPos = *rPam.GetPoint();
/*N*/       SwCntntNode * pNd = rPos.nNode.GetNode().GetCntntNode();
/*N*/       rPos.nContent.Assign( pNd,
/*N*/                       ::binfilter::GetSttOrEnd( aPosPara == fnMoveForward, *pNd ) );
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }



/*N*/ FASTBOOL GoCurrSection( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {
/*N*/   SwPosition& rPos = *rPam.GetPoint();
/*N*/   SwPosition aSavePos( rPos );        // eine Vergleichsposition
/*N*/   SwNodes& rNds = aSavePos.nNode.GetNodes();
/*N*/   (rNds.*fnMove->fnSection)( &rPos.nNode );
/*N*/   SwCntntNode *pNd;
/*N*/   if( 0 == ( pNd = rPos.nNode.GetNode().GetCntntNode()) &&
/*N*/       0 == ( pNd = (*fnMove->fnNds)( &rPos.nNode, TRUE )) )
/*N*/   {
/*?*/       rPos = aSavePos;        // Cusror nicht veraendern
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   rPos.nContent.Assign( pNd,
/*N*/                       ::binfilter::GetSttOrEnd( fnMove == fnMoveForward, *pNd ) );
/*N*/   return aSavePos != rPos;
/*N*/ }


/*N*/ FASTBOOL GoNextSection( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwPosition& rPos = *rPam.GetPoint();
//STRIP001  SwPosition aSavePos( rPos );        // eine Vergleichsposition
//STRIP001  SwNodes& rNds = aSavePos.nNode.GetNodes();
//STRIP001  rNds.GoEndOfSection( &rPos.nNode );
//STRIP001
//STRIP001  // kein weiterer ContentNode vorhanden ?
//STRIP001  if( !GoInCntnt( rPam, fnMoveForward ) )
//STRIP001  {
//STRIP001      rPos = aSavePos;        // Cusror nicht veraendern
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  (rNds.*fnMove->fnSection)( &rPos.nNode );
//STRIP001  SwCntntNode *pNd = rPos.nNode.GetNode().GetCntntNode();
//STRIP001  rPos.nContent.Assign( pNd,
//STRIP001                      ::GetSttOrEnd( fnMove == fnMoveForward, *pNd ) );
/*N*/   return TRUE;
/*N*/ }


/*N*/ FASTBOOL GoPrevSection( SwPaM & rPam, SwMoveFn fnMove )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwPosition& rPos = *rPam.GetPoint();
//STRIP001  SwPosition aSavePos( rPos );        // eine Vergleichsposition
//STRIP001  SwNodes& rNds = aSavePos.nNode.GetNodes();
//STRIP001  rNds.GoStartOfSection( &rPos.nNode );
//STRIP001
//STRIP001  // kein weiterer ContentNode vorhanden ?
//STRIP001  if( !GoInCntnt( rPam, fnMoveBackward ))
//STRIP001  {
//STRIP001      rPos = aSavePos;        // Cusror nicht veraendern
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  (rNds.*fnMove->fnSection)( &rPos.nNode );
//STRIP001  SwCntntNode *pNd = rPos.nNode.GetNode().GetCntntNode();
//STRIP001  rPos.nContent.Assign( pNd,
//STRIP001                          ::GetSttOrEnd( fnMove == fnMoveForward, *pNd ));
/*N*/   return TRUE;
/*N*/ }




}
