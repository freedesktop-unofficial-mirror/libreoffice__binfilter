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
#ifndef _FLTINI_HXX
#define _FLTINI_HXX

#include <bf_svtools/bf_solar.h>


#include <shellio.hxx>
#include <tools/color.hxx>
namespace binfilter {

class SwNumRuleTbl;
class SwDoc;
class SwTxtNode;
class SwNodeNum;
class SwNumRule;
class SwNodeIndex;


// die speziellen Reader

class Sw6Reader: public Reader
{
    virtual ULONG Read( SwDoc &,SwPaM &,const String &);
};

 class W4WReader: public StgReader
 {
    String sVersion;
    USHORT nFilter;
    BOOL bStorageFlag;
    virtual ULONG Read(SwDoc &,SwPaM &,const String &);
    // wir wollen die Streams / Storages nicht geoeffnet haben
    virtual int SetStrmStgPtr();
 public:
    W4WReader() : StgReader(), nFilter(0), bStorageFlag(FALSE) {}
    virtual int GetReaderType();
    virtual void SetFltName( const String& rFltName );

    USHORT GetFilter() const { return nFilter; }
    const String& GetVersion() const { return sVersion; }
 };

#ifdef DEBUG_SH

class Internal_W4WReader: public W4WReader
{
    virtual ULONG Read(SwDoc &,SwPaM &,const String &);
};

#endif

class ExcelReader : public StgReader
{
    virtual ULONG Read(SwDoc &,SwPaM &,const String &);
public:
    virtual int GetReaderType();
};

class LotusReader : public Reader
{
    CharSet eCodeSet;
    virtual ULONG Read(SwDoc &,SwPaM &,const String &);
public:
};

#define SW_SV_BRUSH_25          0
#define SW_SV_BRUSH_50          1
#define SW_SV_BRUSH_75          2
#define SW_SV_BRUSH_NULL        3
#define SW_SV_BRUSH_SOLID       4
#define SW_SV_BRUSH_INVALID     5

Color   ConvertBrushStyle(const Color& rCol, const Color& rFillCol, BYTE nStyle);

// Get size of fly (if 'automatic' in WW) and check if not too small
void    CalculateFlySize( SfxItemSet& rFlySet, SwNodeIndex& rAnchor,
                          SwTwips nPageWidth );

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
