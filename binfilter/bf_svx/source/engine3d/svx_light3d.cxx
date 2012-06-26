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

#include "light3d.hxx"

namespace binfilter {

/*N*/ TYPEINIT1(E3dLight, E3dPointObj);

/*N*/ E3dLight::E3dLight() :
/*N*/   E3dPointObj(Vector3D()),
/*N*/   aColor(255, 255, 255),
/*N*/   fIntensity(1.0),
/*N*/   fRed(1.0),
/*N*/   fGreen(1.0),
/*N*/   fBlue(1.0),
/*N*/   bOn(TRUE),
/*N*/   bVisible(FALSE)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* protected, daher kein Einfuegen von Objekten von aussen moeglich
|*
\************************************************************************/

/*N*/ void E3dLight::Insert3DObj(E3dObject* p3DObj)
/*N*/ {
/*N*/ //    E3dPointObj::Insert3DObj(p3DObj);
/*N*/   GetSubList()->InsertObject(p3DObj);
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dLight::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_LIGHT_ID;
/*N*/ }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen; Return = TRUE bedeutet, dass die maximale
|* Farbintensitaet aller Farbanteile erreicht ist.
|*
\************************************************************************/

/*N*/ bool E3dLight::ImpCalcLighting(Color& rNewColor, const Color& rPntColor,
/*N*/                                   double fR, double fG, double fB) const
/*N*/ {
/*N*/   ULONG   nR(rNewColor.GetRed()),
/*N*/           nG(rNewColor.GetGreen()),
/*N*/           nB(rNewColor.GetBlue());
/*N*/   ULONG   nPntR(rPntColor.GetRed()),
/*N*/           nPntG(rPntColor.GetGreen()),
/*N*/           nPntB(rPntColor.GetBlue());
/*N*/
/*N*/   if ( bOn )
/*N*/   {
/*N*/       nR += (ULONG) (fR * nPntR);
/*N*/       nG += (ULONG) (fG * nPntG);
/*N*/       nB += (ULONG) (fB * nPntB);
/*N*/
/*N*/       nR = Min(nR, nPntR);
/*N*/       nG = Min(nG, nPntG);
/*N*/       nB = Min(nB, nPntB);
/*N*/
/*N*/       rNewColor.SetRed((USHORT) nR);
/*N*/       rNewColor.SetGreen((USHORT) nG);
/*N*/       rNewColor.SetBlue((USHORT) nB);
/*N*/   }
/*N*/   return ( nR == nPntR && nG == nPntG && nB == nPntB );
/*N*/ }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen
|*
\************************************************************************/

/*N*/ bool E3dLight::CalcLighting(Color& rNewColor,
/*N*/                               const Vector3D& /*rPnt*/,
/*N*/                               const Vector3D& /*rPntNormal*/,
/*N*/                               const Color& rPntColor)
/*N*/ {
/*N*/   return ImpCalcLighting(rNewColor, rPntColor, fRed, fGreen, fBlue);
/*N*/ }

/*************************************************************************
|*
|* neue Position setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dLight::SetPosition(const Vector3D& rNewPos)
/*N*/ {
/*N*/   E3dPointObj::SetPosition(rNewPos);
/*N*/   CreateLightObj();
/*N*/ }

/*************************************************************************
|*
|* neue Intensitaet setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dLight::SetIntensity(double fNew)
/*N*/ {
/*N*/   if ( fIntensity != fNew )
/*N*/   {
/*N*/       fIntensity = fNew;
/*N*/       StructureChanged(this);
/*N*/       SetColor(aColor);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* neue Farbe setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dLight::SetColor(const Color& rNewColor)
/*N*/ {
/*N*/   if ( aColor != rNewColor )
/*N*/   {
/*N*/       aColor = rNewColor;
/*N*/       StructureChanged(this);
/*N*/   }
/*N*/
/*N*/   fRed    = fIntensity * aColor.GetRed()   / 255;
/*N*/   fGreen  = fIntensity * aColor.GetGreen() / 255;
/*N*/   fBlue   = fIntensity * aColor.GetBlue()  / 255;
/*N*/ }

/*************************************************************************
|*
|* Lichtquelle ein-/ausschalten und Aenderung an Parents (Szene) melden
|*
\************************************************************************/


/*************************************************************************
|*
|* Darstellung des Lichtobjekts in der Szene ein-/ausschalten
|*
\************************************************************************/


/*************************************************************************
|*
|* Darstellung des Lichtobjekts in der Szene ein-/ausschalten
|*
\************************************************************************/

/*N*/ void E3dLight::CreateLightObj()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* laden
|*
\************************************************************************/

/*N*/ void E3dLight::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       E3dPointObj::ReadData(rHead, rIn);
/*N*/
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dLight");
/*N*/ #endif
/*N*/
/*N*/       BOOL bTmp;
/*N*/
/*N*/       rIn >> aColor;
/*N*/       rIn >> fIntensity;
/*N*/       rIn >> fRed;
/*N*/       rIn >> fGreen;
/*N*/       rIn >> fBlue;
/*N*/       rIn >> bTmp; bOn = bTmp;
/*N*/       rIn >> bTmp; bVisible = bTmp;
/*N*/   }
/*N*/ }

/*N*/ void E3dLight::SetStyleSheet(SfxStyleSheet* /*pNewStyleSheet*/, bool /*bDontRemoveHardAttr*/)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Attribute abfragen
|*
\************************************************************************/

/*N*/ SfxStyleSheet*E3dLight::GetStyleSheet() const
/*N*/ {
/*N*/   return 0;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
