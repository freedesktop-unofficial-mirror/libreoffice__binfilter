/*************************************************************************
 *
 *  $RCSfile: sw_uitool.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:47 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _UIPARAM_HXX
#include <uiparam.hxx>
#endif


#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _UNOTOOLS_COLLATORWRAPPER_HXX
#include <unotools/collatorwrapper.hxx>
#endif

#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SVX_PMDLITEM_HXX //autogen
#include <bf_svx/pmdlitem.hxx>
#endif
#ifndef _SVX_TSTPITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_SIZEITEM_HXX //autogen
#include <bf_svx/sizeitem.hxx>
#endif
#ifndef _SVX_PAGEITEM_HXX //autogen
#include <bf_svx/pageitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
#ifndef _VCL_LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif

#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _TABCOL_HXX //autogen
#include <tabcol.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _SWWVIEW_HXX //autogen
#include <wview.hxx>
#endif
#ifndef _UIITEMS_HXX
#include <uiitems.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _UITOOL_HXX
#include <uitool.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _USRPREF_HXX
#include "usrpref.hxx"
#endif

#ifndef _ERROR_H
#include <error.h>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
#ifndef _UTLUI_HRC
#include <utlui.hrc>
#endif
#ifndef _DOC_HXX //autogen wg. SwDoc
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen wg. SwCharFmt
#include <charfmt.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
// 50 cm 28350
//
#define MAXHEIGHT 28350
#define MAXWIDTH  28350

/*--------------------------------------------------------------------
    Beschreibung: Allgemeine List von StringPointern
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung: Metric umschalten
 --------------------------------------------------------------------*/


//STRIP001 void SetMetric(MetricFormatter& rCtrl, FieldUnit eUnit)
//STRIP001 {
//STRIP001  SwTwips nMin = rCtrl.GetMin(FUNIT_TWIP);
//STRIP001  SwTwips nMax = rCtrl.GetMax(FUNIT_TWIP);
//STRIP001
//STRIP001  rCtrl.SetUnit(eUnit);
//STRIP001
//STRIP001  rCtrl.SetMin(nMin, FUNIT_TWIP);
//STRIP001  rCtrl.SetMax(nMax, FUNIT_TWIP);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Boxinfo-Attribut setzen
 --------------------------------------------------------------------*/


//STRIP001 void PrepareBoxInfo(SfxItemSet& rSet, const SwWrtShell& rSh)
//STRIP001 {
//STRIP001  SvxBoxInfoItem aBoxInfo;
//STRIP001  const SfxPoolItem *pBoxInfo;
//STRIP001  if ( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_BORDER_INNER,
//STRIP001                                      TRUE, &pBoxInfo))
//STRIP001      aBoxInfo = *(SvxBoxInfoItem*)pBoxInfo;
//STRIP001
//STRIP001      // Tabellenvariante, wenn mehrere Tabellenzellen selektiert
//STRIP001  rSh.GetCrsr();                  //Damit GetCrsrCnt() auch das Richtige liefert
//STRIP001  aBoxInfo.SetTable          (rSh.IsTableMode() && rSh.GetCrsrCnt() > 1);
//STRIP001      // Abstandsfeld immer anzeigen
//STRIP001  aBoxInfo.SetDist           ((BOOL) TRUE);
//STRIP001      // Minimalgroesse in Tabellen und Absaetzen setzen
//STRIP001  aBoxInfo.SetMinDist        (rSh.IsTableMode() || rSh.GetSelectionType() & (SwWrtShell::SEL_TXT | SwWrtShell::SEL_TBL));
//STRIP001      // Default-Abstand immer setzen
//STRIP001  aBoxInfo.SetDefDist        (MIN_BORDER_DIST);
//STRIP001      // Einzelne Linien koennen nur in Tabellen DontCare-Status haben
//STRIP001  aBoxInfo.SetValid(VALID_DISABLE, !rSh.IsTableMode());
//STRIP001
//STRIP001  rSet.Put(aBoxInfo);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Header Footer fuellen
 --------------------------------------------------------------------*/


/*N*/ void FillHdFt(SwFrmFmt* pFmt, const  SfxItemSet& rSet)
/*N*/ {
/*N*/   SwAttrSet aSet(pFmt->GetAttrSet());
/*N*/   aSet.Put(rSet);
/*N*/
/*N*/   const SvxSizeItem& rSize = (const SvxSizeItem&)rSet.Get(SID_ATTR_PAGE_SIZE);
/*N*/   const SfxBoolItem& rDynamic = (const SfxBoolItem&)rSet.Get(SID_ATTR_PAGE_DYNAMIC);
/*N*/
/*N*/   // Groesse umsetzen
/*N*/   //
/*N*/   SwFmtFrmSize aFrmSize(rDynamic.GetValue() ? ATT_MIN_SIZE : ATT_FIX_SIZE,
/*N*/                           rSize.GetSize().Width(),
/*N*/                           rSize.GetSize().Height());
/*N*/   aSet.Put(aFrmSize);
/*N*/   pFmt->SetAttr(aSet);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   PageDesc <-> in Sets wandeln und zurueck
 --------------------------------------------------------------------*/


/*N*/ void ItemSetToPageDesc( const SfxItemSet& rSet, SwPageDesc& rPageDesc )
/*N*/ {
/*N*/   SwFrmFmt& rMaster = rPageDesc.GetMaster();
/*N*/
/*N*/   // alle allgemeinen Rahmen-Attribute uebertragen
/*N*/   //
/*N*/   rMaster.SetAttr(rSet);
/*N*/
/*N*/   // PageData
/*N*/   //
/*N*/   if(rSet.GetItemState(SID_ATTR_PAGE) == SFX_ITEM_SET)
/*N*/   {
/*N*/       const SvxPageItem& rPageItem = (const SvxPageItem&)rSet.Get(SID_ATTR_PAGE);
/*N*/
/*N*/       USHORT nUse = (USHORT)rPageItem.GetPageUsage();
/*N*/       if(nUse & 0x04)
/*N*/           nUse |= 0x03;
/*N*/       if(nUse)
/*N*/           rPageDesc.SetUseOn( (UseOnPage) nUse );
/*N*/       rPageDesc.SetLandscape(rPageItem.IsLandscape());
/*N*/       SvxNumberType aNumType;
/*N*/       aNumType.SetNumberingType(rPageItem.GetNumType());
/*N*/       rPageDesc.SetNumType(aNumType);
/*N*/   }
/*N*/   // Groesse
/*N*/   //
/*N*/   if(rSet.GetItemState(SID_ATTR_PAGE_SIZE) == SFX_ITEM_SET)
/*N*/   {
/*N*/       const SvxSizeItem& rSizeItem = (const SvxSizeItem&)rSet.Get(SID_ATTR_PAGE_SIZE);
/*N*/       SwFmtFrmSize aSize(ATT_FIX_SIZE);
/*N*/       aSize.SetSize(rSizeItem.GetSize());
/*N*/       rMaster.SetAttr(aSize);
/*N*/   }
/*N*/   // Kopzeilen-Attribute auswerten
/*N*/   //
/*N*/   const SfxPoolItem* pItem;
/*N*/   if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_PAGE_HEADERSET,
/*N*/           FALSE, &pItem ) )
/*N*/   {
/*N*/       const SfxItemSet& rHeaderSet = ((SvxSetItem*)pItem)->GetItemSet();
/*N*/       const SfxBoolItem& rHeaderOn = (const SfxBoolItem&)rHeaderSet.Get(SID_ATTR_PAGE_ON);
/*N*/
/*N*/       if(rHeaderOn.GetValue())
/*N*/       {
/*N*/           // Werte uebernehmen
/*N*/           if(!rMaster.GetHeader().IsActive())
/*N*/               rMaster.SetAttr(SwFmtHeader(TRUE));
/*N*/
/*N*/           // Das Headerformat rausholen und anpassen
/*N*/           //
/*N*/           SwFmtHeader aHeaderFmt(rMaster.GetHeader());
/*N*/           SwFrmFmt *pHeaderFmt = aHeaderFmt.GetHeaderFmt();
/*N*/           ASSERT(pHeaderFmt != 0, "kein HeaderFormat");
/*N*/
/*N*/           ::FillHdFt(pHeaderFmt, rHeaderSet);
/*N*/
/*N*/           rPageDesc.ChgHeaderShare(((const SfxBoolItem&)
/*N*/                       rHeaderSet.Get(SID_ATTR_PAGE_SHARED)).GetValue());
/*N*/       }
/*N*/       else
/*N*/       {   // Header ausschalten
/*N*/           //
/*?*/           if(rMaster.GetHeader().IsActive())
/*?*/           {
/*?*/               rMaster.SetAttr(SwFmtHeader(BOOL(FALSE)));
/*?*/               rPageDesc.ChgHeaderShare(FALSE);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Fusszeilen-Attribute auswerten
/*N*/   //
/*N*/   if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_PAGE_FOOTERSET,
/*N*/           FALSE, &pItem ) )
/*N*/   {
/*N*/       const SfxItemSet& rFooterSet = ((SvxSetItem*)pItem)->GetItemSet();
/*N*/       const SfxBoolItem& rFooterOn = (const SfxBoolItem&)rFooterSet.Get(SID_ATTR_PAGE_ON);
/*N*/
/*N*/       if(rFooterOn.GetValue())
/*N*/       {
/*N*/           // Werte uebernehmen
/*N*/           if(!rMaster.GetFooter().IsActive())
/*N*/               rMaster.SetAttr(SwFmtFooter(TRUE));
/*N*/
/*N*/           // Das Footerformat rausholen und anpassen
/*N*/           //
/*N*/           SwFmtFooter aFooterFmt(rMaster.GetFooter());
/*N*/           SwFrmFmt *pFooterFmt = aFooterFmt.GetFooterFmt();
/*N*/           ASSERT(pFooterFmt != 0, "kein FooterFormat");
/*N*/
/*N*/           ::FillHdFt(pFooterFmt, rFooterSet);
/*N*/
/*N*/           rPageDesc.ChgFooterShare(((const SfxBoolItem&)
/*N*/                       rFooterSet.Get(SID_ATTR_PAGE_SHARED)).GetValue());
/*N*/       }
/*N*/       else
/*N*/       {   // Footer ausschalten
/*?*/           //
/*?*/           if(rMaster.GetFooter().IsActive())
/*?*/           {
/*?*/               rMaster.SetAttr(SwFmtFooter(BOOL(FALSE)));
/*?*/               rPageDesc.ChgFooterShare(FALSE);
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Fussnoten
/*N*/   //
/*N*/   if( SFX_ITEM_SET == rSet.GetItemState( FN_PARAM_FTN_INFO,
/*N*/           FALSE, &pItem ) )
/*N*/       rPageDesc.SetFtnInfo( ((SwPageFtnInfoItem*)pItem)->GetPageFtnInfo() );
/*N*/
/*N*/
/*N*/   //
/*N*/   // Columns
/*N*/   //
/*N*/
/*N*/   // Registerhaltigkeit
/*N*/
/*N*/   if(SFX_ITEM_SET == rSet.GetItemState(
/*N*/                           SID_SWREGISTER_MODE, FALSE, &pItem))
/*N*/   {
/*N*/       BOOL bSet = ((const SfxBoolItem*)pItem)->GetValue();
/*N*/       if(!bSet)
/*N*/           rPageDesc.SetRegisterFmtColl(0);
/*N*/       else if(SFX_ITEM_SET == rSet.GetItemState(
/*N*/                               SID_SWREGISTER_COLLECTION, FALSE, &pItem))
/*N*/       {
/*N*/           const String& rColl = ((const SfxStringItem*)pItem)->GetValue();
/*N*/           SwDoc& rDoc = *rMaster.GetDoc();
/*N*/           SwTxtFmtColl* pColl = rDoc.FindTxtFmtCollByName( rColl );
/*N*/           if( !pColl )
/*N*/           {
/*?*/               USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName( rColl, GET_POOLID_TXTCOLL );
/*?*/               if( USHRT_MAX != nId )
/*?*/                   pColl = rDoc.GetTxtCollFromPool( nId );
/*?*/               else
/*?*/                   pColl = rDoc.MakeTxtFmtColl( rColl,
/*?*/                               (SwTxtFmtColl*)rDoc.GetDfltTxtFmtColl() );
/*N*/           }
/*N*/           if( pColl )
/*N*/               pColl->SetAttr( SwRegisterItem ( TRUE ));
/*N*/           rPageDesc.SetRegisterFmtColl( pColl );
/*N*/       }
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


/*N*/ void PageDescToItemSet(   const SwPageDesc& rPageDesc, SfxItemSet& rSet)
/*N*/ {
/*N*/   const SwFrmFmt& rMaster = rPageDesc.GetMaster();
/*N*/
/*N*/   // Seitendaten
/*N*/   //
/*N*/   SvxPageItem aPageItem(SID_ATTR_PAGE);
/*N*/   aPageItem.SetDescName(rPageDesc.GetName());
/*N*/   aPageItem.SetPageUsage((SvxPageUsage)rPageDesc.GetUseOn());
/*N*/   aPageItem.SetLandscape(rPageDesc.GetLandscape());
/*N*/   aPageItem.SetNumType((SvxNumType)rPageDesc.GetNumType().GetNumberingType());
/*N*/   rSet.Put(aPageItem);
/*N*/
/*N*/   // Groesse
/*N*/   SvxSizeItem aSizeItem(SID_ATTR_PAGE_SIZE, rMaster.GetFrmSize().GetSize());
/*N*/   rSet.Put(aSizeItem);
/*N*/
/*N*/   // Maximale Groesse
/*N*/   SvxSizeItem aMaxSizeItem(SID_ATTR_PAGE_MAXSIZE, Size(MAXWIDTH, MAXHEIGHT));
/*N*/   rSet.Put(aMaxSizeItem);
/*N*/
/*N*/   // Raender, Umrandung und das andere Zeug
/*N*/   //
/*N*/   rSet.Put(rMaster.GetAttrSet());
/*N*/
/*N*/   SvxBoxInfoItem aBoxInfo;
/*N*/   const SfxPoolItem *pBoxInfo;
/*N*/   if ( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_BORDER_INNER,
/*N*/                                           TRUE, &pBoxInfo) )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 aBoxInfo = *(SvxBoxInfoItem*)pBoxInfo;
/*N*/
/*N*/   aBoxInfo.SetTable( FALSE );
/*N*/       // Abstandsfeld immer anzeigen
/*N*/   aBoxInfo.SetDist( TRUE);
/*N*/       // Minimalgroesse in Tabellen und Absaetzen setzen
/*N*/   aBoxInfo.SetMinDist( FALSE );
/*N*/   // Default-Abstand immer setzen
/*N*/   aBoxInfo.SetDefDist( MIN_BORDER_DIST );
/*N*/       // Einzelne Linien koennen nur in Tabellen DontCare-Status haben
/*N*/   aBoxInfo.SetValid( VALID_DISABLE );
/*N*/   rSet.Put( aBoxInfo );
/*N*/
/*N*/
/*N*/   SfxStringItem aFollow(SID_ATTR_PAGE_EXT1, aEmptyStr);
/*N*/   if(rPageDesc.GetFollow())
/*N*/       aFollow.SetValue(rPageDesc.GetFollow()->GetName());
/*N*/   rSet.Put(aFollow);
/*N*/
/*N*/   // Header
/*N*/   //
/*N*/   if(rMaster.GetHeader().IsActive())
/*N*/   {
/*N*/       const SwFmtHeader &rHeaderFmt = rMaster.GetHeader();
/*N*/       const SwFrmFmt *pHeaderFmt = rHeaderFmt.GetHeaderFmt();
/*N*/       ASSERT(pHeaderFmt != 0, kein HeaderFormat.);
/*N*/
/*N*/       // HeaderInfo, Raender, Hintergrund, Umrandung
/*N*/       //
/*N*/       SfxItemSet aHeaderSet( *rSet.GetPool(),
/*N*/                   SID_ATTR_PAGE_ON,       SID_ATTR_PAGE_SHARED,
/*N*/                   SID_ATTR_PAGE_SIZE,     SID_ATTR_PAGE_SIZE,
/*N*/                   SID_ATTR_BORDER_INNER,  SID_ATTR_BORDER_INNER,
/*N*/                   RES_FRMATR_BEGIN,       RES_FRMATR_END-1,
/*N*/                   0);
/*N*/
/*N*/       // dynamische oder feste Hoehe
/*N*/       //
/*N*/       SfxBoolItem aOn(SID_ATTR_PAGE_ON, TRUE);
/*N*/       aHeaderSet.Put(aOn);
/*N*/
/*N*/       const SwFmtFrmSize &rFrmSize = pHeaderFmt->GetFrmSize();
/*N*/       const SwFrmSize eSizeType = rFrmSize.GetSizeType();
/*N*/       SfxBoolItem aDynamic(SID_ATTR_PAGE_DYNAMIC, eSizeType != ATT_FIX_SIZE);
/*N*/       aHeaderSet.Put(aDynamic);
/*N*/
/*N*/       // Links gleich rechts
/*N*/       //
/*N*/       SfxBoolItem aShared(SID_ATTR_PAGE_SHARED, rPageDesc.IsHeaderShared());
/*N*/       aHeaderSet.Put(aShared);
/*N*/
/*N*/       // Groesse
/*N*/       SvxSizeItem aSize(SID_ATTR_PAGE_SIZE, Size(rFrmSize.GetSize()));
/*N*/       aHeaderSet.Put(aSize);
/*N*/
/*N*/       // Rahmen-Attribute umschaufeln
/*N*/       //
/*N*/       aHeaderSet.Put(pHeaderFmt->GetAttrSet());
/*N*/       aHeaderSet.Put( aBoxInfo );
/*N*/
/*N*/       // SetItem erzeugen
/*N*/       //
/*N*/       SvxSetItem aSetItem(SID_ATTR_PAGE_HEADERSET, aHeaderSet);
/*N*/       rSet.Put(aSetItem);
/*N*/   }
/*N*/
/*N*/   // Footer
/*N*/   if(rMaster.GetFooter().IsActive())
/*N*/   {
/*N*/       const SwFmtFooter &rFooterFmt = rMaster.GetFooter();
/*N*/       const SwFrmFmt *pFooterFmt = rFooterFmt.GetFooterFmt();
/*N*/       ASSERT(pFooterFmt != 0, kein FooterFormat.);
/*N*/
/*N*/       // FooterInfo, Raender, Hintergrund, Umrandung
/*N*/       //
/*N*/       SfxItemSet aFooterSet( *rSet.GetPool(),
/*N*/                   SID_ATTR_PAGE_ON,       SID_ATTR_PAGE_SHARED,
/*N*/                   SID_ATTR_PAGE_SIZE,     SID_ATTR_PAGE_SIZE,
/*N*/                   SID_ATTR_BORDER_INNER,  SID_ATTR_BORDER_INNER,
/*N*/                   RES_FRMATR_BEGIN,       RES_FRMATR_END-1,
/*N*/                   0);
/*N*/
/*N*/       // dynamische oder feste Hoehe
/*N*/       //
/*N*/       SfxBoolItem aOn(SID_ATTR_PAGE_ON, TRUE);
/*N*/       aFooterSet.Put(aOn);
/*N*/
/*N*/       const SwFmtFrmSize &rFrmSize = pFooterFmt->GetFrmSize();
/*N*/       const SwFrmSize eSizeType = rFrmSize.GetSizeType();
/*N*/       SfxBoolItem aDynamic(SID_ATTR_PAGE_DYNAMIC, eSizeType != ATT_FIX_SIZE);
/*N*/       aFooterSet.Put(aDynamic);
/*N*/
/*N*/       // Links gleich rechts
/*N*/       //
/*N*/       SfxBoolItem aShared(SID_ATTR_PAGE_SHARED, rPageDesc.IsFooterShared());
/*N*/       aFooterSet.Put(aShared);
/*N*/
/*N*/       // Groesse
/*N*/       SvxSizeItem aSize(SID_ATTR_PAGE_SIZE, Size(rFrmSize.GetSize()));
/*N*/       aFooterSet.Put(aSize);
/*N*/
/*N*/       // Rahmen-Attribute umschaufeln
/*N*/       //
/*N*/       aFooterSet.Put(pFooterFmt->GetAttrSet());
/*N*/       aFooterSet.Put( aBoxInfo );
/*N*/
/*N*/       // SetItem erzeugen
/*N*/       //
/*N*/       SvxSetItem aSetItem(SID_ATTR_PAGE_FOOTERSET, aFooterSet);
/*N*/       rSet.Put(aSetItem);
/*N*/   }
/*N*/
/*N*/   // Fussnoten einbauen
/*N*/   //
/*N*/   SwPageFtnInfo& rInfo = (SwPageFtnInfo&)rPageDesc.GetFtnInfo();
/*N*/   SwPageFtnInfoItem aFtnItem(FN_PARAM_FTN_INFO, rInfo);
/*N*/   rSet.Put(aFtnItem);
/*N*/
/*N*/   // Registerhaltigkeit
/*N*/
/*N*/   const SwTxtFmtColl* pCol = rPageDesc.GetRegisterFmtColl();
/*N*/   SwRegisterItem aReg(pCol != 0);
/*N*/   aReg.SetWhich(SID_SWREGISTER_MODE);
/*N*/   rSet.Put(aReg);
/*N*/   if(pCol)
/*N*/       rSet.Put(SfxStringItem(SID_SWREGISTER_COLLECTION, pCol->GetName()));
/*N*/
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:   DefaultTabs setzen
 --------------------------------------------------------------------*/


//STRIP001 void MakeDefTabs(SwTwips nDefDist, SvxTabStopItem& rTabs)
//STRIP001 {
//STRIP001  if( rTabs.Count() )
//STRIP001      return;
//STRIP001  {
//STRIP001      SvxTabStop aSwTabStop( nDefDist, SVX_TAB_ADJUST_DEFAULT );
//STRIP001      rTabs.Insert( aSwTabStop );
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Abstand zwischen zwei Tabs
 --------------------------------------------------------------------*/


/*N*/ USHORT GetTabDist(const SvxTabStopItem& rTabs)
/*N*/ {
/*N*/   USHORT nDefDist;
/*N*/   if( rTabs.Count() )
/*N*/       nDefDist = (USHORT)( rTabs[0].GetTabPos() );
/*N*/   else
/*N*/       nDefDist = 1134;     // 2cm
/*N*/   return nDefDist;
/*N*/ }


// erfrage ob im Set eine Sfx-PageDesc-Kombination vorliegt und returne diese
//STRIP001 void SfxToSwPageDescAttr( const SwWrtShell& rShell, SfxItemSet& rSet )
//STRIP001 {
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  SwFmtPageDesc aPgDesc;
//STRIP001
//STRIP001  BOOL bChanged = FALSE;
//STRIP001  // Seitennummer
//STRIP001  if(SFX_ITEM_SET == rSet.GetItemState(SID_ATTR_PARA_PAGENUM, FALSE, &pItem))
//STRIP001  {
//STRIP001      aPgDesc.SetNumOffset(((SfxUInt16Item*)pItem)->GetValue());
//STRIP001      bChanged = TRUE;
//STRIP001  }
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_PARA_MODEL, FALSE, &pItem ))
//STRIP001  {
//STRIP001      const String& rDescName = ((SvxPageModelItem*)pItem)->GetValue();
//STRIP001      if( rDescName.Len() )   // kein Name -> PageDesc ausschalten!
//STRIP001      {
//STRIP001          // nur loeschen, wenn PageDesc eingschaltet wird!
//STRIP001          rSet.ClearItem( RES_BREAK );
//STRIP001          SwPageDesc* pDesc = ((SwWrtShell&)rShell).FindPageDescByName(
//STRIP001                                                  rDescName, TRUE );
//STRIP001          if( pDesc )
//STRIP001              pDesc->Add( &aPgDesc );
//STRIP001      }
//STRIP001      rSet.ClearItem( SID_ATTR_PARA_MODEL );
//STRIP001      bChanged = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SfxItemSet aCoreSet(rShell.GetView().GetPool(), RES_PAGEDESC, RES_PAGEDESC );
//STRIP001      rShell.GetAttr( aCoreSet );
//STRIP001      if(SFX_ITEM_SET == aCoreSet.GetItemState( RES_PAGEDESC, TRUE, &pItem ) )
//STRIP001      {
//STRIP001          if( ((SwFmtPageDesc*)pItem)->GetPageDesc() )
//STRIP001          {
//STRIP001              ((SwFmtPageDesc*)pItem)->GetPageDesc()->Add(&aPgDesc);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  if(bChanged)
//STRIP001      rSet.Put( aPgDesc );
//STRIP001 }


// erfrage ob im Set eine Sfx-PageDesc-Kombination vorliegt und returne diese
//STRIP001 void SwToSfxPageDescAttr( SfxItemSet& rCoreSet )
//STRIP001 {
//STRIP001  const SfxPoolItem* pItem = 0;
//STRIP001  String aName;
//STRIP001  USHORT nPageNum = 0;
//STRIP001  BOOL bPut = TRUE;
//STRIP001  switch( rCoreSet.GetItemState( RES_PAGEDESC, TRUE, &pItem ) )
//STRIP001  {
//STRIP001  case SFX_ITEM_SET:
//STRIP001      {
//STRIP001          if( ((SwFmtPageDesc*)pItem)->GetPageDesc() )
//STRIP001          {
//STRIP001              aName = ((SwFmtPageDesc*)pItem)->GetPageDesc()->GetName();
//STRIP001              nPageNum = ((SwFmtPageDesc*)pItem)->GetNumOffset();
//STRIP001          }
//STRIP001          rCoreSet.ClearItem( RES_PAGEDESC );
//STRIP001          // Seitennummer
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_ITEM_AVAILABLE:
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      bPut = FALSE;
//STRIP001  }
//STRIP001  SfxUInt16Item aPageNum( SID_ATTR_PARA_PAGENUM, nPageNum );
//STRIP001  rCoreSet.Put( aPageNum );
//STRIP001
//STRIP001  if(bPut)
//STRIP001      rCoreSet.Put( SvxPageModelItem( aName, TRUE, SID_ATTR_PARA_MODEL ) );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Metric ermitteln
 --------------------------------------------------------------------*/


//STRIP001 FieldUnit    GetDfltMetric(BOOL bWeb)
//STRIP001 {
//STRIP001  return SW_MOD()->GetUsrPref(bWeb)->GetMetric();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Metric ermitteln
 --------------------------------------------------------------------*/


//STRIP001 void SetDfltMetric( FieldUnit eMetric, BOOL bWeb )
//STRIP001 {
//STRIP001  SW_MOD()->ApplyUserMetric(eMetric, bWeb);
//STRIP001 }

/*-----------------15.07.97 10:49-------------------

--------------------------------------------------*/
// Umwandlung:  Sub(LibName.ModulName) -> LibName.ModulName.Sub
//STRIP001 String ConvertMacroFormat(const String& rInput )
//STRIP001 {
//STRIP001  String sTemp(rInput);
//STRIP001  USHORT nFound = sTemp.Search('(');
//STRIP001  USHORT nTokenCount = sTemp.GetTokenCount('.');
//STRIP001  String sMac(rInput);
//STRIP001  if( STRING_NOTFOUND != nFound || nTokenCount < 2)
//STRIP001  {
//STRIP001      if(nTokenCount < 2)
//STRIP001          nFound = sTemp.Len();
//STRIP001      // anderes Format: "Macro(Bibliothek.Modul)"
//STRIP001      sMac = sTemp.Copy(0, nFound);
//STRIP001      sTemp.Erase(0, nFound);
//STRIP001      if(sTemp.Len() > 2)
//STRIP001      {
//STRIP001          sMac.Insert('.', 0);
//STRIP001          sMac.Insert(sTemp.Copy(1, sTemp.Len() - 2), 0);
//STRIP001      }
//STRIP001  }
//STRIP001  return sMac;
//STRIP001 }


//STRIP001 BOOL GetFileFilterNameDlg( Window& rParent, String& rFileName,
//STRIP001                          String* pPassword, String* pFilterName,
//STRIP001                          SfxMedium** ppMedium )
//STRIP001 {
//STRIP001  Window* pDefDlgParent = Application::GetDefDialogParent();
//STRIP001  Application::SetDefDialogParent( &rParent );
//STRIP001  SfxMedium* pMed = SFX_APP()->InsertDocumentDialog( 0, SwDocShell::Factory() );
//STRIP001  if( pMed )
//STRIP001  {
//STRIP001      if( pFilterName )
//STRIP001          *pFilterName = pMed->GetFilter()->GetFilterName();
//STRIP001
//STRIP001      rFileName = URIHelper::SmartRelToAbs( pMed->GetName() );
//STRIP001      if( pPassword )
//STRIP001      {
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == pMed->GetItemSet()->GetItemState(
//STRIP001                                  SID_PASSWORD, FALSE, &pItem ) )
//STRIP001              *pPassword = ((SfxStringItem*)pItem)->GetValue();
//STRIP001      }
//STRIP001
//STRIP001      if( ppMedium )
//STRIP001          *ppMedium = pMed;
//STRIP001      else
//STRIP001          delete pMed;        // das brauchen wir nicht mehr !
//STRIP001  }
//STRIP001  Application::SetDefDialogParent( pDefDlgParent );
//STRIP001  return 0 != pMed;
//STRIP001 }

/*-----------------09.04.98 16:58-------------------

--------------------------------------------------*/
//STRIP001 USHORT InsertStringSorted(const String& rEntry, ListBox& rToFill, USHORT nOffset )
//STRIP001 {
//STRIP001     USHORT i = nOffset;
//STRIP001  CollatorWrapper& rCaseColl = ::GetAppCaseCollator();
//STRIP001
//STRIP001  for( ; i < rToFill.GetEntryCount(); i++ )
//STRIP001  {
//STRIP001      if( 0 < rCaseColl.compareString( rToFill.GetEntry(i), rEntry ))
//STRIP001          break;
//STRIP001  }
//STRIP001  return rToFill.InsertEntry(rEntry, i);
//STRIP001 }
//STRIP001 void FillCharStyleListBox(ListBox& rToFill, SwDocShell* pDocSh, BOOL bSorted, BOOL bWithDefault)
//STRIP001 {
//STRIP001  BOOL bHasOffset = rToFill.GetEntryCount() > 0;
//STRIP001  SfxStyleSheetBasePool* pPool = pDocSh->GetStyleSheetPool();
//STRIP001  pPool->SetSearchMask(SFX_STYLE_FAMILY_CHAR, SFXSTYLEBIT_ALL);
//STRIP001  SwDoc* pDoc = pDocSh->GetDoc();
//STRIP001  const SfxStyleSheetBase* pBase = pPool->First();
//STRIP001  String sStandard;
//STRIP001  SwStyleNameMapper::FillUIName( RES_POOLCOLL_STANDARD, sStandard );
//STRIP001  while(pBase)
//STRIP001  {
//STRIP001         if(bWithDefault || pBase->GetName() !=  sStandard)
//STRIP001      {
//STRIP001          USHORT nPos;
//STRIP001          if(bSorted)
//STRIP001              nPos = InsertStringSorted(pBase->GetName(), rToFill, bHasOffset );
//STRIP001          else
//STRIP001              nPos = rToFill.InsertEntry(pBase->GetName());
//STRIP001          long nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( pBase->GetName(), GET_POOLID_CHRFMT );
//STRIP001          rToFill.SetEntryData( nPos, (void*) (nPoolId));
//STRIP001      }
//STRIP001      pBase = pPool->Next();
//STRIP001  }
//STRIP001  // non-pool styles
//STRIP001  const SwCharFmts* pFmts = pDoc->GetCharFmts();
//STRIP001  for(USHORT i = 0; i < pFmts->Count(); i++)
//STRIP001  {
//STRIP001      const SwCharFmt* pFmt = (*pFmts)[i];
//STRIP001      if(pFmt->IsDefault())
//STRIP001          continue;
//STRIP001      const String& rName = pFmt->GetName();
//STRIP001      if(rToFill.GetEntryPos(rName) == LISTBOX_ENTRY_NOTFOUND)
//STRIP001      {
//STRIP001          USHORT nPos;
//STRIP001          if(bSorted)
//STRIP001              nPos = InsertStringSorted(rName, rToFill, bHasOffset );
//STRIP001          else
//STRIP001              nPos = rToFill.InsertEntry(rName);
//STRIP001          long nPoolId = USHRT_MAX;
//STRIP001          rToFill.SetEntryData( nPos, (void*) (nPoolId));
//STRIP001      }
//STRIP001  }
//STRIP001 };

/* -----------------27.04.98 08:26-------------------
 *
 * --------------------------------------------------*/
//STRIP001 SwTwips GetTableWidth( SwFrmFmt* pFmt, SwTabCols& rCols, USHORT *pPercent,
//STRIP001          SwWrtShell* pSh )
//STRIP001 {
//STRIP001  //Die Breite zu besorgen ist etwas komplizierter.
//STRIP001  SwTwips nWidth;
//STRIP001  const SwHoriOrient eOri = pFmt->GetHoriOrient().GetHoriOrient();
//STRIP001  switch(eOri)
//STRIP001  {
//STRIP001      case HORI_FULL: nWidth = rCols.GetRight(); break;
//STRIP001      case HORI_LEFT_AND_WIDTH:
//STRIP001      case HORI_LEFT:
//STRIP001      case HORI_RIGHT:
//STRIP001      case HORI_CENTER:
//STRIP001          nWidth = pFmt->GetFrmSize().GetWidth();
//STRIP001      break;
//STRIP001      default:
//STRIP001      {
//STRIP001          if(pSh)
//STRIP001          {
//STRIP001              const SwFrmFmt *pFlyFmt;
//STRIP001              if ( 0 == (pFlyFmt = pSh->GetFlyFrmFmt()) )
//STRIP001              {
//STRIP001                  nWidth = pSh->GetAnyCurRect(RECT_PAGE_PRT).Width();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  nWidth = pSh->GetAnyCurRect(RECT_FLY_PRT_EMBEDDED).Width();
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              DBG_ERROR("wo soll die Breite denn herkommen?")
//STRIP001          }
//STRIP001          const SvxLRSpaceItem& rLRSpace = pFmt->GetLRSpace();
//STRIP001          nWidth -= (rLRSpace.GetRight() + rLRSpace.GetLeft());
//STRIP001      }
//STRIP001  }
//STRIP001  if (pPercent)
//STRIP001      *pPercent = pFmt->GetFrmSize().GetWidthPercent();
//STRIP001  return nWidth;
//STRIP001 }

/*------------------------------------------------------------------------*/

//STRIP001 String GetAppLangDateTimeString( const DateTime& rDT )
//STRIP001 {
//STRIP001  LocaleDataWrapper& rAppLclData = GetAppLocaleData();
//STRIP001  String sRet( rAppLclData.getDate( rDT ));
//STRIP001  ( sRet += ' ' ) += rAppLclData.getTime( rDT, FALSE, FALSE );
//STRIP001  return sRet;
//STRIP001 }
