/*************************************************************************
 *
 *  $RCSfile: svx_svdomeas.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:40 $
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

#include "svdomeas.hxx"
#include <math.h>
#include "svditext.hxx" // enthaelt u.a. define ITEMID_FIELD fuer include flditem
#include "xpoly.hxx"
#include "xoutx.hxx"
#include "svdtrans.hxx"
#include "svdtouch.hxx"
#include "svdhdl.hxx"
#include "svdoutl.hxx"
#include "svddrag.hxx"
#include "svdpool.hxx"
#include "svdattrx.hxx"
#include "svdmodel.hxx"
#include "svdio.hxx"
#include "svdview.hxx"
#include "svdglob.hxx"   // StringCache
#include "svdstr.hrc"    // Objektname

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif

#ifndef _EEITEM_HXX //autogen
#include <eeitem.hxx>
#endif

#ifndef _SVX_XLNSTIT_HXX //autogen
#include "xlnstit.hxx"
#endif

#ifndef _SVX_XLNSTWIT_HXX //autogen
#include "xlnstwit.hxx"
#endif

#ifndef _SVX_XLNEDIT_HXX //autogen
#include "xlnedit.hxx"
#endif

#ifndef _SVX_XLNWTIT_HXX //autogen
#include "xlnwtit.hxx"
#endif

#ifndef _SVX_XLNEDWIT_HXX //autogen
#include "xlnedwit.hxx"
#endif

#ifndef _SVX_XLNSTCIT_HXX //autogen
#include "xlnstcit.hxx"
#endif

#ifndef _SVX_XLNEDCIT_HXX //autogen
#include "xlnedcit.hxx"
#endif

#ifndef _OUTLOBJ_HXX //autogen
#include <outlobj.hxx>
#endif

#ifndef _OUTLINER_HXX //autogen
#include "outliner.hxx"
#endif

#ifndef _EDITOBJ_HXX //autogen
#include <editobj.hxx>
#endif

#include "svdfield.hxx"
#include "flditem.hxx"

#include "svdogrp.hxx"
#include "svdopath.hxx"
#include "svdpage.hxx"

#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif

#ifndef _SVX_SVDOIMP_HXX
#include "svdoimp.hxx"
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrMeasureObjGeoData::SdrMeasureObjGeoData() {}
//STRIP001 SdrMeasureObjGeoData::~SdrMeasureObjGeoData() {}

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SV_IMPL_PERSIST1(SdrMeasureField,SvxFieldData);
/*N*/
/*N*/ __EXPORT SdrMeasureField::~SdrMeasureField()
/*N*/ {
/*N*/ }

/*N*/ SvxFieldData* __EXPORT SdrMeasureField::Clone() const
/*N*/ {
/*N*/   return new SdrMeasureField(*this);
/*N*/ }

/*N*/ int __EXPORT SdrMeasureField::operator==(const SvxFieldData& rSrc) const
/*N*/ {
/*N*/   return eMeasureFieldKind==((SdrMeasureField&)rSrc).GetMeasureFieldKind();
/*N*/ }

/*N*/ void __EXPORT SdrMeasureField::Load(SvPersistStream& rIn)
/*N*/ {
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrMeasureField");
/*N*/ #endif
/*N*/   UINT16 nFieldKind;
/*N*/   rIn>>nFieldKind;
/*N*/   eMeasureFieldKind=(SdrMeasureFieldKind)nFieldKind;
/*N*/ }

/*N*/ void __EXPORT SdrMeasureField::Save(SvPersistStream& rOut)
/*N*/ {
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrMeasureField");
/*N*/ #endif
/*N*/   rOut<<(UINT16)eMeasureFieldKind;
/*N*/ }

/*?*/ void SdrMeasureField::TakeRepresentation(const SdrMeasureObj& rObj, XubString& rStr) const
/*?*/ {
/*?*/   rStr.Erase();
/*?*/   Fraction aMeasureScale(1, 1);
/*?*/   BOOL bTextRota90(FALSE);
/*?*/   BOOL bShowUnit(FALSE);
/*?*/   FieldUnit eMeasureUnit(FUNIT_NONE);
/*?*/   FieldUnit eModUIUnit(FUNIT_NONE);
/*?*/
/*?*/   const SfxItemSet& rSet = rObj.GetItemSet();
/*?*/   bTextRota90 = ((SdrMeasureTextRota90Item&)rSet.Get(SDRATTR_MEASURETEXTROTA90)).GetValue();
/*?*/   eMeasureUnit = ((SdrMeasureUnitItem&)rSet.Get(SDRATTR_MEASUREUNIT)).GetValue();
/*?*/   aMeasureScale = ((SdrMeasureScaleItem&)rSet.Get(SDRATTR_MEASURESCALE)).GetValue();
/*?*/   bShowUnit = ((SdrMeasureShowUnitItem&)rSet.Get(SDRATTR_MEASURESHOWUNIT)).GetValue();
/*?*/   sal_Int16 nNumDigits = ((SdrMeasureDecimalPlacesItem&)rSet.Get(SDRATTR_MEASUREDECIMALPLACES)).GetValue();
/*?*/
/*?*/   SdrModel* pModel = rObj.pModel;
/*?*/
/*?*/   switch(eMeasureFieldKind)
/*?*/   {
/*?*/       case SDRMEASUREFIELD_VALUE:
/*?*/       {
/*?*/           if(pModel)
/*?*/           {
/*?*/               eModUIUnit = pModel->GetUIUnit();
/*?*/
/*?*/               if(eMeasureUnit == FUNIT_NONE)
/*?*/                   eMeasureUnit = eModUIUnit;
/*?*/
/*?*/               INT32 nLen(GetLen(rObj.aPt2 - rObj.aPt1));
/*?*/               Fraction aFact(1,1);
/*?*/
/*?*/               if(eMeasureUnit != eModUIUnit)
/*?*/               {
/*?*/                   // Zur Umrechnung der Einheiten
/*?*/                   aFact *= GetMapFactor(eModUIUnit, eMeasureUnit).X();
/*?*/               }
/*?*/
/*?*/               if(aMeasureScale.GetNumerator() != aMeasureScale.GetDenominator())
/*?*/               {
/*?*/                   aFact *= aMeasureScale;
/*?*/               }
/*?*/
/*?*/               if(aFact.GetNumerator() != aFact.GetDenominator())
/*?*/               {
/*?*/                   // Scaling ueber BigInt, um Ueberlaeufe zu vermeiden
/*?*/                   nLen = BigMulDiv(nLen, aFact.GetNumerator(), aFact.GetDenominator());
/*?*/               }
/*?*/
/*?*/               pModel->TakeMetricStr(nLen, rStr, TRUE, nNumDigits);
/*?*/
/*?*/               if(!aFact.IsValid())
/*?*/               {
/*?*/                   rStr = String();
/*?*/                   rStr += sal_Unicode('?');
/*?*/               }
/*?*/
/*?*/                 sal_Unicode cDec(SvtSysLocale().GetLocaleData().getNumDecimalSep().GetChar(0));
/*?*/
/*?*/               if(rStr.Search(cDec) != STRING_NOTFOUND)
/*?*/               {
/*?*/                   xub_StrLen nLen(rStr.Len() - 1);
/*?*/
/*?*/                   while(rStr.GetChar(nLen) == sal_Unicode('0'))
/*?*/                   {
/*?*/                       rStr.Erase(nLen);
/*?*/                       nLen--;
/*?*/                   }
/*?*/
/*?*/                   if(rStr.GetChar(nLen) == cDec)
/*?*/                   {
/*?*/                       rStr.Erase(nLen);
/*?*/                       nLen--;
/*?*/                   }
/*?*/
/*?*/                   if(!rStr.Len())
/*?*/                       rStr += sal_Unicode('0');
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               // falls kein Model da ... (z.B. Preview im Dialog)
/*?*/               rStr = String();
/*?*/               rStr.AppendAscii("4711");
/*?*/           }
/*?*/
/*?*/           break;
/*?*/       }
/*?*/       case SDRMEASUREFIELD_UNIT:
/*?*/       {
/*?*/           if(bShowUnit)
/*?*/           {
/*?*/               if(rObj.pModel)
/*?*/               {
/*?*/                   eModUIUnit = pModel->GetUIUnit();
/*?*/
/*?*/                   if(eMeasureUnit == FUNIT_NONE)
/*?*/                       eMeasureUnit = eModUIUnit;
/*?*/
/*?*/                   if(bShowUnit)
/*?*/                       pModel->TakeUnitStr(eMeasureUnit, rStr);
/*?*/               }
/*?*/           }
/*?*/
/*?*/           break;
/*?*/       }
/*?*/       case SDRMEASUREFIELD_ROTA90BLANCS:
/*?*/       {
/*?*/           if(bTextRota90)
/*?*/           {
/*?*/               rStr = String();
/*?*/               rStr += sal_Unicode(' ');
/*?*/           }
/*?*/
/*?*/           break;
/*?*/       }
/*?*/   }
/*?*/ }

/*N*/ TYPEINIT1(SdrMeasureObj,SdrTextObj);

/*N*/ void SdrMeasureObj::ForceDefaultAttr()
/*N*/ {
/*N*/   SdrTextObj::ForceDefaultAttr();
/*N*/
/*N*/   //#71958# by default, the show units Bool-Item is set as hard
/*N*/   // attribute to TRUE to aviod confusion when copying SdrMeasureObj's
/*N*/   // from one application to another
/*N*/   ImpForceItemSet();
/*N*/   mpObjectItemSet->Put(SdrMeasureShowUnitItem(TRUE));
/*N*/
/*N*/   XPolygon aXP(4);        //      []
/*N*/   aXP[0] = Point(100,0);    // 0,4__[]__2,4
/*N*/   aXP[1] = Point(200,400);  //    \    /
/*N*/   aXP[2] = Point(0,400);    //     \  /
/*N*/   aXP[3] = Point(100,0);    //      \/1,0
/*N*/
/*N*/   mpObjectItemSet->Put(XLineStartItem(String(), aXP));
/*N*/   mpObjectItemSet->Put(XLineStartWidthItem(200));
/*N*/   mpObjectItemSet->Put(XLineEndItem(String(), aXP));
/*N*/   mpObjectItemSet->Put(XLineEndWidthItem(200));
/*N*/   mpObjectItemSet->Put(XLineStyleItem(XLINE_SOLID));
/*N*/ }

/*N*/ SdrMeasureObj::SdrMeasureObj():
/*N*/   bTextDirty(FALSE)
/*N*/ {
/*N*/ }

/*N*/ SdrMeasureObj::SdrMeasureObj(const Point& rPt1, const Point& rPt2):
/*N*/   aPt1(rPt1),
/*N*/   aPt2(rPt2),
/*N*/   bTextDirty(FALSE)
/*N*/ {
/*N*/ }

/*N*/ SdrMeasureObj::~SdrMeasureObj()
/*N*/ {
/*N*/ }

//STRIP001 void SdrMeasureObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bSelectAllowed    =TRUE;
//STRIP001  rInfo.bMoveAllowed      =TRUE;
//STRIP001  rInfo.bResizeFreeAllowed=TRUE;
//STRIP001  rInfo.bResizePropAllowed=TRUE;
//STRIP001  rInfo.bRotateFreeAllowed=TRUE;
//STRIP001  rInfo.bRotate90Allowed  =TRUE;
//STRIP001  rInfo.bMirrorFreeAllowed=TRUE;
//STRIP001  rInfo.bMirror45Allowed  =TRUE;
//STRIP001  rInfo.bMirror90Allowed  =TRUE;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed     =TRUE;
//STRIP001  rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001  rInfo.bNoOrthoDesired   =TRUE;
//STRIP001  rInfo.bNoContortion     =FALSE;
//STRIP001  rInfo.bCanConvToPath    =FALSE;
//STRIP001  rInfo.bCanConvToPoly    =TRUE;
//STRIP001  rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToContour = (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

/*N*/ UINT16 SdrMeasureObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return (UINT16)OBJ_MEASURE;
/*N*/ }

/*N*/ struct ImpMeasureRec
/*N*/ {
/*N*/   Point                       aPt1;
/*N*/   Point                       aPt2;
/*N*/   SdrMeasureKind              eKind;
/*N*/   SdrMeasureTextHPos          eWantTextHPos;
/*N*/   SdrMeasureTextVPos          eWantTextVPos;
/*N*/   long                        nLineDist;
/*N*/   long                        nHelplineOverhang;
/*N*/   long                        nHelplineDist;
/*N*/   long                        nHelpline1Len;
/*N*/   long                        nHelpline2Len;
/*N*/   FASTBOOL                    bBelowRefEdge;
/*N*/   FASTBOOL                    bTextRota90;
/*N*/   FASTBOOL                    bTextUpsideDown;
/*N*/   long                        nMeasureOverhang;
/*N*/   FieldUnit                   eMeasureUnit;
/*N*/   Fraction                    aMeasureScale;
/*N*/   FASTBOOL                    bShowUnit;
/*N*/   String                      aFormatString;
/*N*/   FASTBOOL                    bTextAutoAngle;
/*N*/   long                        nTextAutoAngleView;
/*N*/   FASTBOOL                    bTextIsFixedAngle;
/*N*/   long                        nTextFixedAngle;
/*N*/ };
/*N*/
/*N*/ struct ImpLineRec
/*N*/ {
/*N*/   Point                       aP1;
/*N*/   Point                       aP2;
/*N*/ };
/*N*/
/*N*/ struct ImpMeasurePoly
/*N*/ {
/*N*/   ImpLineRec                  aMainline1; // die mit dem 1. Pfeil
/*N*/   ImpLineRec                  aMainline2; // die mit dem 2. Pfeil
/*N*/   ImpLineRec                  aMainline3; // die dazwischen
/*N*/   ImpLineRec                  aHelpline1;
/*N*/   ImpLineRec                  aHelpline2;
/*N*/   Rectangle                   aTextRect;
/*N*/   Size                        aTextSize;
/*N*/   long                        nLineLen;
/*N*/   long                        nLineWink;
/*N*/   long                        nTextWink;
/*N*/   long                        nHlpWink;
/*N*/   double                      nLineSin;
/*N*/   double                      nLineCos;
/*N*/   double                      nHlpSin;
/*N*/   double                      nHlpCos;
/*N*/   USHORT                      nMainlineAnz;
/*N*/   SdrMeasureTextHPos          eUsedTextHPos;
/*N*/   SdrMeasureTextVPos          eUsedTextVPos;
/*N*/   long                        nLineWdt2;  // Halbe Strichstaerke
/*N*/   long                        nArrow1Len; // Laenge des 1. Pfeils. Bei Center nur die Haelfte
/*N*/   long                        nArrow2Len; // Laenge des 2. Pfeils. Bei Center nur die Haelfte
/*N*/   long                        nArrow1Wdt; // Breite des 1. Pfeils
/*N*/   long                        nArrow2Wdt; // Breite des 2. Pfeils
/*N*/   long                        nShortLineLen; // Linienlaenge, wenn PfeileAussen
/*N*/   FASTBOOL                    bArrow1Center; // Pfeil 1 zentriert?
/*N*/   FASTBOOL                    bArrow2Center; // Pfeil 2 zentriert?
/*N*/   FASTBOOL                    bAutoUpsideDown; // UpsideDown durch Automatik
/*N*/   FASTBOOL                    bPfeileAussen;
/*N*/   FASTBOOL                    bBreakedLine;
/*N*/ };

/*N*/ void SdrMeasureObj::ImpTakeAttr(ImpMeasureRec& rRec) const
/*N*/ {
/*N*/   rRec.aPt1 = aPt1;
/*N*/   rRec.aPt2 = aPt2;
/*N*/
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   rRec.eKind            =((SdrMeasureKindItem&            )rSet.Get(SDRATTR_MEASUREKIND            )).GetValue();
/*N*/   rRec.eWantTextHPos    =((SdrMeasureTextHPosItem&        )rSet.Get(SDRATTR_MEASURETEXTHPOS        )).GetValue();
/*N*/   rRec.eWantTextVPos    =((SdrMeasureTextVPosItem&        )rSet.Get(SDRATTR_MEASURETEXTVPOS        )).GetValue();
/*N*/   rRec.nLineDist        =((SdrMeasureLineDistItem&        )rSet.Get(SDRATTR_MEASURELINEDIST        )).GetValue();
/*N*/   rRec.nHelplineOverhang=((SdrMeasureHelplineOverhangItem&)rSet.Get(SDRATTR_MEASUREHELPLINEOVERHANG)).GetValue();
/*N*/   rRec.nHelplineDist    =((SdrMeasureHelplineDistItem&    )rSet.Get(SDRATTR_MEASUREHELPLINEDIST    )).GetValue();
/*N*/   rRec.nHelpline1Len    =((SdrMeasureHelpline1LenItem&    )rSet.Get(SDRATTR_MEASUREHELPLINE1LEN    )).GetValue();
/*N*/   rRec.nHelpline2Len    =((SdrMeasureHelpline2LenItem&    )rSet.Get(SDRATTR_MEASUREHELPLINE2LEN    )).GetValue();
/*N*/   rRec.bBelowRefEdge    =((SdrMeasureBelowRefEdgeItem&    )rSet.Get(SDRATTR_MEASUREBELOWREFEDGE    )).GetValue();
/*N*/   rRec.bTextRota90      =((SdrMeasureTextRota90Item&      )rSet.Get(SDRATTR_MEASURETEXTROTA90      )).GetValue();
/*N*/   rRec.bTextUpsideDown  =((SdrMeasureTextUpsideDownItem&  )rSet.Get(SDRATTR_MEASURETEXTUPSIDEDOWN  )).GetValue();
/*N*/   rRec.nMeasureOverhang =((SdrMeasureOverhangItem&        )rSet.Get(SDRATTR_MEASUREOVERHANG        )).GetValue();
/*N*/   rRec.eMeasureUnit     =((SdrMeasureUnitItem&            )rSet.Get(SDRATTR_MEASUREUNIT            )).GetValue();
/*N*/   rRec.aMeasureScale    =((SdrMeasureScaleItem&           )rSet.Get(SDRATTR_MEASURESCALE           )).GetValue();
/*N*/   rRec.bShowUnit        =((SdrMeasureShowUnitItem&        )rSet.Get(SDRATTR_MEASURESHOWUNIT        )).GetValue();
/*N*/   rRec.aFormatString    =((SdrMeasureFormatStringItem&    )rSet.Get(SDRATTR_MEASUREFORMATSTRING    )).GetValue();
/*N*/   rRec.bTextAutoAngle    =((SdrMeasureTextAutoAngleItem&    )rSet.Get(SDRATTR_MEASURETEXTAUTOANGLE    )).GetValue();
/*N*/   rRec.nTextAutoAngleView=((SdrMeasureTextAutoAngleViewItem&)rSet.Get(SDRATTR_MEASURETEXTAUTOANGLEVIEW)).GetValue();
/*N*/   rRec.bTextIsFixedAngle =((SdrMeasureTextIsFixedAngleItem& )rSet.Get(SDRATTR_MEASURETEXTISFIXEDANGLE )).GetValue();
/*N*/   rRec.nTextFixedAngle   =((SdrMeasureTextFixedAngleItem&   )rSet.Get(SDRATTR_MEASURETEXTFIXEDANGLE   )).GetValue();
/*N*/ }

/*N*/ void SdrMeasureObj::ImpCalcGeometrics(const ImpMeasureRec& rRec, ImpMeasurePoly& rPol) const
/*N*/ {
/*N*/   Point aP1(rRec.aPt1);
/*N*/   Point aP2(rRec.aPt2);
/*N*/   Point aDelt(aP2); aDelt-=aP1;
/*N*/
/*N*/   rPol.aTextSize=GetTextSize();
/*N*/   rPol.nLineLen=GetLen(aDelt);
/*N*/
/*N*/   rPol.nLineWdt2=0;
/*N*/   long nArrow1Len=0; FASTBOOL bArrow1Center=FALSE;
/*N*/   long nArrow2Len=0; FASTBOOL bArrow2Center=FALSE;
/*N*/   long nArrow1Wdt=0;
/*N*/   long nArrow2Wdt=0;
/*N*/   rPol.nArrow1Wdt=0;
/*N*/   rPol.nArrow2Wdt=0;
/*N*/   long nArrowNeed=0;
/*N*/   long nShortLen=0;
/*N*/   FASTBOOL bPfeileAussen=FALSE;
/*N*/
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   sal_Int32 nLineWdt = ((XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue(); // Strichstaerke
/*N*/   rPol.nLineWdt2 = (nLineWdt + 1) / 2;
/*N*/
/*N*/   nArrow1Wdt = ((const XLineStartWidthItem&)(rSet.Get(XATTR_LINESTARTWIDTH))).GetValue();
/*N*/   if(nArrow1Wdt < 0)
/*N*/       nArrow1Wdt = -nLineWdt * nArrow1Wdt / 100; // <0 = relativ
/*N*/
/*N*/   nArrow2Wdt = ((const XLineEndWidthItem&)(rSet.Get(XATTR_LINEENDWIDTH))).GetValue();
/*N*/   if(nArrow2Wdt < 0)
/*N*/       nArrow2Wdt = -nLineWdt * nArrow2Wdt / 100; // <0 = relativ
/*N*/
/*N*/   XPolygon aPol1(((const XLineStartItem&)(rSet.Get(XATTR_LINESTART))).GetValue());
/*N*/   XPolygon aPol2(((const XLineEndItem&)(rSet.Get(XATTR_LINEEND))).GetValue());
/*N*/   bArrow1Center = ((const XLineStartCenterItem&)(rSet.Get(XATTR_LINESTARTCENTER))).GetValue();
/*N*/   bArrow2Center = ((const XLineEndCenterItem&)(rSet.Get(XATTR_LINEENDCENTER))).GetValue();
/*N*/   nArrow1Len = XOutputDevice::InitLineStartEnd(aPol1, nArrow1Wdt, bArrow1Center) - 1;
/*N*/   nArrow2Len = XOutputDevice::InitLineStartEnd(aPol2, nArrow2Wdt, bArrow2Center) - 1;
/*N*/
/*N*/   // nArrowLen ist bei bCenter bereits halbiert
/*N*/   // Bei 2 Pfeilen a 4mm ist unter 10mm Schluss.
/*N*/   nArrowNeed=nArrow1Len+nArrow2Len+(nArrow1Wdt+nArrow2Wdt)/2;
/*N*/   if (rPol.nLineLen<nArrowNeed) bPfeileAussen=TRUE;
/*N*/   nShortLen=(nArrow1Len+nArrow1Wdt + nArrow2Len+nArrow2Wdt) /2;
/*N*/
/*N*/   rPol.eUsedTextHPos=rRec.eWantTextHPos;
/*N*/   rPol.eUsedTextVPos=rRec.eWantTextVPos;
/*N*/   if (rPol.eUsedTextVPos==SDRMEASURE_TEXTVAUTO) rPol.eUsedTextVPos=SDRMEASURE_ABOVE;
/*N*/   FASTBOOL bBrkLine=rPol.eUsedTextVPos==SDRMEASURETEXT_BREAKEDLINE;
/*N*/   if (rPol.eUsedTextVPos==SDRMEASURETEXT_VERTICALCENTERED) {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (pOutlinerParaObject!=NULL && pOutlinerParaObject->GetTextObject().GetParagraphCount()==1) {
//STRIP001 /*?*/            bBrkLine=TRUE; // Unterbrochene Linie, wenn nur 1 Absatz.
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   rPol.bBreakedLine=bBrkLine;
/*N*/   if (rPol.eUsedTextHPos==SDRMEASURE_TEXTHAUTO) { // bei zu breitem Text diesen eventuell nach aussen schieben
/*N*/       FASTBOOL bOutside=FALSE;
/*N*/       long nNeedSiz=!rRec.bTextRota90 ? rPol.aTextSize.Width() : rPol.aTextSize.Height();
/*N*/       if (nNeedSiz>rPol.nLineLen) bOutside=TRUE; // Text passt nicht in die Mitte
/*N*/       if (bBrkLine) {
/*N*/           if (nNeedSiz+nArrowNeed>rPol.nLineLen) bPfeileAussen=TRUE; // Text passt in die Mitte, wenn die Pfeile nach aussen kommen
/*N*/       } else {
/*N*/           long nSmallNeed=nArrow1Len+nArrow2Len+(nArrow1Wdt+nArrow2Wdt)/2/4;
/*N*/           if (nNeedSiz+nSmallNeed>rPol.nLineLen) bPfeileAussen=TRUE; // Text passt in die Mitte, wenn die Pfeile nach aussen kommen
/*N*/       }
/*N*/       rPol.eUsedTextHPos=bOutside ? SDRMEASURE_TEXTLEFTOUTSIDE : SDRMEASURE_TEXTINSIDE;
/*N*/   }
/*N*/   if (rPol.eUsedTextHPos!=SDRMEASURE_TEXTINSIDE) bPfeileAussen=TRUE;
/*N*/   rPol.nArrow1Wdt=nArrow1Wdt;
/*N*/   rPol.nArrow2Wdt=nArrow2Wdt;
/*N*/   rPol.nShortLineLen=nShortLen;
/*N*/   rPol.bPfeileAussen=bPfeileAussen;
/*N*/   rPol.nArrow1Len=nArrow1Len;
/*N*/   rPol.bArrow1Center=bArrow1Center;
/*N*/   rPol.nArrow2Len=nArrow2Len;
/*N*/   rPol.bArrow2Center=bArrow2Center;
/*N*/
/*N*/   rPol.nLineWink=GetAngle(aDelt);
/*N*/   double a=rPol.nLineWink*nPi180;
/*N*/   double nLineSin=sin(a);
/*N*/   double nLineCos=cos(a);
/*N*/   rPol.nLineSin=nLineSin;
/*N*/   rPol.nLineCos=nLineCos;
/*N*/
/*N*/   rPol.nTextWink=rPol.nLineWink;
/*N*/   if (rRec.bTextRota90) rPol.nTextWink+=9000;
/*N*/
/*N*/   rPol.bAutoUpsideDown=FALSE;
/*N*/   if (rRec.bTextAutoAngle) {
/*N*/       long nTmpWink=NormAngle360(rPol.nTextWink-rRec.nTextAutoAngleView);
/*N*/       if (nTmpWink>=18000) {
/*N*/           rPol.nTextWink+=18000;
/*N*/           rPol.bAutoUpsideDown=TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (rRec.bTextUpsideDown) rPol.nTextWink+=18000;
/*N*/   rPol.nTextWink=NormAngle360(rPol.nTextWink);
/*N*/   rPol.nHlpWink=rPol.nLineWink+9000;
/*N*/   if (rRec.bBelowRefEdge) rPol.nHlpWink+=18000;
/*N*/   rPol.nHlpWink=NormAngle360(rPol.nHlpWink);
/*N*/   double nHlpSin=nLineCos;
/*N*/   double nHlpCos=-nLineSin;
/*N*/   if (rRec.bBelowRefEdge) {
/*N*/       nHlpSin=-nHlpSin;
/*N*/       nHlpCos=-nHlpCos;
/*N*/   }
/*N*/   rPol.nHlpSin=nHlpSin;
/*N*/   rPol.nHlpCos=nHlpCos;
/*N*/
/*N*/   long nLineDist=rRec.nLineDist;
/*N*/   long nOverhang=rRec.nHelplineOverhang;
/*N*/   long nHelplineDist=rRec.nHelplineDist;
/*N*/
/*N*/   long dx= Round(nLineDist*nHlpCos);
/*N*/   long dy=-Round(nLineDist*nHlpSin);
/*N*/   long dxh1a= Round((nHelplineDist-rRec.nHelpline1Len)*nHlpCos);
/*N*/   long dyh1a=-Round((nHelplineDist-rRec.nHelpline1Len)*nHlpSin);
/*N*/   long dxh1b= Round((nHelplineDist-rRec.nHelpline2Len)*nHlpCos);
/*N*/   long dyh1b=-Round((nHelplineDist-rRec.nHelpline2Len)*nHlpSin);
/*N*/   long dxh2= Round((nLineDist+nOverhang)*nHlpCos);
/*N*/   long dyh2=-Round((nLineDist+nOverhang)*nHlpSin);
/*N*/
/*N*/   // Masshilfslinie 1
/*N*/   rPol.aHelpline1.aP1=Point(aP1.X()+dxh1a,aP1.Y()+dyh1a);
/*N*/   rPol.aHelpline1.aP2=Point(aP1.X()+dxh2,aP1.Y()+dyh2);
/*N*/
/*N*/   // Masshilfslinie 2
/*N*/   rPol.aHelpline2.aP1=Point(aP2.X()+dxh1b,aP2.Y()+dyh1b);
/*N*/   rPol.aHelpline2.aP2=Point(aP2.X()+dxh2,aP2.Y()+dyh2);
/*N*/
/*N*/   // Masslinie(n)
/*N*/   Point aMainlinePt1(aP1.X()+dx,aP1.Y()+dy);
/*N*/   Point aMainlinePt2(aP2.X()+dx,aP2.Y()+dy);
/*N*/   if (!bPfeileAussen) {
/*N*/       rPol.aMainline1.aP1=aMainlinePt1;
/*N*/       rPol.aMainline1.aP2=aMainlinePt2;
/*N*/       rPol.aMainline2=rPol.aMainline1;
/*N*/       rPol.aMainline3=rPol.aMainline1;
/*N*/       rPol.nMainlineAnz=1;
/*N*/       if (bBrkLine) {
/*?*/           long nNeedSiz=!rRec.bTextRota90 ? rPol.aTextSize.Width() : rPol.aTextSize.Height();
/*?*/           long nHalfLen=(rPol.nLineLen-nNeedSiz-nArrow1Wdt/4-nArrow2Wdt/4) /2;
/*?*/           rPol.nMainlineAnz=2;
/*?*/           rPol.aMainline1.aP2=aMainlinePt1;
/*?*/           rPol.aMainline1.aP2.X()+=nHalfLen;
/*?*/           RotatePoint(rPol.aMainline1.aP2,rPol.aMainline1.aP1,nLineSin,nLineCos);
/*?*/           rPol.aMainline2.aP1=aMainlinePt2;
/*?*/           rPol.aMainline2.aP1.X()-=nHalfLen;
/*?*/           RotatePoint(rPol.aMainline2.aP1,rPol.aMainline2.aP2,nLineSin,nLineCos);
/*N*/       }
/*N*/   } else {
/*N*/       long nLen1=nShortLen; // Pfeilbreite als Linienlaenge ausserhalb des Pfeils
/*N*/       long nLen2=nShortLen;
/*N*/       long nTextWdt=rRec.bTextRota90 ? rPol.aTextSize.Height() : rPol.aTextSize.Width();
/*N*/       if (!bBrkLine) {
/*N*/           if (rPol.eUsedTextHPos==SDRMEASURE_TEXTLEFTOUTSIDE) nLen1=nArrow1Len+nTextWdt;
/*N*/           if (rPol.eUsedTextHPos==SDRMEASURE_TEXTRIGHTOUTSIDE) nLen2=nArrow2Len+nTextWdt;
/*N*/       }
/*N*/       rPol.aMainline1.aP1=aMainlinePt1;
/*N*/       rPol.aMainline1.aP2=aMainlinePt1; rPol.aMainline1.aP2.X()-=nLen1; RotatePoint(rPol.aMainline1.aP2,aMainlinePt1,nLineSin,nLineCos);
/*N*/       rPol.aMainline2.aP1=aMainlinePt2; rPol.aMainline2.aP1.X()+=nLen2; RotatePoint(rPol.aMainline2.aP1,aMainlinePt2,nLineSin,nLineCos);
/*N*/       rPol.aMainline2.aP2=aMainlinePt2;
/*N*/       rPol.aMainline3.aP1=aMainlinePt1;
/*N*/       rPol.aMainline3.aP2=aMainlinePt2;
/*N*/       rPol.nMainlineAnz=3;
/*N*/       if (bBrkLine && rPol.eUsedTextHPos==SDRMEASURE_TEXTINSIDE) rPol.nMainlineAnz=2;
/*N*/   }
/*N*/ }

/*N*/ void SdrMeasureObj::ImpCalcXPoly(const ImpMeasurePoly& rPol, XPolyPolygon& rXPP) const
/*N*/ {
/*N*/   rXPP.Clear();
/*N*/   XPolygon aXP(2);
/*N*/   aXP[0]=rPol.aMainline1.aP1;
/*N*/   aXP[1]=rPol.aMainline1.aP2;
/*N*/   rXPP.Insert(aXP);
/*N*/   if (rPol.nMainlineAnz>1) {
/*N*/       aXP[0]=rPol.aMainline2.aP1;
/*N*/       aXP[1]=rPol.aMainline2.aP2;
/*N*/       rXPP.Insert(aXP);
/*N*/   }
/*N*/   if (rPol.nMainlineAnz>2) {
/*N*/       aXP[0]=rPol.aMainline3.aP1;
/*N*/       aXP[1]=rPol.aMainline3.aP2;
/*N*/       rXPP.Insert(aXP);
/*N*/   }
/*N*/   aXP[0]=rPol.aHelpline1.aP1;
/*N*/   aXP[1]=rPol.aHelpline1.aP2;
/*N*/   rXPP.Insert(aXP);
/*N*/   aXP[0]=rPol.aHelpline2.aP1;
/*N*/   aXP[1]=rPol.aHelpline2.aP2;
/*N*/   rXPP.Insert(aXP);
/*N*/ }

//STRIP001 FASTBOOL SdrMeasureObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  // Hidden objects on masterpages, draw nothing
//STRIP001  if((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) && bNotVisibleAsMaster)
//STRIP001      return TRUE;
//STRIP001
//STRIP001  // prepare ItemSet of this object
//STRIP001  const SfxItemSet& rSet = GetItemSet();
//STRIP001
//STRIP001  // perepare ItemSet to avoid old XOut line drawing
//STRIP001  SfxItemSet aEmptySet(*rSet.GetPool());
//STRIP001  aEmptySet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001
//STRIP001  // prepare line geometry
//STRIP001  BOOL bIsLineDraft(0 != (rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTLINE));
//STRIP001  ::std::auto_ptr< SdrLineGeometry > pLineGeometry( ImpPrepareLineGeometry(rXOut, rSet, bIsLineDraft) );
//STRIP001
//STRIP001  // Shadows
//STRIP001  BOOL bShadOn = ((SdrShadowItem&)(rSet.Get(SDRATTR_SHADOW))).GetValue();
//STRIP001  if( bShadOn && pLineGeometry.get() )
//STRIP001  {
//STRIP001      // draw the line geometry
//STRIP001      ImpDrawShadowLineGeometry(rXOut, rSet, *pLineGeometry);
//STRIP001  }
//STRIP001
//STRIP001  // Before here the LineAttr were set: if(pLineAttr) rXOut.SetLineAttr(*pLineAttr);
//STRIP001  rXOut.SetLineAttr(aEmptySet);
//STRIP001
//STRIP001  // !!! aGeo muss noch fuer Textausgabe gesetzt werden !!!
//STRIP001  // aRect ebenso
//STRIP001  ImpMeasureRec aRec;
//STRIP001  ImpMeasurePoly aMPol;
//STRIP001  ImpTakeAttr(aRec);
//STRIP001  ImpCalcGeometrics(aRec,aMPol);
//STRIP001  FASTBOOL bMerk1=rXOut.IsLineStart();
//STRIP001  FASTBOOL bMerk2=rXOut.IsLineEnd();
//STRIP001  if (aMPol.nMainlineAnz>1) {
//STRIP001      // Je 1 Linienende temporaer abschalten
//STRIP001      rXOut.OverrideLineEnd(FALSE);
//STRIP001      rXOut.DrawLine(aMPol.aMainline1.aP1,aMPol.aMainline1.aP2);
//STRIP001      rXOut.OverrideLineEnd(bMerk2);
//STRIP001      rXOut.OverrideLineStart(FALSE);
//STRIP001      rXOut.DrawLine(aMPol.aMainline2.aP1,aMPol.aMainline2.aP2);
//STRIP001      rXOut.OverrideLineStart(bMerk1);
//STRIP001  } else {
//STRIP001      rXOut.DrawLine(aMPol.aMainline1.aP1,aMPol.aMainline1.aP2);
//STRIP001  }
//STRIP001  rXOut.OverrideLineStart(FALSE);
//STRIP001  rXOut.OverrideLineEnd(FALSE);
//STRIP001  if (aMPol.nMainlineAnz>2) {
//STRIP001      rXOut.DrawLine(aMPol.aMainline3.aP1,aMPol.aMainline3.aP2);
//STRIP001  }
//STRIP001  rXOut.DrawLine(aMPol.aHelpline1.aP1,aMPol.aHelpline1.aP2);
//STRIP001  rXOut.DrawLine(aMPol.aHelpline2.aP1,aMPol.aHelpline2.aP2);
//STRIP001
//STRIP001  // Own line drawing
//STRIP001  if( pLineGeometry.get() )
//STRIP001  {
//STRIP001      // draw the line geometry
//STRIP001      ImpDrawColorLineGeometry(rXOut, rSet, *pLineGeometry);
//STRIP001  }
//STRIP001
//STRIP001  FASTBOOL bOk=TRUE;
//STRIP001  if (bTextDirty) UndirtyText();
//STRIP001  bOk=SdrTextObj::Paint(rXOut,rInfoRec);
//STRIP001  if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {
//STRIP001      bOk=PaintGluePoints(rXOut,rInfoRec);
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
//STRIP001 }

/*N*/ FASTBOOL SdrMeasureObj::CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos,
/*N*/   FASTBOOL bEdit,
/*N*/   Color*& rpTxtColor, Color*& rpFldColor, XubString& rRet) const
/*N*/ {
/*N*/   const SvxFieldData* pField=rField.GetField();
/*N*/   SdrMeasureField* pMeasureField=PTR_CAST(SdrMeasureField,pField);
/*N*/   if (pMeasureField!=NULL) {
/*N*/       pMeasureField->TakeRepresentation(*this,rRet);
/*N*/       if (rpFldColor!=NULL) {
/*?*/           if (!bEdit)
/*?*/           {
/*?*/               delete rpFldColor;
/*?*/               rpFldColor=NULL;
/*?*/           }
/*N*/       }
/*N*/       return TRUE;
/*N*/   } else {
/*?*/       return SdrTextObj::CalcFieldValue(rField,nPara,nPos,bEdit,rpTxtColor,rpFldColor,rRet);
/*N*/   }
/*N*/ }

/*N*/ void SdrMeasureObj::UndirtyText() const
/*N*/ {
/*N*/   if (bTextDirty) {
/*N*/       SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*N*/       if (pOutlinerParaObject==NULL) {
/*N*/           rOutliner.QuickInsertField(SvxFieldItem(SdrMeasureField(SDRMEASUREFIELD_ROTA90BLANCS)),ESelection(0,0));
/*N*/           rOutliner.QuickInsertField(SvxFieldItem(SdrMeasureField(SDRMEASUREFIELD_VALUE)),ESelection(0,1));
/*N*/           rOutliner.QuickInsertField(SvxFieldItem(SdrMeasureField(SDRMEASUREFIELD_UNIT)),ESelection(0,2));
/*N*/           rOutliner.QuickInsertField(SvxFieldItem(SdrMeasureField(SDRMEASUREFIELD_ROTA90BLANCS)),ESelection(0,3));
/*N*/
/*N*/           if(GetStyleSheet())
/*N*/               rOutliner.SetStyleSheet(0, GetStyleSheet());
/*N*/
/*N*/           rOutliner.SetParaAttribs(0, GetItemSet());
/*N*/
/*N*/           // casting auf nonconst
/*N*/           ((SdrMeasureObj*)this)->pOutlinerParaObject=rOutliner.CreateParaObject();
/*N*/       } else {
/*N*/           rOutliner.SetText(*pOutlinerParaObject);
/*N*/       }
/*N*/       rOutliner.SetUpdateMode(TRUE);
/*N*/       rOutliner.UpdateFields();
/*N*/       Size aSiz(rOutliner.CalcTextSize());
/*N*/       rOutliner.Clear();
/*N*/       // 3x casting auf nonconst
/*N*/       ((SdrMeasureObj*)this)->aTextSize=aSiz;
/*N*/       ((SdrMeasureObj*)this)->bTextSizeDirty=FALSE;
/*N*/       ((SdrMeasureObj*)this)->bTextDirty=FALSE;
/*N*/   }
/*N*/ }

/*N*/ void SdrMeasureObj::TakeUnrotatedSnapRect(Rectangle& rRect) const
/*N*/ {
/*N*/   if (bTextDirty) UndirtyText();
/*N*/   ImpMeasureRec aRec;
/*N*/   ImpMeasurePoly aMPol;
/*N*/   ImpTakeAttr(aRec);
/*N*/   ImpCalcGeometrics(aRec,aMPol);
/*N*/
/*N*/   // TextSize ermitteln inkl. Textrahmenabstaende
/*N*/   Size aTextSize(aMPol.aTextSize);
/*N*/   if (aTextSize.Width()<1) aTextSize.Width()=1;
/*N*/   if (aTextSize.Height()<1) aTextSize.Height()=1;
/*N*/   aTextSize.Width()+=GetTextLeftDistance()+GetTextRightDistance();
/*N*/   aTextSize.Height()+=GetTextUpperDistance()+GetTextLowerDistance();
/*N*/
/*N*/   Point aPt1(aMPol.aMainline1.aP1);
/*N*/   long nLen=aMPol.nLineLen;
/*N*/   long nLWdt=aMPol.nLineWdt2;
/*N*/   long nArr1Len=aMPol.nArrow1Len;
/*N*/   long nArr2Len=aMPol.nArrow2Len;
/*N*/   if (aMPol.bBreakedLine) {
/*N*/       // Bei Unterbrochener Linie und Outside muss der Text nicht neben den
/*N*/       // Pfeil sondern neben die Linie an dem Pfeil plaziert werden
/*?*/       nArr1Len=aMPol.nShortLineLen+aMPol.nArrow1Wdt/4;
/*?*/       nArr2Len=aMPol.nShortLineLen+aMPol.nArrow2Wdt/4;
/*N*/   }
/*N*/
/*N*/   Point aTextPos;
/*N*/   FASTBOOL bRota90=aRec.bTextRota90;
/*N*/   FASTBOOL bUpsideDown=aRec.bTextUpsideDown!=aMPol.bAutoUpsideDown;
/*N*/   FASTBOOL bBelowRefEdge=aRec.bBelowRefEdge;
/*N*/   SdrMeasureTextHPos eMH=aMPol.eUsedTextHPos;
/*N*/   SdrMeasureTextVPos eMV=aMPol.eUsedTextVPos;
/*N*/   if (!bRota90) {
/*N*/       switch (eMH) {
/*N*/           case SDRMEASURE_TEXTLEFTOUTSIDE: aTextPos.X()=aPt1.X()-aTextSize.Width()-nArr1Len-nLWdt; break;
/*N*/           case SDRMEASURE_TEXTRIGHTOUTSIDE: aTextPos.X()=aPt1.X()+nLen+nArr2Len+nLWdt; break;
/*N*/           default: aTextPos.X()=aPt1.X(); aTextSize.Width()=nLen;
/*N*/       }
/*N*/       switch (eMV) {
/*N*/           case SDRMEASURETEXT_VERTICALCENTERED:
/*N*/           case SDRMEASURETEXT_BREAKEDLINE: aTextPos.Y()=aPt1.Y()-aTextSize.Height()/2; break;
/*N*/           case SDRMEASURE_BELOW: {
/*N*/               if (!bUpsideDown) aTextPos.Y()=aPt1.Y()+nLWdt;
/*N*/               else aTextPos.Y()=aPt1.Y()-aTextSize.Height()-nLWdt;
/*N*/           } break;
/*N*/           default: {
/*N*/               if (!bUpsideDown) aTextPos.Y()=aPt1.Y()-aTextSize.Height()-nLWdt;
/*N*/               else aTextPos.Y()=aPt1.Y()+nLWdt;
/*N*/           }
/*N*/       }
/*N*/       if (bUpsideDown) {
/*N*/           aTextPos.X()+=aTextSize.Width();
/*N*/           aTextPos.Y()+=aTextSize.Height();
/*N*/       }
/*N*/   } else { // also wenn bTextRota90==TRUE
/*N*/       switch (eMH) {
/*N*/           case SDRMEASURE_TEXTLEFTOUTSIDE: aTextPos.X()=aPt1.X()-aTextSize.Height()-nArr1Len; break;
/*N*/           case SDRMEASURE_TEXTRIGHTOUTSIDE: aTextPos.X()=aPt1.X()+nLen+nArr2Len; break;
/*N*/           default: aTextPos.X()=aPt1.X(); aTextSize.Height()=nLen;
/*N*/       }
/*N*/       switch (eMV) {
/*N*/           case SDRMEASURETEXT_VERTICALCENTERED:
/*N*/           case SDRMEASURETEXT_BREAKEDLINE: aTextPos.Y()=aPt1.Y()+aTextSize.Width()/2; break;
/*N*/           case SDRMEASURE_BELOW: {
/*N*/               if (!bBelowRefEdge) aTextPos.Y()=aPt1.Y()+aTextSize.Width()+nLWdt;
/*N*/               else aTextPos.Y()=aPt1.Y()-nLWdt;
/*N*/           } break;
/*N*/           default: {
/*N*/               if (!bBelowRefEdge) aTextPos.Y()=aPt1.Y()-nLWdt;
/*N*/               else aTextPos.Y()=aPt1.Y()+aTextSize.Width()+nLWdt;
/*N*/           }
/*N*/       }
/*N*/       if (bUpsideDown) {
/*N*/           aTextPos.X()+=aTextSize.Height();
/*N*/           aTextPos.Y()-=aTextSize.Width();
/*N*/       }
/*N*/   }
/*N*/   if (aMPol.nTextWink!=aGeo.nDrehWink) {
/*N*/       ((SdrMeasureObj*)this)->aGeo.nDrehWink=aMPol.nTextWink;
/*N*/       ((SdrMeasureObj*)this)->aGeo.RecalcSinCos();
/*N*/   }
/*N*/   RotatePoint(aTextPos,aPt1,aMPol.nLineSin,aMPol.nLineCos);
/*N*/   aTextSize.Width()++; aTextSize.Height()++; // wg. des komischen Verhaltens beim Rect-Ctor
/*N*/   rRect=Rectangle(aTextPos,aTextSize);
/*N*/   rRect.Justify();
/*N*/   ((SdrMeasureObj*)this)->aRect=rRect;
/*N*/
/*N*/   if (aMPol.nTextWink!=aGeo.nDrehWink) {
/*N*/       ((SdrMeasureObj*)this)->aGeo.nDrehWink=aMPol.nTextWink;
/*N*/       ((SdrMeasureObj*)this)->aGeo.RecalcSinCos();
/*N*/   }
/*N*/ }

//STRIP001 SdrObject* SdrMeasureObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  FASTBOOL bHit=FALSE;
//STRIP001  if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
//STRIP001  INT32 nMyTol=nTol;
//STRIP001  INT32 nWdt=ImpGetLineWdt()/2; // Halbe Strichstaerke
//STRIP001  if (nWdt>nMyTol) nMyTol=nWdt; // Bei dicker Linie keine Toleranz noetig
//STRIP001  Rectangle aR(rPnt,rPnt);
//STRIP001  aR.Left()  -=nMyTol;
//STRIP001  aR.Right() +=nMyTol;
//STRIP001  aR.Top()   -=nMyTol;
//STRIP001  aR.Bottom()+=nMyTol;
//STRIP001
//STRIP001  if (bTextDirty) UndirtyText();
//STRIP001  ImpMeasureRec aRec;
//STRIP001  ImpMeasurePoly aMPol;
//STRIP001  ImpTakeAttr(aRec);
//STRIP001  ImpCalcGeometrics(aRec,aMPol);
//STRIP001  bHit=IsRectTouchesLine(aMPol.aMainline1.aP1,aMPol.aMainline1.aP2,aR) ||
//STRIP001       IsRectTouchesLine(aMPol.aMainline2.aP1,aMPol.aMainline2.aP2,aR) ||
//STRIP001       IsRectTouchesLine(aMPol.aHelpline1.aP1,aMPol.aHelpline1.aP2,aR) ||
//STRIP001       IsRectTouchesLine(aMPol.aHelpline2.aP1,aMPol.aHelpline2.aP2,aR);
//STRIP001  // und nun noch ggf. den Textbereich checken
//STRIP001  bHit=bHit || SdrTextObj::CheckHit(rPnt,nTol,pVisiLayer)!=NULL;
//STRIP001  return bHit ? (SdrObject*)this : NULL;
//STRIP001 }

//STRIP001 void SdrMeasureObj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  SdrTextObj::operator=(rObj);
//STRIP001  aPt1=((SdrMeasureObj&)rObj).aPt1;
//STRIP001  aPt2=((SdrMeasureObj&)rObj).aPt2;
//STRIP001  bTextDirty=((SdrMeasureObj&)rObj).bTextDirty;
//STRIP001 }

//STRIP001 void SdrMeasureObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulMEASURE);
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

//STRIP001 void SdrMeasureObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralMEASURE);
//STRIP001 }

//STRIP001 void SdrMeasureObj::TakeXorPoly(XPolyPolygon& rXPP, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  ImpMeasureRec aRec;
//STRIP001  ImpMeasurePoly aMPol;
//STRIP001  ImpTakeAttr(aRec);
//STRIP001  ImpCalcGeometrics(aRec,aMPol);
//STRIP001  ImpCalcXPoly(aMPol,rXPP);
//STRIP001 }

//STRIP001 void SdrMeasureObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

//STRIP001 USHORT SdrMeasureObj::GetHdlCount() const
//STRIP001 {
//STRIP001  return 6;
//STRIP001 }

//STRIP001 SdrHdl* SdrMeasureObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  ImpMeasureRec aRec;
//STRIP001  ImpMeasurePoly aMPol;
//STRIP001  ImpTakeAttr(aRec);
//STRIP001  aRec.nHelplineDist=0;
//STRIP001  ImpCalcGeometrics(aRec,aMPol);
//STRIP001  Point aPt;
//STRIP001  SdrHdlKind eHdl=HDL_POLY;
//STRIP001  switch (nHdlNum) {
//STRIP001      case 0: aPt=aMPol.aHelpline1.aP1; break;
//STRIP001      case 1: aPt=aMPol.aHelpline2.aP1; break;
//STRIP001      case 2: aPt=aPt1;       break;
//STRIP001      case 3: aPt=aPt2;       break;
//STRIP001      case 4: aPt=aMPol.aHelpline1.aP2; break;
//STRIP001      case 5: aPt=aMPol.aHelpline2.aP2; break;
//STRIP001  } // switch
//STRIP001  SdrHdl* pHdl=new ImpMeasureHdl(aPt,HDL_USER);
//STRIP001  pHdl->SetObjHdlNum(nHdlNum);
//STRIP001  pHdl->SetDrehWink(aMPol.nLineWink);
//STRIP001  return pHdl;
//STRIP001 }

//STRIP001 void SdrMeasureObj::AddToHdlList(SdrHdlList& rHdlList) const
//STRIP001 {
//STRIP001  SdrTextObj::AddToHdlList(rHdlList);
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  if (pHdl!=NULL) {
//STRIP001      USHORT nHdlNum=pHdl->GetObjHdlNum();
//STRIP001      if (nHdlNum!=2 && nHdlNum!=3) {
//STRIP001          rDrag.SetEndDragChangesAttributes(TRUE);
//STRIP001      }
//STRIP001      ImpMeasureRec* pMR=new ImpMeasureRec; // #48544#
//STRIP001      ImpTakeAttr(*pMR);
//STRIP001      rDrag.SetUser(pMR);
//STRIP001  }
//STRIP001  return pHdl!=NULL;
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  ImpMeasureRec* pMR=(ImpMeasureRec*)rDrag.GetUser();
//STRIP001  if (pMR!=NULL) { // #48544#
//STRIP001      ImpTakeAttr(*pMR);
//STRIP001      ImpEvalDrag(*pMR,rDrag);
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  ImpMeasureRec* pMR=(ImpMeasureRec*)rDrag.GetUser(); // #48544#
//STRIP001  ImpMeasureRec aRec0;
//STRIP001  ImpTakeAttr(aRec0);
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  USHORT nHdlNum=pHdl->GetObjHdlNum();
//STRIP001  switch (nHdlNum) {
//STRIP001      case 2: aPt1=pMR->aPt1; SetTextDirty(); break;
//STRIP001      case 3: aPt2=pMR->aPt2; SetTextDirty(); break;
//STRIP001      default:
//STRIP001      {
//STRIP001          switch(nHdlNum)
//STRIP001          {
//STRIP001              case 0:
//STRIP001              case 1:
//STRIP001              {
//STRIP001                  if(pMR->nHelpline1Len!=aRec0.nHelpline1Len)
//STRIP001                  {
//STRIP001                      SetItem(SdrMeasureHelpline1LenItem(pMR->nHelpline1Len));
//STRIP001                  }
//STRIP001
//STRIP001                  if(pMR->nHelpline2Len!=aRec0.nHelpline2Len)
//STRIP001                  {
//STRIP001                      SetItem(SdrMeasureHelpline2LenItem(pMR->nHelpline2Len));
//STRIP001                  }
//STRIP001
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              case 4:
//STRIP001              case 5:
//STRIP001              {
//STRIP001                  if (pMR->nLineDist!=aRec0.nLineDist)
//STRIP001                  {
//STRIP001                      SetItem(SdrMeasureLineDistItem(pMR->nLineDist));
//STRIP001                  }
//STRIP001
//STRIP001                  if(pMR->bBelowRefEdge!=aRec0.bBelowRefEdge)
//STRIP001                  {
//STRIP001                      SetItem(SdrMeasureBelowRefEdgeItem(pMR->bBelowRefEdge));
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  } // switch
//STRIP001  SetRectsDirty();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pMR!=NULL) {
//STRIP001      delete pMR; // #48544#
//STRIP001      rDrag.SetUser(NULL);
//STRIP001  }
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrMeasureObj::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  ImpMeasureRec* pMR=(ImpMeasureRec*)rDrag.GetUser();
//STRIP001  if (pMR!=NULL) {
//STRIP001      delete pMR; // #48544#
//STRIP001      rDrag.SetUser(NULL);
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrMeasureObj::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrMeasureObj::ImpEvalDrag(ImpMeasureRec& rRec, const SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  long nLineWink=GetAngle(rRec.aPt2-rRec.aPt1);
//STRIP001  double a=nLineWink*nPi180;
//STRIP001  double nSin=sin(a);
//STRIP001  double nCos=cos(a);
//STRIP001
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  USHORT nHdlNum=pHdl->GetObjHdlNum();
//STRIP001  FASTBOOL bOrtho=rDrag.GetView()!=NULL && rDrag.GetView()->IsOrtho();
//STRIP001  FASTBOOL bBigOrtho=bOrtho && rDrag.GetView()->IsBigOrtho();
//STRIP001  FASTBOOL bBelow=rRec.bBelowRefEdge;
//STRIP001  Point aPt(rDrag.GetNow());
//STRIP001
//STRIP001  switch (nHdlNum) {
//STRIP001      case 0: {
//STRIP001          RotatePoint(aPt,aPt1,nSin,-nCos);
//STRIP001          rRec.nHelpline1Len=aPt1.Y()-aPt.Y();
//STRIP001          if (bBelow) rRec.nHelpline1Len=-rRec.nHelpline1Len;
//STRIP001          if (bOrtho) rRec.nHelpline2Len=rRec.nHelpline1Len;
//STRIP001      } break;
//STRIP001      case 1: {
//STRIP001          RotatePoint(aPt,aPt2,nSin,-nCos);
//STRIP001          rRec.nHelpline2Len=aPt2.Y()-aPt.Y();
//STRIP001          if (bBelow) rRec.nHelpline2Len=-rRec.nHelpline2Len;
//STRIP001          if (bOrtho) rRec.nHelpline1Len=rRec.nHelpline2Len;
//STRIP001      } break;
//STRIP001      case 2: case 3: {
//STRIP001          FASTBOOL bAnf=nHdlNum==2;
//STRIP001          Point& rMov=bAnf ? rRec.aPt1 : rRec.aPt2;
//STRIP001          Point aMov(rMov);
//STRIP001          Point aFix(bAnf ? rRec.aPt2 : rRec.aPt1);
//STRIP001          if (bOrtho) {
//STRIP001              long ndx0=aMov.X()-aFix.X();
//STRIP001              long ndy0=aMov.Y()-aFix.Y();
//STRIP001              FASTBOOL bHLin=ndy0==0;
//STRIP001              FASTBOOL bVLin=ndx0==0;
//STRIP001              if (!bHLin || !bVLin) { // sonst ist aPt1==aPt2
//STRIP001                  long ndx=aPt.X()-aFix.X();
//STRIP001                  long ndy=aPt.Y()-aFix.Y();
//STRIP001                  double nXFact=0; if (!bVLin) nXFact=(double)ndx/(double)ndx0;
//STRIP001                  double nYFact=0; if (!bHLin) nYFact=(double)ndy/(double)ndy0;
//STRIP001                  FASTBOOL bHor=bHLin || (!bVLin && (nXFact>nYFact) ==bBigOrtho);
//STRIP001                  FASTBOOL bVer=bVLin || (!bHLin && (nXFact<=nYFact)==bBigOrtho);
//STRIP001                  if (bHor) ndy=long(ndy0*nXFact);
//STRIP001                  if (bVer) ndx=long(ndx0*nYFact);
//STRIP001                  aPt=aFix;
//STRIP001                  aPt.X()+=ndx;
//STRIP001                  aPt.Y()+=ndy;
//STRIP001              } // else Ortho8
//STRIP001          }
//STRIP001          rMov=aPt;
//STRIP001      } break;
//STRIP001      case 4: case 5: {
//STRIP001          long nVal0=rRec.nLineDist;
//STRIP001          RotatePoint(aPt,(nHdlNum==4 ? aPt1 : aPt2),nSin,-nCos);
//STRIP001          rRec.nLineDist=aPt.Y()- (nHdlNum==4 ? aPt1.Y() : aPt2.Y());
//STRIP001          if (bBelow) rRec.nLineDist=-rRec.nLineDist;
//STRIP001          if (rRec.nLineDist<0) {
//STRIP001              rRec.nLineDist=-rRec.nLineDist;
//STRIP001              rRec.bBelowRefEdge=!bBelow;
//STRIP001          }
//STRIP001          rRec.nLineDist-=rRec.nHelplineOverhang;
//STRIP001          if (bOrtho) rRec.nLineDist=nVal0;
//STRIP001      } break;
//STRIP001  } // switch
//STRIP001 }

//STRIP001 void SdrMeasureObj::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  ImpMeasureRec* pMR=(ImpMeasureRec*)rDrag.GetUser(); // #48544#
//STRIP001  if (pMR!=NULL) {
//STRIP001      ImpMeasurePoly aMPol;
//STRIP001      ImpCalcGeometrics(*pMR,aMPol);
//STRIP001      ImpCalcXPoly(aMPol,rXPP);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rStat.SetOrtho8Possible();
//STRIP001  aPt1=rStat.GetStart();
//STRIP001  aPt2=rStat.GetNow();
//STRIP001  SetTextDirty();
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::MovCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  SdrView* pView=rStat.GetView();
//STRIP001  aPt1=rStat.GetStart();
//STRIP001  aPt2=rStat.GetNow();
//STRIP001  if (pView!=NULL && pView->IsCreate1stPointAsCenter()) {
//STRIP001      aPt1+=aPt1;
//STRIP001      aPt1-=rStat.Now();
//STRIP001  }
//STRIP001  SetTextDirty();
//STRIP001  bBoundRectDirty=TRUE;
//STRIP001  bSnapRectDirty=TRUE;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  SetTextDirty();
//STRIP001  SetRectsDirty();
//STRIP001  return (eCmd==SDRCREATE_FORCEEND || rStat.GetPointAnz()>=2);
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::BckCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrMeasureObj::BrkCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrMeasureObj::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  ImpMeasureRec aRec;
//STRIP001  ImpMeasurePoly aMPol;
//STRIP001  ImpTakeAttr(aRec);
//STRIP001  ImpCalcGeometrics(aRec,aMPol);
//STRIP001  ImpCalcXPoly(aMPol,rXPP);
//STRIP001 }

//STRIP001 Pointer SdrMeasureObj::GetCreatePointer() const
//STRIP001 {
//STRIP001  return Pointer(POINTER_CROSS);
//STRIP001 }

/*N*/ void SdrMeasureObj::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   SdrTextObj::NbcMove(rSiz);
/*N*/   MovePoint(aPt1,rSiz);
/*N*/   MovePoint(aPt2,rSiz);
/*N*/ }

/*N*/ void SdrMeasureObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrTextObj::NbcResize(rRef,xFact,yFact);
/*N*/   ResizePoint(aPt1,rRef,xFact,yFact);
/*N*/   ResizePoint(aPt2,rRef,xFact,yFact);
/*N*/   SetTextDirty();
/*N*/ }

//STRIP001 void SdrMeasureObj::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
//STRIP001 {
//STRIP001  SdrTextObj::NbcRotate(rRef,nWink,sn,cs);
//STRIP001  long nLen0=GetLen(aPt2-aPt1);
//STRIP001  RotatePoint(aPt1,rRef,sn,cs);
//STRIP001  RotatePoint(aPt2,rRef,sn,cs);
//STRIP001  long nLen1=GetLen(aPt2-aPt1);
//STRIP001  if (nLen1!=nLen0) { // Aha, Rundungsfehler
//STRIP001      long dx=aPt2.X()-aPt1.X();
//STRIP001      long dy=aPt2.Y()-aPt1.Y();
//STRIP001      dx=BigMulDiv(dx,nLen0,nLen1);
//STRIP001      dy=BigMulDiv(dy,nLen0,nLen1);
//STRIP001      if (rRef==aPt2) {
//STRIP001          aPt1.X()=aPt2.X()-dx;
//STRIP001          aPt1.Y()=aPt2.Y()-dy;
//STRIP001      } else {
//STRIP001          aPt2.X()=aPt1.X()+dx;
//STRIP001          aPt2.Y()=aPt1.Y()+dy;
//STRIP001      }
//STRIP001  }
//STRIP001  SetRectsDirty();
//STRIP001 }

//STRIP001 void SdrMeasureObj::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  SdrTextObj::NbcMirror(rRef1,rRef2);
//STRIP001  MirrorPoint(aPt1,rRef1,rRef2);
//STRIP001  MirrorPoint(aPt2,rRef1,rRef2);
//STRIP001  SetRectsDirty();
//STRIP001 }

//STRIP001 void SdrMeasureObj::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
//STRIP001 {
//STRIP001  SdrTextObj::NbcShear(rRef,nWink,tn,bVShear);
//STRIP001  ShearPoint(aPt1,rRef,tn,bVShear);
//STRIP001  ShearPoint(aPt2,rRef,tn,bVShear);
//STRIP001  SetRectsDirty();
//STRIP001  SetTextDirty();
//STRIP001 }

//STRIP001 const Rectangle& SdrMeasureObj::GetLogicRect() const
//STRIP001 {
//STRIP001  return SdrTextObj::GetLogicRect();
//STRIP001 }

//STRIP001 void SdrMeasureObj::NbcSetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  SdrTextObj::NbcSetLogicRect(rRect);
//STRIP001 }

/*N*/ long SdrMeasureObj::GetRotateAngle() const
/*N*/ {
/*N*/   return GetAngle(aPt2-aPt1);
/*N*/ }

/*N*/ void SdrMeasureObj::RecalcBoundRect()
/*N*/ {
/*N*/   if (bTextDirty) UndirtyText();
/*N*/   ImpMeasureRec aRec;
/*N*/   ImpMeasurePoly aMPol;
/*N*/   ImpTakeAttr(aRec);
/*N*/   ImpCalcGeometrics(aRec,aMPol);
/*N*/   XPolyPolygon aXPP;
/*N*/   ImpCalcXPoly(aMPol,aXPP);
/*N*/   aOutRect=aXPP.GetBoundRect();
/*N*/
/*N*/   // Strichstaerke und Linienenden drauftun
/*N*/   long nLineWdt=ImpGetLineWdt();
/*N*/   long nLEndWdt=ImpGetLineEndAdd();
/*N*/   if (nLEndWdt>nLineWdt) nLineWdt=nLEndWdt;
/*N*/   if (nLineWdt!=0) {
/*N*/       aOutRect.Left  ()-=nLineWdt;
/*N*/       aOutRect.Top   ()-=nLineWdt;
/*N*/       aOutRect.Right ()+=nLineWdt;
/*N*/       aOutRect.Bottom()+=nLineWdt;
/*N*/   }
/*N*/
/*N*/ // AW 10082000 taken out, seems not to be necessary...
/*N*/ //    Rectangle aTempRect;
/*N*/ //    TakeUnrotatedSnapRect(aTempRect); // Damit aRect gesetzt ist
/*N*/   ImpAddShadowToBoundRect();
/*N*/   ImpAddTextToBoundRect();
/*N*/ }

/*N*/ void SdrMeasureObj::RecalcSnapRect()
/*N*/ {
/*N*/   // !!!!! nur zu Testzwecken !!!!!
/*N*/   //maSnapRect=Rectangle(aPt1,aPt2);
/*N*/   //maSnapRect.Justify();
/*N*/
/*N*/   // #94520# Added correct implementation here.
/*N*/   ImpMeasureRec aRec;
/*N*/   ImpMeasurePoly aMPol;
/*N*/   XPolyPolygon aXPP;
/*N*/
/*N*/   ImpTakeAttr(aRec);
/*N*/   ImpCalcGeometrics(aRec, aMPol);
/*N*/   ImpCalcXPoly(aMPol, aXPP);
/*N*/   maSnapRect = aXPP.GetBoundRect();
/*N*/ }

//STRIP001 USHORT SdrMeasureObj::GetSnapPointCount() const
//STRIP001 {
//STRIP001  return 2;
//STRIP001 }

//STRIP001 Point SdrMeasureObj::GetSnapPoint(USHORT i) const
//STRIP001 {
//STRIP001  if (i==0) return aPt1;
//STRIP001  else return aPt2;
//STRIP001 }

//STRIP001 FASTBOOL SdrMeasureObj::IsPolyObj() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 USHORT SdrMeasureObj::GetPointCount() const
//STRIP001 {
//STRIP001  return 2;
//STRIP001 }

/*N*/ const Point& SdrMeasureObj::GetPoint(USHORT i) const
/*N*/ {
/*N*/    return i==0 ? aPt1 : aPt2;
/*N*/ }

/*N*/ void SdrMeasureObj::NbcSetPoint(const Point& rPnt, USHORT i)
/*N*/ {
/*N*/   if (i==0) aPt1=rPnt;
/*N*/   if (i==1) aPt2=rPnt;
/*N*/   SetRectsDirty();
/*N*/   SetTextDirty();
/*N*/ }

//STRIP001 SdrObjGeoData* SdrMeasureObj::NewGeoData() const
//STRIP001 {
//STRIP001  return new SdrMeasureObjGeoData;
//STRIP001 }

//STRIP001 void SdrMeasureObj::SaveGeoData(SdrObjGeoData& rGeo) const
//STRIP001 {
//STRIP001  SdrTextObj::SaveGeoData(rGeo);
//STRIP001  SdrMeasureObjGeoData& rMGeo=(SdrMeasureObjGeoData&)rGeo;
//STRIP001  rMGeo.aPt1=aPt1;
//STRIP001  rMGeo.aPt2=aPt2;
//STRIP001 }

//STRIP001 void SdrMeasureObj::RestGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  SdrTextObj::RestGeoData(rGeo);
//STRIP001  SdrMeasureObjGeoData& rMGeo=(SdrMeasureObjGeoData&)rGeo;
//STRIP001  aPt1=rMGeo.aPt1;
//STRIP001  aPt2=rMGeo.aPt2;
//STRIP001  SetTextDirty();
//STRIP001 }

//STRIP001 ::std::auto_ptr< SdrLineGeometry > SdrMeasureObj::CreateLinePoly( OutputDevice& rOut,
//STRIP001                                                                   BOOL           bForceOnePixel,
//STRIP001                                                                   BOOL           bForceTwoPixel,
//STRIP001                                                                   BOOL           bIsLineDraft    ) const
//STRIP001 {
//STRIP001     PolyPolygon3D aPolyPoly3D;
//STRIP001     PolyPolygon3D aLinePoly3D;
//STRIP001
//STRIP001  // get XOR Poly as base
//STRIP001  XPolyPolygon aTmpPolyPolygon;
//STRIP001  TakeXorPoly(aTmpPolyPolygon, TRUE);
//STRIP001
//STRIP001  // get ImpLineStyleParameterPack
//STRIP001  ImpLineStyleParameterPack aLineAttr(GetItemSet(), bForceOnePixel || bForceTwoPixel || bIsLineDraft, &rOut);
//STRIP001  ImpLineGeometryCreator aLineCreator(aLineAttr, aPolyPoly3D, aLinePoly3D, bIsLineDraft);
//STRIP001  UINT16 nCount(aTmpPolyPolygon.Count());
//STRIP001  Polygon3D aPoly3D;
//STRIP001  UINT16 nLoopStart(0);
//STRIP001
//STRIP001  if(nCount == 3)
//STRIP001  {
//STRIP001      // three lines, first one is the middle one
//STRIP001      aPoly3D = Polygon3D(aTmpPolyPolygon[0]);
//STRIP001      aLineCreator.AddPolygon3D(aPoly3D);
//STRIP001
//STRIP001      aLineAttr.ForceNoArrowsLeft(TRUE);
//STRIP001      aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001      nLoopStart = 1;
//STRIP001  }
//STRIP001  else if(nCount == 4)
//STRIP001  {
//STRIP001      // four lines, middle line with gap, so there are two lines used
//STRIP001      // which have one arrow each
//STRIP001      aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001
//STRIP001      aPoly3D = Polygon3D(aTmpPolyPolygon[0]);
//STRIP001      aLineCreator.AddPolygon3D(aPoly3D);
//STRIP001
//STRIP001      aLineAttr.ForceNoArrowsRight(FALSE);
//STRIP001      aLineAttr.ForceNoArrowsLeft(TRUE);
//STRIP001
//STRIP001      aPoly3D = Polygon3D(aTmpPolyPolygon[1]);
//STRIP001      aLineCreator.AddPolygon3D(aPoly3D);
//STRIP001
//STRIP001      aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001      nLoopStart = 2;
//STRIP001  }
//STRIP001  else if(nCount == 5)
//STRIP001  {
//STRIP001      // five lines, first two are the outer ones
//STRIP001      aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001
//STRIP001      aPoly3D = Polygon3D(aTmpPolyPolygon[0]);
//STRIP001      aLineCreator.AddPolygon3D(aPoly3D);
//STRIP001
//STRIP001      aLineAttr.ForceNoArrowsRight(FALSE);
//STRIP001      aLineAttr.ForceNoArrowsLeft(TRUE);
//STRIP001
//STRIP001      aPoly3D = Polygon3D(aTmpPolyPolygon[1]);
//STRIP001      aLineCreator.AddPolygon3D(aPoly3D);
//STRIP001
//STRIP001      aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001      nLoopStart = 2;
//STRIP001  }
//STRIP001
//STRIP001  for(;nLoopStart<nCount;nLoopStart++)
//STRIP001  {
//STRIP001      aPoly3D = Polygon3D(aTmpPolyPolygon[nLoopStart]);
//STRIP001      aLineCreator.AddPolygon3D(aPoly3D);
//STRIP001  }
//STRIP001
//STRIP001     if(aPolyPoly3D.Count() || aLinePoly3D.Count())
//STRIP001         return ::std::auto_ptr< SdrLineGeometry > (new SdrLineGeometry(aPolyPoly3D, aLinePoly3D,
//STRIP001                                                                        aLineAttr, bForceOnePixel, bForceTwoPixel));
//STRIP001     else
//STRIP001         return ::std::auto_ptr< SdrLineGeometry > (NULL);
//STRIP001 }

//STRIP001 SdrObject* SdrMeasureObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  // get XOR Poly as base
//STRIP001  XPolyPolygon aTmpPolyPolygon;
//STRIP001  TakeXorPoly(aTmpPolyPolygon, TRUE);
//STRIP001
//STRIP001  // get local ItemSet
//STRIP001  SfxItemSet aSet(GetItemSet());
//STRIP001
//STRIP001  // prepare group
//STRIP001  SdrObjGroup* pGroup = new SdrObjGroup;
//STRIP001  pGroup->SetModel(GetModel());
//STRIP001
//STRIP001  // prepare parameters
//STRIP001  XPolyPolygon aNewPoly;
//STRIP001  SdrPathObj* pPath;
//STRIP001  UINT16 nCount(aTmpPolyPolygon.Count());
//STRIP001  UINT16 nLoopStart(0);
//STRIP001
//STRIP001  if(nCount == 3)
//STRIP001  {
//STRIP001      // three lines, first one is the middle one
//STRIP001      aNewPoly.Clear();
//STRIP001      aNewPoly.Insert(aTmpPolyPolygon[0]);
//STRIP001      pPath = new SdrPathObj(OBJ_PATHLINE, aNewPoly);
//STRIP001      pPath->SetModel(GetModel());
//STRIP001
//STRIP001      pPath->SetItemSet(aSet);
//STRIP001
//STRIP001      pGroup->GetSubList()->NbcInsertObject(pPath);
//STRIP001
//STRIP001      aSet.Put(XLineStartWidthItem(0L));
//STRIP001      aSet.Put(XLineEndWidthItem(0L));
//STRIP001      nLoopStart = 1;
//STRIP001  }
//STRIP001  else if(nCount == 4)
//STRIP001  {
//STRIP001      // four lines, middle line with gap, so there are two lines used
//STRIP001      // which have one arrow each
//STRIP001      INT32 nStartWidth = ((const XLineStartWidthItem&)(aSet.Get(XATTR_LINESTARTWIDTH))).GetValue();
//STRIP001      INT32 nEndWidth = ((const XLineEndWidthItem&)(aSet.Get(XATTR_LINEENDWIDTH))).GetValue();
//STRIP001
//STRIP001      aSet.Put(XLineEndWidthItem(0L));
//STRIP001
//STRIP001      aNewPoly.Clear();
//STRIP001      aNewPoly.Insert(aTmpPolyPolygon[0]);
//STRIP001      pPath = new SdrPathObj(OBJ_PATHLINE, aNewPoly);
//STRIP001      pPath->SetModel(GetModel());
//STRIP001
//STRIP001      pPath->SetItemSet(aSet);
//STRIP001
//STRIP001      pGroup->GetSubList()->NbcInsertObject(pPath);
//STRIP001
//STRIP001      aSet.Put(XLineEndWidthItem(nEndWidth));
//STRIP001      aSet.Put(XLineStartWidthItem(0L));
//STRIP001
//STRIP001      aNewPoly.Clear();
//STRIP001      aNewPoly.Insert(aTmpPolyPolygon[1]);
//STRIP001      pPath = new SdrPathObj(OBJ_PATHLINE, aNewPoly);
//STRIP001      pPath->SetModel(GetModel());
//STRIP001
//STRIP001      pPath->SetItemSet(aSet);
//STRIP001
//STRIP001      pGroup->GetSubList()->NbcInsertObject(pPath);
//STRIP001
//STRIP001      aSet.Put(XLineEndWidthItem(0L));
//STRIP001      nLoopStart = 2;
//STRIP001  }
//STRIP001  else if(nCount == 5)
//STRIP001  {
//STRIP001      // five lines, first two are the outer ones
//STRIP001      INT32 nStartWidth = ((const XLineStartWidthItem&)(aSet.Get(XATTR_LINESTARTWIDTH))).GetValue();
//STRIP001      INT32 nEndWidth = ((const XLineEndWidthItem&)(aSet.Get(XATTR_LINEENDWIDTH))).GetValue();
//STRIP001
//STRIP001      aSet.Put(XLineEndWidthItem(0L));
//STRIP001
//STRIP001      aNewPoly.Clear();
//STRIP001      aNewPoly.Insert(aTmpPolyPolygon[0]);
//STRIP001      pPath = new SdrPathObj(OBJ_PATHLINE, aNewPoly);
//STRIP001      pPath->SetModel(GetModel());
//STRIP001
//STRIP001      pPath->SetItemSet(aSet);
//STRIP001
//STRIP001      pGroup->GetSubList()->NbcInsertObject(pPath);
//STRIP001
//STRIP001      aSet.Put(XLineEndWidthItem(nEndWidth));
//STRIP001      aSet.Put(XLineStartWidthItem(0L));
//STRIP001
//STRIP001      aNewPoly.Clear();
//STRIP001      aNewPoly.Insert(aTmpPolyPolygon[1]);
//STRIP001      pPath = new SdrPathObj(OBJ_PATHLINE, aNewPoly);
//STRIP001      pPath->SetModel(GetModel());
//STRIP001
//STRIP001      pPath->SetItemSet(aSet);
//STRIP001
//STRIP001      pGroup->GetSubList()->NbcInsertObject(pPath);
//STRIP001
//STRIP001      aSet.Put(XLineEndWidthItem(0L));
//STRIP001      nLoopStart = 2;
//STRIP001  }
//STRIP001
//STRIP001  for(;nLoopStart<nCount;nLoopStart++)
//STRIP001  {
//STRIP001      aNewPoly.Clear();
//STRIP001      aNewPoly.Insert(aTmpPolyPolygon[nLoopStart]);
//STRIP001      pPath = new SdrPathObj(OBJ_PATHLINE, aNewPoly);
//STRIP001      pPath->SetModel(GetModel());
//STRIP001
//STRIP001      pPath->SetItemSet(aSet);
//STRIP001
//STRIP001      pGroup->GetSubList()->NbcInsertObject(pPath);
//STRIP001  }
//STRIP001
//STRIP001  return ImpConvertAddText(pGroup, bBezier);
//STRIP001 }

/*N*/ FASTBOOL SdrMeasureObj::BegTextEdit(SdrOutliner& rOutl)
/*N*/ {DBG_BF_ASSERT(0, "STRIP");return FALSE; //STRIP001
//STRIP001  UndirtyText();
//STRIP001  return SdrTextObj::BegTextEdit(rOutl);
/*N*/ }

/*N*/ void SdrMeasureObj::EndTextEdit(SdrOutliner& rOutl)
/*N*/ {
/*N*/   SdrTextObj::EndTextEdit(rOutl);
/*N*/ }

/*N*/ const Size& SdrMeasureObj::GetTextSize() const
/*N*/ {
/*N*/   if (bTextDirty) UndirtyText();
/*N*/   return SdrTextObj::GetTextSize();
/*N*/ }

/*N*/ OutlinerParaObject* SdrMeasureObj::GetOutlinerParaObject() const
/*N*/ {
/*N*/   if (bTextDirty) UndirtyText();
/*N*/   return pOutlinerParaObject;
/*N*/ }

/*N*/ void SdrMeasureObj::NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject)
/*N*/ {
/*N*/   SdrTextObj::NbcSetOutlinerParaObject(pTextObject);
/*N*/   if (pOutlinerParaObject==NULL) SetTextDirty(); // Text neu berechnen!
/*N*/ }

/*N*/ void SdrMeasureObj::TakeTextRect( SdrOutliner& rOutliner, Rectangle& rTextRect, FASTBOOL bNoEditText,
/*N*/   Rectangle* pAnchorRect, BOOL bLineWidth ) const
/*N*/ {
/*N*/   if (bTextDirty) UndirtyText();
/*N*/   SdrTextObj::TakeTextRect( rOutliner, rTextRect, bNoEditText, pAnchorRect, bLineWidth );
/*N*/ }

/*N*/ void SdrMeasureObj::TakeTextAnchorRect(Rectangle& rAnchorRect) const
/*N*/ {
/*N*/   if (bTextDirty) UndirtyText();
/*N*/   SdrTextObj::TakeTextAnchorRect(rAnchorRect);
/*N*/ }

//STRIP001 void SdrMeasureObj::TakeTextEditArea(Size* pPaperMin, Size* pPaperMax, Rectangle* pViewInit, Rectangle* pViewMin) const
//STRIP001 {
//STRIP001  if (bTextDirty) UndirtyText();
//STRIP001  SdrTextObj::TakeTextEditArea(pPaperMin,pPaperMax,pViewInit,pViewMin);
//STRIP001 }

//STRIP001 SdrObject* SdrMeasureObj::CheckTextEditHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  if (bTextDirty) UndirtyText();
//STRIP001  return SdrTextObj::CheckTextEditHit(rPnt,nTol,pVisiLayer);
//STRIP001 }

//STRIP001 USHORT SdrMeasureObj::GetOutlinerViewAnchorMode() const
//STRIP001 {
//STRIP001  if (bTextDirty) UndirtyText();
//STRIP001  ImpMeasureRec aRec;
//STRIP001  ImpMeasurePoly aMPol;
//STRIP001  ImpTakeAttr(aRec);
//STRIP001  ImpCalcGeometrics(aRec,aMPol);
//STRIP001
//STRIP001  SdrTextHorzAdjust eTH=GetTextHorizontalAdjust();
//STRIP001  SdrTextVertAdjust eTV=GetTextVerticalAdjust();
//STRIP001  SdrMeasureTextHPos eMH=aMPol.eUsedTextHPos;
//STRIP001  SdrMeasureTextVPos eMV=aMPol.eUsedTextVPos;
//STRIP001  FASTBOOL bTextRota90=aRec.bTextRota90;
//STRIP001  FASTBOOL bTextUpsideDown=aRec.bTextUpsideDown;
//STRIP001  FASTBOOL bBelowRefEdge=aRec.bBelowRefEdge;
//STRIP001
//STRIP001  // bTextUpsideDown muss hier noch ausgewertet werden!!!!
//STRIP001  if (!bTextRota90) {
//STRIP001      if (eMH==SDRMEASURE_TEXTLEFTOUTSIDE) eTH=SDRTEXTHORZADJUST_RIGHT;
//STRIP001      if (eMH==SDRMEASURE_TEXTRIGHTOUTSIDE) eTH=SDRTEXTHORZADJUST_LEFT;
//STRIP001      // bei eMH==SDRMEASURE_TEXTINSIDE kann horizontal geankert werden.
//STRIP001      if (eMV==SDRMEASURE_ABOVE) eTV=SDRTEXTVERTADJUST_BOTTOM;
//STRIP001      if (eMV==SDRMEASURE_BELOW) eTV=SDRTEXTVERTADJUST_TOP;
//STRIP001      if (eMV==SDRMEASURETEXT_BREAKEDLINE || eMV==SDRMEASURETEXT_VERTICALCENTERED) eTV=SDRTEXTVERTADJUST_CENTER;
//STRIP001  } else {
//STRIP001      if (eMH==SDRMEASURE_TEXTLEFTOUTSIDE) eTV=SDRTEXTVERTADJUST_BOTTOM;
//STRIP001      if (eMH==SDRMEASURE_TEXTRIGHTOUTSIDE) eTV=SDRTEXTVERTADJUST_TOP;
//STRIP001      // bei eMH==SDRMEASURE_TEXTINSIDE kann vertikal geankert werden.
//STRIP001      if (!bBelowRefEdge) {
//STRIP001          if (eMV==SDRMEASURE_ABOVE) eTH=SDRTEXTHORZADJUST_LEFT;
//STRIP001          if (eMV==SDRMEASURE_BELOW) eTH=SDRTEXTHORZADJUST_RIGHT;
//STRIP001      } else {
//STRIP001          if (eMV==SDRMEASURE_ABOVE) eTH=SDRTEXTHORZADJUST_RIGHT;
//STRIP001          if (eMV==SDRMEASURE_BELOW) eTH=SDRTEXTHORZADJUST_LEFT;
//STRIP001      }
//STRIP001      if (eMV==SDRMEASURETEXT_BREAKEDLINE || eMV==SDRMEASURETEXT_VERTICALCENTERED) eTH=SDRTEXTHORZADJUST_CENTER;
//STRIP001  }
//STRIP001
//STRIP001  EVAnchorMode eRet=ANCHOR_BOTTOM_HCENTER;
//STRIP001  if (eTH==SDRTEXTHORZADJUST_LEFT) {
//STRIP001      if (eTV==SDRTEXTVERTADJUST_TOP) eRet=ANCHOR_TOP_LEFT;
//STRIP001      else if (eTV==SDRTEXTVERTADJUST_BOTTOM) eRet=ANCHOR_BOTTOM_LEFT;
//STRIP001      else eRet=ANCHOR_VCENTER_LEFT;
//STRIP001  } else if (eTH==SDRTEXTHORZADJUST_RIGHT) {
//STRIP001      if (eTV==SDRTEXTVERTADJUST_TOP) eRet=ANCHOR_TOP_RIGHT;
//STRIP001      else if (eTV==SDRTEXTVERTADJUST_BOTTOM) eRet=ANCHOR_BOTTOM_RIGHT;
//STRIP001      else eRet=ANCHOR_VCENTER_RIGHT;
//STRIP001  } else {
//STRIP001      if (eTV==SDRTEXTVERTADJUST_TOP) eRet=ANCHOR_TOP_HCENTER;
//STRIP001      else if (eTV==SDRTEXTVERTADJUST_BOTTOM) eRet=ANCHOR_BOTTOM_HCENTER;
//STRIP001      else eRet=ANCHOR_VCENTER_HCENTER;
//STRIP001  }
//STRIP001  return (USHORT)eRet;
//STRIP001 }

/*N*/ void __EXPORT SdrMeasureObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   if (HAS_BASE(SfxStyleSheet,&rBC)) {
/*?*/       SfxSimpleHint* pSimple=PTR_CAST(SfxSimpleHint,&rHint);
/*?*/       ULONG nId=pSimple==NULL ? 0 : pSimple->GetId();
/*?*/
/*?*/       if(nId == SFX_HINT_DATACHANGED)
/*?*/       {
/*?*/           // Alten Bereich invalidieren
/*?*/           SendRepaintBroadcast();
/*?*/
/*?*/           // Text hart aufVeraenderung setzen
/*?*/           SetTextDirty();
/*?*/       }
/*N*/   }
/*N*/   SdrTextObj::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/ }

/*N*/ void SdrMeasureObj::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   SetTextDirty();
/*N*/   SdrTextObj::NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ SfxItemSet* SdrMeasureObj::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // include ALL items, 2D and 3D
/*N*/   return new SfxItemSet(rPool,
/*N*/       // ranges from SdrAttrObj
/*N*/       SDRATTR_START, SDRATTRSET_SHADOW,
/*N*/       SDRATTRSET_OUTLINER, SDRATTRSET_MISC,
/*N*/       SDRATTR_TEXTDIRECTION, SDRATTR_TEXTDIRECTION,
/*N*/
/*N*/       // measure attributes
/*N*/       SDRATTR_MEASURE_FIRST, SDRATTRSET_MEASURE,
/*N*/
/*N*/       // outliner and end
/*N*/       EE_ITEMS_START, EE_ITEMS_END,
/*N*/       0, 0);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access
/*N*/ void SdrMeasureObj::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/   // call parent
/*N*/   SdrTextObj::ItemSetChanged(rSet);
/*N*/
/*N*/   // local changes
/*N*/   SetTextDirty();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrMeasureObj::PreSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrTextObj::PreSave();
/*N*/
/*N*/   // prepare SetItems for storage
/*N*/   const SfxItemSet& rSet = GetUnmergedItemSet();
/*N*/   const SfxItemSet* pParent = GetStyleSheet() ? &GetStyleSheet()->GetItemSet() : 0L;
/*N*/   SdrMeasureSetItem aMeasAttr(rSet.GetPool());
/*N*/   aMeasAttr.GetItemSet().Put(rSet);
/*N*/   aMeasAttr.GetItemSet().SetParent(pParent);
/*N*/   mpObjectItemSet->Put(aMeasAttr);
/*N*/ }

/*N*/ void SdrMeasureObj::PostSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrTextObj::PostSave();
/*N*/
/*N*/   // remove SetItems from local itemset
/*N*/   mpObjectItemSet->ClearItem(SDRATTRSET_MEASURE);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMeasureObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   UndirtyText();
/*N*/
/*N*/   SdrTextObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrMeasureObj");
/*N*/ #endif
/*N*/
/*N*/   rOut << aPt1;
/*N*/   rOut << aPt2;
/*N*/   rOut << BOOL(FALSE); // bTextOverwritten wg. Kompatibilitaet. Gibt's nicht mehr.
/*N*/
/*N*/   SfxItemPool* pPool=GetItemPool();
/*N*/
/*N*/   if(pPool)
/*N*/   {
/*N*/       const SfxItemSet& rSet = GetUnmergedItemSet();
/*N*/
/*N*/       pPool->StoreSurrogate(rOut, &rSet.Get(SDRATTRSET_MEASURE));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rOut << sal_uInt16(SFX_ITEMS_NULL);
/*N*/   }
/*N*/ }

/*N*/ void SdrMeasureObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrTextObj::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrMeasureObj");
/*N*/ #endif
/*N*/   rIn>>aPt1;
/*N*/   rIn>>aPt2;
/*N*/   BOOL bTextOverwrittenTmp;
/*N*/   rIn>>bTextOverwrittenTmp;
/*N*/   SfxItemPool* pPool=GetItemPool();
/*N*/
/*N*/   if(pPool)
/*N*/   {
/*N*/       sal_uInt16 nSetID = SDRATTRSET_MEASURE;
/*N*/       const SdrMeasureSetItem* pMeasAttr = (const SdrMeasureSetItem*)pPool->LoadSurrogate(rIn, nSetID, 0);
/*N*/       if(pMeasAttr)
/*N*/           SetItemSet(pMeasAttr->GetItemSet());
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       sal_uInt16 nSuroDum;
/*N*/       rIn >> nSuroDum;
/*N*/   }
/*N*/ }

}
