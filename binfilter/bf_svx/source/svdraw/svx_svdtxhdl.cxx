/*************************************************************************
 *
 *  $RCSfile: svx_svdtxhdl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:32:54 $
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

#include "svdtxhdl.hxx"
#include <limits.h>
// auto strip #include "svditext.hxx"
#include "svdmodel.hxx"
// auto strip #include "svdpage.hxx"
// auto strip #include "svdogrp.hxx"
#include "svdotext.hxx"
// auto strip #include "svdxout.hxx"
#include "svdoutl.hxx"

// auto strip #ifndef _OUTLINER_HXX //autogen
// auto strip #include "outliner.hxx"
// auto strip #endif

#ifndef _OUTLOBJ_HXX //autogen
#include <outlobj.hxx>
#endif

// auto strip #ifndef _SVX_SVXFONT_HXX //autogen
// auto strip #include "svxfont.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XLNCLIT_HXX //autogen
// auto strip #include "xlnclit.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XLNWTIT_HXX //autogen
// auto strip #include "xlnwtit.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XFLCLIT_HXX //autogen
// auto strip #include "xflclit.hxx"
// auto strip #endif

// auto strip #ifndef _SV_METRIC_HXX //autogen
// auto strip #include <vcl/metric.hxx>
// auto strip #endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// #101499#
// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif

// auto strip #ifndef _COM_SUN_STAR_I18N_XBREAKITERATOR_HPP_
// auto strip #include <com/sun/star/i18n/XBreakIterator.hpp>
// auto strip #endif

// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif

#ifndef _COM_SUN_STAR_I18N_CHARACTERITERATORMODE_HDL_
#include <com/sun/star/i18n/CharacterIteratorMode.hdl>
#endif

// auto strip #ifndef _UNO_LINGU_HXX
// auto strip #include "unolingu.hxx"
// auto strip #endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::i18n;

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ ImpTextPortionHandler::ImpTextPortionHandler(SdrOutliner& rOutln, const SdrTextObj& rTxtObj):
/*N*/   rOutliner(rOutln),
/*N*/   rTextObj(rTxtObj),
/*N*/   // #101498# aPoly(0)
/*N*/   mpRecordPortions(0L)
/*N*/ {
/*N*/   pModel=rTextObj.GetModel();
/*N*/   MapMode aMap=aVDev.GetMapMode();
/*N*/
/*N*/   aMap.SetMapUnit(pModel->GetScaleUnit());
/*N*/   aMap.SetScaleX(pModel->GetScaleFraction());
/*N*/   aMap.SetScaleY(pModel->GetScaleFraction());
/*N*/   aVDev.SetMapMode(aMap);
/*N*/ }

//STRIP001 void ImpTextPortionHandler::ConvertToPathObj(SdrObjGroup& rGroup, FASTBOOL bPoly)
//STRIP001 {
//STRIP001  bToPoly=bPoly;
//STRIP001  pGroup=&rGroup;
//STRIP001
//STRIP001  Rectangle aAnchorRect;
//STRIP001  Rectangle aTextRect;
//STRIP001  SdrFitToSizeType eFit=rTextObj.GetFitToSize();
//STRIP001  FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
//STRIP001  // Bei TakeTextRect wird u.a. auch der Text in
//STRIP001  // den Outliner gesteckt
//STRIP001  rTextObj.TakeTextRect(rOutliner,aTextRect,FALSE,&aAnchorRect);
//STRIP001  aFormTextBoundRect=aTextRect; // Missbrauch von FormTextBoundRect
//STRIP001  if (bFitToSize) aFormTextBoundRect=aAnchorRect;
//STRIP001  rOutliner.SetDrawPortionHdl(LINK(this,ImpTextPortionHandler,ConvertHdl));
//STRIP001  rOutliner.StripPortions();
//STRIP001  rOutliner.SetDrawPortionHdl(Link());
//STRIP001  rOutliner.Clear();
//STRIP001
//STRIP001  if(bFitToSize)
//STRIP001  {
//STRIP001      Fraction nX(aAnchorRect.Right()-aAnchorRect.Left(),aTextRect.Right()-aTextRect.Left());
//STRIP001      Fraction nY(aAnchorRect.Bottom()-aAnchorRect.Top(),aTextRect.Bottom()-aTextRect.Top());
//STRIP001
//STRIP001      // #95395# scale from top-right when vertical text
//STRIP001      if(rOutliner.IsVertical())
//STRIP001          pGroup->NbcResize(aAnchorRect.TopRight(),nX,nY);
//STRIP001      else
//STRIP001          pGroup->NbcResize(aAnchorRect.TopLeft(),nX,nY);
//STRIP001  }
//STRIP001  if (rTextObj.aGeo.nDrehWink!=0) { // #35825# Rotieren erst nach Resize (wg. FitToSize)
//STRIP001      pGroup->NbcRotate(aFormTextBoundRect.TopLeft(),rTextObj.aGeo.nDrehWink,rTextObj.aGeo.nSin,rTextObj.aGeo.nCos);
//STRIP001  }
//STRIP001 }

/*N*/ void ImpTextPortionHandler::DrawTextToPath(ExtOutputDevice& rXOut, FASTBOOL bDrawEffect)
/*N*/ {
/*N*/   aFormTextBoundRect=Rectangle();
/*N*/   const Rectangle& rBR = rTextObj.GetSnapRect();
/*N*/
/*N*/   bDraw = bDrawEffect;
/*N*/
/*N*/   OutlinerParaObject* pPara=rTextObj.GetOutlinerParaObject();
/*N*/   if (rTextObj.IsTextEditActive()) {
/*?*/       pPara=rTextObj.GetEditOutlinerParaObject();
/*N*/   }
/*N*/   if (pPara!=NULL) {
/*N*/       XPolyPolygon aXPP;
/*N*/       //rTextObj.TakeContour(aXPP);
/*N*/       rTextObj.TakeXorPoly(aXPP,FALSE);
/*N*/       pXOut=&rXOut;
/*N*/       Font aFont(rXOut.GetOutDev()->GetFont());
/*N*/       rOutliner.Clear();
/*N*/       rOutliner.SetPaperSize(Size(LONG_MAX,LONG_MAX));
/*N*/       rOutliner.SetText(*pPara);
/*N*/       USHORT nCnt = Min(aXPP.Count(), (USHORT) rOutliner.GetParagraphCount());
/*N*/
/*N*/       if ( nCnt == 1 )    bToLastPoint = TRUE;
/*N*/       else                bToLastPoint = FALSE;
/*N*/
/*N*/       // #101498# completely different methodology needed here for making this BIDI-able
/*N*/       // iterate over paragraphs and Polygons, thus each paragraph will be put to
/*N*/       // one Polygon
/*N*/       const sal_uInt32 nSavedLayoutMode(rXOut.GetOutDev()->GetLayoutMode());
/*N*/       sal_uInt32 nLayoutMode(nSavedLayoutMode);
/*N*/
/*N*/       if(TRUE)
/*N*/       {
/*N*/           nLayoutMode &= ~(TEXT_LAYOUT_BIDI_RTL|TEXT_LAYOUT_COMPLEX_DISABLED|TEXT_LAYOUT_BIDI_STRONG);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           nLayoutMode &= ~(TEXT_LAYOUT_BIDI_RTL);
/*N*/           nLayoutMode |= ~(TEXT_LAYOUT_COMPLEX_DISABLED|TEXT_LAYOUT_BIDI_STRONG);
/*N*/       }
/*N*/
/*N*/       rXOut.GetOutDev()->SetLayoutMode(nLayoutMode);
/*N*/
/*N*/       for(nParagraph = 0; nParagraph < nCnt; nParagraph++)
/*N*/       {
/*N*/           Polygon aPoly = XOutCreatePolygon(aXPP[sal_uInt16(nParagraph)], rXOut.GetOutDev());
/*N*/
/*N*/           rOutliner.SetDrawPortionHdl(LINK(this, ImpTextPortionHandler, FormTextRecordPortionHdl));
/*N*/           rOutliner.StripPortions();
/*N*/
/*N*/           DrawFormTextRecordPortions(aPoly);
/*N*/           ClearFormTextRecordPortions();
/*N*/
/*N*/           const Rectangle& rFTBR = rXOut.GetFormTextBoundRect();
/*N*/           aFormTextBoundRect.Union(rFTBR);
/*N*/       }
/*N*/
/*N*/       rXOut.GetOutDev()->SetLayoutMode(nSavedLayoutMode);
/*N*/
/*N*/       //for (nParagraph = 0; nParagraph < nCnt; nParagraph++)
/*N*/       //{
/*N*/       //  aPoly = XOutCreatePolygon(aXPP[USHORT(nParagraph)], rXOut.GetOutDev());
/*N*/       //  nTextWidth = 0;
/*N*/       //
/*N*/       //  rOutliner.SetDrawPortionHdl(LINK(this,ImpTextPortionHandler,FormTextWidthHdl));
/*N*/       //  rOutliner.StripPortions();
/*N*/       //  rOutliner.SetDrawPortionHdl(LINK(this,ImpTextPortionHandler,FormTextDrawHdl));
/*N*/       //  rOutliner.StripPortions();
/*N*/       //  rOutliner.SetDrawPortionHdl(Link());
/*N*/       //
/*N*/       //  const Rectangle& rFTBR=rXOut.GetFormTextBoundRect();
/*N*/       //  aFormTextBoundRect.Union(rFTBR);
/*N*/       //}
/*N*/
/*N*/       rXOut.GetOutDev()->SetFont(aFont);
/*N*/       rOutliner.Clear();
/*N*/   }
/*N*/   if (rTextObj.IsTextEditActive()) {
/*?*/       delete pPara;
/*N*/   }
/*N*/ }

// #101498# Record and sort all portions
/*N*/ IMPL_LINK(ImpTextPortionHandler, FormTextRecordPortionHdl, DrawPortionInfo*, pInfo)
/*N*/ {
/*N*/   if(pInfo->nPara == nParagraph)
/*N*/   {
/*N*/       SortedAddFormTextRecordPortion(pInfo);
/*N*/   }
/*N*/
/*N*/   return 0;
/*N*/ }

// #101498# Helper class to remember text portions in sorted manner
/*N*/ class ImpRecordPortion
/*N*/ {
/*N*/ public:
/*N*/   Point                       maPosition;
/*N*/   String                      maText;
/*N*/   xub_StrLen                  mnTextStart;
/*N*/   xub_StrLen                  mnTextLength;
/*N*/   sal_uInt16                  mnPara;
/*N*/   xub_StrLen                  mnIndex;
/*N*/
/*N*/   // #102819# Here SvxFont needs to be used instead of Font
/*N*/   SvxFont                     maFont;
/*N*/
/*N*/   sal_Int32*                  mpDXArray;
/*N*/   sal_uInt8                   mnBiDiLevel;
/*N*/
/*N*/   ImpRecordPortion(DrawPortionInfo* pInfo);
/*N*/   ~ImpRecordPortion();
/*N*/
/*N*/   sal_uInt8 GetBiDiLevel() const { return mnBiDiLevel; }
/*N*/ };

/*N*/ ImpRecordPortion::ImpRecordPortion(DrawPortionInfo* pInfo)
/*N*/ : maPosition(pInfo->rStartPos),
/*N*/   maText(pInfo->rText),
/*N*/   mnTextStart((xub_StrLen)pInfo->nTextStart),
/*N*/   mnTextLength((xub_StrLen)pInfo->nTextLen),
/*N*/   mnPara(pInfo->nPara),
/*N*/   mnIndex(pInfo->nIndex),
/*N*/   maFont(pInfo->rFont),
/*N*/   mpDXArray(NULL),
/*N*/   mnBiDiLevel(pInfo->GetBiDiLevel())
/*N*/ {
/*N*/   if(pInfo->pDXArray)
/*N*/   {
/*N*/       mpDXArray = new sal_Int32[pInfo->nTextLen];
/*N*/
/*N*/       for(sal_uInt32 a(0L); a < pInfo->nTextLen; a++)
/*N*/       {
/*N*/           mpDXArray[a] = pInfo->pDXArray[a];
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
/*N*/ ImpRecordPortion::~ImpRecordPortion()
/*N*/ {
/*N*/   if(mpDXArray)
/*N*/   {
/*N*/       delete[] mpDXArray;
/*N*/   }
/*N*/ }

/*N*/ // #101498# List classes for recording portions
/*N*/ DECLARE_LIST(ImpRecordPortionList, ImpRecordPortion*)//STRIP008 ;
/*N*/ DECLARE_LIST(ImpRecordPortionListList, ImpRecordPortionList*)//STRIP008 ;

/*N*/ // #101498# Draw recorded formtext along Poly
/*N*/ void ImpTextPortionHandler::DrawFormTextRecordPortions(Polygon aPoly)
/*N*/ {
/*N*/   sal_Int32 nTextWidth = -((sal_Int32)GetFormTextPortionsLength(pXOut->GetOutDev()));
/*N*/
/*N*/   ImpRecordPortionListList* pListList = (ImpRecordPortionListList*)mpRecordPortions;
/*N*/   if(pListList)
/*N*/   {
/*N*/       for(sal_uInt32 a(0L); a < pListList->Count(); a++)
/*N*/       {
/*N*/           ImpRecordPortionList* pList = pListList->GetObject(a);
/*N*/
/*N*/           for(sal_uInt32 b(0L); b < pList->Count(); b++)
/*N*/           {
/*N*/               ImpRecordPortion* pPortion = pList->GetObject(b);
/*N*/
/*N*/               DrawPortionInfo aNewInfo(
/*N*/                   pPortion->maPosition,
/*N*/                   pPortion->maText,
/*N*/                   pPortion->mnTextStart,
/*N*/                   pPortion->mnTextLength,
/*N*/                   pPortion->maFont,
/*N*/                   pPortion->mnPara,
/*N*/                   pPortion->mnIndex,
/*N*/                   pPortion->mpDXArray,
/*N*/                   pPortion->mnBiDiLevel);
/*N*/
/*N*/               nTextWidth = pXOut->DrawFormText(&aNewInfo, aPoly, nTextWidth, bToLastPoint, bDraw);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ // #101498# Insert new portion sorted
/*N*/ void ImpTextPortionHandler::SortedAddFormTextRecordPortion(DrawPortionInfo* pInfo)
/*N*/ {
/*N*/   // get ListList and create on demand
/*N*/   ImpRecordPortionListList* pListList = (ImpRecordPortionListList*)mpRecordPortions;
/*N*/   if(!pListList)
/*N*/   {
/*N*/       mpRecordPortions = (void*)(new ImpRecordPortionListList(2, 2));
/*N*/       pListList = (ImpRecordPortionListList*)mpRecordPortions;
/*N*/   }
/*N*/
/*N*/   // create new portion
/*N*/   ImpRecordPortion* pNewPortion = new ImpRecordPortion(pInfo);
/*N*/
/*N*/   // look for the list where to insert new portion
/*N*/   ImpRecordPortionList* pList = 0L;
/*N*/
/*N*/   for(sal_uInt32 nListListIndex(0L); !pList && nListListIndex < pListList->Count(); nListListIndex++)
/*N*/   {
/*?*/       ImpRecordPortionList* pTmpList = pListList->GetObject(nListListIndex);
/*?*/
/*?*/       if(pTmpList->GetObject(0)->maPosition.Y() == pNewPortion->maPosition.Y())
/*?*/           pList = pTmpList;
/*N*/   }
/*N*/
/*N*/   if(!pList)
/*N*/   {
/*N*/       // no list for that Y-Coordinate yet, create a new one.
/*N*/       pList = new ImpRecordPortionList(8, 8);
/*N*/       pList->Insert(pNewPortion, LIST_APPEND);
/*N*/       pListList->Insert(pList, LIST_APPEND);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // found a list for that for that Y-Coordinate, sort in
/*?*/       sal_uInt32 nInsertInd(0L);
/*?*/
/*?*/       while(nInsertInd < pList->Count()
/*?*/           && pList->GetObject(nInsertInd)->maPosition.X() < pNewPortion->maPosition.X())
/*?*/       {
/*?*/           nInsertInd++;
/*?*/       }
/*?*/
/*?*/       if(nInsertInd == pList->Count())
/*?*/           nInsertInd = LIST_APPEND;
/*?*/
/*?*/       pList->Insert(pNewPortion, nInsertInd);
/*N*/   }
/*N*/ }

// #101498# Calculate complete length of FormTextPortions
/*N*/ sal_uInt32 ImpTextPortionHandler::GetFormTextPortionsLength(OutputDevice* pOut)
/*N*/ {
/*N*/   sal_uInt32 nRetval(0L);
/*N*/
/*N*/   ImpRecordPortionListList* pListList = (ImpRecordPortionListList*)mpRecordPortions;
/*N*/   if(pListList)
/*N*/   {
/*N*/       for(sal_uInt32 a(0L); a < pListList->Count(); a++)
/*N*/       {
/*N*/           ImpRecordPortionList* pList = pListList->GetObject(a);
/*N*/
/*N*/           for(sal_uInt32 b(0L); b < pList->Count(); b++)
/*N*/           {
/*N*/               ImpRecordPortion* pPortion = pList->GetObject(b);
/*N*/
/*N*/               if(pPortion->mpDXArray)
/*N*/               {
/*N*/                   if(pPortion->maFont.IsVertical() && pOut)
/*?*/                       nRetval += pOut->GetTextHeight() * pPortion->mnTextLength;
/*N*/                   else
/*N*/                       nRetval += pPortion->mpDXArray[pPortion->mnTextLength - 1];
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return nRetval;
/*N*/ }

// #101498# Cleanup recorded portions
/*N*/ void ImpTextPortionHandler::ClearFormTextRecordPortions()
/*N*/ {
/*N*/   ImpRecordPortionListList* pListList = (ImpRecordPortionListList*)mpRecordPortions;
/*N*/   if(pListList)
/*N*/   {
/*N*/       for(sal_uInt32 a(0L); a < pListList->Count(); a++)
/*N*/       {
/*N*/           ImpRecordPortionList* pList = pListList->GetObject(a);
/*N*/
/*N*/           for(sal_uInt32 b(0L); b < pList->Count(); b++)
/*N*/           {
/*N*/               delete pList->GetObject(b);
/*N*/           }
/*N*/
/*N*/           delete pList;
/*N*/       }
/*N*/
/*N*/       delete pListList;
/*N*/       mpRecordPortions = (void*)0L;
/*N*/   }
/*N*/ }

//STRIP001 IMPL_LINK(ImpTextPortionHandler,ConvertHdl,DrawPortionInfo*,pInfo)
//STRIP001 {
//STRIP001  // aFormTextBoundRect enthaelt den Ausgabebereich des Textobjekts
//STRIP001  BOOL bIsVertical(rOutliner.IsVertical());
//STRIP001  Point aPos(aFormTextBoundRect.TopLeft() + pInfo->rStartPos);
//STRIP001  Color aColor(pInfo->rFont.GetColor());
//STRIP001
//STRIP001  if(bIsVertical)
//STRIP001      aPos = aFormTextBoundRect.TopRight() + pInfo->rStartPos;
//STRIP001
//STRIP001  // #100318# new for XOutGetCharOutline
//STRIP001  // xub_StrLen nCnt = pInfo->nTextLen;
//STRIP001
//STRIP001  Point aStartPos(aPos);
//STRIP001  SfxItemSet aAttrSet((SfxItemPool&)(*rTextObj.GetItemPool()));
//STRIP001  long nHochTief(pInfo->rFont.GetEscapement());
//STRIP001  FontMetric aFontMetric(aVDev.GetFontMetric());
//STRIP001  sal_Int32 nLineLen(0L);
//STRIP001
//STRIP001  if(!nHochTief)
//STRIP001  {
//STRIP001      // Normalstellung
//STRIP001      aVDev.SetFont(pInfo->rFont);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Fuer Hoch-Tiefstellung den Font verkleinern
//STRIP001      long nPercent(pInfo->rFont.GetPropr());
//STRIP001
//STRIP001      if(nPercent != 100)
//STRIP001      {
//STRIP001          Font aFont(pInfo->rFont);
//STRIP001          Size aSize(aFont.GetSize());
//STRIP001
//STRIP001          aSize.Height() = (aSize.Height() * nPercent +50) / 100;
//STRIP001          aSize.Width() = (aSize.Width() * nPercent +50) / 100;
//STRIP001          aFont.SetSize(aSize);
//STRIP001          aVDev.SetFont(aFont);
//STRIP001      }
//STRIP001
//STRIP001      sal_Bool bNeg(nHochTief < 0);
//STRIP001
//STRIP001      if(bNeg)
//STRIP001          nHochTief = -nHochTief;
//STRIP001
//STRIP001      nHochTief = (nHochTief * pInfo->rFont.GetSize().Height() +50) /100;
//STRIP001
//STRIP001      if(bNeg)
//STRIP001          nHochTief = -nHochTief;
//STRIP001  }
//STRIP001
//STRIP001  if(bIsVertical)
//STRIP001      // #83068#
//STRIP001      aPos.X() += aFontMetric.GetAscent() + nHochTief;
//STRIP001  else
//STRIP001      aPos.Y() -= aFontMetric.GetAscent() + nHochTief;
//STRIP001
//STRIP001  if (pInfo->rFont.IsOutline())
//STRIP001  {
//STRIP001      aAttrSet.Put(XLineColorItem(String(),aColor));
//STRIP001      aAttrSet.Put(XLineStyleItem(XLINE_SOLID));
//STRIP001      aAttrSet.Put(XLineWidthItem(0));
//STRIP001      aAttrSet.Put(XFillStyleItem(XFILL_NONE));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aAttrSet.Put(XFillColorItem(String(),aColor));
//STRIP001      aAttrSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001      aAttrSet.Put(XFillStyleItem(XFILL_SOLID));
//STRIP001  }
//STRIP001
//STRIP001  // #100318# convert in a single step
//STRIP001  // #101499# Use GetTextOutlines and a PolyPolyVector now
//STRIP001  PolyPolyVector aPolyPolyVector;
//STRIP001
//STRIP001  if(aVDev.GetTextOutlines(aPolyPolyVector, pInfo->rText, pInfo->nTextStart, pInfo->nTextStart, pInfo->nTextLen)
//STRIP001      && aPolyPolyVector.size())
//STRIP001  {
//STRIP001      for(sal_uInt32 a(0); a < aPolyPolyVector.size(); a++)
//STRIP001      {
//STRIP001          PolyPolygon aPolyPoly(aPolyPolyVector[a]);
//STRIP001
//STRIP001          if(aPolyPoly.Count() > 0 && aPolyPoly[0].GetSize() > 0)
//STRIP001          {
//STRIP001
//STRIP001              XPolyPolygon aXPP(aPolyPoly);
//STRIP001
//STRIP001              // rotate 270 degree if vertical since result is unrotated
//STRIP001              if(bIsVertical)
//STRIP001                  aXPP.Rotate(Point(), 2700);
//STRIP001
//STRIP001              // result is baseline oriented, thus move one line height, too
//STRIP001              if(bIsVertical)
//STRIP001                  aXPP.Move(-aFontMetric.GetAscent(), 0);
//STRIP001              else
//STRIP001                  aXPP.Move(0, aFontMetric.GetAscent());
//STRIP001
//STRIP001              // move to output coordinates
//STRIP001              aXPP.Move(aPos.X(), aPos.Y());
//STRIP001              SdrObject* pObj = rTextObj.ImpConvertMakeObj(aXPP, TRUE, !bToPoly, TRUE);
//STRIP001
//STRIP001              pObj->SetItemSet(aAttrSet);
//STRIP001              pGroup->GetSubList()->InsertObject(pObj);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      nLineLen = pInfo->pDXArray[pInfo->nTextLen - 1];
//STRIP001  }
//STRIP001
//STRIP001  FontUnderline eUndl=pInfo->rFont.GetUnderline();
//STRIP001  FontStrikeout eStrk=pInfo->rFont.GetStrikeout();
//STRIP001  if (eUndl!=UNDERLINE_NONE) {
//STRIP001      FASTBOOL bDouble=eUndl==UNDERLINE_DOUBLE;
//STRIP001      long nDescent=aFontMetric.GetDescent();
//STRIP001      long nAscend=aFontMetric.GetAscent();
//STRIP001      long nDick=nDescent / (bDouble ? 5 : 3);
//STRIP001      long nDist=(nDescent-nDick*2)/3; // Linienabstand bei doppelt
//STRIP001
//STRIP001      XPolyPolygon aXPP;
//STRIP001      if (eUndl!=UNDERLINE_DOTTED) {
//STRIP001          Point aPoint(0,0);
//STRIP001          XPolygon aXP(Rectangle(aPoint,bIsVertical ? Point(nDick,nLineLen) : Point(nLineLen,nDick)));
//STRIP001          if(bIsVertical)
//STRIP001              aXP.Move(nAscend-nDist,0);
//STRIP001          aXPP.Insert(aXP);
//STRIP001          if (bDouble) {
//STRIP001              if(bIsVertical)
//STRIP001                  aXP.Move(-(nDick+nDist),0);
//STRIP001              else
//STRIP001                  aXP.Move(0,nDick+nDist);
//STRIP001              aXPP.Insert(aXP);
//STRIP001          }
//STRIP001      } else {
//STRIP001          Point aPoint(0,0);
//STRIP001          XPolygon aXP(Rectangle(aPoint,Point(nDick,nDick)));
//STRIP001          long n=0;
//STRIP001          while (n<=nLineLen) {
//STRIP001              if (n+nDick>nLineLen) { // ler letzte Dot ggf. etwas schmaler
//STRIP001                  aXP=XPolygon(Rectangle(
//STRIP001                      bIsVertical ? Point(0,n) : Point(n,0),
//STRIP001                      bIsVertical ? Point(nDick,nLineLen) : Point(nLineLen,nDick)));
//STRIP001              }
//STRIP001              aXPP.Insert(aXP);
//STRIP001              if(bIsVertical)
//STRIP001                  aXP.Move(0,2*nDick);
//STRIP001              else
//STRIP001                  aXP.Move(2*nDick,0);
//STRIP001              n+=2*nDick;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      long y=nDescent-nDick; // y-Position der Striche zur Baseline bestimmen
//STRIP001      if (bDouble) y-=nDick+nDist;
//STRIP001      y=(y+1)/2;
//STRIP001
//STRIP001      if(bIsVertical)
//STRIP001          aXPP.Move(aStartPos.X()-(y-nHochTief),aStartPos.Y());
//STRIP001      else
//STRIP001          aXPP.Move(aStartPos.X(),aStartPos.Y()+y-nHochTief);
//STRIP001      // aFormTextBoundRect enthaelt den Ausgabebereich des Textobjekts
//STRIP001      // #35825# Rotieren erst nach Resize (wg. FitToSize)
//STRIP001      //RotateXPoly(aXPP,aFormTextBoundRect.TopLeft(),rTextObj.aGeo.nSin,rTextObj.aGeo.nCos);
//STRIP001      SdrObject* pObj=rTextObj.ImpConvertMakeObj(aXPP,TRUE,!bToPoly, TRUE);
//STRIP001      pObj->SetItemSet(aAttrSet);
//STRIP001      pGroup->GetSubList()->InsertObject(pObj);
//STRIP001  }
//STRIP001  if (eStrk!=STRIKEOUT_NONE) {
//STRIP001      FASTBOOL bDouble=eStrk==STRIKEOUT_DOUBLE;
//STRIP001      long nDescent=aFontMetric.GetDescent();
//STRIP001      long nAscend=aFontMetric.GetAscent();
//STRIP001      long nDick=nDescent / (bDouble ? 5 : 3);
//STRIP001      long nDist=(nDescent-nDick*2)/3; // Linienabstand bei doppelt
//STRIP001
//STRIP001      XPolyPolygon aXPP;
//STRIP001      Point aPoint(0,0);
//STRIP001      XPolygon aXP(Rectangle(aPoint,bIsVertical ? Point(nDick,nLineLen) : Point(nLineLen,nDick)));
//STRIP001      aXPP.Insert(aXP);
//STRIP001      if (bDouble) {
//STRIP001          if(bIsVertical)
//STRIP001              aXP.Move(-(nDick+nDist),0);
//STRIP001          else
//STRIP001              aXP.Move(0,nDick+nDist);
//STRIP001          aXPP.Insert(aXP);
//STRIP001      }
//STRIP001
//STRIP001      // y-Position der Striche zur Baseline bestimmen
//STRIP001      long y=-(long)(aFontMetric.GetAscent()-aFontMetric.GetIntLeading()+1)/3;
//STRIP001      if (!bDouble) y-=(nDick+1)/2;
//STRIP001      else y-=nDick+(nDist+1)/2;
//STRIP001
//STRIP001      if(bIsVertical)
//STRIP001          aXPP.Move(aStartPos.X()-(y-nHochTief),aStartPos.Y());
//STRIP001      else
//STRIP001          aXPP.Move(aStartPos.X(),aStartPos.Y() +y-nHochTief);
//STRIP001      // aFormTextBoundRect enthaelt den Ausgabebereich des Textobjekts
//STRIP001      // #35825# Rotieren erst nach Resize (wg. FitToSize)
//STRIP001      //RotateXPoly(aXPP,aFormTextBoundRect.TopLeft(),rTextObj.aGeo.nSin,rTextObj.aGeo.nCos);
//STRIP001      SdrObject* pObj=rTextObj.ImpConvertMakeObj(aXPP,TRUE,!bToPoly, TRUE);
//STRIP001      pObj->SetItemSet(aAttrSet);
//STRIP001      pGroup->GetSubList()->InsertObject(pObj);
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void ImpTextPortionHandler::DrawFitText(ExtOutputDevice& rXOut, const Point& rPos, const Fraction& rXFact)
//STRIP001 {
//STRIP001  pXOut=&rXOut;
//STRIP001  aPos=rPos;
//STRIP001  aXFact=rXFact;
//STRIP001  rOutliner.SetDrawPortionHdl(LINK(this,ImpTextPortionHandler,FitTextDrawHdl));
//STRIP001  rOutliner.StripPortions();
//STRIP001  rOutliner.SetDrawPortionHdl(Link());
//STRIP001 }

//STRIP001 IMPL_LINK(ImpTextPortionHandler,FitTextDrawHdl,DrawPortionInfo*,pInfo)
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//IMPL_LINK(ImpTextPortionHandler, FormTextWidthHdl, DrawPortionInfo*, pInfo)
//{
//  // #101498# change calculation of nTextWidth
//  if(pInfo->nPara == nParagraph && pInfo->nTextLen)
//  {
//      // negative value is used because of the interface of
//      // XOutputDevice::ImpDrawFormText(...), please look there
//      // for more info.
//      nTextWidth -= pInfo->pDXArray[pInfo->nTextLen - 1];
//  }
//
//  return 0;
//}

//IMPL_LINK(ImpTextPortionHandler, FormTextDrawHdl, DrawPortionInfo*, pInfo)
//{
//  // #101498# Implementation of DrawFormText needs to be updated, too.
//  if(pInfo->nPara == nParagraph)
//  {
//      nTextWidth = pXOut->DrawFormText(pInfo, aPoly, nTextWidth, bToLastPoint, bDraw);
//          //pInfo->rText, aPoly, pInfo->rFont, nTextWidth,
//          //bToLastPoint, bDraw, pInfo->pDXArray);
//  }
//
//  return 0;
//}
}
