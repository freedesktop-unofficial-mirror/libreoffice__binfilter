/*************************************************************************
 *
 *  $RCSfile: sc_subtotal.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:22:47 $
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
// INCLUDE ---------------------------------------------------------------

#ifdef RS6000

#include <fptrap.h>
#include <fpxcp.h>

#elif defined ( MAC )

#include <MAC_START.h>
#include <fp.h>
#include <MAC_END.h>

#endif

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif


#include <float.h>
#include <math.h>
#ifdef SOLARIS
#include <ieeefp.h>
#endif
#include <signal.h>

#include "subtotal.hxx"
#include "interpre.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

jmp_buf SubTotal::aGlobalJumpBuf;

// -----------------------------------------------------------------------

/*N*/ SubTotal::SubTotal()
/*N*/ {
/*N*/   nIndex = 0;             //! test fuer Pivot
/*N*/
/*N*/   nCount     = 0;
/*N*/   nCount2    = 0;
/*N*/   nSum       = 0.0;
/*N*/   nSumSqr    = 0.0;
/*N*/   nMax       = -MAXDOUBLE;
/*N*/   nMin       = MAXDOUBLE;
/*N*/   nProduct   = 1.0;
/*N*/   bSumOk     = TRUE;
/*N*/   bSumSqrOk  = TRUE;
/*N*/   bProductOk = TRUE;
/*N*/ }


/*N*/ SubTotal::~SubTotal()
/*N*/ {
/*N*/ }


//STRIP001 void SubTotal::UpdateNoVal()
//STRIP001 {
//STRIP001  nCount++;
//STRIP001 }


/*N*/ void SubTotal::Update( double nVal )
/*N*/ {
/*N*/   SAL_MATH_FPEXCEPTIONS_OFF();
/*N*/     nCount++;
/*N*/     nCount2++;
/*N*/     if (nVal > nMax) nMax = nVal;
/*N*/     if (nVal < nMin) nMin = nVal;
/*N*/     nProgress = 0;
/*N*/     if (bSumOk) nSum += nVal;
/*N*/     nProgress = 1;
/*N*/     if (bProductOk) nProduct *= nVal;
/*N*/     nProgress = 2;
/*N*/     if (bSumSqrOk) nSumSqr += nVal*nVal;
/*N*/   if (!::rtl::math::isFinite(nSum))
/*N*/       bSumOk = FALSE;
/*N*/   if (!::rtl::math::isFinite(nProduct))
/*N*/       bProductOk = FALSE;
/*N*/   if (!::rtl::math::isFinite(nSumSqr))
/*N*/       bSumSqrOk = FALSE;
/*N*/ }


//STRIP001 void SubTotal::Update( const SubTotal& rVal )
//STRIP001 {
//STRIP001  SAL_MATH_FPEXCEPTIONS_OFF();
//STRIP001     nCount   += rVal.nCount;
//STRIP001     nCount2  += rVal.nCount2;
//STRIP001     if (rVal.nMax > nMax) nMax = rVal.nMax;
//STRIP001     if (rVal.nMin < nMin) nMin = rVal.nMin;
//STRIP001     nProgress = 0;
//STRIP001     if (rVal.bSumOk && bSumOk)
//STRIP001         nSum += rVal.nSum;
//STRIP001     else
//STRIP001         bSumOk = FALSE;
//STRIP001     nProgress = 1;
//STRIP001     if (rVal.bProductOk && bProductOk)
//STRIP001         nProduct *= rVal.nProduct;
//STRIP001     else
//STRIP001         bProductOk = FALSE;
//STRIP001     nProgress = 2;
//STRIP001     if (rVal.bSumSqrOk && bSumSqrOk)
//STRIP001         nSumSqr  += rVal.nSumSqr;
//STRIP001     else
//STRIP001         bSumSqrOk = FALSE;
//STRIP001  if (!::rtl::math::isFinite(nSum))
//STRIP001      bSumOk = FALSE;
//STRIP001  if (!::rtl::math::isFinite(nProduct))
//STRIP001      bProductOk = FALSE;
//STRIP001  if (!::rtl::math::isFinite(nSumSqr))
//STRIP001      bSumSqrOk = FALSE;
//STRIP001 }


//STRIP001 short SubTotal::Valid( USHORT nFunction ) const
//STRIP001                          // return 0 => Fehler, -1 => kein Wert, 1 => ok
//STRIP001 {
//STRIP001  short nRet;
//STRIP001  switch (nFunction)
//STRIP001  {
//STRIP001      case PIVOT_FUNC_AVERAGE:
//STRIP001          if (nCount2 == 0)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = bSumOk;
//STRIP001          break;
//STRIP001      case PIVOT_FUNC_STD_DEVP:
//STRIP001      case PIVOT_FUNC_STD_VARP:
//STRIP001          if (nCount2 == 0)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = bSumSqrOk;
//STRIP001          break;
//STRIP001      case PIVOT_FUNC_STD_DEV:
//STRIP001      case PIVOT_FUNC_STD_VAR:
//STRIP001          if (nCount2 < 2)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = bSumSqrOk;
//STRIP001          break;
//STRIP001      case PIVOT_FUNC_MAX:
//STRIP001          if (nCount2 == 0)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = 1;
//STRIP001          break;
//STRIP001      case PIVOT_FUNC_MIN:
//STRIP001          if (nCount2 == 0)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = 1;
//STRIP001          break;
//STRIP001      case PIVOT_FUNC_SUM:
//STRIP001          if (nCount2 == 0)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = bSumOk;
//STRIP001          break;
//STRIP001      case PIVOT_FUNC_PRODUCT:
//STRIP001          if (nCount2 == 0)
//STRIP001              nRet = -1;
//STRIP001          else
//STRIP001              nRet = bProductOk;
//STRIP001          break;
//STRIP001      default:
//STRIP001          nRet = 1;
//STRIP001          break;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


//STRIP001 double SubTotal::Result( USHORT nFunction ) const
//STRIP001 {
//STRIP001  double nRet = 0.0;
//STRIP001  switch (nFunction)
//STRIP001  {
//STRIP001      case PIVOT_FUNC_COUNT:      nRet = (double) nCount;     break;
//STRIP001      case PIVOT_FUNC_COUNT_NUM:  nRet = (double) nCount2;    break;
//STRIP001      case PIVOT_FUNC_SUM:        nRet = nSum;                break;
//STRIP001      case PIVOT_FUNC_MAX:        nRet = nMax;                break;
//STRIP001      case PIVOT_FUNC_MIN:        nRet = nMin;                break;
//STRIP001      case PIVOT_FUNC_PRODUCT:    nRet = nProduct;            break;
//STRIP001      case PIVOT_FUNC_AVERAGE:
//STRIP001              if (nCount2 > 0)
//STRIP001                  nRet = nSum / (double) nCount2;
//STRIP001              break;
//STRIP001      case PIVOT_FUNC_STD_DEV:
//STRIP001              if (nCount2 > 1)
//STRIP001                  nRet = sqrt((nSumSqr - nSum*nSum/(double)(nCount2))
//STRIP001                          / (double)(nCount2-1));
//STRIP001              break;
//STRIP001      case PIVOT_FUNC_STD_DEVP:
//STRIP001              if (nCount2 > 0)
//STRIP001                  nRet = sqrt((nSumSqr - nSum*nSum/(double)(nCount2))
//STRIP001                          / (double)nCount2);
//STRIP001              break;
//STRIP001      case PIVOT_FUNC_STD_VAR:
//STRIP001              if (nCount2 > 1)
//STRIP001                  nRet = (nSumSqr - nSum*nSum/(double)(nCount2))
//STRIP001                          / (double)(nCount2-1);
//STRIP001              break;
//STRIP001      case PIVOT_FUNC_STD_VARP:
//STRIP001              if (nCount2 > 0)
//STRIP001                  nRet = (nSumSqr - nSum*nSum/(double)(nCount2))
//STRIP001                          / (double)(nCount2);
//STRIP001              break;
//STRIP001      default:
//STRIP001              DBG_ERROR("unbekannte Funktion bei SubTotal::Result");
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


/*N*/ BOOL SubTotal::SafePlus(double& fVal1, double fVal2)
/*N*/ {
/*N*/   BOOL bOk = TRUE;
/*N*/   SAL_MATH_FPEXCEPTIONS_OFF();
/*N*/     fVal1 += fVal2;
/*N*/   if (!::rtl::math::isFinite(fVal1))
/*N*/   {
/*N*/       bOk = FALSE;
/*N*/       if (fVal2 > 0.0)
/*N*/           fVal1 = DBL_MAX;
/*N*/       else
/*N*/           fVal1 = -DBL_MAX;
/*N*/   }
/*N*/   return bOk;
/*N*/ }


/*N*/ BOOL SubTotal::SafeMult(double& fVal1, double fVal2)
/*N*/ {
/*N*/   BOOL bOk = TRUE;
/*N*/   SAL_MATH_FPEXCEPTIONS_OFF();
/*N*/     fVal1 *= fVal2;
/*N*/   if (!::rtl::math::isFinite(fVal1))
/*N*/   {
/*N*/       bOk = FALSE;
/*N*/       fVal1 = DBL_MAX;
/*N*/   }
/*N*/   return bOk;
/*N*/ }


//STRIP001 BOOL SubTotal::SafeDiv(double& fVal1, double fVal2)
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  SAL_MATH_FPEXCEPTIONS_OFF();
//STRIP001     fVal1 /= fVal2;
//STRIP001  if (!::rtl::math::isFinite(fVal1))
//STRIP001  {
//STRIP001      bOk = FALSE;
//STRIP001      fVal1 = DBL_MAX;
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }
}
