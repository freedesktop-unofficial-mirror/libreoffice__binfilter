/*************************************************************************
 *
 *  $RCSfile: sw_crypter.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:31:06 $
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


//STRIP001 #pragma hdrstop
//STRIP001
//STRIP001 #include <string.h>
//STRIP001 #ifndef _STRING_HXX //autogen
//STRIP001 #include <tools/string.hxx>
//STRIP001 #endif
//STRIP001
//STRIP001 #ifndef _CRYPTER_HXX
//STRIP001 #include <crypter.hxx>
//STRIP001 #endif
//STRIP001
//STRIP001 Crypter::Crypter( const ByteString& r )
//STRIP001 {
//STRIP001  // Dies sind Randomwerte, die konstant zur Verschluesselung
//STRIP001  // des Passworts verwendet werden. Durch die Verwendung eines
//STRIP001  // verschluesselten Passworts wird vermieden, dass das Passwort
//STRIP001  // im RAM gehalten wird.
//STRIP001  static const BYTE cEncode[] =
//STRIP001  { 0xAB, 0x9E, 0x43, 0x05, 0x38, 0x12, 0x4d, 0x44,
//STRIP001    0xD5, 0x7e, 0xe3, 0x84, 0x98, 0x23, 0x3f, 0xba };
//STRIP001
//STRIP001  xub_StrLen nLen = r.Len();
//STRIP001  if( nLen > PASSWDLEN ) nLen = PASSWDLEN;
//STRIP001  ByteString aPasswd( r );
//STRIP001  if( nLen > PASSWDLEN )
//STRIP001      aPasswd.Erase( nLen );
//STRIP001  else
//STRIP001      aPasswd.Expand( PASSWDLEN, ' ' );
//STRIP001  memcpy( cPasswd, cEncode, PASSWDLEN );
//STRIP001  Encrypt( aPasswd );
//STRIP001  memcpy( cPasswd, aPasswd.GetBuffer(), PASSWDLEN );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void Crypter::Encrypt( ByteString& r ) const
//STRIP001 {
//STRIP001  xub_StrLen nLen = r.Len();
//STRIP001  if( !nLen )
//STRIP001      return ;
//STRIP001
//STRIP001  xub_StrLen nCryptPtr = 0;
//STRIP001  BYTE cBuf[ PASSWDLEN ];
//STRIP001  memcpy( cBuf, cPasswd, PASSWDLEN );
//STRIP001  BYTE* pSrc = (BYTE*)r.GetBufferAccess();
//STRIP001  BYTE* p = cBuf;
//STRIP001
//STRIP001  while( nLen-- )
//STRIP001  {
//STRIP001      *pSrc = *pSrc ^ ( *p ^ (BYTE) ( cBuf[ 0 ] * nCryptPtr ) );
//STRIP001      *p += ( nCryptPtr < (PASSWDLEN-1) ) ? *(p+1) : cBuf[ 0 ];
//STRIP001      if( !*p ) *p += 1;
//STRIP001      p++;
//STRIP001      if( ++nCryptPtr >= PASSWDLEN ) nCryptPtr = 0, p = cBuf;
//STRIP001      pSrc++;
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void Crypter::Decrypt( ByteString& r ) const
//STRIP001 {
//STRIP001  Encrypt( r );
//STRIP001 }



