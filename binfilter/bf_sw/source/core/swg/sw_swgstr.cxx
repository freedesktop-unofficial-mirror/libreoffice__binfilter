/*************************************************************************
 *
 *  $RCSfile: sw_swgstr.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:04 $
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
#include "segmentc.hxx"

#include "swgstr.hxx"
#include "swgids.hxx"
namespace binfilter {

#define BUFSIZE 4096                // Groesse des Datenpuffers

/////////////////////////// class swstream ////////////////////////////////

// Diese Klasse stellt nur die Passwort-Funktionalitaet zur Verfuegung.

//STRIP001 swcrypter::swcrypter()
//STRIP001 {
//STRIP001  bPasswd = FALSE;
//STRIP001  memset( cPasswd, 0, PASSWDLEN );
//STRIP001 }

//STRIP001 BOOL swcrypter::setpasswd( const String& rP )
//STRIP001 {
//STRIP001  // Dies sind Randomwerte, die konstant zur Verschluesselung
//STRIP001  // des Passworts verwendet werden.
//STRIP001  static BYTE __READONLY_DATA cEncode[] =
//STRIP001  { 0xAB, 0x9E, 0x43, 0x05, 0x38, 0x12, 0x4d, 0x44,
//STRIP001    0xD5, 0x7e, 0xe3, 0x84, 0x98, 0x23, 0x3f, 0xba };
//STRIP001
//STRIP001  bPasswd = TRUE;
//STRIP001  xub_StrLen len = rP.Len();
//STRIP001  if( len > PASSWDLEN ) len = PASSWDLEN;
//STRIP001  memcpy( cPasswd, cEncode, PASSWDLEN );
//STRIP001  sal_Char cBuf[ PASSWDLEN ];
//STRIP001  memset( cBuf, ' ', PASSWDLEN );
//STRIP001 //   before unicode: memcpy( cBuf, p, len );
//STRIP001  for( xub_StrLen i=0; i < len; i++ )
//STRIP001  {
//STRIP001      sal_Unicode c = rP.GetChar( i );
//STRIP001      if( c > 255 )
//STRIP001          return FALSE;
//STRIP001      cBuf[i] = (sal_Char)c;
//STRIP001  }
//STRIP001  encode( cBuf, PASSWDLEN );
//STRIP001  memcpy( cPasswd, cBuf, PASSWDLEN );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void swcrypter::copypasswd( const sal_Char* p )
//STRIP001 {
//STRIP001  memcpy( cPasswd, p, PASSWDLEN );
//STRIP001  bPasswd = TRUE;
//STRIP001 }

//STRIP001 void swcrypter::encode( sal_Char* pSrc, USHORT nLen )
//STRIP001 {
//STRIP001  USHORT nCryptPtr = 0;
//STRIP001  BYTE cBuf[ PASSWDLEN ];
//STRIP001  memcpy( cBuf, cPasswd, PASSWDLEN );
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

/////////////////////////// class swstreambase /////////////////////////////

// Diese Klasse stellt einen dynamischen Puffer zur Verfuegung,
// der fuer das Einlesen von Texten verwendet wird.

//STRIP001 swstreambase::swstreambase( SvStream& r ) : pStrm( &r )
//STRIP001 {
//STRIP001  pStrm->SetBufferSize( BUFSIZE );
//STRIP001  pStrm->SetNumberFormatInt( NUMBERFORMAT_INT_LITTLEENDIAN );
//STRIP001  pBuf = new sal_Char [128];
//STRIP001  nBuflen = 128;
//STRIP001  nLong = 3;
//STRIP001  bTempStrm = FALSE;
//STRIP001 }

//STRIP001 swstreambase::~swstreambase()
//STRIP001 {
//STRIP001  delete pBuf;
//STRIP001  if( bTempStrm ) delete pStrm;
//STRIP001 }

//STRIP001 void swstreambase::checkbuf( USHORT n )
//STRIP001 {
//STRIP001  if( n > nBuflen ) {
//STRIP001      n = ( ( n + 127 ) / 128 ) * 128;
//STRIP001      if( n == 0 ) n = 0xFFFF;
//STRIP001      delete pBuf;
//STRIP001      pBuf = new sal_Char[ n ];
//STRIP001      nBuflen = n;
//STRIP001  }
//STRIP001 }

//STRIP001 void swstreambase::clear()
//STRIP001 {
//STRIP001  if( nBuflen > 128 )
//STRIP001  {
//STRIP001      delete pBuf;
//STRIP001      pBuf = new sal_Char [128];
//STRIP001      nBuflen = 128;
//STRIP001  }
//STRIP001 }

//STRIP001 BYTE swstreambase::get()
//STRIP001 {
//STRIP001  BYTE c = 0;
//STRIP001  pStrm->Read( (sal_Char*) &c, 1 );
//STRIP001  return c;
//STRIP001 }

//STRIP001 void swstreambase::setbad()
//STRIP001 {
//STRIP001  pStrm->SetError( SVSTREAM_GENERALERROR );
//STRIP001 }

//STRIP001 long swstreambase::filesize()
//STRIP001 {
//STRIP001  long cur = pStrm->Tell();
//STRIP001  long siz = pStrm->Seek( STREAM_SEEK_TO_END );
//STRIP001  pStrm->Seek( cur );
//STRIP001  return siz;
//STRIP001 }

// E/A fuer longs als 3-Byte-Zahlen

//STRIP001 swstreambase& swstreambase::operator>>( long& n )
//STRIP001 {
//STRIP001  BYTE c[ 4 ];
//STRIP001  pStrm->Read( (sal_Char*) &c, nLong );
//STRIP001  n = c[ 0 ]
//STRIP001    + (long) (USHORT) ( c[ 1 ] << 8 )
//STRIP001    + ( (long) c[ 2 ] << 16 );
//STRIP001  if( nLong == 4 )
//STRIP001  {
//STRIP001      n += (long) c[ 3 ] << 24;
//STRIP001      if ( ( sizeof( long ) > 4 ) && ( c[ 3 ] & 0x80 ) )
//STRIP001          // Vorzeichenerweiterung!
//STRIP001          n |= ~0xFFFFFFFFL;
//STRIP001  } else if( c[ 2 ] & 0x80 )
//STRIP001      // Vorzeichenerweiterung!
//STRIP001      n |= ~0xFFFFFFL;
//STRIP001  return *this;
//STRIP001 }

//////////////////////////// class swistream ///////////////////////////////

//STRIP001 swistream::swistream( SvStream& r ) : swstreambase( r )
//STRIP001 {
//STRIP001  nOffset = 0;
//STRIP001  cType = SWG_EOF;
//STRIP001 }

//STRIP001 long swistream::size()
//STRIP001 {
//STRIP001  return nOffset - pStrm->Tell();
//STRIP001 }

//STRIP001 sal_Char* swistream::text()
//STRIP001 {
//STRIP001  BOOL bSkip = FALSE;
//STRIP001  // der String ohne 0, Laenge ist im Offset (von SWG_TEXT)
//STRIP001  long len = size();
//STRIP001  // Sicherheitshalber kuerzen
//STRIP001  if( len > 0xFFF0L ) len = 0xFFF0L, bSkip = TRUE;
//STRIP001  // Eventuell den Puffer vergroessern
//STRIP001  checkbuf( (USHORT) len + 1 );
//STRIP001  pStrm->Read( pBuf, (USHORT) len );
//STRIP001  if( bPasswd )
//STRIP001      encode( pBuf, (USHORT) len );
//STRIP001  pBuf[ (USHORT) len ] = 0;
//STRIP001  if( bSkip ) skip();
//STRIP001  return pBuf;
//STRIP001 }

//STRIP001 BYTE swistream::peek()
//STRIP001 {
//STRIP001  BYTE ch = get();
//STRIP001  pStrm->SeekRel( -1 );
//STRIP001  return ch;
//STRIP001 }

//STRIP001 BYTE swistream::next()
//STRIP001 {
//STRIP001  long pos = pStrm->Tell();
//STRIP001  short n = nLong; nLong = 3;
//STRIP001  cType = get();
//STRIP001  long val;
//STRIP001  swstreambase::operator>>( val );
//STRIP001  // Man achte darauf: Dieser Wert ist immer positiv,
//STRIP001  // es findet keine VZ-Erweiterung statt!
//STRIP001  val &= 0x00FFFFFFL;
//STRIP001  if( good() ) nOffset = val + pos;
//STRIP001  nLong = n;
//STRIP001  return cType;
//STRIP001 }

//STRIP001 void swistream::undonext()
//STRIP001 {
//STRIP001  // der Read-Pointer wird um 4 Bytes zurueckversetzt
//STRIP001  long pos = pStrm->Tell();
//STRIP001  if( pos >= 4 )
//STRIP001  {
//STRIP001      pStrm->Seek( pos - 4 );
//STRIP001      nOffset = -1;   // damit skip() klappt
//STRIP001  }
//STRIP001 }

//STRIP001 void swistream::skip( long posn )
//STRIP001 {
//STRIP001  if( posn == -1L ) posn = nOffset;
//STRIP001  if( posn != -1L ) pStrm->Seek( posn );
//STRIP001 }

//STRIP001 BYTE swistream::skipnext()
//STRIP001 {
//STRIP001  pStrm->Seek( nOffset );
//STRIP001  return next();
//STRIP001 }


}
