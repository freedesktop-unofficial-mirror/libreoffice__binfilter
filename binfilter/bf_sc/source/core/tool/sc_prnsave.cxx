/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_prnsave.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 17:14:12 $
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

#include "prnsave.hxx"
#include "global.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

//------------------------------------------------------------------

//
//      Daten pro Tabelle
//

/*N*/ ScPrintSaverTab::ScPrintSaverTab() :
/*N*/   nPrintCount(0),
/*N*/   pPrintRanges(NULL),
/*N*/   pRepeatCol(NULL),
/*N*/   pRepeatRow(NULL)
/*N*/ {
/*N*/ }

/*N*/ ScPrintSaverTab::~ScPrintSaverTab()
/*N*/ {
/*N*/   delete[] pPrintRanges;
/*N*/   delete pRepeatCol;
/*N*/   delete pRepeatRow;
/*N*/ }

/*N*/ void ScPrintSaverTab::SetAreas( USHORT nCount, const ScRange* pRanges )
/*N*/ {
/*N*/   delete[] pPrintRanges;
/*N*/   if (nCount && pRanges)
/*N*/   {
/*N*/       nPrintCount = nCount;
/*N*/       pPrintRanges = new ScRange[nCount];
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/           pPrintRanges[i] = pRanges[i];
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nPrintCount = 0;
/*N*/       pPrintRanges = NULL;
/*N*/   }
/*N*/ }

/*N*/ void ScPrintSaverTab::SetRepeat( const ScRange* pCol, const ScRange* pRow )
/*N*/ {
/*N*/   delete pRepeatCol;
/*N*/   pRepeatCol = pCol ? new ScRange(*pCol) : NULL;
/*N*/   delete pRepeatRow;
/*N*/   pRepeatRow = pRow ? new ScRange(*pRow) : NULL;
/*N*/ }

//STRIP001 inline BOOL PtrEqual( const ScRange* p1, const ScRange* p2 )
//STRIP001 {
//STRIP001  return ( !p1 && !p2 ) || ( p1 && p2 && *p1 == *p2 );
//STRIP001 }

//STRIP001 BOOL ScPrintSaverTab::operator==( const ScPrintSaverTab& rCmp ) const
//STRIP001 {
//STRIP001  BOOL bEqual = ( nPrintCount == rCmp.nPrintCount &&
//STRIP001                  PtrEqual( pRepeatCol, rCmp.pRepeatCol ) &&
//STRIP001                  PtrEqual( pRepeatRow, rCmp.pRepeatRow ) );
//STRIP001  if (bEqual)
//STRIP001      for (USHORT i=0; i<nPrintCount; i++)
//STRIP001          if ( pPrintRanges[i] != rCmp.pPrintRanges[i] )
//STRIP001          {
//STRIP001              bEqual = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001  return bEqual;
//STRIP001 }

//
//      Daten fuer das ganze Dokument
//

/*N*/ ScPrintRangeSaver::ScPrintRangeSaver( USHORT nCount ) :
/*N*/   nTabCount( nCount )
/*N*/ {
/*N*/   if (nCount)
/*N*/       pData = new ScPrintSaverTab[nCount];
/*N*/   else
/*N*/       pData = NULL;
/*N*/ }

/*N*/ ScPrintRangeSaver::~ScPrintRangeSaver()
/*N*/ {
/*N*/   delete[] pData;
/*N*/ }

/*N*/ ScPrintSaverTab& ScPrintRangeSaver::GetTabData(USHORT nTab)
/*N*/ {
/*N*/   DBG_ASSERT(nTab<nTabCount,"ScPrintRangeSaver Tab zu gross");
/*N*/   return pData[nTab];
/*N*/ }

//STRIP001 const ScPrintSaverTab& ScPrintRangeSaver::GetTabData(USHORT nTab) const
//STRIP001 {
//STRIP001  DBG_ASSERT(nTab<nTabCount,"ScPrintRangeSaver Tab zu gross");
//STRIP001  return pData[nTab];
//STRIP001 }

//STRIP001 BOOL ScPrintRangeSaver::operator==( const ScPrintRangeSaver& rCmp ) const
//STRIP001 {
//STRIP001  BOOL bEqual = ( nTabCount == rCmp.nTabCount );
//STRIP001  if (bEqual)
//STRIP001      for (USHORT i=0; i<nTabCount; i++)
//STRIP001          if (!(pData[i]==rCmp.pData[i]))
//STRIP001          {
//STRIP001              bEqual = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001  return bEqual;
//STRIP001 }




}
