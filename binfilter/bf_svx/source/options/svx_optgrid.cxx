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

#define _SVX_OPTGRID_CXX

#include "svxids.hrc"
#include "optgrid.hxx"
#include "dialogs.hrc"
namespace binfilter {

/*--------------------------------------------------------------------
    Beschreibung: Rastereinstellungen Ctor
 --------------------------------------------------------------------*/

/*N*/ SvxOptionsGrid::SvxOptionsGrid() :
/*N*/   nFldDrawX       ( 100 ),
/*N*/   nFldDivisionX   ( 0 ),
/*N*/   nFldDrawY       ( 100 ),
/*N*/   nFldDivisionY   ( 0 ),
/*N*/   nFldSnapX       ( 100 ),
/*N*/   nFldSnapY       ( 100 ),
/*N*/   bUseGridsnap    ( 0 ),
/*N*/   bSynchronize    ( 1 ),
/*N*/   bGridVisible    ( 0 ),
/*N*/   bEqualGrid      ( 1 )
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Rastereinstellungen Dtor
 --------------------------------------------------------------------*/

/*N*/ SvxOptionsGrid::~SvxOptionsGrid()
/*N*/ {
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
