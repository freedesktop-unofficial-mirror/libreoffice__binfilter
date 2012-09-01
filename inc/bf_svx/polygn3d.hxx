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

#ifndef _E3D_POLYGON3D_HXX
#define _E3D_POLYGON3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/obj3d.hxx>

#include <bf_svx/poly3d.hxx>
namespace binfilter {

class E3dPolygonObj : public E3dCompoundObject
{
private:
    // Parameter
    PolyPolygon3D   aPolyPoly3D;
    PolyPolygon3D   aPolyNormals3D;
    PolyPolygon3D   aPolyTexture3D;
    BOOL            bLineOnly;

    void CreateDefaultNormals();
    void CreateDefaultTexture();

public:
    void SetPolyPolygon3D(const PolyPolygon3D& rNewPolyPoly3D);
    void SetPolyNormals3D(const PolyPolygon3D& rNewPolyPoly3D);
    void SetPolyTexture3D(const PolyPolygon3D& rNewPolyPoly3D);

    TYPEINFO();

    E3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        BOOL bLinOnly=FALSE);
    E3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D, BOOL bLinOnly=FALSE);
    E3dPolygonObj(E3dDefaultAttributes& rDefault, const Vector3D& rP1,
        const Vector3D& rP2, BOOL bLinOnly=TRUE);

    E3dPolygonObj();
    virtual ~E3dPolygonObj();

    using SdrAttrObj::operator=;

    const PolyPolygon3D& GetPolyPolygon3D() const { return aPolyPoly3D; }
    const PolyPolygon3D& GetPolyNormals3D() const { return aPolyNormals3D; }
    const PolyPolygon3D& GetPolyTexture3D() const { return aPolyTexture3D; }

    virtual UINT16 GetObjIdentifier() const;

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // LineOnly?
    BOOL GetLineOnly() { return bLineOnly; }
};

}//end of namespace binfilter
#endif          // _E3D_POLYGON3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
