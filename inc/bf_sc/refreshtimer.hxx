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

#ifndef SC_REFRESHTIMER_HXX
#define SC_REFRESHTIMER_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/timer.hxx>
#include <osl/mutex.hxx>
namespace binfilter {

//=============================================================================
class ScRefreshTimerControl
{
private:
    ::osl::Mutex    aMutex;
    USHORT          nBlockRefresh;

public:
    ScRefreshTimerControl() : nBlockRefresh(0) {}

    void SetAllowRefresh( BOOL b ) {
        if ( b && nBlockRefresh )
            --nBlockRefresh;
        else if ( !b && nBlockRefresh < (USHORT)(~0) )
            ++nBlockRefresh;
    }

    BOOL IsRefreshAllowed() const { return !nBlockRefresh; }

    ::osl::Mutex& GetMutex() { return aMutex; }
};


//=============================================================================
class ScRefreshTimerProtector
{
private:
    ScRefreshTimerControl * const * ppControl;

public:
    ScRefreshTimerProtector( ScRefreshTimerControl * const * pp );

    ~ScRefreshTimerProtector() {
        if ( ppControl && *ppControl )
            (*ppControl)->SetAllowRefresh( TRUE );
    }
};


//=============================================================================
class ScRefreshTimer : public AutoTimer
{
private:
    ScRefreshTimerControl * const * ppControl;

    void AppendToControl() {}

    void RemoveFromControl() {}

    void Start() {
        if ( GetTimeout() )
            AutoTimer::Start();
    }

public:
    ScRefreshTimer() : ppControl(0) { SetTimeout( 0 ); }

    ScRefreshTimer( ULONG nSeconds ) : ppControl(0) {
        SetTimeout( nSeconds * 1000 );
        Start();
    }

    ScRefreshTimer( const ScRefreshTimer& r )
        : AutoTimer( r )
        , ppControl(0)
    {}

    virtual ~ScRefreshTimer();

    ScRefreshTimer& operator=( const ScRefreshTimer& r ) {
        SetRefreshControl(0);
        AutoTimer::operator=( r );
        return *this;
    }

    BOOL operator==( const ScRefreshTimer& r ) const
        { return GetTimeout() == r.GetTimeout(); }

    BOOL operator!=( const ScRefreshTimer& r ) const
        { return !ScRefreshTimer::operator==( r ); }

    void StartRefreshTimer() { Start(); }

    void SetRefreshControl( ScRefreshTimerControl * const * pp ) {
        RemoveFromControl();
        ppControl = pp;
        AppendToControl();
    }

    void SetRefreshHandler( const Link& rLink )
        { SetTimeoutHdl( rLink ); }

    ULONG GetRefreshDelay() const
        { return GetTimeout() / 1000; }

    void StopRefreshTimer() { Stop(); }

    virtual void SetRefreshDelay( ULONG nSeconds );
};


} //namespace binfilter
#endif // SC_REFRESHTIMER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
