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
#ifndef _SDTAGITM_HXX
#define _SDTAGITM_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/sdooitm.hxx>

#include <bf_svx/svddef.hxx>
namespace binfilter {

//------------------------------------
// class SdrTextAutoGrowHeightItem
//------------------------------------
class SdrTextAutoGrowHeightItem: public SdrOnOffItem {
public:
    SdrTextAutoGrowHeightItem(BOOL bAuto=TRUE): SdrOnOffItem(SDRATTR_TEXT_AUTOGROWHEIGHT,bAuto) {}
    SdrTextAutoGrowHeightItem(SvStream& rIn)  : SdrOnOffItem(SDRATTR_TEXT_AUTOGROWHEIGHT,rIn)   {}
};

//------------------------------------
// class SdrTextAutoGrowWidthItem
//------------------------------------
class SdrTextAutoGrowWidthItem: public SdrOnOffItem {
public:
    SdrTextAutoGrowWidthItem(BOOL bAuto=FALSE): SdrOnOffItem(SDRATTR_TEXT_AUTOGROWWIDTH,bAuto) {}
    SdrTextAutoGrowWidthItem(SvStream& rIn)   : SdrOnOffItem(SDRATTR_TEXT_AUTOGROWWIDTH,rIn)   {}
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
