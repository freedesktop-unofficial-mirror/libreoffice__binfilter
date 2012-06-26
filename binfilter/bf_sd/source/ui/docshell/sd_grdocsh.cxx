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

#include <bf_svx/svxids.hrc>
#define ITEMID_SEARCH                   SID_SEARCH_ITEM
#include <bf_sfx2/app.hxx>


#include <comphelper/classids.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "strings.hrc"
#include "glob.hrc"

#include "bf_sd/grdocsh.hxx"
#include "sdresid.hxx"

namespace binfilter
{

TYPEINIT1(SdGraphicDocShell, SdDrawDocShell);

SFX_IMPL_OBJECTFACTORY_LOD(SdGraphicDocShell, sdraw, SvGlobalName(BF_SO3_SDRAW_CLASSID), Sd)

SdGraphicDocShell::SdGraphicDocShell(SfxObjectCreateMode eMode, BOOL bDataObject, DocumentType eInDocType)
: SdDrawDocShell(eMode, bDataObject, eInDocType)
{
    SetStyleFamily( 2 );
}

SdGraphicDocShell::~SdGraphicDocShell()
{
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
