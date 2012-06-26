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

#ifndef _SCH_SCHGROUP_HXX
#define _SCH_SCHGROUP_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdogrp.hxx>

#include "chtmodel.hxx"
namespace binfilter {

/************************************************************************/

class SchObjGroup : public SdrObjGroup
{
 public:
    enum ChartGroupTypeNames {LEGEND, DIAGRAM, NOTHING};

 private:
    SdrObjTransformInfoRec aInfo;
    ChartGroupTypeNames eChartGroupType;  // FG: 11.3.97 Wird einfach auf TRUE gesetzt falls es
                                   //     das Chart selbst ist. Das muss beim Resize anders
                                   //     behandelt werden
    ChartModel *pChartmodel;       // Auch das ist nur fuer das Resize wichtig, um dort
                                   // CreateChart() aufzurufen;

    BOOL bAskForLogicRect;         // Da die Groesse eines Gruppenobjektes durch die
                                   // Mitlgieder berechnet wird, hilft ein Resize der Gruppe nichts.
                                   // Bei BuildChart muss eine Neuberechnung bisweilen verhindert
                                   // werden. (z.B falls der Benutzer die Gruppe selbst resized hat)
    bool mbUseChartInventor;

public:

    TYPEINFO();

    SchObjGroup(ChartModel *pChmodel = NULL);
    virtual ~SchObjGroup();

    virtual UINT32 GetObjInventor() const;
    virtual UINT16 GetObjIdentifier() const;

    using SdrObjGroup::operator=;

    // FG: Damit soll erm�glicht werden dass man Objektgruppen im Chart resizen kann
    void    SetObjInfo(SdrObjTransformInfoRec aMyInfo);

    // FG: Um das Verhalten bei einem Resize zu aendern muessen beide Routinen
    //     �berladen werden.

    // FG: 9.3.1997 Methode von Joe, die �berladen wird um zu Kennzeichnen
    //              ob die Gruppe jemals verschoben worden ist.
    virtual void Move  (const Size& rSiz);

    void SetGroupType (ChartGroupTypeNames value) {eChartGroupType = value;}
    ChartGroupTypeNames GetGroupType() {return eChartGroupType;}
    void SetGroupIsChart() {eChartGroupType = DIAGRAM;}
    BOOL GetGroupIsChart() {return (eChartGroupType == DIAGRAM);}


    using SdrObjGroup::SetModel;
    void SetModel (ChartModel *pChModel) {pChartmodel = pChModel; SdrObjGroup::SetModel( (SdrModel*) pChModel ); }

    void SetAskForLogicRect(BOOL value) {bAskForLogicRect = value;}
    BOOL GetAskForLogicRect() {return bAskForLogicRect;}

    void SetUseChartInventor( bool bUseChartInventor );
};

} //namespace binfilter
#endif  // _SCH_SCHGROUP_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
