/*************************************************************************
 *
 *  $RCSfile: svx_adritem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:45:42 $
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

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _SBXVAR_HXX //autogen
#include <svtools/sbxvar.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_USEROPTIONS_HXX
#include <svtools/useroptions.hxx>
#endif
#pragma hdrstop

#include "adritem.hxx"
#include "svxids.hrc"
namespace binfilter {

#define INVALID_TOKEN ((USHORT)0xFFFF)

// -----------------------------------------------------------------------

/*?*/ String ConvertToStore_Impl( const String& rText )
/*?*/ {
/*?*/   String sRet;
/*?*/   USHORT i = 0;
/*?*/
/*?*/   while ( i < rText.Len() )
/*?*/   {
/*?*/       if ( rText.GetChar(i) == '\\' || rText.GetChar(i) == '#' )
/*?*/           sRet += '\\';
/*?*/       sRet += rText.GetChar(i++);
/*?*/   }
/*?*/   return sRet;
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1(SvxAddressItem, SfxStringItem);

// -----------------------------------------------------------------------

/*N*/ SvxAddressItem::SvxAddressItem( USHORT nWhich ) :
/*N*/
/*N*/   SfxStringItem( nWhich, String() )
/*N*/
/*N*/ {
/*N*/   SvtUserOptions aUserOpt;
/*N*/
/*N*/   aName = aUserOpt.GetLastName();
/*N*/   aFirstName = aUserOpt.GetFirstName();
/*N*/   aShortName = aUserOpt.GetID();
/*N*/
/*N*/   SetToken( POS_COMPANY, aUserOpt.GetCompany() );
/*N*/   SetToken( POS_STREET, aUserOpt.GetStreet() );
/*N*/   SetToken( POS_CITY, aUserOpt.GetCity() );
/*N*/   SetToken( POS_STATE, aUserOpt.GetState() );
/*N*/   SetToken( POS_PLZ, aUserOpt.GetZip() );
/*N*/   SetToken( POS_COUNTRY, aUserOpt.GetCountry() );
/*N*/   SetToken( POS_POSITION, aUserOpt.GetPosition() );
/*N*/   SetToken( POS_TITLE, aUserOpt.GetTitle() );
/*N*/   SetToken( POS_TEL_PRIVATE, aUserOpt.GetTelephoneHome() );
/*N*/   SetToken( POS_TEL_COMPANY, aUserOpt.GetTelephoneWork() );
/*N*/   SetToken( POS_FAX, aUserOpt.GetFax() );
/*N*/   SetToken( POS_EMAIL, aUserOpt.GetEmail() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxAddressItem::SvxAddressItem( const SvxAddressItem& rItem ) :
/*N*/
/*N*/   SfxStringItem( rItem.Which(), rItem.GetValue() ),
/*N*/
/*N*/   aName       ( rItem.aName ),
/*N*/   aFirstName  ( rItem.aFirstName ),
/*N*/   aShortName  ( rItem.aShortName )
/*N*/
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxAddressItem::SvxAddressItem( const String &rAdress,
/*N*/                               const String &rShortName,
/*N*/                               const String &rFirstName,
/*N*/                               const String &rName,
/*N*/                               USHORT nWhich ) :
/*N*/
/*N*/   SfxStringItem( nWhich, rAdress ),
/*N*/
/*N*/   aName       ( rName ),
/*N*/   aFirstName  ( rFirstName ),
/*N*/   aShortName  ( rShortName )
/*N*/
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxAddressItem::Store()
//STRIP001 {
//STRIP001  SvtUserOptions aUserOpt;
//STRIP001  aUserOpt.SetCompany( GetCompany() );
//STRIP001  aUserOpt.SetFirstName( GetFirstName() );
//STRIP001  aUserOpt.SetLastName( GetName() );
//STRIP001  aUserOpt.SetID( GetShortName() );
//STRIP001  aUserOpt.SetStreet( GetStreet() );
//STRIP001  aUserOpt.SetCity( GetCity() );
//STRIP001  aUserOpt.SetState( GetState() );
//STRIP001  aUserOpt.SetZip( GetPLZ() );
//STRIP001  aUserOpt.SetCountry( GetCountry() );
//STRIP001  aUserOpt.SetPosition( GetPosition() );
//STRIP001  aUserOpt.SetTitle( GetTitle() );
//STRIP001  aUserOpt.SetTelephoneHome( GetTelPriv() );
//STRIP001  aUserOpt.SetTelephoneWork( GetTelCompany() );
//STRIP001  aUserOpt.SetFax( GetFax() );
//STRIP001  aUserOpt.SetEmail( GetEmail() );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxAddressItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new SvxAddressItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxAddressItem::Create( SvStream& rStream, USHORT nVersion ) const
//STRIP001 {
//STRIP001  DBG_ERROR( "wer will denn ein SvxAdddressItem laden?" );
//STRIP001
//STRIP001  String aAdr, aShortName, aFirstName, aName;
//STRIP001  rStream.ReadByteString(aAdr);
//STRIP001  rStream.ReadByteString(aShortName);
//STRIP001  rStream.ReadByteString(aFirstName);
//STRIP001  rStream.ReadByteString(aName);
//STRIP001  return new SvxAddressItem( aAdr, aShortName, aFirstName, aName, Which() );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxAddressItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
//STRIP001
//STRIP001  const SvxAddressItem& rItem = (const SvxAddressItem&)rAttr;
//STRIP001
//STRIP001  return SfxStringItem::operator==(rAttr) &&
//STRIP001         ( rItem.GetName() == aName ) &&
//STRIP001         ( rItem.GetFirstName() == aFirstName ) &&
//STRIP001         ( rItem.GetShortName() == aShortName );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SvxAddressItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001  USHORT nPos = USHRT_MAX;
//STRIP001     switch ( nMemberId )
//STRIP001  {
//STRIP001         case MID_ADR_CITY           : nPos = (USHORT)POS_CITY; break;
//STRIP001         case MID_ADR_COMPANY        : nPos = (USHORT)POS_COMPANY; break;
//STRIP001         case MID_ADR_COUNTRY        : nPos = (USHORT)POS_COUNTRY; break;
//STRIP001         case MID_ADR_EMAIL          : nPos = (USHORT)POS_EMAIL; break;
//STRIP001         case MID_ADR_FAX            : nPos = (USHORT)POS_FAX; break;
//STRIP001         case MID_ADR_FIRSTNAME      : rVal <<= (::rtl::OUString) aFirstName; break;
//STRIP001         case MID_ADR_ID             : rVal <<= (::rtl::OUString) aShortName; break;
//STRIP001         case MID_ADR_LASTNAME       : rVal <<= (::rtl::OUString) aName; break;
//STRIP001         case MID_ADR_PHONE          : nPos = (USHORT)POS_TEL_COMPANY; break;
//STRIP001         case MID_ADR_PHONEPRIVATE   : nPos = (USHORT)POS_TEL_PRIVATE; break;
//STRIP001         case MID_ADR_POSITION       : nPos = (USHORT)POS_POSITION; break;
//STRIP001         case MID_ADR_STREET         : nPos = (USHORT)POS_STREET; break;
//STRIP001         case MID_ADR_TITLE          : nPos = (USHORT)POS_TITLE; break;
//STRIP001         case MID_ADR_ZIPCODE        : nPos = (USHORT)POS_PLZ; break;
//STRIP001         case MID_ADR_STATE          : nPos = (USHORT)POS_STATE ; break;
//STRIP001         case MID_ADR_FATHERSNAME    : nPos = (USHORT)POS_FATHERSNAME ; break;
//STRIP001         case MID_ADR_APARTMENT      : nPos = (USHORT)POS_APARTMENT ; break;
//STRIP001      default:
//STRIP001             DBG_ERROR( "can't interprete Id" );
//STRIP001             return sal_False;
//STRIP001  }
//STRIP001
//STRIP001  if ( nPos != USHRT_MAX )
//STRIP001         rVal <<= (::rtl::OUString) GetToken(nPos);
//STRIP001     return sal_True;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SvxAddressItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001     ::rtl::OUString aString;
//STRIP001     rVal >>= aString;
//STRIP001
//STRIP001  String sOld;
//STRIP001  USHORT nId = USHRT_MAX;
//STRIP001     switch ( nMemberId )
//STRIP001  {
//STRIP001         case MID_ADR_CITY           : nId = (USHORT)POS_CITY; break;
//STRIP001         case MID_ADR_COMPANY        : nId = (USHORT)POS_COMPANY; break;
//STRIP001         case MID_ADR_COUNTRY        : nId = (USHORT)POS_COUNTRY; break;
//STRIP001         case MID_ADR_EMAIL          : nId = (USHORT)POS_EMAIL; break;
//STRIP001         case MID_ADR_FAX            : nId = (USHORT)POS_FAX; break;
//STRIP001         case MID_ADR_FIRSTNAME      : aFirstName = aString; break;
//STRIP001         case MID_ADR_ID             : aShortName = aString; break;
//STRIP001         case MID_ADR_LASTNAME       : aName = aString; break;
//STRIP001         case MID_ADR_PHONE          : nId = (USHORT)POS_TEL_COMPANY; break;
//STRIP001         case MID_ADR_PHONEPRIVATE   : nId = (USHORT)POS_TEL_PRIVATE; break;
//STRIP001         case MID_ADR_POSITION       : nId = (USHORT)POS_POSITION; break;
//STRIP001         case MID_ADR_STREET         : nId = (USHORT)POS_STREET; break;
//STRIP001         case MID_ADR_TITLE          : nId = (USHORT)POS_TITLE; break;
//STRIP001         case MID_ADR_ZIPCODE        : nId = (USHORT)POS_PLZ; break;
//STRIP001         case MID_ADR_STATE          : nId = (USHORT)POS_STATE ; break;
//STRIP001         case MID_ADR_FATHERSNAME    : nId = (USHORT)POS_FATHERSNAME ; break;
//STRIP001         case MID_ADR_APARTMENT      : nId = (USHORT)POS_APARTMENT ; break;
//STRIP001
//STRIP001      default:
//STRIP001             DBG_ERROR( "can't interprete Id" );
//STRIP001  }
//STRIP001
//STRIP001  if ( nId != USHRT_MAX )
//STRIP001  {
//STRIP001      // mache ggf. aus '#' -> "\#"
//STRIP001         String aVal = ConvertToStore_Impl( aString );
//STRIP001      SetToken( nId, aVal );
//STRIP001  }
//STRIP001
//STRIP001  return 0;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ BOOL SvxAddressItem::SetToken( USHORT nPos, const String &rVal )
/*N*/ {
/*N*/   // nach dem 'nPos'-ten Token suchen
/*N*/   String aAdress( GetValue() );
/*N*/   USHORT nStart, nEnd = 0;
/*N*/   for ( USHORT nNo = 0; nNo <= nPos; ++nNo )
/*N*/   {
/*N*/       // End-'#' finden
/*N*/       for ( nStart = nEnd;
/*N*/             nEnd < aAdress.Len() && aAdress.GetChar(nEnd) != '#';
/*N*/             ++nEnd )
/*N*/           if ( aAdress.GetChar(nEnd) == '\\' )
/*N*/               ++nEnd;
/*N*/
/*N*/       // aAdress[nEnd] == '#' oder am Ende, also eine Position weiter gehen
/*N*/       ++nEnd;
/*N*/
/*N*/       // ggf. fehlende '#' auff"ullen
/*N*/       if ( nNo < nPos && nEnd >= aAdress.Len() )
/*N*/           aAdress += '#';
/*N*/   }
/*N*/
/*N*/   // gefunden
/*N*/   aAdress.Erase( nStart, nEnd-nStart-1 );
/*N*/   aAdress.Insert( ::binfilter::ConvertToStore_Impl( rVal ), nStart );
/*N*/   SetValue( aAdress );
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ String SvxAddressItem::GetToken( USHORT nPos ) const
/*N*/ {
/*N*/   String sRet, sEmpty;
/*N*/   const String &rAdress = GetValue();
/*N*/   USHORT i = 0, nTxt = 0;
/*N*/
/*N*/   while ( i < rAdress.Len() )
/*N*/   {
/*N*/       while ( i < rAdress.Len() && rAdress.GetChar(i) != '#' )
/*N*/       {
/*N*/           if ( rAdress.GetChar(i) == '\\' )
/*N*/               i++;
/*N*/           sRet += rAdress.GetChar(i++);
/*N*/       }
/*N*/
/*N*/       // rAdress[i] == '#' oder am Ende, also eine Position weiter gehen
/*N*/       i++;
/*N*/
/*N*/       if ( nPos == nTxt )
/*N*/           return sRet;
/*N*/       else if ( i >= rAdress.Len() )
/*N*/           return sEmpty;
/*N*/       else
/*N*/       {
/*N*/           sRet.Erase();
/*N*/           nTxt++;
/*N*/       }
/*N*/   }
/*N*/   return sEmpty;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SvxAddressItem::IsTokenReadonly( USHORT nToken ) const
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001
//STRIP001  switch ( nToken )
//STRIP001  {
//STRIP001      case POS_COMPANY :      nToken = USER_OPT_COMPANY;          break;
//STRIP001      case POS_STREET :       nToken = USER_OPT_STREET;           break;
//STRIP001      case POS_COUNTRY :      nToken = USER_OPT_COUNTRY;          break;
//STRIP001      case POS_PLZ :          nToken = USER_OPT_ZIP;              break;
//STRIP001      case POS_CITY :         nToken = USER_OPT_CITY;             break;
//STRIP001      case POS_TITLE :        nToken = USER_OPT_TITLE;            break;
//STRIP001      case POS_POSITION :     nToken = USER_OPT_POSITION;         break;
//STRIP001      case POS_TEL_PRIVATE :  nToken = USER_OPT_TELEPHONEHOME;    break;
//STRIP001      case POS_TEL_COMPANY :  nToken = USER_OPT_TELEPHONEWORK;    break;
//STRIP001      case POS_FAX :          nToken = USER_OPT_FAX;              break;
//STRIP001      case POS_EMAIL :        nToken = USER_OPT_EMAIL;            break;
//STRIP001      case POS_STATE :        nToken = USER_OPT_STATE;            break;
//STRIP001      case POS_FIRSTNAME :    nToken = USER_OPT_FIRSTNAME;        break;
//STRIP001      case POS_LASTNAME :     nToken = USER_OPT_LASTNAME;         break;
//STRIP001      case POS_SHORTNAME :    nToken = USER_OPT_ID;               break;
//STRIP001
//STRIP001      case POS_FATHERSNAME :
//STRIP001      case POS_APARTMENT :
//STRIP001      default:
//STRIP001      {
//STRIP001          nToken = INVALID_TOKEN;
//STRIP001          DBG_ERRORFILE( "SvxAddressItem::IsTokenReadonly(): invalid token" );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return SvtUserOptions().IsTokenReadonly( nToken );
//STRIP001 }

}
