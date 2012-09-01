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
#ifndef _ITABENUM_HXX
#define _ITABENUM_HXX
namespace binfilter {

enum SwTableInsMode
{
    DEFAULT_BORDER     = 0x01,
    HEADLINE           = 0x02,
    REPEAT             = 0x04,
    HEADLINE_REPEAT    = 0x06,  // Headline + Repeat
    SPLIT_LAYOUT       = 0x08,
    HEADLINE_NO_BORDER = HEADLINE_REPEAT|SPLIT_LAYOUT,
    ALL_TBL_INS_ATTR   = DEFAULT_BORDER|HEADLINE_REPEAT|SPLIT_LAYOUT
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
