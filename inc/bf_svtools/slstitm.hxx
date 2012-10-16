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
#ifndef _SFXSLSTITM_HXX
#define _SFXSLSTITM_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/rtti.hxx>

#include <bf_svtools/poolitem.hxx>

#include <com/sun/star/uno/Sequence.h>

namespace binfilter
{

class SfxImpStringList;

class  SfxStringListItem : public SfxPoolItem
{
protected:
    SfxImpStringList*   pImp;

public:
    TYPEINFO();

    SfxStringListItem();
    SfxStringListItem( USHORT nWhich, SvStream& rStream );
    SfxStringListItem( const SfxStringListItem& rItem );
    ~SfxStringListItem();

#ifndef TF_POOLABLE
    virtual int             IsPoolable() const;
#endif

    // String-Separator: \n
    virtual void            SetString( const XubString& );
    virtual XubString       GetString();

    void                    SetStringList( const com::sun::star::uno::Sequence< rtl::OUString >& rList );
    void                    GetStringList( com::sun::star::uno::Sequence< rtl::OUString >& rList ) const;

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * = 0 ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream &, USHORT nVersion ) const;
    virtual SvStream& Store( SvStream &rStream, USHORT ) const { return rStream; }

    virtual bool            PutValue  ( const com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 );
    virtual bool            QueryValue( com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 ) const;
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
