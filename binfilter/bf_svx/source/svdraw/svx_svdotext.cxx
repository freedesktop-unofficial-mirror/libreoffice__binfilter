/*************************************************************************
 *
 *  $RCSfile: svx_svdotext.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:28:06 $
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

// auto strip #include "svdotext.hxx"
#include "svditext.hxx"
// auto strip #include "svdpagv.hxx"  // fuer Abfrage im Paint, ob das
#include "svdview.hxx"  // Objekt gerade editiert wird
// auto strip #include "svdpage.hxx"  // und fuer AnimationHandler (Laufschrift)
// auto strip #include "svdxout.hxx"
#include "svdtouch.hxx"
#include "svdio.hxx"
#include "svdetc.hxx"
#include "svdoutl.hxx"
// auto strip #include "svdscrol.hxx"  // fuer Laufschrift
// auto strip #include "svdmodel.hxx"  // OutlinerDefaults
// auto strip #include "svdglob.hxx"  // Stringcache
#include "svdstr.hrc"   // Objektname
#include "svdtxhdl.hxx"  // DrawTextToPath
#include "writingmodeitem.hxx"

// auto strip #ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
// auto strip #include <svtools/colorcfg.hxx>
// auto strip #endif

// auto strip #ifndef _EEITEM_HXX //autogen
// auto strip #include <eeitem.hxx>
// auto strip #endif

#ifndef _EDITSTAT_HXX //autogen
#include <editstat.hxx>
#endif

#ifndef _OUTLOBJ_HXX //autogen
#include <outlobj.hxx>
#endif

#ifndef _EDITOBJ_HXX //autogen
#include <editobj.hxx>
#endif

// auto strip #ifndef _OUTLINER_HXX //autogen
// auto strip #include "outliner.hxx"
// auto strip #endif

#ifndef _SVX_FHGTITEM_HXX //autogen
#include "fhgtitem.hxx"
#endif

#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif

#ifndef _SVX_ADJITEM_HXX //autogen
#include "adjitem.hxx"
#endif

// auto strip #ifndef _PSTM_HXX
// auto strip #include <tools/pstm.hxx>
// auto strip #endif

#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif

#include "flditem.hxx"

// auto strip #ifndef _SVX_XFTOUIT_HXX
// auto strip #include "xftouit.hxx"
// auto strip #endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>     // FRound
#endif

#ifndef _SVX_XFLGRIT_HXX
#include "xflgrit.hxx"
#endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

namespace binfilter {

// #104018# replace macros above with type-safe methods
inline double ImplTwipsToMM(double fVal) { return (fVal * (127.0 / 72.0)); }
inline double ImplMMToTwips(double fVal) { return (fVal * (72.0 / 127.0)); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@@ @@@@@ @@   @@ @@@@@@  @@@@  @@@@@  @@@@@@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@     @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@@@    @@@     @@   @@  @@ @@@@@      @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@ @@  @@
//    @@   @@@@@ @@   @@   @@    @@@@  @@@@@   @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrTextObj,SdrAttrObj);

/*N*/ SdrTextObj::SdrTextObj():
/*N*/   eTextKind(OBJ_TEXT),
/*N*/   pOutlinerParaObject(NULL),
/*N*/   pEdtOutl(NULL),
/*N*/   pFormTextBoundRect(NULL)
/*N*/ {
/*N*/   bTextSizeDirty=FALSE;
/*N*/   bPortionInfoChecked=FALSE;
/*N*/   bTextFrame=FALSE;
/*N*/   bNoShear=FALSE;
/*N*/   bNoRotate=FALSE;
/*N*/   bNoMirror=FALSE;
/*N*/   bDisableAutoWidthOnDragging=FALSE;
/*N*/
/*N*/   // #101684#
/*N*/   mbInEditMode = FALSE;
/*N*/
/*N*/   // #108784#
/*N*/   maTextEditOffset = Point(0, 0);
/*N*/ }

/*N*/ SdrTextObj::SdrTextObj(const Rectangle& rNewRect):
/*N*/   aRect(rNewRect),
/*N*/   eTextKind(OBJ_TEXT),
/*N*/   pOutlinerParaObject(NULL),
/*N*/   pEdtOutl(NULL),
/*N*/   pFormTextBoundRect(NULL)
/*N*/ {
/*N*/   bTextSizeDirty=FALSE;
/*N*/   bPortionInfoChecked=FALSE;
/*N*/   bTextFrame=FALSE;
/*N*/   bNoShear=FALSE;
/*N*/   bNoRotate=FALSE;
/*N*/   bNoMirror=FALSE;
/*N*/   bDisableAutoWidthOnDragging=FALSE;
/*N*/   ImpJustifyRect(aRect);
/*N*/
/*N*/   // #101684#
/*N*/   mbInEditMode = FALSE;
/*N*/
/*N*/   // #108784#
/*N*/   maTextEditOffset = Point(0, 0);
/*N*/ }

/*N*/ SdrTextObj::SdrTextObj(SdrObjKind eNewTextKind):
/*N*/   eTextKind(eNewTextKind),
/*N*/   pOutlinerParaObject(NULL),
/*N*/   pEdtOutl(NULL),
/*N*/   pFormTextBoundRect(NULL)
/*N*/ {
/*N*/   bTextSizeDirty=FALSE;
/*N*/   bTextFrame=TRUE;
/*N*/   bNoShear=TRUE;
/*N*/   bNoRotate=FALSE;
/*N*/   bNoMirror=TRUE;
/*N*/   bPortionInfoChecked=FALSE;
/*N*/   bDisableAutoWidthOnDragging=FALSE;
/*N*/
/*N*/   // #101684#
/*N*/   mbInEditMode = FALSE;
/*N*/
/*N*/   // #108784#
/*N*/   maTextEditOffset = Point(0, 0);
/*N*/ }

/*N*/ SdrTextObj::SdrTextObj(SdrObjKind eNewTextKind, const Rectangle& rNewRect):
/*N*/   aRect(rNewRect),
/*N*/   eTextKind(eNewTextKind),
/*N*/   pOutlinerParaObject(NULL),
/*N*/   pEdtOutl(NULL),
/*N*/   pFormTextBoundRect(NULL)
/*N*/ {
/*N*/   bTextSizeDirty=FALSE;
/*N*/   bTextFrame=TRUE;
/*N*/   bNoShear=TRUE;
/*N*/   bNoRotate=FALSE;
/*N*/   bNoMirror=TRUE;
/*N*/   bPortionInfoChecked=FALSE;
/*N*/   bDisableAutoWidthOnDragging=FALSE;
/*N*/   ImpJustifyRect(aRect);
/*N*/
/*N*/   // #101684#
/*N*/   mbInEditMode = FALSE;
/*N*/
/*N*/   // #108784#
/*N*/   maTextEditOffset = Point(0, 0);
/*N*/ }

/*?*/ SdrTextObj::SdrTextObj(SdrObjKind eNewTextKind, const Rectangle& rNewRect, SvStream& rInput, USHORT eFormat):
/*?*/   aRect(rNewRect),
/*?*/   eTextKind(eNewTextKind),
/*?*/   pOutlinerParaObject(NULL),
/*?*/   pEdtOutl(NULL),
/*?*/   pFormTextBoundRect(NULL)
/*?*/ {
/*?*/   bTextSizeDirty=FALSE;
/*?*/   bTextFrame=TRUE;
/*?*/   bNoShear=TRUE;
/*?*/   bNoRotate=FALSE;
/*?*/   bNoMirror=TRUE;
/*?*/   bPortionInfoChecked=FALSE;
/*?*/   bDisableAutoWidthOnDragging=FALSE;
/*?*/   ImpJustifyRect(aRect);
/*?*/
/*?*/   NbcSetText(rInput,eFormat);
/*?*/
/*?*/   // #101684#
/*?*/   mbInEditMode = FALSE;
/*?*/
/*?*/   // #108784#
/*?*/   maTextEditOffset = Point(0, 0);
/*?*/ }

/*N*/ SdrTextObj::~SdrTextObj()
/*N*/ {
/*N*/   if( pModel )
/*N*/   {
/*N*/       SdrOutliner& rOutl = pModel->GetHitTestOutliner();
/*N*/       if( rOutl.GetTextObj() == this )
/*N*/           rOutl.SetTextObj( NULL );
/*N*/   }
/*N*/
/*N*/   if (pOutlinerParaObject!=NULL) {
/*N*/       delete pOutlinerParaObject;
/*N*/   }
/*N*/   if (pFormTextBoundRect!=NULL) {
/*N*/       delete pFormTextBoundRect;
/*N*/   }
/*N*/   ImpLinkAbmeldung();
/*N*/ }

//STRIP001 void SdrTextObj::FitFrameToTextSize()
//STRIP001 {
//STRIP001  DBG_ASSERT(pModel!=NULL,"SdrTextObj::FitFrameToTextSize(): pModel=NULL!")
//STRIP001  ImpJustifyRect(aRect);
//STRIP001  if (pOutlinerParaObject!=NULL && pModel!=NULL) {
//STRIP001      SdrOutliner& rOutliner=ImpGetDrawOutliner();
//STRIP001      rOutliner.SetPaperSize(Size(aRect.Right()-aRect.Left(),aRect.Bottom()-aRect.Top()));
//STRIP001      rOutliner.SetUpdateMode(TRUE);
//STRIP001      rOutliner.SetText(*pOutlinerParaObject);
//STRIP001      Rectangle aTextRect;
//STRIP001      Size aNewSize(rOutliner.CalcTextSize());
//STRIP001      rOutliner.Clear();
//STRIP001      aNewSize.Width()++; // wegen evtl. Rundungsfehler
//STRIP001      aNewSize.Width()+=GetTextLeftDistance()+GetTextRightDistance();
//STRIP001      aNewSize.Height()+=GetTextUpperDistance()+GetTextLowerDistance();
//STRIP001      Rectangle aNewRect(aRect);
//STRIP001      aNewRect.SetSize(aNewSize);
//STRIP001      ImpJustifyRect(aNewRect);
//STRIP001      if (aNewRect!=aRect) {
//STRIP001          SetLogicRect(aNewRect);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*?*/ void SdrTextObj::NbcSetText(const XubString& rStr)
/*?*/ {
/*?*/   SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*?*/   rOutliner.SetStyleSheet( 0, GetStyleSheet());
/*?*/   OutputDevice* pRef1=rOutliner.GetRefDevice();
/*?*/   rOutliner.SetUpdateMode(TRUE);
/*?*/   rOutliner.SetText(rStr,rOutliner.GetParagraph( 0 ));
/*?*/   OutlinerParaObject* pNewText=rOutliner.CreateParaObject();
/*?*/   Size aSiz(rOutliner.CalcTextSize());
/*?*/   OutputDevice* pRef2=rOutliner.GetRefDevice();
/*?*/   rOutliner.Clear();
/*?*/   NbcSetOutlinerParaObject(pNewText);
/*?*/   aTextSize=aSiz;
/*?*/   bTextSizeDirty=FALSE;
/*?*/ }

//STRIP001 void SdrTextObj::SetText(const XubString& rStr)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcSetText(rStr);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (GetBoundRect()!=aBoundRect0) {
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

/*?*/ void SdrTextObj::NbcSetText(SvStream& rInput, USHORT eFormat)
/*?*/ {
/*?*/   SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*?*/   rOutliner.SetStyleSheet( 0, GetStyleSheet());
/*?*/   rOutliner.Read(rInput,eFormat);
/*?*/   OutlinerParaObject* pNewText=rOutliner.CreateParaObject();
/*?*/   rOutliner.SetUpdateMode(TRUE);
/*?*/   Size aSiz(rOutliner.CalcTextSize());
/*?*/   rOutliner.Clear();
/*?*/   NbcSetOutlinerParaObject(pNewText);
/*?*/   aTextSize=aSiz;
/*?*/   bTextSizeDirty=FALSE;
/*?*/ }

//STRIP001 void SdrTextObj::SetText(SvStream& rInput, USHORT eFormat)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcSetText(rInput,eFormat);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (GetBoundRect()!=aBoundRect0) {
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

/*N*/ const Size& SdrTextObj::GetTextSize() const
/*N*/ {
/*N*/   if (bTextSizeDirty) {
/*N*/       Size aSiz;
/*N*/       if (pOutlinerParaObject!=NULL) {
/*N*/           SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*N*/           rOutliner.SetText(*pOutlinerParaObject);
/*N*/           rOutliner.SetUpdateMode(TRUE);
/*N*/           aSiz=rOutliner.CalcTextSize();
/*N*/           rOutliner.Clear();
/*N*/       }
/*N*/       // 2x casting auf nonconst
/*N*/       ((SdrTextObj*)this)->aTextSize=aSiz;
/*N*/       ((SdrTextObj*)this)->bTextSizeDirty=FALSE;
/*N*/   }
/*N*/   return aTextSize;
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::IsAutoGrowHeight() const
/*N*/ {
/*N*/   if(!bTextFrame)
/*N*/       return FALSE; // AutoGrow nur bei TextFrames
/*N*/
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   BOOL bRet = ((SdrTextAutoGrowHeightItem&)(rSet.Get(SDRATTR_TEXT_AUTOGROWHEIGHT))).GetValue();
/*N*/
/*N*/   if(bRet)
/*N*/   {
/*N*/       SdrTextAniKind eAniKind = ((SdrTextAniKindItem&)(rSet.Get(SDRATTR_TEXT_ANIKIND))).GetValue();
/*N*/
/*N*/       if(eAniKind == SDRTEXTANI_SCROLL || eAniKind == SDRTEXTANI_ALTERNATE || eAniKind == SDRTEXTANI_SLIDE)
/*N*/       {
/*N*/           SdrTextAniDirection eDirection = ((SdrTextAniDirectionItem&)(rSet.Get(SDRATTR_TEXT_ANIDIRECTION))).GetValue();
/*N*/
/*N*/           if(eDirection == SDRTEXTANI_UP || eDirection == SDRTEXTANI_DOWN)
/*N*/           {
/*N*/               bRet = FALSE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::IsAutoGrowWidth() const
/*N*/ {
/*N*/   if(!bTextFrame)
/*N*/       return FALSE; // AutoGrow nur bei TextFrames
/*N*/
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   BOOL bRet = ((SdrTextAutoGrowHeightItem&)(rSet.Get(SDRATTR_TEXT_AUTOGROWWIDTH))).GetValue();
/*N*/
/*N*/   // #101684#
/*N*/   BOOL bInEditMOde = IsInEditMode();
/*N*/
/*N*/   if(!bInEditMOde && bRet)
/*N*/   {
/*N*/       SdrTextAniKind eAniKind = ((SdrTextAniKindItem&)(rSet.Get(SDRATTR_TEXT_ANIKIND))).GetValue();
/*N*/
/*N*/       if(eAniKind == SDRTEXTANI_SCROLL || eAniKind == SDRTEXTANI_ALTERNATE || eAniKind == SDRTEXTANI_SLIDE)
/*N*/       {
/*?*/           SdrTextAniDirection eDirection = ((SdrTextAniDirectionItem&)(rSet.Get(SDRATTR_TEXT_ANIDIRECTION))).GetValue();
/*?*/
/*?*/           if(eDirection == SDRTEXTANI_LEFT || eDirection == SDRTEXTANI_RIGHT)
/*?*/           {
/*?*/               bRet = FALSE;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ SdrTextHorzAdjust SdrTextObj::GetTextHorizontalAdjust() const
/*N*/ {
/*N*/   if(IsContourTextFrame())
/*?*/       return SDRTEXTHORZADJUST_BLOCK;
/*N*/
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   SdrTextHorzAdjust eRet = ((SdrTextHorzAdjustItem&)(rSet.Get(SDRATTR_TEXT_HORZADJUST))).GetValue();
/*N*/
/*N*/   // #101684#
/*N*/   BOOL bInEditMode = IsInEditMode();
/*N*/
/*N*/   if(!bInEditMode && eRet == SDRTEXTHORZADJUST_BLOCK)
/*N*/   {
/*N*/       SdrTextAniKind eAniKind = ((SdrTextAniKindItem&)(rSet.Get(SDRATTR_TEXT_ANIKIND))).GetValue();
/*N*/
/*N*/       if(eAniKind == SDRTEXTANI_SCROLL || eAniKind == SDRTEXTANI_ALTERNATE || eAniKind == SDRTEXTANI_SLIDE)
/*N*/       {
/*?*/           SdrTextAniDirection eDirection = ((SdrTextAniDirectionItem&)(rSet.Get(SDRATTR_TEXT_ANIDIRECTION))).GetValue();
/*?*/
/*?*/           if(eDirection == SDRTEXTANI_LEFT || eDirection == SDRTEXTANI_RIGHT)
/*?*/           {
/*?*/               eRet = SDRTEXTHORZADJUST_LEFT;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return eRet;
/*N*/ } // defaults: BLOCK fuer Textrahmen, CENTER fuer beschriftete Grafikobjekte

/*N*/ SdrTextVertAdjust SdrTextObj::GetTextVerticalAdjust() const
/*N*/ {
/*N*/   if(IsContourTextFrame())
/*?*/       return SDRTEXTVERTADJUST_TOP;
/*N*/
/*N*/   // #103516# Take care for vertical text animation here
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   SdrTextVertAdjust eRet = ((SdrTextVertAdjustItem&)(rSet.Get(SDRATTR_TEXT_VERTADJUST))).GetValue();
/*N*/   BOOL bInEditMode = IsInEditMode();
/*N*/
/*N*/   // #103516# Take care for vertical text animation here
/*N*/   if(!bInEditMode && eRet == SDRTEXTVERTADJUST_BLOCK)
/*N*/   {
/*N*/       SdrTextAniKind eAniKind = ((SdrTextAniKindItem&)(rSet.Get(SDRATTR_TEXT_ANIKIND))).GetValue();
/*N*/
/*N*/       if(eAniKind == SDRTEXTANI_SCROLL || eAniKind == SDRTEXTANI_ALTERNATE || eAniKind == SDRTEXTANI_SLIDE)
/*N*/       {
/*N*/           SdrTextAniDirection eDirection = ((SdrTextAniDirectionItem&)(rSet.Get(SDRATTR_TEXT_ANIDIRECTION))).GetValue();
/*N*/
/*N*/           if(eDirection == SDRTEXTANI_LEFT || eDirection == SDRTEXTANI_RIGHT)
/*N*/           {
/*N*/               eRet = SDRTEXTVERTADJUST_TOP;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return eRet;
/*N*/ } // defaults: TOP fuer Textrahmen, CENTER fuer beschriftete Grafikobjekte

/*N*/ void SdrTextObj::ImpJustifyRect(Rectangle& rRect) const
/*N*/ {
/*N*/   if (!rRect.IsEmpty()) {
/*N*/       rRect.Justify();
/*N*/       if (rRect.Left()==rRect.Right()) rRect.Right()++;
/*N*/       if (rRect.Top()==rRect.Bottom()) rRect.Bottom()++;
/*N*/   }
/*N*/ }

/*N*/ void SdrTextObj::ImpCheckShear()
/*N*/ {
/*N*/   if (bNoShear && aGeo.nShearWink!=0) {
/*N*/       aGeo.nShearWink=0;
/*N*/       aGeo.nTan=0;
/*N*/   }
/*N*/ }

//STRIP001 void SdrTextObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  FASTBOOL bNoTextFrame=!IsTextFrame();
//STRIP001  rInfo.bResizeFreeAllowed=bNoTextFrame || aGeo.nDrehWink%9000==0;
//STRIP001  rInfo.bResizePropAllowed=TRUE;
//STRIP001  rInfo.bRotateFreeAllowed=TRUE;
//STRIP001  rInfo.bRotate90Allowed  =TRUE;
//STRIP001  rInfo.bMirrorFreeAllowed=bNoTextFrame;
//STRIP001  rInfo.bMirror45Allowed  =bNoTextFrame;
//STRIP001  rInfo.bMirror90Allowed  =bNoTextFrame;
//STRIP001
//STRIP001  // allow transparence
//STRIP001  rInfo.bTransparenceAllowed = TRUE;
//STRIP001
//STRIP001  // gradient depends on fillstyle
//STRIP001  XFillStyle eFillStyle = ((XFillStyleItem&)(GetItem(XATTR_FILLSTYLE))).GetValue();
//STRIP001  rInfo.bGradientAllowed = (eFillStyle == XFILL_GRADIENT);
//STRIP001  rInfo.bShearAllowed     =bNoTextFrame;
//STRIP001  rInfo.bEdgeRadiusAllowed=TRUE;
//STRIP001  FASTBOOL bCanConv=ImpCanConvTextToCurve();
//STRIP001  rInfo.bCanConvToPath    =bCanConv;
//STRIP001  rInfo.bCanConvToPoly    =bCanConv;
//STRIP001  rInfo.bCanConvToPathLineToArea=bCanConv;
//STRIP001  rInfo.bCanConvToPolyLineToArea=bCanConv;
//STRIP001  rInfo.bCanConvToContour = (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

//STRIP001 UINT16 SdrTextObj::GetObjIdentifier() const
//STRIP001 {
//STRIP001  return USHORT(eTextKind);
//STRIP001 }

/*N*/ FASTBOOL SdrTextObj::HasEditText() const
/*N*/ {
/*N*/   FASTBOOL bRet=FALSE;
/*N*/   if (pEdtOutl!=NULL) {
/*N*/       Paragraph* p1stPara=pEdtOutl->GetParagraph( 0 );
/*N*/       ULONG nParaAnz=pEdtOutl->GetParagraphCount();
/*N*/       if (p1stPara==NULL) nParaAnz=0;
/*N*/       if (nParaAnz==1) { // bei nur einem Para nachsehen ob da ueberhaupt was drin steht
/*N*/           XubString aStr(pEdtOutl->GetText(p1stPara));
/*N*/
/*N*/           // Aha, steht nix drin!
/*N*/           if(!aStr.Len())
/*N*/               nParaAnz = 0;
/*N*/       }
/*N*/       bRet=nParaAnz!=0;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ void SdrTextObj::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   FASTBOOL bRemove=pNewPage==NULL && pPage!=NULL;
/*N*/   FASTBOOL bInsert=pNewPage!=NULL && pPage==NULL;
/*N*/   FASTBOOL bLinked=IsLinkedText();
/*N*/
/*N*/   if (bLinked && bRemove) {
/*?*/       ImpLinkAbmeldung();
/*N*/   }
/*N*/
/*N*/   SdrAttrObj::SetPage(pNewPage);
/*N*/
/*N*/   if (bLinked && bInsert) {
/*?*/       ImpLinkAnmeldung();
/*N*/   }
/*N*/ }

/*N*/ void SdrTextObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   SdrModel* pOldModel=pModel;
/*N*/   BOOL bLinked=IsLinkedText();
/*N*/   BOOL bChg=pNewModel!=pModel;
/*N*/   BOOL bHgtSet = rSet.GetItemState(EE_CHAR_FONTHEIGHT, TRUE) == SFX_ITEM_SET;
/*N*/   if (bLinked && bChg) {
/*?*/       ImpLinkAbmeldung();
/*N*/   }
/*N*/
/*N*/   SdrAttrObj::SetModel(pNewModel);
/*N*/
/*N*/   if (bChg && pOutlinerParaObject!=NULL && pOldModel!=NULL && pNewModel!=NULL) {
/*?*/       MapUnit aOldUnit(pOldModel->GetScaleUnit());
/*?*/       MapUnit aNewUnit(pNewModel->GetScaleUnit());
/*?*/       FASTBOOL bScaleUnitChanged=aNewUnit!=aOldUnit;
/*?*/       SetTextSizeDirty();
/*?*/       // und nun dem OutlinerParaObject einen neuen Pool verpassen
/*?*/       // !!! Hier muss noch DefTab und RefDevice der beiden Models
/*?*/       // !!! verglichen werden und dann ggf. AutoGrow zuschlagen !!!
/*?*/       // !!! fehlende Implementation !!!
/*?*/       ULONG nOldFontHgt=pOldModel->GetDefaultFontHeight();
/*?*/       ULONG nNewFontHgt=pNewModel->GetDefaultFontHeight();
/*?*/       BOOL bDefHgtChanged=nNewFontHgt!=nOldFontHgt;
/*?*/       BOOL bSetHgtItem=bDefHgtChanged && !bHgtSet;
/*?*/       if (bSetHgtItem) { // #32665#
/*?*/           // zunaechst das HeightItem festklopfen, damit
/*?*/           // 1. Es eben bestehen bleibt und
/*?*/           // 2. DoStretchChars vom richtigen Wert ausgeht
/*?*/           SetItem(SvxFontHeightItem(nOldFontHgt));
/*?*/       }
/*?*/       // erst jetzt den Outliner holen, etc. damit obiges SetAttr auch wirkt
/*?*/       SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*?*/       rOutliner.SetText(*pOutlinerParaObject);
/*?*/       delete pOutlinerParaObject;
/*?*/       pOutlinerParaObject=NULL;
/*?*/       if (bScaleUnitChanged) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            Fraction aMetricFactor=GetMapFactor(aOldUnit,aNewUnit).X();
//STRIP001 /*?*/
//STRIP001 /*?*/            // Funktioniert nicht richtig:
//STRIP001 /*?*/            // Geht am Outliner leider nur in %
//STRIP001 /*?*/            // double nPercFloat=double(aMetricFactor)*100+0.5;
//STRIP001 /*?*/            // USHORT nPerc=(USHORT)nPercFloat;
//STRIP001 /*?*/            // rOutliner.DoStretchChars(100,nPerc);
//STRIP001 /*?*/
//STRIP001 /*?*/            if (bSetHgtItem) {
//STRIP001 /*?*/                // Und nun noch das Rahmenattribut korregieren
//STRIP001 /*?*/                nOldFontHgt=BigMulDiv(nOldFontHgt,aMetricFactor.GetNumerator(),aMetricFactor.GetDenominator());
//STRIP001 /*?*/                SetItem(SvxFontHeightItem(nOldFontHgt));
//STRIP001 /*?*/            }
/*?*/       }
/*?*/       SetOutlinerParaObject(rOutliner.CreateParaObject()); // #34494#
/*?*/       pOutlinerParaObject->ClearPortionInfo();
/*?*/       bPortionInfoChecked=FALSE;
/*?*/       rOutliner.Clear();
/*?*/       //ImpSetTextStyleSheetListeners();
/*N*/   }

/*N*/   if (bLinked && bChg) {
/*?*/       ImpLinkAnmeldung();
/*N*/   }
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::NbcSetEckenradius(long nRad)
/*N*/ {
/*N*/   SetItem(SdrEckenradiusItem(nRad));
/*N*/   return TRUE;
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::NbcSetAutoGrowHeight(FASTBOOL bAuto)
/*N*/ {
/*N*/   if(bTextFrame)
/*N*/   {
/*N*/       SetItem(SdrTextAutoGrowHeightItem(bAuto));
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::NbcSetMinTextFrameHeight(long nHgt)
/*N*/ {
/*N*/   if(bTextFrame)
/*N*/   {
/*N*/       SetItem(SdrTextMinFrameHeightItem(nHgt));
/*N*/
/*N*/       // #84974# use bDisableAutoWidthOnDragging as
/*N*/       // bDisableAutoHeightOnDragging if vertical.
/*N*/       if(IsVerticalWriting() && bDisableAutoWidthOnDragging)
/*N*/       {
/*?*/           bDisableAutoWidthOnDragging = FALSE;
/*?*/           SetItem(SdrTextAutoGrowHeightItem(FALSE));
/*N*/       }
/*N*/
/*N*/       return TRUE;
/*N*/   }
/*?*/   return FALSE;
/*N*/ }

//STRIP001 FASTBOOL SdrTextObj::NbcSetMaxTextFrameHeight(long nHgt)
//STRIP001 {
//STRIP001  if(bTextFrame)
//STRIP001  {
//STRIP001      SetItem(SdrTextMaxFrameHeightItem(nHgt));
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 FASTBOOL SdrTextObj::NbcSetAutoGrowWidth(FASTBOOL bAuto)
//STRIP001 {
//STRIP001  if(bTextFrame)
//STRIP001  {
//STRIP001      SetItem(SdrTextAutoGrowWidthItem(bAuto));
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ FASTBOOL SdrTextObj::NbcSetMinTextFrameWidth(long nWdt)
/*N*/ {
/*N*/   if(bTextFrame)
/*N*/   {
/*N*/       SetItem(SdrTextMinFrameWidthItem(nWdt));
/*N*/
/*N*/       // #84974# use bDisableAutoWidthOnDragging only
/*N*/       // when not vertical.
/*N*/       if(!IsVerticalWriting() && bDisableAutoWidthOnDragging)
/*N*/       {
/*?*/           bDisableAutoWidthOnDragging = FALSE;
/*?*/           SetItem(SdrTextAutoGrowWidthItem(FALSE));
/*N*/       }
/*N*/
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

//STRIP001 FASTBOOL SdrTextObj::NbcSetMaxTextFrameWidth(long nWdt)
//STRIP001 {
//STRIP001  if(bTextFrame)
//STRIP001  {
//STRIP001      SetItem(SdrTextMaxFrameWidthItem(nWdt));
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 FASTBOOL SdrTextObj::NbcSetFitToSize(SdrFitToSizeType eFit)
//STRIP001 {
//STRIP001  if(bTextFrame)
//STRIP001  {
//STRIP001      SetItem(SdrTextFitToSizeTypeItem(eFit));
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrTextObj::ImpSetContourPolygon( SdrOutliner& rOutliner, Rectangle& rAnchorRect, BOOL bLineWidth ) const
//STRIP001 {
//STRIP001
//STRIP001  XPolyPolygon aXorXPP;
//STRIP001  TakeXorPoly(aXorXPP, FALSE);
//STRIP001  if (aGeo.nDrehWink!=0) { // Unrotate!
//STRIP001      RotateXPoly(aXorXPP,rAnchorRect.TopLeft(),-aGeo.nSin,aGeo.nCos);
//STRIP001  }
//STRIP001  Point aRef(rAnchorRect.TopLeft());
//STRIP001  aXorXPP.Move(-aRef.X(),-aRef.Y());
//STRIP001
//STRIP001  XPolyPolygon* pContourXPP = NULL;
//STRIP001
//STRIP001  if( bLineWidth )
//STRIP001  {
//STRIP001      // Strichstaerke beruecksichtigen
//STRIP001      // Beim Hittest muss das unterbleiben (Performance!)
//STRIP001      pContourXPP = new XPolyPolygon();
//STRIP001
//STRIP001      // #86258# test if shadow needs to be avoided for TakeContour()
//STRIP001      const SfxItemSet& rSet = GetItemSet();
//STRIP001      sal_Bool bShadowOn = ((SdrShadowItem&)(rSet.Get(SDRATTR_SHADOW))).GetValue();
//STRIP001
//STRIP001      if(bShadowOn)
//STRIP001      {
//STRIP001          // #86258# force shadow off
//STRIP001          SdrObject* pCopy = Clone();
//STRIP001          pCopy->SetItem(SdrShadowItem(FALSE));
//STRIP001          pCopy->TakeContour(*pContourXPP);
//STRIP001          delete pCopy;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          TakeContour(*pContourXPP);
//STRIP001      }
//STRIP001
//STRIP001      if (aGeo.nDrehWink!=0)  // Unrotate!
//STRIP001          RotateXPoly(*pContourXPP,rAnchorRect.TopLeft(),-aGeo.nSin,aGeo.nCos);
//STRIP001      pContourXPP->Move(-aRef.X(),-aRef.Y());
//STRIP001  }
//STRIP001
//STRIP001  rOutliner.SetPolygon(aXorXPP, pContourXPP);
//STRIP001 }

/*N*/ void SdrTextObj::TakeUnrotatedSnapRect(Rectangle& rRect) const
/*N*/ {
/*N*/   rRect=aRect;
/*N*/ }

/*N*/ void SdrTextObj::TakeTextAnchorRect(Rectangle& rAnchorRect) const
/*N*/ {
/*N*/   long nLeftDist=GetTextLeftDistance();
/*N*/   long nRightDist=GetTextRightDistance();
/*N*/   long nUpperDist=GetTextUpperDistance();
/*N*/   long nLowerDist=GetTextLowerDistance();
/*N*/   Rectangle aAnkRect(aRect); // Rect innerhalb dem geankert wird
/*N*/   FASTBOOL bFrame=IsTextFrame();
/*N*/   if (!bFrame) {
/*N*/       TakeUnrotatedSnapRect(aAnkRect);
/*N*/   }
/*N*/   Point aRotateRef(aAnkRect.TopLeft());
/*N*/   aAnkRect.Left()+=nLeftDist;
/*N*/   aAnkRect.Top()+=nUpperDist;
/*N*/   aAnkRect.Right()-=nRightDist;
/*N*/   aAnkRect.Bottom()-=nLowerDist;
/*N*/
/*N*/   // #108816#
/*N*/   // Since sizes may be bigger than the object bounds it is necessary to
/*N*/   // justify the rect now.
/*N*/   ImpJustifyRect(aAnkRect);
/*N*/
/*N*/   if (bFrame) {
/*N*/       // !!! hier noch etwas verfeinern !!!
/*N*/       if (aAnkRect.GetWidth()<2) aAnkRect.Right()=aAnkRect.Left()+1;   // Mindestgroesse 2
/*N*/       if (aAnkRect.GetHeight()<2) aAnkRect.Bottom()=aAnkRect.Top()+1;  // Mindestgroesse 2
/*N*/   }
/*N*/   if (aGeo.nDrehWink!=0) {
/*N*/       Point aTmpPt(aAnkRect.TopLeft());
/*N*/       RotatePoint(aTmpPt,aRotateRef,aGeo.nSin,aGeo.nCos);
/*N*/       aTmpPt-=aAnkRect.TopLeft();
/*N*/       aAnkRect.Move(aTmpPt.X(),aTmpPt.Y());
/*N*/   }
/*N*/   rAnchorRect=aAnkRect;
/*N*/ }

/*N*/ void SdrTextObj::TakeTextRect( SdrOutliner& rOutliner, Rectangle& rTextRect, FASTBOOL bNoEditText,
/*N*/                              Rectangle* pAnchorRect, BOOL bLineWidth ) const
/*N*/ {
/*N*/   Rectangle aAnkRect; // Rect innerhalb dem geankert wird
/*N*/   TakeTextAnchorRect(aAnkRect);
/*N*/   SdrTextVertAdjust eVAdj=GetTextVerticalAdjust();
/*N*/   SdrTextHorzAdjust eHAdj=GetTextHorizontalAdjust();
/*N*/   SdrTextAniKind      eAniKind=GetTextAniKind();
/*N*/   SdrTextAniDirection eAniDirection=GetTextAniDirection();
/*N*/
/*N*/   SdrFitToSizeType eFit=GetFitToSize();
/*N*/   FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
/*N*/   FASTBOOL bContourFrame=IsContourTextFrame();
/*N*/
/*N*/   FASTBOOL bFrame=IsTextFrame();
/*N*/   ULONG nStat0=rOutliner.GetControlWord();
/*N*/   Size aNullSize;
/*N*/   if (!bContourFrame)
/*N*/   {
/*N*/       rOutliner.SetControlWord(nStat0|EE_CNTRL_AUTOPAGESIZE);
/*N*/       rOutliner.SetMinAutoPaperSize(aNullSize);
/*N*/       rOutliner.SetMaxAutoPaperSize(Size(1000000,1000000));
/*N*/   }
/*N*/
/*N*/   if (!bFitToSize && !bContourFrame)
/*N*/   {
/*N*/       long nAnkWdt=aAnkRect.GetWidth();
/*N*/       long nAnkHgt=aAnkRect.GetHeight();
/*N*/       if (bFrame)
/*N*/       {
/*N*/           long nWdt=nAnkWdt;
/*N*/           long nHgt=nAnkHgt;
/*N*/
/*N*/           // #101684#
/*N*/           BOOL bInEditMode = IsInEditMode();
/*N*/
/*N*/           if (!bInEditMode && (eAniKind==SDRTEXTANI_SCROLL || eAniKind==SDRTEXTANI_ALTERNATE || eAniKind==SDRTEXTANI_SLIDE))
/*N*/           {
/*?*/               // Grenzenlose Papiergroesse fuer Laufschrift
/*?*/               if (eAniDirection==SDRTEXTANI_LEFT || eAniDirection==SDRTEXTANI_RIGHT) nWdt=1000000;
/*?*/               if (eAniDirection==SDRTEXTANI_UP || eAniDirection==SDRTEXTANI_DOWN) nHgt=1000000;
/*N*/           }
/*N*/           rOutliner.SetMaxAutoPaperSize(Size(nWdt,nHgt));
/*N*/       }
/*N*/
/*N*/       // #103516# New try with _BLOCK for hor and ver after completely
/*N*/       // supporting full width for vertical text.
/*N*/       if(SDRTEXTHORZADJUST_BLOCK == eHAdj && !IsVerticalWriting())
/*N*/       {
/*N*/           rOutliner.SetMinAutoPaperSize(Size(nAnkWdt, 0));
/*N*/       }
/*N*/
/*N*/       if(SDRTEXTVERTADJUST_BLOCK == eVAdj && IsVerticalWriting())
/*N*/       {
/*N*/           rOutliner.SetMinAutoPaperSize(Size(0, nAnkHgt));
/*N*/       }
/*N*/
/*N*/       // #103335# back to old solution, thus #100801# will be back and needs to be solved in
/*N*/       // another way.
//      if (eHAdj==SDRTEXTHORZADJUST_BLOCK)
//      {
//          if(IsVerticalWriting())
//              rOutliner.SetMinAutoPaperSize(Size(nAnkWdt, nAnkHgt));
//          else
//              rOutliner.SetMinAutoPaperSize(Size(nAnkWdt, 0));
//      }

//      // #100801# MinAutoPaperSize needs always to be set completely
//      // when Verical
//      if(IsVerticalWriting())
//      {
//          rOutliner.SetMinAutoPaperSize(Size(nAnkWdt, nAnkHgt));
//      }
//
//      if(SDRTEXTHORZADJUST_BLOCK == eHAdj)
//      {
//          // #89459#
//          if(!IsVerticalWriting())
//          {
//              rOutliner.SetMinAutoPaperSize(Size(nAnkWdt, 0));
//          }
//      }
/*N*/   }
/*N*/
/*N*/   rOutliner.SetPaperSize(aNullSize);
/*N*/   if (bContourFrame)
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ImpSetContourPolygon( rOutliner, aAnkRect, bLineWidth );
/*N*/
/*N*/   // Text in den Outliner stecken - ggf. den aus dem EditOutliner
/*N*/   OutlinerParaObject* pPara=pOutlinerParaObject;
/*N*/   if (pEdtOutl && !bNoEditText)
/*?*/       pPara=pEdtOutl->CreateParaObject();
/*N*/
/*N*/   if (pPara)
/*N*/   {
/*N*/       BOOL bHitTest = FALSE;
/*N*/       if( pModel )
/*N*/           bHitTest = &pModel->GetHitTestOutliner() == &rOutliner;
/*N*/
/*N*/       const SdrTextObj* pTestObj = rOutliner.GetTextObj();
/*N*/       if( !pTestObj || !bHitTest || pTestObj != this ||
/*N*/           pTestObj->GetOutlinerParaObject() != pOutlinerParaObject )
/*N*/       {
/*N*/           if( bHitTest )
/*N*/               rOutliner.SetTextObj( this );
/*N*/
/*N*/           rOutliner.SetUpdateMode(TRUE);
/*N*/           rOutliner.SetText(*pPara);
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/ //        rOutliner.Clear();
/*?*/       rOutliner.SetTextObj( NULL );
/*N*/   }
/*N*/
/*N*/   if (pEdtOutl && !bNoEditText && pPara)
/*?*/       delete pPara;
/*N*/
/*N*/   rOutliner.SetUpdateMode(TRUE);
/*N*/   rOutliner.SetControlWord(nStat0);
/*N*/
/*N*/   if (!bPortionInfoChecked)
/*N*/   {
/*N*/       // Optimierung: ggf. BigTextObject erzeugen
/*N*/       ((SdrTextObj*)this)->bPortionInfoChecked=TRUE;
/*N*/       if (pOutlinerParaObject!=NULL && rOutliner.ShouldCreateBigTextObject())
/*?*/           ((SdrTextObj*)this)->pOutlinerParaObject=rOutliner.CreateParaObject();
/*N*/   }
/*N*/
/*N*/   Point aTextPos(aAnkRect.TopLeft());
/*N*/   Size aTextSiz(rOutliner.GetPaperSize()); // GetPaperSize() hat etwas Toleranz drauf, oder?
/*N*/
/*N*/   // #106653#
/*N*/   // For draw objects containing text correct hor/ver alignment if text is bigger
/*N*/   // than the object itself. Without that correction, the text would always be
/*N*/   // formatted to the left edge (or top edge when vertical) of the draw object.
/*N*/   if(!IsTextFrame())
/*N*/   {
/*N*/       if(aAnkRect.GetWidth() < aTextSiz.Width() && !IsVerticalWriting())
/*N*/       {
/*N*/           // #110129#
/*N*/           // Horizontal case here. Correct only if eHAdj == SDRTEXTHORZADJUST_BLOCK,
/*N*/           // else the alignment is wanted.
/*N*/           if(SDRTEXTHORZADJUST_BLOCK == eHAdj)
/*N*/           {
/*N*/               eHAdj = SDRTEXTHORZADJUST_CENTER;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if(aAnkRect.GetHeight() < aTextSiz.Height() && IsVerticalWriting())
/*N*/       {
/*N*/           // #110129#
/*N*/           // Vertical case here. Correct only if eHAdj == SDRTEXTVERTADJUST_BLOCK,
/*N*/           // else the alignment is wanted.
/*N*/           if(SDRTEXTVERTADJUST_BLOCK == eVAdj)
/*N*/           {
/*N*/               eVAdj = SDRTEXTVERTADJUST_CENTER;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (eHAdj==SDRTEXTHORZADJUST_CENTER || eHAdj==SDRTEXTHORZADJUST_RIGHT)
/*N*/   {
/*N*/       long nFreeWdt=aAnkRect.GetWidth()-aTextSiz.Width();
/*N*/       if (eHAdj==SDRTEXTHORZADJUST_CENTER)
/*N*/           aTextPos.X()+=nFreeWdt/2;
/*N*/       if (eHAdj==SDRTEXTHORZADJUST_RIGHT)
/*N*/           aTextPos.X()+=nFreeWdt;
/*N*/   }
/*N*/   if (eVAdj==SDRTEXTVERTADJUST_CENTER || eVAdj==SDRTEXTVERTADJUST_BOTTOM)
/*N*/   {
/*N*/       long nFreeHgt=aAnkRect.GetHeight()-aTextSiz.Height();
/*N*/       if (eVAdj==SDRTEXTVERTADJUST_CENTER)
/*N*/           aTextPos.Y()+=nFreeHgt/2;
/*N*/       if (eVAdj==SDRTEXTVERTADJUST_BOTTOM)
/*N*/           aTextPos.Y()+=nFreeHgt;
/*N*/   }
/*N*/   if (aGeo.nDrehWink!=0)
/*N*/       RotatePoint(aTextPos,aAnkRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/
/*N*/   if (pAnchorRect)
/*N*/       *pAnchorRect=aAnkRect;
/*N*/
/*N*/   // rTextRect ist bei ContourFrame in einigen Faellen nicht korrekt
/*N*/   rTextRect=Rectangle(aTextPos,aTextSiz);
/*N*/   if (bContourFrame)
/*?*/       rTextRect=aAnkRect;
/*N*/ }

/*N*/ OutlinerParaObject* SdrTextObj::GetEditOutlinerParaObject() const
/*N*/ {
/*N*/   OutlinerParaObject* pPara=NULL;
/*N*/   if (pEdtOutl!=NULL) { // Wird gerade editiert, also das ParaObject aus dem aktiven Editor verwenden
/*?*/       Paragraph* p1stPara=pEdtOutl->GetParagraph( 0 );
/*?*/       ULONG nParaAnz=pEdtOutl->GetParagraphCount();
/*?*/       if (nParaAnz==1 && p1stPara!=NULL) { // bei nur einem Para nachsehen ob da ueberhaupt was drin steht
/*?*/           XubString aStr(pEdtOutl->GetText(p1stPara));
/*?*/
/*?*/           // Aha, steht nix drin!
/*?*/           if(!aStr.Len())
/*?*/               nParaAnz = 0;
/*?*/       }
/*?*/       if (p1stPara!=NULL && nParaAnz!=0) {
/*?*/           pPara = pEdtOutl->CreateParaObject(0, (sal_uInt16)nParaAnz);
/*?*/       }
/*N*/   }
/*N*/   return pPara;
/*N*/ }

//STRIP001 void SdrTextObj::ImpSetCharStretching(SdrOutliner& rOutliner, const Rectangle& rTextRect, const Rectangle& rAnchorRect, Fraction& rFitXKorreg) const
//STRIP001 {
//STRIP001  OutputDevice* pOut = rOutliner.GetRefDevice();
//STRIP001  BOOL bNoStretching(FALSE);
//STRIP001
//STRIP001  if(pOut && pOut->GetOutDevType() == OUTDEV_PRINTER)
//STRIP001  {
//STRIP001      // #35762#: Checken ob CharStretching ueberhaupt moeglich
//STRIP001      GDIMetaFile* pMtf = pOut->GetConnectMetaFile();
//STRIP001      UniString aTestString(sal_Unicode('J'));
//STRIP001
//STRIP001      if(pMtf && (!pMtf->IsRecord() || pMtf->IsPause()))
//STRIP001          pMtf = NULL;
//STRIP001
//STRIP001      if(pMtf)
//STRIP001          pMtf->Pause(TRUE);
//STRIP001
//STRIP001      Font aFontMerk(pOut->GetFont());
//STRIP001      Font aTmpFont( OutputDevice::GetDefaultFont( DEFAULTFONT_SERIF, LANGUAGE_SYSTEM, DEFAULTFONT_FLAGS_ONLYONE ) );
//STRIP001
//STRIP001      aTmpFont.SetSize(Size(0,100));
//STRIP001      pOut->SetFont(aTmpFont);
//STRIP001      Size aSize1(pOut->GetTextWidth(aTestString), pOut->GetTextHeight());
//STRIP001      aTmpFont.SetSize(Size(800,100));
//STRIP001      pOut->SetFont(aTmpFont);
//STRIP001      Size aSize2(pOut->GetTextWidth(aTestString), pOut->GetTextHeight());
//STRIP001      pOut->SetFont(aFontMerk);
//STRIP001
//STRIP001      if(pMtf)
//STRIP001          pMtf->Pause(FALSE);
//STRIP001
//STRIP001      bNoStretching = (aSize1 == aSize2);
//STRIP001
//STRIP001 #ifdef WNT
//STRIP001      // #35762# Windows vergroessert bei Size(100,500) den Font proportional
//STRIP001      // Und das finden wir nicht so schoen.
//STRIP001      if(aSize2.Height() >= aSize1.Height() * 2)
//STRIP001      {
//STRIP001          bNoStretching = TRUE;
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001  unsigned nLoopCount=0;
//STRIP001  FASTBOOL bNoMoreLoop=FALSE;
//STRIP001  long nXDiff0=0x7FFFFFFF;
//STRIP001  long nWantWdt=rAnchorRect.Right()-rAnchorRect.Left();
//STRIP001  long nIsWdt=rTextRect.Right()-rTextRect.Left();
//STRIP001  if (nIsWdt==0) nIsWdt=1;
//STRIP001
//STRIP001  long nWantHgt=rAnchorRect.Bottom()-rAnchorRect.Top();
//STRIP001  long nIsHgt=rTextRect.Bottom()-rTextRect.Top();
//STRIP001  if (nIsHgt==0) nIsHgt=1;
//STRIP001
//STRIP001  long nXTolPl=nWantWdt/100; // Toleranz +1%
//STRIP001  long nXTolMi=nWantWdt/25;  // Toleranz -4%
//STRIP001  long nXKorr =nWantWdt/20;  // Korrekturmasstab 5%
//STRIP001
//STRIP001  long nX=(nWantWdt*100) /nIsWdt; // X-Stretching berechnen
//STRIP001  long nY=(nWantHgt*100) /nIsHgt; // Y-Stretching berechnen
//STRIP001  FASTBOOL bChkX=TRUE;
//STRIP001  FASTBOOL bChkY=TRUE;
//STRIP001  if (bNoStretching) { // #35762# evtl. nur proportional moeglich
//STRIP001      if (nX>nY) { nX=nY; bChkX=FALSE; }
//STRIP001      else { nY=nX; bChkY=FALSE; }
//STRIP001  }
//STRIP001
//STRIP001  while (nLoopCount<5 && !bNoMoreLoop) {
//STRIP001      if (nX<0) nX=-nX;
//STRIP001      if (nX<1) { nX=1; bNoMoreLoop=TRUE; }
//STRIP001      if (nX>65535) { nX=65535; bNoMoreLoop=TRUE; }
//STRIP001
//STRIP001      if (nY<0) nY=-nY;
//STRIP001      if (nY<1) { nY=1; bNoMoreLoop=TRUE; }
//STRIP001      if (nY>65535) { nY=65535; bNoMoreLoop=TRUE; }
//STRIP001
//STRIP001      // exception, there is no text yet (horizontal case)
//STRIP001      if(nIsWdt <= 1)
//STRIP001      {
//STRIP001          nX = nY;
//STRIP001          bNoMoreLoop = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      // #87877# exception, there is no text yet (vertical case)
//STRIP001      if(nIsHgt <= 1)
//STRIP001      {
//STRIP001          nY = nX;
//STRIP001          bNoMoreLoop = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      rOutliner.SetGlobalCharStretching((USHORT)nX,(USHORT)nY);
//STRIP001      nLoopCount++;
//STRIP001      Size aSiz(rOutliner.CalcTextSize());
//STRIP001      long nXDiff=aSiz.Width()-nWantWdt;
//STRIP001      rFitXKorreg=Fraction(nWantWdt,aSiz.Width());
//STRIP001      if (((nXDiff>=nXTolMi || !bChkX) && nXDiff<=nXTolPl) || nXDiff==nXDiff0/*&& Abs(nYDiff)<=nYTol*/) {
//STRIP001          bNoMoreLoop=TRUE;
//STRIP001      } else {
//STRIP001          // Stretchingfaktoren korregieren
//STRIP001          long nMul=nWantWdt;
//STRIP001          long nDiv=aSiz.Width();
//STRIP001          if (Abs(nXDiff)<=2*nXKorr) {
//STRIP001              if (nMul>nDiv) nDiv+=(nMul-nDiv)/2; // und zwar nur um die haelfte des berechneten
//STRIP001              else nMul+=(nDiv-nMul)/2;           // weil die EE ja eh wieder falsch rechnet
//STRIP001          }
//STRIP001          nX=nX*nMul/nDiv;
//STRIP001          if (bNoStretching) nY=nX;
//STRIP001      }
//STRIP001      nXDiff0=nXDiff;
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrTextObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  // Hidden objects on masterpages, draw nothing
//STRIP001  if((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) && bNotVisibleAsMaster)
//STRIP001      return TRUE;
//STRIP001
//STRIP001  FASTBOOL bOk=TRUE;
//STRIP001  FASTBOOL bPrinter=rXOut.GetOutDev()->GetOutDevType()==OUTDEV_PRINTER;
//STRIP001     FASTBOOL bPrintPreView=rXOut.GetOutDev()->GetOutDevViewType()==OUTDEV_VIEWTYPE_PRINTPREVIEW;
//STRIP001
//STRIP001  if (bPrinter && bEmptyPresObj)
//STRIP001      return bOk; // Leere Praesentationsobjekte nicht drucken!
//STRIP001
//STRIP001  if (!bPrinter && pEdtOutl!=NULL && rInfoRec.pPV!=NULL &&
//STRIP001      rInfoRec.pPV->GetView().GetTextEditObject()==(SdrObject*)this)
//STRIP001      return bOk; // Textobjekt wird gerade editiert in der auffordernen View
//STRIP001
//STRIP001  if ((rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTTEXT) ==0)
//STRIP001  {
//STRIP001      if (pOutlinerParaObject!=NULL || (pEdtOutl!=NULL && HasEditText()))
//STRIP001      {
//STRIP001          SdrOutliner& rOutliner=ImpGetDrawOutliner();
//STRIP001
//STRIP001          {
//STRIP001              SvtAccessibilityOptions aOptions;
//STRIP001                 FASTBOOL bForceAutoColor = aOptions.GetIsAutomaticFontColor();
//STRIP001                 //#106611# don't use automatic colors in WYSIWYG Print Previews
//STRIP001                 if(bPrintPreView&& !aOptions.GetIsForPagePreviews())
//STRIP001                     bForceAutoColor = FALSE;
//STRIP001              rOutliner.ForceAutoColor( bForceAutoColor );
//STRIP001          }
//STRIP001
//STRIP001          FASTBOOL bContourFrame=IsContourTextFrame();
//STRIP001          if (IsFontwork() && !bContourFrame)
//STRIP001          { // FontWork
//STRIP001              if (pModel!=NULL)
//STRIP001              {
//STRIP001                  rOutliner.SetUpdateMode(TRUE); // hier kann ggf. noch optimiert werden !!!
//STRIP001                  ImpTextPortionHandler aTPHandler(rOutliner,*this);
//STRIP001
//STRIP001                  // #78478# to have the outline color in XOutputDevice::ImpDrawFormText(...)
//STRIP001                  // SetLineAttr(...) needs to be called if the outline item is set
//STRIP001                  const SfxItemSet& rSet = GetItemSet();
//STRIP001                  BOOL bFormTextOutline = ((XFormTextOutlineItem&)(rSet.Get(XATTR_FORMTXTOUTLINE))).GetValue();
//STRIP001
//STRIP001                  if(bFormTextOutline)
//STRIP001                      rXOut.SetLineAttr(rSet);
//STRIP001
//STRIP001                  rXOut.SetTextAttr(rSet);
//STRIP001
//STRIP001                  aTPHandler.DrawTextToPath(rXOut); // drucken bei aktivem Textedit fehlt hier
//STRIP001                  rOutliner.Clear();
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // sonst kein Fontwork
//STRIP001              // hier findet das richtige Painten des Textes statt
//STRIP001
//STRIP001              Rectangle aTextRect;
//STRIP001              Rectangle aAnchorRect;
//STRIP001              Rectangle aPaintRect;
//STRIP001              Fraction aFitXKorreg(1,1);
//STRIP001
//STRIP001                 // #101029#: Extracted Outliner setup to ImpSetupDrawOutlinerForPaint
//STRIP001                 ImpSetupDrawOutlinerForPaint( bContourFrame, rOutliner, aTextRect, aAnchorRect, aPaintRect, aFitXKorreg );
//STRIP001
//STRIP001              FASTBOOL bAnimated=GetTextAniKind()!=SDRTEXTANI_NONE;
//STRIP001              OutputDevice* pOutDev=rXOut.GetOutDev();
//STRIP001
//STRIP001              // #98825# Text animation is initialized and strted from this Paint()
//STRIP001              // no one seems to use StartTextAnimation(...) or StopTextAnimation(...)
//STRIP001              // at all. Thus, I need to stop text animation here when necessary.
//STRIP001              sal_Bool bDoNotPaintAnimatedText =
//STRIP001                  bPrinter || (rInfoRec.nPaintMode & SDRPAINTMODE_ANILIKEPRN) !=0 || !bAnimated;
//STRIP001
//STRIP001              if(!bDoNotPaintAnimatedText)
//STRIP001              {
//STRIP001                  // if animated text is disabled, do not start it here...
//STRIP001                  if(0L != rInfoRec.pPV)
//STRIP001                  {
//STRIP001                      const SdrView& rTargetView = rInfoRec.pPV->GetView();
//STRIP001                      const SvtAccessibilityOptions& rOpt = ((SdrView&)rTargetView).getAccessibilityOptions();
//STRIP001                      sal_Bool bIsAllowedAnimatedText = rOpt.GetIsAllowAnimatedText();
//STRIP001
//STRIP001                      if(!bIsAllowedAnimatedText)
//STRIP001                      {
//STRIP001                          bDoNotPaintAnimatedText = sal_True;
//STRIP001
//STRIP001                          if(pPlusData && pPlusData->pAnimator)
//STRIP001                          {
//STRIP001                              pPlusData->pAnimator->Stop();
//STRIP001                              delete pPlusData->pAnimator;
//STRIP001                              pPlusData->pAnimator = 0L;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if(bDoNotPaintAnimatedText)
//STRIP001              {
//STRIP001                  if (!bAnimated && pPlusData!=NULL && pPlusData->pAnimator!=NULL)
//STRIP001                  {
//STRIP001                      delete pPlusData->pAnimator;
//STRIP001                      pPlusData->pAnimator=NULL;
//STRIP001                  }
//STRIP001                  if (aGeo.nDrehWink!=0)
//STRIP001                  {
//STRIP001                      // #49328# bei AutoGrowHeight()=TRUE nicht mehr clippen
//STRIP001                      FASTBOOL bNeedClip=(bTextFrame && !IsAutoGrowHeight()) || bContourFrame;
//STRIP001                      // ClipRegion setzen. Das macht Malte bei gedrehter Ausgabe naemlich nicht!
//STRIP001                      FASTBOOL bMtf=pOutDev->GetConnectMetaFile()!=NULL;
//STRIP001                      // Clipping merken
//STRIP001                      FASTBOOL bClip0=pOutDev->IsClipRegion();
//STRIP001                      Region   aClip0(pOutDev->GetClipRegion());
//STRIP001                      if (bNeedClip)
//STRIP001                      {
//STRIP001                          if (bMtf) pOutDev->Push();
//STRIP001                          // Neues Clipping setzen
//STRIP001                          Rectangle aClipRect(aPaintRect);
//STRIP001                          if (bPrinter)
//STRIP001                          { // #42520#: Bei HP-Druckern fehlt sonst oefter der letzte Buchstabe einer Zeile
//STRIP001                              Size a1Pix(pOutDev->PixelToLogic(Size(1,1)));
//STRIP001                              aClipRect.Top()-=a1Pix.Width();
//STRIP001                              aClipRect.Left()-=a1Pix.Height();
//STRIP001                              aClipRect.Right()+=a1Pix.Width();
//STRIP001                              aClipRect.Bottom()+=a1Pix.Height();
//STRIP001                          }
//STRIP001                          Polygon aClipPoly(aClipRect);
//STRIP001                          RotatePoly(aClipPoly,aPaintRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001                          // Intersect geht leider nicht, weil Poly statt Rect
//STRIP001                          pOutDev->SetClipRegion(aClipPoly);
//STRIP001                          if (bClip0)
//STRIP001                          {
//STRIP001                              // Aber wenn's vorher nur ein Rechteck war, dann
//STRIP001                              // intersecte ich mein Poly nun mit diesem
//STRIP001                              pOutDev->IntersectClipRegion(aClip0.GetBoundRect());
//STRIP001                          }
//STRIP001                      }
//STRIP001                      // Textausgabe
//STRIP001                      rOutliner.Draw(pOutDev,aPaintRect.TopLeft(),(short)(aGeo.nDrehWink/10));
//STRIP001                      if (bNeedClip)
//STRIP001                      {
//STRIP001                          // Clipping restaurieren
//STRIP001                          if (bMtf)
//STRIP001                              pOutDev->Pop();
//STRIP001                          else
//STRIP001                          {
//STRIP001                              if (bClip0)
//STRIP001                                  pOutDev->SetClipRegion(aClip0);
//STRIP001                              else
//STRIP001                                  pOutDev->SetClipRegion();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                         if(IsVerticalWriting())
//STRIP001                         {
//STRIP001                             // new try for #82826#
//STRIP001                             if(aAnchorRect.GetWidth() > aPaintRect.GetWidth())
//STRIP001                             {
//STRIP001                                 aPaintRect = Rectangle(
//STRIP001                                     aPaintRect.Right() - aAnchorRect.GetWidth(), aPaintRect.Top(),
//STRIP001                                     aPaintRect.Right(), aPaintRect.Bottom());
//STRIP001                             }
//STRIP001
//STRIP001                             // #91744# for vertical writing the original fix #82826#
//STRIP001                             // needs to be taken out.
//STRIP001                             rOutliner.Draw(pOutDev, aPaintRect);
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             // new try for #82826#
//STRIP001                             if(aAnchorRect.GetHeight() > aPaintRect.GetHeight())
//STRIP001                             {
//STRIP001                                 aPaintRect = Rectangle(
//STRIP001                                     aPaintRect.Left(), aPaintRect.Top(),
//STRIP001                                     aPaintRect.Right(), aPaintRect.Top() + aAnchorRect.GetHeight());
//STRIP001                             }
//STRIP001
//STRIP001                             // #91809# for horizontal writing the original fix #82826#
//STRIP001                             // needs to be taken out, too.
//STRIP001                             rOutliner.Draw(pOutDev, aPaintRect);
//STRIP001
//STRIP001                             // #82826# for correct preview of outliner views
//STRIP001                             //// rOutliner.Draw(pOutDev,aPaintRect);
//STRIP001                             //if(aPaintRect.Top() > aAnchorRect.Top())
//STRIP001                             //   rOutliner.Draw(pOutDev, aPaintRect);
//STRIP001                             //else
//STRIP001                             //   rOutliner.Draw(pOutDev, aAnchorRect);
//STRIP001                         }
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  ImpPaintAnimatedText(*rXOut.GetOutDev(),rXOut.GetOffset(),rOutliner,aAnchorRect,aPaintRect,rInfoRec);
//STRIP001              }
//STRIP001
//STRIP001              rOutliner.Clear();
//STRIP001          }
//STRIP001      } // if (pPara!=NULL)
//STRIP001      if (bEmptyPresObj)
//STRIP001      {
//STRIP001          // leere Praesentationsobjekte bekommen einen grauen Rahmen
//STRIP001             svtools::ColorConfig aColorConfig;
//STRIP001             svtools::ColorConfigValue aColor( aColorConfig.GetColorValue( svtools::OBJECTBOUNDARIES ) );
//STRIP001
//STRIP001          if( aColor.bIsVisible )
//STRIP001          {
//STRIP001              rXOut.GetOutDev()->SetFillColor();
//STRIP001              rXOut.GetOutDev()->SetLineColor( aColor.nColor );
//STRIP001
//STRIP001              if (aGeo.nDrehWink!=0 || aGeo.nShearWink!=0)
//STRIP001              {
//STRIP001                  Polygon aPoly(aRect);
//STRIP001                  if (aGeo.nShearWink!=0)
//STRIP001                      ShearPoly(aPoly,aRect.TopLeft(),aGeo.nTan);
//STRIP001
//STRIP001                  if (aGeo.nDrehWink!=0)
//STRIP001                      RotatePoly(aPoly,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001
//STRIP001                  rXOut.GetOutDev()->DrawPolyLine(aPoly);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rXOut.GetOutDev()->DrawRect(aRect);
//STRIP001              }
//STRIP001          }
//STRIP001      } // if pOutlParaObj!=NULL
//STRIP001  }
//STRIP001  else
//STRIP001  { // sonst SDRPAINTMODE_DRAFTTEXT
//STRIP001      FASTBOOL bFill=HasFill();
//STRIP001      FASTBOOL bLine=HasLine();
//STRIP001      FASTBOOL bHide=IsFontwork() && IsHideContour() && pFormTextBoundRect!=NULL;
//STRIP001
//STRIP001      if (bHide)
//STRIP001      {
//STRIP001          bFill=FALSE;
//STRIP001          bLine=FALSE;
//STRIP001      }
//STRIP001
//STRIP001      if ((bTextFrame && !bLine && !bFill) || bHide)
//STRIP001      {
//STRIP001          OutputDevice* pOut=rXOut.GetOutDev();
//STRIP001          Polygon aPoly;
//STRIP001
//STRIP001          if (bHide)
//STRIP001              aPoly=Polygon(*pFormTextBoundRect);
//STRIP001          else
//STRIP001              aPoly=Rect2Poly(aRect,aGeo);
//STRIP001
//STRIP001          if (aPoly.GetSize()>=4)
//STRIP001          {
//STRIP001              pOut->SetLineColor(Color(COL_BLACK));
//STRIP001              pOut->DrawPolyLine(aPoly);
//STRIP001              pOut->DrawLine(aPoly[0],aPoly[2]);
//STRIP001              pOut->DrawLine(aPoly[1],aPoly[3]);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }

// Geht z.Zt. nur wenn das Obj schon wenigstens einmal gepaintet wurde
// Denn dann ist der MtfAnimator initiallisiert
//STRIP001 void SdrTextObj::StartTextAnimation(OutputDevice* pOutDev, const Point& rOffset, long nExtraData)
//STRIP001 {
//STRIP001  if (GetTextAniKind()!=SDRTEXTANI_NONE && ImpGetMtfAnimator()!=NULL) {
//STRIP001      ImpSdrMtfAnimator* pAnimator=ImpForceMtfAnimator();
//STRIP001      pAnimator->Start(*pOutDev,rOffset,nExtraData);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrTextObj::StopTextAnimation(OutputDevice* pOutDev, long nExtraData)
//STRIP001 {
//STRIP001  if (pPlusData!=NULL && pPlusData->pAnimator!=NULL) {
//STRIP001      ImpSdrMtfAnimator* pAnimator=pPlusData->pAnimator;
//STRIP001      for (ULONG nInfoNum=pAnimator->GetInfoCount(); nInfoNum>0;) {
//STRIP001          nInfoNum--;
//STRIP001          ImpMtfAnimationInfo* pInfo=pAnimator->GetInfo(nInfoNum);
//STRIP001          if (pInfo->nExtraData==nExtraData &&
//STRIP001              (pOutDev==NULL || pInfo->pOutDev==pOutDev)) pAnimator->RemoveInfo(nInfoNum);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrTextObj::ImpPaintAnimatedText(OutputDevice& rOut, const Point& rOffset,
//STRIP001  SdrOutliner& rOutliner, const Rectangle& rAnchorRect, const Rectangle& rPaintRect,
//STRIP001  const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  SdrTextAniKind eAniKind = GetTextAniKind();
//STRIP001  FASTBOOL bBlink = eAniKind == SDRTEXTANI_BLINK;
//STRIP001  const SfxItemSet& rSet = GetItemSet();
//STRIP001  SdrTextAniDirection eDirection = ((SdrTextAniDirectionItem&)(rSet.Get(SDRATTR_TEXT_ANIDIRECTION))).GetValue();
//STRIP001  ImpSdrMtfAnimator* pAnimator = ((SdrTextObj*)this)->ImpForceMtfAnimator();
//STRIP001  pAnimator->SetAnimationNotifyHdl(LINK(this,SdrTextObj,ImpAnimationHdl));
//STRIP001
//STRIP001  // erstmal checken, ob nicht schon laeuft
//STRIP001  ImpMtfAnimationInfo* pRunningInfo = NULL;
//STRIP001
//STRIP001  for(ULONG nInfoNum = pAnimator->GetInfoCount(); nInfoNum>0 && pRunningInfo==NULL;) {
//STRIP001      nInfoNum--;
//STRIP001      ImpMtfAnimationInfo* pInfo=pAnimator->GetInfo(nInfoNum);
//STRIP001      if (pInfo->pPageView==rInfoRec.pPV && pInfo->pOutDev==&rOut) {
//STRIP001          if (!pInfo->bBackSaved) pRunningInfo=pInfo;
//STRIP001          else {
//STRIP001              MapMode aMap1(pInfo->aBackground.GetMapMode());
//STRIP001              MapMode aMap2(rOut.GetMapMode());
//STRIP001              if (aMap1.GetMapUnit()==aMap2.GetMapUnit() &&
//STRIP001                  aMap1.GetScaleX()==aMap2.GetScaleX() &&
//STRIP001                  aMap1.GetScaleY()==aMap2.GetScaleY()) pRunningInfo=pInfo;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (pRunningInfo!=NULL) {
//STRIP001      if (pRunningInfo->bBackSaved) {
//STRIP001          // Teilinvalidierung des Hintergrunds
//STRIP001          Rectangle aClipRect(rInfoRec.aDirtyRect);
//STRIP001          if (rOut.GetMapMode().GetMapUnit()==MAP_TWIP) {
//STRIP001              HACK(Bei Teilinvalidierung von Laufschrift im Writer 1 Pixel korregieren);
//STRIP001              Size a1Pix(rOut.PixelToLogic(Size(1,1)));
//STRIP001              aClipRect.Top()+=a1Pix.Width();
//STRIP001              aClipRect.Left()+=a1Pix.Height();
//STRIP001              aClipRect.Right()-=a1Pix.Width();
//STRIP001              aClipRect.Bottom()-=a1Pix.Height();
//STRIP001          }
//STRIP001          Region aRegion(aClipRect);
//STRIP001          pRunningInfo->SaveBackground(*pAnimator,&aRegion);
//STRIP001          pRunningInfo->Paint(*pAnimator,rOut);
//STRIP001      }
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  pAnimator->SetAttributes(rSet);
//STRIP001
//STRIP001  Point aRotateRef(rAnchorRect.TopLeft());
//STRIP001  // Die Drehreferenz ist bei allen Rechtecken jeweils das eigene TopLeft()
//STRIP001  // (rPaintRect,rAnchorRect). Ich verschiebe nun aPaintRect so, dass fuer
//STRIP001  // beide die Drehreferenz rAnchorRect.TopLeft() gilt.
//STRIP001  Rectangle aPaintRect(rPaintRect);
//STRIP001
//STRIP001  // #103516# Do this calculatin for vertical text, too.
//STRIP001  if((SDRTEXTHORZADJUST_BLOCK == GetTextHorizontalAdjust() || SDRTEXTVERTADJUST_BLOCK == GetTextVerticalAdjust())
//STRIP001      && SDRTEXTFIT_NONE != GetFitToSize())
//STRIP001  {
//STRIP001      // Bei den Default-Textrahmen muss ich erstmal die laengste Zeile berechnen
//STRIP001      // Das gibt allerdings Probleme bei Absatzformatierungen Center, Rechts
//STRIP001      // und evtl. auch bei Blocksatz.
//STRIP001      Size aSiz(rOutliner.CalcTextSize());
//STRIP001      aPaintRect.Right()=aPaintRect.Left()+aSiz.Width();
//STRIP001      aPaintRect.Bottom()=aPaintRect.Top()+aSiz.Height();
//STRIP001  }
//STRIP001
//STRIP001  // PaintRect auf's AnchorRect ausrichten (den selben Drehpunkt fuer alle)
//STRIP001  if (aGeo.nDrehWink!=0) {
//STRIP001      if (aPaintRect.TopLeft()!=aRotateRef) {
//STRIP001          Point aTmpPt(aPaintRect.TopLeft());
//STRIP001          RotatePoint(aTmpPt,aRotateRef,-aGeo.nSin,aGeo.nCos); // -sin=zurueckdrehen
//STRIP001          aTmpPt-=aPaintRect.TopLeft();
//STRIP001          aPaintRect.Move(aTmpPt.X(),aTmpPt.Y());
//STRIP001      }
//STRIP001  }
//STRIP001  Rectangle aScrollFrameRect(aPaintRect);
//STRIP001  if (!bBlink) {
//STRIP001      if (eDirection==SDRTEXTANI_LEFT || eDirection==SDRTEXTANI_RIGHT) {
//STRIP001          aScrollFrameRect.Left()=rAnchorRect.Left();
//STRIP001          aScrollFrameRect.Right()=rAnchorRect.Right();
//STRIP001      }
//STRIP001      if (eDirection==SDRTEXTANI_UP || eDirection==SDRTEXTANI_DOWN) {
//STRIP001          aScrollFrameRect.Top()=rAnchorRect.Top();
//STRIP001          aScrollFrameRect.Bottom()=rAnchorRect.Bottom();
//STRIP001      }
//STRIP001  }
//STRIP001  Rectangle aAnimationBoundRect(aScrollFrameRect);
//STRIP001  if (aGeo.nDrehWink!=0) {
//STRIP001      // Das aAnimationBoundRect ist das BoundRect des gedrehten aScrollFrameRect.
//STRIP001      // Fuer diesen Bereich muss spaeter der Hintergrund gesichert werden, ...
//STRIP001      Polygon aPoly(aAnimationBoundRect);
//STRIP001      RotatePoly(aPoly,aRotateRef,aGeo.nSin,aGeo.nCos);
//STRIP001      aAnimationBoundRect=aPoly.GetBoundRect();
//STRIP001  }
//STRIP001  // ClipRegion am pAnimator setzen, falls erforderlich
//STRIP001  if (bBlink) pAnimator->SetClipRegion(); // kein Clipping erforderlich
//STRIP001  else {
//STRIP001      if (aGeo.nDrehWink==0) pAnimator->SetClipRegion(aScrollFrameRect); // RectClipping
//STRIP001      else {
//STRIP001          Polygon aPoly(aScrollFrameRect);
//STRIP001          RotatePoly(aPoly,aRotateRef,aGeo.nSin,aGeo.nCos);
//STRIP001          pAnimator->SetClipRegion(aPoly); // PolyClipping
//STRIP001      }
//STRIP001  }
//STRIP001  Rectangle aAnimationBoundRectPlus(aAnimationBoundRect); // Das ist das AnimationBoundRect +PvOfs
//STRIP001  aAnimationBoundRectPlus.Move(rOffset.X(),rOffset.Y());
//STRIP001
//STRIP001  { // Nun das Metafile erzeugen
//STRIP001      GDIMetaFile* pMtf=new GDIMetaFile;
//STRIP001      VirtualDevice aBlackHole;
//STRIP001      aBlackHole.EnableOutput(FALSE);
//STRIP001      pMtf->Record(&aBlackHole);
//STRIP001
//STRIP001      //AW vertical writing
//STRIP001      // For the outliner::Draw method which takes a start position
//STRIP001      // the upper right position must be offered for vertical writing.
//STRIP001      // Update: MT changed the method to take the same position as normal,
//STRIP001      // so I changed this back.
//STRIP001      Point aPaintPos = rPaintRect.TopLeft();
//STRIP001
//STRIP001      //aPaintPos-=aAnimationBoundRect.TopLeft();
//STRIP001      // Die RedLines der Online-Rechtschreibpruefung werden via DrawPixel
//STRIP001      // gemalt. Das ist bei Laufschrift, besonders unter OS/2, viel zu langsam.
//STRIP001      // Deshalb schalte ich diese hier bei der Metafileaufzeichnung temporaer ab.
//STRIP001      ULONG nStat0=rOutliner.GetControlWord();
//STRIP001      rOutliner.SetControlWord(nStat0|EE_CNTRL_NOREDLINES);
//STRIP001      rOutliner.Draw(&aBlackHole,aPaintPos,(short)(aGeo.nDrehWink/10));
//STRIP001      rOutliner.SetControlWord(nStat0);
//STRIP001      pMtf->Stop();
//STRIP001      pMtf->WindStart();
//STRIP001      pAnimator->SetGDIMetaFile(pMtf);
//STRIP001  }
//STRIP001  pAnimator->SetOutputRect(aAnimationBoundRect);
//STRIP001  pAnimator->SetScrollFrameRect(aScrollFrameRect);
//STRIP001  pAnimator->SetMtfFrameRect(aPaintRect);
//STRIP001  pAnimator->SetRotateRef(aRotateRef);
//STRIP001  pAnimator->SetRotateAngle(aGeo.nDrehWink);
//STRIP001
//STRIP001  ImpMtfAnimationInfo* pInfo=pAnimator->Start(rOut,rOffset);
//STRIP001  // Nun noch die PageView setzen (fuer Xor)
//STRIP001  pInfo->pPageView=rInfoRec.pPV;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrTextObj::RecalcBoundRect()
//STRIP001 {
//STRIP001  aOutRect=GetSnapRect();
//STRIP001 }

/*N*/ void SdrTextObj::ImpAddTextToBoundRect()
/*N*/ {
/*N*/   if (pOutlinerParaObject!=NULL) {
/*N*/       if (IsContourTextFrame()) return;
/*N*/       if (IsFontwork()) {
/*N*/           if (pModel!=NULL) {
/*N*/               VirtualDevice aVD;
/*N*/               ExtOutputDevice aXOut(&aVD);
/*N*/               SdrOutliner& rOutl=ImpGetDrawOutliner();
/*N*/               rOutl.SetUpdateMode(TRUE);
/*N*/               ImpTextPortionHandler aTPHandler(rOutl,*this);
/*N*/
/*N*/               aXOut.SetTextAttr(GetItemSet());
/*N*/
/*N*/               aTPHandler.DrawTextToPath(aXOut,FALSE);
/*N*/               if (pFormTextBoundRect==NULL) pFormTextBoundRect=new Rectangle;
/*N*/               *pFormTextBoundRect=aTPHandler.GetFormTextBoundRect();
/*N*/               aOutRect.Union(*pFormTextBoundRect);
/*N*/           }
/*N*/       } else { // Ansonsten Text im Zeichenobjekt zentriert
/*N*/           if (pFormTextBoundRect!=NULL) {
/*?*/               delete pFormTextBoundRect;
/*?*/               pFormTextBoundRect=NULL;
/*N*/           }
/*N*/           FASTBOOL bCheckText=TRUE;
/*N*/           if (bTextFrame) {
/*N*/               bCheckText=GetTextLeftDistance ()<0 ||
/*N*/                          GetTextRightDistance()<0 ||
/*N*/                          GetTextUpperDistance()<0 ||
/*N*/                          GetTextLowerDistance()<0 ||
/*N*/                          (GetEckenradius()>0 && aGeo.nDrehWink!=0);
/*N*/           }
/*N*/           if (bCheckText) {
/*N*/               SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*N*/               Rectangle aTextRect;
/*N*/               Rectangle aAnchorRect;
/*N*/               TakeTextRect(rOutliner,aTextRect,TRUE,&aAnchorRect); // EditText ignorieren!
/*N*/               SdrFitToSizeType eFit=GetFitToSize();
/*N*/               FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
/*N*/               if (bFitToSize) aTextRect=aAnchorRect;
/*N*/               rOutliner.Clear();
/*N*/               if (aGeo.nDrehWink!=0) {
/*N*/                   Polygon aPol(aTextRect);
/*N*/                   if (aGeo.nDrehWink!=0) RotatePoly(aPol,aTextRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/                   aOutRect.Union(aPol.GetBoundRect());
/*N*/               } else {
/*N*/                   aOutRect.Union(aTextRect);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ SdrObject* SdrTextObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   if (!bTextFrame && pOutlinerParaObject==NULL) return NULL;
/*N*/   if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
/*N*/   INT32 nMyTol=nTol;
/*N*/   FASTBOOL bFontwork=IsFontwork();
/*N*/   SdrFitToSizeType eFit=GetFitToSize();
/*N*/   FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
/*N*/   Rectangle aR(aRect);
/*N*/   Rectangle aAnchor(aR);
/*N*/   Rectangle aTextRect(aR);
/*N*/   SdrOutliner* pOutliner = NULL;
/*N*/   pOutliner = &pModel->GetHitTestOutliner();
/*N*/
/*N*/   if (bFontwork) {
/*?*/       if (pFormTextBoundRect!=NULL) aR=*pFormTextBoundRect;
/*?*/       else aR=GetBoundRect();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       TakeTextRect( *pOutliner, aTextRect, FALSE, &aAnchor, FALSE ); // EditText nicht mehr ignorieren! TRUE); // EditText ignorieren!
/*N*/
/*N*/       if (bFitToSize)
/*?*/           aR=aAnchor;
/*N*/       else
/*N*/           aR=aTextRect;
/*N*/   }
/*N*/   if (aR.GetWidth()-1>short(nTol) && aR.GetHeight()-1>short(nTol)) nMyTol=0; // Keine Toleranz noetig hier
/*N*/   if (nMyTol!=0) {
/*?*/       aR.Left  ()-=nMyTol;
/*?*/       aR.Top   ()-=nMyTol;
/*?*/       aR.Right ()+=nMyTol;
/*?*/       aR.Bottom()+=nMyTol;
/*N*/   }
/*N*/   FASTBOOL bRet=FALSE;
/*N*/
/*N*/   if(bFontwork)
/*N*/   {
/*N*/       bRet = aR.IsInside(rPnt);
/*N*/
/*N*/       // #105130# Include aRect here in measurements to be able to hit a
/*N*/       // fontwork object on its border
/*N*/       if(!bRet)
/*N*/       {
/*N*/           const Rectangle aSnapRect = GetSnapRect();
/*N*/
/*N*/           if( (rPnt.X() >= aSnapRect.Left() - nTol && rPnt.X() <= aSnapRect.Left() + nTol)
/*N*/            || (rPnt.X() >= aSnapRect.Right() - nTol && rPnt.X() <= aSnapRect.Right() + nTol)
/*N*/            || (rPnt.Y() >= aSnapRect.Top() - nTol && rPnt.Y() <= aSnapRect.Top() + nTol)
/*N*/            || (rPnt.Y() >= aSnapRect.Bottom() - nTol && rPnt.Y() <= aSnapRect.Bottom() + nTol))
/*N*/           {
/*N*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if (aGeo.nDrehWink!=0) {
/*N*/           Polygon aPol(aR);
/*N*/           RotatePoly(aPol,aR.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/           bRet=IsPointInsidePoly(aPol,rPnt);
/*N*/       } else {
/*N*/           bRet=aR.IsInside(rPnt);
/*N*/       }
/*N*/       if (bRet) { // und nun noch checken, ob wirklich Buchstaben getroffen sind
/*N*/           // Featurewunsch zur 4.0
/*N*/           // Zunaechst meine Dok-Koordinaten in EE-Dok-Koordinaten umwandeln.
/*N*/           Point aPt(rPnt); aPt-=aR.TopLeft();
/*N*/           if (bFitToSize) { // #38214#: FitToSize berueksichtigen
/*?*/               Fraction aX(aTextRect.GetWidth()-1,aAnchor.GetWidth()-1);
/*?*/               Fraction aY(aTextRect.GetHeight()-1,aAnchor.GetHeight()-1);
/*?*/               ResizePoint(aPt,Point(),aX,aY);
/*N*/           }
/*N*/           if (aGeo.nDrehWink!=0) RotatePoint(aPt,Point(),-aGeo.nSin,aGeo.nCos); // -sin fuer Unrotate
/*N*/           // Und nun im EE-Dok auf Buchstabensuche gehen
/*N*/           long nHitTol = 2000;
/*N*/           OutputDevice* pRef = pOutliner->GetRefDevice();
/*N*/           if( pRef )
/*N*/               nHitTol = pRef->LogicToLogic( nHitTol, MAP_100TH_MM, pRef->GetMapMode().GetMapUnit() );
/*N*/
/*N*/           bRet = pOutliner->IsTextPos( aPt, (sal_uInt16)nHitTol );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bRet ? (SdrObject*)this : NULL;
/*N*/ }

//STRIP001 void SdrTextObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001
//STRIP001  switch(eTextKind)
//STRIP001  {
//STRIP001      case OBJ_OUTLINETEXT:
//STRIP001      {
//STRIP001          aStr = ImpGetResStr(STR_ObjNameSingulOUTLINETEXT);
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case OBJ_TITLETEXT  :
//STRIP001      {
//STRIP001          aStr = ImpGetResStr(STR_ObjNameSingulTITLETEXT);
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      default:
//STRIP001      {
//STRIP001          if(IsLinkedText())
//STRIP001              aStr = ImpGetResStr(STR_ObjNameSingulTEXTLNK);
//STRIP001          else
//STRIP001              aStr = ImpGetResStr(STR_ObjNameSingulTEXT);
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(pOutlinerParaObject && eTextKind != OBJ_OUTLINETEXT)
//STRIP001  {
//STRIP001      // Macht bei OUTLINETEXT wohl derzeit noch etwas Probleme
//STRIP001      XubString aStr2(pOutlinerParaObject->GetTextObject().GetText(0));
//STRIP001      aStr2.EraseLeadingChars();
//STRIP001
//STRIP001      // #69446# avoid non expanded text portions in object name
//STRIP001      // (second condition is new)
//STRIP001      if(aStr2.Len() && aStr2.Search(sal_Unicode(255)) == STRING_NOTFOUND)
//STRIP001      {
//STRIP001          // #76681# space between ResStr and content text
//STRIP001          aStr += sal_Unicode(' ');
//STRIP001
//STRIP001          aStr += sal_Unicode('\'');
//STRIP001
//STRIP001          if(aStr2.Len() > 10)
//STRIP001          {
//STRIP001              aStr2.Erase(8);
//STRIP001              aStr2.AppendAscii("...", 3);
//STRIP001          }
//STRIP001
//STRIP001          aStr += aStr2;
//STRIP001          aStr += sal_Unicode('\'');
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rName = aStr;
//STRIP001
//STRIP001  String aName( GetName() );
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001
//STRIP001 }

//STRIP001 void SdrTextObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  switch (eTextKind) {
//STRIP001      case OBJ_OUTLINETEXT: rName=ImpGetResStr(STR_ObjNamePluralOUTLINETEXT); break;
//STRIP001      case OBJ_TITLETEXT  : rName=ImpGetResStr(STR_ObjNamePluralTITLETEXT);   break;
//STRIP001      default: {
//STRIP001          if (IsLinkedText()) {
//STRIP001              rName=ImpGetResStr(STR_ObjNamePluralTEXTLNK);
//STRIP001          } else {
//STRIP001              rName=ImpGetResStr(STR_ObjNamePluralTEXT);
//STRIP001          }
//STRIP001      } break;
//STRIP001  } // switch
//STRIP001 }

/*N*/ void SdrTextObj::operator=(const SdrObject& rObj)
/*N*/ {
/*N*/   SdrAttrObj::operator=(rObj);
/*N*/   const SdrTextObj* pText=PTR_CAST(SdrTextObj,&rObj);
/*N*/   if (pText!=NULL) {
/*N*/       aRect     =pText->aRect;
/*N*/       aGeo      =pText->aGeo;
/*N*/       eTextKind =pText->eTextKind;
/*N*/       bTextFrame=pText->bTextFrame;
/*N*/       aTextSize=pText->aTextSize;
/*N*/       bTextSizeDirty=pText->bTextSizeDirty;
/*N*/
/*N*/       // #101776# Not all of the necessary parameters were copied yet.
/*N*/       bNoShear = pText->bNoShear;
/*N*/       bNoRotate = pText->bNoRotate;
/*N*/       bNoMirror = pText->bNoMirror;
/*N*/       bDisableAutoWidthOnDragging = pText->bDisableAutoWidthOnDragging;
/*N*/
/*N*/       if (pOutlinerParaObject!=NULL) delete pOutlinerParaObject;
/*N*/       if (pText->HasText()) {
/*N*/           const Outliner* pEO=pText->pEdtOutl;
/*N*/           if (pEO!=NULL) {
/*?*/               pOutlinerParaObject=pEO->CreateParaObject();
/*N*/           } else {
/*N*/               pOutlinerParaObject=pText->pOutlinerParaObject->Clone();
/*N*/           }
/*N*/       } else {
/*N*/           pOutlinerParaObject=NULL;
/*N*/       }
/*N*/       ImpSetTextStyleSheetListeners();
/*N*/   }
/*N*/ }

//STRIP001 void SdrTextObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  Polygon aPol(aRect);
//STRIP001  if (aGeo.nShearWink!=0) ShearPoly(aPol,aRect.TopLeft(),aGeo.nTan);
//STRIP001  if (aGeo.nDrehWink!=0) RotatePoly(aPol,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001  rPoly=XPolyPolygon(XPolygon(aPol));
//STRIP001 }

/*N*/ void SdrTextObj::TakeContour(XPolyPolygon& rPoly) const
/*N*/ {
/*N*/   SdrAttrObj::TakeContour(rPoly);
/*N*/
/*N*/   // #80328# using Clone()-Paint() strategy inside TakeContour() leaves a destroyed
/*N*/   // SdrObject as pointer in DrawOutliner. Set *this again in fetching the outliner
/*N*/   // in every case
/*N*/   SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*N*/
/*N*/   // und nun noch ggf. das BoundRect des Textes dazu
/*N*/   if (pOutlinerParaObject!=NULL && !IsFontwork() && !IsContourTextFrame()) {
/*?*/       Rectangle aAnchor;
/*?*/       Rectangle aR;
/*?*/       TakeTextRect(rOutliner,aR,FALSE,&aAnchor);
/*?*/       rOutliner.Clear();
/*?*/       SdrFitToSizeType eFit=GetFitToSize();
/*?*/       FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
/*?*/       if (bFitToSize) aR=aAnchor;
/*?*/       Polygon aPol(aR);
/*?*/       if (aGeo.nDrehWink!=0) RotatePoly(aPol,aR.TopLeft(),aGeo.nSin,aGeo.nCos);
/*?*/       rPoly.Insert(XPolygon(aPol));
/*N*/   }
/*N*/ }

//STRIP001 void SdrTextObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

/*N*/ void SdrTextObj::RecalcSnapRect()
/*N*/ {
/*N*/   if (aGeo.nDrehWink!=0 || aGeo.nShearWink!=0) {
/*N*/       Polygon aPol(aRect);
/*N*/       if (aGeo.nShearWink!=0) ShearPoly(aPol,aRect.TopLeft(),aGeo.nTan);
/*N*/       if (aGeo.nDrehWink!=0) RotatePoly(aPol,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/       maSnapRect=aPol.GetBoundRect();
/*N*/   } else {
/*N*/       maSnapRect=aRect;
/*N*/   }
/*N*/ }

//STRIP001 USHORT SdrTextObj::GetSnapPointCount() const
//STRIP001 {
//STRIP001  return 4;
//STRIP001 }

//STRIP001 Point SdrTextObj::GetSnapPoint(USHORT i) const
//STRIP001 {
//STRIP001  Point aP;
//STRIP001  switch (i) {
//STRIP001      case 0: aP=aRect.TopLeft(); break;
//STRIP001      case 1: aP=aRect.TopRight(); break;
//STRIP001      case 2: aP=aRect.BottomLeft(); break;
//STRIP001      case 3: aP=aRect.BottomRight(); break;
//STRIP001      default: aP=aRect.Center(); break;
//STRIP001  }
//STRIP001  if (aGeo.nShearWink!=0) ShearPoint(aP,aRect.TopLeft(),aGeo.nTan);
//STRIP001  if (aGeo.nDrehWink!=0) RotatePoint(aP,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001  return aP;
//STRIP001 }

/*N*/ void SdrTextObj::ImpCheckMasterCachable()
/*N*/ {
/*N*/   bNotMasterCachable=FALSE;
/*N*/   if (!bNotVisibleAsMaster && pOutlinerParaObject!=NULL && pOutlinerParaObject->IsEditDoc()) {
/*N*/       const EditTextObject& rText=pOutlinerParaObject->GetTextObject();
/*N*/       bNotMasterCachable=rText.HasField(SvxPageField::StaticType());
/*N*/   }
/*N*/ }

// #101029#: Extracted from ImpGetDrawOutliner()
/*N*/ void SdrTextObj::ImpInitDrawOutliner( SdrOutliner& rOutl ) const
/*N*/ {
/*N*/   rOutl.SetUpdateMode(FALSE);
/*N*/   USHORT nOutlinerMode = OUTLINERMODE_OUTLINEOBJECT;
/*N*/   if ( !IsOutlText() )
/*N*/       nOutlinerMode = OUTLINERMODE_TEXTOBJECT;
/*N*/   rOutl.Init( nOutlinerMode );
/*N*/
/*N*/   rOutl.SetGlobalCharStretching(100,100);
/*N*/   ULONG nStat=rOutl.GetControlWord();
/*N*/   nStat&=~(EE_CNTRL_STRETCHING|EE_CNTRL_AUTOPAGESIZE);
/*N*/   rOutl.SetControlWord(nStat);
/*N*/   Size aNullSize;
/*N*/   Size aMaxSize(100000,100000);
/*N*/   rOutl.SetMinAutoPaperSize(aNullSize);
/*N*/   rOutl.SetMaxAutoPaperSize(aMaxSize);
/*N*/   rOutl.SetPaperSize(aMaxSize);
/*N*/   rOutl.ClearPolygon();
/*N*/ }

/*N*/ SdrOutliner& SdrTextObj::ImpGetDrawOutliner() const
/*N*/ {
/*N*/   SdrOutliner& rOutl=pModel->GetDrawOutliner(this);
/*N*/
/*N*/     // #101029#: Code extracted to ImpInitDrawOutliner()
/*N*/     ImpInitDrawOutliner( rOutl );
/*N*/
/*N*/   return rOutl;
/*N*/ }

// #101029#: Extracted from Paint()
//STRIP001 void SdrTextObj::ImpSetupDrawOutlinerForPaint( FASTBOOL      bContourFrame,
//STRIP001                                                SdrOutliner&  rOutliner,
//STRIP001                                                Rectangle&        rTextRect,
//STRIP001                                                Rectangle&        rAnchorRect,
//STRIP001                                                Rectangle&        rPaintRect,
//STRIP001                                                Fraction&         rFitXKorreg ) const
//STRIP001 {
//STRIP001     if (!bContourFrame)
//STRIP001     {
//STRIP001         // FitToSize erstmal nicht mit ContourFrame
//STRIP001         SdrFitToSizeType eFit=GetFitToSize();
//STRIP001         if (eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES)
//STRIP001         {
//STRIP001             ULONG nStat=rOutliner.GetControlWord();
//STRIP001             nStat|=EE_CNTRL_STRETCHING|EE_CNTRL_AUTOPAGESIZE;
//STRIP001             rOutliner.SetControlWord(nStat);
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     TakeTextRect(rOutliner, rTextRect, FALSE, &rAnchorRect);
//STRIP001     rPaintRect = rTextRect;
//STRIP001
//STRIP001     if (!bContourFrame)
//STRIP001     {
//STRIP001         // FitToSize erstmal nicht mit ContourFrame
//STRIP001         SdrFitToSizeType eFit=GetFitToSize();
//STRIP001         if (eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES)
//STRIP001         {
//STRIP001             ImpSetCharStretching(rOutliner,rTextRect,rAnchorRect,rFitXKorreg);
//STRIP001             rPaintRect=rAnchorRect;
//STRIP001         }
//STRIP001     }
//STRIP001 }

/*N*/ void SdrTextObj::SetupOutlinerFormatting( SdrOutliner& rOutl, Rectangle& rPaintRect ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     ImpInitDrawOutliner( rOutl );
//STRIP001     UpdateOutlinerFormatting( rOutl, rPaintRect );
//STRIP001 }
//STRIP001
//STRIP001 void SdrTextObj::UpdateOutlinerFormatting( SdrOutliner& rOutl, Rectangle& rPaintRect ) const
//STRIP001 {
//STRIP001     Rectangle aTextRect;
//STRIP001     Rectangle aAnchorRect;
//STRIP001     Fraction aFitXKorreg(1,1);
//STRIP001
//STRIP001     FASTBOOL bContourFrame=IsContourTextFrame();
//STRIP001
//STRIP001     ImpSetupDrawOutlinerForPaint( bContourFrame, rOutl, aTextRect, aAnchorRect, rPaintRect, aFitXKorreg );
//STRIP001
//STRIP001     if( GetModel() )
//STRIP001     {
//STRIP001      MapMode aMapMode(GetModel()->GetScaleUnit(), Point(0,0),
//STRIP001                          GetModel()->GetScaleFraction(),
//STRIP001                          GetModel()->GetScaleFraction());
//STRIP001      rOutl.SetRefMapMode(aMapMode);
//STRIP001  }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrTextObj::PreSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrAttrObj::PreSave();
/*N*/
/*N*/   // Prepare OutlinerParaObjects for storing
/*N*/   OutlinerParaObject* pParaObj = GetOutlinerParaObject();
/*N*/   if(pParaObj && GetModel())
/*N*/       pParaObj->PrepareStore((SfxStyleSheetPool*)GetModel()->GetStyleSheetPool());
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ OutlinerParaObject* SdrTextObj::GetOutlinerParaObject() const
/*N*/ {
/*N*/   return pOutlinerParaObject;
/*N*/ }

/*N*/ void SdrTextObj::NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject)
/*N*/ {
/*N*/   if( pModel )
/*N*/   {
/*N*/       // Update HitTestOutliner
/*N*/       const SdrTextObj* pTestObj = pModel->GetHitTestOutliner().GetTextObj();
/*N*/       if( pTestObj && pTestObj->GetOutlinerParaObject() == pOutlinerParaObject )
/*?*/           pModel->GetHitTestOutliner().SetTextObj( NULL );
/*N*/   }
/*N*/
/*N*/   if (pOutlinerParaObject!=NULL) {
/*N*/       delete pOutlinerParaObject;
/*N*/       pOutlinerParaObject=NULL;
/*N*/   }
/*N*/   pOutlinerParaObject=pTextObject;
/*N*/
/*N*/   if( pOutlinerParaObject )
/*N*/   {
/*N*/       ImpForceItemSet();
/*N*/       mpObjectItemSet->Put( SvxWritingModeItem( pOutlinerParaObject->IsVertical() ? ::com::sun::star::text::WritingMode_TB_RL : ::com::sun::star::text::WritingMode_LR_TB ) );
/*N*/   }
/*N*/
/*N*/   SetTextSizeDirty();
/*N*/   bPortionInfoChecked=FALSE;
/*N*/   if (IsTextFrame() && (IsAutoGrowHeight() || IsAutoGrowWidth())) { // Textrahmen anpassen!
/*N*/       NbcAdjustTextFrameWidthAndHeight();
/*N*/   }
/*N*/   if (!IsTextFrame()) {
/*N*/       // Das SnapRect behaelt seine Groesse bei
/*N*/       bBoundRectDirty=TRUE;
/*N*/       SetRectsDirty(TRUE);
/*N*/   }
/*N*/   ImpSetTextStyleSheetListeners();
/*N*/   ImpCheckMasterCachable();
/*N*/ }

/*N*/ void SdrTextObj::NbcReformatText()
/*N*/ {
/*N*/   if (pOutlinerParaObject!=NULL) {
/*N*/       bPortionInfoChecked=FALSE;
/*N*/       pOutlinerParaObject->ClearPortionInfo();
/*N*/       if (bTextFrame) {
/*N*/           NbcAdjustTextFrameWidthAndHeight();
/*N*/       } else {
/*N*/           // Das SnapRect behaelt seine Groesse bei
/*N*/           bBoundRectDirty=TRUE;
/*N*/           SetRectsDirty(TRUE);
/*N*/       }
/*N*/       SetTextSizeDirty();
/*N*/   }
/*N*/ }

/*N*/ void SdrTextObj::ReformatText()
/*N*/ {
/*N*/   if (pOutlinerParaObject!=NULL) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcReformatText();
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       if (GetBoundRect()!=aBoundRect0) {
/*N*/           SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrTextObj::RestartAnimation(SdrPageView* pPageView) const
/*N*/ {
///*N*/     FASTBOOL bAnimated=GetTextAniKind()!=SDRTEXTANI_NONE;
///*N*/     if (bAnimated) {
///*N*/         ImpSdrMtfAnimator* pAnimator=((SdrTextObj*)this)->ImpGetMtfAnimator();
///*N*/         if (pAnimator!=NULL) {
///*?*/             if (pPageView==NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
////STRIP001 /*?*/              pAnimator->Stop();
///*?*/             } else {
///*?*/                 for (ULONG nInfoNum=pAnimator->GetInfoCount(); nInfoNum>0;) {
///*?*/                     nInfoNum--;
///*?*/                     ImpMtfAnimationInfo* pInfo=pAnimator->GetInfo(nInfoNum);
///*?*/                     if (pInfo->pPageView==pPageView) {
///*?*/                         pAnimator->RemoveInfo(nInfoNum);
///*?*/                     }
///*?*/                 }
///*?*/             }
///*N*/         }
///*N*/     }
/*N*/ }

//STRIP001 SdrObjGeoData* SdrTextObj::NewGeoData() const
//STRIP001 {
//STRIP001  return new SdrTextObjGeoData;
//STRIP001 }

/*N*/ void SdrTextObj::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {
/*N*/   SdrAttrObj::SaveGeoData(rGeo);
/*N*/   SdrTextObjGeoData& rTGeo=(SdrTextObjGeoData&)rGeo;
/*N*/   rTGeo.aRect  =aRect;
/*N*/   rTGeo.aGeo   =aGeo;
/*N*/ }

/*N*/ void SdrTextObj::RestGeoData(const SdrObjGeoData& rGeo)
/*N*/ { // RectsDirty wird von SdrObject gerufen
/*N*/   SdrAttrObj::RestGeoData(rGeo);
/*N*/   SdrTextObjGeoData& rTGeo=(SdrTextObjGeoData&)rGeo;
/*N*/   aRect  =rTGeo.aRect;
/*N*/   aGeo   =rTGeo.aGeo;
/*N*/   SetTextSizeDirty();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// I/O
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrTextObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrAttrObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrTextObj");
/*N*/ #endif
/*N*/   rOut<<BYTE(eTextKind);
/*N*/   rOut<<aRect;
/*N*/   rOut<<INT32(aGeo.nDrehWink);
/*N*/   rOut<<INT32(aGeo.nShearWink);
/*N*/
/*N*/   // Wird gerade editiert, also das ParaObject aus dem aktiven Editor verwenden
/*N*/   // Das war frueher. Jetzt wird beim Speichern sowas aehnliches wie EndTextEdit gemacht! #43095#
/*N*/   if (pEdtOutl!=NULL) {
/*?*/       // #43095#
/*?*/       OutlinerParaObject* pPara=GetEditOutlinerParaObject();
/*?*/       // casting auf nicht-const
/*?*/       ((SdrTextObj*)this)->SetOutlinerParaObject(pPara);
/*?*/
/*?*/       // #91254# put text to object and set EmptyPresObj to FALSE
/*?*/       if(pPara && IsEmptyPresObj())
/*?*/           ((SdrTextObj*)this)->SetEmptyPresObj(FALSE);
/*N*/   }
/*N*/   OutlinerParaObject* pPara=pOutlinerParaObject;
/*N*/
/*N*/   BOOL bOutlinerParaObjectValid=pPara!=NULL;
/*N*/   rOut<<bOutlinerParaObjectValid;
/*N*/
/*N*/   if (bOutlinerParaObjectValid)
/*N*/   {
/*N*/       SdrDownCompat aTextCompat(rOut,STREAM_WRITE); // Ab V11 eingepackt
/*N*/ #ifdef DBG_UTIL
/*N*/       aTextCompat.SetID("SdrTextObj(OutlinerParaObject)");
/*N*/ #endif
/*N*/       pPara->Store(rOut); // neues Store am Outliner ab SV303
/*N*/       pPara->FinishStore();
/*N*/   }
/*N*/
/*N*/   // Ab FileVersion 10 wird das TextBoundRect gestreamt
/*N*/   BOOL bFormTextBoundRectValid=pFormTextBoundRect!=NULL;
/*N*/   rOut<<bFormTextBoundRectValid;
/*N*/   if (bFormTextBoundRectValid) {
/*N*/       rOut<<*pFormTextBoundRect;
/*N*/   }
/*N*/ }

/*N*/ void SdrTextObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   if (pOutlinerParaObject!=NULL) {
/*?*/       delete pOutlinerParaObject;
/*?*/       pOutlinerParaObject=NULL;
/*N*/   }
/*N*/
/*N*/   SdrAttrObj::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrTextObj");
/*N*/ #endif
/*N*/   BYTE nTmp;
/*N*/   rIn>>nTmp;
/*N*/   eTextKind=SdrObjKind(nTmp);
/*N*/   rIn>>aRect;
/*N*/   INT32 n32;
/*N*/   rIn>>n32; aGeo.nDrehWink=n32;
/*N*/   rIn>>n32; aGeo.nShearWink=n32;
/*N*/   aGeo.RecalcSinCos();
/*N*/   aGeo.RecalcTan();
/*N*/   //rIn>>aText;
/*N*/   if (rHead.GetVersion()<=5 && IsOutlText()) { // Das war bis zu diesem Zeitpunkt nicht gespeichert
/*?*/       NbcSetAutoGrowHeight(FALSE);
/*N*/   }
/*N*/
/*N*/   BOOL bOutlinerParaObjectValid=FALSE;
/*N*/   rIn>>bOutlinerParaObjectValid;
/*N*/   if (bOutlinerParaObjectValid)
/*N*/   {
/*N*/       SfxItemPool* pOutlPool=pModel!=NULL ? &pModel->GetItemPool() : NULL;
/*N*/       if (rHead.GetVersion()>=11) {
/*N*/           SdrDownCompat aTextCompat(rIn,STREAM_READ); // ab V11 eingepackt
/*N*/ #ifdef DBG_UTIL
/*N*/           aTextCompat.SetID("SdrTextObj(OutlinerParaObject)");
/*N*/ #endif
/*N*/           pOutlinerParaObject=OutlinerParaObject::Create(rIn,pOutlPool);
/*N*/       } else {
/*N*/           pOutlinerParaObject=OutlinerParaObject::Create(rIn,pOutlPool);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( pOutlinerParaObject )
/*N*/   {
/*N*/       if( pOutlinerParaObject->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/       {
/*N*/           if( eTextKind == OBJ_TITLETEXT )
/*N*/               pOutlinerParaObject->SetOutlinerMode( OUTLINERMODE_TITLEOBJECT );
/*N*/           else if( eTextKind == OBJ_OUTLINETEXT )
/*N*/               pOutlinerParaObject->SetOutlinerMode( OUTLINERMODE_OUTLINEOBJECT );
/*N*/           else
/*N*/               pOutlinerParaObject->SetOutlinerMode( OUTLINERMODE_TEXTOBJECT );
/*N*/       }
/*N*/
/*N*/       if( pOutlinerParaObject->IsVertical() )
/*N*/       {
/*?*/           ImpForceItemSet();
/*?*/           mpObjectItemSet->Put( SvxWritingModeItem( ::com::sun::star::text::WritingMode_TB_RL ) );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (rHead.GetVersion()>=10) {
/*N*/       // Ab FileVersion 10 wird das TextBoundRect gestreamt
/*N*/       BOOL bFormTextBoundRectValid=FALSE;
/*N*/       rIn>>bFormTextBoundRectValid;
/*N*/       if (bFormTextBoundRectValid) {
/*N*/           if (pFormTextBoundRect==NULL) pFormTextBoundRect=new Rectangle;
/*N*/           rIn>>*pFormTextBoundRect;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(rHead.GetVersion() < 12 && !bTextFrame)
/*N*/   {
/*N*/       mpObjectItemSet->Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_CENTER));
/*N*/       mpObjectItemSet->Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_CENTER));
/*N*/       mpObjectItemSet->Put(SvxAdjustItem(SVX_ADJUST_CENTER));
/*N*/   }
/*N*/
/*N*/   if (bTextFrame && pOutlinerParaObject!=NULL)
/*N*/       NbcAdjustTextFrameWidthAndHeight();
/*N*/
/*N*/   if ( pOutlinerParaObject &&
/*N*/        pOutlinerParaObject->GetTextObject().GetVersion() < 500 &&
/*N*/        !pOutlinerParaObject->IsEditDoc() )
/*N*/   {
/*N*/       pOutlinerParaObject->MergeParaAttribs( GetItemSet() );
/*N*/   }
/*N*/
/*N*/   // #84529# correct gradient rotation for 5.2 and earlier
/*N*/   if(aGeo.nDrehWink != 0 && rHead.GetVersion() <= 16)
/*N*/   {
/*N*/       XFillStyle eStyle = ((const XFillStyleItem&)GetItem(XATTR_FILLSTYLE)).GetValue();
/*N*/       if(XFILL_GRADIENT == eStyle)
/*N*/       {
/*N*/           XFillGradientItem aItem = (XFillGradientItem&)GetItem(XATTR_FILLGRADIENT);
/*N*/           XGradient aGradient = aItem.GetValue();
/*N*/
/*N*/           // calc new angle. aGeo.nDrehWink is 1/100th degree, aGradient.GetAngle()
/*N*/           // is 1/10th degree. Match this.
/*N*/           sal_Int32 nNewAngle = ((aGeo.nDrehWink + (aGradient.GetAngle() * 10)) + 5) / 10;
/*N*/
/*N*/           while(nNewAngle < 0)
/*?*/               nNewAngle += 3600;
/*N*/
/*N*/           while(nNewAngle >= 3600)
/*N*/               nNewAngle -= 3600;
/*N*/
/*N*/           // create new item and set
/*N*/           aGradient.SetAngle(nNewAngle);
/*N*/           aItem.SetValue(aGradient);
/*N*/           SetItem(aItem);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ImpSetTextStyleSheetListeners();
/*N*/   SetTextSizeDirty();
/*N*/   ImpCheckMasterCachable();
/*N*/ }

//STRIP001 IMPL_LINK(SdrTextObj,ImpAnimationHdl,ImpSdrMtfAnimator*,pAnimator)
//STRIP001 {
//STRIP001  // Aehnliche Implementation am Grafikobjekt: svdograf.cxx, SdrGrafObj
//STRIP001
//STRIP001  // Wenn wir nicht mehr da sind, stoppen wir natuerlich alles
//STRIP001  // und kehren gleich zurueck
//STRIP001  if (!bInserted || pPage==NULL || pModel==NULL) {
//STRIP001      pAnimator->Stop();
//STRIP001      return 0;
//STRIP001  }
//STRIP001
//STRIP001  // Alle Extra-Data auf 0 setzen, wenn keine andere ExtraData
//STRIP001  // ausser der eigenen (1) gesetzt;
//STRIP001  // groesser als 1 bedeutet zum. beim GrafObj, dass die Animation
//STRIP001  // von aussen gestartet wurde, z.B. von der DiaShow.
//STRIP001  ULONG nInfoNum;
//STRIP001  for (nInfoNum=pAnimator->GetInfoCount(); nInfoNum>0;) {
//STRIP001      nInfoNum--;
//STRIP001      ImpMtfAnimationInfo* pInfo=pAnimator->GetInfo(nInfoNum);
//STRIP001      if (pInfo->nExtraData==1L) pInfo->nExtraData=0L;
//STRIP001  }
//STRIP001
//STRIP001  USHORT   nPageNum=pPage->GetPageNum();
//STRIP001  FASTBOOL bMaster=pPage->IsMasterPage() && !bNotVisibleAsMaster;
//STRIP001  USHORT   nLsAnz=pModel->GetListenerCount();
//STRIP001
//STRIP001  for (USHORT nLsNum=0; nLsNum<nLsAnz; nLsNum++) {
//STRIP001      SfxListener* pLs=pModel->GetListener(nLsNum);
//STRIP001      SdrObjEditView* pView=PTR_CAST(SdrObjEditView,pLs);
//STRIP001      if (pView!=NULL) {
//STRIP001          FASTBOOL bDis=!pView->IsAnimationEnabled();
//STRIP001          FASTBOOL bMrk=pView->IsObjMarked(this);
//STRIP001          FASTBOOL bEdt=pView->GetTextEditObject()==this;
//STRIP001          USHORT nPvAnz=pView->GetPageViewCount();
//STRIP001          for (USHORT nPvNum=0; nPvNum<nPvAnz; nPvNum++) {
//STRIP001              SdrPageView* pPV=pView->GetPageViewPvNum(nPvNum);
//STRIP001              SdrPage* pPg=pPV->GetPage();
//STRIP001              if (pPV->GetVisibleLayers().IsSet(nLayerID)) {
//STRIP001                  FASTBOOL bJa=pPg==pPage;
//STRIP001                  if (!bJa && bMaster && !pPg->IsMasterPage()) {
//STRIP001                      USHORT nMasterAnz=pPg->GetMasterPageCount();
//STRIP001                      for  (USHORT nMasterNum=0; nMasterNum<nMasterAnz && !bJa; nMasterNum++) {
//STRIP001                          const SdrMasterPageDescriptor& rMPD=pPg->GetMasterPageDescriptor(nMasterNum);
//STRIP001                          bJa=nPageNum==rMPD.GetPageNum() && rMPD.GetVisibleLayers().IsSet(nLayerID);
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if (bJa) {
//STRIP001                      USHORT nOutAnz=pView->GetWinCount();
//STRIP001                      for (USHORT nOutNum=0; nOutNum<nOutAnz; nOutNum++) {
//STRIP001                          OutputDevice* pOut=pView->GetWin(nOutNum);
//STRIP001                          if (pOut->GetOutDevType()==OUTDEV_WINDOW)
//STRIP001                          {
//STRIP001                              Point                   aPvOfs( pPV->GetOffset() );
//STRIP001                              ULONG                   nPos = pAnimator->FindInfo(*pOut,aPvOfs,0);
//STRIP001                              ImpMtfAnimationInfo*    pInfo = NULL;
//STRIP001                              const BOOL              bPause = ( bMrk || bEdt || bDis );
//STRIP001
//STRIP001                              if( nPos != CONTAINER_ENTRY_NOTFOUND )
//STRIP001                              {
//STRIP001                                  pInfo = pAnimator->GetInfo(nPos);
//STRIP001
//STRIP001                                  if( ( pInfo->pPageView && pInfo->pPageView != pPV ) && pInfo->nExtraData == 0L )
//STRIP001                                      pInfo = NULL;
//STRIP001                              }
//STRIP001                              else if( !bPause )
//STRIP001                              {
//STRIP001                                  // Falls kein Record gefunden, wird ein neuer erzeugt
//STRIP001                                  // Das passiert z.B., wenn das Obj auf einer MasterPage liegt
//STRIP001                                  // und diese mittels MasterPagePaintCache angezeigt wurde.
//STRIP001                                  pInfo=pAnimator->Start(*pOut,aPvOfs);
//STRIP001                              }
//STRIP001
//STRIP001                              if( pInfo )
//STRIP001                              {
//STRIP001                                  // Flag am gefundenen bzw. neuen Objekt setzen
//STRIP001                                  // ( Info soll _nicht_ geloescht werden )
//STRIP001                                  if( pInfo->nExtraData == 0L )
//STRIP001                                      pInfo->nExtraData = 1L;
//STRIP001
//STRIP001                                  pInfo->bPause = bPause;
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Alle Objekte mit nicht gesetztem Flag loeschen
//STRIP001  for (nInfoNum=pAnimator->GetInfoCount(); nInfoNum>0;) {
//STRIP001      nInfoNum--;
//STRIP001      ImpMtfAnimationInfo* pInfo=pAnimator->GetInfo(nInfoNum);
//STRIP001      if (pInfo->nExtraData==0L) {
//STRIP001          pAnimator->RemoveInfo(nInfoNum);
//STRIP001      }
//STRIP001      if (pInfo->nExtraData==1L) pInfo->nExtraData=0L;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SdrTextObj::SetTextAnimationSupervisor( OutputDevice* pDisplayDev, BOOL bObjSupervises )
//STRIP001 {
//STRIP001  ImpSdrMtfAnimator* pAnimator = ImpGetMtfAnimator();
//STRIP001
//STRIP001  if( GetTextAniKind() != SDRTEXTANI_NONE && pAnimator )
//STRIP001  {
//STRIP001      for( ULONG nInfoNum = pAnimator->GetInfoCount(); nInfoNum > 0; )
//STRIP001      {
//STRIP001          ImpMtfAnimationInfo* pInfo = pAnimator->GetInfo( --nInfoNum );
//STRIP001
//STRIP001          if( pInfo->pOutDev == pDisplayDev )
//STRIP001          {
//STRIP001              pInfo->nExtraData = ( bObjSupervises ? 1L : (long) this );
//STRIP001
//STRIP001              if( !bObjSupervises )
//STRIP001                  pInfo->bPause = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ SdrFitToSizeType SdrTextObj::GetFitToSize() const
/*N*/ {
/*N*/   SdrFitToSizeType eType = SDRTEXTFIT_NONE;
/*N*/
/*N*/   if(!IsAutoGrowWidth())
/*N*/       eType = ((SdrTextFitToSizeTypeItem&)(GetItem(SDRATTR_TEXT_FITTOSIZE))).GetValue();
/*N*/
/*N*/   return eType;
/*N*/ }

/*N*/ void SdrTextObj::ForceOutlinerParaObject()
/*N*/ {
/*N*/   if( pOutlinerParaObject == NULL )
/*N*/   {
/*?*/       USHORT nOutlMode = OUTLINERMODE_TEXTOBJECT;
/*?*/       if( IsTextFrame() && eTextKind == OBJ_OUTLINETEXT )
/*?*/           nOutlMode = OUTLINERMODE_OUTLINEOBJECT;
/*?*/
/*?*/       Outliner* pOutliner = SdrMakeOutliner( nOutlMode, pModel );
/*?*/       if( pOutliner )
/*?*/       {
/*?*/           Outliner& aDrawOutliner = pModel->GetDrawOutliner();
/*?*/           pOutliner->SetCalcFieldValueHdl( aDrawOutliner.GetCalcFieldValueHdl() );
/*?*/
/*?*/           pOutliner->SetStyleSheet( 0, GetStyleSheet());
/*?*/           OutlinerParaObject* pOutlinerParaObject = pOutliner->CreateParaObject();
/*?*/           SetOutlinerParaObject( pOutlinerParaObject );
/*?*/
/*?*/           delete pOutliner;
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrTextObj::IsVerticalWriting() const
/*N*/ {
/*N*/   // #89459#
/*N*/   if(pOutlinerParaObject)
/*N*/       return pOutlinerParaObject->IsVertical();
/*N*/   if(pEdtOutl)
/*?*/       return pEdtOutl->IsVertical();
/*N*/   return FALSE;
/*N*/ }

/*N*/ void SdrTextObj::SetVerticalWriting( BOOL bVertical )
/*N*/ {
/*N*/   ForceOutlinerParaObject();
/*N*/
/*N*/   DBG_ASSERT( pOutlinerParaObject, "SdrTextObj::SetVerticalWriting() without OutlinerParaObject!" );
/*N*/   if( pOutlinerParaObject )
/*N*/   {
/*N*/       if(pOutlinerParaObject->IsVertical() != bVertical)
/*N*/       {
/*?*/           // get item settings
/*?*/           const SfxItemSet& rSet = GetItemSet();
/*?*/           sal_Bool bAutoGrowWidth = ((SdrTextAutoGrowWidthItem&)rSet.Get(SDRATTR_TEXT_AUTOGROWWIDTH)).GetValue();
/*?*/           sal_Bool bAutoGrowHeight = ((SdrTextAutoGrowHeightItem&)rSet.Get(SDRATTR_TEXT_AUTOGROWHEIGHT)).GetValue();
/*?*/
/*?*/           // #103516# Also exchange hor/ver adjust items
/*?*/           SdrTextHorzAdjust eHorz = ((SdrTextHorzAdjustItem&)(rSet.Get(SDRATTR_TEXT_HORZADJUST))).GetValue();
/*?*/           SdrTextVertAdjust eVert = ((SdrTextVertAdjustItem&)(rSet.Get(SDRATTR_TEXT_VERTADJUST))).GetValue();
/*?*/
/*?*/           // rescue object size
/*?*/           Rectangle aObjectRect = GetSnapRect();
/*?*/
/*?*/           // prepare ItemSet to set exchanged width and height items
/*?*/           SfxItemSet aNewSet(*rSet.GetPool(),
/*?*/               SDRATTR_TEXT_AUTOGROWHEIGHT, SDRATTR_TEXT_AUTOGROWHEIGHT,
/*?*/               // #103516# Expanded item ranges to also support hor and ver adjust.
/*?*/               SDRATTR_TEXT_VERTADJUST, SDRATTR_TEXT_VERTADJUST,
/*?*/               SDRATTR_TEXT_AUTOGROWWIDTH, SDRATTR_TEXT_HORZADJUST,
/*?*/               0, 0);
/*?*/
/*?*/           aNewSet.Put(rSet);
/*?*/           aNewSet.Put(SdrTextAutoGrowWidthItem(bAutoGrowHeight));
/*?*/           aNewSet.Put(SdrTextAutoGrowHeightItem(bAutoGrowWidth));
/*?*/
/*?*/           // #103516# Exchange horz and vert adjusts
/*?*/           switch(eVert)
/*?*/           {
/*?*/               case SDRTEXTVERTADJUST_TOP: aNewSet.Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT)); break;
/*?*/               case SDRTEXTVERTADJUST_CENTER: aNewSet.Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_CENTER)); break;
/*?*/               case SDRTEXTVERTADJUST_BOTTOM: aNewSet.Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_LEFT)); break;
/*?*/               case SDRTEXTVERTADJUST_BLOCK: aNewSet.Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_BLOCK)); break;
/*?*/           }
/*?*/           switch(eHorz)
/*?*/           {
/*?*/               case SDRTEXTHORZADJUST_LEFT: aNewSet.Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_BOTTOM)); break;
/*?*/               case SDRTEXTHORZADJUST_CENTER: aNewSet.Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_CENTER)); break;
/*?*/               case SDRTEXTHORZADJUST_RIGHT: aNewSet.Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_TOP)); break;
/*?*/               case SDRTEXTHORZADJUST_BLOCK: aNewSet.Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_BLOCK)); break;
/*?*/           }
/*?*/
/*?*/           SetItemSet(aNewSet);
/*?*/
/*?*/           // set ParaObject orientation accordingly
/*?*/           pOutlinerParaObject->SetVertical(bVertical);
/*?*/
/*?*/           // restore object size
/*?*/           SetSnapRect(aObjectRect);
/*N*/       }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// transformation interface for StarOfficeAPI. This implements support for
// homogen 3x3 matrices containing the transformation of the SdrObject. At the
// moment it contains a shearX, rotation and translation, but for setting all linear
// transforms like Scale, ShearX, ShearY, Rotate and Translate are supported.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
// gets base transformation and rectangle of object. If it's an SdrPathObj it fills the PolyPolygon
// with the base geometry and returns TRUE. Otherwise it returns FALSE.
/*N*/ BOOL SdrTextObj::TRGetBaseGeometry(Matrix3D& rMat, XPolyPolygon& rPolyPolygon) const
/*N*/ {
/*N*/   // get turn and shear
/*N*/   double fRotate = (aGeo.nDrehWink / 100.0) * F_PI180;
/*N*/   double fShear = (aGeo.nShearWink / 100.0) * F_PI180;
/*N*/
/*N*/   // get aRect, this is the unrotated snaprect
/*N*/   Rectangle aRectangle(aRect);
/*N*/
/*N*/   // fill other values
/*N*/   Vector2D aScale((double)aRectangle.GetWidth(), (double)aRectangle.GetHeight());
/*N*/   Vector2D aTranslate((double)aRectangle.Left(), (double)aRectangle.Top());
/*N*/
/*N*/   // position maybe relative to anchorpos, convert
/*N*/   if( pModel->IsWriter() )
/*N*/   {
/*N*/       if(GetAnchorPos().X() != 0 || GetAnchorPos().Y() != 0)
/*N*/           aTranslate -= Vector2D(GetAnchorPos().X(), GetAnchorPos().Y());
/*N*/   }
/*N*/
/*N*/   // force MapUnit to 100th mm
/*N*/   SfxMapUnit eMapUnit = pModel->GetItemPool().GetMetric(0);
/*N*/   if(eMapUnit != SFX_MAPUNIT_100TH_MM)
/*N*/   {
/*N*/       switch(eMapUnit)
/*N*/       {
/*N*/           case SFX_MAPUNIT_TWIP :
/*N*/           {
/*N*/               // position
/*N*/               // #104018#
/*N*/               aTranslate.X() = ImplTwipsToMM(aTranslate.X());
/*N*/               aTranslate.Y() = ImplTwipsToMM(aTranslate.Y());
/*N*/
/*N*/               // size
/*N*/               // #104018#
/*N*/               aScale.X() = ImplTwipsToMM(aScale.X());
/*N*/               aScale.Y() = ImplTwipsToMM(aScale.Y());
/*N*/
/*N*/               break;
/*N*/           }
/*N*/           default:
/*N*/           {
/*N*/               DBG_ERROR("TRGetBaseGeometry: Missing unit translation to 100th mm!");
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // build matrix
/*N*/   rMat.Identity();
/*N*/   if(aScale.X() != 1.0 || aScale.Y() != 1.0)
/*N*/       rMat.Scale(aScale.X(), aScale.Y());
/*N*/   if(fShear != 0.0)
/*N*/       rMat.ShearX(tan(fShear));
/*N*/   if(fRotate != 0.0)
/*N*/       rMat.Rotate(fRotate);
/*N*/   if(aTranslate.X() != 0.0 || aTranslate.Y() != 0.0)
/*N*/       rMat.Translate(aTranslate.X(), aTranslate.Y());
/*N*/
/*N*/   return FALSE;
/*N*/ }

// sets the base geometry of the object using infos contained in the homogen 3x3 matrix.
// If it's an SdrPathObj it will use the provided geometry information. The Polygon has
// to use (0,0) as upper left and will be scaled to the given size in the matrix.
/*N*/ void SdrTextObj::TRSetBaseGeometry(const Matrix3D& rMat, const XPolyPolygon& rPolyPolygon)
/*N*/ {
/*N*/   // break up matrix
/*N*/   Vector2D aScale, aTranslate;
/*N*/   double fShear, fRotate;
/*N*/   rMat.DecomposeAndCorrect(aScale, fShear, fRotate, aTranslate);
/*N*/
/*N*/   // reset object shear and rotations
/*N*/   aGeo.nDrehWink = 0;
/*N*/   aGeo.RecalcSinCos();
/*N*/   aGeo.nShearWink = 0;
/*N*/   aGeo.RecalcTan();
/*N*/
/*N*/   // force metric to pool metric
/*N*/   SfxMapUnit eMapUnit = pModel->GetItemPool().GetMetric(0);
/*N*/   if(eMapUnit != SFX_MAPUNIT_100TH_MM)
/*N*/   {
/*N*/       switch(eMapUnit)
/*N*/       {
/*N*/           case SFX_MAPUNIT_TWIP :
/*N*/           {
/*N*/               // position
/*N*/               // #104018#
/*N*/               aTranslate.X() = ImplMMToTwips(aTranslate.X());
/*N*/               aTranslate.Y() = ImplMMToTwips(aTranslate.Y());
/*N*/
/*N*/               // size
/*N*/               // #104018#
/*N*/               aScale.X() = ImplMMToTwips(aScale.X());
/*N*/               aScale.Y() = ImplMMToTwips(aScale.Y());
/*N*/
/*N*/               break;
/*N*/           }
/*N*/           default:
/*N*/           {
/*N*/               DBG_ERROR("TRSetBaseGeometry: Missing unit translation to PoolMetric!");
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // if anchor is used, make position relative to it
/*N*/   if( pModel->IsWriter() )
/*N*/   {
/*N*/       if(GetAnchorPos().X() != 0 || GetAnchorPos().Y() != 0)
/*N*/           aTranslate += Vector2D(GetAnchorPos().X(), GetAnchorPos().Y());
/*N*/   }
/*N*/
/*N*/   // build and set BaseRect (use scale)
/*N*/   Point aPoint = Point();
/*N*/   Size  aSize(FRound(aScale.X()), FRound(aScale.Y()));
/*N*/   Rectangle aBaseRect(aPoint, aSize);
/*N*/   SetSnapRect(aBaseRect);
/*N*/
/*N*/   // shear?
/*N*/   if(fShear != 0.0)
/*N*/   {
/*N*/       GeoStat aGeoStat;
/*N*/       aGeoStat.nShearWink = FRound((atan(fShear) / F_PI180) * 100.0);
/*N*/       aGeoStat.RecalcTan();
/*N*/       Shear(Point(), aGeoStat.nShearWink, aGeoStat.nTan, FALSE);
/*N*/   }
/*N*/
/*N*/   // rotation?
/*N*/   if(fRotate != 0.0)
/*N*/   {
/*N*/       GeoStat aGeoStat;
/*N*/       aGeoStat.nDrehWink = FRound((fRotate / F_PI180) * 100.0);
/*N*/       aGeoStat.RecalcSinCos();
/*N*/       Rotate(Point(), aGeoStat.nDrehWink, aGeoStat.nSin, aGeoStat.nCos);
/*N*/   }
/*N*/
/*N*/   // translate?
/*N*/   if(aTranslate.X() != 0.0 || aTranslate.Y() != 0.0)
/*N*/   {
/*N*/       Move(Size(
/*N*/           (sal_Int32)FRound(aTranslate.X()),
/*N*/           (sal_Int32)FRound(aTranslate.Y())));
/*N*/   }
/*N*/ }

//STRIP001 bool SdrTextObj::IsRealyEdited() const
//STRIP001 {
//STRIP001  return pEdtOutl && pEdtOutl->IsModified();
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Konzept des TextObjekts:
// ~~~~~~~~~~~~~~~~~~~~~~~~
// Attribute/Varianten:
// - BOOL Textrahmen / beschriftetes Zeichenobjekt
// - BOOL FontWork                 (wenn nicht Textrahmen und nicht ContourTextFrame)
// - BOOL ContourTextFrame         (wenn nicht Textrahmen und nicht Fontwork)
// - long Drehwinkel               (wenn nicht FontWork)
// - long Textrahmenabstaende      (wenn nicht FontWork)
// - BOOL FitToSize                (wenn nicht FontWork)
// - BOOL AutoGrowingWidth/Height  (wenn nicht FitToSize und nicht FontWork)
// - long Min/MaxFrameWidth/Height (wenn AutoGrowingWidth/Height)
// - enum Horizontale Textverankerung Links,Mitte,Rechts,Block,Stretch(ni)
// - enum Vertikale Textverankerung Oben,Mitte,Unten,Block,Stretch(ni)
// - enum Laufschrift              (wenn nicht FontWork)
//
// Jedes abgeleitete Objekt ist entweder ein Textrahmen (bTextFrame=TRUE)
// oder ein beschriftetes Zeichenobjekt (bTextFrame=FALSE).
//
// Defaultverankerung von Textrahmen:
//   SDRTEXTHORZADJUST_BLOCK, SDRTEXTVERTADJUST_TOP
//   = statische Pooldefaults
// Defaultverankerung von beschrifteten Zeichenobjekten:
//   SDRTEXTHORZADJUST_CENTER, SDRTEXTVERTADJUST_CENTER
//   durch harte Attributierung von SdrAttrObj
//
// Jedes vom SdrTextObj abgeleitete Objekt muss ein "UnrotatedSnapRect"
// (->TakeUnrotatedSnapRect()) liefern (Drehreferenz ist TopLeft dieses
// Rechtecks (aGeo.nDrehWink)), welches die Grundlage der Textverankerung
// bildet. Von diesem werden dann ringsum die Textrahmenabstaende abgezogen;
// das Ergebnis ist der Ankerbereich (->TakeTextAnchorRect()). Innerhalb
// dieses Bereichs wird dann in Abhaengigkeit von der horizontalen und
// vertikalen Ausrichtung (SdrTextVertAdjust,SdrTextHorzAdjust) der Ankerpunkt
// sowie der Ausgabebereich bestimmt. Bei beschrifteten Grafikobjekten kann
// der Ausgabebereich durchaus groesser als der Ankerbereich werden, bei
// Textrahmen ist er stets kleiner oder gleich (ausser bei negativen Textrahmen-
// abstaenden).
//
// FitToSize hat Prioritaet vor Textverankerung und AutoGrowHeight/Width. Der
// Ausgabebereich ist bei FitToSize immer genau der Ankerbereich. Weiterhin
// gibt es bei FitToSize keinen automatischen Zeilenumbruch.
//
// ContourTextFrame:
// - long Drehwinkel
// - long Textrahmenabstaende         spaeter vielleicht
// - BOOL FitToSize                   spaeter vielleicht
// - BOOL AutoGrowingWidth/Height     viel spaeter vielleicht
// - long Min/MaxFrameWidth/Height    viel spaeter vielleicht
// - enum Horizontale Textverankerung spaeter vielleicht, erstmal Links, Absatz zentr.
// - enum Vertikale Textverankerung   spaeter vielleicht, erstmal oben
// - enum Laufschrift                 spaeter vielleicht (evtl. sogar mit korrektem Clipping)
//
// Bei Aenderungen zu beachten:
// - Paint
// - HitTest
// - RecalcBoundRect
// - ConvertToPoly
// - Edit
// - Drucken,Speichern, Paint in Nachbarview waerend Edit
// - ModelChanged (z.B. durch NachbarView oder Lineale) waerend Edit
// - FillColorChanged waerend Edit
// - uvm...
//
/////////////////////////////////////////////////////////////////////////////////////////////////

}
