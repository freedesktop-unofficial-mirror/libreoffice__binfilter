/*************************************************************************
 *
 *  $RCSfile: sw3io.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-20 04:58:58 $
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
#ifndef _SW3IO_HXX
#define _SW3IO_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class SvStorage;
class SvStrings;
class UniString;
class SvxMacroTableDtor;

namespace binfilter {

class Sw3IoImp;
class SwPaM;
class SwDoc;

class SwgReaderOption;

#define DRAWING_STREAM_NAME     "DrawingLayer"

class Sw3Io
{
    friend class Sw3IoImp;
    Sw3IoImp* pImp;                 // Implementationsdaten

    // nur ueber diese beiden Klassen darf ein Load/Save erfolgen!!
    friend class Sw3Reader;
    friend class Sw3Writer;

    ULONG Load( SvStorage*, SwPaM* = NULL );
    ULONG Save( SwPaM* = NULL, BOOL = TRUE );
    ULONG SaveAs( SvStorage*, SwPaM* = NULL, BOOL = TRUE );

public:
    Sw3Io( SwDoc& );
   ~Sw3Io();
    Sw3IoImp* GetImp() { return pImp; }
//STRIP001  void  SetDoc( SwDoc& );
    void  SetReadOptions( const SwgReaderOption& rOpt, BOOL bOverwrite=TRUE );
//STRIP001  void  SetSw31Export( BOOL b31 );

     SvStorage* GetStorage();
    void  HandsOff();
    BOOL  SaveCompleted( SvStorage* );

//STRIP001  ULONG LoadStyles( SvStorage* );
     ULONG SaveStyles();
    // Erzeugen eines eindeutigen Streamnamens im gegebenen Storage
    static UniString UniqueName( SvStorage*, const sal_Char* pPrefix );

    // Ermitteln aller Sections eines Dokuments
//STRIP001  ULONG GetSectionList( SvStorage*, SvStrings& rSectionList );
//STRIP001  ULONG GetMacroTable( SvStorage*, SvxMacroTableDtor& rMacroTbl );
};

} //namespace binfilter
#endif
