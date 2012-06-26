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

#include "svdvmark.hxx"
#include "svdobj.hxx"
#include "svdpntv.hxx"

namespace binfilter {

/*N*/ SdrViewUserMarker::SdrViewUserMarker(SdrPaintView* pView_)
/*N*/ : pView(pView_),
/*N*/   pForcedOutDev(NULL),
/*N*/   pPoint(NULL),
/*N*/   pRect(NULL),
/*N*/   pPoly(NULL),
/*N*/   pPolyPoly(NULL),
/*N*/   pXPoly(NULL),
/*N*/   pXPolyPoly(NULL),
/*N*/   eAlign(SDRMARKER_ALIGNCENTER),
/*N*/   nPixelDistance(0),
/*N*/   nLineWdt(0),
/*N*/   nCrossSize(0),
/*N*/   bLineWdtLog(FALSE),
/*N*/   bCrossSizeLog(FALSE),
/*N*/   bSolidArea(FALSE),
/*N*/   bDashed(FALSE),
/*N*/   bCrossHair(FALSE),
/*N*/   bStripes(FALSE),
/*N*/   bEllipse(FALSE),
/*N*/   bPolyLine(FALSE),
/*N*/   bAnimate(FALSE),
/*N*/   bVisible(FALSE),
/*N*/   nAnimateDelay(0),
/*N*/   nAnimateSpeed(0),
/*N*/   nAnimateAnz(0),
/*N*/   bAnimateBwd(FALSE),
/*N*/   bAnimateToggle(FALSE),
/*N*/   nAnimateDelayCountDown(0),
/*N*/   nAnimateSpeedCountDown(0),
/*N*/   nAnimateNum(0),
/*N*/   bHasPointer(FALSE),
/*N*/   bMouseMovable(FALSE)
/*N*/ {
/*N*/   if (pView!=NULL) pView->ImpInsertUserMarker(this);
/*N*/   bAnimateToggle=TRUE;
/*N*/ }
/*N*/
/*N*/ SdrViewUserMarker::~SdrViewUserMarker()
/*N*/ {
/*N*/   if (bVisible) {DBG_BF_ASSERT(0, "STRIP"); }
/*N*/   if (pView!=NULL) pView->ImpRemoveUserMarker(this);
/*N*/   ImpDelGeometrics();
/*N*/ }
/*N*/
/*N*/ void SdrViewUserMarker::ImpDelGeometrics()
/*N*/ {
/*N*/   if (pPoint    !=NULL) { delete pPoint    ; pPoint    =NULL; }
/*N*/   if (pRect     !=NULL) { delete pRect     ; pRect     =NULL; }
/*N*/   if (pPoly     !=NULL) { delete pPoly     ; pPoly     =NULL; }
/*N*/   if (pPolyPoly !=NULL) { delete pPolyPoly ; pPolyPoly =NULL; }
/*N*/   if (pXPoly    !=NULL) { delete pXPoly    ; pXPoly    =NULL; }
/*N*/   if (pXPolyPoly!=NULL) { delete pXPolyPoly; pXPolyPoly=NULL; }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
