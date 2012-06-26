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

#include "axisid.hxx"
#include "schgroup.hxx"
#include "objfac.hxx"
#include "objid.hxx"
#include "objadj.hxx"
#include "datarow.hxx"
#include "datapoin.hxx"
#include "glob.hxx"

namespace binfilter {


/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjFactory::SchObjFactory() :
/*N*/   bInserted(FALSE)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Chart-interne Objekte erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK( SchObjFactory, MakeObject, SdrObjFactory*, pObjFactory)
/*N*/ {
/*N*/   if (pObjFactory->nInventor == SchInventor &&
/*N*/       pObjFactory->nIdentifier == SCH_OBJGROUP_ID)
/*N*/       pObjFactory->pNewObj = new SchObjGroup;
/*N*/
/*N*/   return 0;
/*N*/ }

/*************************************************************************
|*
|* Chart-Userdata erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK( SchObjFactory, MakeUserData, SdrObjFactory* ,pObjFactory)
/*N*/ {
/*N*/   if (pObjFactory->nInventor == SchInventor)
/*N*/       switch (pObjFactory->nIdentifier)
/*N*/       {
/*N*/           case SCH_OBJECTID_ID:
/*N*/               pObjFactory->pNewData = new SchObjectId;
/*N*/               break;
/*N*/
/*N*/           case SCH_OBJECTADJUST_ID:
/*N*/               pObjFactory->pNewData = new SchObjectAdjust;
/*N*/               break;
/*N*/
/*N*/           case SCH_DATAROW_ID:
/*N*/               pObjFactory->pNewData = new SchDataRow;
/*N*/               break;
/*N*/
/*N*/           case SCH_DATAPOINT_ID:
/*N*/               pObjFactory->pNewData = new SchDataPoint;
/*N*/               break;
/*N*/
/*N*/           case SCH_LIGHTFACTOR_ID:
/*?*/               OSL_FAIL("SCH_LIGHTFACTOR_ID no longer available");
/*?*/               break;
/*N*/
/*N*/           case SCH_AXIS_ID :
/*N*/               pObjFactory->pNewData = new SchAxisId;
/*N*/               break;
/*N*/       }
/*N*/
/*N*/       return 0;
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
