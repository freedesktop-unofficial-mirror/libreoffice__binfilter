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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "objadj.hxx"
#include "glob.hxx"

#include <tools/debug.hxx>

namespace binfilter {


/*************************************************************************
|*
|* Objekt-Ausrichting ermitteln
|*
\************************************************************************/

/*N*/ SchObjectAdjust* GetObjectAdjust(const SdrObject& rObj)
/*N*/ {
/*N*/   for (USHORT i = 0; i < rObj.GetUserDataCount(); i++)
/*N*/   {
/*N*/       SdrObjUserData *pData = rObj.GetUserData(i);
/*N*/       if (pData && pData->GetId() == SCH_OBJECTADJUST_ID)
/*N*/           return (SchObjectAdjust*)pData;
/*N*/   }
/*N*/
/*?*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectAdjust::SchObjectAdjust() :
/*N*/   SdrObjUserData(SchInventor, SCH_OBJECTADJUST_ID, 1),
/*N*/   eAdjust(CHADJUST_TOP_LEFT),
/*N*/   eOrient(CHTXTORIENT_STANDARD)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectAdjust::SchObjectAdjust(ChartAdjust eAdj,
/*N*/                                SvxChartTextOrient eOr) :
/*N*/   SdrObjUserData(SchInventor, SCH_OBJECTADJUST_ID, 1),
/*N*/   eAdjust(eAdj),
/*N*/   eOrient(eOr)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchObjectAdjust::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/
/*N*/   INT16 nInt16;
/*N*/
/*N*/   rIn >> nInt16; eAdjust = (ChartAdjust)nInt16;
/*N*/
/*N*/   if (nVersion < 1)
/*?*/       eOrient = CHTXTORIENT_STANDARD;
/*N*/   else
/*N*/   {
/*N*/       rIn >> nInt16; eOrient = (SvxChartTextOrient)nInt16;
/*N*/   }
/*N*/
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
