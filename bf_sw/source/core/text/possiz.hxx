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
#ifndef _POSSIZ_HXX
#define _POSSIZ_HXX


#include <tools/gen.hxx>
#include "txttypes.hxx"
namespace binfilter {

// Im Gegensazt zu den SV-Sizes ist die SwPosSize immer positiv
class SwPosSize
{
    KSHORT nWidth;
    KSHORT nHeight;
public:
    inline SwPosSize( const KSHORT _nWidth = 0, const KSHORT _nHeight = 0 )
        : nWidth(_nWidth), nHeight(_nHeight) { }
    inline SwPosSize( const Size &rSize )
        : nWidth(KSHORT(rSize.Width())), nHeight(KSHORT(rSize.Height())){ }
    inline KSHORT Height() const { return nHeight; }
    inline void Height( const KSHORT nNew ) { nHeight = nNew; }
    inline KSHORT Width() const { return nWidth; }
    inline void Width( const KSHORT nNew ) { nWidth = nNew; }

    inline Size SvLSize() const { return Size( nWidth, nHeight ); }
    inline void SvLSize( const Size &rSize );
    inline void SvXSize( const Size &rSize );
    inline sal_Bool operator==( const SwPosSize &rSize ) const;
    inline SwPosSize &operator=( const SwPosSize &rSize );
    inline SwPosSize &operator=( const Size &rSize );
};

inline sal_Bool SwPosSize::operator==(const SwPosSize &rSize ) const
{
    return( Height() == rSize.Height() &&
            Width() == rSize.Width() );
}

inline SwPosSize &SwPosSize::operator=(const SwPosSize &rSize )
{
    nWidth  = rSize.Width();
    nHeight = rSize.Height();
    return *this;
}

inline void SwPosSize::SvLSize( const Size &rSize )
{
    nWidth  = KSHORT(rSize.Width());
    nHeight = KSHORT(rSize.Height());
}

inline void SwPosSize::SvXSize( const Size &rSize )
{
    nHeight = KSHORT(rSize.Width());
    nWidth = KSHORT(rSize.Height());
}

inline SwPosSize &SwPosSize::operator=( const Size &rSize )
{
    nWidth  = KSHORT(rSize.Width());
    nHeight = KSHORT(rSize.Height());
    return *this;
}


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
