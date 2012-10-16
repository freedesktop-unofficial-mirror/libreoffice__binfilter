/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif


#include <tools/debug.hxx>

#include "detdata.hxx"
#include "refupdat.hxx"
#include "rechead.hxx"
namespace binfilter {

//------------------------------------------------------------------------

/*N*/ SV_IMPL_PTRARR( ScDetOpArr_Impl, ScDetOpDataPtr );

//------------------------------------------------------------------------

/*N*/ ScDetOpList::ScDetOpList(const ScDetOpList& rList) :
/*N*/   ScDetOpArr_Impl(),
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

/*N*/ void ScDetOpList::Append( ScDetOpData* pInData )
/*N*/ {
/*N*/   if ( pInData->GetOperation() == SCDETOP_ADDERROR )
/*N*/       bHasAddError = TRUE;
/*N*/
/*N*/   Insert( pInData, Count() );
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


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
