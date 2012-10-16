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

#ifndef _SVX_VECTOR3D_HXX
#define _SVX_VECTOR3D_HXX

#include <bf_svtools/bf_solar.h>

#ifndef _INC_MATH
#include <math.h>
#endif

#include <vector>

class Point;
class SvStream;

/*************************************************************************
|*
|* 3D-Vektor
|*
\************************************************************************/

namespace binfilter {
class Vector3D
{
 protected:
    double V[3];

 public:
    Vector3D(double fX = 0, double fY = 0, double fZ = 0)
        { V[0] = fX; V[1] = fY; V[2] = fZ; }
    Vector3D(const Point& rPnt, double fZ = 0);
    const double& X() const { return V[0]; }
    const double& Y() const { return V[1]; }
    const double& Z() const { return V[2]; }
    double& X() { return V[0]; }
    double& Y() { return V[1]; }
    double& Z() { return V[2]; }
    const double& operator[] (int nPos) const { return V[nPos]; }
    double& operator[] (int nPos) { return V[nPos]; }

    double  GetLength(void) const;
    double  GetXZLength(void) const;
    double  GetYZLength(void) const;

    void    Normalize();
    void    Min(const Vector3D& rVec);
    void    Max(const Vector3D& rVec);
    void    Abs();

    void CalcInBetween(const Vector3D& rOld1, const Vector3D& rOld2, double t);
    void CalcMiddle(const Vector3D& rOld1, const Vector3D& rOld2);

    Vector3D&   operator+=  (const Vector3D&);
    Vector3D&   operator-=  (const Vector3D&);
    Vector3D    operator+   (const Vector3D&) const;
    Vector3D    operator-   (const Vector3D&) const;
    Vector3D    operator-   (void) const;

    // Kreuzprodukt mittels operator| (wie: Senkrecht)
    Vector3D&   operator|=  (const Vector3D&);
    Vector3D    operator|   (const Vector3D&) const;

    // Skalarprodukt als Methode, um Verwechslungen zu vermeiden
    double Scalar(const Vector3D&) const;

    Vector3D&   operator/=  (const Vector3D&);
    Vector3D    operator/   (const Vector3D&) const;
    Vector3D&   operator*=  (const Vector3D&);
    Vector3D    operator*   (const Vector3D&) const;

    Vector3D&   operator*=  (double);
    Vector3D    operator*   (double) const;
    Vector3D&   operator/=  (double);
    Vector3D    operator/   (double) const;

    BOOL        operator==  (const Vector3D&) const;
    BOOL        operator!=  (const Vector3D&) const;

    friend SvStream& operator>>(SvStream& rIStream, Vector3D&);
    friend SvStream& operator<<(SvStream& rOStream, const Vector3D&);
};

// #110988# typedefs for a vector of Vector3Ds
typedef ::std::vector< Vector3D > Vector3DVector;

}//end of namespace binfilter
#endif // _SVX_VECTOR3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
