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

#ifndef _SFXRNGITEM_HXX

#ifndef NUMTYPE

#define NUMTYPE USHORT
#define SfxXRangeItem SfxRangeItem
#define SfxXRangesItem SfxUShortRangesItem
#include <bf_svtools/rngitem.hxx>
#undef NUMTYPE
#undef SfxXRangeItem
#undef SfxXRangesItem

#define _SFXRNGITEM_HXX

#else

#include "bf_svtools/svtdllapi.h"

#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter
{

// -----------------------------------------------------------------------

class  SfxXRangeItem : public SfxPoolItem
{
private:
    NUMTYPE                     nFrom;
    NUMTYPE                     nTo;
public:
                                TYPEINFO();
                                SfxXRangeItem();
                                SfxXRangeItem( USHORT nWID, NUMTYPE nFrom, NUMTYPE nTo );
                                SfxXRangeItem( const SfxXRangeItem& rItem );
    virtual int                 operator==( const SfxPoolItem& ) const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * = 0 ) const;
    virtual SfxPoolItem*        Clone( SfxItemPool *pPool = 0 ) const;
    inline NUMTYPE&             From() { return nFrom; }
    inline NUMTYPE              From() const { return nFrom; }
    inline NUMTYPE&             To() { return nTo; }
    inline NUMTYPE              To() const { return nTo; }
    inline BOOL                 HasRange() const { return nTo>nFrom; }
    virtual SfxPoolItem*        Create( SvStream &, USHORT nVersion ) const;
    virtual SvStream& Store( SvStream &rStream, USHORT ) const { return rStream; }
};

// -----------------------------------------------------------------------

class  SfxXRangesItem : public SfxPoolItem
{
private:
    NUMTYPE*                    _pRanges;

public:
                                TYPEINFO();
                                SfxXRangesItem();
                                SfxXRangesItem( USHORT nWID, SvStream &rStream );
                                SfxXRangesItem( const SfxXRangesItem& rItem );
    virtual                     ~SfxXRangesItem();
    virtual int                 operator==( const SfxPoolItem& ) const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * = 0 ) const;
    virtual SfxPoolItem*        Clone( SfxItemPool *pPool = 0 ) const;
    inline const NUMTYPE*       GetRanges() const { return _pRanges; }
    virtual SfxPoolItem*        Create( SvStream &, USHORT nVersion ) const;
    virtual SvStream& Store( SvStream &rStream, USHORT ) const { return rStream; }
};

}

#endif
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
