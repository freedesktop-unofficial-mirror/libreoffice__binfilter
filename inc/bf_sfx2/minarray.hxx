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
#ifndef _SFXVARARR_HXX
#define _SFXVARARR_HXX

#include <bf_svtools/bf_solar.h>

#include <limits.h>
#include <string.h>

#include <tools/debug.hxx>

namespace binfilter {

#if defined (ALPHA) && defined (UNX)
#define DEL_ARRAY( X )
#else
#define DEL_ARRAY( X ) X
#endif

class SfxPtrArr
{
private:
    void** pData;
    USHORT nUsed;
    BYTE nGrow;
    BYTE nUnused;
public:
    SfxPtrArr( BYTE nInitSize = 0, BYTE nGrowSize = 8 );
    SfxPtrArr( const SfxPtrArr& rOrig );
    ~SfxPtrArr();
    void* GetObject( USHORT nPos ) const { return operator[](nPos); }
    void*& GetObject( USHORT nPos ) { return operator[](nPos); }
    USHORT Remove( USHORT nPos, USHORT nLen );
    USHORT Count() const { return nUsed; }
    inline void** operator*();
    inline void* operator[]( USHORT nPos ) const;
    inline void*& operator[]( USHORT nPos );
    void Clear() { Remove( 0, Count() ); }
};

inline void** SfxPtrArr::operator*()
{
    return ( nUsed==0 ? 0 : pData );
}

inline void* SfxPtrArr::operator[]( USHORT nPos ) const
{
    DBG_ASSERT( nPos < nUsed, "" );
    return *(pData+nPos);
}

inline void*& SfxPtrArr::operator [] (USHORT nPos)
{
    DBG_ASSERT( nPos < nUsed, "" );
    return *(pData+nPos);
}

#define DECL_PTRARRAY(ARR, T, nI, nG)\
class ARR: public SfxPtrArr\
{\
public:\
   ARR( BYTE nIni=nI, BYTE nGrowSize=nG ):\
       SfxPtrArr(nIni,nGrowSize) \
   {}\
   ARR( const ARR& rOrig ):\
       SfxPtrArr(rOrig) \
   {}\
   T GetObject( USHORT nPos ) const { return operator[](nPos); } \
   T& GetObject( USHORT nPos ) { return operator[](nPos); } \
   void Remove( USHORT nPos, USHORT nLen = 1 ) {\
       SfxPtrArr::Remove( nPos, nLen ); \
   }\
   T* operator *() {\
       return (T*) SfxPtrArr::operator*();\
   }\
   T operator[]( USHORT nPos ) const { \
       return (T) SfxPtrArr::operator[](nPos); } \
   T& operator[]( USHORT nPos ) { \
       return (T&) SfxPtrArr::operator[](nPos); } \
   void Clear() { Remove( 0, Count() ); }\
};


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
