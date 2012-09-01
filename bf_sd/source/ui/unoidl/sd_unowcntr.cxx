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

#include <unowcntr.hxx>
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

SvUnoWeakContainer::SvUnoWeakContainer() throw()
{
    mpList = new WeakRefList;
}

SvUnoWeakContainer::~SvUnoWeakContainer() throw()
{
    for ( size_t i = 0, n =  mpList->size(); i < n ; ++i )
        delete (*mpList)[ i ];
    mpList->clear();
    delete mpList;
}

/** inserts the given ref into this container */
void SvUnoWeakContainer::insert( uno::WeakReference< uno::XInterface > xRef ) throw()
{
    for ( size_t i = 0; i < mpList->size(); )
    {
        uno::WeakReference< uno::XInterface >* pRef = (*mpList)[ i ];
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xTestRef( *pRef );
        if(! xTestRef.is() )
        {
            delete pRef;
            WeakRefList::iterator it = mpList->begin();
            ::std::advance( it, i );
            mpList->erase( it );
        }
        else
        {
            if( *pRef == xRef )
                return;

            ++i;
        }
    }

    mpList->push_back( new uno::WeakReference< uno::XInterface >( xRef ) );
}

/** searches the container for a ref that returns true on the given
    search function
*/
sal_Bool SvUnoWeakContainer::findRef( uno::WeakReference< uno::XInterface >& rRef, void* pSearchData, weakref_searchfunc pSearchFunc )
{
    for ( size_t i = 0; i < mpList->size(); )
    {
        uno::WeakReference< uno::XInterface >* pRef = (*mpList)[ i ];
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xTestRef( *pRef );
        if(! xTestRef.is() )
        {
            delete pRef;
            WeakRefList::iterator it = mpList->begin();
            ::std::advance( it, i );
            mpList->erase( it );
        }
        else
        {
            if( (*pSearchFunc)( *pRef, pSearchData ) )
            {
                rRef = *pRef;
                return sal_True;
            }

            ++i;
        }
    }

    return sal_False;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
