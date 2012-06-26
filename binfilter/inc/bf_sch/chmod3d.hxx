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


#ifndef SCH_CHARTMODEL_3D_OBJECTS
#define SCH_CHARTMODEL_3D_OBJECTS


//Ableitungen der 3D-Objekte, um #52277# zu beheben.
//Ueberladen der NbcSetAttributes um Attr abzufangen und in das ChartModel zu leiten

#include <bf_svx/extrud3d.hxx>
#include <bf_svx/polygn3d.hxx>
#include <bf_svx/deflt3d.hxx>
#include <bf_svx/svdorect.hxx>
#include <bf_svx/lathe3d.hxx>
#define CHART_SHAPE3D_IGNORE  -2 //intern! (GetChartShapeStyle()!)
#define CHART_SHAPE3D_ANY     -1 //undefinierter Typ (GetChartShapeStyle()!)
#define CHART_SHAPE3D_SQUARE   0
#define CHART_SHAPE3D_CYLINDER 1
#define CHART_SHAPE3D_CONE     2
#define CHART_SHAPE3D_PYRAMID  3 //reserved
#define CHART_SHAPE3D_HANOI    4
namespace binfilter {


class SchE3dLatheObj : public E3dLatheObj
{
public:
    SchE3dLatheObj(E3dDefaultAttributes& rDefault, const PolyPolygon& rPP)
        :E3dLatheObj(rDefault,rPP){};
    SchE3dLatheObj()
        :E3dLatheObj(){};

    using SdrAttrObj::operator=;

    virtual void SetItem(const SfxPoolItem& rItem);
    virtual void SetItemSet(const SfxItemSet& rSet);
};


class SchE3dExtrudeObj : public E3dExtrudeObj
{
public:

    SchE3dExtrudeObj(E3dDefaultAttributes& rDefault, const PolyPolygon& rPP, double fDepth)
        :E3dExtrudeObj(rDefault,rPP,fDepth){};
    SchE3dExtrudeObj(E3dDefaultAttributes& rDefault, const XPolyPolygon& rXPP, double fDepth)
        :E3dExtrudeObj(rDefault,rXPP,fDepth){};
    SchE3dExtrudeObj()
        :E3dExtrudeObj(){};

    using SdrAttrObj::operator=;

    virtual void SetItem(const SfxPoolItem& rItem);
    virtual void SetItemSet(const SfxItemSet& rSet);
};

class SchE3dPolygonObj : public E3dPolygonObj
{
public:
    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        BOOL bLinOnly=FALSE)
        :E3dPolygonObj(rDefault,rPoly3D,bLinOnly){};

    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D, BOOL bLinOnly=FALSE)
        :E3dPolygonObj(rDefault,rPoly3D,rVector3D,bLinOnly){};

    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const Vector3D& rP1,
        const Vector3D& rP2, BOOL bLinOnly=TRUE)
        : E3dPolygonObj(rDefault,rP1,rP2,bLinOnly){};

    SchE3dPolygonObj() : E3dPolygonObj(){};

    using SdrAttrObj::operator=;

    virtual void SetItem(const SfxPoolItem& rItem);
    virtual void SetItemSet(const SfxItemSet& rSet);
};


class SchE3dObject : public E3dObject
{

 public:
     SchE3dObject()
         :E3dObject(){};

    using SdrAttrObj::operator=;

    virtual void SetItemSet(const SfxItemSet& rSet);
};
class SchRectObj : public SdrRectObj
{
public:
    SchRectObj(SdrObjKind eNewTextKind, const Rectangle& rRect)
        :SdrRectObj(eNewTextKind,rRect){};
    SchRectObj(const Rectangle& rRect): SdrRectObj(rRect){};

    using SdrRectObj::operator=;

    virtual void NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject);
    virtual void SetItemSet(const SfxItemSet& rSet);
};

} //namespace binfilter
#endif




/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
