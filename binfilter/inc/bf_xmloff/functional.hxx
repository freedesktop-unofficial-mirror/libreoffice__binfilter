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

#ifndef _XMLOFF_FUNCTIONAL_HXX
#define _XMLOFF_FUNCTIONAL_HXX

#include <rtl/ustring.hxx>

/* THIS HEADER IS DEPRECATED. USE comphelper/stl_types.hxx INSTEAD!!! */

/** @#file
 *
 * re-implement STL functors as needed
 *
 * The standard comparison operators from the STL cause warnings with
 * several compilers about our sal_Bool (=unsigned char) being
 * converted to bool (C++ bool). We wish to avoid that.
 */

struct less_functor
{
    bool operator()(const ::rtl::OUString& x,
                    const ::rtl::OUString& y) const
    {
        return 0 != (x<y);
    }
};

namespace binfilter {
}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
