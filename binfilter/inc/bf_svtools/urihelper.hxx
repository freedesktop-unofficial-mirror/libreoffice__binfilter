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

#ifndef SVTOOLS_URIHELPER_HXX
#define SVTOOLS_URIHELPER_HXX

#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/uri/XUriReference.hpp>
#include <com/sun/star/uno/RuntimeException.hpp>

#include <rtl/textenc.h>
#include <rtl/ustring.hxx>

#include <unotools/charclass.hxx>
#include <tools/link.hxx>
#include <bf_svtools/bf_solar.h>
#include <tools/urlobj.hxx>
#include <bf_tools/string.hxx>


//============================================================================
namespace binfilter
{

/**
   @ATT
   Calling this function with defaulted arguments rMaybeFileHdl = Link() and
   bCheckFileExists = true often leads to results that are not intended:
   Whenever the given rTheBaseURIRef is a file URL, the given rTheRelURIRef is
   relative, and rTheRelURIRef could also be smart-parsed as a non-file URL
   (e.g., the relative URL "foo/bar" can be smart-parsed as "http://foo/bar"),
   then SmartRel2Abs called with rMaybeFileHdl = Link() and bCheckFileExists =
   true returns the non-file URL interpretation.  To avoid this, either pass
   some non-null rMaybeFileHdl if you want to check generated file URLs for
   existence (see GetMaybeFileHdl), or use bCheckFileExists = false
   if you want to generate file URLs without checking for their existence.
*/
 UniString
SmartRel2Abs(INetURLObject const & rTheBaseURIRef,
             UniString const & rTheRelURIRef,
             Link const & rMaybeFileHdl = Link(),
             bool bCheckFileExists = true,
             bool bIgnoreFragment = false,
             INetURLObject::EncodeMechanism eEncodeMechanism
                 = INetURLObject::WAS_ENCODED,
             INetURLObject::DecodeMechanism eDecodeMechanism
                 = INetURLObject::DECODE_TO_IURI,
             rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
             bool bRelativeNonURIs = false,
             INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

//============================================================================
 void SetMaybeFileHdl(Link const & rTheMaybeFileHdl);

//============================================================================
 Link GetMaybeFileHdl();

//============================================================================
 UniString
FindFirstURLInText(UniString const & rText,
                   xub_StrLen & rBegin,
                   xub_StrLen & rEnd,
                   CharClass const & rCharClass,
                   INetURLObject::EncodeMechanism eMechanism
                       = INetURLObject::WAS_ENCODED,
                   rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
                   INetURLObject::FSysStyle eStyle
                       = INetURLObject::FSYS_DETECT);

//============================================================================
/** Remove any password component from both absolute and relative URLs.

    @ATT  The current implementation will not remove a password from a
    relative URL that has an authority component (e.g., the password is not
    removed from the relative ftp URL <//user:password@domain/path>).  But
    since our functions to translate between absolute and relative URLs never
    produce relative URLs with authority components, this is no real problem.

    @ATT  For relative URLs (or anything not recognized as an absolute URI),
    the current implementation will return the input unmodified, not applying
    any translations implied by the encode/decode parameters.

    @param rURI  An absolute or relative URI reference.

    @param eEncodeMechanism  See the general discussion for INetURLObject set-
    methods.

    @param eDecodeMechanism  See the general discussion for INetURLObject get-
    methods.

    @param eCharset  See the general discussion for INetURLObject get- and
    set-methods.

    @return  The input URI with any password component removed.
 */
 UniString
removePassword(UniString const & rURI,
               INetURLObject::EncodeMechanism eEncodeMechanism
                   = INetURLObject::WAS_ENCODED,
               INetURLObject::DecodeMechanism eDecodeMechanism
                   = INetURLObject::DECODE_TO_IURI,
               rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);
}

#endif // SVTOOLS_URIHELPER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
