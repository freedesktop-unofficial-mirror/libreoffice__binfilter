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

#ifndef _SVX_XBTMPIT_HXX
#define _SVX_XBTMPIT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/xbitmap.hxx>
namespace binfilter {

class SdrModel;

//----------------------
// class XFillBitmapItem
//----------------------
class XFillBitmapItem : public NameOrIndex
{
    XOBitmap aXOBitmap;

public:
            TYPEINFO();
            XFillBitmapItem() : NameOrIndex(XATTR_FILLBITMAP, -1 ) {}
            XFillBitmapItem( const String& rName, const XOBitmap& rTheBitmap );
            XFillBitmapItem( SfxItemPool* pPool, const XOBitmap& rTheBitmap );
            XFillBitmapItem( const XFillBitmapItem& rItem );
            XFillBitmapItem( SvStream& rIn, USHORT nVer = 0 );

    virtual int             operator==( const SfxPoolItem& rItem ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;
    virtual SvStream&       Store( SvStream& rOut, USHORT ) const { return rOut; }
    virtual USHORT          GetVersion( USHORT nFileFormatVersion ) const;

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    const XOBitmap& GetValue() const;
    void           SetValue( const XOBitmap& rNew )  { aXOBitmap = rNew; Detach(); }

    static BOOL CompareValueFunc( const NameOrIndex* p1, const NameOrIndex* p2 );
    XFillBitmapItem* checkForUniqueItem( SdrModel* pModel ) const;
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
