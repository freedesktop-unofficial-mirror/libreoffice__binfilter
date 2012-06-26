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

#include <stdio.h>
#include <tools/rcid.h>

#include <cstdarg>
#include "app.hxx"
#include "arrdecl.hxx"
#include "docfac.hxx"
#include "module.hxx"

namespace binfilter {

static SfxModuleArr_Impl* pModules=0;

/*N*/ TYPEINIT1(SfxModule, SfxShell);

BOOL SfxModule::QueryUnload()
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
    return FALSE;
}

SfxModule* SfxModule::Load()
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
    return 0;
}

void SfxModule::Free()
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
}


ResMgr* SfxModule::GetResMgr()
{
    return pResMgr;
}

//====================================================================
/*N*/ SfxModule::SfxModule( ResMgr* pMgrP, BOOL bDummyP,
/*N*/                     SfxObjectFactory* pFactoryP, ... )
/*N*/   : pResMgr( pMgrP ), bDummy( bDummyP )
/*N*/ {
/*N*/   if( !bDummy )
/*N*/   {
/*N*/       SfxApplication *pApp = SFX_APP();
/*N*/       SfxModuleArr_Impl& rArr = GetModules_Impl();
/*N*/       SfxModule* pPtr = (SfxModule*)this;
/*N*/       rArr.C40_INSERT( SfxModule, pPtr, rArr.Count() );
/*N*/       SetPool( &pApp->GetPool() );
/*N*/   }
/*N*/   std::va_list pVarArgs;
/*N*/   va_start( pVarArgs, pFactoryP );
/*N*/   for ( SfxObjectFactory *pArg = pFactoryP; pArg;
/*N*/        pArg = va_arg( pVarArgs, SfxObjectFactory* ) )
/*N*/       pArg->SetModule_Impl( this );
/*N*/   va_end(pVarArgs);
/*N*/ }

/*N*/ SfxModule::~SfxModule()
/*N*/ {
/*N*/   if( !bDummy )
/*N*/   {
/*N*/       if ( SFX_APP()->Get_Impl() )
/*N*/       {
/*N*/           // Das Modul wird noch vor dem DeInitialize zerst"ort, also auis dem Array entfernen
/*N*/           SfxModuleArr_Impl& rArr = GetModules_Impl();
/*N*/           for( USHORT nPos = rArr.Count(); nPos--; )
/*N*/           {
/*N*/               if( rArr[ nPos ] == this )
/*N*/               {
/*N*/                   rArr.Remove( nPos );
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       delete pResMgr;
/*N*/   }
/*N*/ }

/*N*/ SfxModuleArr_Impl& SfxModule::GetModules_Impl()
/*N*/ {
/*N*/     if( !pModules )
/*N*/         pModules = new SfxModuleArr_Impl;
/*N*/     return *pModules;
/*N*/ };
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
