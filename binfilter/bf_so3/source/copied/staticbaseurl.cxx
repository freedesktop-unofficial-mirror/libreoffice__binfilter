/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: staticbaseurl.cxx,v $
 * $Revision: 1.4 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include "sal/config.h"

#include "bf_so3/staticbaseurl.hxx"

#include "com/sun/star/ucb/XCommandEnvironment.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "rtl/instance.hxx"
#include "rtl/textenc.h"
#include "rtl/ustring.h"
#include "rtl/ustring.hxx"
#include "bf_svtools/urihelper.hxx"
#include "tools/debug.hxx"
#include "tools/string.hxx"
#include "tools/urlobj.hxx"
#include "ucbhelper/content.hxx"

namespace {

struct BaseURIRef: public rtl::Static< INetURLObject, BaseURIRef > {};

String extend(ByteString const & rOctets) {
    return String(rOctets, RTL_TEXTENCODING_ISO_8859_1);
}

com::sun::star::uno::Any GetCasePreservedURL(INetURLObject const & aObj) {
    DBG_ASSERT( aObj.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL!" );
    if (aObj.GetProtocol() == INET_PROT_FILE) {
        try {
            com::sun::star::uno::Any aVoidArgument;
            ucbhelper::Content aCnt(
                aObj.GetMainURL(INetURLObject::NO_DECODE),
                com::sun::star::uno::Reference<
                com::sun::star::ucb::XCommandEnvironment >());
            return aCnt.executeCommand(
                rtl::OUString(
                    RTL_CONSTASCII_USTRINGPARAM("getCasePreservingURL")),
                aVoidArgument);
        } catch (com::sun::star::uno::Exception &) {
            DBG_WARNING("Any other exception");
        }
    }
    return com::sun::star::uno::Any();
}

}

namespace binfilter { namespace StaticBaseUrl {

String RelToAbs(
    ByteString const & rTheRelURIRef, bool bIgnoreFragment,
    INetURLObject::EncodeMechanism eEncodeMechanism,
    INetURLObject::DecodeMechanism eDecodeMechanism, rtl_TextEncoding eCharset,
    INetURLObject::FSysStyle eStyle)
{
    // Backwards compatibility:
    if (rTheRelURIRef.Len() == 0 || rTheRelURIRef.GetChar(0) == '#') {
        return extend(rTheRelURIRef);
    }
    INetURLObject aTheAbsURIRef;
    BaseURIRef::get().GetNewAbsURL(
        rTheRelURIRef, &aTheAbsURIRef, eEncodeMechanism, eCharset, eStyle,
        bIgnoreFragment);
    return aTheAbsURIRef.GetMainURL(eDecodeMechanism, eCharset);
}

String RelToAbs(
    String const & rTheRelURIRef, bool bIgnoreFragment,
    INetURLObject::EncodeMechanism eEncodeMechanism,
    INetURLObject::DecodeMechanism eDecodeMechanism, rtl_TextEncoding eCharset,
    INetURLObject::FSysStyle eStyle)
{
    // Backwards compatibility:
    if (rTheRelURIRef.Len() == 0 || rTheRelURIRef.GetChar(0) == '#') {
        return rTheRelURIRef;
    }
    INetURLObject aTheAbsURIRef;
    return (BaseURIRef::get().GetNewAbsURL(
                rTheRelURIRef, &aTheAbsURIRef, eEncodeMechanism, eCharset,
                eStyle, bIgnoreFragment)
            || eEncodeMechanism != INetURLObject::WAS_ENCODED
            || eDecodeMechanism != INetURLObject::DECODE_TO_IURI
            || eCharset != RTL_TEXTENCODING_UTF8)
        ? String(aTheAbsURIRef.GetMainURL(eDecodeMechanism, eCharset))
        : rTheRelURIRef;
}

String AbsToRel(
    ByteString const & rTheAbsURIRef,
    INetURLObject::EncodeMechanism eEncodeMechanism,
    INetURLObject::DecodeMechanism eDecodeMechanism, rtl_TextEncoding eCharset,
    INetURLObject::FSysStyle eStyle)
{
    INetURLObject const & rINetURLObject = BaseURIRef::get();
    com::sun::star::uno::Any aAny;
    if ( rINetURLObject.GetProtocol() != INET_PROT_NOT_VALID )
        aAny = GetCasePreservedURL(rINetURLObject);
    rtl::OUString aBaseURL;
    sal_Bool success = (aAny >>= aBaseURL);
    if (success) {
        INetURLObject aAbsURIRef(rTheAbsURIRef, eEncodeMechanism, eCharset);
        com::sun::star::uno::Any aAny2(GetCasePreservedURL(aAbsURIRef));
        rtl::OUString aAbsURL;
        success = (aAny2 >>= aAbsURL);
        if (success) {
            return INetURLObject::GetRelURL(
                aBaseURL, aAbsURL, INetURLObject::WAS_ENCODED, eDecodeMechanism,
                RTL_TEXTENCODING_UTF8, eStyle);
        } else {
            return INetURLObject::GetRelURL(
                aBaseURL, extend(rTheAbsURIRef), eEncodeMechanism,
                eDecodeMechanism, eCharset, eStyle);
        }
    } else {
        return INetURLObject::GetRelURL(
            rINetURLObject.GetMainURL(INetURLObject::NO_DECODE),
            extend(rTheAbsURIRef), eEncodeMechanism, eDecodeMechanism, eCharset,
            eStyle);
    }
}

String AbsToRel(
    String const & rTheAbsURIRef,
    INetURLObject::EncodeMechanism eEncodeMechanism,
    INetURLObject::DecodeMechanism eDecodeMechanism, rtl_TextEncoding eCharset,
    INetURLObject::FSysStyle eStyle)
{
    INetURLObject const & rINetURLObject = BaseURIRef::get();
    com::sun::star::uno::Any aAny;
    if ( rINetURLObject.GetProtocol() != INET_PROT_NOT_VALID )
        aAny = GetCasePreservedURL(rINetURLObject);
    rtl::OUString aBaseURL;
    sal_Bool success = (aAny >>= aBaseURL);
    if (success) {
        INetURLObject aAbsURIRef(rTheAbsURIRef,eEncodeMechanism,eCharset);
        com::sun::star::uno::Any aAny2(GetCasePreservedURL(aAbsURIRef));
        rtl::OUString aAbsURL;
        success = (aAny2 >>= aAbsURL);
        if (success) {
            return INetURLObject::GetRelURL(
                aBaseURL, aAbsURL, INetURLObject::WAS_ENCODED, eDecodeMechanism,
                RTL_TEXTENCODING_UTF8, eStyle);
        } else {
            return INetURLObject::GetRelURL(
                aBaseURL, rTheAbsURIRef, eEncodeMechanism, eDecodeMechanism,
                eCharset, eStyle);
        }
    } else {
        return INetURLObject::GetRelURL(
            rINetURLObject.GetMainURL(INetURLObject::NO_DECODE), rTheAbsURIRef,
            eEncodeMechanism, eDecodeMechanism, eCharset, eStyle);
    }
}

bool SetBaseURL(
    ByteString const & rTheBaseURIRef,
    INetURLObject::EncodeMechanism eMechanism, rtl_TextEncoding eCharset)
{
    return BaseURIRef::get().SetURL(rTheBaseURIRef, eMechanism, eCharset);
}

bool SetBaseURL(
    String const & rTheBaseURIRef, INetURLObject::EncodeMechanism eMechanism,
    rtl_TextEncoding eCharset)
{
    return BaseURIRef::get().SetURL(rTheBaseURIRef, eMechanism, eCharset);
}

String GetBaseURL(
    INetURLObject::DecodeMechanism eMechanism, rtl_TextEncoding eCharset)
{
    return BaseURIRef::get().GetMainURL(eMechanism, eCharset);
}

String SmartRelToAbs(
    ByteString const & rTheRelURIRef, bool bIgnoreFragment,
    INetURLObject::EncodeMechanism eEncodeMechanism,
    INetURLObject::DecodeMechanism eDecodeMechanism, rtl_TextEncoding eCharset,
    INetURLObject::FSysStyle eStyle)
{
    return ::binfilter::SmartRel2Abs(
        INetURLObject(GetBaseURL()), rTheRelURIRef,
        ::binfilter::GetMaybeFileHdl(), true, bIgnoreFragment, eEncodeMechanism,
        eDecodeMechanism, eCharset, false, eStyle);
}

String SmartRelToAbs(
    String const & rTheRelURIRef, bool bIgnoreFragment,
    INetURLObject::EncodeMechanism eEncodeMechanism,
    INetURLObject::DecodeMechanism eDecodeMechanism, rtl_TextEncoding eCharset,
    INetURLObject::FSysStyle eStyle)
{
    return ::binfilter::SmartRel2Abs(
        INetURLObject(GetBaseURL()), rTheRelURIRef,
        ::binfilter::GetMaybeFileHdl(), true, bIgnoreFragment, eEncodeMechanism,
        eDecodeMechanism, eCharset, false, eStyle);
}

} }
