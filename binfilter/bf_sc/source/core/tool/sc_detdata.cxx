/*************************************************************************
 *
 *  $RCSfile: sc_detdata.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:29 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

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

//STRIP001 void ScDetOpList::UpdateReference( ScDocument* pDoc, UpdateRefMode eUpdateRefMode,
//STRIP001                              const ScRange& rRange, short nDx, short nDy, short nDz )
//STRIP001 {
//STRIP001  USHORT nCount = Count();
//STRIP001  for (USHORT i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      ScAddress aPos = (*this)[i]->GetPos();
//STRIP001      USHORT nCol1 = aPos.Col();
//STRIP001      USHORT nRow1 = aPos.Row();
//STRIP001      USHORT nTab1 = aPos.Tab();
//STRIP001      USHORT nCol2 = nCol1;
//STRIP001      USHORT nRow2 = nRow1;
//STRIP001      USHORT nTab2 = nTab1;
//STRIP001
//STRIP001      ScRefUpdateRes eRes =
//STRIP001          ScRefUpdate::Update( pDoc, eUpdateRefMode,
//STRIP001              rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
//STRIP001              rRange.aEnd.Col(), rRange.aEnd.Row(), rRange.aEnd.Tab(), nDx, nDy, nDz,
//STRIP001              nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001      if ( eRes != UR_NOTHING )
//STRIP001          (*this)[i]->SetPos( ScAddress( nCol1, nRow1, nTab1 ) );
//STRIP001  }
//STRIP001 }

/*N*/ void ScDetOpList::Append( ScDetOpData* pData )
/*N*/ {
/*N*/   if ( pData->GetOperation() == SCDETOP_ADDERROR )
/*N*/       bHasAddError = TRUE;
/*N*/
/*N*/   Insert( pData, Count() );
/*N*/ }


//STRIP001 BOOL ScDetOpList::operator==( const ScDetOpList& r ) const
//STRIP001 {
//STRIP001  // fuer Ref-Undo
//STRIP001
//STRIP001  USHORT nCount = Count();
//STRIP001  BOOL bEqual = ( nCount == r.Count() );
//STRIP001  for (USHORT i=0; i<nCount && bEqual; i++)       // Reihenfolge muss auch gleich sein
//STRIP001      if ( !(*(*this)[i] == *r[i]) )              // Eintraege unterschiedlich ?
//STRIP001          bEqual = FALSE;
//STRIP001
//STRIP001  return bEqual;
//STRIP001 }

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
