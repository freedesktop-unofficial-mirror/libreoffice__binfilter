/*************************************************************************
 *
 *  $RCSfile: matrix3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:07 $
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

#ifndef _SVX_MATRIX3D_HXX
#define _SVX_MATRIX3D_HXX

#ifndef _B3D_HMATRIX_HXX
#include <goodies/hmatrix.hxx>
#endif

#ifndef _SVX_VECTOR3D_HXX
#include <goodies/vector3d.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* 3D-Transformationsmatrix, bestehend aus 3 Zeilenvektoren und
|* einem Spaltenvektor, der die Translation enthaelt:
|*
|*      |V11 V12 V13 T1|
|*  M = |V21 V22 C33 T2|
|*      |V31 V32 V33 T3|
|*
|* Vektortransformation durch Postmultiplikation mit Spaltenvektoren:
|* V' = M * V
|* Matrixverkettung per Postmultiplikation mit Transformation oder
|* anderer Matrix:
|* M' = [T,S,Rxyz] * M oder
|* M' = M2 * M
|*
\************************************************************************/

class Old_Matrix3D
{
protected:
    Vector3D                    M[3];
    Vector3D                    aTranslation;

 public:
    // default: Einheitsmatrix erstellen (Vektoren sind auf 0 initialisiert)
    Old_Matrix3D() { M[0][0] = M[1][1] = M[2][2] = 1; }

    // Zeilenvektor zurueckgeben
    Vector3D& operator[](int nPos) { return M[nPos]; }
    const Vector3D& operator[](int nPos) const { return M[nPos]; }

    // Spaltenvektor zurueckgeben
    Vector3D GetColumnVector(int nCol) const
        { return Vector3D(M[0][nCol], M[1][nCol], M[2][nCol]); }

    friend SvStream& operator>>(SvStream& rIStream, Old_Matrix3D&);
    friend SvStream& operator<<(SvStream& rOStream, const Old_Matrix3D&);

    operator Matrix4D();
    Old_Matrix3D operator=(const Matrix4D&);
};

}//end of namespace binfilter
#endif
