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

#include "matrix3d.hxx"
namespace binfilter {

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


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
