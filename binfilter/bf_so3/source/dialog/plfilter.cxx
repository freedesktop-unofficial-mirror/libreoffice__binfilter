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

#include <set>
#include <map>

#include <tools/debug.hxx>
#include <vcl/stdtext.hxx>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/plugin/PluginDescription.hpp>
#include <com/sun/star/plugin/XPluginManager.hpp>

using namespace std;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::plugin;

namespace binfilter {

struct ltstr
{
    bool operator()( const String& s1, const String& s2 ) const
    {
        return ( s1.CompareTo( s2 ) == COMPARE_LESS );
    }
};

typedef set< String, ltstr > StrSet;
typedef map< String, StrSet, ltstr > FilterMap;


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
