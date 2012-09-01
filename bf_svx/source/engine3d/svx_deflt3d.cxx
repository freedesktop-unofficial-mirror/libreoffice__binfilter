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

#define ITEMID_COLOR            SID_ATTR_3D_LIGHTCOLOR


#include "cube3d.hxx"

#include "svxids.hrc"


namespace binfilter {

/*************************************************************************
|*
|* Klasse zum verwalten der 3D-Default Attribute
|*
\************************************************************************/

// Konstruktor
/*N*/ E3dDefaultAttributes::E3dDefaultAttributes()
/*N*/ {
/*N*/   Reset();
/*N*/ }

/*N*/ void E3dDefaultAttributes::Reset()
/*N*/ {
/*N*/   // Compound-Objekt
/*N*/ //    aDefaultFrontMaterial;
/*N*/ //    aDefaultBackMaterial;
/*N*/   bDefaultCreateNormals = TRUE;
/*N*/   bDefaultCreateTexture = TRUE;
/*N*/   bDefaultUseDifferentBackMaterial = FALSE;
/*N*/
/*N*/   // Cube-Objekt
/*N*/   aDefaultCubePos = Vector3D(-500.0, -500.0, -500.0);
/*N*/   aDefaultCubeSize = Vector3D(1000.0, 1000.0, 1000.0);
/*N*/   nDefaultCubeSideFlags = CUBE_FULL;
/*N*/   bDefaultCubePosIsCenter = FALSE;
/*N*/
/*N*/   // Sphere-Objekt
/*N*/   aDefaultSphereCenter = Vector3D(0.0, 0.0, 0.0);
/*N*/   aDefaultSphereSize = Vector3D(1000.0, 1000.0, 1000.0);
/*N*/
/*N*/   // Lathe-Objekt
/*N*/   nDefaultLatheEndAngle = 3600;
/*N*/   fDefaultLatheScale = 1.0;
/*N*/   bDefaultLatheSmoothed = TRUE;
/*N*/   bDefaultLatheSmoothFrontBack = FALSE;
/*N*/   bDefaultLatheCharacterMode = FALSE;
/*N*/   bDefaultLatheCloseFront = TRUE;
/*N*/   bDefaultLatheCloseBack = TRUE;
/*N*/
/*N*/   // Extrude-Objekt
/*N*/   fDefaultExtrudeScale = 1.0;
/*N*/   bDefaultExtrudeSmoothed = TRUE;
/*N*/   bDefaultExtrudeSmoothFrontBack = FALSE;
/*N*/   bDefaultExtrudeCharacterMode = FALSE;
/*N*/   bDefaultExtrudeCloseFront = TRUE;
/*N*/   bDefaultExtrudeCloseBack = TRUE;
/*N*/
/*N*/   // Scene-Objekt
/*N*/ //    aDefaultLightGroup;
/*N*/   bDefaultDither = TRUE;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
