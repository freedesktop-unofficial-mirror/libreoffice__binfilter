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

#include "pntlock.hxx"
namespace binfilter {

//------------------------------------------------------------------------

/*N*/ ScPaintLockData::ScPaintLockData(USHORT nNewMode) :
/*N*/   nMode( nNewMode ),
/*N*/   nLevel( 0 ),
/*N*/   nDocLevel( 0 ),
/*N*/   nParts( 0 ),
/*N*/   bModified( FALSE )
/*N*/ {
/*N*/ }

/*N*/ ScPaintLockData::~ScPaintLockData()
/*N*/ {
/*N*/ }

/*N*/ void ScPaintLockData::AddRange( const ScRange& rRange, USHORT nP )
/*N*/ {
/*N*/   if (!xRangeList.Is())
/*N*/       xRangeList = new ScRangeList;
/*N*/
/*N*/   xRangeList->Join( rRange );
/*N*/   nParts |= nP;
/*N*/ }




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
