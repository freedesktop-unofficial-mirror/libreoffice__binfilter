/*************************************************************************
 *
 *  $RCSfile: sw_docufld.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:36 $
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

#include <tools/pstm.hxx>

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _COM_SUN_STAR_TEXT_SETVARIABLETYPE_HPP_
#include <com/sun/star/text/SetVariableType.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXTFIELDSSUPPLIER_HPP_
#include <com/sun/star/text/XTextFieldsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_USERDATAPART_HPP_
#include <com/sun/star/text/UserDataPart.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_CHAPTERFORMAT_HPP_
#include <com/sun/star/text/ChapterFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXTFIELD_HPP_
#include <com/sun/star/text/XTextField.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_PLACEHOLDERTYPE_HPP_
#include <com/sun/star/text/PlaceholderType.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_TEMPLATEDISPLAYFORMAT_HPP_
#include <com/sun/star/text/TemplateDisplayFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_USERFIELDFORMAT_HPP_
#include <com/sun/star/text/UserFieldFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_PAGENUMBERTYPE_HPP_
#include <com/sun/star/text/PageNumberType.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_REFERENCEFIELDPART_HPP_
#include <com/sun/star/text/ReferenceFieldPart.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_FilenameDisplayFormat_HPP_
#include <com/sun/star/text/FilenameDisplayFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XDEPENDENTTEXTFIELD_HPP_
#include <com/sun/star/text/XDependentTextField.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_DOCUMENTSTATISTIC_HPP_
#include <com/sun/star/text/DocumentStatistic.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_DATE_HPP_
#include <com/sun/star/util/Date.hpp>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#include <comphelper/types.hxx>

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _INTN_HXX //autogen
#include <tools/intn.hxx>
#endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_USEROPTIONS_HXX
#include <svtools/useroptions.hxx>
#endif

#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFXDOCINF_HXX //autogen
#include <bf_sfx2/docinf.hxx>
#endif
#ifndef _SFXDOCTEMPL_HXX //autogen
#include <bf_sfx2/doctempl.hxx>
#endif
#ifndef _SVX_ADRITEM_HXX
#include <bf_svx/adritem.hxx>
#endif


#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#ifndef _DOCSTAT_HXX //autogen
#include <docstat.hxx>
#endif
#ifndef _PAGEDESC_HXX //autogen
#include <pagedesc.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>      // AuthorField
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>      //
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>       //
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif
#ifndef _SWUNOHELPER_HXX
#include <swunohelper.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#define URL_DECODE  INetURLObject::DECODE_UNAMBIGUOUS
namespace binfilter {
extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr ); //STRIP008
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::rtl;
/*--------------------------------------------------------------------
    Beschreibung: SwPageNumberFieldType
 --------------------------------------------------------------------*/

/*N*/ SwPageNumberFieldType::SwPageNumberFieldType()
/*N*/   : SwFieldType( RES_PAGENUMBERFLD ),
/*N*/   nNumberingType( SVX_NUM_ARABIC ),
/*N*/   nNum( 0 ),
/*N*/   nMax( USHRT_MAX ),
/*N*/   bVirtuell( sal_False )
/*N*/ {
/*N*/ }

/*N*/ String& SwPageNumberFieldType::Expand( sal_uInt32 nFmt, short nOff,
/*N*/                               const String& rUserStr, String& rRet ) const
/*N*/ {
/*N*/   sal_uInt32 nTmpFmt = (SVX_NUM_PAGEDESC == nFmt) ? (sal_uInt32)nNumberingType : nFmt;
/*N*/   long nTmp = nNum + nOff;
/*N*/
/*N*/   if( 0 >= nTmp || SVX_NUM_NUMBER_NONE == nTmpFmt || (!bVirtuell && nTmp > nMax) )
/*N*/       rRet = aEmptyStr;
/*N*/   else if( SVX_NUM_CHAR_SPECIAL == nTmpFmt )
/*?*/       rRet = rUserStr;
/*N*/   else
/*N*/       rRet = FormatNumber( (sal_uInt16)nTmp, nTmpFmt );
/*N*/   return rRet;
/*N*/ }

/*N*/ SwFieldType* SwPageNumberFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwPageNumberFieldType *pTmp = new SwPageNumberFieldType();
//STRIP001
//STRIP001  pTmp->nNum       = nNum;
//STRIP001  pTmp->nMax       = nMax;
//STRIP001  pTmp->nNumberingType = nNumberingType;
//STRIP001  pTmp->bVirtuell  = bVirtuell;
//STRIP001
//STRIP001  return pTmp;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Verschiedene Expandierung
 --------------------------------------------------------------------*/

/*N*/ void SwPageNumberFieldType::ChangeExpansion( SwDoc* pDoc, sal_uInt16 nPage,
/*N*/                                           sal_uInt16 nNumPages, sal_Bool bVirt,
/*N*/                                           const sal_Int16* pNumFmt )
/*N*/ {
/*N*/   nNum = nPage;
/*N*/   nMax = nNumPages;
/*N*/   if( pNumFmt )
/*N*/       nNumberingType = *pNumFmt;
/*N*/
/*N*/   bVirtuell = sal_False;
/*N*/   if( bVirt )
/*N*/   {
/*N*/       // dann muss das Flag ueberprueft werden, denn das Layout setzt
/*N*/       // es NIE zurueck
/*N*/       const SfxItemPool &rPool = pDoc->GetAttrPool();
/*N*/       const SwFmtPageDesc *pDesc;
/*N*/       sal_uInt16 nMaxItems = rPool.GetItemCount( RES_PAGEDESC );
/*N*/       for( sal_uInt16 n = 0; n < nMaxItems; ++n )
/*N*/           if( 0 != (pDesc = (SwFmtPageDesc*)rPool.GetItem( RES_PAGEDESC, n ) )
/*N*/               && pDesc->GetNumOffset() && pDesc->GetDefinedIn() )
/*N*/           {
/*N*/               if( pDesc->GetDefinedIn()->ISA( SwCntntNode ))
/*N*/               {
/*N*/                   SwClientIter aIter( *(SwModify*)pDesc->GetDefinedIn() );
/*N*/                   if( aIter.First( TYPE( SwFrm ) ) )
/*N*/                   {
/*N*/                       bVirtuell = sal_True;
/*N*/                       break;
/*N*/                   }
/*N*/               }
/*N*/               else if( pDesc->GetDefinedIn()->ISA( SwFmt ))
/*N*/               {
/*N*/                   SwAutoFmtGetDocNode aGetHt( &pDoc->GetNodes() );
/*N*/                   bVirtuell = !pDesc->GetDefinedIn()->GetInfo( aGetHt );
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwPageNumberField
 --------------------------------------------------------------------*/

/*N*/ SwPageNumberField::SwPageNumberField(SwPageNumberFieldType* pTyp,
/*N*/                                    sal_uInt16 nSub, sal_uInt32 nFmt, short nOff)
/*N*/   : SwField(pTyp, nFmt), nOffset(nOff), nSubType(nSub)
/*N*/ {
/*N*/ }

/*N*/ String SwPageNumberField::Expand() const
/*N*/ {
/*N*/   String sRet;
/*N*/   SwPageNumberFieldType* pFldType = (SwPageNumberFieldType*)GetTyp();
/*N*/
/*N*/   if( PG_NEXT == nSubType && 1 != nOffset )
/*N*/   {
/*?*/       if( pFldType->Expand( GetFormat(), 1, sUserStr, sRet ).Len() )
/*?*/           pFldType->Expand( GetFormat(), nOffset, sUserStr, sRet );
/*N*/   }
/*N*/   else if( PG_PREV == nSubType && -1 != nOffset )
/*N*/   {
/*?*/       if( pFldType->Expand( GetFormat(), -1, sUserStr, sRet ).Len() )
/*?*/           pFldType->Expand( GetFormat(), nOffset, sUserStr, sRet );
/*N*/   }
/*N*/   else
/*N*/       pFldType->Expand( GetFormat(), nOffset, sUserStr, sRet );
/*N*/   return sRet;
/*N*/ }

/*N*/ SwField* SwPageNumberField::Copy() const
/*N*/ {
/*N*/   SwPageNumberField *pTmp =
/*N*/       new SwPageNumberField((SwPageNumberFieldType*)GetTyp(), nSubType, GetFormat(), nOffset);
/*N*/   pTmp->SetLanguage( GetLanguage() );
/*N*/   pTmp->SetUserString( sUserStr );
/*N*/   return pTmp;
/*N*/ }

/*N*/ String SwPageNumberField::GetPar2() const
/*N*/ {
/*N*/   return String::CreateFromInt32(nOffset);
/*N*/ }

//STRIP001 void SwPageNumberField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  nOffset = (short)rStr.ToInt32();
//STRIP001 }

/*N*/ sal_uInt16 SwPageNumberField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

/*-----------------05.03.98 10:25-------------------

--------------------------------------------------*/
/*N*/ BOOL SwPageNumberField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= (sal_Int16)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_USHORT1:
/*N*/       rAny <<= nOffset;
/*N*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       {
/*N*/           text::PageNumberType eType;
/*N*/           eType = text::PageNumberType_CURRENT;
/*N*/           if(nSubType == PG_PREV)
/*?*/               eType = text::PageNumberType_PREV;
/*N*/           else if(nSubType == PG_NEXT)
/*?*/               eType = text::PageNumberType_NEXT;
/*N*/           rAny.setValue(&eType, ::getCppuType((const text::PageNumberType*)0));
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*?*/       rAny <<= OUString(sUserStr);
/*?*/       break;
/*?*/
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 10:25-------------------

--------------------------------------------------*/
/*N*/ BOOL SwPageNumberField::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     BOOL bRet = TRUE;
/*N*/   sal_Int16 nSet;
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_FORMAT:
/*?*/       rAny >>= nSet;
/*?*/
/*?*/       // TODO: woher kommen die defines?
/*?*/       if(nSet <= SVX_NUM_PAGEDESC )
/*?*/           SetFormat(nSet);
/*?*/       else
/*?*/           //exception(wrong_value)
/*?*/           ;
/*?*/       break;
/*?*/   case FIELD_PROP_USHORT1:
/*?*/       rAny >>= nSet;
/*?*/       nOffset = nSet;
/*?*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/         switch( SWUnoHelper::GetEnumAsInt32( rAny ) )
/*N*/       {
/*N*/           case text::PageNumberType_CURRENT:
/*N*/               nSubType = PG_RANDOM;
/*N*/           break;
/*N*/           case text::PageNumberType_PREV:
/*?*/               nSubType = PG_PREV;
/*?*/           break;
/*?*/             case text::PageNumberType_NEXT:
/*?*/                 nSubType = PG_NEXT;
/*?*/           break;
/*?*/           default:
/*?*/                 bRet = FALSE;
/*N*/       }
/*N*/       break;
/*?*/   case FIELD_PROP_PAR1:
/*?*/       ::binfilter::GetString( rAny, sUserStr );
/*?*/       break;
/*?*/
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/     return bRet;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwAuthorFieldType
 --------------------------------------------------------------------*/

/*N*/ SwAuthorFieldType::SwAuthorFieldType()
/*N*/   : SwFieldType( RES_AUTHORFLD )
/*N*/ {
/*N*/ }

/*N*/ String SwAuthorFieldType::Expand(sal_uInt32 nFmt) const
/*N*/ {
/*N*/   String sRet;
/*N*/   SvtUserOptions aOpt;
/*N*/   if((nFmt & 0xff) == AF_NAME)
/*N*/       sRet = aOpt.GetFullName();
/*N*/   else
/*N*/       sRet = aOpt.GetID();
/*N*/   return sRet;
/*N*/ }

/*N*/ SwFieldType* SwAuthorFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwAuthorFieldType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwAuthorField
 --------------------------------------------------------------------*/

/*N*/ SwAuthorField::SwAuthorField(SwAuthorFieldType* pTyp, sal_uInt32 nFmt)
/*N*/   : SwField(pTyp, nFmt)
/*N*/ {
/*N*/   aContent = ((SwAuthorFieldType*)GetTyp())->Expand(GetFormat());
/*N*/ }

/*N*/ String SwAuthorField::Expand() const
/*N*/ {
/*N*/   if (!IsFixed())
/*N*/       ((SwAuthorField*)this)->aContent =
/*N*/                   ((SwAuthorFieldType*)GetTyp())->Expand(GetFormat());
/*N*/
/*N*/   return aContent;
/*N*/ }

/*N*/ SwField* SwAuthorField::Copy() const
/*N*/ {
/*N*/   SwAuthorField *pTmp = new SwAuthorField( (SwAuthorFieldType*)GetTyp(),
/*N*/                                               GetFormat());
/*N*/   pTmp->SetExpansion(aContent);
/*N*/   return pTmp;
/*N*/ }

/*-----------------05.03.98 11:15-------------------

--------------------------------------------------*/
/*N*/ BOOL SwAuthorField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/   sal_Bool bVal;
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       bVal = GetFormat() == AF_NAME;
/*N*/       rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/       break;
/*N*/
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       bVal = IsFixed();
/*N*/       rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/       break;
/*N*/
/*N*/   case FIELD_PROP_PAR1:
/*?*/       rAny <<= ::rtl::OUString(GetContent());
/*?*/       break;
/*?*/
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 11:15-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwAuthorField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      SetFormat( *(sal_Bool*)rAny.getValue() ? AF_NAME : AF_SHORTCUT );
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_BOOL2:
//STRIP001      if( *(sal_Bool*)rAny.getValue() )
//STRIP001          SetFormat( GetFormat() | AF_FIXED);
//STRIP001      else
//STRIP001          SetFormat( GetFormat() & ~AF_FIXED);
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      ::GetString( rAny, aContent );
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: SwFileNameFieldType
 --------------------------------------------------------------------*/

/*N*/ SwFileNameFieldType::SwFileNameFieldType(SwDoc *pDocument)
/*N*/   : SwFieldType( RES_FILENAMEFLD )
/*N*/ {
/*N*/   pDoc = pDocument;
/*N*/ }

/*M*/ String SwFileNameFieldType::Expand(sal_uInt32 nFmt) const
/*M*/ {
/*M*/   String aRet;
/*M*/   const SwDocShell* pDShell = pDoc->GetDocShell();
/*M*/   if( pDShell && pDShell->HasName() )
/*M*/   {
/*M*/       const INetURLObject& rURLObj = pDShell->GetMedium()->GetURLObject();
/*M*/       switch( nFmt & ~FF_FIXED )
/*M*/       {
/*M*/           case FF_PATH:
/*M*/               {
/*M*/                   if( INET_PROT_FILE == rURLObj.GetProtocol() )
/*M*/                   {
/*M*/                       INetURLObject aTemp(rURLObj);
/*M*/                       aTemp.removeSegment();
/*M*/                         // #101947# last slash should belong to the pathname
/*M*/                       aRet = aTemp.PathToFileName();//GetFull();
/*M*/                   }
/*M*/                   else
/*M*/                   {
/*M*/                       aRet = URIHelper::removePassword(
/*M*/                                   rURLObj.GetMainURL( INetURLObject::NO_DECODE ),
/*M*/                                   INetURLObject::WAS_ENCODED, URL_DECODE );
/*M*/                       aRet.Erase( aRet.Search( rURLObj.GetLastName(
/*M*/                                                   URL_DECODE ) ) );
/*M*/                   }
/*M*/               }
/*M*/               break;
/*M*/
/*M*/           case FF_NAME:
/*M*/               aRet = rURLObj.GetLastName( URL_DECODE );
/*M*/               break;
/*M*/
/*M*/           case FF_NAME_NOEXT:
/*M*/               aRet = rURLObj.GetBase();
/*M*/               break;
/*M*/
/*M*/           default:
/*M*/               if( INET_PROT_FILE == rURLObj.GetProtocol() )
/*M*/                   aRet = rURLObj.GetFull();
/*M*/               else
/*M*/                   aRet = URIHelper::removePassword(
/*M*/                                   rURLObj.GetMainURL( INetURLObject::NO_DECODE ),
/*M*/                                   INetURLObject::WAS_ENCODED, URL_DECODE );
/*M*/       }
/*M*/   }
/*M*/   return aRet;
/*M*/ }

/*N*/ SwFieldType* SwFileNameFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwFieldType *pTmp = new SwFileNameFieldType(pDoc);
//STRIP001  return pTmp;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwFileNameField
 --------------------------------------------------------------------*/

/*N*/ SwFileNameField::SwFileNameField(SwFileNameFieldType* pTyp, sal_uInt32 nFmt)
/*N*/   : SwField(pTyp, nFmt)
/*N*/ {
/*N*/   aContent = ((SwFileNameFieldType*)GetTyp())->Expand(GetFormat());
/*N*/ }

/*N*/ String SwFileNameField::Expand() const
/*N*/ {
/*N*/   if (!IsFixed())
/*N*/       ((SwFileNameField*)this)->aContent = ((SwFileNameFieldType*)GetTyp())->Expand(GetFormat());
/*N*/
/*N*/   return aContent;
/*N*/ }

/*N*/ SwField* SwFileNameField::Copy() const
/*N*/ {
/*N*/   SwFileNameField *pTmp =
/*N*/       new SwFileNameField((SwFileNameFieldType*)GetTyp(), GetFormat());
/*N*/   pTmp->SetExpansion(aContent);
/*N*/
/*N*/   return pTmp;
/*N*/ }

/*-----------------05.03.98 08:59-------------------

--------------------------------------------------*/
/*N*/ BOOL SwFileNameField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       {
/*N*/           sal_Int16 nRet;
/*N*/           switch( GetFormat() &(~FF_FIXED) )
/*N*/           {
/*N*/               case FF_PATH:
/*N*/                   nRet = text::FilenameDisplayFormat::PATH;
/*N*/               break;
/*N*/               case FF_NAME_NOEXT:
/*N*/                   nRet = text::FilenameDisplayFormat::NAME;
/*N*/               break;
/*N*/               case FF_NAME:
/*N*/                   nRet = text::FilenameDisplayFormat::NAME_AND_EXT;
/*N*/               break;
/*N*/               default:    nRet = text::FilenameDisplayFormat::FULL;
/*N*/           }
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       {
/*N*/           BOOL bVal = IsFixed();
/*N*/           rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case FIELD_PROP_PAR3:
/*?*/       rAny <<= OUString(GetContent());
/*?*/       break;
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 09:01-------------------

--------------------------------------------------*/
/*N*/ BOOL SwFileNameField::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       {
/*N*/           //JP 24.10.2001: int32 because in UnoField.cxx a putvalue is
/*N*/           //              called with a int32 value! But normally we need
/*N*/           //              here only a int16
/*N*/           sal_Int32 nType;
/*N*/           rAny >>= nType;
/*N*/           BOOL bFixed = IsFixed();
/*N*/           switch( nType )
/*N*/           {
/*N*/               case text::FilenameDisplayFormat::PATH:
/*N*/                   nType = FF_PATH;
/*N*/               break;
/*N*/               case text::FilenameDisplayFormat::NAME:
/*N*/                   nType = FF_NAME_NOEXT;
/*N*/               break;
/*N*/               case text::FilenameDisplayFormat::NAME_AND_EXT:
/*N*/                   nType = FF_NAME;
/*N*/               break;
/*N*/               default:    nType = FF_PATHNAME;
/*N*/           }
/*N*/           if(bFixed)
/*?*/               nType |= FF_FIXED;
/*N*/           SetFormat(nType);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case FIELD_PROP_BOOL2:
/*?*/       if( *(sal_Bool*)rAny.getValue() )
/*?*/           SetFormat( GetFormat() | FF_FIXED);
/*?*/       else
/*?*/           SetFormat( GetFormat() & ~FF_FIXED);
/*?*/       break;
/*?*/
/*?*/   case FIELD_PROP_PAR3:
/*?*/       ::binfilter::GetString( rAny, aContent );
/*?*/       break;
/*?*/
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwTemplNameFieldType
 --------------------------------------------------------------------*/

/*N*/ SwTemplNameFieldType::SwTemplNameFieldType(SwDoc *pDocument)
/*N*/   : SwFieldType( RES_TEMPLNAMEFLD )
/*N*/ {
/*N*/   pDoc = pDocument;
/*N*/ }

/*N*/ String SwTemplNameFieldType::Expand(sal_uInt32 nFmt) const
/*N*/ {
/*N*/   ASSERT(nFmt >= FF_BEGIN && nFmt < FF_END, "Expand: kein guelt. Fmt!" );
/*N*/
/*N*/   String aRet;
/*N*/   const SfxDocumentInfo* pDInfo = pDoc->GetpInfo();
/*N*/
/*N*/   if( pDInfo )
/*N*/   {
/*N*/       if( FF_UI_NAME == nFmt )
/*N*/           aRet = pDInfo->GetTemplateName();
/*N*/       else if( pDInfo->GetTemplateFileName().Len() )
/*N*/       {
/*N*/           if( FF_UI_RANGE == nFmt )
/*N*/           {
/*N*/               // fuers besorgen vom RegionNamen !!
/*N*/               SfxDocumentTemplates aFac;
/*N*/               aFac.Construct();
/*N*/               String sTmp;
/*N*/               aFac.GetLogicNames( pDInfo->GetTemplateFileName(), aRet, sTmp );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               INetURLObject aPathName( pDInfo->GetTemplateFileName() );
/*N*/               if( FF_NAME == nFmt )
/*N*/                   aRet = aPathName.GetName(URL_DECODE);
/*N*/               else if( FF_NAME_NOEXT == nFmt )
/*N*/                   aRet = aPathName.GetBase();
/*N*/               else
/*N*/               {
/*N*/                   if( FF_PATH == nFmt )
/*N*/                   {
/*N*/                       aPathName.removeSegment();
/*N*/                       aRet = aPathName.GetFull();
/*N*/                   }
/*N*/                   else
/*N*/                       aRet = aPathName.GetFull();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return aRet;
/*N*/ }

/*N*/ SwFieldType* SwTemplNameFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwFieldType *pTmp = new SwTemplNameFieldType(pDoc);
//STRIP001  return pTmp;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwTemplNameField
 --------------------------------------------------------------------*/

/*N*/ SwTemplNameField::SwTemplNameField(SwTemplNameFieldType* pTyp, sal_uInt32 nFmt)
/*N*/   : SwField(pTyp, nFmt)
/*N*/ {}

/*N*/ String SwTemplNameField::Expand() const
/*N*/ {
/*N*/   return((SwTemplNameFieldType*)GetTyp())->Expand(GetFormat());
/*N*/ }

/*N*/ SwField* SwTemplNameField::Copy() const
/*N*/ {
/*N*/   SwTemplNameField *pTmp =
/*N*/       new SwTemplNameField((SwTemplNameFieldType*)GetTyp(), GetFormat());
/*N*/   return pTmp;
/*N*/ }

/*-----------------05.03.98 08:59-------------------

--------------------------------------------------*/
/*N*/ BOOL SwTemplNameField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch ( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       {
/*N*/           sal_Int16 nRet;
/*N*/           switch( GetFormat() )
/*N*/           {
/*N*/               case FF_PATH:       nRet = text::FilenameDisplayFormat::PATH; break;
/*N*/               case FF_NAME_NOEXT: nRet = text::FilenameDisplayFormat::NAME; break;
/*N*/               case FF_NAME:       nRet = text::FilenameDisplayFormat::NAME_AND_EXT; break;
/*N*/               case FF_UI_RANGE:   nRet = text::TemplateDisplayFormat::AREA; break;
/*N*/               case FF_UI_NAME:    nRet = text::TemplateDisplayFormat::TITLE;  break;
/*N*/               default:    nRet = text::FilenameDisplayFormat::FULL;
/*N*/
/*N*/           }
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 09:01-------------------

--------------------------------------------------*/
/*N*/ BOOL SwTemplNameField::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch ( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       {
/*N*/           //JP 24.10.2001: int32 because in UnoField.cxx a putvalue is
/*N*/           //              called with a int32 value! But normally we need
/*N*/           //              here only a int16
/*N*/           sal_Int32 nType;
/*N*/           rAny >>= nType;
/*N*/           switch( nType )
/*N*/           {
/*N*/           case text::FilenameDisplayFormat::PATH:
/*N*/               SetFormat(FF_PATH);
/*N*/           break;
/*N*/           case text::FilenameDisplayFormat::NAME:
/*N*/               SetFormat(FF_NAME_NOEXT);
/*N*/           break;
/*N*/           case text::FilenameDisplayFormat::NAME_AND_EXT:
/*N*/               SetFormat(FF_NAME);
/*N*/           break;
/*N*/           case text::TemplateDisplayFormat::AREA  :
/*N*/               SetFormat(FF_UI_RANGE);
/*N*/           break;
/*N*/           case text::TemplateDisplayFormat::TITLE  :
/*N*/               SetFormat(FF_UI_NAME);
/*N*/           break;
/*N*/           default:    SetFormat(FF_PATHNAME);
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwDocStatFieldType
 --------------------------------------------------------------------*/

/*N*/ SwDocStatFieldType::SwDocStatFieldType(SwDoc* pDocument)
/*N*/   : SwFieldType( RES_DOCSTATFLD ), nNumberingType( SVX_NUM_ARABIC )
/*N*/ {
/*N*/   pDoc = pDocument;
/*N*/ }

/*N*/ String SwDocStatFieldType::Expand(sal_uInt16 nSubType, sal_uInt32 nFmt) const
/*N*/ {
/*N*/   sal_uInt32 nVal = 0;
/*N*/   const SwDocStat& rDStat = pDoc->GetDocStat();
/*N*/   switch( nSubType )
/*N*/   {
/*N*/       case DS_TBL:  nVal = rDStat.nTbl;   break;
/*N*/       case DS_GRF:  nVal = rDStat.nGrf;   break;
/*N*/       case DS_OLE:  nVal = rDStat.nOLE;   break;
/*N*/       case DS_PARA: nVal = rDStat.nPara;  break;
/*N*/       case DS_WORD: nVal = rDStat.nWord;  break;
/*N*/       case DS_CHAR: nVal = rDStat.nChar;  break;
/*N*/       case DS_PAGE:
/*N*/           if( pDoc->GetRootFrm() )
/*N*/               ((SwDocStat &)rDStat).nPage = pDoc->GetRootFrm()->GetPageNum();
/*N*/           nVal = rDStat.nPage;
/*N*/           if( SVX_NUM_PAGEDESC == nFmt )
/*?*/               nFmt = (sal_uInt32)nNumberingType;
/*N*/           break;
/*N*/       default:
/*?*/           ASSERT( sal_False, "SwDocStatFieldType::Expand: unbekannter SubType" );
/*N*/   }
/*N*/
/*N*/   String sRet;
/*N*/   if( nVal <= SHRT_MAX )
/*N*/       sRet = FormatNumber( (sal_uInt16)nVal, nFmt );
/*N*/   else
/*?*/       sRet = String::CreateFromInt32( nVal );
/*N*/   return sRet;
/*N*/ }

/*N*/ SwFieldType* SwDocStatFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP");return NULL; //STRIP001 //STRIP001   SwDocStatFieldType *pTmp = new SwDocStatFieldType(pDoc);
//STRIP001  return pTmp;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwDocStatFieldType
                  Aus historischen Gruenden steht in nFormat der
                  SubType
 --------------------------------------------------------------------*/

/*N*/ SwDocStatField::SwDocStatField(SwDocStatFieldType* pTyp, sal_uInt16 nSub, sal_uInt32 nFmt)
/*N*/   : SwField(pTyp, nFmt),
/*N*/   nSubType(nSub)
/*N*/ {}

/*N*/ String SwDocStatField::Expand() const
/*N*/ {
/*N*/   return((SwDocStatFieldType*)GetTyp())->Expand(nSubType, GetFormat());
/*N*/ }

/*N*/ SwField* SwDocStatField::Copy() const
/*N*/ {
/*N*/   SwDocStatField *pTmp = new SwDocStatField(
/*N*/                   (SwDocStatFieldType*)GetTyp(), nSubType, GetFormat() );
/*N*/   return pTmp;
/*N*/ }

/*N*/ sal_uInt16 SwDocStatField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

//STRIP001 void SwDocStatField::SetSubType(sal_uInt16 nSub)
//STRIP001 {
//STRIP001  nSubType = nSub;
//STRIP001 }

/*N*/ void SwDocStatField::ChangeExpansion( const SwFrm* pFrm )
/*N*/ {
/*N*/   if( DS_PAGE == nSubType && SVX_NUM_PAGEDESC == GetFormat() )
/*N*/       ((SwDocStatFieldType*)GetTyp())->SetNumFormat(
/*?*/               pFrm->FindPageFrm()->GetPageDesc()->GetNumType().GetNumberingType() );
/*N*/ }

/*-----------------05.03.98 11:38-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDocStatField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch ( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_USHORT2:
/*N*/       rAny <<= (sal_Int16)GetFormat();
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 11:38-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwDocStatField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch ( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_USHORT2:
//STRIP001      {
//STRIP001          sal_Int16 nSet;
//STRIP001          rAny >>= nSet;
//STRIP001          if(nSet <= SVX_NUM_CHARS_LOWER_LETTER_N &&
//STRIP001              nSet != SVX_NUM_CHAR_SPECIAL &&
//STRIP001                  nSet != SVX_NUM_BITMAP)
//STRIP001          {
//STRIP001              SetFormat(nSet);
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: DokumentinfoFields
 --------------------------------------------------------------------*/

/*N*/ SwDocInfoFieldType::SwDocInfoFieldType(SwDoc* pDc)
/*N*/   : SwValueFieldType( pDc, RES_DOCINFOFLD )
/*N*/ {
/*N*/ }

/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwFieldType* SwDocInfoFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP");return NULL; //STRIP001 //STRIP001   SwDocInfoFieldType* pType = new SwDocInfoFieldType(GetDoc());
//STRIP001  return pType;
/*N*/ }

/*N*/ void lcl_GetLocalDataWrapper( ULONG nLang,
/*N*/                             LocaleDataWrapper **ppAppLocalData,
/*N*/                             LocaleDataWrapper **ppLocalData )
/*N*/ {
/*N*/   *ppAppLocalData = &GetAppLocaleData();
/*N*/   *ppLocalData = *ppAppLocalData;
/*N*/   if( nLang != SvxLocaleToLanguage( (*ppLocalData)->getLocale() ) )
/*N*/       *ppLocalData = new LocaleDataWrapper(
/*N*/                       ::legacy_binfilters::getLegacyProcessServiceFactory(),
/*N*/                       SvxCreateLocale( nLang ) );
/*N*/ }

/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwDocInfoFieldType::Expand( sal_uInt16 nSub, sal_uInt32 nFormat,
/*N*/                                   sal_uInt16 nLang) const
/*N*/ {
/*N*/   String aStr;
/*N*/   LocaleDataWrapper *pAppLocalData = 0, *pLocalData = 0;
/*N*/   const SfxDocumentInfo*  pInf = GetDoc()->GetInfo();
/*N*/
/*N*/   sal_uInt16 nExtSub = nSub & 0xff00;
/*N*/   nSub &= 0xff;   // ExtendedSubTypes nicht beachten
/*N*/
/*N*/   switch(nSub)
/*N*/   {
/*N*/   case DI_TITEL:  aStr = pInf->GetTitle();    break;
/*N*/   case DI_THEMA:  aStr = pInf->GetTheme();    break;
/*N*/   case DI_KEYS:   aStr = pInf->GetKeywords(); break;
/*N*/   case DI_COMMENT:aStr = pInf->GetComment();  break;
/*N*/   case DI_INFO1:
/*N*/   case DI_INFO2:
/*N*/   case DI_INFO3:
/*N*/   case DI_INFO4:  aStr = pInf->GetUserKey(nSub - DI_INFO1).GetWord();break;
/*N*/   case DI_DOCNO:  aStr = String::CreateFromInt32(
/*N*/                                               pInf->GetDocumentNumber() );
/*N*/                   break;
/*N*/   case DI_EDIT:
/*N*/       if ( !nFormat )
/*N*/       {
/*?*/           lcl_GetLocalDataWrapper( nLang, &pAppLocalData, &pLocalData );
/*?*/           aStr = pLocalData->getTime( pInf->GetTime(), sal_False, sal_False);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/             double fVal = Time(pInf->GetTime()).GetTimeInDays();
/*N*/           aStr = ExpandValue(fVal, nFormat, nLang);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   default:
/*N*/       {
/*N*/           SfxStamp aTmp;
/*N*/           aTmp = pInf->GetCreated();
/*N*/           if( nSub == DI_CREATE )
/*N*/               ;       // das wars schon!!
/*N*/           else if( nSub == DI_CHANGE &&
/*N*/                   (pInf->GetChanged().GetTime() != aTmp.GetTime() ||
/*N*/                   (nExtSub & ~DI_SUB_FIXED) == DI_SUB_AUTHOR &&
/*N*/                   pInf->GetDocumentNumber() > 1) )
/*N*/               aTmp = pInf->GetChanged();
/*N*/           else if( nSub == DI_PRINT &&
/*N*/                   pInf->GetPrinted().GetTime() != aTmp.GetTime() )
/*N*/               aTmp = pInf->GetPrinted();
/*N*/           else
/*?*/               break;
/*N*/
/*N*/           if (aTmp.IsValid())
/*N*/           {
/*N*/               switch (nExtSub & ~DI_SUB_FIXED)
/*N*/               {
/*N*/               case DI_SUB_AUTHOR:
/*N*/                   aStr = aTmp.GetName();
/*N*/                   break;
/*N*/
/*N*/               case DI_SUB_TIME:
/*N*/                   if (!nFormat)
/*N*/                   {
/*N*/                       lcl_GetLocalDataWrapper( nLang, &pAppLocalData,
/*N*/                                                       &pLocalData );
/*N*/                       aStr = pLocalData->getTime( aTmp.GetTime(),
/*N*/                                                   sal_False, sal_False);
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       // Numberformatter anwerfen!
/*?*/                       double fVal = SwDateTimeField::GetDateTime( GetDoc(),
/*?*/                                                     aTmp.GetTime());
/*?*/                       aStr = ExpandValue(fVal, nFormat, nLang);
/*N*/                   }
/*N*/                   break;
/*N*/
/*N*/               case DI_SUB_DATE:
/*N*/                   if (!nFormat)
/*N*/                   {
/*N*/                       lcl_GetLocalDataWrapper( nLang, &pAppLocalData,
/*N*/                                                &pLocalData );
/*N*/                       aStr = pLocalData->getDate( aTmp.GetTime() );
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       // Numberformatter anwerfen!
/*?*/                       double fVal = SwDateTimeField::GetDateTime( GetDoc(),
/*?*/                                                     aTmp.GetTime());
/*?*/                       aStr = ExpandValue(fVal, nFormat, nLang);
/*N*/                   }
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   if( pAppLocalData != pLocalData )
/*N*/       delete pLocalData;
/*N*/
/*N*/   return aStr;
/*N*/ }

/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDocInfoField::SwDocInfoField(SwDocInfoFieldType* pType, sal_uInt16 nSub, sal_uInt32 nFmt) :
/*N*/   SwValueField(pType, nFmt), nSubType(nSub)
/*N*/ {
/*N*/   aContent = ((SwDocInfoFieldType*)GetTyp())->Expand(nSubType, nFmt, GetLanguage());
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwDocInfoField::Expand() const
/*N*/ {
/*N*/   if (!IsFixed()) // aContent fuer Umschaltung auf fixed mitpflegen
/*N*/       ((SwDocInfoField*)this)->aContent = ((SwDocInfoFieldType*)GetTyp())->Expand(nSubType, GetFormat(), GetLanguage());
/*N*/
/*N*/   return aContent;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwDocInfoField::GetCntnt(sal_Bool bName) const
/*N*/ {
/*N*/   if ( bName )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 String aStr(SwFieldType::GetTypeStr(GetTypeId()));
//STRIP001 /*?*/        aStr += ':';
//STRIP001 /*?*/
//STRIP001 /*?*/        sal_uInt16 nSub = nSubType & 0xff;
//STRIP001 /*?*/
//STRIP001 /*?*/        switch(nSub)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            case DI_INFO1:
//STRIP001 /*?*/            case DI_INFO2:
//STRIP001 /*?*/            case DI_INFO3:
//STRIP001 /*?*/            case DI_INFO4:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                const SfxDocumentInfo*  pInf = GetDoc()->GetInfo();
//STRIP001 /*?*/                aStr += pInf->GetUserKey(nSub - DI_INFO1).GetTitle();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/            default:
//STRIP001 /*?*/                aStr += *ViewShell::GetShellRes()->aDocInfoLst[ nSub - DI_SUBTYPE_BEGIN ];
//STRIP001 /*?*/                break;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if( IsFixed() )
//STRIP001 /*?*/            ( aStr += ' ' ) += ViewShell::GetShellRes()->aFixedStr;
//STRIP001 /*?*/        return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwField* SwDocInfoField::Copy() const
/*N*/ {
/*N*/   SwDocInfoField* pFld = new SwDocInfoField((SwDocInfoFieldType*)GetTyp(), nSubType, GetFormat());
/*N*/     pFld->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/   pFld->aContent = aContent;
/*N*/
/*N*/   return pFld;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_uInt16 SwDocInfoField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwDocInfoField::SetSubType(sal_uInt16 nSub)
//STRIP001 {
//STRIP001  nSubType = nSub;
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwDocInfoField::SetLanguage(sal_uInt16 nLng)
/*N*/ {
/*N*/   if (!GetFormat())
/*N*/       SwField::SetLanguage(nLng);
/*N*/   else
/*N*/       SwValueField::SetLanguage(nLng);
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwDocInfoField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*?*/       rAny <<= OUString(aContent);
/*?*/       break;
/*?*/
/*?*/   case FIELD_PROP_USHORT1:
/*?*/       rAny  <<= (sal_Int16)aContent.ToInt32();
/*?*/       break;
/*N*/
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           sal_Bool bVal = 0 != (nSubType & DI_SUB_FIXED);
/*N*/           rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny  <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/
/*?*/   case FIELD_PROP_DOUBLE:
/*?*/       {
/*?*/           double fVal = GetValue();
/*?*/           rAny.setValue(&fVal, ::getCppuType(&fVal));
/*?*/       }
/*?*/       break;
/*?*/   case FIELD_PROP_PAR3:
/*?*/       rAny <<= ::rtl::OUString(Expand());
/*?*/       break;
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       {
/*N*/           sal_uInt16 nExtSub = (nSubType & 0xff00) & ~DI_SUB_FIXED;
/*N*/           sal_Bool bVal = (nExtSub == DI_SUB_DATE);
/*N*/           rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/         return SwField::QueryValue(rAny, nMId);
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwDocInfoField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      if( nSubType & DI_SUB_FIXED )
//STRIP001          ::GetString( rAny, aContent );
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_USHORT1:
//STRIP001      if( nSubType & DI_SUB_FIXED )
//STRIP001      {
//STRIP001          rAny >>= nValue;
//STRIP001          aContent = String::CreateFromInt32(nValue);
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      if(*(sal_Bool*)rAny.getValue())
//STRIP001          nSubType |= DI_SUB_FIXED;
//STRIP001      else
//STRIP001          nSubType &= ~DI_SUB_FIXED;
//STRIP001      break;
//STRIP001  case FIELD_PROP_FORMAT:
//STRIP001      {
//STRIP001          rAny >>= nValue;
//STRIP001          if( nValue >= 0)
//STRIP001              SetFormat(nValue);
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_PAR3:
//STRIP001      ::GetString( rAny, aContent );
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL2:
//STRIP001      nSubType &= 0xf0ff;
//STRIP001      if(*(sal_Bool*)rAny.getValue())
//STRIP001          nSubType |= DI_SUB_DATE;
//STRIP001      else
//STRIP001          nSubType |= DI_SUB_TIME;
//STRIP001      break;
//STRIP001  default:
//STRIP001         return SwField::PutValue(rAny, nMId);
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: SwHiddenTxtFieldType by JP
 --------------------------------------------------------------------*/

/*N*/ SwHiddenTxtFieldType::SwHiddenTxtFieldType( sal_Bool bSetHidden )
/*N*/   : SwFieldType( RES_HIDDENTXTFLD ), bHidden( bSetHidden )
/*N*/ {}

/*N*/ SwFieldType* SwHiddenTxtFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP");return NULL; //STRIP001 //STRIP001   return new SwHiddenTxtFieldType( bHidden );
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwHiddenTxtFieldType::SetHiddenFlag( sal_Bool bSetHidden )
/*N*/ {
/*N*/   if( bHidden != bSetHidden )
/*N*/   {
/*?*/       bHidden = bSetHidden;
/*?*/       UpdateFlds();       // alle HiddenText benachrichtigen
/*N*/   }
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwHiddenTxtField::SwHiddenTxtField( SwHiddenTxtFieldType* pFldType,
/*N*/                                   sal_Bool    bConditional,
/*N*/                                   const   String& rCond,
/*N*/                                   const   String& rStr,
/*N*/                                   sal_Bool    bHidden,
/*N*/                                   sal_uInt16  nSub) :
/*N*/   SwField( pFldType ), aCond(rCond), bValid(sal_False),
/*N*/   bCanToggle(bConditional), bIsHidden(bHidden), nSubType(nSub)
/*N*/ {
/*N*/   if(nSubType == TYP_CONDTXTFLD)
/*N*/   {
/*N*/       sal_uInt16 nPos = 0;
/*N*/       aTRUETxt = rStr.GetToken(0, '|', nPos);
/*N*/
/*N*/       if(nPos != STRING_NOTFOUND)
/*N*/       {
/*N*/           aFALSETxt = rStr.GetToken(0, '|', nPos);
/*N*/           if(nPos != STRING_NOTFOUND)
/*N*/           {
/*?*/               aContent = rStr.GetToken(0, '|', nPos);
/*?*/               bValid = sal_True;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       aTRUETxt = rStr;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwHiddenTxtField::SwHiddenTxtField( SwHiddenTxtFieldType* pFldType,
/*N*/                                   const String& rCond,
/*N*/                                   const String& rTrue,
/*N*/                                   const String& rFalse,
/*N*/                                   sal_uInt16 nSub)
/*N*/   : SwField( pFldType ), aCond(rCond), bIsHidden(sal_True), nSubType(nSub),
/*N*/     aTRUETxt(rTrue), aFALSETxt(rFalse), bValid(sal_False)
/*N*/ {
/*N*/   bCanToggle  = aCond.Len() > 0;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwHiddenTxtField::Expand() const
/*N*/ {
/*N*/   // Type: !Hidden  -> immer anzeigen
/*N*/   //        Hide    -> Werte die Bedingung aus
/*N*/
/*N*/   if( TYP_CONDTXTFLD == nSubType )
/*N*/   {
/*N*/       if( bValid )
/*?*/           return aContent;
/*N*/
/*N*/       if( bCanToggle && !bIsHidden )
/*?*/           return aTRUETxt;
/*N*/   }
/*N*/   else if( !((SwHiddenTxtFieldType*)GetTyp())->GetHiddenFlag() ||
/*N*/       ( bCanToggle && bIsHidden ))
/*?*/       return aTRUETxt;
/*N*/
/*N*/   return aFALSETxt;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Aktuellen Field-Value holen und cachen
 --------------------------------------------------------------------*/

/*N*/ void SwHiddenTxtField::Evaluate(SwDoc* pDoc)
/*N*/ {
/*N*/   ASSERT(pDoc, Wo ist das Dokument Seniore);
/*N*/
/*N*/   if( TYP_CONDTXTFLD == nSubType )
/*N*/   {
/*N*/       SwNewDBMgr* pMgr = pDoc->GetNewDBMgr();
/*N*/
/*N*/       bValid = sal_False;
/*N*/       String sTmpName;
/*N*/
/*N*/       if (bCanToggle && !bIsHidden)
/*N*/           sTmpName = aTRUETxt;
/*N*/       else
/*N*/           sTmpName = aFALSETxt;
/*N*/
/*N*/ // OS 21.08.97: #42943# Datenbankausdruecke muessen sich von
/*N*/ //                einfachem Text unterscheiden. also wird der einfache Text
/*N*/ //                bevorzugt in Anfuehrungszeichen gesetzt.
/*N*/ //                Sind diese vorhanden werden umschliessende entfernt.
/*N*/ //                Wenn nicht, dann wird auf die Tauglichkeit als Datenbankname
/*N*/ //                geprueft. Nur wenn zwei oder mehr Punkte vorhanden sind und kein
/*N*/ //                Anfuehrungszeichen enthalten ist, gehen wir von einer DB aus.
/*N*/       if(sTmpName.Len() > 1 && sTmpName.GetChar(0) == '\"' &&
/*N*/           sTmpName.GetChar((sTmpName.Len() - 1)))
/*N*/       {
/*N*/           aContent = sTmpName.Copy(1, sTmpName.Len() - 2);
/*N*/           bValid = sal_True;
/*N*/       }
/*N*/       else if(sTmpName.Search('\"') == STRING_NOTFOUND &&
/*N*/           sTmpName.GetTokenCount('.') > 2)
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            ::ReplacePoint(sTmpName);
//STRIP001 /*?*/            if(sTmpName.GetChar(0) == '[' && sTmpName.GetChar(sTmpName.Len()-1) == ']')
//STRIP001 /*?*/            {   // Eckige Klammern entfernen
//STRIP001 /*?*/                sTmpName.Erase(0, 1);
//STRIP001 /*?*/                sTmpName.Erase(sTmpName.Len()-1, 1);
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if( pMgr)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                String sDBName( GetDBName( sTmpName, pDoc ));
//STRIP001 /*?*/                String sDataSource(sDBName.GetToken(0, DB_DELIM));
//STRIP001 /*?*/                String sDataTableOrQuery(sDBName.GetToken(1, DB_DELIM));
//STRIP001 /*?*/                if( pMgr->IsInMerge() && sDBName.Len() &&
//STRIP001 /*?*/                    pMgr->IsDataSourceOpen( sDataSource,
//STRIP001 /*?*/                                                sDataTableOrQuery, sal_False))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    double fNumber;
//STRIP001 /*?*/                    sal_uInt32 nFormat;
//STRIP001 /*?*/                    pMgr->GetMergeColumnCnt(GetColumnName( sTmpName ),
//STRIP001 /*?*/                                    GetLanguage(), aContent, &fNumber, &nFormat );
//STRIP001 /*?*/                    bValid = sal_True;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( sDBName.Len() && sDataSource.Len() &&
//STRIP001 /*?*/                         sDataTableOrQuery.Len() )
//STRIP001 /*?*/                    bValid = sal_True;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwHiddenTxtField::GetCntnt(sal_Bool bName) const
/*N*/ {
/*N*/   if ( bName )
/*N*/   {
/*?*/       String aStr(SwFieldType::GetTypeStr(nSubType));
/*?*/       aStr += ' ';
/*?*/       aStr += aCond;
/*?*/       aStr += ' ';
/*?*/       aStr += aTRUETxt;
/*?*/
/*?*/       if(nSubType == TYP_CONDTXTFLD)
/*?*/       {
/*?*/ static char __READONLY_DATA cTmp[] = " : ";
/*?*/           aStr.AppendAscii(cTmp);
/*?*/           aStr += aFALSETxt;
/*?*/       }
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwField* SwHiddenTxtField::Copy() const
/*N*/ {
/*N*/   SwHiddenTxtField* pFld =
/*N*/       new SwHiddenTxtField((SwHiddenTxtFieldType*)GetTyp(), aCond,
/*N*/                             aTRUETxt, aFALSETxt);
/*N*/   pFld->bIsHidden = bIsHidden;
/*N*/   pFld->bValid    = bValid;
/*N*/   pFld->aContent  = aContent;
/*N*/   pFld->SetFormat(GetFormat());
/*N*/   pFld->nSubType  = nSubType;
/*N*/   return pFld;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung: Bedingung setzen
 --------------------------------------------------------------------*/

/*N*/ void SwHiddenTxtField::SetPar1(const String& rStr)
/*N*/ {
/*N*/   aCond = rStr;
/*N*/   bCanToggle = aCond.Len() > 0;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const String& SwHiddenTxtField::GetPar1() const
/*N*/ {
/*N*/   return aCond;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: True/False Text
 --------------------------------------------------------------------*/

//STRIP001 void SwHiddenTxtField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  if(nSubType == TYP_CONDTXTFLD)
//STRIP001  {
//STRIP001      sal_uInt16 nPos = rStr.Search('|');
//STRIP001      aTRUETxt = rStr.Copy(0, nPos);
//STRIP001
//STRIP001      if(nPos != STRING_NOTFOUND)
//STRIP001          aFALSETxt = rStr.Copy(nPos + 1);
//STRIP001  }
//STRIP001  else
//STRIP001      aTRUETxt = rStr;
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwHiddenTxtField::GetPar2() const
/*N*/ {
/*N*/   String aRet(aTRUETxt);
/*N*/   if(nSubType == TYP_CONDTXTFLD)
/*N*/   {
/*N*/       aRet += '|';
/*N*/       aRet += aFALSETxt;
/*N*/   }
/*N*/   return aRet;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_uInt16 SwHiddenTxtField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwHiddenTxtField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/   const String* pOut = 0;
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*N*/       pOut = &aCond;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       pOut = &aTRUETxt;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR3:
/*N*/       pOut = &aFALSETxt;
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           sal_Bool bHidden = bIsHidden;
/*N*/           rAny.setValue(&bHidden, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   if( pOut )
/*N*/       rAny <<= OUString( *pOut );
/*N*/   return sal_True;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwHiddenTxtField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      {
//STRIP001          String sVal;
//STRIP001          SetPar1(::GetString( rAny, sVal ));
//STRIP001      }
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      ::GetString( rAny, aTRUETxt );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR3:
//STRIP001      ::GetString( rAny, aFALSETxt );
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001         bIsHidden = *(sal_Bool*)rAny.getValue();
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

//------------------------------------------------------------------------------

//STRIP001 String SwHiddenTxtField::GetColumnName(const String& rName)
//STRIP001 {
//STRIP001  sal_uInt16 nPos = rName.Search(DB_DELIM);
//STRIP001  if( STRING_NOTFOUND != nPos )
//STRIP001  {
//STRIP001      nPos = rName.Search(DB_DELIM, nPos + 1);
//STRIP001
//STRIP001      if( STRING_NOTFOUND != nPos )
//STRIP001          return rName.Copy(nPos + 1);
//STRIP001  }
//STRIP001  return rName;
//STRIP001 }

//------------------------------------------------------------------------------

//STRIP001 String SwHiddenTxtField::GetDBName(const String& rName, SwDoc *pDoc)
//STRIP001 {
//STRIP001  sal_uInt16 nPos = rName.Search(DB_DELIM);
//STRIP001  if( STRING_NOTFOUND != nPos )
//STRIP001  {
//STRIP001      nPos = rName.Search(DB_DELIM, nPos + 1);
//STRIP001
//STRIP001      if( STRING_NOTFOUND != nPos )
//STRIP001          return rName.Copy( 0, nPos );
//STRIP001  }
//STRIP001  SwDBData aData = pDoc->GetDBData();
//STRIP001  String sRet = aData.sDataSource;
//STRIP001  sRet += DB_DELIM;
//STRIP001  sRet += String(aData.sCommand);
//STRIP001  return sRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Der Feldtyp fuer Zeilenhoehe 0
 --------------------------------------------------------------------*/

/*N*/ SwHiddenParaFieldType::SwHiddenParaFieldType()
/*N*/   : SwFieldType( RES_HIDDENPARAFLD )
/*N*/ {
/*N*/ }

/*N*/ SwFieldType* SwHiddenParaFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwHiddenParaFieldType* pType = new SwHiddenParaFieldType();
//STRIP001  return pType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Das Feld Zeilenhoehe 0
 --------------------------------------------------------------------*/

/*N*/ SwHiddenParaField::SwHiddenParaField(SwHiddenParaFieldType* pType, const String& rStr)
/*N*/   : SwField(pType), aCond(rStr)
/*N*/ {
/*N*/   bIsHidden = sal_False;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwHiddenParaField::Expand() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwField* SwHiddenParaField::Copy() const
/*N*/ {
/*N*/   SwHiddenParaField* pFld = new SwHiddenParaField((SwHiddenParaFieldType*)GetTyp(), aCond);
/*N*/   pFld->bIsHidden = bIsHidden;
/*N*/
/*N*/   return pFld;
/*N*/ }
/*-----------------05.03.98 13:25-------------------

--------------------------------------------------*/
/*N*/ BOOL SwHiddenParaField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch ( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*N*/       rAny <<= OUString(aCond);
/*N*/       break;
/*N*/   case  FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           sal_Bool bHidden = bIsHidden;
/*N*/           rAny.setValue(&bHidden, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 13:25-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwHiddenParaField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch ( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      ::GetString( rAny, aCond );
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001         bIsHidden = *(sal_Bool*)rAny.getValue();
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Bedingung setzen
 --------------------------------------------------------------------*/

//STRIP001 void SwHiddenParaField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  aCond = rStr;
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const String& SwHiddenParaField::GetPar1() const
/*N*/ {
/*N*/   return aCond;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: PostIt
 --------------------------------------------------------------------*/

/*N*/ SwPostItFieldType::SwPostItFieldType()
/*N*/   : SwFieldType( RES_POSTITFLD )
/*N*/ {}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwFieldType* SwPostItFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwPostItFieldType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwPostItFieldType
 --------------------------------------------------------------------*/

/*?*/ SwPostItField::SwPostItField( SwPostItFieldType* pType,
/*?*/       const String& rAuthor, const String& rTxt, const Date& rDate )
/*?*/   : SwField( pType ), sTxt( rTxt ), sAuthor( rAuthor ), aDate( rDate )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ String SwPostItField::Expand() const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return aEmptyStr;
/*?*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 SwField* SwPostItField::Copy() const
//STRIP001 {
//STRIP001  return new SwPostItField( (SwPostItFieldType*)GetTyp(), sAuthor,
//STRIP001                              sTxt, aDate );
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: Author setzen
 --------------------------------------------------------------------*/

//STRIP001 void SwPostItField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  sAuthor = rStr;
//STRIP001 }

//STRIP001 const String& SwPostItField::GetPar1() const
//STRIP001 {
//STRIP001  return sAuthor;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Text fuers PostIt setzen
 --------------------------------------------------------------------*/

//STRIP001 void SwPostItField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  sTxt = rStr;
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 String SwPostItField::GetPar2() const
//STRIP001 {
//STRIP001  return sTxt;
//STRIP001 }

/*-----------------05.03.98 13:42-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwPostItField::QueryValue( uno::Any& rAny, BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      rAny <<= OUString(sAuthor);
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      rAny <<= OUString(sTxt);
//STRIP001      break;
//STRIP001  case FIELD_PROP_DATE:
//STRIP001      {
//STRIP001          util::Date aSetDate;
//STRIP001          aSetDate.Day = aDate.GetDay();
//STRIP001          aSetDate.Month = aDate.GetMonth();
//STRIP001          aSetDate.Year = aDate.GetYear();
//STRIP001          rAny.setValue(&aSetDate, ::getCppuType((util::Date*)0));
//STRIP001      }
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }
/*-----------------05.03.98 13:42-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwPostItField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      ::GetString( rAny, sAuthor );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      ::GetString( rAny, sTxt );
//STRIP001      break;
//STRIP001  case FIELD_PROP_DATE:
//STRIP001      if( rAny.getValueType() == ::getCppuType((util::Date*)0) )
//STRIP001      {
//STRIP001          util::Date aSetDate = *(util::Date*)rAny.getValue();
//STRIP001          aDate = Date(aSetDate.Day, aSetDate.Month, aSetDate.Year);
//STRIP001      }
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: DokumentinfoFields
 --------------------------------------------------------------------*/

/*N*/ SwExtUserFieldType::SwExtUserFieldType()
/*N*/   : SwFieldType( RES_EXTUSERFLD )
/*N*/ {
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwFieldType* SwExtUserFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwExtUserFieldType* pType = new SwExtUserFieldType;
//STRIP001  return pType;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwExtUserFieldType::Expand(sal_uInt16 nSub, sal_uInt32 nFormat) const
/*N*/ {
/*N*/   SvxAddressItem aAdr;
/*N*/   String aRet( aEmptyStr );
/*N*/   sal_uInt16 nRet = USHRT_MAX;
/*N*/   switch(nSub)
/*N*/   {
/*N*/   case EU_FIRSTNAME:      aRet = aAdr.GetFirstName(); break;
/*N*/   case EU_NAME:           aRet = aAdr.GetName();      break;
/*N*/   case EU_SHORTCUT:       aRet = aAdr.GetShortName(); break;
/*N*/
/*N*/   case EU_COMPANY:        nRet = POS_COMPANY;         break;
/*N*/   case EU_STREET:         nRet = POS_STREET;          break;
/*N*/   case EU_TITLE:          nRet = POS_TITLE;           break;
/*N*/   case EU_POSITION:       nRet = POS_POSITION;        break;
/*N*/   case EU_PHONE_PRIVATE:  nRet = POS_TEL_PRIVATE;     break;
/*N*/   case EU_PHONE_COMPANY:  nRet = POS_TEL_COMPANY;     break;
/*N*/   case EU_FAX:            nRet = POS_FAX;             break;
/*N*/   case EU_EMAIL:          nRet = POS_EMAIL;           break;
/*N*/   case EU_COUNTRY:        nRet = POS_COUNTRY;         break;
/*N*/   case EU_ZIP:            nRet = POS_PLZ;             break;
/*N*/   case EU_CITY:           nRet = POS_CITY;            break;
/*N*/   case EU_STATE:          nRet = POS_STATE;           break;
/*?*/   case EU_FATHERSNAME:    nRet = POS_FATHERSNAME;     break;
/*?*/   case EU_APARTMENT:      nRet = POS_APARTMENT;       break;
/*?*/   default:                ASSERT( !this, "Field unknown");
/*N*/   }
/*N*/   if( USHRT_MAX != nRet )
/*N*/       aRet = aAdr.GetToken( nRet );
/*N*/   return aRet;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwExtUserField::SwExtUserField(SwExtUserFieldType* pType, sal_uInt16 nSubTyp, sal_uInt32 nFmt) :
/*N*/   SwField(pType, nFmt), nType(nSubTyp)
/*N*/ {
/*N*/   aContent = ((SwExtUserFieldType*)GetTyp())->Expand(nType, GetFormat());
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwExtUserField::Expand() const
/*N*/ {
/*N*/   if (!IsFixed())
/*N*/       ((SwExtUserField*)this)->aContent = ((SwExtUserFieldType*)GetTyp())->Expand(nType, GetFormat());
/*N*/
/*N*/   return aContent;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwField* SwExtUserField::Copy() const
/*N*/ {
/*N*/   SwExtUserField* pFld = new SwExtUserField((SwExtUserFieldType*)GetTyp(), nType, GetFormat());
/*N*/   pFld->SetExpansion(aContent);
/*N*/
/*N*/   return pFld;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_uInt16 SwExtUserField::GetSubType() const
/*N*/ {
/*N*/   return nType;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwExtUserField::SetSubType(sal_uInt16 nSub)
//STRIP001 {
//STRIP001  nType = nSub;
//STRIP001 }

/*-----------------05.03.98 14:14-------------------

--------------------------------------------------*/
/*N*/ BOOL SwExtUserField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*?*/       rAny <<= OUString(aContent);
/*?*/       break;
/*N*/
/*N*/   case FIELD_PROP_USHORT1:
/*N*/       {
/*N*/           sal_Int16 nTmp = nType;
/*N*/           rAny <<= nTmp;
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           sal_Bool bTmp = IsFixed();
/*N*/           rAny.setValue(&bTmp, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 14:14-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwExtUserField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      ::GetString( rAny, aContent );
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_USHORT1:
//STRIP001      {
//STRIP001          sal_Int16 nTmp;
//STRIP001          rAny >>= nTmp;
//STRIP001          nType = nTmp;
//STRIP001      }
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      if( *(sal_Bool*)rAny.getValue() )
//STRIP001          SetFormat(GetFormat() | AF_FIXED);
//STRIP001      else
//STRIP001          SetFormat(GetFormat() & ~AF_FIXED);
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }
//-------------------------------------------------------------------------

/*--------------------------------------------------------------------
    Beschreibung: Relatives Seitennummern - Feld
 --------------------------------------------------------------------*/

/*N*/ SwRefPageSetFieldType::SwRefPageSetFieldType()
/*N*/   : SwFieldType( RES_REFPAGESETFLD )
/*N*/ {
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwFieldType* SwRefPageSetFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwRefPageSetFieldType;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
// ueberlagert, weil es nichts zum Updaten gibt!
//STRIP001 void SwRefPageSetFieldType::Modify( SfxPoolItem *, SfxPoolItem * )
//STRIP001 {
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Relative Seitennummerierung
 --------------------------------------------------------------------*/

/*?*/ SwRefPageSetField::SwRefPageSetField( SwRefPageSetFieldType* pType,
/*?*/                   short nOff, sal_Bool bFlag )
/*?*/   : SwField( pType ), nOffset( nOff ), bOn( bFlag )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ String SwRefPageSetField::Expand() const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return aEmptyStr;
/*?*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 SwField* SwRefPageSetField::Copy() const
//STRIP001 {
//STRIP001  return new SwRefPageSetField( (SwRefPageSetFieldType*)GetTyp(), nOffset, bOn );
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 String SwRefPageSetField::GetPar2() const
//STRIP001 {
//STRIP001  return String::CreateFromInt32( GetOffset() );
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwRefPageSetField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  SetOffset( (short) rStr.ToInt32() );
//STRIP001 }

/*-----------------05.03.98 14:52-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwRefPageSetField::QueryValue( uno::Any& rAny, BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      rAny.setValue(&bOn, ::getBooleanCppuType());
//STRIP001      break;
//STRIP001  case FIELD_PROP_USHORT1:
//STRIP001      rAny <<= (sal_Int16)nOffset;
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }
/*-----------------05.03.98 14:52-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwRefPageSetField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      bOn = *(sal_Bool*)rAny.getValue();
//STRIP001      break;
//STRIP001  case FIELD_PROP_USHORT1:
//STRIP001      rAny >>=nOffset;
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: relatives Seitennummern - Abfrage Feld
 --------------------------------------------------------------------*/

/*N*/ SwRefPageGetFieldType::SwRefPageGetFieldType( SwDoc* pDc )
/*N*/   : SwFieldType( RES_REFPAGEGETFLD ), nNumberingType( SVX_NUM_ARABIC ), pDoc( pDc )
/*N*/ {
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwFieldType* SwRefPageGetFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwRefPageGetFieldType* pNew = new SwRefPageGetFieldType( pDoc );
//STRIP001  pNew->nNumberingType = nNumberingType;
//STRIP001  return pNew;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwRefPageGetFieldType::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   // Update auf alle GetReferenz-Felder
/*N*/   if( !pNew && !pOld && GetDepends() )
/*N*/   {
/*?*/       // sammel erstmal alle SetPageRefFelder ein.
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 _SetGetExpFlds aTmpLst( 10, 5 );
//STRIP001 /*?*/        if( MakeSetList( aTmpLst ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwClientIter aIter( *this );
//STRIP001 /*?*/            if( aIter.GoStart() )
//STRIP001 /*?*/                do {
//STRIP001 /*?*/                    // nur die GetRef-Felder Updaten
//STRIP001 /*?*/                    SwFmtFld* pFmtFld = (SwFmtFld*)aIter();
//STRIP001 /*?*/                    if( pFmtFld->GetTxtFld() )
//STRIP001 /*?*/                        UpdateField( pFmtFld->GetTxtFld(), aTmpLst );
//STRIP001 /*?*/                } while( aIter++ );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/
/*N*/   // weiter an die Text-Felder, diese "Expandieren" den Text
/*N*/   SwModify::Modify( pOld, pNew );
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 sal_uInt16 SwRefPageGetFieldType::MakeSetList( _SetGetExpFlds& rTmpLst )
//STRIP001 {
//STRIP001  SwClientIter aIter( *pDoc->GetSysFldType( RES_REFPAGESETFLD));
//STRIP001  if( aIter.GoStart() )
//STRIP001      do {
//STRIP001          // nur die GetRef-Felder Updaten
//STRIP001          SwFmtFld* pFmtFld = (SwFmtFld*)aIter();
//STRIP001          const SwTxtFld* pTFld = pFmtFld->GetTxtFld();
//STRIP001          if( pTFld )
//STRIP001          {
//STRIP001              const SwTxtNode& rTxtNd = pTFld->GetTxtNode();
//STRIP001
//STRIP001              // immer den ersten !! (in Tab-Headline, Kopf-/Fuss )
//STRIP001              Point aPt;
//STRIP001              const SwCntntFrm* pFrm = rTxtNd.GetFrm( &aPt, 0, sal_False );
//STRIP001
//STRIP001              _SetGetExpFld* pNew;
//STRIP001
//STRIP001              if( !pFrm || pFrm->IsInDocBody() )
//STRIP001              {
//STRIP001                  // einen sdbcx::Index fuers bestimmen vom TextNode anlegen
//STRIP001                  SwNodeIndex aIdx( rTxtNd );
//STRIP001                  pNew = new _SetGetExpFld( aIdx, pTFld );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // einen sdbcx::Index fuers bestimmen vom TextNode anlegen
//STRIP001                  SwPosition aPos( pDoc->GetNodes().GetEndOfPostIts() );
//STRIP001 #ifndef PRODUCT
//STRIP001                  ASSERT( GetBodyTxtNode( *pDoc, aPos, *pFrm ),
//STRIP001                          "wo steht das Feld" );
//STRIP001 #else
//STRIP001                  GetBodyTxtNode( *pDoc, aPos, *pFrm );
//STRIP001 #endif
//STRIP001                  pNew = new _SetGetExpFld( aPos.nNode, pTFld,
//STRIP001                                              &aPos.nContent );
//STRIP001              }
//STRIP001
//STRIP001              if( !rTmpLst.Insert( pNew ))
//STRIP001                  delete pNew;
//STRIP001          }
//STRIP001      } while( aIter++ );
//STRIP001
//STRIP001  return rTmpLst.Count();
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwRefPageGetFieldType::UpdateField( SwTxtFld* pTxtFld,
//STRIP001                                      _SetGetExpFlds& rSetList )
//STRIP001 {
//STRIP001  SwRefPageGetField* pGetFld = (SwRefPageGetField*)pTxtFld->GetFld().GetFld();
//STRIP001  pGetFld->SetText( aEmptyStr );
//STRIP001
//STRIP001  // dann suche mal das richtige RefPageSet-Field
//STRIP001  SwTxtNode* pTxtNode = (SwTxtNode*)&pTxtFld->GetTxtNode();
//STRIP001  if( pTxtNode->StartOfSectionIndex() >
//STRIP001      pDoc->GetNodes().GetEndOfExtras().GetIndex() )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *pTxtNode );
//STRIP001      _SetGetExpFld aEndFld( aIdx, pTxtFld );
//STRIP001
//STRIP001      sal_uInt16 nLast;
//STRIP001      rSetList.Seek_Entry( &aEndFld, &nLast );
//STRIP001
//STRIP001      if( nLast-- )
//STRIP001      {
//STRIP001          const SwTxtFld* pRefTxtFld = rSetList[ nLast ]->GetFld();
//STRIP001          const SwRefPageSetField* pSetFld =
//STRIP001                      (SwRefPageSetField*)pRefTxtFld->GetFld().GetFld();
//STRIP001          if( pSetFld->IsOn() )
//STRIP001          {
//STRIP001              // dann bestimme mal den entsp. Offset
//STRIP001              Point aPt;
//STRIP001              const SwCntntFrm* pFrm = pTxtNode->GetFrm( &aPt, 0, sal_False );
//STRIP001              const SwCntntFrm* pRefFrm = pRefTxtFld->GetTxtNode().GetFrm( &aPt, 0, sal_False );
//STRIP001              const SwPageFrm* pPgFrm = 0;
//STRIP001              sal_uInt16 nDiff = ( pFrm && pRefFrm )
//STRIP001                      ?   (pPgFrm = pFrm->FindPageFrm())->GetPhyPageNum() -
//STRIP001                          pRefFrm->FindPageFrm()->GetPhyPageNum() + 1
//STRIP001                      : 1;
//STRIP001
//STRIP001              sal_uInt32 nTmpFmt = SVX_NUM_PAGEDESC == pGetFld->GetFormat()
//STRIP001                      ? ( !pPgFrm
//STRIP001                              ? SVX_NUM_ARABIC
//STRIP001                              : pPgFrm->GetPageDesc()->GetNumType().GetNumberingType() )
//STRIP001                      : pGetFld->GetFormat();
//STRIP001              short nPageNum = Max(0, pSetFld->GetOffset() + (short)nDiff);
//STRIP001              pGetFld->SetText( FormatNumber( nPageNum, nTmpFmt ) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  // dann die Formatierung anstossen
//STRIP001  ((SwFmtFld&)pTxtFld->GetFld()).Modify( 0, 0 );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Relative Seitennummerierung Abfragen
 --------------------------------------------------------------------*/

/*?*/ SwRefPageGetField::SwRefPageGetField( SwRefPageGetFieldType* pType,
/*?*/                                   sal_uInt32 nFmt )
/*?*/   : SwField( pType, nFmt )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ String SwRefPageGetField::Expand() const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return sTxt;
/*?*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 SwField* SwRefPageGetField::Copy() const
//STRIP001 {
//STRIP001  SwRefPageGetField* pCpy = new SwRefPageGetField(
//STRIP001                      (SwRefPageGetFieldType*)GetTyp(), GetFormat() );
//STRIP001  pCpy->SetText( sTxt );
//STRIP001  return pCpy;
//STRIP001 }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwRefPageGetField::ChangeExpansion( const SwFrm* pFrm,
//STRIP001                                      const SwTxtFld* pFld )
//STRIP001 {
//STRIP001  // nur Felder in Footer, Header, FootNote, Flys
//STRIP001  SwTxtNode* pTxtNode = (SwTxtNode*)&pFld->GetTxtNode();
//STRIP001  SwRefPageGetFieldType* pGetType = (SwRefPageGetFieldType*)GetTyp();
//STRIP001  SwDoc* pDoc = pGetType->GetDoc();
//STRIP001  if( pFld->GetTxtNode().StartOfSectionIndex() >
//STRIP001      pDoc->GetNodes().GetEndOfExtras().GetIndex() )
//STRIP001      return;
//STRIP001
//STRIP001  sTxt.Erase();
//STRIP001
//STRIP001  ASSERT( !pFrm->IsInDocBody(), "Flag ist nicht richtig, Frame steht im DocBody" );
//STRIP001
//STRIP001  // sammel erstmal alle SetPageRefFelder ein.
//STRIP001  _SetGetExpFlds aTmpLst( 10, 5 );
//STRIP001  if( !pGetType->MakeSetList( aTmpLst ) )
//STRIP001      return ;
//STRIP001
//STRIP001  // einen sdbcx::Index fuers bestimmen vom TextNode anlegen
//STRIP001  SwPosition aPos( SwNodeIndex( pDoc->GetNodes() ) );
//STRIP001  pTxtNode = (SwTxtNode*) GetBodyTxtNode( *pDoc, aPos, *pFrm );
//STRIP001
//STRIP001  // Wenn kein Layout vorhanden, kommt es in Kopf und Fusszeilen dazu
//STRIP001  // das ChangeExpansion uebers Layout-Formatieren aufgerufen wird
//STRIP001  // aber kein TxtNode vorhanden ist
//STRIP001  //
//STRIP001  if(!pTxtNode)
//STRIP001      return;
//STRIP001
//STRIP001  _SetGetExpFld aEndFld( aPos.nNode, pFld, &aPos.nContent );
//STRIP001
//STRIP001  sal_uInt16 nLast;
//STRIP001  aTmpLst.Seek_Entry( &aEndFld, &nLast );
//STRIP001
//STRIP001  if( !nLast-- )
//STRIP001      return ;        // es gibt kein entsprechendes Set - Feld vor mir
//STRIP001
//STRIP001  const SwTxtFld* pRefTxtFld = aTmpLst[ nLast ]->GetFld();
//STRIP001  const SwRefPageSetField* pSetFld =
//STRIP001                      (SwRefPageSetField*)pRefTxtFld->GetFld().GetFld();
//STRIP001     Point aPt;
//STRIP001     const SwCntntFrm* pRefFrm = pRefTxtFld ? pRefTxtFld->GetTxtNode().GetFrm( &aPt, 0, sal_False ) : 0;
//STRIP001     if( pSetFld->IsOn() && pRefFrm )
//STRIP001  {
//STRIP001      // dann bestimme mal den entsp. Offset
//STRIP001      const SwPageFrm* pPgFrm = pFrm->FindPageFrm();
//STRIP001      sal_uInt16 nDiff = pPgFrm->GetPhyPageNum() -
//STRIP001                          pRefFrm->FindPageFrm()->GetPhyPageNum() + 1;
//STRIP001
//STRIP001      SwRefPageGetField* pGetFld = (SwRefPageGetField*)pFld->GetFld().GetFld();
//STRIP001      sal_uInt32 nTmpFmt = SVX_NUM_PAGEDESC == pGetFld->GetFormat()
//STRIP001                          ? pPgFrm->GetPageDesc()->GetNumType().GetNumberingType()
//STRIP001                          : pGetFld->GetFormat();
//STRIP001      short nPageNum = Max(0, pSetFld->GetOffset() + (short)nDiff );
//STRIP001      pGetFld->SetText( FormatNumber( nPageNum, nTmpFmt ) );
//STRIP001  }
//STRIP001 }
/*-----------------05.03.98 14:52-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwRefPageGetField::QueryValue( uno::Any& rAny, BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001         case FIELD_PROP_USHORT1:
//STRIP001             rAny <<= (sal_Int16)GetFormat();
//STRIP001         break;
//STRIP001         case FIELD_PROP_PAR1:
//STRIP001             rAny <<= OUString(sTxt);
//STRIP001         break;
//STRIP001         default:
//STRIP001             DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }
/*-----------------05.03.98 14:52-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwRefPageGetField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001         case FIELD_PROP_USHORT1:
//STRIP001      {
//STRIP001          sal_Int16 nSet;
//STRIP001          rAny >>= nSet;
//STRIP001          if(nSet <= SVX_NUM_PAGEDESC )
//STRIP001              SetFormat(nSet);
//STRIP001          else
//STRIP001              //exception(wrong_value)
//STRIP001              ;
//STRIP001      }
//STRIP001      break;
//STRIP001         case FIELD_PROP_PAR1:
//STRIP001         {
//STRIP001             OUString sTmp;
//STRIP001             rAny >>= sTmp;
//STRIP001             sTxt = sTmp;
//STRIP001         }
//STRIP001         break;
//STRIP001     default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Feld zum Anspringen und Editieren
 --------------------------------------------------------------------*/

/*N*/ SwJumpEditFieldType::SwJumpEditFieldType( SwDoc* pD )
/*N*/   : SwFieldType( RES_JUMPEDITFLD ), pDoc( pD ), aDep( this, 0 )
/*N*/ {
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwFieldType* SwJumpEditFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwJumpEditFieldType( pDoc );
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwCharFmt* SwJumpEditFieldType::GetCharFmt()
/*N*/ {
/*N*/   SwCharFmt* pFmt = pDoc->GetCharFmtFromPool( RES_POOLCHR_JUMPEDIT );
/*N*/
/*N*/   // noch nicht registriert ?
/*N*/   if( !aDep.GetRegisteredIn() )
/*N*/       pFmt->Add( &aDep );     // anmelden
/*N*/
/*N*/   return pFmt;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwJumpEditField::SwJumpEditField( SwJumpEditFieldType* pTyp, sal_uInt32 nFormat,
/*N*/                               const String& rTxt, const String& rHelp )
/*N*/   : SwField( pTyp, nFormat ), sTxt( rTxt ), sHelp( rHelp )
/*N*/ {
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwJumpEditField::Expand() const
/*N*/ {
/*N*/   String sTmp( '<' );
/*N*/   sTmp += sTxt;
/*N*/   return sTmp += '>';
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwField* SwJumpEditField::Copy() const
/*N*/ {
/*N*/   return new SwJumpEditField( (SwJumpEditFieldType*)GetTyp(), GetFormat(),
/*N*/                               sTxt, sHelp );
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
// Platzhalter-Text

/*N*/ const String& SwJumpEditField::GetPar1() const
/*N*/ {
/*N*/   return sTxt;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwJumpEditField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  sTxt = rStr;
//STRIP001 }

// HinweisText
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwJumpEditField::GetPar2() const
/*N*/ {
/*N*/   return sHelp;
/*N*/ }
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwJumpEditField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  sHelp = rStr;
//STRIP001 }

/*-----------------05.03.98 15:00-------------------

--------------------------------------------------*/
/*N*/ BOOL SwJumpEditField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_USHORT1:
/*N*/       {
/*N*/           sal_Int16 nRet;
/*N*/           switch( GetFormat() )
/*N*/           {
/*N*/           case JE_FMT_TABLE:  nRet = text::PlaceholderType::TABLE; break;
/*N*/           case JE_FMT_FRAME:  nRet = text::PlaceholderType::TEXTFRAME; break;
/*N*/           case JE_FMT_GRAPHIC:nRet = text::PlaceholderType::GRAPHIC; break;
/*N*/           case JE_FMT_OLE:    nRet = text::PlaceholderType::OBJECT; break;
/*N*/ //            case JE_FMT_TEXT:
/*N*/           default:
/*N*/               nRet = text::PlaceholderType::TEXT; break;
/*N*/           }
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1 :
/*N*/       rAny <<= OUString(sHelp);
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2 :
/*?*/        rAny <<= OUString(sTxt);
/*?*/        break;
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
/*-----------------05.03.98 15:00-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwJumpEditField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_USHORT1:
//STRIP001      {
//STRIP001          //JP 24.10.2001: int32 because in UnoField.cxx a putvalue is
//STRIP001          //              called with a int32 value! But normally we need
//STRIP001          //              here only a int16
//STRIP001          sal_Int32 nSet;
//STRIP001          rAny >>= nSet;
//STRIP001          switch( nSet )
//STRIP001          {
//STRIP001              case text::PlaceholderType::TEXT     : SetFormat(JE_FMT_TEXT); break;
//STRIP001              case text::PlaceholderType::TABLE    : SetFormat(JE_FMT_TABLE); break;
//STRIP001              case text::PlaceholderType::TEXTFRAME: SetFormat(JE_FMT_FRAME); break;
//STRIP001              case text::PlaceholderType::GRAPHIC  : SetFormat(JE_FMT_GRAPHIC); break;
//STRIP001              case text::PlaceholderType::OBJECT   : SetFormat(JE_FMT_OLE); break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR1 :
//STRIP001      ::GetString( rAny, sHelp );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2 :
//STRIP001       ::GetString( rAny, sTxt);
//STRIP001       break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: Combined Character Fieldtype / Field
 --------------------------------------------------------------------*/

/*N*/ SwCombinedCharFieldType::SwCombinedCharFieldType()
/*N*/   : SwFieldType( RES_COMBINED_CHARS )
/*N*/ {
/*N*/ }

/*N*/ SwFieldType* SwCombinedCharFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwCombinedCharFieldType;
/*N*/ }

/* --------------------------------------------------------------------*/

/*?*/ SwCombinedCharField::SwCombinedCharField( SwCombinedCharFieldType* pFTyp,
/*?*/                                           const String& rChars )
/*?*/   : SwField( pFTyp, 0 ),
/*?*/   sCharacters( rChars.Copy( 0, MAX_COMBINED_CHARACTERS ))
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*?*/ String    SwCombinedCharField::Expand() const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return sCharacters;
/*?*/ }

//STRIP001 SwField* SwCombinedCharField::Copy() const
//STRIP001 {
//STRIP001  return new SwCombinedCharField( (SwCombinedCharFieldType*)GetTyp(),
//STRIP001                                      sCharacters );
//STRIP001 }

//STRIP001 const String& SwCombinedCharField::GetPar1() const
//STRIP001 {
//STRIP001  return sCharacters;
//STRIP001 }

//STRIP001 void SwCombinedCharField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  sCharacters = rStr.Copy( 0, MAX_COMBINED_CHARACTERS );
//STRIP001 }

//STRIP001 BOOL SwCombinedCharField::QueryValue( ::com::sun::star::uno::Any& rAny,
//STRIP001                                      BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      rAny <<= ::rtl::OUString( sCharacters );
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SwCombinedCharField::PutValue( const ::com::sun::star::uno::Any& rAny,
//STRIP001                                      BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      ::GetString( rAny, sCharacters ).Erase( MAX_COMBINED_CHARACTERS );
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

}
