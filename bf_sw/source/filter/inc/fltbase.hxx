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
#ifndef __FLTBASE_HXX__
#define __FLTBASE_HXX__

#include <tools/stream.hxx>
#include <bf_tools/string.hxx>

namespace binfilter {

class SwFilterBase
{
protected:
    SvStream    *pIn;
    sal_Char    *pReadBuff; //      Groessenangabe
    INT32       nBytesLeft; // noch zu lesende Bytes des aktuelle Records

    CharSet     eQuellChar; // Quell-Zeichensatz (interner Zeichensatz)
//  CharSet     eZielChar;  // Ziel-Zeichensatz

    USHORT      nTab;       // z.Zt. bearbeitete Tabelle
    USHORT      nReadBuffSize;// temporaerer Lesepuffer mit

    // ----------------------------------------------------------
    inline void ReadChar( char &rC );
    inline void ReadByte( BYTE &rN );
    inline void Read( short &rN );
    inline void ReadUnicode( sal_Unicode &rU );
    inline void Read( BYTE &rN0, USHORT &rN1, USHORT &rN2 );
    inline void Read( USHORT &rN );
    inline void Read( USHORT &rN1, USHORT &rN2 );
    inline void Read( USHORT &rN1, USHORT &rN2, USHORT &rN3, USHORT &rN4 );
    inline void Read( double &rF );
            void Read( String &rS );        // liest 0-terminierten C-String!
    inline void ClearBytesLeft( void );
};


inline void SwFilterBase::ReadChar( char &rC )
    {
    *pIn >> rC;
    nBytesLeft--;
    }

inline void SwFilterBase::ReadByte( BYTE &rN )
    {
    *pIn >> rN;
    nBytesLeft--;
    }

inline void SwFilterBase::ReadUnicode( sal_Unicode &rU )
{
    {
    sal_Char cC;
    *pIn >> cC;
    rU = ByteString::ConvertToUnicode(cC, eQuellChar);
    nBytesLeft--;
    }
}

inline void SwFilterBase::Read( short &rN )
    {
    *pIn >> rN;
    nBytesLeft -= 2;
    }

inline void SwFilterBase::Read( BYTE &rN0, USHORT &rN1, USHORT &rN2 )
    {
    *pIn >> rN0 >> rN1 >> rN2;
    nBytesLeft -= 5;
    }

inline void SwFilterBase::Read( USHORT &rN )
    {
    *pIn >> rN;
    nBytesLeft -= 2;
    }

inline void SwFilterBase::Read( USHORT &rN1, USHORT &rN2 )
    {
    *pIn >> rN1 >> rN2;
    nBytesLeft -= 4;
    }

inline void SwFilterBase::Read( USHORT &rN1, USHORT &rN2, USHORT &rN3, USHORT &rN4 )
    {
    *pIn >> rN1 >> rN2 >> rN3 >> rN4;
    nBytesLeft -= 8;
    }

inline void SwFilterBase::Read( double &rF )
    {
    *pIn >> rF;
    nBytesLeft -= 8;
    }

inline void SwFilterBase::ClearBytesLeft( void )
    {
    pIn->SeekRel( nBytesLeft );
    nBytesLeft = 0;
    }


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
