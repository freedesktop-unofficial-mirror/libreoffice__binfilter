/*************************************************************************
 *
 *  $RCSfile: sw_viewimp.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:44:43 $
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

#include "scrrect.hxx"
#include "doc.hxx"
#include "crsrsh.hxx"
#include "rootfrm.hxx"
#include "pagefrm.hxx"
#include "viewimp.hxx"
#include "errhdl.hxx"
#include "viewopt.hxx"
#include "flyfrm.hxx"
#include "frmfmt.hxx"
#include "layact.hxx"
#include "swregion.hxx"
#include "dflyobj.hxx"
#include "dview.hxx"
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifdef ACCESSIBLE_LAYOUT
#ifndef _ACCMAP_HXX
#include <accmap.hxx>
#endif
#endif

// OD 12.12.2002 #103492#
#ifndef _PAGEPREVIEWLAYOUT_HXX
#include <pagepreviewlayout.hxx>
#endif

/*************************************************************************
|*
|*  SwViewImp::Init()
|*
|*  Ersterstellung      MA 25. Jul. 94
|*  Letzte Aenderung    MA 03. Nov. 95
|*
|*************************************************************************/

/*N*/ void SwViewImp::Init( const SwViewOption *pNewOpt )
/*N*/ {
/*N*/   ASSERT( pDrawView, "SwViewImp::Init without DrawView" );
/*N*/   //Jetzt die PageView erzeugen wenn sie noch nicht existiert.
/*N*/   SwRootFrm *pRoot = pSh->GetDoc()->GetRootFrm();
/*N*/   if ( !pSdrPageView )
/*N*/   {
/*N*/       if ( !pRoot->GetDrawPage() )
/*?*/           pRoot->SetDrawPage( pSh->GetDoc()->GetDrawModel()->GetPage( 0 ) );
/*N*/
/*N*/       pRoot->GetDrawPage()->SetSize( pRoot->Frm().SSize() );
/*N*/       pSdrPageView = pDrawView->ShowPage( pRoot->GetDrawPage(), Point());
/*N*/         // OD 26.06.2003 #108784# - notify drawing page view about invisible
/*N*/         // layers.
/*N*/         pSh->GetDoc()->NotifyInvisibleLayers( *pSdrPageView );
/*N*/   }
/*N*/   pDrawView->SetDragStripes( pNewOpt->IsCrossHair() );
/*N*/   pDrawView->SetGridSnap( pNewOpt->IsSnap() );
/*N*/   pDrawView->SetGridVisible( pNewOpt->IsGridVisible() );
/*N*/   const Size &rSz = pNewOpt->GetSnapSize();
/*N*/   pDrawView->SetGridCoarse( rSz );
/*N*/   const Size aFSize
/*N*/           ( rSz.Width() ? rSz.Width() /Max(short(1),pNewOpt->GetDivisionX()):0,
/*N*/             rSz.Height()? rSz.Height()/Max(short(1),pNewOpt->GetDivisionY()):0);
/*N*/   pDrawView->SetGridFine( aFSize );
/*N*/   pDrawView->SetSnapGrid( aFSize );
/*N*/   Fraction aSnGrWdtX(rSz.Width(), pNewOpt->GetDivisionX() + 1);
/*N*/   Fraction aSnGrWdtY(rSz.Height(), pNewOpt->GetDivisionY() + 1);
/*N*/   pDrawView->SetSnapGridWidth( aSnGrWdtX, aSnGrWdtY );
/*N*/
/*N*/   //Ersatzdarstellung
/*N*/   FASTBOOL bDraw = !pNewOpt->IsDraw();
/*N*/   pDrawView->SetLineDraft( bDraw );
/*N*/   pDrawView->SetFillDraft( bDraw );
/*N*/   pDrawView->SetGrafDraft( bDraw );
/*N*/   pDrawView->SetTextDraft( bDraw );
/*N*/
/*N*/   if ( pRoot->Frm().HasArea() )
/*N*/       pDrawView->SetWorkArea( pRoot->Frm().SVRect() );
/*N*/
/*N*/   if ( GetShell()->IsPreView() )
/*?*/       pDrawView->SetAnimationEnabled( FALSE );
/*N*/
/*N*/   pDrawView->SetUseIncompatiblePathCreateInterface( FALSE );
/*N*/   pDrawView->SetSolidMarkHdl(pNewOpt->IsSolidMarkHdl());
/*N*/
/*N*/   // it's a JOE interface !
/*N*/   pDrawView->SetMarkHdlSizePixel(pNewOpt->IsBigMarkHdl() ? 9 : 7);
/*N*/ }

/*************************************************************************
|*
|*  SwViewImp::SwViewImp()  CTor fuer die Core-Internas
|*
|*  Ersterstellung      MA 25. Jul. 94
|*  Letzte Aenderung    MA 06. Sep. 96
|*
|*************************************************************************/

/*N*/ SwViewImp::SwViewImp( ViewShell *pParent ) :
/*N*/   pSh( pParent ),
/*N*/   pFirstVisPage( 0 ),
/*N*/   pRegion( 0 ),
/*N*/   pScrollRects( 0 ),
/*N*/   pScrolledArea( 0 ),
/*N*/   pLayAct( 0 ),
/*N*/   pIdleAct( 0 ),
/*N*/   pSdrPageView( 0 ),
/*N*/   pDrawView( 0 ),
/*N*/     nRestoreActions( 0 ) //STRIP001 ,
/*N*/     // OD 12.12.2002 #103492#
//STRIP001 /*N*/     mpPgPrevwLayout( 0 )
/*N*/ #ifdef ACCESSIBLE_LAYOUT
//STRIP001 /*N*/    ,pAccMap( 0 )
/*N*/ #endif
/*N*/ {
/*N*/   bResetXorVisibility = bShowHdlPaint =
/*N*/   bResetHdlHiddenPaint = bScrolled =
/*N*/   bPaintInScroll = bSmoothUpdate = bStopSmooth = bStopPrt = FALSE;
/*N*/   bFirstPageInvalid = bScroll = bNextScroll = TRUE;
/*N*/
/*N*/   aScrollTimer.SetTimeout( 1500 );
/*N*/   aScrollTimer.SetTimeoutHdl( LINK( this, SwViewImp, RefreshScrolledHdl));
/*N*/   aScrollTimer.Stop();
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::~SwViewImp()
|*
|*  Ersterstellung      MA 25. Jul. 94
|*  Letzte Aenderung    MA 16. Dec. 94
|*
******************************************************************************/

/*N*/ SwViewImp::~SwViewImp()
/*N*/ {
/*N*/ #ifdef ACCESSIBLE_LAYOUT
//STRIP001 /*N*/    delete pAccMap;
/*N*/ #endif
/*N*/
/*N*/     // OD 12.12.2002 #103492#
//STRIP001 /*N*/     delete mpPgPrevwLayout;
/*N*/
/*N*/   //JP 29.03.96: nach ShowPage muss auch HidePage gemacht werden!!!
/*N*/   if( pDrawView )
/*N*/       pDrawView->HidePage( pSdrPageView );
/*N*/
/*N*/   delete pDrawView;
/*N*/
/*N*/   DelRegions();
/*N*/   delete pScrolledArea;
/*N*/
/*N*/   ASSERT( !pLayAct, "Have action for the rest of your life." );
/*N*/   ASSERT( !pIdleAct,"Be idle for the rest of your life." );
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::DelRegions()
|*
|*  Ersterstellung      MA 14. Apr. 94
|*  Letzte Aenderung    MA 14. Apr. 94
|*
******************************************************************************/

/*N*/ void SwViewImp::DelRegions()
/*N*/ {
/*N*/   DELETEZ(pRegion);
/*N*/   DELETEZ(pScrollRects);
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::AddPaintRect()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 27. Jul. 94
|*
******************************************************************************/

/*N*/ BOOL SwViewImp::AddPaintRect( const SwRect &rRect )
/*N*/ {
/*N*/   if ( rRect.IsOver( pSh->VisArea() ) )
/*N*/   {
/*?*/       if ( !pRegion )
/*?*/           pRegion = new SwRegionRects( pSh->VisArea() );
/*?*/       (*pRegion) -= rRect;
/*?*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }


/******************************************************************************
|*
|*  ViewImp::CheckWaitCrsr()
|*
|*  Ersterstellung      MA 10. Aug. 94
|*  Letzte Aenderung    MA 10. Aug. 94
|*
******************************************************************************/

/*N*/ void SwViewImp::CheckWaitCrsr()
/*N*/ {
/*N*/   if ( pLayAct )
/*N*/       pLayAct->CheckWaitCrsr();
/*N*/ }

/******************************************************************************
|*
|*  ViewImp::IsCalcLayoutProgress()
|*
|*  Ersterstellung      MA 12. Aug. 94
|*  Letzte Aenderung    MA 12. Aug. 94
|*
******************************************************************************/

/*N*/ BOOL SwViewImp::IsCalcLayoutProgress() const
/*N*/ {
/*N*/   if ( pLayAct )
/*N*/       return pLayAct->IsCalcLayout();
/*N*/   return FALSE;
/*N*/ }

/******************************************************************************
|*
|*  ViewImp::IsUpdateExpFlds()
|*
|*  Ersterstellung      MA 28. Mar. 96
|*  Letzte Aenderung    MA 28. Mar. 96
|*
******************************************************************************/

/*N*/ BOOL SwViewImp::IsUpdateExpFlds()
/*N*/ {
/*N*/   if ( pLayAct && pLayAct->IsCalcLayout() )
/*N*/   {
/*?*/       pLayAct->SetUpdateExpFlds();
/*?*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }


/******************************************************************************
|*
|*  SwViewImp::SetFirstVisPage(), ImplGetFirstVisPage();
|*
|*  Ersterstellung      MA 21. Sep. 93
|*  Letzte Aenderung    MA 08. Mar. 94
|*
******************************************************************************/

/*N*/ void SwViewImp::SetFirstVisPage()
/*N*/ {
/*N*/   if ( pSh->bDocSizeChgd && pSh->VisArea().Top() > pSh->GetLayout()->Frm().Height() )
/*N*/   {
/*N*/       //Wir stecken in einer Action und die VisArea sitzt wegen
/*N*/       //Loeschoperationen hinter der erste sichtbaren Seite.
/*N*/       //Damit nicht zu heftig Formatiert wird, liefern wir die letzte Seite
/*N*/       //zurueck.
/*?*/       pFirstVisPage = (SwPageFrm*)pSh->GetLayout()->Lower();
/*?*/       while ( pFirstVisPage && pFirstVisPage->GetNext() )
/*?*/           pFirstVisPage = (SwPageFrm*)pFirstVisPage->GetNext();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwPageFrm *pPage = (SwPageFrm*)pSh->GetLayout()->Lower();
/*N*/       while ( pPage && !pPage->Frm().IsOver( pSh->VisArea() ) )
/*N*/           pPage = (SwPageFrm*)pPage->GetNext();
/*N*/       pFirstVisPage = pPage ? pPage : (SwPageFrm*)pSh->GetLayout()->Lower();
/*N*/   }
/*N*/   bFirstPageInvalid = FALSE;
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::MakeDrawView();
|*
|*  Ersterstellung      AMA 01. Nov. 95
|*  Letzte Aenderung    AMA 01. Nov. 95
|*
******************************************************************************/

/*N*/ void SwViewImp::MakeDrawView()
/*N*/ {
/*N*/   if( !GetShell()->GetDoc()->GetDrawModel() )
/*?*/       GetShell()->GetDoc()->_MakeDrawModel();
/*N*/   else
/*N*/   {
/*N*/       if ( !pDrawView )
/*N*/       {
/*N*/           pDrawView = new SwDrawView( *this,
/*N*/                       GetShell()->GetDoc()->GetDrawModel(),
/*N*/                           GetShell()->GetWin() ?
/*N*/                           GetShell()->GetWin() :
/*N*/                           (OutputDevice*)GetShell()->GetDoc()->GetPrt() );
/*N*/       }
/*N*/       GetDrawView()->SetActiveLayer( XubString::CreateFromAscii(
/*N*/                           RTL_CONSTASCII_STRINGPARAM( "Heaven" ) ) );
/*N*/       Init( GetShell()->GetViewOptions() );
/*N*/   }
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::GetRetoucheColor()
|*
|*  Ersterstellung      MA 24. Jun. 98
|*  Letzte Aenderung    MA 24. Jun. 98
|*
******************************************************************************/

//STRIP001 Color SwViewImp::GetRetoucheColor() const
//STRIP001 {
//STRIP001     Color aRet( COL_TRANSPARENT );
//STRIP001  const ViewShell &rSh = *GetShell();
//STRIP001  if ( rSh.GetWin() )
//STRIP001  {
//STRIP001      if ( rSh.GetDoc()->IsBrowseMode() &&
//STRIP001           COL_TRANSPARENT != rSh.GetViewOptions()->GetRetoucheColor().GetColor() )
//STRIP001          aRet = rSh.GetViewOptions()->GetRetoucheColor();
//STRIP001         else if(rSh.GetViewOptions()->IsPagePreview()  &&
//STRIP001                     !SW_MOD()->GetAccessibilityOptions().GetIsForPagePreviews())
//STRIP001             aRet.SetColor(COL_WHITE);
//STRIP001         else
//STRIP001             aRet = SwViewOption::GetDocColor();
//STRIP001     }
//STRIP001  return aRet;
//STRIP001 }

/** create page preview layout

    OD 12.12.2002 #103492#

    @author OD
*/
//STRIP001 void SwViewImp::InitPagePreviewLayout()
//STRIP001 {
//STRIP001     ASSERT( pSh->GetLayout(), "no layout - page preview layout can not be created.");
//STRIP001     if ( pSh->GetLayout() )
//STRIP001         mpPgPrevwLayout = new SwPagePreviewLayout( *pSh, *(pSh->GetLayout()) );
//STRIP001 }

//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001 void SwViewImp::UpdateAccessible()
//STRIP001 {
//STRIP001  // We require a layout and an XModel to be accessible.
//STRIP001  SwDoc *pDoc = GetShell()->GetDoc();
//STRIP001  Window *pWin = GetShell()->GetWin();
//STRIP001  ASSERT( pDoc->GetRootFrm(), "no layout, no access" );
//STRIP001  ASSERT( pWin, "no window, no access" );
//STRIP001
//STRIP001  if( IsAccessible() && pDoc->GetRootFrm() && pWin )
//STRIP001      GetAccessibleMap().GetDocumentView();
//STRIP001 }

/*N*/ void SwViewImp::DisposeAccessible( const SwFrm *pFrm,
/*N*/                                  const SdrObject *pObj,
/*N*/                                  sal_Bool bRecursive )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*N*/    ASSERT( !pFrm || pFrm->IsAccessibleFrm(), "frame is not accessible" );
//STRIP001 /*N*/    ViewShell *pVSh = GetShell();
//STRIP001 /*N*/    ViewShell *pTmp = pVSh;
//STRIP001 /*N*/    do
//STRIP001 /*N*/    {
//STRIP001 /*N*/        if( pTmp->Imp()->IsAccessible() )
//STRIP001 /*N*/            pTmp->Imp()->GetAccessibleMap().Dispose( pFrm, pObj, bRecursive );
//STRIP001 /*N*/        pTmp = (ViewShell *)pTmp->GetNext();
//STRIP001 /*N*/    } while ( pTmp != pVSh );
/*N*/ }

/*N*/ void SwViewImp::MoveAccessible( const SwFrm *pFrm, const SdrObject *pObj,
/*N*/                               const SwRect& rOldFrm )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*N*/    ASSERT( !pFrm || pFrm->IsAccessibleFrm(), "frame is not accessible" );
//STRIP001 /*N*/    ViewShell *pVSh = GetShell();
//STRIP001 /*N*/    ViewShell *pTmp = pVSh;
//STRIP001 /*N*/    do
//STRIP001 /*N*/    {
//STRIP001 /*N*/        if( pTmp->Imp()->IsAccessible() )
//STRIP001 /*N*/            pTmp->Imp()->GetAccessibleMap().InvalidatePosOrSize( pFrm, pObj,
//STRIP001 /*N*/                                                                 rOldFrm );
//STRIP001 /*N*/        pTmp = (ViewShell *)pTmp->GetNext();
//STRIP001 /*N*/    } while ( pTmp != pVSh );
/*N*/ }

/*N*/ void SwViewImp::InvalidateAccessibleFrmContent( const SwFrm *pFrm )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*N*/    ASSERT( pFrm->IsAccessibleFrm(), "frame is not accessible" );
//STRIP001 /*N*/    ViewShell *pVSh = GetShell();
//STRIP001 /*N*/    ViewShell *pTmp = pVSh;
//STRIP001 /*N*/    do
//STRIP001 /*N*/    {
//STRIP001 /*N*/        if( pTmp->Imp()->IsAccessible() )
//STRIP001 /*N*/            pTmp->Imp()->GetAccessibleMap().InvalidateContent( pFrm );
//STRIP001 /*N*/        pTmp = (ViewShell *)pTmp->GetNext();
//STRIP001 /*N*/    } while ( pTmp != pVSh );
/*N*/ }

//STRIP001 void SwViewImp::InvalidateAccessibleCursorPosition( const SwFrm *pFrm )
//STRIP001 {
//STRIP001  if( IsAccessible() )
//STRIP001      GetAccessibleMap().InvalidateCursorPosition( pFrm );
//STRIP001 }
//STRIP001
//STRIP001 void SwViewImp::InvalidateAccessibleEditableState( sal_Bool bAllShells,
//STRIP001                                                 const SwFrm *pFrm    )
//STRIP001 {
//STRIP001  if( bAllShells )
//STRIP001  {
//STRIP001      ViewShell *pVSh = GetShell();
//STRIP001      ViewShell *pTmp = pVSh;
//STRIP001      do
//STRIP001      {
//STRIP001          if( pTmp->Imp()->IsAccessible() )
//STRIP001              pTmp->Imp()->GetAccessibleMap().InvalidateStates( ACC_STATE_EDITABLE, pFrm );
//STRIP001          pTmp = (ViewShell *)pTmp->GetNext();
//STRIP001      } while ( pTmp != pVSh );
//STRIP001  }
//STRIP001  else if( IsAccessible() )
//STRIP001  {
//STRIP001      GetAccessibleMap().InvalidateStates( ACC_STATE_EDITABLE, pFrm );
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void SwViewImp::InvalidateAccessibleOpaqueState()
//STRIP001 {
//STRIP001  ViewShell *pVSh = GetShell();
//STRIP001  ViewShell *pTmp = pVSh;
//STRIP001  do
//STRIP001  {
//STRIP001      if( pTmp->Imp()->IsAccessible() )
//STRIP001          pTmp->Imp()->GetAccessibleMap().InvalidateStates( ACC_STATE_OPAQUE );
//STRIP001      pTmp = (ViewShell *)pTmp->GetNext();
//STRIP001  } while ( pTmp != pVSh );
//STRIP001 }
//STRIP001
//STRIP001 void SwViewImp::InvalidateAccessibleRelationSet( const SwFlyFrm *pMaster,
//STRIP001                                                  const SwFlyFrm *pFollow )
//STRIP001 {
//STRIP001  ViewShell *pVSh = GetShell();
//STRIP001  ViewShell *pTmp = pVSh;
//STRIP001  do
//STRIP001  {
//STRIP001      if( pTmp->Imp()->IsAccessible() )
//STRIP001          pTmp->Imp()->GetAccessibleMap().InvalidateRelationSet( pMaster,
//STRIP001                                                                    pFollow );
//STRIP001      pTmp = (ViewShell *)pTmp->GetNext();
//STRIP001  } while ( pTmp != pVSh );
//STRIP001 }
//STRIP001
// OD 15.01.2003 #103492# - method signature change due to new page preview functionality
//STRIP001 void SwViewImp::UpdateAccessiblePreview( const std::vector<PrevwPage*>& _rPrevwPages,
//STRIP001                                          const Fraction&  _rScale,
//STRIP001                                          const SwPageFrm* _pSelectedPageFrm,
//STRIP001                                          const Size&      _rPrevwWinSize )
//STRIP001 {
//STRIP001     if( IsAccessible() )
//STRIP001         GetAccessibleMap().UpdatePreview( _rPrevwPages, _rScale,
//STRIP001                                           _pSelectedPageFrm, _rPrevwWinSize );
//STRIP001 }
//STRIP001
//STRIP001 void SwViewImp::InvalidateAccessiblePreViewSelection( sal_uInt16 nSelPage )
//STRIP001 {
//STRIP001     if( IsAccessible() )
//STRIP001         GetAccessibleMap().InvalidatePreViewSelection( nSelPage );
//STRIP001 }
//STRIP001
//STRIP001 SwAccessibleMap *SwViewImp::CreateAccessibleMap()
//STRIP001 {
//STRIP001  ASSERT( !pAccMap, "accessible map exists" )
//STRIP001  pAccMap = new SwAccessibleMap( GetShell() );
//STRIP001  return pAccMap;
//STRIP001 }
//STRIP001
//STRIP001 void SwViewImp::FireAccessibleEvents()
//STRIP001 {
//STRIP001  if( IsAccessible() )
//STRIP001      GetAccessibleMap().FireEvents();
//STRIP001 }
//STRIP001
//STRIP001 IMPL_LINK(SwViewImp, SetStopPrt, void *, EMPTYARG)
//STRIP001 {
//STRIP001  bStopPrt = TRUE;
//STRIP001
//STRIP001  return 0;
//STRIP001 }
//STRIP001
//STRIP001 #endif
