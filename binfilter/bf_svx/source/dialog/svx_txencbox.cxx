/*************************************************************************
 *
 *  $RCSfile: svx_txencbox.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:14 $
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

#pragma hdrstop

#include "txencbox.hxx"
#include "txenctab.hxx"
#include "dialogs.hrc"

#ifndef SVX_DBCHARSETHELPER_HXX
#include "dbcharsethelper.hxx"
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _RTL_TENCINFO_H
#include <rtl/tencinfo.h>
#endif
#ifndef _RTL_LOCALE_H_
#include <rtl/locale.h>
#endif
#ifndef _OSL_NLSUPPORT_H_
#include <osl/nlsupport.h>
#endif

//========================================================================
//  class SvxTextEncodingBox
//========================================================================

/*N*/ SvxTextEncodingBox::SvxTextEncodingBox( Window* pParent, const ResId& rResId )
/*N*/   :
/*N*/   ListBox( pParent, rResId )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 m_pEncTable = new SvxTextEncodingTable;
/*N*/ }

//------------------------------------------------------------------------
//STRIP001
//STRIP001 SvxTextEncodingBox::~SvxTextEncodingBox()
//STRIP001 {
//STRIP001  delete m_pEncTable;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 USHORT SvxTextEncodingBox::EncodingToPos_Impl( rtl_TextEncoding nEnc ) const
//STRIP001 {
//STRIP001  USHORT nCount = GetEntryCount();
//STRIP001  for ( USHORT i=0; i<nCount; i++ )
//STRIP001  {
//STRIP001      if ( nEnc == rtl_TextEncoding( (ULONG)GetEntryData(i) ) )
//STRIP001          return i;
//STRIP001  }
//STRIP001  return LISTBOX_ENTRY_NOTFOUND;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::FillFromTextEncodingTable(
//STRIP001         sal_Bool bExcludeImportSubsets, sal_uInt32 nExcludeInfoFlags,
//STRIP001         sal_uInt32 nButIncludeInfoFlags )
//STRIP001 {
//STRIP001     rtl_TextEncodingInfo aInfo;
//STRIP001     aInfo.StructSize = sizeof(rtl_TextEncodingInfo);
//STRIP001     USHORT nCount = m_pEncTable->Count();
//STRIP001     for ( USHORT j=0; j<nCount; j++ )
//STRIP001     {
//STRIP001         BOOL bInsert = TRUE;
//STRIP001         rtl_TextEncoding nEnc = rtl_TextEncoding( m_pEncTable->GetValue( j ) );
//STRIP001         if ( nExcludeInfoFlags )
//STRIP001         {
//STRIP001             if ( !rtl_getTextEncodingInfo( nEnc, &aInfo ) )
//STRIP001                 bInsert = FALSE;
//STRIP001             else
//STRIP001             {
//STRIP001                 if ( (aInfo.Flags & nExcludeInfoFlags) == 0 )
//STRIP001                 {
//STRIP001                     if ( (nExcludeInfoFlags & RTL_TEXTENCODING_INFO_UNICODE) &&
//STRIP001                             ((nEnc == RTL_TEXTENCODING_UCS2) ||
//STRIP001                             nEnc == RTL_TEXTENCODING_UCS4) )
//STRIP001                         bInsert = FALSE;    // InfoFlags don't work for Unicode :-(
//STRIP001                 }
//STRIP001                 else if ( (aInfo.Flags & nButIncludeInfoFlags) == 0 )
//STRIP001                     bInsert = FALSE;
//STRIP001             }
//STRIP001         }
//STRIP001         if ( bInsert )
//STRIP001         {
//STRIP001             if ( bExcludeImportSubsets )
//STRIP001             {
//STRIP001                 switch ( nEnc )
//STRIP001                 {
//STRIP001                     // subsets of RTL_TEXTENCODING_GB_18030
//STRIP001                     case RTL_TEXTENCODING_GB_2312 :
//STRIP001                     case RTL_TEXTENCODING_GBK :
//STRIP001                     case RTL_TEXTENCODING_MS_936 :
//STRIP001                         bInsert = FALSE;
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001             if ( bInsert )
//STRIP001                 InsertTextEncoding( nEnc, m_pEncTable->GetString( j ) );
//STRIP001         }
//STRIP001     }
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::FillFromDbTextEncodingMap(
//STRIP001         sal_Bool bExcludeImportSubsets, sal_uInt32 nExcludeInfoFlags,
//STRIP001         sal_uInt32 nButIncludeInfoFlags )
//STRIP001 {
//STRIP001     rtl_TextEncodingInfo aInfo;
//STRIP001     aInfo.StructSize = sizeof(rtl_TextEncodingInfo);
//STRIP001     svxform::ODataAccessCharsetHelper aCSH;
//STRIP001     ::std::vector< rtl_TextEncoding > aEncs;
//STRIP001     sal_Int32 nCount = aCSH.getSupportedTextEncodings( aEncs );
//STRIP001     for ( USHORT j=0; j<nCount; j++ )
//STRIP001     {
//STRIP001         BOOL bInsert = TRUE;
//STRIP001         rtl_TextEncoding nEnc = rtl_TextEncoding( aEncs[j] );
//STRIP001         if ( nExcludeInfoFlags )
//STRIP001         {
//STRIP001             if ( !rtl_getTextEncodingInfo( nEnc, &aInfo ) )
//STRIP001                 bInsert = FALSE;
//STRIP001             else
//STRIP001             {
//STRIP001                 if ( (aInfo.Flags & nExcludeInfoFlags) == 0 )
//STRIP001                 {
//STRIP001                     if ( (nExcludeInfoFlags & RTL_TEXTENCODING_INFO_UNICODE) &&
//STRIP001                             ((nEnc == RTL_TEXTENCODING_UCS2) ||
//STRIP001                             nEnc == RTL_TEXTENCODING_UCS4) )
//STRIP001                         bInsert = FALSE;    // InfoFlags don't work for Unicode :-(
//STRIP001                 }
//STRIP001                 else if ( (aInfo.Flags & nButIncludeInfoFlags) == 0 )
//STRIP001                     bInsert = FALSE;
//STRIP001             }
//STRIP001         }
//STRIP001         if ( bInsert )
//STRIP001         {
//STRIP001             if ( bExcludeImportSubsets )
//STRIP001             {
//STRIP001                 switch ( nEnc )
//STRIP001                 {
//STRIP001                     // subsets of RTL_TEXTENCODING_GB_18030
//STRIP001                     case RTL_TEXTENCODING_GB_2312 :
//STRIP001                     case RTL_TEXTENCODING_GBK :
//STRIP001                     case RTL_TEXTENCODING_MS_936 :
//STRIP001                         bInsert = FALSE;
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001             // CharsetMap offers a RTL_TEXTENCODING_DONTKNOW for internal use,
//STRIP001             // makes no sense here and would result in an empty string as list
//STRIP001             // entry.
//STRIP001             if ( bInsert && nEnc != RTL_TEXTENCODING_DONTKNOW )
//STRIP001                 InsertTextEncoding( nEnc );
//STRIP001         }
//STRIP001     }
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 // static
//STRIP001 rtl_TextEncoding SvxTextEncodingBox::GetBestMimeEncoding()
//STRIP001 {
//STRIP001     const sal_Char* pCharSet = rtl_getBestMimeCharsetFromTextEncoding(
//STRIP001             gsl_getSystemTextEncoding() );
//STRIP001     if ( !pCharSet )
//STRIP001     {
//STRIP001         // If the system locale is unknown to us, e.g. LC_ALL=xx, match the UI
//STRIP001         // language if possible.
//STRIP001         ::com::sun::star::lang::Locale aLocale(
//STRIP001                 Application::GetSettings().GetUILocale() );
//STRIP001         rtl_Locale * pLocale = rtl_locale_register( aLocale.Language.getStr(),
//STRIP001                 aLocale.Country.getStr(), aLocale.Variant.getStr() );
//STRIP001         rtl_TextEncoding nEnc = osl_getTextEncodingFromLocale( pLocale );
//STRIP001         pCharSet = rtl_getBestMimeCharsetFromTextEncoding( nEnc );
//STRIP001     }
//STRIP001     rtl_TextEncoding nRet;
//STRIP001     if ( pCharSet )
//STRIP001         nRet = rtl_getTextEncodingFromMimeCharset( pCharSet );
//STRIP001     else
//STRIP001         nRet = RTL_TEXTENCODING_UTF8;
//STRIP001     return nRet;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::FillWithMimeAndSelectBest()
//STRIP001 {
//STRIP001  FillFromTextEncodingTable( sal_False, 0xffffffff, RTL_TEXTENCODING_INFO_MIME );
//STRIP001     rtl_TextEncoding nEnc = GetBestMimeEncoding();
//STRIP001     SelectTextEncoding( nEnc );
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::InsertTextEncoding( const rtl_TextEncoding nEnc,
//STRIP001          const String& rEntry, USHORT nPos )
//STRIP001 {
//STRIP001  USHORT nAt = InsertEntry( rEntry, nPos );
//STRIP001  SetEntryData( nAt, (void*)(ULONG)nEnc );
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::InsertTextEncoding( const rtl_TextEncoding nEnc, USHORT nPos )
//STRIP001 {
//STRIP001     const String& rEntry = m_pEncTable->GetTextString( nEnc );
//STRIP001     if ( rEntry.Len() )
//STRIP001         InsertTextEncoding( nEnc, rEntry, nPos );
//STRIP001     else
//STRIP001     {
//STRIP001 #ifdef DBG_UTIL
//STRIP001         ByteString aMsg( "SvxTextEncodingBox::InsertTextEncoding: no resource string for text encoding: " );
//STRIP001         aMsg += ByteString::CreateFromInt32( nEnc );
//STRIP001         DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001     }
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::RemoveTextEncoding( const rtl_TextEncoding nEnc )
//STRIP001 {
//STRIP001  USHORT nAt = EncodingToPos_Impl( nEnc );
//STRIP001
//STRIP001  if ( nAt != LISTBOX_ENTRY_NOTFOUND )
//STRIP001      RemoveEntry( nAt );
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 rtl_TextEncoding SvxTextEncodingBox::GetSelectTextEncoding() const
//STRIP001 {
//STRIP001  USHORT nPos = GetSelectEntryPos();
//STRIP001
//STRIP001  if ( nPos != LISTBOX_ENTRY_NOTFOUND )
//STRIP001      return rtl_TextEncoding( (ULONG)GetEntryData(nPos) );
//STRIP001  else
//STRIP001      return RTL_TEXTENCODING_DONTKNOW;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SvxTextEncodingBox::SelectTextEncoding( const rtl_TextEncoding nEnc, BOOL bSelect )
//STRIP001 {
//STRIP001  USHORT nAt = EncodingToPos_Impl( nEnc );
//STRIP001
//STRIP001  if ( nAt != LISTBOX_ENTRY_NOTFOUND )
//STRIP001      SelectEntryPos( nAt, bSelect );
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 BOOL SvxTextEncodingBox::IsTextEncodingSelected( const rtl_TextEncoding nEnc ) const
//STRIP001 {
//STRIP001  USHORT nAt = EncodingToPos_Impl( nEnc );
//STRIP001
//STRIP001  if ( nAt != LISTBOX_ENTRY_NOTFOUND )
//STRIP001      return IsEntryPosSelected( nAt );
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

