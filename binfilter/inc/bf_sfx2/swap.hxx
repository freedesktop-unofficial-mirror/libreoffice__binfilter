/*************************************************************************
 *
 *  $RCSfile: swap.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:26:30 $
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
#ifndef _SWAP_HXX
#define _SWAP_HXX

#include <solar.h>
namespace binfilter {

inline BOOL SwapShort()
{
    short aLoHiTst = 0x55AA;
    return (*((char*)&aLoHiTst) == 0x55 );
}

inline BOOL SwapLong()
{
    long aLoHiTst = 0x5555AAAA;
    return (*((short*)&aLoHiTst) == 0x5555 );
}

union LoHi
{
    BYTE nBytes[2];
    short nShort;
};

#define SWAP( n )   (( ((LoHi&)n).nBytes[1] << 8 ) + ((LoHi&)n).nBytes[0] )

inline short Swap(short nV)
{
    return SwapShort()? SWAP(nV): nV;
}

inline unsigned short Swap(unsigned short nV)
{
    return SwapShort()? SWAP(nV): nV;
}


union LL
{
    USHORT nBytes[2];
    long l;
};

#define SWAPL(n)   (( ((LL&)n).nBytes[1] << 16 ) + ((LL&)n).nBytes[0] )

inline long SwapL(long l)
{
    LL aL;
    aL.l = l;
    aL.nBytes[0] = SWAP(aL.nBytes[0]);
    aL.nBytes[1] = SWAP(aL.nBytes[1]);
    aL.l = SWAPL(aL.l);
    return aL.l;
}

inline long Swap(long lV)
{
    return SwapLong()? SwapL(lV): lV;
}

inline unsigned long Swap(unsigned long lV)
{
    return SwapLong()? SwapL(lV): lV;
}

}//end of namespace binfilter
#endif
