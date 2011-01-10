/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif


#include <tools/stream.hxx>

#include <errhdl.hxx>

#include <pam.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <ndtxt.hxx>
#include <mdiexp.hxx>           // ...Percent()
#include <docary.hxx>
#include <fmtcntnt.hxx>
#include <frmfmt.hxx>
#include <wrtasc.hxx>

#include <statstr.hrc>          // ResId fuer Statusleiste
#include <osl/endian.h>
namespace binfilter {

//-----------------------------------------------------------------

/*N*/ SwASCWriter::SwASCWriter( const String& rFltNm )
/*N*/ {
/*N*/   SwAsciiOptions aNewOpts;
/*N*/
/*N*/   switch( 5 <= rFltNm.Len() ? rFltNm.GetChar( 4 ) : 0 )
/*N*/   {
/*?*/   case 'D':
/*?*/ #if !defined(PM2)
/*?*/               aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_850 );
/*?*/               aNewOpts.SetParaFlags( LINEEND_CRLF );
/*?*/ #endif
/*?*/               if( 5 < rFltNm.Len() )
/*?*/                   switch( rFltNm.Copy( 5 ).ToInt32() )
/*?*/                   {
/*?*/                   case 437: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_437 );  break;
/*?*/                   case 850: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_850 );  break;
/*?*/                   case 860: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_860 );  break;
/*?*/                   case 861: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_861 );  break;
/*?*/                   case 863: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_863 );  break;
/*?*/                   case 865: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_865 );  break;
/*?*/                   }
/*?*/               break;
/*?*/
/*?*/   case 'A':
/*?*/ #if !defined(WIN) && !defined(WNT)
/*?*/               aNewOpts.SetCharSet( RTL_TEXTENCODING_MS_1252 );
/*?*/               aNewOpts.SetParaFlags( LINEEND_CRLF );
/*?*/ #endif
/*?*/               break;
/*?*/
/*?*/   case 'M':
/*?*/ #if !defined(MAC)
/*?*/               aNewOpts.SetCharSet( RTL_TEXTENCODING_APPLE_ROMAN );
/*?*/               aNewOpts.SetParaFlags( LINEEND_CR );
/*?*/ #endif
/*?*/               break;
/*?*/
/*?*/   case 'X':
/*?*/ #if !defined(UNX)
/*?*/               aNewOpts.SetCharSet( RTL_TEXTENCODING_MS_1252 );
/*?*/               aNewOpts.SetParaFlags( LINEEND_LF );
/*?*/ #endif
/*?*/               break;
/*?*/
/*N*/   default:
/*N*/       if( rFltNm.Copy( 4 ).EqualsAscii( "_DLG" ))
/*N*/       {
/*N*/           // use the options
/*N*/           aNewOpts = GetAsciiOptions();
/*N*/       }
/*N*/   }
/*N*/   SetAsciiOptions( aNewOpts );
/*N*/ }

/*N*/ SwASCWriter::~SwASCWriter() {}

/*N*/ void GetASCWriter( const String& rFltNm, WriterRef& xRet )
/*N*/ {
/*N*/   xRet = new SwASCWriter( rFltNm );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
