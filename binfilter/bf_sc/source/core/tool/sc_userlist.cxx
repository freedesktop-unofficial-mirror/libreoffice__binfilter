/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_userlist.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:52:01 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

//------------------------------------------------------------------------

#include <unotools/charclass.hxx>
#include <string.h>

#include "global.hxx"
#include "userlist.hxx"

#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
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

/*N*/ ScUserListData::ScUserListData( SvStream& rStream )
/*N*/ {
/*N*/   rStream.ReadByteString( aStr, rStream.GetStreamCharSet() );
/*N*/   InitTokens();
/*N*/ }

/*N*/ BOOL ScUserListData::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   rStream.WriteByteString( aStr, rStream.GetStreamCharSet() );
/*N*/   return TRUE;
/*N*/ }



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

/*N*/ BOOL ScUserList::Load( SvStream& rStream )
/*N*/ {
/*N*/   BOOL    bSuccess = TRUE;
/*N*/   USHORT  nNewCount;
/*N*/
/*N*/   while( nCount > 0 )
/*N*/       AtFree(0);                  // alles loeschen
/*N*/
/*N*/   rStream >> nNewCount;
/*N*/
/*N*/   for ( USHORT i=0; i<nNewCount && bSuccess; i++ )
/*N*/       Insert( new ScUserListData( rStream ) );
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ BOOL ScUserList::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/
/*N*/   rStream << nCount;
/*N*/
/*N*/   for ( USHORT i=0; i<nCount && bSuccess; i++ )
/*N*/       bSuccess = ((const ScUserListData*)At(i))->Store( rStream );
/*N*/
/*N*/   return bSuccess;
/*N*/ }

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
