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
#ifndef _SFX_MAP_HXX
#define _SFX_MAP_HXX

#include <bf_svtools/bf_solar.h>

#include <tools.hxx>
#include <sfxitems.hxx>
namespace binfilter {

class SfxInterface;
class SfxDispatcher;
class SfxShell;

class SfxMap: public SfxWhichMap
{
    const SfxInterface  *pInterface;
    const SfxDispatcher *pDispatcher;
    BOOL                bRecursive;
public:
    inline              SfxMap();
    inline              SfxMap(const SfxDispatcher &rDispatcher );
                        SfxMap(const SfxShell &, BOOL bRecursiveSearch = FALSE );
    inline              SfxMap( const SfxMap & rMap);

    virtual USHORT      GetWhich(USHORT nSlot) const;
    virtual USHORT      GetSlot(USHORT nWhich) const;
    virtual SfxWhichMap*Clone() const;
};

//--------------------------------------------------------------------

inline SfxMap::SfxMap():
        SfxWhichMap( FALSE ),
        pInterface( 0 ),
        pDispatcher( 0 ),
        bRecursive( FALSE )
{
}

inline SfxMap::SfxMap( const SfxMap & rMap):
        SfxWhichMap( TRUE ),
        pInterface( rMap.pInterface ),
        pDispatcher( rMap.pDispatcher ),
        bRecursive( rMap.bRecursive )
{
}

inline SfxMap::SfxMap(const SfxDispatcher &rDispatcher ):
        SfxWhichMap( TRUE ),
        pInterface( 0 ),
        pDispatcher( &rDispatcher ),
        bRecursive( 0 )
{
}

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
