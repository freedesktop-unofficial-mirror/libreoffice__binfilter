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

#ifdef WIN

#include <svwin.h>

namespace binfilter
{

// Statische DLL-Verwaltungs-Variablen
static HINSTANCE hDLLInst = 0;      // HANDLE der DLL


/***************************************************************************
|*
|*    LibMain()
|*
|*    Beschreibung       Initialisierungsfunktion der DLL
|*
***************************************************************************/

extern "C" int CALLBACK LibMain( HINSTANCE hDLL, WORD, WORD nHeap, LPSTR )
{
#ifndef WNT
    if ( nHeap )
        UnlockData( 0 );
#endif

    hDLLInst = hDLL;

    return TRUE;
}

/***************************************************************************
|*
|*    WEP()
|*
|*    Beschreibung      DLL-Deinitialisierung
|*
***************************************************************************/

extern "C" int CALLBACK WEP( int )
{
    return 1;
}

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
