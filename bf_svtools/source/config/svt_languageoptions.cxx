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

#include <bf_svtools/languageoptions.hxx>

#include <bf_svtools/cjkoptions.hxx>
#include <bf_svtools/ctloptions.hxx>
#include <vcl/svapp.hxx>
#include <i18npool/mslangid.hxx>

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>
#include <osl/mutex.hxx>
#include <rtl/instance.hxx>

#include <com/sun/star/i18n/ScriptType.hpp>

using namespace ::com::sun::star;
// global ----------------------------------------------------------------------

namespace { struct ALMutex : public rtl::Static< ::osl::Mutex, ALMutex > {}; }

namespace binfilter
{

// -----------------------------------------------------------------------------
// returns for a language the scripttype
sal_uInt16 SvtLanguageOptions::GetScriptTypeOfLanguage( sal_uInt16 nLang )
{
    if( LANGUAGE_DONTKNOW == nLang )
        nLang = LANGUAGE_ENGLISH_US;
    else if( LANGUAGE_SYSTEM == nLang  )
        nLang = Application::GetSettings().GetLanguage();

    sal_Int16 nScriptType = MsLangId::getScriptType( nLang );
    USHORT nScript;
    switch (nScriptType)
    {
        case ::com::sun::star::i18n::ScriptType::ASIAN:
            nScript = SCRIPTTYPE_ASIAN;
            break;
        case ::com::sun::star::i18n::ScriptType::COMPLEX:
            nScript = SCRIPTTYPE_COMPLEX;
            break;
        default:
            nScript = SCRIPTTYPE_LATIN;
    }
    return nScript;
}
// -----------------------------------------------------------------------------



SvtSystemLanguageOptions::SvtSystemLanguageOptions() :
    utl::ConfigItem( rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("System/L10N") ))
{
    uno::Sequence< rtl::OUString > aPropertyNames(1);
    rtl::OUString* pNames = aPropertyNames.getArray();
    pNames[0] = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("SystemLocale"));
    uno::Sequence< uno::Any > aValues = GetProperties( aPropertyNames );

    if ( aValues.getLength() )
    {
        aValues[0]>>= m_sWin16SystemLocale;
    }
}

SvtSystemLanguageOptions::~SvtSystemLanguageOptions()
{
}

void    SvtSystemLanguageOptions::Commit()
{
    //does nothing
}

LanguageType SvtSystemLanguageOptions::GetWin16SystemLanguage()
{
    if( m_sWin16SystemLocale.getLength() == 0 )
        return LANGUAGE_NONE;
    return MsLangId::convertIsoStringToLanguage( m_sWin16SystemLocale );
}

    void SvtSystemLanguageOptions::Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& ) {}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
