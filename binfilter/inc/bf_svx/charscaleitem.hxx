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
#ifndef _SVX_CHARSCALEITEM_HXX
#define _SVX_CHARSCALEITEM_HXX

// include ---------------------------------------------------------------

#include <bf_svtools/intitem.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// class SvxCharScaleItem ----------------------------------------------

/* [Description]

    This item defines a character scaling factor as percent value.
    A value of 100 is identical to 100% and means normal width
    A value of 50 is identical to 50% and means 1/2 width.

*/

class SvxCharScaleWidthItem : public SfxUInt16Item
{
public:
    TYPEINFO();

    SvxCharScaleWidthItem( sal_uInt16 nValue = 100,
                            const sal_uInt16 nId = ITEMID_CHARSCALE_W );

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream& Store( SvStream& rStream , USHORT ) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;


    virtual bool PutValue( const ::com::sun::star::uno::Any& rVal,
                                    BYTE nMemberId );
    virtual bool QueryValue( ::com::sun::star::uno::Any& rVal,
                                BYTE nMemberId ) const;

    inline SvxCharScaleWidthItem& operator=(const SvxCharScaleWidthItem& rItem )
    {
        SetValue( rItem.GetValue() );
        return *this;
    }

};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
