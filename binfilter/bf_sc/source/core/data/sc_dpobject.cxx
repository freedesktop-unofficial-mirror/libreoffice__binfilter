/*************************************************************************
 *
 *  $RCSfile: sc_dpobject.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:35:55 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "dpobject.hxx"
#include "dptabsrc.hxx"
#include "dpsave.hxx"
#include "dpoutput.hxx"
#include "dpshttab.hxx"
#include "dpsdbtab.hxx"
#include "document.hxx"
#include "rechead.hxx"
#include "pivot.hxx"        // PIVOT_DATA_FIELD
#include "dapiuno.hxx"      // ScDataPilotConversion
#include "miscuno.hxx"
#include "scerrors.hxx"
#include "refupdat.hxx"

#include <com/sun/star/sheet/GeneralFunction.hpp>
#include <com/sun/star/sheet/DataPilotFieldOrientation.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/container/XContentEnumerationAccess.hpp>

#include <comphelper/processfactory.hxx>
#include <tools/debug.hxx>
#include <svtools/zforlist.hxx>     // IsNumberFormat
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
using namespace com::sun::star;

// -----------------------------------------------------------------------

#define MAX_LABELS 256 //!!! from fieldwnd.hxx, must be moved to global.hxx

// -----------------------------------------------------------------------

#define SCDPSOURCE_SERVICE  "com.sun.star.sheet.DataPilotSource"

// -----------------------------------------------------------------------

// incompatible versions of data pilot files
#define SC_DP_VERSION_CURRENT   6

// type of source data
#define SC_DP_SOURCE_SHEET      0
#define SC_DP_SOURCE_DATABASE   1
#define SC_DP_SOURCE_SERVICE    2

// -----------------------------------------------------------------------

//! move to a header file
#define DP_PROP_COLUMNGRAND         "ColumnGrand"
#define DP_PROP_FUNCTION            "Function"
#define DP_PROP_IGNOREEMPTY         "IgnoreEmptyRows"
#define DP_PROP_ISDATALAYOUT        "IsDataLayoutDimension"
//#define DP_PROP_ISVISIBLE         "IsVisible"
#define DP_PROP_ORIENTATION         "Orientation"
#define DP_PROP_ORIGINAL            "Original"
#define DP_PROP_POSITION            "Position"
#define DP_PROP_REPEATIFEMPTY       "RepeatIfEmpty"
#define DP_PROP_ROWGRAND            "RowGrand"
#define DP_PROP_SHOWDETAILS         "ShowDetails"
#define DP_PROP_SHOWEMPTY           "ShowEmpty"
#define DP_PROP_SUBTOTALS           "SubTotals"
#define DP_PROP_USEDHIERARCHY       "UsedHierarchy"

// -----------------------------------------------------------------------

/*N*/ USHORT lcl_GetDataGetOrientation( const uno::Reference<sheet::XDimensionsSupplier>& xSource )
/*N*/ {
/*N*/   long nRet = sheet::DataPilotFieldOrientation_HIDDEN;
/*N*/ if ( xSource.is() )
/*N*/   {
/*N*/       uno::Reference<container::XNameAccess> xDimsName = xSource->getDimensions();
/*N*/       uno::Reference<container::XIndexAccess> xIntDims = new ScNameToIndexAccess( xDimsName );
/*N*/       long nIntCount = xIntDims->getCount();
/*N*/       BOOL bFound = FALSE;
/*N*/       for (long nIntDim=0; nIntDim<nIntCount && !bFound; nIntDim++)
/*N*/       {
/*N*/           uno::Reference<uno::XInterface> xIntDim =
/*N*/               ScUnoHelpFunctions::AnyToInterface( xIntDims->getByIndex(nIntDim) );
/*N*/           uno::Reference<beans::XPropertySet> xDimProp( xIntDim, uno::UNO_QUERY );
/*N*/           if ( xDimProp.is() )
/*N*/           {
/*N*/               bFound = ScUnoHelpFunctions::GetBoolProperty( xDimProp,
/*N*/                   rtl::OUString::createFromAscii(DP_PROP_ISDATALAYOUT) );
/*N*/               //! error checking -- is "IsDataLayoutDimension" property required??
/*N*/               if (bFound)
/*N*/                   nRet = ScUnoHelpFunctions::GetEnumProperty(
/*N*/                           xDimProp, rtl::OUString::createFromAscii(DP_PROP_ORIENTATION),
/*N*/                           sheet::DataPilotFieldOrientation_HIDDEN );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScDPObject::ScDPObject( ScDocument* pD ) :
/*N*/   pDoc( pD ),
/*N*/   bAlive( FALSE ),
/*N*/   pSaveData( NULL ),
/*N*/   pSheetDesc( NULL ),
/*N*/   pImpDesc( NULL ),
/*N*/   pServDesc( NULL ),
/*N*/   pOutput( NULL ),
/*N*/   bSettingsChanged( FALSE )
/*N*/ {
/*N*/ }

/*N*/ ScDPObject::ScDPObject(const ScDPObject& r) :
/*N*/   pDoc( r.pDoc ),
/*N*/   bAlive( FALSE ),
/*N*/   pSaveData( NULL ),
/*N*/   aTableName( r.aTableName ),
/*N*/   aTableTag( r.aTableTag ),
/*N*/   aOutRange( r.aOutRange ),
/*N*/   pSheetDesc( NULL ),
/*N*/   pImpDesc( NULL ),
/*N*/   pServDesc( NULL ),
/*N*/   pOutput( NULL ),
/*N*/   bSettingsChanged( FALSE )
/*N*/ {
/*N*/   if (r.pSaveData)
/*N*/       pSaveData = new ScDPSaveData(*r.pSaveData);
/*N*/   if (r.pSheetDesc)
/*N*/       pSheetDesc = new ScSheetSourceDesc(*r.pSheetDesc);
/*N*/   if (r.pImpDesc)
/*N*/       pImpDesc = new ScImportSourceDesc(*r.pImpDesc);
/*N*/   if (r.pServDesc)
/*N*/       pServDesc = new ScDPServiceDesc(*r.pServDesc);
/*N*/   // xSource (and pOutput) is not copied
/*N*/ }

/*N*/ ScDPObject::~ScDPObject()
/*N*/ {
/*N*/   delete pOutput;
/*N*/   delete pSaveData;
/*N*/   delete pSheetDesc;
/*N*/   delete pImpDesc;
/*N*/   delete pServDesc;
/*N*/ }

/*N*/ DataObject* ScDPObject::Clone() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001  return new ScDPObject(*this);
/*N*/ }

/*N*/ void ScDPObject::SetAlive(BOOL bSet)
/*N*/ {
/*N*/   bAlive = bSet;
/*N*/ }

/*N*/ void ScDPObject::SetSaveData(const ScDPSaveData& rData)
/*N*/ {
/*N*/   delete pSaveData;
/*N*/   pSaveData = new ScDPSaveData( rData );
/*N*/
/*N*/   InvalidateData();       // re-init source from SaveData
/*N*/ }

/*N*/ void ScDPObject::SetOutRange(const ScRange& rRange)
/*N*/ {
/*N*/   aOutRange = rRange;
/*N*/
/*N*/   if ( pOutput )
/*N*/       pOutput->SetPosition( rRange.aStart );
/*N*/ }

/*N*/ void ScDPObject::SetSheetDesc(const ScSheetSourceDesc& rDesc)
/*N*/ {
/*N*/   if ( pSheetDesc && rDesc == *pSheetDesc )
/*N*/       return;             // nothing to do
/*N*/
/*N*/   DELETEZ( pImpDesc );
/*N*/   DELETEZ( pServDesc );
/*N*/
/*N*/   delete pImpDesc;
/*N*/   pSheetDesc = new ScSheetSourceDesc(rDesc);
/*N*/
/*N*/   //  make valid QueryParam
/*N*/
/*N*/   pSheetDesc->aQueryParam.nCol1 = pSheetDesc->aSourceRange.aStart.Col();
/*N*/   pSheetDesc->aQueryParam.nRow1 = pSheetDesc->aSourceRange.aStart.Row();
/*N*/   pSheetDesc->aQueryParam.nCol2 = pSheetDesc->aSourceRange.aEnd.Col();
/*N*/   pSheetDesc->aQueryParam.nRow2 = pSheetDesc->aSourceRange.aEnd.Row();;
/*N*/   pSheetDesc->aQueryParam.bHasHeader = TRUE;
/*N*/   USHORT nCount = pSheetDesc->aQueryParam.GetEntryCount();
/*N*/
/*N*/   InvalidateSource();     // new source must be created
/*N*/ }

/*N*/ void ScDPObject::SetImportDesc(const ScImportSourceDesc& rDesc)
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  if ( pImpDesc && rDesc == *pImpDesc )
//STRIP001      return;             // nothing to do
//STRIP001
//STRIP001  DELETEZ( pSheetDesc );
//STRIP001  DELETEZ( pServDesc );
//STRIP001
//STRIP001  delete pImpDesc;
//STRIP001  pImpDesc = new ScImportSourceDesc(rDesc);
//STRIP001
//STRIP001  InvalidateSource();     // new source must be created
/*N*/ }

/*N*/ void ScDPObject::SetServiceData(const ScDPServiceDesc& rDesc)
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  if ( pServDesc && rDesc == *pServDesc )
//STRIP001      return;             // nothing to do
//STRIP001
//STRIP001  DELETEZ( pSheetDesc );
//STRIP001  DELETEZ( pImpDesc );
//STRIP001
//STRIP001  delete pServDesc;
//STRIP001  pServDesc = new ScDPServiceDesc(rDesc);
//STRIP001
//STRIP001  InvalidateSource();     // new source must be created
/*N*/ }

//STRIP001 void ScDPObject::WriteSourceDataTo( ScDPObject& rDest ) const
//STRIP001 {
//STRIP001  if ( pSheetDesc )
//STRIP001      rDest.SetSheetDesc( *pSheetDesc );
//STRIP001  else if ( pImpDesc )
//STRIP001      rDest.SetImportDesc( *pImpDesc );
//STRIP001  else if ( pServDesc )
//STRIP001      rDest.SetServiceData( *pServDesc );
//STRIP001
//STRIP001  //  name/tag are not source data, but needed along with source data
//STRIP001
//STRIP001  rDest.aTableName = aTableName;
//STRIP001  rDest.aTableTag  = aTableTag;
//STRIP001 }

/*N*/ BOOL ScDPObject::IsSheetData() const
/*N*/ {
/*N*/   return ( pSheetDesc != NULL );
/*N*/ }

/*N*/ void ScDPObject::SetName(const String& rNew)
/*N*/ {
/*N*/   aTableName = rNew;
/*N*/ }

/*N*/ void ScDPObject::SetTag(const String& rNew)
/*N*/ {
/*N*/   aTableTag = rNew;
/*N*/ }

//STRIP001 uno::Reference<sheet::XDimensionsSupplier> ScDPObject::GetSource()
//STRIP001 {
//STRIP001  CreateObjects();
//STRIP001  return xSource;
//STRIP001 }

//STRIP001 void ScDPObject::CreateOutput()
//STRIP001 {
//STRIP001  CreateObjects();
//STRIP001  if (!pOutput)
//STRIP001      pOutput = new ScDPOutput( pDoc, xSource, aOutRange.aStart, IsSheetData() );
//STRIP001 }

/*N*/ void ScDPObject::CreateObjects()
/*N*/ {
/*N*/   if (!xSource.is())
/*N*/   {
/*N*/       //! cache DPSource and/or Output?
/*N*/
/*N*/       DBG_ASSERT( bAlive, "CreateObjects on non-inserted DPObject" );
/*N*/
/*N*/       DELETEZ( pOutput );     // not valid when xSource is changed
/*N*/
/*N*/       if ( pImpDesc )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 ScDatabaseDPData* pData = new ScDatabaseDPData( pDoc->GetServiceManager(), *pImpDesc );
//STRIP001 /*?*/            xSource = new ScDPSource( pData );
/*N*/       }
/*N*/       else if ( pServDesc )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 xSource = CreateSource( *pServDesc );
/*N*/       }
/*N*/
/*N*/       if ( !xSource.is() )    // sheet data or error in above cases
/*N*/       {
/*N*/           DBG_ASSERT( !pImpDesc && !pServDesc, "DPSource could not be created" );
/*N*/           if (!pSheetDesc)
/*N*/           {
/*?*/               DBG_ERROR("no source descriptor");
/*?*/               pSheetDesc = new ScSheetSourceDesc;     // dummy defaults
/*N*/           }
/*N*/           ScSheetDPData* pData = new ScSheetDPData( pDoc, *pSheetDesc );
/*N*/           xSource = new ScDPSource( pData );
/*N*/       }
/*N*/
/*N*/       if (pSaveData)
/*N*/           pSaveData->WriteToSource( xSource );
/*N*/   }
/*N*/   else if (bSettingsChanged)
/*N*/   {
/*?*/       DELETEZ( pOutput );     // not valid when xSource is changed
/*?*/
/*?*/       uno::Reference<util::XRefreshable> xRef( xSource, uno::UNO_QUERY );
/*?*/       if (xRef.is())
/*?*/       {
/*?*/           try
/*?*/           {
/*?*/               xRef->refresh();
/*?*/           }
/*?*/           catch(uno::Exception&)
/*?*/           {
/*?*/               DBG_ERROR("exception in refresh");
/*?*/           }
/*?*/       }
/*?*/
/*?*/       if (pSaveData)
/*?*/           pSaveData->WriteToSource( xSource );
/*N*/   }
/*N*/   bSettingsChanged = FALSE;
/*N*/ }

/*N*/ void ScDPObject::InvalidateData()
/*N*/   {
/*N*/   bSettingsChanged = TRUE;
/*N*/ }

/*N*/ void ScDPObject::InvalidateSource()
/*N*/ {
/*N*/   xSource = NULL;
/*N*/ }

//STRIP001 ScRange ScDPObject::GetNewOutputRange( BOOL& rOverflow )
//STRIP001 {
//STRIP001  CreateOutput();             // create xSource and pOutput if not already done
//STRIP001
//STRIP001  rOverflow = pOutput->HasError();        // range overflow or exception from source
//STRIP001  if ( rOverflow )
//STRIP001      return ScRange( aOutRange.aStart );
//STRIP001  else
//STRIP001  {
//STRIP001      //  don't store the result in aOutRange, because nothing has been output yet
//STRIP001      return pOutput->GetOutputRange();
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDPObject::Output()
//STRIP001 {
//STRIP001  //  clear old output area
//STRIP001  pDoc->DeleteAreaTab( aOutRange.aStart.Col(), aOutRange.aStart.Row(),
//STRIP001                       aOutRange.aEnd.Col(), aOutRange.aEnd.Row(),
//STRIP001                       aOutRange.aStart.Tab(), IDF_ALL );
//STRIP001
//STRIP001  CreateOutput();             // create xSource and pOutput if not already done
//STRIP001
//STRIP001  pOutput->Output();
//STRIP001
//STRIP001  //  aOutRange is always the range that was last output to the document
//STRIP001  aOutRange = pOutput->GetOutputRange();
//STRIP001 }

/*N*/ void ScDPObject::UpdateReference( UpdateRefMode eUpdateRefMode,
/*N*/                                    const ScRange& rRange, short nDx, short nDy, short nDz )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 // Output area
//STRIP001
//STRIP001  USHORT nCol1 = aOutRange.aStart.Col();
//STRIP001  USHORT nRow1 = aOutRange.aStart.Row();
//STRIP001  USHORT nTab1 = aOutRange.aStart.Tab();
//STRIP001  USHORT nCol2 = aOutRange.aEnd.Col();
//STRIP001  USHORT nRow2 = aOutRange.aEnd.Row();
//STRIP001  USHORT nTab2 = aOutRange.aEnd.Tab();
//STRIP001
//STRIP001  ScRefUpdateRes eRes =
//STRIP001      ScRefUpdate::Update( pDoc, eUpdateRefMode,
//STRIP001          rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
//STRIP001          rRange.aEnd.Col(), rRange.aEnd.Row(), rRange.aEnd.Tab(), nDx, nDy, nDz,
//STRIP001          nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001  if ( eRes != UR_NOTHING )
//STRIP001      SetOutRange( ScRange( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 ) );
//STRIP001
//STRIP001  // sheet source data
//STRIP001
//STRIP001  if ( pSheetDesc )
//STRIP001  {
//STRIP001      nCol1 = pSheetDesc->aSourceRange.aStart.Col();
//STRIP001      nRow1 = pSheetDesc->aSourceRange.aStart.Row();
//STRIP001      nTab1 = pSheetDesc->aSourceRange.aStart.Tab();
//STRIP001      nCol2 = pSheetDesc->aSourceRange.aEnd.Col();
//STRIP001      nRow2 = pSheetDesc->aSourceRange.aEnd.Row();
//STRIP001      nTab2 = pSheetDesc->aSourceRange.aEnd.Tab();
//STRIP001
//STRIP001      eRes = ScRefUpdate::Update( pDoc, eUpdateRefMode,
//STRIP001              rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
//STRIP001              rRange.aEnd.Col(), rRange.aEnd.Row(), rRange.aEnd.Tab(), nDx, nDy, nDz,
//STRIP001              nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001      if ( eRes != UR_NOTHING )
//STRIP001      {
//STRIP001          ScSheetSourceDesc aNewDesc;
//STRIP001          aNewDesc.aSourceRange = ScRange( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001
//STRIP001          short nDiffX = nCol1 - (short) pSheetDesc->aSourceRange.aStart.Col();
//STRIP001          short nDiffY = nRow1 - (short) pSheetDesc->aSourceRange.aStart.Row();
//STRIP001
//STRIP001          aNewDesc.aQueryParam = pSheetDesc->aQueryParam;
//STRIP001          aNewDesc.aQueryParam.nCol1 += nDiffX;
//STRIP001          aNewDesc.aQueryParam.nCol2 += nDiffX;
//STRIP001          aNewDesc.aQueryParam.nRow1 += nDiffY;   //! used?
//STRIP001          aNewDesc.aQueryParam.nRow2 += nDiffY;   //! used?
//STRIP001          USHORT nEC = aNewDesc.aQueryParam.GetEntryCount();
//STRIP001          for (USHORT i=0; i<nEC; i++)
//STRIP001              if (aNewDesc.aQueryParam.GetEntry(i).bDoQuery)
//STRIP001                  aNewDesc.aQueryParam.GetEntry(i).nField += nDiffX;
//STRIP001
//STRIP001          SetSheetDesc( aNewDesc );       // allocates new pSheetDesc
//STRIP001      }
//STRIP001  }
}

/*N*/ BOOL ScDPObject::RefsEqual( const ScDPObject& r ) const
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   if ( aOutRange != r.aOutRange )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( pSheetDesc && r.pSheetDesc )
//STRIP001  {
//STRIP001      if ( pSheetDesc->aSourceRange != r.pSheetDesc->aSourceRange )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  else if ( pSheetDesc || r.pSheetDesc )
//STRIP001  {
//STRIP001      DBG_ERROR("RefsEqual: SheetDesc set at only one object");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScDPObject::WriteRefsTo( ScDPObject& r ) const
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  r.SetOutRange( aOutRange );
//STRIP001  if ( pSheetDesc )
//STRIP001      r.SetSheetDesc( *pSheetDesc );
/*N*/ }

//STRIP001 String ScDPObject::GetDimName( long nDim, BOOL& rIsDataLayout )
//STRIP001 {
//STRIP001  rIsDataLayout = FALSE;
//STRIP001  String aRet;
//STRIP001
//STRIP001  if ( xSource.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XNameAccess> xDimsName = xSource->getDimensions();
//STRIP001      uno::Reference<container::XIndexAccess> xDims = new ScNameToIndexAccess( xDimsName );
//STRIP001      long nDimCount = xDims->getCount();
//STRIP001      if ( nDim < nDimCount )
//STRIP001      {
//STRIP001          uno::Reference<uno::XInterface> xIntDim =
//STRIP001              ScUnoHelpFunctions::AnyToInterface( xDims->getByIndex(nDim) );
//STRIP001          uno::Reference<container::XNamed> xDimName( xIntDim, uno::UNO_QUERY );
//STRIP001          uno::Reference<beans::XPropertySet> xDimProp( xIntDim, uno::UNO_QUERY );
//STRIP001          if ( xDimName.is() && xDimProp.is() )
//STRIP001          {
//STRIP001              BOOL bData = ScUnoHelpFunctions::GetBoolProperty( xDimProp,
//STRIP001                              rtl::OUString::createFromAscii(DP_PROP_ISDATALAYOUT) );
//STRIP001              //! error checking -- is "IsDataLayoutDimension" property required??
//STRIP001
//STRIP001              rtl::OUString aName;
//STRIP001              try
//STRIP001              {
//STRIP001                  aName = xDimName->getName();
//STRIP001              }
//STRIP001              catch(uno::Exception&)
//STRIP001              {
//STRIP001              }
//STRIP001              if ( bData )
//STRIP001                  rIsDataLayout = TRUE;
//STRIP001              else
//STRIP001                  aRet = String( aName );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 void ScDPObject::GetPositionData( ScDPPositionData& rData, const ScAddress& rPos )
//STRIP001 {
//STRIP001  CreateOutput();             // create xSource and pOutput if not already done
//STRIP001
//STRIP001  pOutput->GetPositionData( rData, rPos );
//STRIP001 }

//STRIP001 BOOL ScDPObject::IsFilterButton( const ScAddress& rPos )
//STRIP001 {
//STRIP001  CreateOutput();             // create xSource and pOutput if not already done
//STRIP001
//STRIP001  return pOutput->IsFilterButton( rPos );
//STRIP001 }

//STRIP001 long ScDPObject::GetHeaderDim( const ScAddress& rPos )
//STRIP001 {
//STRIP001  CreateOutput();             // create xSource and pOutput if not already done
//STRIP001
//STRIP001  return pOutput->GetHeaderDim( rPos );
//STRIP001 }

//STRIP001 BOOL ScDPObject::GetHeaderDrag( const ScAddress& rPos, BOOL bMouseLeft, BOOL bMouseTop, long nDragDim,
//STRIP001                              Rectangle& rPosRect, USHORT& rOrient, long& rDimPos )
//STRIP001 {
//STRIP001  CreateOutput();             // create xSource and pOutput if not already done
//STRIP001
//STRIP001  return pOutput->GetHeaderDrag( rPos, bMouseLeft, bMouseTop, nDragDim, rPosRect, rOrient, rDimPos );
//STRIP001 }

//STRIP001 void ScDPObject::ToggleDetails( ScDPPositionData& rElemDesc, ScDPObject* pDestObj )
//STRIP001 {
//STRIP001  CreateObjects();            // create xSource if not already done
//STRIP001
//STRIP001  //  find dimension name
//STRIP001
//STRIP001  uno::Reference<container::XNamed> xDim;
//STRIP001  uno::Reference<container::XNameAccess> xDimsName = xSource->getDimensions();
//STRIP001  uno::Reference<container::XIndexAccess> xIntDims = new ScNameToIndexAccess( xDimsName );
//STRIP001  long nIntCount = xIntDims->getCount();
//STRIP001  if ( rElemDesc.nDimension < nIntCount )
//STRIP001  {
//STRIP001      uno::Reference<uno::XInterface> xIntDim = ScUnoHelpFunctions::AnyToInterface(
//STRIP001                                  xIntDims->getByIndex(rElemDesc.nDimension) );
//STRIP001      xDim = uno::Reference<container::XNamed>( xIntDim, uno::UNO_QUERY );
//STRIP001  }
//STRIP001  DBG_ASSERT( xDim.is(), "dimension not found" );
//STRIP001  if ( !xDim.is() ) return;
//STRIP001  String aDimName = xDim->getName();
//STRIP001
//STRIP001  uno::Reference<beans::XPropertySet> xDimProp( xDim, uno::UNO_QUERY );
//STRIP001  BOOL bDataLayout = ScUnoHelpFunctions::GetBoolProperty( xDimProp,
//STRIP001                      rtl::OUString::createFromAscii(DP_PROP_ISDATALAYOUT) );
//STRIP001  if (bDataLayout)
//STRIP001  {
//STRIP001      //  the elements of the data layout dimension can't be found by their names
//STRIP001      //  -> don't change anything
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  //  query old state
//STRIP001
//STRIP001  long nHierCount = 0;
//STRIP001  uno::Reference<container::XIndexAccess> xHiers;
//STRIP001  uno::Reference<sheet::XHierarchiesSupplier> xHierSupp( xDim, uno::UNO_QUERY );
//STRIP001  if ( xHierSupp.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XNameAccess> xHiersName = xHierSupp->getHierarchies();
//STRIP001      xHiers = new ScNameToIndexAccess( xHiersName );
//STRIP001      nHierCount = xHiers->getCount();
//STRIP001  }
//STRIP001  uno::Reference<uno::XInterface> xHier;
//STRIP001  if ( rElemDesc.nHierarchy < nHierCount )
//STRIP001      xHier = ScUnoHelpFunctions::AnyToInterface( xHiers->getByIndex(rElemDesc.nHierarchy) );
//STRIP001  DBG_ASSERT( xHier.is(), "hierarchy not found" );
//STRIP001  if ( !xHier.is() ) return;
//STRIP001
//STRIP001  long nLevCount = 0;
//STRIP001  uno::Reference<container::XIndexAccess> xLevels;
//STRIP001  uno::Reference<sheet::XLevelsSupplier> xLevSupp( xHier, uno::UNO_QUERY );
//STRIP001  if ( xLevSupp.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XNameAccess> xLevsName = xLevSupp->getLevels();
//STRIP001      xLevels = new ScNameToIndexAccess( xLevsName );
//STRIP001      nLevCount = xLevels->getCount();
//STRIP001  }
//STRIP001  uno::Reference<uno::XInterface> xLevel;
//STRIP001  if ( rElemDesc.nLevel < nLevCount )
//STRIP001      xLevel = ScUnoHelpFunctions::AnyToInterface( xLevels->getByIndex(rElemDesc.nLevel) );
//STRIP001  DBG_ASSERT( xLevel.is(), "level not found" );
//STRIP001  if ( !xLevel.is() ) return;
//STRIP001
//STRIP001  uno::Reference<container::XNameAccess> xMembers;
//STRIP001  uno::Reference<sheet::XMembersSupplier> xMbrSupp( xLevel, uno::UNO_QUERY );
//STRIP001  if ( xMbrSupp.is() )
//STRIP001      xMembers = xMbrSupp->getMembers();
//STRIP001
//STRIP001  BOOL bFound = FALSE;
//STRIP001  BOOL bShowDetails = TRUE;
//STRIP001
//STRIP001  if ( xMembers.is() )
//STRIP001  {
//STRIP001      rtl::OUString aName = rElemDesc.aMemberName;
//STRIP001      if ( xMembers->hasByName( aName ) )
//STRIP001      {
//STRIP001          uno::Reference<uno::XInterface> xMemberInt = ScUnoHelpFunctions::AnyToInterface(
//STRIP001                                          xMembers->getByName( aName ) );
//STRIP001          uno::Reference<beans::XPropertySet> xMbrProp( xMemberInt, uno::UNO_QUERY );
//STRIP001          if ( xMbrProp.is() )
//STRIP001          {
//STRIP001              bShowDetails = ScUnoHelpFunctions::GetBoolProperty( xMbrProp,
//STRIP001                                  rtl::OUString::createFromAscii(DP_PROP_SHOWDETAILS) );
//STRIP001              //! don't set bFound if property is unknown?
//STRIP001              bFound = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  DBG_ASSERT( bFound, "member not found" );
//STRIP001
//STRIP001  //! use Hierarchy and Level in SaveData !!!!
//STRIP001
//STRIP001  //  modify pDestObj if set, this object otherwise
//STRIP001  ScDPSaveData* pModifyData = pDestObj ? ( pDestObj->pSaveData ) : pSaveData;
//STRIP001  DBG_ASSERT( pModifyData, "no data?" );
//STRIP001  if ( pModifyData )
//STRIP001  {
//STRIP001      pModifyData->GetDimensionByName(aDimName)->
//STRIP001          GetMemberByName(rElemDesc.aMemberName)->SetShowDetails( !bShowDetails );    // toggle
//STRIP001
//STRIP001      if ( pDestObj )
//STRIP001          pDestObj->InvalidateData();     // re-init source from SaveData
//STRIP001      else
//STRIP001          InvalidateData();               // re-init source from SaveData
//STRIP001  }
//STRIP001 }

//STRIP001 long lcl_FindName( const rtl::OUString& rString, const uno::Reference<container::XNameAccess>& xCollection )
//STRIP001 {
//STRIP001  if ( xCollection.is() )
//STRIP001  {
//STRIP001      uno::Sequence<rtl::OUString> aSeq = xCollection->getElementNames();
//STRIP001      long nCount = aSeq.getLength();
//STRIP001      const rtl::OUString* pArr = aSeq.getConstArray();
//STRIP001      for (long nPos=0; nPos<nCount; nPos++)
//STRIP001          if ( pArr[nPos] == rString )
//STRIP001              return nPos;
//STRIP001  }
//STRIP001  return -1;      // not found
//STRIP001 }

/*N*/ USHORT lcl_FirstSubTotal( const uno::Reference<beans::XPropertySet>& xDimProp )       // PIVOT_FUNC mask
/*N*/ {
/*N*/   uno::Reference<sheet::XHierarchiesSupplier> xDimSupp( xDimProp, uno::UNO_QUERY );
/*N*/   if ( xDimProp.is() && xDimSupp.is() )
/*N*/   {
/*N*/       uno::Reference<container::XIndexAccess> xHiers = new ScNameToIndexAccess( xDimSupp->getHierarchies() );
/*N*/       long nHierarchy = ScUnoHelpFunctions::GetLongProperty( xDimProp,
/*N*/                               rtl::OUString::createFromAscii(DP_PROP_USEDHIERARCHY) );
/*N*/       if ( nHierarchy >= xHiers->getCount() )
/*N*/           nHierarchy = 0;
/*N*/
/*N*/       uno::Reference<uno::XInterface> xHier = ScUnoHelpFunctions::AnyToInterface(
/*N*/                                   xHiers->getByIndex(nHierarchy) );
/*N*/       uno::Reference<sheet::XLevelsSupplier> xHierSupp( xHier, uno::UNO_QUERY );
/*N*/       if ( xHierSupp.is() )
/*N*/       {
/*N*/           uno::Reference<container::XIndexAccess> xLevels = new ScNameToIndexAccess( xHierSupp->getLevels() );
/*N*/           uno::Reference<uno::XInterface> xLevel =
/*N*/               ScUnoHelpFunctions::AnyToInterface( xLevels->getByIndex( 0 ) );
/*N*/           uno::Reference<beans::XPropertySet> xLevProp( xLevel, uno::UNO_QUERY );
/*N*/           if ( xLevProp.is() )
/*N*/           {
/*N*/               uno::Any aSubAny;
/*N*/               try
/*N*/               {
/*N*/                   aSubAny = xLevProp->getPropertyValue(
/*N*/                           rtl::OUString::createFromAscii(DP_PROP_SUBTOTALS) );
/*N*/               }
/*N*/               catch(uno::Exception&)
/*N*/               {
/*N*/               }
/*N*/               uno::Sequence<sheet::GeneralFunction> aSeq;
/*N*/               if ( aSubAny >>= aSeq )
/*N*/               {
/*N*/                   USHORT nMask = 0;
/*N*/                   const sheet::GeneralFunction* pArray = aSeq.getConstArray();
/*N*/                   long nCount = aSeq.getLength();
/*N*/                   for (long i=0; i<nCount; i++)
/*?*/                       nMask |= ScDataPilotConversion::FunctionBit(pArray[i]);
/*N*/                   return nMask;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*?*/   DBG_ERROR("FirstSubTotal: NULL");
/*?*/   return 0;
/*N*/ }

/*N*/ USHORT lcl_CountBits( USHORT nBits )
/*N*/ {
/*N*/   if (!nBits) return 0;
/*N*/
/*N*/   USHORT nCount = 0;
/*N*/   USHORT nMask = 1;
/*N*/   for (USHORT i=0; i<16; i++)
/*N*/   {
/*N*/       if ( nBits & nMask )
/*N*/           ++nCount;
/*N*/       nMask <<= 1;
/*N*/   }
/*N*/   return nCount;
/*N*/ }

/*N*/ USHORT lcl_FillOldFields( PivotField* pFields,
/*N*/                           const uno::Reference<sheet::XDimensionsSupplier>& xSource,
/*N*/                           USHORT nOrient, USHORT nColAdd, BOOL bAddData )
/*N*/ {
/*N*/   USHORT nOutCount = 0;
/*N*/   BOOL bDataFound = FALSE;
/*N*/
/*N*/   //! merge multiple occurences (data field with different functions)
/*N*/   //! force data field in one dimension
/*N*/
/*N*/   long nPos[PIVOT_MAXFIELD];
/*N*/
/*N*/   uno::Reference<container::XNameAccess> xDimsName = xSource->getDimensions();
/*N*/   uno::Reference<container::XIndexAccess> xDims = new ScNameToIndexAccess( xDimsName );
/*N*/   long nDimCount = xDims->getCount();
/*N*/   for (long nDim=0; nDim < nDimCount && nOutCount < PIVOT_MAXFIELD; nDim++)
/*N*/   {
/*N*/       uno::Reference<uno::XInterface> xIntDim =
/*N*/           ScUnoHelpFunctions::AnyToInterface( xDims->getByIndex(nDim) );
/*N*/       uno::Reference<beans::XPropertySet> xDimProp( xIntDim, uno::UNO_QUERY );
/*N*/       long nDimOrient = ScUnoHelpFunctions::GetEnumProperty(
/*N*/                           xDimProp, rtl::OUString::createFromAscii(DP_PROP_ORIENTATION),
/*N*/                           sheet::DataPilotFieldOrientation_HIDDEN );
/*N*/       if ( xDimProp.is() && nDimOrient == nOrient )
/*N*/       {
/*N*/           USHORT nMask = 0;
/*N*/           if ( nOrient == sheet::DataPilotFieldOrientation_DATA )
/*N*/           {
/*N*/               sheet::GeneralFunction eFunc = (sheet::GeneralFunction)ScUnoHelpFunctions::GetEnumProperty(
/*N*/                                           xDimProp, rtl::OUString::createFromAscii(DP_PROP_FUNCTION),
/*N*/                                           sheet::GeneralFunction_NONE );
/*N*/               if ( eFunc == sheet::GeneralFunction_AUTO )
/*N*/               {
/*N*/                   //! test for numeric data
/*?*/                   eFunc = sheet::GeneralFunction_SUM;
/*N*/               }
/*N*/               nMask = ScDataPilotConversion::FunctionBit(eFunc);
/*N*/           }
/*N*/           else
/*N*/               nMask = lcl_FirstSubTotal( xDimProp );      // from first hierarchy
/*N*/
/*N*/           BOOL bDataLayout = ScUnoHelpFunctions::GetBoolProperty( xDimProp,
/*N*/                                   rtl::OUString::createFromAscii(DP_PROP_ISDATALAYOUT) );
/*N*/           uno::Any aOrigAny;
/*N*/           try
/*N*/           {
/*N*/               aOrigAny = xDimProp->getPropertyValue(
/*N*/                               rtl::OUString::createFromAscii(DP_PROP_ORIGINAL) );
/*N*/           }
/*N*/           catch(uno::Exception&)
/*N*/           {
/*N*/           }
/*N*/
/*N*/           long nDupSource = -1;
/*N*/           uno::Reference<uno::XInterface> xIntOrig = ScUnoHelpFunctions::AnyToInterface( aOrigAny );
/*N*/           if ( xIntOrig.is() )
/*N*/           {
/*?*/               uno::Reference<container::XNamed> xNameOrig( xIntOrig, uno::UNO_QUERY );
/*?*/               if ( xNameOrig.is() )
/*?*/               {DBG_ASSERT(0, "STRIP");} //STRIP001    nDupSource = lcl_FindName( xNameOrig->getName(), xDimsName );
/*N*/           }
/*N*/
/*N*/           BOOL bDupUsed = FALSE;
/*N*/           if ( nDupSource >= 0 )
/*N*/           {
/*?*/               //  add function bit to previous entry
/*?*/
/*?*/               short nCompCol;
/*?*/               if ( bDataLayout )
/*?*/                   nCompCol = PIVOT_DATA_FIELD;
/*?*/               else
/*?*/                   nCompCol = (short)(nDupSource+nColAdd);     //! seek source column from name
/*?*/
/*?*/               for (USHORT nOld=0; nOld<nOutCount && !bDupUsed; nOld++)
/*?*/                   if ( pFields[nOld].nCol == nCompCol )
/*?*/                   {
/*?*/                       //  add to previous column only if new bits aren't already set there
/*?*/                       if ( ( pFields[nOld].nFuncMask & nMask ) == 0 )
/*?*/                       {
/*?*/                           pFields[nOld].nFuncMask |= nMask;
/*?*/                           pFields[nOld].nFuncCount = lcl_CountBits( pFields[nOld].nFuncMask );
/*?*/                           bDupUsed = TRUE;
/*?*/                       }
/*?*/                   }
/*N*/           }
/*N*/
/*N*/           if ( !bDupUsed )        // also for duplicated dim if original has different orientation
/*N*/           {
/*N*/               if ( bDataLayout )
/*N*/               {
/*N*/                   pFields[nOutCount].nCol = PIVOT_DATA_FIELD;
/*N*/                   bDataFound = TRUE;
/*N*/               }
/*N*/               else if ( nDupSource >= 0 )     // if source was not found (different orientation)
/*?*/                   pFields[nOutCount].nCol = (short)(nDupSource+nColAdd);      //! seek from name
/*N*/               else
/*N*/                   pFields[nOutCount].nCol = (short)(nDim+nColAdd);    //! seek source column from name
/*N*/
/*N*/               pFields[nOutCount].nFuncMask = nMask;
/*N*/               pFields[nOutCount].nFuncCount = lcl_CountBits( nMask );
/*N*/               nPos[nOutCount] = ScUnoHelpFunctions::GetLongProperty( xDimProp,
/*N*/                                   rtl::OUString::createFromAscii(DP_PROP_POSITION) );
/*N*/               ++nOutCount;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //  sort by getPosition() value
/*N*/
/*N*/   for (long i=0; i+1<nOutCount; i++)
/*N*/   {
/*N*/       for (long j=0; j+i+1<nOutCount; j++)
/*N*/           if ( nPos[j+1] < nPos[j] )
/*N*/           {
/*?*/               long nTemp = nPos[j+1];
/*?*/               nPos[j+1] = nPos[j];
/*?*/               nPos[j] = nTemp;
/*?*/               PivotField aField = pFields[j+1];
/*?*/               pFields[j+1] = pFields[j];
/*?*/               pFields[j] = aField;
/*N*/           }
/*N*/   }
/*N*/
/*N*/   if ( bAddData && !bDataFound )
/*N*/   {
/*?*/       if ( nOutCount >= PIVOT_MAXFIELD )              //  space for data field?
/*?*/           --nOutCount;                                //! error?
/*?*/       pFields[nOutCount].nCol = PIVOT_DATA_FIELD;
/*?*/       pFields[nOutCount].nFuncMask = 0;
/*?*/       pFields[nOutCount].nFuncCount = 0;
/*?*/       ++nOutCount;
/*N*/   }
/*N*/
/*N*/   return nOutCount;
/*N*/ }

/*N*/ void lcl_SaveOldFieldArr( SvStream& rStream,
/*N*/                           const uno::Reference<sheet::XDimensionsSupplier>& xSource,
/*N*/                           USHORT nOrient, USHORT nColAdd, BOOL bAddData )
/*N*/ {
/*N*/   // PIVOT_MAXFIELD = max. number in old files
/*N*/   PivotField aFields[PIVOT_MAXFIELD];
/*N*/   USHORT nOutCount = lcl_FillOldFields( aFields, xSource, nOrient, nColAdd, bAddData );
/*N*/
/*N*/   rStream << nOutCount;
/*N*/   for (USHORT i=0; i<nOutCount; i++)
/*N*/   {
/*N*/       rStream << (BYTE) 0x00
/*N*/               << aFields[i].nCol
/*N*/               << aFields[i].nFuncMask
/*N*/               << aFields[i].nFuncCount;
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDPObject::StoreNew( SvStream& rStream, ScMultipleWriteHeader& rHdr ) const
/*N*/ {
/*N*/   //  save all data
/*N*/
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   if ( pImpDesc )
/*N*/   {
/*N*/       rStream << (BYTE) SC_DP_SOURCE_DATABASE;
/*N*/       rStream.WriteByteString( pImpDesc->aDBName, rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( pImpDesc->aObject, rStream.GetStreamCharSet() );
/*N*/       rStream << pImpDesc->nType;     // USHORT
/*N*/       rStream << pImpDesc->bNative;
/*N*/   }
/*N*/   else if ( pServDesc )
/*N*/   {
/*N*/       rStream << (BYTE) SC_DP_SOURCE_SERVICE;
/*N*/       rStream.WriteByteString( pServDesc->aServiceName, rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( pServDesc->aParSource,   rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( pServDesc->aParName,     rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( pServDesc->aParUser,     rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( pServDesc->aParPass,     rStream.GetStreamCharSet() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if (!pSheetDesc)
/*N*/       {
/*N*/           DBG_ERROR("no source descriptor");
/*N*/           ((ScDPObject*)this)->pSheetDesc = new ScSheetSourceDesc;        // dummy defaults
/*N*/       }
/*N*/
/*N*/       rStream << (BYTE) SC_DP_SOURCE_SHEET;
/*N*/       rStream << pSheetDesc->aSourceRange;
/*N*/       pSheetDesc->aQueryParam.Store( rStream );
/*N*/   }
/*N*/
/*N*/   rStream << aOutRange;
/*N*/
/*N*/   DBG_ASSERT(pSaveData, "ScDPObject::StoreNew no SaveData");
/*N*/   pSaveData->Store( rStream );
/*N*/
/*N*/   //  additional data starting from 561b
/*N*/   rStream.WriteByteString( aTableName, rStream.GetStreamCharSet() );
/*N*/   rStream.WriteByteString( aTableTag,  rStream.GetStreamCharSet() );
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/   return TRUE;
/*N*/ }
/*N*/
/*N*/ BOOL ScDPObject::LoadNew(SvStream& rStream, ScMultipleReadHeader& rHdr )
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   DELETEZ( pImpDesc );
/*N*/   DELETEZ( pSheetDesc );
/*N*/   DELETEZ( pServDesc );
/*N*/
/*N*/   BYTE nType;
/*N*/   rStream >> nType;
/*N*/   switch (nType)
/*N*/   {
/*N*/       case SC_DP_SOURCE_DATABASE:
/*N*/           pImpDesc = new ScImportSourceDesc;
/*N*/           rStream.ReadByteString( pImpDesc->aDBName, rStream.GetStreamCharSet() );
/*N*/           rStream.ReadByteString( pImpDesc->aObject, rStream.GetStreamCharSet() );
/*N*/           rStream >> pImpDesc->nType;     // USHORT
/*N*/           rStream >> pImpDesc->bNative;
/*N*/           break;
/*N*/
/*N*/       case SC_DP_SOURCE_SHEET:
/*N*/           pSheetDesc = new ScSheetSourceDesc;
/*N*/           rStream >> pSheetDesc->aSourceRange;
/*N*/           pSheetDesc->aQueryParam.Load( rStream );
/*N*/           break;
/*N*/
/*N*/       case SC_DP_SOURCE_SERVICE:
/*N*/           {
/*N*/               String aServiceName, aParSource, aParName, aParUser, aParPass;
/*N*/               rStream.ReadByteString( aServiceName, rStream.GetStreamCharSet() );
/*N*/               rStream.ReadByteString( aParSource,   rStream.GetStreamCharSet() );
/*N*/               rStream.ReadByteString( aParName,     rStream.GetStreamCharSet() );
/*N*/               rStream.ReadByteString( aParUser,     rStream.GetStreamCharSet() );
/*N*/               rStream.ReadByteString( aParPass,     rStream.GetStreamCharSet() );
/*N*/               pServDesc = new ScDPServiceDesc( aServiceName,
/*N*/                                       aParSource, aParName, aParUser, aParPass );
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           DBG_ERROR("unknown source type");
/*N*/   }
/*N*/
/*N*/   rStream >> aOutRange;
/*N*/
/*N*/   SetSaveData(ScDPSaveData());
/*N*/   pSaveData->Load( rStream );
/*N*/
/*N*/   if (rHdr.BytesLeft())       //  additional data starting from 561b
/*N*/   {
/*N*/       rStream.ReadByteString( aTableName, rStream.GetStreamCharSet() );
/*N*/       rStream.ReadByteString( aTableTag,  rStream.GetStreamCharSet() );
/*N*/   }
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDPObject::StoreOld( SvStream& rStream, ScMultipleWriteHeader& rHdr ) const
/*N*/ {
/*N*/   //  write compatible data for office 5.1 and below
/*N*/
/*N*/   DBG_ASSERT( pSheetDesc, "StoreOld: !pSheetDesc" );
/*N*/   ScRange aStoreRange;
/*N*/   ScQueryParam aStoreQuery;
/*N*/   if (pSheetDesc)
/*N*/   {
/*N*/       aStoreRange = pSheetDesc->aSourceRange;
/*N*/       aStoreQuery = pSheetDesc->aQueryParam;
/*N*/   }
/*N*/
/*N*/   ((ScDPObject*)this)->CreateObjects();       // xSource is needed for field numbers
/*N*/
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rStream << (BOOL) TRUE;         // bHasHeader
/*N*/
/*N*/   rStream << aStoreRange.aStart.Col();
/*N*/   rStream << aStoreRange.aStart.Row();
/*N*/   rStream << aStoreRange.aEnd.Col();
/*N*/   rStream << aStoreRange.aEnd.Row();
/*N*/   rStream << aStoreRange.aStart.Tab();
/*N*/
/*N*/   //! make sure aOutRange is initialized
/*N*/
/*N*/   rStream << aOutRange.aStart.Col();
/*N*/   rStream << aOutRange.aStart.Row();
/*N*/   rStream << aOutRange.aEnd.Col();
/*N*/   rStream << aOutRange.aEnd.Row();
/*N*/   rStream << aOutRange.aStart.Tab();
/*N*/
/*N*/   BOOL bAddData = ( lcl_GetDataGetOrientation( xSource ) == sheet::DataPilotFieldOrientation_HIDDEN );
/*N*/
/*N*/   lcl_SaveOldFieldArr( rStream, xSource, sheet::DataPilotFieldOrientation_ROW,    aStoreRange.aStart.Col(), bAddData );
/*N*/   lcl_SaveOldFieldArr( rStream, xSource, sheet::DataPilotFieldOrientation_COLUMN, aStoreRange.aStart.Col(), FALSE );
/*N*/   lcl_SaveOldFieldArr( rStream, xSource, sheet::DataPilotFieldOrientation_DATA,   aStoreRange.aStart.Col(), FALSE );
/*N*/
/*N*/   aStoreQuery.Store( rStream );
/*N*/
/*N*/   BOOL bColumnGrand   = TRUE;
/*N*/   BOOL bRowGrand      = TRUE;
/*N*/   BOOL bIgnoreEmpty   = FALSE;
/*N*/   BOOL bRepeatIfEmpty = FALSE;
/*N*/
/*N*/   uno::Reference<beans::XPropertySet> xProp( xSource, uno::UNO_QUERY );
/*N*/   if (xProp.is())
/*N*/   {
/*N*/       bColumnGrand = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_COLUMNGRAND), TRUE );
/*N*/       bRowGrand = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_ROWGRAND), TRUE );
/*N*/
/*N*/       // following properties may be missing for external sources
/*N*/       bIgnoreEmpty = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_IGNOREEMPTY) );
/*N*/       bRepeatIfEmpty = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_REPEATIFEMPTY) );
/*N*/   }
/*N*/
/*N*/   rStream << bIgnoreEmpty;        // bIgnoreEmpty
/*N*/   rStream << bRepeatIfEmpty;      // bDetectCat
/*N*/
/*N*/   rStream << bColumnGrand;        // bMakeTotalCol
/*N*/   rStream << bRowGrand;           // bMakeTotalRow
/*N*/
/*N*/   if( rStream.GetVersion() > SOFFICE_FILEFORMAT_40 )
/*N*/   {
/*N*/       rStream.WriteByteString( aTableName, rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( aTableTag,  rStream.GetStreamCharSet() );
/*N*/       rStream << (USHORT)0;       // nColNameCount
/*N*/   }
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDPObject::FillOldParam(ScPivotParam& rParam, BOOL bForFile) const
/*N*/ {
/*N*/   ((ScDPObject*)this)->CreateObjects();       // xSource is needed for field numbers
/*N*/
/*N*/   rParam.nCol = aOutRange.aStart.Col();
/*N*/   rParam.nRow = aOutRange.aStart.Row();
/*N*/   rParam.nTab = aOutRange.aStart.Tab();
/*N*/   // ppLabelArr / nLabels is not changed
/*N*/
/*N*/   USHORT nColAdd = 0;
/*N*/   if ( bForFile )
/*N*/   {
/*N*/       // in old file format, columns are within document, not within source range
/*N*/
/*N*/       DBG_ASSERT( pSheetDesc, "FillOldParam: bForFile, !pSheetDesc" );
/*N*/       nColAdd = pSheetDesc->aSourceRange.aStart.Col();
/*N*/   }
/*N*/
/*N*/   BOOL bAddData = ( lcl_GetDataGetOrientation( xSource ) == sheet::DataPilotFieldOrientation_HIDDEN );
/*N*/   rParam.nColCount  = lcl_FillOldFields( rParam.aColArr,
/*N*/                           xSource, sheet::DataPilotFieldOrientation_COLUMN, nColAdd, bAddData );
/*N*/   rParam.nRowCount  = lcl_FillOldFields( rParam.aRowArr,
/*N*/                           xSource, sheet::DataPilotFieldOrientation_ROW,    nColAdd, FALSE );
/*N*/   rParam.nDataCount = lcl_FillOldFields( rParam.aDataArr,
/*N*/                           xSource, sheet::DataPilotFieldOrientation_DATA,   nColAdd, FALSE );
/*N*/
/*N*/   uno::Reference<beans::XPropertySet> xProp( xSource, uno::UNO_QUERY );
/*N*/   if (xProp.is())
/*N*/   {
/*N*/       try
/*N*/       {
/*N*/           rParam.bMakeTotalCol = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_COLUMNGRAND), TRUE );
/*N*/           rParam.bMakeTotalRow = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_ROWGRAND), TRUE );
/*N*/
/*N*/           // following properties may be missing for external sources
/*N*/           rParam.bIgnoreEmptyRows = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_IGNOREEMPTY) );
/*N*/           rParam.bDetectCategories = ScUnoHelpFunctions::GetBoolProperty( xProp,
/*N*/                       rtl::OUString::createFromAscii(DP_PROP_REPEATIFEMPTY) );
/*N*/       }
/*N*/       catch(uno::Exception&)
/*N*/       {
/*N*/           // no error
/*N*/       }
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

//STRIP001 BOOL lcl_ShowEmptyFromDim( const uno::Reference<beans::XPropertySet>& xDimProp )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  uno::Reference<sheet::XHierarchiesSupplier> xDimSupp( xDimProp, uno::UNO_QUERY );
//STRIP001  if ( xDimProp.is() && xDimSupp.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XIndexAccess> xHiers = new ScNameToIndexAccess( xDimSupp->getHierarchies() );
//STRIP001      long nHierarchy = ScUnoHelpFunctions::GetLongProperty( xDimProp,
//STRIP001                              rtl::OUString::createFromAscii(DP_PROP_USEDHIERARCHY) );
//STRIP001      if ( nHierarchy >= xHiers->getCount() )
//STRIP001          nHierarchy = 0;
//STRIP001
//STRIP001      uno::Reference<uno::XInterface> xHier = ScUnoHelpFunctions::AnyToInterface(
//STRIP001                                  xHiers->getByIndex(nHierarchy) );
//STRIP001      uno::Reference<sheet::XLevelsSupplier> xHierSupp( xHier, uno::UNO_QUERY );
//STRIP001      if ( xHierSupp.is() )
//STRIP001      {
//STRIP001          uno::Reference<container::XIndexAccess> xLevels = new ScNameToIndexAccess( xHierSupp->getLevels() );
//STRIP001          uno::Reference<uno::XInterface> xLevel =
//STRIP001              ScUnoHelpFunctions::AnyToInterface( xLevels->getByIndex( 0 ) );
//STRIP001          uno::Reference<beans::XPropertySet> xLevProp( xLevel, uno::UNO_QUERY );
//STRIP001          if ( xLevProp.is() )
//STRIP001              bRet = ScUnoHelpFunctions::GetBoolProperty( xLevProp,
//STRIP001                                  rtl::OUString::createFromAscii(DP_PROP_SHOWEMPTY) );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL ScDPObject::FillLabelData(ScPivotParam& rParam, BOOL* pShowAll, USHORT nShowAllMax) const
//STRIP001 {
//STRIP001  ((ScDPObject*)this)->CreateObjects();
//STRIP001
//STRIP001  uno::Reference<container::XNameAccess> xDimsName = xSource->getDimensions();
//STRIP001  uno::Reference<container::XIndexAccess> xDims = new ScNameToIndexAccess( xDimsName );
//STRIP001  long nDimCount = xDims->getCount();
//STRIP001  if ( nDimCount > MAX_LABELS )
//STRIP001      nDimCount = MAX_LABELS;
//STRIP001  if (!nDimCount)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nOutCount = 0;
//STRIP001  LabelData** aLabelArr = new LabelData*[nDimCount];
//STRIP001  for (long nDim=0; nDim < nDimCount; nDim++)
//STRIP001  {
//STRIP001      String aFieldName;
//STRIP001      uno::Reference<uno::XInterface> xIntDim =
//STRIP001          ScUnoHelpFunctions::AnyToInterface( xDims->getByIndex(nDim) );
//STRIP001      uno::Reference<container::XNamed> xDimName( xIntDim, uno::UNO_QUERY );
//STRIP001      uno::Reference<beans::XPropertySet> xDimProp( xIntDim, uno::UNO_QUERY );
//STRIP001
//STRIP001      if ( xDimName.is() && xDimProp.is() )
//STRIP001      {
//STRIP001          BOOL bDuplicated = FALSE;
//STRIP001          BOOL bData = ScUnoHelpFunctions::GetBoolProperty( xDimProp,
//STRIP001                          rtl::OUString::createFromAscii(DP_PROP_ISDATALAYOUT) );
//STRIP001          //! error checking -- is "IsDataLayoutDimension" property required??
//STRIP001
//STRIP001          try
//STRIP001          {
//STRIP001              aFieldName = String( xDimName->getName() );
//STRIP001
//STRIP001              uno::Any aOrigAny = xDimProp->getPropertyValue(
//STRIP001                          rtl::OUString::createFromAscii(DP_PROP_ORIGINAL) );
//STRIP001              uno::Reference<uno::XInterface> xIntOrig;
//STRIP001              if ( (aOrigAny >>= xIntOrig) && xIntOrig.is() )
//STRIP001                  bDuplicated = TRUE;
//STRIP001          }
//STRIP001          catch(uno::Exception&)
//STRIP001          {
//STRIP001          }
//STRIP001
//STRIP001          if ( aFieldName.Len() && !bData && !bDuplicated )
//STRIP001          {
//STRIP001              BOOL bIsValue = TRUE;       //! check
//STRIP001              USHORT nCol = nDim;         //! ???
//STRIP001
//STRIP001              aLabelArr[nOutCount] = new LabelData( aFieldName, nCol, bIsValue );
//STRIP001              if ( pShowAll && nOutCount < nShowAllMax )
//STRIP001                  pShowAll[nOutCount] = lcl_ShowEmptyFromDim( xDimProp );
//STRIP001
//STRIP001              ++nOutCount;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rParam.SetLabelData( aLabelArr, nOutCount );
//STRIP001
//STRIP001  for (USHORT i=0; i<nOutCount; i++)
//STRIP001      delete aLabelArr[i];
//STRIP001  delete[] aLabelArr;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//------------------------------------------------------------------------
//  convert old pivot tables into new datapilot tables

//STRIP001 String lcl_GetDimName( const uno::Reference<sheet::XDimensionsSupplier>& xSource, long nDim )
//STRIP001 {
//STRIP001  rtl::OUString aName;
//STRIP001  if ( xSource.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XNameAccess> xDimsName = xSource->getDimensions();
//STRIP001      uno::Reference<container::XIndexAccess> xDims = new ScNameToIndexAccess( xDimsName );
//STRIP001      long nDimCount = xDims->getCount();
//STRIP001      if ( nDim < nDimCount )
//STRIP001      {
//STRIP001          uno::Reference<uno::XInterface> xIntDim =
//STRIP001              ScUnoHelpFunctions::AnyToInterface( xDims->getByIndex(nDim) );
//STRIP001          uno::Reference<container::XNamed> xDimName( xIntDim, uno::UNO_QUERY );
//STRIP001          if (xDimName.is())
//STRIP001          {
//STRIP001              try
//STRIP001              {
//STRIP001                  aName = xDimName->getName();
//STRIP001              }
//STRIP001              catch(uno::Exception&)
//STRIP001              {
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return aName;
//STRIP001 }

// static
/*N*/ void ScDPObject::ConvertOrientation( ScDPSaveData& rSaveData,
/*N*/                           PivotField* pFields, USHORT nCount, USHORT nOrient,
/*N*/                           ScDocument* pDoc, USHORT nRow, USHORT nTab,
/*N*/                           const uno::Reference<sheet::XDimensionsSupplier>& xSource,
/*N*/                           BOOL bOldDefaults,
/*N*/                           PivotField* pRefColFields, USHORT nRefColCount,
/*N*/                           PivotField* pRefRowFields, USHORT nRefRowCount )
/*N*/ {
/*N*/   //  pDoc or xSource must be set
/*N*/   DBG_ASSERT( pDoc || xSource.is(), "missing string source" );
/*N*/
/*N*/   String aDocStr;
/*N*/   ScDPSaveDimension* pDim;
/*N*/
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*N*/       USHORT nCol = pFields[i].nCol;
/*N*/       USHORT nFuncs = pFields[i].nFuncMask;
/*N*/       if ( nCol == PIVOT_DATA_FIELD )
/*N*/           pDim = rSaveData.GetDataLayoutDimension();
/*N*/       else
/*N*/       {
/*N*/           if ( pDoc )
/*N*/               pDoc->GetString( nCol, nRow, nTab, aDocStr );
/*N*/           else
/*?*/           {DBG_ASSERT(0, "STRIP");} //STRIP001    aDocStr = lcl_GetDimName( xSource, nCol );  // cols must start at 0
/*N*/
/*N*/           if ( aDocStr.Len() )
/*N*/               pDim = rSaveData.GetDimensionByName(aDocStr);
/*N*/           else
/*?*/               pDim = NULL;
/*N*/       }
/*N*/
/*N*/       if ( pDim )
/*N*/       {
/*N*/           if ( nOrient == sheet::DataPilotFieldOrientation_DATA )     // set summary function
/*N*/           {
/*N*/               //  generate an individual entry for each function
/*N*/               BOOL bFirst = TRUE;
/*N*/
/*N*/               //  if a dimension is used for column or row and data,
/*N*/               //  use duplicated dimensions for all data occurrences
/*N*/               if (pRefColFields)
/*N*/                   for (USHORT nRefCol=0; nRefCol<nRefColCount; nRefCol++)
/*N*/                       if (pRefColFields[nRefCol].nCol == nCol)
/*?*/                           bFirst = FALSE;
/*N*/               if (pRefRowFields)
/*N*/                   for (USHORT nRefRow=0; nRefRow<nRefRowCount; nRefRow++)
/*N*/                       if (pRefRowFields[nRefRow].nCol == nCol)
/*?*/                           bFirst = FALSE;
/*N*/
/*N*/               //  if set via api, a data column may occur several times
/*N*/               //  (if the function hasn't been changed yet) -> also look for duplicate data column
/*N*/               for (USHORT nPrevData=0; nPrevData<i; nPrevData++)
/*?*/                   if (pFields[nPrevData].nCol == nCol)
/*?*/                       bFirst = FALSE;
/*N*/
/*N*/               USHORT nMask = 1;
/*N*/               for (USHORT nBit=0; nBit<16; nBit++)
/*N*/               {
/*N*/                   if ( nFuncs & nMask )
/*N*/                   {
/*N*/                       sheet::GeneralFunction eFunc = ScDataPilotConversion::FirstFunc( nMask );
/*N*/                       if (bFirst)
/*N*/                       {
/*N*/                           pDim->SetOrientation( nOrient );
/*N*/                           pDim->SetFunction( eFunc );
/*N*/                           bFirst = FALSE;
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*?*/                           ScDPSaveDimension* pDup = rSaveData.DuplicateDimension(pDim->GetName());
/*?*/                           pDup->SetOrientation( nOrient );
/*?*/                           pDup->SetFunction( eFunc );
/*N*/                       }
/*N*/                   }
/*N*/                   nMask *= 2;
/*N*/               }
/*N*/           }
/*N*/           else                                            // set SubTotals
/*N*/           {
/*N*/               pDim->SetOrientation( nOrient );
/*N*/
/*N*/               USHORT nFuncArray[16];
/*N*/               USHORT nFuncCount = 0;
/*N*/               USHORT nMask = 1;
/*N*/               for (USHORT nBit=0; nBit<16; nBit++)
/*N*/               {
/*N*/                   if ( nFuncs & nMask )
/*?*/                       nFuncArray[nFuncCount++] = ScDataPilotConversion::FirstFunc( nMask );
/*N*/                   nMask *= 2;
/*N*/               }
/*N*/               pDim->SetSubTotals( nFuncCount, nFuncArray );
/*N*/
/*N*/               //  ShowEmpty was implicit in old tables,
/*N*/               //  must be set for data layout dimension (not accessible in dialog)
/*N*/               if ( bOldDefaults || nCol == PIVOT_DATA_FIELD )
/*N*/                   pDim->SetShowEmpty( TRUE );
/*N*/           }
/*N*/       }
/*N*/   }
}

/*N*/ void ScDPObject::InitFromOldPivot( const ScPivot& rOld, ScDocument* pDoc, BOOL bSetSource )
/*N*/ {
/*N*/   ScDPSaveData aSaveData;
/*N*/
/*N*/   ScPivotParam aParam;
/*N*/   ScQueryParam aQuery;
/*N*/   ScArea aArea;
/*N*/   rOld.GetParam( aParam, aQuery, aArea );
/*N*/
/*N*/   ConvertOrientation( aSaveData, aParam.aColArr, aParam.nColCount,
/*N*/                           sheet::DataPilotFieldOrientation_COLUMN, pDoc, aArea.nRowStart, aArea.nTab,
/*N*/                           uno::Reference<sheet::XDimensionsSupplier>(), TRUE );
/*N*/   ConvertOrientation( aSaveData, aParam.aRowArr, aParam.nRowCount,
/*N*/                           sheet::DataPilotFieldOrientation_ROW, pDoc, aArea.nRowStart, aArea.nTab,
/*N*/                           uno::Reference<sheet::XDimensionsSupplier>(), TRUE );
/*N*/   ConvertOrientation( aSaveData, aParam.aDataArr, aParam.nDataCount,
/*N*/                           sheet::DataPilotFieldOrientation_DATA, pDoc, aArea.nRowStart, aArea.nTab,
/*N*/                           uno::Reference<sheet::XDimensionsSupplier>(), TRUE,
/*N*/                           aParam.aColArr, aParam.nColCount, aParam.aRowArr, aParam.nRowCount );
/*N*/
/*N*/   aSaveData.SetIgnoreEmptyRows( rOld.GetIgnoreEmpty() );
/*N*/   aSaveData.SetRepeatIfEmpty( rOld.GetDetectCat() );
/*N*/   aSaveData.SetColumnGrand( rOld.GetMakeTotalCol() );
/*N*/   aSaveData.SetRowGrand( rOld.GetMakeTotalRow() );
/*N*/
/*N*/   SetSaveData( aSaveData );
/*N*/   if (bSetSource)
/*N*/   {
/*N*/       ScSheetSourceDesc aDesc;
/*N*/       aDesc.aSourceRange = rOld.GetSrcArea();
/*N*/       rOld.GetQuery( aDesc.aQueryParam );
/*N*/       SetSheetDesc( aDesc );
/*N*/   }
/*N*/   SetOutRange( rOld.GetDestArea() );
/*N*/
/*N*/   aTableName = rOld.GetName();
/*N*/   aTableTag  = rOld.GetTag();
/*N*/ }

// -----------------------------------------------------------------------

//  static
//STRIP001 BOOL ScDPObject::HasRegisteredSources()
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001
//STRIP001  uno::Reference<lang::XMultiServiceFactory> xManager = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001  uno::Reference<container::XContentEnumerationAccess> xEnAc( xManager, uno::UNO_QUERY );
//STRIP001  if ( xEnAc.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XEnumeration> xEnum = xEnAc->createContentEnumeration(
//STRIP001                                      rtl::OUString::createFromAscii( SCDPSOURCE_SERVICE ) );
//STRIP001      if ( xEnum.is() && xEnum->hasMoreElements() )
//STRIP001          bFound = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//  static
//STRIP001 uno::Sequence<rtl::OUString> ScDPObject::GetRegisteredSources()
//STRIP001 {
//STRIP001  long nCount = 0;
//STRIP001  uno::Sequence<rtl::OUString> aSeq(0);
//STRIP001
//STRIP001  //  use implementation names...
//STRIP001
//STRIP001  uno::Reference<lang::XMultiServiceFactory> xManager = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001  uno::Reference<container::XContentEnumerationAccess> xEnAc( xManager, uno::UNO_QUERY );
//STRIP001  if ( xEnAc.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XEnumeration> xEnum = xEnAc->createContentEnumeration(
//STRIP001                                      rtl::OUString::createFromAscii( SCDPSOURCE_SERVICE ) );
//STRIP001      if ( xEnum.is() )
//STRIP001      {
//STRIP001          while ( xEnum->hasMoreElements() )
//STRIP001          {
//STRIP001              uno::Any aAddInAny = xEnum->nextElement();
//STRIP001 //               if ( aAddInAny.getReflection()->getTypeClass() == TypeClass_INTERFACE )
//STRIP001              {
//STRIP001                  uno::Reference<uno::XInterface> xIntFac;
//STRIP001                  aAddInAny >>= xIntFac;
//STRIP001                  if ( xIntFac.is() )
//STRIP001                  {
//STRIP001                      uno::Reference<lang::XServiceInfo> xInfo( xIntFac, uno::UNO_QUERY );
//STRIP001                      if ( xInfo.is() )
//STRIP001                      {
//STRIP001                          rtl::OUString sName = xInfo->getImplementationName();
//STRIP001
//STRIP001                          aSeq.realloc( nCount+1 );
//STRIP001                          aSeq.getArray()[nCount] = sName;
//STRIP001                          ++nCount;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aSeq;
//STRIP001 }

//  static
//STRIP001 uno::Reference<sheet::XDimensionsSupplier> ScDPObject::CreateSource( const ScDPServiceDesc& rDesc )
//STRIP001 {
//STRIP001  rtl::OUString aImplName = rDesc.aServiceName;
//STRIP001  uno::Reference<sheet::XDimensionsSupplier> xRet = NULL;
//STRIP001
//STRIP001  uno::Reference<lang::XMultiServiceFactory> xManager = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001  uno::Reference<container::XContentEnumerationAccess> xEnAc( xManager, uno::UNO_QUERY );
//STRIP001  if ( xEnAc.is() )
//STRIP001  {
//STRIP001      uno::Reference<container::XEnumeration> xEnum = xEnAc->createContentEnumeration(
//STRIP001                                      rtl::OUString::createFromAscii( SCDPSOURCE_SERVICE ) );
//STRIP001      if ( xEnum.is() )
//STRIP001      {
//STRIP001          while ( xEnum->hasMoreElements() && !xRet.is() )
//STRIP001          {
//STRIP001              uno::Any aAddInAny = xEnum->nextElement();
//STRIP001 //               if ( aAddInAny.getReflection()->getTypeClass() == TypeClass_INTERFACE )
//STRIP001              {
//STRIP001                  uno::Reference<uno::XInterface> xIntFac;
//STRIP001                  aAddInAny >>= xIntFac;
//STRIP001                  if ( xIntFac.is() )
//STRIP001                  {
//STRIP001                      uno::Reference<lang::XServiceInfo> xInfo( xIntFac, uno::UNO_QUERY );
//STRIP001                      uno::Reference<lang::XSingleServiceFactory> xFac( xIntFac, uno::UNO_QUERY );
//STRIP001                      if ( xFac.is() && xInfo.is() && xInfo->getImplementationName() == aImplName )
//STRIP001                      {
//STRIP001                          try
//STRIP001                          {
//STRIP001                              uno::Reference<uno::XInterface> xInterface = xFac->createInstance();
//STRIP001                              uno::Reference<lang::XInitialization> xInit( xInterface, uno::UNO_QUERY );
//STRIP001                              if (xInit.is())
//STRIP001                              {
//STRIP001                                  //  initialize
//STRIP001                                  uno::Sequence<uno::Any> aSeq(4);
//STRIP001                                  uno::Any* pArray = aSeq.getArray();
//STRIP001                                  pArray[0] <<= rtl::OUString( rDesc.aParSource );
//STRIP001                                  pArray[1] <<= rtl::OUString( rDesc.aParName );
//STRIP001                                  pArray[2] <<= rtl::OUString( rDesc.aParUser );
//STRIP001                                  pArray[3] <<= rtl::OUString( rDesc.aParPass );
//STRIP001                                  xInit->initialize( aSeq );
//STRIP001                              }
//STRIP001                              xRet = uno::Reference<sheet::XDimensionsSupplier>( xInterface, uno::UNO_QUERY );
//STRIP001                          }
//STRIP001                          catch(uno::Exception&)
//STRIP001                          {
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return xRet;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ ScDPCollection::ScDPCollection(ScDocument* pDocument) :
/*N*/   pDoc( pDocument )
/*N*/ {
/*N*/ }

/*N*/ ScDPCollection::ScDPCollection(const ScDPCollection& r) :
/*N*/   Collection(r),
/*N*/   pDoc(r.pDoc)
/*N*/ {
/*N*/ }

/*N*/ ScDPCollection::~ScDPCollection()
/*N*/ {
/*N*/ }

/*N*/ DataObject* ScDPCollection::Clone() const
/*N*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001    return new ScDPCollection(*this);
/*N*/ }

/*N*/ BOOL ScDPCollection::StoreOld( SvStream& rStream ) const
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/
/*N*/   USHORT nSheetCount = 0;
/*N*/   USHORT i;
/*N*/   for (i=0; i<nCount; i++)
/*N*/       if ( ((const ScDPObject*)At(i))->IsSheetData() )
/*N*/           ++nSheetCount;
/*N*/
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   rStream << nSheetCount;         // only tables from sheet data
/*N*/
/*N*/   for (i=0; i<nCount && bSuccess; i++)
/*N*/   {
/*N*/       const ScDPObject* pObj = (const ScDPObject*)At(i);
/*N*/       if ( pObj->IsSheetData() )
/*N*/           bSuccess = pObj->StoreOld( rStream, aHdr );
/*N*/   }
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ BOOL ScDPCollection::StoreNew( SvStream& rStream ) const
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   rStream << (long)SC_DP_VERSION_CURRENT;
/*N*/   rStream << (long)nCount;
/*N*/
/*N*/   for (USHORT i=0; i<nCount && bSuccess; i++)
/*N*/       bSuccess = ((const ScDPObject*)At(i))->StoreNew( rStream, aHdr );
/*N*/
/*N*/   return bSuccess;
/*N*/ }
/*N*/
/*N*/ BOOL ScDPCollection::LoadNew( SvStream& rStream )
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/
/*N*/   FreeAll();
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   long nVer;
/*N*/   rStream >> nVer;
/*N*/
/*N*/   //  check for all supported versions here..
/*N*/
/*N*/   if ( nVer != SC_DP_VERSION_CURRENT )
/*N*/   {
/*N*/       DBG_ERROR("skipping unknown version of data pilot obejct");
/*N*/       if ( rStream.GetError() == SVSTREAM_OK )
/*N*/           rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   long nNewCount;
/*N*/   rStream >> nNewCount;
/*N*/   for (long i=0; i<nNewCount; i++)
/*N*/   {
/*N*/       ScDPObject* pObj = new ScDPObject( pDoc );
/*N*/       if ( pObj->LoadNew(rStream, aHdr) )
/*N*/       {
/*N*/           pObj->SetAlive( TRUE );
/*N*/           Insert( pObj );
/*N*/       }
/*N*/       else
/*N*/           delete pObj;
/*N*/   }
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ void ScDPCollection::UpdateReference( UpdateRefMode eUpdateRefMode,
/*N*/                                        const ScRange& r, short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       ((ScDPObject*)At(i))->UpdateReference( eUpdateRefMode, r, nDx, nDy, nDz );
/*N*/ }

/*N*/ BOOL ScDPCollection::RefsEqual( const ScDPCollection& r ) const
/*N*/ {
/*N*/   if ( nCount != r.nCount )
/*N*/       return FALSE;
/*N*/
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       if ( ! ((const ScDPObject*)At(i))->RefsEqual( *((const ScDPObject*)r.At(i)) ) )
/*N*/           return FALSE;
/*N*/
/*N*/   return TRUE;    // all equal
/*N*/ }
/*N*/
/*N*/ void ScDPCollection::WriteRefsTo( ScDPCollection& r ) const
/*N*/ {
/*N*/   if ( nCount == r.nCount )
/*N*/   {
/*N*/       //! assert equal names?
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/           ((const ScDPObject*)At(i))->WriteRefsTo( *((ScDPObject*)r.At(i)) );
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR("WriteRefsTo: different count");
/*N*/ }

/*N*/ String ScDPCollection::CreateNewName( USHORT nMin ) const
/*N*/ {
/*N*/   String aBase = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("DataPilot"));
/*N*/   //! from Resource?
/*N*/
/*N*/   for (USHORT nAdd=0; nAdd<=nCount; nAdd++)   //  nCount+1 tries
/*N*/   {
/*N*/       String aNewName = aBase;
/*N*/       aNewName += String::CreateFromInt32( nMin + nAdd );
/*N*/       BOOL bFound = FALSE;
/*N*/       for (USHORT i=0; i<nCount && !bFound; i++)
/*N*/           if (((const ScDPObject*)pItems[i])->GetName() == aNewName)
/*N*/               bFound = TRUE;
/*N*/       if (!bFound)
/*N*/           return aNewName;            // found unused Name
/*N*/   }
/*N*/   return String();                    // should not happen
/*N*/ }

/*N*/ void ScDPCollection::EnsureNames()
/*N*/ {
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       if (!((const ScDPObject*)At(i))->GetName().Len())
/*?*/           ((ScDPObject*)At(i))->SetName( CreateNewName() );
/*N*/ }

//------------------------------------------------------------------------
//  convert old pivot tables into new datapilot tables

/*N*/ void ScDPCollection::ConvertOldTables( ScPivotCollection& rOldColl )
/*N*/ {
/*N*/   //  convert old pivot tables into new datapilot tables
/*N*/
/*N*/   USHORT nOldCount = rOldColl.GetCount();
/*N*/   for (USHORT i=0; i<nOldCount; i++)
/*N*/   {
/*N*/       ScDPObject* pNewObj = new ScDPObject(pDoc);
/*N*/       pNewObj->InitFromOldPivot( *(rOldColl)[i], pDoc, TRUE );
/*N*/       pNewObj->SetAlive( TRUE );
/*N*/       Insert( pNewObj );
/*N*/   }
/*N*/   rOldColl.FreeAll();
/*N*/ }




