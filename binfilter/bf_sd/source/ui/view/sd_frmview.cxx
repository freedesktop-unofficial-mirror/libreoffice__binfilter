/*************************************************************************
 *
 *  $RCSfile: sd_frmview.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:43 $
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

#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SFX_TOPFRM_HXX //autogen wg. SfxTopViewFrame
#include <bf_sfx2/topfrm.hxx>
#endif

#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HPP_
#include <com/sun/star/awt/Rectangle.hpp>
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _SD_UNOKYWDS_HXX_
#include "unokywds.hxx"
#endif

#include <vector>

#include "frmview.hxx"
#include "viewshel.hxx"
#include "drawdoc.hxx"
#include "docshell.hxx"
#include "optsitem.hxx"
#include "drviewsh.hxx"
#include "outlnvsh.hxx"
#include "slidvish.hxx"
#include "app.hxx"
#include "sdresid.hxx"
#include "pres.hxx"
#include "glob.hrc"
#include "sdiocmpt.hxx"

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
/*N*/           SdViewShell* pViewSh = NULL;
/*N*/           SfxViewShell* pSfxViewSh = NULL;
/*N*/           SfxViewFrame* pSfxViewFrame = SfxViewFrame::GetFirst(pDocShell,
/*N*/                                                                TYPE(SfxTopViewFrame));
/*N*/
/*N*/           while (pSfxViewFrame)
/*N*/           {
/*?*/               // Anzahl FrameViews ermitteln
/*?*/               pSfxViewSh = pSfxViewFrame->GetViewShell();
/*?*/               pViewSh = PTR_CAST( SdViewShell, pSfxViewSh );
/*?*/
/*?*/               if (pViewSh)
/*?*/               {
/*?*/                   nSdViewShellCount++;
/*?*/
/*?*/                   if (pViewSh->ISA(SdDrawViewShell))
/*?*/                   {
/*?*/                       nPresViewShellId = SID_VIEWSHELL0;
/*?*/                   }
/*?*/                   else if (pViewSh->ISA(SdSlideViewShell))
/*?*/                   {
/*?*/                       nPresViewShellId = SID_VIEWSHELL1;
/*?*/                   }
/*?*/                   else if (pViewSh->ISA(SdOutlineViewShell))
/*?*/                   {
/*?*/                       nPresViewShellId = SID_VIEWSHELL2;
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               pSfxViewFrame = SfxViewFrame::GetNext(*pSfxViewFrame, pDocShell,
/*?*/                                                     TYPE(SfxTopViewFrame));
/*?*/           }
/*?*/
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
/*N*/   ULONG nULTemp;
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
/*N*/   nULTemp = (ULONG) rView.ePageKind;            rOut << nULTemp;
/*N*/   rOut << rView.nSelectedPage;
/*N*/   nULTemp = (ULONG) rView.eStandardEditMode;    rOut << nULTemp;
/*N*/   rOut << rView.bLayerMode;
/*N*/   rOut << rView.bQuickEdit;
/*N*/   rOut << rView.bDragWithCopy;
/*N*/   rOut << (UINT16)rView.nSlidesPerRow;
/*N*/
/*N*/   rOut << rView.bBigHandles;
/*N*/   rOut << rView.bDoubleClickTextEdit;
/*N*/   rOut << rView.bClickChangeRotation;
/*N*/
/*N*/   nULTemp = (ULONG) rView.eNotesEditMode;       rOut << nULTemp;
/*N*/   nULTemp = (ULONG) rView.eHandoutEditMode;     rOut << nULTemp;
/*N*/
/*N*/   rOut << rView.nDrawMode;
/*N*/   rOut << rView.nPreviewDrawMode;
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
/*N*/       ULONG nULTemp;
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
/*N*/       ULONG nULTemp;
/*N*/       rIn >> nULTemp; rView.eNotesEditMode   = (EditMode) nULTemp;
/*N*/       rIn >> nULTemp; rView.eHandoutEditMode = (EditMode) nULTemp;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() >= 9)
/*N*/   {
/*N*/       rIn >> rView.nDrawMode;
/*N*/       rIn >> rView.nPreviewDrawMode;
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

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsSnapLinesVisible ) );
//  pValue->Value <<= (sal_Bool)IsHlplVisible();
//  pValue++;nIndex++;

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsDragStripes ) );
//  pValue->Value <<= (sal_Bool)IsDragStripes();
//  pValue++;nIndex++;

/*N*/   aUserData.addValue( sUNO_View_IsPlusHandlesAlwaysVisible, makeAny( (sal_Bool)IsPlusHandlesAlwaysVisible() ) );
/*N*/   aUserData.addValue( sUNO_View_IsFrameDragSingles, makeAny( (sal_Bool)IsFrameDragSingles() ) );

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsMarkedHitMovesAlways ) );
//  pValue->Value <<= (sal_Bool)IsMarkedHitMovesAlways();
//  pValue++;nIndex++;

/*N*/   aUserData.addValue( sUNO_View_EliminatePolyPointLimitAngle, makeAny( (sal_Int32)GetEliminatePolyPointLimitAngle() ) );
/*N*/   aUserData.addValue( sUNO_View_IsEliminatePolyPoints, makeAny( (sal_Bool)IsEliminatePolyPoints() ) );

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsLineDraft ) );
//  pValue->Value <<= (sal_Bool)IsLineDraft();
//  pValue++;nIndex++;

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsFillDraft ) );
//  pValue->Value <<= (sal_Bool)IsFillDraft();
//  pValue++;nIndex++;

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsTextDraft ) );
//  pValue->Value <<= (sal_Bool)IsTextDraft();
//  pValue++;nIndex++;

//  pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsGrafDraft ) );
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
/*N*/       DBG_ASSERT(0, "STRIP"); //STRIP001 aUserData.addValue( sUNO_View_SnapLinesNotes, makeAny( createHelpLinesString( GetNotesHelpLines() ) ) );
/*N*/
/*N*/   if( GetHandoutHelpLines().GetCount() )
/*N*/       DBG_ASSERT(0, "STRIP"); //STRIP001 aUserData.addValue( sUNO_View_SnapLinesHandout, makeAny( createHelpLinesString( GetHandoutHelpLines() ) ) );
/*N*/
/*N*/   aUserData.addValue( sUNO_View_RulerIsVisible, makeAny( (sal_Bool)HasRuler() ) );
/*N*/   aUserData.addValue( sUNO_View_PageKind, makeAny( (sal_Int16)GetPageKind() ) );
/*N*/   aUserData.addValue( sUNO_View_SelectedPage, makeAny( (sal_Int16)GetSelectedPage() ) );
/*N*/   aUserData.addValue( sUNO_View_IsLayerMode, makeAny( (sal_Bool)IsLayerMode() ) );
/*N*/
/*N*/ //    pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsQuickEdit ) );
/*N*/ //    pValue->Value <<= (sal_Bool)IsQuickEdit();
/*N*/ //  pValue++;nIndex++;
/*N*/
/*N*/   aUserData.addValue( sUNO_View_IsBigHandles, makeAny( (sal_Bool)IsBigHandles() ) );
/*N*/   aUserData.addValue( sUNO_View_IsDoubleClickTextEdit,  makeAny( (sal_Bool)IsDoubleClickTextEdit() ) );
/*N*/   aUserData.addValue( sUNO_View_IsClickChangeRotation, makeAny( (sal_Bool)IsClickChangeRotation() ) );
/*N*/
/*N*/ //    pValue->Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( sUNO_View_IsDragWithCopy ) );
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

//STRIP001 static void createHelpLinesFromString( const rtl::OUString& rLines, SdrHelpLineList& rHelpLines )
//STRIP001 {
//STRIP001  const sal_Unicode * pStr = rLines.getStr();
//STRIP001  SdrHelpLine aNewHelpLine;
//STRIP001  rtl::OUStringBuffer sBuffer;
//STRIP001
//STRIP001  while( *pStr )
//STRIP001  {
//STRIP001      Point aPoint;
//STRIP001
//STRIP001      switch( *pStr )
//STRIP001      {
//STRIP001      case (sal_Unicode)'P':
//STRIP001          aNewHelpLine.SetKind( SDRHELPLINE_POINT );
//STRIP001          break;
//STRIP001      case (sal_Unicode)'V':
//STRIP001          aNewHelpLine.SetKind( SDRHELPLINE_VERTICAL );
//STRIP001          break;
//STRIP001      case (sal_Unicode)'H':
//STRIP001          aNewHelpLine.SetKind( SDRHELPLINE_HORIZONTAL );
//STRIP001          break;
//STRIP001      default:
//STRIP001          DBG_ERROR( "syntax error in snap lines settings string" );
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001      pStr++;
//STRIP001
//STRIP001      while( (*pStr >= sal_Unicode('0') && *pStr <= sal_Unicode('9')) || (*pStr == '+') || (*pStr == '-') )
//STRIP001      {
//STRIP001          sBuffer.append( *pStr++ );
//STRIP001      }
//STRIP001
//STRIP001      sal_Int32 nValue = sBuffer.makeStringAndClear().toInt32();
//STRIP001
//STRIP001      if( aNewHelpLine.GetKind() == SDRHELPLINE_HORIZONTAL )
//STRIP001      {
//STRIP001          aPoint.Y() = nValue;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aPoint.X() = nValue;
//STRIP001
//STRIP001          if( aNewHelpLine.GetKind() == SDRHELPLINE_POINT )
//STRIP001          {
//STRIP001              if( *pStr++ != ',' )
//STRIP001                  return;
//STRIP001
//STRIP001              while( (*pStr >= sal_Unicode('0') && *pStr <= sal_Unicode('9')) || (*pStr == '+') || (*pStr == '-')  )
//STRIP001              {
//STRIP001                  sBuffer.append( *pStr++ );
//STRIP001              }
//STRIP001
//STRIP001              aPoint.Y() = sBuffer.makeStringAndClear().toInt32();
//STRIP001
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      aNewHelpLine.SetPos( aPoint );
//STRIP001      rHelpLines.Insert( aNewHelpLine );
//STRIP001  }
//STRIP001 }

/*?*/ void FrameView::ReadUserDataSequence ( const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& rSequence, sal_Bool bBrowse )
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  const sal_Int32 nLength = rSequence.getLength();
//STRIP001     if (nLength)
//STRIP001     {
//STRIP001      sal_Bool bBool;
//STRIP001      sal_Int32 nInt32;
//STRIP001      sal_Int16 nInt16;
//STRIP001      rtl::OUString aString;
//STRIP001
//STRIP001      sal_Int32 aSnapGridWidthXNum = GetSnapGridWidthX().GetNumerator();
//STRIP001      sal_Int32 aSnapGridWidthXDom = GetSnapGridWidthX().GetDenominator();
//STRIP001
//STRIP001      sal_Int32 aSnapGridWidthYNum = GetSnapGridWidthY().GetNumerator();
//STRIP001      sal_Int32 aSnapGridWidthYDom = GetSnapGridWidthY().GetDenominator();
//STRIP001
//STRIP001         const com::sun::star::beans::PropertyValue *pValue = rSequence.getConstArray();
//STRIP001         for (sal_Int16 i = 0 ; i < nLength; i++, pValue++ )
//STRIP001         {
//STRIP001             if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_ViewId ) ) )
//STRIP001             {
//STRIP001             }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapLinesDrawing ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= aString )
//STRIP001              {
//STRIP001                  SdrHelpLineList aHelpLines;
//STRIP001                  createHelpLinesFromString( aString, aHelpLines );
//STRIP001                  SetStandardHelpLines( aHelpLines );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapLinesNotes ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= aString )
//STRIP001              {
//STRIP001                  SdrHelpLineList aHelpLines;
//STRIP001                  createHelpLinesFromString( aString, aHelpLines );
//STRIP001                  SetNotesHelpLines( aHelpLines );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapLinesHandout ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= aString )
//STRIP001              {
//STRIP001                  SdrHelpLineList aHelpLines;
//STRIP001                  createHelpLinesFromString( aString, aHelpLines );
//STRIP001                  SetHandoutHelpLines( aHelpLines );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_RulerIsVisible ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetRuler( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_PageKind ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt16 )
//STRIP001              {
//STRIP001                  SetPageKind( (PageKind)nInt16 );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SelectedPage ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt16 )
//STRIP001              {
//STRIP001                  SetSelectedPage( (USHORT)nInt16 );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsLayerMode ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetLayerMode( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 /*           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsQuickEdit ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetQuickEdit( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 */           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsBigHandles ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetBigHandles( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsDoubleClickTextEdit ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetDoubleClickTextEdit( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsClickChangeRotation ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetClickChangeRotation( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 /*           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsDragWithCopy ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetDragWithCopy( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 */           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SlidesPerRow ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt16 )
//STRIP001              {
//STRIP001                  SetSlidesPerRow( (USHORT)nInt16 );
//STRIP001              }
//STRIP001          }
//STRIP001 /* #107128# Product managment decided to not make this persistent
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_DrawMode ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
//STRIP001                  if( rStyleSettings.GetHighContrastMode() )
//STRIP001                      continue;
//STRIP001                  SetDrawMode( (ULONG)nInt32 );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_PreviewDrawMode ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
//STRIP001                  SvtAccessibilityOptions aAccOptions;
//STRIP001                  if( rStyleSettings.GetHighContrastMode() && aAccOptions.GetIsForPagePreviews() )
//STRIP001                      continue;
//STRIP001                  SetPreviewDrawMode( (ULONG)nInt32 );
//STRIP001              }
//STRIP001          }
//STRIP001 */
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsShowPreviewInPageMode ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetShowPreviewInPageMode( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsShowPreviewInMasterPageMode ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetShowPreviewInMasterPageMode( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SetShowPreviewInOutlineMode ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetShowPreviewInOutlineMode( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EditModeStandard ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  SetViewShEditMode( (EditMode)nInt32, PK_STANDARD );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EditModeNotes ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  SetViewShEditMode( (EditMode)nInt32, PK_NOTES );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EditModeHandout ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  SetViewShEditMode( (EditMode)nInt32, PK_HANDOUT );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaTop ) ) )
//STRIP001          {
//STRIP001              sal_Int32 nTop;
//STRIP001              if( pValue->Value >>= nTop )
//STRIP001              {
//STRIP001                  Rectangle aVisArea( GetVisArea() );
//STRIP001                  aVisArea.nBottom += nTop - aVisArea.nTop;
//STRIP001                  aVisArea.nTop = nTop;
//STRIP001                  SetVisArea( aVisArea );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaLeft ) ) )
//STRIP001          {
//STRIP001              sal_Int32 nLeft;
//STRIP001              if( pValue->Value >>= nLeft )
//STRIP001              {
//STRIP001                  Rectangle aVisArea( GetVisArea() );
//STRIP001                  aVisArea.nRight += nLeft - aVisArea.nLeft;
//STRIP001                  aVisArea.nLeft = nLeft;
//STRIP001                  SetVisArea( aVisArea );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaWidth ) ) )
//STRIP001          {
//STRIP001              sal_Int32 nWidth;
//STRIP001              if( pValue->Value >>= nWidth )
//STRIP001              {
//STRIP001                  Rectangle aVisArea( GetVisArea() );
//STRIP001                  aVisArea.nRight = aVisArea.nLeft + nWidth - 1;
//STRIP001                  SetVisArea( aVisArea );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleAreaHeight ) ) )
//STRIP001          {
//STRIP001              sal_Int32 nHeight;
//STRIP001              if( pValue->Value >>= nHeight )
//STRIP001              {
//STRIP001                  Rectangle aVisArea( GetVisArea() );
//STRIP001                  aVisArea.nBottom = nHeight + aVisArea.nTop - 1;
//STRIP001                  SetVisArea( aVisArea );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridIsVisible ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetGridVisible( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToGrid ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetGridSnap( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridIsFront ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetGridFront( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToPageMargins ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetBordSnap( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToSnapLines ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetHlplSnap( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToObjectFrame ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetOFrmSnap( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapToObjectPoints ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetOPntSnap( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 /*           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsSnapLinesVisible ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetHlplVisible( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsDragStripes ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetDragStripes( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 */           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsPlusHandlesAlwaysVisible ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetPlusHandlesAlwaysVisible( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsFrameDragSingles ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetFrameDragSingles( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 /*           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsMarkedHitMovesAlways ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetMarkedHitMovesAlways( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 */           else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_EliminatePolyPointLimitAngle ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  SetEliminatePolyPointLimitAngle( nInt32 );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsEliminatePolyPoints ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetEliminatePolyPoints( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 /*
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsLineDraft ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetLineDraft( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsFillDraft ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetFillDraft( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsTextDraft ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetTextDraft( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsGrafDraft ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetGrafDraft( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001 */
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_ActiveLayer ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= aString )
//STRIP001              {
//STRIP001                  SetActiveLayer( aString );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_NoAttribs ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetNoAttribs( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_NoColors ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetNoColors( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridCoarseWidth ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const Size aCoarse( nInt32, GetGridCoarse().Height() );
//STRIP001                  SetGridCoarse( aCoarse );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridCoarseHeight ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const Size aCoarse( GetGridCoarse().Width(), nInt32 );
//STRIP001                  SetGridCoarse( aCoarse );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridFineWidth ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const Size aCoarse( nInt32, GetGridFine().Height() );
//STRIP001                  SetGridFine( aCoarse );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridFineHeight ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const Size aCoarse( GetGridFine().Width(), nInt32 );
//STRIP001                  SetGridFine( aCoarse );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidth ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const Size aCoarse( nInt32, GetSnapGrid().Height() );
//STRIP001                  SetSnapGrid( aCoarse );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapHeight ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  const Size aCoarse( GetSnapGrid().Width(), nInt32 );
//STRIP001                  SetSnapGrid( aCoarse );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_IsAngleSnapEnabled ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= bBool )
//STRIP001              {
//STRIP001                  SetAngleSnapEnabled( bBool );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_SnapAngle ) ) )
//STRIP001          {
//STRIP001              if( pValue->Value >>= nInt32 )
//STRIP001              {
//STRIP001                  SetSnapAngle( nInt32 );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthXNumerator ) ) )
//STRIP001          {
//STRIP001              pValue->Value >>= aSnapGridWidthXNum;
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthXDenominator ) ) )
//STRIP001          {
//STRIP001              pValue->Value >>= aSnapGridWidthXDom;
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthYNumerator ) ) )
//STRIP001          {
//STRIP001              pValue->Value >>= aSnapGridWidthYNum;
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_GridSnapWidthYDenominator ) ) )
//STRIP001          {
//STRIP001              pValue->Value >>= aSnapGridWidthYDom;
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_VisibleLayers ) ) )
//STRIP001          {
//STRIP001              SetOfByte aSetOfBytes;
//STRIP001              aSetOfBytes.PutValue( pValue->Value );
//STRIP001              SetVisibleLayers( aSetOfBytes );
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_PrintableLayers ) ) )
//STRIP001          {
//STRIP001              SetOfByte aSetOfBytes;
//STRIP001              aSetOfBytes.PutValue( pValue->Value );
//STRIP001              SetPrintableLayers( aSetOfBytes );
//STRIP001          }
//STRIP001          else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sUNO_View_LockedLayers ) ) )
//STRIP001          {
//STRIP001              SetOfByte aSetOfBytes;
//STRIP001              aSetOfBytes.PutValue( pValue->Value );
//STRIP001              SetLockedLayers( aSetOfBytes );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      const Fraction aSnapGridWidthX( aSnapGridWidthXNum, aSnapGridWidthXDom );
//STRIP001      const Fraction aSnapGridWidthY( aSnapGridWidthYNum, aSnapGridWidthYDom );
//STRIP001
//STRIP001      SetSnapGridWidth( aSnapGridWidthX, aSnapGridWidthY );
//STRIP001  }
/*?*/ }
