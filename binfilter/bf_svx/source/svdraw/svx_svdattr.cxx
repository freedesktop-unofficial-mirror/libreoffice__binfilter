/*************************************************************************
 *
 *  $RCSfile: svx_svdattr.cxx,v $
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

#define ITEMID_GRF_CROP 0

#ifndef _COM_SUN_STAR_DRAWING_TEXTFITTOSIZETYPE_HPP_
#include <com/sun/star/drawing/TextFitToSizeType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTHORIZONTALADJUST_HPP_
#include <com/sun/star/drawing/TextHorizontalAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTVERTICALADJUST_HPP_
#include <com/sun/star/drawing/TextVerticalAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONKIND_HPP_
#include <com/sun/star/drawing/TextAnimationKind.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONDIRECTION_HPP_
#include <com/sun/star/drawing/TextAnimationDirection.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CONNECTORTYPE_HPP_
#include <com/sun/star/drawing/ConnectorType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASUREKIND_HPP_
#include <com/sun/star/drawing/MeasureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTHORZPOS_HPP_
#include <com/sun/star/drawing/MeasureTextHorzPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTVERTPOS_HPP_
#include <com/sun/star/drawing/MeasureTextVertPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CIRCLEKIND_HPP_
#include <com/sun/star/drawing/CircleKind.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#include <unotools/intlwrapper.hxx>
#include <comphelper/processfactory.hxx>

#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif

#include "svdattr.hxx"
#include "svdattrx.hxx"
#include "svdpool.hxx"

#ifndef _SOLAR_HRC
#include <svtools/solar.hrc>
#endif

#ifndef _SVX_XMLCNITM_HXX
#include "xmlcnitm.hxx"
#endif

#include "svxids.hrc"
#include "xtable.hxx"    // fuer RGB_Color()
#include "svditext.hxx"
#include "svdmodel.hxx"  // fuer DEGREE_CHAR
#include "svdtrans.hxx"
#include "svdglob.hxx"  // Stringcache
#include "svdstr.hrc"
#include "sdgcpitm.hxx"
#include "adjitem.hxx"
#include "writingmodeitem.hxx"

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

#include <xtxasit.hxx>
#include <xfillit0.hxx>
#include <xflclit.hxx>
#include <xlineit0.hxx>

#ifndef _SVX3DITEMS_HXX
#include <svx3ditems.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::rtl;
using namespace ::com::sun::star;

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SdrItemPool::SdrItemPool(USHORT nAttrStart, USHORT nAttrEnd, FASTBOOL bLoadRefCounts):
/*N*/   XOutdevItemPool(nAttrStart,nAttrEnd,bLoadRefCounts)
/*N*/ {
/*N*/   Ctor(NULL,nAttrStart,nAttrEnd);
/*N*/ }

/*N*/ SdrItemPool::SdrItemPool(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd, FASTBOOL bLoadRefCounts):
/*N*/   XOutdevItemPool(pMaster,nAttrStart,nAttrEnd,bLoadRefCounts)
/*N*/ {
/*N*/   Ctor(pMaster,nAttrStart,nAttrEnd);
/*N*/ }

/*N*/ void SdrItemPool::Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd)
/*N*/ {
/*N*/   if (pMaster==NULL) {
/*N*/       pMaster=this;
/*N*/   }
/*N*/
/*N*/   Color aNullCol(RGB_Color(COL_BLACK));
/*N*/   XubString aEmptyStr;
/*N*/
/*N*/   USHORT i;
/*N*/   for (i=SDRATTR_NOTPERSIST_FIRST; i<=SDRATTR_NOTPERSIST_LAST; i++) {
/*N*/       pItemInfos[i-SDRATTR_START]._nFlags=0;
/*N*/   }
/*N*/   // Schatten
/*N*/   ppPoolDefaults[SDRATTR_SHADOW            -SDRATTR_START]=new SdrShadowItem;
/*N*/   ppPoolDefaults[SDRATTR_SHADOWCOLOR       -SDRATTR_START]=new SdrShadowColorItem(aEmptyStr,aNullCol);
/*N*/   ppPoolDefaults[SDRATTR_SHADOWXDIST       -SDRATTR_START]=new SdrShadowXDistItem;
/*N*/   ppPoolDefaults[SDRATTR_SHADOWYDIST       -SDRATTR_START]=new SdrShadowYDistItem;
/*N*/   ppPoolDefaults[SDRATTR_SHADOWTRANSPARENCE-SDRATTR_START]=new SdrShadowTransparenceItem;
/*N*/   ppPoolDefaults[SDRATTR_SHADOW3D          -SDRATTR_START]=new SfxVoidItem(SDRATTR_SHADOW3D    );
/*N*/   ppPoolDefaults[SDRATTR_SHADOWPERSP       -SDRATTR_START]=new SfxVoidItem(SDRATTR_SHADOWPERSP );
/*N*/   for (i=SDRATTR_SHADOWRESERVE1; i<=SDRATTR_SHADOWRESERVE5; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/
/*N*/   ppPoolDefaults[SDRATTRSET_SHADOW-SDRATTR_START]=new SdrShadowSetItem(pMaster);
/*N*/
/*N*/   // SID_ATTR_FILL_SHADOW = SID_SVX_START+299 = SID_LIB_START+299 = 10299
/*N*/   pItemInfos[SDRATTR_SHADOW-SDRATTR_START]._nSID=SID_ATTR_FILL_SHADOW;
/*N*/
/*N*/   // Legendenobjekt
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONTYPE      -SDRATTR_START]=new SdrCaptionTypeItem      ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONFIXEDANGLE-SDRATTR_START]=new SdrCaptionFixedAngleItem;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONANGLE     -SDRATTR_START]=new SdrCaptionAngleItem     ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONGAP       -SDRATTR_START]=new SdrCaptionGapItem       ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONESCDIR    -SDRATTR_START]=new SdrCaptionEscDirItem    ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONESCISREL  -SDRATTR_START]=new SdrCaptionEscIsRelItem  ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONESCREL    -SDRATTR_START]=new SdrCaptionEscRelItem    ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONESCABS    -SDRATTR_START]=new SdrCaptionEscAbsItem    ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONLINELEN   -SDRATTR_START]=new SdrCaptionLineLenItem   ;
/*N*/   ppPoolDefaults[SDRATTR_CAPTIONFITLINELEN-SDRATTR_START]=new SdrCaptionFitLineLenItem;
/*N*/   for (i=SDRATTR_CAPTIONRESERVE1; i<=SDRATTR_CAPTIONRESERVE5; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/   ppPoolDefaults[SDRATTRSET_CAPTION-SDRATTR_START]=new SdrCaptionSetItem(pMaster);
/*N*/
/*N*/   // Outliner-Attribute
/*N*/   ppPoolDefaults[SDRATTRSET_OUTLINER-SDRATTR_START]=new SdrOutlinerSetItem(pMaster);
/*N*/
/*N*/   // Misc-Attribute
/*N*/   ppPoolDefaults[SDRATTR_ECKENRADIUS          -SDRATTR_START]=new SdrEckenradiusItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_MINFRAMEHEIGHT  -SDRATTR_START]=new SdrTextMinFrameHeightItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_AUTOGROWHEIGHT  -SDRATTR_START]=new SdrTextAutoGrowHeightItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_FITTOSIZE       -SDRATTR_START]=new SdrTextFitToSizeTypeItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_LEFTDIST        -SDRATTR_START]=new SdrTextLeftDistItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_RIGHTDIST       -SDRATTR_START]=new SdrTextRightDistItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_UPPERDIST       -SDRATTR_START]=new SdrTextUpperDistItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_LOWERDIST       -SDRATTR_START]=new SdrTextLowerDistItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_VERTADJUST      -SDRATTR_START]=new SdrTextVertAdjustItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_MAXFRAMEHEIGHT  -SDRATTR_START]=new SdrTextMaxFrameHeightItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_MINFRAMEWIDTH   -SDRATTR_START]=new SdrTextMinFrameWidthItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_MAXFRAMEWIDTH   -SDRATTR_START]=new SdrTextMaxFrameWidthItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_AUTOGROWWIDTH   -SDRATTR_START]=new SdrTextAutoGrowWidthItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_HORZADJUST      -SDRATTR_START]=new SdrTextHorzAdjustItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANIKIND         -SDRATTR_START]=new SdrTextAniKindItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANIDIRECTION    -SDRATTR_START]=new SdrTextAniDirectionItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANISTARTINSIDE  -SDRATTR_START]=new SdrTextAniStartInsideItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANISTOPINSIDE   -SDRATTR_START]=new SdrTextAniStopInsideItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANICOUNT        -SDRATTR_START]=new SdrTextAniCountItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANIDELAY        -SDRATTR_START]=new SdrTextAniDelayItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_ANIAMOUNT       -SDRATTR_START]=new SdrTextAniAmountItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXT_CONTOURFRAME    -SDRATTR_START]=new SdrTextContourFrameItem;
/*N*/   ppPoolDefaults[SDRATTR_AUTOSHAPE_ADJUSTMENT -SDRATTR_START]=new SdrAutoShapeAdjustmentItem;
/*N*/ #ifndef SVX_LIGHT
/*N*/   ppPoolDefaults[SDRATTR_XMLATTRIBUTES -SDRATTR_START]=new SvXMLAttrContainerItem( SDRATTR_XMLATTRIBUTES );
/*N*/ #else
/*N*/     // no need to have alien attributes persistent in the player
/*N*/   ppPoolDefaults[SDRATTR_XMLATTRIBUTES -SDRATTR_START]=new SfxVoidItem( SDRATTR_XMLATTRIBUTES );
/*N*/ #endif // #ifndef SVX_LIGHT
/*N*/   for (i=SDRATTR_RESERVE15; i<=SDRATTR_RESERVE19; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/   ppPoolDefaults[SDRATTRSET_MISC-SDRATTR_START]=new SdrMiscSetItem(pMaster);
/*N*/
/*N*/   pItemInfos[SDRATTR_TEXT_FITTOSIZE-SDRATTR_START]._nSID=SID_ATTR_TEXT_FITTOSIZE;
/*N*/
/*N*/   // Objektverbinder
/*N*/   ppPoolDefaults[SDRATTR_EDGEKIND         -SDRATTR_START]=new SdrEdgeKindItem;
/*N*/   long nDefEdgeDist=500; // Erstmal hart defaulted fuer Draw (100TH_MM). hier muss noch der MapMode beruecksichtigt werden.
/*N*/   ppPoolDefaults[SDRATTR_EDGENODE1HORZDIST-SDRATTR_START]=new SdrEdgeNode1HorzDistItem(nDefEdgeDist);
/*N*/   ppPoolDefaults[SDRATTR_EDGENODE1VERTDIST-SDRATTR_START]=new SdrEdgeNode1VertDistItem(nDefEdgeDist);
/*N*/   ppPoolDefaults[SDRATTR_EDGENODE2HORZDIST-SDRATTR_START]=new SdrEdgeNode2HorzDistItem(nDefEdgeDist);
/*N*/   ppPoolDefaults[SDRATTR_EDGENODE2VERTDIST-SDRATTR_START]=new SdrEdgeNode2VertDistItem(nDefEdgeDist);
/*N*/   ppPoolDefaults[SDRATTR_EDGENODE1GLUEDIST-SDRATTR_START]=new SdrEdgeNode1GlueDistItem;
/*N*/   ppPoolDefaults[SDRATTR_EDGENODE2GLUEDIST-SDRATTR_START]=new SdrEdgeNode2GlueDistItem;
/*N*/   ppPoolDefaults[SDRATTR_EDGELINEDELTAANZ -SDRATTR_START]=new SdrEdgeLineDeltaAnzItem;
/*N*/   ppPoolDefaults[SDRATTR_EDGELINE1DELTA   -SDRATTR_START]=new SdrEdgeLine1DeltaItem;
/*N*/   ppPoolDefaults[SDRATTR_EDGELINE2DELTA   -SDRATTR_START]=new SdrEdgeLine2DeltaItem;
/*N*/   ppPoolDefaults[SDRATTR_EDGELINE3DELTA   -SDRATTR_START]=new SdrEdgeLine3DeltaItem;
/*N*/   for (i=SDRATTR_EDGERESERVE02; i<=SDRATTR_EDGERESERVE09; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/   ppPoolDefaults[SDRATTRSET_EDGE-SDRATTR_START]=new SdrEdgeSetItem(pMaster);
/*N*/
/*N*/    // Bemassungsobjekt
/*N*/   ppPoolDefaults[SDRATTR_MEASUREKIND             -SDRATTR_START]=new SdrMeasureKindItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTHPOS         -SDRATTR_START]=new SdrMeasureTextHPosItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTVPOS         -SDRATTR_START]=new SdrMeasureTextVPosItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASURELINEDIST         -SDRATTR_START]=new SdrMeasureLineDistItem(800);
/*N*/   ppPoolDefaults[SDRATTR_MEASUREHELPLINEOVERHANG -SDRATTR_START]=new SdrMeasureHelplineOverhangItem(200);
/*N*/   ppPoolDefaults[SDRATTR_MEASUREHELPLINEDIST     -SDRATTR_START]=new SdrMeasureHelplineDistItem(100);
/*N*/   ppPoolDefaults[SDRATTR_MEASUREHELPLINE1LEN     -SDRATTR_START]=new SdrMeasureHelpline1LenItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASUREHELPLINE2LEN     -SDRATTR_START]=new SdrMeasureHelpline2LenItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASUREBELOWREFEDGE     -SDRATTR_START]=new SdrMeasureBelowRefEdgeItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTROTA90       -SDRATTR_START]=new SdrMeasureTextRota90Item;
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTUPSIDEDOWN   -SDRATTR_START]=new SdrMeasureTextUpsideDownItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASUREOVERHANG         -SDRATTR_START]=new SdrMeasureOverhangItem(600);
/*N*/   ppPoolDefaults[SDRATTR_MEASUREUNIT             -SDRATTR_START]=new SdrMeasureUnitItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASURESCALE            -SDRATTR_START]=new SdrMeasureScaleItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASURESHOWUNIT         -SDRATTR_START]=new SdrMeasureShowUnitItem;
/*N*/   ppPoolDefaults[SDRATTR_MEASUREFORMATSTRING     -SDRATTR_START]=new SdrMeasureFormatStringItem();
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTAUTOANGLE    -SDRATTR_START]=new SdrMeasureTextAutoAngleItem();
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTAUTOANGLEVIEW-SDRATTR_START]=new SdrMeasureTextAutoAngleViewItem();
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTISFIXEDANGLE -SDRATTR_START]=new SdrMeasureTextIsFixedAngleItem();
/*N*/   ppPoolDefaults[SDRATTR_MEASURETEXTFIXEDANGLE   -SDRATTR_START]=new SdrMeasureTextFixedAngleItem();
/*N*/   ppPoolDefaults[SDRATTR_MEASUREDECIMALPLACES    -SDRATTR_START]=new SdrMeasureDecimalPlacesItem();
/*N*/   for (i=SDRATTR_MEASURERESERVE05; i<=SDRATTR_MEASURERESERVE07; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/   ppPoolDefaults[SDRATTRSET_MEASURE-SDRATTR_START]=new SdrMeasureSetItem(pMaster);
/*N*/
/*N*/    // Kreis
/*N*/   ppPoolDefaults[SDRATTR_CIRCKIND      -SDRATTR_START]=new SdrCircKindItem;
/*N*/   ppPoolDefaults[SDRATTR_CIRCSTARTANGLE-SDRATTR_START]=new SdrCircStartAngleItem;
/*N*/   ppPoolDefaults[SDRATTR_CIRCENDANGLE  -SDRATTR_START]=new SdrCircEndAngleItem;
/*N*/   for (i=SDRATTR_CIRCRESERVE0; i<=SDRATTR_CIRCRESERVE3; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/   ppPoolDefaults[SDRATTRSET_CIRC-SDRATTR_START]=new SdrCircSetItem(pMaster);
/*N*/
/*N*/    // Nichtpersistente-Items
/*N*/   ppPoolDefaults[SDRATTR_OBJMOVEPROTECT -SDRATTR_START]=new SdrObjMoveProtectItem;
/*N*/   ppPoolDefaults[SDRATTR_OBJSIZEPROTECT -SDRATTR_START]=new SdrObjSizeProtectItem;
/*N*/   ppPoolDefaults[SDRATTR_OBJPRINTABLE   -SDRATTR_START]=new SdrObjPrintableItem;
/*N*/   ppPoolDefaults[SDRATTR_LAYERID        -SDRATTR_START]=new SdrLayerIdItem;
/*N*/   ppPoolDefaults[SDRATTR_LAYERNAME      -SDRATTR_START]=new SdrLayerNameItem;
/*N*/   ppPoolDefaults[SDRATTR_OBJECTNAME     -SDRATTR_START]=new SdrObjectNameItem;
/*N*/   ppPoolDefaults[SDRATTR_ALLPOSITIONX   -SDRATTR_START]=new SdrAllPositionXItem;
/*N*/   ppPoolDefaults[SDRATTR_ALLPOSITIONY   -SDRATTR_START]=new SdrAllPositionYItem;
/*N*/   ppPoolDefaults[SDRATTR_ALLSIZEWIDTH   -SDRATTR_START]=new SdrAllSizeWidthItem;
/*N*/   ppPoolDefaults[SDRATTR_ALLSIZEHEIGHT  -SDRATTR_START]=new SdrAllSizeHeightItem;
/*N*/   ppPoolDefaults[SDRATTR_ONEPOSITIONX   -SDRATTR_START]=new SdrOnePositionXItem;
/*N*/   ppPoolDefaults[SDRATTR_ONEPOSITIONY   -SDRATTR_START]=new SdrOnePositionYItem;
/*N*/   ppPoolDefaults[SDRATTR_ONESIZEWIDTH   -SDRATTR_START]=new SdrOneSizeWidthItem;
/*N*/   ppPoolDefaults[SDRATTR_ONESIZEHEIGHT  -SDRATTR_START]=new SdrOneSizeHeightItem;
/*N*/   ppPoolDefaults[SDRATTR_LOGICSIZEWIDTH -SDRATTR_START]=new SdrLogicSizeWidthItem;
/*N*/   ppPoolDefaults[SDRATTR_LOGICSIZEHEIGHT-SDRATTR_START]=new SdrLogicSizeHeightItem;
/*N*/   ppPoolDefaults[SDRATTR_ROTATEANGLE    -SDRATTR_START]=new SdrRotateAngleItem;
/*N*/   ppPoolDefaults[SDRATTR_SHEARANGLE     -SDRATTR_START]=new SdrShearAngleItem;
/*N*/   ppPoolDefaults[SDRATTR_MOVEX          -SDRATTR_START]=new SdrMoveXItem;
/*N*/   ppPoolDefaults[SDRATTR_MOVEY          -SDRATTR_START]=new SdrMoveYItem;
/*N*/   ppPoolDefaults[SDRATTR_RESIZEXONE     -SDRATTR_START]=new SdrResizeXOneItem;
/*N*/   ppPoolDefaults[SDRATTR_RESIZEYONE     -SDRATTR_START]=new SdrResizeYOneItem;
/*N*/   ppPoolDefaults[SDRATTR_ROTATEONE      -SDRATTR_START]=new SdrRotateOneItem;
/*N*/   ppPoolDefaults[SDRATTR_HORZSHEARONE   -SDRATTR_START]=new SdrHorzShearOneItem;
/*N*/   ppPoolDefaults[SDRATTR_VERTSHEARONE   -SDRATTR_START]=new SdrVertShearOneItem;
/*N*/   ppPoolDefaults[SDRATTR_RESIZEXALL     -SDRATTR_START]=new SdrResizeXAllItem;
/*N*/   ppPoolDefaults[SDRATTR_RESIZEYALL     -SDRATTR_START]=new SdrResizeYAllItem;
/*N*/   ppPoolDefaults[SDRATTR_ROTATEALL      -SDRATTR_START]=new SdrRotateAllItem;
/*N*/   ppPoolDefaults[SDRATTR_HORZSHEARALL   -SDRATTR_START]=new SdrHorzShearAllItem;
/*N*/   ppPoolDefaults[SDRATTR_VERTSHEARALL   -SDRATTR_START]=new SdrVertShearAllItem;
/*N*/   ppPoolDefaults[SDRATTR_TRANSFORMREF1X -SDRATTR_START]=new SdrTransformRef1XItem;
/*N*/   ppPoolDefaults[SDRATTR_TRANSFORMREF1Y -SDRATTR_START]=new SdrTransformRef1YItem;
/*N*/   ppPoolDefaults[SDRATTR_TRANSFORMREF2X -SDRATTR_START]=new SdrTransformRef2XItem;
/*N*/   ppPoolDefaults[SDRATTR_TRANSFORMREF2Y -SDRATTR_START]=new SdrTransformRef2YItem;
/*N*/   ppPoolDefaults[SDRATTR_TEXTDIRECTION  -SDRATTR_START]=new SvxWritingModeItem;
/*N*/
/*N*/   for (i=SDRATTR_NOTPERSISTRESERVE2; i<=SDRATTR_NOTPERSISTRESERVE15; i++) {
/*N*/       ppPoolDefaults[i-SDRATTR_START]=new SfxVoidItem(i);
/*N*/   }
/*N*/
/*N*/   // Grafik
/*N*/   ppPoolDefaults[ SDRATTR_GRAFRED             - SDRATTR_START] = new SdrGrafRedItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFGREEN           - SDRATTR_START] = new SdrGrafGreenItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFBLUE            - SDRATTR_START] = new SdrGrafBlueItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFLUMINANCE       - SDRATTR_START] = new SdrGrafLuminanceItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFCONTRAST        - SDRATTR_START] = new SdrGrafContrastItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFGAMMA           - SDRATTR_START] = new SdrGrafGamma100Item;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFTRANSPARENCE    - SDRATTR_START] = new SdrGrafTransparenceItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFINVERT          - SDRATTR_START] = new SdrGrafInvertItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFMODE            - SDRATTR_START] = new SdrGrafModeItem;
/*N*/   ppPoolDefaults[ SDRATTR_GRAFCROP            - SDRATTR_START] = new SdrGrafCropItem;
/*N*/   for( i = SDRATTR_GRAFRESERVE3; i <= SDRATTR_GRAFRESERVE6; i++ )
/*N*/       ppPoolDefaults[ i - SDRATTR_START ] = new SfxVoidItem( i );
/*N*/   ppPoolDefaults[ SDRATTRSET_GRAF - SDRATTR_START ] = new SdrGrafSetItem( pMaster );
/*N*/   pItemInfos[SDRATTR_GRAFCROP-SDRATTR_START]._nSID=SID_ATTR_GRAF_CROP;
/*N*/
/*N*/   // 3D Object Attr (28092000 AW)
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_PERCENT_DIAGONAL - SDRATTR_START ] = new Svx3DPercentDiagonalItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_BACKSCALE - SDRATTR_START ] = new Svx3DBackscaleItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_DEPTH - SDRATTR_START ] = new Svx3DDepthItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_HORZ_SEGS - SDRATTR_START ] = new Svx3DHorizontalSegmentsItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_VERT_SEGS - SDRATTR_START ] = new Svx3DVerticalSegmentsItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_END_ANGLE - SDRATTR_START ] = new Svx3DEndAngleItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_DOUBLE_SIDED - SDRATTR_START ] = new Svx3DDoubleSidedItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_NORMALS_KIND - SDRATTR_START ] = new Svx3DNormalsKindItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_NORMALS_INVERT - SDRATTR_START ] = new Svx3DNormalsInvertItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_TEXTURE_PROJ_X - SDRATTR_START ] = new Svx3DTextureProjectionXItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_TEXTURE_PROJ_Y - SDRATTR_START ] = new Svx3DTextureProjectionYItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_SHADOW_3D - SDRATTR_START ] = new Svx3DShadow3DItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_MAT_COLOR - SDRATTR_START ] = new Svx3DMaterialColorItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_MAT_EMISSION - SDRATTR_START ] = new Svx3DMaterialEmissionItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_MAT_SPECULAR - SDRATTR_START ] = new Svx3DMaterialSpecularItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_MAT_SPECULAR_INTENSITY - SDRATTR_START ] = new Svx3DMaterialSpecularIntensityItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_TEXTURE_KIND - SDRATTR_START ] = new Svx3DTextureKindItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_TEXTURE_MODE - SDRATTR_START ] = new Svx3DTextureModeItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_TEXTURE_FILTER - SDRATTR_START ] = new Svx3DTextureFilterItem;
/*N*/
/*N*/   // #107245# Add new items for 3d objects
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_SMOOTH_NORMALS - SDRATTR_START ] = new Svx3DSmoothNormalsItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_SMOOTH_LIDS - SDRATTR_START ] = new Svx3DSmoothLidsItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_CHARACTER_MODE - SDRATTR_START ] = new Svx3DCharacterModeItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_CLOSE_FRONT - SDRATTR_START ] = new Svx3DCloseFrontItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DOBJ_CLOSE_BACK - SDRATTR_START ] = new Svx3DCloseBackItem;
/*N*/
/*N*/   // #107245# Start with SDRATTR_3DOBJ_RESERVED_06 now
/*N*/   for( i = SDRATTR_3DOBJ_RESERVED_06; i <= SDRATTR_3DOBJ_RESERVED_20; i++ )
/*N*/       ppPoolDefaults[ i - SDRATTR_START ] = new SfxVoidItem( i );
/*N*/
/*N*/   // 3D Scene Attr (28092000 AW)
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_PERSPECTIVE - SDRATTR_START ] = new Svx3DPerspectiveItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_DISTANCE - SDRATTR_START ] = new Svx3DDistanceItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_FOCAL_LENGTH - SDRATTR_START ] = new Svx3DFocalLengthItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_TWO_SIDED_LIGHTING - SDRATTR_START ] = new Svx3DTwoSidedLightingItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_1 - SDRATTR_START ] = new Svx3DLightcolor1Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_2 - SDRATTR_START ] = new Svx3DLightcolor2Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_3 - SDRATTR_START ] = new Svx3DLightcolor3Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_4 - SDRATTR_START ] = new Svx3DLightcolor4Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_5 - SDRATTR_START ] = new Svx3DLightcolor5Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_6 - SDRATTR_START ] = new Svx3DLightcolor6Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_7 - SDRATTR_START ] = new Svx3DLightcolor7Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTCOLOR_8 - SDRATTR_START ] = new Svx3DLightcolor8Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_AMBIENTCOLOR - SDRATTR_START ] = new Svx3DAmbientcolorItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_1 - SDRATTR_START ] = new Svx3DLightOnOff1Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_2 - SDRATTR_START ] = new Svx3DLightOnOff2Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_3 - SDRATTR_START ] = new Svx3DLightOnOff3Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_4 - SDRATTR_START ] = new Svx3DLightOnOff4Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_5 - SDRATTR_START ] = new Svx3DLightOnOff5Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_6 - SDRATTR_START ] = new Svx3DLightOnOff6Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_7 - SDRATTR_START ] = new Svx3DLightOnOff7Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTON_8 - SDRATTR_START ] = new Svx3DLightOnOff8Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_1 - SDRATTR_START ] = new Svx3DLightDirection1Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_2 - SDRATTR_START ] = new Svx3DLightDirection2Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_3 - SDRATTR_START ] = new Svx3DLightDirection3Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_4 - SDRATTR_START ] = new Svx3DLightDirection4Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_5 - SDRATTR_START ] = new Svx3DLightDirection5Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_6 - SDRATTR_START ] = new Svx3DLightDirection6Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_7 - SDRATTR_START ] = new Svx3DLightDirection7Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_LIGHTDIRECTION_8 - SDRATTR_START ] = new Svx3DLightDirection8Item;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_SHADOW_SLANT - SDRATTR_START ] = new Svx3DShadowSlantItem;
/*N*/   ppPoolDefaults[ SDRATTR_3DSCENE_SHADE_MODE - SDRATTR_START ] = new Svx3DShadeModeItem;
/*N*/
/*N*/   for( i = SDRATTR_3DSCENE_RESERVED_01; i <= SDRATTR_3DSCENE_RESERVED_20; i++ )
/*N*/       ppPoolDefaults[ i - SDRATTR_START ] = new SfxVoidItem( i );
/*N*/
/*N*/   ////////////////////////////////
/*N*/ #ifdef DBG_UTIL
/*N*/   UINT16 nAnz(SDRATTR_END-SDRATTR_START + 1);
/*N*/
/*N*/   for(UINT16 nNum = 0; nNum < nAnz; nNum++)
/*N*/   {
/*N*/       const SfxPoolItem* pItem = ppPoolDefaults[nNum];
/*N*/
/*N*/       if(!pItem)
/*N*/       {
/*?*/           ByteString aStr("PoolDefaultItem not set: ");
/*?*/
/*?*/           aStr += "Num=";
/*?*/           aStr += ByteString::CreateFromInt32( nNum );
/*?*/           aStr += "Which=";
/*?*/           aStr += ByteString::CreateFromInt32( nNum + 1000 );
/*?*/
/*?*/           DBG_ERROR(aStr.GetBuffer());
/*N*/       }
/*N*/       else if(pItem->Which() != nNum + 1000)
/*N*/       {
/*?*/           ByteString aStr("PoolDefaultItem has wrong WhichId: ");
/*?*/
/*?*/           aStr += "Num=";
/*?*/           aStr += ByteString::CreateFromInt32( nNum );
/*?*/           aStr += " Which=";
/*?*/           aStr += ByteString::CreateFromInt32( pItem->Which() );
/*?*/
/*?*/           DBG_ERROR(aStr.GetBuffer());
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   if (nAttrStart==SDRATTR_START && nAttrEnd==SDRATTR_END) {
/*N*/       SetDefaults(ppPoolDefaults);
/*N*/       SetItemInfos(pItemInfos);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* copy ctor, sorgt dafuer, dass die static defaults gecloned werden
|*            (Parameter 2 = TRUE)
|*
\************************************************************************/

/*N*/ SdrItemPool::SdrItemPool(const SdrItemPool& rPool):
/*N*/   XOutdevItemPool(rPool)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Clone()
|*
\************************************************************************/

/*N*/ SfxItemPool* __EXPORT SdrItemPool::Clone() const
/*N*/ {
/*N*/   return new SdrItemPool(*this);
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SdrItemPool::~SdrItemPool()
/*N*/ {
/*N*/   Delete(); // erstmal den 'dtor' des SfxItemPools rufen
/*N*/   // und nun meine eigenen statischen Defaults abraeumen
/*N*/   if (ppPoolDefaults!=NULL) {
/*N*/       unsigned nBeg=SDRATTR_SHADOW-SDRATTR_START;
/*N*/       unsigned nEnd=SDRATTR_END-SDRATTR_START;
/*N*/       for (unsigned i=nBeg; i<=nEnd; i++) {
/*N*/           SetRefCount(*ppPoolDefaults[i],0);
/*N*/           delete ppPoolDefaults[i];
/*N*/           ppPoolDefaults[i]=NULL;
/*N*/       }
/*N*/   }
/*N*/   // Vor dem zerstoeren die Pools ggf. voneinander trennen
/*N*/   SetSecondaryPool(NULL);
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SdrItemPool::GetPresentation(
//STRIP001            const SfxPoolItem& rItem, SfxItemPresentation ePresentation,
//STRIP001            SfxMapUnit ePresentationMetric, XubString& rText,
//STRIP001               const IntlWrapper * pIntlWrapper) const
//STRIP001 {
//STRIP001  if (!IsInvalidItem(&rItem)) {
//STRIP001      USHORT nWhich=rItem.Which();
//STRIP001      if (nWhich>=SDRATTR_SHADOW_FIRST && nWhich<=SDRATTR_END) {
//STRIP001          rItem.GetPresentation(SFX_ITEM_PRESENTATION_NAMELESS,
//STRIP001                      GetMetric(nWhich),ePresentationMetric,rText,
//STRIP001                         pIntlWrapper);
//STRIP001          String aStr;
//STRIP001
//STRIP001          TakeItemName(nWhich, aStr);
//STRIP001          aStr += sal_Unicode(' ');
//STRIP001          rText.Insert(aStr, 0);
//STRIP001
//STRIP001          return ePresentation;
//STRIP001      }
//STRIP001  }
//STRIP001     return XOutdevItemPool::GetPresentation(rItem,ePresentation,ePresentationMetric,rText,pIntlWrapper);
//STRIP001 }

//STRIP001 FASTBOOL SdrItemPool::TakeItemName(USHORT nWhich, String& rItemName)
//STRIP001 {
//STRIP001  ResMgr* pResMgr = ImpGetResMgr();
//STRIP001  USHORT  nResId = SIP_UNKNOWN_ATTR;
//STRIP001
//STRIP001  switch (nWhich)
//STRIP001  {
//STRIP001      case XATTR_LINESTYLE        : nResId = SIP_XA_LINESTYLE;break;
//STRIP001      case XATTR_LINEDASH         : nResId = SIP_XA_LINEDASH;break;
//STRIP001      case XATTR_LINEWIDTH        : nResId = SIP_XA_LINEWIDTH;break;
//STRIP001      case XATTR_LINECOLOR        : nResId = SIP_XA_LINECOLOR;break;
//STRIP001      case XATTR_LINESTART        : nResId = SIP_XA_LINESTART;break;
//STRIP001      case XATTR_LINEEND          : nResId = SIP_XA_LINEEND;break;
//STRIP001      case XATTR_LINESTARTWIDTH   : nResId = SIP_XA_LINESTARTWIDTH;break;
//STRIP001      case XATTR_LINEENDWIDTH     : nResId = SIP_XA_LINEENDWIDTH;break;
//STRIP001      case XATTR_LINESTARTCENTER  : nResId = SIP_XA_LINESTARTCENTER;break;
//STRIP001      case XATTR_LINEENDCENTER    : nResId = SIP_XA_LINEENDCENTER;break;
//STRIP001      case XATTR_LINETRANSPARENCE : nResId = SIP_XA_LINETRANSPARENCE;break;
//STRIP001      case XATTR_LINEJOINT        : nResId = SIP_XA_LINEJOINT;break;
//STRIP001      case XATTR_LINERESERVED2    : nResId = SIP_XA_LINERESERVED2;break;
//STRIP001      case XATTR_LINERESERVED3    : nResId = SIP_XA_LINERESERVED3;break;
//STRIP001      case XATTR_LINERESERVED4    : nResId = SIP_XA_LINERESERVED4;break;
//STRIP001      case XATTR_LINERESERVED5    : nResId = SIP_XA_LINERESERVED5;break;
//STRIP001      case XATTR_LINERESERVED_LAST: nResId = SIP_XA_LINERESERVED_LAST;break;
//STRIP001      case XATTRSET_LINE          : nResId = SIP_XATTRSET_LINE;break;
//STRIP001
//STRIP001      case XATTR_FILLSTYLE            : nResId = SIP_XA_FILLSTYLE;break;
//STRIP001      case XATTR_FILLCOLOR            : nResId = SIP_XA_FILLCOLOR;break;
//STRIP001      case XATTR_FILLGRADIENT         : nResId = SIP_XA_FILLGRADIENT;break;
//STRIP001      case XATTR_FILLHATCH            : nResId = SIP_XA_FILLHATCH;break;
//STRIP001      case XATTR_FILLBITMAP           : nResId = SIP_XA_FILLBITMAP;break;
//STRIP001      case XATTR_FILLTRANSPARENCE     : nResId = SIP_XA_FILLTRANSPARENCE;break;
//STRIP001      case XATTR_GRADIENTSTEPCOUNT    : nResId = SIP_XA_GRADIENTSTEPCOUNT;break;
//STRIP001      case XATTR_FILLBMP_TILE         : nResId = SIP_XA_FILLBMP_TILE;break;
//STRIP001      case XATTR_FILLBMP_POS          : nResId = SIP_XA_FILLBMP_POS;break;
//STRIP001      case XATTR_FILLBMP_SIZEX        : nResId = SIP_XA_FILLBMP_SIZEX;break;
//STRIP001      case XATTR_FILLBMP_SIZEY        : nResId = SIP_XA_FILLBMP_SIZEY;break;
//STRIP001      case XATTR_FILLFLOATTRANSPARENCE: nResId = SIP_XA_FILLFLOATTRANSPARENCE;break;
//STRIP001      case XATTR_FILLRESERVED2        : nResId = SIP_XA_FILLRESERVED2;break;
//STRIP001      case XATTR_FILLBMP_SIZELOG      : nResId = SIP_XA_FILLBMP_SIZELOG;break;
//STRIP001      case XATTR_FILLBMP_TILEOFFSETX  : nResId = SIP_XA_FILLBMP_TILEOFFSETX;break;
//STRIP001      case XATTR_FILLBMP_TILEOFFSETY  : nResId = SIP_XA_FILLBMP_TILEOFFSETY;break;
//STRIP001      case XATTR_FILLBMP_STRETCH      : nResId = SIP_XA_FILLBMP_STRETCH;break;
//STRIP001      case XATTR_FILLRESERVED3        : nResId = SIP_XA_FILLRESERVED3;break;
//STRIP001      case XATTR_FILLRESERVED4        : nResId = SIP_XA_FILLRESERVED4;break;
//STRIP001      case XATTR_FILLRESERVED5        : nResId = SIP_XA_FILLRESERVED5;break;
//STRIP001      case XATTR_FILLRESERVED6        : nResId = SIP_XA_FILLRESERVED6;break;
//STRIP001      case XATTR_FILLRESERVED7        : nResId = SIP_XA_FILLRESERVED7;break;
//STRIP001      case XATTR_FILLRESERVED8        : nResId = SIP_XA_FILLRESERVED8;break;
//STRIP001      case XATTR_FILLBMP_POSOFFSETX   : nResId = SIP_XA_FILLBMP_POSOFFSETX;break;
//STRIP001      case XATTR_FILLBMP_POSOFFSETY   : nResId = SIP_XA_FILLBMP_POSOFFSETY;break;
//STRIP001      case XATTR_FILLBACKGROUND       : nResId = SIP_XA_FILLBACKGROUND;break;
//STRIP001      case XATTR_FILLRESERVED10       : nResId = SIP_XA_FILLRESERVED10;break;
//STRIP001      case XATTR_FILLRESERVED11       : nResId = SIP_XA_FILLRESERVED11;break;
//STRIP001      case XATTR_FILLRESERVED_LAST    : nResId = SIP_XA_FILLRESERVED_LAST;break;
//STRIP001
//STRIP001      case XATTRSET_FILL             : nResId = SIP_XATTRSET_FILL;break;
//STRIP001
//STRIP001      case XATTR_FORMTXTSTYLE     : nResId = SIP_XA_FORMTXTSTYLE;break;
//STRIP001      case XATTR_FORMTXTADJUST    : nResId = SIP_XA_FORMTXTADJUST;break;
//STRIP001      case XATTR_FORMTXTDISTANCE  : nResId = SIP_XA_FORMTXTDISTANCE;break;
//STRIP001      case XATTR_FORMTXTSTART     : nResId = SIP_XA_FORMTXTSTART;break;
//STRIP001      case XATTR_FORMTXTMIRROR    : nResId = SIP_XA_FORMTXTMIRROR;break;
//STRIP001      case XATTR_FORMTXTOUTLINE   : nResId = SIP_XA_FORMTXTOUTLINE;break;
//STRIP001      case XATTR_FORMTXTSHADOW    : nResId = SIP_XA_FORMTXTSHADOW;break;
//STRIP001      case XATTR_FORMTXTSHDWCOLOR : nResId = SIP_XA_FORMTXTSHDWCOLOR;break;
//STRIP001      case XATTR_FORMTXTSHDWXVAL  : nResId = SIP_XA_FORMTXTSHDWXVAL;break;
//STRIP001      case XATTR_FORMTXTSHDWYVAL  : nResId = SIP_XA_FORMTXTSHDWYVAL;break;
//STRIP001      case XATTR_FORMTXTSTDFORM   : nResId = SIP_XA_FORMTXTSTDFORM;break;
//STRIP001      case XATTR_FORMTXTHIDEFORM  : nResId = SIP_XA_FORMTXTHIDEFORM;break;
//STRIP001      case XATTR_FORMTXTSHDWTRANSP: nResId = SIP_XA_FORMTXTSHDWTRANSP;break;
//STRIP001      case XATTR_FTRESERVED2      : nResId = SIP_XA_FTRESERVED2;break;
//STRIP001      case XATTR_FTRESERVED3      : nResId = SIP_XA_FTRESERVED3;break;
//STRIP001      case XATTR_FTRESERVED4      : nResId = SIP_XA_FTRESERVED4;break;
//STRIP001      case XATTR_FTRESERVED5      : nResId = SIP_XA_FTRESERVED5;break;
//STRIP001      case XATTR_FTRESERVED_LAST  : nResId = SIP_XA_FTRESERVED_LAST;break;
//STRIP001      case XATTRSET_TEXT          : nResId = SIP_XATTRSET_TEXT;break;
//STRIP001
//STRIP001      case SDRATTR_SHADOW            : nResId = SIP_SA_SHADOW;break;
//STRIP001      case SDRATTR_SHADOWCOLOR       : nResId = SIP_SA_SHADOWCOLOR;break;
//STRIP001      case SDRATTR_SHADOWXDIST       : nResId = SIP_SA_SHADOWXDIST;break;
//STRIP001      case SDRATTR_SHADOWYDIST       : nResId = SIP_SA_SHADOWYDIST;break;
//STRIP001      case SDRATTR_SHADOWTRANSPARENCE: nResId = SIP_SA_SHADOWTRANSPARENCE;break;
//STRIP001      case SDRATTR_SHADOW3D          : nResId = SIP_SA_SHADOW3D;break;
//STRIP001      case SDRATTR_SHADOWPERSP       : nResId = SIP_SA_SHADOWPERSP;break;
//STRIP001      case SDRATTR_SHADOWRESERVE1    : nResId = SIP_SA_SHADOWRESERVE1;break;
//STRIP001      case SDRATTR_SHADOWRESERVE2    : nResId = SIP_SA_SHADOWRESERVE2;break;
//STRIP001      case SDRATTR_SHADOWRESERVE3    : nResId = SIP_SA_SHADOWRESERVE3;break;
//STRIP001      case SDRATTR_SHADOWRESERVE4    : nResId = SIP_SA_SHADOWRESERVE4;break;
//STRIP001      case SDRATTR_SHADOWRESERVE5    : nResId = SIP_SA_SHADOWRESERVE5;break;
//STRIP001      case SDRATTRSET_SHADOW         : nResId = SIP_SDRATTRSET_SHADOW;break;
//STRIP001
//STRIP001      case SDRATTR_CAPTIONTYPE      : nResId = SIP_SA_CAPTIONTYPE;break;
//STRIP001      case SDRATTR_CAPTIONFIXEDANGLE: nResId = SIP_SA_CAPTIONFIXEDANGLE;break;
//STRIP001      case SDRATTR_CAPTIONANGLE     : nResId = SIP_SA_CAPTIONANGLE;break;
//STRIP001      case SDRATTR_CAPTIONGAP       : nResId = SIP_SA_CAPTIONGAP;break;
//STRIP001      case SDRATTR_CAPTIONESCDIR    : nResId = SIP_SA_CAPTIONESCDIR;break;
//STRIP001      case SDRATTR_CAPTIONESCISREL  : nResId = SIP_SA_CAPTIONESCISREL;break;
//STRIP001      case SDRATTR_CAPTIONESCREL    : nResId = SIP_SA_CAPTIONESCREL;break;
//STRIP001      case SDRATTR_CAPTIONESCABS    : nResId = SIP_SA_CAPTIONESCABS;break;
//STRIP001      case SDRATTR_CAPTIONLINELEN   : nResId = SIP_SA_CAPTIONLINELEN;break;
//STRIP001      case SDRATTR_CAPTIONFITLINELEN: nResId = SIP_SA_CAPTIONFITLINELEN;break;
//STRIP001      case SDRATTR_CAPTIONRESERVE1  : nResId = SIP_SA_CAPTIONRESERVE1;break;
//STRIP001      case SDRATTR_CAPTIONRESERVE2  : nResId = SIP_SA_CAPTIONRESERVE2;break;
//STRIP001      case SDRATTR_CAPTIONRESERVE3  : nResId = SIP_SA_CAPTIONRESERVE3;break;
//STRIP001      case SDRATTR_CAPTIONRESERVE4  : nResId = SIP_SA_CAPTIONRESERVE4;break;
//STRIP001      case SDRATTR_CAPTIONRESERVE5  : nResId = SIP_SA_CAPTIONRESERVE5;break;
//STRIP001      case SDRATTRSET_CAPTION       : nResId = SIP_SDRATTRSET_CAPTION;break;
//STRIP001
//STRIP001      case SDRATTRSET_OUTLINER: nResId = SIP_SDRATTRSET_OUTLINER;break;
//STRIP001
//STRIP001      case SDRATTR_ECKENRADIUS            : nResId = SIP_SA_ECKENRADIUS;break;
//STRIP001      case SDRATTR_TEXT_MINFRAMEHEIGHT    : nResId = SIP_SA_TEXT_MINFRAMEHEIGHT;break;
//STRIP001      case SDRATTR_TEXT_AUTOGROWHEIGHT    : nResId = SIP_SA_TEXT_AUTOGROWHEIGHT;break;
//STRIP001      case SDRATTR_TEXT_FITTOSIZE         : nResId = SIP_SA_TEXT_FITTOSIZE;break;
//STRIP001      case SDRATTR_TEXT_LEFTDIST          : nResId = SIP_SA_TEXT_LEFTDIST;break;
//STRIP001      case SDRATTR_TEXT_RIGHTDIST         : nResId = SIP_SA_TEXT_RIGHTDIST;break;
//STRIP001      case SDRATTR_TEXT_UPPERDIST         : nResId = SIP_SA_TEXT_UPPERDIST;break;
//STRIP001      case SDRATTR_TEXT_LOWERDIST         : nResId = SIP_SA_TEXT_LOWERDIST;break;
//STRIP001      case SDRATTR_TEXT_VERTADJUST        : nResId = SIP_SA_TEXT_VERTADJUST;break;
//STRIP001      case SDRATTR_TEXT_MAXFRAMEHEIGHT    : nResId = SIP_SA_TEXT_MAXFRAMEHEIGHT;break;
//STRIP001      case SDRATTR_TEXT_MINFRAMEWIDTH     : nResId = SIP_SA_TEXT_MINFRAMEWIDTH;break;
//STRIP001      case SDRATTR_TEXT_MAXFRAMEWIDTH     : nResId = SIP_SA_TEXT_MAXFRAMEWIDTH;break;
//STRIP001      case SDRATTR_TEXT_AUTOGROWWIDTH     : nResId = SIP_SA_TEXT_AUTOGROWWIDTH;break;
//STRIP001      case SDRATTR_TEXT_HORZADJUST        : nResId = SIP_SA_TEXT_HORZADJUST;break;
//STRIP001      case SDRATTR_TEXT_ANIKIND           : nResId = SIP_SA_TEXT_ANIKIND;break;
//STRIP001      case SDRATTR_TEXT_ANIDIRECTION      : nResId = SIP_SA_TEXT_ANIDIRECTION;break;
//STRIP001      case SDRATTR_TEXT_ANISTARTINSIDE    : nResId = SIP_SA_TEXT_ANISTARTINSIDE;break;
//STRIP001      case SDRATTR_TEXT_ANISTOPINSIDE     : nResId = SIP_SA_TEXT_ANISTOPINSIDE;break;
//STRIP001      case SDRATTR_TEXT_ANICOUNT          : nResId = SIP_SA_TEXT_ANICOUNT;break;
//STRIP001      case SDRATTR_TEXT_ANIDELAY          : nResId = SIP_SA_TEXT_ANIDELAY;break;
//STRIP001      case SDRATTR_TEXT_ANIAMOUNT         : nResId = SIP_SA_TEXT_ANIAMOUNT;break;
//STRIP001      case SDRATTR_TEXT_CONTOURFRAME      : nResId = SIP_SA_TEXT_CONTOURFRAME;break;
//STRIP001      case SDRATTR_AUTOSHAPE_ADJUSTMENT   : nResId = SIP_SA_AUTOSHAPE_ADJUSTMENT;break;
//STRIP001      case SDRATTR_XMLATTRIBUTES          : nResId = SIP_SA_XMLATTRIBUTES;break;
//STRIP001      case SDRATTR_RESERVE15              : nResId = SIP_SA_RESERVE15;break;
//STRIP001      case SDRATTR_RESERVE16              : nResId = SIP_SA_RESERVE16;break;
//STRIP001      case SDRATTR_RESERVE17              : nResId = SIP_SA_RESERVE17;break;
//STRIP001      case SDRATTR_RESERVE18              : nResId = SIP_SA_RESERVE18;break;
//STRIP001      case SDRATTR_RESERVE19              : nResId = SIP_SA_RESERVE19;break;
//STRIP001      case SDRATTRSET_MISC                : nResId = SIP_SDRATTRSET_MISC;break;
//STRIP001
//STRIP001      case SDRATTR_EDGEKIND           : nResId = SIP_SA_EDGEKIND;break;
//STRIP001      case SDRATTR_EDGENODE1HORZDIST  : nResId = SIP_SA_EDGENODE1HORZDIST;break;
//STRIP001      case SDRATTR_EDGENODE1VERTDIST  : nResId = SIP_SA_EDGENODE1VERTDIST;break;
//STRIP001      case SDRATTR_EDGENODE2HORZDIST  : nResId = SIP_SA_EDGENODE2HORZDIST;break;
//STRIP001      case SDRATTR_EDGENODE2VERTDIST  : nResId = SIP_SA_EDGENODE2VERTDIST;break;
//STRIP001      case SDRATTR_EDGENODE1GLUEDIST  : nResId = SIP_SA_EDGENODE1GLUEDIST;break;
//STRIP001      case SDRATTR_EDGENODE2GLUEDIST  : nResId = SIP_SA_EDGENODE2GLUEDIST;break;
//STRIP001      case SDRATTR_EDGELINEDELTAANZ   : nResId = SIP_SA_EDGELINEDELTAANZ;break;
//STRIP001      case SDRATTR_EDGELINE1DELTA     : nResId = SIP_SA_EDGELINE1DELTA;break;
//STRIP001      case SDRATTR_EDGELINE2DELTA     : nResId = SIP_SA_EDGELINE2DELTA;break;
//STRIP001      case SDRATTR_EDGELINE3DELTA     : nResId = SIP_SA_EDGELINE3DELTA;break;
//STRIP001      case SDRATTR_EDGERESERVE02      : nResId = SIP_SA_EDGERESERVE02;break;
//STRIP001      case SDRATTR_EDGERESERVE03      : nResId = SIP_SA_EDGERESERVE03;break;
//STRIP001      case SDRATTR_EDGERESERVE04      : nResId = SIP_SA_EDGERESERVE04;break;
//STRIP001      case SDRATTR_EDGERESERVE05      : nResId = SIP_SA_EDGERESERVE05;break;
//STRIP001      case SDRATTR_EDGERESERVE06      : nResId = SIP_SA_EDGERESERVE06;break;
//STRIP001      case SDRATTR_EDGERESERVE07      : nResId = SIP_SA_EDGERESERVE07;break;
//STRIP001      case SDRATTR_EDGERESERVE08      : nResId = SIP_SA_EDGERESERVE08;break;
//STRIP001      case SDRATTR_EDGERESERVE09      : nResId = SIP_SA_EDGERESERVE09;break;
//STRIP001      case SDRATTRSET_EDGE            : nResId = SIP_SDRATTRSET_EDGE;break;
//STRIP001
//STRIP001      case SDRATTR_MEASUREKIND             : nResId = SIP_SA_MEASUREKIND;break;
//STRIP001      case SDRATTR_MEASURETEXTHPOS         : nResId = SIP_SA_MEASURETEXTHPOS;break;
//STRIP001      case SDRATTR_MEASURETEXTVPOS         : nResId = SIP_SA_MEASURETEXTVPOS;break;
//STRIP001      case SDRATTR_MEASURELINEDIST         : nResId = SIP_SA_MEASURELINEDIST;break;
//STRIP001      case SDRATTR_MEASUREHELPLINEOVERHANG : nResId = SIP_SA_MEASUREHELPLINEOVERHANG;break;
//STRIP001      case SDRATTR_MEASUREHELPLINEDIST     : nResId = SIP_SA_MEASUREHELPLINEDIST;break;
//STRIP001      case SDRATTR_MEASUREHELPLINE1LEN     : nResId = SIP_SA_MEASUREHELPLINE1LEN;break;
//STRIP001      case SDRATTR_MEASUREHELPLINE2LEN     : nResId = SIP_SA_MEASUREHELPLINE2LEN;break;
//STRIP001      case SDRATTR_MEASUREBELOWREFEDGE     : nResId = SIP_SA_MEASUREBELOWREFEDGE;break;
//STRIP001      case SDRATTR_MEASURETEXTROTA90       : nResId = SIP_SA_MEASURETEXTROTA90;break;
//STRIP001      case SDRATTR_MEASURETEXTUPSIDEDOWN   : nResId = SIP_SA_MEASURETEXTUPSIDEDOWN;break;
//STRIP001      case SDRATTR_MEASUREOVERHANG         : nResId = SIP_SA_MEASUREOVERHANG;break;
//STRIP001      case SDRATTR_MEASUREUNIT             : nResId = SIP_SA_MEASUREUNIT;break;
//STRIP001      case SDRATTR_MEASURESCALE            : nResId = SIP_SA_MEASURESCALE;break;
//STRIP001      case SDRATTR_MEASURESHOWUNIT         : nResId = SIP_SA_MEASURESHOWUNIT;break;
//STRIP001      case SDRATTR_MEASUREFORMATSTRING     : nResId = SIP_SA_MEASUREFORMATSTRING;break;
//STRIP001      case SDRATTR_MEASURETEXTAUTOANGLE    : nResId = SIP_SA_MEASURETEXTAUTOANGLE;break;
//STRIP001      case SDRATTR_MEASURETEXTAUTOANGLEVIEW: nResId = SIP_SA_MEASURETEXTAUTOANGLEVIEW;break;
//STRIP001      case SDRATTR_MEASURETEXTISFIXEDANGLE : nResId = SIP_SA_MEASURETEXTISFIXEDANGLE;break;
//STRIP001      case SDRATTR_MEASURETEXTFIXEDANGLE   : nResId = SIP_SA_MEASURETEXTFIXEDANGLE;break;
//STRIP001      case SDRATTR_MEASUREDECIMALPLACES    : nResId = SIP_SA_MEASUREDECIMALPLACES;break;
//STRIP001      case SDRATTR_MEASURERESERVE05        : nResId = SIP_SA_MEASURERESERVE05;break;
//STRIP001      case SDRATTR_MEASURERESERVE06        : nResId = SIP_SA_MEASURERESERVE06;break;
//STRIP001      case SDRATTR_MEASURERESERVE07        : nResId = SIP_SA_MEASURERESERVE07;break;
//STRIP001      case SDRATTRSET_MEASURE              : nResId = SIP_SDRATTRSET_MEASURE;break;
//STRIP001
//STRIP001      case SDRATTR_CIRCKIND      : nResId = SIP_SA_CIRCKIND;break;
//STRIP001      case SDRATTR_CIRCSTARTANGLE: nResId = SIP_SA_CIRCSTARTANGLE;break;
//STRIP001      case SDRATTR_CIRCENDANGLE  : nResId = SIP_SA_CIRCENDANGLE;break;
//STRIP001      case SDRATTR_CIRCRESERVE0  : nResId = SIP_SA_CIRCRESERVE0;break;
//STRIP001      case SDRATTR_CIRCRESERVE1  : nResId = SIP_SA_CIRCRESERVE1;break;
//STRIP001      case SDRATTR_CIRCRESERVE2  : nResId = SIP_SA_CIRCRESERVE2;break;
//STRIP001      case SDRATTR_CIRCRESERVE3  : nResId = SIP_SA_CIRCRESERVE3;break;
//STRIP001      case SDRATTRSET_CIRC       : nResId = SIP_SDRATTRSET_CIRC;break;
//STRIP001
//STRIP001      case SDRATTR_OBJMOVEPROTECT : nResId = SIP_SA_OBJMOVEPROTECT;break;
//STRIP001      case SDRATTR_OBJSIZEPROTECT : nResId = SIP_SA_OBJSIZEPROTECT;break;
//STRIP001      case SDRATTR_OBJPRINTABLE   : nResId = SIP_SA_OBJPRINTABLE;break;
//STRIP001      case SDRATTR_LAYERID        : nResId = SIP_SA_LAYERID;break;
//STRIP001      case SDRATTR_LAYERNAME      : nResId = SIP_SA_LAYERNAME;break;
//STRIP001      case SDRATTR_OBJECTNAME     : nResId = SIP_SA_OBJECTNAME;break;
//STRIP001      case SDRATTR_ALLPOSITIONX   : nResId = SIP_SA_ALLPOSITIONX;break;
//STRIP001      case SDRATTR_ALLPOSITIONY   : nResId = SIP_SA_ALLPOSITIONY;break;
//STRIP001      case SDRATTR_ALLSIZEWIDTH   : nResId = SIP_SA_ALLSIZEWIDTH;break;
//STRIP001      case SDRATTR_ALLSIZEHEIGHT  : nResId = SIP_SA_ALLSIZEHEIGHT;break;
//STRIP001      case SDRATTR_ONEPOSITIONX   : nResId = SIP_SA_ONEPOSITIONX;break;
//STRIP001      case SDRATTR_ONEPOSITIONY   : nResId = SIP_SA_ONEPOSITIONY;break;
//STRIP001      case SDRATTR_ONESIZEWIDTH   : nResId = SIP_SA_ONESIZEWIDTH;break;
//STRIP001      case SDRATTR_ONESIZEHEIGHT  : nResId = SIP_SA_ONESIZEHEIGHT;break;
//STRIP001      case SDRATTR_LOGICSIZEWIDTH : nResId = SIP_SA_LOGICSIZEWIDTH;break;
//STRIP001      case SDRATTR_LOGICSIZEHEIGHT: nResId = SIP_SA_LOGICSIZEHEIGHT;break;
//STRIP001      case SDRATTR_ROTATEANGLE    : nResId = SIP_SA_ROTATEANGLE;break;
//STRIP001      case SDRATTR_SHEARANGLE     : nResId = SIP_SA_SHEARANGLE;break;
//STRIP001      case SDRATTR_MOVEX          : nResId = SIP_SA_MOVEX;break;
//STRIP001      case SDRATTR_MOVEY          : nResId = SIP_SA_MOVEY;break;
//STRIP001      case SDRATTR_RESIZEXONE     : nResId = SIP_SA_RESIZEXONE;break;
//STRIP001      case SDRATTR_RESIZEYONE     : nResId = SIP_SA_RESIZEYONE;break;
//STRIP001      case SDRATTR_ROTATEONE      : nResId = SIP_SA_ROTATEONE;break;
//STRIP001      case SDRATTR_HORZSHEARONE   : nResId = SIP_SA_HORZSHEARONE;break;
//STRIP001      case SDRATTR_VERTSHEARONE   : nResId = SIP_SA_VERTSHEARONE;break;
//STRIP001      case SDRATTR_RESIZEXALL     : nResId = SIP_SA_RESIZEXALL;break;
//STRIP001      case SDRATTR_RESIZEYALL     : nResId = SIP_SA_RESIZEYALL;break;
//STRIP001      case SDRATTR_ROTATEALL      : nResId = SIP_SA_ROTATEALL;break;
//STRIP001      case SDRATTR_HORZSHEARALL   : nResId = SIP_SA_HORZSHEARALL;break;
//STRIP001      case SDRATTR_VERTSHEARALL   : nResId = SIP_SA_VERTSHEARALL;break;
//STRIP001      case SDRATTR_TRANSFORMREF1X : nResId = SIP_SA_TRANSFORMREF1X;break;
//STRIP001      case SDRATTR_TRANSFORMREF1Y : nResId = SIP_SA_TRANSFORMREF1Y;break;
//STRIP001      case SDRATTR_TRANSFORMREF2X : nResId = SIP_SA_TRANSFORMREF2X;break;
//STRIP001      case SDRATTR_TRANSFORMREF2Y : nResId = SIP_SA_TRANSFORMREF2Y;break;
//STRIP001
//STRIP001      case SDRATTR_GRAFRED            : nResId = SIP_SA_GRAFRED;break;
//STRIP001      case SDRATTR_GRAFGREEN          : nResId = SIP_SA_GRAFGREEN;break;
//STRIP001      case SDRATTR_GRAFBLUE           : nResId = SIP_SA_GRAFBLUE;break;
//STRIP001      case SDRATTR_GRAFLUMINANCE      : nResId = SIP_SA_GRAFLUMINANCE;break;
//STRIP001      case SDRATTR_GRAFCONTRAST       : nResId = SIP_SA_GRAFCONTRAST;break;
//STRIP001      case SDRATTR_GRAFGAMMA          : nResId = SIP_SA_GRAFGAMMA;break;
//STRIP001      case SDRATTR_GRAFTRANSPARENCE   : nResId = SIP_SA_GRAFTRANSPARENCE;break;
//STRIP001      case SDRATTR_GRAFINVERT         : nResId = SIP_SA_GRAFINVERT;break;
//STRIP001      case SDRATTR_GRAFMODE           : nResId = SIP_SA_GRAFMODE;break;
//STRIP001      case SDRATTR_GRAFCROP           : nResId = SIP_SA_GRAFCROP;break;
//STRIP001      case SDRATTR_GRAFRESERVE3       : nResId = SIP_SA_GRAFRESERVE3;break;
//STRIP001      case SDRATTR_GRAFRESERVE4       : nResId = SIP_SA_GRAFRESERVE4;break;
//STRIP001      case SDRATTR_GRAFRESERVE5       : nResId = SIP_SA_GRAFRESERVE5;break;
//STRIP001      case SDRATTR_GRAFRESERVE6       : nResId = SIP_SA_GRAFRESERVE6;break;
//STRIP001      case SDRATTRSET_GRAF            : nResId = SIP_SDRATTRSET_GRAF;break;
//STRIP001
//STRIP001      case EE_PARA_HYPHENATE  : nResId = SIP_EE_PARA_HYPHENATE;break;
//STRIP001      case EE_PARA_BULLETSTATE: nResId = SIP_EE_PARA_BULLETSTATE;break;
//STRIP001      case EE_PARA_OUTLLRSPACE: nResId = SIP_EE_PARA_OUTLLRSPACE;break;
//STRIP001      case EE_PARA_OUTLLEVEL  : nResId = SIP_EE_PARA_OUTLLEVEL;break;
//STRIP001      case EE_PARA_BULLET     : nResId = SIP_EE_PARA_BULLET;break;
//STRIP001      case EE_PARA_LRSPACE    : nResId = SIP_EE_PARA_LRSPACE;break;
//STRIP001      case EE_PARA_ULSPACE    : nResId = SIP_EE_PARA_ULSPACE;break;
//STRIP001      case EE_PARA_SBL        : nResId = SIP_EE_PARA_SBL;break;
//STRIP001      case EE_PARA_JUST       : nResId = SIP_EE_PARA_JUST;break;
//STRIP001      case EE_PARA_TABS       : nResId = SIP_EE_PARA_TABS;break;
//STRIP001
//STRIP001      case EE_CHAR_COLOR      : nResId = SIP_EE_CHAR_COLOR;break;
//STRIP001      case EE_CHAR_FONTINFO   : nResId = SIP_EE_CHAR_FONTINFO;break;
//STRIP001      case EE_CHAR_FONTHEIGHT : nResId = SIP_EE_CHAR_FONTHEIGHT;break;
//STRIP001      case EE_CHAR_FONTWIDTH  : nResId = SIP_EE_CHAR_FONTWIDTH;break;
//STRIP001      case EE_CHAR_WEIGHT     : nResId = SIP_EE_CHAR_WEIGHT;break;
//STRIP001      case EE_CHAR_UNDERLINE  : nResId = SIP_EE_CHAR_UNDERLINE;break;
//STRIP001      case EE_CHAR_STRIKEOUT  : nResId = SIP_EE_CHAR_STRIKEOUT;break;
//STRIP001      case EE_CHAR_ITALIC     : nResId = SIP_EE_CHAR_ITALIC;break;
//STRIP001      case EE_CHAR_OUTLINE    : nResId = SIP_EE_CHAR_OUTLINE;break;
//STRIP001      case EE_CHAR_SHADOW     : nResId = SIP_EE_CHAR_SHADOW;break;
//STRIP001      case EE_CHAR_ESCAPEMENT : nResId = SIP_EE_CHAR_ESCAPEMENT;break;
//STRIP001      case EE_CHAR_PAIRKERNING: nResId = SIP_EE_CHAR_PAIRKERNING;break;
//STRIP001      case EE_CHAR_KERNING    : nResId = SIP_EE_CHAR_KERNING;break;
//STRIP001      case EE_CHAR_WLM        : nResId = SIP_EE_CHAR_WLM;break;
//STRIP001      case EE_FEATURE_TAB     : nResId = SIP_EE_FEATURE_TAB;break;
//STRIP001      case EE_FEATURE_LINEBR  : nResId = SIP_EE_FEATURE_LINEBR;break;
//STRIP001      case EE_FEATURE_NOTCONV : nResId = SIP_EE_FEATURE_NOTCONV;break;
//STRIP001      case EE_FEATURE_FIELD   : nResId = SIP_EE_FEATURE_FIELD;break;
//STRIP001  } // switch
//STRIP001
//STRIP001  rItemName = String( ResId( nResId, pResMgr ) );
//STRIP001
//STRIP001  return (BOOL)rItemName.Len();
//STRIP001 }

//STRIP001 BOOL SdrItemPool::TakeWhichName(USHORT nWhich, ByteString& rWhichName)
//STRIP001 {
//STRIP001  ByteString aStr;
//STRIP001
//STRIP001 #ifdef DBG_UTIL
//STRIP001  switch(nWhich)
//STRIP001  {
//STRIP001      case XATTR_LINESTYLE                 : aStr="XATTR_LINESTYLE                 "; break;
//STRIP001      case XATTR_LINEDASH                  : aStr="XATTR_LINEDASH                  "; break;
//STRIP001      case XATTR_LINEWIDTH                 : aStr="XATTR_LINEWIDTH                 "; break;
//STRIP001      case XATTR_LINECOLOR                 : aStr="XATTR_LINECOLOR                 "; break;
//STRIP001      case XATTR_LINESTART                 : aStr="XATTR_LINESTART                 "; break;
//STRIP001      case XATTR_LINEEND                   : aStr="XATTR_LINEEND                   "; break;
//STRIP001      case XATTR_LINESTARTWIDTH            : aStr="XATTR_LINESTARTWIDTH            "; break;
//STRIP001      case XATTR_LINEENDWIDTH              : aStr="XATTR_LINEENDWIDTH              "; break;
//STRIP001      case XATTR_LINESTARTCENTER           : aStr="XATTR_LINESTARTCENTER           "; break;
//STRIP001      case XATTR_LINEENDCENTER             : aStr="XATTR_LINEENDCENTER             "; break;
//STRIP001      case XATTR_LINETRANSPARENCE          : aStr="XATTR_LINETRANSPARENCE          "; break;
//STRIP001      case XATTR_LINEJOINT                 : aStr="XATTR_LINEJOINT                 "; break;
//STRIP001      case XATTR_LINERESERVED2             : aStr="XATTR_LINERESERVED2             "; break;
//STRIP001      case XATTR_LINERESERVED3             : aStr="XATTR_LINERESERVED3             "; break;
//STRIP001      case XATTR_LINERESERVED4             : aStr="XATTR_LINERESERVED4             "; break;
//STRIP001      case XATTR_LINERESERVED5             : aStr="XATTR_LINERESERVED5             "; break;
//STRIP001      case XATTR_LINERESERVED_LAST         : aStr="XATTR_LINERESERVED_LAST         "; break;
//STRIP001      case XATTRSET_LINE                   : aStr="XATTRSET_LINE                   "; break;
//STRIP001
//STRIP001      case XATTR_FILLSTYLE                 : aStr="XATTR_FILLSTYLE                 "; break;
//STRIP001      case XATTR_FILLCOLOR                 : aStr="XATTR_FILLCOLOR                 "; break;
//STRIP001      case XATTR_FILLGRADIENT              : aStr="XATTR_FILLGRADIENT              "; break;
//STRIP001      case XATTR_FILLHATCH                 : aStr="XATTR_FILLHATCH                 "; break;
//STRIP001      case XATTR_FILLBITMAP                : aStr="XATTR_FILLBITMAP                "; break;
//STRIP001      case XATTR_FILLTRANSPARENCE          : aStr="XATTR_FILLTRANSPARENCE          "; break;
//STRIP001      case XATTR_GRADIENTSTEPCOUNT         : aStr="XATTR_GRADIENTSTEPCOUNT         "; break;
//STRIP001
//STRIP001      case XATTR_FILLBMP_TILE              : aStr="XATTR_FILLBMP_TILE              "; break;
//STRIP001      case XATTR_FILLBMP_POS               : aStr="XATTR_FILLBMP_POS               "; break;
//STRIP001      case XATTR_FILLBMP_SIZEX             : aStr="XATTR_FILLBMP_SIZEX             "; break;
//STRIP001      case XATTR_FILLBMP_SIZEY             : aStr="XATTR_FILLBMP_SIZEY             "; break;
//STRIP001      case XATTR_FILLFLOATTRANSPARENCE     : aStr="XATTR_FILLFLOATTRANSPARENCE     "; break;
//STRIP001      case XATTR_FILLRESERVED2             : aStr="XATTR_FILLRESERVED2             "; break;
//STRIP001      case XATTR_FILLBMP_SIZELOG           : aStr="XATTR_FILLBMP_SIZELOG           "; break;
//STRIP001      case XATTR_FILLBMP_TILEOFFSETX       : aStr="XATTR_FILLBMP_TILEOFFSETX       "; break;
//STRIP001      case XATTR_FILLBMP_TILEOFFSETY       : aStr="XATTR_FILLBMP_TILEOFFSETY       "; break;
//STRIP001
//STRIP001      case XATTR_FILLBMP_STRETCH           : aStr="XATTR_FILLBMP_STRETCH           "; break;
//STRIP001      case XATTR_FILLRESERVED3             : aStr="XATTR_FILLRESERVED3             "; break;
//STRIP001      case XATTR_FILLRESERVED4             : aStr="XATTR_FILLRESERVED4             "; break;
//STRIP001      case XATTR_FILLRESERVED5             : aStr="XATTR_FILLRESERVED5             "; break;
//STRIP001      case XATTR_FILLRESERVED6             : aStr="XATTR_FILLRESERVED6             "; break;
//STRIP001      case XATTR_FILLRESERVED7             : aStr="XATTR_FILLRESERVED7             "; break;
//STRIP001      case XATTR_FILLRESERVED8             : aStr="XATTR_FILLRESERVED8             "; break;
//STRIP001      case XATTR_FILLBMP_POSOFFSETX        : aStr="XATTR_FILLBMP_POSOFFSETX        "; break;
//STRIP001      case XATTR_FILLBMP_POSOFFSETY        : aStr="XATTR_FILLBMP_POSOFFSETY        "; break;
//STRIP001      case XATTR_FILLBACKGROUND            : aStr="XATTR_FILLBACKGROUND            "; break;
//STRIP001      case XATTR_FILLRESERVED10            : aStr="XATTR_FILLRESERVED10            "; break;
//STRIP001      case XATTR_FILLRESERVED11            : aStr="XATTR_FILLRESERVED11            "; break;
//STRIP001      case XATTR_FILLRESERVED_LAST         : aStr="XATTR_FILLRESERVED_LAST         "; break;
//STRIP001
//STRIP001      case XATTRSET_FILL                   : aStr="XATTRSET_FILL                   "; break;
//STRIP001
//STRIP001      case XATTR_FORMTXTSTYLE              : aStr="XATTR_FORMTXTSTYLE              "; break;
//STRIP001      case XATTR_FORMTXTADJUST             : aStr="XATTR_FORMTXTADJUST             "; break;
//STRIP001      case XATTR_FORMTXTDISTANCE           : aStr="XATTR_FORMTXTDISTANCE           "; break;
//STRIP001      case XATTR_FORMTXTSTART              : aStr="XATTR_FORMTXTSTART              "; break;
//STRIP001      case XATTR_FORMTXTMIRROR             : aStr="XATTR_FORMTXTMIRROR             "; break;
//STRIP001      case XATTR_FORMTXTOUTLINE            : aStr="XATTR_FORMTXTOUTLINE            "; break;
//STRIP001      case XATTR_FORMTXTSHADOW             : aStr="XATTR_FORMTXTSHADOW             "; break;
//STRIP001      case XATTR_FORMTXTSHDWCOLOR          : aStr="XATTR_FORMTXTSHDWCOLOR          "; break;
//STRIP001      case XATTR_FORMTXTSHDWXVAL           : aStr="XATTR_FORMTXTSHDWXVAL           "; break;
//STRIP001      case XATTR_FORMTXTSHDWYVAL           : aStr="XATTR_FORMTXTSHDWYVAL           "; break;
//STRIP001      case XATTR_FORMTXTSTDFORM            : aStr="XATTR_FORMTXTSTDFORM            "; break;
//STRIP001      case XATTR_FORMTXTHIDEFORM           : aStr="XATTR_FORMTXTHIDEFORM           "; break;
//STRIP001      case XATTR_FORMTXTSHDWTRANSP         : aStr="XATTR_FORMTXTSHDWTRANSP         "; break;
//STRIP001      case XATTR_FTRESERVED2               : aStr="XATTR_FTRESERVED2               "; break;
//STRIP001      case XATTR_FTRESERVED3               : aStr="XATTR_FTRESERVED3               "; break;
//STRIP001      case XATTR_FTRESERVED4               : aStr="XATTR_FTRESERVED4               "; break;
//STRIP001      case XATTR_FTRESERVED5               : aStr="XATTR_FTRESERVED5               "; break;
//STRIP001      case XATTR_FTRESERVED_LAST           : aStr="XATTR_FTRESERVED_LAST           "; break;
//STRIP001      case XATTRSET_TEXT                   : aStr="XATTRSET_TEXT                   "; break;
//STRIP001
//STRIP001      case SDRATTR_SHADOW                  : aStr="SDRATTR_SHADOW                  "; break;
//STRIP001      case SDRATTR_SHADOWCOLOR             : aStr="SDRATTR_SHADOWCOLOR             "; break;
//STRIP001      case SDRATTR_SHADOWXDIST             : aStr="SDRATTR_SHADOWXDIST             "; break;
//STRIP001      case SDRATTR_SHADOWYDIST             : aStr="SDRATTR_SHADOWYDIST             "; break;
//STRIP001      case SDRATTR_SHADOWTRANSPARENCE      : aStr="SDRATTR_SHADOWTRANSPARENCE      "; break;
//STRIP001      case SDRATTR_SHADOW3D                : aStr="SDRATTR_SHADOW3D                "; break;
//STRIP001      case SDRATTR_SHADOWPERSP             : aStr="SDRATTR_SHADOWPERSP             "; break;
//STRIP001      case SDRATTR_SHADOWRESERVE1          : aStr="SDRATTR_SHADOWRESERVE1          "; break;
//STRIP001      case SDRATTR_SHADOWRESERVE2          : aStr="SDRATTR_SHADOWRESERVE2          "; break;
//STRIP001      case SDRATTR_SHADOWRESERVE3          : aStr="SDRATTR_SHADOWRESERVE3          "; break;
//STRIP001      case SDRATTR_SHADOWRESERVE4          : aStr="SDRATTR_SHADOWRESERVE4          "; break;
//STRIP001      case SDRATTR_SHADOWRESERVE5          : aStr="SDRATTR_SHADOWRESERVE5          "; break;
//STRIP001      case SDRATTRSET_SHADOW               : aStr="SDRATTRSET_SHADOW               "; break;
//STRIP001
//STRIP001      case SDRATTR_CAPTIONTYPE             : aStr="SDRATTR_CAPTIONTYPE             "; break;
//STRIP001      case SDRATTR_CAPTIONFIXEDANGLE       : aStr="SDRATTR_CAPTIONFIXEDANGLE       "; break;
//STRIP001      case SDRATTR_CAPTIONANGLE            : aStr="SDRATTR_CAPTIONANGLE            "; break;
//STRIP001      case SDRATTR_CAPTIONGAP              : aStr="SDRATTR_CAPTIONGAP              "; break;
//STRIP001      case SDRATTR_CAPTIONESCDIR           : aStr="SDRATTR_CAPTIONESCDIR           "; break;
//STRIP001      case SDRATTR_CAPTIONESCISREL         : aStr="SDRATTR_CAPTIONESCISREL         "; break;
//STRIP001      case SDRATTR_CAPTIONESCREL           : aStr="SDRATTR_CAPTIONESCREL           "; break;
//STRIP001      case SDRATTR_CAPTIONESCABS           : aStr="SDRATTR_CAPTIONESCABS           "; break;
//STRIP001      case SDRATTR_CAPTIONLINELEN          : aStr="SDRATTR_CAPTIONLINELEN          "; break;
//STRIP001      case SDRATTR_CAPTIONFITLINELEN       : aStr="SDRATTR_CAPTIONFITLINELEN       "; break;
//STRIP001      case SDRATTR_CAPTIONRESERVE1         : aStr="SDRATTR_CAPTIONRESERVE1         "; break;
//STRIP001      case SDRATTR_CAPTIONRESERVE2         : aStr="SDRATTR_CAPTIONRESERVE2         "; break;
//STRIP001      case SDRATTR_CAPTIONRESERVE3         : aStr="SDRATTR_CAPTIONRESERVE3         "; break;
//STRIP001      case SDRATTR_CAPTIONRESERVE4         : aStr="SDRATTR_CAPTIONRESERVE4         "; break;
//STRIP001      case SDRATTR_CAPTIONRESERVE5         : aStr="SDRATTR_CAPTIONRESERVE5         "; break;
//STRIP001      case SDRATTRSET_CAPTION              : aStr="SDRATTRSET_CAPTION              "; break;
//STRIP001
//STRIP001      case SDRATTRSET_OUTLINER             : aStr="SDRATTRSET_OUTLINER             "; break;
//STRIP001
//STRIP001      case SDRATTR_ECKENRADIUS             : aStr="SDRATTR_ECKENRADIUS             "; break;
//STRIP001      case SDRATTR_TEXT_MINFRAMEHEIGHT     : aStr="SDRATTR_TEXT_MINFRAMEHEIGHT     "; break;
//STRIP001      case SDRATTR_TEXT_AUTOGROWHEIGHT     : aStr="SDRATTR_TEXT_AUTOGROWHEIGHT     "; break;
//STRIP001      case SDRATTR_TEXT_FITTOSIZE          : aStr="SDRATTR_TEXT_FITTOSIZE          "; break;
//STRIP001      case SDRATTR_TEXT_LEFTDIST           : aStr="SDRATTR_TEXT_LEFTDIST           "; break;
//STRIP001      case SDRATTR_TEXT_RIGHTDIST          : aStr="SDRATTR_TEXT_RIGHTDIST          "; break;
//STRIP001      case SDRATTR_TEXT_UPPERDIST          : aStr="SDRATTR_TEXT_UPPERDIST          "; break;
//STRIP001      case SDRATTR_TEXT_LOWERDIST          : aStr="SDRATTR_TEXT_LOWERDIST          "; break;
//STRIP001      case SDRATTR_TEXT_VERTADJUST         : aStr="SDRATTR_TEXT_VERTADJUST         "; break;
//STRIP001      case SDRATTR_TEXT_MAXFRAMEHEIGHT     : aStr="SDRATTR_TEXT_MAXFRAMEHEIGHT     "; break;
//STRIP001      case SDRATTR_TEXT_MINFRAMEWIDTH      : aStr="SDRATTR_TEXT_MINFRAMEWIDTH      "; break;
//STRIP001      case SDRATTR_TEXT_MAXFRAMEWIDTH      : aStr="SDRATTR_TEXT_MAXFRAMEWIDTH      "; break;
//STRIP001      case SDRATTR_TEXT_AUTOGROWWIDTH      : aStr="SDRATTR_TEXT_AUTOGROWWIDTH      "; break;
//STRIP001      case SDRATTR_TEXT_HORZADJUST         : aStr="SDRATTR_TEXT_HORZADJUST         "; break;
//STRIP001      case SDRATTR_TEXT_ANIKIND            : aStr="SDRATTR_TEXT_ANIKIND            "; break;
//STRIP001      case SDRATTR_TEXT_ANIDIRECTION       : aStr="SDRATTR_TEXT_ANIDIRECTION       "; break;
//STRIP001      case SDRATTR_TEXT_ANISTARTINSIDE     : aStr="SDRATTR_TEXT_ANISTARTINSIDE     "; break;
//STRIP001      case SDRATTR_TEXT_ANISTOPINSIDE      : aStr="SDRATTR_TEXT_ANISTOPINSIDE      "; break;
//STRIP001      case SDRATTR_TEXT_ANICOUNT           : aStr="SDRATTR_TEXT_ANICOUNT           "; break;
//STRIP001      case SDRATTR_TEXT_ANIDELAY           : aStr="SDRATTR_TEXT_ANIDELAY           "; break;
//STRIP001      case SDRATTR_TEXT_ANIAMOUNT          : aStr="SDRATTR_TEXT_ANIAMOUNT          "; break;
//STRIP001      case SDRATTR_TEXT_CONTOURFRAME       : aStr="SDRATTR_TEXT_CONTOURFRAME       "; break;
//STRIP001      case SDRATTR_AUTOSHAPE_ADJUSTMENT    : aStr="SDRATTR_AUTOSHAPE_ADJUSTMENT    "; break;
//STRIP001      case SDRATTR_XMLATTRIBUTES           : aStr="SDRATTR_XMLATTRIBUTES           "; break;
//STRIP001      case SDRATTR_RESERVE15               : aStr="SDRATTR_RESERVE15               "; break;
//STRIP001      case SDRATTR_RESERVE16               : aStr="SDRATTR_RESERVE16               "; break;
//STRIP001      case SDRATTR_RESERVE17               : aStr="SDRATTR_RESERVE17               "; break;
//STRIP001      case SDRATTR_RESERVE18               : aStr="SDRATTR_RESERVE18               "; break;
//STRIP001      case SDRATTR_RESERVE19               : aStr="SDRATTR_RESERVE19               "; break;
//STRIP001      case SDRATTRSET_MISC                 : aStr="SDRATTRSET_MISC                 "; break;
//STRIP001
//STRIP001      case SDRATTR_EDGEKIND                : aStr="SDRATTR_EDGEKIND                "; break;
//STRIP001      case SDRATTR_EDGENODE1HORZDIST       : aStr="SDRATTR_EDGENODE1HORZDIST       "; break;
//STRIP001      case SDRATTR_EDGENODE1VERTDIST       : aStr="SDRATTR_EDGENODE1VERTDIST       "; break;
//STRIP001      case SDRATTR_EDGENODE2HORZDIST       : aStr="SDRATTR_EDGENODE2HORZDIST       "; break;
//STRIP001      case SDRATTR_EDGENODE2VERTDIST       : aStr="SDRATTR_EDGENODE2VERTDIST       "; break;
//STRIP001      case SDRATTR_EDGENODE1GLUEDIST       : aStr="SDRATTR_EDGENODE1GLUEDIST       "; break;
//STRIP001      case SDRATTR_EDGENODE2GLUEDIST       : aStr="SDRATTR_EDGENODE2GLUEDIST       "; break;
//STRIP001      case SDRATTR_EDGELINEDELTAANZ        : aStr="SDRATTR_EDGELINEDELTAANZ        "; break;
//STRIP001      case SDRATTR_EDGELINE1DELTA          : aStr="SDRATTR_EDGELINE1DELTA          "; break;
//STRIP001      case SDRATTR_EDGELINE2DELTA          : aStr="SDRATTR_EDGELINE2DELTA          "; break;
//STRIP001      case SDRATTR_EDGELINE3DELTA          : aStr="SDRATTR_EDGELINE3DELTA          "; break;
//STRIP001      case SDRATTR_EDGERESERVE02           : aStr="SDRATTR_EDGERESERVE02           "; break;
//STRIP001      case SDRATTR_EDGERESERVE03           : aStr="SDRATTR_EDGERESERVE03           "; break;
//STRIP001      case SDRATTR_EDGERESERVE04           : aStr="SDRATTR_EDGERESERVE04           "; break;
//STRIP001      case SDRATTR_EDGERESERVE05           : aStr="SDRATTR_EDGERESERVE05           "; break;
//STRIP001      case SDRATTR_EDGERESERVE06           : aStr="SDRATTR_EDGERESERVE06           "; break;
//STRIP001      case SDRATTR_EDGERESERVE07           : aStr="SDRATTR_EDGERESERVE07           "; break;
//STRIP001      case SDRATTR_EDGERESERVE08           : aStr="SDRATTR_EDGERESERVE08           "; break;
//STRIP001      case SDRATTR_EDGERESERVE09           : aStr="SDRATTR_EDGERESERVE09           "; break;
//STRIP001      case SDRATTRSET_EDGE                 : aStr="SDRATTRSET_EDGE                 "; break;
//STRIP001
//STRIP001      case SDRATTR_MEASUREKIND             : aStr="SDRATTR_MEASUREKIND             "; break;
//STRIP001      case SDRATTR_MEASURETEXTHPOS         : aStr="SDRATTR_MEASURETEXTHPOS         "; break;
//STRIP001      case SDRATTR_MEASURETEXTVPOS         : aStr="SDRATTR_MEASURETEXTVPOS         "; break;
//STRIP001      case SDRATTR_MEASURELINEDIST         : aStr="SDRATTR_MEASURELINEDIST         "; break;
//STRIP001      case SDRATTR_MEASUREHELPLINEOVERHANG : aStr="SDRATTR_MEASUREHELPLINEOVERHANG "; break;
//STRIP001      case SDRATTR_MEASUREHELPLINEDIST     : aStr="SDRATTR_MEASUREHELPLINEDIST     "; break;
//STRIP001      case SDRATTR_MEASUREHELPLINE1LEN     : aStr="SDRATTR_MEASUREHELPLINE1LEN     "; break;
//STRIP001      case SDRATTR_MEASUREHELPLINE2LEN     : aStr="SDRATTR_MEASUREHELPLINE2LEN     "; break;
//STRIP001      case SDRATTR_MEASUREBELOWREFEDGE     : aStr="SDRATTR_MEASUREBELOWREFEDGE     "; break;
//STRIP001      case SDRATTR_MEASURETEXTROTA90       : aStr="SDRATTR_MEASURETEXTROTA90       "; break;
//STRIP001      case SDRATTR_MEASURETEXTUPSIDEDOWN   : aStr="SDRATTR_MEASURETEXTUPSIDEDOWN   "; break;
//STRIP001      case SDRATTR_MEASUREOVERHANG         : aStr="SDRATTR_MEASUREOVERHANG         "; break;
//STRIP001      case SDRATTR_MEASUREUNIT             : aStr="SDRATTR_MEASUREUNIT             "; break;
//STRIP001      case SDRATTR_MEASURESCALE            : aStr="SDRATTR_MEASURESCALE            "; break;
//STRIP001      case SDRATTR_MEASURESHOWUNIT         : aStr="SDRATTR_MEASURESHOWUNIT         "; break;
//STRIP001      case SDRATTR_MEASUREFORMATSTRING     : aStr="SDRATTR_MEASUREFORMATSTRING     "; break;
//STRIP001      case SDRATTR_MEASURETEXTAUTOANGLE    : aStr="SDRATTR_MEASURETEXTAUTOANGLE    "; break;
//STRIP001      case SDRATTR_MEASURETEXTAUTOANGLEVIEW: aStr="SDRATTR_MEASURETEXTAUTOANGLEVIEW"; break;
//STRIP001      case SDRATTR_MEASURETEXTISFIXEDANGLE : aStr="SDRATTR_MEASURETEXTISFIXEDANGLE "; break;
//STRIP001      case SDRATTR_MEASURETEXTFIXEDANGLE   : aStr="SDRATTR_MEASURETEXTFIXEDANGLE   "; break;
//STRIP001      case SDRATTR_MEASUREDECIMALPLACES    : aStr="SDRATTR_MEASUREDECIMALPLACES    "; break;
//STRIP001      case SDRATTR_MEASURERESERVE05        : aStr="SDRATTR_MEASURERESERVE05        "; break;
//STRIP001      case SDRATTR_MEASURERESERVE06        : aStr="SDRATTR_MEASURERESERVE06        "; break;
//STRIP001      case SDRATTR_MEASURERESERVE07        : aStr="SDRATTR_MEASURERESERVE07        "; break;
//STRIP001      case SDRATTRSET_MEASURE              : aStr="SDRATTRSET_MEASURE              "; break;
//STRIP001
//STRIP001      case SDRATTR_CIRCKIND                : aStr="SDRATTR_CIRCKIND                "; break;
//STRIP001      case SDRATTR_CIRCSTARTANGLE          : aStr="SDRATTR_CIRCSTARTANGLE          "; break;
//STRIP001      case SDRATTR_CIRCENDANGLE            : aStr="SDRATTR_CIRCENDANGLE            "; break;
//STRIP001      case SDRATTR_CIRCRESERVE0            : aStr="SDRATTR_CIRCRESERVE0            "; break;
//STRIP001      case SDRATTR_CIRCRESERVE1            : aStr="SDRATTR_CIRCRESERVE1            "; break;
//STRIP001      case SDRATTR_CIRCRESERVE2            : aStr="SDRATTR_CIRCRESERVE2            "; break;
//STRIP001      case SDRATTR_CIRCRESERVE3            : aStr="SDRATTR_CIRCRESERVE3            "; break;
//STRIP001      case SDRATTRSET_CIRC                 : aStr="SDRATTRSET_CIRC                 "; break;
//STRIP001
//STRIP001      case SDRATTR_OBJMOVEPROTECT          : aStr="SDRATTR_OBJMOVEPROTECT          "; break;
//STRIP001      case SDRATTR_OBJSIZEPROTECT          : aStr="SDRATTR_OBJSIZEPROTECT          "; break;
//STRIP001      case SDRATTR_OBJPRINTABLE            : aStr="SDRATTR_OBJPRINTABLE            "; break;
//STRIP001      case SDRATTR_LAYERID                 : aStr="SDRATTR_LAYERID                 "; break;
//STRIP001      case SDRATTR_LAYERNAME               : aStr="SDRATTR_LAYERNAME               "; break;
//STRIP001      case SDRATTR_OBJECTNAME              : aStr="SDRATTR_OBJECTNAME              "; break;
//STRIP001      case SDRATTR_ALLPOSITIONX            : aStr="SDRATTR_ALLPOSITIONX            "; break;
//STRIP001      case SDRATTR_ALLPOSITIONY            : aStr="SDRATTR_ALLPOSITIONY            "; break;
//STRIP001      case SDRATTR_ALLSIZEWIDTH            : aStr="SDRATTR_ALLSIZEWIDTH            "; break;
//STRIP001      case SDRATTR_ALLSIZEHEIGHT           : aStr="SDRATTR_ALLSIZEHEIGHT           "; break;
//STRIP001      case SDRATTR_ONEPOSITIONX            : aStr="SDRATTR_ONEPOSITIONX            "; break;
//STRIP001      case SDRATTR_ONEPOSITIONY            : aStr="SDRATTR_ONEPOSITIONY            "; break;
//STRIP001      case SDRATTR_ONESIZEWIDTH            : aStr="SDRATTR_ONESIZEWIDTH            "; break;
//STRIP001      case SDRATTR_ONESIZEHEIGHT           : aStr="SDRATTR_ONESIZEHEIGHT           "; break;
//STRIP001      case SDRATTR_LOGICSIZEWIDTH          : aStr="SDRATTR_LOGICSIZEWIDTH          "; break;
//STRIP001      case SDRATTR_LOGICSIZEHEIGHT         : aStr="SDRATTR_LOGICSIZEHEIGHT         "; break;
//STRIP001      case SDRATTR_ROTATEANGLE             : aStr="SDRATTR_ROTATEANGLE             "; break;
//STRIP001      case SDRATTR_SHEARANGLE              : aStr="SDRATTR_SHEARANGLE              "; break;
//STRIP001      case SDRATTR_MOVEX                   : aStr="SDRATTR_MOVEX                   "; break;
//STRIP001      case SDRATTR_MOVEY                   : aStr="SDRATTR_MOVEY                   "; break;
//STRIP001      case SDRATTR_RESIZEXONE              : aStr="SDRATTR_RESIZEXONE              "; break;
//STRIP001      case SDRATTR_RESIZEYONE              : aStr="SDRATTR_RESIZEYONE              "; break;
//STRIP001      case SDRATTR_ROTATEONE               : aStr="SDRATTR_ROTATEONE               "; break;
//STRIP001      case SDRATTR_HORZSHEARONE            : aStr="SDRATTR_HORZSHEARONE            "; break;
//STRIP001      case SDRATTR_VERTSHEARONE            : aStr="SDRATTR_VERTSHEARONE            "; break;
//STRIP001      case SDRATTR_RESIZEXALL              : aStr="SDRATTR_RESIZEXALL              "; break;
//STRIP001      case SDRATTR_RESIZEYALL              : aStr="SDRATTR_RESIZEYALL              "; break;
//STRIP001      case SDRATTR_ROTATEALL               : aStr="SDRATTR_ROTATEALL               "; break;
//STRIP001      case SDRATTR_HORZSHEARALL            : aStr="SDRATTR_HORZSHEARALL            "; break;
//STRIP001      case SDRATTR_VERTSHEARALL            : aStr="SDRATTR_VERTSHEARALL            "; break;
//STRIP001      case SDRATTR_TRANSFORMREF1X          : aStr="SDRATTR_TRANSFORMREF1X          "; break;
//STRIP001      case SDRATTR_TRANSFORMREF1Y          : aStr="SDRATTR_TRANSFORMREF1Y          "; break;
//STRIP001      case SDRATTR_TRANSFORMREF2X          : aStr="SDRATTR_TRANSFORMREF2X          "; break;
//STRIP001      case SDRATTR_TRANSFORMREF2Y          : aStr="SDRATTR_TRANSFORMREF2Y          "; break;
//STRIP001
//STRIP001      case SDRATTR_GRAFRED                 : aStr="SDRATTR_GRAFRED                 "; break;
//STRIP001      case SDRATTR_GRAFGREEN               : aStr="SDRATTR_GRAFGREEN               "; break;
//STRIP001      case SDRATTR_GRAFBLUE                : aStr="SDRATTR_GRAFBLUE                "; break;
//STRIP001      case SDRATTR_GRAFLUMINANCE           : aStr="SDRATTR_GRAFLUMINANCE           "; break;
//STRIP001      case SDRATTR_GRAFCONTRAST            : aStr="SDRATTR_GRAFCONTRAST            "; break;
//STRIP001      case SDRATTR_GRAFGAMMA               : aStr="SDRATTR_GRAFGAMMA               "; break;
//STRIP001      case SDRATTR_GRAFTRANSPARENCE        : aStr="SDRATTR_GRAFTRANSPARENCE        "; break;
//STRIP001      case SDRATTR_GRAFINVERT              : aStr="SDRATTR_GRAFINVERT              "; break;
//STRIP001      case SDRATTR_GRAFMODE                : aStr="SDRATTR_GRAFMODE                "; break;
//STRIP001      case SDRATTR_GRAFCROP                : aStr="SDRATTR_GRAFCROP                "; break;
//STRIP001      case SDRATTR_GRAFRESERVE3            : aStr="SDRATTR_GRAFRESERVE3            "; break;
//STRIP001      case SDRATTR_GRAFRESERVE4            : aStr="SDRATTR_GRAFRESERVE4            "; break;
//STRIP001      case SDRATTR_GRAFRESERVE5            : aStr="SDRATTR_GRAFRESERVE5            "; break;
//STRIP001      case SDRATTR_GRAFRESERVE6            : aStr="SDRATTR_GRAFRESERVE6            "; break;
//STRIP001      case SDRATTRSET_GRAF                 : aStr="SDRATTRSET_GRAF                 "; break;
//STRIP001
//STRIP001      case EE_PARA_HYPHENATE               : aStr="EE_PARA_HYPHENATE               "; break;
//STRIP001      case EE_PARA_BULLETSTATE             : aStr="EE_PARA_BULLETSTATE             "; break;
//STRIP001      case EE_PARA_OUTLLRSPACE             : aStr="EE_PARA_OUTLLRSPACE             "; break;
//STRIP001      case EE_PARA_OUTLLEVEL               : aStr="EE_PARA_OUTLLEVEL               "; break;
//STRIP001      case EE_PARA_BULLET                  : aStr="EE_PARA_BULLET                  "; break;
//STRIP001      case EE_PARA_LRSPACE                 : aStr="EE_PARA_LRSPACE                 "; break;
//STRIP001      case EE_PARA_ULSPACE                 : aStr="EE_PARA_ULSPACE                 "; break;
//STRIP001      case EE_PARA_SBL                     : aStr="EE_PARA_SBL                     "; break;
//STRIP001      case EE_PARA_JUST                    : aStr="EE_PARA_JUST                    "; break;
//STRIP001      case EE_PARA_TABS                    : aStr="EE_PARA_TABS                    "; break;
//STRIP001
//STRIP001      case EE_CHAR_COLOR                   : aStr="EE_CHAR_COLOR                   "; break;
//STRIP001      case EE_CHAR_FONTINFO                : aStr="EE_CHAR_FONTINFO                "; break;
//STRIP001      case EE_CHAR_FONTHEIGHT              : aStr="EE_CHAR_FONTHEIGHT              "; break;
//STRIP001      case EE_CHAR_FONTWIDTH               : aStr="EE_CHAR_FONTWIDTH               "; break;
//STRIP001      case EE_CHAR_WEIGHT                  : aStr="EE_CHAR_WEIGHT                  "; break;
//STRIP001      case EE_CHAR_UNDERLINE               : aStr="EE_CHAR_UNDERLINE               "; break;
//STRIP001      case EE_CHAR_STRIKEOUT               : aStr="EE_CHAR_STRIKEOUT               "; break;
//STRIP001      case EE_CHAR_ITALIC                  : aStr="EE_CHAR_ITALIC                  "; break;
//STRIP001      case EE_CHAR_OUTLINE                 : aStr="EE_CHAR_OUTLINE                 "; break;
//STRIP001      case EE_CHAR_SHADOW                  : aStr="EE_CHAR_SHADOW                  "; break;
//STRIP001      case EE_CHAR_ESCAPEMENT              : aStr="EE_CHAR_ESCAPEMENT              "; break;
//STRIP001      case EE_CHAR_PAIRKERNING             : aStr="EE_CHAR_PAIRKERNING             "; break;
//STRIP001      case EE_CHAR_KERNING                 : aStr="EE_CHAR_KERNING                 "; break;
//STRIP001      case EE_CHAR_WLM                     : aStr="EE_CHAR_WLM                     "; break;
//STRIP001      case EE_FEATURE_TAB                  : aStr="EE_FEATURE_TAB                  "; break;
//STRIP001      case EE_FEATURE_LINEBR               : aStr="EE_FEATURE_LINEBR               "; break;
//STRIP001      case EE_FEATURE_NOTCONV              : aStr="EE_FEATURE_NOTCONV              "; break;
//STRIP001      case EE_FEATURE_FIELD                : aStr="EE_FEATURE_FIELD                "; break;
//STRIP001  } // switch
//STRIP001
//STRIP001  aStr.EraseTrailingChars();
//STRIP001 #endif // if DBG_UTIL
//STRIP001
//STRIP001  rWhichName = aStr;
//STRIP001  return (BOOL)aStr.Len();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////
// FractionItem
////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1_AUTOFACTORY(SdrFractionItem,SfxPoolItem);

/*N*/ SdrFractionItem::SdrFractionItem(USHORT nId, SvStream& rIn):
/*N*/   SfxPoolItem(nId)
/*N*/ {
/*N*/   INT32 nMul,nDiv;
/*N*/   rIn>>nMul;
/*N*/   rIn>>nDiv;
/*N*/   nValue=Fraction(nMul,nDiv);
/*N*/ }

/*N*/ int __EXPORT SdrFractionItem::operator==(const SfxPoolItem& rCmp) const
/*N*/ {
/*N*/   return SfxPoolItem::operator==(rCmp) &&
/*N*/          ((SdrFractionItem&)rCmp).GetValue()==nValue;
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SdrFractionItem::GetPresentation(
//STRIP001  SfxItemPresentation ePresentation, SfxMapUnit eCoreMetric,
//STRIP001     SfxMapUnit ePresentationMetric, XubString &rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  if(nValue.IsValid())
//STRIP001  {
//STRIP001      INT32 nDiv = nValue.GetDenominator();
//STRIP001      rText = UniString::CreateFromInt32(nValue.GetNumerator());
//STRIP001
//STRIP001      if(nDiv != 1)
//STRIP001      {
//STRIP001          rText += sal_Unicode('/');
//STRIP001          rText += UniString::CreateFromInt32(nDiv);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rText = UniString();
//STRIP001      rText += sal_Unicode('?');
//STRIP001  }
//STRIP001
//STRIP001  if(ePresentation == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePresentation;
//STRIP001 }

//STRIP001 SfxPoolItem* __EXPORT SdrFractionItem::Create(SvStream& rIn, USHORT nVer) const
//STRIP001 {
//STRIP001  return new SdrFractionItem(Which(),rIn);
//STRIP001 }

/*?*/ SvStream& __EXPORT SdrFractionItem::Store(SvStream& rOut, USHORT nItemVers) const
/*?*/ {
/*?*/   rOut<<INT32(nValue.GetNumerator());
/*?*/   rOut<<INT32(nValue.GetDenominator());
/*?*/   return rOut;
/*?*/ }

/*N*/ SfxPoolItem* __EXPORT SdrFractionItem::Clone(SfxItemPool *pPool) const
/*N*/ {
/*N*/   return new SdrFractionItem(Which(),GetValue());
/*N*/ }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrFractionItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId<SDRATTR_NOTPERSIST_FIRST || nId>SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

////////////////////////////////////////////////////////////////////////////////
// ScaleItem
////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1_AUTOFACTORY(SdrScaleItem,SdrFractionItem);

//STRIP001 SfxItemPresentation __EXPORT SdrScaleItem::GetPresentation(
//STRIP001  SfxItemPresentation ePresentation, SfxMapUnit eCoreMetric,
//STRIP001     SfxMapUnit ePresentationMetric, XubString &rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  if(GetValue().IsValid())
//STRIP001  {
//STRIP001      INT32 nDiv = GetValue().GetDenominator();
//STRIP001
//STRIP001      rText = UniString::CreateFromInt32(GetValue().GetNumerator());
//STRIP001      rText += sal_Unicode(':');
//STRIP001      rText += UniString::CreateFromInt32(nDiv);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rText = UniString();
//STRIP001      rText += sal_Unicode('?');
//STRIP001  }
//STRIP001
//STRIP001  if(ePresentation == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePresentation;
//STRIP001 }

/*N*/ SfxPoolItem* __EXPORT SdrScaleItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SdrScaleItem(Which(),rIn);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrScaleItem::Clone(SfxItemPool *pPool) const
/*N*/ {
/*N*/   return new SdrScaleItem(Which(),GetValue());
/*N*/ }

////////////////////////////////////////////////////////////////////////////////
// OnOffItem
////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1_AUTOFACTORY(SdrOnOffItem,SfxBoolItem);

/*N*/ SfxPoolItem* __EXPORT SdrOnOffItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SdrOnOffItem(Which(),GetValue());
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrOnOffItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SdrOnOffItem(Which(),rIn);
/*N*/ }

//STRIP001 XubString __EXPORT SdrOnOffItem::GetValueTextByVal(BOOL bVal) const
//STRIP001 {
//STRIP001  if (bVal) return ImpGetResStr(STR_ItemValON);
//STRIP001  else return ImpGetResStr(STR_ItemValOFF);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrOnOffItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByVal(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrOnOffItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId<SDRATTR_NOTPERSIST_FIRST || nId>SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

/*N*/ TYPEINIT1_AUTOFACTORY(SdrYesNoItem,SfxBoolItem);

/*N*/ SfxPoolItem* __EXPORT SdrYesNoItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SdrYesNoItem(Which(),GetValue());
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrYesNoItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SdrYesNoItem(Which(),rIn);
/*N*/ }

//STRIP001 XubString __EXPORT SdrYesNoItem::GetValueTextByVal(BOOL bVal) const
//STRIP001 {
//STRIP001  if (bVal) return ImpGetResStr(STR_ItemValYES);
//STRIP001  else return ImpGetResStr(STR_ItemValNO);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrYesNoItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByVal(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrYesNoItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId<SDRATTR_NOTPERSIST_FIRST || nId>SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

//------------------------------------------------------------
// class SdrPercentItem
//------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SdrPercentItem,SfxUInt16Item);

/*N*/ SfxPoolItem* __EXPORT SdrPercentItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SdrPercentItem(Which(),GetValue());
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrPercentItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SdrPercentItem(Which(),rIn);
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SdrPercentItem::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreMetric,
//STRIP001     SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText = UniString::CreateFromInt32(GetValue());
//STRIP001  rText += sal_Unicode('%');
//STRIP001
//STRIP001  if(ePres == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrPercentItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId<SDRATTR_NOTPERSIST_FIRST || nId>SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

//------------------------------------------------------------
// class SdrAngleItem
//------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SdrAngleItem,SfxInt32Item);

/*N*/ SfxPoolItem* __EXPORT SdrAngleItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SdrAngleItem(Which(),GetValue());
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrAngleItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SdrAngleItem(Which(),rIn);
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SdrAngleItem::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001     XubString& rText, const IntlWrapper * pIntlWrapper) const
//STRIP001 {
//STRIP001  INT32 nValue(GetValue());
//STRIP001  BOOL bNeg(nValue < 0);
//STRIP001
//STRIP001  if(bNeg)
//STRIP001      nValue = -nValue;
//STRIP001
//STRIP001  rText = UniString::CreateFromInt32(nValue);
//STRIP001
//STRIP001  if(nValue)
//STRIP001  {
//STRIP001      sal_Unicode aUnicodeNull('0');
//STRIP001      xub_StrLen nAnz(2);
//STRIP001
//STRIP001         const IntlWrapper* pMyIntlWrapper = NULL;
//STRIP001         DBG_ASSERT( pIntlWrapper, "SdrAngleItem::GetPresentation: "
//STRIP001             "using default App-IntlWrapper" );
//STRIP001         if(!pIntlWrapper)
//STRIP001             pIntlWrapper = pMyIntlWrapper = new IntlWrapper(
//STRIP001                 ::legacy_binfilters::getLegacyProcessServiceFactory(),
//STRIP001                 Application::GetSettings().GetLanguage() );
//STRIP001
//STRIP001         if(pIntlWrapper->getLocaleData()->isNumLeadingZero())
//STRIP001          nAnz++;
//STRIP001
//STRIP001      while(rText.Len() < nAnz)
//STRIP001          rText.Insert(aUnicodeNull, 0);
//STRIP001
//STRIP001      xub_StrLen nLen = rText.Len();
//STRIP001      BOOL bNull1(rText.GetChar(nLen-1) == aUnicodeNull);
//STRIP001      BOOL bNull2(bNull1 && rText.GetChar(nLen-2) == aUnicodeNull);
//STRIP001
//STRIP001      if(bNull2)
//STRIP001      {
//STRIP001          // keine Nachkommastellen
//STRIP001          rText.Erase(nLen-2);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             sal_Unicode cDec =
//STRIP001                 pIntlWrapper->getLocaleData()->getNumDecimalSep().GetChar(0);
//STRIP001          rText.Insert(cDec, nLen-2);
//STRIP001
//STRIP001          if(bNull1)
//STRIP001              rText.Erase(nLen);
//STRIP001      }
//STRIP001
//STRIP001      if(bNeg)
//STRIP001          rText.Insert(sal_Unicode('-'), 0);
//STRIP001
//STRIP001         if ( pMyIntlWrapper )
//STRIP001         {
//STRIP001             delete pMyIntlWrapper;
//STRIP001             pIntlWrapper = NULL;
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  rText += sal_Unicode(DEGREE_CHAR);
//STRIP001
//STRIP001  if(ePres == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrAngleItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId<SDRATTR_NOTPERSIST_FIRST || nId>SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

//------------------------------------------------------------
// class SdrMetricItem
//------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SdrMetricItem,SfxInt32Item);

/*N*/ SfxPoolItem* __EXPORT SdrMetricItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SdrMetricItem(Which(),GetValue());
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrMetricItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SdrMetricItem(Which(),rIn);
/*N*/ }

//STRIP001 FASTBOOL __EXPORT SdrMetricItem::HasMetrics() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL __EXPORT SdrMetricItem::ScaleMetrics(long nMul, long nDiv)
//STRIP001 {
//STRIP001  if (GetValue()!=0) {
//STRIP001      BigInt aVal(GetValue());
//STRIP001      aVal*=nMul;
//STRIP001      aVal+=nDiv/2; // fuer korrektes Runden
//STRIP001      aVal/=nDiv;
//STRIP001      SetValue(long(aVal));
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrMetricItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  long nValue=GetValue();
//STRIP001  SdrFormatter aFmt((MapUnit)eCoreMetric,(MapUnit)ePresMetric);
//STRIP001  aFmt.TakeStr(nValue,rText);
//STRIP001  String aStr;
//STRIP001  aFmt.TakeUnitStr((MapUnit)ePresMetric,aStr);
//STRIP001  rText+=aStr;
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrMetricItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId<SDRATTR_NOTPERSIST_FIRST || nId>SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ShadowSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrShadowSetItem,SfxSetItem);

/*N*/ SdrShadowSetItem::SdrShadowSetItem(SfxItemSet* pItemSet):
/*N*/   SfxSetItem(SDRATTRSET_SHADOW,pItemSet)
/*N*/ {
/*N*/ }

/*N*/ SdrShadowSetItem::SdrShadowSetItem(SfxItemPool* pItemPool):
/*N*/   SfxSetItem(SDRATTRSET_SHADOW,new SfxItemSet(*pItemPool,SDRATTR_SHADOW_FIRST,SDRATTR_SHADOW_LAST))
/*N*/ {
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrShadowSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrShadowSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrShadowSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_SHADOW_FIRST, SDRATTR_SHADOW_LAST);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrShadowSetItem(pSet);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////
// Items des Legendenobjekts
////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1_AUTOFACTORY(SdrCaptionTypeItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrCaptionTypeItem::Clone(SfxItemPool* pPool) const                { return new SdrCaptionTypeItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrCaptionTypeItem::Create(SvStream& rIn, USHORT nVer) const       { return new SdrCaptionTypeItem(rIn); }

/*N*/ USHORT __EXPORT SdrCaptionTypeItem::GetValueCount() const { return 4; }

//STRIP001 XubString __EXPORT SdrCaptionTypeItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValCAPTIONTYPE1+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrCaptionTypeItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrCaptionEscDirItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrCaptionEscDirItem::Clone(SfxItemPool* pPool) const              { return new SdrCaptionEscDirItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrCaptionEscDirItem::Create(SvStream& rIn, USHORT nVer) const     { return new SdrCaptionEscDirItem(rIn); }

/*N*/ USHORT __EXPORT SdrCaptionEscDirItem::GetValueCount() const { return 3; }

//STRIP001 XubString __EXPORT SdrCaptionEscDirItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValCAPTIONESCHORI+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrCaptionEscDirItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CaptionSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrCaptionSetItem,SfxSetItem);

/*N*/ SfxPoolItem* __EXPORT SdrCaptionSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrCaptionSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrCaptionSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_CAPTION_FIRST, SDRATTR_CAPTION_LAST);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrCaptionSetItem(pSet);
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// OutlinerSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrOutlinerSetItem,SfxSetItem);

/*N*/ SdrOutlinerSetItem::SdrOutlinerSetItem(SfxItemPool* pItemPool):
/*N*/   SfxSetItem(SDRATTRSET_OUTLINER,new SfxItemSet(*pItemPool,EE_ITEMS_START,EE_ITEMS_END))
/*N*/ {
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrOutlinerSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrOutlinerSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrOutlinerSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       EE_ITEMS_START, EE_ITEMS_END);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrOutlinerSetItem(pSet);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////
// MiscItems
////////////////////////////////////////////////////////////////////////////////

// FitToSize
/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextFitToSizeTypeItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrTextFitToSizeTypeItem::Clone(SfxItemPool* pPool) const         { return new SdrTextFitToSizeTypeItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrTextFitToSizeTypeItem::Create(SvStream& rIn, USHORT nVer) const { return new SdrTextFitToSizeTypeItem(rIn); }

/*N*/ USHORT __EXPORT SdrTextFitToSizeTypeItem::GetValueCount() const { return 4; }

//STRIP001 XubString __EXPORT SdrTextFitToSizeTypeItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValFITTOSIZENONE+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrTextFitToSizeTypeItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 int  __EXPORT SdrTextFitToSizeTypeItem::HasBoolValue() const { return TRUE; }

//STRIP001 BOOL __EXPORT SdrTextFitToSizeTypeItem::GetBoolValue() const { return GetValue()!=SDRTEXTFIT_NONE; }

//STRIP001 void __EXPORT SdrTextFitToSizeTypeItem::SetBoolValue(BOOL bVal) { SetValue(bVal ? SDRTEXTFIT_PROPORTIONAL : SDRTEXTFIT_NONE); }

/*N*/ sal_Bool SdrTextFitToSizeTypeItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   drawing::TextFitToSizeType eFS = (drawing::TextFitToSizeType)GetValue();
/*N*/   rVal <<= eFS;
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrTextFitToSizeTypeItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::TextFitToSizeType eFS;
/*N*/   if(!(rVal >>= eFS))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/
/*?*/       eFS = (drawing::TextFitToSizeType) nEnum;
/*N*/   }

/*N*/   SetValue( (SdrFitToSizeType)eFS );

/*N*/   return sal_True;
/*N*/ }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextVertAdjustItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrTextVertAdjustItem::Clone(SfxItemPool* pPool) const            { return new SdrTextVertAdjustItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrTextVertAdjustItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrTextVertAdjustItem(rIn); }

/*N*/ USHORT __EXPORT SdrTextVertAdjustItem::GetValueCount() const { return 5; }

//STRIP001 XubString __EXPORT SdrTextVertAdjustItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValTEXTVADJTOP+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrTextVertAdjustItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

/*N*/ sal_Bool SdrTextVertAdjustItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   rVal <<= (drawing::TextVerticalAdjust)GetValue();
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrTextVertAdjustItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::TextVerticalAdjust eAdj;
/*N*/   if(!(rVal >>= eAdj))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/
/*?*/       eAdj = (drawing::TextVerticalAdjust)nEnum;
/*N*/   }
/*N*/
/*N*/   SetValue( (SdrTextVertAdjust)eAdj );
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextHorzAdjustItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrTextHorzAdjustItem::Clone(SfxItemPool* pPool) const            { return new SdrTextHorzAdjustItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrTextHorzAdjustItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrTextHorzAdjustItem(rIn); }

/*N*/ USHORT __EXPORT SdrTextHorzAdjustItem::GetValueCount() const { return 5; }

/*N*/ XubString __EXPORT SdrTextHorzAdjustItem::GetValueTextByPos(USHORT nPos) const
/*N*/ {DBG_ASSERT(0, "STRIP");XubString a; return a; //STRIP001
//STRIP001  return ImpGetResStr(STR_ItemValTEXTHADJLEFT+nPos);
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SdrTextHorzAdjustItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

/*N*/ sal_Bool SdrTextHorzAdjustItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   rVal <<= (drawing::TextHorizontalAdjust)GetValue();
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrTextHorzAdjustItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::TextHorizontalAdjust eAdj;
/*N*/   if(!(rVal >>= eAdj))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/
/*?*/       eAdj = (drawing::TextHorizontalAdjust)nEnum;
/*N*/   }

/*N*/   SetValue( (SdrTextHorzAdjust)eAdj );

/*N*/   return sal_True;
/*N*/ }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextAniKindItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrTextAniKindItem::Clone(SfxItemPool* pPool) const            { return new SdrTextAniKindItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrTextAniKindItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrTextAniKindItem(rIn); }

/*N*/ USHORT __EXPORT SdrTextAniKindItem::GetValueCount() const { return 5; }

//STRIP001 XubString __EXPORT SdrTextAniKindItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValTEXTANI_NONE+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrTextAniKindItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

/*N*/ sal_Bool SdrTextAniKindItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   rVal <<= (drawing::TextAnimationKind)GetValue();
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrTextAniKindItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::TextAnimationKind eKind;
/*N*/   if(!(rVal >>= eKind))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/       eKind = (drawing::TextAnimationKind)nEnum;
/*N*/   }
/*N*/
/*N*/   SetValue( (SdrTextAniKind)eKind );
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextAniDirectionItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrTextAniDirectionItem::Clone(SfxItemPool* pPool) const            { return new SdrTextAniDirectionItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrTextAniDirectionItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrTextAniDirectionItem(rIn); }

/*N*/ USHORT __EXPORT SdrTextAniDirectionItem::GetValueCount() const { return 4; }

//STRIP001 XubString __EXPORT SdrTextAniDirectionItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValTEXTANI_LEFT+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrTextAniDirectionItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

/*N*/ sal_Bool SdrTextAniDirectionItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   rVal <<= (drawing::TextAnimationDirection)GetValue();
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrTextAniDirectionItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::TextAnimationDirection eDir;
/*N*/   if(!(rVal >>= eDir))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/
/*?*/       eDir = (drawing::TextAnimationDirection)nEnum;
/*N*/   }
/*N*/
/*N*/   SetValue( (SdrTextAniDirection)eDir );
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextAniDelayItem,SfxUInt16Item);
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrTextAniDelayItem::Clone(SfxItemPool* pPool) const            { return new SdrTextAniDelayItem(*this); }
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrTextAniDelayItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrTextAniDelayItem(rIn); }

//STRIP001 SfxItemPresentation __EXPORT SdrTextAniDelayItem::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001     XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText = UniString::CreateFromInt32(GetValue());
//STRIP001  rText += sal_Unicode('m');
//STRIP001  rText += sal_Unicode('s');
//STRIP001
//STRIP001  if(ePres == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrTextAniAmountItem,SfxInt16Item);
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrTextAniAmountItem::Clone(SfxItemPool* pPool) const            { return new SdrTextAniAmountItem(*this); }
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrTextAniAmountItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrTextAniAmountItem(rIn); }

//STRIP001 FASTBOOL __EXPORT SdrTextAniAmountItem::HasMetrics() const
//STRIP001 {
//STRIP001  return GetValue()>0;
//STRIP001 }

//STRIP001 FASTBOOL __EXPORT SdrTextAniAmountItem::ScaleMetrics(long nMul, long nDiv)
//STRIP001 {
//STRIP001  if (GetValue()>0) {
//STRIP001      BigInt aVal(GetValue());
//STRIP001      aVal*=nMul;
//STRIP001      aVal+=nDiv/2; // fuer korrektes Runden
//STRIP001      aVal/=nDiv;
//STRIP001      SetValue(short(aVal));
//STRIP001      return TRUE;
//STRIP001  } else return FALSE;
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrTextAniAmountItem::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001     XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  INT32 nValue(GetValue());
//STRIP001
//STRIP001  if(!nValue)
//STRIP001      nValue = -1L;
//STRIP001
//STRIP001  if(nValue < 0)
//STRIP001  {
//STRIP001      sal_Char aText[] = "pixel";
//STRIP001
//STRIP001      rText = UniString::CreateFromInt32(-nValue);
//STRIP001      rText += UniString(aText, sizeof(aText-1));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SdrFormatter aFmt((MapUnit)eCoreMetric, (MapUnit)ePresMetric);
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      aFmt.TakeStr(nValue, rText);
//STRIP001      aFmt.TakeUnitStr((MapUnit)ePresMetric, aStr);
//STRIP001      rText += aStr;
//STRIP001  }
//STRIP001
//STRIP001  if(ePres == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

/*N*/ TYPEINIT1_AUTOFACTORY( SdrAutoShapeAdjustmentItem, SfxPoolItem );

/*N*/ SdrAutoShapeAdjustmentItem::SdrAutoShapeAdjustmentItem() : SfxPoolItem( SDRATTR_AUTOSHAPE_ADJUSTMENT )
/*N*/ {
/*N*/ }

/*N*/ SdrAutoShapeAdjustmentItem::SdrAutoShapeAdjustmentItem( SvStream& rIn, sal_uInt16 nVersion ):
/*N*/   SfxPoolItem( SDRATTR_AUTOSHAPE_ADJUSTMENT )
/*N*/ {
/*N*/   if ( nVersion )
/*N*/   {
/*N*/       SdrAutoShapeAdjustmentValue aVal;
/*N*/       sal_uInt32 i, nCount;
/*N*/       rIn >> nCount;
/*N*/       for ( i = 0; i < nCount; i++ )
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            rIn >> aVal.nValue;
//STRIP001 /*?*/            SetValue( i, aVal );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ SdrAutoShapeAdjustmentItem::~SdrAutoShapeAdjustmentItem()
/*N*/ {
/*N*/   void* pPtr;
/*N*/   for ( pPtr = aAdjustmentValueList.First(); pPtr; pPtr = aAdjustmentValueList.Next() )
/*?*/       delete (SdrAutoShapeAdjustmentValue*)pPtr;
/*N*/ }

/*N*/ int __EXPORT SdrAutoShapeAdjustmentItem::operator==( const SfxPoolItem& rCmp ) const
/*N*/ {
/*N*/   int bRet = SfxPoolItem::operator==( rCmp );
/*N*/   if ( bRet )
/*N*/   {
/*N*/       bRet = ((SdrAutoShapeAdjustmentItem&)rCmp).GetCount() == GetCount();
/*N*/       if ( bRet )
/*N*/       {
/*N*/           sal_uInt32 i;
/*N*/           for ( i = 0; i < GetCount(); i++ )
/*N*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                if ( ((SdrAutoShapeAdjustmentItem&)rCmp).GetValue( i ).nValue != GetValue( i ).nValue )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    bRet = 0;
//STRIP001 /*?*/                    break;
//STRIP001 /*?*/                }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 SfxItemPresentation __EXPORT SdrAutoShapeAdjustmentItem::GetPresentation(
//STRIP001  SfxItemPresentation ePresentation, SfxMapUnit eCoreMetric,
//STRIP001     SfxMapUnit ePresentationMetric, XubString &rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  sal_uInt32 i, nCount = GetCount();
//STRIP001  rText.Append( UniString::CreateFromInt32( nCount ) );
//STRIP001  for ( i = 0; i < nCount; i++ )
//STRIP001  {
//STRIP001      rText += sal_Unicode( ' ' );
//STRIP001      rText.Append( UniString::CreateFromInt32( GetValue( i ).nValue ) );
//STRIP001  }
//STRIP001  if ( ePresentation == SFX_ITEM_PRESENTATION_COMPLETE )
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName( Which(), aStr );
//STRIP001      aStr += sal_Unicode( ' ' );
//STRIP001      rText.Insert( aStr, 0 );
//STRIP001  }
//STRIP001  return ePresentation;
//STRIP001 }

/*N*/ SfxPoolItem* __EXPORT SdrAutoShapeAdjustmentItem::Create( SvStream& rIn, sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   return new SdrAutoShapeAdjustmentItem( rIn, nItemVersion );
/*N*/ }

/*N*/ SvStream& __EXPORT SdrAutoShapeAdjustmentItem::Store( SvStream& rOut, sal_uInt16 nItemVersion ) const
/*N*/ {
/*N*/   if ( nItemVersion )
/*N*/   {
/*N*/       sal_uInt32 i, nCount = GetCount();
/*N*/       rOut << nCount;
/*N*/       for ( i = 0; i < nCount; i++ )
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001    rOut << GetValue( i ).nValue;
/*N*/   }
/*N*/   return rOut;
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrAutoShapeAdjustmentItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   sal_uInt32 i;
/*N*/   SdrAutoShapeAdjustmentItem* pItem = new SdrAutoShapeAdjustmentItem;
/*N*/   for ( i = 0; i < GetCount(); i++ )
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        const SdrAutoShapeAdjustmentValue& rVal = GetValue( i );
//STRIP001 /*?*/        pItem->SetValue( i, rVal );
/*N*/   }
/*N*/   return pItem;
/*N*/ }

#ifdef SDR_ISPOOLABLE
/*?*/ int __EXPORT SdrAutoShapeAdjustmentItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId < SDRATTR_NOTPERSIST_FIRST || nId > SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

//STRIP001 const SdrAutoShapeAdjustmentValue& SdrAutoShapeAdjustmentItem::GetValue( sal_uInt32 nIndex ) const
//STRIP001 {
//STRIP001 #ifdef DBG_UTIL
//STRIP001  if ( aAdjustmentValueList.Count() <= nIndex )
//STRIP001      DBG_ERROR( "SdrAutoShapeAdjustemntItem::GetValue - nIndex out of range (SJ)" );
//STRIP001 #endif
//STRIP001  return *(SdrAutoShapeAdjustmentValue*)aAdjustmentValueList.GetObject( nIndex );
//STRIP001 }

//STRIP001 void SdrAutoShapeAdjustmentItem::SetValue( sal_uInt32 nIndex, const SdrAutoShapeAdjustmentValue& rVal )
//STRIP001 {
//STRIP001  sal_uInt32 i;
//STRIP001  for ( i = GetCount(); i <= nIndex; i++ )
//STRIP001  {
//STRIP001      SdrAutoShapeAdjustmentValue* pItem = new SdrAutoShapeAdjustmentValue;
//STRIP001      aAdjustmentValueList.Insert( pItem, LIST_APPEND );
//STRIP001  }
//STRIP001  SdrAutoShapeAdjustmentValue& rValue = *(SdrAutoShapeAdjustmentValue*)aAdjustmentValueList.GetObject( nIndex );
//STRIP001  rValue.nValue = rVal.nValue;
//STRIP001 }

/*N*/ sal_uInt16 SdrAutoShapeAdjustmentItem::GetVersion( sal_uInt16 nFileFormatVersion ) const
/*N*/ {
/*N*/   return 1;
/*N*/ }

//STRIP001 sal_Bool SdrAutoShapeAdjustmentItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  sal_uInt32 i, nCount = GetCount();
//STRIP001  uno::Sequence< sal_Int32 > aSequence( nCount );
//STRIP001  if ( nCount )
//STRIP001  {
//STRIP001      sal_Int32* pPtr = aSequence.getArray();
//STRIP001      for ( i = 0; i < nCount; i++ )
//STRIP001          *pPtr++ = GetValue( i ).nValue;
//STRIP001  }
//STRIP001  rVal <<= aSequence;
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SdrAutoShapeAdjustmentItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  uno::Sequence< sal_Int32 > aSequence;
//STRIP001  if( !( rVal >>= aSequence ) )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  void* pPtr;
//STRIP001  for ( pPtr = aAdjustmentValueList.First(); pPtr; pPtr = aAdjustmentValueList.Next() )
//STRIP001      delete (SdrAutoShapeAdjustmentValue*)pPtr;
//STRIP001
//STRIP001  sal_uInt32 i, nCount = aSequence.getLength();
//STRIP001  if ( nCount )
//STRIP001  {
//STRIP001      const sal_Int32* pPtr = aSequence.getConstArray();
//STRIP001      for ( i = 0; i < nCount; i++ )
//STRIP001      {
//STRIP001          SdrAutoShapeAdjustmentValue* pItem = new SdrAutoShapeAdjustmentValue;
//STRIP001          pItem->nValue = *pPtr++;
//STRIP001          aAdjustmentValueList.Insert( pItem, LIST_APPEND );
//STRIP001      }
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrMiscSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrMiscSetItem,SfxSetItem);

/*N*/ SfxPoolItem* __EXPORT SdrMiscSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrMiscSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrMiscSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_MISC_FIRST, SDRATTR_MISC_LAST);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrMiscSetItem(pSet);
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Edge
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// EdgeKind
/*N*/ TYPEINIT1_AUTOFACTORY(SdrEdgeKindItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrEdgeKindItem::Clone(SfxItemPool* pPool) const            { return new SdrEdgeKindItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrEdgeKindItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrEdgeKindItem(rIn); }

/*N*/ USHORT __EXPORT SdrEdgeKindItem::GetValueCount() const { return 4; }

//STRIP001 XubString __EXPORT SdrEdgeKindItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValEDGE_ORTHOLINES+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrEdgeKindItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

/*N*/ sal_Bool SdrEdgeKindItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   drawing::ConnectorType eCT = drawing::ConnectorType_STANDARD;
/*N*/
/*N*/   switch( GetValue() )
/*N*/   {
/*N*/       case SDREDGE_ORTHOLINES :   eCT = drawing::ConnectorType_STANDARD; break;
/*N*/       case SDREDGE_THREELINES :   eCT = drawing::ConnectorType_LINES; break;
/*N*/       case SDREDGE_ONELINE :      eCT = drawing::ConnectorType_LINE;  break;
/*N*/       case SDREDGE_BEZIER :       eCT = drawing::ConnectorType_CURVE; break;
/*N*/       case SDREDGE_ARC :          eCT = drawing::ConnectorType_CURVE; break;
/*N*/       default:
/*N*/           DBG_ERROR( "SdrEdgeKindItem::QueryValue : unknown enum" );
/*N*/   }
/*N*/
/*N*/   rVal <<= eCT;
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrEdgeKindItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::ConnectorType eCT;
/*N*/   if(!(rVal >>= eCT))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/
/*?*/       eCT = (drawing::ConnectorType)nEnum;
/*N*/   }
/*N*/
/*N*/   SdrEdgeKind eEK = SDREDGE_ORTHOLINES;
/*N*/   switch( eCT )
/*N*/   {
/*N*/       case drawing::ConnectorType_STANDARD :  eEK = SDREDGE_ORTHOLINES;   break;
/*N*/       case drawing::ConnectorType_CURVE :     eEK = SDREDGE_BEZIER;       break;
/*N*/       case drawing::ConnectorType_LINE :       eEK = SDREDGE_ONELINE;     break;
/*N*/       case drawing::ConnectorType_LINES :      eEK = SDREDGE_THREELINES;   break;
/*N*/       default:
/*N*/           DBG_ERROR( "SdrEdgeKindItem::PuValue : unknown enum" );
/*N*/   }
/*N*/   SetValue( eEK );
/*N*/
/*N*/   return sal_True;
/*N*/ }

//STRIP001 sal_Bool SdrEdgeNode1HorzDistItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SdrEdgeNode1HorzDistItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeNode1VertDistItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeNode1VertDistItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeNode2HorzDistItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeNode2HorzDistItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeNode2VertDistItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeNode2VertDistItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeLine1DeltaItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeLine1DeltaItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeLine2DeltaItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeLine2DeltaItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeLine3DeltaItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 BOOL SdrEdgeLine3DeltaItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nValue;
//STRIP001  if(!(rVal >>= nValue))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( nValue );
//STRIP001  return sal_True;
//STRIP001 }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrEdgeSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrEdgeSetItem,SfxSetItem);

/*N*/ SfxPoolItem* __EXPORT SdrEdgeSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrEdgeSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrEdgeSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_EDGE_FIRST, SDRATTR_EDGE_LAST);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrEdgeSetItem(pSet);
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Measure
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// MeasureKind
/*N*/ TYPEINIT1_AUTOFACTORY(SdrMeasureKindItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrMeasureKindItem::Clone(SfxItemPool* pPool) const            { return new SdrMeasureKindItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrMeasureKindItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrMeasureKindItem(rIn); }

/*N*/ USHORT __EXPORT SdrMeasureKindItem::GetValueCount() const { return 2; }

//STRIP001 XubString __EXPORT SdrMeasureKindItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValMEASURE_STD+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrMeasureKindItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureKindItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (drawing::MeasureKind)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureKindItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  drawing::MeasureKind eKind;
//STRIP001  if(!(rVal >>= eKind))
//STRIP001  {
//STRIP001      sal_Int32 nEnum;
//STRIP001      if(!(rVal >>= nEnum))
//STRIP001          return sal_False;
//STRIP001
//STRIP001      eKind = (drawing::MeasureKind)nEnum;
//STRIP001  }
//STRIP001
//STRIP001  SetValue( (SdrMeasureKind)eKind );
//STRIP001  return sal_True;
//STRIP001 }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrMeasureTextHPosItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrMeasureTextHPosItem::Clone(SfxItemPool* pPool) const            { return new SdrMeasureTextHPosItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrMeasureTextHPosItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrMeasureTextHPosItem(rIn); }

/*N*/ USHORT __EXPORT SdrMeasureTextHPosItem::GetValueCount() const { return 4; }

//STRIP001 XubString __EXPORT SdrMeasureTextHPosItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValMEASURE_TEXTHAUTO+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrMeasureTextHPosItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureTextHPosItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (drawing::MeasureTextHorzPos)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureTextHPosItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  drawing::MeasureTextHorzPos ePos;
//STRIP001  if(!(rVal >>= ePos))
//STRIP001  {
//STRIP001      sal_Int32 nEnum;
//STRIP001      if(!(rVal >>= nEnum))
//STRIP001          return sal_False;
//STRIP001
//STRIP001      ePos = (drawing::MeasureTextHorzPos)nEnum;
//STRIP001  }
//STRIP001
//STRIP001  SetValue( (SdrMeasureTextHPos)ePos );
//STRIP001  return sal_True;
//STRIP001 }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrMeasureTextVPosItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrMeasureTextVPosItem::Clone(SfxItemPool* pPool) const            { return new SdrMeasureTextVPosItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrMeasureTextVPosItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrMeasureTextVPosItem(rIn); }

/*N*/ USHORT __EXPORT SdrMeasureTextVPosItem::GetValueCount() const { return 5; }

//STRIP001 XubString __EXPORT SdrMeasureTextVPosItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValMEASURE_TEXTVAUTO+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrMeasureTextVPosItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureTextVPosItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (drawing::MeasureTextVertPos)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureTextVPosItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  drawing::MeasureTextVertPos ePos;
//STRIP001  if(!(rVal >>= ePos))
//STRIP001  {
//STRIP001      sal_Int32 nEnum;
//STRIP001      if(!(rVal >>= nEnum))
//STRIP001          return sal_False;
//STRIP001
//STRIP001      ePos = (drawing::MeasureTextVertPos)nEnum;
//STRIP001  }
//STRIP001
//STRIP001  SetValue( (SdrMeasureTextHPos)ePos );
//STRIP001  return sal_True;
//STRIP001 }

/*N*/ TYPEINIT1_AUTOFACTORY(SdrMeasureUnitItem,SfxEnumItem);

/*N*/ SfxPoolItem* __EXPORT SdrMeasureUnitItem::Clone(SfxItemPool* pPool) const            { return new SdrMeasureUnitItem(*this); }

/*N*/ SfxPoolItem* __EXPORT SdrMeasureUnitItem::Create(SvStream& rIn, USHORT nVer) const   { return new SdrMeasureUnitItem(rIn); }

/*N*/ USHORT __EXPORT SdrMeasureUnitItem::GetValueCount() const { return 14; }

//STRIP001 XubString __EXPORT SdrMeasureUnitItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  XubString aRetval;
//STRIP001
//STRIP001  if((FieldUnit)nPos == FUNIT_NONE)
//STRIP001  {
//STRIP001      sal_Char aText[] = "default";
//STRIP001      aRetval += UniString(aText, sizeof(aText-1));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SdrFormatter::TakeUnitStr((FieldUnit)nPos, aRetval);
//STRIP001  }
//STRIP001
//STRIP001  return aRetval;
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrMeasureUnitItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureUnitItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (sal_Int32)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SdrMeasureUnitItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Int32 nMeasure;
//STRIP001  if(!(rVal >>= nMeasure))
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SetValue( (FieldUnit)nMeasure );
//STRIP001  return sal_True;
//STRIP001 }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrMeasureSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrMeasureSetItem,SfxSetItem);

/*N*/ SfxPoolItem* __EXPORT SdrMeasureSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrMeasureSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrMeasureSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_MEASURE_FIRST, SDRATTR_MEASURE_LAST);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrMeasureSetItem(pSet);
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Circ
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// CircKind
/*N*/ TYPEINIT1_AUTOFACTORY(SdrCircKindItem,SfxEnumItem);
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrCircKindItem::Clone(SfxItemPool* pPool) const          { return new SdrCircKindItem(*this); }
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrCircKindItem::Create(SvStream& rIn, USHORT nVer) const { return new SdrCircKindItem(rIn); }

/*N*/ USHORT __EXPORT SdrCircKindItem::GetValueCount() const { return 4; }

//STRIP001 XubString __EXPORT SdrCircKindItem::GetValueTextByPos(USHORT nPos) const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_ItemValCIRC_FULL+nPos);
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrCircKindItem::GetPresentation(SfxItemPresentation ePres,
//STRIP001                       SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText=GetValueTextByPos(GetValue());
//STRIP001  if (ePres==SFX_ITEM_PRESENTATION_COMPLETE) {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 sal_Bool SdrCircKindItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  rVal <<= (drawing::CircleKind)GetValue();
//STRIP001  return sal_True;
//STRIP001 }

/*N*/ sal_Bool SdrCircKindItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   drawing::CircleKind eKind;
/*N*/   if(!(rVal >>= eKind))
/*N*/   {
/*?*/       sal_Int32 nEnum;
/*?*/       if(!(rVal >>= nEnum))
/*?*/           return sal_False;
/*?*/
/*?*/       eKind = (drawing::CircleKind)nEnum;
/*N*/   }
/*N*/
/*N*/   SetValue( (SdrCircKind)eKind );
/*N*/   return sal_True;
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrCircSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(SdrCircSetItem,SfxSetItem);

/*N*/ SfxPoolItem* __EXPORT SdrCircSetItem::Clone(SfxItemPool* pToPool) const
/*N*/ {
/*N*/   return new SdrCircSetItem(*this,pToPool);
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrCircSetItem::Create(SvStream& rStream, USHORT nVersion) const
/*N*/ {
/*N*/   SfxItemSet *pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_CIRC_FIRST, SDRATTR_CIRC_LAST);
/*N*/   pSet->Load(rStream);
/*N*/   return new SdrCircSetItem(pSet);
/*N*/ }

//------------------------------------------------------------
// class SdrSignedPercentItem
//------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY( SdrSignedPercentItem, SfxInt16Item );


//STRIP001 SfxPoolItem* __EXPORT SdrSignedPercentItem::Clone(SfxItemPool* pPool) const
//STRIP001 {
//STRIP001  return new SdrSignedPercentItem( Which(), GetValue() );
//STRIP001 }

//STRIP001 SfxPoolItem* __EXPORT SdrSignedPercentItem::Create( SvStream& rIn, USHORT nVer ) const
//STRIP001 {
//STRIP001  return new SdrSignedPercentItem( Which(), rIn );
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrSignedPercentItem::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001     XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText = UniString::CreateFromInt32(GetValue());
//STRIP001  rText += sal_Unicode('%');
//STRIP001
//STRIP001  if(ePres == SFX_ITEM_PRESENTATION_COMPLETE)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName(Which(), aStr);
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert(aStr, 0);
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

#ifdef SDR_ISPOOLABLE

/*?*/ int __EXPORT SdrSignedPercentItem::IsPoolable() const
/*?*/ {
/*?*/   USHORT nId=Which();
/*?*/   return nId < SDRATTR_NOTPERSIST_FIRST || nId > SDRATTR_NOTPERSIST_LAST;
/*?*/ }
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafSetItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafSetItem,SfxSetItem );

/*N*/ SfxPoolItem* __EXPORT SdrGrafSetItem::Clone( SfxItemPool* pToPool ) const
/*N*/ {
/*N*/   return new SdrGrafSetItem( *this, pToPool );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafSetItem::Create( SvStream& rStream, USHORT nVersion ) const
/*N*/ {
/*N*/   SfxItemSet* pSet = new SfxItemSet(*GetItemSet().GetPool(),
/*N*/       SDRATTR_GRAF_FIRST, SDRATTR_GRAF_LAST );
/*N*/   pSet->Load( rStream );
/*N*/   return new SdrGrafSetItem( pSet );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafRedItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafRedItem, SdrSignedPercentItem );

/*N*/ SfxPoolItem* __EXPORT SdrGrafRedItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafRedItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafRedItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafRedItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafGreenItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafGreenItem, SdrSignedPercentItem );

/*N*/ SfxPoolItem* __EXPORT SdrGrafGreenItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafGreenItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafGreenItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafGreenItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafBlueItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafBlueItem, SdrSignedPercentItem );

/*N*/ SfxPoolItem* __EXPORT SdrGrafBlueItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafBlueItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafBlueItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafBlueItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafLuminanceItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafLuminanceItem, SdrSignedPercentItem );
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrGrafLuminanceItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafLuminanceItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafLuminanceItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafLuminanceItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafContrastItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafContrastItem, SdrSignedPercentItem );
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrGrafContrastItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafContrastItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafContrastItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafContrastItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafGamma100Item
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafGamma100Item, SfxUInt32Item );

/*N*/ SfxPoolItem* __EXPORT SdrGrafGamma100Item::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafGamma100Item( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafGamma100Item::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafGamma100Item( rIn );
/*N*/ }

/*N*/ sal_Bool SdrGrafGamma100Item::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   rVal <<= ((double)GetValue()) / 100.0;
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SdrGrafGamma100Item::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   double nGamma;
/*N*/   if(!(rVal >>= nGamma))
/*N*/       return sal_False;
/*N*/
/*N*/   SetValue( (UINT32)(nGamma * 100.0  ) );
/*N*/   return sal_True;
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafInvertItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafInvertItem, SdrOnOffItem );

/*N*/ SfxPoolItem* __EXPORT SdrGrafInvertItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafInvertItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafInvertItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafInvertItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafTransparenceItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafTransparenceItem, SdrPercentItem );
/*N*/
/*N*/ SfxPoolItem* __EXPORT SdrGrafTransparenceItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafTransparenceItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafTransparenceItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafTransparenceItem( rIn );
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafModeItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafModeItem, SfxEnumItem );

/*N*/ SfxPoolItem* __EXPORT SdrGrafModeItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SdrGrafModeItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* __EXPORT SdrGrafModeItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return new SdrGrafModeItem( rIn );
/*N*/ }

/*N*/ USHORT __EXPORT SdrGrafModeItem::GetValueCount() const
/*N*/ {
/*N*/   return 4;
/*N*/ }

//STRIP001 XubString __EXPORT SdrGrafModeItem::GetValueTextByPos(UINT16 nPos) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001
//STRIP001  switch(nPos)
//STRIP001  {
//STRIP001      case 1:
//STRIP001      {
//STRIP001          sal_Char aTextGreys[] = "Greys";
//STRIP001          aStr += UniString(aTextGreys, sizeof(aTextGreys-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case 2:
//STRIP001      {
//STRIP001          sal_Char aTextBlackWhite[] = "Black/White";
//STRIP001          aStr += UniString(aTextBlackWhite, sizeof(aTextBlackWhite-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case 3:
//STRIP001      {
//STRIP001          sal_Char aTextWatermark[] = "Watermark";
//STRIP001          aStr += UniString(aTextWatermark, sizeof(aTextWatermark-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      default:
//STRIP001      {
//STRIP001          sal_Char aTextStandard[] = "Standard";
//STRIP001          aStr += UniString(aTextStandard, sizeof(aTextStandard-1));
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 SfxItemPresentation __EXPORT SdrGrafModeItem::GetPresentation( SfxItemPresentation ePres,
//STRIP001                                                             SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001                                                                XubString& rText, const IntlWrapper *) const
//STRIP001 {
//STRIP001  rText = GetValueTextByPos( GetValue() );
//STRIP001
//STRIP001  if( ePres == SFX_ITEM_PRESENTATION_COMPLETE )
//STRIP001  {
//STRIP001      String aStr;
//STRIP001
//STRIP001      SdrItemPool::TakeItemName( Which(), aStr );
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      rText.Insert( aStr, 0 );
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SdrGrafCropItem
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1( SdrGrafCropItem, SvxGrfCrop );

/*N*/ SfxPoolItem* SdrGrafCropItem::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/   return new SdrGrafCropItem( *this );
/*N*/ }
/*N*/
/*N*/ SfxPoolItem* SdrGrafCropItem::Create( SvStream& rIn, USHORT nVer ) const
/*N*/ {
/*N*/   return( ( 0 == nVer ) ? Clone( NULL ) : SvxGrfCrop::Create( rIn, nVer ) );
/*N*/ }
/*N*/
/*N*/ USHORT SdrGrafCropItem::GetVersion( USHORT nFileVersion ) const
/*N*/ {
/*N*/   // GRFCROP_VERSION_MOVETOSVX is 1
/*N*/   return GRFCROP_VERSION_MOVETOSVX;
/*N*/ }
