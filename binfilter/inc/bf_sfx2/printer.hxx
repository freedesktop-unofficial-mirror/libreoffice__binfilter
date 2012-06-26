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
#ifndef _SFX_PRINTER_HXX
#define _SFX_PRINTER_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/print.hxx>
namespace binfilter {
class SfxItemSet;

class SfxFont;
class SfxTabPage;

struct SfxPrinter_Impl;

#define SFX_RANGE_NOTSET    ((USHORT)0xFFFF)

#define SFX_PRINTER_PRINTER          1  // ohne JOBSETUP => temporaer
#define SFX_PRINTER_JOBSETUP         2
#define SFX_PRINTER_OPTIONS          4
#define SFX_PRINTER_CHG_ORIENTATION  8
#define SFX_PRINTER_CHG_SIZE        16
#define SFX_PRINTER_ALL             31

#define SFX_PRINTER_CHG_ORIENTATION_FLAG  3
#define SFX_PRINTER_CHG_SIZE_FLAG         4

// class SfxFontSizeInfo -------------------------------------------------


// class SfxFont ---------------------------------------------------------

class SfxFont
{
private:
    rtl::OUString           aName;
    FontFamily              eFamily;
    FontPitch               ePitch;
    CharSet                 eCharSet;

    SfxFont&                operator=(const SfxFont& rFont); // not implemented

public:
    SfxFont( const FontFamily eFam,
             const rtl::OUString& aName,
             const FontPitch eFontPitch = PITCH_DONTKNOW,
             const CharSet eFontCharSet = RTL_TEXTENCODING_DONTKNOW );
    // ZugriffsMethoden:
    inline const rtl::OUString& GetName() const { return aName; }
    inline FontFamily       GetFamily() const { return eFamily; }
    inline FontPitch        GetPitch() const { return ePitch; }
    inline CharSet          GetCharSet() const { return eCharSet; }
};

// class SfxPrinter ------------------------------------------------------

class SfxPrinter : public Printer
{
private:
    JobSetup                aOrigJobSetup;
    SfxItemSet*             pOptions;
    SfxPrinter_Impl*        pImpl;
    BOOL                    bKnown;


public:
                            SfxPrinter( SfxItemSet *pTheOptions );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const rtl::OUString &rPrinterName );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const JobSetup &rTheOrigJobSetup );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const rtl::OUString &rPrinterName,
                                        const JobSetup &rTheOrigJobSetup );
                            ~SfxPrinter();


    static SfxPrinter*      Create( SvStream &rStream, SfxItemSet *pOptions );
    SvStream&               Store( SvStream &rStream ) const { return rStream; }


    const SfxItemSet&       GetOptions() const { return *pOptions; }
    void                    SetOptions( const SfxItemSet &rNewOptions );


    BOOL                    IsKnown() const { return bKnown; }
    BOOL                    IsOriginal() const { return bKnown; }

};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
