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

#ifndef SC_PRNSAVE_HXX
#define SC_PRNSAVE_HXX

#include <bf_svtools/bf_solar.h>
namespace binfilter {

class ScRange;

class ScPrintSaverTab
{
    USHORT      nPrintCount;
    ScRange*    pPrintRanges;   // Array
    ScRange*    pRepeatCol;     // einzeln
    ScRange*    pRepeatRow;     // einzeln

public:
            ScPrintSaverTab();
            ~ScPrintSaverTab();

    void    SetAreas( USHORT nCount, const ScRange* pRanges );
    void    SetRepeat( const ScRange* pCol, const ScRange* pRow );

    USHORT          GetPrintCount() const   { return nPrintCount; }
    const ScRange*  GetPrintRanges() const  { return pPrintRanges; }
    const ScRange*  GetRepeatCol() const    { return pRepeatCol; }
    const ScRange*  GetRepeatRow() const    { return pRepeatRow; }

};

class ScPrintRangeSaver
{
    USHORT              nTabCount;
    ScPrintSaverTab*    pData;      // Array

public:
            ScPrintRangeSaver( USHORT nCount );
            ~ScPrintRangeSaver();

    USHORT                  GetTabCount() const     { return nTabCount; }
    ScPrintSaverTab&        GetTabData(USHORT nTab);

};


} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
