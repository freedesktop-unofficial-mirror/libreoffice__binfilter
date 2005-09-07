/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_zforauto.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 17:20:08 $
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
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------------

// auto strip #include <svtools/zforlist.hxx>
#include <svtools/zformat.hxx>
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#include <tools/debug.hxx>

#include "zforauto.hxx"
#include "global.hxx"
namespace binfilter {

static const sal_Char __FAR_DATA pStandardName[] = "Standard";

//------------------------------------------------------------------------

/*N*/ ScNumFormatAbbrev::ScNumFormatAbbrev() :
/*N*/   eLnge           (LANGUAGE_SYSTEM),
/*N*/   eSysLnge        (LANGUAGE_GERMAN),      // sonst passt "Standard" nicht
/*N*/   sFormatstring   ( RTL_CONSTASCII_USTRINGPARAM( pStandardName ) )
/*N*/ {
/*N*/ }

/*N*/ ScNumFormatAbbrev::ScNumFormatAbbrev(const ScNumFormatAbbrev& aFormat) :
/*N*/   eLnge           (aFormat.eLnge),
/*N*/   eSysLnge        (aFormat.eSysLnge),
/*N*/   sFormatstring   (aFormat.sFormatstring)
/*N*/ {
/*N*/ }

/*N*/ ScNumFormatAbbrev::ScNumFormatAbbrev(SvStream& rStream)
/*N*/ {
/*N*/   Load(rStream);
/*N*/ }

//STRIP001 ScNumFormatAbbrev::ScNumFormatAbbrev(ULONG nFormat,
//STRIP001                                   SvNumberFormatter& rFormatter)
//STRIP001 {
//STRIP001  PutFormatIndex(nFormat, rFormatter);
//STRIP001 }

/*N*/ void ScNumFormatAbbrev::Load( SvStream& rStream )
/*N*/ {
/*N*/   USHORT nSysLang, nLang;
/*N*/   rStream.ReadByteString( sFormatstring, rStream.GetStreamCharSet() );
/*N*/   rStream >> nSysLang >> nLang;
/*N*/   eLnge = (LanguageType) nLang;
/*N*/   eSysLnge = (LanguageType) nSysLang;
/*N*/     if ( eSysLnge == LANGUAGE_SYSTEM )          // old versions did write it
/*N*/         eSysLnge = Application::GetSettings().GetLanguage();
/*N*/ }

/*N*/ void ScNumFormatAbbrev::Save( SvStream& rStream ) const
/*N*/ {
/*N*/   rStream.WriteByteString( sFormatstring, rStream.GetStreamCharSet() );
/*N*/   rStream << (USHORT) eSysLnge << (USHORT) eLnge;
/*N*/ }

//STRIP001 void ScNumFormatAbbrev::PutFormatIndex(ULONG nFormat,
//STRIP001                                     SvNumberFormatter& rFormatter)
//STRIP001 {
//STRIP001  const SvNumberformat* pFormat = rFormatter.GetEntry(nFormat);
//STRIP001  if (pFormat)
//STRIP001  {
//STRIP001         eSysLnge = Application::GetSettings().GetLanguage();
//STRIP001      eLnge = pFormat->GetLanguage();
//STRIP001      sFormatstring = ((SvNumberformat*)pFormat)->GetFormatstring();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR("SCNumFormatAbbrev:: unbekanntes Zahlformat");
//STRIP001      eLnge = LANGUAGE_SYSTEM;
//STRIP001      eSysLnge = LANGUAGE_GERMAN;     // sonst passt "Standard" nicht
//STRIP001      sFormatstring.AssignAscii( RTL_CONSTASCII_STRINGPARAM( pStandardName ) );
//STRIP001  }
//STRIP001 }

//STRIP001 ULONG ScNumFormatAbbrev::GetFormatIndex( SvNumberFormatter& rFormatter)
//STRIP001 {
//STRIP001  //  #62389# leerer Formatstring (vom Writer) -> Standardformat
//STRIP001  if ( !sFormatstring.Len() )
//STRIP001      return rFormatter.GetStandardIndex( eLnge );
//STRIP001
//STRIP001     if ( eLnge == LANGUAGE_SYSTEM && eSysLnge != Application::GetSettings().GetLanguage() )
//STRIP001  {
//STRIP001      ULONG nOrig = rFormatter.GetEntryKey( sFormatstring, eSysLnge );
//STRIP001      if ( nOrig != NUMBERFORMAT_ENTRY_NOT_FOUND )
//STRIP001             return rFormatter.GetFormatForLanguageIfBuiltIn( nOrig, Application::GetSettings().GetLanguage() );
//STRIP001      else
//STRIP001          return rFormatter.GetStandardIndex( eLnge );    // geht nicht -> Standard
//STRIP001  }
//STRIP001
//STRIP001  xub_StrLen nCheckPos;
//STRIP001  short nType;
//STRIP001  ULONG nKey = rFormatter.GetEntryKey(sFormatstring, eLnge);
//STRIP001  if (nKey == NUMBERFORMAT_ENTRY_NOT_FOUND)
//STRIP001  {
//STRIP001      BOOL res = rFormatter.PutEntry(sFormatstring,
//STRIP001                                     nCheckPos, nType, nKey, eLnge);
//STRIP001      if (nCheckPos > 0)
//STRIP001          DBG_ERROR("SCNumFormatAbbrev:: unkorrekter Formatstring");
//STRIP001  }
//STRIP001  return nKey;
//STRIP001 }





}
