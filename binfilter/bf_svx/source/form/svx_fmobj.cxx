/*************************************************************************
 *
 *  $RCSfile: svx_fmobj.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:46:19 $
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

// auto strip #ifndef _SVX_FMPROP_HXX
// auto strip #include "fmprop.hxx"
// auto strip #endif

// auto strip #ifndef _TOOLS_RESMGR_HXX
// auto strip #include <tools/resmgr.hxx>
// auto strip #endif

#ifndef _SVX_FMOBJ_HXX
#include "fmobj.hxx"
#endif

#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif


#ifndef _COM_SUN_STAR_SCRIPT_XEVENTATTACHERMANAGER_HPP_
#include <com/sun/star/script/XEventAttacherManager.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
// auto strip #include <com/sun/star/io/XPersistObject.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_AWT_XCONTROLCONTAINER_HPP_
// auto strip #include <com/sun/star/awt/XControlContainer.hpp>
// auto strip #endif

// auto strip #ifndef _SVDIO_HXX //autogen
// auto strip #include <svdio.hxx>
// auto strip #endif

#ifndef _SVX_FMMODEL_HXX
#include "fmmodel.hxx"
#endif

#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif

// auto strip #ifndef _SHL_HXX
// auto strip #include <tools/shl.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_DIALMGR_HXX
// auto strip #include "dialmgr.hxx"
// auto strip #endif

#ifndef _SVX_FMRESIDS_HRC
#include "fmresids.hrc"
#endif

#ifndef _SVX_FMVIEW_HXX //autogen
#include <fmview.hxx>
#endif

#ifndef _SVX_FMGLOB_HXX
#include "fmglob.hxx"
#endif

#ifndef _SVX_FMPGEIMP_HXX
#include "fmpgeimp.hxx"
#endif

#ifndef _SVX_FMPAGE_HXX
#include "fmpage.hxx"
#endif
// auto strip #ifndef _COMPHELPER_PROPERTY_HXX_
// auto strip #include <comphelper/property.hxx>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
// auto strip #ifndef _LEGACYBINFILTERMGR_HXX
// auto strip #include <legacysmgr/legacy_binfilters_smgr.hxx>  //STRIP002
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;

/*N*/ TYPEINIT1(FmFormObj, SdrUnoObj);
/*N*/ DBG_NAME(FmFormObj)
//------------------------------------------------------------------
//STRIP001 FmFormObj::FmFormObj(const ::rtl::OUString& rModelName,sal_Int32 _nType)
//STRIP001        :SdrUnoObj(rModelName, sal_False)
//STRIP001        ,pTempView(0)
//STRIP001        ,nEvent(0)
//STRIP001        ,nPos(-1)
//STRIP001        ,m_nType(_nType)
//STRIP001 {
//STRIP001  DBG_CTOR(FmFormObj, NULL);
//STRIP001 }

//------------------------------------------------------------------
/*N*/ FmFormObj::FmFormObj(sal_Int32 _nType)
/*N*/         :SdrUnoObj(String(), sal_False)
/*N*/         ,nEvent(0)
/*N*/         ,pTempView(0)
/*N*/         ,nPos(-1)
/*N*/         ,m_nType(_nType)
/*N*/ {
/*N*/   DBG_CTOR(FmFormObj, NULL);
/*N*/ }

//------------------------------------------------------------------
/*N*/ FmFormObj::~FmFormObj()
/*N*/ {
/*N*/   DBG_DTOR(FmFormObj, NULL);
/*N*/   if (nEvent)
/*?*/       Application::RemoveUserEvent(nEvent);
/*N*/
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent> xHistory(m_xEnvironmentHistory, ::com::sun::star::uno::UNO_QUERY);
/*N*/   if (xHistory.is())
/*?*/       xHistory->dispose();
/*N*/
/*N*/   m_xEnvironmentHistory = NULL;
/*N*/   m_aEventsHistory.realloc(0);
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormObj::SetObjEnv(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > & xForm, sal_Int32 nIdx,
/*N*/                         const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& rEvts)
/*N*/ {
/*N*/   xParent = xForm;
/*N*/   aEvts   = rEvts;
/*N*/   nPos    = nIdx;
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormObj::SetPage(SdrPage* _pNewPage)
/*N*/ {
/*N*/   FmFormPage* pNewFormPage = PTR_CAST(FmFormPage, _pNewPage);
/*N*/   if (!pNewFormPage || (GetPage() == _pNewPage))
/*N*/   {   // Maybe it makes sense to create an environment history here : if somebody set's our page to NULL, and we have a valid page before,
/*N*/       // me may want to remember our place within the old page. For this we could create a new m_pEnvironmentHistory to store it.
/*N*/       // So the next SetPage with a valid new page would restore that environment within the new page.
/*N*/       // But for the original Bug (#57300#) we don't need that, so I omit it here. Maybe this will be implemented later.
/*N*/       SdrUnoObj::SetPage(_pNewPage);
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >    xNewParent;
/*N*/   ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor>   aNewEvents;
/*N*/
/*N*/   // calc the new parent for my model (within the new page's forms hierarchy)
/*N*/   // do we have a history ? (from :Clone)
/*N*/   if (m_xEnvironmentHistory.is())
/*N*/   {
/*N*/       // the element in *m_pEnvironmentHistory which is equivalent to my new parent (which (perhaps) has to be created within _pNewPage->GetForms)
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*N*/         // is the right-most element in the tree.
//STRIP001 /*?*/        ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xLoop = m_xEnvironmentHistory;
//STRIP001 /*?*/        do
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if (xLoop->getCount() == 0)
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xRightMostChild;
//STRIP001 /*?*/            xLoop->getByIndex(xLoop->getCount() - 1) >>= xRightMostChild;
//STRIP001 /*?*/            if (!xRightMostChild.is())
//STRIP001 /*?*/            {
//STRIP001 /*?*/                DBG_ERROR("FmFormObj::SetPage : invalid elements in environment history !");
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            xLoop = xRightMostChild;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        while (sal_True);
//STRIP001 /*?*/
//STRIP001 /*?*/        xNewParent = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (ensureModelEnv(xLoop, ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (pNewFormPage->GetForms(), ::com::sun::star::uno::UNO_QUERY)), ::com::sun::star::uno::UNO_QUERY);
//STRIP001 /*?*/        if (xNewParent.is())
//STRIP001 /*?*/            // we successfully clone the environment in m_pEnvironmentHistory, so we can use m_aEventsHistory
//STRIP001 /*?*/            // (which describes the events of our model at the moment m_pEnvironmentHistory was created)
//STRIP001 /*?*/            aNewEvents = m_aEventsHistory;
/*N*/   }
/*N*/
/*N*/   if (!xNewParent.is())
/*N*/   {
/*N*/       // are we a valid part of our current page forms ?
/*N*/       FmFormPage* pOldFormPage = PTR_CAST(FmFormPage, GetPage());
/*N*/       ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xOldForms = pOldFormPage ? ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (pOldFormPage->GetForms(), ::com::sun::star::uno::UNO_QUERY) : ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > ();
/*N*/       if (xOldForms.is())
/*N*/       {
/*N*/           // search (upward from our model) for xOldForms
/*?*/           ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild >  xSearch(GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
/*?*/           while (xSearch.is())
/*?*/           {
/*?*/               if (xSearch == xOldForms)
/*?*/                   break;
/*?*/               xSearch = ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild > (xSearch->getParent(), ::com::sun::star::uno::UNO_QUERY);
/*?*/           }
/*?*/           if (xSearch.is())   // implies xSearch == xOldForms, which means we're a valid part of our current page forms hierarchy
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/                 ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild >  xMeAsChild(GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001 /*?*/                xNewParent = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (ensureModelEnv(xMeAsChild->getParent(), ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (pNewFormPage->GetForms(), ::com::sun::star::uno::UNO_QUERY)), ::com::sun::star::uno::UNO_QUERY);
//STRIP001 /*?*/
//STRIP001 /*?*/                if (xNewParent.is())
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    try
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // transfer the events from our (model's) parent to the new (model's) parent, too
//STRIP001 /*?*/                        ::com::sun::star::uno::Reference< ::com::sun::star::script::XEventAttacherManager >  xEventManager(xMeAsChild->getParent(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001 /*?*/                        ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >  xManagerAsIndex(xEventManager, ::com::sun::star::uno::UNO_QUERY);
//STRIP001 /*?*/                        if (xManagerAsIndex.is())
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            sal_Int32 nPos = getElementPos(xManagerAsIndex, xMeAsChild);
//STRIP001 /*?*/                            if (nPos >= 0)
//STRIP001 /*?*/                                aNewEvents = xEventManager->getScriptEvents(nPos);
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                            aNewEvents = aEvts;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    catch(...)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        DBG_ERROR("FmFormObj::SetPage : could not retrieve script events !");
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // now set the page
/*N*/   SdrUnoObj::SetPage(_pNewPage);
/*N*/
/*N*/   // place my model within the new parent container
/*N*/   if (xNewParent.is())
/*N*/   {
/*?*/       ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >  xMeAsFormComp(GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
/*?*/       if (xMeAsFormComp.is())
/*?*/       {
/*?*/           // check if I have another parent (and remove me, if neccessary)
/*?*/           ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xOldParent(xMeAsFormComp->getParent(), ::com::sun::star::uno::UNO_QUERY);
/*?*/           if (xOldParent.is())
/*?*/           {
/*?*/               sal_Int32 nPos = getElementPos(::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > (xOldParent, ::com::sun::star::uno::UNO_QUERY), xMeAsFormComp);
/*?*/               if (nPos > -1)
/*?*/                   xOldParent->removeByIndex(nPos);
/*?*/           }
/*?*/           // and insert into the new container
/*?*/           xNewParent->insertByIndex(xNewParent->getCount(), ::com::sun::star::uno::makeAny(xMeAsFormComp));
/*?*/
/*?*/           // transfer the events
/*?*/           if (aNewEvents.getLength())
/*?*/           {
/*?*/               try
/*?*/               {
/*?*/                   ::com::sun::star::uno::Reference< ::com::sun::star::script::XEventAttacherManager >  xEventManager(xNewParent, ::com::sun::star::uno::UNO_QUERY);
/*?*/                   ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >  xManagerAsIndex(xEventManager, ::com::sun::star::uno::UNO_QUERY);
/*?*/                   if (xManagerAsIndex.is())
/*?*/                   {
/*?*/                       sal_Int32 nPos = getElementPos(xManagerAsIndex, xMeAsFormComp);
/*?*/                       DBG_ASSERT(nPos >= 0, "FmFormObj::SetPage : inserted but not present ?");
/*?*/                       xEventManager->registerScriptEvents(nPos, aNewEvents);
/*?*/                   }
/*?*/               }
/*?*/               catch(...)
/*?*/               {
/*?*/                   DBG_ERROR("FmFormObj::SetPage : could not tranfer script events !");
/*?*/               }
/*?*/
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   // delete my history
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent> xHistory(m_xEnvironmentHistory, ::com::sun::star::uno::UNO_QUERY);
/*N*/   if (xHistory.is())
/*?*/       xHistory->dispose();
/*N*/
/*N*/   m_xEnvironmentHistory = NULL;
/*N*/   m_aEventsHistory.realloc(0);
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_uInt32 FmFormObj::GetObjInventor()   const
/*N*/ {
/*N*/   if( GetModel() && ((FmFormModel*)GetModel())->IsStreamingOldVersion() )
/*?*/       return SdrInventor;
/*N*/   return FmFormInventor;
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_uInt16 FmFormObj::GetObjIdentifier() const
/*N*/ {
/*N*/   if( GetModel() && ((FmFormModel*)GetModel())->IsStreamingOldVersion() )
/*?*/       return OBJ_RECT;
/*N*/   return OBJ_FM_CONTROL;
/*N*/ }

//------------------------------------------------------------------
//STRIP001 void FmFormObj::clonedFrom(const FmFormObj* _pSource)
//STRIP001 {
//STRIP001  DBG_ASSERT(_pSource != NULL, "FmFormObj::clonedFrom : invalid source !");
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent> xHistory(m_xEnvironmentHistory, ::com::sun::star::uno::UNO_QUERY);
//STRIP001  if (xHistory.is())
//STRIP001      xHistory->dispose();
//STRIP001
//STRIP001  m_xEnvironmentHistory = NULL;
//STRIP001  m_aEventsHistory.realloc(0);
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild >  xSourceAsChild(_pSource->GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001  if (!xSourceAsChild.is())
//STRIP001      return;
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xSourceContainer = xSourceAsChild->getParent();
//STRIP001
//STRIP001  m_xEnvironmentHistory = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >(
//STRIP001      ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.form.Forms")),
//STRIP001      ::com::sun::star::uno::UNO_QUERY);
//STRIP001  DBG_ASSERT(m_xEnvironmentHistory.is(), "FmFormObj::clonedFrom : could not create a forms collection !");
//STRIP001
//STRIP001  if (m_xEnvironmentHistory.is())
//STRIP001  {
//STRIP001      ensureModelEnv(xSourceContainer, m_xEnvironmentHistory);
//STRIP001      m_aEventsHistory = aEvts;
//STRIP001          // if we we're clone there was a call to operator=, so aEvts are excatly the events we need here ...
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 SdrObject* FmFormObj::Clone() const
//STRIP001 {
//STRIP001  SdrObject* pReturn = SdrUnoObj::Clone();
//STRIP001
//STRIP001  FmFormObj* pFormObject = PTR_CAST(FmFormObj, pReturn);
//STRIP001  DBG_ASSERT(pFormObject != NULL, "FmFormObj::Clone : invalid clone !");
//STRIP001  if (pFormObject)
//STRIP001      pFormObject->clonedFrom(this);
//STRIP001
//STRIP001  return pReturn;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 SdrObject* FmFormObj::Clone(SdrPage* _pPage, SdrModel* _pModel) const
//STRIP001 {
//STRIP001  SdrObject* pReturn = SdrUnoObj::Clone(_pPage, _pModel);
//STRIP001  if (!pReturn)
//STRIP001      return pReturn;
//STRIP001
//STRIP001  FmFormObj* pCloneAsFormObj = PTR_CAST(FmFormObj, pReturn);
//STRIP001  if (!pCloneAsFormObj)
//STRIP001      return pReturn;
//STRIP001
//STRIP001  FmFormPage* pClonesPage = PTR_CAST(FmFormPage, pReturn->GetPage());
//STRIP001  if (!pClonesPage || !pClonesPage->GetForms().is())
//STRIP001      return pReturn;
//STRIP001
//STRIP001  // build an form environment equivalent to my own withín the destination page
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild >  xMeAsChild(GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001  if (!xMeAsChild.is())
//STRIP001      return pReturn;
//STRIP001
//STRIP001  try
//STRIP001  {
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xMyParent = xMeAsChild->getParent();
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xClonesParent = ensureModelEnv(xMyParent, ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (pClonesPage->GetForms(), ::com::sun::star::uno::UNO_QUERY));
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xNewParentContainer(xClonesParent, ::com::sun::star::uno::UNO_QUERY);
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >  xCloneAsFormComponent(PTR_CAST(FmFormObj, pReturn)->GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001      if (xNewParentContainer.is() && xCloneAsFormComponent.is())
//STRIP001      {
//STRIP001          sal_Int32 nPos = xNewParentContainer->getCount();
//STRIP001          xNewParentContainer->insertByIndex(nPos, ::com::sun::star::uno::makeAny(xCloneAsFormComponent));
//STRIP001          // transfer the events, too
//STRIP001          ::com::sun::star::uno::Reference< ::com::sun::star::script::XEventAttacherManager >  xEventManager(xNewParentContainer, ::com::sun::star::uno::UNO_QUERY);
//STRIP001          if (xEventManager.is())
//STRIP001              xEventManager->registerScriptEvents(nPos, pCloneAsFormObj->GetEvents());
//STRIP001      }
//STRIP001  }
//STRIP001  catch(...)
//STRIP001  {
//STRIP001      DBG_ERROR("FmFormObj::Clone : error while placing the model within it's new env");
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  return pReturn;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 void FmFormObj::operator= (const SdrObject& rObj)
//STRIP001 {
//STRIP001  SdrUnoObj::operator= (rObj);
//STRIP001
//STRIP001  FmFormObj* pFormObj = PTR_CAST(FmFormObj, &rObj);
//STRIP001  if (pFormObj)
//STRIP001  {
//STRIP001      // liegt das ::com::sun::star::awt::UnoControlModel in einer Eventumgebung,
//STRIP001      // dann koennen noch Events zugeordnet sein
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >  xContent(pFormObj->xUnoControlModel, ::com::sun::star::uno::UNO_QUERY);
//STRIP001      if (xContent.is())
//STRIP001      {
//STRIP001          ::com::sun::star::uno::Reference< ::com::sun::star::script::XEventAttacherManager >  xManager(xContent->getParent(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001          ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >  xManagerAsIndex(xManager, ::com::sun::star::uno::UNO_QUERY);
//STRIP001          if (xManagerAsIndex.is())
//STRIP001          {
//STRIP001              sal_Int32 nPos = getElementPos(xManagerAsIndex, xContent);
//STRIP001              if (nPos >= 0)
//STRIP001                  aEvts = xManager->getScriptEvents(nPos);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          aEvts = pFormObj->aEvts;
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------
/*N*/ void FmFormObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   FmFormModel* pModel = (FmFormModel*)GetModel();
/*N*/   if( pModel && pModel->IsStreamingOldVersion() )
/*N*/   {
/*?*/       SdrLayerID nOld = GetLayer();
/*?*/       ((FmFormObj*)this)->NbcSetLayer( pModel->GetControlExportLayerId( *this ) );
/*?*/       SdrUnoObj::WriteData( rOut );
/*?*/       ((FmFormObj*)this)->NbcSetLayer( nOld );
/*?*/       return;
/*N*/   }
/*N*/   SdrUnoObj::WriteData(rOut);
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   SdrUnoObj::ReadData(rHead,rIn);
/*N*/ }

//------------------------------------------------------------------
//STRIP001 ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  FmFormObj::ensureModelEnv(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > & _rSourceContainer, const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  _rTopLevelDestContainer)
//STRIP001 {
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xTopLevelSouce;
//STRIP001  String sAccessPath = getFormComponentAccessPath(_rSourceContainer, xTopLevelSouce);
//STRIP001  if (!xTopLevelSouce.is())
//STRIP001      // somthing went wrong, maybe _rSourceContainer isn't part of a valid forms hierarchy
//STRIP001      return ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ();
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xDestContainer(_rTopLevelDestContainer);
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xSourceContainer(xTopLevelSouce, ::com::sun::star::uno::UNO_QUERY);
//STRIP001  DBG_ASSERT(xSourceContainer.is(), "FmFormObj::ensureModelEnv : the top level source is invalid !");
//STRIP001
//STRIP001  for (xub_StrLen i=0; i<sAccessPath.GetTokenCount('\\'); ++i)
//STRIP001  {
//STRIP001      sal_uInt16 nIndex = sAccessPath.GetToken(i, '\\').ToInt32();
//STRIP001
//STRIP001      // get the DSS of the source form (we have to find an aquivalent for)
//STRIP001      DBG_ASSERT(nIndex<xSourceContainer->getCount(), "FmFormObj::ensureModelEnv : invalid access path !");
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >  xSourceForm;
//STRIP001      xSourceContainer->getByIndex(nIndex) >>= xSourceForm;
//STRIP001      DBG_ASSERT(xSourceForm.is(), "FmFormObj::ensureModelEnv : invalid source form !");
//STRIP001
//STRIP001      ::com::sun::star::uno::Any aSrcCursorSource, aSrcCursorSourceType, aSrcDataSource;
//STRIP001      DBG_ASSERT(::comphelper::hasProperty(FM_PROP_COMMAND, xSourceForm) && ::comphelper::hasProperty(FM_PROP_COMMANDTYPE, xSourceForm)
//STRIP001          && ::comphelper::hasProperty(FM_PROP_DATASOURCE, xSourceForm), "FmFormObj::ensureModelEnv : invalid access path or invalid form (missing props) !");
//STRIP001          // the parent access path should refer to a row set
//STRIP001      try
//STRIP001      {
//STRIP001          aSrcCursorSource        = xSourceForm->getPropertyValue(FM_PROP_COMMAND);
//STRIP001          aSrcCursorSourceType    = xSourceForm->getPropertyValue(FM_PROP_COMMANDTYPE);
//STRIP001          aSrcDataSource          = xSourceForm->getPropertyValue(FM_PROP_DATASOURCE);
//STRIP001      }
//STRIP001      catch(Exception&)
//STRIP001      {
//STRIP001          DBG_ERROR("FmFormObj::ensureModelEnv : could not retrieve a source DSS !");
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      // calc the number of (source) form siblings with the same DSS
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >  xCurrentSourceForm, xCurrentDestForm;
//STRIP001      sal_Int16 nCurrentSourceIndex = 0, nCurrentDestIndex = 0;
//STRIP001      while (nCurrentSourceIndex <= nIndex)
//STRIP001      {
//STRIP001          sal_Bool bEqualDSS = sal_False;
//STRIP001          while (!bEqualDSS)  // (we don't have to check nCurrentSourceIndex here : it's bounded by nIndex)
//STRIP001          {
//STRIP001              xSourceContainer->getByIndex(nCurrentSourceIndex) >>= xCurrentSourceForm;
//STRIP001              DBG_ASSERT(xCurrentSourceForm.is(), "FmFormObj::ensureModelEnv : invalid form ancestor (2) !");
//STRIP001              bEqualDSS = sal_False;
//STRIP001              if (::comphelper::hasProperty(FM_PROP_DATASOURCE, xCurrentSourceForm))
//STRIP001              {   // it is a form
//STRIP001                  try
//STRIP001                  {
//STRIP001                      if  (   ::comphelper::compare(xCurrentSourceForm->getPropertyValue(FM_PROP_COMMAND), aSrcCursorSource)
//STRIP001                          &&  ::comphelper::compare(xCurrentSourceForm->getPropertyValue(FM_PROP_COMMANDTYPE), aSrcCursorSourceType)
//STRIP001                          &&  ::comphelper::compare(xCurrentSourceForm->getPropertyValue(FM_PROP_DATASOURCE), aSrcDataSource)
//STRIP001                          )
//STRIP001                      {
//STRIP001                          bEqualDSS = sal_True;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  catch(Exception&)
//STRIP001                  {
//STRIP001                      DBG_ERROR("FmFormObj::ensureModelEnv : exception while getting a sibling's DSS !");
//STRIP001                  }
//STRIP001
//STRIP001              }
//STRIP001              ++nCurrentSourceIndex;
//STRIP001          }
//STRIP001
//STRIP001          DBG_ASSERT(bEqualDSS, "FmFormObj::ensureModelEnv : found no source form !");
//STRIP001          // ??? at least the nIndex-th one should have been found ???
//STRIP001
//STRIP001          // now search the next one with the given DSS (within the destination container)
//STRIP001          bEqualDSS = sal_False;
//STRIP001          while (!bEqualDSS && (nCurrentDestIndex < xDestContainer->getCount()))
//STRIP001          {
//STRIP001              xDestContainer->getByIndex(nCurrentDestIndex) >>= xCurrentDestForm;
//STRIP001              DBG_ASSERT(xCurrentDestForm.is(), "FmFormObj::ensureModelEnv : invalid destination form !");
//STRIP001              bEqualDSS = sal_False;
//STRIP001              if (::comphelper::hasProperty(FM_PROP_DATASOURCE, xCurrentDestForm))
//STRIP001              {   // it is a form
//STRIP001                  try
//STRIP001                  {
//STRIP001                      if  (   ::comphelper::compare(xCurrentDestForm->getPropertyValue(FM_PROP_COMMAND), aSrcCursorSource)
//STRIP001                          &&  ::comphelper::compare(xCurrentDestForm->getPropertyValue(FM_PROP_COMMANDTYPE), aSrcCursorSourceType)
//STRIP001                          &&  ::comphelper::compare(xCurrentDestForm->getPropertyValue(FM_PROP_DATASOURCE), aSrcDataSource)
//STRIP001                          )
//STRIP001                      {
//STRIP001                          bEqualDSS = sal_True;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  catch(Exception&)
//STRIP001                  {
//STRIP001                      DBG_ERROR("FmFormObj::ensureModelEnv : exception while getting a destination DSS !");
//STRIP001                  }
//STRIP001
//STRIP001              }
//STRIP001              ++nCurrentDestIndex;
//STRIP001          }
//STRIP001
//STRIP001          if (!bEqualDSS)
//STRIP001          {   // There is at least one more source form with the given DSS than destination forms are.
//STRIP001              // correct this ...
//STRIP001              try
//STRIP001              {
//STRIP001                  ::com::sun::star::uno::Reference< ::com::sun::star::io::XPersistObject >  xSourcePersist(xCurrentSourceForm, ::com::sun::star::uno::UNO_QUERY);
//STRIP001                  DBG_ASSERT(xSourcePersist.is(), "FmFormObj::ensureModelEnv : invalid form (no persist object) !");
//STRIP001
//STRIP001                  // create and insert (into the destination) a clone of the form
//STRIP001                  xCurrentDestForm = ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > (cloneUsingProperties(xSourcePersist), ::com::sun::star::uno::UNO_QUERY);
//STRIP001                  DBG_ASSERT(xCurrentDestForm.is(), "FmFormObj::ensureModelEnv : invalid cloned form !");
//STRIP001
//STRIP001                  DBG_ASSERT(nCurrentDestIndex == xDestContainer->getCount(), "FmFormObj::ensureModelEnv : something went wrong with the numbers !");
//STRIP001                  xDestContainer->insertByIndex(nCurrentDestIndex, ::com::sun::star::uno::makeAny(xCurrentDestForm));
//STRIP001
//STRIP001                  ++nCurrentDestIndex;
//STRIP001                      // like nCurrentSourceIndex, nCurrentDestIndex now points 'behind' the form it actally means
//STRIP001              }
//STRIP001              catch(Exception&)
//STRIP001              {
//STRIP001                  DBG_ERROR("FmFormObj::ensureModelEnv : something went seriously wrong while creating a new form !");
//STRIP001                  // no more options anymore ...
//STRIP001                  return ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ();
//STRIP001              }
//STRIP001
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // now xCurrentDestForm is a form aequivalent to xSourceForm (which means they have the same DSS and the same number
//STRIP001      // of left siblings with the same DSS, which counts for all their ancestors, too)
//STRIP001
//STRIP001      // go down
//STRIP001      xDestContainer = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (xCurrentDestForm, ::com::sun::star::uno::UNO_QUERY);
//STRIP001      xSourceContainer = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer > (xSourceForm, ::com::sun::star::uno::UNO_QUERY);
//STRIP001      DBG_ASSERT(xDestContainer.is() && xSourceContainer.is(), "FmFormObj::ensureModelEnv : invalid container !");
//STRIP001  }
//STRIP001
//STRIP001  return ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > (xDestContainer, ::com::sun::star::uno::UNO_QUERY);
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 FASTBOOL FmFormObj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  sal_Bool bResult = SdrUnoObj::EndCreate(rStat, eCmd);
//STRIP001  if (bResult && SDRCREATE_FORCEEND == eCmd && rStat.GetView())
//STRIP001  {
//STRIP001      // ist das Object teil einer ::com::sun::star::form::Form?
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >  xContent(xUnoControlModel, ::com::sun::star::uno::UNO_QUERY);
//STRIP001      if (xContent.is() && pPage)
//STRIP001      {
//STRIP001          // Komponente gehoert noch keiner ::com::sun::star::form::Form an
//STRIP001          if (!xContent->getParent().is())
//STRIP001          {
//STRIP001              ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >  xTemp = ((FmFormPage*)pPage)->GetImpl()->SetDefaults(xContent);
//STRIP001              ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >  xForm(xTemp, ::com::sun::star::uno::UNO_QUERY);
//STRIP001
//STRIP001              // Position des Elements
//STRIP001              sal_Int32 nPos = xForm->getCount();
//STRIP001              xForm->insertByIndex(nPos, ::com::sun::star::uno::makeAny(xContent));
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (nEvent)
//STRIP001          Application::RemoveUserEvent(nEvent);
//STRIP001
//STRIP001      pTempView = (FmFormView*)rStat.GetView();
//STRIP001      nEvent = Application::PostUserEvent(LINK(this,FmFormObj,OnCreate));
//STRIP001  }
//STRIP001  return bResult;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 IMPL_LINK(FmFormObj, OnCreate, void*, EMPTYTAG)
//STRIP001 {
//STRIP001  nEvent = 0;
//STRIP001  if (pTempView)
//STRIP001      pTempView->ObjectCreated(this);
//STRIP001  return 0;
//STRIP001 }
// -----------------------------------------------------------------------------
//STRIP001 sal_Int32 FmFormObj::getType() const
//STRIP001 {
//STRIP001  return m_nType;
//STRIP001 }
// -----------------------------------------------------------------------------



}
