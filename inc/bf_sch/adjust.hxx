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

#ifndef _SCH_ADJUST_HXX
#define _SCH_ADJUST_HXX

/************************************************************************/
namespace binfilter {

enum ChartAdjust
{
    CHADJUST_TOP_LEFT,
    CHADJUST_TOP_RIGHT,
    CHADJUST_TOP_CENTER,
    CHADJUST_CENTER_LEFT,
    CHADJUST_CENTER_RIGHT,
    CHADJUST_CENTER_CENTER,
    CHADJUST_BOTTOM_LEFT,
    CHADJUST_BOTTOM_CENTER,
    CHADJUST_BOTTOM_RIGHT
};

#define CHADJUST_COUNT  CHADJUST_BOTTOM_RIGHT + 1

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
