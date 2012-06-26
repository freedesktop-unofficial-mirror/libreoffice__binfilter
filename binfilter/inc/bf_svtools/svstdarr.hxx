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

#include <bf_svtools/svarray.hxx>

#include <bf_tools/string.hxx>

namespace binfilter
{

#ifndef _SVSTDARR_BOOLS_DECL
SV_DECL_VARARR_VISIBILITY( SvBools, BOOL, 1, 1,  )
#define _SVSTDARR_BOOLS_DECL
#endif

#ifndef _SVSTDARR_BYTES_DECL
SV_DECL_VARARR_VISIBILITY( SvBytes, BYTE, 1, 1,  )
#define _SVSTDARR_BYTES_DECL
#endif

#ifndef _SVSTDARR_ULONGS_DECL
SV_DECL_VARARR_VISIBILITY( SvULongs, ULONG, 1, 1,  )
#define _SVSTDARR_ULONGS_DECL
#endif

#ifndef _SVSTDARR_USHORTS_DECL
SV_DECL_VARARR_VISIBILITY( SvUShorts, USHORT, 1, 1,  )
#define _SVSTDARR_USHORTS_DECL
#endif

#ifndef _SVSTDARR_USHORTSSORT_DECL

typedef BOOL (*FnForEach_SvUShortsSort)( const USHORT&, void* );
class  SvUShortsSort : private SvUShorts
{
public:
    SvUShortsSort(BYTE nSize = 1, BYTE nG = 1)
        : SvUShorts(nSize,nG) {}

    void Insert( const SvUShortsSort *pI, USHORT nS=0, USHORT nE=USHRT_MAX );
    BOOL Insert( const USHORT aE );
    BOOL Insert( const USHORT aE, USHORT& rP );
    void Insert( const USHORT *pE, USHORT nL );
    // remove ab dem Eintrag
    void Remove( const USHORT nP, USHORT nL = 1 );
    BOOL Seek_Entry( const USHORT aE, USHORT* pP = 0 ) const;

    USHORT Count() const  {   return SvUShorts::Count();    }
    const USHORT* GetData() const { return (const USHORT*)pData; }

    const USHORT& operator[](USHORT nP) const {
        return SvUShorts::operator[]( nP );
    }
    const USHORT& GetObject(USHORT nP) const {
        return SvUShorts::GetObject( nP );
    }
    void ForEach( FnForEach_SvUShortsSort fnForEach, void* pArgs = 0 )
    {
        _ForEach( 0, nA, (FnForEach_SvUShorts)fnForEach, pArgs );
    }
    void ForEach( USHORT nS, USHORT nE,
                    FnForEach_SvUShortsSort fnForEach, void* pArgs = 0 )
    {
        _ForEach( nS, nE, (FnForEach_SvUShorts)fnForEach, pArgs );
    }
private:
    SvUShortsSort( const SvUShortsSort& );
    SvUShortsSort& operator=( const SvUShortsSort& );
};

#define _SVSTDARR_USHORTSSORT_DECL
#endif

#ifndef _SVSTDARR_LONGS_DECL
SV_DECL_VARARR_VISIBILITY( SvLongs, long, 1, 1,  )
#define _SVSTDARR_LONGS_DECL
#endif

#ifndef _SVSTDARR_SHORTS_DECL
SV_DECL_VARARR_VISIBILITY( SvShorts, short, 1, 1,  )
#define _SVSTDARR_SHORTS_DECL
#endif

typedef String* StringPtr;
typedef ByteString* ByteStringPtr;


#ifndef _SVSTDARR_STRINGS_DECL
SV_DECL_PTRARR_VISIBILITY( SvStrings, StringPtr, 1, 1,  )
#define _SVSTDARR_STRINGS_DECL
#endif

#ifndef _SVSTDARR_STRINGSDTOR_DECL
SV_DECL_PTRARR_DEL_VISIBILITY( SvStringsDtor, StringPtr, 1, 1,  )
#define _SVSTDARR_STRINGSDTOR_DECL
#endif

#ifndef _SVSTDARR_STRINGSSORT_DECL
SV_DECL_PTRARR_SORT_VISIBILITY( SvStringsSort, StringPtr, 1, 1,  )
#define _SVSTDARR_STRINGSSORT_DECL
#endif

#ifndef _SVSTDARR_STRINGSSORTDTOR_DECL
SV_DECL_PTRARR_SORT_DEL_VISIBILITY( SvStringsSortDtor, StringPtr, 1, 1,  )
#define _SVSTDARR_STRINGSSORTDTOR_DECL
#endif

#ifndef _SVSTDARR_STRINGSISORT_DECL
SV_DECL_PTRARR_SORT_VISIBILITY( SvStringsISort, StringPtr, 1, 1,  )
#define _SVSTDARR_STRINGSISORT_DECL
#endif

#ifndef _SVSTDARR_STRINGSISORTDTOR_DECL
SV_DECL_PTRARR_SORT_DEL_VISIBILITY( SvStringsISortDtor, StringPtr, 1, 1,  )
#define _SVSTDARR_STRINGSISORTDTOR_DECL
#endif

#ifndef _SVSTDARR_XUB_STRLEN_DECL
SV_DECL_VARARR_VISIBILITY( SvXub_StrLens, xub_StrLen, 1, 1,  )
#define _SVSTDARR_XUB_STRLEN_DECL
#endif

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
