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

#ifdef _MSC_VER
#pragma hdrstop
#endif


#include "printopt.hxx"
namespace binfilter {

using namespace utl;
using namespace ::com::sun::star::uno;
using ::rtl::OUString;

// -----------------------------------------------------------------------

/*N*/ ScPrintOptions::ScPrintOptions()
/*N*/ {
/*N*/   SetDefaults();
/*N*/ }

/*N*/ ScPrintOptions::ScPrintOptions( const ScPrintOptions& rCpy ) :
/*N*/   bSkipEmpty( rCpy.bSkipEmpty ),
/*N*/   bAllSheets( rCpy.bAllSheets )
/*N*/ {
/*N*/ }

/*N*/ ScPrintOptions::~ScPrintOptions()
/*N*/ {
/*N*/ }

/*N*/ void ScPrintOptions::SetDefaults()
/*N*/ {
/*N*/   bSkipEmpty = FALSE;
/*N*/   bAllSheets = TRUE;
/*N*/ }


// -----------------------------------------------------------------------

#define CFGPATH_PRINT           "Office.Calc/Print"

#define SCPRINTOPT_EMPTYPAGES       0
#define SCPRINTOPT_ALLSHEETS        1
#define SCPRINTOPT_COUNT            2


ScPrintCfg::ScPrintCfg() :
    ConfigItem( OUString(RTL_CONSTASCII_USTRINGPARAM( CFGPATH_PRINT )) )
{
    DBG_BF_ASSERT(0, "STRIP");  // CONSTRUCTOR
}


void ScPrintCfg::Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& /*aPropertyNames*/ )
{
}

void ScPrintCfg::Commit()
{
}




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
