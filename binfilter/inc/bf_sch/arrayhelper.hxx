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


#ifndef _SCH_ARRAYHELPER_HXX
#define _SCH_ARRAYHELPER_HXX

#include <limits>

namespace binfilter {

/** Helper class for creating an array of type T and size nSize.
    The create methods are protected against integer overflow in
    operator new[].
 */
template< typename T >
class ArrayHelper
{
public:
    static T* create_short_size( short n );
    static T* create_short_size( short m, short n );
    static T* create_long_size( long n );
    static T* create_long_size( long m, long n );
};

template< typename T >
T* ArrayHelper< T >::create_short_size( short n )
{
    T* pRet = 0;
    if ( n > 0 &&
         static_cast< unsigned short >( n ) <= ( ::std::numeric_limits< size_t >::max() / sizeof( T ) ) )
    {
        pRet = new (std::nothrow) T[ n ];
    }
    return pRet;
}

template< typename T >
T* ArrayHelper< T >::create_short_size( short m, short n )
{
    T* pRet = 0;
    if ( m > 0 && n > 0 &&
         static_cast< unsigned short >( m ) <= ( ( ::std::numeric_limits< size_t >::max() / n ) / sizeof( T ) ) )
    {
        pRet = new (std::nothrow) T[ static_cast< size_t >( m ) * n ];
    }
    return pRet;
}

template< typename T >
T* ArrayHelper< T >::create_long_size( long n )
{
    T* pRet = 0;
    if ( n > 0 &&
         static_cast< unsigned long >( n ) <= ( ::std::numeric_limits< size_t >::max() / sizeof( T ) ) )
    {
        pRet = new (std::nothrow) T[ n ];
    }
    return pRet;
}

template< typename T >
T* ArrayHelper< T >::create_long_size( long m, long n )
{
    T* pRet = 0;
    if ( m > 0 && n > 0 &&
         static_cast< unsigned long >( m ) <= ( ( ::std::numeric_limits< size_t >::max() / n ) / sizeof( T ) ) )
    {
        pRet = new (std::nothrow) T[ static_cast< size_t >( m ) * n ];
    }
    return pRet;
}

} //namespace binfilter
#endif
