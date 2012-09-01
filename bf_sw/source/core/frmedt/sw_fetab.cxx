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

#define ITEMID_BOXINFO SID_ATTR_BORDER_INNER
#include <hintids.hxx>

#include <bf_svx/svxids.hrc>


#include <horiornt.hxx>

#include <fesh.hxx>
#include <doc.hxx>
#include <cntfrm.hxx>
#include <tabfrm.hxx>
#include <cellfrm.hxx>
#include <ndtxt.hxx>
#include <tabcol.hxx>
#include <viscrs.hxx>

#include <swerror.h>
namespace binfilter {

//siehe auch swtable.cxx
#define COLFUZZY 20L

/*N*/ SwTabCols *pLastCols   = 0;

/*N*/ void ClearFEShellTabCols()
/*N*/ {
/*N*/   DELETEZ( pLastCols );
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
