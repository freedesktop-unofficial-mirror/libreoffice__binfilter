/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: goodies_point3d.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 11:56:31 $
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
#include "point3d.hxx"
#endif

/*************************************************************************
|*
|* Konstruktor aus Point
|*
\************************************************************************/

namespace binfilter {
Point3D::Point3D(const Point& rPnt, double fW )
{
    V[0] = rPnt.X();
    V[1] = rPnt.Y();
    V[2] = fW;
}

/*************************************************************************
|*
|* Konstruktor aus Vector2D
|*
\************************************************************************/

Point3D::Point3D(const Vector2D& rPnt, double fW )
{
    V[0] = rPnt.X();
    V[1] = rPnt.Y();
    V[2] = fW;
}

/*************************************************************************
|*
|* Punkt Korrigieren (in homogene Koorinaten wandeln)
|*
\************************************************************************/

void Point3D::ImplHomogenize(void)
{
    if(V[2] != 0.0)
    {
        V[0] /= V[2];
        V[1] /= V[2];
        V[2] = 1.0;
    }
}

/*************************************************************************
|*
|* Punkt als Vector2D zurueckliefern. Dazu wird er Homogenisiert, wonach
|* die vierte Dimension (W) keine Rolle mehr spielt. An dieser Stelle
|* wird ausnahmsweise mal gecastet, aber zumindest ein const
|* zurueckgegeben.
|*
\************************************************************************/

const Vector2D& Point3D::GetVector2D() const
{
    ((Point3D* const)this)->Homogenize();
    return *((Vector2D*)this);
}

/*************************************************************************
|*
|* Neuen Punkt an der Stelle t im Parametergebiet der Linie berechnen
|*
\************************************************************************/

void Point3D::CalcInBetween(Point3D& rOld1, Point3D& rOld2, double t)
{
    // Punktkoordinaten berechnen
    for(UINT16 i=0;i<3;i++)
    {
        if(rOld2[i] == rOld1[i])
        {
            V[i] = rOld1[i];
        }
        else
        {
            V[i] = ((rOld2[i] - rOld1[i]) * t) + rOld1[i];
        }
    }
}

/*************************************************************************
|*
|* Neuen Punkt in der Mitte der Linie berechnen
|*
\************************************************************************/

void Point3D::CalcMiddle(Point3D& rOld1, Point3D& rOld2)
{
    // Punktkoordinaten berechnen
    for(UINT16 i=0;i<3;i++)
    {
        if(rOld2[i] == rOld1[i])
        {
            V[i] = rOld1[i];
        }
        else
        {
            V[i] = (rOld1[i] + rOld2[i]) / 2.0;
        }
    }
}

/*************************************************************************
|*
|* Neuen Punkt in der Mitte der drei Punkte berechnen
|*
\************************************************************************/

void Point3D::CalcMiddle(Point3D& rOld1, Point3D& rOld2, Point3D& rOld3)
{
    // Punktkoordinaten berechnen
    for(UINT16 i=0;i<3;i++)
    {
        if(rOld3[i] == rOld2[i] && rOld2[i] == rOld1[i])
        {
            V[i] = rOld1[i];
        }
        else
        {
            V[i] = (rOld1[i] + rOld2[i] + rOld3[i]) / 3.0;
        }
    }
}

/*************************************************************************
|*
|* Minimum aus diesem und dem uebergebenen Punkt bilden
|*
\************************************************************************/

void Point3D::Min(const Point3D& rPnt)
{
    Point3D aCompare = rPnt;
    aCompare.Homogenize();
    Homogenize();
    if ( V[0] > aCompare.V[0] ) V[0] = aCompare.V[0];
    if ( V[1] > aCompare.V[1] ) V[1] = aCompare.V[1];
}

/*************************************************************************
|*
|* Maximum aus diesem und dem uebergebenen Punkt bilden
|*
\************************************************************************/

void Point3D::Max(const Point3D& rPnt)
{
    Point3D aCompare = rPnt;
    aCompare.Homogenize();
    Homogenize();
    if ( V[0] < aCompare.V[0] ) V[0] = aCompare.V[0];
    if ( V[1] < aCompare.V[1] ) V[1] = aCompare.V[1];
}

/*************************************************************************
|*
|* Absolutwert
|*
\************************************************************************/

void Point3D::Abs()
{
    if ( V[0] < 0 ) V[0] = - V[0];
    if ( V[1] < 0 ) V[1] = - V[1];
}

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
            V[0] = V[0] + rPnt[0] * V[3];
            V[1] = V[1] + rPnt[1] * V[3];
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
            V[0] = V[0] - rPnt[0] * V[3];
            V[1] = V[1] - rPnt[1] * V[3];
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
