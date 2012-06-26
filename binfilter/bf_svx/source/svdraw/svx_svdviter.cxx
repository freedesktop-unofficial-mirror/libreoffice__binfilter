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

#include "svdviter.hxx"
#include "svdpage.hxx"
#include "svdview.hxx"
#include "svdpagv.hxx"

namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrViewIter::ImpInitVars()
/*N*/ {
/*N*/   nListenerNum=0;
/*N*/   nPageViewNum=0;
/*N*/   nOutDevNum=0;
/*N*/   pAktView=NULL;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrViewIter::SdrViewIter(const SdrObject* pObject_, bool bNoMasterPage_)
/*N*/ {
/*N*/   pObject=pObject_;
/*N*/   pModel=pObject_!=NULL ? pObject_->GetModel() : NULL;
/*N*/   pPage=pObject_!=NULL ? pObject_->GetPage() : NULL;
/*N*/   bNoMasterPage=bNoMasterPage_;
/*N*/   if (pModel==NULL || pPage==NULL) {
/*N*/       pModel=NULL;
/*N*/       pPage=NULL;
/*N*/   }
/*N*/   ImpInitVars();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ bool SdrViewIter::ImpCheckPageView(SdrPageView* pPV) const
/*N*/ {
/*N*/   if (pPage!=NULL) {
/*N*/       bool bMaster=pPage->IsMasterPage();
/*N*/       USHORT nPageNum=pPage->GetPageNum();
/*N*/       SdrPage* pPg=pPV->GetPage();
/*N*/       if (pPg==pPage) {
/*N*/           if (pObject!=NULL) {
/*N*/               // Objekt gewuenscht? Na dann erstmal sehen, ob
/*N*/               // das Obj in dieser PageView auch sichtbar ist.
/*N*/               SetOfByte aObjLay;
/*N*/               pObject->GetLayer(aObjLay);
/*N*/               aObjLay&=pPV->GetVisibleLayers();
/*N*/               return !aObjLay.IsEmpty();
/*N*/           } else {
/*N*/               return TRUE;
/*N*/           }
/*N*/       } else {
/*N*/           if (!bNoMasterPage && bMaster && (pObject==NULL || !pObject->IsNotVisibleAsMaster())) {
/*N*/               USHORT nMasterPageAnz=pPg->GetMasterPageCount();
/*N*/               USHORT nMasterPagePos=0;
/*N*/               while (nMasterPagePos<nMasterPageAnz) {
/*N*/                   if (nPageNum==pPg->GetMasterPageNum(nMasterPagePos)) {
/*N*/                       // Aha, die gewuenschte Page ist also MasterPage in dieser PageView
/*N*/                       if (pObject!=NULL) {
/*N*/                           // Objekt gewuenscht? Na dann erstmal sehen, ob
/*N*/                           // das Obj in dieser PageView auch sichtbar ist.
/*N*/                           SetOfByte aObjLay;
/*N*/                           pObject->GetLayer(aObjLay);
/*N*/                           aObjLay&=pPV->GetVisibleLayers();
/*N*/                           aObjLay&=pPg->GetMasterPageVisibleLayers(nMasterPagePos);
/*N*/                           if (!aObjLay.IsEmpty()) {
/*N*/                               return TRUE;
/*N*/                           } // ansonsten die naechste MasterPage der Page ansehen...
/*N*/                       } else {
/*N*/                           return TRUE;
/*N*/                       }
/*N*/                   }
/*N*/                   nMasterPagePos++;
/*N*/               }
/*N*/           }
/*N*/           // MasterPage nicht erlaubt oder keine passende gefunden
/*N*/           return FALSE;
/*N*/       }
/*N*/   } else {
/*N*/       return TRUE;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrView* SdrViewIter::ImpFindView()
/*N*/ {
/*N*/   if (pModel!=NULL) {
/*N*/       USHORT nLsAnz=pModel->GetListenerCount();
/*N*/       while (nListenerNum<nLsAnz) {
/*N*/           SfxListener* pLs=pModel->GetListener(nListenerNum);
/*N*/           pAktView=PTR_CAST(SdrView,pLs);
/*N*/           if (pAktView!=NULL) {
/*N*/               if (pPage!=NULL) {
/*N*/                   USHORT nPvAnz=pAktView->GetPageViewCount();
/*N*/                   USHORT nPvNum=0;
/*N*/                   while (nPvNum<nPvAnz) {
/*N*/                       SdrPageView* pPV=pAktView->GetPageViewPvNum(nPvNum);
/*N*/                       if (ImpCheckPageView(pPV)) {
/*N*/                           return pAktView;
/*N*/                       }
/*N*/                       nPvNum++;
/*N*/                   }
/*N*/               } else {
/*N*/                   return pAktView;
/*N*/               }
/*N*/           }
/*N*/           nListenerNum++;
/*N*/       }
/*N*/   }
/*N*/   pAktView=NULL;
/*N*/   return pAktView;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrView* SdrViewIter::FirstView()
/*N*/ {
/*N*/   ImpInitVars();
/*N*/   return ImpFindView();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrView* SdrViewIter::NextView()
/*N*/ {
/*N*/   nListenerNum++;
/*N*/   return ImpFindView();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
