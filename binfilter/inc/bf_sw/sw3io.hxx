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
#ifndef _SW3IO_HXX
#define _SW3IO_HXX

#include <bf_svtools/bf_solar.h>

class UniString;

namespace binfilter {
class SvStorage;
class SvStrings;
class SvxMacroTableDtor;

class Sw3IoImp;
class SwPaM;
class SwDoc;

class SwgReaderOption;

#define DRAWING_STREAM_NAME     "DrawingLayer"

class Sw3Io
{
    friend class Sw3IoImp;
    Sw3IoImp* pImp;                 // Implementationsdaten

    // nur ueber diese beiden Klassen darf ein Load/Save erfolgen!!
    friend class Sw3Reader;
    friend class Sw3Writer;

    ULONG Load( SvStorage*, SwPaM* = NULL );

public:
    Sw3Io( SwDoc& );
   ~Sw3Io();
    Sw3IoImp* GetImp() { return pImp; }
    void  SetReadOptions( const SwgReaderOption& rOpt, BOOL bOverwrite=TRUE );

    void  HandsOff();

    // Erzeugen eines eindeutigen Streamnamens im gegebenen Storage
    static UniString UniqueName( SvStorage*, const sal_Char* pPrefix );

    // Ermitteln aller Sections eines Dokuments
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
