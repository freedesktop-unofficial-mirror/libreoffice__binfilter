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


#include "xdef.hxx"

#include "globl3d.hxx"

#include "polysc3d.hxx"


namespace binfilter {

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPEINIT1(E3dPolyScene, E3dScene);

E3dPolyScene::E3dPolyScene()
    : E3dScene()
{
}

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

UINT16 E3dPolyScene::GetObjIdentifier() const
{
    return E3D_POLYSCENE_ID;
}

/*************************************************************************
|*
|* Paint
|*
\************************************************************************/

bool E3dPolyScene::Paint(
    ExtOutputDevice& /*rOut*/,
    const SdrPaintInfoRec& /*rInfoRec*/
) const
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
    return FALSE;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
