/*************************************************************************
 *
 *  $RCSfile: sw_viewsh.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:24:34 $
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

#define _SVX_PARAITEM_HXX
#define _SVX_TEXTITEM_HXX

#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SVX_SRCHDLG_HXX //autogen
#include <bf_svx/srchdlg.hxx>
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _SFXVIEWSH_HXX
#include <bf_sfx2/viewsh.hxx>
#endif
#ifndef _SHL_HXX
//#include <tools/shl.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
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
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _SWREGION_HXX
#include <swregion.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _FMTFSIZE_HXX
#include <fmtfsize.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _LAYACT_HXX
#include <layact.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
#ifndef _SCRRECT_HXX
#include <scrrect.hxx>      // SwScrollRect, SwScrollRects
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif
#ifndef _PTQUEUE_HXX
#include <ptqueue.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifdef ACCESSIBLE_LAYOUT
#ifndef _ACCMAP_HXX
#include <accmap.hxx>
#endif
#endif
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif
#ifndef _ACCESSIBILITYOPTIONS_HXX
#include <accessibilityoptions.hxx>
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif
// OD 14.01.2003 #103492#
#ifndef _PAGEPREVIEWLAYOUT_HXX
#include <pagepreviewlayout.hxx>
#endif
namespace binfilter {

BOOL ViewShell::bLstAct = FALSE;
ShellResource *ViewShell::pShellRes = 0;
Window *ViewShell::pCareWindow = 0;

FASTBOOL bInSizeNotify = FALSE;

/*N*/ DBG_NAME(LayoutIdle)

/*N*/ TYPEINIT0(ViewShell);

/******************************************************************************
|*
|*  ViewShell::ImplEndAction()
|*
|*  Letzte Aenderung    MA 04. Sep. 96
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
/*N*/   const FASTBOOL bExtraData = ::binfilter::IsExtraData( GetDoc() );
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
/*?*/           FASTBOOL bPaintsFromSystem = aInvalidRect.HasArea();
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
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001  GetDrawView()->ForceInvalidateMarkHandles();
//STRIP001 /*?*/
//STRIP001 /*?*/                    // #94195# set remark
//STRIP001 /*?*/                    bRefreshMarker = sal_True;
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
/*?*/               {DBG_ASSERT(0, "STRIP");} //STRIP001 ((SwCrsrShell*)this)->HideCrsrs();
/*?*/
/*?*/           Scroll();
/*?*/           if ( bPaintsFromSystem && Imp()->pScrolledArea )
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/              Imp()->FlushScrolledArea();
/*?*/
/*?*/           if ( pRegion )
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/          {
//STRIP001 /*?*/                SwRootFrm* pLayout = GetLayout();
//STRIP001 /*?*/
//STRIP001 /*?*/                 Imp()->pRegion = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/                 //Erst Invert dann Compress, niemals andersherum!
//STRIP001 /*?*/                pRegion->Invert();
//STRIP001 /*?*/
//STRIP001 /*?*/                const USHORT nCnt = pRegion->Count();
//STRIP001 /*?*/                pRegion->Compress();
//STRIP001 /*?*/
//STRIP001 /*?*/                VirtualDevice *pVout = 0;
//STRIP001 /*?*/                while ( pRegion->Count() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwRect aRect( (*pRegion)[ pRegion->Count() - 1 ] );
//STRIP001 /*?*/                    pRegion->Remove( pRegion->Count() - 1 );
//STRIP001 /*?*/
//STRIP001 /*?*/                    BOOL bPaint = TRUE;
//STRIP001 /*?*/                    if ( IsEndActionByVirDev() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        //virtuelles device erzeugen und einstellen.
//STRIP001 /*?*/                        if ( !pVout )
//STRIP001 /*?*/                            pVout = new VirtualDevice( *GetOut() );
//STRIP001 /*?*/                        MapMode aMapMode( GetOut()->GetMapMode() );
//STRIP001 /*?*/                        pVout->SetMapMode( aMapMode );
//STRIP001 /*?*/
//STRIP001 /*?*/                        BOOL bSizeOK = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/                        Rectangle aTmp1( aRect.SVRect() );
//STRIP001 /*?*/                        aTmp1 = GetOut()->LogicToPixel( aTmp1 );
//STRIP001 /*?*/                        Rectangle aTmp2( GetOut()->PixelToLogic( aTmp1 ) );
//STRIP001 /*?*/                        if ( aTmp2.Left() > aRect.Left() )
//STRIP001 /*?*/                            aTmp1.Left() = Max( 0L, aTmp1.Left() - 1L );
//STRIP001 /*?*/                        if ( aTmp2.Top() > aRect.Top() )
//STRIP001 /*?*/                            aTmp1.Top() = Max( 0L, aTmp1.Top() - 1L );
//STRIP001 /*?*/                        aTmp1.Right() += 1;
//STRIP001 /*?*/                        aTmp1.Bottom() += 1;
//STRIP001 /*?*/                        aTmp1 = GetOut()->PixelToLogic( aTmp1 );
//STRIP001 /*?*/                        aRect = SwRect( aTmp1 );
//STRIP001 /*?*/
//STRIP001 /*?*/                        const Size aTmp( pVout->GetOutputSize() );
//STRIP001 /*?*/                        if ( aTmp.Height() < aRect.Height() ||
//STRIP001 /*?*/                             aTmp.Width()  < aRect.Width() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            bSizeOK = pVout->SetOutputSize( aRect.SSize() );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        if ( bSizeOK )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            bPaint = FALSE;
//STRIP001 /*?*/                            OutputDevice  *pOld = GetOut();
//STRIP001 /*?*/                            pVout->SetLineColor( pOld->GetLineColor() );
//STRIP001 /*?*/                            pVout->SetFillColor( pOld->GetFillColor() );
//STRIP001 /*?*/                            Point aOrigin( aRect.Pos() );
//STRIP001 /*?*/                            aOrigin.X() = -aOrigin.X(); aOrigin.Y() = -aOrigin.Y();
//STRIP001 /*?*/                            aMapMode.SetOrigin( aOrigin );
//STRIP001 /*?*/                            pVout->SetMapMode( aMapMode );
//STRIP001 /*?*/                            pOut = pVout;
//STRIP001 /*?*/                             if ( bPaintsFromSystem )
//STRIP001 /*?*/                                 PaintDesktop( aRect );
//STRIP001 /*?*/                            pLayout->Paint( aRect );
//STRIP001 /*?*/                            pOld->DrawOutDev( aRect.Pos(), aRect.SSize(),
//STRIP001 /*?*/                                              aRect.Pos(), aRect.SSize(), *pVout );
//STRIP001 /*?*/                            pOut = pOld;
//STRIP001 /*?*/
//STRIP001 /*?*/                            if( !GetViewOptions()->IsReadonly() &&
//STRIP001 /*?*/                                GetViewOptions()->IsControl() )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                Imp()->PaintLayer( pDoc->GetControlsId(), VisArea() );
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    if ( bPaint )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         if ( bPaintsFromSystem )
//STRIP001 /*?*/                             PaintDesktop( aRect );
//STRIP001 /*?*/                        pLayout->Paint( aRect );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                delete pVout;
//STRIP001 /*?*/                 delete pRegion;
//STRIP001 /*?*/                Imp()->DelRegions();
//STRIP001 /*?*/            }
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
/*N*/ #ifndef PRODUCT
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
//STRIP001 /*?*/    if( Imp()->IsAccessible() )
//STRIP001 /*?*/        Imp()->FireAccessibleEvents();
/*N*/ #endif
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::ImplStartAction()
|*
|*  Ersterstellung      MA 25. Jul. 94
|*  Letzte Aenderung    MA 25. Jul. 94
|*
******************************************************************************/

/*N*/ void ViewShell::ImplStartAction()
/*N*/ {
/*N*/   bPaintWorks = FALSE;
/*N*/   Imp()->StartAction();
/*N*/ }


/******************************************************************************
|*
|*  ViewShell::ImplLockPaint(), ImplUnlockPaint()
|*
|*  Ersterstellung      MA 11. Jun. 96
|*  Letzte Aenderung    MA 11. Jun. 96
|*
******************************************************************************/

//STRIP001 void ViewShell::ImplLockPaint()
//STRIP001 {
//STRIP001  if ( GetWin() && GetWin()->IsVisible() )
//STRIP001      GetWin()->EnablePaint( FALSE ); //Auch die Controls abklemmen.
//STRIP001  Imp()->LockPaint();
//STRIP001 }


//STRIP001 void ViewShell::ImplUnlockPaint( BOOL bVirDev )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  if ( GetWin() && GetWin()->IsVisible() )
//STRIP001  {
//STRIP001      if ( (bInSizeNotify || bVirDev ) && VisArea().HasArea() )
//STRIP001      {
//STRIP001          //Refresh mit virtuellem Device um das Flackern zu verhindern.
//STRIP001          VirtualDevice *pVout = new VirtualDevice( *pOut );
//STRIP001          pVout->SetMapMode( pOut->GetMapMode() );
//STRIP001          Size aSize( VisArea().SSize() );
//STRIP001          aSize.Width() += 20;
//STRIP001          aSize.Height()+= 20;
//STRIP001          if( pVout->SetOutputSize( aSize ) )
//STRIP001          {
//STRIP001              GetWin()->EnablePaint( TRUE );
//STRIP001              GetWin()->Validate();
//STRIP001
//STRIP001              Imp()->UnlockPaint();
//STRIP001              pVout->SetLineColor( pOut->GetLineColor() );
//STRIP001              pVout->SetFillColor( pOut->GetFillColor() );
//STRIP001              OutputDevice *pOld = pOut;
//STRIP001              pOut = pVout;
//STRIP001              Paint( VisArea().SVRect() );
//STRIP001              pOut = pOld;
//STRIP001              pOut->DrawOutDev( VisArea().Pos(), aSize,
//STRIP001                                VisArea().Pos(), aSize, *pVout );
//STRIP001              if( GetViewOptions()->IsControl() )
//STRIP001              {
//STRIP001                  Imp()->PaintLayer( pDoc->GetControlsId(), VisArea() );
//STRIP001                  GetWin()->Update();//Damit aktive, transparente Controls auch
//STRIP001                                     //gleich durchkommen
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              Imp()->UnlockPaint();
//STRIP001              GetWin()->EnablePaint( TRUE );
//STRIP001              GetWin()->Invalidate( INVALIDATE_CHILDREN );
//STRIP001          }
//STRIP001          delete pVout;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          Imp()->UnlockPaint();
//STRIP001          GetWin()->EnablePaint( TRUE );
//STRIP001          GetWin()->Invalidate( INVALIDATE_CHILDREN );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      Imp()->UnlockPaint();
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::AddPaintRect()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 09. Feb. 97
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
/*?*/           ::binfilter::RepaintPagePreview( pSh, rRect );
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
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 09. Feb. 97
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
/*?*/                   ::binfilter::RepaintPagePreview( pSh, rRect );
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
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    AMA 10. Okt. 95
|*
******************************************************************************/

/*N*/ void ViewShell::MakeVisible( const SwRect &rRect )
/*N*/ {
/*N*/   if ( !VisArea().IsInside( rRect ) || IsScrollMDI( this, rRect ) || GetCareWin(*this) )
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
/*N*/                   ScrollMDI( this, rRect, USHRT_MAX, USHRT_MAX );
/*N*/                   EndAction();
/*N*/               } while( nOldH != pRoot->Frm().Height() && nLoopCnt-- );
/*N*/           }
/*N*/ #ifndef PRODUCT
/*N*/           else
/*N*/           {
/*N*/               //MA: 04. Nov. 94, braucht doch keiner oder??
/*N*/               ASSERT( !this, "MakeVisible fuer Drucker wird doch gebraucht?" );
/*N*/           }
/*N*/
/*N*/ #endif
/*N*/       }
/*N*/   }
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::CareChildWindow()
|*
|*  Ersterstellung      AMA 10. Okt. 95
|*  Letzte Aenderung    AMA 10. Okt. 95
|*
******************************************************************************/

//STRIP001 Window* ViewShell::CareChildWin(ViewShell& rVSh)
//STRIP001 {
//STRIP001  if(rVSh.pSfxViewShell)
//STRIP001  {
//STRIP001      const USHORT nId = SvxSearchDialogWrapper::GetChildWindowId();
//STRIP001      SfxViewFrame* pVFrame = rVSh.pSfxViewShell->GetViewFrame();
//STRIP001      const SfxChildWindow* pChWin = pVFrame->GetChildWindow( nId );
//STRIP001      Window *pWin = pChWin ? pChWin->GetWindow() : NULL;
//STRIP001      if ( pWin && pWin->IsVisible() )
//STRIP001          return pWin;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::GetPagePos()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 04. Aug. 93
|*
******************************************************************************/

//STRIP001 Point ViewShell::GetPagePos( USHORT nPageNum ) const
//STRIP001 {
//STRIP001  return GetLayout()->GetPagePos( nPageNum );
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::GetNumPages()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 20. Apr. 94
|*
******************************************************************************/

//STRIP001 USHORT ViewShell::GetNumPages()
//STRIP001 {
//STRIP001  //Es kann sein, das noch kein Layout existiert weil die Methode vom
//STRIP001  //Root-Ctor gerufen wird.
//STRIP001  return GetLayout() ? GetLayout()->GetPageNum() : 0;
//STRIP001 }

//STRIP001 sal_Bool ViewShell::IsDummyPage( USHORT nPageNum ) const
//STRIP001 {
//STRIP001     return GetLayout() ? GetLayout()->IsDummyPage( nPageNum ) : 0;
//STRIP001 }

/*************************************************************************
|*
|*                  ViewShell::UpdateFlds()
|*
|*    Ersterstellung    BP 04.05.92
|*    Beschreibung      erzwingt ein Update fuer jedes Feld
|*
|*  UpdateFlds benachrichtigt alle Felder mit pNewHt.
|*  Wenn pNewHt == 0 ist (default), wird der Feldtyp verschickt.
|*
*************************************************************************/

//STRIP001 void ViewShell::UpdateFlds(BOOL bCloseDB)
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  BOOL bCrsr = ISA(SwCrsrShell);
//STRIP001  if ( bCrsr )
//STRIP001      ((SwCrsrShell*)this)->StartAction();
//STRIP001  else
//STRIP001      StartAction();
//STRIP001
//STRIP001  GetDoc()->UpdateFlds(0, bCloseDB);
//STRIP001
//STRIP001  if ( bCrsr )
//STRIP001      ((SwCrsrShell*)this)->EndAction();
//STRIP001  else
//STRIP001      EndAction();
//STRIP001 }

// update all charts, for that exists any table
//STRIP001 void ViewShell::UpdateAllCharts()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  // Start-/EndAction handled in the SwDoc-Method!
//STRIP001  GetDoc()->UpdateAllCharts();
//STRIP001 }
//STRIP001
//STRIP001 BOOL ViewShell::HasCharts() const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwStartNode *pStNd;
//STRIP001  SwNodeIndex aIdx( *GetDoc()->GetNodes().GetEndOfAutotext().
//STRIP001                      StartOfSectionNode(), 1 );
//STRIP001  while ( 0 != (pStNd = aIdx.GetNode().GetStartNode()) )
//STRIP001  {
//STRIP001      aIdx++;
//STRIP001      const SwOLENode *pNd = aIdx.GetNode().GetOLENode();
//STRIP001      if( pNd && pNd->GetChartTblName().Len() )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*    ViewShell::LayoutIdle()
|*
|*    Ersterstellung    MA 26. May. 92
|*    Letzte Aenderung  OG 19. Mar. 96
|*
*************************************************************************/

/*N*/ void ViewShell::LayoutIdle()
/*N*/ {
/*N*/ #ifdef TCOVER
/*N*/   //fuer TCV-Version: Ende der Startphase des Programmes
/*N*/   TCovCall::Idle();
/*N*/ #endif
/*N*/   if( !pOpt->IsIdle() || !GetWin() ||
/*N*/       ( Imp()->HasDrawView() && Imp()->GetDrawView()->IsDragObj() ) )
/*N*/       return;
/*N*/
/*N*/   //Kein Idle wenn gerade gedruckt wird.
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {   if ( !pSh->GetWin() )
/*N*/           return;
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/
/*N*/   SET_CURR_SHELL( this );
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   // Wenn Test5 gedrueckt ist, wird der IdleFormatierer abgeknipst.
/*N*/   if( pOpt->IsTest5() )
/*N*/       return;
/*N*/ #endif
/*N*/
/*N*/   {
/*N*/       DBG_PROFSTART( LayoutIdle );
/*N*/
/*N*/       //Cache vorbereiten und restaurieren, damit er nicht versaut wird.
/*N*/       SwSaveSetLRUOfst aSave( *SwTxtFrm::GetTxtCache(),
/*N*/                            SwTxtFrm::GetTxtCache()->GetCurMax() - 50 );
/*N*/       SwLayIdle aIdle( GetLayout(), Imp() );
/*N*/       DBG_PROFSTOP( LayoutIdle );
/*N*/   }
/*N*/ }

// Absatzabstaende koennen wahlweise addiert oder maximiert werden

//STRIP001 BOOL ViewShell::IsParaSpaceMax() const
//STRIP001 {
//STRIP001  return GetDoc()->IsParaSpaceMax();
//STRIP001 }

//STRIP001 BOOL ViewShell::IsParaSpaceMaxAtPages() const
//STRIP001 {
//STRIP001  return GetDoc()->IsParaSpaceMaxAtPages();
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void ViewShell::SetParaSpaceMax( BOOL bNew, BOOL bAtPages )
//STRIP001 {
//STRIP001  if( GetDoc()->IsParaSpaceMax() != bNew  ||
//STRIP001  GetDoc()->IsParaSpaceMaxAtPages() != bAtPages )
//STRIP001  {
//STRIP001      SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
//STRIP001      GetDoc()->SetParaSpaceMax( bNew, bAtPages );
//STRIP001      BOOL bCrsr = ISA(SwCrsrShell);
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->StartAction();
//STRIP001      else
//STRIP001          StartAction();
//STRIP001      GetLayout()->InvalidateAllCntnt( INV_PRTAREA | INV_TABLE | INV_SECTION );
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->EndAction();
//STRIP001      else
//STRIP001          EndAction();
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ViewShell::IsTabCompat() const
//STRIP001 {
//STRIP001     return GetDoc()->IsTabCompat();
//STRIP001 }

//STRIP001 void ViewShell::SetTabCompat( BOOL bNew )
//STRIP001 {
//STRIP001     if( GetDoc()->IsTabCompat() != bNew  )
//STRIP001  {
//STRIP001      SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
//STRIP001         GetDoc()->SetTabCompat( bNew );
//STRIP001      BOOL bCrsr = ISA(SwCrsrShell);
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->StartAction();
//STRIP001      else
//STRIP001          StartAction();
//STRIP001      GetLayout()->InvalidateAllCntnt( INV_PRTAREA | INV_TABLE | INV_SECTION );
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->EndAction();
//STRIP001      else
//STRIP001          EndAction();
//STRIP001  }
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::Reformat
|*
|*  Ersterstellung      BP ???
|*  Letzte Aenderung    MA 13. Feb. 98
|*
******************************************************************************/

/*N*/ void ViewShell::Reformat()
/*N*/ {
/*N*/   SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
/*N*/
/*N*/   // Wir gehen auf Nummer sicher:
/*N*/   // Wir muessen die alten Fontinformationen wegschmeissen,
/*N*/   // wenn die Druckeraufloesung oder der Zoomfaktor sich aendert.
/*N*/   // Init() und Reformat() sind die sichersten Stellen.
/*N*/ #ifdef FNTMET
/*N*/   aFntMetList.Flush();
/*N*/ #else
/*N*/   pFntCache->Flush( );
/*N*/ #endif
/*N*/
/*N*/     if( GetLayout()->IsCallbackActionEnabled() )
/*N*/     {
/*N*/
/*N*/         StartAction();
/*N*/         GetLayout()->InvalidateAllCntnt();
/*N*/         EndAction();
/*N*/     }
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::CalcLayout()
|*                  Vollstaendige Formatierung von Layout und Inhalt.
|*
|*  Ersterstellung      MA 31. Jan. 94
|*  Letzte Aenderung    MA 08. Oct. 96
|*
******************************************************************************/

/*N*/ void ViewShell::CalcLayout()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   SwWait aWait( *GetDoc()->GetDocShell(), TRUE );
/*N*/
/*N*/   //Cache vorbereiten und restaurieren, damit er nicht versaut wird.
/*N*/   SwSaveSetLRUOfst aSaveLRU( *SwTxtFrm::GetTxtCache(),
/*N*/                               SwTxtFrm::GetTxtCache()->GetCurMax() - 50 );
/*N*/
/*N*/   //Progress einschalten wenn noch keiner Lauft.
/*N*/   const BOOL bEndProgress = SfxProgress::GetActiveProgress( GetDoc()->GetDocShell() ) == 0;
/*N*/   if ( bEndProgress )
/*N*/   {
/*N*/       USHORT nEndPage = GetLayout()->GetPageNum();
/*N*/       nEndPage += nEndPage * 10 / 100;
/*N*/       ::binfilter::StartProgress( STR_STATSTR_REFORMAT, 0, nEndPage, GetDoc()->GetDocShell() );
/*N*/   }
/*N*/
/*N*/   SwLayAction aAction( GetLayout(), Imp() );
/*N*/   aAction.SetPaint( FALSE );
/*N*/   aAction.SetStatBar( TRUE );
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
/*N*/       aAction.SetStatBar( TRUE );
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
/*N*/   if ( bEndProgress )
/*N*/       ::binfilter::EndProgress( GetDoc()->GetDocShell() );
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::SetFirstVisPageInvalid()
|*
|*  Ersterstellung      MA 19. May. 94
|*  Letzte Aenderung    MA 19. May. 94
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
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 17. Sep. 96
|*
******************************************************************************/

/*N*/ void ViewShell::SizeChgNotify(const Size &rSize)
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
/*N*/               PageNumNotify( this, pCnt->GetPhyPageNum(), nVirtNum, sDisplay );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       bDocSizeChgd = FALSE;
/*N*/       ::binfilter::SizeNotify( this, GetLayout()->Frm().SSize() );
/*N*/   }
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::VisPortChgd()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 22. Jul. 96
|*
******************************************************************************/

//STRIP001 void ViewShell::VisPortChgd( const SwRect &rRect)
//STRIP001 {
//STRIP001  ASSERT( GetWin(), "VisPortChgd ohne Window." );
//STRIP001
//STRIP001  if ( rRect == VisArea() )
//STRIP001      return;
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  if ( bInEndAction )
//STRIP001  {
//STRIP001      //Da Rescheduled doch schon wieder irgendwo einer?
//STRIP001      ASSERT( !this, "Scroll waehrend einer EndAction." );
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  ASSERT( rRect.Top() >= 0 && rRect.Left() >= 0 &&
//STRIP001          rRect.Bottom() >= 0 && rRect.Right() >= 0,
//STRIP001          "VisArea in die Wiese?" );
//STRIP001
//STRIP001  //Ersteinmal die alte sichtbare Seite holen, dann braucht nacher nicht
//STRIP001  //lange gesucht werden.
//STRIP001  const SwFrm *pOldPage = Imp()->GetFirstVisPage();
//STRIP001
//STRIP001  const SwRect aPrevArea( VisArea() );
//STRIP001  const BOOL bFull = aPrevArea.IsEmpty();
//STRIP001  aVisArea = rRect;
//STRIP001  SetFirstVisPageInvalid();
//STRIP001
//STRIP001  //Wenn noch eine PaintRegion herumsteht und sich die VisArea geaendert hat,
//STRIP001  //so ist die PaintRegion spaetestens jetzt obsolete. Die PaintRegion kann
//STRIP001  //vom RootFrm::Paint erzeugt worden sein.
//STRIP001  if ( !bInEndAction &&
//STRIP001       Imp()->GetRegion() && Imp()->GetRegion()->GetOrigin() != VisArea() )
//STRIP001      Imp()->DelRegions();
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  SwSaveHdl aSaveHdl( Imp() );
//STRIP001
//STRIP001  if ( bFull )
//STRIP001      GetWin()->Invalidate();
//STRIP001  else
//STRIP001  {
//STRIP001      // Betrag ausrechnen, um den gescrolled werden muss.
//STRIP001      const long nXDiff = aPrevArea.Left() - VisArea().Left();
//STRIP001      const long nYDiff = aPrevArea.Top()  - VisArea().Top();
//STRIP001
//STRIP001      if( !nXDiff && !GetDoc()->IsBrowseMode() &&
//STRIP001          (!Imp()->HasDrawView() || !Imp()->GetDrawView()->IsGridVisible() ) )
//STRIP001      {
//STRIP001          //Falls moeglich die Wiese nicht mit Scrollen.
//STRIP001          //Also linke und rechte Kante des Scrollbereiches auf die
//STRIP001          //Seiten begrenzen.
//STRIP001          const SwPageFrm *pPage = (SwPageFrm*)GetDoc()->GetRootFrm()->Lower();
//STRIP001          if ( pPage->Frm().Top() > pOldPage->Frm().Top() )
//STRIP001              pPage = (SwPageFrm*)pOldPage;
//STRIP001          SwRect aBoth( VisArea() );
//STRIP001          aBoth.Union( aPrevArea );
//STRIP001          const SwTwips nBottom = aBoth.Bottom();
//STRIP001          const SwTwips nRight  = aBoth.Right();
//STRIP001          SwTwips nMinLeft = LONG_MAX;
//STRIP001          SwTwips nMaxRight= 0;
//STRIP001          while ( pPage &&
//STRIP001                  !((pPage->Frm().Top()  > nBottom) ||
//STRIP001                    (pPage->Frm().Left() > nRight)))
//STRIP001          {
//STRIP001              if ( pPage->Frm().IsOver( aBoth ) )
//STRIP001              {
//STRIP001                     // OD 12.02.2003 #i9719#, #105645# - consider new border
//STRIP001                     // and shadow width
//STRIP001                     const SwTwips nBorderWidth =
//STRIP001                             GetOut()->PixelToLogic( Size( pPage->BorderPxWidth(), 0 ) ).Width();
//STRIP001                     const SwTwips nShadowWidth =
//STRIP001                             GetOut()->PixelToLogic( Size( pPage->ShadowPxWidth(), 0 ) ).Width();
//STRIP001                     // OD 03.03.2003 #107927# - use correct datatype
//STRIP001                     const SwTwips nPageLeft = pPage->Frm().Left() - nBorderWidth;
//STRIP001                     if( nPageLeft < nMinLeft )
//STRIP001                         nMinLeft = nPageLeft;
//STRIP001                     // OD 03.03.2003 #107927# - use correct datatype
//STRIP001                     const SwTwips nPageRight = pPage->Frm().Right() + nBorderWidth + nShadowWidth;
//STRIP001                     if( nPageRight > nMaxRight )
//STRIP001                         nMaxRight = nPageRight;
//STRIP001                  //Zus. auf die Zeichenobjekte abgleichen.
//STRIP001                  //Einen Ofst beruecksichtigen, weil die Objekte u.U.
//STRIP001                  //selektiert sind und die Henkel dann hinausstehen.
//STRIP001                  if ( pPage->GetSortedObjs() )
//STRIP001                  {
//STRIP001                      const long nOfst = GetOut()->PixelToLogic(
//STRIP001                          Size(Imp()->GetDrawView()->GetMarkHdlSizePixel()/2,0)).Width();
//STRIP001                         for ( USHORT i = 0;
//STRIP001                            i < pPage->GetSortedObjs()->Count(); ++i )
//STRIP001                      {
//STRIP001                          SdrObject *pObj = (*pPage->GetSortedObjs())[i];
//STRIP001 //JP 22.12.99: why ignore FlyFrames? The result is Bug 69762 for FlyFrames
//STRIP001 //                           if ( pObj->IsWriterFlyFrame() )
//STRIP001 //                               continue;
//STRIP001                          const Rectangle &rBound = pObj->GetBoundRect();
//STRIP001                             // OD 03.03.2003 #107927# - use correct datatype
//STRIP001                             const SwTwips nL = Max( 0L, rBound.Left() - nOfst );
//STRIP001                          if ( nL < nMinLeft )
//STRIP001                              nMinLeft = nL;
//STRIP001                          if( rBound.Right() + nOfst > nMaxRight )
//STRIP001                              nMaxRight = rBound.Right() + nOfst;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001          }
//STRIP001          Rectangle aRect( aPrevArea.SVRect() );
//STRIP001          aRect.Left()  = nMinLeft;
//STRIP001          aRect.Right() = nMaxRight;
//STRIP001          if( VisArea().IsOver( aPrevArea ) && !nLockPaint )
//STRIP001          {
//STRIP001              aVisArea.Pos() = aPrevArea.Pos();
//STRIP001              if ( SmoothScroll( nXDiff, nYDiff, &aRect ) )
//STRIP001                  return;
//STRIP001              aVisArea.Pos() = rRect.Pos();
//STRIP001          }
//STRIP001          else
//STRIP001              GetWin()->Invalidate( aRect );
//STRIP001      }
//STRIP001      else if ( !nLockPaint ) //Wird im UnLock erledigt
//STRIP001      {
//STRIP001          if( VisArea().IsOver( aPrevArea ) )
//STRIP001          {
//STRIP001              aVisArea.Pos() = aPrevArea.Pos();
//STRIP001              if ( SmoothScroll( nXDiff, nYDiff, 0 ) )
//STRIP001                  return;
//STRIP001              aVisArea.Pos() = rRect.Pos();
//STRIP001          }
//STRIP001          else
//STRIP001              GetWin()->Invalidate();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  Point aPt( VisArea().Pos() );
//STRIP001  aPt.X() = -aPt.X(); aPt.Y() = -aPt.Y();
//STRIP001  MapMode aMapMode( GetWin()->GetMapMode() );
//STRIP001  aMapMode.SetOrigin( aPt );
//STRIP001  GetWin()->SetMapMode( aMapMode );
//STRIP001  if ( HasDrawView() )
//STRIP001  {
//STRIP001      Imp()->GetDrawView()->VisAreaChanged( GetWin() );
//STRIP001      Imp()->GetDrawView()->SetActualWin( GetWin() );
//STRIP001  }
//STRIP001  Imp()->bPaintInScroll = TRUE;
//STRIP001  GetWin()->Update();
//STRIP001  Imp()->bPaintInScroll = FALSE;
//STRIP001
//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001  if( Imp()->IsAccessible() )
//STRIP001      Imp()->UpdateAccessible();
//STRIP001 #endif
//STRIP001
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::SmoothScroll()
|*
|*  Ersterstellung      MA 04. Jul. 96
|*  Letzte Aenderung    MA 25. Mar. 97
|*
******************************************************************************/

//STRIP001 BOOL ViewShell::SmoothScroll( long lXDiff, long lYDiff, const Rectangle *pRect )
//STRIP001 {
//STRIP001  const ULONG nColCnt = pOut->GetColorCount();
//STRIP001  long lMult = 1, lMax = LONG_MAX;
//STRIP001  if ( nColCnt == 65536 )
//STRIP001  {
//STRIP001      lMax = 7000;
//STRIP001      lMult = 2;
//STRIP001  }
//STRIP001  if ( nColCnt == 16777216 )
//STRIP001  {
//STRIP001      lMax = 5000;
//STRIP001      lMult = 6;
//STRIP001  }
//STRIP001  else if ( nColCnt == 1 )
//STRIP001  {
//STRIP001      lMax = 3000;
//STRIP001      lMult = 12;
//STRIP001  }
//STRIP001
//STRIP001  if ( !lXDiff && bEnableSmooth && Abs(lYDiff) < lMax &&
//STRIP001       GetViewOptions()->IsSmoothScroll() &&
//STRIP001       (!ISA( SwCrsrShell ) ||
//STRIP001        (!((SwCrsrShell*)this)->HasSelection() &&
//STRIP001         ((SwCrsrShell*)this)->GetCrsrCnt() < 2)) &&
//STRIP001       GetWin()->GetWindowClipRegionPixel(
//STRIP001          WINDOW_GETCLIPREGION_NOCHILDREN|WINDOW_GETCLIPREGION_NULL )
//STRIP001                                                          .IsNull() )
//STRIP001  {
//STRIP001      Imp()->bStopSmooth = FALSE;
//STRIP001
//STRIP001      const SwRect aOldVis( VisArea() );
//STRIP001
//STRIP001      //Virtuelles Device erzeugen und einstellen.
//STRIP001      const Size aPixSz = GetWin()->PixelToLogic(Size(1,1));
//STRIP001      VirtualDevice *pVout = new VirtualDevice( *GetWin() );
//STRIP001      pVout->SetLineColor( GetWin()->GetLineColor() );
//STRIP001      pVout->SetFillColor( GetWin()->GetFillColor() );
//STRIP001      MapMode aMapMode( GetWin()->GetMapMode() );
//STRIP001      pVout->SetMapMode( aMapMode );
//STRIP001      Size aSize( aVisArea.Width()+2*aPixSz.Width(), Abs(lYDiff)+(2*aPixSz.Height()) );
//STRIP001      if ( pRect )
//STRIP001          aSize.Width() = Min(aSize.Width(), pRect->GetWidth()+2*aPixSz.Width());
//STRIP001      if ( pVout->SetOutputSize( aSize ) )
//STRIP001      {
//STRIP001          nLockPaint++;
//STRIP001
//STRIP001          //Ersteinmal alles neue in das VirDev Painten.
//STRIP001          SwRect aRect( VisArea() );
//STRIP001          aRect.Height( aSize.Height() );
//STRIP001          if ( pRect )
//STRIP001          {
//STRIP001              aRect.Pos().X() = Max(aRect.Left(),pRect->Left()-aPixSz.Width());
//STRIP001              aRect.Right( Min(aRect.Right()+2*aPixSz.Width(), pRect->Right()+aPixSz.Width()));
//STRIP001          }
//STRIP001          else
//STRIP001              aRect.SSize().Width() += 2*aPixSz.Width();
//STRIP001          aRect.Pos().Y() = lYDiff < 0 ? aOldVis.Bottom() - aPixSz.Height()
//STRIP001                                       : aRect.Top() - aSize.Height() + aPixSz.Height();
//STRIP001          aRect.Pos().X() = Max( 0L, aRect.Left()-aPixSz.Width() );
//STRIP001          aRect.Pos()  = GetWin()->PixelToLogic( GetWin()->LogicToPixel( aRect.Pos()));
//STRIP001          aRect.SSize()= GetWin()->PixelToLogic( GetWin()->LogicToPixel( aRect.SSize()));
//STRIP001          aVisArea = aRect;
//STRIP001          const Point aPt( -aRect.Left(), -aRect.Top() );
//STRIP001          aMapMode.SetOrigin( aPt );
//STRIP001          pVout->SetMapMode( aMapMode );
//STRIP001          OutputDevice *pOld = pOut;
//STRIP001          pOut = pVout;
//STRIP001          PaintDesktop( aRect );
//STRIP001          ViewShell::bLstAct = TRUE;
//STRIP001          GetLayout()->Paint( aRect );
//STRIP001          ViewShell::bLstAct = FALSE;
//STRIP001          pOut = pOld;
//STRIP001          aVisArea = aOldVis;
//STRIP001          BOOL bControls = GetViewOptions()->IsControl();
//STRIP001
//STRIP001
//STRIP001          //Jetzt Stueckchenweise schieben und die neuen Pixel aus dem
//STRIP001          //VirDev  kopieren.
//STRIP001
//STRIP001          // ??????????????????????
//STRIP001          // or is it better to get the scrollfactor from the User
//STRIP001          // as option?
//STRIP001          // ??????????????????????
//STRIP001          long lMaDelta = aPixSz.Height();
//STRIP001          if ( Abs(lYDiff) > ( aVisArea.Height() / 3 ) )
//STRIP001              lMaDelta *= 6;
//STRIP001          else
//STRIP001              lMaDelta *= 2;
//STRIP001
//STRIP001          lMaDelta *= lMult;
//STRIP001
//STRIP001          if ( lYDiff < 0 )
//STRIP001              lMaDelta = -lMaDelta;
//STRIP001
//STRIP001          long lDiff = lYDiff;
//STRIP001          while ( lDiff )
//STRIP001          {
//STRIP001              long lScroll;
//STRIP001              if ( Imp()->bStopSmooth || Abs(lDiff) <= Abs(lMaDelta) )
//STRIP001              {
//STRIP001                  lScroll = lDiff;
//STRIP001                  lDiff = 0;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  lScroll = lMaDelta;
//STRIP001                  lDiff -= lMaDelta;
//STRIP001              }
//STRIP001
//STRIP001              SwRect aOldVis = VisArea();
//STRIP001              aVisArea.Pos().Y() -= lScroll;
//STRIP001              aVisArea.Pos() = GetWin()->PixelToLogic( GetWin()->LogicToPixel( VisArea().Pos()));
//STRIP001              lScroll = aOldVis.Top() - VisArea().Top();
//STRIP001              if ( pRect )
//STRIP001              {
//STRIP001                  Rectangle aTmp( aOldVis.SVRect() );
//STRIP001                  aTmp.Left() = pRect->Left();
//STRIP001                  aTmp.Right()= pRect->Right();
//STRIP001                  GetWin()->Scroll( 0, lScroll, aTmp, SCROLL_CHILDREN );
//STRIP001              }
//STRIP001              else
//STRIP001                  GetWin()->Scroll( 0, lScroll, SCROLL_CHILDREN );
//STRIP001              const Point aPt( -VisArea().Left(), -VisArea().Top() );
//STRIP001              MapMode aMapMode( GetWin()->GetMapMode() );
//STRIP001              aMapMode.SetOrigin( aPt );
//STRIP001              GetWin()->SetMapMode( aMapMode );
//STRIP001
//STRIP001              if ( Imp()->HasDrawView() )
//STRIP001                  Imp()->GetDrawView()->VisAreaChanged( GetWin() );
//STRIP001
//STRIP001              SetFirstVisPageInvalid();
//STRIP001              if ( !Imp()->bStopSmooth )
//STRIP001              {
//STRIP001                  Imp()->aSmoothRect = VisArea();
//STRIP001                  if ( lScroll > 0 )
//STRIP001                      Imp()->aSmoothRect.Bottom( VisArea().Top() +
//STRIP001                                  lScroll + aPixSz.Height() );
//STRIP001                  else
//STRIP001                      Imp()->aSmoothRect.Top( VisArea().Bottom() +
//STRIP001                                  lScroll + aPixSz.Height() );
//STRIP001
//STRIP001                  Imp()->bSmoothUpdate = TRUE;
//STRIP001                  GetWin()->Update();
//STRIP001                  Imp()->bSmoothUpdate = FALSE;
//STRIP001
//STRIP001                  if ( !Imp()->bStopSmooth )
//STRIP001                  {
//STRIP001                      SwRect &rTmp = Imp()->aSmoothRect;
//STRIP001                      rTmp.Pos().Y() -= aPixSz.Height();
//STRIP001                      rTmp.Pos().X() -= aPixSz.Width();
//STRIP001                      rTmp.SSize().Height() += 2*aPixSz.Height();
//STRIP001                      rTmp.SSize().Width() += 2*aPixSz.Width();
//STRIP001                      GetWin()->DrawOutDev( rTmp.Pos(), rTmp.SSize(),
//STRIP001                                            rTmp.Pos(), rTmp.SSize(),
//STRIP001                                            *pVout );
//STRIP001                      if( bControls )
//STRIP001                          Imp()->PaintLayer( pDoc->GetControlsId(), rTmp );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      --nLockPaint;
//STRIP001              }
//STRIP001          }
//STRIP001          delete pVout;
//STRIP001          GetWin()->Update();
//STRIP001          if ( !Imp()->bStopSmooth )
//STRIP001              --nLockPaint;
//STRIP001          SetFirstVisPageInvalid();
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001      delete pVout;
//STRIP001  }
//STRIP001 //#endif
//STRIP001  aVisArea.Pos().X() -= lXDiff;
//STRIP001  aVisArea.Pos().Y() -= lYDiff;
//STRIP001  if ( pRect )
//STRIP001      GetWin()->Scroll( lXDiff, lYDiff, *pRect, SCROLL_CHILDREN );
//STRIP001  else
//STRIP001      GetWin()->Scroll( lXDiff, lYDiff, SCROLL_CHILDREN );
//STRIP001  return FALSE;
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::PaintDesktop()
|*
|*  Ersterstellung      MA 16. Dec. 93
|*  Letzte Aenderung    MA 30. Nov. 95
|*
******************************************************************************/

//STRIP001 void ViewShell::PaintDesktop( const SwRect &rRect )
//STRIP001 {
//STRIP001  if ( !GetWin() && !GetOut()->GetConnectMetaFile() )
//STRIP001      return;                     //Fuer den Drucker tun wir hier nix
//STRIP001
//STRIP001  //Sonderfaelle abfangen, damit es nicht gar so ueberraschend aussieht.
//STRIP001  //Kann z.B. waehrend des Idle'ns zwischenzeitlich auftreten.
//STRIP001  //Die Rechtecke neben den Seiten muessen wir leider auf jedenfall Painten,
//STRIP001  //den diese werden spaeter beim VisPortChgd ausgespart.
//STRIP001  FASTBOOL bBorderOnly = FALSE;
//STRIP001  const SwRootFrm *pRoot = GetDoc()->GetRootFrm();
//STRIP001  if ( rRect.Top() > pRoot->Frm().Bottom() )
//STRIP001  {
//STRIP001      const SwFrm *pPg = pRoot->Lower();
//STRIP001      while ( pPg && pPg->GetNext() )
//STRIP001          pPg = pPg->GetNext();
//STRIP001      if ( !pPg || !pPg->Frm().IsOver( VisArea() ) )
//STRIP001          bBorderOnly = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  SwRegionRects aRegion( rRect );
//STRIP001
//STRIP001  if ( bBorderOnly )
//STRIP001  {
//STRIP001      const SwFrm *pPage = pRoot->Lower();
//STRIP001      SwRect aLeft( rRect ), aRight( rRect );
//STRIP001      while ( pPage )
//STRIP001      {
//STRIP001          long nTmp = pPage->Frm().Left();
//STRIP001          if ( nTmp < aLeft.Right() )
//STRIP001              aLeft.Right( nTmp );
//STRIP001          nTmp = pPage->Frm().Right();
//STRIP001          if ( nTmp > aRight.Left() )
//STRIP001              aRight.Left( nTmp );
//STRIP001          pPage = pPage->GetNext();
//STRIP001      }
//STRIP001      aRegion.Remove( 0, aRegion.Count() );
//STRIP001      if ( aLeft.HasArea() )
//STRIP001          aRegion.Insert( aLeft, 0 );
//STRIP001      if ( aRight.HasArea() )
//STRIP001          aRegion.Insert( aRight, 1 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SwFrm *pPage = Imp()->GetFirstVisPage();
//STRIP001      const SwTwips nBottom = rRect.Bottom();
//STRIP001      const SwTwips nRight  = rRect.Right();
//STRIP001      while ( pPage && aRegion.Count() &&
//STRIP001              !((pPage->Frm().Top() > nBottom) || (pPage->Frm().Left() > nRight)))
//STRIP001      {
//STRIP001          if ( pPage->Frm().IsOver( rRect ) )
//STRIP001              aRegion -= pPage->Frm();
//STRIP001          pPage = pPage->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001  if ( aRegion.Count() )
//STRIP001      _PaintDesktop( aRegion );
//STRIP001 }


// PaintDesktop gesplittet, dieser Teil wird auch von PreViewPage benutzt
//STRIP001 void ViewShell::_PaintDesktop( const SwRegionRects &rRegion )
//STRIP001 {
//STRIP001  GetOut()->Push( PUSH_FILLCOLOR );
//STRIP001     // OD 14.02.2003 #107424# - no longer needed, because color configuration
//STRIP001     // is loaded in constructor of <SwModule>.
//STRIP001     /*
//STRIP001     //make sure the color configuration has been loaded
//STRIP001     SW_MOD()->GetColorConfig();
//STRIP001     */
//STRIP001     GetOut()->SetFillColor( SwViewOption::GetAppBackgroundColor());
//STRIP001  for ( USHORT i = 0; i < rRegion.Count(); ++i )
//STRIP001      GetOut()->DrawRect( rRegion[i].SVRect() );
//STRIP001  GetOut()->Pop();
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::CheckInvalidForPaint()
|*
|*  Ersterstellung      MA 19. May. 94
|*  Letzte Aenderung    MA 09. Jun. 94
|*
******************************************************************************/

//STRIP001 BOOL ViewShell::CheckInvalidForPaint( const SwRect &rRect )
//STRIP001 {
//STRIP001  if ( !GetWin() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwPageFrm *pPage = Imp()->GetFirstVisPage();
//STRIP001  const SwTwips nBottom = VisArea().Bottom();
//STRIP001  const SwTwips nRight  = VisArea().Right();
//STRIP001  BOOL bRet = FALSE;
//STRIP001  while ( !bRet && pPage && !((pPage->Frm().Top()  > nBottom) ||
//STRIP001                              (pPage->Frm().Left() > nRight)))
//STRIP001  {
//STRIP001      if ( pPage->IsInvalid() || pPage->IsInvalidFly() )
//STRIP001          bRet = TRUE;
//STRIP001      pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  if ( bRet )
//STRIP001  {
//STRIP001      //Start/EndAction wuerden hier leider nix helfen, weil das Paint vom
//STRIP001      //GUI 'reinkam und somit ein Clipping gesetzt ist gegen das wir nicht
//STRIP001      //nicht ankommen.
//STRIP001      //Ergo: Alles selbst machen (siehe ImplEndAction())
//STRIP001      if ( Imp()->GetRegion() && Imp()->GetRegion()->GetOrigin() != VisArea())
//STRIP001           Imp()->DelRegions();
//STRIP001
//STRIP001      Imp()->ResetScroll();
//STRIP001      SwLayAction aAction( GetLayout(), Imp() );
//STRIP001      aAction.SetComplete( FALSE );
//STRIP001         // We increment the action counter to avoid a recursive call of actions
//STRIP001         // e.g. from a SwFEShell::RequestObjectResize(..) in bug 95829.
//STRIP001         // A recursive call of actions is no good idea because the inner action
//STRIP001         // can't format frames which are locked by the outer action. This may
//STRIP001         // cause and endless loop.
//STRIP001         ++nStartAction;
//STRIP001      aAction.Action();
//STRIP001         --nStartAction;
//STRIP001
//STRIP001      SwRegionRects *pRegion = Imp()->GetRegion();
//STRIP001      if ( pRegion && aAction.IsBrowseActionStop() )
//STRIP001      {
//STRIP001          //Nur dann interessant, wenn sich im sichtbaren Bereich etwas
//STRIP001          //veraendert hat.
//STRIP001          BOOL bStop = TRUE;
//STRIP001          for ( USHORT i = 0; i < pRegion->Count(); ++i )
//STRIP001          {
//STRIP001              const SwRect &rTmp = (*pRegion)[i];
//STRIP001              if ( FALSE == (bStop = rTmp.IsOver( VisArea() )) )
//STRIP001                  break;
//STRIP001          }
//STRIP001          if ( bStop )
//STRIP001          {
//STRIP001              Imp()->DelRegions();
//STRIP001              pRegion = 0;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( pRegion )
//STRIP001      {
//STRIP001          //Erst Invert dann Compress, niemals andersherum!
//STRIP001          pRegion->Invert();
//STRIP001          pRegion->Compress();
//STRIP001          bRet = FALSE;
//STRIP001          if ( pRegion->Count() )
//STRIP001          {
//STRIP001              SwRegionRects aRegion( rRect );
//STRIP001              for ( USHORT i = 0; i < pRegion->Count(); ++i )
//STRIP001              {   const SwRect &rTmp = (*pRegion)[i];
//STRIP001                  if ( !rRect.IsInside( rTmp ) )
//STRIP001                  {
//STRIP001                      InvalidateWindows( rTmp );
//STRIP001                      if ( rTmp.IsOver( VisArea() ) )
//STRIP001                      {   aRegion -= rTmp;
//STRIP001                          bRet = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( bRet )
//STRIP001              {
//STRIP001                  for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001                      GetWin()->Invalidate( aRegion[i].SVRect() );
//STRIP001
//STRIP001                  if ( rRect != VisArea() )
//STRIP001                  {
//STRIP001                      //rRect == VisArea ist der spezialfall fuer neu bzw.
//STRIP001                      //Shift-Ctrl-R, dafuer sollte es nicht notwendig sein
//STRIP001                      //das Rechteck nocheinmal in Dokumentkoordinaten v
//STRIP001                      //vorzuhalten.
//STRIP001                      if ( aInvalidRect.IsEmpty() )
//STRIP001                          aInvalidRect = rRect;
//STRIP001                      else
//STRIP001                          aInvalidRect.Union( rRect );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              bRet = FALSE;
//STRIP001          Imp()->DelRegions();
//STRIP001      }
//STRIP001      else
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::Paint()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 17. Sep. 96
|*
******************************************************************************/

//STRIP001 void ViewShell::Paint(const Rectangle &rRect)
//STRIP001 {
//STRIP001  if ( nLockPaint )
//STRIP001  {
//STRIP001      if ( Imp()->bSmoothUpdate )
//STRIP001      {
//STRIP001          SwRect aTmp( rRect );
//STRIP001          if ( !Imp()->aSmoothRect.IsInside( aTmp ) )
//STRIP001              Imp()->bStopSmooth = TRUE;
//STRIP001          else
//STRIP001          {
//STRIP001              Imp()->aSmoothRect = aTmp;
//STRIP001              return;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          return;
//STRIP001  }
//STRIP001
//STRIP001  if ( SwRootFrm::IsInPaint() )
//STRIP001  {
//STRIP001      //Waehrend der Ausgabe einer Seite beim Druckvorgang wird das
//STRIP001      //Paint gepuffert.
//STRIP001      SwPaintQueue::Add( this, SwRect( rRect ) );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  //MA 30. Jul. 95: fix(16787): mit !nStartAction versuche ich mal mich gegen
//STRIP001  //fehlerhaften Code an anderen Stellen zu wehren. Hoffentlich fuehrt das
//STRIP001  //nicht zu Problemen!?
//STRIP001  if ( bPaintWorks && !nStartAction )
//STRIP001  {
//STRIP001      if( GetWin() && GetWin()->IsVisible() )
//STRIP001      {
//STRIP001          //Wenn mit dem Paint ein Bereich betroffen ist, der vorher gescrolled
//STRIP001          //wurde, so wiederholen wir das Paint mit dem Gesamtbereich. Nur so
//STRIP001          //koennen wir sicherstellen, das (nicht mal kurzfristig) durch das Paint
//STRIP001          //keine Alignmentfehler sichtbar werden.
//STRIP001          SwRect aRect( rRect );
//STRIP001          if ( Imp()->IsScrolled() && Imp()->FlushScrolledArea( aRect ) )
//STRIP001          {
//STRIP001              GetWin()->Invalidate( aRect.SVRect() );
//STRIP001              return;
//STRIP001          }
//STRIP001
//STRIP001          if ( bPaintInProgress ) //Schutz gegen doppelte Paints!
//STRIP001          {
//STRIP001              GetWin()->Invalidate( rRect );
//STRIP001              return;
//STRIP001          }
//STRIP001
//STRIP001          bPaintInProgress = TRUE;
//STRIP001          SET_CURR_SHELL( this );
//STRIP001          SwRootFrm::SetNoVirDev( TRUE );
//STRIP001
//STRIP001          //Wir wollen nicht staendig hin und her Clippen, wir verlassen
//STRIP001          //uns darauf, das sich alle auf das Rechteck beschraeken und
//STRIP001          //brauchen das Clipping hier nur einmalig einkalkulieren. Das
//STRIP001          //ClipRect wird hier einmal entfernt und nicht Restauriert, denn
//STRIP001          //von aussen braucht es sowieso keiner mehr.
//STRIP001          //Nicht wenn wir ein MetaFile aufzeichnen.
//STRIP001          if( !GetOut()->GetConnectMetaFile() && GetOut()->IsClipRegion())
//STRIP001              GetOut()->SetClipRegion();
//STRIP001
//STRIP001          if ( IsPreView() )
//STRIP001          {
//STRIP001              //Falls sinnvoll gleich das alte InvalidRect verarbeiten bzw.
//STRIP001              //vernichten.
//STRIP001              if ( aRect.IsInside( aInvalidRect ) )
//STRIP001                  ResetInvalidRect();
//STRIP001              ViewShell::bLstAct = TRUE;
//STRIP001              GetLayout()->Paint( aRect );
//STRIP001              ViewShell::bLstAct = FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwSaveHdl *pSaveHdl = 0;
//STRIP001              if ( Imp()->HasDrawView() )
//STRIP001                  pSaveHdl = new SwSaveHdl( Imp() );
//STRIP001
//STRIP001              //Wenn eine der sichtbaren Seiten noch irgendetwas zum Repaint
//STRIP001              //angemeldet hat, so muessen Repaints ausgeloest werden.
//STRIP001              if ( !CheckInvalidForPaint( aRect ) )
//STRIP001              {
//STRIP001                  PaintDesktop( aRect );
//STRIP001                  //Falls sinnvoll gleich das alte InvalidRect verarbeiten bzw.
//STRIP001                  //vernichten.
//STRIP001                  if ( aRect.IsInside( aInvalidRect ) )
//STRIP001                      ResetInvalidRect();
//STRIP001                  ViewShell::bLstAct = TRUE;
//STRIP001                  GetLayout()->Paint( aRect );
//STRIP001                  ViewShell::bLstAct = FALSE;
//STRIP001              }
//STRIP001              delete pSaveHdl;
//STRIP001          }
//STRIP001          SwRootFrm::SetNoVirDev( FALSE );
//STRIP001          bPaintInProgress = FALSE;
//STRIP001          UISizeNotify();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( aInvalidRect.IsEmpty() )
//STRIP001          aInvalidRect = SwRect( rRect );
//STRIP001      else
//STRIP001          aInvalidRect.Union( SwRect( rRect ) );
//STRIP001
//STRIP001      if ( bInEndAction && GetWin() )
//STRIP001      {
//STRIP001          Region aRegion( GetWin()->GetPaintRegion() );
//STRIP001          RegionHandle hHdl( aRegion.BeginEnumRects() );
//STRIP001          Rectangle aRect;
//STRIP001          while ( aRegion.GetNextEnumRect( hHdl, aRect ) )
//STRIP001              Imp()->AddPaintRect( aRect );
//STRIP001          aRegion.EndEnumRects( hHdl );
//STRIP001      }
//STRIP001      else if ( SfxProgress::GetActiveProgress( GetDoc()->GetDocShell() ) &&
//STRIP001                GetOut() == GetWin() )
//STRIP001      {
//STRIP001          pOut->Push( PUSH_FILLCOLOR );
//STRIP001          pOut->SetFillColor( Imp()->GetRetoucheColor() );
//STRIP001          pOut->DrawRect( rRect );
//STRIP001          pOut->Pop();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::SetBrowseBorder()
|*
|*  Ersterstellung      AMA 20. Aug. 96
|*  Letzte Aenderung    AMA 20. Aug. 96
|*
******************************************************************************/

/*N*/ void ViewShell::SetBrowseBorder( const Size& rNew )
/*N*/ {
/*N*/   if( rNew != GetBrowseBorder() )
/*N*/   {
/*N*/       aBrowseBorder = rNew;
/*N*/       if ( aVisArea.HasArea() )
                {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/          CheckBrowseView( FALSE );
/*N*/   }
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::CheckBrowseView()
|*
|*  Ersterstellung      MA 04. Mar. 96
|*  Letzte Aenderung    MA 04. Jul. 96
|*
******************************************************************************/

/*N*/ void ViewShell::CheckBrowseView( FASTBOOL bBrowseChgd )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   if ( !bBrowseChgd && !GetDoc()->IsBrowseMode() )
//STRIP001      return;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  ASSERT( GetLayout(), "Layout not ready" );
//STRIP001
//STRIP001  // Wenn das Layout noch nicht einmal eine Hoehe hat,
//STRIP001  // ist sowieso nichts formatiert.
//STRIP001  // Dann eruebrigt sich die Invalidierung
//STRIP001  // Falsch, z.B. beim Anlegen einer neuen View wird der Inhalt eingefügt
//STRIP001  // und formatiert (trotz einer leeren VisArea). Hier muessen deshalb
//STRIP001  // die Seiten zur Formatierung angeregt werden.
//STRIP001  if( !GetLayout()->Frm().Height() )
//STRIP001  {
//STRIP001      SwFrm* pPage = GetLayout()->Lower();
//STRIP001      while( pPage )
//STRIP001      {
//STRIP001          pPage->_InvalidateSize();
//STRIP001          pPage = pPage->GetNext();
//STRIP001      }
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  FASTBOOL bBrowseOn = GetDoc()->IsBrowseMode();
//STRIP001
//STRIP001  LockPaint();
//STRIP001  StartAction();
//STRIP001
//STRIP001  SwPageFrm *pPg = (SwPageFrm*)GetLayout()->Lower();
//STRIP001  do
//STRIP001  {   pPg->InvalidateSize();
//STRIP001      pPg->_InvalidatePrt();
//STRIP001      pPg->InvaPercentLowers();
//STRIP001      if ( bBrowseChgd )
//STRIP001      {
//STRIP001          pPg->PrepareHeader();
//STRIP001          pPg->PrepareFooter();
//STRIP001      }
//STRIP001      pPg = (SwPageFrm*)pPg->GetNext();
//STRIP001  } while ( pPg );
//STRIP001
//STRIP001  // Wenn sich die Groessenverhaeltnise im BrowseModus aendern,
//STRIP001  // muss die Position und PrtArea der Cntnt- und Tab-Frames invalidiert werden.
//STRIP001  BYTE nInv = INV_PRTAREA | INV_TABLE | INV_POS;
//STRIP001  // Beim BrowseModus-Wechsel benoetigen die CntntFrms
//STRIP001  // wg. der Drucker/Bildschirmformatierung eine Size-Invalidierung
//STRIP001  if( bBrowseChgd )
//STRIP001         nInv |= INV_SIZE | INV_DIRECTION;
//STRIP001
//STRIP001  GetLayout()->InvalidateAllCntnt( nInv );
//STRIP001
//STRIP001  SwFrm::CheckPageDescs( (SwPageFrm*)GetLayout()->Lower() );
//STRIP001
//STRIP001  EndAction();
//STRIP001  UnlockPaint();
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::Is/Set[Head|Foot]InBrowse()
|*
|*  Ersterstellung      MA 10. Feb. 97
|*  Letzte Aenderung    MA 10. Feb. 97
|*
******************************************************************************/

//STRIP001 BOOL ViewShell::IsHeadInBrowse() const
//STRIP001 {
//STRIP001  return GetDoc()->IsHeadInBrowse();
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void ViewShell::SetHeadInBrowse( BOOL bOn )
//STRIP001 {
//STRIP001  if ( GetDoc()->IsHeadInBrowse() != bOn )
//STRIP001  {
//STRIP001      BOOL bCrsr = ISA(SwCrsrShell);
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->StartAction();
//STRIP001      else
//STRIP001          StartAction();
//STRIP001      GetDoc()->SetHeadInBrowse( bOn );
//STRIP001
//STRIP001      SwPageFrm *pPg = GetLayout() ? (SwPageFrm*)GetLayout()->Lower() : 0;
//STRIP001      while ( pPg )
//STRIP001      {
//STRIP001          if ( bCrsr )
//STRIP001              ::MA_ParkCrsr( pPg->GetPageDesc(), *(SwCrsrShell*)this );
//STRIP001          pPg->PrepareHeader();
//STRIP001          pPg = (SwPageFrm*)pPg->GetNext();
//STRIP001      }
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->EndAction();
//STRIP001      else
//STRIP001          EndAction();
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL ViewShell::IsFootInBrowse() const
//STRIP001 {
//STRIP001  return GetDoc()->IsFootInBrowse();
//STRIP001 }


//STRIP001 void ViewShell::SetFootInBrowse( BOOL bOn )
//STRIP001 {
//STRIP001  if ( GetDoc()->IsFootInBrowse() != bOn )
//STRIP001  {
//STRIP001      BOOL bCrsr = ISA(SwCrsrShell);
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->StartAction();
//STRIP001      else
//STRIP001          StartAction();
//STRIP001      GetDoc()->SetFootInBrowse( bOn );
//STRIP001
//STRIP001      SwPageFrm *pPg = GetLayout() ? (SwPageFrm*)GetLayout()->Lower() : 0;
//STRIP001      while ( pPg )
//STRIP001      {
//STRIP001          if ( bCrsr )
//STRIP001              ::MA_ParkCrsr( pPg->GetPageDesc(), *(SwCrsrShell*)this );
//STRIP001          pPg->PrepareFooter();
//STRIP001          pPg = (SwPageFrm*)pPg->GetNext();
//STRIP001      }
//STRIP001      if ( bCrsr )
//STRIP001          ((SwCrsrShell*)this)->EndAction();
//STRIP001      else
//STRIP001          EndAction();
//STRIP001  }
//STRIP001 }


/*************************************************************************
|*
|*    ViewShell::GetLayout()
|*    ViewShell::GetNodes()
|*
|*    Ersterstellung    OK 26. May. 92
|*    Letzte Aenderung  MA 16. Sep. 93
|*
*************************************************************************/

/*N*/ SwRootFrm *ViewShell::GetLayout() const
/*N*/ {
/*N*/   return GetDoc()->GetRootFrm();
/*N*/ }
/*N*/
/*N*/ SfxPrinter* ViewShell::GetPrt( BOOL bCreate ) const
/*N*/ {
/*N*/     return GetDoc()->GetPrt( bCreate );
/*N*/ }

//STRIP001 VirtualDevice* ViewShell::GetVirDev( BOOL bCreate ) const
//STRIP001 {
//STRIP001     return GetDoc()->GetVirDev( bCreate );
//STRIP001 }

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

/*N*/ SwPrintData*    ViewShell::GetPrintData() const
/*N*/ {
/*?*/     return GetDoc()->GetPrintData();
/*N*/ }
/*N*/ void            ViewShell::SetPrintData(SwPrintData& rPrtData)
/*N*/ {
/*?*/     DBG_ASSERT(0, "STRIP"); //STRIP001 GetDoc()->SetPrintData(rPrtData);
/*N*/ }

/*N*/ const SwNodes& ViewShell::GetNodes() const
/*N*/ {
/*N*/     return pDoc->GetNodes();
/*N*/ }


/*N*/ void ViewShell::DrawSelChanged(SdrView*)
/*N*/ {
/*N*/ }


/*N*/ Size ViewShell::GetDocSize() const
/*N*/ {
/*N*/   Size aSz;
/*N*/   const SwRootFrm* pRoot = GetLayout();
/*N*/   if( pRoot )
/*N*/       aSz = pRoot->Frm().SSize();
/*N*/   return aSz;
/*N*/ }


/*N*/ SfxItemPool& ViewShell::GetAttrPool()
/*N*/ {
/*N*/   return GetDoc()->GetAttrPool();
/*N*/ }

/*************************************************************************
|*
|*    ViewShell::SetSubsLines()
|*
|*    Beschreibung      Hilfslinien An-/Abschalten
|*    Ersterstellung    MA 26. May. 92
|*    Letzte Aenderung  MA 03. May. 95
|*
*************************************************************************/

//STRIP001 void ViewShell::SetSubsLines()
//STRIP001 {
//STRIP001  if( GetWin() )
//STRIP001      GetWin()->Invalidate();
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::ApplyViewOptions(), ImplApplyViewOptions()
|*
|*  Ersterstellung      ??
|*  Letzte Aenderung    MA 03. Mar. 98
|*
******************************************************************************/

//STRIP001 void ViewShell::ApplyViewOptions( const SwViewOption &rOpt )
//STRIP001 {
//STRIP001
//STRIP001  ViewShell *pSh = this;
//STRIP001  do
//STRIP001  {   pSh->StartAction();
//STRIP001      pSh = (ViewShell*)pSh->GetNext();
//STRIP001  } while ( pSh != this );
//STRIP001
//STRIP001  ImplApplyViewOptions( rOpt );
//STRIP001
//STRIP001  //Einige Aenderungen muessen synchronisiert werden.
//STRIP001  pSh = (ViewShell*)this->GetNext();
//STRIP001  while ( pSh != this )
//STRIP001  {
//STRIP001      SwViewOption aOpt( *pSh->GetViewOptions() );
//STRIP001      aOpt.SetFldName( rOpt.IsFldName() );
//STRIP001      aOpt.SetHidden( rOpt.IsHidden() );
//STRIP001      aOpt.SetShowHiddenPara( rOpt.IsShowHiddenPara() );
//STRIP001      if ( !(aOpt == *pSh->GetViewOptions()) )
//STRIP001          pSh->ImplApplyViewOptions( aOpt );
//STRIP001      pSh = (ViewShell*)pSh->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  pSh = this;
//STRIP001  do
//STRIP001  {   pSh->EndAction();
//STRIP001      pSh = (ViewShell*)pSh->GetNext();
//STRIP001  } while ( pSh != this );
//STRIP001
//STRIP001 }

//STRIP001 void ViewShell::ImplApplyViewOptions( const SwViewOption &rOpt )
//STRIP001 {
//STRIP001  ASSERT( !(*pOpt == rOpt), "ViewShell::ApplyViewOptions: ");
//STRIP001
//STRIP001  Window *pWin = GetWin();
//STRIP001  if( !pWin )
//STRIP001  {
//STRIP001      ASSERT( pWin, "ViewShell::ApplyViewOptions: no window" );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  BOOL bReformat   = FALSE;
//STRIP001
//STRIP001  if( pOpt->IsHidden() != rOpt.IsHidden() )
//STRIP001  {
//STRIP001      ((SwHiddenTxtFieldType*)pDoc->GetSysFldType( RES_HIDDENTXTFLD ))->
//STRIP001                                          SetHiddenFlag( !rOpt.IsHidden() );
//STRIP001      bReformat = TRUE;
//STRIP001  }
//STRIP001  if ( pOpt->IsShowHiddenPara() != rOpt.IsShowHiddenPara() )
//STRIP001  {
//STRIP001      SwHiddenParaFieldType* pFldType = (SwHiddenParaFieldType*)GetDoc()->
//STRIP001                                        GetSysFldType(RES_HIDDENPARAFLD);
//STRIP001      if( pFldType && pFldType->GetDepends() )
//STRIP001      {
//STRIP001          SwMsgPoolItem aHnt( RES_HIDDENPARA_PRINT );
//STRIP001          pFldType->Modify( &aHnt, 0);
//STRIP001      }
//STRIP001      bReformat = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // bReformat wird TRUE, wenn ...
//STRIP001  // - Feldnamen anzeigen oder nicht ...
//STRIP001  // ( - SwEndPortion muessen _nicht_ mehr generiert werden. )
//STRIP001  // - Das Window ist natuerlich was ganz anderes als der Drucker...
//STRIP001  bReformat = bReformat || pOpt->IsFldName()   != rOpt.IsFldName();
//STRIP001
//STRIP001  // Der Mapmode wird veraendert, Minima/Maxima werden von der UI beachtet
//STRIP001  if( pOpt->GetZoom() != rOpt.GetZoom() && !IsPreView() )
//STRIP001  {
//STRIP001      MapMode aMode( pWin->GetMapMode() );
//STRIP001      Fraction aNewFactor( rOpt.GetZoom(), 100 );
//STRIP001      aMode.SetScaleX( aNewFactor );
//STRIP001      aMode.SetScaleY( aNewFactor );
//STRIP001      pWin->SetMapMode( aMode );
//STRIP001      // Wenn kein ReferenzDevice (Drucker) zum Formatieren benutzt wird,
//STRIP001      // sondern der Bildschirm, muss bei Zoomfaktoraenderung neu formatiert
//STRIP001      // werden.
//STRIP001         if( IsBrowseMode() )
//STRIP001          bReformat = TRUE;
//STRIP001  }
//STRIP001
//STRIP001     if ( IsBrowseMode() && pOpt->IsPrtFormat() != rOpt.IsPrtFormat() )
//STRIP001         bReformat = TRUE;
//STRIP001
//STRIP001  if ( HasDrawView() || rOpt.IsGridVisible() )
//STRIP001  {
//STRIP001      if ( !HasDrawView() )
//STRIP001          MakeDrawView();
//STRIP001
//STRIP001      SwDrawView *pDView = Imp()->GetDrawView();
//STRIP001      if ( pDView->IsDragStripes() != rOpt.IsCrossHair() )
//STRIP001          pDView->SetDragStripes( rOpt.IsCrossHair() );
//STRIP001
//STRIP001      if ( pDView->IsGridSnap() != rOpt.IsSnap() )
//STRIP001          pDView->SetGridSnap( rOpt.IsSnap() );
//STRIP001
//STRIP001      if ( pDView->IsGridVisible() != rOpt.IsGridVisible() )
//STRIP001          pDView->SetGridVisible( rOpt.IsGridVisible() );
//STRIP001
//STRIP001      const Size &rSz = rOpt.GetSnapSize();
//STRIP001      pDView->SetGridCoarse( rSz );
//STRIP001
//STRIP001      const Size aFSize
//STRIP001          ( rSz.Width() ? rSz.Width() / (rOpt.GetDivisionX()+1) : 0,
//STRIP001            rSz.Height()? rSz.Height()/ (rOpt.GetDivisionY()+1) : 0);
//STRIP001      pDView->SetGridFine( aFSize );
//STRIP001      pDView->SetSnapGrid( aFSize );
//STRIP001      Fraction aSnGrWdtX(rSz.Width(), rOpt.GetDivisionX() + 1);
//STRIP001      Fraction aSnGrWdtY(rSz.Height(), rOpt.GetDivisionY() + 1);
//STRIP001      pDView->SetSnapGridWidth( aSnGrWdtX, aSnGrWdtY );
//STRIP001
//STRIP001      if ( pOpt->IsDraw() != rOpt.IsDraw() )
//STRIP001      {
//STRIP001          FASTBOOL bDraw = !rOpt.IsDraw();
//STRIP001          pDView->SetLineDraft( bDraw );
//STRIP001          pDView->SetFillDraft( bDraw );
//STRIP001          pDView->SetGrafDraft( bDraw );
//STRIP001          pDView->SetTextDraft( bDraw );
//STRIP001      }
//STRIP001      if ( pOpt->IsSolidMarkHdl() != rOpt.IsSolidMarkHdl() )
//STRIP001          pDView->SetSolidMarkHdl( rOpt.IsSolidMarkHdl() );
//STRIP001
//STRIP001          // it's a JOE interface !
//STRIP001      if ( pOpt->IsBigMarkHdl() != rOpt.IsBigMarkHdl() )
//STRIP001          pDView->SetMarkHdlSizePixel(rOpt.IsBigMarkHdl() ? 9 : 7);
//STRIP001  }
//STRIP001
//STRIP001  FASTBOOL bOnlineSpellChgd = pOpt->IsOnlineSpell() != rOpt.IsOnlineSpell();
//STRIP001
//STRIP001  *pOpt = rOpt;   // Erst jetzt werden die Options uebernommen.
//STRIP001  pOpt->SetUIOptions(rOpt);
//STRIP001
//STRIP001  pDoc->SetHTMLMode( 0 != ::binfilter::GetHtmlMode(pDoc->GetDocShell()) );
//STRIP001
//STRIP001  pWin->Invalidate();
//STRIP001  if ( bReformat )
//STRIP001  {
//STRIP001      // Es hilft alles nichts, wir muessen an alle CntntFrms ein
//STRIP001      // Prepare verschicken, wir formatieren neu:
//STRIP001      StartAction();
//STRIP001      Reformat();
//STRIP001      EndAction();
//STRIP001  }
//STRIP001
//STRIP001  if( bOnlineSpellChgd )
//STRIP001  {
//STRIP001      ViewShell *pSh = (ViewShell*)this->GetNext();
//STRIP001      BOOL bOnlineSpl = rOpt.IsOnlineSpell();
//STRIP001      while( pSh != this )
//STRIP001      {   pSh->pOpt->SetOnlineSpell( bOnlineSpl );
//STRIP001          Window *pTmpWin = pSh->GetWin();
//STRIP001          if( pTmpWin )
//STRIP001              pTmpWin->Invalidate();
//STRIP001          pSh = (ViewShell*)pSh->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::SetUIOptions()
|*
|*  Ersterstellung      OS 29.07.96
|*  Letzte Aenderung    OS 29.07.96
|*
******************************************************************************/

/*N*/ void ViewShell::SetUIOptions( const SwViewOption &rOpt )
/*N*/ {
/*N*/   pOpt->SetUIOptions(rOpt);
/*N*/   //the API-Flag of the view options is set but never reset
/*N*/   //it is required to set scroll bars in readonly documents
/*N*/   if(rOpt.IsStarOneSetting())
/*N*/       pOpt->SetStarOneSetting(TRUE);
/*N*/
/*N*/   pOpt->SetSymbolFont(rOpt.GetSymbolFont());
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::SetReadonly()
|*
|*  Ersterstellung      OS 05.09.96
|*  Letzte Aenderung    MA 12. Feb. 97
|*
******************************************************************************/

//STRIP001 void ViewShell::SetReadonlyOption(BOOL bSet)
//STRIP001 {
//STRIP001  //JP 01.02.99: bei ReadOnly Flag richtig abfragen und ggfs. neu
//STRIP001  //              formatieren; Bug 61335
//STRIP001
//STRIP001  // Schalten wir gerade von Readonly auf Bearbeiten um?
//STRIP001  if( bSet != pOpt->IsReadonly() )
//STRIP001  {
//STRIP001      // damit die Flags richtig erfragt werden koennen.
//STRIP001      pOpt->SetReadonly( FALSE );
//STRIP001
//STRIP001      BOOL bReformat = pOpt->IsFldName();
//STRIP001
//STRIP001      pOpt->SetReadonly( bSet );
//STRIP001
//STRIP001      if( bReformat )
//STRIP001      {
//STRIP001          StartAction();
//STRIP001          Reformat();
//STRIP001          if ( GetWin() )
//STRIP001              GetWin()->Invalidate();
//STRIP001          EndAction();
//STRIP001      }
//STRIP001      else if ( GetWin() )
//STRIP001          GetWin()->Invalidate();
//STRIP001      if( Imp()->IsAccessible() )
//STRIP001          Imp()->InvalidateAccessibleEditableState( sal_False );
//STRIP001  }
//STRIP001 }
/* -----------------------------2002/07/31 17:06------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ void  ViewShell::SetReadonlySelectionOption(sal_Bool bSet)
/*M*/ {
/*M*/     if( bSet != pOpt->IsSelectionInReadonly() )
/*M*/     {
/*M*/         pOpt->SetSelectionInReadonly(bSet);
/*M*/     }
/*M*/ }
/******************************************************************************
|*
|*  ViewShell::SetPrtFormatOption()
|*
|*  Ersterstellung      AMA 10. Sep. 97
|*  Letzte Aenderung    AMA 10. Sep. 97
|*
******************************************************************************/

//STRIP001 void ViewShell::SetPrtFormatOption( BOOL bSet )
//STRIP001 {
//STRIP001  pOpt->SetPrtFormat( bSet );
//STRIP001 }

/******************************************************************************
|*
|*  ViewShell::UISizeNotify()
|*
|*  Ersterstellung      MA 14. Jan. 97
|*  Letzte Aenderung    MA 14. Jan. 97
|*
******************************************************************************/


/*N*/ void ViewShell::UISizeNotify()
/*N*/ {
/*N*/   if ( bDocSizeChgd )
/*N*/   {
/*N*/       bDocSizeChgd = FALSE;
/*N*/       FASTBOOL bOld = bInSizeNotify;
/*N*/       bInSizeNotify = TRUE;
/*N*/       ::binfilter::SizeNotify( this, GetLayout()->Frm().SSize() );
/*N*/       bInSizeNotify = bOld;
/*N*/   }
/*N*/ }


/*N*/ BOOL ViewShell::IsBrowseMode() const
/*N*/ {
/*N*/   return GetDoc()->IsBrowseMode();
/*N*/ }

//STRIP001 void ViewShell::SetRestoreActions(USHORT nSet)
//STRIP001 {
//STRIP001  DBG_ASSERT(!GetRestoreActions()||!nSet, "mehrfaches Restore der Actions ?")
//STRIP001  Imp()->SetRestoreActions(nSet);
//STRIP001 }
//STRIP001 USHORT   ViewShell::GetRestoreActions() const
//STRIP001 {
//STRIP001  return Imp()->GetRestoreActions();
//STRIP001 }
//STRIP001
//STRIP001 BOOL ViewShell::IsNewLayout() const
//STRIP001 {
//STRIP001  return GetLayout()->IsNewLayout();
//STRIP001 }

//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::accessibility::XAccessible > ViewShell::CreateAccessible()
//STRIP001 {
//STRIP001  using namespace ::com::sun::star::uno;
//STRIP001  using namespace ::com::sun::star::accessibility;
//STRIP001  Reference< XAccessible > xAcc;
//STRIP001
//STRIP001  SwDoc *pDoc = GetDoc();
//STRIP001
//STRIP001  // We require a layout and an XModel to be accessible.
//STRIP001  ASSERT( pDoc->GetRootFrm(), "no layout, no access" );
//STRIP001  ASSERT( GetWin(), "no window, no access" );
//STRIP001
//STRIP001  if( pDoc->GetRootFrm() && GetWin() )
//STRIP001      xAcc = Imp()->GetAccessibleMap().GetDocumentView();
//STRIP001
//STRIP001  return xAcc;
//STRIP001 }

//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001     ::com::sun::star::accessibility::XAccessible >
//STRIP001 ViewShell::CreateAccessiblePreview()
//STRIP001 {
//STRIP001  using ::com::sun::star::uno::Reference;
//STRIP001  using ::com::sun::star::accessibility::XAccessible;
//STRIP001
//STRIP001     DBG_ASSERT( IsPreView(),
//STRIP001                 "Can't create accessible preview for non-preview ViewShell" );
//STRIP001
//STRIP001  // We require a layout and an XModel to be accessible.
//STRIP001  ASSERT( pDoc->GetRootFrm(), "no layout, no access" );
//STRIP001  ASSERT( GetWin(), "no window, no access" );
//STRIP001
//STRIP001     // OD 15.01.2003 #103492# - add condition <IsPreView()>
//STRIP001     if ( IsPreView() && pDoc->GetRootFrm() && GetWin() )
//STRIP001     {
//STRIP001         // OD 14.01.2003 #103492# - adjustment for new method signature
//STRIP001         return Imp()->GetAccessibleMap().GetDocumentPreview(
//STRIP001                     PagePreviewLayout()->maPrevwPages,
//STRIP001                     GetWin()->GetMapMode().GetScaleX(),
//STRIP001                     pDoc->GetRootFrm()->GetPageByPageNum( PagePreviewLayout()->mnSelectedPageNum ),
//STRIP001                     PagePreviewLayout()->maWinSize );
//STRIP001     }
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 void ViewShell::InvalidateAccessibleFocus()
//STRIP001 {
//STRIP001  if( Imp()->IsAccessible() )
//STRIP001      Imp()->GetAccessibleMap().InvalidateFocus();
//STRIP001 }

/* -----------------------------06.05.2002 13:23------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void ViewShell::ApplyAccessiblityOptions(SvtAccessibilityOptions& rAccessibilityOptions)
/*N*/ {
/*N*/     if(pOpt->IsPagePreview() && !rAccessibilityOptions.GetIsForPagePreviews())
/*N*/     {
/*?*/         pAccOptions->SetAlwaysAutoColor(sal_False);
/*?*/         pAccOptions->SetStopAnimatedGraphics(sal_False);
/*?*/         pAccOptions->SetStopAnimatedText(sal_False);
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         pAccOptions->SetAlwaysAutoColor(rAccessibilityOptions.GetIsAutomaticFontColor());
/*N*/         pAccOptions->SetStopAnimatedGraphics(! rAccessibilityOptions.GetIsAllowAnimatedGraphics());
/*N*/         pAccOptions->SetStopAnimatedText(! rAccessibilityOptions.GetIsAllowAnimatedText());
/*N*/
/*N*/         if(pOpt->IsReadonly())
/*N*/             pOpt->SetSelectionInReadonly(rAccessibilityOptions.IsSelectionInReadonly());
/*N*/     }
/*N*/ }
/*-----------------07.03.2003 12:38-----------------
 *
 * --------------------------------------------------*/
//STRIP001 sal_Bool ViewShell::IsUseVirtualDevice() const
//STRIP001 {
//STRIP001     return GetDoc()->IsUseVirtualDevice();
//STRIP001 }
/*-----------------07.03.2003 12:38-----------------
 *
 * --------------------------------------------------*/
//STRIP001 void ViewShell::SetUseVirtualDevice( sal_Bool bNew )
//STRIP001 {
//STRIP001     // this sets the flag at the document and calls PrtDataChanged
//STRIP001     GetDoc()->SetUseVirtualDevice( bNew );
//STRIP001 }

}
