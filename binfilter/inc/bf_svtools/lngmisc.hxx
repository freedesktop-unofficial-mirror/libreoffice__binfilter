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

#ifndef _SVTOOLS_LNGMISC_HXX_
#define _SVTOOLS_LNGMISC_HXX_

#include <bf_svtools/bf_solar.h>
#include <sal/types.h>

#include <rtl/ustring.hxx>

///////////////////////////////////////////////////////////////////////////

#define SVT_SOFT_HYPHEN ((sal_Unicode) 0x00AD)
#define SVT_HARD_HYPHEN ((sal_Unicode) 0x2011)

// the non-breaking space
#define SVT_HARD_SPACE  ((sal_Unicode) 0x00A0)

namespace binfilter
{

inline BOOL IsHyphen( sal_Unicode cChar )
{
    return cChar == SVT_SOFT_HYPHEN  ||  cChar == SVT_HARD_HYPHEN;
}


inline BOOL IsControlChar( sal_Unicode cChar )
{
    return cChar < (sal_Unicode) ' ';
}


inline BOOL HasHyphens( const rtl::OUString &rTxt )
{
    return  rTxt.indexOf( SVT_SOFT_HYPHEN ) != -1  ||
            rTxt.indexOf( SVT_HARD_HYPHEN ) != -1;
}

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
