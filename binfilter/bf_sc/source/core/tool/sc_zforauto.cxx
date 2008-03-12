/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_zforauto.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 06:58:57 $
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

#include <bf_svtools/zformat.hxx>
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







}
