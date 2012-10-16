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

#ifndef INCLUDED_SVTOOLS_SYSLOCALEOPTIONS_HXX
#define INCLUDED_SVTOOLS_SYSLOCALEOPTIONS_HXX


#include <sal/types.h>
#include <rtl/ustring.hxx>

#include <bf_svtools/bf_solar.h>
#include <tools/link.hxx>
#include <i18npool/lang.h>
#include <bf_tools/string.hxx>
#include <bf_svtools/options.hxx>

namespace osl { class Mutex; }

namespace binfilter
{

// bits for broadcasting hints of changes in a SfxSimpleHint, may be combined
const ULONG SYSLOCALEOPTIONS_HINT_LOCALE    = 0x00000001;
const ULONG SYSLOCALEOPTIONS_HINT_CURRENCY  = 0x00000002;

class SvtSysLocaleOptions_Impl;
class SvtListener;


class  SvtSysLocaleOptions: public Options
{
    static  SvtSysLocaleOptions_Impl*   pOptions;
    static  sal_Int32                   nRefCount;

    static  ::osl::Mutex&       GetMutex();

public:

    enum EOption
    {
        E_LOCALE,
        E_CURRENCY
    };
                                SvtSysLocaleOptions();
                                virtual ~SvtSysLocaleOptions();

    // ConfigItem methods

                                /** Add a listener to react on config changes
                                    which are broadcasted in a SfxSimpleHint
                                    @return
                                        <TRUE/> if added
                                        <FALSE/> if not added
                                 */
            BOOL                AddListener( SvtListener& );
            BOOL                RemoveListener( SvtListener& );

    // config value access methods

    /// The config string may be empty to denote the default currency of the locale
            const ::rtl::OUString&  GetCurrencyConfigString() const;

    // convenience methods

    /// Get currency abbreviation and locale from an USD-en-US or EUR-de-DE string
    static  void                GetCurrencyAbbrevAndLanguage(
                                    String& rAbbrev,
                                    LanguageType& eLang,
                                    const ::rtl::OUString& rConfigString );

            void                GetCurrencyAbbrevAndLanguage(
                                        String& rAbbrev,
                                        LanguageType& eLang ) const
                                    {
                                        GetCurrencyAbbrevAndLanguage( rAbbrev,
                                            eLang, GetCurrencyConfigString() );
                                    }

    /** Set a link to a method to be called whenever the default currency
        changes. This can be only one method, and normally it is the static
        link method which calls SvNumberFormatter::SetDefaultSystemCurrency().
        This is needed because the number formatter isn't part of the svl light
        library, otherwise we could call SetDefaultSystemCurrency() directly.
     */
    static  void                SetCurrencyChangeLink( const Link& rLink );
    static  const Link&         GetCurrencyChangeLink();
};

}

#endif  // INCLUDED_SVTOOLS_SYSLOCALEOPTIONS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
