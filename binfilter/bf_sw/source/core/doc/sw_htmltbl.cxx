/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_htmltbl.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:01:58 $
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


//#define TEST_DELAYED_RESIZE

#ifdef TEST_DELAYED_RESIZE
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif


#include "htmltbl.hxx"
namespace binfilter {

#define COLFUZZY 20
#define MAX_TABWIDTH (USHRT_MAX - 2001)


/*  */


/*  */





/*  */



/*  */



/*  */




/*  */


/*N*/ SwHTMLTableLayout::SwHTMLTableLayout(
/*N*/                       const SwTable * pSwTbl,
/*N*/                       USHORT nRws, USHORT nCls, BOOL bColsOpt, BOOL bColTgs,
/*N*/                       USHORT nWdth, BOOL bPrcWdth, USHORT nBorderOpt,
/*N*/                       USHORT nCellPad, USHORT nCellSp, SvxAdjust eAdjust,
/*N*/                       USHORT nLMargin, USHORT nRMargin,
/*N*/                       USHORT nBWidth, USHORT nLeftBWidth,
/*N*/                       USHORT nRightBWidth,
/*N*/                       USHORT nInhLeftBWidth, USHORT nInhRightBWidth ) //STRIP001 :
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ SwHTMLTableLayout::~SwHTMLTableLayout()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

#ifdef USED

#endif

// Die Breiten der Umrandung werden zunaechst wie in Netscape berechnet:
// Aussere Umrandung: BORDER + CELLSPACING + CELLPADDING
// Innere Umrandung: CELLSPACING + CELLPADDING
// Allerdings wird die Breite der Umrandung im SW trotzdem beachtet, wenn
// bSwBorders gesetzt ist, damit nicht faellschlich umgebrochen wird.
// MIB 27.6.97: Dabei muss auch der Abstand zum Inhalt berueckichtigt werden,
// und zwar auch dann, wenn wenn nur die gegenueberliegende Seite
// eine Umrandung hat.













// nAbsAvail ist der verfuegbare Platz in TWIPS.
// nRelAvail ist der auf USHRT_MAX bezogene verfuegbare Platz oder 0
// nAbsSpace ist der Anteil von nAbsAvail, der durch der umgebende Zelle
//           fur die Umrandung und den Abstand zum Inhalt reserviert ist.











}
