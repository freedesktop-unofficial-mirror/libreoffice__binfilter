/*************************************************************************
 *
 *  $RCSfile: svx_asiancfg.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:11 $
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

#ifndef _SVX_ASIANCFG_HXX
#include <asiancfg.hxx>
#endif
#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

//-----------------------------------------------------------------------------
using namespace utl;
using namespace rtl;
using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::beans;
using namespace com::sun::star::lang;

#define C2U(cChar) OUString::createFromAscii(cChar)
/*N*/ const sal_Char sStartEndCharacters[] = "StartEndCharacters";
/*N*/ const sal_Char sStartCharacters[] = "StartCharacters";
/*N*/ const sal_Char sEndCharacters[] = "EndCharacters";

//-----------------------------------------------------------------------------
/*N*/ struct SvxForbiddenStruct_Impl
/*N*/ {
/*N*/   Locale      aLocale;
/*N*/   OUString    sStartChars;
/*N*/   OUString    sEndChars;
/*N*/ };
//-----------------------------------------------------------------------------
/*N*/ typedef SvxForbiddenStruct_Impl* SvxForbiddenStruct_ImplPtr;
/*N*/ SV_DECL_PTRARR_DEL(SvxForbiddenStructArr, SvxForbiddenStruct_ImplPtr, 2, 2);
/*N*/ SV_IMPL_PTRARR(SvxForbiddenStructArr, SvxForbiddenStruct_ImplPtr);
//-----------------------------------------------------------------------------
/*N*/ struct SvxAsianConfig_Impl
/*N*/ {
/*N*/   sal_Bool    bKerningWesternTextOnly;
/*N*/   sal_Int16   nCharDistanceCompression;
/*N*/
/*N*/   SvxForbiddenStructArr   aForbiddenArr;
/*N*/
/*N*/   SvxAsianConfig_Impl() :
/*N*/       bKerningWesternTextOnly(sal_True),
/*N*/       nCharDistanceCompression(0) {}
/*N*/ };
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ Sequence<OUString> lcl_GetPropertyNames()
/*N*/ {
/*N*/   Sequence<OUString> aNames(2);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   pNames[0] = C2U("IsKerningWesternTextOnly");
/*N*/   pNames[1] = C2U("CompressCharacterDistance");
/*N*/   return aNames;;
/*N*/ }
// ---------------------------------------------------------------------------
/*N*/ SvxAsianConfig::SvxAsianConfig(sal_Bool bEnableNotify) :
/*N*/   utl::ConfigItem(C2U("Office.Common/AsianLayout")),
/*N*/   pImpl(new SvxAsianConfig_Impl)
/*N*/ {
/*N*/   if(bEnableNotify)
/*N*/       EnableNotification(lcl_GetPropertyNames());
/*N*/   Load();
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SvxAsianConfig::~SvxAsianConfig()
/*N*/ {
/*N*/   delete pImpl;
/*N*/ }
/* -----------------------------17.01.01 09:57--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SvxAsianConfig::Load()
/*N*/ {
/*N*/   Sequence<Any> aValues = GetProperties(lcl_GetPropertyNames());
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   if(pValues[0].hasValue())
/*N*/       pImpl->bKerningWesternTextOnly = *(sal_Bool*) pValues[0].getValue();
/*N*/   pValues[1] >>= pImpl->nCharDistanceCompression;
/*N*/
/*N*/   pImpl->aForbiddenArr.DeleteAndDestroy(0, pImpl->aForbiddenArr.Count());
/*N*/   OUString sPropPrefix(C2U(sStartEndCharacters));
/*N*/   Sequence<OUString> aNodes = GetNodeNames(sPropPrefix);
/*N*/
/*N*/   Sequence<OUString> aPropNames(aNodes.getLength() * 2);
/*N*/   OUString* pNames = aPropNames.getArray();
/*N*/   sal_Int32 nName = 0;
/*N*/   sPropPrefix += C2U("/");
/*N*/   sal_Int32 nNode;
/*N*/   const OUString* pNodes = aNodes.getConstArray();
/*N*/   for(nNode = 0; nNode < aNodes.getLength(); nNode++)
/*N*/   {
/*?*/       OUString sStart(sPropPrefix);
/*?*/       sStart += pNodes[nNode];
/*?*/       sStart += C2U("/");
/*?*/       pNames[nName] = sStart;     pNames[nName++] += C2U("StartCharacters");
/*?*/       pNames[nName] = sStart;     pNames[nName++] += C2U("EndCharacters");
/*N*/   }
/*N*/   Sequence<Any> aNodeValues = GetProperties(aPropNames);
/*N*/   const Any* pNodeValues = aNodeValues.getConstArray();
/*N*/   nName = 0;
/*N*/   for(nNode = 0; nNode < aNodes.getLength(); nNode++)
/*N*/   {
/*?*/       SvxForbiddenStruct_ImplPtr pInsert = new SvxForbiddenStruct_Impl;
/*?*/       pInsert->aLocale.Language = pNodes[nNode].copy(0, 2);
/*?*/       DBG_ASSERT(pInsert->aLocale.Language.getLength(), "illegal language");
/*?*/       pInsert->aLocale.Country = pNodes[nNode].copy(3, 2);
/*?*/
/*?*/       pNodeValues[nName++] >>= pInsert->sStartChars;
/*?*/       pNodeValues[nName++] >>= pInsert->sEndChars;
/*?*/       pImpl->aForbiddenArr.Insert(pInsert, pImpl->aForbiddenArr.Count());
/*N*/   }
/*N*/ }
/* -----------------------------17.01.01 09:57--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void     SvxAsianConfig::Notify( const Sequence<OUString>& rPropertyNames)
//STRIP001 {
//STRIP001  Load();
//STRIP001 }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SvxAsianConfig::Commit()
//STRIP001 {
//STRIP001  Sequence<Any> aValues(2);
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001  pValues[0].setValue(&pImpl->bKerningWesternTextOnly, ::getBooleanCppuType());
//STRIP001  pValues[1] <<= pImpl->nCharDistanceCompression;
//STRIP001  PutProperties(lcl_GetPropertyNames(), aValues);
//STRIP001
//STRIP001
//STRIP001  OUString sNode(C2U(sStartEndCharacters));
//STRIP001  if(!pImpl->aForbiddenArr.Count())
//STRIP001      ClearNodeSet(sNode);
//STRIP001  else
//STRIP001  {
//STRIP001      Sequence<PropertyValue> aSetValues(2 * pImpl->aForbiddenArr.Count());
//STRIP001      PropertyValue* pSetValues = aSetValues.getArray();
//STRIP001      sal_Int32 nSetValue = 0;
//STRIP001      const OUString sStartChars(C2U(sStartCharacters));
//STRIP001      const OUString sEndChars(C2U(sEndCharacters));
//STRIP001      for(sal_uInt16 i = 0; i < pImpl->aForbiddenArr.Count(); i++)
//STRIP001      {
//STRIP001          OUString sPrefix(sNode);
//STRIP001          sPrefix += C2U("/");
//STRIP001          sPrefix += pImpl->aForbiddenArr[i]->aLocale.Language;
//STRIP001          DBG_ASSERT(pImpl->aForbiddenArr[i]->aLocale.Language.getLength(), "illegal language");
//STRIP001          sPrefix += C2U("-");
//STRIP001          sPrefix += pImpl->aForbiddenArr[i]->aLocale.Country;
//STRIP001          sPrefix += C2U("/");
//STRIP001          pSetValues[nSetValue].Name = sPrefix; pSetValues[nSetValue].Name += sStartChars;
//STRIP001          pSetValues[nSetValue++].Value <<= pImpl->aForbiddenArr[i]->sStartChars;
//STRIP001          pSetValues[nSetValue].Name = sPrefix; pSetValues[nSetValue].Name += sEndChars;
//STRIP001          pSetValues[nSetValue++].Value <<= pImpl->aForbiddenArr[i]->sEndChars;
//STRIP001      }
//STRIP001      ReplaceSetProperties(sNode, aSetValues);
//STRIP001  }
//STRIP001 }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_Bool  SvxAsianConfig::IsKerningWesternTextOnly() const
/*N*/ {
/*N*/   return pImpl->bKerningWesternTextOnly;
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void         SvxAsianConfig::SetKerningWesternTextOnly(sal_Bool bSet)
//STRIP001 {
//STRIP001  pImpl->bKerningWesternTextOnly = bSet;
//STRIP001  SetModified();
//STRIP001 }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_Int16 SvxAsianConfig::GetCharDistanceCompression() const
/*N*/ {
/*N*/   return pImpl->nCharDistanceCompression;
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void         SvxAsianConfig::SetCharDistanceCompression(sal_Int16 nSet)
//STRIP001 {
//STRIP001  DBG_ASSERT(nSet >= 0 && nSet < 3, "compression value illegal");
//STRIP001  SetModified();
//STRIP001  pImpl->nCharDistanceCompression = nSet;
//STRIP001 }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ uno::Sequence<lang::Locale> SvxAsianConfig::GetStartEndCharLocales()
/*N*/ {
/*N*/   Sequence<Locale> aRet(pImpl->aForbiddenArr.Count());
/*N*/   Locale* pRet = aRet.getArray();
/*N*/   for(sal_uInt16 i = 0; i < pImpl->aForbiddenArr.Count(); i++)
/*N*/   {
/*?*/       pRet[i] = pImpl->aForbiddenArr[i]->aLocale;
/*N*/   }
/*N*/   return aRet;
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 sal_Bool SvxAsianConfig::GetStartEndChars( const Locale& rLocale,
//STRIP001                                  OUString& rStartChars,
//STRIP001                                  OUString& rEndChars )
//STRIP001 {
//STRIP001  for(sal_uInt16 i = 0; i < pImpl->aForbiddenArr.Count(); i++)
//STRIP001  {
//STRIP001      if(rLocale.Language == pImpl->aForbiddenArr[i]->aLocale.Language &&
//STRIP001          rLocale.Country == pImpl->aForbiddenArr[i]->aLocale.Country)
//STRIP001      {
//STRIP001          rStartChars = pImpl->aForbiddenArr[i]->sStartChars;
//STRIP001          rEndChars = pImpl->aForbiddenArr[i]->sEndChars;
//STRIP001          return sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SvxAsianConfig::SetStartEndChars( const Locale& rLocale,
//STRIP001                                  const OUString* pStartChars,
//STRIP001                                  const OUString* pEndChars )
//STRIP001 {
//STRIP001  sal_Bool bFound = sal_False;
//STRIP001  for(sal_uInt16 i = 0; i < pImpl->aForbiddenArr.Count(); i++)
//STRIP001  {
//STRIP001      if(rLocale.Language == pImpl->aForbiddenArr[i]->aLocale.Language &&
//STRIP001          rLocale.Country == pImpl->aForbiddenArr[i]->aLocale.Country)
//STRIP001      {
//STRIP001          if(pStartChars && pEndChars)
//STRIP001          {
//STRIP001              pImpl->aForbiddenArr[i]->sStartChars = *pStartChars;
//STRIP001              pImpl->aForbiddenArr[i]->sEndChars = *pEndChars;
//STRIP001          }
//STRIP001          else
//STRIP001              pImpl->aForbiddenArr.DeleteAndDestroy(i, 1);
//STRIP001          bFound = sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001  if(!bFound && pStartChars && pEndChars)
//STRIP001  {
//STRIP001      SvxForbiddenStruct_ImplPtr pInsert = new SvxForbiddenStruct_Impl;
//STRIP001      pInsert->aLocale = rLocale;
//STRIP001      pInsert->sStartChars = *pStartChars;
//STRIP001      pInsert->sEndChars = *pEndChars;
//STRIP001      pImpl->aForbiddenArr.Insert(pInsert, pImpl->aForbiddenArr.Count());
//STRIP001  }
//STRIP001 #ifdef DBG_UTIL
//STRIP001  else if(!bFound)
//STRIP001      DBG_ERROR("attempt to clear unavailable data");
//STRIP001 #endif
//STRIP001  SetModified();
//STRIP001 }
