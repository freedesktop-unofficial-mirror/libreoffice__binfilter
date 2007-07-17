/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_viewimp.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:03:01 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


#pragma hdrstop

#include "scrrect.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"
#include "crsrsh.hxx"
#include "rootfrm.hxx"
#include "pagefrm.hxx"
#include "viewimp.hxx"
#include "viewopt.hxx"
#include "layact.hxx"
#include "swregion.hxx"
#include "dview.hxx"
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifdef ACCESSIBLE_LAYOUT
#endif

// OD 12.12.2002 #103492#
namespace binfilter {

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
#if 0
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
#endif
        DBG_ERROR("Strip!");
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
/*N*/ #ifdef ACCESSIBLE_LAYOUT
/*N*/ #endif
/*N*/ {
#if 0
/*N*/   bResetXorVisibility = bShowHdlPaint =
/*N*/   bResetHdlHiddenPaint = bScrolled =
/*N*/   bPaintInScroll = bSmoothUpdate = bStopSmooth = bStopPrt = FALSE;
/*N*/   bFirstPageInvalid = bScroll = bNextScroll = TRUE;
/*N*/
/*N*/   aScrollTimer.SetTimeout( 1500 );
/*N*/   aScrollTimer.SetTimeoutHdl( LINK( this, SwViewImp, RefreshScrolledHdl));
/*N*/   aScrollTimer.Stop();
#endif
        DBG_ERROR("Strip!");
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
#if 0
/*N*/
/*N*/     // OD 12.12.2002 #103492#
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
#endif
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
#if 0
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
#endif
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::GetRetoucheColor()
|*
|*  Ersterstellung      MA 24. Jun. 98
|*  Letzte Aenderung    MA 24. Jun. 98
|*
******************************************************************************/


/** create page preview layout

    OD 12.12.2002 #103492#

    @author OD
*/


/*N*/ void SwViewImp::DisposeAccessible( const SwFrm *pFrm,
/*N*/                                  const SdrObject *pObj,
/*N*/                                  sal_Bool bRecursive )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void SwViewImp::MoveAccessible( const SwFrm *pFrm, const SdrObject *pObj,
/*N*/                               const SwRect& rOldFrm )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void SwViewImp::InvalidateAccessibleFrmContent( const SwFrm *pFrm )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

// OD 15.01.2003 #103492# - method signature change due to new page preview functionality
}
