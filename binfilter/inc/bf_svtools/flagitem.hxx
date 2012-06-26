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
#ifndef _SFXFLAGITEM_HXX
#define _SFXFLAGITEM_HXX

#include "bf_svtools/svtdllapi.h"

#include <bf_svtools/bf_solar.h>
#include <tools/rtti.hxx>
#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter
{

extern USHORT nSfxFlagVal[16];

// -----------------------------------------------------------------------

DBG_NAMEEX_VISIBILITY(SfxFlagItem, )

class  SfxFlagItem: public SfxPoolItem
{
    USHORT                   nVal;

public:
                             TYPEINFO();

                             SfxFlagItem( USHORT nWhich = 0, USHORT nValue = 0 );
                             SfxFlagItem( const SfxFlagItem& );

                             ~SfxFlagItem() {
                                DBG_DTOR(SfxFlagItem, 0); }

    virtual BYTE             GetFlagCount() const;
    virtual XubString        GetFlagText( BYTE nFlag ) const;

    virtual int              operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT nVersion) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * = 0 ) const;
            USHORT           GetValue() const { return nVal; }
            void             SetValue( USHORT nNewVal ) {
                                 DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
                                 nVal = nNewVal;
                             }
            int              GetFlag( BYTE nFlag ) const {
                                 return ( (nVal & nSfxFlagVal[nFlag]) != 0 ); }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
