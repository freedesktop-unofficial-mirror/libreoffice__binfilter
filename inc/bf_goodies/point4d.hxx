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

#ifndef _B3D_POINT4D_HXX
#define _B3D_POINT4D_HXX

#include <bf_svtools/bf_solar.h>


#include "vector3d.hxx"

#include "point3d.hxx"

#include <tools/stream.hxx>


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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
