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
#ifdef WIN
#define _TL_LANG_SPECIAL
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <com/sun/star/lang/XTypeProvider.hpp>

#include "appdata.hxx"
#include "plugobj.hxx"
#include "arrdecl.hxx"
#include "macrconf.hxx"

#include <bf_svtools/imgdef.hxx>

#include "frameobj.hxx"
#include "docfile.hxx"
#include "sfxtypes.hxx"
#include "appimp.hxx"
#include "fcontnr.hxx"
#include "nochaos.hxx"
#include "doctempl.hxx"
#include "dlgcont.hxx"
#include "scriptcont.hxx"
#include "misccfg.hxx"
#include "docfac.hxx"

namespace binfilter {

SV_DECL_PTRARR(SfxInitLinkList, Link*, 2, 2)

//-------------------------------------------------------------------------

/*?*/ void SfxApplication::Deinitialize()
/*?*/ {
/*?*/     if ( bDowning )
/*?*/         return;
/*?*/
/*?*/   StarBASIC::Stop();
/*?*/
/*?*/   bDowning = TRUE; // wegen Timer aus DecAliveCount und QueryExit
/*?*/
/*?*/   bDowning = FALSE;
/*?*/   DBG_ASSERT( !SfxObjectShell::GetFirst(),
/*?*/               "existing SfxObjectShell after Execute" );
/*?*/   bDowning = TRUE;
/*?*/
/*?*/   // call derived application-exit
/*?*/   bInExit = TRUE;
/*?*/   Exit();
/*?*/
/*?*/     // Controller u."a. freigeben
/*?*/     // dabei sollten auch restliche Komponenten ( Beamer! ) verschwinden
/*?*/   SfxObjectFactory::ClearAll_Impl();
//      pBasMgr = NULL;
/*?*/   if( pImp->pBasicLibContainer )
/*?*/       pImp->pBasicLibContainer->release();
/*?*/   if( pImp->pDialogLibContainer )
/*?*/       pImp->pDialogLibContainer->release();
/*?*/
/*?*/   bInExit = FALSE;
/*?*/
/*?*/   // ab hier d"urfen keine SvObjects mehr existieren
/*?*/   DELETEX(pAppData_Impl->pMatcher);
/*?*/   DELETEX(pAppData_Impl->pSfxFrameObjectFactoryPtr);
/*?*/
/*?*/   DELETEX(pAppData_Impl->pEventConfig);
/*?*/   DELETEX(pAppData_Impl->pMiscConfig);
/*?*/   SfxMacroConfig::Release_Impl();
/*?*/   DELETEX(pAppData_Impl->pInitLinkList);
/*?*/
/*?*/     DELETEX(pImp->pEventHdl);
/*?*/     DELETEX(pImp->pObjShells);
/*?*/
/*?*/   NoChaos::ReleaseItemPool();
/*?*/   pAppData_Impl->pPool = NULL;
/*?*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
