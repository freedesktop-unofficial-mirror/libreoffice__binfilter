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

#include <vcl/svapp.hxx>

#include <flbytes.hxx>

#ifndef _SVSTDARR_ULONGS_DECL
#define _SVSTDARR_ULONGS
#include <bf_svtools/svstdarr.hxx>
#undef _SVSTDARR_ULONGS
#endif

#include <bf_so3/ref.hxx>

//============================================================================
namespace binfilter
{

inline ULONG MyMin( long a, long b )
{
    return Max( long( Min(  a ,  b ) ), 0L );
}

//============================================================================
SV_DECL_REF_LIST(SvLockBytes,SvLockBytes*)
SV_IMPL_REF_LIST(SvLockBytes,SvLockBytes*)

//============================================================================
//
//  SvSyncLockBytes
//
//============================================================================

TYPEINIT1(SvSyncLockBytes, SvOpenLockBytes);

//============================================================================
// virtual
ErrCode SvSyncLockBytes::ReadAt(ULONG nPos, void * pBuffer, ULONG nCount,
                                ULONG * pRead) const
{
    for (ULONG nReadTotal = 0;;)
    {
        ULONG nReadCount = 0;
        ErrCode nError = m_xAsyncLockBytes->ReadAt(nPos, pBuffer, nCount,
                                                   &nReadCount);
        nReadTotal += nReadCount;
        if (nError != ERRCODE_IO_PENDING || !IsSynchronMode())
        {
            if (pRead)
                *pRead = nReadTotal;
            return nError;
        }
        nPos += nReadCount;
        pBuffer = static_cast< sal_Char * >(pBuffer) + nReadCount;
        nCount -= nReadCount;
        Application::Yield();
    }
}

//============================================================================
// virtual
ErrCode SvSyncLockBytes::WriteAt(ULONG nPos, const void * pBuffer,
                                 ULONG nCount, ULONG * pWritten)
{
    for (ULONG nWrittenTotal = 0;;)
    {
        ULONG nWrittenCount = 0;
        ErrCode nError = m_xAsyncLockBytes->WriteAt(nPos, pBuffer, nCount,
                                                    &nWrittenCount);
        nWrittenTotal += nWrittenCount;
        if (nError != ERRCODE_IO_PENDING || !IsSynchronMode())
        {
            if (pWritten)
                *pWritten = nWrittenTotal;
            return nError;
        }
        nPos += nWrittenCount;
        pBuffer = static_cast< sal_Char const * >(pBuffer) + nWrittenCount;
        nCount -= nWrittenCount;
        Application::Yield();
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
