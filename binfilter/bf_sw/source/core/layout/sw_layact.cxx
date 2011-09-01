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

#include <time.h>
#include "pagefrm.hxx"

#include <horiornt.hxx>

#include "doc.hxx"
#include "viewimp.hxx"
#include "crsrsh.hxx"
#include "dflyobj.hxx"
#include "frmtool.hxx"
#include "dcontact.hxx"
#include "frmfmt.hxx"
#include "swregion.hxx"
#include "viewopt.hxx"  // OnlineSpelling ueber Internal-TabPage testen.
#include "pam.hxx"      // OnlineSpelling wg. der aktuellen Cursorposition
#include "dbg_lay.hxx"
#include "layouter.hxx" // LoopControlling

#include <ftnidx.hxx>

#include <vcl/window.hxx>
#include <vcl/svapp.hxx>
#include <bf_svx/brshitem.hxx>

#define _SVSTDARR_BOOLS

#define _LAYACT_CXX
#include "layact.hxx"

#include <swwait.hxx>
#include <fmtanchr.hxx>
#include <bf_sfx2/progress.hxx>

#include "tabfrm.hxx"
#include "ftnfrm.hxx"
#include "txtfrm.hxx"
#include "flyfrms.hxx"
#include "frmsh.hxx"
#include "mdiexp.hxx"
#include "fmtornt.hxx"
#include "sectfrm.hxx"
#include <acmplwrd.hxx>
namespace binfilter {

//#pragma optimize("ity",on)

/*************************************************************************
|*
|*  SwLayAction Statisches Geraffel
|*
|*************************************************************************/

/*N*/ #define IS_FLYS (pPage->GetSortedObjs())
/*N*/ #define IS_INVAFLY (pPage->IsInvalidFly())


//Sparen von Schreibarbeit um den Zugriff auf zerstoerte Seiten zu vermeiden.
/*N*/ #ifdef DBG_UTIL

/*N*/ static void BreakPoint()
/*N*/ {
/*N*/   return;
/*N*/ }

/*N*/ #define CHECKPAGE \
/*N*/           {   if ( IsAgain() ) \
/*N*/               {   BreakPoint(); \
/*N*/                   return; \
/*N*/               } \
/*N*/           }
/*N*/
/*N*/ #else
/*?*/ #define CHECKPAGE \
/*?*/           {   if ( IsAgain() ) \
/*?*/                   return; \
/*?*/           }
/*?*/
/*N*/ #endif

/*N*/ #define RESCHEDULE \
/*N*/   { \
/*N*/       if ( IsReschedule() )  \
/*N*/         { \
/*N*/             if (pProgress) pProgress->Reschedule(); \
/*N*/           ::binfilter::RescheduleProgress( pImp->GetShell()->GetDoc()->GetDocShell() ); \
/*N*/         } \
/*N*/   }

/*N*/ inline ULONG Ticks()
/*N*/ {
/*N*/   return 1000 * clock() / CLOCKS_PER_SEC;
/*N*/ }

/*N*/ void SwLayAction::CheckWaitCrsr()
/*N*/ {
/*N*/   RESCHEDULE
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::CheckIdleEnd()
|*
|*************************************************************************/
//Ist es wirklich schon soweit...
/*N*/ inline void SwLayAction::CheckIdleEnd()
/*N*/ {
/*N*/   if ( !IsInput() )
/*N*/         bInput = GetInputType() && Application::AnyInput( GetInputType() );
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::PaintCntnt()
|*
|*  Beschreibung        Je nach Typ wird der Cntnt entsprechend seinen
|*      Veraenderungen ausgegeben bzw. wird die auszugebende Flaeche in der
|*      Region eingetragen.
|*      PaintCntnt:  fuellt die Region,
|*
|*************************************************************************/
/*N*/ BOOL SwLayAction::PaintWithoutFlys( const SwRect &rRect, const SwCntntFrm *pCnt,
/*N*/                                   const SwPageFrm *pPage )
/*N*/ {
/*N*/   SwRegionRects aTmp( rRect );
/*N*/   const SwSortDrawObjs &rObjs = *pPage->GetSortedObjs();
/*N*/   const SwFlyFrm *pSelfFly = pCnt->FindFlyFrm();
/*N*/
        USHORT i=0;
/*N*/   for ( i = 0; i < rObjs.Count() && aTmp.Count(); ++i )
/*N*/   {
/*N*/       SdrObject *pO = rObjs[i];
/*N*/       if ( !pO->IsWriterFlyFrame() )
/*N*/           continue;
/*N*/
/*N*/       SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/
/*N*/       if ( pFly == pSelfFly || !rRect.IsOver( pFly->Frm() ) )
/*N*/           continue;
/*?*/ DBG_BF_ASSERT(0, "STRIP");
/*N*/   }
/*N*/
/*N*/   BOOL bPaint1 = FALSE;
/*N*/   const SwRect *pData = aTmp.GetData();
/*N*/   for ( i = 0; i < aTmp.Count(); ++pData, ++i )
/*N*/       bPaint1 |= pImp->GetShell()->AddPaintRect( *pData );
/*N*/   return bPaint1;
/*N*/ }

/*N*/ inline BOOL SwLayAction::_PaintCntnt( const SwCntntFrm *pCntnt,
/*N*/                                     const SwPageFrm *pPage,
/*N*/                                     const SwRect &rRect )
/*N*/ {
/*N*/   if ( rRect.HasArea() )
/*N*/   {
/*N*/       if ( pPage->GetSortedObjs() )
/*N*/           return PaintWithoutFlys( rRect, pCntnt, pPage );
/*N*/       else
/*N*/           return pImp->GetShell()->AddPaintRect( rRect );
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ void SwLayAction::PaintCntnt( const SwCntntFrm *pCnt,
/*N*/                             const SwPageFrm *pPage,
/*N*/                               const SwRect &rOldRect,
/*N*/                               long nOldBottom )
/*N*/ {
/*N*/     SWRECTFN( pCnt )
/*N*/
/*N*/     if ( pCnt->IsCompletePaint() || !pCnt->IsTxtFrm() )
/*N*/   {
/*N*/       SwRect aPaint( pCnt->PaintArea() );
/*N*/         // paint of old area no longer needed.
/*N*/       if ( !_PaintCntnt( pCnt, pPage, aPaint ) )
/*N*/           pCnt->ResetCompletePaint();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         // paint the area between printing bottom and frame bottom and
/*N*/         // the area left and right beside the frame, if its height changed.
/*N*/         long nOldHeight = (rOldRect.*fnRect->fnGetHeight)();
/*N*/         long nNewHeight = (pCnt->Frm().*fnRect->fnGetHeight)();
/*N*/         const bool bHeightDiff = nOldHeight != nNewHeight;
/*N*/         if( bHeightDiff )
/*N*/         {
/*N*/             // consider whole potential paint area.
/*N*/             //SwRect aDrawRect( pCnt->UnionFrm( TRUE ) );
/*N*/             SwRect aDrawRect( pCnt->PaintArea() );
/*N*/             if( nOldHeight > nNewHeight )
/*N*/                 nOldBottom = (pCnt->*fnRect->fnGetPrtBottom)();
/*N*/             (aDrawRect.*fnRect->fnSetTop)( nOldBottom );
/*N*/             _PaintCntnt( pCnt, pPage, aDrawRect );
/*N*/         }
/*N*/         // paint content area
/*N*/         SwRect aPaintRect = static_cast<SwTxtFrm*>(const_cast<SwCntntFrm*>(pCnt))->Paint();
/*N*/         _PaintCntnt( pCnt, pPage, aPaintRect );
/*N*/   }
/*N*/
/*N*/   if ( pCnt->IsRetouche() && !pCnt->GetNext() )
/*N*/   {
/*N*/       const SwFrm *pTmp = pCnt;
/*N*/       if( pCnt->IsInSct() )
/*N*/       {
/*N*/           const SwSectionFrm* pSct = pCnt->FindSctFrm();
/*N*/           if( pSct->IsRetouche() && !pSct->GetNext() )
/*N*/               pTmp = pSct;
/*N*/       }
/*N*/       SwRect aRect( pTmp->GetUpper()->PaintArea() );
/*N*/         (aRect.*fnRect->fnSetTop)( (pTmp->*fnRect->fnGetPrtBottom)() );
/*N*/       if ( !_PaintCntnt( pCnt, pPage, aRect ) )
/*N*/           pCnt->ResetRetouche();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::_AddScrollRect()
|*
|*************************************************************************/
/*N*/ BOOL MA_FASTCALL lcl_IsOverObj( const SwFrm *pFrm, const SwPageFrm *pPage,
/*N*/                      const SwRect &rRect1, const SwRect &rRect2,
/*N*/                      const SwLayoutFrm *pLay )
/*N*/ {
/*N*/   const SwSortDrawObjs &rObjs = *pPage->GetSortedObjs();
/*N*/   const SwFlyFrm *pSelfFly = pFrm->FindFlyFrm();
/*N*/   const BOOL bInCnt = pSelfFly && pSelfFly->IsFlyInCntFrm() ? TRUE : FALSE;
/*N*/
/*N*/   for ( USHORT j = 0; j < rObjs.Count(); ++j )
/*N*/   {
/*N*/       const SdrObject         *pObj = rObjs[j];
/*N*/       const SwRect aRect( pObj->GetBoundRect() );
/*N*/       if ( !rRect1.IsOver( aRect ) && !rRect2.IsOver( aRect ) )
/*N*/           continue;       //Keine Ueberlappung, der naechste.
/*N*/
/*N*/       const SwVirtFlyDrawObj *pFlyObj = pObj->IsWriterFlyFrame() ?
/*N*/                                               (SwVirtFlyDrawObj*)pObj : 0;
/*N*/       const SwFlyFrm *pFly = pFlyObj ? pFlyObj->GetFlyFrm() : 0;
/*N*/
/*N*/       //Wenn der Rahmen innerhalb des LayFrm verankert ist, so darf er
/*N*/       //mitgescrollt werden, wenn er nicht seitlich aus dem Rechteck
/*N*/       //herausschaut.
/*N*/       if ( pLay && pFlyObj && pFlyObj->GetFlyFrm()->IsLowerOf( pLay ) )
/*N*/       {
/*?*/            if ( pFly->Frm().Left() < rRect1.Left() ||
/*?*/                 pFly->Frm().Right()> rRect1.Right() )
/*?*/               return TRUE;
/*?*/           continue;
/*N*/       }
/*N*/
/*N*/       if ( !pSelfFly )    //Nur wenn der Frm in einem Fly steht kann
/*N*/           return TRUE;    //es Einschraenkungen geben.
/*N*/
/*?*/       if ( !pFlyObj )     //Keine Einschraenkung fuer Zeichenobjekte.
/*?*/           return TRUE;
/*?*/
/*?*/       if ( pFly != pSelfFly )
/*?*/       {
/*?*/           //Flys unter dem eigenen nur dann abziehen, wenn sie innerhalb des
/*?*/           //eigenen stehen.
/*?*/           //Fuer inhaltsgebundene Flys alle Flys abziehen fuer die gilt, dass
/*?*/           //pSelfFly nicht innerhalb von ihnen steht.
/*?*/           if ( bInCnt )
/*?*/           {
/*?*/               const SwFlyFrm *pTmp = pSelfFly->GetAnchor()->FindFlyFrm();
/*?*/               while ( pTmp )
/*?*/               {
/*?*/                   if ( pTmp == pFly )
/*?*/                       return FALSE;
/*?*/                   else
/*?*/                       pTmp = pTmp->GetAnchor()->FindFlyFrm();
/*?*/               }
/*?*/           } else if ( pObj->GetOrdNum() < pSelfFly->GetVirtDrawObj()->GetOrdNum() )
/*?*/           {
/*?*/               const SwFlyFrm *pTmp = pFly;
/*?*/               do
/*?*/               {   if ( pTmp == pSelfFly )
/*?*/                       return TRUE;
/*?*/                   else
/*?*/                       pTmp = pTmp->GetAnchor()->FindFlyFrm();
/*?*/               } while ( pTmp );
/*?*/           } else
/*?*/               return TRUE;
/*?*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ void SwLayAction::_AddScrollRect( const SwCntntFrm *pCntnt,
/*N*/                                 const SwPageFrm *pPage,
/*N*/                                 const SwTwips nOfst,
/*N*/                                 const SwTwips nOldBottom )
/*N*/ {
/*N*/   bool bScroll = TRUE;
/*N*/   SwRect aPaintRect( pCntnt->PaintArea() );
/*N*/     SWRECTFN( pCntnt )
/*N*/
/*N*/   //Wenn altes oder neues Rechteck mit einem Fly ueberlappen, in dem der
/*N*/   //Cntnt nicht selbst steht, so ist nichts mit Scrollen.
/*N*/   if ( pPage->GetSortedObjs() )
/*N*/   {
/*N*/       SwRect aRect( aPaintRect );
/*N*/         if( bVert )
/*?*/             aPaintRect.Pos().X() += nOfst;
/*N*/         else
/*N*/       aPaintRect.Pos().Y() -= nOfst;
/*N*/       if ( ::binfilter::lcl_IsOverObj( pCntnt, pPage, aPaintRect, aRect, 0 ) )
/*N*/           bScroll = FALSE;
/*N*/         if( bVert )
/*?*/             aPaintRect.Pos().X() -= nOfst;
/*N*/         else
/*N*/       aPaintRect.Pos().Y() += nOfst;
/*N*/   }
/*N*/   if ( bScroll && pPage->GetFmt()->GetBackground().GetGraphicPos() != GPOS_NONE )
/*N*/       bScroll = FALSE;
/*N*/
    // Don't intersect potential paint rectangle with
    // union of frame and printing area, because at scroll destination position
    // could be a frame that has filled up the potential paint area.
    //aPaintRect.Intersection( pCntnt->UnionFrm( TRUE ) );

/*N*/   if ( bScroll )
/*N*/   {
/*N*/       if( aPaintRect.HasArea() )
/*N*/           pImp->GetShell()->AddScrollRect( pCntnt, aPaintRect, nOfst );
/*N*/       if ( pCntnt->IsRetouche() && !pCntnt->GetNext() )
/*N*/       {
/*N*/           SwRect aRect( pCntnt->GetUpper()->PaintArea() );
/*N*/             (aRect.*fnRect->fnSetTop)( (pCntnt->*fnRect->fnGetPrtBottom)() );
/*N*/           if ( !pImp->GetShell()->AddPaintRect( aRect ) )
/*N*/               pCntnt->ResetRetouche();
/*N*/       }
/*N*/       pCntnt->ResetCompletePaint();
/*N*/   }
/*N*/   else if( aPaintRect.HasArea() )
/*N*/   {
/*N*/         if( bVert )
/*?*/             aPaintRect.Pos().X() += nOfst;
/*N*/         else
/*N*/       aPaintRect.Pos().Y() -= nOfst;
/*N*/       PaintCntnt( pCntnt, pPage, aPaintRect, nOldBottom );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::SwLayAction()
|*
|*************************************************************************/
/*N*/ SwLayAction::SwLayAction( SwRootFrm *pRt, SwViewImp *pI )
/*N*/   : pRoot( pRt )
/*N*/   , pImp( pI )
/*N*/   , pOptTab( 0 )
/*N*/   , pWait( 0 )
/*N*/   , pProgress(NULL)
/*N*/   , nPreInvaPage( USHRT_MAX )
/*N*/   , nStartTicks( Ticks() )
/*N*/   , nInputType( 0 )
/*N*/   , nEndPage( USHRT_MAX )
/*N*/   , nCheckPageNum( USHRT_MAX )
/*N*/ {
/*N*/   bPaintExtraData = ::binfilter::IsExtraData( pImp->GetShell()->GetDoc() );
/*N*/   bPaint = bComplete = bWaitAllowed = bCheckPages = TRUE;
/*N*/   bInput = bAgain = bNextCycle = bCalcLayout = bIdle = bReschedule =
/*N*/   bUpdateExpFlds = bBrowseActionStop = bActionInProgress = FALSE;
/*N*/     // init new flag <mbFormatCntntOnInterrupt>.
/*N*/     mbFormatCntntOnInterrupt = sal_False;
/*N*/
/*N*/     pImp->pLayAct = this;   //Anmelden
/*N*/ }

/*N*/ SwLayAction::~SwLayAction()
/*N*/ {
/*N*/   OSL_ENSURE( !pWait, "Wait object not destroyed" );
/*N*/   pImp->pLayAct = 0;      //Abmelden
/*N*/ }

/*************************************************************************
|*
|*  Beschreibung:       Liefert ein True, wenn die Seite vollstaendig unter
|*      oder rechts neben dem sichbaren Bereich liegt.
|*      Es kann passieren, dass sich die Verhaeltnisse derart aendern, dass
|*      die Verarbeitung (des Aufrufers!) mit der Vorgaengerseite der
|*      uebergebenen Seite weitergefuehrt werden muss. Der Paramter wird also
|*      ggf. veraendert!
|*      Fuer den BrowseMode kann auch dann der ShortCut aktiviert werden,
|*      wenn der ungueltige Inhalt der Seite unterhalb des sichbaren
|*      bereiches liegt.
|*
|*************************************************************************/
/*N*/ const SwFrm *lcl_FindFirstInvaLay( const SwFrm *pFrm, long nBottom )
/*N*/ {
/*N*/   OSL_ENSURE( pFrm->IsLayoutFrm(), "FindFirstInvaLay, no LayFrm" );
/*N*/
/*N*/   if ( !pFrm->IsValid() || (pFrm->IsCompletePaint() &&
/*N*/        pFrm->Frm().Top() < nBottom) )
/*N*/       return pFrm;
/*N*/   pFrm = ((SwLayoutFrm*)pFrm)->Lower();
/*N*/   while ( pFrm )
/*N*/   {
/*N*/       if ( pFrm->IsLayoutFrm() )
/*N*/       {
/*N*/           if ( !pFrm->IsValid() || (pFrm->IsCompletePaint() &&
/*N*/                pFrm->Frm().Top() < nBottom) )
/*N*/               return pFrm;
/*N*/           const SwFrm *pTmp;
/*N*/           if ( 0 != (pTmp = ::binfilter::lcl_FindFirstInvaLay( pFrm, nBottom )) )
/*N*/               return pTmp;
/*N*/       }
/*N*/       pFrm = pFrm->GetNext();
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ const SwFrm *lcl_FindFirstInvaCntnt( const SwLayoutFrm *pLay, long nBottom,
/*N*/                                    const SwCntntFrm *pFirst )
/*N*/ {
/*N*/   const SwCntntFrm *pCnt = pFirst ? pFirst->GetNextCntntFrm() :
/*N*/                                     pLay->ContainsCntnt();
/*N*/   while ( pCnt )
/*N*/   {
/*N*/       if ( !pCnt->IsValid() || pCnt->IsCompletePaint() )
/*N*/       {
/*N*/           if ( pCnt->Frm().Top() <= nBottom )
/*N*/               return pCnt;
/*N*/       }
/*N*/
/*N*/       if ( pCnt->GetDrawObjs() )
/*N*/       {
/*N*/           const SwDrawObjs &rObjs = *pCnt->GetDrawObjs();
/*N*/           for ( USHORT i = 0; i < rObjs.Count(); ++i )
/*N*/           {
/*N*/               const SdrObject *pO = rObjs[i];
/*N*/               if ( pO->IsWriterFlyFrame() )
/*N*/               {
/*N*/                   const SwFlyFrm* pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/                   if ( pFly->IsFlyInCntFrm() )
/*N*/                   {
/*N*/                       if ( ((SwFlyInCntFrm*)pFly)->IsInvalid() ||
/*N*/                            pFly->IsCompletePaint() )
/*N*/                       {
/*N*/                           if ( pFly->Frm().Top() <= nBottom )
/*N*/                               return pFly;
/*N*/                       }
/*N*/                       const SwFrm *pFrm = lcl_FindFirstInvaCntnt( pFly, nBottom, 0 );
/*N*/                       if ( pFrm && pFrm->Frm().Bottom() <= nBottom )
/*N*/                           return pFrm;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       if ( pCnt->Frm().Top() > nBottom && !pCnt->IsInTab() )
/*N*/           return 0;
/*N*/       pCnt = pCnt->GetNextCntntFrm();
/*N*/       if ( !pLay->IsAnLower( pCnt ) )
/*N*/           break;
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::ChkFlyAnchor()
|*
|*************************************************************************/
/*N*/ void SwLayAction::ChkFlyAnchor( SwFlyFrm *pFly, const SwPageFrm *pPage )
/*N*/ {
/*N*/   //Wenn der Fly innerhalb eines anderen Rahmens gebunden ist, so sollte
/*N*/   //dieser zuerst Formatiert werden.
/*N*/
/*N*/   if ( pFly->GetAnchor()->IsInTab() )
/*N*/       pFly->GetAnchor()->FindTabFrm()->Calc();
/*N*/
/*N*/   SwFlyFrm *pAnch = pFly->GetAnchor()->FindFlyFrm();
/*N*/   if ( pAnch )
/*N*/   {
/*N*/       ChkFlyAnchor( pAnch, pPage );
/*N*/       CHECKPAGE;
/*N*/       while ( pPage == pAnch->FindPageFrm() && FormatLayoutFly( pAnch ) )
/*N*/           /* do nothing */;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::FormatLayout(), FormatLayoutFly, FormatLayoutTab()
|*
|*************************************************************************/
// introduce support for vertical layout
/*N*/ BOOL SwLayAction::FormatLayout( SwLayoutFrm *pLay, BOOL bAddRect )
/*N*/ {
/*N*/   OSL_ENSURE( !IsAgain(), "Ungueltige Seite beachten." );
/*N*/   if ( IsAgain() )
/*?*/       return FALSE;
/*N*/
/*N*/   BOOL bChanged = FALSE;
/*N*/   BOOL bAlreadyPainted = FALSE;
/*N*/     // remember frame at complete paint
/*N*/     SwRect aFrmAtCompletePaint;
/*N*/
/*N*/   if ( !pLay->IsValid() || pLay->IsCompletePaint() )
/*N*/   {
/*N*/       if ( pLay->GetPrev() && !pLay->GetPrev()->IsValid() )
/*N*/           pLay->GetPrev()->SetCompletePaint();
/*N*/
/*N*/       SwRect aOldRect( pLay->Frm() );
/*N*/       pLay->Calc();
/*N*/       if ( aOldRect != pLay->Frm() )
/*N*/           bChanged = TRUE;
/*N*/
/*N*/       bool bNoPaint = FALSE;
/*N*/         if ( pLay->IsPageBodyFrm() &&
/*N*/              pLay->Frm().Pos() == aOldRect.Pos() &&
/*N*/              pLay->Lower() &&
/*N*/              pLay->GetFmt()->GetDoc()->IsBrowseMode() )
/*N*/       {
/*N*/           //HotFix: Vobis Homepage, nicht so genau hinsehen, sonst
/*N*/           //rpaints
/*N*/
/*N*/           //Einschraenkungen wegen Kopf-/Fusszeilen
/*N*/             if ( !( pLay->IsCompletePaint() &&
/*N*/                    ( pLay->GetFmt()->GetDoc()->IsHeadInBrowse() ||
/*N*/                      pLay->GetFmt()->GetDoc()->IsFootInBrowse() ||
/*N*/                      pLay->FindPageFrm()->FindFtnCont() )
/*N*/                   )
/*N*/                )
/*N*/           {
/*N*/               bNoPaint = TRUE;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( !bNoPaint && IsPaint() && bAddRect && (pLay->IsCompletePaint() || bChanged) )
/*N*/       {
/*N*/           SwRect aPaint( pLay->Frm() );
/*N*/             // #i9719# - consider border and shadow for
/*N*/             // page frames -> enlarge paint rectangle correspondingly.
/*N*/             if ( pLay->IsPageFrm() )
/*N*/             {
/*N*/                 SwPageFrm* pPageFrm = static_cast<SwPageFrm*>(pLay);
/*N*/                 const int nBorderWidth =
/*N*/                         pImp->GetShell()->GetOut()->PixelToLogic( Size( pPageFrm->BorderPxWidth(), 0 ) ).Width();
/*N*/                 const int nShadowWidth =
/*N*/                         pImp->GetShell()->GetOut()->PixelToLogic( Size( pPageFrm->ShadowPxWidth(), 0 ) ).Width();
/*N*/                 aPaint.Left( aPaint.Left() - nBorderWidth );
/*N*/                 aPaint.Top( aPaint.Top() - nBorderWidth );
/*N*/                 aPaint.Right( aPaint.Right() + nBorderWidth + nShadowWidth );
/*N*/                 aPaint.Bottom( aPaint.Bottom() + nBorderWidth + nShadowWidth );
/*N*/             }
/*N*/
/*N*/             if ( pLay->IsPageFrm() &&
/*N*/                  pLay->GetFmt()->GetDoc()->IsBrowseMode() )
/*N*/           {
/*N*/                 // NOTE: no vertical layout in online layout
/*N*/                 //Ist die Aenderung ueberhaupt sichtbar?
/*N*/               if ( pLay->IsCompletePaint() )
/*N*/               {
/*N*/                   pImp->GetShell()->AddPaintRect( aPaint );
/*N*/                   bAddRect = FALSE;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   SwRegionRects aRegion( aOldRect );
/*N*/                   aRegion -= aPaint;
                        USHORT i=0;
/*N*/                   for ( i = 0; i < aRegion.Count(); ++i )
/*N*/                       pImp->GetShell()->AddPaintRect( aRegion[i] );
/*N*/                     aRegion.ChangeOrigin( aPaint );
/*N*/                   aRegion.Remove( 0, aRegion.Count() );
/*N*/                   aRegion.Insert( aPaint, 0 );
/*N*/                   aRegion -= aOldRect;
/*N*/                   for ( i = 0; i < aRegion.Count(); ++i )
/*N*/                       pImp->GetShell()->AddPaintRect( aRegion[i] );
/*N*/               }
/*N*/
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pImp->GetShell()->AddPaintRect( aPaint );
/*N*/                 bAlreadyPainted = TRUE;
/*N*/                 // remember frame at complete paint
/*N*/                 aFrmAtCompletePaint = pLay->Frm();
/*N*/           }
/*N*/
/*N*/             // #i9719# - provide paint of spacing
/*N*/             // between pages (not only for in online mode).
/*N*/             if ( pLay->IsPageFrm() )
/*N*/             {
/*N*/                 if ( pLay->GetPrev() )
/*N*/                 {
/*N*/                     SwRect aSpaceToPrevPage( pLay->Frm() );
/*N*/                     SwTwips nTop = aSpaceToPrevPage.Top() - DOCUMENTBORDER/2;
/*N*/                     if ( nTop >= 0 )
/*N*/                         aSpaceToPrevPage.Top( nTop );
/*N*/                     aSpaceToPrevPage.Bottom( pLay->Frm().Top() );
/*N*/                     pImp->GetShell()->AddPaintRect( aSpaceToPrevPage );
/*N*/                 }
/*N*/                 if ( pLay->GetNext() )
/*N*/                 {
/*N*/                     SwRect aSpaceToNextPage( pLay->Frm() );
/*N*/                     aSpaceToNextPage.Bottom( aSpaceToNextPage.Bottom() + DOCUMENTBORDER/2 );
/*N*/                     aSpaceToNextPage.Top( pLay->Frm().Bottom() );
/*N*/                     pImp->GetShell()->AddPaintRect( aSpaceToNextPage );
/*N*/                 }
/*N*/             }
/*N*/
/*N*/         }
/*N*/       pLay->ResetCompletePaint();
/*N*/   }
/*N*/
/*N*/   if ( IsPaint() && bAddRect &&
/*N*/        !pLay->GetNext() && pLay->IsRetoucheFrm() && pLay->IsRetouche() )
/*N*/   {
/*N*/         // vertical layout support
/*N*/         SWRECTFN( pLay );
/*N*/         SwRect aRect( pLay->GetUpper()->PaintArea() );
/*N*/         (aRect.*fnRect->fnSetTop)( (pLay->*fnRect->fnGetPrtBottom)() );
/*N*/       if ( !pImp->GetShell()->AddPaintRect( aRect ) )
/*N*/           pLay->ResetRetouche();
/*N*/   }
/*N*/
/*N*/   if( bAlreadyPainted )
/*N*/       bAddRect = FALSE;
/*N*/
/*N*/   CheckWaitCrsr();
/*N*/
/*N*/   if ( IsAgain() )
/*N*/       return FALSE;
/*N*/
/*N*/   //Jetzt noch diejenigen Lowers versorgen die LayoutFrm's sind
/*N*/
/*N*/   if ( pLay->IsFtnFrm() ) //Hat keine LayFrms als Lower.
/*N*/       return bChanged;
/*N*/
/*N*/   SwFrm *pLow = pLay->Lower();
/*N*/   BOOL bTabChanged = FALSE;
/*N*/   while ( pLow && pLow->GetUpper() == pLay )
/*N*/   {
/*N*/       if ( pLow->IsLayoutFrm() )
/*N*/       {
/*N*/           if ( pLow->IsTabFrm() )
/*N*/               bTabChanged |= FormatLayoutTab( (SwTabFrm*)pLow, bAddRect );
/*N*/           // bereits zum Loeschen angemeldete Ueberspringen
/*N*/           else if( !pLow->IsSctFrm() || ((SwSectionFrm*)pLow)->GetSection() )
/*N*/               bChanged |= FormatLayout( (SwLayoutFrm*)pLow, bAddRect );
/*N*/       }
/*N*/       else if ( pImp->GetShell()->IsPaintLocked() )
/*N*/           //Abkuerzung im die Zyklen zu minimieren, bei Lock kommt das
/*N*/           //Paint sowieso (Primaer fuer Browse)
/*N*/           pLow->OptCalc();
/*N*/
/*N*/       if ( IsAgain() )
/*N*/           return FALSE;
/*N*/       pLow = pLow->GetNext();
/*N*/   }
/*N*/     // add complete frame area as paint area, if frame area has been
/*N*/     // already added and after formating its lowers the frame area
/*N*/     // is enlarged.
/*N*/     if ( bAlreadyPainted &&
/*N*/          ( pLay->Frm().Width() > aFrmAtCompletePaint.Width() ||
/*N*/            pLay->Frm().Height() > aFrmAtCompletePaint.Height() )
/*N*/        )
/*N*/     {
/*N*/         pImp->GetShell()->AddPaintRect( pLay->Frm() );
/*N*/     }
/*N*/     return bChanged || bTabChanged;
/*N*/ }

/*N*/ BOOL SwLayAction::FormatLayoutFly( SwFlyFrm *pFly, BOOL bAddRect )
/*N*/ {
/*N*/   OSL_ENSURE( !IsAgain(), "Ungueltige Seite beachten." );
/*N*/   if ( IsAgain() )
/*?*/       return FALSE;
/*N*/
/*N*/   BOOL bChanged = FALSE;
/*N*/
/*N*/   if ( !pFly->IsValid() || pFly->IsCompletePaint() || pFly->IsInvalid() )
/*N*/   {
/*N*/       //Der Frame hat sich veraendert, er wird jetzt Formatiert
/*N*/       const SwRect aOldRect( pFly->Frm() );
/*N*/       pFly->Calc();
/*N*/       bChanged = aOldRect != pFly->Frm();
/*N*/
/*N*/       if ( IsPaint() && bAddRect && (pFly->IsCompletePaint() || bChanged) &&
/*N*/            pFly->Frm().Top() > 0 && pFly->Frm().Left() > 0 )
/*N*/           pImp->GetShell()->AddPaintRect( pFly->Frm() );
/*N*/
/*N*/       if ( bChanged )
/*N*/           pFly->Invalidate();
/*N*/       else
/*N*/           pFly->Validate();
/*N*/       bAddRect = FALSE;
/*N*/       pFly->ResetCompletePaint();
/*N*/   }
/*N*/
/*N*/   if ( IsAgain() )
/*?*/       return FALSE;
/*N*/
/*N*/   //Jetzt noch diejenigen Lowers versorgen die LayoutFrm's sind
/*N*/   BOOL bTabChanged = FALSE;
/*N*/   SwFrm *pLow = pFly->Lower();
/*N*/   while ( pLow )
/*N*/   {
/*N*/       if ( pLow->IsLayoutFrm() )
/*N*/       {
/*N*/           if ( pLow->IsTabFrm() )
/*N*/               bTabChanged |= FormatLayoutTab( (SwTabFrm*)pLow, bAddRect );
/*N*/           else
/*N*/               bChanged |= FormatLayout( (SwLayoutFrm*)pLow, bAddRect );
/*N*/       }
/*N*/       pLow = pLow->GetNext();
/*N*/   }
/*N*/   return bChanged || bTabChanged;
/*N*/ }

/*N*/ BOOL MA_FASTCALL lcl_AreLowersScrollable( const SwLayoutFrm *pLay )
/*N*/ {
/*N*/   const SwFrm *pLow = pLay->Lower();
/*N*/   while ( pLow )
/*N*/   {
/*N*/       if ( pLow->IsCompletePaint() || !pLow->IsValid() )
/*N*/           return FALSE;
/*N*/       if ( pLow->IsLayoutFrm() && !::binfilter::lcl_AreLowersScrollable( (SwLayoutFrm*)pLow ))
/*N*/           return FALSE;
/*N*/       pLow = pLow->GetNext();
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ SwLayoutFrm * MA_FASTCALL lcl_IsTabScrollable( SwTabFrm *pTab )
/*N*/ {
/*N*/   //returnt die erste unveraenderte Zeile, oder 0 wenn nicht
/*N*/   //gescrollt werden darf.
/*N*/   if ( !pTab->IsCompletePaint() )
/*N*/   {
/*N*/       SwLayoutFrm *pUnchgdRow = 0;
/*N*/       SwLayoutFrm *pRow = (SwLayoutFrm*)pTab->Lower();
/*N*/       while ( pRow )
/*N*/       {
/*N*/           if ( !::binfilter::lcl_AreLowersScrollable( pRow ) )
/*N*/               pUnchgdRow = 0;
/*N*/           else if ( !pUnchgdRow )
/*N*/               pUnchgdRow = pRow;
/*N*/           pRow = (SwLayoutFrm*)pRow->GetNext();
/*N*/       }
/*N*/       return pUnchgdRow;
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ void MA_FASTCALL lcl_ValidateLowers( SwLayoutFrm *pLay, const SwTwips nOfst,
/*N*/                       SwLayoutFrm *pRow, SwPageFrm *pPage,
/*N*/                       BOOL bResetOnly )
/*N*/ {
/*N*/   pLay->ResetCompletePaint();
/*N*/   SwFrm *pLow = pLay->Lower();
/*N*/   if ( pRow )
/*N*/       while ( pLow != pRow )
/*N*/           pLow = pLow->GetNext();
/*N*/
/*N*/   while ( pLow )
/*N*/   {
/*N*/       if ( !bResetOnly )
/*N*/       {
/*N*/           SwRect aOldFrm( pLow->Frm() );
/*N*/           pLow->Frm().Pos().Y() += nOfst;
/*N*/       }
/*N*/       if ( pLow->IsLayoutFrm() )
/*N*/       {
/*N*/           ::binfilter::lcl_ValidateLowers( (SwLayoutFrm*)pLow, nOfst, 0, pPage, bResetOnly);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pLow->ResetCompletePaint();
/*N*/           if ( pLow->GetDrawObjs() )
/*N*/           {
/*N*/               for ( USHORT i = 0; i < pLow->GetDrawObjs()->Count(); ++i )
/*N*/               {
/*N*/                   SdrObject *pO = (*pLow->GetDrawObjs())[i];
/*N*/                   if ( pO->IsWriterFlyFrame() )
/*N*/                   {
/*N*/                       SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/                       if ( !bResetOnly )
/*N*/                       {
/*N*/                           pFly->Frm().Pos().Y() += nOfst;
/*N*/                             pFly->GetVirtDrawObj()->_SetRectsDirty();
/*N*/                           if ( pFly->IsFlyInCntFrm() )
/*N*/                               ((SwFlyInCntFrm*)pFly)->AddRefOfst( nOfst );
/*N*/                       }
/*N*/                       ::binfilter::lcl_ValidateLowers( pFly, nOfst, 0, pPage, bResetOnly);
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                         // consider 'virtual' drawing objects.
/*N*/                         if ( pO->ISA(SwDrawVirtObj) )
/*N*/                         {
/*N*/                             SwDrawVirtObj* pDrawVirtObj = static_cast<SwDrawVirtObj*>(pO);
/*N*/                             pDrawVirtObj->SetAnchorPos( pLow->GetFrmAnchorPos( ::binfilter::HasWrap( pO ) ) );
/*N*/                             pDrawVirtObj->AdjustRelativePosToReference();
/*N*/                         }
/*N*/                         else
/*N*/                         {
/*N*/                             pO->SetAnchorPos( pLow->GetFrmAnchorPos( ::binfilter::HasWrap( pO ) ) );
/*N*/                             SwFrmFmt *pFrmFmt = FindFrmFmt( pO );
/*N*/                             if( !pFrmFmt ||
/*N*/                                 FLY_IN_CNTNT != pFrmFmt->GetAnchor().GetAnchorId() )
/*N*/                             {
/*N*/                                 ((SwDrawContact*)pO->GetUserCall())->ChkPage();
/*N*/                             }
/*N*/                             // correct relative position
/*N*/                             // of 'virtual' drawing objects.
/*N*/                             SwDrawContact* pDrawContact =
/*N*/                                 static_cast<SwDrawContact*>(pO->GetUserCall());
/*N*/                             if ( pDrawContact )
/*N*/                             {
/*N*/                                 pDrawContact->CorrectRelativePosOfVirtObjs();
/*N*/                             }
/*N*/                         }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       if ( !bResetOnly )
/*N*/           pLow->Calc();           //#55435# Stabil halten.
/*N*/       pLow = pLow->GetNext();
/*N*/   }
/*N*/ }

/*N*/ void MA_FASTCALL lcl_AddScrollRectTab( SwTabFrm *pTab, SwLayoutFrm *pRow,
/*N*/                              const SwRect &rRect,
/*N*/                              const SwTwips nOfst)
/*N*/ {
/*N*/   //Wenn altes oder neues Rechteck mit einem Fly ueberlappen, in dem der
/*N*/   //Frm nicht selbst steht, so ist nichts mit Scrollen.
/*N*/   const SwPageFrm *pPage = pTab->FindPageFrm();
/*N*/   SwRect aRect( rRect );
/*N*/     // <SWRECTFN( pTab )> not needed.
/*N*/     if( pTab->IsVertical() )
/*?*/         aRect.Pos().X() -= nOfst;
/*N*/     else
/*N*/   aRect.Pos().Y() += nOfst;
/*N*/   if ( pPage->GetSortedObjs() )
/*N*/   {
/*N*/       if ( ::binfilter::lcl_IsOverObj( pTab, pPage, rRect, aRect, pTab ) )
/*N*/           return;
/*N*/   }
/*N*/   if ( pPage->GetFmt()->GetBackground().GetGraphicPos() != GPOS_NONE )
/*?*/       return;
/*N*/
/*N*/   ViewShell *pSh = pPage->GetShell();
/*N*/   if ( pSh )
/*N*/       pSh->AddScrollRect( pTab, aRect, nOfst );
/*N*/   ::binfilter::lcl_ValidateLowers( pTab, nOfst, pRow, pTab->FindPageFrm(),
/*N*/                                               pTab->IsLowersFormatted() );
/*N*/ }

// NOTE: no adjustments for vertical layout support necessary
/*N*/ BOOL CheckPos( SwFrm* /*pFrm*/ )
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/   return TRUE;
/*N*/ }

// Implement vertical layout support
/*N*/ BOOL SwLayAction::FormatLayoutTab( SwTabFrm *pTab, BOOL bAddRect )
/*N*/ {
/*N*/   OSL_ENSURE( !IsAgain(), "8-) Ungueltige Seite beachten." );
/*N*/   if ( IsAgain() )
/*?*/       return FALSE;
/*N*/
/*N*/   SwDoc* pDoc = pRoot->GetFmt()->GetDoc();
/*N*/   const BOOL bOldIdle = pDoc->IsIdleTimerActive();
/*N*/   pDoc->StopIdleTimer();
/*N*/
/*N*/     BOOL bChanged = FALSE;
/*N*/   bool bPainted = FALSE;
/*N*/
/*N*/   const SwPageFrm *pOldPage = pTab->FindPageFrm();
/*N*/
/*N*/     // vertical layout support
/*N*/     // use macro to declare and init <sal_Bool bVert>, <sal_Bool bRev> and
/*N*/     // <SwRectFn fnRect> for table frame <pTab>.
/*N*/     SWRECTFN( pTab );
/*N*/
/*N*/   if ( !pTab->IsValid() || pTab->IsCompletePaint() || pTab->IsComplete() )
/*N*/   {
/*N*/       if ( pTab->GetPrev() && !pTab->GetPrev()->IsValid() )
/*N*/           pTab->GetPrev()->SetCompletePaint();
/*N*/
/*N*/       //Potenzielles Scrollrect ist die ganze Tabelle. Da bereits ein
/*N*/       //Wachstum innerhalb der Tabelle - und damit der Tabelle selbst -
/*N*/       //stattgefunden haben kann, muss die untere Kante durch die
/*N*/       //Unterkante der letzten Zeile bestimmt werden.
/*N*/       SwLayoutFrm *pRow = NULL;
/*N*/       SwRect aScrollRect( pTab->PaintArea() );
/*N*/       if ( IsPaint() || bAddRect )
/*N*/       {
/*N*/           pRow = (SwLayoutFrm*)pTab->Lower();
/*N*/           while ( pRow->GetNext() )
/*N*/               pRow = (SwLayoutFrm*)pRow->GetNext();
/*N*/             // vertical layout support
/*N*/             (aScrollRect.*fnRect->fnSetBottom)( (pRow->Frm().*fnRect->fnGetBottom)() );
/*N*/           //Die Oberkante wird ggf. durch die erste unveraenderte Zeile bestimmt.
/*N*/           pRow = ::binfilter::lcl_IsTabScrollable( pTab );
/*N*/           if ( pRow && pRow != pTab->Lower() )
/*N*/                 // vertical layout support
/*N*/                 (aScrollRect.*fnRect->fnSetTop)( (pRow->Frm().*fnRect->fnGetTop)() );
/*N*/       }
/*N*/
/*N*/       const SwFrm *pOldUp = pTab->GetUpper();
/*N*/
/*N*/       SwRect aOldRect( pTab->Frm() );
/*N*/       pTab->SetLowersFormatted( FALSE );
/*N*/       pTab->Calc();
/*N*/       if ( aOldRect != pTab->Frm() )
/*N*/           bChanged = TRUE;
/*N*/       SwRect aPaintFrm = pTab->PaintArea();
/*N*/
/*N*/       if ( IsPaint() && bAddRect )
/*N*/       {
/*N*/           if ( pRow && pOldUp == pTab->GetUpper() &&
/*N*/                pTab->Frm().SSize() == aOldRect.SSize() &&
/*N*/                  // vertical layout support
/*N*/                  (pTab->Frm().*fnRect->fnGetLeft)() == (aOldRect.*fnRect->fnGetLeft)() &&
/*N*/                pTab->IsAnLower( pRow ) )
/*N*/           {
/*N*/               SwTwips nOfst;
/*N*/               if ( pRow->GetPrev() )
/*N*/               {
/*N*/                   if ( pRow->GetPrev()->IsValid() ||
/*N*/                        ::binfilter::CheckPos( pRow->GetPrev() ) )
/*N*/                     {
/*N*/                         // vertical layout support
/*N*/                         nOfst = -(pRow->Frm().*fnRect->fnTopDist)( (pRow->GetPrev()->Frm().*fnRect->fnGetBottom)() );
/*N*/                   }
/*N*/               else
/*N*/                       nOfst = 0;
/*N*/               }
/*N*/               else
/*N*/                     // vertical layout support
/*N*/                     nOfst = (pTab->Frm().*fnRect->fnTopDist)( (aOldRect.*fnRect->fnGetTop)() );
/*N*/
/*N*/               if ( nOfst )
/*N*/               {
/*N*/                    ::binfilter::lcl_AddScrollRectTab( pTab, pRow, aScrollRect, nOfst );
/*N*/                    bPainted = TRUE;
/*N*/               }
/*N*/           }
/*N*/
/*N*/             // add condition <pTab->Frm().HasArea()>
/*N*/             if ( !pTab->IsCompletePaint() && pTab->IsComplete() &&
/*N*/                ( pTab->Frm().SSize() != pTab->Prt().SSize() ||
/*N*/                    // vertical layout support
/*N*/                    (pTab->*fnRect->fnGetLeftMargin)()
/*N*/                  ) &&
/*N*/                  pTab->Frm().HasArea()
/*N*/                )
/*N*/           {
/*N*/                 // re-implement calculation of margin rectangles.
/*N*/                 SwRect aMarginRect;
/*N*/
/*N*/                 SwTwips nLeftMargin = (pTab->*fnRect->fnGetLeftMargin)();
/*N*/                 if ( nLeftMargin > 0)
/*N*/                 {
/*N*/                     aMarginRect = pTab->Frm();
/*N*/                     (aMarginRect.*fnRect->fnSetWidth)( nLeftMargin );
/*N*/                     pImp->GetShell()->AddPaintRect( aMarginRect );
/*N*/                 }
/*N*/
/*N*/                 if ( (pTab->*fnRect->fnGetRightMargin)() > 0)
/*N*/                 {
/*N*/                     aMarginRect = pTab->Frm();
/*N*/                     (aMarginRect.*fnRect->fnSetLeft)( (pTab->*fnRect->fnGetPrtRight)() );
/*N*/                     pImp->GetShell()->AddPaintRect( aMarginRect );
/*N*/                 }
/*N*/
/*N*/                 SwTwips nTopMargin = (pTab->*fnRect->fnGetTopMargin)();
/*N*/                 if ( nTopMargin > 0)
/*N*/                 {
/*N*/                     aMarginRect = pTab->Frm();
/*N*/                     (aMarginRect.*fnRect->fnSetHeight)( nTopMargin );
/*N*/                     pImp->GetShell()->AddPaintRect( aMarginRect );
/*N*/                 }
/*N*/
/*N*/                 if ( (pTab->*fnRect->fnGetBottomMargin)() > 0)
/*N*/                 {
/*N*/                     aMarginRect = pTab->Frm();
/*N*/                     (aMarginRect.*fnRect->fnSetTop)( (pTab->*fnRect->fnGetPrtBottom)() );
/*N*/                     pImp->GetShell()->AddPaintRect( aMarginRect );
/*N*/                 }
/*N*/           }
/*N*/           else if ( pTab->IsCompletePaint() )
/*N*/           {
/*N*/               pImp->GetShell()->AddPaintRect( aPaintFrm );
/*N*/               bAddRect = FALSE;
/*N*/               bPainted = TRUE;
/*N*/           }
/*N*/
/*N*/             if ( pTab->IsRetouche() && !pTab->GetNext() )
/*N*/           {
/*N*/               SwRect aRect( pTab->GetUpper()->PaintArea() );
/*N*/                 // vertical layout support
/*N*/                 (aRect.*fnRect->fnSetTop)( (pTab->*fnRect->fnGetPrtBottom)() );
/*N*/                 if ( !pImp->GetShell()->AddPaintRect( aRect ) )
/*N*/                   pTab->ResetRetouche();
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           bAddRect = FALSE;
/*N*/
/*N*/         if ( pTab->IsCompletePaint() && !pOptTab )
/*N*/           pOptTab = pTab;
/*N*/       pTab->ResetCompletePaint();
/*N*/   }
/*N*/   if ( IsPaint() && bAddRect && pTab->IsRetouche() && !pTab->GetNext() )
/*N*/   {
/*N*/         // set correct rectangle for retouche: area between bottom of table frame
/*N*/         // and bottom of paint area of the upper frame.
/*N*/         SwRect aRect( pTab->GetUpper()->PaintArea() );
/*N*/         // vertical layout support
/*N*/         (aRect.*fnRect->fnSetTop)( (pTab->*fnRect->fnGetPrtBottom)() );
/*N*/       if ( !pImp->GetShell()->AddPaintRect( aRect ) )
/*N*/           pTab->ResetRetouche();
/*N*/   }
/*N*/
/*N*/   CheckWaitCrsr();
/*N*/
/*N*/   if ( bOldIdle )
/*N*/       pDoc->StartIdleTimer();
/*N*/
/*N*/   //Heftige Abkuerzung!
/*N*/   if ( pTab->IsLowersFormatted() &&
/*N*/          (bPainted || !pImp->GetShell()->VisArea().IsOver( pTab->Frm())) )
/*N*/       return FALSE;
/*N*/
/*N*/   //Jetzt noch die Lowers versorgen
/*N*/   if ( IsAgain() )
/*N*/       return FALSE;
/*N*/   SwLayoutFrm *pLow = (SwLayoutFrm*)pTab->Lower();
/*N*/   while ( pLow )
/*N*/   {
/*N*/       bChanged |= FormatLayout( (SwLayoutFrm*)pLow, bAddRect );
/*N*/       if ( IsAgain() )
/*N*/           return FALSE;
/*N*/       pLow = (SwLayoutFrm*)pLow->GetNext();
/*N*/   }
/*N*/
/*N*/   if ( pOldPage->GetPhyPageNum() > (pTab->FindPageFrm()->GetPhyPageNum() + 1) )
/*N*/       SetNextCycle( TRUE );
/*N*/
/*N*/   return bChanged;
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::FormatFlyInCnt()
|*
|*  Beschreibung        Da die Flys im Cntnt nix mit der Seite am Hut
|*      (bzw. in den Bits ;-)) haben werden sie vom Cntnt (FormatCntnt)
|*      gerufen und hier verarbeitet. Die Verarebeitungsmimik ist
|*      prinzipiell die gleich wie bei Seiten nur nicht ganz so
|*      kompliziert (SwLayAction::Action()).
|*      - Returnt TRUE wenn der Fly vollstaendig verbeitet wurde, FALSE bei
|*        einem vorzeitigen Abbruch.
|*
|*************************************************************************/
/*N*/ void SwLayAction::FormatFlyInCnt( SwFlyInCntFrm *pFly )
/*N*/ {
/*N*/     if ( IsAgain() )
/*?*/         return;
/*N*/   //Wg. Aenderung eine kleine Vorsichtsmassnahme. Es wird jetzt vor der
/*N*/   //Cntntformatierung das Flag validiert und wenn die Formatierung mit
/*N*/   //FALSE returnt wird halt wieder invalidiert.
/*N*/   while ( pFly->IsInvalid() )
/*N*/   {
/*N*/       if ( pFly->IsInvalidLayout() )
/*N*/       {
/*N*/           while ( FormatLayoutFly( pFly ) )
/*N*/           {
/*N*/               if ( IsAgain() )
/*?*/                   return;
/*N*/           }
/*N*/           if ( IsAgain() )
/*?*/               return;
/*N*/           pFly->ValidateLayout();
/*N*/       }
/*N*/       if ( pFly->IsInvalidCntnt() )
/*N*/       {
/*N*/           pFly->ValidateCntnt();
/*N*/           if ( !_FormatFlyCntnt( pFly ) )
/*?*/               pFly->InvalidateCntnt();
/*N*/       }
/*N*/   }
/*N*/   CheckWaitCrsr();
/*N*/ }
/*************************************************************************
|*
|*  SwLayAction::_FormatFlyCntnt()
|*
|*  Beschreibung:
|*      - Returnt TRUE wenn alle Cntnts des Flys vollstaendig verarbeitet
|*        wurden. FALSE wenn vorzeitig unterbrochen wurde.
|*
|*************************************************************************/
/*N*/ BOOL SwLayAction::_FormatFlyCntnt( const SwFlyFrm *pFly )
/*N*/ {
/*N*/   BOOL bOneProcessed = FALSE;
/*N*/   const SwCntntFrm *pCntnt = pFly->ContainsCntnt();
/*N*/
/*N*/   while ( pCntnt )
/*N*/   {
/*N*/       if ( __FormatFlyCntnt( pCntnt ) )
/*N*/           bOneProcessed = TRUE;
/*N*/
/*N*/       if ( !pCntnt->GetValidLineNumFlag() && pCntnt->IsTxtFrm() )
/*N*/       {
/*N*/           const ULONG nAllLines = ((SwTxtFrm*)pCntnt)->GetAllLines();
/*N*/           ((SwTxtFrm*)pCntnt)->RecalcAllLines();
/*N*/           if ( IsPaintExtraData() && IsPaint() &&
/*N*/                nAllLines != ((SwTxtFrm*)pCntnt)->GetAllLines() )
/*?*/               pImp->GetShell()->AddPaintRect( pCntnt->Frm() );
/*N*/       }
/*N*/
/*N*/       if ( IsAgain() )
/*N*/           return FALSE;
/*N*/
/*N*/       //wenn eine Eingabe anliegt breche ich die Verarbeitung ab.
/*N*/       if ( bOneProcessed && !pFly->IsFlyInCntFrm() )
/*N*/       {
/*N*/           CheckIdleEnd();
/*N*/             // consider interrupt formatting.
/*N*/             if ( IsInterrupt() && !mbFormatCntntOnInterrupt )
/*N*/               return FALSE;
/*N*/       }
/*N*/       pCntnt = pCntnt->GetNextCntntFrm();
/*N*/   }
/*N*/   CheckWaitCrsr();
/*N*/     // consider interrupt formatting.
/*N*/     return !(IsInterrupt() && !mbFormatCntntOnInterrupt);
/*N*/ }

/*************************************************************************
|*
|*  SwLayAction::__FormatFlyCntnt()
|*
|*  Beschreibung:
|*      - Returnt TRUE, wenn der Cntnt verarbeitet,
|*        d.h. Kalkuliert und/oder gepaintet wurde.
|*
|*************************************************************************/
/*N*/ BOOL SwLayAction::__FormatFlyCntnt( const SwCntntFrm *pCntnt )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   if ( !pCntnt->IsValid() || pCntnt->IsCompletePaint() ||
/*N*/        pCntnt->IsRetouche() )
/*N*/   {
/*N*/       if ( IsPaint() )
/*N*/       {
/*N*/           const SwRect aOldRect( pCntnt->UnionFrm( TRUE ) );
/*N*/           const long   nOldBottom = pCntnt->Frm().Top() + pCntnt->Prt().Bottom();
/*N*/           pCntnt->OptCalc();
/*N*/           if ( pCntnt->Frm().Bottom() <  aOldRect.Bottom() )
/*N*/               pCntnt->SetRetouche();
/*N*/           PaintCntnt( pCntnt, pCntnt->FindPageFrm(), aOldRect, nOldBottom );
/*N*/       }
/*N*/       else
/*N*/           pCntnt->OptCalc();
/*N*/       if( IsAgain() )
/*N*/           return FALSE;
/*N*/       bRet = TRUE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //Falls der Frm schon vor der Abarbeitung hier formatiert wurde.
/*N*/       if ( pCntnt->IsTxtFrm() && ((SwTxtFrm*)pCntnt)->HasRepaint() &&
/*N*/            IsPaint() )
/*N*/           PaintCntnt( pCntnt, pCntnt->FindPageFrm(), pCntnt->Frm(), pCntnt->Frm().Bottom());
/*N*/   }
/*N*/   //Die im Absatz verankerten Flys wollen auch mitspielen.
/*N*/   if ( pCntnt->GetDrawObjs() )
/*N*/   {
/*N*/       const SwDrawObjs *pObjs = pCntnt->GetDrawObjs();
/*N*/       for ( USHORT i = 0; i < pObjs->Count(); ++i )
/*N*/       {
/*N*/           SdrObject *pO = (*pObjs)[i];
/*N*/           if ( pO->IsWriterFlyFrame() )
/*N*/           {
/*N*/               SwFlyFrm* pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/               if ( pFly->IsFlyInCntFrm() && ((SwFlyInCntFrm*)pFly)->IsInvalid() )
/*N*/               {
/*N*/                   FormatFlyInCnt( (SwFlyInCntFrm*)pFly );
/*N*/                   if ( IsAgain() )
/*N*/                       return FALSE;
/*N*/                   pObjs = pCntnt->GetDrawObjs();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL SwLayAction::IsStopPrt() const
/*N*/ {
/*N*/   BOOL bResult = FALSE;
/*N*/
/*N*/   if (pImp != NULL && pProgress != NULL)
/*N*/       bResult = pImp->IsStopPrt();
/*N*/
/*N*/   return bResult;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
