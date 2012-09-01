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

#include <hintids.hxx>
#include <osl/diagnose.h>
#include <fmthbsh.hxx>
namespace binfilter {


/*************************************************************************
|*
|*    class SwFmtHardBlank
|*
|*    Beschreibung      Dokument 1.20
|*
*************************************************************************/

/*N*/ SwFmtHardBlank::SwFmtHardBlank( sal_Unicode cCh, BOOL bCheck )
/*N*/   : SfxPoolItem( RES_TXTATR_HARDBLANK ),
/*N*/   cChar( cCh )
/*N*/ {
/*N*/   OSL_ENSURE( !bCheck || (' ' != cCh && '-' != cCh),
/*N*/           "Invalid character for the HardBlank attribute - "
/*N*/           "must be a normal unicode character" );
        (void) bCheck; // avoid warnings
/*N*/ }



/*************************************************************************
|*
|*    class SwFmtSoftHyph
|*
|*    Beschreibung      Dokument 1.20
|*
*************************************************************************/

/*N*/ SwFmtSoftHyph::SwFmtSoftHyph()
/*N*/   : SfxPoolItem( RES_TXTATR_SOFTHYPH )
/*N*/ {
/*N*/ }




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
