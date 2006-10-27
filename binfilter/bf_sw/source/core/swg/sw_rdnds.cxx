/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_rdnds.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:03:21 $
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


#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {


//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

// Text-Hints
// nOffset ist ungleich Null, wenn innerhalb eines Nodes eingefuegt werden
// soll. Dann ist nOffset die Start-Position des Textes.


// Bookmarks:


// Hilfsroutine fuer ConvertText: Suche nach dem naechsten Hint,
// der eine Konversion verbietet. Zur Zeit sind dies Hints, die entweder
// direkt oder indirekt auf einen Font mit CHARSET_SYMBOL hinweisen.


// Text Node konvertieren
// Wird aufgerufen, wenn sich die Systeme unterscheiden. Der Text wird
// vom einen in den anderen Zeichensatz konvertiert. Nicht konvertierbare
// Zeichen werden farblich unterlegt; Hints mit CHARSET_SYMBOL-Zeichensaetzen
// werden uebersprungen


// Attributsack mit einem anderen Sack fuellen. Dies ist der Fall,
// wenn auf Autoformate eines anderen Nodes Bezug genommen wird.


// all textattributes can ask for here textcharacter. But in the node is the
// converted text, were they don't found the right characters. So they need
// a access to the original text, which will be done by this class. The read
// can be called recursiv!!


// Text Node einlesen
// Falls kein Node angegeben ist, wird ein neuer Node an der angegebenen
// Position erzeugt.

// Einlesen des puren Textes eines TextNodes. Der Text wird an den vorhandenen
// Text im String angefuegt.


// Die Formate von Grafik- und OLE-Nodes muessen nicht registriert
// werden; die Layout-Frames erhalten ja eine Node-Referenz.


// OLE-Node:




}
