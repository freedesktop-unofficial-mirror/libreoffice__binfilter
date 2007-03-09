/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_optgrid.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 16:23:32 $
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

#define _SVX_OPTGRID_CXX

#include "svxids.hrc"
#include "optgrid.hxx"
#include "dialogs.hrc"
namespace binfilter {

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

}
