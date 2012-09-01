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

#ifndef SC_SORTPARAM_HXX
#define SC_SORTPARAM_HXX

#include <bf_tools/string.hxx>
#include <bf_svtools/bf_solar.h>
#include <com/sun/star/lang/Locale.hpp>
namespace binfilter {


#define MAXSORT     3


struct ScSubTotalParam;
struct ScQueryParam;

struct ScSortParam
{
    USHORT      nCol1;
    USHORT      nRow1;
    USHORT      nCol2;
    USHORT      nRow2;
    BOOL        bHasHeader;
    BOOL        bByRow;
    BOOL        bCaseSens;
    BOOL        bUserDef;
    USHORT      nUserIndex;
    BOOL        bIncludePattern;
    BOOL        bInplace;
    USHORT      nDestTab;
    USHORT      nDestCol;
    USHORT      nDestRow;
    BOOL        bDoSort[MAXSORT];
    USHORT      nField[MAXSORT];
    BOOL        bAscending[MAXSORT];
    ::com::sun::star::lang::Locale      aCollatorLocale;
    String      aCollatorAlgorithm;

    ScSortParam();
    ScSortParam( const ScSortParam& r );
    /// SubTotals sort
    /// TopTen sort

    void            Clear       ();

};


} //namespace binfilter
#endif // SC_SORTPARAM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
