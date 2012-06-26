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

#ifndef _E3D_SPHERE3D_HXX
#define _E3D_SPHERE3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/obj3d.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Kugelobjekt mit Durchmesser r3DSize; Anzahl der Flaechen wird durch
|* die horizontale und vertikale Segmentanzahl vorgegeben
|*
\************************************************************************/

class E3dSphereObj : public E3dCompoundObject
{
    Vector3D        aCenter;
    Vector3D        aSize;

protected:
    void SetDefaultAttributes(E3dDefaultAttributes& rDefault);

public:
    TYPEINFO();

    using SdrAttrObj::operator=;

    // HorizontalSegments:
    sal_Int32 GetHorizontalSegments() const
        { return ((const Svx3DHorizontalSegmentsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_HORZ_SEGS)).GetValue(); }

    // VerticalSegments:
    sal_Int32 GetVerticalSegments() const
        { return ((const Svx3DVerticalSegmentsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_VERT_SEGS)).GetValue(); }


    virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    const Vector3D Center() const { return aCenter; }
    const Vector3D Size() const { return aSize; }

    // FG: Dieser Konstruktor wird nur von MakeObject aus der 3d-Objectfactory beim
    //     Laden von Dokumenten mit Kugeln aufgerufen. Dieser Konstruktor ruft kein
    //     CreateSphere auf, er erzeugt also keine Kugel.
    E3dSphereObj(int dummy);

    // FG: Liest die Kugel im Format der Version 31 ein. Diese Funktion wurde aus
    //     Gruenden der Uebersichtlichkeit ausgelagert.
    void ReadData31(const SdrObjIOHeader& rHead, SvStream& rIn);

    // Geometrieerzeugung
    virtual void CreateGeometry();

    // Give out simple line geometry
    virtual void GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const;

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void PostItemChange(const sal_uInt16 nWhich);

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".
};

}//end of namespace binfilter
#endif          // _E3D_SPHERE3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
