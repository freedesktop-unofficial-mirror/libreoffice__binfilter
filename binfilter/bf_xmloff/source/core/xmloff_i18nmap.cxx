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

#include <rtl/ustring.hxx>

#include <tools/debug.hxx>

#include <bf_svtools/svarray.hxx>

#include "i18nmap.hxx"
namespace binfilter {

using ::rtl::OUString;
class SvI18NMapEntry_Impl
{
    USHORT          nKind;
    OUString        aName;
    OUString        aNewName;

public:

    const OUString& GetNewName() const { return aNewName; }

    SvI18NMapEntry_Impl( USHORT nKnd, const OUString& rName,
                         const OUString& rNewName ) :
        nKind( nKnd ),
        aName( rName ),
        aNewName( rNewName )
    {}

    SvI18NMapEntry_Impl( USHORT nKnd, const OUString& rName ) :
        nKind( nKnd ),
        aName( rName )
    {}

    BOOL operator==( const SvI18NMapEntry_Impl& r ) const
    {
        return nKind == r.nKind &&
               aName == r.aName;
    }

    BOOL operator<( const SvI18NMapEntry_Impl& r ) const
    {
        return nKind < r.nKind ||
               ( nKind == r.nKind &&
                 aName < r.aName);
    }
};

typedef SvI18NMapEntry_Impl *SvI18NMapEntry_ImplPtr;
SV_DECL_PTRARR_SORT_DEL( SvI18NMap_Impl, SvI18NMapEntry_ImplPtr, 20, 5 )
SV_IMPL_OP_PTRARR_SORT( SvI18NMap_Impl, SvI18NMapEntry_ImplPtr )

// ---------------------------------------------------------------------

SvI18NMapEntry_Impl *SvI18NMap::_Find( USHORT nKind,
                                     const OUString& rName ) const
{
    SvI18NMapEntry_Impl *pRet = 0;
    SvI18NMapEntry_Impl aTst( nKind, rName );

    USHORT nPos;
    if( pImpl->Seek_Entry( &aTst, &nPos ) )
    {
        pRet = (*pImpl)[nPos];
    }

    return pRet;
}

SvI18NMap::SvI18NMap() :
    pImpl( 0 )
{
    pImpl = new SvI18NMap_Impl;
}

SvI18NMap::~SvI18NMap()
{
    delete pImpl;
}

void SvI18NMap::Add( USHORT nKind, const OUString& rName,
                     const OUString& rNewName )
{
    SvI18NMapEntry_Impl *pEntry = _Find( nKind, rName );
    DBG_ASSERT( !pEntry, "SvI18NMap::Add: item registered already" );
    if( !pEntry )
    {
        pEntry = new SvI18NMapEntry_Impl( nKind, rName, rNewName );
        pImpl->Insert( pEntry );
    }
}

const OUString& SvI18NMap::Get( USHORT nKind, const OUString& rName ) const
{
    SvI18NMapEntry_Impl *pEntry = _Find( nKind, rName );
    if( pEntry )
        return pEntry->GetNewName();
    else
        return rName;
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
