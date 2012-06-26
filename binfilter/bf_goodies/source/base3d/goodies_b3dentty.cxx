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

#include "b3dentty.hxx"

#include "b3dtrans.hxx"

#include <tools/debug.hxx>

namespace binfilter {
/*************************************************************************
|*
|* Flags auf Ausgangsposition
|*
\************************************************************************/

void B3dEntity::Reset()
{
    bValid = bNormalUsed = bTexCoorUsed = bDeviceCoor = FALSE;
    bEdgeFlag = TRUE;
}

/*************************************************************************
|*
|* Neuen Punkt an der stelle t des parametrisierten Vektors rOld1, rOld2
|* berechnen und fuellen
|*
\************************************************************************/

void B3dEntity::CalcInBetween(B3dEntity& rOld1, B3dEntity& rOld2, double t)
{
    // DeviceCoor der ersten Quelle benutzen, die Basis sollte
    // vorher abgeglichen sein
    SetDeviceCoor(rOld1.IsDeviceCoor());

    // Punktkoordinaten berechnen
    aPoint.CalcInBetween(rOld1.Point(), rOld2.Point(), t);
    SetValid();

    // PlaneNormal Koordinaten berechnen
    rOld1.PlaneNormal().Normalize();
    rOld2.PlaneNormal().Normalize();
    aPlaneNormal.CalcInBetween(rOld1.PlaneNormal(), rOld2.PlaneNormal(), t);
    aPlaneNormal.Normalize();

    // Vektor berechnen
    if(rOld1.IsNormalUsed() && rOld2.IsNormalUsed())
    {
        rOld1.Normal().Normalize();
        rOld2.Normal().Normalize();
        aNormal.CalcInBetween(rOld1.Normal(), rOld2.Normal(), t);
        aNormal.Normalize();
        SetNormalUsed();
    }

    // Texturkoordinaten berechnen
    if(rOld1.IsTexCoorUsed() && rOld2.IsTexCoorUsed())
    {
        aTexCoor.CalcInBetween(rOld1.TexCoor(), rOld2.TexCoor(), t);
        SetTexCoorUsed();
    }

    // EdgeVisible berechnen
    SetEdgeVisible(rOld1.IsEdgeVisible());

    // Farbe berechnen
    aColor.CalcInBetween(rOld1.Color(), rOld2.Color(), t);
}

/*************************************************************************
|*
|* Neuen Punkt in der Mitte des parametrisierten Vektors rOld1, rOld2
|* berechnen und fuellen
|*
\************************************************************************/

void B3dEntity::CalcMiddle(B3dEntity& rOld1, B3dEntity& rOld2)
{
    // DeviceCoor der ersten Quelle benutzen, die Basis sollte
    // vorher abgeglichen sein
    SetDeviceCoor(rOld1.IsDeviceCoor());

    // Punktkoordinaten berechnen
    aPoint.CalcMiddle(rOld1.Point(), rOld2.Point());
    SetValid();

    // PlaneNormal Koordinaten berechnen
    rOld1.PlaneNormal().Normalize();
    rOld2.PlaneNormal().Normalize();
    aPlaneNormal.CalcMiddle(rOld1.PlaneNormal(), rOld2.PlaneNormal());
    aPlaneNormal.Normalize();

    // Vektor berechnen
    if(rOld1.IsNormalUsed() && rOld2.IsNormalUsed())
    {
        rOld1.Normal().Normalize();
        rOld2.Normal().Normalize();
        aNormal.CalcMiddle(rOld1.Normal(), rOld2.Normal());
        aNormal.Normalize();
        SetNormalUsed();
    }

    // Texturkoordinaten berechnen
    if(rOld1.IsTexCoorUsed() && rOld2.IsTexCoorUsed())
    {
        aTexCoor.CalcMiddle(rOld1.TexCoor(), rOld2.TexCoor());
        SetTexCoorUsed();
    }

    // EdgeVisible berechnen
    SetEdgeVisible(rOld1.IsEdgeVisible());

    // Farbe berechnen
    aColor.CalcMiddle(rOld1.Color(), rOld2.Color());
}

/*************************************************************************
|*
|* Bucket fuer geometrische Daten
|*
\************************************************************************/

BASE3D_IMPL_BUCKET(B3dEntity, Bucket)

}//end of namespace binfilter

// eof

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
