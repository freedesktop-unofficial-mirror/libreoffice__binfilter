/*************************************************************************
 *
 *  $RCSfile: redlenum.hxx,v $
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
#ifndef _REDLENUM_HXX
#define _REDLENUM_HXX


// Redline Typen
enum SwRedlineType
{
    // die RedlineTypen gehen von 0 bis 127
    REDLINE_INSERT,             // Inhalt wurde eingefuegt
    REDLINE_DELETE,             // Inhalt wurde geloescht
    REDLINE_FORMAT,             // Attributierung wurde angewendet
    REDLINE_TABLE,              // TabellenStruktur wurde veraendert
    REDLINE_FMTCOLL,            // FormatVorlage wurde veraendert (Autoformat!)

    // ab 128 koennen Flags hineinverodert werden
    REDLINE_NO_FLAG_MASK    = 0x007f,
    REDLINE_FLAG_MASK       = 0xff80,
    REDLINE_FORM_AUTOFMT    = 0x0080    // kann als Flag im RedlineType stehen
};


// Redline Modus vom Doc
enum SwRedlineMode
{
    REDLINE_NONE,                       // kein RedlineMode
    REDLINE_ON      = 0x01,             // RedlineMode on
    REDLINE_IGNORE  = 0x02,             // auf Redlines nicht reagieren

    REDLINE_SHOW_INSERT = 0x10,     // alle Einfuegungen anzeigen
    REDLINE_SHOW_DELETE = 0x20,     // alle Loeschungen anzeigen

    REDLINE_SHOW_MASK = REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE,

    // fuer die interne Verwaltung:
    //  die originalen Redlines inclusive des Contents entfernen
    //  (ClipBoard/Textbausteine)
    REDLINE_DELETE_REDLINES = 0x100,
    //  beim Loeschen innerhalb ein RedlineObjectes, waehrend des Appends,
    // das DeleteRedline ignorieren
    REDLINE_IGNOREDELETE_REDLINES = 0x200,
    // don't combine any readlines. This flags is may only used in the Undo.
    REDLINE_DONTCOMBINE_REDLINES = 0x400
};

inline int IsShowChanges( const USHORT eM )
{
    return (REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE) ==
                    (eM & REDLINE_SHOW_MASK);
}
inline int IsHideChanges( const USHORT eM )
{
    return REDLINE_SHOW_INSERT == (eM & REDLINE_SHOW_MASK);
}
inline int IsShowOriginal( const USHORT eM )
{
    return REDLINE_SHOW_DELETE == (eM & REDLINE_SHOW_MASK);
}
inline int IsRedlineOn( const USHORT eM )
{
    return REDLINE_ON == (eM & (REDLINE_ON | REDLINE_IGNORE ));
}



#endif
