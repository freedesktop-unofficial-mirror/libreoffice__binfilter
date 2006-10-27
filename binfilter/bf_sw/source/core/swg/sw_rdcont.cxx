/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_rdcont.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:02:35 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif


#include "bookmrk.hxx"
namespace binfilter {


//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

// Contents-Teil

// Wird ein Text in einen Absatz eingefuegt, wird der erste Absatz an den
// ersten Teil angefuegt, ohne die Formate zu uebernehmen. Alle anderen
// Absaetze uebernehmen die Formate, was auch den Rest des alten Absatzes
// betrifft.
// Falls bNode1 FALSE ist, wird ein evtl. vorhandener leerer Node nicht
// gefuellt. Dadurch laesst sich diese Methode fuer mehrere Contents
// verwenden.
// Falls bBlock TRUE ist, handelt es sich um das Einlesen eies Textblock-
// Inhalts. Hier gibt es keinen Section-ID und auch keine Registrierrung
// der Section!
// nInsFirstPara - beim Document einfuegen, muss der erste Absatz
//                  sonderbehandelt werden (Absatz Attribute!)



// Einlesen des puren Textes eines Content-Bereichs


// Einfuegen einer nicht vorhandenen Contents-Section


// Fuellen einer vorhandenen Contents-Section
// Die Position zeigt auf den StartNode
// Der SwIndex zeigt hinterher auf den EndNode


/////////////////////////////////////////////////////////////////////////////

// Tabellen

// Zeilen und Boxen duerfen keine Rueckwaertsreferenz in andere
// Tabellen enthalten, also: Fixen!


// Das Attribut darf im Prinzip nicht > 65535 werden, da sonst MAs
// Rechenroutinen baden gehen. Da einige alte Tabellen groessere Werte
// enthalten, setzt InTable() ggf. einen Divisionsfaktor, um den
// die gelesenen Werte heruntergeteilt werden. Normalerweise ist er 1.


// Das uebergebene Array ist erst mal leer.
// Der Index zeigt auf den naechsten freien StartNode und wird
// auf den wiederum naechsten vorgeschoben.


// Einlesen einer Zeile


// rPos zeigt anschliessend hinter die Tabelle



// Registrieren einer Section. Der SwIndex zeigt auf den StartNode.



}
