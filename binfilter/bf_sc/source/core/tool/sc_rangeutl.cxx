/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_rangeutl.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 17:15:52 $
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
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <tools/debug.hxx>

#include "rangeutl.hxx"
#include "document.hxx"
// auto strip #include "global.hxx"
#include "dbcolect.hxx"
#include "rangenam.hxx"
// auto strip #include "scresid.hxx"
#include "globstr.hrc"
namespace binfilter {


//------------------------------------------------------------------------

//STRIP001 BOOL ScRangeUtil::MakeArea( const String&    rAreaStr,
//STRIP001                          ScArea&         rArea,
//STRIP001                          ScDocument*     pDoc,
//STRIP001                          USHORT          nTab ) const
//STRIP001 {
//STRIP001  // Eingabe in rAreaStr: "$Tabelle1.$A1:$D17"
//STRIP001
//STRIP001  BOOL        nSuccess    = FALSE;
//STRIP001  USHORT      nPointPos   = rAreaStr.Search('.');
//STRIP001  USHORT      nColonPos   = rAreaStr.Search(':');
//STRIP001  String      aStrArea( rAreaStr );
//STRIP001  ScRefTripel startPos;
//STRIP001  ScRefTripel endPos;
//STRIP001
//STRIP001  if ( nColonPos == STRING_NOTFOUND )
//STRIP001      if ( nPointPos != STRING_NOTFOUND )
//STRIP001      {
//STRIP001          aStrArea += ':';
//STRIP001          aStrArea += rAreaStr.Copy( nPointPos+1 ); // '.' nicht mitkopieren
//STRIP001      }
//STRIP001
//STRIP001  nSuccess = ConvertDoubleRef( pDoc, aStrArea, nTab, startPos, endPos );
//STRIP001
//STRIP001  if ( nSuccess )
//STRIP001      rArea = ScArea( startPos.GetTab(),
//STRIP001                      startPos.GetCol(),  startPos.GetRow(),
//STRIP001                      endPos.GetCol(),    endPos.GetRow() );
//STRIP001
//STRIP001  return nSuccess;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScRangeUtil::CutPosString( const String&    theAreaStr,
//STRIP001                              String&         thePosStr ) const
//STRIP001 {
//STRIP001  String  aPosStr;
//STRIP001  USHORT  nColonPos = theAreaStr.Search(':');
//STRIP001
//STRIP001  if ( nColonPos != STRING_NOTFOUND )
//STRIP001      aPosStr = theAreaStr.Copy( 0, nColonPos ); // ':' nicht mitkopieren
//STRIP001  else
//STRIP001      aPosStr = theAreaStr;
//STRIP001
//STRIP001  thePosStr = aPosStr;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScRangeUtil::IsAbsTabArea( const String&    rAreaStr,
//STRIP001                              ScDocument*     pDoc,
//STRIP001                              ScArea***       pppAreas,
//STRIP001                              USHORT*         pAreaCount,
//STRIP001                              BOOL            bAcceptCellRef ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "Kein Dokument uebergeben!" );
//STRIP001  if ( !pDoc )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  /*
//STRIP001   * Erwartet wird ein String der Form
//STRIP001   *      "$Tabelle1.$A$1:$Tabelle3.$D$17"
//STRIP001   * Wenn bAcceptCellRef == TRUE ist, wird auch ein String der Form
//STRIP001   *      "$Tabelle1.$A$1"
//STRIP001   * akzeptiert.
//STRIP001   *
//STRIP001   * als Ergebnis wird ein ScArea-Array angelegt,
//STRIP001   * welches ueber ppAreas bekannt gegeben wird und auch
//STRIP001   * wieder geloescht werden muss!
//STRIP001   */
//STRIP001
//STRIP001  BOOL    bStrOk = FALSE;
//STRIP001  String  aTempAreaStr(rAreaStr);
//STRIP001  String  aStartPosStr;
//STRIP001  String  aEndPosStr;
//STRIP001
//STRIP001  if ( STRING_NOTFOUND == aTempAreaStr.Search(':') )
//STRIP001  {
//STRIP001      aTempAreaStr.Append(':');
//STRIP001      aTempAreaStr.Append(rAreaStr);
//STRIP001  }
//STRIP001
//STRIP001  USHORT   nColonPos = aTempAreaStr.Search(':');
//STRIP001
//STRIP001  if (   STRING_NOTFOUND != nColonPos
//STRIP001      && STRING_NOTFOUND != aTempAreaStr.Search('.') )
//STRIP001  {
//STRIP001      ScRefTripel aStartPos;
//STRIP001      ScRefTripel aEndPos;
//STRIP001
//STRIP001      aStartPosStr = aTempAreaStr.Copy( 0,           nColonPos  );
//STRIP001      aEndPosStr   = aTempAreaStr.Copy( nColonPos+1, STRING_LEN );
//STRIP001
//STRIP001      if ( ConvertSingleRef( pDoc, aStartPosStr, 0, aStartPos ) )
//STRIP001      {
//STRIP001          if ( ConvertSingleRef( pDoc, aEndPosStr, aStartPos.GetTab(), aEndPos ) )
//STRIP001          {
//STRIP001              aStartPos.SetRelCol( FALSE );
//STRIP001              aStartPos.SetRelRow( FALSE );
//STRIP001              aStartPos.SetRelTab( FALSE );
//STRIP001              aEndPos.SetRelCol( FALSE );
//STRIP001              aEndPos.SetRelRow( FALSE );
//STRIP001              aEndPos.SetRelTab( FALSE );
//STRIP001
//STRIP001              bStrOk = TRUE;
//STRIP001
//STRIP001              if ( pppAreas && pAreaCount ) // Array zurueckgegeben?
//STRIP001              {
//STRIP001                  USHORT      nStartTab   = aStartPos.GetTab();
//STRIP001                  USHORT      nEndTab     = aEndPos.GetTab();
//STRIP001                  USHORT      nTabCount   = nEndTab-nStartTab+1;
//STRIP001                  ScArea**    theAreas    = new ScArea*[nTabCount];
//STRIP001                  USHORT      nTab        = 0;
//STRIP001                  USHORT      i           = 0;
//STRIP001                  ScArea      theArea( 0, aStartPos.GetCol(), aStartPos.GetRow(),
//STRIP001                                          aEndPos.GetCol(), aEndPos.GetRow() );
//STRIP001
//STRIP001                  nTab = nStartTab;
//STRIP001                  for ( i=0; i<nTabCount; i++ )
//STRIP001                  {
//STRIP001                      theAreas[i] = new ScArea( theArea );
//STRIP001                      theAreas[i]->nTab = nTab;
//STRIP001                      nTab++;
//STRIP001                  }
//STRIP001                  *pppAreas   = theAreas;
//STRIP001                  *pAreaCount = nTabCount;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bStrOk;
//STRIP001 }

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

//STRIP001 BOOL ScRangeUtil::IsAbsPos( const String&    rPosStr,
//STRIP001                          ScDocument*     pDoc,
//STRIP001                          USHORT          nTab,
//STRIP001                          String*         pCompleteStr,
//STRIP001                          ScRefTripel*    pPosTripel ) const
//STRIP001 {
//STRIP001  BOOL        bIsAbsPos = FALSE;
//STRIP001  ScRefTripel thePos;
//STRIP001
//STRIP001  bIsAbsPos = ConvertSingleRef( pDoc, rPosStr, nTab, thePos );
//STRIP001
//STRIP001  thePos.SetRelCol( FALSE );
//STRIP001  thePos.SetRelRow( FALSE );
//STRIP001  thePos.SetRelTab( FALSE );
//STRIP001
//STRIP001  if ( bIsAbsPos )
//STRIP001  {
//STRIP001      if ( pPosTripel )
//STRIP001          *pPosTripel = thePos;
//STRIP001      if ( pCompleteStr )
//STRIP001          *pCompleteStr = thePos.GetRefString( pDoc, MAXTAB+1 );
//STRIP001  }
//STRIP001
//STRIP001  return bIsAbsPos;
//STRIP001 }

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
/*N*/   USHORT          nTab, nColStart, nColEnd, nRowStart, nRowEnd;
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
/*N*/           else
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 CutPosString( aStrArea, aStrArea );
//STRIP001 /*?*/
//STRIP001 /*?*/                if ( IsAbsPos( aStrArea, pDoc, nCurTab,
//STRIP001 /*?*/                                          NULL, &aStartPos ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    nTab       = aStartPos.GetTab();
//STRIP001 /*?*/                    nColStart  = nColEnd = aStartPos.GetCol();
//STRIP001 /*?*/                    nRowStart  = nRowEnd = aStartPos.GetRow();
//STRIP001 /*?*/                    bResult    = TRUE;
//STRIP001 /*?*/                }
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
/*N*/       DBG_ERROR( "ScRangeUtil::MakeRangeFromName" );
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

//STRIP001 void ScArea::Clear()
//STRIP001 {
//STRIP001  nTab =
//STRIP001  nColStart = nRowStart =
//STRIP001  nColEnd   = nRowEnd   = 0;
//STRIP001 }

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

//STRIP001 BOOL ScArea::operator==( const ScArea& r ) const
//STRIP001 {
//STRIP001  return (   (nTab        == r.nTab)
//STRIP001          && (nColStart   == r.nColStart)
//STRIP001          && (nRowStart   == r.nRowStart)
//STRIP001          && (nColEnd     == r.nColEnd)
//STRIP001          && (nRowEnd     == r.nRowEnd) );
//STRIP001 }

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

//STRIP001 void ScArea::GetString( String& rStr, BOOL bAbsolute, ScDocument* pDoc ) const
//STRIP001 {
//STRIP001  ScRange aRange( ScAddress( nColStart, nRowStart, nTab ),
//STRIP001                  ScAddress( nColEnd,   nRowEnd,   nTab ) );
//STRIP001  USHORT  nFlags = bAbsolute ? SCA_COL_ABSOLUTE | SCA_ROW_ABSOLUTE : 0;
//STRIP001
//STRIP001  aRange.Format( rStr, nFlags, pDoc );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScAreaNameIterator::ScAreaNameIterator( ScDocument* pDoc ) :
//STRIP001  aStrNoName( ScGlobal::GetRscString(STR_DB_NONAME) )
//STRIP001 {
//STRIP001  pRangeName = pDoc->GetRangeName();
//STRIP001  pDBCollection = pDoc->GetDBCollection();
//STRIP001  nPos = 0;
//STRIP001  bFirstPass = TRUE;
//STRIP001 }

//STRIP001 BOOL ScAreaNameIterator::Next( String& rName, ScRange& rRange )
//STRIP001 {
//STRIP001  for (;;)
//STRIP001  {
//STRIP001      if ( bFirstPass )                                   // erst Bereichsnamen
//STRIP001      {
//STRIP001          if ( pRangeName && nPos < pRangeName->GetCount() )
//STRIP001          {
//STRIP001              ScRangeData* pData = (*pRangeName)[nPos++];
//STRIP001              if ( pData && pData->IsReference(rRange) )
//STRIP001              {
//STRIP001                  rName = pData->GetName();
//STRIP001                  return TRUE;                            // gefunden
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              bFirstPass = FALSE;
//STRIP001              nPos = 0;
//STRIP001          }
//STRIP001      }
//STRIP001      if ( !bFirstPass )                                  // dann DB-Bereiche
//STRIP001      {
//STRIP001          if ( pDBCollection && nPos < pDBCollection->GetCount() )
//STRIP001          {
//STRIP001              ScDBData* pData = (*pDBCollection)[nPos++];
//STRIP001              if (pData && pData->GetName() != aStrNoName)
//STRIP001              {
//STRIP001                  pData->GetArea( rRange );
//STRIP001                  rName = pData->GetName();
//STRIP001                  return TRUE;                            // gefunden
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              return FALSE;                               // gibt nichts mehr
//STRIP001      }
//STRIP001  }
//STRIP001 }




}
