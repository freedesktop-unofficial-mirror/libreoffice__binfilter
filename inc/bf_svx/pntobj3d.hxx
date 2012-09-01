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

#ifndef _E3D_PNTOBJ3D_HXX
#define _E3D_PNTOBJ3D_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/obj3d.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Klasse fuer einzelne dreidimensionale Punkte
|*
\************************************************************************/

class E3dPointObj : public E3dObject
{
 protected:
    Vector3D    aPosition;
    Vector3D    aTransPos;

    bool    bTransPosValid  : 1;

    virtual void SetTransformChanged();

 public:
    TYPEINFO();
    E3dPointObj(const Vector3D& rPos);
    E3dPointObj();

    using SdrAttrObj::operator=;


    virtual void SetPosition(const Vector3D& rNewPos);
    const Vector3D& GetPosition() const { return aPosition; }
    const Vector3D& GetTransPosition();

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

};

}//end of namespace binfilter
#endif          // _E3D_PNTOBJ3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
