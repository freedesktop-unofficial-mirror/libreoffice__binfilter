/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_fillinfo.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:36:19 $
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
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/boxitem.hxx>
#include <bf_svx/shaditem.hxx>

#include "document.hxx"
#include "cell.hxx"
#include "attarray.hxx"
#include "markdata.hxx"
#include "patattr.hxx"
#include "poolhelp.hxx"
#include "docpool.hxx"
#include "conditio.hxx"
#include "stlpool.hxx"
namespace binfilter {


// -----------------------------------------------------------------------

enum FillInfoLinePos
    {
        FILP_TOP,
        FILP_BOTTOM,
        FILP_LEFT,
        FILP_RIGHT
    };


/*N*/ inline const SvxBorderLine* GetNullOrLine( const SvxBoxItem* pBox, FillInfoLinePos eWhich )
/*N*/ {
/*N*/  if (pBox)
/*N*/   {
/*N*/       if (eWhich==FILP_TOP)
/*N*/           return pBox->GetTop();
/*N*/       else if (eWhich==FILP_BOTTOM)
/*N*/           return pBox->GetBottom();
/*N*/       else if (eWhich==FILP_LEFT)
/*N*/           return pBox->GetLeft();
/*N*/       else
/*N*/           return pBox->GetRight();
/*N*/   }
/*N*/   else
/*N*/       return NULL;
/*N*/ }

//  aehnlich wie in output.cxx

/*N*/ void lcl_GetMergeRange( short nX, short nY, USHORT nArrY,
/*N*/                           ScDocument* pDoc, RowInfo* pRowInfo,
/*N*/                           USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2, USHORT nTab,
/*N*/                           short& rStartX, short& rStartY, short& rEndX, short& rEndY )
/*N*/ {
/*N*/   CellInfo* pInfo = &pRowInfo[nArrY].pCellInfo[nX+1];
/*N*/
/*N*/   rStartX = nX;
/*N*/   rStartY = nY;
/*N*/   BOOL bHOver = pInfo->bHOverlapped;
/*N*/   BOOL bVOver = pInfo->bVOverlapped;
/*N*/
/*N*/   while (bHOver)              // nY konstant
/*N*/   {
/*N*/       --rStartX;
/*N*/       if (rStartX >= (short) nX1 && (pDoc->GetColFlags(rStartX,nTab) & CR_HIDDEN) == 0)
/*N*/       {
/*N*/           bHOver = pRowInfo[nArrY].pCellInfo[rStartX+1].bHOverlapped;
/*N*/           bVOver = pRowInfo[nArrY].pCellInfo[rStartX+1].bVOverlapped;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           USHORT nOverlap = ((ScMergeFlagAttr*)pDoc->GetAttr(
/*?*/                               rStartX, rStartY, nTab, ATTR_MERGE_FLAG ))->GetValue();
/*?*/           bHOver = ((nOverlap & SC_MF_HOR) != 0);
/*?*/           bVOver = ((nOverlap & SC_MF_VER) != 0);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   while (bVOver)
/*N*/   {
/*N*/       --rStartY;
/*N*/
/*N*/       if (nArrY>0)
/*N*/           --nArrY;                        // lokale Kopie !
/*N*/
/*N*/       if (rStartX >= (short) nX1 && rStartY >= (short) nY1 &&
/*N*/           (pDoc->GetColFlags(rStartX,nTab) & CR_HIDDEN) == 0 &&
/*N*/           (pDoc->GetRowFlags(rStartY,nTab) & CR_HIDDEN) == 0 &&
/*N*/           (short) pRowInfo[nArrY].nRowNo == rStartY)
/*N*/       {
/*N*/           bHOver = pRowInfo[nArrY].pCellInfo[rStartX+1].bHOverlapped;
/*N*/           bVOver = pRowInfo[nArrY].pCellInfo[rStartX+1].bVOverlapped;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           USHORT nOverlap = ((ScMergeFlagAttr*)pDoc->GetAttr(
/*?*/                               rStartX, rStartY, nTab, ATTR_MERGE_FLAG ))->GetValue();
/*?*/           bHOver = ((nOverlap & SC_MF_HOR) != 0);
/*?*/           bVOver = ((nOverlap & SC_MF_VER) != 0);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   const ScMergeAttr* pMerge;
/*N*/   if (rStartX >= (short) nX1 && rStartY >= (short) nY1 &&
/*N*/       (pDoc->GetColFlags(rStartX,nTab) & CR_HIDDEN) == 0 &&
/*N*/       (pDoc->GetRowFlags(rStartY,nTab) & CR_HIDDEN) == 0 &&
/*N*/       (short) pRowInfo[nArrY].nRowNo == rStartY)
/*N*/   {
/*N*/       pMerge = (const ScMergeAttr*) &pRowInfo[nArrY].pCellInfo[rStartX+1].pPatternAttr->
/*N*/                                       GetItem(ATTR_MERGE);
/*N*/   }
/*N*/   else
/*?*/       pMerge = (const ScMergeAttr*) pDoc->GetAttr(rStartX,rStartY,nTab,ATTR_MERGE);
/*N*/
/*N*/   rEndX = rStartX + pMerge->GetColMerge() - 1;
/*N*/   rEndY = rStartY + pMerge->GetRowMerge() - 1;
/*N*/ }

/*N*/ inline BOOL ScDocument::RowHidden( USHORT nRow, USHORT nTab )
/*N*/ {
/*N*/   return ( pTab[nTab]->pRowFlags[nRow] & CR_HIDDEN ) != 0;
/*N*/ }


#define CELLINFO(x,y) pRowInfo[nArrY+y].pCellInfo[nArrX+x]

/*N*/ USHORT ScDocument::FillInfo( RowInfo* pRowInfo, USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
/*N*/                           USHORT nTab, double nScaleX, double nScaleY,
/*N*/                           BOOL bPageMode, BOOL bFormulaMode, const ScMarkData* pMarkData )
/*N*/ {
/*N*/   DBG_ASSERT( pTab[nTab], "Tabelle existiert nicht" );
/*N*/
/*N*/   ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*N*/   ScStyleSheetPool* pStlPool = xPoolHelper->GetStylePool();
/*N*/
/*N*/   const SvxBrushItem* pDefBackground =
/*N*/           (const SvxBrushItem*) &pPool->GetDefaultItem( ATTR_BACKGROUND );
/*N*/   const ScMergeAttr* pDefMerge =
/*N*/           (const ScMergeAttr*) &pPool->GetDefaultItem( ATTR_MERGE );
/*N*/   const SvxBoxItem* pDefLines =
/*N*/           (const SvxBoxItem*) &pPool->GetDefaultItem( ATTR_BORDER );
/*N*/   const SvxShadowItem* pDefShadow =
/*N*/           (const SvxShadowItem*) &pPool->GetDefaultItem( ATTR_SHADOW );
/*N*/
/*N*/   USHORT nThisRow;
/*N*/   USHORT nX;
/*N*/   USHORT nY;
/*N*/   short nSignedY;
/*N*/   USHORT nArrX;
/*N*/   USHORT nArrY;
/*N*/   USHORT nArrCount;
/*N*/   BOOL bAnyLines = FALSE;
/*N*/   BOOL bAnyMerged = FALSE;
/*N*/   BOOL bAnyShadow = FALSE;
/*N*/   BOOL bAnyCondition = FALSE;
/*N*/
/*N*/   BOOL bTabProtect = IsTabProtected(nTab);
/*N*/
/*N*/                                               // fuer Blockmarken von zusammengefassten Zellen mit
/*N*/                                               // versteckter erster Zeile / Spalte
/*N*/   BOOL bPaintMarks = FALSE;
/*N*/   BOOL bSkipMarks = FALSE;
/*N*/   USHORT nBlockStartX, nBlockStartY, nBlockEndX, nBlockEndY;
/*N*/   if (pMarkData && pMarkData->IsMarked())
/*N*/   {
/*?*/       ScRange aTmpRange;
/*?*/       pMarkData->GetMarkArea(aTmpRange);
/*?*/       if ( nTab >= aTmpRange.aStart.Tab() && nTab <= aTmpRange.aEnd.Tab() )
/*?*/       {
/*?*/           nBlockStartX = aTmpRange.aStart.Col();
/*?*/           nBlockStartY = aTmpRange.aStart.Row();
/*?*/           nBlockEndX = aTmpRange.aEnd.Col();
/*?*/           nBlockEndY = aTmpRange.aEnd.Row();
/*?*/           ExtendHidden( nBlockStartX, nBlockStartY, nBlockEndX, nBlockEndY, nTab );   //? noetig ?
/*?*/           if (pMarkData->IsMarkNegative())
/*?*/               bSkipMarks = TRUE;
/*?*/           else
/*?*/               bPaintMarks = TRUE;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   //  zuerst nur die Eintraege fuer die ganze Spalte
/*N*/
/*N*/   nArrY=0;
/*N*/   USHORT nYExtra = nY2+1;
/*N*/   for (nSignedY=((short)nY1)-1; nSignedY<=(short)nYExtra; nSignedY++)
/*N*/   {
/*N*/       if (nSignedY >= 0)
/*N*/           nY = (USHORT) nSignedY;
/*N*/       else
/*N*/           nY = MAXROW+1;          // ungueltig
/*N*/
/*N*/       USHORT nDocHeight;
/*N*/       if (nY <= MAXROW)
/*N*/           nDocHeight = GetRowHeight( nY, nTab );
/*N*/       else
/*N*/           nDocHeight = ScGlobal::nStdRowHeight;
/*N*/
/*N*/       if ( nArrY==0 || nDocHeight || nY > MAXROW )
/*N*/       {
/*N*/           RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*N*/           pThisRowInfo->pCellInfo = NULL;                 // wird unten belegt
/*N*/
/*N*/           USHORT nHeight = (USHORT) ( nDocHeight * nScaleY );
/*N*/           if (!nHeight)
/*N*/               nHeight = 1;
/*N*/
/*N*/           pThisRowInfo->nRowNo        = nY;               //! Fall < 0 ?
/*N*/           pThisRowInfo->nHeight       = nHeight;
/*N*/           pThisRowInfo->bEmptyBack    = TRUE;
/*N*/           pThisRowInfo->bEmptyText    = TRUE;
/*N*/           pThisRowInfo->bChanged      = TRUE;
/*N*/           pThisRowInfo->bAutoFilter   = FALSE;
/*N*/           pThisRowInfo->bPushButton   = FALSE;
/*N*/           pThisRowInfo->nRotMaxCol    = SC_ROTMAX_NONE;
/*N*/
/*N*/           ++nArrY;
/*N*/           if (nArrY >= ROWINFO_MAX)
/*N*/           {
/*N*/               DBG_ERROR("Zu grosser Bereich bei FillInfo" );
/*N*/               nYExtra = nSignedY;                                 // Ende
/*N*/               nY2 = nYExtra - 1;                                  // Bereich anpassen
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           if (nSignedY==(short) nYExtra)                          // zusaetzliche Zeile verdeckt ?
/*N*/               ++nYExtra;
/*N*/   }
/*N*/   nArrCount = nArrY;                                      // incl. Dummys
/*N*/
/*N*/   //  rotierter Text...
/*N*/
/*N*/   //  Attribut im Dokument ueberhaupt verwendet?
/*N*/   BOOL bAnyItem = FALSE;
/*N*/   USHORT nRotCount = pPool->GetItemCount( ATTR_ROTATE_VALUE );
/*N*/   for (USHORT nItem=0; nItem<nRotCount; nItem++)
/*N*/       if (pPool->GetItem( ATTR_ROTATE_VALUE, nItem ))
/*N*/       {
/*N*/           bAnyItem = TRUE;
/*N*/           break;
/*N*/       }
/*N*/
/*N*/   USHORT nRotMax = nX2;
/*N*/   if ( bAnyItem && HasAttrib( 0,nY1,nTab, MAXCOL,nY2+1,nTab,
/*N*/                               HASATTR_ROTATE | HASATTR_CONDITIONAL ) )
/*N*/   {
/*N*/       //! Conditionals auch bei HASATTR_ROTATE abfragen ????
/*N*/
/*N*/       DBG_ASSERT( nArrCount>2, "nArrCount zu klein" );
/*N*/ //        FindMaxRotCol( nTab, &pRowInfo[1], nArrCount-2, nX1, nX2 );
/*N*/       FindMaxRotCol( nTab, &pRowInfo[1], nArrCount-1, nX1, nX2 );
/*N*/       //  FindMaxRotCol setzt nRotMaxCol
/*N*/
/*N*/       for (nArrY=0; nArrY<nArrCount; nArrY++)
/*N*/           if (pRowInfo[nArrY].nRotMaxCol != SC_ROTMAX_NONE && pRowInfo[nArrY].nRotMaxCol > nRotMax)
/*N*/               nRotMax = pRowInfo[nArrY].nRotMaxCol;
/*N*/   }
/*N*/
/*N*/   //  Zell-Infos erst nach dem Test auf gedrehte allozieren
/*N*/   //  bis nRotMax wegen nRotateDir Flag
/*N*/
/*N*/   for (nArrY=0; nArrY<nArrCount; nArrY++)
/*N*/   {
/*N*/       RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*N*/       nY = pThisRowInfo->nRowNo;
/*N*/       pThisRowInfo->pCellInfo = new CellInfo[ nRotMax+1+2 ];  // vom Aufrufer zu loeschen !
/*N*/
/*N*/       for (nArrX=0; nArrX<=nRotMax+2; nArrX++)                // Zell-Infos vorbelegen
/*N*/       {
/*N*/           if (nArrX>0)
/*N*/               nX = nArrX-1;
/*N*/           else
/*N*/               nX = MAXCOL+1;      // ungueltig
/*N*/
/*N*/           CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*N*/           pInfo->bEmptyCellText = TRUE;
/*N*/           pInfo->pCell = NULL;
/*N*/           if (bPaintMarks)
/*N*/               pInfo->bMarked = ( nX >= nBlockStartX && nX <= nBlockEndX
/*N*/                               && nY >= nBlockStartY && nY <= nBlockEndY );
/*N*/           else
/*N*/               pInfo->bMarked = FALSE;
/*N*/           pInfo->nWidth = 0;
/*N*/
/*N*/           pInfo->bStandard    = FALSE;    //! umbenennen in bClipped
/*N*/           pInfo->bMerged      = FALSE;
/*N*/           pInfo->bHOverlapped = FALSE;
/*N*/           pInfo->bVOverlapped = FALSE;
/*N*/           pInfo->bAutoFilter  = FALSE;
/*N*/           pInfo->bPushButton  = FALSE;
/*N*/           pInfo->nRotateDir   = SC_ROTDIR_NONE;
/*N*/
/*N*/           pInfo->bPrinted     = FALSE;                    //  view-intern
/*N*/           pInfo->bHideGrid    = FALSE;                    //  view-intern
/*N*/           pInfo->bEditEngine  = FALSE;                    //  view-intern
/*N*/
/*N*/           pInfo->pBackground  = NULL;                     //! weglassen?
/*N*/           pInfo->pPatternAttr = NULL;
/*N*/           pInfo->pConditionSet= NULL;
/*N*/
/*N*/           pInfo->pLinesAttr  = NULL;
/*N*/           pInfo->pRightLine  = NULL;
/*N*/           pInfo->pBottomLine = NULL;
/*N*/
/*N*/           pInfo->pShadowAttr    = pDefShadow;
/*N*/           pInfo->pHShadowOrigin = NULL;
/*N*/           pInfo->pVShadowOrigin = NULL;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   for (nArrX=nX2+3; nArrX<=nRotMax+2; nArrX++)            // restliche Breiten eintragen
/*N*/   {
/*?*/       nX = nArrX-1;
/*?*/       if ( nX <= MAXCOL )
/*?*/       {
/*?*/           if ( (GetColFlags(nX,nTab) & CR_HIDDEN) == 0 )          // Spalte nicht versteckt
/*?*/           {
/*?*/               USHORT nThisWidth = (USHORT) (GetColWidth( nX, nTab ) * nScaleX);
/*?*/               if (!nThisWidth)
/*?*/                   nThisWidth = 1;
/*?*/
/*?*/               pRowInfo[0].pCellInfo[nArrX].nWidth = nThisWidth;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   for (nArrX=0; nArrX<=nX2+2; nArrX++)                    // links & rechts + 1
/*N*/   {
/*N*/       nX = (nArrX>0) ? nArrX-1 : MAXCOL+1;                    // negativ -> ungueltig
/*N*/
/*N*/       if ( nX <= MAXCOL )
/*N*/       {
/*N*/           if ( (GetColFlags(nX,nTab) & CR_HIDDEN) == 0 )          // Spalte nicht versteckt
/*N*/           {
/*N*/               USHORT nThisWidth = (USHORT) (GetColWidth( nX, nTab ) * nScaleX);
/*N*/               if (!nThisWidth)
/*N*/                   nThisWidth = 1;
/*N*/
/*N*/               pRowInfo[0].pCellInfo[nArrX].nWidth = nThisWidth;           //! dies sollte reichen
/*N*/
/*N*/               ScColumn* pThisCol = &pTab[nTab]->aCol[nX];                 // Spalten-Daten
/*N*/
/*N*/               nArrY = 1;
/*N*/               USHORT nUIndex;
/*N*/               (void) pThisCol->Search( nY1, nUIndex );
/*N*/               while ( nUIndex < pThisCol->nCount &&
/*N*/                       (nThisRow=pThisCol->pItems[nUIndex].nRow) <= nY2 )
/*N*/               {
/*N*/                   if ( !RowHidden( nThisRow,nTab ) )
/*N*/                   {
/*N*/                       while ( pRowInfo[nArrY].nRowNo < nThisRow )
/*N*/                           ++nArrY;
/*N*/                       DBG_ASSERT( pRowInfo[nArrY].nRowNo == nThisRow, "Zeile nicht gefunden in FillInfo" );
/*N*/
/*N*/                       RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*N*/                       CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*N*/                       pInfo->pCell = pThisCol->pItems[nUIndex].pCell;
/*N*/                       if (pInfo->pCell->GetCellType() != CELLTYPE_NOTE)
/*N*/                       {
/*N*/                           pThisRowInfo->bEmptyText = FALSE;                   // Zeile nicht leer
/*N*/                           pInfo->bEmptyCellText = FALSE;                      // Zelle nicht leer
/*N*/                       }
/*N*/                       ++nArrY;
/*N*/                   }
/*N*/                   ++nUIndex;
/*N*/               }
/*N*/
/*N*/               if (nX+1 >= nX1)                                // Attribute/Blockmarken ab nX1-1
/*N*/               {
/*N*/                   ScAttrArray* pThisAttrArr = pThisCol->pAttrArray;       // Attribute
/*N*/
/*N*/                   nArrY = 0;
/*N*/                   const ScPatternAttr* pPattern;
/*N*/                   USHORT nCurRow=nY1;                 // einzelne Zeile
/*N*/                   if (nCurRow>0)
/*N*/                       --nCurRow;                      // oben 1 mehr
/*N*/                   else
/*N*/                       nArrY = 1;
/*N*/                   nThisRow=nCurRow;                   // Ende des Bereichs
/*N*/                   short  nIndex;
/*N*/                   (void) pThisAttrArr->Search( nCurRow, nIndex );
/*N*/
/*N*/
/*N*/                   do
/*N*/                   {
/*N*/                       nThisRow=pThisAttrArr->pData[nIndex].nRow;              // Ende des Bereichs
/*N*/                       pPattern=pThisAttrArr->pData[nIndex].pPattern;
/*N*/
/*N*/                       const SvxBrushItem* pBackground = (const SvxBrushItem*)
/*N*/                                                       &pPattern->GetItem(ATTR_BACKGROUND);
/*N*/                       const SvxBoxItem* pLinesAttr = (const SvxBoxItem*)
/*N*/                                                       &pPattern->GetItem(ATTR_BORDER);
/*N*/                       if (pLinesAttr != pDefLines)
/*N*/                           bAnyLines = TRUE;
/*N*/
/*N*/                       const SvxShadowItem* pShadowAttr = (const SvxShadowItem*)
/*N*/                                                       &pPattern->GetItem(ATTR_SHADOW);
/*N*/                       if (pShadowAttr != pDefShadow)
/*N*/                           bAnyShadow = TRUE;
/*N*/
/*N*/                       const ScMergeAttr* pMergeAttr = (const ScMergeAttr*)
/*N*/                                               &pPattern->GetItem(ATTR_MERGE);
/*N*/                       BOOL bMerged = ( pMergeAttr != pDefMerge && *pMergeAttr != *pDefMerge );
/*N*/                       USHORT nOverlap = ((const ScMergeFlagAttr*) &pPattern->GetItemSet().
/*N*/                                                       Get(ATTR_MERGE_FLAG))->GetValue();
/*N*/                       BOOL bHOverlapped = ((nOverlap & SC_MF_HOR) != 0);
/*N*/                       BOOL bVOverlapped = ((nOverlap & SC_MF_VER) != 0);
/*N*/                       BOOL bAutoFilter  = ((nOverlap & SC_MF_AUTO) != 0);
/*N*/                       BOOL bPushButton  = ((nOverlap & SC_MF_BUTTON) != 0);
/*N*/                       BOOL bScenario    = ((nOverlap & SC_MF_SCENARIO) != 0);
/*N*/                       if (bMerged||bHOverlapped||bVOverlapped)
/*N*/                           bAnyMerged = TRUE;                              // intern
/*N*/
/*N*/                       BOOL bHidden, bHideFormula;
/*N*/                       if (bTabProtect)
/*N*/                       {
/*N*/                           const ScProtectionAttr& rProtAttr = (const ScProtectionAttr&)
/*N*/                                                       pPattern->GetItem(ATTR_PROTECTION);
/*N*/                           bHidden = rProtAttr.GetHideCell();
/*N*/                           bHideFormula = rProtAttr.GetHideFormula();
/*N*/                       }
/*N*/                       else
/*N*/                           bHidden = bHideFormula = FALSE;
/*N*/
/*N*/                       ULONG nConditional = ((const SfxUInt32Item&)pPattern->
/*N*/                                               GetItem(ATTR_CONDITIONAL)).GetValue();
/*N*/                       const ScConditionalFormat* pCondForm = NULL;
/*N*/                       if ( nConditional && pCondFormList )
/*N*/                           pCondForm = pCondFormList->GetFormat( nConditional );
/*N*/
/*N*/                       do
/*N*/                       {
/*N*/                           if ( nArrY==0 || !RowHidden( nCurRow,nTab ) )
/*N*/                           {
/*N*/                               RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*N*/                               if (pBackground != pDefBackground)          // Spalten-HG == Standard ?
/*N*/                                   pThisRowInfo->bEmptyBack = FALSE;
/*N*/                               if (bAutoFilter)
/*N*/                                   pThisRowInfo->bAutoFilter = TRUE;
/*N*/                               if (bPushButton)
/*N*/                                   pThisRowInfo->bPushButton = TRUE;
/*N*/
/*N*/                               CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*N*/                               pInfo->pBackground  = pBackground;
/*N*/                               pInfo->pPatternAttr = pPattern;
/*N*/                               pInfo->bMerged      = bMerged;
/*N*/                               pInfo->bHOverlapped = bHOverlapped;
/*N*/                               pInfo->bVOverlapped = bVOverlapped;
/*N*/                               pInfo->bAutoFilter  = bAutoFilter;
/*N*/                               pInfo->bPushButton  = bPushButton;
/*N*/                               pInfo->pLinesAttr   = pLinesAttr;
/*N*/                               pInfo->pShadowAttr  = pShadowAttr;
/*N*/                               //  nWidth wird nicht mehr einzeln gesetzt
/*N*/
/*N*/                               BOOL bEmbed = bIsEmbedded &&
/*N*/                                       nTab    >= aEmbedRange.aStart.Tab() &&
/*N*/                                       nTab    <= aEmbedRange.aEnd.Tab()   &&
/*N*/                                       nX      >= aEmbedRange.aStart.Col() &&
/*N*/                                       nX      <= aEmbedRange.aEnd.Col()   &&
/*N*/                                       nCurRow >= aEmbedRange.aStart.Row() &&
/*N*/                                       nCurRow <= aEmbedRange.aEnd.Row();
/*N*/
/*N*/                               if (bPushButton || bScenario)
/*N*/                               {
/*N*/                                   pInfo->pBackground = ScGlobal::GetButtonBrushItem();
/*N*/                                   pThisRowInfo->bEmptyBack = FALSE;
/*N*/                               }
/*N*/                               else if (bEmbed)
/*N*/                               {
/*N*/                                   pInfo->pBackground = ScGlobal::GetEmbeddedBrushItem();
/*N*/                                   pThisRowInfo->bEmptyBack = FALSE;
/*N*/                               }
/*N*/
/*N*/                               if (bHidden || ( bFormulaMode && bHideFormula && pInfo->pCell
/*N*/                                                   && pInfo->pCell->GetCellType()
/*N*/                                                       == CELLTYPE_FORMULA ))
/*N*/                                   pInfo->bEmptyCellText = TRUE;
/*N*/
/*N*/                               if ( pCondForm )
/*N*/                               {
/*N*/                                   String aStyle = pCondForm->GetCellStyle( pInfo->pCell,
/*N*/                                                       ScAddress( nX, nCurRow, nTab ) );
/*N*/                                   if (aStyle.Len())
/*N*/                                   {
/*N*/                                       SfxStyleSheetBase* pStyleSheet =
/*N*/                                               pStlPool->Find( aStyle, SFX_STYLE_FAMILY_PARA );
/*N*/                                       if ( pStyleSheet )
/*N*/                                       {
/*N*/                                           //! Style-Sets cachen !!!
/*N*/                                           pInfo->pConditionSet = &pStyleSheet->GetItemSet();
/*N*/                                           bAnyCondition = TRUE;
/*N*/                                       }
/*N*/                                       // if style is not there, treat like no condition
/*N*/                                   }
/*N*/                               }
/*N*/
/*N*/                               ++nArrY;
/*N*/                           }
/*N*/                           ++nCurRow;
/*N*/                       }
/*N*/                       while (nCurRow <= nThisRow && nCurRow <= nYExtra);
/*N*/                       ++nIndex;
/*N*/                   }
/*N*/                   while ( nIndex < (short) pThisAttrArr->nCount && nThisRow < nYExtra );
/*N*/
/*N*/
/*N*/                   if (pMarkData && pMarkData->IsMultiMarked())
/*N*/                   {
/*?*/                       //  Blockmarken
/*?*/                       const ScMarkArray* pThisMarkArr = pMarkData->GetArray()+nX;
/*?*/                       BOOL bThisMarked;
/*?*/                       nArrY = 1;
/*?*/                       nCurRow = nY1;                                      // einzelne Zeile
/*?*/                       nThisRow = nY1;                                     // Ende des Bereichs
/*?*/                       (void) pThisMarkArr->Search( nY1, nIndex );
/*?*/
/*?*/                       do
/*?*/                       {
/*?*/                           nThisRow=pThisMarkArr->pData[nIndex].nRow;      // Ende des Bereichs
/*?*/                           bThisMarked=pThisMarkArr->pData[nIndex].bMarked;
/*?*/
/*?*/                           do
/*?*/                           {
/*?*/                               if ( !RowHidden( nCurRow,nTab ) )
/*?*/                               {
/*?*/                                   if ( bThisMarked )
/*?*/                                   {
/*?*/                                       BOOL bSkip = bSkipMarks &&
/*?*/                                                   nX      >= nBlockStartX &&
/*?*/                                                   nX      <= nBlockEndX   &&
/*?*/                                                   nCurRow >= nBlockStartY &&
/*?*/                                                   nCurRow <= nBlockEndY;
/*?*/                                       if (!bSkip)
/*?*/                                       {
/*?*/                                           RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*?*/                                           CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*?*/                                           pInfo->bMarked = TRUE;
/*?*/                                       }
/*?*/                                   }
/*?*/                                   ++nArrY;
/*?*/                               }
/*?*/                               ++nCurRow;
/*?*/                           }
/*?*/                           while (nCurRow <= nThisRow && nCurRow <= nY2);
/*?*/                           ++nIndex;
/*?*/                       }
/*?*/                       while ( nIndex < (short) pThisMarkArr->nCount && nThisRow < nY2 );
/*?*/                   }
/*?*/               }
/*?*/               else                                    // vordere Spalten
/*?*/               {
/*?*/                   for (nArrY=1; nArrY+1<nArrCount; nArrY++)
/*?*/                   {
/*?*/                       RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*?*/                       CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*?*/
/*?*/                       pInfo->nWidth       = nThisWidth;           //! oder nur 0 abfragen ??
/*?*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           pRowInfo[0].pCellInfo[nArrX].nWidth = STD_COL_WIDTH;
/*N*/       // STD_COL_WIDTH ganz links und rechts wird fuer DrawExtraShadow gebraucht
/*N*/   }
/*N*/
/*N*/   //-------------------------------------------------------------------------
/*N*/   //  bedingte Formatierung auswerten
/*N*/
/*N*/   if (bAnyCondition)
/*N*/   {
/*?*/       for (nArrY=0; nArrY<nArrCount; nArrY++)
/*?*/       {
/*?*/           for (nArrX=nX1; nArrX<=nX2+2; nArrX++)                  // links und rechts einer mehr
/*?*/           {
/*?*/               CellInfo* pInfo = &pRowInfo[nArrY].pCellInfo[nArrX];
/*?*/               const SfxItemSet* pCondSet = pInfo->pConditionSet;
/*?*/               if (pCondSet)
/*?*/               {
/*?*/                   const SfxPoolItem* pItem;
/*?*/
/*?*/                           //  Hintergrund
/*?*/                   if ( pCondSet->GetItemState( ATTR_BACKGROUND, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/                   {
/*?*/                       pInfo->pBackground = (const SvxBrushItem*) pItem;
/*?*/                       pRowInfo[nArrY].bEmptyBack = FALSE;
/*?*/                   }
/*?*/
/*?*/                           //  Umrandung
/*?*/                   if ( pCondSet->GetItemState( ATTR_BORDER, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/                   {
/*?*/                       pInfo->pLinesAttr = (const SvxBoxItem*) pItem;
/*?*/                       bAnyLines = TRUE;
/*?*/                   }
/*?*/
/*?*/                           //  Schatten
/*?*/                   if ( pCondSet->GetItemState( ATTR_SHADOW, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/                   {
/*?*/                       pInfo->pShadowAttr = (const SvxShadowItem*) pItem;
/*?*/                       bAnyShadow = TRUE;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   //  bedingte Formatierung Ende
/*N*/   //-------------------------------------------------------------------------
/*N*/
/*N*/
/*N*/   if (bAnyMerged)
/*N*/       bAnyLines = TRUE;                           // Linien koennen aus Merge hereinkommen!
/*N*/
/*N*/   if (bAnyLines)                                  // vier Seiten suchen
/*N*/   {
/*N*/       for (nArrY=0; nArrY<nArrCount; nArrY++)
/*N*/       {
/*N*/ //            short nY = nArrY ? pRowInfo[nArrY].nRowNo : ((short)nY1)-1;
/*N*/
/*N*/           for (nArrX=nX1; nArrX<=nX2+2; nArrX++)                  // links und rechts einer mehr
/*N*/           {
/*N*/               short nX = ((short) nArrX) - 1;
/*N*/               CellInfo* pInfo = &pRowInfo[nArrY].pCellInfo[nArrX];
/*N*/
/*N*/               pInfo->pThisBottom = GetNullOrLine( pInfo->pLinesAttr, FILP_BOTTOM );
/*N*/               if ( nArrY+1 < nArrCount )
/*N*/                   pInfo->pNextTop =
/*N*/                       GetNullOrLine( CELLINFO(0,1).pLinesAttr, FILP_TOP );
/*N*/               else
/*N*/                   pInfo->pNextTop = NULL;
/*N*/
/*N*/               pInfo->pThisRight = GetNullOrLine( pInfo->pLinesAttr, FILP_RIGHT );
/*N*/               if ( nX <= (short) nX2 )
/*N*/                   pInfo->pNextLeft =
/*N*/                       GetNullOrLine( CELLINFO(1,0).pLinesAttr, FILP_LEFT );
/*N*/               else
/*N*/                   pInfo->pNextLeft = NULL;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/               //
/*N*/               //      Daten von zusammengefassten Zellen anpassen
/*N*/               //
/*N*/
/*N*/   if (bAnyMerged)
/*N*/   {
/*N*/       for (nArrY=0; nArrY<nArrCount; nArrY++)
/*N*/       {
/*N*/           RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*N*/           short nY = nArrY ? pThisRowInfo->nRowNo : ((short)nY1)-1;
/*N*/
/*N*/           for (nArrX=nX1; nArrX<=nX2+2; nArrX++)                  // links und rechts einer mehr
/*N*/           {
/*N*/               short nX = ((short) nArrX) - 1;
/*N*/               CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*N*/
/*N*/               if (pInfo->bMerged || pInfo->bHOverlapped || pInfo->bVOverlapped)
/*N*/               {
/*N*/                   short nStartX;
/*N*/                   short nStartY;
/*N*/                   short nEndX;
/*N*/                   short nEndY;
/*N*/                   lcl_GetMergeRange( nX,nY, nArrY, this,pRowInfo, nX1,nY1,nX2,nY2,nTab,
/*N*/                                       nStartX,nStartY, nEndX,nEndY );
/*N*/                   const ScPatternAttr* pStartPattern = GetPattern( nStartX,nStartY,nTab );
/*N*/                   const SfxItemSet* pStartCond = GetCondResult( nStartX,nStartY,nTab );
/*N*/                   const SfxPoolItem* pItem;
/*N*/
/*N*/                   USHORT nVisStartX = (USHORT) nStartX;           // sichtbarer Bereich
/*N*/                   USHORT nVisStartY = (USHORT) nStartY;
/*N*/                   USHORT nVisEndX = (USHORT) nEndX;
/*N*/                   USHORT nVisEndY = (USHORT) nEndY;
/*N*/                   StripHidden( nVisStartX, nVisStartY, nVisEndX, nVisEndY, nTab );
/*N*/
/*N*/                   if ( nX != (short) nVisStartX && nArrX > 0)
/*N*/                       pThisRowInfo->pCellInfo[nArrX-1].pNextLeft = NULL;
/*N*/                   if ( nY != (short) nVisStartY && nArrY > 0)
/*N*/                       pRowInfo[nArrY-1].pCellInfo[nArrX].pNextTop = NULL;
/*N*/
/*N*/                   if ( nX != (short) nVisEndX ) pInfo->pThisRight = NULL;
/*N*/                   if ( nY != (short) nVisEndY ) pInfo->pThisBottom = NULL;
/*N*/
/*N*/                   if ( nX == (short) nVisStartX || nY == (short) nVisStartY ||
/*N*/                        nX == (short) nVisEndX   || nY == (short) nVisEndY )
/*N*/                   {
/*N*/                       if ( !pStartCond || pStartCond->
/*N*/                                   GetItemState(ATTR_BORDER,TRUE,&pItem) != SFX_ITEM_SET )
/*N*/                           pItem = &pStartPattern->GetItem(ATTR_BORDER);
/*N*/                       const SvxBoxItem* pBox = (const SvxBoxItem*) pItem;
/*N*/                       if ( nX == (short) nVisStartX && nArrX > 0 )
/*N*/                           pThisRowInfo->pCellInfo[nArrX-1].pNextLeft = pBox->GetLeft();
/*N*/                       if ( nY == (short) nVisStartY && nArrY > 0)
/*N*/                           pRowInfo[nArrY-1].pCellInfo[nArrX].pNextTop = pBox->GetTop();
/*N*/                       if ( nX == (short) nVisEndX )
/*N*/                           pInfo->pThisRight = pBox->GetRight();
/*N*/                       if ( nY == (short) nVisEndY )
/*N*/                           pInfo->pThisBottom = pBox->GetBottom();
/*N*/                   }
/*N*/
/*N*/                   // Hintergrund kopieren (oder in output.cxx)
/*N*/
/*N*/                   if ( !pStartCond || pStartCond->
/*N*/                                   GetItemState(ATTR_BACKGROUND,TRUE,&pItem) != SFX_ITEM_SET )
/*N*/                       pItem = &pStartPattern->GetItem(ATTR_BACKGROUND);
/*N*/                   pInfo->pBackground = (const SvxBrushItem*) pItem;
/*N*/                   pRowInfo[nArrY].bEmptyBack = FALSE;
/*N*/
/*N*/                   // Schatten
/*N*/
/*N*/                   if ( !pStartCond || pStartCond->
/*N*/                                   GetItemState(ATTR_SHADOW,TRUE,&pItem) != SFX_ITEM_SET )
/*N*/                       pItem = &pStartPattern->GetItem(ATTR_SHADOW);
/*N*/                   pInfo->pShadowAttr = (const SvxShadowItem*) pItem;
/*N*/                   if (pInfo->pShadowAttr != pDefShadow)
/*N*/                       bAnyShadow = TRUE;
/*N*/
/*N*/                   // Blockmarken - wieder mit Original-Merge-Werten
/*N*/
/*N*/                   BOOL bCellMarked = FALSE;
/*N*/                   if (bPaintMarks)
/*?*/                       bCellMarked = ( nStartX >= (short) nBlockStartX
/*?*/                                   && nStartX <= (short) nBlockEndX
/*?*/                                   && nStartY >= (short) nBlockStartY
/*?*/                                   && nStartY <= (short) nBlockEndY );
/*N*/                   if (pMarkData && pMarkData->IsMultiMarked() && !bCellMarked)
/*N*/                   {
/*?*/                       const ScMarkArray* pThisMarkArr = pMarkData->GetArray()+nStartX;
/*?*/                       short nIndex;
/*?*/                       (void) pThisMarkArr->Search( nStartY, nIndex );
/*?*/                       bCellMarked=pThisMarkArr->pData[nIndex].bMarked;
/*N*/                   }
/*N*/
/*N*/                   pInfo->bMarked = bCellMarked;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bAnyLines)                                  // nach Merge Linien zusammenfassen
/*N*/   {
/*N*/       for (nArrY=0; nArrY<nArrCount; nArrY++)
/*N*/       {
/*N*/           RowInfo* pThisRowInfo = &pRowInfo[nArrY];
/*N*/ //            short nY = nArrY ? pRowInfo[nArrY].nRowNo : ((short)nY1)-1;
/*N*/
/*N*/           for (nArrX=nX1; nArrX<=nX2+2; nArrX++)                  // links und rechts einer mehr
/*N*/           {
/*N*/ //                short nX = ((short) nArrX) - 1;
/*N*/               CellInfo* pInfo = &pThisRowInfo->pCellInfo[nArrX];
/*N*/
/*N*/               if ( pInfo->pThisBottom || pInfo->pNextTop )
/*N*/               {
/*N*/                   if ( bPageMode && nArrY == 0 )
/*N*/                       pInfo->pBottomLine = pInfo->pNextTop;
/*N*/                   else if ( bPageMode && nArrY+2 >= nArrCount )
/*N*/                       pInfo->pBottomLine = pInfo->pThisBottom;
/*N*/                   else if (HasPriority(pInfo->pThisBottom,pInfo->pNextTop))
/*N*/                       pInfo->pBottomLine = pInfo->pThisBottom;
/*N*/                   else
/*N*/                       pInfo->pBottomLine = pInfo->pNextTop;
/*N*/               }
/*N*/               else
/*N*/                   pInfo->pBottomLine = NULL;                      //! Standard
/*N*/
/*N*/               if ( pInfo->pThisRight || pInfo->pNextLeft )
/*N*/               {
/*N*/                   if ( bPageMode && nArrX == nX1 )
/*N*/                       pInfo->pRightLine = pInfo->pNextLeft;
/*N*/                   else if ( bPageMode && nArrX > nX2 )
/*N*/                       pInfo->pRightLine = pInfo->pThisRight;
/*N*/                   else if (HasPriority(pInfo->pThisRight,pInfo->pNextLeft))
/*N*/                       pInfo->pRightLine = pInfo->pThisRight;
/*N*/                   else
/*N*/                       pInfo->pRightLine = pInfo->pNextLeft;
/*N*/               }
/*N*/               else
/*N*/                   pInfo->pRightLine = NULL;                       //! Standard
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bAnyShadow)                             // Schatten verteilen
/*N*/   {
/*?*/       for (nArrY=0; nArrY<nArrCount; nArrY++)
/*?*/       {
/*?*/           BOOL bTop = ( nArrY == 0 );
/*?*/           BOOL bBottom = ( nArrY+1 == nArrCount );
/*?*/
/*?*/ //            short nY = nArrY ? pRowInfo[nArrY].nRowNo : ((short)nY1)-1;
/*?*/
/*?*/           for (nArrX=nX1; nArrX<=nX2+2; nArrX++)                  // links und rechts einer mehr
/*?*/           {
/*?*/               BOOL bLeft = ( nArrX == nX1 );
/*?*/               BOOL bRight = ( nArrX == nX2+2 );
/*?*/
/*?*/ //                short nX = ((short) nArrX) - 1;
/*?*/               CellInfo* pInfo = &pRowInfo[nArrY].pCellInfo[nArrX];
/*?*/               const SvxShadowItem* pThisAttr = pInfo->pShadowAttr;
/*?*/               SvxShadowLocation eLoc = pThisAttr ? pThisAttr->GetLocation() : SVX_SHADOW_NONE;
/*?*/               if (eLoc != SVX_SHADOW_NONE)
/*?*/               {
/*?*/                   //  oder Test auf != eLoc
/*?*/
/*?*/                   short nDxPos = 1;
/*?*/                   short nDxNeg = -1;
/*?*/
/*?*/                   while ( nArrX+nDxPos < nX2+2 && pRowInfo[0].pCellInfo[nArrX+nDxPos].nWidth == 0 )
/*?*/                       ++nDxPos;
/*?*/                   while ( nArrX+nDxNeg > nX1 && pRowInfo[0].pCellInfo[nArrX+nDxNeg].nWidth == 0 )
/*?*/                       --nDxNeg;
/*?*/
/*?*/                   BOOL bLeftDiff = !bLeft &&
/*?*/                           CELLINFO(nDxNeg,0).pShadowAttr->GetLocation() == SVX_SHADOW_NONE;
/*?*/                   BOOL bRightDiff = !bRight &&
/*?*/                           CELLINFO(nDxPos,0).pShadowAttr->GetLocation() == SVX_SHADOW_NONE;
/*?*/                   BOOL bTopDiff = !bTop &&
/*?*/                           CELLINFO(0,-1).pShadowAttr->GetLocation() == SVX_SHADOW_NONE;
/*?*/                   BOOL bBottomDiff = !bBottom &&
/*?*/                           CELLINFO(0,1).pShadowAttr->GetLocation() == SVX_SHADOW_NONE;
/*?*/
/*?*/                   switch (eLoc)
/*?*/                   {
/*?*/                       case SVX_SHADOW_BOTTOMRIGHT:
/*?*/                           if (bBottomDiff)
/*?*/                           {
/*?*/                               CELLINFO(0,1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(0,1).eHShadowPart =
/*?*/                                               bLeftDiff ? SC_SHADOW_HSTART : SC_SHADOW_HORIZ;
/*?*/                           }
/*?*/                           if (bRightDiff)
/*?*/                           {
/*?*/                               CELLINFO(1,0).pVShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(1,0).eVShadowPart =
/*?*/                                               bTopDiff ? SC_SHADOW_VSTART : SC_SHADOW_VERT;
/*?*/                           }
/*?*/                           if (bBottomDiff && bRightDiff)
/*?*/                           {
/*?*/                               CELLINFO(1,1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(1,1).eHShadowPart = SC_SHADOW_CORNER;
/*?*/                           }
/*?*/                           break;
/*?*/
/*?*/                       case SVX_SHADOW_BOTTOMLEFT:
/*?*/                           if (bBottomDiff)
/*?*/                           {
/*?*/                               CELLINFO(0,1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(0,1).eHShadowPart =
/*?*/                                               bRightDiff ? SC_SHADOW_HSTART : SC_SHADOW_HORIZ;
/*?*/                           }
/*?*/                           if (bLeftDiff)
/*?*/                           {
/*?*/                               CELLINFO(-1,0).pVShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(-1,0).eVShadowPart =
/*?*/                                               bTopDiff ? SC_SHADOW_VSTART : SC_SHADOW_VERT;
/*?*/                           }
/*?*/                           if (bBottomDiff && bLeftDiff)
/*?*/                           {
/*?*/                               CELLINFO(-1,1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(-1,1).eHShadowPart = SC_SHADOW_CORNER;
/*?*/                           }
/*?*/                           break;
/*?*/
/*?*/                       case SVX_SHADOW_TOPRIGHT:
/*?*/                           if (bTopDiff)
/*?*/                           {
/*?*/                               CELLINFO(0,-1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(0,-1).eHShadowPart =
/*?*/                                               bLeftDiff ? SC_SHADOW_HSTART : SC_SHADOW_HORIZ;
/*?*/                           }
/*?*/                           if (bRightDiff)
/*?*/                           {
/*?*/                               CELLINFO(1,0).pVShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(1,0).eVShadowPart =
/*?*/                                               bBottomDiff ? SC_SHADOW_VSTART : SC_SHADOW_VERT;
/*?*/                           }
/*?*/                           if (bTopDiff && bRightDiff)
/*?*/                           {
/*?*/                               CELLINFO(1,-1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(1,-1).eHShadowPart = SC_SHADOW_CORNER;
/*?*/                           }
/*?*/                           break;
/*?*/
/*?*/                       case SVX_SHADOW_TOPLEFT:
/*?*/                           if (bTopDiff)
/*?*/                           {
/*?*/                               CELLINFO(0,-1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(0,-1).eHShadowPart =
/*?*/                                               bRightDiff ? SC_SHADOW_HSTART : SC_SHADOW_HORIZ;
/*?*/                           }
/*?*/                           if (bLeftDiff)
/*?*/                           {
/*?*/                               CELLINFO(-1,0).pVShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(-1,0).eVShadowPart =
/*?*/                                               bBottomDiff ? SC_SHADOW_VSTART : SC_SHADOW_VERT;
/*?*/                           }
/*?*/                           if (bTopDiff && bLeftDiff)
/*?*/                           {
/*?*/                               CELLINFO(-1,-1).pHShadowOrigin = pThisAttr;
/*?*/                               CELLINFO(-1,-1).eHShadowPart = SC_SHADOW_CORNER;
/*?*/                           }
/*?*/                           break;
/*?*/
/*?*/                       default:
/*?*/                           DBG_ERROR("falscher Shadow-Enum");
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   return nArrCount;
/*N*/ }



}
