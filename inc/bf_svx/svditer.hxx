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

#ifndef _SVDITER_HXX
#define _SVDITER_HXX

#include <bf_svtools/bf_solar.h>
#include <sal/types.h>
#include <vector>

namespace binfilter {

class SdrObjList;
class SdrObject;

// SdrObjListIter methods:
// IM_FLAT              : Flach ueber die Liste
// IM_DEEPWITHGROUPS    : Mit rekursivem Abstieg, Next() liefert auch Gruppenobjekte
// IM_DEEPNOGROUPS      : Mit rekursivem Abstieg, Next() liefert keine Gruppenobjekte
enum SdrIterMode { IM_FLAT, IM_DEEPWITHGROUPS, IM_DEEPNOGROUPS};

typedef ::std::vector< SdrObject* > SdrObjectList;

class SdrObjListIter
{
    SdrObjectList   maObjList;
    size_t          mnIndex;
    BOOL            mbReverse;

    void ImpProcessObjectList(const SdrObjList& rObjList, SdrIterMode eMode);

public:
    SdrObjListIter(const SdrObjList& rObjList, SdrIterMode eMode = IM_DEEPNOGROUPS, BOOL bReverse = FALSE);
    SdrObjListIter(const SdrObject& rGroup, SdrIterMode eMode = IM_DEEPNOGROUPS, BOOL bReverse = FALSE);

    void Reset() { mnIndex = (mbReverse ? maObjList.size() : 0L); }
    BOOL IsMore() const { return (mbReverse ? mnIndex != 0 : ( mnIndex < maObjList.size())); }

    SdrObject* Next() {
        return IsMore() ? maObjList[ mbReverse ? --mnIndex : mnIndex++ ] : NULL;
    }
};

}//end of namespace binfilter
#endif //_SVDITER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
