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
#ifndef _NUMPARA_HXX
#define _NUMPARA_HXX

#include <bf_svtools/bf_solar.h>

#include "numrule.hxx"
#include "ndarr.hxx"
#include "ndindex.hxx"
namespace binfilter {

class SwTxtNode;
class SwDoc;
class SwNumSection;
class SwNodes;

class _NumPara
{
    const SwNumSection& rNumSection;

    void _Init();

public:
    SwNodeIndex aNdIdx;
    ULONG nCnt;
    SwNum aNum;
    char nDiff;             // +1, 0, -1 !! dafuer reicht ein char !!
    BYTE nOldLevel;
    BOOL bInitNum : 1;
    BOOL bWasUndo : 1;
    BOOL bOverTbl : 1;      // Flag fuer ForEach-Methoden, Tabelle ueberspr.

    _NumPara( char nOffset, const SwNodeIndex& rNdIdx,
                const SwNumSection& rSect, ULONG nCntNodes );
    _NumPara( const SwNodeIndex& rNdIdx, const SwNumSection& rSect );
    ~_NumPara();

    void UpdateNum( SwTxtNode& rTxtNd );
};

// Funktion fuer ForEach am Nodes-Array
BOOL _NumUpDown( const SwNodePtr& rpNode, void* pPara );


} //namespace binfilter
#endif  // _NUMPARA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
