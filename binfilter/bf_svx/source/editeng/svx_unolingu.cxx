/*************************************************************************
 *
 *  $RCSfile: svx_unolingu.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2005-04-04 12:36:26 $
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

#pragma hdrstop

#include <unolingu.hxx>

#include <cppuhelper/implbase1.hxx> // helper for implementations

#ifndef _LANG_HXX
#include <tools/lang.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XSTORABLE_HPP_
#include <com/sun/star/frame/XStorable.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XEVENTLISTENER_HPP_
#include <com/sun/star/lang/XEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XAVAILABLELOCALES_HPP_
#include <com/sun/star/linguistic2/XAvailableLocales.hpp>
#endif
#include <comphelper/processfactory.hxx>

#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx> // helper for implementations
#endif

#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif
#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _LINGUISTIC_MISC_HXX_
#include <bf_linguistic/misc.hxx>
#endif

#ifndef _SVX_DIALMGR_HXX
#include <dialmgr.hxx>
#endif
#include "dialogs.hrc"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::rtl;
using namespace ::comphelper;
using namespace ::com::sun::star;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::linguistic2;

#define A2OU(x) OUString::createFromAscii(x)

///////////////////////////////////////////////////////////////////////////


/*N*/ static Reference< XLinguServiceManager > GetLngSvcMgr_Impl()
/*N*/ {
/*N*/   Reference< XLinguServiceManager > xRes;
/*N*/   Reference< XMultiServiceFactory >  xMgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   if (xMgr.is())
/*N*/   {
/*N*/       xRes = Reference< XLinguServiceManager > ( xMgr->createInstance(
/*N*/               OUString( RTL_CONSTASCII_USTRINGPARAM(
/*N*/                   "com.sun.star.linguistic2.LinguServiceManager" ) ) ), UNO_QUERY ) ;
/*N*/   }
/*N*/   return xRes;
/*N*/ }

///////////////////////////////////////////////////////////////////////////

/*N*/ BOOL lcl_FindEntry( const OUString &rEntry, const Sequence< OUString > &rCfgSvcs )
/*N*/ {
/*N*/     INT32 nRes = -1;
/*N*/     INT32 nEntries = rCfgSvcs.getLength();
/*N*/     const OUString *pEntry = rCfgSvcs.getConstArray();
/*N*/     for (INT32 i = 0;  i < nEntries && nRes == -1;  ++i)
/*N*/     {
/*?*/         if (rEntry == pEntry[i])
/*?*/             nRes = i;
/*N*/     }
/*N*/     return nRes != -1;
/*N*/ }


/*N*/ Sequence< OUString > lcl_RemoveMissingEntries(
/*N*/         const Sequence< OUString > &rCfgSvcs,
/*N*/         const Sequence< OUString > &rAvailSvcs )
/*N*/ {
/*N*/     Sequence< OUString > aRes( rCfgSvcs.getLength() );
/*N*/     OUString *pRes = aRes.getArray();
/*N*/     INT32 nCnt = 0;
/*N*/
/*N*/     INT32 nEntries = rCfgSvcs.getLength();
/*N*/     const OUString *pEntry = rCfgSvcs.getConstArray();
/*N*/     for (INT32 i = 0;  i < nEntries;  ++i)
/*N*/     {
/*N*/         if (pEntry[i].getLength() && lcl_FindEntry( pEntry[i], rAvailSvcs ))
/*N*/             pRes[ nCnt++ ] = pEntry[i];
/*N*/     }
/*N*/
/*N*/     aRes.realloc( nCnt );
/*N*/     return aRes;
/*N*/ }


/*N*/ Sequence< OUString > lcl_GetLastFoundSvcs(
/*N*/         SvtLinguConfig &rCfg,
/*N*/         const OUString &rLastFoundList ,
/*N*/         const Locale &rAvailLocale )
/*N*/ {
/*N*/     Sequence< OUString > aRes;
/*N*/
/*N*/     OUString aCfgLocaleStr( ConvertLanguageToIsoString(
/*N*/                                 SvxLocaleToLanguage( rAvailLocale ) ) );
/*N*/
/*N*/     Sequence< OUString > aNodeNames( rCfg.GetNodeNames(rLastFoundList) );
/*N*/     BOOL bFound = lcl_FindEntry( aCfgLocaleStr, aNodeNames);
/*N*/
/*N*/     if (bFound)
/*N*/     {
/*N*/         Sequence< OUString > aNames(1);
/*N*/         OUString &rNodeName = aNames.getArray()[0];
/*N*/         rNodeName = rLastFoundList;
/*N*/         rNodeName += OUString::valueOf( (sal_Unicode)'/' );
/*N*/         rNodeName += aCfgLocaleStr;
/*N*/         Sequence< Any > aValues( rCfg.GetProperties( aNames ) );
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/         const Any *pValue = aValues.getConstArray();
/*N*/ #endif
/*N*/         if (aValues.getLength())
/*N*/         {
/*N*/             DBG_ASSERT( aValues.getLength() == 1, "unexpected length of sequence" );
/*N*/             Sequence< OUString > aSvcImplNames;
/*N*/             if (aValues.getConstArray()[0] >>= aSvcImplNames)
/*N*/                 aRes = aSvcImplNames;
/*N*/             else
/*N*/                 DBG_ERROR( "type mismatch" );
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return aRes;
/*N*/ }


/*N*/ Sequence< OUString > lcl_GetNewEntries(
/*N*/         const Sequence< OUString > &rLastFoundSvcs,
/*N*/         const Sequence< OUString > &rAvailSvcs )
/*N*/ {
/*N*/     INT32 nLen = rAvailSvcs.getLength();
/*N*/     Sequence< OUString > aRes( nLen );
/*N*/     OUString *pRes = aRes.getArray();
/*N*/     INT32 nCnt = 0;
/*N*/
/*N*/     const OUString *pEntry = rAvailSvcs.getConstArray();
/*N*/     for (INT32 i = 0;  i < nLen;  ++i)
/*N*/     {
/*N*/         if (pEntry[i].getLength() && !lcl_FindEntry( pEntry[i], rLastFoundSvcs ))
/*N*/             pRes[ nCnt++ ] = pEntry[i];
/*N*/     }
/*N*/
/*N*/     aRes.realloc( nCnt );
/*N*/     return aRes;
/*N*/ }


/*N*/ Sequence< OUString > lcl_MergeSeq(
/*N*/         const Sequence< OUString > &rCfgSvcs,
/*N*/         const Sequence< OUString > &rNewSvcs )
/*N*/ {
/*N*/     Sequence< OUString > aRes( rCfgSvcs.getLength() + rNewSvcs.getLength() );
/*N*/     OUString *pRes = aRes.getArray();
/*N*/     INT32 nCnt = 0;
/*N*/
/*N*/     for (INT32 k = 0;  k < 2;  ++k)
/*N*/     {
/*N*/         const Sequence< OUString > &rSeq = k == 0 ? rCfgSvcs : rNewSvcs;
/*N*/         INT32 nLen = rSeq.getLength();
/*N*/         const OUString *pEntry = rSeq.getConstArray();
/*N*/         for (INT32 i = 0;  i < nLen;  ++i)
/*N*/         {
/*N*/             if (pEntry[i].getLength() && !lcl_FindEntry( pEntry[i], aRes ))
/*N*/                 pRes[ nCnt++ ] = pEntry[i];
/*N*/         }
/*N*/     }
/*N*/
/*N*/     aRes.realloc( nCnt );
/*N*/     return aRes;
/*N*/ }

///////////////////////////////////////////////////////////////////////////

// static member initialization
BOOL SvxLinguConfigUpdate::bUpdated = FALSE;

/*N*/ void SvxLinguConfigUpdate::UpdateAll()
/*N*/ {
/*N*/     if (!IsUpdated())
/*N*/     {
/*N*/         Reference< XLinguServiceManager > xLngSvcMgr( GetLngSvcMgr_Impl() );
/*N*/         DBG_ASSERT( xLngSvcMgr.is(), "service manager missing")
/*N*/         if (!xLngSvcMgr.is())
/*N*/             return;
/*N*/
/*N*/         SvtLinguConfig aCfg;
/*N*/
/*N*/         const sal_Char * apServices[3]      =  { SN_THESAURUS,         SN_SPELLCHECKER,            SN_HYPHENATOR };
              const sal_Char * apActiveLists[3]    =  { "ServiceManager/ThesaurusList",      "ServiceManager/SpellCheckerList",         "ServiceManager/HyphenatorList" };
              const sal_Char * apLastFoundLists[3] =  { "ServiceManager/LastFoundThesauri",  "ServiceManager/LastFoundSpellCheckers",   "ServiceManager/LastFoundHyphenators" };
/*N*/
/*N*/         for (int k = 0;  k < 3;  ++k)
/*N*/         {
/*N*/             OUString aService( A2OU( (sal_Char *)apServices[k]) );
/*N*/             OUString aActiveList( A2OU( (sal_Char *) apActiveLists[k]) );
/*N*/             OUString aLastFoundList( A2OU( (sal_Char *) apLastFoundLists[k]) );
/*N*/             INT32 i;
/*N*/
/*N*/             //
/*N*/             // remove configured but not available language/services entries
/*N*/             //
/*N*/             Sequence< OUString > aNodeNames( aCfg.GetNodeNames( aActiveList ) );   // list of configured locales
/*N*/             INT32 nNodeNames = aNodeNames.getLength();
/*N*/             const OUString *pNodeName = aNodeNames.getConstArray();
/*N*/             for (i = 0;  i < nNodeNames;  ++i)
/*N*/             {
/*N*/                 Locale aLocale( SvxCreateLocale( ConvertIsoStringToLanguage(pNodeName[i]) ) );
/*N*/                 Sequence< OUString > aCfgSvcs(
/*N*/                         xLngSvcMgr->getConfiguredServices( aService, aLocale ));
/*N*/                 Sequence< OUString > aAvailSvcs(
/*N*/                         xLngSvcMgr->getAvailableServices( aService, aLocale ));
/*N*/                 aCfgSvcs = lcl_RemoveMissingEntries( aCfgSvcs, aAvailSvcs );
/*N*/                 xLngSvcMgr->setConfiguredServices( aService, aLocale, aCfgSvcs );
/*N*/             }
/*N*/
/*N*/             //
/*N*/             // add new available language/servcice entries
/*N*/             //
/*N*/             Reference< XAvailableLocales > xAvail( xLngSvcMgr, UNO_QUERY );
/*N*/             Sequence< Locale > aAvailLocales( xAvail->getAvailableLocales(aService) );
/*N*/             INT32 nAvailLocales = aAvailLocales.getLength();
/*N*/             const Locale *pAvailLocale = aAvailLocales.getConstArray();
/*N*/             for (i = 0;  i < nAvailLocales;  ++i)
/*N*/             {
/*N*/                 Sequence< OUString > aAvailSvcs(
/*N*/                         xLngSvcMgr->getAvailableServices( aService, pAvailLocale[i] ));
/*N*/                 Sequence< OUString > aLastFoundSvcs(
/*N*/                         lcl_GetLastFoundSvcs( aCfg, aLastFoundList , pAvailLocale[i] ));
/*N*/                 Sequence< OUString > aNewSvcs =
/*N*/                         lcl_GetNewEntries( aLastFoundSvcs, aAvailSvcs );
/*N*/
/*N*/                 Sequence< OUString > aCfgSvcs(
/*N*/                         xLngSvcMgr->getConfiguredServices( aService, pAvailLocale[i] ));
/*N*/                 aCfgSvcs = lcl_MergeSeq( aCfgSvcs, aNewSvcs );
/*N*/                 xLngSvcMgr->setConfiguredServices( aService, pAvailLocale[i], aCfgSvcs );
/*N*/             }
/*N*/
/*N*/             //
/*N*/             // set last found services to currently available ones
/*N*/             //
/*N*/             Sequence< PropertyValue > aValues( nAvailLocales );
/*N*/             PropertyValue *pValue = aValues.getArray();
/*N*/             for (i = 0;  i < nAvailLocales;  ++i)
/*N*/             {
/*?*/                 Sequence< OUString > aSvcImplNames(
/*?*/                         xLngSvcMgr->getConfiguredServices( aService, pAvailLocale[i] ) );
/*?*/
/*?*/ #if OSL_DEBUG_LEVEL > 1
/*?*/                 INT32 nSvcs = aSvcImplNames.getLength();
/*?*/                 const OUString *pSvcImplName = aSvcImplNames.getConstArray();
/*?*/                 for (INT32 j = 0;  j < nSvcs;  ++j)
/*?*/                 {
/*?*/                     OUString aImplName( pSvcImplName[j] );
/*?*/                 }
/*?*/ #endif
/*?*/                 // build value to be written back to configuration
/*?*/                 Any aCfgAny;
/*?*/                 aCfgAny <<= aSvcImplNames;
/*?*/                 DBG_ASSERT( aCfgAny.hasValue(), "missing value for 'Any' type" );
/*?*/
/*?*/                 OUString aCfgLocaleStr( ConvertLanguageToIsoString(
/*?*/                                             SvxLocaleToLanguage( pAvailLocale[i] ) ) );
/*?*/                 pValue->Value = aCfgAny;
/*?*/                 pValue->Name  = aLastFoundList;
/*?*/                 pValue->Name += OUString::valueOf( (sal_Unicode) '/' );
/*?*/                 pValue->Name += aCfgLocaleStr;
/*?*/                 pValue++;
/*N*/             }
/*N*/             // change, add new or replace existing entries.
/*N*/             BOOL bRes = aCfg.ReplaceSetProperties( aLastFoundList, aValues );
/*N*/             DBG_ASSERT( bRes, "failed to set LastFound list" );
/*N*/         }
/*N*/
/*N*/         bUpdated = TRUE;
/*N*/     }
/*N*/ }

///////////////////////////////////////////////////////////////////////////


//! Dummy implementation in order to avoid loading of lingu DLL
//! when only the XSupportedLocales interface is used.
//! The dummy accesses the real implementation (and thus loading the DLL)
//! when "real" work needs to be done only.
/*N*/ class ThesDummy_Impl :
/*N*/     public cppu::WeakImplHelper1< XThesaurus >
/*N*/ {
/*N*/     Reference< XThesaurus >     xThes;      // the real one...
/*N*/     Sequence< Locale >         *pLocaleSeq;
/*N*/
/*N*/     void GetCfgLocales();
/*N*/
/*N*/     void GetThes_Impl();
/*N*/
/*N*/ public:
/*N*/     ThesDummy_Impl() : pLocaleSeq(0)  {}
/*N*/     ~ThesDummy_Impl();
/*N*/
/*N*/     // XSupportedLocales
/*N*/     virtual ::com::sun::star::uno::Sequence<
/*N*/           ::com::sun::star::lang::Locale > SAL_CALL
/*N*/       getLocales()
/*N*/           throw(::com::sun::star::uno::RuntimeException);
/*N*/     virtual sal_Bool SAL_CALL
/*N*/         hasLocale( const ::com::sun::star::lang::Locale& rLocale )
/*N*/           throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/   // XThesaurus
/*N*/     virtual ::com::sun::star::uno::Sequence<
/*N*/           ::com::sun::star::uno::Reference<
/*N*/               ::com::sun::star::linguistic2::XMeaning > > SAL_CALL
/*N*/         queryMeanings( const ::rtl::OUString& rTerm,
/*N*/                 const ::com::sun::star::lang::Locale& rLocale,
/*N*/                 const ::com::sun::star::beans::PropertyValues& rProperties )
/*N*/           throw(::com::sun::star::lang::IllegalArgumentException,
/*N*/                 ::com::sun::star::uno::RuntimeException);
/*N*/ };


/*N*/ ThesDummy_Impl::~ThesDummy_Impl()
/*N*/ {
/*N*/     delete pLocaleSeq;
/*N*/ }


/*N*/ void ThesDummy_Impl::GetCfgLocales()
/*N*/ {
/*N*/     if (!pLocaleSeq)
/*N*/     {
/*N*/         SvtLinguConfig aCfg;
/*N*/         String  aNode( A2OU( "ServiceManager/ThesaurusList" ) );
/*N*/         Sequence < OUString > aNodeNames( aCfg.GetNodeNames( aNode ) );
/*N*/         const OUString *pNodeNames = aNodeNames.getConstArray();
/*N*/         INT32 nLen = aNodeNames.getLength();
/*N*/         pLocaleSeq = new Sequence< Locale >( nLen );
/*N*/         Locale *pLocale = pLocaleSeq->getArray();
/*N*/         for (INT32 i = 0;  i < nLen;  ++i)
/*N*/         {
/*N*/             pLocale[i] = SvxCreateLocale(
/*N*/                             ConvertIsoStringToLanguage( pNodeNames[i] ) );
/*N*/         }
/*N*/     }
/*N*/ }


/*N*/ void ThesDummy_Impl::GetThes_Impl()
/*N*/ {
/*N*/     // update configuration before accessing the service
/*N*/     if (!SvxLinguConfigUpdate::IsUpdated())
/*?*/         SvxLinguConfigUpdate::UpdateAll();
/*N*/
/*N*/     if (!xThes.is())
/*N*/     {
/*N*/         Reference< XLinguServiceManager > xLngSvcMgr( GetLngSvcMgr_Impl() );
/*N*/         if (xLngSvcMgr.is())
/*N*/             xThes = xLngSvcMgr->getThesaurus();
/*N*/
/*?*/         if (xThes.is())
/*?*/         {
/*?*/             // no longer needed...
/*?*/             delete pLocaleSeq;    pLocaleSeq = 0;
/*?*/         }
/*N*/     }
/*N*/ }


/*N*/ uno::Sequence< lang::Locale > SAL_CALL
/*N*/         ThesDummy_Impl::getLocales()
/*N*/             throw(uno::RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); uno::Sequence< lang::Locale > aa; return aa; //STRIP001
//STRIP001     if (SvxLinguConfigUpdate::IsUpdated())
//STRIP001         GetThes_Impl();
//STRIP001     if (xThes.is())
//STRIP001         return xThes->getLocales();
//STRIP001     else if (!pLocaleSeq)
//STRIP001         GetCfgLocales();
//STRIP001     return *pLocaleSeq;
/*N*/ }


/*N*/ sal_Bool SAL_CALL
/*N*/         ThesDummy_Impl::hasLocale( const lang::Locale& rLocale )
/*N*/             throw(uno::RuntimeException)
/*N*/ {
/*N*/     if (SvxLinguConfigUpdate::IsUpdated())
/*N*/         GetThes_Impl();
/*N*/     if (xThes.is())
/*?*/         return xThes->hasLocale( rLocale );
/*N*/     else if (!pLocaleSeq)
/*N*/         GetCfgLocales();
/*N*/     BOOL bFound = FALSE;
/*N*/     INT32 nLen = pLocaleSeq->getLength();
/*N*/     const Locale *pLocale = pLocaleSeq->getConstArray();
/*N*/     const Locale *pEnd = pLocale + nLen;
/*N*/     for ( ;  pLocale < pEnd  &&  !bFound;  ++pLocale)
/*N*/     {
/*N*/         bFound = pLocale->Language == rLocale.Language  &&
/*N*/                  pLocale->Country  == rLocale.Country   &&
/*N*/                  pLocale->Variant  == rLocale.Variant;
/*N*/     }
/*N*/     return bFound;
/*N*/ }


/*N*/ uno::Sequence< uno::Reference< linguistic2::XMeaning > > SAL_CALL
/*N*/         ThesDummy_Impl::queryMeanings(
/*N*/                 const ::rtl::OUString& rTerm,
/*N*/                 const lang::Locale& rLocale,
/*N*/                 const beans::PropertyValues& rProperties )
/*N*/             throw(lang::IllegalArgumentException,
/*N*/                   uno::RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); uno::Sequence< uno::Reference< linguistic2::XMeaning > > aRes;return aRes; //STRIP001
//STRIP001 /*?*/     GetThes_Impl();
//STRIP001 /*?*/     uno::Sequence< uno::Reference< linguistic2::XMeaning > > aRes;
//STRIP001 /*?*/     DBG_ASSERT( xThes.is(), "Thesaurus missing" );
//STRIP001 /*?*/     if (xThes.is())
//STRIP001 /*?*/         aRes = xThes->queryMeanings( rTerm, rLocale, rProperties );
//STRIP001 /*?*/     return aRes;
/*N*/ }


///////////////////////////////////////////////////////////////////////////


//! Dummy implementation in order to avoid loading of lingu DLL.
//! The dummy accesses the real implementation (and thus loading the DLL)
//! when it needs to be done only.
/*N*/ class SpellDummy_Impl :
/*N*/     public cppu::WeakImplHelper1< XSpellChecker1 >
/*N*/ {
/*N*/     Reference< XSpellChecker1 >     xSpell;      // the real one...
/*N*/
/*N*/     void    GetSpell_Impl();
/*N*/
/*N*/ public:
/*N*/
/*N*/   // XSupportedLanguages (for XSpellChecker1)
/*N*/     virtual ::com::sun::star::uno::Sequence< sal_Int16 > SAL_CALL
/*N*/       getLanguages()
/*N*/           throw(::com::sun::star::uno::RuntimeException);
/*N*/     virtual sal_Bool SAL_CALL
/*N*/       hasLanguage( sal_Int16 nLanguage )
/*N*/           throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/   // XSpellChecker1 (same as XSpellChecker but sal_Int16 for language)
/*N*/   virtual sal_Bool SAL_CALL
/*N*/         isValid( const ::rtl::OUString& rWord, sal_Int16 nLanguage,
/*N*/                 const ::com::sun::star::beans::PropertyValues& rProperties )
/*N*/           throw(::com::sun::star::lang::IllegalArgumentException,
/*N*/                 ::com::sun::star::uno::RuntimeException);
/*N*/   virtual ::com::sun::star::uno::Reference<
/*N*/           ::com::sun::star::linguistic2::XSpellAlternatives > SAL_CALL
/*N*/         spell( const ::rtl::OUString& rWord, sal_Int16 nLanguage,
/*N*/                 const ::com::sun::star::beans::PropertyValues& rProperties )
/*N*/           throw(::com::sun::star::lang::IllegalArgumentException,
/*N*/                 ::com::sun::star::uno::RuntimeException);
/*N*/ };


/*N*/ void SpellDummy_Impl::GetSpell_Impl()
/*N*/ { DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     // update configuration before accessing the service
//STRIP001     if (!SvxLinguConfigUpdate::IsUpdated())
//STRIP001         SvxLinguConfigUpdate::UpdateAll();
//STRIP001
//STRIP001     if (!xSpell.is())
//STRIP001     {
//STRIP001         Reference< XLinguServiceManager > xLngSvcMgr( GetLngSvcMgr_Impl() );
//STRIP001         if (xLngSvcMgr.is())
//STRIP001             xSpell = Reference< XSpellChecker1 >( xLngSvcMgr->getSpellChecker(), UNO_QUERY );
//STRIP001     }
/*N*/ }


/*N*/ uno::Sequence< sal_Int16 > SAL_CALL
/*N*/     SpellDummy_Impl::getLanguages()
/*N*/         throw(uno::RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return uno::Sequence< sal_Int16 >(); //STRIP001
//STRIP001     GetSpell_Impl();
//STRIP001     if (xSpell.is())
//STRIP001         return xSpell->getLanguages();
//STRIP001     else
//STRIP001         return uno::Sequence< sal_Int16 >();
/*N*/ }


/*N*/ sal_Bool SAL_CALL
/*N*/     SpellDummy_Impl::hasLanguage( sal_Int16 nLanguage )
/*N*/         throw(uno::RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP");return FALSE; //STRIP001
//STRIP001     GetSpell_Impl();
//STRIP001     BOOL bRes = FALSE;
//STRIP001     if (xSpell.is())
//STRIP001         bRes = xSpell->hasLanguage( nLanguage );
//STRIP001     return bRes;
/*N*/ }


/*N*/ sal_Bool SAL_CALL
/*N*/     SpellDummy_Impl::isValid( const ::rtl::OUString& rWord, sal_Int16 nLanguage,
/*N*/             const beans::PropertyValues& rProperties )
/*N*/         throw(lang::IllegalArgumentException,
/*N*/               uno::RuntimeException)
/*N*/ {
/*?*/     GetSpell_Impl();
/*?*/     BOOL bRes = TRUE;
/*?*/     if (xSpell.is())
/*?*/         bRes = xSpell->isValid( rWord, nLanguage, rProperties );
/*?*/     return bRes;
/*N*/ }


/*N*/ uno::Reference< linguistic2::XSpellAlternatives > SAL_CALL
/*N*/     SpellDummy_Impl::spell( const ::rtl::OUString& rWord, sal_Int16 nLanguage,
/*N*/             const beans::PropertyValues& rProperties )
/*N*/         throw(lang::IllegalArgumentException,
/*N*/               uno::RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); uno::Reference< linguistic2::XSpellAlternatives > xRes; return xRes; //STRIP001
//STRIP001     GetSpell_Impl();
//STRIP001     uno::Reference< linguistic2::XSpellAlternatives > xRes;
//STRIP001     if (xSpell.is())
//STRIP001         xRes = xSpell->spell( rWord, nLanguage, rProperties );
//STRIP001     return xRes;
/*N*/ }


///////////////////////////////////////////////////////////////////////////


//! Dummy implementation in order to avoid loading of lingu DLL.
//! The dummy accesses the real implementation (and thus loading the DLL)
//! when it needs to be done only.
/*N*/ class HyphDummy_Impl :
/*N*/     public cppu::WeakImplHelper1< XHyphenator >
/*N*/ {
/*N*/     Reference< XHyphenator >     xHyph;      // the real one...
/*N*/
/*N*/     void    GetHyph_Impl();
/*N*/
/*N*/ public:
/*N*/
/*N*/     // XSupportedLocales
/*N*/     virtual ::com::sun::star::uno::Sequence<
/*N*/           ::com::sun::star::lang::Locale > SAL_CALL
/*N*/       getLocales()
/*N*/           throw(::com::sun::star::uno::RuntimeException);
/*N*/     virtual sal_Bool SAL_CALL
/*N*/         hasLocale( const ::com::sun::star::lang::Locale& rLocale )
/*N*/           throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/     // XHyphenator
/*N*/     virtual ::com::sun::star::uno::Reference<
/*N*/           ::com::sun::star::linguistic2::XHyphenatedWord > SAL_CALL
/*N*/         hyphenate( const ::rtl::OUString& rWord,
/*N*/                 const ::com::sun::star::lang::Locale& rLocale,
/*N*/               sal_Int16 nMaxLeading,
/*N*/                 const ::com::sun::star::beans::PropertyValues& rProperties )
/*N*/           throw(::com::sun::star::lang::IllegalArgumentException,
/*N*/                 ::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Reference<
/*N*/           ::com::sun::star::linguistic2::XHyphenatedWord > SAL_CALL
/*N*/         queryAlternativeSpelling( const ::rtl::OUString& rWord,
/*N*/                 const ::com::sun::star::lang::Locale& rLocale,
/*N*/               sal_Int16 nIndex,
/*N*/                 const ::com::sun::star::beans::PropertyValues& rProperties )
/*N*/           throw(::com::sun::star::lang::IllegalArgumentException,
/*N*/                 ::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Reference<
/*N*/           ::com::sun::star::linguistic2::XPossibleHyphens > SAL_CALL
/*N*/       createPossibleHyphens(
/*N*/                 const ::rtl::OUString& rWord,
/*N*/                 const ::com::sun::star::lang::Locale& rLocale,
/*N*/                 const ::com::sun::star::beans::PropertyValues& rProperties )
/*N*/           throw(::com::sun::star::lang::IllegalArgumentException,
/*N*/                 ::com::sun::star::uno::RuntimeException);
/*N*/ };


/*N*/ void HyphDummy_Impl::GetHyph_Impl()
/*N*/ {
/*N*/     // update configuration before accessing the service
/*N*/     if (!SvxLinguConfigUpdate::IsUpdated())
/*N*/         SvxLinguConfigUpdate::UpdateAll();
/*N*/
/*N*/     if (!xHyph.is())
/*N*/     {
/*N*/         Reference< XLinguServiceManager > xLngSvcMgr( GetLngSvcMgr_Impl() );
/*N*/         if (xLngSvcMgr.is())
/*N*/             xHyph = xLngSvcMgr->getHyphenator();
/*N*/     }
/*N*/ }


/*N*/ uno::Sequence< lang::Locale > SAL_CALL
/*N*/     HyphDummy_Impl::getLocales()
/*N*/         throw(uno::RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return uno::Sequence< lang::Locale >();//STRIP001
//STRIP001     GetHyph_Impl();
//STRIP001     if (xHyph.is())
//STRIP001         return xHyph->getLocales();
//STRIP001     else
//STRIP001         return uno::Sequence< lang::Locale >();
/*N*/ }


/*N*/ sal_Bool SAL_CALL
/*N*/     HyphDummy_Impl::hasLocale( const lang::Locale& rLocale )
/*N*/         throw(uno::RuntimeException)
/*N*/ {
/*N*/     GetHyph_Impl();
/*N*/     BOOL bRes = FALSE;
/*N*/     if (xHyph.is())
/*N*/         bRes = xHyph->hasLocale( rLocale );
/*N*/     return bRes;
/*N*/ }


/*N*/ uno::Reference< linguistic2::XHyphenatedWord > SAL_CALL
/*N*/     HyphDummy_Impl::hyphenate(
/*N*/             const ::rtl::OUString& rWord,
/*N*/             const lang::Locale& rLocale,
/*N*/             sal_Int16 nMaxLeading,
/*N*/             const beans::PropertyValues& rProperties )
/*N*/         throw(lang::IllegalArgumentException,
/*N*/               uno::RuntimeException)
/*N*/ {
/*N*/     GetHyph_Impl();
/*N*/     uno::Reference< linguistic2::XHyphenatedWord > xRes;
/*N*/     if (xHyph.is())
/*N*/         xRes = xHyph->hyphenate( rWord, rLocale, nMaxLeading, rProperties );
/*N*/     return xRes;
/*N*/ }


/*N*/ uno::Reference< linguistic2::XHyphenatedWord > SAL_CALL
/*N*/     HyphDummy_Impl::queryAlternativeSpelling(
/*N*/             const ::rtl::OUString& rWord,
/*N*/             const lang::Locale& rLocale,
/*N*/             sal_Int16 nIndex,
/*N*/             const PropertyValues& rProperties )
/*N*/         throw(lang::IllegalArgumentException,
/*N*/               uno::RuntimeException)
/*N*/ {
/*N*/     GetHyph_Impl();
/*N*/     uno::Reference< linguistic2::XHyphenatedWord > xRes;
/*N*/     if (xHyph.is())
/*N*/         xRes = xHyph->queryAlternativeSpelling( rWord, rLocale, nIndex, rProperties );
/*N*/     return xRes;
/*N*/ }


/*N*/ uno::Reference< linguistic2::XPossibleHyphens > SAL_CALL
/*N*/     HyphDummy_Impl::createPossibleHyphens(
/*N*/             const ::rtl::OUString& rWord,
/*N*/             const lang::Locale& rLocale,
/*N*/             const beans::PropertyValues& rProperties )
/*N*/         throw(lang::IllegalArgumentException,
/*N*/               uno::RuntimeException)
/*N*/ {
/*?*/     GetHyph_Impl();
/*?*/     uno::Reference< linguistic2::XPossibleHyphens > xRes;
/*?*/     if (xHyph.is())
/*?*/         xRes = xHyph->createPossibleHyphens( rWord, rLocale, rProperties );
/*?*/     return xRes;
/*N*/ }


///////////////////////////////////////////////////////////////////////////


/*N*/ typedef cppu::WeakImplHelper1 < XEventListener > LinguMgrAppExitLstnrBaseClass;

/*N*/ class LinguMgrAppExitLstnr : public LinguMgrAppExitLstnrBaseClass
/*N*/ {
/*N*/   Reference< XComponent >         xDesktop;
/*N*/
/*N*/ public:
/*N*/   LinguMgrAppExitLstnr();
/*N*/   virtual ~LinguMgrAppExitLstnr();
/*N*/
/*N*/   virtual void    AtExit() = 0;
/*N*/
/*N*/
/*N*/   // lang::XEventListener
/*N*/     virtual void  SAL_CALL disposing(const EventObject& rSource)
/*N*/           throw( RuntimeException );
/*N*/ };

/*N*/ LinguMgrAppExitLstnr::LinguMgrAppExitLstnr()
/*N*/ {
/*N*/   // add object to frame::Desktop EventListeners in order to properly call
/*N*/   // the AtExit function at appliction exit.
/*N*/
/*N*/   Reference< XMultiServiceFactory >  xMgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   if ( xMgr.is() )
/*N*/   {
/*N*/       xDesktop = Reference< XComponent > ( xMgr->createInstance(
/*N*/               OUString( RTL_CONSTASCII_USTRINGPARAM ( "com.sun.star.frame.Desktop" ) ) ), UNO_QUERY ) ;
/*N*/       if (xDesktop.is())
/*N*/           xDesktop->addEventListener( this );
/*N*/   }
/*N*/ }

/*N*/ LinguMgrAppExitLstnr::~LinguMgrAppExitLstnr()
/*N*/ {
/*N*/   if (xDesktop.is())
/*N*/   {
/*?*/       xDesktop->removeEventListener( this );
/*?*/       xDesktop = NULL;    //! release reference to desktop
/*N*/   }
/*N*/   DBG_ASSERT(!xDesktop.is(), "reference to desktop should be realeased");
/*N*/ }

/*N*/ void LinguMgrAppExitLstnr::disposing(const EventObject& rSource)
/*N*/       throw( RuntimeException )
/*N*/ {
/*N*/   if (xDesktop.is()  &&  rSource.Source == xDesktop)
/*N*/   {
/*N*/       xDesktop->removeEventListener( this );
/*N*/       xDesktop = NULL;    //! release reference to desktop
/*N*/
/*N*/       AtExit();
/*N*/   }
/*N*/ }

///////////////////////////////////////////////////////////////////////////

/*N*/ class LinguMgrExitLstnr : public LinguMgrAppExitLstnr
/*N*/ {
/*N*/ public:
/*N*/   virtual void    AtExit();
/*N*/ };

/*N*/ void LinguMgrExitLstnr::AtExit()
/*N*/ {
/*N*/   // release references
/*N*/   LinguMgr::xLngSvcMgr    = 0;
/*N*/   LinguMgr::xSpell        = 0;
/*N*/   LinguMgr::xHyph         = 0;
/*N*/   LinguMgr::xThes         = 0;
/*N*/   LinguMgr::xDicList      = 0;
/*N*/   LinguMgr::xProp         = 0;
/*N*/   LinguMgr::xIgnoreAll    = 0;
/*N*/   LinguMgr::xChangeAll    = 0;
/*N*/
/*N*/   LinguMgr::bExiting      = sal_True;
/*N*/
/*N*/   //TL:TODO: MBA fragen wie ich ohne Absturz hier meinen Speicher
/*N*/   //  wieder freibekomme...
/*N*/   //delete LinguMgr::pExitLstnr;
/*N*/   LinguMgr::pExitLstnr    = 0;
/*N*/ }

///////////////////////////////////////////////////////////////////////////


// static member initialization
/*N*/ LinguMgrExitLstnr *           LinguMgr::pExitLstnr    = 0;
/*N*/ sal_Bool                      LinguMgr::bExiting      = sal_False;
/*N*/ Reference< XLinguServiceManager > LinguMgr::xLngSvcMgr    = 0;
/*N*/ Reference< XSpellChecker1 >   LinguMgr::xSpell        = 0;
/*N*/ Reference< XHyphenator >      LinguMgr::xHyph         = 0;
/*N*/ Reference< XThesaurus >       LinguMgr::xThes         = 0;
/*N*/ Reference< XDictionaryList >  LinguMgr::xDicList      = 0;
/*N*/ Reference< XPropertySet >         LinguMgr::xProp         = 0;
/*N*/ Reference< XDictionary1 >         LinguMgr::xIgnoreAll    = 0;
/*N*/ Reference< XDictionary1 >         LinguMgr::xChangeAll    = 0;


//STRIP001 Reference< XLinguServiceManager > LinguMgr::GetLngSvcMgr()
//STRIP001 {
//STRIP001  if (bExiting)
//STRIP001      return 0;
//STRIP001
//STRIP001  if (!pExitLstnr)
//STRIP001      pExitLstnr = new LinguMgrExitLstnr;
//STRIP001
//STRIP001  if (!xLngSvcMgr.is())
//STRIP001      xLngSvcMgr = GetLngSvcMgr_Impl();
//STRIP001
//STRIP001  return xLngSvcMgr;
//STRIP001 }


/*N*/ Reference< XSpellChecker1 > LinguMgr::GetSpellChecker()
/*N*/ {
/*N*/   return xSpell.is() ? xSpell : GetSpell();
/*N*/ }

/*N*/ Reference< XHyphenator > LinguMgr::GetHyphenator()
/*N*/ {
/*N*/   return xHyph.is() ? xHyph : GetHyph();
/*N*/ }

/*N*/ Reference< XThesaurus > LinguMgr::GetThesaurus()
/*N*/ {
/*N*/   return xThes.is() ? xThes : GetThes();
/*N*/ }

/*N*/ Reference< XDictionaryList > LinguMgr::GetDictionaryList()
/*N*/ {
/*N*/   return xDicList.is() ? xDicList : GetDicList();
/*N*/ }

//STRIP001 Reference< XPropertySet > LinguMgr::GetLinguPropertySet()
//STRIP001 {
//STRIP001  return xProp.is() ? xProp : GetProp();
//STRIP001 }

//STRIP001 Reference< XDictionary1 > LinguMgr::GetStandardDic()
//STRIP001 {
//STRIP001  //! don't hold reference to this
//STRIP001  //! (it may be removed from dictionary list and needs to be
//STRIP001  //! created empty if accessed again)
//STRIP001  return GetStandard();
//STRIP001 }

//STRIP001 Reference< XDictionary1 > LinguMgr::GetIgnoreAllList()
//STRIP001 {
//STRIP001  return xIgnoreAll.is() ? xIgnoreAll : GetIgnoreAll();
//STRIP001 }

//STRIP001 Reference< XDictionary1 > LinguMgr::GetChangeAllList()
//STRIP001 {
//STRIP001  return xChangeAll.is() ? xChangeAll : GetChangeAll();
//STRIP001 }

/*N*/ Reference< XSpellChecker1 > LinguMgr::GetSpell()
/*N*/ {
/*N*/   if (bExiting)
/*N*/       return 0;
/*N*/
/*N*/   if (!pExitLstnr)
/*N*/       pExitLstnr = new LinguMgrExitLstnr;
/*N*/
/*N*/     //! use dummy implementation in order to avoid loading of lingu DLL
/*N*/     xSpell = new SpellDummy_Impl;
/*N*/
/*    if (!xLngSvcMgr.is())
        xLngSvcMgr = GetLngSvcMgr_Impl();

    if (xLngSvcMgr.is())
    {
        xSpell = Reference< XSpellChecker1 > (
                        xLngSvcMgr->getSpellChecker(), UNO_QUERY );
    }
*/
/*N*/   return xSpell;
/*N*/ }

/*N*/ Reference< XHyphenator > LinguMgr::GetHyph()
/*N*/ {
/*N*/   if (bExiting)
/*N*/       return 0;
/*N*/
/*N*/   if (!pExitLstnr)
/*N*/       pExitLstnr = new LinguMgrExitLstnr;
/*N*/
/*N*/     //! use dummy implementation in order to avoid loading of lingu DLL
/*N*/     xHyph = new HyphDummy_Impl;
/*N*/
/*
    if (!xLngSvcMgr.is())
        xLngSvcMgr = GetLngSvcMgr_Impl();

    if (xLngSvcMgr.is())
    {
        xHyph = xLngSvcMgr->getHyphenator();
    }
*/
/*N*/   return xHyph;
/*N*/ }

/*N*/ Reference< XThesaurus > LinguMgr::GetThes()
/*N*/ {
/*N*/   if (bExiting)
/*N*/       return 0;
/*N*/
/*N*/   if (!pExitLstnr)
/*N*/       pExitLstnr = new LinguMgrExitLstnr;
/*N*/
/*N*/     //! use dummy implementation in order to avoid loading of lingu DLL
/*N*/     //! when only the XSupportedLocales interface is used.
/*N*/     //! The dummy accesses the real implementation (and thus loading the DLL)
/*N*/     //! when "real" work needs to be done only.
/*N*/     xThes = new ThesDummy_Impl;
/*
    if (!xLngSvcMgr.is())
        xLngSvcMgr = GetLngSvcMgr_Impl();

    if (xLngSvcMgr.is())
    {
        xThes = xLngSvcMgr->getThesaurus();
    }
*/
/*N*/   return xThes;
/*N*/ }


//STRIP001 void LinguMgr::UpdateAll()
//STRIP001 {
//STRIP001 }


/*N*/ Reference< XDictionaryList > LinguMgr::GetDicList()
/*N*/ {
/*N*/   if (bExiting)
/*N*/       return 0;
/*N*/
/*N*/   if (!pExitLstnr)
/*N*/       pExitLstnr = new LinguMgrExitLstnr;
/*N*/
/*N*/   Reference< XMultiServiceFactory >  xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/   if (xMgr.is())
/*N*/   {
/*N*/       xDicList = Reference< XDictionaryList > ( xMgr->createInstance(
/*N*/                     A2OU("com.sun.star.linguistic2.DictionaryList") ), UNO_QUERY );
/*N*/   }
/*N*/   return xDicList;
/*N*/ }

//STRIP001 Reference< XPropertySet > LinguMgr::GetProp()
//STRIP001 {
//STRIP001  if (bExiting)
//STRIP001      return 0;
//STRIP001
//STRIP001  if (!pExitLstnr)
//STRIP001      pExitLstnr = new LinguMgrExitLstnr;
//STRIP001
//STRIP001  Reference< XMultiServiceFactory >  xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001  if (xMgr.is())
//STRIP001  {
//STRIP001      xProp = Reference< XPropertySet > ( xMgr->createInstance(
//STRIP001                     A2OU("com.sun.star.linguistic2.LinguProperties") ), UNO_QUERY );
//STRIP001  }
//STRIP001  return xProp;
//STRIP001 }

//STRIP001 Reference< XDictionary1 > LinguMgr::GetIgnoreAll()
//STRIP001 {
//STRIP001  if (bExiting)
//STRIP001      return 0;
//STRIP001
//STRIP001  if (!pExitLstnr)
//STRIP001      pExitLstnr = new LinguMgrExitLstnr;
//STRIP001
//STRIP001  Reference< XDictionaryList >  xTmpDicList( GetDictionaryList() );
//STRIP001  if (xTmpDicList.is())
//STRIP001  {
//STRIP001      xIgnoreAll = Reference< XDictionary1 > ( xTmpDicList->getDictionaryByName(
//STRIP001                     A2OU("IgnoreAllList") ), UNO_QUERY );
//STRIP001  }
//STRIP001  return xIgnoreAll;
//STRIP001 }

//STRIP001 Reference< XDictionary1 > LinguMgr::GetChangeAll()
//STRIP001 {
//STRIP001  if (bExiting)
//STRIP001      return 0;
//STRIP001
//STRIP001  if (!pExitLstnr)
//STRIP001      pExitLstnr = new LinguMgrExitLstnr;
//STRIP001
//STRIP001  Reference< XDictionaryList >  xDicList( GetDictionaryList() , UNO_QUERY );
//STRIP001  if (xDicList.is())
//STRIP001  {
//STRIP001      xChangeAll = Reference< XDictionary1 > (
//STRIP001                      xDicList->createDictionary(
//STRIP001                             A2OU("ChangeAllList"),
//STRIP001                          SvxCreateLocale( LANGUAGE_NONE ),
//STRIP001                          DictionaryType_NEGATIVE, String() ), UNO_QUERY );
//STRIP001  }
//STRIP001  return xChangeAll;
//STRIP001 }

//STRIP001 Reference< XDictionary1 > LinguMgr::GetStandard()
//STRIP001 {
//STRIP001  // Tries to return a dictionary which may hold positive entries is
//STRIP001  // persistent and not read-only.
//STRIP001
//STRIP001  if (bExiting)
//STRIP001      return 0;
//STRIP001
//STRIP001  Reference< XDictionaryList >  xTmpDicList( GetDictionaryList() );
//STRIP001  if (!xTmpDicList.is())
//STRIP001      return NULL;
//STRIP001
//STRIP001  const OUString aDicName( RTL_CONSTASCII_USTRINGPARAM( "standard.dic" ) );
//STRIP001  Reference< XDictionary1 >   xDic( xTmpDicList->getDictionaryByName( aDicName ),
//STRIP001                                    UNO_QUERY );
//STRIP001     if (!xDic.is())
//STRIP001     {
//STRIP001         // try to create standard dictionary
//STRIP001         Reference< XDictionary >    xTmp;
//STRIP001         try
//STRIP001         {
//STRIP001             xTmp =  xTmpDicList->createDictionary( aDicName,
//STRIP001                         SvxCreateLocale( LANGUAGE_NONE ),
//STRIP001                         DictionaryType_POSITIVE,
//STRIP001                         SvxGetDictionaryURL( aDicName, sal_True ) );
//STRIP001         }
//STRIP001         catch(::com::sun::star::uno::Exception &)
//STRIP001         {
//STRIP001         }
//STRIP001
//STRIP001         // add new dictionary to list
//STRIP001         if (xTmp.is())
//STRIP001             xTmpDicList->addDictionary( xTmp );
//STRIP001         xDic = Reference< XDictionary1 > ( xTmp, UNO_QUERY );
//STRIP001     }
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001     Reference< XStorable >      xStor( xDic, UNO_QUERY );
//STRIP001     DBG_ASSERT( xDic.is() && xDic->getDictionaryType() == DictionaryType_POSITIVE,
//STRIP001             "wrong dictionary type");
//STRIP001     DBG_ASSERT( xDic.is() && xDic->getLanguage() == LANGUAGE_NONE,
//STRIP001             "wrong dictionary language");
//STRIP001     DBG_ASSERT( !xStor.is() || (xStor->hasLocation() && !xStor->isReadonly()),
//STRIP001             "dictionary not editable" );
//STRIP001 #endif
//STRIP001
//STRIP001  return xDic;
//STRIP001 }

///////////////////////////////////////////////////////////////////////////

//STRIP001 Reference< XSpellChecker1 >  SvxGetSpellChecker()
//STRIP001 {
//STRIP001  return LinguMgr::GetSpellChecker();
//STRIP001 }

//STRIP001 Reference< XHyphenator >  SvxGetHyphenator()
//STRIP001 {
//STRIP001  return LinguMgr::GetHyphenator();
//STRIP001 }

//STRIP001 Reference< XThesaurus >  SvxGetThesaurus()
//STRIP001 {
//STRIP001  return LinguMgr::GetThesaurus();
//STRIP001 }

//STRIP001 Reference< XDictionaryList >  SvxGetDictionaryList()
//STRIP001 {
//STRIP001  return LinguMgr::GetDictionaryList();
//STRIP001 }

//STRIP001 Reference< XPropertySet >    SvxGetLinguPropertySet()
//STRIP001 {
//STRIP001  return LinguMgr::GetLinguPropertySet();
//STRIP001 }

//TL:TODO: remove argument or provide SvxGetIgnoreAllList with the same one
//STRIP001 Reference< XDictionary1 >  SvxGetOrCreatePosDic(
//STRIP001      Reference< XDictionaryList >  xDicList )
//STRIP001 {
//STRIP001  return LinguMgr::GetStandardDic();
//STRIP001 }

//STRIP001 Reference< XDictionary1 >  SvxGetIgnoreAllList()
//STRIP001 {
//STRIP001  return LinguMgr::GetIgnoreAllList();
//STRIP001 }

//STRIP001 Reference< XDictionary1 >  SvxGetChangeAllList()
//STRIP001 {
//STRIP001  return LinguMgr::GetChangeAllList();
//STRIP001 }

///////////////////////////////////////////////////////////////////////////


#ifndef _COM_SUN_STAR_LINGUISTIC2_XHYPHENATEDWORD_HPP_
#include <com/sun/star/linguistic2/XHyphenatedWord.hpp>
#endif

//STRIP001 SvxAlternativeSpelling SvxGetAltSpelling(
//STRIP001      const ::com::sun::star::uno::Reference<
//STRIP001          ::com::sun::star::linguistic2::XHyphenatedWord > & rHyphWord )
//STRIP001 {
//STRIP001  SvxAlternativeSpelling aRes;
//STRIP001  if (rHyphWord.is() && rHyphWord->isAlternativeSpelling())
//STRIP001  {
//STRIP001      OUString aWord( rHyphWord->getWord() ),
//STRIP001                  aAltWord( rHyphWord->getHyphenatedWord() );
//STRIP001      INT16   nHyphenationPos     = rHyphWord->getHyphenationPos(),
//STRIP001              nHyphenPos          = rHyphWord->getHyphenPos();
//STRIP001         INT16   nLen    = (INT16)aWord.getLength();
//STRIP001         INT16   nAltLen = (INT16)aAltWord.getLength();
//STRIP001      const sal_Unicode *pWord    = aWord.getStr(),
//STRIP001                           *pAltWord = aAltWord.getStr();
//STRIP001
//STRIP001         // count number of chars from the left to the
//STRIP001         // hyphenation pos / hyphen pos that are equal
//STRIP001         INT16 nL = 0;
//STRIP001         while (nL <= nHyphenationPos && nL <= nHyphenPos
//STRIP001                && pWord[ nL ] == pAltWord[ nL ])
//STRIP001             ++nL;
//STRIP001         // count number of chars from the right to the
//STRIP001         // hyphenation pos / hyphen pos that are equal
//STRIP001         INT16 nR = 0;
//STRIP001         INT32 nIdx    = nLen - 1;
//STRIP001         INT32 nAltIdx = nAltLen - 1;
//STRIP001         while (nIdx > nHyphenationPos && nAltIdx > nHyphenPos
//STRIP001                && pWord[ nIdx-- ] == pAltWord[ nAltIdx-- ])
//STRIP001             ++nR;
//STRIP001
//STRIP001         aRes.aReplacement       = OUString( aAltWord.copy( nL, nAltLen - nL - nR ) );
//STRIP001         aRes.nChangedPos        = (INT16) nL;
//STRIP001         aRes.nChangedLength     = nLen - nL - nR;
//STRIP001      aRes.bIsAltSpelling     = TRUE;
//STRIP001      aRes.xHyphWord          = rHyphWord;
//STRIP001  }
//STRIP001  return aRes;
//STRIP001 }


///////////////////////////////////////////////////////////////////////////

//STRIP001 SvxDicListChgClamp::SvxDicListChgClamp( Reference< XDictionaryList >  &rxDicList ) :
//STRIP001  xDicList    ( rxDicList )
//STRIP001 {
//STRIP001  if (xDicList.is())
//STRIP001  {
//STRIP001      xDicList->beginCollectEvents();
//STRIP001  }
//STRIP001 }

//STRIP001 SvxDicListChgClamp::~SvxDicListChgClamp()
//STRIP001 {
//STRIP001  if (xDicList.is())
//STRIP001  {
//STRIP001      xDicList->endCollectEvents();
//STRIP001  }
//STRIP001 }

///////////////////////////////////////////////////////////////////////////

//STRIP001 String SvxGetDictionaryURL(const String &rDicName, sal_Bool bIsUserDic)
//STRIP001 {
//STRIP001  // build URL to use for new (persistent) dictionaries
//STRIP001
//STRIP001  SvtPathOptions aPathOpt;
//STRIP001  String aDirName( bIsUserDic ?
//STRIP001          aPathOpt.GetUserDictionaryPath() : aPathOpt.GetDictionaryPath() );
//STRIP001
//STRIP001  INetURLObject aURLObj;
//STRIP001  aURLObj.SetSmartProtocol( INET_PROT_FILE );
//STRIP001  aURLObj.SetSmartURL( aDirName );
//STRIP001  DBG_ASSERT(!aURLObj.HasError(), "lng : invalid URL");
//STRIP001  aURLObj.Append( rDicName, INetURLObject::ENCODE_ALL );
//STRIP001  DBG_ASSERT(!aURLObj.HasError(), "lng : invalid URL");
//STRIP001
//STRIP001  return aURLObj.GetMainURL( INetURLObject::DECODE_TO_IURI );
//STRIP001 }

//TL:TODO: soll mal den rictigen Rückgabetyp bekommen!
//STRIP001 sal_Bool SvxAddEntryToDic(
//STRIP001      Reference< XDictionary >  &rxDic,
//STRIP001      const OUString &rWord, sal_Bool bIsNeg,
//STRIP001      const OUString &rRplcTxt, sal_Int16 nRplcLang,
//STRIP001      sal_Bool bStripDot )
//STRIP001 {
//STRIP001  if (!rxDic.is())
//STRIP001      return DIC_ERR_NOT_EXISTS;
//STRIP001
//STRIP001  OUString aTmp( rWord );
//STRIP001  if (bStripDot)
//STRIP001  {
//STRIP001      sal_Int32 nLen = rWord.getLength();
//STRIP001      if (nLen > 0  &&  '.' == rWord[ nLen - 1])
//STRIP001      {
//STRIP001          // remove trailing '.'
//STRIP001          // (this is the official way to do this :-( )
//STRIP001          aTmp = aTmp.copy( 0, nLen - 1 );
//STRIP001      }
//STRIP001  }
//STRIP001  sal_Bool bAddOk = rxDic->add( aTmp, bIsNeg, rRplcTxt );
//STRIP001
//STRIP001  sal_Int16 nRes = DIC_ERR_NONE;
//STRIP001  if (!bAddOk)
//STRIP001  {
//STRIP001      if (rxDic->isFull())
//STRIP001          nRes = DIC_ERR_FULL;
//STRIP001      else
//STRIP001      {
//STRIP001          Reference< XStorable >  xStor( rxDic, UNO_QUERY );
//STRIP001          if (xStor.is() && xStor->isReadonly())
//STRIP001              nRes = DIC_ERR_READONLY;
//STRIP001          else
//STRIP001              nRes = DIC_ERR_UNKNOWN;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return (sal_Bool)nRes;
//STRIP001 }

//STRIP001 short SvxDicError( Window *pParent, sal_Int16 nError )
//STRIP001 {
//STRIP001  short nRes = 0;
//STRIP001  if (DIC_ERR_NONE != nError)
//STRIP001  {
//STRIP001      int nRid;
//STRIP001      switch (nError)
//STRIP001      {
//STRIP001          case DIC_ERR_FULL     : nRid = RID_SVXSTR_DIC_ERR_FULL;  break;
//STRIP001          case DIC_ERR_READONLY : nRid = RID_SVXSTR_DIC_ERR_READONLY;  break;
//STRIP001          default:
//STRIP001              nRid = RID_SVXSTR_DIC_ERR_UNKNOWN;
//STRIP001              DBG_ASSERT(0, "unexpected case");
//STRIP001      }
//STRIP001      nRes = InfoBox( pParent, SVX_RESSTR( nRid ) ).Execute();
//STRIP001  }
//STRIP001  return nRes;
//STRIP001 }

//STRIP001 sal_Bool SvxSaveDictionaries( const Reference< XDictionaryList >  &xDicList )
//STRIP001 {
//STRIP001  if (!xDicList.is())
//STRIP001      return sal_True;
//STRIP001
//STRIP001  sal_Bool bRet = sal_True;
//STRIP001
//STRIP001  Sequence< Reference< XDictionary >  > aDics( xDicList->getDictionaries() );
//STRIP001  const Reference< XDictionary >  *pDic = aDics.getConstArray();
//STRIP001  INT32 nCount = aDics.getLength();
//STRIP001  for (INT32 i = 0;  i < nCount;  i++)
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          Reference< XStorable >  xStor( pDic[i], UNO_QUERY );
//STRIP001          if (xStor.is())
//STRIP001          {
//STRIP001              if (!xStor->isReadonly() && xStor->hasLocation())
//STRIP001                  xStor->store();
//STRIP001          }
//STRIP001      }
//STRIP001         catch(::com::sun::star::uno::Exception &)
//STRIP001      {
//STRIP001          bRet = sal_False;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ LanguageType SvxLocaleToLanguage( const Locale& rLocale )
/*N*/ {
/*N*/   //  empty Locale -> LANGUAGE_NONE
/*N*/   if ( rLocale.Language.getLength() == 0 )
/*N*/       return LANGUAGE_NONE;
/*N*/
/*N*/   //  Variant of Locale is ignored
/*N*/   return ConvertIsoNamesToLanguage( rLocale.Language, rLocale.Country );
/*N*/ }

/*N*/ Locale& SvxLanguageToLocale( Locale& rLocale, LanguageType eLang )
/*N*/ {
/*N*/   String aLangStr, aCtryStr;
/*N*/   if ( eLang != LANGUAGE_NONE /* &&  eLang != LANGUAGE_SYSTEM */)
/*N*/       ConvertLanguageToIsoNames( eLang, aLangStr, aCtryStr );
/*N*/
/*N*/   rLocale.Language = aLangStr;
/*N*/   rLocale.Country  = aCtryStr;
/*N*/   rLocale.Variant  = OUString();
/*N*/
/*N*/   return rLocale;
/*N*/ }

/*N*/ Locale SvxCreateLocale( LanguageType eLang )
/*N*/ {
/*N*/   String aLangStr, aCtryStr;
/*N*/   if ( eLang != LANGUAGE_NONE /* &&  eLang != LANGUAGE_SYSTEM */)
/*N*/       ConvertLanguageToIsoNames( eLang, aLangStr, aCtryStr );
/*N*/
/*N*/   return Locale( aLangStr, aCtryStr, OUString() );
/*N*/ }


}
