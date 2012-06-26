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

#include <bf_svx/svxids.hrc>

#include <document.hxx>

#include <starmath.hrc>
namespace binfilter {

BOOL SmDLL::bInitialized = FALSE;

/*************************************************************************
|*
|* Initialisierung
|*
\************************************************************************/
/*N*/ void SmDLL::Init()
/*N*/ {
/*N*/     if ( bInitialized )
/*N*/         return;
/*N*/
/*N*/     bInitialized = TRUE;
/*N*/
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sd-DLL too
/*N*/
/*N*/   // the SdModule must be created
/*N*/
/*N*/   SmModuleDummy** ppShlPtr = (SmModuleDummy**) GetAppData(BF_SHL_SM);
/*N*/
/*N*/     SvFactory* pFact = PTR_CAST(SvFactory,(*ppShlPtr)->pSmDocShellFactory);
/*N*/     delete (*ppShlPtr);
/*N*/     (*ppShlPtr) = new SmModule(pFact);
/*N*/     (*ppShlPtr)->pSmDocShellFactory = pFact;
/*N*/ }

/*************************************************************************
|*
|* Deinitialisierung
|*
\************************************************************************/
/*N*/ void SmDLL::Exit()
/*N*/ {
/*N*/   // the SdModule must be destroyed
/*N*/   SmModuleDummy** ppShlPtr = (SmModuleDummy**) GetAppData(BF_SHL_SM);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/
/*N*/   *GetAppData(BF_SHL_SM) = 0;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
