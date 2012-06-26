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

#include "svdundo.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "scene3d.hxx"


namespace binfilter {

/*N*/ SdrUndoGroup::SdrUndoGroup(SdrModel& rNewMod)
/*N*/ : SdrUndoAction(rNewMod),
/*N*/   aBuf(1024,32,32),
/*N*/   eFunction(SDRREPFUNC_OBJ_NONE)      /*#72642#*/
/*N*/ {}

/*N*/ SdrUndoGroup::~SdrUndoGroup()
/*N*/ {
/*N*/   Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::Clear()
/*N*/ {
/*N*/   for (ULONG nu=0; nu<GetActionCount(); nu++) {
/*N*/       SdrUndoAction* pAct=GetAction(nu);
/*N*/       delete pAct;
/*N*/   }
/*N*/   aBuf.Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::AddAction(SdrUndoAction* pAct)
/*N*/ {
/*N*/   aBuf.Insert(pAct,CONTAINER_APPEND);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// OBJECTS
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoObj::SdrUndoObj(SdrObject& rNewObj):
/*N*/   SdrUndoAction(*rNewObj.GetModel()),
/*N*/   pObj(&rNewObj)
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoGeoObj::SdrUndoGeoObj(SdrObject& rNewObj):
/*N*/   SdrUndoObj(rNewObj),
/*N*/   pUndoGeo(NULL),
/*N*/   pRedoGeo(NULL),
/*N*/   pUndoGroup(NULL)
/*N*/ {
/*N*/   SdrObjList* pOL=rNewObj.GetSubList();
/*N*/   if (pOL!=NULL && pOL->GetObjCount() && !rNewObj.ISA(E3dScene))
/*N*/   {
/*?*/       // Aha, Gruppenobjekt
/*?*/       // AW: Aber keine 3D-Szene, dann nur fuer die Szene selbst den Undo anlegen
/*?*/       pUndoGroup=new SdrUndoGroup(*pObj->GetModel());
/*?*/       ULONG nObjAnz=pOL->GetObjCount();
/*?*/       for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
/*?*/           pUndoGroup->AddAction(new SdrUndoGeoObj(*pOL->GetObj(nObjNum)));
/*?*/       }
/*N*/   } else {
/*N*/       pUndoGeo=pObj->GetGeoData();
/*N*/   }
/*N*/ }

/*N*/ SdrUndoGeoObj::~SdrUndoGeoObj()
/*N*/ {
/*N*/   if (pUndoGeo!=NULL) delete pUndoGeo;
/*N*/   if (pRedoGeo!=NULL) delete pRedoGeo;
/*N*/   if (pUndoGroup!=NULL) delete pUndoGroup;
/*N*/ }

/*N*/ SdrUndoObjList::SdrUndoObjList(SdrObject& rNewObj, bool bOrdNumDirect):
/*N*/   SdrUndoObj(rNewObj),
/*N*/   bOwner(FALSE),
/*N*/   pView(NULL),
/*N*/   pPageView(NULL)
/*N*/ {
/*N*/   pObjList=pObj->GetObjList();
/*N*/   if (bOrdNumDirect) {
/*?*/       nOrdNum=pObj->GetOrdNumDirect();
/*N*/   } else {
/*N*/       nOrdNum=pObj->GetOrdNum();
/*N*/   }
/*N*/ }
/*N*/
/*N*/ SdrUndoObjList::~SdrUndoObjList()
/*N*/ {
/*N*/   if (pObj!=NULL && IsOwner())
/*N*/   {
/*N*/       // Attribute muessen wieder in den regulaeren Pool
/*?*/       DBG_BF_ASSERT(0, "STRIP");
/*?*/
/*?*/       // nun loeschen
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PAGES
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoPage::SdrUndoPage(SdrPage& rNewPg):
/*N*/   SdrUndoAction(*rNewPg.GetModel()), pPage(&rNewPg)
/*N*/ { }

/*N*/ SdrUndoPageList::SdrUndoPageList(SdrPage& rNewPg):
/*N*/   SdrUndoPage(rNewPg),
/*N*/   bItsMine(FALSE)
/*N*/ {
/*N*/   nPageNum=rNewPg.GetPageNum();
/*N*/ }

/*N*/ SdrUndoPageList::~SdrUndoPageList()
/*N*/ {
/*N*/   if(bItsMine && pPage)
/*N*/   {
/*?*/       delete pPage;
/*?*/       pPage = 0L;
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
