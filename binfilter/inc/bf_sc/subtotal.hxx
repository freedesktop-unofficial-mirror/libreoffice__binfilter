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

#ifndef SC_SUBTOTAL_HXX
#define SC_SUBTOTAL_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"

#include <setjmp.h>

namespace binfilter {

class SubTotal
{
private:
    long    nCount;
    long    nCount2;
    double  nSum;
    double  nSumSqr;
    double  nMax;
    double  nMin;
    double  nProduct;
    BOOL    bSumOk;
    BOOL    bSumSqrOk;
    BOOL    bProductOk;
    USHORT  nProgress;

public:
    USHORT  nIndex;         // Test
    static jmp_buf aGlobalJumpBuf;

public:
            SubTotal();
            ~SubTotal();

    void    Update( double nVal );
    static  BOOL SafePlus( double& fVal1, double fVal2);
    static  BOOL SafeMult( double& fVal1, double fVal2);
};


struct ScFunctionData                   // zum Berechnen von einzelnen Funktionen
{
    ScSubTotalFunc  eFunc;
    double          nVal;
    long            nCount;
    BOOL            bError;

    ScFunctionData( ScSubTotalFunc eFn ) :
        eFunc(eFn), nVal(0.0), nCount(0), bError(FALSE) {}
};


} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
