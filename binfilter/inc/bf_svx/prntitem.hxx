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
#ifndef _SVX_PRNTITEM_HXX
#define _SVX_PRNTITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#include <bf_svtools/eitem.hxx>
namespace binfilter {

// class SvxPrintItem ----------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt eine logische Variable "Drucken ja oder nein".
*/

class SvxPrintItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxPrintItem( const USHORT nId = ITEMID_PRINT, const BOOL bPrt = TRUE );
    inline SvxPrintItem &operator=( const SvxPrintItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

};

inline SvxPrintItem::SvxPrintItem( const USHORT nId, const BOOL bPrt )
    : SfxBoolItem( nId, bPrt )
{}

inline SvxPrintItem &SvxPrintItem::operator=( const SvxPrintItem &rCpy )
{
    SetValue( rCpy.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
