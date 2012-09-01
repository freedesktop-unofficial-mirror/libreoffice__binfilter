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


#include <bf_sfx2/app.hxx>
#include <bf_svx/svxids.hrc>

#include <comphelper/classids.hxx>

#include "cmdid.h"
#include "swtypes.hxx"

// nur wegen des Itemtypes
#include "wdocsh.hxx"
#include "web.hrc"

namespace binfilter {

#define C2S(cChar) UniString::CreateFromAscii(cChar)

/*--------------------------------------------------------------------
    Beschreibung:   Alle Filter registrieren
 --------------------------------------------------------------------*/

// 4.0: 0xf0caa840, 0x7821, 0x11d0, 0xa4, 0xa7, 0x0, 0xa0, 0x24, 0x9d, 0x57, 0xb1, Sw)
// 5.0: 0xc20cf9d2, 0x85ae, 0x11d1, 0xaa, 0xb4, 0x0, 0x60, 0x97, 0xda, 0x56, 0x1a

SFX_IMPL_OBJECTFACTORY_LOD(SwWebDocShell, SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU, /*swriter4/web,*/ \
            SvGlobalName(BF_SO3_SWWEB_CLASSID), Sw)
/*{
    ::RegisterWebFilterInSfxFactory( (SfxObjectFactory&)Factory(), RC_WEB_ICON );
} */


TYPEINIT1(SwWebDocShell, SwDocShell);

SwWebDocShell::SwWebDocShell(SfxObjectCreateMode eMode ) :
SwDocShell(eMode),
nSourcePara(0)
{
}

SwWebDocShell::~SwWebDocShell()
{
}






}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
