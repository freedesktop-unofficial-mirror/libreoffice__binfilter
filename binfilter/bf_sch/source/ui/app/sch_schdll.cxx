/*************************************************************************
 *
 *  $RCSfile: sch_schdll.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:54 $
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


#ifndef _STDCTRL_HXX
#include <svtools/stdctrl.hxx>
#endif

#ifndef _SVX_PSZCTRL_HXX
#include <bf_svx/pszctrl.hxx>
#endif

#ifndef _SVX_MODCTRL_HXX
#include <bf_svx/modctrl.hxx>
#endif

#ifndef _SVX_XLINEIT0_HXX
#include <bf_svx/xlineit0.hxx>
#endif

#ifndef _SVX_XLNWTIT_HXX
#include <bf_svx/xlnwtit.hxx>
#endif

#ifndef _SVX_XLNCLIT_HXX
#include <bf_svx/xlnclit.hxx>
#endif

#ifndef _SVX_XFLCLIT_HXX
#include <bf_svx/xflclit.hxx>
#endif

#ifndef _SVX_XFILLIT0_HXX
#include <bf_svx/xfillit0.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVX_F3DCHILD_HXX //autogen
#include <bf_svx/f3dchild.hxx>
#endif
// header for XFillTransparenceItem
#ifndef _SVX_XFLTRIT_HXX
#include <bf_svx/xfltrit.hxx>
#endif
#ifndef _COM_SUN_STAR_CHART_CHARTDATACHANGEEVENT_HPP_
#include <com/sun/star/chart/ChartDataChangeEvent.hpp>
#endif


#include "schdll0.hxx"
#include "docshell.hxx"
#include "schmod.hxx"
#include "app.hrc"
#include "schresid.hxx"
#include "schdll.hxx"
#include "memchrt.hxx"
#include "viewshel.hxx"
#ifndef _CHTMODEL_HXX
#include "chtmodel.hxx"
#endif
#include "dgrdata.hxx"
#include "dlggraut.hxx"
#include "objfac.hxx"
#include "res_bmp.hrc"  // contains define for RID_MENU, RID_ACCEL

#include "globopt.hxx"
namespace binfilter {

/*************************************************************************
|*
|* Initialisierung aus SfxApplicaton::Init()
|*
\************************************************************************/

/*N*/ void __EXPORT SchDLL::Init()
/*N*/ {
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sd-DLL too
/*N*/
/*N*/   // the SchModule must be created (may loaded by doc-fac or direct)
/*N*/   SchModuleDummy** ppShlPtr = (SchModuleDummy**) GetAppData(BF_SHL_SCH);
/*N*/   if ( (*ppShlPtr)->IsLoaded() ) return;
/*N*/
/*N*/   SvFactory* pFact = PTR_CAST(SvFactory,(*ppShlPtr)->pSchChartDocShellFactory);
/*N*/
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = new SchModule(pFact);
/*N*/
/*N*/   SchChartDocShell::Factory().RegisterAccel(SchResId(RID_ACCEL));
/*N*/   SchChartDocShell::Factory().RegisterMenuBar(SchResId(RID_MENU));
/*N*/
/*N*/   // register menu for Star Portal
/*N*/   SchChartDocShell::Factory().RegisterPluginMenuBar( SchResId( RID_PORTAL_MENU ));
/*N*/
/*N*/   SchViewShell::RegisterFactory(1);
/*N*/
/*N*/   SfxModule* pMod = SCH_MOD();
/*N*/   SchModule::RegisterInterface(pMod);
/*N*/   SchChartDocShell::RegisterInterface(pMod);
/*N*/   SchViewShell::RegisterInterface(pMod);
/*N*/
//STRIP001 /*?*/    SchDiagramDataWrapper::RegisterChildWindow(0, pMod);
/*N*/   Svx3DChildWindow::RegisterChildWindow(0, pMod);
/*N*/   SvxPosSizeStatusBarControl::RegisterControl(SID_ATTR_SIZE, pMod);
/*N*/   SvxModifyControl::RegisterControl(SID_DOC_MODIFIED, pMod);
/*N*/
    /*N*/     pMod->PutItem( SfxUInt16Item( SID_ATTR_METRIC, ::binfilter::sch::util::GetMeasureUnit() ));
/*N*/ }

/*************************************************************************
|*
|* Deinitialisierung
|*
\************************************************************************/

/*N*/ void __EXPORT SchDLL::Exit()
/*N*/ {
/*N*/   // the SchModule must be destroyed
/*N*/   SchModuleDummy** ppShlPtr = (SchModuleDummy**) GetAppData(BF_SHL_SCH);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/ }


/*N*/ extern_c void __LOADONCALLAPI SchSetTransparent( SvInPlaceObjectRef aIPObj, BOOL bTransp )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SchChartDocShellRef aSchChartDocShellRef = &aIPObj;
//STRIP001
//STRIP001  if (aSchChartDocShellRef.Is())
//STRIP001  {
//STRIP001      ChartModel& rDoc = aSchChartDocShellRef->GetDoc();
//STRIP001
//STRIP001      const SfxItemSet &rAttr = rDoc.GetDiagramAreaAttr();
//STRIP001
//STRIP001      SAL_CONST_CAST( SfxItemSet &, rAttr).Put( XLineStyleItem( XLINE_NONE ));
//STRIP001      SAL_CONST_CAST( SfxItemSet &, rAttr).Put( XLineWidthItem( 0 ));
//STRIP001      SAL_CONST_CAST( SfxItemSet &, rAttr).Put( XLineColorItem( String(), COL_BLACK ));
//STRIP001      SAL_CONST_CAST( SfxItemSet &, rAttr).Put( XFillColorItem( String(), COL_WHITE ));
//STRIP001
//STRIP001      if( bTransp )
//STRIP001          SAL_CONST_CAST( SfxItemSet &, rAttr).Put( XFillTransparenceItem( 100 ) );
//STRIP001      else
//STRIP001          SAL_CONST_CAST( SfxItemSet &, rAttr).ClearItem( XATTR_FILLTRANSPARENCE );
//STRIP001
//STRIP001         rDoc.PageColorChanged( rAttr );
//STRIP001
//STRIP001         // #109154# propagate changes in chart item set to drawing object
//STRIP001         rDoc.BuildChart( FALSE );
//STRIP001  }
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c void __LOADONCALLAPI SchUpdate( SvInPlaceObjectRef aIPObj,
/*N*/                                        SchMemChart* pData, OutputDevice* pOut )
/*N*/ {
/*N*/   SchChartDocShellRef aSchChartDocShellRef = &aIPObj;
/*N*/
/*N*/   if( aSchChartDocShellRef.Is() )
/*N*/   {
/*N*/ #ifdef DBG_UTIL
/*N*/       if( !pData )
/*N*/           DBG_TRACE( "SchUpdate was called without MemChart" );
/*N*/ #endif
/*N*/       ChartModel& rDoc = aSchChartDocShellRef->GetDoc();
/*N*/
/*N*/       if( pData )
/*N*/       {
/*N*/           rDoc.SetChartDataBuffered( *pData, FALSE );     // don't update titles. This can't be done via SchUpdate
/*N*/           rDoc.CheckForNewAxisNumFormat();
/*N*/           rDoc.SetChanged();                              // #72576#
/*N*/
/*N*/           ::com::sun::star::chart::ChartDataChangeEvent aEvent;
/*N*/           aEvent.Type = ::com::sun::star::chart::ChartDataChangeType_ALL;
/*N*/           aEvent.StartColumn = 0;
/*N*/           aEvent.EndColumn = 0;
/*N*/           aEvent.StartRow = 0;
/*N*/           aEvent.EndRow = 0;
/*N*/
/*N*/           aSchChartDocShellRef->DataModified( aEvent );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           rDoc.BuildChart( FALSE );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aIPObj->SendViewChanged();
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c void __LOADONCALLAPI SchUpdateAttr( SvInPlaceObjectRef aIPObj,
/*N*/                                            SchMemChart* pData,
/*N*/                                            const SfxItemSet& rAttr,
/*N*/                                            OutputDevice* pOut )
/*N*/ {
/*N*/   DBG_ASSERT(pData, "Kein Chart-Datenobjekt angegeben!");
/*N*/   if(!pData)return;
/*N*/
/*N*/   SchChartDocShellRef aSchChartDocShellRef = &aIPObj;
/*N*/
/*N*/   if (aSchChartDocShellRef.Is())
/*N*/   {
/*N*/
/*N*/       ChartModel& rDoc = aSchChartDocShellRef->GetDoc();
/*N*/
/*N*/       rDoc.SetChartData(*new SchMemChart(*pData));
/*N*/       rDoc.PutAttr(rAttr);
/*N*/
/*N*/       if( pOut )
/*N*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     aSchChartDocShellRef->UpdateChart(pOut);
/*N*/       else
/*N*/           rDoc.BuildChart(TRUE);
/*N*/   }
/*N*/
/*N*/   aIPObj->SendViewChanged();
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c ModalDialog* __LOADONCALLAPI SchCreateDiagramAutoPilotDlg
/*N*/                                               (Window* pParent,
/*N*/                                                SchMemChart* pData,
/*N*/                                                const SfxItemSet& rInAttrs,
/*N*/                                                SfxItemSet& rOutAttrs,
/*N*/                                                BOOL bPrePage)
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001     DBG_ASSERT(pData, "Kein Chart-Datenobjekt angegeben!");
//STRIP001
//STRIP001  if(!pData)return NULL;
//STRIP001  return new SchDiagramAutoPilotDlg( pParent, *new SchMemChart(*pData), rInAttrs,
//STRIP001                                     rOutAttrs, bPrePage );
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c void __LOADONCALLAPI SchChangeChartData(ModalDialog* pDlg,
/*N*/                                                SchMemChart* pData)
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 DBG_ASSERT(pData, "Kein Chart-Datenobjekt angegeben!");
//STRIP001
//STRIP001  ((SchDiagramAutoPilotDlg*)pDlg)->ChangeChartData(*new SchMemChart(*pData));
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c SfxTabDialog* __LOADONCALLAPI SchCreateOptionsDlg(Window* pParent,
/*N*/                                                          const SfxItemSet& rInAttrs,
/*N*/                                                          XOutdevItemPool* pItemPool)
/*N*/ {
/*N*/   return( NULL );
/*N*/   //return new SchOptionsDlg(pParent, rInAttrs, pItemPool);
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c SchMemChart* __LOADONCALLAPI SchGetChartData (SvInPlaceObjectRef aIPObj)
/*N*/ {
/*N*/   SchChartDocShellRef aSchChartDocShellRef = &aIPObj;
/*N*/
/*N*/   if (aSchChartDocShellRef.Is())
/*N*/   {
/*N*/       ChartModel& rDoc = aSchChartDocShellRef->GetDoc();
/*N*/       SchMemChart* pMemChart = rDoc.GetChartData ();
/*N*/
/*N*/       if (pMemChart)
/*N*/       {
/*N*/           pMemChart->SetMainTitle(rDoc.MainTitle());
/*N*/           pMemChart->SetSubTitle(rDoc.SubTitle());
/*N*/           pMemChart->SetXAxisTitle(rDoc.XAxisTitle());
/*N*/           pMemChart->SetYAxisTitle(rDoc.YAxisTitle());
/*N*/           pMemChart->SetZAxisTitle(rDoc.ZAxisTitle());
/*N*/       }
/*N*/
/*N*/       return pMemChart;
/*N*/   }
/*N*/   else return 0;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartNone ()
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP");return NULL; //STRIP001 return new SchMemChart;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartXY (short nCols, short nRows)
/*N*/ {
/*N*/   return new SchMemChart (nCols, nRows);
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartCopy (const SchMemChart &rMemChart)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 return new SchMemChart (rMemChart);
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ extern_c ChartModel* __LOADONCALLAPI SchGetModel (SvInPlaceObjectRef aIPObj)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  SchChartDocShellRef aSchChartDocShellRef = &aIPObj;
//STRIP001
//STRIP001  if (aSchChartDocShellRef.Is()) return &aSchChartDocShellRef->GetDoc();
//STRIP001  else return 0;
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchGetDefaultForColumnText(
/*N*/               const SchMemChart& rMemChart, sal_Int32 nCol, String& aResult )
/*N*/ {
/*N*/   aResult = rMemChart.GetDefaultColumnText( nCol );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchGetDefaultForRowText(
/*N*/           const SchMemChart& rMemChart, sal_Int32 nRow, String& aResult )
/*N*/ {
/*N*/   aResult = rMemChart.GetDefaultRowText( nRow );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchConvertChartRangeForWriter(
/*N*/                           SchMemChart& rMemChart, BOOL bOldToNew )
/*N*/ {
/*N*/   rMemChart.ConvertChartRangeForWriter( bOldToNew );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchConvertChartRangeForCalc(
/*N*/                           SchMemChart& rMemChart, BOOL bOldToNew )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.ConvertChartRangeForCalc( bOldToNew );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartResetTranslation(
/*N*/                           SchMemChart& rMemChart, long *pTable,long nCnt )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.ResetTranslation( pTable, nCnt );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartUpdateTranslation(
/*N*/                           SchMemChart& rMemChart, long *pTable, long nCnt )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.UpdateTranslation( pTable, nCnt );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartInsertCols( SchMemChart& rMemChart,
/*N*/                                               short nAtCol, short nCount)
/*N*/ {
/*N*/   rMemChart.InsertCols( nAtCol, nCount );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartRemoveCols( SchMemChart& rMemChart,
/*N*/                                               short nAtCol, short nCount)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.RemoveCols( nAtCol, nCount );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartInsertRows( SchMemChart& rMemChart,
/*N*/                                               short nAtRow, short nCount)
/*N*/ {
/*N*/   rMemChart.InsertRows( nAtRow, nCount );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartRemoveRows( SchMemChart& rMemChart,
/*N*/                                               short nAtRow, short nCount)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.RemoveRows( nAtRow, nCount );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartSwapCols( SchMemChart& rMemChart,
/*N*/                                               int nAtCol1, int nAtCol2)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.SwapCols( nAtCol1, nAtCol2 );
/*N*/ }

/*N*/ extern_c void __LOADONCALLAPI SchMemChartSwapRows( SchMemChart& rMemChart,
/*N*/                                               int nAtRow1,int nAtRow2)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rMemChart.SwapRows( nAtRow1, nAtRow2 );
/*N*/ }


}
