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

#include "svdio.hxx"

#include "globl3d.hxx"

#include "polyob3d.hxx"

#include "dlight3d.hxx"

namespace binfilter {

/*N*/ TYPEINIT1(E3dDistantLight, E3dLight);

/*************************************************************************
|*
|* E3dDistantLight-Destruktor
|*
\************************************************************************/

/*N*/ E3dDistantLight::~E3dDistantLight()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dDistantLight::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_DISTLIGHT_ID;
/*N*/ }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen
|*
\************************************************************************/

/*?*/ bool E3dDistantLight::CalcLighting(Color& rNewColor,
/*?*/                                       const Vector3D& /*rPnt*/,
/*?*/                                       const Vector3D& rPntNormal,
/*?*/                                       const Color& rPntColor)
/*?*/ {
/*?*/   double fR = 0, fG = 0, fB = 0;
/*?*/
/*?*/   if ( IsOn() )
/*?*/   {
/*?*/       double fLight = rPntNormal.Scalar(aDirection);
/*?*/
/*?*/       if ( fLight > 0 )
/*?*/       {
/*?*/           fR = fLight * GetRed();
/*?*/           fG = fLight * GetGreen();
/*?*/           fB = fLight * GetBlue();
/*?*/       }
/*?*/   }
/*?*/   return ImpCalcLighting(rNewColor, rPntColor, fR, fG, fB);
/*?*/ }

/*************************************************************************
|*
|* Darstellung des Lichtobjekts in der Szene ein-/ausschalten
|*
\************************************************************************/

/*N*/ void E3dDistantLight::CreateLightObj()
/*N*/ {
/*N*/   pSub->Clear();
/*N*/
/*N*/   if ( IsLightObjVisible() )
/*N*/   {
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() + aDirection, GetPosition()));
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* laden
|*
\************************************************************************/

/*N*/ void E3dDistantLight::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       E3dLight::ReadData(rHead, rIn);
/*N*/
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dDistantLight");
/*N*/ #endif
/*N*/
/*N*/       rIn >> aDirection;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
