/*************************************************************************
 *
 *  $RCSfile: sw_usrpref.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:36:54 $
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


#pragma hdrstop

// auto strip #ifndef _STREAM_HXX //autogen
// auto strip #include <tools/stream.hxx>
// auto strip #endif


// auto strip #include "swtypes.hxx"
// auto strip #include "hintids.hxx"
// auto strip #include "uitool.hxx"
#include "usrpref.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "crstate.hxx"
// auto strip #ifndef _OFA_OSPLCFG_HXX
// auto strip #include <bf_offmgr/osplcfg.hxx>
// auto strip #endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif

// auto strip #ifndef _LINGUISTIC_LNGPROPS_HHX_
// auto strip #include <bf_linguistic/lngprops.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
// auto strip #include <com/sun/star/uno/Sequence.hxx>
// auto strip #endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

/*N*/ #define C2U(cChar) OUString::createFromAscii(cChar)
/*N*/ #define C2S(cChar) String::CreateFromAscii(cChar)

//STRIP001 void SwMasterUsrPref::SetUsrPref(const SwViewOption &rCopy)
//STRIP001 {
//STRIP001  *((SwViewOption*)this) = rCopy;
//STRIP001 }

/*N*/ SwMasterUsrPref::SwMasterUsrPref(BOOL bWeb) :
/*N*/   aContentConfig(bWeb, *this),
/*N*/   aLayoutConfig(bWeb, *this),
/*N*/   aGridConfig(bWeb, *this),
/*N*/   aCursorConfig(*this),
/*N*/   pWebColorConfig(bWeb ? new SwWebColorConfig(*this) : 0),
/*N*/   nFldUpdateFlags(0),
/*N*/     nLinkUpdateMode(0),
/*N*/     bIsHScrollMetricSet(sal_False),
/*N*/     bIsVScrollMetricSet(sal_False),
/*N*/     nDefTab( MM50 * 4 )
/*N*/ {
/*N*/     MeasurementSystem eSystem = GetAppLocaleData().getMeasurementSystemEnum();
/*N*/     eUserMetric = MEASURE_METRIC == eSystem ? FUNIT_CM : FUNIT_INCH;
/*N*/     eHScrollMetric = eUserMetric;
/*N*/     eVScrollMetric = eUserMetric;
/*N*/
/*N*/     aContentConfig.Load();
/*N*/   aLayoutConfig.Load();
/*N*/   aGridConfig.Load();
/*N*/   aCursorConfig.Load();
/*N*/   if(pWebColorConfig)
/*N*/       pWebColorConfig->Load();
/*N*/ }
/* -----------------------------13.02.01 09:48--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwMasterUsrPref::~SwMasterUsrPref()
/*N*/ {
/*N*/   delete pWebColorConfig;
/*N*/ }
/*-- 28.09.00 09:55:32---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ Sequence<OUString> SwContentViewConfig::GetPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "Display/GraphicObject",                    //  0
/*N*/       "Display/Table",                            //  1
/*N*/       "Display/DrawingControl",                   //  2
/*N*/       "Display/FieldCode",                        //  3
/*N*/       "Display/Note",                             //  4
/*N*/         "Display/PreventTips",                      //  5
/*N*/         "NonprintingCharacter/MetaCharacters",     //   6
/*N*/         "NonprintingCharacter/ParagraphEnd",        //  7
/*N*/         "NonprintingCharacter/OptionalHyphen",      //  8
/*N*/         "NonprintingCharacter/Space",               //  9
/*N*/         "NonprintingCharacter/Break",               // 10
/*N*/         "NonprintingCharacter/ProtectedSpace",      // 11
/*N*/             "NonprintingCharacter/Tab",             // 12 //not in Writer/Web
/*N*/             "NonprintingCharacter/HiddenText",      // 13
/*N*/             "NonprintingCharacter/HiddenParagraph", // 14
/*N*/             "Update/Link",                          // 15
/*N*/             "Update/Field",                         // 16
/*N*/             "Update/Chart"                          // 17
/*N*/
/*N*/
/*N*/   };
/*N*/     const int nCount = bWeb ? 12 : 18;
/*N*/   Sequence<OUString> aNames(nCount);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < nCount; i++)
/*N*/   {
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/*-- 28.09.00 09:55:33---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwContentViewConfig::SwContentViewConfig(BOOL bIsWeb, SwMasterUsrPref& rPar) :
/*N*/     ConfigItem(bIsWeb ? C2U("Office.WriterWeb/Content") :  C2U("Office.Writer/Content"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   rParent(rPar),
/*N*/   bWeb(bIsWeb)
/*N*/ {
/*N*/ }
/*-- 28.09.00 09:55:33---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwContentViewConfig::~SwContentViewConfig()
/*N*/ {
/*N*/ }
/*-- 28.09.00 09:55:33---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void SwContentViewConfig::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      sal_Bool bVal = FALSE;
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0: bVal = rParent.IsGraphic();    break;// "Display/GraphicObject",
//STRIP001          case  1: bVal = rParent.IsTable();  break;// "Display/Table",
//STRIP001          case  2: bVal = rParent.IsDraw();       break;// "Display/DrawingControl",
//STRIP001          case  3: bVal = rParent.IsFldName();    break;// "Display/FieldCode",
//STRIP001          case  4: bVal = rParent.IsPostIts();    break;// "Display/Note",
//STRIP001             case  5: bVal = rParent.IsPreventTips(); break; // "Display/PreventTips"
//STRIP001             case  6: bVal = rParent.IsViewMetaChars(); break; //"NonprintingCharacter/MetaCharacters"
//STRIP001             case  7: bVal = rParent.IsParagraph(); break;// "NonprintingCharacter/ParagraphEnd",
//STRIP001             case  8: bVal = rParent.IsSoftHyph(); break;// "NonprintingCharacter/OptionalHyphen",
//STRIP001             case  9: bVal = rParent.IsBlank();  break;// "NonprintingCharacter/Space",
//STRIP001             case 10: bVal = rParent.IsLineBreak();break;// "NonprintingCharacter/Break",
//STRIP001             case 11: bVal = rParent.IsHardBlank(); break;// "NonprintingCharacter/ProtectedSpace",
//STRIP001             case 12: bVal = rParent.IsTab();        break;// "NonprintingCharacter/Tab",
//STRIP001             case 13: bVal = rParent.IsHidden(); break;// "NonprintingCharacter/HiddenText",
//STRIP001             case 14: bVal = rParent.IsShowHiddenPara(); break;// "NonprintingCharacter/HiddenParagraph",
//STRIP001             case 15: pValues[nProp] <<= rParent.GetUpdateLinkMode();    break;// "Update/Link",
//STRIP001             case 16: bVal = rParent.IsUpdateFields(); break;// "Update/Field",
//STRIP001             case 17: bVal = rParent.IsUpdateCharts(); break;// "Update/Chart"
//STRIP001         }
//STRIP001         if(nProp != 15)
//STRIP001          pValues[nProp].setValue(&bVal, ::getBooleanCppuType());
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/*-- 28.09.00 09:55:34---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ void SwContentViewConfig::Load()
/*N*/ {
/*N*/   Sequence<OUString> aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/                 sal_Bool bSet = nProp != 15 ? *(sal_Bool*)pValues[nProp].getValue() : sal_False;
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case  0: rParent.SetGraphic(bSet);  break;// "Display/GraphicObject",
/*N*/                   case  1: rParent.SetTable(bSet);    break;// "Display/Table",
/*N*/                   case  2: rParent.SetDraw(bSet);     break;// "Display/DrawingControl",
/*N*/                   case  3: rParent.SetFldName(bSet);  break;// "Display/FieldCode",
/*N*/                   case  4: rParent.SetPostIts(bSet);  break;// "Display/Note",
/*N*/                     case  5: rParent.SetPreventTips(bSet);  break;// "Display/PreventTips",
/*N*/                     case  6: rParent.SetViewMetaChars(bSet); break; //"NonprintingCharacter/MetaCharacters"
/*N*/                     case  7: rParent.SetParagraph(bSet); break;// "NonprintingCharacter/ParagraphEnd",
/*N*/                     case  8: rParent.SetSoftHyph(bSet); break;// "NonprintingCharacter/OptionalHyphen",
/*N*/                     case  9: rParent.SetBlank(bSet);    break;// "NonprintingCharacter/Space",
/*N*/                     case 10: rParent.SetLineBreak(bSet);break;// "NonprintingCharacter/Break",
/*N*/                     case 11: rParent.SetHardBlank(bSet); break;// "NonprintingCharacter/ProtectedSpace",
/*N*/                     case 12: rParent.SetTab(bSet);      break;// "NonprintingCharacter/Tab",
/*N*/                     case 13: rParent.SetHidden(bSet);   break;// "NonprintingCharacter/HiddenText",
/*N*/                     case 14: rParent.SetShowHiddenPara(bSet); break;// "NonprintingCharacter/HiddenParagraph",
/*N*/                     case 15:
/*N*/                     {
/*N*/                       sal_Int32 nSet; pValues[nProp] >>= nSet;
/*N*/                         rParent.SetUpdateLinkMode(nSet, TRUE);
/*N*/                   }
/*N*/                   break;// "Update/Link",
/*N*/                     case 16: rParent.SetUpdateFields(bSet, TRUE); break;// "Update/Field",
/*N*/                     case 17: rParent.SetUpdateCharts(bSet, TRUE); break;// "Update/Chart"
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*-- 28.09.00 09:55:34---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ Sequence<OUString> SwLayoutViewConfig::GetPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/         "Line/Guide",                       // 0
/*N*/         "Line/SimpleControlPoint",          // 1
/*N*/         "Line/LargeControlPoint",           // 2
/*N*/         "Window/HorizontalScroll",          // 3
/*N*/         "Window/VerticalScroll",            // 4
/*M*/         "Window/ShowRulers",                // 5
/*M*/         "Window/HorizontalRuler",           // 6
/*M*/         "Window/VerticalRuler",             // 7
/*M*/         "Window/HorizontalRulerUnit",       // 8
/*M*/         "Window/VerticalRulerUnit",         // 9
/*M*/         "Window/SmoothScroll",              //10
/*M*/         "Zoom/Value",                       //11
/*M*/         "Zoom/Type",                        //12
/*M*/         "Other/MeasureUnit",                //13
/*M*/         "Other/TabStop",                    //14
/*M*/         "Window/IsVerticalRulerRight"       //15
/*M*/     };
/*M*/     const int nCount = bWeb ? 14 : 16;
/*N*/     Sequence<OUString> aNames(nCount);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < nCount; i++)
/*N*/   {
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/*-- 28.09.00 09:55:34---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwLayoutViewConfig::SwLayoutViewConfig(BOOL bIsWeb, SwMasterUsrPref& rPar) :
/*N*/     ConfigItem(bIsWeb ? C2U("Office.WriterWeb/Layout") :  C2U("Office.Writer/Layout"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   rParent(rPar),
/*N*/   bWeb(bIsWeb)
/*N*/ {
/*N*/ }
/*-- 28.09.00 09:55:35---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwLayoutViewConfig::~SwLayoutViewConfig()
/*N*/ {
/*N*/ }
/*-- 28.09.00 09:55:36---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void SwLayoutViewConfig::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      sal_Bool bSet;
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001             case  0: bSet = rParent.IsCrossHair(); break;// "Line/Guide",
//STRIP001             case  1: bSet = rParent.IsSolidMarkHdl(); break;// "Line/SimpleControlPoint",
//STRIP001             case  2: bSet = rParent.IsBigMarkHdl(); break;// "Line/LargeControlPoint",
//STRIP001             case  3: bSet = rParent.IsViewHScrollBar(); break;// "Window/HorizontalScroll",
//STRIP001             case  4: bSet = rParent.IsViewVScrollBar(); break;// "Window/VerticalScroll",
//STRIP001             case  5: bSet = rParent.IsViewAnyRuler(); break; // "Window/ShowRulers"
//STRIP001             // #i14593# use IsView*Ruler(TRUE) instead of IsView*Ruler()
//STRIP001             // this preserves the single ruler states even if "Window/ShowRulers" is off
//STRIP001             case  6: bSet = rParent.IsViewHRuler(TRUE); break;// "Window/HorizontalRuler",
//STRIP001             case  7: bSet = rParent.IsViewVRuler(TRUE); break;// "Window/VerticalRuler",
//STRIP001             case  8:
//STRIP001                 if(rParent.bIsHScrollMetricSet)
//STRIP001                     pValues[nProp] <<= (sal_Int32)rParent.eHScrollMetric; // "Window/HorizontalRulerUnit"
//STRIP001             break;
//STRIP001             case  9:
//STRIP001                 if(rParent.bIsVScrollMetricSet)
//STRIP001                     pValues[nProp] <<= (sal_Int32)rParent.eVScrollMetric; // "Window/VerticalRulerUnit"
//STRIP001             break;
//STRIP001             case 10: bSet = rParent.IsSmoothScroll(); break;// "Window/SmoothScroll",
//STRIP001             case 11: pValues[nProp] <<= (sal_Int32)rParent.GetZoom(); break;// "Zoom/Value",
//STRIP001             case 12: pValues[nProp] <<= (sal_Int32)rParent.GetZoomType(); break;// "Zoom/Type",
//STRIP001             case 13: pValues[nProp] <<= (sal_Int32)rParent.GetMetric(); break;// "Other/MeasureUnit",
//STRIP001             case 14: pValues[nProp] <<= TWIP_TO_MM100(rParent.GetDefTab()); break;// "Other/TabStop",
//STRIP001             case 15: bSet = rParent.IsVRulerRight(); break;// "Window/IsVerticalRulerRight",
//STRIP001         }
//STRIP001         if(nProp < 8 || nProp == 10)
//STRIP001          pValues[nProp].setValue(&bSet, ::getBooleanCppuType());
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/*-- 28.09.00 09:55:36---------------------------------------------------

  -----------------------------------------------------------------------*/
/*M*/ void SwLayoutViewConfig::Load()
/*M*/ {
/*M*/   Sequence<OUString> aNames = GetPropertyNames();
/*M*/   Sequence<Any> aValues = GetProperties(aNames);
/*M*/   const Any* pValues = aValues.getConstArray();
/*M*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*M*/   if(aValues.getLength() == aNames.getLength())
/*M*/   {
/*M*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*M*/       {
/*M*/           if(pValues[nProp].hasValue())
/*M*/           {
/*M*/                 sal_Bool bSet = nProp < 8 || nProp == 10 ? *(sal_Bool*)pValues[nProp].getValue() : sal_False;
/*M*/                 switch(nProp)
/*M*/               {
/*M*/                     case  0: rParent.SetCrossHair(bSet); break;// "Line/Guide",
/*M*/                     case  1: rParent.SetSolidMarkHdl(bSet); break;// "Line/SimpleControlPoint",
/*M*/                     case  2: rParent.SetBigMarkHdl(bSet); break;// "Line/LargeControlPoint",
/*M*/                     case  3: rParent.SetViewHScrollBar(bSet); break;// "Window/HorizontalScroll",
/*M*/                     case  4: rParent.SetViewVScrollBar(bSet); break;// "Window/VerticalScroll",
/*M*/                     case  5: rParent.SetViewAnyRuler(bSet);break; // "Window/ShowRulers"
/*M*/                     case  6: rParent.SetViewHRuler(bSet); break;// "Window/HorizontalRuler",
/*M*/                     case  7: rParent.SetViewVRuler(bSet); break;// "Window/VerticalRuler",
/*M*/                     case  8:
/*M*/                     {
/*M*/                         rParent.bIsHScrollMetricSet = sal_True;
/*M*/                         sal_Int32 nUnit; pValues[nProp] >>= nUnit;
/*M*/                         rParent.eHScrollMetric = ((FieldUnit)nUnit);  // "Window/HorizontalRulerUnit"
/*M*/                     }
/*M*/                     break;
/*M*/                     case  9:
/*M*/                     {
/*M*/                         rParent.bIsVScrollMetricSet = sal_True;
/*M*/                         sal_Int32 nUnit; pValues[nProp] >>= nUnit;
/*M*/                         rParent.eVScrollMetric = ((FieldUnit)nUnit); // "Window/VerticalRulerUnit"
/*M*/                     }
/*M*/                     break;
/*M*/                     case 10: rParent.SetSmoothScroll(bSet); break;// "Window/SmoothScroll",
/*M*/                     case 11:
/*M*/                     {
/*M*/                         sal_Int32 nVal; pValues[nProp] >>= nVal;
/*N*/                         rParent.SetZoom((USHORT)nVal);
/*M*/                     }
/*M*/                     break;// "Zoom/Value",
/*M*/                     case 12:
/*M*/                     {
/*M*/                         sal_Int32 nVal; pValues[nProp] >>= nVal;
/*M*/                         rParent.SetZoomType((BYTE)nVal);
/*M*/                     }
/*M*/                     break;// "Zoom/Type",
/*M*/                     case 13:
/*M*/                   {
/*M*/                       sal_Int32 nUnit; pValues[nProp] >>= nUnit;
/*M*/                         rParent.SetMetric((FieldUnit)nUnit, TRUE);
/*M*/                   }
/*M*/                   break;// "Other/MeasureUnit",
/*M*/                     case 14:
/*M*/                   {
/*M*/                       sal_Int32 nTab; pValues[nProp] >>= nTab;
/*M*/                         rParent.SetDefTab(MM100_TO_TWIP(nTab), TRUE);
/*M*/                   }
/*M*/                   break;// "Other/TabStop",
/*M*/                     case 15: rParent.SetVRulerRight(bSet); break;// "Window/IsVerticalRulerRight",
/*M*/                 }
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ Sequence<OUString> SwGridConfig::GetPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "Option/SnapToGrid",            // 0
/*N*/       "Option/VisibleGrid",           // 1
/*N*/       "Option/Synchronize",           // 2
/*N*/       "Resolution/XAxis",             // 3
/*N*/       "Resolution/YAxis",             // 4
/*N*/       "Subdivision/XAxis",            // 5
/*N*/       "Subdivision/YAxis"             // 6
/*N*/   };
/*N*/   const int nCount = 7;
/*N*/   Sequence<OUString> aNames(nCount);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < nCount; i++)
/*N*/   {
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwGridConfig::SwGridConfig(BOOL bIsWeb, SwMasterUsrPref& rPar) :
/*N*/     ConfigItem(bIsWeb ? C2U("Office.WriterWeb/Grid") :  C2U("Office.Writer/Grid"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   rParent(rPar),
/*N*/   bWeb(bIsWeb)
/*N*/ {
/*N*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwGridConfig::~SwGridConfig()
/*N*/ {
/*N*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwGridConfig::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      sal_Bool bSet;
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0: bSet = rParent.IsSnap(); break;//      "Option/SnapToGrid",
//STRIP001          case  1: bSet = rParent.IsGridVisible(); break;//"Option/VisibleGrid",
//STRIP001          case  2: bSet = rParent.IsSynchronize(); break;//  "Option/Synchronize",
//STRIP001          case  3: pValues[nProp] <<= (sal_Int32)TWIP_TO_MM100(rParent.GetSnapSize().Width()); break;//      "Resolution/XAxis",
//STRIP001          case  4: pValues[nProp] <<= (sal_Int32)TWIP_TO_MM100(rParent.GetSnapSize().Height()); break;//      "Resolution/YAxis",
//STRIP001          case  5: pValues[nProp] <<= (sal_Int16)rParent.GetDivisionX(); break;//   "Subdivision/XAxis",
//STRIP001          case  6: pValues[nProp] <<= (sal_Int16)rParent.GetDivisionY(); break;//   "Subdivision/YAxis"
//STRIP001      }
//STRIP001      if(nProp < 3)
//STRIP001              pValues[nProp].setValue(&bSet, ::getBooleanCppuType());
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwGridConfig::Load()
/*N*/ {
/*N*/   Sequence<OUString> aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       Size aSnap(rParent.GetSnapSize());
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               sal_Bool bSet = nProp < 3 ? *(sal_Bool*)pValues[nProp].getValue() : sal_False;
/*N*/               sal_Int32 nSet;
/*N*/               if(nProp >= 3)
/*N*/                   pValues[nProp] >>= nSet;
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case  0: rParent.SetSnap(bSet); break;//        "Option/SnapToGrid",
/*N*/                   case  1: rParent.SetGridVisible(bSet); break;//"Option/VisibleGrid",
/*N*/                   case  2: rParent.SetSynchronize(bSet); break;//  "Option/Synchronize",
/*N*/                   case  3: aSnap.Width() = MM100_TO_TWIP(nSet); break;//      "Resolution/XAxis",
/*N*/                   case  4: aSnap.Height() = MM100_TO_TWIP(nSet); break;//      "Resolution/YAxis",
/*N*/                   case  5: rParent.SetDivisionX((short)nSet); break;//   "Subdivision/XAxis",
/*N*/                   case  6: rParent.SetDivisionY((short)nSet); break;//   "Subdivision/YAxis"
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       rParent.SetSnapSize(aSnap);
/*N*/   }
/*N*/ }

/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ Sequence<OUString> SwCursorConfig::GetPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "DirectCursor/UseDirectCursor", // 0
/*N*/       "DirectCursor/Insert",          // 1
/*N*/         "Option/ProtectedArea"          // 2
/*N*/   };
/*N*/     const int nCount = 3;
/*N*/   Sequence<OUString> aNames(nCount);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < nCount; i++)
/*N*/       pNames[i] = C2U(aPropNames[i]);
/*N*/   return aNames;
/*N*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwCursorConfig::SwCursorConfig(SwMasterUsrPref& rPar) :
/*N*/     ConfigItem(C2U("Office.Writer/Cursor"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   rParent(rPar)
/*N*/ {
/*N*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwCursorConfig::~SwCursorConfig()
/*N*/ {
/*N*/ }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwCursorConfig::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      sal_Bool bSet;
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0: bSet = rParent.IsShadowCursor();       break;//  "DirectCursor/UseDirectCursor",
//STRIP001          case  1: pValues[nProp] <<= (sal_Int32)rParent.GetShdwCrsrFillMode();   break;//  "DirectCursor/Insert",
//STRIP001             case  2: bSet = rParent.IsCursorInProtectedArea(); break;// "Option/ProtectedArea"
//STRIP001      }
//STRIP001         if(nProp != 1 )
//STRIP001              pValues[nProp].setValue(&bSet, ::getBooleanCppuType());
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/* -----------------------------19.01.01 13:07--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwCursorConfig::Load()
/*N*/ {
/*N*/   Sequence<OUString> aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               sal_Bool bSet;
/*N*/               sal_Int32 nSet;
/*N*/                 if(nProp != 1 )
/*N*/                   bSet = *(sal_Bool*)pValues[nProp].getValue();
/*N*/               else
/*N*/                   pValues[nProp] >>= nSet;
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case  0: rParent.SetShadowCursor(bSet);         break;//  "DirectCursor/UseDirectCursor",
/*N*/                     case  1: rParent.SetShdwCrsrFillMode((BYTE)nSet); break;//  "DirectCursor/Insert",
/*N*/                     case  2: rParent.SetCursorInProtectedArea(bSet); break;// "Option/ProtectedArea"
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/   }
/*N*/ }
/*-- 28.09.00 09:55:33---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwWebColorConfig::SwWebColorConfig(SwMasterUsrPref& rPar) :
/*N*/     ConfigItem(C2U("Office.WriterWeb/Background"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   rParent(rPar),
/*N*/   aPropNames(1)
/*N*/ {
/*N*/   aPropNames.getArray()[0] = C2U("Color");
/*N*/ }
/*-- 28.09.00 09:55:33---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwWebColorConfig::~SwWebColorConfig()
/*N*/ {
/*N*/ }
/*-- 28.09.00 09:55:33---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void SwWebColorConfig::Commit()
//STRIP001 {
//STRIP001  Sequence<Any> aValues(aPropNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001  for(int nProp = 0; nProp < aPropNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0: pValues[nProp] <<= (sal_Int32)rParent.GetRetoucheColor().GetColor();   break;// "Color",
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aPropNames, aValues);
//STRIP001 }
/*-- 28.09.00 09:55:34---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ void SwWebColorConfig::Load()
/*N*/ {
/*N*/   Sequence<Any> aValues = GetProperties(aPropNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aPropNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aPropNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aPropNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*?*/               switch(nProp)
/*?*/               {
/*?*/                   case  0:
/*?*/                       sal_Int32 nSet; pValues[nProp] >>= nSet; rParent.SetRetoucheColor(nSet);
/*?*/                   break;// "Color",
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


}
