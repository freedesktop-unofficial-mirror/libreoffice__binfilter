/*************************************************************************
 *
 *  $RCSfile: sc_sortparam.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:08 $
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

#include "sortparam.hxx"
#include "global.hxx"

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
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

//STRIP001 ScSortParam& ScSortParam::operator=( const ScSortParam& r )
//STRIP001 {
//STRIP001  nCol1           = r.nCol1;
//STRIP001  nRow1           = r.nRow1;
//STRIP001  nCol2           = r.nCol2;
//STRIP001  nRow2           = r.nRow2;
//STRIP001  bHasHeader      = r.bHasHeader;
//STRIP001  bCaseSens       = r.bCaseSens;
//STRIP001  bByRow          = r.bByRow;
//STRIP001  bUserDef        = r.bUserDef;
//STRIP001  nUserIndex      = r.nUserIndex;
//STRIP001  bIncludePattern = r.bIncludePattern;
//STRIP001  bInplace        = r.bInplace;
//STRIP001  nDestTab        = r.nDestTab;
//STRIP001  nDestCol        = r.nDestCol;
//STRIP001  nDestRow        = r.nDestRow;
//STRIP001  aCollatorLocale         = r.aCollatorLocale;
//STRIP001  aCollatorAlgorithm      = r.aCollatorAlgorithm;
//STRIP001
//STRIP001  for (USHORT i=0; i<MAXSORT; i++)
//STRIP001  {
//STRIP001      bDoSort[i]    = r.bDoSort[i];
//STRIP001      nField[i]     = r.nField[i];
//STRIP001      bAscending[i] = r.bAscending[i];
//STRIP001  }
//STRIP001
//STRIP001  return *this;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScSortParam::operator==( const ScSortParam& rOther ) const
//STRIP001 {
//STRIP001  BOOL bEqual = FALSE;
//STRIP001  // Anzahl der Sorts gleich?
//STRIP001  USHORT nLast      = 0;
//STRIP001  USHORT nOtherLast = 0;
//STRIP001  while ( bDoSort[nLast++] && nLast < MAXSORT );
//STRIP001  while ( rOther.bDoSort[nOtherLast++] && nOtherLast < MAXSORT );
//STRIP001  nLast--;
//STRIP001  nOtherLast--;
//STRIP001  if (   (nLast           == nOtherLast)
//STRIP001      && (nCol1           == rOther.nCol1)
//STRIP001      && (nRow1           == rOther.nRow1)
//STRIP001      && (nCol2           == rOther.nCol2)
//STRIP001      && (nRow2           == rOther.nRow2)
//STRIP001      && (bHasHeader      == rOther.bHasHeader)
//STRIP001      && (bByRow          == rOther.bByRow)
//STRIP001      && (bCaseSens       == rOther.bCaseSens)
//STRIP001      && (bUserDef        == rOther.bUserDef)
//STRIP001      && (nUserIndex      == rOther.nUserIndex)
//STRIP001      && (bIncludePattern == rOther.bIncludePattern)
//STRIP001      && (bInplace        == rOther.bInplace)
//STRIP001      && (nDestTab        == rOther.nDestTab)
//STRIP001      && (nDestCol        == rOther.nDestCol)
//STRIP001      && (nDestRow        == rOther.nDestRow)
//STRIP001      && (aCollatorLocale.Language    == rOther.aCollatorLocale.Language)
//STRIP001      && (aCollatorLocale.Country     == rOther.aCollatorLocale.Country)
//STRIP001      && (aCollatorLocale.Variant     == rOther.aCollatorLocale.Variant)
//STRIP001      && (aCollatorAlgorithm          == rOther.aCollatorAlgorithm)
//STRIP001      )
//STRIP001  {
//STRIP001      bEqual = TRUE;
//STRIP001      for ( USHORT i=0; i<=nLast && bEqual; i++ )
//STRIP001      {
//STRIP001          bEqual = (nField[i] == rOther.nField[i]) && (bAscending[i]  == rOther.bAscending[i]);
//STRIP001      }
//STRIP001  }
//STRIP001  return bEqual;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScSortParam::ScSortParam( const ScSubTotalParam& rSub, const ScSortParam& rOld ) :
//STRIP001      nCol1(rSub.nCol1),nRow1(rSub.nRow1),nCol2(rSub.nCol2),nRow2(rSub.nRow2),
//STRIP001      bHasHeader(TRUE),bCaseSens(rSub.bCaseSens),
//STRIP001      bByRow(TRUE),bUserDef(rSub.bUserDef),nUserIndex(rSub.nUserIndex),bIncludePattern(rSub.bIncludePattern),
//STRIP001      bInplace(TRUE),
//STRIP001      nDestTab(0),nDestCol(0),nDestRow(0),
//STRIP001      aCollatorLocale( rOld.aCollatorLocale ), aCollatorAlgorithm( rOld.aCollatorAlgorithm )
//STRIP001 {
//STRIP001  USHORT nNewCount = 0;
//STRIP001  USHORT i;
//STRIP001
//STRIP001  //  zuerst die Gruppen aus den Teilergebnissen
//STRIP001  if (rSub.bDoSort)
//STRIP001      for (i=0; i<MAXSUBTOTAL; i++)
//STRIP001          if (rSub.bGroupActive[i])
//STRIP001          {
//STRIP001              if (nNewCount < MAXSORT)
//STRIP001              {
//STRIP001                  bDoSort[nNewCount]    = TRUE;
//STRIP001                  nField[nNewCount]     = rSub.nField[i];
//STRIP001                  bAscending[nNewCount] = rSub.bAscending;
//STRIP001                  ++nNewCount;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001  //  dann dahinter die alten Einstellungen
//STRIP001  for (i=0; i<MAXSORT; i++)
//STRIP001      if (rOld.bDoSort[i])
//STRIP001      {
//STRIP001          USHORT nThisField = rOld.nField[i];
//STRIP001          BOOL bDouble = FALSE;
//STRIP001          for (USHORT j=0; j<nNewCount; j++)
//STRIP001              if ( nField[j] == nThisField )
//STRIP001                  bDouble = TRUE;
//STRIP001          if (!bDouble)               // ein Feld nicht zweimal eintragen
//STRIP001          {
//STRIP001              if (nNewCount < MAXSORT)
//STRIP001              {
//STRIP001                  bDoSort[nNewCount]    = TRUE;
//STRIP001                  nField[nNewCount]     = nThisField;
//STRIP001                  bAscending[nNewCount] = rOld.bAscending[i];
//STRIP001                  ++nNewCount;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  for (i=nNewCount; i<MAXSORT; i++)       // Rest loeschen
//STRIP001  {
//STRIP001      bDoSort[i]    = FALSE;
//STRIP001      nField[i]     = 0;
//STRIP001      bAscending[i] = TRUE;
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScSortParam::ScSortParam( const ScQueryParam& rParam, USHORT nCol ) :
//STRIP001      nCol1(nCol),nRow1(rParam.nRow1),nRow2(rParam.nRow2),nCol2(nCol),
//STRIP001      bHasHeader(rParam.bHasHeader),bCaseSens(rParam.bCaseSens),
//STRIP001 //! TODO: what about Locale and Algorithm?
//STRIP001      bByRow(TRUE),bUserDef(FALSE),nUserIndex(0),bIncludePattern(FALSE),
//STRIP001      bInplace(TRUE),
//STRIP001      nDestTab(0),nDestCol(0),nDestRow(0)
//STRIP001 {
//STRIP001  bDoSort[0] = TRUE;
//STRIP001  nField[0] = nCol;
//STRIP001  bAscending[0] = TRUE;
//STRIP001  for (USHORT i=1; i<MAXSORT; i++)
//STRIP001  {
//STRIP001      bDoSort[i]    = FALSE;
//STRIP001      nField[i]     = 0;
//STRIP001      bAscending[i] = TRUE;
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScSortParam::MoveToDest()
//STRIP001 {
//STRIP001  if (!bInplace)
//STRIP001  {
//STRIP001      short nDifX = ((short) nDestCol) - ((short) nCol1);
//STRIP001      short nDifY = ((short) nDestRow) - ((short) nRow1);
//STRIP001
//STRIP001      nCol1 += nDifX;
//STRIP001      nRow1 += nDifY;
//STRIP001      nCol2 += nDifX;
//STRIP001      nRow2 += nDifY;
//STRIP001      for (USHORT i=0; i<MAXSORT; i++)
//STRIP001          if (bByRow)
//STRIP001              nField[i] += nDifX;
//STRIP001          else
//STRIP001              nField[i] += nDifY;
//STRIP001
//STRIP001      bInplace = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR("MoveToDest, bInplace == TRUE");
//STRIP001 }

}
