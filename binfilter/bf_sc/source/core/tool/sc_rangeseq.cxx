/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_rangeseq.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:49:55 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <svtools/zforlist.hxx>
#include <rtl/math.hxx>
#include <tools/debug.hxx>


#include "rangeseq.hxx"
#include "document.hxx"
#include "scmatrix.hxx"
#include "cell.hxx"
namespace binfilter {

using namespace ::com::sun::star;

//------------------------------------------------------------------------

/*N*/ long lcl_DoubleToLong( double fVal )
/*N*/ {
/*N*/   double fInt = (fVal >= 0.0) ? ::rtl::math::approxFloor( fVal ) :
/*N*/                                 ::rtl::math::approxCeil( fVal );
/*N*/   if ( fInt >= LONG_MIN && fInt <= LONG_MAX )
/*N*/       return (long)fInt;
/*N*/   else
/*N*/       return 0;       // out of range
/*N*/ }

/*N*/ BOOL ScRangeToSequence::FillLongArray( uno::Any& rAny, ScDocument* pDoc, const ScRange& rRange )
/*N*/ {
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   long nColCount = rRange.aEnd.Col() + 1 - rRange.aStart.Col();
/*N*/   long nRowCount = rRange.aEnd.Row() + 1 - rRange.aStart.Row();
/*N*/
/*N*/   uno::Sequence< uno::Sequence<INT32> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<INT32>* pRowAry = aRowSeq.getArray();
/*N*/   for (long nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<INT32> aColSeq( nColCount );
/*N*/       INT32* pColAry = aColSeq.getArray();
/*N*/       for (long nCol = 0; nCol < nColCount; nCol++)
/*N*/           pColAry[nCol] = lcl_DoubleToLong( pDoc->GetValue(
/*N*/               ScAddress( (USHORT)(nStartCol+nCol), (USHORT)(nStartRow+nRow), nTab ) ) );
/*N*/
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;        //! check for errors
/*N*/ }


/*N*/ BOOL ScRangeToSequence::FillLongArray( uno::Any& rAny, const ScMatrix* pMatrix )
/*N*/ {
/*N*/   if (!pMatrix)
/*N*/       return FALSE;
/*N*/
/*N*/   USHORT nColCount, nRowCount;
/*N*/   pMatrix->GetDimensions( nColCount, nRowCount );
/*N*/
/*N*/   uno::Sequence< uno::Sequence<INT32> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<INT32>* pRowAry = aRowSeq.getArray();
/*N*/   for (USHORT nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<INT32> aColSeq( nColCount );
/*N*/       INT32* pColAry = aColSeq.getArray();
/*N*/       for (USHORT nCol = 0; nCol < nColCount; nCol++)
/*N*/           if ( pMatrix->IsString( nCol, nRow ) )
/*N*/               pColAry[nCol] = 0;
/*N*/           else
/*N*/               pColAry[nCol] = lcl_DoubleToLong( pMatrix->GetDouble( nCol, nRow ) );
/*N*/
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScRangeToSequence::FillDoubleArray( uno::Any& rAny, ScDocument* pDoc, const ScRange& rRange )
/*N*/ {
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   long nColCount = rRange.aEnd.Col() + 1 - rRange.aStart.Col();
/*N*/   long nRowCount = rRange.aEnd.Row() + 1 - rRange.aStart.Row();
/*N*/
/*N*/   uno::Sequence< uno::Sequence<double> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<double>* pRowAry = aRowSeq.getArray();
/*N*/   for (long nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<double> aColSeq( nColCount );
/*N*/       double* pColAry = aColSeq.getArray();
/*N*/       for (long nCol = 0; nCol < nColCount; nCol++)
/*N*/           pColAry[nCol] = pDoc->GetValue(
/*N*/               ScAddress( (USHORT)(nStartCol+nCol), (USHORT)(nStartRow+nRow), nTab ) );
/*N*/
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;        //! check for errors
/*N*/ }


/*N*/ BOOL ScRangeToSequence::FillDoubleArray( uno::Any& rAny, const ScMatrix* pMatrix )
/*N*/ {
/*N*/   if (!pMatrix)
/*N*/       return FALSE;
/*N*/
/*N*/   USHORT nColCount, nRowCount;
/*N*/   pMatrix->GetDimensions( nColCount, nRowCount );
/*N*/
/*N*/   uno::Sequence< uno::Sequence<double> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<double>* pRowAry = aRowSeq.getArray();
/*N*/   for (USHORT nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<double> aColSeq( nColCount );
/*N*/       double* pColAry = aColSeq.getArray();
/*N*/       for (USHORT nCol = 0; nCol < nColCount; nCol++)
/*N*/           if ( pMatrix->IsString( nCol, nRow ) )
/*N*/               pColAry[nCol] = 0.0;
/*N*/           else
/*N*/               pColAry[nCol] = pMatrix->GetDouble( nCol, nRow );
/*N*/
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScRangeToSequence::FillStringArray( uno::Any& rAny, ScDocument* pDoc, const ScRange& rRange )
/*N*/ {
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   long nColCount = rRange.aEnd.Col() + 1 - rRange.aStart.Col();
/*N*/   long nRowCount = rRange.aEnd.Row() + 1 - rRange.aStart.Row();
/*N*/
/*N*/   String aDocStr;
/*N*/
/*N*/   uno::Sequence< uno::Sequence<rtl::OUString> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<rtl::OUString>* pRowAry = aRowSeq.getArray();
/*N*/   for (long nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<rtl::OUString> aColSeq( nColCount );
/*N*/       ::rtl::OUString* pColAry = aColSeq.getArray();
/*N*/       for (long nCol = 0; nCol < nColCount; nCol++)
/*N*/       {
/*N*/           pDoc->GetString( (USHORT)(nStartCol+nCol), (USHORT)(nStartRow+nRow), nTab, aDocStr );
/*N*/           pColAry[nCol] = ::rtl::OUString( aDocStr );
/*N*/       }
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;        //! check for errors
/*N*/ }


/*N*/ BOOL ScRangeToSequence::FillStringArray( uno::Any& rAny, const ScMatrix* pMatrix,
/*N*/                                           SvNumberFormatter* pFormatter )
/*N*/ {
/*N*/   if (!pMatrix)
/*N*/       return FALSE;
/*N*/
/*N*/   USHORT nColCount, nRowCount;
/*N*/   pMatrix->GetDimensions( nColCount, nRowCount );
/*N*/
/*N*/   uno::Sequence< uno::Sequence<rtl::OUString> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<rtl::OUString>* pRowAry = aRowSeq.getArray();
/*N*/   for (USHORT nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<rtl::OUString> aColSeq( nColCount );
/*N*/       ::rtl::OUString* pColAry = aColSeq.getArray();
/*N*/       for (USHORT nCol = 0; nCol < nColCount; nCol++)
/*N*/       {
/*N*/           String aStr;
/*N*/           if ( pMatrix->IsString( nCol, nRow ) )
/*N*/           {
/*N*/               if ( !pMatrix->IsEmpty( nCol, nRow ) )
/*N*/                   aStr = pMatrix->GetString( nCol, nRow );
/*N*/           }
/*N*/           else if ( pFormatter )
/*N*/           {
/*N*/               double fVal = pMatrix->GetDouble( nCol, nRow );
/*N*/               Color* pColor;
/*N*/               pFormatter->GetOutputString( fVal, 0, aStr, &pColor );
/*N*/           }
/*N*/           pColAry[nCol] = ::rtl::OUString( aStr );
/*N*/       }
/*N*/
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ double lcl_GetValueFromCell( ScBaseCell& rCell )
/*N*/ {
/*N*/   //! ScBaseCell member function?
/*N*/
/*N*/   CellType eType = rCell.GetCellType();
/*N*/   if ( eType == CELLTYPE_VALUE )
/*N*/       return ((ScValueCell&)rCell).GetValue();
/*N*/   else if ( eType == CELLTYPE_FORMULA )
/*N*/       return ((ScFormulaCell&)rCell).GetValue();      // called only if result is value
/*N*/
/*N*/   DBG_ERROR( "GetValueFromCell: wrong type" );
/*N*/   return 0;
/*N*/ }

/*N*/ BOOL ScRangeToSequence::FillMixedArray( uno::Any& rAny, ScDocument* pDoc, const ScRange& rRange,
/*N*/                                       BOOL bAllowNV )
/*N*/ {
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   long nColCount = rRange.aEnd.Col() + 1 - rRange.aStart.Col();
/*N*/   long nRowCount = rRange.aEnd.Row() + 1 - rRange.aStart.Row();
/*N*/
/*N*/   String aDocStr;
/*N*/   BOOL bHasErrors = FALSE;
/*N*/
/*N*/   uno::Sequence< uno::Sequence<uno::Any> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<uno::Any>* pRowAry = aRowSeq.getArray();
/*N*/   for (long nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<uno::Any> aColSeq( nColCount );
/*N*/       uno::Any* pColAry = aColSeq.getArray();
/*N*/       for (long nCol = 0; nCol < nColCount; nCol++)
/*N*/       {
/*N*/           uno::Any& rElement = pColAry[nCol];
/*N*/
/*N*/           ScAddress aPos( (USHORT)(nStartCol+nCol), (USHORT)(nStartRow+nRow), nTab );
/*N*/           ScBaseCell* pCell = pDoc->GetCell( aPos );
/*N*/           if ( pCell )
/*N*/           {
/*N*/               if ( pCell->GetCellType() == CELLTYPE_FORMULA &&
/*N*/                       ((ScFormulaCell*)pCell)->GetErrCode() != 0 )
/*N*/               {
/*N*/                   // if NV is allowed, leave empty for errors
/*N*/                   bHasErrors = TRUE;
/*N*/               }
/*N*/               else if ( pCell->HasValueData() )
/*N*/                   rElement <<= (double) lcl_GetValueFromCell( *pCell );
/*N*/               else
/*N*/                   rElement <<= ::rtl::OUString( pCell->GetStringData() );
/*N*/           }
/*N*/           else
/*N*/               rElement <<= ::rtl::OUString();     // empty: empty string
/*N*/       }
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return bAllowNV || !bHasErrors;
/*N*/ }


/*N*/ BOOL ScRangeToSequence::FillMixedArray( uno::Any& rAny, const ScMatrix* pMatrix )
/*N*/ {
/*N*/   if (!pMatrix)
/*N*/       return FALSE;
/*N*/
/*N*/   USHORT nColCount, nRowCount;
/*N*/   pMatrix->GetDimensions( nColCount, nRowCount );
/*N*/
/*N*/   uno::Sequence< uno::Sequence<uno::Any> > aRowSeq( nRowCount );
/*N*/   uno::Sequence<uno::Any>* pRowAry = aRowSeq.getArray();
/*N*/   for (USHORT nRow = 0; nRow < nRowCount; nRow++)
/*N*/   {
/*N*/       uno::Sequence<uno::Any> aColSeq( nColCount );
/*N*/       uno::Any* pColAry = aColSeq.getArray();
/*N*/       for (USHORT nCol = 0; nCol < nColCount; nCol++)
/*N*/       {
/*N*/           if ( pMatrix->IsString( nCol, nRow ) )
/*N*/           {
/*N*/               String aStr;
/*N*/               if ( !pMatrix->IsEmpty( nCol, nRow ) )
/*N*/                   aStr = pMatrix->GetString( nCol, nRow );
/*N*/               pColAry[nCol] <<= ::rtl::OUString( aStr );
/*N*/           }
/*N*/           else
/*N*/               pColAry[nCol] <<= (double) pMatrix->GetDouble( nCol, nRow );
/*N*/       }
/*N*/
/*N*/       pRowAry[nRow] = aColSeq;
/*N*/   }
/*N*/
/*N*/   rAny <<= aRowSeq;
/*N*/   return TRUE;
/*N*/ }


//------------------------------------------------------------------------


//------------------------------------------------------------------------

}
