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

#include "svdstr.hrc"
#include "svdio.hxx"
#include "globl3d.hxx"
#include "label3d.hxx"

namespace binfilter {

/*N*/ TYPEINIT1(E3dLabelObj, E3dPointObj);

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dLabelObj::~E3dLabelObj()
/*N*/ {
/*N*/   // zugehoeriges 2D-SdrObject loeschen
/*N*/   delete p2DLabelObj;
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dLabelObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_LABELOBJ_ID;
/*N*/ }

/*************************************************************************
|*
|* SdrPage auch an p2DLabelObj setzen
|*
\************************************************************************/

/*N*/ void E3dLabelObj::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   E3dPointObj::SetPage(pNewPage);
/*N*/   if ( p2DLabelObj )
/*N*/       p2DLabelObj->SetPage(pNewPage);
/*N*/ }

/*************************************************************************
|*
|* SdrModel auch an p2DLabelObj setzen
|*
\************************************************************************/

/*N*/ void E3dLabelObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   E3dPointObj::SetModel(pNewModel);
/*N*/   if ( p2DLabelObj )
/*N*/       p2DLabelObj->SetModel(pNewModel);
/*N*/ }

/*************************************************************************
|*
|* Aus Stream laden
|*
\************************************************************************/

/*N*/ void E3dLabelObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       E3dPointObj::ReadData(rHead, rIn);
/*N*/
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dLabelObj");
/*N*/ #endif
/*N*/
/*N*/   // loeschen, falls schon vorhanden
/*N*/       delete p2DLabelObj;
/*N*/       p2DLabelObj = NULL;
/*N*/
/*N*/       SdrObjIOHeaderLookAhead aHead(rIn, STREAM_READ);
/*N*/
/*N*/       p2DLabelObj = SdrObjFactory::MakeNewObject(aHead.nInventor,
/*N*/                                                  aHead.nIdentifier, GetPage());
/*N*/       if ( p2DLabelObj != NULL )
/*N*/       {
/*N*/           rIn >> *p2DLabelObj;
/*N*/           p2DLabelObj->SetModel(GetModel());
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aHead.SkipRecord();
/*N*/       }
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
