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
#ifndef _SFXRECTITEM_HXX
#define _SFXRECTITEM_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/debug.hxx>
#include <tools/gen.hxx>
#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter
{

DBG_NAMEEX_VISIBILITY(SfxRectangleItem, )

// -----------------------------------------------------------------------

class  SfxRectangleItem: public SfxPoolItem
{
    Rectangle                aVal;

public:
                             TYPEINFO();
                             SfxRectangleItem();
                             SfxRectangleItem( USHORT nWhich, const Rectangle& rVal );
                             SfxRectangleItem( const SfxRectangleItem& );
                             ~SfxRectangleItem() {
                                 DBG_DTOR(SfxRectangleItem, 0); }

    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * = 0 ) const;

    virtual int              operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT nItemVersion) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    const Rectangle&         GetValue() const { return aVal; }
            void             SetValue( const Rectangle& rNewVal ) {
                                 DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
                                 aVal = rNewVal;
                             }
    virtual bool             QueryValue( com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const com::sun::star::uno::Any& rVal,
                                       BYTE nMemberId = 0 );
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
