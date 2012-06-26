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
#ifndef _LINETYPE_HXX
#define _LINETYPE_HXX

#include <bf_svtools/bf_solar.h>
namespace binfilter {

/*--------------------------------------------------------------------
     Beschreibung: Ein Linientyp wird durch die 3 Werte festgelegt
 --------------------------------------------------------------------*/

enum SwLineWidth
{
    LIN_0   = 0,
    LIN_1   = 1,
    LIN_2   = 20,
    LIN_3   = 50,
    LIN_4   = 80,
    LIN_5   = 100
};

struct SwLineType
{
    USHORT nIn;
    USHORT nOut;
    USHORT nDist;
};

USHORT             GetLineTypeCount();
const SwLineType&  GetLineType(USHORT nIdx);

} //namespace binfilter
#endif // _LINETYPE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
