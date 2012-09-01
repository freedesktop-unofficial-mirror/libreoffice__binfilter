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

#include "decode.hxx"

namespace binfilter
{

// ------------------------------------------------------------------------

struct GIFLZWTableEntry
{
    GIFLZWTableEntry*   pPrev;
    GIFLZWTableEntry*   pFirst;
    BYTE                nData;
};

// ------------------------------------------------------------------------

GIFLZWDecompressor::GIFLZWDecompressor( BYTE cDataSize ) :
            nInputBitsBuf       ( 0 ),
            nOutBufDataLen      ( 0 ),
            nInputBitsBufSize   ( 0 ),
            bEOIFound           ( FALSE ),
            nDataSize           ( cDataSize )
{
    pTable = new GIFLZWTableEntry[ 4096 ];
    pOutBuf = new BYTE[ 4096 ];

    nClearCode = 1 << nDataSize;
    nEOICode = nClearCode + 1;
    nTableSize = nEOICode + 1;
    nCodeSize = nDataSize + 1;
    nOldCode = 0xffff;
    pOutBufData = pOutBuf + 4096;

    for( USHORT i = 0; i < nTableSize; i++ )
    {
        pTable[i].pPrev = NULL;
        pTable[i].pFirst = pTable + i;
        pTable[i].nData = (BYTE) i;
    }
}

// ------------------------------------------------------------------------

GIFLZWDecompressor::~GIFLZWDecompressor()
{
    delete[] pOutBuf;
    delete[] pTable;
}

// ------------------------------------------------------------------------

HPBYTE GIFLZWDecompressor::DecompressBlock( HPBYTE pSrc, BYTE cBufSize,
                                            ULONG& rCount, BOOL& rEOI )
{
    ULONG   nTargetSize = 4096;
    ULONG   nCount = 0;
    HPBYTE  pTarget = (HPBYTE) rtl_allocateMemory( nTargetSize );
    HPBYTE  pTmpTarget = pTarget;

    nBlockBufSize = cBufSize;
    nBlockBufPos = 0;
    pBlockBuf = pSrc;

    while( ProcessOneCode() )
    {
        nCount += nOutBufDataLen;

        if( nCount > nTargetSize )
        {
            ULONG   nNewSize = nTargetSize << 1;
            ULONG   nOffset = pTmpTarget - pTarget;
            HPBYTE  pTmp = (HPBYTE) rtl_allocateMemory( nNewSize );

            memcpy( pTmp, pTarget, nTargetSize );
            rtl_freeMemory( pTarget );

            nTargetSize = nNewSize;
            pTmpTarget = ( pTarget = pTmp ) + nOffset;
        }

        memcpy( pTmpTarget, pOutBufData, nOutBufDataLen );
        pTmpTarget += nOutBufDataLen;
        pOutBufData += nOutBufDataLen;
        nOutBufDataLen = 0;

        if ( bEOIFound )
            break;
    }

    rCount = nCount;
    rEOI = bEOIFound;

    return pTarget;
}

// ------------------------------------------------------------------------

void GIFLZWDecompressor::AddToTable( USHORT nPrevCode, USHORT nCodeFirstData )
{
    GIFLZWTableEntry* pE;

    if( nTableSize < 4096 )
    {
        pE = pTable + nTableSize;
        pE->pPrev = pTable + nPrevCode;
        pE->pFirst = pE->pPrev->pFirst;
        pE->nData = pTable[ nCodeFirstData ].pFirst->nData;
        nTableSize++;

        if ( ( nTableSize == (USHORT) (1 << nCodeSize) ) && ( nTableSize < 4096 ) )
            nCodeSize++;
    }
}

// ------------------------------------------------------------------------

BOOL GIFLZWDecompressor::ProcessOneCode()
{
    GIFLZWTableEntry*   pE;
    USHORT              nCode;
    BOOL                bRet = FALSE;
    BOOL                bEndOfBlock = FALSE;

    while( nInputBitsBufSize < nCodeSize )
    {
        if( nBlockBufPos >= nBlockBufSize )
        {
            bEndOfBlock = TRUE;
            break;
        }

        nInputBitsBuf |= ( (ULONG) pBlockBuf[ nBlockBufPos++ ] ) << nInputBitsBufSize;
        nInputBitsBufSize += 8;
    }

    if ( !bEndOfBlock )
    {
        // Einen Code aus dem Eingabe-Buffer holen:
        nCode = sal::static_int_cast< USHORT >(
            ( (USHORT) nInputBitsBuf ) & ( ~( 0xffff << nCodeSize ) ));
        nInputBitsBuf >>= nCodeSize;
        nInputBitsBufSize = nInputBitsBufSize - nCodeSize;

        if ( nCode < nClearCode )
        {
            if ( nOldCode != 0xffff )
                AddToTable( nOldCode, nCode );
        }
        else if ( ( nCode > nEOICode ) && ( nCode <= nTableSize ) )
        {
            if ( nCode == nTableSize )
                AddToTable( nOldCode, nOldCode );
            else
                AddToTable( nOldCode, nCode );
        }
        else
        {
            if ( nCode == nClearCode )
            {
                nTableSize = nEOICode + 1;
                nCodeSize = nDataSize + 1;
                nOldCode = 0xffff;
                nOutBufDataLen = 0;
            }
            else
                bEOIFound = TRUE;

            return TRUE;
        }

        nOldCode = nCode;

        // Zeichen(/-folge) des Codes nCode in den Ausgabe-Buffer schreiben:
        pE = pTable + nCode;
        do
        {
            nOutBufDataLen++;
            *(--pOutBufData) = pE->nData;
            pE = pE->pPrev;
        }
        while( pE );

        bRet = TRUE;
    }

    return bRet;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
