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

#include <string.h>
#include <bf_tools/string.hxx>
#include <comphelper/string.hxx>

#include <crypter.hxx>

namespace binfilter {




Crypter::Crypter( const ByteString& r )
{
    // Dies sind Randomwerte, die konstant zur Verschluesselung
    // des Passworts verwendet werden. Durch die Verwendung eines
    // verschluesselten Passworts wird vermieden, dass das Passwort
    // im RAM gehalten wird.
    static const BYTE cEncode[] =
    { 0xAB, 0x9E, 0x43, 0x05, 0x38, 0x12, 0x4d, 0x44,
      0xD5, 0x7e, 0xe3, 0x84, 0x98, 0x23, 0x3f, 0xba };

    rtl::OStringBuffer aBuf(r);
    comphelper::string::padToLength(aBuf, PASSWDLEN, ' ');
    memcpy( cPasswd, cEncode, PASSWDLEN );
    Encrypt( aBuf );
    memcpy( cPasswd, aBuf.getStr(), PASSWDLEN );
}



void Crypter::Encrypt( rtl::OStringBuffer& r ) const
{
    sal_Int32 nLen = r.getLength(), i = 0;
    if( !nLen )
        return ;

    xub_StrLen nCryptPtr = 0;
    BYTE cBuf[ PASSWDLEN ];
    memcpy( cBuf, cPasswd, PASSWDLEN );
    BYTE* p = cBuf;

    while( nLen-- )
    {
        r[i] = r[i] ^ ( *p ^ (BYTE) ( cBuf[ 0 ] * nCryptPtr ) );
        *p += ( nCryptPtr < (PASSWDLEN-1) ) ? *(p+1) : cBuf[ 0 ];
        if( !*p )
            *p += 1;
        p++;
        if( ++nCryptPtr >= PASSWDLEN )
            nCryptPtr = 0, p = cBuf;
        ++i;
    }
}



void Crypter::Decrypt( rtl::OStringBuffer& r ) const
{
    Encrypt( r );
}



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
