/*************************************************************************
 *
 *  $RCSfile: sw_crypter.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: os $ $Date: 2004-04-22 15:41:24 $
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

#include <string.h>
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _CRYPTER_HXX
#include <crypter.hxx>
#endif

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

    xub_StrLen nLen = r.Len();
    if( nLen > PASSWDLEN ) nLen = PASSWDLEN;
    ByteString aPasswd( r );
    if( nLen > PASSWDLEN )
        aPasswd.Erase( nLen );
    else
        aPasswd.Expand( PASSWDLEN, ' ' );
    memcpy( cPasswd, cEncode, PASSWDLEN );
    Encrypt( aPasswd );
    memcpy( cPasswd, aPasswd.GetBuffer(), PASSWDLEN );
}



void Crypter::Encrypt( ByteString& r ) const
{
    xub_StrLen nLen = r.Len();
    if( !nLen )
        return ;

    xub_StrLen nCryptPtr = 0;
    BYTE cBuf[ PASSWDLEN ];
    memcpy( cBuf, cPasswd, PASSWDLEN );
    BYTE* pSrc = (BYTE*)r.GetBufferAccess();
    BYTE* p = cBuf;

    while( nLen-- )
    {
        *pSrc = *pSrc ^ ( *p ^ (BYTE) ( cBuf[ 0 ] * nCryptPtr ) );
        *p += ( nCryptPtr < (PASSWDLEN-1) ) ? *(p+1) : cBuf[ 0 ];
        if( !*p ) *p += 1;
        p++;
        if( ++nCryptPtr >= PASSWDLEN ) nCryptPtr = 0, p = cBuf;
        pSrc++;
    }
}



void Crypter::Decrypt( ByteString& r ) const
{
    Encrypt( r );
}



}
