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
#ifndef _SVX_PBINITEM_HXX
#define _SVX_PBINITEM_HXX

// include ---------------------------------------------------------------

#include <bf_svtools/intitem.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// define ----------------------------------------------------------------

#define PAPERBIN_PRINTER_SETTINGS   ((BYTE)0xFF)

// class SvxPaperBinItem -------------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt die Auswahl eines Papierschachts des Drucker.
*/

class SvxPaperBinItem : public SfxByteItem
{
public:
    TYPEINFO();

    inline SvxPaperBinItem( const USHORT nId = ITEMID_PAPERBIN,
                            const BYTE nTray = PAPERBIN_PRINTER_SETTINGS );
    inline SvxPaperBinItem &operator=( const SvxPaperBinItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream &, USHORT ) const;
    virtual SvStream&       Store( SvStream &rStream, USHORT ) const { return rStream; }
};

inline SvxPaperBinItem::SvxPaperBinItem( const USHORT nId, const BYTE nT )
    : SfxByteItem( nId, nT )
{}

inline SvxPaperBinItem &SvxPaperBinItem::operator=(
    const SvxPaperBinItem &rCpy )
{
    SetValue( rCpy.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
