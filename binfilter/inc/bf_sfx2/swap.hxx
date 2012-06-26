/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef _SWAP_HXX
#define _SWAP_HXX

#include <bf_svtools/bf_solar.h>

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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
