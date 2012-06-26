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


#define _SVTOOLS_SVDDE_DDEWRAP_CXX_

#if defined _MSC_VER
#pragma warning(push, 1)
#endif
#include <windows.h>
#if defined _MSC_VER
#pragma warning(pop)
#endif
#include "ddewrap.hxx"

namespace binfilter
{

//------------------------------------------------------------------------

HSZ WINAPI DdeCreateStringHandleW_9x( DWORD idInst, LPCWSTR pszString, int )
{
    HSZ     hszResult;
    LPSTR   pszANSIString;
    int     nSize;

    nSize = pszString ? WideCharToMultiByte( CP_ACP, 0, pszString, -1, NULL, 0, NULL, NULL ) : 0;
    pszANSIString = nSize ? (LPSTR)HeapAlloc( GetProcessHeap(), 0, nSize * sizeof(CHAR) ) : NULL;

    if ( pszANSIString )
        WideCharToMultiByte( CP_ACP, 0, pszString, -1, pszANSIString, nSize, NULL, NULL );

    hszResult = DdeCreateStringHandleA( idInst, pszANSIString, CP_WINANSI );

    if ( pszANSIString )
        HeapFree( GetProcessHeap(), 0, pszANSIString );

    return hszResult;
}

//------------------------------------------------------------------------

DWORD WINAPI DdeQueryStringW_9x( DWORD idInst, HSZ hsz, LPWSTR pszString, DWORD cchMax, int )
{
    DWORD   dwResult;
    LPSTR   pszANSIString;

    pszANSIString = cchMax ? (LPSTR)HeapAlloc( GetProcessHeap(), 0, cchMax * sizeof(CHAR) ) : NULL;

    dwResult = DdeQueryStringA( idInst, hsz, pszANSIString, cchMax, CP_WINANSI );

    if ( dwResult && pszANSIString )
        MultiByteToWideChar( CP_ACP, 0, pszANSIString, -1, pszString, cchMax );

    if ( pszANSIString )
        HeapFree( GetProcessHeap(), 0, pszANSIString );

    return dwResult;
}

//------------------------------------------------------------------------

UINT WINAPI DdeInitializeW_9x( LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes )
{
    return DdeInitializeA( pidInst, pfnCallback, afCmd, ulRes );
}

//------------------------------------------------------------------------

#define DEFINE_WAPI_FUNC(func) \
func##_PROC lpfn##func = (LONG)GetVersion() >= 0 ? func : func##_9x;


DEFINE_WAPI_FUNC( DdeCreateStringHandleW );
DEFINE_WAPI_FUNC( DdeQueryStringW );
DEFINE_WAPI_FUNC( DdeInitializeW );

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
