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

#ifndef SVTOOLS_ASYNCLINK_HXX
#define  SVTOOLS_ASYNCLINK_HXX

#include <bf_svtools/bf_solar.h>
#include <tools/link.hxx>
#include <osl/mutex.hxx>

class Timer;

namespace binfilter {

class AsynchronLink
{
    Link   _aLink;
    ULONG  _nEventId;
    Timer* _pTimer;
    BOOL   _bInCall;
    BOOL*  _pDeleted;
    void*  _pArg;
    osl::Mutex* _pMutex;

    DECL_STATIC_LINK( AsynchronLink, HandleCall, void* );
    void Call_Impl( void* pArg );

public:
    AsynchronLink( const Link& rLink ) :
        _aLink( rLink ), _nEventId( 0 ), _pTimer( 0 ), _bInCall( FALSE ),
        _pDeleted( 0 ), _pMutex( 0 ){}
    AsynchronLink() : _nEventId( 0 ), _pTimer( 0 ), _bInCall( FALSE ),
            _pDeleted( 0 ), _pMutex( 0 ){}
    ~AsynchronLink();

    void CreateMutex();
    void operator=( const Link& rLink ) { _aLink = rLink; }
    void Call( void* pObj, BOOL bAllowDoubles = FALSE,
               BOOL bUseTimer = FALSE );
    void ClearPendingCall( );
    BOOL IsSet() const { return _aLink.IsSet(); }
    Link GetLink() const { return _aLink; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
