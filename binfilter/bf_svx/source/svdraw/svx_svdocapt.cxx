/*************************************************************************
 *
 *  $RCSfile: svx_svdocapt.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:27 $
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

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif

#ifndef _SVX_XLNWTIT_HXX //autogen
#include <xlnwtit.hxx>
#endif

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#include "svdocapt.hxx"
#include "xpool.hxx"
#include "xpoly.hxx"
#include "svdattrx.hxx"
#include "svdpool.hxx"
#include "svdxout.hxx"
#include "svdetc.hxx"
#include "svdtrans.hxx"
#include "svdtouch.hxx"
#include "svdio.hxx"
#include "svdhdl.hxx"
#include "svddrag.hxx"
#include "svdmodel.hxx"
#include "svdview.hxx"   // fuer RectSnap
#include "svdpagv.hxx"   // fuer GetOffset bei BegDrag()
#include "svdglob.hxx"   // StringCache
#include "svdstr.hrc"    // Objektname
#include "svdogrp.hxx"
#include "svdpage.hxx"

#ifndef _SVX_XFLHTIT_HXX
#include <xflhtit.hxx>
#endif

#ifndef _SVX_XFLCLIT_HXX
#include <xflclit.hxx>
#endif

#ifndef _SVX_XFLTRIT_HXX
#include <xfltrit.hxx>
#endif

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ enum EscDir {LKS,RTS,OBN,UNT};

/*N*/ class ImpCaptParams
/*N*/ {
/*N*/ public:
/*N*/   SdrCaptionType              eType;
/*N*/   long                        nAngle;
/*N*/   long                        nGap;
/*N*/   long                        nEscRel;
/*N*/   long                        nEscAbs;
/*N*/   long                        nLineLen;
/*N*/   SdrCaptionEscDir            eEscDir;
/*N*/   FASTBOOL                    bFitLineLen;
/*N*/   FASTBOOL                    bEscRel;
/*N*/   FASTBOOL                    bFixedAngle;
/*N*/
/*N*/ public:
/*N*/   ImpCaptParams()
/*N*/   {
/*N*/       eType      =SDRCAPT_TYPE3;
/*N*/       bFixedAngle=FALSE;
/*N*/       nAngle     =4500;
/*N*/       nGap       =0;
/*N*/       eEscDir    =SDRCAPT_ESCHORIZONTAL;
/*N*/       bEscRel    =TRUE;
/*N*/       nEscRel    =5000;
/*N*/       nEscAbs    =0;
/*N*/       nLineLen   =0;
/*N*/       bFitLineLen=TRUE;
/*N*/   }
/*N*/   void CalcEscPos(const Point& rTail, const Rectangle& rRect, Point& rPt, EscDir& rDir) const;
/*N*/ };

/*N*/ void ImpCaptParams::CalcEscPos(const Point& rTailPt, const Rectangle& rRect, Point& rPt, EscDir& rDir) const
/*N*/ {
/*N*/   Point aTl(rTailPt); // lokal kopieren wg. Performance
/*N*/   long nX,nY;
/*N*/   if (bEscRel) {
/*N*/       nX=rRect.Right()-rRect.Left();
/*N*/       nX=BigMulDiv(nX,nEscRel,10000);
/*N*/       nY=rRect.Bottom()-rRect.Top();
/*N*/       nY=BigMulDiv(nY,nEscRel,10000);
/*N*/   } else {
/*N*/       nX=nEscAbs;
/*N*/       nY=nEscAbs;
/*N*/   }
/*N*/   nX+=rRect.Left();
/*N*/   nY+=rRect.Top();
/*N*/   Point  aBestPt;
/*N*/   EscDir eBestDir=LKS;
/*N*/   FASTBOOL bTryH=eEscDir==SDRCAPT_ESCBESTFIT;
/*N*/   if (!bTryH) {
/*N*/       if (eType!=SDRCAPT_TYPE1) {
/*N*/           bTryH=eEscDir==SDRCAPT_ESCHORIZONTAL;
/*N*/       } else {
/*N*/           bTryH=eEscDir==SDRCAPT_ESCVERTICAL;
/*N*/       }
/*N*/   }
/*N*/   FASTBOOL bTryV=eEscDir==SDRCAPT_ESCBESTFIT;
/*N*/   if (!bTryV) {
/*N*/       if (eType!=SDRCAPT_TYPE1) {
/*N*/           bTryV=eEscDir==SDRCAPT_ESCVERTICAL;
/*N*/       } else {
/*N*/           bTryV=eEscDir==SDRCAPT_ESCHORIZONTAL;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bTryH) {
/*N*/       Point aLft(rRect.Left()-nGap,nY);
/*N*/       Point aRgt(rRect.Right()+nGap,nY);
/*N*/       FASTBOOL bLft=(aTl.X()-aLft.X()<aRgt.X()-aTl.X());
/*N*/       if (bLft) {
/*N*/           eBestDir=LKS;
/*N*/           aBestPt=aLft;
/*N*/       } else {
/*N*/           eBestDir=RTS;
/*N*/           aBestPt=aRgt;
/*N*/       }
/*N*/   }
/*N*/   if (bTryV) {
/*?*/       Point aTop(nX,rRect.Top()-nGap);
/*?*/       Point aBtm(nX,rRect.Bottom()+nGap);
/*?*/       FASTBOOL bTop=(aTl.Y()-aTop.Y()<aBtm.Y()-aTl.Y());
/*?*/       Point aBest2;
/*?*/       EscDir eBest2;
/*?*/       if (bTop) {
/*?*/           eBest2=OBN;
/*?*/           aBest2=aTop;
/*?*/       } else {
/*?*/           eBest2=UNT;
/*?*/           aBest2=aBtm;
/*?*/       }
/*?*/       FASTBOOL bTakeIt=eEscDir!=SDRCAPT_ESCBESTFIT;
/*?*/       if (!bTakeIt) {
/*?*/           BigInt aHorX(aBestPt.X()-aTl.X()); aHorX*=aHorX;
/*?*/           BigInt aHorY(aBestPt.Y()-aTl.Y()); aHorY*=aHorY;
/*?*/           BigInt aVerX(aBest2.X()-aTl.X());  aVerX*=aVerX;
/*?*/           BigInt aVerY(aBest2.Y()-aTl.Y());  aVerY*=aVerY;
/*?*/           if (eType!=SDRCAPT_TYPE1) {
/*?*/               bTakeIt=aVerX+aVerY<aHorX+aHorY;
/*?*/           } else {
/*?*/               bTakeIt=aVerX+aVerY>=aHorX+aHorY;
/*?*/           }
/*?*/       }
/*?*/       if (bTakeIt) {
/*?*/           aBestPt=aBest2;
/*?*/           eBestDir=eBest2;
/*?*/       }
/*N*/   }
/*N*/   rPt=aBestPt;
/*N*/   rDir=eBestDir;
/*N*/ }

/*N*/ TYPEINIT1(SdrCaptionObj,SdrRectObj);

/*N*/ SdrCaptionObj::SdrCaptionObj():
/*N*/   SdrRectObj(OBJ_TEXT),
/*N*/   aTailPoly(3),  // Default Groesse: 3 Punkte = 2 Linien
/*N*/   mbSpecialTextBoxShadow(FALSE)
/*N*/ {
/*N*/ }

/*?*/ SdrCaptionObj::SdrCaptionObj(const Rectangle& rRect):
/*?*/   SdrRectObj(OBJ_TEXT,rRect),
/*?*/   aTailPoly(3),  // Default Groesse: 3 Punkte = 2 Linien
/*?*/   mbSpecialTextBoxShadow(FALSE)
/*?*/ {
/*?*/ }

/*?*/ SdrCaptionObj::SdrCaptionObj(const Rectangle& rRect, const Point& rTail):
/*?*/   SdrRectObj(OBJ_TEXT,rRect),
/*?*/   aTailPoly(3),  // Default Groesse: 3 Punkte = 2 Linien
/*?*/   mbSpecialTextBoxShadow(FALSE)
/*?*/ {
/*?*/   aTailPoly[0]=rTail;
/*?*/ }

/*N*/ SdrCaptionObj::~SdrCaptionObj()
/*N*/ {
/*N*/ }

//STRIP001 FASTBOOL SdrCaptionObj::Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  // special shadow paint for calc
//STRIP001  if(mbSpecialTextBoxShadow)
//STRIP001  {
//STRIP001      const SfxItemSet& rSet = GetItemSet();
//STRIP001      sal_uInt32 nXDist = ((SdrShadowXDistItem&)(rSet.Get(SDRATTR_SHADOWXDIST))).GetValue();
//STRIP001      sal_uInt32 nYDist = ((SdrShadowYDistItem&)(rSet.Get(SDRATTR_SHADOWYDIST))).GetValue();
//STRIP001      const SdrShadowColorItem& rShadColItem = ((SdrShadowColorItem&)(rSet.Get(SDRATTR_SHADOWCOLOR)));
//STRIP001      Color aShadCol(rShadColItem.GetValue());
//STRIP001      sal_uInt16 nTransp = ((SdrShadowTransparenceItem&)(rSet.Get(SDRATTR_SHADOWTRANSPARENCE))).GetValue();
//STRIP001      XFillStyle eStyle = ((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001
//STRIP001      SfxItemSet aSet(rSet);
//STRIP001      // #99001# Hide lines for special calc shadow
//STRIP001      aSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001
//STRIP001      if(eStyle == XFILL_HATCH) // #41666#
//STRIP001      {
//STRIP001          XHatch aHatch = ((XFillHatchItem&)(rSet.Get(XATTR_FILLHATCH))).GetValue();
//STRIP001          aHatch.SetColor(aShadCol);
//STRIP001          aSet.Put(XFillHatchItem(String(),aHatch));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(eStyle != XFILL_NONE && eStyle != XFILL_SOLID)
//STRIP001          {
//STRIP001              // also fuer Gradient und Bitmap
//STRIP001              aSet.Put(XFillStyleItem(XFILL_SOLID));
//STRIP001          }
//STRIP001
//STRIP001          aSet.Put(XFillColorItem(String(),aShadCol));
//STRIP001          aSet.Put(XFillTransparenceItem(nTransp));
//STRIP001      }
//STRIP001
//STRIP001      rOut.SetFillAttr(aSet);
//STRIP001      // #99001# Hide lines for special calc shadow
//STRIP001      rOut.SetLineAttr(aSet);
//STRIP001
//STRIP001      sal_Int32 nEckRad(GetEckenradius());
//STRIP001      if(PaintNeedsXPoly(nEckRad))
//STRIP001      {
//STRIP001          XPolygon aX(GetXPoly());
//STRIP001          aX.Move(nXDist,nYDist);
//STRIP001          rOut.DrawXPolygon(aX);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          Rectangle aR(aRect);
//STRIP001          aR.Move(nXDist,nYDist);
//STRIP001          rOut.DrawRect(aR,USHORT(2*nEckRad),USHORT(2*nEckRad));
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // call parent for normal paint
//STRIP001  return SdrRectObj::Paint(rOut, rInfoRec);
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bRotateFreeAllowed=FALSE;
//STRIP001  rInfo.bRotate90Allowed  =FALSE;
//STRIP001  rInfo.bMirrorFreeAllowed=FALSE;
//STRIP001  rInfo.bMirror45Allowed  =FALSE;
//STRIP001  rInfo.bMirror90Allowed  =FALSE;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed     =FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001  rInfo.bCanConvToPath    =TRUE;
//STRIP001  rInfo.bCanConvToPoly    =TRUE;
//STRIP001  rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToContour = (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

/*N*/ UINT16 SdrCaptionObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return UINT16(OBJ_CAPTION);
/*N*/ }

/*N*/ void SdrCaptionObj::RecalcBoundRect()
/*N*/ {
/*N*/   aOutRect=GetSnapRect();
/*N*/   long nLineWdt=ImpGetLineWdt();
/*N*/   nLineWdt++; nLineWdt/=2;
/*N*/   long nLEndWdt=ImpGetLineEndAdd();
/*N*/   if (nLEndWdt>nLineWdt) nLineWdt=nLEndWdt;
/*N*/   if (nLineWdt!=0) {
/*N*/       aOutRect.Left  ()-=nLineWdt;
/*N*/       aOutRect.Top   ()-=nLineWdt;
/*N*/       aOutRect.Right ()+=nLineWdt;
/*N*/       aOutRect.Bottom()+=nLineWdt;
/*N*/   }
/*N*/   ImpAddShadowToBoundRect();
/*N*/   ImpAddTextToBoundRect();
/*N*/ }

//STRIP001 SdrObject* SdrCaptionObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
//STRIP001  FASTBOOL bHit=SdrRectObj::CheckHit(rPnt,nTol,pVisiLayer)!=NULL;
//STRIP001  if (!bHit) {
//STRIP001      INT32 nMyTol=nTol;
//STRIP001      INT32 nWdt = ((XLineWidthItem&)(GetItem(XATTR_LINEWIDTH))).GetValue();
//STRIP001      nWdt++;
//STRIP001      nWdt /= 2;
//STRIP001
//STRIP001      if (nWdt>nMyTol) nMyTol=nWdt; // Bei dicker Linie keine Toleranz noetig
//STRIP001      Rectangle aR(rPnt,rPnt);
//STRIP001      aR.Left()  -=nMyTol;
//STRIP001      aR.Right() +=nMyTol;
//STRIP001      aR.Top()   -=nMyTol;
//STRIP001      aR.Bottom()+=nMyTol;
//STRIP001      bHit=IsRectTouchesLine(aTailPoly,aR);
//STRIP001  }
//STRIP001  return bHit ? (SdrObject*)this : NULL;
//STRIP001 }

//STRIP001 void SdrCaptionObj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  SdrRectObj::operator=(rObj);
//STRIP001  aTailPoly=((SdrCaptionObj&)rObj).aTailPoly;
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulCAPTION);
//STRIP001
//STRIP001  String aName( GetName() );
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralCAPTION);
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  SdrRectObj::TakeXorPoly(rPoly,bDetail);
//STRIP001  rPoly.Insert(XPolygon(aTailPoly));
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

//STRIP001 USHORT SdrCaptionObj::GetHdlCount() const
//STRIP001 {
//STRIP001  USHORT nAnz1=SdrRectObj::GetHdlCount();
//STRIP001  USHORT nAnz2=aTailPoly.GetSize();
//STRIP001  // Derzeit ist nur das Draggen des Schwanzendes implementiert
//STRIP001  return nAnz1+1;
//STRIP001 }

//STRIP001 SdrHdl* SdrCaptionObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  USHORT nRectHdlAnz=SdrRectObj::GetHdlCount();
//STRIP001  if (nHdlNum<nRectHdlAnz) {
//STRIP001      return SdrRectObj::GetHdl(nHdlNum);
//STRIP001  } else {
//STRIP001      USHORT nPntNum=nHdlNum;
//STRIP001      nPntNum-=nRectHdlAnz;
//STRIP001      if (nPntNum<aTailPoly.GetSize()) {
//STRIP001          SdrHdl* pHdl=new SdrHdl(aTailPoly.GetPoint(nPntNum),HDL_POLY);
//STRIP001          pHdl->SetPolyNum(1);
//STRIP001          pHdl->SetPointNum(nPntNum);
//STRIP001          return pHdl;
//STRIP001      } else return NULL;
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001
//STRIP001  // #109992#
//STRIP001  // If this is a CaptionObj, set the flags bEndDragChangesAttributes
//STRIP001  // and bEndDragChangesGeoAndAttributes to create an undo action which
//STRIP001  // contains geo and attr changes. Joe seems to have added this as a fix
//STRIP001  // for a similar occurring problem.
//STRIP001  rDrag.SetEndDragChangesAttributes(TRUE);
//STRIP001  rDrag.SetEndDragChangesGeoAndAttributes(TRUE);
//STRIP001
//STRIP001  if (pHdl!=NULL && pHdl->GetPolyNum()==0) {
//STRIP001      return SdrRectObj::BegDrag(rDrag);
//STRIP001  } else {
//STRIP001      rDrag.SetOrtho8Possible(TRUE);
//STRIP001      if (pHdl==NULL) {
//STRIP001          if (bMovProt) return FALSE; // Position geschuetzt
//STRIP001          rDrag.SetNoSnap(TRUE); // Snap mache ich in diesem Fall selbst (RectSnap)
//STRIP001          rDrag.SetActionRect(aRect);
//STRIP001          Point aHit(rDrag.GetStart());
//STRIP001          if (rDrag.GetPageView()!=NULL) { // Hitposition bei versetzter PageView korregieren
//STRIP001              aHit-=rDrag.GetPageView()->GetOffset();
//STRIP001          }
//STRIP001          if (SdrRectObj::CheckHit(aHit,0,NULL)!=NULL) return TRUE;
//STRIP001          else return FALSE;
//STRIP001      } else {
//STRIP001          return (pHdl->GetPolyNum()==1) && (pHdl->GetPointNum()==0);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  if (pHdl!=NULL && pHdl->GetPolyNum()==0) {
//STRIP001      return SdrRectObj::MovDrag(rDrag);
//STRIP001  } else {
//STRIP001      SdrView* pView=rDrag.GetView();
//STRIP001      SdrPageView* pPV=rDrag.GetPageView();
//STRIP001      Rectangle aR(aRect);
//STRIP001      aR.Move(rDrag.GetDX(),rDrag.GetDY());
//STRIP001      if (pView!=NULL && pPV!=NULL && pView->IsSnapEnabled()) { // RectSnap
//STRIP001          long nDX=0,nDY=0;
//STRIP001          pView->SnapRect(aR,pPV,nDX,nDY);
//STRIP001          rDrag.Now().X()+=nDX;
//STRIP001          rDrag.Now().Y()+=nDY;
//STRIP001          aR.Move(nDX,nDY);
//STRIP001      }
//STRIP001      rDrag.SetActionRect(aR);
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  if (pHdl!=NULL && pHdl->GetPolyNum()==0) {
//STRIP001      FASTBOOL bRet=SdrRectObj::EndDrag(rDrag);
//STRIP001      ImpRecalcTail();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001      return bRet;
//STRIP001  } else {
//STRIP001      SendRepaintBroadcast();
//STRIP001      Point aDelt(rDrag.GetNow()-rDrag.GetStart());
//STRIP001      if (pHdl==NULL) { // Rect verschoben
//STRIP001          aRect.Move(aDelt.X(),aDelt.Y());
//STRIP001      } else {          // Schwanz verschoben
//STRIP001          aTailPoly[0]+=aDelt;
//STRIP001      }
//STRIP001      ImpRecalcTail();
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCaptionObj::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  if (pHdl!=NULL && pHdl->GetPolyNum()==0) {
//STRIP001      SdrRectObj::BrkDrag(rDrag);
//STRIP001  } else {
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrCaptionObj::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  if (bCreateComment) return String();
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  if (pHdl!=NULL && pHdl->GetPolyNum()==0) {
//STRIP001      return SdrRectObj::GetDragComment(rDrag,bUndoDragComment,FALSE);
//STRIP001  } else {
//STRIP001      XubString aStr;
//STRIP001      if (pHdl==NULL) {
//STRIP001          ImpTakeDescriptionStr(STR_DragCaptFram,aStr);
//STRIP001      } else {
//STRIP001          ImpTakeDescriptionStr(STR_DragCaptTail,aStr);
//STRIP001      }
//STRIP001      return aStr;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  FASTBOOL bRad=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  FASTBOOL bRectSiz=(pHdl!=NULL && pHdl->GetPolyNum()==0);
//STRIP001  if (bRad) {
//STRIP001      SdrRectObj::TakeDragPoly(rDrag,rXPP);
//STRIP001  } else {
//STRIP001      Point aDelt(rDrag.GetNow()-rDrag.GetStart());
//STRIP001      Polygon aTmpPoly(aTailPoly);
//STRIP001      Rectangle aTmpRect;
//STRIP001      if (bRectSiz) aTmpRect=ImpDragCalcRect(rDrag);
//STRIP001      else aTmpRect=aRect;
//STRIP001      ImpCaptParams aPara;
//STRIP001      ImpGetCaptParams(aPara);
//STRIP001      if (!bRectSiz) {
//STRIP001          if (pHdl==NULL) { // Rect verschieben
//STRIP001              aTmpRect.Move(aDelt.X(),aDelt.Y());
//STRIP001          } else {          // Schwanz verschieben
//STRIP001              aTmpPoly[0]+=aDelt;
//STRIP001          }
//STRIP001      }
//STRIP001      ImpCalcTail(aPara,aTmpPoly,aTmpRect);
//STRIP001      rXPP.Insert(ImpCalcXPoly(aTmpRect,GetEckenradius()));
//STRIP001      rXPP.Insert(XPolygon(aTmpPoly));
//STRIP001  }
//STRIP001 }

/*N*/ void SdrCaptionObj::ImpGetCaptParams(ImpCaptParams& rPara) const
/*N*/ {
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   rPara.eType      =((SdrCaptionTypeItem&)      (rSet.Get(SDRATTR_CAPTIONTYPE      ))).GetValue();
/*N*/   rPara.bFixedAngle=((SdrCaptionFixedAngleItem&)(rSet.Get(SDRATTR_CAPTIONANGLE     ))).GetValue();
/*N*/   rPara.nAngle     =((SdrCaptionAngleItem&)     (rSet.Get(SDRATTR_CAPTIONFIXEDANGLE))).GetValue();
/*N*/   rPara.nGap       =((SdrCaptionGapItem&)       (rSet.Get(SDRATTR_CAPTIONGAP       ))).GetValue();
/*N*/   rPara.eEscDir    =((SdrCaptionEscDirItem&)    (rSet.Get(SDRATTR_CAPTIONESCDIR    ))).GetValue();
/*N*/   rPara.bEscRel    =((SdrCaptionEscIsRelItem&)  (rSet.Get(SDRATTR_CAPTIONESCISREL  ))).GetValue();
/*N*/   rPara.nEscRel    =((SdrCaptionEscRelItem&)    (rSet.Get(SDRATTR_CAPTIONESCREL    ))).GetValue();
/*N*/   rPara.nEscAbs    =((SdrCaptionEscAbsItem&)    (rSet.Get(SDRATTR_CAPTIONESCABS    ))).GetValue();
/*N*/   rPara.nLineLen   =((SdrCaptionLineLenItem&)   (rSet.Get(SDRATTR_CAPTIONLINELEN   ))).GetValue();
/*N*/   rPara.bFitLineLen=((SdrCaptionFitLineLenItem&)(rSet.Get(SDRATTR_CAPTIONFITLINELEN))).GetValue();
/*N*/ }

/*N*/ void SdrCaptionObj::ImpRecalcTail()
/*N*/ {
/*N*/   ImpCaptParams aPara;
/*N*/   ImpGetCaptParams(aPara);
/*N*/   ImpCalcTail(aPara,aTailPoly,aRect);
/*N*/   SetRectsDirty();
/*N*/   SetXPolyDirty();
/*N*/ }

//STRIP001 void SdrCaptionObj::ImpCalcTail1(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const
//STRIP001 { // Gap/EscDir/EscPos
//STRIP001  Polygon aPol(2);
//STRIP001  Point aTl(rPoly[0]);
//STRIP001  aPol[0]=aTl;
//STRIP001  aPol[1]=aTl;
//STRIP001  EscDir eEscDir;
//STRIP001  Point aEscPos;
//STRIP001  rPara.CalcEscPos(aTl,rRect,aEscPos,eEscDir);
//STRIP001  if (eEscDir==LKS || eEscDir==RTS) {
//STRIP001      long dx=aTl.X()-aEscPos.X();
//STRIP001      rRect.Move(dx,0);
//STRIP001      aPol[1].Y()=aEscPos.Y();
//STRIP001  } else {
//STRIP001      long dy=aTl.Y()-aEscPos.Y();
//STRIP001      rRect.Move(0,dy);
//STRIP001      aPol[1].X()=aEscPos.X();
//STRIP001  }
//STRIP001  rPoly=aPol;
//STRIP001 }

//STRIP001 void SdrCaptionObj::ImpCalcTail2(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const
//STRIP001 { // Gap/EscDir/EscPos/Angle
//STRIP001  Polygon aPol(2);
//STRIP001  Point aTl(rPoly[0]);
//STRIP001  aPol[0]=aTl;
//STRIP001
//STRIP001  EscDir eEscDir;
//STRIP001  Point aEscPos;
//STRIP001  rPara.CalcEscPos(aTl,rRect,aEscPos,eEscDir);
//STRIP001  aPol[1]=aEscPos;
//STRIP001
//STRIP001  if (!rPara.bFixedAngle) {
//STRIP001      // fehlende Implementation
//STRIP001  }
//STRIP001  rPoly=aPol;
//STRIP001 }

/*N*/ void SdrCaptionObj::ImpCalcTail3(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const
/*N*/ { // Gap/EscDir/EscPos/Angle/LineLen
/*N*/   Polygon aPol(3);
/*N*/   Point aTl(rPoly[0]);
/*N*/   aPol[0]=aTl;
/*N*/
/*N*/   EscDir eEscDir;
/*N*/   Point aEscPos;
/*N*/   rPara.CalcEscPos(aTl,rRect,aEscPos,eEscDir);
/*N*/   aPol[1]=aEscPos;
/*N*/   aPol[2]=aEscPos;
/*N*/
/*N*/   if (eEscDir==LKS || eEscDir==RTS) {
/*N*/       if (rPara.bFitLineLen) {
/*N*/           aPol[1].X()=(aTl.X()+aEscPos.X())/2;
/*N*/       } else {
/*N*/           if (eEscDir==LKS) aPol[1].X()-=rPara.nLineLen;
/*N*/           else aPol[1].X()+=rPara.nLineLen;
/*N*/       }
/*N*/   } else {
/*N*/       if (rPara.bFitLineLen) {
/*N*/           aPol[1].Y()=(aTl.Y()+aEscPos.Y())/2;
/*N*/       } else {
/*N*/           if (eEscDir==OBN) aPol[1].Y()-=rPara.nLineLen;
/*N*/           else aPol[1].Y()+=rPara.nLineLen;
/*N*/       }
/*N*/   }
/*N*/   if (!rPara.bFixedAngle) {
/*N*/       // fehlende Implementation
/*N*/   }
/*N*/   rPoly=aPol;
/*N*/ }

//STRIP001 void SdrCaptionObj::ImpCalcTail4(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const
//STRIP001 {
//STRIP001  ImpCalcTail3(rPara,rPoly,rRect);
//STRIP001 }

/*N*/ void SdrCaptionObj::ImpCalcTail(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const
/*N*/ {
/*N*/   switch (rPara.eType) {
/*?*/       case SDRCAPT_TYPE1: DBG_ASSERT(0, "STRIP"); break;//STRIP001 ImpCalcTail1(rPara,rPoly,rRect); break;
/*?*/       case SDRCAPT_TYPE2: DBG_ASSERT(0, "STRIP"); break;//STRIP001 ImpCalcTail2(rPara,rPoly,rRect); break;
/*N*/       case SDRCAPT_TYPE3: ImpCalcTail3(rPara,rPoly,rRect); break;
/*?*/       case SDRCAPT_TYPE4: DBG_ASSERT(0, "STRIP"); break;//STRIP001 ImpCalcTail4(rPara,rPoly,rRect); break;
/*N*/   }
/*N*/ }

//STRIP001 FASTBOOL SdrCaptionObj::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  if (aRect.IsEmpty()) return FALSE; // Create z.Zt. nur mit vorgegebenen Rect
//STRIP001
//STRIP001  ImpCaptParams aPara;
//STRIP001  ImpGetCaptParams(aPara);
//STRIP001  aRect.SetPos(rStat.GetNow());
//STRIP001  aTailPoly[0]=rStat.GetStart();
//STRIP001  ImpCalcTail(aPara,aTailPoly,aRect);
//STRIP001  rStat.SetActionRect(aRect);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::MovCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  ImpCaptParams aPara;
//STRIP001  ImpGetCaptParams(aPara);
//STRIP001  aRect.SetPos(rStat.GetNow());
//STRIP001  ImpCalcTail(aPara,aTailPoly,aRect);
//STRIP001  rStat.SetActionRect(aRect);
//STRIP001  bBoundRectDirty=TRUE;
//STRIP001  bSnapRectDirty=TRUE;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  ImpCaptParams aPara;
//STRIP001  ImpGetCaptParams(aPara);
//STRIP001  aRect.SetPos(rStat.GetNow());
//STRIP001  ImpCalcTail(aPara,aTailPoly,aRect);
//STRIP001  SetRectsDirty();
//STRIP001  return (eCmd==SDRCREATE_FORCEEND || rStat.GetPointAnz()>=2);
//STRIP001 }

//STRIP001 FASTBOOL SdrCaptionObj::BckCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrCaptionObj::BrkCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrCaptionObj::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  rXPP.Insert(XPolygon(aRect));
//STRIP001  rXPP.Insert(XPolygon(aTailPoly));
//STRIP001 }

//STRIP001 Pointer SdrCaptionObj::GetCreatePointer() const
//STRIP001 {
//STRIP001  return Pointer(POINTER_DRAW_CAPTION);
//STRIP001 }

/*N*/ void SdrCaptionObj::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   SdrRectObj::NbcMove(rSiz);
/*N*/   MovePoly(aTailPoly,rSiz);
/*N*/ }

/*N*/ void SdrCaptionObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrRectObj::NbcResize(rRef,xFact,yFact);
/*N*/   ResizePoly(aTailPoly,rRef,xFact,yFact);
/*N*/   ImpRecalcTail();
/*N*/ }

//STRIP001 void SdrCaptionObj::NbcSetRelativePos(const Point& rPnt)
//STRIP001 {
//STRIP001  Point aRelPos0(aTailPoly.GetPoint(0)-aAnchor);
//STRIP001  Size aSiz(rPnt.X()-aRelPos0.X(),rPnt.Y()-aRelPos0.Y());
//STRIP001  NbcMove(aSiz); // Der ruft auch das SetRectsDirty()
//STRIP001 }

//STRIP001 Point SdrCaptionObj::GetRelativePos() const
//STRIP001 {
//STRIP001  return aTailPoly.GetPoint(0)-aAnchor;
//STRIP001 }

/*N*/ void SdrCaptionObj::NbcSetAnchorPos(const Point& rPnt)
/*N*/ {
/*N*/   SdrRectObj::NbcSetAnchorPos(rPnt);
/*N*/   // !!!!! fehlende Impl.
/*N*/ }

/*N*/ const Point& SdrCaptionObj::GetAnchorPos() const
/*N*/ {
/*N*/   // !!!!! fehlende Impl.
/*N*/   return SdrRectObj::GetAnchorPos();
/*N*/ }

/*N*/ void SdrCaptionObj::RecalcSnapRect()
/*N*/ {
/*N*/   SdrRectObj::RecalcSnapRect();
/*N*/   maSnapRect.Union(aTailPoly.GetBoundRect());
/*N*/   // !!!!! fehlende Impl.
/*N*/ }

/*N*/ const Rectangle& SdrCaptionObj::GetSnapRect() const
/*N*/ {
/*N*/   return SdrRectObj::GetSnapRect();
/*N*/ }

/*N*/ void SdrCaptionObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   // #109587#
/*N*/   //
/*N*/   // The new SnapRect contains the tail BoundRect, see
/*N*/   // RecalcSnapRect() above. Thus, the new to-be-setted
/*N*/   // SnapRect needs to be 'cleared' from that tail offsets
/*N*/   // before setting it as new SnapRect at the SdrRectObj.
/*N*/   //
/*N*/   // As base for 'clearing' the old text rect is taken from aRect
/*N*/   // using GetLogicRect(), see below. Second the outer tail point
/*N*/   // wich expanded that rect. Since the other end of the
/*N*/   // connection polygon always resides at one edge of the text rect
/*N*/   // this is sufficient information.
/*N*/   Rectangle aNewSnapRect(rRect);
/*N*/   const Rectangle aOriginalTextRect(GetLogicRect());
/*N*/   const Point aTailPoint = GetTailPos();
/*N*/
/*N*/   // #109992#
/*N*/   // This compares only make sense when aOriginalTextRect and the
/*N*/   // aTailPoint contain useful data. Thus, test it before usage.
/*N*/   if(!aOriginalTextRect.IsEmpty())
/*N*/   {
/*N*/       if(aTailPoint.X() < aOriginalTextRect.Left())
/*N*/       {
/*N*/           const sal_Int32 nDist = aOriginalTextRect.Left() - aTailPoint.X();
/*N*/           aNewSnapRect.Left() = aNewSnapRect.Left() + nDist;
/*N*/       }
/*N*/       else if(aTailPoint.X() > aOriginalTextRect.Right())
/*N*/       {
/*N*/           const sal_Int32 nDist = aTailPoint.X() - aOriginalTextRect.Right();
/*N*/           aNewSnapRect.Right() = aNewSnapRect.Right() - nDist;
/*N*/       }
/*N*/
/*N*/       if(aTailPoint.Y() < aOriginalTextRect.Top())
/*N*/       {
/*N*/           const sal_Int32 nDist = aOriginalTextRect.Top() - aTailPoint.Y();
/*N*/           aNewSnapRect.Top() = aNewSnapRect.Top() + nDist;
/*N*/       }
/*N*/       else if(aTailPoint.Y() > aOriginalTextRect.Bottom())
/*N*/       {
/*N*/           const sal_Int32 nDist = aTailPoint.Y() - aOriginalTextRect.Bottom();
/*N*/           aNewSnapRect.Bottom() = aNewSnapRect.Bottom() - nDist;
/*N*/       }
/*N*/
/*N*/       // make sure rectangle is correctly defined
/*N*/       ImpJustifyRect(aNewSnapRect);
/*N*/
/*N*/       // #86616#
/*N*/       SdrRectObj::NbcSetSnapRect(aNewSnapRect);
/*N*/   }
/*N*/ }

//STRIP001 const Rectangle& SdrCaptionObj::GetLogicRect() const
//STRIP001 {
//STRIP001  return aRect;
//STRIP001 }

//STRIP001 void SdrCaptionObj::NbcSetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  SdrRectObj::NbcSetLogicRect(rRect);
//STRIP001  ImpRecalcTail();
//STRIP001 }

/*N*/ const Point& SdrCaptionObj::GetTailPos() const
/*N*/ {
/*N*/   return aTailPoly[0];
/*N*/ }

/*N*/ void SdrCaptionObj::SetTailPos(const Point& rPos)
/*N*/ {
/*N*/   if (aTailPoly.GetSize()==0 || aTailPoly[0]!=rPos) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcSetTailPos(rPos);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

/*N*/ void SdrCaptionObj::NbcSetTailPos(const Point& rPos)
/*N*/ {
/*N*/   aTailPoly[0]=rPos;
/*N*/   ImpRecalcTail();
/*N*/ }

//STRIP001 USHORT SdrCaptionObj::GetSnapPointCount() const
//STRIP001 {
//STRIP001  // !!!!! fehlende Impl.
//STRIP001  return 0;
//STRIP001 }

//STRIP001 Point SdrCaptionObj::GetSnapPoint(USHORT i) const
//STRIP001 {
//STRIP001  // !!!!! fehlende Impl.
//STRIP001  return Point(0,0);
//STRIP001 }

/*N*/ void SdrCaptionObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrRectObj::SetModel(pNewModel);
/*N*/   ImpRecalcTail();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ SfxItemSet* SdrCaptionObj::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // include ALL items, 2D and 3D
/*N*/   return new SfxItemSet(rPool,
/*N*/       // ranges from SdrAttrObj
/*N*/       SDRATTR_START, SDRATTRSET_SHADOW,
/*N*/       SDRATTRSET_OUTLINER, SDRATTRSET_MISC,
/*N*/       SDRATTR_TEXTDIRECTION, SDRATTR_TEXTDIRECTION,
/*N*/
/*N*/       // caption attributes
/*N*/       SDRATTR_CAPTION_FIRST, SDRATTRSET_CAPTION,
/*N*/
/*N*/       // outliner and end
/*N*/       EE_ITEMS_START, EE_ITEMS_END,
/*N*/       0, 0);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access
/*N*/ void SdrCaptionObj::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/   // local changes
/*N*/   ImpRecalcTail();
/*N*/
/*N*/   // call parent
/*N*/   SdrRectObj::ItemSetChanged(rSet);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCaptionObj::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   SdrRectObj::NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/   ImpRecalcTail();
/*N*/ }

//STRIP001 void SdrCaptionObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
//STRIP001 {
//STRIP001  SdrRectObj::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
//STRIP001  ImpRecalcTail();
//STRIP001 }

//STRIP001 SdrObjGeoData* SdrCaptionObj::NewGeoData() const
//STRIP001 {
//STRIP001  return new SdrCaptObjGeoData;
//STRIP001 }

//STRIP001 void SdrCaptionObj::SaveGeoData(SdrObjGeoData& rGeo) const
//STRIP001 {
//STRIP001  SdrRectObj::SaveGeoData(rGeo);
//STRIP001  SdrCaptObjGeoData& rCGeo=(SdrCaptObjGeoData&)rGeo;
//STRIP001  rCGeo.aTailPoly=aTailPoly;
//STRIP001 }

//STRIP001 void SdrCaptionObj::RestGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  SdrRectObj::RestGeoData(rGeo);
//STRIP001  SdrCaptObjGeoData& rCGeo=(SdrCaptObjGeoData&)rGeo;
//STRIP001  aTailPoly=rCGeo.aTailPoly;
//STRIP001 }

//STRIP001 SdrObject* SdrCaptionObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 { // #42334# - Convert implementiert
//STRIP001  SdrObject* pRect=SdrRectObj::DoConvertToPolyObj(bBezier);
//STRIP001  SdrObject* pTail=ImpConvertMakeObj(XPolyPolygon(XPolygon(aTailPoly)),FALSE,bBezier);
//STRIP001  SdrObject* pRet=(pTail!=NULL) ? pTail : pRect;
//STRIP001  if (pTail!=NULL && pRect!=NULL) {
//STRIP001      FASTBOOL bInsRect=TRUE;
//STRIP001      FASTBOOL bInsTail=TRUE;
//STRIP001      SdrObjList* pOL=pTail->GetSubList();
//STRIP001      if (pOL!=NULL) { pRet=pRect; bInsTail=FALSE; }
//STRIP001      if (pOL==NULL) pOL=pRect->GetSubList();
//STRIP001      if (pOL!=NULL) { pRet=pRect; bInsRect=FALSE; }
//STRIP001      if (pOL==NULL) {
//STRIP001          SdrObjGroup* pGrp=new SdrObjGroup;
//STRIP001          pOL=pGrp->GetSubList();
//STRIP001          pRet=pGrp;
//STRIP001      }
//STRIP001      if (bInsRect) pOL->NbcInsertObject(pRect);
//STRIP001      if (bInsTail) pOL->NbcInsertObject(pTail,0);
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*?*/ void SdrCaptionObj::PreSave()
/*?*/ {
/*?*/   // call parent
/*?*/   SdrRectObj::PreSave();
/*?*/
/*?*/   // prepare SetItems for storage
/*?*/   const SfxItemSet& rSet = GetUnmergedItemSet();
/*?*/   const SfxItemSet* pParent = GetStyleSheet() ? &GetStyleSheet()->GetItemSet() : 0L;
/*?*/   SdrCaptionSetItem aCaptAttr(rSet.GetPool());
/*?*/   aCaptAttr.GetItemSet().Put(rSet);
/*?*/   aCaptAttr.GetItemSet().SetParent(pParent);
/*?*/   mpObjectItemSet->Put(aCaptAttr);
/*?*/ }

/*?*/ void SdrCaptionObj::PostSave()
/*?*/ {
/*?*/   // call parent
/*?*/   SdrRectObj::PostSave();
/*?*/
/*?*/   // remove SetItems from local itemset
/*?*/   mpObjectItemSet->ClearItem(SDRATTRSET_CAPTION);
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*?*/ void SdrCaptionObj::WriteData(SvStream& rOut) const
/*?*/ {
/*?*/   SdrRectObj::WriteData(rOut);
/*?*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/   aCompat.SetID("SdrCaptionObj");
/*?*/ #endif
/*?*/
/*?*/   rOut << aTailPoly;
/*?*/   SfxItemPool* pPool = GetItemPool();
/*?*/
/*?*/   if(pPool)
/*?*/   {
/*?*/       const SfxItemSet& rSet = GetUnmergedItemSet();
/*?*/
/*?*/       pPool->StoreSurrogate(rOut, &rSet.Get(SDRATTRSET_CAPTION));
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       rOut << UINT16(SFX_ITEMS_NULL);
/*?*/   }
/*?*/ }

/*N*/ void SdrCaptionObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if(rIn.GetError())
/*N*/       return;
/*N*/
/*N*/   SdrRectObj::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrCaptionObj");
/*N*/ #endif
/*N*/
/*N*/   rIn >> aTailPoly;
/*N*/
/*N*/   if(rHead.GetVersion() < 11) { sal_uInt16 nWhichDum; rIn >> nWhichDum; } // ab V11 keine WhichId mehr
/*N*/
/*N*/   SfxItemPool* pPool = GetItemPool();
/*N*/
/*N*/   if(pPool)
/*N*/   {
/*N*/       sal_uInt16 nSetID = SDRATTRSET_CAPTION;
/*N*/       const SdrCaptionSetItem* pCaptAttr = (const SdrCaptionSetItem*)pPool->LoadSurrogate(rIn, nSetID, 0);
/*N*/       if(pCaptAttr)
/*N*/           SetItemSet(pCaptAttr->GetItemSet());
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       sal_uInt16 nSuroDum;
/*N*/       rIn >> nSuroDum;
/*N*/   }
/*N*/ }

