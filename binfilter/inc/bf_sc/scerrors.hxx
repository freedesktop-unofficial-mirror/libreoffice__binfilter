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

#ifndef _SCERRORS_HXX
#define _SCERRORS_HXX


// ERRCODE_CLASS_READ - file related, displays "Read-Error" in MsgBox
#define SCERR_IMPORT_CONNECT        (   1 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_OPEN           (   2 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_UNKNOWN        (   3 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_FORMAT         (   6 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_NI             (   7 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_8K_LIMIT       (  12 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_INFOLOST      (  15 | ERRCODE_CLASS_READ | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCERR_IMPORT_FILE_ROWCOL    (  16 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_FORMAT_ROWCOL  (  17 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_FILE_ROWCOL   (  18 | ERRCODE_CLASS_READ | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

// ERRCODE_CLASS_WRITE - file related, displays "Write-Error" in MsgBox

// ERRCODE_CLASS_IMPORT - does not display "Read-Error" in MsgBox
#define SCWARN_IMPORT_RANGE_OVERFLOW (  1 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_ROW_OVERFLOW (  2 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_COLUMN_OVERFLOW (  3 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_SHEET_OVERFLOW (  4 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

// ERRCODE_CLASS_EXPORT - does not display "Write-Error" in MsgBox
#define SCWARN_EXPORT_MAXROW        (   3 | ERRCODE_CLASS_EXPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

// ERRCODE_CLASS_GENERAL
#define SCWARN_CORE_HARD_RECALC     (   1 | ERRCODE_CLASS_GENERAL | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
