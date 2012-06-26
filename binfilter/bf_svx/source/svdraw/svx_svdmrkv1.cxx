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

#include "svdmrkv.hxx"
namespace binfilter {

/*N*/ BOOL SdrMarkView::HasMarkedPoints() const
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (!ImpIsFrameHandles()) {
/*N*/       ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/       if (nMarkAnz<=nFrameHandlesLimit) {
/*N*/           for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
/*?*/               const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/               const SdrUShortCont* pPts=pM->GetMarkedPoints();
/*?*/               bRet=pPts!=NULL && pPts->GetCount()!=0;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ void SdrMarkView::SetPlusHandlesAlwaysVisible(BOOL bOn)
/*N*/ { // HandlePaint optimieren !!!!!!!
/*N*/   if (bOn!=bPlusHdlAlways) {
/*?*/       bPlusHdlAlways=bOn;
/*?*/       SetMarkHandles();
/*?*/       MarkListHasChanged();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////



/*N*/ BOOL SdrMarkView::HasMarkedGluePoints() const
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
/*?*/       const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/       const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
/*?*/       bRet=pPts!=NULL && pPts->GetCount()!=0;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
