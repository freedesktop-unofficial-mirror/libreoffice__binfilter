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

#ifndef NF_NUMHEAD_HXX
#define NF_NUMHEAD_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/stream.hxx>

namespace binfilter
{

// -----------------------------------------------------------------------

        //  "Automatischer" Record-Header mit Groessenangabe

/*                      wird fuer SvNumberFormatter nicht gebraucht
class SvNumReadHeader
{
private:
    SvStream&   rStream;
    ULONG       nDataEnd;

public:
    SvNumReadHeader(SvStream& rNewStream);
    ~SvNumReadHeader();

    ULONG   BytesLeft() const;
};

class SvNumWriteHeader
{
private:
    SvStream&   rStream;
    ULONG       nDataPos;
    ULONG       nDataSize;

public:
    SvNumWriteHeader(SvStream& rNewStream, ULONG nDefault = 0);
    ~SvNumWriteHeader();
};

*/

        //  Header mit Groessenangaben fuer mehrere Objekte

class ImpSvNumMultipleReadHeader
{
private:
    SvStream&       rStream;
    char*           pBuf;
    SvMemoryStream* pMemStream;
    ULONG           nEndPos;
    ULONG           nEntryEnd;

public:
    ImpSvNumMultipleReadHeader(SvStream& rNewStream);
    ~ImpSvNumMultipleReadHeader();

    void    StartEntry();
    void    EndEntry();
    ULONG   BytesLeft() const;

    static void Skip( SvStream& );      // komplett ueberspringen
};

}

#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
