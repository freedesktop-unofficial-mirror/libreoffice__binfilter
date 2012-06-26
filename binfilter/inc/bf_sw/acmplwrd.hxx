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
#ifndef _ACMPLWRD_HXX
#define _ACMPLWRD_HXX

#include <bf_svtools/bf_solar.h>


#define _SVSTDARR_STRINGSISORTDTOR
#include <bf_svtools/svstdarr.hxx>
namespace binfilter {

class SwDoc;
class SwAutoCompleteWord_Impl;
class SwAutoCompleteClient;

class SwAutoCompleteWord
{
    friend class SwAutoCompleteClient;

    SvStringsISortDtor aWordLst; // contains extended strings carrying source information
    SvPtrarr aLRULst;

    SwAutoCompleteWord_Impl* pImpl;
    USHORT nMaxCount, nMinWrdLen;
    BOOL bLockWordLst;

    void DocumentDying(const SwDoc& rDoc);
public:
    SwAutoCompleteWord( USHORT nWords = 500, USHORT nMWrdLen = 10 );
    ~SwAutoCompleteWord();

    BOOL InsertWord( const String& rWord, SwDoc& rDoc );



    USHORT Count() const { return aWordLst.Count(); }

    const String& operator[]( USHORT n ) const { return *aWordLst[ n ]; }

    BOOL IsLockWordLstLocked() const        { return bLockWordLst; }
    void SetLockWordLstLocked( BOOL bFlag ) { bLockWordLst = bFlag; }

    USHORT GetMaxCount() const              { return nMaxCount; }

    USHORT GetMinWordLen() const                { return nMinWrdLen; }

    const SvStringsISortDtor& GetWordList() const { return aWordLst; }
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
