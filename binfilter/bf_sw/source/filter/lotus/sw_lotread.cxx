/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_lotread.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:58:49 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#include "fltglbls.hxx"
#include "lotpar.hxx"
namespace binfilter {



// ---------------------------------------------- SwLotusParser::Parse() -
void SwLotusParser::Parse( void )
{
    USHORT nOpcode, nLen;
    enum { SearchBof, SearchDim, InWKS, InWK1, Ende } eAkt;
    BOOL bInTab = TRUE;

    eAkt = SearchBof;
    while( eAkt != Ende )
    {
        *pIn >> nOpcode >> nLen;
        if( pIn->IsEof() )
            eAkt = Ende;

        nBytesLeft = nLen;
        switch( eAkt )
        {
        case SearchBof: // ----------------------------
            if( 0x00 ==  nOpcode )
            {
                Bof();
                eAkt = SearchDim;
            }
            break;
        case SearchDim: // ----------------------------
            if( 0x06 == nOpcode )               // DIMENSIONS   [S1   ]
            {
                Dimensions();
                switch( eDateiTyp )
                {
                case WKS:
                    eAkt = InWKS;
                    pLotGlob->CreateTable();
                    break;
                case WK1:
                    eAkt = InWK1;
                    pLotGlob->CreateTable();
                    break;
                case WKUnknown:
                case WK3:
                case WK4:
                    eAkt = Ende; break;
                }
            }
            break;
        case InWKS:     // ----------------------------
        case InWK1:
            {
            switch( nOpcode )
                {
                case 0x01:                          // EOF          [S1   ]
//Leere Methode!!                   Eof();
                    eAkt = Ende;
                    break;
                case 0x0C:  Blank1(); break;        // BLANK        [S1   ]
                case 0x0D:  Integer1(); break;      // INTEGER      [S1   ]
                case 0x0E:  Number1(); break;       // NUMBER       [S1   ]
                case 0x0F:  Label1(); break;        // LABEL        [S1   ]
                case 0x10:  Formula1(); break;      // FORMULA      [S1   ]
                }
            }
            break;


        case Ende: // ---------------------------------
            break;

        default:
            DBG_ERROR( "-SwLotusParser::Read(): Unbekannter Zustand!" );
        }
        ClearBytesLeft();
    }
}


}
