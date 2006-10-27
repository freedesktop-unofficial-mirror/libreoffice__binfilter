/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_tblrwcl.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:28:16 $
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

#define _ZFORLIST_DECLARE_TABLE
#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER



#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _TBLRWCL_HXX
#include <tblrwcl.hxx>
#endif
namespace binfilter {

#define COLFUZZY 20
#define ROWFUZZY 10

typedef SwTableLine* SwTableLinePtr;

/*N*/ SV_IMPL_PTRARR( _SwShareBoxFmts, SwShareBoxFmt* )

// fuers setzen der Frame-Formate an den Boxen reicht es, das aktuelle
// im Array zu suchen. Ist es vorhanden, so gebe das neue zurueck




#if !defined( PRODUCT ) || defined( JP_DEBUG )




#else

#define CHECKBOXWIDTH
#define CHECKTABLELAYOUT

#endif








// ---------------------------------------------------------------





//-----------------------------------------------------------
























// ---------------------------------------------------------------



// ---------------------------------------------------------------

/*
    ----------------------- >> MERGE << ------------------------
     Algorythmus:
        ist in der _FndBox nur eine Line angegeben, nehme die Line
        und teste die Anzahl der Boxen
        - ist mehr als 1 Box angegeben, so wird auf Boxenebene zusammen-
            gefasst, d.H. die neue Box wird so Breit wie die alten.
            - Alle Lines die ueber/unter dem Bereich liegen werden in die
            Box als Line + Box mit Lines eingefuegt
            - Alle Lines die vor/hinter dem Bereich liegen werden in
            die Boxen Left/Right eingetragen

    ----------------------- >> MERGE << ------------------------
*/












// ---------------------------------------------------------------









// ---------------------------------------------------------------

// suche ab dieser Line nach der naechsten Box mit Inhalt

// suche ab dieser Line nach der vorherigen Box

// suche ab dieser Line nach der naechsten Box mit Inhalt

// suche ab dieser Line nach der naechsten Box mit Inhalt




/*  */

#pragma optimize( "", off )


//#pragma optimize( "", on )



/**/

//#pragma optimize( "", off )

//#pragma optimize( "", on )



// das Ergebnis des Positions Vergleiches
//  POS_BEFORE,             // Box liegt davor
//  POS_BEHIND,             // Box liegt dahinter
//  POS_INSIDE,             // Box liegt vollstaendig in Start/End
//  POS_OUTSIDE,            // Box ueberlappt Start/End vollstaendig
//  POS_EQUAL,              // Box und Start/End sind gleich
//  POS_OVERLAP_BEFORE,     // Box ueberlappt den Start
//  POS_OVERLAP_BEHIND      // Box ueberlappt das Ende






// Dummy Funktion fuer die Methode SetColWidth

/**/


#if !defined( PRODUCT ) || defined( JP_DEBUG )


#endif


#pragma optimize( "", on )

/*  */







/*  */





/*N*/ SwShareBoxFmts::~SwShareBoxFmts()
/*N*/ {
/*N*/ }









}
