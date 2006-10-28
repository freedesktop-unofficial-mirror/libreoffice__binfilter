/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw3io.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:53:13 $
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
    void  SetDoc( SwDoc& );
    void  SetReadOptions( const SwgReaderOption& rOpt, BOOL bOverwrite=TRUE );
    void  SetSw31Export( BOOL b31 );

     SvStorage* GetStorage();
    void  HandsOff();
    BOOL  SaveCompleted( SvStorage* );

     ULONG SaveStyles();
    // Erzeugen eines eindeutigen Streamnamens im gegebenen Storage
    static UniString UniqueName( SvStorage*, const sal_Char* pPrefix );

    // Ermitteln aller Sections eines Dokuments
};

} //namespace binfilter
#endif
