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

#ifndef _DBTOKEN_HXX
#define _DBTOKEN_HXX

#include <bf_svtools/bf_solar.h>

#include "compiler.hxx"
namespace binfilter {


// SET DBG_TOKEN=string
// +  - make new data
// -  - do not make old data
// aA - dump old/new token array
// uU - dump old/new UPN array

BOOL DbgToken( char );
ScTokenArray* DbgMakeTokenArray
    ( ScDocument* pDoc, USHORT nTab, const String& r, USHORT& rErr );
void DbgDumpTokenArray( const BYTE* pArr, USHORT nLen, const char* pMsg );
void DbgDelTokenArray( ScTokenArray* );
StackVar DbgInterpret( ScDocument* pDok, const ScTokenArray* pToken,
                       USHORT nCOL, USHORT nROW, USHORT nTAB,
                                  StackVar eStackVar,
                                  char* &rStringErgPtr,
                                  double& rDoubleErg,
                                  USHORT& rError,
                                  ScMatrix** ppMat);

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
