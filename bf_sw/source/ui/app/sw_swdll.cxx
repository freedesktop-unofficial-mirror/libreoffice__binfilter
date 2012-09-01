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


#include <bf_svx/svdobj.hxx>
#include <rtl/logfile.hxx>

#include "globdoc.hrc"

#include <wdocsh.hxx>
#include <globdoc.hxx>
#include <swmodule.hxx>
#include <swtypes.hxx>
#include <init.hxx>
#include <dobjfac.hxx>
#include <cfgid.h>
namespace binfilter {

/*************************************************************************
|*
|* Init
|*
\************************************************************************/

/*N*/ void SwDLL::Init()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDLL" );
/*N*/
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sw-DLL too
/*N*/
/*N*/   // the SdModule must be created
/*N*/   SwModuleDummy** ppShlPtr = (SwModuleDummy**) GetAppData(BF_SHL_WRITER);
/*N*/
/*N*/   SvFactory* pDocFact     = (SvFactory*)(*ppShlPtr)->pSwDocShellFactory;
/*N*/   SvFactory* pWDocFact    = (SvFactory*)(*ppShlPtr)->pSwWebDocShellFactory;
/*N*/   SvFactory* pGlobDocFact = (SvFactory*)(*ppShlPtr)->pSwGlobalDocShellFactory;
/*N*/   delete (*ppShlPtr);
/*N*/     SwModule* pModule = new SwModule( pWDocFact, pDocFact, pGlobDocFact );
/*N*/   (*ppShlPtr) = pModule;
/*N*/   (*ppShlPtr)->pSwDocShellFactory         = pDocFact    ;
/*N*/   (*ppShlPtr)->pSwWebDocShellFactory      = pWDocFact   ;
/*N*/   (*ppShlPtr)->pSwGlobalDocShellFactory   = pGlobDocFact;
/*N*/
/*N*/   SdrObjFactory::InsertMakeObjectHdl( LINK( &aSwObjectFactory, SwObjectFactory, MakeObject ) );
/*N*/
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "Init Core/UI/Filter" );
/*N*/
/*N*/   //Initialisierung der Statics
/*N*/   ::binfilter::_InitCore();
/*N*/   ::binfilter::_InitFilter();
///*N*/   ::binfilter::_InitUI();
/*N*/
/*N*/   pModule->InitAttrPool();
/*N*/   //jetzt darf das SwModule seinen Pool anlegen
/*N*/ }

/*************************************************************************
|*
|* Exit
|*
\************************************************************************/

/*N*/ void SwDLL::Exit()
/*N*/ {
/*N*/   // called directly befor unloading the DLL
/*N*/   // do whatever you want, Sw-DLL is accessible
/*N*/
/*N*/   // der Pool muss vor den statics geloescht werden
/*N*/   SW_MOD()->RemoveAttrPool();
/*N*/
///*N*/   ::binfilter::_FinitUI();
/*N*/   ::binfilter::_FinitFilter();
/*N*/   ::binfilter::_FinitCore();
/*N*/   // Objekt-Factory austragen
/*N*/   SdrObjFactory::RemoveMakeObjectHdl(LINK(&aSwObjectFactory, SwObjectFactory, MakeObject ));
/*N*/    // the SwModule must be destroyed
/*N*/   SwModuleDummy** ppShlPtr = (SwModuleDummy**) GetAppData(BF_SHL_WRITER);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
