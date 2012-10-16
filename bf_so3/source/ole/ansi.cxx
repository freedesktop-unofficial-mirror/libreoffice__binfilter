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


#define NOMACROREDIRECT
#include "soole.h"

namespace binfilter {

#ifdef WIN32ANSI


/*
 * ConvertStringAlloc
 *
 * Purpose:
 *  Allocates memory using the task allocator.  Used internally
 *  in this file.
 */

HRESULT ConvertStringAlloc(ULONG ulSize, void **ppv)
    {
    HRESULT     hr;
    IMalloc    *pIMalloc;

    if (NULL==ppv)
        return ResultFromScode(E_INVALIDARG);

    hr=CoGetMalloc(MEMCTX_TASK, &pIMalloc);

    if (FAILED(hr))
        return hr;

    *ppv=pIMalloc->Alloc(ulSize);
    pIMalloc->Release();

    return (NULL==*ppv) ? ResultFromScode(E_OUTOFMEMORY) : NOERROR;
    }



/*
 * StarObject_ConvertStringToANSI
 *
 * Purpose:
 *  Converts the string in pszW to ANSI, allocating the
 *  output buffer pointed to by *ppszA on output.  The
 *  string is allocated with COM's task allocator.
 *
 */

STDAPI StarObject_ConvertStringToANSI(LPCWSTR pszW, LPSTR *ppszA)
    {
    ULONG   cch;
    HRESULT hr;

    //If input is NULL then just return the same
    if (NULL==pszW)
        {
        *ppszA=NULL;
        return NOERROR;
        }

    cch=wcslen(pszW)+1;

    hr=ConvertStringAlloc(cch, (void **)ppszA);

    if (FAILED(hr))
        return hr;

    WideCharToMultiByte(CP_ACP, 0, pszW, -1, *ppszA, cch, NULL, NULL);
    return NOERROR;
    }




/*
 * StarObject_StringFromCLSID
 */

STDAPI StarObject_StringFromCLSID(REFCLSID clsID, LPSTR *ppszCLSID)
    {
    LPWSTR  psz;
    HRESULT hr;

    if (NULL==ppszCLSID)
        return ResultFromScode(E_INVALIDARG);

    hr=StringFromCLSID(clsID, &psz);

    if (FAILED(hr))
        return hr;

    hr=StarObject_ConvertStringToANSI(psz, ppszCLSID);
    CoTaskMemFree((void *)psz);
    return hr;
    }



/*
 * StarObject_StringFromGUID2
 */

STDAPI StarObject_StringFromGUID2(REFGUID guid, LPSTR pszGUID, int cch)
    {
    LPSTR   psz;
    HRESULT hr;

    if (NULL==pszGUID)
        return ResultFromScode(E_INVALIDARG);

    hr=StarObject_StringFromCLSID(guid, &psz);

    if (FAILED(hr))
        return hr;

    lstrcpyn(pszGUID, psz, cch);
    CoTaskMemFree((void *)psz);
    return hr;
    }





/*
 * StarObject_ProgIDFromCLSID
 */

STDAPI StarObject_ProgIDFromCLSID(REFCLSID clsID, LPSTR *ppszProgID)
    {
    LPWSTR  psz;
    HRESULT hr;

    if (NULL==ppszProgID)
        return ResultFromScode(E_INVALIDARG);

    hr=ProgIDFromCLSID(clsID, &psz);

    if (FAILED(hr))
        return hr;

    hr=StarObject_ConvertStringToANSI(psz, ppszProgID);
    CoTaskMemFree(psz);
    return hr;
    }




/*
 * StarObject_ReadFmtUserTypeStg
 * StarObject_WriteFmtUserTypeStg
 */

STDAPI StarObject_ReadFmtUserTypeStg(IStorage *pIStorage
    , CLIPFORMAT *pcf, LPSTR *ppszUserType)
    {
    HRESULT     hr;
    LPOLESTR    pszUserType;

    if (NULL==ppszUserType)
        return ResultFromScode(E_INVALIDARG);

    hr=ReadFmtUserTypeStg(pIStorage, pcf, &pszUserType);

    if (FAILED(hr))
        return hr;

    if (ppszUserType)
        {
        hr=StarObject_ConvertStringToANSI(pszUserType, ppszUserType);
        CoTaskMemFree(pszUserType);
        }

    return hr;
    }


STDAPI StarObject_WriteFmtUserTypeStg(IStorage *pIStorage, CLIPFORMAT cf
    , LPSTR pszUserType)
    {
    OLECHAR     szType[512];
    HRESULT     hr;

    if (NULL==pszUserType)
        return ResultFromScode(E_INVALIDARG);

    MultiByteToWideChar(CP_ACP, 0, pszUserType, -1, szType, 512);
    hr=WriteFmtUserTypeStg(pIStorage, cf, szType);

    return hr;
    }



/*
 * StarObject_StgIsStorageFile
 * StarObject_StgCreateDocfile
 * StarObject_StgOpenStorage
 */

STDAPI StarObject_StgIsStorageFile(LPCSTR pszName)
    {
    OLECHAR     szTemp[MAX_PATH];

    MultiByteToWideChar(CP_ACP, 0, pszName, -1
        , szTemp, MAX_PATH);
    return StgIsStorageFile(szTemp);
    }



STDAPI StarObject_StgCreateDocfile(LPCSTR pszNameA, DWORD grfMode
    , DWORD reserved, IStorage **ppIStorage)
    {
    OLECHAR     szTemp[MAX_PATH];
    LPOLESTR    pszName;

    *ppIStorage=NULL;

    if (NULL!=pszNameA)
        {
        MultiByteToWideChar(CP_ACP, 0, pszNameA, -1
            , szTemp, MAX_PATH);
        pszName=szTemp;
        }
    else
        pszName=NULL;

    return StgCreateDocfile(pszName, grfMode, reserved
        , ppIStorage);
    }



STDAPI StarObject_StgOpenStorage(LPCSTR pszNameA, IStorage *pStgPri
    , DWORD grfMode, SNB snbEx, DWORD reserved
    , IStorage * *ppIStorage)
    {
    OLECHAR   szTemp[MAX_PATH];
    LPOLESTR  pszName;

    *ppIStorage=NULL;

    if (NULL!=pszNameA)
        {
        MultiByteToWideChar(CP_ACP, 0, pszNameA, -1
            , szTemp, MAX_PATH);
        pszName= szTemp;
        }
    else
        pszName=NULL;

    return StgOpenStorage(pszName, pStgPri, grfMode, snbEx
        , reserved, ppIStorage);
    }




/*
 * StarObject_CreateFileMoniker
 * StarObject_CreateItemMoniker
 * StarObject_MkParseDisplayName
 */

STDAPI StarObject_CreateFileMoniker(LPCSTR pszPathNameA, LPMONIKER *ppmk)
    {
    OLECHAR     szTemp[MAX_PATH];

    if (NULL==ppmk)
        return ResultFromScode(E_INVALIDARG);

    *ppmk=NULL;

    MultiByteToWideChar(CP_ACP, 0, pszPathNameA, -1
        , szTemp, MAX_PATH);

    return CreateFileMoniker(szTemp, ppmk);
    }


STDAPI StarObject_CreateItemMoniker(LPCSTR pszDelimA, LPCSTR pszItemA
    , LPMONIKER *ppmk)
    {
    OLECHAR     szItem[MAX_PATH];   //Some assumptions about string length
    OLECHAR     szDelim[20];

    if (NULL==ppmk)
        return ResultFromScode(E_INVALIDARG);

    *ppmk=NULL;

    MultiByteToWideChar(CP_ACP, 0, pszItemA, -1
        , szItem, MAX_PATH);
    MultiByteToWideChar(CP_ACP, 0, pszDelimA, -1
        , szDelim, 20);

    return CreateItemMoniker(szDelim, szItem, ppmk);
    }


STDAPI StarObject_MkParseDisplayName(LPBC pbc, LPCSTR pszUserNameA
    , ULONG *pchEaten, LPMONIKER *ppmk)
    {
    OLECHAR     szTemp[512];    //Assumption on string length

    if (NULL==ppmk)
        return ResultFromScode(E_INVALIDARG);

    *ppmk=NULL;

    MultiByteToWideChar(CP_ACP, 0, pszUserNameA, -1
        , szTemp, 512);

    return MkParseDisplayName(pbc, szTemp, pchEaten, ppmk);
    }



/*
 * StarObject_OleCreateLinkToFile
 * StarObject_OleCreateFromFile
 */

STDAPI StarObject_OleCreateLinkToFile(LPCSTR lpszFileName, REFIID riid
    , DWORD renderopt, LPFORMATETC lpFormatEtc
    , LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID *ppvObj)
    {
    OLECHAR     szFile[512];    //Assumption on string length

    MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, szFile, 512);
    return OleCreateLinkToFile(szFile, riid, renderopt, lpFormatEtc
        , pClientSite, pStg, ppvObj);
    }



STDAPI StarObject_OleCreateFromFile(REFCLSID rclsid, LPCSTR lpszFileName
    , REFIID riid, DWORD renderopt, LPFORMATETC lpFormatEtc
    , LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID *ppvObj)
    {
    OLECHAR     szFile[512];    //Assumption on string length

    MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, szFile, 512);
    return OleCreateFromFile(rclsid, szFile, riid, renderopt, lpFormatEtc
        , pClientSite, pStg, ppvObj);
    }

#else

//Do-nothing functions so we can at least export them.

#ifndef WIN32
STDAPI StarObject_ConvertStringToANSI(LPCSTR a, LPSTR *b) {return NOERROR;}
#else
STDAPI StarObject_ConvertStringToANSI(LPCWSTR a, LPSTR *b) {return NOERROR;}
#endif
STDAPI StarObject_StringFromCLSID(REFCLSID a, LPSTR *b) {return NOERROR;}
STDAPI StarObject_StringFromGUID2(REFGUID a, LPSTR b, int c) {return NOERROR;}
STDAPI StarObject_ProgIDFromCLSID(REFCLSID a, LPSTR *b) {return NOERROR;}

STDAPI StarObject_ReadFmtUserTypeStg(IStorage *a, CLIPFORMAT *b, LPSTR *c) {return NOERROR;}
STDAPI StarObject_WriteFmtUserTypeStg(IStorage *a, CLIPFORMAT b, LPSTR c) {return NOERROR;}

STDAPI StarObject_StgIsStorageFile(LPCSTR a) {return NOERROR;}
STDAPI StarObject_StgCreateDocfile(LPCSTR a, DWORD b, DWORD c, IStorage ** d) {return NOERROR;}
STDAPI StarObject_StgOpenStorage(LPCSTR a, IStorage *b, DWORD c, SNB d
           , DWORD e, IStorage **f) {return NOERROR;}

STDAPI StarObject_CreateFileMoniker(LPCSTR, LPMONIKER *) {return NOERROR;}
STDAPI StarObject_CreateItemMoniker(LPCSTR, LPCSTR, LPMONIKER *) {return NOERROR;}
STDAPI StarObject_MkParseDisplayName(LPBC, LPCSTR, ULONG *, LPMONIKER *) {return NOERROR;}

STDAPI StarObject_OleCreateLinkToFile(LPCOLESTR, REFIID, DWORD, LPFORMATETC
    , LPOLECLIENTSITE, LPSTORAGE, LPVOID *) {return NOERROR;}

STDAPI StarObject_OleCreateFromFile(REFCLSID, LPCOLESTR, REFIID
    , DWORD, LPFORMATETC, LPOLECLIENTSITE, LPSTORAGE, LPVOID *) {return NOERROR;}


#endif

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
