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

#ifndef _B2D_POINT3D_HXX
#define _B2D_POINT3D_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/stream.hxx>

#include <tools/gen.hxx>

#include <tools/vector2d.hxx>

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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
