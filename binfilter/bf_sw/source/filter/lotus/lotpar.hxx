/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: lotpar.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: vg $ $Date: 2006-11-20 12:38:57 $
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
#ifndef __LOTPAR_HXX__
#define __LOTPAR_HXX__

#include "fltbase.hxx"
class SvStream;
class String;
namespace binfilter {

// einige Forward-Deklaratioen

class SwPaM;
class SwDoc;


enum WKTyp {
    WKUnknown = 0,  // = unbekanntes Format
    WKS,            // = 1-2-3/1, 1-2-3/1A
    WK1,            // = 1-2-3/2
    WK3,            // = 1-2-3/3
    WK4             // = 1-2-3/4
    };


class SwLotusParser : public SwFilterBase
{
    int             bNewDoc : 1;

    WKTyp           eDateiTyp;

    // ---------------------------------------------------------------
    void Bof();                 // 0x00
    void Dimensions();          // 0x06
    void Blank1();              // 0x0C
    void Integer1();            // 0x0D
    void Number1();             // 0x0E
    void Label1();              // 0x0F
    void Formula1();            // 0x10
    // ---------------------------------------------------------------
    void            PutCell( USHORT nCol, USHORT nRow, short nVal );
    void            PutCell( USHORT nCol, USHORT nRow, double fVal );
    void            PutCell( USHORT nCol, USHORT nRow, const String &rText,
                            char cJusty );
    // ---------------------------------------------------------------
    void            Parse( void );
    void            Init( void );
public:
    // Parameter bReadNewDoc gibt an, ob in ein bestehendes Dokument ein-
    // gelesen wird. TRUE: in ein "neues" Dokument einfuegen.
    SwLotusParser( SwDoc& rDoc, const SwPaM & rCrsr, SvStream& pIn,
        int bReadNewDoc /*= TRUE*/, CharSet eQ  );

    ~SwLotusParser();

    ULONG CallParser();
};



} //namespace binfilter
#endif
    // _EXLPAR_HXX

