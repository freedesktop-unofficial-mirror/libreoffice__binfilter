/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ctrltool.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:55:04 $
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

#ifndef _CTRLTOOL_HXX
#define _CTRLTOOL_HXX

#include <sal/types.h>
#include <tools/list.hxx>
#include <vcl/metric.hxx>


class OutputDevice;

namespace binfilter {

class ImplFontListNameInfo;
#define FONTLIST_FONTINFO_NOTFOUND  ((USHORT)0xFFFF)

#define FONTLIST_FONTNAMETYPE_PRINTER           ((USHORT)0x0001)
#define FONTLIST_FONTNAMETYPE_SCREEN            ((USHORT)0x0002)
#define FONTLIST_FONTNAMETYPE_SCALABLE          ((USHORT)0x0004)

class FontList : private List
{
private:
    XubString               maMapBoth;
    XubString               maMapPrinterOnly;
    XubString               maMapScreenOnly;
    XubString               maMapSizeNotAvailable;
    XubString               maMapStyleNotAvailable;
    XubString               maMapNotAvailable;
    XubString               maLight;
    XubString               maLightItalic;
    XubString               maNormal;
    XubString               maNormalItalic;
    XubString               maBold;
    XubString               maBoldItalic;
    XubString               maBlack;
    XubString               maBlackItalic;
    long*                   mpSizeAry;
    OutputDevice*           mpDev;
    OutputDevice*           mpDev2;

#ifdef CTRLTOOL_CXX
    ImplFontListNameInfo*   ImplFind( const XubString& rSearchName, ULONG* pIndex ) const;
    ImplFontListNameInfo*   ImplFindByName( const XubString& rStr ) const;
    void                    ImplInsertFonts( OutputDevice* pDev, BOOL bAll,
                                             BOOL bInsertData );
#endif

public:
                            FontList( OutputDevice* pDevice,
                                      OutputDevice* pDevice2 = NULL,
                                      BOOL bAll = TRUE );
                            ~FontList();

    FontList*               Clone() const;

    OutputDevice*           GetDevice() const { return mpDev; }
    OutputDevice*           GetDevice2() const { return mpDev2; }
    XubString               GetFontMapText( const FontInfo& rInfo ) const;
    USHORT                  GetFontNameType( const XubString& rFontName ) const;

    const XubString&        GetNormalStr() const { return maNormal; }
    const XubString&        GetItalicStr() const { return maNormalItalic; }
    const XubString&        GetBoldStr() const { return maBold; }
    const XubString&        GetBoldItalicStr() const { return maBoldItalic; }
    const XubString&        GetStyleName( FontWeight eWeight, FontItalic eItalic ) const;
    XubString               GetStyleName( const FontInfo& rInfo ) const;

    FontInfo                Get( const XubString& rName,
                                 const XubString& rStyleName ) const;
    FontInfo                Get( const XubString& rName,
                                 FontWeight eWeight,
                                 FontItalic eItalic ) const;

    BOOL                    IsAvailable( const XubString& rName ) const;
    USHORT                  GetFontNameCount() const
                                { return (USHORT)List::Count(); }
    const FontInfo&         GetFontName( USHORT nFont ) const;
    USHORT                  GetFontNameType( USHORT nFont ) const;
    sal_Handle              GetFirstFontInfo( const XubString& rName ) const;
    sal_Handle              GetNextFontInfo( sal_Handle hFontInfo ) const;
    const FontInfo&         GetFontInfo( sal_Handle hFontInfo ) const;

    const long*             GetSizeAry( const FontInfo& rInfo ) const;
    static const long*      GetStdSizeAry();

private:
                            FontList( const FontList& );
    FontList&               operator =( const FontList& );
};


// -----------------
// - FontSizeNames -
// -----------------

class FontSizeNames
{
private:
    struct ImplFSNameItem*  mpArray;
    ULONG                   mnElem;

public:
                            FontSizeNames( LanguageType eLanguage /* = LANGUAGE_DONTKNOW */ );

    ULONG                   Count() const { return mnElem; }
    BOOL                    IsEmpty() const { return !mnElem; }

    long                    Name2Size( const String& ) const;
    String                  Size2Name( long ) const;

    String                  GetIndexName( ULONG nIndex ) const;
    long                    GetIndexSize( ULONG nIndex ) const;
};

}

#endif  // _CTRLTOOL_HXX
