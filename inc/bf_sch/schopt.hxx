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

#ifndef _SCH_SCHOPT_HXX
#define _SCH_SCHOPT_HXX

#include <bf_svtools/bf_solar.h>

// header for TYPEINFO
#include <tools/rtti.hxx>
// header for ConfigItem
#include <unotools/configitem.hxx>
// header for SfxPoolItem
#include <bf_svtools/poolitem.hxx>
// header for Color
#include <tools/color.hxx>
// header for Table
#include <bf_tools/table.hxx>
// header for XColorEntry
#include <bf_svx/xtable.hxx>
namespace binfilter {

// --------------------
// default colors
// --------------------
class SchColorTable : private Table
{
public:
    SchColorTable();
    virtual ~SchColorTable() {}


    // make public
    using Table::Count;

    // specialized methods from Table
    void            ClearAndDestroy();

    BOOL            Insert( ULONG nKey, XColorEntry* );
    XColorEntry*    Get( ULONG nKey ) const;

    Color           GetColor( ULONG nKey ) const;
    ColorData       GetColorData( ULONG nKey ) const;

    BOOL            operator ==( const SchColorTable& rCol ) const
                    { return Table::operator ==( rCol ); }
    BOOL            operator !=( const SchColorTable& rCol ) const
                    { return Table::operator !=( rCol ); }
};

// ====================
// all options
// ====================
class SchOptions : public ::utl::ConfigItem
{
private:
    SchColorTable       maDefColors;
    BOOL                mbIsInitialized;
    ::com::sun::star::uno::Sequence< ::rtl::OUString > maPropertyNames;

    ::com::sun::star::uno::Sequence< ::rtl::OUString > GetPropertyNames() const
        { return maPropertyNames; }
    BOOL RetrieveOptions();

public:
    SchOptions();
    virtual ~SchOptions();
void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
void Commit();

    const SchColorTable& GetDefaultColors();

};

// ====================
// items
// ====================

} //namespace binfilter
#endif  // _SCH_SCHOPT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
