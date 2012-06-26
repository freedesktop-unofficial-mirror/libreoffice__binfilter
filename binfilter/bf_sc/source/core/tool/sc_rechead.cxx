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


#include <tools/debug.hxx>

#include "rechead.hxx"
#include "scerrors.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

// =======================================================================

/*N*/ ScReadHeader::ScReadHeader(SvStream& rNewStream) :
/*N*/   rStream( rNewStream )
/*N*/ {
/*N*/   sal_uInt32 nDataSize;
/*N*/   rStream >> nDataSize;
/*N*/   nDataEnd = rStream.Tell() + nDataSize;
/*N*/ }

/*N*/ ScReadHeader::~ScReadHeader()
/*N*/ {
/*N*/   ULONG nReadEnd = rStream.Tell();
/*N*/   DBG_ASSERT( nReadEnd <= nDataEnd, "zuviele Bytes gelesen" );
/*N*/   if ( nReadEnd != nDataEnd )
/*N*/   {
/*?*/       if ( rStream.GetError() == SVSTREAM_OK )
/*?*/           rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*?*/       rStream.Seek(nDataEnd);                     // Rest ueberspringen
/*N*/   }
/*N*/ }

/*N*/ ULONG ScReadHeader::BytesLeft() const
/*N*/ {
/*N*/   ULONG nReadEnd = rStream.Tell();
/*N*/   if (nReadEnd <= nDataEnd)
/*N*/       return nDataEnd-nReadEnd;
/*N*/
/*N*/   OSL_FAIL("Fehler bei ScReadHeader::BytesLeft");
/*N*/   return 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScWriteHeader::ScWriteHeader(SvStream& rNewStream, sal_uInt32 nDefault) :
/*N*/   rStream( rNewStream )
/*N*/ {
/*N*/   nDataSize = nDefault;
/*N*/   rStream << nDataSize;
/*N*/
/*N*/   nDataPos = rStream.Tell();
/*N*/ }

/*N*/ ScWriteHeader::~ScWriteHeader()
/*N*/ {
/*N*/   ULONG nPos = rStream.Tell();
/*N*/
/*N*/   if ( nPos - nDataPos != nDataSize )             // Default getroffen?
/*N*/   {
/*N*/       nDataSize = nPos - nDataPos;
/*N*/       rStream.Seek(nDataPos - sizeof(sal_uInt32));
/*N*/       rStream << nDataSize;                       // Groesse am Anfang eintragen
/*N*/       rStream.Seek(nPos);
/*N*/   }
/*N*/ }

// =======================================================================

/*N*/ ScMultipleReadHeader::ScMultipleReadHeader(SvStream& rNewStream) :
/*N*/   rStream( rNewStream )
/*N*/ {
/*N*/   sal_uInt32 nDataSize;
/*N*/   rStream >> nDataSize;
/*N*/   ULONG nDataPos = rStream.Tell();
/*N*/   nTotalEnd = nDataPos + nDataSize;
/*N*/   nEntryEnd = nTotalEnd;
/*N*/
/*N*/   rStream.SeekRel(nDataSize);
/*N*/   USHORT nID;
/*N*/   rStream >> nID;
/*N*/   if (nID != SCID_SIZES)
/*N*/   {
/*N*/       OSL_FAIL("SCID_SIZES nicht gefunden");
/*N*/       if ( rStream.GetError() == SVSTREAM_OK )
/*N*/           rStream.SetError( SVSTREAM_FILEFORMAT_ERROR );
/*N*/
/*N*/       //  alles auf 0, damit BytesLeft() wenigstens abbricht
/*N*/       pBuf = NULL; pMemStream = NULL;
/*N*/       nEntryEnd = nDataPos;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       sal_uInt32 nSizeTableLen;
/*N*/       rStream >> nSizeTableLen;
/*N*/       pBuf = new BYTE[nSizeTableLen];
/*N*/       rStream.Read( pBuf, nSizeTableLen );
/*N*/       pMemStream = new SvMemoryStream( (char*)pBuf, nSizeTableLen, STREAM_READ );
/*N*/   }
/*N*/
/*N*/   nEndPos = rStream.Tell();
/*N*/   rStream.Seek( nDataPos );
/*N*/ }

/*N*/ ScMultipleReadHeader::~ScMultipleReadHeader()
/*N*/ {
/*N*/   if ( pMemStream && pMemStream->Tell() != pMemStream->GetEndOfData() )
/*N*/   {
/*N*/       DBG_ERRORFILE( "Sizes nicht vollstaendig gelesen" );
/*N*/       if ( rStream.GetError() == SVSTREAM_OK )
/*N*/           rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*N*/   }
/*N*/   delete pMemStream;
/*N*/   delete[] pBuf;
/*N*/
/*N*/   rStream.Seek(nEndPos);
/*N*/ }

/*N*/ void ScMultipleReadHeader::EndEntry()
/*N*/ {
/*N*/   ULONG nPos = rStream.Tell();
/*N*/   DBG_ASSERT( nPos <= nEntryEnd, "zuviel gelesen" );
/*N*/   if ( nPos != nEntryEnd )
/*N*/   {
/*?*/       if ( rStream.GetError() == SVSTREAM_OK )
/*?*/           rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*?*/       rStream.Seek( nEntryEnd );          // Rest ueberspringen
/*N*/   }
/*N*/
/*N*/   nEntryEnd = nTotalEnd;          // den ganzen Rest, wenn kein StartEntry kommt
/*N*/ }

/*N*/ void ScMultipleReadHeader::StartEntry()
/*N*/ {
/*N*/   ULONG nPos = rStream.Tell();
/*N*/   sal_uInt32 nEntrySize;
/*N*/   (*pMemStream) >> nEntrySize;
/*N*/
/*N*/   nEntryEnd = nPos + nEntrySize;
/*N*/   DBG_ASSERT( nEntryEnd <= nTotalEnd, "zuviele Eintraege gelesen" );
/*N*/ }

/*N*/ ULONG ScMultipleReadHeader::BytesLeft() const
/*N*/ {
/*N*/   ULONG nReadEnd = rStream.Tell();
/*N*/   if (nReadEnd <= nEntryEnd)
/*N*/       return nEntryEnd-nReadEnd;
/*N*/
/*N*/   OSL_FAIL("Fehler bei ScMultipleReadHeader::BytesLeft");
/*N*/   return 0;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
