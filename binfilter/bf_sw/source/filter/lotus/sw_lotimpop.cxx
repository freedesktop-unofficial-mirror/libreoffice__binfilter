/*************************************************************************
 *
 *  $RCSfile: sw_lotimpop.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:44 $
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


#pragma hdrstop

#include <stdio.h>

#include "hintids.hxx"


#ifndef _SVX_ADJITEM_HXX //autogen
#include <bf_svx/adjitem.hxx>
#endif

#include "doc.hxx"
#include "pam.hxx"
#include "swtable.hxx"
#include "lotpar.hxx"
#include "fltglbls.hxx"



// ----------------------------------------- SwLotusParser::Bof() - 0x00 -
void SwLotusParser::Bof()
    {
    USHORT nRev;

    Read( nRev );

    if( nRev == 0x0404 )
        {
        eDateiTyp = WKS;
        eQuellChar = RTL_TEXTENCODING_IBM_437;
        }
    else if( nRev == 0x0406 )
        {
        eDateiTyp = WK1;
        eQuellChar = RTL_TEXTENCODING_IBM_437;
        }
    else
        eDateiTyp = WKUnknown;

    }

// ---------------------------------- SwLotusParser::Dimensions() - 0x06 -
void SwLotusParser::Dimensions()
{
    USHORT nCS, nCE, nRS, nRE;

    Read( nCS, nRS, nCE, nRE );

    pLotGlob->ColLimitter( nCS );   // Cols/Rows in ihre Schranken verweisen
    pLotGlob->ColLimitter( nCE );

    pLotGlob->RowLimitter( nRS );
    pLotGlob->RowLimitter( nRE );

    pLotGlob->SetRange( nCS, nCE, nRS, nRE );
}


// --------------------------------------- SwLotusParser::Blank() - 0x0C -
void SwLotusParser::Blank1()
{
    BYTE nFormat;
    USHORT nCol, nRow;

    Read( nFormat, nCol, nRow );

}

// ------------------------------------ SwLotusParser::Integer1() - 0x0D -
void SwLotusParser::Integer1()
{
    BYTE nFormat;
    USHORT nCol, nRow;

    Read( nFormat, nCol, nRow );

    if( pLotGlob->IsInRange( nCol, nRow ) )
    {
        short nValue;

        Read( nValue );

        PutCell( nCol, nRow, nValue );
        //SetFormat( nCol, nRow, nTab, nFormat, 0 );
    }
}

// ------------------------------------- SwLotusParser::Number1() - 0x0E -
void SwLotusParser::Number1()
{
    BYTE nFormat;
    USHORT nCol, nRow;

    Read( nFormat, nCol, nRow );

    if( pLotGlob->IsInRange( nCol, nRow ) )
    {
        double fValue;

        Read( fValue );

        PutCell( nCol, nRow, fValue );
    }
}

// -------------------------------------- SwLotusParser::Label1() - 0x0F -
void SwLotusParser::Label1()
{
    BYTE nFormat;
    USHORT nCol, nRow;

    Read( nFormat, nCol, nRow );

    if( pLotGlob->IsInRange( nCol, nRow ) )
    {
        sal_Char cPrefix;
        String aLabel;

        ReadChar( cPrefix );
        Read( aLabel );

        PutCell( nCol, nRow, aLabel, cPrefix );
    }
}

// ------------------------------------ SwLotusParser::Formula1() - 0x10 -
void SwLotusParser::Formula1()
    {
    BYTE nFormat;
    USHORT nCol, nRow;

    Read( nFormat, nCol, nRow );


    if( pLotGlob->IsInRange( nCol, nRow ) )
        {
        double fValue;

        Read( fValue );

        PutCell( nCol, nRow, fValue );
        // nFormat = Standard -> Nachkommastellen wie Float
        //SetFormat( nCol, nRow, nTab, nFormat, nDezFloat );
        }
    }

//--------------------------------- SwLotusParser::PutCell( ..., short ) -
void SwLotusParser::PutCell( USHORT nCol, USHORT nRow, short nVal )
{
    PutCell( nCol, nRow, String( nVal ), '"' );
}

//-------------------------------- SwLotusParser::PutCell( ..., double ) -
void SwLotusParser::PutCell( USHORT nCol, USHORT nRow, double fVal )
{

    String sText(String::CreateFromFloat(fVal));
    xub_StrLen nLen = sText.Len();
    for (xub_StrLen nI = 0; nI <  nLen; ++nI)
    {
                                // Q&D tauschen ',' <-> '.'  -> nur
                                //  fuer deutsche Version brauchbar!
        if( sText.GetChar(nI) == '.' )
            sText.SetChar(nI, ',');
        else if( sText.GetChar(nI) == ',' )
            sText.SetChar(nI, '.');
    }

    PutCell( nCol, nRow, sText, '"' );
}

//-------------------------- SwLotusParser::PutCell( ..., String, char ) -
void SwLotusParser::PutCell( USHORT nCol, USHORT nRow,
    const String &rText, sal_Char cJusty )
{
    pLotGlob->Normalize( nCol, nRow );
    pLotGlob->InsertText( nCol, nRow, rText );

    SvxAdjust eAdjust = SVX_ADJUST_LEFT;
    switch( cJusty )
    {
    case '"':   // rechtsbuendig
        eAdjust =  SVX_ADJUST_RIGHT;
        break;
    case '^':   // zentriert
        eAdjust =  SVX_ADJUST_CENTER;
        break;
    }

    pLotGlob->InsertAttr( SvxAdjustItem( eAdjust ) );
}
