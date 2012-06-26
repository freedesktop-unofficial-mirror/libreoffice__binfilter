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

#ifndef _SVTOOLS_INETOPTIONS_HXX_
#define _SVTOOLS_INETOPTIONS_HXX_

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/uno/Sequence.hxx>
#include <sal/types.h>
#include <bf_svtools/options.hxx>

namespace com { namespace sun { namespace star { namespace beans {
    class XPropertiesChangeListener;
} } } }
namespace rtl { class OUString; }

namespace binfilter
{

//============================================================================
/** The names of all the properties (options) accessible through
    SvtInetOptions.

    @descr  These names are used in the methods
    SvtInetOptions::addPropertiesChangeListener()
 */
#define SVT_INET_OPTION_PROXY_NO_PROXY "Inet/Proxy/NoProxy"
#define SVT_INET_OPTION_PROXY_TYPE "Inet/Proxy/Type"
#define SVT_INET_OPTION_PROXY_FTP_NAME "Inet/Proxy/FTP/Name"
#define SVT_INET_OPTION_PROXY_FTP_PORT "Inet/Proxy/FTP/Port"
#define SVT_INET_OPTION_PROXY_HTTP_NAME "Inet/Proxy/HTTP/Name"
#define SVT_INET_OPTION_PROXY_HTTP_PORT "Inet/Proxy/HTTP/Port"

//============================================================================
/** Interface to access those configuration database entries that are related
    to the various Internet services.

    @descr  The Set...() methods all have a second parameter bFlush.  If false
    is passed (the default), the new value is not written back directly, but
    only cached within this class.  If the value in the configuration database
    is also changed, the cached change will get lost.  If, on the other hand,
    true is passed, the new value is instantly written back to the
    configuration database.
 */
class  SvtInetOptions: public Options
{
public:
    SvtInetOptions();

    virtual ~SvtInetOptions();

private:
    class Impl;

    static Impl * m_pImpl;
};

}

#endif // _SVTOOLS_INETOPTIONS_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
