/*************************************************************************
 *
 *  $RCSfile: sc_global.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:07:23 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
// auto strip #include <bf_svx/algitem.hxx>
// auto strip #include <bf_svx/brshitem.hxx>
#include <bf_svx/editobj.hxx>
#include <bf_svx/scripttypeitem.hxx>
// auto strip #include <bf_svx/srchitem.hxx>
#include <bf_svx/langitem.hxx>
// auto strip #include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/dispatch.hxx>
// auto strip #include <bf_sfx2/objsh.hxx>
// auto strip #include <bf_sfx2/viewfrm.hxx>
// auto strip #include <bf_sfx2/viewsh.hxx>
// auto strip #include <svtools/stritem.hxx>
// auto strip #include <svtools/zforlist.hxx>
#include <svtools/zformat.hxx>
#include <vcl/image.hxx>
#include <tools/rcid.h>
#include <vcl/virdev.hxx>
// auto strip #include <unotools/charclass.hxx>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif
// auto strip #ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
// auto strip #include <com/sun/star/lang/Locale.hpp>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_CALENDARWRAPPER_HXX
// auto strip #include <unotools/calendarwrapper.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_COLLATORWRAPPER_HXX
// auto strip #include <unotools/collatorwrapper.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_I18N_COLLATOROPTIONS_HPP_
// auto strip #include <com/sun/star/i18n/CollatorOptions.hpp>
// auto strip #endif
#ifndef _UNOTOOLS_INTLWRAPPER_HXX
#include <unotools/intlwrapper.hxx>
#endif
// auto strip #ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
// auto strip #include <svtools/syslocale.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
// auto strip #include <unotools/transliterationwrapper.hxx>
// auto strip #endif

// auto strip #include "global.hxx"
// auto strip #include "scresid.hxx"
#include "autoform.hxx"
// auto strip #include "document.hxx"
#include "patattr.hxx"
#include "addincol.hxx"
#include "adiasync.hxx"
#include "userlist.hxx"
#include "interpre.hxx"
#include "strload.hxx"
#include "docpool.hxx"
#include "unitconv.hxx"
#include "globstr.hrc"
#include "scfuncs.hrc"
#include "bf_sc.hrc"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

#ifndef _SFX_SRCHITEM_HXX
#include <bf_sfx2/srchitem.hxx>
#endif

namespace binfilter {
// -----------------------------------------------------------------------

#define CLIPST_AVAILABLE    0
#define CLIPST_CAPTURED     1
#define CLIPST_DELETE       2
#define CLIPST_DRAW         3

ScDocShellRef*  ScGlobal::pDrawClipDocShellRef = NULL;
SvxSearchItem*  ScGlobal::pSearchItem = NULL;
ScAutoFormat*   ScGlobal::pAutoFormat = NULL;
FuncCollection* ScGlobal::pFuncCollection = NULL;
ScUnoAddInCollection* ScGlobal::pAddInCollection = NULL;
ScUserList*     ScGlobal::pUserList = NULL;
String**        ScGlobal::ppRscString = NULL;
LanguageType    ScGlobal::eLnge = LANGUAGE_SYSTEM;
::com::sun::star::lang::Locale*     ScGlobal::pLocale = NULL;
SvtSysLocale*   ScGlobal::pSysLocale = NULL;
const CharClass*  ScGlobal::pCharClass = NULL;
const LocaleDataWrapper*  ScGlobal::pLocaleData = NULL;
CalendarWrapper* ScGlobal::pCalendar = NULL;
CollatorWrapper* ScGlobal::pCollator = NULL;
CollatorWrapper* ScGlobal::pCaseCollator = NULL;
::utl::TransliterationWrapper* ScGlobal::pTransliteration = NULL;
::utl::TransliterationWrapper* ScGlobal::pCaseTransliteration = NULL;
IntlWrapper*    ScGlobal::pScIntlWrapper = NULL;
sal_Unicode     ScGlobal::cListDelimiter = ',';
String*         ScGlobal::pEmptyString = NULL;
String*         ScGlobal::pStrClipDocName = NULL;

SvxBrushItem*   ScGlobal::pEmptyBrushItem = NULL;
SvxBrushItem*   ScGlobal::pButtonBrushItem = NULL;
SvxBrushItem*   ScGlobal::pEmbeddedBrushItem = NULL;
SvxBrushItem*   ScGlobal::pProtectedBrushItem = NULL;

ImageList*      ScGlobal::pOutlineBitmaps = NULL;
ImageList*      ScGlobal::pOutlineBitmapsHC = NULL;

ScFunctionList* ScGlobal::pStarCalcFunctionList = NULL;
ScFunctionMgr*  ScGlobal::pStarCalcFunctionMgr  = NULL;

ScUnitConverter* ScGlobal::pUnitConverter = NULL;
SvNumberFormatter* ScGlobal::pEnglishFormatter = NULL;

double          ScGlobal::nScreenPPTX           = 96.0;
double          ScGlobal::nScreenPPTY           = 96.0;

USHORT          ScGlobal::nDefFontHeight        = 240;
USHORT          ScGlobal::nStdRowHeight         = 257;

long            ScGlobal::nLastRowHeightExtra   = 0;
long            ScGlobal::nLastColWidthExtra    = STD_EXTRA_WIDTH;

static USHORT nPPTZoom = 0;     // ScreenZoom used to determine nScreenPPTX/Y


// ... oder so?

BOOL bOderSo;

class SfxViewShell;
SfxViewShell* pScActiveViewShell = NULL;            //! als Member !!!!!
USHORT nScClickMouseModifier = 0;                   //! dito
USHORT nScFillModeMouseModifier = 0;                //! dito

// Hack: ScGlobal::GetUserList() muss InitAppOptions in der UI aufrufen,
//       damit UserList aus Cfg geladen wird

void global_InitAppOptions();

// -----------------------------------------------------------------------

/*N*/ String ScTripel::GetText() const
/*N*/ {
/*N*/   String aString('(');
/*N*/   aString += String::CreateFromInt32( nCol );
/*N*/   aString += ',';
/*N*/   aString += String::CreateFromInt32( nRow );
/*N*/   aString += ',';
/*N*/   aString += String::CreateFromInt32( nTab );
/*N*/   aString += ')';
/*N*/   return aString;
/*N*/ }
/*N*/
/*N*/ String ScTripel::GetColRowString( BOOL bAbsolute ) const
/*N*/ {
/*N*/   String aString;
/*N*/   if (bAbsolute)
/*N*/       aString.Append( '$' );
/*N*/
/*N*/   if ( nCol < 26 )
/*N*/       aString.Append( (sal_Unicode) ( 'A' + nCol ) );
/*N*/   else
/*N*/   {
/*N*/       aString.Append( (sal_Unicode) ( 'A' + ( nCol / 26 ) - 1 ) );
/*N*/       aString.Append( (sal_Unicode) ( 'A' + ( nCol % 26 ) ) );
/*N*/   }
/*N*/
/*N*/   if ( bAbsolute )
/*N*/       aString.Append( '$' );
/*N*/
/*N*/   aString += String::CreateFromInt32(nRow+1);
/*N*/
/*N*/   return aString;
/*N*/ }

/*N*/ String ScRefTripel::GetRefString(ScDocument* pDoc, USHORT nActTab) const
/*N*/ {
/*N*/   if ( !pDoc )
/*N*/       return EMPTY_STRING;
/*N*/   if ( nTab+1 > pDoc->GetTableCount() )
/*N*/       return ScGlobal::GetRscString( STR_NOREF_STR );
/*N*/
/*N*/     String aString;
/*N*/     USHORT nFlags = SCA_VALID;
/*N*/     if ( nActTab != nTab )
/*N*/     {
/*N*/         nFlags |= SCA_TAB_3D;
/*N*/         if ( !bRelTab )
/*N*/             nFlags |= SCA_TAB_ABSOLUTE;
/*N*/     }
/*N*/     if ( !bRelCol )
/*N*/         nFlags |= SCA_COL_ABSOLUTE;
/*N*/     if ( !bRelRow )
/*N*/         nFlags |= SCA_ROW_ABSOLUTE;
/*N*/
/*N*/     ScAddress( nCol, nRow, nTab ).Format( aString, nFlags, pDoc );
/*N*/
/*N*/     return aString;
/*N*/ }


//========================================================================
//
//      statische Funktionen
//
//========================================================================

/*N*/ BOOL ScGlobal::HasAttrChanged( const SfxItemSet&  rNewAttrs,
/*N*/                              const SfxItemSet&  rOldAttrs,
/*N*/                              const USHORT       nWhich )
/*N*/ {
/*N*/   BOOL                bInvalidate = FALSE;
/*N*/   const SfxItemState  eNewState   = rNewAttrs.GetItemState( nWhich );
/*N*/   const SfxItemState  eOldState   = rOldAttrs.GetItemState( nWhich );
/*N*/
/*N*/   //----------------------------------------------------------
/*N*/
/*N*/   if ( eNewState == eOldState )
/*N*/   {
/*N*/       // beide Items gesetzt
/*N*/       // PoolItems, d.h. Pointer-Vergleich zulaessig
/*N*/       if ( SFX_ITEM_SET == eOldState )
/*N*/           bInvalidate = (&rNewAttrs.Get( nWhich ) != &rOldAttrs.Get( nWhich ));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // ein Default-Item dabei
/*N*/       // PoolItems, d.h. Item-Vergleich noetig
/*N*/
/*N*/       const SfxPoolItem& rOldItem = ( SFX_ITEM_SET == eOldState )
/*N*/                   ? rOldAttrs.Get( nWhich )
/*N*/                   : rOldAttrs.GetPool()->GetDefaultItem( nWhich );
/*N*/
/*N*/       const SfxPoolItem& rNewItem = ( SFX_ITEM_SET == eNewState )
/*N*/                   ? rNewAttrs.Get( nWhich )
/*N*/                   : rNewAttrs.GetPool()->GetDefaultItem( nWhich );
/*N*/
/*N*/       bInvalidate = (rNewItem != rOldItem);
/*N*/   }
/*N*/
/*N*/   return bInvalidate;
/*N*/ }

/*N*/ ULONG ScGlobal::GetStandardFormat( SvNumberFormatter& rFormatter,
/*N*/       ULONG nFormat, short nType )
/*N*/ {
/*N*/   const SvNumberformat* pFormat = rFormatter.GetEntry( nFormat );
/*N*/   if ( pFormat )
/*N*/       return rFormatter.GetStandardFormat( nFormat, nType, pFormat->GetLanguage() );
/*N*/   return rFormatter.GetStandardFormat( nType, eLnge );
/*N*/ }

/*N*/ ULONG ScGlobal::GetStandardFormat( double fNumber, SvNumberFormatter& rFormatter,
/*N*/       ULONG nFormat, short nType )
/*N*/ {
/*N*/   const SvNumberformat* pFormat = rFormatter.GetEntry( nFormat );
/*N*/   if ( pFormat )
/*N*/       return rFormatter.GetStandardFormat( fNumber, nFormat, nType,
/*N*/           pFormat->GetLanguage() );
/*?*/   return rFormatter.GetStandardFormat( nType, eLnge );
/*N*/ }


// static
/*N*/ SvNumberFormatter* ScGlobal::GetEnglishFormatter()
/*N*/ {
/*N*/     if ( !pEnglishFormatter )
/*N*/     {
/*N*/         pEnglishFormatter = new SvNumberFormatter(
/*N*/             ::legacy_binfilters::getLegacyProcessServiceFactory(), LANGUAGE_ENGLISH_US );
/*N*/         pEnglishFormatter->SetEvalDateFormat( NF_EVALDATEFORMAT_INTL_FORMAT );
/*N*/     }
/*N*/     return pEnglishFormatter;
/*N*/ }


//------------------------------------------------------------------------

/*N*/ BOOL ScGlobal::CheckWidthInvalidate( BOOL& bNumFormatChanged,
/*N*/                                    const SfxItemSet& rNewAttrs,
/*N*/                                    const SfxItemSet& rOldAttrs )
/*N*/ {
/*N*/   // Ueberpruefen, ob Attributaenderungen in rNewAttrs gegnueber
/*N*/   // rOldAttrs die Textbreite an einer Zelle ungueltig machen
/*N*/
/*N*/   bNumFormatChanged =
/*N*/           HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_VALUE_FORMAT );
/*N*/   return ( bNumFormatChanged
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_LANGUAGE_FORMAT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CJK_FONT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CTL_FONT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_HEIGHT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CJK_FONT_HEIGHT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CTL_FONT_HEIGHT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_WEIGHT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CJK_FONT_WEIGHT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CTL_FONT_WEIGHT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_POSTURE )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CJK_FONT_POSTURE )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_CTL_FONT_POSTURE )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_UNDERLINE )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_CROSSEDOUT )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_CONTOUR )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_FONT_SHADOWED )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_ORIENTATION )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_ROTATE_VALUE )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_ROTATE_MODE )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_LINEBREAK )
/*N*/       || HasAttrChanged( rNewAttrs, rOldAttrs, ATTR_MARGIN )
/*N*/       );
/*N*/ }

//STRIP001 const SvxSearchItem& ScGlobal::GetSearchItem()
//STRIP001 {
//STRIP001  if (!pSearchItem)
//STRIP001  {
//STRIP001      pSearchItem = new SvxSearchItem( SID_SEARCH_ITEM );
//STRIP001      pSearchItem->SetAppFlag( SVX_SEARCHAPP_CALC );
//STRIP001  }
//STRIP001  return *pSearchItem;
//STRIP001 }

//STRIP001 void ScGlobal::SetSearchItem( const SvxSearchItem& rNew )
//STRIP001 {
//STRIP001  // Hier waere ein Zuweisungsoperator ganz nett:
//STRIP001  delete pSearchItem;
//STRIP001  pSearchItem = (SvxSearchItem*)rNew.Clone();
//STRIP001
//STRIP001  pSearchItem->SetWhich( SID_SEARCH_ITEM );
//STRIP001 }

//STRIP001 void ScGlobal::ClearAutoFormat()
//STRIP001 {
//STRIP001  if (pAutoFormat!=NULL)
//STRIP001  {
//STRIP001      delete pAutoFormat;
//STRIP001      pAutoFormat=NULL;
//STRIP001  }
//STRIP001 }

/*N*/ ScAutoFormat* ScGlobal::GetAutoFormat()
/*N*/ {
/*N*/   if ( !pAutoFormat )
/*N*/   {
/*N*/       pAutoFormat = new ScAutoFormat;
/*N*/       pAutoFormat->Load();
/*N*/   }
/*N*/
/*N*/   return pAutoFormat;
/*N*/ }

/*N*/ FuncCollection* ScGlobal::GetFuncCollection()
/*N*/ {
/*N*/   if (!pFuncCollection)
/*N*/       pFuncCollection = new FuncCollection();
/*N*/   return pFuncCollection;
/*N*/ }

/*N*/ ScUnoAddInCollection* ScGlobal::GetAddInCollection()
/*N*/ {
/*N*/   if (!pAddInCollection)
/*N*/       pAddInCollection = new ScUnoAddInCollection();
/*N*/   return pAddInCollection;
/*N*/ }

/*N*/ ScUserList* ScGlobal::GetUserList()
/*N*/ {
/*N*/   // Hack: Cfg-Item an der App ggF. laden
/*N*/
/*N*/   global_InitAppOptions();
/*N*/
/*N*/   if (!pUserList)
/*N*/       pUserList = new ScUserList();
/*N*/   return pUserList;
/*N*/ }

/*N*/ void ScGlobal::SetUserList( const ScUserList* pNewList )
/*N*/ {
/*N*/   if ( pNewList )
/*N*/   {
/*N*/       if ( !pUserList )
/*N*/           pUserList = new ScUserList( *pNewList );
/*N*/       else
/*?*/           *pUserList = *pNewList;
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       delete pUserList;
/*?*/       pUserList = NULL;
/*N*/   }
/*N*/ }

/*N*/ const String& ScGlobal::GetRscString( USHORT nIndex )
/*N*/ {
/*N*/   DBG_ASSERT( nIndex <= STR_COUNT,
/*N*/       "-ScGlobal::GetRscString(): Index zu gross!");
/*N*/   if( !ppRscString[ nIndex ] )
/*N*/   {
/*N*/       ppRscString[ nIndex ] =
/*N*/           new String( ScRscStrLoader( RID_GLOBSTR, nIndex ).GetString() );
/*N*/   }
/*N*/   return *ppRscString[ nIndex ];
/*N*/ }

/*N*/ String ScGlobal::GetErrorString(USHORT nErrNumber)
/*N*/ {
/*N*/   String sResStr;
/*N*/   switch (nErrNumber)
/*N*/   {
/*N*/       case NOVALUE     : nErrNumber = STR_NV_STR; break;
/*N*/       case errNoRef    : nErrNumber = STR_NO_REF_TABLE; break;
/*N*/       case errNoName   : nErrNumber = STR_NO_NAME_REF; break;
/*N*/         case errNoAddin  : nErrNumber = STR_NO_ADDIN; break;
/*N*/         case errNoMacro  : nErrNumber = STR_NO_MACRO; break;
/*N*/       case errDoubleRef:
/*N*/       case errNoValue  : nErrNumber = STR_NO_VALUE; break;
/*N*/
/*N*/       default          : sResStr = GetRscString(STR_ERROR_STR);
/*N*/                          sResStr += String::CreateFromInt32( nErrNumber );
/*N*/                          nErrNumber = 0;
/*N*/                          break;
/*N*/   }
/*N*/   if( nErrNumber )
/*N*/       sResStr = GetRscString( nErrNumber );
/*N*/   return sResStr;
/*N*/ }

//STRIP001 String ScGlobal::GetLongErrorString(USHORT nErrNumber)
//STRIP001 {
//STRIP001  switch (nErrNumber)
//STRIP001  {
//STRIP001      case 0:
//STRIP001          break;
//STRIP001      case 1:
//STRIP001      case errIllegalArgument:
//STRIP001          nErrNumber = STR_LONG_ERR_ILL_ARG;
//STRIP001      break;
//STRIP001      case 2:
//STRIP001      case 3:
//STRIP001      case 4:
//STRIP001      case 5:
//STRIP001      case errIllegalFPOperation:
//STRIP001          nErrNumber = STR_LONG_ERR_ILL_FPO;
//STRIP001      break;
//STRIP001      case errIllegalChar:
//STRIP001          nErrNumber = STR_LONG_ERR_ILL_CHAR;
//STRIP001      break;
//STRIP001      case errIllegalParameter:
//STRIP001          nErrNumber = STR_LONG_ERR_ILL_PAR;
//STRIP001      break;
//STRIP001      case errSeparator:
//STRIP001          nErrNumber = STR_LONG_ERR_ILL_SEP;
//STRIP001      break;
//STRIP001      case errPair:
//STRIP001      case errPairExpected:
//STRIP001          nErrNumber = STR_LONG_ERR_PAIR;
//STRIP001      break;
//STRIP001      case errOperatorExpected:
//STRIP001          nErrNumber = STR_LONG_ERR_OP_EXP;
//STRIP001      break;
//STRIP001      case errVariableExpected:
//STRIP001      case errParameterExpected:
//STRIP001          nErrNumber = STR_LONG_ERR_VAR_EXP;
//STRIP001      break;
//STRIP001      case errCodeOverflow:
//STRIP001          nErrNumber = STR_LONG_ERR_CODE_OVF;
//STRIP001      break;
//STRIP001      case errStringOverflow:
//STRIP001          nErrNumber = STR_LONG_ERR_STR_OVF;
//STRIP001      break;
//STRIP001      case errStackOverflow:
//STRIP001      case errInterpOverflow:
//STRIP001          nErrNumber = STR_LONG_ERR_STACK_OVF;
//STRIP001      break;
//STRIP001      case errIllegalJump:
//STRIP001      case errUnknownState:
//STRIP001      case errUnknownVariable:
//STRIP001      case errUnknownOpCode:
//STRIP001      case errUnknownStackVariable:
//STRIP001      case errUnknownToken:
//STRIP001      case errNoCode:
//STRIP001      case errDoubleRef:
//STRIP001          nErrNumber = STR_LONG_ERR_SYNTAX;
//STRIP001      break;
//STRIP001      case errCircularReference:
//STRIP001          nErrNumber = STR_LONG_ERR_CIRC_REF;
//STRIP001      break;
//STRIP001      case errNoConvergence:
//STRIP001          nErrNumber = STR_LONG_ERR_NO_CONV;
//STRIP001      break;
//STRIP001      case errNoRef:
//STRIP001          nErrNumber = STR_LONG_ERR_NO_REF;
//STRIP001      break;
//STRIP001      case errNoName:
//STRIP001          nErrNumber = STR_LONG_ERR_NO_NAME;
//STRIP001      break;
//STRIP001         case errNoAddin:
//STRIP001             nErrNumber = STR_LONG_ERR_NO_ADDIN;
//STRIP001      break;
//STRIP001         case errNoMacro:
//STRIP001             nErrNumber = STR_LONG_ERR_NO_MACRO;
//STRIP001      break;
//STRIP001      case errNoValue:
//STRIP001          nErrNumber = STR_LONG_ERR_NO_VALUE;
//STRIP001      break;
//STRIP001      case NOVALUE:
//STRIP001          nErrNumber = STR_LONG_ERR_NV;
//STRIP001      break;
//STRIP001      default:
//STRIP001          nErrNumber = STR_ERROR_STR;
//STRIP001      break;
//STRIP001  }
//STRIP001  String aRes( GetRscString( nErrNumber ) );
//STRIP001  if( bOderSo )
//STRIP001  {
//STRIP001      String aOderSo( GetRscString( STR_ODER_SO ) );
//STRIP001      aOderSo.SearchAndReplace( String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("%s")), aRes );
//STRIP001      aRes = aOderSo;
//STRIP001  }
//STRIP001  return aRes;
//STRIP001 }

/*N*/ SvxBrushItem* ScGlobal::GetButtonBrushItem()
/*N*/ {
/*?*/     DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 pButtonBrushItem->SetColor( Application::GetSettings().GetStyleSettings().GetFaceColor() );
//STRIP001     return pButtonBrushItem;
/*N*/ }

/*N*/ const String& ScGlobal::GetEmptyString()
/*N*/ {
/*N*/   return *pEmptyString;
/*N*/ }

//STRIP001 ImageList* ScGlobal::GetOutlineSymbols( bool bHC )
//STRIP001 {
//STRIP001     ImageList*& rpImageList = bHC ? pOutlineBitmapsHC : pOutlineBitmaps;
//STRIP001     if( !rpImageList )
//STRIP001         rpImageList = new ImageList( ScResId( bHC ? RID_OUTLINEBITMAPS_H : RID_OUTLINEBITMAPS ) );
//STRIP001     return rpImageList;
//STRIP001 }

/*N*/ void ScGlobal::Init()
/*N*/ {
/*N*/   pEmptyString = new String;
/*N*/
/*N*/   //  Die Default-Sprache fuer Zahlenformate (ScGlobal::eLnge)
/*N*/   //  muss immer LANGUAGE_SYSTEM sein
/*N*/   //! Dann kann auch die Variable raus
/*N*/   eLnge = LANGUAGE_SYSTEM;
/*N*/
/*N*/   //! Wenn Sortierung etc. von der Sprache der installierten Offfice-Version
/*N*/     //! abhaengen sollen, hier "Application::GetSettings().GetUILanguage()"
/*N*/   String aLanguage, aCountry;
/*N*/     LanguageType eOfficeLanguage = Application::GetSettings().GetLanguage();
/*N*/     ConvertLanguageToIsoNames( eOfficeLanguage, aLanguage, aCountry );
/*N*/   pLocale = new ::com::sun::star::lang::Locale( aLanguage, aCountry, EMPTY_STRING );
/*N*/     pSysLocale = new SvtSysLocale;
/*N*/     pCharClass = pSysLocale->GetCharClassPtr();
/*N*/     pLocaleData = pSysLocale->GetLocaleDataPtr();
/*N*/   pCalendar = new CalendarWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/   pCalendar->loadDefaultCalendar( *pLocale );
/*N*/   pCollator = new CollatorWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/   pCollator->loadDefaultCollator( *pLocale, SC_COLLATOR_IGNORES );
/*N*/   pCaseCollator = new CollatorWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/   pCaseCollator->loadDefaultCollator( *pLocale, 0 );
/*N*/     pTransliteration = new ::utl::TransliterationWrapper(
/*N*/         ::legacy_binfilters::getLegacyProcessServiceFactory(), SC_TRANSLITERATION_IGNORECASE );
/*N*/     pTransliteration->loadModuleIfNeeded( eOfficeLanguage );
/*N*/     pCaseTransliteration = new ::utl::TransliterationWrapper(
/*N*/         ::legacy_binfilters::getLegacyProcessServiceFactory(), SC_TRANSLITERATION_CASESENSE );
/*N*/     pCaseTransliteration->loadModuleIfNeeded( eOfficeLanguage );
/*N*/     pScIntlWrapper = new IntlWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory(), *pLocale );
/*N*/
/*N*/   ppRscString = new String *[ STR_COUNT+1 ];
/*N*/   for( USHORT nC = 0 ; nC <= STR_COUNT ; nC++ ) ppRscString[ nC ] = NULL;
/*N*/
/*N*/   pEmptyBrushItem = new SvxBrushItem( Color( COL_TRANSPARENT ) );
/*N*/     pButtonBrushItem = new SvxBrushItem( Color() );
/*N*/   pEmbeddedBrushItem = new SvxBrushItem( Color( COL_LIGHTCYAN ) );
/*N*/   pProtectedBrushItem = new SvxBrushItem( Color( COL_LIGHTGRAY ) );
/*N*/
/*N*/   UpdatePPT(NULL);
/*N*/   ScCompiler::Init();
/*N*/   srand( (unsigned) time( NULL ) );       // Random Seed Init fuer Interpreter
/*N*/
/*N*/   InitAddIns();
/*N*/
/*N*/   pStrClipDocName = new String( ScResId( SCSTR_NONAME ) );
/*N*/   *pStrClipDocName += '1';
/*N*/
/*N*/   //  ScDocumentPool::InitVersionMaps() ist schon vorher gerufen worden
/*N*/ }

/*N*/ void ScGlobal::UpdatePPT( OutputDevice* pDev )
/*N*/ {
/*N*/   USHORT nCurrentZoom = Application::GetSettings().GetStyleSettings().GetScreenZoom();
/*N*/   if ( nCurrentZoom != nPPTZoom )
/*N*/   {
/*N*/       //  Screen PPT values must be updated when ScreenZoom has changed.
/*N*/       //  If called from Window::DataChanged, the window is passed as pDev,
/*N*/       //  to make sure LogicToPixel uses a device which already uses the new zoom.
/*N*/       //  For the initial settings, NULL is passed and GetDefaultDevice used.
/*N*/
/*N*/       if ( !pDev )
/*N*/           pDev = Application::GetDefaultDevice();
/*N*/       Point aPix1000 = pDev->LogicToPixel( Point(1000,1000), MAP_TWIP );
/*N*/       nScreenPPTX = aPix1000.X() / 1000.0;
/*N*/       nScreenPPTY = aPix1000.Y() / 1000.0;
/*N*/       nPPTZoom = nCurrentZoom;
/*N*/   }
/*N*/ }

//STRIP001 const String& ScGlobal::GetClipDocName()
//STRIP001 {
//STRIP001  return *pStrClipDocName;
//STRIP001 }

//STRIP001 void ScGlobal::SetClipDocName( const String& rNew )
//STRIP001 {
//STRIP001  *pStrClipDocName = rNew;
//STRIP001 }


/*N*/ void ScGlobal::InitTextHeight(SfxItemPool* pPool)
/*N*/ {
/*N*/   if (!pPool)
/*N*/   {
/*?*/       DBG_ERROR("kein Pool bei ScGlobal::InitTextHeight");
/*?*/       return;
/*N*/   }
/*N*/
/*N*/   const ScPatternAttr* pPattern = (const ScPatternAttr*)&pPool->GetDefaultItem(ATTR_PATTERN);
/*N*/   if (!pPattern)
/*N*/   {
/*?*/       DBG_ERROR("kein Default-Pattern bei ScGlobal::InitTextHeight");
/*?*/       return;
/*N*/   }
/*N*/
/*N*/ //    String aTestString('X');
/*N*/   OutputDevice* pDefaultDev = Application::GetDefaultDevice();
/*N*/   VirtualDevice aVirtWindow( *pDefaultDev );
/*N*/   aVirtWindow.SetMapMode(MAP_PIXEL);
/*N*/   Font aDefFont;
/*N*/   pPattern->GetFont(aDefFont, SC_AUTOCOL_BLACK, &aVirtWindow);        // font color doesn't matter here
/*N*/   aVirtWindow.SetFont(aDefFont);
/*N*/   nDefFontHeight = (USHORT) aVirtWindow.PixelToLogic(Size(0, aVirtWindow.GetTextHeight()),
/*N*/                               MAP_TWIP).Height();
/*N*/
/*N*/   const SvxMarginItem* pMargin = (const SvxMarginItem*)&pPattern->GetItem(ATTR_MARGIN);
/*N*/
/*N*/   nStdRowHeight = (USHORT) ( nDefFontHeight +
/*N*/                               pMargin->GetTopMargin() + pMargin->GetBottomMargin()
/*N*/                               - STD_ROWHEIGHT_DIFF );
/*N*/ }

/*N*/ void ScGlobal::Clear()
/*N*/ {
/*N*/   // asyncs _vor_ ExitExternalFunc zerstoeren!
/*N*/   theAddInAsyncTbl.DeleteAndDestroy( 0, theAddInAsyncTbl.Count() );
/*N*/   ExitExternalFunc();
/*N*/   DELETEZ(pAutoFormat);
/*N*/   DELETEZ(pSearchItem);
/*N*/   DELETEZ(pFuncCollection);
/*N*/   DELETEZ(pAddInCollection);
/*N*/   DELETEZ(pUserList);
/*N*/
/*N*/   for( USHORT nC = 0 ; nC < STR_COUNT ; nC++ )
/*N*/       if( ppRscString ) delete ppRscString[ nC ];
/*N*/   delete[] ppRscString;
/*N*/   ppRscString = NULL;
/*N*/
/*N*/   DELETEZ(pStarCalcFunctionList);     // vor ResMgr zerstoeren!
/*N*/   DELETEZ(pStarCalcFunctionMgr);
/*N*/   ScCompiler::DeInit();
/*N*/   ScInterpreter::GlobalExit();            // statischen Stack loeschen
/*N*/
/*N*/   DELETEZ(pEmptyBrushItem);
/*N*/   DELETEZ(pButtonBrushItem);
/*N*/   DELETEZ(pEmbeddedBrushItem);
/*N*/   DELETEZ(pProtectedBrushItem);
/*N*/     DELETEZ(pOutlineBitmaps);
/*N*/     DELETEZ(pOutlineBitmapsHC);
/*N*/ //    DELETEZ(pAnchorBitmap);
/*N*/ //    DELETEZ(pGrayAnchorBitmap);
/*N*/     DELETEZ(pEnglishFormatter);
/*N*/     DELETEZ(pCaseTransliteration);
/*N*/     DELETEZ(pTransliteration);
/*N*/   DELETEZ(pCaseCollator);
/*N*/   DELETEZ(pCollator);
/*N*/   DELETEZ(pCalendar);
/*N*/     //! do NOT delete pCharClass since it is a pointer to the single SvtSysLocale instance
/*N*/     pCharClass = NULL;
/*N*/     //! do NOT delete pLocaleData since it is a pointer to the single SvtSysLocale instance
/*N*/     pLocaleData = NULL;
/*N*/     DELETEZ(pSysLocale);
/*N*/   DELETEZ(pLocale);
/*N*/     DELETEZ(pScIntlWrapper);
/*N*/   DELETEZ(pStrClipDocName);
/*N*/
/*N*/   DELETEZ(pUnitConverter);
/*N*/
/*N*/   ScDocumentPool::DeleteVersionMaps();
/*N*/
/*N*/   DELETEZ(pEmptyString);
/*N*/ }

//------------------------------------------------------------------------

// static
/*N*/ CharSet ScGlobal::GetCharsetValue( const String& rCharSet )
/*N*/ {
/*N*/   // new TextEncoding values
/*N*/   if ( CharClass::isAsciiNumeric( rCharSet ) )
/*N*/   {
/*?*/       sal_Int32 nVal = rCharSet.ToInt32();
/*?*/       if ( !nVal || nVal == RTL_TEXTENCODING_DONTKNOW )
/*?*/           return gsl_getSystemTextEncoding();
/*?*/       return (CharSet) nVal;
/*N*/   }
/*N*/   // old CharSet values for compatibility
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("ANSI")     ) return RTL_TEXTENCODING_MS_1252;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("MAC")      ) return RTL_TEXTENCODING_APPLE_ROMAN;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC")    ) return RTL_TEXTENCODING_IBM_850;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC_437")) return RTL_TEXTENCODING_IBM_437;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC_850")) return RTL_TEXTENCODING_IBM_850;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC_860")) return RTL_TEXTENCODING_IBM_860;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC_861")) return RTL_TEXTENCODING_IBM_861;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC_863")) return RTL_TEXTENCODING_IBM_863;
/*N*/   else if (rCharSet.EqualsIgnoreCaseAscii("IBMPC_865")) return RTL_TEXTENCODING_IBM_865;
/*N*/ //    else if (rCharSet.EqualsIgnoreCaseAscii("SYSTEM")   ) return gsl_getSystemTextEncoding();
/*N*/   else return gsl_getSystemTextEncoding();
/*N*/ }

//------------------------------------------------------------------------

// static
/*N*/ String ScGlobal::GetCharsetString( CharSet eVal )
/*N*/ {
/*N*/   const sal_Char* pChar;
/*N*/   switch ( eVal )
/*N*/   {
/*N*/       // old CharSet strings for compatibility
/*N*/       case RTL_TEXTENCODING_MS_1252:      pChar = "ANSI";         break;
/*N*/       case RTL_TEXTENCODING_APPLE_ROMAN:  pChar = "MAC";          break;
/*N*/       // IBMPC == IBMPC_850
/*N*/       case RTL_TEXTENCODING_IBM_437:      pChar = "IBMPC_437";    break;
/*N*/       case RTL_TEXTENCODING_IBM_850:      pChar = "IBMPC_850";    break;
/*N*/       case RTL_TEXTENCODING_IBM_860:      pChar = "IBMPC_860";    break;
/*N*/       case RTL_TEXTENCODING_IBM_861:      pChar = "IBMPC_861";    break;
/*N*/       case RTL_TEXTENCODING_IBM_863:      pChar = "IBMPC_863";    break;
/*N*/       case RTL_TEXTENCODING_IBM_865:      pChar = "IBMPC_865";    break;
/*N*/       case RTL_TEXTENCODING_DONTKNOW:     pChar = "SYSTEM";       break;
/*N*/       // new string of TextEncoding value
/*N*/       default:
/*N*/           return String::CreateFromInt32( eVal );
/*N*/   }
/*N*/   return String::CreateFromAscii(pChar);
/*N*/  }

//------------------------------------------------------------------------

/*N*/ ScFunctionList* ScGlobal::GetStarCalcFunctionList()
/*N*/ {
/*N*/   if ( !pStarCalcFunctionList )
/*N*/       pStarCalcFunctionList = new ScFunctionList;
/*N*/
/*N*/   return pStarCalcFunctionList;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 ScFunctionMgr* ScGlobal::GetStarCalcFunctionMgr()
//STRIP001 {
//STRIP001  if ( !pStarCalcFunctionMgr )
//STRIP001      pStarCalcFunctionMgr = new ScFunctionMgr;
//STRIP001
//STRIP001  return pStarCalcFunctionMgr;
//STRIP001 }

//------------------------------------------------------------------------

// static
/*N*/ ScUnitConverter* ScGlobal::GetUnitConverter()
/*N*/ {
/*N*/   if ( !pUnitConverter )
/*N*/       pUnitConverter = new ScUnitConverter;
/*N*/
/*N*/   return pUnitConverter;
/*N*/ }


//------------------------------------------------------------------------

// static
/*N*/ const sal_Unicode* ScGlobal::UnicodeStrChr( const sal_Unicode* pStr,
/*N*/           sal_Unicode c )
/*N*/ {
/*N*/   if ( !pStr )
/*N*/       return NULL;
/*N*/   while ( *pStr )
/*N*/   {
/*N*/       if ( *pStr == c )
/*N*/           return pStr;
/*N*/       pStr++;
/*N*/   }
/*N*/   return NULL;
/*N*/ }


//------------------------------------------------------------------------

/*N*/ BOOL ScGlobal::EETextObjEqual( const EditTextObject* pObj1,
/*N*/                              const EditTextObject* pObj2 )
/*N*/ {
/*N*/   if ( pObj1 == pObj2 )               // both empty or the same object
/*N*/       return TRUE;
/*N*/
/*N*/   if ( pObj1 && pObj2 )
/*N*/   {
/*N*/       //  first test for equal text content
/*N*/       USHORT nParCount = pObj1->GetParagraphCount();
/*N*/       if ( nParCount != pObj2->GetParagraphCount() )
/*N*/           return FALSE;
/*N*/       for (USHORT nPar=0; nPar<nParCount; nPar++)
/*N*/           if ( pObj1->GetText(nPar) != pObj2->GetText(nPar) )
/*N*/               return FALSE;
/*N*/
/*N*/       SvMemoryStream  aStream1;
/*N*/       SvMemoryStream  aStream2;
/*N*/       pObj1->Store( aStream1 );
/*N*/       pObj2->Store( aStream2 );
/*N*/       ULONG nSize = aStream1.Tell();
/*N*/       if ( aStream2.Tell() == nSize )
/*N*/           if ( !memcmp( aStream1.GetData(), aStream2.GetData(), (USHORT) nSize ) )
/*N*/               return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

//STRIP001 void ScGlobal::OpenURL( const String& rURL, const String& rTarget )
//STRIP001 {
//STRIP001  //  OpenURL wird immer ueber irgendwelche Umwege durch Mausklicks im GridWindow
//STRIP001  //  aufgerufen, darum stimmen pScActiveViewShell und nScClickMouseModifier.
//STRIP001
//STRIP001  SfxStringItem aUrl( SID_FILE_NAME, rURL );
//STRIP001  SfxStringItem aTarget( SID_TARGETNAME, rTarget );
//STRIP001
//STRIP001  if ( nScClickMouseModifier & KEY_MOD1 )     // control-click -> into new window
//STRIP001      aTarget.SetValue(
//STRIP001          String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("_blank")) );
//STRIP001
//STRIP001  SfxViewFrame* pFrame = NULL;
//STRIP001  String aReferName;
//STRIP001  if ( pScActiveViewShell )
//STRIP001  {
//STRIP001      pFrame = pScActiveViewShell->GetViewFrame();
//STRIP001      SfxMedium* pMed = pFrame->GetObjectShell()->GetMedium();
//STRIP001      if (pMed)
//STRIP001          aReferName = pMed->GetName();
//STRIP001  }
//STRIP001
//STRIP001  SfxFrameItem aFrm( SID_DOCFRAME, pFrame );
//STRIP001  SfxStringItem aReferer( SID_REFERER, aReferName );
//STRIP001
//STRIP001  SfxBoolItem aNewView( SID_OPEN_NEW_VIEW, FALSE );
//STRIP001  SfxBoolItem aBrowsing( SID_BROWSE, TRUE );
//STRIP001
//STRIP001  //  kein SID_SILENT mehr wegen Bug #42525# (war angeblich sowieso falsch)
//STRIP001
//STRIP001  SfxViewFrame* pViewFrm = SfxViewFrame::Current();
//STRIP001  if (pViewFrm)
//STRIP001      pViewFrm->GetDispatcher()->Execute( SID_OPENDOC,
//STRIP001                                  SFX_CALLMODE_ASYNCHRON | SFX_CALLMODE_RECORD,
//STRIP001                                  &aUrl, &aTarget,
//STRIP001                                  &aFrm, &aReferer,
//STRIP001                                  &aNewView, &aBrowsing,
//STRIP001                                  0L );
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BYTE ScGlobal::GetDefaultScriptType()
/*N*/ {
/*N*/   //  Used when text contains only WEAK characters.
/*N*/   //  Script type of office language is used then (same as GetEditDefaultLanguage,
/*N*/   //  to get consistent behavior of text in simple cells and EditEngine,
/*N*/   //  also same as GetAppLanguage() in Writer)
/*N*/
/*N*/   return (BYTE) SvtLanguageOptions::GetScriptTypeOfLanguage( Application::GetSettings().GetLanguage() );
/*N*/ }

/*N*/ LanguageType ScGlobal::GetEditDefaultLanguage()
/*N*/ {
/*N*/   //  used for EditEngine::SetDefaultLanguage
/*N*/
/*N*/   return Application::GetSettings().GetLanguage();
/*N*/ }

//STRIP001 USHORT ScGlobal::GetScriptedWhichID( BYTE nScriptType, USHORT nWhich )
//STRIP001 {
//STRIP001     switch ( nScriptType )
//STRIP001     {
//STRIP001         case SCRIPTTYPE_LATIN:
//STRIP001      case SCRIPTTYPE_ASIAN:
//STRIP001         case SCRIPTTYPE_COMPLEX:
//STRIP001         break;      // take exact matches
//STRIP001         default:    // prefer one, first COMPLEX, then ASIAN
//STRIP001             if ( nScriptType & SCRIPTTYPE_COMPLEX )
//STRIP001                 nScriptType = SCRIPTTYPE_COMPLEX;
//STRIP001             else if ( nScriptType & SCRIPTTYPE_ASIAN )
//STRIP001                 nScriptType = SCRIPTTYPE_ASIAN;
//STRIP001     }
//STRIP001     switch ( nScriptType )
//STRIP001     {
//STRIP001         case SCRIPTTYPE_COMPLEX:
//STRIP001         {
//STRIP001             switch ( nWhich )
//STRIP001             {
//STRIP001                 case ATTR_FONT:
//STRIP001                 case ATTR_CJK_FONT:
//STRIP001                     nWhich = ATTR_CTL_FONT;
//STRIP001                 break;
//STRIP001                 case ATTR_FONT_HEIGHT:
//STRIP001                 case ATTR_CJK_FONT_HEIGHT:
//STRIP001                     nWhich = ATTR_CTL_FONT_HEIGHT;
//STRIP001                 break;
//STRIP001                 case ATTR_FONT_WEIGHT:
//STRIP001                 case ATTR_CJK_FONT_WEIGHT:
//STRIP001                     nWhich = ATTR_CTL_FONT_WEIGHT;
//STRIP001                 break;
//STRIP001                 case ATTR_FONT_POSTURE:
//STRIP001                 case ATTR_CJK_FONT_POSTURE:
//STRIP001                     nWhich = ATTR_CTL_FONT_POSTURE;
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001         break;
//STRIP001      case SCRIPTTYPE_ASIAN:
//STRIP001         {
//STRIP001             switch ( nWhich )
//STRIP001             {
//STRIP001                 case ATTR_FONT:
//STRIP001                 case ATTR_CTL_FONT:
//STRIP001                     nWhich = ATTR_CJK_FONT;
//STRIP001                 break;
//STRIP001                 case ATTR_FONT_HEIGHT:
//STRIP001                 case ATTR_CTL_FONT_HEIGHT:
//STRIP001                     nWhich = ATTR_CJK_FONT_HEIGHT;
//STRIP001                 break;
//STRIP001                 case ATTR_FONT_WEIGHT:
//STRIP001                 case ATTR_CTL_FONT_WEIGHT:
//STRIP001                     nWhich = ATTR_CJK_FONT_WEIGHT;
//STRIP001                 break;
//STRIP001                 case ATTR_FONT_POSTURE:
//STRIP001                 case ATTR_CTL_FONT_POSTURE:
//STRIP001                     nWhich = ATTR_CJK_FONT_POSTURE;
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001         break;
//STRIP001         default:
//STRIP001         {
//STRIP001             switch ( nWhich )
//STRIP001             {
//STRIP001                 case ATTR_CTL_FONT:
//STRIP001                 case ATTR_CJK_FONT:
//STRIP001                     nWhich = ATTR_FONT;
//STRIP001                 break;
//STRIP001                 case ATTR_CTL_FONT_HEIGHT:
//STRIP001                 case ATTR_CJK_FONT_HEIGHT:
//STRIP001                     nWhich = ATTR_FONT_HEIGHT;
//STRIP001                 break;
//STRIP001                 case ATTR_CTL_FONT_WEIGHT:
//STRIP001                 case ATTR_CJK_FONT_WEIGHT:
//STRIP001                     nWhich = ATTR_FONT_WEIGHT;
//STRIP001                 break;
//STRIP001                 case ATTR_CTL_FONT_POSTURE:
//STRIP001                 case ATTR_CJK_FONT_POSTURE:
//STRIP001                     nWhich = ATTR_FONT_POSTURE;
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return nWhich;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ void ScGlobal::AddLanguage( SfxItemSet& rSet, SvNumberFormatter& rFormatter )
/*N*/ {
/*N*/     DBG_ASSERT( rSet.GetItemState( ATTR_LANGUAGE_FORMAT, FALSE ) == SFX_ITEM_DEFAULT,
/*N*/         "ScGlobal::AddLanguage - language already added");
/*N*/
/*N*/     const SfxPoolItem* pHardItem;
/*N*/     if ( rSet.GetItemState( ATTR_VALUE_FORMAT, FALSE, &pHardItem ) == SFX_ITEM_SET )
/*N*/     {
/*N*/         const SvNumberformat* pHardFormat = rFormatter.GetEntry(
/*N*/             ((const SfxUInt32Item*)pHardItem)->GetValue() );
/*N*/
/*N*/         ULONG nParentFmt = 0;   // pool default
/*N*/         const SfxItemSet* pParent = rSet.GetParent();
/*N*/         if ( pParent )
/*N*/             nParentFmt = ((const SfxUInt32Item&)pParent->Get( ATTR_VALUE_FORMAT )).GetValue();
/*N*/         const SvNumberformat* pParFormat = rFormatter.GetEntry( nParentFmt );
/*N*/
/*N*/         if ( pHardFormat && pParFormat &&
/*N*/                 (pHardFormat->GetLanguage() != pParFormat->GetLanguage()) )
/*N*/             rSet.Put( SvxLanguageItem( pHardFormat->GetLanguage(), ATTR_LANGUAGE_FORMAT ) );
/*N*/     }
/*N*/ }



//===================================================================
//  class ScFormulaUtil - statische Methoden
//===================================================================

//STRIP001 ScFuncDesc aDefaultFuncDesc;

//STRIP001 const ScFuncDesc* ScFormulaUtil::GetDefaultFuncDesc()
//STRIP001 {
//STRIP001  return &aDefaultFuncDesc;
//STRIP001 }

//STRIP001 BOOL ScFormulaUtil::GetNextFunc( const String&   rFormula,
//STRIP001                               BOOL           bBack,
//STRIP001                               xub_StrLen&    rFStart,   // Ein- und Ausgabe
//STRIP001                               xub_StrLen*    pFEnd,     // = NULL
//STRIP001                               ScFuncDesc**   ppFDesc,   // = NULL
//STRIP001                               String***      pppArgs )  // = NULL
//STRIP001 {
//STRIP001  BOOL        bFound = FALSE;
//STRIP001  xub_StrLen  nOldStart = rFStart;
//STRIP001  String      aFname;
//STRIP001
//STRIP001  rFStart = GetFunctionStart( rFormula, rFStart, bBack, ppFDesc ? &aFname : NULL );
//STRIP001  bFound  = ( rFStart != FUNC_NOTFOUND );
//STRIP001
//STRIP001  if ( bFound )
//STRIP001  {
//STRIP001      if ( pFEnd )
//STRIP001          *pFEnd = GetFunctionEnd( rFormula, rFStart );
//STRIP001
//STRIP001      if ( ppFDesc )
//STRIP001      {
//STRIP001          ScFunctionMgr* pFuncMgr = ScGlobal::GetStarCalcFunctionMgr();
//STRIP001          *ppFDesc = pFuncMgr->Get( aFname );
//STRIP001          if ( *ppFDesc )
//STRIP001          {
//STRIP001              if (pppArgs)
//STRIP001                  *pppArgs = GetArgStrings( rFormula, rFStart, (*ppFDesc)->nArgCount );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              *ppFDesc = &aDefaultFuncDesc;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rFStart = nOldStart;
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScFormulaUtil::FillArgStrings( const String&    rFormula,
//STRIP001                                  xub_StrLen      nFuncPos,
//STRIP001                                  USHORT          nArgs,
//STRIP001                                  String**        aArgArr )
//STRIP001 {
//STRIP001  if ( !aArgArr ) return;
//STRIP001
//STRIP001  xub_StrLen  nStart  = 0;
//STRIP001  xub_StrLen  nEnd    = 0;
//STRIP001  USHORT      i;
//STRIP001  BOOL        bLast   = FALSE;
//STRIP001
//STRIP001  for ( i=0; i<nArgs && !bLast; i++ )
//STRIP001  {
//STRIP001      nStart = GetArgStart( rFormula, nFuncPos, i );
//STRIP001
//STRIP001      if ( i+1<nArgs ) // letztes Argument?
//STRIP001      {
//STRIP001          nEnd = GetArgStart( rFormula, nFuncPos, i+1 );
//STRIP001
//STRIP001          if ( nEnd != nStart )
//STRIP001              aArgArr[i] = new String( rFormula.Copy( nStart, nEnd-1-nStart ) );
//STRIP001          else
//STRIP001              aArgArr[i] = new String, bLast = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nEnd = GetFunctionEnd( rFormula, nFuncPos )-1;
//STRIP001          if ( nStart < nEnd )
//STRIP001              aArgArr[i] = new String( rFormula.Copy( nStart, nEnd-nStart ) );
//STRIP001          else
//STRIP001              aArgArr[i] = new String;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( bLast )
//STRIP001      for ( ; i<nArgs; i++ )
//STRIP001          aArgArr[i] = new String;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String** ScFormulaUtil::GetArgStrings( const String& rFormula,
//STRIP001                                     xub_StrLen nFuncPos,
//STRIP001                                     USHORT nArgs )
//STRIP001 {
//STRIP001  String** aArgArr = NULL;
//STRIP001  if (nArgs)
//STRIP001  {
//STRIP001      aArgArr = new String*[nArgs];
//STRIP001      FillArgStrings( rFormula, nFuncPos, nArgs, aArgArr );
//STRIP001  }
//STRIP001  return aArgArr;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 inline BOOL IsFormulaText( const String& rStr, xub_StrLen nPos )
//STRIP001 {
//STRIP001  if( ScGlobal::pCharClass->isLetterNumeric( rStr, nPos ) )
//STRIP001      return TRUE;
//STRIP001  else
//STRIP001  {   // In internationalized versions function names may contain a dot
//STRIP001      //  and in every version also an underscore... ;-)
//STRIP001      sal_Unicode c = rStr.GetChar(nPos);
//STRIP001      return c == '.' || c == '_';
//STRIP001  }
//STRIP001
//STRIP001 }

//STRIP001 xub_StrLen ScFormulaUtil::GetFunctionStart( const String&    rFormula,
//STRIP001                                      xub_StrLen      nStart,
//STRIP001                                      BOOL            bBack,
//STRIP001                                      String*         pFuncName )
//STRIP001 {
//STRIP001  xub_StrLen nStrLen = rFormula.Len();
//STRIP001
//STRIP001  if ( nStrLen < nStart )
//STRIP001      return nStart;
//STRIP001
//STRIP001  xub_StrLen  nFStart = FUNC_NOTFOUND;
//STRIP001  xub_StrLen  nParPos = nStart;
//STRIP001
//STRIP001  BOOL bRepeat, bFound;
//STRIP001  do
//STRIP001  {
//STRIP001      bFound  = FALSE;
//STRIP001      bRepeat = FALSE;
//STRIP001
//STRIP001      if ( bBack )
//STRIP001      {
//STRIP001          while ( !bFound && (nParPos > 0) )
//STRIP001          {
//STRIP001              if ( rFormula.GetChar(nParPos) == '"' )
//STRIP001              {
//STRIP001                  nParPos--;
//STRIP001                  while ( (nParPos > 0) && rFormula.GetChar(nParPos) != '"' )
//STRIP001                      nParPos--;
//STRIP001                  if (nParPos > 0)
//STRIP001                      nParPos--;
//STRIP001              }
//STRIP001              else if ( !(bFound = ( rFormula.GetChar(nParPos) == '(' ) ) )
//STRIP001                  nParPos--;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          while ( !bFound && (nParPos < nStrLen) )
//STRIP001          {
//STRIP001              if ( rFormula.GetChar(nParPos) == '"' )
//STRIP001              {
//STRIP001                  nParPos++;
//STRIP001                  while ( (nParPos < nStrLen) && rFormula.GetChar(nParPos) != '"' )
//STRIP001                      nParPos++;
//STRIP001                  nParPos++;
//STRIP001              }
//STRIP001              else if ( !(bFound = ( rFormula.GetChar(nParPos) == '(' ) ) )
//STRIP001                  nParPos++;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( bFound && (nParPos > 0) )
//STRIP001      {
//STRIP001          nFStart = nParPos-1;
//STRIP001
//STRIP001          while ( (nFStart > 0) && IsFormulaText( rFormula, nFStart ))
//STRIP001              nFStart--;
//STRIP001      }
//STRIP001
//STRIP001      nFStart++;
//STRIP001
//STRIP001      if ( bFound )
//STRIP001      {
//STRIP001          if ( IsFormulaText( rFormula, nFStart ) )
//STRIP001          {
//STRIP001                                  //  Funktion gefunden
//STRIP001              if ( pFuncName )
//STRIP001                  *pFuncName = rFormula.Copy( nFStart, nParPos-nFStart );
//STRIP001          }
//STRIP001          else                    // Klammern ohne Funktion -> weitersuchen
//STRIP001          {
//STRIP001              bRepeat = TRUE;
//STRIP001              if ( !bBack )
//STRIP001                  nParPos++;
//STRIP001              else if (nParPos > 0)
//STRIP001                  nParPos--;
//STRIP001              else
//STRIP001                  bRepeat = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      else                        // keine Klammern gefunden
//STRIP001      {
//STRIP001          nFStart = FUNC_NOTFOUND;
//STRIP001          if ( pFuncName )
//STRIP001              pFuncName->Erase();
//STRIP001      }
//STRIP001  }
//STRIP001  while(bRepeat);
//STRIP001
//STRIP001  return nFStart;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 xub_StrLen   ScFormulaUtil::GetFunctionEnd( const String& rStr, xub_StrLen nStart )
//STRIP001 {
//STRIP001  xub_StrLen nStrLen = rStr.Len();
//STRIP001
//STRIP001  if ( nStrLen < nStart )
//STRIP001      return nStart;
//STRIP001
//STRIP001  short   nParCount = 0;
//STRIP001  BOOL    bFound = FALSE;
//STRIP001
//STRIP001  while ( !bFound && (nStart < nStrLen) )
//STRIP001  {
//STRIP001      sal_Unicode c = rStr.GetChar(nStart);
//STRIP001
//STRIP001      if ( c == '"' )
//STRIP001      {
//STRIP001          nStart++;
//STRIP001          while ( (nStart < nStrLen) && rStr.GetChar(nStart) != '"' )
//STRIP001              nStart++;
//STRIP001      }
//STRIP001      else if ( c == '(' )
//STRIP001          nParCount++;
//STRIP001      else if ( c == ')' )
//STRIP001      {
//STRIP001          nParCount--;
//STRIP001          if ( nParCount == 0 )
//STRIP001              bFound = TRUE;
//STRIP001          else if ( nParCount < 0 )
//STRIP001          {
//STRIP001              bFound = TRUE;
//STRIP001              nStart--;   // einen zu weit gelesen
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( c == ';' )
//STRIP001      {
//STRIP001          if ( nParCount == 0 )
//STRIP001          {
//STRIP001              bFound = TRUE;
//STRIP001              nStart--;   // einen zu weit gelesen
//STRIP001          }
//STRIP001      }
//STRIP001      nStart++; // hinter gefundene Position stellen
//STRIP001  }
//STRIP001
//STRIP001  return nStart;
//STRIP001 }

//------------------------------------------------------------------

//STRIP001 xub_StrLen ScFormulaUtil::GetArgStart( const String& rStr, xub_StrLen nStart, USHORT nArg )
//STRIP001 {
//STRIP001  xub_StrLen nStrLen = rStr.Len();
//STRIP001
//STRIP001  if ( nStrLen < nStart )
//STRIP001      return nStart;
//STRIP001
//STRIP001  short   nParCount   = 0;
//STRIP001  short   nSemiCount  = 0;
//STRIP001  BOOL    bFound      = FALSE;
//STRIP001
//STRIP001  while ( !bFound && (nStart < nStrLen) )
//STRIP001  {
//STRIP001      sal_Unicode c = rStr.GetChar(nStart);
//STRIP001
//STRIP001      if ( c == '"' )
//STRIP001      {
//STRIP001          nStart++;
//STRIP001          while ( (nStart < nStrLen) && rStr.GetChar(nStart) != '"' )
//STRIP001              nStart++;
//STRIP001      }
//STRIP001      else if ( c == '(' )
//STRIP001      {
//STRIP001          bFound = ( nArg == 0 );
//STRIP001          nParCount++;
//STRIP001      }
//STRIP001      else if ( c == ')' )
//STRIP001      {
//STRIP001          nParCount--;
//STRIP001          bFound = ( nParCount == 0 );
//STRIP001      }
//STRIP001      else if ( c == ';' )
//STRIP001      {
//STRIP001          if ( nParCount == 1 )
//STRIP001          {
//STRIP001              nArg--;
//STRIP001              bFound = ( nArg == 0  );
//STRIP001          }
//STRIP001      }
//STRIP001      nStart++;
//STRIP001  }
//STRIP001
//STRIP001  return nStart;
//STRIP001 }


//===================================================================
// class ScFunctionList:
//===================================================================

//===================================================================
//      class ScFuncRes
// fuer temporaere Objekte zum Holen der Resourcen

//STRIP001 class ScFuncRes : public Resource
//STRIP001 {
//STRIP001 public:
//STRIP001  ScFuncRes( ResId&, ScFuncDesc* );
//STRIP001
//STRIP001 private:
//STRIP001  USHORT GetNum();
//STRIP001 };

//--------------------------------------------------------------------

//STRIP001 ScFuncRes::ScFuncRes( ResId &aRes, ScFuncDesc* pDesc )
//STRIP001  : Resource(aRes)
//STRIP001 {
//STRIP001  USHORT      nArgs;
//STRIP001
//STRIP001  pDesc->nCategory = 1;
//STRIP001  pDesc->nCategory = GetNum();
//STRIP001  pDesc->nHelpId = GetNum() + 32768;      //! Hack, siehe ScFuncs.src
//STRIP001  pDesc->nArgCount = GetNum();
//STRIP001  nArgs = pDesc->nArgCount;
//STRIP001  if (nArgs >= VAR_ARGS) nArgs = nArgs-VAR_ARGS+1;
//STRIP001  if (nArgs)
//STRIP001  {
//STRIP001      pDesc->aDefArgOpt = new BOOL[nArgs];
//STRIP001      for (USHORT i = 0; i < nArgs; i++)
//STRIP001          pDesc->aDefArgOpt[i] = (BOOL)GetNum();
//STRIP001  }
//STRIP001
//STRIP001  pDesc->pFuncName = new String( ScCompiler::pSymbolTableNative[aRes.GetId()] );
//STRIP001  pDesc->pFuncDesc = new String(ScResId(1));
//STRIP001
//STRIP001  if (nArgs)
//STRIP001  {
//STRIP001      pDesc->aDefArgNames = new String*[nArgs];
//STRIP001      pDesc->aDefArgDescs = new String*[nArgs];
//STRIP001      for (USHORT i = 0; i < nArgs; i++)
//STRIP001      {
//STRIP001          pDesc->aDefArgNames[i] = new String(ScResId(2*(i+1)  ));
//STRIP001          pDesc->aDefArgDescs[i] = new String(ScResId(2*(i+1)+1));
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  FreeResource();
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 USHORT ScFuncRes::GetNum()
//STRIP001 {
//STRIP001  return ReadShortRes();
//STRIP001 }

//=========================================================================

// um an die protected von Resource ranzukommen
//STRIP001 class ScResourcePublisher : public Resource
//STRIP001 {
//STRIP001 public:
//STRIP001      ScResourcePublisher( const ScResId& rId ) : Resource( rId ) {}
//STRIP001  BOOL            IsAvailableRes( const ResId& rId ) const
//STRIP001                      { return Resource::IsAvailableRes( rId ); }
//STRIP001  void            FreeResource() { Resource::FreeResource(); }
//STRIP001 };


/*N*/ ScFunctionList::ScFunctionList() :
/*N*/       nMaxFuncNameLen ( 0 )
/*N*/ {
/*N*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScFuncDesc*       pDesc   = NULL;
//STRIP001  xub_StrLen      nStrLen = 0;
//STRIP001  FuncCollection* pFuncColl;
//STRIP001  USHORT i,j;
//STRIP001  USHORT nDescBlock[] =
//STRIP001  {
//STRIP001      RID_SC_FUNCTION_DESCRIPTIONS1,
//STRIP001      RID_SC_FUNCTION_DESCRIPTIONS2
//STRIP001  };
//STRIP001  const USHORT nBlocks = sizeof(nDescBlock) / sizeof(USHORT);
//STRIP001
//STRIP001  aFunctionList.Clear();
//STRIP001
//STRIP001  for ( USHORT k = 0; k < nBlocks; k++ )
//STRIP001  {
//STRIP001      ScResourcePublisher* pBlock =
//STRIP001          new ScResourcePublisher( ScResId( nDescBlock[k] ) );
//STRIP001      for (i = 0; i <= SC_OPCODE_LAST_OPCODE_ID; i++)
//STRIP001      {   // Alle moeglichen OpCodes abgrasen.
//STRIP001          // Das ist zwar nicht das schnellste, aber sonst muessten
//STRIP001          // die Sub-Ressources innerhalb der Ressource-Bloecke und die
//STRIP001          // Ressource-Bloecke selber nach OpCodes geordnet sein,
//STRIP001          // was wohl eher utopisch ist..
//STRIP001          ScResId aRes(i);
//STRIP001          aRes.SetRT(RSC_RESOURCE);
//STRIP001          if (pBlock->IsAvailableRes(aRes))
//STRIP001          {   // Subresource fuer OpCode vorhanden
//STRIP001              pDesc = new ScFuncDesc;
//STRIP001              ScFuncRes aSubRes(aRes, pDesc);
//STRIP001              pDesc->nFIndex = i;
//STRIP001              aFunctionList.Insert( pDesc, LIST_APPEND );
//STRIP001
//STRIP001              nStrLen = (*(pDesc->pFuncName)).Len();
//STRIP001              if (nStrLen > nMaxFuncNameLen)
//STRIP001                  nMaxFuncNameLen = nStrLen;
//STRIP001          }
//STRIP001      }
//STRIP001      pBlock->FreeResource();
//STRIP001      delete pBlock;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nNextId = SC_OPCODE_LAST_OPCODE_ID + 1;      // FuncID for AddIn functions
//STRIP001
//STRIP001  // Auswertung AddIn-Liste
//STRIP001  String aDefArgNameValue =   String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("value"));
//STRIP001  String aDefArgNameString =  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("string"));
//STRIP001  String aDefArgNameValues =  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("values"));
//STRIP001  String aDefArgNameStrings = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("strings"));
//STRIP001  String aDefArgNameCells =   String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("cells"));
//STRIP001  String aDefArgNameNone =    String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("none"));
//STRIP001  String aDefArgDescValue =   String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("a value"));
//STRIP001  String aDefArgDescString =  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("a string"));
//STRIP001  String aDefArgDescValues =  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("array of values"));
//STRIP001  String aDefArgDescStrings = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("array of strings"));
//STRIP001  String aDefArgDescCells =   String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("range of cells"));
//STRIP001  String aDefArgDescNone =    String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("none"));
//STRIP001  String aArgName, aArgDesc;
//STRIP001  pFuncColl = ScGlobal::GetFuncCollection();
//STRIP001  for (i = 0; i < pFuncColl->GetCount(); i++)
//STRIP001  {
//STRIP001      pDesc = new ScFuncDesc;
//STRIP001      FuncData *pAddInFuncData = (FuncData*)pFuncColl->At(i);
//STRIP001      USHORT nArgs = pAddInFuncData->GetParamCount() - 1;
//STRIP001      pAddInFuncData->GetParamDesc( aArgName, aArgDesc, 0 );
//STRIP001        pDesc->nFIndex     = nNextId++;               //  ??? OpCode vergeben
//STRIP001        pDesc->nCategory   = ID_FUNCTION_GRP_ADDINS;
//STRIP001        pDesc->pFuncName   = new String(pAddInFuncData->GetInternalName());
//STRIP001        pDesc->pFuncName->ToUpperAscii();
//STRIP001        pDesc->pFuncDesc   = new String( aArgDesc );
//STRIP001      *(pDesc->pFuncDesc) += '\n';
//STRIP001        pDesc->pFuncDesc->AppendAscii(RTL_CONSTASCII_STRINGPARAM( "( AddIn: " ));
//STRIP001      *(pDesc->pFuncDesc) += pAddInFuncData->GetModuleName();
//STRIP001        pDesc->pFuncDesc->AppendAscii(RTL_CONSTASCII_STRINGPARAM( " )" ));
//STRIP001        pDesc->nArgCount   = nArgs;
//STRIP001      if (nArgs)
//STRIP001      {
//STRIP001          pDesc->aDefArgOpt   = new BOOL[nArgs];
//STRIP001          pDesc->aDefArgNames = new String*[nArgs];
//STRIP001          pDesc->aDefArgDescs = new String*[nArgs];
//STRIP001          for (j = 0; j < nArgs; j++)
//STRIP001          {
//STRIP001              pDesc->aDefArgOpt[j] = FALSE;
//STRIP001              pAddInFuncData->GetParamDesc( aArgName, aArgDesc, j+1 );
//STRIP001              if ( aArgName.Len() )
//STRIP001                  pDesc->aDefArgNames[j] = new String( aArgName );
//STRIP001              else
//STRIP001              {
//STRIP001                  switch (pAddInFuncData->GetParamType(j+1))
//STRIP001                  {
//STRIP001                      case PTR_DOUBLE:
//STRIP001                          pDesc->aDefArgNames[j] = new String( aDefArgNameValue );
//STRIP001                          break;
//STRIP001                      case PTR_STRING:
//STRIP001                          pDesc->aDefArgNames[j] = new String( aDefArgNameString );
//STRIP001                          break;
//STRIP001                      case PTR_DOUBLE_ARR:
//STRIP001                          pDesc->aDefArgNames[j] = new String( aDefArgNameValues );
//STRIP001                          break;
//STRIP001                      case PTR_STRING_ARR:
//STRIP001                          pDesc->aDefArgNames[j] = new String( aDefArgNameStrings );
//STRIP001                          break;
//STRIP001                      case PTR_CELL_ARR:
//STRIP001                          pDesc->aDefArgNames[j] = new String( aDefArgNameCells );
//STRIP001                          break;
//STRIP001                      default:
//STRIP001                          pDesc->aDefArgNames[j] = new String( aDefArgNameNone );
//STRIP001                          break;
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( aArgDesc.Len() )
//STRIP001                  pDesc->aDefArgDescs[j] = new String( aArgDesc );
//STRIP001              else
//STRIP001              {
//STRIP001                  switch (pAddInFuncData->GetParamType(j+1))
//STRIP001                  {
//STRIP001                      case PTR_DOUBLE:
//STRIP001                          pDesc->aDefArgDescs[j] = new String( aDefArgDescValue );
//STRIP001                          break;
//STRIP001                      case PTR_STRING:
//STRIP001                          pDesc->aDefArgDescs[j] = new String( aDefArgDescString );
//STRIP001                          break;
//STRIP001                      case PTR_DOUBLE_ARR:
//STRIP001                          pDesc->aDefArgDescs[j] = new String( aDefArgDescValues );
//STRIP001                          break;
//STRIP001                      case PTR_STRING_ARR:
//STRIP001                          pDesc->aDefArgDescs[j] = new String( aDefArgDescStrings );
//STRIP001                          break;
//STRIP001                      case PTR_CELL_ARR:
//STRIP001                          pDesc->aDefArgDescs[j] = new String( aDefArgDescCells );
//STRIP001                          break;
//STRIP001                      default:
//STRIP001                          pDesc->aDefArgDescs[j] = new String( aDefArgDescNone );
//STRIP001                          break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001 //       pDesc->nHelpId    = 0;
//STRIP001
//STRIP001      aFunctionList.Insert(pDesc, LIST_APPEND);
//STRIP001      nStrLen = (*(pDesc->pFuncName)).Len();
//STRIP001      if ( nStrLen > nMaxFuncNameLen)
//STRIP001          nMaxFuncNameLen = nStrLen;
//STRIP001  }
//STRIP001
//STRIP001  //  StarOne AddIns
//STRIP001
//STRIP001  ScUnoAddInCollection* pUnoAddIns = ScGlobal::GetAddInCollection();
//STRIP001  long nUnoCount = pUnoAddIns->GetFuncCount();
//STRIP001  for (long nFunc=0; nFunc<nUnoCount; nFunc++)
//STRIP001  {
//STRIP001      pDesc = new ScFuncDesc;
//STRIP001      pDesc->nFIndex = nNextId++;
//STRIP001
//STRIP001      if ( pUnoAddIns->FillFunctionDesc( nFunc, *pDesc ) )
//STRIP001      {
//STRIP001          aFunctionList.Insert(pDesc, LIST_APPEND);
//STRIP001          nStrLen = (*(pDesc->pFuncName)).Len();
//STRIP001          if (nStrLen > nMaxFuncNameLen)
//STRIP001              nMaxFuncNameLen = nStrLen;
//STRIP001      }
//STRIP001      else
//STRIP001          delete pDesc;
//STRIP001  }
}

//------------------------------------------------------------------------

/*N*/ ScFunctionList::~ScFunctionList()
/*N*/ {
/*N*/   ScFuncDesc* pDesc = (ScFuncDesc*)aFunctionList.First();
/*N*/   while (pDesc)
/*N*/   {
/*N*/       delete pDesc;
/*N*/       pDesc = (ScFuncDesc*)aFunctionList.Next();
/*N*/   }
/*N*/ }


//========================================================================
// class ScFuncDesc:

/*N*/ ScFuncDesc::ScFuncDesc()
/*N*/   :   nFIndex         (0),
/*N*/       nCategory       (0),
/*N*/       pFuncName       (NULL),
/*N*/       pFuncDesc       (NULL),
/*N*/       nArgCount       (0),
/*N*/       aDefArgNames    (NULL),
/*N*/       aDefArgDescs    (NULL),
/*N*/       aDefArgOpt      (NULL),
/*N*/       nHelpId         (0)
/*N*/ {}

//------------------------------------------------------------------------

/*N*/ ScFuncDesc::~ScFuncDesc()
/*N*/ {
/*N*/   USHORT      nArgs;
/*N*/
/*N*/   nArgs = nArgCount;
/*N*/   if (nArgs >= VAR_ARGS) nArgs -= VAR_ARGS-1;
/*N*/   if (nArgs)
/*N*/   {
/*?*/       for (USHORT i=0; i<nArgs; i++ )
/*?*/       {
/*?*/           delete aDefArgNames[i];
/*?*/           delete aDefArgDescs[i];
/*?*/       }
/*?*/       delete [] aDefArgNames;
/*?*/       delete [] aDefArgDescs;
/*?*/       delete [] aDefArgOpt;
/*N*/   }
/*N*/   if(pFuncName)
/*?*/       delete pFuncName;
/*N*/
/*N*/   if(pFuncDesc)
/*?*/       delete pFuncDesc;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String ScFuncDesc::GetSignature() const
//STRIP001 {
//STRIP001  String aSig;
//STRIP001
//STRIP001  if(pFuncName)
//STRIP001  {
//STRIP001      aSig = *pFuncName;
//STRIP001      if ( nArgCount > 0 )
//STRIP001      {
//STRIP001          aSig.AppendAscii(RTL_CONSTASCII_STRINGPARAM( "( " ));
//STRIP001          if ( nArgCount < VAR_ARGS )
//STRIP001          {
//STRIP001              for ( USHORT i=0; i<nArgCount; i++ )
//STRIP001              {
//STRIP001                  aSig += *(aDefArgNames[i]);
//STRIP001                  if ( i != nArgCount-1 )
//STRIP001                      aSig.AppendAscii(RTL_CONSTASCII_STRINGPARAM( "; " ));
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              USHORT nFix = nArgCount - VAR_ARGS;
//STRIP001              for ( USHORT nArg = 0; nArg < nFix; nArg++ )
//STRIP001              {
//STRIP001                  aSig += *(aDefArgNames[nArg]);
//STRIP001                  aSig.AppendAscii(RTL_CONSTASCII_STRINGPARAM( "; " ));
//STRIP001              }
//STRIP001              aSig += *(aDefArgNames[nFix]);
//STRIP001              aSig += '1';
//STRIP001              aSig.AppendAscii(RTL_CONSTASCII_STRINGPARAM( "; " ));
//STRIP001              aSig += *(aDefArgNames[nFix]);
//STRIP001              aSig += '2';
//STRIP001              aSig.AppendAscii(RTL_CONSTASCII_STRINGPARAM( "; ... " ));
//STRIP001          }
//STRIP001
//STRIP001             aSig.Append( 0xA0 ).Append( ')' );
//STRIP001      }
//STRIP001      else
//STRIP001          aSig.AppendAscii(RTL_CONSTASCII_STRINGPARAM( "()" ));
//STRIP001  }
//STRIP001  return aSig;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String ScFuncDesc::GetFormulaString( String** aArgArr ) const
//STRIP001 {
//STRIP001  String aFormula;
//STRIP001
//STRIP001  if(pFuncName)
//STRIP001  {
//STRIP001      aFormula= *pFuncName;
//STRIP001
//STRIP001      aFormula += '(';
//STRIP001
//STRIP001      if ( nArgCount > 0 && aArgArr )
//STRIP001      {
//STRIP001          BOOL bLastArg = ( aArgArr[0]->Len() == 0 );
//STRIP001
//STRIP001          if ( !bLastArg )
//STRIP001          {
//STRIP001              for ( USHORT i=0; i<nArgCount && !bLastArg; i++ )
//STRIP001              {
//STRIP001                  aFormula += *(aArgArr[i]);
//STRIP001
//STRIP001                  if ( i < (nArgCount-1) )
//STRIP001                  {
//STRIP001                      bLastArg = !( aArgArr[i+1]->Len() > 0 );
//STRIP001                      if ( !bLastArg )
//STRIP001                          aFormula += ';';
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      aFormula += ')';
//STRIP001  }
//STRIP001  return aFormula;
//STRIP001 }

//========================================================================
// class ScFunctionMgr:

/*N*/ScFunctionMgr::ScFunctionMgr()
/*N*/   :   pFuncList   ( ScGlobal::GetStarCalcFunctionList() ),
/*N*/       pCurCatList ( NULL )
/*N*/{
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*N*/ DBG_ASSERT( pFuncList, "Funktionsliste nicht gefunden." );
//STRIP001  ULONG       nCount  = pFuncList->GetCount();
//STRIP001  ScFuncDesc* pDesc;
//STRIP001  List*       pRootList;
//STRIP001  ULONG       n;
//STRIP001
//STRIP001  for ( USHORT i=0; i<MAX_FUNCCAT; i++ )                  // Kategorie-Listen erstellen
//STRIP001      aCatLists[i] = new List;
//STRIP001
//STRIP001  pRootList = aCatLists[0];                               // Gesamtliste ("Alle") erstellen
//STRIP001  for ( n=0; n<nCount; n++ )
//STRIP001  {
//STRIP001      ULONG nTmpCnt=0;
//STRIP001      pDesc = pFuncList->GetFunction(n);
//STRIP001      for (nTmpCnt = 0; nTmpCnt < n; nTmpCnt++)
//STRIP001      {
//STRIP001          // ist zwar case-sensitiv, aber Umlaute muessen richtig einsortiert werden
//STRIP001
//STRIP001          ScFuncDesc* pTmpDesc = (ScFuncDesc*)pRootList->GetObject(nTmpCnt);
//STRIP001          if ( ScGlobal::pCaseCollator->compareString(
//STRIP001                      *pDesc->pFuncName, *pTmpDesc->pFuncName ) == COMPARE_LESS )
//STRIP001              break;
//STRIP001      }
//STRIP001      pRootList->Insert(pDesc, nTmpCnt);                  // Einsortieren
//STRIP001  }
//STRIP001
//STRIP001  for ( n=0; n<nCount; n++ )                              // in Gruppenlisten kopieren
//STRIP001  {
//STRIP001      pDesc = (ScFuncDesc*)pRootList->GetObject(n);
//STRIP001      DBG_ASSERT((pDesc->nCategory) < MAX_FUNCCAT, "Unbekannte Kategorie");
//STRIP001      if ((pDesc->nCategory) < MAX_FUNCCAT)
//STRIP001          aCatLists[pDesc->nCategory]->Insert(pDesc, LIST_APPEND);
//STRIP001  }
}

//------------------------------------------------------------------------

/*N*/ ScFunctionMgr::~ScFunctionMgr()
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 for (USHORT i = 0; i < MAX_FUNCCAT; i++)
//STRIP001      delete aCatLists[i];
//STRIP001 //   delete pFuncList;       // Macht später die App
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 ScFuncDesc* ScFunctionMgr::Get( const String& rFName )
//STRIP001 {
//STRIP001  ScFuncDesc* pDesc = NULL;
//STRIP001  if (rFName.Len() <= pFuncList->GetMaxFuncNameLen())
//STRIP001      for (pDesc = First(0); pDesc; pDesc = Next())
//STRIP001          if (rFName.EqualsIgnoreCaseAscii(*(pDesc->pFuncName)))
//STRIP001              break;
//STRIP001  return pDesc;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScFuncDesc* ScFunctionMgr::Get( USHORT nFIndex )
//STRIP001 {
//STRIP001  ScFuncDesc* pDesc;
//STRIP001  for (pDesc = First(0); pDesc; pDesc = Next())
//STRIP001      if (pDesc->nFIndex == nFIndex)
//STRIP001          break;
//STRIP001  return pDesc;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScFuncDesc*  ScFunctionMgr::First( USHORT nCategory )
//STRIP001 {
//STRIP001  DBG_ASSERT( nCategory < MAX_FUNCCAT, "Unbekannte Kategorie" );
//STRIP001
//STRIP001  if ( nCategory < MAX_FUNCCAT )
//STRIP001  {
//STRIP001      pCurCatList = aCatLists[nCategory];
//STRIP001      return (ScFuncDesc*)pCurCatList->First();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pCurCatList = NULL;
//STRIP001      return NULL;
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScFuncDesc* ScFunctionMgr::Next()
//STRIP001 {
//STRIP001  if ( pCurCatList )
//STRIP001      return (ScFuncDesc*)pCurCatList->Next();
//STRIP001  else
//STRIP001      return NULL;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ String ColToAlpha( const USHORT nCol )
/*N*/ {
/*N*/   String aStr;
/*N*/
/*N*/   if ( nCol < 26 )
/*N*/       aStr = (sal_Unicode) ( 'A' + nCol );
/*N*/   else
/*N*/   {
/*N*/       aStr  = (sal_Unicode) ( 'A' + ( nCol / 26 ) - 1 );
/*N*/       aStr += (sal_Unicode) ( 'A' + ( nCol % 26 ) );
/*N*/   }
/*N*/
/*N*/   return aStr;
/*N*/ }

}
