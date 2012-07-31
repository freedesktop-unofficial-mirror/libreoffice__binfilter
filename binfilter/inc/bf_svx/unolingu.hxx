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

#ifndef _UNO_LINGU_HXX
#define _UNO_LINGU_HXX

#include <bf_svtools/bf_solar.h>

#include <i18npool/lang.h>
#include <bf_tools/string.hxx>

#include <com/sun/star/linguistic2/XLinguServiceManager.hpp>
#include <com/sun/star/linguistic2/XSpellChecker1.hpp>
#include <com/sun/star/linguistic2/XDictionaryList.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/linguistic2/XDictionary1.hpp>
class Window;
namespace binfilter {

class LinguMgrExitLstnr;


// SvxAddEntryToDic return values
#define DIC_ERR_NONE        0
#define DIC_ERR_FULL        1
#define DIC_ERR_READONLY    2
#define DIC_ERR_UNKNOWN     3
#define DIC_ERR_NOT_EXISTS  4
//#define DIC_ERR_ENTRY_EXISTS  5
//#define DIC_ERR_ENTRY_NOTEXISTS   6

///////////////////////////////////////////////////////////////////////////

class LinguMgr
{
    friend class LinguMgrExitLstnr;

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XLinguServiceManager > xLngSvcMgr;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XSpellChecker1 > xSpell;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator >    xHyph;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XThesaurus >     xThes;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > xDicList;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet >         xProp;

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionary1 >   xIgnoreAll;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionary1 >   xChangeAll;

    static LinguMgrExitLstnr                           *pExitLstnr;
    static sal_Bool                                     bExiting;

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator >    GetHyph();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > GetDicList();

    // disallow access to copy-constructor and assignment-operator
    LinguMgr(const LinguMgr &);
    LinguMgr & operator = (const LinguMgr &);

public:

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator >    GetHyphenator();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > GetDictionaryList();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet >         GetLinguPropertySet();


    // update all configuration entries
    static void UpdateAll();
};

///////////////////////////////////////////////////////////////////////////
}//end of namespace binfilter
namespace com { namespace sun { namespace star { namespace linguistic2 {
    class XHyphenatedWord;
}}}}
namespace binfilter {
struct SvxAlternativeSpelling
{
    String      aReplacement;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenatedWord >    xHyphWord;
    INT16       nChangedPos,
                 nChangedLength;
    BOOL        bIsAltSpelling;

    inline SvxAlternativeSpelling();
};

inline SvxAlternativeSpelling::SvxAlternativeSpelling() :
    nChangedPos(-1), nChangedLength(-1), bIsAltSpelling(FALSE)
{
}


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////

//TL:TODO: remove those functions or make them inline
//TL:TODO: remove argument or provide SvxGetIgnoreAllList with the same one

///////////////////////////////////////////////////////////////////////////
// misc functions
//

LanguageType                        SvxLocaleToLanguage(
        const ::com::sun::star::lang::Locale& rLocale );
::com::sun::star::lang::Locale&     SvxLanguageToLocale(
        ::com::sun::star::lang::Locale& rLocale, LanguageType eLang );
::com::sun::star::lang::Locale      SvxCreateLocale( LanguageType eLang );


//TL:TODO: soll mal den rictigen R�ckgabetyp bekommen!


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
