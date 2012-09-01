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

#ifndef _SCH_STLSHEET_HXX
#define _SCH_STLSHEET_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/style.hxx>
namespace binfilter {




class SchStyleSheet : public SfxStyleSheet
{
protected:
    virtual void Load (SvStream& rIn, USHORT nVersion);
    virtual void Store(SvStream&) {}

public:
    TYPEINFO();
    SchStyleSheet(const String& rName, SfxStyleSheetBasePool& rPool,
                  SfxStyleFamily eFamily, USHORT nMask);
    virtual ~SchStyleSheet();

    virtual BOOL SetParent (const String& rParentName);
    virtual SfxItemSet& GetItemSet();
};

} //namespace binfilter
#endif     // _SCH_STLSHEET_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
