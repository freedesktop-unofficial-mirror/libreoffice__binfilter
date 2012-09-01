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

#include "globl3d.hxx"
#include "polysc3d.hxx"
#include "dlight3d.hxx"
#include "plight3d.hxx"
#include "polyob3d.hxx"
#include "cube3d.hxx"
#include "sphere3d.hxx"
#include "extrud3d.hxx"
#include "lathe3d.hxx"
#include "polygn3d.hxx"
#include "objfac3d.hxx"

namespace binfilter {

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ E3dObjFactory::E3dObjFactory()
/*N*/ {
/*N*/   SdrObjFactory::InsertMakeObjectHdl(LINK(this, E3dObjFactory, MakeObject));
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dObjFactory::~E3dObjFactory()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Chart-interne Objekte erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK( E3dObjFactory, MakeObject, SdrObjFactory*, pObjFactory)
/*N*/ {
/*N*/   if ( pObjFactory->nInventor == E3dInventor )
/*N*/   {
/*N*/       switch ( pObjFactory->nIdentifier )
/*N*/       {
/*N*/           case E3D_POLYSCENE_ID:
/*N*/               pObjFactory->pNewObj = new E3dPolyScene();
/*N*/               break;
/*N*/           case E3D_LIGHT_ID:
/*N*/               pObjFactory->pNewObj = new E3dLight();
/*N*/               break;
/*N*/           case E3D_DISTLIGHT_ID:
/*N*/               pObjFactory->pNewObj = new E3dDistantLight();
/*N*/               break;
/*N*/           case E3D_POINTLIGHT_ID:
/*N*/               pObjFactory->pNewObj = new E3dPointLight();
/*N*/               break;
/*N*/           case E3D_SPOTLIGHT_ID:
/*N*/               break;
/*N*/           case E3D_OBJECT_ID:
/*N*/               pObjFactory->pNewObj = new E3dObject();
/*N*/               break;
/*N*/           case E3D_POLYOBJ_ID :
/*N*/               pObjFactory->pNewObj = new E3dPolyObj();
/*N*/               break;
/*N*/           case E3D_POLYGONOBJ_ID  :
/*N*/               pObjFactory->pNewObj = new E3dPolygonObj();
/*N*/               break;
/*N*/           case E3D_CUBEOBJ_ID :
/*N*/               pObjFactory->pNewObj = new E3dCubeObj();
/*N*/               break;
/*N*/           case E3D_SPHEREOBJ_ID:
/*N*/                   // FG: ruft den dummy constructor, da dieser Aufruf nur beim Laden von Dokumenten erfolgt.
/*N*/                   //     die wirkliche Anzahkl Segmente wird aber erst nach dem Laden der Member festgelegt.
/*N*/                   //     dies hat zur Folge das die erste Kugel gleich wieder zerstoert wird, obwohl sie nie
/*N*/                   //     gebraucht worden ist.
/*N*/               pObjFactory->pNewObj = new E3dSphereObj(123);
/*N*/               break;
/*N*/           case E3D_POINTOBJ_ID:
/*N*/               pObjFactory->pNewObj = new E3dPointObj();
/*N*/               break;
/*N*/           case E3D_EXTRUDEOBJ_ID:
/*N*/               pObjFactory->pNewObj = new E3dExtrudeObj();
/*N*/               break;
/*N*/           case E3D_LATHEOBJ_ID:
/*N*/               pObjFactory->pNewObj = new E3dLatheObj();
/*N*/               break;
/*N*/           case E3D_LABELOBJ_ID:
/*N*/               pObjFactory->pNewObj = new E3dLabelObj();
/*N*/               break;
/*N*/           case E3D_COMPOUNDOBJ_ID:
/*N*/               pObjFactory->pNewObj = new E3dCompoundObject();
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/   return 0;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
