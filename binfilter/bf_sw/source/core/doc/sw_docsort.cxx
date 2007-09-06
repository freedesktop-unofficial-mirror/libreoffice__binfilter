/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_docsort.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:00:30 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif




#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#if OSL_DEBUG_LEVEL > 1
//nur zum debugen
#endif
namespace binfilter {

using namespace ::com::sun::star::lang;




/*--------------------------------------------------------------------
    Beschreibung: Ein Sortierelement fuers Sort konstruieren
 --------------------------------------------------------------------*/









/*--------------------------------------------------------------------
    Beschreibung: Operatoren zum Vergleichen
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: Kleiner-Operator fuers sortieren
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: SortierElemente fuer Text
 --------------------------------------------------------------------*/






/*--------------------------------------------------------------------
    Beschreibung: Key ermitteln
 --------------------------------------------------------------------*/




/*--------------------------------------------------------------------
    Beschreibung: Sortier-Elemente fuer Tabellen
 --------------------------------------------------------------------*/




/*--------------------------------------------------------------------
    Beschreibung: Schluessel zu einer Zelle ermitteln
 --------------------------------------------------------------------*/




/*--------------------------------------------------------------------
    Beschreibung: Text sortieren im Document
 --------------------------------------------------------------------*/


/*N*/ BOOL SwDoc::SortText(const SwPaM& rPaM, const SwSortOptions& rOpt)
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // pruefen ob Rahmen im Text
/*N*/  return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Tabelle sortieren im Document
 --------------------------------------------------------------------*/

/*N*/ BOOL SwDoc::SortTbl(const SwSelBoxes& rBoxes, const SwSortOptions& rOpt)
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // uebers SwDoc fuer Undo !!
/*N*/   return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Zeilenweise verschieben
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: Spaltenweise verschieben
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: Eine einzelne Zelle verschieben
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: Zweidimensionales Array aus FndBoxes generieren
 --------------------------------------------------------------------*/





/*--------------------------------------------------------------------
    Beschreibung:   Alle Lines einer Box muessen gleichviel Boxen haben
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung:   Box auf Symmetrie pruefen
                    Alle Boxen einer Line muessen gleichviele Lines haben
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: max Anzahl der Spalten (Boxes)
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: max Anzahl der Zeilen (Lines)
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: lineares Array aus atomaren FndBoxes erzeugen
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung: Zugriff auf eine bestimmte Zelle
 --------------------------------------------------------------------*/





}
