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

#include <forbiddencharacterstable.hxx>

#include <unotools/localedatawrapper.hxx>
#include <unolingu.hxx>

/*STRIP001*/#include <tools/debug.hxx>
namespace binfilter {
/*N*/ SvxForbiddenCharactersTable::SvxForbiddenCharactersTable( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF, USHORT nISize, USHORT nGrow )
/*N*/  : SvxForbiddenCharactersTableImpl( nISize, nGrow )
/*N*/ {
/*N*/   mxMSF = xMSF;
/*N*/ }


/*N*/ SvxForbiddenCharactersTable::~SvxForbiddenCharactersTable()
/*N*/ {
/*N*/   for ( ULONG n = Count(); n; )
/*N*/       delete GetObject( --n );
/*N*/ }



const ::com::sun::star::i18n::ForbiddenCharacters* SvxForbiddenCharactersTable::GetForbiddenCharacters( USHORT nLanguage, BOOL bGetDefault ) const
{
    ForbiddenCharactersInfo* pInf = Get( nLanguage );
    if ( !pInf && bGetDefault && mxMSF.is() )
    {
        const SvxForbiddenCharactersTableImpl *pConstImpl =
            dynamic_cast<const SvxForbiddenCharactersTableImpl*>(this);
        SvxForbiddenCharactersTableImpl* pImpl =
            const_cast<SvxForbiddenCharactersTableImpl*>(pConstImpl);
        pInf = new ForbiddenCharactersInfo;
        pImpl->Insert( nLanguage, pInf );
        pInf->bTemporary = TRUE;
        LocaleDataWrapper aWrapper( mxMSF, SvxCreateLocale( nLanguage ) );
        pInf->aForbiddenChars = aWrapper.getForbiddenCharacters();
    }
    return pInf ? &pInf->aForbiddenChars : NULL;
}



/*N*/ void SvxForbiddenCharactersTable::SetForbiddenCharacters( USHORT nLanguage, const ::com::sun::star::i18n::ForbiddenCharacters& rForbiddenChars )
/*N*/ {
/*N*/   ForbiddenCharactersInfo* pInf = Get( nLanguage );
/*N*/   if ( !pInf )
/*N*/   {
/*N*/       pInf = new ForbiddenCharactersInfo;
/*N*/       Insert( nLanguage, pInf );
/*N*/   }
/*N*/   pInf->bTemporary = FALSE;
/*N*/   pInf->aForbiddenChars = rForbiddenChars;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
