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

#define _SVX_PARAITEM_HXX
#define _SVX_TEXTITEM_HXX

#include <bf_sfx2/progress.hxx>
#include <swwait.hxx>

#include <horiornt.hxx>

#include <fesh.hxx>
#include <doc.hxx>
#include <rootfrm.hxx>
#include <pagefrm.hxx>
#include <viewimp.hxx>
#include <frmtool.hxx>
#include <viewopt.hxx>
#include <dview.hxx>
#include <swregion.hxx>
#include <hints.hxx>
#include <txtfrm.hxx>
#include <layact.hxx>
#include <mdiexp.hxx>
#include <fntcache.hxx>
#include <docsh.hxx>
#include <pagedesc.hxx>
#include <accessibilityoptions.hxx>
#include <statstr.hrc>
#include <shellres.hxx>
namespace binfilter {

BOOL ViewShell::bLstAct = FALSE;
ShellResource *ViewShell::pShellRes = 0;
Window *ViewShell::pCareWindow = 0;

bool bInSizeNotify = FALSE;

/*N*/ TYPEINIT0(ViewShell);

/******************************************************************************
|*
|*  ViewShell::ImplEndAction()
|*
******************************************************************************/

/*N*/ void ViewShell::ImplEndAction( const BOOL bIdleEnd )
/*N*/ {
/*N*/   //Fuer den Drucker gibt es hier nichts zu tun.
/*N*/   if ( !GetWin() || IsPreView() )
/*N*/   {
/*?*/       bPaintWorks = TRUE;
/*?*/       UISizeNotify();
/*?*/       return;
/*N*/   }
/*N*/
/*N*/   // #94195# remember when the handles need refresh at end of method
/*N*/   sal_Bool bRefreshMarker(sal_False);
/*N*/
/*N*/   bInEndAction = TRUE;
/*N*/
/*N*/   //Laeuft hiermit das EndAction der Letzten Shell im Ring?
/*N*/   ViewShell::bLstAct = TRUE;
/*N*/   ViewShell *pSh = (ViewShell*)this->GetNext();
/*N*/   while ( pSh != this )
/*?*/   {   if ( pSh->ActionPend() )
/*?*/       {   ViewShell::bLstAct = FALSE;
/*?*/           pSh = this;
/*?*/       }
/*?*/       else
/*?*/           pSh = (ViewShell*)pSh->GetNext();
/*?*/   }
/*N*/
/*N*/   SET_CURR_SHELL( this );
/*N*/   if ( Imp()->HasDrawView() && !Imp()->GetDrawView()->IsMarkHdlHidden() )
/*?*/       Imp()->StartAction();
/*N*/
/*N*/   if ( Imp()->GetRegion() && Imp()->GetRegion()->GetOrigin() != VisArea() )
/*N*/       Imp()->DelRegions();
/*N*/
/*N*/   const bool bExtraData = ::binfilter::IsExtraData( GetDoc() );
/*N*/
/*N*/   if ( !bIdleEnd )
/*N*/   {
/*N*/       if ( Imp()->IsNextScroll() && !bExtraData )
/*N*/           Imp()->SetScroll();
/*N*/       else
/*N*/       {
/*N*/           if ( bExtraData )
/*?*/               Imp()->bScroll = FALSE;
/*N*/           Imp()->SetNextScroll();
/*N*/           Imp()->ResetScroll();
/*N*/       }
/*N*/       SwLayAction aAction( GetLayout(), Imp() );
/*N*/       aAction.SetComplete( FALSE );
/*N*/       if ( nLockPaint )
/*?*/           aAction.SetPaint( FALSE );
/*N*/       aAction.SetInputType( INPUT_KEYBOARD );
/*N*/       aAction.Action();
/*N*/       Imp()->SetScroll();
/*N*/   }
/*N*/
/*N*/   //Wenn wir selbst keine Paints erzeugen, so warten wir auf das Paint
/*N*/   //vom System. Dann ist das Clipping korrekt gesetzt; Beispiel: verschieben
/*N*/   //eines DrawObjektes.
/*N*/   if ( Imp()->GetRegion()     || Imp()->GetScrollRects() ||
/*N*/        aInvalidRect.HasArea() || bExtraData )
/*N*/   {
/*?*/       if ( !nLockPaint )
/*?*/       {
/*?*/           bool bPaintsFromSystem = aInvalidRect.HasArea();
/*?*/           GetWin()->Update();
/*?*/           if ( aInvalidRect.HasArea() )
/*?*/           {
/*?*/               if ( bPaintsFromSystem )
/*?*/                   Imp()->AddPaintRect( aInvalidRect );
/*?*/
/*?*/               // AW 22.09.99: tell DrawView that drawing order will be rearranged
/*?*/               // to give it a chance to react with proper IAO updates
/*?*/               if (HasDrawView())
/*?*/               {
/*?*/               DBG_BF_ASSERT(0, "STRIP");
/*?*/               }
/*?*/
/*?*/               ResetInvalidRect();
/*?*/               bPaintsFromSystem = TRUE;
/*?*/           }
/*?*/           bPaintWorks = TRUE;
/*?*/
/*?*/           SwRegionRects *pRegion = Imp()->GetRegion();
/*?*/
/*?*/           //JP 27.11.97: wer die Selection hided, muss sie aber auch
/*?*/           //              wieder Showen. Sonst gibt es Paintfehler!
/*?*/           //  z.B.: addional Mode, Seite vertikal hab zu sehen, in der
/*?*/           // Mitte eine Selektion und mit einem anderen Cursor an linken
/*?*/           // rechten Rand springen. Ohne ShowCrsr verschwindet die
/*?*/           // Selektion
/*?*/           BOOL bShowCrsr = (pRegion || Imp()->GetScrollRects()) &&
/*?*/                               IsA( TYPE(SwCrsrShell) );
/*?*/           if( bShowCrsr )
/*?*/               {DBG_BF_ASSERT(0, "STRIP");}
/*?*/
/*?*/           Scroll();
/*?*/           if ( bPaintsFromSystem && Imp()->pScrolledArea )
                    {DBG_BF_ASSERT(0, "STRIP");}
/*?*/
/*?*/           if ( pRegion )
                    {DBG_BF_ASSERT(0, "STRIP");}
/*?*/           if( bShowCrsr )
/*?*/               ((SwCrsrShell*)this)->ShowCrsrs( TRUE );
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           Imp()->DelRegions();
/*?*/           bPaintWorks =  TRUE;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/       bPaintWorks = TRUE;
/*N*/
/*N*/   bInEndAction = FALSE;
/*N*/   ViewShell::bLstAct = FALSE;
/*N*/   Imp()->EndAction();
/*N*/
/*N*/
/*N*/   //Damit sich die automatischen Scrollbars auch richtig anordnen k”nnen
/*N*/   //muessen wir die Aktion hier kuenstlich beenden (EndAction loesst ein
/*N*/   //Notify aus, und das muss Start-/EndAction rufen um die  Scrollbars
/*N*/   //klarzubekommen.
/*N*/   --nStartAction;
/*N*/   UISizeNotify();
/*N*/   ++nStartAction;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   // No Scroll starts the timer to repair the scrolled area automatically
/*N*/   if( GetViewOptions()->IsTest8() )
/*N*/ #endif
/*?*/   if ( Imp()->IsScrolled() )
/*?*/       Imp()->RestartScrollTimer();
/*N*/
/*N*/   // #94195# refresh handles when they were hard removed for display change
/*N*/   if(bRefreshMarker && HasDrawView())
/*N*/   {
/*?*/       GetDrawView()->AdjustMarkHdl(FALSE);
/*N*/   }
/*N*/
/*N*/ #ifdef ACCESSIBLE_LAYOUT
/*N*/ #endif
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::ImplStartAction()
|*
******************************************************************************/

/*N*/ void ViewShell::ImplStartAction()
/*N*/ {
/*N*/   bPaintWorks = FALSE;
/*N*/   Imp()->StartAction();
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::AddPaintRect()
|*
******************************************************************************/

/*N*/ BOOL ViewShell::AddPaintRect( const SwRect & rRect )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {
/*N*/       if ( pSh->IsPreView() && pSh->GetWin() )
/*N*/ //            pSh->GetWin()->Invalidate();
/*?*/           DBG_BF_ASSERT(0, "STRIP");//::binfilter::RepaintPagePreview( pSh, rRect );
/*N*/       else
/*N*/           bRet |= pSh->Imp()->AddPaintRect( rRect );
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/   return bRet;
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::InvalidateWindows()
|*
******************************************************************************/

/*N*/ void ViewShell::InvalidateWindows( const SwRect &rRect )
/*N*/ {
/*N*/   if ( !Imp()->IsCalcLayoutProgress() )
/*N*/   {
/*N*/       ViewShell *pSh = this;
/*N*/       do
/*N*/       {
/*N*/           if ( pSh->GetWin() )
/*N*/           {
/*N*/               if ( pSh->IsPreView() )
/*N*/ //                    pSh->GetWin()->Invalidate();
/*?*/                   DBG_BF_ASSERT(0, "STRIP");//::binfilter::RepaintPagePreview( pSh, rRect );
/*N*/               else if ( pSh->VisArea().IsOver( rRect ) )
/*N*/                   pSh->GetWin()->Invalidate( rRect.SVRect() );
/*N*/           }
/*N*/           pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/       } while ( pSh != this );
/*N*/   }
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::MakeVisible()
|*
******************************************************************************/

/*N*/ void ViewShell::MakeVisible( const SwRect &rRect )
/*N*/ {
/*N*/   if ( !VisArea().IsInside( rRect ) || /*IsScrollMDI( this, rRect ) ||*/ GetCareWin(*this) )
/*N*/   {
/*N*/       if ( !IsViewLocked() )
/*N*/       {
/*N*/           if( pWin )
/*N*/           {
/*N*/               const SwFrm* pRoot = GetDoc()->GetRootFrm();
/*N*/               int nLoopCnt = 3;
/*N*/               long nOldH;
/*N*/               do{
/*N*/                   nOldH = pRoot->Frm().Height();
/*N*/                   StartAction();
/*N*/                   DBG_BF_ASSERT(0, "STRIP");//ScrollMDI( this, rRect, USHRT_MAX, USHRT_MAX );
/*N*/                   EndAction();
/*N*/               } while( nOldH != pRoot->Frm().Height() && nLoopCnt-- );
/*N*/           }
/*N*/ #ifdef DBG_UTIL
/*N*/           else
/*N*/           {
/*N*/               //MA: 04. Nov. 94, braucht doch keiner oder??
/*N*/               OSL_ENSURE( !this, "MakeVisible fuer Drucker wird doch gebraucht?" );
/*N*/           }
/*N*/
/*N*/ #endif
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ViewShell::Reformat()
/*N*/ {
/*N*/   // Wir gehen auf Nummer sicher:
/*N*/   // Wir muessen die alten Fontinformationen wegschmeissen,
/*N*/   // wenn die Druckeraufloesung oder der Zoomfaktor sich aendert.
/*N*/   // Init() und Reformat() sind die sichersten Stellen.
/*N*/ #ifdef FNTMET
/*N*/   aFntMetList.Flush();
/*N*/ #else
/*N*/   pFntCache->Flush( );
/*N*/ #endif
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::CalcLayout()
|*                  Vollstaendige Formatierung von Layout und Inhalt.
|*
******************************************************************************/

/*N*/ void ViewShell::CalcLayout()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/
/*N*/   //Cache vorbereiten und restaurieren, damit er nicht versaut wird.
/*N*/   SwSaveSetLRUOfst aSaveLRU( *SwTxtFrm::GetTxtCache(),
/*N*/                               SwTxtFrm::GetTxtCache()->GetCurMax() - 50 );
/*N*/
/*N*/   SwLayAction aAction( GetLayout(), Imp() );
/*N*/   aAction.SetPaint( FALSE );
/*N*/   aAction.SetCalcLayout( TRUE );
/*N*/   aAction.SetReschedule( TRUE );
/*N*/   GetDoc()->LockExpFlds();
/*N*/   aAction.Action();
/*N*/   GetDoc()->UnlockExpFlds();
/*N*/
/*N*/   //Das SetNewFldLst() am Doc wurde unterbunden und muss nachgeholt
/*N*/   //werden (siehe flowfrm.cxx, txtfld.cxx)
/*N*/   if ( aAction.IsExpFlds() )
/*N*/   {
/*N*/       aAction.Reset();
/*N*/       aAction.SetPaint( FALSE );
/*N*/       aAction.SetReschedule( TRUE );
/*N*/
/*N*/       SwDocPosUpdate aMsgHnt( 0 );
/*N*/       GetDoc()->UpdatePageFlds( &aMsgHnt );
/*N*/       GetDoc()->UpdateExpFlds();
/*N*/
/*N*/       aAction.Action();
/*N*/   }
/*N*/
/*N*/   if ( VisArea().HasArea() )
/*N*/       InvalidateWindows( VisArea() );
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::SetFirstVisPageInvalid()
|*
******************************************************************************/

/*N*/ void ViewShell::SetFirstVisPageInvalid()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {   pSh->Imp()->SetFirstVisPageInvalid();
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::SizeChgNotify()
|*
******************************************************************************/

/*N*/ void ViewShell::SizeChgNotify(const Size &)
/*N*/ {
/*N*/   if ( !pWin )
/*N*/       bDocSizeChgd = TRUE;
/*N*/   else if( ActionPend() || Imp()->IsCalcLayoutProgress() || bPaintInProgress )
/*N*/   {
/*N*/       bDocSizeChgd = TRUE;
/*N*/
/*N*/       if ( !Imp()->IsCalcLayoutProgress() && ISA( SwCrsrShell ) )
/*N*/       {
/*N*/           const SwFrm *pCnt = ((SwCrsrShell*)this)->GetCurrFrm( FALSE );
/*N*/           const SwPageFrm *pPage;
/*N*/           if ( pCnt && 0 != (pPage = pCnt->FindPageFrm()) )
/*N*/           {
/*N*/               USHORT nVirtNum = pPage->GetVirtPageNum();
/*N*/               const SvxNumberType& rNum = pPage->GetPageDesc()->GetNumType();
/*N*/               String sDisplay = rNum.GetNumStr( nVirtNum );
/*N*/               DBG_BF_ASSERT(0, "STRIP");//PageNumNotify( this, pCnt->GetPhyPageNum(), nVirtNum, sDisplay );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       bDocSizeChgd = FALSE;
/*N*/       DBG_BF_ASSERT(0, "STRIP");//::binfilter::SizeNotify( this, GetLayout()->Frm().SSize() );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*    ViewShell::GetLayout()
|*
*************************************************************************/

/*N*/ SwRootFrm *ViewShell::GetLayout() const
/*N*/ {
/*N*/   return GetDoc()->GetRootFrm();
/*N*/ }

/*N*/ OutputDevice& ViewShell::GetRefDev() const
/*N*/ {
/*N*/     OutputDevice* pTmpOut = 0;
/*N*/     if ( GetWin() && IsBrowseMode() &&
/*N*/          ! GetViewOptions()->IsPrtFormat() )
/*N*/         pTmpOut = GetWin();
/*N*/     else if ( 0 != mpTmpRef )
/*N*/         pTmpOut = mpTmpRef;
/*N*/     else
/*N*/         pTmpOut = &GetDoc()->GetRefDev();
/*N*/
/*N*/     return *pTmpOut;
/*N*/ }

/*N*/ void ViewShell::DrawSelChanged(SdrView*)
/*N*/ {
/*N*/ }


/******************************************************************************
|*
|*  ViewShell::UISizeNotify()
|*
******************************************************************************/


/*N*/ void ViewShell::UISizeNotify()
/*N*/ {
/*N*/   if ( bDocSizeChgd )
/*N*/   {
/*N*/       bDocSizeChgd = FALSE;
/*N*/       bool bOld = bInSizeNotify;
/*N*/       bInSizeNotify = TRUE;
/*N*/       DBG_BF_ASSERT(0, "STRIP");//::binfilter::SizeNotify( this, GetLayout()->Frm().SSize() );
/*N*/       bInSizeNotify = bOld;
/*N*/   }
/*N*/ }


/*N*/ BOOL ViewShell::IsBrowseMode() const
/*N*/ {
/*N*/   return GetDoc()->IsBrowseMode();
/*N*/ }

ShellResource* ViewShell::GetShellRes()
{
    if ( !pShellRes )
        pShellRes = new ShellResource();
    return pShellRes;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
