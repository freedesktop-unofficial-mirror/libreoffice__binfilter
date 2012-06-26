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

#ifndef _XOUTX_HXX
#define _XOUTX_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/bitmap.hxx>

#include <bf_svx/xhatch.hxx>
#include <bf_svx/xgrad.hxx>
#include <bf_svx/xpoly.hxx>
#include <bf_svx/rectenum.hxx>
#include <bf_svx/xenum.hxx>
#include <vcl/outdev.hxx>
#include <vcl/bitmap.hxx>

namespace binfilter {
class SfxItemSet;
class BfGraphicObject;

class FormattedText;
class XPolygon;
class XPolyPolygon;
class XLineAttrSetItem;
class XFillAttrSetItem;
class XTextAttrSetItem;
class XLineAttrSetItem;
class XFillAttrSetItem;
class XOutdevItemPool;
class XLineParam;
struct ImpData;

// #101498# predeclaration for DrawPortionInfo
class DrawPortionInfo;

#if _SOLAR__PRIVATE

// -----------
// - ImpData -
// -----------

struct ImpData
{
    XGradient*      pTransGradient;
    BOOL            bSolidHatch;
};

#define iRotTransGradient() ( ( (ImpData*)pImpData )->pTransGradient )
#define iSolidHatch()       ( ( (ImpData*)pImpData )->bSolidHatch )

#endif // _PRIVATE

/*************************************************************************
|*
|* Extended OutputDevice
|*
\************************************************************************/

class XOutputDevice
{
private:

    ImpData*            pImpData;

    long*               pLinePattern;
    USHORT              nLinePatternCnt;

    XLineStyle          eLineStyle;
    Color               aLineColor;
    USHORT              nLineTransparence;
    long                nLineWidth;
    XPolygon            aLineStartPoly, aLineEndPoly;
    long                nLineStartSqLen, nLineEndSqLen;
    BOOL                bLineStart, bLineEnd;
    BOOL                bHair;

    XFillStyle          eFillStyle;
    Color               aFillColor;
    USHORT              nFillTransparence;

    Bitmap              maFillBitmap;
    BfGraphicObject*      mpFillGraphicObject;
    void*               mpDummy1;
    void*               mpDummy2;
    void*               mpDummy3;
    void*               mpDummy4;
    void*               mpDummy5;
    long                mnDummy;
    long                mnDummy2;
    long                mnDummy3;
    long                mnDummy4;
    long                mnDummy5;
    MapMode             maLastMapMode;
    Size                maFillBitmapSize;
    Size                maBmpSize;
    Size                maBmpOutputSize;
    long                mnDummy6;
    long                mnDummy7;
    Point               maStartPoint;
    USHORT              mnBmpPerCentX;
    USHORT              mnBmpPerCentY;
    USHORT              mnBmpOffX;
    USHORT              mnBmpOffY;
    USHORT              mnBmpOffPosX;
    USHORT              mnBmpOffPosY;
    OutDevType          meLastOutDevType;
    RECT_POINT          meBmpRectPoint;
    BOOL                mbBmpTile;
    BOOL                mbBmpStretch;
    BOOL                mbBmpLogSize;
    BOOL                mbDummy;
    BOOL                mbRecalc;

    XGradient           aGradient;
    XHatch              aHatch;
    BOOL                bDither;

    BOOL                bIgnoreLineAttr;
    BOOL                bIgnoreLineStyle;
    BOOL                bIgnoreFillAttr;

    XFormTextStyle      eFormTextStyle;
    XFormTextAdjust     eFormTextAdjust;
    long                nFormTextDistance;
    long                nFormTextStart;
    BOOL                bFormTextMirror;
    BOOL                bFormTextOutline;
    XFormTextShadow     eFormTextShadow;
    Color               aFormTextShdwColor;
    USHORT              nFormTextShdwTransp;
    long                nFormTextShdwXVal;
    long                nFormTextShdwYVal;
    XFormTextStdForm    eFormTextStdForm;
    BOOL                bFormTextHideForm;

    // Zwischenspeicher fuer FormText-Auto-Fonthoehe bei mehreren
    // zusammengehoerigen Aufrufen
    long                nFtAutoHeightSave;
    // umschliessendes Rechteck der Formtext-Effekte
    Rectangle           aFormTextBoundRect;

    void                ImpDrawFillPolyPolygon( const PolyPolygon& rPoly, BOOL bRect );
    void                ImpDrawLinePolygon(const Polygon& rPoly, BOOL bClosePoly);

protected:

    OutputDevice*       pOut;
    Point               aOfs;

    void                DrawFillPolyPolygon( const PolyPolygon& rPoly, BOOL bRect = FALSE );
    void                DrawLinePolygon( const Polygon& rPoly, BOOL bClosePoly );

    // #101498# changed interface due to bidi requirements
    sal_Int32 ImpDrawFormText(DrawPortionInfo* pInfo, const Polygon& rPoly, sal_Int32 nAbsStart,
        sal_Bool bToLastPoint, sal_Bool bDraw, sal_Bool bIsShadow);
    void ImpDrawFormTextShadow(DrawPortionInfo* pInfo, const Polygon& rPoly, sal_Int32 nAbsStart,
        sal_Bool bToLastPoint, sal_Bool bDraw);

/*N*/   void                ImpDrawTiledBitmap( OutputDevice* pOut, const Rectangle& rRect,
/*N*/                                           const Point& rStartPoint, const Rectangle& rClipRect,
/*N*/                                             BOOL bPrinter );

 public:
                        XOutputDevice(OutputDevice* pOut);
                        ~XOutputDevice();

    OutputDevice*       GetOutDev() const { return pOut; }

    RasterOp            GetRasterOp() const { return pOut->GetRasterOp(); }
    void                SetRasterOp(RasterOp eRop) { pOut->SetRasterOp(eRop); }

    // Allgemeine Ausgabemethoden
    void                DrawLine( const Point& rStart, const Point& rEnd );
    void                DrawRect( const Rectangle& rRect, ULONG nXRound=0, ULONG nYRound=0 );
    void                DrawEllipse( const Rectangle& rRect );
    void                DrawArc( const Rectangle& rRect, const Point& rStart, const Point& rEnd );
    void                DrawPie( const Rectangle& rRect, const Point& rStart, const Point& rEnd );
    void                DrawXPolyLine( const XPolygon& rXPoly );
    void                DrawXPolygon( const XPolygon& rXPoly );
    void                DrawXPolyPolygon( const XPolyPolygon& rXPoly );

    // Bitmap Ausgabemethoden
    void                DrawBitmap( const Point& rPos, const Size& rSize, const Bitmap& rBmp );
    void                DrawBitmap( const Point& rDestPos, const Size& rDestSize,
                                    const Point& rSrcPos,  const Size& rSrcSize );

    // Text Ausgabemethoden
    // Der formatierte Text kommt aus der EditEngine von MT
    void                DrawFormattedText( const Point& rPos, const FormattedText& rText );

    // #101498# changed interface due to bidi requirements
    sal_Int32 DrawFormText(DrawPortionInfo* pInfo, const Polygon& rPoly,
        sal_Int32 nAbsStart = 0L, sal_Bool bToLastPoint = sal_True,
        sal_Bool bDraw = sal_True);

    const Rectangle&    GetFormTextBoundRect() const { return aFormTextBoundRect; }

    // Nur Temporaer
    const Color&        GetLineColor() const { return pOut->GetLineColor(); }
    void                SetLineColor( const Color& rColor ) { pOut->SetLineColor( rColor ); }

    const Color&        GetFillColor() const { return pOut->GetFillColor(); }
    void                SetFillColor( const Color& rColor ) { pOut->SetFillColor( rColor ); }

    // Attributeinstellungen
    void                SetLineAttr(const SfxItemSet& rAttr);
    void                SetFillAttr(const SfxItemSet& rAttr);
    void                SetTextAttr(const SfxItemSet& rAttr);

    // Attributeinstellungen ignorieren
    void                SetIgnoreLineAttr(BOOL bIgnore) { bIgnoreLineAttr = bIgnore; }
    BOOL                GetIgnoreLineAttr() { return bIgnoreLineAttr; }
    void                SetIgnoreLineStyle(BOOL bIgnore) { bIgnoreLineStyle = bIgnore; }
    BOOL                GetIgnoreLineStyle() { return bIgnoreLineStyle; }
    void                SetIgnoreFillAttr(BOOL bIgnore) { bIgnoreFillAttr = bIgnore; }
    BOOL                GetIgnoreFillAttr() { return bIgnoreFillAttr; }

    // StarView- Linecolor/style und Fillcolor/style temporaer ueberschreiben, z.B. fuer
    // dragging in SvDraw
    void                OverrideLineColor(const Color& rColor );
    void                OverrideFillColor(const Color& rColor );

    // Zum Abschalten der Linienenden
    BOOL                IsLineStart() const { return bLineStart; }
    void                OverrideLineStart(BOOL bOn) { bLineStart=bOn; }
    BOOL                IsLineEnd() const { return bLineEnd; }
    void                OverrideLineEnd(BOOL bOn) { bLineEnd=bOn; }

    // Allgemeine Einstellungen
    const Point&        GetOffset() const { return aOfs; }
    void                SetOffset( const Point& rOfs );

    // Initialisierung der Linienenden statisch, damit auch ohne XOutDev
    // von SvDraw verwendbar
    static long         InitLineStartEnd(XPolygon& rXPoly, long nWidth, BOOL bCenter);
};

// Nur aus Kompatibilitaetsgruenden fuer SvDraw
class ExtOutputDevice : public XOutputDevice
{
public:

        ExtOutputDevice(OutputDevice* pNewOut): XOutputDevice(pNewOut) {}
};

/*************************************************************************
|*
|* Funktionen zur Berechnung von Bezierkurven; muessen global sein,
|* da sie auch von XPolygon::GetBoundRect benoetigt werden
|*
\************************************************************************/

Rectangle       XOutCalcXPolyExtent(const XPolygon& rXPoly, OutputDevice* pOut);
long            XOutCalcBezierStepCount( const XPolygon& rXPoly, USHORT nIndex, OutputDevice* pOut, USHORT nRough = 0 );
void            XOutCalcBezier( const XPolygon& rXPoly, USHORT nBezIndex, Polygon& rPoly, USHORT nPolyIndex, long nSteps );
Polygon         XOutCreatePolygon( const XPolygon& rXPoly, OutputDevice* pOut, USHORT nRough = 0 );
Polygon         XOutCreatePolygonBezier( const XPolygon& rXPoly, OutputDevice* pOut );

}//end of namespace binfilter
#endif      // _XOUTX_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
