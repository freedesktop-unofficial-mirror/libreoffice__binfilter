/*************************************************************************
 *
 *  $RCSfile: svdvmark.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:48 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _SVDVMARK_HXX
#define _SVDVMARK_HXX

#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif

#ifndef _VCL_POINTR_HXX
#include <vcl/pointr.hxx>
#endif

//************************************************************
//   Vorausdeklarationen
//************************************************************

class XPolygon;
class XPolyPolygon;
class SdrObject;
class SdrPageView;

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
//STRIP001  void ImpDraw(FASTBOOL bHiding, FASTBOOL bNoSaveDC);
//STRIP001  virtual void Draw(OutputDevice* pOut, FASTBOOL bHiding, FASTBOOL bNoSaveDC);

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
//STRIP001  void SetView(SdrPaintView* pView_);
//STRIP001  SdrPaintView* GetView() const { return pView; }

    void SetPoint(const Point& rPoint); // fuer CROSS
//STRIP001  void SetRectangle(const Rectangle& rRect); // fuer RECT, ELLIPSE und STRIPES
//STRIP001  void SetRectangle(const SdrObject* pObj, const SdrPageView* pPV=NULL);
//STRIP001  void SetPolygon(const Polygon& rPoly);
//STRIP001  void SetPolyPolygon(const PolyPolygon& rPolyPoly);
//STRIP001  void SetXPolygon(const XPolygon& rXPoly);
//STRIP001  void SetXPolyPolygon(const XPolyPolygon& rXPolyPoly);
//STRIP001  void SetXPolyPolygon(const SdrObject* pObj, const SdrPageView* pPV=NULL);

//STRIP001  void SetCrossHair(FASTBOOL bOn);
//STRIP001  void SetStripes(FASTBOOL bOn);
//STRIP001  void SetEllipse(FASTBOOL bOn);
//STRIP001  void SetPolyLine(FASTBOOL bOn);
//STRIP001  void SetSolidArea(FASTBOOL bOn);
//STRIP001  void SetDashed(FASTBOOL bOn);
//STRIP001  void SetPixelDistance(USHORT nDistance);
    void SetLineWidth(USHORT nWdt);
//STRIP001  void SetLineWidthIsLogic(FASTBOOL bOn);
//STRIP001  void SetCrossHairSize(USHORT nSize);
//STRIP001  void SetCrossSizeIsLogic(FASTBOOL bOn);

//STRIP001  void SetAnimate(FASTBOOL bOn); // Animate noch nicht vollstaendig unterstuetzt
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

//STRIP001  virtual void Move(long nXMove, long nYMove);
    void Show();
    void Hide();
    FASTBOOL IsVisible() const { return bVisible; }
//STRIP001  virtual void DoAnimateOneStep();
//STRIP001  FASTBOOL IncAnimateCounters();

//STRIP001  virtual FASTBOOL IsHit(const Point& rPnt, short nTol=-2) const;
    FASTBOOL HasPointer() const { return bHasPointer; }
//STRIP001  virtual Pointer  GetPointer() const;
    FASTBOOL IsMouseMovable() const { return bMouseMovable; }
};

#endif //_SVDVMARK_HXX

