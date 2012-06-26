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

#ifndef _OUTLOBJ_HXX
#define _OUTLOBJ_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>

#include <rsc/rscsfx.hxx>

#include <bf_svtools/itemset.hxx>

#include <bf_svx/eeitem.hxx>
class SvStream;
namespace binfilter {

class SfxItemPool;
class SfxStyleSheetPool;
class Outliner;
class EditTextObject;

class OutlinerParaObject
{
    friend class Outliner;

    EditTextObject*             pText;
    USHORT*                     pDepthArr;
    sal_uInt32                  nCount;
    BOOL                        bIsEditDoc;
                                OutlinerParaObject( USHORT nParaCount );

public:
                                OutlinerParaObject( const OutlinerParaObject& );
                                ~OutlinerParaObject();

    OutlinerParaObject*         Clone() const;

    USHORT                      GetOutlinerMode() const;
    void                        SetOutlinerMode( USHORT n );

    BOOL                        IsVertical() const;
    void                        SetVertical( BOOL bVertical );

    sal_uInt32                  Count() const                   { return nCount; }
    USHORT                      GetDepth( USHORT nPara ) const  { return pDepthArr[nPara]; }
    const EditTextObject&       GetTextObject() const           { return *pText; }
    void                        ClearPortionInfo();
    BOOL                        IsEditDoc() const               { return bIsEditDoc; }
    void                        Store( SvStream& ) const {}
    static OutlinerParaObject*  Create( SvStream&, SfxItemPool* pTextObjectPool = 0 );

    BOOL                        ChangeStyleSheets(  const XubString& rOldName, SfxStyleFamily eOldFamily,
                                                    const XubString& rNewName, SfxStyleFamily eNewFamily );
    void                        ChangeStyleSheetName( SfxStyleFamily eFamily, const XubString& rOldName, const XubString& rNewName );

    void                        MergeParaAttribs( const SfxItemSet& rAttribs, USHORT nStart = EE_CHAR_START, USHORT nEnd = EE_CHAR_END );

    void                        FinishLoad( SfxStyleSheetPool* pStyleSheetPool );
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
