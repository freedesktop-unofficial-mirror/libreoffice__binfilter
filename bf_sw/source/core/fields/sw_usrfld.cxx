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

#include <bf_svtools/zformat.hxx>


#include <calc.hxx>
#include <usrfld.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <unofldmid.h>
namespace binfilter {
extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr );
using namespace ::com::sun::star;
using namespace ::rtl;
/*--------------------------------------------------------------------
    Beschreibung: Benutzerfelder
 --------------------------------------------------------------------*/

/*N*/ SwUserField::SwUserField(SwUserFieldType* pTyp, sal_uInt16 nSub, sal_uInt32 nFmt)
/*N*/   : SwValueField(pTyp, nFmt),
/*N*/   nSubType(nSub)
/*N*/ {
/*N*/ }

/*N*/ String SwUserField::Expand() const
/*N*/ {
/*N*/   String sStr;
/*N*/   if(!(nSubType & SUB_INVISIBLE))
/*N*/       sStr = ((SwUserFieldType*)GetTyp())->Expand(GetFormat(), nSubType, GetLanguage());
/*N*/
/*N*/   return sStr;
/*N*/ }

/*N*/ SwField* SwUserField::Copy() const
/*N*/ {
/*N*/     SwField* pTmp = new SwUserField((SwUserFieldType*)GetTyp(), nSubType, GetFormat());
/*N*/     pTmp->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/     return pTmp;
/*N*/ }

/*N*/ String SwUserField::GetCntnt(sal_Bool bName) const
/*N*/ {
/*N*/   if ( bName )
/*N*/   {   String aStr(SwFieldType::GetTypeStr(TYP_USERFLD));
/*?*/       aStr += ' ';
/*?*/       aStr += GetTyp()->GetName();
/*?*/       aStr.AppendAscii(" = ");
/*?*/       aStr += ((SwUserFieldType*)GetTyp())->GetContent();
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }

double SwUserField::GetValue() const
{
    return ((SwUserFieldType*)GetTyp())->GetValue();
}

void SwUserField::SetValue( const double& rVal )
{
    ((SwUserFieldType*)GetTyp())->SetValue(rVal);
}

/*--------------------------------------------------------------------
    Beschreibung: Name
 --------------------------------------------------------------------*/

const String& SwUserField::GetPar1() const
{
    return ((SwUserFieldType*)GetTyp())->GetName();
}

/*--------------------------------------------------------------------
    Beschreibung: Content
 --------------------------------------------------------------------*/

String SwUserField::GetPar2() const
{
    return ((SwUserFieldType*)GetTyp())->GetContent(GetFormat());
}

void SwUserField::SetPar2(const String& rStr)
{
    ((SwUserFieldType*)GetTyp())->SetContent(rStr, GetFormat());
}

/*N*/ sal_uInt16 SwUserField::GetSubType() const
/*N*/ {
/*N*/   return ((SwUserFieldType*)GetTyp())->GetType() | nSubType;
/*N*/ }

/*N*/ void SwUserField::SetSubType(sal_uInt16 nSub)
/*N*/ {
/*N*/   ((SwUserFieldType*)GetTyp())->SetType(nSub & 0x00ff);
/*N*/   nSubType = nSub & 0xff00;
/*N*/ }


/*N*/ BOOL SwUserField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       {
/*N*/           BOOL bTmp = 0 != (nSubType & SUB_CMD);
/*N*/           rAny.setValue(&bTmp, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           BOOL bTmp = 0 == (nSubType & SUB_INVISIBLE);
/*N*/           rAny.setValue(&bTmp, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/   default:
/*?*/         return SwField::QueryValue(rAny, nMId);
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SwUserField::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       if(*(sal_Bool*) rAny.getValue())
/*N*/           nSubType &= (~SUB_INVISIBLE);
/*N*/       else
/*?*/           nSubType |= SUB_INVISIBLE;
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       if(*(sal_Bool*) rAny.getValue())
/*N*/           nSubType |= SUB_CMD;
/*N*/       else
/*N*/           nSubType &= (~SUB_CMD);
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*?*/       {
/*?*/           sal_Int32 nTmp(0);
/*?*/           rAny >>= nTmp;
/*?*/           SetFormat(nTmp);
/*?*/       }
/*?*/       break;
/*?*/   default:
/*?*/         return SwField::PutValue(rAny, nMId);
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Benutzerfeldtypen
 --------------------------------------------------------------------*/

/*N*/ SwUserFieldType::SwUserFieldType( SwDoc* pDocPtr, const String& aNam )
/*N*/   : SwValueFieldType( pDocPtr, RES_USERFLD )
/*N*/   , nValue( 0 )
/*N*/   , nType(GSE_STRING)
/*N*/ {
/*N*/   bValidValue = bDeleted = sal_False;
/*N*/   aName = aNam;
/*N*/
/*N*/   if (nType & GSE_STRING)
/*N*/       EnableFormat(sal_False);    // Numberformatter nicht einsetzen
/*N*/ }

/*N*/ String SwUserFieldType::Expand(sal_uInt32 nFmt, sal_uInt16 nSubType, sal_uInt16 nLng)
/*N*/ {
/*N*/   String aStr(aContent);
/*N*/   if((nType & GSE_EXPR) && !(nSubType & SUB_CMD))
/*N*/   {
/*N*/       EnableFormat(sal_True);
/*N*/       aStr = ExpandValue(nValue, nFmt, nLng);
/*N*/   }
/*N*/   else
/*N*/       EnableFormat(sal_False);    // Numberformatter nicht einsetzen
/*N*/
/*N*/   return aStr;
/*N*/ }

/*N*/ SwFieldType* SwUserFieldType::Copy() const
/*N*/ {
/*N*/   SwUserFieldType *pTmp = new SwUserFieldType( GetDoc(), aName );
/*N*/   pTmp->aContent      = aContent;
/*N*/   pTmp->nType         = nType;
/*N*/   pTmp->bValidValue   = bValidValue;
/*N*/   pTmp->nValue        = nValue;
/*N*/   pTmp->bDeleted      = bDeleted;
/*N*/
/*N*/   return pTmp;
/*N*/ }

/*N*/ const String& SwUserFieldType::GetName() const
/*N*/ {
/*N*/   return aName;
/*N*/ }


/*N*/ double SwUserFieldType::GetValue( SwCalc& rCalc )
/*N*/ {
/*N*/   if(bValidValue)
/*N*/       return nValue;
/*N*/
/*N*/   if(!rCalc.Push( this ))
/*N*/   {
/*N*/       rCalc.SetCalcError( CALC_SYNTAX );
/*N*/       return 0;
/*N*/   }
/*N*/   nValue = rCalc.Calculate( aContent ).GetDouble();
/*N*/   rCalc.Pop( this );
/*N*/
/*N*/   if( !rCalc.IsCalcError() )
/*N*/       bValidValue = sal_True;
/*N*/   else
/*N*/       nValue = 0;
/*N*/
/*N*/   return nValue;
/*N*/ }

/*N*/ String SwUserFieldType::GetContent( sal_uInt32 nFmt )
/*N*/ {
/*N*/   if (nFmt && nFmt != SAL_MAX_UINT32)
/*N*/   {
/*?*/       String sFormattedValue;
/*?*/       Color* pCol = 0;
/*?*/
/*?*/       SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
/*?*/
/*?*/       pFormatter->GetOutputString(GetValue(), nFmt, sFormattedValue, &pCol);
/*?*/       return sFormattedValue;
/*N*/   }
/*N*/   else
/*N*/       return aContent;
/*N*/ }

/*N*/ void SwUserFieldType::SetContent( const String& rStr, sal_uInt32 nFmt )
/*N*/ {
/*N*/   if( aContent != rStr )
/*N*/   {
/*N*/       aContent = rStr;
/*N*/
/*N*/       if (nFmt && nFmt != SAL_MAX_UINT32)
/*N*/       {
/*?*/           double fValue;
/*?*/
/*?*/           SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
/*?*/
/*?*/           if (pFormatter->IsNumberFormat(rStr, nFmt, fValue))
/*?*/           {
/*?*/               SetValue(fValue);
/*?*/               aContent.Erase();
/*?*/               DoubleToString(aContent, fValue, nFmt);
/*?*/           }
/*N*/       }
/*N*/
/*N*/       GetDoc()->IsModified();
/*N*/       GetDoc()->SetModified();
/*N*/   }
/*N*/ }


/*N*/ BOOL SwUserFieldType::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_DOUBLE:
/*N*/       rAny <<= (double) nValue;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       rAny <<= ::rtl::OUString(aContent);
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           BOOL bExpression = 0 != (GSE_EXPR&nType);
/*N*/           rAny.setValue(&bExpression, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       OSL_FAIL("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

/*N*/ BOOL SwUserFieldType::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_DOUBLE:
/*N*/       {
/*N*/           double fVal(0.0);
/*N*/           rAny >>= fVal;
/*N*/           nValue = fVal;
/*N*/
/*N*/           // Folgende Zeile ist eigentlich falsch, da die Sprache unbekannt ist
/*N*/           // (haengt am Feld) und aContent daher auch eigentlich ans Feld gehoeren
/*N*/           // muesste. Jedes Feld kann eine andere Sprache, aber den gleichen Inhalt
/*N*/           // haben, nur die Formatierung ist unterschiedlich.
/*N*/           DoubleToString(aContent, nValue, (sal_uInt16)LANGUAGE_SYSTEM);
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       ::binfilter::GetString( rAny, aContent );
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       if(*(sal_Bool*)rAny.getValue())
/*N*/         {
/*N*/           nType |= GSE_EXPR;
/*N*/             nType &= ~GSE_STRING;
/*N*/         }
/*N*/       else
/*N*/         {
/*N*/           nType &= ~GSE_EXPR;
/*N*/           nType |= GSE_STRING;
/*N*/         }
/*N*/       break;
/*N*/   default:
/*?*/       OSL_FAIL("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
