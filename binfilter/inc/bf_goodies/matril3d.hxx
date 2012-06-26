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

#ifndef _B3D_MATRIL3D_HXX
#define _B3D_MATRIL3D_HXX

#include <bf_svtools/bf_solar.h>


#include "bucket.hxx"

#include <tools/color.hxx>

#include <tools/stream.hxx>

namespace binfilter {

/*************************************************************************
|*
|* Moegliche MaterialModes fuer Polygone
|*
\************************************************************************/

enum Base3DMaterialMode
{
    Base3DMaterialFront = 0,
    Base3DMaterialBack,
    Base3DMaterialFrontAndBack
};

/*************************************************************************
|*
|* Moegliche MaterialValues fuer Polygone
|*
\************************************************************************/

enum Base3DMaterialValue
{
    Base3DMaterialAmbient = 0,
    Base3DMaterialDiffuse,
    Base3DMaterialSpecular,
    Base3DMaterialEmission
};

/*************************************************************************
|*
|* Basisklasse fuer Materialparameter
|*
\************************************************************************/

class B3dMaterial
{
private:
    Color                   aAmbient;
    Color                   aDiffuse;
    Color                   aSpecular;
    Color                   aEmission;
    UINT16                  nExponent;

public:
    B3dMaterial();

    virtual ~B3dMaterial() {}

    // Laden/Speichern in StarView
    virtual void ReadData(SvStream& rIn);

    // Vergleichsoperator
    BOOL operator==(const B3dMaterial&);
    BOOL operator!=(const B3dMaterial& rMat) { return (!((*this) == rMat)); }
};

}//end of namespace binfilter

#endif          // _B3D_MATRIL3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
