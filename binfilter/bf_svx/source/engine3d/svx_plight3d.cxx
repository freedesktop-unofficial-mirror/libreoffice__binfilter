/*************************************************************************
 *
 *  $RCSfile: svx_plight3d.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:46 $
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

#ifndef _SVDPAGE_HXX
#include "svdpage.hxx"
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_POLYOB3D_HXX
#include "polyob3d.hxx"
#endif

#ifndef _E3D_PLIGHT3D_HXX
#include "plight3d.hxx"
#endif

/*N*/ TYPEINIT1(E3dPointLight, E3dLight);

/*************************************************************************
|*
|* E3dPointLight-Konstruktor
|*
\************************************************************************/

/*N*/ E3dPointLight::E3dPointLight(const Vector3D& rPos, const Color& rColor,
/*N*/                            double fLightIntensity) :
/*N*/   E3dLight(rPos, rColor, fLightIntensity)
/*N*/ {
/*N*/   CreateLightObj();
/*N*/ }

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

//STRIP001 UINT16 E3dPointLight::GetObjIdentifier() const
//STRIP001 {
//STRIP001  return E3D_POINTLIGHT_ID;
//STRIP001 }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen
|*
\************************************************************************/

/*N*/ FASTBOOL E3dPointLight::CalcLighting(Color& rNewColor,
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



