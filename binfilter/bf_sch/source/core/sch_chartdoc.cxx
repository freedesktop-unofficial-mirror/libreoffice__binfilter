/*************************************************************************
 *
 *  $RCSfile: sch_chartdoc.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:55:37 $
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

#pragma hdrstop

#include <bf_svx/eeitem.hxx>

#ifndef _CTRLTOOL_HXX //autogen
#include <svtools/ctrltool.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SV_MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif
#ifndef _CTRLTOOL_HXX //autogen
#include <svtools/ctrltool.hxx>
#endif

#ifndef _ZFORLIST_HXX
#ifndef _ZFORLIST_DECLARE_TABLE
#define _ZFORLIST_DECLARE_TABLE
#endif
#include <svtools/zforlist.hxx>
#endif


#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif

#ifndef _SCHATTR_HXX
#include "schattr.hxx"
#endif
#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTDATADESCR   SCHATTR_DATADESCR_DESCR
#include <bf_svx/chrtitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _CHTMODEL_HXX
#include "chtmodel.hxx"
#endif
#ifndef _SCH_STLPOOL_HXX
#include "stlpool.hxx"
#endif
#ifndef _SCH_SCHIOCMP_HXX
#include "schiocmp.hxx"
#endif
#ifndef _SCH_SCHRESID_HXX
#include "schresid.hxx"
#endif
#ifndef _SCH_DOCSHELL_HXX
#include "docshell.hxx"
#endif
#define ITEMID_FONT        EE_CHAR_FONTINFO
#define ITEMID_COLOR       EE_CHAR_COLOR
#define ITEMID_FONTHEIGHT  EE_CHAR_FONTHEIGHT

#include "glob.hrc"
#include "chtmodel.hxx"
#include "globfunc.hxx"

#include <bf_svx/fontitem.hxx>
#include <bf_svx/fhgtitem.hxx>

#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVDLAYER_HXX //autogen
#include <bf_svx/svdlayer.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif

#include "pairs.hxx"
#include "chaxis.hxx"

#include "memchrt.hxx"

/*************************************************************************
|*
|* Diese Methode erzeugt ein neues Dokument (ChartModel) und gibt einen
|* Zeiger darauf zurueck. Die Drawing Engine benutzt diese Methode um das
|* Dokument oder Teile davon ins Clipboard/DragServer stellen zu koennen.
|*
|* this method works like a copy constructor. So make sure to copy all
|* members inside this method !!!
|*
\************************************************************************/
/*N*/ SdrModel* ChartModel::AllocModel() const
/*N*/ {DBG_ASSERT(0, "STRIP"); return NULL; //STRIP001
//STRIP001 #ifdef DBG_UTIL
//STRIP001  ByteString aBStr( aMainTitle, RTL_TEXTENCODING_ASCII_US );
//STRIP001  CHART_TRACE1( "ChartModel::AllocModel (%s)", aBStr.GetBuffer() );
//STRIP001 #endif
//STRIP001
//STRIP001  ChartModel *pNewModel = new ChartModel( SvtPathOptions().GetPalettePath(), NULL );
//STRIP001  pNewModel->SetChartData (*pChartData, TRUE);
//STRIP001
//STRIP001  pNewModel->TextScalability ()      = bTextScalable;
//STRIP001  pNewModel->IsCopied ()             = bIsCopied;
//STRIP001  pNewModel->ShowAverage ()          = bShowAverage;
//STRIP001  pNewModel->ChartKindError ()       = eErrorKind;
//STRIP001  pNewModel->ChartIndicate ()        = eIndicate;
//STRIP001  pNewModel->ChartRegress ()         = eRegression;
//STRIP001
//STRIP001  pNewModel->IndicatePercent ()      = fIndicatePercent;
//STRIP001  pNewModel->IndicateBigError ()     = fIndicateBigError;
//STRIP001  pNewModel->IndicatePlus ()         = fIndicatePlus;
//STRIP001  pNewModel->IndicateMinus ()        = fIndicateMinus;
//STRIP001  pNewModel->nSplineDepth             = nSplineDepth;
//STRIP001  pNewModel->Granularity ()          = nGranularity;
//STRIP001
//STRIP001  pNewModel->InitialSize ()          = aInitialSize;
//STRIP001  pNewModel->LightVec ()             = *aLightVec;
//STRIP001  pNewModel->SetAmbientIntensity (fAmbientIntensity);
//STRIP001  pNewModel->SetAmbientColor(aAmbientColor);
//STRIP001  pNewModel->SpotIntensity ()        = fSpotIntensity;
//STRIP001  pNewModel->SetSpotColor(aSpotColor);
//STRIP001  pNewModel->ChartStyle ()           = eChartStyle;
//STRIP001  pNewModel->OldChartStyle ()        = eOldChartStyle;
//STRIP001  pNewModel->PieHeight ()            = nPieHeight;
//STRIP001  pNewModel->PieSegCount ()          = nPieSegCount;
//STRIP001  pNewModel->ShowMainTitle ()        = bShowMainTitle;
//STRIP001  pNewModel->ShowSubTitle ()         = bShowSubTitle;
//STRIP001  pNewModel->ShowXAxisTitle ()       = bShowXAxisTitle;
//STRIP001  pNewModel->ShowYAxisTitle ()       = bShowYAxisTitle;
//STRIP001  pNewModel->ShowZAxisTitle ()       = bShowZAxisTitle;
//STRIP001 //    pNewModel->ShowXAxis ()            = bShowXAxis;
//STRIP001 //    pNewModel->ShowYAxis ()            = bShowYAxis;
//STRIP001 //    pNewModel->ShowZAxis ()            = bShowZAxis;
//STRIP001  pNewModel->ShowXGridMain ()        = bShowXGridMain;
//STRIP001  pNewModel->ShowYGridMain ()        = bShowYGridMain;
//STRIP001  pNewModel->ShowZGridMain ()        = bShowZGridMain;
//STRIP001  pNewModel->ShowXGridHelp ()        = bShowXGridHelp;
//STRIP001  pNewModel->ShowYGridHelp ()        = bShowYGridHelp;
//STRIP001  pNewModel->ShowZGridHelp()         = bShowZGridHelp;
//STRIP001 //    pNewModel->ShowXDescr ()           = bShowXDescr;
//STRIP001 //    pNewModel->ShowYDescr ()           = bShowYDescr;
//STRIP001 //    pNewModel->ShowZDescr ()           = bShowZDescr;
//STRIP001  pNewModel->MainTitle ()            = aMainTitle;
//STRIP001  pNewModel->SubTitle ()             = aSubTitle;
//STRIP001  pNewModel->XAxisTitle ()           = aXAxisTitle;
//STRIP001  pNewModel->YAxisTitle ()           = aYAxisTitle;
//STRIP001  pNewModel->ZAxisTitle ()           = aZAxisTitle;
//STRIP001
//STRIP001  pNewModel->ShowSym ()              = bShowSym;
//STRIP001  pNewModel->SetSwitchData(bSwitchData);
//STRIP001
//STRIP001  pNewModel->aBarY1 = aBarY1;
//STRIP001     pNewModel->aBarY1.ChangeModel( pNewModel );
//STRIP001  pNewModel->aBarY2 = aBarY2;
//STRIP001     pNewModel->aBarY2.ChangeModel( pNewModel );
//STRIP001
//STRIP001  pNewModel->ReadError ()            = bReadError;
//STRIP001  pNewModel->DataDescr  ()           = eDataDescr;
//STRIP001
//STRIP001  pNewModel->CopyDefaultColors (pDefaultColors);
//STRIP001  pNewModel->SetShowLegend (bLegendVisible);
//STRIP001 //    pNewModel->SetChartData (*pChartData, TRUE); #64058#
//STRIP001  pNewModel->SetAngles (nXAngle, nYAngle, nZAngle);
//STRIP001
//STRIP001  pNewModel->AllocPieSegOfs (nPieSegCount);
//STRIP001
//STRIP001  // #68527# BM: some attributes have been missing
//STRIP001
//STRIP001  pNewModel->SetUseRelativePositions( bUseRelativePositionsForChartGroups );
//STRIP001  pNewModel->aDiagramRectangle                = aDiagramRectangle;
//STRIP001  pNewModel->aLastDiagramRectangle            = aDiagramRectangle;
//STRIP001  pNewModel->bDiagramHasBeenMovedOrResized    = bDiagramHasBeenMovedOrResized;
//STRIP001  pNewModel->aLegendTopLeft                   = aLegendTopLeft;
//STRIP001  pNewModel->aTitleTopCenter                  = aTitleTopCenter;
//STRIP001  pNewModel->aSubTitleTopCenter               = aSubTitleTopCenter;
//STRIP001  pNewModel->aTitleXAxisPosition              = aTitleXAxisPosition;
//STRIP001  pNewModel->aTitleYAxisPosition              = aTitleYAxisPosition;
//STRIP001  pNewModel->aTitleZAxisPosition              = aTitleZAxisPosition;
//STRIP001  pNewModel->bAdjustMarginsForLegend          = bAdjustMarginsForLegend;
//STRIP001  pNewModel->bAdjustMarginsForMainTitle       = bAdjustMarginsForMainTitle;
//STRIP001  pNewModel->bAdjustMarginsForSubTitle        = bAdjustMarginsForSubTitle;
//STRIP001  pNewModel->bAdjustMarginsForXAxisTitle      = bAdjustMarginsForXAxisTitle;
//STRIP001  pNewModel->bAdjustMarginsForYAxisTitle      = bAdjustMarginsForYAxisTitle;
//STRIP001  pNewModel->bAdjustMarginsForZAxisTitle      = bAdjustMarginsForZAxisTitle;
//STRIP001  pNewModel->bDiagramHasBeenMovedOrResized    = bDiagramHasBeenMovedOrResized;
//STRIP001  pNewModel->bMainTitleHasBeenMoved           = bMainTitleHasBeenMoved;
//STRIP001  pNewModel->bSubTitleHasBeenMoved            = bSubTitleHasBeenMoved;
//STRIP001  pNewModel->bLegendHasBeenMoved              = bLegendHasBeenMoved;
//STRIP001  pNewModel->bXAxisTitleHasBeenMoved          = bXAxisTitleHasBeenMoved;
//STRIP001  pNewModel->bYAxisTitleHasBeenMoved          = bYAxisTitleHasBeenMoved;
//STRIP001  pNewModel->bZAxisTitleHasBeenMoved          = bZAxisTitleHasBeenMoved;
//STRIP001  pNewModel->bSwitch3DColRow                  = bSwitch3DColRow;
//STRIP001  pNewModel->nMarkLen                         = nMarkLen;
//STRIP001  pNewModel->bCanRebuild                      = bCanRebuild;
//STRIP001  pNewModel->bShowDataDescr                   = bShowDataDescr;
//STRIP001  pNewModel->eAdjustXAxesTitle                = eAdjustXAxesTitle;
//STRIP001  pNewModel->eAdjustYAxesTitle                = eAdjustYAxesTitle;
//STRIP001  pNewModel->eAdjustZAxesTitle                = eAdjustZAxesTitle;
//STRIP001  pNewModel->nBarPercentWidth                 = nBarPercentWidth;
//STRIP001  pNewModel->nNumLinesInColChart              = nNumLinesInColChart;
//STRIP001  pNewModel->aChartRect                       = aChartRect;
//STRIP001  pNewModel->aInitialSize                     = aInitialSize;
//STRIP001  pNewModel->nChartStatus                     = nChartStatus;
//STRIP001  pNewModel->bAttrAutoStorage                 = bAttrAutoStorage;
//STRIP001
//STRIP001  // #68527# BM: End
//STRIP001
//STRIP001  pNewModel->PutTitleAttr(     *pTitleAttr     ,FALSE);
//STRIP001  pNewModel->PutMainTitleAttr( *pMainTitleAttr ,FALSE);
//STRIP001  pNewModel->PutSubTitleAttr(  *pSubTitleAttr  ,FALSE);
//STRIP001  pNewModel->PutXAxisTitleAttr(*pXAxisTitleAttr,FALSE);
//STRIP001  pNewModel->PutYAxisTitleAttr(*pYAxisTitleAttr,FALSE);
//STRIP001  pNewModel->PutZAxisTitleAttr(*pZAxisTitleAttr,FALSE);
//STRIP001
//STRIP001  // merge numberformatters
//STRIP001  if( pNewModel->pOwnNumFormatter && pNumFormatter )
//STRIP001  {
//STRIP001      SvULONGTable* pTransTable =
//STRIP001          pNewModel->pOwnNumFormatter->MergeFormatter( *pNumFormatter );
//STRIP001
//STRIP001      if( pTransTable && pTransTable->Count() )
//STRIP001      {
//STRIP001          // we have to merge some formats
//STRIP001          DBG_ERROR1( "Unexpected situation: %d number format(s) have to be merged.", pTransTable->Count() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pNewModel->PutAxisAttr (*pAxisAttr,FALSE);
//STRIP001
//STRIP001  pNewModel->CopyAxisMembers(this);
//STRIP001  pNewModel->CopyAxisAttributes(this,FALSE);
//STRIP001
//STRIP001  pNewModel->PutGridAttr (*pGridAttr,FALSE);
//STRIP001  pNewModel->PutXGridMainAttr(*pXGridMainAttr,FALSE);
//STRIP001  pNewModel->PutYGridMainAttr(*pYGridMainAttr,FALSE);
//STRIP001  pNewModel->PutZGridMainAttr(*pZGridMainAttr,FALSE);
//STRIP001  pNewModel->PutXGridHelpAttr(*pXGridHelpAttr,FALSE);
//STRIP001  pNewModel->PutYGridHelpAttr(*pYGridHelpAttr,FALSE);
//STRIP001  pNewModel->PutZGridHelpAttr(*pZGridHelpAttr,FALSE);
//STRIP001
//STRIP001  pNewModel->PutDiagramAreaAttr(*pDiagramAreaAttr,FALSE);
//STRIP001  pNewModel->PutDiagramWallAttr(*pDiagramWallAttr,FALSE);
//STRIP001  pNewModel->PutDiagramFloorAttr(*pDiagramFloorAttr,FALSE);
//STRIP001
//STRIP001  pNewModel->PutLegendAttr (*pLegendAttr,FALSE);
//STRIP001  pNewModel->SetItemSetLists(*this);
//STRIP001  pNewModel->PutChartAttr(*pChartAttr,FALSE);
//STRIP001
//STRIP001  pNewModel->SetAttributes(CHOBJID_DIAGRAM_STOCKLINE_GROUP,*pStockLineAttr,FALSE);
//STRIP001  pNewModel->SetAttributes(CHOBJID_DIAGRAM_STOCKLOSS_GROUP,*pStockLossAttr,FALSE);
//STRIP001  pNewModel->SetAttributes(CHOBJID_DIAGRAM_STOCKPLUS_GROUP,*pStockPlusAttr,FALSE);
//STRIP001
//STRIP001  DBG_ITEMS((SfxItemSet&)pNewModel->GetDataRowAttr(0),pNewModel);
//STRIP001  DBG_ITEMS((SfxItemSet&)GetDataRowAttr(0),(ChartModel*)this);
//STRIP001
//STRIP001  return pNewModel;
/*N*/ }

/*************************************************************************
|*
|* Diese Methode erzeugt eine neue Seite (SchPage) und gibt einen Zeiger
|* darauf zurueck. Die Drawing Engine benutzt diese Methode beim Laden
|* zur Erzeugung von Seiten (deren Typ sie ja nicht kennt, da es ABLEITUNGEN
|* der SdrPage sind).
|*
\************************************************************************/

/*N*/ SdrPage* ChartModel::AllocPage(FASTBOOL bMasterPage)
/*N*/ {
/*N*/   return new SdrPage(*this, bMasterPage);
/*N*/ }
/*************************************************************************
|*
|* Inserter fuer SvStream zum Speichern
|*
\************************************************************************/
/*N*/ SvStream& operator << (SvStream& rOut, const ChartModel& rDoc)
/*N*/ {
/*N*/   // die daemlichen blockklammern muessen erhalten bleiben, damit
/*N*/   // im destruktor ~SchIOCompat dei korrekte blockgröße geschrieben
/*N*/   // wird. ansonsten gibt es beim einlesen mit der 304 jede menge
/*N*/   // aerger
/*N*/   {
/*N*/       SchIOCompat aIO(rOut, STREAM_WRITE, 1);
/*N*/
/*N*/       // AF: Don't write VCItemPool any longer (01/2001)
/*N*/       rOut << (ULONG)0L;
/*N*/
        /**************************************************************************
        * Frueher (StarChart Version 3.0, File-Format Version 1) wurde hier das
        * JobSetup geschrieben, nun der Printer (binaer-kompatibel, daher wurde
        * die Version des File-Formats nicht geaendert)
        **************************************************************************/
/*N*/       if (rDoc.pDocShell)
/*N*/       {
/*N*/           SfxPrinter* pPrinter =
/*N*/                ((SchChartDocShell*)rDoc.pDocShell)->GetPrinter();
/*N*/
/*N*/
/*N*/           if (pPrinter)
/*N*/           {
/*N*/               pPrinter->Store(rOut);
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               // Es ist kein Printer vorhanden -> muss erzeugt werden
/*?*/               SfxBoolItem aItem(SID_PRINTER_NOTFOUND_WARN, TRUE);
/*?*/               SfxItemSet* pSet = new SfxItemSet(((ChartModel&) rDoc).GetPool(),
/*?*/                               SID_PRINTER_NOTFOUND_WARN,
/*?*/                               SID_PRINTER_NOTFOUND_WARN, 0);
/*?*/               pSet->Put(aItem);
/*?*/               SfxPrinter* pPrinter = new SfxPrinter(pSet);
/*?*/
/*?*/               MapMode aMapMode = pPrinter->GetMapMode();
/*?*/               aMapMode.SetMapUnit(MAP_100TH_MM);
/*?*/               pPrinter->SetMapMode(aMapMode);
/*?*/
/*?*/               pPrinter->Store(rOut);
/*?*/               delete pPrinter;
/*?*/               //delete pSet; bloss nicht! Killt der Printer gleich mit!
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           // Keine DocShell, daher wird ein JobSetup geschrieben
/*?*/           JobSetup aJobSetup;
/*?*/           rOut << aJobSetup;
/*N*/       }
/*N*/   }
/*N*/
/*N*/
/*N*/   rOut << (SdrModel&) rDoc;
/*N*/
/*N*/   SchIOCompat aIO(rOut, STREAM_WRITE, 0);
/*N*/
/*N*/   rDoc.StoreAttributes(rOut);
/*N*/   //<- ehemals Basisklasse
/*N*/
/*N*/
/*N*/
/*N*/   return rOut;
/*N*/ }

/*************************************************************************
|*
|* Extractor fuer SvStream zum Laden
|*
\************************************************************************/

/*N*/ SvStream& operator >> (SvStream& rIn, ChartModel& rDoc)
/*N*/ {
/*N*/   // auch hier muessen die blockklammern erhalten bleiben,
/*N*/   // um 304-er dokumente sauber lesen zu koennen.
/*N*/   {
/*N*/       SchIOCompat aIO(rIn, STREAM_READ);
/*N*/
/*N*/       ULONG n;
/*N*/       rIn >> n;
/*N*/       // must be 0 or 1. Otherwise we have an error
/*N*/       // most probably a wrong password
/*N*/       if( n == 1L )
/*N*/       {
/*N*/           // AF: Skip VCItemPool.
/*N*/           rIn.SeekRel (74);
/*N*/       }
/*N*/       else if( n != 0L )
/*N*/       {
/*?*/           rIn.SetError( ERRCODE_IO_GENERAL );
/*?*/           return rIn;
/*N*/       }
/*N*/
/*N*/       if (aIO.GetVersion() >= 1)
/*N*/       {

            /******************************************************************
            * Frueher (StarChart Version 3.0, File-Format Version 1) wurde hier
            * das JobSetup eingelesen, nun wird der Printer erzeugt
            * (binaer-kompatibel)
            *******************************************************************/
            // ItemSet mit speziellem Poolbereich anlegen
/*N*/           SfxItemSet* pSet =
/*N*/               new SfxItemSet(rDoc.GetPool(),
/*N*/                              SID_PRINTER_NOTFOUND_WARN,
/*N*/                              SID_PRINTER_NOTFOUND_WARN, 0);
/*N*/           pSet->Put(SfxBoolItem(SID_PRINTER_NOTFOUND_WARN, TRUE));
/*N*/
/*N*/           SfxPrinter* pPrinter = SfxPrinter::Create(rIn, pSet);
/*N*/
/*N*/           MapMode aMM(pPrinter->GetMapMode());
/*N*/           aMM.SetMapUnit(MAP_100TH_MM);
/*N*/           pPrinter->SetMapMode(aMM);
/*N*/
/*N*/           if (rDoc.pDocShell->GetCreateMode() != SFX_CREATE_MODE_EMBEDDED)
/*N*/           {
/*N*/               ((SchChartDocShell*)rDoc.pDocShell)->SetPrinter( pPrinter, TRUE );  // will be deleted by DocShell
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               delete pPrinter;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // statt Basisklassenaufruf [    rIn >> (ChartModel&)rDoc;] direkt:
/*N*/   rIn >> (SdrModel&)rDoc;
/*N*/
/*N*/   if (rIn.GetError() != SVSTREAM_FILEFORMAT_ERROR)
/*N*/   {
/*N*/       SchIOCompat aIO(rIn, STREAM_READ);
/*N*/
/*N*/       rDoc.LoadAttributes(rIn);
/*N*/   }
/*N*/   // <- Basisaufruf
/*N*/
/*N*/   rDoc.GetItemPool().LoadCompleted();
/*N*/
/*N*/   rDoc.ReadError () = FALSE;
/*N*/
/*N*/   // alle 3D-Objekte werden bei einem Paint erstmailg sortiert, damit wird auch
/*N*/   // das Dokument als geaendert gekennzeichnet. Diese Variable wird in der
/*N*/   // CHVIEWSH-Paint-Methode abgefragt und bei Bedarf wird der Modified-Status
/*N*/   // des Dokuments zurueckgesetzt.
/*N*/
/*N*/   // no longer needed
/*N*/ //-   rDoc.FreshLoaded () = TRUE;
/*N*/
/*N*/   return rIn;
/*N*/ }

/*************************************************************************
|*
|* SetChanged(), das Model wurde geaendert
|*
\************************************************************************/

/*N*/ void ChartModel::SetChanged(FASTBOOL bFlag)
/*N*/ {
/*N*/   if (pDocShell)
/*N*/   {
/*N*/       if (bNewOrLoadCompleted && pDocShell->IsEnableSetModified())
/*N*/       {
/*N*/           // weitergeben an Basisklasse
/*N*/           //ChartModel
/*N*/           SdrModel::SetChanged(bFlag);
/*N*/
/*N*/           // an ObjectShell weiterleiten
/*N*/           pDocShell->SetModified(bFlag);
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       // weitergeben an Basisklasse
/*?*/       //ChartModel
/*?*/       SdrModel::SetChanged(bFlag);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* NewOrLoadCompleted
|*
|* Wird gerufen, wenn das Dokument geladen wurde bzw. feststeht, dass es
|* nicht mehr geladen wird.
|*
\************************************************************************/

/*N*/ void ChartModel::NewOrLoadCompleted(USHORT eMode)
/*N*/ {
/*N*/   if (eMode == NEW_DOC)
/*N*/   {
/*N*/       // StyleSheets generieren
/*N*/       Font aFont( OutputDevice::GetDefaultFont( DEFAULTFONT_SANS, GetLanguage( EE_CHAR_LANGUAGE ), DEFAULTFONT_FLAGS_ONLYONE ) );
/*N*/       SvxFontItem aFontItem( aFont.GetFamily(), aFont.GetName(), aFont.GetStyleName(), aFont.GetPitch(),
/*N*/                              aFont.GetCharSet(), EE_CHAR_FONTINFO );
/*N*/
/*N*/       SfxStyleSheetBase* pSheet =
/*N*/           &pStyleSheetPool->Make(String(SchResId(STR_STLSHEET_TITLE_MAIN)),
/*N*/                                         SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(493));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_TITLE_SUB)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(423));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_TITLE_X_AXIS)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(352));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_TITLE_Y_AXIS)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(352));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_TITLE_Z_AXIS)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(352));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_DATAROWS)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(282));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_DATACOLS)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(282));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_DATAVALUES)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(282));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_DATADESCR)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO ) ));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(282));
/*N*/
/*N*/       pSheet = &pStyleSheetPool->
/*N*/                   Make(String(SchResId(STR_STLSHEET_LEGEND)),
/*N*/                        SFX_STYLE_FAMILY_PARA);
/*N*/       pSheet->GetItemSet().Put(aFontItem);
/*N*/       pSheet->GetItemSet().Put(SvxColorItem( Color( COL_AUTO )));
/*N*/       pSheet->GetItemSet().Put(SvxFontHeightItem(282));
/*N*/
/*N*/         pAxisAttr->ClearItem( SCHATTR_AXIS_SHOWDESCR );
/*N*/   }
/*N*/   else if (eMode == DOC_LOADED)
/*N*/   {
/*N*/         // set intersection of all axis attributes used as axis
/*N*/         // 'style' (that is an itemset for the 'all axes' dialog)
/*N*/         GetFullAxisAttr( NULL, true ).ClearInvalidItems();
/*N*/         pAxisAttr->ClearItem( SCHATTR_AXIS_SHOWDESCR );
/*N*/
/*N*/         // set 'all axis' attributes on all axes that are currently
/*N*/         // disabled
/*N*/         if( ! HasAxis( CHOBJID_DIAGRAM_X_AXIS ))
/*?*/             pChartXAxis->SetAttributes( pAxisAttr );
/*N*/         if( ! HasAxis( CHOBJID_DIAGRAM_Y_AXIS ))
/*?*/             pChartYAxis->SetAttributes( pAxisAttr );
/*N*/         if( ! HasAxis( CHOBJID_DIAGRAM_Z_AXIS ))
/*N*/             pChartZAxis->SetAttributes( pAxisAttr );
/*N*/         if( ! HasAxis( CHOBJID_DIAGRAM_A_AXIS ))
/*N*/             pChartAAxis->SetAttributes( pAxisAttr );
/*N*/         if( ! HasAxis( CHOBJID_DIAGRAM_B_AXIS ))
/*N*/             pChartBAxis->SetAttributes( pAxisAttr );
/*N*/         // #99528# change auto-font color according to diagram area
/*N*/         PageColorChanged( *pDiagramAreaAttr );
/*N*/
/*N*/         // #101591# set precision of own number-formatter to 2 if we reside in a
/*N*/         // calc or writer, which is assumed by checking the cell-range in the
/*N*/         // MemChart.
/*N*/         OSL_ASSERT( pChartData );
/*N*/         const SchChartRange & rRange = pChartData->GetChartRange();
/*N*/         if( rRange.maRanges.size() > 0 )
/*N*/         {
/*?*/             pOwnNumFormatter->ChangeStandardPrec( 2 );
/*N*/         }
/*N*/   }
/*N*/
/*N*/   bNewOrLoadCompleted = TRUE;
/*N*/ #ifdef DBG_UTIL
/*N*/   if(pChartData && GetRowCount() && GetColCount())
/*N*/   {
/*N*/       CHART_TRACE1( "ChartModel::NewOrLoadCompleted debugging ChartItems Model %s ",
/*N*/                     (eMode==DOC_LOADED)? "was loaded": ((eMode==NEW_DOC)? "is new" : "don't know") );
/*N*/       DBG_ITEMS((SfxItemSet&)GetDataRowAttr(0),this);
/*N*/       DBG_ITEMS((SfxItemSet&)GetDataPointAttr(0,0),this);
/*N*/   }
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Setze den Modified-Status zurueck, wenn ein Dokument mit
|* 3D-Objekten geladen und ausgegeben wurde
|*
\************************************************************************/

//  void ChartModel::ResetFreshLoaded ()
//  {
//      bFreshLoaded = FALSE;
//      SetChanged (FALSE);
//  }


