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

#ifndef _CHTSCENE_HXX
#define _CHTSCENE_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/polysc3d.hxx>
#include <chtmodel.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Basisklasse fuer 3D-Szenen
|* Die Ableitung von SchObjGroup erfolgt damit das Chart frei plaziert
|* werden kann. Die Komponenten von 2d-Charts sind auch SchObjGroups
|*
\************************************************************************/

class ChartScene : public E3dPolyScene
{
  protected:
    ChartModel* pDoc;
    BOOL        bAskForLogicRect;
    Rectangle   Get3DDescrRect(E3dLabelObj *p3DObj,B3dCamera& rCamSet);

  public:

    TYPEINFO();
    ChartScene(ChartModel* pModel);
    virtual ~ChartScene();

    using SdrAttrObj::operator=;

    void Initialize();

    virtual Volume3D FitInSnapRect();

    BOOL GetAskForLogicRect() {return bAskForLogicRect;}
    void SetAskForLogicRect(BOOL value) {bAskForLogicRect = value;}

    void InsertAllTitleText (DescrList         &rList,
                             E3dObject         *pGroup,
                             long              nAxisId);

    void ReduceDescrList(DescrList& aList);
};


} //namespace binfilter
#endif          // _E3D_SCENE3D_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
