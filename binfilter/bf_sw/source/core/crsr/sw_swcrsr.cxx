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

#include <hintids.hxx>

#include <com/sun/star/i18n/WordType.hdl>
#include <com/sun/star/i18n/CharType.hdl>

#include <osl/diagnose.h>

#include <unocrsr.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <section.hxx>
#include <docsh.hxx>
#include <crsskip.hxx>
#include <mdiexp.hxx>           // ...Percent()
#include <statstr.hrc>          // ResId fuer Statusleiste
namespace binfilter {

using namespace ::com::sun::star::i18n;

static const USHORT coSrchRplcThreshold = 60000;

struct _PercentHdl
{
    SwDocShell* pDSh;
    ULONG nActPos;
    BOOL bBack, bNodeIdx;

    _PercentHdl( ULONG nStt, ULONG nEnd, SwDocShell* pSh )
        : pDSh( pSh )
    {
        nActPos = nStt;
        if( 0 != ( bBack = (nStt > nEnd )) )
        {
            ULONG n = nStt; nStt = nEnd; nEnd = n;
        }
        ::binfilter::StartProgress( STR_STATSTR_SEARCH, nStt, nEnd, 0 );
    }

    _PercentHdl( const SwPaM& rPam )
        : pDSh( (SwDocShell*)rPam.GetDoc()->GetDocShell() )
    {
        ULONG nStt, nEnd;
        if( rPam.GetPoint()->nNode == rPam.GetMark()->nNode )
        {
            bNodeIdx = FALSE;
            nStt = rPam.GetMark()->nContent.GetIndex();
            nEnd = rPam.GetPoint()->nContent.GetIndex();
        }
        else
        {
            nStt = rPam.GetMark()->nNode.GetIndex();
            nEnd = rPam.GetPoint()->nNode.GetIndex();
        }
        nActPos = nStt;
        if( 0 != ( bBack = (nStt > nEnd )) )
        {
            ULONG n = nStt; nStt = nEnd; nEnd = n;
        }
        ::binfilter::StartProgress( STR_STATSTR_SEARCH, nStt, nEnd, pDSh );
    }

    ~_PercentHdl()                      { ::binfilter::EndProgress( pDSh ); }

    void NextPos( ULONG nPos ) const
    { ::binfilter::SetProgressState( bBack ? nActPos - nPos : nPos, pDSh ); }

    void NextPos( SwPosition& rPos ) const
        {
            ULONG nPos;
            if( bNodeIdx )
                nPos = rPos.nNode.GetIndex();
            else
                nPos = rPos.nContent.GetIndex();
            ::binfilter::SetProgressState( bBack ? nActPos - nPos : nPos, pDSh );
        }
};

/*N*/ SwCursor::SwCursor( const SwPosition &rPos, SwPaM* pRing )
/*N*/       : SwPaM( rPos, pRing ), pSavePos( 0 ), nCursorBidiLevel( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwCursor::~SwCursor()
/*N*/ {
/*N*/   while( pSavePos )
/*N*/   {
/*?*/       _SwCursor_SavePos* pNext1 = pSavePos->pNext;
/*?*/       delete pSavePos;
/*?*/       pSavePos = pNext1;
/*N*/   }
/*N*/ }

// Sicher die aktuelle Position, damit ggfs. auf diese zurueck
// gefallen werden kann. Die SavePos Objekte werden als Stack verwaltet,
// damit das auch alles bei verschachtelten Aufrufen funktioniert.
// Das CreateNewSavePos ist virtual, damit abgeleitete Klassen vom Cursor
// gegebenenfalls eigene SaveObjecte anlegen und in den virtuellen
// Check-Routinen verwenden koennen.

/*N*/ void SwCursor::SaveState()
/*N*/ {
/*N*/   _SwCursor_SavePos* pNew = CreateNewSavePos();
/*N*/   pNew->pNext = pSavePos;
/*N*/   pSavePos = pNew;
/*N*/ }

/*N*/ void SwCursor::RestoreState()
/*N*/ {
/*N*/   _SwCursor_SavePos* pDel = pSavePos;
/*N*/   pSavePos = pSavePos->pNext;
/*N*/   delete pDel;
/*N*/ }

/*N*/ _SwCursor_SavePos* SwCursor::CreateNewSavePos() const
/*N*/ {
/*N*/   return new _SwCursor_SavePos( *this );
/*N*/ }

// stelle fest, ob sich der Point ausserhalb des Content-Bereichs
// vom Nodes-Array befindet

/*N*/ bool SwCursor::IsSelOvr( int eFlags )
/*N*/ {
/*N*/   SwTableCursor* pTblCrsr = *this;
/*N*/   SwDoc* pDoc = GetDoc();
/*N*/   SwNodes& rNds = pDoc->GetNodes();
/*N*/
/*N*/   BOOL bSkipOverHiddenSections, bSkipOverProtectSections;
/*N*/   SwUnoCrsr* pUnoCrsr = *this;
/*N*/   if( pUnoCrsr )
/*N*/   {
/*N*/       bSkipOverHiddenSections = pUnoCrsr->IsSkipOverHiddenSections();
/*N*/       bSkipOverProtectSections = pUnoCrsr->IsSkipOverProtectSections();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       bSkipOverHiddenSections = TRUE;
/*?*/       bSkipOverProtectSections = !IsReadOnlyAvailable();
/*N*/   }

    // Bereiche vom Nodes-Array ueberpruefen
/*N*/   if( (SELOVER_CHECKNODESSECTION & eFlags) && pTblCrsr && HasMark() )
/*N*/   {
/*?*/       SwNodeIndex aOldPos( rNds, pSavePos->nNode );
/*?*/       if( !CheckNodesRange( aOldPos, GetPoint()->nNode, TRUE ))
/*?*/       {
/*?*/           GetPoint()->nNode = aOldPos;
/*?*/           GetPoint()->nContent.Assign( GetCntntNode(), pSavePos->nCntnt );
/*?*/           return TRUE;
/*?*/       }
/*N*/   }

// neu: Bereiche ueberpruefen
// Anfang
/*N*/   if( pSavePos->nNode != GetPoint()->nNode.GetIndex() &&
/*N*/       //JP 28.10.97: Bug 45129 - im UI-ReadOnly ist alles erlaubt
/*N*/       ( !pDoc->GetDocShell() || !pDoc->GetDocShell()->IsReadOnlyUI() ))
/*N*/   {
/*N*/       // teste doch mal die neuen Sections:
/*N*/       SwNodeIndex& rPtIdx = GetPoint()->nNode;
/*N*/       const SwSectionNode* pSectNd = rPtIdx.GetNode().FindSectionNode();
/*N*/       if( pSectNd &&
/*N*/           ((bSkipOverHiddenSections && pSectNd->GetSection().IsHiddenFlag() ) ||
/*N*/            (bSkipOverProtectSections && pSectNd->GetSection().IsProtectFlag() )))
/*N*/       {
/*?*/   DBG_BF_ASSERT(0, "STRIP");
/*N*/       }

/*N*/   }
// Ende
// neu: Bereiche ueberpruefen

/*N*/   const SwNode* pNd = &GetPoint()->nNode.GetNode();


/*N*/   if( !HasMark() )
/*N*/       return FALSE;

/*N*/   const SwTableNode* pPtNd = pNd->FindTableNode();

/*N*/   const SwTableNode* pMrkNd = pNd->FindTableNode();
/*N*/
/*N*/   // beide in keinem oder beide im gleichen TableNode
/*N*/   if( ( !pMrkNd && !pPtNd ) || pPtNd == pMrkNd )
/*N*/       return FALSE;

/*?*/   return FALSE;       // was bleibt noch ??
/*N*/ }

#if defined( UNX ) || defined( MAC )
#define IDX     (*pCellStt)
#else
#define IDX     aCellStt
#endif

/*N*/ bool SwCursor::IsInProtectTable( bool /* bMove */, bool /*bChgCrsr*/ )
/*N*/ {
/*N*/   // stehe ich in einer Tabelle ??
/*N*/   GetDoc();
/*N*/   SwCntntNode* pCNd = GetCntntNode();
/*N*/   if( !pCNd || pSavePos->nNode == GetPoint()->nNode.GetIndex() ||
/*N*/       !pCNd->FindTableNode() ||
/*N*/       !pCNd->IsProtect() ||
/*N*/       IsReadOnlyAvailable() )
/*N*/       return FALSE;

/*?*/   OSL_ENSURE( FALSE, "sollte nie erreicht werden oder??" );
/*?*/   return  FALSE;
/*N*/ }

/*N*/ bool SwCursor::LeftRight( BOOL bLeft, USHORT nCnt, USHORT nMode,
/*N*/                               BOOL /*bVisualAllowed*/, BOOL /*bInsertCrsr*/ )
/*N*/ {
/*N*/   SwTableCursor* pTblCrsr = (SwTableCursor*)*this;
/*N*/   if( pTblCrsr )
/*N*/       return FALSE;
/*N*/
/*N*/     // calculate cursor bidi level
/*N*/     GetPoint()->nNode.GetNode();
/*N*/
/*N*/   // kann der Cursor n-mal weiterverschoben werden ?
/*N*/     SwCrsrSaveState aSave( *this );
/*N*/     SwMoveFn fnMove = bLeft ? fnMoveBackward : fnMoveForward;
/*N*/     SwGoInDoc fnGo = CRSR_SKIP_CELLS == nMode ? fnGoCntntCells : fnGoCntnt;
/*N*/     while( nCnt && Move( fnMove, fnGo ) )
/*N*/         --nCnt;
/*N*/
/*N*/   return 0 == nCnt && !IsInProtectTable( TRUE ) &&
/*N*/           !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
/*N*/ }

/*N*/ bool SwCursor::MovePara(SwWhichPara fnWhichPara, SwPosPara fnPosPara )
/*N*/ {
/*N*/   //JP 28.8.2001: for optimization test something before
/*N*/   const SwNode* pNd;
/*N*/   if( fnWhichPara == fnParaCurr ||
/*N*/       (( pNd = &GetPoint()->nNode.GetNode())->IsTxtNode() &&
/*N*/         pNd->GetNodes()[ pNd->GetIndex() +
/*N*/                   (fnWhichPara == fnParaNext ? 1 : -1 ) ]->IsTxtNode() ) )
/*N*/   {
/*N*/       return (*fnWhichPara)( *this, fnPosPara );
/*N*/   }
/*N*/   // else we must use the SaveStructure, because the next/prev is not
/*N*/   // a same node type.
/*N*/   SwCrsrSaveState aSave( *this );
/*N*/   return (*fnWhichPara)( *this, fnPosPara ) &&
/*N*/           !IsInProtectTable( TRUE ) &&
/*N*/           !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
/*N*/ }

/*N*/ bool SwCursor::MoveSection( SwWhichSection fnWhichSect,
/*N*/                               SwPosSection fnPosSect)
/*N*/ {
/*N*/   SwCrsrSaveState aSave( *this );
/*N*/   return (*fnWhichSect)( *this, fnPosSect ) &&
/*N*/           !IsInProtectTable( TRUE ) &&
/*N*/           !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
/*N*/ }

/*N*/ SwTableCursor::~SwTableCursor() {}

/*N*/ SwTableCursor::operator SwTableCursor* () { return this; }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
