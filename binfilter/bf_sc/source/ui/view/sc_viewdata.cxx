/*************************************************************************
 *
 *  $RCSfile: sc_viewdata.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:19 $
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

#ifdef PCH
#include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/adjitem.hxx>
#include <bf_svx/algitem.hxx>
#include <bf_svx/brshitem.hxx>
#include <svtools/colorcfg.hxx>
#include <bf_svx/editview.hxx>
#include <bf_svx/editstat.hxx>
#include <bf_svx/outliner.hxx>
#include <bf_svx/unolingu.hxx>

#include <vcl/svapp.hxx>
//#include <vcl/system.hxx>
#include <rtl/math.hxx>

#include "viewdata.hxx"
#include "docoptio.hxx"
#include "scmod.hxx"
#include "global.hxx"
#include "document.hxx"
#include "attrib.hxx"
#include "tabview.hxx"
#include "tabvwsh.hxx"
#include "docsh.hxx"
#include "bf_sc.hrc"
#include "patattr.hxx"
#include "editutil.hxx"
#include "scextopt.hxx"
#include "miscuno.hxx"
#include "unonames.hxx"
#include "inputopt.hxx"

#ifndef _XMLOFF_XMLUCONV_HXX
#include <bf_xmloff/xmluconv.hxx>
#endif

#ifndef _SC_VIEWSETTINGSSEQUENCEDEFINES_HXX
#include "ViewSettingsSequenceDefines.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

#define SC_GROWY_SMALL_EXTRA    100
#define SC_GROWY_BIG_EXTRA      200

#define TAG_TABBARWIDTH "tw:"

static BOOL bMoveArea = FALSE;              //! Member?
USHORT nEditAdjust = SVX_ADJUST_LEFT;       //! Member !!!

//==================================================================

/*N*/ ScViewDataTable::ScViewDataTable() :
/*N*/               nCurX( 0 ),
/*N*/               nCurY( 0 ),
/*N*/               bOldCurValid( FALSE ),
/*N*/               eHSplitMode( SC_SPLIT_NONE ),
/*N*/               eVSplitMode( SC_SPLIT_NONE ),
/*N*/               nHSplitPos( 0 ),
/*N*/               nVSplitPos( 0 ),
/*N*/               nFixPosX( 0 ),
/*N*/               nFixPosY( 0 ),
/*N*/               eWhichActive( SC_SPLIT_BOTTOMLEFT )
/*N*/ {
/*N*/   nPosX[0]=nPosX[1]=
/*N*/   nPosY[0]=nPosY[1]=0;
/*N*/   nTPosX[0]=nTPosX[1]=
/*N*/   nTPosY[0]=nTPosY[1]=0;
/*N*/   nMPosX[0]=nMPosX[1]=
/*N*/   nMPosY[0]=nMPosY[1]=0;
/*N*/   nPixPosX[0]=nPixPosX[1]=
/*N*/   nPixPosY[0]=nPixPosY[1]=0;
/*N*/ }

//STRIP001 ScViewDataTable::ScViewDataTable( const ScViewDataTable& rDataTable ) :
//STRIP001              nCurX( rDataTable.nCurX ),
//STRIP001              nCurY( rDataTable.nCurY ),
//STRIP001              bOldCurValid( rDataTable.bOldCurValid ),
//STRIP001              nOldCurX( rDataTable.nOldCurX ),
//STRIP001              nOldCurY( rDataTable.nOldCurY ),
//STRIP001              eHSplitMode( rDataTable.eHSplitMode ),
//STRIP001              eVSplitMode( rDataTable.eVSplitMode ),
//STRIP001              nHSplitPos( rDataTable.nHSplitPos ),
//STRIP001              nVSplitPos( rDataTable.nVSplitPos ),
//STRIP001              nFixPosX( rDataTable.nFixPosX ),
//STRIP001              nFixPosY( rDataTable.nFixPosY ),
//STRIP001              eWhichActive( rDataTable.eWhichActive )
//STRIP001 {
//STRIP001  nPosX[0]=rDataTable.nPosX[0];
//STRIP001  nPosX[1]=rDataTable.nPosX[1];
//STRIP001  nPosY[0]=rDataTable.nPosY[0];
//STRIP001  nPosY[1]=rDataTable.nPosY[1];
//STRIP001
//STRIP001  nTPosX[0]=rDataTable.nTPosX[0];
//STRIP001  nTPosX[1]=rDataTable.nTPosX[1];
//STRIP001  nTPosY[0]=rDataTable.nTPosY[0];
//STRIP001  nTPosY[1]=rDataTable.nTPosY[1];
//STRIP001
//STRIP001  nMPosX[0]=rDataTable.nMPosX[0];
//STRIP001  nMPosX[1]=rDataTable.nMPosX[1];
//STRIP001  nMPosY[0]=rDataTable.nMPosY[0];
//STRIP001  nMPosY[1]=rDataTable.nMPosY[1];
//STRIP001
//STRIP001  nPixPosX[0]=rDataTable.nPixPosX[0];
//STRIP001  nPixPosX[1]=rDataTable.nPixPosX[1];
//STRIP001  nPixPosY[0]=rDataTable.nPixPosY[0];
//STRIP001  nPixPosY[1]=rDataTable.nPixPosY[1];
//STRIP001 }

/*N*/ ScViewDataTable::~ScViewDataTable()
/*N*/ {
/*N*/ }

/*N*/ void ScViewDataTable::WriteUserDataSequence(uno::Sequence <beans::PropertyValue>& rSettings)
/*N*/ {
/*N*/   rSettings.realloc(SC_TABLE_VIEWSETTINGS_COUNT);
/*N*/   beans::PropertyValue* pSettings = rSettings.getArray();
/*N*/   if (pSettings)
/*N*/   {
/*N*/       pSettings[SC_CURSOR_X].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_CURSORPOSITIONX));
/*N*/       pSettings[SC_CURSOR_X].Value <<= sal_Int32(nCurX);
/*N*/       pSettings[SC_CURSOR_Y].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_CURSORPOSITIONY));
/*N*/       pSettings[SC_CURSOR_Y].Value <<= sal_Int32(nCurY);
/*N*/       pSettings[SC_HORIZONTAL_SPLIT_MODE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_HORIZONTALSPLITMODE));
/*N*/       pSettings[SC_HORIZONTAL_SPLIT_MODE].Value <<= sal_Int16(eHSplitMode);
/*N*/       pSettings[SC_VERTICAL_SPLIT_MODE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_VERTICALSPLITMODE));
/*N*/       pSettings[SC_VERTICAL_SPLIT_MODE].Value <<= sal_Int16(eVSplitMode);
/*N*/       pSettings[SC_HORIZONTAL_SPLIT_POSITION].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_HORIZONTALSPLITPOSITION));
/*N*/       if (eHSplitMode == SC_SPLIT_FIX)
/*N*/           pSettings[SC_HORIZONTAL_SPLIT_POSITION].Value <<= sal_Int32(nFixPosX);
/*N*/       else
/*N*/           pSettings[SC_HORIZONTAL_SPLIT_POSITION].Value <<= nHSplitPos;
/*N*/       pSettings[SC_VERTICAL_SPLIT_POSITION].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_VERTICALSPLITPOSITION));
/*N*/       if (eVSplitMode == SC_SPLIT_FIX)
/*N*/           pSettings[SC_VERTICAL_SPLIT_POSITION].Value <<= sal_Int32(nFixPosY);
/*N*/       else
/*N*/           pSettings[SC_VERTICAL_SPLIT_POSITION].Value <<= nVSplitPos;
/*N*/       pSettings[SC_ACTIVE_SPLIT_RANGE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_ACTIVESPLITRANGE));
/*N*/       pSettings[SC_ACTIVE_SPLIT_RANGE].Value <<= sal_Int16(eWhichActive);
/*N*/       pSettings[SC_POSITION_LEFT].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_POSITIONLEFT));
/*N*/       pSettings[SC_POSITION_LEFT].Value <<= sal_Int32(nPosX[SC_SPLIT_LEFT]);
/*N*/       pSettings[SC_POSITION_RIGHT].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_POSITIONRIGHT));
/*N*/       pSettings[SC_POSITION_RIGHT].Value <<= sal_Int32(nPosX[SC_SPLIT_RIGHT]);
/*N*/       pSettings[SC_POSITION_TOP].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_POSITIONTOP));
/*N*/       pSettings[SC_POSITION_TOP].Value <<= sal_Int32(nPosY[SC_SPLIT_TOP]);
/*N*/       pSettings[SC_POSITION_BOTTOM].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_POSITIONBOTTOM));
/*N*/       pSettings[SC_POSITION_BOTTOM].Value <<= sal_Int32(nPosY[SC_SPLIT_BOTTOM]);
/*N*/   }
/*N*/ }

//STRIP001 void ScViewDataTable::ReadUserDataSequence(const uno::Sequence <beans::PropertyValue>& aSettings)
//STRIP001 {
//STRIP001  sal_Int32 nCount(aSettings.getLength());
//STRIP001  DBG_ASSERT(nCount == SC_TABLE_VIEWSETTINGS_COUNT, " wrong Table View Settings count");
//STRIP001  sal_Int32 nTemp32(0);
//STRIP001  sal_Int16 nTemp16(0);
//STRIP001  sal_Int32 nTempPosV(0);
//STRIP001  sal_Int32 nTempPosH(0);
//STRIP001  for (sal_Int32 i = 0; i < nCount; i++)
//STRIP001  {
//STRIP001      ::rtl::OUString sName(aSettings[i].Name);
//STRIP001      if (sName.compareToAscii(SC_CURSORPOSITIONX) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp32;
//STRIP001          nCurX = static_cast<sal_uInt16>(nTemp32);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_CURSORPOSITIONY) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp32;
//STRIP001          nCurY = static_cast<sal_uInt16>(nTemp32);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_HORIZONTALSPLITMODE) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp16;
//STRIP001          eHSplitMode = static_cast<ScSplitMode>(nTemp16);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_VERTICALSPLITMODE) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp16;
//STRIP001          eVSplitMode = static_cast<ScSplitMode>(nTemp16);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_HORIZONTALSPLITPOSITION) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTempPosH;
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_VERTICALSPLITPOSITION) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTempPosV;
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_ACTIVESPLITRANGE) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp16;
//STRIP001          eWhichActive = static_cast<ScSplitPos>(nTemp16);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_POSITIONLEFT) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp32;
//STRIP001          nPosX[SC_SPLIT_LEFT] = static_cast<sal_uInt16>(nTemp32);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_POSITIONRIGHT) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp32;
//STRIP001          nPosX[SC_SPLIT_RIGHT] = static_cast<sal_uInt16>(nTemp32);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_POSITIONTOP) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp32;
//STRIP001          nPosY[SC_SPLIT_TOP] = static_cast<sal_uInt16>(nTemp32);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_POSITIONBOTTOM) == 0)
//STRIP001      {
//STRIP001          aSettings[i].Value >>= nTemp32;
//STRIP001          nPosY[SC_SPLIT_BOTTOM] = static_cast<sal_uInt16>(nTemp32);
//STRIP001      }
//STRIP001  }
//STRIP001  if (eHSplitMode == SC_SPLIT_FIX)
//STRIP001      nFixPosX = static_cast<sal_uInt16>(nTempPosH);
//STRIP001  else
//STRIP001      nHSplitPos = nTempPosH;
//STRIP001  if (eVSplitMode == SC_SPLIT_FIX)
//STRIP001      nFixPosY = static_cast<sal_uInt16>(nTempPosV);
//STRIP001  else
//STRIP001      nVSplitPos = nTempPosV;
//STRIP001 }

//==================================================================

/*N*/ ScViewData::ScViewData( ScDocShell* pDocSh, ScTabViewShell* pViewSh )
/*N*/   :   pDocShell   ( pDocSh ),
/*N*/       pViewShell  ( pViewSh ),
/*N*/       pDoc        ( NULL ),
/*N*/       pView       ( pViewSh ),
/*N*/       pOptions    ( new ScViewOptions ),
/*N*/       nTabNo      ( 0 ),
/*N*/       nRefTabNo   ( 0 ),
/*N*/       aZoomX      ( 1,1 ),
/*N*/       aZoomY      ( 1,1 ),
/*N*/       aPageZoomX  ( 3,5 ),                    // Page-Default: 60%
/*N*/       aPageZoomY  ( 3,5 ),
/*N*/       aLogicMode  ( MAP_100TH_MM ),
/*N*/       bIsRefMode  ( FALSE ),
/*N*/       eRefType    ( SC_REFTYPE_NONE ),
/*N*/       nFillMode   ( SC_FILL_NONE ),
/*N*/       bDelMarkValid( FALSE ),
/*N*/       bActive     ( TRUE ),                   //! wie initialisieren?
/*N*/       bPagebreak  ( FALSE ),
/*N*/       pSpellingView ( NULL )
/*N*/ {
/*N*/   SetGridMode     ( TRUE );
/*N*/   SetSyntaxMode   ( FALSE );
/*N*/   SetHeaderMode   ( TRUE );
/*N*/   SetTabMode      ( TRUE );
/*N*/   SetVScrollMode  ( TRUE );
/*N*/   SetHScrollMode  ( TRUE );
/*N*/   SetOutlineMode  ( TRUE );
/*N*/
/*N*/   aScrSize = Size( (long) ( STD_COL_WIDTH           * PIXEL_PER_TWIPS * OLE_STD_CELLS_X ),
/*N*/                    (long) ( ScGlobal::nStdRowHeight * PIXEL_PER_TWIPS * OLE_STD_CELLS_Y ) );
/*N*/   pTabData[0] = new ScViewDataTable;
/*N*/   for (USHORT i=1; i<=MAXTAB; i++) pTabData[i] = NULL;
/*N*/   pThisTab = pTabData[nTabNo];
/*N*/   for (i=0; i<4; i++)
/*N*/   {
/*N*/       pEditView[i] = NULL;
/*N*/       bEditActive[i] = FALSE;
/*N*/   }
/*N*/
/*N*/   nEditEndCol = nEditCol = nEditEndRow = nEditRow = 0;
/*N*/   nTabStartCol = SC_TABSTART_NONE;
/*N*/
/*N*/   if (pDocShell)
/*N*/   {
/*N*/       pDoc = pDocShell->GetDocument();
/*N*/       *pOptions = pDoc->GetViewOptions();
/*N*/   }
/*N*/
/*N*/   //  keine ausgeblendete Tabelle anzeigen:
/*N*/   if (pDoc && !pDoc->IsVisible(nTabNo))
/*N*/   {
/*?*/       while ( !pDoc->IsVisible(nTabNo) && pDoc->HasTable(nTabNo+1) )
/*?*/           ++nTabNo;
/*?*/
/*?*/       pTabData[nTabNo] = new ScViewDataTable;
/*?*/       pThisTab = pTabData[nTabNo];
/*N*/   }
/*N*/
/*N*/   CalcPPT();
/*N*/ }

//STRIP001 ScViewData::ScViewData( const ScViewData& rViewData )
//STRIP001  :   pDocShell   ( rViewData.pDocShell ),
//STRIP001      pViewShell  ( rViewData.pViewShell ),
//STRIP001      pDoc        ( rViewData.pDoc ),
//STRIP001      pView       ( rViewData.pView ),
//STRIP001      pOptions    ( new ScViewOptions( *(rViewData.pOptions) )  ),
//STRIP001      nTabNo      ( rViewData.nTabNo ),
//STRIP001      nRefTabNo   ( rViewData.nTabNo ),           // kein RefMode
//STRIP001      aZoomX      ( rViewData.aZoomX ),
//STRIP001      aZoomY      ( rViewData.aZoomY ),
//STRIP001      aPageZoomX  ( rViewData.aPageZoomX ),
//STRIP001      aPageZoomY  ( rViewData.aPageZoomY ),
//STRIP001      aLogicMode  ( rViewData.aLogicMode ),
//STRIP001      bIsRefMode  ( FALSE ),
//STRIP001      eRefType    ( SC_REFTYPE_NONE ),
//STRIP001      nFillMode   ( SC_FILL_NONE ),
//STRIP001      bDelMarkValid( FALSE ),
//STRIP001      bActive     ( TRUE ),                               //! wie initialisieren?
//STRIP001      bPagebreak  ( rViewData.bPagebreak ),
//STRIP001      pSpellingView ( rViewData.pSpellingView )
//STRIP001 {
//STRIP001  SetGridMode     ( rViewData.IsGridMode() );
//STRIP001  SetSyntaxMode   ( rViewData.IsSyntaxMode() );
//STRIP001  SetHeaderMode   ( rViewData.IsHeaderMode() );
//STRIP001  SetTabMode      ( rViewData.IsTabMode() );
//STRIP001  SetVScrollMode  ( rViewData.IsVScrollMode() );
//STRIP001  SetHScrollMode  ( rViewData.IsHScrollMode() );
//STRIP001  SetOutlineMode  ( rViewData.IsOutlineMode() );
//STRIP001
//STRIP001  aScrSize = rViewData.aScrSize;
//STRIP001  for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001      if (rViewData.pTabData[i])
//STRIP001          pTabData[i] = new ScViewDataTable( *rViewData.pTabData[i] );
//STRIP001      else
//STRIP001          pTabData[i] = NULL;
//STRIP001  pThisTab = pTabData[nTabNo];
//STRIP001  for (i=0; i<4; i++)
//STRIP001  {
//STRIP001      pEditView[i] = NULL;
//STRIP001      bEditActive[i] = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  nEditEndCol = nEditCol = nEditEndRow = nEditRow = 0;
//STRIP001  nTabStartCol = SC_TABSTART_NONE;
//STRIP001  CalcPPT();
//STRIP001 }

//STRIP001 void ScViewData::SetDocShell( ScDocShell* pShell )
//STRIP001 {
//STRIP001  pDocShell = pShell;
//STRIP001  pDoc = pDocShell->GetDocument();
//STRIP001  *pOptions = pDoc->GetViewOptions();
//STRIP001  CalcPPT();
//STRIP001 }

//STRIP001 void ScViewData::InitData( ScDocument* pDocument )
//STRIP001 {
//STRIP001  pDoc = pDocument;
//STRIP001  *pOptions = pDoc->GetViewOptions();
//STRIP001 }

//STRIP001 void ScViewData::InitFrom( const ScViewData* pRef )
//STRIP001 {
//STRIP001  if (pRef==NULL)
//STRIP001  {
//STRIP001      DBG_ERROR("ScViewData::InitFrom mit NULL");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  aScrSize    = pRef->aScrSize;
//STRIP001  nTabNo      = pRef->nTabNo;
//STRIP001  aZoomX      = pRef->aZoomX;
//STRIP001  aZoomY      = pRef->aZoomY;
//STRIP001  aPageZoomX  = pRef->aPageZoomX;
//STRIP001  aPageZoomY  = pRef->aPageZoomY;
//STRIP001  bPagebreak  = pRef->bPagebreak;
//STRIP001  aLogicMode  = pRef->aLogicMode;
//STRIP001
//STRIP001  SetGridMode     ( pRef->IsGridMode() );
//STRIP001  SetSyntaxMode   ( pRef->IsSyntaxMode() );
//STRIP001  SetHeaderMode   ( pRef->IsHeaderMode() );
//STRIP001  SetTabMode      ( pRef->IsTabMode() );
//STRIP001  SetVScrollMode  ( pRef->IsVScrollMode() );
//STRIP001  SetHScrollMode  ( pRef->IsHScrollMode() );
//STRIP001  SetOutlineMode  ( pRef->IsOutlineMode() );
//STRIP001
//STRIP001  for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001  {
//STRIP001      delete pTabData[i];
//STRIP001      if (pRef->pTabData[i])
//STRIP001          pTabData[i] = new ScViewDataTable( *pRef->pTabData[i] );
//STRIP001      else
//STRIP001          pTabData[i] = NULL;
//STRIP001  }
//STRIP001  pThisTab = pTabData[nTabNo];
//STRIP001  CalcPPT();
//STRIP001 }

/*N*/ ScDocument* ScViewData::GetDocument() const
/*N*/ {
/*N*/   if (pDoc)
/*N*/       return pDoc;
/*N*/   else if (pDocShell)
/*?*/       return pDocShell->GetDocument();
/*N*/
/*N*/   DBG_ERROR("kein Document an ViewData");
/*N*/   return NULL;
/*N*/ }

/*N*/ ScViewData::~ScViewData()
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/       if (pTabData[i])
/*N*/           delete pTabData[i];
/*N*/
/*N*/   KillEditView();
/*N*/   delete pOptions;
/*N*/ }

/*N*/ void ScViewData::UpdateThis()
/*N*/ {
/*N*/   do
/*N*/   {
/*N*/       pThisTab = pTabData[nTabNo];
/*N*/       if (!pThisTab)
/*N*/       {
/*N*/           if (nTabNo>0)
/*N*/               --nTabNo;
/*N*/           else
/*?*/               pThisTab = pTabData[0] = new ScViewDataTable;
/*N*/
/*N*/               // hier keine Assertion, weil sonst Paints kommen, bevor alles initialisiert ist!
/*N*/       }
/*N*/   }
/*N*/   while (!pThisTab);
/*N*/ }

/*N*/ void ScViewData::InsertTab( USHORT nTab )
/*N*/ {
/*N*/   delete pTabData[MAXTAB];
/*N*/
/*N*/   for (USHORT i=MAXTAB; i>nTab; i--)
/*N*/       pTabData[i] = pTabData[i-1];
/*N*/
/*N*/   pTabData[nTab] = new ScViewDataTable;
/*N*/
/*N*/   UpdateThis();
/*N*/   aMarkData.InsertTab( nTab );
/*N*/ }

//STRIP001 void ScViewData::DeleteTab( USHORT nTab )
//STRIP001 {
//STRIP001  delete pTabData[nTab];
//STRIP001
//STRIP001  for (USHORT i=nTab; i<MAXTAB; i++)
//STRIP001      pTabData[i] = pTabData[i+1];
//STRIP001
//STRIP001  pTabData[MAXTAB] = NULL;
//STRIP001
//STRIP001  UpdateThis();
//STRIP001  aMarkData.DeleteTab( nTab );
//STRIP001 }

//STRIP001 void ScViewData::CopyTab( USHORT nSrcTab, USHORT nDestTab )
//STRIP001 {
//STRIP001  if (nDestTab==SC_TAB_APPEND)
//STRIP001      nDestTab = pDoc->GetTableCount() - 1;   // am Doc muss vorher kopiert worden sein
//STRIP001
//STRIP001  if (nDestTab > MAXTAB)
//STRIP001  {
//STRIP001      DBG_ERROR("Zuviele Tabellen");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  delete pTabData[MAXTAB];
//STRIP001
//STRIP001  for (USHORT i=MAXTAB; i>nDestTab; i--)
//STRIP001      pTabData[i] = pTabData[i-1];
//STRIP001
//STRIP001  if ( pTabData[nSrcTab] )
//STRIP001      pTabData[nDestTab] = new ScViewDataTable( *pTabData[nSrcTab] );
//STRIP001  else
//STRIP001      pTabData[nDestTab] = NULL;
//STRIP001
//STRIP001  UpdateThis();
//STRIP001  aMarkData.InsertTab( nDestTab );
//STRIP001 }

//STRIP001 void ScViewData::MoveTab( USHORT nSrcTab, USHORT nDestTab )
//STRIP001 {
//STRIP001  if (nDestTab==SC_TAB_APPEND)
//STRIP001      nDestTab = pDoc->GetTableCount() - 1;
//STRIP001
//STRIP001  USHORT i;
//STRIP001  ScViewDataTable* pTab = pTabData[nSrcTab];
//STRIP001
//STRIP001  USHORT nInsTab = nDestTab;
//STRIP001  if ( nSrcTab < nDestTab )
//STRIP001  {
//STRIP001      --nInsTab;
//STRIP001      for (i=nSrcTab; i<nDestTab; i++)
//STRIP001          pTabData[i] = pTabData[i+1];
//STRIP001  }
//STRIP001  else
//STRIP001      for (i=nSrcTab; i>nDestTab; i--)
//STRIP001          pTabData[i] = pTabData[i-1];
//STRIP001
//STRIP001  pTabData[nDestTab] = pTab;
//STRIP001
//STRIP001  UpdateThis();
//STRIP001  aMarkData.DeleteTab( nSrcTab );
//STRIP001  aMarkData.InsertTab( nInsTab );         // ggf. angepasst
//STRIP001 }

//STRIP001 void ScViewData::UpdateOle( ScSplitPos eWhich )
//STRIP001 {
//STRIP001  GetDocShell()->UpdateOle(this);
//STRIP001 }

/*N*/ void ScViewData::SetViewShell( ScTabViewShell* pViewSh )
/*N*/ {
/*N*/   if (pViewSh)
/*N*/   {
/*N*/       pViewShell  = pViewSh;
/*N*/       pView       = pViewSh;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pViewShell  = NULL;
/*N*/       pView       = NULL;
/*N*/   }
/*N*/ }

/*N*/ void ScViewData::SetZoom( const Fraction& rNewX, const Fraction& rNewY )
/*N*/ {
/*N*/   Fraction aFrac20( 1,5 );
/*N*/   Fraction aFrac400( 4,1 );
/*N*/
/*N*/   Fraction aValidX = rNewX;
/*N*/   if (aValidX<aFrac20) aValidX = aFrac20;
/*N*/   if (aValidX>aFrac400) aValidX = aFrac400;
/*N*/
/*N*/   Fraction aValidY = rNewY;
/*N*/   if (aValidY<aFrac20) aValidY = aFrac20;
/*N*/   if (aValidY>aFrac400) aValidY = aFrac400;
/*N*/
/*N*/   if ( bPagebreak )
/*N*/   {
/*N*/       aPageZoomX = aValidX;
/*N*/       aPageZoomY = aValidY;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aZoomX = aValidX;
/*N*/       aZoomY = aValidY;
/*N*/   }
/*N*/
/*N*/   CalcPPT();
/*N*/   RecalcPixPos();
/*N*/   aScenButSize = Size(0,0);
/*N*/   aLogicMode.SetScaleX( aValidX );
/*N*/   aLogicMode.SetScaleY( aValidY );
/*N*/ }

//STRIP001 void ScViewData::SetPagebreakMode( BOOL bSet )
//STRIP001 {
//STRIP001  bPagebreak = bSet;
//STRIP001
//STRIP001  CalcPPT();
//STRIP001  RecalcPixPos();
//STRIP001  aScenButSize = Size(0,0);
//STRIP001  aLogicMode.SetScaleX( GetZoomX() );
//STRIP001  aLogicMode.SetScaleY( GetZoomY() );
//STRIP001 }

/*M*/ BOOL ScViewData::GetSimpleArea( USHORT& rStartCol, USHORT& rStartRow, USHORT& rStartTab,
/*N*/                               USHORT& rEndCol, USHORT& rEndRow, USHORT& rEndTab )
/*N*/ {
/*N*/   //  parameter bMergeMark is no longer needed: The view's selection is never modified
/*N*/   //  (a local copy is used), and a multi selection that adds to a single range can always
/*N*/   //  be treated like a single selection (#108266# - GetSimpleArea isn't used in selection
/*N*/   //  handling itself)
/*N*/
/*N*/   ScMarkData aNewMark( aMarkData );       // use a local copy for MarkToSimple
/*N*/
/*N*/   if ( aNewMark.IsMarked() || aNewMark.IsMultiMarked() )
/*N*/   {
/*N*/       if ( aNewMark.IsMultiMarked() )
/*N*/           aNewMark.MarkToSimple();
/*M*/
/*M*/       if ( aNewMark.IsMarked() && !aNewMark.IsMultiMarked() )
/*M*/       {
/*M*/           ScRange aMarkRange;
/*M*/           aNewMark.GetMarkArea( aMarkRange );
/*M*/           rStartCol = aMarkRange.aStart.Col();
/*M*/           rStartRow = aMarkRange.aStart.Row();
/*M*/           rStartTab = aMarkRange.aStart.Tab();
/*M*/           rEndCol = aMarkRange.aEnd.Col();
/*M*/           rEndRow = aMarkRange.aEnd.Row();
/*M*/           rEndTab = aMarkRange.aEnd.Tab();
/*M*/       }
/*M*/       else
/*M*/       {
/*M*/           rStartCol = rEndCol = GetCurX();
/*M*/           rStartRow = rEndRow = GetCurY();
/*M*/           rStartTab = rEndTab = GetTabNo();
/*M*/           return FALSE;
/*M*/       }
/*M*/   }
/*M*/   else
/*M*/   {
/*M*/       rStartCol = rEndCol = GetCurX();
/*M*/       rStartRow = rEndRow = GetCurY();
/*M*/       rStartTab = rEndTab = GetTabNo();
/*M*/   }
/*M*/   return TRUE;
/*M*/ }

/*N*/ BOOL ScViewData::GetSimpleArea( ScRange& rRange )
/*N*/ {
/*N*/   //  parameter bMergeMark is no longer needed, see above
/*N*/
/*N*/   ScMarkData aNewMark( aMarkData );       // use a local copy for MarkToSimple
/*N*/
/*N*/   if ( aNewMark.IsMarked() || aNewMark.IsMultiMarked() )
/*N*/   {
/*?*/       if ( aNewMark.IsMultiMarked() )
/*?*/           aNewMark.MarkToSimple();
/*?*/
/*?*/       if ( aNewMark.IsMarked() && !aNewMark.IsMultiMarked() )
/*?*/           aNewMark.GetMarkArea( rRange );
/*?*/       else
/*?*/       {
/*?*/           rRange = ScRange( GetCurX(), GetCurY(), GetTabNo() );
/*?*/           return FALSE;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rRange = ScRange( GetCurX(), GetCurY(), GetTabNo() );
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

//STRIP001 void ScViewData::GetMultiArea( ScRangeListRef& rRange )
//STRIP001 {
//STRIP001  //  parameter bMergeMark is no longer needed, see GetSimpleArea
//STRIP001
//STRIP001  ScMarkData aNewMark( aMarkData );       // use a local copy for MarkToSimple
//STRIP001
//STRIP001  BOOL bMulti = aNewMark.IsMultiMarked();
//STRIP001  if (bMulti)
//STRIP001  {
//STRIP001      aNewMark.MarkToSimple();
//STRIP001      bMulti = aNewMark.IsMultiMarked();
//STRIP001  }
//STRIP001  if (bMulti)
//STRIP001  {
//STRIP001      rRange = new ScRangeList;
//STRIP001      aNewMark.FillRangeListWithMarks( rRange, FALSE );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ScRange aSimple;
//STRIP001      GetSimpleArea(aSimple);
//STRIP001      rRange = new ScRangeList;
//STRIP001      rRange->Append(aSimple);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ScViewData::SimpleColMarked()
//STRIP001 {
//STRIP001  USHORT nStartCol;
//STRIP001  USHORT nStartRow;
//STRIP001  USHORT nStartTab;
//STRIP001  USHORT nEndCol;
//STRIP001  USHORT nEndRow;
//STRIP001  USHORT nEndTab;
//STRIP001  if (GetSimpleArea(nStartCol,nStartRow,nStartTab,nEndCol,nEndRow,nEndTab))
//STRIP001      if (nStartRow==0 && nEndRow==MAXROW)
//STRIP001          return TRUE;
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ScViewData::SimpleRowMarked()
//STRIP001 {
//STRIP001  USHORT nStartCol;
//STRIP001  USHORT nStartRow;
//STRIP001  USHORT nStartTab;
//STRIP001  USHORT nEndCol;
//STRIP001  USHORT nEndRow;
//STRIP001  USHORT nEndTab;
//STRIP001  if (GetSimpleArea(nStartCol,nStartRow,nStartTab,nEndCol,nEndRow,nEndTab))
//STRIP001      if (nStartCol==0 && nEndCol==MAXCOL)
//STRIP001          return TRUE;
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

/*M*/ BOOL ScViewData::IsMultiMarked()
/*M*/ {
/*M*/   // test for "real" multi selection, calling MarkToSimple on a local copy
/*M*/
/*M*/   if ( aMarkData.IsMultiMarked() )
/*M*/   {
/*M*/       ScMarkData aNewMark( aMarkData );       // use a local copy for MarkToSimple
/*M*/       aNewMark.MarkToSimple();
/*M*/       if ( aNewMark.IsMultiMarked() )
/*M*/           return TRUE;
/*M*/   }
/*M*/   return FALSE;
/*M*/ }

//STRIP001 void ScViewData::SetFillMode( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow )
//STRIP001 {
//STRIP001  nFillMode   = SC_FILL_FILL;
//STRIP001  nFillStartX = nStartCol;
//STRIP001  nFillStartY = nStartRow;
//STRIP001  nFillEndX   = nEndCol;
//STRIP001  nFillEndY   = nEndRow;
//STRIP001 }

//STRIP001 void ScViewData::SetDragMode( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
//STRIP001                              BYTE nMode )
//STRIP001 {
//STRIP001  nFillMode   = nMode;
//STRIP001  nFillStartX = nStartCol;
//STRIP001  nFillStartY = nStartRow;
//STRIP001  nFillEndX   = nEndCol;
//STRIP001  nFillEndY   = nEndRow;
//STRIP001 }

//STRIP001 void ScViewData::ResetFillMode()
//STRIP001 {
//STRIP001  nFillMode   = SC_FILL_NONE;
//STRIP001 }

//STRIP001 void ScViewData::GetFillData( USHORT& rStartCol, USHORT& rStartRow,
//STRIP001                              USHORT& rEndCol, USHORT& rEndRow )
//STRIP001 {
//STRIP001  rStartCol = nFillStartX;
//STRIP001  rStartRow = nFillStartY;
//STRIP001  rEndCol   = nFillEndX;
//STRIP001  rEndRow   = nFillEndY;
//STRIP001 }

//STRIP001 USHORT ScViewData::GetOldCurX() const
//STRIP001 {
//STRIP001  if (pThisTab->bOldCurValid)
//STRIP001      return pThisTab->nOldCurX;
//STRIP001  else
//STRIP001      return pThisTab->nCurX;
//STRIP001 }
//STRIP001
//STRIP001 USHORT ScViewData::GetOldCurY() const
//STRIP001 {
//STRIP001  if (pThisTab->bOldCurValid)
//STRIP001      return pThisTab->nOldCurY;
//STRIP001  else
//STRIP001      return pThisTab->nCurY;
//STRIP001 }
//STRIP001
//STRIP001 void ScViewData::SetOldCursor( USHORT nNewX, USHORT nNewY )
//STRIP001 {
//STRIP001  pThisTab->nOldCurX = nNewX;
//STRIP001  pThisTab->nOldCurY = nNewY;
//STRIP001  pThisTab->bOldCurValid = TRUE;
//STRIP001 }
//STRIP001
//STRIP001 void ScViewData::ResetOldCursor()
//STRIP001 {
//STRIP001  pThisTab->bOldCurValid = FALSE;
//STRIP001 }

//STRIP001 Rectangle ScViewData::GetEditArea( ScSplitPos eWhich, USHORT nPosX, USHORT nPosY,
//STRIP001                                  Window* pWin, const ScPatternAttr* pPattern,
//STRIP001                                  BOOL bForceToTop )
//STRIP001 {
//STRIP001  return ScEditUtil( pDoc, nPosX, nPosY, nTabNo, GetScrPos(nPosX,nPosY,eWhich,TRUE),
//STRIP001                      pWin, nPPTX, nPPTY, GetZoomX(), GetZoomY() ).
//STRIP001                          GetEditArea( pPattern, bForceToTop );
//STRIP001 }
//STRIP001
//STRIP001 void ScViewData::SetEditEngine( ScSplitPos eWhich,
//STRIP001                              ScEditEngineDefaulter* pNewEngine,
//STRIP001                              Window* pWin, USHORT nNewX, USHORT nNewY )
//STRIP001 {
//STRIP001  ScHSplitPos eHWhich = WhichH(eWhich);
//STRIP001
//STRIP001  BOOL bWasThere = FALSE;
//STRIP001  if (pEditView[eWhich])
//STRIP001  {
//STRIP001      //  Wenn die View schon da ist, nichts aufrufen, was die Cursorposition aendert
//STRIP001
//STRIP001      if (bEditActive[eWhich])
//STRIP001          bWasThere = TRUE;
//STRIP001      else
//STRIP001          pEditView[eWhich]->SetEditEngine(pNewEngine);
//STRIP001
//STRIP001      if (pEditView[eWhich]->GetWindow() != pWin)
//STRIP001      {
//STRIP001          pEditView[eWhich]->SetWindow(pWin);
//STRIP001          DBG_ERROR("EditView Window geaendert");
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pEditView[eWhich] = new EditView( pNewEngine, pWin );
//STRIP001  }
//STRIP001
//STRIP001  //  bei IdleFormat wird manchmal ein Cursor gemalt, wenn die View schon weg ist (23576)
//STRIP001
//STRIP001  ULONG nEC = pNewEngine->GetControlWord();
//STRIP001  pNewEngine->SetControlWord(nEC & ~EE_CNTRL_DOIDLEFORMAT);
//STRIP001
//STRIP001  ULONG nVC = pEditView[eWhich]->GetControlWord();
//STRIP001  pEditView[eWhich]->SetControlWord(nVC & ~EV_CNTRL_AUTOSCROLL);
//STRIP001
//STRIP001  bEditActive[eWhich] = TRUE;
//STRIP001
//STRIP001  const ScPatternAttr* pPattern = pDoc->GetPattern( nNewX, nNewY, nTabNo );
//STRIP001  SvxCellHorJustify eJust = (SvxCellHorJustify)((const SvxHorJustifyItem&)
//STRIP001                                  pPattern->GetItem( ATTR_HOR_JUSTIFY )).GetValue();
//STRIP001
//STRIP001  BOOL bBreak = ( eJust == SVX_HOR_JUSTIFY_BLOCK ) ||
//STRIP001                  ((SfxBoolItem&)pPattern->GetItem(ATTR_LINEBREAK)).GetValue();
//STRIP001
//STRIP001  BOOL bAsianVertical = pNewEngine->IsVertical();     // set by InputHandler
//STRIP001
//STRIP001  Rectangle aPixRect = ScEditUtil( pDoc, nNewX,nNewY,nTabNo, GetScrPos(nNewX,nNewY,eWhich),
//STRIP001                                      pWin, nPPTX,nPPTY,GetZoomX(),GetZoomY() ).
//STRIP001                                          GetEditArea( pPattern, TRUE );
//STRIP001
//STRIP001  //  when right-aligned, leave space for the cursor
//STRIP001  //  in vertical mode, editing is always right-aligned
//STRIP001  if ( nEditAdjust == SVX_ADJUST_RIGHT || bAsianVertical )
//STRIP001      aPixRect.Right() += 1;
//STRIP001
//STRIP001  Rectangle aOutputArea = pWin->PixelToLogic( aPixRect, GetLogicMode() );
//STRIP001  pEditView[eWhich]->SetOutputArea( aOutputArea );
//STRIP001
//STRIP001  if ( bActive && eWhich == GetActivePart() )
//STRIP001  {
//STRIP001      //  modify members nEditCol etc. only if also extending for needed area
//STRIP001      nEditCol = nNewX;
//STRIP001      nEditRow = nNewY;
//STRIP001      const ScMergeAttr* pMergeAttr = (ScMergeAttr*)&pPattern->GetItem(ATTR_MERGE);
//STRIP001      nEditEndCol = nEditCol;
//STRIP001      if (pMergeAttr->GetColMerge() > 1)
//STRIP001          nEditEndCol += pMergeAttr->GetColMerge() - 1;
//STRIP001      nEditEndRow = nEditRow;
//STRIP001      if (pMergeAttr->GetRowMerge() > 1)
//STRIP001          nEditEndRow += pMergeAttr->GetRowMerge() - 1;
//STRIP001
//STRIP001      long nSizeXPix;
//STRIP001      if (bBreak && !bAsianVertical)
//STRIP001          nSizeXPix = aPixRect.GetWidth();    // Papersize -> kein H-Scrolling
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ASSERT(pView,"keine View fuer EditView");
//STRIP001          nSizeXPix = pView->GetGridWidth(eHWhich) - aPixRect.Left();
//STRIP001
//STRIP001          if ( nSizeXPix <= 0 )
//STRIP001              nSizeXPix = aPixRect.GetWidth();    // editing outside to the right of the window -> keep cell width
//STRIP001      }
//STRIP001      DBG_ASSERT(pView,"keine View fuer EditView");
//STRIP001      long nSizeYPix = pView->GetGridHeight(WhichV(eWhich)) - aPixRect.Top();
//STRIP001      if ( nSizeYPix <= 0 )
//STRIP001          nSizeYPix = aPixRect.GetHeight();   // editing outside below the window -> keep cell height
//STRIP001
//STRIP001      Size aPaperSize = pView->GetActiveWin()->PixelToLogic( Size( nSizeXPix, nSizeYPix ), GetLogicMode() );
//STRIP001      if ( bBreak && !bAsianVertical && SC_MOD()->GetInputOptions().GetTextWysiwyg() )
//STRIP001      {
//STRIP001          //  #95593# if text is formatted for printer, use the exact same paper width
//STRIP001          //  (and same line breaks) as for output.
//STRIP001
//STRIP001          Fraction aFract(1,1);
//STRIP001          Rectangle aUtilRect = ScEditUtil( pDoc,nNewX,nNewY,nTabNo, Point(0,0), pWin,
//STRIP001                                  HMM_PER_TWIPS, HMM_PER_TWIPS, aFract, aFract ).GetEditArea( pPattern, FALSE );
//STRIP001          aPaperSize.Width() = aUtilRect.GetWidth();
//STRIP001      }
//STRIP001      pNewEngine->SetPaperSize( aPaperSize );
//STRIP001
//STRIP001      // sichtbarer Ausschnitt
//STRIP001      Size aPaper = pNewEngine->GetPaperSize();
//STRIP001      Rectangle aVis = pEditView[eWhich]->GetVisArea();
//STRIP001      long nDiff = aVis.Right() - aVis.Left();
//STRIP001      if ( nEditAdjust == SVX_ADJUST_RIGHT )
//STRIP001      {
//STRIP001          aVis.Right() = aPaper.Width() - 1;
//STRIP001          bMoveArea = TRUE;
//STRIP001      }
//STRIP001      else if ( nEditAdjust == SVX_ADJUST_CENTER )
//STRIP001      {
//STRIP001          aVis.Right() = ( aPaper.Width() - 1 + nDiff ) / 2;
//STRIP001          bMoveArea = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aVis.Right() = nDiff;
//STRIP001          bMoveArea = FALSE;
//STRIP001      }
//STRIP001      aVis.Left() = aVis.Right() - nDiff;
//STRIP001      pEditView[eWhich]->SetVisArea(aVis);
//STRIP001      //
//STRIP001
//STRIP001      //  UpdateMode has been disabled in ScInputHandler::StartTable
//STRIP001      //  must be enabled before EditGrowY (GetTextHeight)
//STRIP001      pNewEngine->SetUpdateMode( TRUE );
//STRIP001
//STRIP001      pNewEngine->SetStatusEventHdl( LINK( this, ScViewData, EditEngineHdl ) );
//STRIP001
//STRIP001      EditGrowY( TRUE );      // adjust to existing text content
//STRIP001      EditGrowX();
//STRIP001
//STRIP001      Point aDocPos = pEditView[eWhich]->GetWindowPosTopLeft(0);
//STRIP001      if (aDocPos.Y() < aOutputArea.Top())
//STRIP001          pEditView[eWhich]->Scroll( 0, aOutputArea.Top() - aDocPos.Y() );
//STRIP001
//STRIP001      //!     Status (Event) zuruecksetzen
//STRIP001  }
//STRIP001
//STRIP001                                                  // hier muss bEditActive schon gesetzt sein
//STRIP001                                                  // (wegen Map-Mode bei Paint)
//STRIP001  if (!bWasThere)
//STRIP001      pNewEngine->InsertView(pEditView[eWhich]);
//STRIP001
//STRIP001  //      Hintergrundfarbe der Zelle
//STRIP001  Color aBackCol = ((const SvxBrushItem&)pPattern->GetItem(ATTR_BACKGROUND)).GetColor();
//STRIP001  ScModule* pScMod = SC_MOD();
//STRIP001  //  #105733# SvtAccessibilityOptions::GetIsForBorders is no longer used (always assumed TRUE)
//STRIP001  if ( aBackCol.GetTransparency() > 0 ||
//STRIP001          Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001  {
//STRIP001         aBackCol.SetColor( pScMod->GetColorConfig().GetColorValue(svtools::DOCCOLOR).nColor );
//STRIP001  }
//STRIP001  pEditView[eWhich]->SetBackgroundColor( aBackCol );
//STRIP001
//STRIP001  pEditView[eWhich]->Invalidate();            //  noetig ??
//STRIP001  //  noetig, wenn Position geaendert
//STRIP001 }

//STRIP001 IMPL_LINK_INLINE_START( ScViewData, EmptyEditHdl, EditStatus *, pStatus )
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }
//STRIP001 IMPL_LINK_INLINE_END( ScViewData, EmptyEditHdl, EditStatus *, pStatus )
//STRIP001
//STRIP001 IMPL_LINK( ScViewData, EditEngineHdl, EditStatus *, pStatus )
//STRIP001 {
//STRIP001  ULONG nStatus = pStatus->GetStatusWord();
//STRIP001  if (nStatus & (EE_STAT_HSCROLL | EE_STAT_TEXTHEIGHTCHANGED | EE_STAT_TEXTWIDTHCHANGED | EE_STAT_CURSOROUT))
//STRIP001  {
//STRIP001      EditGrowY();
//STRIP001      EditGrowX();
//STRIP001
//STRIP001      if (nStatus & EE_STAT_CURSOROUT)
//STRIP001      {
//STRIP001          ScSplitPos eWhich = GetActivePart();
//STRIP001          if (pEditView[eWhich])
//STRIP001              pEditView[eWhich]->ShowCursor(FALSE);
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void ScViewData::EditGrowX()
//STRIP001 {
//STRIP001  ScDocument* pDoc = GetDocument();
//STRIP001
//STRIP001  ScSplitPos eWhich = GetActivePart();
//STRIP001  ScHSplitPos eHWhich = WhichH(eWhich);
//STRIP001  EditView* pCurView = pEditView[eWhich];
//STRIP001
//STRIP001  if ( !pCurView || !bEditActive[eWhich])
//STRIP001      return;
//STRIP001
//STRIP001  ScEditEngineDefaulter* pEngine =
//STRIP001      (ScEditEngineDefaulter*) pCurView->GetEditEngine();
//STRIP001  Window* pWin = pCurView->GetWindow();
//STRIP001
//STRIP001  USHORT nRight = GetPosX(eHWhich) + VisibleCellsX(eHWhich);
//STRIP001
//STRIP001  Size        aSize = pEngine->GetPaperSize();
//STRIP001  Rectangle   aArea = pCurView->GetOutputArea();
//STRIP001  long        nOldRight = aArea.Right();
//STRIP001
//STRIP001  //  Margin ist schon bei der urspruenglichen Breite beruecksichtigt
//STRIP001  long nTextWidth = pEngine->CalcTextWidth();
//STRIP001
//STRIP001  BOOL bChanged = FALSE;
//STRIP001  while (aArea.GetWidth() + 0 < nTextWidth && nEditEndCol < nRight)
//STRIP001  {
//STRIP001      ++nEditEndCol;
//STRIP001      long nPix = ToPixel( pDoc->GetColWidth( nEditEndCol, nTabNo ), nPPTX );
//STRIP001      aArea.Right() += pWin->PixelToLogic(Size(nPix,0)).Width();
//STRIP001
//STRIP001      if ( aArea.Right() > aArea.Left() + aSize.Width() - 1 )
//STRIP001          aArea.Right() = aArea.Left() + aSize.Width() - 1;
//STRIP001
//STRIP001      bChanged = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if (bChanged)
//STRIP001  {
//STRIP001      if ( bMoveArea )
//STRIP001      {
//STRIP001          //  hart auf linksbuendig schalten und VisArea wieder nach links setzen
//STRIP001
//STRIP001          pEngine->SetDefaultItem( SvxAdjustItem( SVX_ADJUST_LEFT, EE_PARA_JUST ) );
//STRIP001
//STRIP001          Rectangle aVis = pCurView->GetVisArea();
//STRIP001          long nMove = aVis.Left();
//STRIP001          aVis.Left() = 0;
//STRIP001          aVis.Right() -= nMove;
//STRIP001          pCurView->SetVisArea( aVis );
//STRIP001          bMoveArea = FALSE;
//STRIP001      }
//STRIP001
//STRIP001      pCurView->SetOutputArea(aArea);
//STRIP001
//STRIP001      //  In vertical mode, the whole text is moved to the next cell (right-aligned),
//STRIP001      //  so everything must be repainted. Otherwise, paint only the new area.
//STRIP001      if ( !pEngine->IsVertical() )
//STRIP001          aArea.Left() = nOldRight;
//STRIP001      pWin->Invalidate(aArea);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScViewData::EditGrowY( BOOL bInitial )
//STRIP001 {
//STRIP001  ScSplitPos eWhich = GetActivePart();
//STRIP001  ScVSplitPos eVWhich = WhichV(eWhich);
//STRIP001  EditView* pCurView = pEditView[eWhich];
//STRIP001
//STRIP001  if ( !pCurView || !bEditActive[eWhich])
//STRIP001      return;
//STRIP001
//STRIP001  ULONG nControl = pEditView[eWhich]->GetControlWord();
//STRIP001  if ( nControl & EV_CNTRL_AUTOSCROLL )
//STRIP001  {
//STRIP001      //  if end of screen had already been reached and scrolling enabled,
//STRIP001      //  don't further try to grow the edit area
//STRIP001
//STRIP001      pCurView->SetOutputArea( pCurView->GetOutputArea() );   // re-align to pixels
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  EditEngine* pEngine = pCurView->GetEditEngine();
//STRIP001  Window* pWin = pCurView->GetWindow();
//STRIP001
//STRIP001  USHORT nBottom = GetPosY(eVWhich) + VisibleCellsY(eVWhich);
//STRIP001
//STRIP001  Size        aSize = pEngine->GetPaperSize();
//STRIP001  Rectangle   aArea = pCurView->GetOutputArea();
//STRIP001  long        nOldBottom = aArea.Bottom();
//STRIP001  long        nTextHeight = pEngine->GetTextHeight();
//STRIP001
//STRIP001  //  #106635# When editing a formula in a cell with optimal height, allow a larger portion
//STRIP001  //  to be clipped before extending to following rows, to avoid obscuring cells for
//STRIP001  //  reference input (next row is likely to be useful in formulas).
//STRIP001  long nAllowedExtra = SC_GROWY_SMALL_EXTRA;
//STRIP001  if ( nEditEndRow == nEditRow && !( pDoc->GetRowFlags( nEditRow, nTabNo ) & CR_MANUALSIZE ) &&
//STRIP001          pEngine->GetParagraphCount() <= 1 )
//STRIP001  {
//STRIP001      //  If the (only) paragraph starts with a '=', it's a formula.
//STRIP001      //  If this is the initial call and the text is empty, allow the larger value, too,
//STRIP001      //  because this occurs in the normal progress of editing a formula.
//STRIP001      //  Subsequent calls with empty text might involve changed attributes (including
//STRIP001      //  font height), so they are treated like normal text.
//STRIP001      String aText = pEngine->GetText( (USHORT) 0 );
//STRIP001      if ( ( aText.Len() == 0 && bInitial ) || aText.GetChar(0) == (sal_Unicode)'=' )
//STRIP001          nAllowedExtra = SC_GROWY_BIG_EXTRA;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bChanged = FALSE;
//STRIP001  BOOL bMaxReached = FALSE;
//STRIP001  while (aArea.GetHeight() + nAllowedExtra < nTextHeight && nEditEndRow < nBottom && !bMaxReached)
//STRIP001  {
//STRIP001      ++nEditEndRow;
//STRIP001      ScDocument* pDoc = GetDocument();
//STRIP001      long nPix = ToPixel( pDoc->GetRowHeight( nEditEndRow, nTabNo ), nPPTY );
//STRIP001      aArea.Bottom() += pWin->PixelToLogic(Size(0,nPix)).Height();
//STRIP001
//STRIP001      if ( aArea.Bottom() > aArea.Top() + aSize.Height() - 1 )
//STRIP001      {
//STRIP001          aArea.Bottom() = aArea.Top() + aSize.Height() - 1;
//STRIP001          bMaxReached = TRUE;     // don't occupy more cells beyond paper size
//STRIP001      }
//STRIP001
//STRIP001      bChanged = TRUE;
//STRIP001      nAllowedExtra = SC_GROWY_SMALL_EXTRA;   // larger value is only for first row
//STRIP001  }
//STRIP001
//STRIP001  if (bChanged)
//STRIP001  {
//STRIP001      pCurView->SetOutputArea(aArea);
//STRIP001
//STRIP001      if (nEditEndRow >= nBottom || bMaxReached)
//STRIP001      {
//STRIP001          if ((nControl & EV_CNTRL_AUTOSCROLL) == 0)
//STRIP001              pCurView->SetControlWord( nControl | EV_CNTRL_AUTOSCROLL );
//STRIP001      }
//STRIP001
//STRIP001      aArea.Top() = nOldBottom;
//STRIP001      pWin->Invalidate(aArea);
//STRIP001  }
//STRIP001 }

/*N*/ void ScViewData::ResetEditView()
/*N*/ {
/*N*/   EditEngine* pEngine = NULL;
/*N*/   for (USHORT i=0; i<4; i++)
/*N*/       if (pEditView[i])
/*N*/       {
/*?*/           if (bEditActive[i])
/*?*/           {
/*?*/               pEngine = pEditView[i]->GetEditEngine();
/*?*/               pEngine->RemoveView(pEditView[i]);
/*?*/               pEditView[i]->SetOutputArea( Rectangle() );
/*?*/           }
/*?*/           bEditActive[i] = FALSE;
/*N*/       }
/*N*/
/*N*/   if (pEngine)
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/      pEngine->SetStatusEventHdl( LINK( this, ScViewData, EmptyEditHdl ) );
/*N*/ }

/*N*/ void ScViewData::KillEditView()
/*N*/ {
/*N*/   for (USHORT i=0; i<4; i++)
/*N*/       if (pEditView[i])
/*N*/       {
/*?*/           if (bEditActive[i])
/*?*/               pEditView[i]->GetEditEngine()->RemoveView(pEditView[i]);
/*?*/           delete pEditView[i];
/*?*/           pEditView[i] = NULL;
/*N*/       }
/*N*/ }

//STRIP001 void ScViewData::GetEditView( ScSplitPos eWhich, EditView*& rViewPtr, USHORT& rCol, USHORT& rRow )
//STRIP001 {
//STRIP001  rViewPtr = pEditView[eWhich];
//STRIP001  rCol = nEditCol;
//STRIP001  rRow = nEditRow;
//STRIP001 }

//STRIP001 void ScViewData::SetTabNo( USHORT nNewTab )
//STRIP001 {
//STRIP001  if (nNewTab>MAXTAB)
//STRIP001  {
//STRIP001      DBG_ERROR("falsche Tabellennummer");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  nTabNo = nNewTab;
//STRIP001  if (!pTabData[nTabNo])
//STRIP001      pTabData[nTabNo] = new ScViewDataTable;
//STRIP001  pThisTab = pTabData[nTabNo];
//STRIP001
//STRIP001  CalcPPT();          //  for common column width correction
//STRIP001  RecalcPixPos();     //! nicht immer noetig!
//STRIP001 }

//STRIP001 void ScViewData::SetActivePart( ScSplitPos eNewActive )
//STRIP001 {
//STRIP001  pThisTab->eWhichActive = eNewActive;
//STRIP001 }

/*N*/ Point ScViewData::GetScrPos( USHORT nWhereX, USHORT nWhereY, ScHSplitPos eWhich ) const
/*N*/ {
/*N*/   DBG_ASSERT( eWhich==SC_SPLIT_LEFT || eWhich==SC_SPLIT_RIGHT, "Falsche Position" );
/*N*/   ScSplitPos ePos = ( eWhich == SC_SPLIT_LEFT ) ? SC_SPLIT_BOTTOMLEFT : SC_SPLIT_BOTTOMRIGHT;
/*N*/   return GetScrPos( nWhereX, nWhereY, ePos );
/*N*/ }

/*N*/ Point ScViewData::GetScrPos( USHORT nWhereX, USHORT nWhereY, ScVSplitPos eWhich ) const
/*N*/ {
/*N*/   DBG_ASSERT( eWhich==SC_SPLIT_TOP || eWhich==SC_SPLIT_BOTTOM, "Falsche Position" );
/*N*/   ScSplitPos ePos = ( eWhich == SC_SPLIT_TOP ) ? SC_SPLIT_TOPLEFT : SC_SPLIT_BOTTOMLEFT;
/*N*/   return GetScrPos( nWhereX, nWhereY, ePos );
/*N*/ }

/*N*/ Point ScViewData::GetScrPos( USHORT nWhereX, USHORT nWhereY, ScSplitPos eWhich,
/*N*/                               BOOL bAllowNeg ) const
/*N*/ {
/*N*/   ScHSplitPos eWhichX;
/*N*/   ScVSplitPos eWhichY;
/*N*/   switch( eWhich )
/*N*/   {
/*N*/       case SC_SPLIT_TOPLEFT:
/*N*/           eWhichX = SC_SPLIT_LEFT;
/*N*/           eWhichY = SC_SPLIT_TOP;
/*N*/           break;
/*N*/       case SC_SPLIT_TOPRIGHT:
/*N*/           eWhichX = SC_SPLIT_RIGHT;
/*N*/           eWhichY = SC_SPLIT_TOP;
/*N*/           break;
/*N*/       case SC_SPLIT_BOTTOMLEFT:
/*N*/           eWhichX = SC_SPLIT_LEFT;
/*N*/           eWhichY = SC_SPLIT_BOTTOM;
/*N*/           break;
/*N*/       case SC_SPLIT_BOTTOMRIGHT:
/*N*/           eWhichX = SC_SPLIT_RIGHT;
/*N*/           eWhichY = SC_SPLIT_BOTTOM;
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   if (pView)
/*N*/   {
/*N*/       ((ScViewData*)this)->aScrSize.Width()  = pView->GetGridWidth(eWhichX);
/*N*/       ((ScViewData*)this)->aScrSize.Height() = pView->GetGridHeight(eWhichY);
/*N*/   }
/*N*/
/*N*/   USHORT nTSize;
/*N*/
/*N*/   USHORT  nPosX = GetPosX(eWhichX);
/*N*/   USHORT  nX;
/*N*/
/*N*/   long nScrPosX=0;
/*N*/   if (nWhereX >= nPosX)
/*N*/       for (nX=nPosX; nX<nWhereX && (bAllowNeg || nScrPosX<=aScrSize.Width()); nX++)
/*N*/       {
/*N*/           if ( nX > MAXCOL )
/*N*/               nScrPosX = 65535;
/*N*/           else
/*N*/           {
/*N*/               nTSize = pDoc->GetColWidth( nX, nTabNo );
/*N*/               if (nTSize)
/*N*/               {
/*N*/                   long nSizeXPix = ToPixel( nTSize, nPPTX );
/*N*/                   nScrPosX += nSizeXPix;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   else if (bAllowNeg)
/*?*/       for (nX=nPosX; nX>nWhereX;)
/*?*/       {
/*?*/           --nX;
/*?*/           nTSize = pDoc->GetColWidth( nX, nTabNo );
/*?*/           if (nTSize)
/*?*/           {
/*?*/               long nSizeXPix = ToPixel( nTSize, nPPTX );
/*?*/               nScrPosX -= nSizeXPix;
/*?*/           }
/*?*/       }
/*N*/
/*N*/   USHORT  nPosY = GetPosY(eWhichY);
/*N*/   USHORT  nY;
/*N*/
/*N*/   long nScrPosY=0;
/*N*/   if (nWhereY >= nPosY)
/*N*/       for (nY=nPosY; nY<nWhereY && (bAllowNeg || nScrPosY<=aScrSize.Height()); nY++)
/*N*/       {
/*N*/           if ( nY > MAXROW )
/*N*/               nScrPosY = 65535;
/*N*/           else
/*N*/           {
/*N*/               nTSize = pDoc->FastGetRowHeight( nY, nTabNo );
/*N*/               if (nTSize)
/*N*/               {
/*N*/                   long nSizeYPix = ToPixel( nTSize, nPPTY );
/*N*/                   nScrPosY += nSizeYPix;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   else if (bAllowNeg)
/*?*/       for (nY=nPosY; nY>nWhereY;)
/*?*/       {
/*?*/           --nY;
/*?*/           nTSize = pDoc->FastGetRowHeight( nY, nTabNo );
/*?*/           if (nTSize)
/*?*/           {
/*?*/               long nSizeYPix = ToPixel( nTSize, nPPTY );
/*?*/               nScrPosY -= nSizeYPix;
/*?*/           }
/*?*/       }
/*N*/
/*N*/   if (nScrPosX > 32767) nScrPosX=32767;
/*N*/   if (nScrPosY > 32767) nScrPosY=32767;
/*N*/   return Point( nScrPosX, nScrPosY );
/*N*/ }

//
//      Anzahl Zellen auf einem Bildschirm
//

/*N*/ USHORT ScViewData::CellsAtX( short nPosX, short nDir, ScHSplitPos eWhichX, USHORT nScrSizeX ) const
/*N*/ {
/*N*/   DBG_ASSERT( nDir==1 || nDir==-1, "falscher CellsAt Aufruf" );
/*N*/
/*N*/   if (pView)
/*N*/       ((ScViewData*)this)->aScrSize.Width()  = pView->GetGridWidth(eWhichX);
/*N*/
/*N*/   short   nX;
/*N*/   USHORT  nScrPosX = 0;
/*N*/   if (nScrSizeX == SC_SIZE_NONE) nScrSizeX = (USHORT) aScrSize.Width();
/*N*/
/*N*/   if (nDir==1)
/*N*/       nX = nPosX;             // vorwaerts
/*N*/   else
/*N*/       nX = nPosX-1;           // rueckwaerts
/*N*/
/*N*/   BOOL bOut = FALSE;
/*N*/   for ( ; nScrPosX<=nScrSizeX && !bOut; nX+=nDir )
/*N*/   {
/*N*/       short   nColNo = nX;
/*N*/       if ( nColNo < 0 || nColNo > MAXCOL )
/*N*/           bOut = TRUE;
/*N*/       else
/*N*/       {
/*N*/           USHORT nTSize = pDoc->GetColWidth( nColNo, nTabNo );
/*N*/           if (nTSize)
/*N*/           {
/*N*/               long nSizeXPix = ToPixel( nTSize, nPPTX );
/*N*/               nScrPosX += (USHORT) nSizeXPix;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (nDir==1)
/*N*/       nX -= nPosX;
/*N*/   else
/*N*/       nX = (nPosX-1)-nX;
/*N*/
/*N*/   if (nX>0) --nX;
/*N*/   return nX;
/*N*/ }

/*N*/ USHORT ScViewData::CellsAtY( short nPosY, short nDir, ScVSplitPos eWhichY, USHORT nScrSizeY ) const
/*N*/ {
/*N*/   DBG_ASSERT( nDir==1 || nDir==-1, "falscher CellsAt Aufruf" );
/*N*/
/*N*/   if (pView)
/*N*/       ((ScViewData*)this)->aScrSize.Height() = pView->GetGridHeight(eWhichY);
/*N*/
/*N*/   short   nY;
/*N*/   USHORT  nScrPosY = 0;
/*N*/
/*N*/   if (nScrSizeY == SC_SIZE_NONE) nScrSizeY = (USHORT) aScrSize.Height();
/*N*/
/*N*/   if (nDir==1)
/*N*/       nY = nPosY;             // vorwaerts
/*N*/   else
/*N*/       nY = nPosY-1;           // rueckwaerts
/*N*/
/*N*/   BOOL bOut = FALSE;
/*N*/   for ( ; nScrPosY<=nScrSizeY && !bOut; nY+=nDir )
/*N*/   {
/*N*/       short   nRowNo = nY;
/*N*/       if ( nRowNo < 0 || nRowNo > MAXROW )
/*N*/           bOut = TRUE;
/*N*/       else
/*N*/       {
/*N*/ //            USHORT nTSize = pDoc->GetRowHeight( nRowNo, nTabNo );
/*N*/           USHORT nTSize = pDoc->FastGetRowHeight( nRowNo, nTabNo );
/*N*/           if (nTSize)
/*N*/           {
/*N*/               long nSizeYPix = ToPixel( nTSize, nPPTY );
/*N*/               nScrPosY += (USHORT) nSizeYPix;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (nDir==1)
/*N*/       nY -= nPosY;
/*N*/   else
/*N*/       nY = (nPosY-1)-nY;
/*N*/
/*N*/   if (nY>0) --nY;
/*N*/   return nY;
/*N*/ }

/*N*/ USHORT ScViewData::VisibleCellsX( ScHSplitPos eWhichX ) const
/*N*/ {
/*N*/   return CellsAtX( GetPosX( eWhichX ), 1, eWhichX, SC_SIZE_NONE );
/*N*/ }

/*N*/ USHORT ScViewData::VisibleCellsY( ScVSplitPos eWhichY ) const
/*N*/ {
/*N*/   return CellsAtY( GetPosY( eWhichY ), 1, eWhichY, SC_SIZE_NONE );
/*N*/ }

//STRIP001 USHORT ScViewData::PrevCellsX( ScHSplitPos eWhichX ) const
//STRIP001 {
//STRIP001  return CellsAtX( GetPosX( eWhichX ), -1, eWhichX, SC_SIZE_NONE );
//STRIP001 }
//STRIP001
//STRIP001 USHORT ScViewData::PrevCellsY( ScVSplitPos eWhichY ) const
//STRIP001 {
//STRIP001  return CellsAtY( GetPosY( eWhichY ), -1, eWhichY, SC_SIZE_NONE );
//STRIP001 }
//STRIP001
//STRIP001 USHORT ScViewData::LastCellsX( ScHSplitPos eWhichX ) const
//STRIP001 {
//STRIP001  return CellsAtX( MAXCOL+1, -1, eWhichX, SC_SIZE_NONE );
//STRIP001 }
//STRIP001
//STRIP001 USHORT ScViewData::LastCellsY( ScVSplitPos eWhichY ) const
//STRIP001 {
//STRIP001  return CellsAtY( MAXROW+1, -1, eWhichY, SC_SIZE_NONE );
//STRIP001 }

/*N*/ BOOL ScViewData::GetMergeSizePixel( USHORT nX, USHORT nY, long& rSizeXPix, long& rSizeYPix )
/*N*/ {
/*N*/   const ScMergeAttr* pMerge = (const ScMergeAttr*) pDoc->GetAttr( nX,nY,nTabNo, ATTR_MERGE );
/*N*/   if ( pMerge->GetColMerge() > 1 || pMerge->GetRowMerge() > 1 )
/*N*/   {
/*N*/       long nOutWidth = 0;
/*N*/       long nOutHeight = 0;
/*N*/       USHORT i;
/*N*/       USHORT nCountX = pMerge->GetColMerge();
/*N*/       for (i=0; i<nCountX; i++)
/*N*/           nOutWidth += ToPixel( pDoc->GetColWidth(nX+i,nTabNo), nPPTX );
/*N*/       USHORT nCountY = pMerge->GetRowMerge();
/*N*/       for (i=0; i<nCountY; i++)
/*N*/           nOutHeight += ToPixel( pDoc->GetRowHeight(nY+i,nTabNo), nPPTY );
/*N*/
/*N*/       rSizeXPix = nOutWidth;
/*N*/       rSizeYPix = nOutHeight;
/*N*/       return TRUE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rSizeXPix = ToPixel( pDoc->GetColWidth( nX, nTabNo ), nPPTX );
/*N*/       rSizeYPix = ToPixel( pDoc->GetRowHeight( nY, nTabNo ), nPPTY );
/*N*/       return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ScViewData::GetPosFromPixel( long nClickX, long nClickY, ScSplitPos eWhich,
/*N*/                                       short& rPosX, short& rPosY,
/*N*/                                       BOOL bTestMerge, BOOL bRepair, BOOL bNextIfLarge )
/*N*/ {
/*M*/   //  special handling of 0 is now in ScViewFunctionSet::SetCursorAtPoint
/*N*/
/*N*/   ScHSplitPos eHWhich = WhichH(eWhich);
/*N*/   ScVSplitPos eVWhich = WhichV(eWhich);
/*N*/   short nStartPosX = GetPosX(eHWhich);
/*N*/   short nStartPosY = GetPosY(eVWhich);
/*N*/   rPosX = nStartPosX;
/*N*/   rPosY = nStartPosY;
/*N*/   long nScrX = 0;
/*N*/   long nScrY = 0;
/*N*/
/*N*/   if (nClickX > 0)
/*N*/   {
/*N*/       while ( rPosX<=MAXCOL && nClickX >= nScrX )
/*N*/       {
/*N*/           nScrX += ToPixel( pDoc->GetColWidth( rPosX, nTabNo ), nPPTX );
/*N*/           ++rPosX;
/*N*/       }
/*N*/       --rPosX;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       while ( rPosX>0 && nClickX < nScrX )
/*N*/       {
/*N*/           --rPosX;
/*N*/           nScrX -= ToPixel( pDoc->GetColWidth( rPosX, nTabNo ), nPPTX );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (nClickY > 0)
/*N*/   {
/*N*/       while ( rPosY<=MAXROW && nClickY >= nScrY )
/*N*/       {
/*N*/           nScrY += ToPixel( pDoc->FastGetRowHeight( rPosY, nTabNo ), nPPTY );
/*N*/           ++rPosY;
/*N*/       }
/*N*/       --rPosY;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       while ( rPosY>0 && nClickY < nScrY )
/*N*/       {
/*N*/           --rPosY;
/*N*/           nScrY -= ToPixel( pDoc->FastGetRowHeight( rPosY, nTabNo ), nPPTY );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bNextIfLarge)       //  zu grosse Zellen ?
/*N*/   {
/*N*/       if ( rPosX == nStartPosX && nClickX > 0 )
/*N*/       {
/*N*/           if (pView)
/*N*/               aScrSize.Width() = pView->GetGridWidth(eHWhich);
/*N*/           if ( nClickX > aScrSize.Width() )
/*N*/               ++rPosX;
/*N*/       }
/*N*/       if ( rPosY == nStartPosY && nClickY > 0 )
/*N*/       {
/*N*/           if (pView)
/*N*/               aScrSize.Height() = pView->GetGridHeight(eVWhich);
/*N*/           if ( nClickY > aScrSize.Height() )
/*N*/               ++rPosY;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (rPosX<0) rPosX=0;
/*N*/   if (rPosX>MAXCOL) rPosX=MAXCOL;
/*N*/   if (rPosY<0) rPosY=0;
/*N*/   if (rPosY>MAXROW) rPosY=MAXROW;
/*N*/
/*N*/   if (bTestMerge)
/*N*/   {
/*?*/       //! public Methode um Position anzupassen
/*?*/
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 BOOL bHOver = FALSE;
//STRIP001 /*?*/        while (pDoc->IsHorOverlapped( rPosX, rPosY, nTabNo ))
//STRIP001 /*?*/            { --rPosX; bHOver=TRUE; }
//STRIP001 /*?*/        BOOL bVOver = FALSE;
//STRIP001 /*?*/        while (pDoc->IsVerOverlapped( rPosX, rPosY, nTabNo ))
//STRIP001 /*?*/            { --rPosY; bVOver=TRUE; }
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( bRepair && ( bHOver || bVOver ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            const ScMergeAttr* pMerge = (const ScMergeAttr*)
//STRIP001 /*?*/                                pDoc->GetAttr( rPosX, rPosY, nTabNo, ATTR_MERGE );
//STRIP001 /*?*/            if ( ( bHOver && pMerge->GetColMerge() <= 1 ) ||
//STRIP001 /*?*/                 ( bVOver && pMerge->GetRowMerge() <= 1 ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                DBG_ERROR("Merge-Fehler gefunden");
//STRIP001 /*?*/
//STRIP001 /*?*/                pDoc->RemoveFlagsTab( 0,0, MAXCOL,MAXROW, nTabNo, SC_MF_HOR | SC_MF_VER );
//STRIP001 /*?*/                USHORT nEndCol = MAXCOL;
//STRIP001 /*?*/                USHORT nEndRow = MAXROW;
//STRIP001 /*?*/                pDoc->ExtendMerge( 0,0, nEndCol,nEndRow, nTabNo, TRUE, FALSE );
//STRIP001 /*?*/                if (pDocShell)
//STRIP001 /*?*/                    pDocShell->PostPaint( ScRange(0,0,nTabNo,MAXCOL,MAXROW,nTabNo), PAINT_GRID );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

//STRIP001 void ScViewData::GetMouseQuadrant( const Point& rClickPos, ScSplitPos eWhich,
//STRIP001                                      short nPosX, short nPosY, BOOL& rLeft, BOOL& rTop )
//STRIP001 {
//STRIP001  Point aCellStart = GetScrPos( nPosX, nPosY, eWhich, TRUE );
//STRIP001  long nSizeX;
//STRIP001  long nSizeY;
//STRIP001  GetMergeSizePixel( nPosX, nPosY, nSizeX, nSizeY );
//STRIP001  rLeft = rClickPos.X() - aCellStart.X() <= nSizeX / 2;
//STRIP001  rTop  = rClickPos.Y() - aCellStart.Y() <= nSizeY / 2;
//STRIP001 }

//STRIP001 void ScViewData::SetPosX( ScHSplitPos eWhich, USHORT nNewPosX )
//STRIP001 {
//STRIP001  if (nNewPosX)
//STRIP001  {
//STRIP001      USHORT nOldPosX = pThisTab->nPosX[eWhich];
//STRIP001      long nTPosX = pThisTab->nTPosX[eWhich];
//STRIP001      long nPixPosX = pThisTab->nPixPosX[eWhich];
//STRIP001      USHORT i;
//STRIP001      if ( nNewPosX > nOldPosX )
//STRIP001          for ( i=nOldPosX; i<nNewPosX; i++ )
//STRIP001          {
//STRIP001              long nThis = pDoc->GetColWidth( i,nTabNo );
//STRIP001              nTPosX -= nThis;
//STRIP001              nPixPosX -= ToPixel(nThis, nPPTX);
//STRIP001          }
//STRIP001      else
//STRIP001          for ( i=nNewPosX; i<nOldPosX; i++ )
//STRIP001          {
//STRIP001              long nThis = pDoc->GetColWidth( i,nTabNo );
//STRIP001              nTPosX += nThis;
//STRIP001              nPixPosX += ToPixel(nThis, nPPTX);
//STRIP001          }
//STRIP001
//STRIP001      pThisTab->nPosX[eWhich] = nNewPosX;
//STRIP001      pThisTab->nTPosX[eWhich] = nTPosX;
//STRIP001      pThisTab->nMPosX[eWhich] = (long) (nTPosX * HMM_PER_TWIPS);
//STRIP001      pThisTab->nPixPosX[eWhich] = nPixPosX;
//STRIP001  }
//STRIP001  else
//STRIP001      pThisTab->nPixPosX[eWhich] =
//STRIP001      pThisTab->nTPosX[eWhich] =
//STRIP001      pThisTab->nMPosX[eWhich] =
//STRIP001      pThisTab->nPosX[eWhich] = 0;
//STRIP001 }

//STRIP001 void ScViewData::SetPosY( ScVSplitPos eWhich, USHORT nNewPosY )
//STRIP001 {
//STRIP001  if (nNewPosY)
//STRIP001  {
//STRIP001      USHORT nOldPosY = pThisTab->nPosY[eWhich];
//STRIP001      long nTPosY = pThisTab->nTPosY[eWhich];
//STRIP001      long nPixPosY = pThisTab->nPixPosY[eWhich];
//STRIP001      USHORT i;
//STRIP001      if ( nNewPosY > nOldPosY )
//STRIP001          for ( i=nOldPosY; i<nNewPosY; i++ )
//STRIP001          {
//STRIP001              long nThis = pDoc->FastGetRowHeight( i,nTabNo );
//STRIP001              nTPosY -= nThis;
//STRIP001              nPixPosY -= ToPixel(nThis, nPPTY);
//STRIP001          }
//STRIP001      else
//STRIP001          for ( i=nNewPosY; i<nOldPosY; i++ )
//STRIP001          {
//STRIP001              long nThis = pDoc->FastGetRowHeight( i,nTabNo );
//STRIP001              nTPosY += nThis;
//STRIP001              nPixPosY += ToPixel(nThis, nPPTY);
//STRIP001          }
//STRIP001
//STRIP001      pThisTab->nPosY[eWhich] = nNewPosY;
//STRIP001      pThisTab->nTPosY[eWhich] = nTPosY;
//STRIP001      pThisTab->nMPosY[eWhich] = (long) (nTPosY * HMM_PER_TWIPS);
//STRIP001      pThisTab->nPixPosY[eWhich] = nPixPosY;
//STRIP001  }
//STRIP001  else
//STRIP001      pThisTab->nPixPosY[eWhich] =
//STRIP001      pThisTab->nTPosY[eWhich] =
//STRIP001      pThisTab->nMPosY[eWhich] =
//STRIP001      pThisTab->nPosY[eWhich] = 0;
//STRIP001 }

/*N*/ void ScViewData::RecalcPixPos()               // nach Zoom-Aenderungen
/*N*/ {
/*N*/   USHORT i;
/*N*/
/*N*/   for (USHORT eWhich=0; eWhich<2; eWhich++)
/*N*/   {
/*N*/       long nPixPosX = 0;
/*N*/       USHORT nPosX = pThisTab->nPosX[eWhich];
/*N*/       for (i=0; i<nPosX; i++)
/*?*/           nPixPosX -= ToPixel(pDoc->GetColWidth(i,nTabNo), nPPTX);
/*N*/       pThisTab->nPixPosX[eWhich] = nPixPosX;
/*N*/
/*N*/       long nPixPosY = 0;
/*N*/       USHORT nPosY = pThisTab->nPosY[eWhich];
/*N*/       for (i=0; i<nPosY; i++)
/*?*/           nPixPosY -= ToPixel(pDoc->FastGetRowHeight(i,nTabNo), nPPTY);
/*N*/       pThisTab->nPixPosY[eWhich] = nPixPosY;
/*N*/   }
/*N*/ }

/*N*/ const MapMode& ScViewData::GetLogicMode( ScSplitPos eWhich )
/*N*/ {
/*N*/   aLogicMode.SetOrigin( Point( pThisTab->nMPosX[WhichH(eWhich)],
/*N*/                                   pThisTab->nMPosY[WhichV(eWhich)] ) );
/*N*/   return aLogicMode;
/*N*/ }

/*N*/ const MapMode& ScViewData::GetLogicMode()
/*N*/ {
/*N*/   aLogicMode.SetOrigin( Point() );
/*N*/   return aLogicMode;
/*N*/ }

//STRIP001 void ScViewData::SetScreen( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 )
//STRIP001 {
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  USHORT nTSize;
//STRIP001  long nSizePix;
//STRIP001  long nScrPosX = 0;
//STRIP001  long nScrPosY = 0;
//STRIP001
//STRIP001  SetActivePart( SC_SPLIT_BOTTOMLEFT );
//STRIP001  SetPosX( SC_SPLIT_LEFT, nCol1 );
//STRIP001  SetPosY( SC_SPLIT_BOTTOM, nRow1 );
//STRIP001
//STRIP001  for (nCol=nCol1; nCol<=nCol2; nCol++)
//STRIP001  {
//STRIP001      nTSize = pDoc->GetColWidth( nCol, nTabNo );
//STRIP001      if (nTSize)
//STRIP001      {
//STRIP001          nSizePix = ToPixel( nTSize, nPPTX );
//STRIP001          nScrPosX += (USHORT) nSizePix;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  for (nRow=nRow1; nRow<=nRow2; nRow++)
//STRIP001  {
//STRIP001      nTSize = pDoc->FastGetRowHeight( nRow, nTabNo );
//STRIP001      if (nTSize)
//STRIP001      {
//STRIP001          nSizePix = ToPixel( nTSize, nPPTY );
//STRIP001          nScrPosY += (USHORT) nSizePix;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aScrSize = Size( nScrPosX, nScrPosY );
//STRIP001 }

//STRIP001 void ScViewData::SetScreenPos( const Point& rVisAreaStart )
//STRIP001 {
//STRIP001  long nSize;
//STRIP001  long nTwips;
//STRIP001  long nAdd;
//STRIP001  BOOL bEnd;
//STRIP001
//STRIP001  nSize = 0;
//STRIP001  nTwips = (long) (rVisAreaStart.X() / HMM_PER_TWIPS);
//STRIP001  USHORT nX1 = 0;
//STRIP001  bEnd = FALSE;
//STRIP001  while (!bEnd)
//STRIP001  {
//STRIP001      nAdd = (long) pDoc->GetColWidth(nX1,nTabNo);
//STRIP001      if (nSize+nAdd <= nTwips+1 && nX1<MAXCOL)
//STRIP001      {
//STRIP001          nSize += nAdd;
//STRIP001          ++nX1;
//STRIP001      }
//STRIP001      else
//STRIP001          bEnd = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  nSize = 0;
//STRIP001  nTwips = (long) (rVisAreaStart.Y() / HMM_PER_TWIPS);
//STRIP001  USHORT nY1 = 0;
//STRIP001  bEnd = FALSE;
//STRIP001  while (!bEnd)
//STRIP001  {
//STRIP001      nAdd = (long) pDoc->FastGetRowHeight(nY1,nTabNo);
//STRIP001      if (nSize+nAdd <= nTwips+1 && nY1<MAXROW)
//STRIP001      {
//STRIP001          nSize += nAdd;
//STRIP001          ++nY1;
//STRIP001      }
//STRIP001      else
//STRIP001          bEnd = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  SetActivePart( SC_SPLIT_BOTTOMLEFT );
//STRIP001  SetPosX( SC_SPLIT_LEFT, nX1 );
//STRIP001  SetPosY( SC_SPLIT_BOTTOM, nY1 );
//STRIP001
//STRIP001  SetCurX( nX1 );
//STRIP001  SetCurY( nY1 );
//STRIP001 }

//STRIP001 void ScViewData::SetScreen( const Rectangle& rVisArea )
//STRIP001 {
//STRIP001  SetScreenPos( rVisArea.TopLeft() );
//STRIP001
//STRIP001  //  hier ohne GetOutputFactor(), weil fuer Ausgabe in Metafile
//STRIP001
//STRIP001  aScrSize = rVisArea.GetSize();
//STRIP001  aScrSize.Width() = (long)
//STRIP001      ( aScrSize.Width() * ScGlobal::nScreenPPTX / HMM_PER_TWIPS );
//STRIP001  aScrSize.Height() = (long)
//STRIP001      ( aScrSize.Height() * ScGlobal::nScreenPPTY / HMM_PER_TWIPS );
//STRIP001 }

/*N*/ SfxObjectShell* ScViewData::GetSfxDocShell() const
/*N*/ {
/*N*/   return pDocShell;
/*N*/ }

/*N*/ SfxBindings& ScViewData::GetBindings()
/*N*/ {
/*N*/   DBG_ASSERT( pViewShell, "GetBindings() without ViewShell" );
/*N*/   return pViewShell->GetViewFrame()->GetBindings();
/*N*/ }

/*N*/ SfxDispatcher& ScViewData::GetDispatcher()
/*N*/ {
/*N*/   DBG_ASSERT( pViewShell, "GetDispatcher() without ViewShell" );
/*N*/   return *pViewShell->GetViewFrame()->GetDispatcher();
/*N*/ }

//STRIP001 Window* ScViewData::GetDialogParent()
//STRIP001 {
//STRIP001  DBG_ASSERT( pViewShell, "GetDialogParent() ohne ViewShell" );
//STRIP001  return pViewShell->GetDialogParent();
//STRIP001 }

/*N*/ Window* ScViewData::GetActiveWin()
/*N*/ {
/*N*/   DBG_ASSERT( pView, "GetActiveWin() ohne View" );
/*N*/   return pView->GetActiveWin();
/*N*/ }

/*N*/ ScDrawView* ScViewData::GetScDrawView()
/*N*/ {
/*N*/   DBG_ASSERT( pView, "GetScDrawView() ohne View" );
/*N*/   return pView->GetScDrawView();
/*N*/ }

/*N*/ BOOL ScViewData::IsMinimized()
/*N*/ {
/*N*/   DBG_ASSERT( pView, "IsMinimized() ohne View" );
/*N*/   return pView->IsMinimized();
/*N*/ }

//STRIP001 void ScViewData::UpdateScreenZoom( const Fraction& rNewX, const Fraction& rNewY )
//STRIP001 {
//STRIP001  Fraction aOldX = GetZoomX();
//STRIP001  Fraction aOldY = GetZoomY();
//STRIP001
//STRIP001  SetZoom(rNewX,rNewY);
//STRIP001
//STRIP001  Fraction aWidth = GetZoomX();
//STRIP001  aWidth *= Fraction( aScrSize.Width(),1 );
//STRIP001  aWidth /= aOldX;
//STRIP001
//STRIP001  Fraction aHeight = GetZoomY();
//STRIP001  aHeight *= Fraction( aScrSize.Height(),1 );
//STRIP001  aHeight /= aOldY;
//STRIP001
//STRIP001  aScrSize.Width()  = (long) aWidth;
//STRIP001  aScrSize.Height() = (long) aHeight;
//STRIP001 }

/*N*/ void ScViewData::CalcPPT()
/*N*/ {
/*N*/   nPPTX = ScGlobal::nScreenPPTX * (double) GetZoomX();
/*N*/   if (pDocShell)
/*N*/       nPPTX = nPPTX / pDocShell->GetOutputFactor();   // Faktor ist Drucker zu Bildschirm
/*N*/   nPPTY = ScGlobal::nScreenPPTY * (double) GetZoomY();
/*N*/
/*N*/   //  #83616# if detective objects are present,
/*N*/   //  try to adjust horizontal scale so the most common column width has minimal rounding errors,
/*N*/   //  to avoid differences between cell and drawing layer output
/*N*/
/*N*/   if ( pDoc && pDoc->HasDetectiveObjects(nTabNo) )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nEndCol = 0;
//STRIP001 /*?*/        USHORT nDummy = 0;
//STRIP001 /*?*/        pDoc->GetTableArea( nTabNo, nEndCol, nDummy );
//STRIP001 /*?*/        if (nEndCol<20)
//STRIP001 /*?*/            nEndCol = 20;           // same end position as when determining draw scale
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nTwips = pDoc->GetCommonWidth( nEndCol, nTabNo );
//STRIP001 /*?*/        if ( nTwips )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            double fOriginal = nTwips * nPPTX;
//STRIP001 /*?*/            if ( fOriginal < nEndCol )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                //  if one column is smaller than the column count,
//STRIP001 /*?*/                //  rounding errors are likely to add up to a whole column.
//STRIP001 /*?*/
//STRIP001 /*?*/                double fRounded = ::rtl::math::approxFloor( fOriginal + 0.5 );
//STRIP001 /*?*/                if ( fRounded > 0.0 )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    double fScale = fRounded / fOriginal + 1E-6;
//STRIP001 /*?*/                    if ( fScale >= 0.9 && fScale <= 1.1 )
//STRIP001 /*?*/                        nPPTX *= fScale;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

//------------------------------------------------------------------

#define SC_OLD_TABSEP   '/'
#define SC_NEW_TABSEP   '+'

/*N*/ void ScViewData::WriteUserData(String& rData)
/*N*/ {
/*N*/   //  nZoom (bis 364v) oder nZoom/nPageZoom/bPageMode (ab 364w)
/*N*/   //  nTab
/*N*/   //  Tab-ControlBreite
/*N*/   //  pro Tabelle:
/*N*/   //  CursorX/CursorY/HSplitMode/VSplitMode/HSplitPos/VSplitPos/SplitActive/
/*N*/   //  PosX[links]/PosX[rechts]/PosY[oben]/PosY[unten]
/*N*/   //  wenn Zeilen groesser 8192, "+" statt "/"
/*N*/
/*N*/   USHORT nZoom = (USHORT)((aZoomY.GetNumerator() * 100) / aZoomY.GetDenominator());
/*N*/   rData = String::CreateFromInt32( nZoom );
/*N*/   rData += '/';
/*N*/   nZoom = (USHORT)((aPageZoomY.GetNumerator() * 100) / aPageZoomY.GetDenominator());
/*N*/   rData += String::CreateFromInt32( nZoom );
/*N*/   rData += '/';
/*N*/   if (bPagebreak)
/*N*/       rData += '1';
/*N*/   else
/*N*/       rData += '0';
/*N*/
/*N*/   rData += ';';
/*N*/   rData += String::CreateFromInt32( nTabNo );
/*N*/   rData += ';';
/*N*/   rData.AppendAscii(RTL_CONSTASCII_STRINGPARAM( TAG_TABBARWIDTH ));
/*N*/   rData += String::CreateFromInt32( pView->GetTabBarWidth() );
/*N*/
/*N*/   USHORT nTabCount = pDoc->GetTableCount();
/*N*/   for (USHORT i=0; i<nTabCount; i++)
/*N*/   {
/*N*/       rData += ';';                   // Numerierung darf auf keinen Fall durcheinanderkommen
/*N*/       if (pTabData[i])
/*N*/       {
/*N*/           sal_Unicode cTabSep = SC_OLD_TABSEP;                // wie 3.1
/*N*/           if ( pTabData[i]->nCurY > MAXROW_30 ||
/*N*/                pTabData[i]->nPosY[0] > MAXROW_30 || pTabData[i]->nPosY[1] > MAXROW_30 ||
/*N*/                ( pTabData[i]->eVSplitMode == SC_SPLIT_FIX &&
/*N*/                   pTabData[i]->nFixPosY > MAXROW_30 ) )
/*N*/           {
/*N*/               cTabSep = SC_NEW_TABSEP;        // um eine 3.1-Version nicht umzubringen
/*N*/           }
/*N*/
/*N*/
/*N*/           rData += String::CreateFromInt32( pTabData[i]->nCurX );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->nCurY );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->eHSplitMode );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->eVSplitMode );
/*N*/           rData += cTabSep;
/*N*/           if ( pTabData[i]->eHSplitMode == SC_SPLIT_FIX )
/*N*/               rData += String::CreateFromInt32( pTabData[i]->nFixPosX );
/*N*/           else
/*N*/               rData += String::CreateFromInt32( pTabData[i]->nHSplitPos );
/*N*/           rData += cTabSep;
/*N*/           if ( pTabData[i]->eVSplitMode == SC_SPLIT_FIX )
/*N*/               rData += String::CreateFromInt32( pTabData[i]->nFixPosY );
/*N*/           else
/*N*/               rData += String::CreateFromInt32( pTabData[i]->nVSplitPos );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->eWhichActive );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->nPosX[0] );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->nPosX[1] );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->nPosY[0] );
/*N*/           rData += cTabSep;
/*N*/           rData += String::CreateFromInt32( pTabData[i]->nPosY[1] );
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScViewData::ReadUserData(const String& rData)
//STRIP001 {
//STRIP001  if (!rData.Len())       // Leerer String kommt bei "neu Laden"
//STRIP001      return;             // dann auch ohne Assertion beenden
//STRIP001
//STRIP001  xub_StrLen nCount = rData.GetTokenCount(';');
//STRIP001  if ( nCount <= 2 )
//STRIP001  {
//STRIP001      //  #45208# beim Reload in der Seitenansicht sind evtl. die Preview-UserData
//STRIP001      //  stehengelassen worden. Den Zoom von der Preview will man hier nicht...
//STRIP001      DBG_ERROR("ReadUserData: das sind nicht meine Daten");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  String aTabOpt;
//STRIP001  xub_StrLen nTagLen = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(TAG_TABBARWIDTH)).Len();
//STRIP001
//STRIP001  //-------------------
//STRIP001  // nicht pro Tabelle:
//STRIP001  //-------------------
//STRIP001  USHORT nTabStart = 2;
//STRIP001
//STRIP001  String aZoomStr = rData.GetToken(0);                        // Zoom/PageZoom/Modus
//STRIP001  USHORT nNormZoom = aZoomStr.GetToken(0,'/').ToInt32();
//STRIP001  if ( nNormZoom >= MINZOOM && nNormZoom <= MAXZOOM )
//STRIP001      aZoomX = aZoomY = Fraction( nNormZoom, 100 );           //  "normaler" Zoom (immer)
//STRIP001  USHORT nPageZoom = aZoomStr.GetToken(1,'/').ToInt32();
//STRIP001  if ( nPageZoom >= MINZOOM && nPageZoom <= MAXZOOM )
//STRIP001      aPageZoomX = aPageZoomY = Fraction( nPageZoom, 100 );   // Pagebreak-Zoom, wenn gesetzt
//STRIP001  sal_Unicode cMode = aZoomStr.GetToken(2,'/').GetChar(0);    // 0 oder "0"/"1"
//STRIP001  SetPagebreakMode( cMode == '1' );
//STRIP001  // SetPagebreakMode muss immer gerufen werden wegen CalcPPT / RecalcPixPos()
//STRIP001
//STRIP001  //
//STRIP001  //  Tabelle kann ungueltig geworden sein (z.B. letzte Version):
//STRIP001  //
//STRIP001  USHORT nNewTab = rData.GetToken(1).ToInt32();
//STRIP001  if (pDoc->HasTable( nNewTab ))
//STRIP001      SetTabNo(nNewTab);
//STRIP001
//STRIP001  //
//STRIP001  // wenn vorhanden, TabBar-Breite holen:
//STRIP001  //
//STRIP001  aTabOpt = rData.GetToken(2);
//STRIP001
//STRIP001  if ( nTagLen && aTabOpt.Copy(0,nTagLen).EqualsAscii(TAG_TABBARWIDTH) )
//STRIP001  {
//STRIP001      pView->SetTabBarWidth( aTabOpt.Copy(nTagLen).ToInt32() );
//STRIP001      nTabStart = 3;
//STRIP001  }
//STRIP001
//STRIP001  //-------------
//STRIP001  // pro Tabelle:
//STRIP001  //-------------
//STRIP001  USHORT nPos = 0;
//STRIP001  while ( nCount > nPos+nTabStart )
//STRIP001  {
//STRIP001      aTabOpt = rData.GetToken(nPos+nTabStart);
//STRIP001      if (!pTabData[nPos])
//STRIP001          pTabData[nPos] = new ScViewDataTable;
//STRIP001
//STRIP001      sal_Unicode cTabSep = 0;
//STRIP001      if (aTabOpt.GetTokenCount(SC_OLD_TABSEP) >= 11)
//STRIP001          cTabSep = SC_OLD_TABSEP;
//STRIP001 #ifndef SC_LIMIT_ROWS
//STRIP001      else if (aTabOpt.GetTokenCount(SC_NEW_TABSEP) >= 11)
//STRIP001          cTabSep = SC_NEW_TABSEP;
//STRIP001      // '+' ist nur erlaubt, wenn wir mit Zeilen > 8192 umgehen koennen
//STRIP001 #endif
//STRIP001
//STRIP001      if (cTabSep)
//STRIP001      {
//STRIP001          pTabData[nPos]->nCurX = aTabOpt.GetToken(0,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->nCurY = aTabOpt.GetToken(1,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->eHSplitMode = (ScSplitMode) aTabOpt.GetToken(2,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->eVSplitMode = (ScSplitMode) aTabOpt.GetToken(3,cTabSep).ToInt32();
//STRIP001
//STRIP001          if ( pTabData[nPos]->eHSplitMode == SC_SPLIT_FIX )
//STRIP001          {
//STRIP001              pTabData[nPos]->nFixPosX = aTabOpt.GetToken(4,cTabSep).ToInt32();
//STRIP001              UpdateFixX(nPos);
//STRIP001          }
//STRIP001          else
//STRIP001              pTabData[nPos]->nHSplitPos = aTabOpt.GetToken(4,cTabSep).ToInt32();
//STRIP001
//STRIP001          if ( pTabData[nPos]->eVSplitMode == SC_SPLIT_FIX )
//STRIP001          {
//STRIP001              pTabData[nPos]->nFixPosY = aTabOpt.GetToken(5,cTabSep).ToInt32();
//STRIP001              UpdateFixY(nPos);
//STRIP001          }
//STRIP001          else
//STRIP001              pTabData[nPos]->nVSplitPos = aTabOpt.GetToken(5,cTabSep).ToInt32();
//STRIP001
//STRIP001          pTabData[nPos]->eWhichActive = (ScSplitPos) aTabOpt.GetToken(6,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->nPosX[0] = aTabOpt.GetToken(7,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->nPosX[1] = aTabOpt.GetToken(8,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->nPosY[0] = aTabOpt.GetToken(9,cTabSep).ToInt32();
//STRIP001          pTabData[nPos]->nPosY[1] = aTabOpt.GetToken(10,cTabSep).ToInt32();
//STRIP001
//STRIP001          //  Test, ob der aktive Teil laut SplitMode ueberhaupt existiert
//STRIP001          //  (Bug #44516#)
//STRIP001          ScSplitPos eTest = pTabData[nPos]->eWhichActive;
//STRIP001          if ( ( WhichH( eTest ) == SC_SPLIT_RIGHT &&
//STRIP001                  pTabData[nPos]->eHSplitMode == SC_SPLIT_NONE ) ||
//STRIP001               ( WhichV( eTest ) == SC_SPLIT_TOP &&
//STRIP001                  pTabData[nPos]->eVSplitMode == SC_SPLIT_NONE ) )
//STRIP001          {
//STRIP001              //  dann wieder auf Default (unten links)
//STRIP001              pTabData[nPos]->eWhichActive = SC_SPLIT_BOTTOMLEFT;
//STRIP001              DBG_ERROR("SplitPos musste korrigiert werden");
//STRIP001          }
//STRIP001      }
//STRIP001      ++nPos;
//STRIP001  }
//STRIP001
//STRIP001  RecalcPixPos();
//STRIP001 }

//STRIP001 void ScViewData::WriteExtOptions(ScExtDocOptions& rOpt)
//STRIP001 {
//STRIP001  // for Excel export
//STRIP001
//STRIP001  // document settings
//STRIP001  rOpt.SetActTab( GetTabNo() );
//STRIP001  rOpt.nSelTabs = 0;
//STRIP001  if( pOptions && (pOptions->GetGridColor().GetColor() != SC_STD_GRIDCOLOR) )
//STRIP001      rOpt.SetGridCol( pOptions->GetGridColor() );
//STRIP001
//STRIP001  // table settings
//STRIP001  USHORT nTabCount = pDoc->GetTableCount();
//STRIP001  for( USHORT nTab = 0; nTab < nTabCount; nTab++ )
//STRIP001  {
//STRIP001      ScViewDataTable* pViewTab = pTabData[ nTab ];
//STRIP001      if( pViewTab )
//STRIP001      {
//STRIP001             ScExtTabOptions* pTabOpt = rOpt.GetExtTabOptions( nTab );
//STRIP001             if( !pTabOpt )
//STRIP001                 rOpt.SetExtTabOptions( nTab, pTabOpt = new ScExtTabOptions );
//STRIP001
//STRIP001             pTabOpt->nTabNum = nTab;
//STRIP001          pTabOpt->bSelected = GetMarkData().GetTableSelect( nTab );
//STRIP001          if( pTabOpt->bSelected )
//STRIP001              rOpt.nSelTabs++;
//STRIP001
//STRIP001          BOOL bHorSplit = (pViewTab->eHSplitMode != SC_SPLIT_NONE);
//STRIP001          BOOL bVertSplit = (pViewTab->eVSplitMode != SC_SPLIT_NONE);
//STRIP001          BOOL bNormalSplit = (pViewTab->eHSplitMode == SC_SPLIT_NORMAL) || (pViewTab->eVSplitMode == SC_SPLIT_NORMAL);
//STRIP001          pTabOpt->bFrozen = (pViewTab->eHSplitMode == SC_SPLIT_FIX) || (pViewTab->eVSplitMode == SC_SPLIT_FIX);
//STRIP001
//STRIP001          if( bNormalSplit )
//STRIP001          {
//STRIP001              Point aPixel = Application::GetDefaultDevice()->PixelToLogic(
//STRIP001                  Point( pViewTab->nHSplitPos, pViewTab->nVSplitPos ), MapMode( MAP_TWIP ) );
//STRIP001              if ( pDocShell )
//STRIP001                  aPixel.X() = (long)((double)aPixel.X() / pDocShell->GetOutputFactor());
//STRIP001              pTabOpt->nSplitX = aPixel.X();
//STRIP001              pTabOpt->nSplitY = aPixel.Y();
//STRIP001          }
//STRIP001          else if( pTabOpt->bFrozen )
//STRIP001          {
//STRIP001              pTabOpt->nSplitX = (pViewTab->eHSplitMode == SC_SPLIT_FIX) ? pViewTab->nFixPosX : 0;
//STRIP001              pTabOpt->nSplitY = (pViewTab->eVSplitMode == SC_SPLIT_FIX) ? pViewTab->nFixPosY : 0;
//STRIP001          }
//STRIP001
//STRIP001          pTabOpt->nLeftCol = pViewTab->nPosX[ SC_SPLIT_LEFT ];
//STRIP001          pTabOpt->nLeftSplitCol = pViewTab->nPosX[ SC_SPLIT_RIGHT ];
//STRIP001             pTabOpt->nTopRow = pViewTab->nPosY[ bVertSplit ? SC_SPLIT_TOP : SC_SPLIT_BOTTOM ];
//STRIP001          pTabOpt->nTopSplitRow = pViewTab->nPosY[ SC_SPLIT_BOTTOM ];
//STRIP001
//STRIP001          switch( pViewTab->eWhichActive )
//STRIP001          {
//STRIP001              case SC_SPLIT_TOPLEFT:      pTabOpt->nActPane = 3;  break;
//STRIP001              case SC_SPLIT_TOPRIGHT:     pTabOpt->nActPane = 1;  break;
//STRIP001              case SC_SPLIT_BOTTOMLEFT:   pTabOpt->nActPane = 2;  break;
//STRIP001              case SC_SPLIT_BOTTOMRIGHT:  pTabOpt->nActPane = 0;  break;
//STRIP001          }
//STRIP001          if( !bHorSplit )
//STRIP001              pTabOpt->nActPane |= 2;
//STRIP001          if( !bVertSplit )
//STRIP001              pTabOpt->nActPane |= 1;
//STRIP001
//STRIP001          pTabOpt->aLastSel.aStart.Set( pViewTab->nCurX, pViewTab->nCurY, nTab );
//STRIP001          pTabOpt->aLastSel.aEnd = pTabOpt->aLastSel.aStart;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScViewData::ReadExtOptions( const ScExtDocOptions& rOpt )
//STRIP001 {
//STRIP001  // for Excel import
//STRIP001     if( !rOpt.IsChanged() ) return;
//STRIP001
//STRIP001  USHORT nTabCount = pDoc->GetTableCount();
//STRIP001  for (USHORT nTab=0; nTab<nTabCount; nTab++)
//STRIP001  {
//STRIP001      const ScExtTabOptions* pExtTab = rOpt.GetExtTabOptions( nTab );
//STRIP001      if ( pExtTab )
//STRIP001      {
//STRIP001          if (!pTabData[nTab])
//STRIP001              pTabData[nTab] = new ScViewDataTable;
//STRIP001          ScViewDataTable* pViewTab = pTabData[nTab];
//STRIP001
//STRIP001          pViewTab->nPosX[SC_SPLIT_LEFT] = pExtTab->nLeftCol;
//STRIP001          ScVSplitPos eDefV = pExtTab->nSplitY ? SC_SPLIT_TOP : SC_SPLIT_BOTTOM;
//STRIP001          pViewTab->nPosY[eDefV] = pExtTab->nTopRow;
//STRIP001
//STRIP001          if ( pExtTab->nSplitX || pExtTab->nSplitY )
//STRIP001          {
//STRIP001              if ( pExtTab->bFrozen )
//STRIP001              {
//STRIP001                  if ( pExtTab->nSplitX )
//STRIP001                  {
//STRIP001                      pViewTab->eHSplitMode = SC_SPLIT_FIX;
//STRIP001                      pViewTab->nFixPosX = pExtTab->nSplitX;
//STRIP001                      pViewTab->nHSplitPos = 0;
//STRIP001                      UpdateFixX(nTab);
//STRIP001                      pViewTab->nPosX[SC_SPLIT_RIGHT]  = pExtTab->nLeftSplitCol;
//STRIP001                  }
//STRIP001                  if ( pExtTab->nSplitY )
//STRIP001                  {
//STRIP001                      pViewTab->eVSplitMode = SC_SPLIT_FIX;
//STRIP001                      pViewTab->nFixPosY = pExtTab->nSplitY;
//STRIP001                      pViewTab->nVSplitPos = 0;
//STRIP001                      UpdateFixY(nTab);
//STRIP001                      pViewTab->nPosY[SC_SPLIT_BOTTOM] = pExtTab->nTopSplitRow;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  Point aPixel = Application::GetDefaultDevice()->LogicToPixel(
//STRIP001                                  Point( pExtTab->nSplitX, pExtTab->nSplitY ),
//STRIP001                                  MapMode( MAP_TWIP ) );  //! Zoom?
//STRIP001                  if ( pDocShell )
//STRIP001                  {
//STRIP001                      double nFactor = pDocShell->GetOutputFactor();
//STRIP001                      aPixel.X() = (long)( aPixel.X() * nFactor + 0.5 );
//STRIP001                  }
//STRIP001                  if ( pExtTab->nSplitX )
//STRIP001                  {
//STRIP001                      pViewTab->eHSplitMode = SC_SPLIT_NORMAL;
//STRIP001                      pViewTab->nHSplitPos = aPixel.X();
//STRIP001                      pViewTab->nPosX[SC_SPLIT_RIGHT]  = pExtTab->nLeftSplitCol;
//STRIP001                  }
//STRIP001                  if ( pExtTab->nSplitY )
//STRIP001                  {
//STRIP001                      pViewTab->eVSplitMode = SC_SPLIT_NORMAL;
//STRIP001                      pViewTab->nVSplitPos = aPixel.Y();
//STRIP001                      pViewTab->nPosY[SC_SPLIT_BOTTOM] = pExtTab->nTopSplitRow;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              ScSplitPos ePos = SC_SPLIT_BOTTOMLEFT;
//STRIP001              switch ( pExtTab->nActPane )
//STRIP001              {
//STRIP001                  case 0: ePos = SC_SPLIT_BOTTOMRIGHT; break;
//STRIP001                  case 1: ePos = SC_SPLIT_TOPRIGHT;    break;
//STRIP001                  case 2: ePos = SC_SPLIT_BOTTOMLEFT;  break;
//STRIP001                  case 3: ePos = SC_SPLIT_TOPLEFT;     break;
//STRIP001              }
//STRIP001              if ( pViewTab->eHSplitMode == SC_SPLIT_NONE )   // hor. nicht geteilt?
//STRIP001              {
//STRIP001                  if (ePos == SC_SPLIT_BOTTOMRIGHT)           // dann immer links
//STRIP001                      ePos = SC_SPLIT_BOTTOMLEFT;
//STRIP001                  else if (ePos == SC_SPLIT_TOPRIGHT)
//STRIP001                      ePos = SC_SPLIT_TOPLEFT;
//STRIP001              }
//STRIP001              if ( pViewTab->eVSplitMode == SC_SPLIT_NONE )   // vert. nicht geteilt?
//STRIP001              {
//STRIP001                  if (ePos == SC_SPLIT_TOPLEFT)               // dann immer unten
//STRIP001                      ePos = SC_SPLIT_BOTTOMLEFT;
//STRIP001                  else if (ePos == SC_SPLIT_TOPRIGHT)
//STRIP001                      ePos = SC_SPLIT_BOTTOMRIGHT;
//STRIP001              }
//STRIP001              pViewTab->eWhichActive = ePos;
//STRIP001          }
//STRIP001
//STRIP001          if ( pExtTab->bValidSel )
//STRIP001          {
//STRIP001              ScRange aSelRange = pExtTab->aLastSel;
//STRIP001              pViewTab->nCurX = aSelRange.aStart.Col();
//STRIP001              pViewTab->nCurY = aSelRange.aStart.Row();
//STRIP001          }
//STRIP001          GetMarkData().SelectTable( nTab, pExtTab->bSelected );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SetTabNo( rOpt.nActTab );
//STRIP001  if( pOptions && rOpt.pGridCol )
//STRIP001      pOptions->SetGridColor( *rOpt.pGridCol, EMPTY_STRING );
//STRIP001
//STRIP001  // RecalcPixPos oder so - auch nMPos - auch bei ReadUserData ??!?!
//STRIP001 }

/*N*/ void ScViewData::WriteUserDataSequence(uno::Sequence <beans::PropertyValue>& rSettings)
/*N*/ {
/*N*/   rSettings.realloc(SC_VIEWSETTINGS_COUNT);
/*N*/   // + 1, because we have to put the view id in the sequence
/*N*/   beans::PropertyValue* pSettings = rSettings.getArray();
/*N*/   if (pSettings)
/*N*/   {
/*N*/       sal_uInt16 nViewID(pViewShell->GetViewFrame()->GetCurViewId());
/*N*/       pSettings[SC_VIEW_ID].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_VIEWID));
/*N*/       ::rtl::OUStringBuffer sBuffer(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_VIEW)));
/*N*/       SvXMLUnitConverter::convertNumber(sBuffer, static_cast<sal_Int32>(nViewID));
/*N*/       pSettings[SC_VIEW_ID].Value <<= sBuffer.makeStringAndClear();
/*N*/
/*N*/       USHORT nTabCount (pDoc->GetTableCount());
/*N*/       uno::Reference<lang::XMultiServiceFactory> xServiceFactory =
/*N*/                                       ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/       DBG_ASSERT( xServiceFactory.is(), "got no service manager" );
/*N*/       if( xServiceFactory.is() )
/*N*/       {
/*N*/           ::rtl::OUString sName(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.NamedPropertyValues"));
/*N*/           uno::Reference<container::XNameContainer> xNameContainer = uno::Reference<container::XNameContainer>(xServiceFactory->createInstance(sName), uno::UNO_QUERY);
/*N*/           if (xNameContainer.is())
/*N*/           {
/*N*/               for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/               {
/*N*/                   if (pTabData[nTab])
/*N*/                   {
/*N*/                       uno::Sequence <beans::PropertyValue> aTableViewSettings;
/*N*/                       pTabData[nTab]->WriteUserDataSequence(aTableViewSettings);
/*N*/                       String sName;
/*N*/                       GetDocument()->GetName( nTab, sName );
/*N*/                       ::rtl::OUString sOUName(sName);
/*N*/                       uno::Any aAny;
/*N*/                       aAny <<= aTableViewSettings;
/*N*/                         try
/*N*/                         {
/*N*/                           xNameContainer->insertByName(sName, aAny);
/*N*/                         }
/*N*/                         //#101739#; two tables with the same name are possible
/*N*/                         catch ( container::ElementExistException& )
/*N*/                         {
/*N*/                             DBG_ERRORFILE("seems there are two tables with the same name");
/*N*/                         }
/*N*/                         catch ( uno::RuntimeException& )
/*N*/                         {
/*N*/                             DBG_ERRORFILE("something went wrong");
/*N*/                         }
/*N*/                   }
/*N*/               }
/*N*/               pSettings[SC_TABLE_VIEWSETTINGS].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_TABLES));
/*N*/               pSettings[SC_TABLE_VIEWSETTINGS].Value <<= xNameContainer;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       String sName;
/*N*/       GetDocument()->GetName( nTabNo, sName );
/*N*/       ::rtl::OUString sOUName(sName);
/*N*/       pSettings[SC_ACTIVE_TABLE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_ACTIVETABLE));
/*N*/       pSettings[SC_ACTIVE_TABLE].Value <<= sOUName;
/*N*/       pSettings[SC_HORIZONTAL_SCROLL_BAR_WIDTH].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_HORIZONTALSCROLLBARWIDTH));
/*N*/       pSettings[SC_HORIZONTAL_SCROLL_BAR_WIDTH].Value <<= sal_Int32(pView->GetTabBarWidth());
/*N*/       sal_Int32 nZoomValue ((aZoomY.GetNumerator() * 100) / aZoomY.GetDenominator());
/*N*/       sal_Int32 nPageZoomValue ((aPageZoomY.GetNumerator() * 100) / aPageZoomY.GetDenominator());
/*N*/       pSettings[SC_ZOOM_TYPE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_ZOOMTYPE));
/*N*/       pSettings[SC_ZOOM_TYPE].Value <<= sal_Int16(pView->GetZoomType());
/*N*/       pSettings[SC_ZOOM_VALUE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_ZOOMVALUE));
/*N*/       pSettings[SC_ZOOM_VALUE].Value <<= nZoomValue;
/*N*/       pSettings[SC_PAGE_VIEW_ZOOM_VALUE].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_PAGEVIEWZOOMVALUE));
/*N*/       pSettings[SC_PAGE_VIEW_ZOOM_VALUE].Value <<= nPageZoomValue;
/*N*/       pSettings[SC_PAGE_BREAK_PREVIEW].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_SHOWPAGEBREAKPREVIEW));
/*N*/       ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_PAGE_BREAK_PREVIEW].Value, bPagebreak);
/*N*/
/*N*/       if (pOptions)
/*N*/       {
/*N*/           pSettings[SC_SHOWZERO].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_SHOWZERO));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_SHOWZERO].Value, pOptions->GetOption( VOPT_NULLVALS ) );
/*N*/           pSettings[SC_SHOWNOTES].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_SHOWNOTES));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_SHOWNOTES].Value, pOptions->GetOption( VOPT_NOTES ) );
/*N*/           pSettings[SC_SHOWGRID].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_SHOWGRID));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_SHOWGRID].Value, pOptions->GetOption( VOPT_GRID ) );
/*N*/           pSettings[SC_GRIDCOLOR].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_GRIDCOLOR));
/*N*/           String aColorName;
/*N*/           Color aColor = pOptions->GetGridColor(&aColorName);
/*N*/           pSettings[SC_GRIDCOLOR].Value <<= static_cast<sal_Int64>(aColor.GetColor());
/*N*/           pSettings[SC_SHOWPAGEBR].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_SHOWPAGEBR));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_SHOWPAGEBR].Value, pOptions->GetOption( VOPT_PAGEBREAKS ) );
/*N*/           pSettings[SC_COLROWHDR].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_COLROWHDR));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_COLROWHDR].Value, pOptions->GetOption( VOPT_HEADER ) );
/*N*/           pSettings[SC_SHEETTABS].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_SHEETTABS));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_SHEETTABS].Value, pOptions->GetOption( VOPT_TABCONTROLS ) );
/*N*/           pSettings[SC_OUTLSYMB].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_OUTLSYMB));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_OUTLSYMB].Value, pOptions->GetOption( VOPT_OUTLINER ) );
/*N*/
/*N*/           const ScGridOptions& aGridOpt = pOptions->GetGridOptions();
/*N*/           pSettings[SC_SNAPTORASTER].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_SNAPTORASTER));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_SNAPTORASTER].Value, aGridOpt.GetUseGridSnap() );
/*N*/           pSettings[SC_RASTERVIS].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_RASTERVIS));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_RASTERVIS].Value, aGridOpt.GetGridVisible() );
/*N*/           pSettings[SC_RASTERRESX].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_RASTERRESX));
/*N*/           pSettings[SC_RASTERRESX].Value <<= static_cast<sal_Int32> ( aGridOpt.GetFldDrawX() );
/*N*/           pSettings[SC_RASTERRESY].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_RASTERRESY));
/*N*/           pSettings[SC_RASTERRESY].Value <<= static_cast<sal_Int32> ( aGridOpt.GetFldDrawY() );
/*N*/           pSettings[SC_RASTERSUBX].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_RASTERSUBX));
/*N*/           pSettings[SC_RASTERSUBX].Value <<= static_cast<sal_Int32> ( aGridOpt.GetFldDivisionX() );
/*N*/           pSettings[SC_RASTERSUBY].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_RASTERSUBY));
/*N*/           pSettings[SC_RASTERSUBY].Value <<= static_cast<sal_Int32> ( aGridOpt.GetFldDivisionY() );
/*N*/           pSettings[SC_RASTERSYNC].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_RASTERSYNC));
/*N*/           ScUnoHelpFunctions::SetBoolInAny( pSettings[SC_RASTERSYNC].Value, aGridOpt.GetSynchronize() );
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScViewData::ReadUserDataSequence(const uno::Sequence <beans::PropertyValue>& rSettings)
//STRIP001 {
//STRIP001  sal_Int32 nCount(rSettings.getLength());
//STRIP001  sal_Int32 nTemp32(0);
//STRIP001  sal_Int16 nTemp16(0);
//STRIP001  sal_Bool bPageMode(sal_False);
//STRIP001  for (sal_Int32 i = 0; i < nCount; i++)
//STRIP001  {
//STRIP001      // SC_VIEWID has to parse and use by mba
//STRIP001      ::rtl::OUString sName(rSettings[i].Name);
//STRIP001      if (sName.compareToAscii(SC_TABLES) == 0)
//STRIP001      {
//STRIP001          uno::Reference<container::XNameContainer> xNameContainer;
//STRIP001          if ((rSettings[i].Value >>= xNameContainer) && xNameContainer->hasElements())
//STRIP001          {
//STRIP001              uno::Sequence< ::rtl::OUString > aNames(xNameContainer->getElementNames());
//STRIP001              for (sal_Int32 i = 0; i < aNames.getLength(); i++)
//STRIP001              {
//STRIP001                  String sTabName(aNames[i]);
//STRIP001                  sal_uInt16 nTab(0);
//STRIP001                  if (GetDocument()->GetTable(sTabName, nTab))
//STRIP001                  {
//STRIP001                      uno::Any aAny = xNameContainer->getByName(aNames[i]);
//STRIP001                      uno::Sequence<beans::PropertyValue> aTabSettings;
//STRIP001                      if (aAny >>= aTabSettings)
//STRIP001                      {
//STRIP001                          pTabData[nTab] = new ScViewDataTable;
//STRIP001                          pTabData[nTab]->ReadUserDataSequence(aTabSettings);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_ACTIVETABLE) == 0)
//STRIP001      {
//STRIP001          ::rtl::OUString sName;
//STRIP001          if(rSettings[i].Value >>= sName)
//STRIP001          {
//STRIP001              String sTabName(sName);
//STRIP001              sal_uInt16 nTab(0);
//STRIP001              if (GetDocument()->GetTable(sTabName, nTab))
//STRIP001                  nTabNo = nTab;
//STRIP001          }
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_HORIZONTALSCROLLBARWIDTH) == 0)
//STRIP001      {
//STRIP001          if (rSettings[i].Value >>= nTemp32)
//STRIP001              pView->SetTabBarWidth(nTemp32);
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_ZOOMTYPE) == 0)
//STRIP001      {
//STRIP001          if (rSettings[i].Value >>= nTemp16)
//STRIP001              pView->SetZoomType(SvxZoomType(nTemp16));
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_ZOOMVALUE) == 0)
//STRIP001      {
//STRIP001          if (rSettings[i].Value >>= nTemp32)
//STRIP001          {
//STRIP001              Fraction aZoom(nTemp32, 100);
//STRIP001              aZoomX = aZoomY = aZoom;
//STRIP001          }
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_PAGEVIEWZOOMVALUE) == 0)
//STRIP001      {
//STRIP001          if (rSettings[i].Value >>= nTemp32)
//STRIP001          {
//STRIP001              Fraction aZoom(nTemp32, 100);
//STRIP001              aPageZoomX = aPageZoomY = aZoom;
//STRIP001          }
//STRIP001      }
//STRIP001      else if (sName.compareToAscii(SC_SHOWPAGEBREAKPREVIEW) == 0)
//STRIP001          bPageMode = ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_SHOWZERO ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_NULLVALS, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_SHOWNOTES ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_NOTES, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_SHOWGRID ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_GRID, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_GRIDCOLOR ) == 0 )
//STRIP001      {
//STRIP001          sal_Int64 nColor;
//STRIP001          if (rSettings[i].Value >>= nColor)
//STRIP001          {
//STRIP001              String aColorName;
//STRIP001              Color aColor(static_cast<sal_uInt32>(nColor));
//STRIP001              pOptions->SetGridColor(aColor, aColorName);
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( sName.compareToAscii( SC_UNO_SHOWPAGEBR ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_PAGEBREAKS, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_COLROWHDR ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_HEADER, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_SHEETTABS ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_TABCONTROLS, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else if ( sName.compareToAscii( SC_UNO_OUTLSYMB ) == 0 )
//STRIP001          pOptions->SetOption(VOPT_OUTLINER, ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001      else
//STRIP001      {
//STRIP001          ScGridOptions aGridOpt(pOptions->GetGridOptions());
//STRIP001          if ( sName.compareToAscii( SC_UNO_SNAPTORASTER ) == 0 )
//STRIP001              aGridOpt.SetUseGridSnap( ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001          else if ( sName.compareToAscii( SC_UNO_RASTERVIS ) == 0 )
//STRIP001              aGridOpt.SetGridVisible( ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001          else if ( sName.compareToAscii( SC_UNO_RASTERRESX ) == 0 )
//STRIP001              aGridOpt.SetFldDrawX( static_cast <sal_uInt32> ( ScUnoHelpFunctions::GetInt32FromAny( rSettings[i].Value ) ) );
//STRIP001          else if ( sName.compareToAscii( SC_UNO_RASTERRESY ) == 0 )
//STRIP001              aGridOpt.SetFldDrawY( static_cast <sal_uInt32> ( ScUnoHelpFunctions::GetInt32FromAny( rSettings[i].Value ) ) );
//STRIP001          else if ( sName.compareToAscii( SC_UNO_RASTERSUBX ) == 0 )
//STRIP001              aGridOpt.SetFldDivisionX( static_cast <sal_uInt32> ( ScUnoHelpFunctions::GetInt32FromAny( rSettings[i].Value ) ) );
//STRIP001          else if ( sName.compareToAscii( SC_UNO_RASTERSUBY ) == 0 )
//STRIP001              aGridOpt.SetFldDivisionY( static_cast <sal_uInt32> ( ScUnoHelpFunctions::GetInt32FromAny( rSettings[i].Value ) ) );
//STRIP001          else if ( sName.compareToAscii( SC_UNO_RASTERSYNC ) == 0 )
//STRIP001              aGridOpt.SetSynchronize( ScUnoHelpFunctions::GetBoolFromAny( rSettings[i].Value ) );
//STRIP001          pOptions->SetGridOptions(aGridOpt);
//STRIP001      }
//STRIP001  }
//STRIP001  if (nCount)
//STRIP001      SetPagebreakMode( bPageMode );
//STRIP001 }

/*N*/ void ScViewData::SetOptions( const ScViewOptions& rOpt )
/*N*/ {
/*N*/   //  if visibility of horiz. ScrollBar is changed, TabBar may have to be resized...
/*N*/   BOOL bHScrollChanged = ( rOpt.GetOption(VOPT_HSCROLL) != pOptions->GetOption(VOPT_HSCROLL) );
/*N*/
/*N*/   //  if graphics are turned on or off, animation has to be started or stopped
/*N*/   //  graphics are controlled by VOBJ_TYPE_OLE
/*N*/   BOOL bGraphicsChanged = ( pOptions->GetObjMode(VOBJ_TYPE_OLE) !=
/*N*/                                  rOpt.GetObjMode(VOBJ_TYPE_OLE) );
/*N*/
/*N*/   *pOptions = rOpt;
/*N*/   DBG_ASSERT( pView, "No View" );
/*N*/
/*N*/   if( pView )
/*N*/   {
/*N*/       pView->ViewOptionsHasChanged( bHScrollChanged, bGraphicsChanged );
/*N*/   }
/*N*/ }

//STRIP001 Point ScViewData::GetMousePosPixel()
//STRIP001 {
//STRIP001  DBG_ASSERT( pView, "GetMousePosPixel() ohne View" );
//STRIP001  return pView->GetMousePosPixel();
//STRIP001 }

//STRIP001 void ScViewData::UpdateInputHandler( BOOL bForce, BOOL bStopEditing )
//STRIP001 {
//STRIP001  if (pViewShell)
//STRIP001      pViewShell->UpdateInputHandler( bForce, bStopEditing );
//STRIP001 }

//STRIP001 BOOL ScViewData::IsOle()
//STRIP001 {
//STRIP001  return pDocShell && pDocShell->IsOle();
//STRIP001 }

//STRIP001 BOOL ScViewData::UpdateFixX( USHORT nTab )               // TRUE = Wert geaendert
//STRIP001 {
//STRIP001  if (nTab>MAXTAB)        // Default
//STRIP001      nTab=nTabNo;        // akuelle Tabelle
//STRIP001
//STRIP001  if (!pView || pTabData[nTab]->eHSplitMode != SC_SPLIT_FIX)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nFix = pTabData[nTab]->nFixPosX;
//STRIP001  ScDocument* pDoc = GetDocument();
//STRIP001  long nNewPos = 0;
//STRIP001  for (USHORT nX=pTabData[nTab]->nPosX[SC_SPLIT_LEFT]; nX<nFix; nX++)
//STRIP001  {
//STRIP001      USHORT nTSize = pDoc->GetColWidth( nX, nTab );
//STRIP001      if (nTSize)
//STRIP001      {
//STRIP001          long nPix = ToPixel( nTSize, nPPTX );
//STRIP001          nNewPos += nPix;
//STRIP001      }
//STRIP001  }
//STRIP001  nNewPos += pView->GetGridOffset().X();
//STRIP001  if (nNewPos != pTabData[nTab]->nHSplitPos)
//STRIP001  {
//STRIP001      pTabData[nTab]->nHSplitPos = nNewPos;
//STRIP001      if (nTab == nTabNo)
//STRIP001          RecalcPixPos();                 //! sollte nicht noetig sein !!!
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ScViewData::UpdateFixY( USHORT nTab )               // TRUE = Wert geaendert
//STRIP001 {
//STRIP001  if (nTab>MAXTAB)        // Default
//STRIP001      nTab=nTabNo;        // akuelle Tabelle
//STRIP001
//STRIP001  if (!pView || pTabData[nTab]->eVSplitMode != SC_SPLIT_FIX)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nFix = pTabData[nTab]->nFixPosY;
//STRIP001  ScDocument* pDoc = GetDocument();
//STRIP001  long nNewPos = 0;
//STRIP001  for (USHORT nY=pTabData[nTab]->nPosY[SC_SPLIT_TOP]; nY<nFix; nY++)
//STRIP001  {
//STRIP001      USHORT nTSize = pDoc->FastGetRowHeight( nY, nTab );
//STRIP001      if (nTSize)
//STRIP001      {
//STRIP001          long nPix = ToPixel( nTSize, nPPTY );
//STRIP001          nNewPos += nPix;
//STRIP001      }
//STRIP001  }
//STRIP001  nNewPos += pView->GetGridOffset().Y();
//STRIP001  if (nNewPos != pTabData[nTab]->nVSplitPos)
//STRIP001  {
//STRIP001      pTabData[nTab]->nVSplitPos = nNewPos;
//STRIP001      if (nTab == nTabNo)
//STRIP001          RecalcPixPos();                 //! sollte nicht noetig sein !!!
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void ScViewData::UpdateOutlinerFlags( Outliner& rOutl ) const
//STRIP001 {
//STRIP001  ScDocument* pLocalDoc = GetDocument();
//STRIP001  BOOL bOnlineSpell = pLocalDoc->GetDocOptions().IsAutoSpell();
//STRIP001  BOOL bHideSpell = GetOptions().IsHideAutoSpell();
//STRIP001
//STRIP001  ULONG nCntrl = rOutl.GetControlWord();
//STRIP001  nCntrl |= EE_CNTRL_URLSFXEXECUTE;
//STRIP001  nCntrl |= EE_CNTRL_MARKFIELDS;
//STRIP001  nCntrl |= EE_CNTRL_AUTOCORRECT;
//STRIP001  if( bHideSpell )
//STRIP001      nCntrl |= EE_CNTRL_NOREDLINES;
//STRIP001  else
//STRIP001      nCntrl &= ~EE_CNTRL_NOREDLINES;
//STRIP001  if( bOnlineSpell )
//STRIP001      nCntrl |= EE_CNTRL_ONLINESPELLING;
//STRIP001  else
//STRIP001      nCntrl &= ~EE_CNTRL_ONLINESPELLING;
//STRIP001  rOutl.SetControlWord(nCntrl);
//STRIP001
//STRIP001  rOutl.SetCalcFieldValueHdl( LINK( SC_MOD(), ScModule, CalcFieldValueHdl ) );
//STRIP001
//STRIP001  //  #97417# don't call GetSpellChecker if online spelling isn't enabled.
//STRIP001  //  The language for AutoCorrect etc. is taken from the pool defaults
//STRIP001  //  (set in ScDocument::UpdateDrawLanguages)
//STRIP001
//STRIP001  if ( bOnlineSpell )
//STRIP001  {
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::linguistic2::XSpellChecker1> xXSpellChecker1( LinguMgr::GetSpellChecker() );
//STRIP001      rOutl.SetSpeller( xXSpellChecker1 );
//STRIP001  }
//STRIP001
//STRIP001  rOutl.SetDefaultHorizontalTextDirection(
//STRIP001      (EEHorizontalTextDirection)pLocalDoc->GetEditTextDirection( nTabNo ) );
//STRIP001 }

//STRIP001 ScAddress ScViewData::GetCurPos() const
//STRIP001 {
//STRIP001  return ScAddress( GetCurX(), GetCurY(), GetTabNo() );
//STRIP001 }




}
