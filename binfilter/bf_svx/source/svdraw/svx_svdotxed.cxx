/*************************************************************************
 *
 *  $RCSfile: svx_svdotxed.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:23 $
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

#include "svdotext.hxx"
#include "svditext.hxx"
#include "svdmodel.hxx" // fuer GetMaxObjSize
#include "svdoutl.hxx"

#ifndef _OUTLINER_HXX //autogen
#include "outliner.hxx"
#endif

#ifndef _EDITSTAT_HXX //autogen
#include <editstat.hxx>
#endif
namespace binfilter {

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
//  TextEdit
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ FASTBOOL SdrTextObj::HasTextEdit() const
/*N*/ {
/*N*/   // lt. Anweisung von MB duerfen gelinkte Textobjekte nun doch
/*N*/   // geaendert werden (kein automatisches Reload)
/*N*/   return TRUE;
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::BegTextEdit(SdrOutliner& rOutl)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  if (pEdtOutl!=NULL) return FALSE; // Textedit laeuft evtl. schon an einer anderen View!
//STRIP001  pEdtOutl=&rOutl;
//STRIP001
//STRIP001  // #101684#
//STRIP001  mbInEditMode = TRUE;
//STRIP001
//STRIP001  USHORT nOutlinerMode = OUTLINERMODE_OUTLINEOBJECT;
//STRIP001  if ( !IsOutlText() )
//STRIP001      nOutlinerMode = OUTLINERMODE_TEXTOBJECT;
//STRIP001  rOutl.Init( nOutlinerMode );
//STRIP001  rOutl.SetRefDevice( pModel->GetRefDevice() );
//STRIP001
//STRIP001  SdrFitToSizeType eFit=GetFitToSize();
//STRIP001  FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
//STRIP001  FASTBOOL bContourFrame=IsContourTextFrame();
//STRIP001  ImpSetTextEditParams();
//STRIP001
//STRIP001  if (!bContourFrame) {
//STRIP001      ULONG nStat=rOutl.GetControlWord();
//STRIP001      nStat|=EE_CNTRL_AUTOPAGESIZE;
//STRIP001      if (bFitToSize) nStat|=EE_CNTRL_STRETCHING; else nStat&=~EE_CNTRL_STRETCHING;
//STRIP001      rOutl.SetControlWord(nStat);
//STRIP001  }
//STRIP001
//STRIP001  if (pOutlinerParaObject!=NULL) {
//STRIP001      rOutl.SetText(*pOutlinerParaObject);
//STRIP001  }
//STRIP001  // ggf. Rahmenattribute am 1. (neuen) Absatz des Outliners setzen
//STRIP001  if (rOutl.GetParagraphCount()==1) { // bei nur einem Para nachsehen ob da ueberhaupt was drin steht
//STRIP001      XubString aStr( rOutl.GetText( rOutl.GetParagraph( 0 ) ) );
//STRIP001
//STRIP001      if(!aStr.Len())
//STRIP001      {
//STRIP001          // Aha, steht nix drin!
//STRIP001          // damit sich der Outliner initiallisiert
//STRIP001          rOutl.SetText( String(), rOutl.GetParagraph( 0 ) );
//STRIP001
//STRIP001          if(GetStyleSheet())
//STRIP001              rOutl.SetStyleSheet( 0, GetStyleSheet());
//STRIP001
//STRIP001          // Beim setzen der harten Attribute an den ersten Absatz muss
//STRIP001          // der Parent pOutlAttr (=die Vorlage) temporaer entfernt
//STRIP001          // werden, da sonst bei SetParaAttribs() auch alle in diesem
//STRIP001          // Parent enthaltenen Items hart am Absatz attributiert werden.
//STRIP001          // -> BugID 22467
//STRIP001          const SfxItemSet& rSet = GetItemSet();
//STRIP001          SdrOutlinerSetItem aOutlSetItem(rSet.GetPool());
//STRIP001          aOutlSetItem.GetItemSet().Put(rSet);
//STRIP001          const SfxItemSet* pTmpSet = &aOutlSetItem.GetItemSet();
//STRIP001          const SfxItemSet* pParentMerk = pTmpSet->GetParent();
//STRIP001          ((SfxItemSet*)pTmpSet)->SetParent(NULL);
//STRIP001          rOutl.SetParaAttribs(0,*pTmpSet);
//STRIP001          ((SfxItemSet*)pTmpSet)->SetParent(pParentMerk);
//STRIP001      }
//STRIP001  }
//STRIP001  if (bFitToSize) {
//STRIP001      Rectangle aAnchorRect;
//STRIP001      Rectangle aTextRect;
//STRIP001      TakeTextRect(rOutl, aTextRect, FALSE,
//STRIP001          &aAnchorRect/* #97097# give TRUE here, not FALSE */);
//STRIP001      Fraction aFitXKorreg(1,1);
//STRIP001      ImpSetCharStretching(rOutl,aTextRect,aAnchorRect,aFitXKorreg);
//STRIP001  }
//STRIP001
//STRIP001  if(pOutlinerParaObject)
//STRIP001  {
//STRIP001      // #78476# also repaint when animated text is put to edit mode
//STRIP001      // to not make appear the text double
//STRIP001      BOOL bIsAnimated(pPlusData && pPlusData->pAnimator);
//STRIP001
//STRIP001      if(aGeo.nDrehWink || IsFontwork() || bIsAnimated)
//STRIP001          SendRepaintBroadcast();
//STRIP001  }
//STRIP001
//STRIP001  rOutl.UpdateFields();
//STRIP001  rOutl.ClearModifyFlag();
//STRIP001
//STRIP001  return TRUE;
/*N*/ }

//STRIP001 void SdrTextObj::TakeTextEditArea(Size* pPaperMin, Size* pPaperMax, Rectangle* pViewInit, Rectangle* pViewMin) const
//STRIP001 {
//STRIP001  SdrFitToSizeType eFit=GetFitToSize();
//STRIP001  FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
//STRIP001  Size aPaperMin,aPaperMax;
//STRIP001  Rectangle aViewInit;
//STRIP001  TakeTextAnchorRect(aViewInit);
//STRIP001  if (aGeo.nDrehWink!=0) {
//STRIP001      Point aCenter(aViewInit.Center());
//STRIP001      aCenter-=aViewInit.TopLeft();
//STRIP001      Point aCenter0(aCenter);
//STRIP001      RotatePoint(aCenter,Point(),aGeo.nSin,aGeo.nCos);
//STRIP001      aCenter-=aCenter0;
//STRIP001      aViewInit.Move(aCenter.X(),aCenter.Y());
//STRIP001  }
//STRIP001  Size aAnkSiz(aViewInit.GetSize());
//STRIP001  aAnkSiz.Width()--; aAnkSiz.Height()--; // weil GetSize() ein draufaddiert
//STRIP001  Size aMaxSiz(1000000,1000000);
//STRIP001  if (pModel!=NULL) {
//STRIP001      Size aTmpSiz(pModel->GetMaxObjSize());
//STRIP001      if (aTmpSiz.Width()!=0) aMaxSiz.Width()=aTmpSiz.Width();
//STRIP001      if (aTmpSiz.Height()!=0) aMaxSiz.Height()=aTmpSiz.Height();
//STRIP001  }
//STRIP001
//STRIP001  // #106879#
//STRIP001  // Done earlier since used in else tree below
//STRIP001  SdrTextHorzAdjust eHAdj(GetTextHorizontalAdjust());
//STRIP001  SdrTextVertAdjust eVAdj(GetTextVerticalAdjust());
//STRIP001
//STRIP001  if(IsTextFrame())
//STRIP001  {
//STRIP001      long nMinWdt=GetMinTextFrameWidth();
//STRIP001      long nMinHgt=GetMinTextFrameHeight();
//STRIP001      long nMaxWdt=GetMaxTextFrameWidth();
//STRIP001      long nMaxHgt=GetMaxTextFrameHeight();
//STRIP001      if (nMinWdt<1) nMinWdt=1;
//STRIP001      if (nMinHgt<1) nMinHgt=1;
//STRIP001      if (!bFitToSize) {
//STRIP001          if (nMaxWdt==0 || nMaxWdt>aMaxSiz.Width())  nMaxWdt=aMaxSiz.Width();
//STRIP001          if (nMaxHgt==0 || nMaxHgt>aMaxSiz.Height()) nMaxHgt=aMaxSiz.Height();
//STRIP001          if (!IsAutoGrowWidth() ) { nMaxWdt=aAnkSiz.Width();  nMinWdt=nMaxWdt; }
//STRIP001          if (!IsAutoGrowHeight()) { nMaxHgt=aAnkSiz.Height(); nMinHgt=nMaxHgt; }
//STRIP001          SdrTextAniKind      eAniKind=GetTextAniKind();
//STRIP001          SdrTextAniDirection eAniDirection=GetTextAniDirection();
//STRIP001
//STRIP001          // #101684#
//STRIP001          BOOL bInEditMode = IsInEditMode();
//STRIP001
//STRIP001          if (!bInEditMode && (eAniKind==SDRTEXTANI_SCROLL || eAniKind==SDRTEXTANI_ALTERNATE || eAniKind==SDRTEXTANI_SLIDE))
//STRIP001          {
//STRIP001              // Grenzenlose Papiergroesse fuer Laufschrift
//STRIP001              if (eAniDirection==SDRTEXTANI_LEFT || eAniDirection==SDRTEXTANI_RIGHT) nMaxWdt=1000000;
//STRIP001              if (eAniDirection==SDRTEXTANI_UP || eAniDirection==SDRTEXTANI_DOWN) nMaxHgt=1000000;
//STRIP001          }
//STRIP001          aPaperMax.Width()=nMaxWdt;
//STRIP001          aPaperMax.Height()=nMaxHgt;
//STRIP001      } else {
//STRIP001          aPaperMax=aMaxSiz;
//STRIP001      }
//STRIP001      aPaperMin.Width()=nMinWdt;
//STRIP001      aPaperMin.Height()=nMinHgt;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // #106879#
//STRIP001      // aPaperMin needs to be set to object's size if full width is activated
//STRIP001      // for hor or ver writing respectively
//STRIP001      if((SDRTEXTHORZADJUST_BLOCK == eHAdj && !IsVerticalWriting())
//STRIP001          || (SDRTEXTVERTADJUST_BLOCK == eVAdj && IsVerticalWriting()))
//STRIP001      {
//STRIP001          aPaperMin = aAnkSiz;
//STRIP001      }
//STRIP001
//STRIP001      aPaperMax=aMaxSiz;
//STRIP001  }
//STRIP001
//STRIP001  if (pViewMin!=NULL) {
//STRIP001      *pViewMin=aViewInit;
//STRIP001
//STRIP001      long nXFree=aAnkSiz.Width()-aPaperMin.Width();
//STRIP001      if (eHAdj==SDRTEXTHORZADJUST_LEFT) pViewMin->Right()-=nXFree;
//STRIP001      else if (eHAdj==SDRTEXTHORZADJUST_RIGHT) pViewMin->Left()+=nXFree;
//STRIP001      else { pViewMin->Left()+=nXFree/2; pViewMin->Right()=pViewMin->Left()+aPaperMin.Width(); }
//STRIP001
//STRIP001      long nYFree=aAnkSiz.Height()-aPaperMin.Height();
//STRIP001      if (eVAdj==SDRTEXTVERTADJUST_TOP) pViewMin->Bottom()-=nYFree;
//STRIP001      else if (eVAdj==SDRTEXTVERTADJUST_BOTTOM) pViewMin->Top()+=nYFree;
//STRIP001      else { pViewMin->Top()+=nYFree/2; pViewMin->Bottom()=pViewMin->Top()+aPaperMin.Height(); }
//STRIP001  }
//STRIP001
//STRIP001  // Die PaperSize soll in den meisten Faellen von selbst wachsen
//STRIP001  // #89459#
//STRIP001  if(IsVerticalWriting())
//STRIP001      aPaperMin.Width() = 0;
//STRIP001  else
//STRIP001      aPaperMin.Height() = 0; // #33102#
//STRIP001
//STRIP001  if(eHAdj!=SDRTEXTHORZADJUST_BLOCK || bFitToSize) {
//STRIP001      aPaperMin.Width()=0;
//STRIP001  }
//STRIP001
//STRIP001  // #103516# For complete ver adjust support, set paper min height to 0, here.
//STRIP001  if(SDRTEXTHORZADJUST_BLOCK != eVAdj || bFitToSize)
//STRIP001  {
//STRIP001      aPaperMin.Height() = 0;
//STRIP001  }
//STRIP001
//STRIP001  if (pPaperMin!=NULL) *pPaperMin=aPaperMin;
//STRIP001  if (pPaperMax!=NULL) *pPaperMax=aPaperMax;
//STRIP001  if (pViewInit!=NULL) *pViewInit=aViewInit;
//STRIP001 }

/*N*/ void SdrTextObj::EndTextEdit(SdrOutliner& rOutl)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if(rOutl.IsModified())
//STRIP001  {
//STRIP001      OutlinerParaObject* pNewText = NULL;
//STRIP001      Paragraph* p1stPara = rOutl.GetParagraph( 0 );
//STRIP001      UINT32 nParaAnz = rOutl.GetParagraphCount();
//STRIP001
//STRIP001      if(p1stPara)
//STRIP001      {
//STRIP001          if(nParaAnz == 1)
//STRIP001          {
//STRIP001              // bei nur einem Para nachsehen ob da ueberhaupt was drin steht
//STRIP001              XubString aStr(rOutl.GetText(p1stPara));
//STRIP001
//STRIP001              if(!aStr.Len())
//STRIP001              {
//STRIP001                  // Aha, steht nix drin!
//STRIP001                  nParaAnz = 0;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // Damit der grauen Feldhintergrund wieder verschwindet
//STRIP001          rOutl.UpdateFields();
//STRIP001
//STRIP001          if(nParaAnz != 0)
//STRIP001          {
//STRIP001              // Wirklich Textobjekt kreieren
//STRIP001              pNewText = rOutl.CreateParaObject( 0, (sal_uInt16)nParaAnz );
//STRIP001          }
//STRIP001      }
//STRIP001      SetOutlinerParaObject(pNewText);
//STRIP001  }
//STRIP001
//STRIP001  pEdtOutl = NULL;
//STRIP001  rOutl.Clear();
//STRIP001  UINT32 nStat = rOutl.GetControlWord();
//STRIP001  nStat &= ~EE_CNTRL_AUTOPAGESIZE;
//STRIP001  rOutl.SetControlWord(nStat);
//STRIP001
//STRIP001  // #101684#
//STRIP001  mbInEditMode = FALSE;
/*N*/ }

/*N*/ SdrObject* SdrTextObj::CheckTextEditHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   return SdrTextObj::CheckHit(rPnt,nTol,pVisiLayer);
/*N*/ }

//STRIP001 USHORT SdrTextObj::GetOutlinerViewAnchorMode() const
//STRIP001 {
//STRIP001  SdrTextHorzAdjust eH=GetTextHorizontalAdjust();
//STRIP001  SdrTextVertAdjust eV=GetTextVerticalAdjust();
//STRIP001  EVAnchorMode eRet=ANCHOR_TOP_LEFT;
//STRIP001  if (IsContourTextFrame()) return (USHORT)eRet;
//STRIP001  if (eH==SDRTEXTHORZADJUST_LEFT) {
//STRIP001      if (eV==SDRTEXTVERTADJUST_TOP) {
//STRIP001          eRet=ANCHOR_TOP_LEFT;
//STRIP001      } else if (eV==SDRTEXTVERTADJUST_BOTTOM) {
//STRIP001          eRet=ANCHOR_BOTTOM_LEFT;
//STRIP001      } else {
//STRIP001          eRet=ANCHOR_VCENTER_LEFT;
//STRIP001      }
//STRIP001  } else if (eH==SDRTEXTHORZADJUST_RIGHT) {
//STRIP001      if (eV==SDRTEXTVERTADJUST_TOP) {
//STRIP001          eRet=ANCHOR_TOP_RIGHT;
//STRIP001      } else if (eV==SDRTEXTVERTADJUST_BOTTOM) {
//STRIP001          eRet=ANCHOR_BOTTOM_RIGHT;
//STRIP001      } else {
//STRIP001          eRet=ANCHOR_VCENTER_RIGHT;
//STRIP001      }
//STRIP001  } else {
//STRIP001      if (eV==SDRTEXTVERTADJUST_TOP) {
//STRIP001          eRet=ANCHOR_TOP_HCENTER;
//STRIP001      } else if (eV==SDRTEXTVERTADJUST_BOTTOM) {
//STRIP001          eRet=ANCHOR_BOTTOM_HCENTER;
//STRIP001      } else {
//STRIP001          eRet=ANCHOR_VCENTER_HCENTER;
//STRIP001      }
//STRIP001  }
//STRIP001  return (USHORT)eRet;
//STRIP001 }

//STRIP001 void SdrTextObj::ImpSetTextEditParams() const
//STRIP001 {
//STRIP001  if (pEdtOutl!=NULL) {
//STRIP001      FASTBOOL bUpdMerk=pEdtOutl->GetUpdateMode();
//STRIP001      if (bUpdMerk) pEdtOutl->SetUpdateMode(FALSE);
//STRIP001      Size aPaperMin;
//STRIP001      Size aPaperMax;
//STRIP001      Rectangle aEditArea;
//STRIP001      TakeTextEditArea(&aPaperMin,&aPaperMax,&aEditArea,NULL);
//STRIP001      SdrFitToSizeType eFit=GetFitToSize();
//STRIP001      FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
//STRIP001      FASTBOOL bContourFrame=IsContourTextFrame();
//STRIP001      EVAnchorMode eAM=(EVAnchorMode)GetOutlinerViewAnchorMode();
//STRIP001      ULONG nViewAnz=pEdtOutl->GetViewCount();
//STRIP001      pEdtOutl->SetMinAutoPaperSize(aPaperMin);
//STRIP001      pEdtOutl->SetMaxAutoPaperSize(aPaperMax);
//STRIP001      pEdtOutl->SetPaperSize(Size());
//STRIP001      if (bContourFrame) {
//STRIP001          Rectangle aAnchorRect;
//STRIP001          TakeTextAnchorRect(aAnchorRect);
//STRIP001          ImpSetContourPolygon(*pEdtOutl,aAnchorRect, TRUE);
//STRIP001      }
//STRIP001      if (bUpdMerk) pEdtOutl->SetUpdateMode(TRUE);
//STRIP001  }
//STRIP001 }

}
