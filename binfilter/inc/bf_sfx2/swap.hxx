/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swap.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:41:20 $
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
