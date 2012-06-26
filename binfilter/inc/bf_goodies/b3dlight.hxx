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

#ifndef _B3D_B3DLIGHT_HXX
#define _B3D_B3DLIGHT_HXX

#include <bf_svtools/bf_solar.h>


#include "vector3d.hxx"

#include "matril3d.hxx"

#include <tools/stream.hxx>

namespace binfilter {

/*************************************************************************
|*
|* Unterstuetzte Lichtquellen
|*
\************************************************************************/

#define BASE3D_MAX_NUMBER_LIGHTS        (8)

enum Base3DLightNumber
{
    Base3DLight0 = 0,
    Base3DLight1,
    Base3DLight2,
    Base3DLight3,
    Base3DLight4,
    Base3DLight5,
    Base3DLight6,
    Base3DLight7,
    Base3DLightNone
};

/*************************************************************************
|*
|* Basisklasse fuer Lichtquellen
|*
\************************************************************************/

class B3dLight
{
private:
    Color                   aAmbient;
    Color                   aDiffuse;
    Color                   aSpecular;
    Vector3D                aPosition;
    Vector3D                aPositionEye;
    Vector3D                aSpotDirection;
    Vector3D                aSpotDirectionEye;
    UINT16                  nSpotExponent;
    double                  fSpotCutoff;
    double                  fCosSpotCutoff;
    double                  fConstantAttenuation;
    double                  fLinearAttenuation;
    double                  fQuadraticAttenuation;

    unsigned                bIsFirstLight           : 1;
    unsigned                bIsEnabled              : 1;
    unsigned                bIsDirectionalSource    : 1;
    unsigned                bIsSpot                 : 1;
    unsigned                bIsAmbient              : 1;
    unsigned                bIsDiffuse              : 1;
    unsigned                bIsSpecular             : 1;
    unsigned                bLinearOrQuadratic      : 1;

public:
    B3dLight();

    virtual ~B3dLight() {}

    // Zugriffsfunktionen
    void SetIntensity(const Color rNew,
        Base3DMaterialValue=Base3DMaterialAmbient);
    const Color GetIntensity(Base3DMaterialValue=Base3DMaterialAmbient);
    void SetPositionEye(const Vector3D& rNew)
        { aPositionEye=rNew; }
    const Vector3D& GetPositionEye()
        { return aPositionEye; }
    void SetPosition(const Vector3D& rNew)
        { aPosition=rNew; }
    const Vector3D& GetPosition()
        { return aPosition; }
    const Vector3D& GetSpotDirection()
        { return aSpotDirection; }
    const Vector3D& GetSpotDirectionEye()
        { return aSpotDirectionEye; }
    void SetSpotExponent(UINT16 nNew)
        { nSpotExponent=nNew; }
    UINT16 GetSpotExponent()
        { return nSpotExponent; }
    double GetSpotCutoff()
        { return fSpotCutoff; }
    double GetCosSpotCutoff()
        { return fCosSpotCutoff; }
    void SetConstantAttenuation(double fNew)
        { fConstantAttenuation=fNew; }
    double GetConstantAttenuation()
        { return fConstantAttenuation; }
    double GetLinearAttenuation()
        { return fLinearAttenuation; }
    double GetQuadraticAttenuation()
        { return fQuadraticAttenuation; }

    void Enable(BOOL bNew=TRUE)
        { bIsEnabled=bNew; }
    BOOL IsEnabled()
        { return bIsEnabled; }
    void SetFirst(BOOL bNew=TRUE)
        { bIsFirstLight=bNew; }
    BOOL IsFirst()
        { return bIsFirstLight; }
    void SetDirectionalSource(BOOL bNew=TRUE)
        { bIsDirectionalSource=bNew; }
    BOOL IsDirectionalSource()
        { return bIsDirectionalSource; }
    BOOL IsSpot()
        { return bIsSpot; }
    BOOL IsAmbient()
        { return bIsAmbient; }
    BOOL IsDiffuse()
        { return bIsDiffuse; }
    BOOL IsSpecular()
        { return bIsSpecular; }
    BOOL IsLinearOrQuadratic()
        { return bLinearOrQuadratic; }

    void Init();

    // Laden/Speichern in StarView
    virtual void ReadData(SvStream& rIn);
};

/*************************************************************************
|*
|* Gruppe von Lichtquellen
|*
\************************************************************************/

class B3dLightGroup
{
private:
    // Lichtquellen
    B3dLight                aLight[BASE3D_MAX_NUMBER_LIGHTS];

    // lokale Parameter des LightModels
    Color                   aGlobalAmbientLight;

    // Hauptschalter fuer die Beleuchtung
    unsigned                bLightingEnabled            : 1;
    unsigned                bLocalViewer                : 1;
    unsigned                bModelTwoSide               : 1;

public:
    // Konstruktor
    B3dLightGroup();

    virtual ~B3dLightGroup() {}

    // lokale Parameter des LightModels
    virtual void SetGlobalAmbientLight(const Color rNew);
    const Color GetGlobalAmbientLight();
    virtual void SetLocalViewer(BOOL bNew=TRUE);
    virtual void SetModelTwoSide(BOOL bNew=FALSE);
    BOOL GetModelTwoSide();

    // Hauptschalter fuer die Beleuchtung
    virtual void EnableLighting(BOOL bNew=TRUE);

    // Lichtquellen Interface
    void SetIntensity(const Color rNew,
        Base3DMaterialValue=Base3DMaterialAmbient,
        Base3DLightNumber=Base3DLight0);
    const Color GetIntensity(Base3DMaterialValue=Base3DMaterialAmbient,
        Base3DLightNumber=Base3DLight0);
    void SetPosition(const Vector3D& rNew,
        Base3DLightNumber=Base3DLight0);
    void SetDirection(const Vector3D& rNew,
        Base3DLightNumber=Base3DLight0);
    const Vector3D& GetDirection(Base3DLightNumber=Base3DLight0);
    void Enable(BOOL bNew=TRUE,
        Base3DLightNumber=Base3DLight0);
    BOOL IsEnabled(Base3DLightNumber=Base3DLight0);

    // Direkter Zugriff auf B3dLight
    B3dLight& GetLightObject(Base3DLightNumber=Base3DLight0);

    // Laden/Speichern in StarView
    virtual void ReadData(SvStream& rIn);
};

}//end of namespace binfilter

#endif          // _B3D_B3DLIGHT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
