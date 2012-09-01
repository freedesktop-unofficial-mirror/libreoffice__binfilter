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

#include <cppuhelper/weakref.hxx>

#include "SinglePropertySetInfoCache.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::beans::XPropertySetInfo;

sal_Bool SinglePropertySetInfoCache::hasProperty(
        const Reference< XPropertySet >& rPropSet,
        Reference< XPropertySetInfo >& rPropSetInfo )
{
    if( !rPropSetInfo.is() )
        rPropSetInfo = rPropSet->getPropertySetInfo();
    iterator aIter = find( rPropSetInfo );
    if( aIter != end() )
    {
        return aIter->second;
    }
    bool bRet = rPropSetInfo->hasPropertyByName( sName );
    // Check whether the property set info is destroyed if it is
    // assigned to a weak reference only. If it is destroyed, then
    // every instance of getPropertySetInfo returns a new object.
    // Such property set infos must not be cached.
    WeakReference < XPropertySetInfo > xWeakInfo( rPropSetInfo );
    rPropSetInfo = 0;
    rPropSetInfo = xWeakInfo;
    if( rPropSetInfo.is() )
    {
        value_type aValue( rPropSetInfo, bRet );
        insert( aValue );
    }
    return bRet;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
