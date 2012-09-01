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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <com/sun/star/i18n/ScriptType.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <unotools/localedatawrapper.hxx>
#include <bf_svx/unolingu.hxx>
#include <bf_svx/scripttypeitem.hxx>

#include <breakit.hxx>
#include <legacysmgr/legacy_binfilters_smgr.hxx>

#include "swtypes.hxx"

namespace binfilter {
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::i18n;


/*N*/ SwBreakIt::SwBreakIt()
/*N*/   : pLocale( NULL ), pForbidden( NULL )
/*N*/ {
/*N*/   _GetLocale( (LanguageType)GetAppLanguage() );
/*N*/   Reference< XMultiServiceFactory > xMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   Reference < XInterface > xI = xMSF->createInstance(
/*N*/       ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.i18n.BreakIterator" )) );
/*N*/   if ( xI.is() )
/*N*/   {
/*N*/       Any x = xI->queryInterface( ::getCppuType((const Reference< XBreakIterator >*)0) );
/*N*/       x >>= xBreak;
/*N*/   }
/*N*/ }

/*N*/ void SwBreakIt::_GetLocale( const LanguageType aLang )
/*N*/ {
/*N*/   aLast = aLang;
/*N*/   delete pLocale;
/*N*/   pLocale = new Locale( SvxCreateLocale( aLast ) );
/*N*/ }

/*N*/ void SwBreakIt::_GetForbidden( const LanguageType aLang )
/*N*/ {
/*N*/   aForbiddenLang = aLang;
/*N*/   Reference< XMultiServiceFactory > xMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   LocaleDataWrapper aWrap( xMSF, GetLocale( aLang ) );
/*N*/   delete pForbidden;
/*N*/   pForbidden = new ForbiddenCharacters( aWrap.getForbiddenCharacters() );
/*N*/ }

/*N*/ USHORT SwBreakIt::GetRealScriptOfText( const String& rTxt,
/*N*/                                       xub_StrLen nPos ) const
/*N*/ {
/*N*/   USHORT nScript = ScriptType::WEAK;
/*N*/   if( xBreak.is() && rTxt.Len() )
/*N*/   {
/*N*/       if( nPos && nPos == rTxt.Len() )
/*N*/           --nPos;
/*N*/       nScript = xBreak->getScriptType( rTxt, nPos );
/*N*/       sal_Int32 nChgPos;
/*N*/       if( ScriptType::WEAK == nScript && nPos &&
/*N*/           0 < (nChgPos = xBreak->beginOfScript( rTxt, nPos, nScript )) )
/*N*/           nScript = xBreak->getScriptType( rTxt, nChgPos-1 );
/*N*/
/*N*/       if( ScriptType::WEAK == nScript && rTxt.Len() >
/*N*/           ( nChgPos = xBreak->endOfScript( rTxt, nPos, nScript ) ) &&
/*N*/           0 <= nChgPos )
/*N*/           nScript = xBreak->getScriptType( rTxt, nChgPos );
/*N*/   }
/*N*/   if( ScriptType::WEAK == nScript )
/*N*/     nScript = GetI18NScriptTypeOfLanguage( (USHORT)GetAppLanguage() );
/*N*/   return nScript;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
