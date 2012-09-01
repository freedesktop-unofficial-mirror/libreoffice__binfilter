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

#ifndef _SBXBASE_HXX
#define _SBXBASE_HXX

#include <i18npool/lang.h>

#include "bf_svtools/svarray.hxx"

#include "sbxdef.hxx"

namespace binfilter {

class SbxFactory;
class SbxVariable;
class SbxBasicFormater;

SV_DECL_PTRARR_DEL(SbxFacs,SbxFactory*,5,5)

// AppData-Struktur fuer SBX:
struct SbxAppData
{
    SbxError            eSbxError;  // Fehlercode
    SbxFacs             aFacs;      // Factories

    SbxAppData() : eSbxError( SbxERR_OK ), aFacs() {}
};

SbxAppData* GetSbxData_Impl();

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
