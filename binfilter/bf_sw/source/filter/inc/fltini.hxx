/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fltini.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 03:16:46 $
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

//STRIP001 class Sw6Reader: public Reader
//STRIP001 {
//STRIP001  virtual ULONG Read( SwDoc &,SwPaM &,const String &);
//STRIP001 };

//STRIP001 class W4WReader: public StgReader
//STRIP001 {
//STRIP001  String sVersion;
//STRIP001  USHORT nFilter;
//STRIP001  BOOL bStorageFlag;
//STRIP001  virtual ULONG Read(SwDoc &,SwPaM &,const String &);
//STRIP001  // wir wollen die Streams / Storages nicht geoeffnet haben
//STRIP001  virtual int SetStrmStgPtr();
//STRIP001 public:
//STRIP001  W4WReader() : StgReader(), nFilter(0), bStorageFlag(FALSE) {}
//STRIP001  virtual int GetReaderType();
//STRIP001  virtual void SetFltName( const String& rFltName );
//STRIP001
//STRIP001  USHORT GetFilter() const { return nFilter; }
//STRIP001  const String& GetVersion() const { return sVersion; }
//STRIP001 };

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
//STRIP001  virtual void SetFltName( const String& rFltNm );
};

//STRIP001 class HTMLReader: public Reader
//STRIP001 {
//STRIP001  // wir wollen die Streams / Storages nicht geoeffnet haben
//STRIP001  virtual int SetStrmStgPtr();
//STRIP001  virtual ULONG Read(SwDoc &,SwPaM &,const String &);
//STRIP001  virtual String GetTemplateName() const;
//STRIP001 public:
//STRIP001  HTMLReader();
//STRIP001 };

//STRIP001 class WW1Reader : public Reader
//STRIP001 {
//STRIP001  virtual ULONG Read(SwDoc &,SwPaM &,const String &);
//STRIP001 };

//STRIP001 class WW8Reader : public StgReader
//STRIP001 {
//STRIP001  virtual ULONG Read(SwDoc &,SwPaM &,const String &);
//STRIP001 public:
//STRIP001  virtual int GetReaderType();
//STRIP001
//STRIP001  virtual BOOL HasGlossaries() const;
//STRIP001  virtual BOOL ReadGlossaries( SwTextBlocks&, BOOL bSaveRelFiles ) const;
//STRIP001 };

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
//STRIP001 /*?*/ void GetW4WWriter( const String&, WriterRef& );
void GetStgWriter( const String&, WriterRef& );
void GetWWWriter( const String&, WriterRef& );
//STRIP001 /*?*/ void GetWW8Writer( const String&, WriterRef& );
#if !( defined(PRODUCT) || defined(MAC) || defined(PM2) )
//STRIP001 /*?*/ void GetDebugWriter( const String&, WriterRef& );
//STRIP001 /*?*/ void GetUndoWriter( const String&, WriterRef& );
#endif
#endif


// JP 17.03.99 - 63049
// Umsetzen der LRSpaces im aktuell importierten Doc. Die Fremd-Filter
// liefern immer absolute Werte fuer die Ebenen einer NumRule. Wir
// verarbeiten jetzt aber relative Werte bezogen auf das LR-Space-Item.
// Das hat zur Folge, das bei allen Absaetzen die EInzuege der NumRule vom
// Absatz-Einzug abgezogen werden muss.
//STRIP001 class SwRelNumRuleSpaces
//STRIP001 {
//STRIP001  SwNumRuleTbl* pNumRuleTbl;  // Liste aller benannten NumRules
//STRIP001  BOOL bNewDoc;
//STRIP001
//STRIP001  void SetNumLSpace( SwTxtNode& rNd, const SwNumRule& rRule );
//STRIP001
//STRIP001 public:
//STRIP001  SwRelNumRuleSpaces( SwDoc& rDoc, BOOL bNewDoc );
//STRIP001  ~SwRelNumRuleSpaces();
//STRIP001
//STRIP001  void SetNumRelSpaces( SwDoc& rDoc );
//STRIP001  void SetOultineRelSpaces( const SwNodeIndex& rStt,
//STRIP001                              const SwNodeIndex& rEnd );
//STRIP001 };

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
