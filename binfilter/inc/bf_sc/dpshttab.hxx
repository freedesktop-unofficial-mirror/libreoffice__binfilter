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

#ifndef SC_DPSHTTAB_HXX
#define SC_DPSHTTAB_HXX

#include <bf_svtools/bf_solar.h>

#include "dptabdat.hxx"

#include "global.hxx"
namespace binfilter {


// --------------------------------------------------------------------
//
//  implementation of ScDPTableData with sheet data
//

struct ScSheetSourceDesc
{
    ScRange         aSourceRange;
    ScQueryParam    aQueryParam;
};

 class ScSheetDPData_Impl;

class ScSheetDPData : public ScDPTableData
{
private:
    ScSheetDPData_Impl* pImpl;
    BOOL* pSpecial;

public:
                    ScSheetDPData( ScDocument* pD, const ScSheetSourceDesc& rDesc );
    virtual         ~ScSheetDPData();

    virtual long    GetColumnCount();
    virtual String  getDimensionName(long nColumn);
    virtual BOOL    getIsDataLayoutDimension(long nColumn);
    virtual BOOL    IsDateDimension(long nDim);
    virtual UINT32  GetNumberFormat(long /*nDim*/) { return 0; } // DBG_BF_ASSERT
    virtual void    DisposeData() {} // DBG_BF_ASSERT
    virtual void    SetEmptyFlags( BOOL bIgnoreEmptyRows, BOOL bRepeatIfEmpty );

    virtual void    ResetIterator();
    virtual BOOL    GetNextRow( const ScDPTableIteratorParam& /*rParam*/ ) { return FALSE; } // DBG_BF_ASSERT
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
