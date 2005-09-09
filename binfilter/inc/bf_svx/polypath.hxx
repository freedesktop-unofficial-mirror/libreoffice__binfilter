/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: polypath.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:12:19 $
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

#ifndef _POLYPATH_HXX
#define _POLYPATH_HXX

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace binfilter {

class XPolygon; // Dummy zum Uebersetzen

enum PathKind {PATH_POLYGON,
               PATH_POLYLINE,
               PATH_BEZIER,
               PATH_BEZIERLINE};

class PolyPath {
protected:
    // ...
public:
    PolyPath();
    PolyPath(const PolyPath& rPath);
    ~PolyPath();
    void Clear();

          USHORT    GetPathCount()        const;
          PathKind  GetPathKind(USHORT i) const;
    const Polygon&  GetPolygon (USHORT i) const;
    const XPolygon& GetXPolygon(USHORT i) const;
          Polygon&  GetPolygon (USHORT i);
          XPolygon& GetXPolygon(USHORT i);
    const Polygon&  operator[] (USHORT i); // eigentlich identisch mit Get

    void InsertPolyPath  (const PolyPath&   , USHORT nPos=POLYPOLY_APPEND);
    void InsertPolygon   (const Polygon&    , USHORT nPos=POLYPOLY_APPEND);
    void InsertPolygon   (const PolyPolygon&, USHORT nPos=POLYPOLY_APPEND);
    void InsertPolyLine  (const Polygon&    , USHORT nPos=POLYPOLY_APPEND);
    void InsertBezier    (const XPolygon&   , USHORT nPos=POLYPOLY_APPEND);
    void InsertBezierLine(const XPolygon&   , USHORT nPos=POLYPOLY_APPEND);

    BOOL operator==(const PolyPath& rPath);
    void operator!=(const PolyPath& rPath);
    void operator= (const PolyPath& rPath);
    void operator+=(const Point&);
    void operator-=(const Point&);

    Rectangle GetBoundRect() const;
    BOOL IsInside(const Point&) const;
    BOOL IsTouch(const Rectangle&) const;
};

// ExtOutputDevice::DrawPolyPath(const PolyPath&)
// Alle Polygone und Beziers werden zu einem einzigen PolyPolygon gemacht das
// dann mit DrawPolyPolygon() ausgegeben wird. Alle PolyLines und BezierLines
// werden dagegen mit DrawPolyLine() (oder DrawPolyPolyLine()?) gamalt.

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_POLYPATH_HXX

