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

#ifndef SC_CONVUNO_HXX
#define SC_CONVUNO_HXX


#include <com/sun/star/table/CellAddress.hpp>
#include <com/sun/star/table/CellRangeAddress.hpp>


#include "global.hxx"
namespace binfilter {

class ScUnoConversion
{
public:
    static LanguageType GetLanguage( const ::com::sun::star::lang::Locale& rLocale );
    static void FillLocale( ::com::sun::star::lang::Locale& rLocale, LanguageType eLang );

    // CellAddress -> ScAddress
    static inline void  FillScAddress(
                            ScAddress& rScAddress,
                            const ::com::sun::star::table::CellAddress& rApiAddress );
    // ScAddress -> CellAddress
    static inline void  FillApiAddress(
                            ::com::sun::star::table::CellAddress& rApiAddress,
                            const ScAddress& rScAddress );
    // CellRangeAddress -> ScRange
    static inline void  FillScRange(
                            ScRange& rScRange,
                            const ::com::sun::star::table::CellRangeAddress& rApiRange );
    // ScRange -> CellRangeAddress
    static inline void  FillApiRange(
                            ::com::sun::star::table::CellRangeAddress& rApiRange,
                            const ScRange& rScRange );
    // CellAddress -> CellRangeAddress
    static inline void  FillApiRange(
                            ::com::sun::star::table::CellRangeAddress& rApiRange,
                            const ::com::sun::star::table::CellAddress& rApiAddress );
    // CellRangeAddress-Start -> CellAddress
    static inline void  FillApiStartAddress(
                            ::com::sun::star::table::CellAddress& rApiAddress,
                            const ::com::sun::star::table::CellRangeAddress& rApiRange );
    // CellRangeAddress-End -> CellAddress
    static inline void  FillApiEndAddress(
                            ::com::sun::star::table::CellAddress& rApiAddress,
                            const ::com::sun::star::table::CellRangeAddress& rApiRange );
};


inline void ScUnoConversion::FillScAddress(
        ScAddress& rScAddress,
        const ::com::sun::star::table::CellAddress& rApiAddress )
{
    rScAddress.Set( (USHORT)rApiAddress.Column, (USHORT)rApiAddress.Row, (USHORT)rApiAddress.Sheet );
}

inline void ScUnoConversion::FillApiAddress(
        ::com::sun::star::table::CellAddress& rApiAddress,
        const ScAddress& rScAddress )
{
    rApiAddress.Column = rScAddress.Col();
    rApiAddress.Row = rScAddress.Row();
    rApiAddress.Sheet = rScAddress.Tab();
}

inline void ScUnoConversion::FillScRange(
        ScRange& rScRange,
        const ::com::sun::star::table::CellRangeAddress& rApiRange )
{
    rScRange.aStart.Set( (USHORT)rApiRange.StartColumn, (USHORT)rApiRange.StartRow, (USHORT)rApiRange.Sheet );
    rScRange.aEnd.Set( (USHORT)rApiRange.EndColumn, (USHORT)rApiRange.EndRow, (USHORT)rApiRange.Sheet );
}

inline void ScUnoConversion::FillApiRange(
        ::com::sun::star::table::CellRangeAddress& rApiRange,
        const ScRange& rScRange )
{
    rApiRange.StartColumn = rScRange.aStart.Col();
    rApiRange.StartRow = rScRange.aStart.Row();
    rApiRange.Sheet = rScRange.aStart.Tab();
    rApiRange.EndColumn = rScRange.aEnd.Col();
    rApiRange.EndRow = rScRange.aEnd.Row();
}

inline void ScUnoConversion::FillApiRange(
        ::com::sun::star::table::CellRangeAddress& rApiRange,
        const ::com::sun::star::table::CellAddress& rApiAddress )
{
    rApiRange.StartColumn = rApiRange.EndColumn = rApiAddress.Column;
    rApiRange.StartRow = rApiRange.EndRow = rApiAddress.Row;
    rApiRange.Sheet = rApiAddress.Sheet;
}

inline void ScUnoConversion::FillApiStartAddress(
        ::com::sun::star::table::CellAddress& rApiAddress,
        const ::com::sun::star::table::CellRangeAddress& rApiRange )
{
    rApiAddress.Column = rApiRange.StartColumn;
    rApiAddress.Row = rApiRange.StartRow;
    rApiAddress.Sheet = rApiRange.Sheet;
}

inline void ScUnoConversion::FillApiEndAddress(
        ::com::sun::star::table::CellAddress& rApiAddress,
        const ::com::sun::star::table::CellRangeAddress& rApiRange )
{
    rApiAddress.Column = rApiRange.EndColumn;
    rApiAddress.Row = rApiRange.EndRow;
    rApiAddress.Sheet = rApiRange.Sheet;
}

//___________________________________________________________________

inline sal_Bool operator==(
        const ::com::sun::star::table::CellAddress& rApiAddress1,
        const ::com::sun::star::table::CellAddress& rApiAddress2 )
{
    return
        (rApiAddress1.Column == rApiAddress2.Column) &&
        (rApiAddress1.Row == rApiAddress2.Row) &&
        (rApiAddress1.Sheet == rApiAddress2.Sheet);
}

inline sal_Bool operator!=(
        const ::com::sun::star::table::CellAddress& rApiAddress1,
        const ::com::sun::star::table::CellAddress& rApiAddress2 )
{
    return !(rApiAddress1 == rApiAddress2);
}

inline sal_Bool operator==(
        const ::com::sun::star::table::CellRangeAddress& rApiRange1,
        const ::com::sun::star::table::CellRangeAddress& rApiRange2 )
{
    return
        (rApiRange1.StartColumn == rApiRange2.StartColumn) &&
        (rApiRange1.StartRow == rApiRange2.StartRow) &&
        (rApiRange1.EndColumn == rApiRange2.EndColumn) &&
        (rApiRange1.EndRow == rApiRange2.EndRow) &&
        (rApiRange1.Sheet == rApiRange2.Sheet);
}

inline sal_Bool operator!=(
        const ::com::sun::star::table::CellRangeAddress& rApiRange1,
        const ::com::sun::star::table::CellRangeAddress& rApiRange2 )
{
    return !(rApiRange1 == rApiRange2);
}

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
