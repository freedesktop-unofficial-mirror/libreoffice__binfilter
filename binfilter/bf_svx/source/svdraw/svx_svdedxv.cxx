/*************************************************************************
 *
 *  $RCSfile: svx_svdedxv.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:10 $
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

#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif

#include "svdedxv.hxx"
#include <svtools/solar.hrc>

#ifndef _STRING_H
#include <tools/string.h>
#endif

#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif

#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif

#ifndef _SV_HATCH_HXX //autogen
#include <vcl/hatch.hxx>
#endif

#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#ifndef _EDITSTAT_HXX //autogen
#include <editstat.hxx>
#endif

#ifndef _SV_CONFIG_HXX //autogen
#include <vcl/config.hxx>
#endif

#ifndef _SV_CURSOR_HXX //autogen
#include <vcl/cursor.hxx>
#endif


#include "editobj.hxx"
#include "outlobj.hxx"
#include "scripttypeitem.hxx"
#include "svditext.hxx"
#include "svdoutl.hxx"
#include "svdxout.hxx"
#include "svdotext.hxx"
#include "svdundo.hxx"
#include "svditer.hxx"
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svdetc.hxx"   // fuer GetDraftFillColor
#include "svdibrow.hxx"
#include "svdoutl.hxx"
#include "svddrgv.hxx"  // fuer SetSolidDragging()
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache

#ifndef _OUTLINER_HXX //autogen
#include "outliner.hxx"
#endif

#ifndef _SVX_ADJITEM_HXX //autogen
#include "adjitem.hxx"
#endif

// #98988#
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrObjEditView::ImpClearVars()
/*N*/ {
/*N*/     bQuickTextEditMode=TRUE;
/*N*/     bMacroMode=TRUE;
/*N*/     pTextEditObj=NULL;
/*N*/     pTextEditOutliner=NULL;
/*N*/     pTextEditOutlinerView=NULL;
/*N*/     pTextEditPV=NULL;
/*N*/     pTextEditWin=NULL;
/*N*/     pTextEditCursorMerker=NULL;
/*N*/     pEditPara=NULL;
/*N*/     bTextEditNewObj=FALSE;
/*N*/     bMacroDown=FALSE;
/*N*/     pMacroObj=NULL;
/*N*/     pMacroPV=NULL;
/*N*/     pMacroWin=NULL;
/*N*/     nMacroTol=0;
/*N*/     bTextEditDontDelete=FALSE;
/*N*/     bTextEditOnlyOneView=FALSE;
/*N*/ }

/*N*/ SdrObjEditView::SdrObjEditView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/     SdrGlueEditView(pModel1,pOut)
/*N*/ {
/*N*/     ImpClearVars();
/*N*/ }

/*?*/ SdrObjEditView::SdrObjEditView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/     SdrGlueEditView(pModel1,pXOut)
/*?*/ {
/*?*/     ImpClearVars();
/*?*/ }

/*N*/ SdrObjEditView::~SdrObjEditView()
/*N*/ {
/*N*/   pTextEditWin = NULL;            // Damit es in EndTextEdit kein ShowCursor gibt
/*N*/   if (IsTextEdit()){DBG_ASSERT(0, "STRIP"); }//STRIP001  EndTextEdit();
/*N*/     if (pTextEditOutliner!=NULL) {
/*?*/         delete pTextEditOutliner;
/*N*/     }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrObjEditView::IsAction() const
/*N*/ {
/*N*/     return IsMacroObj() || SdrGlueEditView::IsAction();
/*N*/ }

//STRIP001 void SdrObjEditView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001     if (IsMacroObj()) MovMacroObj(rPnt);
//STRIP001     SdrGlueEditView::MovAction(rPnt);
//STRIP001 }

//STRIP001 void SdrObjEditView::EndAction()
//STRIP001 {
//STRIP001     if (IsMacroObj()) EndMacroObj();
//STRIP001     SdrGlueEditView::EndAction();
//STRIP001 }

//STRIP001 void SdrObjEditView::BckAction()
//STRIP001 {
//STRIP001     BrkMacroObj();
//STRIP001     SdrGlueEditView::BckAction();
//STRIP001 }

/*N*/ void SdrObjEditView::BrkAction()
/*N*/ {
/*N*/     BrkMacroObj();
/*N*/     SdrGlueEditView::BrkAction();
/*N*/ }

//STRIP001 void SdrObjEditView::TakeActionRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001     if (IsMacroObj()) {
//STRIP001         rRect=pMacroObj->GetBoundRect()+pMacroPV->GetOffset();
//STRIP001     } else {
//STRIP001         SdrGlueEditView::TakeActionRect(rRect);
//STRIP001     }
//STRIP001 }

/*N*/ void __EXPORT SdrObjEditView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/     SdrGlueEditView::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/     // Printerwechsel waerend des Editierens
/*N*/     SdrHint* pSdrHint=PTR_CAST(SdrHint,&rHint);
/*N*/     if (pSdrHint!=NULL && pTextEditOutliner!=NULL) {
/*?*/         SdrHintKind eKind=pSdrHint->GetKind();
/*?*/         if (eKind==HINT_REFDEVICECHG) {
/*?*/             pTextEditOutliner->SetRefDevice(pMod->GetRefDevice());
/*?*/         }
/*?*/         if (eKind==HINT_DEFAULTTABCHG) {
/*?*/             pTextEditOutliner->SetDefTab(pMod->GetDefaultTabulator());
/*?*/         }
/*?*/         if (eKind==HINT_DEFFONTHGTCHG) {
/*?*/             // ...
/*?*/         }
/*?*/         if (eKind==HINT_MODELSAVED) { // #43095#
/*?*/             DBG_ASSERT(0, "STRIP"); //STRIP001 pTextEditOutliner->ClearModifyFlag();
/*?*/         }
/*N*/     }
/*N*/ }

/*N*/ void SdrObjEditView::ModelHasChanged()
/*N*/ {
/*N*/     SdrGlueEditView::ModelHasChanged();
/*N*/     if (IsTextEdit() && !pTextEditObj->IsInserted()) {DBG_ASSERT(0, "STRIP"); }//STRIP001 EndTextEdit(); // Objekt geloescht
/*N*/     // TextEditObj geaendert?
/*N*/     if (IsTextEdit()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001 /*?*/         if (pTextObj!=NULL) {
//STRIP001 /*?*/             ULONG nOutlViewAnz=pTextEditOutliner->GetViewCount();
//STRIP001 /*?*/             BOOL bAreaChg=FALSE;
//STRIP001 /*?*/             BOOL bAnchorChg=FALSE;
//STRIP001 /*?*/             BOOL bColorChg=FALSE;
//STRIP001 /*?*/             BOOL bContourFrame=pTextObj->IsContourTextFrame();
//STRIP001 /*?*/             EVAnchorMode eNewAnchor;
//STRIP001 /*?*/             Rectangle aOldArea(aMinTextEditArea);
//STRIP001 /*?*/             aOldArea.Union(aTextEditArea);
//STRIP001 /*?*/             Color aNewColor;
//STRIP001 /*?*/             { // Area Checken
//STRIP001 /*?*/                 Size aPaperMin1;
//STRIP001 /*?*/                 Size aPaperMax1;
//STRIP001 /*?*/                 Rectangle aEditArea1;
//STRIP001 /*?*/                 Rectangle aMinArea1;
//STRIP001 /*?*/                 pTextObj->TakeTextEditArea(&aPaperMin1,&aPaperMax1,&aEditArea1,&aMinArea1);
//STRIP001 /*?*/                 Point aPvOfs(pTextEditPV->GetOffset());
//STRIP001 /*?*/
//STRIP001 /*?*/                // #108784#
//STRIP001 /*?*/                aPvOfs += pTextObj->GetTextEditOffset();
//STRIP001 /*?*/
//STRIP001 /*?*/                 aEditArea1.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001 /*?*/                 aMinArea1.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001 /*?*/                 Rectangle aNewArea(aMinArea1);
//STRIP001 /*?*/                 aNewArea.Union(aEditArea1);
//STRIP001 /*?*/                 if (aNewArea!=aOldArea || aEditArea1!=aTextEditArea || aMinArea1!=aMinTextEditArea ||
//STRIP001 /*?*/                     pTextEditOutliner->GetMinAutoPaperSize()!=aPaperMin1 || pTextEditOutliner->GetMaxAutoPaperSize()!=aPaperMax1) {
//STRIP001 /*?*/                     aTextEditArea=aEditArea1;
//STRIP001 /*?*/                     aMinTextEditArea=aMinArea1;
//STRIP001 /*?*/                     pTextEditOutliner->SetUpdateMode(FALSE);
//STRIP001 /*?*/                     pTextEditOutliner->SetMinAutoPaperSize(aPaperMin1);
//STRIP001 /*?*/                     pTextEditOutliner->SetMaxAutoPaperSize(aPaperMax1);
//STRIP001 /*?*/                     pTextEditOutliner->SetPaperSize(Size(0,0)); // Damit der Outliner neu formatiert
//STRIP001 /*?*/                     if (!bContourFrame) {
//STRIP001 /*?*/                         pTextEditOutliner->ClearPolygon();
//STRIP001 /*?*/                         ULONG nStat=pTextEditOutliner->GetControlWord();
//STRIP001 /*?*/                         nStat|=EE_CNTRL_AUTOPAGESIZE;
//STRIP001 /*?*/                         pTextEditOutliner->SetControlWord(nStat);
//STRIP001 /*?*/                     } else {
//STRIP001 /*?*/                         ULONG nStat=pTextEditOutliner->GetControlWord();
//STRIP001 /*?*/                         nStat&=~EE_CNTRL_AUTOPAGESIZE;
//STRIP001 /*?*/                         pTextEditOutliner->SetControlWord(nStat);
//STRIP001 /*?*/                         Rectangle aAnchorRect;
//STRIP001 /*?*/                         pTextObj->TakeTextAnchorRect(aAnchorRect);
//STRIP001 /*?*/                         pTextObj->ImpSetContourPolygon(*pTextEditOutliner,aAnchorRect, TRUE);
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     for (ULONG nOV=0; nOV<nOutlViewAnz; nOV++) {
//STRIP001 /*?*/                         OutlinerView* pOLV=pTextEditOutliner->GetView(nOV);
//STRIP001 /*?*/                         ULONG nStat0=pOLV->GetControlWord();
//STRIP001 /*?*/                         ULONG nStat=nStat0;
//STRIP001 /*?*/                         // AutoViewSize nur wenn nicht KontourFrame.
//STRIP001 /*?*/                         if (!bContourFrame) nStat|=EV_CNTRL_AUTOSIZE;
//STRIP001 /*?*/                         else nStat&=~EV_CNTRL_AUTOSIZE;
//STRIP001 /*?*/                         if (nStat!=nStat0) pOLV->SetControlWord(nStat);
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     pTextEditOutliner->SetUpdateMode(TRUE);
//STRIP001 /*?*/                     bAreaChg=TRUE;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/             if (pTextEditOutlinerView!=NULL) { // Fuellfarbe und Anker checken
//STRIP001 /*?*/                 EVAnchorMode eOldAnchor=pTextEditOutlinerView->GetAnchorMode();
//STRIP001 /*?*/                 eNewAnchor=(EVAnchorMode)pTextObj->GetOutlinerViewAnchorMode();
//STRIP001 /*?*/                 bAnchorChg=eOldAnchor!=eNewAnchor;
//STRIP001 /*?*/                 Color aOldColor(pTextEditOutlinerView->GetBackgroundColor());
//STRIP001 /*?*/                 aNewColor=ImpGetTextEditBackgroundColor();
//STRIP001 /*?*/                 bColorChg=aOldColor!=aNewColor;
//STRIP001 /*?*/             }
//STRIP001 /*?*/            // #104082# refresh always when it's a contour frame. That
//STRIP001 /*?*/            // refresh is necessary since it triggers the repaint
//STRIP001 /*?*/            // which makes the Handles visible. Changes at TakeTextRect()
//STRIP001 /*?*/            // seem to have resulted in a case where no refresh is executed.
//STRIP001 /*?*/            // Before that, a refresh must have been always executed
//STRIP001 /*?*/            // (else this error would have happend earlier), thus i
//STRIP001 /*?*/            // even think here a refresh should be done always.
//STRIP001 /*?*/            // Since follow-up problems cannot even be guessed I only
//STRIP001 /*?*/            // add this one more case to the if below.
//STRIP001 /*?*/            // BTW: It's VERY bad style that here, inside ModelHasChanged()
//STRIP001 /*?*/            // the outliner is again massively changed for the text object
//STRIP001 /*?*/            // in text edit mode. Normally, all necessary data should be
//STRIP001 /*?*/            // set at BeginTextEdit(). Some changes and value assigns in
//STRIP001 /*?*/            // BeginTextEdit() are completely useless since they are set here
//STRIP001 /*?*/            // again on ModelHasChanged().
//STRIP001 /*?*/             if (bContourFrame || bAreaChg || bAnchorChg || bColorChg)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 for (ULONG nOV=0; nOV<nOutlViewAnz; nOV++)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                     OutlinerView* pOLV=pTextEditOutliner->GetView(nOV);
//STRIP001 /*?*/                     { // Alten OutlinerView-Bereich invalidieren
//STRIP001 /*?*/                         Window* pWin=pOLV->GetWindow();
//STRIP001 /*?*/                         Rectangle aTmpRect(aOldArea);
//STRIP001 /*?*/                         USHORT nPixSiz=pOLV->GetInvalidateMore()+1;
//STRIP001 /*?*/                         Size aMore(pWin->PixelToLogic(Size(nPixSiz,nPixSiz)));
//STRIP001 /*?*/                         aTmpRect.Left()-=aMore.Width();
//STRIP001 /*?*/                         aTmpRect.Right()+=aMore.Width();
//STRIP001 /*?*/                         aTmpRect.Top()-=aMore.Height();
//STRIP001 /*?*/                         aTmpRect.Bottom()+=aMore.Height();
//STRIP001 /*?*/                         InvalidateOneWin(*pWin,aTmpRect);
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     if (bAnchorChg)
//STRIP001 /*?*/                        pOLV->SetAnchorMode(eNewAnchor);
//STRIP001 /*?*/                     if (bColorChg)
//STRIP001 /*?*/                        pOLV->SetBackgroundColor( aNewColor );
//STRIP001 /*?*/
//STRIP001 /*?*/                    pOLV->SetOutputArea(aTextEditArea); // weil sonst scheinbar nicht richtig umgeankert wird
//STRIP001 /*?*/                     ImpPaintOutlinerView(*pOLV);
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 pTextEditOutlinerView->ShowCursor();
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
//STRIP001 /*?*/         ImpMakeTextCursorAreaVisible();
/*N*/     }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@@ @@@@@ @@   @@ @@@@@@  @@@@@ @@@@@  @@ @@@@@@
//    @@   @@    @@@ @@@   @@    @@    @@  @@ @@   @@
//    @@   @@     @@@@@    @@    @@    @@  @@ @@   @@
//    @@   @@@@    @@@     @@    @@@@  @@  @@ @@   @@
//    @@   @@     @@@@@    @@    @@    @@  @@ @@   @@
//    @@   @@    @@@ @@@   @@    @@    @@  @@ @@   @@
//    @@   @@@@@ @@   @@   @@    @@@@@ @@@@@  @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrObjEditView::ImpPaintOutlinerView(OutlinerView& rOutlView, const Rectangle* pRect, BOOL bDrawButPaint) const
//STRIP001 {
//STRIP001     const SdrObject* pTextObjTmp=GetTextEditObject();
//STRIP001     const SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextObjTmp);
//STRIP001     BOOL bTextFrame=pText!=NULL && pText->IsTextFrame();
//STRIP001     BOOL bFitToSize=(pTextEditOutliner->GetControlWord() & EE_CNTRL_STRETCHING) !=0;
//STRIP001     BOOL bContourFrame=pText!=NULL && pText->IsContourTextFrame();
//STRIP001     Window* pWin=rOutlView.GetWindow();
//STRIP001     Rectangle aBlankRect(rOutlView.GetOutputArea());
//STRIP001     aBlankRect.Union(aMinTextEditArea);
//STRIP001     Rectangle aPixRect(pWin->LogicToPixel(aBlankRect));
//STRIP001     if (pRect!=NULL) aBlankRect.Intersection(*pRect);
//STRIP001     BOOL bModifyMerk=pTextEditOutliner->IsModified(); // #43095#
//STRIP001     if (bDrawButPaint) {
//STRIP001         pTextEditOutliner->Draw(pWin,rOutlView.GetOutputArea());
//STRIP001     } else {
//STRIP001         rOutlView.GetOutliner()->SetUpdateMode(TRUE); // Bugfix #22596#
//STRIP001         rOutlView.Paint(aBlankRect);
//STRIP001     }
//STRIP001     if (!bModifyMerk) pTextEditOutliner->ClearModifyFlag(); // #43095#
//STRIP001     if (bTextFrame && !bFitToSize) {
//STRIP001         aPixRect.Left()--;
//STRIP001         aPixRect.Top()--;
//STRIP001         aPixRect.Right()++;
//STRIP001         aPixRect.Bottom()++;
//STRIP001         USHORT nPixSiz=rOutlView.GetInvalidateMore()-1;
//STRIP001         { // xPixRect Begrenzen, wegen Treiberproblem bei zu weit hinausragenden Pixelkoordinaten
//STRIP001             Size aMaxXY=pWin->GetOutputSizePixel();
//STRIP001             long a=2*nPixSiz;
//STRIP001             long nMaxX=aMaxXY.Width()+a;
//STRIP001             long nMaxY=aMaxXY.Height()+a;
//STRIP001             if (aPixRect.Left  ()<-a) aPixRect.Left()=-a;
//STRIP001             if (aPixRect.Top   ()<-a) aPixRect.Top ()=-a;
//STRIP001             if (aPixRect.Right ()>nMaxX) aPixRect.Right ()=nMaxX;
//STRIP001             if (aPixRect.Bottom()>nMaxY) aPixRect.Bottom()=nMaxY;
//STRIP001         }
//STRIP001         Rectangle aOuterPix(aPixRect);
//STRIP001         aOuterPix.Left()-=nPixSiz;
//STRIP001         aOuterPix.Top()-=nPixSiz;
//STRIP001         aOuterPix.Right()+=nPixSiz;
//STRIP001         aOuterPix.Bottom()+=nPixSiz;
//STRIP001
//STRIP001         BOOL bXor=(bDrawButPaint && IsShownXorVisible(pWin));
//STRIP001         if (bXor) ((SdrPaintView*)this)->HideShownXor(pWin);
//STRIP001         BOOL bMerk=pWin->IsMapModeEnabled();
//STRIP001         pWin->EnableMapMode(FALSE);
//STRIP001
//STRIP001         PolyPolygon aPolyPoly( 2 );
//STRIP001
//STRIP001      svtools::ColorConfig aColorConfig;
//STRIP001      Color aHatchCol( aColorConfig.GetColorValue( svtools::FONTCOLOR ).nColor );
//STRIP001         const Hatch aHatch( HATCH_SINGLE, aHatchCol, 3, 450 );
//STRIP001
//STRIP001         aPolyPoly.Insert( aOuterPix );
//STRIP001         aPolyPoly.Insert( aPixRect );
//STRIP001         pWin->DrawHatch( aPolyPoly, aHatch );
//STRIP001
//STRIP001         pWin->EnableMapMode(bMerk);
//STRIP001         if (bXor) ((SdrPaintView*)this)->ShowShownXor(pWin);
//STRIP001     }
//STRIP001     rOutlView.ShowCursor();
//STRIP001 }

//STRIP001 Color SdrObjEditView::ImpGetTextEditBackgroundColor() const
//STRIP001 {
//STRIP001     // #108759# Extracted significant parts to SdrPaintView::CalcBackgroundColor()
//STRIP001     svtools::ColorConfig aColorConfig;
//STRIP001     Color aBackground(aColorConfig.GetColorValue(svtools::DOCCOLOR).nColor);
//STRIP001
//STRIP001  // #98988# test if we are in High contrast mode; if yes, take
//STRIP001  // application background color
//STRIP001     // #10049# wrong, always use svtools::DOCCOLOR as default and use document settings if
//STRIP001  //         not hc mode
//STRIP001  const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
//STRIP001
//STRIP001  if(!rStyleSettings.GetHighContrastMode())
//STRIP001  {
//STRIP001      BOOL bFound=FALSE;
//STRIP001      SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001      if (pText!=NULL && pText->IsClosedObj())
//STRIP001      {
//STRIP001          bFound=GetDraftFillColor(pText->GetItemSet(),aBackground);
//STRIP001      }
//STRIP001      if (!bFound && pTextEditPV!=NULL && pTextEditObj!=NULL)
//STRIP001      {
//STRIP001             Point aPvOfs(pTextEditPV->GetOffset());
//STRIP001
//STRIP001          // #108784#
//STRIP001          aPvOfs += ((SdrTextObj*)pTextEditObj)->GetTextEditOffset();
//STRIP001
//STRIP001          const SdrPage* pPg=pTextEditPV->GetPage();
//STRIP001             Rectangle aSnapRect( pTextEditObj->GetSnapRect() );
//STRIP001             aSnapRect.Move(aPvOfs.X(), aPvOfs.Y());
//STRIP001
//STRIP001             return CalcBackgroundColor( aSnapRect, pTextEditPV->GetVisibleLayers(), *pPg );
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return aBackground;
//STRIP001 }

//STRIP001 OutlinerView* SdrObjEditView::ImpMakeOutlinerView(Window* pWin, BOOL bNoPaint, OutlinerView* pGivenView) const
//STRIP001 {
//STRIP001     // Hintergrund
//STRIP001     Color aBackground(ImpGetTextEditBackgroundColor());
//STRIP001     SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001     BOOL bTextFrame=pText!=NULL && pText->IsTextFrame();
//STRIP001     BOOL bContourFrame=pText!=NULL && pText->IsContourTextFrame();
//STRIP001     // OutlinerView erzeugen
//STRIP001     OutlinerView* pOutlView=pGivenView;
//STRIP001     pTextEditOutliner->SetUpdateMode(FALSE);
//STRIP001     if (pOutlView==NULL) pOutlView=new OutlinerView(pTextEditOutliner,pWin);
//STRIP001     else pOutlView->SetWindow(pWin);
//STRIP001     // Scrollen verbieten
//STRIP001     ULONG nStat=pOutlView->GetControlWord();
//STRIP001     nStat&=~EV_CNTRL_AUTOSCROLL;
//STRIP001     // AutoViewSize nur wenn nicht KontourFrame.
//STRIP001     if (!bContourFrame) nStat|=EV_CNTRL_AUTOSIZE;
//STRIP001     if (bTextFrame) {
//STRIP001         USHORT nPixSiz=aHdl.GetHdlSize()*2+1;
//STRIP001         nStat|=EV_CNTRL_INVONEMORE;
//STRIP001         pOutlView->SetInvalidateMore(nPixSiz);
//STRIP001     }
//STRIP001     pOutlView->SetControlWord(nStat);
//STRIP001     pOutlView->SetBackgroundColor( aBackground );
//STRIP001     if (pText!=NULL) {
//STRIP001         pOutlView->SetAnchorMode((EVAnchorMode)(pText->GetOutlinerViewAnchorMode()));
//STRIP001     }
//STRIP001     pOutlView->SetOutputArea(aTextEditArea);
//STRIP001     pTextEditOutliner->SetUpdateMode(TRUE);
//STRIP001     ImpPaintOutlinerView(*pOutlView,NULL,TRUE);
//STRIP001     return pOutlView;
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::IsTextEditFrame() const
//STRIP001 {
//STRIP001     SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001     return pText!=NULL && pText->IsTextFrame();
//STRIP001 }

//STRIP001 IMPL_LINK(SdrObjEditView,ImpOutlinerStatusEventHdl,EditStatus*,pEditStat)
//STRIP001 {
//STRIP001     if (pTextEditOutliner==NULL || pTextEditObj==NULL) return 0;
//STRIP001     ULONG nStat=pEditStat->GetStatusWord();
//STRIP001     BOOL bGrowX=(nStat & EE_STAT_TEXTWIDTHCHANGED) !=0;
//STRIP001     BOOL bGrowY=(nStat & EE_STAT_TEXTHEIGHTCHANGED) !=0;
//STRIP001     SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001     BOOL bTextFrame=pTextObj!=NULL && pTextObj->IsTextFrame();
//STRIP001     if (!bTextFrame || (!bGrowX && !bGrowY)) return 0;
//STRIP001     BOOL bAutoGrowHgt=bTextFrame && pTextObj->IsAutoGrowHeight();
//STRIP001     BOOL bAutoGrowWdt=bTextFrame && pTextObj->IsAutoGrowWidth();
//STRIP001
//STRIP001     if ((bGrowX && bAutoGrowWdt) || (bGrowY && bAutoGrowHgt)) {
//STRIP001         if (pTextObj->AdjustTextFrameWidthAndHeight()) {
//STRIP001         }
//STRIP001     }
//STRIP001     return 0;
//STRIP001 }

//STRIP001 IMPL_LINK(SdrObjEditView,ImpOutlinerCalcFieldValueHdl,EditFieldInfo*,pFI)
//STRIP001 {
//STRIP001     BOOL bOk=FALSE;
//STRIP001     String& rStr=pFI->GetRepresentation();
//STRIP001     rStr.Erase();
//STRIP001     SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001     if (pTextObj!=NULL) {
//STRIP001         Color* pTxtCol=NULL;
//STRIP001         Color* pFldCol=NULL;
//STRIP001         bOk=pTextObj->CalcFieldValue(pFI->GetField(),pFI->GetPara(),pFI->GetPos(),TRUE,pTxtCol,pFldCol,rStr);
//STRIP001         if (bOk) {
//STRIP001             if (pTxtCol!=NULL) {
//STRIP001                 pFI->SetTxtColor(*pTxtCol);
//STRIP001                 delete pTxtCol;
//STRIP001             }
//STRIP001             if (pFldCol!=NULL) {
//STRIP001                 pFI->SetFldColor(*pFldCol);
//STRIP001                 delete pFldCol;
//STRIP001             } else {
//STRIP001                 pFI->SetFldColor(Color(COL_LIGHTGRAY)); // kann spaeter (357) raus
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     Outliner& rDrawOutl=pMod->GetDrawOutliner(pTextObj);
//STRIP001     Link aDrawOutlLink=rDrawOutl.GetCalcFieldValueHdl();
//STRIP001     if (!bOk && aDrawOutlLink.IsSet()) {
//STRIP001         aDrawOutlLink.Call(pFI);
//STRIP001         bOk = (BOOL)rStr.Len();
//STRIP001     }
//STRIP001     if (!bOk && aOldCalcFieldValueLink.IsSet()) {
//STRIP001         return aOldCalcFieldValueLink.Call(pFI);
//STRIP001     }
//STRIP001     return 0;
//STRIP001 }

/*N*/ BOOL SdrObjEditView::BegTextEdit(SdrObject* pObj, SdrPageView* pPV, Window* pWin,
/*N*/   SdrOutliner* pGivenOutliner, OutlinerView* pGivenOutlinerView,
/*N*/   BOOL bDontDeleteOutliner, BOOL bOnlyOneView)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     return BegTextEdit(pObj,pPV,pWin,FALSE,pGivenOutliner,pGivenOutlinerView,bDontDeleteOutliner,bOnlyOneView);
/*N*/ }

/*N*/ BOOL SdrObjEditView::BegTextEdit(SdrObject* pObj, SdrPageView* pPV, Window* pWin, BOOL bIsNewObj,
/*N*/   SdrOutliner* pGivenOutliner, OutlinerView* pGivenOutlinerView,
/*N*/   BOOL bDontDeleteOutliner, BOOL bOnlyOneView)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     EndTextEdit();
//STRIP001     if (!HAS_BASE(SdrTextObj,pObj)) return FALSE; // z.Zt. nur mit meinen Textobjekten
//STRIP001     bTextEditDontDelete=bDontDeleteOutliner && pGivenOutliner!=NULL;
//STRIP001     bTextEditOnlyOneView=bOnlyOneView;
//STRIP001     bTextEditNewObj=bIsNewObj;
//STRIP001     USHORT nWinAnz=GetWinCount();
//STRIP001     USHORT i;
//STRIP001     BOOL bBrk=FALSE;
//STRIP001     // Abbruch, wenn kein Objekt angegeben.
//STRIP001     if (pObj==NULL) bBrk=TRUE;
//STRIP001     if (!bBrk && pWin==NULL) {
//STRIP001         for (i=0; i<nWinAnz && pWin==NULL; i++) {
//STRIP001             OutputDevice* pOut=GetWin(i);
//STRIP001             if (pOut->GetOutDevType()==OUTDEV_WINDOW) pWin=(Window*)pOut;
//STRIP001         }
//STRIP001         // Abbruch, wenn kein Window da.
//STRIP001         if (pWin==NULL) bBrk=TRUE;
//STRIP001     }
//STRIP001     if (!bBrk && pPV==NULL) {
//STRIP001         SdrPage* pPage=pObj->GetPage();
//STRIP001         pPV=GetPageView(pPage);
//STRIP001         // Abbruch, wenn keine PageView zu dem Objekt vorhanden.
//STRIP001         if (pPV==NULL) bBrk=TRUE;
//STRIP001     }
//STRIP001     if (pObj!=NULL && pPV!=NULL) {
//STRIP001         // Kein TextEdit an Objekten im gesperrten Layer
//STRIP001         if (pPV->GetLockedLayers().IsSet(pObj->GetLayer())) {
//STRIP001             bBrk=TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if (pTextEditOutliner!=NULL) {
//STRIP001         DBG_ERROR("SdrObjEditView::BegTextEdit() da stand noch ein alter Outliner rum");
//STRIP001         delete pTextEditOutliner;
//STRIP001         pTextEditOutliner=NULL;
//STRIP001     }
//STRIP001
//STRIP001     if (!bBrk) {
//STRIP001         pTextEditWin=pWin;
//STRIP001         pTextEditPV=pPV;
//STRIP001         pTextEditObj=pObj;
//STRIP001         pTextEditOutliner=pGivenOutliner;
//STRIP001         if (pTextEditOutliner==NULL)
//STRIP001          pTextEditOutliner = SdrMakeOutliner( OUTLINERMODE_TEXTOBJECT, pTextEditObj->GetModel() );
//STRIP001
//STRIP001      {
//STRIP001          SvtAccessibilityOptions aOptions;
//STRIP001          pTextEditOutliner->ForceAutoColor( aOptions.GetIsAutomaticFontColor() );
//STRIP001      }
//STRIP001
//STRIP001         BOOL bEmpty=pTextEditObj->GetOutlinerParaObject()==NULL;
//STRIP001
//STRIP001         aOldCalcFieldValueLink=pTextEditOutliner->GetCalcFieldValueHdl();
//STRIP001         // Der FieldHdl muss von BegTextEdit gesetzt sein, da dor ein UpdateFields gerufen wird.
//STRIP001         pTextEditOutliner->SetCalcFieldValueHdl(LINK(this,SdrObjEditView,ImpOutlinerCalcFieldValueHdl));
//STRIP001         if (pTextEditObj->BegTextEdit(*pTextEditOutliner)) {
//STRIP001             // alten Cursor merken
//STRIP001             if (pTextEditOutliner->GetViewCount()!=0) {
//STRIP001                 OutlinerView* pTmpOLV=pTextEditOutliner->RemoveView(ULONG(0));
//STRIP001                 if (pTmpOLV!=NULL && pTmpOLV!=pGivenOutlinerView) delete pTmpOLV;
//STRIP001             }
//STRIP001             // EditArea ueberTakeTextEditArea bestimmen
//STRIP001          // Das koennte eigentlich entfallen, da TakeTextRect() die Berechnung der aTextEditArea vornimmt
//STRIP001          // Die aMinTextEditArea muss jedoch wohl auch erfolgen (darum bleibt es voerst drinnen)
//STRIP001             ((SdrTextObj*)pTextEditObj)->TakeTextEditArea(NULL,NULL,&aTextEditArea,&aMinTextEditArea);
//STRIP001
//STRIP001          Rectangle aTextRect;
//STRIP001          Rectangle aAnchorRect;
//STRIP001          ((SdrTextObj*)pTextEditObj)->TakeTextRect(*pTextEditOutliner, aTextRect, TRUE,
//STRIP001              &aAnchorRect /* #97097# Give TRUE here, not FALSE */);
//STRIP001
//STRIP001          if ( !((SdrTextObj*)pTextEditObj)->IsContourTextFrame() )
//STRIP001          {
//STRIP001              // FitToSize erstmal nicht mit ContourFrame
//STRIP001              SdrFitToSizeType eFit = ((SdrTextObj*)pTextEditObj)->GetFitToSize();
//STRIP001              if (eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES)
//STRIP001                  aTextRect = aAnchorRect;
//STRIP001          }
//STRIP001
//STRIP001          aTextEditArea = aTextRect;
//STRIP001
//STRIP001             Point aPvOfs(pTextEditPV->GetOffset());
//STRIP001
//STRIP001          // #108784#
//STRIP001          aPvOfs += ((SdrTextObj*)pTextEditObj)->GetTextEditOffset();
//STRIP001
//STRIP001          aTextEditArea.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001             aMinTextEditArea.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001             pTextEditCursorMerker=pWin->GetCursor();
//STRIP001
//STRIP001          aHdl.SetMoveOutside(TRUE);
//STRIP001          RefreshAllIAOManagers();
//STRIP001
//STRIP001             pTextEditOutlinerView=ImpMakeOutlinerView(pWin,!bEmpty,pGivenOutlinerView);
//STRIP001             pTextEditOutliner->InsertView(pTextEditOutlinerView,0);
//STRIP001
//STRIP001          aHdl.SetMoveOutside(FALSE);
//STRIP001          aHdl.SetMoveOutside(TRUE);
//STRIP001          RefreshAllIAOManagers();
//STRIP001
//STRIP001             // alle Wins als OutlinerView beim Outliner anmelden
//STRIP001             if (!bOnlyOneView) {
//STRIP001                 for (i=0; i<nWinAnz; i++) {
//STRIP001                     OutputDevice* pOut=GetWin(i);
//STRIP001                     if (pOut!=pWin && pOut->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001                         OutlinerView* pOutlView=ImpMakeOutlinerView((Window*)pOut,!bEmpty,NULL);
//STRIP001                         pTextEditOutliner->InsertView(pOutlView,i);
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             pWin->GrabFocus(); // Damit der Cursor hier auch blinkt
//STRIP001             pTextEditOutlinerView->ShowCursor();
//STRIP001             pTextEditOutliner->SetStatusEventHdl(LINK(this,SdrObjEditView,ImpOutlinerStatusEventHdl));
//STRIP001 #ifndef SVX_LIGHT
//STRIP001             if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001             pTextEditOutliner->ClearModifyFlag();
//STRIP001
//STRIP001          // #71519#, #91453#
//STRIP001          if(pWin)
//STRIP001          {
//STRIP001              sal_Bool bExtraInvalidate(sal_False);
//STRIP001
//STRIP001              // #91453#
//STRIP001              if(!bExtraInvalidate && IsTextDraft())
//STRIP001                  bExtraInvalidate = sal_True;
//STRIP001
//STRIP001              // #71519#
//STRIP001              if(!bExtraInvalidate)
//STRIP001              {
//STRIP001                  SdrFitToSizeType eFit = ((SdrTextObj*)pTextEditObj)->GetFitToSize();
//STRIP001                  if(eFit == SDRTEXTFIT_PROPORTIONAL || eFit == SDRTEXTFIT_ALLLINES)
//STRIP001                      bExtraInvalidate = sal_True;
//STRIP001              }
//STRIP001
//STRIP001              if(bExtraInvalidate)
//STRIP001              {
//STRIP001                  pWin->Invalidate(aTextEditArea);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001             // send HINT_BEGEDIT #99840#
//STRIP001             if( GetModel() )
//STRIP001             {
//STRIP001                 SdrHint aHint(*pTextEditObj);
//STRIP001                 aHint.SetKind(HINT_BEGEDIT);
//STRIP001                 GetModel()->Broadcast(aHint);
//STRIP001             }
//STRIP001
//STRIP001             return TRUE; // Gut gelaufen, TextEdit laeuft nun
//STRIP001         } else {
//STRIP001             bBrk=TRUE;
//STRIP001             pTextEditOutliner->SetCalcFieldValueHdl(aOldCalcFieldValueLink);
//STRIP001         }
//STRIP001     }
//STRIP001     // wenn hier angekommen, dann ist irgendwas schief gelaufen
//STRIP001     if (!bDontDeleteOutliner) {
//STRIP001         if (pGivenOutliner!=NULL) { delete pGivenOutliner; pTextEditOutliner=NULL; }
//STRIP001         if (pGivenOutlinerView!=NULL) delete pGivenOutlinerView;
//STRIP001     }
//STRIP001     if (pTextEditOutliner!=NULL) delete pTextEditOutliner;
//STRIP001     pTextEditOutliner=NULL;
//STRIP001     pTextEditOutlinerView=NULL;
//STRIP001     pTextEditObj=NULL;
//STRIP001     pTextEditPV=NULL;
//STRIP001     pTextEditWin=NULL;
//STRIP001     if (bMarkHdlWhenTextEdit) {
//STRIP001         HideMarkHdl(NULL);
//STRIP001     }
//STRIP001     aHdl.SetMoveOutside(FALSE);
//STRIP001  RefreshAllIAOManagers();
//STRIP001     ShowMarkHdl(NULL);
//STRIP001     return FALSE;
/*N*/ }

/*N*/ SdrEndTextEditKind SdrObjEditView::EndTextEdit(BOOL bDontDeleteReally)
/*N*/ {DBG_ASSERT(0, "STRIP");SdrEndTextEditKind eRet=SDRENDTEXTEDIT_UNCHANGED; return eRet; //STRIP001
//STRIP001     SdrEndTextEditKind eRet=SDRENDTEXTEDIT_UNCHANGED;
//STRIP001     SdrObject*    pTEObj         =pTextEditObj;
//STRIP001     SdrPageView*  pTEPV          =pTextEditPV;
//STRIP001     Window*       pTEWin         =pTextEditWin;
//STRIP001     SdrOutliner*  pTEOutliner    =pTextEditOutliner;
//STRIP001     OutlinerView* pTEOutlinerView=pTextEditOutlinerView;
//STRIP001     Cursor*       pTECursorMerker=pTextEditCursorMerker;
//STRIP001
//STRIP001     // send HINT_ENDEDIT #99840#
//STRIP001     if( GetModel() && pTextEditObj )
//STRIP001     {
//STRIP001         SdrHint aHint(*pTextEditObj);
//STRIP001         aHint.SetKind(HINT_ENDEDIT);
//STRIP001         GetModel()->Broadcast(aHint);
//STRIP001     }
//STRIP001
//STRIP001     pTextEditObj=NULL;
//STRIP001     pTextEditPV=NULL;
//STRIP001     pTextEditWin=NULL;
//STRIP001     pTextEditOutliner=NULL;
//STRIP001     pTextEditOutlinerView=NULL;
//STRIP001     pTextEditCursorMerker=NULL;
//STRIP001     aTextEditArea=Rectangle();
//STRIP001
//STRIP001     if (pTEOutliner!=NULL) {
//STRIP001         BOOL bModified=pTEOutliner->IsModified();
//STRIP001         if (pTEOutlinerView!=NULL)
//STRIP001      {
//STRIP001          // #102524# After long discussion ProdMan decided not to do a
//STRIP001          // AutoCorrect when leaving Text edit mode. It's a feature, not
//STRIP001          // a bug. I comment it out.
//STRIP001             // pTEOutlinerView->CompleteAutoCorrect(); // #43095#
//STRIP001             pTEOutlinerView->HideCursor();
//STRIP001         }
//STRIP001         if (pTEObj!=NULL) {
//STRIP001             pTEOutliner->CompleteOnlineSpelling();
//STRIP001             Point aPvOfs(pTEPV->GetOffset());
//STRIP001             SdrUndoObjSetText* pTxtUndo=bModified ? new SdrUndoObjSetText(*pTEObj) : NULL;
//STRIP001             // Den alten CalcFieldValue-Handler wieder setzen
//STRIP001             // Muss vor Obj::EndTextEdit() geschehen, da dort ein UpdateFields() gemacht wird.
//STRIP001             pTEOutliner->SetCalcFieldValueHdl(aOldCalcFieldValueLink);
//STRIP001
//STRIP001             pTEObj->EndTextEdit(*pTEOutliner);
//STRIP001
//STRIP001          if ( pTEObj->GetRotateAngle() != 0 )
//STRIP001              pTEObj->SendRepaintBroadcast();  // Sonst wird nicht alles restauriert
//STRIP001
//STRIP001          // #90468# invalidate here for FontWork object to force complete redraw
//STRIP001          if(pTEObj && pTEObj->ISA(SdrTextObj) && ((SdrTextObj*)pTEObj)->IsFontwork())
//STRIP001          {
//STRIP001              pTEObj->SendRepaintBroadcast();
//STRIP001          }
//STRIP001
//STRIP001             if (pTxtUndo!=NULL) {
//STRIP001                 pTxtUndo->AfterSetText();
//STRIP001                 if (!pTxtUndo->IsDifferent()) { delete pTxtUndo; pTxtUndo=NULL; }
//STRIP001             }
//STRIP001             // Loeschung des gesamten TextObj checken
//STRIP001             SdrUndoDelObj* pDelUndo=NULL;
//STRIP001             BOOL bDelObj=FALSE;
//STRIP001             SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pTEObj);
//STRIP001             if (pTextObj!=NULL && bTextEditNewObj) {
//STRIP001                 bDelObj=pTextObj->IsTextFrame() &&
//STRIP001                         pTextObj->GetOutlinerParaObject()==NULL &&
//STRIP001                         !pTextObj->IsEmptyPresObj() &&
//STRIP001                         !pTextObj->HasFill() &&
//STRIP001                         !pTextObj->HasLine();
//STRIP001                 if (pTEObj->IsInserted() && bDelObj && pTextObj->GetObjInventor()==SdrInventor && !bDontDeleteReally) {
//STRIP001                     SdrObjKind eIdent=(SdrObjKind)pTextObj->GetObjIdentifier();
//STRIP001                     if (eIdent==OBJ_TEXT || eIdent==OBJ_TEXTEXT) {
//STRIP001                         pDelUndo=new SdrUndoDelObj(*pTEObj);
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             XubString aObjName;
//STRIP001             pTEObj->TakeObjNameSingul(aObjName);
//STRIP001             BegUndo(ImpGetResStr(STR_UndoObjSetText),aObjName);
//STRIP001             if (pTxtUndo!=NULL) { AddUndo(pTxtUndo); eRet=SDRENDTEXTEDIT_CHANGED; }
//STRIP001             if (pDelUndo!=NULL) {
//STRIP001                 AddUndo(pDelUndo);
//STRIP001                 eRet=SDRENDTEXTEDIT_DELETED;
//STRIP001                 DBG_ASSERT(pTEObj->GetObjList()!=NULL,"SdrObjEditView::EndTextEdit(): Fatal: Editiertes Objekt hat keine ObjList!");
//STRIP001                 if (pTEObj->GetObjList()!=NULL) {
//STRIP001                     pTEObj->GetObjList()->RemoveObject(pTEObj->GetOrdNum());
//STRIP001                     CheckMarked(); // und gleich die Maekierung entfernen...
//STRIP001                 }
//STRIP001             } else if (bDelObj) { // Fuer den Writer: Loeschen muss die App nachholen.
//STRIP001                 eRet=SDRENDTEXTEDIT_SHOULDBEDELETED;
//STRIP001             }
//STRIP001             EndUndo(); // EndUndo hinter Remove, falls der UndoStack gleich weggehaun' wird
//STRIP001         }
//STRIP001         // alle OutlinerViews loeschen
//STRIP001         for (ULONG i=pTEOutliner->GetViewCount(); i>0;) {
//STRIP001             i--;
//STRIP001             OutlinerView* pOLV=pTEOutliner->GetView(i);
//STRIP001             USHORT nMorePix=pOLV->GetInvalidateMore();
//STRIP001             Window* pWin=pOLV->GetWindow();
//STRIP001             Rectangle aRect(pOLV->GetOutputArea());
//STRIP001             pTEOutliner->RemoveView(i);
//STRIP001             if (!bTextEditDontDelete || i!=0) {
//STRIP001                 // die nullte gehoert mir u.U. nicht.
//STRIP001                 delete pOLV;
//STRIP001             }
//STRIP001             aRect.Union(aTextEditArea);
//STRIP001             aRect.Union(aMinTextEditArea);
//STRIP001             aRect=pWin->LogicToPixel(aRect);
//STRIP001             aRect.Left()-=nMorePix;
//STRIP001             aRect.Top()-=nMorePix;
//STRIP001             aRect.Right()+=nMorePix;
//STRIP001             aRect.Bottom()+=nMorePix;
//STRIP001             aRect=pWin->PixelToLogic(aRect);
//STRIP001             InvalidateOneWin(*pWin,aRect);
//STRIP001         }
//STRIP001         // und auch den Outliner selbst
//STRIP001         if (!bTextEditDontDelete) delete pTEOutliner;
//STRIP001         else pTEOutliner->Clear();
//STRIP001         if (pTEWin!=NULL) {
//STRIP001             pTEWin->SetCursor(pTECursorMerker);
//STRIP001         }
//STRIP001         if (bMarkHdlWhenTextEdit) {
//STRIP001             HideMarkHdl(NULL);
//STRIP001         }
//STRIP001         aHdl.SetMoveOutside(FALSE);
//STRIP001      RefreshAllIAOManagers();
//STRIP001         if (eRet==SDRENDTEXTEDIT_UNCHANGED) {
//STRIP001             ShowMarkHdl(NULL); // Handles kommen ansonsten via Broadcast
//STRIP001         } else aMark.SetNameDirty();
//STRIP001 #ifndef SVX_LIGHT
//STRIP001         if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001     }
//STRIP001
//STRIP001  // #108784#
//STRIP001  if( pTEObj &&
//STRIP001      pTEObj->GetModel() &&
//STRIP001      !pTEObj->GetModel()->isLocked() &&
//STRIP001      pTEObj->GetBroadcaster())
//STRIP001  {
//STRIP001      SdrHint aHint(HINT_ENDEDIT);
//STRIP001      aHint.SetObject(pTEObj);
//STRIP001      ((SfxBroadcaster*)pTEObj->GetBroadcaster())->Broadcast(aHint);
//STRIP001  }
//STRIP001
//STRIP001  return eRet;
/*N*/ }

//STRIP001 OutlinerView* SdrObjEditView::ImpFindOutlinerView(Window* pWin) const
//STRIP001 {
//STRIP001     if (pWin==NULL) return NULL;
//STRIP001     if (pTextEditOutliner==NULL) return NULL;
//STRIP001     OutlinerView* pNewView=NULL;
//STRIP001     ULONG nWinAnz=pTextEditOutliner->GetViewCount();
//STRIP001     for (ULONG i=0; i<nWinAnz && pNewView==NULL; i++) {
//STRIP001         OutlinerView* pView=pTextEditOutliner->GetView(i);
//STRIP001         if (pView->GetWindow()==pWin) pNewView=pView;
//STRIP001     }
//STRIP001     return pNewView;
//STRIP001 }

//STRIP001 void SdrObjEditView::SetTextEditWin(Window* pWin)
//STRIP001 {
//STRIP001     if (pTextEditObj!=NULL && pWin!=NULL && pWin!=pTextEditWin) {
//STRIP001         OutlinerView* pNewView=ImpFindOutlinerView(pWin);
//STRIP001         if (pNewView!=NULL && pNewView!=pTextEditOutlinerView) {
//STRIP001             if (pTextEditOutlinerView!=NULL) {
//STRIP001                 pTextEditOutlinerView->HideCursor();
//STRIP001             }
//STRIP001             pTextEditOutlinerView=pNewView;
//STRIP001             pTextEditWin=pWin;
//STRIP001             pWin->GrabFocus(); // Damit der Cursor hier auch blinkt
//STRIP001             pNewView->ShowCursor();
//STRIP001             ImpMakeTextCursorAreaVisible();
//STRIP001         }
//STRIP001     }
//STRIP001 }

/*N*/ BOOL SdrObjEditView::IsTextEditHit(const Point& rHit, short nTol) const
/*N*/ {
/*N*/     BOOL bOk=FALSE;
/*N*/     if (pTextEditObj!=NULL) {
/*?*/         nTol=ImpGetHitTolLogic(nTol,NULL);
/*?*/         // nur drittel Toleranz hier, damit die Handles
/*?*/         // noch vernuenftig getroffen werden koennen
/*?*/         nTol=nTol/3;
/*?*/         nTol=0; // Joe am 6.3.1997: Keine Hittoleranz mehr hier
/*?*/         if (!bOk) {
/*?*/             DBG_ASSERT(0, "STRIP"); //STRIP001 Rectangle aEditArea;
//STRIP001 /*?*/             OutlinerView* pOLV=pTextEditOutliner->GetView(0);
//STRIP001 /*?*/             if (pOLV!=NULL) {
//STRIP001 /*?*/                 aEditArea.Union(pOLV->GetOutputArea());
//STRIP001 /*?*/             }
//STRIP001 /*?*/             aEditArea.Left()-=nTol;
//STRIP001 /*?*/             aEditArea.Top()-=nTol;
//STRIP001 /*?*/             aEditArea.Right()+=nTol;
//STRIP001 /*?*/             aEditArea.Bottom()+=nTol;
//STRIP001 /*?*/             bOk=aEditArea.IsInside(rHit);
//STRIP001 /*?*/             if (bOk) { // Nun noch checken, ob auch wirklich Buchstaben getroffen wurden
//STRIP001 /*?*/                 Point aPnt(rHit); aPnt-=aEditArea.TopLeft();
//STRIP001 /*?*/                long nHitTol = 2000;
//STRIP001 /*?*/                OutputDevice* pRef = pTextEditOutliner->GetRefDevice();
//STRIP001 /*?*/                if( pRef )
//STRIP001 /*?*/                    nHitTol = pRef->LogicToLogic( nHitTol, MAP_100TH_MM, pRef->GetMapMode().GetMapUnit() );
//STRIP001 /*?*/
//STRIP001 /*?*/                 bOk = pTextEditOutliner->IsTextPos( aPnt, (sal_uInt16)nHitTol );
//STRIP001 /*?*/             }
/*?*/         }
/*N*/     }
/*N*/     return bOk;
/*N*/ }

/*N*/ BOOL SdrObjEditView::IsTextEditFrameHit(const Point& rHit) const
/*N*/ {
/*N*/     BOOL bOk=FALSE;
/*N*/     if (pTextEditObj!=NULL) {
/*?*/         DBG_ASSERT(0, "STRIP"); //STRIP001 SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextEditObj);
//STRIP001 /*?*/         OutlinerView* pOLV=pTextEditOutliner->GetView(0);
//STRIP001 /*?*/        if( pOLV )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            Window* pWin=pOLV->GetWindow();
//STRIP001 /*?*/            if (pText!=NULL && pText->IsTextFrame() && pOLV!=NULL && pWin!=NULL) {
//STRIP001 /*?*/                USHORT nPixSiz=pOLV->GetInvalidateMore();
//STRIP001 /*?*/                Rectangle aEditArea(aMinTextEditArea);
//STRIP001 /*?*/                aEditArea.Union(pOLV->GetOutputArea());
//STRIP001 /*?*/                if (!aEditArea.IsInside(rHit)) {
//STRIP001 /*?*/                    Size aSiz(pWin->PixelToLogic(Size(nPixSiz,nPixSiz)));
//STRIP001 /*?*/                    aEditArea.Left()-=aSiz.Width();
//STRIP001 /*?*/                    aEditArea.Top()-=aSiz.Height();
//STRIP001 /*?*/                    aEditArea.Right()+=aSiz.Width();
//STRIP001 /*?*/                    aEditArea.Bottom()+=aSiz.Height();
//STRIP001 /*?*/                    bOk=aEditArea.IsInside(rHit);
//STRIP001 /*?*/                }
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
/*N*/     }
/*N*/     return bOk;
/*N*/ }

//STRIP001 void SdrObjEditView::AddTextEditOfs(MouseEvent& rMEvt) const
//STRIP001 {
//STRIP001     if (pTextEditObj!=NULL) {
//STRIP001         Point aPvOfs(pTextEditPV->GetOffset());
//STRIP001
//STRIP001      // #108784#
//STRIP001      aPvOfs += ((SdrTextObj*)pTextEditObj)->GetTextEditOffset();
//STRIP001
//STRIP001      Point aObjOfs(pTextEditObj->GetLogicRect().TopLeft());
//STRIP001         (Point&)(rMEvt.GetPosPixel())+=aPvOfs+aObjOfs;
//STRIP001     }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrObjEditView::KeyInput(const KeyEvent& rKEvt, Window* pWin)
//STRIP001 {
//STRIP001     if(pTextEditOutlinerView)
//STRIP001  {
//STRIP001         if(rKEvt.GetKeyCode().GetCode() == KEY_RETURN && pTextEditOutliner->GetParagraphCount() == 1)
//STRIP001      {
//STRIP001             ByteString aLine(
//STRIP001              pTextEditOutliner->GetText(pTextEditOutliner->GetParagraph( 0 ), 1),
//STRIP001              gsl_getSystemTextEncoding());
//STRIP001             aLine = aLine.ToUpperAscii();
//STRIP001
//STRIP001             if(aLine == "HELLO JOE, PLEASE SHOW THE ITEMBROWSER")
//STRIP001              ShowItemBrowser();
//STRIP001         }
//STRIP001         if (pTextEditOutlinerView->PostKeyEvent(rKEvt))
//STRIP001      {
//STRIP001          if( pMod && !pMod->IsChanged() )
//STRIP001          {
//STRIP001              if( pTextEditOutliner && pTextEditOutliner->IsModified() )
//STRIP001                  pMod->SetChanged( TRUE );
//STRIP001          }
//STRIP001
//STRIP001             if (pWin!=NULL && pWin!=pTextEditWin) SetTextEditWin(pWin);
//STRIP001 #ifndef SVX_LIGHT
//STRIP001             if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001             ImpMakeTextCursorAreaVisible();
//STRIP001             return TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001     return SdrGlueEditView::KeyInput(rKEvt,pWin);
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::MouseButtonDown(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001     if (pTextEditOutlinerView!=NULL) {
//STRIP001         BOOL bPostIt=pTextEditOutliner->IsInSelectionMode();
//STRIP001         if (!bPostIt) {
//STRIP001             Point aPt(rMEvt.GetPosPixel());
//STRIP001             if (pWin!=NULL) aPt=pWin->PixelToLogic(aPt);
//STRIP001             else if (pTextEditWin!=NULL) aPt=pTextEditWin->PixelToLogic(aPt);
//STRIP001             bPostIt=IsTextEditHit(aPt,nHitTolLog);
//STRIP001         }
//STRIP001         if (bPostIt) {
//STRIP001             Point aPixPos(rMEvt.GetPosPixel());
//STRIP001             Rectangle aR(pWin->LogicToPixel(pTextEditOutlinerView->GetOutputArea()));
//STRIP001             if (aPixPos.X()<aR.Left  ()) aPixPos.X()=aR.Left  ();
//STRIP001             if (aPixPos.X()>aR.Right ()) aPixPos.X()=aR.Right ();
//STRIP001             if (aPixPos.Y()<aR.Top   ()) aPixPos.Y()=aR.Top   ();
//STRIP001             if (aPixPos.Y()>aR.Bottom()) aPixPos.Y()=aR.Bottom();
//STRIP001             MouseEvent aMEvt(aPixPos,rMEvt.GetClicks(),rMEvt.GetMode(),
//STRIP001                              rMEvt.GetButtons(),rMEvt.GetModifier());
//STRIP001             if (pTextEditOutlinerView->MouseButtonDown(aMEvt)) {
//STRIP001                 if (pWin!=NULL && pWin!=pTextEditWin) SetTextEditWin(pWin);
//STRIP001 #ifndef SVX_LIGHT
//STRIP001                 if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001                 ImpMakeTextCursorAreaVisible();
//STRIP001                 return TRUE;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return SdrGlueEditView::MouseButtonDown(rMEvt,pWin);
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::MouseButtonUp(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001     if (pTextEditOutlinerView!=NULL) {
//STRIP001         BOOL bPostIt=pTextEditOutliner->IsInSelectionMode();
//STRIP001         if (!bPostIt) {
//STRIP001             Point aPt(rMEvt.GetPosPixel());
//STRIP001             if (pWin!=NULL) aPt=pWin->PixelToLogic(aPt);
//STRIP001             else if (pTextEditWin!=NULL) aPt=pTextEditWin->PixelToLogic(aPt);
//STRIP001             bPostIt=IsTextEditHit(aPt,nHitTolLog);
//STRIP001         }
//STRIP001         if (bPostIt) {
//STRIP001             Point aPixPos(rMEvt.GetPosPixel());
//STRIP001             Rectangle aR(pWin->LogicToPixel(pTextEditOutlinerView->GetOutputArea()));
//STRIP001             if (aPixPos.X()<aR.Left  ()) aPixPos.X()=aR.Left  ();
//STRIP001             if (aPixPos.X()>aR.Right ()) aPixPos.X()=aR.Right ();
//STRIP001             if (aPixPos.Y()<aR.Top   ()) aPixPos.Y()=aR.Top   ();
//STRIP001             if (aPixPos.Y()>aR.Bottom()) aPixPos.Y()=aR.Bottom();
//STRIP001             MouseEvent aMEvt(aPixPos,rMEvt.GetClicks(),rMEvt.GetMode(),
//STRIP001                              rMEvt.GetButtons(),rMEvt.GetModifier());
//STRIP001             if (pTextEditOutlinerView->MouseButtonUp(aMEvt)) {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001                 if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001                 ImpMakeTextCursorAreaVisible();
//STRIP001                 return TRUE;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return SdrGlueEditView::MouseButtonUp(rMEvt,pWin);
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::MouseMove(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001     if (pTextEditOutlinerView!=NULL) {
//STRIP001         BOOL bSelMode=pTextEditOutliner->IsInSelectionMode();
//STRIP001         BOOL bPostIt=bSelMode;
//STRIP001         if (!bPostIt) {
//STRIP001             Point aPt(rMEvt.GetPosPixel());
//STRIP001             if (pWin!=NULL) aPt=pWin->PixelToLogic(aPt);
//STRIP001             else if (pTextEditWin!=NULL) aPt=pTextEditWin->PixelToLogic(aPt);
//STRIP001             bPostIt=IsTextEditHit(aPt,nHitTolLog);
//STRIP001         }
//STRIP001         if (bPostIt) {
//STRIP001             Point aPixPos(rMEvt.GetPosPixel());
//STRIP001             Rectangle aR(pWin->LogicToPixel(pTextEditOutlinerView->GetOutputArea()));
//STRIP001             if (aPixPos.X()<aR.Left  ()) aPixPos.X()=aR.Left  ();
//STRIP001             if (aPixPos.X()>aR.Right ()) aPixPos.X()=aR.Right ();
//STRIP001             if (aPixPos.Y()<aR.Top   ()) aPixPos.Y()=aR.Top   ();
//STRIP001             if (aPixPos.Y()>aR.Bottom()) aPixPos.Y()=aR.Bottom();
//STRIP001             MouseEvent aMEvt(aPixPos,rMEvt.GetClicks(),rMEvt.GetMode(),
//STRIP001                              rMEvt.GetButtons(),rMEvt.GetModifier());
//STRIP001             if (pTextEditOutlinerView->MouseMove(aMEvt) && bSelMode) {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001                 if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001                 ImpMakeTextCursorAreaVisible();
//STRIP001                 return TRUE;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return SdrGlueEditView::MouseMove(rMEvt,pWin);
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::Command(const CommandEvent& rCEvt, Window* pWin)
//STRIP001 {
//STRIP001     // solange bis die OutlinerView einen BOOL zurueckliefert
//STRIP001     // bekommt sie nur COMMAND_STARTDRAG
//STRIP001     if (pTextEditOutlinerView!=NULL)
//STRIP001  {
//STRIP001      if (rCEvt.GetCommand()==COMMAND_STARTDRAG) {
//STRIP001          BOOL bPostIt=pTextEditOutliner->IsInSelectionMode() || !rCEvt.IsMouseEvent();
//STRIP001          if (!bPostIt && rCEvt.IsMouseEvent()) {
//STRIP001              Point aPt(rCEvt.GetMousePosPixel());
//STRIP001              if (pWin!=NULL) aPt=pWin->PixelToLogic(aPt);
//STRIP001              else if (pTextEditWin!=NULL) aPt=pTextEditWin->PixelToLogic(aPt);
//STRIP001              bPostIt=IsTextEditHit(aPt,nHitTolLog);
//STRIP001          }
//STRIP001          if (bPostIt) {
//STRIP001              Point aPixPos(rCEvt.GetMousePosPixel());
//STRIP001              if (rCEvt.IsMouseEvent()) {
//STRIP001                  Rectangle aR(pWin->LogicToPixel(pTextEditOutlinerView->GetOutputArea()));
//STRIP001                  if (aPixPos.X()<aR.Left  ()) aPixPos.X()=aR.Left  ();
//STRIP001                  if (aPixPos.X()>aR.Right ()) aPixPos.X()=aR.Right ();
//STRIP001                  if (aPixPos.Y()<aR.Top   ()) aPixPos.Y()=aR.Top   ();
//STRIP001                  if (aPixPos.Y()>aR.Bottom()) aPixPos.Y()=aR.Bottom();
//STRIP001              }
//STRIP001              CommandEvent aCEvt(aPixPos,rCEvt.GetCommand(),rCEvt.IsMouseEvent());
//STRIP001              // Command ist an der OutlinerView leider void
//STRIP001              pTextEditOutlinerView->Command(aCEvt);
//STRIP001              if (pWin!=NULL && pWin!=pTextEditWin) SetTextEditWin(pWin);
//STRIP001 #ifndef SVX_LIGHT
//STRIP001              if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001              ImpMakeTextCursorAreaVisible();
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else // if (rCEvt.GetCommand() == COMMAND_VOICE )
//STRIP001      {
//STRIP001          pTextEditOutlinerView->Command(rCEvt);
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return SdrGlueEditView::Command(rCEvt,pWin);
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::Cut(ULONG nFormat)
//STRIP001 {
//STRIP001     if (pTextEditOutliner!=NULL) {
//STRIP001         pTextEditOutlinerView->Cut();
//STRIP001 #ifndef SVX_LIGHT
//STRIP001         if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001         ImpMakeTextCursorAreaVisible();
//STRIP001         return TRUE;
//STRIP001     } else {
//STRIP001         return SdrGlueEditView::Cut(nFormat);
//STRIP001     }
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::Yank(ULONG nFormat)
//STRIP001 {
//STRIP001     if (pTextEditOutliner!=NULL) {
//STRIP001         pTextEditOutlinerView->Copy();
//STRIP001         return TRUE;
//STRIP001     } else {
//STRIP001         return SdrGlueEditView::Yank(nFormat);
//STRIP001     }
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::Paste(Window* pWin, ULONG nFormat)
//STRIP001 {
//STRIP001     if (pTextEditOutliner!=NULL) {
//STRIP001         if (pWin!=NULL) {
//STRIP001             OutlinerView* pNewView=ImpFindOutlinerView(pWin);
//STRIP001             if (pNewView!=NULL) {
//STRIP001                 pNewView->Paste();
//STRIP001             }
//STRIP001         } else {
//STRIP001             pTextEditOutlinerView->Paste();
//STRIP001         }
//STRIP001 #ifndef SVX_LIGHT
//STRIP001         if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001         ImpMakeTextCursorAreaVisible();
//STRIP001         return TRUE;
//STRIP001     } else {
//STRIP001         return SdrGlueEditView::Paste(pWin,nFormat);
//STRIP001     }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrObjEditView::ImpIsTextEditAllSelected() const
//STRIP001 {
//STRIP001     BOOL bRet=FALSE;
//STRIP001     if (pTextEditOutliner!=NULL && pTextEditOutlinerView!=NULL) {
//STRIP001         BOOL bEmpty=FALSE;
//STRIP001         ULONG nParaAnz=pTextEditOutliner->GetParagraphCount();
//STRIP001         Paragraph* p1stPara=pTextEditOutliner->GetParagraph( 0 );
//STRIP001         Paragraph* pLastPara=pTextEditOutliner->GetParagraph( nParaAnz > 1 ? nParaAnz - 1 : 0 );
//STRIP001         if (p1stPara==NULL) nParaAnz=0;
//STRIP001         if (nParaAnz==1) { // bei nur einem Para nachsehen ob da ueberhaupt was drin steht
//STRIP001             XubString aStr(pTextEditOutliner->GetText(p1stPara));
//STRIP001
//STRIP001          // Aha, steht nix drin!
//STRIP001             if(!aStr.Len())
//STRIP001              nParaAnz = 0;
//STRIP001         }
//STRIP001         bEmpty=nParaAnz==0;
//STRIP001         if (!bEmpty) {
//STRIP001             ESelection aESel(pTextEditOutlinerView->GetSelection());
//STRIP001             if (aESel.nStartPara==0 && aESel.nStartPos==0 && aESel.nEndPara==USHORT(nParaAnz-1)) {
//STRIP001                 XubString aStr(pTextEditOutliner->GetText(pLastPara));
//STRIP001
//STRIP001              if(aStr.Len() == aESel.nEndPos)
//STRIP001                  bRet = TRUE;
//STRIP001             }
//STRIP001             // und nun auch noch fuer den Fall, das rueckwaerts selektiert wurde
//STRIP001             if (!bRet && aESel.nEndPara==0 && aESel.nEndPos==0 && aESel.nStartPara==USHORT(nParaAnz-1)) {
//STRIP001                 XubString aStr(pTextEditOutliner->GetText(pLastPara));
//STRIP001
//STRIP001                 if(aStr.Len() == aESel.nStartPos)
//STRIP001                  bRet = TRUE;
//STRIP001             }
//STRIP001         } else {
//STRIP001             bRet=TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001     return bRet;
//STRIP001 }

//STRIP001 void SdrObjEditView::ImpMakeTextCursorAreaVisible()
//STRIP001 {
//STRIP001     if (pTextEditOutlinerView!=NULL && pTextEditWin!=NULL) {
//STRIP001         Cursor* pCsr=pTextEditWin->GetCursor();
//STRIP001         if (pCsr!=NULL) {
//STRIP001             Size aSiz(pCsr->GetSize());
//STRIP001             if (aSiz.Width()!=0 && aSiz.Height()!=0) { // #38450#
//STRIP001                 MakeVisible(Rectangle(pCsr->GetPos(),aSiz),*pTextEditWin);
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001 }

//STRIP001 USHORT SdrObjEditView::GetScriptType() const
//STRIP001 {
//STRIP001  USHORT nScriptType = 0;
//STRIP001
//STRIP001     if( IsTextEdit() )
//STRIP001  {
//STRIP001      if( pTextEditObj->GetOutlinerParaObject() )
//STRIP001          nScriptType = pTextEditObj->GetOutlinerParaObject()->GetTextObject().GetScriptType();
//STRIP001
//STRIP001      if( pTextEditOutlinerView )
//STRIP001          nScriptType = pTextEditOutlinerView->GetSelectedScriptType();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      sal_uInt32 nMarkCount( aMark.GetMarkCount() );
//STRIP001
//STRIP001      for( sal_uInt32 i = 0; i < nMarkCount; i++ )
//STRIP001      {
//STRIP001          OutlinerParaObject* pParaObj = aMark.GetMark( i )->GetObj()->GetOutlinerParaObject();
//STRIP001
//STRIP001          if( pParaObj )
//STRIP001          {
//STRIP001              USHORT nType = pParaObj->GetTextObject().GetScriptType();
//STRIP001
//STRIP001              switch ( nType )
//STRIP001              {
//STRIP001                  case SCRIPTTYPE_LATIN:
//STRIP001                      nScriptType |= SCRIPTTYPE_LATIN;
//STRIP001                  break;
//STRIP001                  case SCRIPTTYPE_ASIAN:
//STRIP001                      nScriptType |= SCRIPTTYPE_ASIAN;
//STRIP001                  break;
//STRIP001                  case SCRIPTTYPE_COMPLEX:
//STRIP001                      nScriptType |= SCRIPTTYPE_COMPLEX;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( nScriptType == 0 )
//STRIP001      nScriptType = SCRIPTTYPE_LATIN;
//STRIP001
//STRIP001  return nScriptType;
//STRIP001 }

/* new interface src537 */
//STRIP001 BOOL SdrObjEditView::GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr) const
//STRIP001 {
//STRIP001     if(IsTextEdit())
//STRIP001  {
//STRIP001         DBG_ASSERT(pTextEditOutlinerView!=NULL,"SdrObjEditView::GetAttributes(): pTextEditOutlinerView=NULL");
//STRIP001         DBG_ASSERT(pTextEditOutliner!=NULL,"SdrObjEditView::GetAttributes(): pTextEditOutliner=NULL");
//STRIP001
//STRIP001      // #92389# take care of bOnlyHardAttr(!)
//STRIP001      if(!bOnlyHardAttr && pTextEditObj->GetStyleSheet())
//STRIP001          rTargetSet.Put(pTextEditObj->GetStyleSheet()->GetItemSet());
//STRIP001
//STRIP001      // add object attributes
//STRIP001      rTargetSet.Put( pTextEditObj->GetItemSet() );
//STRIP001
//STRIP001      if( pTextEditObj->GetOutlinerParaObject() )
//STRIP001          rTargetSet.Put( SvxScriptTypeItem( pTextEditObj->GetOutlinerParaObject()->GetTextObject().GetScriptType() ) );
//STRIP001
//STRIP001      if(pTextEditOutlinerView)
//STRIP001      {
//STRIP001          // FALSE= InvalidItems nicht al Default, sondern als "Loecher" betrachten
//STRIP001             rTargetSet.Put(pTextEditOutlinerView->GetAttribs(), FALSE);
//STRIP001          rTargetSet.Put( SvxScriptTypeItem( pTextEditOutlinerView->GetSelectedScriptType() ), FALSE );
//STRIP001         }
//STRIP001
//STRIP001         if(aMark.GetMarkCount()==1 && aMark.GetMark(0)->GetObj()==pTextEditObj)
//STRIP001      {
//STRIP001             MergeNotPersistAttrFromMarked(rTargetSet, bOnlyHardAttr);
//STRIP001         }
//STRIP001
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         return SdrGlueEditView::GetAttributes(rTargetSet, bOnlyHardAttr);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrObjEditView::SetAttributes(const SfxItemSet& rSet, BOOL bReplaceAll)
//STRIP001 {
//STRIP001     BOOL bRet=FALSE;
//STRIP001     BOOL bTextEdit=pTextEditOutlinerView!=NULL;
//STRIP001     BOOL bAllTextSelected=ImpIsTextEditAllSelected();
//STRIP001     SfxItemSet* pModifiedSet=NULL;
//STRIP001     const SfxItemSet* pSet=&rSet;
//STRIP001     const SvxAdjustItem* pParaJust=NULL;
//STRIP001
//STRIP001     if (!bTextEdit)
//STRIP001  {
//STRIP001         // Kein TextEdit aktiv -> alle Items ans Zeichenobjekt
//STRIP001         bRet=SdrGlueEditView::SetAttributes(*pSet,bReplaceAll);
//STRIP001     }
//STRIP001  else
//STRIP001  {
//STRIP001 #ifdef DBG_UTIL
//STRIP001         {
//STRIP001             BOOL bHasEEFeatureItems=FALSE;
//STRIP001             SfxItemIter aIter(rSet);
//STRIP001             const SfxPoolItem* pItem=aIter.FirstItem();
//STRIP001             while (!bHasEEFeatureItems && pItem!=NULL)
//STRIP001          {
//STRIP001                 if (!IsInvalidItem(pItem))
//STRIP001              {
//STRIP001                     USHORT nW=pItem->Which();
//STRIP001                     if (nW>=EE_FEATURE_START && nW<=EE_FEATURE_END)
//STRIP001                      bHasEEFeatureItems=TRUE;
//STRIP001                 }
//STRIP001
//STRIP001                 pItem=aIter.NextItem();
//STRIP001             }
//STRIP001
//STRIP001             if(bHasEEFeatureItems)
//STRIP001          {
//STRIP001              String aMessage;
//STRIP001              aMessage.AppendAscii("SdrObjEditView::SetAttributes(): Das setzen von EE_FEATURE-Items an der SdrView macht keinen Sinn! Es fuehrt nur zu Overhead und nicht mehr lesbaren Dokumenten.");
//STRIP001                 InfoBox(NULL, aMessage).Execute();
//STRIP001             }
//STRIP001         }
//STRIP001 #endif
//STRIP001
//STRIP001         BOOL bOnlyEEItems;
//STRIP001         BOOL bNoEEItems=!SearchOutlinerItems(*pSet,bReplaceAll,&bOnlyEEItems);
//STRIP001         // alles selektiert? -> Attrs auch an den Rahmen
//STRIP001         // und falls keine EEItems, dann Attrs nur an den Rahmen
//STRIP001         if (bAllTextSelected || bNoEEItems) {
//STRIP001             String aStr;
//STRIP001             ImpTakeDescriptionStr(STR_EditSetAttributes,aStr);
//STRIP001             BegUndo(aStr);
//STRIP001             AddUndo(new SdrUndoGeoObj(*pTextEditObj));
//STRIP001             AddUndo(new SdrUndoAttrObj(*pTextEditObj,FALSE,!bNoEEItems));
//STRIP001             EndUndo();
//STRIP001
//STRIP001          SdrBroadcastItemChange aItemChange(*pTextEditObj);
//STRIP001          if(bReplaceAll)
//STRIP001              pTextEditObj->ClearItem();
//STRIP001             pTextEditObj->SetItemSet(*pSet);
//STRIP001             pTextEditObj->BroadcastItemChange(aItemChange);
//STRIP001
//STRIP001          FlushComeBackTimer(); // Damit ModeHasChanged sofort kommt
//STRIP001             bRet=TRUE;
//STRIP001         } else if (!bOnlyEEItems) { // sonst Set ggf. splitten
//STRIP001             // Es wird nun ein ItemSet aSet gemacht, in den die EE_Items von
//STRIP001             // *pSet nicht enhalten ist (ansonsten ist es eine Kopie).
//STRIP001             USHORT* pNewWhichTable=RemoveWhichRange(pSet->GetRanges(),EE_ITEMS_START,EE_ITEMS_END);
//STRIP001             SfxItemSet aSet(pMod->GetItemPool(),pNewWhichTable);
//STRIP001             /*90353*/ delete[] pNewWhichTable;
//STRIP001             SfxWhichIter aIter(aSet);
//STRIP001             USHORT nWhich=aIter.FirstWhich();
//STRIP001             while (nWhich!=0) {
//STRIP001                 const SfxPoolItem* pItem;
//STRIP001                 SfxItemState eState=pSet->GetItemState(nWhich,FALSE,&pItem);
//STRIP001                 if (eState==SFX_ITEM_SET) aSet.Put(*pItem);
//STRIP001                 nWhich=aIter.NextWhich();
//STRIP001             }
//STRIP001             String aStr;
//STRIP001             ImpTakeDescriptionStr(STR_EditSetAttributes,aStr);
//STRIP001             BegUndo(aStr);
//STRIP001             AddUndo(new SdrUndoGeoObj(*pTextEditObj));
//STRIP001             AddUndo(new SdrUndoAttrObj(*pTextEditObj,FALSE,FALSE));
//STRIP001             EndUndo();
//STRIP001
//STRIP001          SdrBroadcastItemChange aItemChange(*pTextEditObj);
//STRIP001          if(bReplaceAll)
//STRIP001              pTextEditObj->ClearItem();
//STRIP001             pTextEditObj->SetItemSet(aSet);
//STRIP001             pTextEditObj->BroadcastItemChange(aItemChange);
//STRIP001
//STRIP001             if (aMark.GetMarkCount()==1 && aMark.GetMark(0)->GetObj()==pTextEditObj) {
//STRIP001                 SetNotPersistAttrToMarked(aSet,bReplaceAll);
//STRIP001             }
//STRIP001             FlushComeBackTimer();
//STRIP001             bRet=TRUE;
//STRIP001         }
//STRIP001         if(!bNoEEItems)
//STRIP001      {
//STRIP001             // und nun die Attribute auch noch an die EditEngine
//STRIP001             if (bReplaceAll) {
//STRIP001                 // Am Outliner kann man leider nur alle Attribute platthauen
//STRIP001                 pTextEditOutlinerView->RemoveAttribs( TRUE );
//STRIP001             }
//STRIP001             pTextEditOutlinerView->SetAttribs(rSet);
//STRIP001
//STRIP001             if (pItemBrowser!=NULL)
//STRIP001              pItemBrowser->SetDirty();
//STRIP001
//STRIP001             ImpMakeTextCursorAreaVisible();
//STRIP001         }
//STRIP001         bRet=TRUE;
//STRIP001     }
//STRIP001     if (pModifiedSet!=NULL) delete pModifiedSet;
//STRIP001     return bRet;
//STRIP001 }

//STRIP001 SfxStyleSheet* SdrObjEditView::GetStyleSheet(BOOL& rOk) const
//STRIP001 {
//STRIP001     if ( pTextEditOutlinerView )
//STRIP001  {
//STRIP001         rOk=TRUE;
//STRIP001      SfxStyleSheet* pSheet = pTextEditOutlinerView->GetStyleSheet();
//STRIP001         return pSheet;
//STRIP001     }
//STRIP001  else
//STRIP001  {
//STRIP001         return SdrGlueEditView::GetStyleSheet(rOk);
//STRIP001     }
//STRIP001 }

/*N*/ BOOL SdrObjEditView::SetStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  // if we are currently in edit mode we must also set the stylesheet
//STRIP001  // on all paragraphs in the Outliner for the edit view
//STRIP001  // #92191#
//STRIP001  if( NULL != pTextEditOutlinerView )
//STRIP001  {
//STRIP001      Outliner* pOutliner = pTextEditOutlinerView->GetOutliner();
//STRIP001
//STRIP001      const ULONG nParaCount = pOutliner->GetParagraphCount();
//STRIP001      ULONG nPara;
//STRIP001      for( nPara = 0; nPara < nParaCount; nPara++ )
//STRIP001      {
//STRIP001          pOutliner->SetStyleSheet( nPara, pStyleSheet );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 /*   #92191# we do not support the 'feature' for different styles in paragraphs
//STRIP001  any longer
//STRIP001
//STRIP001     if (pTextEditOutlinerView!=NULL) {
//STRIP001         BOOL bAllSelected=ImpIsTextEditAllSelected();
//STRIP001         if (bAllSelected) {
//STRIP001             String aStr;
//STRIP001             if (pStyleSheet!=NULL) ImpTakeDescriptionStr(STR_EditSetStylesheet,aStr);
//STRIP001             else ImpTakeDescriptionStr(STR_EditDelStylesheet,aStr);
//STRIP001             BegUndo(aStr);
//STRIP001             AddUndo(new SdrUndoGeoObj(*pTextEditObj));
//STRIP001             AddUndo(new SdrUndoAttrObj(*pTextEditObj,TRUE,TRUE));
//STRIP001             EndUndo();
//STRIP001             pTextEditObj->SetStyleSheet(pStyleSheet,bDontRemoveHardAttr);
//STRIP001         }
//STRIP001         if (pStyleSheet!=NULL) {
//STRIP001             // Der Outliner entfernt bei der Zuweisung eines StyleSheets immer
//STRIP001             // dir entsprechenden harten Attribute. Jedoch nur vom Absatz,
//STRIP001             // keine Zeichenattribute. Und genau so soll das scheinbar auch
//STRIP001             // sein, auch wenn es nicht ganz meinem Interface entspricht.
//STRIP001             // (Joe M. 27-11-1995)
//STRIP001             pTextEditOutlinerView->SetStyleSheet(pStyleSheet);
//STRIP001         }
//STRIP001 #ifndef SVX_LIGHT
//STRIP001         if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001         ImpMakeTextCursorAreaVisible();
//STRIP001         return TRUE;
//STRIP001     } else
//STRIP001 */
//STRIP001  {
//STRIP001         return SdrGlueEditView::SetStyleSheet(pStyleSheet,bDontRemoveHardAttr);
//STRIP001     }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrObjEditView::AddWin(OutputDevice* pWin1)
//STRIP001 {
//STRIP001     SdrGlueEditView::AddWin(pWin1);
//STRIP001     if (pTextEditObj!=NULL && !bTextEditOnlyOneView && pWin1->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001         OutlinerView* pOutlView=ImpMakeOutlinerView((Window*)pWin1,FALSE,NULL);
//STRIP001         pTextEditOutliner->InsertView(pOutlView);
//STRIP001     }
//STRIP001 }

/*N*/ void SdrObjEditView::DelWin(OutputDevice* pWin1)
/*N*/ {
/*N*/     SdrGlueEditView::DelWin(pWin1);
/*N*/     if (pTextEditObj!=NULL && !bTextEditOnlyOneView && pWin1->GetOutDevType()==OUTDEV_WINDOW) {
/*?*/         DBG_ASSERT(0, "STRIP"); //STRIP001 for (ULONG i=pTextEditOutliner->GetViewCount(); i>0;) {
//STRIP001 /*?*/             i--;
//STRIP001 /*?*/             OutlinerView* pOLV=pTextEditOutliner->GetView(i);
//STRIP001 /*?*/             if (pOLV && pOLV->GetWindow()==(Window*)pWin1) {
//STRIP001 /*?*/                 delete pTextEditOutliner->RemoveView(i);
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
/*N*/     }
/*N*/ }

/*N*/ BOOL SdrObjEditView::IsTextEditInSelectionMode() const
/*N*/ {
/*N*/     return pTextEditOutliner!=NULL && pTextEditOutliner->IsInSelectionMode();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@   @@  @@@@   @@@@  @@@@@   @@@@   @@   @@  @@@@  @@@@@  @@@@@
//  @@@ @@@ @@  @@ @@  @@ @@  @@ @@  @@  @@@ @@@ @@  @@ @@  @@ @@
//  @@@@@@@ @@  @@ @@     @@  @@ @@  @@  @@@@@@@ @@  @@ @@  @@ @@
//  @@@@@@@ @@@@@@ @@     @@@@@  @@  @@  @@@@@@@ @@  @@ @@  @@ @@@@
//  @@ @ @@ @@  @@ @@     @@  @@ @@  @@  @@ @ @@ @@  @@ @@  @@ @@
//  @@   @@ @@  @@ @@  @@ @@  @@ @@  @@  @@   @@ @@  @@ @@  @@ @@
//  @@   @@ @@  @@  @@@@  @@  @@  @@@@   @@   @@  @@@@  @@@@@  @@@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrObjEditView::BegMacroObj(const Point& rPnt, short nTol, SdrObject* pObj, SdrPageView* pPV, Window* pWin)
//STRIP001 {
//STRIP001     BOOL bRet=FALSE;
//STRIP001     BrkMacroObj();
//STRIP001     if (pObj!=NULL && pPV!=NULL && pWin!=NULL && pObj->HasMacro()) {
//STRIP001         nTol=ImpGetHitTolLogic(nTol,NULL);
//STRIP001         pMacroObj=pObj;
//STRIP001         pMacroPV=pPV;
//STRIP001         pMacroWin=pWin;
//STRIP001         bMacroDown=FALSE;
//STRIP001         nMacroTol=USHORT(nTol);
//STRIP001         aMacroDownPos=rPnt;
//STRIP001         aMacroDownPos-=pMacroPV->GetOffset();
//STRIP001         MovMacroObj(rPnt);
//STRIP001     }
//STRIP001     return bRet;
//STRIP001 }

//STRIP001 void SdrObjEditView::ImpMacroUp(const Point& rUpPos)
//STRIP001 {
//STRIP001     if (pMacroObj!=NULL && bMacroDown) {
//STRIP001         pXOut->SetOutDev(pMacroWin);
//STRIP001         BOOL bOn=IsShownXorVisible(pMacroWin);
//STRIP001         if (bOn) HideShownXor(pMacroWin);
//STRIP001         Point aOfs(pMacroPV->GetOffset());
//STRIP001         pXOut->SetOffset(aOfs);
//STRIP001         SdrObjMacroHitRec aHitRec;
//STRIP001         aHitRec.aPos=rUpPos;
//STRIP001         aHitRec.aDownPos=aMacroDownPos;
//STRIP001         aHitRec.nTol=nMacroTol;
//STRIP001         aHitRec.pVisiLayer=&pMacroPV->GetVisibleLayers();
//STRIP001         aHitRec.pPageView=pMacroPV;
//STRIP001         aHitRec.pOut=pMacroWin;
//STRIP001         pMacroObj->PaintMacro(*pXOut,Rectangle(),aHitRec);
//STRIP001         pXOut->SetOffset(Point(0,0));
//STRIP001         if (bOn) ShowShownXor(pMacroWin);
//STRIP001         bMacroDown=FALSE;
//STRIP001     }
//STRIP001 }

//STRIP001 void SdrObjEditView::ImpMacroDown(const Point& rDownPos)
//STRIP001 {
//STRIP001     if (pMacroObj!=NULL && !bMacroDown) {
//STRIP001         pXOut->SetOutDev(pMacroWin);
//STRIP001         BOOL bOn=IsShownXorVisible(pMacroWin);
//STRIP001         if (bOn) HideShownXor(pMacroWin);
//STRIP001         Point aOfs(pMacroPV->GetOffset());
//STRIP001         pXOut->SetOffset(aOfs);
//STRIP001         SdrObjMacroHitRec aHitRec;
//STRIP001         aHitRec.aPos=rDownPos;
//STRIP001         aHitRec.aDownPos=aMacroDownPos;
//STRIP001         aHitRec.nTol=nMacroTol;
//STRIP001         aHitRec.pVisiLayer=&pMacroPV->GetVisibleLayers();
//STRIP001         aHitRec.pPageView=pMacroPV;
//STRIP001         aHitRec.bDown=TRUE;
//STRIP001         aHitRec.pOut=pMacroWin;
//STRIP001         pMacroObj->PaintMacro(*pXOut,Rectangle(),aHitRec);
//STRIP001         pXOut->SetOffset(Point(0,0));
//STRIP001         if (bOn) ShowShownXor(pMacroWin);
//STRIP001         bMacroDown=TRUE;
//STRIP001     }
//STRIP001 }

//STRIP001 void SdrObjEditView::MovMacroObj(const Point& rPnt)
//STRIP001 {
//STRIP001     if (pMacroObj!=NULL) {
//STRIP001         Point aPnt(rPnt-pMacroPV->GetOffset());
//STRIP001         SdrObjMacroHitRec aHitRec;
//STRIP001         aHitRec.aPos=aPnt;
//STRIP001         aHitRec.aDownPos=aMacroDownPos;
//STRIP001         aHitRec.nTol=nMacroTol;
//STRIP001         aHitRec.pVisiLayer=&pMacroPV->GetVisibleLayers();
//STRIP001         aHitRec.pPageView=pMacroPV;
//STRIP001         aHitRec.bDown=bMacroDown;
//STRIP001         aHitRec.pOut=pMacroWin;
//STRIP001         BOOL bDown=pMacroObj->IsMacroHit(aHitRec);
//STRIP001         if (bDown) ImpMacroDown(aPnt);
//STRIP001         else ImpMacroUp(aPnt);
//STRIP001     }
//STRIP001 }

/*N*/ void SdrObjEditView::BrkMacroObj()
/*N*/ {
/*N*/     if (pMacroObj!=NULL) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         ImpMacroUp(aMacroDownPos);
//STRIP001 /*?*/         pMacroObj=NULL;
//STRIP001 /*?*/         pMacroPV=NULL;
//STRIP001 /*?*/         pMacroWin=NULL;
/*N*/     }
/*N*/ }

//STRIP001 BOOL SdrObjEditView::EndMacroObj()
//STRIP001 {
//STRIP001     if (pMacroObj!=NULL && bMacroDown) {
//STRIP001         ImpMacroUp(aMacroDownPos);
//STRIP001         SdrObjMacroHitRec aHitRec;
//STRIP001         aHitRec.aPos=aMacroDownPos;
//STRIP001         aHitRec.aDownPos=aMacroDownPos;
//STRIP001         aHitRec.nTol=nMacroTol;
//STRIP001         aHitRec.pVisiLayer=&pMacroPV->GetVisibleLayers();
//STRIP001         aHitRec.pPageView=pMacroPV;
//STRIP001         aHitRec.bDown=TRUE;
//STRIP001         aHitRec.pOut=pMacroWin;
//STRIP001         BOOL bRet=pMacroObj->DoMacro(aHitRec);
//STRIP001         pMacroObj=NULL;
//STRIP001         pMacroPV=NULL;
//STRIP001         pMacroWin=NULL;
//STRIP001         return bRet;
//STRIP001     } else {
//STRIP001         BrkMacroObj();
//STRIP001         return FALSE;
//STRIP001     }
//STRIP001 }

}
