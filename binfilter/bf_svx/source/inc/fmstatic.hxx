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

#ifndef _FM_STATIC_HXX_
#define _FM_STATIC_HXX_
#include <bf_tools/string.hxx>
namespace binfilter {

struct ConstAsciiString
{
    const sal_Char* ascii;
    sal_Int32       length;

    inline  operator const ::rtl::OUString () const;
    inline  operator const sal_Char* () const { return ascii; }

    inline ConstAsciiString(const sal_Char* _pAsciiZeroTerminated, const sal_Int32 _nLength);
    inline ~ConstAsciiString();

private:
    mutable ::rtl::OUString*    ustring;
};

//------------------------------------------------------------
inline ConstAsciiString::ConstAsciiString(const sal_Char* _pAsciiZeroTerminated, const sal_Int32 _nLength)
    :ascii(_pAsciiZeroTerminated)
    ,length(_nLength)
    ,ustring(NULL)
{
}

//------------------------------------------------------------
inline ConstAsciiString::~ConstAsciiString()
{
    delete ustring;
    ustring = NULL;
}

//------------------------------------------------------------
inline ConstAsciiString::operator const ::rtl::OUString () const
{
    if (!ustring)
        ustring = new ::rtl::OUString(ascii, length, RTL_TEXTENCODING_ASCII_US);
    return *ustring;
}

#define DECLARE_CONSTASCII_USTRING(name)    \
    extern ConstAsciiString name

#define IMPLEMENT_CONSTASCII_USTRING(name, asciivalue)  \
    ConstAsciiString name(asciivalue, sizeof(asciivalue) - 1)


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
