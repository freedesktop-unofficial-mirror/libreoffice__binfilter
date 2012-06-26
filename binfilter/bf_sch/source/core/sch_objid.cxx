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

#include "objid.hxx"
#include "glob.hxx"

#include "defines.hxx"

#include <tools/debug.hxx>

namespace binfilter {

/*************************************************************************
|*
|* Objekt-Id ermitteln;
|* Liefert -1, wenn das Objekt keine Id hat
|*
\************************************************************************/

/*N*/ SchObjectId* GetObjectId(const SdrObject& rObj)
/*N*/ {
/*N*/   for (USHORT i = 0; i < rObj.GetUserDataCount(); i++)
/*N*/   {
/*N*/       SdrObjUserData *pData = rObj.GetUserData(i);
/*N*/       if (pData && pData->GetId() == SCH_OBJECTID_ID)
/*N*/           return (SchObjectId*)pData;
/*N*/   }
/*N*/
/*N*/   return NULL;
/*N*/ }


/*************************************************************************
|*
|* Objekt mit Id suchen;
|* liefert NULL, wenn kein Objekt gefunden wurde.
|*
\************************************************************************/

/*N*/ SdrObject* GetObjWithId(UINT16 nObjId, const SdrObjList& rObjList,
/*N*/                       ULONG* pIndex, SdrIterMode eMode)
/*N*/ {
/*N*/   ULONG nIndex = 0;
/*N*/
/*N*/   SdrObjListIter aIterator(rObjList, eMode);
/*N*/   while (aIterator.IsMore())
/*N*/   {
/*N*/       SdrObject* pObj = aIterator.Next();
/*N*/       SchObjectId* pObjId = GetObjectId(*pObj);
/*N*/       if (pObjId && pObjId->GetObjId() == nObjId)
/*N*/       {
/*N*/           if (pIndex)
/*?*/               *pIndex = nIndex;
/*N*/           return pObj;
/*N*/       }
/*N*/
/*N*/       nIndex++;
/*N*/   }
/*N*/
/*N*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectId::SchObjectId() :
/*N*/   SdrObjUserData(SchInventor, SCH_OBJECTID_ID, 0),
/*N*/   nObjId(0)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectId::SchObjectId(UINT16 nId) :
/*N*/   SdrObjUserData(SchInventor, SCH_OBJECTID_ID, 0),
/*N*/   nObjId(nId)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchObjectId::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/
/*N*/   rIn >> nObjId;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
