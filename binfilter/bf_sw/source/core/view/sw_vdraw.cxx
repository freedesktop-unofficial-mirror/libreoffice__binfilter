/*************************************************************************
 *
 *  $RCSfile: sw_vdraw.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:16:02 $
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

// auto strip #ifndef _SVDMODEL_HXX //autogen
// auto strip #include <bf_svx/svdmodel.hxx>
// auto strip #endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
// auto strip #ifndef _XOUTX_HXX //autogen
// auto strip #include <bf_svx/xoutx.hxx>
// auto strip #endif
// auto strip #ifndef _SHL_HXX
// auto strip #include <tools/shl.hxx>
// auto strip #endif
// auto strip #ifndef _SWMODULE_HXX
// auto strip #include <swmodule.hxx>
// auto strip #endif
// auto strip #ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
// auto strip #include <svtools/accessibilityoptions.hxx>
// auto strip #endif

#ifndef _SVDPAGV_HXX //autogen
#include <bf_svx/svdpagv.hxx>
#endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif

/// OD 29.08.2002 #102450#
/// include <bf_svx/svdoutl.hxx>
// auto strip #ifndef _SVDOUTL_HXX
// auto strip #include <bf_svx/svdoutl.hxx>
// auto strip #endif

#ifndef PRODUCT
// auto strip #ifndef _SVX_FMGLOB_HXX
// auto strip #include <bf_svx/fmglob.hxx>
// auto strip #endif
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "fesh.hxx"
#include "doc.hxx"
// auto strip #include "pagefrm.hxx"
// auto strip #include "rootfrm.hxx"
#include "viewimp.hxx"
// auto strip #include "dflyobj.hxx"
// auto strip #include "viewopt.hxx"
#include "dcontact.hxx"
#include "dview.hxx"
#include "flyfrm.hxx"
namespace binfilter {


/*************************************************************************
|*
|*  SwSaveHdl
|*
|*  Ersterstellung      MA 14. Feb. 95
|*  Letzte Aenderung    MA 02. Jun. 98
|*
|*************************************************************************/
//STRIP001 SwSaveHdl::SwSaveHdl( SwViewImp *pI ) :
//STRIP001  pImp( pI ),
//STRIP001  bXorVis( FALSE )
//STRIP001 {
//STRIP001  if ( pImp->HasDrawView() )
//STRIP001  {
//STRIP001      bXorVis = pImp->GetDrawView()->IsShownXorVisible( pImp->GetShell()->GetOut());
//STRIP001      if ( bXorVis )
//STRIP001          pImp->GetDrawView()->HideShownXor( pImp->GetShell()->GetOut() );
//STRIP001  }
//STRIP001 }


//STRIP001 SwSaveHdl::~SwSaveHdl()
//STRIP001 {
//STRIP001  if ( bXorVis )
//STRIP001      pImp->GetDrawView()->ShowShownXor( pImp->GetShell()->GetOut() );
//STRIP001 }


/*************************************************************************
|*
|*  SwViewImp::StartAction(), EndAction()
|*
|*  Ersterstellung      MA 14. Feb. 95
|*  Letzte Aenderung    MA 14. Sep. 98
|*
|*************************************************************************/


/*N*/ void SwViewImp::StartAction()
/*N*/ {
/*N*/   if ( HasDrawView() )
/*N*/   {
/*N*/       SET_CURR_SHELL( GetShell() );
/*N*/       if ( pSh->ISA(SwFEShell) )
/*N*/           ((SwFEShell*)pSh)->HideChainMarker();   //Kann sich geaendert haben
/*N*/       bResetXorVisibility = GetDrawView()->IsShownXorVisible( GetShell()->GetOut());
/*N*/       GetDrawView()->HideShownXor( GetShell()->GetOut() );
/*N*/   }
/*N*/ }



/*N*/ void SwViewImp::EndAction()
/*N*/ {
/*N*/   if ( HasDrawView() )
/*N*/   {
/*N*/       SET_CURR_SHELL( GetShell() );
/*N*/       if ( bResetXorVisibility )
/*?*/           GetDrawView()->ShowShownXor( GetShell()->GetOut() );
/*N*/       if ( pSh->ISA(SwFEShell) )
/*N*/           ((SwFEShell*)pSh)->SetChainMarker();    //Kann sich geaendert haben
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwViewImp::LockPaint(), UnlockPaint()
|*
|*  Ersterstellung      MA 11. Jun. 96
|*  Letzte Aenderung    MA 11. Jun. 96
|*
|*************************************************************************/


//STRIP001 void SwViewImp::LockPaint()
//STRIP001 {
//STRIP001  if ( HasDrawView() )
//STRIP001  {
//STRIP001      bShowHdlPaint = GetDrawView()->IsMarkHdlShown();
//STRIP001      if ( bShowHdlPaint )
//STRIP001          GetDrawView()->HideMarkHdl( GetShell()->GetOut() );
//STRIP001      bResetHdlHiddenPaint = !GetDrawView()->IsMarkHdlHidden();
//STRIP001      GetDrawView()->SetMarkHdlHidden( TRUE );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      bShowHdlPaint = FALSE;
//STRIP001      bResetHdlHiddenPaint = FALSE;
//STRIP001  }
//STRIP001 }



//STRIP001 void SwViewImp::UnlockPaint()
//STRIP001 {
//STRIP001  if ( bResetHdlHiddenPaint )
//STRIP001      GetDrawView()->SetMarkHdlHidden( FALSE );
//STRIP001  if ( bShowHdlPaint )
//STRIP001      GetDrawView()->ShowMarkHdl( GetShell()->GetOut() );
//STRIP001 }


/*************************************************************************
|*
|*  SwViewImp::PaintLayer(), PaintDispatcher()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    AMA 04. Jun. 98
|*
|*************************************************************************/
// OD 29.08.2002 #102450#
// add 3rd paramter <const Color* pPageBackgrdColor> for setting this
// color as the background color at the outliner of the draw view.
// OD 09.12.2002 #103045# - add 4th parameter for the horizontal text direction
// of the page in order to set the default horizontal text direction at the
// outliner of the draw view for painting layers <hell> and <heaven>.
// OD 25.06.2003 #108784# - correct type of 1st parameter
//STRIP001 void SwViewImp::PaintLayer( const SdrLayerID _nLayerID,
//STRIP001                             const SwRect& _rRect,
//STRIP001                             const Color* _pPageBackgrdColor,
//STRIP001                             const bool _bIsPageRightToLeft ) const
//STRIP001 {
//STRIP001     if ( HasDrawView() )
//STRIP001  {
//STRIP001         //change the draw mode in high contrast mode
//STRIP001         OutputDevice* pOutDev = GetShell()->GetOut();
//STRIP001         ULONG nOldDrawMode = pOutDev->GetDrawMode();
//STRIP001         if( GetShell()->GetWin() &&
//STRIP001             Application::GetSettings().GetStyleSettings().GetHighContrastMode() &&
//STRIP001             (!GetShell()->IsPreView()||SW_MOD()->GetAccessibilityOptions().GetIsForPagePreviews()))
//STRIP001         {
//STRIP001             pOutDev->SetDrawMode( nOldDrawMode | DRAWMODE_SETTINGSLINE | DRAWMODE_SETTINGSFILL |
//STRIP001                                 DRAWMODE_SETTINGSTEXT | DRAWMODE_SETTINGSGRADIENT );
//STRIP001         }
//STRIP001
//STRIP001         // OD 29.08.2002 #102450#
//STRIP001         // For correct handling of accessibility, high contrast, the page background
//STRIP001         // color is set as the background color at the outliner of the draw view.
//STRIP001         // Only necessary for the layers hell and heaven
//STRIP001         Color aOldOutlinerBackgrdColor;
//STRIP001         // OD 09.12.2002 #103045# - set default horizontal text direction on
//STRIP001         // painting <hell> or <heaven>.
//STRIP001         EEHorizontalTextDirection aOldEEHoriTextDir;
//STRIP001         if ( (_nLayerID == GetShell()->GetDoc()->GetHellId()) ||
//STRIP001              (_nLayerID == GetShell()->GetDoc()->GetHeavenId()) )
//STRIP001         {
//STRIP001             ASSERT( _pPageBackgrdColor,
//STRIP001                     "incorrect usage of SwViewImp::PaintLayer: pPageBackgrdColor have to be set for painting layer <hell> or <heaven>");
//STRIP001             if ( _pPageBackgrdColor )
//STRIP001             {
//STRIP001                 aOldOutlinerBackgrdColor =
//STRIP001                         GetDrawView()->GetModel()->GetDrawOutliner().GetBackgroundColor();
//STRIP001                 GetDrawView()->GetModel()->GetDrawOutliner().SetBackgroundColor( *_pPageBackgrdColor );
//STRIP001             }
//STRIP001
//STRIP001             aOldEEHoriTextDir =
//STRIP001                 GetDrawView()->GetModel()->GetDrawOutliner().GetDefaultHorizontalTextDirection();
//STRIP001             EEHorizontalTextDirection aEEHoriTextDirOfPage =
//STRIP001                 _bIsPageRightToLeft ? EE_HTEXTDIR_R2L : EE_HTEXTDIR_L2R;
//STRIP001             GetDrawView()->GetModel()->GetDrawOutliner().SetDefaultHorizontalTextDirection( aEEHoriTextDirOfPage );
//STRIP001         }
//STRIP001
//STRIP001         Link aLnk( LINK( this, SwViewImp, PaintDispatcher ) );
//STRIP001         GetPageView()->RedrawOneLayer( _nLayerID, _rRect.SVRect(),
//STRIP001                         pOutDev,
//STRIP001                      GetShell()->IsPreView() ? SDRPAINTMODE_ANILIKEPRN : 0,
//STRIP001                      &aLnk );
//STRIP001
//STRIP001         // OD 29.08.2002 #102450#
//STRIP001         // reset background color of the outliner
//STRIP001         // OD 09.12.2002 #103045# - reset default horizontal text direction
//STRIP001         if ( (_nLayerID == GetShell()->GetDoc()->GetHellId()) ||
//STRIP001              (_nLayerID == GetShell()->GetDoc()->GetHeavenId()) )
//STRIP001         {
//STRIP001             GetDrawView()->GetModel()->GetDrawOutliner().SetBackgroundColor( aOldOutlinerBackgrdColor );
//STRIP001             GetDrawView()->GetModel()->GetDrawOutliner().SetDefaultHorizontalTextDirection( aOldEEHoriTextDir );
//STRIP001         }
//STRIP001
//STRIP001         pOutDev->SetDrawMode( nOldDrawMode );
//STRIP001     }
//STRIP001 }


//STRIP001 IMPL_LINK( SwViewImp, PaintDispatcher, SdrPaintProcRec *, pRec )
//STRIP001 {
//STRIP001  SdrObject *pObj = pRec->pObj;
//STRIP001
//STRIP001  //Controls muessen im Control-Layer liegen. Dort duerfen aber auch
//STRIP001  //Gruppenobjekte oder mit Controls gruppierte Objekte liegen.
//STRIP001  ASSERT( FmFormInventor != pObj->GetObjInventor() ||
//STRIP001          GetShell()->GetDoc()->GetControlsId() == pObj->GetLayer(),
//STRIP001          "PaintDispatcher: Wrong Layer" );
//STRIP001
//STRIP001  if ( !SwFlyFrm::IsPaint( pObj, GetShell() ) )
//STRIP001      return 0;
//STRIP001
//STRIP001  if ( pObj->IsWriterFlyFrame() )
//STRIP001  {
//STRIP001      const SdrLayerID nHellId = GetShell()->GetDoc()->GetHellId();
//STRIP001      if( pObj->GetLayer() == nHellId )
//STRIP001      {
//STRIP001          //Fuer Rahmen in der Hoelle gelten andere Regeln:
//STRIP001          //1. Rahmen mit einem Parent werden nie direkt, sondern von ihren
//STRIP001          //   Parents gepaintet.
//STRIP001          //1a.Es sei denn, der Parent steht nicht in der Hoelle.
//STRIP001          //2. Rahmen mit Childs painten zuerst die Childs in
//STRIP001          //   umgekehrter Z-Order.
//STRIP001          SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001          const FASTBOOL bInFly = pFly->GetAnchor()->IsInFly();
//STRIP001          if ( !bInFly ||
//STRIP001               (bInFly && pFly->GetAnchor()->FindFlyFrm()->
//STRIP001                                GetVirtDrawObj()->GetLayer() != nHellId))
//STRIP001              PaintFlyChilds( pFly, pRec->rOut, pRec->rInfoRec );
//STRIP001      }
//STRIP001      else
//STRIP001          pObj->Paint( pRec->rOut, pRec->rInfoRec );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwRect aTmp( pRec->rInfoRec.aDirtyRect );
//STRIP001
//STRIP001      OutputDevice *pOut = pRec->rOut.GetOutDev();
//STRIP001      pOut->Push( PUSH_CLIPREGION );
//STRIP001      pOut->IntersectClipRegion( aTmp.SVRect() );
//STRIP001
//STRIP001      //Um zu verhindern, dass der Dispatcher fr jedes Gruppenobjekt
//STRIP001      //gerufen wird, muessen wir die Struktur manipulieren
//STRIP001      //(Absprache mit JOE).
//STRIP001      const Link *pSave = 0;
//STRIP001      if ( pObj->IsGroupObject() )
//STRIP001      {
//STRIP001          pSave = pRec->rInfoRec.pPaintProc;
//STRIP001          ((SdrPaintInfoRec&)pRec->rInfoRec).pPaintProc = 0;
//STRIP001      }
//STRIP001
//STRIP001      pObj->Paint( pRec->rOut, pRec->rInfoRec );
//STRIP001
//STRIP001      if ( pSave )
//STRIP001          ((SdrPaintInfoRec&)pRec->rInfoRec).pPaintProc = pSave;
//STRIP001
//STRIP001      pOut->Pop();
//STRIP001  }
//STRIP001     return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwViewImp::PaintFlyChilds()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 02. Aug. 95
|*
|*************************************************************************/


//STRIP001 void SwViewImp::PaintFlyChilds( SwFlyFrm *pFly, ExtOutputDevice& rOut,
//STRIP001                              const SdrPaintInfoRec& rInfoRec )
//STRIP001 {
//STRIP001  SdrObject *pFlyObj  = pFly->GetVirtDrawObj();
//STRIP001  SdrPage   *pPage = pFlyObj->GetPage();
//STRIP001  OutputDevice *pOut = rOut.GetOutDev();
//STRIP001
//STRIP001  //Zuerst den am weitesten oben liegenden Child suchen.
//STRIP001  ULONG i;
//STRIP001  for ( i = pFlyObj->GetOrdNumDirect()+1; i < pPage->GetObjCount(); ++i )
//STRIP001  {
//STRIP001      SdrObject *pObj = pPage->GetObj( i );
//STRIP001      SwFlyFrm *pF;
//STRIP001      if ( pObj->IsWriterFlyFrame() )
//STRIP001          pF = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001      else
//STRIP001      {
//STRIP001          SwFrm *pFrm = ((SwDrawContact*)GetUserCall(pObj))->GetAnchor();
//STRIP001          pF = pFrm ? pFrm->FindFlyFrm() : 0;
//STRIP001      }
//STRIP001      if ( pF && pF != pFly && !pF->IsLowerOf( pFly ) )
//STRIP001          break;
//STRIP001  }
//STRIP001  --i;    //Ich bin auf immer einen zu weit gelaufen.
//STRIP001  if ( i != pFlyObj->GetOrdNumDirect() )
//STRIP001  {
//STRIP001      for ( UINT32 j = i; j > pFlyObj->GetOrdNumDirect(); --j )
//STRIP001      {
//STRIP001          SdrObject *pObj = pPage->GetObj( j );
//STRIP001          if ( pObj->IsWriterFlyFrame() )
//STRIP001          {
//STRIP001              SwFlyFrm *pF = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001              if ( pF->GetAnchor()->FindFlyFrm() == pFly )
//STRIP001                  PaintFlyChilds( pF, rOut, rInfoRec );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwFrm *pFrm = ((SwDrawContact*)GetUserCall(pObj))->GetAnchor();
//STRIP001              if( pFrm && pFrm->FindFlyFrm() == pFly )
//STRIP001              {
//STRIP001                  pOut->Push( PUSH_LINECOLOR );
//STRIP001                  pObj->Paint( rOut, rInfoRec );
//STRIP001                  pOut->Pop();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pFlyObj->Paint( rOut, rInfoRec );
//STRIP001 }

/*************************************************************************
|*
|*  SwViewImp::IsDragPossible()
|*
|*  Ersterstellung      MA 19. Jan. 93
|*  Letzte Aenderung    MA 16. Jan. 95
|*
|*************************************************************************/



#define WIEDUWILLST 400

//STRIP001 BOOL SwViewImp::IsDragPossible( const Point &rPoint )
//STRIP001 {
//STRIP001  if ( !HasDrawView() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = GetDrawView()->GetMarkList();
//STRIP001
//STRIP001  if( !rMrkList.GetMarkCount() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SdrObject *pO = rMrkList.GetMark(rMrkList.GetMarkCount()-1)->GetObj();
//STRIP001
//STRIP001  SwRect aRect;
//STRIP001  if( ::CalcClipRect( pO, aRect, FALSE ) )
//STRIP001  {
//STRIP001      SwRect aTmp;
//STRIP001      ::CalcClipRect( pO, aTmp, TRUE );
//STRIP001      aRect.Union( aTmp );
//STRIP001  }
//STRIP001  else
//STRIP001      aRect = GetShell()->GetLayout()->Frm();
//STRIP001
//STRIP001  aRect.Top(    aRect.Top()    - WIEDUWILLST );
//STRIP001  aRect.Bottom( aRect.Bottom() + WIEDUWILLST );
//STRIP001  aRect.Left(   aRect.Left()   - WIEDUWILLST );
//STRIP001  aRect.Right(  aRect.Right()  + WIEDUWILLST );
//STRIP001  return aRect.IsInside( rPoint );
//STRIP001 }

/*************************************************************************
|*
|*  SwViewImp::NotifySizeChg()
|*
|*  Ersterstellung      MA 23. Jun. 93
|*  Letzte Aenderung    MA 05. Oct. 98
|*
|*************************************************************************/

/*N*/ void SwViewImp::NotifySizeChg( const Size &rNewSz )
/*N*/ {
/*N*/   if ( !HasDrawView() )
/*N*/       return;
/*N*/
/*N*/   if ( GetPageView() )
/*N*/       GetPageView()->GetPage()->SetSize( rNewSz );
/*N*/
/*N*/   //Begrenzung des Arbeitsbereiches.
/*N*/   Rectangle aRect( Point( DOCUMENTBORDER, DOCUMENTBORDER ), rNewSz );
/*N*/   const Rectangle &rOldWork = GetDrawView()->GetWorkArea();
/*N*/   BOOL bCheckDrawObjs = FALSE;
/*N*/   if ( aRect != rOldWork )
/*N*/   {
/*N*/       if ( rOldWork.Bottom() > aRect.Bottom() || rOldWork.Right() > aRect.Right())
/*N*/           bCheckDrawObjs = TRUE;
/*N*/       GetDrawView()->SetWorkArea( aRect );
/*N*/   }
/*N*/   if ( !bCheckDrawObjs )
/*N*/       return;
/*N*/
/*N*/   ASSERT( pSh->GetDoc()->GetDrawModel(), "NotifySizeChg without DrawModel" );
/*N*/   SdrPage* pPage = pSh->GetDoc()->GetDrawModel()->GetPage( 0 );
/*N*/   const ULONG nObjs = pPage->GetObjCount();
/*N*/   for( ULONG nObj = 0; nObj < nObjs; ++nObj )
/*N*/   {
/*N*/       SdrObject *pObj = pPage->GetObj( nObj );
/*N*/       if( !pObj->IsWriterFlyFrame() )
/*N*/       {
/*N*/           //Teilfix(26793): Objekte, die in Rahmen verankert sind, brauchen
/*N*/           //nicht angepasst werden.
/*N*/             const SwContact *pCont = (SwContact*)GetUserCall(pObj);
/*N*/           //JP - 16.3.00 Bug 73920: this function might be called by the
/*N*/           //              InsertDocument, when a PageDesc-Attribute is
/*N*/           //              set on a node. Then the SdrObject must not have
/*N*/           //              an UserCall.
/*N*/             if( !pCont || !pCont->ISA(SwDrawContact) )
/*N*/               continue;
/*N*/
/*N*/             const SwFrm *pAnchor = ((SwDrawContact*)pCont)->GetAnchor();
/*N*/           if ( !pAnchor || pAnchor->IsInFly() || !pAnchor->IsValid() ||
/*N*/                  !pAnchor->GetUpper() || !pAnchor->FindPageFrm() ||
/*N*/                FLY_IN_CNTNT == pCont->GetFmt()->GetAnchor().GetAnchorId() )
/*N*/               continue;
/*N*/
/*N*/             // OD 19.06.2003 #108784# - no move for drawing objects in header/footer
/*N*/             if ( pAnchor->FindFooterOrHeader() )
/*N*/             {
/*N*/                 continue;
/*N*/             }
/*N*/
/*N*/           const Rectangle aBound( pObj->GetBoundRect() );
/*N*/           if ( !aRect.IsInside( aBound ) )
/*N*/           {
/*N*/               Size aSz;
/*N*/               if ( aBound.Left() > aRect.Right() )
/*N*/                   aSz.Width() = (aRect.Right() - aBound.Left()) - MINFLY;
/*N*/               if ( aBound.Top() > aRect.Bottom() )
/*?*/                   aSz.Height() = (aRect.Bottom() - aBound.Top()) - MINFLY;
/*N*/               if ( aSz.Width() || aSz.Height() )
/*N*/                   pObj->Move( aSz );
/*N*/
/*N*/               //Notanker: Grosse Objekte nicht nach oben verschwinden lassen.
/*N*/               aSz.Width() = aSz.Height() = 0;
/*N*/               if ( aBound.Bottom() < aRect.Top() )
/*N*/                   aSz.Width() = (aBound.Bottom() - aRect.Top()) - MINFLY;
/*N*/               if ( aBound.Right() < aRect.Left() )
/*N*/                   aSz.Height() = (aBound.Right() - aRect.Left()) - MINFLY;
/*N*/               if ( aSz.Width() || aSz.Height() )
/*N*/                   pObj->Move( aSz );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }



}
