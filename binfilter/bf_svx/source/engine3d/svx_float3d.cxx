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

#include <bf_sfx2/dispatch.hxx>

#include <bf_sfx2/dockwin.hxx>

#include <bf_svx/f3dchild.hxx>

#include "float3d.hrc"
namespace binfilter {

SFX_IMPL_DOCKINGWINDOW( Svx3DChildWindow, SID_3D_WIN )

/*************************************************************************
|*
|* Ableitung vom SfxChildWindow als "Behaelter" fuer Effekte
|*
\************************************************************************/
Svx3DChildWindow::Svx3DChildWindow(
    Window* pParent,
    USHORT nId,
    SfxBindings* pBindings,
    SfxChildWinInfo* pInfo
) : SfxChildWindow( pParent, nId )
{
    DBG_BF_ASSERT(0, "STRIP");  // CONSTRUCTOR
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
