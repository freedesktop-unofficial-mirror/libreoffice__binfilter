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

#define _SVX_PARAITEM_HXX
#define _SVX_TEXTITEM_HXX

#include <bf_sfx2/progress.hxx>
#include <swwait.hxx>

#include <horiornt.hxx>

#include <fesh.hxx>
#include <doc.hxx>
#include <rootfrm.hxx>
#include <pagefrm.hxx>
#include <viewimp.hxx>
#include <frmtool.hxx>
#include <viewopt.hxx>
#include <dview.hxx>
#include <swregion.hxx>
#include <hints.hxx>
#include <txtfrm.hxx>
#include <mdiexp.hxx>
#include <fntcache.hxx>
#include <docsh.hxx>
#include <pagedesc.hxx>
#include <accessibilityoptions.hxx>
#include <statstr.hrc>
#include <shellres.hxx>
namespace binfilter {

ShellResource *ViewShell::pShellRes = 0;
Window *ViewShell::pCareWindow = 0;

bool bInSizeNotify = FALSE;

/*N*/ TYPEINIT0(ViewShell);

/*N*/ OutputDevice& ViewShell::GetRefDev() const
/*N*/ {
/*N*/     OutputDevice* pTmpOut = 0;
/*N*/     if ( GetWin() && IsBrowseMode() &&
/*N*/          ! GetViewOptions()->IsPrtFormat() )
/*N*/         pTmpOut = GetWin();
/*N*/     else if ( 0 != mpTmpRef )
/*N*/         pTmpOut = mpTmpRef;
/*N*/     else
/*N*/         pTmpOut = &GetDoc()->GetRefDev();
/*N*/
/*N*/     return *pTmpOut;
/*N*/ }

/*N*/ void ViewShell::DrawSelChanged(SdrView*)
/*N*/ {
/*N*/ }

/*N*/ BOOL ViewShell::IsBrowseMode() const
/*N*/ {
/*N*/   return GetDoc()->IsBrowseMode();
/*N*/ }

ShellResource* ViewShell::GetShellRes()
{
    if ( !pShellRes )
        pShellRes = new ShellResource();
    return pShellRes;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
