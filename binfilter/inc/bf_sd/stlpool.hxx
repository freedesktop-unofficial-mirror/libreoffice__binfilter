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

#ifndef _SD_STLPOOL_HXX
#define _SD_STLPOOL_HXX


#include <bf_svtools/style.hxx>
#include <bf_tools/list.hxx>
namespace binfilter {

class SdStyleSheet;
class SdDrawDocument;


class SdStyleSheetPool : public SfxStyleSheetPool
{
private:
    SfxStyleSheetBase* pActualStyleSheet;
    SdDrawDocument*    pDoc;

protected:
    using SfxStyleSheetPool::Create;
    virtual SfxStyleSheetBase* Create(const String& rName,
                                      SfxStyleFamily eFamily,
                                      USHORT nMask);

public:
                        SdStyleSheetPool(SfxItemPool& rPool, SdDrawDocument* pDocument);
    virtual             ~SdStyleSheetPool();

    void                SetActualStyleSheet(SfxStyleSheetBase* pActStyleSheet)
                                       { pActualStyleSheet = pActStyleSheet; }
    SfxStyleSheetBase*  GetActualStyleSheet()    { return pActualStyleSheet; }

    SfxStyleSheetBase*  GetTitleSheet(const String& rLayoutName);

                            // Caller muss Liste loeschen
    List*               CreateOutlineSheetList(const String& rLayoutName);

    /** creates all layout style sheets for the givin layout name if they
        don't exist yet.

        @param rLayoutName  Must be the name of a master page
        @param bCheck       If set to true, the debug version will assert if a style
                            had to be created. This is used to assert errors in documents
                            when styles are missing.
    */
    void                CreateLayoutStyleSheets(const String& rLayoutName, sal_Bool bCheck = sal_False );

    void                CreatePseudosIfNecessary();
    void                UpdateStdNames();
    void                AdjustLRSpaceItems();
    static void         PutNumBulletItem( SfxStyleSheetBase* pSheet, Font& rBulletFont );
    Font                GetBulletFont() const;

    SdDrawDocument*     GetDoc() const { return pDoc; }
};

} //namespace binfilter
#endif     // _SD_STLPOOL_HXX



/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
