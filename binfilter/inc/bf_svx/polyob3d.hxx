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

#ifndef _E3D_POLYOB3D_HXX
#define _E3D_POLYOB3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/obj3d.hxx>
#include <bf_svx/poly3d.hxx>
namespace binfilter {

/*************************************************************************
|*
\************************************************************************/

class E3dPolyObj : public E3dObject
{
 protected:
    PolyPolygon3D   aPolyPoly3D;
    PolyPolygon3D   aPolyNormals3D;
    PolyPolygon3D   aPolyTexture3D;
    Vector3D        aNormal;

    BOOL    bDoubleSided : 1;
    BOOL    bBackSideVisible : 1;
    BOOL    bLighted : 1;
    BOOL    bOwnAttrs;
    BOOL    bOwnStyle;
    long    nObjectnumber;  // default ist -1;

    // [FG]: Zwecks schreiben des Formates der 3.1 Version
    //       Diese Funktionen werden nur von ReadData31
    //       aufgerufen.
    void ReadData31(const SdrObjIOHeader& rHead, SvStream& rIn);

public:
    TYPEINFO();
    E3dPolyObj(const PolyPolygon3D& rPoly3D, bool bDblSided = FALSE,
                                             bool bLight = TRUE);
    E3dPolyObj(const PolyPolygon3D& rPoly3D, const PolyPolygon3D& rVector3D,
                                             bool bDblSided = FALSE,
                                             bool bLight = TRUE);
    E3dPolyObj(const PolyPolygon3D& rPoly3D, const PolyPolygon3D& rVector3D,
                                             const PolyPolygon3D& rNormal3D,
                                             bool bDblSided = FALSE,
                                             bool bLight = TRUE);
    E3dPolyObj(const Vector3D& rP1, const Vector3D& rP2);
    E3dPolyObj();
    using SdrAttrObj::operator=;
    virtual ~E3dPolyObj();

    virtual UINT16  GetObjIdentifier() const;
    void SetPolyPolygon3D(const PolyPolygon3D& rNewPolyPoly3D);
    const PolyPolygon3D& GetPolyPolygon3D() const { return aPolyPoly3D; }

    void SetPolyNormals3D(const PolyPolygon3D& rNewPolyPoly3D);
    const PolyPolygon3D& GetPolyNormals3D() const { return aPolyNormals3D; }

    void SetPolyTexture3D(const PolyPolygon3D& rNewPolyPoly3D);
    const PolyPolygon3D& GetPolyTexture3D() const { return aPolyTexture3D; }

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".

    virtual const   Rectangle& GetBoundRect() const;

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    virtual SdrObjGeoData *NewGeoData() const;
    virtual void          SaveGeoData(SdrObjGeoData &rGeo) const;
    virtual void          RestGeoData(const SdrObjGeoData &rGeo);
    virtual void          SetPage(SdrPage *pNewPage);
    virtual void          SetModel(SdrModel *pNewModel);
    using SdrObject::GetLayer;
    virtual SdrLayerID    GetLayer() const;
    virtual void          NbcSetLayer(SdrLayerID nLayer);
    virtual SfxStyleSheet *GetStyleSheet() const;

    BOOL OwnAttrs() const { return bOwnAttrs; }
    BOOL &OwnAttrs() { return bOwnAttrs; }
    BOOL OwnStyle() const { return bOwnStyle; }
    BOOL &OwnStyle() { return bOwnStyle; }

    BOOL DoubleSided () const { return bDoubleSided; }
    void SetDoubleSided (BOOL bNewDoubleSided) { bDoubleSided = bNewDoubleSided; }

    long  GetObjectnumber () const { return nObjectnumber; }
    void  SetObjectnumber (long value) { nObjectnumber = value; }

    const Vector3D& GetNormal() { return aNormal; }
};

}//end of namespace binfilter
#endif          // _E3D_POLYOB3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
