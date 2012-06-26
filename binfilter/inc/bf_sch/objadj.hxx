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

#ifndef _SCH_OBJADJ_HXX
#define _SCH_OBJADJ_HXX

#include "adjust.hxx"

#include <bf_svx/chrtitem.hxx>
#include <bf_svx/svdobj.hxx>
#include <tools/stream.hxx>
namespace binfilter {


/*************************************************************************
|*
|* Ausrichtung von Chart-Objekten
|*
\************************************************************************/

class SchObjectAdjust : public SdrObjUserData
{
    ChartAdjust         eAdjust;    // Ausrichtung
    SvxChartTextOrient  eOrient;    // Orientierung

public:
    SchObjectAdjust();
    SchObjectAdjust(ChartAdjust eAdj, SvxChartTextOrient eOr);

    virtual SdrObjUserData* Clone(SdrObject *) const { return NULL; } // DBG_BF_ASSERT

    virtual void ReadData(SvStream& rIn);

    void SetAdjust(ChartAdjust eAdj) { eAdjust = eAdj; }
    ChartAdjust GetAdjust() { return eAdjust; }

    void SetOrient(SvxChartTextOrient eOr) { eOrient = eOr; }
    SvxChartTextOrient GetOrient() { return eOrient; }
};

/*************************************************************************
|*
|* Tool-Funktion fuer Objekt-Ausrichtung
|*
\************************************************************************/

extern SchObjectAdjust* GetObjectAdjust(const SdrObject& rObj);

} //namespace binfilter
#endif  // _SCH_OBJADJ_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
