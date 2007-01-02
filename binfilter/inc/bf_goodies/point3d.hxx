/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: point3d.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:23:04 $
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

#ifndef _B2D_POINT3D_HXX
#define _B2D_POINT3D_HXX

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _SV_GEN_HXX
#include <tools/gen.hxx>
#endif

#ifndef _VECTOR2D_HXX
#include <tools/vector2d.hxx>
#endif

/*************************************************************************
|*
|* homogener 3D-Punkt (x,y,w)
|*
\************************************************************************/

namespace binfilter {
class Point3D
{
protected:
    // 3 Dimensinen, X,Y und W
    double                      V[3];

public:
    Point3D(double fX = 0.0, double fY = 0.0, double fW = 1.0)
        { V[0] = fX; V[1] = fY; V[2] = fW; }

    const double& X() const { return V[0]; }
    const double& Y() const { return V[1]; }
    const double& W() const { return V[2]; }

    double& X() { return V[0]; }
    double& Y() { return V[1]; }
    double& W() { return V[2]; }

    const double& operator[] (int nPos) const { return V[nPos]; }
    double& operator[] (int nPos) { return V[nPos]; }

    // Rechnen untereinander
    Point3D&    operator+=  (const Point3D&);
    Point3D&    operator-=  (const Point3D&);
    Point3D     operator+   (const Point3D&) const;
    Point3D     operator-   (const Point3D&) const;
    Point3D     operator-   (void) const;
    Point3D&    operator*=  (const Point3D&);
    Point3D&    operator/=  (const Point3D&);
    Point3D     operator*   (const Point3D&) const;
    Point3D     operator/   (const Point3D&) const;

    // Verschiebung um einen Vektor
    Point3D&    operator+=  (const Vector2D&);
    Point3D&    operator-=  (const Vector2D&);
    Point3D     operator+   (const Vector2D&) const;
    Point3D     operator-   (const Vector2D&) const;

    // Multiplikation, Division um einen Faktor
    Point3D&    operator*=  (double);
    Point3D     operator*   (double) const;
    Point3D&    operator/=  (double);
    Point3D     operator/   (double) const;

    BOOL        operator==  (const Point3D&) const;
    BOOL        operator!=  (const Point3D&) const;

    friend SvStream& operator>>(SvStream& rIStream, Point3D&);
    friend SvStream& operator<<(SvStream& rOStream, const Point3D&);
};
}//end of namespace binfilter


#endif          // _B2D_POINT3D_HXX
