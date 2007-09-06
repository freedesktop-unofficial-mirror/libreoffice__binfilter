/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_detdata.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:45:30 $
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

// INCLUDE ---------------------------------------------------------------

#include <tools/debug.hxx>

#include "detdata.hxx"
#include "refupdat.hxx"
#include "rechead.hxx"
namespace binfilter {

//------------------------------------------------------------------------

/*N*/ SV_IMPL_PTRARR( ScDetOpArr_Impl, ScDetOpDataPtr );

//------------------------------------------------------------------------

/*N*/ ScDetOpList::ScDetOpList(const ScDetOpList& rList) :
/*N*/   bHasAddError( FALSE )
/*N*/ {
/*N*/   USHORT nCount = rList.Count();
/*N*/
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       Append( new ScDetOpData(*rList[i]) );
/*N*/ }

/*N*/ void ScDetOpList::UpdateReference( ScDocument* pDoc, UpdateRefMode eUpdateRefMode,
/*N*/                               const ScRange& rRange, short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   USHORT nCount = Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*N*/       ScAddress aPos = (*this)[i]->GetPos();
/*N*/       USHORT nCol1 = aPos.Col();
/*N*/       USHORT nRow1 = aPos.Row();
/*N*/       USHORT nTab1 = aPos.Tab();
/*N*/       USHORT nCol2 = nCol1;
/*N*/       USHORT nRow2 = nRow1;
/*N*/       USHORT nTab2 = nTab1;
/*N*/
/*N*/       ScRefUpdateRes eRes =
/*N*/           ScRefUpdate::Update( pDoc, eUpdateRefMode,
/*N*/               rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
/*N*/               rRange.aEnd.Col(), rRange.aEnd.Row(), rRange.aEnd.Tab(), nDx, nDy, nDz,
/*N*/               nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
/*N*/       if ( eRes != UR_NOTHING )
/*N*/           (*this)[i]->SetPos( ScAddress( nCol1, nRow1, nTab1 ) );
/*N*/   }
/*N*/ }

/*N*/ void ScDetOpList::Append( ScDetOpData* pData )
/*N*/ {
/*N*/   if ( pData->GetOperation() == SCDETOP_ADDERROR )
/*N*/       bHasAddError = TRUE;
/*N*/
/*N*/   Insert( pData, Count() );
/*N*/ }



/*N*/ void ScDetOpList::Load( SvStream& rStream )
/*N*/ {
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nNewCount;
/*N*/   rStream >> nNewCount;
/*N*/
/*N*/   ScAddress aPos;
/*N*/   USHORT nOper;
/*N*/
/*N*/   for (USHORT i=0; i<nNewCount; i++)
/*N*/   {
/*N*/       //  1) Position (ScAddress)
/*N*/       //  2) Operation (USHORT)
/*N*/
/*N*/       aHdr.StartEntry();
/*N*/
/*N*/       rStream >> aPos;
/*N*/       rStream >> nOper;
/*N*/       Append( new ScDetOpData( aPos, (ScDetOpType) nOper ) );
/*N*/
/*N*/       aHdr.EndEntry();
/*N*/   }
/*N*/ }

/*N*/ void ScDetOpList::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nCount = Count();
/*N*/   rStream << nCount;
/*N*/
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*N*/       //  1) Position (ScAddress)
/*N*/       //  2) Operation (USHORT)
/*N*/
/*N*/       aHdr.StartEntry();
/*N*/
/*N*/       ScDetOpData* pData = (*this)[i];
/*N*/       rStream << pData->GetPos();
/*N*/       rStream << (USHORT) pData->GetOperation();
/*N*/
/*N*/       aHdr.EndEntry();
/*N*/   }
/*N*/ }



}
