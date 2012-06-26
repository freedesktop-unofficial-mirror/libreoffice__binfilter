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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <tools/rcid.h>

#include "command.hxx"
namespace binfilter {

SmCommandDesc::SmCommandDesc(const ResId& rResId) :
    Resource(rResId)
{
    if (IsAvailableRes(ResId(1).SetRT(RSC_STRING)))
        pSample = new String(ResId(1));
    else
        pSample = new String;

    if (IsAvailableRes(ResId(2).SetRT(RSC_STRING)))
        pCommand = new String(ResId(2));
    else
        pCommand = new String;

    if (IsAvailableRes(ResId(3).SetRT(RSC_STRING)))
        pText = new String(ResId(3));
    else
        pText = new String("sorry, no help available");

    if (IsAvailableRes(ResId(4).SetRT(RSC_STRING)))
        pHelp = new String(ResId(4));
    else
        pHelp = new String("sorry, no help available");

    if (IsAvailableRes(ResId(1).SetRT(RSC_BITMAP)))
        pGraphic =  new Bitmap(ResId(1));
    else
        pGraphic = new Bitmap();

    FreeResource();
}

SmCommandDesc::~SmCommandDesc()
{
    if (pText)      delete pText;
    if (pHelp)      delete pHelp;
    if (pSample)    delete pSample;
    if (pCommand)   delete pCommand;
    if (pGraphic)   delete pGraphic;
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
