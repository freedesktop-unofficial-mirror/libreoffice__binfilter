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
#ifndef SVTOOLS_TESTTOOL_HXX
#define SVTOOLS_TESTTOOL_HXX

#include <bf_svtools/bf_solar.h>
#include <tools/link.hxx>
#include <bf_tools/string.hxx>

class Application;
class SvStream;

namespace binfilter
{

class StatementFlow;
class CommunicationManager;
class CommunicationLink;
#if OSL_DEBUG_LEVEL > 1
class EditWindow;
#endif
class ImplRC;

class RemoteControl
{
    friend class StatementFlow;

    BOOL         m_bIdleInserted;
#if OSL_DEBUG_LEVEL > 1
    EditWindow *m_pDbgWin;
#endif
    ImplRC* pImplRC;

public:
    RemoteControl();
    ~RemoteControl();
    BOOL QueCommands( ULONG nServiceId, SvStream *pIn );
    SvStream* GetReturnStream();

    DECL_LINK( IdleHdl,   Application* );
    DECL_LINK( CommandHdl, Application* );

    DECL_LINK( QueCommandsEvent, CommunicationLink* );
    ULONG nStoredServiceId;
    SvStream *pStoredStream;

    void ExecuteURL( String &aURL );

protected:
    CommunicationManager *pServiceMgr;
    SvStream *pRetStream;
};

}

#endif // SVTOOLS_TESTTOOL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
