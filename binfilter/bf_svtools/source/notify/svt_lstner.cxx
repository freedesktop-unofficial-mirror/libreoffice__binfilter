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

#include <bf_svtools/hint.hxx>
#include <bf_svtools/brdcst.hxx>

#define _SFX_LSTNER_CXX
#include <bf_svtools/lstner.hxx>

namespace binfilter
{

//====================================================================
DBG_NAME(SfxListener)
TYPEINIT0(SfxListener);

//====================================================================
// simple ctor of class SfxListener

SfxListener::SfxListener()
{
    DBG_CTOR(SfxListener, 0);
}
//--------------------------------------------------------------------

// copy ctor of class SfxListener

SfxListener::SfxListener( const SfxListener &rListener )
{
    DBG_CTOR(SfxListener, 0);

    for ( USHORT n = 0; n < rListener.aBCs.Count(); ++n )
        StartListening( *rListener.aBCs[n] );
}
//--------------------------------------------------------------------

// unregisteres the SfxListener from its SfxBroadcasters

SfxListener::~SfxListener()
{
    DBG_DTOR(SfxListener, 0);

    // unregister at all remainding broadcasters
    for ( USHORT nPos = 0; nPos < aBCs.Count(); ++nPos )
    {
        SfxBroadcaster *pBC = aBCs[nPos];
        pBC->RemoveListener(*this);
    }
}

//--------------------------------------------------------------------

// unregisteres at a specific SfxBroadcaster

void SfxListener::RemoveBroadcaster_Impl( SfxBroadcaster& rBC )
{
    DBG_CHKTHIS(SfxListener, 0);

    const SfxBroadcaster *pBC = &rBC;
    aBCs.Remove( aBCs.GetPos(pBC), 1 );
}

//--------------------------------------------------------------------

// registeres at a specific SfxBroadcaster

BOOL SfxListener::StartListening( SfxBroadcaster& rBroadcaster, BOOL bPreventDups )
{
    DBG_CHKTHIS(SfxListener, 0);

    if ( !bPreventDups || !IsListening( rBroadcaster ) )
    {
        if ( rBroadcaster.AddListener(*this) )
        {
            const SfxBroadcaster *pBC = &rBroadcaster;
            aBCs.Insert( pBC, aBCs.Count() );

            DBG_ASSERT( IsListening(rBroadcaster), "StartListening failed" );
            return TRUE;
        }

    }
    return FALSE;
}

//--------------------------------------------------------------------

// unregisteres at a specific SfxBroadcaster

BOOL SfxListener::EndListening( SfxBroadcaster& rBroadcaster, BOOL bAllDups )
{
    DBG_CHKTHIS(SfxListener, 0);

    if ( !IsListening( rBroadcaster ) )
        return FALSE;

    do
    {
        rBroadcaster.RemoveListener(*this);
        const SfxBroadcaster *pBC = &rBroadcaster;
        aBCs.Remove( aBCs.GetPos(pBC), 1 );
    }
    while ( bAllDups && IsListening( rBroadcaster ) );
    return TRUE;
}

//--------------------------------------------------------------------

// unregisteres all Broadcasters

void SfxListener::EndListeningAll()
{
    DBG_CHKTHIS(SfxListener, 0);

    // MI: bei Optimierung beachten: Seiteneffekte von RemoveListener beachten!
    while ( aBCs.Count() )
    {
        SfxBroadcaster *pBC = aBCs.GetObject(0);
        pBC->RemoveListener(*this);
        aBCs.Remove( 0, 1 );
    }
}

//--------------------------------------------------------------------

BOOL SfxListener::IsListening( SfxBroadcaster& rBroadcaster ) const
{
    const SfxBroadcaster *pBC = &rBroadcaster;
    return USHRT_MAX != aBCs.GetPos( pBC );
}

//--------------------------------------------------------------------

// base implementation of notification handler

#ifdef DBG_UTIL
void SfxListener::SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                              const SfxHint&, const TypeId& rHintType )
#else
void SfxListener::SFX_NOTIFY( SfxBroadcaster&, const TypeId&,
                              const SfxHint&, const TypeId& )
#endif
{
    #ifdef DBG_UTIL
    const SfxBroadcaster *pBC = &rBC;
    DBG_ASSERT( USHRT_MAX != aBCs.GetPos(pBC),
                "notification from unregistered broadcaster" );
    #endif
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
