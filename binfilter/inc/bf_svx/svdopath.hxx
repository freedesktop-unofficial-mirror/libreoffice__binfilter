/*************************************************************************
 *
 *  $RCSfile: svdopath.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:54 $
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

#ifndef _SVDOPATH_HXX
#define _SVDOPATH_HXX

#ifndef _SVDOTEXT_HXX
#include <bf_svx/svdotext.hxx>
#endif

#ifndef _XPOLY_HXX
#include <bf_svx/xpoly.hxx>
#endif
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class XPolyPolygon;

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
    FASTBOOL FindPolyPnt(USHORT nAbsPnt, USHORT& rPolyNum, USHORT& rPointNum, FASTBOOL bAllPoints=TRUE) const;
//STRIP001  void ImpSetClosed(FASTBOOL bClose);
    void ImpForceKind();
    void ImpForceLineWink();
//STRIP001  void ImpConvertSegment(USHORT nPolyNum, USHORT nPointNum, SdrPathType ePathType, FASTBOOL bIgnoreSmooth);
//STRIP001  void ImpSetSmoothFlag(USHORT nPolyNum, USHORT nPointNum, XPolyFlags eFlag);

    // fuer friend class SdrPolyEditView auf einigen Compilern:
    void SetRectsDirty(FASTBOOL bNotMyself=FALSE) { SdrTextObj::SetRectsDirty(bNotMyself); }

public:
    TYPEINFO();
    SdrPathObj(SdrObjKind eNewKind);
    SdrPathObj(SdrObjKind eNewKind, const XPolyPolygon& rPathPoly);
    SdrPathObj(const Point& rPt1, const Point& rPt2);
    virtual ~SdrPathObj();

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
    virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
    virtual void operator=(const SdrObject& rObj);

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;
    virtual void TakeXorPoly(XPolyPolygon& rXPolyPoly, FASTBOOL bDetail) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;
    virtual void RecalcSnapRect();
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void TakeContour(XPolyPolygon& rPoly) const;
//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
//STRIP001  virtual USHORT GetPlusHdlCount(const SdrHdl& rHdl) const;
//STRIP001  virtual SdrHdl* GetPlusHdl(const SdrHdl& rHdl, USHORT nPlNum) const;
//STRIP001  virtual void AddToHdlList(SdrHdlList& rHdlList) const;

//STRIP001  virtual FASTBOOL HasSpecialDrag() const;
//STRIP001  virtual FASTBOOL BegDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL MovDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL EndDrag(SdrDragStat& rDrag);
//STRIP001  virtual void BrkDrag(SdrDragStat& rDrag) const;

//STRIP001  virtual String GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const;

//STRIP001  virtual void TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;

//STRIP001  virtual FASTBOOL BegCreate(SdrDragStat& rStat);
//STRIP001  virtual FASTBOOL MovCreate(SdrDragStat& rStat);
//STRIP001  virtual FASTBOOL EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd);
//STRIP001  virtual FASTBOOL BckCreate(SdrDragStat& rStat);
//STRIP001  virtual void BrkCreate(SdrDragStat& rStat);
//STRIP001  virtual void TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;
//STRIP001  Pointer GetCreatePointer() const;

    virtual void NbcMove(const Size& aSize);
    virtual void NbcResize(const Point& rRefPnt, const Fraction& aXFact, const Fraction& aYFact);
    virtual void NbcRotate(const Point& rRefPnt, long nAngle, double fSin, double fCos);
//STRIP001  virtual void NbcMirror(const Point& rRefPnt1, const Point& rRefPnt2);
    virtual void NbcShear(const Point& rRefPnt, long nAngle, double fTan, FASTBOOL bVShear);

//STRIP001  virtual USHORT GetSnapPointCount() const;
//STRIP001  virtual Point GetSnapPoint(USHORT i) const;

    virtual FASTBOOL IsPolyObj() const;
    virtual USHORT GetPointCount() const;
    virtual const Point& GetPoint(USHORT nHdlNum) const;
    virtual void NbcSetPoint(const Point& rPnt, USHORT nHdlNum);

    // Punkt einfuegen
//STRIP001  virtual USHORT NbcInsPoint(const Point& rPos, FASTBOOL bNewObj, FASTBOOL bHideHim, FASTBOOL& rInsNextAfter);
//STRIP001  virtual USHORT NbcInsPoint(USHORT i, const Point& rPos, FASTBOOL bInsAfter, FASTBOOL bNewObj, FASTBOOL bHideHim);

    // Punkt loeschen
//STRIP001  virtual FASTBOOL NbcDelPoint(USHORT nHdlNum);

    // An diesem Punkt auftrennen
//STRIP001  virtual SdrObject* NbcRipPoint(USHORT nHdlNum, USHORT& rNewPt0Index);

    // Objekt schliessen
//STRIP001  virtual void NbcShut();

protected:
    virtual SdrObjGeoData* NewGeoData() const;
    virtual void SaveGeoData(SdrObjGeoData& rGeo) const;
//STRIP001  virtual void RestGeoData(const SdrObjGeoData& rGeo);

public:
//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // Bezierpolygon holen/setzen
    const XPolyPolygon& GetPathPoly() const { return aPathPolygon; }
    void SetPathPoly(const XPolyPolygon& rPathPoly);
    void NbcSetPathPoly(const XPolyPolygon& rPathPoly);

    // Man stecke die Handlenummer rein und bekomme die Polygon- und Punktnummer
    // des zugehoerigen Punkts im XPolyPolygon.
    FASTBOOL TakePolyIdxForHdlNum(USHORT nHdlNum, USHORT& rPolyNum, USHORT& rPointNum) const { return FindPolyPnt(nHdlNum,rPolyNum,rPointNum,FALSE); }

    // Spezialfunktionen fuer Bezierpolygon-Bearbeitung
    static FASTBOOL IsClosed(SdrObjKind eKind) { return eKind==OBJ_POLY || eKind==OBJ_PATHPOLY || eKind==OBJ_PATHFILL || eKind==OBJ_FREEFILL || eKind==OBJ_SPLNFILL; }
    static FASTBOOL IsLine(SdrObjKind eKind) { return eKind==OBJ_PLIN || eKind==OBJ_PATHPLIN || eKind==OBJ_PATHLINE || eKind==OBJ_FREELINE || eKind==OBJ_SPLNLINE || eKind==OBJ_LINE; }
    static FASTBOOL IsFreeHand(SdrObjKind eKind) { return eKind==OBJ_FREELINE || eKind==OBJ_FREEFILL; }
    static FASTBOOL IsBezier(SdrObjKind eKind) { return eKind==OBJ_PATHLINE || eKind==OBJ_PATHFILL; }
    static FASTBOOL IsSpline(SdrObjKind eKind) { return eKind==OBJ_SPLNLINE || eKind==OBJ_SPLNFILL; }
    FASTBOOL IsClosed() const { return eKind==OBJ_POLY || eKind==OBJ_PATHPOLY || eKind==OBJ_PATHFILL || eKind==OBJ_FREEFILL || eKind==OBJ_SPLNFILL; }
    FASTBOOL IsLine() const { return eKind==OBJ_PLIN || eKind==OBJ_PATHPLIN || eKind==OBJ_PATHLINE || eKind==OBJ_FREELINE || eKind==OBJ_SPLNLINE || eKind==OBJ_LINE; }
    FASTBOOL IsFreeHand() const { return eKind==OBJ_FREELINE || eKind==OBJ_FREEFILL; }
    FASTBOOL IsBezier() const { return eKind==OBJ_PATHLINE || eKind==OBJ_PATHFILL; }
    FASTBOOL IsSpline() const { return eKind==OBJ_SPLNLINE || eKind==OBJ_SPLNFILL; }

    // Pfad schliessen bzw. oeffnen; im letzteren Fall den Endpunkt um
    // "nOpenDistance" verschieben
//STRIP001  void ToggleClosed(long nOpenDistance);

    // Pfadabschnitt in Kurve bzw. Linie umwandeln. Toggle!
//STRIP001  void ConvertSegment(const SdrHdl* pHdl);

    // Flag fuer Uebergang zwischen zwei Pfadsegmenten setzen
//STRIP001  void SetSmoothFlag(const SdrHdl* pHdl, XPolyFlags eFlag);
//STRIP001  void NbcSetSmoothFlag(const SdrHdl* pHdl, XPolyFlags eFlag);
//STRIP001  XPolyFlags GetSmoothFlag(const SdrHdl* pHdl) const;

    // Welche Umwandlung eines Pfadabschnitts ist moeglich?
//STRIP001  SdrPathType CanConvertSegment(const SdrHdl* pHdl) const;

    // Feststellen von welcher Art das Segment ist
//STRIP001  SdrPathType GetSegmentType(const SdrHdl* pHdl) const;

    // eType=SDRPATH_NONE bedeutet Toggle
//STRIP001  void ConvertSegment(const SdrHdl* pHdl, SdrPathType eType, FASTBOOL bIgnoreSmooth=FALSE);
//STRIP001  void NbcConvertSegment(const SdrHdl* pHdl, SdrPathType eType, FASTBOOL bIgnoreSmooth=FALSE);

    // Alle Segmente konvertieren, eType=SDRPATH_NONE bedeutet Toggle
//STRIP001  void ConvertAllSegments(SdrPathType ePathType);

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

