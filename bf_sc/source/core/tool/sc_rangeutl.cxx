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

#include "rangeutl.hxx"
#include "document.hxx"
#include "dbcolect.hxx"
#include "rangenam.hxx"
#include "globstr.hrc"
namespace binfilter {


//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------

/*N*/  BOOL ScRangeUtil::IsAbsArea( const String&   rAreaStr,
/*N*/                            ScDocument*    pDoc,
/*N*/                            USHORT         nTab,
/*N*/                            String*        pCompleteStr,
/*N*/                            ScRefTripel*   pStartPos,
/*N*/                            ScRefTripel*   pEndPos ) const
/*N*/  {
/*N*/   BOOL        bIsAbsArea = FALSE;
/*N*/   ScRefTripel startPos;
/*N*/   ScRefTripel endPos;
/*N*/
/*N*/   bIsAbsArea = ConvertDoubleRef( pDoc, rAreaStr, nTab, startPos, endPos );
/*N*/
/*N*/   if ( bIsAbsArea )
/*N*/   {
/*N*/       startPos.SetRelCol( FALSE );
/*N*/       startPos.SetRelRow( FALSE );
/*N*/       startPos.SetRelTab( FALSE );
/*N*/       endPos  .SetRelCol( FALSE );
/*N*/       endPos  .SetRelRow( FALSE );
/*N*/       endPos  .SetRelTab( FALSE );
/*N*/
/*N*/       if ( pCompleteStr )
/*N*/       {
/*N*/           *pCompleteStr  = startPos.GetRefString( pDoc, MAXTAB+1 );
/*N*/           *pCompleteStr += ':';
/*N*/           *pCompleteStr += endPos  .GetRefString( pDoc, nTab );
/*N*/       }
/*N*/
/*N*/       if ( pStartPos && pEndPos )
/*N*/       {
/*N*/           *pStartPos = startPos;
/*N*/           *pEndPos   = endPos;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bIsAbsArea;
/*N*/  }

//------------------------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ BOOL ScRangeUtil::MakeRangeFromName   (
/*N*/   const String&   rName,
/*N*/   ScDocument*     pDoc,
/*N*/   USHORT          nCurTab,
/*N*/   ScRange&        rRange,
/*N*/   RutlNameScope   eScope
/*N*/                                 ) const
/*N*/ {
/*N*/   BOOL bResult=FALSE;
/*N*/   ScRangeUtil     aRangeUtil;
/*N*/   USHORT          nTab(0), nColStart(0), nColEnd(0), nRowStart(0), nRowEnd(0);
/*N*/
/*N*/   if( eScope==RUTL_NAMES )
/*N*/   {
/*N*/       ScRangeName& rRangeNames = *(pDoc->GetRangeName());
/*N*/       USHORT       nAt         = 0;
/*N*/
/*N*/       if ( rRangeNames.SearchName( rName, nAt ) )
/*N*/       {
/*N*/           ScRangeData* pData = rRangeNames[nAt];
/*N*/           String       aStrArea;
/*N*/           ScRefTripel  aStartPos;
/*N*/           ScRefTripel  aEndPos;
/*N*/
/*N*/           pData->GetSymbol( aStrArea );
/*N*/
/*N*/           if ( IsAbsArea( aStrArea, pDoc, nCurTab,
/*N*/                                      NULL, &aStartPos, &aEndPos ) )
/*N*/           {
/*N*/               nTab       = aStartPos.GetTab();
/*N*/               nColStart  = aStartPos.GetCol();
/*N*/               nRowStart  = aStartPos.GetRow();
/*N*/               nColEnd    = aEndPos.GetCol();
/*N*/               nRowEnd    = aEndPos.GetRow();
/*N*/               bResult    = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else if( eScope==RUTL_DBASE )
/*N*/   {
/*N*/       ScDBCollection& rDbNames = *(pDoc->GetDBCollection());
/*N*/       USHORT          nAt = 0;
/*N*/
/*N*/       if ( rDbNames.SearchName( rName, nAt ) )
/*N*/       {
/*N*/           ScDBData* pData = rDbNames[nAt];
/*N*/
/*N*/           pData->GetArea( nTab, nColStart, nRowStart,
/*N*/                                 nColEnd,   nRowEnd );
/*N*/           bResult = TRUE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       OSL_FAIL( "ScRangeUtil::MakeRangeFromName" );
/*N*/   }
/*N*/
/*N*/   if( bResult )
/*N*/   {
/*N*/       rRange = ScRange( nColStart, nRowStart, nTab, nColEnd, nRowEnd, nTab );
/*N*/   }
/*N*/
/*N*/   return bResult;
/*N*/ }

//========================================================================

/*N*/ ScArea::ScArea( USHORT tab,
/*N*/               USHORT colStart, USHORT rowStart,
/*N*/               USHORT colEnd,   USHORT rowEnd ) :
/*N*/       nTab     ( tab ),
/*N*/       nColStart( colStart ),  nRowStart( rowStart ),
/*N*/       nColEnd  ( colEnd ),    nRowEnd  ( rowEnd )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScArea::ScArea( const ScArea& r ) :
/*N*/       nTab     ( r.nTab ),
/*N*/       nColStart( r.nColStart ),   nRowStart( r.nRowStart ),
/*N*/       nColEnd  ( r.nColEnd ),     nRowEnd  ( r.nRowEnd )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScArea& ScArea::operator=( const ScArea& r )
/*N*/ {
/*N*/   nTab        = r.nTab;
/*N*/   nColStart   = r.nColStart;
/*N*/   nRowStart   = r.nRowStart;
/*N*/   nColEnd     = r.nColEnd;
/*N*/   nRowEnd     = r.nRowEnd;
/*N*/   return *this;
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ SvStream& operator>> ( SvStream& rStream, ScArea& rArea )
/*N*/ {
/*N*/   rStream >> rArea.nTab;
/*N*/   rStream >> rArea.nColStart;
/*N*/   rStream >> rArea.nRowStart;
/*N*/   rStream >> rArea.nColEnd;
/*N*/   rStream >> rArea.nRowEnd;
/*N*/   return rStream;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvStream& operator<< ( SvStream& rStream, const ScArea& rArea )
/*N*/ {
/*N*/   rStream << rArea.nTab;
/*N*/   rStream << rArea.nColStart;
/*N*/   rStream << rArea.nRowStart;
/*N*/   rStream << rArea.nColEnd;
/*N*/   rStream << rArea.nRowEnd;
/*N*/   return rStream;
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------






}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
