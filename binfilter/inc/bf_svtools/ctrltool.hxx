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

#ifndef _CTRLTOOL_HXX
#define _CTRLTOOL_HXX

#include <bf_svtools/bf_solar.h>
#include <bf_tools/string.hxx>

#include <sal/types.h>
#include <vcl/metric.hxx>
#include <vector>

class OutputDevice;

namespace binfilter {

class ImplFontListNameInfo;
typedef ::std::vector< ImplFontListNameInfo* > ImplFontListNameInfoList;

#define FONTLIST_FONTINFO_NOTFOUND  ((USHORT)0xFFFF)

#define FONTLIST_FONTNAMETYPE_PRINTER           ((USHORT)0x0001)
#define FONTLIST_FONTNAMETYPE_SCREEN            ((USHORT)0x0002)
#define FONTLIST_FONTNAMETYPE_SCALABLE          ((USHORT)0x0004)

class FontList
{
private:
    ImplFontListNameInfoList    maFontListNameInfoList;
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

    OutputDevice*           GetDevice() const { return mpDev; }
    OutputDevice*           GetDevice2() const { return mpDev2; }

    const XubString&        GetNormalStr() const { return maNormal; }
    const XubString&        GetItalicStr() const { return maNormalItalic; }
    const XubString&        GetBoldStr() const { return maBold; }
    const XubString&        GetBoldItalicStr() const { return maBoldItalic; }
    FontInfo                Get( const XubString& rName,
                                 FontWeight eWeight,
                                 FontItalic eItalic ) const;

    size_t                  GetFontNameCount() const
                                { return maFontListNameInfoList.size(); }
private:
                            FontList( const FontList& );
    FontList&               operator =( const FontList& );
};

}

#endif  // _CTRLTOOL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
