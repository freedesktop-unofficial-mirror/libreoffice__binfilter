/*************************************************************************
 *
 *  $RCSfile: poly3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:27 $
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

#ifndef _POLY3D_HXX
#define _POLY3D_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _VOLUME3D_HXX
#include <bf_svx/volume3d.hxx>
#endif

#ifndef _B3D_BASE3D_HXX
#include <goodies/base3d.hxx>
#endif
class SvStream;
class Vector3D;
class Matrix4D;
class Polygon;
class PolyPolygon;
namespace binfilter {


class XPolygon;
class XPolyPolygon;

#define POLY3D_APPEND       0xFFFF
#define POLYPOLY3D_APPEND   0xFFFF

#define POLY3D_MAXPOINTS    0x7FFF

/*************************************************************************
|*
|* 3D-Polygon-Implementierung
|*
\************************************************************************/

#if _SOLAR__PRIVATE
class ImpPolygon3D
{
public:
    Vector3D*                   pPointAry;
    Vector3D*                   pOldPointAry;

    UINT16                      nSize;
    UINT16                      nResize;
    UINT16                      nPoints;
    UINT16                      nRefCount;

    unsigned                    bDeleteOldAry : 1;
    unsigned                    bClosed : 1;

    ImpPolygon3D(UINT16 nInitSize = 4, UINT16 nPolyResize = 4);
    ImpPolygon3D(const ImpPolygon3D& rImpPoly3D);
    ~ImpPolygon3D();

    void CheckPointDelete();
    void Resize(UINT16 nNewSize, BOOL bDeletePoints = TRUE);
//STRIP001  void InsertSpace(UINT16 nPos, UINT16 nCount);
    void Remove(UINT16 nPos, UINT16 nCount);
};
#endif

/************************************************************************/

// Degree Flags
#define DEGREE_FLAG_X           (0x0001)
#define DEGREE_FLAG_Y           (0x0002)
#define DEGREE_FLAG_Z           (0x0004)
#define DEGREE_FLAG_ALL         (DEGREE_FLAG_X|DEGREE_FLAG_Y|DEGREE_FLAG_Z)

/************************************************************************/

// Cut Flags for FindCut()
#define CUTFLAG_LINE            (0x0001)
#define CUTFLAG_START1          (0x0002)
#define CUTFLAG_START2          (0x0004)
#define CUTFLAG_END1            (0x0008)
#define CUTFLAG_END2            (0x0010)

#define CUTFLAG_ALL         (CUTFLAG_LINE|CUTFLAG_START1|CUTFLAG_START2|CUTFLAG_END1|CUTFLAG_END2)
#define CUTFLAG_DEFAULT     (CUTFLAG_LINE|CUTFLAG_START2|CUTFLAG_END2)

/************************************************************************/

class ImpPolyPolygon3D;
class ImpPolygon3D;
class PolyPolygon3D;
class E3dTriangle;
class E3dTriangleList;

/************************************************************************/

class Polygon3D
{
protected:
    ImpPolygon3D*               pImpPolygon3D;

    // ImpPolygon3D-ReferenceCount pruefen und ggf. abkoppeln
    void CheckReference();

    // Hilfsfunktionen fuer Triangulation
    UINT16 GetHighestEdge() const;

public:
    Polygon3D(UINT16 nSize = 4, UINT16 nResize = 4);
    Polygon3D(const Polygon3D& rPoly3D);
    Polygon3D(const Polygon& rPoly, double fScale = 1.0);
    // es wird keine Konvertierung des XPolygon durchgefuehrt,
    // sondern es werden nur die Punktkoordinaten uebernommen!
    Polygon3D(const XPolygon& rXPoly, double fScale = 1.0);
    ~Polygon3D();

    // Korrigiert das closed-Flag und entfernt den doppelten Punkt
    void CheckClosed();

//STRIP001  void SetSize(UINT16 nSize);
//STRIP001  UINT16 GetSize() const;

    void SetPointCount(UINT16 nPoints);
    UINT16 GetPointCount() const;

//STRIP001  void Remove(UINT16 nPos, UINT16 nCount);

    const Vector3D& operator[](UINT16 nPos) const;
    Vector3D& operator[](UINT16 nPos);
    Polygon3D& operator= (const Polygon3D& rPoly3D);
    BOOL operator==(const Polygon3D& rPoly3D) const;
//STRIP001  BOOL operator!=(const Polygon3D& rPoly3D) const;

    // Drehrichtung feststellen (fuer Polygone in der XY-Ebene) bzw. umkehren
    BOOL IsClockwise(const Vector3D &rNormal) const;
    BOOL IsClockwise() const { Vector3D aNrm(0.0, 0.0, 1.0); return IsClockwise(aNrm); }
    Vector3D GetNormal() const;
    Vector3D GetMiddle() const;
    void FlipDirection();
    BOOL IsClosed() const;
    void SetClosed(BOOL bNew);

    // aufeinanderfolgende doppelte Punkte sowie gleiche Anfangs- und
    // Endpunkte entfernen
    void RemoveDoublePoints();

    // Ueberlappen sich das aktuelle und das angegebene Polygon ?
//STRIP001  BOOL DoesBoundVolumeOverlap(const Polygon3D& rOrig, UINT16 nDegreeFlag=DEGREE_FLAG_ALL) const;
//STRIP001  BOOL DoesOverlap(const Polygon3D& rOrig, UINT16 nDegreeFlag=DEGREE_FLAG_ALL) const;

    // Existiert ein Schnitt zwischen den Polys?
//STRIP001  BOOL DoesCut(const Polygon3D& rOrig, UINT16 nDegreeFlag=DEGREE_FLAG_ALL) const;

    void Transform(const Matrix4D& rTfMatrix);

    BOOL IsInside(const Vector3D& rPnt, BOOL bWithBorder=FALSE) const;
    BOOL IsInside(const Polygon3D& rPoly, BOOL bWithBorder=TRUE) const;

    // different export formats
    XPolygon GetXPolygon() const;
    Polygon GetPolygon() const;

    Volume3D GetPolySize() const;
    double GetPolyArea(const Vector3D& rNormal) const;
//STRIP001  double GetPolyArea() const;

    // Laenge des Polygons liefern
    double GetLength() const;

    friend SvStream& operator>>(SvStream& rIStream, Polygon3D& rPoly3D);
    friend SvStream& operator<<(SvStream& rOStream, const Polygon3D& rPoly3D);

    // Schnitt zwischen den von den Punkten angegebenen Kanten ermitteln.
    // Dabei ist der Rueckgabewert != 0.0, wenn der Schnitt innerhalb
    // der Parameterbereiche der Kanten liegt und gibt den Wert ]0.0, 1.0]
    // innerhalb der ersten Kante an.
//STRIP001  UINT16 FindCut(UINT16 nEdge1, UINT16 nEdge2,
//STRIP001      UINT16 nCutFlags = CUTFLAG_DEFAULT,
//STRIP001      double* pCut1 = 0L, double* pCut2 = 0L) const;

    // Diese Version arbeitet mit der Kante nEdge1 aus dem lokalen
    // Polygon und nEdge2 aus dem uebergebenen
//STRIP001  UINT16 FindCut(UINT16 nEdge1, const Polygon3D& rPoly3D, UINT16 nEdge2,
//STRIP001      UINT16 nCutFlags = CUTFLAG_DEFAULT,
//STRIP001      double* pCut1 = 0L, double* pCut2 = 0L) const;

    // Diese Version nimmt die Startpunkte und Vektoren (relative Angabe
    // des Endpunktes) zweier Kanten
//STRIP001  static UINT16 FindCut(
//STRIP001      const Vector3D& rEdge1Start, const Vector3D& rEdge1Delta,
//STRIP001      const Vector3D& rEdge2Start, const Vector3D& rEdge2Delta,
//STRIP001      UINT16 nCutFlags = CUTFLAG_DEFAULT,
//STRIP001      double* pCut1 = 0L, double* pCut2 = 0L);

    // test if point is on line in range ]0.0..1.0[ without
    // the points. If so, return TRUE and put the parameter
    // value in pCut (if provided)
//STRIP001  static BOOL FindPointInLine(const Vector3D& rPoint,
//STRIP001      const Vector3D& rEdgeStart, const Vector3D& rEdgeDelta,
//STRIP001      double* pCut = 0L);

    // Orientierung im Punkt nIndex liefern
    BOOL GetPointOrientation(UINT16 nIndex) const;

    // get position on polypos, with clipping to start/end
    Vector3D GetPosition(double fPos) const;

    // create a expanded or compresssed poly with exactly nNum Points
    Polygon3D GetExpandedPolygon(sal_uInt32 nNum);
};

/************************************************************************/

#define TEST_MERGE
#ifdef TEST_MERGE
extern OutputDevice* pThisIsTheActualOutDev;
#endif

///////////////////////////////////////////////////////////////////////////////

class PolyPolygon3D
{
protected:
    ImpPolyPolygon3D*           pImpPolyPolygon3D;

    void CheckReference();

public:
    PolyPolygon3D(UINT16 nInitSize = 4, UINT16 nResize = 4);
    PolyPolygon3D(const Polygon3D& r3DPoly);
    PolyPolygon3D(const PolyPolygon3D& r3DPolyPoly);
    PolyPolygon3D(const Polygon& rPoly, double fScale = 1.0);
    PolyPolygon3D(const PolyPolygon& rPolyPoly, double fScale = 1.0);
    PolyPolygon3D(const XPolygon& rXPoly, double fScale = 1.0);
    PolyPolygon3D(const XPolyPolygon& rXPolyPoly, double fScale = 1.0);
    ~PolyPolygon3D();

    // Korrigiert das closed-Flag und entfernt den doppelten Punkt
//STRIP001  void CheckClosed();

    void Insert(const Polygon3D& rPoly3D, UINT16 nPos = POLYPOLY3D_APPEND);
    void Insert(const PolyPolygon3D& rPoly3D, UINT16 nPos = POLYPOLY3D_APPEND);

//STRIP001  Polygon3D Remove(UINT16 nPos);
//STRIP001  Polygon3D Replace(const Polygon3D& rPoly3D, UINT16 nPos);

    const Polygon3D& GetObject(UINT16 nPos) const;

    void Clear();
    UINT16 Count() const;
//STRIP001  BOOL IsInside(const Vector3D& rPnt, BOOL bWithBorder=FALSE) const;
//STRIP001  BOOL IsInside(const Polygon3D& rPoly, BOOL bWithBorder=TRUE) const;
//STRIP001  BOOL GetCutPoint(Vector3D &rCut, const Vector3D &rLeft, const Vector3D &rRight) const;

    const Polygon3D& operator[](UINT16 nPos) const { return GetObject(nPos); }
    Polygon3D& operator[](UINT16 nPos);

    PolyPolygon3D& operator=(const PolyPolygon3D& rPolyPoly3D);
//STRIP001  BOOL operator==(const PolyPolygon3D& rPolyPoly3D) const;
    BOOL operator!=(const PolyPolygon3D& rPolyPoly3D) const;

    void Transform(const Matrix4D& rTfMatrix);

    void FlipDirection(UINT16 nInd=0);
    void FlipDirections();

    // Die Umlaufrichtungen ineinanderliegender Polygone anpassen
    void SetDirections(const Vector3D& rNormal);
    void SetDirections() { Vector3D aNormal = GetNormal(); SetDirections(aNormal); }

    // in allen Polygonen aufeinanderfolgende doppelte Punkte sowie
    // gleiche Anfangs- und Endpunkte entfernen
    void RemoveDoublePoints();

    // Remove all completely overlapping polygons
//STRIP001  UINT16 RemoveContainedPolygons(BOOL bRemoveHoles=FALSE, BOOL bWithBorder=TRUE);

    // evtl. entstandene Selbstueberschneidungen in Eckpunkten
    // ohne Punktreduzierung korrigieren
    void CorrectGrownPoly(const PolyPolygon3D& rOrig);

    // Ueberlappen sich das aktuelle und das angegebene PolyPolygon ?
//STRIP001  BOOL DoesBoundVolumeOverlap(const PolyPolygon3D& rOrig, UINT16 nDegreeFlag=DEGREE_FLAG_ALL) const;
//STRIP001  BOOL DoesOverlap(const PolyPolygon3D& rOrig, UINT16 nDegreeFlag=DEGREE_FLAG_ALL) const;

    friend SvStream& operator>>(SvStream& rIStream, PolyPolygon3D& rPolyPoly3D);
    friend SvStream& operator<<(SvStream& rOStream, const PolyPolygon3D& rPolyPoly3D);

    // Drehrichtung feststellen (fuer Polygone in der XY-Ebene) bzw. umkehren
    BOOL IsClockwise(UINT16 nInd=0) const;
    Vector3D GetNormal() const;
    Vector3D GetMiddle() const;
    BOOL IsClosed() const;

    XPolyPolygon GetXPolyPolygon() const;
    PolyPolygon GetPolyPolygon() const;

    Volume3D GetPolySize() const;
    double GetPolyArea() const;

    // Laenge des Polygons liefern
    double GetLength() const;

    // Umschliessenden Kugelradius feststellen
    double GetEnclosingRadius() const;

    // merge the contents of the whole PolyPolygon to contain no more
    // cuts or overlaps. Makes all necessary merges between all
    // contained polygons. Preserves Holes.
//STRIP001  void Merge(BOOL bForceClockwise = TRUE, BOOL bInvertRemove = FALSE);
};

}//end of namespace binfilter
#endif      // _POLY3D_HXX

