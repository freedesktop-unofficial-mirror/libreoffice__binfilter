/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_sortparam.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:39:04 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "sortparam.hxx"

namespace binfilter {


//------------------------------------------------------------------------

/*N*/ ScSortParam::ScSortParam()
/*N*/ {
/*N*/   Clear();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSortParam::ScSortParam( const ScSortParam& r ) :
/*N*/       nCol1(r.nCol1),nRow1(r.nRow1),nCol2(r.nCol2),nRow2(r.nRow2),
/*N*/       bHasHeader(r.bHasHeader),bCaseSens(r.bCaseSens),
/*N*/       bByRow(r.bByRow),bUserDef(r.bUserDef),nUserIndex(r.nUserIndex),bIncludePattern(r.bIncludePattern),
/*N*/       bInplace(r.bInplace),
/*N*/       nDestTab(r.nDestTab),nDestCol(r.nDestCol),nDestRow(r.nDestRow),
/*N*/       aCollatorLocale( r.aCollatorLocale ), aCollatorAlgorithm( r.aCollatorAlgorithm )
/*N*/ {
/*N*/   for (USHORT i=0; i<MAXSORT; i++)
/*N*/   {
/*N*/       bDoSort[i]    = r.bDoSort[i];
/*N*/       nField[i]     = r.nField[i];
/*N*/       bAscending[i] = r.bAscending[i];
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScSortParam::Clear()
/*N*/ {
/*N*/   nCol1=nRow1=nCol2=nRow2=nDestTab=nDestCol=nDestRow=nUserIndex = 0;
/*N*/   bHasHeader=bCaseSens=bUserDef = FALSE;
/*N*/   bByRow=bIncludePattern=bInplace = TRUE;
/*N*/   aCollatorLocale = ::com::sun::star::lang::Locale();
/*N*/   aCollatorAlgorithm.Erase();
/*N*/
/*N*/   for (USHORT i=0; i<MAXSORT; i++)
/*N*/   {
/*N*/       bDoSort[i]    = FALSE;
/*N*/       nField[i]     = 0;
/*N*/       bAscending[i] = TRUE;
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------


}
