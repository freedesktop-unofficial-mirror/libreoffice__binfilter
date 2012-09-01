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

#include "svditer.hxx"
#include "scene3d.hxx"

namespace binfilter {

SdrObjListIter::SdrObjListIter(const SdrObjList& rObjList, SdrIterMode eMode, BOOL bReverse)
:   mnIndex(0L),
    mbReverse(bReverse)
{
    ImpProcessObjectList(rObjList, eMode);
    Reset();
}

SdrObjListIter::SdrObjListIter(const SdrObject& rGroup, SdrIterMode eMode, BOOL bReverse)
:   mnIndex(0L),
    mbReverse(bReverse)
{
    ImpProcessObjectList(*rGroup.GetSubList(), eMode);
    Reset();
}

void SdrObjListIter::ImpProcessObjectList(const SdrObjList& rObjList, SdrIterMode eMode)
{
    for(sal_uInt32 a(0L); a < rObjList.GetObjCount(); a++)
    {
        SdrObject* pObj = rObjList.GetObj(a);
        sal_Bool bIsGroup(pObj->IsGroupObject());

        // #99190# 3D objects are no group objects, IsGroupObject()
        // only tests if pSub is not null ptr :-(
        if(bIsGroup && pObj->ISA(E3dObject) && !pObj->ISA(E3dScene))
            bIsGroup = sal_False;

        if(eMode != IM_DEEPNOGROUPS || !bIsGroup)
            maObjList.push_back( pObj );

        if(bIsGroup && eMode != IM_FLAT)
            ImpProcessObjectList(*pObj->GetSubList(), eMode);
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
