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
#include <tools/config.hxx>

#define _SVSTDARR_STRINGS
#include <bf_svtools/svstdarr.hxx>

#include "app.hxx"
#include "appdata.hxx"
#include "doctempl.hxx"
#include "docfile.hxx"
#include "imestatuswindow.hxx"

#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

/*N*/ SfxAppData_Impl::SfxAppData_Impl( SfxApplication* pApp ) :
            pSfxFrameObjectFactoryPtr(0),
/*N*/       pInitLinkList(0),
/*N*/       pMatcher( 0 ),
/*N*/       pCancelMgr( 0 ),
/*N*/       pPool(0),
/*N*/       pEventConfig(0),
/*N*/       pMiscConfig(0),
            pThisDocument(0),
/*N*/       pProgress(0),
/*N*/       nBasicCallLevel(0),
/*N*/       nRescheduleLocks(0),
/*N*/       nInReschedule(0),
/*N*/       m_xImeStatusWindow(new sfx2::appl::ImeStatusWindow(
/*N*/                                *pApp, ::legacy_binfilters::getLegacyProcessServiceFactory())),
/*N*/       bInQuit(sal_False),
/*N*/       bInException( sal_False )
/*N*/ {
/*N*/ }

/*N*/ SfxAppData_Impl::~SfxAppData_Impl()
/*N*/ {
/*N*/   delete pCancelMgr;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
