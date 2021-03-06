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
#ifndef _SFXITEMITER_HXX
#define _SFXITEMITER_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/itemset.hxx>

namespace binfilter
{

class SfxPoolItem;
class SfxItemSet;
class SfxItemPool;

class  SfxItemIter
{
    // Item-Feld - Start & Ende
    const SfxItemSet&   _rSet;
    USHORT              _nStt, _nEnd, _nAkt;

public:
    SfxItemIter( const SfxItemSet& rSet );
    ~SfxItemIter();

    // falls es diese gibt, returne sie, sonst 0
    const SfxPoolItem* FirstItem()
                       { _nAkt = _nStt;
                         return _rSet._nCount ? *(_rSet._aItems+_nAkt) : 0; }
    const SfxPoolItem* LastItem()
                       { _nAkt = _nEnd;
                         return _rSet._nCount ? *(_rSet._aItems+_nAkt) : 0; }
    const SfxPoolItem* GetCurItem()
                       { return _rSet._nCount ? *(_rSet._aItems+_nAkt) : 0; }
    const SfxPoolItem* NextItem();

    BOOL               IsAtStart() const { return _nAkt == _nStt; }
    BOOL               IsAtEnd() const   { return _nAkt == _nEnd; }

    USHORT             GetCurPos() const { return _nAkt; }
    USHORT             GetFirstPos() const { return _nStt; }
    USHORT             GetLastPos() const { return _nEnd; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
