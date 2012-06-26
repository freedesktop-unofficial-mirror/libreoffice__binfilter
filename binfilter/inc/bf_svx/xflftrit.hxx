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

#ifndef _SVX_XFLFTRIT_HXX
#define _SVX_XFLFTRIT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/xflgrit.hxx>
namespace binfilter {

//-----------------------------------
// class XFillFloatTransparenceItem -
//-----------------------------------

class XFillFloatTransparenceItem : public XFillGradientItem
{
private:

    long                    nDummy1;
    long                    nDummy2;
    BOOL                    bEnabled;

public:
                            TYPEINFO();

                            XFillFloatTransparenceItem();
                            XFillFloatTransparenceItem(const String& rName, const XGradient& rGradient, BOOL bEnable = TRUE );
                            XFillFloatTransparenceItem(SfxItemPool* pPool, const XGradient& rTheGradient, BOOL bEnable = TRUE );
                            XFillFloatTransparenceItem( const XFillFloatTransparenceItem& rItem );
                            XFillFloatTransparenceItem( SvStream& rIn, USHORT nVer = 0 );

    virtual int             operator==( const SfxPoolItem& rItem ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = NULL ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;
    virtual SvStream&       Store( SvStream& rOut, USHORT ) const { return rOut; }
    virtual USHORT          GetVersion( USHORT nFileFormatVersion ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;


    BOOL                    IsEnabled() const { return bEnabled; }
    void                    SetEnabled( BOOL bEnable ) { bEnabled = bEnable; }

    XFillFloatTransparenceItem* checkForUniqueItem( SdrModel* pModel ) const;
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
