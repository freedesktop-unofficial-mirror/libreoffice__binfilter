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

#include <tools/debug.hxx>

#include <rtl/ustring.hxx>

#include <bf_svtools/svarray.hxx>

#include "xmltkmap.hxx"

namespace binfilter {

using namespace ::binfilter::xmloff::token;
using ::rtl::OUString;

class SvXMLTokenMapEntry_Impl
{
    sal_uInt16  nPrefixKey;
    OUString    sLocalName;
    sal_uInt16  nToken;

public:

    sal_uInt16 GetToken() const { return nToken; }

    SvXMLTokenMapEntry_Impl( sal_uInt16 nPrefix, const OUString& rLName,
                             sal_uInt16 nTok=XML_TOK_UNKNOWN ) :
        nPrefixKey( nPrefix ),
        sLocalName( rLName  ),
        nToken( nTok )
    {}

    SvXMLTokenMapEntry_Impl( const SvXMLTokenMapEntry& rEntry ) :
        nPrefixKey( rEntry.nPrefixKey ),
        sLocalName( GetXMLToken( rEntry.eLocalName ) ),
        nToken( rEntry.nToken )
    {}

    BOOL operator==( const SvXMLTokenMapEntry_Impl& r ) const
    {
        return nPrefixKey == r.nPrefixKey &&
               sLocalName == r.sLocalName;
    }

    BOOL operator<( const SvXMLTokenMapEntry_Impl& r ) const
    {
        return nPrefixKey < r.nPrefixKey ||
               ( nPrefixKey == r.nPrefixKey &&
                 sLocalName < r.sLocalName);
    }
};

typedef SvXMLTokenMapEntry_Impl *SvXMLTokenMapEntry_ImplPtr;
SV_DECL_PTRARR_SORT_DEL( SvXMLTokenMap_Impl, SvXMLTokenMapEntry_ImplPtr, 5, 5 )
SV_IMPL_OP_PTRARR_SORT( SvXMLTokenMap_Impl, SvXMLTokenMapEntry_ImplPtr )

// ---------------------------------------------------------------------

SvXMLTokenMapEntry_Impl *SvXMLTokenMap::_Find( sal_uInt16 nKeyPrefix,
                                                const OUString& rLName ) const
{
    SvXMLTokenMapEntry_Impl *pRet = 0;
    SvXMLTokenMapEntry_Impl aTst( nKeyPrefix, rLName );

    sal_uInt16 nPos;
    if( pImpl->Seek_Entry( &aTst, &nPos ) )
    {
        pRet = (*pImpl)[nPos];
    }

    return pRet;
}

SvXMLTokenMap::SvXMLTokenMap( SvXMLTokenMapEntry *pMap ) :
    pImpl( new SvXMLTokenMap_Impl )
{
    while( pMap->eLocalName != XML_TOKEN_INVALID )
    {
        pImpl->Insert( new SvXMLTokenMapEntry_Impl( *pMap ) );
        pMap++;
    }
}

SvXMLTokenMap::~SvXMLTokenMap()
{
    delete pImpl;
}

sal_uInt16 SvXMLTokenMap::Get( sal_uInt16 nKeyPrefix,
                               const OUString& rLName ) const
{
    SvXMLTokenMapEntry_Impl *pEntry = _Find( nKeyPrefix, rLName );
    if( pEntry )
        return pEntry->GetToken();
    else
        return XML_TOK_UNKNOWN;
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
