/*************************************************************************
 *
 *  $RCSfile: sc_prnsave.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:19:47 $
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
