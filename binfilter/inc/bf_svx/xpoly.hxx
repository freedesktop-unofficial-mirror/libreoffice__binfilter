/*************************************************************************
 *
 *  $RCSfile: xpoly.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:47 $
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
#ifndef _XPOLY_HXX
#define _XPOLY_HXX

// include ---------------------------------------------------------------

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

class Point;
class Rectangle;
class SvStream;
class Polygon;
class PolyPolygon;
class OutputDevice;
namespace binfilter {

/************************************************************************/

#define XPOLYPOLY_APPEND     0xFFFF
#define XPOLY_APPEND         0xFFFF

#ifdef WIN // Windows 16 Bit
#define XPOLY_MAXPOINTS      8160   /* =0xFF00/sizeof(Point), also mit etwas Platz! */
#else
#define XPOLY_MAXPOINTS      0xFFF0 /* Auch fuer die 32-Bitter etwas Luft lassen */
#endif

/************************************************************************/
// Punktstile im XPolygon:
// NORMAL : Anfangs- oder Endpunkt einer Kurve oder Linie
// SMOOTH : Glatter Uebergang zwischen Kurven
// SYMMTR : glatter und symmetrischer Uebergang zwischen Kurven
// CONTROL: Kontrollpunkt einer Bezierkurve

enum XPolyFlags { XPOLY_NORMAL, XPOLY_SMOOTH, XPOLY_CONTROL, XPOLY_SYMMTR };

/*************************************************************************
|*
|* Klasse XPolygon; hat neben dem Point-Array noch ein Array mit Flags,
|* die Informationen ueber den jeweiligen Punkt enthalten
|*
\************************************************************************/

class ImpXPolygon;

class XPolygon
{
protected:
    ImpXPolygon*    pImpXPolygon;

    // ImpXPolygon-ReferenceCount pruefen und ggf. abkoppeln
    void    CheckReference();

    // Hilfsfunktionen fuer Bezierkonvertierung
    void    SubdivideBezier(USHORT nPos, BOOL bCalcFirst, double fT);
    void    GenBezArc(const Point& rCenter, long nRx, long nRy,
                      long nXHdl, long nYHdl, USHORT nStart, USHORT nEnd,
                      USHORT nQuad, USHORT nFirst);
    BOOL    CheckAngles(USHORT& nStart, USHORT nEnd, USHORT& nA1, USHORT& nA2);

public:
    XPolygon( USHORT nSize=16, USHORT nResize=16 );
    XPolygon( const XPolygon& rXPoly );
    XPolygon( const Polygon& rPoly );
    XPolygon( const Rectangle& rRect, long nRx = 0, long nRy = 0 );
    XPolygon( const Point& rCenter, long nRx, long nRy,
              USHORT nStartAngle = 0, USHORT nEndAngle = 3600,
              BOOL bClose = TRUE );

    ~XPolygon();

    void        SetSize( USHORT nSize );
//STRIP001  USHORT      GetSize() const;

    void        SetPointCount( USHORT nPoints );
    USHORT      GetPointCount() const;

    void        Insert( USHORT nPos, const Point& rPt, XPolyFlags eFlags );
//STRIP001  void        Insert( USHORT nPos, const XPolygon& rXPoly );
//STRIP001  void        Insert( USHORT nPos, const Polygon& rPoly );
    void        Remove( USHORT nPos, USHORT nCount );
    void        Move( long nHorzMove, long nVertMove );
    Rectangle   GetBoundRect(OutputDevice* pOut = NULL) const;

    const Point&    operator[]( USHORT nPos ) const;
          Point&    operator[]( USHORT nPos );
    XPolygon&       operator=( const XPolygon& rXPoly );
    BOOL            operator==( const XPolygon& rXPoly ) const;
    BOOL            operator!=( const XPolygon& rXPoly ) const;

    XPolyFlags  GetFlags( USHORT nPos ) const;
    void        SetFlags( USHORT nPos, XPolyFlags eFlags );
    BOOL        IsControl(USHORT nPos) const;
//STRIP001  BOOL        IsSmooth(USHORT nPos) const;

    // Abstand zwischen zwei Punkten
//STRIP001  double  CalcDistance(USHORT nP1, USHORT nP2);

    // Bezierkonvertierungen
//STRIP001  void CalcSmoothJoin(USHORT nCenter, USHORT nDrag, USHORT nPnt);
//STRIP001  void CalcTangent(USHORT nCenter, USHORT nPrev, USHORT nNext);
//STRIP001  void PointsToBezier(USHORT nFirst);

    // Transformationen
    void Translate(const Point& rTrans);
    void Rotate(const Point& rCenter, double fSin, double fCos);
    void Rotate(const Point& rCenter, USHORT nAngle);
    void Scale(double fSx, double fSy);
    void SlantX(long nYRef, double fSin, double fCos);
//STRIP001  void SlantY(long nXRef, double fSin, double fCos);
//STRIP001  void Distort(const Rectangle& rRefRect, const XPolygon& rDistortedRect);
//STRIP001  void Rotate20 ();

    friend SvStream& operator>>( SvStream& rIStream, XPolygon& rXPoly );
    friend SvStream& operator<<( SvStream& rOStream, const XPolygon& rXPoly );
};

/*************************************************************************
|*
|* Klasse XPolyPolygon; wie PolyPolygon, nur statt aus Polygonen aus
|* XPolygonen bestehend
|*
\************************************************************************/

class ImpXPolyPolygon;

class XPolyPolygon
{
protected:
    ImpXPolyPolygon* pImpXPolyPolygon;

    // ImpXPolyPolygon-ReferenceCount pruefen und ggf. abkoppeln
    void    CheckReference();

public:
                    XPolyPolygon( USHORT nInitSize = 16, USHORT nResize = 16 );
                    XPolyPolygon( const XPolygon& rXPoly );
                    XPolyPolygon( const XPolyPolygon& rXPolyPoly );
                    XPolyPolygon( const PolyPolygon& rPolyPoly);

                    ~XPolyPolygon();

    void            Insert( const XPolygon& rXPoly,
                            USHORT nPos = XPOLYPOLY_APPEND );
//STRIP001  void            Insert( const XPolyPolygon& rXPoly,
//STRIP001                          USHORT nPos=XPOLYPOLY_APPEND );
//STRIP001  XPolygon        Remove( USHORT nPos );
//STRIP001  XPolygon        Replace( const XPolygon& rXPoly, USHORT nPos );
    const XPolygon& GetObject( USHORT nPos ) const;

    void            Clear();
    USHORT          Count() const;

    void            Move( long nHorzMove, long nVertMove );
    Rectangle       GetBoundRect(OutputDevice* pOut = NULL) const;

    const XPolygon& operator[]( USHORT nPos ) const
                        { return GetObject( nPos ); }
    XPolygon&       operator[]( USHORT nPos );

    XPolyPolygon&   operator=( const XPolyPolygon& rXPolyPoly );
//STRIP001  BOOL            operator==( const XPolyPolygon& rXPolyPoly ) const;
//STRIP001  BOOL            operator!=( const XPolyPolygon& rXPolyPoly ) const;

    // Transformationen
    void Translate(const Point& rTrans);
    void Rotate(const Point& rCenter, double fSin, double fCos);
//STRIP001  void Rotate(const Point& rCenter, USHORT nAngle);
    void Scale(double fSx, double fSy);
    void SlantX(long nYRef, double fSin, double fCos);
//STRIP001  void SlantY(long nXRef, double fSin, double fCos);
//STRIP001  void Distort(const Rectangle& rRefRect, const XPolygon& rDistortedRect);
//STRIP001  void Rotate20 ();

    friend SvStream& operator>>( SvStream& rIStream, XPolyPolygon& rXPolyPoly );
    friend SvStream& operator<<( SvStream& rOStream, const XPolyPolygon& rXPolyPoly );
};

}//end of namespace binfilter
#endif      // _XPOLY_HXX

