/*************************************************************************
 *
 *  $RCSfile: sw_swmodul1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-25 09:54:01 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _UIPARAM_HXX
#include <uiparam.hxx>
#endif

#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif
#ifndef _SFXDISPATCH_HXX
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX
#include <bf_sfx2/childwin.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_USEROPTIONS_HXX
#include <svtools/useroptions.hxx>
#endif

#ifndef _CPPUHELPER_WEAK_HXX_
#include <cppuhelper/weak.hxx>
#endif
#ifndef _COM_SUN_STAR_UTIL_URL_HPP_
#include <com/sun/star/util/URL.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDER_HPP_
#include <com/sun/star/frame/XDispatchProvider.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XSTATUSLISTENER_HPP_
#include <com/sun/star/frame/XStatusListener.hpp>
#endif
#ifndef _COM_SUN_STAR_VIEW_XSELECTIONSUPPLIER_HPP_
#include <com/sun/star/view/XSelectionSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx> // helper for implementations
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#include <bf_svx/dataaccessdescriptor.hxx>
#endif

#ifndef _SBASLTID_HRC //autogen
#include <bf_offmgr/sbasltid.hrc>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX //autogen
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_CMAPITEM_HXX //autogen
#include <bf_svx/cmapitem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif

#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _USRPREF_HXX
#include <usrpref.hxx>
#endif
#ifndef _MODCFG_HXX
#include <modcfg.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _PVIEW_HXX
#include <pview.hxx>
#endif
#ifndef _WVIEW_HXX
#include <wview.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _UINUMS_HXX
#include <uinums.hxx>
#endif
#ifndef _PRTOPT_HXX
#include <prtopt.hxx>       // fuer PrintOptions
#endif
#ifndef _NAVICFG_HXX
#include <navicfg.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _APP_HRC
#include <app.hrc>
#endif
#include "helpid.h"
namespace binfilter {

using namespace ::rtl;
using namespace ::binfilter ::svx;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::lang;
#define C2U(char) ::rtl::OUString::createFromAscii(char)

/* -----------------------------05.01.00 15:14--------------------------------

 ---------------------------------------------------------------------------*/

//STRIP001 class SwXDispatchStatusListener : public cppu::WeakImplHelper1
//STRIP001 <
//STRIP001  frame::XStatusListener
//STRIP001 >
//STRIP001 {
//STRIP001  uno::Reference< frame::XStatusListener >            xSelf;
//STRIP001  util::URL                       aDispURL;
//STRIP001  uno::Reference< frame::XDispatch >              xDispatch;
//STRIP001
//STRIP001  void            Invalidate();
//STRIP001 public:
//STRIP001  SwXDispatchStatusListener(uno::Reference< frame::XDispatch > &  xDisp, const util::URL&     aURL);
//STRIP001  ~SwXDispatchStatusListener();
//STRIP001
//STRIP001  //XStatusListener
//STRIP001  virtual void SAL_CALL statusChanged(const frame::FeatureStateEvent& Event) throw( uno::RuntimeException );
//STRIP001
//STRIP001  //XEventListener
//STRIP001     virtual void SAL_CALL disposing(const lang::EventObject& Source) throw( uno::RuntimeException );
//STRIP001 };
/* -----------------------------05.01.00 15:18--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 SwXDispatchStatusListener::SwXDispatchStatusListener(
//STRIP001                              uno::Reference< frame::XDispatch > & xDisp, const util::URL&    aURL) :
//STRIP001  xDispatch(xDisp),
//STRIP001  aDispURL(aURL)
//STRIP001 {
//STRIP001  DBG_ASSERT(xDisp.is(),  "XDispatch not set")
//STRIP001  if(xDisp.is())
//STRIP001      xSelf = this;
//STRIP001 }
/* -----------------------------05.01.00 15:19--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 SwXDispatchStatusListener::~SwXDispatchStatusListener()
//STRIP001 {
//STRIP001 }
/* -----------------------------05.01.00 15:21--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwXDispatchStatusListener::disposing(const lang::EventObject& Source)
//STRIP001  throw( uno::RuntimeException )
//STRIP001 {
//STRIP001  Invalidate();
//STRIP001 }
/* -----------------------------05.01.00 15:22--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwXDispatchStatusListener::statusChanged(const frame::FeatureStateEvent& rEvent)
//STRIP001  throw( uno::RuntimeException )
//STRIP001 {
//STRIP001  if(rEvent.FeatureURL.Complete == aDispURL.Complete && rEvent.IsEnabled)
//STRIP001  {
//STRIP001      uno::Sequence <beans::PropertyValue > aArgs(0);
//STRIP001      xDispatch->dispatch(aDispURL, aArgs);
//STRIP001      Invalidate();
//STRIP001  }
//STRIP001 }
/* -----------------------------05.01.00 15:45--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwXDispatchStatusListener::Invalidate()
//STRIP001 {
//STRIP001  if(xDispatch.is())
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          xDispatch->removeStatusListener(xSelf, aDispURL);
//STRIP001      }
//STRIP001      catch(...)
//STRIP001      {
//STRIP001      }
//STRIP001  }
//STRIP001  xSelf = 0;
//STRIP001 }
/*-----------------08/28/97 08:41pm-----------------

--------------------------------------------------*/
//STRIP001 void lcl_SetUIPrefs(const SwViewOption* pPref, SwView* pView, ViewShell* pSh )
//STRIP001 {
//STRIP001  // in FrameSets kann die tatsaechliche Sichtbarkeit von der Einstellung der ViewOptions abweichen
//STRIP001  sal_Bool bVScrollChanged = pPref->IsViewVScrollBar() != pSh->GetViewOptions()->IsViewVScrollBar();
//STRIP001     sal_Bool bHScrollChanged = pPref->IsViewHScrollBar() != pSh->GetViewOptions()->IsViewHScrollBar();
//STRIP001     sal_Bool bVAlignChanged = pPref->IsVRulerRight() != pSh->GetViewOptions()->IsVRulerRight();
//STRIP001
//STRIP001     pSh->SetUIOptions(*pPref);
//STRIP001     const SwViewOption* pNewPref = pSh->GetViewOptions();
//STRIP001
//STRIP001  // Scrollbars an / aus
//STRIP001  if(bVScrollChanged)
//STRIP001  {
//STRIP001         pView->ShowVScrollbar(pNewPref->IsViewVScrollBar());
//STRIP001  }
//STRIP001  if(bHScrollChanged)
//STRIP001  {
//STRIP001         pView->ShowHScrollbar( pNewPref->IsViewHScrollBar() || pSh->IsBrowseMode());
//STRIP001  }
//STRIP001     //if only the position of the vertical ruler has been changed initiate an update
//STRIP001     if(bVAlignChanged && !bHScrollChanged && !bVScrollChanged)
//STRIP001         pView->InvalidateBorder();
//STRIP001
//STRIP001  // Lineale an / aus
//STRIP001     if(pNewPref->IsViewVRuler())
//STRIP001      pView->CreateVLineal();
//STRIP001  else
//STRIP001      pView->KillVLineal();
//STRIP001
//STRIP001  // TabWindow an/aus
//STRIP001     if(pNewPref->IsViewHRuler())
//STRIP001      pView->CreateTab();
//STRIP001  else
//STRIP001      pView->KillTab();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Aktuelle SwWrtShell
 --------------------------------------------------------------------*/


//STRIP001 SwWrtShell*  GetActiveWrtShell()
//STRIP001 {
//STRIP001  SwView *pActive = ::GetActiveView();
//STRIP001  if( pActive )
//STRIP001      return &pActive->GetWrtShell();
//STRIP001  return 0;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Pointer auf die aktuelle Sicht
 --------------------------------------------------------------------*/


/*N*/ SwView* GetActiveView()
/*N*/ {
/*N*/   SfxViewShell* pView = SfxViewShell::Current();
/*N*/   return PTR_CAST( SwView, pView );
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung:   Ueber Views iterieren - static
 --------------------------------------------------------------------*/

/*N*/ SwView* SwModule::GetFirstView()
/*N*/ {
/*N*/   // liefert nur sichtbare SwViews
/*N*/   const TypeId aTypeId = TYPE(SwView);
/*N*/   SwView* pView = (SwView*)SfxViewShell::GetFirst(&aTypeId);
/*N*/   return pView;
/*N*/ }


/*N*/ SwView* SwModule::GetNextView(SwView* pView)
/*N*/ {
/*N*/   DBG_ASSERT(PTR_CAST(SwView, pView),"keine SwView uebergeben")
/*N*/   const TypeId aTypeId = TYPE(SwView);
/*N*/   // auf Sichtbarkeit pruefen, bis der Sfx das GetFirst/Next
/*N*/   //mit bOnlyVisible implementiert hat
/*N*/   SwView* pNView = (SwView*)SfxViewShell::GetNext(*pView, &aTypeId);
/*N*/   while(pNView && !pNView->GetViewFrame()->IsVisible())
/*N*/   {
/*N*/       pNView = (SwView*)SfxViewShell::GetNext(*pNView, &aTypeId);
/*N*/   }
/*N*/   return pNView;
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Liefert UsrPref mit den Einstellungen des aktuellen
                Fensters
------------------------------------------------------------------------*/


//STRIP001 void SwModule::MakeUsrPref( SwViewOption &rToFill, sal_Bool bWeb ) const
//STRIP001 {
//STRIP001      // Einstellungen Ansicht der Core setzen
//STRIP001  SwView* pView = ::GetActiveView();
//STRIP001  SwPagePreView* pPPView;
//STRIP001
//STRIP001  if(pView)
//STRIP001  {
//STRIP001      rToFill = *(pView->GetWrtShell().GetViewOptions());
//STRIP001      SfxFrame* pTopFrame = pView->GetViewFrame()->GetTopFrame();
//STRIP001      if( pTopFrame->GetChildFrameCount() != 0 )
//STRIP001      {
//STRIP001             rToFill.SetViewHRuler(pUsrPref->IsViewHRuler());
//STRIP001             rToFill.SetViewVRuler(pUsrPref->IsViewVRuler());
//STRIP001      }
//STRIP001  }
//STRIP001  else if( 0 != (pPPView = PTR_CAST( SwPagePreView, SfxViewShell::Current())) )
//STRIP001         rToFill = *(pPPView->GetViewShell()->GetViewOptions());
//STRIP001  else
//STRIP001      rToFill = *((SwModule*)this)->GetUsrPref( bWeb );
//STRIP001 }


/*------------------------------------------------------------------------
 Beschreibung:  Neuer Master fuer die Einstellungen wird gesetzt;
                dieser wirkt sich auf die aktuelle Sicht und alle
                folgenden aus.
------------------------------------------------------------------------*/

/*M*/ void SwModule::ApplyUsrPref(const SwViewOption &rUsrPref, SwView* pActView,
/*M*/                           sal_uInt16 nDest )
/*M*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/    SwView* pView = pActView;
//STRIP001 /*?*/     ViewShell* pSh = pView ? &pView->GetWrtShell() : 0;
//STRIP001 /*?*/
//STRIP001 /*?*/    SwMasterUsrPref* pPref = (SwMasterUsrPref*)GetUsrPref(
//STRIP001 /*?*/                                         VIEWOPT_DEST_WEB == nDest ? sal_True  :
//STRIP001 /*?*/                                         VIEWOPT_DEST_TEXT== nDest ? sal_False :
//STRIP001 /*?*/                                         pView && pView->ISA(SwWebView) );
//STRIP001 /*?*/
//STRIP001 /*?*/    //per Uno soll nur die sdbcx::View, aber nicht das Module veraendert werden
//STRIP001 /*?*/    sal_Bool bViewOnly = VIEWOPT_DEST_VIEW_ONLY == nDest;
//STRIP001 /*?*/    //PreView abfruehstuecken
//STRIP001 /*?*/    SwPagePreView* pPPView;
//STRIP001 /*?*/    if( !pView && 0 != (pPPView = PTR_CAST( SwPagePreView, SfxViewShell::Current())) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if(!bViewOnly)
//STRIP001 /*?*/            pPref->SetUIOptions( rUsrPref );
//STRIP001 /*?*/         pPPView->ShowVScrollbar(pPref->IsViewVScrollBar());
//STRIP001 /*?*/         pPPView->ShowHScrollbar(pPref->IsViewHScrollBar());
//STRIP001 /*?*/        if(!bViewOnly)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pPref->SetPagePrevRow(rUsrPref.GetPagePrevRow());
//STRIP001 /*?*/            pPref->SetPagePrevCol(rUsrPref.GetPagePrevCol());
//STRIP001 /*?*/        }
//STRIP001 /*?*/        return;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if(!bViewOnly)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pPref->SetUsrPref( rUsrPref );
//STRIP001 /*?*/        pPref->SetModified();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if( !pView )
//STRIP001 /*?*/        return;
//STRIP001 /*?*/
//STRIP001 /*?*/    // Weitergabe an die CORE
//STRIP001 /*?*/    const sal_Bool bReadonly = pView->GetDocShell()->IsReadOnly();
//STRIP001 /*?*/    SwViewOption* pViewOpt;
//STRIP001 /*?*/    if(!bViewOnly)
//STRIP001 /*?*/        pViewOpt = new SwViewOption( *pPref );
//STRIP001 /*?*/    else
//STRIP001 /*?*/        pViewOpt = new SwViewOption( rUsrPref );
//STRIP001 /*?*/    pViewOpt->SetReadonly( bReadonly );
//STRIP001 /*?*/    if( !(*pSh->GetViewOptions() == *pViewOpt) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        //Ist evtl. nur eine ViewShell
//STRIP001 /*?*/        pSh->StartAction();
//STRIP001 /*?*/        pSh->ApplyViewOptions( *pViewOpt );
//STRIP001 /*?*/        ((SwWrtShell*)pSh)->SetReadOnlyAvailable(pViewOpt->IsCursorInProtectedArea());
//STRIP001 /*?*/        pSh->EndAction();
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if ( pSh->GetViewOptions()->IsReadonly() != bReadonly )
//STRIP001 /*?*/        pSh->SetReadonlyOption(bReadonly);
//STRIP001 /*?*/
//STRIP001 /*?*/    lcl_SetUIPrefs(pViewOpt, pView, pSh);
//STRIP001 /*?*/     // zum Schluss wird das Idle-Flag wieder gesetzt
//STRIP001 /*?*/    // #42510#
//STRIP001 /*?*/    pPref->SetIdle(sal_True);
//STRIP001 /*?*/
/*M*/ }
/* -----------------------------28.09.00 12:36--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwModule::ApplyUserMetric( FieldUnit eMetric, BOOL bWeb )
//STRIP001 {
//STRIP001      SwMasterUsrPref* pPref;
//STRIP001      if(bWeb)
//STRIP001      {
//STRIP001          if(!pWebUsrPref)
//STRIP001              GetUsrPref(sal_True);
//STRIP001          pPref = pWebUsrPref;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(!pUsrPref)
//STRIP001              GetUsrPref(sal_False);
//STRIP001          pPref = pUsrPref;
//STRIP001      }
//STRIP001      FieldUnit eOldMetric = pPref->GetMetric();
//STRIP001      if(eOldMetric != eMetric)
//STRIP001          pPref->SetMetric(eMetric);
//STRIP001
//STRIP001         FieldUnit eHScrollMetric = pPref->IsHScrollMetric() ? pPref->GetHScrollMetric() : eMetric;
//STRIP001         FieldUnit eVScrollMetric = pPref->IsVScrollMetric() ? pPref->GetVScrollMetric() : eMetric;
//STRIP001
//STRIP001      SwView* pTmpView = SwModule::GetFirstView();
//STRIP001      // fuer alle MDI-Fenster das Lineal umschalten
//STRIP001      while(pTmpView)
//STRIP001      {
//STRIP001          if(bWeb == (0 != PTR_CAST(SwWebView, pTmpView)))
//STRIP001          {
//STRIP001                 pTmpView->ChangeVLinealMetric(eHScrollMetric);
//STRIP001                 pTmpView->ChangeTabMetric(eVScrollMetric);
//STRIP001          }
//STRIP001
//STRIP001          pTmpView = SwModule::GetNextView(pTmpView);
//STRIP001      }
//STRIP001
//STRIP001 }
/*-----------------13.11.96 11.57-------------------

--------------------------------------------------*/

//STRIP001 SwNavigationConfig*  SwModule::GetNavigationConfig()
//STRIP001 {
//STRIP001  if(!pNavigationConfig)
//STRIP001  {
//STRIP001      pNavigationConfig = new SwNavigationConfig;
//STRIP001  }
//STRIP001  return pNavigationConfig;
//STRIP001 }

/*-----------------05.02.97 08.03-------------------

--------------------------------------------------*/

/*N*/ SwPrintOptions*   SwModule::GetPrtOptions(sal_Bool bWeb)
/*N*/ {
/*N*/   if(bWeb && !pWebPrtOpt)
/*N*/   {
/*N*/       pWebPrtOpt = new SwPrintOptions(TRUE);
/*N*/   }
/*N*/   else if(!bWeb && !pPrtOpt)
/*N*/   {
/*N*/       pPrtOpt = new SwPrintOptions(FALSE);
/*N*/   }
/*N*/
/*N*/   return bWeb ? pWebPrtOpt : pPrtOpt;
/*N*/ }

/*-----------------26.06.97 07.52-------------------

--------------------------------------------------*/
//STRIP001 SwChapterNumRules*   SwModule::GetChapterNumRules()
//STRIP001 {
//STRIP001  if(!pChapterNumRules)
//STRIP001      pChapterNumRules = new SwChapterNumRules;
//STRIP001  return pChapterNumRules;
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: Schaut nach ob's min eine View gibt
 --------------------------------------------------------------------*/

//STRIP001 void SwModule::StateIsView(SfxItemSet& rSet)
//STRIP001 {
//STRIP001  SwView *pView = ::GetActiveView();
//STRIP001
//STRIP001  TypeId aType( TYPE(SwView) );
//STRIP001  if( !SfxViewShell::GetFirst(&aType) )   // Ist irgendein Writer-Dok vorhanden?
//STRIP001      rSet.DisableItem(FN_QRY_MERGE);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwModule::ShowDBObj(SwView& rView, const SwDBData& rData, BOOL bOnlyIfAvailable)
//STRIP001 {
//STRIP001     Reference<XFrame> xFrame = rView.GetViewFrame()->GetFrame()->GetFrameInterface();
//STRIP001     Reference<XDispatchProvider> xDP(xFrame, uno::UNO_QUERY);
//STRIP001
//STRIP001     uno::Reference<frame::XFrame> xBeamerFrame = xFrame->findFrame(
//STRIP001                                         ::rtl::OUString::createFromAscii("_beamer"),
//STRIP001                                         FrameSearchFlag::CHILDREN);
//STRIP001     if (xBeamerFrame.is())
//STRIP001     {   // the beamer has been opened by the SfxViewFrame
//STRIP001         Reference<XController> xController = xBeamerFrame->getController();
//STRIP001         Reference<XSelectionSupplier> xControllerSelection(xController, UNO_QUERY);
//STRIP001         if (xControllerSelection.is())
//STRIP001         {
//STRIP001
//STRIP001             ODataAccessDescriptor aSelection;
//STRIP001             aSelection[daDataSource]    <<= rData.sDataSource;
//STRIP001             aSelection[daCommand]       <<= rData.sCommand;
//STRIP001             aSelection[daCommandType]   <<= rData.nCommandType;
//STRIP001             xControllerSelection->select(makeAny(aSelection.createPropertyValueSequence()));
//STRIP001         }
//STRIP001         else
//STRIP001             DBG_ERROR("no selection supplier in the beamer!");
//STRIP001     }
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: Redlining
 --------------------------------------------------------------------*/

/*N*/ sal_uInt16 SwModule::GetRedlineAuthor()
/*N*/ {
DBG_ASSERT(0, "STRIP"); return 0;//STRIP001     if (!bAuthorInitialised)
//STRIP001  {
//STRIP001      SvtUserOptions aOpt;
//STRIP001      if( !(sActAuthor = aOpt.GetFullName()).Len() )
//STRIP001          sActAuthor = String( SW_RES( STR_REDLINE_UNKNOWN_AUTHOR ));
//STRIP001      bAuthorInitialised = sal_True;
//STRIP001  }
//STRIP001  return InsertRedlineAuthor( sActAuthor );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ const String& SwModule::GetRedlineAuthor(sal_uInt16 nPos)
/*N*/ {
/*N*/   return *pAuthorNames->GetObject(nPos);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 sal_uInt16 SwModule::GetRedlineAuthorCount()
//STRIP001 {
//STRIP001  return pAuthorNames->Count();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ sal_uInt16 SwModule::InsertRedlineAuthor(const String& rAuthor) //SW50.SDW
/*N*/ {
/*N*/   sal_uInt16 nPos = 0;
/*N*/
/*N*/   while (nPos < pAuthorNames->Count() && *pAuthorNames->GetObject(nPos) != rAuthor)
/*N*/       nPos++;
/*N*/
/*N*/   if (nPos == pAuthorNames->Count())
/*N*/       pAuthorNames->Insert(new String(rAuthor), nPos);
/*N*/
/*N*/   return nPos;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void lcl_FillAuthorAttr( sal_uInt16 nAuthor, SfxItemSet &rSet,
//STRIP001                      const AuthorCharAttr &rAttr )
//STRIP001 {
//STRIP001  Color aCol( (ColorData)rAttr.nColor );
//STRIP001
//STRIP001  if( COL_TRANSPARENT == rAttr.nColor )
//STRIP001  {
//STRIP001      // dynamische Vergabe der Attribute
//STRIP001      static const ColorData aColArr[] = {
//STRIP001              COL_LIGHTRED,       COL_LIGHTBLUE,      COL_LIGHTMAGENTA,
//STRIP001              COL_GREEN,          COL_RED,            COL_BLUE,
//STRIP001              COL_BROWN,          COL_MAGENTA,        COL_CYAN };
//STRIP001      aCol.SetColor( aColArr[ nAuthor % (sizeof( aColArr ) /
//STRIP001                                         sizeof( aColArr[0] )) ] );
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool bBackGr = COL_NONE == rAttr.nColor;
//STRIP001
//STRIP001  switch (rAttr.nItemId)
//STRIP001  {
//STRIP001  case SID_ATTR_CHAR_WEIGHT:
//STRIP001      {
//STRIP001          SvxWeightItem aW( (FontWeight)rAttr.nAttr, RES_CHRATR_WEIGHT );
//STRIP001          rSet.Put( aW );
//STRIP001          aW.SetWhich( RES_CHRATR_CJK_WEIGHT );
//STRIP001          rSet.Put( aW );
//STRIP001          aW.SetWhich( RES_CHRATR_CTL_WEIGHT );
//STRIP001          rSet.Put( aW );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SID_ATTR_CHAR_POSTURE:
//STRIP001      {
//STRIP001          SvxPostureItem aP( (FontItalic)rAttr.nAttr, RES_CHRATR_POSTURE );
//STRIP001          rSet.Put( aP );
//STRIP001          aP.SetWhich( RES_CHRATR_CJK_POSTURE );
//STRIP001          rSet.Put( aP );
//STRIP001          aP.SetWhich( RES_CHRATR_CTL_POSTURE );
//STRIP001          rSet.Put( aP );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SID_ATTR_CHAR_UNDERLINE:
//STRIP001      rSet.Put( SvxUnderlineItem( (FontUnderline)rAttr.nAttr,
//STRIP001                                  RES_CHRATR_UNDERLINE));
//STRIP001      break;
//STRIP001
//STRIP001  case SID_ATTR_CHAR_STRIKEOUT:
//STRIP001      rSet.Put(SvxCrossedOutItem( (FontStrikeout)rAttr.nAttr,
//STRIP001                                  RES_CHRATR_CROSSEDOUT));
//STRIP001      break;
//STRIP001
//STRIP001  case SID_ATTR_CHAR_CASEMAP:
//STRIP001      rSet.Put( SvxCaseMapItem( (SvxCaseMap)rAttr.nAttr,
//STRIP001                                  RES_CHRATR_CASEMAP));
//STRIP001      break;
//STRIP001
//STRIP001  case SID_ATTR_BRUSH:
//STRIP001      rSet.Put( SvxBrushItem( aCol, RES_CHRATR_BACKGROUND ));
//STRIP001      bBackGr = sal_True;
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( !bBackGr )
//STRIP001      rSet.Put( SvxColorItem( aCol ) );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwModule::GetInsertAuthorAttr(sal_uInt16 nAuthor, SfxItemSet &rSet)
//STRIP001 {
//STRIP001  lcl_FillAuthorAttr(nAuthor, rSet, pModuleConfig->GetInsertAuthorAttr());
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwModule::GetDeletedAuthorAttr(sal_uInt16 nAuthor, SfxItemSet &rSet)
//STRIP001 {
//STRIP001  lcl_FillAuthorAttr(nAuthor, rSet, pModuleConfig->GetDeletedAuthorAttr());
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 const AuthorCharAttr& SwModule::GetInsertAuthorAttr() const
//STRIP001 {
//STRIP001  return pModuleConfig->GetInsertAuthorAttr();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 const AuthorCharAttr& SwModule::GetDeletedAuthorAttr() const
//STRIP001 {
//STRIP001  return pModuleConfig->GetDeletedAuthorAttr();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Fuer zukuenftige Erweiterung:
 --------------------------------------------------------------------*/

//STRIP001 void SwModule::GetFormatAuthorAttr( sal_uInt16 nAuthor, SfxItemSet &rSet )
//STRIP001 {
//STRIP001  lcl_FillAuthorAttr( nAuthor, rSet, pModuleConfig->GetFormatAuthorAttr() );
//STRIP001 }

//STRIP001 const AuthorCharAttr& SwModule::GetFormatAuthorAttr() const
//STRIP001 {
//STRIP001  return pModuleConfig->GetFormatAuthorAttr();
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ sal_uInt16 SwModule::GetRedlineMarkPos()
/*N*/ {
/*N*/   return pModuleConfig->GetMarkAlignMode();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 sal_Bool SwModule::IsInsTblFormatNum(sal_Bool bHTML) const
//STRIP001 {
//STRIP001  return pModuleConfig->IsInsTblFormatNum(bHTML);
//STRIP001 }

//STRIP001 sal_Bool SwModule::IsInsTblChangeNumFormat(sal_Bool bHTML) const
//STRIP001 {
//STRIP001  return pModuleConfig->IsInsTblChangeNumFormat(bHTML);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 sal_Bool SwModule::IsInsTblAlignNum(sal_Bool bHTML) const
//STRIP001 {
//STRIP001  return pModuleConfig->IsInsTblAlignNum(bHTML);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 const Color &SwModule::GetRedlineMarkColor()
//STRIP001 {
//STRIP001  return pModuleConfig->GetMarkAlignColor();
//STRIP001 }

/*-----------------03.03.98 16:47-------------------

--------------------------------------------------*/
/*N*/ const SwViewOption*   SwModule::GetViewOption(sal_Bool bWeb)
/*N*/ {
/*N*/   return GetUsrPref( bWeb );
/*N*/ }

// returne den definierten DocStat - WordDelimiter
/*N*/ const String& SwModule::GetDocStatWordDelim() const
/*N*/ {
/*N*/   return pModuleConfig->GetWordDelimiter();
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
// Durchreichen der Metric von der ModuleConfig (fuer HTML-Export)
/*N*/ sal_uInt16 SwModule::GetMetric( sal_Bool bWeb ) const
/*N*/ {
/*N*/   SwMasterUsrPref* pPref;
/*N*/   if(bWeb)
/*N*/   {
/*?*/       if(!pWebUsrPref)
/*?*/           GetUsrPref(sal_True);
/*?*/       pPref = pWebUsrPref;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if(!pUsrPref)
/*?*/           GetUsrPref(sal_False);
/*N*/       pPref = pUsrPref;
/*N*/   }
/*N*/   return pPref->GetMetric();
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
// Update-Stati durchreichen
/*N*/ sal_uInt16 SwModule::GetLinkUpdMode( sal_Bool ) const
/*N*/ {
/*N*/   if(!pUsrPref)
/*N*/       GetUsrPref(sal_False);
/*N*/     return (sal_uInt16)pUsrPref->GetUpdateLinkMode();
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_uInt16 SwModule::GetFldUpdateFlags( sal_Bool ) const
/*N*/ {
/*N*/   if(!pUsrPref)
/*N*/       GetUsrPref(sal_False);
/*N*/   return (sal_uInt16)pUsrPref->GetFldUpdateFlags();
/*N*/ }
/* -----------------------------28.09.00 14:18--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwModule::ApplyFldUpdateFlags(sal_Int32 nFldFlags)
//STRIP001 {
//STRIP001  if(!pUsrPref)
//STRIP001      GetUsrPref(sal_False);
//STRIP001  pUsrPref->SetFldUpdateFlags(nFldFlags);
//STRIP001 }
/* -----------------------------28.09.00 14:18--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwModule::ApplyLinkMode(sal_Int32 nNewLinkMode)
//STRIP001 {
//STRIP001  if(!pUsrPref)
//STRIP001      GetUsrPref(sal_False);
//STRIP001  pUsrPref->SetUpdateLinkMode(nNewLinkMode);
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwModule::CheckSpellChanges( sal_Bool bOnlineSpelling,
/*N*/       sal_Bool bIsSpellWrongAgain, sal_Bool bIsSpellAllAgain )
/*N*/ {
/*N*/   sal_Bool bOnlyWrong = bIsSpellWrongAgain && !bIsSpellAllAgain;
/*N*/   sal_Bool bInvalid = bOnlyWrong || bIsSpellAllAgain;
/*N*/   if( bOnlineSpelling || bInvalid )
/*N*/   {
/*N*/       TypeId aType = TYPE(SwDocShell);
/*N*/       for( SwDocShell *pDocSh = (SwDocShell*)SfxObjectShell::GetFirst(&aType);
/*N*/            pDocSh;
/*N*/            pDocSh = (SwDocShell*)SfxObjectShell::GetNext( *pDocSh, &aType ) )
/*N*/       {
/*N*/           SwDoc* pTmp = pDocSh->GetDoc();
/*N*/           if ( pTmp->GetRootFrm() )
/*N*/               pTmp->SpellItAgainSam( bInvalid, bOnlyWrong );
/*N*/       }
/*N*/ //        pSpell->SetSpellWrongAgain( sal_False );
/*N*/ //        pSpell->SetSpellAllAgain( sal_False );
/*N*/   }
/*N*/ }

}
