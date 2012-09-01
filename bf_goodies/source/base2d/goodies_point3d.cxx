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

#include "point3d.hxx"

/*************************************************************************
|*
|* Konstruktor aus Point
|*
\************************************************************************/

namespace binfilter {

/*************************************************************************
|*
|* Punktaddition
|*
\************************************************************************/

Point3D& Point3D::operator+= (const Point3D& rPnt)
{
    if(rPnt[2] == 1.0)
    {
        if(V[2] == 1.0)
        {
            V[0] = V[0] + rPnt[0];
            V[1] = V[1] + rPnt[1];
        }
        else
        {
            V[0] = V[0] + rPnt[0] * V[2];
            V[1] = V[1] + rPnt[1] * V[2];
        }
    }
    else
    {
        if(V[2] == 1.0)
        {
            V[0] = V[0] * rPnt[2] + rPnt[0];
            V[1] = V[1] * rPnt[2] + rPnt[1];
            V[2] = rPnt[2];
        }
        else
        {
            V[0] = V[0] * rPnt[2] + rPnt[0] * V[2];
            V[1] = V[1] * rPnt[2] + rPnt[1] * V[2];
            V[2] = V[2] * rPnt[2];
        }
    }
    return *this;
}

/*************************************************************************
|*
|* Punktsubtraktion
|*
\************************************************************************/

Point3D& Point3D::operator-= (const Point3D& rPnt)
{
    if(rPnt[2] == 1.0)
    {
        if(V[2] == 1.0)
        {
            V[0] = V[0] - rPnt[0];
            V[1] = V[1] - rPnt[1];
        }
        else
        {
            V[0] = V[0] - rPnt[0] * V[2];
            V[1] = V[1] - rPnt[1] * V[2];
        }
    }
    else
    {
        if(V[2] == 1.0)
        {
            V[0] = V[0] * rPnt[2] - rPnt[0];
            V[1] = V[1] * rPnt[2] - rPnt[1];
            V[2] = rPnt[2];
        }
        else
        {
            V[0] = V[0] * rPnt[2] - rPnt[0] * V[2];
            V[1] = V[1] * rPnt[2] - rPnt[1] * V[2];
            V[2] = V[2] * rPnt[2];
        }
    }
    return *this;
}

/*************************************************************************
|*
|* Punktaddition, neuen Vektor erzeugen
|*
\************************************************************************/

Point3D Point3D::operator+ (const Point3D& rPnt) const
{
    Point3D aSum = *this;
    aSum += rPnt;
    return aSum;
}

/*************************************************************************
|*
|* Punktsubtraktion, neuen Vektor erzeugen
|*
\************************************************************************/

Point3D Point3D::operator- (const Point3D& rPnt) const
{
    Point3D aSub = *this;
    aSub -= rPnt;
    return aSub;
}

/*************************************************************************
|*
|* Punktnegation
|*
\************************************************************************/

Point3D Point3D::operator- (void) const
{
    Point3D aPnt = *this;
    aPnt[2] = -V[2];
    return aPnt;
}

/*************************************************************************
|*
|* Punktmultiplikation
|*
\************************************************************************/

Point3D& Point3D::operator*= (const Point3D& rPnt)
{
    V[0] = V[0] * rPnt[0];
    V[1] = V[1] * rPnt[1];
    V[2] = V[2] * rPnt[2];
    return *this;
}

/*************************************************************************
|*
|* Punktdivision
|*
\************************************************************************/

Point3D& Point3D::operator/= (const Point3D& rPnt)
{
    if(rPnt[0] != 0.0 && rPnt[1] != 0.0 && rPnt[2] != 0.0)
    {
        V[0] = V[0] / rPnt[0];
        V[1] = V[1] / rPnt[1];
        V[2] = V[2] / rPnt[2];
    }
    return *this;
}

/*************************************************************************
|*
|* Punktmultiplikation, neuen Punkt erzeugen
|*
\************************************************************************/

Point3D Point3D::operator* (const Point3D& rPnt) const
{
    Point3D aSum = *this;
    aSum *= rPnt;
    return aSum;
}

/*************************************************************************
|*
|* Punktdivision, neuen Punkt erzeugen
|*
\************************************************************************/

Point3D Point3D::operator/ (const Point3D& rPnt) const
{
    Point3D aSub = *this;
    aSub /= rPnt;
    return aSub;
}

/*************************************************************************
|*
|* Punkttranslation
|*
\************************************************************************/

Point3D& Point3D::operator+= (const Vector2D& rVec)
{
    if(V[2] == 1.0)
    {
        V[0] = V[0] + rVec.X();
        V[1] = V[1] + rVec.Y();
    }
    else
    {
        V[0] = V[0] + rVec.X() * V[2];
        V[1] = V[1] + rVec.Y() * V[2];
    }
    return *this;
}

/*************************************************************************
|*
|* Punkttranslation um negativen Vektor
|*
\************************************************************************/

Point3D& Point3D::operator-= (const Vector2D& rVec)
{
    if(V[2] == 1.0)
    {
        V[0] = V[0] - rVec.X();
        V[1] = V[1] - rVec.Y();
    }
    else
    {
        V[0] = V[0] - rVec.X() * V[2];
        V[1] = V[1] - rVec.Y() * V[2];
    }
    return *this;
}

/*************************************************************************
|*
|* Punkttranslation, neuen Punkt erzeugen
|*
\************************************************************************/

Point3D Point3D::operator+ (const Vector2D& rVec) const
{
    Point3D aSum = *this;
    aSum += rVec;
    return aSum;
}

/*************************************************************************
|*
|* Punkttranslation um negativen Vektor, neuen Punkt erzeugen
|*
\************************************************************************/

Point3D Point3D::operator- (const Vector2D& rVec) const
{
    Point3D aSum = *this;
    aSum -= rVec;
    return aSum;
}

/*************************************************************************
|*
|* Multiplikation mit Faktor
|*
\************************************************************************/

Point3D& Point3D::operator*= (double fFactor)
{
    V[2] /= fFactor;
    return *this;
}

/*************************************************************************
|*
|* Multiplikation mit Faktor, neuen Punkt erzeugen
|*
\************************************************************************/

Point3D Point3D::operator* (double fFactor) const
{
    Point3D aNewPnt = *this;
    aNewPnt.W() /= fFactor;
    return aNewPnt;
}

/*************************************************************************
|*
|* Division mit Faktor
|*
\************************************************************************/

Point3D& Point3D::operator/= (double fDiv)
{
    if (fDiv != 0.0)
        V[2] *= fDiv;
    return *this;
}

/*************************************************************************
|*
|* Division mit Faktor, neuen Punkt erzeugen
|*
\************************************************************************/

Point3D Point3D::operator/ (double fDiv) const
{
    Point3D aNewPnt = *this;
    if (fDiv != 0.0)
        aNewPnt.W() *= fDiv;
    return aNewPnt;
}

/*************************************************************************
|*
|* Gleichheit
|*
\************************************************************************/

BOOL Point3D::operator==(const Point3D& rPnt) const
{
    if(rPnt[2] == 1.0)
    {
        if(V[2] == 1.0)
        {
            if(V[0] == rPnt[0])
                if(V[1] == rPnt[1])
                    return TRUE;
        }
        else
        {
            if(V[0] == V[2] * rPnt[0])
                if(V[1] == V[2] * rPnt[1])
                    return TRUE;
        }
    }
    else
    {
        if(V[2] == 1.0)
        {
            if(V[0] * rPnt[2] == rPnt[0])
                if(V[1] * rPnt[2] == rPnt[1])
                    return TRUE;
        }
        else
        {
            if(V[0] * rPnt[2] == V[2] * rPnt[0])
                if(V[1] * rPnt[2] == V[2] * rPnt[1])
                    return TRUE;
        }
    }
    return FALSE;
}

/*************************************************************************
|*
|* Ungleichheit
|*
\************************************************************************/

BOOL Point3D::operator!=(const Point3D& rPnt) const
{
    if(rPnt[2] == 1.0)
    {
        if(V[2] == 1.0)
        {
            if(V[0] == rPnt[0])
                if(V[1] == rPnt[1])
                    return FALSE;
        }
        else
        {
            if(V[0] == V[2] * rPnt[0])
                if(V[1] == V[2] * rPnt[1])
                    return FALSE;
        }
    }
    else
    {
        if(V[2] == 1.0)
        {
            if(V[0] * rPnt[2] == rPnt[0])
                if(V[1] * rPnt[2] == rPnt[1])
                    return FALSE;
        }
        else
        {
            if(V[0] * rPnt[2] == V[2] * rPnt[0])
                if(V[1] * rPnt[2] == V[2] * rPnt[1])
                    return FALSE;
        }
    }
    return TRUE;
}

/*************************************************************************
|*
|* Stream-In-Operator fuer Point3D
|*
\************************************************************************/

SvStream& operator>>(SvStream& rIStream, Point3D& rPoint3D)
{
    for (int i = 0; i < 3; i++)
        rIStream >> rPoint3D.V[i];

    return rIStream;
}

/*************************************************************************
|*
|* Stream-Out-Operator fuer Point3D
|*
\************************************************************************/

SvStream& operator<<(SvStream& rOStream, const Point3D& rPoint3D)
{
    for (int i = 0; i < 3; i++)
        rOStream << rPoint3D.V[i];

    return rOStream;
}
}//end of namespace binfilter

// eof

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
