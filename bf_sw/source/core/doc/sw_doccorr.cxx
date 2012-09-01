/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <horiornt.hxx>
#include <osl/diagnose.h>

#include <doc.hxx>
#include <rootfrm.hxx>
#include <viscrs.hxx>
#include <bookmrk.hxx>
#include <mvsave.hxx>
#include <docary.hxx>
#include <unocrsr.hxx>


#include <hints.hxx>
namespace binfilter {


/*
 * MACROS um ueber alle CrsrShells zu iterieren
 */
#define PCURSH ((SwCrsrShell*)_pStartShell)

#define PCURCRSR (_pCurrCrsr)
#define FOREACHPAM_START(pSttCrsr) \
    {\
        SwPaM *_pStartCrsr = pSttCrsr, *_pCurrCrsr = pSttCrsr; \
        do {

#define FOREACHPAM_END() \
        } while( (_pCurrCrsr=(SwPaM *)_pCurrCrsr->GetNext()) != _pStartCrsr ); \
    }


#define _PaMCorrAbs1( pPam ) \
    for( int nb = 0; nb < 2; ++nb ) \
        if( &((pPam)->GetBound( BOOL(nb) ).nNode.GetNode()) == pOldNode )   \
        { \
            (pPam)->GetBound( BOOL(nb) ) = aNewPos; \
            (pPam)->GetBound( BOOL(nb) ).nContent += nOffset; \
        }



/*N*/ void PaMCorrAbs( const SwNodeIndex &rOldNode,
/*N*/               const SwPosition &rNewPos,
/*N*/               const xub_StrLen nOffset)
/*N*/ {
/*N*/   const SwNode* pOldNode = &rOldNode.GetNode();
/*N*/   const SwPosition aNewPos( rNewPos );
/*N*/   const SwDoc* pDoc = pOldNode->GetDoc();
/*N*/
/*N*/   {
/*N*/       register SwUnoCrsrTbl& rTbl = (SwUnoCrsrTbl&)pDoc->GetUnoCrsrTbl();
/*N*/       for( USHORT n = 0; n < rTbl.Count(); ++n )
/*N*/       {
/*N*/           FOREACHPAM_START( rTbl[ n ] )
/*N*/               _PaMCorrAbs1( PCURCRSR )
/*N*/           FOREACHPAM_END()
/*N*/
/*N*/           SwUnoTableCrsr* pUnoTblCrsr = (SwUnoTableCrsr*)*rTbl[ n ];
/*N*/           if( pUnoTblCrsr )
/*N*/           {
/*?*/               FOREACHPAM_START( &pUnoTblCrsr->GetSelRing() )
/*?*/                   _PaMCorrAbs1( PCURCRSR )
/*?*/               FOREACHPAM_END()
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/ }



/*N*/ void SwDoc::CorrAbs( const SwNodeIndex& rOldNode,
/*N*/                    const SwPosition& rNewPos,
/*N*/                    const xub_StrLen nOffset,
/*N*/                    BOOL bMoveCrsr )
/*N*/ {
/*N*/   SwPosition aNewPos( rNewPos );
/*N*/
/*N*/   if( bMoveCrsr )
/*N*/       ::binfilter::PaMCorrAbs( rOldNode, rNewPos, nOffset );
/*N*/ }


/*N*/ bool _PaMCorrAbs2( SwPaM* pPam,
/*N*/                    const SwPosition& rNewPos,
/*N*/                    ULONG nSttNode, ULONG nEndNode )
/*N*/ {
/*N*/     bool bRet = false;
/*N*/
/*N*/   for( int nb = 0; nb < 2; ++nb ) \
/*N*/       if( (pPam)->GetBound( BOOL(nb) ).nNode >= nSttNode &&
/*N*/           (pPam)->GetBound( BOOL(nb) ).nNode <= nEndNode )
/*N*/         {
/*N*/           (pPam)->GetBound( BOOL(nb) ) = rNewPos;
/*N*/             bRet = true;
/*N*/         }
/*N*/
/*N*/     return bRet;
/*N*/ }

// find the relevant section in which the SwUnoCrsr may wander. returns NULL if
// no restrictions apply
/*N*/ const SwStartNode* lcl_FindUnoCrsrSection( const SwNode& rNode )
/*N*/ {
/*N*/     const SwStartNode* pStartNode = rNode.StartOfSectionNode();
/*N*/     while( ( pStartNode != NULL ) &&
/*N*/            ( pStartNode->StartOfSectionNode() != pStartNode ) &&
/*N*/            ( pStartNode->GetStartNodeType() == SwNormalStartNode ) )
/*N*/         pStartNode = pStartNode->StartOfSectionNode();
/*N*/
/*N*/     return pStartNode;
/*N*/ }

/*N*/ void PaMCorrAbs( const SwNodeIndex &rStartNode,
/*N*/                const SwNodeIndex &rEndNode,
/*N*/                const SwPosition &rNewPos )
/*N*/ {
/*N*/   const ULONG nSttNode = rStartNode.GetIndex();
/*N*/   const ULONG nEndNode = rEndNode.GetIndex();
/*N*/   const SwPosition aNewPos( rNewPos );
/*N*/   SwDoc* pDoc = rStartNode.GetNode().GetDoc();
/*N*/
/*N*/   {
/*N*/       register SwUnoCrsrTbl& rTbl = (SwUnoCrsrTbl&)pDoc->GetUnoCrsrTbl();
/*N*/       for( USHORT n = 0; n < rTbl.Count(); ++n )
/*N*/       {
/*N*/             bool bChange = false;
/*N*/
/*N*/             SwUnoCrsr* pUnoCursor = rTbl[ n ];
/*N*/
/*N*/             // determine whether the UNO cursor will leave it's designated
/*N*/             // section
/*N*/             bool bLeaveSection =
/*N*/                 pUnoCursor->IsRemainInSection() &&
/*N*/                 ( lcl_FindUnoCrsrSection( aNewPos.nNode.GetNode() ) !=
/*N*/                   lcl_FindUnoCrsrSection(
/*N*/                       pUnoCursor->GetPoint()->nNode.GetNode() ) );
/*N*/
/*N*/           FOREACHPAM_START( pUnoCursor )
/*N*/               bChange |= _PaMCorrAbs2(PCURCRSR, aNewPos, nSttNode, nEndNode);
/*N*/           FOREACHPAM_END()
/*N*/
/*N*/           SwUnoTableCrsr* pUnoTblCrsr = (SwUnoTableCrsr*)*pUnoCursor;
/*N*/           if( pUnoTblCrsr )
/*N*/           {
/*?*/               FOREACHPAM_START( &pUnoTblCrsr->GetSelRing() )
/*?*/                   bChange |=
/*?*/                         _PaMCorrAbs2( PCURCRSR, aNewPos, nSttNode, nEndNode );
/*?*/               FOREACHPAM_END()
/*N*/           }
/*N*/
/*N*/             // if a UNO cursor leaves its designated section, we must inform
/*N*/             // (and invalidate) said cursor
/*N*/             if( bChange && bLeaveSection )
/*N*/             {
/*N*/                 // the UNO cursor has left its section. We need to notify it!
/*?*/                 SwMsgPoolItem aHint( RES_UNOCURSOR_LEAVES_SECTION );
/*?*/                 pUnoCursor->Modify( &aHint, NULL );
/*N*/             }
/*N*/       }
/*N*/   }
/*N*/ }



/*N*/ void SwDoc::CorrAbs( const SwNodeIndex& rStartNode,
/*N*/                    const SwNodeIndex& rEndNode,
/*N*/                    const SwPosition& rNewPos,
/*N*/                    BOOL bMoveCrsr )
/*N*/ {
/*N*/   rStartNode.GetIndex();
/*N*/   rEndNode.GetIndex();
/*N*/   SwPosition aNewPos( rNewPos );
/*N*/
/*N*/       // erstmal die Bookmarks/Redlines korrigieren
/*N*/       _DelBookmarks( rStartNode, rEndNode );
/*N*/
/*N*/   if( bMoveCrsr )
/*N*/       ::binfilter::PaMCorrAbs( rStartNode, rEndNode, rNewPos );
/*N*/ }



#define _PaMCorrAbs3( pPam ) \
    for( int nb = 0; nb < 2; ++nb ) \
        if( aStart <= (pPam)->GetBound( BOOL(nb) ) && \
            (pPam)->GetBound( BOOL(nb) ) <= aEnd ) \
            (pPam)->GetBound( BOOL(nb) ) = aNewPos;

/*N*/ void PaMCorrAbs( const SwPaM& rRange,
/*N*/               const SwPosition& rNewPos )
/*N*/ {
/*N*/   SwPosition aStart( *rRange.Start() );
/*N*/   SwPosition aEnd( *rRange.End() );
/*N*/   SwPosition aNewPos( rNewPos );
/*N*/   SwDoc* pDoc = aStart.nNode.GetNode().GetDoc();
/*N*/
/*N*/   {
/*N*/       register SwUnoCrsrTbl& rTbl = (SwUnoCrsrTbl&)pDoc->GetUnoCrsrTbl();
/*N*/       for( USHORT n = 0; n < rTbl.Count(); ++n )
/*N*/       {
/*N*/           FOREACHPAM_START( rTbl[ n ] )
/*N*/               _PaMCorrAbs3( PCURCRSR )
/*N*/           FOREACHPAM_END()
/*N*/       }
/*N*/   }
/*N*/ }





#define _PaMCorrRel1( pPam ) \
    for( int nb = 0; nb < 2; ++nb ) \
        if( &((pPam)->GetBound( BOOL(nb) ).nNode.GetNode()) == pOldNode ) \
        { \
            (pPam)->GetBound( BOOL(nb) ).nNode = aNewPos.nNode; \
            (pPam)->GetBound( BOOL(nb) ).nContent.Assign( (SwIndexReg*) \
                            aNewPos.nContent.GetIdxReg(), \
                            nCntIdx + (pPam)->GetBound( BOOL(nb) ).nContent. \
                                GetIndex() ); \
        }



/*N*/ void PaMCorrRel( const SwNodeIndex &rOldNode,
/*N*/                const SwPosition &rNewPos,
/*N*/                const xub_StrLen nOffset )
/*N*/ {
/*N*/   const SwNode* pOldNode = &rOldNode.GetNode();
/*N*/   SwPosition aNewPos( rNewPos );
/*N*/   const SwDoc* pDoc = pOldNode->GetDoc();
/*N*/
/*N*/   xub_StrLen nCntIdx = rNewPos.nContent.GetIndex() + nOffset;
/*N*/
/*N*/   {
/*N*/       register SwUnoCrsrTbl& rTbl = (SwUnoCrsrTbl&)pDoc->GetUnoCrsrTbl();
/*N*/       for( USHORT n = 0; n < rTbl.Count(); ++n )
/*N*/       {
/*N*/           FOREACHPAM_START( rTbl[ n ] )
/*N*/               _PaMCorrRel1( PCURCRSR )
/*N*/           FOREACHPAM_END()
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SwDoc::CorrRel( const SwNodeIndex& rOldNode,
/*N*/                    const SwPosition& rNewPos,
/*N*/                    const xub_StrLen nOffset,
/*N*/                    BOOL bMoveCrsr )
/*N*/ {
/*N*/   const SwNode* pOldNode = &rOldNode.GetNode();
/*N*/   SwPosition aNewPos( rNewPos );
/*N*/   xub_StrLen nCntIdx = aNewPos.nContent.GetIndex() + nOffset;
/*N*/
/*N*/   { // erstmal die Bookmark korrigieren
/*N*/       register SwBookmarks& rBkmks = *pBookmarkTbl;
/*N*/       register SwBookmark* pBkmk;
/*N*/       for( USHORT n = 0; n < rBkmks.Count(); ++n )
/*N*/       {
/*N*/           // liegt auf der Position ??
/*N*/           int bChgd = FALSE;
/*N*/           if( &( pBkmk = (SwBookmark*)rBkmks[ n ])->pPos1->nNode.GetNode()
/*N*/               == pOldNode )
/*N*/           {
/*?*/               pBkmk->pPos1->nNode = aNewPos.nNode;
/*?*/               pBkmk->pPos1->nContent.Assign( (SwIndexReg*)
/*?*/                           aNewPos.nContent.GetIdxReg(),
/*?*/                           nCntIdx + pBkmk->pPos1->nContent.GetIndex() );
/*?*/               bChgd = 1;
/*N*/           }
/*N*/           if( pBkmk->pPos2 && &pBkmk->pPos2->nNode.GetNode() == pOldNode )
/*N*/           {
/*?*/               pBkmk->pPos2->nNode = aNewPos.nNode;
/*?*/               pBkmk->pPos2->nContent.Assign( (SwIndexReg*)
/*?*/                           aNewPos.nContent.GetIdxReg(),
/*?*/                           nCntIdx + pBkmk->pPos2->nContent.GetIndex() );
/*?*/               bChgd = 2;
/*N*/           }
/*N*/           // ungueltige Selektion? Dann die Klammerung aufheben
/*N*/           if( bChgd && pBkmk->pPos2 &&
/*N*/               pBkmk->pPos2->nNode.GetNode().FindTableBoxStartNode() !=
/*N*/               pBkmk->pPos1->nNode.GetNode().FindTableBoxStartNode() )
/*N*/           {
/*N*/               DBG_BF_ASSERT(0, "STRIP");
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( bMoveCrsr )
/*N*/       ::binfilter::PaMCorrRel( rOldNode, rNewPos, nOffset );
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
