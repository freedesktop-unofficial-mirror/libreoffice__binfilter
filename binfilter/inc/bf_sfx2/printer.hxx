/*************************************************************************
 *
 *  $RCSfile: printer.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:26:23 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
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

//STRIP001 class SfxFontSizeInfo
//STRIP001 {
//STRIP001 private:
//STRIP001  static USHORT           pStaticSizes[];
//STRIP001  Size*                   pSizes;
//STRIP001  USHORT                  nSizes;
//STRIP001  BOOL                    bScalable;
//STRIP001
//STRIP001 public:
//STRIP001  SfxFontSizeInfo( const SfxFont& rFont, const OutputDevice& rDevice );
//STRIP001  ~SfxFontSizeInfo();
//STRIP001
//STRIP001  BOOL                    HasSize(const Size &rSize) const;
//STRIP001  BOOL                    IsScalable() const { return bScalable; }
//STRIP001
//STRIP001  USHORT                  SizeCount() const { return nSizes; }
//STRIP001  const Size&             GetSize( USHORT nNo ) const
//STRIP001                          { return pSizes[nNo]; }
//STRIP001 };

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

//STRIP001  void                    UpdateFonts_Impl();

public:
                            SfxPrinter( SfxItemSet *pTheOptions );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const String &rPrinterName );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const JobSetup &rTheOrigJobSetup );
                            SfxPrinter( SfxItemSet *pTheOptions,
                                        const String &rPrinterName,
                                        const JobSetup &rTheOrigJobSetup );
//STRIP001                          SfxPrinter( const SfxPrinter &rPrinter );
                            ~SfxPrinter();

//STRIP001  SfxPrinter*             Clone() const;

    static SfxPrinter*      Create( SvStream &rStream, SfxItemSet *pOptions );
    SvStream&               Store( SvStream &rStream ) const;

//STRIP001  const JobSetup&         GetOrigJobSetup() const { return aOrigJobSetup; }
//STRIP001  void                    SetOrigJobSetup( const JobSetup &rNewJobSetup );

    const SfxItemSet&       GetOptions() const { return *pOptions; }
    void                    SetOptions( const SfxItemSet &rNewOptions );

//STRIP001  void                    EnableRange( USHORT nRange );
//STRIP001  void                    DisableRange( USHORT nRange );
//STRIP001  BOOL                    IsRangeEnabled( USHORT nRange ) const;

    BOOL                    IsKnown() const { return bKnown; }
    BOOL                    IsOriginal() const { return bKnown; }

//STRIP001  USHORT                  GetFontCount();
//STRIP001  const SfxFont*          GetFont( USHORT nNo ) const;
    const SfxFont*          GetFontByName( const String &rFontName );

//STRIP001     BOOL                    InitJob( Window* pUIParent, BOOL bDocumentContainsTransparentObjects );
};

}//end of namespace binfilter
#endif
