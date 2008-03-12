/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdview.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:41:07 $
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

#ifndef _EEITEM_HXX //autogen
#include <eeitem.hxx>
#endif

#include "svdio.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
#include "svdpagv.hxx"
#include "svdopath.hxx" // fuer GetContext
#include "svdograf.hxx" // fuer GetContext
#include "svdview.hxx"
#include "editview.hxx" // fuer GetField
#define ITEMID_FIELD EE_FEATURE_FIELD  /* wird fuer #include <flditem.hxx> benoetigt */


#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif

#include "flditem.hxx"  // fuer URLField
#include "svdoutl.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
namespace binfilter {

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
/*N*/
/*N*/   onAccessibilityOptionsChanged();
/*N*/ }

/*N*/ SdrView::~SdrView()
/*N*/ {
/*N*/ }






/* new interface src537 */



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
/*N*/       if (bDeep || bMid || bRoot) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*N*/       } else if (eHit==SDRHIT_HANDLE) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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

} //namespace binfilter
#ifndef _OUTLOBJ_HXX
#include "outlobj.hxx"
#endif
namespace binfilter {//STRIP009
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
/*N*/   if (pDragBla!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/   if (IsMarkObj() || IsMarkPoints() || IsMarkGluePoints() || IsEncirclement() || IsSetPageOrg()) return Pointer(POINTER_ARROW);
/*N*/   if (IsDragHelpLine()) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 return GetDraggedHelpLine().GetPointer();
/*N*/   if (IsMacroObj()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/   USHORT nTol=nHitTolLog;
/*N*/   // TextEdit, ObjEdit, Macro
/*N*/   if (IsTextEdit() && (IsTextEditInSelectionMode() || IsTextEditHit(rMousePos,0/*nTol*/)))
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if(!pOut || IsTextEditInSelectionMode())
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
/*N*/       case SDREVENT_BEGMACROOBJ: {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       }
/*N*/   } // switch

/*N*/   switch(eHit)
/*N*/   {
/*N*/       case SDRHIT_HELPLINE :
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 return aVEvt.pPV->GetHelpLines()[aVEvt.nHlplIdx].GetPointer();
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
/*?*/   if (pHdl!=NULL || bMarkHit) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*N*/   if (pAktCreate!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   } else if (pDragBla!=NULL) {
/*?*/       if (bInsPolyPoint || IsInsertGluePoint()) {
/*?*/           aStr=aInsPointUndoStr;
/*N*/       } else {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       }
/*N*/   } else if (bMarking) {
/*?*/       if (HasMarkedObj()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/       } else {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       }
/*N*/   } else if (bMarkingPoints) {
/*?*/       if (HasMarkedPoints()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ImpTakeDescriptionStr(STR_ViewMarked,aStr);
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


/*N*/ void SdrView::UnmarkAll()
/*N*/ {
/*N*/   if (IsTextEdit()) {
/*?*/       ESelection eSel=GetTextEditOutlinerView()->GetSelection();
/*?*/       eSel.nStartPara=eSel.nEndPara;
/*?*/       eSel.nStartPos=eSel.nEndPos;
/*?*/       GetTextEditOutlinerView()->SetSelection(eSel);
/*?*/ #ifndef SVX_LIGHT
/*?*/       if (pItemBrowser!=NULL) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pItemBrowser->SetDirty();
/*?*/ #endif
/*N*/   } else if (HasMarkedGluePoints()) UnmarkAllGluePoints();
/*N*/   else if (HasMarkedPoints()) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 UnmarkAllPoints(); // ! Marked statt Markable !
/*N*/   else UnmarkAllObj();
/*N*/ }








/*N*/ void SdrView::DeleteMarked()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }



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


/** method is called whenever the global SvtAccessibilityOptions is changed */
/*N*/ void SdrView::onAccessibilityOptionsChanged()
/*N*/ {
/*N*/ }

}
