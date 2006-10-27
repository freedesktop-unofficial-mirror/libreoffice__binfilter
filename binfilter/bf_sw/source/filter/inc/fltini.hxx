/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fltini.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:39:01 $
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
#ifndef _FLTINI_HXX
#define _FLTINI_HXX


#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
namespace binfilter {

class SwNumRuleTbl;
class SwDoc;
class SwTxtNode;
class SwNodeNum;
class SwNumRule;
class SwNodeIndex;


// die speziellen Reader



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




class XMLReader : public Reader
{
    virtual ULONG Read(SwDoc &,SwPaM &,const String &);
public:
    virtual int GetReaderType();

    XMLReader();

    // read the sections of the document, which is equal to the medium.
    // returns the count of it
    virtual USHORT GetSectionList( SfxMedium& rMedium,
                                SvStrings& rStrings ) const;
};

// die speziellen Writer

#if 0
/*?*/ WriterRef GetW4WWriter( const String& );
WriterRef GetStgWriter( const String& );
WriterRef GetWWWriter( const String& );
/*?*/ WriterRef GetWW8Writer( const String& );
#if !( defined(PRODUCT) || defined(MAC) || defined(PM2) )
/*?*/ WriterRef GetDebugWriter( const String& );
/*?*/ WriterRef GetUndoWriter( const String& );
#endif
#else
void GetStgWriter( const String&, WriterRef& );
void GetWWWriter( const String&, WriterRef& );
#if !( defined(PRODUCT) || defined(MAC) || defined(PM2) )
#endif
#endif


// JP 17.03.99 - 63049
// Umsetzen der LRSpaces im aktuell importierten Doc. Die Fremd-Filter
// liefern immer absolute Werte fuer die Ebenen einer NumRule. Wir
// verarbeiten jetzt aber relative Werte bezogen auf das LR-Space-Item.
// Das hat zur Folge, das bei allen Absaetzen die EInzuege der NumRule vom
// Absatz-Einzug abgezogen werden muss.

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
