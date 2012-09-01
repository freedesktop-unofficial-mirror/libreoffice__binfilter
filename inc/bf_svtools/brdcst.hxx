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
#ifndef _SFXBRDCST_HXX
#define _SFXBRDCST_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/rtti.hxx>

#include <bf_svtools/svarray.hxx>

namespace binfilter {

class SfxListener;
class SfxHint;

SV_DECL_PTRARR( SfxListenerArr_Impl, SfxListener*, 0, 2 )

#define SFX_FORWARD( rBC, rBCT, rHint, rHintT ) \
        Forward( rBC, rHint )

//-------------------------------------------------------------------------

class  SfxBroadcaster
{
friend class SfxListener;

    SfxListenerArr_Impl     aListeners;

private:
    BOOL         AddListener( SfxListener& rListener );
    void                    RemoveListener( SfxListener& rListener );
    const SfxBroadcaster&   operator=(const SfxBroadcaster &); // verboten

protected:
    void                    SFX_FORWARD(SfxBroadcaster& rBC, const TypeId& rBCType,
                                        const SfxHint& rHint, const TypeId& rHintType);
    virtual void            ListenersGone();

public:
                            TYPEINFO();

                            SfxBroadcaster();
                            SfxBroadcaster( const SfxBroadcaster &rBC );
    virtual                 ~SfxBroadcaster();

    void                    Broadcast( const SfxHint &rHint );

    BOOL                    HasListeners() const;
    USHORT                  GetListenerCount() const { return aListeners.Count(); }
    SfxListener*            GetListener( USHORT nNo ) const
                            { return (SfxListener*) aListeners[nNo]; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
