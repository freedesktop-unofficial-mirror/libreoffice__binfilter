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

#ifndef _SVDOPATH_HXX
#define _SVDOPATH_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdotext.hxx>

namespace binfilter {

//************************************************************
//   Defines
//************************************************************

enum SdrPathType {SDRPATH_NONE,SDRPATH_LINE,SDRPATH_CURVE};

//************************************************************
//   Hilfsklasse SdrPathObjGeoData
//
// fuer Undo/Redo
//
//************************************************************

class SdrPathObjGeoData : public SdrTextObjGeoData
{
    friend class                SdrPolyEditView;

public:
    XPolyPolygon                aPathPolygon;
    SdrObjKind                  eKind;

    SdrPathObjGeoData();
    virtual ~SdrPathObjGeoData();
};

//************************************************************
//   SdrPathObj
//************************************************************

class SdrPathObj : public SdrTextObj
{
    friend class                ImpSdrPathDragData;
    friend class                SdrPolyEditView;

protected:
    XPolyPolygon                aPathPolygon;
    SdrObjKind                  eKind;

    // Hilfsvariable fuer Create
    USHORT                      bCreating; // nActPoly;

protected:
    // Hilfsfunktion fuer GET/SET/INS/etc. PNT
    bool FindPolyPnt(USHORT nAbsPnt, USHORT& rPolyNum, USHORT& rPointNum, bool bAllPoints=TRUE) const;
    void ImpForceKind();
    void ImpForceLineWink();

    // fuer friend class SdrPolyEditView auf einigen Compilern:
    void SetRectsDirty(bool bNotMyself=FALSE) { SdrTextObj::SetRectsDirty(bNotMyself); }

public:
    TYPEINFO();
    SdrPathObj(SdrObjKind eNewKind);
    SdrPathObj(SdrObjKind eNewKind, const XPolyPolygon& rPathPoly);
    SdrPathObj(const Point& rPt1, const Point& rPt2);
    virtual ~SdrPathObj();

    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
    virtual bool Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
    virtual void operator=(const SdrObject& rObj);

    virtual void TakeXorPoly(XPolyPolygon& rXPolyPoly, bool bDetail) const;
    virtual void RecalcSnapRect();
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void TakeContour(XPolyPolygon& rPoly) const;
    using SdrObject::TakeContour;

    virtual void NbcMove(const Size& aSize);
    virtual void NbcResize(const Point& rRefPnt, const Fraction& aXFact, const Fraction& aYFact);
    virtual void NbcRotate(const Point& rRefPnt, long nAngle, double fSin, double fCos);
    virtual void NbcShear(const Point& rRefPnt, double fTan, bool bVShear);


    virtual bool IsPolyObj() const { return true; } // DBG_BF_ASSERT
    virtual USHORT GetPointCount() const;
    virtual const Point& GetPoint(USHORT nHdlNum) const;
    virtual void NbcSetPoint(const Point& rPnt, USHORT nHdlNum);

protected:
    virtual SdrObjGeoData* NewGeoData() const;
    virtual void SaveGeoData(SdrObjGeoData& rGeo) const;

public:

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // Bezierpolygon holen/setzen
    const XPolyPolygon& GetPathPoly() const { return aPathPolygon; }
    void SetPathPoly(const XPolyPolygon& rPathPoly);
    void NbcSetPathPoly(const XPolyPolygon& rPathPoly);

    // Spezialfunktionen fuer Bezierpolygon-Bearbeitung
    static bool IsClosed(SdrObjKind eKind) { return eKind==OBJ_POLY || eKind==OBJ_PATHPOLY || eKind==OBJ_PATHFILL || eKind==OBJ_FREEFILL || eKind==OBJ_SPLNFILL; }
    static bool IsLine(SdrObjKind eKind) { return eKind==OBJ_PLIN || eKind==OBJ_PATHPLIN || eKind==OBJ_PATHLINE || eKind==OBJ_FREELINE || eKind==OBJ_SPLNLINE || eKind==OBJ_LINE; }
    bool IsClosed() const { return eKind==OBJ_POLY || eKind==OBJ_PATHPOLY || eKind==OBJ_PATHFILL || eKind==OBJ_FREEFILL || eKind==OBJ_SPLNFILL; }
    bool IsLine() const { return eKind==OBJ_PLIN || eKind==OBJ_PATHPLIN || eKind==OBJ_PATHLINE || eKind==OBJ_FREELINE || eKind==OBJ_SPLNLINE || eKind==OBJ_LINE; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // transformation interface for StarOfficeAPI. This implements support for
    // homogen 3x3 matrices containing the transformation of the SdrObject. At the
    // moment it contains a shearX, rotation and translation, but for setting all linear
    // transforms like Scale, ShearX, ShearY, Rotate and Translate are supported.
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // gets base transformation and rectangle of object. If it's an SdrPathObj it fills the PolyPolygon
    // with the base geometry and returns TRUE. Otherwise it returns FALSE.
    virtual BOOL TRGetBaseGeometry(Matrix3D& rMat, XPolyPolygon& rPolyPolygon) const;
    // sets the base geometry of the object using infos contained in the homogen 3x3 matrix.
    // If it's an SdrPathObj it will use the provided geometry information. The Polygon has
    // to use (0,0) as upper left and will be scaled to the given size in the matrix.
    virtual void TRSetBaseGeometry(const Matrix3D& rMat, const XPolyPolygon& rPolyPolygon);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOPATH_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
