/*************************************************************************
 *
 *  $RCSfile: sc_dptabdat.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:03 $
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
#include <tools/date.hxx>
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#include "dptabdat.hxx"
#include "global.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

//STRIP001 BOOL ScDPItemData::IsCaseInsEqual( const ScDPItemData& r ) const
//STRIP001 {
//STRIP001  //! ApproxEqual ???
//STRIP001     //! pass Transliteration?
//STRIP001  //! inline?
//STRIP001  return bHasValue ? ( r.bHasValue && fValue == r.fValue ) :
//STRIP001                     ( !r.bHasValue &&
//STRIP001                         ScGlobal::pTransliteration->isEqual( aString, r.aString ) );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ScDPTableIteratorParam::ScDPTableIteratorParam(
//STRIP001                          long nCCount, const long* pC, ScDPItemData* pCDat,
//STRIP001                          long nRCount, const long* pR, ScDPItemData* pRDat,
//STRIP001                          long nDCount, const long* pD, ScDPValueData* pV ) :
//STRIP001  nColCount( (USHORT)nCCount ),
//STRIP001  pCols    ( pC ),
//STRIP001  pColData ( pCDat ),
//STRIP001  nRowCount( (USHORT)nRCount ),
//STRIP001  pRows    ( pR ),
//STRIP001  pRowData ( pRDat ),
//STRIP001  nDatCount( (USHORT)nDCount ),
//STRIP001  pDats    ( pD ),
//STRIP001  pValues  ( pV )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ ScDPTableData::ScDPTableData()
/*N*/ {
/*N*/   nLastDateVal = nLastHier = nLastLevel = nLastRet = -1;      // invalid
/*N*/
/*N*/   //! reset before new calculation (in case the base date is changed)
/*N*/ }

/*N*/ ScDPTableData::~ScDPTableData()
/*N*/ {
/*N*/ }

//STRIP001 long ScDPTableData::GetDatePart( long nDateVal, long nHierarchy, long nLevel )
//STRIP001 {
//STRIP001  if ( nDateVal == nLastDateVal && nHierarchy == nLastHier && nLevel == nLastLevel )
//STRIP001      return nLastRet;
//STRIP001
//STRIP001  Date aDate( 30,12,1899 );                   //! get from source data (and cache here)
//STRIP001  aDate += nDateVal;
//STRIP001
//STRIP001  long nRet = 0;
//STRIP001  switch (nHierarchy)
//STRIP001  {
//STRIP001      case SC_DAPI_HIERARCHY_QUARTER:
//STRIP001          switch (nLevel)
//STRIP001          {
//STRIP001              case 0: nRet = aDate.GetYear();                 break;
//STRIP001              case 1: nRet = (aDate.GetMonth()-1) / 3 + 1;    break;
//STRIP001              case 2: nRet = aDate.GetMonth();                break;
//STRIP001              case 3: nRet = aDate.GetDay();                  break;
//STRIP001              default:
//STRIP001                  DBG_ERROR("GetDatePart: wrong level");
//STRIP001          }
//STRIP001          break;
//STRIP001      case SC_DAPI_HIERARCHY_WEEK:
//STRIP001          switch (nLevel)
//STRIP001          {
//STRIP001              //! use settings for different definitions
//STRIP001              case 0: nRet = aDate.GetYear();                 break;      //!...
//STRIP001              case 1: nRet = aDate.GetWeekOfYear();           break;
//STRIP001              case 2: nRet = (long)aDate.GetDayOfWeek();      break;
//STRIP001              default:
//STRIP001                  DBG_ERROR("GetDatePart: wrong level");
//STRIP001          }
//STRIP001          break;
//STRIP001      default:
//STRIP001          DBG_ERROR("GetDatePart: wrong hierarchy");
//STRIP001  }
//STRIP001
//STRIP001  nLastDateVal = nDateVal;
//STRIP001  nLastHier    = nHierarchy;
//STRIP001  nLastLevel   = nLevel;
//STRIP001  nLastRet     = nRet;
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 UINT32 ScDPTableData::GetNumberFormat(long nDim)
//STRIP001 {
//STRIP001  return 0;           // default format
//STRIP001 }

// -----------------------------------------------------------------------




}
