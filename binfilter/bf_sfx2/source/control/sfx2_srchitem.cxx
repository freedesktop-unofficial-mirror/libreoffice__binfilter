/*************************************************************************
 *
 *  $RCSfile: sfx2_srchitem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:11 $
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

// include ---------------------------------------------------------------

#ifndef __SBX_SBXVARIABLE_HXX
#include <svtools/sbxvar.hxx>
#endif
#ifndef _SVT_SEARCHOPT_HXX_
#include <svtools/searchopt.hxx>
#endif

#ifndef _COM_SUN_STAR_UTIL_XREPLACEABLE_HPP_
#include <com/sun/star/util/XReplaceable.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XSEARCHABLE_HPP_
#include <com/sun/star/util/XSearchable.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XSEARCHDESCRIPTOR_HPP_
#include <com/sun/star/util/XSearchDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XPROPERTYREPLACE_HPP_
#include <com/sun/star/util/XPropertyReplace.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XREPLACEDESCRIPTOR_HPP_
#include <com/sun/star/util/XReplaceDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif

#include <svtools/memberid.hrc>
#include <tools/isolang.hxx>

#pragma hdrstop

#define _SVX_SRCHITEM_CXX

#include "sfxsids.hrc"
#define ITEMID_SEARCH   SID_SEARCH_ITEM
#include "srchitem.hxx"

#include <sfxuno.hxx>
namespace binfilter {

//using namespace uno;
using namespace rtl;
using namespace utl;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star::uno;

#define CFG_ROOT_NODE   "Office.Common/SearchOptions"

// STATIC DATA -----------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxSearchItem, SfxPoolItem);

// -----------------------------------------------------------------------

/*N*/ static Sequence< OUString > lcl_GetNotifyNames()
/*N*/ {
/*N*/   // names of transliteration relevant properties
/*N*/   static const char* aTranslitNames[] =
/*N*/   {
/*N*/       "IsMatchCase",                          //  0
/*N*/       "Japanese/IsMatchFullHalfWidthForms",   //  1
/*N*/       "Japanese/IsMatchHiraganaKatakana",     //  2
/*N*/       "Japanese/IsMatchContractions",         //  3
/*N*/       "Japanese/IsMatchMinusDashCho-on",      //  4
/*N*/       "Japanese/IsMatchRepeatCharMarks",      //  5
/*N*/       "Japanese/IsMatchVariantFormKanji",     //  6
/*N*/       "Japanese/IsMatchOldKanaForms",         //  7
/*N*/       "Japanese/IsMatch_DiZi_DuZu",           //  8
/*N*/       "Japanese/IsMatch_BaVa_HaFa",           //  9
/*N*/       "Japanese/IsMatch_TsiThiChi_DhiZi",     // 10
/*N*/       "Japanese/IsMatch_HyuIyu_ByuVyu",       // 11
/*N*/       "Japanese/IsMatch_SeShe_ZeJe",          // 12
/*N*/       "Japanese/IsMatch_IaIya",               // 13
/*N*/       "Japanese/IsMatch_KiKu",                // 14
/*N*/       "Japanese/IsIgnorePunctuation",         // 15
/*N*/       "Japanese/IsIgnoreWhitespace",          // 16
/*N*/       "Japanese/IsIgnoreProlongedSoundMark",  // 17
/*N*/       "Japanese/IsIgnoreMiddleDot"            // 18
/*N*/   };
/*N*/
/*N*/     const int nCount = sizeof( aTranslitNames ) / sizeof( aTranslitNames[0] );
/*N*/   Sequence< OUString > aNames( nCount );
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for (INT32 i = 0;  i < nCount;  ++i)
/*N*/       pNames[i] = OUString::createFromAscii( aTranslitNames[i] );
/*N*/
/*N*/   return aNames;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ SvxSearchItem::SvxSearchItem( const sal_uInt16 nId ) :
/*N*/
/*N*/   SfxPoolItem( nId ),
/*N*/   ConfigItem( OUString::createFromAscii( CFG_ROOT_NODE ) ),
/*N*/
/*N*/   aSearchOpt      (   SearchAlgorithms_ABSOLUTE,
/*N*/                       SearchFlags::LEV_RELAXED,
/*N*/                           OUString(),
/*N*/                           OUString(),
/*N*/                           Locale(),
/*N*/                           2, 2, 2,
/*N*/                           TransliterationModules_IGNORE_CASE ),
/*N*/   nCommand        ( 0 ),
/*N*/   bBackward       ( sal_False ),
/*N*/   bPattern        ( sal_False ),
/*N*/   bContent        ( sal_False ),
/*N*/   eFamily         ( SFX_STYLE_FAMILY_PARA ),
/*N*/   bRowDirection   ( sal_True ),
/*N*/   bAllTables      ( sal_False ),
/*N*/   nCellType       ( SVX_SEARCHIN_FORMULA ),
/*N*/   nAppFlag        ( SVX_SEARCHAPP_WRITER ),
/*N*/   bAsianOptions   ( FALSE )
/*N*/ {
/*N*/   EnableNotification( lcl_GetNotifyNames() );
/*N*/
/*N*/   SvtSearchOptions aOpt;
/*N*/
/*N*/   bBackward       = aOpt.IsBackwards();
/*N*/   bAsianOptions   = aOpt.IsUseAsianOptions();
/*N*/
/*N*/   if (aOpt.IsUseRegularExpression())
/*N*/       aSearchOpt.algorithmType = SearchAlgorithms_REGEXP;
/*N*/   if (aOpt.IsSimilaritySearch())
/*N*/       aSearchOpt.algorithmType = SearchAlgorithms_APPROXIMATE;
/*N*/   if (aOpt.IsWholeWordsOnly())
/*N*/       aSearchOpt.searchFlag |= SearchFlags::NORM_WORD_ONLY;
/*N*/
/*N*/   INT32 &rFlags = aSearchOpt.transliterateFlags;
/*N*/
/*N*/   if (!aOpt.IsMatchCase())
/*N*/       rFlags |= TransliterationModules_IGNORE_CASE;
/*N*/     if ( aOpt.IsMatchFullHalfWidthForms())
/*N*/       rFlags |= TransliterationModules_IGNORE_WIDTH;
/*N*/     if ( aOpt.IsMatchHiraganaKatakana())
/*N*/       rFlags |= TransliterationModules_IGNORE_KANA;
/*N*/     if ( aOpt.IsMatchContractions())
/*N*/       rFlags |= TransliterationModules_ignoreSize_ja_JP;
/*N*/     if ( aOpt.IsMatchMinusDashChoon())
/*N*/       rFlags |= TransliterationModules_ignoreMinusSign_ja_JP;
/*N*/     if ( aOpt.IsMatchRepeatCharMarks())
/*N*/       rFlags |= TransliterationModules_ignoreIterationMark_ja_JP;
/*N*/     if ( aOpt.IsMatchVariantFormKanji())
/*N*/       rFlags |= TransliterationModules_ignoreTraditionalKanji_ja_JP;
/*N*/     if ( aOpt.IsMatchOldKanaForms())
/*N*/       rFlags |= TransliterationModules_ignoreTraditionalKana_ja_JP;
/*N*/     if ( aOpt.IsMatchDiziDuzu())
/*N*/       rFlags |= TransliterationModules_ignoreZiZu_ja_JP;
/*N*/     if ( aOpt.IsMatchBavaHafa())
/*N*/       rFlags |= TransliterationModules_ignoreBaFa_ja_JP;
/*N*/     if ( aOpt.IsMatchTsithichiDhizi())
/*N*/       rFlags |= TransliterationModules_ignoreTiJi_ja_JP;
/*N*/     if ( aOpt.IsMatchHyuiyuByuvyu())
/*N*/       rFlags |= TransliterationModules_ignoreHyuByu_ja_JP;
/*N*/     if ( aOpt.IsMatchSesheZeje())
/*N*/       rFlags |= TransliterationModules_ignoreSeZe_ja_JP;
/*N*/     if ( aOpt.IsMatchIaiya())
/*N*/       rFlags |= TransliterationModules_ignoreIandEfollowedByYa_ja_JP;
/*N*/     if ( aOpt.IsMatchKiku())
/*N*/       rFlags |= TransliterationModules_ignoreKiKuFollowedBySa_ja_JP;
/*N*/   if ( aOpt.IsIgnorePunctuation())
/*N*/       rFlags |= TransliterationModules_ignoreSeparator_ja_JP;
/*N*/   if ( aOpt.IsIgnoreWhitespace())
/*N*/       rFlags |= TransliterationModules_ignoreSpace_ja_JP;
/*N*/   if ( aOpt.IsIgnoreProlongedSoundMark())
/*N*/       rFlags |= TransliterationModules_ignoreProlongedSoundMark_ja_JP;
/*N*/   if ( aOpt.IsIgnoreMiddleDot())
/*N*/       rFlags |= TransliterationModules_ignoreMiddleDot_ja_JP;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxSearchItem::SvxSearchItem( const SvxSearchItem& rItem ) :
/*N*/
/*N*/   SfxPoolItem ( rItem ),
/*N*/   ConfigItem( OUString::createFromAscii( CFG_ROOT_NODE ) ),
/*N*/
/*N*/   aSearchOpt      ( rItem.aSearchOpt ),
/*N*/   nCommand        ( rItem.nCommand ),
/*N*/   bBackward       ( rItem.bBackward ),
/*N*/   bPattern        ( rItem.bPattern ),
/*N*/   bContent        ( rItem.bContent ),
/*N*/   eFamily         ( rItem.eFamily ),
/*N*/   bRowDirection   ( rItem.bRowDirection ),
/*N*/   bAllTables      ( rItem.bAllTables ),
/*N*/   nCellType       ( rItem.nCellType ),
/*N*/   nAppFlag        ( rItem.nAppFlag ),
/*N*/   bAsianOptions   ( rItem.bAsianOptions )
/*N*/ {
/*N*/   EnableNotification( lcl_GetNotifyNames() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxSearchItem::~SvxSearchItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ SfxPoolItem* SvxSearchItem::Clone( SfxItemPool *pPool) const
/*N*/ {
/*N*/   return new SvxSearchItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

//! used below
/*N*/ static BOOL operator == ( const SearchOptions& rItem1, const SearchOptions& rItem2 )
/*N*/ {
/*N*/   return rItem1.algorithmType         == rItem2.algorithmType &&
/*N*/          rItem1.searchFlag            == rItem2.searchFlag    &&
/*N*/          rItem1.searchString          == rItem2.searchString  &&
/*N*/          rItem1.replaceString         == rItem2.replaceString &&
/*N*/          //rItem1.Locale              == rItem2.Locale        &&
/*N*/          rItem1.changedChars          == rItem2.changedChars  &&
/*N*/          rItem1.deletedChars          == rItem2.deletedChars  &&
/*N*/          rItem1.insertedChars         == rItem2.insertedChars &&
/*N*/          rItem1.transliterateFlags    == rItem2.transliterateFlags;
/*N*/ }


/*N*/ int SvxSearchItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal which or type" );
/*N*/   const SvxSearchItem &rSItem = (SvxSearchItem &) rItem;
/*N*/   return ( nCommand       == rSItem.nCommand )        &&
/*N*/          ( bBackward      == rSItem.bBackward )       &&
/*N*/          ( bPattern       == rSItem.bPattern )        &&
/*N*/          ( bContent       == rSItem.bContent )        &&
/*N*/          ( eFamily        == rSItem.eFamily )         &&
/*N*/          ( bRowDirection  == rSItem.bRowDirection )   &&
/*N*/          ( bAllTables     == rSItem.bAllTables )      &&
/*N*/          ( nCellType      == rSItem.nCellType )       &&
/*N*/          ( nAppFlag       == rSItem.nAppFlag )        &&
/*N*/          ( bAsianOptions  == rSItem.bAsianOptions )   &&
/*N*/          ( aSearchOpt     == rSItem.aSearchOpt );
/*N*/ }


//------------------------------------------------------------------------

/*N*/ SfxItemPresentation SvxSearchItem::GetPresentation
/*N*/ (
/*N*/   SfxItemPresentation ePres,
/*N*/   SfxMapUnit          eCoreUnit,
/*N*/   SfxMapUnit          ePresUnit,
/*N*/   XubString&          rText,
/*N*/     const IntlWrapper *
/*N*/ ) const
/*N*/ {
/*N*/   return SFX_ITEM_PRESENTATION_NONE;
/*N*/ }

/*N*/ void SvxSearchItem::GetFromDescriptor( const ::com::sun::star::uno::Reference< ::com::sun::star::util::XSearchDescriptor >& rDescr )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SetSearchString( rDescr->getSearchString() );
//STRIP001  ::com::sun::star::uno::Any aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchWords") );
//STRIP001  sal_Bool bTemp ;
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetWordOnly( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchCaseSensitive") );
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetExact( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchBackwards") );
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetBackward( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchInSelection") );
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetSelection( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchRegularExpression") );
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetRegExp( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarity") );
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetLevenshtein( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityRelax") );
//STRIP001  aAny >>= bTemp ;
//STRIP001  SetLEVRelaxed( bTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityExchange") );
//STRIP001  sal_Int16 nTemp ;
//STRIP001  aAny >>= nTemp ;
//STRIP001  SetLEVOther( nTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityRemove") );
//STRIP001  aAny >>= nTemp ;
//STRIP001  SetLEVShorter( nTemp );
//STRIP001  aAny = rDescr->getPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityAdd") );
//STRIP001  aAny >>= nTemp ;
//STRIP001  SetLEVLonger( nTemp );
/*N*/ }

/*N*/ void SvxSearchItem::SetToDescriptor( ::com::sun::star::uno::Reference< ::com::sun::star::util::XSearchDescriptor > & rDescr )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  rDescr->setSearchString( GetSearchString() );
//STRIP001  ::com::sun::star::uno::Any aAny;
//STRIP001  aAny <<= GetWordOnly() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchWords"), aAny );
//STRIP001  aAny <<= GetExact() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchCaseSensitive"), aAny );
//STRIP001  aAny <<= GetBackward() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchBackwards"), aAny );
//STRIP001  aAny <<= GetSelection() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchInSelection"), aAny );
//STRIP001  aAny <<= GetRegExp() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchRegularExpression"), aAny );
//STRIP001  aAny <<= IsLevenshtein() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarity"), aAny );
//STRIP001  aAny <<= IsLEVRelaxed() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityRelax"), aAny );
//STRIP001  aAny <<= GetLEVOther() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityExchange"), aAny );
//STRIP001  aAny <<= GetLEVShorter() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityRemove"), aAny );
//STRIP001  aAny <<= GetLEVLonger() ;
//STRIP001  rDescr->setPropertyValue( DEFINE_CONST_UNICODE("SearchSimilarityAdd"), aAny );
/*N*/ }


/*N*/ void SvxSearchItem::Notify( const Sequence< OUString > &rPropertyNames )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // applies transliteration changes in the configuration database
//STRIP001  // to the current SvxSearchItem
//STRIP001  SetTransliterationFlags( SvtSearchOptions().GetTransliterationFlags() );
/*N*/ }


/*N*/ void SvxSearchItem::SetMatchFullHalfWidthForms( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if (bVal)
//STRIP001      aSearchOpt.transliterateFlags |=  TransliterationModules_IGNORE_WIDTH;
//STRIP001  else
//STRIP001      aSearchOpt.transliterateFlags &= ~TransliterationModules_IGNORE_WIDTH;
/*N*/ }


/*N*/ void SvxSearchItem::SetWordOnly( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (bVal)
//STRIP001      aSearchOpt.searchFlag |=  SearchFlags::NORM_WORD_ONLY;
//STRIP001  else
//STRIP001      aSearchOpt.searchFlag &= ~SearchFlags::NORM_WORD_ONLY;
/*N*/ }


/*N*/ void SvxSearchItem::SetExact( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (!bVal)
//STRIP001      aSearchOpt.transliterateFlags |=  TransliterationModules_IGNORE_CASE;
//STRIP001  else
//STRIP001      aSearchOpt.transliterateFlags &= ~TransliterationModules_IGNORE_CASE;
/*N*/ }


/*N*/ void SvxSearchItem::SetSelection( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (bVal)
//STRIP001  {
//STRIP001      aSearchOpt.searchFlag |=  (SearchFlags::REG_NOT_BEGINOFLINE |
//STRIP001                                 SearchFlags::REG_NOT_ENDOFLINE);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aSearchOpt.searchFlag &= ~(SearchFlags::REG_NOT_BEGINOFLINE |
//STRIP001                                 SearchFlags::REG_NOT_ENDOFLINE);
//STRIP001  }
/*N*/ }


/*N*/ void SvxSearchItem::SetRegExp( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (bVal)
//STRIP001      aSearchOpt.algorithmType = SearchAlgorithms_REGEXP;
//STRIP001  else
//STRIP001      aSearchOpt.algorithmType = SearchAlgorithms_ABSOLUTE;
/*N*/ }


/*N*/ void SvxSearchItem::SetLEVRelaxed( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (bVal)
//STRIP001      aSearchOpt.searchFlag |=  SearchFlags::LEV_RELAXED;
//STRIP001  else
//STRIP001      aSearchOpt.searchFlag &= ~SearchFlags::LEV_RELAXED;
/*N*/ }


/*N*/ void SvxSearchItem::SetLevenshtein( sal_Bool bVal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (bVal)
//STRIP001      aSearchOpt.algorithmType = SearchAlgorithms_APPROXIMATE;
//STRIP001  else
//STRIP001      aSearchOpt.algorithmType = SearchAlgorithms_ABSOLUTE;
/*N*/ }


/*N*/ void SvxSearchItem::SetTransliterationFlags( sal_Int32 nFlags )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   aSearchOpt.transliterateFlags = nFlags;
/*N*/ }

/*N*/ sal_Bool SvxSearchItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return sal_True;//STRIP001
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001     switch ( nMemberId )
//STRIP001  {
//STRIP001         case MID_SEARCH_COMMAND:
//STRIP001             rVal <<= (sal_Int16) nCommand; break;
//STRIP001         case MID_SEARCH_STYLEFAMILY:
//STRIP001             rVal <<= (sal_Int16) eFamily; break;
//STRIP001         case MID_SEARCH_CELLTYPE:
//STRIP001             rVal <<= (sal_Int32) nCellType; break;
//STRIP001         case MID_SEARCH_ROWDIRECTION:
//STRIP001             rVal <<= (sal_Bool) bRowDirection; break;
//STRIP001         case MID_SEARCH_ALLTABLES:
//STRIP001             rVal <<= (sal_Bool) bAllTables; break;
//STRIP001         case MID_SEARCH_BACKWARD:
//STRIP001             rVal <<= (sal_Bool) bBackward; break;
//STRIP001         case MID_SEARCH_PATTERN:
//STRIP001             rVal <<= (sal_Bool) bPattern; break;
//STRIP001         case MID_SEARCH_CONTENT:
//STRIP001             rVal <<= (sal_Bool) bContent; break;
//STRIP001         case MID_SEARCH_ASIANOPTIONS:
//STRIP001             rVal <<= (sal_Bool) bAsianOptions; break;
//STRIP001         case MID_SEARCH_ALGORITHMTYPE:
//STRIP001             rVal <<= (sal_Int16) aSearchOpt.algorithmType; break;
//STRIP001         case MID_SEARCH_FLAGS:
//STRIP001             rVal <<= aSearchOpt.searchFlag; break;
//STRIP001         case MID_SEARCH_SEARCHSTRING:
//STRIP001             rVal <<= aSearchOpt.searchString; break;
//STRIP001         case MID_SEARCH_REPLACESTRING:
//STRIP001             rVal <<= aSearchOpt.replaceString; break;
//STRIP001         case MID_SEARCH_CHANGEDCHARS:
//STRIP001             rVal <<= aSearchOpt.changedChars; break;
//STRIP001         case MID_SEARCH_DELETEDCHARS:
//STRIP001             rVal <<= aSearchOpt.deletedChars; break;
//STRIP001         case MID_SEARCH_INSERTEDCHARS:
//STRIP001             rVal <<= aSearchOpt.insertedChars; break;
//STRIP001         case MID_SEARCH_TRANSLITERATEFLAGS:
//STRIP001             rVal <<= aSearchOpt.transliterateFlags; break;
//STRIP001         case MID_SEARCH_LOCALE:
//STRIP001         {
//STRIP001             sal_Int16 nLocale;
//STRIP001             if (aSearchOpt.Locale.Language.getLength() || aSearchOpt.Locale.Country.getLength() )
//STRIP001                 nLocale = ConvertIsoNamesToLanguage( aSearchOpt.Locale.Language, aSearchOpt.Locale.Country );
//STRIP001          else
//STRIP001                 nLocale = LANGUAGE_NONE;
//STRIP001             rVal <<= nLocale;
//STRIP001             break;
//STRIP001         }
//STRIP001      default:
//STRIP001             DBG_ERROR( "Unknown MemberId" );
//STRIP001             return sal_False;
//STRIP001  }
//STRIP001
//STRIP001     return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxSearchItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return sal_True;//STRIP001
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001     sal_Bool bRet = sal_False;
//STRIP001     sal_Int32 nInt;
//STRIP001     switch ( nMemberId )
//STRIP001  {
//STRIP001         case MID_SEARCH_COMMAND:
//STRIP001             bRet = (rVal >>= nInt); nCommand = (sal_uInt16) nInt; break;
//STRIP001         case MID_SEARCH_STYLEFAMILY:
//STRIP001             bRet = (rVal >>= nInt); eFamily =  (SfxStyleFamily) (sal_Int16) nInt; break;
//STRIP001         case MID_SEARCH_CELLTYPE:
//STRIP001             bRet = (rVal >>= nInt); nCellType = (sal_uInt16) nInt; break;
//STRIP001         case MID_SEARCH_ROWDIRECTION:
//STRIP001             bRet = (rVal >>= bRowDirection); break;
//STRIP001         case MID_SEARCH_ALLTABLES:
//STRIP001             bRet = (rVal >>= bAllTables); break;
//STRIP001         case MID_SEARCH_BACKWARD:
//STRIP001             bRet = (rVal >>= bBackward); break;
//STRIP001         case MID_SEARCH_PATTERN:
//STRIP001             bRet = (rVal >>= bPattern); break;
//STRIP001         case MID_SEARCH_CONTENT:
//STRIP001             bRet = (rVal >>= bContent); break;
//STRIP001         case MID_SEARCH_ASIANOPTIONS:
//STRIP001             bRet = (rVal >>= bAsianOptions); break;
//STRIP001         case MID_SEARCH_ALGORITHMTYPE:
//STRIP001             bRet = (rVal >>= nInt); aSearchOpt.algorithmType = (::com::sun::star::util::SearchAlgorithms) (sal_Int16) nInt; break;
//STRIP001         case MID_SEARCH_FLAGS:
//STRIP001             bRet = (rVal >>= aSearchOpt.searchFlag); break;
//STRIP001         case MID_SEARCH_SEARCHSTRING:
//STRIP001             bRet = (rVal >>= aSearchOpt.searchString); break;
//STRIP001         case MID_SEARCH_REPLACESTRING:
//STRIP001             bRet = (rVal >>= aSearchOpt.replaceString); break;
//STRIP001         case MID_SEARCH_CHANGEDCHARS:
//STRIP001             bRet = (rVal >>= aSearchOpt.changedChars); break;
//STRIP001         case MID_SEARCH_DELETEDCHARS:
//STRIP001             bRet = (rVal >>= aSearchOpt.deletedChars); break;
//STRIP001         case MID_SEARCH_INSERTEDCHARS:
//STRIP001             bRet = (rVal >>= aSearchOpt.insertedChars); break;
//STRIP001         case MID_SEARCH_TRANSLITERATEFLAGS:
//STRIP001             bRet = (rVal >>= aSearchOpt.transliterateFlags); break;
//STRIP001         case MID_SEARCH_LOCALE:
//STRIP001         {
//STRIP001             bRet = (rVal >>= nInt);
//STRIP001             if ( bRet )
//STRIP001             {
//STRIP001                 if ( nInt == LANGUAGE_NONE )
//STRIP001                 {
//STRIP001                     aSearchOpt.Locale = ::com::sun::star::lang::Locale();
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     String sLanguage, sCountry;
//STRIP001                     ConvertLanguageToIsoNames( (sal_Int16) nInt, sLanguage, sCountry );
//STRIP001                     aSearchOpt.Locale.Language = sLanguage;
//STRIP001                     aSearchOpt.Locale.Country = sCountry;
//STRIP001                 }
//STRIP001             }
//STRIP001             break;
//STRIP001         }
//STRIP001      default:
//STRIP001             DBG_ERROR( "Unknown MemberId" );
//STRIP001  }
//STRIP001
//STRIP001     return bRet;
/*N*/ }


}
