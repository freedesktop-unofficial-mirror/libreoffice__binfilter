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

#ifndef _PVPRTDAT_HXX
#define _PVPRTDAT_HXX

#include <bf_svtools/bf_solar.h>

namespace binfilter {

class SwPagePreViewPrtData
{
    ULONG nLeftSpace, nRightSpace, nTopSpace, nBottomSpace,
            nHorzSpace, nVertSpace;
    BYTE nRow, nCol;
    BOOL bLandscape : 1;
    BOOL bStretch : 1;
public:
    SwPagePreViewPrtData()
        : nLeftSpace(0), nRightSpace(0), nTopSpace(0), nBottomSpace(0),
            nHorzSpace(0), nVertSpace(0), nRow(1), nCol(1),
            bLandscape(0),bStretch(0)
    {}

    ULONG GetLeftSpace() const          { return nLeftSpace; }
    void SetLeftSpace( ULONG n )        { nLeftSpace = n; }

    ULONG GetRightSpace() const         { return nRightSpace; }
    void SetRightSpace( ULONG n )       { nRightSpace = n; }

    ULONG GetTopSpace() const           { return nTopSpace; }
    void SetTopSpace( ULONG n )         { nTopSpace = n; }

    ULONG GetBottomSpace() const        { return nBottomSpace; }
    void SetBottomSpace( ULONG n )      { nBottomSpace = n; }

    ULONG GetHorzSpace() const          { return nHorzSpace; }
    void SetHorzSpace( ULONG n )        { nHorzSpace = n; }

    ULONG GetVertSpace() const          { return nVertSpace; }
    void SetVertSpace( ULONG n )        { nVertSpace = n; }

    BYTE GetRow() const                 { return nRow; }
    void SetRow(BYTE n )                { nRow = n; }

    BYTE GetCol() const                 { return nCol; }
    void SetCol( BYTE n )               { nCol = n; }

    BOOL GetLandscape() const           { return bLandscape; }
    void SetLandscape( BOOL b )         { bLandscape = b; }

    // JP 19.08.98: wird zur Zeit nicht ausgewertet, weil der Font sich
    //              nicht enstprechend stretch laesst.
    BOOL GetStretch() const             { return bStretch; }
    void SetStretch( BOOL b )           { bStretch = b; }
};


} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
