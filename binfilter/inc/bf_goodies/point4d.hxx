/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: point4d.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:23:15 $
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

#ifndef _B3D_POINT4D_HXX
#define _B3D_POINT4D_HXX

#ifndef _SVX_VECTOR3D_HXX //autogen
#include "vector3d.hxx"
#endif

#ifndef _SVX_POINT3D_HXX
#include "point3d.hxx"
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif


/*************************************************************************
|*
|* homogener 4D-Punkt (x,y,z,w)
|*
\************************************************************************/

namespace binfilter {
class Point4D
{
protected:
    // 4 Dimensinen, X,Y,Z und W
    double V[4];

    void    ImplHomogenize();

public:
    Point4D(double fX = 0.0, double fY = 0.0, double fZ = 0.0, double fW = 1.0)
        { V[0] = fX; V[1] = fY; V[2] = fZ; V[3] = fW; }
    Point4D(const Vector3D& rVec, double fW = 1.0);

    const double& X() const { return V[0]; }
    const double& Y() const { return V[1]; }
    const double& Z() const { return V[2]; }
    const double& W() const { return V[3]; }

    double& X() { return V[0]; }
    double& Y() { return V[1]; }
    double& Z() { return V[2]; }
    double& W() { return V[3]; }

    const double& operator[] (int nPos) const { return V[nPos]; }
    double& operator[] (int nPos) { return V[nPos]; }

    void    Homogenize() { if(V[3] != 1.0) ImplHomogenize(); }
    const Vector3D& GetVector3D() const;

    void CalcInBetween(Point4D& rOld1, Point4D& rOld2, double t);
    void CalcMiddle(Point4D& rOld1, Point4D& rOld2);

    // Rechnen untereinander
    Point4D&    operator+=  (const Point4D&);
    Point4D&    operator-=  (const Point4D&);
    Point4D     operator+   (const Point4D&) const;
    Point4D     operator-   (const Point4D&) const;
    Point4D     operator-   (void) const;
    Point4D&    operator*=  (const Point4D&);
    Point4D&    operator/=  (const Point4D&);
    Point4D     operator*   (const Point4D&) const;
    Point4D     operator/   (const Point4D&) const;

    // Verschiebung um einen Vektor
    Point4D&    operator+=  (const Vector3D&);
    Point4D&    operator-=  (const Vector3D&);
    Point4D     operator+   (const Vector3D&) const;
    Point4D     operator-   (const Vector3D&) const;

    // Multiplikation, Division um einen Faktor
    Point4D&    operator*=  (double);
    Point4D     operator*   (double) const;
    Point4D&    operator/=  (double);
    Point4D     operator/   (double) const;

    BOOL        operator==  (const Point4D&) const;
    BOOL        operator!=  (const Point4D&) const;

    friend SvStream& operator>>(SvStream& rIStream, Point4D&);
    friend SvStream& operator<<(SvStream& rOStream, const Point4D&);
};
}//end of namespace binfilter


#endif          // _B3D_POINT4D_HXX
