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

#ifndef _ADRPARSE_HXX
#define _ADRPARSE_HXX

#include <bf_tools/string.hxx>
#include <vector>

namespace binfilter {

//============================================================================
struct SvAddressEntry_Impl
{
    UniString m_aAddrSpec;
    UniString m_aRealName;

    SvAddressEntry_Impl() {};
    SvAddressEntry_Impl(UniString const & rTheAddrSpec,
                        UniString const & rTheRealName):
        m_aAddrSpec(rTheAddrSpec), m_aRealName(rTheRealName) {}
};

//============================================================================
typedef ::std::vector< SvAddressEntry_Impl* > SvAddressList_Impl;

//============================================================================
class  SvAddressParser
{
    friend class SvAddressParser_Impl;

    SvAddressEntry_Impl m_aFirst;
    SvAddressList_Impl m_aRest;
    bool m_bHasFirst;

public:
    SvAddressParser(UniString const & rInput);

    ~SvAddressParser();

    sal_Int32 Count() const { return m_bHasFirst ? m_aRest.size() + 1 : 0; }

    inline UniString const & GetEmailAddress(sal_Int32 nIndex) const;

    inline UniString const &GetRealName(sal_Int32 nIndex) const;
};

inline UniString const & SvAddressParser::GetEmailAddress(sal_Int32 nIndex) const
{
    return nIndex == 0 ? m_aFirst.m_aAddrSpec : m_aRest[ nIndex - 1 ]->m_aAddrSpec;
}

inline UniString const & SvAddressParser::GetRealName(sal_Int32 nIndex) const
{
    return nIndex == 0 ? m_aFirst.m_aRealName : m_aRest[ nIndex - 1 ]->m_aRealName;
}

}

#endif // _ADRPARSE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
