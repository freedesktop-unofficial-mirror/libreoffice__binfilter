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
#ifndef _SVX_HNGPNCTITEM_HXX
#define _SVX_HNGPNCTITEM_HXX

#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// class SvxHangingPunctuationItem -----------------------------------------

/* [Description]

    This item describe how to handle the last character of a line.
*/

class SvxHangingPunctuationItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxHangingPunctuationItem( sal_Bool bOn = sal_False,
                        const sal_uInt16 nId = ITEMID_HANGINGPUNCTUATION );

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;


    inline SvxHangingPunctuationItem& operator=(
                                    const SvxHangingPunctuationItem& rItem )
    {
        SetValue( rItem.GetValue() );
        return *this;
    }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
