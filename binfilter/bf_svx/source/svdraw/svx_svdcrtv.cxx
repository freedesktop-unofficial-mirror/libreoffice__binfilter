/*************************************************************************
 *
 *  $RCSfile: svx_svdcrtv.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:18 $
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

#include "svdcrtv.hxx"
#include "xattr.hxx"
#include "svdio.hxx"
#include "svdxout.hxx"
#include "svdundo.hxx"
#include "svdocapt.hxx" // Spezialbehandlung: Nach dem Create transparente Fuellung
#include "svdcrtmt.hxx"
#include "svdvmark.hxx"
#include "svdoedge.hxx"
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svdetc.hxx"

#ifndef _E3D_SCENE3D_HXX
#include "scene3d.hxx"
#endif

#ifndef _E3D_VIEW3D_HXX
#include "view3d.hxx"
#endif

#define XOR_CREATE_PEN          PEN_SOLID

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ class ImpSdrConnectMarker: public SdrViewUserMarker
/*N*/ {
/*N*/   const SdrObject*            pAktObj;
/*N*/   const SdrPageView*          pAktPV;
/*N*/
//STRIP001  virtual void Draw(OutputDevice* pOut, FASTBOOL bHiding, FASTBOOL bNoSaveDC);

/*N*/ public:
/*N*/   ImpSdrConnectMarker(SdrCreateView* pView): SdrViewUserMarker(pView),pAktObj(NULL),pAktPV(NULL) {}
/*N*/   ~ImpSdrConnectMarker() {}
/*N*/   void SetTargetObject(const SdrObject* pObj);
/*N*/ }; // svdvmark

//STRIP001 void ImpSdrConnectMarker::Draw(OutputDevice* pOut, FASTBOOL bHiding, FASTBOOL bNoSaveDC)
//STRIP001 {
//STRIP001  SdrViewUserMarker::Draw(pOut,bHiding,bNoSaveDC);
//STRIP001
//STRIP001  const SdrCreateView* pView=(SdrCreateView*)GetView();
//STRIP001  const SdrObject* pObj=pAktObj;
//STRIP001  const SdrPageView* pPV=pAktPV;
//STRIP001
//STRIP001  if (pObj!=NULL && pView!=NULL && pOut!=NULL)
//STRIP001  {
//STRIP001      RasterOp eRop0=pOut->GetRasterOp();
//STRIP001      BOOL bMap0=pOut->IsMapModeEnabled();
//STRIP001      pOut->SetRasterOp(ROP_INVERT);
//STRIP001
//STRIP001      Color aOldLineColor, aOldFillColor;
//STRIP001
//STRIP001      if (!bNoSaveDC)
//STRIP001      {
//STRIP001          aOldLineColor = pOut->GetLineColor();
//STRIP001          aOldFillColor = pOut->GetFillColor();
//STRIP001      }
//STRIP001      Point aPvOfs; if (pPV!=NULL) aPvOfs=pPV->GetOffset();
//STRIP001      if (pView->IsAutoVertexConnectors())
//STRIP001      {
//STRIP001          for (USHORT i=0; i<4; i++) {
//STRIP001              SdrGluePoint aGluePoint(pObj->GetVertexGluePoint(i));
//STRIP001              aGluePoint.Draw(*pOut,pObj);
//STRIP001          }
//STRIP001      }
//STRIP001      if (pView->IsAutoCornerConnectors())
//STRIP001      {
//STRIP001          for (USHORT i=0; i<4; i++)
//STRIP001          {
//STRIP001              SdrGluePoint aGluePoint(pObj->GetVertexGluePoint(i));
//STRIP001              aGluePoint.Draw(*pOut,pObj);
//STRIP001          }
//STRIP001      }
//STRIP001      if (!bNoSaveDC)
//STRIP001      {
//STRIP001          pOut->SetLineColor( aOldLineColor );
//STRIP001          if ( aOldFillColor != pOut->GetFillColor() )
//STRIP001              pOut->SetFillColor( aOldFillColor );
//STRIP001      }
//STRIP001      pOut->SetRasterOp(eRop0);
//STRIP001      pOut->EnableMapMode(bMap0);
//STRIP001  }
//STRIP001 }

/*N*/ void ImpSdrConnectMarker::SetTargetObject(const SdrObject* pObj)
/*N*/ {
/*N*/   if (pAktObj!=pObj) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        BOOL bVisible=IsVisible();
//STRIP001 /*?*/        if (bVisible) Hide();
//STRIP001 /*?*/        pAktObj=pObj;
//STRIP001 /*?*/        if (bVisible) Show();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@  @@@@@  @@@@  @@@@@@ @@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@  @@ @@    @@  @@   @@   @@     @@ @@ @@ @@    @@   @@
//  @@     @@  @@ @@    @@  @@   @@   @@     @@ @@ @@ @@    @@ @ @@
//  @@     @@@@@  @@@@  @@@@@@   @@   @@@@   @@@@@ @@ @@@@  @@@@@@@
//  @@     @@  @@ @@    @@  @@   @@   @@      @@@  @@ @@    @@@@@@@
//  @@  @@ @@  @@ @@    @@  @@   @@   @@      @@@  @@ @@    @@@ @@@
//   @@@@  @@  @@ @@@@@ @@  @@   @@   @@@@@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCreateView::ImpClearVars()
/*N*/ {
/*N*/   nAktInvent=SdrInventor;
/*N*/   nAktIdent=OBJ_NONE;
/*N*/   pCurrentLibObj=NULL;
/*N*/   bCurrentLibObjMoveNoResize=FALSE;
/*N*/   bCurrentLibObjSetDefAttr=FALSE;
/*N*/   bCurrentLibObjSetDefLayer=FALSE;
/*N*/   pLibObjDragMeth=NULL;
/*N*/   pAktCreate=NULL;
/*N*/   pCreatePV=NULL;
/*N*/   bAutoTextEdit=FALSE;
/*N*/   b1stPointAsCenter=FALSE;
/*N*/   aAktCreatePointer=Pointer(POINTER_CROSS);
/*N*/   bUseIncompatiblePathCreateInterface=FALSE;
/*N*/   bAutoClosePolys=TRUE;
/*N*/   nAutoCloseDistPix=5;
/*N*/   nFreeHandMinDistPix=10;
/*N*/
/*N*/   pConnectMarker=new ImpSdrConnectMarker(this);
/*N*/   pConnectMarker->SetLineWidth(2);
/*N*/   pConnectMarker->SetAnimateDelay(500);
/*N*/   pConnectMarker->SetAnimateCount(3);
/*N*/   pConnectMarker->SetAnimateSpeed(100);
/*N*/   pConnectMarker->SetAnimateToggle(TRUE);
/*N*/ }

/*N*/ void SdrCreateView::ImpMakeCreateAttr()
/*N*/ {
/*N*/ }

/*N*/ SdrCreateView::SdrCreateView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrDragView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/   ImpMakeCreateAttr();
/*N*/ }

/*?*/ SdrCreateView::SdrCreateView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrDragView(pModel1,pXOut)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/   ImpMakeCreateAttr();
/*?*/ }

/*N*/ SdrCreateView::~SdrCreateView()
/*N*/ {
/*N*/   delete pConnectMarker;
/*N*/   delete pCurrentLibObj;
/*N*/   delete pAktCreate;
/*N*/ }

//STRIP001 void SdrCreateView::ImpDelCreateAttr()
//STRIP001 {
//STRIP001 }

/*N*/ BOOL SdrCreateView::IsAction() const
/*N*/ {
/*N*/   return SdrDragView::IsAction() || pAktCreate!=NULL;
/*N*/ }

//STRIP001 void SdrCreateView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001  SdrDragView::MovAction(rPnt);
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      MovCreateObj(rPnt);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCreateView::EndAction()
//STRIP001 {
//STRIP001  if (pAktCreate!=NULL) EndCreateObj(SDRCREATE_FORCEEND);
//STRIP001  SdrDragView::EndAction();
//STRIP001 }

//STRIP001 void SdrCreateView::BckAction()
//STRIP001 {
//STRIP001  if (pAktCreate!=NULL) BckCreateObj();
//STRIP001  SdrDragView::BckAction();
//STRIP001 }

/*N*/ void SdrCreateView::BrkAction()
/*N*/ {
/*N*/   SdrDragView::BrkAction();
/*N*/   BrkCreateObj();
/*N*/ }

//STRIP001 void SdrCreateView::TakeActionRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      rRect=aDragStat.GetActionRect();
//STRIP001      if (rRect.IsEmpty()) {
//STRIP001          rRect=Rectangle(aDragStat.GetPrev(),aDragStat.GetNow());
//STRIP001      }
//STRIP001  } else {
//STRIP001      SdrDragView::TakeActionRect(rRect);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrCreateView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   SdrDragView::ToggleShownXor(pOut,pRegion);
/*N*/   if (pAktCreate!=NULL && aDragStat.IsShown()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        DrawCreateObj(pOut,TRUE);
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrCreateView::CheckEdgeMode()
/*N*/ {
/*N*/   UINT32 nInv=nAktInvent;
/*N*/   UINT16 nIdn=nAktIdent;
/*N*/   if (pAktCreate!=NULL) {
/*?*/       nInv=pAktCreate->GetObjInventor();
/*?*/       nIdn=pAktCreate->GetObjIdentifier();
/*?*/       // wird vom EdgeObj gemanaged
/*?*/       if (nAktInvent==SdrInventor && nAktIdent==OBJ_EDGE) return FALSE;
/*N*/   }
/*N*/   if (!IsCreateMode() || nAktInvent!=SdrInventor || nAktIdent!=OBJ_EDGE || pCurrentLibObj!=NULL) {
/*?*/       if (pConnectMarker->IsVisible()) {DBG_ASSERT(0, "STRIP"); }//STRIP001 pConnectMarker->Hide();
/*N*/       pConnectMarker->SetTargetObject(NULL);
/*N*/       return FALSE;
/*N*/   } else {
/*N*/       // TRUE heisst: MouseMove soll Connect checken
/*?*/       return !IsAction();
/*N*/   }
/*N*/ }

//STRIP001 void SdrCreateView::SetConnectMarker(const SdrObjConnection& rCon, const SdrPageView& rPV)
//STRIP001 {
//STRIP001  if (rCon.pObj!=NULL) {
//STRIP001      Rectangle aNewRect;
//STRIP001      USHORT nNewDist=0;
//STRIP001      if (rCon.bBestConn || rCon.bBestVertex) {
//STRIP001          aNewRect=rCon.pObj->GetBoundRect();
//STRIP001          nNewDist=2;
//STRIP001      } else {
//STRIP001          nNewDist=aHdl.GetHdlSize()+2;
//STRIP001          SdrGluePoint aGP;
//STRIP001          rCon.TakeGluePoint(aGP,TRUE);
//STRIP001          Point aPt(aGP.GetPos());
//STRIP001          aNewRect=Rectangle(aPt,aPt);
//STRIP001      }
//STRIP001      Point aPvOfs(rPV.GetOffset());
//STRIP001      aNewRect.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001      if (!pConnectMarker->IsVisible() ||
//STRIP001          pConnectMarker->GetRectangle()==NULL ||
//STRIP001          *pConnectMarker->GetRectangle()!=aNewRect ||
//STRIP001          pConnectMarker->GetPixelDistance()!=nNewDist)
//STRIP001      {
//STRIP001          pConnectMarker->Hide();
//STRIP001          pConnectMarker->SetRectangle(aNewRect);
//STRIP001          pConnectMarker->SetPixelDistance(nNewDist);
//STRIP001          pConnectMarker->SetAnimate(TRUE);
//STRIP001          pConnectMarker->SetTargetObject(rCon.pObj);
//STRIP001          pConnectMarker->Show();
//STRIP001      }
//STRIP001  } else {
//STRIP001      HideConnectMarker();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCreateView::HideConnectMarker()
//STRIP001 {
//STRIP001  pConnectMarker->Hide();
//STRIP001  pConnectMarker->SetTargetObject(NULL);
//STRIP001  pConnectMarker->SetAnimate(FALSE);
//STRIP001 }

//STRIP001 BOOL SdrCreateView::MouseMove(const MouseEvent& rMEvt, Window* pWin)
//STRIP001 {
//STRIP001  if (CheckEdgeMode() && pWin!=NULL) {
//STRIP001      Point aPos(pWin->PixelToLogic(rMEvt.GetPosPixel()));
//STRIP001      SdrPageView* pPV=GetPageView(aPos);
//STRIP001      if (pPV!=NULL) {
//STRIP001          // Defaultete Hit-Toleranz bei IsMarkedHit() mal aendern !!!!
//STRIP001          BOOL bMarkHit=HitHandle(aPos,*pWin)!=NULL || IsMarkedObjHit(aPos);
//STRIP001          SdrObjConnection aCon;
//STRIP001          Point aPvOfs(pPV->GetOffset());
//STRIP001          aPos-=aPvOfs;
//STRIP001          if (!bMarkHit) SdrEdgeObj::ImpFindConnector(aPos,*pPV,aCon,NULL,pWin);
//STRIP001          SetConnectMarker(aCon,*pPV);
//STRIP001      }
//STRIP001  }
//STRIP001  return SdrDragView::MouseMove(rMEvt,pWin);
//STRIP001 }

/*N*/ BOOL SdrCreateView::IsTextTool() const
/*N*/ {
/*N*/   return eEditMode==SDREDITMODE_CREATE && pCurrentLibObj==NULL && nAktInvent==SdrInventor && (nAktIdent==OBJ_TEXT || nAktIdent==OBJ_TEXTEXT || nAktIdent==OBJ_TITLETEXT || nAktIdent==OBJ_OUTLINETEXT);
/*N*/ }

/*N*/ BOOL SdrCreateView::IsEdgeTool() const
/*N*/ {
/*N*/   return eEditMode==SDREDITMODE_CREATE && pCurrentLibObj==NULL && nAktInvent==SdrInventor && (nAktIdent==OBJ_EDGE);
/*N*/ }

//STRIP001 BOOL SdrCreateView::IsMeasureTool() const
//STRIP001 {
//STRIP001  return eEditMode==SDREDITMODE_CREATE && pCurrentLibObj==NULL && nAktInvent==SdrInventor && (nAktIdent==OBJ_MEASURE);
//STRIP001 }

/*N*/ void SdrCreateView::SetCurrentObj(UINT16 nIdent, UINT32 nInvent)
/*N*/ {
/*N*/   if (pCurrentLibObj!=NULL) {
/*?*/       delete pCurrentLibObj;
/*?*/       pCurrentLibObj=NULL;
/*N*/   }
/*N*/   if (nAktInvent!=nInvent || nAktIdent!=nIdent) {
/*N*/       nAktInvent=nInvent;
/*N*/       nAktIdent=nIdent;
/*N*/       SdrObject* pObj = SdrObjFactory::MakeNewObject(nInvent,nIdent,NULL,NULL);
/*N*/
/*N*/       if(pObj)
/*N*/       {
/*N*/           // Auf pers. Wunsch von Marco:
/*N*/           // Mauszeiger bei Textwerkzeug immer I-Beam. Fadenkreuz
/*N*/           // mit kleinem I-Beam erst bai MouseButtonDown
/*N*/           if(IsTextTool())
/*N*/           {
/*N*/               // #81944# AW: Here the correct pointer needs to be used
/*N*/               // if the default is set to vertical writing
/*?*/               aAktCreatePointer = POINTER_TEXT;
/*N*/           }
/*N*/           else
/*N*/               aAktCreatePointer = pObj->GetCreatePointer();
/*N*/
/*N*/           delete pObj;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           aAktCreatePointer = Pointer(POINTER_CROSS);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   CheckEdgeMode();
/*N*/   ImpSetGlueVisible3(IsEdgeTool());
/*N*/ }

//STRIP001 void SdrCreateView::SetCurrentLibObj(SdrObject* pObj, BOOL bMoveNoResize, BOOL bSetDefAttr, BOOL bSetDefLayer)
//STRIP001 {
//STRIP001  if (pCurrentLibObj!=NULL && pObj!=pCurrentLibObj) delete pCurrentLibObj;
//STRIP001  pCurrentLibObj=pObj;
//STRIP001  bCurrentLibObjMoveNoResize=bMoveNoResize;
//STRIP001  bCurrentLibObjSetDefAttr=bSetDefAttr;
//STRIP001  bCurrentLibObjSetDefLayer=bSetDefLayer;
//STRIP001  if (pCurrentLibObj!=NULL) {
//STRIP001      pCurrentLibObj->SetModel(pMod);
//STRIP001  }
//STRIP001  aAktCreatePointer=Pointer(POINTER_CROSS);
//STRIP001  nAktInvent=SdrInventor;
//STRIP001  nAktIdent=OBJ_NONE;
//STRIP001  pConnectMarker->Hide();
//STRIP001  ImpSetGlueVisible3(FALSE);
//STRIP001 }

//STRIP001 BOOL SdrCreateView::ImpBegCreateObj(UINT32 nInvent, UINT16 nIdent, const Point& rPnt, OutputDevice* pOut,
//STRIP001  short nMinMov, SdrPageView* pPV, const Rectangle& rLogRect)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  SetSolidDraggingNow(IsSolidDragging());
//STRIP001  SetSolidDraggingCheck(FALSE);
//STRIP001  UnmarkAllObj();
//STRIP001  BrkAction();
//STRIP001  pConnectMarker->Hide();
//STRIP001  DBG_ASSERT(pLibObjDragMeth==NULL,"SdrCreateView::ImpBegCreateObj(): pLibObjDragMeth!=NULL");
//STRIP001  pLibObjDragMeth=NULL;
//STRIP001  if (pPV!=NULL) pCreatePV=pPV;
//STRIP001  else pCreatePV=GetPageView(rPnt);
//STRIP001  if (pCreatePV!=NULL) { // ansonsten keine Seite angemeldet!
//STRIP001      String aLay(aAktLayer);
//STRIP001
//STRIP001      if(nInvent == SdrInventor && nIdent == OBJ_MEASURE && aMeasureLayer.Len())
//STRIP001      {
//STRIP001          aLay = aMeasureLayer;
//STRIP001      }
//STRIP001
//STRIP001      SdrLayerID nLayer=pCreatePV->GetPage()->GetLayerAdmin().GetLayerID(aLay,TRUE);
//STRIP001      if (nLayer==SDRLAYER_NOTFOUND) nLayer=0;
//STRIP001      if (!pCreatePV->GetLockedLayers().IsSet(nLayer) && pCreatePV->GetVisibleLayers().IsSet(nLayer)) {
//STRIP001          pAktCreate=SdrObjFactory::MakeNewObject(nInvent,nIdent,pCreatePV->GetPage(),pMod);
//STRIP001          Point aPnt(rPnt-pCreatePV->GetOffset());
//STRIP001          if (nAktInvent!=SdrInventor || (nAktIdent!=USHORT(OBJ_EDGE) &&
//STRIP001                                          nAktIdent!=USHORT(OBJ_FREELINE) &&
//STRIP001                                          nAktIdent!=USHORT(OBJ_FREEFILL) )) { // Kein Fang fuer Edge und Freihand!
//STRIP001              aPnt=GetSnapPos(aPnt,pCreatePV);
//STRIP001          }
//STRIP001          if (pAktCreate!=NULL) {
//STRIP001              BOOL bStartEdit=FALSE; // nach Ende von Create automatisch TextEdit starten
//STRIP001              if (pDefaultStyleSheet!=NULL) pAktCreate->NbcSetStyleSheet(pDefaultStyleSheet,FALSE);
//STRIP001
//STRIP001              // #101618# SW uses a naked SdrObject for frame construction. Normally, such an
//STRIP001              // object should not be created. Since it is possible to use it as a helper
//STRIP001              // object (e.g. in letting the user define an area with the interactive
//STRIP001              // construction) at least no items should be set at that object.
//STRIP001              if(nInvent != SdrInventor || nIdent != OBJ_NONE)
//STRIP001              {
//STRIP001                  pAktCreate->SetItemSet(aDefaultAttr);
//STRIP001              }
//STRIP001
//STRIP001              if (HAS_BASE(SdrCaptionObj,pAktCreate))
//STRIP001              {
//STRIP001                  SfxItemSet aSet(pMod->GetItemPool());
//STRIP001                  aSet.Put(XFillColorItem(String(),Color(COL_WHITE))); // Falls einer auf Solid umschaltet
//STRIP001                  aSet.Put(XFillStyleItem(XFILL_NONE));
//STRIP001
//STRIP001                  pAktCreate->SetItemSet(aSet);
//STRIP001
//STRIP001                  bStartEdit=TRUE;
//STRIP001              }
//STRIP001              if (nInvent==SdrInventor && (nIdent==OBJ_TEXT || nIdent==OBJ_TEXTEXT ||
//STRIP001                  nIdent==OBJ_TITLETEXT || nIdent==OBJ_OUTLINETEXT))
//STRIP001              {
//STRIP001                  // Fuer alle Textrahmen default keinen Hintergrund und keine Umrandung
//STRIP001                  SfxItemSet aSet(pMod->GetItemPool());
//STRIP001                  aSet.Put(XFillColorItem(String(),Color(COL_WHITE))); // Falls einer auf Solid umschaltet
//STRIP001                  aSet.Put(XFillStyleItem(XFILL_NONE));
//STRIP001                  aSet.Put(XLineColorItem(String(),Color(COL_BLACK))); // Falls einer auf Solid umschaltet
//STRIP001                  aSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001
//STRIP001                  pAktCreate->SetItemSet(aSet);
//STRIP001
//STRIP001                  bStartEdit=TRUE;
//STRIP001              }
//STRIP001              if (!rLogRect.IsEmpty()) pAktCreate->NbcSetLogicRect(rLogRect);
//STRIP001
//STRIP001              // #90129# make sure drag start point is inside WorkArea
//STRIP001              const Rectangle& rWorkArea = ((SdrDragView*)this)->GetWorkArea();
//STRIP001
//STRIP001              if(!rWorkArea.IsEmpty())
//STRIP001              {
//STRIP001                  if(aPnt.X() < rWorkArea.Left())
//STRIP001                  {
//STRIP001                      aPnt.X() = rWorkArea.Left();
//STRIP001                  }
//STRIP001
//STRIP001                  if(aPnt.X() > rWorkArea.Right())
//STRIP001                  {
//STRIP001                      aPnt.X() = rWorkArea.Right();
//STRIP001                  }
//STRIP001
//STRIP001                  if(aPnt.Y() < rWorkArea.Top())
//STRIP001                  {
//STRIP001                      aPnt.Y() = rWorkArea.Top();
//STRIP001                  }
//STRIP001
//STRIP001                  if(aPnt.Y() > rWorkArea.Bottom())
//STRIP001                  {
//STRIP001                      aPnt.Y() = rWorkArea.Bottom();
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              aDragStat.Reset(aPnt);
//STRIP001              aDragStat.SetView((SdrView*)this);
//STRIP001              aDragStat.SetPageView(pCreatePV);
//STRIP001              aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001              pDragWin=pOut;
//STRIP001              if (pAktCreate->BegCreate(aDragStat)) {
//STRIP001                  ShowCreateObj(pOut,TRUE);
//STRIP001                  bRet=TRUE;
//STRIP001              } else {
//STRIP001                  delete pAktCreate;
//STRIP001                  pAktCreate=NULL;
//STRIP001                  pCreatePV=NULL;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrCreateView::BegCreateObj(const Point& rPnt, OutputDevice* pOut, short nMinMov, SdrPageView* pPV)
//STRIP001 {
//STRIP001  if ( !pCurrentLibObj )
//STRIP001      return ImpBegCreateObj(nAktInvent,nAktIdent,rPnt,pOut,nMinMov,pPV,Rectangle());
//STRIP001  else
//STRIP001      return BegCreateLibObj(rPnt,pCurrentLibObj->Clone(),bCurrentLibObjMoveNoResize,
//STRIP001                             bCurrentLibObjSetDefAttr,bCurrentLibObjSetDefLayer,pOut,nMinMov,pPV);
//STRIP001 }

//STRIP001 BOOL SdrCreateView::BegCreateCaptionObj(const Point& rPnt, const Size& rObjSiz,
//STRIP001  OutputDevice* pOut, short nMinMov, SdrPageView* pPV)
//STRIP001 {
//STRIP001  return ImpBegCreateObj(SdrInventor,OBJ_CAPTION,rPnt,pOut,nMinMov,pPV,
//STRIP001                         Rectangle(rPnt,Size(rObjSiz.Width()+1,rObjSiz.Height()+1)));
//STRIP001 }

//STRIP001 BOOL SdrCreateView::BegCreateLibObj(const Point& rPnt, SdrObject* pObj, BOOL bMoveNoResize,
//STRIP001  BOOL bSetDefAttr, BOOL bSetDefLayer,
//STRIP001  OutputDevice* pOut, short nMinMov, SdrPageView* pPV)
//STRIP001 {
//STRIP001  SetSolidDraggingNow(FALSE); // noch kein SolidDragging bei LibObjs
//STRIP001  BOOL bRet=FALSE;
//STRIP001  UnmarkAllObj();
//STRIP001  BrkAction();
//STRIP001  pConnectMarker->Hide();
//STRIP001  DBG_ASSERT(pLibObjDragMeth==NULL,"SdrCreateView::BegCreateLibObj(): pLibObjDragMeth!=NULL");
//STRIP001  pLibObjDragMeth=NULL;
//STRIP001  if (pPV!=NULL) pCreatePV=pPV;
//STRIP001  else pCreatePV=GetPageView(rPnt);
//STRIP001  if (pObj!=NULL && pCreatePV!=NULL) {
//STRIP001      bRet=TRUE;
//STRIP001      pObj->SetModel(pMod);
//STRIP001      if (bSetDefAttr) {
//STRIP001          if (pDefaultStyleSheet!=NULL) pObj->NbcSetStyleSheet(pDefaultStyleSheet,FALSE);
//STRIP001
//STRIP001          pObj->SetItemSet(aDefaultAttr);
//STRIP001      }
//STRIP001      if (bSetDefLayer) {
//STRIP001          SdrLayerID nLayer=pCreatePV->GetPage()->GetLayerAdmin().GetLayerID(aAktLayer,TRUE);
//STRIP001          if (nLayer==SDRLAYER_NOTFOUND) nLayer=0;
//STRIP001          if (pCreatePV->GetLockedLayers().IsSet(nLayer) || !pCreatePV->GetVisibleLayers().IsSet(nLayer)) {
//STRIP001              bRet=FALSE; // Layer gesperrt oder nicht sichtbar!
//STRIP001          }
//STRIP001      }
//STRIP001      if (bRet) {
//STRIP001          pAktCreate=pObj;
//STRIP001          Point aPnt(rPnt-pCreatePV->GetOffset());
//STRIP001          aPnt=GetSnapPos(aPnt,pCreatePV);
//STRIP001
//STRIP001          // #90129# make sure drag start point is inside WorkArea
//STRIP001          const Rectangle& rWorkArea = ((SdrDragView*)this)->GetWorkArea();
//STRIP001
//STRIP001          if(!rWorkArea.IsEmpty())
//STRIP001          {
//STRIP001              if(aPnt.X() < rWorkArea.Left())
//STRIP001              {
//STRIP001                  aPnt.X() = rWorkArea.Left();
//STRIP001              }
//STRIP001
//STRIP001              if(aPnt.X() > rWorkArea.Right())
//STRIP001              {
//STRIP001                  aPnt.X() = rWorkArea.Right();
//STRIP001              }
//STRIP001
//STRIP001              if(aPnt.Y() < rWorkArea.Top())
//STRIP001              {
//STRIP001                  aPnt.Y() = rWorkArea.Top();
//STRIP001              }
//STRIP001
//STRIP001              if(aPnt.Y() > rWorkArea.Bottom())
//STRIP001              {
//STRIP001                  aPnt.Y() = rWorkArea.Bottom();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          aDragStat.Reset(aPnt);
//STRIP001          aDragStat.SetView((SdrView*)this);
//STRIP001          aDragStat.SetPageView(pCreatePV);
//STRIP001          aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001          pDragWin=pOut;
//STRIP001          if (bMoveNoResize) {
//STRIP001              pLibObjDragMeth=new ImpSdrCreateLibObjMove(*this);
//STRIP001          } else {
//STRIP001              pLibObjDragMeth=new ImpSdrCreateLibObjResize(*this);
//STRIP001          }
//STRIP001          bRet=pLibObjDragMeth->Beg();
//STRIP001      }
//STRIP001  }
//STRIP001  if (!bRet) {
//STRIP001      if (pObj!=NULL) delete pObj;
//STRIP001      if (pLibObjDragMeth!=NULL) { delete pLibObjDragMeth; pLibObjDragMeth=NULL; }
//STRIP001      pAktCreate=NULL;
//STRIP001      pCreatePV=NULL;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrCreateView::MovCreateObj(const Point& rPnt)
//STRIP001 {
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      if (IsSolidDraggingNow() && !IsSolidDraggingCheck()) {
//STRIP001          // Z.B. fuer Fill+Linelose Textrahmen bei SolidDragging
//STRIP001          SetSolidDraggingCheck(TRUE);
//STRIP001          const SfxItemSet& rSet = pAktCreate->GetItemSet();
//STRIP001          XFillStyle eFill=((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001          XLineStyle eLine=((XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
//STRIP001          if (eLine==XLINE_NONE && eFill==XFILL_NONE) {
//STRIP001              SetSolidDraggingNow(FALSE);
//STRIP001          }
//STRIP001      }
//STRIP001      Point aPnt(rPnt-pCreatePV->GetOffset());
//STRIP001      if (!aDragStat.IsNoSnap()) {
//STRIP001          aPnt=GetSnapPos(aPnt,pCreatePV);
//STRIP001      }
//STRIP001      if (IsOrtho()) {
//STRIP001          if (aDragStat.IsOrtho8Possible()) OrthoDistance8(aDragStat.GetPrev(),aPnt,IsBigOrtho());
//STRIP001          else if (aDragStat.IsOrtho4Possible()) OrthoDistance4(aDragStat.GetPrev(),aPnt,IsBigOrtho());
//STRIP001      }
//STRIP001
//STRIP001      // #77734# If the drag point was limited and Ortho is active, do
//STRIP001      // the small ortho correction (reduction) -> last parameter to FALSE.
//STRIP001      sal_Bool bDidLimit(ImpLimitToWorkArea(aPnt,pCreatePV));
//STRIP001      if(bDidLimit && IsOrtho())
//STRIP001      {
//STRIP001          if(aDragStat.IsOrtho8Possible())
//STRIP001              OrthoDistance8(aDragStat.GetPrev(), aPnt, FALSE);
//STRIP001          else if(aDragStat.IsOrtho4Possible())
//STRIP001              OrthoDistance4(aDragStat.GetPrev(), aPnt, FALSE);
//STRIP001      }
//STRIP001
//STRIP001      if (aPnt==aDragStat.GetNow()) return;
//STRIP001      if (pLibObjDragMeth==NULL) {
//STRIP001          BOOL bMerk=aDragStat.IsMinMoved();
//STRIP001          if (aDragStat.CheckMinMoved(aPnt)) {
//STRIP001              Rectangle aBound;
//STRIP001              if (IsSolidDraggingNow()) aBound=pAktCreate->GetBoundRect();
//STRIP001              XPolyPolygon aXPP1;
//STRIP001              if (!bMerk) aDragStat.NextPoint();
//STRIP001              aDragStat.NextMove(aPnt);
//STRIP001              pAktCreate->MovCreate(aDragStat);
//STRIP001              pAktCreate->TakeCreatePoly(aDragStat,aXPP1);
//STRIP001              XPolyPolygon aXPP2(aXPP1); // kopieren, weil wird in DrawCreateDiff geaendert
//STRIP001              if (!IsSolidDraggingNow()) {
//STRIP001                  DrawCreateObjDiff(pCreatePV->DragPoly(),aXPP1);
//STRIP001              }
//STRIP001              pCreatePV->DragPoly()=aXPP2;
//STRIP001              if (IsSolidDraggingNow()) {
//STRIP001                  aBound.Union(pAktCreate->GetBoundRect());
//STRIP001                  SdrObjList* pOL=pCreatePV->GetObjList();
//STRIP001                  SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001                  pOL->NbcInsertObject(pAktCreate,CONTAINER_APPEND,&aReason);
//STRIP001                  Point aPvOfs(pCreatePV->GetOffset());
//STRIP001                  USHORT nAnz=pDragWin==NULL ? GetWinCount() : 1;
//STRIP001                  for (USHORT i=0; i<nAnz; i++) {
//STRIP001                      USHORT nWinNum=SDRVIEWWIN_NOTFOUND;
//STRIP001                      OutputDevice* pOut=pDragWin;
//STRIP001                      if (pOut==NULL) {
//STRIP001                          nWinNum=i;
//STRIP001                          pOut=GetWin(nWinNum);
//STRIP001                      } else {
//STRIP001                          nWinNum=aWinList.Find(pOut);
//STRIP001                      }
//STRIP001                      VirtualDevice aVDev(*pOut);
//STRIP001                      Size a2Pix(pOut->PixelToLogic(Size(2,2)));
//STRIP001                      MapMode aMap(pOut->GetMapMode());
//STRIP001                      aVDev.SetMapMode(aMap);
//STRIP001                      #ifdef MAC
//STRIP001                          Color aMixedColor( RGB_COLORDATA( 223, 223, 223 ) );
//STRIP001                      #else
//STRIP001                          Color aMixedColor( RGB_COLORDATA( 234, 234, 234 ) );
//STRIP001                      #endif
//STRIP001                      aVDev.SetBackground( Wallpaper( aMixedColor ) );
//STRIP001                      aVDev.SetOutputSize(pOut->GetOutputSize());
//STRIP001                      Rectangle aDirtyArea(aBound);
//STRIP001                      aDirtyArea.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001                      InitRedraw(&aVDev,aDirtyArea);
//STRIP001                      if (nWinNum!=SDRVIEWWIN_NOTFOUND) {
//STRIP001                          if (IsShownXorVisibleWinNum(nWinNum)) {
//STRIP001                              ToggleShownXor(&aVDev,NULL);
//STRIP001                          }
//STRIP001                      }
//STRIP001                      Point aCopyOfs(aDirtyArea.TopLeft());
//STRIP001                      aCopyOfs.X()-=a2Pix.Width();
//STRIP001                      aCopyOfs.Y()-=a2Pix.Height();
//STRIP001                      Size aCopySize(aBound.Right()-aBound.Left(),aBound.Bottom()-aBound.Top());
//STRIP001                      aCopySize.Width()+=2*a2Pix.Width();
//STRIP001                      aCopySize.Height()+=2*a2Pix.Height();
//STRIP001                      pOut->DrawOutDev(aCopyOfs,aCopySize,aCopyOfs,aCopySize,aVDev);
//STRIP001                  }
//STRIP001                  pOL->NbcRemoveObject(pOL->GetObjCount()-1);
//STRIP001                  // Die Page brauchen die Objekte
//STRIP001                  // hier mal bitte eine Optimierung vornehmen
//STRIP001                  pAktCreate->SetPage(pCreatePV->GetPage());
//STRIP001              }
//STRIP001          }
//STRIP001      } else {
//STRIP001          pLibObjDragMeth->Mov(aPnt);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrCreateView::EndCreateObj(SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  SdrObject* pObjMerk=pAktCreate;
//STRIP001  SdrPageView* pPVMerk=pCreatePV;
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      if (pLibObjDragMeth==NULL) {
//STRIP001          ULONG nAnz=aDragStat.GetPointAnz();
//STRIP001          if (nAnz<=1 && eCmd==SDRCREATE_FORCEEND) {
//STRIP001              BrkCreateObj(); // Objekte mit nur einem Punkt gibt's nicht (zumindest noch nicht)
//STRIP001              return FALSE; // FALSE=Event nicht ausgewertet
//STRIP001          }
//STRIP001          BOOL bPntsEq=nAnz>1;
//STRIP001          ULONG i=1;
//STRIP001          Point aP0=aDragStat.GetPoint(0);
//STRIP001          while (bPntsEq && i<nAnz) { bPntsEq=aP0==aDragStat.GetPoint(i); i++; }
//STRIP001          if (pAktCreate->EndCreate(aDragStat,eCmd)) {
//STRIP001              if (!IsSolidDraggingNow()) HideCreateObj(pDragWin,TRUE);
//STRIP001              if (!bPntsEq) { // sonst Brk, weil alle Punkte gleich sind.
//STRIP001                  SdrObject* pObj=pAktCreate;
//STRIP001                  pAktCreate=NULL;
//STRIP001                  SdrLayerAdmin& rAd=pCreatePV->GetPage()->GetLayerAdmin();
//STRIP001                  SdrLayerID nLayer=rAd.GetLayerID(aAktLayer,TRUE);
//STRIP001                  if (nLayer==SDRLAYER_NOTFOUND) nLayer=0;
//STRIP001                  pObj->SetLayer(nLayer);
//STRIP001                  InsertObject(pObj,*pCreatePV,IsSolidDraggingNow() ? SDRINSERT_NOBROADCAST : 0);
//STRIP001                  pCreatePV=NULL;
//STRIP001                  bRet=TRUE; // TRUE=Event ausgewertet
//STRIP001              } else {
//STRIP001                  BrkCreateObj();
//STRIP001              }
//STRIP001          } else { // Mehr Punkte
//STRIP001              if (eCmd==SDRCREATE_FORCEEND || // nix da, Ende erzwungen
//STRIP001                  nAnz==0 ||                             // keine Punkte da (kann eigentlich nicht vorkommen)
//STRIP001                  (nAnz<=1 && !aDragStat.IsMinMoved())) { // MinMove nicht erfuellt
//STRIP001                  BrkCreateObj();
//STRIP001              } else {
//STRIP001                  XPolyPolygon aXPP1;
//STRIP001                  pAktCreate->TakeCreatePoly(aDragStat,aXPP1);
//STRIP001                  XPolyPolygon aXPP2(aXPP1); // kopieren, weil wird in DrawCreateDiff geaendert
//STRIP001                  if (!IsSolidDraggingNow()) DrawCreateObjDiff(pCreatePV->DragPoly(),aXPP1);
//STRIP001                  pCreatePV->DragPoly()=aXPP2;
//STRIP001                  aDragStat.ResetMinMoved(); // NextPoint gibt's bei MovCreateObj()
//STRIP001                  bRet=TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          if (bRet && pObjMerk!=NULL && IsTextEditAfterCreate()) {
//STRIP001              SdrTextObj* pText=PTR_CAST(SdrTextObj,pObjMerk);
//STRIP001              if (pText!=NULL && pText->IsTextFrame()) {
//STRIP001                  BegTextEdit(pText,pPVMerk,(Window*)NULL,TRUE,(SdrOutliner*)NULL,(OutlinerView*)NULL);
//STRIP001              }
//STRIP001          }
//STRIP001      } else {
//STRIP001          if (pLibObjDragMeth->End(FALSE)) {
//STRIP001              pAktCreate=NULL;
//STRIP001              pCreatePV=NULL;
//STRIP001              SdrLayerAdmin& rAd=pPVMerk->GetPage()->GetLayerAdmin();
//STRIP001              SdrLayerID nLayer=rAd.GetLayerID(aAktLayer,TRUE);
//STRIP001              if (nLayer==SDRLAYER_NOTFOUND) nLayer=0;
//STRIP001              pObjMerk->SetLayer(nLayer);
//STRIP001
//STRIP001              // #83403# recognize creation of a new 3D object inside a 3D scene
//STRIP001              BOOL bSceneIntoScene(FALSE);
//STRIP001
//STRIP001              if(pObjMerk
//STRIP001                  && pObjMerk->ISA(E3dScene)
//STRIP001                  && pPVMerk
//STRIP001                  && pPVMerk->GetAktGroup()
//STRIP001                  && pPVMerk->GetAktGroup()->ISA(E3dScene))
//STRIP001              {
//STRIP001                  BOOL bDidInsert = ((E3dView*)this)->ImpCloneAll3DObjectsToDestScene(
//STRIP001                      (E3dScene*)pObjMerk, (E3dScene*)pPVMerk->GetAktGroup(), Point(0, 0));
//STRIP001                  if(bDidInsert)
//STRIP001                  {
//STRIP001                      // delete object, it's content is cloned and inserted
//STRIP001                      delete pAktCreate;
//STRIP001                      bRet = FALSE;
//STRIP001                      bSceneIntoScene = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if(!bSceneIntoScene)
//STRIP001              {
//STRIP001                  // do the same as before
//STRIP001                  InsertObject(pObjMerk,*pPVMerk);
//STRIP001              }
//STRIP001
//STRIP001              bRet=TRUE;
//STRIP001          } else {
//STRIP001              delete pAktCreate;
//STRIP001              bRet=FALSE;
//STRIP001          }
//STRIP001          delete pLibObjDragMeth;
//STRIP001          pLibObjDragMeth=NULL;
//STRIP001          pAktCreate=NULL;
//STRIP001          pCreatePV=NULL;
//STRIP001      }
//STRIP001      if (pAktCreate==NULL) {
//STRIP001          SetSolidDraggingNow(FALSE);
//STRIP001          SetSolidDraggingCheck(FALSE);
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrCreateView::BckCreateObj()
//STRIP001 {
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      if (aDragStat.GetPointAnz()<=2 || pLibObjDragMeth!=NULL) {
//STRIP001          BrkCreateObj();
//STRIP001      } else {
//STRIP001          HideCreateObj(pDragWin,TRUE);
//STRIP001          aDragStat.PrevPoint();
//STRIP001          if (pAktCreate->BckCreate(aDragStat)) {
//STRIP001              ShowCreateObj(pDragWin,TRUE);
//STRIP001          } else {
//STRIP001              BrkCreateObj();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrCreateView::BrkCreateObj()
/*N*/ {
/*N*/   if (pAktCreate!=NULL) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if (pLibObjDragMeth==NULL) {
//STRIP001 /*?*/            if (!IsSolidDraggingNow()) {
//STRIP001 /*?*/                HideCreateObj(pDragWin,TRUE);
//STRIP001 /*?*/            } else {
//STRIP001 /*?*/                Rectangle aBound(pAktCreate->GetBoundRect());
//STRIP001 /*?*/                Point aPvOfs(pCreatePV->GetOffset());
//STRIP001 /*?*/                aBound.Move(aPvOfs.X(),aPvOfs.Y());
//STRIP001 /*?*/                InvalidateAllWin(aBound);
//STRIP001 /*?*/            }
//STRIP001 /*?*/            pAktCreate->BrkCreate(aDragStat);
//STRIP001 /*?*/        } else {
//STRIP001 /*?*/            pLibObjDragMeth->Brk();
//STRIP001 /*?*/            delete pLibObjDragMeth;
//STRIP001 /*?*/            pLibObjDragMeth=NULL;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        delete pAktCreate;
//STRIP001 /*?*/        pAktCreate=NULL;
//STRIP001 /*?*/        pCreatePV=NULL;
//STRIP001 /*?*/        SetSolidDraggingNow(FALSE);
//STRIP001 /*?*/        SetSolidDraggingCheck(FALSE);
/*N*/   }
/*N*/ }

//STRIP001 void SdrCreateView::DrawCreateObjDiff(XPolyPolygon& rXPP0, XPolyPolygon& rXPP1)
//STRIP001 {
//STRIP001  if (IsSolidDraggingNow()) return;
//STRIP001  USHORT nPolyAnz0=rXPP0.Count();
//STRIP001  USHORT nPolyAnz1=rXPP1.Count();
//STRIP001  USHORT nMinPolyAnz=Min(nPolyAnz0,nPolyAnz1);
//STRIP001  USHORT nPolyNum;
//STRIP001  for (nPolyNum=nMinPolyAnz; nPolyNum>0;) { // unveraenderte Polygone entfernen
//STRIP001      nPolyNum--;
//STRIP001      if (rXPP0[nPolyNum]==rXPP1[nPolyNum]) {
//STRIP001          rXPP0.Remove(nPolyNum);
//STRIP001          rXPP1.Remove(nPolyNum);
//STRIP001      }
//STRIP001  }
//STRIP001  nPolyAnz0=rXPP0.Count();
//STRIP001  nPolyAnz1=rXPP1.Count();
//STRIP001  nMinPolyAnz=Min(nPolyAnz0,nPolyAnz1);
//STRIP001  BOOL bNeedDot=FALSE;
//STRIP001  for (nPolyNum=nMinPolyAnz; nPolyNum>0;) { // unveraenderte Polygonteile entfernen
//STRIP001      nPolyNum--;
//STRIP001      const XPolygon& rXP0=rXPP0[nPolyNum];
//STRIP001      const XPolygon& rXP1=rXPP1[nPolyNum];
//STRIP001      USHORT nPntAnz0=rXP0.GetPointCount();
//STRIP001      USHORT nPntAnz1=rXP1.GetPointCount();
//STRIP001      USHORT nMinPntAnz=Min(nPntAnz0,nPntAnz1);
//STRIP001      USHORT nEquCnt0=0;
//STRIP001      USHORT nEquCnt1=0;
//STRIP001      for (USHORT nPntNum=0; nPntNum<nMinPntAnz; nPntNum++) {
//STRIP001          if (rXP0[nPntNum]==rXP1[nPntNum]) {
//STRIP001              nEquCnt0=nEquCnt1;
//STRIP001              BOOL bCtrl0=(nPntNum<nMinPntAnz) && rXP0.IsControl(nPntNum+1);
//STRIP001              BOOL bCtrl1=(nPntNum<nMinPntAnz) && rXP1.IsControl(nPntNum+1);
//STRIP001              if (bCtrl0==bCtrl1) {
//STRIP001                  nEquCnt1=nPntNum+1;
//STRIP001                  if (bCtrl0) {
//STRIP001                      nPntNum++;
//STRIP001                      if (rXP0[nPntNum]==rXP1[nPntNum]) {
//STRIP001                          nPntNum++;
//STRIP001                          if (rXP0[nPntNum]==rXP1[nPntNum]) {
//STRIP001                              nEquCnt1=nPntNum+1;
//STRIP001                          } else nPntNum=nMinPntAnz; // sowas wie break.
//STRIP001                      } else nPntNum=nMinPntAnz; // sowas wie break.
//STRIP001                  }
//STRIP001              } else nPntNum=nMinPntAnz; // sowas wie break.
//STRIP001          } else nPntNum=nMinPntAnz; // sowas wie break.
//STRIP001      }
//STRIP001      if (nEquCnt0!=0) {
//STRIP001          rXPP0[nPolyNum].Remove(0,nEquCnt0);
//STRIP001          rXPP1[nPolyNum].Remove(0,nEquCnt0);
//STRIP001 #ifndef MAC // anderes Polygonpainting beim Mac
//STRIP001          if (nPolyNum==nMinPolyAnz-1 &&
//STRIP001              (rXPP0[nPolyNum].GetPointCount()<=1 ||
//STRIP001               rXPP1[nPolyNum].GetPointCount()<=1)) bNeedDot=TRUE;
//STRIP001 #endif
//STRIP001      }
//STRIP001  }
//STRIP001  aDragStat.SetShown(TRUE);
//STRIP001  USHORT nOutNum=0;
//STRIP001  do {
//STRIP001      Window* pO= (Window*)pDragWin;
//STRIP001      if (pO==NULL) {
//STRIP001          pO=(Window*)GetWin(nOutNum);
//STRIP001          nOutNum++;
//STRIP001      }
//STRIP001      if (pO!=NULL) {
//STRIP001          ImpSdrHdcMerk aHDCMerk(*pO,SDRHDC_SAVEALL,bRestoreColors);
//STRIP001          RasterOp eRop0=pO->GetRasterOp();
//STRIP001          pO->SetRasterOp(ROP_INVERT);
//STRIP001          pXOut->SetOutDev(pO);
//STRIP001
//STRIP001          Color aBlackColor( COL_BLACK );
//STRIP001          Color aTranspColor( COL_TRANSPARENT );
//STRIP001          pXOut->OverrideLineColor( aBlackColor );
//STRIP001          pXOut->OverrideFillColor( aTranspColor );
//STRIP001          pXOut->SetOffset(pCreatePV->GetOffset());
//STRIP001          USHORT nAnz=rXPP0.Count();
//STRIP001          USHORT i;
//STRIP001          for (i=0; i<nAnz; i++) {
//STRIP001              pXOut->DrawXPolyLine(rXPP0[i]);
//STRIP001          }
//STRIP001          nAnz=rXPP1.Count();
//STRIP001          for (i=0; i<nAnz; i++) {
//STRIP001              pXOut->DrawXPolyLine(rXPP1[i]);
//STRIP001              if (bNeedDot && nPolyNum==nMinPolyAnz-1) {
//STRIP001                  Point aPt(rXPP1[i][0]);
//STRIP001                  //pO->InvertRect(Rectangle(aPt,aPt));
//STRIP001                  pO->Invert( Rectangle( aPt, aPt ) );
//STRIP001              }
//STRIP001          }
//STRIP001          pXOut->SetOffset(Point(0,0));
//STRIP001          pO->SetRasterOp(eRop0);
//STRIP001          if (bRestoreColors) aHDCMerk.Restore(*pO);
//STRIP001      }
//STRIP001  } while (pDragWin==NULL && nOutNum<GetWinCount());
//STRIP001 }

//STRIP001 void SdrCreateView::DrawCreateObj(OutputDevice* pOut, BOOL bFull) const
//STRIP001 {
//STRIP001  if (IsSolidDraggingNow()) return;
//STRIP001  if (IsCreateObj()) {
//STRIP001      USHORT i=0;
//STRIP001      do {
//STRIP001          OutputDevice* pO=pOut;
//STRIP001          if (pO==NULL) {
//STRIP001              pO=GetWin(i);
//STRIP001              i++;
//STRIP001          }
//STRIP001          if (pO!=NULL) {
//STRIP001              ImpSdrHdcMerk aHDCMerk(*pO,SDRHDC_SAVEALL,bRestoreColors);
//STRIP001              RasterOp eRop0=pO->GetRasterOp();
//STRIP001              pO->SetRasterOp(ROP_INVERT);
//STRIP001              pXOut->SetOutDev(pO);
//STRIP001              Color aBlackColor( COL_BLACK );
//STRIP001              Color aTranspColor( COL_TRANSPARENT );
//STRIP001              pXOut->OverrideLineColor( aBlackColor );
//STRIP001              pXOut->OverrideFillColor( aTranspColor );
//STRIP001              pXOut->SetOffset(pCreatePV->GetOffset());
//STRIP001              XPolyPolygon aXPP(pCreatePV->DragPoly());
//STRIP001              USHORT nAnz=aXPP.Count();
//STRIP001              for (USHORT i=0; i<nAnz; i++) {
//STRIP001                  pXOut->DrawXPolyLine(aXPP[i]);
//STRIP001              }
//STRIP001              pXOut->SetOffset(Point(0,0));
//STRIP001              pO->SetRasterOp(eRop0);
//STRIP001              if (bRestoreColors) aHDCMerk.Restore(*pO);
//STRIP001          }
//STRIP001      } while (pOut==NULL && i<GetWinCount());
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCreateView::ShowCreateObj(OutputDevice* pOut, BOOL bFull)
//STRIP001 {
//STRIP001  if (IsCreateObj() && !aDragStat.IsShown()) {
//STRIP001      XPolyPolygon aXPP;
//STRIP001      if (pLibObjDragMeth==NULL) {
//STRIP001          pAktCreate->TakeCreatePoly(aDragStat,pCreatePV->DragPoly());
//STRIP001      }
//STRIP001      DrawCreateObj(pOut,bFull);
//STRIP001      aDragStat.SetShown(TRUE);
//STRIP001
//STRIP001      // #i3705# set shown state at views
//STRIP001      if(pOut)
//STRIP001      {
//STRIP001          sal_uInt16 nw(aWinList.Find(pOut));
//STRIP001
//STRIP001          if(nw < GetWinCount() && SDRVIEWWIN_NOTFOUND != nw)
//STRIP001          {
//STRIP001              if(!IsShownXorVisibleWinNum(nw))
//STRIP001              {
//STRIP001                  SetShownXorVisible(nw, TRUE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCreateView::HideCreateObj(OutputDevice* pOut, BOOL bFull)
//STRIP001 {
//STRIP001  if (IsCreateObj() && aDragStat.IsShown()) {
//STRIP001      DrawCreateObj(pOut,bFull);
//STRIP001      aDragStat.SetShown(FALSE);
//STRIP001
//STRIP001      // #i3705# clear shown state at views
//STRIP001      if(pOut)
//STRIP001      {
//STRIP001          sal_uInt16 nw(aWinList.Find(pOut));
//STRIP001
//STRIP001          if(nw < GetWinCount() && SDRVIEWWIN_NOTFOUND != nw)
//STRIP001          {
//STRIP001              if(IsShownXorVisibleWinNum(nw))
//STRIP001              {
//STRIP001                  SetShownXorVisible(nw, FALSE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/* new interface src537 */
//STRIP001 BOOL SdrCreateView::GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr) const
//STRIP001 {
//STRIP001  if(pAktCreate)
//STRIP001  {
//STRIP001      rTargetSet.Put(pAktCreate->GetItemSet());
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return SdrDragView::GetAttributes(rTargetSet, bOnlyHardAttr);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrCreateView::SetAttributes(const SfxItemSet& rSet, BOOL bReplaceAll)
//STRIP001 {
//STRIP001  if(pAktCreate)
//STRIP001  {
//STRIP001      SdrBroadcastItemChange aItemChange(*pAktCreate);
//STRIP001      if(bReplaceAll)
//STRIP001          pAktCreate->ClearItem();
//STRIP001      pAktCreate->SetItemSet(rSet);
//STRIP001      pAktCreate->BroadcastItemChange(aItemChange);
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return SdrDragView::SetAttributes(rSet,bReplaceAll);
//STRIP001  }
//STRIP001 }

//STRIP001 SfxStyleSheet* SdrCreateView::GetStyleSheet(BOOL& rOk) const
//STRIP001 {
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      rOk=TRUE;
//STRIP001      return pAktCreate->GetStyleSheet();
//STRIP001  } else {
//STRIP001      return SdrDragView::GetStyleSheet(rOk);
//STRIP001  }
//STRIP001 }

/*N*/ BOOL SdrCreateView::SetStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  if (pAktCreate!=NULL) {
//STRIP001      pAktCreate->SetStyleSheet(pStyleSheet,bDontRemoveHardAttr);
//STRIP001      return TRUE;
//STRIP001  } else {
//STRIP001      return SdrDragView::SetStyleSheet(pStyleSheet,bDontRemoveHardAttr);
//STRIP001  }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCreateView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   SdrDragView::WriteRecords(rOut);
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCROBJECT);
/*N*/       rOut<<nAktInvent;
/*N*/       rOut<<nAktIdent;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCRFLAGS);
/*N*/       rOut<<BOOL(b1stPointAsCenter);
/*N*/   } {
/*N*/       // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWTEXTEDIT);
/*N*/       rOut<<BOOL(bQuickTextEditMode);
/*N*/   } {
/*N*/       // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWMACRO);
/*N*/       rOut<<BOOL(bMacroMode);
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrCreateView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWCROBJECT: {
/*N*/               UINT32 nInvent;
/*N*/               UINT16 nIdent;
/*N*/               rIn>>nInvent;
/*N*/               rIn>>nIdent;
/*N*/               SetCurrentObj(nIdent,nInvent);
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWCRFLAGS: {
/*N*/               BOOL bTmp; rIn>>bTmp; b1stPointAsCenter=bTmp;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWTEXTEDIT: {
/*N*/               // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/               BOOL bTmp; rIn>>bTmp; bQuickTextEditMode=bTmp;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWMACRO: {
/*N*/               // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/               BOOL bTmp; rIn>>bTmp; bMacroMode=bTmp;
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrDragView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

