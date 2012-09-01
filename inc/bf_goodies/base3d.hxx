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

#ifndef _B3D_BASE3D_HXX
#define _B3D_BASE3D_HXX

#include <bf_svtools/bf_solar.h>


#include "hmatrix.hxx"

#ifndef _INC_FLOAT
#include <float.h>
#endif

#include <vcl/timer.hxx>
#include <osl/mutex.hxx>

namespace binfilter {

enum Base3DObjectMode
{

    // die folgenden Primitive muessen von jedem abgeleiteten Renderer
    // ausgefuehrt werden koennen

    Base3DPoints = 0,
    Base3DLines,
    Base3DLineLoop,
    Base3DLineStrip,
    Base3DTriangles,
    Base3DTriangleStrip,
    Base3DTriangleFan,
    Base3DQuads,
    Base3DQuadStrip,
    Base3DPolygon,

    // ab hier beginnen hoehere Primitive, die mit speziellen Methoden
    // innerhalb von Base3D auf die obenstehenden Primitive
    // abgebildet werden. Diese Methoden tun dies alles im object
    // coordinate system.

    // PolyPolygon ohne Selbstueberschneidungen und ohne
    // Ueberschneidungen der evtl. vorhandenen Teilpolygone
    Base3DComplexPolygon,

    // Beliebiges PolyPolygon mit Selbstueberschneidungen und
    // Ueberschneidungen der weiteren Teilpolygone
    Base3DComplexPolygonCut
};

/*************************************************************************
|*
|* Moegliche Darstellungsarten fuer Primitive
|*
\************************************************************************/

enum Base3DRenderMode
{
    Base3DRenderNone = 0,
    Base3DRenderPoint,
    Base3DRenderLine,
    Base3DRenderFill
};

/*************************************************************************
|*
|* Moegliche CullingModes fuer Polygone
|*
\************************************************************************/

enum Base3DCullMode
{
    Base3DCullNone = 0,
    Base3DCullFront,
    Base3DCullBack
};

/*************************************************************************
|*
|* Moegliche ShadeModels fuer Polygone
|*
\************************************************************************/

enum Base3DShadeModel
{
    Base3DSmooth = 0,
    Base3DFlat,
    Base3DPhong
};

/*************************************************************************
|*
|* Unterstuetzung PolygonOffset
|*
\************************************************************************/

enum Base3DPolygonOffset
{
    Base3DPolygonOffsetFill = 1,
    Base3DPolygonOffsetLine,
    Base3DPolygonOffsetPoint
};

/*************************************************************************
|*
|* Genauigkeit der Berechnungen; im Zweifelsfall wird dieser
|* Wert benutzt, um mit 0.0 zu vergleichen oder Abstaende von
|* Randvereichen von Wertebereichen zu testen
|*
\************************************************************************/

#define SMALL_DVALUE                    (0.0000001)

}//end of namespace binfilter

#endif          // _B3D_BASE3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
