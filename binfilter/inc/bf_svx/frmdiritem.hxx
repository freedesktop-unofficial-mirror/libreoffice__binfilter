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
#ifndef _SVX_FRMDIRITEM_HXX
#define _SVX_FRMDIRITEM_HXX

#include <bf_svtools/intitem.hxx>
#include <bf_svx/frmdir.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// class SvxFrameDirectionItem ----------------------------------------------

/* [Description]

    This item defines a frame direction, which place the content inside
    a frame. It exist different kind of directions which are used to the
    layout text for Western, CJK and CTL languages.
*/

class SvxFrameDirectionItem : public SfxUInt16Item
{
public:
    TYPEINFO();

    SvxFrameDirectionItem( SvxFrameDirection nValue = FRMDIR_HORI_LEFT_TOP,
                            USHORT nWhich = ITEMID_FRAMEDIR );
    virtual ~SvxFrameDirectionItem();

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&  Store(SvStream & rStrm, USHORT) const { return rStrm; }
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;
    virtual int             operator==( const SfxPoolItem& ) const;


    virtual bool PutValue( const ::com::sun::star::uno::Any& rVal,
                                    BYTE nMemberId );
    virtual bool QueryValue( ::com::sun::star::uno::Any& rVal,
                                BYTE nMemberId ) const;

    inline SvxFrameDirectionItem& operator=( const SvxFrameDirectionItem& rItem )
    {
        SetValue( rItem.GetValue() );
        return *this;
    }
};

}//end of namespace binfilter
#endif // #ifndef _SVX_FRMDIRITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
