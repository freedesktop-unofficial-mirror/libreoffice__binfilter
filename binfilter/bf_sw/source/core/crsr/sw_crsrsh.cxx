/*************************************************************************
 *
 *  $RCSfile: sw_crsrsh.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:08:51 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVDMODEL_HXX //autogen
#include <bf_svx/svdmodel.hxx>
#endif

#ifdef BIDI
#ifndef _SVX_FRMDIRITEM_HXX
#include <bf_svx/frmdiritem.hxx>
#endif
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>           // fuer ASSERT
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _CALLNK_HXX
#include <callnk.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>
#endif
#ifndef _SWGLOBDOCSH_HXX //autogen
#include <globdoc.hxx>
#endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>           // ...Percent()
#endif
#ifndef _FMTEIRO_HXX //autogen
#include <fmteiro.hxx>
#endif

using namespace com::sun::star;
using namespace com::sun::star::util;

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

/*N*/SwPaM * SwCrsrShell::CreateCrsr()
/*N*/{
DBG_ASSERT(0, "STRIP");  return NULL;//STRIP001     // Innerhalb der Tabellen-SSelection keinen neuen Crsr anlegen
//STRIP001  ASSERT( !IsTableMode(), "in Tabellen SSelection" );
//STRIP001
//STRIP001  // neuen Cursor als Kopie vom akt. und in den Ring aufnehmen
//STRIP001  // Verkettung zeigt immer auf den zuerst erzeugten, also vorwaerts
//STRIP001  SwShellCrsr* pNew = new SwShellCrsr( *pCurCrsr );
//STRIP001
//STRIP001  // hier den akt. Pam nur logisch Hiden, weil sonst die Invertierung
//STRIP001  // vom kopierten Pam aufgehoben wird !!
//STRIP001  pNew->Insert( pCurCrsr, 0 );
//STRIP001  pCurCrsr->Remove( 0, pCurCrsr->Count() );
//STRIP001
//STRIP001  pCurCrsr->DeleteMark();
//STRIP001
//STRIP001  UpdateCrsr( SwCrsrShell::SCROLLWIN );
//STRIP001 //   return pCurCrsr;
//STRIP001  return pNew;
/*N*/ }

// loesche den aktuellen Cursor und der folgende wird zum Aktuellen


//STRIP001 FASTBOOL SwCrsrShell::DestroyCrsr()
//STRIP001 {
//STRIP001  // Innerhalb der Tabellen-SSelection keinen neuen Crsr loeschen
//STRIP001  ASSERT( !IsTableMode(), "in Tabellen SSelection" );
//STRIP001
//STRIP001  // ist ueberhaupt ein naechtser vorhanden ?
//STRIP001  if(pCurCrsr->GetNext() == pCurCrsr)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
//STRIP001  SwCursor* pNext = (SwCursor*)pCurCrsr->GetNext();
//STRIP001  delete pCurCrsr;
//STRIP001  pCurCrsr = (SwShellCrsr*)*pNext;
//STRIP001  UpdateCrsr();
//STRIP001  return TRUE;
//STRIP001 }


// gebe den aktuellen zurueck

/*N*/ SwPaM* SwCrsrShell::GetCrsr( FASTBOOL bMakeTblCrsr ) const
/*N*/ {
/*N*/   if( pTblCrsr )
/*N*/   {
DBG_ASSERT(0, "STRIP"); //STRIP001  /*?*/       if( bMakeTblCrsr && pTblCrsr->IsCrsrMovedUpdt() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // geparkte Cursor werden nicht wieder erzeugt
//STRIP001 /*?*/            const SwCntntNode* pCNd;
//STRIP001 /*?*/            if( pTblCrsr->GetPoint()->nNode.GetIndex() &&
//STRIP001 /*?*/                pTblCrsr->GetMark()->nNode.GetIndex() &&
//STRIP001 /*?*/                0 != ( pCNd = pTblCrsr->GetCntntNode() ) && pCNd->GetFrm() &&
//STRIP001 /*?*/                0 != ( pCNd = pTblCrsr->GetCntntNode(FALSE) ) && pCNd->GetFrm())
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwShellTableCrsr* pTC = (SwShellTableCrsr*)pTblCrsr;
//STRIP001 /*?*/                GetLayout()->MakeTblCrsrs( *pTC );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( pTblCrsr->IsChgd() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwCrsrShell* pThis = (SwCrsrShell*)this;
//STRIP001 /*?*/            pThis->pCurCrsr = (SwShellCrsr*)
//STRIP001 /*?*/                            *pTblCrsr->MakeBoxSels( pThis->pCurCrsr );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   return pCurCrsr;
/*N*/ }


/*N*/ void SwCrsrShell::StartAction()
/*N*/ {
/*N*/   if( !ActionPend() )
/*N*/   {
/*N*/       // fuer das Update des Ribbon-Bars merken
/*N*/       const SwNode& rNd = pCurCrsr->GetPoint()->nNode.GetNode();
/*N*/       nAktNode = rNd.GetIndex();
/*N*/       nAktCntnt = pCurCrsr->GetPoint()->nContent.GetIndex();
/*N*/       nAktNdTyp = rNd.GetNodeType();
/*N*/       bAktSelection = *pCurCrsr->GetPoint() != *pCurCrsr->GetMark();
/*N*/       if( ND_TEXTNODE & nAktNdTyp )
/*N*/           nLeftFrmPos = SwCallLink::GetFrm( (SwTxtNode&)rNd, nAktCntnt, TRUE );
/*N*/       else
/*?*/           nLeftFrmPos = 0;
/*N*/   }
/*N*/   ViewShell::StartAction();           // zur ViewShell
/*N*/ }


/*N*/ void SwCrsrShell::EndAction( const BOOL bIdleEnd )
/*N*/ {
/*
//OS: Wird z.B. eine Basic-Action im Hintergrund ausgefuehrt, geht es so nicht
    if( !bHasFocus )
    {
        // hat die Shell nicht den Focus, dann nur das EndAction an
        // die ViewShell weitergeben.
        ViewShell::EndAction( bIdleEnd );
        return;
    }
*/

/*N*/   FASTBOOL bVis = bSVCrsrVis;

    // Idle-Formatierung ?
/*N*/   if( bIdleEnd && Imp()->GetRegion() )
/*N*/   {
/*?*/       pCurCrsr->Hide();

/*?*/ #ifdef SHOW_IDLE_REGION
/*?*/ if( GetWin() )
/*?*/ {
/*?*/   GetWin()->Push();
/*?*/   GetWin()->ChangePen( Pen( Color( COL_YELLOW )));
/*?*/   for( USHORT n = 0; n < aPntReg.Count(); ++n )
/*?*/   {
/*?*/       SwRect aIRect( aPntReg[n] );
/*?*/       GetWin()->DrawRect( aIRect.SVRect() );
/*?*/   }
/*?*/   GetWin()->Pop();
/*?*/ }
/*?*/ #endif

/*N*/   }

    // vor der letzten Action alle invaliden Numerierungen updaten
/*N*/   if( 1 == nStartAction )
/*N*/       GetDoc()->UpdateNumRule();
/*N*/
/*N*/   // Task: 76923: dont show the cursor in the ViewShell::EndAction() - call.
/*N*/   //              Only the UpdateCrsr shows the cursor.
/*N*/   BOOL bSavSVCrsrVis = bSVCrsrVis;
/*N*/   bSVCrsrVis = FALSE;
/*N*/
/*N*/   ViewShell::EndAction( bIdleEnd );   //der ViewShell den Vortritt lassen
/*N*/
/*N*/   bSVCrsrVis = bSavSVCrsrVis;
/*N*/
/*N*/   if( ActionPend() )
/*N*/   {
/*N*/       if( bVis )    // auch SV-Cursor wieder anzeigen
/*N*/           pVisCrsr->Show();
/*N*/
/*N*/       // falls noch ein ChgCall vorhanden ist und nur noch die Basic
/*N*/       // Klammerung vorhanden ist, dann rufe ihn. Dadurch wird die interne
/*N*/       // mit der Basic-Klammerung entkoppelt; die Shells werden umgeschaltet
/*N*/       if( !BasicActionPend() )
/*N*/       {
/*?*/           //JP 12.01.98: Bug #46496# - es muss innerhalb einer BasicAction
/*?*/           //              der Cursor geupdatet werden; um z.B. den
/*?*/           //              TabellenCursor zu erzeugen. Im UpdateCrsr wird
/*?*/           //              das jetzt beruecksichtigt!
DBG_ASSERT(0, "STRIP"); //STRIP001  /*?*/           UpdateCrsr( SwCrsrShell::CHKRANGE, bIdleEnd );
//STRIP001 /*?*/
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001 /*?*/                // der DTOR ist das interressante!!
//STRIP001 /*?*/                SwCallLink aLk( *this, nAktNode, nAktCntnt, (BYTE)nAktNdTyp,
//STRIP001 /*?*/                                                    nLeftFrmPos, bAktSelection );
//STRIP001 /*?*/
//STRIP001 /*?*/            }
//STRIP001 /*?*/            if( bCallChgLnk && bChgCallFlag && aChgLnk.IsSet() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                aChgLnk.Call( this );
//STRIP001 /*?*/                bChgCallFlag = FALSE;       // Flag zuruecksetzen
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       return;
/*N*/   }

/*N*/   USHORT nParm = SwCrsrShell::CHKRANGE;
/*N*/   if ( !bIdleEnd )
/*N*/       nParm |= SwCrsrShell::SCROLLWIN;
/*N*/   UpdateCrsr( nParm, bIdleEnd );      // Cursor-Aenderungen anzeigen
/*N*/
/*N*/   {
/*N*/       SwCallLink aLk( *this );        // Crsr-Moves ueberwachen,
/*N*/       aLk.nNode = nAktNode;           // evt. Link callen
/*N*/       aLk.nNdTyp = (BYTE)nAktNdTyp;
/*N*/       aLk.nCntnt = nAktCntnt;
/*N*/       aLk.nLeftFrmPos = nLeftFrmPos;
/*N*/
/*N*/       if( !nCrsrMove ||
/*N*/           ( 1 == nCrsrMove && bInCMvVisportChgd ) )
/*N*/           ShowCrsrs( bSVCrsrVis ? TRUE : FALSE );    // Cursor & Selektionen wieder anzeigen
/*N*/   }
/*N*/   // falls noch ein ChgCall vorhanden ist, dann rufe ihn
/*N*/   if( bCallChgLnk && bChgCallFlag && aChgLnk.IsSet() )
/*N*/   {
/*N*/       aChgLnk.Call( this );
/*N*/       bChgCallFlag = FALSE;       // Flag zuruecksetzen
/*N*/   }
/*N*/ }


/*?*/ #if !defined( PRODUCT )
/*?*/
/*?*/ void SwCrsrShell::SttCrsrMove()
/*?*/ {
/*?*/   ASSERT( nCrsrMove < USHRT_MAX, "To many nested CrsrMoves." );
/*?*/   ++nCrsrMove;
/*?*/   StartAction();
/*?*/ }
/*?*/
/*?*/ void SwCrsrShell::EndCrsrMove( const BOOL bIdleEnd )
/*?*/ {
/*?*/   ASSERT( nCrsrMove, "EndCrsrMove() ohne SttCrsrMove()." );
/*?*/   EndAction( bIdleEnd );
/*?*/   if( !--nCrsrMove )
/*?*/       bInCMvVisportChgd = FALSE;
/*?*/ }
/*?*/
/*?*/ #endif


//STRIP001 FASTBOOL SwCrsrShell::LeftRight( BOOL bLeft, USHORT nCnt, USHORT nMode,
//STRIP001                                  BOOL bVisualAllowed )
//STRIP001 {
//STRIP001  if( IsTableMode() )
//STRIP001      return bLeft ? GoPrevCell() : GoNextCell();
//STRIP001
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001     FASTBOOL bRet = pCurCrsr->LeftRight( bLeft, nCnt, nMode, bVisualAllowed,
//STRIP001                                          ! IsOverwriteCrsr() );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr();
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::UpDown( BOOL bUp, USHORT nCnt )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001
//STRIP001  BOOL bTableMode = IsTableMode();
//STRIP001  SwShellCrsr* pTmpCrsr = bTableMode ? pTblCrsr : pCurCrsr;
//STRIP001
//STRIP001  FASTBOOL bRet = pTmpCrsr->UpDown( bUp, nCnt );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      eMvState = MV_UPDOWN;       // Status fuers Crsr-Travelling - GetCrsrOfst
//STRIP001      if( !ActionPend() )
//STRIP001      {
//STRIP001          CrsrFlag eUpdtMode = SwCrsrShell::SCROLLWIN;
//STRIP001          if( !bTableMode )
//STRIP001              eUpdtMode = (CrsrFlag) (eUpdtMode
//STRIP001                          | SwCrsrShell::UPDOWN | SwCrsrShell::CHKRANGE);
//STRIP001          UpdateCrsr( eUpdtMode );
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::LRMargin( BOOL bLeft, BOOL bAPI)
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  eMvState = MV_LEFTMARGIN;       // Status fuers Crsr-Travelling - GetCrsrOfst
//STRIP001
//STRIP001  BOOL bTableMode = IsTableMode();
//STRIP001  SwShellCrsr* pTmpCrsr = bTableMode ? pTblCrsr : pCurCrsr;
//STRIP001  FASTBOOL bRet = pTmpCrsr->LeftRightMargin( bLeft, bAPI );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr();
//STRIP001  return bRet;
//STRIP001 }

/*N*/ FASTBOOL SwCrsrShell::IsAtLRMargin( BOOL bLeft, BOOL bAPI ) const
/*N*/ {
/*N*/   SwShellCrsr* pTmpCrsr = IsTableMode() ? pTblCrsr : pCurCrsr;
/*N*/   return pTmpCrsr->IsAtLeftRightMargin( bLeft, bAPI );
/*N*/ }


/*N*/ FASTBOOL SwCrsrShell::SttEndDoc( BOOL bStt )
/*N*/ {
/*?*/       DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001 //STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001
//STRIP001  FASTBOOL bRet = pCurCrsr->SttEndDoc( bStt );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      if( bStt )
//STRIP001          pCurCrsr->GetPtPos().Y() = 0;       // expl. 0 setzen (TabellenHeader)
//STRIP001
//STRIP001      UpdateCrsr(SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE|SwCrsrShell::READONLY);
//STRIP001  }
//STRIP001  return bRet;
/*N*/ }



//STRIP001 FASTBOOL SwCrsrShell::MovePage( SwWhichPage fnWhichPage, SwPosPage fnPosPage )
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001
//STRIP001  // Springe beim Selektieren nie ueber Section-Grenzen !!
//STRIP001  if( !pCurCrsr->HasMark() || !pCurCrsr->IsNoCntnt() )
//STRIP001  {
//STRIP001      SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001      SET_CURR_SHELL( this );
//STRIP001
//STRIP001      SwCrsrSaveState aSaveState( *pCurCrsr );
//STRIP001      Point& rPt = pCurCrsr->GetPtPos();
//STRIP001      SwCntntFrm * pFrm = pCurCrsr->GetCntntNode()->
//STRIP001                          GetFrm( &rPt, pCurCrsr->GetPoint() );
//STRIP001      if( pFrm && TRUE == ( bRet = GetFrmInPage( pFrm, fnWhichPage,
//STRIP001                                              fnPosPage, pCurCrsr )  ) &&
//STRIP001          !pCurCrsr->IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS ))
//STRIP001          UpdateCrsr();
//STRIP001      else
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::MovePara(SwWhichPara fnWhichPara, SwPosPara fnPosPara )
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  FASTBOOL bRet = pCurCrsr->MovePara( fnWhichPara, fnPosPara );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr();
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::MoveSection( SwWhichSection fnWhichSect,
//STRIP001                              SwPosSection fnPosSect)
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  FASTBOOL bRet = pCurCrsr->MoveSection( fnWhichSect, fnPosSect );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr();
//STRIP001  return bRet;
//STRIP001
//STRIP001 }


// Positionieren des Cursors


//STRIP001 SwFrm* lcl_IsInHeaderFooter( const SwNodeIndex& rIdx, Point& rPt )
//STRIP001 {
//STRIP001  SwFrm* pFrm = 0;
//STRIP001  SwCntntNode* pCNd = rIdx.GetNode().GetCntntNode();
//STRIP001  if( pCNd )
//STRIP001  {
//STRIP001      pFrm = pCNd->GetFrm( &rPt, 0, FALSE )->GetUpper();
//STRIP001      while( pFrm && !pFrm->IsHeaderFrm() && !pFrm->IsFooterFrm() )
//STRIP001          pFrm = pFrm->IsFlyFrm() ? ((SwFlyFrm*)pFrm)->GetAnchor()
//STRIP001                                  : pFrm->GetUpper();
//STRIP001  }
//STRIP001  return pFrm;
//STRIP001 }

//STRIP001 FASTBOOL SwCrsrShell::IsInHeaderFooter( FASTBOOL* pbInHeader ) const
//STRIP001 {
//STRIP001  SwShellCrsr* pCrsr = IsTableMode() ? pTblCrsr : pCurCrsr;
//STRIP001  Point aPt;
//STRIP001  SwFrm* pFrm = ::lcl_IsInHeaderFooter( pCurCrsr->GetPoint()->nNode, aPt );
//STRIP001  if( pFrm && pbInHeader )
//STRIP001      *pbInHeader = pFrm->IsHeaderFrm();
//STRIP001  return 0 != pFrm;
//STRIP001 }

/*N*/ int SwCrsrShell::SetCrsr( const Point &rLPt, BOOL bOnlyText )
/*N*/ {
DBG_ASSERT(0, "STRIP"); return 0;//STRIP001     SET_CURR_SHELL( this );
//STRIP001
//STRIP001  SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  SwShellCrsr* pCrsr = IsTableMode() ? pTblCrsr : pCurCrsr;
//STRIP001  SwPosition aPos( *pCrsr->GetPoint() );
//STRIP001  Point aPt( rLPt );
//STRIP001  Point & rAktCrsrPt = pCrsr->GetPtPos();
//STRIP001  SwCrsrMoveState aTmpState( IsTableMode() ? MV_TBLSEL :
//STRIP001                                  bOnlyText ?  MV_SETONLYTEXT : MV_NONE );
//STRIP001  aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
//STRIP001
//STRIP001  int bRet = CRSR_POSOLD |
//STRIP001              ( GetLayout()->GetCrsrOfst( &aPos, aPt, &aTmpState )
//STRIP001                  ? 0 : CRSR_POSCHG );
//STRIP001
//STRIP001     pCrsr->SetCrsrBidiLevel( aTmpState.nCursorBidiLevel );
//STRIP001
//STRIP001  if( MV_RIGHTMARGIN == aTmpState.eState )
//STRIP001      eMvState = MV_RIGHTMARGIN;
//STRIP001  // steht neu Pos im Header/Footer ?
//STRIP001  SwFrm* pFrm = lcl_IsInHeaderFooter( aPos.nNode, aPt );
//STRIP001  if( IsTableMode() && !pFrm && aPos.nNode.GetNode().FindStartNode() ==
//STRIP001      pCrsr->GetPoint()->nNode.GetNode().FindStartNode() )
//STRIP001      // gleiche Tabellenzelle und nicht im Header/Footer
//STRIP001      // -> zurueck
//STRIP001      return bRet;
//STRIP001
//STRIP001  if( !pCrsr->HasMark() )
//STRIP001  {
//STRIP001      // steht an der gleichen Position und wenn im Header/Footer,
//STRIP001      // dann im gleichen
//STRIP001      if( aPos == *pCrsr->GetPoint() )
//STRIP001      {
//STRIP001          if( pFrm )
//STRIP001          {
//STRIP001              if( pFrm->Frm().IsInside( rAktCrsrPt ))
//STRIP001                  return bRet;
//STRIP001          }
//STRIP001          else if( aPos.nNode.GetNode().IsCntntNode() )
//STRIP001          {
//STRIP001              // im gleichen Frame gelandet?
//STRIP001              SwFrm* pOld = ((SwCntntNode&)aPos.nNode.GetNode()).GetFrm(
//STRIP001                                      &aCharRect.Pos(), 0, FALSE );
//STRIP001              SwFrm* pNew = ((SwCntntNode&)aPos.nNode.GetNode()).GetFrm(
//STRIP001                                      &aPt, 0, FALSE );
//STRIP001              if( pNew == pOld )
//STRIP001                  return bRet;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // SSelection ueber nicht erlaubte Sections oder wenn im Header/Footer
//STRIP001      // dann in verschiedene
//STRIP001      if( !CheckNodesRange( aPos.nNode, pCrsr->GetMark()->nNode, TRUE )
//STRIP001          || ( pFrm && !pFrm->Frm().IsInside( pCrsr->GetMkPos() ) ))
//STRIP001          return bRet;
//STRIP001
//STRIP001      // steht an der gleichen Position und nicht im Header/Footer
//STRIP001      if( aPos == *pCrsr->GetPoint() )
//STRIP001          return bRet;
//STRIP001  }
//STRIP001
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  SwCrsrSaveState aSaveState( *pCrsr );
//STRIP001
//STRIP001  *pCrsr->GetPoint() = aPos;
//STRIP001  rAktCrsrPt = aPt;
//STRIP001
//STRIP001  if( !pCrsr->IsSelOvr( SELOVER_CHANGEPOS ) )
//STRIP001  {
//STRIP001      UpdateCrsr( SwCrsrShell::SCROLLWIN | SwCrsrShell::CHKRANGE);
//STRIP001      bRet &= ~CRSR_POSOLD;
//STRIP001  }
//STRIP001  else if( bOnlyText && !pCurCrsr->HasMark() )
//STRIP001  {
//STRIP001      if( FindValidCntntNode( bOnlyText ) )
//STRIP001      {
//STRIP001          // Cursor in einen gueltigen Content stellen
//STRIP001          if( aPos == *pCrsr->GetPoint() )
//STRIP001              bRet = CRSR_POSOLD;
//STRIP001          else
//STRIP001          {
//STRIP001              UpdateCrsr( SwCrsrShell::SCROLLWIN | SwCrsrShell::CHKRANGE );
//STRIP001              bRet &= ~CRSR_POSOLD;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // es gibt keinen gueltigen Inhalt -> Cursor verstecken
//STRIP001          pVisCrsr->Hide();       // sichtbaren Cursor immer verstecken
//STRIP001          eMvState = MV_NONE;     // Status fuers Crsr-Travelling
//STRIP001          bAllProtect = TRUE;
//STRIP001          if( GetDoc()->GetDocShell() )
//STRIP001          {
//STRIP001              GetDoc()->GetDocShell()->SetReadOnlyUI( TRUE );
//STRIP001              CallChgLnk();           // UI bescheid sagen!
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
/*N*/ }


//STRIP001 void SwCrsrShell::TblCrsrToCursor()
//STRIP001 {
//STRIP001  ASSERT( pTblCrsr, "TblCrsrToCursor: Why?" );
//STRIP001  delete pTblCrsr, pTblCrsr = 0;
//STRIP001 }


//STRIP001 void SwCrsrShell::ClearMark()
//STRIP001 {
//STRIP001  // ist ueberhaupt ein GetMark gesetzt ?
//STRIP001  if( pTblCrsr )
//STRIP001  {
//STRIP001      while( pCurCrsr->GetNext() != pCurCrsr )
//STRIP001          delete pCurCrsr->GetNext();
//STRIP001      pTblCrsr->DeleteMark();
//STRIP001
//STRIP001      if( pCurCrsr->HasMark() )
//STRIP001      {
//STRIP001          // falls doch nicht alle Indizies richtig verschoben werden
//STRIP001          //  (z.B.: Kopf-/Fusszeile loeschen) den Content-Anteil vom
//STRIP001          //  Mark aufs Nodes-Array setzen
//STRIP001          SwPosition& rPos = *pCurCrsr->GetMark();
//STRIP001          rPos.nNode.Assign( pDoc->GetNodes(), 0 );
//STRIP001          rPos.nContent.Assign( 0, 0 );
//STRIP001          pCurCrsr->DeleteMark();
//STRIP001      }
//STRIP001
//STRIP001      *pCurCrsr->GetPoint() = *pTblCrsr->GetPoint();
//STRIP001      pCurCrsr->GetPtPos() = pTblCrsr->GetPtPos();
//STRIP001      delete pTblCrsr, pTblCrsr = 0;
//STRIP001      pCurCrsr->SwSelPaintRects::Show();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !pCurCrsr->HasMark() )
//STRIP001          return;
//STRIP001      // falls doch nicht alle Indizies richtig verschoben werden
//STRIP001      //  (z.B.: Kopf-/Fusszeile loeschen) den Content-Anteil vom
//STRIP001      //  Mark aufs Nodes-Array setzen
//STRIP001      SwPosition& rPos = *pCurCrsr->GetMark();
//STRIP001      rPos.nNode.Assign( pDoc->GetNodes(), 0 );
//STRIP001      rPos.nContent.Assign( 0, 0 );
//STRIP001      pCurCrsr->DeleteMark();
//STRIP001      if( !nCrsrMove )
//STRIP001          pCurCrsr->SwSelPaintRects::Show();
//STRIP001  }
//STRIP001 }


//STRIP001 void SwCrsrShell::NormalizePam(BOOL bPointFirst)
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001     pCurCrsr->Normalize(bPointFirst);
//STRIP001 }

//STRIP001 void SwCrsrShell::SwapPam()
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  pCurCrsr->Exchange();
//STRIP001 }


// suche innerhalb der Selektierten-Bereiche nach einer Selektion, die
// den angebenen SPoint umschliesst
// Ist das Flag bTstOnly gesetzt, dann wird nur getestet, ob dort eine
// SSelection besteht; des akt. Cursr wird nicht umgesetzt!
// Ansonsten wird er auf die gewaehlte SSelection gesetzt.


//STRIP001 FASTBOOL SwCrsrShell::ChgCurrPam( const Point & rPt,
//STRIP001                            BOOL bTstOnly, BOOL bTstHit )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  // Pruefe ob der SPoint in einer Tabellen-Selektion liegt
//STRIP001  if( bTstOnly && pTblCrsr )
//STRIP001      return pTblCrsr->IsInside( rPt );
//STRIP001
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  // Suche die Position rPt im Dokument
//STRIP001  SwPosition aPtPos( *pCurCrsr->GetPoint() );
//STRIP001  Point aPt( rPt );
//STRIP001
//STRIP001  SwCrsrMoveState aTmpState( MV_NONE );
//STRIP001  aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
//STRIP001  if ( !GetLayout()->GetCrsrOfst( &aPtPos, aPt, &aTmpState ) && bTstHit )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche in allen Selektionen nach dieser Position
//STRIP001  SwShellCrsr* pCmp = (SwShellCrsr*)pCurCrsr;        // sicher den Pointer auf Cursor
//STRIP001  do {
//STRIP001      if( pCmp->HasMark() &&
//STRIP001          *pCmp->Start() <= aPtPos && *pCmp->End() > aPtPos )
//STRIP001      {
//STRIP001          if( bTstOnly || pCurCrsr == pCmp )     // ist der aktuelle.
//STRIP001              return TRUE;                       // return ohne Update
//STRIP001
//STRIP001          pCurCrsr = pCmp;
//STRIP001          UpdateCrsr();     // Cursor steht schon richtig
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  } while( pCurCrsr != ( pCmp = (SwShellCrsr*)*((SwCursor*)pCmp->GetNext()) ) );
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 void SwCrsrShell::KillPams()
//STRIP001 {
//STRIP001  // keiner zum loeschen vorhanden?
//STRIP001  if( !pTblCrsr && pCurCrsr->GetNext() == pCurCrsr )
//STRIP001      return;
//STRIP001
//STRIP001  while( pCurCrsr->GetNext() != pCurCrsr )
//STRIP001      delete pCurCrsr->GetNext();
//STRIP001
//STRIP001  if( pTblCrsr )
//STRIP001  {
//STRIP001      // Cursor Ring loeschen
//STRIP001      pCurCrsr->DeleteMark();
//STRIP001      *pCurCrsr->GetPoint() = *pTblCrsr->GetPoint();
//STRIP001      pCurCrsr->GetPtPos() = pTblCrsr->GetPtPos();
//STRIP001      delete pTblCrsr;
//STRIP001      pTblCrsr = 0;
//STRIP001  }
//STRIP001  UpdateCrsr( SwCrsrShell::SCROLLWIN );
//STRIP001 }


//STRIP001 int SwCrsrShell::CompareCursor( CrsrCompareType eType ) const
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  const SwPosition *pFirst = 0, *pSecond = 0;
//STRIP001  const SwPaM *pCur = GetCrsr(), *pStk = pCrsrStk;
//STRIP001  if( CurrPtCurrMk != eType && pStk )
//STRIP001  {
//STRIP001      switch ( eType)
//STRIP001      {
//STRIP001      case StackPtStackMk:
//STRIP001          pFirst = pStk->GetPoint();
//STRIP001          pSecond = pStk->GetMark();
//STRIP001          break;
//STRIP001      case StackPtCurrPt:
//STRIP001          pFirst = pStk->GetPoint();
//STRIP001          pSecond = pCur->GetPoint();
//STRIP001          break;
//STRIP001      case StackPtCurrMk:
//STRIP001          pFirst = pStk->GetPoint();
//STRIP001          pSecond = pCur->GetMark();
//STRIP001          break;
//STRIP001      case StackMkCurrPt:
//STRIP001          pFirst = pStk->GetMark();
//STRIP001          pSecond = pCur->GetPoint();
//STRIP001          break;
//STRIP001      case StackMkCurrMk:
//STRIP001          pFirst = pStk->GetMark();
//STRIP001          pSecond = pStk->GetMark();
//STRIP001          break;
//STRIP001      case CurrPtCurrMk:
//STRIP001          pFirst = pCur->GetPoint();
//STRIP001          pSecond = pCur->GetMark();
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  if( !pFirst || !pSecond )
//STRIP001      nRet = INT_MAX;
//STRIP001  else if( *pFirst < *pSecond )
//STRIP001      nRet = -1;
//STRIP001  else if( *pFirst == *pSecond )
//STRIP001      nRet = 0;
//STRIP001  else
//STRIP001      nRet = 1;
//STRIP001  return nRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::IsSttPara() const
//STRIP001 {   return( pCurCrsr->GetPoint()->nContent == 0 ? TRUE : FALSE ); }


//STRIP001 FASTBOOL SwCrsrShell::IsEndPara() const
//STRIP001 {   return( pCurCrsr->GetPoint()->nContent == pCurCrsr->GetCntntNode()->Len() ? TRUE : FALSE ); }


//STRIP001 FASTBOOL SwCrsrShell::GotoPage( USHORT nPage )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  SwCrsrSaveState aSaveState( *pCurCrsr );
//STRIP001  FASTBOOL bRet = GetLayout()->SetCurrPage( pCurCrsr, nPage ) &&
//STRIP001                  !pCurCrsr->IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
//STRIP001  if( bRet )
//STRIP001      UpdateCrsr(SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE|SwCrsrShell::READONLY);
//STRIP001  return bRet;
//STRIP001 }


/*N*/ void SwCrsrShell::GetPageNum( USHORT &rnPhyNum, USHORT &rnVirtNum,
/*N*/                             BOOL bAtCrsrPos, const BOOL bCalcFrm )
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   // Seitennummer: die erste sichtbare Seite oder die am Cursor
/*N*/   const SwCntntFrm* pCFrm;
/*N*/   const SwPageFrm *pPg = 0;
/*N*/
/*N*/   if( !bAtCrsrPos || 0 == (pCFrm = GetCurrFrm( bCalcFrm )) ||
/*N*/                      0 == (pPg   = pCFrm->FindPageFrm()) )
/*N*/   {
/*?*/       pPg = Imp()->GetFirstVisPage();
/*?*/       while( pPg && pPg->IsEmptyPage() )
/*?*/           pPg = (const SwPageFrm *)pPg->GetNext();
/*N*/   }
/*N*/   // Abfrage auf pPg muss fuer den Sonderfall Writerstart mit
/*N*/   // standard.vor sein.
/*N*/   rnPhyNum  = pPg? pPg->GetPhyPageNum() : 1;
/*N*/   rnVirtNum = pPg? pPg->GetVirtPageNum() : 1;
/*N*/ }


//STRIP001 USHORT SwCrsrShell::GetNextPrevPageNum( BOOL bNext )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  // Seitennummer: die erste sichtbare Seite oder die am Cursor
//STRIP001  const SwPageFrm *pPg = Imp()->GetFirstVisPage();
//STRIP001  if( pPg )
//STRIP001  {
//STRIP001      if( bNext )
//STRIP001      {
//STRIP001          // erstmal die sichtbare suchen !!
//STRIP001          while( pPg && pPg->IsEmptyPage() )
//STRIP001              pPg = (const SwPageFrm *)pPg->GetNext();
//STRIP001          while( pPg && 0 != (pPg = (const SwPageFrm *)pPg->GetNext() ) &&
//STRIP001                  pPg->IsEmptyPage() )
//STRIP001              ;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          while( pPg && 0 != (pPg = (const SwPageFrm *)pPg->GetPrev() ) &&
//STRIP001                  pPg->IsEmptyPage() )
//STRIP001              ;
//STRIP001      }
//STRIP001  }
//STRIP001  // Abfrage auf pPg muss fuer den Sonderfall Writerstart mit
//STRIP001  // standard.vor sein.
//STRIP001  return pPg ? pPg->GetPhyPageNum() : USHRT_MAX;
//STRIP001 }


/*N*/ USHORT SwCrsrShell::GetPageCnt()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   // gebe die Anzahl der Seiten zurueck
/*N*/   return GetLayout()->GetPageNum();
/*N*/ }

// Gehe zur naechsten SSelection


//STRIP001 FASTBOOL SwCrsrShell::GoNextCrsr()
//STRIP001 {
//STRIP001  // besteht ueberhaupt ein Ring ?
//STRIP001  if( pCurCrsr->GetNext() == pCurCrsr )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  pCurCrsr = (SwShellCrsr*)*((SwCursor*)pCurCrsr->GetNext());
//STRIP001
//STRIP001  // Bug 24086: auch alle anderen anzeigen
//STRIP001  if( !ActionPend() )
//STRIP001  {
//STRIP001      UpdateCrsr();
//STRIP001      pCurCrsr->Show();
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

// gehe zur vorherigen SSelection


//STRIP001 FASTBOOL SwCrsrShell::GoPrevCrsr()
//STRIP001 {
//STRIP001  // besteht ueberhaupt ein Ring ?
//STRIP001  if( pCurCrsr->GetNext() == pCurCrsr )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  pCurCrsr = (SwShellCrsr*)*((SwCursor*)pCurCrsr->GetPrev());
//STRIP001
//STRIP001  // Bug 24086: auch alle anderen anzeigen
//STRIP001  if( !ActionPend() )
//STRIP001  {
//STRIP001      UpdateCrsr();
//STRIP001      pCurCrsr->Show();
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 void SwCrsrShell::Paint( const Rectangle &rRect)
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  // beim Painten immer alle Cursor ausschalten
//STRIP001  SwRect aRect( rRect );
//STRIP001
//STRIP001  FASTBOOL bVis = FALSE;
//STRIP001  // ist Cursor sichtbar, dann verstecke den SV-Cursor
//STRIP001  if( pVisCrsr->IsVisible() && !aRect.IsOver( aCharRect ) )   //JP 18.06.97: ???
//STRIP001  {
//STRIP001      bVis = TRUE;
//STRIP001      pVisCrsr->Hide();
//STRIP001  }
//STRIP001
//STRIP001  ViewShell::Paint( rRect );      // Bereich neu painten
//STRIP001  if( bHasFocus && !bBasicHideCrsr )
//STRIP001  {
//STRIP001      SwShellCrsr* pAktCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001 //       pAktCrsr->Invalidate( aRect );
//STRIP001      if( !ActionPend() )
//STRIP001      {
//STRIP001          // damit nicht rechts/unten die Raender abgeschnitten werden
//STRIP001          pAktCrsr->Invalidate( VisArea() );
//STRIP001          pAktCrsr->Show();
//STRIP001      }
//STRIP001      else
//STRIP001          pAktCrsr->Invalidate( aRect );
//STRIP001
//STRIP001  }
//STRIP001  if( bSVCrsrVis && bVis )        // auch SV-Cursor wieder anzeigen
//STRIP001      pVisCrsr->Show();
//STRIP001 }



//STRIP001 void SwCrsrShell::VisPortChgd( const SwRect & rRect )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  FASTBOOL bVis;      // beim Scrollen immer alle Cursor ausschalten
//STRIP001
//STRIP001  // ist Cursor sichtbar, dann verstecke den SV-Cursor
//STRIP001  if( TRUE == ( bVis = pVisCrsr->IsVisible() ))
//STRIP001      pVisCrsr->Hide();
//STRIP001
//STRIP001  bVisPortChgd = TRUE;
//STRIP001  aOldRBPos.X() = VisArea().Right();
//STRIP001  aOldRBPos.Y() = VisArea().Bottom();
//STRIP001
//STRIP001  //Damit es es keine Probleme mit dem SV-Cursor gibt, wird in
//STRIP001  //ViewShell::VisPo.. ein Update() auf das Window gerufen.
//STRIP001  //Waehrend des Paintens duerfen aber nun wieder keine Selectionen
//STRIP001  //angezeigt werden, deshalb wird der Aufruf hier geklammert.
//STRIP001  ViewShell::VisPortChgd( rRect );        // Bereich verschieben
//STRIP001
//STRIP001 /*
//STRIP001  SwRect aRect( rRect );
//STRIP001  if( VisArea().IsOver( aRect ) )
//STRIP001      pCurCrsr->Invalidate( aRect );
//STRIP001 */
//STRIP001
//STRIP001  if( bSVCrsrVis && bVis )    // auch SV-Cursor wieder anzeigen
//STRIP001      pVisCrsr->Show();
//STRIP001
//STRIP001  if( nCrsrMove )
//STRIP001      bInCMvVisportChgd = TRUE;
//STRIP001
//STRIP001  bVisPortChgd = FALSE;
//STRIP001 }

// aktualisiere den Crsrs, d.H. setze ihn wieder in den Content.
// Das sollte nur aufgerufen werden, wenn der Cursor z.B. beim
// Loeschen von Rahmen irgendwohin gesetzt wurde. Die Position
// ergibt sich aus seiner aktuellen Position im Layout !!


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


//STRIP001 BOOL lcl_IsInValueBox( const SwPaM& rCrsr, SwCrsrShell& rShell )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwStartNode* pSttNd = rCrsr.GetNode()->FindSttNodeByType( SwTableBoxStartNode );
//STRIP001  if( pSttNd )
//STRIP001  {
//STRIP001      const SwFrmFmt* pFmt = pSttNd->FindTableNode()->GetTable().
//STRIP001                  GetTblBox( pSttNd->GetIndex() )->GetFrmFmt();
//STRIP001      bRet = SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_VALUE ) ||
//STRIP001              SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_FORMULA );
//STRIP001      // der WrtShell bescheid sagen!!!
//STRIP001      rShell.NewCoreSelection();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

// JP 30.04.99: Bug 65475 - falls Point/Mark in versteckten Bereichen
//              stehen, so mussen diese daraus verschoben werden
//STRIP001 void lcl_CheckHiddenSection( SwNodeIndex& rIdx )
//STRIP001 {
//STRIP001  const SwSectionNode* pSectNd = rIdx.GetNode().FindSectionNode();
//STRIP001  if( pSectNd && pSectNd->GetSection().IsHiddenFlag() )
//STRIP001  {
//STRIP001      SwNodeIndex aTmp( *pSectNd );
//STRIP001      const SwNode* pFrmNd = rIdx.GetNodes().FindPrvNxtFrmNode(
//STRIP001                                  aTmp, pSectNd->EndOfSectionNode() );
//STRIP001      ASSERT( pFrmNd, "keinen Node mit Frames gefunden" );
//STRIP001      rIdx = aTmp;
//STRIP001  }
//STRIP001 }

/*M*/ void SwCrsrShell::UpdateCrsr( USHORT eFlags, BOOL bIdleEnd )
/*M*/ {
/*M*/   SET_CURR_SHELL( this );
/*M*/
/*N*/     ClearUpCrsrs();
/*M*/
/*M*/   // erfrage den Count fuer die Start-/End-Actions und ob die Shell
/*M*/   // ueberhaupt den Focus hat
/*M*/ //    if( ActionPend() /*|| !bHasFocus*/ )
/*M*/   //JP 12.01.98: Bug #46496# - es muss innerhalb einer BasicAction der
/*M*/   //              Cursor geupdatet werden; um z.B. den TabellenCursor zu
/*M*/   //              erzeugen. Im EndAction wird jetzt das UpdateCrsr gerufen!
/*M*/   if( ActionPend() && BasicActionPend() )
/*M*/   {
/*M*/       if ( eFlags & SwCrsrShell::READONLY )
/*M*/           bIgnoreReadonly = TRUE;
/*M*/       return;             // wenn nicht, dann kein Update !!
/*M*/   }
/*M*/
/*M*/   if ( bIgnoreReadonly )
/*M*/   {
/*M*/       bIgnoreReadonly = FALSE;
/*M*/       eFlags |= SwCrsrShell::READONLY;
/*M*/   }
/*M*/
/*M*/   if( eFlags & SwCrsrShell::CHKRANGE )    // alle Cursor-Bewegungen auf
/*M*/       CheckRange( pCurCrsr );         // ueberlappende Bereiche testen
/*M*/
/*M*/   if( !bIdleEnd )
/*M*/       CheckTblBoxCntnt();
/*M*/
/*M*/   // steht der akt. Crsr in einer Tabelle und in unterschiedlichen Boxen
/*M*/   // (oder ist noch TabellenMode), dann gilt der Tabellen Mode
/*M*/   SwPaM* pTstCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
/*M*/   if( ( pTstCrsr->HasMark() &&
/*M*/         pDoc->IsIdxInTbl( pTstCrsr->GetPoint()->nNode ) &&
/*M*/         ( pTblCrsr ||
/*M*/           pTstCrsr->GetNode( TRUE )->FindStartNode() !=
/*M*/           pTstCrsr->GetNode( FALSE )->FindStartNode() ))
/*M*/       /*|| ( !pTblCrsr && lcl_IsInValueBox( *pTstCrsr, *this ) )*/ )
/*M*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SwShellCrsr* pITmpCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001 /*?*/        Point aTmpPt( pITmpCrsr->GetPtPos() );
//STRIP001 /*?*/        Point aTmpMk( pITmpCrsr->GetMkPos() );
//STRIP001 /*?*/        SwPosition* pPos = pITmpCrsr->GetPoint();
//STRIP001 /*?*/
//STRIP001 /*?*/        // JP 30.04.99: Bug 65475 - falls Point/Mark in versteckten Bereichen
//STRIP001 /*?*/        //              stehen, so mussen diese daraus verschoben werden
//STRIP001 /*?*/        ::lcl_CheckHiddenSection( pPos->nNode );
//STRIP001 /*?*/        ::lcl_CheckHiddenSection( pITmpCrsr->GetMark()->nNode );
//STRIP001 /*?*/
//STRIP001 /*?*/        SwCntntFrm *pTblFrm = pPos->nNode.GetNode().GetCntntNode()->
//STRIP001 /*?*/                                                GetFrm( &aTmpPt, pPos ),
//STRIP001 /*?*/                   *pMarkTblFrm;
//STRIP001 /*?*/        ASSERT( pTblFrm, "Tabelle Crsr nicht im Content ??" );
//STRIP001 /*?*/
//STRIP001 /*?*/        SwTabFrm *pTab = pTblFrm->FindTabFrm(), *pMarkTab;
//STRIP001 /*?*/
//STRIP001 /*?*/        if( pTab && pTab->GetTable()->IsHeadlineRepeat() && (
//STRIP001 /*?*/            ( pTab->IsFollow() &&
//STRIP001 /*?*/              ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pTblFrm )) ||
//STRIP001 /*?*/            ( (pMarkTab = (pMarkTblFrm = pITmpCrsr->GetCntntNode( FALSE )
//STRIP001 /*?*/                ->GetFrm( &aTmpMk, pITmpCrsr->GetMark() ))->FindTabFrm())->IsFollow() &&
//STRIP001 /*?*/                ((SwLayoutFrm*)pMarkTab->Lower())->IsAnLower( pMarkTblFrm )) ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // in wiederholten Tabellen-Kopfzeilen wollen wir keine
//STRIP001 /*?*/            // Tabellen-Selektion !!
//STRIP001 /*?*/            pTblFrm = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/            SwPosSection fnPosSect = *pPos <  *pITmpCrsr->GetMark()
//STRIP001 /*?*/                                        ? fnSectionStart
//STRIP001 /*?*/                                        : fnSectionEnd;
//STRIP001 /*?*/
//STRIP001 /*?*/            // dann nur innerhalb der Box selektieren
//STRIP001 /*?*/            if( pTblCrsr )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pCurCrsr->SetMark();
//STRIP001 /*?*/                *pCurCrsr->GetMark() = *pTblCrsr->GetMark();
//STRIP001 /*?*/                pCurCrsr->GetMkPos() = pTblCrsr->GetMkPos();
//STRIP001 /*?*/                pTblCrsr->DeleteMark();
//STRIP001 /*?*/                pTblCrsr->SwSelPaintRects::Hide();
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            *pCurCrsr->GetPoint() = *pCurCrsr->GetMark();
//STRIP001 /*?*/            (*fnSectionCurr)( *pCurCrsr, fnPosSect );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // wir wollen wirklich eine Tabellen-Selektion
//STRIP001 /*?*/        if( pTab && pTblFrm )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if( !pTblCrsr )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pTblCrsr = new SwShellTableCrsr( *this,
//STRIP001 /*?*/                                *pCurCrsr->GetMark(), pCurCrsr->GetMkPos(),
//STRIP001 /*?*/                                *pPos, aTmpPt );
//STRIP001 /*?*/                pCurCrsr->DeleteMark();
//STRIP001 /*?*/                pCurCrsr->SwSelPaintRects::Hide();
//STRIP001 /*?*/
//STRIP001 /*?*/                CheckTblBoxCntnt();
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if( !pTblFrm->GetCharRect( aCharRect, *pTblCrsr->GetPoint() ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                Point aCentrPt( aCharRect.Center() );
//STRIP001 /*?*/                SwCrsrMoveState aTmpState( MV_NONE );
//STRIP001 /*?*/                aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
//STRIP001 /*?*/                pTblFrm->GetCrsrOfst( pTblCrsr->GetPoint(), aCentrPt, &aTmpState );
//STRIP001 /*?*/                 if ( !pTblFrm->GetCharRect( aCharRect, *pTblCrsr->GetPoint() ) )
//STRIP001 /*?*/                    ASSERT( !this, "GetCharRect failed." );
//STRIP001 /*?*/            }
//STRIP001 /*?*/ //         ALIGNRECT( aCharRect );
//STRIP001 /*?*/
//STRIP001 /*?*/            pVisCrsr->Hide();       // sichtbaren Cursor immer verstecken
//STRIP001 /*?*/            // Curosr in den sichtbaren Bereich scrollen
//STRIP001 /*?*/            if( (eFlags & SwCrsrShell::SCROLLWIN) &&
//STRIP001 /*?*/                 (HasSelection() || eFlags & SwCrsrShell::READONLY ||
//STRIP001 /*?*/                 !IsCrsrReadonly()) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwFrm* pBoxFrm = pTblFrm;
//STRIP001 /*?*/                while( pBoxFrm && !pBoxFrm->IsCellFrm() )
//STRIP001 /*?*/                    pBoxFrm = pBoxFrm->GetUpper();
//STRIP001 /*?*/                if( pBoxFrm && pBoxFrm->Frm().HasArea() )
//STRIP001 /*?*/                    MakeVisible( pBoxFrm->Frm() );
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    MakeVisible( aCharRect );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // lasse vom Layout die Crsr in den Boxen erzeugen
//STRIP001 /*?*/            if( pTblCrsr->IsCrsrMovedUpdt() )
//STRIP001 /*?*/                GetLayout()->MakeTblCrsrs( *pTblCrsr );
//STRIP001 /*?*/            if( bHasFocus && !bBasicHideCrsr )
//STRIP001 /*?*/                pTblCrsr->Show();
//STRIP001 /*?*/
//STRIP001 /*?*/            // Cursor-Points auf die neuen Positionen setzen
//STRIP001 /*?*/            pTblCrsr->GetPtPos().X() = aCharRect.Left();
//STRIP001 /*?*/            pTblCrsr->GetPtPos().Y() = aCharRect.Top();
//STRIP001 /*?*/
//STRIP001 /*?*/            if( bSVCrsrVis )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                aCrsrHeight.X() = 0;
//STRIP001 /*?*/                aCrsrHeight.Y() = aCharRect.Height();
//STRIP001 /*?*/                pVisCrsr->Show();           // wieder anzeigen
//STRIP001 /*?*/            }
//STRIP001 /*?*/            eMvState = MV_NONE;     // Status fuers Crsr-Travelling - GetCrsrOfst
//STRIP001 /*?*/ #ifdef ACCESSIBLE_LAYOUT
//STRIP001 /*?*/            if( pTblFrm && Imp()->IsAccessible() )
//STRIP001 /*?*/                Imp()->InvalidateAccessibleCursorPosition( pTblFrm );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/            return;
//STRIP001 /*?*/        }
/*M*/   }
/*M*/
/*M*/   if( pTblCrsr )
/*M*/   {
/*M*/       // Cursor Ring loeschen
/*M*/       while( pCurCrsr->GetNext() != pCurCrsr )
/*M*/           delete pCurCrsr->GetNext();
/*M*/       pCurCrsr->DeleteMark();
/*M*/       *pCurCrsr->GetPoint() = *pTblCrsr->GetPoint();
/*M*/       pCurCrsr->GetPtPos() = pTblCrsr->GetPtPos();
/*M*/       delete pTblCrsr, pTblCrsr = 0;
/*M*/   }
/*M*/
/*M*/   pVisCrsr->Hide();       // sichtbaren Cursor immer verstecken
/*M*/
/*M*/   // sind wir vielleicht in einer geschuetzten/versteckten Section ?
/*M*/   {
/*M*/       BOOL bChgState = TRUE;
/*M*/       const SwSectionNode* pSectNd = pCurCrsr->GetNode()->FindSectionNode();
/*M*/       if( pSectNd && ( pSectNd->GetSection().IsHiddenFlag() ||
/*M*/           ( !IsReadOnlyAvailable() &&
/*M*/             pSectNd->GetSection().IsProtectFlag() &&
/*M*/            ( !pDoc->GetDocShell() ||
/*M*/              !pDoc->GetDocShell()->IsReadOnly() || bAllProtect )) ) )
/*M*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            if( !FindValidCntntNode( !HasDrawView() ||
//STRIP001 /*?*/                    0 == Imp()->GetDrawView()->GetMarkList().GetMarkCount()))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // alles ist geschuetzt / versteckt -> besonderer Mode
//STRIP001 /*?*/                if( bAllProtect && !IsReadOnlyAvailable() &&
//STRIP001 /*?*/                    pSectNd->GetSection().IsProtectFlag() )
//STRIP001 /*?*/                    bChgState = FALSE;
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    eMvState = MV_NONE;     // Status fuers Crsr-Travelling
//STRIP001 /*?*/                    bAllProtect = TRUE;
//STRIP001 /*?*/                    if( GetDoc()->GetDocShell() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        GetDoc()->GetDocShell()->SetReadOnlyUI( TRUE );
//STRIP001 /*?*/                        CallChgLnk();       // UI bescheid sagen!
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    return;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*M*/       }
/*M*/       if( bChgState )
/*M*/       {
/*M*/           BOOL bWasAllProtect = bAllProtect;
/*M*/           bAllProtect = FALSE;
/*M*/           if( bWasAllProtect && GetDoc()->GetDocShell() &&
/*M*/               GetDoc()->GetDocShell()->IsReadOnlyUI() )
/*M*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                GetDoc()->GetDocShell()->SetReadOnlyUI( FALSE );
//STRIP001 /*?*/                CallChgLnk();       // UI bescheid sagen!
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/
/*M*/   UpdateCrsrPos();
/*M*/
/*M*/
/*M*/     // #100722# The cursor must always point into content; there's some code
/*M*/     // that relies on this. (E.g. in SwEditShell::GetScriptType, which always
/*M*/     // loops _behind_ the last node in the selection, which always works if you
/*M*/     // are in content.) To achieve this, we'll force cursor(s) to point into
/*M*/     // content, if UpdateCrsrPos() hasn't already done so.
/*M*/     SwPaM* pCmp = pCurCrsr;
/*M*/     do
/*M*/     {
/*M*/         // start will move forwards, end will move backwards
/*M*/         bool bPointIsStart = ( pCmp->Start() == pCmp->GetPoint() );
/*M*/
/*M*/         // move point; forward if it's the start, backwards if it's the end
/*M*/         if( ! pCmp->GetPoint()->nNode.GetNode().IsCntntNode() )
/*M*/             pCmp->Move( bPointIsStart ? fnMoveForward : fnMoveBackward,
/*M*/                         fnGoCntnt );
/*M*/
/*M*/         // move mark (if exists); forward if it's the start, else backwards
/*M*/         if( pCmp->HasMark() )
/*M*/         {
/*M*/             if( ! pCmp->GetMark()->nNode.GetNode().IsCntntNode() )
/*M*/             {
/*M*/                 pCmp->Exchange();
/*M*/                 pCmp->Move( !bPointIsStart ? fnMoveForward : fnMoveBackward,
/*M*/                             fnGoCntnt );
/*M*/                 pCmp->Exchange();
/*M*/             }
/*M*/         }
/*M*/
/*M*/         // iterate to next PaM in ring
/*M*/         pCmp = static_cast<SwPaM*>( pCmp->GetNext() );
/*M*/     }
/*M*/     while( pCmp != pCurCrsr );
/*M*/
/*M*/
/*M*/   SwRect aOld( aCharRect );
/*M*/   FASTBOOL bFirst = TRUE;
/*M*/   SwCntntFrm *pFrm;
/*M*/   int nLoopCnt = 100;
/*M*/
/*M*/   do {
/*M*/       BOOL bAgainst;
/*M*/       do {
/*M*/           bAgainst = FALSE;
/*M*/           pFrm = pCurCrsr->GetCntntNode()->GetFrm(
/*M*/                       &pCurCrsr->GetPtPos(), pCurCrsr->GetPoint() );
/*M*/           // ist der Frm nicht mehr vorhanden, dann muss das gesamte Layout
/*M*/           // erzeugt werden, weil ja mal hier einer vorhanden war !!
/*M*/           if ( !pFrm )
/*M*/           {
/*M*/               do
/*M*/               {
/*M*/                   CalcLayout();
/*M*/                   pFrm = pCurCrsr->GetCntntNode()->GetFrm(
/*M*/                               &pCurCrsr->GetPtPos(), pCurCrsr->GetPoint() );
/*M*/               }  while( !pFrm );
/*M*/           }
/*M*/           else if ( Imp()->IsIdleAction() )
/*M*/               //Wir stellen sicher, dass anstaendig Formatiert wurde #42224#
/*?*/               {DBG_ASSERT(0, "STRIP"); }//STRIP001 pFrm->PrepareCrsr();
/*M*/
/*M*/           // im geschuetzten Fly? aber bei Rahmenselektion ignorieren
/*M*/           if( !IsReadOnlyAvailable() && pFrm->IsProtected() &&
/*M*/               ( !Imp()->GetDrawView() ||
/*M*/                 !Imp()->GetDrawView()->GetMarkList().GetMarkCount() ) &&
/*M*/               (!pDoc->GetDocShell() ||
/*M*/                !pDoc->GetDocShell()->IsReadOnly() || bAllProtect ) )
/*M*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                // dann suche eine gueltige Position
//STRIP001 /*?*/                BOOL bChgState = TRUE;
//STRIP001 /*?*/                if( !FindValidCntntNode(!HasDrawView() ||
//STRIP001 /*?*/                    0 == Imp()->GetDrawView()->GetMarkList().GetMarkCount()))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // alles ist geschuetzt / versteckt -> besonderer Mode
//STRIP001 /*?*/                    if( bAllProtect )
//STRIP001 /*?*/                        bChgState = FALSE;
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        eMvState = MV_NONE;     // Status fuers Crsr-Travelling
//STRIP001 /*?*/                        bAllProtect = TRUE;
//STRIP001 /*?*/                        if( GetDoc()->GetDocShell() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            GetDoc()->GetDocShell()->SetReadOnlyUI( TRUE );
//STRIP001 /*?*/                            CallChgLnk();       // UI bescheid sagen!
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        return;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if( bChgState )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    BOOL bWasAllProtect = bAllProtect;
//STRIP001 /*?*/                    bAllProtect = FALSE;
//STRIP001 /*?*/                    if( bWasAllProtect && GetDoc()->GetDocShell() &&
//STRIP001 /*?*/                        GetDoc()->GetDocShell()->IsReadOnlyUI() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        GetDoc()->GetDocShell()->SetReadOnlyUI( FALSE );
//STRIP001 /*?*/                        CallChgLnk();       // UI bescheid sagen!
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    bAllProtect = FALSE;
//STRIP001 /*?*/                    bAgainst = TRUE;        // nochmal den richigen Frm suchen
//STRIP001 /*?*/                }
/*M*/           }
/*M*/       } while( bAgainst );
/*M*/
/*M*/       if( !( eFlags & SwCrsrShell::NOCALRECT ))
/*M*/       {
/*M*/           SwCrsrMoveState aTmpState( eMvState );
/*M*/           aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
/*M*/             aTmpState.bRealHeight = TRUE;
/*M*/           aTmpState.bRealWidth = IsOverwriteCrsr();
/*N*/             aTmpState.nCursorBidiLevel = pCurCrsr->GetCrsrBidiLevel();
/*M*/           if( !pFrm->GetCharRect( aCharRect, *pCurCrsr->GetPoint(), &aTmpState ) )
/*M*/           {
/*N*/               Point& rPt = pCurCrsr->GetPtPos();
/*N*/               rPt = aCharRect.Center();
/*N*/               pFrm->GetCrsrOfst( pCurCrsr->GetPoint(), rPt, &aTmpState );
/*N*/ #ifndef VERTICAL_LAYOUT
/*N*/                 if ( !pFrm->GetCharRect(aCharRect, *pCurCrsr->GetPoint(), &aTmpState) )
/*N*/                   ASSERT( !this, "GetCharRect failed." );
/*N*/ #endif
/*M*/           }
/*M*/ //            ALIGNRECT( aCharRect );
/*M*/
/*M*/             if( !pCurCrsr->HasMark() )
/*M*/               aCrsrHeight = aTmpState.aRealHeight;
/*M*/           else
/*M*/           {
/*M*/               aCrsrHeight.X() = 0;
/*M*/                 aCrsrHeight.Y() = aTmpState.aRealHeight.Y() < 0 ?
/*M*/                                   -aCharRect.Width() : aCharRect.Height();
/*M*/           }
/*M*/       }
/*M*/       else
/*M*/       {
/*M*/           aCrsrHeight.X() = 0;
/*M*/           aCrsrHeight.Y() = aCharRect.Height();
/*M*/       }
/*M*/
/*M*/       if( !bFirst && aOld == aCharRect )
/*M*/           break;
/*M*/
/*M*/       // falls das Layout meint, nach dem 100 durchlauf ist man immer noch
/*M*/       // im Fluss, sollte man die akt. Pos. als gegeben hinnehmen!
/*M*/       // siehe Bug: 29658
/*M*/       if( !--nLoopCnt )
/*M*/       {
/*M*/           ASSERT( !this, "Endlosschleife? CharRect != OldCharRect ");
/*M*/           break;
/*M*/       }
/*M*/       aOld = aCharRect;
/*M*/       bFirst = FALSE;
/*M*/
/*M*/       // Cursor-Points auf die neuen Positionen setzen
/*M*/       pCurCrsr->GetPtPos().X() = aCharRect.Left();
/*M*/       pCurCrsr->GetPtPos().Y() = aCharRect.Top();
/*M*/
/*M*/       if( !(eFlags & SwCrsrShell::UPDOWN ))   // alte Pos. von Up/Down loeschen
/*M*/       {
/*M*/           pFrm->Calc();
/*M*/ #ifdef VERTICAL_LAYOUT
/*M*/             nUpDownX = pFrm->IsVertical() ?
/*M*/                        aCharRect.Top() - pFrm->Frm().Top() :
/*M*/                        aCharRect.Left() - pFrm->Frm().Left();
/*M*/ #else
/*M*/           nUpDownX = aCharRect.Left() - pFrm->Frm().Left();
/*M*/ #endif
/*M*/       }
/*M*/
/*M*/       // Curosr in den sichtbaren Bereich scrollen
/*M*/         if( bHasFocus && eFlags & SwCrsrShell::SCROLLWIN &&
/*M*/           (HasSelection() || eFlags & SwCrsrShell::READONLY ||
/*M*/              !IsCrsrReadonly() || GetViewOptions()->IsSelectionInReadonly()) )
/*M*/       {
/*M*/           //JP 30.04.99:  damit das EndAction, beim evtuellen Scrollen, den
/*M*/           //      SV-Crsr nicht wieder sichtbar macht, wird hier das Flag
/*M*/           //      gesichert und zurueckgesetzt.
/*M*/           BOOL bSav = bSVCrsrVis; bSVCrsrVis = FALSE;
/*M*/           MakeSelVisible();
/*M*/           bSVCrsrVis = bSav;
/*M*/       }
/*M*/
/*M*/   } while( eFlags & SwCrsrShell::SCROLLWIN );
/*M*/
/*M*/   if( !bIdleEnd && bHasFocus && !bBasicHideCrsr )
/*M*/       pCurCrsr->SwSelPaintRects::Show();
/*M*/
/*M*/   //Ggf. gescrollten Bereicht korrigieren (Alignment).
/*M*/   //Nur wenn gescrollt wurde, und wenn keine Selektion existiert.
/*M*/   if( pFrm && Imp()->IsScrolled() &&
/*M*/           pCurCrsr->GetNext() == pCurCrsr && !pCurCrsr->HasMark() )
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 Imp()->RefreshScrolledArea( aCharRect );
/*M*/
/*M*/
/*M*/   eMvState = MV_NONE;     // Status fuers Crsr-Travelling - GetCrsrOfst
/*M*/
/*M*/ #ifdef ACCESSIBLE_LAYOUT
//STRIP001 /*?*/    if( pFrm && Imp()->IsAccessible() )
//STRIP001 /*?*/        Imp()->InvalidateAccessibleCursorPosition( pFrm );
/*M*/ #endif
/*M*/
/*M*/ #ifndef REMOTE_APPSERVER
/*M*/
/*M*/     // switch from blinking cursor to read-only-text-selection cursor
/*M*/     long nBlinkTime = GetOut()->GetSettings().GetStyleSettings().
/*M*/                       GetCursorBlinkTime();
/*M*/
/*M*/     if ( (IsCrsrReadonly() && GetViewOptions()->IsSelectionInReadonly()) ==
/*M*/         ( nBlinkTime != STYLE_CURSOR_NOBLINKTIME ) )
/*M*/     {
/*M*/         // non blinking cursor in read only - text selection mode
/*M*/         AllSettings aSettings = GetOut()->GetSettings();
/*M*/         StyleSettings aStyleSettings = aSettings.GetStyleSettings();
/*M*/         long nNewBlinkTime = nBlinkTime == STYLE_CURSOR_NOBLINKTIME ?
/*M*/                              500 :
/*M*/                              STYLE_CURSOR_NOBLINKTIME;
/*M*/         aStyleSettings.SetCursorBlinkTime( nNewBlinkTime );
/*M*/         aSettings.SetStyleSettings( aStyleSettings );
/*M*/         GetOut()->SetSettings( aSettings );
/*M*/     }
/*M*/
/*M*/ #endif
/*M*/
/*M*/   if( bSVCrsrVis )
/*M*/       pVisCrsr->Show();           // wieder anzeigen
/*M*/ }



// erzeuge eine Kopie vom Cursor und speicher diese im Stack


//STRIP001 void SwCrsrShell::Push()
//STRIP001 {
//STRIP001  pCrsrStk = new SwShellCrsr( *this, *pCurCrsr->GetPoint(),
//STRIP001                                  pCurCrsr->GetPtPos(), pCrsrStk );
//STRIP001
//STRIP001  if( pCurCrsr->HasMark() )
//STRIP001  {
//STRIP001      pCrsrStk->SetMark();
//STRIP001      *pCrsrStk->GetMark() = *pCurCrsr->GetMark();
//STRIP001  }
//STRIP001 }

/*
 *  Loescht einen Cursor (gesteuert durch bOldCrsr)
 *      - vom Stack oder    ( bOldCrsr = TRUE )
 *      - den aktuellen und der auf dem Stack stehende wird zum aktuellen
 *
 *  Return:  es war auf dem Stack noch einer vorhanden
 */


//STRIP001 FASTBOOL SwCrsrShell::Pop( BOOL bOldCrsr )
//STRIP001 {
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001
//STRIP001  // noch weitere vorhanden ?
//STRIP001  if( 0 == pCrsrStk )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwShellCrsr *pTmp = 0, *pOldStk = pCrsrStk;
//STRIP001
//STRIP001  // der Nachfolger wird der Aktuelle
//STRIP001  if( pCrsrStk->GetNext() != pCrsrStk )
//STRIP001      pTmp = (SwShellCrsr*)*((SwCursor*)pCrsrStk->GetNext());
//STRIP001
//STRIP001  if( bOldCrsr )              // loesche vom Stack
//STRIP001      delete pCrsrStk;        //
//STRIP001
//STRIP001  pCrsrStk = pTmp;            // neu zuweisen
//STRIP001
//STRIP001  if( !bOldCrsr )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSaveState( *pCurCrsr );
//STRIP001
//STRIP001      // wurde die sichtbare SSelection nicht veraendert
//STRIP001      if( pOldStk->GetPtPos() == pCurCrsr->GetPtPos() ||
//STRIP001          pOldStk->GetPtPos() == pCurCrsr->GetMkPos() )
//STRIP001      {
//STRIP001          // "Selektions-Rechtecke" verschieben
//STRIP001          pCurCrsr->Insert( pOldStk, 0 );
//STRIP001          pOldStk->Remove( 0, pOldStk->Count() );
//STRIP001      }
//STRIP001
//STRIP001      if( pOldStk->HasMark() )
//STRIP001      {
//STRIP001          pCurCrsr->SetMark();
//STRIP001          *pCurCrsr->GetMark() = *pOldStk->GetMark();
//STRIP001          pCurCrsr->GetMkPos() = pOldStk->GetMkPos();
//STRIP001      }
//STRIP001      else
//STRIP001          // keine Selection also alte aufheben und auf die alte Pos setzen
//STRIP001          pCurCrsr->DeleteMark();
//STRIP001      *pCurCrsr->GetPoint() = *pOldStk->GetPoint();
//STRIP001      pCurCrsr->GetPtPos() = pOldStk->GetPtPos();
//STRIP001      delete pOldStk;
//STRIP001
//STRIP001      if( !pCurCrsr->IsInProtectTable( TRUE ) &&
//STRIP001          !pCurCrsr->IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS ) )
//STRIP001          UpdateCrsr();             // akt. Cursor Updaten
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*
 * Verbinde zwei Cursor miteinander.
 * Loesche vom Stack den obersten und setzen dessen GetMark im Aktuellen.
 */


//STRIP001 void SwCrsrShell::Combine()
//STRIP001 {
//STRIP001  // noch weitere vorhanden ?
//STRIP001  if( 0 == pCrsrStk )
//STRIP001      return;
//STRIP001
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  SwCrsrSaveState aSaveState( *pCurCrsr );
//STRIP001  if( pCrsrStk->HasMark() )           // nur wenn GetMark gesetzt wurde
//STRIP001  {
//STRIP001      if( !CheckNodesRange( pCrsrStk->GetMark()->nNode, pCurCrsr->GetPoint()->nNode, TRUE ))
//STRIP001          ASSERT( !this, "StackCrsr & akt. Crsr nicht in gleicher Section." );
//STRIP001
//STRIP001      // kopiere das GetMark
//STRIP001      if( !pCurCrsr->HasMark() )
//STRIP001          pCurCrsr->SetMark();
//STRIP001      *pCurCrsr->GetMark() = *pCrsrStk->GetMark();
//STRIP001      pCurCrsr->GetMkPos() = pCrsrStk->GetMkPos();
//STRIP001  }
//STRIP001
//STRIP001  SwShellCrsr * pTmp = 0;
//STRIP001  if( pCrsrStk->GetNext() != pCrsrStk )
//STRIP001      pTmp = (SwShellCrsr*)*((SwCursor*)pCrsrStk->GetNext());
//STRIP001  delete pCrsrStk;
//STRIP001  pCrsrStk = pTmp;
//STRIP001  if( !pCurCrsr->IsInProtectTable( TRUE ) &&
//STRIP001      !pCurCrsr->IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS ) )
//STRIP001      UpdateCrsr();             // akt. Cursor Updaten
//STRIP001 }


//STRIP001 void SwCrsrShell::HideCrsrs()
//STRIP001 {
//STRIP001  if( !bHasFocus || bBasicHideCrsr )
//STRIP001      return;
//STRIP001
//STRIP001  // ist Cursor sichtbar, dann verstecke den SV-Cursor
//STRIP001  if( pVisCrsr->IsVisible() )
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      pVisCrsr->Hide();
//STRIP001  }
//STRIP001  // hebe die Invertierung der SSelection auf
//STRIP001  SwShellCrsr* pAktCrsr = pTblCrsr ? pTblCrsr : pCurCrsr;
//STRIP001  pAktCrsr->Hide();
//STRIP001 }



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

// Methoden zum Anzeigen bzw. Verstecken des sichtbaren Text-Cursors


/*N*/ void SwCrsrShell::ShowCrsr()
/*N*/ {
/*N*/   if( !bBasicHideCrsr )
/*N*/   {
/*N*/       bSVCrsrVis = TRUE;
/*N*/       UpdateCrsr();
/*N*/   }
/*N*/ }


/*N*/ void SwCrsrShell::HideCrsr()
/*N*/ {
/*N*/   if( !bBasicHideCrsr )
/*N*/   {
/*N*/       bSVCrsrVis = FALSE;
/*N*/       // evt. die sel. Bereiche aufheben !!
/*N*/       SET_CURR_SHELL( this );
/*N*/       pVisCrsr->Hide();
/*N*/   }
/*N*/ }


//STRIP001 void SwCrsrShell::ShLooseFcs()
//STRIP001 {
//STRIP001  if( !bBasicHideCrsr )
//STRIP001      HideCrsrs();
//STRIP001  bHasFocus = FALSE;
//STRIP001 }


/*N*/ void SwCrsrShell::ShGetFcs( BOOL bUpdate )
/*N*/ {
/*N*/   bHasFocus = TRUE;
/*N*/   if( !bBasicHideCrsr && VisArea().Width() )
/*N*/   {
/*?*/       UpdateCrsr( bUpdate ? SwCrsrShell::CHKRANGE|SwCrsrShell::SCROLLWIN
/*?*/                           : SwCrsrShell::CHKRANGE );
/*?*/       ShowCrsrs( bSVCrsrVis ? TRUE : FALSE );
/*N*/   }
/*N*/ }

// gebe den aktuellen Frame, in dem der Cursor steht, zurueck

#if 0

//MA 03. Nov. 95: Die letzten Anwender habe ich gerade aus wrtsh1.cxx entfernt.
//                Weil's so kunstvoll aussieht lass ich die Funktion vorlauefig
//                hier.


//STRIP001 Rectangle SwCrsrShell::GetCurrFrmArea() const
//STRIP001 {
//STRIP001  //Sitzt der Crsr ueberhaupt auf einem CntntNode?
//STRIP001  SET_CURR_SHELL( (ViewShell*)this );
//STRIP001  Rectangle aRet;
//STRIP001  SwCntntNode *pNd = GetNode().GetCntntNode();
//STRIP001  if ( pNd )
//STRIP001  {
//STRIP001      const USHORT* pST = &nStartAction;
//STRIP001      ++(*((USHORT*)pST));
//STRIP001      const Size aOldSz( GetLayout()->Frm().SSize() );
//STRIP001      SwCntntFrm *pFrm = pNd->GetFrm(
//STRIP001                          &pCurCrsr->GetPtPos(), pCurCrsr->GetPoint() );
//STRIP001      aRet = pFrm->Frm().SVRect();
//STRIP001      --(*((USHORT*)pST));
//STRIP001      if( aOldSz != GetLayout()->Frm().SSize() )
//STRIP001          ((SwCrsrShell*)this)->SizeChgNotify( GetLayout()->Frm().SSize() );
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }
#endif


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
/*N*/                               : RES_MSG_BEGIN;
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


/*N*/ FASTBOOL SwCrsrShell::HasSelection() const
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

// returne den am akt.Cursor selektierten Text eines Nodes.


//STRIP001 String SwCrsrShell::GetSelTxt() const
//STRIP001 {
//STRIP001  String aTxt;
//STRIP001  if( pCurCrsr->GetPoint()->nNode.GetIndex() ==
//STRIP001      pCurCrsr->GetMark()->nNode.GetIndex() )
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd = pCurCrsr->GetNode()->GetTxtNode();
//STRIP001      if( pTxtNd )
//STRIP001      {
//STRIP001          xub_StrLen nStt = pCurCrsr->Start()->nContent.GetIndex();
//STRIP001          aTxt = pTxtNd->GetExpandTxt( nStt,
//STRIP001                  pCurCrsr->End()->nContent.GetIndex() - nStt );
//STRIP001      }
//STRIP001  }
//STRIP001  return aTxt;
//STRIP001 }

// gebe nur den Text ab der akt. Cursor Position zurueck (bis zum NodeEnde)


//STRIP001 String SwCrsrShell::GetText() const
//STRIP001 {
//STRIP001  String aTxt;
//STRIP001  if( pCurCrsr->GetPoint()->nNode.GetIndex() ==
//STRIP001      pCurCrsr->GetMark()->nNode.GetIndex() )
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd = pCurCrsr->GetNode()->GetTxtNode();
//STRIP001      if( pTxtNd )
//STRIP001          aTxt = pTxtNd->GetTxt().Copy(
//STRIP001                  pCurCrsr->GetPoint()->nContent.GetIndex() );
//STRIP001  }
//STRIP001  return aTxt;
//STRIP001 }

// retrurne die Anzahl der selektierten Zeichen.
// Falls keine Selektion vorliegt entscheided nType was selektiert wird
// bIntrnlChar besagt ob interne Zeichen erhalten bleiben (TRUE) oder
// ob sie expandiert werden (z.B Felder/...)
//STRIP001 ULONG SwCrsrShell::GetCharCount( USHORT nType, BOOL bIntrnlChrs ) const
//STRIP001 {
//STRIP001  if( IsTableMode() )
//STRIP001      GetCrsr();
//STRIP001
//STRIP001  BOOL bPop = FALSE;
//STRIP001  if( !pCurCrsr->HasMark() && pCurCrsr->GetNext() == pCurCrsr )
//STRIP001  {
//STRIP001      // dann den Type auswerten, ansonsten ist ein Bereich vorhanden
//STRIP001      bPop = TRUE;
//STRIP001      SwCrsrShell* pThis = (SwCrsrShell*)this;
//STRIP001      pThis->Push();
//STRIP001      switch( nType )
//STRIP001      {
//STRIP001      case GETCHARCOUNT_PARA:     // Absatz selektieren
//STRIP001          {
//STRIP001              SwCntntNode* pCNd = pCurCrsr->GetCntntNode();
//STRIP001              if( pCNd )
//STRIP001              {
//STRIP001                  pCurCrsr->SetMark();
//STRIP001                  pCurCrsr->GetMark()->nContent.Assign( pCNd, 0 );
//STRIP001                  pCurCrsr->GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case GETCHARCOUNT_SECTION:      // "Section" selektieren
//STRIP001          {
//STRIP001              pCurCrsr->SetMark();
//STRIP001              GoStartSection( pCurCrsr->GetMark() );
//STRIP001              GoEndSection( pCurCrsr->GetPoint() );
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  USHORT nCrsrCnt = 0;
//STRIP001  ULONG nCount = 0;
//STRIP001  USHORT nLineOffset = /* Basic zaehlt CRLF als ein Zeichen
//STRIP001                      LINEEND_CRLF == GetSystemLineEnd() ? 2 : 1*/ 1;
//STRIP001
//STRIP001  const SwPaM* pTmp = pCurCrsr;
//STRIP001  do {
//STRIP001      ++nCrsrCnt;
//STRIP001      const SwPosition *pStt = pTmp->Start(), *pEnd = pTmp->End();
//STRIP001      if( *pStt < *pEnd )
//STRIP001      {
//STRIP001          ULONG nSttNd = pStt->nNode.GetIndex(),
//STRIP001                nEndNd = pEnd->nNode.GetIndex();
//STRIP001          xub_StrLen nSttCnt = pStt->nContent.GetIndex(),
//STRIP001                     nEndCnt = pEnd->nContent.GetIndex();
//STRIP001
//STRIP001          if( nSttNd != nEndNd )
//STRIP001          {
//STRIP001              for( ; nSttNd < nEndNd; ++nSttNd, nSttCnt = 0 )
//STRIP001              {
//STRIP001                  const SwCntntNode* pCNd = pDoc->GetNodes()[
//STRIP001                                          nSttNd ]->GetCntntNode();
//STRIP001                  if( pCNd )
//STRIP001                  {
//STRIP001                      if( pCNd->IsTxtNode() && !bIntrnlChrs )
//STRIP001                          nCount += ((SwTxtNode*)pCNd)->GetExpandTxt(
//STRIP001                                                          nSttCnt ).Len();
//STRIP001                      else
//STRIP001                          nCount += pCNd->Len();
//STRIP001
//STRIP001                      nCount += nLineOffset;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( bIntrnlChrs )
//STRIP001              nCount += nEndCnt - nSttCnt;
//STRIP001          else
//STRIP001          {
//STRIP001              const SwTxtNode* pNd = pDoc->GetNodes()[ nEndNd ]->GetTxtNode();
//STRIP001              if( pNd )
//STRIP001                  nCount += pNd->GetExpandTxt( nSttCnt,
//STRIP001                              nEndCnt - nSttCnt ).Len();
//STRIP001          }
//STRIP001      }
//STRIP001  } while( pCurCrsr != ( pTmp = (SwPaM*)pTmp->GetNext() ) );
//STRIP001
//STRIP001  // bei TabellenSelektion werden alle Boxen mit CR/LF abgeschlossen
//STRIP001  if( IsTableMode() && 1 < nCrsrCnt )
//STRIP001      nCount += nCrsrCnt * nLineOffset;
//STRIP001
//STRIP001  if( bPop )
//STRIP001  {
//STRIP001      SwCrsrShell* pThis = (SwCrsrShell*)this;
//STRIP001      pThis->Pop( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  return nCount;
//STRIP001 }


// hole vom Start/Ende der akt. SSelection das nte Zeichen
//STRIP001 sal_Unicode SwCrsrShell::GetChar( BOOL bEnd, long nOffset )
//STRIP001 {
//STRIP001  if( IsTableMode() )         // im TabelleMode nicht moeglich
//STRIP001      return 0;
//STRIP001
//STRIP001  const SwPosition* pPos = !pCurCrsr->HasMark() ? pCurCrsr->GetPoint()
//STRIP001                              : bEnd ? pCurCrsr->End() : pCurCrsr->Start();
//STRIP001  SwTxtNode* pTxtNd = pPos->nNode.GetNode().GetTxtNode();
//STRIP001  ASSERT( pTxtNd, "kein TextNode, wie soll ein char returnt werden?" );
//STRIP001
//STRIP001  xub_StrLen nPos = pPos->nContent.GetIndex();
//STRIP001  const String& rStr = pTxtNd->GetTxt();
//STRIP001  sal_Unicode cCh = 0;
//STRIP001
//STRIP001  if( ((nPos+nOffset) >= 0 ) && (nPos+nOffset) < rStr.Len() )
//STRIP001      cCh = rStr.GetChar( nPos+nOffset );
//STRIP001
//STRIP001  return cCh;
//STRIP001 }

// erweiter die akt. SSelection am Anfang/Ende um n Zeichen


//STRIP001 FASTBOOL SwCrsrShell::ExtendSelection( BOOL bEnd, xub_StrLen nCount )
//STRIP001 {
//STRIP001  if( !pCurCrsr->HasMark() || IsTableMode() )
//STRIP001      return FALSE;           // keine Selektion
//STRIP001
//STRIP001  SwPosition* pPos = bEnd ? pCurCrsr->End() : pCurCrsr->Start();
//STRIP001  SwTxtNode* pTxtNd = pPos->nNode.GetNode().GetTxtNode();
//STRIP001  ASSERT( pTxtNd, "kein TextNode, wie soll erweitert werden?" );
//STRIP001
//STRIP001  xub_StrLen nPos = pPos->nContent.GetIndex();
//STRIP001  if( bEnd )
//STRIP001  {
//STRIP001      if( ( nPos + nCount ) <= pTxtNd->GetTxt().Len() )
//STRIP001          nPos += nCount;
//STRIP001      else
//STRIP001          return FALSE;       // nicht mehr moeglich
//STRIP001  }
//STRIP001  else if( nPos >= nCount )
//STRIP001      nPos -= nCount;
//STRIP001  else
//STRIP001      return FALSE;           // nicht mehr moeglich
//STRIP001
//STRIP001  SwCallLink aLk( *this );    // Crsr-Moves ueberwachen,
//STRIP001
//STRIP001  pPos->nContent = nPos;
//STRIP001  UpdateCrsr();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

// setze nur den sichtbaren Cursor an die angegebene Dokument-Pos.
// returnt FALSE: wenn der SPoint vom Layout korrigiert wurde.

//STRIP001 FASTBOOL SwCrsrShell::SetVisCrsr( const Point &rPt )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  Point aPt( rPt );
//STRIP001  SwPosition aPos( *pCurCrsr->GetPoint() );
//STRIP001  SwCrsrMoveState aTmpState( MV_SETONLYTEXT );
//STRIP001  aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
//STRIP001  aTmpState.bRealHeight = TRUE;
//STRIP001
//STRIP001  FASTBOOL bRet = GetLayout()->GetCrsrOfst( &aPos, aPt /*, &aTmpState*/ );
//STRIP001  // nur in TextNodes anzeigen !!
//STRIP001  SwTxtNode* pTxtNd = aPos.nNode.GetNode().GetTxtNode();
//STRIP001  if( !pTxtNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwSectionNode* pSectNd = pTxtNd->FindSectionNode();
//STRIP001  if( pSectNd && (pSectNd->GetSection().IsHiddenFlag() ||
//STRIP001                  ( !IsReadOnlyAvailable() &&
//STRIP001                    pSectNd->GetSection().IsProtectFlag())) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwCntntFrm *pFrm = pTxtNd->GetFrm( &aPt, &aPos );
//STRIP001  if ( Imp()->IsIdleAction() )
//STRIP001      pFrm->PrepareCrsr();
//STRIP001  SwRect aTmp( aCharRect );
//STRIP001
//STRIP001
//STRIP001  pFrm->GetCharRect( aCharRect, aPos, &aTmpState );
//STRIP001 //   ALIGNRECT( aCharRect );
//STRIP001
//STRIP001  if( aTmp == aCharRect &&        // BUG 10137: bleibt der Cursor auf der
//STRIP001      pVisCrsr->IsVisible() )     // Position nicht hidden & showen
//STRIP001      return TRUE;
//STRIP001
//STRIP001  pVisCrsr->Hide();       // sichtbaren Cursor immer verstecken
//STRIP001  if( IsScrollMDI( this, aCharRect ))
//STRIP001  {
//STRIP001      MakeVisible( aCharRect );
//STRIP001      pCurCrsr->Show();
//STRIP001  }
//STRIP001
//STRIP001  // Bug 29584: bei Rahmenselektion ist der Cursor versteckt, aber den
//STRIP001  //          D&D-Cursor will man trotzdem haben
//STRIP001 //   if( bSVCrsrVis )
//STRIP001  {
//STRIP001      if( aTmpState.bRealHeight )
//STRIP001          aCrsrHeight = aTmpState.aRealHeight;
//STRIP001      else
//STRIP001      {
//STRIP001          aCrsrHeight.X() = 0;
//STRIP001          aCrsrHeight.Y() = aCharRect.Height();
//STRIP001      }
//STRIP001
//STRIP001      pVisCrsr->SetDragCrsr( TRUE );
//STRIP001      pVisCrsr->Show();           // wieder anzeigen
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SwCrsrShell::IsOverReadOnlyPos( const Point& rPt ) const
//STRIP001 {
//STRIP001 //   SET_CURR_SHELL( this );
//STRIP001  Point aPt( rPt );
//STRIP001  SwPaM aPam( *pCurCrsr->GetPoint() );
//STRIP001  FASTBOOL bRet = GetLayout()->GetCrsrOfst( aPam.GetPoint(), aPt );
//STRIP001  return aPam.HasReadonlySel();
//STRIP001 }


    // returne die Anzahl der Cursor im Ring (Flag besagt ob man nur
    // aufgepspannte haben will - sprich etwas selektiert ist (Basic))
/*N*/ USHORT SwCrsrShell::GetCrsrCnt( BOOL bAll ) const
/*N*/ {
/*N*/   Ring* pTmp = GetCrsr()->GetNext();
/*N*/   USHORT n = (bAll || ( pCurCrsr->HasMark() &&
/*N*/                   *pCurCrsr->GetPoint() != *pCurCrsr->GetMark())) ? 1 : 0;
/*N*/   while( pTmp != pCurCrsr )
/*N*/   {
/*?*/       if( bAll || ( ((SwPaM*)pTmp)->HasMark() &&
/*?*/               *((SwPaM*)pTmp)->GetPoint() != *((SwPaM*)pTmp)->GetMark()))
/*?*/           ++n;
/*?*/       pTmp = pTmp->GetNext();
/*N*/   }
/*N*/   return n;
/*N*/ }


//STRIP001 FASTBOOL SwCrsrShell::IsStartOfDoc() const
//STRIP001 {
//STRIP001  if( pCurCrsr->GetPoint()->nContent.GetIndex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // Hinter EndOfIcons kommt die Content-Section (EndNd+StNd+CntntNd)
//STRIP001  SwNodeIndex aIdx( GetDoc()->GetNodes().GetEndOfExtras(), 2 );
//STRIP001  if( !aIdx.GetNode().IsCntntNode() )
//STRIP001      GetDoc()->GetNodes().GoNext( &aIdx );
//STRIP001  return aIdx == pCurCrsr->GetPoint()->nNode;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::IsEndOfDoc() const
//STRIP001 {
//STRIP001  SwNodeIndex aIdx( GetDoc()->GetNodes().GetEndOfContent(), -1 );
//STRIP001  SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
//STRIP001  if( !pCNd )
//STRIP001      pCNd = GetDoc()->GetNodes().GoPrevious( &aIdx );
//STRIP001
//STRIP001  return aIdx == pCurCrsr->GetPoint()->nNode &&
//STRIP001          pCNd->Len() == pCurCrsr->GetPoint()->nContent.GetIndex();
//STRIP001 }


// loesche alle erzeugten Crsr, setze den Tabellen-Crsr und den letzten
// Cursor auf seinen TextNode (oder StartNode?).
// Beim naechsten ::GetCrsr werden sie wieder alle erzeugt
// Wird fuers Drag&Drop / ClipBorad-Paste in Tabellen benoetigt.
//STRIP001 FASTBOOL SwCrsrShell::ParkTblCrsr()
//STRIP001 {
//STRIP001  if( !pTblCrsr )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pTblCrsr->ParkCrsr();
//STRIP001
//STRIP001  while( pCurCrsr->GetNext() != pCurCrsr )
//STRIP001      delete pCurCrsr->GetNext();
//STRIP001
//STRIP001  // vom Cursor !immer! SPoint und Mark umsetzen
//STRIP001  pCurCrsr->SetMark();
//STRIP001  *pCurCrsr->GetMark() = *pCurCrsr->GetPoint() = *pTblCrsr->GetPoint();
//STRIP001  pCurCrsr->DeleteMark();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/***********************************************************************
#*  Class       :  SwCrsrShell
#*  Methode     :  ParkCrsr
#*  Beschreibung:  Vernichtet Selektionen und zus. Crsr aller Shell der
#*                 verbleibende Crsr der Shell wird geparkt.
#*  Datum       :  MA 05. Nov. 92
#*  Update      :  JP 19.09.97
#***********************************************************************/

//STRIP001 void SwCrsrShell::_ParkPams( SwPaM* pDelRg, SwShellCrsr** ppDelRing )
//STRIP001 {
//STRIP001  const SwPosition *pStt = pDelRg->Start(),
//STRIP001      *pEnd = pDelRg->GetPoint() == pStt ? pDelRg->GetMark() : pDelRg->GetPoint();
//STRIP001
//STRIP001  SwPaM *pTmpDel = 0, *pTmp = *ppDelRing;
//STRIP001
//STRIP001  // durchsuche den gesamten Ring
//STRIP001  BOOL bGoNext;
//STRIP001  do {
//STRIP001      const SwPosition *pTmpStt = pTmp->Start(),
//STRIP001                      *pTmpEnd = pTmp->GetPoint() == pTmpStt ?
//STRIP001                                      pTmp->GetMark() : pTmp->GetPoint();
//STRIP001      /*
//STRIP001       * liegt ein SPoint oder GetMark innerhalb vom Crsr-Bereich
//STRIP001       * muss der alte Bereich aufgehoben werden.
//STRIP001       * Beim Vergleich ist darauf zu achten, das End() nicht mehr zum
//STRIP001       * Bereich gehoert !
//STRIP001       */
//STRIP001      if( *pStt <= *pTmpStt )
//STRIP001      {
//STRIP001          if( *pEnd > *pTmpStt ||
//STRIP001              ( *pEnd == *pTmpStt && *pEnd == *pTmpEnd ))
//STRIP001              pTmpDel = pTmp;
//STRIP001      }
//STRIP001      else
//STRIP001          if( *pStt < *pTmpEnd )
//STRIP001              pTmpDel = pTmp;
//STRIP001
//STRIP001      bGoNext = TRUE;
//STRIP001      if( pTmpDel )           // ist der Pam im Bereich ?? loesche ihn
//STRIP001      {
//STRIP001          BOOL bDelete = TRUE;
//STRIP001          if( *ppDelRing == pTmpDel )
//STRIP001          {
//STRIP001              if( *ppDelRing == pCurCrsr )
//STRIP001              {
//STRIP001                  if( TRUE == ( bDelete = GoNextCrsr() ))
//STRIP001                  {
//STRIP001                      bGoNext = FALSE;
//STRIP001                      pTmp = (SwPaM*)pTmp->GetNext();
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  bDelete = FALSE;        // StackCrsr nie loeschen !!
//STRIP001          }
//STRIP001
//STRIP001          if( bDelete )
//STRIP001              delete pTmpDel;         // hebe alten Bereich auf
//STRIP001          else
//STRIP001          {
//STRIP001              pTmpDel->GetPoint()->nContent.Assign( 0, 0 );
//STRIP001              pTmpDel->GetPoint()->nNode = 0;
//STRIP001              pTmpDel->SetMark();
//STRIP001              pTmpDel->DeleteMark();
//STRIP001          }
//STRIP001          pTmpDel = 0;
//STRIP001      }
//STRIP001      else if( !pTmp->HasMark() )     // sorge auf jedenfall dafuer, das
//STRIP001      {                       // nicht benutzte Indizies beachtet werden!
//STRIP001          pTmp->SetMark();            // SPoint liegt nicht im Bereich,
//STRIP001          pTmp->DeleteMark();         // aber vielleicht GetMark, also setzen
//STRIP001      }
//STRIP001      if( bGoNext )
//STRIP001          pTmp = (SwPaM*)pTmp->GetNext();
//STRIP001  } while( !bGoNext || *ppDelRing != pTmp );
//STRIP001 }

//STRIP001 void SwCrsrShell::ParkCrsr( const SwNodeIndex &rIdx )
//STRIP001 {
//STRIP001  SwNode *pNode = &rIdx.GetNode();
//STRIP001
//STRIP001  // erzeuge einen neuen Pam
//STRIP001  SwPaM * pNew = new SwPaM( *GetCrsr()->GetPoint() );
//STRIP001  if( pNode->GetStartNode() )
//STRIP001  {
//STRIP001      if( ( pNode = pNode->StartOfSectionNode())->IsTableNode() )
//STRIP001      {
//STRIP001          // der angegebene Node steht in einer Tabelle, also Parke
//STRIP001          // den Crsr auf dem Tabellen-Node (ausserhalb der Tabelle)
//STRIP001          pNew->GetPoint()->nNode = *pNode->StartOfSectionNode();
//STRIP001      }
//STRIP001      else    // also auf dem StartNode selbst.
//STRIP001              // Dann immer ueber seinen EndNode den StartNode erfragen !!!
//STRIP001              // (StartOfSection vom StartNode ist der Parent !)
//STRIP001          pNew->GetPoint()->nNode = *pNode->EndOfSectionNode()->StartOfSectionNode();
//STRIP001  }
//STRIP001  else
//STRIP001      pNew->GetPoint()->nNode = *pNode->StartOfSectionNode();
//STRIP001  pNew->SetMark();
//STRIP001  pNew->GetPoint()->nNode = *pNode->EndOfSectionNode();
//STRIP001
//STRIP001  //Alle Shells wollen etwas davon haben.
//STRIP001  ViewShell *pTmp = this;
//STRIP001  do {
//STRIP001      if( pTmp->IsA( TYPE( SwCrsrShell )))
//STRIP001      {
//STRIP001          SwCrsrShell* pSh = (SwCrsrShell*)pTmp;
//STRIP001          if( pSh->pCrsrStk )
//STRIP001              pSh->_ParkPams( pNew, &pSh->pCrsrStk );
//STRIP001
//STRIP001          pSh->_ParkPams( pNew, &pSh->pCurCrsr );
//STRIP001          if( pSh->pTblCrsr )
//STRIP001          {
//STRIP001              // setze den Tabellen Cursor immer auf 0, den aktuellen
//STRIP001              // immer auf den Anfang der Tabelle
//STRIP001              SwPaM* pTCrsr = pSh->GetTblCrs();
//STRIP001              SwNode* pTblNd = pTCrsr->GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001              if ( pTblNd )
//STRIP001              {
//STRIP001                  pTCrsr->GetPoint()->nContent.Assign( 0, 0 );
//STRIP001                  pTCrsr->GetPoint()->nNode = 0;
//STRIP001                  pTCrsr->SetMark();
//STRIP001                  pTCrsr->DeleteMark();
//STRIP001                  pSh->pCurCrsr->GetPoint()->nNode = *pTblNd;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  } while ( this != (pTmp = (ViewShell*)pTmp->GetNext() ));
//STRIP001  delete pNew;
//STRIP001 }

//=========================================================================

/*
 * der Copy-Constructor
 * Cursor-Position kopieren, in den Ring eingetragen.
 * Alle Ansichten eines Dokumentes stehen im Ring der Shells.
 */

/*N*/ SwCrsrShell::SwCrsrShell( SwCrsrShell& rShell, Window *pWin )
/*N*/   : ViewShell( rShell, pWin ),
/*N*/   SwModify( 0 )
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   // Nur die Position vom aktuellen Cursor aus der Copy-Shell uebernehmen
/*N*/   pCurCrsr = new SwShellCrsr( *this, *(rShell.pCurCrsr->GetPoint()) );
/*N*/   pCurCrsr->GetCntntNode()->Add( this );
/*N*/   pCrsrStk = 0;
/*N*/   pTblCrsr = 0;
/*N*/
/*N*/   nBasicActionCnt = 0;
/*N*/
/*N*/   pBoxIdx = 0;
/*N*/   pBoxPtr = 0;
/*N*/
    /*
     * setze die initiale Spalten-Position fuer Up / Down
     */
/*N*/   nCrsrMove = 0;
/*N*/   bAllProtect = bVisPortChgd = bChgCallFlag = bInCMvVisportChgd =
/*N*/   bGCAttr = bIgnoreReadonly = bSelTblCells = bBasicHideCrsr =
/*N*/   bOverwriteCrsr = FALSE;
/*N*/   bCallChgLnk = bHasFocus = bSVCrsrVis = bAutoUpdateCells = TRUE;
/*N*/   bSetCrsrInReadOnly = TRUE;
/*N*/   eMvState = MV_NONE;     // Status fuers Crsr-Travelling - GetCrsrOfst
/*N*/   pVisCrsr = new SwVisCrsr( this );
/*N*/ //    UpdateCrsr( 0 );
/*N*/     // OD 11.02.2003 #100556#
/*N*/     mbMacroExecAllowed = rShell.IsMacroExecAllowed();
/*N*/ }


/*
 * der normale Constructor
 */

/*N*/ SwCrsrShell::SwCrsrShell( SwDoc& rDoc, Window *pWin, SwRootFrm *pRoot,
/*N*/                           const SwViewOption *pOpt )
/*N*/   : ViewShell( rDoc, pWin, pOpt ),
/*N*/   SwModify( 0 )
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
    /*
      * Erzeugen des initialen Cursors, wird auf die erste
     * Inhaltsposition gesetzt
     */
/*N*/   SwNodes& rNds = rDoc.GetNodes();
/*N*/
/*N*/   SwNodeIndex aNodeIdx( *rNds.GetEndOfContent().StartOfSectionNode() );
/*N*/   SwCntntNode* pCNd = rNds.GoNext( &aNodeIdx ); // gehe zum 1. ContentNode
/*N*/
/*N*/   pCurCrsr = new SwShellCrsr( *this, SwPosition( aNodeIdx, SwIndex( pCNd, 0 )));
/*N*/   pCrsrStk = 0;
/*N*/   pTblCrsr = 0;
/*N*/
/*N*/   nBasicActionCnt = 0;
/*N*/
/*N*/   pBoxIdx = 0;
/*N*/   pBoxPtr = 0;
/*N*/
/*N*/   // melde die Shell beim akt. Node als abhaengig an, dadurch koennen alle
/*N*/   // Attribut-Aenderungen ueber den Link weiter gemeldet werden.
/*N*/   pCNd->Add( this );
/*N*/
     /*
      * setze die initiale Spalten-Position fuer Up / Down
     */
/*N*/   nCrsrMove = 0;
/*N*/   bAllProtect = bVisPortChgd = bChgCallFlag = bInCMvVisportChgd =
/*N*/   bGCAttr = bIgnoreReadonly = bSelTblCells = bBasicHideCrsr =
/*N*/   bOverwriteCrsr = FALSE;
/*N*/   bCallChgLnk = bHasFocus = bSVCrsrVis = bAutoUpdateCells = TRUE;
/*N*/   bSetCrsrInReadOnly = TRUE;
/*N*/   eMvState = MV_NONE;     // Status fuers Crsr-Travelling - GetCrsrOfst
/*N*/
/*N*/   pVisCrsr = new SwVisCrsr( this );
/*N*/ //    UpdateCrsr( 0 );
/*N*/     // OD 11.02.2003 #100556#
/*N*/     mbMacroExecAllowed = true;
/*N*/ }



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

//STRIP001 FASTBOOL SwCrsrShell::ShouldWait() const
//STRIP001 {
//STRIP001  if ( IsTableMode() || GetCrsrCnt() > 1 )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  if( HasDrawView() && GetDrawView()->GetMarkList().GetMarkCount() )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  SwPaM* pPam = GetCrsr();
//STRIP001  return pPam->Start()->nNode.GetIndex() + 10 <
//STRIP001          pPam->End()->nNode.GetIndex();
//STRIP001 }


//STRIP001 USHORT SwCrsrShell::UpdateTblSelBoxes()
//STRIP001 {
//STRIP001  if( pTblCrsr && ( pTblCrsr->IsChgd() || !pTblCrsr->GetBoxesCount() ))
//STRIP001       GetLayout()->MakeTblCrsrs( *pTblCrsr );
//STRIP001  return pTblCrsr ? pTblCrsr->GetBoxesCount() : 0;
//STRIP001 }


// steht der Curor auf einem "Symbol"-Zeichen
//STRIP001 FASTBOOL SwCrsrShell::IsInSymbolFont() const
//STRIP001 {
//STRIP001  if( IsTableMode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwPosition* pPos = GetCrsr()->GetPoint();
//STRIP001  SwTxtNode* pTNd = pPos->nNode.GetNode().GetTxtNode();
//STRIP001  if( pTNd )
//STRIP001      return pTNd->IsInSymbolFont( pPos->nContent.GetIndex() );
//STRIP001  return FALSE;
//STRIP001 }


// zeige das akt. selektierte "Object" an
/*N*/ void SwCrsrShell::MakeSelVisible()
/*N*/ {
/*N*/   ASSERT( bHasFocus, "kein Focus aber Cursor sichtbar machen?" );
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
//STRIP001 FASTBOOL SwCrsrShell::FindValidCntntNode( BOOL bOnlyText )
//STRIP001 {
//STRIP001  if( pTblCrsr )      // was soll ich jetzt machen ??
//STRIP001  {
//STRIP001      ASSERT( !this, "TabellenSelection nicht aufgehoben!" );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  //JP 28.10.97: Bug 45129 - im UI-ReadOnly ist alles erlaubt
//STRIP001  if( !bAllProtect && GetDoc()->GetDocShell() &&
//STRIP001      GetDoc()->GetDocShell()->IsReadOnlyUI() )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  // dann raus da!
//STRIP001  if( pCurCrsr->HasMark() )
//STRIP001      ClearMark();
//STRIP001
//STRIP001  // als erstes mal auf Rahmen abpruefen
//STRIP001  SwNodeIndex& rNdIdx = pCurCrsr->GetPoint()->nNode;
//STRIP001  ULONG nNdIdx = rNdIdx.GetIndex();       // sichern
//STRIP001  SwNodes& rNds = pDoc->GetNodes();
//STRIP001  SwCntntNode* pCNd = rNdIdx.GetNode().GetCntntNode();
//STRIP001  const SwCntntFrm * pFrm;
//STRIP001
//STRIP001  if( pCNd && 0 != (pFrm = pCNd->GetFrm(0,pCurCrsr->GetPoint(),FALSE)) &&
//STRIP001      !IsReadOnlyAvailable() && pFrm->IsProtected() &&
//STRIP001      nNdIdx < rNds.GetEndOfExtras().GetIndex() )
//STRIP001  {
//STRIP001      // geschuetzter Rahmen ueberspringen
//STRIP001      SwPaM aPam( *pCurCrsr->GetPoint() );
//STRIP001      aPam.SetMark();
//STRIP001      aPam.GetMark()->nNode = rNds.GetEndOfContent();
//STRIP001      aPam.GetPoint()->nNode = *pCNd->EndOfSectionNode();
//STRIP001
//STRIP001      FASTBOOL bFirst = FALSE;
//STRIP001      if( 0 == (pCNd = ::GetNode( aPam, bFirst, fnMoveForward, FALSE )))
//STRIP001      {
//STRIP001          aPam.GetMark()->nNode = *rNds.GetEndOfPostIts().StartOfSectionNode();
//STRIP001          pCNd = ::GetNode( aPam, bFirst, fnMoveBackward, FALSE );
//STRIP001      }
//STRIP001
//STRIP001      if( !pCNd )     // sollte nie passieren !!!
//STRIP001      {
//STRIP001          rNdIdx = nNdIdx;        // alten Node zurueck
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      *pCurCrsr->GetPoint() = *aPam.GetPoint();
//STRIP001  }
//STRIP001  else if( bOnlyText && pCNd && pCNd->IsNoTxtNode() )
//STRIP001  {
//STRIP001      // dann auf den Anfang vom Doc stellen
//STRIP001      rNdIdx = pDoc->GetNodes().GetEndOfExtras();
//STRIP001      pCurCrsr->GetPoint()->nContent.Assign( pDoc->GetNodes().GoNext(
//STRIP001                                                          &rNdIdx ), 0 );
//STRIP001      nNdIdx = rNdIdx.GetIndex();
//STRIP001  }
//STRIP001
//STRIP001  BOOL bOk = TRUE;
//STRIP001
//STRIP001     // #i9059# cursor may not stand in protected cells
//STRIP001     //         (unless cursor in protected areas is OK.)
//STRIP001     const SwTableNode* pTableNode = rNdIdx.GetNode().FindTableNode();
//STRIP001     if( !IsReadOnlyAvailable()  &&
//STRIP001         pTableNode != NULL  &&  rNdIdx.GetNode().IsProtect() )
//STRIP001     {
//STRIP001         // we're in a table, and we're in a protected area, so we're
//STRIP001         // probably in a protected cell.
//STRIP001
//STRIP001         // move forward into non-protected area.
//STRIP001         SwPaM aPam( rNdIdx.GetNode(), 0 );
//STRIP001         while( aPam.GetNode()->IsProtect() &&
//STRIP001                aPam.Move( fnMoveForward, fnGoCntnt ) )
//STRIP001             ; // nothing to do in the loop; the aPam.Move does the moving!
//STRIP001
//STRIP001         // didn't work? then go backwards!
//STRIP001         if( aPam.GetNode()->IsProtect() )
//STRIP001         {
//STRIP001             SwPaM aTmpPaM( rNdIdx.GetNode(), 0 );
//STRIP001          aPam = aTmpPaM;
//STRIP001             while( aPam.GetNode()->IsProtect() &&
//STRIP001                    aPam.Move( fnMoveBackward, fnGoCntnt ) )
//STRIP001                 ; // nothing to do in the loop; the aPam.Move does the moving!
//STRIP001         }
//STRIP001
//STRIP001         // if we're successful, set the new position
//STRIP001         if( ! aPam.GetNode()->IsProtect() )
//STRIP001         {
//STRIP001             *pCurCrsr->GetPoint() = *aPam.GetPoint();
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  // in einem geschuetzten Bereich
//STRIP001  const SwSectionNode* pSectNd = rNdIdx.GetNode().FindSectionNode();
//STRIP001  if( pSectNd && ( pSectNd->GetSection().IsHiddenFlag() ||
//STRIP001      ( !IsReadOnlyAvailable() &&
//STRIP001         pSectNd->GetSection().IsProtectFlag() )) )
//STRIP001  {
//STRIP001      typedef SwCntntNode* (SwNodes:: *FNGoSection)( SwNodeIndex *, int, int ) const;
//STRIP001      FNGoSection fnGoSection = &SwNodes::GoNextSection;
//STRIP001
//STRIP001      bOk = FALSE;
//STRIP001
//STRIP001      for( int nLoopCnt = 0; !bOk && nLoopCnt < 2; ++nLoopCnt )
//STRIP001      {
//STRIP001          BOOL bWeiter;
//STRIP001          do {
//STRIP001              bWeiter = FALSE;
//STRIP001              while( 0 != ( pCNd = (rNds.*fnGoSection)( &rNdIdx,
//STRIP001                                          TRUE, !IsReadOnlyAvailable() )) )
//STRIP001              {
//STRIP001                  // in eine Tabelle verschoben -> pruefe ob die
//STRIP001                  // vielleicht geschuetzt ist
//STRIP001                  if( pCNd->FindTableNode() )
//STRIP001                  {
//STRIP001                      SwCallLink aTmp( *this );
//STRIP001                      SwCrsrSaveState aSaveState( *pCurCrsr );
//STRIP001                      aTmp.nNdTyp = 0;        // im DTOR nichts machen!
//STRIP001                      if( !pCurCrsr->IsInProtectTable( TRUE, TRUE ) )
//STRIP001                      {
//STRIP001                          const SwSectionNode* pSNd = pCNd->FindSectionNode();
//STRIP001                          if( !pSNd || !pSNd->GetSection().IsHiddenFlag()
//STRIP001                              || (!IsReadOnlyAvailable()  &&
//STRIP001                                  pSNd->GetSection().IsProtectFlag() ))
//STRIP001                          {
//STRIP001                              bOk = TRUE;
//STRIP001                              break;      // eine nicht geschuetzte Zelle gef.
//STRIP001                          }
//STRIP001                          continue;       // dann weiter suchen
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      bOk = TRUE;
//STRIP001                      break;      // eine nicht geschuetzte Zelle gef.
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( bOk && rNdIdx.GetIndex() < rNds.GetEndOfExtras().GetIndex() )
//STRIP001              {
//STRIP001                  // Teste mal auf Fly - kann auch noch geschuetzt sein!!
//STRIP001                  if( 0 == (pFrm = pCNd->GetFrm(0,0,FALSE)) ||
//STRIP001                      ( !IsReadOnlyAvailable() && pFrm->IsProtected() ) ||
//STRIP001                      ( bOnlyText && pCNd->IsNoTxtNode() ) )
//STRIP001                  {
//STRIP001                      // dann weiter suchen!
//STRIP001                      bOk = FALSE;
//STRIP001                      bWeiter = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          } while( bWeiter );
//STRIP001
//STRIP001          if( !bOk )
//STRIP001          {
//STRIP001              if( !nLoopCnt )
//STRIP001                  fnGoSection = &SwNodes::GoPrevSection;
//STRIP001              rNdIdx = nNdIdx;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( bOk )
//STRIP001  {
//STRIP001      pCNd = rNdIdx.GetNode().GetCntntNode();
//STRIP001 //       USHORT nCntnt = Min( pCNd->Len(), pCurCrsr->GetPoint()->nContent.GetIndex() );
//STRIP001      xub_StrLen nCntnt = rNdIdx.GetIndex() < nNdIdx ? pCNd->Len() : 0;
//STRIP001      pCurCrsr->GetPoint()->nContent.Assign( pCNd, nCntnt );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pCNd = rNdIdx.GetNode().GetCntntNode();
//STRIP001
//STRIP001      // falls Cursor im versteckten Bereich ist, auf jedenfall schon mal
//STRIP001      // verschieben!!
//STRIP001      if( !pCNd || !pCNd->GetFrm(0,0,FALSE) )
//STRIP001      {
//STRIP001          SwCrsrMoveState aTmpState( MV_NONE );
//STRIP001          aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
//STRIP001          GetLayout()->GetCrsrOfst( pCurCrsr->GetPoint(), pCurCrsr->GetPtPos(),
//STRIP001                                      &aTmpState );
//STRIP001      }
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 void SwCrsrShell::NewCoreSelection()
//STRIP001 {
//STRIP001 }


/*N*/ FASTBOOL SwCrsrShell::IsCrsrReadonly() const
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


// darf der Cursor in ReadOnlyBereiche?
/*N*/ void SwCrsrShell::SetReadOnlyAvailable( BOOL bFlag )
/*N*/ {
/*N*/   // im GlobalDoc darf NIE umgeschaltet werden
/*N*/   if( (!GetDoc()->GetDocShell() ||
/*N*/        !GetDoc()->GetDocShell()->IsA( SwGlobalDocShell::StaticType() )) &&
/*N*/       bFlag != bSetCrsrInReadOnly )
/*N*/   {
/*?*/       // wenn das Flag ausgeschaltet wird, dann muessen erstmal alle
/*?*/       // Selektionen aufgehoben werden. Denn sonst wird sich darauf
/*?*/       // verlassen, das nichts geschuetztes selektiert ist!
DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/        if( !bFlag )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ClearMark();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        bSetCrsrInReadOnly = bFlag;
//STRIP001 /*?*/        UpdateCrsr();
/*N*/   }
/*N*/ }

/*N*/ FASTBOOL SwCrsrShell::HasReadonlySel() const
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;
/*N*/   if( IsReadOnlyAvailable() )
/*N*/   {
/*N*/       if( pTblCrsr )
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001        bRet = pTblCrsr->HasReadOnlyBoxSel() ||
//STRIP001 /*?*/                    pTblCrsr->HasReadonlySel();
/*N*/       else
/*N*/       {
/*N*/           const SwPaM* pCrsr = pCurCrsr;
/*N*/
/*N*/           do {
/*N*/               if( pCrsr->HasReadonlySel() )
/*N*/                   bRet = TRUE;
/*N*/           } while( !bRet && pCurCrsr != ( pCrsr = (SwPaM*)pCrsr->GetNext() ));
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

// SwCursor - Methode !!!!
/*N*/ FASTBOOL SwCursor::IsReadOnlyAvailable() const
/*N*/ {
/*N*/   const SwShellCrsr* pShCrsr = *this;
/*N*/   const SwUnoCrsr* pUnoCrsr = *this;
/*N*/   return pShCrsr ? pShCrsr->GetShell()->IsReadOnlyAvailable() :
/*N*/       pUnoCrsr ? TRUE : FALSE;
/*N*/ }


//STRIP001 FASTBOOL SwCrsrShell::IsSelFullPara() const
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001
//STRIP001  if( pCurCrsr->GetPoint()->nNode.GetIndex() ==
//STRIP001      pCurCrsr->GetMark()->nNode.GetIndex() && pCurCrsr == pCurCrsr->GetNext() )
//STRIP001  {
//STRIP001      xub_StrLen nStt = pCurCrsr->GetPoint()->nContent.GetIndex(),
//STRIP001                 nEnd = pCurCrsr->GetMark()->nContent.GetIndex();
//STRIP001      if( nStt > nEnd )
//STRIP001      {
//STRIP001          xub_StrLen nTmp = nStt;
//STRIP001          nStt = nEnd;
//STRIP001          nEnd = nTmp;
//STRIP001      }
//STRIP001      const SwCntntNode* pCNd = pCurCrsr->GetCntntNode();
//STRIP001      bRet = pCNd && !nStt && nEnd == pCNd->Len();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

#ifdef BIDI

/*N*/ short SwCrsrShell::GetTextDirection( const Point* pPt ) const
/*N*/ {
/*N*/   SwPosition aPos( *pCurCrsr->GetPoint() );
/*N*/   Point aPt( pPt ? *pPt : pCurCrsr->GetPtPos() );
/*N*/   if( pPt )
/*N*/   {
/*?*/       SwCrsrMoveState aTmpState( MV_NONE );
/*?*/       aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
/*?*/
/*?*/       GetLayout()->GetCrsrOfst( &aPos, aPt, &aTmpState );
/*N*/   }

/*N*/     return pDoc->GetTextDirection( aPos, &aPt );
/*N*/ }

/*N*/ FASTBOOL SwCrsrShell::IsInVerticalText( const Point* pPt ) const
/*N*/ {
/*N*/     const short nDir = GetTextDirection( pPt );
/*N*/     return FRMDIR_VERT_TOP_RIGHT == nDir || FRMDIR_VERT_TOP_LEFT == nDir;
/*N*/ }

/*N*/ FASTBOOL SwCrsrShell::IsInRightToLeftText( const Point* pPt ) const
/*N*/ {
/*N*/     const short nDir = GetTextDirection( pPt );
/*N*/     // GetTextDirection uses FRMDIR_VERT_TOP_LEFT to indicate RTL in
/*N*/     // vertical environment
/*N*/     return FRMDIR_VERT_TOP_LEFT == nDir || FRMDIR_HORI_RIGHT_TOP == nDir;
/*N*/ }

#else

/*?*/ FASTBOOL SwCrsrShell::IsInVerticalText( const Point* pPt ) const
/*?*/ {
/*?*/   SwPosition aPos( *pCurCrsr->GetPoint() );
/*?*/   Point aPt( pPt ? *pPt : pCurCrsr->GetPtPos() );
/*?*/   if( pPt )
/*?*/   {
/*?*/       SwCrsrMoveState aTmpState( MV_NONE );
/*?*/       aTmpState.bSetInReadOnly = IsReadOnlyAvailable();
/*?*/
/*?*/       GetLayout()->GetCrsrOfst( &aPos, aPt, &aTmpState );
/*?*/   }
/*?*/   return pDoc->IsInVerticalText( aPos, &aPt );
/*?*/ }

#endif

/*  */

    // die Suchfunktionen
//STRIP001 ULONG SwCrsrShell::Find( const SearchOptions& rSearchOpt,
//STRIP001                          SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001                             BOOL& bCancel,
//STRIP001                          FindRanges eRng, int bReplace )
//STRIP001 {
//STRIP001  if( pTblCrsr )
//STRIP001      GetCrsr();
//STRIP001  delete pTblCrsr, pTblCrsr = 0;
//STRIP001     SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001     ULONG nRet = pCurCrsr->Find( rSearchOpt, eStart, eEnde, bCancel, eRng, bReplace );
//STRIP001     if( nRet || bCancel )
//STRIP001         UpdateCrsr();
//STRIP001     return nRet;
//STRIP001 }

//STRIP001 ULONG SwCrsrShell::Find( const SwTxtFmtColl& rFmtColl,
//STRIP001                          SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001                          BOOL& bCancel,
//STRIP001                          FindRanges eRng, const SwTxtFmtColl* pReplFmt )
//STRIP001 {
//STRIP001  if( pTblCrsr )
//STRIP001      GetCrsr();
//STRIP001  delete pTblCrsr, pTblCrsr = 0;
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  ULONG nRet = pCurCrsr->Find( rFmtColl, eStart, eEnde, bCancel, eRng, pReplFmt );
//STRIP001  if( nRet )
//STRIP001      UpdateCrsr();
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 ULONG SwCrsrShell::Find( const SfxItemSet& rSet, FASTBOOL bNoCollections,
//STRIP001                          SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001                          BOOL& bCancel,
//STRIP001                          FindRanges eRng, const SearchOptions* pSearchOpt,
//STRIP001                          const SfxItemSet* rReplSet )
//STRIP001 {
//STRIP001  if( pTblCrsr )
//STRIP001      GetCrsr();
//STRIP001  delete pTblCrsr, pTblCrsr = 0;
//STRIP001  SwCallLink aLk( *this );        // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  ULONG nRet = pCurCrsr->Find( rSet, bNoCollections, eStart, eEnde, bCancel,
//STRIP001                              eRng, pSearchOpt, rReplSet );
//STRIP001  if( nRet )
//STRIP001      UpdateCrsr();
//STRIP001  return nRet;
//STRIP001 }

/*N*/ void SwCrsrShell::SetSelection( const SwPaM& rCrsr )
/*N*/ {
/*N*/   StartAction();
/*N*/   BOOL bFirst = TRUE;
/*N*/   SwPaM* pCrsr = GetCrsr();
/*N*/   *pCrsr->GetPoint() = *rCrsr.GetPoint();
/*N*/   if(rCrsr.HasMark())
/*N*/   {
/*N*/       pCrsr->SetMark();
/*N*/       *pCrsr->GetMark() = *rCrsr.GetMark();
/*N*/   }
/*N*/   if((SwPaM*)rCrsr.GetNext() != &rCrsr)
/*N*/   {
/*N*/       const SwPaM *_pStartCrsr = (SwPaM*)rCrsr.GetNext(), *__pStartCrsr = _pStartCrsr;
/*N*/       do
/*N*/       {
/*N*/           SwPaM* pCurCrsr = CreateCrsr();
/*N*/           *pCurCrsr->GetPoint() = *_pStartCrsr->GetPoint();
/*N*/           if(_pStartCrsr->HasMark())
/*N*/           {
/*N*/               pCurCrsr->SetMark();
/*N*/               *pCurCrsr->GetMark() = *_pStartCrsr->GetMark();
/*N*/           }
/*N*/       } while( (_pStartCrsr=(SwPaM *)_pStartCrsr->GetNext()) != &rCrsr );
/*N*/   }
/*N*/   EndAction();
/*N*/ }

/*  */

#if !defined(PRODUCT) || defined(WIN)

//STRIP001 void SwCrsrShell::SetMark()
//STRIP001 {
//STRIP001  pCurCrsr->SetMark();
//STRIP001 }

//STRIP001 FASTBOOL SwCrsrShell::HasMark()
//STRIP001 {
//STRIP001  return pCurCrsr->HasMark();
//STRIP001 }

/*N*/ SwCursor* SwCrsrShell::GetSwCrsr( FASTBOOL bMakeTblCrsr ) const
/*N*/ {
/*N*/   return (SwCursor*)GetCrsr( bMakeTblCrsr );
/*N*/ }

// gebe den Stack Cursor zurueck
/*N*/ SwPaM * SwCrsrShell::GetStkCrsr() const           { return pCrsrStk; }

// gebe den TabellenCrsr zurueck
/*N*/ const SwPaM* SwCrsrShell::GetTblCrs() const   { return pTblCrsr; }
/*N*/       SwPaM* SwCrsrShell::GetTblCrs()         { return pTblCrsr; }

// Abfrage, ob ueberhaupt eine Selektion existiert, sprich der akt. Cursor
// aufgespannt oder nicht der einzigste ist.

/*N*/ FASTBOOL SwCrsrShell::IsSelection() const
/*N*/ {
/*N*/   return IsTableMode() || pCurCrsr->HasMark() ||
/*N*/           pCurCrsr->GetNext() != pCurCrsr;
/*N*/ }
// returns if multiple cursors are available
/*N*/ FASTBOOL SwCrsrShell::IsMultiSelection() const
/*N*/ {
/*N*/     return pCurCrsr->GetNext() != pCurCrsr;
/*N*/ }

// pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
/*N*/ const SwTableNode* SwCrsrShell::IsCrsrInTbl( BOOL bIsPtInTbl ) const
/*N*/ {
/*N*/   return pCurCrsr->GetNode( bIsPtInTbl )->FindTableNode();
/*N*/ }


/*?*/ FASTBOOL SwCrsrShell::IsCrsrPtAtEnd() const
/*?*/ {
/*?*/   return pCurCrsr->End() == pCurCrsr->GetPoint();
/*?*/ }


/*?*/ Point& SwCrsrShell::GetCrsrDocPos( BOOL bPoint ) const
/*?*/ {
/*?*/   return bPoint ? pCurCrsr->GetPtPos() : pCurCrsr->GetMkPos();
/*?*/ }


/*?*/ void SwCrsrShell::UnSetVisCrsr()
/*?*/ {
/*?*/   pVisCrsr->Hide();
/*?*/   pVisCrsr->SetDragCrsr( FALSE );
/*?*/ }


/*?*/ FASTBOOL SwCrsrShell::IsSelOnePara() const
/*?*/ {
/*?*/   return pCurCrsr == pCurCrsr->GetNext() &&
/*?*/          pCurCrsr->GetPoint()->nNode ==
/*?*/          pCurCrsr->GetMark()->nNode;
/*?*/ }

/*?*/ SwMoveFnCollection* SwCrsrShell::MakeFindRange(
/*?*/                           USHORT nStt, USHORT nEnd, SwPaM* pPam ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001    return pCurCrsr->MakeFindRange( (SwDocPositions)nStt,
//STRIP001 /*?*/                                    (SwDocPositions)nEnd, pPam );
/*?*/ }
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
/*?*/         ASSERT(bFound, "no content node found");
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
/*?*/         {DBG_ASSERT(0, "STRIP"); }//STRIP001 TblCrsrToCursor();
/*N*/ }

