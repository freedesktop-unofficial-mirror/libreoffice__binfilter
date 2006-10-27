/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_dlight3d.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:48:06 $
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

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_POLYOB3D_HXX
#include "polyob3d.hxx"
#endif

#ifndef _E3D_DLIGHT3D_HXX
#include "dlight3d.hxx"
#endif

namespace binfilter {

/*N*/ TYPEINIT1(E3dDistantLight, E3dLight);

/*************************************************************************
|*
|* E3dDistantLight-Konstruktor
|*
\************************************************************************/

/*N*/ E3dDistantLight::E3dDistantLight(const Vector3D& rPos, const Vector3D& rDir,
/*N*/                                const Color& rColor, double fLightIntensity) :
/*N*/   E3dLight(rPos, rColor, fLightIntensity)
/*N*/ {
/*N*/   SetDirection(rDir);
/*N*/   CreateLightObj();
/*N*/ }

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
|* Richtung ZUR Lichtquelle setzen
|*
\************************************************************************/

/*N*/ void E3dDistantLight::SetDirection(const Vector3D& rNewDir)
/*N*/ {
/*N*/   if ( aDirection != rNewDir )
/*N*/   {
/*N*/       aDirection = rNewDir;
/*N*/       aDirection.Normalize();
/*N*/       CreateLightObj();
/*N*/       StructureChanged(this);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen
|*
\************************************************************************/

/*?*/ FASTBOOL E3dDistantLight::CalcLighting(Color& rNewColor,
/*?*/                                       const Vector3D& rPnt,
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
|* sichern
|*
\************************************************************************/

/*N*/ void E3dDistantLight::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   E3dLight::WriteData(rOut);
/*N*/
/*N*/ #ifdef E3D_STREAMING
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dDistantLight");
/*N*/ #endif
/*N*/
/*N*/   rOut << aDirection;
/*N*/ #endif
/*N*/ #endif    // #ifndef SVX_LIGHT
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
