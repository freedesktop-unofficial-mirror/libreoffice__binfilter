/*************************************************************************
 *
 *  $RCSfile: sc_table1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:32 $
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

#ifdef WIN

// SFX
#define _SFXAPPWIN_HXX
#define _SFX_SAVEOPT_HXX
//#define _SFX_CHILDWIN_HXX ***
#define _SFXCTRLITEM_HXX
#define _SFXPRNMON_HXX
#define _INTRO_HXX
#define _SFXMSGDESCR_HXX
#define _SFXMSGPOOL_HXX
#define _SFXFILEDLG_HXX
#define _PASSWD_HXX
#define _SFXTBXCTRL_HXX
#define _SFXSTBITEM_HXX
#define _SFXMNUITEM_HXX
#define _SFXIMGMGR_HXX
#define _SFXTBXMGR_HXX
#define _SFXSTBMGR_HXX
#define _SFX_MINFITEM_HXX
#define _SFXEVENT_HXX

//#define _SI_HXX
//#define SI_NODRW
#define _SI_DLL_HXX
#define _SIDLL_HXX
#define _SI_NOITEMS
#define _SI_NOOTHERFORMS
#define _SI_NOSBXCONTROLS
#define _SINOSBXCONTROLS
#define _SI_NODRW         //
#define _SI_NOCONTROL
#define _VCBRW_HXX
#define _VCTRLS_HXX
//#define _VCSBX_HXX
#define _VCONT_HXX
#define _VDRWOBJ_HXX
#define _VCATTR_HXX


#define _SVX_DAILDLL_HXX
#define _SVX_HYPHEN_HXX
#define _SVX_IMPGRF_HXX
#define _SVX_OPTITEMS_HXX
#define _SVX_OPTGERL_HXX
#define _SVX_OPTSAVE_HXX
#define _SVX_OPTSPELL_HXX
#define _SVX_OPTPATH_HXX
#define _SVX_OPTLINGU_HXX
#define _SVX_RULER_HXX
#define _SVX_RULRITEM_HXX
#define _SVX_SPLWRAP_HXX
#define _SVX_SPLDLG_HXX
#define _SVX_THESDLG_HXX

#endif  //WIN

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <unotools/textsearch.hxx>
#include <bf_sfx2/objsh.hxx>

#include "attrib.hxx"
#include "patattr.hxx"
#include "cell.hxx"
#include "table.hxx"
#include "document.hxx"
#include "drwlayer.hxx"
#include "olinetab.hxx"
#include "stlsheet.hxx"
#include "global.hxx"
#include "globstr.hrc"
#include "refupdat.hxx"
#include "markdata.hxx"
#include "progress.hxx"
#include "hints.hxx"        // fuer Paint-Broadcast
#include "prnsave.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

extern BOOL bIsOlk, bOderSo;

// -----------------------------------------------------------------------

/*N*/ ScTable::ScTable( ScDocument* pDoc, USHORT nNewTab, const String& rNewName,
/*N*/                   BOOL bColInfo, BOOL bRowInfo ) :
/*N*/   pDocument( pDoc ),
/*N*/   aName( rNewName ),
/*N*/   nTab( nNewTab ),
/*N*/   bScenario( FALSE ),
/*N*/   bActiveScenario( FALSE ),
/*N*/   nScenarioFlags( 0 ),
/*N*/   aScenarioColor( COL_LIGHTGRAY ),
/*N*/   nLinkMode( 0 ),
/*N*/   pColWidth( NULL ),
/*N*/   pColFlags( NULL ),
/*N*/   pRowHeight( NULL ),
/*N*/   pRowFlags( NULL ),
/*N*/   pOutlineTable( NULL ),
/*N*/   bVisible( TRUE ),
/*N*/   pSearchParam( NULL ),
/*N*/   pSearchText ( NULL ),
/*N*/   bProtected( FALSE ),
/*N*/   nRecalcLvl( 0 ),
/*N*/   bPageSizeValid( FALSE ),
/*N*/   nRepeatStartX( REPEAT_NONE ),
/*N*/   nRepeatStartY( REPEAT_NONE ),
/*N*/   aPageStyle( ScGlobal::GetRscString(STR_STYLENAME_STANDARD) ),
/*N*/   bTableAreaValid( FALSE ),
/*N*/   nPrintRangeCount( 0 ),
/*N*/   pPrintRanges( NULL ),
/*N*/   pRepeatColRange( NULL ),
/*N*/   pRepeatRowRange( NULL ),
/*N*/   nLockCount( 0 ),
/*N*/   pScenarioRanges( NULL ),
/*N*/   pSortCollator( NULL )
/*N*/ {
/*N*/   USHORT i;
/*N*/
/*N*/   if (bColInfo)
/*N*/   {
/*N*/       pColWidth  = new USHORT[ MAXCOL+1 ];
/*N*/       pColFlags  = new BYTE[ MAXCOL+1 ];
/*N*/
/*N*/       for (i=0; i<=MAXCOL; i++)
/*N*/       {
/*N*/           pColWidth[i] = STD_COL_WIDTH;
/*N*/           pColFlags[i] = 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bRowInfo)
/*N*/   {
/*N*/       pRowHeight = new USHORT[ MAXROW+1 ];
/*N*/       pRowFlags  = new BYTE[ MAXROW+1 ];
/*N*/
/*N*/       for (i=0; i<=MAXROW; i++)
/*N*/       {
/*N*/           pRowHeight[i] = ScGlobal::nStdRowHeight;
/*N*/           pRowFlags[i] = 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ScDrawLayer* pDrawLayer = pDocument->GetDrawLayer();
/*N*/   if (pDrawLayer)
/*N*/   {
/*N*/       pDrawLayer->ScAddPage( nTab );
/*N*/       pDrawLayer->ScRenamePage( nTab, aName );
/*N*/       ULONG nx = (ULONG) ((double) (MAXCOL+1) * STD_COL_WIDTH           * HMM_PER_TWIPS );
/*N*/       ULONG ny = (ULONG) ((double) (MAXROW+1) * ScGlobal::nStdRowHeight * HMM_PER_TWIPS );
/*N*/       pDrawLayer->SetPageSize( nTab, Size( nx, ny ) );
/*N*/   }
/*N*/
/*N*/   for (i=0; i<=MAXCOL; i++)
/*N*/       aCol[i].Init( i, nTab, pDocument );
/*N*/ }

/*N*/ ScTable::~ScTable()
/*N*/ {
/*N*/   if (!pDocument->IsInDtorClear())
/*N*/   {
/*?*/       //  nicht im dtor die Pages in der falschen Reihenfolge loeschen
/*?*/       //  (nTab stimmt dann als Page-Number nicht!)
/*?*/       //  In ScDocument::Clear wird hinterher per Clear am DrawLayer alles geloescht.
/*?*/
/*?*/       ScDrawLayer* pDrawLayer = pDocument->GetDrawLayer();
/*?*/       if (pDrawLayer)
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/             pDrawLayer->ScRemovePage( nTab );
/*N*/   }
/*N*/
/*N*/   delete[] pColWidth;
/*N*/   delete[] pRowHeight;
/*N*/   delete[] pColFlags;
/*N*/   delete[] pRowFlags;
/*N*/   delete pOutlineTable;
/*N*/   delete pSearchParam;
/*N*/   delete pSearchText;
/*N*/   delete[] pPrintRanges;
/*N*/   delete pRepeatColRange;
/*N*/   delete pRepeatRowRange;
/*N*/   delete pScenarioRanges;
/*N*/   DestroySortCollator();
/*N*/ }

/*N*/ void ScTable::GetName( String& rName ) const
/*N*/ {
/*N*/   rName = aName;
/*N*/ }

/*N*/ void ScTable::SetName( const String& rNewName )
/*N*/ {
/*N*/   String aMd( "D\344umling", RTL_TEXTENCODING_MS_1252 );  // ANSI
/*N*/   if( rNewName == aMd )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 bIsOlk = bOderSo = TRUE;
/*N*/   aName = rNewName;
/*N*/ }

/*N*/ void ScTable::SetVisible( BOOL bVis )
/*N*/ {
/*N*/   bVisible = bVis;
/*N*/ }

/*N*/ void ScTable::SetScenario( BOOL bFlag )
/*N*/ {
/*N*/   bScenario = bFlag;
/*N*/ }

/*N*/ void ScTable::SetLink( BYTE nMode,
/*N*/                       const String& rDoc, const String& rFlt, const String& rOpt,
/*N*/                       const String& rTab, ULONG nRefreshDelay )
/*N*/ {
/*N*/   nLinkMode = nMode;
/*N*/   aLinkDoc = rDoc;        // Datei
/*N*/   aLinkFlt = rFlt;        // Filter
/*N*/   aLinkOpt = rOpt;        // Filter-Optionen
/*N*/   aLinkTab = rTab;        // Tabellenname in Quelldatei
/*N*/   nLinkRefreshDelay = nRefreshDelay;  // refresh delay in seconds, 0==off
/*N*/ }

/*N*/ USHORT ScTable::GetOptimalColWidth( USHORT nCol, OutputDevice* pDev,
/*N*/                                   double nPPTX, double nPPTY,
/*N*/                                   const Fraction& rZoomX, const Fraction& rZoomY,
/*N*/                                   BOOL bFormula, const ScMarkData* pMarkData,
/*N*/                                   BOOL bSimpleTextImport )
/*N*/ {
/*N*/   return aCol[nCol].GetOptimalColWidth( pDev, nPPTX, nPPTY, rZoomX, rZoomY,
/*N*/       bFormula, STD_COL_WIDTH - STD_EXTRA_WIDTH, pMarkData, bSimpleTextImport );
/*N*/ }

//STRIP001 long ScTable::GetNeededSize( USHORT nCol, USHORT nRow,
//STRIP001                              OutputDevice* pDev,
//STRIP001                              double nPPTX, double nPPTY,
//STRIP001                              const Fraction& rZoomX, const Fraction& rZoomY,
//STRIP001                              BOOL bWidth, BOOL bTotalSize )
//STRIP001 {
//STRIP001  ScNeededSizeOptions aOptions;
//STRIP001  aOptions.bSkipMerged = FALSE;       // zusammengefasste mitzaehlen
//STRIP001  aOptions.bTotalSize  = bTotalSize;
//STRIP001
//STRIP001  return aCol[nCol].GetNeededSize
//STRIP001      ( nRow, pDev, nPPTX, nPPTY, rZoomX, rZoomY, bWidth, aOptions );
//STRIP001 }

/*N*/ BOOL ScTable::SetOptimalHeight( USHORT nStartRow, USHORT nEndRow, USHORT nExtra,
/*N*/                               OutputDevice* pDev,
/*N*/                               double nPPTX, double nPPTY,
/*N*/                               const Fraction& rZoomX, const Fraction& rZoomY,
/*N*/                               BOOL bForce )
/*N*/ {
/*N*/   DBG_ASSERT( nExtra==0 || bForce, "autom. OptimalHeight mit Extra" );
/*N*/
/*N*/   BOOL    bChanged = FALSE;
/*N*/   USHORT  nCount = nEndRow-nStartRow+1;
/*N*/
/*N*/   ScProgress* pProgress = NULL;
/*N*/   if ( nCount > 1 )
/*N*/       pProgress = new ScProgress( pDocument->GetDocumentShell(),
/*N*/                           ScGlobal::GetRscString(STR_PROGRESS_HEIGHTING), GetWeightedCount() );
/*N*/
/*N*/   USHORT* pHeight = new USHORT[nCount];                   // Twips !
/*N*/     memset( pHeight, 0, sizeof(USHORT) * nCount );
/*N*/
/*N*/   //  zuerst einmal ueber den ganzen Bereich
/*N*/   //  (mit der letzten Spalte in der Hoffnung, dass die am ehesten noch auf
/*N*/   //   Standard formatiert ist)
/*N*/
/*N*/   aCol[MAXCOL].GetOptimalHeight(
/*N*/           nStartRow, nEndRow, pHeight, pDev, nPPTX, nPPTY, rZoomX, rZoomY, bForce, 0, 0 );
/*N*/
/*N*/   //  daraus Standardhoehe suchen, die im unteren Bereich gilt
/*N*/
/*N*/   USHORT nMinHeight = pHeight[nCount-1];
/*N*/   USHORT nPos = nCount-1;
/*N*/   while ( nPos && pHeight[nPos-1] >= nMinHeight )
/*N*/       --nPos;
/*N*/   USHORT nMinStart = nStartRow + nPos;
/*N*/
/*N*/   long nWeightedCount = 0;
/*N*/   for (USHORT nCol=0; nCol<MAXCOL; nCol++)        // MAXCOL schon oben
/*N*/   {
/*N*/       aCol[nCol].GetOptimalHeight(
/*N*/           nStartRow, nEndRow, pHeight, pDev, nPPTX, nPPTY, rZoomX, rZoomY, bForce,
/*N*/           nMinHeight, nMinStart );
/*N*/
/*N*/       if (pProgress)
/*N*/       {
/*N*/           long nWeight = aCol[nCol].GetWeightedCount();
/*N*/           if (nWeight)        // nochmal denselben Status muss auch nicht sein
/*N*/           {
/*N*/               nWeightedCount += nWeight;
/*N*/               pProgress->SetState( nWeightedCount );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   USHORT nRngStart;
/*N*/   USHORT nRngEnd;
/*N*/   USHORT nLast = 0;
/*N*/   USHORT i;
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       if ( (pRowFlags[nStartRow+i] & CR_MANUALSIZE) == 0 || bForce )
/*N*/       {
/*N*/           if (nExtra)
/*N*/               pRowFlags[nStartRow+i] |= CR_MANUALSIZE;
/*N*/           else
/*N*/               pRowFlags[nStartRow+i] &= ~CR_MANUALSIZE;
/*N*/
/*N*/           if (nLast)
/*N*/           {
/*N*/               if (pHeight[i]+nExtra == nLast)
/*N*/                   nRngEnd = nStartRow+i;
/*N*/               else
/*N*/               {
/*N*/                   bChanged |= SetRowHeightRange( nRngStart, nRngEnd, nLast, nPPTX, nPPTY );
/*N*/                   nLast = 0;
/*N*/               }
/*N*/           }
/*N*/           if (!nLast)
/*N*/           {
/*N*/               nLast = pHeight[i]+nExtra;
/*N*/               nRngStart = nStartRow+i;
/*N*/               nRngEnd = nStartRow+i;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if (nLast)
/*N*/               bChanged |= SetRowHeightRange( nRngStart, nRngEnd, nLast, nPPTX, nPPTY );
/*N*/           nLast = 0;
/*N*/       }
/*N*/   }
/*N*/   if (nLast)
/*N*/       bChanged |= SetRowHeightRange( nRngStart, nRngEnd, nLast, nPPTX, nPPTY );
/*N*/
/*N*/   delete[] pHeight;
/*N*/   delete pProgress;
/*N*/
/*N*/   return bChanged;
/*N*/ }

/*N*/ BOOL ScTable::GetCellArea( USHORT& rEndCol, USHORT& rEndRow ) const
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/   USHORT nMaxX = 0;
/*N*/   USHORT nMaxY = 0;
/*N*/   for (USHORT i=0; i<=MAXCOL; i++)
/*N*/       if (!aCol[i].IsEmptyVisData(TRUE))      // TRUE = Notizen zaehlen auch
/*N*/       {
/*N*/           bFound = TRUE;
/*N*/           nMaxX = i;
/*N*/           USHORT nColY = aCol[i].GetLastVisDataPos(TRUE);
/*N*/           if (nColY > nMaxY)
/*N*/               nMaxY = nColY;
/*N*/       }
/*N*/
/*N*/   rEndCol = nMaxX;
/*N*/   rEndRow = nMaxY;
/*N*/   return bFound;
/*N*/ }

/*N*/ BOOL ScTable::GetTableArea( USHORT& rEndCol, USHORT& rEndRow ) const
/*N*/ {
/*N*/   BOOL bRet = TRUE;               //! merken?
/*N*/   if (!bTableAreaValid)
/*N*/   {
/*N*/       bRet = GetPrintArea( ((ScTable*)this)->nTableAreaX,
/*N*/                               ((ScTable*)this)->nTableAreaY, TRUE );
/*N*/       ((ScTable*)this)->bTableAreaValid = TRUE;
/*N*/   }
/*N*/   rEndCol = nTableAreaX;
/*N*/   rEndRow = nTableAreaY;
/*N*/   return bRet;
/*N*/ }

/*      vorher:

    BOOL bFound = FALSE;
    USHORT nMaxX = 0;
    USHORT nMaxY = 0;
    for (USHORT i=0; i<=MAXCOL; i++)
        if (!aCol[i].IsEmpty())
        {
            bFound = TRUE;
            nMaxX = i;
            USHORT nColY = aCol[i].GetLastEntryPos();
            if (nColY > nMaxY)
                nMaxY = nColY;
        }

    rEndCol = nMaxX;
    rEndRow = nMaxY;
    return bFound;
*/

/*N*/ BOOL ScTable::GetPrintArea( USHORT& rEndCol, USHORT& rEndRow, BOOL bNotes ) const
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/   USHORT nMaxX = 0;
/*N*/   USHORT nMaxY = 0;
/*N*/   USHORT i;
/*N*/
/*N*/   for (i=0; i<=MAXCOL; i++)               // Attribute testen
/*N*/   {
/*N*/       USHORT nFirstRow,nLastRow;
/*N*/       if (aCol[i].HasVisibleAttr( nFirstRow,nLastRow, FALSE ))
/*N*/       {
/*N*/           bFound = TRUE;
/*N*/           nMaxX = i;
/*N*/           if (nLastRow > nMaxY)
/*N*/               nMaxY = nLastRow;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (nMaxX == MAXCOL)                    // Attribute rechts weglassen
/*N*/   {
/*N*/       --nMaxX;
/*N*/       while ( nMaxX>0 && aCol[nMaxX].IsVisibleAttrEqual(aCol[nMaxX+1]) )
/*N*/           --nMaxX;
/*N*/   }
/*N*/
/*N*/   for (i=0; i<=MAXCOL; i++)               // Daten testen
/*N*/       if (!aCol[i].IsEmptyVisData(bNotes))
/*N*/       {
/*N*/           bFound = TRUE;
/*N*/           if (i>nMaxX)
/*N*/               nMaxX = i;
/*N*/           USHORT nColY = aCol[i].GetLastVisDataPos(bNotes);
/*N*/           if (nColY > nMaxY)
/*N*/               nMaxY = nColY;
/*N*/       }
/*N*/
/*N*/   rEndCol = nMaxX;
/*N*/   rEndRow = nMaxY;
/*N*/   return bFound;
/*N*/ }

//STRIP001 BOOL ScTable::GetPrintAreaHor( USHORT nStartRow, USHORT nEndRow,
//STRIP001                              USHORT& rEndCol, BOOL bNotes ) const
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001  USHORT nMaxX = 0;
//STRIP001  USHORT i;
//STRIP001
//STRIP001  for (i=0; i<=MAXCOL; i++)               // Attribute testen
//STRIP001  {
//STRIP001      if (aCol[i].HasVisibleAttrIn( nStartRow, nEndRow ))
//STRIP001      {
//STRIP001          bFound = TRUE;
//STRIP001          nMaxX = i;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (nMaxX == MAXCOL)                    // Attribute rechts weglassen
//STRIP001  {
//STRIP001      --nMaxX;
//STRIP001      while ( nMaxX>0 && aCol[nMaxX].IsVisibleAttrEqual(aCol[nMaxX+1], nStartRow, nEndRow) )
//STRIP001          --nMaxX;
//STRIP001  }
//STRIP001
//STRIP001  for (i=0; i<=MAXCOL; i++)               // Daten testen
//STRIP001  {
//STRIP001      if (!aCol[i].IsEmptyBlock( nStartRow, nEndRow ))        //! bNotes ??????
//STRIP001      {
//STRIP001          bFound = TRUE;
//STRIP001          if (i>nMaxX)
//STRIP001              nMaxX = i;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rEndCol = nMaxX;
//STRIP001  return bFound;
//STRIP001 }

//STRIP001 BOOL ScTable::GetPrintAreaVer( USHORT nStartCol, USHORT nEndCol,
//STRIP001                              USHORT& rEndRow, BOOL bNotes ) const
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001  USHORT nMaxY = 0;
//STRIP001  USHORT i;
//STRIP001
//STRIP001  for (i=nStartCol; i<=nEndCol; i++)              // Attribute testen
//STRIP001  {
//STRIP001      USHORT nFirstRow,nLastRow;
//STRIP001      if (aCol[i].HasVisibleAttr( nFirstRow,nLastRow, FALSE ))
//STRIP001      {
//STRIP001          bFound = TRUE;
//STRIP001          if (nLastRow > nMaxY)
//STRIP001              nMaxY = nLastRow;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  for (i=nStartCol; i<=nEndCol; i++)              // Daten testen
//STRIP001      if (!aCol[i].IsEmptyVisData(bNotes))
//STRIP001      {
//STRIP001          bFound = TRUE;
//STRIP001          USHORT nColY = aCol[i].GetLastVisDataPos(bNotes);
//STRIP001          if (nColY > nMaxY)
//STRIP001              nMaxY = nColY;
//STRIP001      }
//STRIP001
//STRIP001  rEndRow = nMaxY;
//STRIP001  return bFound;
//STRIP001 }

/*N*/ BOOL ScTable::GetDataStart( USHORT& rStartCol, USHORT& rStartRow ) const
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/   USHORT nMinX = MAXCOL;
/*N*/   USHORT nMinY = MAXROW;
/*N*/   USHORT i;
/*N*/
/*N*/   for (i=0; i<=MAXCOL; i++)                   // Attribute testen
/*N*/   {
/*N*/       USHORT nFirstRow,nLastRow;
/*N*/       if (aCol[i].HasVisibleAttr( nFirstRow,nLastRow, TRUE ))
/*N*/       {
/*N*/           if (!bFound)
/*N*/               nMinX = i;
/*N*/           bFound = TRUE;
/*N*/           if (nFirstRow < nMinY)
/*N*/               nMinY = nFirstRow;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (nMinX == 0)                                     // Attribute links weglassen
/*N*/   {
/*N*/       if ( aCol[0].IsVisibleAttrEqual(aCol[1]) )      // keine einzelnen
/*N*/       {
/*?*/           ++nMinX;
/*?*/           while ( nMinX<MAXCOL && aCol[nMinX].IsVisibleAttrEqual(aCol[nMinX-1]) )
/*?*/               ++nMinX;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   BOOL bDatFound = FALSE;
/*N*/   for (i=0; i<=MAXCOL; i++)                   // Daten testen
/*N*/       if (!aCol[i].IsEmptyVisData(TRUE))
/*N*/       {
/*N*/           if (!bDatFound && i<nMinX)
/*N*/               nMinX = i;
/*N*/           bFound = bDatFound = TRUE;
/*N*/           USHORT nColY = aCol[i].GetFirstVisDataPos(TRUE);
/*N*/           if (nColY < nMinY)
/*N*/               nMinY = nColY;
/*N*/       }
/*N*/
/*N*/   rStartCol = nMinX;
/*N*/   rStartRow = nMinY;
/*N*/   return bFound;
/*N*/ }

/*N*/ void ScTable::GetDataArea( USHORT& rStartCol, USHORT& rStartRow, USHORT& rEndCol, USHORT& rEndRow,
/*N*/                           BOOL bIncludeOld )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    BOOL bLeft       = FALSE;
//STRIP001  BOOL bRight  = FALSE;
//STRIP001  BOOL bTop        = FALSE;
//STRIP001  BOOL bBottom = FALSE;
//STRIP001  BOOL bChanged;
//STRIP001  BOOL bFound;
//STRIP001  USHORT i;
//STRIP001  USHORT nTest;
//STRIP001
//STRIP001  do
//STRIP001  {
//STRIP001      bChanged = FALSE;
//STRIP001
//STRIP001      USHORT nStart = rStartRow;
//STRIP001      USHORT nEnd = rEndRow;
//STRIP001      if (nStart>0) --nStart;
//STRIP001      if (nEnd<MAXROW) ++nEnd;
//STRIP001
//STRIP001      if (rEndCol < MAXCOL)
//STRIP001          if (!aCol[rEndCol+1].IsEmptyBlock(nStart,nEnd))
//STRIP001          {
//STRIP001              ++rEndCol;
//STRIP001              bChanged = TRUE;
//STRIP001              bRight = TRUE;
//STRIP001          }
//STRIP001
//STRIP001      if (rStartCol > 0)
//STRIP001          if (!aCol[rStartCol-1].IsEmptyBlock(nStart,nEnd))
//STRIP001          {
//STRIP001              --rStartCol;
//STRIP001              bChanged = TRUE;
//STRIP001              bLeft = TRUE;
//STRIP001          }
//STRIP001
//STRIP001      if (rEndRow < MAXROW)
//STRIP001      {
//STRIP001          nTest = rEndRow+1;
//STRIP001          bFound = FALSE;
//STRIP001          for (i=rStartCol; i<=rEndCol && !bFound; i++)
//STRIP001              if (aCol[i].HasDataAt(nTest))
//STRIP001                  bFound = TRUE;
//STRIP001          if (bFound)
//STRIP001          {
//STRIP001              ++rEndRow;
//STRIP001              bChanged = TRUE;
//STRIP001              bBottom = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (rStartRow > 0)
//STRIP001      {
//STRIP001          nTest = rStartRow-1;
//STRIP001          bFound = FALSE;
//STRIP001          for (i=rStartCol; i<=rEndCol && !bFound; i++)
//STRIP001              if (aCol[i].HasDataAt(nTest))
//STRIP001                  bFound = TRUE;
//STRIP001          if (bFound)
//STRIP001          {
//STRIP001              --rStartRow;
//STRIP001              bChanged = TRUE;
//STRIP001              bTop = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  while( bChanged );
//STRIP001
//STRIP001  if ( !bIncludeOld )
//STRIP001  {
//STRIP001      if ( !bLeft && rStartCol < MAXCOL && rStartCol < rEndCol )
//STRIP001          if ( aCol[rStartCol].IsEmptyBlock(rStartRow,rEndRow) )
//STRIP001              ++rStartCol;
//STRIP001      if ( !bRight && rEndCol > 0 && rStartCol < rEndCol )
//STRIP001          if ( aCol[rEndCol].IsEmptyBlock(rStartRow,rEndRow) )
//STRIP001              --rEndCol;
//STRIP001      if ( !bTop && rStartRow < MAXROW && rStartRow < rEndRow )
//STRIP001      {
//STRIP001          bFound = FALSE;
//STRIP001          for (i=rStartCol; i<=rEndCol && !bFound; i++)
//STRIP001              if (aCol[i].HasDataAt(rStartRow))
//STRIP001                  bFound = TRUE;
//STRIP001          if (!bFound)
//STRIP001              ++rStartRow;
//STRIP001      }
//STRIP001      if ( !bBottom && rEndRow > 0 && rStartRow < rEndRow )
//STRIP001      {
//STRIP001          bFound = FALSE;
//STRIP001          for (i=rStartCol; i<=rEndCol && !bFound; i++)
//STRIP001              if (aCol[i].HasDataAt(rEndRow))
//STRIP001                  bFound = TRUE;
//STRIP001          if (!bFound)
//STRIP001              --rEndRow;
//STRIP001      }
//STRIP001  }
/*N*/ }

//STRIP001 USHORT ScTable::GetEmptyLinesInBlock( USHORT nStartCol, USHORT nStartRow,
//STRIP001                                      USHORT nEndCol, USHORT nEndRow, ScDirection eDir )
//STRIP001 {
//STRIP001  USHORT nCount = 0;
//STRIP001  USHORT nCol;
//STRIP001  if ((eDir == DIR_BOTTOM) || (eDir == DIR_TOP))
//STRIP001  {
//STRIP001      nCount = nEndRow - nStartRow;
//STRIP001      for (nCol = nStartCol; nCol <= nEndCol; nCol++)
//STRIP001          nCount = Min(nCount, aCol[nCol].GetEmptyLinesInBlock(nStartRow, nEndRow, eDir));
//STRIP001  }
//STRIP001  else if (eDir == DIR_RIGHT)
//STRIP001  {
//STRIP001      nCol = nEndCol;
//STRIP001      while (((short)nCol >= (short)nStartCol) &&
//STRIP001               aCol[nCol].IsEmptyBlock(nStartRow, nEndRow))
//STRIP001      {
//STRIP001          nCount++;
//STRIP001          nCol--;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nCol = nStartCol;
//STRIP001      while ((nCol <= nEndCol) && aCol[nCol].IsEmptyBlock(nStartRow, nEndRow))
//STRIP001      {
//STRIP001          nCount++;
//STRIP001          nCol++;
//STRIP001      }
//STRIP001  }
//STRIP001  return nCount;
//STRIP001 }

//STRIP001 BOOL ScTable::IsEmptyLine( USHORT nRow, USHORT nStartCol, USHORT nEndCol )
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001  for (USHORT i=nStartCol; i<=nEndCol && !bFound; i++)
//STRIP001      if (aCol[i].HasDataAt(nRow))
//STRIP001          bFound = TRUE;
//STRIP001  return !bFound;
//STRIP001 }

//STRIP001 void ScTable::LimitChartArea( USHORT& rStartCol, USHORT& rStartRow, USHORT& rEndCol, USHORT& rEndRow )
//STRIP001 {
//STRIP001  while ( rStartCol<rEndCol && aCol[rStartCol].IsEmptyBlock(rStartRow,rEndRow) )
//STRIP001      ++rStartCol;
//STRIP001
//STRIP001  while ( rStartCol<rEndCol && aCol[rEndCol].IsEmptyBlock(rStartRow,rEndRow) )
//STRIP001      --rEndCol;
//STRIP001
//STRIP001  while ( rStartRow<rEndRow && IsEmptyLine(rStartRow, rStartCol, rEndCol) )
//STRIP001      ++rStartRow;
//STRIP001
//STRIP001  while ( rStartRow<rEndRow && IsEmptyLine(rEndRow, rStartCol, rEndCol) )
//STRIP001      --rEndRow;
//STRIP001 }

//STRIP001 void ScTable::FindAreaPos( USHORT& rCol, USHORT& rRow, short nMovX, short nMovY )
//STRIP001 {
//STRIP001  if (nMovX)
//STRIP001  {
//STRIP001      short nNewCol = (short) rCol;
//STRIP001      BOOL bThere = aCol[nNewCol].HasVisibleDataAt(rRow);
//STRIP001      BOOL bFnd;
//STRIP001      if (bThere)
//STRIP001      {
//STRIP001          do
//STRIP001          {
//STRIP001              nNewCol += nMovX;
//STRIP001              bFnd = (nNewCol>=0 && nNewCol<=MAXCOL) ? aCol[nNewCol].HasVisibleDataAt(rRow) : FALSE;
//STRIP001          }
//STRIP001          while (bFnd);
//STRIP001          nNewCol -= nMovX;
//STRIP001
//STRIP001          if (nNewCol == (short)rCol)
//STRIP001              bThere = FALSE;
//STRIP001      }
//STRIP001
//STRIP001      if (!bThere)
//STRIP001      {
//STRIP001          do
//STRIP001          {
//STRIP001              nNewCol += nMovX;
//STRIP001              bFnd = (nNewCol>=0 && nNewCol<=MAXCOL) ? aCol[nNewCol].HasVisibleDataAt(rRow) : TRUE;
//STRIP001          }
//STRIP001          while (!bFnd);
//STRIP001      }
//STRIP001
//STRIP001      if (nNewCol<0) nNewCol=0;
//STRIP001      if (nNewCol>MAXCOL) nNewCol=MAXCOL;
//STRIP001      rCol = (USHORT) nNewCol;
//STRIP001  }
//STRIP001
//STRIP001  if (nMovY)
//STRIP001      aCol[rCol].FindDataAreaPos(rRow,nMovY);
//STRIP001 }

//STRIP001 BOOL ScTable::ValidNextPos( USHORT nCol, USHORT nRow, const ScMarkData& rMark,
//STRIP001                              BOOL bMarked, BOOL bUnprotected )
//STRIP001 {
//STRIP001  if (nCol > MAXCOL || nRow > MAXROW)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if (bMarked && !rMark.IsCellMarked(nCol,nRow))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if (bUnprotected && ((const ScProtectionAttr*)
//STRIP001                      GetAttr(nCol,nRow,ATTR_PROTECTION))->GetProtection())
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if (bMarked || bUnprotected)        //! auch sonst ???
//STRIP001  {
//STRIP001      //  #53697# ausgeblendete muessen uebersprungen werden, weil der Cursor sonst
//STRIP001      //  auf der naechsten Zelle landet, auch wenn die geschuetzt/nicht markiert ist.
//STRIP001      //! per Extra-Parameter steuern, nur fuer Cursor-Bewegung ???
//STRIP001
//STRIP001      if ( pRowFlags && ( pRowFlags[nRow] & CR_HIDDEN ) )
//STRIP001          return FALSE;
//STRIP001      if ( pColFlags && ( pColFlags[nCol] & CR_HIDDEN ) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ void ScTable::GetNextPos( USHORT& rCol, USHORT& rRow, short nMovX, short nMovY,
/*N*/                               BOOL bMarked, BOOL bUnprotected, const ScMarkData& rMark )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    if (bUnprotected && !IsProtected())     // Tabelle ueberhaupt geschuetzt?
//STRIP001      bUnprotected = FALSE;
//STRIP001
//STRIP001  USHORT nWrap = 0;
//STRIP001  short nCol = rCol;
//STRIP001  short nRow = rRow;
//STRIP001
//STRIP001  nCol += nMovX;
//STRIP001  nRow += nMovY;
//STRIP001
//STRIP001  DBG_ASSERT( !nMovY || !bUnprotected,
//STRIP001              "GetNextPos mit bUnprotected horizontal nicht implementiert" );
//STRIP001
//STRIP001  if ( nMovY && bMarked )
//STRIP001  {
//STRIP001      BOOL bUp = ( nMovY < 0 );
//STRIP001      nRow = rMark.GetNextMarked( nCol, nRow, bUp );
//STRIP001      while ( VALIDROW(nRow) && pRowFlags && (pRowFlags[nRow] & CR_HIDDEN) )
//STRIP001      {
//STRIP001          //  #53697# ausgeblendete ueberspringen (s.o.)
//STRIP001          nRow += nMovY;
//STRIP001          nRow = rMark.GetNextMarked( nCol, nRow, bUp );
//STRIP001      }
//STRIP001
//STRIP001      while ( nRow < 0 || nRow > MAXROW )
//STRIP001      {
//STRIP001          nCol += nMovY;
//STRIP001          while ( VALIDCOL(nCol) && pColFlags && (pColFlags[nCol] & CR_HIDDEN) )
//STRIP001              nCol += nMovY;      //  #53697# ausgeblendete ueberspringen (s.o.)
//STRIP001          if (nCol < 0)
//STRIP001          {
//STRIP001              nCol = MAXCOL;
//STRIP001              if (++nWrap >= 2)
//STRIP001                  return;
//STRIP001          }
//STRIP001          else if (nCol > MAXCOL)
//STRIP001          {
//STRIP001              nCol = 0;
//STRIP001              if (++nWrap >= 2)
//STRIP001                  return;
//STRIP001          }
//STRIP001          if (nRow < 0)
//STRIP001              nRow = MAXROW;
//STRIP001          else if (nRow > MAXROW)
//STRIP001              nRow = 0;
//STRIP001          nRow = rMark.GetNextMarked( nCol, nRow, bUp );
//STRIP001          while ( VALIDROW(nRow) && pRowFlags && (pRowFlags[nRow] & CR_HIDDEN) )
//STRIP001          {
//STRIP001              //  #53697# ausgeblendete ueberspringen (s.o.)
//STRIP001              nRow += nMovY;
//STRIP001              nRow = rMark.GetNextMarked( nCol, nRow, bUp );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( nMovX && ( bMarked || bUnprotected ) )
//STRIP001  {
//STRIP001      // initiales Weiterzaehlen wrappen:
//STRIP001      if (nCol<0)
//STRIP001      {
//STRIP001          nCol = MAXCOL;
//STRIP001          --nRow;
//STRIP001          if (nRow<0)
//STRIP001              nRow = MAXROW;
//STRIP001      }
//STRIP001      if (nCol>MAXCOL)
//STRIP001      {
//STRIP001          nCol = 0;
//STRIP001          ++nRow;
//STRIP001          if (nRow>MAXROW)
//STRIP001              nRow = 0;
//STRIP001      }
//STRIP001
//STRIP001      if ( !ValidNextPos(nCol, nRow, rMark, bMarked, bUnprotected) )
//STRIP001      {
//STRIP001          short* pNextRows = new short[MAXCOL+1];
//STRIP001          USHORT i;
//STRIP001
//STRIP001          if ( nMovX > 0 )                            //  vorwaerts
//STRIP001          {
//STRIP001              for (i=0; i<=MAXCOL; i++)
//STRIP001                  pNextRows[i] = (i<nCol) ? (nRow+1) : nRow;
//STRIP001              do
//STRIP001              {
//STRIP001                  short nNextRow = pNextRows[nCol] + 1;
//STRIP001                  if ( bMarked )
//STRIP001                      nNextRow = rMark.GetNextMarked( nCol, nNextRow, FALSE );
//STRIP001                  if ( bUnprotected )
//STRIP001                      nNextRow = aCol[nCol].GetNextUnprotected( nNextRow, FALSE );
//STRIP001                  pNextRows[nCol] = nNextRow;
//STRIP001
//STRIP001                  short nMinRow = MAXROW+1;
//STRIP001                  for (i=0; i<=MAXCOL; i++)
//STRIP001                      if (pNextRows[i] < nMinRow)     // bei gleichen den linken
//STRIP001                      {
//STRIP001                          nMinRow = pNextRows[i];
//STRIP001                          nCol = i;
//STRIP001                      }
//STRIP001                  nRow = nMinRow;
//STRIP001
//STRIP001                  if ( nRow > MAXROW )
//STRIP001                  {
//STRIP001                      if (++nWrap >= 2) break;        // ungueltigen Wert behalten
//STRIP001                      nCol = nRow = 0;
//STRIP001                      for (i=0; i<=MAXCOL; i++)
//STRIP001                          pNextRows[i] = 0;           // alles ganz von vorne
//STRIP001                  }
//STRIP001              }
//STRIP001              while ( !ValidNextPos(nCol, nRow, rMark, bMarked, bUnprotected) );
//STRIP001          }
//STRIP001          else                                        //  rueckwaerts
//STRIP001          {
//STRIP001              for (i=0; i<=MAXCOL; i++)
//STRIP001                  pNextRows[i] = (i>nCol) ? (nRow-1) : nRow;
//STRIP001              do
//STRIP001              {
//STRIP001                  short nNextRow = pNextRows[nCol] - 1;
//STRIP001                  if ( bMarked )
//STRIP001                      nNextRow = rMark.GetNextMarked( nCol, nNextRow, TRUE );
//STRIP001                  if ( bUnprotected )
//STRIP001                      nNextRow = aCol[nCol].GetNextUnprotected( nNextRow, TRUE );
//STRIP001                  pNextRows[nCol] = nNextRow;
//STRIP001
//STRIP001                  short nMaxRow = -1;
//STRIP001                  for (i=0; i<=MAXCOL; i++)
//STRIP001                      if (pNextRows[i] >= nMaxRow)    // bei gleichen den rechten
//STRIP001                      {
//STRIP001                          nMaxRow = pNextRows[i];
//STRIP001                          nCol = i;
//STRIP001                      }
//STRIP001                  nRow = nMaxRow;
//STRIP001
//STRIP001                  if ( nRow < 0 )
//STRIP001                  {
//STRIP001                      if (++nWrap >= 2) break;        // ungueltigen Wert behalten
//STRIP001                      nCol = MAXCOL;
//STRIP001                      nRow = MAXROW;
//STRIP001                      for (i=0; i<=MAXCOL; i++)
//STRIP001                          pNextRows[i] = MAXROW;      // alles ganz von vorne
//STRIP001                  }
//STRIP001              }
//STRIP001              while ( !ValidNextPos(nCol, nRow, rMark, bMarked, bUnprotected) );
//STRIP001          }
//STRIP001
//STRIP001          delete[] pNextRows;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  ungueltige Werte kommen z.b. bei Tab heraus,
//STRIP001  //  wenn nicht markiert und nicht geschuetzt ist (linker / rechter Rand),
//STRIP001  //  dann Werte unveraendert lassen
//STRIP001
//STRIP001  if (VALIDCOLROW(nCol,nRow))
//STRIP001  {
//STRIP001      rCol = nCol;
//STRIP001      rRow = nRow;
//STRIP001  }
/*N*/ }

/*N*/ BOOL ScTable::GetNextMarkedCell( USHORT& rCol, USHORT& rRow, const ScMarkData& rMark )
/*N*/ {
/*N*/   const ScMarkArray* pMarkArray = rMark.GetArray();
/*N*/   DBG_ASSERT(pMarkArray,"GetNextMarkedCell ohne MarkArray");
/*N*/   if ( !pMarkArray )
/*N*/       return FALSE;
/*N*/
/*N*/   ++rRow;                 // naechste Zelle ist gesucht
/*N*/
/*N*/   while ( rCol <= MAXCOL )
/*N*/   {
/*N*/       const ScMarkArray& rArray = pMarkArray[rCol];
/*N*/       while ( rRow <= MAXROW )
/*N*/       {
/*N*/           USHORT nStart = (USHORT) rArray.GetNextMarked( (short) rRow, FALSE );
/*N*/           if ( nStart <= MAXROW )
/*N*/           {
/*N*/               USHORT nEnd = rArray.GetMarkEnd( nStart, FALSE );
/*N*/               ScColumnIterator aColIter( &aCol[rCol], nStart, nEnd );
/*N*/               USHORT nCellRow;
/*N*/               ScBaseCell* pCell = NULL;
/*N*/               while ( aColIter.Next( nCellRow, pCell ) )
/*N*/               {
/*N*/                   if ( pCell && pCell->GetCellType() != CELLTYPE_NOTE )
/*N*/                   {
/*N*/                       rRow = nCellRow;
/*N*/                       return TRUE;            // Zelle gefunden
/*N*/                   }
/*N*/               }
/*N*/               rRow = nEnd + 1;                // naechsten markierten Bereich suchen
/*N*/           }
/*N*/           else
/*N*/               rRow = MAXROW + 1;              // Ende der Spalte
/*N*/       }
/*N*/       rRow = 0;
/*N*/       ++rCol;                                 // naechste Spalte testen
/*N*/   }
/*N*/
/*N*/   return FALSE;                               // alle Spalten durch
/*N*/ }

/*N*/ void ScTable::UpdateDrawRef( UpdateRefMode eUpdateRefMode, USHORT nCol1, USHORT nRow1, USHORT nTab1,
/*N*/                                   USHORT nCol2, USHORT nRow2, USHORT nTab2,
/*N*/                                   short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   if ( nTab >= nTab1 && nTab <= nTab2 && nDz == 0 )       // only within the table
/*N*/   {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/         ScDrawLayer* pDrawLayer = pDocument->GetDrawLayer();
//STRIP001 /*?*/        if ( eUpdateRefMode != URM_COPY && pDrawLayer )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if ( eUpdateRefMode == URM_MOVE )
//STRIP001 /*?*/            {                                               // source range
//STRIP001 /*?*/                nCol1 -= nDx;
//STRIP001 /*?*/                nRow1 -= nDy;
//STRIP001 /*?*/                nCol2 -= nDx;
//STRIP001 /*?*/                nRow2 -= nDy;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            pDrawLayer->MoveArea( nTab, nCol1,nRow1, nCol2,nRow2, nDx,nDy,
//STRIP001 /*?*/                                    (eUpdateRefMode == URM_INSDEL) );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

/*N*/ void ScTable::UpdateReference( UpdateRefMode eUpdateRefMode, USHORT nCol1, USHORT nRow1, USHORT nTab1,
/*N*/                    USHORT nCol2, USHORT nRow2, USHORT nTab2, short nDx, short nDy, short nDz,
/*N*/                    ScDocument* pUndoDoc, BOOL bIncludeDraw )
/*N*/ {
/*N*/   USHORT i;
/*N*/   USHORT iMax;
/*N*/   if ( eUpdateRefMode == URM_COPY )
/*N*/   {
/*N*/       i = nCol1;
/*N*/       iMax = nCol2;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       i = 0;
/*N*/       iMax = MAXCOL;
/*N*/   }
/*N*/   for ( ; i<=iMax; i++)
/*N*/       aCol[i].UpdateReference( eUpdateRefMode, nCol1, nRow1, nTab1, nCol2, nRow2, nTab2,
/*N*/                                   nDx, nDy, nDz, pUndoDoc );
/*N*/
/*N*/   if ( bIncludeDraw )
/*N*/       UpdateDrawRef( eUpdateRefMode, nCol1, nRow1, nTab1, nCol2, nRow2, nTab2, nDx, nDy, nDz );
/*N*/
/*N*/   if ( nTab >= nTab1 && nTab <= nTab2 && nDz == 0 )       // print ranges: only within the table
/*N*/   {
/*?*/       USHORT nSTab,nETab,nSCol,nSRow,nECol,nERow;
/*?*/       BOOL bRecalcPages = FALSE;
/*?*/
/*?*/       if ( pPrintRanges && nPrintRangeCount )
/*?*/           for ( i=0; i<nPrintRangeCount; i++ )
/*?*/           {
/*?*/               nSTab = nETab = pPrintRanges[i].aStart.Tab();
/*?*/               nSCol = pPrintRanges[i].aStart.Col();
/*?*/               nSRow = pPrintRanges[i].aStart.Row();
/*?*/               nECol = pPrintRanges[i].aEnd.Col();
/*?*/               nERow = pPrintRanges[i].aEnd.Row();
/*?*/
/*?*/               if ( ScRefUpdate::Update( pDocument, eUpdateRefMode,
/*?*/                                         nCol1,nRow1,nTab1, nCol2,nRow2,nTab2,
/*?*/                                         nDx,nDy,nDz,
/*?*/                                         nSCol,nSRow,nSTab, nECol,nERow,nETab ) )
/*?*/               {
/*?*/                   pPrintRanges[i] = ScRange( nSCol, nSRow, nSTab, nECol, nERow, nSTab );
/*?*/                   bRecalcPages = TRUE;
/*?*/               }
/*?*/           }
/*?*/
/*?*/       if ( pRepeatColRange )
/*?*/       {
/*?*/           nSTab = nETab = pRepeatColRange->aStart.Tab();
/*?*/           nSCol = pRepeatColRange->aStart.Col();
/*?*/           nSRow = pRepeatColRange->aStart.Row();
/*?*/           nECol = pRepeatColRange->aEnd.Col();
/*?*/           nERow = pRepeatColRange->aEnd.Row();
/*?*/
/*?*/           if ( ScRefUpdate::Update( pDocument, eUpdateRefMode,
/*?*/                                     nCol1,nRow1,nTab1, nCol2,nRow2,nTab2,
/*?*/                                     nDx,nDy,nDz,
/*?*/                                     nSCol,nSRow,nSTab, nECol,nERow,nETab ) )
/*?*/           {
/*?*/               *pRepeatColRange = ScRange( nSCol, nSRow, nSTab, nECol, nERow, nSTab );
/*?*/               bRecalcPages = TRUE;
/*?*/               nRepeatStartX = nSCol;  // fuer UpdatePageBreaks
/*?*/               nRepeatEndX = nECol;
/*?*/           }
/*?*/       }
/*?*/
/*?*/       if ( pRepeatRowRange )
/*?*/       {
/*?*/           nSTab = nETab = pRepeatRowRange->aStart.Tab();
/*?*/           nSCol = pRepeatRowRange->aStart.Col();
/*?*/           nSRow = pRepeatRowRange->aStart.Row();
/*?*/           nECol = pRepeatRowRange->aEnd.Col();
/*?*/           nERow = pRepeatRowRange->aEnd.Row();
/*?*/
/*?*/           if ( ScRefUpdate::Update( pDocument, eUpdateRefMode,
/*?*/                                     nCol1,nRow1,nTab1, nCol2,nRow2,nTab2,
/*?*/                                     nDx,nDy,nDz,
/*?*/                                     nSCol,nSRow,nSTab, nECol,nERow,nETab ) )
/*?*/           {
/*?*/               *pRepeatRowRange = ScRange( nSCol, nSRow, nSTab, nECol, nERow, nSTab );
/*?*/               bRecalcPages = TRUE;
/*?*/               nRepeatStartY = nSRow;  // fuer UpdatePageBreaks
/*?*/               nRepeatEndY = nERow;
/*?*/           }
/*?*/       }
/*?*/
/*?*/       //  updating print ranges is not necessary with multiple print ranges
/*?*/       if ( bRecalcPages && GetPrintRangeCount() <= 1 )
/*?*/       {
/*?*/           UpdatePageBreaks(NULL);
/*?*/
/*?*/           SfxObjectShell* pDocSh = pDocument->GetDocumentShell();
/*?*/           if (pDocSh)
/*?*/               pDocSh->Broadcast( ScPaintHint(
/*?*/                                   ScRange(0,0,nTab,MAXCOL,MAXROW,nTab),
/*?*/                                   PAINT_GRID ) );
/*?*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScTable::UpdateTranspose( const ScRange& rSource, const ScAddress& rDest,
//STRIP001                                  ScDocument* pUndoDoc )
//STRIP001 {
//STRIP001  for ( USHORT i=0; i<=MAXCOL; i++ )
//STRIP001      aCol[i].UpdateTranspose( rSource, rDest, pUndoDoc );
//STRIP001 }

//STRIP001 void ScTable::UpdateGrow( const ScRange& rArea, USHORT nGrowX, USHORT nGrowY )
//STRIP001 {
//STRIP001  for ( USHORT i=0; i<=MAXCOL; i++ )
//STRIP001      aCol[i].UpdateGrow( rArea, nGrowX, nGrowY );
//STRIP001 }

/*N*/ void ScTable::UpdateInsertTab(USHORT nTable)
/*N*/ {
/*N*/   if (nTab >= nTable) nTab++;
/*N*/   for (USHORT i=0; i <= MAXCOL; i++) aCol[i].UpdateInsertTab(nTable);
/*N*/ }

//STRIP001 void ScTable::UpdateInsertTabOnlyCells(USHORT nTable)
//STRIP001 {
//STRIP001  for (USHORT i=0; i <= MAXCOL; i++) aCol[i].UpdateInsertTabOnlyCells(nTable);
//STRIP001 }

/*N*/  void ScTable::UpdateDeleteTab( USHORT nTable, BOOL bIsMove, ScTable* pRefUndo )
/*N*/  {
/*N*/   if (nTab > nTable) nTab--;
/*N*/
/*N*/   USHORT i;
/*N*/   if (pRefUndo)
/*N*/       for (i=0; i <= MAXCOL; i++) aCol[i].UpdateDeleteTab(nTable, bIsMove, &pRefUndo->aCol[i]);
/*N*/   else
/*N*/       for (i=0; i <= MAXCOL; i++) aCol[i].UpdateDeleteTab(nTable, bIsMove, NULL);
/*N*/  }

/*N*/  void ScTable::UpdateMoveTab( USHORT nOldPos, USHORT nNewPos, USHORT nTabNo,
/*N*/       ScProgress& rProgress )
/*N*/  {
/*N*/   nTab = nTabNo;
/*N*/   for ( USHORT i=0; i <= MAXCOL; i++ )
/*N*/   {
/*N*/       aCol[i].UpdateMoveTab( nOldPos, nNewPos, nTabNo );
/*N*/       rProgress.SetState( rProgress.GetState() + aCol[i].GetCodeCount() );
/*N*/   }
/*N*/  }

/*N*/ void ScTable::UpdateCompile( BOOL bForceIfNameInUse )
/*N*/ {
/*N*/   for (USHORT i=0; i <= MAXCOL; i++)
/*N*/   {
/*N*/       aCol[i].UpdateCompile( bForceIfNameInUse );
/*N*/   }
/*N*/ }

/*N*/ void ScTable::SetTabNo(USHORT nNewTab)
/*N*/ {
/*N*/   nTab = nNewTab;
/*N*/   for (USHORT i=0; i <= MAXCOL; i++) aCol[i].SetTabNo(nNewTab);
/*N*/ }

/*N*/ BOOL ScTable::IsRangeNameInUse(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
                               USHORT nIndex) const
/*N*/ {
/*N*/   BOOL bInUse = FALSE;
/*N*/   for (USHORT i = nCol1; !bInUse && (i <= nCol2) && (i <= MAXCOL); i++)
/*N*/       bInUse = aCol[i].IsRangeNameInUse(nRow1, nRow2, nIndex);
/*N*/   return bInUse;
/*N*/ }

/*N*/ void ScTable::ReplaceRangeNamesInUse(USHORT nCol1, USHORT nRow1,
/*N*/                               USHORT nCol2, USHORT nRow2,
/*N*/                                   const ScIndexMap& rMap )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    for (USHORT i = nCol1; i <= nCol2 && (i <= MAXCOL); i++)
//STRIP001  {
//STRIP001      aCol[i].ReplaceRangeNamesInUse( nRow1, nRow2, rMap );
//STRIP001  }
/*N*/ }

/*N*/ void ScTable::ExtendPrintArea( OutputDevice* pDev,
/*N*/                   USHORT nStartCol, USHORT nStartRow, USHORT& rEndCol, USHORT nEndRow )
/*N*/ {
/*N*/   if ( !pColFlags || !pRowFlags )
/*N*/   {
/*N*/       DBG_ERROR("keine ColInfo oder RowInfo in ExtendPrintArea");
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   Point aPix1000 = pDev->LogicToPixel( Point(1000,1000), MAP_TWIP );
/*N*/   double nPPTX = aPix1000.X() / 1000.0;
/*N*/   double nPPTY = aPix1000.Y() / 1000.0;
/*N*/
/*N*/   BOOL bEmpty[MAXCOL+1];
/*N*/   for (USHORT i=0; i<=MAXCOL; i++)
/*N*/       bEmpty[i] = ( aCol[i].GetCellCount() == 0 );
/*N*/
/*N*/   USHORT nIndex;
/*N*/   USHORT nPrintCol = rEndCol;
/*N*/   for (USHORT nRow = nStartRow; nRow<=nEndRow; nRow++)
/*N*/   {
/*N*/       if ( ( pRowFlags[nRow] & CR_HIDDEN ) == 0 )
/*N*/       {
/*N*/           USHORT nDataCol = rEndCol;
/*N*/           while (nDataCol > 0 && ( bEmpty[nDataCol] || !aCol[nDataCol].Search(nRow,nIndex) ) )
/*N*/               --nDataCol;
/*N*/           if ( ( pColFlags[nDataCol] & CR_HIDDEN ) == 0 )
/*N*/           {
/*N*/               ScBaseCell* pCell = aCol[nDataCol].GetCell(nRow);
/*N*/               if (pCell)
/*N*/               {
/*N*/                   CellType eType = pCell->GetCellType();
/*N*/                   if (eType == CELLTYPE_STRING || eType == CELLTYPE_EDIT
/*N*/                       || (eType == CELLTYPE_FORMULA && !((ScFormulaCell*)pCell)->IsValue()) )
/*N*/                   {
/*N*/                       BOOL bFormula = FALSE;  //! uebergeben
/*N*/                       long nPixel = pCell->GetTextWidth();
/*N*/
/*N*/                       // Breite bereits im Idle-Handler berechnet?
/*N*/                       if ( TEXTWIDTH_DIRTY == nPixel )
/*N*/                       {
/*N*/                           ScNeededSizeOptions aOptions;
/*N*/                           aOptions.bTotalSize  = TRUE;
/*N*/                           aOptions.bFormula    = bFormula;
/*N*/                           aOptions.bSkipMerged = FALSE;
/*N*/
/*N*/                           Fraction aZoom(1,1);
/*N*/                           nPixel = aCol[nDataCol].GetNeededSize( nRow,
/*N*/                                                       pDev,nPPTX,nPPTY,aZoom,aZoom,
/*N*/                                                       TRUE, aOptions );
/*N*/                           pCell->SetTextWidth( (USHORT)nPixel );
/*N*/                       }
/*N*/
/*N*/                       long nTwips = (long) (nPixel / nPPTX);
/*N*/                       long nDocW = GetColWidth( nDataCol );
/*N*/                       USHORT nCol = nDataCol;
/*N*/                       while (nTwips > nDocW && nCol < MAXCOL)
/*N*/                       {
/*N*/                           ++nCol;
/*N*/                           nDocW += GetColWidth( nCol );
/*N*/                       }
/*N*/                       if (nCol>nPrintCol)
/*N*/                           nPrintCol = nCol;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   rEndCol = nPrintCol;
/*N*/ }

/*N*/ void ScTable::DoColResize( USHORT nCol1, USHORT nCol2, USHORT nAdd )
/*N*/ {
/*N*/   for (USHORT nCol=nCol1; nCol<=nCol2; nCol++)
/*N*/       aCol[nCol].Resize(aCol[nCol].GetCellCount() + nAdd);
/*N*/ }

/*N*/ #define SET_PRINTRANGE( p1, p2 ) \
/*N*/   if ( (p2) )                             \
/*N*/   {                                       \
/*N*/       if ( (p1) )                         \
/*N*/           *(p1) = *(p2);                  \
/*N*/       else                                \
/*N*/           (p1) = new ScRange( *(p2) );    \
/*N*/   }                                       \
/*N*/   else                                    \
/*N*/       DELETEZ( (p1) )

/*N*/ void ScTable::SetRepeatColRange( const ScRange* pNew )
/*N*/ {
/*N*/   SET_PRINTRANGE( pRepeatColRange, pNew );
/*N*/ }

/*N*/ void ScTable::SetRepeatRowRange( const ScRange* pNew )
/*N*/ {
/*N*/   SET_PRINTRANGE( pRepeatRowRange, pNew );
/*N*/ }

// #42845# zeroptimiert
#if defined(WIN) && defined(MSC)
#pragma optimize("",off)
#endif
/*N*/ void ScTable::SetPrintRangeCount( USHORT nNew )
/*N*/ {
/*N*/   ScRange* pNewRanges;
/*N*/   if (nNew)
/*N*/       pNewRanges = new ScRange[nNew];
/*N*/   else
/*N*/       pNewRanges = NULL;
/*N*/
/*N*/   if ( pPrintRanges && nNew >= nPrintRangeCount )     //  Anzahl vergroessert?
/*?*/       for ( USHORT i=0; i<nPrintRangeCount; i++ )     //  (fuer "Hinzufuegen")
/*?*/           pNewRanges[i] = pPrintRanges[i];            //  alte Ranges kopieren
/*N*/
/*N*/   delete[] pPrintRanges;
/*N*/   pPrintRanges = pNewRanges;
/*N*/   nPrintRangeCount = nNew;
/*N*/ }
#if defined(WIN) && defined(MSC)
#pragma optimize("",on)
#endif

/*N*/ void ScTable::SetPrintRange( USHORT nPos, const ScRange& rNew )
/*N*/ {
/*N*/   if (nPos < nPrintRangeCount && pPrintRanges)
/*N*/       pPrintRanges[nPos] = rNew;
/*N*/   else
/*N*/       DBG_ERROR("SetPrintRange falsch");
/*N*/ }

/*N*/ const ScRange* ScTable::GetPrintRange(USHORT nPos) const
/*N*/ {
/*N*/   if (nPos < nPrintRangeCount && pPrintRanges)
/*N*/       return pPrintRanges+nPos;
/*N*/   else
/*N*/       return NULL;
/*N*/ }

/*N*/ void ScTable::FillPrintSaver( ScPrintSaverTab& rSaveTab ) const
/*N*/ {
/*N*/   rSaveTab.SetAreas( nPrintRangeCount, pPrintRanges );
/*N*/   rSaveTab.SetRepeat( pRepeatColRange, pRepeatRowRange );
/*N*/ }

//STRIP001 void ScTable::RestorePrintRanges( const ScPrintSaverTab& rSaveTab )
//STRIP001 {
//STRIP001  USHORT nNewCount = rSaveTab.GetPrintCount();
//STRIP001  const ScRange* pNewRanges = rSaveTab.GetPrintRanges();
//STRIP001
//STRIP001  SetPrintRangeCount( nNewCount );
//STRIP001  for (USHORT i=0; i<nNewCount; i++ )
//STRIP001      SetPrintRange( i, pNewRanges[i] );
//STRIP001
//STRIP001  SetRepeatColRange( rSaveTab.GetRepeatCol() );
//STRIP001  SetRepeatRowRange( rSaveTab.GetRepeatRow() );
//STRIP001
//STRIP001  UpdatePageBreaks(NULL);
//STRIP001 }





}
