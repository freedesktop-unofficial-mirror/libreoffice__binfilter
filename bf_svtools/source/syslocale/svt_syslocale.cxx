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

#include <bf_svtools/syslocale.hxx>

#include <broadcast.hxx>
#include <listener.hxx>
#include <bf_svtools/smplhint.hxx>
#include <vcl/svapp.hxx>
#include <bf_tools/string.hxx>
#include <bf_svtools/syslocaleoptions.hxx>
#include <unotools/localedatawrapper.hxx>
#include <comphelper/processfactory.hxx>


using namespace osl;
using namespace com::sun::star;

namespace binfilter
{


SvtSysLocale_Impl*  SvtSysLocale::pImpl = NULL;
sal_Int32           SvtSysLocale::nRefCount = 0;


class SvtSysLocale_Impl : public SvtListener
{
    friend class SvtSysLocale;

        SvtSysLocaleOptions     aSysLocaleOptions;
        LocaleDataWrapper*      pLocaleData;
        CharClass*              pCharClass;

public:
                                SvtSysLocale_Impl();
    virtual                     ~SvtSysLocale_Impl();

    virtual void                Notify( SvtBroadcaster& rBC, const SfxHint& rHint );

};


// -----------------------------------------------------------------------

SvtSysLocale_Impl::SvtSysLocale_Impl()
{
    const lang::Locale& rLocale = Application::GetSettings().GetLocale();
    pLocaleData = new LocaleDataWrapper(
        ::comphelper::getProcessServiceFactory(), rLocale );
    pCharClass = new CharClass(
        ::comphelper::getProcessComponentContext(), rLocale );
    aSysLocaleOptions.AddListener( *this );
}


SvtSysLocale_Impl::~SvtSysLocale_Impl()
{
    aSysLocaleOptions.RemoveListener( *this );
    delete pCharClass;
    delete pLocaleData;
}


void SvtSysLocale_Impl::Notify( SvtBroadcaster&, const SfxHint& rHint )
{
    const SfxSimpleHint* p = PTR_CAST( SfxSimpleHint, &rHint );
    if( p && (p->GetId() & SYSLOCALEOPTIONS_HINT_LOCALE) )
    {
        MutexGuard aGuard( SvtSysLocale::GetMutex() );
        const lang::Locale& rLocale = Application::GetSettings().GetLocale();
        pLocaleData->setLocale( rLocale );
        pCharClass->setLocale( rLocale );
    }
}


// ====================================================================

SvtSysLocale::SvtSysLocale()
{
    MutexGuard aGuard( GetMutex() );
    if ( !pImpl )
        pImpl = new SvtSysLocale_Impl;
    ++nRefCount;
}


SvtSysLocale::~SvtSysLocale()
{
    MutexGuard aGuard( GetMutex() );
    if ( !--nRefCount )
    {
        delete pImpl;
        pImpl = NULL;
    }
}


// static
Mutex& SvtSysLocale::GetMutex()
{
    static Mutex* pMutex = NULL;
    if( !pMutex )
    {
        MutexGuard aGuard( Mutex::getGlobalMutex() );
        if( !pMutex )
        {
            // #i77768# Due to a static reference in the toolkit lib
            // we need a mutex that lives longer than the svtools library.
            // Otherwise the dtor would use a destructed mutex!!
            pMutex = new Mutex;
        }
    }
    return *pMutex;
}


const LocaleDataWrapper& SvtSysLocale::GetLocaleData() const
{
    return *(pImpl->pLocaleData);
}


const LocaleDataWrapper* SvtSysLocale::GetLocaleDataPtr() const
{
    return pImpl->pLocaleData;
}


const CharClass& SvtSysLocale::GetCharClass() const
{
    return *(pImpl->pCharClass);
}


const CharClass* SvtSysLocale::GetCharClassPtr() const
{
    return pImpl->pCharClass;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
