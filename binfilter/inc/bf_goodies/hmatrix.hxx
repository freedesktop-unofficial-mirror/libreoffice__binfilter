/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hmatrix.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:22:29 $
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

#ifndef _B3D_HMATRIX_HXX
#define _B3D_HMATRIX_HXX

#ifndef _B3D_POINT4D_HXX
#include "point4d.hxx"
#endif

namespace binfilter {

//////////////////////////////////////////////////////////////////////////
// external declarations
class Matrix3D;

/*************************************************************************
|*
|* homogene 4x4 matrix
|*
\************************************************************************/

class Matrix4D
{
private:
    // Hilfsfunktionen fuer Matrixinvertierung und Determinantenbestimmung
    BOOL Ludcmp(UINT16 nIndex[], INT16& nParity);
    void Lubksb(UINT16 nIndex[], Point4D& aVec);

protected:
    Point4D     M[4];

public:
    // default: Einheitsmatrix erstellen (Vektoren sind auf 0
    // initialisiert, der recte Spaltenvektor auf 1)
    Matrix4D() { M[0][0] = M[1][1] = M[2][2] = 1.0;
                 M[0][3] = M[1][3] = M[2][3] = 0.0; }

    // constructor using homogen 3x3 matrix
    Matrix4D(const Matrix3D& rMat);

    // set to given homogen 3x3 matrix
    //void SetMatrix(const Matrix3D& rMat);

    // Zeilenvektor zurueckgeben
    Point4D& operator[](int nPos) { return M[nPos]; }
    const Point4D& operator[](int nPos) const { return M[nPos]; }

    // Spaltenvektor zurueckgeben
    Point4D GetColumnVector(int nCol) const
        { return Point4D(M[0][nCol], M[1][nCol], M[2][nCol], M[3][nCol]); }

    // Auf Einheitsmatrix zuruecksetzen
    void Identity(void);

    // Invertierung
    BOOL Invert();

    // Zerlegung
    BOOL Decompose(Vector3D& rScale, Vector3D& rTranslate, Vector3D& rRotate, Vector3D& rShear) const;

    // Determinante
    double Determinant();

    // Transpose
    void Transpose();

    // Rotation
    void RotateX(double fAngle);
    void RotateY(double fAngle);
    void RotateZ(double fAngle);
    void RotateX(double fSin, double fCos );
    void RotateY(double fSin, double fCos );
    void RotateZ(double fSin, double fCos );

    // Translation
    void Translate(double fX, double fY, double fZ );
    void Translate(const Vector3D& aTrans);
    void TranslateZ(double fValue);

    // Skalierung
    void Scale(double fX, double fY, double fZ);
    void Scale(const Vector3D& aScale);

    // ModelViewMatrix (ViewOrientationMatrix) fuer die Umwandlung
    // ObjectCoordinates in EyeCoordinates
#if defined( ICC ) || defined( GCC )
    void Orientation(Point4D aVRP = Point4D(0.0,0.0,1.0),
        Vector3D aVPN = Vector3D(0.0,0.0,1.0),
        Vector3D aVUP = Vector3D(0.0,1.0,0.0));
#else
    void Orientation(Point4D& aVRP = Point4D(0.0,0.0,1.0),
        Vector3D& aVPN = Vector3D(0.0,0.0,1.0),
        Vector3D& aVUP = Vector3D(0.0,1.0,0.0));
#endif
    // Projektionsmatritzen fuer die Umwandlung von EyeCoordinates
    // auf ClipCoordinates
    void Frustum(double fLeft = -1.0, double fRight = 1.0,
        double fBottom = -1.0, double fTop = 1.0,
        double fNear = 0.001, double fFar = 1.0);
    void Ortho(double fLeft = -1.0, double fRight = 1.0,
        double fBottom = -1.0, double fTop = 1.0,
        double fNear = 0.0, double fFar = 1.0);

    // Addition, Subtraktion
    Matrix4D&   operator+=  (const Matrix4D&);
    Matrix4D&   operator-=  (const Matrix4D&);
    Matrix4D    operator+   (const Matrix4D&) const;
    Matrix4D    operator-   (const Matrix4D&) const;

    // Vergleichsoperatoren
    BOOL        operator==  (const Matrix4D&) const;
    BOOL        operator!=  (const Matrix4D&) const;

    // Multiplikation, Division mit Konstante
    Matrix4D&   operator*=  (double);
    Matrix4D    operator*   (double) const;
    Matrix4D&   operator/=  (double);
    Matrix4D    operator/   (double) const;

    // Matritzenmultiplikation von links auf die lokale
    Matrix4D&   operator*=  (const Matrix4D&);
    Matrix4D    operator*   (const Matrix4D&) const;

    // Operatoren zur Punkttransformation
    friend Point4D  operator*   (const Matrix4D&, const Point4D&);
    friend Point4D& operator*=  (Point4D& rPnt, const Matrix4D& rMat)
        { return (rPnt = rMat * rPnt); }

    // Operatoren zur Vektortransformation
    friend Vector3D     operator*   (const Matrix4D&, const Vector3D&);
    friend Vector3D&    operator*=  (Vector3D& rVec, const Matrix4D& rMat)
        { return (rVec = rMat * rVec); }

    // NUR die Rotation und Skalierung auf den Vektor anwenden!
    void RotateAndNormalize(Vector3D& rVec) const;

    // Streamoperatoren
    friend SvStream& operator>>(SvStream& rIStream, Matrix4D&);
    friend SvStream& operator<<(SvStream& rOStream, const Matrix4D&);
};
}//end of namespace binfilter


#endif          // _B3D_HMATRIX_HXX
