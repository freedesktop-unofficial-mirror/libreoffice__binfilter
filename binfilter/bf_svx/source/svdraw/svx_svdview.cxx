/*************************************************************************
 *
 *  $RCSfile: svx_svdview.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:22 $
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

#ifndef _EEITEM_HXX //autogen
#include <eeitem.hxx>
#endif

#include "svdio.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
#include "svdpagv.hxx"
#include "svdmrkv.hxx"
#include "svdedxv.hxx"
#include "svdobj.hxx"
#include "svdopath.hxx" // fuer GetContext
#include "svdograf.hxx" // fuer GetContext
#include "svdetc.hxx"   // Fuer SdrEngineDefaults
#include "svdibrow.hxx"
#include "svdoutl.hxx"
#include "svdview.hxx"
#include "editview.hxx" // fuer GetField
#define ITEMID_FIELD EE_FEATURE_FIELD  /* wird fuer #include <flditem.hxx> benoetigt */
#include "flditem.hxx"  // fuer URLField
#include "obj3d.hxx"
#include "svddrgmt.hxx"
#include "svdoutl.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrViewEvent::SdrViewEvent():
/*N*/     bMouseDown(FALSE),
/*N*/     bMouseUp(FALSE),
/*N*/     nMouseClicks(0),
/*N*/     nMouseMode(0),
/*N*/     nMouseCode(0),
/*N*/     nHlplIdx(0),
/*N*/     nGlueId(0),
/*N*/     pHdl(NULL),
/*N*/     pObj(NULL),
/*N*/     pRootObj(NULL),
/*N*/     pPV(NULL),
/*N*/     eHit(SDRHIT_NONE),
/*N*/     eEvent(SDREVENT_NONE),
/*N*/     eHdlKind(HDL_MOVE),
/*N*/     bDoubleHdlSize(FALSE),
/*N*/     pURLField(NULL),
/*N*/     bIsAction(FALSE),
/*N*/     bIsTextEdit(FALSE),
/*N*/     bTextEditHit(FALSE),
/*N*/     bAddMark(FALSE),
/*N*/     bUnmark(FALSE),
/*N*/     bPrevNextMark(FALSE),
/*N*/     bMarkPrev(FALSE),
/*N*/     bInsPointNewObj(FALSE),
/*N*/     eEndCreateCmd(SDRCREATE_NEXTPOINT),
/*N*/     bDragWithCopy(FALSE),
/*N*/     bCaptureMouse(FALSE),
/*N*/     bReleaseMouse(FALSE)
/*N*/ {
/*N*/ }

/*N*/ SdrViewEvent::~SdrViewEvent()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@ @@ @@ @@@@@ @@   @@
//  @@ @@ @@ @@    @@   @@
//  @@ @@ @@ @@    @@ @ @@
//  @@@@@ @@ @@@@  @@@@@@@
//   @@@  @@ @@    @@@@@@@
//   @@@  @@ @@    @@@ @@@
//    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrView,SdrCreateView);

/*N*/ SdrView::SdrView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrCreateView(pModel1,pOut),
/*N*/   bNoExtendedMouseDispatcher(FALSE),
/*N*/   bNoExtendedKeyDispatcher(FALSE),
/*N*/   bNoExtendedCommandDispatcher(FALSE)
/*N*/ {
/*N*/   bTextEditOnObjectsWithoutTextIfTextTool=FALSE;
/*N*/
/*N*/   StartListening( maAccessibilityOptions );
/*N*/
/*N*/   onAccessibilityOptionsChanged();
/*N*/ }

/*N*/ SdrView::SdrView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*N*/   SdrCreateView(pModel1,pXOut),
/*N*/   bNoExtendedMouseDispatcher(FALSE),
/*N*/   bNoExtendedKeyDispatcher(FALSE),
/*N*/   bNoExtendedCommandDispatcher(FALSE)
/*N*/ {
/*N*/   bTextEditOnObjectsWithoutTextIfTextTool=FALSE;
/*N*/
/*N*/   StartListening( maAccessibilityOptions );
/*N*/
/*N*/   onAccessibilityOptionsChanged();
/*N*/ }

/*N*/ SdrView::SdrView(SdrModel* pModel1):
/*N*/   SdrCreateView(pModel1,(OutputDevice*)NULL),
/*N*/   bNoExtendedMouseDispatcher(FALSE),
/*N*/   bNoExtendedKeyDispatcher(FALSE),
/*N*/   bNoExtendedCommandDispatcher(FALSE)
/*N*/ {
/*N*/   bTextEditOnObjectsWithoutTextIfTextTool=FALSE;
/*N*/
/*N*/   StartListening( maAccessibilityOptions );
/*N*/
/*N*/   onAccessibilityOptionsChanged();
/*N*/ }

/*N*/ SdrView::~SdrView()
/*N*/ {
/*N*/   EndListening( maAccessibilityOptions );
/*N*/ }

//STRIP001 BOOL SdrView::KeyInput(const KeyEvent& rKEvt, Window* pWin)
//STRIP001 {
//STRIP001  SetActualWin(pWin);
//STRIP001  BOOL bRet=SdrCreateView::KeyInput(rKEvt,pWin);
//STRIP001  if (!bRet && !IsExtendedKeyInputDispatcherEnabled()) {
//STRIP001      bRet=TRUE;
//STRIP001      switch (rKEvt.GetKeyCode().GetFullFunction()) {
//STRIP001          case KEYFUNC_CUT   : Cut(); break;
//STRIP001          case KEYFUNC_COPY  : Yank(); break;
//STRIP001          case KEYFUNC_PASTE : Paste(pWin); break;
//STRIP001          case KEYFUNC_DELETE: DeleteMarked(); break;
//STRIP001          case KEYFUNC_UNDO: pMod->Undo(); break;
//STRIP001          case KEYFUNC_REDO: pMod->Redo(); break;
//STRIP001          case KEYFUNC_REPEAT: pMod->Repeat(*this); break;
//STRIP001          default: {
//STRIP001              switch (rKEvt.GetKeyCode().GetFullCode()) {
//STRIP001                  case KEY_ESCAPE: {
//STRIP001                      if (IsTextEdit()) EndTextEdit();
//STRIP001                      if (IsAction()) BrkAction();
//STRIP001                      if (pWin!=NULL) pWin->ReleaseMouse();
//STRIP001                  } break;
//STRIP001                  case KEY_DELETE: DeleteMarked(); break;
//STRIP001                  case KEY_CUT: case KEY_DELETE+KEY_SHIFT: Cut(); break;
//STRIP001                  case KEY_COPY: case KEY_INSERT+KEY_MOD1: Yank(); break;
//STRIP001                  case KEY_PASTE: case KEY_INSERT+KEY_SHIFT: Paste(pWin); break;
//STRIP001                  case KEY_UNDO: case KEY_BACKSPACE+KEY_MOD2: pMod->Undo(); break;
//STRIP001                  case KEY_BACKSPACE+KEY_MOD2+KEY_SHIFT: pMod->Redo(); break;
//STRIP001                  case KEY_REPEAT: case KEY_BACKSPACE+KEY_MOD2+KEY_MOD1: pMod->Repeat(*this); break;
//STRIP001                  case KEY_MOD1+KEY_A: MarkAll(); break;
//STRIP001                  default: bRet=FALSE;
//STRIP001              } // switch
//STRIP001          }
//STRIP001      } // switch
//STRIP001      if (bRet && pWin!=NULL) {
//STRIP001          pWin->SetPointer(GetPreferedPointer(
//STRIP001              pWin->PixelToLogic(pWin->ScreenToOutputPixel( pWin->GetPointerPosPixel() ) ),
//STRIP001              pWin,
//STRIP001              rKEvt.GetKeyCode().GetModifier()));
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrView::MouseButtonDown(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001  SetActualWin(pWin);
//STRIP001  if (rMEvt.IsLeft()) aDragStat.SetMouseDown(TRUE);
//STRIP001  BOOL bRet=SdrCreateView::MouseButtonDown(rMEvt,pWin);
//STRIP001  if (!bRet && !IsExtendedMouseEventDispatcherEnabled()) {
//STRIP001      SdrViewEvent aVEvt;
//STRIP001      PickAnything(rMEvt,SDRMOUSEBUTTONDOWN,aVEvt);
//STRIP001      bRet=DoMouseEvent(aVEvt);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrView::MouseButtonUp(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001  SetActualWin(pWin);
//STRIP001  if (rMEvt.IsLeft()) aDragStat.SetMouseDown(FALSE);
//STRIP001  BOOL bAction=IsAction();
//STRIP001  BOOL bRet=!bAction && SdrCreateView::MouseButtonUp(rMEvt,pWin);
//STRIP001  if (!bRet && !IsExtendedMouseEventDispatcherEnabled()) {
//STRIP001      SdrViewEvent aVEvt;
//STRIP001      PickAnything(rMEvt,SDRMOUSEBUTTONUP,aVEvt);
//STRIP001      bRet=DoMouseEvent(aVEvt);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrView::MouseMove(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001  SetActualWin(pWin);
//STRIP001  aDragStat.SetMouseDown(rMEvt.IsLeft());
//STRIP001  BOOL bRet=SdrCreateView::MouseMove(rMEvt,pWin);
//STRIP001  if (!IsExtendedMouseEventDispatcherEnabled() && !IsTextEditInSelectionMode()) {
//STRIP001      SdrViewEvent aVEvt;
//STRIP001      PickAnything(rMEvt,SDRMOUSEMOVE,aVEvt);
//STRIP001      if (DoMouseEvent(aVEvt)) bRet=TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // #87792# Removed code which did let the mouse snap on object
//STRIP001  // points
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrView::Command(const CommandEvent& rCEvt, Window* pWin)
//STRIP001 {
//STRIP001  SetActualWin(pWin);
//STRIP001  BOOL bRet=SdrCreateView::Command(rCEvt,pWin);
//STRIP001  return bRet;
//STRIP001 }

/* new interface src537 */
//STRIP001 BOOL SdrView::GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr) const
//STRIP001 {
//STRIP001  return SdrCreateView::GetAttributes(rTargetSet, bOnlyHardAttr);
//STRIP001 }

//STRIP001 SfxStyleSheet* SdrView::GetStyleSheet() const
//STRIP001 {
//STRIP001  BOOL bOk=FALSE;
//STRIP001  return SdrCreateView::GetStyleSheet(bOk);
//STRIP001 }

//STRIP001 SdrHitKind SdrView::PickAnything(const MouseEvent& rMEvt, USHORT nEventKind, SdrViewEvent& rVEvt) const
//STRIP001 {
//STRIP001  rVEvt.bMouseDown=nEventKind==SDRMOUSEBUTTONDOWN;
//STRIP001  rVEvt.bMouseUp=nEventKind==SDRMOUSEBUTTONUP;
//STRIP001  rVEvt.nMouseClicks=rMEvt.GetClicks();
//STRIP001  rVEvt.nMouseMode=rMEvt.GetMode();
//STRIP001  rVEvt.nMouseCode=rMEvt.GetButtons() | rMEvt.GetModifier();
//STRIP001  const OutputDevice* pOut=pActualOutDev;
//STRIP001  if (pOut==NULL) pOut=GetWin(0);
//STRIP001  Point aPnt(rMEvt.GetPosPixel());
//STRIP001  if (pOut!=NULL) aPnt=pOut->PixelToLogic(aPnt);
//STRIP001  rVEvt.aLogicPos=aPnt;
//STRIP001  return PickAnything(aPnt,rVEvt);
//STRIP001 }

// Mit der Maus draggen (Move)
// Beispiel beim erzeugen eines Rechtecks. MouseDown muss ohne
// ModKey erfolgen, weil sonst i.d.R. Markieren forciert wird (s.u.)
// Drueckt man dann beim MouseMove gleichzeitig Shift, Ctrl, und Alt,
// so erzeugt man ein zentrisches Quadrat ohne Fang.
// Die Doppelbelegung von Ortho und Shift stellt i.d.R. kein Problem dar,
// da sich beides meisst gegenseitig ausschliesst. Einzig Shear (das beim
// Verzerren, nicht dass beim Drehen) beruecksichtigt beides gleichzeitig.
// Dass muss der Anwender erstmal noch umschiffen (z.B. mit einer Hilfslinie).
#define MODKEY_NoSnap    bCtrl  /* Fang temporaer aus */
#define MODKEY_Ortho     bShift /* na eben ortho */
#define MODKEY_Center    bAlt   /* Zentrisch erzeugen/resizen */
//#define MODKEY_BigOrtho  bAlt
#define MODKEY_AngleSnap bShift
#define MODKEY_CopyDrag  bCtrl  /* Draggen mit kopieren */

// irgendwo hinklicken (MouseDown)
#define MODKEY_PolyPoly  bAlt   /* Neues Poly bei InsPt und bei Create */
#define MODKEY_MultiMark bShift /* MarkObj ohne vorher UnmarkAll */
#define MODKEY_Unmark    bAlt   /* Unmark durch Rahmenaufziehen */
#define MODKEY_ForceMark bCtrl  /* Rahmenaufziehen erzwingen, auch wenn Obj an MausPos */
#define MODKEY_DeepMark  bAlt   /* MarkNextObj */
#define MODKEY_DeepBackw bShift /* MarkNextObj rueckwaerts */

/*N*/ SdrHitKind SdrView::PickAnything(const Point& rLogicPos, SdrViewEvent& rVEvt) const
/*N*/ {
/*N*/   const OutputDevice* pOut=pActualOutDev;
/*N*/   if (pOut==NULL) pOut=GetWin(0);
/*N*/   Point aPnt(rLogicPos);
/*N*/   BOOL bEditMode=IsEditMode();
/*N*/   BOOL bPointMode=bEditMode && HasMarkablePoints();
/*N*/   BOOL bGluePointMode=IsGluePointEditMode();
/*N*/   BOOL bInsPolyPt=bPointMode && IsInsObjPointMode() && IsInsObjPointPossible();
/*N*/   BOOL bInsGluePt=bGluePointMode && IsInsGluePointMode() && IsInsGluePointPossible();
/*N*/   BOOL bIsTextEdit=IsTextEdit();
/*N*/   BOOL bTextEditHit=IsTextEditHit(aPnt,0/*nHitTolLog*/);
/*N*/   BOOL bTextEditSel=IsTextEditInSelectionMode();
/*N*/   BOOL bShift=(rVEvt.nMouseCode & KEY_SHIFT) !=0;
/*N*/   BOOL bCtrl=(rVEvt.nMouseCode & KEY_MOD1) !=0;
/*N*/   BOOL bAlt=(rVEvt.nMouseCode & KEY_MOD2) !=0;
/*N*/   SdrHitKind eHit=SDRHIT_NONE;
/*N*/   SdrHdl* pHdl=pOut!=NULL && !bTextEditSel ? HitHandle(aPnt,*pActualOutDev) : NULL;
/*N*/   SdrPageView* pPV=NULL;
/*N*/   SdrObject* pObj=NULL;
/*N*/   SdrObject* pHitObj=NULL;
/*N*/   USHORT nHitPassNum=0;
/*N*/   USHORT nHlplIdx=0;
/*N*/   USHORT nGlueId=0;
/*N*/   BOOL bUnmarkedObjHit=FALSE;
/*N*/   if (bTextEditHit || bTextEditSel) {
/*N*/       eHit=SDRHIT_TEXTEDIT;
/*N*/       bTextEditHit=TRUE;
/*N*/   } else if (pHdl!=NULL) {
/*N*/       eHit=SDRHIT_HANDLE; // Handle getroffen hat hoechste Prioritaet
/*N*/   } else if (bEditMode && IsHlplVisible() && IsHlplFront() && pOut!=NULL && PickHelpLine(aPnt,nHitTolLog,*pOut,nHlplIdx,pPV)) {
/*N*/       eHit=SDRHIT_HELPLINE; // Hilfslinie im Vordergrund getroffen zum verschieben
/*N*/   } else if (bGluePointMode && PickGluePoint(aPnt,pObj,nGlueId,pPV)) {
/*N*/       eHit=SDRHIT_GLUEPOINT; // nichtmarkierter Klebepunkt getroffen
/*N*/   } else if (PickObj(aPnt,nHitTolLog,pHitObj,pPV,SDRSEARCH_DEEP|SDRSEARCH_MARKED,&pObj,NULL,&nHitPassNum)) {
/*N*/       eHit=SDRHIT_MARKEDOBJECT;
/*N*/   } else if (PickObj(aPnt,nHitTolLog,pHitObj,pPV,SDRSEARCH_DEEP|/*SDRSEARCH_TESTMARKABLE|*/SDRSEARCH_ALSOONMASTER|SDRSEARCH_WHOLEPAGE,&pObj,NULL,&nHitPassNum)) {
/*N*/       // MasterPages und WholePage fuer Macro und URL
/*N*/       eHit=SDRHIT_UNMARKEDOBJECT;
/*N*/       bUnmarkedObjHit=TRUE;
/*N*/   } else if (bEditMode && IsHlplVisible() && !IsHlplFront() && pOut!=NULL && PickHelpLine(aPnt,nHitTolLog,*pOut,nHlplIdx,pPV)) {
/*N*/       eHit=SDRHIT_HELPLINE; // Hilfslinie im Vordergrund getroffen zum verschieben
/*N*/   }
/*N*/   if (IsMacroMode() && eHit==SDRHIT_UNMARKEDOBJECT) {
/*N*/       BOOL bRoot=pObj->HasMacro();
/*N*/       BOOL bDeep=pObj!=pHitObj && pHitObj->HasMacro();
/*N*/       BOOL bMid=FALSE; // Gruppierte Gruppe mit Macro getroffen?
/*N*/       SdrObject* pMidObj=NULL;
/*N*/       if (pObj!=pHitObj) {
/*?*/           SdrObject* pObjTmp=NULL;
/*?*/           pObjTmp=pHitObj->GetUpGroup();
/*?*/           if (pObjTmp==pObj) pObjTmp=NULL;
/*?*/           while (pObjTmp!=NULL) {
/*?*/               if (pObjTmp->HasMacro()) {
/*?*/                   bMid=TRUE;
/*?*/                   pMidObj=pObjTmp;
/*?*/               }
/*?*/               pObjTmp=pObjTmp->GetUpGroup();
/*?*/               if (pObjTmp==pObj) pObjTmp=NULL;
/*?*/           }
/*N*/       }
/*N*/
/*N*/       if (bDeep || bMid || bRoot) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            Point aP(aPnt);
//STRIP001 /*?*/            aP-=pPV->GetOffset();
//STRIP001 /*?*/            SdrObjMacroHitRec aHitRec;
//STRIP001 /*?*/            aHitRec.aPos=aP;
//STRIP001 /*?*/            aHitRec.aDownPos=aP;
//STRIP001 /*?*/            aHitRec.nTol=nHitTolLog;
//STRIP001 /*?*/            aHitRec.pVisiLayer=&pPV->GetVisibleLayers();
//STRIP001 /*?*/            aHitRec.pPageView=pPV;
//STRIP001 /*?*/            if (bDeep) bDeep=pHitObj->IsMacroHit(aHitRec);
//STRIP001 /*?*/            if (bMid ) bMid =pMidObj->IsMacroHit(aHitRec);
//STRIP001 /*?*/            if (bRoot) bRoot=pObj->IsMacroHit(aHitRec);
//STRIP001 /*?*/            if (bRoot || bMid || bDeep) {
//STRIP001 /*?*/                // Prio: 1.Root, 2.Mid, 3.Deep
//STRIP001 /*?*/                rVEvt.pRootObj=pObj;
//STRIP001 /*?*/                if (!bRoot) pObj=pMidObj;
//STRIP001 /*?*/                if (!bRoot && !bMid) pObj=pHitObj;
//STRIP001 /*?*/                eHit=SDRHIT_MACRO;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
    // auf URL-Field checken
/*N*/   if (IsMacroMode() && eHit==SDRHIT_UNMARKEDOBJECT) {
/*N*/       SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pHitObj);
/*N*/       if (pTextObj!=NULL && pTextObj->HasText()) {
/*N*/           Point aP(aPnt);
/*N*/           aP-=pPV->GetOffset();
/*N*/           BOOL bTEHit=pTextObj->IsTextEditHit(aP,0/*nHitTolLog*/,&pPV->GetVisibleLayers());
/*N*/           if (bTEHit) {
/*N*/               Rectangle aTextRect;
/*N*/               Rectangle aAnchor;
/*N*/               SdrOutliner* pOutliner = &pTextObj->ImpGetDrawOutliner();
/*N*/               if( pTextObj->GetModel() )
/*N*/                   pOutliner = &pTextObj->GetModel()->GetHitTestOutliner();
/*N*/
/*N*/               pTextObj->TakeTextRect( *pOutliner, aTextRect, FALSE, &aAnchor, FALSE );
/*N*/               aP-=aTextRect.TopLeft();
/*N*/               // FitToSize berueksichtigen
/*N*/               SdrFitToSizeType eFit=pTextObj->GetFitToSize();
/*N*/               BOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
/*N*/               if (bFitToSize) {
/*?*/                   Fraction aX(aTextRect.GetWidth()-1,aAnchor.GetWidth()-1);
/*?*/                   Fraction aY(aTextRect.GetHeight()-1,aAnchor.GetHeight()-1);
/*?*/                   ResizePoint(aP,Point(),aX,aY);
/*N*/               }
/*N*/               // Drehung berueksichtigen
/*N*/               const GeoStat& rGeo=pTextObj->GetGeoStat();
/*N*/               if (rGeo.nDrehWink!=0) RotatePoint(aP,Point(),-rGeo.nSin,rGeo.nCos); // -sin fuer Unrotate
/*N*/               // Laufschrift berueksichtigen fehlt noch ...
/*N*/               if(pActualOutDev && pActualOutDev->GetOutDevType() == OUTDEV_WINDOW)
/*N*/               {
/*N*/                   OutlinerView aOLV(pOutliner, (Window*)pActualOutDev);
/*N*/                   const EditView& aEV=aOLV.GetEditView();
/*N*/                   const SvxFieldItem* pItem=aEV.GetField(aP);
/*N*/                   if (pItem!=NULL) {
/*?*/                       const SvxFieldData* pFld=pItem->GetField();
/*?*/                       const SvxURLField* pURL=PTR_CAST(SvxURLField,pFld);
/*N*/                       if (pURL!=NULL) {
/*N*/                           eHit=SDRHIT_URLFIELD;
/*N*/                           rVEvt.pURLField=pURL;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (nHitPassNum==SDRSEARCHPASS_DIRECT &&
/*N*/       (eHit==SDRHIT_MARKEDOBJECT || eHit==SDRHIT_UNMARKEDOBJECT) &&
/*N*/       (IsTextTool() || (IsEditMode() && IsQuickTextEditMode())) && pHitObj->HasTextEdit())
/*N*/   {
/*N*/       Point aP(aPnt);
/*N*/       aP-=pPV->GetOffset();
/*N*/       // Ringsum die TextEditArea ein Rand zum Selektieren ohne Textedit
/*N*/       Rectangle aBoundRect(pHitObj->GetBoundRect());
/*N*/
/*N*/       // #105130# Force to SnapRect when Fontwork
/*N*/       if(pHitObj->ISA(SdrTextObj) && ((SdrTextObj*)pHitObj)->IsFontwork())
/*N*/       {
/*N*/           aBoundRect = pHitObj->GetSnapRect();
/*N*/       }
/*N*/
/*N*/       // #105130# Old test for hit on BoundRect is completely wrong
/*N*/       // and never worked, doing it new here.
/*N*/       sal_Int32 nTolerance(nHitTolLog);
/*N*/       sal_Bool bBoundRectHit(sal_False);
/*N*/
/*N*/       if(pOut)
/*N*/       {
/*N*/           nTolerance = pOut->PixelToLogic(Size(2, 0)).Width();
/*N*/       }
/*N*/
/*N*/       if( (aP.X() >= aBoundRect.Left() - nTolerance && aP.X() <= aBoundRect.Left() + nTolerance)
/*N*/        || (aP.X() >= aBoundRect.Right() - nTolerance && aP.X() <= aBoundRect.Right() + nTolerance)
/*N*/        || (aP.Y() >= aBoundRect.Top() - nTolerance && aP.Y() <= aBoundRect.Top() + nTolerance)
/*N*/        || (aP.Y() >= aBoundRect.Bottom() - nTolerance && aP.Y() <= aBoundRect.Bottom() + nTolerance))
/*N*/       {
/*N*/           bBoundRectHit = sal_True;
/*N*/       }
/*N*/
/*N*/       if(!bBoundRectHit)
/*N*/       {
/*N*/           BOOL bTEHit=pHitObj->IsTextEditHit(aP,0,&pPV->GetVisibleLayers());
/*N*/
/*N*/           // TextEdit an Objekten im gesperrten Layer
/*N*/           if (pPV->GetLockedLayers().IsSet(pHitObj->GetLayer())) bTEHit=FALSE;
/*N*/           if (bTEHit) {
/*N*/               rVEvt.pRootObj=pObj;
/*N*/               pObj=pHitObj;
/*N*/               eHit=SDRHIT_TEXTEDITOBJ;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if (nHitPassNum!=SDRSEARCHPASS_DIRECT && eHit==SDRHIT_UNMARKEDOBJECT) {
/*N*/       eHit=SDRHIT_NONE;
/*N*/       pObj=NULL;
/*N*/       pPV=NULL;
/*N*/   }
/*N*/   BOOL bMouseLeft=(rVEvt.nMouseCode&MOUSE_LEFT)!=0;
/*N*/   BOOL bMouseRight=(rVEvt.nMouseCode&MOUSE_RIGHT)!=0;
/*N*/   BOOL bMouseDown=rVEvt.bMouseDown;
/*N*/   BOOL bMouseUp=rVEvt.bMouseUp;
/*N*/   SdrEventKind eEvent=SDREVENT_NONE;
/*N*/   BOOL bIsAction=IsAction();
/*N*/
/*N*/   if (bIsAction) {
/*?*/       if (bMouseDown) {
/*?*/           if (bMouseRight) eEvent=SDREVENT_BCKACTION;
/*?*/       } else if (bMouseUp) {
/*?*/           if (bMouseLeft) {
/*?*/               eEvent=SDREVENT_ENDACTION;
/*?*/               if (IsDragObj()) {
/*?*/                   eEvent=SDREVENT_ENDDRAG;
/*?*/                   rVEvt.bDragWithCopy=MODKEY_CopyDrag;
/*?*/               } else if (IsCreateObj() || IsInsObjPoint()) {
/*?*/                   eEvent=IsCreateObj() ? SDREVENT_ENDCREATE : SDREVENT_ENDINSOBJPOINT;
/*?*/                   rVEvt.eEndCreateCmd=SDRCREATE_NEXTPOINT;
/*?*/                   if (MODKEY_PolyPoly) rVEvt.eEndCreateCmd=SDRCREATE_NEXTOBJECT;
/*?*/                   if (rVEvt.nMouseClicks>1) rVEvt.eEndCreateCmd=SDRCREATE_FORCEEND;
/*?*/               } else if (IsMarking()) {
/*?*/                   eEvent=SDREVENT_ENDMARK;
/*?*/                   if (!aDragStat.IsMinMoved()) {
/*?*/                       eEvent=SDREVENT_BRKMARK;
/*?*/                       rVEvt.bAddMark=MODKEY_MultiMark;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       } else eEvent=SDREVENT_MOVACTION;
/*N*/   } else if (eHit==SDRHIT_TEXTEDIT) {
/*N*/       eEvent=SDREVENT_TEXTEDIT;
/*N*/   } else if (bMouseDown && bMouseLeft) {
/*N*/       if (rVEvt.nMouseClicks==2 && rVEvt.nMouseCode==MOUSE_LEFT && pObj!=NULL && pHitObj!=NULL && pHitObj->HasTextEdit() && eHit==SDRHIT_MARKEDOBJECT)
/*N*/       {
/*N*/           rVEvt.pRootObj=pObj;
/*N*/           pObj=pHitObj;
/*N*/           eEvent=SDREVENT_BEGTEXTEDIT;
/*N*/       }
/*N*/       else if (MODKEY_ForceMark && eHit!=SDRHIT_URLFIELD)
/*N*/       {
/*N*/           eEvent=SDREVENT_BEGMARK; // AddMark,Unmark */
/*N*/       }
/*N*/       else if (eHit==SDRHIT_HELPLINE) {
/*N*/           eEvent=SDREVENT_BEGDRAGHELPLINE; // nix weiter
/*N*/       } else if (eHit==SDRHIT_GLUEPOINT) {
/*N*/           eEvent=SDREVENT_MARKGLUEPOINT; // AddMark+Drag
/*N*/           rVEvt.bAddMark=MODKEY_MultiMark || MODKEY_DeepMark; // falls bei Deep nicht getroffen
/*N*/       } else if (eHit==SDRHIT_HANDLE) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            eEvent=SDREVENT_BEGDRAGOBJ;    // Mark+Drag,AddMark+Drag,DeepMark+Drag,Unmark
//STRIP001 /*?*/            BOOL bGlue=pHdl->GetKind()==HDL_GLUE;
//STRIP001 /*?*/            BOOL bPoly=!bGlue && IsPointMarkable(*pHdl);
//STRIP001 /*?*/            BOOL bMarked=bGlue || bPoly && pHdl->IsSelected();
//STRIP001 /*?*/            if (bGlue || bPoly) {
//STRIP001 /*?*/                eEvent=bGlue ? SDREVENT_MARKGLUEPOINT : SDREVENT_MARKPOINT;
//STRIP001 /*?*/                if (MODKEY_DeepMark) {
//STRIP001 /*?*/                    rVEvt.bAddMark=TRUE;
//STRIP001 /*?*/                    rVEvt.bPrevNextMark=TRUE;
//STRIP001 /*?*/                    rVEvt.bMarkPrev=MODKEY_DeepBackw;
//STRIP001 /*?*/                } else if (MODKEY_MultiMark) {
//STRIP001 /*?*/                    rVEvt.bAddMark=TRUE;
//STRIP001 /*?*/                    rVEvt.bUnmark=bMarked; // Toggle
//STRIP001 /*?*/                    if (bGlue) {
//STRIP001 /*?*/                        pObj=pHdl->GetObj();
//STRIP001 /*?*/                        nGlueId=pHdl->GetObjHdlNum();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                } else if (bMarked) eEvent=SDREVENT_BEGDRAGOBJ; // MarkState nicht aendern, nur Drag
//STRIP001 /*?*/            }
/*N*/       } else if (bInsPolyPt && (MODKEY_PolyPoly || (!MODKEY_MultiMark && !MODKEY_DeepMark))) {
/*?*/           eEvent=SDREVENT_BEGINSOBJPOINT;
/*?*/           rVEvt.bInsPointNewObj=MODKEY_PolyPoly;
/*N*/       } else if (bInsGluePt && !MODKEY_MultiMark && !MODKEY_DeepMark) {
/*?*/           eEvent=SDREVENT_BEGINSGLUEPOINT;
/*N*/       } else if (eHit==SDRHIT_TEXTEDITOBJ) {
/*?*/           eEvent=SDREVENT_BEGTEXTEDIT; // AddMark+Drag,DeepMark+Drag,Unmark
/*N*/           if (MODKEY_MultiMark || MODKEY_DeepMark) { // falls bei Deep nicht getroffen
/*N*/               eEvent=SDREVENT_MARKOBJ;
/*N*/           }
/*N*/       } else if (eHit==SDRHIT_MACRO) {
/*N*/           eEvent=SDREVENT_BEGMACROOBJ;       // AddMark+Drag
/*N*/           if (MODKEY_MultiMark || MODKEY_DeepMark) { // falls bei Deep nicht getroffen
/*N*/               eEvent=SDREVENT_MARKOBJ;
/*N*/           }
/*N*/       } else if (eHit==SDRHIT_URLFIELD) {
/*N*/           eEvent=SDREVENT_EXECUTEURL;       // AddMark+Drag
/*N*/           if (MODKEY_MultiMark || MODKEY_DeepMark) { // falls bei Deep nicht getroffen
/*N*/               eEvent=SDREVENT_MARKOBJ;
/*N*/           }
/*N*/       } else if (eHit==SDRHIT_MARKEDOBJECT) {
/*N*/           eEvent=SDREVENT_BEGDRAGOBJ; // DeepMark+Drag,Unmark
/*N*/           if (MODKEY_MultiMark || MODKEY_DeepMark) { // falls bei Deep nicht getroffen
/*N*/               eEvent=SDREVENT_MARKOBJ;
/*N*/           }
/*N*/       } else if (IsCreateMode()) {
/*N*/           eEvent=SDREVENT_BEGCREATEOBJ;          // Nix weiter
/*N*/       } else if (eHit==SDRHIT_UNMARKEDOBJECT) {
/*N*/           eEvent=SDREVENT_MARKOBJ;  // AddMark+Drag
/*N*/       } else eEvent=SDREVENT_BEGMARK;
/*N*/
/*N*/       if (eEvent==SDREVENT_MARKOBJ) {
/*N*/           rVEvt.bAddMark=MODKEY_MultiMark || MODKEY_DeepMark; // falls bei Deep nicht getroffen
/*N*/           rVEvt.bPrevNextMark=MODKEY_DeepMark;
/*N*/           rVEvt.bMarkPrev=MODKEY_DeepMark && MODKEY_DeepBackw;
/*N*/       }
/*N*/       if (eEvent==SDREVENT_BEGMARK) {
/*N*/           rVEvt.bAddMark=MODKEY_MultiMark;
/*N*/           rVEvt.bUnmark=MODKEY_Unmark;
/*N*/       }
/*N*/   }
/*N*/   rVEvt.bIsAction=bIsAction;
/*N*/   rVEvt.bIsTextEdit=bIsTextEdit;
/*N*/   rVEvt.bTextEditHit=bTextEditHit;
/*N*/   rVEvt.aLogicPos=aPnt;
/*N*/   rVEvt.pHdl=pHdl;
/*N*/   rVEvt.pObj=pObj;
/*N*/   if (rVEvt.pRootObj==NULL) rVEvt.pRootObj=pObj;
/*N*/   rVEvt.pPV=pPV;
/*N*/   rVEvt.nHlplIdx=nHlplIdx;
/*N*/   rVEvt.nGlueId=nGlueId;
/*N*/   rVEvt.eHit=eHit;
/*N*/   rVEvt.eEvent=eEvent;
/*N*/   rVEvt.bCaptureMouse=bMouseLeft && bMouseDown && eEvent!=SDREVENT_NONE;
/*N*/   rVEvt.bReleaseMouse=bMouseLeft && bMouseUp;
/*N*/ #if DGB_UTIL
/*N*/   if (rVEvt.pRootObj!=NULL) {
/*N*/       if (rVEvt.pRootObj->GetObjList()!=rVEvt.pPV->GetObjList()) {
/*N*/           DBG_ERROR("SdrView::PickAnything(): pRootObj->GetObjList()!=pPV->GetObjList() !");
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/   return eHit;
/*N*/ }

//STRIP001 BOOL SdrView::DoMouseEvent(const SdrViewEvent& rVEvt)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  SdrHitKind eHit=rVEvt.eHit;
//STRIP001  Point aLogicPos(rVEvt.aLogicPos);
//STRIP001
//STRIP001  BOOL bShift=(rVEvt.nMouseCode & KEY_SHIFT) !=0;
//STRIP001  BOOL bCtrl=(rVEvt.nMouseCode & KEY_MOD1) !=0;
//STRIP001  BOOL bAlt=(rVEvt.nMouseCode & KEY_MOD2) !=0;
//STRIP001  BOOL bMouseLeft=(rVEvt.nMouseCode&MOUSE_LEFT)!=0;
//STRIP001  BOOL bMouseRight=(rVEvt.nMouseCode&MOUSE_RIGHT)!=0;
//STRIP001  BOOL bMouseDown=rVEvt.bMouseDown;
//STRIP001  BOOL bMouseUp=rVEvt.bMouseUp;
//STRIP001  if (bMouseDown) {
//STRIP001      if (bMouseLeft) aDragStat.SetMouseDown(TRUE);
//STRIP001  } else if (bMouseUp) {
//STRIP001      if (bMouseLeft) aDragStat.SetMouseDown(FALSE);
//STRIP001  } else { // ansonsten MoueMove
//STRIP001      aDragStat.SetMouseDown(bMouseLeft);
//STRIP001  }
//STRIP001
//STRIP001 #ifdef MODKEY_NoSnap
//STRIP001  SetSnapEnabled(!MODKEY_NoSnap);
//STRIP001 #endif
//STRIP001 #ifdef MODKEY_Ortho
//STRIP001  SetOrtho(MODKEY_Ortho!=IsOrthoDesired());
//STRIP001 #endif
//STRIP001 #ifdef MODKEY_BigOrtho
//STRIP001  SetBigOrtho(MODKEY_BigOrtho);
//STRIP001 #endif
//STRIP001 #ifdef MODKEY_AngleSnap
//STRIP001  SetAngleSnapEnabled(MODKEY_AngleSnap);
//STRIP001 #endif
//STRIP001 #ifdef MODKEY_CopyDrag
//STRIP001  SetDragWithCopy(MODKEY_CopyDrag);
//STRIP001 #endif
//STRIP001 #ifdef MODKEY_Center
//STRIP001  SetCreate1stPointAsCenter(MODKEY_Center);
//STRIP001  SetResizeAtCenter(MODKEY_Center);
//STRIP001  SetCrookAtCenter(MODKEY_Center);
//STRIP001 #endif
//STRIP001  if (bMouseLeft && bMouseDown && rVEvt.bIsTextEdit && (eHit==SDRHIT_UNMARKEDOBJECT || eHit==SDRHIT_NONE)) {
//STRIP001      EndTextEdit(); // Danebengeklickt, Ende mit Edit
//STRIP001      // pHdl ist dann ungueltig. Sollte aber egal sein, wein pHdl==NULL
//STRIP001      // sein muesste (wg. eHit).
//STRIP001  }
//STRIP001  switch (rVEvt.eEvent) {
//STRIP001      case SDREVENT_NONE: bRet=FALSE; break;
//STRIP001      case SDREVENT_TEXTEDIT: bRet=FALSE; break; // Events an die OutlinerView werden hier nicht beruecksichtigt
//STRIP001      case SDREVENT_MOVACTION: MovAction(aLogicPos); bRet=TRUE; break;
//STRIP001      case SDREVENT_ENDACTION: EndAction(); bRet=TRUE; break;
//STRIP001      case SDREVENT_BCKACTION: BckAction(); bRet=TRUE; break;
//STRIP001      case SDREVENT_BRKACTION: BrkAction(); bRet=TRUE; break;
//STRIP001      case SDREVENT_ENDMARK  : EndAction(); bRet=TRUE; break;
//STRIP001      case SDREVENT_BRKMARK  : {
//STRIP001          BrkAction();
//STRIP001          if (!MarkObj(aLogicPos,nHitTolLog,rVEvt.bAddMark)) {
//STRIP001              // Kein Obj getroffen. Dann werden zuerst
//STRIP001              // - Markierte Klebepunkte deselektiert
//STRIP001              // - dann ggf. selektierte Polygonpunkte
//STRIP001              // - und ansonsten Objekte
//STRIP001              if (!rVEvt.bAddMark) UnmarkAll();
//STRIP001          }
//STRIP001          bRet=TRUE;
//STRIP001      } break;
//STRIP001      case SDREVENT_ENDCREATE: { // ggf. MarkObj
//STRIP001          SdrCreateCmd eCmd=SDRCREATE_NEXTPOINT;
//STRIP001          if (MODKEY_PolyPoly) eCmd=SDRCREATE_NEXTOBJECT;
//STRIP001          if (rVEvt.nMouseClicks>1) eCmd=SDRCREATE_FORCEEND;
//STRIP001          if (!EndCreateObj(eCmd)) { // Event fuer Create nicht ausgewerten? -> Markieren
//STRIP001              if (eHit==SDRHIT_UNMARKEDOBJECT || eHit==SDRHIT_TEXTEDIT) {
//STRIP001                  MarkObj(rVEvt.pRootObj,rVEvt.pPV);
//STRIP001                  if (eHit==SDRHIT_TEXTEDIT) {
//STRIP001                      BOOL bRet=pActualOutDev!=NULL && pActualOutDev->GetOutDevType()==OUTDEV_WINDOW &&
//STRIP001                                    BegTextEdit(rVEvt.pObj,rVEvt.pPV,(Window*)pActualOutDev,(SdrOutliner*)NULL);
//STRIP001                      if (bRet) {
//STRIP001                          MouseEvent aMEvt(pActualOutDev->LogicToPixel(aLogicPos),
//STRIP001                                           1,rVEvt.nMouseMode,rVEvt.nMouseCode,rVEvt.nMouseCode);
//STRIP001                          OutlinerView* pOLV=GetTextEditOutlinerView();
//STRIP001                          if (pOLV!=NULL) {
//STRIP001                              pOLV->MouseButtonDown(aMEvt); // Event an den Outliner, aber ohne Doppelklick
//STRIP001                              pOLV->MouseButtonUp(aMEvt); // Event an den Outliner, aber ohne Doppelklick
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  bRet=TRUE; // Obj markiert und ggf. TextEdit gestartet
//STRIP001              } else bRet=FALSE; // Create abgebrochen, sonst nix weiter.
//STRIP001          } else bRet=TRUE; // EndCreate mit TRUE returniert
//STRIP001      } break;
//STRIP001      case SDREVENT_ENDDRAG: {
//STRIP001          bRet=EndDragObj(IsDragWithCopy());
//STRIP001          ForceMarkedObjToAnotherPage(); // Undo+Klammerung fehlt noch !!!
//STRIP001      } break;
//STRIP001      case SDREVENT_MARKOBJ: { // + ggf. BegDrag
//STRIP001          if (!rVEvt.bAddMark) UnmarkAllObj();
//STRIP001          BOOL bUnmark=rVEvt.bUnmark;
//STRIP001          if (rVEvt.bPrevNextMark) {
//STRIP001              bRet=MarkNextObj(aLogicPos,nHitTolLog,rVEvt.bMarkPrev);
//STRIP001          } else {
//STRIP001              aMark.ForceSort();
//STRIP001              ULONG nAnz0=aMark.GetMarkCount();
//STRIP001              bRet=MarkObj(aLogicPos,nHitTolLog,rVEvt.bAddMark);
//STRIP001              aMark.ForceSort();
//STRIP001              ULONG nAnz1=aMark.GetMarkCount();
//STRIP001              bUnmark=nAnz1<nAnz0;
//STRIP001          }
//STRIP001          if (!bUnmark) {
//STRIP001              BegDragObj(aLogicPos,NULL,(SdrHdl*)NULL,nMinMovLog);
//STRIP001              bRet=TRUE;
//STRIP001          }
//STRIP001      } break;
//STRIP001      case SDREVENT_MARKPOINT: { // + ggf. BegDrag
//STRIP001          if (!rVEvt.bAddMark) UnmarkAllPoints();
//STRIP001          if (rVEvt.bPrevNextMark) {
//STRIP001              bRet=MarkNextPoint(aLogicPos,rVEvt.bMarkPrev);
//STRIP001          } else {
//STRIP001              bRet=MarkPoint(*rVEvt.pHdl,rVEvt.bUnmark);
//STRIP001          }
//STRIP001          if (!rVEvt.bUnmark && !rVEvt.bPrevNextMark) {
//STRIP001              BegDragObj(aLogicPos,NULL,rVEvt.pHdl,nMinMovLog);
//STRIP001              bRet=TRUE;
//STRIP001          }
//STRIP001      } break;
//STRIP001      case SDREVENT_MARKGLUEPOINT: { // + ggf. BegDrag
//STRIP001          if (!rVEvt.bAddMark) UnmarkAllGluePoints();
//STRIP001          if (rVEvt.bPrevNextMark) {
//STRIP001              bRet=MarkNextGluePoint(aLogicPos,rVEvt.bMarkPrev);
//STRIP001          } else {
//STRIP001              bRet=MarkGluePoint(rVEvt.pObj,rVEvt.nGlueId,rVEvt.pPV,rVEvt.bUnmark);
//STRIP001          }
//STRIP001          if (!rVEvt.bUnmark && !rVEvt.bPrevNextMark) {
//STRIP001              SdrHdl* pHdl=GetGluePointHdl(rVEvt.pObj,rVEvt.nGlueId);
//STRIP001              BegDragObj(aLogicPos,NULL,pHdl,nMinMovLog);
//STRIP001              bRet=TRUE;
//STRIP001          }
//STRIP001      } break;
//STRIP001      case SDREVENT_BEGMARK: bRet=BegMark(aLogicPos,rVEvt.bAddMark,rVEvt.bUnmark); break;
//STRIP001      case SDREVENT_BEGINSOBJPOINT: bRet=BegInsObjPoint(aLogicPos,MODKEY_PolyPoly); break;
//STRIP001      case SDREVENT_ENDINSOBJPOINT: {
//STRIP001          SdrCreateCmd eCmd=SDRCREATE_NEXTPOINT;
//STRIP001          if (MODKEY_PolyPoly) eCmd=SDRCREATE_NEXTOBJECT;
//STRIP001          if (rVEvt.nMouseClicks>1) eCmd=SDRCREATE_FORCEEND;
//STRIP001          EndInsObjPoint(eCmd);
//STRIP001          bRet=TRUE;
//STRIP001      } break;
//STRIP001      case SDREVENT_BEGINSGLUEPOINT: bRet=BegInsGluePoint(aLogicPos); break;
//STRIP001      case SDREVENT_BEGDRAGHELPLINE: bRet=BegDragHelpLine(rVEvt.nHlplIdx,rVEvt.pPV); break;
//STRIP001      case SDREVENT_BEGDRAGOBJ: bRet=BegDragObj(aLogicPos,NULL,rVEvt.pHdl,nMinMovLog); break;
//STRIP001      case SDREVENT_BEGCREATEOBJ: {
//STRIP001          if (nAktInvent==SdrInventor && nAktIdent==OBJ_CAPTION) {
//STRIP001              long nHgt=SdrEngineDefaults::GetFontHeight();
//STRIP001              bRet=BegCreateCaptionObj(aLogicPos,Size(5*nHgt,2*nHgt));
//STRIP001          } else bRet=BegCreateObj(aLogicPos);
//STRIP001      } break;
//STRIP001      case SDREVENT_BEGMACROOBJ: bRet=BegMacroObj(aLogicPos,nHitTolLog,rVEvt.pObj,rVEvt.pPV,(Window*)pActualOutDev); break;
//STRIP001      case SDREVENT_BEGTEXTEDIT: {
//STRIP001          if (!IsObjMarked(rVEvt.pObj)) {
//STRIP001              UnmarkAllObj();
//STRIP001              MarkObj(rVEvt.pRootObj,rVEvt.pPV);
//STRIP001          }
//STRIP001          bRet=pActualOutDev!=NULL && pActualOutDev->GetOutDevType()==OUTDEV_WINDOW &&
//STRIP001               BegTextEdit(rVEvt.pObj,rVEvt.pPV,(Window*)pActualOutDev,(SdrOutliner*)NULL);
//STRIP001          if (bRet) {
//STRIP001              MouseEvent aMEvt(pActualOutDev->LogicToPixel(aLogicPos),
//STRIP001                               1,rVEvt.nMouseMode,rVEvt.nMouseCode,rVEvt.nMouseCode);
//STRIP001              OutlinerView* pOLV=GetTextEditOutlinerView();
//STRIP001              if (pOLV!=NULL) pOLV->MouseButtonDown(aMEvt); // Event an den Outliner, aber ohne Doppelklick
//STRIP001          }
//STRIP001      } break;
//STRIP001  } // switch
//STRIP001  if (bRet && pActualOutDev!=NULL && pActualOutDev->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001      Window* pWin=(Window*)pActualOutDev;
//STRIP001      // Maus links gedrueckt?
//STRIP001      BOOL bLeftDown=(rVEvt.nMouseCode&MOUSE_LEFT)!=0 && rVEvt.bMouseDown;
//STRIP001      // Maus links losgelassen?
//STRIP001      BOOL bLeftUp=(rVEvt.nMouseCode&MOUSE_LEFT)!=0 && rVEvt.bMouseUp;
//STRIP001      // Maus links gedrueckt oder gehalten?
//STRIP001      BOOL bLeftDown1=(rVEvt.nMouseCode&MOUSE_LEFT)!=0 && !rVEvt.bMouseUp;
//STRIP001      pWin->SetPointer(GetPreferedPointer(rVEvt.aLogicPos,pWin,
//STRIP001              rVEvt.nMouseCode & (KEY_SHIFT|KEY_MOD1|KEY_MOD2),bLeftDown1));
//STRIP001      BOOL bAction=IsAction();
//STRIP001      if (bLeftDown && bAction) pWin->CaptureMouse();
//STRIP001      else if (bLeftUp || (rVEvt.bIsAction && !bAction)) pWin->ReleaseMouse();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

#ifndef _OUTLOBJ_HXX
#include "outlobj.hxx"
#endif

/*N*/ Pointer SdrView::GetPreferedPointer(const Point& rMousePos, const OutputDevice* pOut, USHORT nModifier, BOOL bLeftDown) const
/*N*/ {
/*N*/   // Actions
/*N*/   if (IsCreateObj()) {
/*?*/       if (pLibObjDragMeth!=NULL) {
/*?*/           return Pointer(POINTER_CROSS);
/*?*/       } else {
/*?*/           return pAktCreate->GetCreatePointer();
/*?*/       }
/*N*/   }
/*N*/   if (pDragBla!=NULL) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if ((IsDraggingPoints() || IsDraggingGluePoints()) && IsMouseHideWhileDraggingPoints()) return Pointer(POINTER_NULL);
//STRIP001 /*?*/        return pDragBla->GetPointer();
/*N*/   }
/*N*/   if (IsMarkObj() || IsMarkPoints() || IsMarkGluePoints() || IsEncirclement() || IsSetPageOrg()) return Pointer(POINTER_ARROW);
/*N*/   if (IsDragHelpLine()) {DBG_ASSERT(0, "STRIP"); }//STRIP001 return GetDraggedHelpLine().GetPointer();
/*N*/   if (IsMacroObj()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrObjMacroHitRec aHitRec;
//STRIP001 /*?*/        aHitRec.aPos=pOut->LogicToPixel(rMousePos);
//STRIP001 /*?*/        aHitRec.aDownPos=aMacroDownPos;
//STRIP001 /*?*/        aHitRec.nTol=nMacroTol;
//STRIP001 /*?*/        aHitRec.pVisiLayer=&pMacroPV->GetVisibleLayers();
//STRIP001 /*?*/        aHitRec.pPageView=pMacroPV;
//STRIP001 /*?*/        aHitRec.pOut=pMacroWin;
//STRIP001 /*?*/        aHitRec.bDown=bMacroDown;
//STRIP001 /*?*/        return pMacroObj->GetMacroPointer(aHitRec);
/*N*/   }
/*N*/   USHORT nTol=nHitTolLog;
/*N*/   // TextEdit, ObjEdit, Macro
/*N*/   if (IsTextEdit() && (IsTextEditInSelectionMode() || IsTextEditHit(rMousePos,0/*nTol*/)))
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 if(!pOut || IsTextEditInSelectionMode())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if(pTextEditOutliner->IsVertical())
//STRIP001 /*?*/                return Pointer(POINTER_TEXT_VERTICAL);
//STRIP001 /*?*/            else
//STRIP001 /*?*/                return Pointer(POINTER_TEXT);
//STRIP001 /*?*/        }
//STRIP001 /*?*/        // hier muss besser der Outliner was liefern:
//STRIP001 /*?*/        Point aPos(pOut->LogicToPixel(rMousePos));
//STRIP001 /*?*/        Pointer aPointer(pTextEditOutlinerView->GetPointer(aPos));
//STRIP001 /*?*/        if (aPointer==POINTER_ARROW)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if(pTextEditOutliner->IsVertical())
//STRIP001 /*?*/                aPointer = POINTER_TEXT_VERTICAL;
//STRIP001 /*?*/            else
//STRIP001 /*?*/                aPointer = POINTER_TEXT;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        return aPointer;
/*N*/   }

/*N*/   SdrViewEvent aVEvt;
/*N*/   aVEvt.nMouseCode=(nModifier&(KEY_SHIFT|KEY_MOD1|KEY_MOD2))|MOUSE_LEFT; // um zu sehen, was bei MouseLeftDown passieren wuerde
/*N*/   aVEvt.bMouseDown=!bLeftDown; // Was waere wenn ...
/*N*/   aVEvt.bMouseUp=bLeftDown;    // Was waere wenn ...
/*N*/   if (pOut!=NULL) ((SdrView*)this)->SetActualWin(pOut);
/*N*/   SdrHitKind eHit=PickAnything(rMousePos,aVEvt);
/*N*/   SdrEventKind eEvent=aVEvt.eEvent;
/*N*/   switch (eEvent) {
/*N*/       case SDREVENT_BEGCREATEOBJ: return aAktCreatePointer;
/*N*/       case SDREVENT_MARKOBJ: case SDREVENT_BEGMARK: return Pointer(POINTER_ARROW);
/*N*/       case SDREVENT_MARKPOINT: case SDREVENT_MARKGLUEPOINT: return Pointer(POINTER_MOVEPOINT);
/*N*/       case SDREVENT_BEGINSOBJPOINT: case SDREVENT_BEGINSGLUEPOINT: return Pointer(POINTER_CROSS);
/*N*/       case SDREVENT_EXECUTEURL: return Pointer(POINTER_REFHAND);
/*N*/       case SDREVENT_BEGMACROOBJ: {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            SdrObjMacroHitRec aHitRec;
//STRIP001 /*?*/            aHitRec.aPos=aVEvt.aLogicPos;
//STRIP001 /*?*/            aHitRec.aDownPos=aHitRec.aPos;
//STRIP001 /*?*/            aHitRec.nTol=nHitTolLog;
//STRIP001 /*?*/            aHitRec.pVisiLayer=&aVEvt.pPV->GetVisibleLayers();
//STRIP001 /*?*/            aHitRec.pPageView=aVEvt.pPV;
//STRIP001 /*?*/            aHitRec.pOut=(OutputDevice*)pOut;
//STRIP001 /*?*/            return aVEvt.pObj->GetMacroPointer(aHitRec);
/*N*/       }
/*N*/   } // switch

/*N*/   switch(eHit)
/*N*/   {
/*N*/       case SDRHIT_HELPLINE :
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 return aVEvt.pPV->GetHelpLines()[aVEvt.nHlplIdx].GetPointer();
/*N*/       case SDRHIT_GLUEPOINT:
/*N*/           return Pointer(POINTER_MOVEPOINT);
/*N*/       case SDRHIT_TEXTEDIT :
/*N*/       case SDRHIT_TEXTEDITOBJ:
/*N*/       {
/*N*/           if(aVEvt.pObj && aVEvt.pObj->ISA(SdrTextObj))
/*N*/           {
/*N*/               SdrTextObj* pText = (SdrTextObj*)aVEvt.pObj;
/*N*/               if(pText->HasText())
/*N*/               {
/*N*/                   OutlinerParaObject* pParaObj = pText->GetOutlinerParaObject();
/*N*/                   if(pParaObj && pParaObj->IsVertical())
/*N*/                       return Pointer(POINTER_TEXT_VERTICAL);
/*N*/               }
/*N*/           }
/*N*/           return Pointer(POINTER_TEXT);
/*N*/       }
/*N*/   }

/*?*/   BOOL bMarkHit=eHit==SDRHIT_MARKEDOBJECT;
/*?*/   SdrHdl* pHdl=aVEvt.pHdl;
/*?*/   // Nun die Pointer fuer Dragging checken
/*?*/   if (pHdl!=NULL || bMarkHit) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrHdlKind eHdl= pHdl!=NULL ? pHdl->GetKind() : HDL_MOVE;
//STRIP001 /*?*/        BOOL bCorner=pHdl!=NULL && pHdl->IsCornerHdl();
//STRIP001 /*?*/        BOOL bVertex=pHdl!=NULL && pHdl->IsVertexHdl();
//STRIP001 /*?*/        BOOL bMov=eHdl==HDL_MOVE;
//STRIP001 /*?*/        if (bMov && (eDragMode==SDRDRAG_MOVE || eDragMode==SDRDRAG_RESIZE || bMarkedHitMovesAlways)) {
//STRIP001 /*?*/            if (!IsMoveAllowed()) return Pointer(POINTER_ARROW); // weil Doppelklick oder Drag&Drop moeglich
//STRIP001 /*?*/            return Pointer(POINTER_MOVE);
//STRIP001 /*?*/        }
//STRIP001 /*?*/        switch (eDragMode) {
//STRIP001 /*?*/            case SDRDRAG_ROTATE: {
//STRIP001 /*?*/                if ((bCorner || bMov) && !IsRotateAllowed(TRUE))
//STRIP001 /*?*/                    return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/
//STRIP001 /*?*/                // Sind 3D-Objekte selektiert?
//STRIP001 /*?*/                BOOL b3DObjSelected = FALSE;
//STRIP001 /*?*/ #ifndef SVX_LIGHT
//STRIP001 /*?*/                for (UINT32 a=0; !b3DObjSelected && a<aMark.GetMarkCount(); a++) {
//STRIP001 /*?*/                    SdrObject* pObj = aMark.GetMark(a)->GetObj();
//STRIP001 /*?*/                    if(pObj && pObj->ISA(E3dObject))
//STRIP001 /*?*/                        b3DObjSelected = TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/                // Falls es um ein 3D-Objekt geht, muss trotz !IsShearAllowed
//STRIP001 /*?*/                // weitergemacht werden, da es sich um eine Rotation statt um
//STRIP001 /*?*/                // einen Shear handelt
//STRIP001 /*?*/                if (bVertex && !IsShearAllowed() && !b3DObjSelected)
//STRIP001 /*?*/                    return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/                if (bMov)
//STRIP001 /*?*/                    return Pointer(POINTER_ROTATE);
//STRIP001 /*?*/            } break;
//STRIP001 /*?*/            case SDRDRAG_SHEAR: case SDRDRAG_DISTORT: {
//STRIP001 /*?*/                if (bCorner) {
//STRIP001 /*?*/                    if (!IsDistortAllowed(TRUE) && !IsDistortAllowed(FALSE)) return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/                    else return Pointer(POINTER_REFHAND);
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if (bVertex && !IsShearAllowed()) return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/                if (bMov) {
//STRIP001 /*?*/                    if (!IsMoveAllowed()) return Pointer(POINTER_ARROW); // weil Doppelklick oder Drag&Drop moeglich
//STRIP001 /*?*/                    return Pointer(POINTER_MOVE);
//STRIP001 /*?*/                }
//STRIP001 /*?*/            } break;
//STRIP001 /*?*/            case SDRDRAG_MIRROR: {
//STRIP001 /*?*/                if (bCorner || bVertex || bMov) {
//STRIP001 /*?*/                    SdrHdl* pH1=aHdl.GetHdl(HDL_REF1);
//STRIP001 /*?*/                    SdrHdl* pH2=aHdl.GetHdl(HDL_REF2);
//STRIP001 /*?*/                    BOOL b90=FALSE;
//STRIP001 /*?*/                    BOOL b45=FALSE;
//STRIP001 /*?*/                    Point aDif;
//STRIP001 /*?*/                    if (pH1!=NULL && pH2!=NULL) {
//STRIP001 /*?*/                        aDif=pH2->GetPos()-pH1->GetPos();
//STRIP001 /*?*/                        b90=(aDif.X()==0) || aDif.Y()==0;
//STRIP001 /*?*/                        b45=b90 || (Abs(aDif.X())==Abs(aDif.Y()));
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    BOOL bNo=FALSE;
//STRIP001 /*?*/                    if (!IsMirrorAllowed(TRUE,TRUE)) bNo=TRUE; // Spiegeln ueberhaupt nicht erlaubt
//STRIP001 /*?*/                    if (!IsMirrorAllowed(FALSE,FALSE) && !b45) bNo=TRUE; // freies Spiegeln nicht erlaubt
//STRIP001 /*?*/                    if (!IsMirrorAllowed(TRUE,FALSE) && !b90) bNo=TRUE;  // Spiegeln hor/ver erlaubt
//STRIP001 /*?*/                    if (bNo) return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/                    if (b90) {
//STRIP001 /*?*/                        return Pointer(POINTER_MIRROR);
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    return Pointer(POINTER_MIRROR);
//STRIP001 /*?*/                }
//STRIP001 /*?*/            } break;
//STRIP001 /*?*/
//STRIP001 /*?*/            case SDRDRAG_TRANSPARENCE:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if(!IsTransparenceAllowed())
//STRIP001 /*?*/                    return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/
//STRIP001 /*?*/                return Pointer(POINTER_REFHAND);
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            case SDRDRAG_GRADIENT:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if(!IsGradientAllowed())
//STRIP001 /*?*/                    return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/
//STRIP001 /*?*/                return Pointer(POINTER_REFHAND);
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            case SDRDRAG_CROOK: {
//STRIP001 /*?*/                if (bCorner || bVertex || bMov) {
//STRIP001 /*?*/                    if (!IsCrookAllowed(TRUE) && !IsCrookAllowed(FALSE)) return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/                    return Pointer(POINTER_CROOK); break;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            default: {
//STRIP001 /*?*/                if ((bCorner || bVertex) && !IsResizeAllowed(TRUE)) return Pointer(POINTER_NOTALLOWED);
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if (pHdl!=NULL) return pHdl->GetPointer();
//STRIP001 /*?*/        if (bMov) {
//STRIP001 /*?*/            if (!IsMoveAllowed()) return Pointer(POINTER_ARROW); // weil Doppelklick oder Drag&Drop moeglich
//STRIP001 /*?*/            return Pointer(POINTER_MOVE);
//STRIP001 /*?*/        }
/*?*/   }
/*?*/   if (eEditMode==SDREDITMODE_CREATE) return aAktCreatePointer;
/*?*/   return Pointer(POINTER_ARROW);
/*N*/ }

/*N*/ XubString SdrView::GetStatusText()
/*N*/ {
/*N*/   XubString aStr;
/*N*/   XubString aName;
/*N*/
/*N*/   aStr.AppendAscii("nix");
/*N*/
/*N*/   if (pAktCreate!=NULL) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        aStr=pAktCreate->GetDragComment(aDragStat,FALSE,TRUE);
//STRIP001 /*?*/
//STRIP001 /*?*/        if(!aStr.Len())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pAktCreate->TakeObjNameSingul(aName);
//STRIP001 /*?*/            aStr = ImpGetResStr(STR_ViewCreateObj);
//STRIP001 /*?*/        }
/*N*/   } else if (pDragBla!=NULL) {
/*?*/       if (bInsPolyPoint || IsInsertGluePoint()) {
/*?*/           aStr=aInsPointUndoStr;
/*N*/       } else {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            if (aDragStat.IsMinMoved()) {
//STRIP001 /*?*/                pDragBla->TakeComment(aStr);
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   } else if (bMarking) {
/*?*/       if (HasMarkedObj()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            aStr=ImpGetResStr(STR_ViewMarkMoreObjs);
/*?*/       } else {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            aStr=ImpGetResStr(STR_ViewMarkObjs);
/*N*/       }
/*N*/   } else if (bMarkingPoints) {
/*?*/       if (HasMarkedPoints()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            aStr=ImpGetResStr(STR_ViewMarkMorePoints);
/*N*/       } else {
/*N*/           aStr=ImpGetResStr(STR_ViewMarkPoints);
/*N*/       }
/*N*/   } else if (bMarkingGluePoints) {
/*?*/       if (HasMarkedGluePoints()) {
/*?*/           aStr=ImpGetResStr(STR_ViewMarkMoreGluePoints);
/*N*/       } else {
/*?*/           aStr=ImpGetResStr(STR_ViewMarkGluePoints);
/*N*/       }
/*N*/   } else if (IsTextEdit() && pTextEditOutlinerView!=NULL) {
/*?*/       aStr=ImpGetResStr(STR_ViewTextEdit); // "TextEdit - Zeile y  Spalte x";
/*?*/       ESelection aSel(pTextEditOutlinerView->GetSelection());
/*?*/       long nPar=aSel.nEndPara,nLin=0,nCol=aSel.nEndPos;
/*?*/       if (aSel.nEndPara>0) {
/*?*/           for (USHORT nParaNum=0; nParaNum<aSel.nEndPara; nParaNum++) {
/*?*/               nLin+=pTextEditOutliner->GetLineCount(nParaNum);
/*?*/           }
/*?*/       }
/*?*/       // Noch 'ne kleine Unschoenheit:
/*?*/       // Am Ende einer Zeile eines mehrzeiligen Absatzes wird die Position
/*?*/       // der naechsten Zeile des selben Absatzes angezeigt, so es eine solche
/*?*/       // gibt.
/*?*/       USHORT nParaLine=0;
/*?*/       ULONG nParaLineAnz=pTextEditOutliner->GetLineCount(aSel.nEndPara);
/*?*/       BOOL bBrk=FALSE;
/*?*/       while (!bBrk) {
/*?*/           USHORT nLen=pTextEditOutliner->GetLineLen(aSel.nEndPara,nParaLine);
/*?*/           BOOL bLastLine=(nParaLine==nParaLineAnz-1);
/*?*/           if (nCol>nLen || (!bLastLine && nCol==nLen)) {
/*?*/               nCol-=nLen;
/*?*/               nLin++;
/*?*/               nParaLine++;
/*?*/           } else bBrk=TRUE;
/*?*/           if (nLen==0) bBrk=TRUE; // Sicherheitshalber
/*?*/       }
/*?*/
/*?*/       aStr.SearchAndReplaceAscii("%a", UniString::CreateFromInt32(nPar + 1));
/*?*/       aStr.SearchAndReplaceAscii("%z", UniString::CreateFromInt32(nLin + 1));
/*?*/       aStr.SearchAndReplaceAscii("%s", UniString::CreateFromInt32(nCol + 1));
/*N*/   }
/*N*/
/*N*/   if(aStr.EqualsAscii("nix"))
/*N*/   {
/*?*/       if (HasMarkedObj()) {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 ImpTakeDescriptionStr(STR_ViewMarked,aStr);
//STRIP001 /*?*/            if (IsGluePointEditMode()) {
//STRIP001 /*?*/                if (HasMarkedGluePoints()) {
//STRIP001 /*?*/                    ImpTakeDescriptionStr(STR_ViewMarked,aStr,0,IMPSDR_GLUEPOINTSDESCRIPTION);
//STRIP001 /*?*/                }
//STRIP001 /*?*/            } else {
//STRIP001 /*?*/                if (HasMarkedPoints()) {
//STRIP001 /*?*/                    ImpTakeDescriptionStr(STR_ViewMarked,aStr,0,IMPSDR_POINTSDESCRIPTION);
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*?*/       } else {
/*?*/           aStr.Erase();
/*?*/       }
/*N*/   }
/*N*/   else if(aName.Len())
/*N*/   {
/*?*/       aStr.SearchAndReplaceAscii("%O", aName);
/*N*/   }
/*N*/
/*N*/   if(aStr.Len())
/*N*/   {
/*?*/       // ersten Buchstaben gross schreiben
/*?*/       String aTmpStr(aStr.Copy(0, 1));
/*?*/       aTmpStr.ToUpperAscii();
/*?*/       aStr.Replace(0, 1, aTmpStr);
/*N*/   }
/*N*/   return aStr;
/*N*/ }

/*N*/ SdrViewContext SdrView::GetContext() const
/*N*/ {
/*N*/   if( IsTextEdit() )
/*N*/       return SDRCONTEXT_TEXTEDIT;
/*N*/
/*N*/   if( IsGluePointEditMode() )
/*N*/       return SDRCONTEXT_GLUEPOINTEDIT;
/*N*/
/*N*/   const ULONG nMarkAnz = aMark.GetMarkCount();
/*N*/
/*N*/   if( HasMarkablePoints() && !IsFrameHandles() )
/*N*/   {
/*?*/       BOOL bPath=TRUE;
/*?*/       for( ULONG nMarkNum = 0; nMarkNum < nMarkAnz && bPath; nMarkNum++ )
/*?*/           if (!aMark.GetMark(nMarkNum)->GetObj()->ISA(SdrPathObj))
/*?*/               bPath=FALSE;
/*?*/
/*?*/       if( bPath )
/*?*/           return SDRCONTEXT_POINTEDIT;
/*N*/   }
/*N*/
/*N*/   if( aMark.GetMarkCount() )
/*N*/   {
/*?*/       BOOL bGraf = TRUE;
/*?*/       for( ULONG nMarkNum = 0; nMarkNum < nMarkAnz && bGraf; nMarkNum++ )
/*?*/       {
/*?*/           const SdrObject* pMarkObj = aMark.GetMark( nMarkNum )->GetObj();
/*?*/
/*?*/           if( !pMarkObj->ISA( SdrGrafObj ) )
/*?*/               bGraf = FALSE;
/*?*/       }
/*?*/
/*?*/       if( bGraf )
/*?*/           return SDRCONTEXT_GRAPHIC;
/*N*/   }
/*N*/
/*N*/   return SDRCONTEXT_STANDARD;
/*N*/ }

//STRIP001 void SdrView::MarkAll()
//STRIP001 {
//STRIP001  if (IsTextEdit()) {
//STRIP001      GetTextEditOutlinerView()->SetSelection(ESelection(0,0,0xFFFF,0xFFFF));
//STRIP001 #ifndef SVX_LIGHT
//STRIP001      if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001  } else if (IsGluePointEditMode()) MarkAllGluePoints();
//STRIP001  else if (HasMarkablePoints()) MarkAllPoints();
//STRIP001  else MarkAllObj();
//STRIP001 }

/*N*/ void SdrView::UnmarkAll()
/*N*/ {
/*N*/   if (IsTextEdit()) {
/*?*/       ESelection eSel=GetTextEditOutlinerView()->GetSelection();
/*?*/       eSel.nStartPara=eSel.nEndPara;
/*?*/       eSel.nStartPos=eSel.nEndPos;
/*?*/       GetTextEditOutlinerView()->SetSelection(eSel);
/*?*/ #ifndef SVX_LIGHT
/*?*/       if (pItemBrowser!=NULL) {DBG_ASSERT(0, "STRIP");} //STRIP001 pItemBrowser->SetDirty();
/*?*/ #endif
/*N*/   } else if (HasMarkedGluePoints()) UnmarkAllGluePoints();
/*N*/   else if (HasMarkedPoints()) {DBG_ASSERT(0, "STRIP"); }//STRIP001 UnmarkAllPoints(); // ! Marked statt Markable !
/*N*/   else UnmarkAllObj();
/*N*/ }

//STRIP001 BOOL SdrView::IsAllMarked() const
//STRIP001 {
//STRIP001  if (IsTextEdit()) {
//STRIP001      return ImpIsTextEditAllSelected();
//STRIP001  }
//STRIP001  if (IsGluePointEditMode()) {
//STRIP001      ULONG nAnz=GetMarkableGluePointCount();
//STRIP001      return nAnz!=0 && nAnz==GetMarkedGluePointCount();
//STRIP001  }
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      ULONG nAnz=GetMarkablePointCount();
//STRIP001      return nAnz!=0 && nAnz==GetMarkedPointCount();
//STRIP001  }
//STRIP001  ULONG nAnz=GetMarkableObjCount();
//STRIP001  return nAnz!=0 && nAnz==GetMarkedObjCount();
//STRIP001 }

//STRIP001 BOOL SdrView::IsMarkPossible() const
//STRIP001 {
//STRIP001  if (IsTextEdit()) {
//STRIP001      Paragraph* p1stPara=pTextEditOutliner->GetParagraph( 0 );
//STRIP001      ULONG nParaAnz=pTextEditOutliner->GetParagraphCount();
//STRIP001      if (p1stPara==NULL) nParaAnz=0;
//STRIP001      if (nParaAnz==1) { // bei nur einem Para nachsehen ob da ueberhaupt was drin steht
//STRIP001          XubString aStr(pTextEditOutliner->GetText(p1stPara));
//STRIP001
//STRIP001          // Aha, steht nix drin!
//STRIP001          if(!aStr.Len())
//STRIP001              nParaAnz = 0;
//STRIP001      }
//STRIP001      return nParaAnz!=0;
//STRIP001  }
//STRIP001  if (IsGluePointEditMode()) {
//STRIP001      return HasMarkableGluePoints();
//STRIP001  }
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      return HasMarkablePoints();
//STRIP001  }
//STRIP001  return HasMarkableObj();
//STRIP001 }

//STRIP001 BOOL SdrView::IsAllMarkPrevNextPossible() const
//STRIP001 {
//STRIP001  if (IsTextEdit()) {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  if (IsGluePointEditMode()) {
//STRIP001      return HasMarkableGluePoints();
//STRIP001  }
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      return HasMarkablePoints();
//STRIP001  }
//STRIP001  return HasMarkableObj();
//STRIP001 }

//STRIP001 BOOL SdrView::MarkNext(BOOL bPrev)
//STRIP001 {
//STRIP001  if (IsTextEdit()) {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  if (IsGluePointEditMode() && HasMarkedGluePoints()) {
//STRIP001      return MarkNextGluePoint(bPrev);
//STRIP001  }
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      return MarkNextPoint(bPrev);
//STRIP001  }
//STRIP001  return MarkNextObj(bPrev);
//STRIP001 }

//STRIP001 BOOL SdrView::MarkNext(const Point& rPnt, BOOL bPrev)
//STRIP001 {
//STRIP001  if (IsTextEdit()) {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  if (IsGluePointEditMode() && HasMarkedGluePoints()) {
//STRIP001      //return MarkNextGluePoint(rPnt,bPrev); fehlende Implementation !!!
//STRIP001  }
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      //return MarkNextPoint(rPnt,bPrev);     fehlende Implementation !!!
//STRIP001  }
//STRIP001  return MarkNextObj(rPnt,-2,bPrev);
//STRIP001 }

//STRIP001 const Rectangle& SdrView::GetMarkedRect() const
//STRIP001 {
//STRIP001  if (IsGluePointEditMode() && HasMarkedGluePoints()) {
//STRIP001      return GetMarkedGluePointsRect();
//STRIP001  }
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      return GetMarkedPointsRect();
//STRIP001  }
//STRIP001  return GetMarkedObjRect();
//STRIP001 }

//STRIP001 void SdrView::SetMarkedRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  if (IsGluePointEditMode() && HasMarkedGluePoints()) {
//STRIP001      //SetMarkedGluePointsRect(rRect); fehlende Implementation !!!
//STRIP001  } else if (HasMarkedPoints()) {
//STRIP001      //SetMarkedPointsRect(rRect);     fehlende Implementation !!!
//STRIP001  } else SetMarkedObjRect(rRect);
//STRIP001 }

/*N*/ void SdrView::DeleteMarked()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (IsTextEdit()) {
//STRIP001      SdrObjEditView::KeyInput(KeyEvent(0,KeyCode(KEYFUNC_DELETE)),pTextEditWin);
//STRIP001  } else {
//STRIP001      if (IsGluePointEditMode() && HasMarkedGluePoints()) {
//STRIP001          DeleteMarkedGluePoints();
//STRIP001      } else if (GetContext()==SDRCONTEXT_POINTEDIT && HasMarkedPoints()) {
//STRIP001          DeleteMarkedPoints();
//STRIP001      } else {
//STRIP001          DeleteMarkedObj();
//STRIP001      }
//STRIP001  }
/*N*/ }

//STRIP001 BOOL SdrView::BegMark(const Point& rPnt, BOOL bAddMark, BOOL bUnmark)
//STRIP001 {
//STRIP001  if (bUnmark) bAddMark=TRUE;
//STRIP001  if (IsGluePointEditMode()) {
//STRIP001      if (!bAddMark) UnmarkAllGluePoints();
//STRIP001      return BegMarkGluePoints(rPnt,bUnmark);
//STRIP001  } else if (HasMarkablePoints()) {
//STRIP001      if (!bAddMark) UnmarkAllPoints();
//STRIP001      return BegMarkPoints(rPnt,bUnmark);
//STRIP001  } else {
//STRIP001      if (!bAddMark) UnmarkAllObj();
//STRIP001      return BegMarkObj(rPnt,bUnmark);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrView::IsDeleteMarkedPossible() const
//STRIP001 {
//STRIP001  if (IsReadOnly()) return FALSE;
//STRIP001  if (IsTextEdit()) return TRUE;
//STRIP001  if (IsGluePointEditMode() && HasMarkedGluePoints()) return TRUE;
//STRIP001  if (HasMarkedPoints()) return TRUE;
//STRIP001  return IsDeleteMarkedObjPossible();
//STRIP001 }

/*N*/ void SdrView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   {
/*N*/       // Der CharSet muss! als erstes rausgestreamt werden
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCHARSET);
/*N*/
/*N*/       // UNICODE:
/*N*/       // rtl_TextEncoding eOutCharSet=rOut.GetStreamCharSet();
/*N*/       rtl_TextEncoding eOutCharSet = gsl_getSystemTextEncoding();
/*N*/
/*N*/       // #90477# rOut << UINT16( GetStoreCharSet( eOutCharSet ) );
/*N*/       rOut << (UINT16)GetSOStoreTextEncoding(eOutCharSet, (sal_uInt16)rOut.GetVersion());
/*N*/   }
/*N*/   SdrCreateView::WriteRecords(rOut);
/*N*/ }

/*N*/ BOOL SdrView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWCHARSET: {
/*N*/               UINT16 nCharSet;
/*N*/               // #90477# rIn>>nCharSet;
/*N*/               // rIn.SetStreamCharSet(rtl_TextEncoding(nCharSet));
/*N*/               rIn >> nCharSet;
/*N*/               rIn.SetStreamCharSet(GetSOLoadTextEncoding((rtl_TextEncoding)nCharSet, (sal_uInt16)rIn.GetVersion()));
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrCreateView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrView& rView)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOViewID);
/*N*/   rView.WriteRecords(rOut);
/*N*/   return rOut;
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrView& rView)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return rIn;
/*N*/   rView.BrkAction();
/*N*/   rView.Clear();
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   if (!aHead.IsMagic()) {
/*N*/       rIn.SetError(SVSTREAM_FILEFORMAT_ERROR); // Format-Fehler
/*N*/       return rIn;
/*N*/   }
/*N*/   rtl_TextEncoding eStreamCharSetMerker=rIn.GetStreamCharSet(); // Der StreamCharSet wird von SdrView::ReadRecord() gesetzt
/*N*/   while (aHead.GetBytesLeft()>0 && rIn.GetError()==0 && !rIn.IsEof()) {
/*N*/       SdrNamedSubRecord aSubRecord(rIn,STREAM_READ);
/*N*/       rView.ReadRecord(aHead,aSubRecord,rIn);
/*N*/   }
/*N*/
/*N*/   rIn.SetStreamCharSet(eStreamCharSetMerker); // StreamCharSet wieder restaurieren
/*N*/
/*N*/   rView.InvalidateAllWin();
/*N*/   return rIn;
/*N*/ }


/*N*/ void SdrView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   if( rHint.ISA( SfxSimpleHint ) && ( (SfxSimpleHint&) rHint ).GetId() == SFX_HINT_ACCESSIBILITY_CHANGED )
/*N*/   {
/*?*/       onAccessibilityOptionsChanged();
/*N*/   }
/*N*/
/*N*/   SdrCreateView::SFX_NOTIFY(rBC, rBCType, rHint, rHintType );
/*N*/ }

//STRIP001 SvtAccessibilityOptions& SdrView::getAccessibilityOptions()
//STRIP001 {
//STRIP001  return maAccessibilityOptions;
//STRIP001 }

/** method is called whenever the global SvtAccessibilityOptions is changed */
/*N*/ void SdrView::onAccessibilityOptionsChanged()
/*N*/ {
/*N*/ }

