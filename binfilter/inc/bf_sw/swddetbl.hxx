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
#ifndef _SWDDETBL_HXX
#define _SWDDETBL_HXX

#include <bf_svtools/bf_solar.h>

#include "swtable.hxx"
namespace binfilter {

class SwDDEFieldType;

class SwDDETable : public SwTable
{
public:
    TYPEINFO();
    // Constructor movet alle Lines/Boxen aus der SwTable zu sich.
    // Die SwTable ist danach Leer und muss geloescht werden.
    SwDDETable( SwTable& rTable, SwDDEFieldType*, BOOL = TRUE )
        : SwTable( rTable )
        {}
    SwDDEFieldType* GetDDEFldType() { DBG_BF_ASSERT(0, "STRIP"); return NULL; }
    inline const SwDDEFieldType* GetDDEFldType() const;
};


// ----------- Inlines -----------------------------

inline const SwDDEFieldType* SwDDETable::GetDDEFldType() const
{
    return ((SwDDETable*)this)->GetDDEFldType();
}

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
