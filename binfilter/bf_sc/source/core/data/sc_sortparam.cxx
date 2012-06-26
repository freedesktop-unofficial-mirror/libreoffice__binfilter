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
/*N*/       bHasHeader(r.bHasHeader),bByRow(r.bByRow),bCaseSens(r.bCaseSens),
/*N*/       bUserDef(r.bUserDef),nUserIndex(r.nUserIndex),bIncludePattern(r.bIncludePattern),
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
