/*************************************************************************
 *
 *  $RCSfile: svx_svdxcgv.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:42 $
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

#include <vector>
#include "editeng.hxx"
#include "xexch.hxx"
#include "xflclit.hxx"
#include "svdxcgv.hxx"
#include "svdoutl.hxx"
#include "svditext.hxx"
#include "svdetc.hxx"
#include "svdxout.hxx"
#include "svdundo.hxx"
#include "svdograf.hxx"
#include "svdoole2.hxx" // fuer kein OLE im SdrClipboardFormat
#include "svdorect.hxx"
#include "svdoedge.hxx" // fuer Konnektoren uebers Clipboard
#include "svdopage.hxx" // fuer Konnektoren uebers Clipboard
#include "svdpage.hxx"
#include "svdpagv.hxx"
#include "svdtrans.hxx" // Fuer GetMapFactor zum umskalieren bei PasteModel
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
#include "xoutbmp.hxx"

#ifndef _SV_METAACT_HXX
#include <vcl/metaact.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif
#ifndef _SOT_FORMATS_HXX //autogen
#include <sot/formats.hxx>
#endif

// #i13033#
#ifndef _CLONELIST_HXX_
#include <clonelist.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrExchangeView::SdrExchangeView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrObjEditView(pModel1,pOut)
/*N*/ {
/*N*/ }

/*?*/ SdrExchangeView::SdrExchangeView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrObjEditView(pModel1,pXOut)
/*?*/ {
/*?*/ }
//STRIP001
//STRIP001 ////////////////////////////////////////////////////////////////////////////////////////////////////
//STRIP001
//STRIP001 Point SdrExchangeView::GetViewCenter(const OutputDevice* pOut) const
//STRIP001 {
//STRIP001  Point aCenter;
//STRIP001  if (pOut==NULL) pOut=GetWin(0);
//STRIP001  if (pOut!=NULL) {
//STRIP001      Point aOfs=pOut->GetMapMode().GetOrigin();
//STRIP001      Size aOutSiz=pOut->GetOutputSize();
//STRIP001      aOutSiz.Width()/=2;
//STRIP001      aOutSiz.Height()/=2;
//STRIP001      aCenter.X()=aOutSiz.Width() -aOfs.X();
//STRIP001      aCenter.Y()=aOutSiz.Height()-aOfs.Y();
//STRIP001  }
//STRIP001  return aCenter;
//STRIP001 }
//STRIP001
//STRIP001 Point SdrExchangeView::GetPastePos(SdrObjList* pLst, OutputDevice* pOut)
//STRIP001 {
//STRIP001  Point aP(GetViewCenter(pOut));
//STRIP001  SdrPage* pPg=NULL;
//STRIP001  if (pLst!=NULL) pPg=pLst->GetPage();
//STRIP001  if (pPg!=NULL) {
//STRIP001      Size aSiz(pPg->GetSize());
//STRIP001      aP.X()=aSiz.Width()/2;
//STRIP001      aP.Y()=aSiz.Height()/2;
//STRIP001  }
//STRIP001  return aP;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::ImpLimitToWorkArea(Point& rPt, const SdrPageView* pPV) const
//STRIP001 {
//STRIP001  BOOL bRet(FALSE);
//STRIP001
//STRIP001  if(!aMaxWorkArea.IsEmpty())
//STRIP001  {
//STRIP001      if(pPV)
//STRIP001          rPt += pPV->GetOffset();
//STRIP001
//STRIP001      if(rPt.X()<aMaxWorkArea.Left())
//STRIP001      {
//STRIP001          rPt.X() = aMaxWorkArea.Left();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if(rPt.X()>aMaxWorkArea.Right())
//STRIP001      {
//STRIP001          rPt.X() = aMaxWorkArea.Right();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if(rPt.Y()<aMaxWorkArea.Top())
//STRIP001      {
//STRIP001          rPt.Y() = aMaxWorkArea.Top();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if(rPt.Y()>aMaxWorkArea.Bottom())
//STRIP001      {
//STRIP001          rPt.Y() = aMaxWorkArea.Bottom();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if(pPV)
//STRIP001          rPt -= pPV->GetOffset();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 void SdrExchangeView::ImpGetPasteObjList(Point& rPos, SdrObjList*& rpLst)
//STRIP001 {
//STRIP001  if (rpLst==NULL) {
//STRIP001      SdrPageView* pPV=GetPageView(rPos);
//STRIP001      if (pPV!=NULL) {
//STRIP001          rpLst=pPV->GetObjList();
//STRIP001          rPos-=pPV->GetOffset();
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::ImpGetPasteLayer(const SdrObjList* pObjList, SdrLayerID& rLayer) const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  rLayer=0;
//STRIP001  if (pObjList!=NULL) {
//STRIP001      const SdrPage* pPg=pObjList->GetPage();
//STRIP001      if (pPg!=NULL) {
//STRIP001          rLayer=pPg->GetLayerAdmin().GetLayerID(aAktLayer,TRUE);
//STRIP001          if (rLayer==SDRLAYER_NOTFOUND) rLayer=0;
//STRIP001          SdrPageView* pPV=GetPageView(pPg);
//STRIP001          if (pPV!=NULL) {
//STRIP001              bRet=!pPV->GetLockedLayers().IsSet(rLayer) && pPV->GetVisibleLayers().IsSet(rLayer);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 ////////////////////////////////////////////////////////////////////////////////////////////////////
//STRIP001
//STRIP001 BOOL SdrExchangeView::Paste(const GDIMetaFile& rMtf, const Point& rPos, SdrObjList* pLst, UINT32 nOptions)
//STRIP001 {
//STRIP001  Point aPos(rPos);
//STRIP001  ImpGetPasteObjList(aPos,pLst);
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  for ( USHORT nv = 0; nv < GetPageViewCount() && !pMarkPV; nv++ )
//STRIP001  {
//STRIP001      SdrPageView* pPV = GetPageViewPvNum(nv);
//STRIP001      if ( pPV->GetObjList() == pLst )
//STRIP001          pMarkPV=pPV;
//STRIP001  }
//STRIP001
//STRIP001  ImpLimitToWorkArea( aPos, pMarkPV );
//STRIP001  if (pLst==NULL) return FALSE;
//STRIP001  SdrLayerID nLayer;
//STRIP001  if (!ImpGetPasteLayer(pLst,nLayer)) return FALSE;
//STRIP001  BOOL bUnmark=(nOptions&(SDRINSERT_DONTMARK|SDRINSERT_ADDMARK))==0 && !IsTextEdit();
//STRIP001  if (bUnmark) UnmarkAllObj();
//STRIP001  SdrGrafObj* pObj=new SdrGrafObj(Graphic(rMtf));
//STRIP001  pObj->SetLayer(nLayer);
//STRIP001  ImpPasteObject(pObj,*pLst,aPos,rMtf.GetPrefSize(),rMtf.GetPrefMapMode(),nOptions);
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::Paste(const Bitmap& rBmp, const Point& rPos, SdrObjList* pLst, UINT32 nOptions)
//STRIP001 {
//STRIP001  Point aPos(rPos);
//STRIP001  ImpGetPasteObjList(aPos,pLst);
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  for ( USHORT nv = 0; nv < GetPageViewCount() && !pMarkPV; nv++ )
//STRIP001  {
//STRIP001      SdrPageView* pPV = GetPageViewPvNum(nv);
//STRIP001      if ( pPV->GetObjList() == pLst )
//STRIP001          pMarkPV=pPV;
//STRIP001  }
//STRIP001
//STRIP001  ImpLimitToWorkArea( aPos, pMarkPV );
//STRIP001  if (pLst==NULL) return FALSE;
//STRIP001  SdrLayerID nLayer;
//STRIP001  if (!ImpGetPasteLayer(pLst,nLayer)) return FALSE;
//STRIP001  BOOL bUnmark=(nOptions&(SDRINSERT_DONTMARK|SDRINSERT_ADDMARK))==0 && !IsTextEdit();
//STRIP001  if (bUnmark) UnmarkAllObj();
//STRIP001  SdrGrafObj* pObj=new SdrGrafObj(Graphic(rBmp));
//STRIP001  pObj->SetLayer(nLayer);
//STRIP001  ImpPasteObject(pObj,*pLst,aPos,rBmp.GetSizePixel(),MapMode(MAP_PIXEL),nOptions);
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::Paste(const XubString& rStr, const Point& rPos, SdrObjList* pLst, UINT32 nOptions)
//STRIP001 {
//STRIP001  if(!rStr.Len())
//STRIP001      return FALSE;
//STRIP001
//STRIP001  Point aPos(rPos);
//STRIP001  ImpGetPasteObjList(aPos,pLst);
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  for ( USHORT nv = 0; nv < GetPageViewCount() && !pMarkPV; nv++ )
//STRIP001  {
//STRIP001      SdrPageView* pPV = GetPageViewPvNum(nv);
//STRIP001      if ( pPV->GetObjList() == pLst )
//STRIP001          pMarkPV=pPV;
//STRIP001  }
//STRIP001
//STRIP001  ImpLimitToWorkArea( aPos, pMarkPV );
//STRIP001  if (pLst==NULL) return FALSE;
//STRIP001  SdrLayerID nLayer;
//STRIP001  if (!ImpGetPasteLayer(pLst,nLayer)) return FALSE;
//STRIP001  BOOL bUnmark=(nOptions&(SDRINSERT_DONTMARK|SDRINSERT_ADDMARK))==0 && !IsTextEdit();
//STRIP001  if (bUnmark) UnmarkAllObj();
//STRIP001  Rectangle aTextRect(0,0,500,500);
//STRIP001  SdrPage* pPage=pLst->GetPage();
//STRIP001  if (pPage!=NULL) {
//STRIP001      aTextRect.SetSize(pPage->GetSize());
//STRIP001  }
//STRIP001  SdrRectObj* pObj=new SdrRectObj(OBJ_TEXT,aTextRect);
//STRIP001  pObj->SetModel(pMod);
//STRIP001  pObj->SetLayer(nLayer);
//STRIP001  pObj->NbcSetText(rStr); // #32424# SetText vor SetAttr, weil SetAttr sonst unwirksam!
//STRIP001  if (pDefaultStyleSheet!=NULL) pObj->NbcSetStyleSheet(pDefaultStyleSheet,FALSE);
//STRIP001
//STRIP001  pObj->SetItemSet(aDefaultAttr);
//STRIP001
//STRIP001  SfxItemSet aTempAttr(pMod->GetItemPool());  // Keine Fuellung oder Linie
//STRIP001  aTempAttr.Put(XLineStyleItem(XLINE_NONE));
//STRIP001  aTempAttr.Put(XFillStyleItem(XFILL_NONE));
//STRIP001
//STRIP001  pObj->SetItemSet(aTempAttr);
//STRIP001
//STRIP001  pObj->FitFrameToTextSize();
//STRIP001  Size aSiz(pObj->GetLogicRect().GetSize());
//STRIP001  MapUnit eMap=pMod->GetScaleUnit();
//STRIP001  Fraction aMap=pMod->GetScaleFraction();
//STRIP001  ImpPasteObject(pObj,*pLst,aPos,aSiz,MapMode(eMap,Point(0,0),aMap,aMap),nOptions);
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::Paste(SvStream& rInput, USHORT eFormat, const Point& rPos, SdrObjList* pLst, UINT32 nOptions)
//STRIP001 {
//STRIP001  Point aPos(rPos);
//STRIP001  ImpGetPasteObjList(aPos,pLst);
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  for ( USHORT nv = 0; nv < GetPageViewCount() && !pMarkPV; nv++ )
//STRIP001  {
//STRIP001      SdrPageView* pPV = GetPageViewPvNum(nv);
//STRIP001      if ( pPV->GetObjList() == pLst )
//STRIP001          pMarkPV=pPV;
//STRIP001  }
//STRIP001
//STRIP001  ImpLimitToWorkArea( aPos, pMarkPV );
//STRIP001  if (pLst==NULL) return FALSE;
//STRIP001  SdrLayerID nLayer;
//STRIP001  if (!ImpGetPasteLayer(pLst,nLayer)) return FALSE;
//STRIP001  BOOL bUnmark=(nOptions&(SDRINSERT_DONTMARK|SDRINSERT_ADDMARK))==0 && !IsTextEdit();
//STRIP001  if (bUnmark) UnmarkAllObj();
//STRIP001  Rectangle aTextRect(0,0,500,500);
//STRIP001  SdrPage* pPage=pLst->GetPage();
//STRIP001  if (pPage!=NULL) {
//STRIP001      aTextRect.SetSize(pPage->GetSize());
//STRIP001  }
//STRIP001  SdrRectObj* pObj=new SdrRectObj(OBJ_TEXT,aTextRect);
//STRIP001  pObj->SetModel(pMod);
//STRIP001  pObj->SetLayer(nLayer);
//STRIP001  if (pDefaultStyleSheet!=NULL) pObj->NbcSetStyleSheet(pDefaultStyleSheet,FALSE);
//STRIP001
//STRIP001  pObj->SetItemSet(aDefaultAttr);
//STRIP001
//STRIP001  SfxItemSet aTempAttr(pMod->GetItemPool());  // Keine Fuellung oder Linie
//STRIP001  aTempAttr.Put(XLineStyleItem(XLINE_NONE));
//STRIP001  aTempAttr.Put(XFillStyleItem(XFILL_NONE));
//STRIP001
//STRIP001  pObj->SetItemSet(aTempAttr);
//STRIP001
//STRIP001  pObj->NbcSetText(rInput,eFormat);
//STRIP001  pObj->FitFrameToTextSize();
//STRIP001  Size aSiz(pObj->GetLogicRect().GetSize());
//STRIP001  MapUnit eMap=pMod->GetScaleUnit();
//STRIP001  Fraction aMap=pMod->GetScaleFraction();
//STRIP001  ImpPasteObject(pObj,*pLst,aPos,aSiz,MapMode(eMap,Point(0,0),aMap,aMap),nOptions);
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::Paste(const SdrModel& rMod, const Point& rPos, SdrObjList* pLst, UINT32 nOptions)
//STRIP001 {
//STRIP001  const SdrModel* pSrcMod=&rMod;
//STRIP001  if (pSrcMod==pMod) return FALSE; // na so geht's ja nun nicht
//STRIP001  Point aPos(rPos);
//STRIP001  ImpGetPasteObjList(aPos,pLst);
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  for ( USHORT nv = 0; nv < GetPageViewCount() && !pMarkPV; nv++ )
//STRIP001  {
//STRIP001      SdrPageView* pPV = GetPageViewPvNum(nv);
//STRIP001      if ( pPV->GetObjList() == pLst )
//STRIP001          pMarkPV=pPV;
//STRIP001  }
//STRIP001
//STRIP001  ImpLimitToWorkArea( aPos, pMarkPV );
//STRIP001  if (pLst==NULL) return FALSE;
//STRIP001  BOOL bUnmark=(nOptions&(SDRINSERT_DONTMARK|SDRINSERT_ADDMARK))==0 && !IsTextEdit();
//STRIP001  if (bUnmark) UnmarkAllObj();
//STRIP001
//STRIP001  // evtl. umskalieren bei unterschiedlicher MapUnit am Model
//STRIP001  // Dafuer erstmal die Faktoren berechnen
//STRIP001  MapUnit eSrcUnit=pSrcMod->GetScaleUnit();
//STRIP001  MapUnit eDstUnit=pMod->GetScaleUnit();
//STRIP001  BOOL bResize=eSrcUnit!=eDstUnit;
//STRIP001  Fraction xResize,yResize;
//STRIP001  Point aPt0;
//STRIP001  if (bResize) {
//STRIP001      FrPair aResize(GetMapFactor(eSrcUnit,eDstUnit));
//STRIP001      xResize=aResize.X();
//STRIP001      yResize=aResize.Y();
//STRIP001  }
//STRIP001  SdrObjList*  pDstLst=pLst;
//STRIP001  USHORT nPg,nPgAnz=pSrcMod->GetPageCount();
//STRIP001  BegUndo(ImpGetResStr(STR_ExchangePaste));
//STRIP001  for (nPg=0; nPg<nPgAnz; nPg++) {
//STRIP001      const SdrPage* pSrcPg=pSrcMod->GetPage(nPg);
//STRIP001
//STRIP001      // #104148# Use SnapRect, not BoundRect here
//STRIP001      Rectangle aR=pSrcPg->GetAllObjSnapRect();
//STRIP001
//STRIP001      if (bResize) ResizeRect(aR,aPt0,xResize,yResize);
//STRIP001      Point aDist(aPos-aR.Center());
//STRIP001      Size  aSiz(aDist.X(),aDist.Y());
//STRIP001      ULONG nDstObjAnz0=pDstLst->GetObjCount();
//STRIP001      ULONG nCloneErrCnt=0;
//STRIP001      ULONG nOb,nObAnz=pSrcPg->GetObjCount();
//STRIP001      BOOL bMark=pMarkPV!=NULL && !IsTextEdit() && (nOptions&SDRINSERT_DONTMARK)==0;
//STRIP001
//STRIP001      // #i13033#
//STRIP001      // New mechanism to re-create the connections of cloned connectors
//STRIP001      CloneList aCloneList;
//STRIP001
//STRIP001      for (nOb=0; nOb<nObAnz; nOb++) {
//STRIP001          const SdrObject* pSrcOb=pSrcPg->GetObj(nOb);
//STRIP001          SdrObject* pNeuObj=pSrcOb->Clone(pDstLst->GetPage(),pDstLst->GetModel());
//STRIP001          if (pNeuObj!=NULL) {
//STRIP001              if (bResize) {
//STRIP001                  pNeuObj->GetModel()->SetPasteResize(TRUE); // #51139#
//STRIP001                  pNeuObj->NbcResize(aPt0,xResize,yResize);
//STRIP001                  pNeuObj->GetModel()->SetPasteResize(FALSE); // #51139#
//STRIP001              }
//STRIP001              pNeuObj->NbcMove(aSiz);
//STRIP001
//STRIP001              const SdrPage* pPg = pDstLst->GetPage();
//STRIP001              if ( pPg )
//STRIP001                  pNeuObj->SetLayer( pPg->GetLayerAdmin().GetLayerID(aAktLayer, TRUE) );
//STRIP001
//STRIP001              SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001              pDstLst->InsertObject(pNeuObj,CONTAINER_APPEND,&aReason);
//STRIP001
//STRIP001              AddUndo(new SdrUndoNewObj(*pNeuObj));
//STRIP001              if (bMark) {
//STRIP001                  // Markhandles noch nicht sofort setzen!
//STRIP001                  // Das erledigt das ModelHasChanged der MarkView.
//STRIP001                  MarkObj(pNeuObj,pMarkPV,FALSE,TRUE);
//STRIP001              }
//STRIP001
//STRIP001              // #i13033#
//STRIP001              aCloneList.AddPair(pSrcOb, pNeuObj);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nCloneErrCnt++;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // #i13033#
//STRIP001      // New mechanism to re-create the connections of cloned connectors
//STRIP001      aCloneList.CopyConnections();
//STRIP001
//STRIP001      if(0L != nCloneErrCnt)
//STRIP001      {
//STRIP001 #ifdef DBG_UTIL
//STRIP001          ByteString aStr("SdrExchangeView::Paste(): Fehler beim Clonen ");
//STRIP001
//STRIP001          if(nCloneErrCnt == 1)
//STRIP001          {
//STRIP001              aStr += "eines Zeichenobjekts.";
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aStr += "von ";
//STRIP001              aStr += ByteString::CreateFromInt32( nCloneErrCnt );
//STRIP001              aStr += " Zeichenobjekten.";
//STRIP001          }
//STRIP001
//STRIP001          aStr += " Objektverbindungen werden nicht mitkopiert.";
//STRIP001
//STRIP001          DBG_ERROR(aStr.GetBuffer());
//STRIP001 #endif
//STRIP001      }
//STRIP001  }
//STRIP001  EndUndo();
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SdrExchangeView::IsExchangeFormatSupported(ULONG nFormat) const
//STRIP001 {
//STRIP001     return( FORMAT_PRIVATE == nFormat ||
//STRIP001          FORMAT_GDIMETAFILE == nFormat ||
//STRIP001          FORMAT_BITMAP == nFormat ||
//STRIP001          FORMAT_RTF == nFormat ||
//STRIP001          FORMAT_STRING == nFormat ||
//STRIP001          SOT_FORMATSTR_ID_DRAWING == nFormat ||
//STRIP001          SOT_FORMATSTR_ID_EDITENGINE == nFormat );
//STRIP001 }
//STRIP001
//STRIP001 void SdrExchangeView::ImpPasteObject(SdrObject* pObj, SdrObjList& rLst, const Point& rCenter, const Size& rSiz, const MapMode& rMap, UINT32 nOptions)
//STRIP001 {
//STRIP001  BigInt nSizX(rSiz.Width());
//STRIP001  BigInt nSizY(rSiz.Height());
//STRIP001  MapUnit eSrcMU=rMap.GetMapUnit();
//STRIP001  MapUnit eDstMU=pMod->GetScaleUnit();
//STRIP001  FrPair aMapFact(GetMapFactor(eSrcMU,eDstMU));
//STRIP001  Fraction aDstFr(pMod->GetScaleFraction());
//STRIP001  nSizX*=aMapFact.X().GetNumerator();
//STRIP001  nSizX*=rMap.GetScaleX().GetNumerator();
//STRIP001  nSizX*=aDstFr.GetDenominator();
//STRIP001  nSizX/=aMapFact.X().GetDenominator();
//STRIP001  nSizX/=rMap.GetScaleX().GetDenominator();
//STRIP001  nSizX/=aDstFr.GetNumerator();
//STRIP001  nSizY*=aMapFact.Y().GetNumerator();
//STRIP001  nSizY*=rMap.GetScaleY().GetNumerator();
//STRIP001  nSizX*=aDstFr.GetDenominator();
//STRIP001  nSizY/=aMapFact.Y().GetDenominator();
//STRIP001  nSizY/=rMap.GetScaleY().GetDenominator();
//STRIP001  nSizY/=aDstFr.GetNumerator();
//STRIP001  long xs=nSizX;
//STRIP001  long ys=nSizY;
//STRIP001  Point aPos(rCenter.X()-xs/2,rCenter.Y()-ys/2);
//STRIP001  Rectangle aR(aPos.X(),aPos.Y(),aPos.X()+xs,aPos.Y()+ys);
//STRIP001  pObj->SetLogicRect(aR);
//STRIP001  SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001  rLst.InsertObject(pObj,CONTAINER_APPEND,&aReason);
//STRIP001  AddUndo(new SdrUndoNewObj(*pObj));
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  for (USHORT nv=0; nv<GetPageViewCount() && pMarkPV==NULL; nv++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001      if (pPV->GetObjList()==&rLst) pMarkPV=pPV;
//STRIP001  }
//STRIP001  BOOL bMark=pMarkPV!=NULL && !IsTextEdit() && (nOptions&SDRINSERT_DONTMARK)==0;
//STRIP001  if (bMark) { // Obj in der ersten gefundenen PageView markieren
//STRIP001      MarkObj(pObj,pMarkPV);
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 ////////////////////////////////////////////////////////////////////////////////////////////////////
//STRIP001
//STRIP001 Bitmap SdrExchangeView::GetMarkedObjBitmap( BOOL bNoVDevIfOneBmpMarked ) const
//STRIP001 {
//STRIP001  Bitmap aBmp;
//STRIP001
//STRIP001  if( HasMarkedObj() )
//STRIP001  {
//STRIP001      if( bNoVDevIfOneBmpMarked )
//STRIP001      {
//STRIP001          SdrObject*  pGrafObjTmp = aMark.GetMark( 0 )->GetObj();
//STRIP001          SdrGrafObj* pGrafObj = ( aMark.GetMarkCount() == 1 ) ? PTR_CAST( SdrGrafObj, pGrafObjTmp ) : NULL;
//STRIP001
//STRIP001          if( pGrafObj && ( pGrafObj->GetGraphicType() == GRAPHIC_BITMAP ) )
//STRIP001              aBmp = pGrafObj->GetTransformedGraphic().GetBitmap();
//STRIP001      }
//STRIP001
//STRIP001      if( !aBmp )
//STRIP001      {
//STRIP001          const Graphic aGraphic( GetMarkedObjMetaFile( bNoVDevIfOneBmpMarked ) );
//STRIP001          aBmp = aGraphic.GetBitmap();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aBmp;
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
/*?*/ GDIMetaFile SdrExchangeView::GetMarkedObjMetaFile( BOOL bNoVDevIfOneMtfMarked ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); GDIMetaFile aMtf; return aMtf;//STRIP001
//STRIP001     GDIMetaFile aMtf;
//STRIP001
//STRIP001     if( HasMarkedObj() )
//STRIP001  {
//STRIP001      Rectangle   aBound( GetMarkedObjBoundRect() );
//STRIP001      Size        aBoundSize( aBound.GetWidth(), aBound.GetHeight() );
//STRIP001      MapMode     aMap( pMod->GetScaleUnit(), Point(), pMod->GetScaleFraction(), pMod->GetScaleFraction() );
//STRIP001
//STRIP001      if( bNoVDevIfOneMtfMarked )
//STRIP001      {
//STRIP001          SdrObject*  pGrafObjTmp = aMark.GetMark( 0 )->GetObj();
//STRIP001          SdrGrafObj* pGrafObj = ( aMark.GetMarkCount() ==1 ) ? PTR_CAST( SdrGrafObj, pGrafObjTmp ) : NULL;
//STRIP001
//STRIP001          if( pGrafObj )
//STRIP001             {
//STRIP001                 Graphic aGraphic( pGrafObj->GetTransformedGraphic() );
//STRIP001
//STRIP001                 if( aGraphic.GetType() == GRAPHIC_BITMAP )
//STRIP001                 {
//STRIP001                     const Point aPos;
//STRIP001
//STRIP001                     aMtf.AddAction( new MetaBmpExScaleAction( aPos, aBoundSize, aGraphic.GetBitmapEx() ) );
//STRIP001                  aMtf.SetPrefMapMode( aMap );
//STRIP001                  aMtf.SetPrefSize( aBoundSize );
//STRIP001                 }
//STRIP001                 else
//STRIP001                     aMtf = aGraphic.GetGDIMetaFile();
//STRIP001             }
//STRIP001      }
//STRIP001
//STRIP001      if( !aMtf.GetActionCount() )
//STRIP001      {
//STRIP001          VirtualDevice   aOut;
//STRIP001             Size            aDummySize( 2, 2 );
//STRIP001
//STRIP001             aOut.SetOutputSizePixel( aDummySize );
//STRIP001          aOut.EnableOutput( FALSE );
//STRIP001          aOut.SetMapMode( aMap );
//STRIP001
//STRIP001             aMtf.Clear();
//STRIP001          aMtf.Record( &aOut );
//STRIP001
//STRIP001             DrawMarkedObj( aOut, aBound.TopLeft() );
//STRIP001
//STRIP001             aMtf.Stop();
//STRIP001          aMtf.WindStart();
//STRIP001          aMtf.SetPrefMapMode( aMap );
//STRIP001
//STRIP001          // #i8506# Add something to the prefsize, to prevent
//STRIP001          // the draw shapes from clipping away the right/bottom-
//STRIP001          // most line. Honestly, I have not the slightest idea
//STRIP001          // why exactly 32 does the trick here, but that's the
//STRIP001          // smallest number which still works even for the highest
//STRIP001          // zoom level.
//STRIP001          // See also #108486# for further details.
//STRIP001          aMtf.SetPrefSize( Size(aBoundSize.Width()+32,
//STRIP001                                 aBoundSize.Height()+32) );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aMtf;
/*?*/ }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 Graphic SdrExchangeView::GetAllMarkedGraphic() const
//STRIP001 {
//STRIP001     Graphic aRet;
//STRIP001
//STRIP001     if( HasMarkedObj() )
//STRIP001     {
//STRIP001         if( ( 1 == aMark.GetMarkCount() ) && aMark.GetMark( 0 ) )
//STRIP001             aRet = SdrExchangeView::GetObjGraphic( pMod, aMark.GetMark( 0 )->GetObj() );
//STRIP001         else
//STRIP001             aRet = GetMarkedObjMetaFile( FALSE );
//STRIP001     }
//STRIP001
//STRIP001     return aRet;
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 Graphic SdrExchangeView::GetObjGraphic( SdrModel* pModel, SdrObject* pObj )
//STRIP001 {
//STRIP001     Graphic aRet;
//STRIP001
//STRIP001     if( pModel && pObj )
//STRIP001     {
//STRIP001         // try to get a graphic from the object first
//STRIP001         if( pObj->ISA( SdrGrafObj ) )
//STRIP001             aRet = static_cast< SdrGrafObj* >( pObj )->GetGraphic();
//STRIP001         else if( pObj->ISA( SdrOle2Obj ) )
//STRIP001         {
//STRIP001             SdrOle2Obj* pOLEObj = static_cast< SdrOle2Obj* >( pObj );
//STRIP001
//STRIP001             if( pOLEObj->HasGDIMetaFile() )
//STRIP001             {
//STRIP001                 const GDIMetaFile* pMtf = pOLEObj->GetGDIMetaFile();
//STRIP001
//STRIP001                 if( pMtf )
//STRIP001                     aRet = *pMtf;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // if graphic could not be retrieved => go the hard way and create a MetaFile
//STRIP001         if( ( GRAPHIC_NONE == aRet.GetType() ) || ( GRAPHIC_DEFAULT == aRet.GetType() ) )
//STRIP001         {
//STRIP001          VirtualDevice   aOut;
//STRIP001          ExtOutputDevice aXOut( &aOut);
//STRIP001          SdrPaintInfoRec aInfoRec;
//STRIP001             GDIMetaFile     aMtf;
//STRIP001          const Rectangle aBoundRect( pObj->GetBoundRect() );
//STRIP001          const MapMode   aMap( pModel->GetScaleUnit(),
//STRIP001                                   Point(),
//STRIP001                                pModel->GetScaleFraction(),
//STRIP001                                   pModel->GetScaleFraction() );
//STRIP001
//STRIP001          aOut.EnableOutput( FALSE );
//STRIP001          aOut.SetMapMode( aMap );
//STRIP001          aMtf.Record( &aOut );
//STRIP001
//STRIP001          aXOut.SetOffset( Point( -aBoundRect.Left(), -aBoundRect.Top() ) );
//STRIP001          aInfoRec.nPaintMode |= SDRPAINTMODE_ANILIKEPRN;
//STRIP001             pObj->Paint( aXOut, aInfoRec );
//STRIP001
//STRIP001             aMtf.Stop();
//STRIP001          aMtf.WindStart();
//STRIP001          aMtf.SetPrefMapMode( aMap );
//STRIP001          aMtf.SetPrefSize( aBoundRect.GetSize() );
//STRIP001
//STRIP001             if( aMtf.GetActionCount() )
//STRIP001                 aRet = aMtf;
//STRIP001         }
//STRIP001      }
//STRIP001
//STRIP001      return aRet;
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 void SdrExchangeView::DrawMarkedObj(OutputDevice& rOut, const Point& rOfs) const
//STRIP001 {
//STRIP001  ((SdrExchangeView*)this)->aMark.ForceSort();
//STRIP001  pXOut->SetOutDev(&rOut);
//STRIP001  SdrPaintInfoRec aInfoRec;
//STRIP001  aInfoRec.nPaintMode|=SDRPAINTMODE_ANILIKEPRN;
//STRIP001
//STRIP001     ::std::vector< ::std::vector< SdrMark* > >  aObjVectors( 2 );
//STRIP001     ::std::vector< SdrMark* >&                  rObjVector1 = aObjVectors[ 0 ];
//STRIP001     ::std::vector< SdrMark* >&                  rObjVector2 = aObjVectors[ 1 ];
//STRIP001     const SdrLayerAdmin&                        rLayerAdmin = pMod->GetLayerAdmin();
//STRIP001     const sal_uInt32                            nControlLayerId = rLayerAdmin.GetLayerID( rLayerAdmin.GetControlLayerName(), FALSE );
//STRIP001     sal_uInt32                                  n, nCount;
//STRIP001
//STRIP001  for( n = 0, nCount = aMark.GetMarkCount(); n < nCount; n++ )
//STRIP001     {
//STRIP001         SdrMark* pMark = aMark.GetMark( n );
//STRIP001
//STRIP001         // paint objects on control layer on top of all otherobjects
//STRIP001         if( nControlLayerId == pMark->GetObj()->GetLayer() )
//STRIP001             rObjVector2.push_back( pMark );
//STRIP001         else
//STRIP001             rObjVector1.push_back( pMark );
//STRIP001     }
//STRIP001
//STRIP001     for( n = 0, nCount = aObjVectors.size(); n < nCount; n++ )
//STRIP001     {
//STRIP001         ::std::vector< SdrMark* >& rObjVector = aObjVectors[ n ];
//STRIP001
//STRIP001         for( sal_uInt32 i = 0; i < rObjVector.size(); i++ )
//STRIP001         {
//STRIP001          SdrMark*    pMark = rObjVector[ i ];
//STRIP001          Point       aOfs( -rOfs.X(),-rOfs.Y() );
//STRIP001
//STRIP001             aOfs += pMark->GetPageView()->GetOffset();
//STRIP001
//STRIP001             if( aOfs != pXOut->GetOffset() )
//STRIP001                 pXOut->SetOffset(aOfs);
//STRIP001
//STRIP001             pMark->GetObj()->Paint( *pXOut, aInfoRec );
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  pXOut->SetOffset( Point(0,0) );
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 SdrModel* SdrExchangeView::GetMarkedObjModel() const
//STRIP001 {
//STRIP001  // Wenn das sortieren der MarkList mal stoeren sollte,
//STRIP001  // werde ich sie mir wohl kopieren muessen.
//STRIP001  ((SdrExchangeView*)this)->aMark.ForceSort();
//STRIP001  SdrModel* pNeuMod=pMod->AllocModel();
//STRIP001  SdrPage* pNeuPag=pNeuMod->AllocPage(FALSE);
//STRIP001  pNeuMod->InsertPage(pNeuPag);
//STRIP001
//STRIP001     ::std::vector< ::std::vector< SdrMark* > >  aObjVectors( 2 );
//STRIP001     ::std::vector< SdrMark* >&                  rObjVector1 = aObjVectors[ 0 ];
//STRIP001     ::std::vector< SdrMark* >&                  rObjVector2 = aObjVectors[ 1 ];
//STRIP001     const SdrLayerAdmin&                        rLayerAdmin = pMod->GetLayerAdmin();
//STRIP001     const sal_uInt32                            nControlLayerId = rLayerAdmin.GetLayerID( rLayerAdmin.GetControlLayerName(), FALSE );
//STRIP001     sal_uInt32                                  n, nCount, nCloneErrCnt = 0;
//STRIP001
//STRIP001  for( n = 0, nCount = aMark.GetMarkCount(); n < nCount; n++ )
//STRIP001     {
//STRIP001         SdrMark* pMark = aMark.GetMark( n );
//STRIP001
//STRIP001         // paint objects on control layer on top of all otherobjects
//STRIP001         if( nControlLayerId == pMark->GetObj()->GetLayer() )
//STRIP001             rObjVector2.push_back( pMark );
//STRIP001         else
//STRIP001             rObjVector1.push_back( pMark );
//STRIP001     }
//STRIP001
//STRIP001  // #i13033#
//STRIP001  // New mechanism to re-create the connections of cloned connectors
//STRIP001  CloneList aCloneList;
//STRIP001
//STRIP001     for( n = 0, nCount = aObjVectors.size(); n < nCount; n++ )
//STRIP001     {
//STRIP001         ::std::vector< SdrMark* >& rObjVector = aObjVectors[ n ];
//STRIP001
//STRIP001         for( sal_uInt32 i = 0; i < rObjVector.size(); i++ )
//STRIP001         {
//STRIP001              const SdrMark*      pMark = rObjVector[ i ];
//STRIP001          const SdrObject*    pObj = pMark->GetObj();
//STRIP001             SdrObject*          pNeuObj;
//STRIP001
//STRIP001             if( pObj->ISA( SdrPageObj ) )
//STRIP001             {
//STRIP001                 // convert SdrPageObj's to a graphic representation, because
//STRIP001                 // virtual connection to referenced page gets lost in new model
//STRIP001                 pNeuObj = new SdrGrafObj( GetObjGraphic( pMod, const_cast< SdrObject* >( pObj ) ), pObj->GetLogicRect() );
//STRIP001                 pNeuObj->SetPage( pNeuPag );
//STRIP001                 pNeuObj->SetModel( pNeuMod );
//STRIP001             }
//STRIP001             else
//STRIP001              pNeuObj = pObj->Clone( pNeuPag, pNeuMod );
//STRIP001
//STRIP001             if( pNeuObj )
//STRIP001             {
//STRIP001              Point aP(pMark->GetPageView()->GetOffset());
//STRIP001              if (aP.X()!=0 || aP.Y()!=0) pNeuObj->NbcMove(Size(aP.X(),aP.Y()));
//STRIP001              SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001              pNeuPag->InsertObject(pNeuObj,CONTAINER_APPEND,&aReason);
//STRIP001
//STRIP001              // #i13033#
//STRIP001              aCloneList.AddPair(pObj, pNeuObj);
//STRIP001          }
//STRIP001             else
//STRIP001                 nCloneErrCnt++;
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  // #i13033#
//STRIP001  // New mechanism to re-create the connections of cloned connectors
//STRIP001  aCloneList.CopyConnections();
//STRIP001
//STRIP001  if(0L != nCloneErrCnt)
//STRIP001  {
//STRIP001 #ifdef DBG_UTIL
//STRIP001      ByteString aStr("SdrExchangeView::GetMarkedObjModel(): Fehler beim Clonen ");
//STRIP001
//STRIP001      if(nCloneErrCnt == 1)
//STRIP001      {
//STRIP001          aStr += "eines Zeichenobjekts.";
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aStr += "von ";
//STRIP001          aStr += ByteString::CreateFromInt32( nCloneErrCnt );
//STRIP001          aStr += " Zeichenobjekten.";
//STRIP001      }
//STRIP001
//STRIP001      aStr += " Objektverbindungen werden nicht mitkopiert.";
//STRIP001
//STRIP001      DBG_ERROR(aStr.GetBuffer());
//STRIP001 #endif
//STRIP001  }
//STRIP001  return pNeuMod;
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 BOOL SdrExchangeView::Cut( ULONG nFormat )
//STRIP001 {
//STRIP001     DBG_ERROR( "SdrExchangeView::Cut: Not supported anymore" );
//STRIP001     return FALSE;
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 void SdrExchangeView::CutMarked( ULONG nFormat )
//STRIP001 {
//STRIP001     DBG_ERROR( "SdrExchangeView::CutMarked: Not supported anymore" );
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 BOOL SdrExchangeView::Yank(ULONG nFormat)
//STRIP001 {
//STRIP001     DBG_ERROR( "SdrExchangeView::Yank: Not supported anymore" );
//STRIP001     return FALSE;
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 void SdrExchangeView::YankMarked(ULONG nFormat)
//STRIP001 {
//STRIP001     DBG_ERROR( "YankMarked: Not supported anymore" );
//STRIP001 }
//STRIP001
//STRIP001 // -----------------------------------------------------------------------------
//STRIP001
//STRIP001 BOOL SdrExchangeView::Paste(Window* pWin, ULONG nFormat)
//STRIP001 {
//STRIP001     DBG_ERROR( "SdrExchangeView::Paste: Not supported anymore" );
//STRIP001     return FALSE;
//STRIP001 }
}
