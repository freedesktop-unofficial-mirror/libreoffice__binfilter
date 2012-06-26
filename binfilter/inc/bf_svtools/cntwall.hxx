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
#ifndef _CNTWALL_HXX
#define _CNTWALL_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/shl.hxx>
#include <tools/rtti.hxx>
#include <tools/color.hxx>

#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter {

class  CntWallpaperItem : public SfxPoolItem
{
private:
    UniString               _aURL;
    Color                   _nColor;
    USHORT                  _nStyle;

public:
                            TYPEINFO();

                            CntWallpaperItem( USHORT nWhich, SvStream& rStream, USHORT nVersion );
                            CntWallpaperItem( const CntWallpaperItem& rCpy );
                            ~CntWallpaperItem();

    virtual USHORT GetVersion(USHORT) const;

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Create( SvStream&, USHORT nItemVersion ) const;
    virtual SvStream& Store( SvStream& rStream, USHORT ) const { return rStream; }
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 ) const;
    virtual bool            PutValue  ( const ::com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 );

    void                    SetBitmapURL( const UniString& rURL ) { _aURL = rURL; }
    void                    SetColor( Color nColor ) { _nColor = nColor; }
    void                    SetStyle( USHORT nStyle ) { _nStyle = nStyle; }

    const UniString&        GetBitmapURL() const { return _aURL; }
    Color                   GetColor() const { return _nColor; }
    USHORT                  GetStyle() const { return _nStyle; }
};

}

////////////////////////////////////////////////////////////////////////////////

#endif // _CNTWALL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
