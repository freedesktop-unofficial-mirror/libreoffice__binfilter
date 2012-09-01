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

#ifndef _E3D_DLIGHT3D_HXX
#define _E3D_DLIGHT3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/light3d.hxx>
namespace binfilter {

/*************************************************************************
|*
|* gerichtete Lichtquelle, aDirection zeigt ZUR Lichtquelle (also den
|* Lichtstrahlen entgegensetzt); die Position (geerbt von E3dLight) hat
|* auf die Lichtberechnung keinen Einfluss, sondern dient nur der
|* Anordnung in der Szene (fuer evtl. spaetere interaktive Bearbeitung)
|*
\************************************************************************/

class E3dDistantLight : public E3dLight
{
 protected:
    Vector3D aDirection;

    virtual void CreateLightObj();

 public:
    TYPEINFO();

    E3dDistantLight() :
        aDirection(Vector3D(0, 1, 0))
    {
    }

    virtual ~E3dDistantLight();

    using SdrAttrObj::operator=;

    virtual UINT16 GetObjIdentifier() const;

    virtual bool CalcLighting(Color& rNewColor,
                                  const Vector3D& rPnt,
                                  const Vector3D& rPntNormal,
                                  const Color& rPntColor);

    const Vector3D& GetDirection() const { return aDirection; }

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

};

}//end of namespace binfilter
#endif          // _E3D_DLIGHT3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
