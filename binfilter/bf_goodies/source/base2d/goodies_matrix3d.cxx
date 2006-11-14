/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: goodies_matrix3d.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 11:56:23 $
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

#ifndef _B2D_MATRIX3D_HXX
#include "matrix3d.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _B3D_HMATRIX_HXX
#include "hmatrix.hxx"
#endif

#ifndef _B3D_BASE3D_HXX
#include "base3d.hxx"
#endif

/*************************************************************************
|*
|* Hilfsfunktionen fuer Matrixinvertierung und Determinantenbestimmung
|*
\************************************************************************/

namespace binfilter {
BOOL Matrix3D::Ludcmp(UINT16 nIndex[], INT16& nParity)
{
    double fBig;
    double fTemp;
    double fStorage[3];
    double fSum;
    double fDum;
    UINT16 i,j,k,imax = 0;

    nParity = 1;

    // Ermittle das Maximum jeder Zeile. Falls eine Zeile
    // leer ist, breche ab. Matrix ist dann nicht invertierbar.
    for(i=0;i<3;i++)
    {
        fBig = 0.0;
        for(j=0;j<3;j++)
        {
            fTemp = fabs(M[i][j]);
            if(fTemp > fBig)
                fBig = fTemp;
        }
        if(fBig == 0.0)
            return FALSE;
        fStorage[i] = 1.0 / fBig;
    }
    // beginne mit dem normalisieren
    for(j=0;j<3;j++)
    {
        for(i=0;i<j;i++)
        {
            fSum = M[i][j];
            for(k=0;k<i;k++)
            {
                fSum -= M[i][k] * M[k][j];
            }
            M[i][j] = fSum;
        }
        fBig = 0.0;
        for(i=j;i<3;i++)
        {
            fSum = M[i][j];
            for(k=0L;k<j;k++)
            {
                fSum -= M[i][k] * M[k][j];
            }
            M[i][j] = fSum;
            fDum = fStorage[i] * fabs(fSum);
            if(fDum >= fBig)
            {
                fBig = fDum;
                imax = i;
            }
        }
        if(j != imax)
        {
            for(k=0;k<3;k++)
            {
                fDum = M[imax][k];
                M[imax][k] = M[j][k];
                M[j][k] = fDum;
            }
            nParity = -nParity;
            fStorage[imax] = fStorage[j];
        }
        nIndex[j] = imax;

        // here the failure of precision occurs
        if(fabs(M[j][j]) == 0.0)
            return FALSE;

        if(j != 2)
        {
            fDum = 1.0 / M[j][j];
            for(i=j+1;i<3;i++)
            {
                M[i][j] *= fDum;
            }
        }
    }
    return TRUE;
}

/*************************************************************************
|*
|* Hilfsfunktionen fuer Matrixinvertierung und Determinantenbestimmung
|*
\************************************************************************/

void Matrix3D::Lubksb(UINT16 nIndex[], Point3D& rPnt)
{
    UINT16 j,ip;
    INT16 i,ii = -1;
    double fSum;

    for(i=0;i<3;i++)
    {
        ip = nIndex[i];
        fSum = rPnt[ip];
        rPnt[ip] = rPnt[i];
        if(ii >= 0)
        {
            for(j=ii;j<i;j++)
            {
                fSum -= M[i][j] * rPnt[j];
            }
        }
        else if(fSum != 0.0)
        {
            ii = i;
        }
        rPnt[i] = fSum;
    }
    for(i=2;i>=0;i--)
    {
        fSum = rPnt[i];
        for(j=i+1;j<3;j++)
        {
            fSum -= M[i][j] * rPnt[j];
        }
        if(M[i][i] != 0.0)
            rPnt[i] = fSum / M[i][i];
    }
}

/*************************************************************************
|*
|* Einheitsmatrix herstellen
|*
\************************************************************************/

void Matrix3D::Identity(void)
{
    UINT16 i,j;

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(i!=j)
                M[i][j] = 0.0;
            else
                M[i][j] = 1.0;
        }
    }
}

/*************************************************************************
|*
|* Inverse Matrix bilden
|*
\************************************************************************/

BOOL Matrix3D::Invert()
{
    Matrix3D aWork = *this;
    UINT16 nIndex[3];
    INT16 nParity;
    UINT16 i;

    if(!aWork.Ludcmp(nIndex, nParity))
        return FALSE;

    Matrix3D aInverse;
    for(i=0;i<3;i++)
    {
        // Zeile expandieren
        aWork.Lubksb(nIndex, aInverse[i]);
    }
    // transponieren
    aInverse.Transpose();

    // kopieren
    *this = aInverse;

    return TRUE;
}

/*************************************************************************
|*
|* Testet, ob diese Matrix invertierbar ist
|*
\************************************************************************/

BOOL Matrix3D::IsInvertible()
{
    Matrix3D aWork = *this;
    UINT16 nIndex[3];
    INT16 nParity;
    return aWork.Ludcmp(nIndex, nParity);
}

/*************************************************************************
|*
|* Korrigiert die Matrix zu einer homogenen Matrix. Dazu werden
|* Nullen in die letzte Zeile und Spalte eingetragen und in die untere
|* rechte Ecke eine 1.0 gesetzt
|*
\************************************************************************/

void Matrix3D::Correct()
{
    M[0][2] = M[1][2] = 0.0;
    M[2][0] = M[2][1] = 0.0;
    M[2][2] = 1.0;
}

/*************************************************************************
|*
|* Liefert die Determinante dieser Matrix
|*
\************************************************************************/

double Matrix3D::Determinant()
{
    Matrix3D aWork = *this;
    UINT16 nIndex[3];
    INT16 nParity;
    UINT16 i;
    double fRetval = 0.0;

    if(aWork.Ludcmp(nIndex, nParity))
    {
        fRetval = (double)nParity;
        for(i=0;i<3;i++)
            fRetval *= aWork[i][i];
    }
    return fRetval;
}

/*************************************************************************
|*
|* Liefert den Trace dieser Matrix
|*
\************************************************************************/

double Matrix3D::Trace()
{
    double fTrace = 0.0;
    UINT16 i;

    for(i=0;i<3;i++)
    {
        fTrace += M[i][i];
    }
    return fTrace;
}

/*************************************************************************
|*
|* Transponiert diese Matrix
|*
\************************************************************************/

void Matrix3D::Transpose()
{
    UINT16 i,j;
    double fTemp;

    for(i=0;i<2;i++)
    {
        for(j=i+1;j<3;j++)
        {
            fTemp = M[i][j];
            M[i][j] = M[j][i];
            M[j][i] = fTemp;
        }
    }
}

/*************************************************************************
|*
|* Rotation mit Winkel (0.0 ... 2PI)
|*
\************************************************************************/

void Matrix3D::Rotate(double fAngle)
{
    Rotate(sin(fAngle),cos(fAngle));
}

/*************************************************************************
|*
|* Rotation mit Sin(),Cos()
|*
\************************************************************************/

void Matrix3D::Rotate(double fSin, double fCos )
{
    Matrix3D aTemp;
    aTemp.M[0][0] = aTemp.M[1][1] = fCos;
    aTemp.M[1][0] = fSin;
    aTemp.M[0][1] = -fSin;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Translationsmatrix aufbauen
|*
\************************************************************************/

void Matrix3D::Translate(double fX, double fY)
{
    Matrix3D aTemp;
    aTemp.M[0][2] = fX;
    aTemp.M[1][2] = fY;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Translationsmatrix aufbauen aus einem Vektor
|*
\************************************************************************/

void Matrix3D::Translate(const Vector2D& rVec)
{
    Translate(rVec.X(), rVec.Y());
}

/*************************************************************************
|*
|* Translationsmatrix nur in X
|*
\************************************************************************/

void Matrix3D::TranslateX(double fValue)
{
    Matrix3D aTemp;
    aTemp.M[0][2] = fValue;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Translationsmatrix nur in Y
|*
\************************************************************************/

void Matrix3D::TranslateY(double fValue)
{
    Matrix3D aTemp;
    aTemp.M[1][2] = fValue;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Skalierungsmatrix aufbauen
|*
\************************************************************************/

void Matrix3D::Scale(double fX, double fY)
{
    Matrix3D aTemp;
    aTemp.M[0][0] = fX;
    aTemp.M[1][1] = fY;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Skalierungsmatrix aufbauen aus Vektor
|*
\************************************************************************/

void Matrix3D::Scale(const Vector2D& rVec)
{
    Scale(rVec.X(), rVec.Y());
}

/*************************************************************************
|*
|* Skalierungsmatrix nur in X
|*
\************************************************************************/

void Matrix3D::ScaleX(double fFactor)
{
    Matrix3D aTemp;
    aTemp.M[0][0] = fFactor;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Skalierungsmatrix nur in Y
|*
\************************************************************************/

void Matrix3D::ScaleY(double fFactor)
{
    Matrix3D aTemp;
    aTemp.M[1][1] = fFactor;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Shearing-Matrix for X
|*
\************************************************************************/

void Matrix3D::ShearX(double fSx)
{
    Matrix3D aTemp;
    aTemp.M[0][1] = fSx;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Shearing-Matrix for Y
|*
\************************************************************************/

void Matrix3D::ShearY(double fSy)
{
    Matrix3D aTemp;
    aTemp.M[1][0] = fSy;
    *this *= aTemp;
}

/*************************************************************************
|*
|* Matrix normalisieren
|*
\************************************************************************/

void Matrix3D::Normalize()
{
    if(M[2][2] != 0.0 && M[2][2] != 1.0)
        for(UINT16 i=0;i<3;i++)
            for(UINT16 j=0;j<3;j++)
                M[i][j] /= M[2][2];
}

/*************************************************************************
|*
|* Matrixaddition
|*
\************************************************************************/

Matrix3D& Matrix3D::operator+= (const Matrix3D& rMat)
{
    for(UINT16 i=0;i<3;i++)
    {
        for(UINT16 j=0;j<3;j++)
        {
            M[i][j] += rMat[i][j];
        }
    }
    return *this;
}

Matrix3D Matrix3D::operator+ (const Matrix3D& rMat) const
{
    Matrix3D aSum = *this;
    aSum += rMat;
    return aSum;
}

/*************************************************************************
|*
|* Matrixsubtraktion
|*
\************************************************************************/

Matrix3D& Matrix3D::operator-= (const Matrix3D& rMat)
{
    for(UINT16 i=0;i<3;i++)
    {
        for(UINT16 j=0;j<3;j++)
        {
            M[i][j] -= rMat[i][j];
        }
    }
    return *this;
}

Matrix3D Matrix3D::operator- (const Matrix3D& rMat) const
{
    Matrix3D aSum = *this;
    aSum -= rMat;
    return aSum;
}

/*************************************************************************
|*
|* Vergleichsoperatoren
|*
\************************************************************************/

BOOL Matrix3D::operator== (const Matrix3D& rMat) const
{
    for(UINT16 i=0;i<3;i++)
    {
        for(UINT16 j=0;j<3;j++)
        {
            if(M[i][j] != rMat[i][j])
                return FALSE;
        }
    }
    return TRUE;
}

BOOL Matrix3D::operator!=(const Matrix3D& rMat) const
{
    for(UINT16 i=0;i<3;i++)
    {
        for(UINT16 j=0;j<3;j++)
        {
            if(M[i][j] != rMat[i][j])
                return TRUE;
        }
    }
    return FALSE;
}

/*************************************************************************
|*
|* Matrixmultiplikation mit einem Faktor
|*
\************************************************************************/

Matrix3D& Matrix3D::operator*= (double fFactor)
{
    for(UINT16 i=0;i<3;i++)
    {
        for(UINT16 j=0;j<3;j++)
        {
            M[i][j] *= fFactor;
        }
    }
    return *this;
}

Matrix3D Matrix3D::operator* (double fFactor) const
{
    Matrix3D aZwi = *this;
    aZwi *= fFactor;
    return aZwi;
}

/*************************************************************************
|*
|* Matrixdivision durch einen Faktor
|*
\************************************************************************/

Matrix3D& Matrix3D::operator/= (double fFactor)
{
    if(fFactor != 0.0)
    {
        for(UINT16 i=0;i<3;i++)
        {
            for(UINT16 j=0;j<3;j++)
            {
                M[i][j] /= fFactor;
            }
        }
    }
    return *this;
}

Matrix3D Matrix3D::operator/ (double fFactor) const
{
    Matrix3D aZwi = *this;
    aZwi /= fFactor;
    return aZwi;
}

/*************************************************************************
|*
|* Matrixmultiplikation von links, von rechts mittels umgekehrter
|* Parameterangaben zu erreichen
|*
\************************************************************************/

Matrix3D& Matrix3D::operator*= (const Matrix3D& rMat)
{
    // Matrixmultiplikation
    Matrix3D aCopy = *this;
    double fZwi;

    for(UINT16 i=0;i<3;i++)
    {
        for(UINT16 j=0;j<3;j++)
        {
            fZwi = 0.0;
            for(UINT16 k=0;k<3;k++)
            {
                fZwi += aCopy[k][j] * rMat[i][k];
            }
            M[i][j] = fZwi;
        }
    }
    return *this;
}

Matrix3D Matrix3D::operator* (const Matrix3D& rMat) const
{
    Matrix3D aZwi = rMat; // #112587#
    aZwi *= (*this);
    return aZwi;
}

/*************************************************************************
|*
|* Multiplikation Matrix, Punkt
|*
\************************************************************************/

Point3D operator* (const Matrix3D& rMatrix, const Point3D& rPnt)
{
    Point3D aNewPnt;
    UINT16 i,j;
    double fZwi;

    for(i=0;i<3;i++)
    {
        fZwi = 0.0;
        for(j=0;j<3;j++)
        {
            fZwi += rMatrix.M[i][j] * rPnt[j];
        }
        aNewPnt[i] = fZwi;
    }
    return aNewPnt;
}

/*************************************************************************
|*
|* Multiplikation Matrix, Vektor
|*
\************************************************************************/

Vector2D operator* (const Matrix3D& rMatrix, const Vector2D& rVec)
{
    Vector2D aNewVec;
    UINT16 i,j;
    double fZwi;

    for(i=0;i<2;i++)
    {
        fZwi = 0.0;
        for(j=0;j<2;j++)
        {
            fZwi += rMatrix.M[i][j] * rVec[j];
        }
        fZwi += rMatrix.M[i][2];
        aNewVec[i] = fZwi;
    }
    fZwi = rMatrix[2][0] * rVec[0]
         + rMatrix[2][1] * rVec[1]
         + rMatrix[2][2];
    if(fZwi != 1.0 && fZwi != 0.0)
    {
        aNewVec[0] /= fZwi;
        aNewVec[1] /= fZwi;
    }
    return aNewVec;
}

/*************************************************************************
|*
|* NUR die Rotation und Skalierung auf den Vektor anwenden!
|*
\************************************************************************/

void Matrix3D::RotateAndNormalize(Vector2D& rVec) const
{
    Vector2D aNewVec;
    UINT16 i,j;
    double fZwi;

    for(i=0;i<2;i++)
    {
        fZwi = 0.0;
        for(j=0;j<2;j++)
        {
            fZwi += M[i][j] * rVec[j];
        }
        aNewVec[i] = fZwi;
    }
    aNewVec.Normalize();
    rVec = aNewVec;
}

/*************************************************************************
|*
|* Stream-In-Operator fuer Matrix3D
|*
\************************************************************************/

SvStream& operator>>(SvStream& rIStream, Matrix3D& rMatrix3D)
{
    for (int i = 0; i < 3; i++)
        rIStream >> rMatrix3D.M[i];
    return rIStream;
}

/*************************************************************************
|*
|* Stream-Out-Operator fuer Matrix3D
|*
\************************************************************************/

SvStream& operator<<(SvStream& rOStream, const Matrix3D& rMatrix3D)
{
    for (int i = 0; i < 3; i++)
        rOStream << rMatrix3D.M[i];
    return rOStream;
}



/*************************************************************************
|*
|* Help routine to decompose given homogen 3x3 matrix to components. A correction of
|* the components is done to avoid inaccuracies.
|*
\************************************************************************/

BOOL Matrix3D::DecomposeAndCorrect(Vector2D& rScale,
    double& rShear, double& rRotate, Vector2D& rTranslate) const
{
    // break up homogen 3x3 matrix using homogen 4x4 matrix
    Matrix4D aDecomposeTrans(*this);
    Vector3D aScale;
    Vector3D aShear;
    Vector3D aRotate;
    Vector3D aTranslate;
    if(aDecomposeTrans.Decompose(aScale, aTranslate, aRotate, aShear))
    {
        const double fSmallValue(SMALL_DVALUE);

        // handle scale
        if(fabs(aScale.X() - 1.0) < fSmallValue)
            aScale.X() = 1.0;
        if(fabs(aScale.Y() - 1.0) < fSmallValue)
            aScale.Y() = 1.0;
        rScale.X() = aScale.X();
        rScale.Y() = aScale.Y();

        // handle shear
        if(fabs(aShear.X()) < fSmallValue)
            aShear.X() = 0.0;
        rShear = aShear.X();

        // handle rotate
        if(fabs(aRotate.Z()) < fSmallValue)
            aRotate.Z() = 0.0;
        rRotate = aRotate.Z();

        // handle translate
        if(fabs(aTranslate.X()) < fSmallValue)
            aTranslate.X() = 0.0;
        if(fabs(aTranslate.Y()) < fSmallValue)
            aTranslate.Y() = 0.0;
        rTranslate.X() = aTranslate.X();
        rTranslate.Y() = aTranslate.Y();

        return TRUE;
    }
    else
    {
        rScale.X() = rScale.Y() = 10000.0;
        rShear = rRotate = 0.0;
        rTranslate.X() = rTranslate.Y() = 0.0;

        return FALSE;
    }
}
}//end of namespace binfilter

// eof
