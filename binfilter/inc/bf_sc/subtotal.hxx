/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: subtotal.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:43:30 $
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

#ifndef SC_SUBTOTAL_HXX
#define SC_SUBTOTAL_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef MSC
    #include <setjmp.h>
#else
    extern "C"
    {
    #define _JBLEN  9  /* bp, di, si, sp, ret addr, ds */
    typedef  int  jmp_buf[_JBLEN];
    #define _JMP_BUF_DEFINED
    #define setjmp  _setjmp
    int  __cdecl _setjmp(jmp_buf);
    void __cdecl longjmp(jmp_buf, int);
    };
#endif

namespace binfilter {

class SubTotal
{
private:
    long    nCount;
    long    nCount2;
    double  nSum;
    double  nSumSqr;
    double  nMax;
    double  nMin;
    double  nProduct;
    BOOL    bSumOk;
    BOOL    bSumSqrOk;
    BOOL    bProductOk;
    USHORT  nProgress;

public:
    USHORT  nIndex;         // Test
    static jmp_buf aGlobalJumpBuf;

public:
            SubTotal();
            ~SubTotal();

    void    Update( double nVal );
    static  BOOL SafePlus( double& fVal1, double fVal2);
    static  BOOL SafeMult( double& fVal1, double fVal2);
};


struct ScFunctionData                   // zum Berechnen von einzelnen Funktionen
{
    ScSubTotalFunc  eFunc;
    double          nVal;
    long            nCount;
    BOOL            bError;

    ScFunctionData( ScSubTotalFunc eFn ) :
        eFunc(eFn), nVal(0.0), nCount(0), bError(FALSE) {}
};


} //namespace binfilter
#endif


