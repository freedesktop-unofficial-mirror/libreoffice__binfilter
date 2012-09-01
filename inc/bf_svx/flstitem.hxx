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
#ifndef _SVX_FLSTITEM_HXX
#define _SVX_FLSTITEM_HXX

#include <bf_svtools/poolitem.hxx>
#ifndef   ITEMID_FONTLIST
#define   ITEMID_FONTLIST 0
#endif

namespace binfilter {

class FontList;

// class SvxFontListItem -------------------------------------------------
/*
    [Beschreibung]

    Dieses Item dient als Transport-Medium fuer eine FontListe.
    Die Fontliste wird nicht kopiert und nicht geloescht!
*/

class SvxFontListItem : public SfxPoolItem
{
private:
    const FontList*         pFontList;

public:
    TYPEINFO();

    SvxFontListItem( const FontList* pFontLst,
                     const USHORT nId = ITEMID_FONTLIST );
    SvxFontListItem( const SvxFontListItem& rItem );

    virtual int             operator==( const SfxPoolItem& ) const {return 0; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;


    const FontList*         GetFontList() const { return pFontList; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
