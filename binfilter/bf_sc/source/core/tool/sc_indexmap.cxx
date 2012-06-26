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


#include <memory.h>

#include "indexmap.hxx"
namespace binfilter {


/*N*/ ScIndexMap::ScIndexMap( USHORT nEntries )
/*N*/ {
/*N*/   nCount = nEntries;
/*N*/   ULONG nC = nEntries ? ((ULONG) nEntries * 2) : 2;
/*N*/   pMap = new USHORT [ nC ];
/*N*/   memset( pMap, 0, nC * sizeof(USHORT) );
/*N*/ }


/*N*/ ScIndexMap::~ScIndexMap()
/*N*/ {
/*N*/   delete [] pMap;
/*N*/ }


/*N*/ void ScIndexMap::SetPair( USHORT nEntry, USHORT nIndex1, USHORT nIndex2 )
/*N*/ {
/*N*/   if ( nEntry < nCount )
/*N*/   {
/*N*/       ULONG nOff = (ULONG) nEntry * 2;
/*N*/       pMap[nOff] = nIndex1;
/*N*/       pMap[nOff+1] = nIndex2;
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
