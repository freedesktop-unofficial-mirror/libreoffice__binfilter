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

#ifndef _SFXILSTITEM_HXX
#define _SFXILSTITEM_HXX

#include <bf_svtools/bf_solar.h>

#ifndef INCLUDED_SVLDLLAPI_H

#endif

#include <bf_svtools/poolitem.hxx>

#include <com/sun/star/uno/Sequence.hxx>

namespace binfilter
{
class SvULongs;

class  SfxIntegerListItem : public SfxPoolItem
{
    ::com::sun::star::uno::Sequence < sal_Int32 > m_aList;

public:
    TYPEINFO();

    SfxIntegerListItem();
    SfxIntegerListItem( const SfxIntegerListItem& rItem );
    ~SfxIntegerListItem();

    ::com::sun::star::uno::Sequence < sal_Int32 > GetSequence()
    { return m_aList; }
    ::com::sun::star::uno::Sequence < sal_Int32 > GetConstSequence() const
    { return (const_cast< SfxIntegerListItem * >(this))->GetSequence(); }

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual bool            PutValue  ( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
    virtual bool            QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
};

}

#endif // _SFXINTITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
