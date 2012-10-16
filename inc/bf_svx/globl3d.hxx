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

#ifndef _E3D_GLOBL3D_HXX
#define _E3D_GLOBL3D_HXX

#include <bf_svtools/bf_solar.h>
namespace binfilter {

//#define ESODEBUG
#define E3D_STREAMING

const double PrecisionLimit = 1.0e-14;

const UINT32 E3dInventor = UINT32('E')*0x00000001+
                           UINT32('3')*0x00000100+
                           UINT32('D')*0x00010000+
                           UINT32('1')*0x01000000;

const UINT16 E3D_DISPLAYOBJ_ID  = 1;
const UINT16 E3D_SCENE_ID       = 2;
const UINT16 E3D_POLYSCENE_ID   = 3;
const UINT16 E3D_LIGHT_ID       = 5;
const UINT16 E3D_DISTLIGHT_ID   = 6;
const UINT16 E3D_POINTLIGHT_ID  = 7;
const UINT16 E3D_SPOTLIGHT_ID   = 8;
const UINT16 E3D_OBJECT_ID      = 10;
const UINT16 E3D_POLYOBJ_ID     = 11;
const UINT16 E3D_CUBEOBJ_ID     = 12;
const UINT16 E3D_SPHEREOBJ_ID   = 13;
const UINT16 E3D_POINTOBJ_ID    = 14;
const UINT16 E3D_EXTRUDEOBJ_ID  = 15;
const UINT16 E3D_LATHEOBJ_ID    = 16;
const UINT16 E3D_LABELOBJ_ID    = 20;
const UINT16 E3D_COMPOUNDOBJ_ID = 21;
const UINT16 E3D_POLYGONOBJ_ID  = 22;

}//end of namespace binfilter
#endif      // _E3D_GLOBL3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
