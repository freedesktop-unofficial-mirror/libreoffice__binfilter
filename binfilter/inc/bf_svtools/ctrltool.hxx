/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ctrltool.hxx,v $
 * $Revision: 1.3 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
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
