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

#include <osl/diagnose.h>
#include <doc.hxx>
#include <swerror.h>
#include <fltglbls.hxx>
#include <fltini.hxx>
#include <lotpar.hxx>
#include <swfltopt.hxx>
namespace binfilter {

LotGlob *pLotGlob = NULL;





SwLotusParser::SwLotusParser( SwDoc &rD, const SwPaM & rCrsr,
                                SvStream& rInInit, int bReadNewDoc,
                                CharSet eQ )
    : bNewDoc( bReadNewDoc )
{
    eQuellChar = eQ;
    pIn = &rInInit;
    pLotGlob = new LotGlob( rD, rCrsr );

    nReadBuffSize = 2048;
    pReadBuff = new char[ nReadBuffSize ];

//  aColRowBuff.SetDefWidth( ( USHORT ) ( 9192 ) ); // 4 Zeichen Standardbreite
}

SwLotusParser::~SwLotusParser()
{
    delete[] pReadBuff;
    delete pLotGlob;
    pLotGlob = NULL;
}


ULONG SwLotusParser::CallParser()
{
    static const sal_Char* aNames[4] = {
        "Excel_Lotus/MinRow", "Excel_Lotus/MaxRow",
        "Excel_Lotus/MinCol", "Excel_Lotus/MaxCol"
    };
    sal_uInt32 aVal[4];
    SwFilterOptions aOpt( 4, aNames, aVal );

    USHORT nMinRow = ( USHORT ) aVal[ 0 ];
    USHORT nMaxRow = ( USHORT ) aVal[ 1 ];
    USHORT nMinCol = ( USHORT ) aVal[ 2 ];
    USHORT nMaxCol = ( USHORT ) aVal[ 3 ];

    USHORT nAnzNodes = 65000U - pLotGlob->pD->GetNodes().Count();

    if( nMaxRow < nMinRow )
    {
        USHORT nTemp = nMinRow;
        nMinRow = nMaxRow;
        nMaxRow = nTemp;
    }

    if( nMaxCol < nMinCol )
    {
        USHORT nTemp = nMinCol;
        nMinCol = nMaxCol;
        nMaxCol = nTemp;
    }

    if( nMaxRow - nMinRow == 0 )
        nMaxRow = nMinRow + 30;     // Default bei 0 Rows

    if( nMaxCol - nMinCol == 0 )
        nMaxCol = nMinCol + 15;     // Default bei 0 Cols

    if( nAnzNodes < ( nMaxRow - nMinRow ) * ( nMaxCol - nMinCol ) * 3 )
        return ERR_EXCLOT_WRONG_RANGE;

    pLotGlob->SetRange( nMinCol, nMaxCol, nMinRow, nMaxRow ); // Default-Einstellung

    Parse();

    return 0;   // kein Fehler
}


ULONG LotusReader::Read( SwDoc &rDoc, SwPaM &rPam,
                    const String & /* FileName, falls benoetigt wird */ )
{
    ULONG nRet;
    if( !pStrm )
    {
        OSL_ENSURE( FALSE, "Lotus-Read ohne Stream" );
        nRet = ERR_SWG_READ_ERROR;
    }
    else
    {
        SwLotusParser* pParser = new SwLotusParser( rDoc, rPam, *pStrm,
                                                    !bInsertMode, eCodeSet );
        nRet = pParser->CallParser();       // 0 == kein Fehler aufgetreten
        delete pParser;
    }

    return nRet;
}



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
