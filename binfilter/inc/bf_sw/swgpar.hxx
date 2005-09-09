/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swgpar.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:30:05 $
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
#ifndef _SWGPAR_HXX
#define _SWGPAR_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class UniString;
class SvStream;
namespace binfilter {


class SwDoc;
class SwPaM;
class SwSwgReader;


class SfxDocumentInfo;

enum SwgReadOptions {
    SWGRD_CHARFMTS      = 0x0001,       // Zeichenvorlagen
    SWGRD_FRAMEFMTS     = 0x0002,       // Rahmenvorlagen
    SWGRD_PARAFMTS      = 0x0004,       // Absatzvorlagen
    SWGRD_PAGEFMTS      = 0x0008,       // Seitenvorlagen
    SWGRD_MACROS        = 0x0010,       // globale Makros
    SWGRD_NUMRULES      = 0x0020,       // globale Numerierungsregeln

    SWGRD_FORCE         = 0x1000,       // Vorlagen immer einlesen

    SWGRD_NORMAL        = 0x00FF        // alles (Normalfall)
};

//STRIP001 class SwSwgParser
//STRIP001 {
//STRIP001 private:
//STRIP001  SwSwgReader* pRdr;
//STRIP001 public:
//STRIP001  ULONG  CallParser( USHORT = SWGRD_NORMAL );
//STRIP001  BOOL NeedsPasswd();
//STRIP001  BOOL CheckPasswd( const UniString& );
//STRIP001  const SfxDocumentInfo& GetDocInfo();
//STRIP001
//STRIP001  SwSwgParser( SwDoc *pSwDoc, const SwPaM* pSwPaM,
//STRIP001               SvStream *pIstream, const UniString& rFileName, //$ istream
//STRIP001               BOOL bNewDoc=TRUE );
//STRIP001  SwSwgParser( SvStream *pIstream ); //$ istream
//STRIP001  ~SwSwgParser();
//STRIP001 };

} //namespace binfilter
#endif // _SWGPAR_HXX
