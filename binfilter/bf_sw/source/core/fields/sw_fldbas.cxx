/*************************************************************************
 *
 *  $RCSfile: sw_fldbas.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:24:25 $
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

#include <math.h>
#ifdef MAC
#include <stdlib.h>
#endif
#include <float.h>

#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif
#ifndef _ZFORLIST_HXX //autogen
#include <svtools/zforlist.hxx>
#endif
#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _FRAME_HXX
#include <frame.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
namespace binfilter {


using namespace ::com::sun::star;

/*N*/ USHORT lcl_GetLanguageOfFormat( USHORT nLng, ULONG nFmt,
/*N*/                               const SvNumberFormatter& rFormatter )
/*N*/ {
/*N*/   if( nLng == LANGUAGE_NONE ) // wegen Bug #60010
/*?*/       nLng = LANGUAGE_SYSTEM;
/*N*/   else if( nLng == ::binfilter::GetAppLanguage() )
/*N*/       switch( rFormatter.GetIndexTableOffset( nFmt ))
/*N*/       {
/*?*/       case NF_NUMBER_SYSTEM:
/*?*/       case NF_DATE_SYSTEM_SHORT:
/*?*/       case NF_DATE_SYSTEM_LONG:
/*?*/       case NF_DATETIME_SYSTEM_SHORT_HHMM:
/*?*/           nLng = LANGUAGE_SYSTEM;
/*?*/           break;
/*N*/       }
/*N*/   return nLng;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Globals
 --------------------------------------------------------------------*/
// Array der Feldname

/*N*/ SvStringsDtor* SwFieldType::pFldNames = 0;

/*N*/ DBG_NAME(SwFieldType)

//STRIP001  USHORT __FAR_DATA aTypeTab[] = {
//STRIP001  /* RES_DBFLD            */      TYP_DBFLD,
//STRIP001  /* RES_USERFLD          */      TYP_USERFLD,
//STRIP001  /* RES_FILENAMEFLD      */      TYP_FILENAMEFLD,
//STRIP001  /* RES_DBNAMEFLD        */      TYP_DBNAMEFLD,
//STRIP001  /* RES_DATEFLD          */      TYP_DATEFLD,
//STRIP001  /* RES_TIMEFLD          */      TYP_TIMEFLD,
//STRIP001  /* RES_PAGENUMBERFLD    */      TYP_PAGENUMBERFLD,  // dynamisch
//STRIP001  /* RES_AUTHORFLD        */      TYP_AUTHORFLD,
//STRIP001  /* RES_CHAPTERFLD       */      TYP_CHAPTERFLD,
//STRIP001  /* RES_DOCSTATFLD       */      TYP_DOCSTATFLD,
//STRIP001  /* RES_GETEXPFLD        */      TYP_GETFLD,         // dynamisch
//STRIP001  /* RES_SETEXPFLD        */      TYP_SETFLD,         // dynamisch
//STRIP001  /* RES_GETREFFLD        */      TYP_GETREFFLD,
//STRIP001  /* RES_HIDDENTXTFLD     */      TYP_HIDDENTXTFLD,
//STRIP001  /* RES_POSTITFLD        */      TYP_POSTITFLD,
//STRIP001  /* RES_FIXDATEFLD       */      TYP_FIXDATEFLD,
//STRIP001  /* RES_FIXTIMEFLD       */      TYP_FIXTIMEFLD,
//STRIP001  /* RES_REGFLD           */      0,                  // alt
//STRIP001  /* RES_VARREGFLD        */      0,                  // alt
//STRIP001  /* RES_SETREFFLD        */      TYP_SETREFFLD,
//STRIP001  /* RES_INPUTFLD         */      TYP_INPUTFLD,
//STRIP001  /* RES_MACROFLD         */      TYP_MACROFLD,
//STRIP001  /* RES_DDEFLD           */      TYP_DDEFLD,
//STRIP001  /* RES_TABLEFLD         */      TYP_FORMELFLD,
//STRIP001  /* RES_HIDDENPARAFLD    */      TYP_HIDDENPARAFLD,
//STRIP001  /* RES_DOCINFOFLD       */      TYP_DOCINFOFLD,
//STRIP001  /* RES_TEMPLNAMEFLD     */      TYP_TEMPLNAMEFLD,
//STRIP001  /* RES_DBNEXTSETFLD     */      TYP_DBNEXTSETFLD,
//STRIP001  /* RES_DBNUMSETFLD      */      TYP_DBNUMSETFLD,
//STRIP001  /* RES_DBSETNUMBERFLD   */      TYP_DBSETNUMBERFLD,
//STRIP001  /* RES_EXTUSERFLD       */      TYP_EXTUSERFLD,
//STRIP001  /* RES_REFPAGESETFLD    */      TYP_SETREFPAGEFLD,
//STRIP001  /* RES_REFPAGEGETFLD    */      TYP_GETREFPAGEFLD,
//STRIP001  /* RES_INTERNETFLD      */      TYP_INTERNETFLD,
//STRIP001  /* RES_JUMPEDITFLD      */      TYP_JUMPEDITFLD,
//STRIP001  /* RES_SCRIPTFLD        */      TYP_SCRIPTFLD,
//STRIP001  /* RES_DATETIMEFLD      */      0,                  // dynamisch
//STRIP001  /* RES_AUTHORITY        */      TYP_AUTHORITY,
//STRIP001  /* RES_COMBINED_CHARS   */      TYP_COMBINED_CHARS,
//STRIP001  /* RES_DROPDOWN         */      TYP_DROPDOWN
//STRIP001  };
        // ????? TYP_USRINPFLD,



/*N*/ const String& SwFieldType::GetTypeStr(USHORT nTypeId)
/*N*/ {
/*N*/   if( !pFldNames )
/*N*/       _GetFldName();
/*N*/
/*N*/   if( nTypeId < SwFieldType::pFldNames->Count() )
/*N*/       return *SwFieldType::pFldNames->GetObject( nTypeId );
/*N*/   else
/*?*/       return aEmptyStr;
/*N*/ }

/*---------------------------------------------------
 Jedes Feld referenziert einen Feldtypen, der fuer
 jedes Dokument einmalig ist.
 --------------------------------------------------*/

/*N*/ SwFieldType::SwFieldType( USHORT nWhichId )
/*N*/   : SwModify(0),
/*N*/   nWhich( nWhichId )
/*N*/ {
/*N*/   DBG_CTOR( SwFieldType, 0 );
/*N*/ }

/*N*/ #ifndef PRODUCT

/*N*/ SwFieldType::~SwFieldType()
/*N*/ {
/*N*/   DBG_DTOR( SwFieldType, 0 );
/*N*/ }

/*N*/ #endif

/*N*/ const String& SwFieldType::GetName() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

//STRIP001 BOOL SwFieldType::QueryValue( uno::Any& rVal, BYTE nMId ) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }
//STRIP001 BOOL SwFieldType::PutValue( const uno::Any& rVal, BYTE nMId )
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Basisklasse aller Felder
                    Felder referenzieren einen Feldtyp
                    Felder sind n-mal vorhanden, Feldtypen nur einmal
 --------------------------------------------------------------------*/

/*N*/ SwField::SwField(SwFieldType* pTyp, ULONG nFmt, USHORT nLng) :
/*N*/   nFormat(nFmt),
/*N*/     nLang(nLng),
/*N*/     bIsAutomaticLanguage(TRUE)
/*N*/ {
/*N*/   ASSERT( pTyp, "SwField: ungueltiger SwFieldType" );
/*N*/   pType = pTyp;
/*N*/ }

/*N*/ SwField::~SwField()
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Statt Umweg ueber den Typ
 --------------------------------------------------------------------*/

/*N*/ #ifndef PRODUCT
/*N*/ USHORT SwField::Which() const
/*N*/ {
/*N*/   ASSERT(pType, "Kein Typ vorhanden");
/*N*/   return pType->Which();
/*N*/ }
/*N*/ #endif

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 USHORT SwField::GetResId(USHORT nTypeId, BOOL& bAmbigous)
//STRIP001 {
//STRIP001  static USHORT __READONLY_DATA aTypeTab[] = {
//STRIP001   RES_DATETIMEFLD   ,/*      TYP_DATEFLD,        */
//STRIP001   RES_DATETIMEFLD   ,/*      TYP_TIMEFLD,        */
//STRIP001   RES_FILENAMEFLD   ,/*      TYP_FILENAMEFLD,    */
//STRIP001   RES_DBNAMEFLD     ,/*      TYP_DBNAMEFLD,      */
//STRIP001   RES_CHAPTERFLD    ,/*      TYP_CHAPTERFLD,     */
//STRIP001   RES_PAGENUMBERFLD ,/*      TYP_PAGENUMBERFLD,  */// dynamisch
//STRIP001   RES_DOCSTATFLD    ,/*      TYP_DOCSTATFLD,     */
//STRIP001   RES_AUTHORFLD     ,/*      TYP_AUTHORFLD,      */
//STRIP001   RES_SETEXPFLD     ,/*      TYP_SETFLD,         */// dynamisch
//STRIP001   RES_GETEXPFLD     ,/*      TYP_GETFLD,         */// dynamisch
//STRIP001   RES_TABLEFLD      ,/*      TYP_FORMELFLD,      */
//STRIP001   RES_HIDDENTXTFLD  ,/*      TYP_HIDDENTXTFLD,   */
//STRIP001   RES_SETREFFLD     ,/*      TYP_SETREFFLD,      */
//STRIP001   RES_GETREFFLD     ,/*      TYP_GETREFFLD,      */
//STRIP001   RES_DDEFLD        ,/*      TYP_DDEFLD,         */
//STRIP001   RES_MACROFLD      ,/*      TYP_MACROFLD,       */
//STRIP001   RES_INPUTFLD      ,/*      TYP_INPUTFLD,       */
//STRIP001   RES_HIDDENPARAFLD ,/*      TYP_HIDDENPARAFLD,  */
//STRIP001   RES_DOCINFOFLD    ,/*      TYP_DOCINFOFLD,     */
//STRIP001   RES_DBFLD         ,/*      TYP_DBFLD,          */
//STRIP001   RES_USERFLD       ,/*      TYP_USERFLD,        */
//STRIP001   RES_POSTITFLD     ,/*      TYP_POSTITFLD,      */
//STRIP001   RES_TEMPLNAMEFLD  ,/*      TYP_TEMPLNAMEFLD,   */
//STRIP001   RES_SETEXPFLD     ,/*      TYP_SEQFLD          */
//STRIP001   RES_DBNEXTSETFLD  ,/*      TYP_DBNEXTSETFLD,   */
//STRIP001   RES_DBNUMSETFLD   ,/*      TYP_DBNUMSETFLD,    */
//STRIP001   RES_DBSETNUMBERFLD,/*      TYP_DBSETNUMBERFLD, */
//STRIP001   RES_HIDDENTXTFLD  ,/*      TYP_CONDTXTFLD      */
//STRIP001   RES_PAGENUMBERFLD ,/*      TYP_NEXTPAGEFLD     */
//STRIP001   RES_PAGENUMBERFLD ,/*      TYP_PREVPAGEFLD     */
//STRIP001   RES_EXTUSERFLD    ,/*      TYP_EXTUSERFLD      */
//STRIP001   RES_DATETIMEFLD   ,/*      TYP_FIXDATEFLD,     */
//STRIP001   RES_DATETIMEFLD   ,/*      TYP_FIXTIMEFLD,     */
//STRIP001   RES_SETEXPFLD     ,/*      TYP_SETINPFLD       */
//STRIP001   USHRT_MAX         ,/*      TYP_USRINPFLD       */
//STRIP001   RES_REFPAGESETFLD ,/*      TYP_SETREFPAGEFLD   */
//STRIP001   RES_REFPAGEGETFLD ,/*      TYP_GETREFPAGEFLD   */
//STRIP001   RES_INTERNETFLD   ,/*      TYP_INTERNETFLD     */
//STRIP001   RES_JUMPEDITFLD   ,/*      TYP_JUMPEDITFLD     */
//STRIP001   RES_SCRIPTFLD,     /*      TYP_SCRIPTFLD       */
//STRIP001   RES_AUTHORITY,     /*      TYP_AUTHORITY       */
//STRIP001   RES_COMBINED_CHARS,/*      TYP_COMBINED_CHARS  */
//STRIP001   RES_DROPDOWN       /*      TYP_DROPDOWN        */
//STRIP001  };
//STRIP001
//STRIP001  switch( nTypeId )
//STRIP001  {
//STRIP001      case TYP_CONDTXTFLD:
//STRIP001      case TYP_HIDDENTXTFLD:
//STRIP001      case TYP_USRINPFLD:
//STRIP001      case TYP_PAGENUMBERFLD:
//STRIP001      case TYP_PREVPAGEFLD:
//STRIP001      case TYP_NEXTPAGEFLD:
//STRIP001      case TYP_SEQFLD:
//STRIP001      case TYP_SETFLD:
//STRIP001      case TYP_SETINPFLD:
//STRIP001      case TYP_FORMELFLD:
//STRIP001          bAmbigous = TRUE;
//STRIP001          break;
//STRIP001      default: bAmbigous = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return aTypeTab[ nTypeId ];
//STRIP001 }



/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 USHORT SwField::GetTypeId() const
//STRIP001 {
//STRIP001
//STRIP001  USHORT nRet;
//STRIP001  switch( pType->Which() )
//STRIP001  {
//STRIP001  case RES_DATETIMEFLD:
//STRIP001      if (GetSubType() & FIXEDFLD)
//STRIP001          nRet = GetSubType() & DATEFLD ? TYP_FIXDATEFLD : TYP_FIXTIMEFLD;
//STRIP001      else
//STRIP001          nRet = GetSubType() & DATEFLD ? TYP_DATEFLD : TYP_TIMEFLD;
//STRIP001      break;
//STRIP001  case RES_GETEXPFLD:
//STRIP001      nRet = GSE_FORMULA & GetSubType() ? TYP_FORMELFLD : TYP_GETFLD;
//STRIP001      break;
//STRIP001
//STRIP001  case RES_HIDDENTXTFLD:
//STRIP001      nRet = GetSubType();
//STRIP001      break;
//STRIP001
//STRIP001  case RES_SETEXPFLD:
//STRIP001      if( GSE_SEQ & GetSubType() )
//STRIP001          nRet = TYP_SEQFLD;
//STRIP001      else if( ((SwSetExpField*)this)->GetInputFlag() )
//STRIP001          nRet = TYP_SETINPFLD;
//STRIP001      else
//STRIP001          nRet = TYP_SETFLD;
//STRIP001      break;
//STRIP001
//STRIP001  case RES_PAGENUMBERFLD:
//STRIP001      nRet = GetSubType();
//STRIP001      if( PG_NEXT == nRet )
//STRIP001          nRet = TYP_NEXTPAGEFLD;
//STRIP001      else if( PG_PREV == nRet )
//STRIP001          nRet = TYP_PREVPAGEFLD;
//STRIP001      else
//STRIP001          nRet = TYP_PAGENUMBERFLD;
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      nRet = aTypeTab[ pType->Which() ];
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: liefert den Namen oder den Inhalt
 --------------------------------------------------------------------*/

/*N*/ String SwField::GetCntnt( BOOL bName ) const
/*N*/ {
/*N*/   String sRet;
/*N*/   if( bName )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nTypeId = GetTypeId();
//STRIP001 /*?*/        if( RES_DATETIMEFLD == GetTyp()->Which() )
//STRIP001 /*?*/            nTypeId = GetSubType() & DATEFLD ? TYP_DATEFLD : TYP_TIMEFLD;
//STRIP001 /*?*/
//STRIP001 /*?*/        sRet = SwFieldType::GetTypeStr( nTypeId );
//STRIP001 /*?*/        if( IsFixed() )
//STRIP001 /*?*/            ( sRet += ' ' ) += ViewShell::GetShellRes()->aFixedStr;
/*N*/   }
/*N*/   else
/*N*/       sRet = Expand();
/*N*/   return sRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Parameter setzen auslesen
 --------------------------------------------------------------------*/

/*N*/ const String& SwField::GetPar1() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

/*N*/ String SwField::GetPar2() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

/*N*/ String SwField::GetFormula() const
/*N*/ {
/*N*/   return GetPar2();
/*N*/ }

//STRIP001 void SwField::SetPar1(const String& rStr)
//STRIP001 {}

//STRIP001 void SwField::SetPar2(const String& rStr)
//STRIP001 {}

/*N*/ USHORT SwField::GetSubType() const
/*N*/ {
/*N*/ //    ASSERT(0, "Sorry Not implemented");
/*N*/   return 0;
/*N*/ }

//STRIP001 void SwField::SetSubType(USHORT nType)
//STRIP001 {
//STRIP001 //   ASSERT(0, "Sorry Not implemented");
//STRIP001 }

/*N*/ BOOL  SwField::QueryValue( uno::Any& rVal, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/     switch( nMId )
/*N*/     {
/*N*/         case FIELD_PROP_BOOL4:
/*N*/         {
/*N*/             BOOL bFixed = !bIsAutomaticLanguage;
/*N*/             rVal.setValue(&bFixed, ::getCppuBooleanType());
/*N*/         }
/*N*/         break;
/*N*/         default:
/*N*/             DBG_ERROR("illegal property");
/*N*/     }
/*N*/     return TRUE;
/*N*/ }
/*N*/ BOOL SwField::PutValue( const uno::Any& rVal, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/     switch( nMId )
/*N*/     {
/*N*/         case FIELD_PROP_BOOL4:
/*N*/         {
/*N*/             BOOL bFixed;
/*N*/             if(rVal >>= bFixed)
/*N*/                 bIsAutomaticLanguage = !bFixed;
/*N*/         }
/*N*/         break;
/*N*/         default:
/*N*/             DBG_ERROR("illegal property");
/*N*/     }
/*N*/     return TRUE;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:   neuen Typ setzen
                    (wird fuer das Kopieren zwischen Dokumenten benutzt)
                    muss immer vom gleichen Typ sein.
 --------------------------------------------------------------------*/

//STRIP001 SwFieldType* SwField::ChgTyp( SwFieldType* pNewType )
//STRIP001 {
//STRIP001  ASSERT( pNewType && pNewType->Which() == pType->Which(),
//STRIP001          "kein Typ oder ungleiche Typen" );
//STRIP001
//STRIP001  SwFieldType* pOld = pType;
//STRIP001  pType = pNewType;
//STRIP001  return pOld;
//STRIP001 }

    // hat das Feld eine Action auf dem ClickHandler ? (z.B. INetFelder,..)
//STRIP001 FASTBOOL SwField::HasClickHdl() const
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  switch( pType->Which() )
//STRIP001  {
//STRIP001  case RES_INTERNETFLD:
//STRIP001  case RES_JUMPEDITFLD:
//STRIP001  case RES_GETREFFLD:
//STRIP001  case RES_MACROFLD:
//STRIP001  case RES_INPUTFLD:
//STRIP001  case RES_DROPDOWN :
//STRIP001      bRet = TRUE;
//STRIP001      break;
//STRIP001
//STRIP001  case RES_SETEXPFLD:
//STRIP001      bRet = ((SwSetExpField*)this)->GetInputFlag();
//STRIP001      break;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ void SwField::SetLanguage(USHORT nLng)
/*N*/ {
/*N*/   nLang = nLng;
/*N*/ }

/*N*/ void SwField::ChangeFormat(ULONG n)
/*N*/ {
/*N*/   nFormat = n;
/*N*/ }

/*N*/ FASTBOOL SwField::IsFixed() const
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;
/*N*/   switch( pType->Which() )
/*N*/   {
/*N*/   case RES_FIXDATEFLD:
/*N*/   case RES_FIXTIMEFLD:
/*?*/       bRet = TRUE;
/*?*/       break;
/*N*/
/*N*/   case RES_DATETIMEFLD:
/*N*/       bRet = 0 != (GetSubType() & FIXEDFLD);
/*N*/       break;
/*N*/
/*N*/   case RES_EXTUSERFLD:
/*N*/   case RES_AUTHORFLD:
/*N*/       bRet = 0 != (GetFormat() & AF_FIXED);
/*N*/       break;
/*N*/
/*N*/   case RES_FILENAMEFLD:
/*N*/       bRet = 0 != (GetFormat() & FF_FIXED);
/*N*/       break;
/*N*/
/*N*/   case RES_DOCINFOFLD:
/*N*/       bRet = 0 != (GetSubType() & DI_SUB_FIXED);
/*N*/       break;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Sortierte Feldliste aller Felder usw.
 --------------------------------------------------------------------*/

//STRIP001 SwFieldList::SwFieldList(SwEditShell* pShell)
//STRIP001  : pSh(pShell)
//STRIP001 {
//STRIP001  // Hier die Liste aller Eingabefelder sortiert erstellen
//STRIP001  pSrtLst = new _SetGetExpFlds();
//STRIP001 }

//STRIP001 void SwFieldList::InsertFields(USHORT nTypeId, const String* pName)
//STRIP001 {
//STRIP001  const USHORT nSize = pSh->GetFldTypeCount();
//STRIP001
//STRIP001  // Alle Typen abklappern
//STRIP001
//STRIP001  for(USHORT i=0; i < nSize; ++i)
//STRIP001  {
//STRIP001      SwFieldType* pFldType = pSh->GetFldType(i);
//STRIP001      if( nTypeId == pFldType->Which() )
//STRIP001      {
//STRIP001          if( pName )
//STRIP001          {
//STRIP001              String aMacTmp( pFldType->GetName() );
//STRIP001              if( *pName != aMacTmp )
//STRIP001                  continue;
//STRIP001          }
//STRIP001
//STRIP001          SwClientIter aIter( *pFldType );
//STRIP001          for( SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
//STRIP001                  pFld; pFld = (SwFmtFld*)aIter.Next() )
//STRIP001              if( pFld->GetTxtFld() )
//STRIP001              {
//STRIP001                  const SwTxtFld* pTxtFld = pFld->GetTxtFld();
//STRIP001                  const SwTxtNode& rTxtNode = pTxtFld->GetTxtNode();
//STRIP001                  if( rTxtNode.GetNodes().IsDocNodes() )
//STRIP001                  {
//STRIP001                      SwNodeIndex aIdx( rTxtNode );
//STRIP001                      _SetGetExpFld* pNew = new _SetGetExpFld(aIdx, pTxtFld );
//STRIP001                      pSrtLst->Insert( pNew );
//STRIP001                  }
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 SwFieldList::~SwFieldList()
//STRIP001 {
//STRIP001  delete pSrtLst;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Felder aus der Liste in sortierter Reihenfolge
 --------------------------------------------------------------------*/

//STRIP001 USHORT SwFieldList::Count() const
//STRIP001 {
//STRIP001  return pSrtLst->Count();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   von der CursorPos das naechste und das Letzte Feld
                    in der Liste anfahren
 --------------------------------------------------------------------*/

//STRIP001 SwField* SwFieldList::GetNextField() const
//STRIP001 {
//STRIP001  SwPaM* pCrsr = pSh->GetCrsr();
//STRIP001  ULONG nNdPos = pCrsr->GetPoint()->nNode.GetIndex();
//STRIP001  USHORT nCntPos = pCrsr->GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001  const USHORT nSize = pSrtLst->Count();
//STRIP001  for(USHORT i = 0; i < nSize; ++i )
//STRIP001  {
//STRIP001      _SetGetExpFld* pFnd = (*pSrtLst)[i];
//STRIP001      if( pFnd->GetNode() > nNdPos || ( pFnd->GetNode() == nNdPos &&
//STRIP001          pFnd->GetCntnt() >= nCntPos ))
//STRIP001          return (SwField*)pFnd->GetFld()->GetFld().GetFld();
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 SwField* SwFieldList::GetLastField() const
//STRIP001 {
//STRIP001  SwPaM* pCrsr = pSh->GetCrsr();
//STRIP001  ULONG nNdPos = pCrsr->GetPoint()->nNode.GetIndex();
//STRIP001  USHORT nCntPos = pCrsr->GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001  for( USHORT n = pSrtLst->Count(); n; )
//STRIP001  {
//STRIP001      _SetGetExpFld* pFnd = (*pSrtLst)[ --n ];
//STRIP001      if( pFnd->GetNode() < nNdPos || ( pFnd->GetNode() == nNdPos &&
//STRIP001          pFnd->GetCntnt() <= nCntPos ))
//STRIP001          return (SwField*)pFnd->GetFld()->GetFld().GetFld();
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Numerierung expandieren
 --------------------------------------------------------------------*/

/*N*/ String FormatNumber(USHORT nNum, ULONG nFormat)
/*N*/ {
/*N*/     if(SVX_NUM_PAGEDESC == nFormat)
/*?*/         return  String::CreateFromInt32( nNum );
/*N*/     SvxNumberType aNumber;
/*N*/
/*N*/   ASSERT(nFormat != SVX_NUM_NUMBER_NONE, "Falsches Nummern-Format" );
/*N*/
/*N*/   aNumber.SetNumberingType((sal_Int16)nFormat);
/*N*/   return aNumber.GetNumStr(nNum);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: CTOR SwValueFieldType
 --------------------------------------------------------------------*/

/*N*/ SwValueFieldType::SwValueFieldType( SwDoc* pDocPtr, USHORT nWhichId )
/*N*/   : SwFieldType(nWhichId),
/*N*/   pDoc(pDocPtr),
/*N*/   bUseFormat(TRUE)
/*N*/ {
/*N*/ }

//STRIP001 SwValueFieldType::SwValueFieldType( const SwValueFieldType& rTyp )
//STRIP001  : SwFieldType(rTyp.Which()),
//STRIP001  pDoc(rTyp.GetDoc()),
//STRIP001  bUseFormat(rTyp.UseFormat())
//STRIP001 {
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Wert formatiert als String zurueckgeben
 --------------------------------------------------------------------*/

/*N*/ String SwValueFieldType::ExpandValue( const double& rVal,
/*N*/                                       ULONG nFmt, USHORT nLng) const
/*N*/ {
/*N*/   if (rVal >= DBL_MAX)        // FehlerString fuer Calculator
/*?*/       return ViewShell::GetShellRes()->aCalc_Error;
/*N*/
/*N*/   String sExpand;
/*N*/   SvNumberFormatter* pFormatter = pDoc->GetNumberFormatter();
/*N*/   Color* pCol = 0;
/*N*/
/*N*/   // wegen Bug #60010
/*N*/   USHORT nFmtLng = ::binfilter::lcl_GetLanguageOfFormat( nLng, nFmt, *pFormatter );
/*N*/
/*N*/   if( nFmt < SV_COUNTRY_LANGUAGE_OFFSET && LANGUAGE_SYSTEM != nFmtLng )
/*N*/   {
/*?*/       short nType = NUMBERFORMAT_DEFINED;
/*?*/       xub_StrLen nDummy;
/*?*/
/*?*/       const SvNumberformat* pEntry = pFormatter->GetEntry(nFmt);
/*?*/
/*?*/       if (pEntry && nLng != pEntry->GetLanguage())
/*?*/       {
/*?*/           ULONG nNewFormat = pFormatter->GetFormatForLanguageIfBuiltIn(nFmt,
/*?*/                                                   (LanguageType)nFmtLng);
/*?*/
/*?*/           if (nNewFormat == nFmt)
/*?*/           {
/*?*/               // Warscheinlich benutzerdefiniertes Format
/*?*/               String sFmt(pEntry->GetFormatstring());
/*?*/
/*?*/               pFormatter->PutandConvertEntry(sFmt, nDummy, nType, nFmt,
/*?*/                                       pEntry->GetLanguage(), nFmtLng );
/*?*/           }
/*?*/           else
/*?*/               nFmt = nNewFormat;
/*?*/       }
/*?*/       ASSERT(pEntry, "Unbekanntes Zahlenformat!");
/*N*/   }
/*N*/
/*N*/   if( pFormatter->IsTextFormat( nFmt ) )
/*N*/   {
/*?*/       String sValue;
/*?*/       DoubleToString(sValue, rVal, nFmtLng);
/*?*/       pFormatter->GetOutputString(sValue, nFmt, sExpand, &pCol);
/*N*/   }
/*N*/   else
/*N*/       pFormatter->GetOutputString(rVal, nFmt, sExpand, &pCol);
/*N*/
/*N*/   return sExpand;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwValueFieldType::DoubleToString( String &rValue, const double &rVal,
//STRIP001                                      ULONG nFmt) const
//STRIP001 {
//STRIP001  SvNumberFormatter* pFormatter = pDoc->GetNumberFormatter();
//STRIP001  const SvNumberformat* pEntry = pFormatter->GetEntry(nFmt);
//STRIP001
//STRIP001  if (pEntry)
//STRIP001      DoubleToString(rValue, rVal, pEntry->GetLanguage());
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwValueFieldType::DoubleToString( String &rValue, const double &rVal,
/*N*/                                       USHORT nLng ) const
/*N*/ {
/*N*/   SvNumberFormatter* pFormatter = pDoc->GetNumberFormatter();
/*N*/
/*N*/   // wegen Bug #60010
/*N*/   if( nLng == LANGUAGE_NONE ) // wegen Bug #60010
/*?*/       nLng = LANGUAGE_SYSTEM;
/*N*/
/*N*/   pFormatter->ChangeIntl( nLng ); // Separator in der richtigen Sprache besorgen
/*N*/   rValue = ::rtl::math::doubleToUString( rVal, rtl_math_StringFormat_F, 12,
/*N*/                                   pFormatter->GetDecSep(), TRUE );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: CTOR SwValueField
 --------------------------------------------------------------------*/

/*N*/ SwValueField::SwValueField( SwValueFieldType* pFldType, ULONG nFmt,
/*N*/                           USHORT nLang, const double fVal )
/*N*/   : SwField(pFldType, nFmt, nLang),
/*N*/   fValue(fVal)
/*N*/ {
/*N*/ }

//STRIP001 SwValueField::SwValueField( const SwValueField& rFld )
//STRIP001  : SwField(rFld),
//STRIP001  fValue(rFld.GetValue())
//STRIP001 {
//STRIP001 }

/*N*/ SwValueField::~SwValueField()
/*N*/ {
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung:   neuen Typ setzen
                    (wird fuer das Kopieren zwischen Dokumenten benutzt)
                    muss immer vom gleichen Typ sein.
 --------------------------------------------------------------------*/

//STRIP001 SwFieldType* SwValueField::ChgTyp( SwFieldType* pNewType )
//STRIP001 {
//STRIP001  SwDoc* pNewDoc = ((SwValueFieldType *)pNewType)->GetDoc();
//STRIP001  SwDoc* pDoc    = GetDoc();
//STRIP001
//STRIP001  if( pNewDoc && pDoc && pDoc != pNewDoc)
//STRIP001  {
//STRIP001      SvNumberFormatter* pFormatter = pNewDoc->GetNumberFormatter();
//STRIP001
//STRIP001      if( pFormatter && pFormatter->HasMergeFmtTbl() &&
//STRIP001          ((SwValueFieldType *)GetTyp())->UseFormat() )
//STRIP001          SetFormat(pFormatter->GetMergeFmtIndex( GetFormat() ));
//STRIP001  }
//STRIP001
//STRIP001  return SwField::ChgTyp(pNewType);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Format aendern
 --------------------------------------------------------------------*/
/*
 Was sollte das denn?
void SwValueField::ChangeFormat(ULONG n)
{
    nFormat = n;
}

/*--------------------------------------------------------------------
    Beschreibung: Format in Office-Sprache ermitteln
 --------------------------------------------------------------------*/

//STRIP001 ULONG SwValueField::GetSystemFormat(SvNumberFormatter* pFormatter, ULONG nFmt)
//STRIP001 {
//STRIP001  const SvNumberformat* pEntry = pFormatter->GetEntry(nFmt);
//STRIP001  USHORT nLng = SvxLocaleToLanguage( GetAppLocaleData().getLocale() );
//STRIP001
//STRIP001  if (pEntry && nLng != pEntry->GetLanguage())
//STRIP001  {
//STRIP001      ULONG nNewFormat = pFormatter->GetFormatForLanguageIfBuiltIn(nFmt,
//STRIP001                                                      (LanguageType)nLng);
//STRIP001
//STRIP001      if (nNewFormat == nFmt)
//STRIP001      {
//STRIP001          // Warscheinlich benutzerdefiniertes Format
//STRIP001          short nType = NUMBERFORMAT_DEFINED;
//STRIP001          xub_StrLen nDummy;
//STRIP001
//STRIP001          String sFmt(pEntry->GetFormatstring());
//STRIP001
//STRIP001          ULONG nFormat = nFmt;
//STRIP001          pFormatter->PutandConvertEntry(sFmt, nDummy, nType,
//STRIP001                              nFormat, pEntry->GetLanguage(), nLng);
//STRIP001          nFmt = nFormat;
//STRIP001      }
//STRIP001      else
//STRIP001          nFmt = nNewFormat;
//STRIP001  }
//STRIP001
//STRIP001  return nFmt;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Sprache im Format anpassen
 --------------------------------------------------------------------*/

/*N*/ void SwValueField::SetLanguage( USHORT nLng )
/*N*/ {
/*N*/     if( IsAutomaticLanguage() &&
/*N*/             ((SwValueFieldType *)GetTyp())->UseFormat() &&
/*N*/       GetFormat() != ULONG_MAX )
/*N*/   {
/*N*/       // wegen Bug #60010
/*N*/       SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
/*N*/       USHORT nFmtLng = ::binfilter::lcl_GetLanguageOfFormat( nLng, GetFormat(),
/*N*/                                                   *pFormatter );
/*N*/
/*N*/       if( (GetFormat() >= SV_COUNTRY_LANGUAGE_OFFSET ||
/*N*/            LANGUAGE_SYSTEM != nFmtLng ) &&
/*N*/           !(Which() == RES_USERFLD && (GetSubType()&SUB_CMD) ) )
/*N*/       {
/*N*/           const SvNumberformat* pEntry = pFormatter->GetEntry(GetFormat());
/*N*/
/*N*/           if( pEntry && nFmtLng != pEntry->GetLanguage() )
/*N*/           {
/*N*/               ULONG nNewFormat = pFormatter->GetFormatForLanguageIfBuiltIn(
/*N*/                                       GetFormat(), (LanguageType)nFmtLng );
/*N*/
/*N*/               if( nNewFormat == GetFormat() )
/*N*/               {
/*?*/                   // Warscheinlich benutzerdefiniertes Format
/*?*/                   short nType = NUMBERFORMAT_DEFINED;
/*?*/                   xub_StrLen nDummy;
/*?*/                   String sFmt( pEntry->GetFormatstring() );
/*?*/                   pFormatter->PutandConvertEntry( sFmt, nDummy, nType,
/*?*/                                                   nNewFormat,
/*?*/                                                   pEntry->GetLanguage(),
/*?*/                                                   nFmtLng );
/*N*/               }
/*N*/               SetFormat( nNewFormat );
/*N*/           }
/*N*/           ASSERT(pEntry, "Unbekanntes Zahlenformat!");
/*N*/       }
/*N*/   }
/*N*/
/*N*/   SwField::SetLanguage(nLng);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ double SwValueField::GetValue() const
/*N*/ {
/*N*/   return fValue;
/*N*/ }

/*N*/ void SwValueField::SetValue( const double& rVal )
/*N*/ {
/*N*/   fValue = rVal;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwFormulaField
 --------------------------------------------------------------------*/

/*N*/ SwFormulaField::SwFormulaField( SwValueFieldType* pFldType, ULONG nFmt, const double fVal)
/*N*/   : SwValueField(pFldType, nFmt, LANGUAGE_SYSTEM, fVal)
/*N*/ {
/*N*/ }

//STRIP001 SwFormulaField::SwFormulaField( const SwFormulaField& rFld )
//STRIP001  : SwValueField((SwValueFieldType *)rFld.GetTyp(), rFld.GetFormat(),
//STRIP001                  rFld.GetLanguage(), rFld.GetValue())
//STRIP001 {
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ String SwFormulaField::GetFormula() const
/*N*/ {
/*N*/   return sFormula;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwFormulaField::SetFormula(const String& rStr)
/*N*/ {
/*N*/   sFormula = rStr;
/*N*/
/*N*/   ULONG nFmt(GetFormat());
/*N*/
/*N*/   if( nFmt && ULONG_MAX != nFmt )
/*N*/   {
/*N*/       xub_StrLen nPos = 0;
/*N*/       double fValue;
/*N*/       if( SwCalc::Str2Double( rStr, nPos, fValue, GetDoc() ) )
/*N*/           SwValueField::SetValue( fValue );
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwFormulaField::SetExpandedFormula( const String& rStr )
//STRIP001 {
//STRIP001  ULONG nFmt(GetFormat());
//STRIP001
//STRIP001  if (nFmt && nFmt != ULONG_MAX && ((SwValueFieldType *)GetTyp())->UseFormat())
//STRIP001  {
//STRIP001      double fValue;
//STRIP001
//STRIP001      SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
//STRIP001
//STRIP001      if (pFormatter->IsNumberFormat(rStr, nFmt, fValue))
//STRIP001      {
//STRIP001          SwValueField::SetValue(fValue);
//STRIP001          sFormula.Erase();
//STRIP001
//STRIP001          ((SwValueFieldType *)GetTyp())->DoubleToString(sFormula, fValue, nFmt);
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001  sFormula = rStr;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 String SwFormulaField::GetExpandedFormula() const
//STRIP001 {
//STRIP001  ULONG nFmt(GetFormat());
//STRIP001
//STRIP001  if (nFmt && nFmt != ULONG_MAX && ((SwValueFieldType *)GetTyp())->UseFormat())
//STRIP001  {
//STRIP001      String sFormattedValue;
//STRIP001      Color* pCol = 0;
//STRIP001
//STRIP001      SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
//STRIP001
//STRIP001      if (pFormatter->IsTextFormat(nFmt))
//STRIP001      {
//STRIP001          String sValue;
//STRIP001          ((SwValueFieldType *)GetTyp())->DoubleToString(sValue, GetValue(), nFmt);
//STRIP001          pFormatter->GetOutputString(sValue, nFmt, sFormattedValue, &pCol);
//STRIP001      }
//STRIP001      else
//STRIP001          pFormatter->GetOutputString(GetValue(), nFmt, sFormattedValue, &pCol);
//STRIP001
//STRIP001      return sFormattedValue;
//STRIP001  }
//STRIP001  else
//STRIP001      return GetFormula();
//STRIP001 }
}
