/*************************************************************************
 *
 *  $RCSfile: svx_class3d.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:45 $
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

#ifndef _E3D_GLOBL3D_HXX
#include <globl3d.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _SVX_MATRIX3D_HXX
#include "matrix3d.hxx"
#endif

/*************************************************************************
|*
|* Cast-Operator auf homogene 4x4 Matrix
|*
\************************************************************************/

/*N*/ Old_Matrix3D::operator Matrix4D()
/*N*/ {
/*N*/   Matrix4D aNewMat;
/*N*/
/*N*/   aNewMat[0] = Point4D(M[0], aTranslation[0]);
/*N*/   aNewMat[1] = Point4D(M[1], aTranslation[1]);
/*N*/   aNewMat[2] = Point4D(M[2], aTranslation[2]);
/*N*/
/*N*/   return aNewMat;
/*N*/ }

/*************************************************************************
|*
|* Zuweisungs-Operator mit homogener 4x4 Matrix
|*
\************************************************************************/

/*N*/ Old_Matrix3D Old_Matrix3D::operator=(const Matrix4D& rMat)
/*N*/ {
/*N*/   M[0] = Vector3D(rMat[0][0], rMat[0][1], rMat[0][2]);
/*N*/   M[1] = Vector3D(rMat[1][0], rMat[1][1], rMat[1][2]);
/*N*/   M[2] = Vector3D(rMat[2][0], rMat[2][1], rMat[2][2]);
/*N*/   aTranslation = Vector3D(rMat[0][3], rMat[1][3], rMat[2][3]);
/*N*/
/*N*/   return *this;
/*N*/ }

/*************************************************************************
|*
|* Stream-In-Operator fuer Matrix3D
|*
\************************************************************************/

/*N*/ SvStream& operator>>(SvStream& rIStream, Old_Matrix3D& rMatrix3D)
/*N*/ {
/*N*/   for (int i = 0; i < 3; i++)
/*N*/       rIStream >> rMatrix3D.M[i];
/*N*/
/*N*/   rIStream >> rMatrix3D.aTranslation;
/*N*/
/*N*/   return rIStream;
/*N*/ }

/*************************************************************************
|*
|* Stream-Out-Operator fuer Matrix3D
|*
\************************************************************************/

/*N*/ SvStream& operator<<(SvStream& rOStream, const Old_Matrix3D& rMatrix3D)
/*N*/ {
/*N*/   for (int i = 0; i < 3; i++)
/*N*/       rOStream << rMatrix3D.M[i];
/*N*/
/*N*/   rOStream << rMatrix3D.aTranslation;
/*N*/
/*N*/   return rOStream;
/*N*/ }


