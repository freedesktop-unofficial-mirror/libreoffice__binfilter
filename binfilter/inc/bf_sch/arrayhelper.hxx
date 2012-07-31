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
