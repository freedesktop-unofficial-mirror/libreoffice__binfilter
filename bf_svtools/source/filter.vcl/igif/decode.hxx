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

#ifndef _DECODE_HXX
#define _DECODE_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/bmpacc.hxx>

namespace binfilter
{

struct GIFLZWTableEntry;

class GIFLZWDecompressor
{
    GIFLZWTableEntry*   pTable;
    HPBYTE              pOutBuf;
    HPBYTE              pOutBufData;
    HPBYTE              pBlockBuf;
    ULONG               nInputBitsBuf;
    USHORT              nTableSize;
    USHORT              nClearCode;
    USHORT              nEOICode;
    USHORT              nCodeSize;
    USHORT              nOldCode;
    USHORT              nOutBufDataLen;
    USHORT              nInputBitsBufSize;
    BOOL                bEOIFound;
    BYTE                nDataSize;
    BYTE                nBlockBufSize;
    BYTE                nBlockBufPos;

    void                AddToTable(USHORT nPrevCode, USHORT nCodeFirstData);
    BOOL                ProcessOneCode();


public:

                        GIFLZWDecompressor( BYTE cDataSize );
                        ~GIFLZWDecompressor();

    HPBYTE              DecompressBlock( HPBYTE pSrc, BYTE cBufSize, ULONG& rCount, BOOL& rEOI );
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
