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

#ifndef INCLUDED_SO3_INC_BF_XMLOFF_STATICBASEURL_HXX
#define INCLUDED_SO3_INC_BF_XMLOFF_STATICBASEURL_HXX

#include "sal/config.h"

#include "rtl/textenc.h"
#include "bf_tools/string.hxx"
#include "tools/urlobj.hxx"

#include "bf_so3/so3dllapi.h"

namespace binfilter {

/** A collection of static functions from tools/inc/urlobj.hxx (rev. 1.26) and
    svtools/inc/urihelper.hxx (rev. 1.2) that have since been removed, but need
    to remain available in so3 and binfilter.
 */
namespace StaticBaseUrl {

String RelToAbs(
    String const & rTheRelURIRef, bool bIgnoreFragment = false,
    INetURLObject::EncodeMechanism eEncodeMechanism
    = INetURLObject::WAS_ENCODED,
    INetURLObject::DecodeMechanism eDecodeMechanism
    = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
    INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

String AbsToRel(
    String const & rTheAbsURIRef,
    INetURLObject::EncodeMechanism eEncodeMechanism
    = INetURLObject::WAS_ENCODED,
    INetURLObject::DecodeMechanism eDecodeMechanism
    = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
    INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

bool SetBaseURL(
    String const & rTheBaseURIRef,
    INetURLObject::EncodeMechanism eMechanism = INetURLObject::WAS_ENCODED,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);

String GetBaseURL(
    INetURLObject::DecodeMechanism eMechanism = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);

String SmartRelToAbs(
    String const & rTheRelURIRef, bool bIgnoreFragment = false,
    INetURLObject::EncodeMechanism eEncodeMechanism
    = INetURLObject::WAS_ENCODED,
    INetURLObject::DecodeMechanism eDecodeMechanism
    = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
    INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

}

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
