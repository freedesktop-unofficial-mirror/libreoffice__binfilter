/*************************************************************************
 *
 *  $RCSfile: sch_chtmode7.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:55:42 $
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

#pragma optimize("",off)

#ifndef _SCHATTR_HXX
#include "schattr.hxx"
#endif
#ifndef _SCH_MEMCHRT_HXX
#include "memchrt.hxx"
#endif

#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTTEXTORDER   SCHATTR_TEXT_ORDER
#define ITEMID_CHARTTEXTORIENT  SCHATTR_TEXT_ORIENT
#define ITEMID_CHARTLEGENDPOS   SCHATTR_LEGEND_POS
#define ITEMID_CHARTDATADESCR   SCHATTR_DATADESCR_DESCR
#include <bf_svx/chrtitem.hxx>
#endif


#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif

#define ITEMID_FONT        EE_CHAR_FONTINFO
#define ITEMID_COLOR       EE_CHAR_COLOR
#define ITEMID_FONTHEIGHT  EE_CHAR_FONTHEIGHT
#include <bf_svx/fontitem.hxx>
#include <bf_svx/fhgtitem.hxx>
#include <bf_svx/colritem.hxx>
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _CHTMODEL_HXX
#include <chtmodel.hxx>
#include <globfunc.hxx>
#endif

#ifndef _SVX_XLNWTIT_HXX //autogen
#include <bf_svx/xlnwtit.hxx>
#endif

#ifndef _SVX_XFLCLIT_HXX //autogen
#include <bf_svx/xflclit.hxx>
#endif

#ifndef _SVX_XLNCLIT_HXX //autogen
#include <bf_svx/xlnclit.hxx>
#endif

#include "pairs.hxx"

#include "chaxis.hxx"

// Hier abhaengig von der Reihe den Style zurückgeben, vorerst ist nur aufsplitten der
// Verbundcharts von nöten:
//TVM: bitte nicht benutzen! renovierungsbedürftig!
//STRIP001 SvxChartStyle ChartModel::GetRowChartStyle(const long nRow)
//STRIP001 {
//STRIP001  switch(eChartStyle)
//STRIP001  {
//STRIP001      case CHSTYLE_2D_LINE_STACKEDCOLUMN:
//STRIP001          if(IsLine(nRow))
//STRIP001              return CHSTYLE_2D_LINESYMBOLS;
//STRIP001          else
//STRIP001              return CHSTYLE_2D_STACKEDCOLUMN;
//STRIP001
//STRIP001         break;
//STRIP001
//STRIP001      case CHSTYLE_2D_LINE_COLUMN:
//STRIP001
//STRIP001          if(IsLine(nRow))
//STRIP001              return CHSTYLE_2D_LINESYMBOLS;
//STRIP001          else
//STRIP001              return CHSTYLE_2D_COLUMN;
//STRIP001
//STRIP001         break;
//STRIP001
//STRIP001      default:
//STRIP001          break;
//STRIP001  }
//STRIP001  return eChartStyle;
//STRIP001 }


/*N*/ SchMemChart* ChartModel::GetChartData() const
/*N*/ {
/*N*/   return pChartData;
/*N*/ }


/*N*/ long ChartModel::GetColCount() const
/*N*/ {
/*N*/   if( !pChartData ) return 0;         // GPF via GetMenuState
/*N*/
/*N*/   return IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/              ? pChartData->GetRowCount()
/*N*/              : pChartData->GetColCount();
/*N*/ }


/*N*/ long ChartModel::GetRowCount() const
/*N*/ {
/*N*/   if( !pChartData ) return 0;         // GPF via GetMenuState
/*N*/
/*N*/   return IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/              ? pChartData->GetColCount()
/*N*/              : pChartData->GetRowCount();
/*N*/ }


//STRIP001 const String& ChartModel::ColText( long nCol ) const
//STRIP001 {
//STRIP001  if( !pChartData ) return aMainTitle;        // have to return a const String &
//STRIP001
//STRIP001  return IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
//STRIP001             ? pChartData->GetTransRowText(nCol)
//STRIP001             : pChartData->GetTransColText(nCol);
//STRIP001 }


//STRIP001 const String& ChartModel::RowText( long nRow ) const
//STRIP001 {
//STRIP001  if( !pChartData ) return aMainTitle;        // have to return a const String &
//STRIP001
//STRIP001  return IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
//STRIP001             ? pChartData->GetTransColText(nRow)
//STRIP001             : pChartData->GetTransRowText(nRow);
//STRIP001 }


/*N*/ SvxChartStyle ChartModel::ChartStyle () const
/*N*/ {
/*N*/   return eChartStyle;
/*N*/ }


/*N*/ SvxChartStyle &ChartModel::ChartStyle()
/*N*/ {
/*N*/   return eChartStyle;
/*N*/ }

//STRIP001 void ChartModel::SetSwitchData(BOOL b)
//STRIP001 {
//STRIP001  if(bSwitchData!=b)
//STRIP001      bClearDepth=TRUE;
//STRIP001
//STRIP001  bSwitchData=b;
//STRIP001 }


/*N*/ long ChartModel::PieSegOfs( long nCol ) const
/*N*/ {
/*N*/     DBG_ASSERT( nCol < nPieSegCount, "pie segment requested is out of bounds" );
/*N*/
/*N*/     if( IsPieChart() &&
/*N*/         nCol < nPieSegCount )
/*N*/     {
/*N*/         return pPieSegOfs[ nCol ];
/*N*/     }
/*N*/
/*N*/     return 0;
/*N*/ }

//STRIP001 BOOL ChartModel::ShowMainTitle () const
//STRIP001 {
//STRIP001  return bShowMainTitle;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowMainTitle ()
/*N*/ {
/*N*/   return bShowMainTitle;
/*N*/ }


//STRIP001 const String& ChartModel::MainTitle () const
//STRIP001 {
//STRIP001  return aMainTitle;
//STRIP001 }


/*N*/ String& ChartModel::MainTitle ()
/*N*/ {
/*N*/   return aMainTitle;
/*N*/ }


//STRIP001 BOOL ChartModel::ShowSubTitle () const
//STRIP001 {
//STRIP001  return bShowSubTitle;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowSubTitle()
/*N*/ {
/*N*/   return bShowSubTitle;
/*N*/ }


//STRIP001 const String& ChartModel::SubTitle () const
//STRIP001 {
//STRIP001  return aSubTitle;
//STRIP001 }


/*N*/ String& ChartModel::SubTitle ()
/*N*/ {
/*N*/   return aSubTitle;
/*N*/ }


//STRIP001 BOOL ChartModel::ShowXAxisTitle () const
//STRIP001 {
//STRIP001  return bShowXAxisTitle;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowXAxisTitle ()
/*N*/ {
/*N*/   return bShowXAxisTitle;
/*N*/ }


/*N*/ String& ChartModel::XAxisTitle ()
/*N*/ {
/*N*/   return aXAxisTitle;
/*N*/ }


//STRIP001 const String& ChartModel::XAxisTitle () const
//STRIP001 {
//STRIP001  return aXAxisTitle;
//STRIP001 }


//STRIP001 BOOL ChartModel::ShowYAxisTitle () const
//STRIP001 {
//STRIP001  return bShowYAxisTitle;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowYAxisTitle ()
/*N*/ {
/*N*/   return bShowYAxisTitle;
/*N*/ }
/*N*/

//STRIP001 const String& ChartModel::YAxisTitle () const
//STRIP001 {
//STRIP001  return aYAxisTitle;
//STRIP001 }


/*N*/ String& ChartModel::YAxisTitle ()
/*N*/ {
/*N*/   return aYAxisTitle;
/*N*/ }


//STRIP001 BOOL ChartModel::ShowZAxisTitle () const
//STRIP001 {
//STRIP001  return bShowZAxisTitle;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowZAxisTitle ()
/*N*/ {
/*N*/   return bShowZAxisTitle;
/*N*/ }


//STRIP001 const String& ChartModel::ZAxisTitle () const
//STRIP001 {
//STRIP001  return aZAxisTitle;
//STRIP001 }


/*N*/ String& ChartModel::ZAxisTitle()
/*N*/ {
/*N*/   return aZAxisTitle;
/*N*/ }


/*N*/ BOOL ChartModel::HasTitle() const
/*N*/ {
/*N*/   return bShowMainTitle || bShowSubTitle || IsAxisChart() &&
/*N*/          (bShowXAxisTitle || bShowYAxisTitle || Is3DChart() && bShowZAxisTitle);
/*N*/ }

/*N*/ BOOL ChartModel::ShowXAxis () const
/*N*/ {
/*N*/   return pChartXAxis->IsVisible();
/*N*/ }


/*N*/ void ChartModel::ShowXAxis (BOOL b)
/*N*/ {
/*N*/   pChartXAxis->ShowAxis(b);
/*N*/ }


//STRIP001 BOOL ChartModel::ShowXGridMain () const
//STRIP001 {
//STRIP001  return bShowXGridMain;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowXGridMain ()
/*N*/ {
/*N*/   return bShowXGridMain;
/*N*/ }


//STRIP001 BOOL ChartModel::ShowXGridHelp () const
//STRIP001 {
//STRIP001  return bShowXGridHelp;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowXGridHelp ()
/*N*/ {
/*N*/   return bShowXGridHelp;
/*N*/ }


/*N*/ BOOL ChartModel::ShowXDescr () const
/*N*/ {
/*N*/   return pChartXAxis->HasDescription();
/*N*/ }


/*N*/ void ChartModel::ShowXDescr(BOOL b)
/*N*/ {
/*N*/   pChartXAxis->ShowDescr(b);
/*N*/ }


/*N*/ BOOL ChartModel::ShowYAxis () const
/*N*/ {
/*N*/   return pChartYAxis->IsVisible();
/*N*/ }
/*N*/ void ChartModel::ShowYAxis (BOOL b)
/*N*/ {
/*N*/   pChartYAxis->ShowAxis(b);
/*N*/ }

//STRIP001 BOOL ChartModel::ShowYGridMain () const
//STRIP001 {
//STRIP001  return bShowYGridMain;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowYGridMain ()
/*N*/ {
/*N*/   return bShowYGridMain;
/*N*/ }


//STRIP001 BOOL ChartModel::ShowYGridHelp () const
//STRIP001 {
//STRIP001  return bShowYGridHelp;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowYGridHelp ()
/*N*/ {
/*N*/   return bShowYGridHelp;
/*N*/ }


/*N*/ BOOL ChartModel::ShowYDescr () const
/*N*/ {
/*N*/   return pChartYAxis->HasDescription();
/*N*/ }


/*N*/ void ChartModel::ShowYDescr( BOOL b)
/*N*/ {
/*N*/   pChartYAxis->ShowDescr(b);
/*N*/ }


/*N*/ BOOL ChartModel::ShowZAxis () const
/*N*/ {
/*N*/   return pChartZAxis->IsVisible();
/*N*/ }


/*N*/ void ChartModel::ShowZAxis(BOOL b)
/*N*/ {
/*N*/   pChartZAxis->ShowAxis(b);
/*N*/ }


//STRIP001 BOOL ChartModel::ShowZGridMain () const
//STRIP001 {
//STRIP001  return bShowZGridMain;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowZGridMain ()
/*N*/ {
/*N*/   return bShowZGridMain;
/*N*/ }


//STRIP001 BOOL ChartModel::ShowZGridHelp () const
//STRIP001 {
//STRIP001  return bShowZGridHelp;
//STRIP001 }


/*N*/ BOOL& ChartModel::ShowZGridHelp ()
/*N*/ {
/*N*/   return bShowZGridHelp;
/*N*/ }


/*N*/ BOOL ChartModel::ShowZDescr () const
/*N*/ {
/*N*/   return pChartZAxis->HasDescription();
/*N*/ }


/*N*/ void ChartModel::ShowZDescr (BOOL b)
/*N*/ {
/*N*/   pChartZAxis->ShowDescr(b);
/*N*/ }


/*N*/ BOOL ChartModel::HasAxis( long nObjectId ) const
/*N*/ {
/*N*/     if( CHOBJID_ANY == nObjectId )
/*N*/         return IsAxisChart() &&
/*N*/             ( pChartXAxis->IsVisible() ||
/*N*/               pChartYAxis->IsVisible() ||
/*N*/               pChartAAxis->IsVisible() ||
/*N*/               pChartBAxis->IsVisible() ||
/*N*/               (Is3DChart() && pChartZAxis->IsVisible()) );
/*N*/
/*N*/     switch( nObjectId )
/*N*/     {
/*N*/         case CHOBJID_DIAGRAM_X_AXIS:
/*N*/             return  pChartXAxis->IsVisible();
/*N*/         case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/             return  pChartYAxis->IsVisible();
/*N*/         case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/             return  (Is3DChart() && pChartZAxis->IsVisible());
/*N*/         case CHOBJID_DIAGRAM_A_AXIS:
/*N*/             return  pChartAAxis->IsVisible();
/*N*/         case CHOBJID_DIAGRAM_B_AXIS:
/*N*/             return  pChartBAxis->IsVisible();
/*N*/     }
/*N*/
/*N*/     return FALSE;
/*N*/ }

//STRIP001 bool ChartModel::HasGrid( UINT16 nObjectId ) const
//STRIP001 {
//STRIP001     switch( nObjectId )
//STRIP001     {
//STRIP001         case CHOBJID_DIAGRAM_X_GRID_MAIN:
//STRIP001             return (CanAxis( CHART_AXIS_PRIMARY_X ) && bShowXGridMain);
//STRIP001         case CHOBJID_DIAGRAM_Y_GRID_MAIN:
//STRIP001             return (CanAxis( CHART_AXIS_PRIMARY_Y ) && bShowYGridMain);
//STRIP001         case CHOBJID_DIAGRAM_Z_GRID_MAIN:
//STRIP001             return (Is3DChart() && bShowZGridMain);
//STRIP001         case CHOBJID_DIAGRAM_X_GRID_HELP:
//STRIP001             return (CanAxis( CHART_AXIS_PRIMARY_X ) && bShowXGridHelp);
//STRIP001         case CHOBJID_DIAGRAM_Y_GRID_HELP:
//STRIP001             return (CanAxis( CHART_AXIS_PRIMARY_Y ) && bShowYGridHelp);
//STRIP001         case CHOBJID_DIAGRAM_Z_GRID_HELP:
//STRIP001             return (Is3DChart() && bShowZGridHelp);
//STRIP001         default:
//STRIP001             return false;
//STRIP001     }
//STRIP001 }

/*N*/ BOOL ChartModel::HasGrid() const
/*N*/ {
/*N*/   return IsAxisChart() &&
/*N*/          (bShowXGridMain || bShowXGridHelp ||
/*N*/           bShowYGridMain || bShowYGridHelp ||
/*N*/           Is3DChart() && (bShowZGridMain || bShowZGridHelp));
/*N*/ }
//STRIP001 const SfxItemSet& ChartModel::GetTitleAttr() const
//STRIP001 {
//STRIP001  return *pTitleAttr;
//STRIP001 }

//STRIP001 void ChartModel::PutMainTitleAttr(const SfxItemSet& rAttr,BOOL bMerge /*=TRUE*/)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pMainTitleAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pMainTitleAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetMainTitleAttr() const
//STRIP001 {
//STRIP001  return *pMainTitleAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutSubTitleAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pSubTitleAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pSubTitleAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetSubTitleAttr() const
//STRIP001 {
//STRIP001  return *pSubTitleAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutXAxisTitleAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pXAxisTitleAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pXAxisTitleAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetXAxisTitleAttr() const
//STRIP001 {
//STRIP001  return *pXAxisTitleAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutYAxisTitleAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pYAxisTitleAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pYAxisTitleAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetYAxisTitleAttr() const
//STRIP001 {
//STRIP001  return *pYAxisTitleAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutZAxisTitleAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pZAxisTitleAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pZAxisTitleAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetZAxisTitleAttr() const
//STRIP001 {
//STRIP001  return *pZAxisTitleAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutLegendAttr(const SfxItemSet& rAttr,BOOL bMerge /*=TRUE*/)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pLegendAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pLegendAttr, rAttr );
//STRIP001 }


/*N*/ const SfxItemSet& ChartModel::GetLegendAttr() const
/*N*/ {
/*N*/   return *pLegendAttr;
/*N*/ }

//STRIP001 void ChartModel::PutChartAttr(const SfxItemSet& rAttr,BOOL bMerge /*=TRUE*/)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pChartAttr->ClearItem();
//STRIP001  pChartAttr->Put(rAttr);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetChartAttr() const
//STRIP001 {
//STRIP001  return *pChartAttr;
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetAxisAttr() const
//STRIP001 {
//STRIP001  return *pAxisAttr;
//STRIP001 }




//ToDo: diese Fkt. überflüssig machen (Problem: Austausch der Achseneigenschaften nicht NUR über Attr (??? stimmt das ???)
//STRIP001 void ChartModel::CopyAxisMembers(const ChartModel* pModel)
//STRIP001 {
//STRIP001  pChartXAxis->ReadMembers(*pModel->pChartXAxis);
//STRIP001  pChartYAxis->ReadMembers(*pModel->pChartYAxis);
//STRIP001  pChartZAxis->ReadMembers(*pModel->pChartZAxis);
//STRIP001 }
//STRIP001 void ChartModel::CopyAxisAttributes(const ChartModel* pModel,BOOL bMerge)
//STRIP001 {
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_X_AXIS,pModel->GetAttr(CHOBJID_DIAGRAM_X_AXIS),bMerge);
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_Y_AXIS,pModel->GetAttr(CHOBJID_DIAGRAM_Y_AXIS),bMerge);
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_Z_AXIS,pModel->GetAttr(CHOBJID_DIAGRAM_Z_AXIS),bMerge);
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_A_AXIS,pModel->GetAttr(CHOBJID_DIAGRAM_A_AXIS),bMerge);
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_B_AXIS,pModel->GetAttr(CHOBJID_DIAGRAM_B_AXIS),bMerge);
//STRIP001 //   SetAttributes(CHOBJID_DIAGRAM_C_AXIS,pModel->GetAttr(CHOBJID_DIAGRAM_C_AXIS),bMerge);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetGridAttr() const
//STRIP001 {
//STRIP001  return *pGridAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutXGridMainAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pXGridMainAttr->ClearItem();
//STRIP001  pXGridMainAttr->Put(rAttr);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetXGridMainAttr() const
//STRIP001 {
//STRIP001  return *pXGridMainAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutYGridMainAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pYGridMainAttr->ClearItem();
//STRIP001  pYGridMainAttr->Put(rAttr);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetYGridMainAttr() const
//STRIP001 {
//STRIP001  return *pYGridMainAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutZGridMainAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pZGridMainAttr->ClearItem();
//STRIP001  pZGridMainAttr->Put(rAttr);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetZGridMainAttr() const
//STRIP001 {
//STRIP001  return *pZGridMainAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutXGridHelpAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pXGridHelpAttr->ClearItem();
//STRIP001  pXGridHelpAttr->Put(rAttr);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetXGridHelpAttr() const
//STRIP001 {
//STRIP001  return *pXGridHelpAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutYGridHelpAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pYGridHelpAttr->ClearItem();
//STRIP001  pYGridHelpAttr->Put(rAttr);
//STRIP001 }

//STRIP001 const SfxItemSet& ChartModel::GetYGridHelpAttr() const
//STRIP001 {
//STRIP001  return *pYGridHelpAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutZGridHelpAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pZGridHelpAttr->ClearItem();
//STRIP001  pZGridHelpAttr->Put(rAttr);
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetZGridHelpAttr() const
//STRIP001 {
//STRIP001  return *pZGridHelpAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutDiagramAreaAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pDiagramAreaAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pDiagramAreaAttr, rAttr );
//STRIP001
//STRIP001     // inform outliner about change for apadting the color of text using 'auto-color'
//STRIP001     PageColorChanged( *pDiagramAreaAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetDiagramAreaAttr() const
//STRIP001 {
//STRIP001  return *pDiagramAreaAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutDiagramWallAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pDiagramWallAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pDiagramWallAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetDiagramWallAttr() const
//STRIP001 {
//STRIP001  return *pDiagramWallAttr;
//STRIP001 }


//STRIP001 void ChartModel::PutDiagramFloorAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      pDiagramFloorAttr->ClearItem();
//STRIP001     PutItemSetWithNameCreation( *pDiagramFloorAttr, rAttr );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetDiagramFloorAttr() const
//STRIP001 {
//STRIP001  return *pDiagramFloorAttr;
//STRIP001 }

//STRIP001 SvxChartDataDescr ChartModel::DataDescr () const
//STRIP001 {
//STRIP001  return eDataDescr;
//STRIP001 }


//STRIP001 SvxChartDataDescr& ChartModel::DataDescr()
//STRIP001 {
//STRIP001  return eDataDescr;
//STRIP001 }


//STRIP001 BOOL ChartModel::ShowSym () const
//STRIP001 {
//STRIP001  return bShowSym;
//STRIP001 }


//STRIP001 BOOL& ChartModel::ShowSym()
//STRIP001 {
//STRIP001  return bShowSym;
//STRIP001 }

/*N*/ SdrOutliner* ChartModel::GetOutliner() const
/*N*/ {
/*N*/   return pOutliner;
/*N*/ }

/*
UINT32 ChartModel::ValFor mat () const
{
    return nValFo rmat;
}


UINT32& ChartModel::ValForm at()
{
    return nVal Format;
}


UINT32 ChartModel::PercentVa lFormat () const
{
    return nPercentV alFormat;
}


UINT32& ChartModel::Per centValFormat ()
{
    return nPercentValFo rmat;
}


UINT32 ChartModel::Des crFormat () const
{
    return nDescrFor mat;
}


UINT32& ChartModel::Desc rFormat()
{
    return nDes crFormat;
}


UINT32 ChartModel::PercentD escrFormat () const
{
    return nPercentDescrFo rmat;
}


UINT32& ChartModel::Percent DescrF ormat ()
{
    return nPercentDescr Format;
}

*/
/*N*/ BOOL ChartModel::IsInitialized() const
/*N*/ {
/*N*/   return mbIsInitialized;
/*N*/ }


//STRIP001 BOOL ChartModel::ReadError () const
//STRIP001 {
//STRIP001  return bReadError;
//STRIP001 }


/*N*/ BOOL& ChartModel::ReadError ()
/*N*/ {
/*N*/   return bReadError;
/*N*/ }


/*N*/ ChartScene* ChartModel::GetScene()
/*N*/ {
/*N*/   return pScene;
/*N*/ }


/*N*/ const SchMemChart *ChartModel::GetMemChart () const
/*N*/ {
/*N*/   return pChartData;
/*N*/ }


//STRIP001 const Rectangle &ChartModel::GetChartRect () const
//STRIP001 {
//STRIP001  return aChartRect;
//STRIP001 }


//STRIP001 const Vector3D &ChartModel::LightVec () const
//STRIP001 {
//STRIP001  return *aLightVec;
//STRIP001 }


//STRIP001 Vector3D &ChartModel::LightVec ()
//STRIP001 {
//STRIP001  return *aLightVec;
//STRIP001 }


//STRIP001 double ChartModel::SpotIntensity () const
//STRIP001 {
//STRIP001  return fSpotIntensity;
//STRIP001 }


//STRIP001 double& ChartModel::SpotIntensity ()
//STRIP001 {
//STRIP001  return fSpotIntensity;
//STRIP001 }


//STRIP001 void ChartModel::CanRebuild (BOOL bNewRebuild)
//STRIP001 {
//STRIP001  bCanRebuild = bNewRebuild;
//STRIP001 }


//STRIP001 void ChartModel::GetStatistics (BOOL              &GetShowAverage,
//STRIP001                              SvxChartKindError &GetErrorKind,
//STRIP001                              SvxChartIndicate  &GetIndicate,
//STRIP001                              double            &GetIndicatePercent,
//STRIP001                              double            &GetIndicateBigError,
//STRIP001                              double            &GetIndicatePlus,
//STRIP001                              double            &GetIndicateMinus,
//STRIP001                              SvxChartRegress   &GetRegression) const
//STRIP001 {
//STRIP001  GetShowAverage      = bShowAverage;
//STRIP001  GetErrorKind        = eErrorKind;
//STRIP001  GetIndicate         = eIndicate;
//STRIP001  GetRegression       = eRegression;
//STRIP001  GetIndicatePercent  = fIndicatePercent;
//STRIP001  GetIndicateBigError = fIndicateBigError;
//STRIP001  GetIndicatePlus     = fIndicatePlus;
//STRIP001  GetIndicateMinus    = fIndicateMinus;
//STRIP001 }

//STRIP001 const SfxItemSet& ChartModel::GetRegressAttr( long nRow ) const
//STRIP001 {
//STRIP001  return *aRegressAttrList.GetObject(nRow);
//STRIP001 }

//STRIP001 void ChartModel::PutRegressAttr( long nRow, const SfxItemSet &rAttr, BOOL bMerge )
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      aRegressAttrList.GetObject(nRow)->ClearItem();
//STRIP001  aRegressAttrList.GetObject(nRow)->Put(rAttr);
//STRIP001 }
//STRIP001 void ChartModel::ChangeRegressAttr(const SfxItemSet &rAttr,long nRow,BOOL bMerge)
//STRIP001 {
//STRIP001  PutRegressAttr(nRow, rAttr,bMerge);
//STRIP001  BuildChart (FALSE);
//STRIP001 }

//STRIP001 void ChartModel::PutAverageAttr( long nRow, const SfxItemSet &rAttr, BOOL bMerge )
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      aAverageAttrList.GetObject(nRow)->ClearItem();
//STRIP001  aAverageAttrList.GetObject(nRow)->Put(rAttr);
//STRIP001 }
//STRIP001 const SfxItemSet& ChartModel::GetAverageAttr( long nRow ) const
//STRIP001 {
//STRIP001  return *aAverageAttrList.GetObject(nRow);
//STRIP001 }
//STRIP001 void ChartModel::ChangeAverageAttr(const SfxItemSet &rAttr,long nRow,BOOL bMerge)
//STRIP001 {
//STRIP001  PutAverageAttr(nRow,rAttr,bMerge);
//STRIP001  BuildChart (FALSE);
//STRIP001 }

//STRIP001 void ChartModel::PutErrorAttr( long nRow, const SfxItemSet &rAttr, BOOL bMerge )
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001      aErrorAttrList.GetObject(nRow)->ClearItem();
//STRIP001  aErrorAttrList.GetObject(nRow)->Put(rAttr);
//STRIP001 }
//STRIP001 const SfxItemSet& ChartModel::GetErrorAttr( long nRow ) const
//STRIP001 {
//STRIP001  return *aErrorAttrList.GetObject(nRow);
//STRIP001 }
//STRIP001 void ChartModel::ChangeErrorAttr(const SfxItemSet &rAttr,long nRow,BOOL bMerge)
//STRIP001 {
//STRIP001  PutErrorAttr(nRow, rAttr,bMerge);
//STRIP001  BuildChart (FALSE);
//STRIP001 }

/*N*/ SvNumberFormatter* ChartModel::GetNumFormatter() const
/*N*/ {
/*N*/   return pNumFormatter;
/*N*/ }

//STRIP001 SvxChartKindError ChartModel::ChartKindError () const
//STRIP001 {
//STRIP001  return eErrorKind;
//STRIP001 }


//STRIP001 SvxChartKindError& ChartModel::ChartKindError ()
//STRIP001 {
//STRIP001  return eErrorKind;
//STRIP001 }


//STRIP001 SvxChartIndicate ChartModel::ChartIndicate () const
//STRIP001 {
//STRIP001  return eIndicate;
//STRIP001 }


//STRIP001 SvxChartIndicate& ChartModel::ChartIndicate ()
//STRIP001 {
//STRIP001  return eIndicate;
//STRIP001 }


//STRIP001 SvxChartRegress ChartModel::ChartRegress () const
//STRIP001 {
//STRIP001  return eRegression;
//STRIP001 }


//STRIP001 SvxChartRegress& ChartModel::ChartRegress ()
//STRIP001 {
//STRIP001  return eRegression;
//STRIP001 }


//STRIP001 double ChartModel::IndicatePercent () const
//STRIP001 {
//STRIP001  return fIndicatePercent;
//STRIP001 }


//STRIP001 double& ChartModel::IndicatePercent ()
//STRIP001 {
//STRIP001  return fIndicatePercent;
//STRIP001 }


//STRIP001 double ChartModel::IndicateBigError () const
//STRIP001 {
//STRIP001  return fIndicateBigError;
//STRIP001 }


//STRIP001 double& ChartModel::IndicateBigError ()
//STRIP001 {
//STRIP001  return fIndicateBigError;
//STRIP001 }


//STRIP001 double ChartModel::IndicatePlus () const
//STRIP001 {
//STRIP001  return fIndicatePlus;
//STRIP001 }


//STRIP001 double& ChartModel::IndicatePlus ()
//STRIP001 {
//STRIP001  return fIndicatePlus;
//STRIP001 }


//STRIP001 double ChartModel::IndicateMinus () const
//STRIP001 {
//STRIP001  return fIndicateMinus;
//STRIP001 }


//STRIP001 double& ChartModel::IndicateMinus ()
//STRIP001 {
//STRIP001  return fIndicateMinus;
//STRIP001 }

//STRIP001 int ChartModel::Granularity () const
//STRIP001 {
//STRIP001  return nGranularity;
//STRIP001 }


/*N*/ int& ChartModel::Granularity ()
/*N*/ {
/*N*/   return nGranularity;
/*N*/ }


//STRIP001 const Size& ChartModel::InitialSize () const
//STRIP001 {
//STRIP001  return aInitialSize;
//STRIP001 }


/*N*/ Size& ChartModel::InitialSize ()
/*N*/ {
/*N*/   return aInitialSize;
/*N*/ }


//STRIP001 SvxChartStyle ChartModel::OldChartStyle () const
//STRIP001 {
//STRIP001  return eOldChartStyle;
//STRIP001 }


//STRIP001 SvxChartStyle &ChartModel::OldChartStyle ()
//STRIP001 {
//STRIP001  return eOldChartStyle;
//STRIP001 }


//STRIP001 long ChartModel::PieHeight () const
//STRIP001 {
//STRIP001  return nPieHeight;
//STRIP001 }


//STRIP001 long& ChartModel::PieHeight ()
//STRIP001 {
//STRIP001  return nPieHeight;
//STRIP001 }


//STRIP001 short ChartModel::PieSegCount () const
//STRIP001 {
//STRIP001  return nPieSegCount;
//STRIP001 }


//STRIP001 short& ChartModel::PieSegCount ()
//STRIP001 {
//STRIP001  return nPieSegCount;
//STRIP001 }


//STRIP001 void ChartModel::SetAngles (short nNewXAngle,
//STRIP001                          short nNewYAngle,
//STRIP001                          short nNewZAngle)
//STRIP001 {
//STRIP001  nXAngle = nNewXAngle;
//STRIP001  nYAngle = nNewYAngle;
//STRIP001  nZAngle = nNewZAngle;
//STRIP001 }


//STRIP001 void ChartModel::GetAngles (short &rNewXAngle,
//STRIP001                          short &rNewYAngle,
//STRIP001                          short &rNewZAngle)
//STRIP001 {
//STRIP001  rNewXAngle = nXAngle;
//STRIP001  rNewYAngle = nYAngle;
//STRIP001  rNewZAngle = nZAngle;
//STRIP001 }


/*N*/ void ChartModel::SetPieSegOfs( long nCol, long nOfs )
/*N*/ {
/*N*/     DBG_ASSERT( pPieSegOfs, "Invalid Array" );
/*N*/     DBG_ASSERT( nCol < nPieSegCount, "trying to set pie offset out of bounds" );
/*N*/
/*N*/     if( nCol < nPieSegCount )
/*N*/         pPieSegOfs[ nCol ] = nOfs;
/*N*/ }


/*N*/ String& ChartModel::ColText( long nCol )
/*N*/ {
/*N*/   return IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/              ? (String&) pChartData->GetTransRowText(nCol)
/*N*/              : (String&) pChartData->GetTransColText(nCol);
/*N*/ }


/*N*/ String& ChartModel::RowText( long nRow )
/*N*/ {
/*N*/   return IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/              ? (String&) pChartData->GetTransColText(nRow)
/*N*/              : (String&) pChartData->GetTransRowText(nRow);
/*N*/ }

//STRIP001 void ChartModel::SetItemSetLists(const ChartModel &rSource)
//STRIP001 {
//STRIP001
//STRIP001  CHART_TRACE( "ChartModel::SetItemSetLists" );
//STRIP001
//STRIP001
//STRIP001  long i,nCount;
//STRIP001
//STRIP001
//STRIP001  ClearItemSetLists(); //An dieser Stelle sind die Listen bereits mit default-werten gefuellt!
//STRIP001
//STRIP001  nCount=rSource.aDataRowAttrList.Count();
//STRIP001  SfxItemSet  *   pAttributes;
//STRIP001  for (i=0;i<nCount;i++)
//STRIP001  {
//STRIP001      SfxItemSet *pDataRowAttr = new SfxItemSet (*pItemPool, nRowWhichPairs);
//STRIP001      pDataRowAttr->Put(*(rSource.aDataRowAttrList.GetObject(i)));
//STRIP001      aDataRowAttrList.Insert (pDataRowAttr, LIST_APPEND);
//STRIP001  }
//STRIP001
//STRIP001  nCount=rSource.aDataPointAttrList.Count();
//STRIP001  for (i=0;i<nCount;i++)
//STRIP001   {
//STRIP001      pAttributes = rSource.aDataPointAttrList.GetObject(i);
//STRIP001      if (pAttributes == NULL)
//STRIP001          aDataPointAttrList.Insert (NULL, LIST_APPEND);
//STRIP001      else
//STRIP001      {
//STRIP001          SfxItemSet* pSet=new SfxItemSet(*pItemPool, nRowWhichPairs);
//STRIP001          pSet->Put(*pAttributes);
//STRIP001          aDataPointAttrList.Insert (pSet, LIST_APPEND);
//STRIP001      }
//STRIP001   }
//STRIP001
//STRIP001  nCount=rSource.aSwitchDataPointAttrList.Count();
//STRIP001  for (i=0;i<nCount;i++)
//STRIP001   {
//STRIP001      pAttributes = rSource.aSwitchDataPointAttrList.GetObject(i);
//STRIP001      if (pAttributes == NULL)
//STRIP001          aSwitchDataPointAttrList.Insert (NULL, LIST_APPEND);
//STRIP001      else
//STRIP001      {
//STRIP001          SfxItemSet* pSet=new SfxItemSet(*pItemPool, nRowWhichPairs);
//STRIP001          pSet->Put(*pAttributes);
//STRIP001          aSwitchDataPointAttrList.Insert (pSet, LIST_APPEND);
//STRIP001      }
//STRIP001   }
//STRIP001
//STRIP001  nCount=rSource.aRegressAttrList.Count();
//STRIP001  for (i=0;i<nCount;i++)
//STRIP001   {
//STRIP001      SfxItemSet* pSet=new SfxItemSet(*pItemPool, nGridWhichPairs);
//STRIP001      pSet->Put(*(rSource.aRegressAttrList.GetObject(i)));
//STRIP001      aRegressAttrList.Insert (pSet, LIST_APPEND);
//STRIP001   }
//STRIP001
//STRIP001  nCount = rSource.aAverageAttrList.Count();
//STRIP001  for (i=0;i<nCount;i++)
//STRIP001   {
//STRIP001      SfxItemSet* pSet=new SfxItemSet(*pItemPool, nGridWhichPairs);
//STRIP001      pSet->Put(*(rSource.aAverageAttrList.GetObject(i)));
//STRIP001      aAverageAttrList.Insert (pSet, LIST_APPEND);
//STRIP001   }
//STRIP001
//STRIP001  nCount = rSource.aErrorAttrList.Count();
//STRIP001  for (i=0;i<nCount;i++)
//STRIP001   {
//STRIP001      SfxItemSet* pSet=new SfxItemSet(*pItemPool, nGridWhichPairs);
//STRIP001      pSet->Put(*(rSource.aErrorAttrList.GetObject(i)));
//STRIP001      aErrorAttrList.Insert (pSet, LIST_APPEND);
//STRIP001   }
//STRIP001 }

//STRIP001 void ChartModel::AllocPieSegOfs (long nPieSegCnt)
//STRIP001 {
//STRIP001  delete[] pPieSegOfs;
//STRIP001  pPieSegOfs = new long [nPieSegCnt];
//STRIP001     long i = nPieSegCnt;
//STRIP001     for( ; i < nPieSegCnt; i++ )
//STRIP001      pPieSegOfs[ i ] = 0;
//STRIP001 }


// FG: Ist eine Abfrage ob die Beschriftung eines Charts Zentriert unter einem Datenpunkt (Regelfall) steht
//     oder zentriert zwischen 2 Marken.
/*N*/ BOOL ChartModel::IsDescriptionCenteredUnderDataPoint ()
/*N*/ {
/*N*/   switch (eChartStyle)
/*N*/   {
/*N*/       case CHSTYLE_2D_STACKEDCOLUMN :
/*N*/       case CHSTYLE_2D_COLUMN :
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN :
/*N*/           return FALSE;

//          case CHSTYLE_2D_LINE :
//          case CHSTYLE_2D_STACKEDLINE :
//          case CHSTYLE_2D_PERCENTLINE :
//          case CHSTYLE_2D_LINESYMBOLS :
//          case CHSTYLE_2D_STACKEDLINESYM :
//          case CHSTYLE_2D_PERCENTLINESYM :
//          case CHSTYLE_2D_CUBIC_SPLINE :
//          case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL :
//          case CHSTYLE_2D_B_SPLINE :
//          case CHSTYLE_2D_B_SPLINE_SYMBOL :

//          case CHSTYLE_2D_XY :
//          case CHSTYLE_2D_XYSYMBOLS :
//          case CHSTYLE_2D_XY_LINE :
//          case CHSTYLE_2D_CUBIC_SPLINE_XY :
//          case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
//          case CHSTYLE_2D_B_SPLINE_XY :
//          case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :

//          case CHSTYLE_2D_BAR :
//          case CHSTYLE_2D_STACKEDBAR:
//          case CHSTYLE_2D_PERCENTBAR:

//          case CHSTYLE_2D_AREA :
//          case CHSTYLE_2D_PERCENTAREA :
//          case CHSTYLE_2D_STACKEDAREA :

//          case CHSTYLE_2D_STOCK_1:
//          case CHSTYLE_2D_STOCK_2:
//          case CHSTYLE_2D_STOCK_3:
//          case CHSTYLE_2D_STOCK_4:
/*N*/       default :
/*N*/           return TRUE;
/*N*/   }
/*N*/ }
/*N*/ void ChartModel::LockBuild()
/*N*/ {
/*N*/   bNoBuildChart=TRUE;
/*N*/ }
/*N*/ void ChartModel::UnlockBuild()
/*N*/ {
/*N*/   bNoBuildChart=FALSE;
/*N*/   if(bShouldBuildChart)
/*N*/       BuildChart(FALSE); //evtl. TRUE, um Ranges zu prüfen???
/*N*/
/*N*/   // force broadcast SFX_HINT_DOCCHANGED
/*N*/   SfxObjectShell* pObjSh = GetObjectShell();
/*N*/   if( pObjSh )
/*N*/   {
/*N*/       pObjSh->SetModified( pObjSh->IsModified());
/*N*/   }
/*N*/ }
/*N*/ BOOL ChartModel::IsLockedBuild()
/*N*/ {
/*N*/   return bNoBuildChart;
/*N*/ }

