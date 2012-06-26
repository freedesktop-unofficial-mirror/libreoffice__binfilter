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

#ifndef _XMLOFF_I18NMAP_HXX
#define _XMLOFF_I18NMAP_HXX

#include <bf_svtools/bf_solar.h>

namespace rtl
{
    class OUString;
}
namespace binfilter {

class SvI18NMap_Impl;
class SvI18NMapEntry_Impl;

class SvI18NMap
{
    SvI18NMap_Impl      *pImpl;

    SvI18NMapEntry_Impl *_Find( USHORT nKind,
                                const ::rtl::OUString& rName ) const;

public:

    SvI18NMap();
    ~SvI18NMap();

    // Add a name mapping
    void Add( USHORT nKind, const ::rtl::OUString& rName,
              const ::rtl::OUString& rNewName );

    // Return a mapped name. If the name could not be found, return the
    // original name.
    const ::rtl::OUString& Get( USHORT nKind,
                                const ::rtl::OUString& rName ) const;
};

}//end of namespace binfilter
#endif  //  _XMLOFF_I18NMAP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
