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

#ifndef SC_PAGEPAR_HXX
#define SC_PAGEPAR_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"
namespace binfilter {

//-----------------------------------------------------------------------

struct ScPageTableParam
{
    BOOL    bNotes;
    BOOL    bGrid;
    BOOL    bHeaders;
    BOOL    bCharts;
    BOOL    bObjects;
    BOOL    bDrawings;
    BOOL    bFormulas;
    BOOL    bNullVals;
    BOOL    bTopDown;
    BOOL    bLeftRight;
    BOOL    bSkipEmpty;
    BOOL    bScaleNone;
    BOOL    bScaleAll;
    BOOL    bScalePageNum;
    USHORT  nScaleAll;
    USHORT  nScalePageNum;
    USHORT  nFirstPageNo;

    ScPageTableParam();
    ScPageTableParam( const ScPageTableParam& r );
    ~ScPageTableParam();

    void                Reset       ();
};

struct ScPageAreaParam
{
    BOOL    bPrintArea;
    BOOL    bRepeatRow;
    BOOL    bRepeatCol;
    ScRange aPrintArea;
    ScRange aRepeatRow;
    ScRange aRepeatCol;

    ScPageAreaParam();
    ScPageAreaParam( const ScPageAreaParam& r );
    ~ScPageAreaParam();

    void                Reset       ();
};


} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
