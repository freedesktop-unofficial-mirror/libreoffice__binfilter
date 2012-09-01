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

#ifndef SC_CELLFORM_HXX
#define SC_CELLFORM_HXX

#include <bf_svtools/bf_solar.h>
class String;
class Color;
namespace binfilter {

class SvNumberFormatter;

class ScBaseCell;

enum ScForceTextFmt {
    ftDontForce,            // Zahlen als Zahlen
    ftForce,                // Zahlen als Text
    ftCheck                 // ist das Zahlenformat ein Textformat?
};

//------------------------------------------------------------------------

class ScCellFormat
{
public:
    static void     GetString( ScBaseCell* pCell, ULONG nFormat, String& rString,
                               Color** ppColor, SvNumberFormatter& rFormatter,
                               BOOL bNullVals = TRUE,
                               BOOL bFormula  = FALSE,
                               ScForceTextFmt eForceTextFmt = ftDontForce );

    static void     GetInputString( ScBaseCell* pCell, ULONG nFormat, String& rString,
                                      SvNumberFormatter& rFormatter );
};




} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
