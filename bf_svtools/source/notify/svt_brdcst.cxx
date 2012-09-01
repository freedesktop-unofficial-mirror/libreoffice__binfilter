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

#include <tools/debug.hxx>
#include <osl/diagnose.h>

#include <bf_svtools/hint.hxx>
#include <bf_svtools/smplhint.hxx>
#include <bf_svtools/lstner.hxx>

#define _SFX_BRDCST_CXX
#include <bf_svtools/brdcst.hxx>

namespace binfilter
{

//====================================================================
DBG_NAME(SfxBroadcaster)
TYPEINIT0(SfxBroadcaster);

//====================================================================

//====================================================================
// broadcast immediately


void SfxBroadcaster::Broadcast( const SfxHint &rHint )
{
    DBG_CHKTHIS(SfxBroadcaster, 0);

    // is anybody to notify?
    if ( aListeners.Count() /*! || aGlobListeners.Count() */ )
    {
        // notify all registered listeners exactly once
        for ( USHORT n = 0; n < aListeners.Count(); ++n )
        {
            SfxListener* pListener = aListeners[n];
            if ( pListener )
                pListener->Notify( *this, rHint );
        }
    }
}

//--------------------------------------------------------------------

// unregister all listeners

SfxBroadcaster::~SfxBroadcaster()
{
    DBG_DTOR(SfxBroadcaster, 0);

    Broadcast( SfxSimpleHint(SFX_HINT_DYING) );

    // remove all still registered listeners
    for ( USHORT nPos = 0; nPos < aListeners.Count(); ++nPos )
    {
        SfxListener *pListener = aListeners[nPos];
        if ( pListener )
            pListener->RemoveBroadcaster_Impl(*this);
    }
}

//--------------------------------------------------------------------

// simple ctor of class SfxBroadcaster

SfxBroadcaster::SfxBroadcaster()
{
    DBG_CTOR(SfxBroadcaster, 0);
}

//--------------------------------------------------------------------

// copy ctor of class SfxBroadcaster


SfxBroadcaster::SfxBroadcaster( const SfxBroadcaster &rBC )
{
    DBG_CTOR(SfxBroadcaster, 0);

    for ( USHORT n = 0; n < rBC.aListeners.Count(); ++n )
    {
        SfxListener *pListener = rBC.aListeners[n];
        if ( pListener )
            pListener->StartListening( *this );
    }
}

//--------------------------------------------------------------------

// add a new SfxListener to the list

BOOL SfxBroadcaster::AddListener( SfxListener& rListener )
{
    DBG_CHKTHIS(SfxBroadcaster, 0);
    const SfxListener *pListener = &rListener;
    const SfxListener *pNull = 0;
    USHORT nFreePos = aListeners.GetPos( pNull );
    if ( nFreePos < aListeners.Count() )
        aListeners.GetData()[nFreePos] = pListener;
    else if ( aListeners.Count() < (USHRT_MAX-1) )
        aListeners.Insert( pListener, aListeners.Count() );
    else
    {
        OSL_FAIL( "array overflow" );
        return FALSE;
    }

    DBG_ASSERT( USHRT_MAX != aListeners.GetPos(pListener),
                "AddListener failed" );
    return TRUE;
}

//--------------------------------------------------------------------

// called, if no more listeners exists

void SfxBroadcaster::ListenersGone()
{
    DBG_CHKTHIS(SfxBroadcaster,0);
}

//--------------------------------------------------------------------

// forward a notification to all registered listeners

void SfxBroadcaster::SFX_FORWARD(SfxBroadcaster& rBC, const TypeId& rBCType,
                               const SfxHint& rHint, const TypeId& rHintType)
{
    const USHORT nCount = aListeners.Count();
    for ( USHORT i = 0; i < nCount; ++i )
    {
        SfxListener *pListener = aListeners[i];
        if ( pListener )
            pListener->SFX_NOTIFY( rBC, rBCType, rHint, rHintType);
    }
}

//--------------------------------------------------------------------

// remove one SfxListener from the list

void SfxBroadcaster::RemoveListener( SfxListener& rListener )
{
    {DBG_CHKTHIS(SfxBroadcaster, 0);}
    const SfxListener *pListener = &rListener;
    USHORT nPos = aListeners.GetPos(pListener);
    DBG_ASSERT( nPos != USHRT_MAX, "RemoveListener: Listener unknown" );
    aListeners.GetData()[nPos] = 0;
    if ( !HasListeners() )
        ListenersGone();
}

//--------------------------------------------------------------------

BOOL SfxBroadcaster::HasListeners() const
{
    for ( USHORT n = 0; n < aListeners.Count(); ++n )
        if ( aListeners.GetObject(n) != 0 )
            return TRUE;
    return FALSE;
}

//--------------------------------------------------------------------
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
