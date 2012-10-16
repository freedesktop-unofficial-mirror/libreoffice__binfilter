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

#ifndef _XMLOFF_XMLTKMAP_HXX
#define _XMLOFF_XMLTKMAP_HXX

#include <sal/types.h>

#include <bf_xmloff/xmltoken.hxx>

namespace rtl { class OUString; }
namespace binfilter {

class SvXMLTokenMap_Impl;
class SvXMLTokenMapEntry_Impl;

#define XML_TOK_UNKNOWN 0xffffU
#define XML_TOKEN_MAP_END { 0xffffU, ::binfilter::xmloff::token::XML_TOKEN_INVALID, 0U }

struct SvXMLTokenMapEntry
{
    sal_uInt16  nPrefixKey;
    enum ::binfilter::xmloff::token::XMLTokenEnum eLocalName;
    sal_uInt16  nToken;
};

class SvXMLTokenMap
{
    SvXMLTokenMap_Impl      *pImpl;

    SvXMLTokenMapEntry_Impl     *_Find( sal_uInt16 nKind,
                                        const ::rtl::OUString& rName ) const;

public:

    SvXMLTokenMap( SvXMLTokenMapEntry *pMap );
    ~SvXMLTokenMap();

    sal_uInt16 Get( sal_uInt16 nPrefix, const ::rtl::OUString& rLName ) const;
};

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLTKMAP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
