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

#ifndef _SVDORECT_HXX
#define _SVDORECT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdotext.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class XPolygon;

//************************************************************
//   Hilfsklasse SdrRectObjGeoData
//************************************************************

class SdrRectObjGeoData : public SdrTextObjGeoData
{
public:
    long                        nEckRad; // Eckenradius -> Undo soll dann auch mal ueber Items ...
};

//************************************************************
//   SdrRectObj
//
// Rechteck-Objekte (Rechteck,Kreis,...)
//
//************************************************************

class SdrRectObj : public SdrTextObj
{
    friend class                SdrTextObj; // wg SetXPolyDirty bei GrowAdjust

protected:
    XPolygon*                   pXPoly;
    bool                    bXPolyIsLine;  // TRUE: pXPoly muss als PolyLine angesehen werden.

protected:
    // Liefert TRUE, wenn das Painten ein XPolygon erfordert.
    bool PaintNeedsXPoly(long nEckRad) const;

protected:
    XPolygon ImpCalcXPoly(const Rectangle& rRect1, long nRad1, bool bContour=FALSE) const;
    SdrObject* ImpCheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer, bool bForceFilled, bool bForceTol=FALSE) const;

    //void PaintIt(ExtOutputDevice& rOut, _BOOL bDown) const;
    void SetXPolyDirty();

    // RecalcXPoly sollte ueberladen werden. Dabei muss dann eine XPolygon
    // Instanz generiert (new) und an pXPoly zugewiesen werden.
    virtual void RecalcXPoly();
    const XPolygon& GetXPoly() const;
    virtual SdrObjGeoData* NewGeoData() const;
    virtual void           SaveGeoData(SdrObjGeoData& rGeo) const;
    virtual void           RestGeoData(const SdrObjGeoData& rGeo);

public:
    TYPEINFO();
    // Der Eckenradius-Parameter fliegt irgendwann raus. Der Eckenradius
    // ist dann (spaeter) ueber SfxItems einzustellen (SetAttributes()).
    // Konstruktion eines Rechteck-Zeichenobjekts

    SdrRectObj();
    SdrRectObj(const Rectangle& rRect);

    // Konstruktion eines Textrahmens
    SdrRectObj(SdrObjKind eNewTextKind);
    SdrRectObj(SdrObjKind eNewTextKind, const Rectangle& rRect);
    virtual ~SdrRectObj();

    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
    virtual bool Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;


    virtual void operator=(const SdrObject& rObj);
    virtual void RecalcSnapRect();
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void TakeXorPoly(XPolyPolygon& rPoly, bool bDetail) const;
    using SdrObject::TakeContour;
    virtual void TakeContour(XPolyPolygon& rPoly) const;



    virtual Pointer GetCreatePointer() const;

    virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);
    virtual void NbcShear(const Point& rRef, double tn, bool bVShear);


    virtual SdrGluePoint GetVertexGluePoint(USHORT nNum) const;


    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);
};

}//end of namespace binfilter
#endif //_SVDORECT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
