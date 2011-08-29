/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/



#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <hintids.hxx>


#ifdef BIDI
#include <bf_svx/frmdiritem.hxx>
#endif

#include <horiornt.hxx>

#include <doc.hxx>
#include <rootfrm.hxx>
#include <pagefrm.hxx>
#include <viewimp.hxx>
#include <flyfrm.hxx>
#include <dview.hxx>
#include <viewopt.hxx>
#include <crsrsh.hxx>
#include <txtfrm.hxx>
#include <callnk.hxx>
#include <viscrs.hxx>
#include <section.hxx>
#include <globdoc.hxx>
#include <fmteiro.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::util;

/*N*/ TYPEINIT2(SwCrsrShell,ViewShell,SwModify);


// Funktion loescht, alle ueberlappenden Cursor aus einem Cursor-Ring
/*N*/ void CheckRange( SwCursor* );

//-----------------------------------------------------------------------

/*
 * Ueberpruefe ob der pCurCrsr in einen schon bestehenden Bereich zeigt.
 * Wenn ja, dann hebe den alten Bereich auf.
 */


/*N*/ void CheckRange( SwCursor* pCurCrsr )
/*N*/ {
/*N*/   const SwPosition *pStt = pCurCrsr->Start(),
/*N*/       *pEnd = pCurCrsr->GetPoint() == pStt ? pCurCrsr->GetMark() : pCurCrsr->GetPoint();
/*N*/
/*N*/   SwPaM *pTmpDel = 0,
/*N*/         *pTmp = (SwPaM*)pCurCrsr->GetNext();
/*N*/
/*N*/   // durchsuche den gesamten Ring
/*N*/   while( pTmp != pCurCrsr )
/*N*/   {
/*?*/       const SwPosition *pTmpStt = pTmp->Start(),
/*?*/                       *pTmpEnd = pTmp->GetPoint() == pTmpStt ?
/*?*/                                       pTmp->GetMark() : pTmp->GetPoint();
/*?*/       if( *pStt <= *pTmpStt )
/*?*/       {
/*?*/           if( *pEnd > *pTmpStt ||
/*?*/               ( *pEnd == *pTmpStt && *pEnd == *pTmpEnd ))
/*?*/               pTmpDel = pTmp;
/*?*/       }
/*?*/       else
/*?*/           if( *pStt < *pTmpEnd )
/*?*/               pTmpDel = pTmp;
        /*
         * liegt ein SPoint oder GetMark innerhalb vom Crsr-Bereich
         * muss der alte Bereich aufgehoben werden.
         * Beim Vergleich ist darauf zu achten, das SPoint nicht mehr zum
         * Bereich gehoert !
         */
/*?*/       pTmp = (SwPaM*)pTmp->GetNext();
/*?*/       if( pTmpDel )
/*?*/       {
/*?*/           delete pTmpDel;         // hebe alten Bereich auf
/*?*/           pTmpDel = 0;
/*?*/       }
/*N*/   }
/*N*/ }

// -------------- Methoden von der SwCrsrShell -------------


// gebe den aktuellen zurueck

/*N*/ SwPaM* SwCrsrShell::GetCrsr( bool /*bMakeTblCrsr*/ ) const
/*N*/ {
/*N*/   if( pTblCrsr )
/*N*/   {
        DBG_BF_ASSERT(0, "STRIP");
/*N*/   }
/*N*/   return pCurCrsr;
/*N*/ }

/*N*/ void SwCrsrShell::UpdateCrsrPos()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   ++nStartAction;
/*N*/   Size aOldSz( GetLayout()->Frm().SSize() );
/*N*/   SwCntntNode *pCNode = pCurCrsr->GetCntntNode();
/*N*/   SwCntntFrm  *pFrm = pCNode ?
/*N*/       pCNode->GetFrm( &pCurCrsr->GetPtPos(), pCurCrsr->GetPoint() ) :0;
/*N*/   if( !pFrm || (pFrm->IsTxtFrm() && ((SwTxtFrm*)pFrm)->IsHiddenNow()) )
/*N*/   {
/*?*/       SwCrsrMoveState aTmpState( MV_NONE );
/*?*/       aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
/*?*/       GetLayout()->GetCrsrOfst( pCurCrsr->GetPoint(), pCurCrsr->GetPtPos(),
/*?*/                                    &aTmpState );
/*?*/       if( pCurCrsr->HasMark())
/*?*/           pCurCrsr->DeleteMark();
/*N*/   }
/*N*/   --nStartAction;
/*N*/   if( aOldSz != GetLayout()->Frm().SSize() )
/*N*/       SizeChgNotify( GetLayout()->Frm().SSize() );
/*N*/ }

/*N*/ void SwCrsrShell::ShowCrsrs( BOOL bCrsrVis )
/*N*/ {
/*N*/   if( !bHasFocus || bAllProtect || bBasicHideCrsr )
/*?*/       return;

/*N*/   SET_CURR_SHELL( this );
/*N*/   SwShellCrsr* pAktCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
/*N*/   pAktCrsr->Show();
/*N*/
/*N*/   if( bSVCrsrVis && bCrsrVis )    // auch SV-Cursor wieder anzeigen
/*N*/       pVisCrsr->Show();
/*N*/ }


/*N*/ SwCntntFrm *SwCrsrShell::GetCurrFrm( const BOOL bCalcFrm ) const
/*N*/ {
/*N*/   SET_CURR_SHELL( (ViewShell*)this );
/*N*/   SwCntntFrm *pRet = 0;
/*N*/   SwCntntNode *pNd = pCurCrsr->GetCntntNode();
/*N*/   if ( pNd )
/*N*/   {
/*N*/       if ( bCalcFrm )
/*N*/       {
/*N*/           const USHORT* pST = &nStartAction;
/*N*/           ++(*((USHORT*)pST));
/*N*/           const Size aOldSz( GetLayout()->Frm().SSize() );
/*N*/           pRet = pNd->GetFrm( &pCurCrsr->GetPtPos(), pCurCrsr->GetPoint() );
/*N*/           --(*((USHORT*)pST));
/*N*/           if( aOldSz != GetLayout()->Frm().SSize() )
/*N*/               ((SwCrsrShell*)this)->SizeChgNotify( GetLayout()->Frm().SSize() );
/*N*/       }
/*N*/       else
/*N*/           pRet = pNd->GetFrm( &pCurCrsr->GetPtPos(), pCurCrsr->GetPoint(), FALSE);
/*N*/   }
/*N*/   return pRet;
/*N*/ }


// alle Attribut/Format-Aenderungen am akt. Node werden an den
// Link weitergeleitet.


/*N*/ void SwCrsrShell::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   USHORT nWhich = pOld ? pOld->Which()
/*N*/                        : pNew ? pNew->Which()
/*N*/                               : sal::static_int_cast<USHORT>(RES_MSG_BEGIN);
/*N*/   if( bCallChgLnk &&
/*N*/       ( nWhich < RES_MSG_BEGIN || nWhich >= RES_MSG_END ||
/*N*/           nWhich == RES_FMT_CHG || nWhich == RES_UPDATE_ATTR ||
/*N*/           nWhich == RES_ATTRSET_CHG ))
/*N*/       // die Messages werden nicht weitergemeldet
/*N*/       //MA 07. Apr. 94 fix(6681): RES_UPDATE_ATTR wird implizit vom
/*N*/       //SwTxtNode::Insert(SwTxtHint*, USHORT) abgesetzt; hier wird reagiert und
/*N*/       //vom Insert brauch nicht mehr die Keule RES_FMT_CHG versandt werden.
/*N*/       CallChgLnk();
/*N*/
/*N*/   if( aGrfArrivedLnk.IsSet() &&
/*N*/       ( RES_GRAPHIC_ARRIVED == nWhich || RES_GRAPHIC_SWAPIN == nWhich ))
/*?*/       aGrfArrivedLnk.Call( this );
/*N*/ }


// Abfrage, ob der aktuelle Cursor eine Selektion aufspannt,
// also, ob GetMark gesetzt und SPoint und GetMark unterschiedlich sind.


/*N*/ bool SwCrsrShell::HasSelection() const
/*N*/ {
/*N*/   SwPaM* pCrsr = IsTableMode() ? pTblCrsr : pCurCrsr;
/*N*/   return( IsTableMode() || ( pCurCrsr->HasMark() &&
/*N*/           *pCurCrsr->GetPoint() != *pCrsr->GetMark())
/*N*/       ? TRUE : FALSE );
/*N*/ }


/*N*/ void SwCrsrShell::CallChgLnk()
/*N*/ {
/*N*/   // innerhalb von Start-/End-Action kein Call, sondern nur merken,
/*N*/   // das sich etwas geaendert hat. Wird bei EndAction beachtet.
/*N*/   if( BasicActionPend() )
/*N*/       bChgCallFlag = TRUE;        // das Change merken
/*N*/   else if( aChgLnk.IsSet() )
/*N*/   {
/*N*/       if( bCallChgLnk )
/*N*/           aChgLnk.Call( this );
/*N*/       bChgCallFlag = FALSE;       // Flag zuruecksetzen
/*N*/   }
/*N*/ }

// loesche alle erzeugten Crsr, setze den Tabellen-Crsr und den letzten
// Cursor auf seinen TextNode (oder StartNode?).
// Beim naechsten ::GetCrsr werden sie wieder alle erzeugt
// Wird fuers Drag&Drop / ClipBorad-Paste in Tabellen benoetigt.

/*N*/ SwCrsrShell::~SwCrsrShell()
/*N*/ {
/*N*/   // wenn es nicht die letzte View so sollte zu mindest das
/*N*/   // Feld noch geupdatet werden.
/*N*/   if( GetNext() != this )
/*?*/       CheckTblBoxCntnt( pCurCrsr->GetPoint() );
/*N*/   else
/*N*/       ClearTblBoxCntnt();
/*N*/
/*N*/   delete pVisCrsr;
/*N*/   delete pTblCrsr;
/*N*/
     /*
     * Freigabe der Cursor
      */
/*N*/   while(pCurCrsr->GetNext() != pCurCrsr)
/*?*/       delete pCurCrsr->GetNext();
/*N*/   delete pCurCrsr;
/*N*/
/*N*/   // Stack freigeben
/*N*/   if( pCrsrStk )
/*N*/   {
/*?*/       while( pCrsrStk->GetNext() != pCrsrStk )
/*?*/           delete pCrsrStk->GetNext();
/*?*/       delete pCrsrStk;
/*N*/   }

    // JP 27.07.98: Bug 54025 - ggfs. den HTML-Parser, der als Client in
    //              der CursorShell haengt keine Chance geben, sich an den
    //              TextNode zu haengen.
/*N*/   if( GetRegisteredIn() )
/*N*/       pRegisteredIn->Remove( this );
/*N*/ }



//Sollte fuer das Clipboard der WaitPtr geschaltet werden?
//Warten bei TableMode, Mehrfachselektion und mehr als x Selektieren Absaetzen.





// steht der Curor auf einem "Symbol"-Zeichen


// zeige das akt. selektierte "Object" an
/*N*/ void SwCrsrShell::MakeSelVisible()
/*N*/ {
/*N*/   OSL_ENSURE( bHasFocus, "kein Focus aber Cursor sichtbar machen?" );
/*N*/   if( aCrsrHeight.Y() < aCharRect.Height() && aCharRect.Height() > VisArea().Height() )
/*N*/   {
/*N*/       SwRect aTmp( aCharRect );
/*N*/       long nDiff = aCharRect.Height() - VisArea().Height();
/*N*/       if( nDiff < aCrsrHeight.X() )
/*?*/           aTmp.Top( nDiff + aCharRect.Top() );
/*N*/       else
/*N*/       {
/*N*/           aTmp.Top( aCrsrHeight.X() + aCharRect.Top() );
/*N*/           aTmp.Height( aCrsrHeight.Y() );
/*N*/       }
/*N*/         if( !aTmp.HasArea() )
/*N*/         {
/*?*/             aTmp.SSize().Height() += 1;
/*?*/             aTmp.SSize().Width() += 1;
/*N*/         }
/*N*/       MakeVisible( aTmp );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if( aCharRect.HasArea() )
/*N*/           MakeVisible( aCharRect );
/*N*/       else
/*N*/       {
/*?*/           SwRect aTmp( aCharRect );
/*?*/           aTmp.SSize().Height() += 1; aTmp.SSize().Width() += 1;
/*?*/           MakeVisible( aTmp );
/*N*/       }
/*N*/   }
/*N*/ }


// suche eine gueltige ContentPosition (nicht geschuetzt/nicht versteckt)




/*N*/ bool SwCrsrShell::IsCrsrReadonly() const
/*N*/ {
/*N*/   if ( GetViewOptions()->IsReadonly() )
/*N*/   {
/*N*/       SwFrm *pFrm = GetCurrFrm( FALSE );
/*N*/       SwFlyFrm *pFly;
/*N*/       if( pFrm && pFrm->IsInFly() &&
/*N*/            (pFly = pFrm->FindFlyFrm())->GetFmt()->GetEditInReadonly().GetValue() &&
/*N*/            pFly->Lower() &&
/*N*/            !pFly->Lower()->IsNoTxtFrm() &&
/*N*/            !GetDrawView()->GetMarkList().GetMarkCount() )
/*N*/       {
/*N*/           return FALSE;
/*N*/       }
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

// SwCursor - Methode !!!!
/*N*/ bool SwCursor::IsReadOnlyAvailable() const
/*N*/ {
/*N*/   const SwShellCrsr* pShCrsr = *this;
/*N*/   const SwUnoCrsr* pUnoCrsr = *this;
/*N*/   return pShCrsr ? pShCrsr->GetShell()->IsReadOnlyAvailable() :
/*N*/       pUnoCrsr ? TRUE : FALSE;
/*N*/ }


#if defined(DBG_UTIL) || defined(WIN)

// gebe den Stack Cursor zurueck
/*N*/ SwPaM * SwCrsrShell::GetStkCrsr() const           { return pCrsrStk; }

// gebe den TabellenCrsr zurueck
/*N*/ const SwPaM* SwCrsrShell::GetTblCrs() const   { return pTblCrsr; }
/*N*/       SwPaM* SwCrsrShell::GetTblCrs()         { return pTblCrsr; }

// Abfrage, ob ueberhaupt eine Selektion existiert, sprich der akt. Cursor
// aufgespannt oder nicht der einzigste ist.

/*N*/ bool SwCrsrShell::IsSelection() const
/*N*/ {
/*N*/   return IsTableMode() || pCurCrsr->HasMark() ||
/*N*/           pCurCrsr->GetNext() != pCurCrsr;
/*N*/ }

#endif

/**
   Checks if a position is valid. To be valid the position's node must
   be a content node and the content must not be unregistered.

   @param aPos the position to check.
*/
/*N*/ static bool lcl_PosOk(SwPosition & aPos)
/*N*/ {
/*N*/     bool bResult = true;
/*N*/     SwPosition aTmpPos(aPos);
/*N*/     aTmpPos.nContent.Assign(0, 0);
/*N*/
/*N*/     if (aPos.nNode.GetNode().GetCntntNode() == NULL ||
/*N*/         aPos.nContent.GetIdxReg() == aTmpPos.nContent.GetIdxReg())
/*N*/         bResult = false;
/*N*/
/*N*/     return bResult;
/*N*/ }

/**
   Checks if a PaM is valid. For a PaM to be valid its point must be
   valid. Additionaly if the PaM has a mark this has to be valid, too.

   @param aPam the PaM to check
*/
/*N*/ static bool lcl_CrsrOk(SwPaM & aPam)
/*N*/ {
/*N*/     return lcl_PosOk(*aPam.GetPoint()) && (! aPam.HasMark()
/*N*/         || lcl_PosOk(*aPam.GetMark()));
/*N*/ }

/*N*/ void SwCrsrShell::ClearUpCrsrs()
/*N*/ {
/*N*/     // start of the ring
/*N*/     SwPaM * pStartCrsr = GetCrsr();
/*N*/     // start loop with second entry of the ring
/*N*/     SwPaM * pCrsr = (SwPaM *) pStartCrsr->GetNext();
/*N*/     SwPaM * pTmpCrsr;
/*N*/     bool bChanged = false;
/*N*/
    /*
       For all entries in the ring except the start entry delete the
        entry if it is invalid.
    */
/*N*/     while (pCrsr != pStartCrsr)
/*N*/     {
/*?*/         pTmpCrsr = (SwPaM *) pCrsr->GetNext();
/*?*/
/*?*/         if ( ! lcl_CrsrOk(*pCrsr))
/*?*/         {
/*?*/             delete pCrsr;
/*?*/
/*?*/             bChanged = true;
/*N*/         }
/*N*/
/*N*/         pCrsr = pTmpCrsr;
/*N*/     }
/*N*/
    /*
      If the start entry of the ring is invalid replace it with a
      cursor pointing to the beginning of the first content node in
      the document.
    */
/*N*/     if (! lcl_CrsrOk(*pStartCrsr))
/*N*/     {
/*?*/         SwNodes & aNodes = GetDoc()->GetNodes();
/*?*/         SwNodeIndex aIdx(*(aNodes.GetEndOfContent().StartOfSectionNode()));
/*?*/
/*?*/         SwNode * pNode = aNodes.GoNext(&aIdx);
/*?*/         bool bFound = (pNode != NULL);
/*?*/
/*?*/         OSL_ENSURE(bFound, "no content node found");
/*?*/
/*?*/         if (bFound)
/*?*/         {
/*?*/             SwPaM aTmpPam(*pNode);
/*?*/             *pStartCrsr = aTmpPam;
/*?*/         }
/*?*/
/*?*/         bChanged = true;
/*N*/     }

    /*
      If at least one of the cursors in the ring have been deleted or
      replaced, remove the table cursor.
    */
/*N*/     if (pTblCrsr != NULL && bChanged)
/*?*/         {DBG_BF_ASSERT(0, "STRIP"); }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
