/*************************************************************************
 *
 *  $RCSfile: sc_dptabsrc.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:35:59 $
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

#include <tools/debug.hxx>
#include <rtl/math.hxx>
#include <svtools/itemprop.hxx>

#include "dptabsrc.hxx"
#include "dptabres.hxx"
#include "dptabdat.hxx"
#include "global.hxx"
#include "collect.hxx"
#include "datauno.hxx"      // ScDataUnoConversion
#include "unoguard.hxx"
#include "miscuno.hxx"
#include "unonames.hxx"

#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/sheet/DataPilotFieldOrientation.hpp>

#ifndef _UNOTOOLS_CALENDARWRAPPER_HXX
#include <unotools/calendarwrapper.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_CALENDARDISPLAYINDEX_HPP_
#include <com/sun/star/i18n/CalendarDisplayIndex.hpp>
#endif

using namespace com::sun::star;

// -----------------------------------------------------------------------

#define SC_MINCOUNT_LIMIT   1000000

// -----------------------------------------------------------------------

/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPSource,      "ScDPSource",      "com.sun.star.sheet.DataPilotSource" )
/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPDimensions,  "ScDPDimensions",  "com.sun.star.sheet.DataPilotSourceDimensions" )
/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPDimension,   "ScDPDimension",   "com.sun.star.sheet.DataPilotSourceDimension" )
/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPHierarchies, "ScDPHierarchies", "com.sun.star.sheet.DataPilotSourceHierarcies" )
/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPHierarchy,   "ScDPHierarchy",   "com.sun.star.sheet.DataPilotSourceHierarcy" )
/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPLevels,      "ScDPLevels",      "com.sun.star.sheet.DataPilotSourceLevels" )
/*N*/ SC_SIMPLE_SERVICE_INFO( ScDPLevel,       "ScDPLevel",       "com.sun.star.sheet.DataPilotSourceLevel" )
//STRIP001 SC_SIMPLE_SERVICE_INFO( ScDPMembers,     "ScDPMembers",     "com.sun.star.sheet.DataPilotSourceMembers" )
//STRIP001 SC_SIMPLE_SERVICE_INFO( ScDPMember,      "ScDPMember",      "com.sun.star.sheet.DataPilotSourceMember" )

// -----------------------------------------------------------------------

// property maps for PropertySetInfo
//  DataDescription / NumberFormat are internal

// -----------------------------------------------------------------------

//! move to a header?
/*N*/ BOOL lcl_GetBoolFromAny( const uno::Any& aAny )
/*N*/ {
/*N*/   if ( aAny.getValueTypeClass() == uno::TypeClass_BOOLEAN )
/*N*/       return *(sal_Bool*)aAny.getValue();
/*N*/   return FALSE;
/*N*/ }

/*N*/ void lcl_SetBoolInAny( uno::Any& rAny, BOOL bValue )
/*N*/ {
/*N*/   rAny.setValue( &bValue, getBooleanCppuType() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScDPSource::ScDPSource( ScDPTableData* pD ) :
/*N*/   pData( pD ),
/*N*/   pDimensions( NULL ),
/*N*/   nColDimCount( 0 ),
/*N*/   nRowDimCount( 0 ),
/*N*/   nDataDimCount( 0 ),
/*N*/   nPageDimCount( 0 ),
/*N*/   nDupCount( 0 ),
/*N*/   bResultOverflow( FALSE ),
/*N*/   pResData( NULL ),
/*N*/   pColResRoot( NULL ),
/*N*/   pRowResRoot( NULL ),
/*N*/   pColResults( NULL ),
/*N*/   pRowResults( NULL ),
/*N*/   bColumnGrand( TRUE ),       // default is true
/*N*/   bRowGrand( TRUE ),
/*N*/   bIgnoreEmptyRows( FALSE ),
/*N*/   bRepeatIfEmpty( FALSE )
/*N*/ {
/*N*/   pData->SetEmptyFlags( bIgnoreEmptyRows, bRepeatIfEmpty );
/*N*/ }

/*N*/ ScDPSource::~ScDPSource()
/*N*/ {
/*N*/   delete pData;           // ScDPTableData is not ref-counted
/*N*/
/*N*/   if (pDimensions)
/*N*/       pDimensions->release();     // ref-counted
/*N*/
/*N*/   //! free lists
/*N*/
/*N*/   delete[] pColResults;
/*N*/   delete[] pRowResults;
/*N*/
/*N*/   delete pColResRoot;
/*N*/   delete pRowResRoot;
/*N*/   delete pResData;
/*N*/ }

/*N*/ USHORT ScDPSource::GetOrientation(long nColumn)
/*N*/ {
/*N*/   long i;
/*N*/   for (i=0; i<nColDimCount; i++)
/*N*/       if (nColDims[i] == nColumn)
/*N*/           return sheet::DataPilotFieldOrientation_COLUMN;
/*N*/   for (i=0; i<nRowDimCount; i++)
/*N*/       if (nRowDims[i] == nColumn)
/*N*/           return sheet::DataPilotFieldOrientation_ROW;
/*N*/   for (i=0; i<nDataDimCount; i++)
/*N*/       if (nDataDims[i] == nColumn)
/*N*/           return sheet::DataPilotFieldOrientation_DATA;
/*N*/   for (i=0; i<nPageDimCount; i++)
/*?*/       if (nPageDims[i] == nColumn)
/*?*/           return sheet::DataPilotFieldOrientation_PAGE;
/*N*/   return sheet::DataPilotFieldOrientation_HIDDEN;
/*N*/ }

//STRIP001 long ScDPSource::GetDataDimensionCount()
//STRIP001 {
//STRIP001  return nDataDimCount;
//STRIP001 }

//STRIP001 String ScDPSource::GetDataDimName( long nIndex )
//STRIP001 {
//STRIP001  String aRet;
//STRIP001  if ( nIndex >= 0 && nIndex < nDataDimCount )
//STRIP001  {
//STRIP001      long nDimIndex = nDataDims[nIndex];
//STRIP001      ScDPDimension* pDim = GetDimensionsObject()->getByIndex(nDimIndex);
//STRIP001      if (pDim)
//STRIP001          aRet = String( pDim->getName() );
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }

/*N*/ long ScDPSource::GetPosition(long nColumn)
/*N*/ {
/*N*/   long i;
/*N*/   for (i=0; i<nColDimCount; i++)
/*N*/       if (nColDims[i] == nColumn)
/*N*/           return i;
/*N*/   for (i=0; i<nRowDimCount; i++)
/*N*/       if (nRowDims[i] == nColumn)
/*N*/           return i;
/*N*/   for (i=0; i<nDataDimCount; i++)
/*N*/       if (nDataDims[i] == nColumn)
/*N*/           return i;
/*N*/   for (i=0; i<nPageDimCount; i++)
/*?*/       if (nPageDims[i] == nColumn)
/*?*/           return i;
/*N*/   return 0;
/*N*/ }

/*N*/ BOOL lcl_TestSubTotal( BOOL& rAllowed, long nColumn, long* pArray, long nCount, ScDPSource* pSource )
/*N*/ {
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       if (pArray[i] == nColumn)
/*N*/       {
/*N*/           //  no subtotals for data layout dim, no matter where
/*N*/           if ( pSource->IsDataLayoutDimension(nColumn) )
/*N*/               rAllowed = FALSE;
/*N*/           else
/*N*/           {
/*N*/               //  no subtotals if no other dim but data layout follows
/*N*/               long nNextIndex = i+1;
/*N*/               if ( nNextIndex < nCount && pSource->IsDataLayoutDimension(pArray[nNextIndex]) )
/*N*/                   ++nNextIndex;
/*N*/               if ( nNextIndex >= nCount )
/*N*/                   rAllowed = FALSE;
/*N*/           }
/*N*/
/*N*/           return TRUE;    // found
/*N*/       }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDPSource::SubTotalAllowed(long nColumn)
/*N*/ {
/*N*/   //! cache this at ScDPResultData
/*N*/   BOOL bAllowed = TRUE;
/*N*/   if ( lcl_TestSubTotal( bAllowed, nColumn, nColDims, nColDimCount, this ) )
/*N*/       return bAllowed;
/*N*/   if ( lcl_TestSubTotal( bAllowed, nColumn, nRowDims, nRowDimCount, this ) )
/*N*/       return bAllowed;
/*N*/   return bAllowed;
/*N*/ }

/*N*/ void lcl_RemoveDim( long nRemove, long* pDims, long& rCount )
/*N*/ {
/*N*/   for (long i=0; i<rCount; i++)
/*N*/       if ( pDims[i] == nRemove )
/*N*/       {
/*?*/           for (long j=i; j+1<rCount; j++)
/*?*/               pDims[j] = pDims[j+1];
/*?*/           --rCount;
/*?*/           return;
/*N*/       }
/*N*/ }

/*N*/ void ScDPSource::SetOrientation(long nColumn, USHORT nNew)
/*N*/ {
/*N*/   //! change to no-op if new orientation is equal to old?
/*N*/
/*N*/   // remove from old list
/*N*/   lcl_RemoveDim( nColumn, nColDims, nColDimCount );
/*N*/   lcl_RemoveDim( nColumn, nRowDims, nRowDimCount );
/*N*/   lcl_RemoveDim( nColumn, nDataDims, nDataDimCount );
/*N*/   lcl_RemoveDim( nColumn, nPageDims, nPageDimCount );
/*N*/
/*N*/   // add to new list
/*N*/   switch (nNew)
/*N*/   {
/*N*/       case sheet::DataPilotFieldOrientation_COLUMN:
/*N*/           nColDims[nColDimCount++] = nColumn;
/*N*/           break;
/*N*/       case sheet::DataPilotFieldOrientation_ROW:
/*N*/           nRowDims[nRowDimCount++] = nColumn;
/*N*/           break;
/*N*/       case sheet::DataPilotFieldOrientation_DATA:
/*N*/           nDataDims[nDataDimCount++] = nColumn;
/*N*/           break;
/*N*/       case sheet::DataPilotFieldOrientation_PAGE:
/*?*/           nPageDims[nPageDimCount++] = nColumn;
/*N*/           break;
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDPSource::IsDataLayoutDimension(long nDim)
/*N*/ {
/*N*/   return nDim == pData->GetColumnCount();
/*N*/ }

//STRIP001 USHORT ScDPSource::GetDataLayoutOrientation()
//STRIP001 {
//STRIP001  return GetOrientation(pData->GetColumnCount());
//STRIP001 }

/*N*/ BOOL ScDPSource::IsDateDimension(long nDim)
/*N*/ {
/*N*/   return pData->IsDateDimension(nDim);
/*N*/ }

/*N*/ ScDPDimensions* ScDPSource::GetDimensionsObject()
/*N*/ {
/*N*/   if (!pDimensions)
/*N*/   {
/*N*/       pDimensions = new ScDPDimensions(this);
/*N*/       pDimensions->acquire();                     // ref-counted
/*N*/   }
/*N*/   return pDimensions;
/*N*/ }

/*N*/ uno::Reference<container::XNameAccess> SAL_CALL ScDPSource::getDimensions() throw(uno::RuntimeException)
/*N*/ {
/*N*/   return GetDimensionsObject();
/*N*/ }

//STRIP001 void ScDPSource::SetDupCount( long nNew )
//STRIP001 {
//STRIP001  nDupCount = nNew;
//STRIP001 }

//STRIP001 ScDPDimension* ScDPSource::AddDuplicated(long nSource, const String& rNewName)
//STRIP001 {
//STRIP001  DBG_ASSERT( pDimensions, "AddDuplicated without dimensions?" );
//STRIP001
//STRIP001  //  re-use
//STRIP001
//STRIP001  long nOldDimCount = pDimensions->getCount();
//STRIP001  for (long i=0; i<nOldDimCount; i++)
//STRIP001  {
//STRIP001      ScDPDimension* pDim = pDimensions->getByIndex(i);
//STRIP001      if (pDim && String(pDim->getName()) == rNewName)
//STRIP001      {
//STRIP001          //! test if pDim is a duplicate of source
//STRIP001          return pDim;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SetDupCount( nDupCount + 1 );
//STRIP001  pDimensions->CountChanged();        // uses nDupCount
//STRIP001
//STRIP001  return pDimensions->getByIndex( pDimensions->getCount() - 1 );
//STRIP001 }

/*N*/ long ScDPSource::GetSourceDim(long nDim)
/*N*/ {
/*N*/   //  original source dimension or data layout dimension?
/*N*/   if ( nDim <= pData->GetColumnCount() )
/*N*/       return nDim;
/*N*/
/*?*/   if ( nDim < pDimensions->getCount() )
/*?*/   {
/*?*/       ScDPDimension* pDimObj = pDimensions->getByIndex( nDim );
/*?*/       if ( pDimObj )
/*?*/       {
/*?*/           long nSource = pDimObj->GetSourceDim();
/*?*/           if ( nSource >= 0 )
/*?*/               return nSource;
/*?*/       }
/*?*/   }
/*?*/
/*?*/   DBG_ERROR("GetSourceDim: wrong dim");
/*?*/   return nDim;
/*N*/ }

/*?*/ uno::Sequence< uno::Sequence<sheet::DataResult> > SAL_CALL ScDPSource::getResults()
/*?*/                                                           throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return uno::Sequence< uno::Sequence<sheet::DataResult> >(0); //STRIP001
//STRIP001  CreateRes_Impl();       // create pColResRoot and pRowResRoot
//STRIP001
//STRIP001  if ( bResultOverflow )      // set in CreateRes_Impl
//STRIP001  {
//STRIP001      //  no results available
//STRIP001      throw uno::RuntimeException();
//STRIP001  }
//STRIP001
//STRIP001  long nColCount = pColResRoot->GetSize(pResData->GetColStartMeasure());
//STRIP001  long nRowCount = pRowResRoot->GetSize(pResData->GetRowStartMeasure());
//STRIP001
//STRIP001  //  allocate full sequence
//STRIP001  //! leave out empty rows???
//STRIP001
//STRIP001  uno::Sequence< uno::Sequence<sheet::DataResult> > aSeq( nRowCount );
//STRIP001  uno::Sequence<sheet::DataResult>* pRowAry = aSeq.getArray();
//STRIP001  for (long nRow = 0; nRow < nRowCount; nRow++)
//STRIP001  {
//STRIP001      uno::Sequence<sheet::DataResult> aColSeq( nColCount );
//STRIP001      //  use default values of DataResult
//STRIP001      pRowAry[nRow] = aColSeq;
//STRIP001  }
//STRIP001
//STRIP001  long nSeqRow = 0;
//STRIP001  pRowResRoot->FillDataResults( pColResRoot, aSeq, nSeqRow, pResData->GetRowStartMeasure() );
//STRIP001
//STRIP001  return aSeq;
/*?*/ }

/*?*/ void SAL_CALL ScDPSource::refresh() throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/    disposeData();
/*?*/ }

/*?*/ void SAL_CALL ScDPSource::addRefreshListener( const uno::Reference<util::XRefreshListener >& l )
/*?*/                                               throw(uno::RuntimeException)
/*?*/ {
/*?*/   DBG_ERROR("not implemented");   //! exception?
/*?*/ }

/*?*/ void SAL_CALL ScDPSource::removeRefreshListener( const uno::Reference<util::XRefreshListener >& l )
/*?*/                                               throw(uno::RuntimeException)
/*?*/ {
/*?*/   DBG_ERROR("not implemented");   //! exception?
/*?*/ }

//STRIP001 String ScDPSource::getDataDescription()
//STRIP001 {
//STRIP001  CreateRes_Impl();       // create pResData
//STRIP001
//STRIP001  String aRet;
//STRIP001  if ( pResData->GetMeasureCount() == 1 )
//STRIP001      aRet = pResData->GetMeasureString( 0, TRUE, SUBTOTAL_FUNC_NONE );
//STRIP001
//STRIP001  //  empty for more than one measure
//STRIP001
//STRIP001  return aRet;
//STRIP001 }

/*N*/ BOOL ScDPSource::getColumnGrand() const
/*N*/ {
/*N*/   return bColumnGrand;
/*N*/ }

/*N*/ void ScDPSource::setColumnGrand(BOOL bSet)
/*N*/ {
/*N*/   bColumnGrand = bSet;
/*N*/ }

/*N*/ BOOL ScDPSource::getRowGrand() const
/*N*/ {
/*N*/   return bRowGrand;
/*N*/ }

/*N*/ void ScDPSource::setRowGrand(BOOL bSet)
/*N*/ {
/*N*/   bRowGrand = bSet;
/*N*/ }

/*N*/ BOOL ScDPSource::getIgnoreEmptyRows() const
/*N*/ {
/*N*/   return bIgnoreEmptyRows;
/*N*/ }

/*N*/ void ScDPSource::setIgnoreEmptyRows(BOOL bSet)
/*N*/ {
/*N*/   bIgnoreEmptyRows = bSet;
/*N*/   pData->SetEmptyFlags( bIgnoreEmptyRows, bRepeatIfEmpty );
/*N*/ }

/*N*/ BOOL ScDPSource::getRepeatIfEmpty() const
/*N*/ {
/*N*/   return bRepeatIfEmpty;
/*N*/ }

/*N*/ void ScDPSource::setRepeatIfEmpty(BOOL bSet)
/*N*/ {
/*N*/   bRepeatIfEmpty = bSet;
/*N*/   pData->SetEmptyFlags( bIgnoreEmptyRows, bRepeatIfEmpty );
/*N*/ }

//STRIP001 void ScDPSource::validate()      //! ???
//STRIP001 {
//STRIP001  CreateRes_Impl();
//STRIP001 }

//STRIP001 void ScDPSource::disposeData()
//STRIP001 {
//STRIP001  if ( pResData )
//STRIP001  {
//STRIP001      //  reset all data...
//STRIP001
//STRIP001      DELETEZ(pColResRoot);
//STRIP001      DELETEZ(pRowResRoot);
//STRIP001      DELETEZ(pResData);
//STRIP001      delete[] pColResults;
//STRIP001      delete[] pRowResults;
//STRIP001      pColResults = NULL;
//STRIP001      pRowResults = NULL;
//STRIP001      aColLevelList.Clear();
//STRIP001      aRowLevelList.Clear();
//STRIP001  }
//STRIP001
//STRIP001  if ( pDimensions )
//STRIP001  {
//STRIP001      pDimensions->release(); // ref-counted
//STRIP001      pDimensions = NULL;     //  settings have to be applied (from SaveData) again!
//STRIP001  }
//STRIP001  SetDupCount( 0 );
//STRIP001
//STRIP001  //! Test ????
//STRIP001  nColDimCount = nRowDimCount = nDataDimCount = nPageDimCount = 0;
//STRIP001
//STRIP001  pData->DisposeData();   // cached entries etc.
//STRIP001  bResultOverflow = FALSE;
//STRIP001 }

//STRIP001 long lcl_CountMinMembers( ScDPDimension** ppDim, ScDPLevel** ppLevel, long nLevels )
//STRIP001 {
//STRIP001  //  Calculate the product of the member count for those consecutive levels that
//STRIP001  //  have the "show all" flag, one following level, and the data layout dimension.
//STRIP001
//STRIP001  long nTotal = 1;
//STRIP001  long nDataCount = 1;
//STRIP001  BOOL bWasShowAll = TRUE;
//STRIP001  long nPos = nLevels;
//STRIP001  while ( nPos > 0 )
//STRIP001  {
//STRIP001      --nPos;
//STRIP001
//STRIP001      if ( nPos < nLevels && ppDim[nPos] == ppDim[nPos+1] )
//STRIP001      {
//STRIP001          DBG_ERROR("lcl_CountMinMembers: multiple levels from one dimension not implemented");
//STRIP001          return 0;
//STRIP001      }
//STRIP001
//STRIP001      BOOL bDo = FALSE;
//STRIP001      if ( ppDim[nPos]->getIsDataLayoutDimension() )
//STRIP001      {
//STRIP001          //  data layout dim doesn't interfere with "show all" flags
//STRIP001          nDataCount = ppLevel[nPos]->GetMembersObject()->getCount();
//STRIP001          if ( nDataCount == 0 )
//STRIP001              nDataCount = 1;
//STRIP001      }
//STRIP001      else if ( bWasShowAll )     // "show all" set for all following levels?
//STRIP001      {
//STRIP001          bDo = TRUE;
//STRIP001          if ( !ppLevel[nPos]->getShowEmpty() )
//STRIP001          {
//STRIP001              //  this level is counted, following ones are not
//STRIP001              bWasShowAll = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bDo )
//STRIP001      {
//STRIP001          long nThisCount = ppLevel[nPos]->GetMembersObject()->getMinMembers();
//STRIP001          if ( nThisCount == 0 )
//STRIP001          {
//STRIP001              nTotal = 1;         //  empty level -> start counting from here
//STRIP001                                  //! start with visible elements in this level?
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if ( nTotal >= LONG_MAX / nThisCount )
//STRIP001                  return LONG_MAX;                        //  overflow
//STRIP001              nTotal *= nThisCount;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  always include data layout dim, even after restarting
//STRIP001  if ( nTotal >= LONG_MAX / nDataCount )
//STRIP001      return LONG_MAX;                        //  overflow
//STRIP001  nTotal *= nDataCount;
//STRIP001
//STRIP001  return nTotal;
//STRIP001 }

//STRIP001 void ScDPSource::CreateRes_Impl()
//STRIP001 {
//STRIP001  if ( !pResData )
//STRIP001  {
//STRIP001      USHORT nDataOrient = GetDataLayoutOrientation();
//STRIP001      if ( nDataDimCount > 1 && nDataOrient == sheet::DataPilotFieldOrientation_HIDDEN )
//STRIP001      {
//STRIP001          //  if more than one data dimension, data layout orientation must be set
//STRIP001          SetOrientation( pData->GetColumnCount(), sheet::DataPilotFieldOrientation_ROW );
//STRIP001          nDataOrient = sheet::DataPilotFieldOrientation_ROW;
//STRIP001      }
//STRIP001
//STRIP001      String* pDataNames = NULL;
//STRIP001      if (nDataDimCount)
//STRIP001          pDataNames = new String[nDataDimCount];
//STRIP001
//STRIP001      long nDataSrcCols[SC_DAPI_MAXFIELDS];
//STRIP001
//STRIP001      long i;
//STRIP001      for (i=0; i<nDataDimCount; i++)
//STRIP001      {
//STRIP001          long nDimIndex = nDataDims[i];
//STRIP001          ScDPDimension* pDim = GetDimensionsObject()->getByIndex(nDimIndex);
//STRIP001          sheet::GeneralFunction eUser = (sheet::GeneralFunction)pDim->getFunction();
//STRIP001          if (eUser == sheet::GeneralFunction_AUTO)
//STRIP001          {
//STRIP001              //! test for numeric data
//STRIP001              eUser = sheet::GeneralFunction_SUM;
//STRIP001          }
//STRIP001          eDataFunctions[i] = ScDataUnoConversion::GeneralToSubTotal( eUser );
//STRIP001          pDataNames[i] = String( pDim->getName() );  //! label?
//STRIP001
//STRIP001          //  asterisk is added to duplicated dimension names by ScDPSaveData::WriteToSource
//STRIP001          //! modify user visible strings as in ScDPResultData::GetMeasureString instead!
//STRIP001
//STRIP001          pDataNames[i].EraseTrailingChars('*');
//STRIP001
//STRIP001          //! if the name is overridden by user, a flag must be set
//STRIP001          //! so the user defined name replaces the function string and field name.
//STRIP001
//STRIP001          //! the complete name (function and field) must be stored at the dimension
//STRIP001
//STRIP001          long nSource = ((ScDPDimension*)pDim)->GetSourceDim();
//STRIP001          if ( nSource >= 0 )
//STRIP001              nDataSrcCols[i] = nSource;
//STRIP001          else
//STRIP001              nDataSrcCols[i] = nDimIndex;
//STRIP001      }
//STRIP001
//STRIP001      pResData = new ScDPResultData( this );
//STRIP001      pResData->SetMeasureData( nDataDimCount, eDataFunctions, pDataNames );
//STRIP001      pResData->SetDataLayoutOrientation(nDataOrient);
//STRIP001
//STRIP001      delete[] pDataNames;
//STRIP001
//STRIP001      pColResRoot = new ScDPResultMember( pResData, NULL, NULL, NULL, bColumnGrand );
//STRIP001      pRowResRoot = new ScDPResultMember( pResData, NULL, NULL, NULL, bRowGrand );
//STRIP001
//STRIP001      ScDPDimension* ppColDim[SC_DAPI_MAXFIELDS];     //! Ref?
//STRIP001      ScDPLevel* ppColLevel[SC_DAPI_MAXFIELDS];       //! Ref?
//STRIP001      long nColLevelDims[SC_DAPI_MAXFIELDS];
//STRIP001      long nColLevelCount = 0;
//STRIP001      for (i=0; i<nColDimCount; i++)
//STRIP001      {
//STRIP001          ScDPDimension* pDim = GetDimensionsObject()->getByIndex( nColDims[i] );
//STRIP001          long nHierarchy = pDim->getUsedHierarchy();
//STRIP001          if ( nHierarchy >= pDim->GetHierarchiesObject()->getCount() )
//STRIP001              nHierarchy = 0;
//STRIP001          ScDPLevels* pLevels = pDim->GetHierarchiesObject()->getByIndex(nHierarchy)->GetLevelsObject();
//STRIP001          long nCount = pLevels->getCount();
//STRIP001
//STRIP001          //! Test
//STRIP001          if ( pDim->getIsDataLayoutDimension() && nDataDimCount < 2 )
//STRIP001              nCount = 0;
//STRIP001          //! Test
//STRIP001
//STRIP001          for (long j=0; j<nCount; j++)
//STRIP001          {
//STRIP001              nColLevelDims[nColLevelCount] = nColDims[i];
//STRIP001              ppColDim[nColLevelCount] = pDim;
//STRIP001              ppColLevel[nColLevelCount] = pLevels->getByIndex(j);
//STRIP001              ++nColLevelCount;
//STRIP001          }
//STRIP001      }
//STRIP001      ppColDim[nColLevelCount] = NULL;
//STRIP001      ppColLevel[nColLevelCount] = NULL;
//STRIP001
//STRIP001      pColResRoot->InitFrom( ppColDim, ppColLevel );
//STRIP001      pColResRoot->SetHasElements();
//STRIP001
//STRIP001      ScDPDimension* ppRowDim[SC_DAPI_MAXFIELDS];     //! Ref?
//STRIP001      ScDPLevel* ppRowLevel[SC_DAPI_MAXFIELDS];       //! Ref?
//STRIP001      long nRowLevelDims[SC_DAPI_MAXFIELDS];
//STRIP001      long nRowLevelCount = 0;
//STRIP001      for (i=0; i<nRowDimCount; i++)
//STRIP001      {
//STRIP001          ScDPDimension* pDim = GetDimensionsObject()->getByIndex( nRowDims[i] );
//STRIP001          long nHierarchy = pDim->getUsedHierarchy();
//STRIP001          if ( nHierarchy >= pDim->GetHierarchiesObject()->getCount() )
//STRIP001              nHierarchy = 0;
//STRIP001          ScDPLevels* pLevels = pDim->GetHierarchiesObject()->getByIndex(nHierarchy)->GetLevelsObject();
//STRIP001          long nCount = pLevels->getCount();
//STRIP001
//STRIP001          //! Test
//STRIP001          if ( pDim->getIsDataLayoutDimension() && nDataDimCount < 2 )
//STRIP001              nCount = 0;
//STRIP001          //! Test
//STRIP001
//STRIP001          for (long j=0; j<nCount; j++)
//STRIP001          {
//STRIP001              nRowLevelDims[nRowLevelCount] = nRowDims[i];
//STRIP001              ppRowDim[nRowLevelCount] = pDim;
//STRIP001              ppRowLevel[nRowLevelCount] = pLevels->getByIndex(j);
//STRIP001              ++nRowLevelCount;
//STRIP001          }
//STRIP001      }
//STRIP001      ppRowDim[nRowLevelCount] = NULL;
//STRIP001      ppRowLevel[nRowLevelCount] = NULL;
//STRIP001
//STRIP001      pRowResRoot->InitFrom( ppRowDim, ppRowLevel );
//STRIP001      pRowResRoot->SetHasElements();
//STRIP001
//STRIP001      //  pre-check: calculate minimum number of result columns / rows from
//STRIP001      //  levels that have the "show all" flag set
//STRIP001
//STRIP001      long nMinColMembers = lcl_CountMinMembers( ppColDim, ppColLevel, nColLevelCount );
//STRIP001      long nMinRowMembers = lcl_CountMinMembers( ppRowDim, ppRowLevel, nRowLevelCount );
//STRIP001      if ( nMinColMembers > SC_MINCOUNT_LIMIT || nMinRowMembers > SC_MINCOUNT_LIMIT )
//STRIP001      {
//STRIP001          //  resulting table is too big -> abort before calculating
//STRIP001          //  (this relies on late init, so no members are allocated in InitFrom above)
//STRIP001
//STRIP001          bResultOverflow = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ScDPItemData aColData[SC_DAPI_MAXFIELDS];
//STRIP001          ScDPItemData aRowData[SC_DAPI_MAXFIELDS];
//STRIP001          ScDPValueData aValues[SC_DAPI_MAXFIELDS];
//STRIP001
//STRIP001          ScDPTableIteratorParam aIterPar(
//STRIP001                      nColLevelCount,  nColLevelDims,  aColData,
//STRIP001                      nRowLevelCount,  nRowLevelDims,  aRowData,
//STRIP001                      nDataDimCount, nDataSrcCols, aValues );
//STRIP001
//STRIP001          pData->ResetIterator();
//STRIP001          while ( pData->GetNextRow( aIterPar ) )
//STRIP001          {
//STRIP001              pColResRoot->LateInitFrom( ppColDim, ppColLevel, aColData );
//STRIP001              pRowResRoot->LateInitFrom( ppRowDim, ppRowLevel, aRowData );
//STRIP001
//STRIP001              //  test for filtered entries
//STRIP001              //! test child dimensions for null !!!
//STRIP001              if ( ( !pColResRoot->GetChildDimension() || pColResRoot->GetChildDimension()->IsValidEntry( aColData ) ) &&
//STRIP001                   ( !pRowResRoot->GetChildDimension() || pRowResRoot->GetChildDimension()->IsValidEntry( aRowData ) ) )
//STRIP001              {
//STRIP001                  //! single process method with ColMembers, RowMembers and data !!!
//STRIP001                  if (pColResRoot->GetChildDimension())
//STRIP001                      pColResRoot->GetChildDimension()->ProcessData( aColData, NULL, NULL, aValues );
//STRIP001
//STRIP001                  pRowResRoot->ProcessData( aRowData, pColResRoot->GetChildDimension(), aColData, aValues );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDPSource::FillLevelList( USHORT nOrientation, List& rList )
//STRIP001 {
//STRIP001  rList.Clear();
//STRIP001
//STRIP001  long nDimCount = 0;
//STRIP001  long* pDimIndex = NULL;
//STRIP001  switch (nOrientation)
//STRIP001  {
//STRIP001      case sheet::DataPilotFieldOrientation_COLUMN:
//STRIP001          pDimIndex = nColDims;
//STRIP001          nDimCount = nColDimCount;
//STRIP001          break;
//STRIP001      case sheet::DataPilotFieldOrientation_ROW:
//STRIP001          pDimIndex = nRowDims;
//STRIP001          nDimCount = nRowDimCount;
//STRIP001          break;
//STRIP001      case sheet::DataPilotFieldOrientation_DATA:
//STRIP001          pDimIndex = nDataDims;
//STRIP001          nDimCount = nDataDimCount;
//STRIP001          break;
//STRIP001      case sheet::DataPilotFieldOrientation_PAGE:
//STRIP001          pDimIndex = nPageDims;
//STRIP001          nDimCount = nPageDimCount;
//STRIP001          break;
//STRIP001  }
//STRIP001  if (!pDimIndex)
//STRIP001  {
//STRIP001      DBG_ERROR("invalid orientation")
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  ScDPDimensions* pDims = GetDimensionsObject();
//STRIP001  for (long nDim=0; nDim<nDimCount; nDim++)
//STRIP001  {
//STRIP001      ScDPDimension* pDim = pDims->getByIndex(pDimIndex[nDim]);
//STRIP001      DBG_ASSERT( pDim->getOrientation() == nOrientation, "orientations are wrong" );
//STRIP001
//STRIP001      ScDPHierarchies* pHiers = pDim->GetHierarchiesObject();
//STRIP001      long nHierarchy = pDim->getUsedHierarchy();
//STRIP001      if ( nHierarchy >= pHiers->getCount() )
//STRIP001          nHierarchy = 0;
//STRIP001      ScDPHierarchy* pHier = pHiers->getByIndex(nHierarchy);
//STRIP001      ScDPLevels* pLevels = pHier->GetLevelsObject();
//STRIP001      long nLevCount = pLevels->getCount();
//STRIP001      for (long nLev=0; nLev<nLevCount; nLev++)
//STRIP001      {
//STRIP001          ScDPLevel* pLevel = pLevels->getByIndex(nLev);
//STRIP001          rList.Insert( pLevel, LIST_APPEND );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDPSource::FillMemberResults()
//STRIP001 {
//STRIP001  if ( !pColResults && !pRowResults )
//STRIP001  {
//STRIP001      CreateRes_Impl();
//STRIP001
//STRIP001      if ( bResultOverflow )      // set in CreateRes_Impl
//STRIP001      {
//STRIP001          //  no results available -> abort (leave empty)
//STRIP001          //  exception is thrown in ScDPSource::getResults
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001      FillLevelList( sheet::DataPilotFieldOrientation_COLUMN, aColLevelList );
//STRIP001      long nColLevelCount = aColLevelList.Count();
//STRIP001      if (nColLevelCount)
//STRIP001      {
//STRIP001          long nColDimSize = pColResRoot->GetSize(pResData->GetColStartMeasure());
//STRIP001          pColResults = new uno::Sequence<sheet::MemberResult>[nColLevelCount];
//STRIP001          for (long i=0; i<nColLevelCount; i++)
//STRIP001              pColResults[i].realloc(nColDimSize);
//STRIP001
//STRIP001          // ScDPResultDimension* pColResDim = pColResRoot->GetChildDimension();
//STRIP001          // pColResDim->FillMemberResults( pColResults, 0, pResData->GetColStartMeasure() );
//STRIP001          long nPos = 0;
//STRIP001          pColResRoot->FillMemberResults( pColResults, nPos, pResData->GetColStartMeasure(),
//STRIP001                                          TRUE, NULL, NULL );
//STRIP001      }
//STRIP001
//STRIP001      FillLevelList( sheet::DataPilotFieldOrientation_ROW, aRowLevelList );
//STRIP001      long nRowLevelCount = aRowLevelList.Count();
//STRIP001      if (nRowLevelCount)
//STRIP001      {
//STRIP001          long nRowDimSize = pRowResRoot->GetSize(pResData->GetRowStartMeasure());
//STRIP001          pRowResults = new uno::Sequence<sheet::MemberResult>[nRowLevelCount];
//STRIP001          for (long i=0; i<nRowLevelCount; i++)
//STRIP001              pRowResults[i].realloc(nRowDimSize);
//STRIP001
//STRIP001          // ScDPResultDimension* pRowResDim = pRowResRoot->GetChildDimension();
//STRIP001          // pRowResDim->FillMemberResults( pRowResults, 0, pResData->GetRowStartMeasure() );
//STRIP001          long nPos = 0;
//STRIP001          pRowResRoot->FillMemberResults( pRowResults, nPos, pResData->GetRowStartMeasure(),
//STRIP001                                          TRUE, NULL, NULL );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 const uno::Sequence<sheet::MemberResult>* ScDPSource::GetMemberResults( ScDPLevel* pLevel )
//STRIP001 {
//STRIP001  FillMemberResults();
//STRIP001
//STRIP001  long i;
//STRIP001  long nColCount = aColLevelList.Count();
//STRIP001  for (i=0; i<nColCount; i++)
//STRIP001  {
//STRIP001      ScDPLevel* pColLevel = (ScDPLevel*)aColLevelList.GetObject(i);
//STRIP001      if ( pColLevel == pLevel )
//STRIP001          return pColResults+i;
//STRIP001  }
//STRIP001  long nRowCount = aRowLevelList.Count();
//STRIP001  for (i=0; i<nRowCount; i++)
//STRIP001  {
//STRIP001      ScDPLevel* pRowLevel = (ScDPLevel*)aRowLevelList.GetObject(i);
//STRIP001      if ( pRowLevel == pLevel )
//STRIP001          return pRowResults+i;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

// XPropertySet

/*?*/ uno::Reference<beans::XPropertySetInfo> SAL_CALL ScDPSource::getPropertySetInfo()
/*?*/                                                       throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return uno::Reference<beans::XPropertySetInfo>(0); //STRIP001
//STRIP001  ScUnoGuard aGuard;
//STRIP001
//STRIP001  static SfxItemPropertyMap aDPSourceMap_Impl[] =
//STRIP001  {
//STRIP001      {MAP_CHAR_LEN(SC_UNO_COLGRAND), 0,  &getBooleanCppuType(),              0, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_DATADESC), 0,  &getCppuType((rtl::OUString*)0),    beans::PropertyAttribute::READONLY, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_IGNOREEM), 0,  &getBooleanCppuType(),              0, 0 },     // for sheet data only
//STRIP001      {MAP_CHAR_LEN(SC_UNO_REPEATIF), 0,  &getBooleanCppuType(),              0, 0 },     // for sheet data only
//STRIP001      {MAP_CHAR_LEN(SC_UNO_ROWGRAND), 0,  &getBooleanCppuType(),              0, 0 },
//STRIP001      {0,0,0,0}
//STRIP001  };
//STRIP001  static uno::Reference<beans::XPropertySetInfo> aRef =
//STRIP001      new SfxItemPropertySetInfo( aDPSourceMap_Impl );
//STRIP001  return aRef;
/*?*/ }

/*N*/ void SAL_CALL ScDPSource::setPropertyValue( const rtl::OUString& aPropertyName, const uno::Any& aValue )
/*N*/               throw(beans::UnknownPropertyException, beans::PropertyVetoException,
/*N*/                       lang::IllegalArgumentException, lang::WrappedTargetException,
/*N*/                       uno::RuntimeException)
/*N*/ {
/*N*/   String aNameStr = aPropertyName;
/*N*/   if ( aNameStr.EqualsAscii( SC_UNO_COLGRAND ) )
/*N*/       setColumnGrand( lcl_GetBoolFromAny( aValue ) );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_ROWGRAND ) )
/*N*/       setRowGrand( lcl_GetBoolFromAny( aValue ) );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_IGNOREEM ) )
/*N*/       setIgnoreEmptyRows( lcl_GetBoolFromAny( aValue ) );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_REPEATIF ) )
/*N*/       setRepeatIfEmpty( lcl_GetBoolFromAny( aValue ) );
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("unknown property");
/*N*/       //! THROW( UnknownPropertyException() );
/*N*/   }
/*N*/ }

/*N*/ uno::Any SAL_CALL ScDPSource::getPropertyValue( const rtl::OUString& aPropertyName )
/*N*/               throw(beans::UnknownPropertyException, lang::WrappedTargetException,
/*N*/                       uno::RuntimeException)
/*N*/ {
/*N*/   uno::Any aRet;
/*N*/   String aNameStr = aPropertyName;
/*N*/   if ( aNameStr.EqualsAscii( SC_UNO_COLGRAND ) )
/*N*/       lcl_SetBoolInAny( aRet, getColumnGrand() );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_ROWGRAND ) )
/*N*/       lcl_SetBoolInAny( aRet, getRowGrand() );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_IGNOREEM ) )
/*N*/       lcl_SetBoolInAny( aRet, getIgnoreEmptyRows() );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_REPEATIF ) )
/*N*/       lcl_SetBoolInAny( aRet, getRepeatIfEmpty() );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_DATADESC ) )             // read-only
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    aRet <<= rtl::OUString( getDataDescription() );
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("unknown property");
/*N*/       //! THROW( UnknownPropertyException() );
/*N*/   }
/*N*/   return aRet;
/*N*/ }

/*N*/ SC_IMPL_DUMMY_PROPERTY_LISTENER( ScDPSource )

// -----------------------------------------------------------------------

/*N*/ ScDPDimensions::ScDPDimensions( ScDPSource* pSrc ) :
/*N*/   pSource( pSrc ),
/*N*/   ppDims( NULL )
/*N*/ {
/*N*/   //! hold pSource
/*N*/
/*N*/   // include data layout dimension and duplicated dimensions
/*N*/   nDimCount = pSource->GetData()->GetColumnCount() + 1 + pSource->GetDupCount();
/*N*/ }

/*N*/ ScDPDimensions::~ScDPDimensions()
/*N*/ {
/*N*/   //! release pSource
/*N*/
/*N*/   if (ppDims)
/*N*/   {
/*N*/       for (long i=0; i<nDimCount; i++)
/*N*/           if ( ppDims[i] )
/*N*/               ppDims[i]->release();           // ref-counted
/*N*/       delete[] ppDims;
/*N*/   }
/*N*/ }

//STRIP001 void ScDPDimensions::CountChanged()
//STRIP001 {
//STRIP001  // include data layout dimension and duplicated dimensions
//STRIP001  long nNewCount = pSource->GetData()->GetColumnCount() + 1 + pSource->GetDupCount();
//STRIP001  if ( ppDims )
//STRIP001  {
//STRIP001      long i;
//STRIP001      long nCopy = Min( nNewCount, nDimCount );
//STRIP001      ScDPDimension** ppNew = new ScDPDimension*[nNewCount];
//STRIP001
//STRIP001      for (i=0; i<nCopy; i++)             // copy existing dims
//STRIP001          ppNew[i] = ppDims[i];
//STRIP001      for (i=nCopy; i<nNewCount; i++)     // clear additional pointers
//STRIP001          ppNew[i] = NULL;
//STRIP001      for (i=nCopy; i<nDimCount; i++)     // delete old dims if count is decreased
//STRIP001          if ( ppDims[i] )
//STRIP001              ppDims[i]->release();       // ref-counted
//STRIP001
//STRIP001      delete[] ppDims;
//STRIP001      ppDims = ppNew;
//STRIP001  }
//STRIP001  nDimCount = nNewCount;
//STRIP001 }

// very simple XNameAccess implementation using getCount/getByIndex

/*N*/ uno::Any SAL_CALL ScDPDimensions::getByName( const rtl::OUString& aName )
/*N*/           throw(container::NoSuchElementException,
/*N*/                   lang::WrappedTargetException, uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       if ( getByIndex(i)->getName() == aName )
/*N*/       {
/*N*/           uno::Reference<container::XNamed> xNamed = getByIndex(i);
/*N*/           uno::Any aRet;
/*N*/           aRet <<= xNamed;
/*N*/           return aRet;
/*N*/       }
/*N*/
/*N*/   throw container::NoSuchElementException();
/*N*/   return uno::Any();
/*N*/ }

/*N*/ uno::Sequence<rtl::OUString> SAL_CALL ScDPDimensions::getElementNames() throw(uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   uno::Sequence<rtl::OUString> aSeq(nCount);
/*N*/   rtl::OUString* pArr = aSeq.getArray();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       pArr[i] = getByIndex(i)->getName();
/*N*/   return aSeq;
/*N*/ }

/*?*/ sal_Bool SAL_CALL ScDPDimensions::hasByName( const rtl::OUString& aName ) throw(uno::RuntimeException)
/*?*/ {
/*?*/   long nCount = getCount();
/*?*/   for (long i=0; i<nCount; i++)
/*?*/       if ( getByIndex(i)->getName() == aName )
/*?*/           return TRUE;
/*?*/   return FALSE;
/*?*/ }

/*?*/ uno::Type SAL_CALL ScDPDimensions::getElementType() throw(uno::RuntimeException)
/*?*/ {
/*?*/   return getCppuType((uno::Reference<container::XNamed>*)0);
/*?*/ }

/*?*/ sal_Bool SAL_CALL ScDPDimensions::hasElements() throw(uno::RuntimeException)
/*?*/ {
/*?*/   return ( getCount() > 0 );
/*?*/ }

// end of XNameAccess implementation

/*N*/ long ScDPDimensions::getCount() const
/*N*/ {
/*N*/   //  in tabular data, every column of source data is a dimension
/*N*/
/*N*/   return nDimCount;
/*N*/ }

/*N*/ ScDPDimension* ScDPDimensions::getByIndex(long nIndex) const
/*N*/ {
/*N*/   if ( nIndex >= 0 && nIndex < nDimCount )
/*N*/   {
/*N*/       if ( !ppDims )
/*N*/       {
/*N*/           ((ScDPDimensions*)this)->ppDims = new ScDPDimension*[nDimCount];
/*N*/           for (long i=0; i<nDimCount; i++)
/*N*/               ppDims[i] = NULL;
/*N*/       }
/*N*/       if ( !ppDims[nIndex] )
/*N*/       {
/*N*/           ppDims[nIndex] = new ScDPDimension( pSource, nIndex );
/*N*/           ppDims[nIndex]->acquire();      // ref-counted
/*N*/       }
/*N*/
/*N*/       return ppDims[nIndex];
/*N*/   }
/*N*/
/*N*/   return NULL;    //! exception?
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScDPDimension::ScDPDimension( ScDPSource* pSrc, long nD ) :
/*N*/   pSource( pSrc ),
/*N*/   nDim( nD ),
/*N*/   pHierarchies( NULL ),
/*N*/   nUsedHier( 0 ),
/*N*/   nFunction( SUBTOTAL_FUNC_SUM ),     // sum is default
/*N*/   nSourceDim( -1 )
/*N*/ {
/*N*/   //! hold pSource
/*N*/ }

/*N*/ ScDPDimension::~ScDPDimension()
/*N*/ {
/*N*/   //! release pSource
/*N*/
/*N*/   if ( pHierarchies )
/*N*/       pHierarchies->release();    // ref-counted
/*N*/ }

/*N*/ ScDPHierarchies* ScDPDimension::GetHierarchiesObject()
/*N*/ {
/*N*/   if (!pHierarchies)
/*N*/   {
/*N*/       pHierarchies = new ScDPHierarchies( pSource, nDim );
/*N*/       pHierarchies->acquire();        // ref-counted
/*N*/   }
/*N*/   return pHierarchies;
/*N*/ }

/*N*/ uno::Reference<container::XNameAccess> SAL_CALL ScDPDimension::getHierarchies()
/*N*/                                                   throw(uno::RuntimeException)
/*N*/ {
/*N*/   return GetHierarchiesObject();
/*N*/ }

/*N*/ ::rtl::OUString SAL_CALL ScDPDimension::getName() throw(uno::RuntimeException)
/*N*/ {
/*N*/   if (aName.Len())
/*N*/       return aName;
/*N*/   else
/*N*/       return pSource->GetData()->getDimensionName( nDim );
/*N*/ }

/*?*/ void SAL_CALL ScDPDimension::setName( const ::rtl::OUString& rNewName ) throw(uno::RuntimeException)
/*?*/ {
/*?*/   //  used after cloning
/*?*/   aName = String( rNewName );
/*?*/ }

/*N*/ USHORT ScDPDimension::getOrientation() const
/*N*/ {
/*N*/   return pSource->GetOrientation( nDim );
/*N*/ }

/*N*/ void ScDPDimension::setOrientation(USHORT nNew)
/*N*/ {
/*N*/   pSource->SetOrientation( nDim, nNew );
/*N*/ }

/*N*/ long ScDPDimension::getPosition() const
/*N*/ {
/*N*/   return pSource->GetPosition( nDim );
/*N*/ }

//STRIP001 void ScDPDimension::setPosition(long nNew)
//STRIP001 {
//STRIP001  //! ...
//STRIP001 }

/*N*/ BOOL ScDPDimension::getIsDataLayoutDimension() const
/*N*/ {
/*N*/   return pSource->GetData()->getIsDataLayoutDimension( nDim );
/*N*/ }

/*N*/ USHORT ScDPDimension::getFunction() const
/*N*/ {
/*N*/   return nFunction;
/*N*/ }

/*N*/ void ScDPDimension::setFunction(USHORT nNew)
/*N*/ {
/*N*/   nFunction = nNew;
/*N*/ }

/*N*/ long ScDPDimension::getUsedHierarchy() const
/*N*/ {
/*N*/   return nUsedHier;
/*N*/ }

//STRIP001 void ScDPDimension::setUsedHierarchy(long nNew)
//STRIP001 {
//STRIP001  nUsedHier = nNew;
//STRIP001 }

//STRIP001 ScDPDimension* ScDPDimension::CreateCloneObject()
//STRIP001 {
//STRIP001  DBG_ASSERT( nSourceDim < 0, "recursive duplicate - not implemented" );
//STRIP001
//STRIP001  //! set new name here, or temporary name ???
//STRIP001  String aNewName = aName;
//STRIP001
//STRIP001  ScDPDimension* pNew = pSource->AddDuplicated( nDim, aNewName );
//STRIP001
//STRIP001  pNew->aName = aNewName;             //! here or in source?
//STRIP001  pNew->nSourceDim = nDim;            //! recursive?
//STRIP001
//STRIP001  return pNew;
//STRIP001 }

/*?*/ uno::Reference<util::XCloneable> SAL_CALL ScDPDimension::createClone() throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return uno::Reference<util::XCloneable>(0); //STRIP001
//STRIP001 /*?*/    return CreateCloneObject();
/*?*/ }

//STRIP001 BOOL ScDPDimension::isDuplicated() const
//STRIP001 {
//STRIP001  return (nSourceDim >= 0);
//STRIP001 }

// XPropertySet

/*?*/ uno::Reference<beans::XPropertySetInfo> SAL_CALL ScDPDimension::getPropertySetInfo()
/*?*/                                                       throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return uno::Reference<beans::XPropertySetInfo>(0); //STRIP001
//STRIP001  ScUnoGuard aGuard;
//STRIP001
//STRIP001  static SfxItemPropertyMap aDPDimensionMap_Impl[] =
//STRIP001  {
//STRIP001      {MAP_CHAR_LEN(SC_UNO_FUNCTION), 0,  &getCppuType((sheet::GeneralFunction*)0),   0, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_ISDATALA), 0,  &getBooleanCppuType(),                      beans::PropertyAttribute::READONLY, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_NUMBERFO), 0,  &getCppuType((sal_Int32*)0),                beans::PropertyAttribute::READONLY, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_ORIENTAT), 0,  &getCppuType((sheet::DataPilotFieldOrientation*)0), 0, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_ORIGINAL), 0,  &getCppuType((uno::Reference<container::XNamed>*)0), beans::PropertyAttribute::READONLY, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_POSITION), 0,  &getCppuType((sal_Int32*)0),                0, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_USEDHIER), 0,  &getCppuType((sal_Int32*)0),                0, 0 },
//STRIP001      {0,0,0,0}
//STRIP001  };
//STRIP001  static uno::Reference<beans::XPropertySetInfo> aRef =
//STRIP001      new SfxItemPropertySetInfo( aDPDimensionMap_Impl );
//STRIP001  return aRef;
/*?*/ }

/*N*/ void SAL_CALL ScDPDimension::setPropertyValue( const rtl::OUString& aPropertyName, const uno::Any& aValue )
/*N*/               throw(beans::UnknownPropertyException, beans::PropertyVetoException,
/*N*/                       lang::IllegalArgumentException, lang::WrappedTargetException,
/*N*/                       uno::RuntimeException)
/*N*/ {
/*N*/   String aNameStr = aPropertyName;
/*N*/   if ( aNameStr.EqualsAscii( SC_UNO_POSITION ) )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 INT32 nInt;
//STRIP001 /*?*/        if (aValue >>= nInt)
//STRIP001 /*?*/            setPosition( nInt );
/*N*/   }
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_USEDHIER ) )
/*N*/   {
/*?*/       INT32 nInt;
/*?*/       if (aValue >>= nInt)
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001    setUsedHierarchy( nInt );
/*N*/   }
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_ORIENTAT ) )
/*N*/   {
/*N*/       sheet::DataPilotFieldOrientation eEnum;
/*N*/       if (aValue >>= eEnum)
/*N*/           setOrientation( eEnum );
/*N*/   }
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_FUNCTION ) )
/*N*/   {
/*N*/       sheet::GeneralFunction eEnum;
/*N*/       if (aValue >>= eEnum)
/*N*/           setFunction( eEnum );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("unknown property");
/*N*/       //! THROW( UnknownPropertyException() );
/*N*/   }
/*N*/ }

/*N*/ uno::Any SAL_CALL ScDPDimension::getPropertyValue( const rtl::OUString& aPropertyName )
/*N*/               throw(beans::UnknownPropertyException, lang::WrappedTargetException,
/*N*/                       uno::RuntimeException)
/*N*/ {
/*N*/   uno::Any aRet;
/*N*/   String aNameStr = aPropertyName;
/*N*/   if ( aNameStr.EqualsAscii( SC_UNO_POSITION ) )
/*N*/       aRet <<= (sal_Int32) getPosition();
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_USEDHIER ) )
/*N*/       aRet <<= (sal_Int32) getUsedHierarchy();
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_ORIENTAT ) )
/*N*/   {
/*N*/       sheet::DataPilotFieldOrientation eVal = (sheet::DataPilotFieldOrientation)getOrientation();
/*N*/       aRet <<= eVal;
/*N*/   }
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_FUNCTION ) )
/*N*/   {
/*N*/       sheet::GeneralFunction eVal = (sheet::GeneralFunction)getFunction();
/*N*/       aRet <<= eVal;
/*N*/   }
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_ISDATALA ) )                 // read-only properties
/*N*/       lcl_SetBoolInAny( aRet, getIsDataLayoutDimension() );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_NUMBERFO ) )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    aRet <<= (sal_Int32) pSource->GetData()->GetNumberFormat(
//STRIP001 /*?*/                                            ( nSourceDim >= 0 ) ? nSourceDim : nDim );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_ORIGINAL ) )
/*N*/   {
/*N*/       uno::Reference<container::XNamed> xOriginal;
/*N*/       if (nSourceDim >= 0)
/*?*/           xOriginal = pSource->GetDimensionsObject()->getByIndex(nSourceDim);
/*N*/       aRet <<= xOriginal;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("unknown property");
/*N*/       //! THROW( UnknownPropertyException() );
/*N*/   }
/*N*/   return aRet;
/*N*/ }

/*N*/ SC_IMPL_DUMMY_PROPERTY_LISTENER( ScDPDimension )

// -----------------------------------------------------------------------

/*N*/ ScDPHierarchies::ScDPHierarchies( ScDPSource* pSrc, long nD ) :
/*N*/   pSource( pSrc ),
/*N*/   nDim( nD ),
/*N*/   ppHiers( NULL )
/*N*/ {
/*N*/   //! hold pSource
/*N*/
/*N*/   //  date columns have 3 hierarchies (flat/quarter/week), other columns only one
/*N*/   long nSrcDim = pSource->GetSourceDim( nDim );
/*N*/   if ( pSource->IsDateDimension( nSrcDim ) )
/*?*/       nHierCount = SC_DAPI_DATE_HIERARCHIES;
/*N*/   else
/*N*/       nHierCount = 1;
/*N*/ }

/*N*/ ScDPHierarchies::~ScDPHierarchies()
/*N*/ {
/*N*/   //! release pSource
/*N*/
/*N*/   if (ppHiers)
/*N*/   {
/*N*/       for (long i=0; i<nHierCount; i++)
/*N*/           if ( ppHiers[i] )
/*N*/               ppHiers[i]->release();      // ref-counted
/*N*/       delete[] ppHiers;
/*N*/   }
/*N*/ }

// very simple XNameAccess implementation using getCount/getByIndex

/*N*/ uno::Any SAL_CALL ScDPHierarchies::getByName( const rtl::OUString& aName )
/*N*/           throw(container::NoSuchElementException,
/*N*/                   lang::WrappedTargetException, uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       if ( getByIndex(i)->getName() == aName )
/*N*/       {
/*N*/           uno::Reference<container::XNamed> xNamed = getByIndex(i);
/*N*/           uno::Any aRet;
/*N*/           aRet <<= xNamed;
/*N*/           return aRet;
/*N*/       }
/*N*/
/*?*/   throw container::NoSuchElementException();
/*N*/   return uno::Any();
/*N*/ }

/*N*/ uno::Sequence<rtl::OUString> SAL_CALL ScDPHierarchies::getElementNames() throw(uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   uno::Sequence<rtl::OUString> aSeq(nCount);
/*N*/   rtl::OUString* pArr = aSeq.getArray();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       pArr[i] = getByIndex(i)->getName();
/*N*/   return aSeq;
/*N*/ }

/*?*/ sal_Bool SAL_CALL ScDPHierarchies::hasByName( const rtl::OUString& aName ) throw(uno::RuntimeException)
/*?*/ {
/*?*/   long nCount = getCount();
/*?*/   for (long i=0; i<nCount; i++)
/*?*/       if ( getByIndex(i)->getName() == aName )
/*?*/           return TRUE;
/*?*/   return FALSE;
/*?*/ }

/*?*/ uno::Type SAL_CALL ScDPHierarchies::getElementType() throw(uno::RuntimeException)
/*?*/ {
/*?*/   return getCppuType((uno::Reference<container::XNamed>*)0);
/*?*/ }

/*?*/ sal_Bool SAL_CALL ScDPHierarchies::hasElements() throw(uno::RuntimeException)
/*?*/ {
/*?*/   return ( getCount() > 0 );
/*?*/ }

// end of XNameAccess implementation

/*N*/ long ScDPHierarchies::getCount() const
/*N*/ {
/*N*/   return nHierCount;
/*N*/ }

/*N*/ ScDPHierarchy* ScDPHierarchies::getByIndex(long nIndex) const
/*N*/ {
/*N*/   //  pass hierarchy index to new object in case the implementation
/*N*/   //  will be extended to more than one hierarchy
/*N*/
/*N*/   if ( nIndex >= 0 && nIndex < nHierCount )
/*N*/   {
/*N*/       if ( !ppHiers )
/*N*/       {
/*N*/           ((ScDPHierarchies*)this)->ppHiers = new ScDPHierarchy*[nHierCount];
/*N*/           for (long i=0; i<nHierCount; i++)
/*N*/               ppHiers[i] = NULL;
/*N*/       }
/*N*/       if ( !ppHiers[nIndex] )
/*N*/       {
/*N*/           ppHiers[nIndex] = new ScDPHierarchy( pSource, nDim, nIndex );
/*N*/           ppHiers[nIndex]->acquire();         // ref-counted
/*N*/       }
/*N*/
/*N*/       return ppHiers[nIndex];
/*N*/   }
/*N*/
/*N*/   return NULL;    //! exception?
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScDPHierarchy::ScDPHierarchy( ScDPSource* pSrc, long nD, long nH ) :
/*N*/   pSource( pSrc ),
/*N*/   nDim( nD ),
/*N*/   nHier( nH ),
/*N*/   pLevels( NULL )
/*N*/ {
/*N*/   //! hold pSource
/*N*/ }

/*N*/ ScDPHierarchy::~ScDPHierarchy()
/*N*/ {
/*N*/   //! release pSource
/*N*/
/*N*/   if (pLevels)
/*N*/       pLevels->release();     // ref-counted
/*N*/ }

/*N*/ ScDPLevels* ScDPHierarchy::GetLevelsObject()
/*N*/ {
/*N*/   if (!pLevels)
/*N*/   {
/*N*/       pLevels = new ScDPLevels( pSource, nDim, nHier );
/*N*/       pLevels->acquire();     // ref-counted
/*N*/   }
/*N*/   return pLevels;
/*N*/ }

/*N*/ uno::Reference<container::XNameAccess> SAL_CALL ScDPHierarchy::getLevels()
/*N*/                                                   throw(uno::RuntimeException)
/*N*/ {
/*N*/   return GetLevelsObject();
/*N*/ }

/*N*/ ::rtl::OUString SAL_CALL ScDPHierarchy::getName() throw(uno::RuntimeException)
/*N*/ {
/*N*/   String aRet;        //! globstr-ID !!!!
/*N*/   switch (nHier)
/*N*/   {
/*N*/       case SC_DAPI_HIERARCHY_FLAT:
/*N*/           aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("flat"));
/*N*/           break;  //! name ???????
/*N*/       case SC_DAPI_HIERARCHY_QUARTER:
/*?*/           aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Quarter"));
/*?*/           break;  //! name ???????
/*N*/       case SC_DAPI_HIERARCHY_WEEK:
/*?*/           aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Week"));
/*?*/           break;  //! name ???????
/*N*/   }
/*N*/   return aRet;
/*N*/ }

/*?*/ void SAL_CALL ScDPHierarchy::setName( const ::rtl::OUString& rNewName ) throw(uno::RuntimeException)
/*?*/ {
/*?*/   DBG_ERROR("not implemented");       //! exception?
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ ScDPLevels::ScDPLevels( ScDPSource* pSrc, long nD, long nH ) :
/*N*/   pSource( pSrc ),
/*N*/   nDim( nD ),
/*N*/   nHier( nH ),
/*N*/   ppLevs( NULL )
/*N*/ {
/*N*/   //! hold pSource
/*N*/
/*N*/   //  text columns have only one level
/*N*/
/*N*/   long nSrcDim = pSource->GetSourceDim( nDim );
/*N*/   if ( pSource->IsDateDimension( nSrcDim ) )
/*N*/   {
/*?*/       switch ( nHier )
/*?*/       {
/*?*/           case SC_DAPI_HIERARCHY_FLAT:    nLevCount = SC_DAPI_FLAT_LEVELS;    break;
/*?*/           case SC_DAPI_HIERARCHY_QUARTER: nLevCount = SC_DAPI_QUARTER_LEVELS; break;
/*?*/           case SC_DAPI_HIERARCHY_WEEK:    nLevCount = SC_DAPI_WEEK_LEVELS;    break;
/*?*/           default:
/*?*/               DBG_ERROR("wrong hierarchy");
/*?*/               nLevCount = 0;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/       nLevCount = 1;
/*N*/ }

/*N*/ ScDPLevels::~ScDPLevels()
/*N*/ {
/*N*/   //! release pSource
/*N*/
/*N*/   if (ppLevs)
/*N*/   {
/*N*/       for (long i=0; i<nLevCount; i++)
/*N*/           if ( ppLevs[i] )
/*N*/               ppLevs[i]->release();   // ref-counted
/*N*/       delete[] ppLevs;
/*N*/   }
/*N*/ }

// very simple XNameAccess implementation using getCount/getByIndex

/*N*/ uno::Any SAL_CALL ScDPLevels::getByName( const rtl::OUString& aName )
/*N*/           throw(container::NoSuchElementException,
/*N*/                   lang::WrappedTargetException, uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       if ( getByIndex(i)->getName() == aName )
/*N*/       {
/*N*/           uno::Reference<container::XNamed> xNamed = getByIndex(i);
/*N*/           uno::Any aRet;
/*N*/           aRet <<= xNamed;
/*N*/           return aRet;
/*N*/       }
/*N*/
/*?*/   throw container::NoSuchElementException();
/*N*/   return uno::Any();
/*N*/ }

/*N*/ uno::Sequence<rtl::OUString> SAL_CALL ScDPLevels::getElementNames() throw(uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   uno::Sequence<rtl::OUString> aSeq(nCount);
/*N*/   rtl::OUString* pArr = aSeq.getArray();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       pArr[i] = getByIndex(i)->getName();
/*N*/   return aSeq;
/*N*/ }

/*N*/ sal_Bool SAL_CALL ScDPLevels::hasByName( const rtl::OUString& aName ) throw(uno::RuntimeException)
/*N*/ {
/*N*/   long nCount = getCount();
/*N*/   for (long i=0; i<nCount; i++)
/*N*/       if ( getByIndex(i)->getName() == aName )
/*N*/           return TRUE;
/*N*/   return FALSE;
/*N*/ }

/*N*/ uno::Type SAL_CALL ScDPLevels::getElementType() throw(uno::RuntimeException)
/*N*/ {
/*N*/   return getCppuType((uno::Reference<container::XNamed>*)0);
/*N*/ }

/*N*/ sal_Bool SAL_CALL ScDPLevels::hasElements() throw(uno::RuntimeException)
/*N*/ {
/*N*/   return ( getCount() > 0 );
/*N*/ }

// end of XNameAccess implementation

/*N*/ long ScDPLevels::getCount() const
/*N*/ {
/*N*/   return nLevCount;
/*N*/ }

/*N*/ ScDPLevel* ScDPLevels::getByIndex(long nIndex) const
/*N*/ {
/*N*/   if ( nIndex >= 0 && nIndex < nLevCount )
/*N*/   {
/*N*/       if ( !ppLevs )
/*N*/       {
/*N*/           ((ScDPLevels*)this)->ppLevs = new ScDPLevel*[nLevCount];
/*N*/           for (long i=0; i<nLevCount; i++)
/*N*/               ppLevs[i] = NULL;
/*N*/       }
/*N*/       if ( !ppLevs[nIndex] )
/*N*/       {
/*N*/           ppLevs[nIndex] = new ScDPLevel( pSource, nDim, nHier, nIndex );
/*N*/           ppLevs[nIndex]->acquire();      // ref-counted
/*N*/       }
/*N*/
/*N*/       return ppLevs[nIndex];
/*N*/   }
/*N*/
/*N*/   return NULL;    //! exception?
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScDPLevel::ScDPLevel( ScDPSource* pSrc, long nD, long nH, long nL ) :
/*N*/   pSource( pSrc ),
/*N*/   nDim( nD ),
/*N*/   nHier( nH ),
/*N*/   nLev( nL ),
/*N*/   pMembers( NULL ),
/*N*/   bShowEmpty( FALSE )
/*N*/ {
/*N*/   //! hold pSource
/*N*/   //  aSubTotals is empty
/*N*/ }

/*N*/ ScDPLevel::~ScDPLevel()
/*N*/ {
/*N*/   //! release pSource
/*N*/
/*N*/   if ( pMembers )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    pMembers->release();    // ref-counted
/*N*/ }

//STRIP001 ScDPMembers* ScDPLevel::GetMembersObject()
//STRIP001 {
//STRIP001  if (!pMembers)
//STRIP001  {
//STRIP001      pMembers = new ScDPMembers( pSource, nDim, nHier, nLev );
//STRIP001      pMembers->acquire();    // ref-counted
//STRIP001  }
//STRIP001  return pMembers;
//STRIP001 }

/*?*/ uno::Reference<container::XNameAccess> SAL_CALL ScDPLevel::getMembers() throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return uno::Reference<container::XNameAccess>(0); //STRIP001
//STRIP001 /*?*/    return GetMembersObject();
/*?*/ }

/*?*/ uno::Sequence<sheet::MemberResult> SAL_CALL ScDPLevel::getResults() throw(uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/    const uno::Sequence<sheet::MemberResult>* pRes = pSource->GetMemberResults( this );
//STRIP001 /*?*/    if (pRes)
//STRIP001 /*?*/        return *pRes;
//STRIP001 /*?*/
/*?*/   return uno::Sequence<sheet::MemberResult>(0);       //! Error?
/*?*/ }

/*N*/ ::rtl::OUString SAL_CALL ScDPLevel::getName() throw(uno::RuntimeException)
/*N*/ {
/*N*/   long nSrcDim = pSource->GetSourceDim( nDim );
/*N*/   if ( pSource->IsDateDimension( nSrcDim ) )
/*?*/   {
/*?*/       String aRet;        //! globstr-ID !!!!
/*?*/
/*?*/       if ( nHier == SC_DAPI_HIERARCHY_QUARTER )
/*?*/       {
/*?*/           switch ( nLev )
/*?*/           {
/*?*/               case SC_DAPI_LEVEL_YEAR:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Year"));
/*?*/                   break;
/*?*/               case SC_DAPI_LEVEL_QUARTER:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Quarter"));
/*?*/                   break;
/*?*/               case SC_DAPI_LEVEL_MONTH:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Month"));
/*?*/                   break;
/*?*/               case SC_DAPI_LEVEL_DAY:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Day"));
/*?*/                   break;
/*?*/           }
/*?*/       }
/*?*/       else if ( nHier == SC_DAPI_HIERARCHY_WEEK )
/*?*/       {
/*?*/           switch ( nLev )
/*?*/           {
/*?*/               case SC_DAPI_LEVEL_YEAR:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Year"));
/*?*/                   break;
/*?*/               case SC_DAPI_LEVEL_WEEK:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Week"));
/*?*/                   break;
/*?*/               case SC_DAPI_LEVEL_WEEKDAY:
/*?*/                   aRet = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Weekday"));
/*?*/                   break;
/*?*/           }
/*?*/       }
/*?*/       if (aRet.Len())
/*?*/           return aRet;
/*N*/   }
/*N*/
/*N*/   return pSource->GetData()->getDimensionName( nSrcDim );     // (original) dimension name
/*N*/ }

/*?*/ void SAL_CALL ScDPLevel::setName( const ::rtl::OUString& rNewName ) throw(uno::RuntimeException)
/*?*/ {
/*?*/   DBG_ERROR("not implemented");       //! exception?
/*?*/ }

/*N*/ uno::Sequence<sheet::GeneralFunction> ScDPLevel::getSubTotals() const
/*N*/ {
/*N*/   //! separate functions for settings and evaluation?
/*N*/
/*N*/   long nSrcDim = pSource->GetSourceDim( nDim );
/*N*/   if ( !pSource->SubTotalAllowed( nSrcDim ) )
/*N*/       return uno::Sequence<sheet::GeneralFunction>(0);
/*N*/
/*N*/   return aSubTotals;
/*N*/ }

//STRIP001 void ScDPLevel::setSubTotals(const uno::Sequence<sheet::GeneralFunction>& rNew)
//STRIP001 {
//STRIP001  aSubTotals = rNew;
//STRIP001  //! set "manual change" flag?
//STRIP001 }

//STRIP001 BOOL ScDPLevel::getShowEmpty() const
//STRIP001 {
//STRIP001  return bShowEmpty;
//STRIP001 }

/*N*/ void ScDPLevel::setShowEmpty(BOOL bSet)
/*N*/ {
/*N*/   bShowEmpty = bSet;
/*N*/ }

// XPropertySet

/*N*/ uno::Reference<beans::XPropertySetInfo> SAL_CALL ScDPLevel::getPropertySetInfo()
/*N*/                                                       throw(uno::RuntimeException)
/*N*/ {
/*N*/   ScUnoGuard aGuard;
/*N*/
/*N*/   static SfxItemPropertyMap aDPLevelMap_Impl[] =
/*N*/   {
/*N*/       {MAP_CHAR_LEN(SC_UNO_SHOWEMPT), 0,  &getBooleanCppuType(),                                   0, 0 },
/*N*/       {MAP_CHAR_LEN(SC_UNO_SUBTOTAL), 0,  &getCppuType((uno::Sequence<sheet::GeneralFunction>*)0), 0, 0 },
/*N*/       {0,0,0,0}
/*N*/   };
/*N*/   static uno::Reference<beans::XPropertySetInfo> aRef =
/*N*/       new SfxItemPropertySetInfo( aDPLevelMap_Impl );
/*N*/   return aRef;
/*N*/ }

/*N*/ void SAL_CALL ScDPLevel::setPropertyValue( const rtl::OUString& aPropertyName, const uno::Any& aValue )
/*N*/               throw(beans::UnknownPropertyException, beans::PropertyVetoException,
/*N*/                       lang::IllegalArgumentException, lang::WrappedTargetException,
/*N*/                       uno::RuntimeException)
/*N*/ {
/*N*/   String aNameStr = aPropertyName;
/*N*/   if ( aNameStr.EqualsAscii( SC_UNO_SHOWEMPT ) )
/*N*/       setShowEmpty( lcl_GetBoolFromAny( aValue ) );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_SUBTOTAL ) )
/*N*/   {
/*?*/       uno::Sequence<sheet::GeneralFunction> aSeq;
/*?*/       if ( aValue >>= aSeq )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001    setSubTotals( aSeq );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("unknown property");
/*N*/       //! THROW( UnknownPropertyException() );
/*N*/   }
/*N*/ }

/*N*/ uno::Any SAL_CALL ScDPLevel::getPropertyValue( const rtl::OUString& aPropertyName )
/*N*/               throw(beans::UnknownPropertyException, lang::WrappedTargetException,
/*N*/                       uno::RuntimeException)
/*N*/ {
/*N*/   uno::Any aRet;
/*N*/   String aNameStr = aPropertyName;
/*N*/   if ( aNameStr.EqualsAscii( SC_UNO_SHOWEMPT ) )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    lcl_SetBoolInAny( aRet, getShowEmpty() );
/*N*/   else if ( aNameStr.EqualsAscii( SC_UNO_SUBTOTAL ) )
/*N*/   {
/*N*/       uno::Sequence<sheet::GeneralFunction> aSeq = getSubTotals();        //! avoid extra copy?
/*N*/       aRet <<= aSeq;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("unknown property");
/*N*/       //! THROW( UnknownPropertyException() );
/*N*/   }
/*N*/   return aRet;
/*N*/ }

/*N*/ SC_IMPL_DUMMY_PROPERTY_LISTENER( ScDPLevel )

// -----------------------------------------------------------------------

//STRIP001 USHORT lcl_GetFirstStringPos( const TypedStrCollection& rColl )
//STRIP001 {
//STRIP001  USHORT nPos = 0;
//STRIP001  USHORT nCount = rColl.GetCount();
//STRIP001  while ( nPos < nCount && !rColl[nPos]->IsStrData() )
//STRIP001      ++nPos;
//STRIP001  return nPos;
//STRIP001 }

//STRIP001 ScDPMembers::ScDPMembers( ScDPSource* pSrc, long nD, long nH, long nL ) :
//STRIP001  pSource( pSrc ),
//STRIP001  nDim( nD ),
//STRIP001  nHier( nH ),
//STRIP001  nLev( nL ),
//STRIP001  ppMbrs( NULL )
//STRIP001 {
//STRIP001  //! hold pSource
//STRIP001
//STRIP001  long nSrcDim = pSource->GetSourceDim( nDim );
//STRIP001  if ( pSource->IsDataLayoutDimension(nSrcDim) )
//STRIP001      nMbrCount = pSource->GetDataDimensionCount();
//STRIP001  else if ( nHier != SC_DAPI_HIERARCHY_FLAT && pSource->IsDateDimension( nSrcDim ) )
//STRIP001  {
//STRIP001      nMbrCount = 0;
//STRIP001      if ( nHier == SC_DAPI_HIERARCHY_QUARTER )
//STRIP001      {
//STRIP001          switch (nLev)
//STRIP001          {
//STRIP001              case SC_DAPI_LEVEL_YEAR:
//STRIP001                  {
//STRIP001                      const TypedStrCollection& rStrings = pSource->GetData()->GetColumnEntries(nSrcDim);
//STRIP001                      USHORT nFirstString = lcl_GetFirstStringPos( rStrings );
//STRIP001                      if ( nFirstString > 0 )
//STRIP001                      {
//STRIP001                          double fFirstVal = rStrings[0]->GetValue();
//STRIP001                          double fLastVal = rStrings[nFirstString-1]->GetValue();
//STRIP001
//STRIP001                          long nFirstYear = pSource->GetData()->GetDatePart(
//STRIP001                                      (long)::rtl::math::approxFloor( fFirstVal ),
//STRIP001                                      nHier, nLev );
//STRIP001                          long nLastYear = pSource->GetData()->GetDatePart(
//STRIP001                                      (long)::rtl::math::approxFloor( fLastVal ),
//STRIP001                                      nHier, nLev );
//STRIP001
//STRIP001                          nMbrCount = nLastYear + 1 - nFirstYear;
//STRIP001                      }
//STRIP001                      else
//STRIP001                          nMbrCount = 0;      // no values
//STRIP001                  }
//STRIP001                  break;
//STRIP001              case SC_DAPI_LEVEL_QUARTER: nMbrCount = 4;  break;
//STRIP001              case SC_DAPI_LEVEL_MONTH:   nMbrCount = 12; break;
//STRIP001              case SC_DAPI_LEVEL_DAY:     nMbrCount = 31; break;
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( nHier == SC_DAPI_HIERARCHY_WEEK )
//STRIP001      {
//STRIP001          switch (nLev)
//STRIP001          {
//STRIP001              case SC_DAPI_LEVEL_YEAR:    nMbrCount = 1;  break;      //! get years from source
//STRIP001              case SC_DAPI_LEVEL_WEEK:    nMbrCount = 53; break;
//STRIP001              case SC_DAPI_LEVEL_WEEKDAY: nMbrCount = 7;  break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //  StringCollection is cached at TableData
//STRIP001      const TypedStrCollection& rStrings = pSource->GetData()->GetColumnEntries(nSrcDim);
//STRIP001      nMbrCount = rStrings.GetCount();
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 ScDPMembers::~ScDPMembers()
//STRIP001 {
//STRIP001  //! release pSource
//STRIP001
//STRIP001  if (ppMbrs)
//STRIP001  {
//STRIP001      for (long i=0; i<nMbrCount; i++)
//STRIP001          if ( ppMbrs[i] )
//STRIP001              ppMbrs[i]->release();   // ref-counted
//STRIP001      delete[] ppMbrs;
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 // very simple XNameAccess implementation using getCount/getByIndex
//STRIP001
//STRIP001 uno::Any SAL_CALL ScDPMembers::getByName( const rtl::OUString& aName )
//STRIP001          throw(container::NoSuchElementException,
//STRIP001                  lang::WrappedTargetException, uno::RuntimeException)
//STRIP001 {
//STRIP001  long nCount = getCount();
//STRIP001  for (long i=0; i<nCount; i++)
//STRIP001      if ( getByIndex(i)->getName() == aName )
//STRIP001      {
//STRIP001          uno::Reference<container::XNamed> xNamed = getByIndex(i);
//STRIP001          uno::Any aRet;
//STRIP001          aRet <<= xNamed;
//STRIP001          return aRet;
//STRIP001      }
//STRIP001
//STRIP001  throw container::NoSuchElementException();
//STRIP001  return uno::Any();
//STRIP001 }
//STRIP001
//STRIP001 uno::Sequence<rtl::OUString> SAL_CALL ScDPMembers::getElementNames() throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  long nCount = getCount();
//STRIP001  uno::Sequence<rtl::OUString> aSeq(nCount);
//STRIP001  rtl::OUString* pArr = aSeq.getArray();
//STRIP001  for (long i=0; i<nCount; i++)
//STRIP001      pArr[i] = getByIndex(i)->getName();
//STRIP001  return aSeq;
//STRIP001 }
//STRIP001
//STRIP001 sal_Bool SAL_CALL ScDPMembers::hasByName( const rtl::OUString& aName ) throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  long nCount = getCount();
//STRIP001  for (long i=0; i<nCount; i++)
//STRIP001      if ( getByIndex(i)->getName() == aName )
//STRIP001          return TRUE;
//STRIP001  return FALSE;
//STRIP001 }
//STRIP001
//STRIP001 uno::Type SAL_CALL ScDPMembers::getElementType() throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  return getCppuType((uno::Reference<container::XNamed>*)0);
//STRIP001 }
//STRIP001
//STRIP001 sal_Bool SAL_CALL ScDPMembers::hasElements() throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  return ( getCount() > 0 );
//STRIP001 }
//STRIP001
//STRIP001 // end of XNameAccess implementation
//STRIP001
//STRIP001 long ScDPMembers::getCount() const
//STRIP001 {
//STRIP001  return nMbrCount;
//STRIP001 }
//STRIP001
//STRIP001 long ScDPMembers::getMinMembers() const
//STRIP001 {
//STRIP001  // used in lcl_CountMinMembers
//STRIP001
//STRIP001  long nVisCount = 0;
//STRIP001  if ( ppMbrs )
//STRIP001  {
//STRIP001      for (long i=0; i<nMbrCount; i++)
//STRIP001      {
//STRIP001          //  count only visible with details (default is true for both)
//STRIP001          const ScDPMember* pMbr = ppMbrs[i];
//STRIP001          if ( !pMbr || ( pMbr->getIsVisible() && pMbr->getShowDetails() ) )
//STRIP001              ++nVisCount;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      nVisCount = nMbrCount;      // default for all
//STRIP001
//STRIP001  return nVisCount;
//STRIP001 }
//STRIP001
//STRIP001 ScDPMember* ScDPMembers::getByIndex(long nIndex) const
//STRIP001 {
//STRIP001  //  result of GetColumnEntries must not change between ScDPMembers ctor
//STRIP001  //  and all calls to getByIndex
//STRIP001
//STRIP001  if ( nIndex >= 0 && nIndex < nMbrCount )
//STRIP001  {
//STRIP001      if ( !ppMbrs )
//STRIP001      {
//STRIP001          ((ScDPMembers*)this)->ppMbrs = new ScDPMember*[nMbrCount];
//STRIP001          for (long i=0; i<nMbrCount; i++)
//STRIP001              ppMbrs[i] = NULL;
//STRIP001      }
//STRIP001      if ( !ppMbrs[nIndex] )
//STRIP001      {
//STRIP001          ScDPMember* pNew;
//STRIP001          long nSrcDim = pSource->GetSourceDim( nDim );
//STRIP001          if ( pSource->IsDataLayoutDimension(nSrcDim) )
//STRIP001          {
//STRIP001              // empty name (never shown, not used for lookup)
//STRIP001              pNew = new ScDPMember( pSource, nDim, nHier, nLev,
//STRIP001                                      String(), 0.0, FALSE );
//STRIP001          }
//STRIP001          else if ( nHier != SC_DAPI_HIERARCHY_FLAT && pSource->IsDateDimension( nSrcDim ) )
//STRIP001          {
//STRIP001              long nVal = 0;
//STRIP001              String aName;
//STRIP001
//STRIP001              if ( nLev == SC_DAPI_LEVEL_YEAR )   // YEAR is in both hierarchies
//STRIP001              {
//STRIP001                  //! cache year range here!
//STRIP001
//STRIP001                  const TypedStrCollection& rStrings = pSource->GetData()->GetColumnEntries(nSrcDim);
//STRIP001                  double fFirstVal = rStrings[0]->GetValue();
//STRIP001                  long nFirstYear = pSource->GetData()->GetDatePart(
//STRIP001                                      (long)::rtl::math::approxFloor( fFirstVal ),
//STRIP001                                      nHier, nLev );
//STRIP001
//STRIP001                  nVal = nFirstYear + nIndex;
//STRIP001              }
//STRIP001              else if ( nHier == SC_DAPI_HIERARCHY_WEEK && nLev == SC_DAPI_LEVEL_WEEKDAY )
//STRIP001              {
//STRIP001                  nVal = nIndex;              // DayOfWeek is 0-based
//STRIP001                  aName = ScGlobal::pCalendar->getDisplayName(
//STRIP001                      ::com::sun::star::i18n::CalendarDisplayIndex::DAY,
//STRIP001                      nVal, 0 );
//STRIP001              }
//STRIP001              else if ( nHier == SC_DAPI_HIERARCHY_QUARTER && nLev == SC_DAPI_LEVEL_MONTH )
//STRIP001              {
//STRIP001                  nVal = nIndex;              // Month is 0-based
//STRIP001                  aName = ScGlobal::pCalendar->getDisplayName(
//STRIP001                      ::com::sun::star::i18n::CalendarDisplayIndex::MONTH,
//STRIP001                      nVal, 0 );
//STRIP001              }
//STRIP001              else
//STRIP001                  nVal = nIndex + 1;          // Quarter, Day, Week are 1-based
//STRIP001
//STRIP001              if ( !aName.Len() )
//STRIP001                  aName = String::CreateFromInt32(nVal);
//STRIP001
//STRIP001              pNew = new ScDPMember( pSource, nDim, nHier, nLev, aName, nVal, TRUE );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              const TypedStrCollection& rStrings = pSource->GetData()->GetColumnEntries(nSrcDim);
//STRIP001              const TypedStrData* pData = rStrings[(USHORT)nIndex];
//STRIP001              pNew = new ScDPMember( pSource, nDim, nHier, nLev,
//STRIP001                                      pData->GetString(), pData->GetValue(), !pData->IsStrData() );
//STRIP001          }
//STRIP001          pNew->acquire();            // ref-counted
//STRIP001          ppMbrs[nIndex] = pNew;
//STRIP001      }
//STRIP001
//STRIP001      return ppMbrs[nIndex];
//STRIP001  }
//STRIP001
//STRIP001  return NULL;    //! exception?
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ScDPMember::ScDPMember( ScDPSource* pSrc, long nD, long nH, long nL,
//STRIP001                      const String& rN, double fV, BOOL bHV ) :
//STRIP001  pSource( pSrc ),
//STRIP001  nDim( nD ),
//STRIP001  nHier( nH ),
//STRIP001  nLev( nL ),
//STRIP001  aName( rN ),
//STRIP001  fValue( fV ),
//STRIP001  bHasValue( bHV ),
//STRIP001  bVisible( TRUE ),
//STRIP001  bShowDet( TRUE )
//STRIP001 {
//STRIP001  //! hold pSource
//STRIP001 }
//STRIP001
//STRIP001 ScDPMember::~ScDPMember()
//STRIP001 {
//STRIP001  //! release pSource
//STRIP001 }
//STRIP001
//STRIP001 BOOL ScDPMember::IsNamedItem( const ScDPItemData& r ) const
//STRIP001 {
//STRIP001  long nSrcDim = pSource->GetSourceDim( nDim );
//STRIP001  if ( nHier != SC_DAPI_HIERARCHY_FLAT && pSource->IsDateDimension( nSrcDim ) && r.bHasValue )
//STRIP001  {
//STRIP001      long nComp = pSource->GetData()->GetDatePart(
//STRIP001                                      (long)::rtl::math::approxFloor( r.fValue ),
//STRIP001                                      nHier, nLev );
//STRIP001
//STRIP001      //  fValue is converted from integer, so simple comparison works
//STRIP001      return nComp == fValue;
//STRIP001  }
//STRIP001
//STRIP001  return r.IsCaseInsEqual( ScDPItemData( aName, fValue, bHasValue ) );
//STRIP001 }
//STRIP001
//STRIP001 String ScDPMember::GetNameStr() const
//STRIP001 {
//STRIP001  return aName;
//STRIP001 }
//STRIP001
//STRIP001 ::rtl::OUString SAL_CALL ScDPMember::getName() throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  return aName;
//STRIP001 }
//STRIP001
//STRIP001 void SAL_CALL ScDPMember::setName( const ::rtl::OUString& rNewName ) throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  DBG_ERROR("not implemented");       //! exception?
//STRIP001 }
//STRIP001
//STRIP001 BOOL ScDPMember::getIsVisible() const
//STRIP001 {
//STRIP001  return bVisible;
//STRIP001 }
//STRIP001
//STRIP001 void ScDPMember::setIsVisible(BOOL bSet)
//STRIP001 {
//STRIP001  bVisible = bSet;
//STRIP001  //! set "manual change" flag
//STRIP001 }
//STRIP001
//STRIP001 BOOL ScDPMember::getShowDetails() const
//STRIP001 {
//STRIP001  return bShowDet;
//STRIP001 }
//STRIP001
//STRIP001 void ScDPMember::setShowDetails(BOOL bSet)
//STRIP001 {
//STRIP001  bShowDet = bSet;
//STRIP001  //! set "manual change" flag
//STRIP001 }
//STRIP001
//STRIP001 // XPropertySet
//STRIP001
//STRIP001 uno::Reference<beans::XPropertySetInfo> SAL_CALL ScDPMember::getPropertySetInfo()
//STRIP001                                                      throw(uno::RuntimeException)
//STRIP001 {
//STRIP001  ScUnoGuard aGuard;
//STRIP001
//STRIP001  static SfxItemPropertyMap aDPMemberMap_Impl[] =
//STRIP001  {
//STRIP001      {MAP_CHAR_LEN(SC_UNO_ISVISIBL), 0,  &getBooleanCppuType(),              0, 0 },
//STRIP001      {MAP_CHAR_LEN(SC_UNO_SHOWDETA), 0,  &getBooleanCppuType(),              0, 0 },
//STRIP001      {0,0,0,0}
//STRIP001  };
//STRIP001  static uno::Reference<beans::XPropertySetInfo> aRef =
//STRIP001      new SfxItemPropertySetInfo( aDPMemberMap_Impl );
//STRIP001  return aRef;
//STRIP001 }
//STRIP001
//STRIP001 void SAL_CALL ScDPMember::setPropertyValue( const rtl::OUString& aPropertyName, const uno::Any& aValue )
//STRIP001              throw(beans::UnknownPropertyException, beans::PropertyVetoException,
//STRIP001                      lang::IllegalArgumentException, lang::WrappedTargetException,
//STRIP001                      uno::RuntimeException)
//STRIP001 {
//STRIP001  String aNameStr = aPropertyName;
//STRIP001  if ( aNameStr.EqualsAscii( SC_UNO_ISVISIBL ) )
//STRIP001      setIsVisible( lcl_GetBoolFromAny( aValue ) );
//STRIP001  else if ( aNameStr.EqualsAscii( SC_UNO_SHOWDETA ) )
//STRIP001      setShowDetails( lcl_GetBoolFromAny( aValue ) );
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR("unknown property");
//STRIP001      //! THROW( UnknownPropertyException() );
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 uno::Any SAL_CALL ScDPMember::getPropertyValue( const rtl::OUString& aPropertyName )
//STRIP001              throw(beans::UnknownPropertyException, lang::WrappedTargetException,
//STRIP001                      uno::RuntimeException)
//STRIP001 {
//STRIP001  uno::Any aRet;
//STRIP001  String aNameStr = aPropertyName;
//STRIP001  if ( aNameStr.EqualsAscii( SC_UNO_ISVISIBL ) )
//STRIP001      lcl_SetBoolInAny( aRet, getIsVisible() );
//STRIP001  else if ( aNameStr.EqualsAscii( SC_UNO_SHOWDETA ) )
//STRIP001      lcl_SetBoolInAny( aRet, getShowDetails() );
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR("unknown property");
//STRIP001      //! THROW( UnknownPropertyException() );
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }
//STRIP001
//STRIP001 SC_IMPL_DUMMY_PROPERTY_LISTENER( ScDPMember )



