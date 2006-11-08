/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swgpar.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 13:12:42 $
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

class SwSwgParser
{
private:
    SwSwgReader* pRdr;
public:
    ULONG  CallParser( USHORT = SWGRD_NORMAL );
    BOOL NeedsPasswd();
    BOOL CheckPasswd( const UniString& );
    const SfxDocumentInfo& GetDocInfo();

    SwSwgParser( SwDoc *pSwDoc, const SwPaM* pSwPaM,
                 SvStream *pIstream, const UniString& rFileName, //$ istream
                 BOOL bNewDoc=TRUE );
    SwSwgParser( SvStream *pIstream ); //$ istream
    ~SwSwgParser();
};

} //namespace binfilter
#endif // _SWGPAR_HXX
