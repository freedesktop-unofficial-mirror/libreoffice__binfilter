/*************************************************************************
 *
 *  $RCSfile: swgpar.hxx,v $
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
#ifndef _SWGPAR_HXX
#define _SWGPAR_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

class UniString;
class SwDoc;
class SwPaM;
class SwSwgReader;
class SvStream;

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

#endif // _SWGPAR_HXX
