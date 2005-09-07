/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_printfun.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 21:33:17 $
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
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
// auto strip #include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/svxids.hrc>
#include <bf_svx/adjitem.hxx>
#include <bf_svx/boxitem.hxx>
// auto strip #include <bf_svx/brshitem.hxx>
// auto strip #include <svtools/colorcfg.hxx>
#include <bf_svx/editstat.hxx>      // EE_CNTRL_RTFSTYLESHEETS
// auto strip #include <bf_svx/fmview.hxx>
#include <bf_svx/lrspitem.hxx>
#include <bf_svx/paperinf.hxx>
// auto strip #include <bf_svx/pbinitem.hxx>
#include <bf_svx/shaditem.hxx>
#include <bf_svx/sizeitem.hxx>
// auto strip #include <bf_svx/svdpagv.hxx>
#include <bf_svx/ulspitem.hxx>
// auto strip #include <bf_sfx2/app.hxx>
#include <bf_sfx2/printer.hxx>
// auto strip #include <bf_sfx2/progress.hxx>
// auto strip #include <tools/multisel.hxx>
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif

#ifdef MAC
#define RGBColor MAC_RGBColor
// auto strip #include <bf_svx/xoutbmp.hxx>
#undef RGBColor
#else
// auto strip #include <bf_svx/xoutbmp.hxx>
#endif


//#if defined( WIN ) || defined( WNT )
//#include <svwin.h>
//#endif


// auto strip #include "editutil.hxx"
#include "docsh.hxx"
// auto strip #include "output.hxx"
// auto strip #include "viewdata.hxx"
// auto strip #include "viewopti.hxx"
#include "stlpool.hxx"
// auto strip #include "pagepar.hxx"
#include "attrib.hxx"
#include "patattr.hxx"
#include "docpool.hxx"
#include "dociter.hxx"
#include "cell.hxx"
// auto strip #include "drawutil.hxx"
#include "globstr.hrc"
// auto strip #include "scresid.hxx"
#include "bf_sc.hrc"
// auto strip #include "pagedata.hxx"
#include "printopt.hxx"
// auto strip #include "prevloc.hxx"
// auto strip #include "scmod.hxx"

#define _PRINTFUN_CXX
#include "printfun.hxx"
namespace binfilter {



#define ZOOM_MIN    10

#define GET_BOOL(set,which)   ((const SfxBoolItem&)(set)->Get((which))).GetValue()
#define GET_USHORT(set,which) ((const SfxUInt16Item&)(set)->Get((which))).GetValue()
#define GET_SHOW(set,which)   ( VOBJ_MODE_SHOW == ScVObjMode( ((const ScViewObjectModeItem&)(set)->Get((which))).GetValue()) )

//------------------------------------------------------------------------

//STRIP001 ScPageRowEntry::ScPageRowEntry(const ScPageRowEntry& r)
//STRIP001 {
//STRIP001  nStartRow = r.nStartRow;
//STRIP001  nEndRow   = r.nEndRow;
//STRIP001  nPagesX   = r.nPagesX;
//STRIP001  if (r.pHidden && nPagesX)
//STRIP001  {
//STRIP001      pHidden = new BOOL[nPagesX];
//STRIP001      memcpy( pHidden, r.pHidden, nPagesX * sizeof(BOOL) );
//STRIP001  }
//STRIP001  else
//STRIP001      pHidden = NULL;
//STRIP001 }

//STRIP001 const ScPageRowEntry& ScPageRowEntry::operator=(const ScPageRowEntry& r)
//STRIP001 {
//STRIP001  delete[] pHidden;
//STRIP001
//STRIP001  nStartRow = r.nStartRow;
//STRIP001  nEndRow   = r.nEndRow;
//STRIP001  nPagesX   = r.nPagesX;
//STRIP001  if (r.pHidden && nPagesX)
//STRIP001  {
//STRIP001      pHidden = new BOOL[nPagesX];
//STRIP001      memcpy( pHidden, r.pHidden, nPagesX * sizeof(BOOL) );
//STRIP001  }
//STRIP001  else
//STRIP001      pHidden = NULL;
//STRIP001
//STRIP001  return *this;
//STRIP001 }

/*N*/ void ScPageRowEntry::SetPagesX(USHORT nNew)
/*N*/ {
/*N*/   if (pHidden)
/*N*/   {
/*N*/       DBG_ERROR("SetPagesX nicht nach SetHidden");
/*N*/       delete[] pHidden;
/*N*/       pHidden = NULL;
/*N*/   }
/*N*/   nPagesX = nNew;
/*N*/ }

//STRIP001 void ScPageRowEntry::SetHidden(USHORT nX)
//STRIP001 {
//STRIP001  if ( nX < nPagesX )
//STRIP001  {
//STRIP001      if ( nX+1 == nPagesX )  // letzte Seite?
//STRIP001          --nPagesX;
//STRIP001      else
//STRIP001      {
//STRIP001          if (!pHidden)
//STRIP001          {
//STRIP001              pHidden = new BOOL[nPagesX];
//STRIP001              memset( pHidden, FALSE, nPagesX * sizeof(BOOL) );
//STRIP001          }
//STRIP001          pHidden[nX] = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ScPageRowEntry::IsHidden(USHORT nX) const
//STRIP001 {
//STRIP001  return nX>=nPagesX || ( pHidden && pHidden[nX] );       //! inline?
//STRIP001 }

//STRIP001 USHORT ScPageRowEntry::CountVisible() const
//STRIP001 {
//STRIP001  if ( pHidden )
//STRIP001  {
//STRIP001      USHORT nVis = 0;
//STRIP001      for (USHORT i=0; i<nPagesX; i++)
//STRIP001          if (!pHidden[i])
//STRIP001              ++nVis;
//STRIP001      return nVis;
//STRIP001  }
//STRIP001  else
//STRIP001      return nPagesX;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ long lcl_LineTotal(const SvxBorderLine* pLine)
/*N*/ {
/*N*/   return pLine ? ( pLine->GetOutWidth() + pLine->GetInWidth() + pLine->GetDistance() ) : 0;
/*N*/ }

/*M*/ void ScPrintFunc::Construct( const ScPrintOptions* pOptions )
/*M*/ {
/*M*/   pDoc = pDocShell->GetDocument();
/*M*/
/*M*/   SfxPrinter* pDocPrinter = pDoc->GetPrinter();   // auch fuer Preview den Drucker nehmen
/*M*/   if (pDocPrinter)
/*M*/       aOldPrinterMode = pDocPrinter->GetMapMode();
/*M*/
/*M*/   //  einheitlicher MapMode ueber alle Aufrufe (z.B. Repaint !!!),
/*M*/   //  weil die EditEngine sonst unterschiedliche Texthoehen liefert
/*M*/   pDev->SetMapMode(MAP_PIXEL);
/*M*/
/*M*/   pPageEndX = NULL;
/*M*/   pPageEndY = NULL;
/*M*/   pPageRows = NULL;
/*M*/   pBorderItem = NULL;
/*M*/   pBackgroundItem = NULL;
/*M*/   pShadowItem = NULL;
/*M*/
/*M*/   pEditEngine = NULL;
/*M*/   pEditDefaults = NULL;
/*M*/
/*M*/   ScStyleSheetPool* pStylePool    = pDoc->GetStyleSheetPool();
/*M*/   SfxStyleSheetBase* pStyleSheet  = pStylePool->Find(
/*M*/                                           pDoc->GetPageStyle( nPrintTab ),
/*M*/                                           SFX_STYLE_FAMILY_PAGE );
/*M*/   if (pStyleSheet)
/*M*/       pParamSet = &pStyleSheet->GetItemSet();
/*M*/   else
/*M*/   {
/*M*/       DBG_ERROR("Seitenvorlage nicht gefunden" );
/*M*/       pParamSet = NULL;
/*M*/   }
/*M*/
/*M*/   if (!bState)
/*M*/       nZoom = 100;
/*M*/   nManualZoom = 100;
/*M*/   bClearWin = FALSE;
/*M*/   bUseStyleColor = FALSE;
/*M*/   bIsRender = FALSE;
/*M*/
/*M*/   InitParam(pOptions);
/*M*/
/*M*/   pPageData = NULL;       // wird nur zur Initialisierung gebraucht
/*M*/ }

/*N*/ ScPrintFunc::ScPrintFunc( ScDocShell* pShell, SfxPrinter* pNewPrinter, USHORT nTab,
/*N*/                           long nPage, long nDocP, const ScRange* pArea,
/*N*/                           const ScPrintOptions* pOptions,
/*N*/                           ScPageBreakData* pData )
/*N*/   :   pDocShell           ( pShell ),
/*N*/       pPrinter            ( pNewPrinter ),
/*N*/       pDrawView           ( NULL ),
/*N*/       nPrintTab           ( nTab ),
/*N*/       nPageStart          ( nPage ),
/*N*/       nDocPages           ( nDocP ),
/*N*/       pUserArea           ( pArea ),
/*N*/       pPageData           ( pData ),
/*N*/       nTotalPages         ( 0 ),
/*N*/       nTabPages           ( 0 ),
/*N*/       bState              ( FALSE ),
/*N*/       bPrintCurrentTable  ( FALSE ),
/*N*/       bMultiArea          ( FALSE ),
/*N*/       bSourceRangeValid   ( FALSE )
/*N*/ {
/*N*/   pDev = pPrinter;
/*N*/   aSrcOffset = pPrinter->PixelToLogic( pPrinter->GetPageOffsetPixel(), MAP_100TH_MM );
/*N*/   Construct( pOptions );
/*N*/ }

/*N*/ ScPrintFunc::ScPrintFunc( OutputDevice* pOutDev, ScDocShell* pShell, USHORT nTab,
/*N*/                           long nPage, long nDocP, const ScRange* pArea,
/*N*/                           const ScPrintOptions* pOptions )
/*N*/   :   pDocShell           ( pShell ),
/*N*/       pPrinter            ( NULL ),
/*N*/       pDrawView           ( NULL ),
/*N*/       nPrintTab           ( nTab ),
/*N*/       nPageStart          ( nPage ),
/*N*/       nDocPages           ( nDocP ),
/*N*/       pUserArea           ( pArea ),
/*N*/       pPageData           ( NULL ),
/*N*/       nTotalPages         ( 0 ),
/*N*/       nTabPages           ( 0 ),
/*N*/       bState              ( FALSE ),
/*N*/       bPrintCurrentTable  ( FALSE ),
/*N*/       bMultiArea          ( FALSE ),
/*N*/       bSourceRangeValid   ( FALSE )
/*N*/ {
/*N*/   pDev = pOutDev;
/*N*/   Construct( pOptions );
/*N*/ }

//STRIP001 ScPrintFunc::ScPrintFunc( OutputDevice* pOutDev, ScDocShell* pShell,
//STRIP001                           const ScPrintState& rState, const ScPrintOptions* pOptions )
//STRIP001  :   pDocShell           ( pShell ),
//STRIP001      pPrinter            ( NULL ),
//STRIP001      pDrawView           ( NULL ),
//STRIP001      pUserArea           ( NULL ),
//STRIP001      pPageData           ( NULL ),
//STRIP001      bPrintCurrentTable  ( FALSE ),
//STRIP001      bMultiArea          ( FALSE ),
//STRIP001      bSourceRangeValid   ( FALSE )
//STRIP001 {
//STRIP001  pDev = pOutDev;
//STRIP001
//STRIP001  nPrintTab   = rState.nPrintTab;
//STRIP001  nStartCol   = rState.nStartCol;
//STRIP001  nStartRow   = rState.nStartRow;
//STRIP001  nEndCol     = rState.nEndCol;
//STRIP001  nEndRow     = rState.nEndRow;
//STRIP001  nZoom       = rState.nZoom;
//STRIP001  nPagesX     = rState.nPagesX;
//STRIP001  nPagesY     = rState.nPagesY;
//STRIP001  nTabPages   = rState.nTabPages;
//STRIP001  nTotalPages = rState.nTotalPages;
//STRIP001  nPageStart  = rState.nPageStart;
//STRIP001  nDocPages   = rState.nDocPages;
//STRIP001  bState      = TRUE;
//STRIP001
//STRIP001  Construct( pOptions );
//STRIP001 }

//STRIP001 void ScPrintFunc::GetPrintState( ScPrintState& rState )
//STRIP001 {
//STRIP001  rState.nPrintTab    = nPrintTab;
//STRIP001  rState.nStartCol    = nStartCol;
//STRIP001  rState.nStartRow    = nStartRow;
//STRIP001  rState.nEndCol      = nEndCol;
//STRIP001  rState.nEndRow      = nEndRow;
//STRIP001  rState.nZoom        = nZoom;
//STRIP001  rState.nPagesX      = nPagesX;
//STRIP001  rState.nPagesY      = nPagesY;
//STRIP001  rState.nTabPages    = nTabPages;
//STRIP001  rState.nTotalPages  = nTotalPages;
//STRIP001  rState.nPageStart   = nPageStart;
//STRIP001  rState.nDocPages    = nDocPages;
//STRIP001 }

//STRIP001 BOOL ScPrintFunc::GetLastSourceRange( ScRange& rRange ) const
//STRIP001 {
//STRIP001  rRange = aLastSourceRange;
//STRIP001  return bSourceRangeValid;
//STRIP001 }

//STRIP001 void ScPrintFunc::FillPageData()
//STRIP001 {
//STRIP001  if (pPageData)
//STRIP001  {
//STRIP001      USHORT nCount = pPageData->GetCount();
//STRIP001      ScPrintRangeData& rData = pPageData->GetData(nCount);       // hochzaehlen
//STRIP001
//STRIP001      rData.SetPrintRange( ScRange( nStartCol, nStartRow, nPrintTab,
//STRIP001                                      nEndCol, nEndRow, nPrintTab ) );
//STRIP001      rData.SetPagesX( nPagesX, pPageEndX );
//STRIP001      rData.SetPagesY( nTotalY, pPageEndY );
//STRIP001
//STRIP001      //  Einstellungen
//STRIP001      rData.SetTopDown( aTableParam.bTopDown );
//STRIP001      rData.SetAutomatic( !aAreaParam.bPrintArea );
//STRIP001  }
//STRIP001 }

/*N*/ ScPrintFunc::~ScPrintFunc()
/*N*/ {
/*N*/   ScTripel* pTripel = (ScTripel*) aNotePosList.First();
/*N*/   while (pTripel)
/*N*/   {
/*?*/       delete pTripel;
/*?*/       pTripel = (ScTripel*) aNotePosList.Next();
/*N*/   }
/*N*/   aNotePosList.Clear();
/*N*/
/*N*/   delete[] pPageEndX;
/*N*/   delete[] pPageEndY;
/*N*/   delete[] pPageRows;
/*N*/   delete pEditDefaults;
/*N*/   delete pEditEngine;
/*N*/
/*N*/   //  Druckereinstellungen werden jetzt von aussen wiederhergestellt
/*N*/
/*N*/   //  #64294# Fuer DrawingLayer/Charts muss der MapMode am Drucker (RefDevice) immer stimmen
/*N*/   SfxPrinter* pDocPrinter = pDoc->GetPrinter();   // auch fuer Preview den Drucker nehmen
/*N*/   if (pDocPrinter)
/*N*/       pDocPrinter->SetMapMode(aOldPrinterMode);
/*N*/ }

/*N*/ void ScPrintFunc::SetDrawView( FmFormView* pNew )
/*N*/ {
/*N*/   pDrawView = pNew;
/*N*/ }

//STRIP001 void lcl_HidePrint( RowInfo* pRowInfo, USHORT nArrCount, USHORT nX1, USHORT nX2 )
//STRIP001 {
//STRIP001  for (USHORT nArrY=1; nArrY+1<nArrCount; nArrY++)
//STRIP001  {
//STRIP001      RowInfo* pThisRowInfo = &pRowInfo[nArrY];
//STRIP001      for (USHORT nX=nX1; nX<=nX2; nX++)
//STRIP001      {
//STRIP001          const CellInfo& rCellInfo = pThisRowInfo->pCellInfo[nX+1];
//STRIP001          if (!rCellInfo.bEmptyCellText)
//STRIP001              if (((const ScProtectionAttr&)rCellInfo.pPatternAttr->
//STRIP001                          GetItem(ATTR_PROTECTION, rCellInfo.pConditionSet)).GetHidePrint())
//STRIP001              {
//STRIP001                  pThisRowInfo->pCellInfo[nX+1].pCell          = NULL;
//STRIP001                  pThisRowInfo->pCellInfo[nX+1].bEmptyCellText = TRUE;
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//
//          Ausgabe auf Device (static)
//
//      wird benutzt fuer:
//      -   Clipboard/Bitmap
//      -   Ole-Object (DocShell::Draw)
//      -   Vorschau bei Vorlagen

//STRIP001 void ScPrintFunc::DrawToDev( ScDocument* pDoc, OutputDevice* pDev, double nPrintFactor,
//STRIP001                          const Rectangle& rBound, ScViewData* pViewData, BOOL bMetaFile )
//STRIP001 {
//STRIP001  //! nPrintFactor auswerten !!!
//STRIP001
//STRIP001  USHORT nTab = 0;
//STRIP001  if (pViewData)
//STRIP001      nTab = pViewData->GetTabNo();
//STRIP001
//STRIP001  BOOL bDoGrid, bNullVal, bFormula;
//STRIP001  ScStyleSheetPool* pStylePool = pDoc->GetStyleSheetPool();
//STRIP001  SfxStyleSheetBase* pStyleSheet = pStylePool->Find( pDoc->GetPageStyle( nTab ), SFX_STYLE_FAMILY_PAGE );
//STRIP001  if (pStyleSheet)
//STRIP001  {
//STRIP001      SfxItemSet& rSet = pStyleSheet->GetItemSet();
//STRIP001      bDoGrid  = ((const SfxBoolItem&)rSet.Get(ATTR_PAGE_GRID)).GetValue();
//STRIP001      bNullVal = ((const SfxBoolItem&)rSet.Get(ATTR_PAGE_NULLVALS)).GetValue();
//STRIP001      bFormula = ((const SfxBoolItem&)rSet.Get(ATTR_PAGE_FORMULAS)).GetValue();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const ScViewOptions& rOpt = pDoc->GetViewOptions();
//STRIP001      bDoGrid  = rOpt.GetOption(VOPT_GRID);
//STRIP001      bNullVal = rOpt.GetOption(VOPT_NULLVALS);
//STRIP001      bFormula = rOpt.GetOption(VOPT_FORMULAS);
//STRIP001  }
//STRIP001
//STRIP001  MapMode aMode = pDev->GetMapMode();
//STRIP001
//STRIP001  Rectangle aRect = rBound;
//STRIP001
//STRIP001  if (aRect.Right() < aRect.Left() || aRect.Bottom() < aRect.Top())
//STRIP001      aRect = Rectangle( Point(), pDev->GetOutputSize() );
//STRIP001
//STRIP001  USHORT nX1 = 0;
//STRIP001  USHORT nY1 = 0;
//STRIP001  USHORT nX2 = OLE_STD_CELLS_X - 1;
//STRIP001  USHORT nY2 = OLE_STD_CELLS_Y - 1;
//STRIP001  if (bMetaFile)
//STRIP001  {
//STRIP001      ScRange aRange = pDoc->GetRange( nTab, rBound );
//STRIP001      nX1 = aRange.aStart.Col();
//STRIP001      nY1 = aRange.aStart.Row();
//STRIP001      nX2 = aRange.aEnd.Col();
//STRIP001      nY2 = aRange.aEnd.Row();
//STRIP001  }
//STRIP001  else if (pViewData)
//STRIP001  {
//STRIP001      ScSplitPos eWhich = pViewData->GetActivePart();
//STRIP001      ScHSplitPos eHWhich = WhichH(eWhich);
//STRIP001      ScVSplitPos eVWhich = WhichV(eWhich);
//STRIP001      nX1 = pViewData->GetPosX(eHWhich);
//STRIP001      nY1 = pViewData->GetPosY(eVWhich);
//STRIP001      nX2 = nX1 + pViewData->VisibleCellsX(eHWhich);
//STRIP001      if (nX2>nX1) --nX2;
//STRIP001      nY2 = nY1 + pViewData->VisibleCellsY(eVWhich);
//STRIP001      if (nY2>nY1) --nY2;
//STRIP001  }
//STRIP001
//STRIP001  if (nX1 > MAXCOL) nX1 = MAXCOL;
//STRIP001  if (nX2 > MAXCOL) nX2 = MAXCOL;
//STRIP001  if (nY1 > MAXROW) nY1 = MAXROW;
//STRIP001  if (nY2 > MAXROW) nY2 = MAXROW;
//STRIP001
//STRIP001  USHORT i;
//STRIP001  long nDevSizeX = aRect.Right()-aRect.Left()+1;
//STRIP001  long nDevSizeY = aRect.Bottom()-aRect.Top()+1;
//STRIP001
//STRIP001  Rectangle aLines;
//STRIP001  ScRange aRange( nX1,nY1,nTab, nX2,nY2,nTab );
//STRIP001  BOOL bAddLines = pDoc->HasLines( aRange, aLines );
//STRIP001
//STRIP001  long nTwipsSizeX = 0;
//STRIP001  for (i=nX1; i<=nX2; i++)
//STRIP001      nTwipsSizeX += pDoc->GetColWidth( i, nTab );
//STRIP001  long nTwipsSizeY = 0;
//STRIP001  for (i=nY1; i<=nY2; i++)
//STRIP001      nTwipsSizeY += pDoc->GetRowHeight( i, nTab );
//STRIP001
//STRIP001  //  wenn keine Linien, dann trotzdem Platz fuer den Aussenrahmen (20 Twips = 1pt)
//STRIP001  //  (HasLines initalisiert aLines auf 0,0,0,0)
//STRIP001  nTwipsSizeX += aLines.Left() + Max( aLines.Right(), 20L );
//STRIP001  nTwipsSizeY += aLines.Top() +  Max( aLines.Bottom(), 20L );
//STRIP001
//STRIP001  double nScaleX = (double) nDevSizeX / nTwipsSizeX;
//STRIP001  double nScaleY = (double) nDevSizeY / nTwipsSizeY;
//STRIP001
//STRIP001                          //!     Flag bei FillInfo uebergeben !!!!!
//STRIP001  ScTripel aEStart;
//STRIP001  ScTripel aEEnd;
//STRIP001  BOOL bEmbed = pDoc->IsEmbedded();
//STRIP001  if (bEmbed)
//STRIP001  {
//STRIP001      pDoc->GetEmbedded(aEStart,aEEnd);
//STRIP001      pDoc->ResetEmbedded();
//STRIP001  }
//STRIP001
//STRIP001  //  Daten zusammenstellen
//STRIP001
//STRIP001  RowInfo* pRowInfo = new RowInfo[ROWINFO_MAX];
//STRIP001  USHORT nArrCount = pDoc->FillInfo( pRowInfo, nX1, nY1, nX2, nY2, nTab,
//STRIP001                                      nScaleX, nScaleY, FALSE, bFormula );
//STRIP001  lcl_HidePrint( pRowInfo, nArrCount, nX1, nX2 );
//STRIP001
//STRIP001  if (bEmbed)
//STRIP001      pDoc->SetEmbedded(aEStart,aEEnd);

/*  if (!bMetaFile)
        pDev->SetMapMode(MAP_PIXEL);
*/
//STRIP001  long nScrX = aRect.Left();
//STRIP001  long nScrY = aRect.Top();
//STRIP001
//STRIP001  //  Wenn keine Linien, trotzdem Platz fuer Gitterlinien lassen
//STRIP001  //  (werden sonst abgeschnitten)
//STRIP001  long nAddX = (long)( aLines.Left() * nScaleX );
//STRIP001  nScrX += ( nAddX ? nAddX : 1 );
//STRIP001  long nAddY = (long)( aLines.Top() * nScaleY );
//STRIP001  nScrY += ( nAddY ? nAddY : 1 );
//STRIP001
//STRIP001  ScOutputData aOutputData( pDev, OUTTYPE_PRINTER, pRowInfo, nArrCount, pDoc, nTab,
//STRIP001                              nScrX, nScrY, nX1, nY1, nX2, nY2, nScaleX, nScaleY );
//STRIP001  aOutputData.SetMetaFileMode(bMetaFile);
//STRIP001  aOutputData.SetShowNullValues(bNullVal);
//STRIP001  aOutputData.SetShowFormulas(bFormula);
//STRIP001
//STRIP001  //! SetUseStyleColor ??
//STRIP001
//STRIP001  if ( bMetaFile && pDev->GetOutDevType() == OUTDEV_VIRDEV )
//STRIP001      aOutputData.SetSnapPixel();
//STRIP001
//STRIP001  Point aLogStart = pDev->PixelToLogic( Point(nScrX,nScrY), MAP_100TH_MM );
//STRIP001  long nLogStX = aLogStart.X();
//STRIP001  long nLogStY = aLogStart.Y();
//STRIP001
//STRIP001  //!     nZoom fuer GetFont in OutputData ???
//STRIP001
//STRIP001  if (!bMetaFile && pViewData)
//STRIP001      pDev->SetMapMode(pViewData->GetLogicMode(pViewData->GetActivePart()));
//STRIP001  aOutputData.DrawingLayer(SC_LAYER_BACK,SC_OBJECTS_ALL,nLogStX,nLogStY);
//STRIP001  if (!bMetaFile && pViewData)
//STRIP001      pDev->SetMapMode(aMode);
//STRIP001
//STRIP001  aOutputData.DrawBackground();
//STRIP001
//STRIP001 #ifdef OS2
//STRIP001  if (bMetaFile && !bDoGrid)
//STRIP001  {
//STRIP001                  // unter OS2 fuer Metafiles gesamte Flaeche benutzen,
//STRIP001                  // weil sonst die Groesse nicht erkannt wird
//STRIP001      pDev->SetLineColor();
//STRIP001      pDev->SetFillColor();
//STRIP001      pDev->DrawRect( Rectangle( nScrX,nScrY,
//STRIP001                      nScrX+aOutputData.GetScrW(), nScrY+aOutputData.GetScrH() ) );
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  aOutputData.DrawShadow();
//STRIP001  aOutputData.DrawFrame();
//STRIP001  aOutputData.DrawStrings();
//STRIP001
//STRIP001  if (!bMetaFile && pViewData)
//STRIP001      pDev->SetMapMode(pViewData->GetLogicMode(pViewData->GetActivePart()));
//STRIP001
//STRIP001  aOutputData.DrawEdit(!bMetaFile);
//STRIP001
//STRIP001  if (bDoGrid)
//STRIP001  {
//STRIP001      if (!bMetaFile && pViewData)
//STRIP001          pDev->SetMapMode(aMode);
//STRIP001
//STRIP001      aOutputData.DrawGrid( TRUE, FALSE );    // keine Seitenumbrueche
//STRIP001
//STRIP001      pDev->SetLineColor( COL_BLACK );
//STRIP001
//STRIP001      Size aOne = pDev->PixelToLogic( Size(1,1) );
//STRIP001      if (bMetaFile)
//STRIP001          aOne = Size(1,1);   // kompatibel zu DrawGrid
//STRIP001      pDev->DrawLine( Point(nScrX,nScrY), Point(nScrX,nScrY+aOutputData.GetScrH()-aOne.Width() ) );
//STRIP001      pDev->DrawLine( Point(nScrX,nScrY), Point(nScrX+aOutputData.GetScrW()-aOne.Height(),nScrY ) );
//STRIP001  }
//STRIP001
//STRIP001  aOutputData.DrawingLayer(SC_LAYER_FRONT,SC_OBJECTS_ALL,nLogStX,nLogStY);
//STRIP001  aOutputData.DrawingLayer(SC_LAYER_INTERN,SC_OBJECTS_ALL,nLogStX,nLogStY);
//STRIP001
//STRIP001  for (i=0; i<nArrCount; i++)
//STRIP001      delete[] pRowInfo[i].pCellInfo;
//STRIP001  delete[] pRowInfo;
//STRIP001 }

//
//          Drucken
//

/*N*/ void lcl_FillHFParam( ScPrintHFParam& rParam, const SfxItemSet* pHFSet )
/*N*/ {
/*N*/   //  nDistance muss vorher unterschiedlich initalisiert sein
/*N*/
/*N*/   if ( pHFSet == NULL )
/*N*/   {
/*N*/       rParam.bEnable  = FALSE;
/*N*/       rParam.pBorder  = NULL;
/*N*/       rParam.pBack    = NULL;
/*N*/       rParam.pShadow  = NULL;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rParam.bEnable  = ((const SfxBoolItem&) pHFSet->Get(ATTR_PAGE_ON)).GetValue();
/*N*/       rParam.bDynamic = ((const SfxBoolItem&) pHFSet->Get(ATTR_PAGE_DYNAMIC)).GetValue();
/*N*/       rParam.bShared  = ((const SfxBoolItem&) pHFSet->Get(ATTR_PAGE_SHARED)).GetValue();
/*N*/       rParam.nHeight  = ((const SvxSizeItem&) pHFSet->Get(ATTR_PAGE_SIZE)).GetSize().Height();
/*N*/       const SvxLRSpaceItem* pHFLR = &(const SvxLRSpaceItem&) pHFSet->Get(ATTR_LRSPACE);
/*N*/       long nTmp;
/*N*/       nTmp = pHFLR->GetLeft();
/*N*/       rParam.nLeft = nTmp < 0 ? 0 : USHORT(nTmp);
/*N*/       nTmp = pHFLR->GetRight();
/*N*/       rParam.nRight = nTmp < 0 ? 0 : USHORT(nTmp);
/*N*/       rParam.pBorder  = (const SvxBoxItem*)   &pHFSet->Get(ATTR_BORDER);
/*N*/       rParam.pBack    = (const SvxBrushItem*) &pHFSet->Get(ATTR_BACKGROUND);
/*N*/       rParam.pShadow  = (const SvxShadowItem*)&pHFSet->Get(ATTR_SHADOW);;
/*N*/
/*N*/ //    jetzt doch wieder schon im Dialog:
/*N*/ //        rParam.nHeight += rParam.nDistance;             // nicht mehr im Dialog ???
/*N*/
/*N*/       if (rParam.pBorder)
/*N*/           rParam.nHeight += lcl_LineTotal( rParam.pBorder->GetTop() ) +
/*N*/                             lcl_LineTotal( rParam.pBorder->GetBottom() );
/*N*/
/*N*/       rParam.nManHeight = rParam.nHeight;
/*N*/   }
/*N*/
/*N*/   if (!rParam.bEnable)
/*N*/       rParam.nHeight = 0;
/*N*/ }

//  bNew = TRUE:    benutzten Bereich aus dem Dokument suchen
//  bNew = FALSE:   nur ganze Zeilen/Spalten begrenzen

/*N*/ BOOL ScPrintFunc::AdjustPrintArea( BOOL bNew )
/*N*/ {
/*N*/   USHORT nOldEndCol = nEndCol;    // nur wichtig bei !bNew
/*N*/   USHORT nOldEndRow = nEndRow;
/*N*/   BOOL bChangeCol = TRUE;         // bei bNew werden beide angepasst
/*N*/   BOOL bChangeRow = TRUE;
/*N*/
/*N*/   BOOL bNotes = aTableParam.bNotes;
/*N*/   if ( bNew )
/*N*/   {
/*N*/       nStartCol = nStartRow = 0;
/*N*/       if (!pDoc->GetPrintArea( nPrintTab, nEndCol, nEndRow, bNotes ))
/*N*/           return FALSE;   // nix
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       BOOL bFound = TRUE;
/*N*/       bChangeCol = ( nStartCol == 0 && nEndCol == MAXCOL );
/*N*/       bChangeRow = ( nStartRow == 0 && nEndRow == MAXROW );
/*N*/       if ( bChangeCol && bChangeRow )
/*?*/           bFound = pDoc->GetPrintArea( nPrintTab, nEndCol, nEndRow, bNotes );
/*N*/       else if ( bChangeCol )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 bFound = pDoc->GetPrintAreaHor( nPrintTab, nStartRow, nEndRow, nEndCol, bNotes );
/*N*/       else if ( bChangeRow )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");}//STRIP001 bFound = pDoc->GetPrintAreaVer( nPrintTab, nStartCol, nEndCol, nEndRow, bNotes );
/*N*/
/*N*/       if (!bFound)
/*N*/           return FALSE;   // leer
/*N*/   }
/*N*/
/*N*/   pDoc->ExtendMerge( nStartCol,nStartRow, nEndCol,nEndRow, nPrintTab,
/*N*/                       FALSE, TRUE );      // kein Refresh, incl. Attrs
/*N*/
/*N*/   if ( bChangeCol )
/*N*/   {
/*N*/       OutputDevice* pRefDev = pDoc->GetPrinter();     // auch fuer Preview den Drucker nehmen
/*N*/       pRefDev->SetMapMode( MAP_PIXEL );               // wichtig fuer GetNeededSize
/*N*/
/*N*/       pDoc->ExtendPrintArea( pRefDev,
/*N*/                           nPrintTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/       //  nEndCol wird veraendert
/*N*/   }
/*N*/
/*N*/   if ( nEndCol < MAXCOL && pDoc->HasAttrib(
/*N*/                   nEndCol,nStartRow,nPrintTab, nEndCol,nEndRow,nPrintTab, HASATTR_SHADOW_RIGHT ) )
/*N*/       ++nEndCol;
/*N*/   if ( nEndRow < MAXROW && pDoc->HasAttrib(
/*N*/                   nStartCol,nEndRow,nPrintTab, nEndCol,nEndRow,nPrintTab, HASATTR_SHADOW_DOWN ) )
/*N*/       ++nEndRow;
/*N*/
/*N*/   if (!bChangeCol) nEndCol = nOldEndCol;
/*N*/   if (!bChangeRow) nEndRow = nOldEndRow;
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ long ScPrintFunc::TextHeight( const EditTextObject* pObject )
/*N*/ {
/*N*/   if (!pObject)
/*N*/       return 0;
/*N*/
/*N*/ //    pEditEngine->SetPageNo( nTotalPages );
/*N*/   pEditEngine->SetTextNewDefaults( *pObject, *pEditDefaults, FALSE );
/*N*/
/*N*/   return (long) pEditEngine->GetTextHeight();
/*N*/ }

//  nZoom muss gesetzt sein !!!
//  und der entsprechende Twip-MapMode eingestellt

/*N*/ void ScPrintFunc::UpdateHFHeight( ScPrintHFParam& rParam )
/*N*/ {
/*N*/   DBG_ASSERT( aPageSize.Width(), "UpdateHFHeight ohne aPageSize");
/*N*/
/*N*/   if (rParam.bEnable && rParam.bDynamic)
/*N*/   {
/*N*/       //  nHeight aus Inhalten berechnen
/*N*/
/*N*/       MakeEditEngine();
/*N*/       long nPaperWidth = ( aPageSize.Width() - nLeftMargin - nRightMargin -
/*N*/                               rParam.nLeft - rParam.nRight ) * 100 / nZoom;
/*N*/       if (rParam.pBorder)
/*N*/           nPaperWidth -= ( rParam.pBorder->GetDistance(BOX_LINE_LEFT) +
/*N*/                            rParam.pBorder->GetDistance(BOX_LINE_RIGHT) +
/*N*/                            lcl_LineTotal(rParam.pBorder->GetLeft()) +
/*N*/                            lcl_LineTotal(rParam.pBorder->GetRight()) ) * 100 / nZoom;
/*N*/
/*N*/       if (rParam.pShadow && rParam.pShadow->GetLocation() != SVX_SHADOW_NONE)
/*N*/           nPaperWidth -= ( rParam.pShadow->CalcShadowSpace(SHADOW_LEFT) +
/*N*/                            rParam.pShadow->CalcShadowSpace(SHADOW_RIGHT) ) * 100L / nZoom;
/*N*/
/*N*/       pEditEngine->SetPaperSize( Size( nPaperWidth, 10000 ) );
/*N*/
/*N*/       long nMaxHeight = 0;
/*N*/       if ( rParam.pLeft )
/*N*/       {
/*N*/           nMaxHeight = Max( nMaxHeight, TextHeight( rParam.pLeft->GetLeftArea() ) );
/*N*/           nMaxHeight = Max( nMaxHeight, TextHeight( rParam.pLeft->GetCenterArea() ) );
/*N*/           nMaxHeight = Max( nMaxHeight, TextHeight( rParam.pLeft->GetRightArea() ) );
/*N*/       }
/*N*/       if ( rParam.pRight )
/*N*/       {
/*N*/           nMaxHeight = Max( nMaxHeight, TextHeight( rParam.pRight->GetLeftArea() ) );
/*N*/           nMaxHeight = Max( nMaxHeight, TextHeight( rParam.pRight->GetCenterArea() ) );
/*N*/           nMaxHeight = Max( nMaxHeight, TextHeight( rParam.pRight->GetRightArea() ) );
/*N*/       }
/*N*/
/*N*/       rParam.nHeight = nMaxHeight + rParam.nDistance;
/*N*/       if (rParam.pBorder)
/*N*/           rParam.nHeight += rParam.pBorder->GetDistance(BOX_LINE_TOP) +
/*N*/                             rParam.pBorder->GetDistance(BOX_LINE_BOTTOM) +
/*N*/                             lcl_LineTotal( rParam.pBorder->GetTop() ) +
/*N*/                             lcl_LineTotal( rParam.pBorder->GetBottom() );
/*N*/       if (rParam.pShadow && rParam.pShadow->GetLocation() != SVX_SHADOW_NONE)
/*N*/           rParam.nHeight += rParam.pShadow->CalcShadowSpace(SHADOW_TOP) +
/*N*/                             rParam.pShadow->CalcShadowSpace(SHADOW_BOTTOM);
/*N*/
/*N*/       if (rParam.nHeight < rParam.nManHeight)
/*N*/           rParam.nHeight = rParam.nManHeight;         // eingestelltes Minimum
/*N*/   }
/*N*/ }

/*N*/ void ScPrintFunc::InitParam( const ScPrintOptions* pOptions )
/*N*/ {
/*N*/   if (!pParamSet)
/*N*/       return;
/*N*/
/*N*/                               // TabPage "Seite"
/*N*/   const SvxLRSpaceItem* pLRItem = (const SvxLRSpaceItem*) &pParamSet->Get( ATTR_LRSPACE );
/*N*/   long nTmp;
/*N*/   nTmp = pLRItem->GetLeft();
/*N*/   nLeftMargin = nTmp < 0 ? 0 : USHORT(nTmp);
/*N*/   nTmp = pLRItem->GetRight();
/*N*/   nRightMargin = nTmp < 0 ? 0 : USHORT(nTmp);
/*N*/   const SvxULSpaceItem* pULItem = (const SvxULSpaceItem*) &pParamSet->Get( ATTR_ULSPACE );
/*N*/   nTopMargin    = pULItem->GetUpper();
/*N*/   nBottomMargin = pULItem->GetLower();
/*N*/
/*N*/   const SvxPageItem* pPageItem = (const SvxPageItem*) &pParamSet->Get( ATTR_PAGE );
/*N*/   nPageUsage          = pPageItem->GetPageUsage();
/*N*/   bLandscape          = pPageItem->IsLandscape();
/*N*/   aFieldData.eNumType = pPageItem->GetNumType();
/*N*/
/*N*/   bCenterHor = ((const SfxBoolItem&) pParamSet->Get(ATTR_PAGE_HORCENTER)).GetValue();
/*N*/   bCenterVer = ((const SfxBoolItem&) pParamSet->Get(ATTR_PAGE_VERCENTER)).GetValue();
/*N*/
/*N*/   aPageSize = ((const SvxSizeItem&) pParamSet->Get(ATTR_PAGE_SIZE)).GetSize();
/*N*/   if ( !aPageSize.Width() || !aPageSize.Height() )
/*N*/   {
/*?*/       DBG_ERROR("PageSize Null ?!?!?");
/*?*/       aPageSize = SvxPaperInfo::GetPaperSize( SVX_PAPER_A4 );
/*N*/   }
/*N*/
/*N*/   pBorderItem     = (const SvxBoxItem*)    &pParamSet->Get(ATTR_BORDER);
/*N*/   pBackgroundItem = (const SvxBrushItem*)  &pParamSet->Get(ATTR_BACKGROUND);
/*N*/   pShadowItem     = (const SvxShadowItem*) &pParamSet->Get(ATTR_SHADOW);
/*N*/
/*N*/                               // TabPage "Kopfzeile"
/*N*/
/*N*/   aHdr.pLeft      = (const ScPageHFItem*) &pParamSet->Get(ATTR_PAGE_HEADERLEFT);      // Inhalt
/*N*/   aHdr.pRight     = (const ScPageHFItem*) &pParamSet->Get(ATTR_PAGE_HEADERRIGHT);
/*N*/
/*N*/   const SvxSetItem* pHeaderSetItem;
/*N*/   const SfxItemSet* pHeaderSet = NULL;
/*N*/   if ( pParamSet->GetItemState( ATTR_PAGE_HEADERSET, FALSE,
/*N*/                           (const SfxPoolItem**)&pHeaderSetItem ) == SFX_ITEM_SET )
/*N*/   {
/*N*/       pHeaderSet = &pHeaderSetItem->GetItemSet();
/*N*/                                                       // Kopfzeile hat unteren Abstand
/*N*/       aHdr.nDistance  = ((const SvxULSpaceItem&) pHeaderSet->Get(ATTR_ULSPACE)).GetLower();
/*N*/   }
/*N*/   lcl_FillHFParam( aHdr, pHeaderSet );
/*N*/
/*N*/                               // TabPage "Fusszeile"
/*N*/
/*N*/   aFtr.pLeft      = (const ScPageHFItem*) &pParamSet->Get(ATTR_PAGE_FOOTERLEFT);      // Inhalt
/*N*/   aFtr.pRight     = (const ScPageHFItem*) &pParamSet->Get(ATTR_PAGE_FOOTERRIGHT);
/*N*/
/*N*/   const SvxSetItem* pFooterSetItem;
/*N*/   const SfxItemSet* pFooterSet = NULL;
/*N*/   if ( pParamSet->GetItemState( ATTR_PAGE_FOOTERSET, FALSE,
/*N*/                           (const SfxPoolItem**)&pFooterSetItem ) == SFX_ITEM_SET )
/*N*/   {
/*N*/       pFooterSet = &pFooterSetItem->GetItemSet();
/*N*/                                                       // Fusszeile hat oberen Abstand
/*N*/       aFtr.nDistance  = ((const SvxULSpaceItem&) pFooterSet->Get(ATTR_ULSPACE)).GetUpper();
/*N*/   }
/*N*/   lcl_FillHFParam( aFtr, pFooterSet );
/*N*/
/*N*/   //------------------------------------------------------
/*N*/   // Table-/Area-Params aus einzelnen Items zusammenbauen:
/*N*/   //------------------------------------------------------
/*N*/   // TabPage "Tabelle"
/*N*/
/*N*/   const SfxUInt16Item* pScaleItem         = NULL;
/*N*/   const SfxUInt16Item* pScaleToPagesItem  = NULL;
/*N*/   SfxItemState         eState;
/*N*/
/*N*/   eState = pParamSet->GetItemState( ATTR_PAGE_SCALE, FALSE,
/*N*/                                     (const SfxPoolItem**)&pScaleItem );
/*N*/   if ( SFX_ITEM_DEFAULT == eState )
/*N*/       pScaleItem = (const SfxUInt16Item*)
/*N*/                    &pParamSet->GetPool()->
/*N*/                       GetDefaultItem( ATTR_PAGE_SCALE );
/*N*/
/*N*/   eState = pParamSet->GetItemState( ATTR_PAGE_SCALETOPAGES, FALSE,
/*N*/                                     (const SfxPoolItem**)&pScaleToPagesItem );
/*N*/   if ( SFX_ITEM_DEFAULT == eState )
/*N*/       pScaleToPagesItem = (const SfxUInt16Item*)
/*N*/                           &pParamSet->GetPool()->
/*N*/                               GetDefaultItem( ATTR_PAGE_SCALETOPAGES );
/*N*/
/*N*/   DBG_ASSERT( pScaleItem && pScaleToPagesItem, "Missing ScaleItem! :-/" );
/*N*/
/*N*/   aTableParam.bNotes          = GET_BOOL(pParamSet,ATTR_PAGE_NOTES);
/*N*/   aTableParam.bGrid           = GET_BOOL(pParamSet,ATTR_PAGE_GRID);
/*N*/   aTableParam.bHeaders        = GET_BOOL(pParamSet,ATTR_PAGE_HEADERS);
/*N*/   aTableParam.bFormulas       = GET_BOOL(pParamSet,ATTR_PAGE_FORMULAS);
/*N*/   aTableParam.bNullVals       = GET_BOOL(pParamSet,ATTR_PAGE_NULLVALS);
/*N*/   aTableParam.bCharts         = GET_SHOW(pParamSet,ATTR_PAGE_CHARTS);
/*N*/   aTableParam.bObjects        = GET_SHOW(pParamSet,ATTR_PAGE_OBJECTS);
/*N*/   aTableParam.bDrawings       = GET_SHOW(pParamSet,ATTR_PAGE_DRAWINGS);
/*N*/   aTableParam.bTopDown        = GET_BOOL(pParamSet,ATTR_PAGE_TOPDOWN);
/*N*/   aTableParam.bLeftRight      = !aTableParam.bLeftRight;
/*N*/   aTableParam.nFirstPageNo    = GET_USHORT(pParamSet,ATTR_PAGE_FIRSTPAGENO);
/*N*/   if (!aTableParam.nFirstPageNo)
/*N*/       aTableParam.nFirstPageNo = (USHORT) nPageStart;     // von vorheriger Tabelle
/*N*/
/*N*/   if ( pScaleItem && pScaleToPagesItem )
/*N*/   {
/*N*/       UINT16  nScaleAll     = pScaleItem->GetValue();
/*N*/       UINT16  nScaleToPages = pScaleToPagesItem->GetValue();
/*N*/
/*N*/       aTableParam.bScaleNone      = (nScaleAll     == 100);
/*N*/       aTableParam.bScaleAll       = (nScaleAll      > 0  );
/*N*/       aTableParam.bScalePageNum   = (nScaleToPages  > 0  );
/*N*/       aTableParam.nScaleAll       = nScaleAll;
/*N*/       aTableParam.nScalePageNum   = nScaleToPages;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aTableParam.bScaleNone      = TRUE;
/*N*/       aTableParam.bScaleAll       = FALSE;
/*N*/       aTableParam.bScalePageNum   = FALSE;
/*N*/       aTableParam.nScaleAll       = 0;
/*N*/       aTableParam.nScalePageNum   = 0;
/*N*/   }
/*N*/
/*N*/   //  skip empty pages only if options with that flag are passed
/*N*/   aTableParam.bSkipEmpty = pOptions && pOptions->GetSkipEmpty();
/*N*/   if ( pPageData )
/*N*/       aTableParam.bSkipEmpty = FALSE;
/*N*/   // Wenn pPageData gesetzt ist, interessieren fuer die Umbruch-Vorschau
/*N*/   // nur die Umbrueche, leere Seiten werden nicht speziell behandelt
/*N*/
/*N*/   //------------------------------------------------------
/*N*/   // TabPage "Bereiche":
/*N*/   //------------------------------------------------------
/*N*/
/*N*/   //! alle PrintAreas der Tabelle durchgehen !!!
/*N*/   const ScRange*  pPrintArea = pDoc->GetPrintRange( nPrintTab, 0 );
/*N*/   const ScRange*  pRepeatCol = pDoc->GetRepeatColRange( nPrintTab );
/*N*/   const ScRange*  pRepeatRow = pDoc->GetRepeatRowRange( nPrintTab );
/*N*/
/*N*/   //  ATTR_PAGE_PRINTTABLES wird ignoriert
/*N*/
/*N*/   if ( pUserArea )                // UserArea (Selektion) hat Vorrang
/*N*/   {
/*?*/       bPrintCurrentTable    =
/*?*/       aAreaParam.bPrintArea = TRUE;                   // Selektion
/*?*/       aAreaParam.aPrintArea = *pUserArea;
/*?*/
/*?*/       //  Die Tabellen-Abfrage ist schon in DocShell::Print, hier immer
/*?*/       aAreaParam.aPrintArea.aStart.SetTab(nPrintTab);
/*?*/       aAreaParam.aPrintArea.aEnd.SetTab(nPrintTab);
/*?*/
/*?*/ //        lcl_LimitRange( aAreaParam.aPrintArea, nPrintTab );         // ganze Zeilen/Spalten...
/*N*/   }
/*N*/   else if ( pDoc->HasPrintRange() )
/*N*/   {
/*N*/       if ( pPrintArea )                               // mindestens eine gesetzt ?
/*N*/       {
/*N*/           bPrintCurrentTable    =
/*N*/           aAreaParam.bPrintArea = TRUE;
/*N*/           aAreaParam.aPrintArea = *pPrintArea;
/*N*/
/*N*/           bMultiArea = ( pDoc->GetPrintRangeCount(nPrintTab) > 1 );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aAreaParam.bPrintArea = TRUE;
/*N*/           bPrintCurrentTable = FALSE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //  #74834# don't print hidden tables if there's no print range defined there
/*N*/       if ( pDoc->IsVisible( nPrintTab ) )
/*N*/       {
/*N*/           aAreaParam.bPrintArea = FALSE;
/*N*/           bPrintCurrentTable = TRUE;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aAreaParam.bPrintArea = TRUE;   // otherwise the table is always counted
/*N*/           bPrintCurrentTable = FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( pRepeatCol )
/*N*/   {
/*N*/       aAreaParam.bRepeatCol = TRUE;
/*N*/       aAreaParam.aRepeatCol = *pRepeatCol;
/*N*/       nRepeatStartCol = pRepeatCol->aStart.Col();
/*N*/       nRepeatEndCol   = pRepeatCol->aEnd  .Col();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aAreaParam.bRepeatCol = FALSE;
/*N*/       nRepeatStartCol = nRepeatEndCol = REPEAT_NONE;
/*N*/   }
/*N*/
/*N*/   if ( pRepeatRow )
/*N*/   {
/*?*/       aAreaParam.bRepeatRow = TRUE;
/*?*/       aAreaParam.aRepeatRow = *pRepeatRow;
/*?*/       nRepeatStartRow = pRepeatRow->aStart.Row();
/*?*/       nRepeatEndRow   = pRepeatRow->aEnd  .Row();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aAreaParam.bRepeatRow = FALSE;
/*N*/       nRepeatStartRow = nRepeatEndRow = REPEAT_NONE;
/*N*/   }
/*N*/
/*N*/           //
/*N*/           //  Seiten aufteilen
/*N*/           //
/*N*/
/*N*/   if (!bState)
/*N*/   {
/*N*/       nTabPages = CountPages();                                   // berechnet auch Zoom
/*N*/       nTotalPages = nTabPages;
/*N*/       nTotalPages += CountNotePages();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       CalcPages();            // nur Umbrueche suchen
/*?*/       CountNotePages();       // Notizen zaehlen, auch wenn Seitenzahl schon bekannt
/*N*/   }
/*N*/
/*N*/   if (nDocPages)
/*N*/       aFieldData.nTotalPages = nDocPages;
/*N*/   else
/*N*/       aFieldData.nTotalPages = nTotalPages;
/*N*/
/*N*/   SetDateTime( Date(), Time() );
/*N*/
/*N*/   aFieldData.aTitle       = pDocShell->GetTitle();
/*N*/   const INetURLObject& rURLObj = pDocShell->GetMedium()->GetURLObject();
/*N*/   aFieldData.aLongDocName = rURLObj.GetMainURL( INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   if ( aFieldData.aLongDocName.Len() )
/*?*/       aFieldData.aShortDocName = rURLObj.GetName( INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   else
/*N*/       aFieldData.aShortDocName = aFieldData.aLongDocName = aFieldData.aTitle;
/*N*/
/*N*/   //  Druckereinstellungen (Orientation, Paper) jetzt erst bei DoPrint
/*N*/ }

//STRIP001 Size ScPrintFunc::GetDataSize() const
//STRIP001 {
//STRIP001  Size aSize = aPageSize;
//STRIP001  aSize.Width()  -= nLeftMargin + nRightMargin;
//STRIP001  aSize.Height() -= nTopMargin + nBottomMargin;
//STRIP001  aSize.Height() -= aHdr.nHeight + aFtr.nHeight;
//STRIP001  return aSize;
//STRIP001 }

//STRIP001 void ScPrintFunc::GetScaleData( Size& rPhysSize, long& rDocHdr, long& rDocFtr )
//STRIP001 {
//STRIP001  rPhysSize = aPageSize;
//STRIP001  rPhysSize.Width()  -= nLeftMargin + nRightMargin;
//STRIP001  rPhysSize.Height() -= nTopMargin + nBottomMargin;
//STRIP001
//STRIP001  rDocHdr = aHdr.nHeight;
//STRIP001  rDocFtr = aFtr.nHeight;
//STRIP001 }

/*N*/ void ScPrintFunc::SetDateTime( const Date& rDate, const Time& rTime )
/*N*/ {
/*N*/   aFieldData.aDate = rDate;
/*N*/   aFieldData.aTime = rTime;
/*N*/ }

//STRIP001 void lcl_DrawGraphic( const Graphic &rGraphic, OutputDevice *pOut,
//STRIP001                      const Rectangle &rGrf, const Rectangle &rOut )
//STRIP001 {
//STRIP001  const FASTBOOL bNotInside = !rOut.IsInside( rGrf );
//STRIP001  if ( bNotInside )
//STRIP001  {
//STRIP001      pOut->Push();
//STRIP001      pOut->IntersectClipRegion( rOut );
//STRIP001  }
//STRIP001
//STRIP001  ((Graphic&)rGraphic).Draw( pOut, rGrf.TopLeft(), rGrf.GetSize() );
//STRIP001
//STRIP001  if ( bNotInside )
//STRIP001      pOut->Pop();
//STRIP001 }
//STRIP001
//STRIP001 void lcl_DrawGraphic( const Bitmap& rBitmap, OutputDevice *pOut,
//STRIP001                      const Rectangle &rGrf, const Rectangle &rOut )
//STRIP001 {
//STRIP001  const FASTBOOL bNotInside = !rOut.IsInside( rGrf );
//STRIP001  if ( bNotInside )
//STRIP001  {
//STRIP001      pOut->Push();
//STRIP001      pOut->IntersectClipRegion( rOut );
//STRIP001  }
//STRIP001
//STRIP001  pOut->DrawBitmap( rGrf.TopLeft(), rGrf.GetSize(), rBitmap );
//STRIP001
//STRIP001  if ( bNotInside )
//STRIP001      pOut->Pop();
//STRIP001 }
//STRIP001
//STRIP001 void lcl_DrawGraphic( const SvxBrushItem &rBrush, OutputDevice *pOut, OutputDevice* pRefDev,
//STRIP001                      const Rectangle &rOrg, const Rectangle &rOut )
//STRIP001 {
//STRIP001  Size aGrfSize(0,0);
//STRIP001  const Graphic *pGraphic = rBrush.GetGraphic();
//STRIP001  SvxGraphicPosition ePos;
//STRIP001  if ( pGraphic && pGraphic->IsSupportedGraphic() )
//STRIP001  {
//STRIP001      const MapMode aMapMM( MAP_100TH_MM );
//STRIP001      if ( pGraphic->GetPrefMapMode().GetMapUnit() == MAP_PIXEL )
//STRIP001          aGrfSize = pRefDev->PixelToLogic( pGraphic->GetPrefSize(), aMapMM );
//STRIP001      else
//STRIP001          aGrfSize = OutputDevice::LogicToLogic( pGraphic->GetPrefSize(),
//STRIP001                                  pGraphic->GetPrefMapMode(), aMapMM );
//STRIP001      ePos = rBrush.GetGraphicPos();
//STRIP001  }
//STRIP001  else
//STRIP001      ePos = GPOS_NONE;
//STRIP001
//STRIP001  Point aPos;
//STRIP001  Size aSize = aGrfSize;
//STRIP001
//STRIP001  FASTBOOL bDraw = TRUE;
//STRIP001 //   FASTBOOL bRetouche = TRUE;
//STRIP001  switch ( ePos )
//STRIP001  {
//STRIP001      case GPOS_LT: aPos = rOrg.TopLeft();
//STRIP001                    break;
//STRIP001      case GPOS_MT: aPos.Y() = rOrg.Top();
//STRIP001                    aPos.X() = rOrg.Left() + rOrg.GetSize().Width()/2 - aGrfSize.Width()/2;
//STRIP001                    break;
//STRIP001      case GPOS_RT: aPos.Y() = rOrg.Top();
//STRIP001                    aPos.X() = rOrg.Right() - aGrfSize.Width();
//STRIP001                    break;
//STRIP001
//STRIP001      case GPOS_LM: aPos.Y() = rOrg.Top() + rOrg.GetSize().Height()/2 - aGrfSize.Height()/2;
//STRIP001                    aPos.X() = rOrg.Left();
//STRIP001                    break;
//STRIP001      case GPOS_MM: aPos.Y() = rOrg.Top() + rOrg.GetSize().Height()/2 - aGrfSize.Height()/2;
//STRIP001                    aPos.X() = rOrg.Left() + rOrg.GetSize().Width()/2 - aGrfSize.Width()/2;
//STRIP001                    break;
//STRIP001      case GPOS_RM: aPos.Y() = rOrg.Top() + rOrg.GetSize().Height()/2 - aGrfSize.Height()/2;
//STRIP001                    aPos.X() = rOrg.Right() - aGrfSize.Width();
//STRIP001                    break;
//STRIP001
//STRIP001      case GPOS_LB: aPos.Y() = rOrg.Bottom() - aGrfSize.Height();
//STRIP001                    aPos.X() = rOrg.Left();
//STRIP001                    break;
//STRIP001      case GPOS_MB: aPos.Y() = rOrg.Bottom() - aGrfSize.Height();
//STRIP001                    aPos.X() = rOrg.Left() + rOrg.GetSize().Width()/2 - aGrfSize.Width()/2;
//STRIP001                    break;
//STRIP001      case GPOS_RB: aPos.Y() = rOrg.Bottom() - aGrfSize.Height();
//STRIP001                    aPos.X() = rOrg.Right() - aGrfSize.Width();
//STRIP001                    break;
//STRIP001
//STRIP001      case GPOS_AREA:
//STRIP001                    aPos = rOrg.TopLeft();
//STRIP001                    aSize = rOrg.GetSize();
//STRIP001 //                     bRetouche = FALSE;
//STRIP001                    break;
//STRIP001      case GPOS_TILED:
//STRIP001                  {
//STRIP001                      //  #104004# use GraphicObject::DrawTiled instead of an own loop
//STRIP001                      //  (pixel rounding is handled correctly, and a very small bitmap
//STRIP001                      //  is duplicated into a bigger one for better performance)
//STRIP001
//STRIP001                      GraphicObject aObject( *pGraphic );
//STRIP001
//STRIP001                         if( pOut->GetPDFWriter() &&
//STRIP001                             (aObject.GetType() == GRAPHIC_BITMAP || aObject.GetType() == GRAPHIC_DEFAULT) )
//STRIP001                         {
//STRIP001                             // #104004# For PDF export, every draw
//STRIP001                             // operation for bitmaps takes a noticeable
//STRIP001                             // amount of place (~50 characters). Thus,
//STRIP001                             // optimize between tile bitmap size and
//STRIP001                             // number of drawing operations here.
//STRIP001                             //
//STRIP001                             //                  A_out
//STRIP001                             // n_chars = k1 *  ---------- + k2 * A_bitmap
//STRIP001                             //                  A_bitmap
//STRIP001                             //
//STRIP001                             // minimum n_chars is obtained for (derive for
//STRIP001                             // A_bitmap, set to 0, take positive
//STRIP001                             // solution):
//STRIP001                             //                   k1
//STRIP001                             // A_bitmap = Sqrt( ---- A_out )
//STRIP001                             //                   k2
//STRIP001                             //
//STRIP001                             // where k1 is the number of chars per draw
//STRIP001                             // operation, and k2 is the number of chars
//STRIP001                             // per bitmap pixel. This is approximately 50
//STRIP001                             // and 7 for current PDF writer, respectively.
//STRIP001                             //
//STRIP001                             const double k1( 50 );
//STRIP001                             const double k2( 7 );
//STRIP001                             const Size       aSize( rOrg.GetSize() );
//STRIP001                             const double     Abitmap( k1/k2 * aSize.Width()*aSize.Height() );
//STRIP001
//STRIP001                             aObject.DrawTiled( pOut, rOrg, aGrfSize, Size(0,0),
//STRIP001                                                NULL, GRFMGR_DRAW_STANDARD,
//STRIP001                                                ::std::max( 128, static_cast<int>( sqrt(sqrt( Abitmap)) + .5 ) ) );
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             aObject.DrawTiled( pOut, rOrg, aGrfSize, Size(0,0) );
//STRIP001                         }
//STRIP001
//STRIP001                      bDraw = FALSE;
//STRIP001 //                       bRetouche = FALSE;
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001      case GPOS_NONE:
//STRIP001                    bDraw = FALSE;
//STRIP001                    break;
//STRIP001
//STRIP001      default: DBG_ASSERT( !pOut, "new Graphic position?" );
//STRIP001  }
//STRIP001  Rectangle aGrf( aPos,aSize );
//STRIP001  if ( bDraw && aGrf.IsOver( rOut ) )
//STRIP001  {
//STRIP001      lcl_DrawGraphic( *pGraphic, pOut, aGrf, rOut );
//STRIP001  }
//STRIP001 }

//  Rahmen wird nach innen gezeichnet

//STRIP001 void ScPrintFunc::DrawBorder( long nScrX, long nScrY, long nScrW, long nScrH,
//STRIP001                              const SvxBoxItem* pBorderData, const SvxBrushItem* pBackground,
//STRIP001                              const SvxShadowItem* pShadow )
//STRIP001 {
//STRIP001  //!     direkte Ausgabe aus SvxBoxItem !!!
//STRIP001
//STRIP001  if (pBorderData)
//STRIP001      if ( !pBorderData->GetTop() && !pBorderData->GetBottom() && !pBorderData->GetLeft() &&
//STRIP001                                      !pBorderData->GetRight() )
//STRIP001          pBorderData = NULL;
//STRIP001
//STRIP001  if (!pBorderData && !pBackground && !pShadow)
//STRIP001      return;                                     // nichts zu tun
//STRIP001
//STRIP001  long nLeft   = 0;
//STRIP001  long nRight  = 0;
//STRIP001  long nTop    = 0;
//STRIP001  long nBottom = 0;
//STRIP001
//STRIP001  //  aFrameRect - aussen um die Umrandung, ohne Schatten
//STRIP001  if ( pShadow && pShadow->GetLocation() != SVX_SHADOW_NONE )
//STRIP001  {
//STRIP001      nLeft   += (long) ( pShadow->CalcShadowSpace(SHADOW_LEFT)   * nScaleX );
//STRIP001      nRight  += (long) ( pShadow->CalcShadowSpace(SHADOW_RIGHT)  * nScaleX );
//STRIP001      nTop    += (long) ( pShadow->CalcShadowSpace(SHADOW_TOP)    * nScaleY );
//STRIP001      nBottom += (long) ( pShadow->CalcShadowSpace(SHADOW_BOTTOM) * nScaleY );
//STRIP001  }
//STRIP001  Rectangle aFrameRect( Point(nScrX+nLeft, nScrY+nTop),
//STRIP001                        Size(nScrW-nLeft-nRight, nScrH-nTop-nBottom) );
//STRIP001
//STRIP001  //  Mitte der Umrandung, um Linien ueber OutputData zu zeichnen:
//STRIP001  if (pBorderData)
//STRIP001  {
//STRIP001      nLeft   += (long) ( lcl_LineTotal(pBorderData->GetLeft())   * nScaleX / 2 );
//STRIP001      nRight  += (long) ( lcl_LineTotal(pBorderData->GetRight())  * nScaleX / 2 );
//STRIP001      nTop    += (long) ( lcl_LineTotal(pBorderData->GetTop())    * nScaleY / 2 );
//STRIP001      nBottom += (long) ( lcl_LineTotal(pBorderData->GetBottom()) * nScaleY / 2 );
//STRIP001  }
//STRIP001  long nEffHeight = nScrH - nTop - nBottom;
//STRIP001  long nEffWidth = nScrW - nLeft - nRight;
//STRIP001  if (nEffHeight<=0 || nEffWidth<=0)
//STRIP001      return;                                         // leer
//STRIP001
//STRIP001  //  #105733# SvtAccessibilityOptions::GetIsForBorders is no longer used (always assumed TRUE)
//STRIP001  BOOL bCellContrast = bUseStyleColor &&
//STRIP001          Application::GetSettings().GetStyleSettings().GetHighContrastMode();
//STRIP001
//STRIP001  if ( pBackground && !bCellContrast )
//STRIP001  {
//STRIP001 //       Rectangle aBackRect( Point(nScrX+nLeft, nScrY+nTop), Size(nEffWidth,nEffHeight) );
//STRIP001      if (pBackground->GetGraphicPos() != GPOS_NONE)
//STRIP001      {
//STRIP001          OutputDevice* pRefDev;
//STRIP001          if ( bIsRender )
//STRIP001              pRefDev = pDev;                 // don't use printer for PDF
//STRIP001          else
//STRIP001              pRefDev = pDoc->GetPrinter();   // use printer also for preview
//STRIP001
//STRIP001          lcl_DrawGraphic( *pBackground, pDev, pRefDev, aFrameRect, aFrameRect );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pDev->SetFillColor(pBackground->GetColor());
//STRIP001          pDev->SetLineColor();
//STRIP001          pDev->DrawRect(aFrameRect);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( pShadow && pShadow->GetLocation() != SVX_SHADOW_NONE )
//STRIP001  {
//STRIP001      if ( bCellContrast )
//STRIP001             pDev->SetFillColor( SC_MOD()->GetColorConfig().GetColorValue(svtools::FONTCOLOR).nColor );
//STRIP001      else
//STRIP001          pDev->SetFillColor(pShadow->GetColor());
//STRIP001      pDev->SetLineColor();
//STRIP001      long nShadowX = (long) ( pShadow->GetWidth() * nScaleX );
//STRIP001      long nShadowY = (long) ( pShadow->GetWidth() * nScaleY );
//STRIP001      switch (pShadow->GetLocation())
//STRIP001      {
//STRIP001          case SVX_SHADOW_TOPLEFT:
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Left()-nShadowX, aFrameRect.Top()-nShadowY,
//STRIP001                      aFrameRect.Right()-nShadowX, aFrameRect.Top() ) );
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Left()-nShadowX, aFrameRect.Top()-nShadowY,
//STRIP001                      aFrameRect.Left(), aFrameRect.Bottom()-nShadowY ) );
//STRIP001              break;
//STRIP001          case SVX_SHADOW_TOPRIGHT:
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Left()+nShadowX, aFrameRect.Top()-nShadowY,
//STRIP001                      aFrameRect.Right()+nShadowX, aFrameRect.Top() ) );
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Right(), aFrameRect.Top()-nShadowY,
//STRIP001                      aFrameRect.Right()+nShadowX, aFrameRect.Bottom()-nShadowY ) );
//STRIP001              break;
//STRIP001          case SVX_SHADOW_BOTTOMLEFT:
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Left()-nShadowX, aFrameRect.Bottom(),
//STRIP001                      aFrameRect.Right()-nShadowX, aFrameRect.Bottom()+nShadowY ) );
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Left()-nShadowX, aFrameRect.Top()+nShadowY,
//STRIP001                      aFrameRect.Left(), aFrameRect.Bottom()+nShadowY ) );
//STRIP001              break;
//STRIP001          case SVX_SHADOW_BOTTOMRIGHT:
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Left()+nShadowX, aFrameRect.Bottom(),
//STRIP001                      aFrameRect.Right()+nShadowX, aFrameRect.Bottom()+nShadowY ) );
//STRIP001              pDev->DrawRect( Rectangle(
//STRIP001                      aFrameRect.Right(), aFrameRect.Top()+nShadowY,
//STRIP001                      aFrameRect.Right()+nShadowX, aFrameRect.Bottom()+nShadowY ) );
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  USHORT i;
//STRIP001  if (pBorderData)
//STRIP001  {
//STRIP001      ScDocument* pBorderDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      pBorderDoc->InitUndo( pDoc, 0,0, TRUE,TRUE );
//STRIP001      if (pBorderData)
//STRIP001          pBorderDoc->ApplyAttr( 0,0,0, *pBorderData );
//STRIP001
//STRIP001      RowInfo* pRowInfo = new RowInfo[ROWINFO_MAX];
//STRIP001      USHORT nArrCount = pBorderDoc->FillInfo( pRowInfo, 0,0, 0,0, 0,
//STRIP001                                          nScaleX, nScaleY, FALSE, FALSE );
//STRIP001      DBG_ASSERT(nArrCount,"nArrCount == 0");
//STRIP001
//STRIP001      pRowInfo[1].nHeight = (USHORT) nEffHeight;
//STRIP001      pRowInfo[0].pCellInfo[1].nWidth =
//STRIP001          pRowInfo[1].pCellInfo[1].nWidth = (USHORT) nEffWidth;
//STRIP001
//STRIP001      ScOutputData aOutputData( pDev, OUTTYPE_PRINTER, pRowInfo, nArrCount, pBorderDoc, 0,
//STRIP001                                  nScrX+nLeft, nScrY+nTop, 0,0, 0,0, nScaleX, nScaleY );
//STRIP001      aOutputData.SetUseStyleColor( bUseStyleColor );
//STRIP001
//STRIP001 //       pDev->SetMapMode(aTwipMode);
//STRIP001
//STRIP001      if (pBorderData)
//STRIP001          aOutputData.DrawFrame();
//STRIP001
//STRIP001      for (i=0; i<nArrCount; i++)
//STRIP001          delete[] pRowInfo[i].pCellInfo;
//STRIP001      delete[] pRowInfo;
//STRIP001
//STRIP001      delete pBorderDoc;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPrintFunc::PrintColHdr( USHORT nX1, USHORT nX2, long nScrX, long nScrY )
//STRIP001 {
//STRIP001  Size aOnePixel = pDev->PixelToLogic(Size(1,1));
//STRIP001  long nOneX = aOnePixel.Width();
//STRIP001  long nOneY = aOnePixel.Height();
//STRIP001
//STRIP001  long nHeight = (long) (PRINT_HEADER_HEIGHT * nScaleY);
//STRIP001  long nEndY = nScrY + nHeight - nOneY;
//STRIP001
//STRIP001  long nPosX = nScrX - nOneX;
//STRIP001  long nPosY = nScrY - nOneY;
//STRIP001  String aText;
//STRIP001
//STRIP001  for (USHORT nCol=nX1; nCol<=nX2; nCol++)
//STRIP001  {
//STRIP001      USHORT nDocW = pDoc->GetColWidth( nCol, nPrintTab );
//STRIP001      if (nDocW)
//STRIP001      {
//STRIP001          long nWidth = (long) (nDocW * nScaleX);
//STRIP001          long nEndX = nPosX + nWidth;
//STRIP001
//STRIP001          pDev->DrawRect( Rectangle( nPosX,nPosY,nEndX,nEndY ) );
//STRIP001
//STRIP001          if ( nCol < 26 )
//STRIP001              aText = (sal_Unicode) ( 'A' + nCol );
//STRIP001          else
//STRIP001          {
//STRIP001              aText = (sal_Unicode) ( 'A' + ( nCol / 26 ) - 1 );
//STRIP001              aText += (sal_Unicode) ( 'A' + ( nCol % 26 ) );
//STRIP001          }
//STRIP001          long nTextWidth = pDev->GetTextWidth(aText);
//STRIP001          long nTextHeight = pDev->GetTextHeight();
//STRIP001          long nAddX = ( nWidth  - nTextWidth  ) / 2;
//STRIP001          long nAddY = ( nHeight - nTextHeight ) / 2;
//STRIP001          pDev->DrawText( Point( nPosX+nAddX,nPosY+nAddY ), aText );
//STRIP001
//STRIP001          nPosX = nEndX;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPrintFunc::PrintRowHdr( USHORT nY1, USHORT nY2, long nScrX, long nScrY )
//STRIP001 {
//STRIP001  Size aOnePixel = pDev->PixelToLogic(Size(1,1));
//STRIP001  long nOneX = aOnePixel.Width();
//STRIP001  long nOneY = aOnePixel.Height();
//STRIP001
//STRIP001  long nWidth = (long) (PRINT_HEADER_WIDTH * nScaleX);
//STRIP001  long nEndX = nScrX + nWidth - nOneX;
//STRIP001
//STRIP001  long nPosX = nScrX - nOneX;
//STRIP001  long nPosY = nScrY - nOneY;
//STRIP001  String aText;
//STRIP001
//STRIP001  for (USHORT nRow=nY1; nRow<=nY2; nRow++)
//STRIP001  {
//STRIP001      USHORT nDocH = pDoc->FastGetRowHeight( nRow, nPrintTab );
//STRIP001      if (nDocH)
//STRIP001      {
//STRIP001          long nHeight = (long) (nDocH * nScaleY);
//STRIP001          long nEndY = nPosY + nHeight;
//STRIP001
//STRIP001          pDev->DrawRect( Rectangle( nPosX,nPosY,nEndX,nEndY ) );
//STRIP001
//STRIP001          aText = String::CreateFromInt32( nRow+1 );
//STRIP001          long nTextWidth = pDev->GetTextWidth(aText);
//STRIP001          long nTextHeight = pDev->GetTextHeight();
//STRIP001          long nAddX = ( nWidth  - nTextWidth  ) / 2;
//STRIP001          long nAddY = ( nHeight - nTextHeight ) / 2;
//STRIP001          pDev->DrawText( Point( nPosX+nAddX,nPosY+nAddY ), aText );
//STRIP001
//STRIP001          nPosY = nEndY;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPrintFunc::LocateColHdr( USHORT nX1, USHORT nX2, long nScrX, long nScrY,
//STRIP001                              BOOL bRepCol, ScPreviewLocationData& rLocationData )
//STRIP001 {
//STRIP001  Size aOnePixel = pDev->PixelToLogic(Size(1,1));
//STRIP001  long nOneX = aOnePixel.Width();
//STRIP001  long nOneY = aOnePixel.Height();
//STRIP001
//STRIP001  long nHeight = (long) (PRINT_HEADER_HEIGHT * nScaleY);
//STRIP001  long nEndY = nScrY + nHeight - nOneY;
//STRIP001
//STRIP001  long nPosX = nScrX - nOneX;
//STRIP001  for (USHORT nCol=nX1; nCol<=nX2; nCol++)
//STRIP001  {
//STRIP001      USHORT nDocW = pDoc->GetColWidth( nCol, nPrintTab );
//STRIP001      if (nDocW)
//STRIP001          nPosX += (long) (nDocW * nScaleX);
//STRIP001  }
//STRIP001  Rectangle aCellRect( nScrX, nScrY, nPosX, nEndY );
//STRIP001  rLocationData.AddColHeaders( aCellRect, nX1, nX2, bRepCol );
//STRIP001 }

//STRIP001 void ScPrintFunc::LocateRowHdr( USHORT nY1, USHORT nY2, long nScrX, long nScrY,
//STRIP001                              BOOL bRepRow, ScPreviewLocationData& rLocationData )
//STRIP001 {
//STRIP001  Size aOnePixel = pDev->PixelToLogic(Size(1,1));
//STRIP001  long nOneX = aOnePixel.Width();
//STRIP001  long nOneY = aOnePixel.Height();
//STRIP001
//STRIP001  long nWidth = (long) (PRINT_HEADER_WIDTH * nScaleX);
//STRIP001  long nEndX = nScrX + nWidth - nOneX;
//STRIP001
//STRIP001  long nPosY = nScrY - nOneY;
//STRIP001  for (USHORT nRow=nY1; nRow<=nY2; nRow++)
//STRIP001  {
//STRIP001      USHORT nDocH = pDoc->FastGetRowHeight( nRow, nPrintTab );
//STRIP001      if (nDocH)
//STRIP001          nPosY += (long) (nDocH * nScaleY);
//STRIP001  }
//STRIP001  Rectangle aCellRect( nScrX, nScrY, nEndX, nPosY );
//STRIP001  rLocationData.AddRowHeaders( aCellRect, nY1, nY2, bRepRow );
//STRIP001 }

//STRIP001 void ScPrintFunc::LocateArea( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                              long nScrX, long nScrY, BOOL bRepCol, BOOL bRepRow,
//STRIP001                              ScPreviewLocationData& rLocationData )
//STRIP001 {
//STRIP001  //  get MapMode for drawing objects (same MapMode as in ScOutputData::DrawingLayer)
//STRIP001
//STRIP001  Point aLogPos = OutputDevice::LogicToLogic(Point(nScrX,nScrY), aOffsetMode, aLogicMode);
//STRIP001  long nLogStX = aLogPos.X();
//STRIP001  long nLogStY = aLogPos.Y();
//STRIP001
//STRIP001  USHORT nCol, nRow;
//STRIP001  Point aOffset;
//STRIP001  for (nCol=0; nCol<nX1; nCol++)
//STRIP001      aOffset.X() -= pDoc->GetColWidth( nCol, nPrintTab );
//STRIP001  for (nRow=0; nRow<nY1; nRow++)
//STRIP001      aOffset.Y() -= pDoc->GetRowHeight( nRow, nPrintTab );
//STRIP001
//STRIP001  Point aMMOffset( aOffset );
//STRIP001  aMMOffset.X() = (long)(aMMOffset.X() * HMM_PER_TWIPS);
//STRIP001  aMMOffset.Y() = (long)(aMMOffset.Y() * HMM_PER_TWIPS);
//STRIP001  aMMOffset += Point( nLogStX, nLogStY );
//STRIP001  MapMode aDrawMapMode( MAP_100TH_MM, aMMOffset, aLogicMode.GetScaleX(), aLogicMode.GetScaleY() );
//STRIP001
//STRIP001  //  get pixel rectangle
//STRIP001
//STRIP001  Size aOnePixel = pDev->PixelToLogic(Size(1,1));
//STRIP001  long nOneX = aOnePixel.Width();
//STRIP001  long nOneY = aOnePixel.Height();
//STRIP001
//STRIP001  long nPosX = nScrX - nOneX;
//STRIP001  for (nCol=nX1; nCol<=nX2; nCol++)
//STRIP001  {
//STRIP001      USHORT nDocW = pDoc->GetColWidth( nCol, nPrintTab );
//STRIP001      if (nDocW)
//STRIP001          nPosX += (long) (nDocW * nScaleX);
//STRIP001  }
//STRIP001
//STRIP001  long nPosY = nScrY - nOneY;
//STRIP001  for (nRow=nY1; nRow<=nY2; nRow++)
//STRIP001  {
//STRIP001      USHORT nDocH = pDoc->FastGetRowHeight( nRow, nPrintTab );
//STRIP001      if (nDocH)
//STRIP001          nPosY += (long) (nDocH * nScaleY);
//STRIP001  }
//STRIP001
//STRIP001  Rectangle aCellRect( nScrX, nScrY, nPosX, nPosY );
//STRIP001  rLocationData.AddCellRange( aCellRect, ScRange( nX1,nY1,nPrintTab, nX2,nY2,nPrintTab ),
//STRIP001                              bRepCol, bRepRow, aDrawMapMode );
//STRIP001 }

//STRIP001 void ScPrintFunc::PrintArea( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                              long nScrX, long nScrY,
//STRIP001                              BOOL bShLeft, BOOL bShTop, BOOL bShRight, BOOL bShBottom )
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001
//STRIP001                          //!     Flag bei FillInfo uebergeben !!!!!
//STRIP001  ScTripel aEStart;
//STRIP001  ScTripel aEEnd;
//STRIP001  BOOL bEmbed = pDoc->IsEmbedded();
//STRIP001  if (bEmbed)
//STRIP001  {
//STRIP001      pDoc->GetEmbedded(aEStart,aEEnd);
//STRIP001      pDoc->ResetEmbedded();
//STRIP001  }
//STRIP001
//STRIP001  Point aPos = OutputDevice::LogicToLogic(Point(nScrX,nScrY), aOffsetMode, aLogicMode);
//STRIP001  long nLogStX = aPos.X();
//STRIP001  long nLogStY = aPos.Y();
//STRIP001
//STRIP001                  //  Daten zusammenstellen
//STRIP001
//STRIP001  RowInfo* pRowInfo = new RowInfo[ROWINFO_MAX];
//STRIP001  USHORT nArrCount = pDoc->FillInfo( pRowInfo, nX1, nY1, nX2, nY2, nPrintTab,
//STRIP001                                      nScaleX, nScaleY, TRUE, aTableParam.bFormulas );
//STRIP001  lcl_HidePrint( pRowInfo, nArrCount, nX1, nX2 );
//STRIP001
//STRIP001  if (bEmbed)
//STRIP001      pDoc->SetEmbedded(aEStart,aEEnd);
//STRIP001
//STRIP001  ScOutputData aOutputData( pDev, OUTTYPE_PRINTER, pRowInfo, nArrCount, pDoc, nPrintTab,
//STRIP001                              nScrX, nScrY, nX1, nY1, nX2, nY2, nScaleX, nScaleY );
//STRIP001
//STRIP001  if (nObjectFlags)
//STRIP001  {
//STRIP001      pDev->SetMapMode(aLogicMode);
//STRIP001      //  hier kein Clipping setzen (Mapmode wird verschoben)
//STRIP001      aOutputData.DrawingLayer(SC_LAYER_BACK,nObjectFlags,nLogStX,nLogStY);
//STRIP001  }
//STRIP001
//STRIP001  pDev->SetMapMode(aOffsetMode);
//STRIP001
//STRIP001  aOutputData.SetShowFormulas( aTableParam.bFormulas );
//STRIP001  aOutputData.SetShowNullValues( aTableParam.bNullVals );
//STRIP001  aOutputData.SetUseStyleColor( bUseStyleColor );
//STRIP001
//STRIP001  Color aGridColor( COL_BLACK );
//STRIP001  if ( bUseStyleColor )
//STRIP001         aGridColor.SetColor( SC_MOD()->GetColorConfig().GetColorValue(svtools::FONTCOLOR).nColor );
//STRIP001  aOutputData.SetGridColor( aGridColor );
//STRIP001
//STRIP001  if ( !pPrinter )
//STRIP001  {
//STRIP001      OutputDevice* pRefDev = pDoc->GetPrinter();     // auch fuer Preview den Drucker nehmen
//STRIP001      Fraction aPrintFrac( nZoom, 100 );              // ohne nManualZoom
//STRIP001      //  MapMode, wie er beim Drucken herauskommen wuerde:
//STRIP001      pRefDev->SetMapMode( MapMode( MAP_100TH_MM, Point(), aPrintFrac, aPrintFrac ) );
//STRIP001
//STRIP001      //  when rendering (PDF), don't use printer as ref device, but printer's MapMode
//STRIP001      //  has to be set anyway, as charts still use it (#106409#)
//STRIP001      if ( !bIsRender )
//STRIP001          aOutputData.SetRefDevice( pRefDev );
//STRIP001  }
//STRIP001
//STRIP001 //   aOutputData.SetMetaFileMode(TRUE);
//STRIP001  aOutputData.DrawBackground();
//STRIP001
//STRIP001  pDev->SetClipRegion( Rectangle( aPos, Size( aOutputData.GetScrW(), aOutputData.GetScrH() ) ) );
//STRIP001  SFX_APP()->SpoilDemoOutput( *pDev, OutputDevice::LogicToLogic(
//STRIP001                              aPageRect, aTwipMode, aOffsetMode ) );
//STRIP001  pDev->SetClipRegion();
//STRIP001
//STRIP001 //   aOutputData.SetMetaFileMode(FALSE);
//STRIP001  aOutputData.DrawExtraShadow( bShLeft, bShTop, bShRight, bShBottom );
//STRIP001  aOutputData.DrawFrame();
//STRIP001  aOutputData.DrawStrings();
//STRIP001
//STRIP001 //   pDev->SetMapMode(aLogicMode);
//STRIP001  aOutputData.DrawEdit(FALSE);
//STRIP001
//STRIP001 //   pDev->SetMapMode(aOffsetMode);
//STRIP001  if (aTableParam.bGrid)
//STRIP001      aOutputData.DrawGrid( TRUE, FALSE );    // keine Seitenumbrueche

/*!!!!!!!!!!!       Notizen in Tabelle markieren ??????????????????????????

    if (aTableParam.bNotes)
    {
        pDev->SetMapMode(aOffsetMode);
        aOutputData.PrintNoteMarks(aNotePosList);
        pDev->SetMapMode(aLogicMode);
    }
*/

//STRIP001 //   pDev->SetMapMode(aDrawMode);
//STRIP001  if (nObjectFlags)
//STRIP001      aOutputData.DrawingLayer(SC_LAYER_FRONT,nObjectFlags,nLogStX,nLogStY);
//STRIP001  aOutputData.DrawingLayer(SC_LAYER_INTERN,SC_OBJECTS_ALL,nLogStX,nLogStY);
//STRIP001
//STRIP001  if ( pDrawView && (nObjectFlags & SC_OBJECTS_DRAWING) )
//STRIP001  {
//STRIP001      SdrPageView* pPV = pDrawView->GetPageViewPgNum(nPrintTab);
//STRIP001      DBG_ASSERT(pPV, "keine PageView fuer gedruckte Tabelle");
//STRIP001      if (pPV)
//STRIP001      {
//STRIP001          Rectangle aLogicRect = pDoc->GetMMRect( nX1,nY1, nX2,nY2, nPrintTab );
//STRIP001          Point aControlOffset( nLogStX - aLogicRect.Left(), nLogStY - aLogicRect.Top() );
//STRIP001          MapMode aControlMode( MAP_100TH_MM, aControlOffset,
//STRIP001                                  aLogicMode.GetScaleX(), aLogicMode.GetScaleY() );
//STRIP001          pDev->SetMapMode( aControlMode );
//STRIP001          pDev->SetClipRegion( aLogicRect );      // single controls may extend beyond the page
//STRIP001
//STRIP001          pPV->RedrawOneLayer( SC_LAYER_CONTROLS, aLogicRect );
//STRIP001
//STRIP001          pDev->SetClipRegion();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  for (i=0; i<nArrCount; i++)
//STRIP001      delete[] pRowInfo[i].pCellInfo;
//STRIP001  delete[] pRowInfo;
//STRIP001 }

BOOL ScPrintFunc::IsMirror( long nPageNo )          // Raender spiegeln ?
{
    SvxPageUsage eUsage = (SvxPageUsage) ( nPageUsage & 0x000f );
    return ( eUsage == SVX_PAGE_MIRROR && (nPageNo & 1) );
}

//STRIP001 BOOL ScPrintFunc::IsLeft( long nPageNo )         // linke Fussnoten ?
//STRIP001 {
//STRIP001  SvxPageUsage eUsage = (SvxPageUsage) ( nPageUsage & 0x000f );
//STRIP001  BOOL bLeft;
//STRIP001  if (eUsage == SVX_PAGE_LEFT)
//STRIP001      bLeft = TRUE;
//STRIP001  else if (eUsage == SVX_PAGE_RIGHT)
//STRIP001      bLeft = FALSE;
//STRIP001  else
//STRIP001      bLeft = (nPageNo & 1) != 0;
//STRIP001  return bLeft;
//STRIP001 }

//STRIP001 void ScPrintFunc::MakeTableString()
//STRIP001 {
//STRIP001  pDoc->GetName( nPrintTab, aFieldData.aTabName );
//STRIP001 }

//STRIP001 String lcl_CmdStr( USHORT nId )
//STRIP001 {
//STRIP001  String aDel( ScGlobal::GetRscString( STR_HFCMD_DELIMITER ) );
//STRIP001  String aCmd = aDel;
//STRIP001  aCmd += ScGlobal::GetRscString( nId );
//STRIP001  aCmd += aDel;
//STRIP001  return aCmd;
//STRIP001 }

/*N*/ void ScPrintFunc::MakeEditEngine()
/*N*/ {
/*N*/   if (!pEditEngine)
/*N*/   {
/*N*/       //  can't use document's edit engine pool here,
/*N*/       //  because pool must have twips as default metric
/*N*/       pEditEngine = new ScHeaderEditEngine( EditEngine::CreatePool(), TRUE );
/*N*/
/*N*/       pEditEngine->EnableUndo(FALSE);
/*N*/       pEditEngine->SetRefDevice( pDev );
/*N*/       pEditEngine->SetWordDelimiters(
/*N*/               ScEditUtil::ModifyDelimiters( pEditEngine->GetWordDelimiters() ) );
/*N*/       pEditEngine->SetControlWord( pEditEngine->GetControlWord() & ~EE_CNTRL_RTFSTYLESHEETS );
/*N*/       pEditEngine->EnableAutoColor( bUseStyleColor );
/*N*/
/*N*/       //  Default-Set fuer Ausrichtung
/*N*/       pEditDefaults = new SfxItemSet( pEditEngine->GetEmptyItemSet() );
/*N*/
/*N*/       const ScPatternAttr& rPattern = (const ScPatternAttr&)pDoc->GetPool()->GetDefaultItem(ATTR_PATTERN);
/*N*/       rPattern.FillEditItemSet( pEditDefaults );
/*N*/       //  FillEditItemSet adjusts font height to 1/100th mm,
/*N*/       //  but for header/footer twips is needed, as in the PatternAttr:
/*N*/       pEditDefaults->Put( rPattern.GetItem(ATTR_FONT_HEIGHT), EE_CHAR_FONTHEIGHT );
/*N*/       pEditDefaults->Put( rPattern.GetItem(ATTR_CJK_FONT_HEIGHT), EE_CHAR_FONTHEIGHT_CJK );
/*N*/       pEditDefaults->Put( rPattern.GetItem(ATTR_CTL_FONT_HEIGHT), EE_CHAR_FONTHEIGHT_CTL );
/*N*/       //  #69193# dont use font color, because background color is not used
/*N*/       //! there's no way to set the background for note pages
/*N*/       pEditDefaults->ClearItem( EE_CHAR_COLOR );
/*N*/   }
/*N*/
/*N*/   pEditEngine->SetData( aFieldData );     // Seitennummer etc. setzen
/*N*/ }

//  nStartY = logic
//STRIP001 void ScPrintFunc::PrintHF( long nPageNo, BOOL bHeader, long nStartY,
//STRIP001                          BOOL bDoPrint, ScPreviewLocationData* pLocationData )
//STRIP001 {
//STRIP001  const ScPrintHFParam& rParam = bHeader ? aHdr : aFtr;
//STRIP001
//STRIP001  pDev->SetMapMode( aTwipMode );          // Kopf-/Fusszeilen in Twips
//STRIP001
//STRIP001  BOOL bLeft = IsLeft(nPageNo) && !rParam.bShared;
//STRIP001  const ScPageHFItem* pHFItem = bLeft ? rParam.pLeft : rParam.pRight;
//STRIP001
//STRIP001  long nLineStartX = aPageRect.Left()  + rParam.nLeft;
//STRIP001  long nLineEndX   = aPageRect.Right() - rParam.nRight;
//STRIP001  long nLineWidth  = nLineEndX - nLineStartX + 1;
//STRIP001
//STRIP001  //  Edit-Engine
//STRIP001
//STRIP001  Point aStart( nLineStartX, nStartY );
//STRIP001  Size aPaperSize( nLineWidth, rParam.nHeight-rParam.nDistance );
//STRIP001  if ( rParam.pBorder )
//STRIP001  {
//STRIP001      long nLeft = lcl_LineTotal( rParam.pBorder->GetLeft() ) + rParam.pBorder->GetDistance(BOX_LINE_LEFT);
//STRIP001      long nTop = lcl_LineTotal( rParam.pBorder->GetTop() ) + rParam.pBorder->GetDistance(BOX_LINE_TOP);
//STRIP001      aStart.X() += nLeft;
//STRIP001      aStart.Y() += nTop;
//STRIP001      aPaperSize.Width() -= nLeft + lcl_LineTotal( rParam.pBorder->GetRight() ) + rParam.pBorder->GetDistance(BOX_LINE_RIGHT);
//STRIP001      aPaperSize.Height() -= nTop + lcl_LineTotal( rParam.pBorder->GetBottom() ) + rParam.pBorder->GetDistance(BOX_LINE_BOTTOM);
//STRIP001  }
//STRIP001
//STRIP001  if ( rParam.pShadow && rParam.pShadow->GetLocation() != SVX_SHADOW_NONE )
//STRIP001  {
//STRIP001      long nLeft  = rParam.pShadow->CalcShadowSpace(SHADOW_LEFT);
//STRIP001      long nTop   = rParam.pShadow->CalcShadowSpace(SHADOW_TOP);
//STRIP001      aStart.X() += nLeft;
//STRIP001      aStart.Y() += nTop;
//STRIP001      aPaperSize.Width() -= nLeft + rParam.pShadow->CalcShadowSpace(SHADOW_RIGHT);
//STRIP001      aPaperSize.Height() -= nTop + rParam.pShadow->CalcShadowSpace(SHADOW_BOTTOM);
//STRIP001  }
//STRIP001
//STRIP001  aFieldData.nPageNo = nPageNo+aTableParam.nFirstPageNo;
//STRIP001  MakeEditEngine();
//STRIP001
//STRIP001  pEditEngine->SetPaperSize(aPaperSize);
//STRIP001  const EditTextObject* pObject;
//STRIP001
//STRIP001  //  Rahmen / Hintergrund
//STRIP001
//STRIP001  Point aBorderStart( nLineStartX, nStartY );
//STRIP001  Size aBorderSize( nLineWidth, rParam.nHeight-rParam.nDistance );
//STRIP001  if ( rParam.bDynamic )
//STRIP001  {
//STRIP001      //  hier nochmal anpassen, wegen geraden/ungeraden Kopf/Fusszeilen
//STRIP001      //  und evtl. anderen Umbruechen durch Variablen (Seitennummer etc.)
//STRIP001
//STRIP001      long nMaxHeight = 0;
//STRIP001      nMaxHeight = Max( nMaxHeight, TextHeight( pHFItem->GetLeftArea() ) );
//STRIP001      nMaxHeight = Max( nMaxHeight, TextHeight( pHFItem->GetCenterArea() ) );
//STRIP001      nMaxHeight = Max( nMaxHeight, TextHeight( pHFItem->GetRightArea() ) );
//STRIP001      if (rParam.pBorder)
//STRIP001          nMaxHeight += lcl_LineTotal( rParam.pBorder->GetTop() ) +
//STRIP001                        lcl_LineTotal( rParam.pBorder->GetBottom() ) +
//STRIP001                                  rParam.pBorder->GetDistance(BOX_LINE_TOP) +
//STRIP001                                  rParam.pBorder->GetDistance(BOX_LINE_BOTTOM);
//STRIP001      if (rParam.pShadow && rParam.pShadow->GetLocation() != SVX_SHADOW_NONE)
//STRIP001          nMaxHeight += rParam.pShadow->CalcShadowSpace(SHADOW_TOP) +
//STRIP001                        rParam.pShadow->CalcShadowSpace(SHADOW_BOTTOM);
//STRIP001
//STRIP001      if (nMaxHeight < rParam.nManHeight-rParam.nDistance)
//STRIP001          nMaxHeight = rParam.nManHeight-rParam.nDistance;        // eingestelltes Minimum
//STRIP001
//STRIP001      aBorderSize.Height() = nMaxHeight;
//STRIP001  }
//STRIP001
//STRIP001  if ( bDoPrint )
//STRIP001  {
//STRIP001      double nOldScaleX = nScaleX;
//STRIP001      double nOldScaleY = nScaleY;
//STRIP001      nScaleX = nScaleY = 1.0;            // direkt in Twips ausgeben
//STRIP001      DrawBorder( aBorderStart.X(), aBorderStart.Y(), aBorderSize.Width(), aBorderSize.Height(),
//STRIP001                      rParam.pBorder, rParam.pBack, rParam.pShadow );
//STRIP001      nScaleX = nOldScaleX;
//STRIP001      nScaleY = nOldScaleY;
//STRIP001
//STRIP001      //  Clipping fuer Text
//STRIP001
//STRIP001      pDev->SetClipRegion( Rectangle( aStart, aPaperSize ) );
//STRIP001
//STRIP001      //  links
//STRIP001
//STRIP001      pObject = pHFItem->GetLeftArea();
//STRIP001      if (pObject)
//STRIP001      {
//STRIP001          pEditDefaults->Put( SvxAdjustItem( SVX_ADJUST_LEFT, EE_PARA_JUST ) );
//STRIP001          pEditEngine->SetTextNewDefaults( *pObject, *pEditDefaults, FALSE );
//STRIP001          Point aDraw = aStart;
//STRIP001          long nDif = aPaperSize.Height() - (long) pEditEngine->GetTextHeight();
//STRIP001          if (nDif > 0)
//STRIP001              aDraw.Y() += nDif / 2;
//STRIP001          pEditEngine->Draw( pDev, aDraw, 0 );
//STRIP001      }
//STRIP001
//STRIP001      //  Mitte
//STRIP001
//STRIP001      pObject = pHFItem->GetCenterArea();
//STRIP001      if (pObject)
//STRIP001      {
//STRIP001          pEditDefaults->Put( SvxAdjustItem( SVX_ADJUST_CENTER, EE_PARA_JUST ) );
//STRIP001          pEditEngine->SetTextNewDefaults( *pObject, *pEditDefaults, FALSE );
//STRIP001          Point aDraw = aStart;
//STRIP001          long nDif = aPaperSize.Height() - (long) pEditEngine->GetTextHeight();
//STRIP001          if (nDif > 0)
//STRIP001              aDraw.Y() += nDif / 2;
//STRIP001          pEditEngine->Draw( pDev, aDraw, 0 );
//STRIP001      }
//STRIP001
//STRIP001      //  rechts
//STRIP001
//STRIP001      pObject = pHFItem->GetRightArea();
//STRIP001      if (pObject)
//STRIP001      {
//STRIP001          pEditDefaults->Put( SvxAdjustItem( SVX_ADJUST_RIGHT, EE_PARA_JUST ) );
//STRIP001          pEditEngine->SetTextNewDefaults( *pObject, *pEditDefaults, FALSE );
//STRIP001          Point aDraw = aStart;
//STRIP001          long nDif = aPaperSize.Height() - (long) pEditEngine->GetTextHeight();
//STRIP001          if (nDif > 0)
//STRIP001              aDraw.Y() += nDif / 2;
//STRIP001          pEditEngine->Draw( pDev, aDraw, 0 );
//STRIP001      }
//STRIP001
//STRIP001      pDev->SetClipRegion();
//STRIP001  }
//STRIP001
//STRIP001  if ( pLocationData )
//STRIP001  {
//STRIP001      Rectangle aHeaderRect( aBorderStart, aBorderSize );
//STRIP001      pLocationData->AddHeaderFooter( aHeaderRect, bHeader, bLeft );
//STRIP001  }
//STRIP001 }

//STRIP001 long ScPrintFunc::DoNotes( long nNoteStart, BOOL bDoPrint, ScPreviewLocationData* pLocationData )
//STRIP001 {
//STRIP001  if (bDoPrint)
//STRIP001      pDev->SetMapMode(aTwipMode);
//STRIP001
//STRIP001  MakeEditEngine();
//STRIP001  pEditDefaults->Put( SvxAdjustItem( SVX_ADJUST_LEFT, EE_PARA_JUST ) );
//STRIP001  pEditEngine->SetDefaults( *pEditDefaults );
//STRIP001
//STRIP001  Font aMarkFont;
//STRIP001  ScAutoFontColorMode eColorMode = bUseStyleColor ? SC_AUTOCOL_DISPLAY : SC_AUTOCOL_PRINT;
//STRIP001  ((const ScPatternAttr&)pDoc->GetPool()->GetDefaultItem(ATTR_PATTERN)).GetFont( aMarkFont, eColorMode );
//STRIP001 //?  aMarkFont.SetWeight( WEIGHT_BOLD );
//STRIP001  pDev->SetFont( aMarkFont );
//STRIP001  long nMarkLen = pDev->GetTextWidth(
//STRIP001          String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("GW99999:")));
//STRIP001  // ohne Space, weil's eh selten so weit kommt
//STRIP001
//STRIP001  Size aDataSize = aPageRect.GetSize();
//STRIP001  if ( nMarkLen > aDataSize.Width() / 2 )     // alles viel zu klein?
//STRIP001      nMarkLen = aDataSize.Width() / 2;       // Seite bruederlich aufteilen
//STRIP001  aDataSize.Width() -= nMarkLen;
//STRIP001
//STRIP001  pEditEngine->SetPaperSize( aDataSize );
//STRIP001  long nPosX = aPageRect.Left() + nMarkLen;
//STRIP001  long nPosY = aPageRect.Top();
//STRIP001
//STRIP001  long nCount = 0;
//STRIP001  BOOL bOk;
//STRIP001  do
//STRIP001  {
//STRIP001      bOk = FALSE;
//STRIP001      ScTripel* pPos = (ScTripel*) aNotePosList.GetObject( nNoteStart+nCount );
//STRIP001      if (pPos)
//STRIP001      {
//STRIP001          ScBaseCell* pCell;
//STRIP001          pDoc->GetCell( pPos->GetCol(), pPos->GetRow(), pPos->GetTab(), pCell );
//STRIP001          const ScPostIt* pNote = pCell->GetNotePtr();
//STRIP001          if (pNote)
//STRIP001          {
//STRIP001              String aString = pNote->GetText();
//STRIP001              pEditEngine->SetText(aString);
//STRIP001              long nTextHeight = pEditEngine->GetTextHeight();
//STRIP001              if ( nPosY + nTextHeight < aPageRect.Bottom() )
//STRIP001              {
//STRIP001                  if (bDoPrint)
//STRIP001                  {
//STRIP001                      pEditEngine->Draw( pDev, Point( nPosX, nPosY ), 0 );
//STRIP001
//STRIP001                      ScAddress aAddress( pPos->GetCol(), pPos->GetRow(), pPos->GetTab() );
//STRIP001                      String aMarkStr;
//STRIP001                      aAddress.Format( aMarkStr, SCA_VALID, pDoc );
//STRIP001                      aMarkStr += ':';
//STRIP001
//STRIP001                      //  Zellposition auch per EditEngine, damit die Position stimmt
//STRIP001                      pEditEngine->SetText(aMarkStr);
//STRIP001                      pEditEngine->Draw( pDev, Point( aPageRect.Left(), nPosY ), 0 );
//STRIP001                  }
//STRIP001
//STRIP001                  if ( pLocationData )
//STRIP001                  {
//STRIP001                      ScAddress aAddress( pPos->GetCol(), pPos->GetRow(), pPos->GetTab() );
//STRIP001                      Rectangle aTextRect( Point( nPosX, nPosY ), Size( aDataSize.Width(), nTextHeight ) );
//STRIP001                      pLocationData->AddNoteText( aTextRect, aAddress );
//STRIP001                      Rectangle aMarkRect( Point( aPageRect.Left(), nPosY ), Size( nMarkLen, nTextHeight ) );
//STRIP001                      pLocationData->AddNoteMark( aMarkRect, aAddress );
//STRIP001                  }
//STRIP001
//STRIP001                  nPosY += nTextHeight;
//STRIP001                  nPosY += 200;                   // Abstand
//STRIP001                  ++nCount;
//STRIP001                  bOk = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  while (bOk);
//STRIP001
//STRIP001  return nCount;
//STRIP001 }

//STRIP001 long ScPrintFunc::PrintNotes( long nPageNo, long nNoteStart, BOOL bDoPrint, ScPreviewLocationData* pLocationData )
//STRIP001 {
//STRIP001  if ( nNoteStart >= (long) aNotePosList.Count() || !aTableParam.bNotes )
//STRIP001      return 0;
//STRIP001
//STRIP001  if ( bDoPrint && bClearWin )
//STRIP001  {
//STRIP001      //! mit PrintPage zusammenfassen !!!
//STRIP001
//STRIP001      Color aBackgroundColor( COL_WHITE );
//STRIP001      if ( bUseStyleColor )
//STRIP001             aBackgroundColor.SetColor( SC_MOD()->GetColorConfig().GetColorValue(svtools::DOCCOLOR).nColor );
//STRIP001
//STRIP001      pDev->SetMapMode(aOffsetMode);
//STRIP001      pDev->SetLineColor();
//STRIP001      pDev->SetFillColor(aBackgroundColor);
//STRIP001      pDev->DrawRect(Rectangle(Point(),
//STRIP001              Size((long)(aPageSize.Width() * nScaleX * 100 / nZoom),
//STRIP001                   (long)(aPageSize.Height() * nScaleY * 100 / nZoom))));
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  //      aPageRect auf linke / rechte Seiten anpassen
//STRIP001
//STRIP001  Rectangle aTempRect = Rectangle( Point(), aPageSize );
//STRIP001  if (IsMirror(nPageNo))
//STRIP001  {
//STRIP001      aPageRect.Left()  = ( aTempRect.Left()  + nRightMargin ) * 100 / nZoom;
//STRIP001      aPageRect.Right() = ( aTempRect.Right() - nLeftMargin  ) * 100 / nZoom;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aPageRect.Left()  = ( aTempRect.Left()  + nLeftMargin  ) * 100 / nZoom;
//STRIP001      aPageRect.Right() = ( aTempRect.Right() - nRightMargin ) * 100 / nZoom;
//STRIP001  }
//STRIP001
//STRIP001  if ( pPrinter && bDoPrint )
//STRIP001      pPrinter->StartPage();
//STRIP001
//STRIP001  if ( bDoPrint || pLocationData )
//STRIP001  {
//STRIP001      //  Kopf- und Fusszeilen
//STRIP001
//STRIP001      if (aHdr.bEnable)
//STRIP001      {
//STRIP001          long nHeaderY = aPageRect.Top()-aHdr.nHeight;
//STRIP001          PrintHF( nPageNo, TRUE, nHeaderY, bDoPrint, pLocationData );
//STRIP001      }
//STRIP001      if (aFtr.bEnable)
//STRIP001      {
//STRIP001          long nFooterY = aPageRect.Bottom()+aFtr.nDistance;
//STRIP001          PrintHF( nPageNo, FALSE, nFooterY, bDoPrint, pLocationData );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  long nCount = DoNotes( nNoteStart, bDoPrint, pLocationData );
//STRIP001
//STRIP001  if ( pPrinter && bDoPrint )
//STRIP001      pPrinter->EndPage();
//STRIP001
//STRIP001  return nCount;
//STRIP001 }

//STRIP001 void ScPrintFunc::PrintPage( long nPageNo, USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                              BOOL bDoPrint, ScPreviewLocationData* pLocationData )
//STRIP001 {
//STRIP001  //  nPageNo - Seitennummer innerhalb einer "Startseite"-Einstellung
//STRIP001
//STRIP001  if ( bClearWin && bDoPrint )
//STRIP001  {
//STRIP001      //  muss genau zum Zeichnen des Rahmens in preview.cxx passen !!!
//STRIP001
//STRIP001      Color aBackgroundColor( COL_WHITE );
//STRIP001      if ( bUseStyleColor )
//STRIP001             aBackgroundColor.SetColor( SC_MOD()->GetColorConfig().GetColorValue(svtools::DOCCOLOR).nColor );
//STRIP001
//STRIP001      pDev->SetMapMode(aOffsetMode);
//STRIP001      pDev->SetLineColor();
//STRIP001      pDev->SetFillColor(aBackgroundColor);
//STRIP001      pDev->DrawRect(Rectangle(Point(),
//STRIP001              Size((long)(aPageSize.Width() * nScaleX * 100 / nZoom),
//STRIP001                   (long)(aPageSize.Height() * nScaleY * 100 / nZoom))));
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  //      aPageRect auf linke / rechte Seiten anpassen
//STRIP001
//STRIP001  Rectangle aTempRect = Rectangle( Point(), aPageSize );
//STRIP001  if (IsMirror(nPageNo))
//STRIP001  {
//STRIP001      aPageRect.Left()  = ( aTempRect.Left()  + nRightMargin ) * 100 / nZoom;
//STRIP001      aPageRect.Right() = ( aTempRect.Right() - nLeftMargin  ) * 100 / nZoom;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aPageRect.Left()  = ( aTempRect.Left()  + nLeftMargin  ) * 100 / nZoom;
//STRIP001      aPageRect.Right() = ( aTempRect.Right() - nRightMargin ) * 100 / nZoom;
//STRIP001  }
//STRIP001
//STRIP001  if ( aAreaParam.bRepeatCol )
//STRIP001      if ( nX1 > nRepeatStartCol && nX1 <= nRepeatEndCol )
//STRIP001          nX1 = nRepeatEndCol + 1;
//STRIP001  BOOL bDoRepCol = (aAreaParam.bRepeatCol && nX1 > nRepeatEndCol);
//STRIP001  if ( aAreaParam.bRepeatRow )
//STRIP001      if ( nY1 > nRepeatStartRow && nY1 <= nRepeatEndRow )
//STRIP001          nY1 = nRepeatEndRow + 1;
//STRIP001  BOOL bDoRepRow = (aAreaParam.bRepeatRow && nY1 > nRepeatEndRow);
//STRIP001
//STRIP001  nObjectFlags = 0;
//STRIP001  if ( aTableParam.bDrawings )
//STRIP001      nObjectFlags |= SC_OBJECTS_DRAWING;
//STRIP001  if ( aTableParam.bObjects )
//STRIP001      nObjectFlags |= SC_OBJECTS_OLE;
//STRIP001  if ( aTableParam.bCharts )
//STRIP001      nObjectFlags |= SC_OBJECTS_CHARTS;
//STRIP001
//STRIP001  USHORT i;
//STRIP001
//STRIP001  if ( pPrinter && bDoPrint )
//STRIP001      pPrinter->StartPage();
//STRIP001
//STRIP001  //  Kopf- und Fusszeilen (ohne Zentrierung)
//STRIP001
//STRIP001  if (aHdr.bEnable)
//STRIP001  {
//STRIP001      long nHeaderY = aPageRect.Top()-aHdr.nHeight;
//STRIP001      PrintHF( nPageNo, TRUE, nHeaderY, bDoPrint, pLocationData );
//STRIP001  }
//STRIP001  if (aFtr.bEnable)
//STRIP001  {
//STRIP001      long nFooterY = aPageRect.Bottom()+aFtr.nDistance;
//STRIP001      PrintHF( nPageNo, FALSE, nFooterY, bDoPrint, pLocationData );
//STRIP001  }
//STRIP001
//STRIP001  //  Position ( Raender / zentrieren )
//STRIP001
//STRIP001  long nLeftSpace = aPageRect.Left();     // Document-Twips
//STRIP001  long nTopSpace  = aPageRect.Top();
//STRIP001  if ( bCenterHor )
//STRIP001  {
//STRIP001      long nDataWidth = 0;
//STRIP001      for (i=nX1; i<=nX2; i++)
//STRIP001          nDataWidth += pDoc->GetColWidth( i,nPrintTab );
//STRIP001      if (bDoRepCol)
//STRIP001          for (i=nRepeatStartCol; i<=nRepeatEndCol; i++)
//STRIP001              nDataWidth += pDoc->GetColWidth( i,nPrintTab );
//STRIP001      if (aTableParam.bHeaders)
//STRIP001          nDataWidth += (long) PRINT_HEADER_WIDTH;
//STRIP001      if (pBorderItem)
//STRIP001          nDataWidth += pBorderItem->GetDistance(BOX_LINE_LEFT) +
//STRIP001                         pBorderItem->GetDistance(BOX_LINE_RIGHT);        //! Line width?
//STRIP001      if (pShadowItem && pShadowItem->GetLocation() != SVX_SHADOW_NONE)
//STRIP001          nDataWidth += pShadowItem->CalcShadowSpace(SHADOW_LEFT) +
//STRIP001                         pShadowItem->CalcShadowSpace(SHADOW_RIGHT);
//STRIP001      nLeftSpace += ( aPageRect.GetWidth() - nDataWidth ) / 2;
//STRIP001      if (pBorderItem)
//STRIP001          nLeftSpace -= lcl_LineTotal(pBorderItem->GetLeft());
//STRIP001  }
//STRIP001  if ( bCenterVer )
//STRIP001  {
//STRIP001      long nDataHeight = 0;
//STRIP001      for (i=nY1; i<=nY2; i++)
//STRIP001          nDataHeight += pDoc->FastGetRowHeight( i,nPrintTab );
//STRIP001      if (bDoRepRow)
//STRIP001          for (i=nRepeatStartRow; i<=nRepeatEndRow; i++)
//STRIP001              nDataHeight += pDoc->FastGetRowHeight( i,nPrintTab );
//STRIP001      if (aTableParam.bHeaders)
//STRIP001          nDataHeight += (long) PRINT_HEADER_HEIGHT;
//STRIP001      if (pBorderItem)
//STRIP001          nDataHeight += pBorderItem->GetDistance(BOX_LINE_TOP) +
//STRIP001                         pBorderItem->GetDistance(BOX_LINE_BOTTOM);       //! Line width?
//STRIP001      if (pShadowItem && pShadowItem->GetLocation() != SVX_SHADOW_NONE)
//STRIP001          nDataHeight += pShadowItem->CalcShadowSpace(SHADOW_TOP) +
//STRIP001                         pShadowItem->CalcShadowSpace(SHADOW_BOTTOM);
//STRIP001      nTopSpace += ( aPageRect.GetHeight() - nDataHeight ) / 2;
//STRIP001      if (pBorderItem)
//STRIP001          nTopSpace -= lcl_LineTotal(pBorderItem->GetTop());
//STRIP001  }
//STRIP001
//STRIP001  //  Seite aufteilen
//STRIP001
//STRIP001  long nStartX = ((long) ( nLeftSpace * nScaleX ));
//STRIP001  long nStartY = ((long) ( nTopSpace  * nScaleY ));
//STRIP001 //       nStartX -= aOffset.X();         // schon im MapMode
//STRIP001 //       nStartY -= aOffset.Y();
//STRIP001
//STRIP001  long nInnerStartX = nStartX;
//STRIP001  long nInnerStartY = nStartY;
//STRIP001  if (pBorderItem)
//STRIP001  {
//STRIP001      nInnerStartX += (long) ( ( lcl_LineTotal(pBorderItem->GetLeft()) +
//STRIP001                                  pBorderItem->GetDistance(BOX_LINE_LEFT) ) * nScaleX );
//STRIP001      nInnerStartY += (long) ( ( lcl_LineTotal(pBorderItem->GetTop()) +
//STRIP001                                  pBorderItem->GetDistance(BOX_LINE_TOP) ) * nScaleY );
//STRIP001  }
//STRIP001  if (pShadowItem && pShadowItem->GetLocation() != SVX_SHADOW_NONE)
//STRIP001  {
//STRIP001      nInnerStartX += (long) ( pShadowItem->CalcShadowSpace(SHADOW_LEFT) * nScaleX );
//STRIP001      nInnerStartY += (long) ( pShadowItem->CalcShadowSpace(SHADOW_TOP) * nScaleY );
//STRIP001  }
//STRIP001  long nRepStartX = nInnerStartX;
//STRIP001  long nRepStartY = nInnerStartY;
//STRIP001  if (aTableParam.bHeaders)
//STRIP001  {
//STRIP001      nRepStartX += (long) (PRINT_HEADER_WIDTH * nScaleX);
//STRIP001      nRepStartY += (long) (PRINT_HEADER_HEIGHT * nScaleY);
//STRIP001  }
//STRIP001  long nDataX = nRepStartX;
//STRIP001  long nDataY = nRepStartY;
//STRIP001  if (bDoRepCol)
//STRIP001      for (i=nRepeatStartCol; i<=nRepeatEndCol; i++)
//STRIP001          nDataX += (long) (pDoc->GetColWidth(i,nPrintTab) * nScaleX);
//STRIP001  if (bDoRepRow)
//STRIP001      for (i=nRepeatStartRow; i<=nRepeatEndRow; i++)
//STRIP001          nDataY += (long) (pDoc->FastGetRowHeight(i,nPrintTab) * nScaleY);
//STRIP001  long nEndX = nDataX;
//STRIP001  long nEndY = nDataY;
//STRIP001  for (i=nX1; i<=nX2; i++)
//STRIP001      nEndX += (long) (pDoc->GetColWidth(i,nPrintTab) * nScaleX);
//STRIP001  for (i=nY1; i<=nY2; i++)
//STRIP001      nEndY += (long) (pDoc->FastGetRowHeight(i,nPrintTab) * nScaleY);
//STRIP001
//STRIP001  //  Seiten-Rahmen / Hintergrund
//STRIP001
//STRIP001  //! nEndX/Y anpassen
//STRIP001
//STRIP001  long nBorderEndX = nEndX;
//STRIP001  long nBorderEndY = nEndY;
//STRIP001  if (pBorderItem)
//STRIP001  {
//STRIP001      nBorderEndX += (long) ( ( lcl_LineTotal(pBorderItem->GetRight()) +
//STRIP001                                  pBorderItem->GetDistance(BOX_LINE_RIGHT) ) * nScaleX );
//STRIP001      nBorderEndY += (long) ( ( lcl_LineTotal(pBorderItem->GetBottom()) +
//STRIP001                                  pBorderItem->GetDistance(BOX_LINE_BOTTOM) ) * nScaleY );
//STRIP001  }
//STRIP001  if (pShadowItem && pShadowItem->GetLocation() != SVX_SHADOW_NONE)
//STRIP001  {
//STRIP001      nBorderEndX += (long) ( pShadowItem->CalcShadowSpace(SHADOW_RIGHT) * nScaleX );
//STRIP001      nBorderEndY += (long) ( pShadowItem->CalcShadowSpace(SHADOW_BOTTOM) * nScaleY );
//STRIP001  }
//STRIP001
//STRIP001  if ( bDoPrint )
//STRIP001  {
//STRIP001      pDev->SetMapMode( aOffsetMode );
//STRIP001      DrawBorder( nStartX, nStartY, nBorderEndX-nStartX, nBorderEndY-nStartY,
//STRIP001                      pBorderItem, pBackgroundItem, pShadowItem );
//STRIP001
//STRIP001      pDev->SetMapMode( aTwipMode );
//STRIP001      SFX_APP()->SpoilDemoOutput( *pDev, aPageRect );
//STRIP001  }
//STRIP001
//STRIP001  pDev->SetMapMode( aOffsetMode );
//STRIP001
//STRIP001  //  Wiederholungszeilen/Spalten ausgeben
//STRIP001
//STRIP001  if (bDoRepCol && bDoRepRow)
//STRIP001  {
//STRIP001      if ( bDoPrint )
//STRIP001          PrintArea( nRepeatStartCol,nRepeatStartRow, nRepeatEndCol,nRepeatEndRow,
//STRIP001                          nRepStartX,nRepStartY, TRUE,TRUE,FALSE,FALSE );
//STRIP001      if ( pLocationData )
//STRIP001          LocateArea( nRepeatStartCol,nRepeatStartRow, nRepeatEndCol,nRepeatEndRow,
//STRIP001                          nRepStartX,nRepStartY, TRUE,TRUE, *pLocationData );
//STRIP001  }
//STRIP001  if (bDoRepCol)
//STRIP001  {
//STRIP001      if ( bDoPrint )
//STRIP001          PrintArea( nRepeatStartCol,nY1, nRepeatEndCol,nY2, nRepStartX,nDataY,
//STRIP001                      TRUE,!bDoRepRow,FALSE,TRUE );
//STRIP001      if ( pLocationData )
//STRIP001          LocateArea( nRepeatStartCol,nY1, nRepeatEndCol,nY2, nRepStartX,nDataY, TRUE,FALSE, *pLocationData );
//STRIP001  }
//STRIP001  if (bDoRepRow)
//STRIP001  {
//STRIP001      if ( bDoPrint )
//STRIP001          PrintArea( nX1,nRepeatStartRow, nX2,nRepeatEndRow, nDataX,nRepStartY,
//STRIP001                      !bDoRepCol,TRUE,TRUE,FALSE );
//STRIP001      if ( pLocationData )
//STRIP001          LocateArea( nX1,nRepeatStartRow, nX2,nRepeatEndRow, nDataX,nRepStartY, FALSE,TRUE, *pLocationData );
//STRIP001  }
//STRIP001
//STRIP001  //  Daten ausgeben
//STRIP001
//STRIP001  if ( bDoPrint )
//STRIP001      PrintArea( nX1,nY1, nX2,nY2, nDataX,nDataY, !bDoRepCol,!bDoRepRow,TRUE,TRUE );
//STRIP001  if ( pLocationData )
//STRIP001      LocateArea( nX1,nY1, nX2,nY2, nDataX,nDataY, FALSE,FALSE, *pLocationData );
//STRIP001
//STRIP001  //  Spalten-/Zeilenkoepfe ausgeben
//STRIP001  //  nach den Daten (ueber evtl. weitergezeichneten Schatten)
//STRIP001
//STRIP001  Color aGridColor( COL_BLACK );
//STRIP001  if ( bUseStyleColor )
//STRIP001         aGridColor.SetColor( SC_MOD()->GetColorConfig().GetColorValue(svtools::FONTCOLOR).nColor );
//STRIP001
//STRIP001  if (aTableParam.bHeaders)
//STRIP001  {
//STRIP001      if ( bDoPrint )
//STRIP001      {
//STRIP001          pDev->SetLineColor( aGridColor );
//STRIP001          pDev->SetFillColor();
//STRIP001          pDev->SetMapMode(aOffsetMode);
//STRIP001      }
//STRIP001
//STRIP001      ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001      Font aFont;
//STRIP001      ScAutoFontColorMode eColorMode = bUseStyleColor ? SC_AUTOCOL_DISPLAY : SC_AUTOCOL_PRINT;
//STRIP001      aPattern.GetFont( aFont, eColorMode, pDev );
//STRIP001      pDev->SetFont( aFont );
//STRIP001
//STRIP001      if (bDoRepCol)
//STRIP001      {
//STRIP001          if ( bDoPrint )
//STRIP001              PrintColHdr( nRepeatStartCol,nRepeatEndCol, nRepStartX,nInnerStartY );
//STRIP001          if ( pLocationData )
//STRIP001              LocateColHdr( nRepeatStartCol,nRepeatEndCol, nRepStartX,nInnerStartY, TRUE, *pLocationData );
//STRIP001      }
//STRIP001      if ( bDoPrint )
//STRIP001          PrintColHdr( nX1,nX2, nDataX,nInnerStartY );
//STRIP001      if ( pLocationData )
//STRIP001          LocateColHdr( nX1,nX2, nDataX,nInnerStartY, FALSE, *pLocationData );
//STRIP001      if (bDoRepRow)
//STRIP001      {
//STRIP001          if ( bDoPrint )
//STRIP001              PrintRowHdr( nRepeatStartRow,nRepeatEndRow, nInnerStartX,nRepStartY );
//STRIP001          if ( pLocationData )
//STRIP001              LocateRowHdr( nRepeatStartRow,nRepeatEndRow, nInnerStartX,nRepStartY, TRUE, *pLocationData );
//STRIP001      }
//STRIP001      if ( bDoPrint )
//STRIP001          PrintRowHdr( nY1,nY2, nInnerStartX,nDataY );
//STRIP001      if ( pLocationData )
//STRIP001          LocateRowHdr( nY1,nY2, nInnerStartX,nDataY, FALSE, *pLocationData );
//STRIP001  }
//STRIP001
//STRIP001  //  einfacher Rahmen
//STRIP001
//STRIP001  if ( bDoPrint && ( aTableParam.bGrid || aTableParam.bHeaders ) )
//STRIP001  {
//STRIP001      Size aOnePixel = pDev->PixelToLogic(Size(1,1));
//STRIP001      long nOneX = aOnePixel.Width();
//STRIP001      long nOneY = aOnePixel.Height();
//STRIP001
//STRIP001      long nLeftX = nInnerStartX-nOneX;
//STRIP001      long nTopY  = nInnerStartY-nOneY;
//STRIP001      pDev->SetMapMode(aOffsetMode);
//STRIP001      pDev->SetLineColor( aGridColor );
//STRIP001      pDev->SetFillColor();
//STRIP001      pDev->DrawRect( Rectangle( nLeftX, nTopY, nEndX-nOneX, nEndY-nOneY ) );
//STRIP001      //  nEndX/Y ohne Rahmen-Anpassung
//STRIP001  }
//STRIP001
//STRIP001  if ( pPrinter && bDoPrint )
//STRIP001      pPrinter->EndPage();
//STRIP001
//STRIP001  aLastSourceRange = ScRange( nX1, nY1, nPrintTab, nX2, nY2, nPrintTab );
//STRIP001  bSourceRangeValid = TRUE;
//STRIP001 }

//STRIP001 void ScPrintFunc::SetOffset( const Point& rOfs )
//STRIP001 {
//STRIP001  aSrcOffset = rOfs;
//STRIP001 }

//STRIP001 void ScPrintFunc::SetManualZoom( USHORT nNewZoom )
//STRIP001 {
//STRIP001  nManualZoom = nNewZoom;
//STRIP001 }

//STRIP001 void ScPrintFunc::SetClearFlag( BOOL bFlag )
//STRIP001 {
//STRIP001  bClearWin = bFlag;
//STRIP001 }

//STRIP001 void ScPrintFunc::SetUseStyleColor( BOOL bFlag )
//STRIP001 {
//STRIP001  bUseStyleColor = bFlag;
//STRIP001  if (pEditEngine)
//STRIP001      pEditEngine->EnableAutoColor( bUseStyleColor );
//STRIP001 }

/*M*/ void ScPrintFunc::SetRenderFlag( BOOL bFlag )
/*M*/ {
/*M*/   bIsRender = bFlag;      // set when using XRenderable (PDF)
/*M*/ }

//
//  UpdatePages wird nur von aussen gerufen, um die Umbrueche fuer die Anzeige
//  richtig zu setzen - immer ohne UserArea
//

/*N*/ BOOL ScPrintFunc::UpdatePages()
/*N*/ {
/*N*/   if (!pParamSet)
/*N*/       return FALSE;
/*N*/
/*N*/   //  Zoom
/*N*/
/*N*/   nZoom = 100;
/*N*/   if (aTableParam.bScalePageNum)
/*N*/       nZoom = ZOOM_MIN;                       // stimmt fuer Umbrueche
/*N*/   else if (aTableParam.bScaleAll)
/*N*/   {
/*N*/       nZoom = aTableParam.nScaleAll;
/*N*/       if ( nZoom <= ZOOM_MIN )
/*N*/           nZoom = ZOOM_MIN;
/*N*/   }
/*N*/
/*N*/   String aName = pDoc->GetPageStyle( nPrintTab );
/*N*/   USHORT nTabCount = pDoc->GetTableCount();
/*N*/   for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/       if ( nTab==nPrintTab || pDoc->GetPageStyle(nTab)==aName )
/*N*/       {
/*N*/           //  Wiederholungszeilen / Spalten
/*N*/           pDoc->SetRepeatArea( nTab, nRepeatStartCol,nRepeatEndCol, nRepeatStartRow,nRepeatEndRow );
/*N*/
/*N*/           //  Umbrueche setzen
/*N*/           ResetBreaks(nTab);
/*N*/           pDocShell->PostPaint(0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID);
/*N*/       }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ long ScPrintFunc::CountPages()                            // setzt auch nPagesX, nPagesY
/*N*/ {
/*N*/   BOOL bAreaOk = FALSE;
/*N*/
/*N*/   if (pDoc->HasTable( nPrintTab ))
/*N*/   {
/*N*/       if (aAreaParam.bPrintArea)                          // Druckbereich angegeben?
/*N*/       {
/*N*/           if ( bPrintCurrentTable )
/*N*/           {
/*N*/               ScRange& rRange = aAreaParam.aPrintArea;
/*N*/
/*N*/               //  hier kein Vergleich der Tabellen mehr, die Area gilt immer fuer diese Tabelle
/*N*/               //  wenn hier verglichen werden soll, muss die Tabelle der Druckbereiche beim
/*N*/               //  Einfuegen von Tabellen etc. angepasst werden !
/*N*/
/*N*/               nStartCol = rRange.aStart.Col();
/*N*/               nStartRow = rRange.aStart.Row();
/*N*/               nEndCol   = rRange.aEnd  .Col();
/*N*/               nEndRow   = rRange.aEnd  .Row();
/*N*/               bAreaOk   = AdjustPrintArea(FALSE);         // begrenzen
/*N*/           }
/*N*/           else
/*N*/               bAreaOk = FALSE;
/*N*/       }
/*N*/       else                                                // aus Dokument suchen
/*N*/           bAreaOk = AdjustPrintArea(TRUE);
/*N*/   }
/*N*/
/*N*/   if (bAreaOk)
/*N*/   {
/*N*/       long nPages = 0;
/*N*/       USHORT nY;
/*N*/       if (bMultiArea)
/*N*/       {
/*?*/           USHORT nRCount = pDoc->GetPrintRangeCount( nPrintTab );
/*?*/           for (USHORT i=0; i<nRCount; i++)
/*?*/           {
/*?*/               CalcZoom(i);
/*?*/               if ( aTableParam.bSkipEmpty )
/*?*/                   for (nY=0; nY<nPagesY; nY++)
                            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/                       nPages += pPageRows[nY].CountVisible();
/*?*/               else
/*?*/                   nPages += ((long) nPagesX) * nPagesY;
/*?*/               if ( pPageData )
                        {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/                   FillPageData();
/*?*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           CalcZoom(RANGENO_NORANGE);                      // Zoom berechnen
/*N*/           if ( aTableParam.bSkipEmpty )
/*?*/               for (nY=0; nY<nPagesY; nY++)
                        {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/                   nPages += pPageRows[nY].CountVisible();
/*N*/           else
/*N*/               nPages += ((long) nPagesX) * nPagesY;
/*N*/           if ( pPageData )
                    {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/               FillPageData();
/*N*/       }
/*N*/       return nPages;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/ //        nZoom = 100;                        // nZoom auf letztem Wert stehenlassen !!!
/*N*/       nPagesX = nPagesY = nTotalY = 0;
/*N*/       return 0;
/*N*/   }
/*N*/ }

/*N*/ long ScPrintFunc::CountNotePages()
/*N*/ {
/*N*/   if ( !aTableParam.bNotes || !bPrintCurrentTable )
/*N*/       return 0;
/*N*/
/*?*/   long nCount=0;
/*?*/   USHORT nCol;
/*?*/   USHORT nRow;
/*?*/
/*?*/   BOOL bError = FALSE;
/*?*/   if (!aAreaParam.bPrintArea)
/*?*/       bError = !AdjustPrintArea(TRUE);            // komplett aus Dok suchen
/*?*/
/*?*/   USHORT nRepeats = 1;                            // wie oft durchgehen ?
/*?*/   if (bMultiArea)
/*?*/       nRepeats = pDoc->GetPrintRangeCount(nPrintTab);
/*?*/   if (bError)
/*?*/       nRepeats = 0;
/*?*/
/*?*/   for (USHORT nStep=0; nStep<nRepeats; nStep++)
/*?*/   {
/*?*/       BOOL bDoThis = TRUE;
/*?*/       if (bMultiArea)             // alle Areas durchgehen
/*?*/       {
/*?*/           const ScRange* pThisRange = pDoc->GetPrintRange( nPrintTab, nStep );
/*?*/           if ( pThisRange )
/*?*/           {
/*?*/               nStartCol = pThisRange->aStart.Col();
/*?*/               nStartRow = pThisRange->aStart.Row();
/*?*/               nEndCol   = pThisRange->aEnd  .Col();
/*?*/               nEndRow   = pThisRange->aEnd  .Row();
/*?*/               bDoThis = AdjustPrintArea(FALSE);
/*?*/           }
/*?*/       }
/*?*/
/*?*/       if (bDoThis)
/*?*/       {
/*?*/           ScHorizontalCellIterator aIter( pDoc, nPrintTab, nStartCol,nStartRow, nEndCol,nEndRow );
/*?*/           ScBaseCell* pCell = aIter.GetNext( nCol, nRow );
/*?*/           while (pCell)
/*?*/           {
/*?*/               if (pCell->GetNotePtr())
/*?*/               {
/*?*/                   aNotePosList.Insert( new ScTripel( nCol,nRow,nPrintTab ), LIST_APPEND );
/*?*/                   ++nCount;
/*?*/               }
/*?*/
/*?*/               pCell = aIter.GetNext( nCol, nRow );
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/
/*?*/   long nPages = 0;
/*?*/   long nNoteNr = 0;
/*?*/   long nNoteAdd;
/*?*/   do
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); nNoteAdd=0;//STRIP001
//STRIP001 /*?*/        nNoteAdd = PrintNotes( nPages, nNoteNr, FALSE, NULL );
//STRIP001 /*?*/        if (nNoteAdd)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nNoteNr += nNoteAdd;
//STRIP001 /*?*/            ++nPages;
//STRIP001 /*?*/        }
/*?*/   }
/*?*/   while (nNoteAdd);
/*?*/
/*?*/   return nPages;
/*N*/ }

/*N*/ void ScPrintFunc::InitModes()             // aus nZoom etc. die MapModes setzen
/*N*/ {
/*N*/   aOffset = Point( aSrcOffset.X()*100/nZoom, aSrcOffset.Y()*100/nZoom );
/*N*/
/*N*/   long nEffZoom = nZoom * (long) nManualZoom;
/*N*/
/*N*/ //    nScaleX = nScaleY = 1.0;            // Ausgabe in Twips
/*N*/   nScaleX = nScaleY = HMM_PER_TWIPS;  // Ausgabe in 1/100 mm
/*N*/
/*N*/   Fraction aZoomFract( nEffZoom,10000 );
/*N*/   Fraction aHorFract = aZoomFract;
/*N*/
/*N*/   if ( !pPrinter && !bIsRender )                          // adjust scale for preview
/*N*/   {
/*?*/       double nFact = pDocShell->GetOutputFactor();
/*?*/       aHorFract = Fraction( (long)( nEffZoom / nFact ), 10000 );
/*N*/   }
/*N*/
/*N*/   aLogicMode = MapMode( MAP_100TH_MM, Point(), aHorFract, aZoomFract );
/*N*/
/*N*/   Point aLogicOfs( -aOffset.X(), -aOffset.Y() );
/*N*/   aOffsetMode = MapMode( MAP_100TH_MM, aLogicOfs, aHorFract, aZoomFract );
/*N*/
/*N*/   Point aTwipsOfs( (long) ( -aOffset.X() / nScaleX + 0.5 ), (long) ( -aOffset.Y() / nScaleY + 0.5 ) );
/*N*/   aTwipMode = MapMode( MAP_TWIP, aTwipsOfs, aHorFract, aZoomFract );
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void ScPrintFunc::ApplyPrintSettings()
//STRIP001 {
//STRIP001  if ( pPrinter )
//STRIP001  {
//STRIP001      //
//STRIP001      //  Printer zum Drucken umstellen
//STRIP001      //
//STRIP001
//STRIP001      Size aEnumSize = aPageSize;
//STRIP001      USHORT nPaperBin = ((const SvxPaperBinItem&)pParamSet->Get(ATTR_PAGE_PAPERBIN)).GetValue();
//STRIP001
//STRIP001      pPrinter->SetOrientation( bLandscape ? ORIENTATION_LANDSCAPE : ORIENTATION_PORTRAIT );
//STRIP001
//STRIP001      MapMode aPrinterMode = pPrinter->GetMapMode();
//STRIP001      MapMode aLocalMode( MAP_TWIP );
//STRIP001      pPrinter->SetMapMode( aLocalMode );
//STRIP001
//STRIP001      // Let VCL decide which printer paper should be used for printing
//STRIP001      pPrinter->SetPaperSizeUser( aEnumSize );
//STRIP001      pPrinter->SetMapMode( aPrinterMode );
//STRIP001
//STRIP001      pPrinter->SetPaperBin( nPaperBin );
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------
//  rPageRanges   = Range fuer alle Tabellen
//  nStartPage    = in rPageRanges beginnen bei nStartPage
//  nDisplayStart = lfd. Nummer fuer Anzeige der Seitennummer

/*N*/ long ScPrintFunc::DoPrint( const MultiSelection& rPageRanges,
/*N*/                               long nStartPage, long nDisplayStart, BOOL bDoPrint,
/*N*/                               SfxProgress* pProgress, ScPreviewLocationData* pLocationData )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001 DBG_ASSERT(pDev,"Device == NULL");
//STRIP001  if (!pParamSet)
//STRIP001      return 0;
//STRIP001
//STRIP001  if ( pPrinter && bDoPrint )
//STRIP001      ApplyPrintSettings();
//STRIP001
//STRIP001  //--------------------------------------------------------------------
//STRIP001
//STRIP001  InitModes();
//STRIP001  if ( pLocationData )
//STRIP001  {
//STRIP001      pLocationData->SetCellMapMode( aOffsetMode );
//STRIP001      pLocationData->SetPrintTab( nPrintTab );
//STRIP001  }
//STRIP001
//STRIP001  MakeTableString();
//STRIP001
//STRIP001  if ( pProgress )
//STRIP001      pProgress->SetText( String( ScResId( SCSTR_STAT_PRINT ) ) );
//STRIP001
//STRIP001  //--------------------------------------------------------------------
//STRIP001
//STRIP001  long nPageNo = 0;
//STRIP001  long nPrinted = 0;
//STRIP001  long nEndPage = rPageRanges.GetTotalRange().Max();
//STRIP001
//STRIP001  USHORT nRepeats = 1;                    // wie oft durchgehen ?
//STRIP001  if (bMultiArea)
//STRIP001      nRepeats = pDoc->GetPrintRangeCount(nPrintTab);
//STRIP001  for (USHORT nStep=0; nStep<nRepeats; nStep++)
//STRIP001  {
//STRIP001      if (bMultiArea)                     // Bereich neu belegen ?
//STRIP001      {
//STRIP001          CalcZoom(nStep);                // setzt auch nStartCol etc. neu
//STRIP001          InitModes();
//STRIP001      }
//STRIP001
//STRIP001      USHORT nX1;
//STRIP001      USHORT nY1;
//STRIP001      USHORT nX2;
//STRIP001      USHORT nY2;
//STRIP001      USHORT nCountX;
//STRIP001      USHORT nCountY;
//STRIP001
//STRIP001      if (aTableParam.bTopDown)                           // von oben nach unten
//STRIP001      {
//STRIP001          nX1 = nStartCol;
//STRIP001          for (nCountX=0; nCountX<nPagesX; nCountX++)
//STRIP001          {
//STRIP001              nX2 = pPageEndX[nCountX];
//STRIP001              for (nCountY=0; nCountY<nPagesY; nCountY++)
//STRIP001              {
//STRIP001                  nY1 = pPageRows[nCountY].GetStartRow();
//STRIP001                  nY2 = pPageRows[nCountY].GetEndRow();
//STRIP001                  if ( !aTableParam.bSkipEmpty || !pPageRows[nCountY].IsHidden(nCountX) )
//STRIP001                  {
//STRIP001                      if ( rPageRanges.IsSelected( nPageNo+nStartPage+1 ) )
//STRIP001                      {
//STRIP001                          PrintPage( nPageNo+nDisplayStart, nX1, nY1, nX2, nY2,
//STRIP001                                      bDoPrint, pLocationData );
//STRIP001
//STRIP001                          if ( pProgress )
//STRIP001                          {
//STRIP001                              pProgress->SetState( nPageNo+nStartPage+1, nEndPage );
//STRIP001                              pProgress->Reschedule(); //Mag der Anwender noch oder hat er genug?
//STRIP001                          }
//STRIP001                          ++nPrinted;
//STRIP001                      }
//STRIP001                      ++nPageNo;
//STRIP001                  }
//STRIP001              }
//STRIP001              nX1 = nX2 + 1;
//STRIP001          }
//STRIP001      }
//STRIP001      else                                                // von links nach rechts
//STRIP001      {
//STRIP001          for (nCountY=0; nCountY<nPagesY; nCountY++)
//STRIP001          {
//STRIP001              nY1 = pPageRows[nCountY].GetStartRow();
//STRIP001              nY2 = pPageRows[nCountY].GetEndRow();
//STRIP001              nX1 = nStartCol;
//STRIP001              for (nCountX=0; nCountX<nPagesX; nCountX++)
//STRIP001              {
//STRIP001                  nX2 = pPageEndX[nCountX];
//STRIP001                  if ( !aTableParam.bSkipEmpty || !pPageRows[nCountY].IsHidden(nCountX) )
//STRIP001                  {
//STRIP001                      if ( rPageRanges.IsSelected( nPageNo+nStartPage+1 ) )
//STRIP001                      {
//STRIP001                          PrintPage( nPageNo+nDisplayStart, nX1, nY1, nX2, nY2,
//STRIP001                                      bDoPrint, pLocationData );
//STRIP001
//STRIP001                          if ( pProgress )
//STRIP001                          {
//STRIP001                              pProgress->SetState( nPageNo+nStartPage+1, nEndPage );
//STRIP001                              pProgress->Reschedule(); //Mag der Anwender noch oder hat er genug?
//STRIP001                          }
//STRIP001                          ++nPrinted;
//STRIP001                      }
//STRIP001                      ++nPageNo;
//STRIP001                  }
//STRIP001                  nX1 = nX2 + 1;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aFieldData.aTabName = ScGlobal::GetRscString( STR_NOTES );
//STRIP001
//STRIP001  long nNoteNr = 0;
//STRIP001  long nNoteAdd;
//STRIP001  do
//STRIP001  {
//STRIP001      if ( nPageNo+nStartPage <= nEndPage )
//STRIP001      {
//STRIP001          BOOL bPageSelected = rPageRanges.IsSelected( nPageNo+nStartPage+1 );
//STRIP001          nNoteAdd = PrintNotes( nPageNo+nStartPage, nNoteNr, bDoPrint && bPageSelected,
//STRIP001                                  ( bPageSelected ? pLocationData : NULL ) );
//STRIP001          if ( nNoteAdd )
//STRIP001          {
//STRIP001              nNoteNr += nNoteAdd;
//STRIP001              if ( pProgress && bPageSelected )
//STRIP001              {
//STRIP001                  pProgress->SetState( nPageNo+nStartPage+1, nEndPage );
//STRIP001                  pProgress->Reschedule(); //Mag der Anwender noch oder hat er genug?
//STRIP001              }
//STRIP001              if (bPageSelected)
//STRIP001              {
//STRIP001                  ++nPrinted;
//STRIP001                  bSourceRangeValid = FALSE;      // last page was no cell range
//STRIP001              }
//STRIP001              ++nPageNo;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          nNoteAdd = 0;
//STRIP001  }
//STRIP001  while (nNoteAdd);
//STRIP001
//STRIP001  if ( bMultiArea )
//STRIP001      ResetBreaks(nPrintTab);                         // Breaks fuer Anzeige richtig
//STRIP001
//STRIP001  return nPrinted;
/*N*/ }

/*N*/ void ScPrintFunc::CalcZoom( USHORT nRangeNo )                     // Zoom berechnen
/*N*/ {
/*N*/   USHORT nRCount = pDoc->GetPrintRangeCount( nPrintTab );
/*N*/   const ScRange* pThisRange = NULL;
/*N*/   if ( nRangeNo != RANGENO_NORANGE || nRangeNo < nRCount )
/*?*/       pThisRange = pDoc->GetPrintRange( nPrintTab, nRangeNo );
/*N*/   if ( pThisRange )
/*N*/   {
/*?*/       nStartCol = pThisRange->aStart.Col();
/*?*/       nStartRow = pThisRange->aStart.Row();
/*?*/       nEndCol   = pThisRange->aEnd  .Col();
/*?*/       nEndRow   = pThisRange->aEnd  .Row();
/*N*/   }
/*N*/
/*N*/   if (!AdjustPrintArea(FALSE))                        // leer
/*N*/   {
/*N*/       nZoom = 100;
/*N*/       nPagesX = nPagesY = nTotalY = 0;
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   pDoc->SetRepeatArea( nPrintTab, nRepeatStartCol,nRepeatEndCol, nRepeatStartRow,nRepeatEndRow );
/*N*/
/*N*/   if (aTableParam.bScalePageNum)
/*N*/   {
/*N*/       nZoom = 100;
/*N*/       BOOL bFound = FALSE;
/*N*/       USHORT nPagesToFit = aTableParam.nScalePageNum;
/*N*/       while (!bFound)
/*N*/       {
/*N*/           CalcPages();
/*N*/           if ( nPagesX * nPagesY <= nPagesToFit || nZoom <= ZOOM_MIN )
/*N*/               bFound = TRUE;
/*N*/           else
/*N*/               --nZoom;
/*N*/       }
/*N*/   }
/*N*/   else if (aTableParam.bScaleAll)
/*N*/   {
/*N*/       nZoom = aTableParam.nScaleAll;
/*N*/       if ( nZoom <= ZOOM_MIN )
/*N*/           nZoom = ZOOM_MIN;
/*N*/       CalcPages();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ASSERT( aTableParam.bScaleNone, "kein Scale-Flag gesetzt" );
/*N*/       nZoom = 100;
/*N*/       CalcPages();
/*N*/   }
/*N*/ }

/*N*/ Size ScPrintFunc::GetDocPageSize()
/*N*/ {
/*N*/                       // Hoehe Kopf-/Fusszeile anpassen
/*N*/
/*N*/   InitModes();                            // aTwipMode aus nZoom initialisieren
/*N*/   pDev->SetMapMode( aTwipMode );          // Kopf-/Fusszeilen in Twips
/*N*/   UpdateHFHeight( aHdr );
/*N*/   UpdateHFHeight( aFtr );
/*N*/
/*N*/                       // Seitengroesse in Document-Twips
/*N*/                       //  Berechnung Left / Right auch in PrintPage
/*N*/
/*N*/   aPageRect = Rectangle( Point(), aPageSize );
/*N*/   aPageRect.Left()   = ( aPageRect.Left()   + nLeftMargin                  ) * 100 / nZoom;
/*N*/   aPageRect.Right()  = ( aPageRect.Right()  - nRightMargin                 ) * 100 / nZoom;
/*N*/   aPageRect.Top()    = ( aPageRect.Top()    + nTopMargin    ) * 100 / nZoom + aHdr.nHeight;
/*N*/   aPageRect.Bottom() = ( aPageRect.Bottom() - nBottomMargin ) * 100 / nZoom - aFtr.nHeight;
/*N*/
/*N*/   Size aDocPageSize = aPageRect.GetSize();
/*N*/   if (aTableParam.bHeaders)
/*N*/   {
/*N*/       aDocPageSize.Width()  -= (long) PRINT_HEADER_WIDTH;
/*N*/       aDocPageSize.Height() -= (long) PRINT_HEADER_HEIGHT;
/*N*/   }
/*N*/   if (pBorderItem)
/*N*/   {
/*N*/       aDocPageSize.Width()  -= lcl_LineTotal(pBorderItem->GetLeft()) +
/*N*/                                lcl_LineTotal(pBorderItem->GetRight()) +
/*N*/                                pBorderItem->GetDistance(BOX_LINE_LEFT) +
/*N*/                                pBorderItem->GetDistance(BOX_LINE_RIGHT);
/*N*/       aDocPageSize.Height() -= lcl_LineTotal(pBorderItem->GetTop()) +
/*N*/                                lcl_LineTotal(pBorderItem->GetBottom()) +
/*N*/                                pBorderItem->GetDistance(BOX_LINE_TOP) +
/*N*/                                pBorderItem->GetDistance(BOX_LINE_BOTTOM);
/*N*/   }
/*N*/   if (pShadowItem && pShadowItem->GetLocation() != SVX_SHADOW_NONE)
/*N*/   {
/*?*/       aDocPageSize.Width()  -= pShadowItem->CalcShadowSpace(SHADOW_LEFT) +
/*?*/                                pShadowItem->CalcShadowSpace(SHADOW_RIGHT);
/*?*/       aDocPageSize.Height() -= pShadowItem->CalcShadowSpace(SHADOW_TOP) +
/*?*/                                pShadowItem->CalcShadowSpace(SHADOW_BOTTOM);
/*N*/   }
/*N*/   return aDocPageSize;
/*N*/ }

/*N*/ void ScPrintFunc::ResetBreaks( USHORT nTab )          // Breaks fuer Anzeige richtig setzen
/*N*/ {
/*N*/   pDoc->SetPageSize( nTab, GetDocPageSize() );
/*N*/   pDoc->UpdatePageBreaks( nTab, NULL );
/*N*/ }

//STRIP001 void lcl_SetHidden( ScDocument* pDoc, USHORT nPrintTab, ScPageRowEntry& rPageRowEntry,
//STRIP001                  USHORT nStartCol, const USHORT* pPageEndX )
//STRIP001 {
//STRIP001  USHORT nPagesX   = rPageRowEntry.GetPagesX();
//STRIP001  USHORT nStartRow = rPageRowEntry.GetStartRow();
//STRIP001  USHORT nEndRow   = rPageRowEntry.GetEndRow();
//STRIP001
//STRIP001  BOOL bLeftIsEmpty = FALSE;
//STRIP001  ScRange aTempRange;
//STRIP001  Rectangle aTempRect = pDoc->GetMMRect( 0,0, 0,0, 0 );
//STRIP001
//STRIP001  for (USHORT i=0; i<nPagesX; i++)
//STRIP001  {
//STRIP001      USHORT nEndCol = pPageEndX[i];
//STRIP001      if ( pDoc->IsPrintEmpty( nPrintTab, nStartCol, nStartRow, nEndCol, nEndRow,
//STRIP001                                  bLeftIsEmpty, &aTempRange, &aTempRect ) )
//STRIP001      {
//STRIP001          rPageRowEntry.SetHidden(i);
//STRIP001          bLeftIsEmpty = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          bLeftIsEmpty = FALSE;
//STRIP001
//STRIP001      nStartCol = nEndCol+1;
//STRIP001  }
//STRIP001 }

/*N*/ void ScPrintFunc::CalcPages()             // berechnet aPageRect und Seiten aus nZoom
/*N*/ {
/*N*/   if (!pPageEndX) pPageEndX = new USHORT[MAXCOL+1];
/*N*/   if (!pPageEndY) pPageEndY = new USHORT[MAXROW+1];
/*N*/   if (!pPageRows) pPageRows = new ScPageRowEntry[MAXROW+1];   //! vorher zaehlen !!!!
/*N*/
/*N*/   pDoc->SetPageSize( nPrintTab, GetDocPageSize() );
/*N*/   if (aAreaParam.bPrintArea)
/*N*/   {
/*N*/       ScRange aRange( nStartCol, nStartRow, nPrintTab, nEndCol, nEndRow, nPrintTab );
/*N*/       pDoc->UpdatePageBreaks( nPrintTab, &aRange );
/*N*/   }
/*N*/   else
/*N*/       pDoc->UpdatePageBreaks( nPrintTab, NULL );      // sonst wird das Ende markiert
/*N*/
/*N*/   //
/*N*/   //  Seiteneinteilung nach Umbruechen in Col/RowFlags
/*N*/   //  Von mehreren Umbruechen in einem ausgeblendeten Bereich zaehlt nur einer.
/*N*/   //
/*N*/
/*N*/   USHORT i;
/*N*/   nPagesX = 0;
/*N*/   nPagesY = 0;
/*N*/   nTotalY = 0;
/*N*/
/*N*/   BOOL bVisCol = FALSE;
/*N*/   for (i=nStartCol; i<=nEndCol; i++)
/*N*/   {
/*N*/       BYTE nFlags = pDoc->GetColFlags(i,nPrintTab);
/*N*/       if ( i>nStartCol && bVisCol && (nFlags & CR_PAGEBREAK) )
/*N*/       {
/*N*/           pPageEndX[nPagesX] = i-1;
/*N*/           ++nPagesX;
/*N*/           bVisCol = FALSE;
/*N*/       }
/*N*/       if (!(nFlags & CR_HIDDEN))
/*N*/           bVisCol = TRUE;
/*N*/   }
/*N*/   if (bVisCol)    // auch am Ende keine leeren Seiten
/*N*/   {
/*N*/       pPageEndX[nPagesX] = nEndCol;
/*N*/       ++nPagesX;
/*N*/   }
/*N*/
/*N*/   BOOL bVisRow = FALSE;
/*N*/   USHORT nPageStartRow = nStartRow;
/*N*/   for (i=nStartRow; i<=nEndRow; i++)
/*N*/   {
/*N*/       BYTE nFlags = pDoc->GetRowFlags(i,nPrintTab);
/*N*/       if ( i>nStartRow && bVisRow && (nFlags & CR_PAGEBREAK) )
/*N*/       {
/*N*/           pPageEndY[nTotalY] = i-1;
/*N*/           ++nTotalY;
/*N*/
/*N*/           if ( !aTableParam.bSkipEmpty ||
/*N*/                   !pDoc->IsPrintEmpty( nPrintTab, nStartCol, nPageStartRow, nEndCol, i-1 ) )
/*N*/           {
/*N*/               pPageRows[nPagesY].SetStartRow( nPageStartRow );
/*N*/               pPageRows[nPagesY].SetEndRow( i-1 );
/*N*/               pPageRows[nPagesY].SetPagesX( nPagesX );
/*N*/               if (aTableParam.bSkipEmpty)
                        {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/                   lcl_SetHidden( pDoc, nPrintTab, pPageRows[nPagesY], nStartCol, pPageEndX );
/*N*/               ++nPagesY;
/*N*/           }
/*N*/
/*N*/           nPageStartRow = i;
/*N*/           bVisRow = FALSE;
/*N*/       }
/*N*/       if (!(nFlags & CR_HIDDEN))
/*N*/           bVisRow = TRUE;
/*N*/   }
/*N*/   if (bVisRow)
/*N*/   {
/*N*/       pPageEndY[nTotalY] = nEndRow;
/*N*/       ++nTotalY;
/*N*/
/*N*/       if ( !aTableParam.bSkipEmpty ||
/*N*/               !pDoc->IsPrintEmpty( nPrintTab, nStartCol, nPageStartRow, nEndCol, nEndRow ) )
/*N*/       {
/*N*/           pPageRows[nPagesY].SetStartRow( nPageStartRow );
/*N*/           pPageRows[nPagesY].SetEndRow( nEndRow );
/*N*/           pPageRows[nPagesY].SetPagesX( nPagesX );
/*N*/           if (aTableParam.bSkipEmpty)
                    {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/               lcl_SetHidden( pDoc, nPrintTab, pPageRows[nPagesY], nStartCol, pPageEndX );
/*N*/           ++nPagesY;
/*N*/       }
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------
//  class ScJobSetup
//------------------------------------------------------------------------

/*N*/ ScJobSetup::ScJobSetup( SfxPrinter* pPrinter )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 eOrientation = pPrinter->GetOrientation();
//STRIP001 /*?*/    nPaperBin    = pPrinter->GetPaperBin();
//STRIP001 /*?*/    ePaper       = pPrinter->GetPaper();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( PAPER_USER == ePaper )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aUserSize = pPrinter->GetPaperSize();
//STRIP001 /*?*/        aUserMapMode = pPrinter->GetMapMode();
//STRIP001 /*?*/    }
/*N*/ };





}
