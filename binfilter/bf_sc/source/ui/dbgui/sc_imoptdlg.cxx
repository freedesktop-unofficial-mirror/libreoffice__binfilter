/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_imoptdlg.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:03:21 $
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

#pragma hdrstop

#include "imoptdlg.hxx"
#include "imoptdlg.hrc"

#ifndef _RTL_TENCINFO_H
#include <rtl/tencinfo.h>
#endif

static const sal_Char pStrFix[] = "FIX";

namespace binfilter {

class ScDelimiterTable
{
public:
        ScDelimiterTable( const String& rDelTab )
            :   theDelTab ( rDelTab ),
                cSep      ( '\t' ),
                nCount    ( rDelTab.GetTokenCount('\t') ),
                nIter     ( 0 )
            {}

    String  FirstDel()  { nIter = 0; return theDelTab.GetToken( nIter, cSep ); }
    String  NextDel()   { nIter +=2; return theDelTab.GetToken( nIter, cSep ); }

private:
    const String        theDelTab;
    const sal_Unicode   cSep;
    const xub_StrLen    nCount;
    xub_StrLen          nIter;
};

//------------------------------------------------------------------------

/*N*/ ScImportOptions::ScImportOptions( const String& rStr )
/*N*/ {
/*N*/     bFixedWidth = FALSE;
/*N*/     nFieldSepCode = 0;
/*N*/   if ( rStr.GetTokenCount(',') >= 3 )
/*N*/   {
/*N*/         String aToken( rStr.GetToken( 0, ',' ) );
/*N*/         if( aToken.EqualsIgnoreCaseAscii( pStrFix ) )
/*N*/             bFixedWidth = TRUE;
/*N*/         else
/*N*/             nFieldSepCode = (sal_Unicode) aToken.ToInt32();
/*N*/       nTextSepCode  = (sal_Unicode) rStr.GetToken(1,',').ToInt32();
/*N*/       aStrFont      = rStr.GetToken(2,',');
/*N*/       eCharSet      = ScGlobal::GetCharsetValue(aStrFont);
/*N*/   }
/*N*/ }
/*N*/
//------------------------------------------------------------------------

/*N*/ void ScImportOptions::SetTextEncoding( rtl_TextEncoding nEnc )
/*N*/ {
/*N*/   eCharSet = (nEnc == RTL_TEXTENCODING_DONTKNOW ?
/*N*/       gsl_getSystemTextEncoding() : nEnc);
/*N*/   aStrFont = ScGlobal::GetCharsetString( nEnc );
/*N*/ }
}
