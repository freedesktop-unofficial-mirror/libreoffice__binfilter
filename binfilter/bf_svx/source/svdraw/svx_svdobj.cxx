/*************************************************************************
 *
 *  $RCSfile: svx_svdobj.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hjs $ $Date: 2004-06-28 12:34:03 $
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

#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#include <math.h>
#include <vcl/metaact.hxx>   // fuer TakeContour
#include <vcl/cvtsvm.hxx>
#include <tools/line.hxx>
#include <tools/bigint.hxx>
#include <vector>
#include "svdobj.hxx"
#include "xpoly.hxx"
#include "svdxout.hxx"
#include "svdetc.hxx"
#include "svdtrans.hxx"
#include "svdio.hxx"
#include "svdhdl.hxx"
#include "svddrag.hxx"
#include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svdovirt.hxx"  // Fuer Add/Del Ref
#include "svdpagv.hxx"   // fuer PaintGluePoints
#include "svdview.hxx"   // fuer Dragging (Ortho abfragen)
#include "svdscrol.hxx"
#include "svdglob.hxx"   // StringCache
#include "svdstr.hrc"    // Objektname
#include "svdogrp.hxx"   // Factory
#include "svdopath.hxx"  // Factory
#include "svdoedge.hxx"  // Factory
#include "svdorect.hxx"  // Factory
#include "svdocirc.hxx"  // Factory
#include "svdotext.hxx"  // Factory
#include "svdomeas.hxx"  // Factory
#include "svdograf.hxx"  // Factory
#include "svdoole2.hxx"  // Factory
#include "svdocapt.hxx"  // Factory
#include "svdopage.hxx"  // Factory
#include "svdouno.hxx"   // Factory
#include "svdattrx.hxx" // NotPersistItems

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "xlnwtit.hxx"
#include "xlnstwit.hxx"
#include "xlnedwit.hxx"
#include "xlnstit.hxx"
#include "xlnedit.hxx"
#include "xlnstcit.hxx"
#include "xlnedcit.hxx"
#include "xlndsit.hxx"
#include "xlnclit.hxx"
#include "xflclit.hxx"
#include "svditer.hxx"
#include "xlntrit.hxx"
#include "xfltrit.hxx"
#include "xfltrit.hxx"
#include "xflftrit.hxx"
#include "xlinjoit.hxx"
#include "unopage.hxx"
#include "eeitem.hxx"
#include "xenum.hxx"
#include "xgrad.hxx"
#include "xhatch.hxx"
#include "xflhtit.hxx"
#include "xbtmpit.hxx"

#ifndef _SVDPOOL_HXX
#include "svdpool.hxx"
#endif

#ifndef _MyEDITENG_HXX
#include "editeng.hxx"
#endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>     // FRound
#endif

#ifndef _SFX_WHITER_HXX
#include <svtools/whiter.hxx>
#endif

// #97849#
#ifndef _SVX_FMMODEL_HXX
#include "fmmodel.hxx"
#endif

#ifndef _SFX_OBJSH_HXX
#include <bf_sfx2/objsh.hxx>
#endif

#ifndef _SFXOBJFACE_HXX
#include <bf_sfx2/objface.hxx>
#endif

#ifndef _SVX_SVDOIMP_HXX
#include "svdoimp.hxx"
#endif

#ifndef _SVTOOLS_GRAPHICTOOLS_HXX_
#include <svtools/graphictools.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;

// #104018# replace macros above with type-detecting methods
inline double ImplTwipsToMM(double fVal) { return (fVal * (127.0 / 72.0)); }
inline double ImplMMToTwips(double fVal) { return (fVal * (72.0 / 127.0)); }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT0(SdrObjUserCall);

/*N*/ SdrObjUserCall::~SdrObjUserCall()
/*N*/ {
/*N*/ }

/*N*/ void SdrObjUserCall::Changed(const SdrObject& rObj, SdrUserCallType eType, const Rectangle& rOldBoundRect)
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT0(SdrObjUserData);

//STRIP001 void SdrObjUserData::operator=(const SdrObjUserData& rData)    // nicht implementiert
//STRIP001 {
//STRIP001 }

//STRIP001 FASTBOOL SdrObjUserData::operator==(const SdrObjUserData& rData) const // nicht implementiert
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 FASTBOOL SdrObjUserData::operator!=(const SdrObjUserData& rData) const // nicht implementiert
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ SdrObjUserData::~SdrObjUserData()
/*N*/ {
/*N*/ }

/*N*/ void SdrObjUserData::WriteData(SvStream& rOut)
/*N*/ {
/*N*/   rOut<<nInventor;
/*N*/   rOut<<nIdentifier;
/*N*/   rOut<<nVersion;
/*N*/ }

/*N*/ void SdrObjUserData::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   //Inventor und Identifier wurden bereits von Aufrufer gelesen,
/*N*/   //sonst haette er mich ja nicht erzeugen koennen (kein SeekBack!).
/*N*/   rIn>>nVersion; // Miniatur-Versionsverwaltung.
/*N*/ }

/*N*/ void SdrObjUserData::AfterRead()
/*N*/ {
/*N*/ }

/*N*/ FASTBOOL SdrObjUserData::HasMacro(const SdrObject* pObj) const
/*N*/ {
/*N*/   return FALSE;
/*N*/ }

//STRIP001 SdrObject* SdrObjUserData::CheckMacroHit(const SdrObjMacroHitRec& rRec, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  if (pObj==NULL) return NULL;
//STRIP001  return pObj->CheckHit(rRec.aPos,rRec.nTol,rRec.pVisiLayer);
//STRIP001 }

//STRIP001 Pointer SdrObjUserData::GetMacroPointer(const SdrObjMacroHitRec& rRec, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  return Pointer(POINTER_REFHAND);
//STRIP001 }

//STRIP001 void SdrObjUserData::PaintMacro(ExtOutputDevice& rXOut, const Rectangle& rDirtyRect, const SdrObjMacroHitRec& rRec, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  if (pObj==NULL) return;
//STRIP001  Color aBlackColor( COL_BLACK );
//STRIP001  Color aTranspColor( COL_TRANSPARENT );
//STRIP001  rXOut.OverrideLineColor( aBlackColor );
//STRIP001  rXOut.OverrideFillColor( aTranspColor );
//STRIP001  RasterOp eRop0=rXOut.GetRasterOp();
//STRIP001  rXOut.SetRasterOp(ROP_INVERT);
//STRIP001  XPolyPolygon aXPP;
//STRIP001  pObj->TakeXorPoly(aXPP,TRUE);
//STRIP001  USHORT nAnz=aXPP.Count();
//STRIP001  for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001      rXOut.DrawXPolyLine(aXPP[nNum]);
//STRIP001  }
//STRIP001  rXOut.SetRasterOp(eRop0);
//STRIP001 }

//STRIP001 FASTBOOL SdrObjUserData::DoMacro(const SdrObjMacroHitRec& rRec, SdrObject* pObj)
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 XubString SdrObjUserData::GetMacroPopupComment(const SdrObjMacroHitRec& rRec, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

/*N*/ void SdrObjUserDataList::Clear()
/*N*/ {
/*N*/   USHORT nAnz=GetUserDataCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       delete GetUserData(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ DBG_NAME(SdrObjGeoData)

/*N*/ SdrObjGeoData::SdrObjGeoData():
/*N*/   pGPL(NULL),
/*N*/   bMovProt(FALSE),
/*N*/   bSizProt(FALSE),
/*N*/   bNoPrint(FALSE),
/*N*/   bClosedObj(FALSE),
/*N*/   nLayerId(0)
/*N*/ {
/*N*/   DBG_CTOR(SdrObjGeoData,NULL);
/*N*/ }

/*N*/ SdrObjGeoData::~SdrObjGeoData()
/*N*/ {
/*N*/   DBG_DTOR(SdrObjGeoData,NULL);
/*N*/   delete pGPL;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT0(SdrObjPlusData);

/*N*/ SdrObjPlusData::SdrObjPlusData():
/*N*/   pBroadcast(NULL),
/*N*/   pUserDataList(NULL),
/*N*/   pGluePoints(NULL),
///*N*/     pAnimator(NULL),
/*N*/   pAutoTimer(NULL)
/*N*/ {
/*N*/ }

/*N*/ SdrObjPlusData::~SdrObjPlusData()
/*N*/ {
/*N*/   if (pBroadcast   !=NULL) delete pBroadcast;
/*N*/   if (pUserDataList!=NULL) delete pUserDataList;
/*N*/   if (pGluePoints  !=NULL) delete pGluePoints;
///*N*/     if (pAnimator    !=NULL) delete pAnimator;
/*N*/   if (pAutoTimer   !=NULL) delete pAutoTimer;
/*N*/ }

//STRIP001 SdrObjPlusData* SdrObjPlusData::Clone(SdrObject* pObj1) const
//STRIP001 {
//STRIP001  SdrObjPlusData* pNeuPlusData=new SdrObjPlusData;
//STRIP001  if (pUserDataList!=NULL) {
//STRIP001      USHORT nAnz=pUserDataList->GetUserDataCount();
//STRIP001      if (nAnz!=0) {
//STRIP001          pNeuPlusData->pUserDataList=new SdrObjUserDataList;
//STRIP001          for (USHORT i=0; i<nAnz; i++) {
//STRIP001              SdrObjUserData* pNeuUserData=pUserDataList->GetUserData(i)->Clone(pObj1);
//STRIP001              if (pNeuUserData!=NULL) {
//STRIP001                  pNeuPlusData->pUserDataList->InsertUserData(pNeuUserData);
//STRIP001              } else {
//STRIP001                  DBG_ERROR("SdrObjPlusData::Clone(): UserData.Clone() liefert NULL");
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (pGluePoints!=NULL) pNeuPlusData->pGluePoints=new SdrGluePointList(*pGluePoints);
//STRIP001  // MtfAnimator wird auch nicht mitkopiert
//STRIP001  pNeuPlusData->aObjName=aObjName;
//STRIP001  if (pAutoTimer!=NULL) {
//STRIP001      pNeuPlusData->pAutoTimer=new AutoTimer;
//STRIP001      // Handler, etc. nicht mitkopieren!
//STRIP001  }
//STRIP001
//STRIP001  // For HTMLName: Do not clone, leave uninitialized (empty string)
//STRIP001
//STRIP001  return pNeuPlusData;
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

static double SMALLEST_DASH_WIDTH(26.95);

/*N*/ ImpLineStyleParameterPack::ImpLineStyleParameterPack(const SfxItemSet& rSet,
/*N*/   BOOL _bForceHair, OutputDevice* pOut)
/*N*/ : mpOut(pOut),
/*N*/   rStartPolygon(((const XLineStartItem&)(rSet.Get(XATTR_LINESTART))).GetValue()),
/*N*/   rEndPolygon(((const XLineEndItem&)(rSet.Get(XATTR_LINEEND))).GetValue()),
/*N*/   bForceNoArrowsLeft(FALSE),
/*N*/   bForceNoArrowsRight(FALSE),
/*N*/     bForceHair(_bForceHair)
/*N*/ {
/*N*/     // #i12227# now storing the real line width, not corrected by
/*N*/     // bForceHair. This is done within the GetDisplay*Width accessors,
/*N*/     // and preserves the true value for the Get*Width accessors.
/*N*/   nLineWidth = ((const XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue();
/*N*/   eLineStyle = (XLineStyle)((const XLineStyleItem&)rSet.Get(XATTR_LINESTYLE)).GetValue();
/*N*/
/*N*/   nStartWidth = ((const XLineStartWidthItem&)(rSet.Get(XATTR_LINESTARTWIDTH))).GetValue();
/*N*/   if(nStartWidth < 0)
/*N*/       nStartWidth = -nLineWidth * nStartWidth / 100;
/*N*/
/*N*/   nEndWidth = ((const XLineEndWidthItem&)(rSet.Get(XATTR_LINEENDWIDTH))).GetValue();
/*N*/   if(nEndWidth < 0)
/*N*/       nEndWidth = -nLineWidth * nEndWidth / 100;
/*N*/
/*N*/   bStartCentered = ((const XLineStartCenterItem&)(rSet.Get(XATTR_LINESTARTCENTER))).GetValue();
/*N*/   bEndCentered = ((const XLineEndCenterItem&)(rSet.Get(XATTR_LINEENDCENTER))).GetValue();
/*N*/
/*N*/   fDegreeStepWidth = 10.0;
/*N*/   eLineJoint = ((const XLineJointItem&)(rSet.Get(XATTR_LINEJOINT))).GetValue();
/*N*/
/*N*/   aDash = ((const XLineDashItem&)(rSet.Get(XATTR_LINEDASH))).GetValue();
/*N*/
/*N*/   // fill local dash info
/*N*/   UINT16 nNumDotDashArray = (GetDots() + GetDashes()) * 2;
/*N*/   aDotDashArray.resize( nNumDotDashArray, 0.0 );
/*N*/   UINT16 a;
/*N*/   UINT16 nIns = 0;
/*N*/   double fDashDotDistance = (double)GetDashDistance();
/*N*/   double fSingleDashLen = (double)GetDashLen();
/*N*/   double fSingleDotLen = (double)GetDotLen();
/*N*/   double fLineWidth = (double)GetDisplayLineWidth();
/*N*/
/*N*/   if(GetDashStyle() == XDASH_RECTRELATIVE || GetDashStyle() == XDASH_ROUNDRELATIVE)
/*?*/   {
/*?*/       if(GetDisplayLineWidth())
/*?*/       {
/*?*/           double fFactor = fLineWidth / 100.0;
/*?*/
/*?*/           if(GetDashes())
/*?*/           {
/*?*/               if(GetDashLen())
/*?*/               {
/*?*/                   // is a dash
/*?*/                   fSingleDashLen *= fFactor;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   // is a dot
/*?*/                   fSingleDashLen = fLineWidth;
/*?*/               }
/*?*/           }
/*?*/
/*?*/           if(GetDots())
/*?*/           {
/*?*/               if(GetDotLen())
/*?*/               {
/*?*/                   // is a dash
/*?*/                   fSingleDotLen *= fFactor;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   // is a dot
/*?*/                   fSingleDotLen = fLineWidth;
/*?*/               }
/*?*/           }
/*?*/
/*?*/           if(GetDashes() || GetDots())
/*?*/           {
/*?*/               if(GetDashDistance())
/*?*/                   fDashDotDistance *= fFactor;
/*?*/               else
/*?*/                   fDashDotDistance = fLineWidth;
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           if(GetDashes())
/*?*/           {
/*?*/               if(GetDashLen())
/*?*/               {
/*?*/                   // is a dash
/*?*/                   fSingleDashLen = (SMALLEST_DASH_WIDTH * fSingleDashLen) / 100.0;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   // is a dot
/*?*/                   fSingleDashLen = SMALLEST_DASH_WIDTH;
/*?*/               }
/*?*/           }
/*?*/
/*?*/           if(GetDots())
/*?*/           {
/*?*/               if(GetDotLen())
/*?*/               {
/*?*/                   // is a dash
/*?*/                   fSingleDotLen = (SMALLEST_DASH_WIDTH * fSingleDotLen) / 100.0;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   // is a dot
/*?*/                   fSingleDotLen = SMALLEST_DASH_WIDTH;
/*?*/               }
/*?*/           }
/*?*/
/*?*/           if(GetDashes() || GetDots())
/*?*/           {
/*?*/               if(GetDashDistance())
/*?*/               {
/*?*/                   // dash as distance
/*?*/                   fDashDotDistance = (SMALLEST_DASH_WIDTH * fDashDotDistance) / 100.0;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   // dot as distance
/*?*/                   fDashDotDistance = SMALLEST_DASH_WIDTH;
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/   }
/*N*/   else
/*N*/   {
/*N*/       // smallest dot size compare value
/*N*/       double fDotCompVal(GetDisplayLineWidth() ? fLineWidth : SMALLEST_DASH_WIDTH);
/*N*/
/*N*/       // absolute values
/*N*/       if(GetDashes())
/*N*/       {
/*N*/           if(GetDashLen())
/*N*/           {
/*N*/               // is a dash
/*N*/               if(fSingleDashLen < SMALLEST_DASH_WIDTH)
/*N*/                   fSingleDashLen = SMALLEST_DASH_WIDTH;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // is a dot
/*?*/               if(fSingleDashLen < fDotCompVal)
/*?*/                   fSingleDashLen = fDotCompVal;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if(GetDots())
/*N*/       {
/*N*/           if(GetDotLen())
/*N*/           {
/*N*/               // is a dash
/*N*/               if(fSingleDotLen < SMALLEST_DASH_WIDTH)
/*N*/                   fSingleDotLen = SMALLEST_DASH_WIDTH;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // is a dot
/*?*/               if(fSingleDotLen < fDotCompVal)
/*?*/                   fSingleDotLen = fDotCompVal;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if(GetDashes() || GetDots())
/*N*/       {
/*N*/           if(GetDashDistance())
/*N*/           {
/*N*/               // dash as distance
/*N*/               if(fDashDotDistance < SMALLEST_DASH_WIDTH)
/*N*/                   fDashDotDistance = SMALLEST_DASH_WIDTH;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // dot as distance
/*?*/               if(fDashDotDistance < fDotCompVal)
/*?*/                   fDashDotDistance = fDotCompVal;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   fFullDashDotLen = 0.0;
/*N*/
/*N*/   for(a=0;a<GetDots();a++)
/*N*/   {
/*N*/       aDotDashArray[nIns++] = fSingleDotLen;
/*N*/       fFullDashDotLen += fSingleDotLen;
/*N*/       aDotDashArray[nIns++] = fDashDotDistance;
/*N*/       fFullDashDotLen += fDashDotDistance;
/*N*/   }
/*N*/
/*N*/   for(a=0;a<GetDashes();a++)
/*N*/   {
/*N*/       aDotDashArray[nIns++] = fSingleDashLen;
/*N*/       fFullDashDotLen += fSingleDashLen;
/*N*/       aDotDashArray[nIns++] = fDashDotDistance;
/*N*/       fFullDashDotLen += fDashDotDistance;
/*N*/   }
/*N*/ }

/*N*/ ImpLineStyleParameterPack::~ImpLineStyleParameterPack()
/*N*/ {
/*N*/ }

/*N*/ UINT16 ImpLineStyleParameterPack::GetFirstDashDotIndex(double fPos, double& rfDist) const
/*N*/ {
/*N*/   double fIndPos = fPos - (fFullDashDotLen * (double)((UINT32)(fPos / fFullDashDotLen)));
/*N*/   UINT16 nPos = 0;
/*N*/
/*N*/   while(fIndPos && fIndPos - aDotDashArray[nPos] > -SMALL_DVALUE)
/*N*/   {
/*N*/       fIndPos -= aDotDashArray[nPos];
/*N*/       nPos = (static_cast< size_t >(nPos + 1) == aDotDashArray.size()) ? 0 : nPos + 1;
/*N*/   }
/*N*/
/*N*/   rfDist = aDotDashArray[nPos] - fIndPos;
/*N*/   nPos = (static_cast< size_t >(nPos + 1) == aDotDashArray.size()) ? 0 : nPos + 1;
/*N*/
/*N*/   return nPos;
/*N*/ }

/*N*/ UINT16 ImpLineStyleParameterPack::GetNextDashDotIndex(UINT16 nPos, double& rfDist) const
/*N*/ {
/*N*/   rfDist = aDotDashArray[nPos];
/*N*/   nPos = (static_cast< size_t >(nPos + 1) == aDotDashArray.size()) ? 0 : nPos + 1;
/*N*/   return nPos;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ double ImpLineGeometryCreator::ImpSimpleFindCutPoint(
/*N*/   const Vector3D& rEdge1Start, const Vector3D& rEdge1Delta,
/*N*/   const Vector3D& rEdge2Start, const Vector3D& rEdge2Delta)
/*N*/ {
/*N*/   double fZwi = (rEdge1Delta.X() * rEdge2Delta.Y()) - (rEdge1Delta.Y() * rEdge2Delta.X());
/*N*/   double fRetval = 0.0;
/*N*/
/*N*/   if(fabs(fZwi) > SMALL_DVALUE)
/*N*/   {
/*N*/       fRetval = (rEdge2Delta.Y() * (rEdge2Start.X() - rEdge1Start.X())
/*N*/           + rEdge2Delta.X() * (rEdge1Start.Y() - rEdge2Start.Y())) / fZwi;
/*N*/   }
/*N*/   return fRetval;
/*N*/ }

/*N*/ void ImpLineGeometryCreator::ImpCreateLineSegment(const Vector3D* pPrev, const Vector3D* pLeft, const Vector3D* pRight, const Vector3D* pNext)
/*N*/ {
/*N*/   if(mrLineAttr.GetDisplayLineWidth())
/*N*/   {
/*N*/       double fHalfLineWidth((double)mrLineAttr.GetDisplayLineWidth() / 2.0);
/*N*/       Vector3D aEdge = *pRight - *pLeft;
/*N*/
/*N*/       // #78972#
/*N*/       Vector3D aPerpend(-aEdge.Y(), aEdge.X(), 0.0);
/*N*/       aPerpend.Normalize();
/*N*/
/*N*/       XLineJoint eJoint = mrLineAttr.GetLineJoint();
/*N*/
/*N*/       // joints need eventually not be done
/*N*/       if((eJoint == XLINEJOINT_MIDDLE || eJoint == XLINEJOINT_MITER) && (!pPrev && !pNext))
/*N*/           eJoint = XLINEJOINT_NONE;
/*N*/
/*N*/       switch(eJoint)
/*N*/       {
/*?*/           case XLINEJOINT_NONE:       // no rounding
/*?*/           {
/*?*/               Polygon3D aNewPoly(4);
/*?*/
/*?*/               aPerpend *= fHalfLineWidth;
/*?*/               aNewPoly[0] = *pLeft + aPerpend;
/*?*/               aNewPoly[1] = *pRight + aPerpend;
/*?*/               aNewPoly[2] = *pRight - aPerpend;
/*?*/               aNewPoly[3] = *pLeft - aPerpend;
/*?*/
/*?*/               aNewPoly.SetClosed(TRUE);
/*?*/               mrPolyPoly3D.Insert(aNewPoly);
/*?*/
/*?*/               break;
/*?*/           }
/*?*/           case XLINEJOINT_MIDDLE:     // calc middle value between joints
/*?*/           {
/*?*/               Polygon3D aNewPoly(4);
/*?*/               Vector3D aPerpendLeft(aPerpend);
/*?*/               Vector3D aPerpendRight(aPerpend);
/*?*/
/*?*/               if(pPrev)
/*?*/               {
/*?*/                   aPerpendLeft = *pLeft - *pPrev;
/*?*/
/*?*/                   // #78972#
/*?*/                   aPerpendLeft = Vector3D(-aPerpendLeft.Y(), aPerpendLeft.X(), 0.0);
/*?*/                   aPerpendLeft.Normalize();
/*?*/               }
/*?*/
/*?*/               if(pNext)
/*?*/               {
/*?*/                   aPerpendRight = *pNext - *pRight;
/*?*/
/*?*/                   // #78972#
/*?*/                   aPerpendRight = Vector3D(-aPerpendRight.Y(), aPerpendRight.X(), 0.0);
/*?*/                   aPerpendRight.Normalize();
/*?*/               }
/*?*/
/*?*/               aPerpendLeft = (aPerpend + aPerpendLeft) * (fHalfLineWidth / 2.0);
/*?*/               aPerpendRight = (aPerpend + aPerpendRight) * (fHalfLineWidth / 2.0);
/*?*/
/*?*/               aNewPoly[0] = *pLeft + aPerpendLeft;
/*?*/               aNewPoly[1] = *pRight + aPerpendRight;
/*?*/               aNewPoly[2] = *pRight - aPerpendRight;
/*?*/               aNewPoly[3] = *pLeft - aPerpendLeft;
/*?*/
/*?*/               aNewPoly.SetClosed(TRUE);
/*?*/               mrPolyPoly3D.Insert(aNewPoly);
/*?*/
/*?*/               break;
/*?*/           }
/*N*/           case XLINEJOINT_BEVEL:      // join edges with line
/*N*/           default: // #73428# case XLINEJOINT_ROUND:      // create arc
/*N*/           {
/*N*/               Vector3D aPerpendRight(aPerpend);
/*N*/               BOOL bCreateSimplePart(TRUE);
/*N*/
/*N*/               if(pNext)
/*N*/               {
/*N*/                   aPerpendRight = *pNext - *pRight;
/*N*/
/*N*/                   // #78972#
/*N*/                   aPerpendRight = Vector3D(-aPerpendRight.Y(), aPerpendRight.X(), 0.0);
/*N*/                   aPerpendRight.Normalize();
/*N*/
/*N*/                   double fAngle = atan2(aPerpend.Y(), aPerpend.X());
/*N*/                   double fRightAngle = atan2(aPerpendRight.Y(), aPerpendRight.X());
/*N*/                   double fAngleDiff = fAngle - fRightAngle;
/*N*/                   double fDegreeStepWidth = mrLineAttr.GetDegreeStepWidth() * F_PI180;
/*N*/
/*N*/                   // go to range [0.0..2*F_PI[
/*N*/                   while(fAngleDiff < 0.0)
/*N*/                       fAngleDiff += (F_PI * 2.0);
/*N*/                   while(fAngleDiff >= (F_PI * 2.0))
/*N*/                       fAngleDiff -= (F_PI * 2.0);
/*N*/
/*N*/                   if((fAngleDiff > fDegreeStepWidth) && (fAngleDiff < ((F_PI * 2.0) - fDegreeStepWidth)))
/*N*/                   {
/*N*/                       bCreateSimplePart = FALSE;
/*N*/                       aPerpend *= fHalfLineWidth;
/*N*/                       aPerpendRight *= fHalfLineWidth;
/*N*/
/*N*/                       if(eJoint == XLINEJOINT_BEVEL)
/*?*/                       {
/*?*/                           UINT16 nPolyPoints(pPrev ? 7 : 6);
/*?*/                           Polygon3D aNewPoly(nPolyPoints);
/*?*/
/*?*/                           aNewPoly[0] = *pLeft + aPerpend;
/*?*/                           aNewPoly[1] = *pRight + aPerpend;
/*?*/                           aNewPoly[4] = *pRight - aPerpend;
/*?*/                           aNewPoly[5] = *pLeft - aPerpend;
/*?*/
/*?*/                           if(pPrev)
/*?*/                               aNewPoly[6] = *pLeft;
/*?*/
/*?*/                           if(fAngleDiff > F_PI)
/*?*/                           {
/*?*/                               // lower side
/*?*/                               aNewPoly[2] = *pRight;
/*?*/                               aNewPoly[3] = *pRight - aPerpendRight;
/*?*/                           }
/*?*/                           else
/*?*/                           {
/*?*/                               // upper side
/*?*/                               aNewPoly[2] = *pRight + aPerpendRight;
/*?*/                               aNewPoly[3] = *pRight;
/*?*/                           }
/*?*/
/*?*/                           aNewPoly.SetClosed(TRUE);
/*?*/                           mrPolyPoly3D.Insert(aNewPoly);
/*?*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           BOOL bUseLowerSide(fAngleDiff > F_PI);
/*N*/                           UINT16 nSegments;
/*N*/
/*N*/                           if(bUseLowerSide)
/*N*/                           {
/*?*/                               fAngleDiff = (F_PI * 2.0) - fAngleDiff;
/*?*/                               nSegments = (UINT16)(fAngleDiff / fDegreeStepWidth);
/*N*/                           }
/*N*/                           else
/*N*/                           {
/*N*/                               nSegments = (UINT16)(fAngleDiff / fDegreeStepWidth);
/*N*/                           }
/*N*/
/*N*/                           UINT16 nPolyPoints(pPrev ? 7 : 6);
/*N*/                           Polygon3D aNewPoly(nPolyPoints + nSegments);
/*N*/
/*N*/                           aNewPoly[0] = *pLeft + aPerpend;
/*N*/                           aNewPoly[1] = *pRight + aPerpend;
/*N*/                           aNewPoly[4 + nSegments] = *pRight - aPerpend;
/*N*/                           aNewPoly[5 + nSegments] = *pLeft - aPerpend;
/*N*/
/*N*/                           if(pPrev)
/*N*/                               aNewPoly[6 + nSegments] = *pLeft;
/*N*/
/*N*/                           fAngleDiff /= (double)(nSegments + 1);
/*N*/
/*N*/                           if(bUseLowerSide)
/*N*/                           {
/*N*/                               // lower side
/*?*/                               aNewPoly[2] = *pRight;
/*?*/                               aNewPoly[3] = *pRight - aPerpendRight;
/*?*/
/*?*/                               for(UINT16 a=0;a<nSegments;a++)
/*?*/                               {
/*?*/                                   double fDegree = fRightAngle - (double)a * fAngleDiff;
/*?*/                                   Vector3D aNewPos(
/*?*/                                       pRight->X() - (cos(fDegree) * fHalfLineWidth),
/*?*/                                       pRight->Y() - (sin(fDegree) * fHalfLineWidth),
/*?*/                                       pRight->Z()); // #78972#
/*?*/                                   aNewPoly[4 + a] = aNewPos;
/*N*/                               }
/*N*/                           }
/*N*/                           else
/*N*/                           {
/*N*/                               // upper side
/*N*/                               aNewPoly[2 + nSegments] = *pRight + aPerpendRight;
/*N*/                               aNewPoly[3 + nSegments] = *pRight;
/*N*/
/*N*/                               for(UINT16 a=0;a<nSegments;a++)
/*N*/                               {
/*N*/                                   double fDegree = fAngle - (double)a * fAngleDiff;
/*N*/                                   Vector3D aNewPos(
/*N*/                                       pRight->X() + (cos(fDegree) * fHalfLineWidth),
/*N*/                                       pRight->Y() + (sin(fDegree) * fHalfLineWidth),
/*N*/                                       pRight->Z()); // #78972#
/*N*/                                   aNewPoly[2 + a] = aNewPos;
/*N*/                               }
/*N*/                           }
/*N*/
/*N*/                           aNewPoly.SetClosed(TRUE);
/*N*/                           mrPolyPoly3D.Insert(aNewPoly);
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               if(bCreateSimplePart)
/*N*/               {
/*N*/                   // angle smaller DegreeStepWidth, create simple segment
/*N*/                   UINT16 nNumPnt(4);
/*N*/
/*N*/                   if(pPrev)
/*N*/                       nNumPnt++;
/*N*/
/*N*/                   if(pNext)
/*N*/                       nNumPnt++;
/*N*/
/*N*/                   Polygon3D aNewPoly(nNumPnt);
/*N*/
/*N*/                   aPerpend *= fHalfLineWidth;
/*N*/                   aPerpendRight *= fHalfLineWidth;
/*N*/                   nNumPnt = 0;
/*N*/
/*N*/                   if(pPrev)
/*N*/                       aNewPoly[nNumPnt++] = *pLeft;
/*N*/
/*N*/                   aNewPoly[nNumPnt++] = *pLeft + aPerpend;
/*N*/                   aNewPoly[nNumPnt++] = *pRight + aPerpendRight;
/*N*/
/*N*/                   if(pNext)
/*N*/                       aNewPoly[nNumPnt++] = *pRight;
/*N*/
/*N*/                   aNewPoly[nNumPnt++] = *pRight - aPerpendRight;
/*N*/                   aNewPoly[nNumPnt++] = *pLeft - aPerpend;
/*N*/
/*N*/                   aNewPoly.SetClosed(TRUE);
/*N*/                   mrPolyPoly3D.Insert(aNewPoly);
/*N*/               }
/*N*/
/*N*/               break;
/*N*/           }
/*N*/           case XLINEJOINT_MITER:      // extend till cut
/*?*/           {
/*?*/               Polygon3D aNewPoly(4);
/*?*/               aPerpend *= fHalfLineWidth;
/*?*/               BOOL bLeftSolved(FALSE);
/*?*/               BOOL bRightSolved(FALSE);
/*?*/
/*?*/               if(pPrev)
/*?*/               {
/*?*/                   Vector3D aLeftVec(*pLeft - *pPrev);
/*?*/
/*?*/                   // #78972#
/*?*/                   Vector3D aPerpendLeft(-aLeftVec.Y(), aLeftVec.X(), 0.0);
/*?*/                   aPerpendLeft.Normalize();
/*?*/
/*?*/                   aPerpendLeft *= fHalfLineWidth;
/*?*/                   double fUpperCut = ImpSimpleFindCutPoint(*pPrev + aPerpendLeft, aLeftVec, *pRight + aPerpend, -aEdge);
/*?*/
/*?*/                   if(fUpperCut != 0.0 && fUpperCut < mrLineAttr.GetLinejointMiterUpperBound())
/*?*/                   {
/*?*/                       double fLowerCut = ImpSimpleFindCutPoint(*pPrev - aPerpendLeft, aLeftVec, *pRight - aPerpend, -aEdge);
/*?*/
/*?*/                       if(fLowerCut < mrLineAttr.GetLinejointMiterUpperBound())
/*?*/                       {
/*?*/                           Vector3D aParam1 = *pPrev + aPerpendLeft;
/*?*/                           Vector3D aParam2 = *pLeft + aPerpendLeft;
/*?*/                           aNewPoly[0].CalcInBetween(aParam1, aParam2, fUpperCut);
/*?*/                           aParam1 = *pPrev - aPerpendLeft;
/*?*/                           aParam2 = *pLeft - aPerpendLeft;
/*?*/                           aNewPoly[3].CalcInBetween(aParam1, aParam2, fLowerCut);
/*?*/                           bLeftSolved = TRUE;
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/               if(!bLeftSolved)
/*?*/               {
/*?*/                   aNewPoly[0] = *pLeft + aPerpend;
/*?*/                   aNewPoly[3] = *pLeft - aPerpend;
/*?*/               }
/*?*/
/*?*/               if(pNext)
/*?*/               {
/*?*/                   Vector3D aRightVec(*pRight - *pNext);
/*?*/                   Vector3D aPerpendRight = -aRightVec;
/*?*/
/*?*/                   // #78972#
/*?*/                   aPerpendRight = Vector3D(-aPerpendRight.Y(), aPerpendRight.X(), 0.0);
/*?*/                   aPerpendRight.Normalize();
/*?*/
/*?*/                   aPerpendRight *= fHalfLineWidth;
/*?*/                   double fUpperCut = ImpSimpleFindCutPoint(*pNext + aPerpendRight, aRightVec, *pRight + aPerpend, aEdge);
/*?*/
/*?*/                   if(fUpperCut != 0.0 && fUpperCut < mrLineAttr.GetLinejointMiterUpperBound())
/*?*/                   {
/*?*/                       double fLowerCut = ImpSimpleFindCutPoint(*pNext - aPerpendRight, aRightVec, *pRight - aPerpend, aEdge);
/*?*/
/*?*/                       if(fLowerCut < mrLineAttr.GetLinejointMiterUpperBound())
/*?*/                       {
/*?*/                           Vector3D aParam1 = *pNext + aPerpendRight;
/*?*/                           Vector3D aParam2 = *pRight + aPerpendRight;
/*?*/                           aNewPoly[1].CalcInBetween(aParam1, aParam2, fUpperCut);
/*?*/                           aParam1 = *pNext - aPerpendRight;
/*?*/                           aParam2 = *pRight - aPerpendRight;
/*?*/                           aNewPoly[2].CalcInBetween(aParam1, aParam2, fLowerCut);
/*?*/                           bRightSolved = TRUE;
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/               if(!bRightSolved)
/*?*/               {
/*?*/                   aNewPoly[1] = *pRight + aPerpend;
/*?*/                   aNewPoly[2] = *pRight - aPerpend;
/*?*/               }
/*?*/
/*?*/               aNewPoly.SetClosed(TRUE);
/*?*/               mrPolyPoly3D.Insert(aNewPoly);
/*?*/
/*?*/               break;
/*?*/           }
/*?*/       }
/*?*/   }
/*N*/   else
/*N*/   {
/*?*/       Polygon3D aNewPoly(2);
/*?*/
/*?*/       aNewPoly[0] = *pLeft;
/*?*/       aNewPoly[1] = *pRight;
/*?*/
/*?*/       aNewPoly.SetClosed(FALSE);
/*?*/       mrPolyLine3D.Insert(aNewPoly);
/*N*/   }
/*N*/ }

/*N*/ void ImpLineGeometryCreator::ImpCreateSegmentsForLine(const Vector3D* pPrev, const Vector3D* pLeft, const Vector3D* pRight, const Vector3D* pNext, double fPolyPos)
/*N*/ {
/*N*/   Vector3D aEdge(*pRight - *pLeft);
/*N*/   double fLen = aEdge.GetLength();
/*N*/   double fPos = 0.0;
/*N*/   double fDist;
/*N*/   BOOL bFirst(TRUE);
/*N*/   BOOL bLast(FALSE);
/*N*/   UINT16 nInd = mrLineAttr.GetFirstDashDotIndex(fPolyPos, fDist);
/*N*/
/*N*/   do {
/*N*/       // nInd right edge, fDist to it
/*N*/       if((nInd % 2) && fDist > SMALL_DVALUE)
/*N*/       {
/*N*/           // left is fpos, get right
/*N*/           double fRight = fPos + fDist;
/*N*/
/*N*/           if(fRight > fLen)
/*N*/           {
/*N*/               fRight = fLen;
/*N*/               bLast = TRUE;
/*N*/           }
/*N*/
/*N*/           // create segment from fPos to fRight
/*N*/           Vector3D aLeft(*pLeft);
/*N*/           Vector3D aRight(*pRight);
/*N*/
/*N*/           if(!bFirst)
/*N*/               aLeft.CalcInBetween(*pLeft, *pRight, fPos / fLen);
/*N*/           if(!bLast)
/*N*/               aRight.CalcInBetween(*pLeft, *pRight, fRight / fLen);
/*N*/
/*N*/           ImpCreateLineSegment(bFirst ? pPrev : 0L, &aLeft, &aRight, bLast ? pNext : 0L);
/*N*/       }
/*N*/
/*N*/       bFirst = FALSE;
/*N*/       fPos += fDist;
/*N*/       nInd = mrLineAttr.GetNextDashDotIndex(nInd, fDist);
/*N*/   } while(fPos < fLen);
/*N*/ }

/*N*/ double ImpLineGeometryCreator::ImpCreateLineStartEnd(Polygon3D& rArrowPoly, const Polygon3D& rSourcePoly, BOOL bFront, double fWantedWidth, BOOL bCentered)
/*N*/ {
/*N*/   double fRetval(0.0);
/*N*/   double fOffset(0.0);
/*N*/   Volume3D aPolySize(rArrowPoly.GetPolySize());
/*N*/   double fScaleValue(fWantedWidth / aPolySize.GetWidth());
/*N*/   Matrix4D aTrans;
/*N*/   Vector3D aCenter;
/*N*/
/*N*/   if(bCentered)
/*N*/   {
/*N*/       aCenter = Vector3D(
/*N*/           (aPolySize.MinVec().X() + aPolySize.MaxVec().X()) / 2.0,
/*N*/           (aPolySize.MinVec().Y() + aPolySize.MaxVec().Y()) / 2.0, 0.0);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aCenter = Vector3D(rArrowPoly.GetMiddle());
/*N*/   }
/*N*/
/*N*/   aTrans.Translate(-aCenter);
/*N*/   aTrans.Scale(fScaleValue, fScaleValue, fScaleValue);
/*N*/
/*N*/   if(bCentered)
/*N*/   {
/*N*/       Vector3D aLowerCenter(aCenter.X(), aPolySize.MinVec().Y(), 0.0);
/*N*/
/*N*/       aLowerCenter *= aTrans;
/*N*/       aCenter *= aTrans;
/*N*/       fOffset = (aCenter - aLowerCenter).GetLength();
/*N*/       fRetval = fOffset / 2.0;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       Vector3D aLowerCenter(aCenter.X(), aPolySize.MinVec().Y(), 0.0);
/*N*/       Vector3D aUpperCenter(aCenter.X(), aPolySize.MaxVec().Y(), 0.0);
/*N*/
/*N*/       aUpperCenter *= aTrans;
/*N*/       aLowerCenter *= aTrans;
/*N*/       fOffset = (aUpperCenter - aLowerCenter).GetLength();
/*N*/       fRetval = fOffset * 0.8;
/*N*/   }
/*N*/
/*N*/   Vector3D aHead = (bFront) ? rSourcePoly[0] : rSourcePoly[rSourcePoly.GetPointCount() - 1];
/*N*/   Vector3D aTail = (bFront) ? rSourcePoly[1] : rSourcePoly[rSourcePoly.GetPointCount() - 2];
/*N*/
/*N*/   if(fOffset != 0.0)
/*N*/   {
/*N*/       if(!bFront)
/*N*/           fOffset = rSourcePoly.GetLength() - fOffset;
/*N*/       aTail = rSourcePoly.GetPosition(fOffset);
/*N*/   }
/*N*/
/*N*/   Vector3D aDirection = aHead - aTail;
/*N*/   aDirection.Normalize();
/*N*/   double fRotation = atan2(aDirection.Y(), aDirection.X()) - (90.0 * F_PI180);
/*N*/
/*N*/   aTrans.RotateZ(fRotation);
/*N*/   aTrans.Translate(aHead);
/*N*/
/*N*/   if(!bCentered)
/*N*/   {
/*N*/       Vector3D aUpperCenter(aCenter.X(), aPolySize.MaxVec().Y(), 0.0);
/*N*/
/*N*/       aUpperCenter *= aTrans;
/*N*/       aCenter *= aTrans;
/*N*/       aTrans.Translate(aCenter - aUpperCenter);
/*N*/   }
/*N*/
/*N*/   rArrowPoly.Transform(aTrans);
/*N*/   rArrowPoly.SetClosed(TRUE);
/*N*/
/*N*/   return fRetval;
/*N*/ }

/*N*/ void ImpLineGeometryCreator::ImpCreateLineGeometry(const Polygon3D& rSourcePoly)
/*N*/ {
/*N*/   UINT16 nPntCnt = rSourcePoly.GetPointCount();
/*N*/
/*N*/   if(nPntCnt > 1)
/*N*/   {
/*N*/       BOOL bClosed = rSourcePoly.IsClosed();
/*N*/       UINT16 nCount = nPntCnt;
/*N*/       Polygon3D aPoly = rSourcePoly;
/*N*/
/*N*/       if(!bClosed)
/*N*/       {
/*N*/           nCount = nPntCnt-1;
/*N*/           double fPolyLength = rSourcePoly.GetLength();
/*N*/           double fStart = 0.0;
/*N*/           double fEnd = fPolyLength;
/*N*/
/*N*/           if(mrLineAttr.IsStartActive())
/*N*/           {
/*?*/               // create line start polygon and move line end
/*?*/               Polygon3D aArrowPoly(XOutCreatePolygon(mrLineAttr.GetStartPolygon(), mrLineAttr.GetOutDev()));
/*?*/               fStart = ImpCreateLineStartEnd(
/*?*/                   aArrowPoly, rSourcePoly, TRUE,
/*?*/                   (double)mrLineAttr.GetStartWidth(), mrLineAttr.IsStartCentered());
/*?*/               mrPolyPoly3D.Insert(aArrowPoly);
/*N*/           }
/*N*/
/*N*/           if(mrLineAttr.IsEndActive())
/*N*/           {
/*?*/               // create line end polygon and move line end
/*?*/               Polygon3D aArrowPoly(XOutCreatePolygon(mrLineAttr.GetEndPolygon(), mrLineAttr.GetOutDev()));
/*?*/               fEnd = fPolyLength - ImpCreateLineStartEnd(
/*?*/                   aArrowPoly, rSourcePoly, FALSE,
/*?*/                   (double)mrLineAttr.GetEndWidth(), mrLineAttr.IsEndCentered());
/*?*/               mrPolyPoly3D.Insert(aArrowPoly);
/*N*/           }
/*N*/
/*N*/           if(fStart != 0.0 || fEnd != fPolyLength)
/*N*/           {
/*?*/               // build new poly, consume something from old poly
/*?*/               aPoly = Polygon3D(nCount);
/*?*/               UINT16 nInsPos(0);
/*?*/               double fPolyPos = 0.0;
/*?*/
/*?*/               for(UINT16 a=0;a<nCount;a++)
/*?*/               {
/*?*/                   Vector3D aEdge = rSourcePoly[a+1] - rSourcePoly[a];
/*?*/                   double fLength = aEdge.GetLength();
/*?*/
/*?*/                   if(fStart != 0.0)
/*?*/                   {
/*?*/                       if(fStart - fLength > -SMALL_DVALUE)
/*?*/                       {
/*?*/                           fStart -= fLength;
/*?*/                       }
/*?*/                       else
/*?*/                       {
/*?*/                           Vector3D aNewPos;
/*?*/                           aNewPos.CalcInBetween(rSourcePoly[a], rSourcePoly[a+1], fStart / fLength);
/*?*/                           aPoly[nInsPos++] = aNewPos;
/*?*/                           fStart = 0.0;
/*?*/                       }
/*?*/                   }
/*?*/                   else
/*?*/                   {
/*?*/                       aPoly[nInsPos++] = rSourcePoly[a];
/*?*/                   }
/*?*/
/*?*/                   if((fPolyPos + fLength) - fEnd > -SMALL_DVALUE)
/*?*/                   {
/*?*/                       Vector3D aNewPos;
/*?*/                       aNewPos.CalcInBetween(rSourcePoly[a], rSourcePoly[a+1], (fEnd - fPolyPos) / fLength);
/*?*/                       aPoly[nInsPos++] = aNewPos;
/*?*/                       a = nCount;
/*?*/                   }
/*?*/
/*?*/                   // next PolyPos
/*?*/                   fPolyPos += fLength;
/*?*/               }
/*?*/
/*?*/               nCount = aPoly.GetPointCount() - 1;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if(nCount)
/*N*/       {
/*N*/           if(!mrLineAttr.GetDisplayLineWidth()
/*N*/               && (mbLineDraft || mrLineAttr.GetLineStyle() == XLINE_SOLID))
/*N*/           {
/*N*/               // LineWidth zero, solid line -> add directly to linePoly
/*N*/               mrPolyLine3D.Insert(aPoly);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               const Vector3D* pPrev = NULL;
/*N*/               const Vector3D* pLeft = NULL;
/*N*/               const Vector3D* pRight = NULL;
/*N*/               const Vector3D* pNext = NULL;
/*N*/               double fPolyPos = 0.0;
/*N*/
/*N*/               for(UINT16 a=0;a<nCount;a++)
/*N*/               {
/*N*/                   BOOL bStart(!a);
/*N*/                   BOOL bEnd(a+1 == nCount);
/*N*/
/*N*/                   // get left, right positions
/*N*/                   pLeft = &aPoly[a];
/*N*/
/*N*/                   // get length
/*N*/                   if(bClosed)
/*N*/                   {
/*N*/                       pRight = &aPoly[(a+1) % nCount];
/*N*/                       pPrev = &aPoly[(a+nCount-1) % nCount];
/*N*/                       pNext = &aPoly[(a+2) % nCount];
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       pRight = &aPoly[a+1];
/*?*/
/*?*/                       if(bStart)
/*?*/                       {
/*?*/                           pPrev = NULL;
/*?*/                       }
/*?*/                       else
/*?*/                       {
/*?*/                           pPrev = &aPoly[a-1];
/*?*/                       }
/*?*/
/*?*/                       if(bEnd)
/*?*/                       {
/*?*/                           pNext = NULL;
/*?*/                       }
/*?*/                       else
/*?*/                       {
/*?*/                           pNext = &aPoly[a+2];
/*?*/                       }
/*N*/                   }

                    // positions are in pPrev, pLeft, pRight and pNext.
/*N*/                   if(!mbLineDraft && mrLineAttr.GetLineStyle() == XLINE_DASH)
/*?*/                       ImpCreateSegmentsForLine(pPrev, pLeft, pRight, pNext, fPolyPos);
/*N*/                   else
/*?*/                       ImpCreateLineSegment(pPrev, pLeft, pRight, pNext);
/*N*/
/*N*/                   // increment PolyPos
/*N*/                   Vector3D aEdge = *pRight - *pLeft;
/*N*/                   fPolyPos += aEdge.GetLength();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// class to remember broadcast start positions

/*N*/ SdrBroadcastItemChange::SdrBroadcastItemChange(const SdrObject& rObj)
/*N*/ {
/*N*/   if(rObj.ISA(SdrObjGroup))
/*N*/   {
/*N*/       SdrObjListIter aIter((const SdrObjGroup&)rObj, IM_DEEPNOGROUPS);
/*N*/       mpData = new List();
/*N*/
/*N*/       while(aIter.IsMore())
/*N*/       {
/*N*/           SdrObject* pObj = aIter.Next();
/*N*/           if(pObj)
/*N*/               ((List*)mpData)->Insert(new Rectangle(pObj->GetBoundRect()), LIST_APPEND);
/*N*/       }
/*N*/
/*N*/       mnCount = ((List*)mpData)->Count();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       mnCount = 1;
/*N*/       mpData = new Rectangle(rObj.GetBoundRect());
/*N*/   }
/*N*/ }

/*N*/ SdrBroadcastItemChange::~SdrBroadcastItemChange()
/*N*/ {
/*N*/   if(mnCount > 1)
/*N*/   {
/*N*/       for(sal_uInt32 a(0); a < mnCount;a++)
/*N*/           delete ((Rectangle*)((List*)mpData)->GetObject(a));
/*N*/       delete ((List*)mpData);
/*N*/   }
/*N*/   else
/*N*/       delete ((Rectangle*)mpData);
/*N*/ }

/*N*/ const Rectangle& SdrBroadcastItemChange::GetRectangle(sal_uInt32 nIndex) const
/*N*/ {
/*N*/   if(mnCount > 1)
/*N*/       return *((Rectangle*)((List*)mpData)->GetObject(nIndex));
/*N*/   else
/*N*/       return *((Rectangle*)mpData);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@  @@@@@@ @@@@@  @@@@  @@@@@@
//  @@  @@ @@  @@     @@ @@    @@  @@   @@
//  @@  @@ @@  @@     @@ @@    @@       @@
//  @@  @@ @@@@@      @@ @@@@  @@       @@
//  @@  @@ @@  @@     @@ @@    @@       @@
//  @@  @@ @@  @@ @@  @@ @@    @@  @@   @@
//   @@@@  @@@@@   @@@@  @@@@@  @@@@    @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ DBG_NAME(SdrObject)
/*N*/ TYPEINIT1(SdrObject,SfxListener);

/*N*/ SdrObject::SdrObject():
/*N*/   pObjList(NULL),
/*N*/   pPage(NULL),
/*N*/   pModel(NULL),
/*N*/   pUserCall(NULL),
/*N*/   pPlusData(NULL),
/*N*/   nOrdNum(0),
/*N*/   nLayerId(0)
/*N*/ {
/*N*/   DBG_CTOR(SdrObject,NULL);
/*N*/   bVirtObj         =FALSE;
/*N*/   bBoundRectDirty  =TRUE;
/*N*/   bSnapRectDirty   =TRUE;
/*N*/   bNetLock         =FALSE;
/*N*/   bInserted        =FALSE;
/*N*/   bGrouped         =FALSE;
/*N*/   bMovProt         =FALSE;
/*N*/   bSizProt         =FALSE;
/*N*/   bNoPrint         =FALSE;
/*N*/   bEmptyPresObj    =FALSE;
/*N*/   bNotPersistent   =FALSE;
/*N*/   bNeedColorRestore=FALSE;
/*N*/   bNotVisibleAsMaster=FALSE;
/*N*/   bClosedObj       =FALSE;
/*N*/   bWriterFlyFrame  =FALSE;
/*N*/   bNotMasterCachable=FALSE;
/*N*/   bIsEdge=FALSE;
/*N*/   bIs3DObj=FALSE;
/*N*/   bMarkProt=FALSE;
/*N*/   bIsUnoObj=FALSE;
/*N*/ }

/*N*/ SdrObject::~SdrObject()
/*N*/ {
/*N*/   uno::Reference< lang::XComponent > xShape( mxUnoShape, uno::UNO_QUERY );
/*N*/   if( xShape.is() )
/*N*/       xShape->dispose();
/*N*/
/*N*/   DBG_DTOR(SdrObject,NULL);
/*N*/   SendUserCall(SDRUSERCALL_DELETE,GetBoundRect());
/*N*/   if (pPlusData!=NULL) delete pPlusData;
/*N*/ }

/*N*/ SdrObjPlusData* SdrObject::NewPlusData() const
/*N*/ {
/*N*/   return new SdrObjPlusData;
/*N*/ }

/*N*/ void SdrObject::SetRectsDirty(FASTBOOL bNotMyself)
/*N*/ {
/*N*/   if (!bNotMyself) {
/*N*/       bBoundRectDirty=TRUE;
/*N*/       bSnapRectDirty=TRUE;
/*N*/   }
/*N*/   if (pObjList!=NULL) {
/*N*/       pObjList->SetRectsDirty();
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   if(pNewModel && pPage)
/*N*/   {
/*N*/       if(pPage->GetModel() != pNewModel)
/*N*/       {
/*N*/           pPage = NULL;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pModel = pNewModel;
/*N*/ }

/*N*/ void SdrObject::SetObjList(SdrObjList* pNewObjList)
/*N*/ {
/*N*/   pObjList=pNewObjList;
/*N*/ }

/*N*/ void SdrObject::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   pPage=pNewPage;
/*N*/   if (pPage!=NULL) {
/*N*/       SdrModel* pMod=pPage->GetModel();
/*N*/       if (pMod!=pModel && pMod!=NULL) {
/*N*/           SetModel(pMod);
/*N*/       }
/*N*/   }
/*N*/ }

// init global static itempool
/*N*/ SdrItemPool* SdrObject::mpGlobalItemPool = NULL;
/*N*/
/*N*/ SdrItemPool* SdrObject::GetGlobalDrawObjectItemPool()
/*N*/ {
/*N*/   if(!mpGlobalItemPool)
/*N*/   {
/*N*/       mpGlobalItemPool = new SdrItemPool(SDRATTR_START, SDRATTR_END);
/*N*/       SfxItemPool* pGlobalOutlPool = EditEngine::CreatePool();
/*N*/       mpGlobalItemPool->SetSecondaryPool(pGlobalOutlPool);
/*N*/       mpGlobalItemPool->SetDefaultMetric((SfxMapUnit)SdrEngineDefaults::GetMapUnit());
/*N*/       mpGlobalItemPool->FreezeIdRanges();
/*N*/   }
/*N*/
/*N*/   return mpGlobalItemPool;
/*N*/ }

//STRIP001 void SdrObject::FreeGlobalDrawObjectItemPool()
//STRIP001 {
//STRIP001  // code for deletion of GlobalItemPool
//STRIP001  if(mpGlobalItemPool)
//STRIP001  {
//STRIP001      SfxItemPool* pGlobalOutlPool = mpGlobalItemPool->GetSecondaryPool();
//STRIP001      delete mpGlobalItemPool;
//STRIP001      delete pGlobalOutlPool;
//STRIP001  }
//STRIP001 }

/*N*/ SdrItemPool* SdrObject::GetItemPool() const
/*N*/ {
/*N*/   if(pModel)
/*N*/       return (SdrItemPool*)(&pModel->GetItemPool());
/*N*/
/*N*/   // use a static global default pool
/*N*/   return SdrObject::GetGlobalDrawObjectItemPool();
/*N*/ }

/*N*/ UINT32 SdrObject::GetObjInventor()   const
/*N*/ {
/*N*/   return SdrInventor;
/*N*/ }

/*N*/ UINT16 SdrObject::GetObjIdentifier() const
/*N*/ {
/*N*/   return UINT16(OBJ_NONE);
/*N*/ }

//STRIP001 void SdrObject::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bRotateFreeAllowed=FALSE;
//STRIP001  rInfo.bMirrorFreeAllowed=FALSE;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed     =FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001  rInfo.bCanConvToPath    =FALSE;
//STRIP001  rInfo.bCanConvToPoly    =FALSE;
//STRIP001  rInfo.bCanConvToContour = FALSE;
//STRIP001  rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001 }

/*N*/ SdrLayerID SdrObject::GetLayer() const
/*N*/ {
/*N*/   return SdrLayerID(nLayerId);
/*N*/ }

/*N*/ void SdrObject::GetLayer(SetOfByte& rSet) const
/*N*/ {
/*N*/   rSet.Set((BYTE)nLayerId);
/*N*/   SdrObjList* pOL=GetSubList();
/*N*/   if (pOL!=NULL) {
/*N*/       ULONG nObjAnz=pOL->GetObjCount();
/*N*/       for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
/*N*/           pOL->GetObj(nObjNum)->GetLayer(rSet);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::NbcSetLayer(SdrLayerID nLayer)
/*N*/ {
/*N*/   nLayerId=nLayer;
/*N*/ }

/*N*/ void SdrObject::SetLayer(SdrLayerID nLayer)
/*N*/ {
/*N*/   NbcSetLayer(nLayer);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/ }

/*N*/ void SdrObject::AddListener(SfxListener& rListener)
/*N*/ {
/*N*/   ImpForcePlusData();
/*N*/   if (pPlusData->pBroadcast==NULL) pPlusData->pBroadcast=new SfxBroadcaster;
/*N*/   rListener.StartListening(*pPlusData->pBroadcast);
/*N*/ }

/*N*/ void SdrObject::RemoveListener(SfxListener& rListener)
/*N*/ {
/*N*/   if (pPlusData!=NULL && pPlusData->pBroadcast!=NULL) {
/*N*/       rListener.EndListening(*pPlusData->pBroadcast);
/*N*/       if (!pPlusData->pBroadcast->HasListeners()) {
/*N*/           delete pPlusData->pBroadcast;
/*N*/           pPlusData->pBroadcast=NULL;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::AddReference(SdrVirtObj& rVrtObj)
/*N*/ {
/*N*/   AddListener(rVrtObj);
/*N*/ }

/*N*/ void SdrObject::DelReference(SdrVirtObj& rVrtObj)
/*N*/ {
/*N*/   RemoveListener(rVrtObj);
/*N*/ }

//STRIP001 ImpSdrMtfAnimator* SdrObject::ImpForceMtfAnimator()
//STRIP001 {
//STRIP001  ImpForcePlusData();
//STRIP001  if (pPlusData->pAnimator==NULL) pPlusData->pAnimator=new ImpSdrMtfAnimator;
//STRIP001  return pPlusData->pAnimator;
//STRIP001 }

//STRIP001 AutoTimer* SdrObject::ForceAutoTimer()
//STRIP001 {
//STRIP001  ImpForcePlusData();
//STRIP001  if (pPlusData->pAutoTimer==NULL) pPlusData->pAutoTimer=new AutoTimer;
//STRIP001  return pPlusData->pAutoTimer;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::HasRefPoint() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 Point SdrObject::GetRefPoint() const
//STRIP001 {
//STRIP001  return GetBoundRect().Center();
//STRIP001 }

//STRIP001 void SdrObject::SetRefPoint(const Point& /*rPnt*/)
//STRIP001 {
//STRIP001 }

/*N*/ SdrObjList* SdrObject::GetSubList() const
/*N*/ {
/*N*/   return NULL;
/*N*/ }

/*N*/ SdrObject* SdrObject::GetUpGroup() const
/*N*/ {
/*N*/   return pObjList!=NULL ? pObjList->GetOwnerObj() : NULL;
/*N*/ }

//STRIP001 FASTBOOL SdrObject::HasSetName() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ void SdrObject::SetName(const XubString& rStr)
/*NBFF*/ {
/*NBFF*/    if(rStr.Len())
/*NBFF*/    {
/*NBFF*/        ImpForcePlusData();
/*NBFF*/        pPlusData->aObjName = rStr;
/*NBFF*/    }
/*NBFF*/    else
/*NBFF*/    {
/*NBFF*/        if(pPlusData)
/*NBFF*/        {
/*NBFF*/            pPlusData->aObjName = rStr;
/*NBFF*/        }
/*NBFF*/    }
/*N*/ }

/*N*/ XubString SdrObject::GetName() const
/*N*/ {
/*N*/   SdrObjPlusData* pPlus=pPlusData;
/*N*/   if (pPlus!=NULL) {
/*N*/       return pPlus->aObjName;
/*N*/   }
/*N*/   return String();
/*N*/ }

// support for HTMLName
//STRIP001 void SdrObject::SetHTMLName(const XubString& rStr)
//STRIP001 {
//STRIP001  if(rStr.Len())
//STRIP001  {
//STRIP001      ImpForcePlusData();
//STRIP001      pPlusData->aHTMLName = rStr;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if(pPlusData)
//STRIP001      {
//STRIP001          pPlusData->aHTMLName.Erase();
//STRIP001      }
//STRIP001  }
//STRIP001 }

// support for HTMLName
//STRIP001 XubString SdrObject::GetHTMLName() const
//STRIP001 {
//STRIP001  if(pPlusData)
//STRIP001      return pPlusData->aHTMLName;
//STRIP001  return String();
//STRIP001 }

/*N*/ UINT32 SdrObject::GetOrdNum() const
/*N*/ {
/*N*/   if (pObjList!=NULL) {
/*N*/       if (pObjList->IsObjOrdNumsDirty()) {
/*N*/           pObjList->RecalcObjOrdNums();
/*N*/       }
/*N*/   } else ((SdrObject*)this)->nOrdNum=0;
/*N*/   return nOrdNum;
/*N*/ }

/*N*/ const Rectangle& SdrObject::GetBoundRect() const
/*N*/ {
/*N*/   if (bBoundRectDirty) {
/*N*/       ((SdrObject*)this)->RecalcBoundRect();
/*N*/       ((SdrObject*)this)->bBoundRectDirty=FALSE;
/*N*/   }
/*N*/   return aOutRect;
/*N*/ }

/*N*/ void SdrObject::RecalcBoundRect()
/*N*/ {
/*N*/ }

/*N*/ void SdrObject::SendRepaintBroadcast(const Rectangle& rRect) const
/*N*/ {
/*N*/   if( pModel && pModel->isLocked() )
/*N*/       return;
/*N*/
/*N*/   BOOL bBrd(pPlusData && pPlusData->pBroadcast);
/*N*/   BOOL bPnt(bInserted && pModel);
/*N*/
/*N*/   if(bPnt || bBrd)
/*N*/   {
/*N*/       SdrHint aHint(*this, rRect);
/*N*/
/*N*/       if(bBrd)
/*?*/           pPlusData->pBroadcast->Broadcast(aHint);
/*N*/
/*N*/       if(bPnt)
/*N*/           pModel->Broadcast(aHint);
/*N*/
/*N*/       // alle Animationen wegen Obj-Aenderung neustarten
/*N*/       RestartAnimation(NULL);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::SendRepaintBroadcast(BOOL bNoPaintNeeded) const
/*N*/ {
/*N*/   if( pModel && pModel->isLocked() )
/*N*/       return;
/*N*/
/*N*/   BOOL bBrd(pPlusData && pPlusData->pBroadcast);
/*N*/   BOOL bPnt(bInserted && pModel);
/*N*/
/*N*/   if(bPnt || bBrd)
/*N*/   {
/*N*/       SdrHint aHint(*this);
/*N*/       aHint.SetNeedRepaint(!bNoPaintNeeded);
/*N*/
/*N*/       if(bBrd)
/*N*/           pPlusData->pBroadcast->Broadcast(aHint);
/*N*/
/*N*/       if(bPnt)
/*N*/           pModel->Broadcast(aHint);
/*N*/
/*N*/       // alle Animationen wegen Obj-Aenderung neustarten
/*N*/       RestartAnimation(NULL);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::SetChanged()
/*N*/ {
/*N*/   if (bInserted && pModel!=NULL) pModel->SetChanged();
/*N*/ }

/*N*/ FASTBOOL SdrObject::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& /*rInfoRec*/) const
/*N*/ {
/*N*/   Color aRedColor( COL_RED );
/*N*/   Color aYellowColor( COL_YELLOW );
/*N*/   rXOut.OverrideLineColor( aRedColor );
/*N*/   rXOut.OverrideFillColor( aYellowColor );
/*N*/   rXOut.DrawRect(GetBoundRect());
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ ::std::auto_ptr< SdrLineGeometry >  SdrObject::CreateLinePoly( OutputDevice&      rOut,
/*N*/                                                                BOOL               bForceOnePixel,
/*N*/                                                                BOOL               bForceTwoPixel,
/*N*/                                                                BOOL               bIsLineDraft    ) const
/*N*/ {
/*N*/     PolyPolygon3D aPolyPoly3D;
/*N*/     PolyPolygon3D aLinePoly3D;
/*N*/
/*N*/   // get XOR Poly as base
/*N*/   XPolyPolygon aTmpPolyPolygon;
/*N*/   TakeXorPoly(aTmpPolyPolygon, TRUE);
/*N*/
/*N*/   // get ImpLineStyleParameterPack
/*N*/   ImpLineStyleParameterPack aLineAttr(GetItemSet(), bForceOnePixel || bForceTwoPixel || bIsLineDraft, &rOut);
/*N*/   ImpLineGeometryCreator aLineCreator(aLineAttr, aPolyPoly3D, aLinePoly3D, bIsLineDraft);
/*N*/
/*N*/   // compute single lines
/*N*/   for(UINT16 a=0;a<aTmpPolyPolygon.Count();a++)
/*N*/   {
/*N*/       // expand splines into polygons and convert to double
/*N*/       Polygon3D aPoly3D(XOutCreatePolygon(aTmpPolyPolygon[a], &rOut));
/*N*/       aPoly3D.RemoveDoublePoints();
/*N*/
/*N*/       // convert line to single Polygons; make sure the part
/*N*/       // polygons are all clockwise oriented
/*N*/       aLineCreator.AddPolygon3D(aPoly3D);
/*N*/   }
/*N*/
/*N*/     if(aPolyPoly3D.Count() || aLinePoly3D.Count())
/*N*/         return ::std::auto_ptr< SdrLineGeometry > (new SdrLineGeometry(aPolyPoly3D, aLinePoly3D,
/*N*/                                                                        aLineAttr, bForceOnePixel, bForceTwoPixel));
/*N*/     else
/*?*/       return ::std::auto_ptr< SdrLineGeometry > (NULL);
/*N*/ }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//#define TEST_SKELETON
#ifdef TEST_SKELETON

static OutputDevice* pImpTestOut = 0L;

class ImpSkeleton;

//STRIP001 class ImpSkeletonNode
//STRIP001 {
//STRIP001  const ImpSkeleton&          mrParent;
//STRIP001  ImpSkeletonNode*            mpNext;
//STRIP001  ImpSkeletonNode*            mpPrev;
//STRIP001  ImpSkeletonNode*            mpUp;
//STRIP001  ImpSkeletonNode*            mpDown;
//STRIP001
//STRIP001  Vector3D                    maPosition;
//STRIP001  Vector3D                    maDirection;
//STRIP001  double                      mfDistance;
//STRIP001  BOOL                        mbDirection;
//STRIP001
//STRIP001 public:
//STRIP001  ImpSkeletonNode(const ImpSkeleton& rPrnt, const Vector3D& rPos, const Vector3D& rDir, BOOL bDir);
//STRIP001  ~ImpSkeletonNode();
//STRIP001
//STRIP001  ImpSkeletonNode* GetNext() const { return mpNext; }
//STRIP001  void SetNext(ImpSkeletonNode* pNew) { mpNext = pNew; }
//STRIP001
//STRIP001  ImpSkeletonNode* GetPrev() const { return mpPrev; }
//STRIP001  void SetPrev(ImpSkeletonNode* pNew) { mpPrev = pNew; }
//STRIP001
//STRIP001  ImpSkeletonNode* GetUp() const { return mpUp; }
//STRIP001  void SetUp(ImpSkeletonNode* pNew) { mpUp = pNew; }
//STRIP001
//STRIP001  ImpSkeletonNode* GetDown() const { return mpDown; }
//STRIP001  void SetDown(ImpSkeletonNode* pNew) { mpDown = pNew; }
//STRIP001
//STRIP001  const Vector3D& GetPosition() const { return maPosition; }
//STRIP001  const Vector3D& GetDirection() const { return maDirection; }
//STRIP001  BOOL GetOrientation() const { return mbDirection; }
//STRIP001
//STRIP001  double GetDistance() const { return mfDistance; }
//STRIP001  void SetDistance(double fNew) { mfDistance = fNew; }
//STRIP001
//STRIP001  void Paint(Color aCol);
//STRIP001 };

///////////////////////////////////////////////////////////////////////////////

//STRIP001 DECLARE_LIST(ImpSkeletonNodeList, ImpSkeletonNode*)//STRIP008 ;

///////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpSkeleton
//STRIP001 {
//STRIP001  ImpSkeletonNodeList         maList;
//STRIP001  ImpSkeletonNode*            mpList;
//STRIP001
//STRIP001 public:
//STRIP001  ImpSkeleton(const Polygon3D& rPoly);
//STRIP001  ~ImpSkeleton();
//STRIP001
//STRIP001  BOOL ImpSimpleFindCutPoint(
//STRIP001      const Vector3D& rEdge1Start, const Vector3D& rEdge1Delta,
//STRIP001      const Vector3D& rEdge2Start, const Vector3D& rEdge2Delta,
//STRIP001      double& rCutA, double& rCutB) const;
//STRIP001
//STRIP001  void PaintTree(ImpSkeletonNode* pNode, Color aCol);
//STRIP001 };

///////////////////////////////////////////////////////////////////////////////

//STRIP001 ImpSkeletonNode::ImpSkeletonNode(const ImpSkeleton& rPrnt, const Vector3D& rPos, const Vector3D& rDir, BOOL bDir)
//STRIP001 :    mrParent(rPrnt),
//STRIP001  mpNext(this),
//STRIP001  mpPrev(this),
//STRIP001  mpUp(0L),
//STRIP001  mpDown(0L),
//STRIP001  maPosition(rPos),
//STRIP001  maDirection(rDir),
//STRIP001  mfDistance(0.0),
//STRIP001  mbDirection(bDir)
//STRIP001 {
//STRIP001 }

//STRIP001 ImpSkeletonNode::~ImpSkeletonNode()
//STRIP001 {
//STRIP001 }

//STRIP001 void ImpSkeletonNode::Paint(Color aCol)
//STRIP001 {
//STRIP001  if(pImpTestOut)
//STRIP001  {
//STRIP001      Vector3D aP1 = GetPosition();
//STRIP001      Vector3D aP2 = aP1 + (GetDirection() * 5000.0);
//STRIP001      Vector3D aP3 = aP1 - (GetDirection() * 1000.0);
//STRIP001
//STRIP001      Point aPn1((INT32)aP1.X(), (INT32)-aP1.Y());
//STRIP001      Point aPn2((INT32)aP2.X(), (INT32)-aP2.Y());
//STRIP001      Point aPn3((INT32)aP3.X(), (INT32)-aP3.Y());
//STRIP001
//STRIP001      pImpTestOut->SetLineColor(Color(aCol));
//STRIP001      pImpTestOut->DrawLine(aPn1, aPn2);
//STRIP001      pImpTestOut->SetLineColor(Color(COL_BLACK));
//STRIP001      pImpTestOut->DrawLine(aPn1, aPn3);
//STRIP001  }
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 ImpSkeleton::ImpSkeleton(const Polygon3D& rPoly)
//STRIP001 :    mpList(0L)
//STRIP001 {
//STRIP001  UINT16 nCnt(rPoly.GetPointCount());
//STRIP001
//STRIP001  // build base list
//STRIP001  for(UINT16 a=0;a<nCnt;a++)
//STRIP001  {
//STRIP001      Vector3D aPrevDir = rPoly[(a + nCnt - 1) % nCnt] - rPoly[a];
//STRIP001      Vector3D aNextDir = rPoly[(a + 1) % nCnt] - rPoly[a];
//STRIP001
//STRIP001      aPrevDir.Normalize();
//STRIP001      aNextDir.Normalize();
//STRIP001
//STRIP001      Vector3D aMidDir = aPrevDir + aNextDir;
//STRIP001
//STRIP001      aMidDir.Normalize();
//STRIP001
//STRIP001      BOOL bDirection((aPrevDir.Y() * aNextDir.X() - aPrevDir.X() * aNextDir.Y()) > -SMALL_DVALUE);
//STRIP001      ImpSkeletonNode* pNewNode = new ImpSkeletonNode(*this, rPoly[a], aMidDir, bDirection);
//STRIP001      maList.Insert(pNewNode);
//STRIP001
//STRIP001      if(mpList)
//STRIP001      {
//STRIP001          pNewNode->SetNext(mpList->GetNext());
//STRIP001          mpList->SetNext(pNewNode);
//STRIP001          pNewNode->GetNext()->SetPrev(pNewNode);
//STRIP001          pNewNode->SetPrev(mpList);
//STRIP001      }
//STRIP001
//STRIP001      mpList = pNewNode;
//STRIP001
//STRIP001      pNewNode->Paint(COL_YELLOW);
//STRIP001  }
//STRIP001
//STRIP001  // iterate
//STRIP001  while(nCnt > 1)
//STRIP001  {
//STRIP001      // make step
//STRIP001      double fLowestDist(DBL_MAX);
//STRIP001      double fLowestCut;
//STRIP001      ImpSkeletonNode* pCand = NULL;
//STRIP001      ImpSkeletonNode* pCurr = mpList;
//STRIP001
//STRIP001      do {
//STRIP001          ImpSkeletonNode* pNext = pCurr->GetNext();
//STRIP001          double fCutA, fCutB;
//STRIP001
//STRIP001          pCurr->Paint(COL_RED);
//STRIP001          pNext->Paint(COL_LIGHTRED);
//STRIP001
//STRIP001          if(ImpSimpleFindCutPoint(pCurr->GetPosition(), pCurr->GetDirection(),
//STRIP001              pNext->GetPosition(), pNext->GetDirection(), fCutA, fCutB))
//STRIP001          {
//STRIP001              if((!pCurr->GetOrientation() && fCutA > 0.0) || (pCurr->GetOrientation() && fCutA < 0.0))
//STRIP001              {
//STRIP001                  Vector3D aCutPos;
//STRIP001                  Vector3D aMidPos = (pCurr->GetPosition() + pNext->GetPosition()) / 2.0;
//STRIP001
//STRIP001                  aCutPos.CalcInBetween(
//STRIP001                      pCurr->GetPosition(),
//STRIP001                      pCurr->GetPosition() + pCurr->GetDirection(), fCutA);
//STRIP001
//STRIP001                  aCutPos -= aMidPos;
//STRIP001
//STRIP001                  double fComp = aCutPos.GetLength() + pCurr->GetDistance() + pNext->GetDistance();
//STRIP001
//STRIP001                  if(fComp < fLowestDist)
//STRIP001                  {
//STRIP001                      fLowestDist = fComp;
//STRIP001                      fLowestCut = fCutA;
//STRIP001                      pCand = pCurr;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          pCurr->Paint(COL_YELLOW);
//STRIP001          pNext->Paint(COL_YELLOW);
//STRIP001
//STRIP001          pCurr = pNext;
//STRIP001      } while(pCurr != mpList);
//STRIP001
//STRIP001      if(pCand)
//STRIP001      {
//STRIP001          // create cut entry and re-arrange tree
//STRIP001          Vector3D aCutPos;
//STRIP001          aCutPos.CalcInBetween(pCand->GetPosition(), pCand->GetPosition() + pCand->GetDirection(), fLowestCut);
//STRIP001
//STRIP001          ImpSkeletonNode* pLeft = pCand;
//STRIP001          ImpSkeletonNode* pRight = pCand->GetNext();
//STRIP001
//STRIP001          pLeft->Paint(COL_RED);
//STRIP001          pRight->Paint(COL_LIGHTRED);
//STRIP001
//STRIP001          Vector3D aPrevDir = pLeft->GetPrev()->GetPosition() - pLeft->GetPosition();
//STRIP001          Vector3D aNextDir = pRight->GetNext()->GetPosition() - pRight->GetPosition();
//STRIP001
//STRIP001          aPrevDir.Normalize();
//STRIP001          aNextDir.Normalize();
//STRIP001
//STRIP001          Vector3D aMidDir = aPrevDir + aNextDir;
//STRIP001
//STRIP001          aMidDir.Normalize();
//STRIP001
//STRIP001          BOOL bDirection((aPrevDir.Y() * aNextDir.X() - aPrevDir.X() * aNextDir.Y()) > -SMALL_DVALUE);
//STRIP001          ImpSkeletonNode* pNewNode = new ImpSkeletonNode(*this, aCutPos, aMidDir, bDirection);
//STRIP001          maList.Insert(pNewNode);
//STRIP001
//STRIP001          // set distance
//STRIP001          Vector3D aMidPoint = (pLeft->GetPosition() + pRight->GetPosition()) / 2.0;
//STRIP001          pNewNode->SetDistance(aMidPoint.GetLength());
//STRIP001
//STRIP001          // add new node to old chain
//STRIP001          pNewNode->SetPrev(pLeft->GetPrev());
//STRIP001          pLeft->GetPrev()->SetNext(pNewNode);
//STRIP001          pNewNode->SetNext(pRight->GetNext());
//STRIP001          pRight->GetNext()->SetPrev(pNewNode);
//STRIP001
//STRIP001          // Set Up-Down chaining
//STRIP001          pNewNode->SetDown(pLeft);
//STRIP001          pLeft->SetUp(pNewNode);
//STRIP001          pRight->SetUp(pNewNode);
//STRIP001
//STRIP001          // close lower chain
//STRIP001          pLeft->SetPrev(pRight);
//STRIP001          pRight->SetNext(pLeft);
//STRIP001
//STRIP001          nCnt--;
//STRIP001          mpList = pNewNode;
//STRIP001
//STRIP001          pLeft->Paint(COL_BLUE);
//STRIP001          pRight->Paint(COL_LIGHTBLUE);
//STRIP001
//STRIP001          pNewNode->Paint(COL_LIGHTGREEN);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // last lines are all parallel, group together
//STRIP001          pCurr = mpList;
//STRIP001          Vector3D aMidPos;
//STRIP001          UINT16 nNumber(0);
//STRIP001
//STRIP001          do {
//STRIP001              aMidPos += pCurr->GetPosition();
//STRIP001              nNumber++;
//STRIP001              pCurr = pCurr->GetNext();
//STRIP001          } while(pCurr != mpList);
//STRIP001
//STRIP001          aMidPos /= (double)nNumber;
//STRIP001
//STRIP001          ImpSkeletonNode* pNewNode = new ImpSkeletonNode(*this, aMidPos, Vector3D(), FALSE);
//STRIP001          maList.Insert(pNewNode);
//STRIP001
//STRIP001          // Set Up-Down chaining
//STRIP001          pNewNode->SetDown(mpList);
//STRIP001          pCurr = mpList;
//STRIP001
//STRIP001          do {
//STRIP001              pCurr->SetUp(pNewNode);
//STRIP001              pCurr->Paint(COL_BLUE);
//STRIP001              pCurr = pCurr->GetNext();
//STRIP001          } while(pCurr != mpList);
//STRIP001
//STRIP001          mpList = pNewNode;
//STRIP001
//STRIP001          nCnt = 1;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // show found centers
//STRIP001  PaintTree(mpList, COL_LIGHTRED);
//STRIP001 }

//STRIP001 ImpSkeleton::~ImpSkeleton()
//STRIP001 {
//STRIP001  while(maList.Count())
//STRIP001      delete maList.Remove((UINT32)0L);
//STRIP001 }

//STRIP001 BOOL ImpSkeleton::ImpSimpleFindCutPoint(
//STRIP001  const Vector3D& rEdge1Start, const Vector3D& rEdge1Delta,
//STRIP001  const Vector3D& rEdge2Start, const Vector3D& rEdge2Delta,
//STRIP001  double& rCutA, double& rCutB) const
//STRIP001 {
//STRIP001  double fZwi = (rEdge1Delta.X() * rEdge2Delta.Y()) - (rEdge1Delta.Y() * rEdge2Delta.X());
//STRIP001  rCutA = 0.0;
//STRIP001
//STRIP001  if(fabs(fZwi) > SMALL_DVALUE)
//STRIP001  {
//STRIP001      rCutA = (rEdge2Delta.Y() * (rEdge2Start.X() - rEdge1Start.X()) + rEdge2Delta.X() * (rEdge1Start.Y() - rEdge2Start.Y())) / fZwi;
//STRIP001
//STRIP001      if(fabs(rEdge2Delta.X()) > fabs(rEdge2Delta.Y()))
//STRIP001          rCutB = (rEdge1Start.X() + rCutA * rEdge1Delta.X() - rEdge2Start.X()) / rEdge2Delta.X();
//STRIP001      else
//STRIP001          rCutB = (rEdge1Start.Y() + rCutA * rEdge1Delta.Y() - rEdge2Start.Y()) / rEdge2Delta.Y();
//STRIP001
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void ImpSkeleton::PaintTree(ImpSkeletonNode* pNode, Color aCol)
//STRIP001 {
//STRIP001  if(pImpTestOut)
//STRIP001  {
//STRIP001      Vector3D aP1 = pNode->GetPosition();
//STRIP001      Point aPn1((INT32)aP1.X(), (INT32)-aP1.Y());
//STRIP001      ImpSkeletonNode* pDown = pNode->GetDown();
//STRIP001
//STRIP001      if(pDown)
//STRIP001      {
//STRIP001          do {
//STRIP001              Vector3D aP2 = pDown->GetPosition();
//STRIP001              Point aPn2((INT32)aP2.X(), (INT32)-aP2.Y());
//STRIP001
//STRIP001              pImpTestOut->SetLineColor(Color(aCol));
//STRIP001              pImpTestOut->DrawLine(aPn1, aPn2);
//STRIP001
//STRIP001              PaintTree(pDown, aCol);
//STRIP001
//STRIP001              pDown = pDown->GetNext();
//STRIP001          } while(pDown != pNode->GetDown());
//STRIP001      }
//STRIP001  }
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 void PolyPolygon3D_BuildSkeletonsAndGrow(const PolyPolygon3D& rPolyPoly)
//STRIP001 {
//STRIP001  for(UINT16 a=0;a<rPolyPoly.Count();a++)
//STRIP001  {
//STRIP001      const Polygon3D& rPoly = rPolyPoly[a];
//STRIP001      ImpSkeleton aSkeleton(rPoly);
//STRIP001  }
//STRIP001 }

#endif
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*N*/ ::std::auto_ptr< SdrLineGeometry > SdrObject::ImpPrepareLineGeometry( ExtOutputDevice& rXOut, const SfxItemSet& rSet,
/*N*/                                                                       BOOL bIsLineDraft) const
/*N*/ {
/*N*/   XLineStyle eXLS = (XLineStyle)((const XLineStyleItem&)rSet.Get(XATTR_LINESTYLE)).GetValue();
/*N*/   if(eXLS != XLINE_NONE)
/*N*/   {
/*N*/       // need to force single point line?
/*N*/       INT32 nLineWidth = ((const XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue();
/*N*/       Size aSize(nLineWidth, nLineWidth);
/*N*/       aSize = rXOut.GetOutDev()->LogicToPixel(aSize);
/*N*/       BOOL bForceOnePixel(aSize.Width() <= 1 || aSize.Height() <= 1);
/*N*/       BOOL bForceTwoPixel(!bForceOnePixel && (aSize.Width() <= 2 || aSize.Height() <= 2));
/*N*/
/*N*/       // no force to two pixel when connected to MetaFile, so that not
/*N*/       // four lines instead of one is recorded (e.g.)
/*N*/       if(bForceTwoPixel && rXOut.GetOutDev()->GetConnectMetaFile())
/*N*/           bForceTwoPixel = FALSE;
/*N*/
/*N*/       // #78210# switch off bForceTwoPixel when line draft mode
/*N*/       if(bForceTwoPixel && bIsLineDraft)
/*N*/       {
/*N*/           bForceTwoPixel = FALSE;
/*N*/           bForceOnePixel = TRUE;
/*N*/       }
/*N*/
/*N*/       // create line geometry
/*N*/       return CreateLinePoly(*rXOut.GetOutDev(),
/*N*/                               bForceOnePixel, bForceTwoPixel, bIsLineDraft);
/*N*/   }
/*N*/
/*N*/   return ::std::auto_ptr< SdrLineGeometry > (0L);
/*N*/ }

//STRIP001 void SdrObject::ImpDrawShadowLineGeometry(
//STRIP001  ExtOutputDevice& rXOut, const SfxItemSet& rSet, SdrLineGeometry& rLineGeometry) const
//STRIP001 {
//STRIP001  sal_Int32 nXDist = ((SdrShadowXDistItem&)(rSet.Get(SDRATTR_SHADOWXDIST))).GetValue();
//STRIP001  sal_Int32 nYDist = ((SdrShadowYDistItem&)(rSet.Get(SDRATTR_SHADOWYDIST))).GetValue();
//STRIP001  const SdrShadowColorItem& rShadColItem = ((SdrShadowColorItem&)(rSet.Get(SDRATTR_SHADOWCOLOR)));
//STRIP001  Color aColor(rShadColItem.GetValue());
//STRIP001  sal_uInt16 nTrans = ((SdrShadowTransparenceItem&)(rSet.Get(SDRATTR_SHADOWTRANSPARENCE))).GetValue();
//STRIP001
//STRIP001     // draw shadow line geometry
//STRIP001     ImpDrawLineGeometry(rXOut, aColor, nTrans, rLineGeometry, nXDist, nYDist);
//STRIP001 }

/*N*/ void SdrObject::ImpDrawColorLineGeometry(
/*N*/   ExtOutputDevice& rXOut, const SfxItemSet& rSet, SdrLineGeometry& rLineGeometry) const
/*N*/ {
/*N*/   Color aColor = ((XLineColorItem&)rSet.Get(XATTR_LINECOLOR)).GetValue();
/*N*/   sal_uInt16 nTrans = ((const XLineTransparenceItem&)(rSet.Get(XATTR_LINETRANSPARENCE))).GetValue();
/*N*/
/*N*/   // draw the line geometry
/*N*/   ImpDrawLineGeometry(rXOut, aColor, nTrans, rLineGeometry);
/*N*/ }

/*N*/ void SdrObject::ImpDrawLineGeometry(   ExtOutputDevice&   rXOut,
/*N*/                                        Color&              rColor,
/*N*/                                        sal_uInt16         nTransparence,
/*N*/                                        SdrLineGeometry&    rLineGeometry,
/*N*/                                        sal_Int32              nDX,
/*N*/                                        sal_Int32              nDY             ) const
/*N*/ {
/*N*/     Color aLineColor( rColor );
/*N*/
/*N*/   // #72796# black/white option active?
/*N*/   const UINT32 nOldDrawMode(rXOut.GetOutDev()->GetDrawMode());
/*N*/
/*N*/   // #72796# if yes, force to DRAWMODE_BLACKFILL for these are LINES to be drawn as polygons
/*N*/   if( ( nOldDrawMode & DRAWMODE_WHITEFILL ) && ( nOldDrawMode & DRAWMODE_BLACKLINE ) )
/*N*/     {
/*?*/         aLineColor = Color( COL_BLACK );
/*?*/         rXOut.GetOutDev()->SetDrawMode( nOldDrawMode & (~DRAWMODE_WHITEFILL) );
/*N*/     }
/*N*/     else if( ( nOldDrawMode & DRAWMODE_SETTINGSFILL ) && ( nOldDrawMode & DRAWMODE_SETTINGSLINE ) )
/*N*/     {
/*?*/       svtools::ColorConfig aColorConfig;
/*?*/         aLineColor = Color( aColorConfig.GetColorValue( svtools::FONTCOLOR ).nColor );
/*?*/         rXOut.GetOutDev()->SetDrawMode( nOldDrawMode & (~DRAWMODE_SETTINGSFILL) );
/*N*/     }
/*N*/
/*N*/     // #103692# Hold local copy of geometry
/*N*/     PolyPolygon3D aPolyPoly = rLineGeometry.GetPolyPoly3D();
/*N*/     PolyPolygon3D aLinePoly = rLineGeometry.GetLinePoly3D();
/*N*/
/*N*/     // #103692# Offset geometry (extracted from SdrObject::ImpDrawShadowLineGeometry)
/*N*/   if( nDX || nDY )
/*N*/   {
/*?*/       // transformation necessary
/*?*/       Matrix4D aTrans;
/*?*/
/*?*/       aTrans.Translate((double)nDX, -(double)nDY, 0.0);
/*?*/       aPolyPoly.Transform(aTrans);
/*?*/       aLinePoly.Transform(aTrans);
/*N*/   }
/*N*/
/*N*/     // #100127# Bracket output with a comment, if recording a Mtf
/*N*/     GDIMetaFile* pMtf=NULL;
/*N*/     bool bMtfCommentWritten( false );
/*N*/     if( (pMtf=rXOut.GetOutDev()->GetConnectMetaFile()) )
/*N*/     {
/*N*/         XPolyPolygon aPolyPoly;
/*N*/         TakeXorPoly(aPolyPoly, TRUE);
/*N*/
/*N*/         // #103692# Offset original geometry, too
/*N*/         if( nDX || nDY )
/*N*/         {
/*?*/             // transformation necessary
/*?*/             aPolyPoly.Move( nDX, nDY );
/*N*/         }
/*N*/
/*N*/         // for geometries with more than one polygon, dashing, arrows
/*N*/         // etc. become ambiguous (e.g. measure objects have no arrows
/*N*/         // on the end line), thus refrain from writing the comment
/*N*/         // here.
/*N*/         if( aPolyPoly.Count() == 1 )
/*N*/         {
/*N*/             // add completely superfluous color action (gets overwritten
/*N*/             // below), to store our line color reliably
/*N*/             rXOut.GetOutDev()->SetLineColor(aLineColor);
/*N*/
/*N*/             const ImpLineStyleParameterPack& rLineParameters = rLineGeometry.GetLineAttr();
/*N*/
/*N*/             XPolygon aStartPoly( rLineParameters.GetStartPolygon() );
/*N*/             XPolygon aEndPoly( rLineParameters.GetEndPolygon() );
/*N*/
/*N*/             // scale arrows to specified stroke width
/*N*/             if( aStartPoly.GetPointCount() )
/*?*/             {
/*?*/                 Rectangle aBounds( aStartPoly.GetBoundRect() );
/*?*/
/*?*/                 // mirror and translate to origin
/*?*/                 aStartPoly.Scale(-1,-1);
/*?*/                 aStartPoly.Translate( Point(aBounds.GetWidth() / 2, aBounds.GetHeight()) );
/*?*/
/*?*/                 if( aBounds.GetWidth() )
/*?*/                 {
/*?*/                   // #104527# Avoid division by zero. If rLineParameters.GetLineWidth
/*?*/                   // is zero this is a hairline which can be handled as 1.0.
/*?*/                   double fLineWidth(rLineParameters.GetLineWidth() ? (double)rLineParameters.GetLineWidth() : 1.0);
/*?*/
/*?*/                     double fScale( (double)rLineParameters.GetStartWidth() / fLineWidth *
/*?*/                                    (double)SvtGraphicStroke::normalizedArrowWidth / (double)aBounds.GetWidth() );
/*?*/                     aStartPoly.Scale( fScale, fScale );
/*?*/                 }
/*?*/
/*?*/                 if( rLineParameters.IsStartCentered() )
/*?*/                     aStartPoly.Translate( Point(0, -aStartPoly.GetBoundRect().GetHeight() / 2) );
/*?*/             }
/*N*/             if( aEndPoly.GetPointCount() )
/*?*/             {
/*?*/                 Rectangle aBounds( aEndPoly.GetBoundRect() );
/*?*/
/*?*/                 // mirror and translate to origin
/*?*/                 aEndPoly.Scale(-1,-1);
/*?*/                 aEndPoly.Translate( Point(aBounds.GetWidth() / 2, aBounds.GetHeight()) );
/*?*/
/*?*/                 if( aBounds.GetWidth() )
/*?*/                 {
/*?*/                   // #104527# Avoid division by zero. If rLineParameters.GetLineWidth
/*?*/                   // is zero this is a hairline which we can be handled as 1.0.
/*?*/                   double fLineWidth(rLineParameters.GetLineWidth() ? (double)rLineParameters.GetLineWidth() : 1.0);
/*?*/
/*?*/                     double fScale( (double)rLineParameters.GetEndWidth() / fLineWidth *
/*?*/                                    (double)SvtGraphicStroke::normalizedArrowWidth / (double)aBounds.GetWidth() );
/*?*/                     aEndPoly.Scale( fScale, fScale );
/*?*/                 }
/*?*/
/*?*/                 if( rLineParameters.IsEndCentered() )
/*?*/                     aEndPoly.Translate( Point(0, -aEndPoly.GetBoundRect().GetHeight() / 2) );
/*?*/             }
/*N*/
/*N*/             SvtGraphicStroke aStroke( XOutCreatePolygonBezier( aPolyPoly[0], rXOut.GetOutDev() ),
/*N*/                                       XOutCreatePolygonBezier( aStartPoly, rXOut.GetOutDev() ),
/*N*/                                       XOutCreatePolygonBezier( aEndPoly, rXOut.GetOutDev() ),
/*N*/                                       nTransparence / 100.0,
/*N*/                                       rLineParameters.GetLineWidth(),
/*N*/                                       SvtGraphicStroke::capButt,
/*N*/                                       SvtGraphicStroke::joinRound,
/*N*/                                       rLineParameters.GetLinejointMiterUpperBound(),
/*N*/                                       rLineParameters.GetLineStyle() == XLINE_DASH ? rLineParameters.GetDotDash() : SvtGraphicStroke::DashArray() );
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/             ::rtl::OString aStr( aStroke.toString() );
/*N*/ #endif
/*N*/
/*N*/             SvMemoryStream    aMemStm;
/*N*/
/*N*/             aMemStm << aStroke;
/*N*/
/*N*/             pMtf->AddAction( new MetaCommentAction( "XPATHSTROKE_SEQ_BEGIN", 0,
/*N*/                                                     static_cast<const BYTE*>(aMemStm.GetData()),
/*N*/                                                     aMemStm.Seek( STREAM_SEEK_TO_END ) ) );
/*N*/             bMtfCommentWritten = true;
/*N*/         }
/*N*/     }
/*N*/
/*N*/   if(nTransparence)
/*?*/   {
/*?*/       if(nTransparence != 100)
/*?*/       {
/*?*/           // to be shown line has transparence, output via MetaFile
/*?*/           UINT8 nScaledTrans((UINT8)((nTransparence * 255)/100));
/*?*/           Color aTransColor(nScaledTrans, nScaledTrans, nScaledTrans);
/*?*/           Gradient aGradient(GRADIENT_LINEAR, aTransColor, aTransColor);
/*?*/           GDIMetaFile aMetaFile;
/*?*/           VirtualDevice aVDev;
/*?*/           Volume3D aVolume;
/*?*/           MapMode aMap(rXOut.GetOutDev()->GetMapMode());
/*?*/
/*?*/           // StepCount to someting small
/*?*/           aGradient.SetSteps(3);
/*?*/
/*?*/           // get bounds of geometry
/*?*/           if(aPolyPoly.Count())
/*?*/               aVolume.Union(aPolyPoly.GetPolySize());
/*?*/           if(aLinePoly.Count())
/*?*/               aVolume.Union(aLinePoly.GetPolySize());
/*?*/
/*?*/           // get pixel size in logic coor for 1,2 pixel cases
/*?*/           Size aSizeSinglePixel(1, 1);
/*?*/
/*?*/           if(rLineGeometry.DoForceOnePixel() || rLineGeometry.DoForceTwoPixel())
/*?*/               aSizeSinglePixel = rXOut.GetOutDev()->PixelToLogic(aSizeSinglePixel);
/*?*/
/*?*/           // create BoundRectangle
/*?*/           Rectangle aBound(
/*?*/               (INT32)aVolume.MinVec().X(),
/*?*/               (INT32)-aVolume.MaxVec().Y(),
/*?*/               (INT32)aVolume.MaxVec().X(),
/*?*/               (INT32)-aVolume.MinVec().Y());
/*?*/
/*?*/           if(rLineGeometry.DoForceOnePixel() || rLineGeometry.DoForceTwoPixel())
/*?*/           {
/*?*/               // enlarge aBound
/*?*/               if(rLineGeometry.DoForceTwoPixel())
/*?*/               {
/*?*/                   aBound.Right() += 2 * (aSizeSinglePixel.Width() - 1);
/*?*/                   aBound.Bottom() += 2 * (aSizeSinglePixel.Height() - 1);
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   aBound.Right() += (aSizeSinglePixel.Width() - 1);
/*?*/                   aBound.Bottom() += (aSizeSinglePixel.Height() - 1);
/*?*/               }
/*?*/           }
/*?*/
/*?*/           // prepare VDev and MetaFile
/*?*/           aVDev.EnableOutput(FALSE);
/*?*/           aVDev.SetMapMode(rXOut.GetOutDev()->GetMapMode());
/*?*/           aMetaFile.Record(&aVDev);
/*?*/           aVDev.SetLineColor(aLineColor);
/*?*/           aVDev.SetFillColor(aLineColor);
/*?*/           aVDev.SetFont(rXOut.GetOutDev()->GetFont());
/*?*/           aVDev.SetDrawMode(rXOut.GetOutDev()->GetDrawMode());
/*?*/           aVDev.SetRefPoint(rXOut.GetOutDev()->GetRefPoint());
/*?*/
/*?*/           // create output
/*?*/           if(aPolyPoly.Count())
/*?*/           {
/*?*/               PolyPolygon aVCLPolyPoly = aPolyPoly.GetPolyPolygon();
/*?*/
/*?*/               for(UINT16 a=0;a<aVCLPolyPoly.Count();a++)
/*?*/                   aMetaFile.AddAction(new MetaPolygonAction(aVCLPolyPoly[a]));
/*?*/           }
/*?*/
/*?*/           if(aLinePoly.Count())
/*?*/           {
/*?*/               PolyPolygon aVCLLinePoly = aLinePoly.GetPolyPolygon();
/*?*/
/*?*/               if(rLineGeometry.DoForceTwoPixel())
/*?*/               {
/*?*/                   UINT16 a;
/*?*/
/*?*/                   for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                       aMetaFile.AddAction(new MetaPolyLineAction(aVCLLinePoly[a]));
/*?*/
/*?*/                   aVCLLinePoly.Move(aSizeSinglePixel.Width() - 1, 0);
/*?*/
/*?*/                   for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                       aMetaFile.AddAction(new MetaPolyLineAction(aVCLLinePoly[a]));
/*?*/
/*?*/                   aVCLLinePoly.Move(0, aSizeSinglePixel.Height() - 1);
/*?*/
/*?*/                   for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                       aMetaFile.AddAction(new MetaPolyLineAction(aVCLLinePoly[a]));
/*?*/
/*?*/                   aVCLLinePoly.Move(-aSizeSinglePixel.Width() - 1, 0);
/*?*/
/*?*/                   for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                       aMetaFile.AddAction(new MetaPolyLineAction(aVCLLinePoly[a]));
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   for(UINT16 a=0;a<aVCLLinePoly.Count();a++)
/*?*/                       aMetaFile.AddAction(new MetaPolyLineAction(aVCLLinePoly[a]));
/*?*/               }
/*?*/           }
/*?*/
/*?*/           // draw metafile
/*?*/           aMetaFile.Stop();
/*?*/           aMetaFile.WindStart();
/*?*/           aMap.SetOrigin(aBound.TopLeft());
/*?*/           aMetaFile.SetPrefMapMode(aMap);
/*?*/           aMetaFile.SetPrefSize(aBound.GetSize());
/*?*/           rXOut.GetOutDev()->DrawTransparent(aMetaFile, aBound.TopLeft(), aBound.GetSize(), aGradient);
/*?*/       }
/*?*/   }
/*N*/   else
/*N*/   {
/*N*/       // no transparence, simple output
/*N*/       if(aPolyPoly.Count())
/*N*/       {
/*N*/           PolyPolygon aVCLPolyPoly = aPolyPoly.GetPolyPolygon();
/*N*/
/*N*/           rXOut.GetOutDev()->SetLineColor();
/*N*/           rXOut.GetOutDev()->SetFillColor(aLineColor);
/*N*/
/*N*/           for(UINT16 a=0;a<aVCLPolyPoly.Count();a++)
/*N*/               rXOut.GetOutDev()->DrawPolygon(aVCLPolyPoly[a]);
/*N*/       }
/*N*/
/*N*/       if(aLinePoly.Count())
/*N*/       {
/*N*/           PolyPolygon aVCLLinePoly = aLinePoly.GetPolyPolygon();
/*N*/
/*N*/           rXOut.GetOutDev()->SetLineColor(aLineColor);
/*N*/           rXOut.GetOutDev()->SetFillColor();
/*N*/
/*N*/           if(rLineGeometry.DoForceTwoPixel())
/*?*/           {
/*?*/               PolyPolygon aPolyPolyPixel( rXOut.GetOutDev()->LogicToPixel(aVCLLinePoly) );
/*?*/               BOOL bWasEnabled = rXOut.GetOutDev()->IsMapModeEnabled();
/*?*/               rXOut.GetOutDev()->EnableMapMode(FALSE);
/*?*/               UINT16 a;
/*?*/
/*?*/               for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                   rXOut.GetOutDev()->DrawPolyLine(aPolyPolyPixel[a]);
/*?*/
/*?*/               aPolyPolyPixel.Move(1,0);
/*?*/
/*?*/               for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                   rXOut.GetOutDev()->DrawPolyLine(aPolyPolyPixel[a]);
/*?*/
/*?*/               aPolyPolyPixel.Move(0,1);
/*?*/
/*?*/               for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                   rXOut.GetOutDev()->DrawPolyLine(aPolyPolyPixel[a]);
/*?*/
/*?*/               aPolyPolyPixel.Move(-1,0);
/*?*/
/*?*/               for(a=0;a<aVCLLinePoly.Count();a++)
/*?*/                   rXOut.GetOutDev()->DrawPolyLine(aPolyPolyPixel[a]);
/*?*/
/*?*/               rXOut.GetOutDev()->EnableMapMode(bWasEnabled);
/*?*/           }
/*N*/           else
/*N*/           {
/*N*/               for( UINT16 a = 0; a < aVCLLinePoly.Count(); a++ )
/*N*/                 {
/*N*/                     const Polygon&  rPoly = aVCLLinePoly[ a ];
/*N*/                     BOOL            bDrawn = FALSE;
/*N*/
/*N*/                     if( rPoly.GetSize() == 2 )
/*N*/                     {
/*N*/                       if ( !rXOut.GetOutDev()->GetConnectMetaFile() )
/*N*/                       {
/*?*/                           const Line  aLine( rXOut.GetOutDev()->LogicToPixel( rPoly[ 0 ] ),
/*?*/                                              rXOut.GetOutDev()->LogicToPixel( rPoly[ 1 ] ) );
/*?*/
/*?*/                           if( aLine.GetLength() > 16000 )
/*?*/                           {
/*?*/                               Point       aPoint;
/*?*/                               Rectangle   aOutRect( aPoint, rXOut.GetOutDev()->GetOutputSizePixel() );
/*?*/                               Line        aIntersection;
/*?*/
/*?*/                               if( aLine.Intersection( aOutRect, aIntersection ) )
/*?*/                               {
/*?*/                                   rXOut.GetOutDev()->DrawLine( rXOut.GetOutDev()->PixelToLogic( aIntersection.GetStart() ),
/*?*/                                                                rXOut.GetOutDev()->PixelToLogic( aIntersection.GetEnd() ) );
/*?*/                               }
/*?*/                               bDrawn = TRUE;
/*?*/                           }
/*?*/                       }
/*N*/                     }
/*N*/                     if( !bDrawn )
/*N*/                         rXOut.GetOutDev()->DrawPolyLine( rPoly );
/*N*/                 }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/     // #100127# Bracket output with a comment, if recording a Mtf
/*N*/     if( bMtfCommentWritten && pMtf )
/*N*/         pMtf->AddAction( new MetaCommentAction( "XPATHSTROKE_SEQ_END" ) );
/*N*/
/*N*/     rXOut.GetOutDev()->SetDrawMode( nOldDrawMode );
/*N*/ }

//STRIP001 BOOL SdrObject::LineGeometryUsageIsNecessary() const
//STRIP001 {
//STRIP001  XLineStyle eXLS = (XLineStyle)((const XLineStyleItem&)GetItem(XATTR_LINESTYLE)).GetValue();
//STRIP001  return (eXLS != XLINE_NONE);
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 FASTBOOL SdrObject::PaintGluePoints(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  // Nur Klebepunkte der aktuellen ObjList Painten
//STRIP001  if (rInfoRec.pPV==NULL || rInfoRec.pPV->GetObjList()==pObjList) {
//STRIP001      const SdrGluePointList* pGPL=GetGluePointList();
//STRIP001      if (pGPL!=NULL) {
//STRIP001          OutputDevice* pOut=rXOut.GetOutDev();
//STRIP001          pGPL->DrawAll(*pOut,this);
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ SdrObject* SdrObject::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP");  return NULL;//STRIP001
//STRIP001  if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
//STRIP001  Rectangle aO(GetBoundRect());
//STRIP001  aO.Left()-=nTol; aO.Top()-=nTol; aO.Right()+=nTol; aO.Bottom()+=nTol;
//STRIP001  FASTBOOL bRet=aO.IsInside(rPnt);
//STRIP001  return bRet ? (SdrObject*)this : NULL;
/*N*/ }

/*N*/ SdrObject* SdrObject::Clone() const
/*N*/ {
/*N*/   SdrObject* pObj=SdrObjFactory::MakeNewObject(GetObjInventor(),GetObjIdentifier(),NULL);
/*N*/   if (pObj!=NULL) {
/*N*/       pObj->pModel=pModel;
/*N*/       pObj->pPage=pPage;
/*N*/       *pObj=*this;
/*N*/   }
/*N*/   return pObj;
/*N*/ }

/*N*/ SdrObject* SdrObject::Clone(SdrPage* pNewPage, SdrModel* pNewModel) const
/*N*/ {
/*N*/   SdrObject* pObj=SdrObjFactory::MakeNewObject(GetObjInventor(),GetObjIdentifier(),NULL);
/*N*/   if (pObj!=NULL) {
/*N*/       pObj->pModel=pNewModel;
/*N*/       pObj->pPage=pNewPage;
/*N*/       *pObj=*this;
/*N*/   }
/*N*/   return pObj;
/*N*/ }

/*N*/ void SdrObject::operator=(const SdrObject& rObj)
/*N*/ {
/*N*/   pModel  =rObj.pModel;
/*N*/   aOutRect=rObj.GetBoundRect();
/*N*/   nLayerId=rObj.GetLayer();
/*N*/   aAnchor =rObj.aAnchor;
/*N*/   bVirtObj=rObj.bVirtObj;
/*N*/   bSizProt=rObj.bSizProt;
/*N*/   bMovProt=rObj.bMovProt;
/*N*/   bNoPrint=rObj.bNoPrint;
/*N*/   bMarkProt=rObj.bMarkProt;
/*N*/   //EmptyPresObj wird nicht kopiert: nun doch! (25-07-1995, Joe)
/*N*/   bEmptyPresObj =rObj.bEmptyPresObj;
/*N*/   //NotVisibleAsMaster wird nicht kopiert: nun doch! (25-07-1995, Joe)
/*N*/   bNotVisibleAsMaster=rObj.bNotVisibleAsMaster;
/*N*/
/*N*/   bBoundRectDirty=rObj.bBoundRectDirty;
/*N*/   bSnapRectDirty=TRUE; //rObj.bSnapRectDirty;
/*N*/   bNotMasterCachable=rObj.bNotMasterCachable;
/*N*/   if (pPlusData!=NULL) { delete pPlusData; pPlusData=NULL; }
/*N*/   if (rObj.pPlusData!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        pPlusData=rObj.pPlusData->Clone(this);
/*N*/   }
/*N*/   if (pPlusData!=NULL && pPlusData->pBroadcast!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        delete pPlusData->pBroadcast; // der Broadcaster wird nicht mitkopiert
//STRIP001 /*?*/        pPlusData->pBroadcast=NULL;
/*N*/   }
/*N*/ }

//STRIP001 void SdrObject::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulNONE);
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

//STRIP001 void SdrObject::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralNONE);
//STRIP001 }

//STRIP001 void SdrObject::ImpTakeDescriptionStr(USHORT nStrCacheID, XubString& rStr, USHORT nVal) const
//STRIP001 {
//STRIP001  rStr = ImpGetResStr(nStrCacheID);
//STRIP001
//STRIP001  sal_Char aSearchText1[] = "%O";
//STRIP001  sal_Char aSearchText2[] = "%N";
//STRIP001  xub_StrLen nPos = rStr.SearchAscii(aSearchText1);
//STRIP001
//STRIP001  if(nPos != STRING_NOTFOUND)
//STRIP001  {
//STRIP001      rStr.Erase(nPos, 2);
//STRIP001
//STRIP001      XubString aObjName;
//STRIP001
//STRIP001      TakeObjNameSingul(aObjName);
//STRIP001      rStr.Insert(aObjName, nPos);
//STRIP001  }
//STRIP001
//STRIP001  nPos = rStr.SearchAscii(aSearchText2);
//STRIP001
//STRIP001  if(nPos != STRING_NOTFOUND)
//STRIP001  {
//STRIP001      rStr.Erase(nPos, 2);
//STRIP001      rStr.Insert(UniString::CreateFromInt32(nVal), nPos);
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrObject::GetWinkStr(long nWink, FASTBOOL bNoDegChar) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  if (pModel!=NULL) {
//STRIP001      pModel->TakeWinkStr(nWink,aStr,bNoDegChar);
//STRIP001  }
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 XubString SdrObject::GetMetrStr(long nVal, MapUnit eWantMap, FASTBOOL bNoUnitChars) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  if (pModel!=NULL) {
//STRIP001      pModel->TakeMetricStr(nVal,aStr,bNoUnitChars);
//STRIP001  }
//STRIP001  return aStr;
//STRIP001 }

/*N*/ void SdrObject::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL /*bDetail*/) const
/*N*/ {
/*N*/   rPoly=XPolyPolygon(XPolygon(GetBoundRect()));
/*N*/ }

/*N*/ void SdrObject::TakeContour( XPolyPolygon& rPoly ) const
/*N*/ {
/*N*/   VirtualDevice   aBlackHole;
/*N*/   GDIMetaFile     aMtf;
/*N*/   SdrPaintInfoRec aPaintInfo;
/*N*/   XPolygon        aXPoly;
/*N*/
/*N*/   aBlackHole.EnableOutput( FALSE );
/*N*/   aBlackHole.SetDrawMode( DRAWMODE_NOFILL );
/*N*/
/*N*/   ExtOutputDevice aXOut( &aBlackHole );
/*N*/   SdrObject*      pClone = Clone();
/*N*/
/*N*/   if(pClone && ISA(SdrEdgeObj))
/*N*/   {
/*N*/       // #102344# Flat cloned SdrEdgeObj, copy connections to original object(s).
/*N*/       // This is deleted later at delete pClone.
/*N*/       SdrObject* pLeft = ((SdrEdgeObj*)this)->GetConnectedNode(TRUE);
/*N*/       SdrObject* pRight = ((SdrEdgeObj*)this)->GetConnectedNode(FALSE);
/*N*/
/*N*/       if(pLeft)
/*N*/       {
/*N*/           pClone->ConnectToNode(TRUE, pLeft);
/*N*/       }
/*N*/
/*N*/       if(pRight)
/*N*/       {
/*N*/           pClone->ConnectToNode(FALSE, pRight);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pClone->SetItem(XLineStyleItem(XLINE_SOLID));
/*N*/   pClone->SetItem(XLineColorItem(String(), Color(COL_BLACK)));
/*N*/   pClone->SetItem(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   aMtf.Record( &aBlackHole );
/*N*/   aPaintInfo.nPaintMode = SDRPAINTMODE_DRAFTTEXT | SDRPAINTMODE_DRAFTGRAF;
/*N*/   pClone->Paint( aXOut, aPaintInfo );
/*N*/   delete pClone;
/*N*/   aMtf.Stop();
/*N*/   aMtf.WindStart();
/*N*/   rPoly.Clear();
/*N*/
/*N*/   for( ULONG nActionNum = 0, nActionAnz = aMtf.GetActionCount(); nActionNum < nActionAnz; nActionNum++ )
/*N*/   {
/*N*/       const MetaAction&   rAct = *aMtf.GetAction( nActionNum );
/*N*/       BOOL                bXPoly = FALSE;
/*N*/
/*N*/       switch( rAct.GetType() )
/*N*/       {
/*?*/           case META_RECT_ACTION:
/*?*/           {
/*?*/               const Rectangle& rRect = ( (const MetaRectAction&) rAct ).GetRect();
/*?*/
/*?*/               if( rRect.GetWidth() && rRect.GetHeight() )
/*?*/               {
/*?*/                   aXPoly = rRect;
/*?*/                   bXPoly = TRUE;
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/
/*?*/           case META_ELLIPSE_ACTION:
/*?*/           {
/*?*/               const Rectangle& rRect = ( (const MetaEllipseAction&) rAct ).GetRect();
/*?*/
/*?*/               if( rRect.GetWidth() && rRect.GetHeight() )
/*?*/               {
/*?*/                   aXPoly = XPolygon( rRect.Center(), rRect.GetWidth() >> 1, rRect.GetHeight() >> 1 );
/*?*/                   bXPoly = TRUE;
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/
/*N*/           case META_POLYGON_ACTION:
/*N*/           {
/*N*/               const Polygon& rPoly = ( (const MetaPolygonAction&) rAct ).GetPolygon();
/*N*/
/*N*/               if( rPoly.GetSize() > 2 )
/*N*/               {
/*N*/                   aXPoly = rPoly;
/*N*/                   bXPoly = TRUE;
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*?*/           case META_POLYPOLYGON_ACTION:
/*?*/           {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                const PolyPolygon& rPolyPoly = ( (const MetaPolyPolygonAction&) rAct ).GetPolyPolygon();
//STRIP001 /*?*/
//STRIP001 /*?*/                if( rPolyPoly.Count() && ( rPolyPoly[ 0 ].GetSize() > 2 ) )
//STRIP001 /*?*/                    rPoly.Insert( rPolyPoly );
/*?*/           }
/*?*/           break;
/*?*/
/*N*/           case META_POLYLINE_ACTION:
/*N*/           {
/*N*/               const Polygon& rPoly = ( (const MetaPolyLineAction&) rAct ).GetPolygon();
/*N*/
/*N*/               if( rPoly.GetSize() > 1 )
/*N*/               {
/*N*/                   aXPoly = rPoly;
/*N*/                   bXPoly = TRUE;
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/           case META_LINE_ACTION:
/*N*/           {
/*N*/               aXPoly = XPolygon( 2 );
/*N*/               aXPoly[ 0 ] = ( (const MetaLineAction&) rAct ).GetStartPoint();
/*N*/               aXPoly[ 1 ] = ( (const MetaLineAction&) rAct ).GetEndPoint();
/*N*/               bXPoly = TRUE;
/*N*/           }
/*N*/           break;
/*N*/
/*N*/           default:
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       if( bXPoly )
/*N*/           rPoly.Insert( aXPoly );
/*N*/   }
/*N*/
/*N*/   // if we only have the outline of the object, we have _no_ contouir
/*N*/   if( rPoly.Count() == 1 )
/*N*/       rPoly.Clear();
/*N*/ }

/*?*/ void SdrObject::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
/*?*/ {
/*?*/ }

// Handles

//STRIP001 USHORT SdrObject::GetHdlCount() const
//STRIP001 {
//STRIP001  return 8;
//STRIP001 }

//STRIP001 SdrHdl* SdrObject::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  SdrHdl* pH=NULL;
//STRIP001  const Rectangle& rR=GetSnapRect();
//STRIP001  switch (nHdlNum) {
//STRIP001      case 0: pH=new SdrHdl(rR.TopLeft(),     HDL_UPLFT); break; // Oben links
//STRIP001      case 1: pH=new SdrHdl(rR.TopCenter(),   HDL_UPPER); break; // Oben
//STRIP001      case 2: pH=new SdrHdl(rR.TopRight(),    HDL_UPRGT); break; // Oben rechts
//STRIP001      case 3: pH=new SdrHdl(rR.LeftCenter(),  HDL_LEFT ); break; // Links
//STRIP001      case 4: pH=new SdrHdl(rR.RightCenter(), HDL_RIGHT); break; // Rechts
//STRIP001      case 5: pH=new SdrHdl(rR.BottomLeft(),  HDL_LWLFT); break; // Unten links
//STRIP001      case 6: pH=new SdrHdl(rR.BottomCenter(),HDL_LOWER); break; // Unten
//STRIP001      case 7: pH=new SdrHdl(rR.BottomRight(), HDL_LWRGT); break; // Unten rechts
//STRIP001  }
//STRIP001  return pH;
//STRIP001 }

//STRIP001 USHORT SdrObject::GetPlusHdlCount(const SdrHdl& rHdl) const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//STRIP001 SdrHdl* SdrObject::GetPlusHdl(const SdrHdl& rHdl, USHORT nPlNum) const
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 void SdrObject::AddToHdlList(SdrHdlList& rHdlList) const
//STRIP001 {
//STRIP001  USHORT nAnz=GetHdlCount();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      SdrHdl* pHdl=GetHdl(i);
//STRIP001      if (pHdl!=NULL) {
//STRIP001          rHdlList.AddHdl(pHdl);
//STRIP001      }
//STRIP001  }
//STRIP001 }

// Drag

//STRIP001 Rectangle SdrObject::ImpDragCalcRect(const SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  Rectangle aTmpRect(GetSnapRect());
//STRIP001  Rectangle aRect(aTmpRect);
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  SdrHdlKind eHdl=pHdl==NULL ? HDL_MOVE : pHdl->GetKind();
//STRIP001  FASTBOOL bEcke=(eHdl==HDL_UPLFT || eHdl==HDL_UPRGT || eHdl==HDL_LWLFT || eHdl==HDL_LWRGT);
//STRIP001  FASTBOOL bOrtho=rDrag.GetView()!=NULL && rDrag.GetView()->IsOrtho();
//STRIP001  FASTBOOL bBigOrtho=bEcke && bOrtho && rDrag.GetView()->IsBigOrtho();
//STRIP001  Point aPos(rDrag.GetNow());
//STRIP001  FASTBOOL bLft=(eHdl==HDL_UPLFT || eHdl==HDL_LEFT  || eHdl==HDL_LWLFT);
//STRIP001  FASTBOOL bRgt=(eHdl==HDL_UPRGT || eHdl==HDL_RIGHT || eHdl==HDL_LWRGT);
//STRIP001  FASTBOOL bTop=(eHdl==HDL_UPRGT || eHdl==HDL_UPPER || eHdl==HDL_UPLFT);
//STRIP001  FASTBOOL bBtm=(eHdl==HDL_LWRGT || eHdl==HDL_LOWER || eHdl==HDL_LWLFT);
//STRIP001  if (bLft) aTmpRect.Left()  =aPos.X();
//STRIP001  if (bRgt) aTmpRect.Right() =aPos.X();
//STRIP001  if (bTop) aTmpRect.Top()   =aPos.Y();
//STRIP001  if (bBtm) aTmpRect.Bottom()=aPos.Y();
//STRIP001  if (bOrtho) { // Ortho
//STRIP001      long nWdt0=aRect.Right() -aRect.Left();
//STRIP001      long nHgt0=aRect.Bottom()-aRect.Top();
//STRIP001      long nXMul=aTmpRect.Right() -aTmpRect.Left();
//STRIP001      long nYMul=aTmpRect.Bottom()-aTmpRect.Top();
//STRIP001      long nXDiv=nWdt0;
//STRIP001      long nYDiv=nHgt0;
//STRIP001      FASTBOOL bXNeg=(nXMul<0)!=(nXDiv<0);
//STRIP001      FASTBOOL bYNeg=(nYMul<0)!=(nYDiv<0);
//STRIP001      nXMul=Abs(nXMul);
//STRIP001      nYMul=Abs(nYMul);
//STRIP001      nXDiv=Abs(nXDiv);
//STRIP001      nYDiv=Abs(nYDiv);
//STRIP001      Fraction aXFact(nXMul,nXDiv); // Fractions zum kuerzen
//STRIP001      Fraction aYFact(nYMul,nYDiv); // und zum vergleichen
//STRIP001      nXMul=aXFact.GetNumerator();
//STRIP001      nYMul=aYFact.GetNumerator();
//STRIP001      nXDiv=aXFact.GetDenominator();
//STRIP001      nYDiv=aYFact.GetDenominator();
//STRIP001      if (bEcke) { // Eckpunkthandles
//STRIP001          FASTBOOL bUseX=(aXFact<aYFact) != bBigOrtho;
//STRIP001          if (bUseX) {
//STRIP001              long nNeed=long(BigInt(nHgt0)*BigInt(nXMul)/BigInt(nXDiv));
//STRIP001              if (bYNeg) nNeed=-nNeed;
//STRIP001              if (bTop) aTmpRect.Top()=aTmpRect.Bottom()-nNeed;
//STRIP001              if (bBtm) aTmpRect.Bottom()=aTmpRect.Top()+nNeed;
//STRIP001          } else {
//STRIP001              long nNeed=long(BigInt(nWdt0)*BigInt(nYMul)/BigInt(nYDiv));
//STRIP001              if (bXNeg) nNeed=-nNeed;
//STRIP001              if (bLft) aTmpRect.Left()=aTmpRect.Right()-nNeed;
//STRIP001              if (bRgt) aTmpRect.Right()=aTmpRect.Left()+nNeed;
//STRIP001          }
//STRIP001      } else { // Scheitelpunkthandles
//STRIP001          if ((bLft || bRgt) && nXDiv!=0) {
//STRIP001              long nHgt0=aRect.Bottom()-aRect.Top();
//STRIP001              long nNeed=long(BigInt(nHgt0)*BigInt(nXMul)/BigInt(nXDiv));
//STRIP001              aTmpRect.Top()-=(nNeed-nHgt0)/2;
//STRIP001              aTmpRect.Bottom()=aTmpRect.Top()+nNeed;
//STRIP001          }
//STRIP001          if ((bTop || bBtm) && nYDiv!=0) {
//STRIP001              long nWdt0=aRect.Right()-aRect.Left();
//STRIP001              long nNeed=long(BigInt(nWdt0)*BigInt(nYMul)/BigInt(nYDiv));
//STRIP001              aTmpRect.Left()-=(nNeed-nWdt0)/2;
//STRIP001              aTmpRect.Right()=aTmpRect.Left()+nNeed;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  aTmpRect.Justify();
//STRIP001  return aTmpRect;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return FALSE; // noch nicht ganz fertig ...
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  if (bSizProt) return FALSE; // Groesse geschuetzt
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  SdrHdlKind eHdl=pHdl==NULL ? HDL_MOVE : pHdl->GetKind();
//STRIP001  if (eHdl==HDL_UPLFT || eHdl==HDL_UPPER || eHdl==HDL_UPRGT ||
//STRIP001      eHdl==HDL_LEFT  ||                    eHdl==HDL_RIGHT ||
//STRIP001      eHdl==HDL_LWLFT || eHdl==HDL_LOWER || eHdl==HDL_LWRGT) return TRUE;
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  Rectangle aNewRect(ImpDragCalcRect(rDrag));
//STRIP001  if (aNewRect!=GetSnapRect()) {
//STRIP001      SetSnapRect(aNewRect);
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrObject::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001 }

//STRIP001 XubString SdrObject::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bDragUndoComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

//STRIP001 void SdrObject::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  Rectangle aTmpRect(ImpDragCalcRect(rDrag));
//STRIP001  rXPP.Insert(XPolygon(aTmpRect));
//STRIP001 }

// Create
//STRIP001 FASTBOOL SdrObject::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rStat.SetOrtho4Possible();
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::MovCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rStat.TakeCreateRect(aOutRect);
//STRIP001  rStat.SetActionRect(aOutRect);
//STRIP001  aOutRect.Justify();
//STRIP001  bBoundRectDirty=TRUE;
//STRIP001  bSnapRectDirty=TRUE;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  rStat.TakeCreateRect(aOutRect);
//STRIP001  aOutRect.Justify();
//STRIP001  SetRectsDirty();
//STRIP001  return (eCmd==SDRCREATE_FORCEEND || rStat.GetPointAnz()>=2);
//STRIP001 }

//STRIP001 void SdrObject::BrkCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::BckCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrObject::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  Rectangle aRect1;
//STRIP001  rDrag.TakeCreateRect(aRect1);
//STRIP001  aRect1.Justify();
//STRIP001  rXPP=XPolyPolygon(XPolygon(aRect1));
//STRIP001 }

/*N*/ Pointer SdrObject::GetCreatePointer() const
/*N*/ {
/*N*/   return Pointer(POINTER_CROSS);
/*N*/ }

// Transformationen
/*N*/ void SdrObject::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   MoveRect(aOutRect,rSiz);
/*N*/   SetRectsDirty();
/*N*/ }

/*N*/ void SdrObject::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   FASTBOOL bXMirr=(xFact.GetNumerator()<0) != (xFact.GetDenominator()<0);
/*N*/   FASTBOOL bYMirr=(yFact.GetNumerator()<0) != (yFact.GetDenominator()<0);
/*N*/   if (bXMirr || bYMirr) {
/*N*/       Point aRef1(GetSnapRect().Center());
/*N*/       if (bXMirr) {
/*N*/           Point aRef2(aRef1);
/*N*/           aRef2.Y()++;
/*N*/           NbcMirrorGluePoints(aRef1,aRef2);
/*N*/       }
/*N*/       if (bYMirr) {
/*N*/           Point aRef2(aRef1);
/*N*/           aRef2.X()++;
/*N*/           NbcMirrorGluePoints(aRef1,aRef2);
/*N*/       }
/*N*/   }
/*N*/   ResizeRect(aOutRect,rRef,xFact,yFact);
/*N*/   SetRectsDirty();
/*N*/ }

/*N*/ void SdrObject::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   SetGlueReallyAbsolute(TRUE);
/*N*/   aOutRect.Move(-rRef.X(),-rRef.Y());
/*N*/   Rectangle R(aOutRect);
/*N*/   if (sn==1.0 && cs==0.0) { // 90?
/*N*/       aOutRect.Left()  =-R.Bottom();
/*N*/       aOutRect.Right() =-R.Top();
/*N*/       aOutRect.Top()   =R.Left();
/*N*/       aOutRect.Bottom()=R.Right();
/*N*/   } else if (sn==0.0 && cs==-1.0) { // 180?
/*N*/       aOutRect.Left()  =-R.Right();
/*N*/       aOutRect.Right() =-R.Left();
/*N*/       aOutRect.Top()   =-R.Bottom();
/*N*/       aOutRect.Bottom()=-R.Top();
/*N*/   } else if (sn==-1.0 && cs==0.0) { // 270?
/*N*/       aOutRect.Left()  =R.Top();
/*N*/       aOutRect.Right() =R.Bottom();
/*N*/       aOutRect.Top()   =-R.Right();
/*N*/       aOutRect.Bottom()=-R.Left();
/*N*/   }
/*N*/   aOutRect.Move(rRef.X(),rRef.Y());
/*N*/   aOutRect.Justify(); // Sicherheitshalber
/*N*/   SetRectsDirty();
/*N*/   NbcRotateGluePoints(rRef,nWink,sn,cs);
/*N*/   SetGlueReallyAbsolute(FALSE);
/*N*/ }

/*N*/ void SdrObject::NbcMirror(const Point& rRef1, const Point& rRef2)
/*N*/ {
/*N*/   SetGlueReallyAbsolute(TRUE);
/*N*/   aOutRect.Move(-rRef1.X(),-rRef1.Y());
/*N*/   Rectangle R(aOutRect);
/*N*/   long dx=rRef2.X()-rRef1.X();
/*N*/   long dy=rRef2.Y()-rRef1.Y();
/*N*/   if (dx==0) {          // Vertikale Achse
/*N*/       aOutRect.Left() =-R.Right();
/*N*/       aOutRect.Right()=-R.Left();
/*N*/   } else if (dy==0) {   // Horizontale Achse
/*N*/       aOutRect.Top()   =-R.Bottom();
/*N*/       aOutRect.Bottom()=-R.Top();
/*N*/   } else if (dx==dy) {  /* 45 Grad Achse \ */
/*N*/       aOutRect.Left()  =R.Top();
/*N*/       aOutRect.Right() =R.Bottom();
/*N*/       aOutRect.Top()   =R.Left();
/*N*/       aOutRect.Bottom()=R.Right();
/*N*/   } else if (dx==-dy) { // 45 Grad Achse /
/*N*/       aOutRect.Left()  =-R.Bottom();
/*N*/       aOutRect.Right() =-R.Top();
/*N*/       aOutRect.Top()   =-R.Right();
/*N*/       aOutRect.Bottom()=-R.Left();
/*N*/   }
/*N*/   aOutRect.Move(rRef1.X(),rRef1.Y());
/*N*/   aOutRect.Justify(); // Sicherheitshalber
/*N*/   SetRectsDirty();
/*N*/   NbcMirrorGluePoints(rRef1,rRef2);
/*N*/   SetGlueReallyAbsolute(FALSE);
/*N*/ }

/*N*/ void SdrObject::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   SetGlueReallyAbsolute(TRUE);
/*N*/   NbcShearGluePoints(rRef,nWink,tn,bVShear);
/*N*/   SetGlueReallyAbsolute(FALSE);
/*N*/ }

/*N*/ void SdrObject::Move(const Size& rSiz)
/*N*/ {
/*N*/   if (rSiz.Width()!=0 || rSiz.Height()!=0) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcMove(rSiz);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_MOVEONLY,aBoundRect0);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   if (xFact.GetNumerator()!=xFact.GetDenominator() || yFact.GetNumerator()!=yFact.GetDenominator()) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcResize(rRef,xFact,yFact);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::Rotate(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   if (nWink!=0) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcRotate(rRef,nWink,sn,cs);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

//STRIP001 void SdrObject::Mirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcMirror(rRef1,rRef2);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

/*N*/ void SdrObject::Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   if (nWink!=0) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcShear(rRef,nWink,tn,bVShear);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::NbcSetRelativePos(const Point& rPnt)
/*N*/ {
/*N*/   Point aRelPos0(GetSnapRect().TopLeft()-aAnchor);
/*N*/   Size aSiz(rPnt.X()-aRelPos0.X(),rPnt.Y()-aRelPos0.Y());
/*N*/   NbcMove(aSiz); // Der ruft auch das SetRectsDirty()
/*N*/ }

/*N*/ void SdrObject::SetRelativePos(const Point& rPnt)
/*N*/ {
/*N*/   if (rPnt!=GetRelativePos()) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcSetRelativePos(rPnt);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_MOVEONLY,aBoundRect0);
/*N*/   }
/*N*/ }
/*N*/
/*N*/ Point SdrObject::GetRelativePos() const
/*N*/ {
/*N*/   return GetSnapRect().TopLeft()-aAnchor;
/*N*/ }
/*N*/
/*N*/ void SdrObject::NbcSetAnchorPos(const Point& rPnt)
/*N*/ {
/*N*/   Size aSiz(rPnt.X()-aAnchor.X(),rPnt.Y()-aAnchor.Y());
/*N*/   aAnchor=rPnt;
/*N*/   NbcMove(aSiz); // Der ruft auch das SetRectsDirty()
/*N*/ }
/*N*/
/*N*/ void SdrObject::SetAnchorPos(const Point& rPnt)
/*N*/ {
/*N*/   if (rPnt!=aAnchor) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       SendRepaintBroadcast();
/*N*/       NbcSetAnchorPos(rPnt);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/       SendUserCall(SDRUSERCALL_MOVEONLY,aBoundRect0);
/*N*/   }
/*N*/ }
/*N*/
/*N*/ const Point& SdrObject::GetAnchorPos() const
/*N*/ {
/*N*/   return aAnchor;
/*N*/ }

/*N*/ void SdrObject::RecalcSnapRect()
/*N*/ {
/*N*/ }

/*N*/ const Rectangle& SdrObject::GetSnapRect() const
/*N*/ {
/*N*/   return aOutRect;
/*N*/ }

/*N*/ void SdrObject::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   aOutRect=rRect;
/*N*/ }

/*N*/ const Rectangle& SdrObject::GetLogicRect() const
/*N*/ {
/*N*/   return GetSnapRect();
/*N*/ }

/*N*/ void SdrObject::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   NbcSetSnapRect(rRect);
/*N*/ }

/*N*/ void SdrObject::SetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   SendRepaintBroadcast();
/*N*/   NbcSetSnapRect(rRect);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/ }

/*N*/ void SdrObject::SetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   SendRepaintBroadcast();
/*N*/   NbcSetLogicRect(rRect);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/ }

/*N*/ long SdrObject::GetRotateAngle() const
/*N*/ {
/*N*/   return 0;
/*N*/ }

/*N*/ long SdrObject::GetShearAngle(FASTBOOL bVertical) const
/*N*/ {
/*N*/   return 0;
/*N*/ }

//STRIP001 USHORT SdrObject::GetSnapPointCount() const
//STRIP001 {
//STRIP001  return GetPointCount();
//STRIP001 }

//STRIP001 Point  SdrObject::GetSnapPoint(USHORT i) const
//STRIP001 {
//STRIP001  return GetPoint(i);
//STRIP001 }

/*N*/ FASTBOOL SdrObject::IsPolyObj() const
/*N*/ {
/*N*/   return FALSE;
/*N*/ }

/*?*/ USHORT SdrObject::GetPointCount() const
/*?*/ {
/*?*/   return 0;
/*?*/ }

/*?*/ const Point& SdrObject::GetPoint(USHORT i) const
/*?*/ {
/*?*/   return *((Point*)NULL);
/*?*/ }

/*N*/ void SdrObject::SetPoint(const Point& rPnt, USHORT i)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   SendRepaintBroadcast();
/*N*/   NbcSetPoint(rPnt,i);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/ }

/*N*/ void SdrObject::NbcSetPoint(const Point& rPnt, USHORT i)
/*N*/ {
/*N*/ }

//STRIP001 USHORT SdrObject::InsPoint(const Point& rPos, FASTBOOL bNewObj, FASTBOOL& rInsNextAfter)
//STRIP001 {
//STRIP001  USHORT nRet=0xFFFF;
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  nRet=NbcInsPoint(rPos,bNewObj,FALSE,rInsNextAfter);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 USHORT SdrObject::NbcInsPoint(const Point& rPos, FASTBOOL bNewObj, FASTBOOL bHideHim, FASTBOOL& rInsNextAfter)
//STRIP001 {
//STRIP001  return 0xFFFF;
//STRIP001 }

//STRIP001 USHORT SdrObject::InsPoint(USHORT i, const Point& rPos, FASTBOOL bInsAfter, FASTBOOL bNewObj)
//STRIP001 {
//STRIP001  USHORT nRet=0xFFFF;
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  nRet=NbcInsPoint(i,rPos,bInsAfter,bNewObj,FALSE);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 USHORT SdrObject::NbcInsPoint(USHORT i, const Point& rPos, FASTBOOL bInsAfter, FASTBOOL bNewObj, FASTBOOL bHideHim)
//STRIP001 {
//STRIP001  return 0xFFFF;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::DelPoint(USHORT i)
//STRIP001 {
//STRIP001  FASTBOOL bRet=TRUE;
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  bRet=NbcDelPoint(i);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::NbcDelPoint(USHORT i)
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 SdrObject* SdrObject::RipPoint(USHORT i, USHORT& rNewPt0Index)
//STRIP001 {
//STRIP001  SdrObject* pRet=NULL;
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  pRet=NbcRipPoint(i,rNewPt0Index);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 SdrObject* SdrObject::NbcRipPoint(USHORT i, USHORT& rNewPt0Index)
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 void SdrObject::Shut()
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcShut();
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

//STRIP001 void SdrObject::NbcShut()
//STRIP001 {
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ FASTBOOL SdrObject::HasTextEdit() const
/*N*/ {
/*N*/   return FALSE;
/*N*/ }

/*N*/ SdrObject* SdrObject::CheckTextEditHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   return CheckHit(rPnt,nTol,pVisiLayer);
/*N*/ }

/*N*/ FASTBOOL SdrObject::BegTextEdit(SdrOutliner& rOutl)
/*N*/ {
/*N*/   return FALSE;
/*N*/ }

/*N*/ void SdrObject::EndTextEdit(SdrOutliner& rOutl)
/*N*/ {
/*N*/ }

/*N*/ void SdrObject::SetOutlinerParaObject(OutlinerParaObject* pTextObject)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   SendRepaintBroadcast();
/*N*/   NbcSetOutlinerParaObject(pTextObject);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   if (GetBoundRect()!=aBoundRect0) {
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject)
/*N*/ {
/*N*/ }

/*N*/ OutlinerParaObject* SdrObject::GetOutlinerParaObject() const
/*N*/ {
/*N*/   return NULL;
/*N*/ }

/*N*/ void SdrObject::NbcReformatText()
/*N*/ {
/*N*/ }

/*N*/ void SdrObject::ReformatText()
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   SendRepaintBroadcast();
/*N*/   NbcReformatText();
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   if (GetBoundRect()!=aBoundRect0) {
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

//STRIP001 void SdrObject::BurnInStyleSheetAttributes( BOOL bPseudoSheetsOnly )
//STRIP001 {
//STRIP001 }

/*N*/ void SdrObject::RestartAnimation(SdrPageView* pPageView) const
/*N*/ {
/*N*/ }

/*N*/ #define Imp2ndKennung (0x434F4D43)
/*N*/ SdrObjUserData* SdrObject::ImpGetMacroUserData() const
/*N*/ {
/*N*/   SdrObjUserData* pData=NULL;
/*N*/   USHORT nAnz=GetUserDataCount();
/*N*/   for (USHORT nNum=nAnz; nNum>0 && pData==NULL;) {
/*N*/       nNum--;
/*N*/       pData=GetUserData(nNum);
/*N*/       if (!pData->HasMacro(this)) pData=NULL;
/*N*/   }
/*N*/   return pData;
/*N*/ }

/*N*/ FASTBOOL SdrObject::HasMacro() const
/*N*/ {
/*N*/   SdrObjUserData* pData=ImpGetMacroUserData();
/*N*/   return pData!=NULL ? pData->HasMacro(this) : FALSE;
/*N*/ }

//STRIP001 SdrObject* SdrObject::CheckMacroHit(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  SdrObjUserData* pData=ImpGetMacroUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      return pData->CheckMacroHit(rRec,this);
//STRIP001  }
//STRIP001  return CheckHit(rRec.aPos,rRec.nTol,rRec.pVisiLayer);
//STRIP001 }

//STRIP001 Pointer SdrObject::GetMacroPointer(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  SdrObjUserData* pData=ImpGetMacroUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      return pData->GetMacroPointer(rRec,this);
//STRIP001  }
//STRIP001  return Pointer(POINTER_REFHAND);
//STRIP001 }

//STRIP001 void SdrObject::PaintMacro(ExtOutputDevice& rXOut, const Rectangle& rDirtyRect, const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  SdrObjUserData* pData=ImpGetMacroUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      pData->PaintMacro(rXOut,rDirtyRect,rRec,this);
//STRIP001  } else {
//STRIP001      Color aBlackColor( COL_BLACK );
//STRIP001      Color aTranspColor( COL_TRANSPARENT );
//STRIP001      rXOut.OverrideLineColor( aBlackColor );
//STRIP001      rXOut.OverrideFillColor( aTranspColor );
//STRIP001      RasterOp eRop0=rXOut.GetRasterOp();
//STRIP001      rXOut.SetRasterOp(ROP_INVERT);
//STRIP001      XPolyPolygon aXPP;
//STRIP001      TakeXorPoly(aXPP,TRUE);
//STRIP001      USHORT nAnz=aXPP.Count();
//STRIP001      for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001          rXOut.DrawXPolyLine(aXPP[nNum]);
//STRIP001      }
//STRIP001      rXOut.SetRasterOp(eRop0);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrObject::DoMacro(const SdrObjMacroHitRec& rRec)
//STRIP001 {
//STRIP001  SdrObjUserData* pData=ImpGetMacroUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      return pData->DoMacro(rRec,this);
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 XubString SdrObject::GetMacroPopupComment(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  SdrObjUserData* pData=ImpGetMacroUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      return pData->GetMacroPopupComment(rRec,this);
//STRIP001  }
//STRIP001  return String();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrObjGeoData* SdrObject::NewGeoData() const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  return new SdrObjGeoData;
/*N*/ }

/*N*/ void SdrObject::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {
/*N*/   rGeo.aBoundRect    =GetBoundRect();
/*N*/   rGeo.aAnchor       =aAnchor       ;
/*N*/   rGeo.bMovProt      =bMovProt      ;
/*N*/   rGeo.bSizProt      =bSizProt      ;
/*N*/   rGeo.bNoPrint      =bNoPrint      ;
/*N*/   rGeo.bClosedObj    =bClosedObj    ;
/*N*/   rGeo.nLayerId      =nLayerId      ;
/*N*/
/*N*/   // Benutzerdefinierte Klebepunkte
/*N*/   if (pPlusData!=NULL && pPlusData->pGluePoints!=NULL) {
/*?*/       if (rGeo.pGPL!=NULL) {
/*?*/           *rGeo.pGPL=*pPlusData->pGluePoints;
/*?*/       } else {
/*?*/           rGeo.pGPL=new SdrGluePointList(*pPlusData->pGluePoints);
/*N*/       }
/*N*/   } else {
/*N*/       if (rGeo.pGPL!=NULL) {
/*?*/           delete rGeo.pGPL;
/*?*/           rGeo.pGPL=NULL;
/*?*/       }
/*N*/   }
/*N*/ }
/*N*/
/*N*/ void SdrObject::RestGeoData(const SdrObjGeoData& rGeo)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SetRectsDirty();
//STRIP001  aOutRect      =rGeo.aBoundRect    ;
//STRIP001  aAnchor       =rGeo.aAnchor       ;
//STRIP001  bMovProt      =rGeo.bMovProt      ;
//STRIP001  bSizProt      =rGeo.bSizProt      ;
//STRIP001  bNoPrint      =rGeo.bNoPrint      ;
//STRIP001  bClosedObj    =rGeo.bClosedObj    ;
//STRIP001  nLayerId      =rGeo.nLayerId      ;
//STRIP001
//STRIP001  // Benutzerdefinierte Klebepunkte
//STRIP001  if (rGeo.pGPL!=NULL) {
//STRIP001      ImpForcePlusData();
//STRIP001      if (pPlusData->pGluePoints!=NULL) {
//STRIP001          *pPlusData->pGluePoints=*rGeo.pGPL;
//STRIP001      } else {
//STRIP001          pPlusData->pGluePoints=new SdrGluePointList(*rGeo.pGPL);
//STRIP001      }
//STRIP001  } else {
//STRIP001      if (pPlusData!=NULL && pPlusData->pGluePoints!=NULL) {
//STRIP001          delete pPlusData->pGluePoints;
//STRIP001          pPlusData->pGluePoints=NULL;
//STRIP001      }
//STRIP001  }
/*N*/ }

/*N*/ SdrObjGeoData* SdrObject::GetGeoData() const
/*N*/ {
/*N*/   SdrObjGeoData* pGeo=NewGeoData();
/*N*/   SaveGeoData(*pGeo);
/*N*/   return pGeo;
/*N*/ }

//STRIP001 void SdrObject::SetGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  RestGeoData(rGeo);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ SfxItemSet* SdrObject::mpEmptyItemSet = 0L;
/*N*/ const SfxItemSet& SdrObject::GetItemSet() const
/*N*/ {
/*N*/   if(!mpEmptyItemSet)
/*N*/       mpEmptyItemSet = ((SdrObject*)this)->CreateNewItemSet((SfxItemPool&)(*GetItemPool()));
/*N*/   DBG_ASSERT(mpEmptyItemSet, "Could not create an SfxItemSet(!)");
/*N*/   DBG_ASSERT(FALSE,"SdrObject::GetItemSet() should never be called, SdrObject has no Items");
/*N*/   return *mpEmptyItemSet;
/*N*/ }

/*N*/ SfxItemSet* SdrObject::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // Basic implementation; Basic object has NO attributes
/*N*/   DBG_ASSERT(FALSE,"SdrObject::CreateNewItemSet() should never be called, SdrObject has no Items");
/*N*/   return new SfxItemSet(rPool, SDRATTR_START, SDRATTR_END);
/*N*/ }

/*N*/ void SdrObject::SetItem( const SfxPoolItem& rItem )
/*N*/ {
/*N*/   sal_uInt16 nWhichID(rItem.Which());
/*N*/
/*N*/   if(AllowItemChange(nWhichID, &rItem))
/*N*/   {
/*N*/       ItemChange(nWhichID, &rItem);
/*N*/       PostItemChange(nWhichID);
/*N*/
/*N*/       SfxItemSet aSet( *GetItemPool(), nWhichID, nWhichID, 0 );
/*N*/       aSet.Put( rItem );
/*N*/       ItemSetChanged( aSet );
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::ClearItem( const sal_uInt16 nWhich )
/*N*/ {
/*N*/   if(AllowItemChange(nWhich))
/*N*/   {
/*N*/       ItemChange(nWhich);
/*N*/       PostItemChange(nWhich);
/*N*/
/*N*/       SfxItemSet aSet( *GetItemPool(), nWhich, nWhich, 0 );
/*N*/       ItemSetChanged( aSet );
/*N*/   }
/*N*/ }
/*N*/
/*N*/ void SdrObject::SetItemSet( const SfxItemSet& rSet )
/*N*/ {
/*N*/   SfxWhichIter aWhichIter(rSet);
/*N*/   sal_uInt16 nWhich(aWhichIter.FirstWhich());
/*N*/   const SfxPoolItem *pPoolItem;
/*N*/   std::vector< sal_uInt16 > aPostItemChangeList;
/*N*/   BOOL bDidChange(FALSE);
/*N*/   SfxItemSet aSet( *GetItemPool(), SDRATTR_START, EE_ITEMS_END, 0 );
/*N*/
/*N*/   while(nWhich)
/*N*/   {
/*N*/       if(SFX_ITEM_SET == rSet.GetItemState(nWhich, FALSE, &pPoolItem))
/*N*/       {
/*N*/           if(AllowItemChange(nWhich, pPoolItem))
/*N*/           {
/*N*/               bDidChange = TRUE;
/*N*/               ItemChange(nWhich, pPoolItem);
/*N*/               aPostItemChangeList.push_back( nWhich );
/*N*/               aSet.Put( *pPoolItem );
/*N*/           }
/*N*/       }
/*N*/       nWhich = aWhichIter.NextWhich();
/*N*/   }
/*N*/
/*N*/   if(bDidChange)
/*N*/   {
/*N*/       std::vector< sal_uInt16 >::iterator aIter = aPostItemChangeList.begin();
/*N*/       const std::vector< sal_uInt16 >::iterator aEnd = aPostItemChangeList.end();
/*N*/       while( aIter != aEnd )
/*N*/       {
/*N*/           PostItemChange((*aIter));
/*N*/           aIter++;
/*N*/       }
/*N*/
/*N*/       ItemSetChanged( aSet );
/*N*/   }
/*N*/ }
/*N*/
/*N*/ ////////////////////////////////////////////////////////////////////////////////////////////////////
/*N*/ // ItemSet was changed, maybe user wants to react
/*N*/
/*N*/ void SdrObject::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SdrObject::BroadcastItemChange(const SdrBroadcastItemChange& rChange)
/*N*/ {
/*N*/   sal_uInt32 nCount(rChange.GetRectangleCount());
/*N*/
/*N*/   sal_uInt32 a; for(a=0; a < nCount; a++)
/*N*/       SendRepaintBroadcast(rChange.GetRectangle(a));
/*N*/
/*N*/   if(ISA(SdrObjGroup))
/*N*/   {
/*N*/       SdrObjListIter aIter(*((SdrObjGroup*)this), IM_DEEPNOGROUPS);
/*N*/       while(aIter.IsMore())
/*N*/       {
/*N*/           SdrObject* pObj = aIter.Next();
/*N*/           SendRepaintBroadcast(pObj->GetBoundRect());
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       SendRepaintBroadcast(GetBoundRect());
/*N*/
/*N*/   for(a = 0; a < nCount; a++)
/*N*/       SendUserCall(SDRUSERCALL_CHGATTR, rChange.GetRectangle(a));
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// syntactical sugar for ItemSet accesses

//STRIP001 void SdrObject::SetItemAndBroadcast(const SfxPoolItem& rItem)
//STRIP001 {
//STRIP001  SdrBroadcastItemChange aC(*this);
//STRIP001  SetItem(rItem);
//STRIP001  BroadcastItemChange(aC);
//STRIP001 }

//STRIP001 void SdrObject::ClearItemAndBroadcast(const sal_uInt16 nWhich)
//STRIP001 {
//STRIP001  SdrBroadcastItemChange aC(*this);
//STRIP001  ClearItem(nWhich);
//STRIP001  BroadcastItemChange(aC);
//STRIP001 }

/*N*/ void SdrObject::SetItemSetAndBroadcast(const SfxItemSet& rSet)
/*N*/ {
/*N*/   SdrBroadcastItemChange aC(*this);
/*N*/   SetItemSet(rSet);
/*N*/   BroadcastItemChange(aC);
/*N*/ }

/*N*/ const SfxPoolItem& SdrObject::GetItem(const sal_uInt16 nWhich) const
/*N*/ {
/*N*/   return GetItemSet().Get(nWhich);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access

/*N*/ BOOL SdrObject::AllowItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem) const
/*N*/ {
/*N*/   return TRUE;
/*N*/ }

/*N*/ void SdrObject::ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem)
/*N*/ {
/*N*/   DBG_ASSERT(FALSE,"SdrObject::ItemChange() should never be called, SdrObject has no Items");
/*N*/ }

/*N*/ void SdrObject::PostItemChange(const sal_uInt16 nWhich)
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrObject::PreSave()
/*N*/ {
/*N*/ }

/*N*/ void SdrObject::PostSave()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrObject::ApplyNotPersistAttr(const SfxItemSet& rAttr)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcApplyNotPersistAttr(rAttr);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/ }

//STRIP001 void SdrObject::NbcApplyNotPersistAttr(const SfxItemSet& rAttr)
//STRIP001 {
//STRIP001  const Rectangle& rSnap=GetSnapRect();
//STRIP001  const Rectangle& rLogic=GetLogicRect();
//STRIP001  Point aRef1(rSnap.Center());
//STRIP001  Point aRef2(aRef1); aRef2.Y()++;
//STRIP001  const SfxPoolItem *pPoolItem=NULL;
//STRIP001  if (rAttr.GetItemState(SDRATTR_TRANSFORMREF1X,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      aRef1.X()=((const SdrTransformRef1XItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_TRANSFORMREF1Y,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      aRef1.Y()=((const SdrTransformRef1YItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_TRANSFORMREF2X,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      aRef2.X()=((const SdrTransformRef2XItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_TRANSFORMREF2Y,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      aRef2.Y()=((const SdrTransformRef2YItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001
//STRIP001  Rectangle aNewSnap(rSnap);
//STRIP001  if (rAttr.GetItemState(SDRATTR_MOVEX,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrMoveXItem*)pPoolItem)->GetValue();
//STRIP001      aNewSnap.Move(n,0);
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_MOVEY,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrMoveYItem*)pPoolItem)->GetValue();
//STRIP001      aNewSnap.Move(0,n);
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_ONEPOSITIONX,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrOnePositionXItem*)pPoolItem)->GetValue();
//STRIP001      aNewSnap.Move(n-aNewSnap.Left(),0);
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_ONEPOSITIONY,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrOnePositionYItem*)pPoolItem)->GetValue();
//STRIP001      aNewSnap.Move(0,n-aNewSnap.Top());
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_ONESIZEWIDTH,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrOneSizeWidthItem*)pPoolItem)->GetValue();
//STRIP001      aNewSnap.Right()=aNewSnap.Left()+n;
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_ONESIZEHEIGHT,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrOneSizeHeightItem*)pPoolItem)->GetValue();
//STRIP001      aNewSnap.Bottom()=aNewSnap.Top()+n;
//STRIP001  }
//STRIP001  if (aNewSnap!=rSnap) {
//STRIP001      if (aNewSnap.GetSize()==rSnap.GetSize()) {
//STRIP001          NbcMove(Size(aNewSnap.Left()-rSnap.Left(),aNewSnap.Top()-rSnap.Top()));
//STRIP001      } else {
//STRIP001          NbcSetSnapRect(aNewSnap);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (rAttr.GetItemState(SDRATTR_SHEARANGLE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrShearAngleItem*)pPoolItem)->GetValue();
//STRIP001      n-=GetShearAngle();
//STRIP001      if (n!=0) {
//STRIP001          double nTan=tan(n*nPi180);
//STRIP001          NbcShear(aRef1,n,nTan,FALSE);
//STRIP001      }
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_ROTATEANGLE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrRotateAngleItem*)pPoolItem)->GetValue();
//STRIP001      n-=GetRotateAngle();
//STRIP001      if (n!=0) {
//STRIP001          double nSin=sin(n*nPi180);
//STRIP001          double nCos=cos(n*nPi180);
//STRIP001          NbcRotate(aRef1,n,nSin,nCos);
//STRIP001      }
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_ROTATEONE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrRotateOneItem*)pPoolItem)->GetValue();
//STRIP001      double nSin=sin(n*nPi180);
//STRIP001      double nCos=cos(n*nPi180);
//STRIP001      NbcRotate(aRef1,n,nSin,nCos);
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_HORZSHEARONE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrHorzShearOneItem*)pPoolItem)->GetValue();
//STRIP001      double nTan=tan(n*nPi180);
//STRIP001      NbcShear(aRef1,n,nTan,FALSE);
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_VERTSHEARONE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrVertShearOneItem*)pPoolItem)->GetValue();
//STRIP001      double nTan=tan(n*nPi180);
//STRIP001      NbcShear(aRef1,n,nTan,TRUE);
//STRIP001  }
//STRIP001
//STRIP001  if (rAttr.GetItemState(SDRATTR_OBJMOVEPROTECT,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      FASTBOOL b=((const SdrObjMoveProtectItem*)pPoolItem)->GetValue();
//STRIP001      SetMoveProtect(b);
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_OBJSIZEPROTECT,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      FASTBOOL b=((const SdrObjSizeProtectItem*)pPoolItem)->GetValue();
//STRIP001      SetResizeProtect(b);
//STRIP001  }
//STRIP001
//STRIP001  /* #67368# move protect always sets size protect */
//STRIP001  if( IsMoveProtect() )
//STRIP001      SetResizeProtect( true );
//STRIP001
//STRIP001  if (rAttr.GetItemState(SDRATTR_OBJPRINTABLE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      FASTBOOL b=((const SdrObjPrintableItem*)pPoolItem)->GetValue();
//STRIP001      SetPrintable(b);
//STRIP001  }
//STRIP001
//STRIP001  SdrLayerID nLayer=SDRLAYER_NOTFOUND;
//STRIP001  if (rAttr.GetItemState(SDRATTR_LAYERID,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      nLayer=((const SdrLayerIdItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_LAYERNAME,TRUE,&pPoolItem)==SFX_ITEM_SET && pModel!=NULL) {
//STRIP001      XubString aLayerName=((const SdrLayerNameItem*)pPoolItem)->GetValue();
//STRIP001      const SdrLayerAdmin* pLayAd=pPage!=NULL ? &pPage->GetLayerAdmin() : pModel!=NULL ? &pModel->GetLayerAdmin() : NULL;
//STRIP001      if (pLayAd!=NULL) {
//STRIP001          const SdrLayer* pLayer=pLayAd->GetLayer(aLayerName, TRUE);
//STRIP001          if (pLayer!=NULL) {
//STRIP001              nLayer=pLayer->GetID();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001  if (nLayer!=SDRLAYER_NOTFOUND) {
//STRIP001      NbcSetLayer(nLayer);
//STRIP001  }
//STRIP001
//STRIP001  if (rAttr.GetItemState(SDRATTR_OBJECTNAME,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      XubString aName=((const SdrObjectNameItem*)pPoolItem)->GetValue();
//STRIP001      SetName(aName);
//STRIP001  }
//STRIP001  Rectangle aNewLogic(rLogic);
//STRIP001  if (rAttr.GetItemState(SDRATTR_LOGICSIZEWIDTH,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrLogicSizeWidthItem*)pPoolItem)->GetValue();
//STRIP001      aNewLogic.Right()=aNewLogic.Left()+n;
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_LOGICSIZEHEIGHT,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      long n=((const SdrLogicSizeHeightItem*)pPoolItem)->GetValue();
//STRIP001      aNewLogic.Bottom()=aNewLogic.Top()+n;
//STRIP001  }
//STRIP001  if (aNewLogic!=rLogic) {
//STRIP001      NbcSetLogicRect(aNewLogic);
//STRIP001  }
//STRIP001  Fraction aResizeX(1,1);
//STRIP001  Fraction aResizeY(1,1);
//STRIP001  if (rAttr.GetItemState(SDRATTR_RESIZEXONE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      aResizeX*=((const SdrResizeXOneItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_RESIZEYONE,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      aResizeY*=((const SdrResizeYOneItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001  if (aResizeX!=Fraction(1,1) || aResizeY!=Fraction(1,1)) {
//STRIP001      NbcResize(aRef1,aResizeX,aResizeY);
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_SetItem(SfxItemSet& rAttr, FASTBOOL bMerge, const SfxPoolItem& rItem)
//STRIP001 {
//STRIP001  if (bMerge) rAttr.MergeValue(rItem,TRUE);
//STRIP001  else rAttr.Put(rItem);
//STRIP001 }

/*N*/ void SdrObject::TakeNotPersistAttr(SfxItemSet& rAttr, FASTBOOL bMerge) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const Rectangle& rSnap=GetSnapRect();
//STRIP001  const Rectangle& rLogic=GetLogicRect();
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrObjMoveProtectItem(IsMoveProtect()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrObjSizeProtectItem(IsResizeProtect()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrObjPrintableItem(IsPrintable()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrRotateAngleItem(GetRotateAngle()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrShearAngleItem(GetShearAngle()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrOneSizeWidthItem(rSnap.GetWidth()-1));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrOneSizeHeightItem(rSnap.GetHeight()-1));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrOnePositionXItem(rSnap.Left()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrOnePositionYItem(rSnap.Top()));
//STRIP001  if (rLogic.GetWidth()!=rSnap.GetWidth()) {
//STRIP001      lcl_SetItem(rAttr,bMerge,SdrLogicSizeWidthItem(rLogic.GetWidth()-1));
//STRIP001  }
//STRIP001  if (rLogic.GetHeight()!=rSnap.GetHeight()) {
//STRIP001      lcl_SetItem(rAttr,bMerge,SdrLogicSizeHeightItem(rLogic.GetHeight()-1));
//STRIP001  }
//STRIP001  if (HasSetName()) {
//STRIP001      XubString aName(GetName());
//STRIP001
//STRIP001      if(aName.Len())
//STRIP001      {
//STRIP001          lcl_SetItem(rAttr, bMerge, SdrObjectNameItem(aName));
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrLayerIdItem(nLayerId));
//STRIP001  const SdrLayerAdmin* pLayAd=pPage!=NULL ? &pPage->GetLayerAdmin() : pModel!=NULL ? &pModel->GetLayerAdmin() : NULL;
//STRIP001  if (pLayAd!=NULL) {
//STRIP001      const SdrLayer* pLayer=pLayAd->GetLayerPerID(nLayerId);
//STRIP001      if (pLayer!=NULL) {
//STRIP001          lcl_SetItem(rAttr,bMerge,SdrLayerNameItem(pLayer->GetName()));
//STRIP001      }
//STRIP001  }
//STRIP001  Point aRef1(rSnap.Center());
//STRIP001  Point aRef2(aRef1); aRef2.Y()++;
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrTransformRef1XItem(aRef1.X()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrTransformRef1YItem(aRef1.Y()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrTransformRef2XItem(aRef2.X()));
//STRIP001  lcl_SetItem(rAttr,bMerge,SdrTransformRef2YItem(aRef2.Y()));
/*N*/ }

/*N*/ SfxStyleSheet* SdrObject::GetStyleSheet() const
/*N*/ {
/*N*/   // Das hier ist ein Hack:
/*N*/   return NULL;
/*N*/ }

/*N*/ void SdrObject::SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/ }

/*N*/ void SdrObject::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/ }

// Das Broadcasting beim Setzen der Attribute wird vom AttrObj gemanagt
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ FASTBOOL SdrObject::IsNode() const
/*N*/ {
/*N*/   return TRUE;
/*N*/ }

/*N*/ SdrGluePoint SdrObject::GetVertexGluePoint(USHORT nPosNum) const
/*N*/ {
/*N*/   Rectangle aR(GetBoundRect());
/*N*/   Point aPt;
/*N*/   switch (nPosNum) {
/*N*/       case 0 : aPt=aR.TopCenter();    break;
/*N*/       case 1 : aPt=aR.RightCenter();  break;
/*N*/       case 2 : aPt=aR.BottomCenter(); break;
/*N*/       case 3 : aPt=aR.LeftCenter();   break;
/*N*/   }
/*N*/   aPt-=GetSnapRect().Center();
/*N*/   SdrGluePoint aGP(aPt);
/*N*/   aGP.SetPercent(FALSE);
/*N*/   return aGP;
/*N*/ }

//STRIP001 SdrGluePoint SdrObject::GetCornerGluePoint(USHORT nPosNum) const
//STRIP001 {
//STRIP001  Rectangle aR(GetBoundRect());
//STRIP001  Point aPt;
//STRIP001  switch (nPosNum) {
//STRIP001      case 0 : aPt=aR.TopLeft();     break;
//STRIP001      case 1 : aPt=aR.TopRight();    break;
//STRIP001      case 2 : aPt=aR.BottomRight(); break;
//STRIP001      case 3 : aPt=aR.BottomLeft();  break;
//STRIP001  }
//STRIP001  aPt-=GetSnapRect().Center();
//STRIP001  SdrGluePoint aGP(aPt);
//STRIP001  aGP.SetPercent(FALSE);
//STRIP001  return aGP;
//STRIP001 }

//STRIP001 const SdrGluePointList* SdrObject::GetGluePointList() const
//STRIP001 {
//STRIP001  if (pPlusData!=NULL) return pPlusData->pGluePoints;
//STRIP001  return NULL;
//STRIP001 }

/*N*/ SdrGluePointList* SdrObject::GetGluePointList()
/*N*/ {
/*N*/   if (pPlusData!=NULL) return pPlusData->pGluePoints;
/*N*/   return NULL;
/*N*/ }

/*N*/ SdrGluePointList* SdrObject::ForceGluePointList()
/*N*/ {
/*N*/   ImpForcePlusData();
/*N*/   if (pPlusData->pGluePoints==NULL) {
/*N*/       pPlusData->pGluePoints=new SdrGluePointList;
/*N*/   }
/*N*/   return pPlusData->pGluePoints;
/*N*/ }

/*N*/ void SdrObject::SetGlueReallyAbsolute(FASTBOOL bOn)
/*N*/ {
/*N*/   // erst Const-Aufruf um zu sehen, ob
/*N*/   // ueberhaupt Klebepunkte da sind
/*N*/   // const-Aufruf erzwingen!
/*N*/   if (GetGluePointList()!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrGluePointList* pGPL=ForceGluePointList();
//STRIP001 /*?*/        pGPL->SetReallyAbsolute(bOn,*this);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::NbcRotateGluePoints(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   // erst Const-Aufruf um zu sehen, ob
/*N*/   // ueberhaupt Klebepunkte da sind
/*N*/   // const-Aufruf erzwingen!
/*N*/   if (GetGluePointList()!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrGluePointList* pGPL=ForceGluePointList();
//STRIP001 /*?*/        pGPL->Rotate(rRef,nWink,sn,cs,this);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::NbcMirrorGluePoints(const Point& rRef1, const Point& rRef2)
/*N*/ {
/*N*/   // erst Const-Aufruf um zu sehen, ob
/*N*/   // ueberhaupt Klebepunkte da sind
/*N*/   // const-Aufruf erzwingen!
/*N*/   if (GetGluePointList()!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrGluePointList* pGPL=ForceGluePointList();
//STRIP001 /*?*/        pGPL->Mirror(rRef1,rRef2,this);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::NbcShearGluePoints(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   // erst Const-Aufruf um zu sehen, ob
/*N*/   // ueberhaupt Klebepunkte da sind
/*N*/   // const-Aufruf erzwingen!
/*N*/   if (GetGluePointList()!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrGluePointList* pGPL=ForceGluePointList();
//STRIP001 /*?*/        pGPL->Shear(rRef,nWink,tn,bVShear,this);
/*N*/   }
/*N*/ }

//STRIP001 FASTBOOL SdrObject::IsEdge() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrObject::ToggleEdgeXor(const SdrDragStat& rDrag, ExtOutputDevice& rXOut, FASTBOOL bTail1, FASTBOOL bTail2, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  Color aBlackColor( COL_BLACK );
//STRIP001  Color aTranspColor( COL_TRANSPARENT );
//STRIP001  rXOut.OverrideLineColor( aBlackColor );
//STRIP001  rXOut.OverrideFillColor( aTranspColor );
//STRIP001  RasterOp eRop0=rXOut.GetRasterOp();
//STRIP001  rXOut.SetRasterOp(ROP_INVERT);
//STRIP001  NspToggleEdgeXor(rDrag,rXOut,bTail1,bTail2,bDetail);
//STRIP001  rXOut.SetRasterOp(eRop0);
//STRIP001 }

//STRIP001 void SdrObject::NspToggleEdgeXor(const SdrDragStat& rDrag, ExtOutputDevice& rXOut, FASTBOOL bTail1, FASTBOOL bTail2, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001 }

/*N*/ void SdrObject::ConnectToNode(FASTBOOL bTail1, SdrObject* pObj)
/*N*/ {
/*N*/ }

/*N*/ void SdrObject::DisconnectFromNode(FASTBOOL bTail1)
/*N*/ {
/*N*/ }

//STRIP001 SdrObject* SdrObject::GetConnectedNode(FASTBOOL bTail1) const
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrObject* SdrObject::ImpConvertToContourObj(SdrObject* pRet, BOOL bForceLineDash) const
//STRIP001 {
//STRIP001  BOOL bNoChange(TRUE);
//STRIP001
//STRIP001  if(pRet->LineGeometryUsageIsNecessary())
//STRIP001  {
//STRIP001      // Polygon aus Bezierkurve interpolieren
//STRIP001      VirtualDevice aVDev;
//STRIP001      MapMode aMap = aVDev.GetMapMode();
//STRIP001      aMap.SetMapUnit(pModel->GetScaleUnit());
//STRIP001      aMap.SetScaleX(pModel->GetScaleFraction());
//STRIP001      aMap.SetScaleY(pModel->GetScaleFraction());
//STRIP001      aVDev.SetMapMode(aMap);
//STRIP001
//STRIP001      ::std::auto_ptr< SdrLineGeometry > aLineGeom( pRet->CreateLinePoly(aVDev, FALSE, FALSE, FALSE) );
//STRIP001         if( aLineGeom.get() )
//STRIP001         {
//STRIP001             PolyPolygon3D& rPolyPoly3D = aLineGeom->GetPolyPoly3D();
//STRIP001             PolyPolygon3D& rLinePoly3D = aLineGeom->GetLinePoly3D();
//STRIP001
//STRIP001          // #107201#
//STRIP001          // Since this may in some cases lead to a count of 0 after
//STRIP001          // the merge i moved the merge to the front.
//STRIP001             if(rPolyPoly3D.Count())
//STRIP001          {
//STRIP001                 rPolyPoly3D.Merge(TRUE);
//STRIP001          }
//STRIP001
//STRIP001             //  || rLinePoly3D.Count() removed; the conversion is ONLY
//STRIP001             // useful when new closed filled polygons are created
//STRIP001             if(rPolyPoly3D.Count() || (bForceLineDash && rLinePoly3D.Count()))
//STRIP001             {
//STRIP001                 SfxItemSet aSet(pRet->GetItemSet());
//STRIP001                 XFillStyle eOldFillStyle = ((const XFillStyleItem&)(aSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001                 SdrPathObj* aLinePolygonPart = NULL;
//STRIP001                 SdrPathObj* aLineLinePart = NULL;
//STRIP001                 BOOL bBuildGroup(FALSE);
//STRIP001
//STRIP001              // #107600#
//STRIP001                 sal_Bool bAddOriginalGeometry(sal_False);
//STRIP001
//STRIP001                 if(rPolyPoly3D.Count())
//STRIP001                 {
//STRIP001                     aLinePolygonPart = new SdrPathObj(OBJ_PATHFILL, rPolyPoly3D.GetXPolyPolygon());
//STRIP001                     aLinePolygonPart->SetModel(pRet->GetModel());
//STRIP001
//STRIP001                     aSet.Put(XLineWidthItem(0L));
//STRIP001                     Color aColorLine = ((const XLineColorItem&)(aSet.Get(XATTR_LINECOLOR))).GetValue();
//STRIP001                     UINT16 nTransLine = ((const XLineTransparenceItem&)(aSet.Get(XATTR_LINETRANSPARENCE))).GetValue();
//STRIP001                     aSet.Put(XFillColorItem(XubString(), aColorLine));
//STRIP001                     aSet.Put(XFillStyleItem(XFILL_SOLID));
//STRIP001                     aSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001                     aSet.Put(XFillTransparenceItem(nTransLine));
//STRIP001
//STRIP001                     aLinePolygonPart->SetItemSet(aSet);
//STRIP001                 }
//STRIP001
//STRIP001                 if(rLinePoly3D.Count())
//STRIP001                 {
//STRIP001                  // #106907#
//STRIP001                  // OBJ_PATHLINE is necessary here, not OBJ_PATHFILL. This is intended
//STRIP001                  // to get a non-filled object. If the poly is closed, the PathObj takes care for
//STRIP001                  // the correct closed state.
//STRIP001                     aLineLinePart = new SdrPathObj(OBJ_PATHLINE, rLinePoly3D.GetXPolyPolygon());
//STRIP001
//STRIP001                  aLineLinePart->SetModel(pRet->GetModel());
//STRIP001
//STRIP001                     aSet.Put(XLineWidthItem(0L));
//STRIP001                     aSet.Put(XFillStyleItem(XFILL_NONE));
//STRIP001                     aSet.Put(XLineStyleItem(XLINE_SOLID));
//STRIP001
//STRIP001                  // #106907#
//STRIP001                  // it is also necessary to switch off line start and ends here
//STRIP001                  aSet.Put(XLineStartWidthItem(0));
//STRIP001                  aSet.Put(XLineEndWidthItem(0));
//STRIP001
//STRIP001                     aLineLinePart->SetItemSet(aSet);
//STRIP001
//STRIP001                     if(aLinePolygonPart)
//STRIP001                         bBuildGroup = TRUE;
//STRIP001                 }
//STRIP001
//STRIP001              // #107600# This test does not depend on !bBuildGroup
//STRIP001                 SdrPathObj* pPath = PTR_CAST(SdrPathObj, pRet);
//STRIP001                 if(pPath && pPath->IsClosed())
//STRIP001                 {
//STRIP001                     if(eOldFillStyle != XFILL_NONE)
//STRIP001                  {
//STRIP001                      // #107600# use new boolean here
//STRIP001                         bAddOriginalGeometry = sal_True;
//STRIP001                  }
//STRIP001                 }
//STRIP001
//STRIP001              // #107600# ask for new boolean, too.
//STRIP001                 if(bBuildGroup || bAddOriginalGeometry)
//STRIP001                 {
//STRIP001                     SdrObject* pGroup = new SdrObjGroup;
//STRIP001                     pGroup->SetModel(pRet->GetModel());
//STRIP001
//STRIP001                  if(bAddOriginalGeometry)
//STRIP001                  {
//STRIP001                      // #107600# Add a clone of the original geometry.
//STRIP001                      aSet.ClearItem();
//STRIP001                      aSet.Put(pRet->GetItemSet());
//STRIP001                      aSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001                      aSet.Put(XLineWidthItem(0L));
//STRIP001
//STRIP001                      SdrObject* pClone = pRet->Clone();
//STRIP001
//STRIP001                      pClone->SetModel(pRet->GetModel());
//STRIP001                      pClone->SetItemSet(aSet);
//STRIP001
//STRIP001                      pGroup->GetSubList()->NbcInsertObject(pClone);
//STRIP001                  }
//STRIP001
//STRIP001                     if(aLinePolygonPart)
//STRIP001                  {
//STRIP001                         pGroup->GetSubList()->NbcInsertObject(aLinePolygonPart);
//STRIP001                  }
//STRIP001
//STRIP001                     if(aLineLinePart)
//STRIP001                  {
//STRIP001                         pGroup->GetSubList()->NbcInsertObject(aLineLinePart);
//STRIP001                  }
//STRIP001
//STRIP001                     pRet = pGroup;
//STRIP001
//STRIP001                  // #107201#
//STRIP001                  // be more careful with the state describing bool
//STRIP001                  bNoChange = FALSE;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if(aLinePolygonPart)
//STRIP001                  {
//STRIP001                         pRet = aLinePolygonPart;
//STRIP001                      // #107201#
//STRIP001                      // be more careful with the state describing bool
//STRIP001                      bNoChange = FALSE;
//STRIP001                  }
//STRIP001                     else if(aLineLinePart)
//STRIP001                  {
//STRIP001                         pRet = aLineLinePart;
//STRIP001                      // #107201#
//STRIP001                      // be more careful with the state describing bool
//STRIP001                      bNoChange = FALSE;
//STRIP001                  }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  if(bNoChange)
//STRIP001  {
//STRIP001      SdrObject* pClone = pRet->Clone();
//STRIP001      pClone->SetModel(pRet->GetModel());
//STRIP001      pRet = pClone;
//STRIP001  }
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

// convert this path object to contour object, even when it is a group
//STRIP001 SdrObject* SdrObject::ConvertToContourObj(SdrObject* pRet, BOOL bForceLineDash) const
//STRIP001 {
//STRIP001  if(pRet->ISA(SdrObjGroup))
//STRIP001  {
//STRIP001      SdrObjList* pObjList = pRet->GetSubList();
//STRIP001      SdrObject* pGroup = new SdrObjGroup;
//STRIP001      pGroup->SetModel(pRet->GetModel());
//STRIP001
//STRIP001      for(UINT32 a=0;a<pObjList->GetObjCount();a++)
//STRIP001      {
//STRIP001          SdrObject* pIterObj = pObjList->GetObj(a);
//STRIP001          pGroup->GetSubList()->NbcInsertObject(ConvertToContourObj(pIterObj, bForceLineDash));
//STRIP001      }
//STRIP001
//STRIP001      pRet = pGroup;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pRet = ImpConvertToContourObj(pRet, bForceLineDash);
//STRIP001  }
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrObject* SdrObject::ConvertToPolyObj(BOOL bBezier, BOOL bLineToArea) const
/*N*/ {
/*N*/   SdrObject* pRet = DoConvertToPolyObj(bBezier);
/*N*/
/*N*/   if(pRet && bLineToArea)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrObject* pNewRet = ConvertToContourObj(pRet);
//STRIP001 /*?*/        delete pRet;
//STRIP001 /*?*/        pRet = pNewRet;
/*N*/   }
/*N*/
/*N*/   return pRet;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrObject* SdrObject::DoConvertToPolyObj(BOOL bBezier) const
/*N*/ {
/*N*/   return NULL;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Streams

/*N*/ void SdrObject::AfterRead()
/*N*/ {
/*N*/   USHORT nAnz=GetUserDataCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       GetUserData(i)->AfterRead();
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrObject");
/*N*/ #endif
/*N*/   rIn>>aOutRect;
/*N*/   rIn>>nLayerId;
/*N*/   rIn>>aAnchor;

    // #97849# when in a Draw/Impress binary import the anchor pos is set it's an error.
    // So, when could figure out that a Draw/Impress is running, correct that position
    // to (0,0). Anchor is not used but with 6.0 and XML no longer ignored in Draw/Impress
    // so this correction needs to be made for objects with that error. These could
    // be created when copying back anchor based draw objects from Calc or Writer to
    // Draw/Impress, this did not reset the anchor position.
/*N*/   if((aAnchor.X() || aAnchor.Y()) && GetModel() && GetModel()->ISA(FmFormModel))
/*N*/   {
/*N*/       // find out which application is running
/*N*/       SfxObjectShell* pObjectShell = ((FmFormModel*)GetModel())->GetObjectShell();
/*N*/
/*N*/       if(pObjectShell)
/*N*/       {
/*N*/           SfxInterface* pInterface = pObjectShell->GetInterface();
/*N*/
/*N*/           if(pInterface)
/*N*/           {
/*N*/               sal_uInt16 nInterfaceID = pInterface->GetInterfaceId();
/*N*/
/*N*/               if(nInterfaceID >= SFX_INTERFACE_SD_START && nInterfaceID <= SFX_INTERFACE_SD_END)
/*N*/               {
/*N*/                   // it's a draw/Impress, reset anchor pos hard
/*N*/                   aAnchor = Point(0, 0);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   BOOL bTemp;
/*N*/   rIn>>bTemp; bMovProt=bTemp;
/*N*/   rIn>>bTemp; bSizProt=bTemp;
/*N*/   rIn>>bTemp; bNoPrint=bTemp;
/*N*/   rIn>>bTemp; bMarkProt=bTemp; // war ganz frueher mal bTextToContour
/*N*/   rIn>>bTemp; bEmptyPresObj=bTemp;
/*N*/   if (rHead.GetVersion()>=4) {
/*N*/       rIn>>bTemp; bNotVisibleAsMaster=bTemp;
/*N*/   }
/*N*/   if (rHead.GetVersion()>=11) { // ab V11 sind Connectors in DownCompat gefasst (mit Flag davor)
/*N*/       rIn>>bTemp;
/*N*/       if (bTemp) {
/*?*/           SdrDownCompat aGluePointsCompat(rIn,STREAM_READ);
/*?*/ #ifdef DBG_UTIL
/*?*/           aGluePointsCompat.SetID("SdrObject(Klebepunkte)");
/*?*/ #endif
/*?*/           if (aGluePointsCompat.GetBytesLeft()!=0) {
/*?*/               ImpForcePlusData();
/*?*/               if (pPlusData->pGluePoints==NULL) pPlusData->pGluePoints=new SdrGluePointList;
/*?*/               rIn>>*pPlusData->pGluePoints;
/*?*/           }
/*N*/       }
/*N*/   } else {
/*N*/       Polygon aTmpPoly;
/*N*/       rIn>>aTmpPoly; // aConnectors; ehemals Konnektoren
/*N*/   }
/*N*/
/*N*/   if (pPlusData!=NULL && pPlusData->pUserDataList!=NULL) {
/*N*/       delete pPlusData->pUserDataList;
/*N*/       pPlusData->pUserDataList=NULL;
/*N*/   }
/*N*/   FASTBOOL bReadUserDataList=FALSE;
/*N*/   SdrDownCompat* pUserDataListCompat=NULL;
/*N*/   if (rHead.GetVersion()>=11) { // ab V11 ist die UserDataList in DownCompat gefasst (mit Flag davor)
/*N*/       rIn>>bTemp;
/*N*/       bReadUserDataList=bTemp;
/*N*/       if (bTemp) {
/*N*/           pUserDataListCompat=new SdrDownCompat(rIn,STREAM_READ); // Record fuer UserDataList oeffnen
/*N*/ #ifdef DBG_UTIL
/*N*/           pUserDataListCompat->SetID("SdrObject(UserDataList)");
/*N*/ #endif
/*N*/       }
/*N*/   } else {
/*N*/       bReadUserDataList=TRUE;
/*N*/   }
/*N*/   if (bReadUserDataList) {
/*N*/       USHORT nUserDataAnz;
/*N*/       rIn>>nUserDataAnz;
/*N*/       if (nUserDataAnz!=0) {
/*N*/           ImpForcePlusData();
/*N*/           pPlusData->pUserDataList=new SdrObjUserDataList;
/*N*/           for (USHORT i=0; i<nUserDataAnz; i++) {
/*N*/               SdrDownCompat* pUserDataCompat=NULL;
/*N*/               if (rHead.GetVersion()>=11) { // ab V11 sind UserData in DownCompat gefasst
/*N*/                   //SdrDownCompat aUserDataCompat(rIn,STREAM_READ); // Record fuer UserData oeffnen (seit V11)
/*N*/                   pUserDataCompat=new SdrDownCompat(rIn,STREAM_READ); // Record fuer UserData oeffnen (seit V11)
/*N*/ #ifdef DBG_UTIL
/*N*/                   pUserDataCompat->SetID("SdrObject(UserData)");
/*N*/ #endif
/*N*/               }
/*N*/               UINT32 nInvent;
/*N*/               UINT16 nIdent;
/*N*/               rIn>>nInvent;
/*N*/               rIn>>nIdent;
/*N*/               SdrObjUserData* pData=SdrObjFactory::MakeNewObjUserData(nInvent,nIdent,this);
/*N*/               if (pData!=NULL)
/*N*/               {
/*N*/                   pData->ReadData(rIn);
/*N*/                   pPlusData->pUserDataList->InsertUserData(pData);
/*N*/               } else {
/*N*/                   // Wenn UserDataFactory nicht gesetzt ist, kann auch keiner
/*N*/                   // etwas mit diesen Daten anfangen; durch Compat werden sie
/*N*/                   // eh ueberlesen, daher ist diese Assertion überflüssig (KA)
/*N*/                   // DBG_ERROR("SdrObject::ReadData(): ObjFactory kann UserData nicht erzeugen");
/*N*/               }
/*N*/               if (pUserDataCompat!=NULL) { // Aha, UserData war eingepackt. Record nun schliessen
/*N*/                   delete pUserDataCompat;
/*N*/                   pUserDataCompat=NULL;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       if (pUserDataListCompat!=NULL) { // Aha, UserDataList war eingepackt. Record nun schliessen
/*N*/           delete pUserDataListCompat;
/*N*/           pUserDataListCompat=NULL;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrObject");
/*N*/ #endif
/*N*/   rOut<<GetBoundRect();
/*N*/   rOut<<nLayerId;
/*N*/   rOut<<aAnchor;
/*N*/   BOOL bTemp;
/*N*/   bTemp=bMovProt;       rOut<<bTemp;
/*N*/   bTemp=bSizProt;       rOut<<bTemp;
/*N*/   bTemp=bNoPrint;       rOut<<bTemp;
/*N*/   bTemp=bMarkProt;      rOut<<bTemp;
/*N*/   bTemp=bEmptyPresObj;  rOut<<bTemp;
/*N*/   bTemp=bNotVisibleAsMaster; rOut<<bTemp;
/*N*/
/*N*/   // Konnektoren
/*N*/   bTemp=pPlusData!=NULL && pPlusData->pGluePoints!=NULL && pPlusData->pGluePoints->GetCount()!=0;
/*N*/   rOut<<bTemp; // Flag fuer GluePointList vorhanden
/*N*/   if (bTemp) {
/*?*/       SdrDownCompat aConnectorsCompat(rOut,STREAM_WRITE); // ab V11 Konnektoren einpacken
/*N*/ #ifdef DBG_UTIL
/*?*/       aConnectorsCompat.SetID("SdrObject(Klebepunkte)");
/*N*/ #endif
/*?*/       rOut<<*pPlusData->pGluePoints;
/*N*/   }

    // UserData
/*N*/   USHORT nUserDataAnz=GetUserDataCount();
/*N*/   bTemp=nUserDataAnz!=0;
/*N*/   rOut<<bTemp;
/*N*/   if (bTemp) {
/*N*/       SdrDownCompat aUserDataListCompat(rOut,STREAM_WRITE); // Record fuer UserDataList oeffnen (seit V11)
/*N*/ #ifdef DBG_UTIL
/*N*/       aUserDataListCompat.SetID("SdrObject(UserDataList)");
/*N*/ #endif
/*N*/       rOut<<nUserDataAnz;
/*N*/       for (USHORT i=0; i<nUserDataAnz; i++) {
/*N*/           SdrDownCompat aUserDataCompat(rOut,STREAM_WRITE); // Record fuer UserData oeffnen (seit V11)
/*N*/ #ifdef DBG_UTIL
/*N*/           aUserDataCompat.SetID("SdrObject(UserData)");
/*N*/ #endif
/*N*/           pPlusData->pUserDataList->GetUserData(i)->WriteData(rOut);
/*N*/       }
/*N*/   }
/*N*/
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrObject& rObj)
/*N*/ {
/*N*/   DBG_ASSERT(!rObj.IsNotPersistent(),"operator>>(SdrObject): Ein nicht persistentes Zeichenobjekts wird gestreamt");
/*N*/   SdrObjIOHeader aHead(rIn,STREAM_READ,&rObj);
/*N*/   rObj.ReadData(aHead,rIn);
/*N*/   return rIn;
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrObject& rObj)
/*N*/ {
/*N*/   DBG_ASSERT(!rObj.IsNotPersistent(),"operator<<(SdrObject): Ein nicht persistentes Zeichenobjekts wird gestreamt");
/*N*/   SdrObjIOHeader aHead(rOut,STREAM_WRITE,&rObj);
/*N*/
/*N*/   if(rObj.ISA(SdrVirtObj))
/*N*/   {
/*N*/       // #108784#
/*N*/       // force to write a naked SdrObj
/*N*/       aHead.nIdentifier = OBJ_NONE;
/*N*/       rObj.SdrObject::WriteData(rOut);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rObj.WriteData(rOut);
/*N*/   }
/*N*/
/*N*/   return rOut;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrObject::SetInserted(FASTBOOL bIns)
/*N*/ {
/*N*/   if (bIns!=bInserted) {
/*N*/       bInserted=bIns;
/*N*/       Rectangle aBoundRect0(GetBoundRect());
/*N*/       if (bIns) SendUserCall(SDRUSERCALL_INSERTED,aBoundRect0);
/*N*/       else SendUserCall(SDRUSERCALL_REMOVED,aBoundRect0);
/*N*/
/*N*/       if (pPlusData!=NULL && pPlusData->pBroadcast!=NULL) { // #42522#
/*N*/           SdrHint aHint(*this);
/*N*/           aHint.SetKind(bIns?HINT_OBJINSERTED:HINT_OBJREMOVED);
/*N*/           pPlusData->pBroadcast->Broadcast(aHint);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::SetMoveProtect(FASTBOOL bProt)
/*N*/ {
/*N*/   bMovProt=bProt;
/*N*/   SetChanged();
/*N*/   if (bInserted && pModel!=NULL) {
/*N*/       SdrHint aHint(*this);
/*N*/       aHint.SetNeedRepaint(FALSE);
/*N*/       pModel->Broadcast(aHint);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::SetResizeProtect(FASTBOOL bProt)
/*N*/ {
/*N*/   bSizProt=bProt;
/*N*/   SetChanged();
/*N*/   if (bInserted && pModel!=NULL) {
/*N*/       SdrHint aHint(*this);
/*N*/       aHint.SetNeedRepaint(FALSE);
/*N*/       pModel->Broadcast(aHint);
/*N*/   }
/*N*/ }

/*N*/ void SdrObject::SetPrintable(FASTBOOL bPrn)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  bNoPrint=!bPrn;
//STRIP001  SetChanged();
//STRIP001  if (bInserted && pModel!=NULL) {
//STRIP001      SdrHint aHint(*this);
//STRIP001      aHint.SetNeedRepaint(FALSE);
//STRIP001      pModel->Broadcast(aHint);
//STRIP001  }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ USHORT SdrObject::GetUserDataCount() const
/*N*/ {
/*N*/   if (pPlusData==NULL || pPlusData->pUserDataList==NULL) return 0;
/*N*/   return pPlusData->pUserDataList->GetUserDataCount();
/*N*/ }

/*N*/ SdrObjUserData* SdrObject::GetUserData(USHORT nNum) const
/*N*/ {
/*N*/   if (pPlusData==NULL || pPlusData->pUserDataList==NULL) return NULL;
/*N*/   return pPlusData->pUserDataList->GetUserData(nNum);
/*N*/ }
/*N*/
/*N*/ void SdrObject::InsertUserData(SdrObjUserData* pData, USHORT nPos)
/*N*/ {
/*N*/   if (pData!=NULL) {
/*N*/       ImpForcePlusData();
/*N*/       if (pPlusData->pUserDataList==NULL) pPlusData->pUserDataList=new SdrObjUserDataList;
/*N*/       pPlusData->pUserDataList->InsertUserData(pData,nPos);
/*N*/   } else {
/*N*/       DBG_ERROR("SdrObject::InsertUserData(): pData ist NULL-Pointer");
/*N*/   }
/*N*/ }

//STRIP001 void SdrObject::DeleteUserData(USHORT nNum)
//STRIP001 {
//STRIP001  USHORT nAnz=GetUserDataCount();
//STRIP001  if (nNum<nAnz) {
//STRIP001      pPlusData->pUserDataList->DeleteUserData(nNum);
//STRIP001      if (nAnz==1)  {
//STRIP001          delete pPlusData->pUserDataList;
//STRIP001          pPlusData->pUserDataList=NULL;
//STRIP001      }
//STRIP001  } else {
//STRIP001      DBG_ERROR("SdrObject::DeleteUserData(): ungueltiger Index");
//STRIP001  }
//STRIP001 }

/*N*/ void SdrObject::SendUserCall(SdrUserCallType eUserCall, const Rectangle& rBoundRect)
/*N*/ {
/*N*/   SdrObjGroup* pGroup = NULL;
/*N*/
/*N*/   if( pObjList && pObjList->GetListKind() == SDROBJLIST_GROUPOBJ )
/*N*/       pGroup = (SdrObjGroup*) pObjList->GetOwnerObj();
/*N*/
/*N*/   if ( pUserCall )
/*N*/   {
/*N*/       // UserCall ausfuehren
/*N*/       pUserCall->Changed( *this, eUserCall, rBoundRect );
/*N*/   }
/*N*/
/*N*/   while( pGroup )
/*N*/   {
/*N*/       // Gruppe benachrichtigen
/*N*/       if( pGroup->GetUserCall() )
/*N*/       {
/*N*/           SdrUserCallType eChildUserType = SDRUSERCALL_CHILD_CHGATTR;
/*N*/
/*N*/           switch( eUserCall )
/*N*/           {
/*N*/               case SDRUSERCALL_MOVEONLY:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_MOVEONLY;
/*N*/               break;
/*N*/
/*N*/               case SDRUSERCALL_RESIZE:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_RESIZE;
/*N*/               break;
/*N*/
/*N*/               case SDRUSERCALL_CHGATTR:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_CHGATTR;
/*N*/               break;
/*N*/
/*N*/               case SDRUSERCALL_DELETE:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_DELETE;
/*N*/               break;
/*N*/
/*N*/               case SDRUSERCALL_COPY:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_COPY;
/*N*/               break;
/*N*/
/*N*/               case SDRUSERCALL_INSERTED:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_INSERTED;
/*N*/               break;
/*N*/
/*N*/               case SDRUSERCALL_REMOVED:
/*N*/                   eChildUserType = SDRUSERCALL_CHILD_REMOVED;
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           pGroup->GetUserCall()->Changed( *this, eChildUserType, rBoundRect );
/*N*/       }
/*N*/
/*N*/       if( pGroup->GetObjList()                                       &&
/*N*/           pGroup->GetObjList()->GetListKind() == SDROBJLIST_GROUPOBJ &&
/*N*/           pGroup != (SdrObjGroup*) pObjList->GetOwnerObj() )
/*N*/           pGroup = (SdrObjGroup*) pObjList->GetOwnerObj();
/*N*/       else
/*N*/           pGroup = NULL;
/*N*/   }
/*N*/ }

// ItemPool fuer dieses Objekt wechseln
/*N*/ void SdrObject::MigrateItemPool(SfxItemPool* pSrcPool, SfxItemPool* pDestPool, SdrModel* pNewModel)
/*N*/ {
/*N*/   // Hier passiert erst was in SdrAttrObj und in SdrObjGroup
/*N*/ }

//STRIP001 FASTBOOL SdrObject::IsTransparent( BOOL bCheckForAlphaChannel ) const
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001
//STRIP001  if( IsGroupObject() )
//STRIP001  {
//STRIP001      SdrObjListIter aIter( *GetSubList(), IM_DEEPNOGROUPS );
//STRIP001
//STRIP001      for( SdrObject* pO = aIter.Next(); pO && !bRet; pO = aIter.Next() )
//STRIP001      {
//STRIP001          SfxItemSet aAttr( pO->GetItemSet() );
//STRIP001
//STRIP001          if( ( ( (const XFillTransparenceItem&) aAttr.Get( XATTR_FILLTRANSPARENCE ) ).GetValue() ||
//STRIP001                ( (const XLineTransparenceItem&) aAttr.Get( XATTR_LINETRANSPARENCE ) ).GetValue() ) ||
//STRIP001              ( ( aAttr.GetItemState( XATTR_FILLFLOATTRANSPARENCE ) == SFX_ITEM_SET ) &&
//STRIP001                ( (const XFillFloatTransparenceItem&) aAttr.Get( XATTR_FILLFLOATTRANSPARENCE ) ).IsEnabled() ) )
//STRIP001          {
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001          else if( pO->ISA( SdrGrafObj ) )
//STRIP001          {
//STRIP001              SdrGrafObj* pGrafObj = (SdrGrafObj*) pO;
//STRIP001              if( ( (const SdrGrafTransparenceItem&) aAttr.Get( SDRATTR_GRAFTRANSPARENCE ) ).GetValue() ||
//STRIP001                     ( pGrafObj->GetGraphicType() == GRAPHIC_BITMAP && pGrafObj->GetGraphic().GetBitmapEx().IsAlpha() ) )
//STRIP001              {
//STRIP001                  bRet = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SfxItemSet aAttr( GetItemSet() );
//STRIP001
//STRIP001      if( ( ( (const XFillTransparenceItem&) aAttr.Get( XATTR_FILLTRANSPARENCE ) ).GetValue() ||
//STRIP001            ( (const XLineTransparenceItem&) aAttr.Get( XATTR_LINETRANSPARENCE ) ).GetValue() ) ||
//STRIP001          ( ( aAttr.GetItemState( XATTR_FILLFLOATTRANSPARENCE ) == SFX_ITEM_SET ) &&
//STRIP001            ( (const XFillFloatTransparenceItem&) aAttr.Get( XATTR_FILLFLOATTRANSPARENCE ) ).IsEnabled() ) )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001      else if( ISA( SdrGrafObj ) )
//STRIP001      {
//STRIP001          SdrGrafObj* pGrafObj = (SdrGrafObj*) this;
//STRIP001
//STRIP001          if( ( (const SdrGrafTransparenceItem&) aAttr.Get( SDRATTR_GRAFTRANSPARENCE ) ).GetValue() ||
//STRIP001                 ( pGrafObj->GetGraphicType() == GRAPHIC_BITMAP && pGrafObj->GetGraphic().GetBitmapEx().IsAlpha() ) )
//STRIP001          {
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SdrObject::getUnoShape()
/*N*/ {
/*N*/   // try weak reference first
/*N*/   uno::Reference< uno::XInterface > xShape( mxUnoShape );
/*N*/
/*N*/   if( !xShape.is() && pPage )
/*N*/   {
/*N*/       uno::Reference< uno::XInterface > xPage( pPage->getUnoPage() );
/*N*/       if( xPage.is() )
/*N*/       {
/*N*/           SvxDrawPage* pDrawPage = SvxDrawPage::getImplementation(xPage);
/*N*/           if( pDrawPage )
/*N*/           {
/*N*/               // create one
/*N*/               xShape = pDrawPage->_CreateShape( this );
/*N*/               mxUnoShape = xShape;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return xShape;
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
/*N*/ BOOL SdrObject::TRGetBaseGeometry(Matrix3D& rMat, XPolyPolygon& rPolyPolygon) const
/*N*/ {
/*N*/   // any kind of SdrObject, just use SnapRect
/*N*/   Rectangle aRectangle(GetSnapRect());
/*N*/
/*N*/   // convert to transformation values
/*N*/   Vector2D aScale((double)aRectangle.GetWidth(), (double)aRectangle.GetHeight());
/*N*/   Vector2D aTranslate((double)aRectangle.Left(), (double)aRectangle.Top());
/*N*/
/*N*/   // position maybe relative to anchorpos, convert
/*N*/   if( pModel->IsWriter() )
/*N*/   {
/*?*/       if(GetAnchorPos().X() != 0 || GetAnchorPos().Y() != 0)
/*?*/           aTranslate -= Vector2D(GetAnchorPos().X(), GetAnchorPos().Y());
/*N*/   }

    // force MapUnit to 100th mm
/*N*/   SfxMapUnit eMapUnit = pModel->GetItemPool().GetMetric(0);
/*N*/   if(eMapUnit != SFX_MAPUNIT_100TH_MM)
/*N*/   {
/*N*/       switch(eMapUnit)
/*N*/       {
/*?*/           case SFX_MAPUNIT_TWIP :
/*?*/           {
/*?*/               // postion
/*?*/               // #104018#
/*?*/               aTranslate.X() = ImplTwipsToMM(aTranslate.X());
/*?*/               aTranslate.Y() = ImplTwipsToMM(aTranslate.Y());
/*?*/
/*?*/               // size
/*?*/               // #104018#
/*?*/               aScale.X() = ImplTwipsToMM(aScale.X());
/*?*/               aScale.Y() = ImplTwipsToMM(aScale.Y());
/*?*/
/*?*/               break;
/*?*/           }
/*?*/           default:
/*?*/           {
/*?*/               DBG_ERROR("TRGetBaseGeometry: Missing unit translation to 100th mm!");
/*?*/           }
/*N*/       }
/*N*/   }

    // build matrix
/*N*/   rMat.Identity();
/*N*/   if(aScale.X() != 1.0 || aScale.Y() != 1.0)
/*N*/       rMat.Scale(aScale.X(), aScale.Y());
/*N*/   if(aTranslate.X() != 0.0 || aTranslate.Y() != 0.0)
/*N*/       rMat.Translate(aTranslate.X(), aTranslate.Y());
/*N*/
/*N*/   return FALSE;
/*N*/ }

// sets the base geometry of the object using infos contained in the homogen 3x3 matrix.
// If it's an SdrPathObj it will use the provided geometry information. The Polygon has
// to use (0,0) as upper left and will be scaled to the given size in the matrix.
/*N*/ void SdrObject::TRSetBaseGeometry(const Matrix3D& rMat, const XPolyPolygon& rPolyPolygon)
/*N*/ {
/*N*/   // break up matrix
/*N*/   Vector2D aScale, aTranslate;
/*N*/   double fShear, fRotate;
/*N*/   rMat.DecomposeAndCorrect(aScale, fShear, fRotate, aTranslate);
/*N*/
/*N*/   // force metric to pool metric
/*N*/   SfxMapUnit eMapUnit = pModel->GetItemPool().GetMetric(0);
/*N*/   if(eMapUnit != SFX_MAPUNIT_100TH_MM)
/*N*/   {
/*N*/       switch(eMapUnit)
/*?*/       {
/*?*/           case SFX_MAPUNIT_TWIP :
/*?*/           {
/*?*/               // position
/*?*/               // #104018#
/*?*/               aTranslate.X() = ImplMMToTwips(aTranslate.X());
/*?*/               aTranslate.Y() = ImplMMToTwips(aTranslate.Y());
/*?*/
/*?*/               // size
/*?*/               // #104018#
/*?*/               aScale.X() = ImplMMToTwips(aScale.X());
/*?*/               aScale.Y() = ImplMMToTwips(aScale.Y());
/*?*/
/*?*/               break;
/*?*/           }
/*?*/           default:
/*?*/           {
/*?*/               DBG_ERROR("TRSetBaseGeometry: Missing unit translation to PoolMetric!");
/*?*/           }
/*?*/       }
/*N*/   }

    // if anchor is used, make position relative to it
/*N*/   if( pModel->IsWriter() )
/*N*/   {
/*?*/       if(GetAnchorPos().X() != 0 || GetAnchorPos().Y() != 0)
/*?*/           aTranslate -= Vector2D(GetAnchorPos().X(), GetAnchorPos().Y());
/*N*/   }
/*N*/
/*N*/   // build BaseRect
/*N*/   Point aPoint(FRound(aTranslate.X()), FRound(aTranslate.Y()));
/*N*/   Rectangle aBaseRect(aPoint, Size(FRound(aScale.X()), FRound(aScale.Y())));
/*N*/
/*N*/   // set BaseRect
/*N*/   SetSnapRect(aBaseRect);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@  @@@@@@  @@@@@  @@@@   @@@@  @@@@@@  @@@@  @@@@@  @@  @@
//  @@  @@ @@  @@     @@  @@    @@  @@ @@  @@   @@   @@  @@ @@  @@ @@  @@
//  @@  @@ @@  @@     @@  @@    @@  @@ @@       @@   @@  @@ @@  @@ @@  @@
//  @@  @@ @@@@@      @@  @@@@  @@@@@@ @@       @@   @@  @@ @@@@@   @@@@
//  @@  @@ @@  @@     @@  @@    @@  @@ @@       @@   @@  @@ @@  @@   @@
//  @@  @@ @@  @@ @@  @@  @@    @@  @@ @@  @@   @@   @@  @@ @@  @@   @@
//   @@@@  @@@@@   @@@@   @@    @@  @@  @@@@    @@    @@@@  @@  @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrObject* SdrObjFactory::MakeNewObject(UINT32 nInvent, UINT16 nIdent, SdrPage* pPage, SdrModel* pModel)
/*N*/ {
/*N*/   if(pModel == NULL && pPage != NULL)
/*N*/       pModel = pPage->GetModel();
/*N*/   SdrObject* pObj = NULL;
/*N*/
/*N*/   if(nInvent == SdrInventor)
/*N*/   {
/*N*/       switch (nIdent)
/*N*/       {
/*N*/           case USHORT(OBJ_NONE       ): pObj=new SdrObject;                   break;
/*N*/           case USHORT(OBJ_GRUP       ): pObj=new SdrObjGroup;                 break;
/*N*/           case USHORT(OBJ_LINE       ): pObj=new SdrPathObj(OBJ_LINE       ); break;
/*N*/           case USHORT(OBJ_POLY       ): pObj=new SdrPathObj(OBJ_POLY       ); break;
/*N*/           case USHORT(OBJ_PLIN       ): pObj=new SdrPathObj(OBJ_PLIN       ); break;
/*N*/           case USHORT(OBJ_PATHLINE   ): pObj=new SdrPathObj(OBJ_PATHLINE   ); break;
/*N*/           case USHORT(OBJ_PATHFILL   ): pObj=new SdrPathObj(OBJ_PATHFILL   ); break;
/*N*/           case USHORT(OBJ_FREELINE   ): pObj=new SdrPathObj(OBJ_FREELINE   ); break;
/*N*/           case USHORT(OBJ_FREEFILL   ): pObj=new SdrPathObj(OBJ_FREEFILL   ); break;
/*?*/           case USHORT(OBJ_PATHPOLY   ): pObj=new SdrPathObj(OBJ_POLY       ); break;
/*?*/           case USHORT(OBJ_PATHPLIN   ): pObj=new SdrPathObj(OBJ_PLIN       ); break;
/*N*/           case USHORT(OBJ_EDGE       ): pObj=new SdrEdgeObj;                  break;
/*N*/           case USHORT(OBJ_RECT       ): pObj=new SdrRectObj;                  break;
/*N*/           case USHORT(OBJ_CIRC       ): pObj=new SdrCircObj(OBJ_CIRC       ); break;
/*N*/           case USHORT(OBJ_SECT       ): pObj=new SdrCircObj(OBJ_SECT       ); break;
/*N*/           case USHORT(OBJ_CARC       ): pObj=new SdrCircObj(OBJ_CARC       ); break;
/*N*/           case USHORT(OBJ_CCUT       ): pObj=new SdrCircObj(OBJ_CCUT       ); break;
/*N*/           case USHORT(OBJ_TEXT       ): pObj=new SdrRectObj(OBJ_TEXT       ); break;
/*?*/           case USHORT(OBJ_TEXTEXT    ): pObj=new SdrRectObj(OBJ_TEXTEXT    ); break;
/*N*/           case USHORT(OBJ_TITLETEXT  ): pObj=new SdrRectObj(OBJ_TITLETEXT  ); break;
/*N*/           case USHORT(OBJ_OUTLINETEXT): pObj=new SdrRectObj(OBJ_OUTLINETEXT); break;
/*N*/           case USHORT(OBJ_MEASURE    ): pObj=new SdrMeasureObj;               break;
/*N*/           case USHORT(OBJ_GRAF       ): pObj=new SdrGrafObj;                  break;
/*N*/           case USHORT(OBJ_OLE2       ): pObj=new SdrOle2Obj;                  break;
/*?*/           case USHORT(OBJ_FRAME      ): pObj=new SdrOle2Obj(TRUE);            break;
/*N*/           case USHORT(OBJ_CAPTION    ): pObj=new SdrCaptionObj;               break;
/*N*/           case USHORT(OBJ_PAGE       ): pObj=new SdrPageObj;                  break;
/*?*/           case USHORT(OBJ_UNO        ): pObj=new SdrUnoObj(String());    break;
/*N*/       }
/*N*/   }

/*N*/   if(pObj == NULL)
/*N*/   {
/*N*/       SdrObjFactory* pFact=new SdrObjFactory(nInvent,nIdent,pPage,pModel);
/*N*/       SdrLinkList& rLL=ImpGetUserMakeObjHdl();
/*N*/       unsigned nAnz=rLL.GetLinkCount();
/*N*/       unsigned i=0;
/*N*/       while (i<nAnz && pObj==NULL) {
/*N*/           rLL.GetLink(i).Call((void*)pFact);
/*N*/           pObj=pFact->pNewObj;
/*N*/           i++;
/*N*/       }
/*N*/       delete pFact;
/*N*/   }
/*N*/
/*N*/   if(pObj == NULL)
/*N*/   {
/*N*/       // Na wenn's denn keiner will ...
/*N*/   }
/*N*/
/*N*/   if(pObj != NULL)
/*N*/   {
/*N*/       if(pPage != NULL)
/*N*/           pObj->SetPage(pPage);
/*N*/       else if(pModel != NULL)
/*?*/           pObj->SetModel(pModel);
/*N*/   }
/*N*/
/*N*/   return pObj;
/*N*/ }

/*N*/ SdrObjUserData* SdrObjFactory::MakeNewObjUserData(UINT32 nInvent, UINT16 nIdent, SdrObject* pObj1)
/*N*/ {
/*N*/   SdrObjUserData* pData=NULL;
/*N*/   if (nInvent==SdrInventor) {
/*N*/       switch (nIdent) {
/*?*/           case USHORT(SDRUSERDATA_OBJGROUPLINK): pData=new ImpSdrObjGroupLinkUserData(pObj1); break;
/*?*/           case USHORT(SDRUSERDATA_OBJTEXTLINK) : pData=new ImpSdrObjTextLinkUserData((SdrTextObj*)pObj1); break;
/*N*/       }
/*N*/   }
/*N*/   if (pData==NULL) {
/*N*/       SdrObjFactory aFact(nInvent,nIdent,pObj1);
/*N*/       SdrLinkList& rLL=ImpGetUserMakeObjUserDataHdl();
/*N*/       unsigned nAnz=rLL.GetLinkCount();
/*N*/       unsigned i=0;
/*N*/       while (i<nAnz && pData==NULL) {
/*N*/           rLL.GetLink(i).Call((void*)&aFact);
/*N*/           pData=aFact.pNewData;
/*N*/           i++;
/*N*/       }
/*N*/   }
/*N*/   return pData;
/*N*/ }

/*N*/ void SdrObjFactory::InsertMakeObjectHdl(const Link& rLink)
/*N*/ {
/*N*/   SdrLinkList& rLL=ImpGetUserMakeObjHdl();
/*N*/   rLL.InsertLink(rLink);
/*N*/ }

/*N*/ void SdrObjFactory::RemoveMakeObjectHdl(const Link& rLink)
/*N*/ {
/*N*/   SdrLinkList& rLL=ImpGetUserMakeObjHdl();
/*N*/   rLL.RemoveLink(rLink);
/*N*/ }

/*N*/ void SdrObjFactory::InsertMakeUserDataHdl(const Link& rLink)
/*N*/ {
/*N*/   SdrLinkList& rLL=ImpGetUserMakeObjUserDataHdl();
/*N*/   rLL.InsertLink(rLink);
/*N*/ }

/*N*/ void SdrObjFactory::RemoveMakeUserDataHdl(const Link& rLink)
/*N*/ {
/*N*/   SdrLinkList& rLL=ImpGetUserMakeObjUserDataHdl();
/*N*/   rLL.RemoveLink(rLink);
/*N*/ }

}
