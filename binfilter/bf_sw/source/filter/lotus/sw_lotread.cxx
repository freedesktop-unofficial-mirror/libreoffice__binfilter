/*************************************************************************
 *
 *  $RCSfile: sw_lotread.cxx,v $
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

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#include "fltglbls.hxx"
#include "lotpar.hxx"



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


