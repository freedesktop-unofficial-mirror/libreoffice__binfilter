/*************************************************************************
 *
 *  $RCSfile: unolingu.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:23 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _UNO_LINGU_HXX
#define _UNO_LINGU_HXX

#ifndef _LANG_HXX
#include <tools/lang.hxx>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _VOS_REFERNCE_HXX_
#include <vos/refernce.hxx>
#endif

#ifndef _COM_SUN_STAR_UTIL_LANGUAGE_HPP_
#include <com/sun/star/util/Language.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XLINGUSERVICEMANAGER_HPP_
#include <com/sun/star/linguistic2/XLinguServiceManager.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XSPELLCHECKER1_HPP_
#include <com/sun/star/linguistic2/XSpellChecker1.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XHYPHENATOR_HPP_
#include <com/sun/star/linguistic2/XHyphenator.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XTHESAURUS_HPP_
#include <com/sun/star/linguistic2/XThesaurus.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARYLIST_HPP_
#include <com/sun/star/linguistic2/XDictionaryList.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARY1_HPP_
#include <com/sun/star/linguistic2/XDictionary1.hpp>
#endif
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
// SvxLinguConfigUpdate
// class to update configuration items when (before!) the linguistic is used.
//
// This class is called by all the dummy implementations to update all of the
// configuration (list of used/available services) when the linguistic is
// accessed for the first time.

class SvxLinguConfigUpdate
{
    static BOOL bUpdated;

public:

    static BOOL IsUpdated() { return bUpdated; }
    static void UpdateAll();
};

///////////////////////////////////////////////////////////////////////////

class LinguMgr
{
    friend class LinguMgrExitLstnr;

    //static ::VOS::ORefCount aRefCount;

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
        ::com::sun::star::linguistic2::XSpellChecker1 > GetSpell();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator >    GetHyph();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XThesaurus >     GetThes();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > GetDicList();
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::beans::XPropertySet >         GetProp();
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary1 >   GetStandard();
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary1 >   GetIgnoreAll();
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary1 >   GetChangeAll();

    // disallow access to copy-constructor and assignment-operator
    LinguMgr(const LinguMgr &);
    LinguMgr & operator = (const LinguMgr &);

public:

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XSpellChecker1 > GetSpellChecker();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator >    GetHyphenator();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XThesaurus >     GetThesaurus();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > GetDictionaryList();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet >         GetLinguPropertySet();

//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XLinguServiceManager > GetLngSvcMgr();
//STRIP001
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary1 >   GetStandardDic();
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary1 >   GetIgnoreAllList();
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary1 >   GetChangeAllList();

    // update all configuration entries
    static void UpdateAll();
};

///////////////////////////////////////////////////////////////////////////
}//end of namespace binfilter
namespace com { namespace sun { namespace star { namespace linguistic2 {
    class XHyphenatedWord;
}}}};
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

//STRIP001 SvxAlternativeSpelling SvxGetAltSpelling(
//STRIP001      const ::com::sun::star::uno::Reference<
//STRIP001          ::com::sun::star::linguistic2::XHyphenatedWord > & rHyphWord );

///////////////////////////////////////////////////////////////////////////

//STRIP001 class SvxDicListChgClamp
//STRIP001 {
//STRIP001 private:
//STRIP001  ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionaryList >    xDicList;
//STRIP001
//STRIP001  // disallow access to copy-constructor and assignment-operator
//STRIP001  SvxDicListChgClamp(const SvxDicListChgClamp &);
//STRIP001  SvxDicListChgClamp & operator = (const SvxDicListChgClamp &);
//STRIP001
//STRIP001 public:
//STRIP001  SvxDicListChgClamp( ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionaryList >  &rxDicList );
//STRIP001  ~SvxDicListChgClamp();
//STRIP001 };

///////////////////////////////////////////////////////////////////////////

//TL:TODO: remove those functions or make them inline
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XSpellChecker1 > SvxGetSpellChecker();
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XHyphenator >    SvxGetHyphenator();
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XThesaurus >     SvxGetThesaurus();
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XDictionaryList > SvxGetDictionaryList();
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::beans::XPropertySet >         SvxGetLinguPropertySet();
//TL:TODO: remove argument or provide SvxGetIgnoreAllList with the same one
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XDictionary1 >   SvxGetOrCreatePosDic(
//STRIP001          ::com::sun::star::uno::Reference<
//STRIP001              ::com::sun::star::linguistic2::XDictionaryList >  xDicList );
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XDictionary1 >   SvxGetIgnoreAllList();
//STRIP001 ::com::sun::star::uno::Reference<
//STRIP001  ::com::sun::star::linguistic2::XDictionary1 >   SvxGetChangeAllList();

///////////////////////////////////////////////////////////////////////////
// misc functions
//

LanguageType                        SvxLocaleToLanguage(
        const ::com::sun::star::lang::Locale& rLocale );
::com::sun::star::lang::Locale&     SvxLanguageToLocale(
        ::com::sun::star::lang::Locale& rLocale, LanguageType eLang );
::com::sun::star::lang::Locale      SvxCreateLocale( LanguageType eLang );

//STRIP001 String   SvxGetDictionaryURL(const String &rDicName,
//STRIP001                          sal_Bool bIsUserDic = sal_True);

//TL:TODO: soll mal den rictigen Rückgabetyp bekommen!
//STRIP001 sal_Bool SvxAddEntryToDic(
//STRIP001  ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionary >  &rxDic,
//STRIP001  const ::rtl::OUString &rWord, sal_Bool bIsNeg,
//STRIP001  const ::rtl::OUString &rRplcTxt, sal_Int16 nRplcLang,
//STRIP001  sal_Bool bStripDot = sal_True );
//STRIP001 short    SvxDicError( Window *pParent, sal_Int16 nError );

//STRIP001 sal_Bool SvxSaveDictionaries(
//STRIP001  const ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XDictionaryList >  &xDicList );

}//end of namespace binfilter
#endif

