/*************************************************************************
 *
 *  $RCSfile: sc_userlist.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:38 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------------

#include <unotools/charclass.hxx>
#include <string.h>

#include "global.hxx"
#include "userlist.hxx"

#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _UNOTOOLS_CALENDARWRAPPER_HXX
#include <unotools/calendarwrapper.hxx>
#endif
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif
namespace binfilter {

// STATIC DATA -----------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ void ScUserListData::InitTokens()
/*N*/ {
/*N*/   sal_Unicode cSep = ScGlobal::cListDelimiter;
/*N*/   nTokenCount = (USHORT) aStr.GetTokenCount(cSep);
/*N*/   if (nTokenCount)
/*N*/   {
/*N*/       pSubStrings = new String[nTokenCount];
/*N*/       pUpperSub   = new String[nTokenCount];
/*N*/       for (USHORT i=0; i<nTokenCount; i++)
/*N*/       {
/*N*/           pUpperSub[i] = pSubStrings[i] = aStr.GetToken((xub_StrLen)i,cSep);
/*N*/           ScGlobal::pCharClass->toUpper(pUpperSub[i]);
/*N*/       }
/*N*/   }
/*N*/   else
/*?*/       pSubStrings = pUpperSub = NULL;
/*N*/ }

/*N*/ ScUserListData::ScUserListData(const String& rStr) :
/*N*/   aStr(rStr)
/*N*/ {
/*N*/   InitTokens();
/*N*/ }

/*N*/ ScUserListData::ScUserListData(const ScUserListData& rData) :
/*N*/   aStr(rData.aStr)
/*N*/ {
/*N*/   InitTokens();
/*N*/ }

/*N*/ __EXPORT ScUserListData::~ScUserListData()
/*N*/ {
/*N*/   delete[] pSubStrings;
/*N*/   delete[] pUpperSub;
/*N*/ }

//STRIP001 ScUserListData::ScUserListData( SvStream& rStream )
//STRIP001 {
//STRIP001  rStream.ReadByteString( aStr, rStream.GetStreamCharSet() );
//STRIP001  InitTokens();
//STRIP001 }

//STRIP001 BOOL ScUserListData::Store( SvStream& rStream ) const
//STRIP001 {
//STRIP001  rStream.WriteByteString( aStr, rStream.GetStreamCharSet() );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void ScUserListData::SetString( const String& rStr )
//STRIP001 {
//STRIP001  delete[] pSubStrings;
//STRIP001  delete[] pUpperSub;
//STRIP001
//STRIP001  aStr = rStr;
//STRIP001  InitTokens();
//STRIP001 }

//STRIP001 USHORT ScUserListData::GetSubCount() const
//STRIP001 {
//STRIP001  return nTokenCount;
//STRIP001 }

/*N*/ BOOL ScUserListData::GetSubIndex(const String& rSubStr, USHORT& rIndex) const
/*N*/ {
/*N*/   USHORT i;
/*N*/   for (i=0; i<nTokenCount; i++)
/*N*/       if (rSubStr == pSubStrings[i])
/*N*/       {
/*N*/           rIndex = i;
/*N*/           return TRUE;
/*N*/       }
/*N*/
/*N*/   String aUpStr = rSubStr;
/*N*/   ScGlobal::pCharClass->toUpper(aUpStr);
/*N*/   for (i=0; i<nTokenCount; i++)
/*N*/       if (aUpStr == pUpperSub[i])
/*N*/       {
/*N*/           rIndex = i;
/*N*/           return TRUE;
/*N*/       }
/*N*/
/*N*/   return FALSE;
/*N*/ }

//STRIP001 String ScUserListData::GetSubStr(USHORT nIndex) const
//STRIP001 {
//STRIP001  if (nIndex < nTokenCount)
//STRIP001      return pSubStrings[nIndex];
//STRIP001  else
//STRIP001      return EMPTY_STRING;
//STRIP001 }

//STRIP001 StringCompare ScUserListData::Compare(const String& rSubStr1, const String& rSubStr2) const
//STRIP001 {
//STRIP001  USHORT nIndex1;
//STRIP001  USHORT nIndex2;
//STRIP001  BOOL bFound1 = GetSubIndex(rSubStr1, nIndex1);
//STRIP001  BOOL bFound2 = GetSubIndex(rSubStr2, nIndex2);
//STRIP001  if (bFound1)
//STRIP001  {
//STRIP001      if (bFound2)
//STRIP001      {
//STRIP001          if (nIndex1 < nIndex2)
//STRIP001              return COMPARE_LESS;
//STRIP001          else if (nIndex1 > nIndex2)
//STRIP001              return COMPARE_GREATER;
//STRIP001          else
//STRIP001              return COMPARE_EQUAL;
//STRIP001      }
//STRIP001      else
//STRIP001          return COMPARE_LESS;
//STRIP001  }
//STRIP001  else if (bFound2)
//STRIP001      return COMPARE_GREATER;
//STRIP001  else
//STRIP001         return (StringCompare) ScGlobal::pCaseTransliteration->compareString( rSubStr1, rSubStr2 );
//STRIP001 }

//STRIP001 StringCompare ScUserListData::ICompare(const String& rSubStr1, const String& rSubStr2) const
//STRIP001 {
//STRIP001  USHORT nIndex1;
//STRIP001  USHORT nIndex2;
//STRIP001  BOOL bFound1 = GetSubIndex(rSubStr1, nIndex1);
//STRIP001  BOOL bFound2 = GetSubIndex(rSubStr2, nIndex2);
//STRIP001  if (bFound1)
//STRIP001  {
//STRIP001      if (bFound2)
//STRIP001      {
//STRIP001          if (nIndex1 < nIndex2)
//STRIP001              return COMPARE_LESS;
//STRIP001          else if (nIndex1 > nIndex2)
//STRIP001              return COMPARE_GREATER;
//STRIP001          else
//STRIP001              return COMPARE_EQUAL;
//STRIP001      }
//STRIP001      else
//STRIP001          return COMPARE_LESS;
//STRIP001  }
//STRIP001  else if (bFound2)
//STRIP001      return COMPARE_GREATER;
//STRIP001  else
//STRIP001         return (StringCompare) ScGlobal::pTransliteration->compareString( rSubStr1, rSubStr2 );
//STRIP001 }

/*N*/ ScUserList::ScUserList(USHORT nLim, USHORT nDel) :
/*N*/   Collection  ( nLim, nDel )
/*N*/ {
/*N*/     using namespace ::com::sun::star;
/*N*/
/*N*/   sal_Unicode cDelimiter = ScGlobal::cListDelimiter;
/*N*/   uno::Sequence< i18n::CalendarItem > xCal;
/*N*/
/*N*/     uno::Sequence< i18n::Calendar > xCalendars(
/*N*/             ScGlobal::pLocaleData->getAllCalendars() );
/*N*/
/*N*/     for ( sal_Int32 j = 0; j < xCalendars.getLength(); ++j )
/*N*/     {
/*N*/         xCal = xCalendars[j].Days;
/*N*/         if ( xCal.getLength() )
/*N*/         {
/*N*/             String sDayShort, sDayLong;
/*N*/             sal_Int32 i;
/*N*/             sal_Int32 nCount = xCal.getLength() - 1;
/*N*/             for (i = 0; i < nCount; i++)
/*N*/             {
/*N*/                 sDayShort += String( xCal[i].AbbrevName );
/*N*/                 sDayShort += cDelimiter;
/*N*/                 sDayLong  += String( xCal[i].FullName );
/*N*/                 sDayLong  += cDelimiter;
/*N*/             }
/*N*/             sDayShort += String( xCal[i].AbbrevName );
/*N*/             sDayLong  += String( xCal[i].FullName );
/*N*/
/*N*/             if ( !HasEntry( sDayShort ) )
/*N*/                 Insert( new ScUserListData( sDayShort ));
/*N*/             if ( !HasEntry( sDayLong ) )
/*N*/                 Insert( new ScUserListData( sDayLong ));
/*N*/         }
/*N*/
/*N*/         xCal = xCalendars[j].Months;
/*N*/         if ( xCal.getLength() )
/*N*/         {
/*N*/             String sMonthShort, sMonthLong;
/*N*/             sal_Int32 i;
/*N*/             sal_Int32 nCount = xCal.getLength() - 1;
/*N*/             for (i = 0; i < nCount; i++)
/*N*/             {
/*N*/                 sMonthShort += String( xCal[i].AbbrevName );
/*N*/                 sMonthShort += cDelimiter;
/*N*/                 sMonthLong  += String( xCal[i].FullName );
/*N*/                 sMonthLong  += cDelimiter;
/*N*/             }
/*N*/             sMonthShort += String( xCal[i].AbbrevName );
/*N*/             sMonthLong  += String( xCal[i].FullName );
/*N*/
/*N*/             if ( !HasEntry( sMonthShort ) )
/*N*/                 Insert( new ScUserListData( sMonthShort ));
/*N*/             if ( !HasEntry( sMonthLong ) )
/*N*/                 Insert( new ScUserListData( sMonthLong ));
/*N*/         }
/*N*/     }
/*N*/ }

//STRIP001 BOOL ScUserList::Load( SvStream& rStream )
//STRIP001 {
//STRIP001  BOOL    bSuccess = TRUE;
//STRIP001  USHORT  nNewCount;
//STRIP001
//STRIP001  while( nCount > 0 )
//STRIP001      AtFree(0);                  // alles loeschen
//STRIP001
//STRIP001  rStream >> nNewCount;
//STRIP001
//STRIP001  for ( USHORT i=0; i<nNewCount && bSuccess; i++ )
//STRIP001      Insert( new ScUserListData( rStream ) );
//STRIP001
//STRIP001  return bSuccess;
//STRIP001 }

//STRIP001 BOOL ScUserList::Store( SvStream& rStream ) const
//STRIP001 {
//STRIP001  BOOL bSuccess = TRUE;
//STRIP001
//STRIP001  rStream << nCount;
//STRIP001
//STRIP001  for ( USHORT i=0; i<nCount && bSuccess; i++ )
//STRIP001      bSuccess = ((const ScUserListData*)At(i))->Store( rStream );
//STRIP001
//STRIP001  return bSuccess;
//STRIP001 }

/*N*/ DataObject* ScUserList::Clone() const
/*N*/ {
/*N*/   return ( new ScUserList( *this ) );
/*N*/ }

/*N*/ ScUserListData* ScUserList::GetData(const String& rSubStr) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   USHORT  i = 0;
/*N*/   for (i=0; i < nCount; i++)
/*N*/       if (((ScUserListData*)pItems[i])->GetSubIndex(rSubStr, nIndex))
/*?*/           return (ScUserListData*)pItems[i];
/*N*/   return NULL;
/*N*/ }

//STRIP001 BOOL ScUserList::operator==( const ScUserList& r ) const
//STRIP001 {
//STRIP001  BOOL bEqual = (nCount == r.nCount);
//STRIP001
//STRIP001  if ( bEqual )
//STRIP001  {
//STRIP001      ScUserListData* pMyData    = NULL;
//STRIP001      ScUserListData* pOtherData = NULL;
//STRIP001
//STRIP001      for ( USHORT i=0; i<nCount && bEqual; i++)
//STRIP001      {
//STRIP001          pMyData    = (ScUserListData*)At(i);
//STRIP001          pOtherData = (ScUserListData*)r.At(i);
//STRIP001
//STRIP001          bEqual =(   (pMyData->nTokenCount == pOtherData->nTokenCount)
//STRIP001                   && (pMyData->aStr        == pOtherData->aStr) );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bEqual;
//STRIP001 }


/*N*/ BOOL ScUserList::HasEntry( const String& rStr ) const
/*N*/ {
/*N*/     for ( USHORT i=0; i<nCount; i++)
/*N*/     {
/*N*/         const ScUserListData* pMyData = (ScUserListData*) At(i);
/*N*/         if ( pMyData->aStr == rStr )
/*N*/             return TRUE;
/*N*/     }
/*N*/     return FALSE;
/*N*/ }

}
