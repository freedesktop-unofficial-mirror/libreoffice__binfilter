/*************************************************************************
 *
 *  $RCSfile: svx_svxacorr.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:27 $
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

#define ITEMID_UNDERLINE    0
#define ITEMID_WEIGHT       0
#define ITEMID_ESCAPEMENT   0
#define ITEMID_CHARSETCOLOR 0
#define ITEMID_COLOR        0

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _LANG_HXX //autogen
#include <tools/lang.hxx>
#endif
#ifndef _TOOLS_TABLE_HXX
#include <tools/table.hxx>
#endif
//#ifndef _SYSTEM_HXX //autogen
//#include <vcl/system.hxx>
//#endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _STORINFO_HXX //autogen
#include <sot/storinfo.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SFX_DOCFILE_HXX
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_HELP_HXX
#include <bf_sfx2/sfxhelp.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif
// fuer die Sort-String-Arrays aus dem SVMEM.HXX
#define _SVSTDARR_STRINGSISORTDTOR
#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>

#ifndef SVTOOLS_FSTATHELPER_HXX
#include <svtools/fstathelper.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_HELPOPT_HXX
#include <svtools/helpopt.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_UNICODETYPE_HDL_
#include <com/sun/star/i18n/UnicodeType.hdl>
#endif
#ifndef _UNOTOOLS_COLLATORWRAPPER_HXX
#include <unotools/collatorwrapper.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_COLLATOROPTIONS_HPP_
#include <com/sun/star/i18n/CollatorOptions.hpp>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <svxids.hrc>
#endif

#include "udlnitem.hxx"
#include "wghtitem.hxx"
#include "escpitem.hxx"
#include "svxacorr.hxx"
#include "unolingu.hxx"

#ifndef _SVX_HELPID_HRC
#include <helpid.hrc>
#endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_INPUTSOURCE_HPP_
#include <com/sun/star/xml/sax/InputSource.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#ifndef _SV_XMLAUTOCORRECTIMPORT_HXX
#include <SvXMLAutoCorrectImport.hxx>
#endif
#ifndef _SV_XMLAUTOCORRECTEXPORT_HXX
#include <SvXMLAutoCorrectExport.hxx>
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _COM_SUN_STAR_UCB_XCOMMANDENVIRONMENT_HPP_
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_TRANSFERINFO_HPP_
#include <com/sun/star/ucb/TransferInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_NAMECLASH_HPP_
#include <com/sun/star/ucb/NameClash.hpp>
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include <bf_xmloff/xmltoken.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;
using namespace ::rtl;
using namespace ::utl;

const int C_NONE                = 0x00;
const int C_FULL_STOP           = 0x01;
const int C_EXCLAMATION_MARK    = 0x02;
const int C_QUESTION_MARK       = 0x04;

static const sal_Char pImplWrdStt_ExcptLstStr[]    = "WordExceptList";
static const sal_Char pImplCplStt_ExcptLstStr[]    = "SentenceExceptList";
static const sal_Char pImplAutocorr_ListStr[]      = "DocumentList";
static const sal_Char pXMLImplWrdStt_ExcptLstStr[] = "WordExceptList.xml";
static const sal_Char pXMLImplCplStt_ExcptLstStr[] = "SentenceExceptList.xml";
static const sal_Char pXMLImplAutocorr_ListStr[]   = "DocumentList.xml";

static const sal_Char
    /* auch bei diesen Anfaengen - Klammern auf und alle Arten von Anf.Zei. */
    sImplSttSkipChars[] = "\"\'([{\x83\x84\x89\x91\x92\x93\x94",
    /* auch bei diesen Ende - Klammern auf und alle Arten von Anf.Zei. */
    sImplEndSkipChars[] = "\"\')]}\x83\x84\x89\x91\x92\x93\x94";

// diese Zeichen sind in Worten erlaubt: (fuer FnCptlSttSntnc)
static const sal_Char sImplWordChars[] = "-'";

void EncryptBlockName_Imp( String& rName );
void DecryptBlockName_Imp( String& rName );


// FileVersions Nummern fuer die Ersetzungs-/Ausnahmelisten getrennt
#define WORDLIST_VERSION_358    1
#define EXEPTLIST_VERSION_358   0


//STRIP001 _SV_IMPL_SORTAR_ALG( SvxAutocorrWordList, SvxAutocorrWordPtr )
//STRIP001 TYPEINIT0(SvxAutoCorrect)

/*N*/ typedef SvxAutoCorrectLanguageLists* SvxAutoCorrectLanguageListsPtr;
/*N*/ DECLARE_TABLE( SvxAutoCorrLanguageTable_Impl,  SvxAutoCorrectLanguageListsPtr)//STRIP008 ;

/*N*/ DECLARE_TABLE( SvxAutoCorrLastFileAskTable_Impl, long )//STRIP008 ;


//STRIP001 inline int IsWordDelim( const sal_Unicode c )
//STRIP001 {
//STRIP001  return ' ' == c || '\t' == c || 0x0a == c ||
//STRIP001             0xA0 == c || 0x2011 == c || 0x1 == c;
//STRIP001 }

//STRIP001 inline int IsLowerLetter( sal_Int32 nCharType )
//STRIP001 {
//STRIP001  return CharClass::isLetterType( nCharType ) &&
//STRIP001          0 == ( ::com::sun::star::i18n::KCharacterType::UPPER & nCharType);
//STRIP001 }
//STRIP001 inline int IsUpperLetter( sal_Int32 nCharType )
//STRIP001 {
//STRIP001  return CharClass::isLetterType( nCharType ) &&
//STRIP001          0 == ( ::com::sun::star::i18n::KCharacterType::LOWER & nCharType);
//STRIP001 }

//STRIP001 BOOL lcl_IsSymbolChar( CharClass& rCC, const String& rTxt,
//STRIP001                      xub_StrLen nStt, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  for( ; nStt < nEnd; ++nStt )
//STRIP001  {
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      sal_Int32 nCharType = rCC.getCharacterType( rTxt, nStt );
//STRIP001      sal_Int32 nChType = rCC.getType( rTxt, nStt );
//STRIP001 #endif
//STRIP001      if( ::com::sun::star::i18n::UnicodeType::PRIVATE_USE ==
//STRIP001              rCC.getType( rTxt, nStt ))
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 static BOOL lcl_IsInAsciiArr( const sal_Char* pArr, const sal_Unicode c )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  for( ; *pArr; ++pArr )
//STRIP001      if( *pArr == c )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 SvxAutoCorrDoc::~SvxAutoCorrDoc()
//STRIP001 {
//STRIP001 }


    // wird nach dem austauschen der Zeichen von den Funktionen
    //  - FnCptlSttWrd
    //  - FnCptlSttSntnc
    // gerufen. Dann koennen die Worte ggfs. in die Ausnahmelisten
    // aufgenommen werden.
//STRIP001 void SvxAutoCorrDoc::SaveCpltSttWord( ULONG, xub_StrLen, const String&,
//STRIP001                                      sal_Unicode )
//STRIP001 {
//STRIP001 }

//STRIP001 LanguageType SvxAutoCorrDoc::GetLanguage( xub_StrLen , BOOL ) const
//STRIP001 {
//STRIP001  return LANGUAGE_SYSTEM;
//STRIP001 }

//STRIP001 static ::com::sun::star::uno::Reference<
//STRIP001          ::com::sun::star::lang::XMultiServiceFactory >& GetProcessFact()
//STRIP001 {
//STRIP001  static ::com::sun::star::uno::Reference<
//STRIP001          ::com::sun::star::lang::XMultiServiceFactory > xMSF =
//STRIP001                                  ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001  return xMSF;
//STRIP001 }

/*N*/ static USHORT GetAppLang()
/*N*/ {
/*N*/   return Application::GetSettings().GetLanguage();
/*N*/ }
//STRIP001 static LocaleDataWrapper& GetLocaleDataWrapper( USHORT nLang )
//STRIP001 {
//STRIP001  static LocaleDataWrapper aLclDtWrp( GetProcessFact(),
//STRIP001                                      SvxCreateLocale( GetAppLang() ) );
//STRIP001  ::com::sun::star::lang::Locale aLcl( SvxCreateLocale( nLang ));
//STRIP001  const ::com::sun::star::lang::Locale& rLcl = aLclDtWrp.getLoadedLocale();
//STRIP001  if( aLcl.Language != rLcl.Language ||
//STRIP001      aLcl.Country != rLcl.Country ||
//STRIP001      aLcl.Variant != rLcl.Variant )
//STRIP001      aLclDtWrp.setLocale( aLcl );
//STRIP001  return aLclDtWrp;
//STRIP001 }
//STRIP001 static TransliterationWrapper& GetIgnoreTranslWrapper()
//STRIP001 {
//STRIP001  static int bIsInit = 0;
//STRIP001  static TransliterationWrapper aWrp( GetProcessFact(),
//STRIP001              ::com::sun::star::i18n::TransliterationModules_IGNORE_CASE |
//STRIP001              ::com::sun::star::i18n::TransliterationModules_IGNORE_KANA |
//STRIP001              ::com::sun::star::i18n::TransliterationModules_IGNORE_WIDTH );
//STRIP001  if( !bIsInit )
//STRIP001  {
//STRIP001      aWrp.loadModuleIfNeeded( GetAppLang() );
//STRIP001      bIsInit = 1;
//STRIP001  }
//STRIP001  return aWrp;
//STRIP001 }
//STRIP001 static CollatorWrapper& GetCollatorWrapper()
//STRIP001 {
//STRIP001  static int bIsInit = 0;
//STRIP001  static CollatorWrapper aCollWrp( GetProcessFact() );
//STRIP001  if( !bIsInit )
//STRIP001  {
//STRIP001      aCollWrp.loadDefaultCollator( SvxCreateLocale( GetAppLang() ), 0 );
//STRIP001      bIsInit = 1;
//STRIP001  }
//STRIP001  return aCollWrp;
//STRIP001 }


//STRIP001 void SvxAutocorrWordList::DeleteAndDestroy( USHORT nP, USHORT nL )
//STRIP001 {
//STRIP001  if( nL )
//STRIP001  {
//STRIP001      DBG_ASSERT( nP < nA && nP + nL <= nA, "ERR_VAR_DEL" );
//STRIP001      for( USHORT n=nP; n < nP + nL; n++ )
//STRIP001          delete *((SvxAutocorrWordPtr*)pData+n);
//STRIP001      SvPtrarr::Remove( nP, nL );
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL SvxAutocorrWordList::Seek_Entry( const SvxAutocorrWordPtr aE, USHORT* pP ) const
//STRIP001 {
//STRIP001  register USHORT nO  = SvxAutocorrWordList_SAR::Count(),
//STRIP001          nM,
//STRIP001          nU = 0;
//STRIP001  if( nO > 0 )
//STRIP001  {
//STRIP001      CollatorWrapper& rCmp = ::GetCollatorWrapper();
//STRIP001      nO--;
//STRIP001      while( nU <= nO )
//STRIP001      {
//STRIP001          nM = nU + ( nO - nU ) / 2;
//STRIP001          long nCmp = rCmp.compareString( aE->GetShort(),
//STRIP001                      (*((SvxAutocorrWordPtr*)pData + nM))->GetShort() );
//STRIP001          if( 0 == nCmp )
//STRIP001          {
//STRIP001              if( pP ) *pP = nM;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001          else if( 0 < nCmp )
//STRIP001              nU = nM + 1;
//STRIP001          else if( nM == 0 )
//STRIP001          {
//STRIP001              if( pP ) *pP = nU;
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001              nO = nM - 1;
//STRIP001      }
//STRIP001  }
//STRIP001  if( pP ) *pP = nU;
//STRIP001  return FALSE;
//STRIP001 }

/* -----------------18.11.98 15:28-------------------
 *
 * --------------------------------------------------*/
/*N*/ void lcl_ClearTable(SvxAutoCorrLanguageTable_Impl& rLangTable)
/*N*/ {
/*N*/   SvxAutoCorrectLanguageListsPtr pLists = rLangTable.Last();
/*N*/   while(pLists)
/*N*/   {
/*?*/       delete pLists;
/*?*/       pLists = rLangTable.Prev();
/*N*/   }
/*N*/   rLangTable.Clear();
/*N*/ }

/* -----------------19.11.98 10:15-------------------
 *
 * --------------------------------------------------*/
/*N*/ long SvxAutoCorrect::GetDefaultFlags()
/*N*/ {
/*N*/   long nRet = Autocorrect
/*N*/                   | CptlSttSntnc
/*N*/                   | CptlSttWrd
/*N*/                   | ChgFractionSymbol
/*N*/                   | ChgOrdinalNumber
/*N*/                   | ChgToEnEmDash
/*N*/                   | ChgWeightUnderl
/*N*/                   | SetINetAttr
/*N*/                   | ChgQuotes
/*N*/                   | SaveWordCplSttLst
/*N*/                   | SaveWordWrdSttLst;
/*N*/   LanguageType eLang = GetAppLang();
/*N*/   switch( eLang )
/*N*/   {
/*N*/   case LANGUAGE_ENGLISH:
/*N*/   case LANGUAGE_ENGLISH_US:
/*N*/   case LANGUAGE_ENGLISH_UK:
/*N*/   case LANGUAGE_ENGLISH_AUS:
/*N*/   case LANGUAGE_ENGLISH_CAN:
/*N*/   case LANGUAGE_ENGLISH_NZ:
/*N*/   case LANGUAGE_ENGLISH_EIRE:
/*N*/   case LANGUAGE_ENGLISH_SAFRICA:
/*N*/   case LANGUAGE_ENGLISH_JAMAICA:
/*N*/   case LANGUAGE_ENGLISH_CARRIBEAN:
/*N*/       nRet &= ~(ChgQuotes|ChgSglQuotes);
/*N*/       break;
/*N*/   }
/*N*/   return nRet;
/*N*/ }


/*N*/ SvxAutoCorrect::SvxAutoCorrect( const String& rShareAutocorrFile,
/*N*/                               const String& rUserAutocorrFile )
/*N*/   : sShareAutoCorrFile( rShareAutocorrFile ),
/*N*/   sUserAutoCorrFile( rUserAutocorrFile ),
/*N*/   cStartSQuote( 0 ), cEndSQuote( 0 ), cStartDQuote( 0 ), cEndDQuote( 0 ),
/*N*/   pLangTable( new SvxAutoCorrLanguageTable_Impl ),
/*N*/   pLastFileTable( new SvxAutoCorrLastFileAskTable_Impl ),
/*N*/   pCharClass( 0 )
/*N*/ {
/*N*/   nFlags = SvxAutoCorrect::GetDefaultFlags();
/*N*/
/*N*/   c1Div2 = ByteString::ConvertToUnicode( '\xBD', RTL_TEXTENCODING_MS_1252 );
/*N*/   c1Div4 = ByteString::ConvertToUnicode( '\xBC', RTL_TEXTENCODING_MS_1252 );
/*N*/   c3Div4 = ByteString::ConvertToUnicode( '\xBE', RTL_TEXTENCODING_MS_1252 );
/*N*/   cEmDash = ByteString::ConvertToUnicode( '\x97', RTL_TEXTENCODING_MS_1252 );
/*N*/   cEnDash = ByteString::ConvertToUnicode( '\x96', RTL_TEXTENCODING_MS_1252 );
/*N*/ }

/*N*/ SvxAutoCorrect::SvxAutoCorrect( const SvxAutoCorrect& rCpy )
/*N*/   : nFlags( rCpy.nFlags & ~(ChgWordLstLoad|CplSttLstLoad|WrdSttLstLoad)),
/*N*/   aSwFlags( rCpy.aSwFlags ),
/* Die Sprachentabelle wird neu aufgebaut, da sie im Dtor von rCpy abgeraeumt wird!
 */
/*N*/   sShareAutoCorrFile( rCpy.sShareAutoCorrFile ),
/*N*/   sUserAutoCorrFile( rCpy.sUserAutoCorrFile ),
/*N*/   cStartSQuote( rCpy.cStartSQuote ), cEndSQuote( rCpy.cEndSQuote ),
/*N*/   cStartDQuote( rCpy.cStartDQuote ), cEndDQuote( rCpy.cEndDQuote ),
/*N*/   c1Div2( rCpy.c1Div2 ), c1Div4( rCpy.c1Div4 ), c3Div4( rCpy.c3Div4 ),
/*N*/   cEmDash( rCpy.cEmDash ), cEnDash( rCpy.cEnDash ),
/*N*/   pLangTable( new SvxAutoCorrLanguageTable_Impl ),
/*N*/   pLastFileTable( new SvxAutoCorrLastFileAskTable_Impl ),
/*N*/   pCharClass( 0 )
/*N*/ {
/*N*/ }


/*N*/ SvxAutoCorrect::~SvxAutoCorrect()
/*N*/ {
/*N*/   lcl_ClearTable(*pLangTable);
/*N*/   delete pLangTable;
/*N*/   delete pLastFileTable;
/*N*/   delete pCharClass;
/*N*/ }

//STRIP001 void SvxAutoCorrect::_GetCharClass( LanguageType eLang )
//STRIP001 {
//STRIP001  delete pCharClass;
//STRIP001  pCharClass = new CharClass( SvxCreateLocale( eLang ));
//STRIP001  eCharClassLang = eLang;
//STRIP001 }

/*N*/ void SvxAutoCorrect::SetAutoCorrFlag( long nFlag, BOOL bOn )
/*N*/ {
/*N*/   long nOld = nFlags;
/*N*/   nFlags = bOn ? nFlags | nFlag
/*N*/                : nFlags & ~nFlag;
/*N*/
/*N*/   if( !bOn )
/*N*/   {
/*N*/       if( (nOld & CptlSttSntnc) != (nFlags & CptlSttSntnc) )
/*?*/           nFlags &= ~CplSttLstLoad;
/*N*/       if( (nOld & CptlSttWrd) != (nFlags & CptlSttWrd) )
/*?*/           nFlags &= ~WrdSttLstLoad;
/*N*/       if( (nOld & Autocorrect) != (nFlags & Autocorrect) )
/*?*/           nFlags &= ~ChgWordLstLoad;
/*N*/   }
/*N*/ }


    // Zwei Grossbuchstaben am Wort-Anfang ??
//STRIP001 BOOL SvxAutoCorrect::FnCptlSttWrd( SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                                  xub_StrLen nSttPos, xub_StrLen nEndPos,
//STRIP001                                  LanguageType eLang )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  CharClass& rCC = GetCharClass( eLang );
//STRIP001
//STRIP001  // loesche alle nicht alpanum. Zeichen am Wortanfang/-ende und
//STRIP001  // teste dann ( erkennt: "(min.", "/min.", usw.)
//STRIP001  for( ; nSttPos < nEndPos; ++nSttPos )
//STRIP001      if( rCC.isLetterNumeric( rTxt, nSttPos ))
//STRIP001          break;
//STRIP001  for( ; nSttPos < nEndPos; --nEndPos )
//STRIP001      if( rCC.isLetterNumeric( rTxt, nEndPos - 1 ))
//STRIP001          break;
//STRIP001
//STRIP001  // Zwei Grossbuchstaben am Wort-Anfang ??
//STRIP001  if( nSttPos+2 < nEndPos &&
//STRIP001      IsUpperLetter( rCC.getCharacterType( rTxt, nSttPos )) &&
//STRIP001      IsUpperLetter( rCC.getCharacterType( rTxt, ++nSttPos )) &&
//STRIP001      // ist das 3. Zeichen ein klein geschiebenes Alpha-Zeichen
//STRIP001      IsLowerLetter( rCC.getCharacterType( rTxt, nSttPos +1 )) &&
//STRIP001      // keine Sonder-Attribute ersetzen
//STRIP001      0x1 != rTxt.GetChar( nSttPos ) && 0x2 != rTxt.GetChar( nSttPos ))
//STRIP001  {
//STRIP001      // teste ob das Wort in einer Ausnahmeliste steht
//STRIP001      String sWord( rTxt.Copy( nSttPos - 1, nEndPos - nSttPos + 1 ));
//STRIP001      if( !FindInWrdSttExceptList(eLang, sWord) )
//STRIP001      {
//STRIP001          sal_Unicode cSave = rTxt.GetChar( nSttPos );
//STRIP001          String sChar( cSave );
//STRIP001          rCC.toLower( sChar );
//STRIP001          if( sChar.GetChar(0) != cSave && rDoc.Replace( nSttPos, sChar ))
//STRIP001          {
//STRIP001              if( SaveWordWrdSttLst & nFlags )
//STRIP001                  rDoc.SaveCpltSttWord( CptlSttWrd, nSttPos, sWord, cSave );
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::FnChgFractionSymbol(
//STRIP001                              SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                              xub_StrLen nSttPos, xub_StrLen nEndPos )
//STRIP001 {
//STRIP001  sal_Unicode cChar = 0;
//STRIP001
//STRIP001  for( ; nSttPos < nEndPos; ++nSttPos )
//STRIP001      if( !lcl_IsInAsciiArr( sImplSttSkipChars, rTxt.GetChar( nSttPos ) ))
//STRIP001          break;
//STRIP001  for( ; nSttPos < nEndPos; --nEndPos )
//STRIP001      if( !lcl_IsInAsciiArr( sImplEndSkipChars, rTxt.GetChar( nEndPos - 1 ) ))
//STRIP001          break;
//STRIP001
//STRIP001  // 1/2, 1/4, ... ersetzen durch das entsprechende Zeichen vom Font
//STRIP001  if( 3 == nEndPos - nSttPos && '/' == rTxt.GetChar( nSttPos+1 ))
//STRIP001  {
//STRIP001      switch( ( rTxt.GetChar( nSttPos )) * 256 + rTxt.GetChar( nEndPos-1 ))
//STRIP001      {
//STRIP001      case '1' * 256 + '2':       cChar = c1Div2;     break;
//STRIP001      case '1' * 256 + '4':       cChar = c1Div4;     break;
//STRIP001      case '3' * 256 + '4':       cChar = c3Div4;     break;
//STRIP001      }
//STRIP001
//STRIP001      if( cChar )
//STRIP001      {
//STRIP001          // also austauschen:
//STRIP001          rDoc.Delete( nSttPos+1, nEndPos );
//STRIP001          rDoc.Replace( nSttPos, cChar );
//STRIP001      }
//STRIP001  }
//STRIP001  return 0 != cChar;
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::FnChgOrdinalNumber(
//STRIP001                              SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                              xub_StrLen nSttPos, xub_StrLen nEndPos,
//STRIP001                              LanguageType eLang )
//STRIP001 {
//STRIP001 // 1st, 2nd, 3rd, 4 - 0th
//STRIP001 // 201th oder 201st
//STRIP001 // 12th oder 12nd
//STRIP001  CharClass& rCC = GetCharClass( eLang );
//STRIP001  BOOL bChg = FALSE;
//STRIP001
//STRIP001  for( ; nSttPos < nEndPos; ++nSttPos )
//STRIP001      if( !lcl_IsInAsciiArr( sImplSttSkipChars, rTxt.GetChar( nSttPos ) ))
//STRIP001          break;
//STRIP001  for( ; nSttPos < nEndPos; --nEndPos )
//STRIP001      if( !lcl_IsInAsciiArr( sImplEndSkipChars, rTxt.GetChar( nEndPos - 1 ) ))
//STRIP001          break;
//STRIP001
//STRIP001  if( 2 < nEndPos - nSttPos &&
//STRIP001      rCC.isDigit( rTxt, nEndPos - 3 ) )
//STRIP001  {
//STRIP001      static sal_Char __READONLY_DATA
//STRIP001          sAll[]      = "th",         /* rest */
//STRIP001          sFirst[]    = "st",         /* 1 */
//STRIP001          sSecond[]   = "nd",         /* 2 */
//STRIP001          sThird[]    = "rd";         /* 3 */
//STRIP001      static const sal_Char* __READONLY_DATA aNumberTab[ 4 ] =
//STRIP001      {
//STRIP001          sAll, sFirst, sSecond, sThird
//STRIP001      };
//STRIP001
//STRIP001      sal_Unicode c = rTxt.GetChar( nEndPos - 3 );
//STRIP001      if( ( c -= '0' ) > 3 )
//STRIP001          c = 0;
//STRIP001
//STRIP001      bChg = ( ((sal_Unicode)*((aNumberTab[ c ])+0)) ==
//STRIP001                                      rTxt.GetChar( nEndPos - 2 ) &&
//STRIP001               ((sal_Unicode)*((aNumberTab[ c ])+1)) ==
//STRIP001                                      rTxt.GetChar( nEndPos - 1 )) ||
//STRIP001             ( 3 < nEndPos - nSttPos &&
//STRIP001              ( ((sal_Unicode)*(sAll+0)) == rTxt.GetChar( nEndPos - 2 ) &&
//STRIP001                ((sal_Unicode)*(sAll+1)) == rTxt.GetChar( nEndPos - 1 )));
//STRIP001
//STRIP001      if( bChg )
//STRIP001      {
//STRIP001          // dann pruefe mal, ob alle bis zum Start alle Zahlen sind
//STRIP001          for( xub_StrLen n = nEndPos - 3; nSttPos < n; )
//STRIP001              if( !rCC.isDigit( rTxt, --n ) )
//STRIP001              {
//STRIP001                  bChg = !rCC.isLetter( rTxt, n );
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001          if( bChg )      // dann setze mal das Escapement Attribut
//STRIP001          {
//STRIP001              SvxEscapementItem aSvxEscapementItem( DFLT_ESC_AUTO_SUPER,
//STRIP001                                                  DFLT_ESC_PROP );
//STRIP001              rDoc.SetAttr( nEndPos - 2, nEndPos,
//STRIP001                              SID_ATTR_CHAR_ESCAPEMENT,
//STRIP001                              aSvxEscapementItem);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001  return bChg;
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::FnChgToEnEmDash(
//STRIP001                              SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                              xub_StrLen nSttPos, xub_StrLen nEndPos,
//STRIP001                              LanguageType eLang )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  CharClass& rCC = GetCharClass( eLang );
//STRIP001
//STRIP001  // ersetze " - " oder " --" durch "enDash"
//STRIP001  if( cEnDash && 1 < nSttPos && 1 <= nEndPos - nSttPos )
//STRIP001  {
//STRIP001      sal_Unicode cCh = rTxt.GetChar( nSttPos );
//STRIP001      if( '-' == cCh )
//STRIP001      {
//STRIP001          if( ' ' == rTxt.GetChar( nSttPos-1 ) &&
//STRIP001              '-' == rTxt.GetChar( nSttPos+1 ))
//STRIP001          {
//STRIP001              xub_StrLen n;
//STRIP001              for( n = nSttPos+2; n < nEndPos && lcl_IsInAsciiArr(
//STRIP001                          sImplSttSkipChars,(cCh = rTxt.GetChar( n )));
//STRIP001                      ++n )
//STRIP001                  ;
//STRIP001
//STRIP001              // found: " --[<AnySttChars>][A-z0-9]
//STRIP001              if( rCC.isLetterNumeric( cCh ) )
//STRIP001              {
//STRIP001                  for( n = nSttPos-1; n && lcl_IsInAsciiArr(
//STRIP001                          sImplEndSkipChars,(cCh = rTxt.GetChar( --n ))); )
//STRIP001                      ;
//STRIP001
//STRIP001                  // found: "[A-z0-9][<AnyEndChars>] --[<AnySttChars>][A-z0-9]
//STRIP001                  if( rCC.isLetterNumeric( cCh ))
//STRIP001                  {
//STRIP001                      rDoc.Delete( nSttPos, nSttPos + 2 );
//STRIP001                      rDoc.Insert( nSttPos, cEnDash );
//STRIP001                      bRet = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if( 3 < nSttPos &&
//STRIP001               ' ' == rTxt.GetChar( nSttPos-1 ) &&
//STRIP001               '-' == rTxt.GetChar( nSttPos-2 ))
//STRIP001      {
//STRIP001          xub_StrLen n, nLen = 1, nTmpPos = nSttPos - 2;
//STRIP001          if( '-' == ( cCh = rTxt.GetChar( nTmpPos-1 )) )
//STRIP001          {
//STRIP001              --nTmpPos;
//STRIP001              ++nLen;
//STRIP001              cCh = rTxt.GetChar( nTmpPos-1 );
//STRIP001          }
//STRIP001          if( ' ' == cCh )
//STRIP001          {
//STRIP001              for( n = nSttPos; n < nEndPos && lcl_IsInAsciiArr(
//STRIP001                          sImplSttSkipChars,(cCh = rTxt.GetChar( n )));
//STRIP001                      ++n )
//STRIP001                  ;
//STRIP001
//STRIP001              // found: " - [<AnySttChars>][A-z0-9]
//STRIP001              if( rCC.isLetterNumeric( cCh ) )
//STRIP001              {
//STRIP001                  cCh = ' ';
//STRIP001                  for( n = nTmpPos-1; n && lcl_IsInAsciiArr(
//STRIP001                          sImplEndSkipChars,(cCh = rTxt.GetChar( --n ))); )
//STRIP001                          ;
//STRIP001                  // found: "[A-z0-9][<AnyEndChars>] - [<AnySttChars>][A-z0-9]
//STRIP001                  if( rCC.isLetterNumeric( cCh ))
//STRIP001                  {
//STRIP001                      rDoc.Delete( nTmpPos, nTmpPos + nLen );
//STRIP001                      rDoc.Insert( nTmpPos, cEnDash );
//STRIP001                      bRet = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // ersetze [A-z0-9]--[A-z0-9] durch "emDash"
//STRIP001  if( cEmDash && 4 <= nEndPos - nSttPos )
//STRIP001  {
//STRIP001      String sTmp( rTxt.Copy( nSttPos, nEndPos - nSttPos ) );
//STRIP001      xub_StrLen nFndPos = sTmp.SearchAscii( "--" );
//STRIP001      if( STRING_NOTFOUND != nFndPos && nFndPos &&
//STRIP001          nFndPos + 2 < sTmp.Len() &&
//STRIP001          ( rCC.isLetterNumeric( sTmp, nFndPos - 1 ) ||
//STRIP001            lcl_IsInAsciiArr( sImplEndSkipChars, rTxt.GetChar( nFndPos - 1 ) )) &&
//STRIP001          ( rCC.isLetterNumeric( sTmp, nFndPos + 2 ) ||
//STRIP001          lcl_IsInAsciiArr( sImplSttSkipChars, rTxt.GetChar( nFndPos + 2 ) )))
//STRIP001      {
//STRIP001          nSttPos += nFndPos;
//STRIP001          rDoc.Delete( nSttPos, nSttPos + 2 );
//STRIP001          rDoc.Insert( nSttPos, cEmDash );
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::FnSetINetAttr( SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                                  xub_StrLen nSttPos, xub_StrLen nEndPos,
//STRIP001                                  LanguageType eLang )
//STRIP001 {
//STRIP001  String sURL( URIHelper::FindFirstURLInText( rTxt, nSttPos, nEndPos,
//STRIP001                                              GetCharClass( eLang ) ));
//STRIP001  BOOL bRet = 0 != sURL.Len();
//STRIP001  if( bRet )          // also Attribut setzen:
//STRIP001      rDoc.SetINetAttr( nSttPos, nEndPos, sURL );
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::FnChgWeightUnderl( SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                                      xub_StrLen nSttPos, xub_StrLen nEndPos,
//STRIP001                                      LanguageType eLang )
//STRIP001 {
//STRIP001  // Bedingung:
//STRIP001  //  Am Anfang:  _ oder * hinter Space mit nachfolgenden !Space
//STRIP001  //  Am Ende:    _ oder * vor Space (Worttrenner?)
//STRIP001
//STRIP001  sal_Unicode c, cInsChar = rTxt.GetChar( nEndPos );  // unterstreichen oder fett
//STRIP001  if( ++nEndPos != rTxt.Len() &&
//STRIP001      !IsWordDelim( rTxt.GetChar( nEndPos ) ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  --nEndPos;
//STRIP001
//STRIP001  BOOL bAlphaNum = FALSE;
//STRIP001  xub_StrLen nPos = nEndPos, nFndPos = STRING_NOTFOUND;
//STRIP001  CharClass& rCC = GetCharClass( eLang );
//STRIP001
//STRIP001  while( nPos )
//STRIP001  {
//STRIP001      switch( c = rTxt.GetChar( --nPos ) )
//STRIP001      {
//STRIP001      case '_':
//STRIP001      case '*':
//STRIP001          if( c == cInsChar )
//STRIP001          {
//STRIP001              if( bAlphaNum && nPos+1 < nEndPos && ( !nPos ||
//STRIP001                  IsWordDelim( rTxt.GetChar( nPos-1 ))) &&
//STRIP001                  !IsWordDelim( rTxt.GetChar( nPos+1 )))
//STRIP001                      nFndPos = nPos;
//STRIP001              else
//STRIP001                  // Bedingung ist nicht erfuellt, also abbrechen
//STRIP001                  nFndPos = STRING_NOTFOUND;
//STRIP001              nPos = 0;
//STRIP001          }
//STRIP001          break;
//STRIP001      default:
//STRIP001          if( !bAlphaNum )
//STRIP001              bAlphaNum = rCC.isLetterNumeric( rTxt, nPos );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( STRING_NOTFOUND != nFndPos )
//STRIP001  {
//STRIP001      // ueber den gefundenen Bereich das Attribut aufspannen und
//STRIP001      // das gefunde und am Ende stehende Zeichen loeschen
//STRIP001      if( '*' == cInsChar )           // Fett
//STRIP001      {
//STRIP001          SvxWeightItem aSvxWeightItem( WEIGHT_BOLD );
//STRIP001          rDoc.SetAttr( nFndPos + 1, nEndPos,
//STRIP001                          SID_ATTR_CHAR_WEIGHT,
//STRIP001                          aSvxWeightItem);
//STRIP001      }
//STRIP001      else                            // unterstrichen
//STRIP001      {
//STRIP001          SvxUnderlineItem aSvxUnderlineItem( UNDERLINE_SINGLE );
//STRIP001          rDoc.SetAttr( nFndPos + 1, nEndPos,
//STRIP001                          SID_ATTR_CHAR_UNDERLINE,
//STRIP001                          aSvxUnderlineItem);
//STRIP001      }
//STRIP001      rDoc.Delete( nEndPos, nEndPos + 1 );
//STRIP001      rDoc.Delete( nFndPos, nFndPos + 1 );
//STRIP001  }
//STRIP001
//STRIP001  return STRING_NOTFOUND != nFndPos;
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::FnCptlSttSntnc( SvxAutoCorrDoc& rDoc,
//STRIP001                                  const String& rTxt, BOOL bNormalPos,
//STRIP001                                  xub_StrLen nSttPos, xub_StrLen nEndPos,
//STRIP001                                  LanguageType eLang )
//STRIP001 {
//STRIP001  // Grossbuchstabe am Satz-Anfang ??
//STRIP001  if( !rTxt.Len() || nEndPos <= nSttPos )
//STRIP001      return FALSE;
//STRIP001
//STRIP001      CharClass& rCC = GetCharClass( eLang );
//STRIP001  String aText( rTxt );
//STRIP001  const sal_Unicode *pStart = aText.GetBuffer(),
//STRIP001                    *pStr = pStart + nEndPos,
//STRIP001                    *pWordStt = 0,
//STRIP001                    *pDelim;
//STRIP001
//STRIP001  BOOL bAtStart = FALSE, bPrevPara = FALSE;
//STRIP001  do {
//STRIP001      --pStr;
//STRIP001      if( rCC.isLetter( aText, pStr - pStart ) )
//STRIP001      {
//STRIP001          if( !pWordStt )
//STRIP001              pDelim = pStr+1;
//STRIP001          pWordStt = pStr;
//STRIP001      }
//STRIP001      else if( pWordStt && !rCC.isDigit( aText, pStr - pStart ))
//STRIP001      {
//STRIP001          if( lcl_IsInAsciiArr( sImplWordChars, *pStr ) &&
//STRIP001              pWordStt - 1 == pStr &&
//STRIP001              (long)(pStart + 1) < (long)pStr &&
//STRIP001              rCC.isLetter( aText, pStr-1 - pStart ) )
//STRIP001              pWordStt = --pStr;
//STRIP001          else
//STRIP001              break;
//STRIP001      }
//STRIP001  } while( 0 == ( bAtStart = (pStart == pStr)) );
//STRIP001
//STRIP001
//STRIP001  if( !pWordStt ||
//STRIP001      rCC.isDigit( aText, pStr - pStart ) ||
//STRIP001      IsUpperLetter( rCC.getCharacterType( aText, pWordStt - pStart )) ||
//STRIP001      0x1 == *pWordStt || 0x2 == *pWordStt )
//STRIP001      return FALSE;       // kein zu ersetzendes Zeichen, oder schon ok
//STRIP001
//STRIP001  // JP 27.10.97: wenn das Wort weniger als 3 Zeichen hat und der Trenner
//STRIP001  //              ein "Num"-Trenner ist, dann nicht ersetzen!
//STRIP001  //              Damit wird ein "a.",  "a)", "a-a" nicht ersetzt!
//STRIP001  if( *pDelim && 2 >= pDelim - pWordStt &&
//STRIP001      lcl_IsInAsciiArr( ".-)>", *pDelim ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( !bAtStart ) // noch kein Absatz Anfang ?
//STRIP001  {
//STRIP001         if ( IsWordDelim( *pStr ) )
//STRIP001         {
//STRIP001             while( 0 == ( bAtStart = (pStart == pStr--) ) && IsWordDelim( *pStr ))
//STRIP001                 ;
//STRIP001         }
//STRIP001         // Asian full stop, full width full stop, full width exclamation mark
//STRIP001         // and full width question marks are treated as word delimiters
//STRIP001         else if ( 0x3002 != *pStr && 0xFF0E != *pStr && 0xFF01 != *pStr &&
//STRIP001                   0xFF1F != *pStr )
//STRIP001             return FALSE; // kein gueltiger Trenner -> keine Ersetzung
//STRIP001     }
//STRIP001
//STRIP001  if( bAtStart )  // am Absatz Anfang ?
//STRIP001  {
//STRIP001      // Ueberpruefe den vorherigen Absatz, wenn es diesen gibt.
//STRIP001      // Wenn ja, dann pruefe auf SatzTrenner am Ende.
//STRIP001      const String* pPrevPara = rDoc.GetPrevPara( bNormalPos );
//STRIP001      if( !pPrevPara )
//STRIP001      {
//STRIP001          // gueltiger Trenner -> Ersetze
//STRIP001          String sChar( *pWordStt );
//STRIP001          rCC.toUpper( sChar );
//STRIP001          return  sChar != *pWordStt &&
//STRIP001                  rDoc.Replace( xub_StrLen( pWordStt - pStart ), sChar );
//STRIP001      }
//STRIP001
//STRIP001      aText = *pPrevPara;
//STRIP001      bPrevPara = TRUE;
//STRIP001      bAtStart = FALSE;
//STRIP001      pStart = aText.GetBuffer();
//STRIP001      pStr = pStart + aText.Len();
//STRIP001
//STRIP001      do {            // alle Blanks ueberlesen
//STRIP001          --pStr;
//STRIP001          if( !IsWordDelim( *pStr ))
//STRIP001              break;
//STRIP001      } while( 0 == ( bAtStart = (pStart == pStr)) );
//STRIP001
//STRIP001      if( bAtStart )
//STRIP001          return FALSE;       // kein gueltiger Trenner -> keine Ersetzung
//STRIP001  }
//STRIP001
//STRIP001  // bis hierhier wurde [ \t]+[A-Z0-9]+ gefunden. Test jetzt auf den
//STRIP001  // Satztrenner. Es koennen alle 3 vorkommen, aber nicht mehrfach !!
//STRIP001  const sal_Unicode* pExceptStt = 0;
//STRIP001  if( !bAtStart )
//STRIP001  {
//STRIP001      BOOL bWeiter = TRUE;
//STRIP001      int nFlag = C_NONE;
//STRIP001      do {
//STRIP001          switch( *pStr )
//STRIP001          {
//STRIP001             // Western and Asian full stop
//STRIP001          case '.':
//STRIP001             case 0x3002 :
//STRIP001             case 0xFF0E :
//STRIP001              {
//STRIP001                  if( nFlag & C_FULL_STOP )
//STRIP001                      return FALSE;       // kein gueltiger Trenner -> keine Ersetzung
//STRIP001                  nFlag |= C_FULL_STOP;
//STRIP001                  pExceptStt = pStr;
//STRIP001              }
//STRIP001              break;
//STRIP001          case '!':
//STRIP001             case 0xFF01 :
//STRIP001              {
//STRIP001                  if( nFlag & C_EXCLAMATION_MARK )
//STRIP001                      return FALSE;   // kein gueltiger Trenner -> keine Ersetzung
//STRIP001                  nFlag |= C_EXCLAMATION_MARK;
//STRIP001              }
//STRIP001              break;
//STRIP001          case '?':
//STRIP001             case 0xFF1F :
//STRIP001              {
//STRIP001                  if( nFlag & C_QUESTION_MARK)
//STRIP001                      return FALSE;       // kein gueltiger Trenner -> keine Ersetzung
//STRIP001                  nFlag |= C_QUESTION_MARK;
//STRIP001              }
//STRIP001              break;
//STRIP001          default:
//STRIP001              if( !nFlag )
//STRIP001                  return FALSE;       // kein gueltiger Trenner -> keine Ersetzung
//STRIP001              else
//STRIP001                  bWeiter = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if( bWeiter && pStr-- == pStart )
//STRIP001          {
//STRIP001 // !!! wenn am Anfang, dann nie ersetzen.
//STRIP001 //               if( !nFlag )
//STRIP001                  return FALSE;       // kein gueltiger Trenner -> keine Ersetzung
//STRIP001 //               ++pStr;
//STRIP001 //               break;      // Schleife beenden
//STRIP001          }
//STRIP001      } while( bWeiter );
//STRIP001      if( C_FULL_STOP != nFlag )
//STRIP001          pExceptStt = 0;
//STRIP001  }
//STRIP001
//STRIP001  if( 2 > ( pStr - pStart ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( !rCC.isLetterNumeric( aText, pStr-- - pStart ) )
//STRIP001  {
//STRIP001      BOOL bValid = FALSE, bAlphaFnd = FALSE;
//STRIP001      const sal_Unicode* pTmpStr = pStr;
//STRIP001      while( !bValid )
//STRIP001      {
//STRIP001          if( rCC.isDigit( aText, pTmpStr - pStart ) )
//STRIP001          {
//STRIP001              bValid = TRUE;
//STRIP001              pStr = pTmpStr - 1;
//STRIP001          }
//STRIP001          else if( rCC.isLetter( aText, pTmpStr - pStart ) )
//STRIP001          {
//STRIP001              if( bAlphaFnd )
//STRIP001              {
//STRIP001                  bValid = TRUE;
//STRIP001                  pStr = pTmpStr;
//STRIP001              }
//STRIP001              else
//STRIP001                  bAlphaFnd = TRUE;
//STRIP001          }
//STRIP001          else if( bAlphaFnd || IsWordDelim( *pTmpStr ) )
//STRIP001              break;
//STRIP001
//STRIP001          if( pTmpStr == pStart )
//STRIP001              break;
//STRIP001
//STRIP001          --pTmpStr;
//STRIP001      }
//STRIP001
//STRIP001      if( !bValid )
//STRIP001          return FALSE;       // kein gueltiger Trenner -> keine Ersetzung
//STRIP001  }
//STRIP001
//STRIP001  BOOL bNumericOnly = '0' <= *(pStr+1) && *(pStr+1) <= '9';
//STRIP001
//STRIP001  // suche den Anfang vom Wort
//STRIP001  while( !IsWordDelim( *pStr ))
//STRIP001  {
//STRIP001      if( bNumericOnly && rCC.isLetter( aText, pStr - pStart ))
//STRIP001          bNumericOnly = FALSE;
//STRIP001
//STRIP001      if( pStart == pStr )
//STRIP001          break;
//STRIP001
//STRIP001      --pStr;
//STRIP001  }
//STRIP001
//STRIP001  if( bNumericOnly )      // besteht nur aus Zahlen, dann nicht
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( IsWordDelim( *pStr ))
//STRIP001      ++pStr;
//STRIP001
//STRIP001  String sWord;
//STRIP001
//STRIP001  // ueberpruefe anhand der Exceptionliste
//STRIP001  if( pExceptStt )
//STRIP001  {
//STRIP001      sWord = String( pStr, pExceptStt - pStr + 1 );
//STRIP001      if( FindInCplSttExceptList(eLang, sWord) )
//STRIP001          return FALSE;
//STRIP001
//STRIP001      // loesche alle nicht alpanum. Zeichen am Wortanfang/-ende und
//STRIP001      // teste dann noch mal ( erkennt: "(min.", "/min.", usw.)
//STRIP001      String sTmp( sWord );
//STRIP001      while( sTmp.Len() &&
//STRIP001              !rCC.isLetterNumeric( sTmp, 0 ) )
//STRIP001          sTmp.Erase( 0, 1 );
//STRIP001
//STRIP001      // alle hinteren nicht alphanumerische Zeichen bis auf das
//STRIP001      // Letzte entfernen
//STRIP001      xub_StrLen nLen = sTmp.Len();
//STRIP001      while( nLen && !rCC.isLetterNumeric( sTmp, nLen-1 ) )
//STRIP001          --nLen;
//STRIP001      if( nLen + 1 < sTmp.Len() )
//STRIP001          sTmp.Erase( nLen + 1 );
//STRIP001
//STRIP001      if( sTmp.Len() && sTmp.Len() != sWord.Len() &&
//STRIP001          FindInCplSttExceptList(eLang, sTmp))
//STRIP001          return FALSE;
//STRIP001
//STRIP001      if(FindInCplSttExceptList(eLang, sWord, TRUE))
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  // Ok, dann ersetze mal
//STRIP001  sal_Unicode cSave = *pWordStt;
//STRIP001  nSttPos = pWordStt - rTxt.GetBuffer();
//STRIP001  String sChar( cSave );
//STRIP001  rCC.toUpper( sChar );
//STRIP001  BOOL bRet = sChar.GetChar(0) != cSave && rDoc.Replace( nSttPos, sChar );
//STRIP001
//STRIP001  // das Wort will vielleicht jemand haben
//STRIP001  if( bRet && SaveWordCplSttLst & nFlags )
//STRIP001      rDoc.SaveCpltSttWord( CptlSttSntnc, nSttPos, sWord, cSave );
//STRIP001
//STRIP001  return bRet;
//STRIP001 }
//The method below is renamed from _GetQuote to GetQuote by BerryJia for Bug95846 Time:2002-8-13 15:50
//STRIP001 sal_Unicode SvxAutoCorrect::GetQuote( sal_Unicode cInsChar, BOOL bSttQuote,
//STRIP001                                      LanguageType eLang ) const
//STRIP001 {
//STRIP001  sal_Unicode cRet = bSttQuote ? ( '\"' == cInsChar
//STRIP001                                  ? GetStartDoubleQuote()
//STRIP001                                  : GetStartSingleQuote() )
//STRIP001                               : ( '\"' == cInsChar
//STRIP001                                  ? GetEndDoubleQuote()
//STRIP001                                  : GetEndSingleQuote() );
//STRIP001  if( !cRet )
//STRIP001  {
//STRIP001      // dann ueber die Language das richtige Zeichen heraussuchen
//STRIP001      if( LANGUAGE_NONE == eLang )
//STRIP001          cRet = cInsChar;
//STRIP001      else
//STRIP001      {
//STRIP001          LocaleDataWrapper& rLcl = GetLocaleDataWrapper( eLang );
//STRIP001          String sRet( bSttQuote
//STRIP001                          ? ( '\"' == cInsChar
//STRIP001                              ? rLcl.getDoubleQuotationMarkStart()
//STRIP001                              : rLcl.getQuotationMarkStart() )
//STRIP001                          : ( '\"' == cInsChar
//STRIP001                              ? rLcl.getDoubleQuotationMarkEnd()
//STRIP001                              : rLcl.getQuotationMarkEnd() ));
//STRIP001          cRet = sRet.Len() ? sRet.GetChar( 0 ) : cInsChar;
//STRIP001      }
//STRIP001  }
//STRIP001  return cRet;
//STRIP001 }

//STRIP001 void SvxAutoCorrect::InsertQuote( SvxAutoCorrDoc& rDoc, xub_StrLen nInsPos,
//STRIP001                                  sal_Unicode cInsChar, BOOL bSttQuote,
//STRIP001                                  BOOL bIns )
//STRIP001 {
//STRIP001  LanguageType eLang = rDoc.GetLanguage( nInsPos, FALSE );
//STRIP001  sal_Unicode cRet = GetQuote( cInsChar, bSttQuote, eLang );
//STRIP001
//STRIP001  //JP 13.02.99: damit beim Undo das "einfuegte" Zeichen wieder erscheint,
//STRIP001  //              wird es erstmal eingefuegt und dann ueberschrieben
//STRIP001  String sChg( cInsChar );
//STRIP001  if( bIns )
//STRIP001      rDoc.Insert( nInsPos, sChg );
//STRIP001  else
//STRIP001      rDoc.Replace( nInsPos, sChg );
//STRIP001
//STRIP001  //JP 13.08.97: Bug 42477 - bei doppelten Anfuehrungszeichen muss bei
//STRIP001  //              franzoesischer Sprache an Anfang ein Leerzeichen dahinter
//STRIP001  //              und am Ende ein Leerzeichen dahinter eingefuegt werden.
//STRIP001  sChg = cRet;
//STRIP001
//STRIP001  if( '\"' == cInsChar )
//STRIP001  {
//STRIP001      if( LANGUAGE_SYSTEM == eLang )
//STRIP001          eLang = GetAppLang();
//STRIP001      switch( eLang )
//STRIP001      {
//STRIP001      case LANGUAGE_FRENCH:
//STRIP001      case LANGUAGE_FRENCH_BELGIAN:
//STRIP001      case LANGUAGE_FRENCH_CANADIAN:
//STRIP001      case LANGUAGE_FRENCH_SWISS:
//STRIP001      case LANGUAGE_FRENCH_LUXEMBOURG:
//STRIP001          // JP 09.02.99: das zusaetzliche Zeichen immer per Insert einfuegen.
//STRIP001          //              Es ueberschreibt nichts!
//STRIP001          {
//STRIP001              String s( 0xA0 );       // UNICODE code for no break space
//STRIP001              if( rDoc.Insert( bSttQuote ? nInsPos+1 : nInsPos, s ))
//STRIP001              {
//STRIP001                  if( !bSttQuote )
//STRIP001                      ++nInsPos;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rDoc.Replace( nInsPos, sChg );
//STRIP001 }

//STRIP001 String SvxAutoCorrect::GetQuote( SvxAutoCorrDoc& rDoc, xub_StrLen nInsPos,
//STRIP001                              sal_Unicode cInsChar, BOOL bSttQuote )
//STRIP001 {
//STRIP001  LanguageType eLang = rDoc.GetLanguage( nInsPos, FALSE );
//STRIP001  sal_Unicode cRet = GetQuote( cInsChar, bSttQuote, eLang );
//STRIP001
//STRIP001  String sRet( cRet );
//STRIP001  //JP 13.08.97: Bug 42477 - bei doppelten Anfuehrungszeichen muss bei
//STRIP001  //              franzoesischer Sprache an Anfang ein Leerzeichen dahinter
//STRIP001  //              und am Ende ein Leerzeichen dahinter eingefuegt werden.
//STRIP001  if( '\"' == cInsChar )
//STRIP001  {
//STRIP001      if( LANGUAGE_SYSTEM == eLang )
//STRIP001          eLang = GetAppLang();
//STRIP001      switch( eLang )
//STRIP001      {
//STRIP001      case LANGUAGE_FRENCH:
//STRIP001      case LANGUAGE_FRENCH_BELGIAN:
//STRIP001      case LANGUAGE_FRENCH_CANADIAN:
//STRIP001      case LANGUAGE_FRENCH_SWISS:
//STRIP001      case LANGUAGE_FRENCH_LUXEMBOURG:
//STRIP001          if( bSttQuote )
//STRIP001              sRet += ' ';
//STRIP001          else
//STRIP001              sRet.Insert( ' ', 0 );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

//STRIP001 ULONG SvxAutoCorrect::AutoCorrect( SvxAutoCorrDoc& rDoc, const String& rTxt,
//STRIP001                                  xub_StrLen nInsPos, sal_Unicode cChar,
//STRIP001                                  BOOL bInsert )
//STRIP001 {
//STRIP001  ULONG nRet = 0;
//STRIP001  do{                                 // only for middle check loop !!
//STRIP001      if( cChar )
//STRIP001      {
//STRIP001          //JP 10.02.97: doppelte Spaces verhindern
//STRIP001          if( nInsPos && ' ' == cChar &&
//STRIP001              IsAutoCorrFlag( IngnoreDoubleSpace ) &&
//STRIP001              ' ' == rTxt.GetChar( nInsPos - 1 ) )
//STRIP001          {
//STRIP001              nRet = IngnoreDoubleSpace;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          BOOL bSingle = '\'' == cChar;
//STRIP001          BOOL bIsReplaceQuote =
//STRIP001                      (IsAutoCorrFlag( ChgQuotes ) && ('\"' == cChar )) ||
//STRIP001                      (IsAutoCorrFlag( ChgSglQuotes ) && bSingle );
//STRIP001          if( bIsReplaceQuote )
//STRIP001          {
//STRIP001              sal_Unicode cPrev;
//STRIP001              BOOL bSttQuote = !nInsPos ||
//STRIP001                      IsWordDelim( ( cPrev = rTxt.GetChar( nInsPos-1 ))) ||
//STRIP001 // os: #56034# - Warum kein schliessendes Anfuehrungszeichen nach dem Bindestrich?
//STRIP001 //                       strchr( "-([{", cPrev ) ||
//STRIP001                      lcl_IsInAsciiArr( "([{", cPrev ) ||
//STRIP001                      ( cEmDash && cEmDash == cPrev ) ||
//STRIP001                      ( cEnDash && cEnDash == cPrev );
//STRIP001
//STRIP001              InsertQuote( rDoc, nInsPos, cChar, bSttQuote, bInsert );
//STRIP001              nRet = bSingle ? ChgSglQuotes : ChgQuotes;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if( bInsert )
//STRIP001              rDoc.Insert( nInsPos, cChar );
//STRIP001          else
//STRIP001              rDoc.Replace( nInsPos, cChar );
//STRIP001      }
//STRIP001
//STRIP001      if( !nInsPos )
//STRIP001          break;
//STRIP001
//STRIP001      xub_StrLen nPos = nInsPos - 1;
//STRIP001
//STRIP001      // Bug 19286: nur direkt hinter dem "Wort" aufsetzen
//STRIP001      if( IsWordDelim( rTxt.GetChar( nPos )))
//STRIP001          break;
//STRIP001
//STRIP001      // automatisches Fett oder Unterstreichen setzen?
//STRIP001      if( '*' == cChar || '_' == cChar )
//STRIP001      {
//STRIP001          if( IsAutoCorrFlag( ChgWeightUnderl ) &&
//STRIP001              FnChgWeightUnderl( rDoc, rTxt, 0, nPos+1 ) )
//STRIP001              nRet = ChgWeightUnderl;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      while( nPos && !IsWordDelim( rTxt.GetChar( --nPos )))
//STRIP001          ;
//STRIP001
//STRIP001      // Absatz-Anfang oder ein Blank gefunden, suche nach dem Wort
//STRIP001      // Kuerzel im Auto
//STRIP001      xub_StrLen nCapLttrPos = nPos+1;        // auf das 1. Zeichen
//STRIP001      if( !nPos && !IsWordDelim( rTxt.GetChar( 0 )))
//STRIP001          --nCapLttrPos;          // Absatz Anfang und kein Blank !
//STRIP001
//STRIP001      LanguageType eLang = rDoc.GetLanguage( nCapLttrPos, FALSE );
//STRIP001      if( LANGUAGE_SYSTEM == eLang )
//STRIP001          eLang = GetSystemLanguage();
//STRIP001      CharClass& rCC = GetCharClass( eLang );
//STRIP001
//STRIP001      // Bug 19285: Symbolzeichen nicht anfassen
//STRIP001      if( lcl_IsSymbolChar( rCC, rTxt, nCapLttrPos, nInsPos ))
//STRIP001          break;
//STRIP001
//STRIP001      if( IsAutoCorrFlag( Autocorrect ) )
//STRIP001      {
//STRIP001          const String* pPara = 0;
//STRIP001          const String** ppPara = IsAutoCorrFlag(CptlSttSntnc) ? &pPara : 0;
//STRIP001
//STRIP001          BOOL bChgWord = rDoc.ChgAutoCorrWord( nCapLttrPos, nInsPos,
//STRIP001                                                  *this, ppPara );
//STRIP001          if( !bChgWord )
//STRIP001          {
//STRIP001              // JP 16.06.98: dann versuche mal alle !AlphaNum. Zeichen los zu
//STRIP001              //              werden und teste dann nochmals
//STRIP001              //JP 22.04.99: Bug 63883 - entferne nur die "Klammern Start/-Anfaenge",
//STRIP001              //              alle anderen Zeichen muessen drin bleiben.
//STRIP001              xub_StrLen nCapLttrPos1 = nCapLttrPos, nInsPos1 = nInsPos;
//STRIP001              while( nCapLttrPos1 < nInsPos &&
//STRIP001                      lcl_IsInAsciiArr( sImplSttSkipChars, rTxt.GetChar( nCapLttrPos1 ) )
//STRIP001                      )
//STRIP001                      ++nCapLttrPos1;
//STRIP001              while( nCapLttrPos1 < nInsPos1 && nInsPos1 &&
//STRIP001                      lcl_IsInAsciiArr( sImplEndSkipChars, rTxt.GetChar( nInsPos1-1 ) )
//STRIP001                      )
//STRIP001                      --nInsPos1;
//STRIP001
//STRIP001              if( (nCapLttrPos1 != nCapLttrPos || nInsPos1 != nInsPos ) &&
//STRIP001                  nCapLttrPos1 < nInsPos1 &&
//STRIP001                  rDoc.ChgAutoCorrWord( nCapLttrPos1, nInsPos1, *this, ppPara ))
//STRIP001              {
//STRIP001                  bChgWord = TRUE;
//STRIP001                  nCapLttrPos = nCapLttrPos1;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( bChgWord )
//STRIP001          {
//STRIP001              nRet = Autocorrect;
//STRIP001              if( pPara )
//STRIP001              {
//STRIP001                  xub_StrLen nEnd = nCapLttrPos;
//STRIP001                  while( nEnd < pPara->Len() &&
//STRIP001                          !IsWordDelim( pPara->GetChar( nEnd )))
//STRIP001                      ++nEnd;
//STRIP001
//STRIP001                  // Grossbuchstabe am Satz-Anfang ??
//STRIP001                  if( IsAutoCorrFlag( CptlSttSntnc ) &&
//STRIP001                      FnCptlSttSntnc( rDoc, *pPara, FALSE,
//STRIP001                                              nCapLttrPos, nEnd, eLang ) )
//STRIP001                      nRet |= CptlSttSntnc;
//STRIP001
//STRIP001                  if( IsAutoCorrFlag( ChgToEnEmDash ) &&
//STRIP001                      FnChgToEnEmDash( rDoc, rTxt, nCapLttrPos, nEnd, eLang ) )
//STRIP001                      nRet |= ChgToEnEmDash;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( ( IsAutoCorrFlag( nRet = ChgFractionSymbol ) &&
//STRIP001              FnChgFractionSymbol( rDoc, rTxt, nCapLttrPos, nInsPos ) ) ||
//STRIP001          ( IsAutoCorrFlag( nRet = ChgOrdinalNumber ) &&
//STRIP001              FnChgOrdinalNumber( rDoc, rTxt, nCapLttrPos, nInsPos, eLang ) ) ||
//STRIP001          ( IsAutoCorrFlag( nRet = SetINetAttr ) &&
//STRIP001              ( ' ' == cChar || '\t' == cChar || 0x0a == cChar || !cChar ) &&
//STRIP001              FnSetINetAttr( rDoc, rTxt, nCapLttrPos, nInsPos, eLang ) ) )
//STRIP001          ;
//STRIP001      else
//STRIP001      {
//STRIP001          nRet = 0;
//STRIP001          // Grossbuchstabe am Satz-Anfang ??
//STRIP001          if( IsAutoCorrFlag( CptlSttSntnc ) &&
//STRIP001              FnCptlSttSntnc( rDoc, rTxt, TRUE, nCapLttrPos, nInsPos, eLang ) )
//STRIP001              nRet |= CptlSttSntnc;
//STRIP001
//STRIP001          // Zwei Grossbuchstaben am Wort-Anfang ??
//STRIP001          if( IsAutoCorrFlag( CptlSttWrd ) &&
//STRIP001              FnCptlSttWrd( rDoc, rTxt, nCapLttrPos, nInsPos, eLang ) )
//STRIP001              nRet |= CptlSttWrd;
//STRIP001
//STRIP001          if( IsAutoCorrFlag( ChgToEnEmDash ) &&
//STRIP001              FnChgToEnEmDash( rDoc, rTxt, nCapLttrPos, nInsPos, eLang ) )
//STRIP001              nRet |= ChgToEnEmDash;
//STRIP001      }
//STRIP001
//STRIP001  } while( FALSE );
//STRIP001
//STRIP001  SfxViewFrame* pVFrame;
//STRIP001  if( nRet && 0 != (pVFrame = SfxViewFrame::Current()) &&
//STRIP001      pVFrame->GetFrame() )
//STRIP001  {
//STRIP001      ULONG nHelpId = 0;
//STRIP001      if( nRet & ( Autocorrect|CptlSttSntnc|CptlSttWrd|ChgToEnEmDash ) )
//STRIP001      {
//STRIP001          // von 0 - 15
//STRIP001          if( nRet & ChgToEnEmDash )
//STRIP001              nHelpId += 8;
//STRIP001          if( nRet & Autocorrect )
//STRIP001              nHelpId += 4;
//STRIP001          if( nRet & CptlSttSntnc )
//STRIP001              nHelpId += 2;
//STRIP001          if( nRet & CptlSttWrd )
//STRIP001              nHelpId += 1;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001               if( nRet & ChgQuotes)          nHelpId = 16;
//STRIP001          else if( nRet & ChgSglQuotes)       nHelpId = 17;
//STRIP001          else if( nRet & SetINetAttr)        nHelpId = 18;
//STRIP001          else if( nRet & IngnoreDoubleSpace) nHelpId = 19;
//STRIP001          else if( nRet & ChgWeightUnderl)    nHelpId = 20;
//STRIP001          else if( nRet & ChgFractionSymbol ) nHelpId = 21;
//STRIP001          else if( nRet & ChgOrdinalNumber)   nHelpId = 22;
//STRIP001      }
//STRIP001
//STRIP001      DBG_ASSERT( nHelpId && nHelpId < (HID_AUTOCORR_HELP_END -
//STRIP001                                        HID_AUTOCORR_HELP_START + 1),
//STRIP001                  "wrong HelpId Range" );
//STRIP001
//STRIP001      if( nHelpId )
//STRIP001      {
//STRIP001          nHelpId += HID_AUTOCORR_HELP_START - 1;
//STRIP001          SfxHelp::OpenHelpAgent( pVFrame->GetFrame(), nHelpId );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  return nRet;
//STRIP001 }
//STRIP001
//STRIP001 SvxAutoCorrectLanguageLists& SvxAutoCorrect::_GetLanguageList(
//STRIP001                                                      LanguageType eLang )
//STRIP001 {
//STRIP001  if( !pLangTable->IsKeyValid( ULONG( eLang )))
//STRIP001      CreateLanguageFile( eLang, TRUE);
//STRIP001  return *pLangTable->Seek( ULONG( eLang ) );
//STRIP001 }

//STRIP001 void SvxAutoCorrect::SaveCplSttExceptList( LanguageType eLang )
//STRIP001 {
//STRIP001  if( pLangTable->IsKeyValid( ULONG( eLang )))
//STRIP001  {
//STRIP001      SvxAutoCorrectLanguageListsPtr pLists = pLangTable->Seek(ULONG(eLang));
//STRIP001      if( pLists )
//STRIP001          pLists->SaveCplSttExceptList();
//STRIP001  }
//STRIP001 #ifndef PRODUCT
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR("speichern einer leeren Liste?")
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

//STRIP001 void SvxAutoCorrect::SaveWrdSttExceptList(LanguageType eLang)
//STRIP001 {
//STRIP001  if(pLangTable->IsKeyValid(ULONG(eLang)))
//STRIP001  {
//STRIP001      SvxAutoCorrectLanguageListsPtr pLists = pLangTable->Seek(ULONG(eLang));
//STRIP001      if(pLists)
//STRIP001          pLists->SaveWrdSttExceptList();
//STRIP001  }
//STRIP001 #ifndef PRODUCT
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR("speichern einer leeren Liste?")
//STRIP001  }
//STRIP001 #endif
//STRIP001 }


    // fuegt ein einzelnes Wort hinzu. Die Liste wird sofort
    // in die Datei geschrieben!
//STRIP001 BOOL SvxAutoCorrect::AddCplSttException( const String& rNew,
//STRIP001                                      LanguageType eLang )
//STRIP001 {
//STRIP001  SvxAutoCorrectLanguageListsPtr pLists = 0;
//STRIP001  //entweder die richtige Sprache ist vorhanden oder es kommt in die allg. Liste
//STRIP001  if( pLangTable->IsKeyValid(ULONG(eLang)))
//STRIP001      pLists = pLangTable->Seek(ULONG(eLang));
//STRIP001  else if(pLangTable->IsKeyValid(ULONG(LANGUAGE_DONTKNOW))||
//STRIP001          CreateLanguageFile(LANGUAGE_DONTKNOW, TRUE))
//STRIP001  {
//STRIP001      pLists = pLangTable->Seek(ULONG(LANGUAGE_DONTKNOW));
//STRIP001  }
//STRIP001  DBG_ASSERT(pLists, "keine Autokorrekturdatei")
//STRIP001  return pLists->AddToCplSttExceptList(rNew);
//STRIP001 }


    // fuegt ein einzelnes Wort hinzu. Die Liste wird sofort
    // in die Datei geschrieben!
//STRIP001 BOOL SvxAutoCorrect::AddWrtSttException( const String& rNew,
//STRIP001                                       LanguageType eLang )
//STRIP001 {
//STRIP001  SvxAutoCorrectLanguageListsPtr pLists = 0;
//STRIP001  //entweder die richtige Sprache ist vorhanden oder es kommt in die allg. Liste
//STRIP001  if(pLangTable->IsKeyValid(ULONG(eLang)))
//STRIP001      pLists = pLangTable->Seek(ULONG(eLang));
//STRIP001  else if(pLangTable->IsKeyValid(ULONG(LANGUAGE_DONTKNOW))||
//STRIP001          CreateLanguageFile(LANGUAGE_DONTKNOW, TRUE))
//STRIP001      pLists = pLangTable->Seek(ULONG(LANGUAGE_DONTKNOW));
//STRIP001  DBG_ASSERT(pLists, "keine Autokorrekturdatei")
//STRIP001  return pLists->AddToWrdSttExceptList(rNew);
//STRIP001 }




//STRIP001 void SvxAutoCorrect::SetUserAutoCorrFileName( const String& rNew )
//STRIP001 {
//STRIP001  if( sUserAutoCorrFile != rNew )
//STRIP001  {
//STRIP001      sUserAutoCorrFile = rNew;
//STRIP001
//STRIP001      // sind die Listen gesetzt sind, so muessen sie jetzt geloescht
//STRIP001      // werden
//STRIP001      lcl_ClearTable(*pLangTable);
//STRIP001      nFlags &= ~(CplSttLstLoad | WrdSttLstLoad | ChgWordLstLoad );
//STRIP001  }
//STRIP001 }

//STRIP001 void SvxAutoCorrect::SetShareAutoCorrFileName( const String& rNew )
//STRIP001 {
//STRIP001  if( sShareAutoCorrFile != rNew )
//STRIP001  {
//STRIP001      sShareAutoCorrFile = rNew;
//STRIP001
//STRIP001      // sind die Listen gesetzt sind, so muessen sie jetzt geloescht
//STRIP001      // werden
//STRIP001      lcl_ClearTable(*pLangTable);
//STRIP001      nFlags &= ~(CplSttLstLoad | WrdSttLstLoad | ChgWordLstLoad );
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL SvxAutoCorrect::GetPrevAutoCorrWord( SvxAutoCorrDoc& rDoc,
//STRIP001                                      const String& rTxt, xub_StrLen nPos,
//STRIP001                                      String& rWord ) const
//STRIP001 {
//STRIP001  if( !nPos )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  xub_StrLen nEnde = nPos;
//STRIP001
//STRIP001  // dahinter muss ein Blank oder Tab folgen!
//STRIP001  if( ( nPos < rTxt.Len() &&
//STRIP001      !IsWordDelim( rTxt.GetChar( nPos ))) ||
//STRIP001      IsWordDelim( rTxt.GetChar( --nPos )))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  while( nPos && !IsWordDelim( rTxt.GetChar( --nPos )))
//STRIP001      ;
//STRIP001
//STRIP001  // Absatz-Anfang oder ein Blank gefunden, suche nach dem Wort
//STRIP001  // Kuerzel im Auto
//STRIP001  xub_StrLen nCapLttrPos = nPos+1;        // auf das 1. Zeichen
//STRIP001  if( !nPos && !IsWordDelim( rTxt.GetChar( 0 )))
//STRIP001      --nCapLttrPos;          // Absatz Anfang und kein Blank !
//STRIP001
//STRIP001  while( lcl_IsInAsciiArr( sImplSttSkipChars, rTxt.GetChar( nCapLttrPos )) )
//STRIP001      if( ++nCapLttrPos >= nEnde )
//STRIP001          return FALSE;
//STRIP001
//STRIP001  // Bug 19285: Symbolzeichen nicht anfassen
//STRIP001  // Interresant erst ab 3 Zeichen
//STRIP001  if( 3 > nEnde - nCapLttrPos )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  LanguageType eLang = rDoc.GetLanguage( nCapLttrPos, FALSE );
//STRIP001  if( LANGUAGE_SYSTEM == eLang )
//STRIP001      eLang = GetSystemLanguage();
//STRIP001
//STRIP001  SvxAutoCorrect* pThis = (SvxAutoCorrect*)this;
//STRIP001  CharClass& rCC = pThis->GetCharClass( eLang );
//STRIP001
//STRIP001  if( lcl_IsSymbolChar( rCC, rTxt, nCapLttrPos, nEnde ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  rWord = rTxt.Copy( nCapLttrPos, nEnde - nCapLttrPos );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SvxAutoCorrect::CreateLanguageFile( LanguageType eLang, BOOL bNewFile )
//STRIP001 {
//STRIP001  DBG_ASSERT(!pLangTable->IsKeyValid(ULONG(eLang)), "Sprache ist bereits vorhanden")
//STRIP001
//STRIP001  String sUserDirFile( GetAutoCorrFileName( eLang, TRUE, FALSE )),
//STRIP001         sShareDirFile( sUserDirFile );
//STRIP001  SvxAutoCorrectLanguageListsPtr pLists = 0;
//STRIP001
//STRIP001  Time nMinTime( 0, 2 ), nAktTime, nLastCheckTime;
//STRIP001  ULONG nFndPos;
//STRIP001  if( TABLE_ENTRY_NOTFOUND !=
//STRIP001                  pLastFileTable->SearchKey( ULONG( eLang ), &nFndPos ) &&
//STRIP001      ( nLastCheckTime.SetTime( pLastFileTable->GetObject( nFndPos )),
//STRIP001          nLastCheckTime < nAktTime ) &&
//STRIP001      ( nAktTime - nLastCheckTime ) < nMinTime )
//STRIP001  {
//STRIP001      // no need to test the file, because the last check is not older then
//STRIP001      // 2 minutes.
//STRIP001      if( bNewFile )
//STRIP001      {
//STRIP001          sShareDirFile = sUserDirFile;
//STRIP001          pLists = new SvxAutoCorrectLanguageLists( *this, sShareDirFile,
//STRIP001                                                      sUserDirFile, eLang );
//STRIP001          pLangTable->Insert( ULONG(eLang), pLists );
//STRIP001          pLastFileTable->Remove( ULONG( eLang ) );
//STRIP001      }
//STRIP001  }
//STRIP001  else if( ( FStatHelper::IsDocument( sUserDirFile ) ||
//STRIP001             FStatHelper::IsDocument( sShareDirFile =
//STRIP001                          GetAutoCorrFileName( eLang, FALSE, FALSE ) ) ) ||
//STRIP001      ( sShareDirFile = sUserDirFile, bNewFile ))
//STRIP001  {
//STRIP001      pLists = new SvxAutoCorrectLanguageLists( *this, sShareDirFile,
//STRIP001                                                  sUserDirFile, eLang );
//STRIP001      pLangTable->Insert( ULONG(eLang), pLists );
//STRIP001      pLastFileTable->Remove( ULONG( eLang ) );
//STRIP001  }
//STRIP001  else if( !bNewFile )
//STRIP001  {
//STRIP001      if( !pLastFileTable->Insert( ULONG( eLang ), nAktTime.GetTime() ))
//STRIP001          pLastFileTable->Replace( ULONG( eLang ), nAktTime.GetTime() );
//STRIP001  }
//STRIP001  return pLists != 0;
//STRIP001 }

//STRIP001 BOOL SvxAutoCorrect::PutText( const String& rShort, const String& rLong,
//STRIP001                              LanguageType eLang )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( pLangTable->IsKeyValid( ULONG(eLang)) || CreateLanguageFile(eLang) )
//STRIP001      bRet = pLangTable->Seek( ULONG(eLang) )->PutText(rShort, rLong);
//STRIP001  return bRet;
//STRIP001 }


    //  - loesche einen Eintrag
//STRIP001 BOOL SvxAutoCorrect::DeleteText( const String& rShort, LanguageType eLang )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( pLangTable->IsKeyValid( ULONG( eLang )) )
//STRIP001      bRet = pLangTable->Seek( ULONG( eLang ))->DeleteText( rShort );
//STRIP001  return bRet;
//STRIP001 }


    //  - return den Ersetzungstext (nur fuer SWG-Format, alle anderen
    //      koennen aus der Wortliste herausgeholt werden!)
//STRIP001 BOOL SvxAutoCorrect::GetLongText( SvStorageRef&, const String& , String& )
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

    //  - Text mit Attributierung (kann nur der SWG - SWG-Format!)
//STRIP001 BOOL SvxAutoCorrect::PutText( SvStorage&, const String&, SfxObjectShell&,
//STRIP001                              String& )
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }



//STRIP001 void EncryptBlockName_Imp( String& rName )
//STRIP001 {
//STRIP001  xub_StrLen nLen, nPos = 1;
//STRIP001  rName.Insert( '#', 0 );
//STRIP001  sal_Unicode* pName = rName.GetBufferAccess();
//STRIP001  for ( nLen = rName.Len(), ++pName; nPos < nLen; ++nPos, ++pName )
//STRIP001  {
//STRIP001      if( lcl_IsInAsciiArr( "!/:.\\", *pName ))
//STRIP001          *pName &= 0x0f;
//STRIP001  }
//STRIP001 }

/* This code is copied from SwXMLTextBlocks::GeneratePackageName */
//STRIP001 void GeneratePackageName ( const String& rShort, String& rPackageName )
//STRIP001 {
//STRIP001  rPackageName = rShort;
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  sal_Unicode pDelims[] = { '!', '/', ':', '.', '\\', 0 };
//STRIP001  ByteString sByte ( rPackageName, RTL_TEXTENCODING_UTF7);
//STRIP001  rPackageName = String (sByte, RTL_TEXTENCODING_ASCII_US);
//STRIP001  while( STRING_NOTFOUND != ( nPos = rPackageName.SearchChar( pDelims, nPos )))
//STRIP001  {
//STRIP001      rPackageName.SetChar( nPos, '_' );
//STRIP001      ++nPos;
//STRIP001  }
//STRIP001 }

//STRIP001 void DecryptBlockName_Imp( String& rName )
//STRIP001 {
//STRIP001  if( '#' == rName.GetChar( 0 ) )
//STRIP001  {
//STRIP001      rName.Erase( 0, 1 );
//STRIP001      sal_Unicode* pName = rName.GetBufferAccess();
//STRIP001      xub_StrLen nLen, nPos;
//STRIP001      for ( nLen = rName.Len(), nPos = 0; nPos < nLen; ++nPos, ++pName )
//STRIP001          switch( *pName )
//STRIP001          {
//STRIP001          case 0x01:  *pName = '!';   break;
//STRIP001          case 0x0A:  *pName = ':';   break;
//STRIP001          case 0x0C:  *pName = '\\';  break;
//STRIP001          case 0x0E:  *pName = '.';   break;
//STRIP001          case 0x0F:  *pName = '/';   break;
//STRIP001          }
//STRIP001  }
//STRIP001 }


/* -----------------18.11.98 16:00-------------------
 *
 * --------------------------------------------------*/
//STRIP001 const SvxAutocorrWord* lcl_SearchWordsInList(
//STRIP001              SvxAutoCorrectLanguageListsPtr pList, const String& rTxt,
//STRIP001              xub_StrLen& rStt, xub_StrLen nEndPos, SvxAutoCorrDoc& rDoc )
//STRIP001 {
//STRIP001  const SvxAutocorrWordList* pAutoCorrWordList = pList->GetAutocorrWordList();
//STRIP001  TransliterationWrapper& rCmp = GetIgnoreTranslWrapper();
//STRIP001  for( xub_StrLen nPos = 0; nPos < pAutoCorrWordList->Count(); ++nPos )
//STRIP001  {
//STRIP001      const SvxAutocorrWord* pFnd = (*pAutoCorrWordList)[ nPos ];
//STRIP001      const String& rChk = pFnd->GetShort();
//STRIP001      if( nEndPos >= rChk.Len() )
//STRIP001      {
//STRIP001          xub_StrLen nCalcStt = nEndPos - rChk.Len();
//STRIP001          if( ( !nCalcStt || nCalcStt == rStt ||
//STRIP001              ( nCalcStt < rStt &&
//STRIP001                  IsWordDelim( rTxt.GetChar(nCalcStt - 1 ) ))) )
//STRIP001          {
//STRIP001              String sWord( rTxt.GetBuffer() + nCalcStt, rChk.Len() );
//STRIP001              if( rCmp.isEqual( rChk, sWord ))
//STRIP001              {
//STRIP001                  rStt = nCalcStt;
//STRIP001                  return pFnd;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }


// suche das oder die Worte in der ErsetzungsTabelle
//STRIP001 const SvxAutocorrWord* SvxAutoCorrect::SearchWordsInList(
//STRIP001              const String& rTxt, xub_StrLen& rStt, xub_StrLen nEndPos,
//STRIP001              SvxAutoCorrDoc& rDoc, LanguageType& rLang )
//STRIP001 {
//STRIP001  LanguageType eLang = rLang;
//STRIP001  const SvxAutocorrWord* pRet = 0;
//STRIP001  if( LANGUAGE_SYSTEM == eLang )
//STRIP001      eLang = GetSystemLanguage();
//STRIP001
//STRIP001  // zuerst nach eLang suchen, dann nach der Obersprache
//STRIP001  // US-Englisch -> Englisch und zuletzt in LANGUAGE_DONTKNOW
//STRIP001
//STRIP001  if( pLangTable->IsKeyValid( ULONG( eLang ) ) ||
//STRIP001      CreateLanguageFile( eLang, FALSE ))
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pList = pLangTable->Seek(ULONG(eLang));
//STRIP001      pRet = lcl_SearchWordsInList(  pList, rTxt, rStt, nEndPos, rDoc );
//STRIP001      if( pRet )
//STRIP001      {
//STRIP001          rLang = eLang;
//STRIP001          return pRet;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // wenn es hier noch nicht gefunden werden konnte, dann weitersuchen
//STRIP001  ULONG nTmpKey1 = eLang & 0x7ff, // die Hauptsprache in vielen Faellen u.B. DE
//STRIP001        nTmpKey2 = eLang & 0x3ff, // sonst z.B. EN
//STRIP001        nTmp;
//STRIP001
//STRIP001  if( ((nTmp = nTmpKey1) != (ULONG)eLang &&
//STRIP001       ( pLangTable->IsKeyValid( nTmpKey1 ) ||
//STRIP001         CreateLanguageFile( LanguageType( nTmpKey1 ), FALSE ) )) ||
//STRIP001      (( nTmp = nTmpKey2) != (ULONG)eLang &&
//STRIP001       ( pLangTable->IsKeyValid( nTmpKey2 ) ||
//STRIP001         CreateLanguageFile( LanguageType( nTmpKey2 ), FALSE ) )) )
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pList = pLangTable->Seek( nTmp );
//STRIP001      pRet = lcl_SearchWordsInList( pList, rTxt, rStt, nEndPos, rDoc);
//STRIP001      if( pRet )
//STRIP001      {
//STRIP001          rLang = LanguageType( nTmp );
//STRIP001          return pRet;
//STRIP001      }
//STRIP001  }
//STRIP001  if( pLangTable->IsKeyValid( ULONG( LANGUAGE_DONTKNOW ) ) ||
//STRIP001      CreateLanguageFile( LANGUAGE_DONTKNOW, FALSE ) )
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pList = pLangTable->Seek(ULONG(LANGUAGE_DONTKNOW));
//STRIP001      pRet = lcl_SearchWordsInList( pList, rTxt, rStt, nEndPos, rDoc);
//STRIP001      if( pRet )
//STRIP001      {
//STRIP001          rLang = LANGUAGE_DONTKNOW;
//STRIP001          return pRet;
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }
/* -----------------18.11.98 13:46-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrect::FindInWrdSttExceptList( LanguageType eLang,
//STRIP001                                           const String& sWord )
//STRIP001 {
//STRIP001  //zuerst nach eLang suchen, dann nach der Obersprace US-Englisch -> Englisch
//STRIP001  //und zuletzt in LANGUAGE_DONTKNOW
//STRIP001  ULONG nTmpKey1 = eLang & 0x7ff; // die Hauptsprache in vielen Faellen u.B. DE
//STRIP001  ULONG nTmpKey2 = eLang & 0x3ff; // sonst z.B. EN
//STRIP001  String sTemp(sWord);
//STRIP001  if( pLangTable->IsKeyValid( ULONG( eLang )) ||
//STRIP001      CreateLanguageFile( eLang, FALSE ) )
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pList = pLangTable->Seek(ULONG(eLang));
//STRIP001      String sTemp(sWord);
//STRIP001      if(pList->GetWrdSttExceptList()->Seek_Entry(&sTemp))
//STRIP001          return TRUE;
//STRIP001
//STRIP001  }
//STRIP001  // wenn es hier noch nicht gefunden werden konnte, dann weitersuchen
//STRIP001  ULONG nTmp;
//STRIP001  if( ((nTmp = nTmpKey1) != (ULONG)eLang &&
//STRIP001       ( pLangTable->IsKeyValid( nTmpKey1 ) ||
//STRIP001         CreateLanguageFile( LanguageType( nTmpKey1 ), FALSE ) )) ||
//STRIP001      (( nTmp = nTmpKey2) != (ULONG)eLang &&
//STRIP001       ( pLangTable->IsKeyValid( nTmpKey2 ) ||
//STRIP001         CreateLanguageFile( LanguageType( nTmpKey2 ), FALSE ) )) )
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pList = pLangTable->Seek(nTmp);
//STRIP001      if(pList->GetWrdSttExceptList()->Seek_Entry(&sTemp))
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  if(pLangTable->IsKeyValid(ULONG(LANGUAGE_DONTKNOW))|| CreateLanguageFile(LANGUAGE_DONTKNOW, FALSE))
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pList = pLangTable->Seek(ULONG(LANGUAGE_DONTKNOW));
//STRIP001      if(pList->GetWrdSttExceptList()->Seek_Entry(&sTemp))
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }
/* -----------------18.11.98 14:28-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL lcl_FindAbbreviation( const SvStringsISortDtor* pList, const String& sWord)
//STRIP001 {
//STRIP001  String sAbk( '~' );
//STRIP001  USHORT nPos;
//STRIP001  pList->Seek_Entry( &sAbk, &nPos );
//STRIP001  if( nPos < pList->Count() )
//STRIP001  {
//STRIP001      String sLowerWord( sWord ); sLowerWord.ToLowerAscii();
//STRIP001      const String* pAbk;
//STRIP001      for( USHORT n = nPos;
//STRIP001              n < pList->Count() &&
//STRIP001              '~' == ( pAbk = (*pList)[ n ])->GetChar( 0 );
//STRIP001          ++n )
//STRIP001      {
//STRIP001          // ~ und ~. sind nicht erlaubt!
//STRIP001          if( 2 < pAbk->Len() && pAbk->Len() - 1 <= sWord.Len() )
//STRIP001          {
//STRIP001              String sLowerAbk( *pAbk ); sLowerAbk.ToLowerAscii();
//STRIP001              for( xub_StrLen i = sLowerAbk.Len(), ii = sLowerWord.Len(); i; )
//STRIP001              {
//STRIP001                  if( !--i )      // stimmt ueberein
//STRIP001                      return TRUE;
//STRIP001
//STRIP001                  if( sLowerAbk.GetChar( i ) != sLowerWord.GetChar( --ii ))
//STRIP001                      break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  DBG_ASSERT( !(nPos && '~' == (*pList)[ --nPos ]->GetChar( 0 ) ),
//STRIP001          "falsch sortierte ExeptionListe?" );
//STRIP001  return FALSE;
//STRIP001 }
/* -----------------18.11.98 14:49-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrect::FindInCplSttExceptList(LanguageType eLang,
//STRIP001                              const String& sWord, BOOL bAbbreviation)
//STRIP001 {
//STRIP001  //zuerst nach eLang suchen, dann nach der Obersprace US-Englisch -> Englisch
//STRIP001  //und zuletzt in LANGUAGE_DONTKNOW
//STRIP001  ULONG nTmpKey1 = eLang & 0x7ff; // die Hauptsprache in vielen Faellen u.B. DE
//STRIP001  ULONG nTmpKey2 = eLang & 0x3ff; // sonst z.B. EN
//STRIP001  String sTemp( sWord );
//STRIP001  if( pLangTable->IsKeyValid( ULONG( eLang )) ||
//STRIP001      CreateLanguageFile( eLang, FALSE ))
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pLists = pLangTable->Seek(ULONG(eLang));
//STRIP001      const SvStringsISortDtor* pList = pLists->GetCplSttExceptList();
//STRIP001      if(bAbbreviation ? lcl_FindAbbreviation( pList, sWord)
//STRIP001                       : pList->Seek_Entry( &sTemp ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  // wenn es hier noch nicht gefunden werden konnte, dann weitersuchen
//STRIP001  ULONG nTmp;
//STRIP001
//STRIP001  if( ((nTmp = nTmpKey1) != (ULONG)eLang &&
//STRIP001       ( pLangTable->IsKeyValid( nTmpKey1 ) ||
//STRIP001         CreateLanguageFile( LanguageType( nTmpKey1 ), FALSE ) )) ||
//STRIP001      (( nTmp = nTmpKey2) != (ULONG)eLang &&
//STRIP001       ( pLangTable->IsKeyValid( nTmpKey2 ) ||
//STRIP001         CreateLanguageFile( LanguageType( nTmpKey2 ), FALSE ) )) )
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pLists = pLangTable->Seek(nTmp);
//STRIP001      const SvStringsISortDtor* pList = pLists->GetCplSttExceptList();
//STRIP001      if(bAbbreviation ? lcl_FindAbbreviation( pList, sWord)
//STRIP001                       : pList->Seek_Entry( &sTemp ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  if(pLangTable->IsKeyValid(ULONG(LANGUAGE_DONTKNOW))|| CreateLanguageFile(LANGUAGE_DONTKNOW, FALSE))
//STRIP001  {
//STRIP001      //die Sprache ist vorhanden - also her damit
//STRIP001      SvxAutoCorrectLanguageListsPtr pLists = pLangTable->Seek(LANGUAGE_DONTKNOW);
//STRIP001      const SvStringsISortDtor* pList = pLists->GetCplSttExceptList();
//STRIP001      if(bAbbreviation ? lcl_FindAbbreviation( pList, sWord)
//STRIP001                       : pList->Seek_Entry( &sTemp ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001
//STRIP001 }

/* -----------------20.11.98 11:53-------------------
 *
 * --------------------------------------------------*/
//STRIP001 String SvxAutoCorrect::GetAutoCorrFileName( LanguageType eLang,
//STRIP001                                          BOOL bNewFile, BOOL bTst ) const
//STRIP001 {
//STRIP001  String sRet, sExt( String::CreateFromInt32( eLang ));
//STRIP001  sExt.AppendAscii( ".dat" );
//STRIP001
//STRIP001  if( bNewFile )
//STRIP001      ( sRet = sUserAutoCorrFile ) += sExt;
//STRIP001  else if( !bTst )
//STRIP001      ( sRet = sShareAutoCorrFile ) += sExt;
//STRIP001  else
//STRIP001  {
//STRIP001      // test first in the user directory - if not exist, then
//STRIP001      ( sRet = sUserAutoCorrFile ) += sExt;
//STRIP001      if( !FStatHelper::IsDocument( sRet ))
//STRIP001          ( sRet = sShareAutoCorrFile ) += sExt;
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

/* -----------------18.11.98 11:16-------------------
 *
 * --------------------------------------------------*/
/*N*/ SvxAutoCorrectLanguageLists::SvxAutoCorrectLanguageLists(
/*N*/               SvxAutoCorrect& rParent,
/*N*/               const String& rShareAutoCorrectFile,
/*N*/               const String& rUserAutoCorrectFile,
/*N*/               LanguageType eLang)
//STRIP001  : rAutoCorrect(rParent),
//STRIP001  eLanguage(eLang),
//STRIP001  sShareAutoCorrFile( rShareAutoCorrectFile ),
//STRIP001  sUserAutoCorrFile( rUserAutoCorrectFile ),
//STRIP001  nFlags(0),
//STRIP001  pCplStt_ExcptLst( 0 ),
//STRIP001  pWrdStt_ExcptLst( 0 ),
//STRIP001  pAutocorr_List( 0 )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/* -----------------18.11.98 11:16-------------------
 *
 * --------------------------------------------------*/
/*N*/ SvxAutoCorrectLanguageLists::~SvxAutoCorrectLanguageLists()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  delete pCplStt_ExcptLst;
//STRIP001  delete pWrdStt_ExcptLst;
//STRIP001  delete pAutocorr_List;
/*N*/ }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrectLanguageLists::IsFileChanged_Imp()
//STRIP001 {
//STRIP001  // nur alle 2 Minuten aufs FileSystem zugreifen um den
//STRIP001  // Dateistempel zu ueberpruefen
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  Time nMinTime( 0, 2 );
//STRIP001  Time nAktTime;
//STRIP001  if( aLastCheckTime > nAktTime ||                    // ueberlauf ?
//STRIP001      ( nAktTime -= aLastCheckTime ) > nMinTime )     // min Zeit vergangen
//STRIP001  {
//STRIP001      Date aTstDate; Time aTstTime;
//STRIP001      if( FStatHelper::GetModifiedDateTimeOfFile( sShareAutoCorrFile,
//STRIP001                                          &aTstDate, &aTstTime ) &&
//STRIP001          ( aModifiedDate != aTstDate || aModifiedTime != aTstTime ))
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          // dann mal schnell alle Listen entfernen!
//STRIP001          if( CplSttLstLoad & nFlags && pCplStt_ExcptLst )
//STRIP001              delete pCplStt_ExcptLst, pCplStt_ExcptLst = 0;
//STRIP001          if( WrdSttLstLoad & nFlags && pWrdStt_ExcptLst )
//STRIP001              delete pWrdStt_ExcptLst, pWrdStt_ExcptLst = 0;
//STRIP001          if( ChgWordLstLoad & nFlags && pAutocorr_List )
//STRIP001              delete pAutocorr_List, pAutocorr_List = 0;
//STRIP001          nFlags &= ~(CplSttLstLoad | WrdSttLstLoad | ChgWordLstLoad );
//STRIP001      }
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::LoadExceptList_Imp(
//STRIP001                                      SvStringsISortDtor*& rpLst,
//STRIP001                                      const sal_Char* pStrmName,
//STRIP001                                      SvStorageRef &rStg)
//STRIP001 {
//STRIP001  if( rpLst )
//STRIP001      rpLst->DeleteAndDestroy( 0, rpLst->Count() );
//STRIP001  else
//STRIP001      rpLst = new SvStringsISortDtor( 16, 16 );
//STRIP001
//STRIP001  {
//STRIP001
//STRIP001      String sStrmName( pStrmName, RTL_TEXTENCODING_MS_1252 );
//STRIP001      String sTmp( sStrmName );
//STRIP001
//STRIP001      if( rStg.Is() && ( rStg->IsStream( sStrmName ) ||
//STRIP001          // "alte" Listen konvertieren!
//STRIP001          ( pCplStt_ExcptLst == rpLst &&
//STRIP001              rStg->IsStream( sTmp.AssignAscii( "ExceptionList" ))) ))
//STRIP001      {
//STRIP001          SvStorageStreamRef xStrm = rStg->OpenStream( sTmp,
//STRIP001              ( STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE ) );
//STRIP001          if( SVSTREAM_OK != xStrm->GetError())
//STRIP001          {
//STRIP001              xStrm.Clear();
//STRIP001              rStg.Clear();
//STRIP001              RemoveStream_Imp( sStrmName );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              xStrm->SetBufferSize( 8192 );
//STRIP001
//STRIP001              BYTE cLen, cSet;
//STRIP001              USHORT nVersion, nCount;
//STRIP001              *xStrm >> cLen >> nVersion >> cSet >> nCount;
//STRIP001
//STRIP001              for( USHORT i = 0; i < nCount; ++i)
//STRIP001              {
//STRIP001                  String* pNew = new String;
//STRIP001                  xStrm->ReadByteString( *pNew, cSet );
//STRIP001
//STRIP001                  if( xStrm->IsEof() || SVSTREAM_OK != xStrm->GetError() )
//STRIP001                  {
//STRIP001 //                       nErr = ( pExceptLst->GetError() == SVSTREAM_OK )
//STRIP001 //                                   ? 0 : ERR_SWG_READ_ERROR;
//STRIP001                      xStrm.Clear();
//STRIP001                      delete pNew;
//STRIP001                      break;
//STRIP001                  }
//STRIP001
//STRIP001                  if( !rpLst->Insert( pNew ) )
//STRIP001                      delete pNew;
//STRIP001              }
//STRIP001
//STRIP001              if( sTmp != sStrmName )
//STRIP001              {
//STRIP001                  xStrm.Clear();
//STRIP001                  rStg.Clear();
//STRIP001                  RemoveStream_Imp( sTmp );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Zeitstempel noch setzen
//STRIP001      FStatHelper::GetModifiedDateTimeOfFile( sShareAutoCorrFile,
//STRIP001                                      &aModifiedDate, &aModifiedTime );
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001 }
//STRIP001 void SvxAutoCorrectLanguageLists::LoadXMLExceptList_Imp(
//STRIP001                                      SvStringsISortDtor*& rpLst,
//STRIP001                                      const sal_Char* pStrmName,
//STRIP001                                      SvStorageRef &rStg)
//STRIP001 {
//STRIP001  if( rpLst )
//STRIP001      rpLst->DeleteAndDestroy( 0, rpLst->Count() );
//STRIP001  else
//STRIP001      rpLst = new SvStringsISortDtor( 16, 16 );
//STRIP001
//STRIP001  {
//STRIP001      String sStrmName( pStrmName, RTL_TEXTENCODING_MS_1252 );
//STRIP001      String sTmp( sStrmName );
//STRIP001
//STRIP001      if( rStg.Is() && rStg->IsStream( sStrmName ) )
//STRIP001      {
//STRIP001          SvStorageStreamRef xStrm = rStg->OpenStream( sTmp,
//STRIP001              ( STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE ) );
//STRIP001          if( SVSTREAM_OK != xStrm->GetError())
//STRIP001          {
//STRIP001              xStrm.Clear();
//STRIP001              rStg.Clear();
//STRIP001              RemoveStream_Imp( sStrmName );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              Reference< lang::XMultiServiceFactory > xServiceFactory =
//STRIP001                  ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001              DBG_ASSERT( xServiceFactory.is(),
//STRIP001                  "XMLReader::Read: got no service manager" );
//STRIP001              if( !xServiceFactory.is() )
//STRIP001              {
//STRIP001                  // Throw an exception ?
//STRIP001              }
//STRIP001
//STRIP001              xml::sax::InputSource aParserInput;
//STRIP001              aParserInput.sSystemId = sStrmName;
//STRIP001
//STRIP001              xStrm->Seek( 0L );
//STRIP001              xStrm->SetBufferSize( 8 * 1024 );
//STRIP001              aParserInput.aInputStream = new utl::OInputStreamWrapper( *xStrm );
//STRIP001
//STRIP001              // get parser
//STRIP001              Reference< XInterface > xXMLParser = xServiceFactory->createInstance(
//STRIP001                  OUString::createFromAscii("com.sun.star.xml.sax.Parser") );
//STRIP001              DBG_ASSERT( xXMLParser.is(),
//STRIP001                  "XMLReader::Read: com.sun.star.xml.sax.Parser service missing" );
//STRIP001              if( !xXMLParser.is() )
//STRIP001              {
//STRIP001                  // Maybe throw an exception?
//STRIP001              }
//STRIP001
//STRIP001              // get filter
//STRIP001              // #110680#
//STRIP001              // Reference< xml::sax::XDocumentHandler > xFilter = new SvXMLExceptionListImport ( *rpLst );
//STRIP001              Reference< xml::sax::XDocumentHandler > xFilter = new SvXMLExceptionListImport ( xServiceFactory, *rpLst );
//STRIP001
//STRIP001              // connect parser and filter
//STRIP001              Reference< xml::sax::XParser > xParser( xXMLParser, UNO_QUERY );
//STRIP001              xParser->setDocumentHandler( xFilter );
//STRIP001
//STRIP001              // parse
//STRIP001              try
//STRIP001              {
//STRIP001                  xParser->parseStream( aParserInput );
//STRIP001              }
//STRIP001              catch( xml::sax::SAXParseException&  )
//STRIP001              {
//STRIP001                  // re throw ?
//STRIP001              }
//STRIP001              catch( xml::sax::SAXException&  )
//STRIP001              {
//STRIP001                  // re throw ?
//STRIP001              }
//STRIP001              catch( io::IOException& )
//STRIP001              {
//STRIP001                  // re throw ?
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Zeitstempel noch setzen
//STRIP001      FStatHelper::GetModifiedDateTimeOfFile( sShareAutoCorrFile,
//STRIP001                                      &aModifiedDate, &aModifiedTime );
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::SaveExceptList_Imp(
//STRIP001                          const SvStringsISortDtor& rLst,
//STRIP001                          const sal_Char* pStrmName,
//STRIP001                          SvStorageRef &rStg,
//STRIP001                          BOOL bConvert )
//STRIP001 {
//STRIP001  if( rStg.Is() )
//STRIP001  {
//STRIP001      String sStrmName( pStrmName, RTL_TEXTENCODING_MS_1252 );
//STRIP001      if( !rLst.Count() )
//STRIP001      {
//STRIP001          rStg->Remove( sStrmName );
//STRIP001          rStg->Commit();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SvStorageStreamRef xStrm = rStg->OpenStream( sStrmName,
//STRIP001                  ( STREAM_READ | STREAM_WRITE | STREAM_SHARE_DENYWRITE ) );
//STRIP001          if( xStrm.Is() )
//STRIP001          {
//STRIP001              xStrm->SetSize( 0 );
//STRIP001              xStrm->SetBufferSize( 8192 );
//STRIP001              String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
//STRIP001              OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
//STRIP001              uno::Any aAny;
//STRIP001              aAny <<= aMime;
//STRIP001              xStrm->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001
//STRIP001              Reference< lang::XMultiServiceFactory > xServiceFactory =
//STRIP001                  ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001              DBG_ASSERT( xServiceFactory.is(),
//STRIP001                          "XMLReader::Read: got no service manager" );
//STRIP001              if( !xServiceFactory.is() )
//STRIP001              {
//STRIP001                  // Throw an exception ?
//STRIP001              }
//STRIP001
//STRIP001                  Reference < XInterface > xWriter (xServiceFactory->createInstance(
//STRIP001                       OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer"))));
//STRIP001                  DBG_ASSERT(xWriter.is(),"com.sun.star.xml.sax.Writer service missing");
//STRIP001              Reference < io::XOutputStream> xOut = new utl::OOutputStreamWrapper( *xStrm );
//STRIP001                  uno::Reference<io::XActiveDataSource> xSrc(xWriter, uno::UNO_QUERY);
//STRIP001                  xSrc->setOutputStream(xOut);
//STRIP001
//STRIP001                  uno::Reference<xml::sax::XDocumentHandler> xHandler(xWriter, uno::UNO_QUERY);
//STRIP001
//STRIP001              // #110680#
//STRIP001                  // SvXMLExceptionListExport aExp(rLst, sStrmName, xHandler);
//STRIP001                  SvXMLExceptionListExport aExp( xServiceFactory, rLst, sStrmName, xHandler );
//STRIP001
//STRIP001              aExp.exportDoc( XML_BLOCK_LIST );
//STRIP001
//STRIP001              xStrm->Commit();
//STRIP001              if( xStrm->GetError() == SVSTREAM_OK )
//STRIP001              {
//STRIP001                  xStrm.Clear();
//STRIP001                  if (!bConvert)
//STRIP001                  {
//STRIP001                      rStg->Commit();
//STRIP001                      if( SVSTREAM_OK != rStg->GetError() )
//STRIP001                      {
//STRIP001                          rStg->Remove( sStrmName );
//STRIP001                          rStg->Commit();
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 SvxAutocorrWordList* SvxAutoCorrectLanguageLists::LoadAutocorrWordList()
//STRIP001 {
//STRIP001  if( pAutocorr_List )
//STRIP001      pAutocorr_List->DeleteAndDestroy( 0, pAutocorr_List->Count() );
//STRIP001  else
//STRIP001      pAutocorr_List = new SvxAutocorrWordList( 16, 16 );
//STRIP001
//STRIP001  SfxMedium aMedium( sShareAutoCorrFile,
//STRIP001                      STREAM_READ | STREAM_SHARE_DENYNONE, TRUE );
//STRIP001  SvStorageRef xStg = aMedium.GetStorage();
//STRIP001
//STRIP001  SvStringsDtor aRemoveArr;
//STRIP001  String aWordListName( pImplAutocorr_ListStr, RTL_TEXTENCODING_MS_1252 );
//STRIP001  String aXMLWordListName( pXMLImplAutocorr_ListStr, RTL_TEXTENCODING_MS_1252 );
//STRIP001  if( xStg.Is() && xStg->IsStream( aWordListName ) )
//STRIP001  {
//STRIP001      SvStorageStreamRef xStrm = xStg->OpenStream( aWordListName,
//STRIP001          ( STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE ) );
//STRIP001      if( SVSTREAM_OK != xStrm->GetError())
//STRIP001      {
//STRIP001          xStrm.Clear();
//STRIP001          xStg.Clear();
//STRIP001          RemoveStream_Imp( aWordListName );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          xStrm->SetBufferSize( 8192 );
//STRIP001
//STRIP001 //!!!!!!!!!!!!!
//STRIP001          // JP 10.10.96: AutocorrDatei vom Writer hat in einer alten
//STRIP001          //              Version keine CharSet Information sondern
//STRIP001          //              beginnt sofort mit einem String.
//STRIP001          //              Diese Dateien koennen wir ERSTMAL nicht
//STRIP001          //              verarbeiten.
//STRIP001 //!!!!!!!!!!!!!
//STRIP001          String sShort, sLong;
//STRIP001          xStrm->ReadByteString( sShort, RTL_TEXTENCODING_MS_1252 );
//STRIP001          if( !sShort.Len() )
//STRIP001          {
//STRIP001              // neuer Stream (mit Header)
//STRIP001              ULONG nOld = xStrm->Tell();
//STRIP001
//STRIP001              BYTE cLen, cSet;
//STRIP001              USHORT nVersion;
//STRIP001              *xStrm >> cLen >> nVersion >> cSet;
//STRIP001
//STRIP001              SvStorageInfoList* pInfoList = 0;
//STRIP001              if( WORDLIST_VERSION_358 > nVersion )
//STRIP001              {
//STRIP001                  pInfoList = new SvStorageInfoList;
//STRIP001                  xStg->FillInfoList( pInfoList );
//STRIP001              }
//STRIP001
//STRIP001              ULONG nNew = xStrm->Tell();
//STRIP001              nOld += cLen;
//STRIP001              if( nOld != nNew )
//STRIP001                  xStrm->Seek( nOld );
//STRIP001
//STRIP001              TransliterationWrapper& rCmp = GetIgnoreTranslWrapper();
//STRIP001
//STRIP001              // dann lese mal alle Ersetzungen:
//STRIP001              while( TRUE )
//STRIP001              {
//STRIP001                  xStrm->ReadByteString( sShort, cSet ).
//STRIP001                         ReadByteString( sLong, cSet );
//STRIP001                  if( xStrm->IsEof() ||  SVSTREAM_OK != xStrm->GetError() )
//STRIP001                      break;
//STRIP001
//STRIP001                  BOOL bOnlyTxt = !rCmp.isEqual( sShort, sLong );
//STRIP001                  if( !bOnlyTxt )
//STRIP001                  {
//STRIP001                      String sLongSave( sLong );
//STRIP001                      if( !rAutoCorrect.GetLongText( xStg, sShort, sLong ) &&
//STRIP001                          sLongSave.Len() )
//STRIP001                      {
//STRIP001                          sLong = sLongSave;
//STRIP001                          bOnlyTxt = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  SvxAutocorrWordPtr pNew = new SvxAutocorrWord(
//STRIP001                                              sShort, sLong, bOnlyTxt );
//STRIP001
//STRIP001                  if( !pAutocorr_List->Insert( pNew ) )
//STRIP001                      delete pNew;
//STRIP001
//STRIP001                  if( pInfoList )
//STRIP001                  {
//STRIP001                      // dann ggfs aus den alten Storages die
//STRIP001                      // ueberfluessigen Streams entfernen
//STRIP001                      EncryptBlockName_Imp( sShort );
//STRIP001                      const SvStorageInfo* pInfo = pInfoList->Get( sShort );
//STRIP001                      if( pInfo && ( pInfo->IsStream() ||
//STRIP001                          (bOnlyTxt && pInfo->IsStorage() ) ))
//STRIP001                      {
//STRIP001                          String* pNew = new String( sShort );
//STRIP001                          aRemoveArr.Insert( pNew, aRemoveArr.Count() );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if( pInfoList )
//STRIP001                  delete pInfoList;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      if( aRemoveArr.Count() && sShareAutoCorrFile == sUserAutoCorrFile )
//STRIP001      {
//STRIP001          xStrm.Clear();
//STRIP001          xStg.Clear();
//STRIP001          xStg = new SvStorage( sShareAutoCorrFile,
//STRIP001                              STREAM_STD_READWRITE, STORAGE_TRANSACTED );
//STRIP001
//STRIP001          if( xStg.Is() && SVSTREAM_OK == xStg->GetError() )
//STRIP001          {
//STRIP001              String* pStr;
//STRIP001              for( USHORT n = aRemoveArr.Count(); n; )
//STRIP001                  if( xStg->IsContained( *( pStr = aRemoveArr[ --n ] ) ) )
//STRIP001                      xStg->Remove( *pStr  );
//STRIP001
//STRIP001              // die neue Liste mit der neuen Versionsnummer speichern
//STRIP001              MakeBlocklist_Imp( *xStg );
//STRIP001              xStg->Commit();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Zeitstempel noch setzen
//STRIP001      FStatHelper::GetModifiedDateTimeOfFile( sShareAutoCorrFile,
//STRIP001                                      &aModifiedDate, &aModifiedTime );
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001  else if( xStg.Is() && xStg->IsStream( aXMLWordListName ) )
//STRIP001  {
//STRIP001      SvStorageStreamRef xStrm = xStg->OpenStream( aXMLWordListName,
//STRIP001          ( STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE ) );
//STRIP001      if( SVSTREAM_OK != xStrm->GetError())
//STRIP001      {
//STRIP001          xStrm.Clear();
//STRIP001          xStg.Clear();
//STRIP001          RemoveStream_Imp( aWordListName );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          Reference< lang::XMultiServiceFactory > xServiceFactory =
//STRIP001              ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001          DBG_ASSERT( xServiceFactory.is(),
//STRIP001              "XMLReader::Read: got no service manager" );
//STRIP001          if( !xServiceFactory.is() )
//STRIP001          {
//STRIP001              // Throw an exception ?
//STRIP001          }
//STRIP001
//STRIP001          xml::sax::InputSource aParserInput;
//STRIP001          aParserInput.sSystemId = aXMLWordListName;
//STRIP001
//STRIP001          xStrm->Seek( 0L );
//STRIP001          xStrm->SetBufferSize( 8 * 1024 );
//STRIP001          aParserInput.aInputStream = new utl::OInputStreamWrapper( *xStrm );
//STRIP001
//STRIP001          // get parser
//STRIP001          Reference< XInterface > xXMLParser = xServiceFactory->createInstance(
//STRIP001              OUString::createFromAscii("com.sun.star.xml.sax.Parser") );
//STRIP001          DBG_ASSERT( xXMLParser.is(),
//STRIP001              "XMLReader::Read: com.sun.star.xml.sax.Parser service missing" );
//STRIP001          if( !xXMLParser.is() )
//STRIP001          {
//STRIP001              // Maybe throw an exception?
//STRIP001          }
//STRIP001
//STRIP001          // get filter
//STRIP001          // #110680#
//STRIP001          // Reference< xml::sax::XDocumentHandler > xFilter = new SvXMLAutoCorrectImport( pAutocorr_List, rAutoCorrect, xStg );
//STRIP001          Reference< xml::sax::XDocumentHandler > xFilter = new SvXMLAutoCorrectImport( xServiceFactory, pAutocorr_List, rAutoCorrect, xStg );
//STRIP001
//STRIP001          // connect parser and filter
//STRIP001          Reference< xml::sax::XParser > xParser( xXMLParser, UNO_QUERY );
//STRIP001          xParser->setDocumentHandler( xFilter );
//STRIP001
//STRIP001          // parse
//STRIP001          try
//STRIP001          {
//STRIP001              xParser->parseStream( aParserInput );
//STRIP001          }
//STRIP001          catch( xml::sax::SAXParseException&  )
//STRIP001          {
//STRIP001              // re throw ?
//STRIP001          }
//STRIP001          catch( xml::sax::SAXException&  )
//STRIP001          {
//STRIP001              // re throw ?
//STRIP001          }
//STRIP001          catch( io::IOException& )
//STRIP001          {
//STRIP001              // re throw ?
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      if( aRemoveArr.Count() && sShareAutoCorrFile == sUserAutoCorrFile )
//STRIP001      {
//STRIP001          xStrm.Clear();
//STRIP001          xStg.Clear();
//STRIP001          xStg = new SvStorage( sShareAutoCorrFile,
//STRIP001                              STREAM_STD_READWRITE, STORAGE_TRANSACTED );
//STRIP001
//STRIP001          if( xStg.Is() && SVSTREAM_OK == xStg->GetError() )
//STRIP001          {
//STRIP001              String* pStr;
//STRIP001              for( USHORT n = aRemoveArr.Count(); n; )
//STRIP001                  if( xStg->IsContained( *( pStr = aRemoveArr[ --n ] ) ) )
//STRIP001                      xStg->Remove( *pStr  );
//STRIP001
//STRIP001              // die neue Liste mit der neuen Versionsnummer speichern
//STRIP001              MakeBlocklist_Imp( *xStg );
//STRIP001              xStg->Commit();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Zeitstempel noch setzen
//STRIP001      FStatHelper::GetModifiedDateTimeOfFile( sShareAutoCorrFile,
//STRIP001                                      &aModifiedDate, &aModifiedTime );
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001  return pAutocorr_List;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/

//STRIP001 void SvxAutoCorrectLanguageLists::SetAutocorrWordList( SvxAutocorrWordList* pList )
//STRIP001 {
//STRIP001  if( pAutocorr_List && pList != pAutocorr_List )
//STRIP001      delete pAutocorr_List;
//STRIP001  pAutocorr_List = pList;
//STRIP001  if( !pAutocorr_List )
//STRIP001  {
//STRIP001      DBG_ASSERT( !this, "keine gueltige Liste" );
//STRIP001      pAutocorr_List = new SvxAutocorrWordList( 16, 16 );
//STRIP001  }
//STRIP001  nFlags |= ChgWordLstLoad;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 const SvxAutocorrWordList* SvxAutoCorrectLanguageLists::GetAutocorrWordList()
//STRIP001 {
//STRIP001  if( !( ChgWordLstLoad & nFlags ) || IsFileChanged_Imp() )
//STRIP001      SetAutocorrWordList( LoadAutocorrWordList() );
//STRIP001  return pAutocorr_List;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 const SvStringsISortDtor* SvxAutoCorrectLanguageLists::GetCplSttExceptList()
//STRIP001 {
//STRIP001  if( !( CplSttLstLoad & nFlags ) || IsFileChanged_Imp() )
//STRIP001      SetCplSttExceptList( LoadCplSttExceptList() );
//STRIP001  return pCplStt_ExcptLst;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrectLanguageLists::AddToCplSttExceptList(const String& rNew)
//STRIP001 {
//STRIP001  String* pNew = new String( rNew );
//STRIP001  if( rNew.Len() && LoadCplSttExceptList()->Insert( pNew ) )
//STRIP001  {
//STRIP001      MakeUserStorage_Impl();
//STRIP001      SfxMedium aMedium( sUserAutoCorrFile, STREAM_READWRITE, TRUE );
//STRIP001
//STRIP001      // #i5746#
//STRIP001      // Use GetOutputStorage(...) instead of GetStorage() here to
//STRIP001      // create new files if necessary
//STRIP001      SvStorageRef xStg = aMedium.GetOutputStorage(sal_True);
//STRIP001
//STRIP001      SaveExceptList_Imp( *pCplStt_ExcptLst, pXMLImplCplStt_ExcptLstStr, xStg );
//STRIP001
//STRIP001      xStg = 0;
//STRIP001      aMedium.Commit();
//STRIP001      // Zeitstempel noch setzen
//STRIP001      FStatHelper::GetModifiedDateTimeOfFile( sUserAutoCorrFile,
//STRIP001                                          &aModifiedDate, &aModifiedTime );
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001  else
//STRIP001      delete pNew, pNew = 0;
//STRIP001  return 0 != pNew;
//STRIP001 }
/* -----------------18.11.98 15:20-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrectLanguageLists::AddToWrdSttExceptList(const String& rNew)
//STRIP001 {
//STRIP001  String* pNew = new String( rNew );
//STRIP001  if( rNew.Len() && LoadWrdSttExceptList()->Insert( pNew ) )
//STRIP001  {
//STRIP001      MakeUserStorage_Impl();
//STRIP001      SfxMedium aMedium( sUserAutoCorrFile, STREAM_READWRITE, TRUE );
//STRIP001
//STRIP001      // #i5746#
//STRIP001      // Use GetOutputStorage(...) instead of GetStorage() here to
//STRIP001      // create new files if necessary
//STRIP001      SvStorageRef xStg = aMedium.GetOutputStorage(sal_True);
//STRIP001
//STRIP001      SaveExceptList_Imp( *pWrdStt_ExcptLst, pXMLImplWrdStt_ExcptLstStr, xStg );
//STRIP001
//STRIP001      xStg = 0;
//STRIP001      aMedium.Commit();
//STRIP001      // Zeitstempel noch setzen
//STRIP001      FStatHelper::GetModifiedDateTimeOfFile( sUserAutoCorrFile,
//STRIP001                                          &aModifiedDate, &aModifiedTime );
//STRIP001      aLastCheckTime = Time();
//STRIP001  }
//STRIP001  else
//STRIP001      delete pNew, pNew = 0;
//STRIP001  return 0 != pNew;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 SvStringsISortDtor* SvxAutoCorrectLanguageLists::LoadCplSttExceptList()
//STRIP001 {
//STRIP001  SfxMedium aMedium( sShareAutoCorrFile,
//STRIP001                          STREAM_READ | STREAM_SHARE_DENYNONE, TRUE );
//STRIP001  SvStorageRef xStg = aMedium.GetStorage();
//STRIP001  String sTemp ( RTL_CONSTASCII_USTRINGPARAM ( pXMLImplCplStt_ExcptLstStr ) );
//STRIP001  if( xStg.Is() && xStg->IsContained( sTemp ) )
//STRIP001      LoadXMLExceptList_Imp( pCplStt_ExcptLst, pXMLImplCplStt_ExcptLstStr, xStg );
//STRIP001  else
//STRIP001      LoadExceptList_Imp( pCplStt_ExcptLst, pImplCplStt_ExcptLstStr, xStg );
//STRIP001
//STRIP001  return pCplStt_ExcptLst;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::SaveCplSttExceptList()
//STRIP001 {
//STRIP001  MakeUserStorage_Impl();
//STRIP001  SfxMedium aMedium( sUserAutoCorrFile, STREAM_READWRITE, TRUE );
//STRIP001
//STRIP001  // #i5746#
//STRIP001  // Use GetOutputStorage(...) instead of GetStorage() here to
//STRIP001  // create new files if necessary
//STRIP001  SvStorageRef xStg = aMedium.GetOutputStorage(sal_True);
//STRIP001
//STRIP001  SaveExceptList_Imp( *pCplStt_ExcptLst, pXMLImplCplStt_ExcptLstStr, xStg );
//STRIP001
//STRIP001  xStg = 0;
//STRIP001  aMedium.Commit();
//STRIP001  // Zeitstempel noch setzen
//STRIP001  FStatHelper::GetModifiedDateTimeOfFile( sUserAutoCorrFile,
//STRIP001                                          &aModifiedDate, &aModifiedTime );
//STRIP001  aLastCheckTime = Time();
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::SetCplSttExceptList( SvStringsISortDtor* pList )
//STRIP001 {
//STRIP001  if( pCplStt_ExcptLst && pList != pCplStt_ExcptLst )
//STRIP001      delete pCplStt_ExcptLst;
//STRIP001
//STRIP001  pCplStt_ExcptLst = pList;
//STRIP001  if( !pCplStt_ExcptLst )
//STRIP001  {
//STRIP001      DBG_ASSERT( !this, "keine gueltige Liste" );
//STRIP001      pCplStt_ExcptLst = new SvStringsISortDtor( 16, 16 );
//STRIP001  }
//STRIP001  nFlags |= CplSttLstLoad;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 SvStringsISortDtor* SvxAutoCorrectLanguageLists::LoadWrdSttExceptList()
//STRIP001 {
//STRIP001  SfxMedium aMedium( sShareAutoCorrFile,
//STRIP001                          STREAM_READ | STREAM_SHARE_DENYNONE, TRUE );
//STRIP001  SvStorageRef xStg = aMedium.GetStorage();
//STRIP001  String sTemp ( RTL_CONSTASCII_USTRINGPARAM ( pXMLImplWrdStt_ExcptLstStr ) );
//STRIP001  if( xStg.Is() && xStg->IsContained( sTemp ) )
//STRIP001      LoadXMLExceptList_Imp( pWrdStt_ExcptLst, pXMLImplWrdStt_ExcptLstStr, xStg );
//STRIP001  else
//STRIP001      LoadExceptList_Imp( pWrdStt_ExcptLst, pImplWrdStt_ExcptLstStr, xStg );
//STRIP001  return pWrdStt_ExcptLst;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::SaveWrdSttExceptList()
//STRIP001 {
//STRIP001  MakeUserStorage_Impl();
//STRIP001  SfxMedium aMedium( sUserAutoCorrFile, STREAM_READWRITE, TRUE );
//STRIP001
//STRIP001  // #i5746#
//STRIP001  // Use GetOutputStorage(...) instead of GetStorage() here to
//STRIP001  // create new files if necessary
//STRIP001  SvStorageRef xStg = aMedium.GetOutputStorage(sal_True);
//STRIP001
//STRIP001  SaveExceptList_Imp( *pWrdStt_ExcptLst, pXMLImplWrdStt_ExcptLstStr, xStg );
//STRIP001
//STRIP001  xStg = 0;
//STRIP001  aMedium.Commit();
//STRIP001  // Zeitstempel noch setzen
//STRIP001  FStatHelper::GetModifiedDateTimeOfFile( sUserAutoCorrFile,
//STRIP001                                          &aModifiedDate, &aModifiedTime );
//STRIP001  aLastCheckTime = Time();
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::SetWrdSttExceptList( SvStringsISortDtor* pList )
//STRIP001 {
//STRIP001  if( pWrdStt_ExcptLst && pList != pWrdStt_ExcptLst )
//STRIP001      delete pWrdStt_ExcptLst;
//STRIP001  pWrdStt_ExcptLst = pList;
//STRIP001  if( !pWrdStt_ExcptLst )
//STRIP001  {
//STRIP001      DBG_ASSERT( !this, "keine gueltige Liste" );
//STRIP001      pWrdStt_ExcptLst = new SvStringsISortDtor( 16, 16 );
//STRIP001  }
//STRIP001  nFlags |= WrdSttLstLoad;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 const SvStringsISortDtor* SvxAutoCorrectLanguageLists::GetWrdSttExceptList()
//STRIP001 {
//STRIP001  if( !( WrdSttLstLoad & nFlags ) || IsFileChanged_Imp() )
//STRIP001      SetWrdSttExceptList( LoadWrdSttExceptList() );
//STRIP001  return pWrdStt_ExcptLst;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 void SvxAutoCorrectLanguageLists::RemoveStream_Imp( const String& rName )
//STRIP001 {
//STRIP001  if( sShareAutoCorrFile != sUserAutoCorrFile )
//STRIP001  {
//STRIP001      SfxMedium aMedium( sUserAutoCorrFile, STREAM_STD_READWRITE, TRUE );
//STRIP001      SvStorageRef xStg = aMedium.GetStorage();
//STRIP001
//STRIP001      if( xStg.Is() && SVSTREAM_OK == xStg->GetError() &&
//STRIP001          xStg->IsStream( rName ) )
//STRIP001      {
//STRIP001          xStg->Remove( rName );
//STRIP001          xStg->Commit();
//STRIP001
//STRIP001          xStg = 0;
//STRIP001          aMedium.Commit();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SvxAutoCorrectLanguageLists::MakeUserStorage_Impl()
//STRIP001 {
//STRIP001  // The conversion needs to happen if the file is already in the user
//STRIP001  // directory and is in the old format. Additionally it needs to
//STRIP001  // happen when the file is being copied from share to user.
//STRIP001
//STRIP001  sal_Bool bError = sal_False, bConvert = sal_False, bCopy = sal_False;
//STRIP001  INetURLObject aDest;
//STRIP001  INetURLObject aSource;
//STRIP001
//STRIP001 //   String sDestPath = sUserAutoCorrFile.Copy ( 0, sUserAutoCorrFile.Len()-3);
//STRIP001 //   sDestPath.AppendAscii ("bak");
//STRIP001
//STRIP001
//STRIP001  if (sUserAutoCorrFile != sShareAutoCorrFile )
//STRIP001  {
//STRIP001      aSource = INetURLObject ( sShareAutoCorrFile ); //aSource.setFSysPath ( sShareAutoCorrFile, INetURLObject::FSYS_DETECT );
//STRIP001      aDest = INetURLObject ( sUserAutoCorrFile );
//STRIP001      if ( SotStorage::IsOLEStorage ( sShareAutoCorrFile ) )
//STRIP001      {
//STRIP001          aDest.SetExtension ( String::CreateFromAscii ( "bak" ) );
//STRIP001          bConvert = sal_True;
//STRIP001      }
//STRIP001      bCopy = sal_True;
//STRIP001  }
//STRIP001  else if ( SotStorage::IsOLEStorage ( sUserAutoCorrFile ) )
//STRIP001  {
//STRIP001      aSource = INetURLObject ( sUserAutoCorrFile );
//STRIP001      aDest = INetURLObject ( sUserAutoCorrFile );
//STRIP001      aDest.SetExtension ( String::CreateFromAscii ( "bak" ) );
//STRIP001      bCopy = bConvert = sal_True;
//STRIP001  }
//STRIP001  if (bCopy)
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          String sMain(aDest.GetMainURL( INetURLObject::DECODE_TO_IURI ));
//STRIP001          sal_Unicode cSlash = '/';
//STRIP001          xub_StrLen nSlashPos = sMain.SearchBackward(cSlash);
//STRIP001          sMain.Erase(nSlashPos);
//STRIP001          ::ucb::Content aNewContent( sMain, Reference< XCommandEnvironment > ());
//STRIP001          Any aAny;
//STRIP001          TransferInfo aInfo;
//STRIP001          aInfo.NameClash = NameClash::OVERWRITE;
//STRIP001          aInfo.NewTitle  = aDest.GetName();
//STRIP001          aInfo.SourceURL = aSource.GetMainURL( INetURLObject::DECODE_TO_IURI );
//STRIP001          aInfo.MoveData  = FALSE;
//STRIP001          aAny <<= aInfo;
//STRIP001          aNewContent.executeCommand( OUString ( RTL_CONSTASCII_USTRINGPARAM( "transfer" ) ), aAny);
//STRIP001      }
//STRIP001      catch (...)
//STRIP001      {
//STRIP001          bError = sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001  if (bConvert && !bError)
//STRIP001  {
//STRIP001      SfxMedium aSrcMedium( aDest.GetMainURL( INetURLObject::DECODE_TO_IURI ), STREAM_STD_READ, TRUE );
//STRIP001      SvStorageRef xSrcStg = aSrcMedium.GetStorage();
//STRIP001      SfxMedium aDstMedium( sUserAutoCorrFile, STREAM_STD_WRITE, TRUE );
//STRIP001      // Copy it to a UCBStorage
//STRIP001      SvStorageRef xDstStg = aDstMedium.GetOutputStorage( TRUE );
//STRIP001
//STRIP001      if( xSrcStg.Is() && xDstStg.Is() )
//STRIP001      {
//STRIP001          String sWord        ( RTL_CONSTASCII_USTRINGPARAM ( pImplWrdStt_ExcptLstStr ) );
//STRIP001          String sSentence    ( RTL_CONSTASCII_USTRINGPARAM ( pImplCplStt_ExcptLstStr ) );
//STRIP001          String sXMLWord     ( RTL_CONSTASCII_USTRINGPARAM ( pXMLImplWrdStt_ExcptLstStr ) );
//STRIP001          String sXMLSentence ( RTL_CONSTASCII_USTRINGPARAM ( pXMLImplCplStt_ExcptLstStr ) );
//STRIP001          SvStringsISortDtor  *pTmpWordList = NULL;
//STRIP001
//STRIP001          if (xSrcStg->IsContained( sWord ) )
//STRIP001              LoadExceptList_Imp( pTmpWordList, pImplWrdStt_ExcptLstStr, xSrcStg );
//STRIP001          else if (xSrcStg->IsContained( sXMLWord ) )
//STRIP001              LoadXMLExceptList_Imp( pTmpWordList, pXMLImplWrdStt_ExcptLstStr, xSrcStg );
//STRIP001
//STRIP001          if (pTmpWordList)
//STRIP001          {
//STRIP001              SaveExceptList_Imp( *pTmpWordList, pXMLImplWrdStt_ExcptLstStr, xDstStg, TRUE );
//STRIP001              pTmpWordList->DeleteAndDestroy( 0, pTmpWordList->Count() );
//STRIP001              pTmpWordList = NULL;
//STRIP001          }
//STRIP001
//STRIP001
//STRIP001          if (xSrcStg->IsContained( sSentence ) )
//STRIP001              LoadExceptList_Imp( pTmpWordList, pImplCplStt_ExcptLstStr, xSrcStg );
//STRIP001          else if (xSrcStg->IsContained( sXMLSentence ) )
//STRIP001              LoadXMLExceptList_Imp( pTmpWordList, pXMLImplCplStt_ExcptLstStr, xSrcStg );
//STRIP001
//STRIP001          if (pTmpWordList)
//STRIP001             {
//STRIP001              SaveExceptList_Imp( *pTmpWordList, pXMLImplCplStt_ExcptLstStr, xDstStg, TRUE );
//STRIP001              pTmpWordList->DeleteAndDestroy( 0, pTmpWordList->Count() );
//STRIP001             }
//STRIP001
//STRIP001          GetAutocorrWordList();
//STRIP001          MakeBlocklist_Imp( *xDstStg );
//STRIP001          // xDstStg is committed in MakeBlocklist_Imp
//STRIP001          /*xSrcStg->CopyTo( &xDstStg );*/
//STRIP001          sShareAutoCorrFile = sUserAutoCorrFile;
//STRIP001          xDstStg = 0;
//STRIP001          aDstMedium.Commit();
//STRIP001          try
//STRIP001          {
//STRIP001              ::ucb::Content aContent ( aDest.GetMainURL( INetURLObject::DECODE_TO_IURI ), Reference < XCommandEnvironment > ());
//STRIP001              aContent.executeCommand ( OUString ( RTL_CONSTASCII_USTRINGPARAM ( "delete" ) ), makeAny ( sal_Bool (sal_True ) ) );
//STRIP001          }
//STRIP001          catch (...)
//STRIP001          {
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if( bCopy && !bError )
//STRIP001      sShareAutoCorrFile = sUserAutoCorrFile;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrectLanguageLists::MakeBlocklist_Imp( SvStorage& rStg )
//STRIP001 {
//STRIP001  String sStrmName( pXMLImplAutocorr_ListStr, RTL_TEXTENCODING_MS_1252 );
//STRIP001  BOOL bRet = TRUE, bRemove = !pAutocorr_List || !pAutocorr_List->Count();
//STRIP001  if( !bRemove )
//STRIP001  {
//STRIP001      /*
//STRIP001      if ( rStg.IsContained( sStrmName) )
//STRIP001      {
//STRIP001          rStg.Remove ( sStrmName );
//STRIP001          rStg.Commit();
//STRIP001      }
//STRIP001      */
//STRIP001      SvStorageStreamRef refList = rStg.OpenStream( sStrmName,
//STRIP001                  ( STREAM_READ | STREAM_WRITE | STREAM_SHARE_DENYWRITE ) );
//STRIP001      if( refList.Is() )
//STRIP001      {
//STRIP001          refList->SetSize( 0 );
//STRIP001          refList->SetBufferSize( 8192 );
//STRIP001          String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
//STRIP001          OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
//STRIP001          uno::Any aAny;
//STRIP001          aAny <<= aMime;
//STRIP001          refList->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001          Reference< lang::XMultiServiceFactory > xServiceFactory =
//STRIP001              ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001          DBG_ASSERT( xServiceFactory.is(),
//STRIP001                      "XMLReader::Read: got no service manager" );
//STRIP001          if( !xServiceFactory.is() )
//STRIP001          {
//STRIP001              // Throw an exception ?
//STRIP001          }
//STRIP001
//STRIP001              Reference < XInterface > xWriter (xServiceFactory->createInstance(
//STRIP001                   OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer"))));
//STRIP001              DBG_ASSERT(xWriter.is(),"com.sun.star.xml.sax.Writer service missing");
//STRIP001          Reference < io::XOutputStream> xOut = new utl::OOutputStreamWrapper( *refList );
//STRIP001              uno::Reference<io::XActiveDataSource> xSrc(xWriter, uno::UNO_QUERY);
//STRIP001              xSrc->setOutputStream(xOut);
//STRIP001
//STRIP001              uno::Reference<xml::sax::XDocumentHandler> xHandler(xWriter, uno::UNO_QUERY);
//STRIP001
//STRIP001          // #110680#
//STRIP001              // SvXMLAutoCorrectExport aExp(pAutocorr_List, sStrmName, xHandler);
//STRIP001              SvXMLAutoCorrectExport aExp( xServiceFactory, pAutocorr_List, sStrmName, xHandler );
//STRIP001          aExp.exportDoc( XML_BLOCK_LIST );
//STRIP001
//STRIP001          refList->Commit();
//STRIP001          bRet = SVSTREAM_OK == refList->GetError();
//STRIP001          if( bRet )
//STRIP001          {
//STRIP001              refList.Clear();
//STRIP001              rStg.Commit();
//STRIP001              if( SVSTREAM_OK != rStg.GetError() )
//STRIP001              {
//STRIP001                  bRemove = TRUE;
//STRIP001                  bRet = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          /*
//STRIP001          refList->SetSize( 0 );
//STRIP001          refList->SetBufferSize( 8192 );
//STRIP001          rtl_TextEncoding eEncoding = gsl_getSystemTextEncoding();
//STRIP001
//STRIP001          String aDummy;              // Erkennungszeichen fuer neue Streams
//STRIP001          refList->WriteByteString( aDummy, RTL_TEXTENCODING_MS_1252 )
//STRIP001                   << (BYTE)  4       // Laenge des Headers (ohne den Leerstring)
//STRIP001                   << (USHORT)WORDLIST_VERSION_358    // Version des Streams
//STRIP001                   << (BYTE)eEncoding;                // der Zeichensatz
//STRIP001
//STRIP001          for( USHORT i = 0; i < pAutocorr_List->Count() &&
//STRIP001                              SVSTREAM_OK == refList->GetError(); ++i )
//STRIP001          {
//STRIP001              SvxAutocorrWord* p = pAutocorr_List->GetObject( i );
//STRIP001              refList->WriteByteString( p->GetShort(), eEncoding ).
//STRIP001                      WriteByteString(  p->IsTextOnly()
//STRIP001                                          ? p->GetLong()
//STRIP001                                          : p->GetShort(), eEncoding );
//STRIP001          }
//STRIP001          refList->Commit();
//STRIP001          bRet = SVSTREAM_OK == refList->GetError();
//STRIP001          if( bRet )
//STRIP001          {
//STRIP001              refList.Clear();
//STRIP001              rStg.Commit();
//STRIP001              if( SVSTREAM_OK != rStg.GetError() )
//STRIP001              {
//STRIP001                  bRemove = TRUE;
//STRIP001                  bRet = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001          */
//STRIP001      }
//STRIP001      else
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( bRemove )
//STRIP001  {
//STRIP001      rStg.Remove( sStrmName );
//STRIP001      rStg.Commit();
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SvxAutoCorrectLanguageLists::PutText( const String& rShort,
//STRIP001                                         const String& rLong )
//STRIP001 {
//STRIP001  // erstmal akt. Liste besorgen!
//STRIP001  GetAutocorrWordList();
//STRIP001
//STRIP001  MakeUserStorage_Impl();
//STRIP001
//STRIP001  SfxMedium aMedium( sUserAutoCorrFile, STREAM_STD_READWRITE, TRUE );
//STRIP001  SvStorageRef xStg = aMedium.GetOutputStorage( TRUE );
//STRIP001  BOOL bRet = xStg.Is() && SVSTREAM_OK == xStg->GetError();
//STRIP001
//STRIP001 /*   if( bRet )
//STRIP001  {
//STRIP001      // PutText( *xStg, rShort );
//STRIP001  }
//STRIP001 */
//STRIP001  // die Wortliste aktualisieren
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      SvxAutocorrWord* pNew = new SvxAutocorrWord( rShort, rLong, TRUE );
//STRIP001      if( pAutocorr_List->Seek_Entry( pNew, &nPos ) )
//STRIP001      {
//STRIP001          if( !(*pAutocorr_List)[ nPos ]->IsTextOnly() )
//STRIP001          {
//STRIP001              // dann ist der Storage noch zu entfernen
//STRIP001              String sStgNm( rShort );
//STRIP001              if (xStg->IsOLEStorage())
//STRIP001                  EncryptBlockName_Imp( sStgNm );
//STRIP001              else
//STRIP001                  GeneratePackageName ( rShort, sStgNm);
//STRIP001
//STRIP001              if( xStg->IsContained( sStgNm ) )
//STRIP001                  xStg->Remove( sStgNm );
//STRIP001          }
//STRIP001          pAutocorr_List->DeleteAndDestroy( nPos );
//STRIP001      }
//STRIP001
//STRIP001      if( pAutocorr_List->Insert( pNew ) )
//STRIP001      {
//STRIP001          bRet = MakeBlocklist_Imp( *xStg );
//STRIP001          xStg = 0;
//STRIP001          aMedium.Commit();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          delete pNew;
//STRIP001          bRet = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
    //  - Text mit Attributierung (kann nur der SWG - SWG-Format!)
//STRIP001 BOOL SvxAutoCorrectLanguageLists::PutText( const String& rShort,
//STRIP001                                      SfxObjectShell& rShell )
//STRIP001 {
//STRIP001  // erstmal akt. Liste besorgen!
//STRIP001  GetAutocorrWordList();
//STRIP001
//STRIP001  MakeUserStorage_Impl();
//STRIP001
//STRIP001  String sLong;
//STRIP001  SfxMedium aMedium( sUserAutoCorrFile, STREAM_STD_READWRITE, TRUE );
//STRIP001  SvStorageRef xStg = aMedium.GetOutputStorage( TRUE );
//STRIP001  BOOL bRet = xStg.Is() && SVSTREAM_OK == xStg->GetError();
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001 //       String aName( rShort );
//STRIP001 //       EncryptBlockName_Imp( aName );
//STRIP001 //       bRet = PutText( *xStg, aName, rShell, sLong );
//STRIP001      bRet = rAutoCorrect.PutText( *xStg, rShort, rShell, sLong );
//STRIP001  }
//STRIP001
//STRIP001  // die Wortliste aktualisieren
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SvxAutocorrWord* pNew = new SvxAutocorrWord( rShort, sLong, FALSE );
//STRIP001      if( pAutocorr_List->Insert( pNew ) )
//STRIP001      {
//STRIP001          MakeBlocklist_Imp( *xStg );
//STRIP001          xStg = 0;
//STRIP001          aMedium.Commit();
//STRIP001      }
//STRIP001      else
//STRIP001          delete pNew;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/* -----------------18.11.98 11:26-------------------
 *
 * --------------------------------------------------*/
    //  - loesche einen Eintrag
//STRIP001 BOOL SvxAutoCorrectLanguageLists::DeleteText( const String& rShort )
//STRIP001 {
//STRIP001  // erstmal akt. Liste besorgen!
//STRIP001  GetAutocorrWordList();
//STRIP001
//STRIP001  MakeUserStorage_Impl();
//STRIP001
//STRIP001  SfxMedium aMedium( sUserAutoCorrFile, STREAM_STD_READWRITE, TRUE );
//STRIP001  SvStorageRef xStg = aMedium.GetStorage();
//STRIP001  BOOL bRet = xStg.Is() && SVSTREAM_OK == xStg->GetError();
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      SvxAutocorrWord aTmp( rShort, rShort );
//STRIP001      if( pAutocorr_List->Seek_Entry( &aTmp, &nPos ) )
//STRIP001      {
//STRIP001          SvxAutocorrWord* pFnd = (*pAutocorr_List)[ nPos ];
//STRIP001          if( !pFnd->IsTextOnly() )
//STRIP001          {
//STRIP001              String aName( rShort );
//STRIP001              if (xStg->IsOLEStorage())
//STRIP001                  EncryptBlockName_Imp( aName );
//STRIP001              else
//STRIP001                  GeneratePackageName ( rShort, aName );
//STRIP001              if( xStg->IsContained( aName ) )
//STRIP001              {
//STRIP001                  xStg->Remove( aName );
//STRIP001                  bRet = xStg->Commit();
//STRIP001              }
//STRIP001
//STRIP001          }
//STRIP001          // die Wortliste aktualisieren
//STRIP001          pAutocorr_List->DeleteAndDestroy( nPos );
//STRIP001          MakeBlocklist_Imp( *xStg );
//STRIP001          xStg = 0;
//STRIP001          aMedium.Commit();
//STRIP001      }
//STRIP001      else
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
}
