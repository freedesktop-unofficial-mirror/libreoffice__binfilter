/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdvmark.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:36:31 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _SVDVMARK_HXX
#define _SVDVMARK_HXX

#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif

namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class XPolygon;
class XPolyPolygon;
class SdrObject;
class SdrPageView;
class SdrPaintView;

//************************************************************
//   Defines
//************************************************************

enum SdrViewUserMarkerAlign
{
    SDRMARKER_ALIGNCENTER,
    SDRMARKER_ALIGNINNER,
    SDRMARKER_ALIGNOUTER
};

//************************************************************
//   SdrViewUserMarker
//************************************************************

class SdrViewUserMarker
{
    friend class                SdrPaintView;

    SdrPaintView*               pView;
    OutputDevice*               pForcedOutDev;
    Point*                      pPoint;
    Rectangle*                  pRect;
    Polygon*                    pPoly;
    PolyPolygon*                pPolyPoly;
    XPolygon*                   pXPoly;
    XPolyPolygon*               pXPolyPoly;

    SdrViewUserMarkerAlign      eAlign;
    USHORT                      nPixelDistance;      // Abstand des Rahmen zum eigentlichen pRect
    USHORT                      nLineWdt;            // Strichstaerke
    USHORT                      nCrossSize;          // fuer CrossHair und Stripes. 0=FullWindow
    FASTBOOL                    bLineWdtLog;
    FASTBOOL                    bCrossSizeLog;
    FASTBOOL                    bSolidArea;
    FASTBOOL                    bDashed;
    FASTBOOL                    bCrossHair;          // Bei pPoint: Fadenkreuz. Sonst Dot (Rect oder Circle)
    FASTBOOL                    bStripes;            // Bei pRect
    FASTBOOL                    bEllipse;            // Bei pRect oder pPoint
    FASTBOOL                    bPolyLine;           // Bei pPoly oder pXPoly
    FASTBOOL                    bAnimate;
    FASTBOOL                    bVisible;

    USHORT                      nAnimateDelay;
    USHORT                      nAnimateSpeed;
    USHORT                      nAnimateAnz;
    FASTBOOL                    bAnimateBwd;
    FASTBOOL                    bAnimateToggle;
    USHORT                      nAnimateDelayCountDown;
    USHORT                      nAnimateSpeedCountDown;
    USHORT                      nAnimateNum;

    FASTBOOL                    bHasPointer;
    FASTBOOL                    bMouseMovable;

protected:
    void ImpDelGeometrics();

public:
    SdrViewUserMarker(SdrPaintView* pView);

    // Jede Ableitung, die ImpDraw ueberladen hat muss
    // im Dtor IsVisible() fragen und ggf. Hiden!
    virtual ~SdrViewUserMarker();

    // Falls der Marker nur in einem bestimmten Window der View
    // dargestellt werden soll. Default ist NULL= alle Windows der View.
    void SetOutputDevice(OutputDevice* pOut) { pForcedOutDev=pOut; }
    OutputDevice* GetOutputDevice() const { return pForcedOutDev; }

    // Der Marker kann durchaus auch in einen andere View gesteckt werden.
    // (Beim Destruieren der View wird die View am Marker automatisch auf NULL gesetzt.)

    void SetLineWidth(USHORT nWdt);

    void SetAnimateDelay(USHORT nTime) { nAnimateDelay=(nTime+25)/50; }
    void SetAnimateSpeed(USHORT nTime) { nAnimateSpeed=(nTime+25)/50; if (nAnimateSpeed>0) nAnimateSpeed--; }
    void SetAnimateCount(USHORT nAnz) { nAnimateAnz=nAnz; }
    void SetAnimateBackward(FASTBOOL bOn) { bAnimateBwd=bOn; }
    void SetAnimateToggle(FASTBOOL bOn) { bAnimateToggle=bOn; }

    const Point* GetPoint() const { return pPoint; }
    const Rectangle* GetRectangle() const { return pRect; }
    const Polygon* GetPolygon() const { return pPoly; }
    const PolyPolygon* GetPolyPolygon() const { return pPolyPoly; }
    const XPolygon* GetXPolygon() const { return pXPoly; }
    const XPolyPolygon* GetXPolyPolygon() const { return pXPolyPoly; }

    FASTBOOL IsDot() const { return pPoint!=NULL && !bCrossHair; }
    FASTBOOL IsCrossHair() const { return pPoint!=NULL && bCrossHair; }
    FASTBOOL IsRectangle() const { return pRect!=NULL && !bEllipse && !bStripes; }
    FASTBOOL IsStripes() const { return pRect!=NULL && bStripes; }
    FASTBOOL IsEllipse() const { return pRect!=NULL && bEllipse; }
    FASTBOOL IsPolyLine() const { return (pPoly!=NULL || pPolyPoly!=NULL || pXPoly!=NULL || pXPolyPoly!=NULL) && bPolyLine; }

    FASTBOOL IsSolidArea() const { return bSolidArea && pPoint==NULL && !bPolyLine; }
    FASTBOOL IsDashed() const { return bDashed; }
    USHORT GetPixelDistance() const { return nPixelDistance; }
    USHORT GetLineWidth() const { return nLineWdt; }
    FASTBOOL IsLineWidthIsLogic() const { return bLineWdtLog; }
    USHORT GetCrossHairSize() const { return nCrossSize; }
    FASTBOOL IsCrossHairSizeIsLogic() const { return bCrossSizeLog; }

    FASTBOOL IsAnimate() const { return bAnimate; }
    USHORT GetAnimateDelay() const { return nAnimateDelay*50; }
    USHORT GetAnimateSpeed() const { return (nAnimateSpeed+1)*50; }
    USHORT GetAnimateCount() const { return nAnimateAnz; }
    FASTBOOL IsAnimateBackward() const { return bAnimateBwd; }
    FASTBOOL IsAnimateToggle() const { return bAnimateToggle; }

    void Show();
    void Hide();
    FASTBOOL IsVisible() const { return bVisible; }

    FASTBOOL HasPointer() const { return bHasPointer; }
    FASTBOOL IsMouseMovable() const { return bMouseMovable; }
};

}//end of namespace binfilter
#endif //_SVDVMARK_HXX

