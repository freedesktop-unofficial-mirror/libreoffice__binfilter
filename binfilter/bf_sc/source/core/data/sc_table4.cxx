/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_table4.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:40:42 $
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

// System - Includes -----------------------------------------------------

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifdef _MSC_VER
#pragma optimize("",off)
#endif
                                        // sonst Absturz Win beim Fuellen

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <math.h>

#include "globstr.hrc"
#include "document.hxx"
#include "autoform.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

#define _D_MAX_LONG_  (double) 0x7fffffff

extern USHORT nScFillModeMouseModifier;     // global.cxx

// -----------------------------------------------------------------------














#define LF_LEFT         1
#define LF_TOP          2
#define LF_RIGHT        4
#define LF_BOTTOM       8
#define LF_ALL          (LF_LEFT | LF_TOP | LF_RIGHT | LF_BOTTOM)



/*N*/ void ScTable::SetError( USHORT nCol, USHORT nRow, USHORT nError)
/*N*/ {
/*N*/   if (ValidColRow(nCol, nRow))
/*N*/       aCol[nCol].SetError( nRow, nError );
/*N*/ }





/*N*/ BOOL ScTable::TestTabRefAbs(USHORT nTable)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   for (USHORT i=0; i <= MAXCOL; i++)
/*N*/       if (aCol[i].TestTabRefAbs(nTable))
/*N*/           bRet = TRUE;
/*N*/   return bRet;
/*N*/ }


/*N*/ void ScTable::CompileDBFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileDBFormula( bCreateFormulaString );
/*N*/ }

/*N*/ void ScTable::CompileNameFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileNameFormula( bCreateFormulaString );
/*N*/ }

/*N*/ void ScTable::CompileColRowNameFormula()
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileColRowNameFormula();
/*N*/ }






}
