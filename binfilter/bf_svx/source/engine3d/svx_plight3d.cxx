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

#include "polyob3d.hxx"

#include "plight3d.hxx"
namespace binfilter {

/*N*/ TYPEINIT1(E3dPointLight, E3dLight);

/*************************************************************************
|*
|* E3dPointLight-Destruktor
|*
\************************************************************************/

/*N*/ E3dPointLight::~E3dPointLight()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/


/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen
|*
\************************************************************************/

/*N*/ bool E3dPointLight::CalcLighting(Color& rNewColor,
/*N*/                                    const Vector3D& rPnt,
/*N*/                                    const Vector3D& rPntNormal,
/*N*/                                    const Color& rPntColor)
/*N*/ {
/*N*/   double fR = 0, fG = 0, fB = 0;
/*N*/
/*N*/   if ( IsOn() )
/*N*/   {
/*N*/       double fLight;
/*N*/       Vector3D aPntToLight = GetTransPosition() - rPnt;
/*N*/
/*N*/       aPntToLight.Normalize();
/*N*/       fLight = rPntNormal.Scalar(aPntToLight);
/*N*/
/*N*/       if ( fLight > 0 )
/*N*/       {
/*N*/           fR = fLight * GetRed();
/*N*/           fG = fLight * GetGreen();
/*N*/           fB = fLight * GetBlue();
/*N*/       }
/*N*/   }
/*N*/   return ImpCalcLighting(rNewColor, rPntColor, fR, fG, fB);
/*N*/ }

/*************************************************************************
|*
|* Darstellung des Lichtobjekts in der Szene ein-/ausschalten
|*
\************************************************************************/

/*N*/ void E3dPointLight::CreateLightObj()
/*N*/ {
/*N*/   pSub->Clear();
/*N*/
/*N*/   if ( IsLightObjVisible() )
/*N*/   {
/*N*/       Vector3D aDiff(0.5,0,0);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/       aDiff = Vector3D(0,0.5,0);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/       aDiff = Vector3D(0,0,0.5);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/       aDiff = Vector3D(0.35,0.35,0.35);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/       aDiff = Vector3D(0.35,0.35,-0.35);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/       aDiff = Vector3D(-0.35,0.35,-0.35);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/       aDiff = Vector3D(-0.35,0.35,0.35);
/*N*/       Insert3DObj(new E3dPolyObj(GetPosition() - aDiff, GetPosition() + aDiff));
/*N*/   }
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
