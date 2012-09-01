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
#ifndef _SWGPAR_HXX
#define _SWGPAR_HXX

#include <bf_svtools/bf_solar.h>

class UniString;
class SvStream;
namespace binfilter {


class SwDoc;
class SwPaM;
class SwSwgReader;


class SfxDocumentInfo;

enum SwgReadOptions {
    SWGRD_CHARFMTS      = 0x0001,       // Zeichenvorlagen
    SWGRD_FRAMEFMTS     = 0x0002,       // Rahmenvorlagen
    SWGRD_PARAFMTS      = 0x0004,       // Absatzvorlagen
    SWGRD_PAGEFMTS      = 0x0008,       // Seitenvorlagen
    SWGRD_MACROS        = 0x0010,       // globale Makros
    SWGRD_NUMRULES      = 0x0020,       // globale Numerierungsregeln

    SWGRD_FORCE         = 0x1000,       // Vorlagen immer einlesen

    SWGRD_NORMAL        = 0x00FF        // alles (Normalfall)
};

class SwSwgParser
{
private:
    SwSwgReader* pRdr;
public:
    ULONG  CallParser( USHORT = SWGRD_NORMAL );
    BOOL NeedsPasswd();
    BOOL CheckPasswd( const UniString& );

    SwSwgParser( SwDoc *pSwDoc, const SwPaM* pSwPaM,
                 SvStream *pIstream, const UniString& rFileName, //$ istream
                 BOOL bNewDoc=TRUE );
    SwSwgParser( SvStream *pIstream ); //$ istream
    ~SwSwgParser();
};

} //namespace binfilter
#endif // _SWGPAR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
