/*************************************************************************
 *
 *  $RCSfile: sc_attarray.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:35:38 $
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

//------------------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/algitem.hxx>
#include <bf_svx/boxitem.hxx>
#include <bf_svx/frmdiritem.hxx>
#include <bf_svx/shaditem.hxx>
#include <svtools/poolcach.hxx>

#ifndef _SVX_FONTITEM_HXX
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SV_FONTCVT_HXX
#include <vcl/fontcvt.hxx>
#endif

#include "attarray.hxx"
#include "global.hxx"
#include "document.hxx"
#include "docpool.hxx"
#include "patattr.hxx"
#include "stlsheet.hxx"
#include "stlpool.hxx"
#include "markarr.hxx"
#include "rechead.hxx"
#include "globstr.hrc"


#undef DBG_INVALIDATE
/*N*/ #define DBGOUTPUT(s) \
/*N*/   DBG_ERROR( String("Invalidate ") + String(s) + String(": ") \
/*N*/              + String(nCol) + String('/') + String(aAdrStart.Row()) + String('/') + String(nTab) \
/*N*/              + String(" bis ") \
/*N*/              + String(nCol) + String('/') + String(aAdrEnd.Row())   + String('/') + String(nTab) \
/*N*/             );

// STATIC DATA -----------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ ScAttrArray::ScAttrArray( USHORT nNewCol, USHORT nNewTab, ScDocument* pDoc ) :
/*N*/   nCol( nNewCol ),
/*N*/   nTab( nNewTab ),
/*N*/   pDocument( pDoc )
/*N*/ {
/*N*/   ScDocumentPool* pDocPool = pDocument->GetPool();
/*N*/
/*N*/     nCount = nLimit = 1;
/*N*/   pData = new ScAttrEntry[1];
/*N*/   if (pData)
/*N*/   {
/*N*/       pData[0].nRow = MAXROW;
/*N*/       pData[0].pPattern = pDocument->GetDefPattern();     // ohne Put !!!
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScAttrArray::~ScAttrArray()
/*N*/ {
/*N*/ #ifdef DBG_UTIL
/*N*/   TestData();
/*N*/ #endif
/*N*/
/*N*/   if (pData)
/*N*/   {
/*N*/       ScDocumentPool* pDocPool = pDocument->GetPool();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/           pDocPool->Remove(*pData[i].pPattern);
/*N*/
/*N*/       delete[] pData;
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScAttrArray::TestData() const
/*N*/ {
/*N*/ #ifdef DBG_UTIL
/*N*/   USHORT nErr = 0;
/*N*/   if (pData)
/*N*/   {
/*N*/       for (USHORT nPos=0; nPos<nCount; nPos++)
/*N*/       {
/*N*/           if (nPos)
/*N*/               if (pData[nPos].pPattern == pData[nPos-1].pPattern || pData[nPos].nRow <= pData[nPos-1].nRow)
/*N*/                   ++nErr;
/*N*/           if (pData[nPos].pPattern->Which() != ATTR_PATTERN)
/*N*/               ++nErr;
/*N*/       }
/*N*/         if ( nPos && pData[nPos-1].nRow != MAXROW )
/*N*/             ++nErr;
/*N*/   }
/*N*/   if (nErr)
/*N*/   {
/*?*/       ByteString aMsg = ByteString::CreateFromInt32(nErr);
/*?*/       aMsg += " errors in attribute array, column ";
/*?*/       aMsg += ByteString::CreateFromInt32(nCol);
/*?*/       DBG_ERROR( aMsg.GetBuffer() );
/*N*/   }
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScAttrArray::Reset( const ScPatternAttr* pPattern, BOOL bAlloc )
/*N*/ {
/*N*/   if (pData)
/*N*/   {
/*N*/       ScDocumentPool*      pDocPool = pDocument->GetPool();
/*N*/       const ScPatternAttr* pOldPattern;
/*N*/       ScAddress            aAdrStart( nCol, 0, nTab );
/*N*/       ScAddress            aAdrEnd  ( nCol, 0, nTab );
/*N*/
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           // ueberpruefen, ob Attributierung die Textbreite der Zelle aendert
/*N*/           pOldPattern = pData[i].pPattern;
/*N*/           BOOL bNumFormatChanged;
/*N*/           if ( ScGlobal::CheckWidthInvalidate( bNumFormatChanged,
/*N*/                   pPattern->GetItemSet(), pOldPattern->GetItemSet() ) )
/*N*/           {
/*N*/               aAdrStart.SetRow( i ? pData[i-1].nRow+1 : 0 );
/*N*/               aAdrEnd  .SetRow( pData[i].nRow );
/*N*/               pDocument->InvalidateTextWidth( &aAdrStart, &aAdrEnd, bNumFormatChanged );
/*N*/ #ifdef DBG_INVALIDATE
/*N*/               DBGOUTPUT("Reset");
/*N*/ #endif
/*N*/           }
/*N*/           // bedingtes Format gesetzt oder geloescht?
/*N*/           if ( &pPattern->GetItem(ATTR_CONDITIONAL) != &pOldPattern->GetItem(ATTR_CONDITIONAL) )
/*N*/           {
/*?*/               pDocument->ConditionalChanged( ((const SfxUInt32Item&)
/*?*/                               pOldPattern->GetItem(ATTR_CONDITIONAL)).GetValue() );
/*?*/               pDocument->ConditionalChanged( ((const SfxUInt32Item&)
/*?*/                               pPattern->GetItem(ATTR_CONDITIONAL)).GetValue() );
/*N*/           }
/*N*/           pDocPool->Remove(*pOldPattern);
/*N*/       }
/*N*/       delete[] pData;
/*N*/
/*N*/       if (bAlloc)
/*N*/       {
/*N*/             nCount = nLimit = 1;
/*N*/           pData = new ScAttrEntry[1];
/*N*/           if (pData)
/*N*/           {
/*N*/               ScPatternAttr* pNewPattern = (ScPatternAttr*) &pDocPool->Put(*pPattern);
/*N*/               pData[0].nRow = MAXROW;
/*N*/               pData[0].pPattern = pNewPattern;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/             nCount = nLimit = 0;
/*N*/           pData = NULL;               // muss sofort wieder belegt werden !
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ BOOL ScAttrArray::Concat(USHORT nPos)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   if (pData && (nPos < nCount))
/*N*/   {
/*N*/       if (nPos > 0)
/*N*/       {
/*N*/           if (pData[nPos - 1].pPattern == pData[nPos].pPattern)
/*N*/           {
/*?*/               pData[nPos - 1].nRow = pData[nPos].nRow;
/*?*/               pDocument->GetPool()->Remove(*pData[nPos].pPattern);
/*?*/               memmove(&pData[nPos], &pData[nPos + 1], (nCount - nPos - 1) * sizeof(ScAttrEntry));
/*?*/               pData[nCount - 1].pPattern = NULL;
/*?*/               pData[nCount - 1].nRow = 0;
/*?*/               nCount--;
/*?*/               nPos--;
/*?*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/       if (nPos + 1 < nCount)
/*N*/       {
/*N*/           if (pData[nPos + 1].pPattern == pData[nPos].pPattern)
/*N*/           {
/*N*/               pData[nPos].nRow = pData[nPos + 1].nRow;
/*N*/               pDocument->GetPool()->Remove(*pData[nPos].pPattern);
/*N*/               memmove(&pData[nPos + 1], &pData[nPos + 2], (nCount - nPos - 2) * sizeof(ScAttrEntry));
/*N*/               pData[nCount - 1].pPattern = NULL;
/*N*/               pData[nCount - 1].nRow = 0;
/*N*/               nCount--;
/*N*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScAttrArray::Search( USHORT nRow, short& nIndex ) const
/*N*/ {
/*N*/   short   nLo         = 0;
/*N*/   short   nHi         = ((short) nCount) - 1;
/*N*/   short   nStartRow   = 0;
/*N*/   short   nEndRow     = 0;
/*N*/   short   i           = 0;
/*N*/   BOOL    bFound      = (nCount == 1);
/*N*/   if (pData)
/*N*/   {
/*N*/       while ( !bFound && nLo <= nHi )
/*N*/       {
/*N*/           i = (nLo + nHi) / 2;
/*N*/           if (i > 0)
/*N*/               nStartRow = (short) pData[i - 1].nRow;
/*N*/           else
/*N*/               nStartRow = -1;
/*N*/           nEndRow = (short) pData[i].nRow;
/*N*/           if (nEndRow < (short) nRow)
/*N*/               nLo = ++i;
/*N*/           else
/*N*/               if (nStartRow >= (short) nRow)
/*N*/                   nHi = --i;
/*N*/               else
/*N*/                   bFound = TRUE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       bFound = FALSE;
/*N*/
/*N*/   if (bFound)
/*N*/       nIndex=i;
/*N*/   else
/*N*/       nIndex=0;
/*N*/   return bFound;
/*N*/ }


/*N*/ const ScPatternAttr* ScAttrArray::GetPattern( USHORT nRow ) const
/*N*/ {
/*N*/   short i;
/*N*/   if (Search( nRow, i ))
/*N*/       return pData[i].pPattern;
/*N*/   else
/*N*/       return NULL;
/*N*/ }


//STRIP001 const ScPatternAttr* ScAttrArray::GetPatternRange( USHORT& rStartRow,
//STRIP001      USHORT& rEndRow, USHORT nRow ) const
//STRIP001 {
//STRIP001  short nIndex;
//STRIP001  if ( Search( nRow, nIndex ) )
//STRIP001  {
//STRIP001      if ( nIndex > 0 )
//STRIP001          rStartRow = pData[nIndex-1].nRow + 1;
//STRIP001      else
//STRIP001          rStartRow = 0;
//STRIP001      rEndRow = pData[nIndex].nRow;
//STRIP001      return pData[nIndex].pPattern;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ void ScAttrArray::SetPattern( USHORT nRow, const ScPatternAttr* pPattern, BOOL bPutToPool )
/*N*/ {
/*N*/   SetPatternArea( nRow, nRow, pPattern, bPutToPool );
/*N*/ }


/*N*/ void ScAttrArray::SetPatternArea(USHORT nStartRow, USHORT nEndRow, const ScPatternAttr *pPattern, BOOL bPutToPool )
/*N*/ {
/*N*/   if (nStartRow >= 0 && nStartRow <= MAXROW && nEndRow >= 0 && nEndRow <= MAXROW)
/*N*/   {
/*N*/       if (bPutToPool)
/*N*/           pPattern = (const ScPatternAttr*) &pDocument->GetPool()->Put(*pPattern);
/*N*/
/*N*/       if ((nStartRow == 0) && (nEndRow == MAXROW))
/*N*/           Reset(pPattern);
/*N*/       else
/*N*/       {
/*N*/             USHORT nNeeded = nCount + 2;
/*N*/             if ( nLimit < nNeeded )
/*N*/             {
/*N*/                 nLimit += SC_ATTRARRAY_DELTA;
/*N*/                 if ( nLimit < nNeeded )
/*N*/                     nLimit = nNeeded;
/*N*/                 ScAttrEntry* pNewData = new ScAttrEntry[nLimit];
/*N*/                 memcpy( pNewData, pData, nCount*sizeof(ScAttrEntry) );
/*N*/               delete[] pData;
/*N*/               pData = pNewData;
/*N*/             }
/*N*/
/*N*/             ScAddress       aAdrStart( nCol, 0, nTab );
/*N*/             ScAddress       aAdrEnd  ( nCol, 0, nTab );
/*N*/
/*N*/             USHORT ni = 0;      // number of entries in beginning
/*N*/             USHORT nx = 0;      // track position
/*N*/             USHORT ns = 0;      // start row of track position
/*N*/             if ( nStartRow > 0 )
/*N*/             {
/*N*/                 // skip beginning
/*N*/                 short nIndex;
/*N*/                 Search( nStartRow, nIndex );
/*N*/                 ni = nIndex;
/*N*/
/*N*/                 if ( ni )
/*N*/                 {
/*N*/                     nx = ni;
/*N*/                     ns = pData[ni-1].nRow+1;
/*N*/                 }
/*N*/             }
/*N*/
/*N*/             // ueberpruefen, ob Attributierung die Textbreite der Zelle aendert
/*N*/             // oder bedingte Formate neu gesetzt oder geloescht werden
/*N*/             while ( ns <= nEndRow )
/*N*/             {
/*N*/                 const SfxItemSet& rNewSet = pPattern->GetItemSet();
/*N*/                 const SfxItemSet& rOldSet = pData[nx].pPattern->GetItemSet();
/*N*/
/*N*/                 BOOL bNumFormatChanged;
/*N*/                 if ( ScGlobal::CheckWidthInvalidate( bNumFormatChanged,
/*N*/                         rNewSet, rOldSet ) )
/*N*/                 {
/*N*/                     aAdrStart.SetRow( Max(nStartRow,ns) );
/*N*/                     aAdrEnd  .SetRow( Min(nEndRow,pData[nx].nRow) );
/*N*/                     pDocument->InvalidateTextWidth( &aAdrStart, &aAdrEnd, bNumFormatChanged );
/*N*/ #ifdef DBG_INVALIDATE
/*N*/                     DBGOUTPUT("SetPatternArea");
/*N*/ #endif
/*N*/                 }
/*N*/                 if ( &rNewSet.Get(ATTR_CONDITIONAL) != &rOldSet.Get(ATTR_CONDITIONAL) )
/*N*/                 {
/*N*/                     pDocument->ConditionalChanged( ((const SfxUInt32Item&)
/*N*/                                     rOldSet.Get(ATTR_CONDITIONAL)).GetValue() );
/*N*/                     pDocument->ConditionalChanged( ((const SfxUInt32Item&)
/*N*/                                     rNewSet.Get(ATTR_CONDITIONAL)).GetValue() );
/*N*/                 }
/*N*/                 ns = pData[nx].nRow + 1;
/*N*/                 nx++;
/*N*/             }
/*N*/
/*N*/             // continue modifying data array
/*N*/
/*N*/             USHORT nInsert;     // insert position (MAXROW+1 := no insert)
/*N*/             BOOL bCombined = FALSE;
/*N*/             BOOL bSplit = FALSE;
/*N*/             if ( nStartRow > 0 )
/*N*/             {
/*N*/                 nInsert = MAXROW+1;
/*N*/                 if ( pData[ni].pPattern != pPattern )
/*N*/                 {
/*N*/                     if ( ni == 0 || (pData[ni-1].nRow < nStartRow - 1) )
/*N*/                     {   // may be a split or a simple insert or just a shrink,
/*N*/                         // row adjustment is done further down
/*N*/                         if ( pData[ni].nRow > nEndRow )
/*N*/                             bSplit = TRUE;
/*N*/                         ni++;
/*N*/                         nInsert = ni;
/*N*/                     }
/*N*/                     else if ( ni > 0 && pData[ni-1].nRow == nStartRow - 1 )
/*N*/                         nInsert = ni;
/*N*/                 }
/*N*/                 if ( ni > 0 && pData[ni-1].pPattern == pPattern )
/*N*/                 {   // combine
/*N*/                     pData[ni-1].nRow = nEndRow;
/*N*/                     nInsert = MAXROW+1;
/*N*/                     bCombined = TRUE;
/*N*/                 }
/*N*/             }
/*N*/             else
/*N*/                 nInsert = 0;
/*N*/
/*N*/             USHORT nj = ni;     // stop position of range to replace
/*N*/             while ( nj < nCount && pData[nj].nRow <= nEndRow )
/*N*/                 nj++;
/*N*/             if ( !bSplit )
/*N*/             {
/*N*/                 if ( nj < nCount && pData[nj].pPattern == pPattern )
/*N*/                 {   // combine
/*N*/                     if ( ni > 0 )
/*N*/                     {
/*N*/                         if ( pData[ni-1].pPattern == pPattern )
/*N*/                         {   // adjacent entries
/*N*/                             pData[ni-1].nRow = pData[nj].nRow;
/*N*/                             nj++;
/*N*/                         }
/*N*/                         else if ( ni == nInsert )
/*N*/                             pData[ni-1].nRow = nStartRow - 1;   // shrink
/*N*/                     }
/*N*/                     nInsert = MAXROW+1;
/*N*/                     bCombined = TRUE;
/*N*/                 }
/*N*/                 else if ( ni > 0 && ni == nInsert )
/*N*/                     pData[ni-1].nRow = nStartRow - 1;   // shrink
/*N*/             }
/*N*/             ScDocumentPool* pDocPool = pDocument->GetPool();
/*N*/             if ( bSplit )
/*N*/             {   // duplicate splitted entry in pool
/*N*/                 pDocPool->Put( *pData[ni-1].pPattern );
/*N*/             }
/*N*/             if ( ni < nj )
/*N*/             {   // remove middle entries
/*N*/                 for ( USHORT nk=ni; nk<nj; nk++)
/*N*/                 {   // remove entries from pool
/*N*/                     pDocPool->Remove( *pData[nk].pPattern );
/*N*/                 }
/*N*/                 if ( !bCombined )
/*N*/                 {   // replace one entry
/*N*/                     pData[ni].nRow = nEndRow;
/*N*/                     pData[ni].pPattern = pPattern;
/*N*/                     ni++;
/*N*/                     nInsert = MAXROW+1;
/*N*/                 }
/*N*/                 if ( ni < nj )
/*N*/                 {   // remove entries
/*N*/                     memmove( pData + ni, pData + nj, (nCount - nj) * sizeof(ScAttrEntry) );
/*N*/                     nCount -= nj - ni;
/*N*/                 }
/*N*/             }
/*N*/
/*N*/             if ( nInsert <= MAXROW )
/*N*/             {   // insert or append new entry
/*N*/                 if ( nInsert <= nCount )
/*N*/                 {
/*N*/                     if ( !bSplit )
/*N*/                         memmove( pData + nInsert + 1, pData + nInsert,
/*N*/                             (nCount - nInsert) * sizeof(ScAttrEntry) );
/*N*/                     else
/*N*/                     {
/*N*/                         memmove( pData + nInsert + 2, pData + nInsert,
/*N*/                             (nCount - nInsert) * sizeof(ScAttrEntry) );
/*N*/                         pData[nInsert+1] = pData[nInsert-1];
/*N*/                         nCount++;
/*N*/                     }
/*N*/                 }
/*N*/                 if ( nInsert )
/*N*/                     pData[nInsert-1].nRow = nStartRow - 1;
/*N*/                 pData[nInsert].nRow = nEndRow;
/*N*/                 pData[nInsert].pPattern = pPattern;
/*N*/                 nCount++;
/*N*/             }
/*N*/       }
/*N*/   }
/*N*/ //    InfoBox(0, String(nCount) + String(" Eintraege") ).Execute();
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/     TestData();
/*N*/ #endif
/*N*/ }


/*N*/ void ScAttrArray::ApplyStyleArea( USHORT nStartRow, USHORT nEndRow, ScStyleSheet* pStyle )
/*N*/ {
/*N*/   if (nStartRow >= 0 && nStartRow <= MAXROW && nEndRow >= 0 && nEndRow <= MAXROW)
/*N*/   {
/*N*/       short nPos;
/*N*/       USHORT nStart=0;
/*N*/       if (!Search( nStartRow, nPos ))
/*N*/       {
/*N*/           DBG_ERROR("Search-Fehler");
/*N*/           return;
/*N*/       }
/*N*/
/*N*/       ScAddress aAdrStart( nCol, 0, nTab );
/*N*/       ScAddress aAdrEnd  ( nCol, 0, nTab );
/*N*/
/*N*/       do
/*N*/       {
/*N*/           const ScPatternAttr* pOldPattern = pData[nPos].pPattern;
/*N*/           ScPatternAttr* pNewPattern = new ScPatternAttr(*pOldPattern);
/*N*/           pNewPattern->SetStyleSheet(pStyle);
/*N*/           USHORT nY1 = nStart;
/*N*/           USHORT nY2 = pData[nPos].nRow;
/*N*/           nStart = pData[nPos].nRow + 1;
/*N*/
/*N*/           if ( *pNewPattern == *pOldPattern )
/*N*/           {
/*N*/               // keep the original pattern (might be default)
/*N*/               // pNewPattern is deleted below
/*N*/               nPos++;
/*N*/           }
/*N*/           else if ( nY1 < nStartRow || nY2 > nEndRow )
/*N*/           {
/*N*/               if (nY1 < nStartRow) nY1=nStartRow;
/*N*/               if (nY2 > nEndRow) nY2=nEndRow;
/*N*/               SetPatternArea( nY1, nY2, pNewPattern, TRUE );
/*N*/               Search( nStart, nPos );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // ueberpruefen, ob Attributierung die Textbreite der Zelle aendert
/*N*/               // bedingte Formate in Vorlagen gibt es (noch) nicht
/*N*/
/*N*/               const SfxItemSet& rNewSet = pNewPattern->GetItemSet();
/*N*/               const SfxItemSet& rOldSet = pOldPattern->GetItemSet();
/*N*/
/*N*/               BOOL bNumFormatChanged;
/*N*/               if ( ScGlobal::CheckWidthInvalidate( bNumFormatChanged,
/*N*/                       rNewSet, rOldSet ) )
/*N*/               {
/*N*/                   aAdrStart.SetRow( nPos ? pData[nPos-1].nRow+1 : 0 );
/*N*/                   aAdrEnd  .SetRow( pData[nPos].nRow );
/*N*/                   pDocument->InvalidateTextWidth( &aAdrStart, &aAdrEnd, bNumFormatChanged );
/*N*/ #ifdef DBG_INVALIDATE
/*N*/                   DBGOUTPUT("ApplyStyleArea");
/*N*/ #endif
/*N*/               }
/*N*/
/*N*/               pDocument->GetPool()->Remove(*pData[nPos].pPattern);
/*N*/               pData[nPos].pPattern = (const ScPatternAttr*)
/*N*/                                           &pDocument->GetPool()->Put(*pNewPattern);
/*N*/               if (Concat(nPos))
/*?*/                   Search(nStart, nPos);
/*N*/               else
/*N*/                   nPos++;
/*N*/           }
/*N*/           delete pNewPattern;
/*N*/       }
/*N*/       while ((nStart <= nEndRow) && (nPos < (short)nCount));
/*N*/   }
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   TestData();
/*N*/ #endif
/*N*/ }


    // const wird weggecastet, weil es sonst
    // zu ineffizient/kompliziert wird!
//STRIP001 #define SET_LINECOLOR(dest,c)                        \
//STRIP001  if ((dest))                                     \
//STRIP001  {                                               \
//STRIP001      ((SvxBorderLine*)(dest))->SetColor((c));    \
//STRIP001  }
//STRIP001
//STRIP001 #define SET_LINE(dest,src)                               \
//STRIP001  if ((dest))                                         \
//STRIP001  {                                                   \
//STRIP001      SvxBorderLine* pCast = (SvxBorderLine*)(dest);  \
//STRIP001      pCast->SetOutWidth((src)->GetOutWidth());       \
//STRIP001      pCast->SetInWidth ((src)->GetInWidth());        \
//STRIP001      pCast->SetDistance((src)->GetDistance());       \
//STRIP001  }

//STRIP001 void ScAttrArray::ApplyLineStyleArea( USHORT nStartRow, USHORT nEndRow,
//STRIP001                                    const SvxBorderLine* pLine, BOOL bColorOnly )
//STRIP001 {
//STRIP001  if ( bColorOnly && !pLine )
//STRIP001      return;
//STRIP001
//STRIP001  if (nStartRow >= 0 && nStartRow <= MAXROW && nEndRow >= 0 && nEndRow <= MAXROW)
//STRIP001  {
//STRIP001      short nPos;
//STRIP001      USHORT nStart=0;
//STRIP001      if (!Search( nStartRow, nPos ))
//STRIP001      {
//STRIP001          DBG_ERROR("Search-Fehler");
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001      do
//STRIP001      {
//STRIP001          const ScPatternAttr*    pOldPattern = pData[nPos].pPattern;
//STRIP001          const SfxPoolItem*      pItem = NULL;
//STRIP001
//STRIP001          if ( SFX_ITEM_SET == pOldPattern->GetItemSet().
//STRIP001                                  GetItemState( ATTR_BORDER, TRUE, &pItem ) )
//STRIP001          {
//STRIP001              ScPatternAttr*  pNewPattern = new ScPatternAttr(*pOldPattern);
//STRIP001              SvxBoxItem      aBoxItem( *(const SvxBoxItem*)pItem );
//STRIP001              USHORT          nY1 = nStart;
//STRIP001              USHORT          nY2 = pData[nPos].nRow;
//STRIP001
//STRIP001              // Linienattribute holen und mit Parametern aktualisieren
//STRIP001
//STRIP001              if ( !pLine )
//STRIP001              {
//STRIP001                  if ( aBoxItem.GetTop() )    aBoxItem.SetLine( NULL, BOX_LINE_TOP );
//STRIP001                  if ( aBoxItem.GetBottom() ) aBoxItem.SetLine( NULL, BOX_LINE_BOTTOM );
//STRIP001                  if ( aBoxItem.GetLeft() )   aBoxItem.SetLine( NULL, BOX_LINE_LEFT );
//STRIP001                  if ( aBoxItem.GetRight() )  aBoxItem.SetLine( NULL, BOX_LINE_RIGHT );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if ( bColorOnly )
//STRIP001                  {
//STRIP001                      Color aColor( pLine->GetColor() );
//STRIP001                      SET_LINECOLOR( aBoxItem.GetTop(),    aColor );
//STRIP001                      SET_LINECOLOR( aBoxItem.GetBottom(), aColor );
//STRIP001                      SET_LINECOLOR( aBoxItem.GetLeft(),   aColor );
//STRIP001                      SET_LINECOLOR( aBoxItem.GetRight(),  aColor );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      SET_LINE( aBoxItem.GetTop(),    pLine );
//STRIP001                      SET_LINE( aBoxItem.GetBottom(), pLine );
//STRIP001                      SET_LINE( aBoxItem.GetLeft(),   pLine );
//STRIP001                      SET_LINE( aBoxItem.GetRight(),  pLine );
//STRIP001                  }
//STRIP001              }
//STRIP001              pNewPattern->GetItemSet().Put( aBoxItem );
//STRIP001
//STRIP001              nStart = pData[nPos].nRow + 1;
//STRIP001
//STRIP001              if ( nY1 < nStartRow || nY2 > nEndRow )
//STRIP001              {
//STRIP001                  if (nY1 < nStartRow) nY1=nStartRow;
//STRIP001                  if (nY2 > nEndRow) nY2=nEndRow;
//STRIP001                  SetPatternArea( nY1, nY2, pNewPattern, TRUE );
//STRIP001                  Search( nStart, nPos );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                      //! aus Pool loeschen?
//STRIP001                  pDocument->GetPool()->Remove(*pData[nPos].pPattern);
//STRIP001                  pData[nPos].pPattern = (const ScPatternAttr*)
//STRIP001                              &pDocument->GetPool()->Put(*pNewPattern);
//STRIP001
//STRIP001                  if (Concat(nPos))
//STRIP001                      Search(nStart, nPos);
//STRIP001                  else
//STRIP001                      nPos++;
//STRIP001              }
//STRIP001              delete pNewPattern;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nStart = pData[nPos].nRow + 1;
//STRIP001              nPos++;
//STRIP001          }
//STRIP001      }
//STRIP001      while ((nStart <= nEndRow) && (nPos < (short)nCount));
//STRIP001  }
//STRIP001 }

//STRIP001 #undef SET_LINECOLOR
//STRIP001 #undef SET_LINE


/*N*/ void ScAttrArray::ApplyCacheArea( USHORT nStartRow, USHORT nEndRow, SfxItemPoolCache* pCache )
/*N*/ {
/*N*/ #ifdef DBG_UTIL
/*N*/   TestData();
/*N*/ #endif
/*N*/
/*N*/   if (nStartRow >= 0 && nStartRow <= MAXROW && nEndRow >= 0 && nEndRow <= MAXROW)
/*N*/   {
/*N*/       short nPos;
/*N*/       USHORT nStart=0;
/*N*/       if (!Search( nStartRow, nPos ))
/*N*/       {
/*N*/           DBG_ERROR("Search-Fehler");
/*N*/           return;
/*N*/       }
/*N*/
/*N*/       ScAddress aAdrStart( nCol, 0, nTab );
/*N*/       ScAddress aAdrEnd  ( nCol, 0, nTab );
/*N*/
/*N*/       do
/*N*/       {
/*N*/           const ScPatternAttr* pOldPattern = pData[nPos].pPattern;
/*N*/           const ScPatternAttr* pNewPattern = (const ScPatternAttr*) &pCache->ApplyTo( *pOldPattern, TRUE );
/*N*/           ScDocumentPool::CheckRef( *pOldPattern );
/*N*/           ScDocumentPool::CheckRef( *pNewPattern );
/*N*/           if (pNewPattern != pOldPattern)
/*N*/           {
/*N*/               USHORT nY1 = nStart;
/*N*/               USHORT nY2 = pData[nPos].nRow;
/*N*/               nStart = pData[nPos].nRow + 1;
/*N*/
/*N*/               if ( nY1 < nStartRow || nY2 > nEndRow )
/*N*/               {
/*N*/                   if (nY1 < nStartRow) nY1=nStartRow;
/*N*/                   if (nY2 > nEndRow) nY2=nEndRow;
/*N*/                   SetPatternArea( nY1, nY2, pNewPattern );
/*N*/                   Search( nStart, nPos );
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   // ueberpruefen, ob Attributierung die Textbreite der Zelle aendert
/*N*/
/*N*/                   const SfxItemSet& rNewSet = pNewPattern->GetItemSet();
/*N*/                   const SfxItemSet& rOldSet = pOldPattern->GetItemSet();
/*N*/
/*N*/                   BOOL bNumFormatChanged;
/*N*/                   if ( ScGlobal::CheckWidthInvalidate( bNumFormatChanged,
/*N*/                           rNewSet, rOldSet ) )
/*N*/                   {
/*N*/                       aAdrStart.SetRow( nPos ? pData[nPos-1].nRow+1 : 0 );
/*N*/                       aAdrEnd  .SetRow( pData[nPos].nRow );
/*N*/                       pDocument->InvalidateTextWidth( &aAdrStart, &aAdrEnd, bNumFormatChanged );
/*N*/ #ifdef DBG_INVALIDATE
/*N*/                       DBGOUTPUT("ApplyCacheArea");
/*N*/ #endif
/*N*/                   }
/*N*/
/*N*/                   // bedingte Formate neu gesetzt oder geloescht ?
/*N*/
/*N*/                   if ( &rNewSet.Get(ATTR_CONDITIONAL) != &rOldSet.Get(ATTR_CONDITIONAL) )
/*N*/                   {
/*?*/                       pDocument->ConditionalChanged( ((const SfxUInt32Item&)
/*?*/                                       rOldSet.Get(ATTR_CONDITIONAL)).GetValue() );
/*?*/                       pDocument->ConditionalChanged( ((const SfxUInt32Item&)
/*?*/                                       rNewSet.Get(ATTR_CONDITIONAL)).GetValue() );
/*N*/                   }
/*N*/
/*N*/                   pDocument->GetPool()->Remove(*pData[nPos].pPattern);
/*N*/                   pData[nPos].pPattern = pNewPattern;
/*N*/                   if (Concat(nPos))
/*?*/                       Search(nStart, nPos);
/*N*/                   else
/*N*/                       ++nPos;
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/ //!!!!!!!!!!!!!!!!!! mit diesem Remove gibt es Abstuerze (Calc1 Import)
/*?*/ //!               pDocument->GetPool()->Remove(*pNewPattern);
/*?*/               nStart = pData[nPos].nRow + 1;
/*?*/               ++nPos;
/*N*/           }
/*N*/       }
/*N*/       while (nStart <= nEndRow);
/*N*/   }
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   TestData();
/*N*/ #endif
/*N*/ }


/*N*/ void lcl_MergeDeep( SfxItemSet& rMergeSet, const SfxItemSet& rSource )
/*N*/ {
/*N*/   const SfxPoolItem* pNewItem;
/*N*/   const SfxPoolItem* pOldItem;
/*N*/   for (USHORT nId=ATTR_PATTERN_START; nId<=ATTR_PATTERN_END; nId++)
/*N*/   {
/*N*/       //  pMergeSet hat keinen Parent
/*N*/       SfxItemState eOldState = rMergeSet.GetItemState( nId, FALSE, &pOldItem );
/*N*/
/*N*/       if ( eOldState == SFX_ITEM_DEFAULT )                // Default
/*N*/       {
/*N*/           SfxItemState eNewState = rSource.GetItemState( nId, TRUE, &pNewItem );
/*N*/           if ( eNewState == SFX_ITEM_SET )
/*N*/           {
/*N*/               if ( *pNewItem != rMergeSet.GetPool()->GetDefaultItem(nId) )
/*N*/                   rMergeSet.InvalidateItem( nId );
/*N*/           }
/*N*/       }
/*N*/       else if ( eOldState == SFX_ITEM_SET )               // Item gesetzt
/*N*/       {
/*N*/           SfxItemState eNewState = rSource.GetItemState( nId, TRUE, &pNewItem );
/*N*/           if ( eNewState == SFX_ITEM_SET )
/*N*/           {
/*N*/               if ( pNewItem != pOldItem )                 // beide gepuhlt
/*?*/                   rMergeSet.InvalidateItem( nId );
/*N*/           }
/*N*/           else            // Default
/*N*/           {
/*N*/               if ( *pOldItem != rSource.GetPool()->GetDefaultItem(nId) )
/*N*/                   rMergeSet.InvalidateItem( nId );
/*N*/           }
/*N*/       }
/*N*/       //  Dontcare bleibt Dontcare
/*N*/   }
/*N*/ }


/*N*/ void ScAttrArray::MergePatternArea( USHORT nStartRow, USHORT nEndRow,
/*N*/                                   SfxItemSet** ppSet, BOOL bDeep ) const
/*N*/ {
/*N*/   if (nStartRow >= 0 && nStartRow <= MAXROW && nEndRow >= 0 && nEndRow <= MAXROW)
/*N*/   {
/*N*/       const ScPatternAttr* pOld1 = NULL;
/*N*/       const ScPatternAttr* pOld2 = NULL;
/*N*/
/*N*/       short nPos;
/*N*/       USHORT nStart=0;
/*N*/       if (!Search( nStartRow, nPos ))
/*N*/       {
/*N*/           DBG_ERROR("Search-Fehler");
/*N*/           return;
/*N*/       }
/*N*/
/*N*/       do
/*N*/       {
/*N*/           //  gleiche Patterns muessen nicht mehrfach angesehen werden
/*N*/
/*N*/           const ScPatternAttr* pPattern = pData[nPos].pPattern;
/*N*/           if ( pPattern != pOld1 && pPattern != pOld2 )
/*N*/           {
/*N*/               const SfxItemSet& rThisSet = pPattern->GetItemSet();
/*N*/               if (*ppSet)
/*N*/               {
/*N*/                   //  (*ppSet)->MergeValues( rThisSet, FALSE );
/*N*/                   //  geht nicht, weil die Vorlagen nicht beruecksichtigt werden
/*N*/
/*N*/                   if (bDeep)
/*N*/                       lcl_MergeDeep( **ppSet, rThisSet );
/*N*/                   else
/*N*/                       (*ppSet)->MergeValues( rThisSet, FALSE );
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   //  erstes Pattern - in Set ohne Parent kopieren
/*N*/                   *ppSet = new SfxItemSet( *rThisSet.GetPool(), rThisSet.GetRanges() );
/*N*/                   (*ppSet)->Set( rThisSet, bDeep );
/*N*/               }
/*N*/
/*N*/               pOld2 = pOld1;
/*N*/               pOld1 = pPattern;
/*N*/           }
/*N*/
/*N*/           nStart = pData[nPos].nRow + 1;
/*N*/           ++nPos;
/*N*/       }
/*N*/       while (nStart <= nEndRow);
/*N*/   }
/*N*/ }



//          Umrandung zusammenbauen

//STRIP001 BOOL lcl_TestAttr( const SvxBorderLine* pOldLine, const SvxBorderLine* pNewLine,
//STRIP001                          BYTE& rModified, const SvxBorderLine*& rpNew )
//STRIP001 {
//STRIP001  if (rModified == SC_LINE_DONTCARE)
//STRIP001      return FALSE;                       // weiter geht's nicht
//STRIP001
//STRIP001  if (rModified == SC_LINE_EMPTY)
//STRIP001  {
//STRIP001      rModified = SC_LINE_SET;
//STRIP001      rpNew = pNewLine;
//STRIP001      return TRUE;                        // zum ersten mal gesetzt
//STRIP001  }
//STRIP001
//STRIP001  if (pOldLine == pNewLine)
//STRIP001  {
//STRIP001      rpNew = pOldLine;
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if (pOldLine && pNewLine)
//STRIP001      if (*pOldLine == *pNewLine)
//STRIP001      {
//STRIP001          rpNew = pOldLine;
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001
//STRIP001  rModified = SC_LINE_DONTCARE;
//STRIP001  rpNew = NULL;
//STRIP001  return TRUE;                            // andere Linie -> dontcare
//STRIP001 }


//STRIP001 void lcl_MergeToFrame( SvxBoxItem* pLineOuter, SvxBoxInfoItem* pLineInner,
//STRIP001                              ScLineFlags& rFlags, const ScPatternAttr* pPattern,
//STRIP001                              BOOL bLeft, USHORT nDistRight, BOOL bTop, USHORT nDistBottom )
//STRIP001 {
//STRIP001  //  rechten/unteren Rahmen setzen, wenn Zelle bis zum Ende zusammengefasst:
//STRIP001  const ScMergeAttr& rMerge = (const ScMergeAttr&)pPattern->GetItem(ATTR_MERGE);
//STRIP001  if ( rMerge.GetColMerge() == nDistRight + 1 )
//STRIP001      nDistRight = 0;
//STRIP001  if ( rMerge.GetRowMerge() == nDistBottom + 1 )
//STRIP001      nDistBottom = 0;
//STRIP001
//STRIP001  const SvxBoxItem* pCellFrame = (SvxBoxItem*) &pPattern->GetItemSet().Get( ATTR_BORDER );
//STRIP001  const SvxBorderLine* pLeftAttr   = pCellFrame->GetLeft();
//STRIP001  const SvxBorderLine* pRightAttr  = pCellFrame->GetRight();
//STRIP001  const SvxBorderLine* pTopAttr    = pCellFrame->GetTop();
//STRIP001  const SvxBorderLine* pBottomAttr = pCellFrame->GetBottom();
//STRIP001  const SvxBorderLine* pNew;
//STRIP001
//STRIP001  if (bTop)
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineOuter->GetTop(), pTopAttr, rFlags.nTop, pNew ))
//STRIP001          pLineOuter->SetLine( pNew, BOX_LINE_TOP );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineInner->GetHori(), pTopAttr, rFlags.nHori, pNew ))
//STRIP001          pLineInner->SetLine( pNew, BOXINFO_LINE_HORI );
//STRIP001  }
//STRIP001
//STRIP001  if (nDistBottom == 0)
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineOuter->GetBottom(), pBottomAttr, rFlags.nBottom, pNew ))
//STRIP001          pLineOuter->SetLine( pNew, BOX_LINE_BOTTOM );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineInner->GetHori(), pBottomAttr, rFlags.nHori, pNew ))
//STRIP001          pLineInner->SetLine( pNew, BOXINFO_LINE_HORI );
//STRIP001  }
//STRIP001
//STRIP001  if (bLeft)
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineOuter->GetLeft(), pLeftAttr, rFlags.nLeft, pNew ))
//STRIP001          pLineOuter->SetLine( pNew, BOX_LINE_LEFT );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineInner->GetVert(), pLeftAttr, rFlags.nVert, pNew ))
//STRIP001          pLineInner->SetLine( pNew, BOXINFO_LINE_VERT );
//STRIP001  }
//STRIP001
//STRIP001  if (nDistRight == 0)
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineOuter->GetRight(), pRightAttr, rFlags.nRight, pNew ))
//STRIP001          pLineOuter->SetLine( pNew, BOX_LINE_RIGHT );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (lcl_TestAttr( pLineInner->GetVert(), pRightAttr, rFlags.nVert, pNew ))
//STRIP001          pLineInner->SetLine( pNew, BOXINFO_LINE_VERT );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScAttrArray::MergeBlockFrame( SvxBoxItem* pLineOuter, SvxBoxInfoItem* pLineInner,
//STRIP001                  ScLineFlags& rFlags,
//STRIP001                  USHORT nStartRow, USHORT nEndRow, BOOL bLeft, USHORT nDistRight ) const
//STRIP001 {
//STRIP001  const ScPatternAttr* pPattern;
//STRIP001
//STRIP001  if (nStartRow == nEndRow)
//STRIP001  {
//STRIP001      pPattern = GetPattern( nStartRow );
//STRIP001      lcl_MergeToFrame( pLineOuter, pLineInner, rFlags, pPattern, bLeft, nDistRight, TRUE, 0 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pPattern = GetPattern( nStartRow );
//STRIP001      lcl_MergeToFrame( pLineOuter, pLineInner, rFlags, pPattern, bLeft, nDistRight, TRUE,
//STRIP001                          nEndRow-nStartRow );
//STRIP001
//STRIP001      short nStartIndex;
//STRIP001      short nEndIndex;
//STRIP001      Search( nStartRow+1, nStartIndex );
//STRIP001      Search( nEndRow-1, nEndIndex );
//STRIP001      for (short i=nStartIndex; i<=nEndIndex; i++)
//STRIP001      {
//STRIP001          pPattern = (ScPatternAttr*) pData[i].pPattern;
//STRIP001          lcl_MergeToFrame( pLineOuter, pLineInner, rFlags, pPattern, bLeft, nDistRight, FALSE,
//STRIP001                          nEndRow - Min( pData[i].nRow, (USHORT)(nEndRow-1) ) );
//STRIP001          // nDistBottom hier immer > 0
//STRIP001      }
//STRIP001
//STRIP001      pPattern = GetPattern( nEndRow );
//STRIP001      lcl_MergeToFrame( pLineOuter, pLineInner, rFlags, pPattern, bLeft, nDistRight, FALSE, 0 );
//STRIP001  }
//STRIP001 }

//
//  Rahmen anwenden
//

//  ApplyFrame - auf einen Eintrag im Array


//STRIP001 BOOL ScAttrArray::ApplyFrame( const SvxBoxItem*      pBoxItem,
//STRIP001                            const SvxBoxInfoItem* pBoxInfoItem,
//STRIP001                            USHORT nStartRow, USHORT nEndRow,
//STRIP001                            BOOL bLeft, USHORT nDistRight, BOOL bTop, USHORT nDistBottom )
//STRIP001 {
//STRIP001  DBG_ASSERT( pBoxItem && pBoxInfoItem, "Linienattribute fehlen!" );
//STRIP001
//STRIP001  const ScPatternAttr* pPattern = GetPattern( nStartRow );
//STRIP001  const SvxBoxItem* pOldFrame = (const SvxBoxItem*)
//STRIP001                                &pPattern->GetItemSet().Get( ATTR_BORDER );
//STRIP001
//STRIP001  //  rechten/unteren Rahmen setzen, wenn Zelle bis zum Ende zusammengefasst:
//STRIP001  const ScMergeAttr& rMerge = (const ScMergeAttr&)pPattern->GetItem(ATTR_MERGE);
//STRIP001  if ( rMerge.GetColMerge() == nDistRight + 1 )
//STRIP001      nDistRight = 0;
//STRIP001  if ( rMerge.GetRowMerge() == nDistBottom + 1 )
//STRIP001      nDistBottom = 0;
//STRIP001
//STRIP001  SvxBoxItem aNewFrame( *pOldFrame );
//STRIP001
//STRIP001  if ( bLeft ? pBoxInfoItem->IsValid(VALID_LEFT) : pBoxInfoItem->IsValid(VALID_VERT) )
//STRIP001      aNewFrame.SetLine( bLeft ? pBoxItem->GetLeft() : pBoxInfoItem->GetVert(),
//STRIP001          BOX_LINE_LEFT );
//STRIP001  if ( (nDistRight==0) ? pBoxInfoItem->IsValid(VALID_RIGHT) : pBoxInfoItem->IsValid(VALID_VERT) )
//STRIP001      aNewFrame.SetLine( (nDistRight==0) ? pBoxItem->GetRight() : pBoxInfoItem->GetVert(),
//STRIP001          BOX_LINE_RIGHT );
//STRIP001  if ( bTop ? pBoxInfoItem->IsValid(VALID_TOP) : pBoxInfoItem->IsValid(VALID_HORI) )
//STRIP001      aNewFrame.SetLine( bTop ? pBoxItem->GetTop() : pBoxInfoItem->GetHori(),
//STRIP001          BOX_LINE_TOP );
//STRIP001  if ( (nDistBottom==0) ? pBoxInfoItem->IsValid(VALID_BOTTOM) : pBoxInfoItem->IsValid(VALID_HORI) )
//STRIP001      aNewFrame.SetLine( (nDistBottom==0) ? pBoxItem->GetBottom() : pBoxInfoItem->GetHori(),
//STRIP001          BOX_LINE_BOTTOM );
//STRIP001
//STRIP001  if (aNewFrame == *pOldFrame)
//STRIP001  {
//STRIP001      // nothing to do
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SfxItemPoolCache aCache( pDocument->GetPool(), &aNewFrame );
//STRIP001      ApplyCacheArea( nStartRow, nEndRow, &aCache );
//STRIP001
//STRIP001 /*       ScPatternAttr* pNewPattern = (ScPatternAttr*) pPattern->Clone();
//STRIP001      pNewPattern->GetItemSet().Put( aNewFrame );
//STRIP001      SetPatternArea( nStartRow, nEndRow, pNewPattern, TRUE );
//STRIP001 */
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScAttrArray::ApplyBlockFrame( const SvxBoxItem* pLineOuter, const SvxBoxInfoItem* pLineInner,
//STRIP001                          USHORT nStartRow, USHORT nEndRow, BOOL bLeft, USHORT nDistRight )
//STRIP001 {
//STRIP001  if (nStartRow == nEndRow)
//STRIP001      ApplyFrame( pLineOuter, pLineInner, nStartRow, nEndRow, bLeft, nDistRight, TRUE, 0 );
//STRIP001  else
//STRIP001  {
//STRIP001      ApplyFrame( pLineOuter, pLineInner, nStartRow, nStartRow, bLeft, nDistRight,
//STRIP001                      TRUE, nEndRow-nStartRow );
//STRIP001
//STRIP001      if ( nEndRow > nStartRow+1 )                // innerer Teil vorhanden?
//STRIP001      {
//STRIP001          short nStartIndex;
//STRIP001          short nEndIndex;
//STRIP001          Search( nStartRow+1, nStartIndex );
//STRIP001          Search( nEndRow-1, nEndIndex );
//STRIP001          USHORT nTmpStart = nStartRow+1;
//STRIP001          USHORT nTmpEnd;
//STRIP001          for (short i=nStartIndex; i<=nEndIndex;)
//STRIP001          {
//STRIP001              nTmpEnd = Min( (USHORT)(nEndRow-1), (USHORT)(pData[i].nRow) );
//STRIP001              BOOL bChanged = ApplyFrame( pLineOuter, pLineInner, nTmpStart, nTmpEnd,
//STRIP001                                          bLeft, nDistRight, FALSE, nEndRow-nTmpEnd );
//STRIP001              nTmpStart = nTmpEnd+1;
//STRIP001              if (bChanged)
//STRIP001              {
//STRIP001                  Search(nTmpStart, i);
//STRIP001                  Search(nEndRow-1, nEndIndex);
//STRIP001              }
//STRIP001              else
//STRIP001                  i++;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      ApplyFrame( pLineOuter, pLineInner, nEndRow, nEndRow, bLeft, nDistRight, FALSE, 0 );
//STRIP001  }
//STRIP001 }


//STRIP001 long lcl_LineSize( const SvxBorderLine& rLine )
//STRIP001 {
//STRIP001  //  nur eine Linie -> halbe Breite, min. 20
//STRIP001  //  doppelte Linie -> halber Abstand + eine Linie (je min. 20)
//STRIP001
//STRIP001  long nTotal = 0;
//STRIP001  USHORT nWidth = Max( rLine.GetOutWidth(), rLine.GetInWidth() );
//STRIP001  USHORT nDist = rLine.GetDistance();
//STRIP001  if (nDist)
//STRIP001  {
//STRIP001      DBG_ASSERT( rLine.GetOutWidth() && rLine.GetInWidth(),
//STRIP001                      "Linie hat Abstand, aber nur eine Breite ???" );
//STRIP001
//STRIP001 //       nTotal += ( nDist > 40 ) ? ( nDist / 2 ) : 20;
//STRIP001      nTotal += ( nDist > 20 ) ? nDist : 20;
//STRIP001      nTotal += ( nWidth > 20 ) ? nWidth : 20;
//STRIP001  }
//STRIP001  else if (nWidth)
//STRIP001 //       nTotal += ( nWidth > 40 ) ? ( nWidth / 2 ) : 20;
//STRIP001      nTotal += ( nWidth > 20 ) ? nWidth  : 20;
//STRIP001
//STRIP001      //! auch halbieren ???
//STRIP001
//STRIP001  return nTotal;
//STRIP001 }


//STRIP001 BOOL ScAttrArray::HasLines( USHORT nRow1, USHORT nRow2, Rectangle& rSizes,
//STRIP001                              BOOL bLeft, BOOL bRight ) const
//STRIP001 {
//STRIP001  short nStartIndex;
//STRIP001  short nEndIndex;
//STRIP001  Search( nRow1, nStartIndex );
//STRIP001  Search( nRow2, nEndIndex );
//STRIP001  BOOL bFound = FALSE;
//STRIP001
//STRIP001  const SvxBoxItem* pItem = 0;
//STRIP001  const SvxBorderLine* pLine = 0;
//STRIP001  long nCmp;
//STRIP001
//STRIP001  //  oben
//STRIP001
//STRIP001  pItem = (const SvxBoxItem*) &pData[nStartIndex].pPattern->GetItem(ATTR_BORDER);
//STRIP001  pLine = pItem->GetTop();
//STRIP001  if (pLine)
//STRIP001  {
//STRIP001      nCmp = lcl_LineSize(*pLine);
//STRIP001      if ( nCmp > rSizes.Top() )
//STRIP001          rSizes.Top() = nCmp;
//STRIP001      bFound = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //  unten
//STRIP001
//STRIP001  if ( nEndIndex != nStartIndex )
//STRIP001      pItem = (const SvxBoxItem*) &pData[nEndIndex].pPattern->GetItem(ATTR_BORDER);
//STRIP001  pLine = pItem->GetBottom();
//STRIP001  if (pLine)
//STRIP001  {
//STRIP001      nCmp = lcl_LineSize(*pLine);
//STRIP001      if ( nCmp > rSizes.Bottom() )
//STRIP001          rSizes.Bottom() = nCmp;
//STRIP001      bFound = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if ( bLeft || bRight )
//STRIP001      for ( USHORT i=nStartIndex; i<=nEndIndex; i++)
//STRIP001      {
//STRIP001          pItem = (const SvxBoxItem*) &pData[i].pPattern->GetItem(ATTR_BORDER);
//STRIP001
//STRIP001          //  links
//STRIP001
//STRIP001          if (bLeft)
//STRIP001          {
//STRIP001              pLine = pItem->GetLeft();
//STRIP001              if (pLine)
//STRIP001              {
//STRIP001                  nCmp = lcl_LineSize(*pLine);
//STRIP001                  if ( nCmp > rSizes.Left() )
//STRIP001                      rSizes.Left() = nCmp;
//STRIP001                  bFound = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          //  rechts
//STRIP001
//STRIP001          if (bRight)
//STRIP001          {
//STRIP001              pLine = pItem->GetRight();
//STRIP001              if (pLine)
//STRIP001              {
//STRIP001                  nCmp = lcl_LineSize(*pLine);
//STRIP001                  if ( nCmp > rSizes.Right() )
//STRIP001                      rSizes.Right() = nCmp;
//STRIP001                  bFound = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//  Testen, ob Bereich bestimmtes Attribut enthaelt

/*N*/ BOOL ScAttrArray::HasAttrib( USHORT nRow1, USHORT nRow2, USHORT nMask ) const
/*N*/ {
/*N*/   short nStartIndex;
/*N*/   short nEndIndex;
/*N*/   Search( nRow1, nStartIndex );
/*N*/   Search( nRow2, nEndIndex );
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   for (short i=nStartIndex; i<=nEndIndex && !bFound; i++)
/*N*/   {
/*N*/       const ScPatternAttr* pPattern = pData[i].pPattern;
/*N*/       if ( nMask & HASATTR_MERGED )
/*N*/       {
/*N*/           const ScMergeAttr* pMerge =
/*N*/                   (const ScMergeAttr*) &pPattern->GetItem( ATTR_MERGE );
/*N*/           if ( pMerge->GetColMerge() > 1 || pMerge->GetRowMerge() > 1 )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & ( HASATTR_OVERLAPPED | HASATTR_NOTOVERLAPPED | HASATTR_AUTOFILTER ) )
/*N*/       {
/*N*/           const ScMergeFlagAttr* pMergeFlag =
/*N*/                   (const ScMergeFlagAttr*) &pPattern->GetItem( ATTR_MERGE_FLAG );
/*N*/           if ( (nMask & HASATTR_OVERLAPPED) && pMergeFlag->IsOverlapped() )
/*N*/               bFound = TRUE;
/*N*/           if ( (nMask & HASATTR_NOTOVERLAPPED) && !pMergeFlag->IsOverlapped() )
/*N*/               bFound = TRUE;
/*N*/           if ( (nMask & HASATTR_AUTOFILTER) && pMergeFlag->HasAutoFilter() )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_LINES )
/*N*/       {
/*N*/           const SvxBoxItem* pBox =
/*N*/                   (const SvxBoxItem*) &pPattern->GetItem( ATTR_BORDER );
/*N*/           if ( pBox->GetLeft() || pBox->GetRight() || pBox->GetTop() || pBox->GetBottom() )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_SHADOW )
/*N*/       {
/*N*/           const SvxShadowItem* pShadow =
/*N*/                   (const SvxShadowItem*) &pPattern->GetItem( ATTR_SHADOW );
/*N*/           if ( pShadow->GetLocation() != SVX_SHADOW_NONE )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_CONDITIONAL )
/*N*/       {
/*N*/           const SfxUInt32Item* pConditional =
/*N*/                   (const SfxUInt32Item*) &pPattern->GetItem( ATTR_CONDITIONAL );
/*N*/           if ( pConditional->GetValue() != 0 )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_PROTECTED )
/*N*/       {
/*N*/           const ScProtectionAttr* pProtect =
/*N*/                   (const ScProtectionAttr*) &pPattern->GetItem( ATTR_PROTECTION );
/*N*/           if ( pProtect->GetProtection() || pProtect->GetHideCell() )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_ROTATE )
/*N*/       {
/*N*/           const SfxInt32Item* pRotate =
/*N*/                   (const SfxInt32Item*) &pPattern->GetItem( ATTR_ROTATE_VALUE );
/*N*/           if ( pRotate->GetValue() != 0 )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_NEEDHEIGHT )
/*N*/       {
/*N*/           SvxCellOrientation eOrient = (SvxCellOrientation)
/*N*/               ((const SvxOrientationItem&)pPattern->GetItem( ATTR_ORIENTATION )).GetValue();
/*N*/           if (eOrient != SVX_ORIENTATION_STANDARD)
/*N*/               bFound = TRUE;
/*N*/           else if (((const SfxBoolItem&)pPattern->GetItem( ATTR_LINEBREAK )).GetValue())
/*N*/               bFound = TRUE;
/*N*/           else if ((SvxCellHorJustify)((const SvxHorJustifyItem&)pPattern->
/*N*/                       GetItem( ATTR_HOR_JUSTIFY )).GetValue() == SVX_HOR_JUSTIFY_BLOCK)
/*N*/               bFound = TRUE;
/*N*/           else if (((const SfxUInt32Item&)pPattern->GetItem( ATTR_CONDITIONAL )).GetValue())
/*N*/               bFound = TRUE;
/*N*/           else if (((const SfxInt32Item&)pPattern->GetItem( ATTR_ROTATE_VALUE )).GetValue())
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & ( HASATTR_SHADOW_RIGHT | HASATTR_SHADOW_DOWN ) )
/*N*/       {
/*N*/           const SvxShadowItem* pShadow =
/*N*/                   (const SvxShadowItem*) &pPattern->GetItem( ATTR_SHADOW );
/*N*/           SvxShadowLocation eLoc = pShadow->GetLocation();
/*N*/           if ( nMask & HASATTR_SHADOW_RIGHT )
/*N*/               if ( eLoc == SVX_SHADOW_TOPRIGHT || eLoc == SVX_SHADOW_BOTTOMRIGHT )
/*N*/                   bFound = TRUE;
/*N*/           if ( nMask & HASATTR_SHADOW_DOWN )
/*N*/               if ( eLoc == SVX_SHADOW_BOTTOMLEFT || eLoc == SVX_SHADOW_BOTTOMRIGHT )
/*N*/                   bFound = TRUE;
/*N*/       }
/*N*/       if ( nMask & HASATTR_RTL )
/*N*/       {
/*?*/           const SvxFrameDirectionItem& rDirection =
/*?*/                   (const SvxFrameDirectionItem&) pPattern->GetItem( ATTR_WRITINGDIR );
/*?*/           if ( rDirection.GetValue() == FRMDIR_HORI_RIGHT_TOP )
/*?*/               bFound = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

//  Bereich um evtl. enthaltene Zusammenfassungen erweitern
//  und evtl. MergeFlag anpassen (bRefresh)

/*N*/ BOOL ScAttrArray::ExtendMerge( USHORT nThisCol, USHORT nStartRow, USHORT nEndRow,
/*N*/                               USHORT& rPaintCol, USHORT& rPaintRow,
/*N*/                               BOOL bRefresh, BOOL bAttrs )
/*N*/ {
/*N*/   const ScPatternAttr* pPattern;
/*N*/   const ScMergeAttr* pItem;
/*N*/   short nStartIndex;
/*N*/   short nEndIndex;
/*N*/   Search( nStartRow, nStartIndex );
/*N*/   Search( nEndRow, nEndIndex );
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   for (short i=nStartIndex; i<=nEndIndex; i++)
/*N*/   {
/*N*/       pPattern = pData[i].pPattern;
/*N*/       pItem = (const ScMergeAttr*) &pPattern->GetItem( ATTR_MERGE );
/*N*/       INT16   nCountX = pItem->GetColMerge();
/*N*/       INT16   nCountY = pItem->GetRowMerge();
/*N*/       if (nCountX>1 || nCountY>1)
/*N*/       {
/*N*/           USHORT nThisRow = (i>0) ? pData[i-1].nRow+1 : 0;
/*N*/           USHORT nMergeEndCol = nThisCol + nCountX - 1;
/*N*/           USHORT nMergeEndRow = nThisRow + nCountY - 1;
/*N*/           if (nMergeEndCol > rPaintCol && nMergeEndCol <= MAXCOL)
/*N*/               rPaintCol = nMergeEndCol;
/*N*/           if (nMergeEndRow > rPaintRow && nMergeEndRow <= MAXROW)
/*N*/               rPaintRow = nMergeEndRow;
/*N*/           bFound = TRUE;
/*N*/
/*N*/           if (bAttrs)
/*N*/           {
/*N*/               const SvxShadowItem* pShadow =
/*N*/                       (const SvxShadowItem*) &pPattern->GetItem( ATTR_SHADOW );
/*N*/               SvxShadowLocation eLoc = pShadow->GetLocation();
/*N*/               if ( eLoc == SVX_SHADOW_TOPRIGHT || eLoc == SVX_SHADOW_BOTTOMRIGHT )
/*N*/                   if ( nMergeEndCol+1 > rPaintCol && nMergeEndCol < MAXCOL )
/*N*/                       rPaintCol = nMergeEndCol+1;
/*N*/               if ( eLoc == SVX_SHADOW_BOTTOMLEFT || eLoc == SVX_SHADOW_BOTTOMRIGHT )
/*?*/                   if ( nMergeEndRow+1 > rPaintRow && nMergeEndRow < MAXROW )
/*?*/                       rPaintRow = nMergeEndRow+1;
/*N*/           }
/*N*/
/*N*/           if (bRefresh)
/*N*/           {
/*?*/               if ( nMergeEndCol > nThisCol )
/*?*/                   pDocument->ApplyFlagsTab( nThisCol+1, nThisRow, nMergeEndCol, pData[i].nRow,
/*?*/                               nTab, SC_MF_HOR );
/*?*/               if ( nMergeEndRow > nThisRow )
/*?*/                   pDocument->ApplyFlagsTab( nThisCol, nThisRow+1, nThisCol, nMergeEndRow,
/*?*/                               nTab, SC_MF_VER );
/*?*/               if ( nMergeEndCol > nThisCol && nMergeEndRow > nThisRow )
/*?*/                   pDocument->ApplyFlagsTab( nThisCol+1, nThisRow+1, nMergeEndCol, nMergeEndRow,
/*?*/                               nTab, SC_MF_HOR | SC_MF_VER );
/*?*/
/*?*/               Search( nThisRow, i );                  // Daten wurden veraendert
/*?*/               Search( nStartRow, nStartIndex );
/*?*/               Search( nEndRow, nEndIndex );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }


/*N*/ BOOL ScAttrArray::RemoveAreaMerge(USHORT nStartRow, USHORT nEndRow)
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/   const ScPatternAttr* pPattern;
/*N*/   const ScMergeAttr* pItem;
/*N*/   short nIndex;
/*N*/
/*N*/   Search( nStartRow, nIndex );
/*N*/   USHORT nThisStart = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
/*N*/   if (nThisStart < nStartRow)
/*N*/       nThisStart = nStartRow;
/*N*/
/*N*/   while ( nThisStart <= nEndRow )
/*N*/   {
/*N*/       USHORT nThisEnd = pData[nIndex].nRow;
/*N*/       if (nThisEnd > nEndRow)
/*N*/           nThisEnd = nEndRow;
/*N*/
/*N*/       pPattern = pData[nIndex].pPattern;
/*N*/       pItem = (const ScMergeAttr*) &pPattern->GetItem( ATTR_MERGE );
/*N*/       INT16   nCountX = pItem->GetColMerge();
/*N*/       INT16   nCountY = pItem->GetRowMerge();
/*N*/       if (nCountX>1 || nCountY>1)
/*N*/       {
/*N*/           const ScMergeAttr* pAttr = (const ScMergeAttr*)
/*N*/                                           &pDocument->GetPool()->GetDefaultItem( ATTR_MERGE );
/*N*/           const ScMergeFlagAttr* pFlagAttr = (const ScMergeFlagAttr*)
/*N*/                                           &pDocument->GetPool()->GetDefaultItem( ATTR_MERGE_FLAG );
/*N*/
/*N*/           DBG_ASSERT( nCountY==1 || nThisStart==nThisEnd, "was'n hier los?" );
/*N*/
/*N*/           USHORT nThisCol = nCol;
/*N*/           USHORT nMergeEndCol = nThisCol + nCountX - 1;
/*N*/           USHORT nMergeEndRow = nThisEnd + nCountY - 1;
/*N*/
/*N*/           //! ApplyAttr fuer Bereiche !!!
/*N*/
/*N*/           for (USHORT nThisRow = nThisStart; nThisRow <= nThisEnd; nThisRow++)
/*N*/               pDocument->ApplyAttr( nThisCol, nThisRow, nTab, *pAttr );
/*N*/
/*N*/           ScPatternAttr*  pNewPattern = new ScPatternAttr( pDocument->GetPool() );
/*N*/           SfxItemSet*     pSet = &pNewPattern->GetItemSet();
/*N*/           pSet->Put( *pFlagAttr );
/*N*/           pDocument->ApplyPatternAreaTab( nThisCol, nThisStart, nMergeEndCol, nMergeEndRow,
/*N*/                                               nTab, *pNewPattern );
/*N*/           delete pNewPattern;
/*N*/
/*N*/           Search( nThisEnd, nIndex );                 // Daten wurden veraendert !!!
/*N*/       }
/*N*/
/*N*/       ++nIndex;
/*N*/       if ( nIndex < (short) nCount )
/*N*/           nThisStart = pData[nIndex-1].nRow+1;
/*N*/       else
/*N*/           nThisStart = MAXROW+1;      // Ende
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

            //      Bereich loeschen, aber Merge-Flags stehenlassen

/*N*/ void ScAttrArray::DeleteAreaSafe(USHORT nStartRow, USHORT nEndRow)
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 SetPatternAreaSafe( nStartRow, nEndRow, pDocument->GetDefPattern(), TRUE );
/*N*/ }


//STRIP001 void ScAttrArray::SetPatternAreaSafe( USHORT nStartRow, USHORT nEndRow,
//STRIP001                      const ScPatternAttr* pWantedPattern, BOOL bDefault )
//STRIP001 {
//STRIP001  const ScPatternAttr*    pOldPattern;
//STRIP001  const ScMergeFlagAttr*  pItem;
//STRIP001
//STRIP001  short   nIndex;
//STRIP001  USHORT  nRow;
//STRIP001  USHORT  nThisRow;
//STRIP001  BOOL    bFirstUse = TRUE;
//STRIP001
//STRIP001  Search( nStartRow, nIndex );
//STRIP001  nThisRow = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
//STRIP001  while ( nThisRow <= nEndRow )
//STRIP001  {
//STRIP001      pOldPattern = pData[nIndex].pPattern;
//STRIP001      if (pOldPattern != pWantedPattern)                          //! else-Zweig ?
//STRIP001      {
//STRIP001          if (nThisRow < nStartRow) nThisRow = nStartRow;
//STRIP001          nRow = pData[nIndex].nRow;
//STRIP001          USHORT nAttrRow = Min( (USHORT)nRow, (USHORT)nEndRow );
//STRIP001          pItem = (const ScMergeFlagAttr*) &pOldPattern->GetItem( ATTR_MERGE_FLAG );
//STRIP001
//STRIP001          if (pItem->IsOverlapped() || pItem->HasAutoFilter())
//STRIP001          {
//STRIP001              //  #108045# default-constructing a ScPatternAttr for DeleteArea doesn't work
//STRIP001              //  because it would have no cell style information.
//STRIP001              //  Instead, the document's GetDefPattern is copied. Since it is passed as
//STRIP001              //  pWantedPattern, no special treatment of default is needed here anymore.
//STRIP001              ScPatternAttr*  pNewPattern = new ScPatternAttr( *pWantedPattern );
//STRIP001              SfxItemSet*     pSet = &pNewPattern->GetItemSet();
//STRIP001              pSet->Put( *pItem );
//STRIP001              SetPatternArea( nThisRow, nAttrRow, pNewPattern, TRUE );
//STRIP001              delete pNewPattern;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if ( !bDefault )
//STRIP001              {
//STRIP001                  if (bFirstUse)
//STRIP001                      bFirstUse = FALSE;
//STRIP001                  else
//STRIP001                      pDocument->GetPool()->Put( *pWantedPattern );       // im Pool ist es schon!
//STRIP001              }
//STRIP001              SetPatternArea( nThisRow, nAttrRow, pWantedPattern );
//STRIP001          }
//STRIP001
//STRIP001          Search( nThisRow, nIndex );                 // Daten wurden veraendert !!!
//STRIP001      }
//STRIP001
//STRIP001      ++nIndex;
//STRIP001      nThisRow = pData[nIndex-1].nRow+1;
//STRIP001  }
//STRIP001 }


/*N*/ BOOL ScAttrArray::ApplyFlags( USHORT nStartRow, USHORT nEndRow, INT16 nFlags )
/*N*/ {
/*N*/   const ScPatternAttr* pOldPattern;
/*N*/
/*N*/   INT16   nOldValue;
/*N*/   short   nIndex;
/*N*/   USHORT  nRow;
/*N*/   USHORT  nThisRow;
/*N*/   BOOL    bChanged = FALSE;
/*N*/
/*N*/   Search( nStartRow, nIndex );
/*N*/   nThisRow = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
/*N*/   if (nThisRow < nStartRow) nThisRow = nStartRow;
/*N*/
/*N*/   while ( nThisRow <= nEndRow )
/*N*/   {
/*N*/       pOldPattern = pData[nIndex].pPattern;
/*N*/       nOldValue = ((const ScMergeFlagAttr*) &pOldPattern->GetItem( ATTR_MERGE_FLAG ))->GetValue();
/*N*/       if ( (nOldValue | nFlags) != nOldValue )
/*N*/       {
/*N*/           nRow = pData[nIndex].nRow;
/*N*/           USHORT nAttrRow = Min( (USHORT)nRow, (USHORT)nEndRow );
/*N*/           ScPatternAttr aNewPattern(*pOldPattern);
/*N*/           aNewPattern.GetItemSet().Put( ScMergeFlagAttr( nOldValue | nFlags ) );
/*N*/           SetPatternArea( nThisRow, nAttrRow, &aNewPattern, TRUE );
/*N*/           Search( nThisRow, nIndex );                                 // Daten wurden veraendert !!!
/*N*/           bChanged = TRUE;
/*N*/       }
/*N*/
/*N*/       ++nIndex;
/*N*/       nThisRow = pData[nIndex-1].nRow+1;
/*N*/   }
/*N*/
/*N*/   return bChanged;
/*N*/ }


//STRIP001 BOOL ScAttrArray::RemoveFlags( USHORT nStartRow, USHORT nEndRow, INT16 nFlags )
//STRIP001 {
//STRIP001  const ScPatternAttr* pOldPattern;
//STRIP001
//STRIP001  INT16   nOldValue;
//STRIP001  short   nIndex;
//STRIP001  USHORT  nRow;
//STRIP001  USHORT  nThisRow;
//STRIP001  BOOL    bChanged = FALSE;
//STRIP001
//STRIP001  Search( nStartRow, nIndex );
//STRIP001  nThisRow = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
//STRIP001  if (nThisRow < nStartRow) nThisRow = nStartRow;
//STRIP001
//STRIP001  while ( nThisRow <= nEndRow )
//STRIP001  {
//STRIP001      pOldPattern = pData[nIndex].pPattern;
//STRIP001      nOldValue = ((const ScMergeFlagAttr*) &pOldPattern->GetItem( ATTR_MERGE_FLAG ))->GetValue();
//STRIP001      if ( (nOldValue & ~nFlags) != nOldValue )
//STRIP001      {
//STRIP001          nRow = pData[nIndex].nRow;
//STRIP001          USHORT nAttrRow = Min( (USHORT)nRow, (USHORT)nEndRow );
//STRIP001          ScPatternAttr aNewPattern(*pOldPattern);
//STRIP001          aNewPattern.GetItemSet().Put( ScMergeFlagAttr( nOldValue & ~nFlags ) );
//STRIP001          SetPatternArea( nThisRow, nAttrRow, &aNewPattern, TRUE );
//STRIP001          Search( nThisRow, nIndex );                                 // Daten wurden veraendert !!!
//STRIP001          bChanged = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      ++nIndex;
//STRIP001      nThisRow = pData[nIndex-1].nRow+1;
//STRIP001  }
//STRIP001
//STRIP001  return bChanged;
//STRIP001 }


//STRIP001 void ScAttrArray::ClearItems( USHORT nStartRow, USHORT nEndRow, const USHORT* pWhich )
//STRIP001 {
//STRIP001  const ScPatternAttr* pOldPattern;
//STRIP001
//STRIP001  short   nIndex;
//STRIP001  USHORT  nRow;
//STRIP001  USHORT  nThisRow;
//STRIP001
//STRIP001  Search( nStartRow, nIndex );
//STRIP001  nThisRow = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
//STRIP001  if (nThisRow < nStartRow) nThisRow = nStartRow;
//STRIP001
//STRIP001  while ( nThisRow <= nEndRow )
//STRIP001  {
//STRIP001      pOldPattern = pData[nIndex].pPattern;
//STRIP001      if ( pOldPattern->HasItemsSet( pWhich ) )
//STRIP001      {
//STRIP001          ScPatternAttr aNewPattern(*pOldPattern);
//STRIP001          aNewPattern.ClearItems( pWhich );
//STRIP001
//STRIP001          nRow = pData[nIndex].nRow;
//STRIP001          USHORT nAttrRow = Min( (USHORT)nRow, (USHORT)nEndRow );
//STRIP001          SetPatternArea( nThisRow, nAttrRow, &aNewPattern, TRUE );
//STRIP001          Search( nThisRow, nIndex );                                 // Daten wurden veraendert !!!
//STRIP001      }
//STRIP001
//STRIP001      ++nIndex;
//STRIP001      nThisRow = pData[nIndex-1].nRow+1;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScAttrArray::ChangeIndent( USHORT nStartRow, USHORT nEndRow, BOOL bIncrement )
//STRIP001 {
//STRIP001  short nIndex;
//STRIP001  Search( nStartRow, nIndex );
//STRIP001  USHORT nThisStart = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
//STRIP001  if (nThisStart < nStartRow) nThisStart = nStartRow;
//STRIP001
//STRIP001  while ( nThisStart <= nEndRow )
//STRIP001  {
//STRIP001      const ScPatternAttr* pOldPattern = pData[nIndex].pPattern;
//STRIP001      const SfxItemSet& rOldSet = pOldPattern->GetItemSet();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001
//STRIP001      BOOL bNeedJust = ( rOldSet.GetItemState( ATTR_HOR_JUSTIFY, FALSE, &pItem ) != SFX_ITEM_SET
//STRIP001                      || ((const SvxHorJustifyItem*)pItem)->GetValue() != SVX_HOR_JUSTIFY_LEFT );
//STRIP001      USHORT nOldValue = ((const SfxUInt16Item&)rOldSet.Get( ATTR_INDENT )).GetValue();
//STRIP001      USHORT nNewValue = nOldValue;
//STRIP001      if ( bIncrement )
//STRIP001      {
//STRIP001          if ( nNewValue < SC_MAX_INDENT )
//STRIP001          {
//STRIP001              nNewValue += SC_INDENT_STEP;
//STRIP001              if ( nNewValue > SC_MAX_INDENT ) nNewValue = SC_MAX_INDENT;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if ( nNewValue > 0 )
//STRIP001          {
//STRIP001              if ( nNewValue > SC_INDENT_STEP )
//STRIP001                  nNewValue -= SC_INDENT_STEP;
//STRIP001              else
//STRIP001                  nNewValue = 0;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( bNeedJust || nNewValue != nOldValue )
//STRIP001      {
//STRIP001          USHORT nThisEnd = pData[nIndex].nRow;
//STRIP001          USHORT nAttrRow = Min( nThisEnd, nEndRow );
//STRIP001          ScPatternAttr aNewPattern(*pOldPattern);
//STRIP001          aNewPattern.GetItemSet().Put( SfxUInt16Item( ATTR_INDENT, nNewValue ) );
//STRIP001          if ( bNeedJust )
//STRIP001              aNewPattern.GetItemSet().Put(
//STRIP001                              SvxHorJustifyItem( SVX_HOR_JUSTIFY_LEFT, ATTR_HOR_JUSTIFY ) );
//STRIP001          SetPatternArea( nThisStart, nAttrRow, &aNewPattern, TRUE );
//STRIP001
//STRIP001          nThisStart = nThisEnd + 1;
//STRIP001          Search( nThisStart, nIndex );               // Daten wurden veraendert !!!
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nThisStart = pData[nIndex].nRow + 1;        // weiterzaehlen...
//STRIP001          ++nIndex;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 short ScAttrArray::GetNextUnprotected( short nRow, BOOL bUp ) const
//STRIP001 {
//STRIP001  short nRet = nRow;
//STRIP001  if (VALIDROW(nRow))
//STRIP001  {
//STRIP001      short nIndex;
//STRIP001      Search(nRow, nIndex);
//STRIP001      while (((const ScProtectionAttr&)pData[nIndex].pPattern->
//STRIP001              GetItem(ATTR_PROTECTION)).GetProtection())
//STRIP001      {
//STRIP001          if (bUp)
//STRIP001          {
//STRIP001              --nIndex;
//STRIP001              if (nIndex<0)
//STRIP001                  return -1;                  // nichts gefunden
//STRIP001              nRet = pData[nIndex].nRow;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nRet = pData[nIndex].nRow+1;
//STRIP001              ++nIndex;
//STRIP001              if (nIndex>=nCount)
//STRIP001                  return MAXROW+1;            // nichts gefunden
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


/*N*/ void ScAttrArray::FindStyleSheet( const SfxStyleSheetBase* pStyleSheet, BOOL* pUsed, BOOL bReset )
/*N*/ {
/*N*/   USHORT nStart = 0;
/*N*/   short nPos = 0;
/*N*/   while (nPos < (short) nCount)
/*N*/   {
/*N*/       USHORT nEnd = pData[nPos].nRow;
/*N*/       if (pData[nPos].pPattern->GetStyleSheet() == pStyleSheet)
/*N*/       {
/*N*/ //            for (USHORT nRow = nStart; nRow <= nEnd; nRow++)
/*N*/ //                pUsed[nRow] = TRUE;
/*N*/
/*N*/           memset( &pUsed[nStart], TRUE, nEnd-nStart+1 );
/*N*/
/*N*/           if (bReset)
/*N*/           {
/*?*/               ScPatternAttr* pNewPattern = new ScPatternAttr(*pData[nPos].pPattern);
/*?*/               pDocument->GetPool()->Remove(*pData[nPos].pPattern);
/*?*/               pNewPattern->SetStyleSheet( (ScStyleSheet*)
/*?*/                   pDocument->GetStyleSheetPool()->
/*?*/                       Find( ScGlobal::GetRscString(STR_STYLENAME_STANDARD),
/*?*/                             SFX_STYLE_FAMILY_PARA,
/*?*/                             SFXSTYLEBIT_AUTO | SCSTYLEBIT_STANDARD ) );
/*?*/               pData[nPos].pPattern = (const ScPatternAttr*)
/*?*/                                           &pDocument->GetPool()->Put(*pNewPattern);
/*?*/               delete pNewPattern;
/*?*/
/*?*/               if (Concat(nPos))
/*?*/               {
/*?*/                   Search(nStart, nPos);
/*?*/                   --nPos;                         // wegen ++ am Ende
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/       nStart = nEnd + 1;
/*N*/       ++nPos;
/*N*/   }
/*N*/ }


/*N*/ BOOL ScAttrArray::IsStyleSheetUsed( const ScStyleSheet& rStyle,
/*N*/         BOOL bGatherAllStyles ) const
/*N*/ {
/*N*/   BOOL    bIsUsed = FALSE;
/*N*/   short   nPos    = 0;
/*N*/
/*N*/   while ( nPos < (short)nCount )
/*N*/   {
/*?*/         const ScStyleSheet* pStyle = pData[nPos].pPattern->GetStyleSheet();
/*?*/         if ( pStyle )
/*?*/         {
/*?*/             pStyle->SetUsage( ScStyleSheet::USED );
/*?*/             if ( pStyle == &rStyle )
/*?*/             {
/*?*/                 if ( !bGatherAllStyles )
/*?*/                     return TRUE;
/*?*/                 bIsUsed = TRUE;
/*?*/             }
/*?*/         }
/*N*/       nPos++;
/*N*/   }
/*N*/
/*N*/   return bIsUsed;
/*N*/ }


/*N*/ BOOL ScAttrArray::IsEmpty() const
/*N*/ {
/*N*/   if (nCount == 1)
/*N*/   {
/*N*/       if ( pData[0].pPattern != pDocument->GetDefPattern() )
/*N*/           return FALSE;
/*N*/       else
/*N*/           return TRUE;
/*N*/   }
/*N*/   else
/*N*/       return FALSE;
/*N*/ }


//STRIP001 USHORT ScAttrArray::GetFirstEntryPos() const
//STRIP001 {
//STRIP001  DBG_ASSERT( nCount, "nCount = 0" );
//STRIP001
//STRIP001  if ( pData[0].pPattern != pDocument->GetDefPattern() )
//STRIP001      return 0;
//STRIP001  else
//STRIP001  {
//STRIP001      if (nCount==1)
//STRIP001          return 0;                               // leer
//STRIP001      else
//STRIP001          return pData[0].nRow + 1;
//STRIP001  }
//STRIP001 }


//STRIP001 USHORT ScAttrArray::GetLastEntryPos( BOOL bIncludeBottom ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( nCount, "nCount == 0" );
//STRIP001
//STRIP001  if (bIncludeBottom)
//STRIP001      bIncludeBottom = ( pData[nCount-1].pPattern != pDocument->GetDefPattern() );
//STRIP001
//STRIP001  if (bIncludeBottom)
//STRIP001      return MAXROW;
//STRIP001  else
//STRIP001  {
//STRIP001      if (nCount<=1)
//STRIP001          return 0;                               // leer
//STRIP001      else
//STRIP001          return pData[nCount-2].nRow;
//STRIP001  }
//STRIP001 }


/*N*/ BOOL ScAttrArray::HasVisibleAttr( USHORT& rFirstRow, USHORT& rLastRow, BOOL bSkipFirst ) const
/*N*/ {
/*N*/   DBG_ASSERT( nCount, "nCount == 0" );
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/   USHORT nStart = 0;
/*N*/
/*N*/   if ( bSkipFirst )                           // Anfang ueberspringen, wenn >1 Zeile
/*N*/   {
/*N*/       USHORT nVisStart = 1;
/*N*/       while ( nVisStart < nCount &&
/*N*/               pData[nVisStart].pPattern->IsVisibleEqual(*pData[nVisStart-1].pPattern) )
/*N*/           ++nVisStart;
/*N*/       if ( nVisStart >= nCount || pData[nVisStart-1].nRow > 0 )   // mehr als 1 Zeile?
/*N*/           nStart = nVisStart;
/*N*/   }
/*N*/
/*N*/   USHORT nVisCount = nCount-1;                // am Ende zusammengehoerende weglassen
/*N*/   while ( nVisCount > nStart &&
/*N*/           pData[nVisCount].pPattern->IsVisibleEqual(*pData[nVisCount-1].pPattern) )
/*N*/       --nVisCount;
/*N*/
/*N*/   while ( nStart < nVisCount && !bFound )
/*N*/   {
/*N*/       if ( pData[nStart].pPattern->IsVisible() )
/*N*/       {
/*N*/           rFirstRow = nStart ? ( pData[nStart-1].nRow + 1 ) : 0;
/*N*/           rLastRow = pData[nStart].nRow;
/*N*/           bFound = TRUE;
/*N*/       }
/*N*/       else
/*N*/           ++nStart;
/*N*/   }
/*N*/
/*N*/   if (!bFound)
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bEnd = FALSE;
/*N*/   USHORT nPos = nVisCount;
/*N*/   while ( nPos > nStart && !bEnd )
/*N*/   {
/*N*/       --nPos;
/*N*/       if ( pData[nPos].pPattern->IsVisible() )
/*N*/       {
/*N*/           rLastRow = pData[nPos].nRow;
/*N*/           bEnd = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }


//STRIP001 BOOL ScAttrArray::HasVisibleAttrIn( USHORT nStartRow, USHORT nEndRow ) const
//STRIP001 {
//STRIP001  short nIndex;
//STRIP001  Search( nStartRow, nIndex );
//STRIP001  USHORT nThisStart = nStartRow;
//STRIP001  BOOL bFound = FALSE;
//STRIP001  while ( nIndex < nCount && nThisStart <= nEndRow && !bFound )
//STRIP001  {
//STRIP001      if ( pData[nIndex].pPattern->IsVisible() )
//STRIP001          bFound = TRUE;
//STRIP001
//STRIP001      nThisStart = pData[nIndex].nRow + 1;
//STRIP001      ++nIndex;
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }


/*N*/ BOOL ScAttrArray::IsVisibleEqual( const ScAttrArray& rOther,
/*N*/                                   USHORT nStartRow, USHORT nEndRow ) const
/*N*/ {
/*N*/   BOOL bEqual = TRUE;
/*N*/   short nThisPos = 0;
/*N*/   short nOtherPos = 0;
/*N*/   if ( nStartRow )
/*N*/   {
/*N*/       Search( nStartRow, nThisPos );
/*N*/       rOther.Search( nStartRow, nOtherPos );
/*N*/   }
/*N*/
/*N*/   while ( nThisPos<nCount && nOtherPos<rOther.nCount && bEqual )
/*N*/   {
/*N*/       USHORT nThisRow = pData[nThisPos].nRow;
/*N*/       USHORT nOtherRow = rOther.pData[nOtherPos].nRow;
/*N*/       const ScPatternAttr* pThisPattern = pData[nThisPos].pPattern;
/*N*/       const ScPatternAttr* pOtherPattern = rOther.pData[nOtherPos].pPattern;
/*N*/       bEqual = ( pThisPattern == pOtherPattern ||
/*N*/                   pThisPattern->IsVisibleEqual(*pOtherPattern) );
/*N*/
/*N*/       if ( nThisRow >= nOtherRow )
/*N*/       {
/*N*/           if ( nOtherRow >= nEndRow ) break;
/*N*/           ++nOtherPos;
/*N*/       }
/*N*/       if ( nThisRow <= nOtherRow )
/*N*/       {
/*N*/           if ( nThisRow >= nEndRow ) break;
/*N*/           ++nThisPos;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bEqual;
/*N*/ }


/*N*/ BOOL ScAttrArray::IsAllEqual( const ScAttrArray& rOther, USHORT nStartRow, USHORT nEndRow ) const
/*N*/ {
/*N*/   //! mit IsVisibleEqual zusammenfassen?
/*N*/
/*N*/   BOOL bEqual = TRUE;
/*N*/   short nThisPos = 0;
/*N*/   short nOtherPos = 0;
/*N*/   if ( nStartRow )
/*N*/   {
/*?*/       Search( nStartRow, nThisPos );
/*?*/       rOther.Search( nStartRow, nOtherPos );
/*N*/   }
/*N*/
/*N*/   while ( nThisPos<nCount && nOtherPos<rOther.nCount && bEqual )
/*N*/   {
/*N*/       USHORT nThisRow = pData[nThisPos].nRow;
/*N*/       USHORT nOtherRow = rOther.pData[nOtherPos].nRow;
/*N*/       const ScPatternAttr* pThisPattern = pData[nThisPos].pPattern;
/*N*/       const ScPatternAttr* pOtherPattern = rOther.pData[nOtherPos].pPattern;
/*N*/       bEqual = ( pThisPattern == pOtherPattern );
/*N*/
/*N*/       if ( nThisRow >= nOtherRow )
/*N*/       {
/*N*/           if ( nOtherRow >= nEndRow ) break;
/*N*/           ++nOtherPos;
/*N*/       }
/*N*/       if ( nThisRow <= nOtherRow )
/*N*/       {
/*N*/           if ( nThisRow >= nEndRow ) break;
/*N*/           ++nThisPos;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bEqual;
/*N*/ }


//STRIP001 BOOL ScAttrArray::TestInsertCol( USHORT nStartRow, USHORT nEndRow) const
//STRIP001 {
//STRIP001  //  horizontal zusammengefasste duerfen nicht herausgeschoben werden
//STRIP001  //  (ob die ganze Zusammenfassung betroffen ist, ist hier nicht zu erkennen)
//STRIP001
//STRIP001  BOOL bTest = TRUE;
//STRIP001  if (!IsEmpty())
//STRIP001  {
//STRIP001      short nIndex = 0;
//STRIP001      if ( nStartRow )
//STRIP001          Search( nStartRow, nIndex );
//STRIP001
//STRIP001      for ( ; nIndex < nCount; nIndex++ )
//STRIP001      {
//STRIP001          if ( ((const ScMergeFlagAttr&)pData[nIndex].pPattern->
//STRIP001                      GetItem(ATTR_MERGE_FLAG)).IsHorOverlapped() )
//STRIP001          {
//STRIP001              bTest = FALSE;                      // darf nicht herausgeschoben werden
//STRIP001              break;
//STRIP001          }
//STRIP001          if ( pData[nIndex].nRow >= nEndRow )    // Ende des Bereichs
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  return bTest;
//STRIP001 }


//STRIP001 BOOL ScAttrArray::TestInsertRow( USHORT nSize ) const
//STRIP001 {
//STRIP001  //  wenn die erste herausgeschobene Zeile vertikal ueberlappt ist,
//STRIP001  //  wuerde eine kaputte Zusammenfassung uebrigbleiben
//STRIP001
//STRIP001  if (pData)
//STRIP001  {
//STRIP001      //  MAXROW + 1 - nSize  = erste herausgeschobene Zeile
//STRIP001
//STRIP001      USHORT nFirstLost = nCount-1;
//STRIP001      while ( nFirstLost && pData[nFirstLost-1].nRow >= MAXROW + 1 - nSize )
//STRIP001          --nFirstLost;
//STRIP001
//STRIP001      if ( ((const ScMergeFlagAttr&)pData[nFirstLost].pPattern->
//STRIP001                          GetItem(ATTR_MERGE_FLAG)).IsVerOverlapped() )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 void ScAttrArray::InsertRow( USHORT nStartRow, USHORT nSize )
//STRIP001 {
//STRIP001  if (!pData)
//STRIP001      return;
//STRIP001
//STRIP001  USHORT nSearch = nStartRow ? nStartRow - 1 : 0;     // Vorgaenger erweitern
//STRIP001  short nIndex;
//STRIP001  Search( nSearch, nIndex );
//STRIP001
//STRIP001  //  ein gesetztes ScMergeAttr darf nicht ausgedehnt werden
//STRIP001  //  (darum hinterher wieder loeschen)
//STRIP001
//STRIP001  BOOL bDoMerge = ((const ScMergeAttr&) pData[nIndex].pPattern->GetItem(ATTR_MERGE)).IsMerged();
//STRIP001
//STRIP001  USHORT nRemove = 0;
//STRIP001  USHORT i;
//STRIP001  for (i = nIndex; i < nCount-1; i++)
//STRIP001  {
//STRIP001      USHORT nNew = pData[i].nRow + nSize;
//STRIP001      if ( nNew >= MAXROW )                   // Ende erreicht ?
//STRIP001      {
//STRIP001          nNew = MAXROW;
//STRIP001          if (!nRemove)
//STRIP001              nRemove = i+1;                  // folgende loeschen
//STRIP001      }
//STRIP001      pData[i].nRow = nNew;
//STRIP001  }
//STRIP001
//STRIP001  //  muessen Eintraege am Ende geloescht werden?
//STRIP001
//STRIP001  if (nRemove && nRemove < nCount)
//STRIP001      DeleteRange( nRemove, nCount-1 );
//STRIP001
//STRIP001  if (bDoMerge)           // ausgedehntes ScMergeAttr wieder reparieren
//STRIP001  {
//STRIP001          //! ApplyAttr fuer Bereiche !!!
//STRIP001
//STRIP001      const SfxPoolItem& rDef = pDocument->GetPool()->GetDefaultItem( ATTR_MERGE );
//STRIP001      for (i=0; i<nSize; i++)
//STRIP001          pDocument->ApplyAttr( nCol, nStartRow+i, nTab, rDef );
//STRIP001
//STRIP001      //  im eingefuegten Bereich ist nichts zusammengefasst
//STRIP001  }
//STRIP001
//STRIP001  //  Flags nicht duplizieren
//STRIP001  //! direkt am Pattern testen ??
//STRIP001  RemoveFlags( nStartRow, nStartRow+nSize-1, SC_MF_HOR | SC_MF_VER | SC_MF_AUTO );
//STRIP001 }


//STRIP001 void ScAttrArray::DeleteRow( USHORT nStartRow, USHORT nSize )
//STRIP001 {
//STRIP001  if (pData)
//STRIP001  {
//STRIP001      BOOL bFirst=TRUE;
//STRIP001      USHORT nStartIndex;
//STRIP001      USHORT nEndIndex;
//STRIP001      for (USHORT i = 0; i < nCount-1; i++)
//STRIP001          if (pData[i].nRow >= nStartRow && pData[i].nRow <= nStartRow+nSize-1)
//STRIP001          {
//STRIP001              if (bFirst)
//STRIP001              {
//STRIP001                  nStartIndex = i;
//STRIP001                  bFirst = FALSE;
//STRIP001              }
//STRIP001              nEndIndex = i;
//STRIP001          }
//STRIP001      if (!bFirst)
//STRIP001      {
//STRIP001          USHORT nStart;
//STRIP001          if (nStartIndex==0)
//STRIP001              nStart = 0;
//STRIP001          else
//STRIP001              nStart = pData[nStartIndex-1].nRow + 1;
//STRIP001
//STRIP001          if (nStart < nStartRow)
//STRIP001          {
//STRIP001              pData[nStartIndex].nRow = nStartRow - 1;
//STRIP001              ++nStartIndex;
//STRIP001          }
//STRIP001          if (nEndIndex >= nStartIndex)
//STRIP001          {
//STRIP001              DeleteRange( nStartIndex, nEndIndex );
//STRIP001              if (nStartIndex > 0)
//STRIP001                  if ( pData[nStartIndex-1].pPattern == pData[nStartIndex].pPattern )
//STRIP001                      DeleteRange( nStartIndex-1, nStartIndex-1 );
//STRIP001          }
//STRIP001      }
//STRIP001      for (i = 0; i < nCount-1; i++)
//STRIP001          if (pData[i].nRow >= nStartRow)
//STRIP001              pData[i].nRow -= nSize;
//STRIP001
//STRIP001 //       unten nicht Default-Pattern nachschieben, um Druckbereiche erkennen zu koennen
//STRIP001 //       stattdessen nur Merge-Flags loeschen
//STRIP001
//STRIP001      RemoveFlags( MAXROW-nSize+1, MAXROW, SC_MF_HOR | SC_MF_VER | SC_MF_AUTO );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScAttrArray::DeleteRange( USHORT nStartIndex, USHORT nEndIndex )
//STRIP001 {
//STRIP001  ScDocumentPool* pDocPool = pDocument->GetPool();
//STRIP001  for (USHORT i = nStartIndex; i <= nEndIndex; i++)
//STRIP001      pDocPool->Remove(*pData[i].pPattern);
//STRIP001
//STRIP001  memmove( &pData[nStartIndex], &pData[nEndIndex + 1], (nCount - nEndIndex - 1) * sizeof(ScAttrEntry) );
//STRIP001  nCount -= nEndIndex-nStartIndex+1;
//STRIP001 }


/*N*/ void ScAttrArray::DeleteArea(USHORT nStartRow, USHORT nEndRow)
/*N*/ {
/*N*/   RemoveAreaMerge( nStartRow, nEndRow );          // von zusammengefassten auch die Flags loeschen
/*N*/
/*N*/   if ( !HasAttrib( nStartRow, nEndRow, HASATTR_OVERLAPPED | HASATTR_AUTOFILTER) )
/*N*/       SetPatternArea( nStartRow, nEndRow, pDocument->GetDefPattern() );
/*N*/   else
/*?*/       DeleteAreaSafe( nStartRow, nEndRow );       // Merge-Flags stehenlassen
/*N*/ }


/*N*/ void ScAttrArray::DeleteHardAttr(USHORT nStartRow, USHORT nEndRow)
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  const ScPatternAttr* pDefPattern = pDocument->GetDefPattern();
//STRIP001  const ScPatternAttr* pOldPattern;
//STRIP001
//STRIP001  short   nIndex;
//STRIP001  USHORT  nRow;
//STRIP001  USHORT  nThisRow;
//STRIP001
//STRIP001  Search( nStartRow, nIndex );
//STRIP001  nThisRow = (nIndex>0) ? pData[nIndex-1].nRow+1 : 0;
//STRIP001  if (nThisRow < nStartRow) nThisRow = nStartRow;
//STRIP001
//STRIP001  while ( nThisRow <= nEndRow )
//STRIP001  {
//STRIP001      pOldPattern = pData[nIndex].pPattern;
//STRIP001
//STRIP001      if ( pOldPattern->GetItemSet().Count() )        // harte Attribute ?
//STRIP001      {
//STRIP001          nRow = pData[nIndex].nRow;
//STRIP001          USHORT nAttrRow = Min( (USHORT)nRow, (USHORT)nEndRow );
//STRIP001
//STRIP001          ScPatternAttr aNewPattern(*pOldPattern);
//STRIP001          SfxItemSet& rSet = aNewPattern.GetItemSet();
//STRIP001          for (USHORT nId = ATTR_PATTERN_START; nId <= ATTR_PATTERN_END; nId++)
//STRIP001              if (nId != ATTR_MERGE && nId != ATTR_MERGE_FLAG)
//STRIP001                  rSet.ClearItem(nId);
//STRIP001
//STRIP001          if ( aNewPattern == *pDefPattern )
//STRIP001              SetPatternArea( nThisRow, nAttrRow, pDefPattern, FALSE );
//STRIP001          else
//STRIP001              SetPatternArea( nThisRow, nAttrRow, &aNewPattern, TRUE );
//STRIP001
//STRIP001          Search( nThisRow, nIndex );                                 // Daten wurden veraendert !!!
//STRIP001      }
//STRIP001
//STRIP001      ++nIndex;
//STRIP001      nThisRow = pData[nIndex-1].nRow+1;
//STRIP001  }
/*N*/ }

        // Verschieben innerhalb eines Dokuments

//STRIP001 void ScAttrArray::MoveTo(USHORT nStartRow, USHORT nEndRow, ScAttrArray& rAttrArray)
//STRIP001 {
//STRIP001  USHORT nStart = nStartRow;
//STRIP001  for (USHORT i = 0; i < nCount; i++)
//STRIP001  {
//STRIP001      if ((pData[i].nRow >= nStartRow) && ((i==0) ? TRUE : pData[i-1].nRow < nEndRow))
//STRIP001      {
//STRIP001          //  Kopieren (bPutToPool=TRUE)
//STRIP001          rAttrArray.SetPatternArea( nStart, Min( (USHORT)pData[i].nRow, (USHORT)nEndRow ),
//STRIP001                                      pData[i].pPattern, TRUE );
//STRIP001      }
//STRIP001      nStart = Max( (USHORT)nStart, (USHORT)(pData[i].nRow + 1) );
//STRIP001  }
//STRIP001  DeleteArea(nStartRow, nEndRow);
//STRIP001 }


        // Kopieren zwischen Dokumenten (Clipboard)

/*N*/ void ScAttrArray::CopyArea( USHORT nStartRow, USHORT nEndRow, short nDy, ScAttrArray& rAttrArray,
/*N*/                               INT16 nStripFlags )
/*N*/ {
/*N*/   nStartRow -= nDy;       // Source
/*N*/   nEndRow -= nDy;
/*N*/
/*N*/   USHORT nDestStart = Max((short)((short)nStartRow + nDy), (short) 0);
/*N*/   USHORT nDestEnd = Min((short)((short)nEndRow + nDy), (short) MAXROW);
/*N*/
/*N*/   ScDocumentPool* pSourceDocPool = pDocument->GetPool();
/*N*/   ScDocumentPool* pDestDocPool = rAttrArray.pDocument->GetPool();
/*N*/   BOOL bSamePool = (pSourceDocPool==pDestDocPool);
/*N*/
/*N*/   for (USHORT i = 0; (i < nCount) && (nDestStart <= nDestEnd); i++)
/*N*/   {
/*N*/       if (pData[i].nRow >= nStartRow)
/*N*/       {
/*N*/           const ScPatternAttr* pOldPattern = pData[i].pPattern;
/*N*/           const ScPatternAttr* pNewPattern;
/*N*/
/*N*/           if (IsDefaultItem( pOldPattern ))
/*N*/           {
/*N*/               //  am Default muss nichts veraendert werden
/*N*/
/*N*/               pNewPattern = (const ScPatternAttr*)
/*N*/                               &pDestDocPool->GetDefaultItem( ATTR_PATTERN );
/*N*/           }
/*N*/           else if ( nStripFlags )
/*N*/           {
/*?*/               ScPatternAttr* pTmpPattern = new ScPatternAttr( *pOldPattern );
/*?*/               INT16 nNewFlags = 0;
/*?*/               if ( nStripFlags != SC_MF_ALL )
/*?*/                   nNewFlags = ((const ScMergeFlagAttr&)pTmpPattern->GetItem(ATTR_MERGE_FLAG)).
/*?*/                               GetValue() & ~nStripFlags;
/*?*/
/*?*/               if ( nNewFlags )
/*?*/                   pTmpPattern->GetItemSet().Put( ScMergeFlagAttr( nNewFlags ) );
/*?*/               else
/*?*/                   pTmpPattern->GetItemSet().ClearItem( ATTR_MERGE_FLAG );
/*?*/
/*?*/               if (bSamePool)
/*?*/                   pNewPattern = (ScPatternAttr*) &pDestDocPool->Put(*pTmpPattern);
/*?*/               else
/*?*/                   pNewPattern = pTmpPattern->PutInPool( rAttrArray.pDocument, pDocument );
/*?*/               delete pTmpPattern;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               if (bSamePool)
/*N*/                   pNewPattern = (ScPatternAttr*) &pDestDocPool->Put(*pOldPattern);
/*N*/               else
/*N*/                   pNewPattern = pOldPattern->PutInPool( rAttrArray.pDocument, pDocument );
/*N*/           }
/*N*/
/*N*/           rAttrArray.SetPatternArea(nDestStart,
/*N*/                           Min((USHORT)(pData[i].nRow + nDy), nDestEnd), pNewPattern);
/*N*/       }
/*N*/
/*N*/       // when pasting from clipboard and skipping filtered rows, the adjusted end position
/*N*/       // can be negative
/*N*/       nDestStart = Max((short)nDestStart, (short)(pData[i].nRow + nDy + 1));
/*N*/   }
/*N*/ }

        // Flags stehenlassen
        //! mit CopyArea zusammenfassen !!!

//STRIP001 void ScAttrArray::CopyAreaSafe( USHORT nStartRow, USHORT nEndRow, short nDy, ScAttrArray& rAttrArray )
//STRIP001 {
//STRIP001  nStartRow -= nDy;       // Source
//STRIP001  nEndRow -= nDy;
//STRIP001
//STRIP001  USHORT nDestStart = Max((short)((short)nStartRow + nDy), (short) 0);
//STRIP001  USHORT nDestEnd = Min((short)((short)nEndRow + nDy), (short) MAXROW);
//STRIP001
//STRIP001  if ( !rAttrArray.HasAttrib( nDestStart, nDestEnd, HASATTR_OVERLAPPED ) )
//STRIP001  {
//STRIP001      CopyArea( nStartRow+nDy, nEndRow+nDy, nDy, rAttrArray );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  ScDocumentPool* pSourceDocPool = pDocument->GetPool();
//STRIP001  ScDocumentPool* pDestDocPool = rAttrArray.pDocument->GetPool();
//STRIP001  BOOL bSamePool = (pSourceDocPool==pDestDocPool);
//STRIP001
//STRIP001  for (USHORT i = 0; (i < nCount) && (nDestStart <= nDestEnd); i++)
//STRIP001  {
//STRIP001      if (pData[i].nRow >= nStartRow)
//STRIP001      {
//STRIP001          const ScPatternAttr* pOldPattern = pData[i].pPattern;
//STRIP001          const ScPatternAttr* pNewPattern;
//STRIP001
//STRIP001          if (bSamePool)
//STRIP001              pNewPattern = (ScPatternAttr*) &pDestDocPool->Put(*pOldPattern);
//STRIP001          else
//STRIP001              pNewPattern = pOldPattern->PutInPool( rAttrArray.pDocument, pDocument );
//STRIP001
//STRIP001          rAttrArray.SetPatternAreaSafe(nDestStart,
//STRIP001                          Min((USHORT)(pData[i].nRow + nDy), nDestEnd), pNewPattern, FALSE);
//STRIP001      }
//STRIP001
//STRIP001      // when pasting from clipboard and skipping filtered rows, the adjusted end position
//STRIP001      // can be negative
//STRIP001      nDestStart = Max((short)nDestStart, (short)(pData[i].nRow + nDy + 1));
//STRIP001  }
//STRIP001 }


//STRIP001 short ScAttrArray::SearchStyle( short nRow, const ScStyleSheet* pSearchStyle,
//STRIP001                                  BOOL bUp, ScMarkArray* pMarkArray )
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001
//STRIP001  if (pMarkArray)
//STRIP001  {
//STRIP001      nRow = pMarkArray->GetNextMarked( nRow, bUp );
//STRIP001      if (nRow<0 || nRow>MAXROW)
//STRIP001          return nRow;
//STRIP001  }
//STRIP001
//STRIP001  short nIndex;
//STRIP001  Search(nRow, nIndex);
//STRIP001  const ScPatternAttr* pPattern = pData[nIndex].pPattern;
//STRIP001
//STRIP001  while (nIndex>=0 && nIndex<(short)nCount && !bFound)
//STRIP001  {
//STRIP001      if (pPattern->GetStyleSheet() == pSearchStyle)
//STRIP001      {
//STRIP001          if (pMarkArray)
//STRIP001          {
//STRIP001              nRow = pMarkArray->GetNextMarked( nRow, bUp );
//STRIP001              short nStart = nIndex ? pData[nIndex-1].nRow+1 : 0;
//STRIP001              if (nRow >= nStart && nRow <= (short) pData[nIndex].nRow)
//STRIP001                  bFound = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001              bFound = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if (!bFound)
//STRIP001      {
//STRIP001          if (bUp)
//STRIP001          {
//STRIP001              --nIndex;
//STRIP001              if (nIndex>=0)
//STRIP001              {
//STRIP001                  nRow = pData[nIndex].nRow;
//STRIP001                  pPattern = pData[nIndex].pPattern;
//STRIP001              }
//STRIP001              else
//STRIP001                  nRow = -1;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nRow = pData[nIndex].nRow+1;
//STRIP001              ++nIndex;
//STRIP001              if (nIndex<(short)nCount)
//STRIP001                  pPattern = pData[nIndex].pPattern;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  DBG_ASSERT( bFound || nRow<0 || nRow>MAXROW, "interner Fehler in ScAttrArray::SearchStyle" );
//STRIP001
//STRIP001  return nRow;
//STRIP001 }


//STRIP001 BOOL ScAttrArray::SearchStyleRange( short& rRow, short& rEndRow,
//STRIP001                      const ScStyleSheet* pSearchStyle, BOOL bUp, ScMarkArray* pMarkArray )
//STRIP001 {
//STRIP001  short nStartRow = SearchStyle( rRow, pSearchStyle, bUp, pMarkArray );
//STRIP001  if (VALIDROW(nStartRow))
//STRIP001  {
//STRIP001      short nIndex;
//STRIP001      Search(nStartRow,nIndex);
//STRIP001
//STRIP001      rRow = nStartRow;
//STRIP001      if (bUp)
//STRIP001      {
//STRIP001          if (nIndex>0)
//STRIP001              rEndRow = pData[nIndex-1].nRow + 1;
//STRIP001          else
//STRIP001              rEndRow = 0;
//STRIP001          if (pMarkArray)
//STRIP001          {
//STRIP001              short nMarkEnd = pMarkArray->GetMarkEnd( nStartRow, TRUE );
//STRIP001              if (nMarkEnd>rEndRow)
//STRIP001                  rEndRow = nMarkEnd;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rEndRow = pData[nIndex].nRow;
//STRIP001          if (pMarkArray)
//STRIP001          {
//STRIP001              short nMarkEnd = pMarkArray->GetMarkEnd( nStartRow, FALSE );
//STRIP001              if (nMarkEnd<rEndRow)
//STRIP001                  rEndRow = nMarkEnd;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

//------------------------------------------------------------------------
//
//                          Laden / Speichern
//


/*N*/ void ScAttrArray::Save( SvStream& rStream ) const
/*N*/ {
/*N*/   ScWriteHeader aHdr( rStream, 8 );
/*N*/
/*N*/   ScDocumentPool* pDocPool = pDocument->GetPool();
/*N*/
/*N*/   USHORT nSaveCount = nCount;
/*N*/   USHORT nSaveMaxRow = pDocument->GetSrcMaxRow();
/*N*/   if ( nSaveMaxRow != MAXROW )
/*N*/   {
/*?*/       if ( nSaveCount > 1 && pData[nSaveCount-2].nRow >= nSaveMaxRow )
/*?*/       {
/*?*/           pDocument->SetLostData();           // Warnung ausgeben
/*?*/           do
/*?*/               --nSaveCount;
/*?*/           while ( nSaveCount > 1 && pData[nSaveCount-2].nRow >= nSaveMaxRow );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   rStream << nSaveCount;
/*N*/
/*N*/   const SfxPoolItem* pItem;
/*N*/   for (USHORT i=0; i<nSaveCount; i++)
/*N*/   {
/*N*/       rStream << Min( pData[i].nRow, nSaveMaxRow );
/*N*/
/*N*/       const ScPatternAttr* pPattern = pData[i].pPattern;
/*N*/       pDocPool->StoreSurrogate( rStream, pPattern );
/*N*/
/*N*/       //  FALSE, weil ATTR_CONDITIONAL (noch) nicht in Vorlagen:
/*N*/       if (pPattern->GetItemSet().GetItemState(ATTR_CONDITIONAL,FALSE,&pItem) == SFX_ITEM_SET)
/*N*/           pDocument->SetConditionalUsed( ((const SfxUInt32Item*)pItem)->GetValue() );
/*N*/
/*N*/       if (pPattern->GetItemSet().GetItemState(ATTR_VALIDDATA,FALSE,&pItem) == SFX_ITEM_SET)
/*N*/           pDocument->SetValidationUsed( ((const SfxUInt32Item*)pItem)->GetValue() );
/*N*/   }
/*N*/ }


/*N*/ void ScAttrArray::Load( SvStream& rStream )
/*N*/ {
/*N*/   ScDocumentPool* pDocPool = pDocument->GetPool();
/*N*/
/*N*/   ScReadHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nNewCount;
/*N*/   rStream >> nNewCount;
/*N*/   if ( nNewCount > MAXROW+1 )                     // wuerde das Array zu gross?
/*N*/   {
/*?*/       pDocument->SetLostData();
/*?*/       rStream.SetError( SVSTREAM_FILEFORMAT_ERROR );
/*?*/       return;
/*N*/   }
/*N*/
/*N*/   Reset( pDocument->GetDefPattern(), FALSE );     // loeschen
/*N*/   pData = new ScAttrEntry[nNewCount];             // neu anlegen
/*N*/   for (USHORT i=0; i<nNewCount; i++)
/*N*/   {
/*N*/       rStream >> pData[i].nRow;
/*N*/
/*N*/       USHORT nWhich = ATTR_PATTERN;
/*N*/       const ScPatternAttr* pNewPattern = (const ScPatternAttr*)
/*N*/                               pDocPool->LoadSurrogate( rStream, nWhich, ATTR_PATTERN );
/*N*/       if (!pNewPattern)
/*N*/       {
/*?*/           // da is was schiefgelaufen
/*?*/           DBG_ERROR("ScAttrArray::Load: Surrogat nicht im Pool");
/*?*/           pNewPattern = pDocument->GetDefPattern();
/*N*/       }
/*N*/       ScDocumentPool::CheckRef( *pNewPattern );
/*N*/       pData[i].pPattern = pNewPattern;
/*N*/
/*N*/       // LoadSurrogate erhoeht auch die Ref
/*N*/   }
/*N*/     nCount = nLimit = nNewCount;
/*N*/
/*N*/   if ( nCount > 1 && pData[nCount-2].nRow >= MAXROW ) // faengt ein Attribut hinter MAXROW an?
/*N*/   {
/*?*/       pDocument->SetLostData();
/*?*/       rStream.SetError( SVSTREAM_FILEFORMAT_ERROR );
/*?*/       return;
/*N*/   }
/*N*/
/*N*/   if ( pDocument->GetSrcMaxRow() != MAXROW )          // Ende anpassen?
/*N*/   {
/*N*/       //  Ende immer auf MAXROW umsetzen (nur auf 32 Bit)
/*N*/
/*N*/       DBG_ASSERT( pData[nCount-1].nRow == pDocument->GetSrcMaxRow(), "Attribut-Ende ?!?" );
/*N*/       pData[nCount-1].nRow = MAXROW;
/*N*/   }
/*N*/ }


/*N*/ void ScAttrArray::ConvertFontsAfterLoad()
/*N*/ {
/*N*/     ScFontToSubsFontConverter_AutoPtr xFontConverter;
/*N*/     const ULONG nFlags = FONTTOSUBSFONT_IMPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS;
/*N*/     short   nIndex = 0;
/*N*/     USHORT  nThisRow = 0;
/*N*/
/*N*/     while ( nThisRow <= MAXROW )
/*N*/   {
/*N*/         const ScPatternAttr* pOldPattern = pData[nIndex].pPattern;
/*N*/         const SfxPoolItem* pItem;
/*N*/         if( pOldPattern->GetItemSet().GetItemState( ATTR_FONT, FALSE, &pItem ) == SFX_ITEM_SET )
/*N*/         {
/*N*/             const SvxFontItem* pFontItem = (const SvxFontItem*) pItem;
/*N*/             const String& rOldName = pFontItem->GetFamilyName();
/*N*/             xFontConverter = CreateFontToSubsFontConverter( rOldName, nFlags );
/*N*/             if ( xFontConverter )
/*N*/             {
/*N*/                 String aNewName( GetFontToSubsFontName( xFontConverter ) );
/*N*/                 if ( aNewName != rOldName )
/*N*/                 {
/*N*/                     USHORT nAttrRow = pData[nIndex].nRow;
/*N*/                     SvxFontItem aNewItem( pFontItem->GetFamily(), aNewName,
/*N*/                         pFontItem->GetStyleName(), pFontItem->GetPitch(),
/*N*/                         RTL_TEXTENCODING_DONTKNOW, ATTR_FONT );
/*N*/                     ScPatternAttr aNewPattern( *pOldPattern );
/*N*/                     aNewPattern.GetItemSet().Put( aNewItem );
/*N*/                     SetPatternArea( nThisRow, nAttrRow, &aNewPattern, TRUE );
/*N*/                     Search( nThisRow, nIndex );     //! data changed
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/       ++nIndex;
/*N*/       nThisRow = pData[nIndex-1].nRow+1;
/*N*/   }
/*N*/ }

