/*************************************************************************
 *
 *  $RCSfile: sc_dpoutput.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:35:01 $
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

#include "scitems.hxx"
#include <bf_svx/algitem.hxx>
#include <bf_svx/boxitem.hxx>
#include <bf_svx/brshitem.hxx>
#include <bf_svx/wghtitem.hxx>

#include "dpoutput.hxx"
#include "document.hxx"
#include "patattr.hxx"
#include "docpool.hxx"
#include "markdata.hxx"
#include "attrib.hxx"
#include "compiler.hxx"     // errNoValue
#include "miscuno.hxx"
#include "globstr.hrc"
#include "stlpool.hxx"
#include "stlsheet.hxx"

#include <com/sun/star/sheet/XLevelsSupplier.hpp>
#include <com/sun/star/sheet/XHierarchiesSupplier.hpp>
#include <com/sun/star/sheet/XDataPilotResults.hpp>
#include <com/sun/star/sheet/XDataPilotMemberResults.hpp>
#include <com/sun/star/sheet/DataResultFlags.hpp>
#include <com/sun/star/sheet/MemberResultFlags.hpp>
#include <com/sun/star/sheet/DataPilotFieldOrientation.hpp>
#include <com/sun/star/container/XNamed.hpp>

using namespace com::sun::star;

// -----------------------------------------------------------------------

//! move to a header file
#define DP_PROP_ORIENTATION         "Orientation"
#define DP_PROP_POSITION            "Position"
#define DP_PROP_USEDHIERARCHY       "UsedHierarchy"
#define DP_PROP_DATADESCR           "DataDescription"
#define DP_PROP_ISDATALAYOUT        "IsDataLayoutDimension"
#define DP_PROP_NUMBERFORMAT        "NumberFormat"

// -----------------------------------------------------------------------

//! dynamic!!!
#define SC_DPOUT_MAXLEVELS  256


struct ScDPOutLevelData
{
    long                                nDim;
    long                                nHier;
    long                                nLevel;
    long                                nDimPos;
    uno::Sequence<sheet::MemberResult>  aResult;
    String                              aCaption;

    ScDPOutLevelData() { nDim = nHier = nLevel = nDimPos = -1; }

    BOOL operator<(const ScDPOutLevelData& r) const
        { return nDimPos<r.nDimPos || ( nDimPos==r.nDimPos && nHier<r.nHier ) ||
            ( nDimPos==r.nDimPos && nHier==r.nHier && nLevel<r.nLevel ); }

    void Swap(ScDPOutLevelData& r)
//!     { ScDPOutLevelData aTemp = r; r = *this; *this = aTemp; }
        { ScDPOutLevelData aTemp; aTemp = r; r = *this; *this = aTemp; }

    //! bug (73840) in uno::Sequence - copy and then assign doesn't work!
};

// -----------------------------------------------------------------------

//STRIP001 void lcl_SetStyleById( ScDocument* pDoc, USHORT nTab,
//STRIP001                  USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                  USHORT nStrId )
//STRIP001 {
//STRIP001  if ( nCol1 > nCol2 || nRow1 > nRow2 )
//STRIP001  {
//STRIP001      DBG_ERROR("SetStyleById: invalid range");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  String aStyleName = ScGlobal::GetRscString( nStrId );
//STRIP001  ScStyleSheetPool* pStlPool = pDoc->GetStyleSheetPool();
//STRIP001  ScStyleSheet* pStyle = (ScStyleSheet*) pStlPool->Find( aStyleName, SFX_STYLE_FAMILY_PARA );
//STRIP001  if (!pStyle)
//STRIP001  {
//STRIP001      //  create new style (was in ScPivot::SetStyle)
//STRIP001
//STRIP001      pStyle = (ScStyleSheet*) &pStlPool->Make( aStyleName, SFX_STYLE_FAMILY_PARA,
//STRIP001                                                  SFXSTYLEBIT_USERDEF );
//STRIP001      pStyle->SetParent( ScGlobal::GetRscString(STR_STYLENAME_STANDARD) );
//STRIP001      SfxItemSet& rSet = pStyle->GetItemSet();
//STRIP001      if ( nStrId==STR_PIVOT_STYLE_RESULT || nStrId==STR_PIVOT_STYLE_TITLE )
//STRIP001          rSet.Put( SvxWeightItem( WEIGHT_BOLD ) );
//STRIP001      if ( nStrId==STR_PIVOT_STYLE_CATEGORY || nStrId==STR_PIVOT_STYLE_TITLE )
//STRIP001          rSet.Put( SvxHorJustifyItem( SVX_HOR_JUSTIFY_LEFT ) );
//STRIP001  }
//STRIP001
//STRIP001  pDoc->ApplyStyleAreaTab( nCol1, nRow1, nCol2, nRow2, nTab, *pStyle );
//STRIP001 }

//STRIP001 void lcl_SetFrame( ScDocument* pDoc, USHORT nTab,
//STRIP001                  USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                  USHORT nWidth )
//STRIP001 {
//STRIP001  SvxBorderLine aLine;
//STRIP001  aLine.SetOutWidth(nWidth);
//STRIP001  SvxBoxItem aBox;
//STRIP001  aBox.SetLine(&aLine, BOX_LINE_LEFT);
//STRIP001  aBox.SetLine(&aLine, BOX_LINE_TOP);
//STRIP001  aBox.SetLine(&aLine, BOX_LINE_RIGHT);
//STRIP001  aBox.SetLine(&aLine, BOX_LINE_BOTTOM);
//STRIP001  SvxBoxInfoItem aBoxInfo;
//STRIP001  aBoxInfo.SetValid(VALID_HORI,FALSE);
//STRIP001  aBoxInfo.SetValid(VALID_VERT,FALSE);
//STRIP001  aBoxInfo.SetValid(VALID_DISTANCE,FALSE);
//STRIP001
//STRIP001  pDoc->ApplyFrameAreaTab( ScRange( nCol1, nRow1, nTab, nCol2, nRow2, nTab ), &aBox, &aBoxInfo );
//STRIP001 }

//STRIP001 void lcl_AttrArea( ScDocument* pDoc, USHORT nTab,
//STRIP001                  USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                  const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001  ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001  aPattern.GetItemSet().Put( rItem );
//STRIP001  pDoc->ApplyPatternAreaTab( nCol1,nRow1, nCol2,nRow2, nTab, aPattern );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void lcl_FillNumberFormats( UINT32*& rFormats, long& rCount,
//STRIP001                          const uno::Reference<sheet::XDataPilotMemberResults>& xLevRes,
//STRIP001                          const uno::Reference<container::XIndexAccess>& xDims )
//STRIP001 {
//STRIP001  if ( rFormats )
//STRIP001      return;                         // already set
//STRIP001
//STRIP001  //  xLevRes is from the data layout dimension
//STRIP001  //! use result sequence from ScDPOutLevelData!
//STRIP001
//STRIP001  uno::Sequence<sheet::MemberResult> aResult = xLevRes->getResults();
//STRIP001
//STRIP001  long nSize = aResult.getLength();
//STRIP001  if (nSize)
//STRIP001  {
//STRIP001      //  get names/formats for all data dimensions
//STRIP001      //! merge this with the loop to collect ScDPOutLevelData?
//STRIP001
//STRIP001      String aDataNames[SC_DPOUT_MAXLEVELS];
//STRIP001      UINT32 nDataFormats[SC_DPOUT_MAXLEVELS];
//STRIP001      long nDataCount = 0;
//STRIP001      BOOL bAnySet = FALSE;
//STRIP001
//STRIP001      long nDimCount = xDims->getCount();
//STRIP001      for (long nDim=0; nDim<nDimCount; nDim++)
//STRIP001      {
//STRIP001          uno::Reference<uno::XInterface> xDim =
//STRIP001                  ScUnoHelpFunctions::AnyToInterface( xDims->getByIndex(nDim) );
//STRIP001          uno::Reference<beans::XPropertySet> xDimProp( xDim, uno::UNO_QUERY );
//STRIP001          uno::Reference<container::XNamed> xDimName( xDim, uno::UNO_QUERY );
//STRIP001          if ( xDimProp.is() && xDimName.is() )
//STRIP001          {
//STRIP001              sheet::DataPilotFieldOrientation eDimOrient =
//STRIP001                  (sheet::DataPilotFieldOrientation) ScUnoHelpFunctions::GetEnumProperty(
//STRIP001                      xDimProp, rtl::OUString::createFromAscii(DP_PROP_ORIENTATION),
//STRIP001                      sheet::DataPilotFieldOrientation_HIDDEN );
//STRIP001              if ( eDimOrient == sheet::DataPilotFieldOrientation_DATA )
//STRIP001              {
//STRIP001                  aDataNames[nDataCount] = String( xDimName->getName() );
//STRIP001                  long nFormat = ScUnoHelpFunctions::GetLongProperty(
//STRIP001                                          xDimProp,
//STRIP001                                          rtl::OUString::createFromAscii(DP_PROP_NUMBERFORMAT) );
//STRIP001                  nDataFormats[nDataCount] = nFormat;
//STRIP001                  if ( nFormat != 0 )
//STRIP001                      bAnySet = TRUE;
//STRIP001                  ++nDataCount;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( bAnySet )      // forget everything if all formats are 0 (or no data dimensions)
//STRIP001      {
//STRIP001          const sheet::MemberResult* pArray = aResult.getConstArray();
//STRIP001
//STRIP001          String aName;
//STRIP001          UINT32* pNumFmt = new UINT32[nSize];
//STRIP001          if (nDataCount == 1)
//STRIP001          {
//STRIP001              //  only one data dimension -> use its numberformat everywhere
//STRIP001              long nFormat = nDataFormats[0];
//STRIP001              for (long nPos=0; nPos<nSize; nPos++)
//STRIP001                  pNumFmt[nPos] = nFormat;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              for (long nPos=0; nPos<nSize; nPos++)
//STRIP001              {
//STRIP001                  //  if CONTINUE bit is set, keep previous name
//STRIP001                  //! keep number format instead!
//STRIP001                  if ( !(pArray[nPos].Flags & sheet::MemberResultFlags::CONTINUE) )
//STRIP001                      aName = String( pArray[nPos].Name );
//STRIP001
//STRIP001                  UINT32 nFormat = 0;
//STRIP001                  for (long i=0; i<nDataCount; i++)
//STRIP001                      if (aName == aDataNames[i])         //! search more efficiently?
//STRIP001                      {
//STRIP001                          nFormat = nDataFormats[i];
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  pNumFmt[nPos] = nFormat;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          rFormats = pNumFmt;
//STRIP001          rCount = nSize;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_SortFields( ScDPOutLevelData* pFields, long nFieldCount )
//STRIP001 {
//STRIP001  for (long i=0; i+1<nFieldCount; i++)
//STRIP001  {
//STRIP001      for (long j=0; j+i+1<nFieldCount; j++)
//STRIP001          if ( pFields[j+1] < pFields[j] )
//STRIP001              pFields[j].Swap( pFields[j+1] );
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_MemberEmpty( const uno::Sequence<sheet::MemberResult>& rSeq )
//STRIP001 {
//STRIP001  //  used to skip levels that have no members
//STRIP001
//STRIP001  long nLen = rSeq.getLength();
//STRIP001  const sheet::MemberResult* pArray = rSeq.getConstArray();
//STRIP001  for (long i=0; i<nLen; i++)
//STRIP001      if (pArray[i].Flags & sheet::MemberResultFlags::HASMEMBER)
//STRIP001          return FALSE;
//STRIP001
//STRIP001  return TRUE;    // no member data -> empty
//STRIP001 }

ScDPOutput::ScDPOutput( ScDocument* pD, const uno::Reference<sheet::XDimensionsSupplier>& xSrc,
                                const ScAddress& rPos, BOOL bFilter ) :
    pDoc( pD ),
    xSource( xSrc ),
    aStartPos( rPos ),
    bDoFilter( bFilter ),
    bSizesValid( FALSE ),
    bSizeOverflow( FALSE ),
    bResultsError( FALSE ),
    pColNumFmt( NULL ),
    pRowNumFmt( NULL ),
    nColFmtCount( 0 ),
    nRowFmtCount( 0 )
{
    DBG_ASSERT(0, "STRIP"); //STRIP001 nTabStartCol = nTabStartRow = nMemberStartCol = nMemberStartRow =
//STRIP001      nDataStartCol = nDataStartRow = nTabEndCol = nTabEndRow = 0;
//STRIP001
//STRIP001  pColFields  = new ScDPOutLevelData[SC_DPOUT_MAXLEVELS];
//STRIP001  pRowFields  = new ScDPOutLevelData[SC_DPOUT_MAXLEVELS];
//STRIP001  pPageFields = new ScDPOutLevelData[SC_DPOUT_MAXLEVELS];
//STRIP001  nColFieldCount = 0;
//STRIP001  nRowFieldCount = 0;
//STRIP001  nPageFieldCount = 0;
//STRIP001
//STRIP001  uno::Reference<sheet::XDataPilotResults> xResult( xSource, uno::UNO_QUERY );
//STRIP001  if ( xSource.is() && xResult.is() )
//STRIP001  {
//STRIP001      //  get dimension results:
//STRIP001
//STRIP001      uno::Reference<container::XIndexAccess> xDims =
//STRIP001              new ScNameToIndexAccess( xSource->getDimensions() );
//STRIP001      long nDimCount = xDims->getCount();
//STRIP001      for (long nDim=0; nDim<nDimCount; nDim++)
//STRIP001      {
//STRIP001          uno::Reference<uno::XInterface> xDim =
//STRIP001                  ScUnoHelpFunctions::AnyToInterface( xDims->getByIndex(nDim) );
//STRIP001          uno::Reference<beans::XPropertySet> xDimProp( xDim, uno::UNO_QUERY );
//STRIP001          uno::Reference<sheet::XHierarchiesSupplier> xDimSupp( xDim, uno::UNO_QUERY );
//STRIP001          if ( xDimProp.is() && xDimSupp.is() )
//STRIP001          {
//STRIP001              sheet::DataPilotFieldOrientation eDimOrient =
//STRIP001                  (sheet::DataPilotFieldOrientation) ScUnoHelpFunctions::GetEnumProperty(
//STRIP001                      xDimProp, rtl::OUString::createFromAscii(DP_PROP_ORIENTATION),
//STRIP001                      sheet::DataPilotFieldOrientation_HIDDEN );
//STRIP001              long nDimPos = ScUnoHelpFunctions::GetLongProperty( xDimProp,
//STRIP001                      rtl::OUString::createFromAscii(DP_PROP_POSITION) );
//STRIP001              BOOL bIsDataLayout = ScUnoHelpFunctions::GetBoolProperty(
//STRIP001                                              xDimProp,
//STRIP001                                              rtl::OUString::createFromAscii(DP_PROP_ISDATALAYOUT) );
//STRIP001
//STRIP001              if ( eDimOrient != sheet::DataPilotFieldOrientation_HIDDEN )
//STRIP001              {
//STRIP001                  uno::Reference<container::XIndexAccess> xHiers =
//STRIP001                          new ScNameToIndexAccess( xDimSupp->getHierarchies() );
//STRIP001                  long nHierarchy = ScUnoHelpFunctions::GetLongProperty(
//STRIP001                                          xDimProp,
//STRIP001                                          rtl::OUString::createFromAscii(DP_PROP_USEDHIERARCHY) );
//STRIP001                  if ( nHierarchy >= xHiers->getCount() )
//STRIP001                      nHierarchy = 0;
//STRIP001
//STRIP001                  uno::Reference<uno::XInterface> xHier =
//STRIP001                          ScUnoHelpFunctions::AnyToInterface(
//STRIP001                                              xHiers->getByIndex(nHierarchy) );
//STRIP001                  uno::Reference<sheet::XLevelsSupplier> xHierSupp( xHier, uno::UNO_QUERY );
//STRIP001                  if ( xHierSupp.is() )
//STRIP001                  {
//STRIP001                      uno::Reference<container::XIndexAccess> xLevels =
//STRIP001                              new ScNameToIndexAccess( xHierSupp->getLevels() );
//STRIP001                      long nLevCount = xLevels->getCount();
//STRIP001                      for (long nLev=0; nLev<nLevCount; nLev++)
//STRIP001                      {
//STRIP001                          uno::Reference<uno::XInterface> xLevel =
//STRIP001                                      ScUnoHelpFunctions::AnyToInterface(
//STRIP001                                                          xLevels->getByIndex(nLev) );
//STRIP001                          uno::Reference<container::XNamed> xLevNam( xLevel, uno::UNO_QUERY );
//STRIP001                          uno::Reference<sheet::XDataPilotMemberResults> xLevRes(
//STRIP001                                  xLevel, uno::UNO_QUERY );
//STRIP001                          if ( xLevNam.is() && xLevRes.is() )
//STRIP001                          {
//STRIP001                              String aCaption = String(xLevNam->getName());   //! Caption...
//STRIP001                              switch ( eDimOrient )
//STRIP001                              {
//STRIP001                                  case sheet::DataPilotFieldOrientation_COLUMN:
//STRIP001                                      pColFields[nColFieldCount].nDim    = nDim;
//STRIP001                                      pColFields[nColFieldCount].nHier   = nHierarchy;
//STRIP001                                      pColFields[nColFieldCount].nLevel  = nLev;
//STRIP001                                      pColFields[nColFieldCount].nDimPos = nDimPos;
//STRIP001                                      pColFields[nColFieldCount].aResult = xLevRes->getResults();
//STRIP001                                      pColFields[nColFieldCount].aCaption= aCaption;
//STRIP001                                      if (!lcl_MemberEmpty(pColFields[nColFieldCount].aResult))
//STRIP001                                          ++nColFieldCount;
//STRIP001                                      break;
//STRIP001                                  case sheet::DataPilotFieldOrientation_ROW:
//STRIP001                                      pRowFields[nRowFieldCount].nDim    = nDim;
//STRIP001                                      pRowFields[nRowFieldCount].nHier   = nHierarchy;
//STRIP001                                      pRowFields[nRowFieldCount].nLevel  = nLev;
//STRIP001                                      pRowFields[nRowFieldCount].nDimPos = nDimPos;
//STRIP001                                      pRowFields[nRowFieldCount].aResult = xLevRes->getResults();
//STRIP001                                      pRowFields[nRowFieldCount].aCaption= aCaption;
//STRIP001                                      if (!lcl_MemberEmpty(pRowFields[nRowFieldCount].aResult))
//STRIP001                                          ++nRowFieldCount;
//STRIP001                                      break;
//STRIP001                                  case sheet::DataPilotFieldOrientation_PAGE:
//STRIP001                                      pPageFields[nPageFieldCount].nDim    = nDim;
//STRIP001                                      pPageFields[nPageFieldCount].nHier   = nHierarchy;
//STRIP001                                      pPageFields[nPageFieldCount].nLevel  = nLev;
//STRIP001                                      pPageFields[nPageFieldCount].nDimPos = nDimPos;
//STRIP001                                      pPageFields[nPageFieldCount].aResult = xLevRes->getResults();
//STRIP001                                      pPageFields[nPageFieldCount].aCaption= aCaption;
//STRIP001                                      if (!lcl_MemberEmpty(pPageFields[nPageFieldCount].aResult))
//STRIP001                                          ++nPageFieldCount;
//STRIP001                                      break;
//STRIP001                              }
//STRIP001
//STRIP001                              // get number formats from data dimensions
//STRIP001                              if ( bIsDataLayout )
//STRIP001                              {
//STRIP001                                  DBG_ASSERT( nLevCount == 1, "data layout: multiple levels?" );
//STRIP001                                  if ( eDimOrient == sheet::DataPilotFieldOrientation_COLUMN )
//STRIP001                                      lcl_FillNumberFormats( pColNumFmt, nColFmtCount, xLevRes, xDims );
//STRIP001                                  else if ( eDimOrient == sheet::DataPilotFieldOrientation_ROW )
//STRIP001                                      lcl_FillNumberFormats( pRowNumFmt, nRowFmtCount, xLevRes, xDims );
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      lcl_SortFields( pColFields, nColFieldCount );
//STRIP001      lcl_SortFields( pRowFields, nRowFieldCount );
//STRIP001      lcl_SortFields( pPageFields, nPageFieldCount );
//STRIP001
//STRIP001      //  get data results:
//STRIP001
//STRIP001      try
//STRIP001      {
//STRIP001          aData = xResult->getResults();
//STRIP001      }
//STRIP001      catch (uno::RuntimeException&)
//STRIP001      {
//STRIP001          bResultsError = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // get "DataDescription" property (may be missing in external sources)
//STRIP001
//STRIP001  uno::Reference<beans::XPropertySet> xSrcProp( xSource, uno::UNO_QUERY );
//STRIP001  if ( xSrcProp.is() )
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          uno::Any aAny = xSrcProp->getPropertyValue(
//STRIP001                  rtl::OUString::createFromAscii(DP_PROP_DATADESCR) );
//STRIP001          rtl::OUString aUStr;
//STRIP001          aAny >>= aUStr;
//STRIP001          aDataDescription = String( aUStr );
//STRIP001      }
//STRIP001      catch(uno::Exception&)
//STRIP001      {
//STRIP001      }
//STRIP001  }
}

ScDPOutput::~ScDPOutput()
{
    delete[] pColFields;
    delete[] pRowFields;
    delete[] pPageFields;

    delete[] pColNumFmt;
    delete[] pRowNumFmt;
}

/*N*/ void ScDPOutput::SetPosition( const ScAddress& rPos )
/*N*/ {
/*N*/   aStartPos = rPos;
/*N*/   bSizesValid = bSizeOverflow = FALSE;
/*N*/ }

//STRIP001 void ScDPOutput::DataCell( USHORT nCol, USHORT nRow, USHORT nTab, const sheet::DataResult& rData )
//STRIP001 {
//STRIP001  long nFlags = rData.Flags;
//STRIP001  if ( nFlags & sheet::DataResultFlags::ERROR )
//STRIP001  {
//STRIP001      pDoc->SetError( nCol, nRow, nTab, errNoValue );
//STRIP001  }
//STRIP001  else if ( nFlags & sheet::DataResultFlags::HASDATA )
//STRIP001  {
//STRIP001      pDoc->SetValue( nCol, nRow, nTab, rData.Value );
//STRIP001
//STRIP001      //  use number formats from source
//STRIP001
//STRIP001      DBG_ASSERT( bSizesValid, "DataCell: !bSizesValid" );
//STRIP001      UINT32 nFormat = 0;
//STRIP001      if ( pColNumFmt )
//STRIP001      {
//STRIP001          if ( nCol >= nDataStartCol )
//STRIP001          {
//STRIP001              long nIndex = nCol - nDataStartCol;
//STRIP001              if ( nIndex < nColFmtCount )
//STRIP001                  nFormat = pColNumFmt[nIndex];
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( pRowNumFmt )
//STRIP001      {
//STRIP001          if ( nRow >= nDataStartRow )
//STRIP001          {
//STRIP001              long nIndex = nRow - nDataStartRow;
//STRIP001              if ( nIndex < nRowFmtCount )
//STRIP001                  nFormat = pRowNumFmt[nIndex];
//STRIP001          }
//STRIP001      }
//STRIP001      if ( nFormat != 0 )
//STRIP001          pDoc->ApplyAttr( nCol, nRow, nTab, SfxUInt32Item( ATTR_VALUE_FORMAT, nFormat ) );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //pDoc->SetString( nCol, nRow, nTab, EMPTY_STRING );
//STRIP001  }
//STRIP001
//STRIP001  //  SubTotal formatting is controlled by headers
//STRIP001 }

//STRIP001 void ScDPOutput::HeaderCell( USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001                              const sheet::MemberResult& rData, BOOL bColHeader, long nLevel )
//STRIP001 {
//STRIP001  long nFlags = rData.Flags;
//STRIP001  if ( nFlags & sheet::MemberResultFlags::HASMEMBER )
//STRIP001  {
//STRIP001      pDoc->SetString( nCol, nRow, nTab, rData.Caption );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //pDoc->SetString( nCol, nRow, nTab, EMPTY_STRING );
//STRIP001  }
//STRIP001
//STRIP001  if ( nFlags & sheet::MemberResultFlags::SUBTOTAL )
//STRIP001  {
//STRIP001 //       SvxWeightItem aItem( WEIGHT_BOLD );     // weight is in the style
//STRIP001
//STRIP001      //! limit frames to horizontal or vertical?
//STRIP001      if (bColHeader)
//STRIP001      {
//STRIP001 //           lcl_AttrArea( pDoc,nTab, nCol,nMemberStartRow+(USHORT)nLevel, nCol,nTabEndRow, aItem );
//STRIP001          lcl_SetFrame( pDoc,nTab, nCol,nMemberStartRow+(USHORT)nLevel, nCol,nTabEndRow, 20 );
//STRIP001          lcl_SetStyleById( pDoc,nTab, nCol,nMemberStartRow+(USHORT)nLevel, nCol,nDataStartRow-1,
//STRIP001                                  STR_PIVOT_STYLE_TITLE );
//STRIP001          lcl_SetStyleById( pDoc,nTab, nCol,nDataStartRow, nCol,nTabEndRow,
//STRIP001                                  STR_PIVOT_STYLE_RESULT );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001 //           lcl_AttrArea( pDoc,nTab, nMemberStartCol+(USHORT)nLevel,nRow, nTabEndCol,nRow, aItem );
//STRIP001          lcl_SetFrame( pDoc,nTab, nMemberStartCol+(USHORT)nLevel,nRow, nTabEndCol,nRow, 20 );
//STRIP001          lcl_SetStyleById( pDoc,nTab, nMemberStartCol+(USHORT)nLevel,nRow, nDataStartCol-1,nRow,
//STRIP001                                  STR_PIVOT_STYLE_TITLE );
//STRIP001          lcl_SetStyleById( pDoc,nTab, nDataStartCol,nRow, nTabEndCol,nRow,
//STRIP001                                  STR_PIVOT_STYLE_RESULT );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDPOutput::FieldCell( USHORT nCol, USHORT nRow, USHORT nTab, const String& rCaption )
//STRIP001 {
//STRIP001  pDoc->SetString( nCol, nRow, nTab, rCaption );
//STRIP001  lcl_SetFrame( pDoc,nTab, nCol,nRow, nCol,nRow, 20 );
//STRIP001
//STRIP001  //  Button
//STRIP001  pDoc->ApplyAttr( nCol, nRow, nTab, ScMergeFlagAttr(SC_MF_BUTTON) );
//STRIP001
//STRIP001  lcl_SetStyleById( pDoc,nTab, nCol,nRow, nCol,nRow, STR_PIVOT_STYLE_FIELDNAME );
//STRIP001 }

//STRIP001 void lcl_DoFilterButton( ScDocument* pDoc, USHORT nCol, USHORT nRow, USHORT nTab )
//STRIP001 {
//STRIP001  pDoc->SetString( nCol, nRow, nTab, ScGlobal::GetRscString(STR_CELL_FILTER) );
//STRIP001  pDoc->ApplyAttr( nCol, nRow, nTab, ScMergeFlagAttr(SC_MF_BUTTON) );
//STRIP001 }

//STRIP001 void ScDPOutput::CalcSizes()
//STRIP001 {
//STRIP001  if (!bSizesValid)
//STRIP001  {
//STRIP001      //  get column size of data from first row
//STRIP001      //! allow different sizes (and clear following areas) ???
//STRIP001
//STRIP001      nRowCount = aData.getLength();
//STRIP001      const uno::Sequence<sheet::DataResult>* pRowAry = aData.getConstArray();
//STRIP001      nColCount = nRowCount ? ( pRowAry[0].getLength() ) : 0;
//STRIP001      nHeaderSize = 1;            // one row for field names
//STRIP001
//STRIP001      //  calculate output positions and sizes
//STRIP001
//STRIP001      long nPageSize = 0;     //! use page fields!
//STRIP001      if ( bDoFilter )
//STRIP001          nPageSize = 2;      //  filter button in page field row
//STRIP001
//STRIP001      if ( aStartPos.Col() + nRowFieldCount + nColCount - 1 > MAXCOL ||
//STRIP001           aStartPos.Row() + nPageSize + nHeaderSize + nColFieldCount + nRowCount > MAXROW )
//STRIP001      {
//STRIP001          bSizeOverflow = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      nTabStartCol = aStartPos.Col();
//STRIP001      nTabStartRow = aStartPos.Row() + (USHORT)nPageSize;         // below page fields
//STRIP001      nMemberStartCol = nTabStartCol;
//STRIP001      nMemberStartRow = nTabStartRow + (USHORT) nHeaderSize;
//STRIP001      nDataStartCol = nMemberStartCol + (USHORT)nRowFieldCount;
//STRIP001      nDataStartRow = nMemberStartRow + (USHORT)nColFieldCount;
//STRIP001      if ( nColCount > 0 )
//STRIP001          nTabEndCol = nDataStartCol + (USHORT)nColCount - 1;
//STRIP001      else
//STRIP001          nTabEndCol = nDataStartCol;     // single column will remain empty
//STRIP001      if ( nRowCount > 0 )
//STRIP001          nTabEndRow = nDataStartRow + (USHORT)nRowCount - 1;
//STRIP001      else
//STRIP001          nTabEndRow = nDataStartRow;     // single row will remain empty
//STRIP001      bSizesValid = TRUE;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDPOutput::Output()
//STRIP001 {
//STRIP001  long nField;
//STRIP001  USHORT nTab = aStartPos.Tab();
//STRIP001  const uno::Sequence<sheet::DataResult>* pRowAry = aData.getConstArray();
//STRIP001
//STRIP001  //  calculate output positions and sizes
//STRIP001
//STRIP001  CalcSizes();
//STRIP001  if ( bSizeOverflow || bResultsError )   // does output area exceed sheet limits?
//STRIP001      return;                             // nothing
//STRIP001
//STRIP001  //  clear whole (new) output area
//STRIP001  //! when modifying table, clear old area
//STRIP001  //! include IDF_OBJECTS ???
//STRIP001  pDoc->DeleteAreaTab( aStartPos.Col(), aStartPos.Row(), nTabEndCol, nTabEndRow, nTab, IDF_ALL );
//STRIP001
//STRIP001  if ( bDoFilter )
//STRIP001      lcl_DoFilterButton( pDoc, aStartPos.Col(), aStartPos.Row(), nTab );
//STRIP001
//STRIP001  //  data description
//STRIP001  //  (may get overwritten by first row field)
//STRIP001
//STRIP001  String aDesc = aDataDescription;
//STRIP001  if ( !aDesc.Len() )
//STRIP001  {
//STRIP001      //! use default string ("result") ?
//STRIP001  }
//STRIP001  pDoc->SetString( nTabStartCol, nTabStartRow, nTab, aDesc );
//STRIP001
//STRIP001  //  set STR_PIVOT_STYLE_INNER for whole data area (subtotals are overwritten)
//STRIP001
//STRIP001  if ( nDataStartRow > nTabStartRow )
//STRIP001      lcl_SetStyleById( pDoc, nTab, nTabStartCol, nTabStartRow, nTabEndCol, nDataStartRow-1,
//STRIP001                          STR_PIVOT_STYLE_TOP );
//STRIP001  lcl_SetStyleById( pDoc, nTab, nDataStartCol, nDataStartRow, nTabEndCol, nTabEndRow,
//STRIP001                      STR_PIVOT_STYLE_INNER );
//STRIP001
//STRIP001  //  output column headers:
//STRIP001
//STRIP001  for (nField=0; nField<nColFieldCount; nField++)
//STRIP001  {
//STRIP001      USHORT nHdrCol = nDataStartCol + (USHORT)nField;                //! check for overflow
//STRIP001      FieldCell( nHdrCol, nTabStartRow, nTab, pColFields[nField].aCaption );
//STRIP001
//STRIP001      USHORT nRowPos = nMemberStartRow + (USHORT)nField;              //! check for overflow
//STRIP001      const uno::Sequence<sheet::MemberResult> rSequence = pColFields[nField].aResult;
//STRIP001      const sheet::MemberResult* pArray = rSequence.getConstArray();
//STRIP001      long nThisColCount = rSequence.getLength();
//STRIP001      DBG_ASSERT( nThisColCount == nColCount, "count mismatch" );     //! ???
//STRIP001      for (long nCol=0; nCol<nThisColCount; nCol++)
//STRIP001      {
//STRIP001          USHORT nColPos = nDataStartCol + (USHORT)nCol;              //! check for overflow
//STRIP001          HeaderCell( nColPos, nRowPos, nTab, pArray[nCol], TRUE, nField );
//STRIP001          if ( ( pArray[nCol].Flags & sheet::MemberResultFlags::HASMEMBER ) &&
//STRIP001              !( pArray[nCol].Flags & sheet::MemberResultFlags::SUBTOTAL ) )
//STRIP001          {
//STRIP001              if ( nField+1 < nColFieldCount )
//STRIP001              {
//STRIP001                  long nEnd = nCol;
//STRIP001                  while ( nEnd+1 < nThisColCount && ( pArray[nEnd+1].Flags & sheet::MemberResultFlags::CONTINUE ) )
//STRIP001                      ++nEnd;
//STRIP001                  USHORT nEndColPos = nDataStartCol + (USHORT)nEnd;       //! check for overflow
//STRIP001                  lcl_SetFrame( pDoc,nTab, nColPos,nRowPos, nEndColPos,nRowPos, 20 );
//STRIP001                  lcl_SetFrame( pDoc,nTab, nColPos,nRowPos, nEndColPos,nTabEndRow, 20 );
//STRIP001
//STRIP001                  lcl_SetStyleById( pDoc, nTab, nColPos,nRowPos, nEndColPos,nDataStartRow-1, STR_PIVOT_STYLE_CATEGORY );
//STRIP001              }
//STRIP001              else
//STRIP001                  lcl_SetStyleById( pDoc, nTab, nColPos,nRowPos, nColPos,nDataStartRow-1, STR_PIVOT_STYLE_CATEGORY );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  output row headers:
//STRIP001
//STRIP001  for (nField=0; nField<nRowFieldCount; nField++)
//STRIP001  {
//STRIP001      USHORT nHdrCol = nTabStartCol + (USHORT)nField;                 //! check for overflow
//STRIP001      USHORT nHdrRow = nDataStartRow - 1;
//STRIP001      FieldCell( nHdrCol, nHdrRow, nTab, pRowFields[nField].aCaption );
//STRIP001
//STRIP001      USHORT nColPos = nMemberStartCol + (USHORT)nField;              //! check for overflow
//STRIP001      const uno::Sequence<sheet::MemberResult> rSequence = pRowFields[nField].aResult;
//STRIP001      const sheet::MemberResult* pArray = rSequence.getConstArray();
//STRIP001      long nThisRowCount = rSequence.getLength();
//STRIP001      DBG_ASSERT( nThisRowCount == nRowCount, "count mismatch" );     //! ???
//STRIP001      for (long nRow=0; nRow<nThisRowCount; nRow++)
//STRIP001      {
//STRIP001          USHORT nRowPos = nDataStartRow + (USHORT)nRow;              //! check for overflow
//STRIP001          HeaderCell( nColPos, nRowPos, nTab, pArray[nRow], FALSE, nField );
//STRIP001          if ( ( pArray[nRow].Flags & sheet::MemberResultFlags::HASMEMBER ) &&
//STRIP001              !( pArray[nRow].Flags & sheet::MemberResultFlags::SUBTOTAL ) )
//STRIP001          {
//STRIP001              if ( nField+1 < nRowFieldCount )
//STRIP001              {
//STRIP001                  long nEnd = nRow;
//STRIP001                  while ( nEnd+1 < nThisRowCount && ( pArray[nEnd+1].Flags & sheet::MemberResultFlags::CONTINUE ) )
//STRIP001                      ++nEnd;
//STRIP001                  USHORT nEndRowPos = nDataStartRow + (USHORT)nEnd;       //! check for overflow
//STRIP001                  lcl_SetFrame( pDoc,nTab, nColPos,nRowPos, nColPos,nEndRowPos, 20 );
//STRIP001                  lcl_SetFrame( pDoc,nTab, nColPos,nRowPos, nTabEndCol,nEndRowPos, 20 );
//STRIP001
//STRIP001                  lcl_SetStyleById( pDoc, nTab, nColPos,nRowPos, nDataStartCol-1,nEndRowPos, STR_PIVOT_STYLE_CATEGORY );
//STRIP001              }
//STRIP001              else
//STRIP001                  lcl_SetStyleById( pDoc, nTab, nColPos,nRowPos, nDataStartCol-1,nRowPos, STR_PIVOT_STYLE_CATEGORY );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  output data results:
//STRIP001
//STRIP001  for (long nRow=0; nRow<nRowCount; nRow++)
//STRIP001  {
//STRIP001      USHORT nRowPos = nDataStartRow + (USHORT)nRow;                  //! check for overflow
//STRIP001      const sheet::DataResult* pColAry = pRowAry[nRow].getConstArray();
//STRIP001      long nThisColCount = pRowAry[nRow].getLength();
//STRIP001      DBG_ASSERT( nThisColCount == nColCount, "count mismatch" );     //! ???
//STRIP001      for (long nCol=0; nCol<nThisColCount; nCol++)
//STRIP001      {
//STRIP001          USHORT nColPos = nDataStartCol + (USHORT)nCol;              //! check for overflow
//STRIP001          DataCell( nColPos, nRowPos, nTab, pColAry[nCol] );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  frame around the whole table
//STRIP001
//STRIP001  lcl_SetFrame( pDoc,nTab, nDataStartCol,nDataStartRow, nTabEndCol,nTabEndRow, 20 );
//STRIP001  if ( nDataStartCol > nMemberStartCol )
//STRIP001      lcl_SetFrame( pDoc,nTab, nMemberStartCol,nDataStartRow, nDataStartCol-1,nTabEndRow, 20 );
//STRIP001  if ( nDataStartRow > nMemberStartRow )
//STRIP001      lcl_SetFrame( pDoc,nTab, nDataStartCol,nMemberStartRow, nTabEndCol,nDataStartRow-1, 20 );
//STRIP001
//STRIP001  lcl_SetFrame( pDoc,nTab, nTabStartCol,nTabStartRow, nTabEndCol,nTabEndRow, 40 );
//STRIP001 }

//STRIP001 ScRange ScDPOutput::GetOutputRange()
//STRIP001 {
//STRIP001  CalcSizes();
//STRIP001
//STRIP001  USHORT nTab = aStartPos.Tab();
//STRIP001  return ScRange( aStartPos.Col(), aStartPos.Row(), nTab, nTabEndCol, nTabEndRow, nTab);
//STRIP001 }

//STRIP001 BOOL ScDPOutput::HasError()
//STRIP001 {
//STRIP001  CalcSizes();
//STRIP001
//STRIP001  return bSizeOverflow || bResultsError;
//STRIP001 }

//
//      Methods to find specific parts of the table
//

//STRIP001 void ScDPOutput::GetPositionData( ScDPPositionData& rData, const ScAddress& rPos )
//STRIP001 {
//STRIP001  //! preset rData to "invalid" ?
//STRIP001
//STRIP001  USHORT nCol = rPos.Col();
//STRIP001  USHORT nRow = rPos.Row();
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001  if ( nTab != aStartPos.Tab() )
//STRIP001      return;                                     // wrong sheet
//STRIP001
//STRIP001  //  calculate output positions and sizes
//STRIP001
//STRIP001  CalcSizes();
//STRIP001
//STRIP001  //  test for column field
//STRIP001
//STRIP001  if ( nRow >= nMemberStartRow && nRow < nMemberStartRow + nColFieldCount )
//STRIP001  {
//STRIP001      long nField = nRow - nMemberStartRow;
//STRIP001      const uno::Sequence<sheet::MemberResult> rSequence = pColFields[nField].aResult;
//STRIP001      const sheet::MemberResult* pArray = rSequence.getConstArray();
//STRIP001      long nThisColCount = rSequence.getLength();
//STRIP001
//STRIP001      if ( nCol >= nDataStartCol && nCol < nDataStartCol + nThisColCount )
//STRIP001      {
//STRIP001          long nItem = nCol - nDataStartCol;
//STRIP001          //  get origin of "continue" fields
//STRIP001          while ( nItem > 0 && ( pArray[nItem].Flags & sheet::MemberResultFlags::CONTINUE ) )
//STRIP001              --nItem;
//STRIP001          rData.aMemberName = String(pArray[nItem].Name);
//STRIP001          rData.nFlags      = pArray[nItem].Flags;
//STRIP001          rData.nDimension  = pColFields[nField].nDim;
//STRIP001          rData.nHierarchy  = pColFields[nField].nHier;
//STRIP001          rData.nLevel      = pColFields[nField].nLevel;
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  test for row field
//STRIP001
//STRIP001  if ( nCol >= nMemberStartCol && nCol < nMemberStartCol + nRowFieldCount )
//STRIP001  {
//STRIP001      long nField = nCol - nMemberStartCol;
//STRIP001      const uno::Sequence<sheet::MemberResult> rSequence = pRowFields[nField].aResult;
//STRIP001      const sheet::MemberResult* pArray = rSequence.getConstArray();
//STRIP001      long nThisRowCount = rSequence.getLength();
//STRIP001
//STRIP001      if ( nRow >= nDataStartRow && nRow < nDataStartRow + nThisRowCount )
//STRIP001      {
//STRIP001          long nItem = nRow - nDataStartRow;
//STRIP001          //  get origin of "continue" fields
//STRIP001          while ( nItem > 0 && ( pArray[nItem].Flags & sheet::MemberResultFlags::CONTINUE ) )
//STRIP001              --nItem;
//STRIP001          rData.aMemberName = String(pArray[nItem].Name);
//STRIP001          rData.nFlags      = pArray[nItem].Flags;
//STRIP001          rData.nDimension  = pRowFields[nField].nDim;
//STRIP001          rData.nHierarchy  = pRowFields[nField].nHier;
//STRIP001          rData.nLevel      = pRowFields[nField].nLevel;
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ScDPOutput::IsFilterButton( const ScAddress& rPos )
//STRIP001 {
//STRIP001  USHORT nCol = rPos.Col();
//STRIP001  USHORT nRow = rPos.Row();
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001  if ( nTab != aStartPos.Tab() || !bDoFilter )
//STRIP001      return FALSE;                               // wrong sheet or no button at all
//STRIP001
//STRIP001  //  filter button is at top left
//STRIP001  return ( nCol == aStartPos.Col() && nRow == aStartPos.Row() );
//STRIP001 }

//STRIP001 long ScDPOutput::GetHeaderDim( const ScAddress& rPos )
//STRIP001 {
//STRIP001  USHORT nCol = rPos.Col();
//STRIP001  USHORT nRow = rPos.Row();
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001  if ( nTab != aStartPos.Tab() )
//STRIP001      return -1;                                      // wrong sheet
//STRIP001
//STRIP001  //  calculate output positions and sizes
//STRIP001
//STRIP001  CalcSizes();
//STRIP001
//STRIP001  //  test for column header
//STRIP001
//STRIP001  if ( nRow == nTabStartRow && nCol >= nDataStartCol && nCol < nDataStartCol + nColFieldCount )
//STRIP001  {
//STRIP001      long nField = nCol - nDataStartCol;
//STRIP001      return pColFields[nField].nDim;
//STRIP001  }
//STRIP001
//STRIP001  //  test for row header
//STRIP001
//STRIP001  if ( nRow+1 == nDataStartRow && nCol >= nTabStartCol == nCol < nTabStartCol + nRowFieldCount )
//STRIP001  {
//STRIP001      long nField = nCol - nTabStartCol;
//STRIP001      return pRowFields[nField].nDim;
//STRIP001  }
//STRIP001
//STRIP001  //! page fields
//STRIP001  //! single data field (?)
//STRIP001
//STRIP001  return -1;      // invalid
//STRIP001 }

//STRIP001 BOOL ScDPOutput::GetHeaderDrag( const ScAddress& rPos, BOOL bMouseLeft, BOOL bMouseTop,
//STRIP001                              long nDragDim,
//STRIP001                              Rectangle& rPosRect, USHORT& rOrient, long& rDimPos )
//STRIP001 {
//STRIP001  //  Rectangle instead of ScRange for rPosRect to allow for negative values
//STRIP001
//STRIP001  USHORT nCol = rPos.Col();
//STRIP001  USHORT nRow = rPos.Row();
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001  if ( nTab != aStartPos.Tab() )
//STRIP001      return FALSE;                                       // wrong sheet
//STRIP001
//STRIP001  //  calculate output positions and sizes
//STRIP001
//STRIP001  CalcSizes();
//STRIP001
//STRIP001  //  test for column header
//STRIP001
//STRIP001  if ( nCol >= nDataStartCol && nCol <= nTabEndCol &&
//STRIP001          nRow + 1 >= nMemberStartRow && nRow < nMemberStartRow + nColFieldCount )
//STRIP001  {
//STRIP001      long nField = nRow - nMemberStartRow;
//STRIP001      if (nField < 0)
//STRIP001      {
//STRIP001          nField = 0;
//STRIP001          bMouseTop = TRUE;
//STRIP001      }
//STRIP001      //! find start of dimension
//STRIP001
//STRIP001      rPosRect = Rectangle( nDataStartCol, nMemberStartRow + nField,
//STRIP001                            nTabEndCol, nMemberStartRow + nField -1 );
//STRIP001
//STRIP001      BOOL bFound = FALSE;            // is this within the same orientation?
//STRIP001      BOOL bBeforeDrag = FALSE;
//STRIP001      BOOL bAfterDrag = FALSE;
//STRIP001      for (long nPos=0; nPos<nColFieldCount && !bFound; nPos++)
//STRIP001      {
//STRIP001          if (pColFields[nPos].nDim == nDragDim)
//STRIP001          {
//STRIP001              bFound = TRUE;
//STRIP001              if ( nField < nPos )
//STRIP001                  bBeforeDrag = TRUE;
//STRIP001              else if ( nField > nPos )
//STRIP001                  bAfterDrag = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( bFound )
//STRIP001      {
//STRIP001          if (!bBeforeDrag)
//STRIP001          {
//STRIP001              ++rPosRect.Bottom();
//STRIP001              if (bAfterDrag)
//STRIP001                  ++rPosRect.Top();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if ( !bMouseTop )
//STRIP001          {
//STRIP001              ++rPosRect.Top();
//STRIP001              ++rPosRect.Bottom();
//STRIP001              ++nField;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      rOrient = sheet::DataPilotFieldOrientation_COLUMN;
//STRIP001      rDimPos = nField;                       //!...
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //  test for row header
//STRIP001
//STRIP001  //  special case if no row fields
//STRIP001  BOOL bSpecial = ( nRow+1 >= nDataStartRow && nRow <= nTabEndRow &&
//STRIP001                      nRowFieldCount == 0 && nCol == nTabStartCol && bMouseLeft );
//STRIP001
//STRIP001  if ( bSpecial || ( nRow+1 >= nDataStartRow && nRow <= nTabEndRow &&
//STRIP001                      nCol + 1 >= nTabStartCol && nCol < nTabStartCol + nRowFieldCount ) )
//STRIP001  {
//STRIP001      long nField = nCol - nTabStartCol;
//STRIP001      //! find start of dimension
//STRIP001
//STRIP001      rPosRect = Rectangle( nTabStartCol + nField, nDataStartRow - 1,
//STRIP001                            nTabStartCol + nField - 1, nTabEndRow );
//STRIP001
//STRIP001      BOOL bFound = FALSE;            // is this within the same orientation?
//STRIP001      BOOL bBeforeDrag = FALSE;
//STRIP001      BOOL bAfterDrag = FALSE;
//STRIP001      for (long nPos=0; nPos<nRowFieldCount && !bFound; nPos++)
//STRIP001      {
//STRIP001          if (pRowFields[nPos].nDim == nDragDim)
//STRIP001          {
//STRIP001              bFound = TRUE;
//STRIP001              if ( nField < nPos )
//STRIP001                  bBeforeDrag = TRUE;
//STRIP001              else if ( nField > nPos )
//STRIP001                  bAfterDrag = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( bFound )
//STRIP001      {
//STRIP001          if (!bBeforeDrag)
//STRIP001          {
//STRIP001              ++rPosRect.Right();
//STRIP001              if (bAfterDrag)
//STRIP001                  ++rPosRect.Left();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if ( !bMouseLeft )
//STRIP001          {
//STRIP001              ++rPosRect.Left();
//STRIP001              ++rPosRect.Right();
//STRIP001              ++nField;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      rOrient = sheet::DataPilotFieldOrientation_ROW;
//STRIP001      rDimPos = nField;                       //!...
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }



