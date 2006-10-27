/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_subtotal.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 14:39:03 $
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


}
