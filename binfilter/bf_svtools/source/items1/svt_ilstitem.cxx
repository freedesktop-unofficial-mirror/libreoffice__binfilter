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

#include <com/sun/star/script/XTypeConverter.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <comphelper/processfactory.hxx>

#include <bf_svtools/ilstitem.hxx>

#define _SVSTDARR_ULONGS
#include <bf_svtools/svstdarr.hxx>

namespace binfilter
{

TYPEINIT1_AUTOFACTORY(SfxIntegerListItem, SfxPoolItem);

SfxIntegerListItem::SfxIntegerListItem()
{
}

SfxIntegerListItem::SfxIntegerListItem( const SfxIntegerListItem& rItem )
    : SfxPoolItem( rItem )
{
    m_aList = rItem.m_aList;
}

SfxIntegerListItem::~SfxIntegerListItem()
{
}

int SfxIntegerListItem::operator==( const SfxPoolItem& rPoolItem ) const
{
    if ( !rPoolItem.ISA( SfxIntegerListItem ) )
        return FALSE;

    const SfxIntegerListItem rItem = (const SfxIntegerListItem&) rPoolItem;
    return rItem.m_aList == m_aList;
}

SfxPoolItem* SfxIntegerListItem::Clone( SfxItemPool * ) const
{
    return new SfxIntegerListItem( *this );
}

bool SfxIntegerListItem::PutValue  ( const com::sun::star::uno::Any& rVal, BYTE )
{
    ::com::sun::star::uno::Reference < ::com::sun::star::script::XTypeConverter > xConverter
            ( ::comphelper::getProcessServiceFactory()->createInstance(::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.script.Converter" ))),
            ::com::sun::star::uno::UNO_QUERY );
    ::com::sun::star::uno::Any aNew;
    try { aNew = xConverter->convertTo( rVal, ::getCppuType((const ::com::sun::star::uno::Sequence < sal_Int32 >*)0) ); }
    catch (::com::sun::star::uno::Exception&)
    {
        return false;
    }

    return ( aNew >>= m_aList );
}

bool SfxIntegerListItem::QueryValue( com::sun::star::uno::Any& rVal, BYTE ) const
{
    rVal <<= m_aList;
    return true;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
