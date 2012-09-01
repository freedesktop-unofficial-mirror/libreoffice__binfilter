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

#ifndef _E3D_DEFLT3D_HXX
#define _E3D_DEFLT3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_goodies/base3d.hxx>

namespace binfilter {

class SfxItemSet;

/*************************************************************************
|*
|* Klasse zum verwalten der 3D-Default Attribute
|*
\************************************************************************/

class E3dDefaultAttributes
{
private:
    // Compound-Objekt
    Color               aDefaultAmbientColor;

//  B3dMaterial         aDefaultBackMaterial;
    BOOL                bDefaultCreateNormals                   ;
    BOOL                bDefaultCreateTexture                   ;
    BOOL                bDefaultUseDifferentBackMaterial        ;

    // Cube-Objekt
    Vector3D            aDefaultCubePos;
    Vector3D            aDefaultCubeSize;
    UINT16              nDefaultCubeSideFlags;
    BOOL                bDefaultCubePosIsCenter                 ;

    // Sphere-Objekt
    Vector3D            aDefaultSphereCenter;
    Vector3D            aDefaultSphereSize;

    // Lathe-Objekt
    long                nDefaultLatheEndAngle;
    double              fDefaultLatheScale;
    BOOL                bDefaultLatheSmoothed                   ;
    BOOL                bDefaultLatheSmoothFrontBack            ;
    BOOL                bDefaultLatheCharacterMode              ;
    BOOL                bDefaultLatheCloseFront;
    BOOL                bDefaultLatheCloseBack;

    // Extrude-Objekt
    double              fDefaultExtrudeScale;
    BOOL                bDefaultExtrudeSmoothed                 ;
    BOOL                bDefaultExtrudeSmoothFrontBack          ;
    BOOL                bDefaultExtrudeCharacterMode            ;
    BOOL                bDefaultExtrudeCloseFront;
    BOOL                bDefaultExtrudeCloseBack;

    // Scene-Objekt
    BOOL                bDefaultDither                          ;

public:
    // Konstruktor
    E3dDefaultAttributes();

    // Defaults zuruecksetzen
    void Reset();

    // Getter/Setter fuer Default-Werte aller 3D-Objekte
    // Compound-Objekt
    const Color& GetDefaultAmbientColor() const { return aDefaultAmbientColor; }
    void SetDefaultAmbientColor(const Color& rNew) { aDefaultAmbientColor = rNew; }

    BOOL GetDefaultCreateNormals() const { return bDefaultCreateNormals; }
    void SetDefaultCreateNormals(const BOOL bNew) { bDefaultCreateNormals = bNew; }
    BOOL GetDefaultCreateTexture() const { return bDefaultCreateTexture; }
    void SetDefaultCreateTexture(const BOOL bNew) { bDefaultCreateTexture = bNew; }
    BOOL GetDefaultUseDifferentBackMaterial() const { return bDefaultUseDifferentBackMaterial; }
    void SetDefaultUseDifferentBackMaterial(const BOOL bNew) { bDefaultUseDifferentBackMaterial = bNew; }

    // Cube-Objekt
    const Vector3D& GetDefaultCubePos() const { return aDefaultCubePos; }
    void SetDefaultCubePos(const Vector3D& rNew) { aDefaultCubePos = rNew; }
    const Vector3D& GetDefaultCubeSize() const { return aDefaultCubeSize; }
    void SetDefaultCubeSize(const Vector3D& rNew) { aDefaultCubeSize = rNew; }
    UINT16 GetDefaultCubeSideFlags() const { return nDefaultCubeSideFlags; }
    void SetDefaultCubeSideFlags(const UINT16 nNew) { nDefaultCubeSideFlags = nNew; }
    BOOL GetDefaultCubePosIsCenter() const { return bDefaultCubePosIsCenter; }
    void SetDefaultCubePosIsCenter(const BOOL bNew) { bDefaultCubePosIsCenter = bNew; }

    // Sphere-Objekt
    const Vector3D& GetDefaultSphereCenter() const { return aDefaultSphereCenter; }
    void SetDefaultSphereCenter(const Vector3D& rNew) { aDefaultSphereCenter = rNew; }
    const Vector3D& GetDefaultSphereSize() const { return aDefaultSphereSize; }
    void SetDefaultSphereSize(const Vector3D& rNew) { aDefaultSphereSize = rNew; }

    // Lathe-Objekt
    long GetDefaultLatheEndAngle() const { return nDefaultLatheEndAngle; }
    void SetDefaultLatheEndAngle(const long nNew) { nDefaultLatheEndAngle = nNew; }
    double GetDefaultLatheScale() const { return fDefaultLatheScale; }
    void SetDefaultLatheScale(const double fNew) { fDefaultLatheScale = fNew; }
    BOOL GetDefaultLatheSmoothed() const { return bDefaultLatheSmoothed; }
    void SetDefaultLatheSmoothed(const BOOL bNew) { bDefaultLatheSmoothed = bNew; }
    BOOL GetDefaultLatheSmoothFrontBack() const { return bDefaultLatheSmoothFrontBack; }
    void SetDefaultLatheSmoothFrontBack(const BOOL bNew) { bDefaultLatheSmoothFrontBack = bNew; }
    BOOL GetDefaultLatheCharacterMode() const { return bDefaultLatheCharacterMode; }
    void SetDefaultLatheCharacterMode(const BOOL bNew) { bDefaultLatheCharacterMode = bNew; }
    BOOL GetDefaultLatheCloseFront() const { return bDefaultLatheCloseFront; }
    void SetDefaultLatheCloseFront(const BOOL bNew) { bDefaultLatheCloseFront = bNew; }
    BOOL GetDefaultLatheCloseBack() const { return bDefaultLatheCloseBack; }
    void SetDefaultLatheCloseBack(const BOOL bNew) { bDefaultLatheCloseBack = bNew; }

    // Extrude-Objekt
    double GetDefaultExtrudeScale() const { return fDefaultExtrudeScale; }
    void SetDefaultExtrudeScale(const double fNew) { fDefaultExtrudeScale = fNew; }
    BOOL GetDefaultExtrudeSmoothed() const { return bDefaultExtrudeSmoothed; }
    void SetDefaultExtrudeSmoothed(const BOOL bNew) { bDefaultExtrudeSmoothed = bNew; }
    BOOL GetDefaultExtrudeSmoothFrontBack() const { return bDefaultExtrudeSmoothFrontBack; }
    void SetDefaultExtrudeSmoothFrontBack(const BOOL bNew) { bDefaultExtrudeSmoothFrontBack = bNew; }
    BOOL GetDefaultExtrudeCharacterMode() const { return bDefaultExtrudeCharacterMode; }
    void SetDefaultExtrudeCharacterMode(const BOOL bNew) { bDefaultExtrudeCharacterMode = bNew; }
    BOOL GetDefaultExtrudeCloseFront() const { return bDefaultExtrudeCloseFront; }
    void SetDefaultExtrudeCloseFront(const BOOL bNew) { bDefaultExtrudeCloseFront = bNew; }
    BOOL GetDefaultExtrudeCloseBack() const { return bDefaultExtrudeCloseBack; }
    void SetDefaultExtrudeCloseBack(const BOOL bNew) { bDefaultExtrudeCloseBack = bNew; }

    // Scene-Objekt
    BOOL GetDefaultDither() const { return bDefaultDither; }
    void SetDefaultDither(const BOOL bNew) { bDefaultDither = bNew; }
};

}//end of namespace binfilter
#endif          // _E3D_DEFLT3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
