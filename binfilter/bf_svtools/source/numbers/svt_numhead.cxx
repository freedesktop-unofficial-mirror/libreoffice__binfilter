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

#include <tools/debug.hxx>

#include "numhead.hxx"

//      ID's fuer Dateien:
#define SV_NUMID_SIZES                      0x4200

namespace binfilter
{

// STATIC DATA -----------------------------------------------------------

//SEG_EOFGLOBALS()

// =======================================================================
/*                              wird fuer SvNumberformatter nicht gebraucht
//#pragma SEG_FUNCDEF(numhead_01)

SvNumReadHeader::SvNumReadHeader(SvStream& rNewStream) :
    rStream( rNewStream )
{
    ULONG nDataSize;
    rStream >> nDataSize;
    nDataEnd = rStream.Tell() + nDataSize;
}

//#pragma SEG_FUNCDEF(numhead_02)

SvNumReadHeader::~SvNumReadHeader()
{
    ULONG nReadEnd = rStream.Tell();
    DBG_ASSERT( nReadEnd <= nDataEnd, "zuviele Bytes gelesen" );
    if ( nReadEnd != nDataEnd )
        rStream.Seek(nDataEnd);                     // Rest ueberspringen
}

//#pragma SEG_FUNCDEF(numhead_03)

ULONG SvNumReadHeader::BytesLeft() const
{
    ULONG nReadEnd = rStream.Tell();
    if (nReadEnd <= nDataEnd)
        return nDataEnd-nReadEnd;

    OSL_FAIL("Fehler bei SvNumReadHeader::BytesLeft");
    return 0;
}

// -----------------------------------------------------------------------

//#pragma SEG_FUNCDEF(numhead_04)

SvNumWriteHeader::SvNumWriteHeader(SvStream& rNewStream, ULONG nDefault) :
    rStream( rNewStream )
{
    nDataSize = nDefault;
    rStream << nDataSize;
    nDataPos = rStream.Tell();
}

//#pragma SEG_FUNCDEF(numhead_05)

SvNumWriteHeader::~SvNumWriteHeader()
{
    ULONG nPos = rStream.Tell();

    if ( nPos - nDataPos != nDataSize )             // Default getroffen?
    {
        nDataSize = nPos - nDataPos;
        rStream.Seek(nDataPos - sizeof(sal_uInt32));
        rStream << nDataSize;                       // Groesse am Anfang eintragen
        rStream.Seek(nPos);
    }
}
*/

// =======================================================================

//#pragma SEG_FUNCDEF(numhead_06)

//! mit Skip() synchron
ImpSvNumMultipleReadHeader::ImpSvNumMultipleReadHeader(SvStream& rNewStream) :
    rStream( rNewStream )
{
    sal_uInt32 nDataSize;
    rStream >> nDataSize;
    ULONG nDataPos = rStream.Tell();
    nEntryEnd = nDataPos;

    rStream.SeekRel(nDataSize);
    USHORT nID;
    rStream >> nID;
    if (nID != SV_NUMID_SIZES)
    {
        OSL_FAIL("SV_NUMID_SIZES nicht gefunden");
    }
    sal_uInt32 nSizeTableLen;
    rStream >> nSizeTableLen;
    pBuf = new char[nSizeTableLen];
    rStream.Read( pBuf, nSizeTableLen );
    pMemStream = new SvMemoryStream( pBuf, nSizeTableLen, STREAM_READ );

    nEndPos = rStream.Tell();
    rStream.Seek( nDataPos );
}

//#pragma SEG_FUNCDEF(numhead_07)

ImpSvNumMultipleReadHeader::~ImpSvNumMultipleReadHeader()
{
    DBG_ASSERT( pMemStream->Tell() == pMemStream->GetEndOfData(),
                "Sizes nicht vollstaendig gelesen" );
    delete pMemStream;
    delete [] pBuf;

    rStream.Seek(nEndPos);
}

//! mit ctor synchron
// static
void ImpSvNumMultipleReadHeader::Skip( SvStream& rStream )
{
    sal_uInt32 nDataSize;
    rStream >> nDataSize;
    rStream.SeekRel( nDataSize );
    USHORT nID;
    rStream >> nID;
    if ( nID != SV_NUMID_SIZES )
    {
        OSL_FAIL("SV_NUMID_SIZES nicht gefunden");
    }
    sal_uInt32 nSizeTableLen;
    rStream >> nSizeTableLen;
    rStream.SeekRel( nSizeTableLen );
}

//#pragma SEG_FUNCDEF(numhead_08)

void ImpSvNumMultipleReadHeader::EndEntry()
{
    ULONG nPos = rStream.Tell();
    DBG_ASSERT( nPos <= nEntryEnd, "zuviel gelesen" );
    if ( nPos != nEntryEnd )
        rStream.Seek( nEntryEnd );          // Rest ueberspringen
}

//#pragma SEG_FUNCDEF(numhead_0d)

void ImpSvNumMultipleReadHeader::StartEntry()
{
    ULONG nPos = rStream.Tell();
    sal_uInt32 nEntrySize;
    (*pMemStream) >> nEntrySize;

    nEntryEnd = nPos + nEntrySize;
}

//#pragma SEG_FUNCDEF(numhead_09)

ULONG ImpSvNumMultipleReadHeader::BytesLeft() const
{
    ULONG nReadEnd = rStream.Tell();
    if (nReadEnd <= nEntryEnd)
        return nEntryEnd-nReadEnd;

    OSL_FAIL("Fehler bei ImpSvNumMultipleReadHeader::BytesLeft");
    return 0;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
