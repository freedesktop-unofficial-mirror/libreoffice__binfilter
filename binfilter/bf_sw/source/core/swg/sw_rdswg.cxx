/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_rdswg.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:03:43 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif


#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif
namespace binfilter {



//////////////////////////////////////////////////////////////////////////////

// CodeSet-Konvertierung ab Version 22:

//////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////////

// Laden des Dateikopfes
// Vor Version 0x0011 wird nur die Signatur gelesen.


// Laden der Header-Informationen
// Ab Version 0x0011 ist der Header Bestandtail eines SWG_DOCUMENT-Records.
// Die Position zeigt auf den Beginn der Infos, also entweder hinter die
// Version (s.o.) oder auf den Beginn des SWG_DOCUMENT-Records.


// Einlesen eines Strings mit Check und Konvertierung



// Einlesen und Konvertierung eines Strings in den Native-Zeichensatz
// Der Record-Header SWG_TEXT ist bereits eingelesen


/*void SwSwgReader::ConvertLineTerminators( String& rText, GUIType eFrom )
{

    GUIType eTo = System::GetGUIType();
    if( eFrom != GUI_DONTKNOW && eFrom != eTo )
    {
        String aFrom, aTo;
        short nFrom = 1, nTo = 1;
        switch( eFrom )
        {
            case GUI_WINDOWS:
            case GUI_WINDOWSNT:
            case GUI_PM:        aFrom = "\x0D\x0A"; nFrom = 2; break;
            case GUI_MAC:       aFrom = "\x0D"; break;
            default:            aFrom = "\x0A";
        }
        switch( eTo )
        {
            case GUI_WINDOWS:
            case GUI_WINDOWSNT:
            case GUI_PM:        aTo = "\x0D\x0A"; nTo = 2; break;
            case GUI_MAC:       aTo = "\x0D"; break;
            default:            aTo = "\x0A";
        }
        USHORT nPos = 0;
        for( ;; )
        {
            nPos = rText.Search( aFrom, nPos );
            if( nPos == STRING_NOTFOUND ) break;
            rText.Erase( nPos, nFrom );
            rText.Insert( aTo, nPos );
            nPos += nTo;
        }
    }
}*/

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////

// Der Returnwert ist der errno-Fehlercode


// Einlesen einer Textblock-Datei
// Hier wird alles ausser dem Inhalt eingelesen.
// Der Inhalt wird nach SWG_TEXTBLOCK-Records durchsucht.
// Dabei werden in allen Textbloecken die Referenzzaehler fuer Formate
// inkrementiert.

// Ansonsten ist die Funktion analog zu Read().




}
