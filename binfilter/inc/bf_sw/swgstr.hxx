/*************************************************************************
 *
 *  $RCSfile: swgstr.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:53 $
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

#ifndef _SWGSTR_HXX
#define _SWGSTR_HXX

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

typedef long long3;                     // Zur Dokumentation: 3-byte-Longs

#define MAX_BEGIN 64                    // Maximale Blockschachtelung
#define PASSWDLEN 16                    // Maximale Passwortlaenge

// Neue Version mit SvStreams

// Passwort- und Codierungs-Funktionalitaet

//STRIP001 class swcrypter {
//STRIP001 protected:
//STRIP001  sal_Char   cPasswd[ PASSWDLEN ];    // Passwort-Puffer
//STRIP001  BOOL   bPasswd;                     // TRUE wenn mit Passwort
//STRIP001  void   encode( sal_Char*, USHORT ); // Puffer codieren/decodieren
//STRIP001 public:
//STRIP001  swcrypter();
//STRIP001  BOOL setpasswd( const String& );    // Passwort setzen
//STRIP001  void copypasswd( const sal_Char* ); // Passwort direkt setzen
//STRIP001  const sal_Char* getpasswd() { return cPasswd; }
//STRIP001 };

// Reader/Writer-Stream-Basisklasse mit Pufferverwaltung fuer Texte
// und Spezial-I/O fuer 3-Byte-Longs

//STRIP001 class swstreambase : public swcrypter {
//STRIP001 protected:
//STRIP001  SvStream* pStrm;                    // eigentlicher Stream
//STRIP001  sal_Char*  pBuf;                        // Zwischenpuffer
//STRIP001  USHORT nBuflen;                     // Laenge des Zwischenpuffers
//STRIP001  short  nLong;                       // Long-Laenge (3 oder 4)
//STRIP001  BOOL   bTempStrm;                   // TRUE: Stream loeschen
//STRIP001  void   checkbuf( USHORT );          // Testen der Pufferlaenge
//STRIP001
//STRIP001  swstreambase( SvStream& );
//STRIP001
//STRIP001  swstreambase( const swstreambase& );
//STRIP001  int operator=( const swstreambase& );
//STRIP001 public:
//STRIP001  ~swstreambase();
//STRIP001  SvStream& Strm()                    { return *pStrm; }
//STRIP001  void clear();                       // Puffer loeschen
//STRIP001  sal_Char* GetBuf()                  { return pBuf; }
//STRIP001
//STRIP001  // Zusatzfunktionen zur I/O von LONGs als 3-Byte-Zahlen
//STRIP001
//STRIP001  void long3()                        { nLong = 3; }
//STRIP001  void long4()                        { nLong = 4; }
//STRIP001
//STRIP001  void sync( swstreambase& r )        { pStrm->Seek( r.tell() ); }
//STRIP001
//STRIP001  // Alias- und Hilfsfunktionen
//STRIP001
//STRIP001  void seek( long nPos )              { pStrm->Seek( nPos );  }
//STRIP001  long tell()                         { return pStrm->Tell(); }
//STRIP001  long filesize();                    // Dateigroesse
//STRIP001  void flush()                        { pStrm->Flush(); }
//STRIP001
//STRIP001  void setbad();
//STRIP001  int good()                          { return ( pStrm->GetError() == SVSTREAM_OK ); }
//STRIP001  int bad()                           { return ( pStrm->GetError() != SVSTREAM_OK ); }
//STRIP001  int operator!()                     { return ( pStrm->GetError() != SVSTREAM_OK ); }
//STRIP001  int eof()                           { return pStrm->IsEof(); }
//STRIP001
//STRIP001  BYTE get();
//STRIP001  void get( void* p, USHORT n )       { pStrm->Read( (sal_Char*) p, n ); }
//STRIP001
//STRIP001  inline swstreambase& operator>>( sal_Char& );
//STRIP001  inline swstreambase& operator>>( BYTE& );
//STRIP001  inline swstreambase& operator>>( short& );
//STRIP001  inline swstreambase& operator>>( USHORT& );
//STRIP001         swstreambase& operator>>( long& );
//STRIP001  inline swstreambase& operator>>( ULONG& );
//STRIP001 };

//STRIP001 inline swstreambase& swstreambase::operator>>( sal_Char& c )
//STRIP001 {
//STRIP001  *pStrm >> c; return *this;
//STRIP001 }

//STRIP001 inline swstreambase& swstreambase::operator>>( BYTE& c )
//STRIP001 {
//STRIP001  *pStrm >> c; return *this;
//STRIP001 }

//STRIP001 inline swstreambase& swstreambase::operator>>( short& c )
//STRIP001 {
//STRIP001  *pStrm >> c; return *this;
//STRIP001 }

//STRIP001 inline swstreambase& swstreambase::operator>>( USHORT& c )
//STRIP001 {
//STRIP001  *pStrm >> c; return *this;
//STRIP001 }

//STRIP001 inline swstreambase& swstreambase::operator>>( ULONG& c )
//STRIP001 {
//STRIP001  return *this >> (long&) c;
//STRIP001 }

//STRIP001 class swistream : public swstreambase {
//STRIP001  BYTE   cType;                       // Record-Typ
//STRIP001  ULONG  nOffset;                     // Record-Offset-Portion
//STRIP001 public:
//STRIP001  swistream( SvStream& );
//STRIP001
//STRIP001  BYTE peek();                        // 1 Byte testen
//STRIP001  BYTE next();                        // Blockstart
//STRIP001  BYTE cur() { return cType; }        // aktueller Block
//STRIP001  BYTE skipnext();                    // Record ueberspringen
//STRIP001  void undonext();                    // next() rueckgaengig machen
//STRIP001  long getskip()                      { return nOffset; }
//STRIP001  void skip( long = -1L );            // Block ueberspringen
//STRIP001  sal_Char* text();                   // Textstring lesen (nach BEGIN)
//STRIP001  long size();                        // aktuelle Record-Laenge
//STRIP001
//STRIP001 private:
//STRIP001  swistream( const swistream& );
//STRIP001  int operator=( const swistream& );
//STRIP001 };


#endif
