/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: printer.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:05:47 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SFX_PRINTER_HXX
#define _SFX_PRINTER_HXX

#ifndef _PRINT_HXX //autogen
#include <vcl/print.hxx>
#endif
class SfxItemSet;
namespace binfilter {

class SfxFont;
class SfxTabPage;

struct SfxPrinter_Impl;

#define SFX_RANGE_NOTSET    ((USHORT)0xFFFF)

// class SfxFontSizeInfo -------------------------------------------------


// class SfxFont ---------------------------------------------------------

class SfxFont
{
private:
    String                  aName;
    FontFamily              eFamily;
    FontPitch               ePitch;
    CharSet                 eCharSet;

    SfxFont&                operator=(const SfxFont& rFont); // not implemented

public:
    SfxFont( const FontFamily eFam,
             const String& aName,
             const FontPitch eFontPitch = PITCH_DONTKNOW,
             const CharSet eFontCharSet = RTL_TEXTENCODING_DONTKNOW );
    // ZugriffsMethoden:
    inline const String&    GetName() const { return aName; }
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
                                        const String &rPrinterName );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const JobSetup &rTheOrigJobSetup );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const String &rPrinterName,
                                        const JobSetup &rTheOrigJobSetup );
                            ~SfxPrinter();


    static SfxPrinter*      Create( SvStream &rStream, SfxItemSet *pOptions );
    SvStream&               Store( SvStream &rStream ) const;


    const SfxItemSet&       GetOptions() const { return *pOptions; }
    void                    SetOptions( const SfxItemSet &rNewOptions );


    BOOL                    IsKnown() const { return bKnown; }
    BOOL                    IsOriginal() const { return bKnown; }

    const SfxFont*          GetFontByName( const String &rFontName );

};

}//end of namespace binfilter
#endif
