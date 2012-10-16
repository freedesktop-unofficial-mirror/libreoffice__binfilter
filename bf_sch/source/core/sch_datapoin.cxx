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

#include <bf_svx/svditer.hxx>

#include "datapoin.hxx"
#include "glob.hxx"
#include <tools/debug.hxx>
namespace binfilter {
/*************************************************************************
|*
|* Datenpunkt ermitteln
|*
\************************************************************************/

/*N*/ SchDataPoint* GetDataPoint(const SdrObject& rObj)
/*N*/ {//#63904 2x Schleife (15%), 50% pData, 18% id
/*N*/   USHORT i=rObj.GetUserDataCount();
/*N*/   while(i--)
/*N*/   {
/*N*/       SdrObjUserData *pData = rObj.GetUserData(i);
/*N*/       if (pData && pData->GetId() == SCH_DATAPOINT_ID)
/*N*/           return (SchDataPoint*)pData;
/*N*/   }
/*N*/
/*N*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Objekt mit Datenpunkt-Indizes suchen;
|* liefert NULL, wenn kein Objekt gefunden wurde.
|*
\************************************************************************/

/*N*/ SdrObject* GetObjWithColRow(short nCol, short nRow,
/*N*/                        const SdrObjList& rObjList, ULONG* pIndex)
/*N*/ {
/*N*/   ULONG nIndex = 0;
/*N*/
/*N*/   SdrObjListIter aIterator(rObjList, IM_FLAT);
/*N*/   while (aIterator.IsMore())
/*N*/   {
/*N*/       SdrObject* pObj = aIterator.Next();
/*N*/       SchDataPoint* pDataPoint = GetDataPoint(*pObj);
/*N*/       if (pDataPoint && pDataPoint->GetCol() == nCol &&
/*N*/                         pDataPoint->GetRow() == nRow)
/*N*/       {
/*N*/           if (pIndex)
/*N*/               *pIndex = nIndex;
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

/*N*/ SchDataPoint::SchDataPoint() :
/*N*/   SdrObjUserData(SchInventor, SCH_DATAPOINT_ID, 0),
/*N*/   nCol(0),
/*N*/   nRow(0)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchDataPoint::SchDataPoint(short nC, short nR) :
/*N*/   SdrObjUserData(SchInventor, SCH_DATAPOINT_ID, 0),
/*N*/   nCol(nC),
/*N*/   nRow(nR)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchDataPoint::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/
/*N*/   INT16 nInt16;
/*N*/
/*N*/   rIn >> nInt16; nCol = (short)nInt16;
/*N*/   rIn >> nInt16; nRow = (short)nInt16;
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
