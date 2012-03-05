/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef _BF_CONTNR_HXX
#define _BF_CONTNR_HXX

#include <tools/solar.h>

#include <limits.h>

namespace binfilter {

class CBlock;

// -------------
// - Container -
// -------------

// Maximale Blockgroesse
#define CONTAINER_MAXBLOCKSIZE      ((sal_uInt16)0x3FF0)

#define CONTAINER_APPEND            ULONG_MAX
#define CONTAINER_ENTRY_NOTFOUND    ULONG_MAX

class Container
{
private:
    CBlock*     pFirstBlock;
    CBlock*     pCurBlock;
    CBlock*     pLastBlock;
    sal_uInt16      nCurIndex;
    sal_uInt16      nBlockSize;
    sal_uInt16      nInitSize;
    sal_uInt16      nReSize;
    sal_uIntPtr       nCount;

    void ImpCopyContainer(Container const *);
#if defined DBG_UTIL
    static char const * DbgCheckContainer(void const *);
#endif

protected:
#ifdef _BF_IMPCONT_HXX
    void        ImpInsert( void* p, CBlock* pBlock, sal_uInt16 nIndex );
    void*       ImpRemove( CBlock* pBlock, sal_uInt16 nIndex );
    void*       ImpGetObject( sal_uIntPtr nIndex ) const;
    void**      ImpGetOnlyNodes() const;
#endif

public:
                Container( sal_uInt16 nBlockSize,
                           sal_uInt16 nInitSize,
                           sal_uInt16 nReSize );
                Container( sal_uIntPtr nSize );
                Container( const Container& rContainer );
                ~Container();

    void        Insert( void* p, sal_uIntPtr nIndex );

    void*       Remove( sal_uIntPtr nIndex );

    void*       Replace( void* p, sal_uIntPtr nIndex );

    void        SetSize( sal_uIntPtr nNewSize );
    sal_uIntPtr       GetSize() const { return nCount; }

    sal_uIntPtr       Count() const { return nCount; }
    void        Clear();

    sal_uIntPtr       GetCurPos() const;
    void*       GetObject( sal_uIntPtr nIndex ) const;

    void*       Seek( sal_uIntPtr nIndex );

    void*       First();
    void*       Last();
    void*       Next();
    void*       Prev();

    Container&  operator =( const Container& rContainer );

    sal_Bool        operator ==( const Container& rContainer ) const;
    sal_Bool        operator !=( const Container& rContainer ) const
                    { return !(Container::operator==( rContainer )); }
};

}

#endif // _BF_CONTNR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
