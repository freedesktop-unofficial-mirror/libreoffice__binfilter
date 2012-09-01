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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <math.h>

#include <bf_svtools/zforlist.hxx>
#include <com/sun/star/util/DateTime.hpp>

#include <horiornt.hxx>

#include <doc.hxx>
#include <flddat.hxx>
#include <unofldmid.h>
namespace binfilter {

using namespace ::com::sun::star;
/*--------------------------------------------------
    Beschreibung: Datum/Zeit-Typ
 ---------------------------------------------------*/

/*N*/ SwDateTimeFieldType::SwDateTimeFieldType(SwDoc* pDoc1)
/*N*/   : SwValueFieldType( pDoc1, RES_DATETIMEFLD )
/*N*/ {}


/*--------------------------------------------------------------------
    Beschreibung: Datum/Zeit-Feld
 --------------------------------------------------------------------*/

/*N*/ SwDateTimeField::SwDateTimeField(SwDateTimeFieldType* pType1, USHORT nSub, ULONG nFmt, USHORT nLng)
/*N*/   : SwValueField(pType1, nFmt, nLng, 0.0),
/*N*/   nSubType(nSub),
/*N*/   nOffset(0)
/*N*/ {
/*N*/   if (!nFmt)
/*N*/   {
/*N*/       SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
/*N*/       if (nSubType & DATEFLD)
/*N*/           ChangeFormat(pFormatter->GetFormatIndex(NF_DATE_SYSTEM_SHORT, GetLanguage()));
/*N*/       else
/*?*/           ChangeFormat(pFormatter->GetFormatIndex(NF_TIME_HHMMSS, GetLanguage()));
/*N*/   }
/*N*/   if (IsFixed())
/*N*/   {
/*N*/         DateTime aDateTime( DateTime::SYSTEM );
/*N*/         SetDateTime(aDateTime);
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ String SwDateTimeField::Expand() const
/*N*/ {
/*N*/   double fVal;
/*N*/
/*N*/   if (!(IsFixed()))
/*N*/   {
/*N*/         DateTime aDateTime( DateTime::SYSTEM );
/*N*/         fVal = GetDateTime(GetDoc(), aDateTime);
/*N*/   }
/*N*/   else
/*N*/       fVal = GetValue();
/*N*/
/*N*/   if (nOffset)
/*N*/       fVal += (double)(nOffset * 60L) / 86400.0;
/*N*/
/*N*/   return ExpandValue(fVal, GetFormat(), GetLanguage());
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ SwField* SwDateTimeField::Copy() const
/*N*/ {
/*N*/   SwDateTimeField *pTmp =
/*N*/       new SwDateTimeField((SwDateTimeFieldType*)GetTyp(), nSubType,
/*N*/                                           GetFormat(), GetLanguage());
/*N*/
/*N*/   pTmp->SetValue(GetValue());
/*N*/   pTmp->SetOffset(nOffset);
/*N*/     pTmp->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/
/*N*/   return pTmp;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ USHORT SwDateTimeField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDateTimeField::SetSubType(USHORT nType) //SW40.SDW
/*N*/ {
/*N*/   nSubType = nType;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDateTimeField::SetDateTime(const DateTime& rDT)
/*N*/ {
/*N*/     SetValue(GetDateTime(GetDoc(), rDT));
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ double SwDateTimeField::GetDateTime(SwDoc* pDoc, const DateTime& rDT)
/*N*/ {
/*N*/   SvNumberFormatter* pFormatter = pDoc->GetNumberFormatter();
/*N*/     Date* pNullDate = pFormatter->GetNullDate();
/*N*/
/*N*/     double fResult = rDT - DateTime(*pNullDate);
/*N*/
/*N*/     return fResult;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ double SwDateTimeField::GetValue() const
/*N*/ {
/*N*/   if (IsFixed())
/*N*/       return SwValueField::GetValue();
/*N*/   else
/*N*/         return GetDateTime(GetDoc(), DateTime( DateTime::SYSTEM ));
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ Date SwDateTimeField::GetDate(BOOL bUseOffset) const
/*N*/ {
/*N*/   SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
/*N*/   Date* pNullDate = pFormatter->GetNullDate();
/*N*/
/*N*/   long nVal = GetValue();
/*N*/
/*N*/   if (bUseOffset && nOffset)
/*?*/       nVal += nOffset / 60 / 24;
/*N*/
/*N*/   Date aDate = *pNullDate + nVal;
/*N*/
/*N*/   return aDate;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ Time SwDateTimeField::GetTime(BOOL bUseOffset) const
/*N*/ {
/*N*/     double fDummy;
/*N*/     double fFract = modf(GetValue(), &fDummy);
/*N*/     DateTime aDT((long)fDummy, 0);
/*N*/     aDT += fFract;
/*N*/     if (bUseOffset)
/*N*/          aDT += Time(0, nOffset);
/*N*/     return (Time)aDT;
/*N*/ }


/*N*/ BOOL SwDateTimeField::QueryValue( uno::Any& rVal, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           BOOL bTmp = IsFixed();
/*N*/           rVal.setValue(&bTmp, ::getCppuBooleanType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       {
/*N*/           BOOL bTmp = IsDate();
/*N*/           rVal.setValue(&bTmp, ::getCppuBooleanType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rVal <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       rVal <<= (sal_Int32)nOffset;
/*N*/       break;
/*N*/   case FIELD_PROP_DATE_TIME:
/*N*/       {
/*N*/             DateTime aDateTime(GetDate(), GetTime());
/*N*/
/*N*/           util::DateTime DateTimeValue;
/*N*/           DateTimeValue.HundredthSeconds = aDateTime.Get100Sec();
/*N*/           DateTimeValue.Seconds = aDateTime.GetSec();
/*N*/           DateTimeValue.Minutes = aDateTime.GetMin();
/*N*/           DateTimeValue.Hours = aDateTime.GetHour();
/*N*/           DateTimeValue.Day = aDateTime.GetDay();
/*N*/           DateTimeValue.Month = aDateTime.GetMonth();
/*N*/           DateTimeValue.Year = aDateTime.GetYear();
/*N*/           rVal <<= DateTimeValue;
/*N*/       }
/*N*/       break;
/*N*/   default:
/*N*/         return SwField::QueryValue(rVal, nMId);
/*N*/     }
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SwDateTimeField::PutValue( const uno::Any& rVal, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   sal_Int32 nTmp(0);
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       if(*(sal_Bool*)rVal.getValue())
/*N*/           nSubType |= FIXEDFLD;
/*N*/       else
/*N*/           nSubType &= ~FIXEDFLD;
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       nSubType &=  ~(DATEFLD|TIMEFLD);
/*N*/       nSubType |= *(sal_Bool*)rVal.getValue() ? DATEFLD : TIMEFLD;
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rVal >>= nTmp;
/*N*/       ChangeFormat(nTmp);
/*N*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       rVal >>= nTmp;
/*N*/       nOffset = nTmp;
/*N*/       break;
/*N*/   case FIELD_PROP_DATE_TIME:
/*N*/       {
/*N*/           util::DateTime aDateTimeValue;
/*N*/           if(!(rVal >>= aDateTimeValue))
/*N*/               return FALSE;
/*N*/           DateTime aDateTime( DateTime::EMPTY );
/*N*/           aDateTime.Set100Sec(aDateTimeValue.HundredthSeconds);
/*N*/           aDateTime.SetSec(aDateTimeValue.Seconds);
/*N*/           aDateTime.SetMin(aDateTimeValue.Minutes);
/*N*/           aDateTime.SetHour(aDateTimeValue.Hours);
/*N*/           aDateTime.SetDay(aDateTimeValue.Day);
/*N*/           aDateTime.SetMonth(aDateTimeValue.Month);
/*N*/           aDateTime.SetYear(aDateTimeValue.Year);
/*N*/             SetDateTime(aDateTime);
/*N*/       }
/*N*/       break;
/*N*/         default:
/*N*/             return SwField::PutValue(rVal, nMId);
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
