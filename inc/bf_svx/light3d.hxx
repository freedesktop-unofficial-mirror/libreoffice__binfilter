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

#ifndef _E3D_LIGHT3D_HXX
#define _E3D_LIGHT3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/pntobj3d.hxx>

namespace binfilter {

/*************************************************************************
|*
|* Basisklasse fuer alle Lichtquellen, gleichzeitig als ambiente
|* (ungerichtete) Lichtquelle zu verwenden. D.h., die Position dient
|* nur der Verwaltung, hat aber keinen Einfluss auf die Beleuchtung.
|*
\************************************************************************/

class E3dLight : public E3dPointObj
{
 private:
    Color       aColor;
    double      fIntensity;
    double      fRed, fGreen, fBlue;

    bool    bOn             : 1;
    bool    bVisible        : 1;

 protected:
    bool ImpCalcLighting(Color& rNewColor, const Color& rPntColor,
                             double fR, double fG, double fB) const;
    // Lichtquellen koennen Unterobjekte nur selbst anlegen
    virtual void Insert3DObj(E3dObject* p3DObj);

    virtual void CreateLightObj();

 public:
    TYPEINFO();
    E3dLight();

    using SdrAttrObj::operator=;

    virtual UINT16 GetObjIdentifier() const;

    virtual bool CalcLighting(Color& rNewColor,
                                  const Vector3D& rPnt,
                                  const Vector3D& rPntNormal,
                                  const Color& rPntColor);

    virtual void SetPosition(const Vector3D& rNewPos);

    double GetIntensity() const { return fIntensity; }
    virtual void SetIntensity(double fNew);

    const Color& GetColor() const { return aColor; }
    virtual void SetColor(const Color& rNewColor);

    bool IsOn() const { return bOn; }

    bool IsLightObjVisible() const { return bVisible; }

    double GetRed() const   { return fRed; }
    double GetGreen() const { return fGreen; }
    double GetBlue() const  { return fBlue; }

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    virtual void           SetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);
    virtual SfxStyleSheet* GetStyleSheet() const;
};

}//end of namespace binfilter
#endif          // _E3D_LIGHT3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
