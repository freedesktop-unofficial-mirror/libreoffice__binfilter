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
#ifndef _TFRMITEM_HXX
#define _TFRMITEM_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/rtti.hxx>

#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter
{

enum SfxOpenMode
{
    SfxOpenSelect       = 0,     // selected in view
    SfxOpenOpen         = 1,     // doubleclicked or <enter>
    SfxOpenAddTask      = 2,     // doubleclicked or <enter> with Ctrl-Modifier
    SfxOpenDontKnow     = 3,
    SfxOpenReserved1    = 4,
    SfxOpenReserved2    = 5,
    SfxOpenModeLast     = 5
};

DBG_NAMEEX(SfxTargetFrameItem)

// class SfxTargetFrameItem -------------------------------------------------

class SfxTargetFrameItem : public SfxPoolItem
{
private:
            String          _aFrames[ (USHORT)SfxOpenModeLast+1 ];
public:
            TYPEINFO();

            SfxTargetFrameItem( const SfxTargetFrameItem& rCpy );
            SfxTargetFrameItem( USHORT nWhich );
            ~SfxTargetFrameItem();

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Create( SvStream&, USHORT nItemVersion ) const;
    virtual SvStream& Store( SvStream& rStream, USHORT ) const { return rStream; }
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;

    virtual bool            QueryValue( com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 ) const;
    virtual bool            PutValue  ( const com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 );
};

}
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
