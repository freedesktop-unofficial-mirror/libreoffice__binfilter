/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_optgrid.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:27:37 $
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

// include ---------------------------------------------------------------

#pragma hdrstop

#define _SVX_OPTGRID_CXX

#include "svxids.hrc"
#include "optgrid.hxx"
#include "dialogs.hrc"
#include "optgrid.hrc"
namespace binfilter {

/* -----------------18.08.98 17:41-------------------
 * local functions
 * --------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung: Rastereinstellungen Ctor
 --------------------------------------------------------------------*/

/*N*/ SvxOptionsGrid::SvxOptionsGrid() :
/*N*/   nFldDrawX       ( 100 ),
/*N*/   nFldDivisionX   ( 0 ),
/*N*/   nFldDrawY       ( 100 ),
/*N*/   nFldDivisionY   ( 0 ),
/*N*/   nFldSnapX       ( 100 ),
/*N*/   nFldSnapY       ( 100 ),
/*N*/   bUseGridsnap    ( 0 ),
/*N*/   bSynchronize    ( 1 ),
/*N*/   bGridVisible    ( 0 ),
/*N*/   bEqualGrid      ( 1 )
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Rastereinstellungen Dtor
 --------------------------------------------------------------------*/

/*N*/ SvxOptionsGrid::~SvxOptionsGrid()
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Item fuer Rastereinstellungen
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/



/*----------------- OS 23.02.95  -----------------------
 TabPage Rastereinstellungen
-------------------------------------------------------*/


//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------


//------------------------------------------------------------------------

//------------------------------------------------------------------------



}
