/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_frmview.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:22:35 $
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

#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif


#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _SD_UNOKYWDS_HXX_
#include "unokywds.hxx"
#endif

#include <vector>

#include "frmview.hxx"
#include "drawdoc.hxx"
#include "optsitem.hxx"
#include "sdresid.hxx"
#include "glob.hrc"
#include "sdiocmpt.hxx"
#include "docshell.hxx"

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::rtl;
using namespace ::std;

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ FrameView::FrameView(SdDrawDocument* pDrawDoc, FrameView* pFrameView /* = NULK */)
/*N*/   : SdrView(pDrawDoc, (OutputDevice*) NULL),
/*N*/   nRefCount(0),
/*N*/   nPresViewShellId(SID_VIEWSHELL0),
/*N*/   nSlotId(SID_OBJECT_SELECT)
/*N*/ {
/*N*/   EndListening(*pDrawDoc);
/*N*/
/*N*/   EnableExtendedKeyInputDispatcher(FALSE);
/*N*/   EnableExtendedMouseEventDispatcher(FALSE);
/*N*/   EnableExtendedCommandEventDispatcher(FALSE);
/*N*/
/*N*/   SetGridFront( TRUE );
/*N*/   SetOConSnap( FALSE );
/*N*/   SetFrameDragSingles( TRUE );
/*N*/   SetSlidesPerRow(4);
/*N*/
/*N*/   if( NULL == pFrameView )
/*N*/   {
/*N*/       SdDrawDocShell* pDocShell = pDrawDoc->GetDocSh();
/*N*/
/*N*/       if ( pDocShell )
/*N*/       {
            /**********************************************************************
            * Das Dokument wurde geladen, ist eine FrameView vorhanden?
            **********************************************************************/
/*N*/           ULONG nSdViewShellCount = 0;
/*N*/           SdDrawDocument* pDoc = pDocShell->GetDoc();
/*N*/           pFrameView = pDoc->GetFrameView(nSdViewShellCount);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (pFrameView)
/*N*/   {
        /**********************************************************************
        * FrameView mit der FrameView der DocShell initialisieren
        **********************************************************************/
/*N*/       SetRuler( pFrameView->HasRuler() );
/*N*/       SetGridCoarse( pFrameView->GetGridCoarse() );
/*N*/       SetGridFine( pFrameView->GetGridFine() );
/*N*/       SetSnapGrid( pFrameView->GetSnapGrid() );
/*N*/       SetSnapGridWidth(pFrameView->GetSnapGridWidthX(), pFrameView->GetSnapGridWidthY());
/*N*/       SetGridVisible( pFrameView->IsGridVisible() );
/*N*/       SetGridFront( pFrameView->IsGridFront() );
/*N*/       SetSnapAngle( pFrameView->GetSnapAngle() );
/*N*/       SetGridSnap( pFrameView->IsGridSnap() );
/*N*/       SetBordSnap( pFrameView->IsBordSnap() );
/*N*/       SetHlplSnap( pFrameView->IsHlplSnap() );
/*N*/       SetOFrmSnap( pFrameView->IsOFrmSnap() );
/*N*/       SetOPntSnap( pFrameView->IsOPntSnap() );
/*N*/       SetOConSnap( pFrameView->IsOConSnap() );
/*N*/       SetHlplVisible( pFrameView->IsHlplVisible() );
/*N*/       SetDragStripes( pFrameView->IsDragStripes() );
/*N*/       SetPlusHandlesAlwaysVisible( pFrameView->IsPlusHandlesAlwaysVisible() );
/*N*/       SetFrameDragSingles( pFrameView->IsFrameDragSingles() );
/*N*/       SetSnapMagneticPixel( pFrameView->GetSnapMagneticPixel() );
/*N*/       SetMarkedHitMovesAlways( pFrameView->IsMarkedHitMovesAlways() );
/*N*/       SetMoveOnlyDragging( pFrameView->IsMoveOnlyDragging() );
/*N*/       SetCrookNoContortion( pFrameView->IsCrookNoContortion() );
/*N*/       SetSlantButShear( pFrameView->IsSlantButShear() );
/*N*/       SetNoDragXorPolys( pFrameView->IsNoDragXorPolys() );
/*N*/       SetAngleSnapEnabled( pFrameView->IsAngleSnapEnabled() );
/*N*/       SetBigOrtho( pFrameView->IsBigOrtho() );
/*N*/       SetOrtho( pFrameView->IsOrtho() );
/*N*/       SetEliminatePolyPointLimitAngle( pFrameView->GetEliminatePolyPointLimitAngle() );
/*N*/       SetEliminatePolyPoints( pFrameView->IsEliminatePolyPoints() );
/*N*/       SetMasterPagePaintCaching( pFrameView->IsMasterPagePaintCaching() );
/*N*/       SetDesignMode( pFrameView->IsDesignMode() );
/*N*/
/*N*/       SetLineDraft( pFrameView->IsLineDraft() );
/*N*/       SetFillDraft( pFrameView->IsFillDraft() );
/*N*/       SetTextDraft( pFrameView->IsTextDraft() );
/*N*/       SetGrafDraft( pFrameView->IsGrafDraft() );
/*N*/       SetSolidMarkHdl( pFrameView->IsSolidMarkHdl() );
/*N*/       SetSolidDragging( pFrameView->IsSolidDragging() );
/*N*/
/*N*/       aVisibleLayers = pFrameView->GetVisibleLayers();
/*N*/       aPrintableLayers = pFrameView->GetPrintableLayers();
/*N*/       aLockedLayers = pFrameView->GetLockedLayers();
/*N*/       aStandardHelpLines = pFrameView->GetStandardHelpLines();
/*N*/       aNotesHelpLines = pFrameView->GetNotesHelpLines();
/*N*/       aHandoutHelpLines = pFrameView->GetHandoutHelpLines();
/*N*/       SetActiveLayer( pFrameView->GetActiveLayer() );
/*N*/       bNoColors = pFrameView->IsNoColors();
/*N*/       bNoAttribs = pFrameView->IsNoAttribs() ;
/*N*/       aVisArea = pFrameView->GetVisArea();
/*N*/       ePageKind = pFrameView->GetPageKind();
/*N*/       nSelectedPage = pFrameView->GetSelectedPage();
/*N*/       eStandardEditMode = pFrameView->GetViewShEditMode(PK_STANDARD);
/*N*/       eNotesEditMode = pFrameView->GetViewShEditMode(PK_NOTES);
/*N*/       eHandoutEditMode = pFrameView->GetViewShEditMode(PK_HANDOUT);
/*N*/       bLayerMode = pFrameView->IsLayerMode();
/*N*/       bQuickEdit = pFrameView->IsQuickEdit();
/*N*/       bDragWithCopy = pFrameView->IsDragWithCopy();
/*N*/       bBigHandles          = pFrameView->IsBigHandles();
/*N*/       bDoubleClickTextEdit = pFrameView->IsDoubleClickTextEdit();
/*N*/       bClickChangeRotation = pFrameView->IsClickChangeRotation();
/*N*/       nSlidesPerRow = pFrameView->GetSlidesPerRow();
/*N*/       nDrawMode = pFrameView->GetDrawMode();
/*N*/       nPreviewDrawMode = pFrameView->GetPreviewDrawMode();
/*N*/       bShowPreviewInPageMode = pFrameView->IsShowPreviewInPageMode() != 0;
/*N*/       bShowPreviewInMasterPageMode = pFrameView->IsShowPreviewInMasterPageMode() != 0;
/*N*/       bShowPreviewInOutlineMode = pFrameView->IsShowPreviewInOutlineMode() != 0;
/*N*/       nTabCtrlPercent = pFrameView->GetTabCtrlPercent();
/*N*/   }
/*N*/   else
/*N*/   {
        /**********************************************************************
        * FrameView mit den Applikationsdaten initialisieren
        **********************************************************************/
/*N*/       aVisibleLayers.SetAll();
/*N*/       aPrintableLayers.SetAll();
/*N*/       SetGridCoarse( Size( 1000, 1000 ) );
/*N*/       SetSnapGrid( Size( 1000, 1000 ) );
/*N*/       SetSnapGridWidth(Fraction(1000, 1), Fraction(1000, 1));
/*N*/       SetActiveLayer( String( SdResId(STR_LAYER_LAYOUT) ) );
/*N*/       bNoColors = TRUE;
/*N*/       bNoAttribs = FALSE;
/*N*/       aVisArea = Rectangle( Point(), Size(0, 0) );
/*N*/       ePageKind = PK_STANDARD;
/*N*/       nSelectedPage = 0;
/*N*/       eStandardEditMode = EM_PAGE;
/*N*/       eNotesEditMode = EM_PAGE;
/*N*/       eHandoutEditMode = EM_MASTERPAGE;
/*N*/       bLayerMode = FALSE;
/*N*/       SetEliminatePolyPoints(FALSE);
/*N*/
/*N*/       {
/*N*/           bool bUseContrast = Application::GetSettings().GetStyleSettings().GetHighContrastMode();
/*N*/           nDrawMode = bUseContrast ? OUTPUT_DRAWMODE_CONTRAST : OUTPUT_DRAWMODE_COLOR;
/*N*/       }
/*N*/       nPreviewDrawMode = nDrawMode;
/*N*/       bShowPreviewInPageMode = FALSE;
/*N*/       bShowPreviewInMasterPageMode = TRUE;
/*N*/       bShowPreviewInOutlineMode = TRUE;
/*N*/       nTabCtrlPercent = 0.0;
/*N*/
/*N*/       // get default for design mode
/*N*/       sal_Bool bInitDesignMode = pDrawDoc->GetOpenInDesignMode();
/*N*/       if( pDrawDoc->OpenInDesignModeIsDefaulted() )
/*N*/       {
/*N*/           bInitDesignMode = sal_True;
/*N*/       }
/*N*/
/*N*/       SfxObjectShell* pObjShell = pDrawDoc->GetObjectShell();
/*N*/       sal_Bool bReadOnly = sal_False;
/*N*/       if( pObjShell )
/*N*/           bReadOnly = pObjShell->IsReadOnly();
/*N*/       if( bReadOnly )
/*N*/           bInitDesignMode = sal_False;
/*N*/       SetDesignMode( bInitDesignMode );
/*N*/
/*N*/       Update( SD_MOD()->GetSdOptions(pDrawDoc->GetDocumentType()) );
/*N*/   }
/*N*/
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ FrameView::~FrameView()
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* Verbindung herstellen
|*
\************************************************************************/

/*N*/ void FrameView::Connect()
/*N*/ {
/*N*/   nRefCount++;
/*N*/ }


/*************************************************************************
|*
|* Verbindung loesen
|*
\************************************************************************/

/*N*/ void FrameView::Disconnect()
/*N*/ {
/*N*/   if (nRefCount > 0)
/*N*/   {
/*N*/       nRefCount--;
/*N*/   }
/*N*/
/*N*/   if (nRefCount == 0)
/*N*/   {
/*N*/       delete this;
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* Inserter fuer SvStream zum Speichern
|*
\************************************************************************/

/*N*/ SvStream& operator << (SvStream& rOut, const FrameView& rView)
/*N*/ {
/*N*/   sal_uInt32 nULTemp;
/*N*/
/*N*/   // #95895# translate view-layer name to standard-ASCII
/*N*/   // like in MakeUniqueLayerNames()
/*N*/   String aLayerName(rView.GetActiveLayer());
/*N*/
/*N*/   String aLayerLayout(SdResId(STR_LAYER_LAYOUT));
/*N*/   String aLayerBckgrnd(SdResId(STR_LAYER_BCKGRND));
/*N*/   String aLayerBckgrndObj(SdResId(STR_LAYER_BCKGRNDOBJ));
/*N*/   String aLayerControls(SdResId(STR_LAYER_CONTROLS));
/*N*/   String aLayerMeasurelines(SdResId(STR_LAYER_MEASURELINES));
/*N*/
/*N*/   sal_Bool bActiveLayerWasChanged(sal_False);
/*N*/   String aOldLayerName(rView.GetActiveLayer());
/*N*/
/*N*/   if (aLayerName == aLayerLayout)
/*N*/   {
/*N*/       ((FrameView&)rView).SetActiveLayer( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_LAYOUT" )));
/*N*/       bActiveLayerWasChanged = sal_True;
/*N*/   }
/*N*/   else if (aLayerName == aLayerBckgrnd)
/*N*/   {
/*N*/       ((FrameView&)rView).SetActiveLayer( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BCKGRND" )));
/*N*/       bActiveLayerWasChanged = sal_True;
/*N*/   }
/*N*/   else if (aLayerName == aLayerBckgrndObj)
/*N*/   {
/*N*/       ((FrameView&)rView).SetActiveLayer( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BACKGRNDOBJ" )));
/*N*/       bActiveLayerWasChanged = sal_True;
/*N*/   }
/*N*/   else if (aLayerName == aLayerControls)
/*N*/   {
/*N*/       ((FrameView&)rView).SetActiveLayer( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_CONTROLS" )));
/*N*/       bActiveLayerWasChanged = sal_True;
/*N*/   }
/*N*/   else if (aLayerName == aLayerMeasurelines)
/*N*/   {
/*N*/       ((FrameView&)rView).SetActiveLayer( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_MEASURELINES" )));
/*N*/       bActiveLayerWasChanged = sal_True;
/*N*/   }
/*N*/
/*N*/   // stream out the view
/*N*/   rOut << (SdrView&) rView;
/*N*/
/*N*/   // #95895# when active layer name was changed for export, change it back to original here
/*N*/   if(bActiveLayerWasChanged)
/*N*/   {
/*N*/       ((FrameView&)rView).SetActiveLayer(aOldLayerName);
/*N*/   }
/*N*/
/*N*/   // Letzter Parameter ist die aktuelle Versionsnummer des Codes
/*N*/   SdIOCompat aIO(rOut, STREAM_WRITE, 11);
/*N*/
/*N*/   rOut << rView.bRuler;
/*N*/   rOut << rView.aVisibleLayers;
/*N*/   rOut << rView.aLockedLayers;
/*N*/   rOut << rView.aPrintableLayers;
/*N*/   rOut << rView.aStandardHelpLines;
/*N*/   rOut << rView.aNotesHelpLines;
/*N*/   rOut << rView.aHandoutHelpLines;
/*N*/   rOut << rView.bNoColors;
/*N*/   rOut << rView.bNoAttribs;
/*N*/   rOut << rView.aVisArea;
/*N*/   nULTemp = (sal_uInt32) rView.ePageKind;            rOut << nULTemp;
/*N*/   rOut << rView.nSelectedPage;
/*N*/   nULTemp = (sal_uInt32) rView.eStandardEditMode;    rOut << nULTemp;
/*N*/   rOut << rView.bLayerMode;
/*N*/   rOut << rView.bQuickEdit;
/*N*/   rOut << rView.bDragWithCopy;
/*N*/   rOut << (UINT16)rView.nSlidesPerRow;
/*N*/
/*N*/   rOut << rView.bBigHandles;
/*N*/   rOut << rView.bDoubleClickTextEdit;
/*N*/   rOut << rView.bClickChangeRotation;
/*N*/
/*N*/   nULTemp = (sal_uInt32) rView.eNotesEditMode;       rOut << nULTemp;
/*N*/   nULTemp = (sal_uInt32) rView.eHandoutEditMode;     rOut << nULTemp;
/*N*/
/*N*/   rOut << static_cast<sal_uInt32>(rView.nDrawMode);
/*N*/   rOut << static_cast<sal_uInt32>(rView.nPreviewDrawMode);
/*N*/
/*N*/   rOut << rView.bShowPreviewInPageMode;
/*N*/   rOut << rView.bShowPreviewInMasterPageMode;
/*N*/   rOut << rView.bShowPreviewInOutlineMode;
/*N*/
/*N*/   return rOut;
/*N*/ }

/*************************************************************************
|*
|* Extractor fuer SvStream zum Laden
|*
\************************************************************************/

/*N*/ SvStream& operator >> (SvStream& rIn, FrameView& rView)
/*N*/ {
/*N*/   rIn >> (SdrView&) rView;
/*N*/
/*N*/   SdIOCompat aIO(rIn, STREAM_READ);
/*N*/
/*N*/   rIn >> rView.bRuler;
/*N*/   rIn >> rView.aVisibleLayers;
/*N*/   rIn >> rView.aLockedLayers;
/*N*/   rIn >> rView.aPrintableLayers;
/*N*/   rIn >> rView.aStandardHelpLines;
/*N*/
/*N*/   if (aIO.GetVersion() >= 1)
/*N*/   {
/*N*/       // Daten der Versionen >= 1 einlesen
/*N*/       rIn >> rView.aNotesHelpLines;
/*N*/       rIn >> rView.aHandoutHelpLines;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 2)
/*N*/   {
/*N*/       // Daten der Versionen >= 2 einlesen
/*N*/       rIn >> rView.bNoColors;
/*N*/       rIn >> rView.bNoAttribs;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 3)
/*N*/   {
/*N*/       sal_uInt32 nULTemp;
/*N*/       rIn >> rView.aVisArea;
/*N*/       rIn >> nULTemp;          rView.ePageKind = (PageKind) nULTemp;
/*N*/       rIn >> rView.nSelectedPage;
/*N*/       rIn >> nULTemp;          rView.eStandardEditMode = (EditMode) nULTemp;
/*N*/       rView.eNotesEditMode   = rView.eStandardEditMode;
/*N*/       rView.eHandoutEditMode = rView.eStandardEditMode;
/*N*/       rIn >> rView.bLayerMode;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 4)
/*N*/   {
/*N*/       rIn >> rView.bQuickEdit;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 5)
/*N*/   {
/*N*/       rIn >> rView.bDragWithCopy;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 6)
/*N*/   {
/*N*/       UINT16 nTemp;
/*N*/       rIn >> nTemp; rView.nSlidesPerRow = (USHORT)nTemp;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 7)
/*N*/   {
/*N*/       rIn >> rView.bBigHandles;
/*N*/       rIn >> rView.bDoubleClickTextEdit;
/*N*/       rIn >> rView.bClickChangeRotation;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 8)
/*N*/   {
/*N*/       sal_uInt32 nULTemp;
/*N*/       rIn >> nULTemp; rView.eNotesEditMode   = (EditMode) nULTemp;
/*N*/       rIn >> nULTemp; rView.eHandoutEditMode = (EditMode) nULTemp;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 9)
/*N*/   {
/*N*/       sal_uInt32 nTemp;
/*N*/       rIn >> nTemp;
/*N*/       rView.nDrawMode = nTemp;
/*N*/       rIn >> nTemp;
/*N*/       rView.nPreviewDrawMode = nTemp;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 10)
/*N*/   {
/*N*/       rIn >> rView.bShowPreviewInPageMode;
/*N*/       rIn >> rView.bShowPreviewInMasterPageMode;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 11)
/*N*/   {
/*N*/       rIn >> rView.bShowPreviewInOutlineMode;
/*N*/   }

    // Falls die UniqueLayerNames vorhanden sind, werden die Default-Namen
    // verwendet
/*N*/   String aLayerName(rView.GetActiveLayer());
/*N*/
/*N*/   if (aLayerName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_LAYOUT" )))
/*N*/   {
/*N*/       rView.SetActiveLayer(String(SdResId(STR_LAYER_LAYOUT)));
/*N*/   }
/*N*/   else if (aLayerName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BCKGRND" )))
/*N*/   {
/*?*/       rView.SetActiveLayer(String(SdResId(STR_LAYER_BCKGRND)));
/*N*/   }
/*N*/   else if (aLayerName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BACKGRNDOBJ" )))
/*N*/   {
/*?*/       rView.SetActiveLayer(String(SdResId(STR_LAYER_BCKGRNDOBJ)));
/*N*/   }
/*N*/   else if (aLayerName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_CONTROLS" )))
/*N*/   {
/*?*/       rView.SetActiveLayer(String(SdResId(STR_LAYER_CONTROLS)));
/*N*/   }
/*N*/   else if (aLayerName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_MEASURELINES" )))
/*N*/   {
/*?*/       rView.SetActiveLayer(String(SdResId(STR_LAYER_MEASURELINES)));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // #i12131#
/*N*/       // If layer name was not translated this may be an old layer name in
/*N*/       // translated speech version. To avoid errors (see bugid) this needs to be
/*N*/       // set to a useful default. Best default-layout is 'Layout'.
/*N*/       rView.SetActiveLayer(String(SdResId(STR_LAYER_LAYOUT)));
/*N*/   }
/*N*/
/*N*/   if (rView.GetModel())
/*N*/   {
/*N*/       USHORT nMaxPages = ((SdDrawDocument* )rView.GetModel())->
/*N*/                                     GetSdPageCount(rView.ePageKind);
/*N*/
/*N*/       if (rView.nSelectedPage >= nMaxPages)
/*N*/       {
/*N*/           // Ggf. auf die letzte Seite selektieren
/*N*/           rView.nSelectedPage = nMaxPages - 1;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return rIn;
/*N*/ }

/*************************************************************************
|*
|* Update mit Daten der SdOptions
|*
\************************************************************************/

/*N*/ void FrameView::Update(SdOptions* pOptions)
/*N*/ {
/*N*/   if (pOptions)
/*N*/   {
/*N*/       bRuler = pOptions->IsRulerVisible();
/*N*/       SetGridVisible( pOptions->IsGridVisible() );
/*N*/       SetSnapAngle( pOptions->GetAngle() );
/*N*/       SetGridSnap( pOptions->IsUseGridSnap() );
/*N*/       SetBordSnap( pOptions->IsSnapBorder()  );
/*N*/       SetHlplSnap( pOptions->IsSnapHelplines() );
/*N*/       SetOFrmSnap( pOptions->IsSnapFrame() );
/*N*/       SetOPntSnap( pOptions->IsSnapPoints() );
/*N*/       SetHlplVisible( pOptions->IsHelplines() );
/*N*/       SetDragStripes( pOptions->IsDragStripes() );
/*N*/       SetPlusHandlesAlwaysVisible( pOptions->IsHandlesBezier() );
/*N*/       SetSnapMagneticPixel( pOptions->GetSnapArea() );
/*N*/       SetMarkedHitMovesAlways( pOptions->IsMarkedHitMovesAlways() );
/*N*/       SetMoveOnlyDragging( pOptions->IsMoveOnlyDragging() );
/*N*/       SetSlantButShear( pOptions->IsMoveOnlyDragging() );
/*N*/       SetNoDragXorPolys ( !pOptions->IsMoveOutline() );
/*N*/       SetCrookNoContortion( pOptions->IsCrookNoContortion() );
/*N*/       SetAngleSnapEnabled( pOptions->IsRotate() );
/*N*/       SetBigOrtho( pOptions->IsBigOrtho() );
/*N*/       SetOrtho( pOptions->IsOrtho() );
/*N*/       SetEliminatePolyPointLimitAngle( pOptions->GetEliminatePolyPointLimitAngle() );
/*N*/       SetMasterPagePaintCaching( pOptions->IsMasterPagePaintCaching() );
/*N*/       GetModel()->SetPickThroughTransparentTextFrames( pOptions->IsPickThrough() );
/*N*/
/*N*/       SetLineDraft( pOptions->IsHairlineMode() );
/*N*/       SetFillDraft( pOptions->IsOutlineMode() );
/*N*/       SetTextDraft( pOptions->IsNoText() );
/*N*/       SetGrafDraft( pOptions->IsExternGraphic() );
/*N*/       SetSolidMarkHdl( pOptions->IsSolidMarkHdl() );
/*N*/       SetSolidDragging( pOptions->IsSolidDragging() );
/*N*/
/*N*/       SetGridCoarse( Size( pOptions->GetFldDrawX(), pOptions->GetFldDrawY() ) );
/*N*/       SetGridFine( Size( pOptions->GetFldDivisionX(), pOptions->GetFldDivisionY() ) );
/*N*/ //        SetSnapGrid( Size( pOptions->GetFldSnapX(), pOptions->GetFldSnapY() ) );
/*N*/       Fraction aFractX(pOptions->GetFldDrawX(), pOptions->GetFldDrawX() / ( pOptions->GetFldDivisionX() ? pOptions->GetFldDivisionX() : 1 ));
/*N*/       Fraction aFractY(pOptions->GetFldDrawY(), pOptions->GetFldDrawY() / ( pOptions->GetFldDivisionY() ? pOptions->GetFldDivisionY() : 1 ));
/*N*/       SetSnapGridWidth(aFractX, aFractY);
/*N*/       SetQuickEdit(pOptions->IsQuickEdit());
/*N*/       SetDragWithCopy(pOptions->IsDragWithCopy());
/*N*/
/*N*/       SetBigHandles( pOptions->IsBigHandles() );
/*N*/       SetDoubleClickTextEdit( pOptions->IsDoubleClickTextEdit() );
/*N*/       SetClickChangeRotation( pOptions->IsClickChangeRotation() );
/*N*/       SetPreviewDrawMode( pOptions->GetPreviewQuality() );
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* EditMode (Page oder MasterPage) des Arbeitsmodus setzen
|*
\************************************************************************/

/*N*/ void FrameView::SetViewShEditMode(EditMode eMode, PageKind eKind)
/*N*/ {
/*N*/   if (eKind == PK_STANDARD)
/*N*/   {
/*N*/       eStandardEditMode = eMode;
/*N*/   }
/*N*/   else if (eKind == PK_NOTES)
/*N*/   {
/*N*/       eNotesEditMode = eMode;
/*N*/   }
/*N*/   else if (eKind == PK_HANDOUT)
/*N*/   {
/*N*/       eHandoutEditMode = eMode;
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* EditMode (Page oder MasterPage) des Arbeitsmodus zurueckgeben
|*
\************************************************************************/

/*N*/ EditMode FrameView::GetViewShEditMode(PageKind eKind)
/*N*/ {
/*N*/   EditMode eMode = EM_PAGE;
/*N*/
/*N*/   if (eKind == PK_STANDARD)
/*N*/   {
/*N*/       eMode = eStandardEditMode;
/*N*/   }
/*N*/   else if (eKind == PK_NOTES)
/*N*/   {
/*N*/       eMode = eNotesEditMode;
/*N*/   }
/*N*/   else if (eKind == PK_HANDOUT)
/*N*/   {
/*N*/       eMode = eHandoutEditMode;
/*N*/   }
/*N*/
/*N*/   return (eMode);
/*N*/ }

/*N*/ static OUString createHelpLinesString( const SdrHelpLineList& rHelpLines )
/*N*/ {
/*N*/   OUStringBuffer aLines;
/*N*/
/*N*/   const USHORT nCount = rHelpLines.GetCount();
/*N*/   for( USHORT nHlpLine = 0; nHlpLine < nCount; nHlpLine++ )
/*N*/   {
/*N*/       const SdrHelpLine& rHelpLine = rHelpLines[nHlpLine];
/*N*/       const Point& rPos = rHelpLine.GetPos();
/*N*/
/*N*/       switch( rHelpLine.GetKind() )
/*N*/       {
/*N*/           case SDRHELPLINE_POINT:
/*N*/               aLines.append( (sal_Unicode)'P' );
/*N*/               aLines.append( (sal_Int32)rPos.X() );
/*N*/               aLines.append( (sal_Unicode)',' );
/*N*/               aLines.append( (sal_Int32)rPos.Y() );
/*N*/               break;
/*N*/           case SDRHELPLINE_VERTICAL:
/*N*/               aLines.append( (sal_Unicode)'V' );
/*N*/               aLines.append( (sal_Int32)rPos.X() );
/*N*/               break;
/*N*/           case SDRHELPLINE_HORIZONTAL:
/*N*/               aLines.append( (sal_Unicode)'H' );
/*N*/               aLines.append( (sal_Int32)rPos.Y() );
/*N*/               break;
/*N*/           default:
/*N*/               DBG_ERROR( "Unsupported helpline Kind!" );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aLines.makeStringAndClear();
/*N*/ }

#define addValue( n, v ) push_back( std::pair< OUString, Any >( OUString( RTL_CONSTASCII_USTRINGPARAM( n ) ), v ) )
/*N*/ void FrameView::WriteUserDataSequence ( ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& rValues, sal_Bool bBrowse )
/*N*/ {
/*N*/   std::vector< std::pair< OUString, Any > > aUserData;
/*N*/
/*N*/   aUserData.addValue( sUNO_View_GridIsVisible, makeAny( (sal_Bool)IsGridVisible() ) );
/*N*/   aUserData.addValue( sUNO_View_GridIsFront, makeAny( (sal_Bool)IsGridFront() ) );
/*N*/   aUserData.addValue( sUNO_View_IsSnapToGrid, makeAny( (sal_Bool)IsGridSnap() ) );
/*N*/   aUserData.addValue( sUNO_View_IsSnapToPageMargins, makeAny( (sal_Bool)IsBordSnap() ) );
/*N*/   aUserData.addValue( sUNO_View_IsSnapToSnapLines, makeAny( (sal_Bool)IsHlplSnap() ) );
/*N*/   aUserData.addValue( sUNO_View_IsSnapToObjectFrame, makeAny( (sal_Bool)IsOFrmSnap() ) );
/*N*/   aUserData.addValue( sUNO_View_IsSnapToObjectPoints, makeAny( (sal_Bool)IsOPntSnap() ) );

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsSnapLinesVisible ) );
//  pValue->Value <<= (sal_Bool)IsHlplVisible();
//  pValue++;nIndex++;

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsDragStripes ) );
//  pValue->Value <<= (sal_Bool)IsDragStripes();
//  pValue++;nIndex++;

/*N*/   aUserData.addValue( sUNO_View_IsPlusHandlesAlwaysVisible, makeAny( (sal_Bool)IsPlusHandlesAlwaysVisible() ) );
/*N*/   aUserData.addValue( sUNO_View_IsFrameDragSingles, makeAny( (sal_Bool)IsFrameDragSingles() ) );

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsMarkedHitMovesAlways ) );
//  pValue->Value <<= (sal_Bool)IsMarkedHitMovesAlways();
//  pValue++;nIndex++;

/*N*/   aUserData.addValue( sUNO_View_EliminatePolyPointLimitAngle, makeAny( (sal_Int32)GetEliminatePolyPointLimitAngle() ) );
/*N*/   aUserData.addValue( sUNO_View_IsEliminatePolyPoints, makeAny( (sal_Bool)IsEliminatePolyPoints() ) );

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsLineDraft ) );
//  pValue->Value <<= (sal_Bool)IsLineDraft();
//  pValue++;nIndex++;

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsFillDraft ) );
//  pValue->Value <<= (sal_Bool)IsFillDraft();
//  pValue++;nIndex++;

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsTextDraft ) );
//  pValue->Value <<= (sal_Bool)IsTextDraft();
//  pValue++;nIndex++;

//  pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsGrafDraft ) );
//  pValue->Value <<= (sal_Bool)IsGrafDraft();
//  pValue++;nIndex++;

/*N*/   Any aAny;
/*N*/   GetVisibleLayers().QueryValue( aAny );
/*N*/   aUserData.addValue( sUNO_View_VisibleLayers, aAny );
/*N*/
/*N*/   GetPrintableLayers().QueryValue( aAny );
/*N*/   aUserData.addValue( sUNO_View_PrintableLayers, aAny );
/*N*/
/*N*/   GetLockedLayers().QueryValue( aAny );
/*N*/   aUserData.addValue( sUNO_View_LockedLayers, aAny );
/*N*/
/*N*/   aUserData.addValue( sUNO_View_NoAttribs, makeAny( (sal_Bool)IsNoAttribs() ) );
/*N*/   aUserData.addValue( sUNO_View_NoColors, makeAny( (sal_Bool)IsNoColors() ) );
/*N*/
/*N*/   if( GetStandardHelpLines().GetCount() )
/*N*/       aUserData.addValue( sUNO_View_SnapLinesDrawing, makeAny( createHelpLinesString( GetStandardHelpLines() ) ) );
/*N*/
/*N*/   if( GetNotesHelpLines().GetCount() )
/*N*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aUserData.addValue( sUNO_View_SnapLinesNotes, makeAny( createHelpLinesString( GetNotesHelpLines() ) ) );
/*N*/
/*N*/   if( GetHandoutHelpLines().GetCount() )
/*N*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aUserData.addValue( sUNO_View_SnapLinesHandout, makeAny( createHelpLinesString( GetHandoutHelpLines() ) ) );
/*N*/
/*N*/   aUserData.addValue( sUNO_View_RulerIsVisible, makeAny( (sal_Bool)HasRuler() ) );
/*N*/   aUserData.addValue( sUNO_View_PageKind, makeAny( (sal_Int16)GetPageKind() ) );
/*N*/   aUserData.addValue( sUNO_View_SelectedPage, makeAny( (sal_Int16)GetSelectedPage() ) );
/*N*/   aUserData.addValue( sUNO_View_IsLayerMode, makeAny( (sal_Bool)IsLayerMode() ) );
/*N*/
/*N*/ //    pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsQuickEdit ) );
/*N*/ //    pValue->Value <<= (sal_Bool)IsQuickEdit();
/*N*/ //  pValue++;nIndex++;
/*N*/
/*N*/   aUserData.addValue( sUNO_View_IsBigHandles, makeAny( (sal_Bool)IsBigHandles() ) );
/*N*/   aUserData.addValue( sUNO_View_IsDoubleClickTextEdit,  makeAny( (sal_Bool)IsDoubleClickTextEdit() ) );
/*N*/   aUserData.addValue( sUNO_View_IsClickChangeRotation, makeAny( (sal_Bool)IsClickChangeRotation() ) );
/*N*/
/*N*/ //    pValue->Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsDragWithCopy ) );
/*N*/ //    pValue->Value <<= (sal_Bool)IsDragWithCopy();
/*N*/ //  pValue++;nIndex++;
/*N*/
/*N*/   aUserData.addValue( sUNO_View_SlidesPerRow, makeAny( (sal_Int16)GetSlidesPerRow() ) );
/* #107128# Product managment decided to not make this persistent
    aUserData.addValue( sUNO_View_DrawMode, makeAny( (sal_Int32)GetDrawMode() ) );
    aUserData.addValue( sUNO_View_PreviewDrawMode, makeAny( (sal_Int32)GetPreviewDrawMode() ) );
*/
/*N*/   aUserData.addValue( sUNO_View_IsShowPreviewInPageMode, makeAny( (sal_Bool)IsShowPreviewInPageMode() ) );
/*N*/   aUserData.addValue( sUNO_View_IsShowPreviewInMasterPageMode, makeAny( (sal_Bool)IsShowPreviewInMasterPageMode() ) );
/*N*/   aUserData.addValue( sUNO_View_SetShowPreviewInOutlineMode, makeAny( (sal_Bool)IsShowPreviewInOutlineMode() ) );
/*N*/     aUserData.addValue( sUNO_View_EditModeStandard, makeAny( (sal_Int32)GetViewShEditMode( PK_STANDARD ) ) );
/*N*/   aUserData.addValue( sUNO_View_EditModeNotes, makeAny( (sal_Int32)GetViewShEditMode( PK_NOTES ) ) );
/*N*/   aUserData.addValue( sUNO_View_EditModeHandout, makeAny( (sal_Int32)GetViewShEditMode( PK_HANDOUT ) ) );
/*N*/
/*N*/   {
/*N*/       const Rectangle aVisArea = GetVisArea();
/*N*/
/*N*/       aUserData.addValue( sUNO_View_VisibleAreaTop, makeAny( (sal_Int32)aVisArea.Top() ) );
/*N*/       aUserData.addValue( sUNO_View_VisibleAreaLeft, makeAny( (sal_Int32)aVisArea.Left() ) );
/*N*/       aUserData.addValue( sUNO_View_VisibleAreaWidth, makeAny( (sal_Int32)aVisArea.GetWidth() ) );
/*N*/       aUserData.addValue( sUNO_View_VisibleAreaHeight, makeAny( (sal_Int32)aVisArea.GetHeight() ) );
/*N*/   }
/*N*/
/*N*/   aUserData.addValue( sUNO_View_GridCoarseWidth, makeAny( (sal_Int32)GetGridCoarse().Width() ) );
/*N*/   aUserData.addValue( sUNO_View_GridCoarseHeight, makeAny( (sal_Int32)GetGridCoarse().Height() ) );
/*N*/   aUserData.addValue( sUNO_View_GridFineWidth, makeAny( (sal_Int32)GetGridFine().Width() ) );
/*N*/   aUserData.addValue( sUNO_View_GridFineHeight, makeAny( (sal_Int32)GetGridFine().Height() ) );
/*N*/   aUserData.addValue( sUNO_View_GridSnapWidth, makeAny( (sal_Int32)GetSnapGrid().Width() ) );
/*N*/   aUserData.addValue( sUNO_View_GridSnapHeight, makeAny( (sal_Int32)GetSnapGrid().Height() ) );
/*N*/   aUserData.addValue( sUNO_View_GridSnapWidthXNumerator, makeAny( (sal_Int32)GetSnapGridWidthX().GetNumerator() ) );
/*N*/   aUserData.addValue( sUNO_View_GridSnapWidthXDenominator, makeAny( (sal_Int32)GetSnapGridWidthX().GetDenominator() ) );
/*N*/   aUserData.addValue( sUNO_View_GridSnapWidthYNumerator, makeAny( (sal_Int32)GetSnapGridWidthY().GetNumerator() ) );
/*N*/   aUserData.addValue( sUNO_View_GridSnapWidthYDenominator, makeAny( (sal_Int32)GetSnapGridWidthY().GetDenominator() ) );
/*N*/   aUserData.addValue( sUNO_View_IsAngleSnapEnabled, makeAny( (sal_Bool)IsAngleSnapEnabled() ) );
/*N*/     aUserData.addValue( sUNO_View_SnapAngle, makeAny( (sal_Int32)GetSnapAngle() ) );
/*N*/
/*N*/   const sal_Int32 nOldLength = rValues.getLength();
/*N*/   rValues.realloc( nOldLength + aUserData.size() );
/*N*/
/*N*/   PropertyValue* pValue = &(rValues.getArray()[nOldLength]);
/*N*/
/*N*/   std::vector< std::pair< OUString, Any > >::iterator aIter( aUserData.begin() );
/*N*/   for( ; aIter != aUserData.end(); aIter++, pValue++ )
/*N*/   {
/*N*/       pValue->Name = (*aIter).first;
/*N*/       pValue->Value = (*aIter).second;
/*N*/   }
/*N*/ }
/*N*/ #undef addValue

 static void createHelpLinesFromString( const ::rtl::OUString& rLines, SdrHelpLineList& rHelpLines )
 {
     const sal_Unicode * pStr = rLines.getStr();
     SdrHelpLine aNewHelpLine;
     ::rtl::OUStringBuffer sBuffer;

     while( *pStr )
     {
         Point aPoint;

         switch( *pStr )
         {
         case (sal_Unicode)'P':
             aNewHelpLine.SetKind( SDRHELPLINE_POINT );
             break;
         case (sal_Unicode)'V':
             aNewHelpLine.SetKind( SDRHELPLINE_VERTICAL );
             break;
         case (sal_Unicode)'H':
             aNewHelpLine.SetKind( SDRHELPLINE_HORIZONTAL );
             break;
         default:
             DBG_ERROR( "syntax error in snap lines settings string" );
             return;
         }

         pStr++;

         while( (*pStr >= sal_Unicode('0') && *pStr <= sal_Unicode('9')) || (*pStr == '+') || (*pStr == '-') )
         {
             sBuffer.append( *pStr++ );
         }

         sal_Int32 nValue = sBuffer.makeStringAndClear().toInt32();

         if( aNewHelpLine.GetKind() == SDRHELPLINE_HORIZONTAL )
         {
             aPoint.Y() = nValue;
         }
         else
         {
             aPoint.X() = nValue;

             if( aNewHelpLine.GetKind() == SDRHELPLINE_POINT )
             {
                 if( *pStr++ != ',' )
                     return;

                 while( (*pStr >= sal_Unicode('0') && *pStr <= sal_Unicode('9')) || (*pStr == '+') || (*pStr == '-')  )
                 {
                     sBuffer.append( *pStr++ );
                 }

                 aPoint.Y() = sBuffer.makeStringAndClear().toInt32();

             }
         }

         aNewHelpLine.SetPos( aPoint );
         rHelpLines.Insert( aNewHelpLine );
     }
 }

/*?*/ void FrameView::ReadUserDataSequence ( const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& rSequence, sal_Bool bBrowse )
/*?*/ {
/*?*/       const sal_Int32 nLength = rSequence.getLength();
     if (nLength)
     {
         sal_Bool bBool;
         sal_Int32 nInt32;
         sal_Int16 nInt16;
         ::rtl::OUString aString;

         sal_Int32 aSnapGridWidthXNum = GetSnapGridWidthX().GetNumerator();
         sal_Int32 aSnapGridWidthXDom = GetSnapGridWidthX().GetDenominator();

         sal_Int32 aSnapGridWidthYNum = GetSnapGridWidthY().GetNumerator();
         sal_Int32 aSnapGridWidthYDom = GetSnapGridWidthY().GetDenominator();

         const ::com::sun::star::beans::PropertyValue *pValue = rSequence.getConstArray();
         for (sal_Int16 i = 0 ; i < nLength; i++, pValue++ )
         {
             if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_ViewId ) ) )
             {
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapLinesDrawing ) ) )
             {
                 if( pValue->Value >>= aString )
                 {
                     SdrHelpLineList aHelpLines;
                     createHelpLinesFromString( aString, aHelpLines );
                     SetStandardHelpLines( aHelpLines );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapLinesNotes ) ) )
             {
                 if( pValue->Value >>= aString )
                 {
                     SdrHelpLineList aHelpLines;
                     createHelpLinesFromString( aString, aHelpLines );
                     SetNotesHelpLines( aHelpLines );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapLinesHandout ) ) )
             {
                 if( pValue->Value >>= aString )
                 {
                     SdrHelpLineList aHelpLines;
                     createHelpLinesFromString( aString, aHelpLines );
                     SetHandoutHelpLines( aHelpLines );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_RulerIsVisible ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetRuler( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_PageKind ) ) )
             {
                 if( pValue->Value >>= nInt16 )
                 {
                     SetPageKind( (PageKind)nInt16 );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SelectedPage ) ) )
             {
                 if( pValue->Value >>= nInt16 )
                 {
                     SetSelectedPage( (USHORT)nInt16 );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsLayerMode ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetLayerMode( bBool );
                 }
             }
 /*         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsQuickEdit ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetQuickEdit( bBool );
                 }
             }
 */         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsBigHandles ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetBigHandles( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsDoubleClickTextEdit ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetDoubleClickTextEdit( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsClickChangeRotation ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetClickChangeRotation( bBool );
                 }
             }
 /*         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsDragWithCopy ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetDragWithCopy( bBool );
                 }
             }
 */         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SlidesPerRow ) ) )
             {
                 if( pValue->Value >>= nInt16 )
                 {
                     SetSlidesPerRow( (USHORT)nInt16 );
                 }
             }
 /* #107128# Product managment decided to not make this persistent
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_DrawMode ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
                     if( rStyleSettings.GetHighContrastMode() )
                         continue;
                     SetDrawMode( (ULONG)nInt32 );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_PreviewDrawMode ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
                     SvtAccessibilityOptions aAccOptions;
                     if( rStyleSettings.GetHighContrastMode() && aAccOptions.GetIsForPagePreviews() )
                         continue;
                     SetPreviewDrawMode( (ULONG)nInt32 );
                 }
             }
 */
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsShowPreviewInPageMode ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetShowPreviewInPageMode( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsShowPreviewInMasterPageMode ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetShowPreviewInMasterPageMode( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SetShowPreviewInOutlineMode ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetShowPreviewInOutlineMode( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EditModeStandard ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     SetViewShEditMode( (EditMode)nInt32, PK_STANDARD );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EditModeNotes ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     SetViewShEditMode( (EditMode)nInt32, PK_NOTES );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EditModeHandout ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     SetViewShEditMode( (EditMode)nInt32, PK_HANDOUT );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaTop ) ) )
             {
                 sal_Int32 nTop;
                 if( pValue->Value >>= nTop )
                 {
                     Rectangle aVisArea( GetVisArea() );
                     aVisArea.nBottom += nTop - aVisArea.nTop;
                     aVisArea.nTop = nTop;
                     SetVisArea( aVisArea );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaLeft ) ) )
             {
                 sal_Int32 nLeft;
                 if( pValue->Value >>= nLeft )
                 {
                     Rectangle aVisArea( GetVisArea() );
                     aVisArea.nRight += nLeft - aVisArea.nLeft;
                     aVisArea.nLeft = nLeft;
                     SetVisArea( aVisArea );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaWidth ) ) )
             {
                 sal_Int32 nWidth;
                 if( pValue->Value >>= nWidth )
                 {
                     Rectangle aVisArea( GetVisArea() );
                     aVisArea.nRight = aVisArea.nLeft + nWidth - 1;
                     SetVisArea( aVisArea );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaHeight ) ) )
             {
                 sal_Int32 nHeight;
                 if( pValue->Value >>= nHeight )
                 {
                     Rectangle aVisArea( GetVisArea() );
                     aVisArea.nBottom = nHeight + aVisArea.nTop - 1;
                     SetVisArea( aVisArea );
                 }
             }

             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridIsVisible ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetGridVisible( bBool );
                 }
             }

             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToGrid ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetGridSnap( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridIsFront ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetGridFront( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToPageMargins ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetBordSnap( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToSnapLines ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetHlplSnap( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToObjectFrame ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetOFrmSnap( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToObjectPoints ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetOPntSnap( bBool );
                 }
             }
 /*         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapLinesVisible ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetHlplVisible( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsDragStripes ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetDragStripes( bBool );
                 }
             }
 */         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsPlusHandlesAlwaysVisible ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetPlusHandlesAlwaysVisible( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsFrameDragSingles ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetFrameDragSingles( bBool );
                 }
             }
 /*         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsMarkedHitMovesAlways ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetMarkedHitMovesAlways( bBool );
                 }
             }
 */         else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EliminatePolyPointLimitAngle ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     SetEliminatePolyPointLimitAngle( nInt32 );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsEliminatePolyPoints ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetEliminatePolyPoints( bBool );
                 }
             }
 /*
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsLineDraft ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetLineDraft( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsFillDraft ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetFillDraft( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsTextDraft ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetTextDraft( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsGrafDraft ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetGrafDraft( bBool );
                 }
             }
 */
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_ActiveLayer ) ) )
             {
                 if( pValue->Value >>= aString )
                 {
                     SetActiveLayer( aString );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_NoAttribs ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetNoAttribs( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_NoColors ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetNoColors( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridCoarseWidth ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const Size aCoarse( nInt32, GetGridCoarse().Height() );
                     SetGridCoarse( aCoarse );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridCoarseHeight ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const Size aCoarse( GetGridCoarse().Width(), nInt32 );
                     SetGridCoarse( aCoarse );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridFineWidth ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const Size aCoarse( nInt32, GetGridFine().Height() );
                     SetGridFine( aCoarse );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridFineHeight ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const Size aCoarse( GetGridFine().Width(), nInt32 );
                     SetGridFine( aCoarse );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidth ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const Size aCoarse( nInt32, GetSnapGrid().Height() );
                     SetSnapGrid( aCoarse );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapHeight ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     const Size aCoarse( GetSnapGrid().Width(), nInt32 );
                     SetSnapGrid( aCoarse );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsAngleSnapEnabled ) ) )
             {
                 if( pValue->Value >>= bBool )
                 {
                     SetAngleSnapEnabled( bBool );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapAngle ) ) )
             {
                 if( pValue->Value >>= nInt32 )
                 {
                     SetSnapAngle( nInt32 );
                 }
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthXNumerator ) ) )
             {
                 pValue->Value >>= aSnapGridWidthXNum;
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthXDenominator ) ) )
             {
                 pValue->Value >>= aSnapGridWidthXDom;
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthYNumerator ) ) )
             {
                 pValue->Value >>= aSnapGridWidthYNum;
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthYDenominator ) ) )
             {
                 pValue->Value >>= aSnapGridWidthYDom;
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleLayers ) ) )
             {
                 SetOfByte aSetOfBytes;
                 aSetOfBytes.PutValue( pValue->Value );
                 SetVisibleLayers( aSetOfBytes );
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_PrintableLayers ) ) )
             {
                 SetOfByte aSetOfBytes;
                 aSetOfBytes.PutValue( pValue->Value );
                 SetPrintableLayers( aSetOfBytes );
             }
             else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_LockedLayers ) ) )
             {
                 SetOfByte aSetOfBytes;
                 aSetOfBytes.PutValue( pValue->Value );
                 SetLockedLayers( aSetOfBytes );
             }
         }

         const Fraction aSnapGridWidthX( aSnapGridWidthXNum, aSnapGridWidthXDom );
         const Fraction aSnapGridWidthY( aSnapGridWidthYNum, aSnapGridWidthYDom );

         SetSnapGridWidth( aSnapGridWidthX, aSnapGridWidthY );
     }
/*?*/ }
} //namespace binfilter
