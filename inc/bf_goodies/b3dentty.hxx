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

#ifndef _B3D_B3DENTITY_HXX
#define _B3D_B3DENTITY_HXX

#include <bf_svtools/bf_solar.h>


#include "b3dcolor.hxx"

#include "point4d.hxx"

#include "bucket.hxx"

namespace binfilter {

/*************************************************************************
|*
|* Merkt sich einen Punkt plus Normale plus Texturkoordinate
|* (in Zukunft noch weitere Attribute, bsp. Farbe, Kante, Linienmodus
|*
\************************************************************************/

//class Base3DCommon;
//class Base3D;
class B3dTransformationSet;
class Matrix4D;

class B3dEntity
{
private:
    // Data defining this point, it's normal and texture coordinates
    Point4D                 aPoint;
    Vector3D                aNormal;
    Vector3D                aPlaneNormal;
    Vector3D                aTexCoor;
    B3dColor                aColor;

    // Ist die diesem Punkt folgende Kante sichtbar ?
    UINT8                   bEdgeFlag;

    // BOOLEAN flags
    // Gueltigkeit der geometrischen Daten
    unsigned                bValid          : 1;

    // Wird eine Normale verwendet ?
    unsigned                bNormalUsed     : 1;

    // Wird eine Texturkoordinate verwendet ?
    unsigned                bTexCoorUsed    : 1;

    // Sind die geometrischen Daten schon in DeviceKoordinaten
    // umgerechnet ?
    unsigned                bDeviceCoor     : 1;

public:
    B3dEntity() { Reset(); }

    BOOL IsValid() { return bValid; }
    void SetValid(BOOL bNew=TRUE) { bValid = bNew; }

    BOOL IsNormalUsed() { return bNormalUsed; }
    void SetNormalUsed(BOOL bNew=TRUE) { bNormalUsed = bNew; }

    BOOL IsTexCoorUsed() { return bTexCoorUsed; }
    void SetTexCoorUsed(BOOL bNew=TRUE) { bTexCoorUsed = bNew; }

    BOOL IsDeviceCoor() { return bDeviceCoor; }
    void SetDeviceCoor(BOOL bNew=TRUE) { bDeviceCoor = bNew; }

    BOOL IsEdgeVisible() { return bEdgeFlag; }
    void SetEdgeVisible(BOOL bNew=TRUE) { bEdgeFlag = bNew; }

    Point4D& Point() { return aPoint; }
    Vector3D& Normal() { return aNormal; }
    Vector3D& PlaneNormal() { return aPlaneNormal; }
    Vector3D& TexCoor() { return aTexCoor; }
    B3dColor& Color() { return aColor; }
    UINT8& EdgeFlag() { return bEdgeFlag; }

    double GetX() { return aPoint.X(); }
    void SetX(double fNew) { aPoint.X() = fNew; }

    double GetY() { return aPoint.Y(); }
    void SetY(double fNew) { aPoint.Y() = fNew; }

    double GetZ() { return aPoint.Z(); }
    void SetZ(double fNew) { aPoint.Z() = fNew; }

    void Reset();

    void CalcInBetween(B3dEntity& rOld1,
        B3dEntity& rOld2, double t);
    void CalcMiddle(B3dEntity& rOld1,
        B3dEntity& rOld2);
};

/*************************************************************************
|*
|* Bucket fuer geometrische Daten
|*
\************************************************************************/

BASE3D_DECL_BUCKET(B3dEntity, Bucket)

}//end of namespace binfilter

#endif          // _B3D_B3DENTITY_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
