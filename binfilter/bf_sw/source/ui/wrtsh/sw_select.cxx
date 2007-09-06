/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_select.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:14:54 $
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

#include <limits.h>




#ifndef _CMDID_H
#include <cmdid.h>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif

#if OSL_DEBUG_LEVEL > 1
#endif
namespace binfilter {

namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }

using namespace ::com::sun::star::util;


static long nStartDragX = 0, nStartDragY = 0;
static BOOL  bStartDrag = FALSE;





/*
BOOL SwWrtShell::SelSentence(const Point *pPt, BOOL )
{
    {
        MV_KONTEXT(this);
        ClearMark();
        if(!_BwdSentence()) {
            return FALSE;
        }
        SttSelect();
        if(!_FwdSentence()) {
            EndSelect();
            return FALSE;
        }
    }
    EndSelect();
    return TRUE;
}

*/







/*------------------------------------------------------------------------
 Beschreibung:  Textsuche
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
 Beschreibung:  Suche nach Vorlagen
------------------------------------------------------------------------*/




// Suche nach Attributen ----------------------------------------------------




// ---------- Selektionsmodi ----------







/*
 * Zwei Methoden fuer das Cursorsetzen; die erste mappt auf die
 * gleichnamige Methoden an der CursorShell, die zweite hebt
 * zuerst alle Selektionen auf.
 */



/*N*/ long SwWrtShell::SetCrsr(const Point *pPt, BOOL bTextOnly)
/*N*/ {
        /*
        * eine gfs.  bestehende Selektion an der Position des
        * Mausklicks aufheben
        */
/*?*/           DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001   if(!IsInSelect() && ChgCurrPam(*pPt)) {
/*N*/ }



/*
 * Aufheben aller Selektionen
 */






/*
 * tue nichts
 */
/*N*/ long SwWrtShell::Ignore(const Point *, BOOL ) {
/*N*/   return 1;
/*N*/ }


/*
 * Ende einer Selektion; falls die Selektion leer ist,
 * ClearMark().
 */



/*N*/ long SwWrtShell::SttLeaveSelect(const Point *, BOOL )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if(SwCrsrShell::HasSelection() && !IsSelTblCells() && bClearMark) {
/*N*/   return 1;
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Rahmengebundenes Macro ausfuehren
------------------------------------------------------------------------*/

/*N*/ IMPL_LINK( SwWrtShell, ExecFlyMac, void *, pFlyFmt )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   const SwFrmFmt *pFmt = pFlyFmt ? (SwFrmFmt*)pFlyFmt : GetFlyFrmFmt();
/*N*/   return 0;
/*N*/ }




/*
 * Handler fuer das Togglen der Modi. Liefern alten Mode zurueck.
 */






/*
 * Draggen im Standard Modus (Selektieren von Inhalt)
 */



/*N*/ long SwWrtShell::BeginDrag(const Point *pPt, BOOL )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001   if(bSelWrd)
/*N*/ }






/*N*/ long SwWrtShell::EndDrag(const Point *pPt, BOOL )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001   fnDrag = &SwWrtShell::BeginDrag;
/*N*/ }
/*------------------------------------------------------------------------
 Beschreibung:  Selektion einer Tabellenzeile / Spalte
------------------------------------------------------------------------*/







/*------------------------------------------------------------------------
 Beschreibung:    Prueft, ob eine Wortselektion vorliegt.
                  Gemaess den Regeln fuer intelligentes Cut / Paste
                  werden umgebende Spaces rausgeschnitten.
 Return:          Liefert Art der Wortselektion zurueck.
------------------------------------------------------------------------*/






    // jump to the next / previous hyperlink - inside text and also
    // on graphics


/* fuer den Erhalt der Selektion wird nach SetMark() der Cursor
 * nach links bewegt, damit er durch das Einfuegen von Text nicht
 * verschoben wird.  Da auf der CORE-Seite am aktuellen Cursor
 * eine bestehende Selektion aufgehoben wird, wird der Cursor auf
 * den Stack gepushed. Nach dem Verschieben werden sie wieder
 * zusammengefasst. */



#if 0
#endif

}
