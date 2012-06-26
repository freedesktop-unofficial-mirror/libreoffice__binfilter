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
#ifndef _BINDING_HXX
#define _BINDING_HXX

#ifndef __RSC

#include <bf_svtools/bf_solar.h>

namespace binfilter {
typedef ULONG SvBindStatus;

typedef ULONG SvStatusCallbackType;
#define SVBSCF_FIRSTDATANOTIFICATION          0x01
#define SVBSCF_LASTDATANOTIFICATION           0x02
#define SVBSCF_INTERMEDIATEDATANOTIFICATION   0x03
#define SVBSCF_RELOADAVAILABLENOTIFICATION    0x04
#define SVBSCF_NEWPARTAVAILABLENOTIFICATION   0x08

typedef ULONG SvBindMode;
#define SVBIND_ASYNC             0x01
#define SVBIND_ASYNCSTORAGE      0x02
#define SVBIND_NEWESTVERSION     0x04
#define SVBIND_SUCCESSONERRORDOC 0x08

enum SvBindAction
{
    BINDACTION_GET    = 0,
    BINDACTION_POST   = 0x1,
    BINDACTION_PUT    = 0x2,
    BINDACTION_CUSTOM = 0x3
};

}

#endif /* __RSC */

#endif /* _BINDING_HXX */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
