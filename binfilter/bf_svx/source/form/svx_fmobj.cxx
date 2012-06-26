/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "fmobj.hxx"
#include "fmprop.hrc"

#include <com/sun/star/script/XEventAttacherManager.hpp>

#include "fmmodel.hxx"
#include "fmtools.hxx"
#include "fmresids.hrc"

#include <fmview.hxx>

#include "fmglob.hxx"
#include "fmpgeimp.hxx"
#include "fmpage.hxx"

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::binfilter::svxform;

/*N*/ TYPEINIT1(FmFormObj, SdrUnoObj);
/*N*/ DBG_NAME(FmFormObj)
//------------------------------------------------------------------

//------------------------------------------------------------------
/*N*/ FmFormObj::FmFormObj(sal_Int32 _nType)
/*N*/         :SdrUnoObj(sal_False)
/*N*/         ,pTempView(0)
/*N*/         ,nEvent(0)
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
/*?*/               sal_Int32 nLclPos = getElementPos(::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > (xOldParent, ::com::sun::star::uno::UNO_QUERY), xMeAsFormComp);
/*?*/               if (nLclPos > -1)
/*?*/                   xOldParent->removeByIndex(nLclPos);
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
/*?*/                       sal_Int32 nLclPos = getElementPos(xManagerAsIndex, xMeAsFormComp);
/*?*/                       DBG_ASSERT(nLclPos >= 0, "FmFormObj::SetPage : inserted but not present ?");
/*?*/                       xEventManager->registerScriptEvents(nLclPos, aNewEvents);
/*?*/                   }
/*?*/               }
/*?*/               catch(...)
/*?*/               {
/*?*/                   OSL_FAIL("FmFormObj::SetPage : could not tranfer script events !");
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

/*N*/ void FmFormObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   SdrUnoObj::ReadData(rHead,rIn);
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
