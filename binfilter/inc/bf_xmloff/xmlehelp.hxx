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

#ifndef _XMLOFF_XMLEHELP_HXX
#define _XMLOFF_XMLEHELP_HXX

#include <tools/mapunit.hxx>
namespace rtl { class OUStringBuffer; }
namespace binfilter {


class SvXMLExportHelper
{
public:
    static void AddLength( sal_Int32 nValue, MapUnit eValueUnit,
                           ::rtl::OUStringBuffer& rOut,
                           MapUnit eOutUnit );
    static double GetConversionFactor(::rtl::OUStringBuffer& rUnit,
        const MapUnit eCoreUnit, const MapUnit eDestUnit);
    static MapUnit GetUnitFromString(const ::rtl::OUString& rString,
        MapUnit eDefaultUnit);
};



}//end of namespace binfilter
#endif  //  _XMLOFF_XMLEHELP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
