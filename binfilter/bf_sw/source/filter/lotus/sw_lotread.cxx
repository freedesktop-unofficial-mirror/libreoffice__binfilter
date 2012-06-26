/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <tools/debug.hxx>

#include "fltglbls.hxx"
#include "lotpar.hxx"
namespace binfilter {



// ---------------------------------------------- SwLotusParser::Parse() -
void SwLotusParser::Parse( void )
{
    USHORT nOpcode, nLen;
    enum { SearchBof, SearchDim, InWKS, InWK1, Ende } eAkt;

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
            OSL_FAIL( "-SwLotusParser::Read(): Unbekannter Zustand!" );
        }
        ClearBytesLeft();
    }
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
