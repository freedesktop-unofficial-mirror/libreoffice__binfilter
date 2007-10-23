/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: staticbaseurl.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:28:22 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef INCLUDED_SO3_INC_BF_XMLOFF_STATICBASEURL_HXX
#define INCLUDED_SO3_INC_BF_XMLOFF_STATICBASEURL_HXX

#ifndef _SAL_CONFIG_H_
#include "sal/config.h"
#endif

#ifndef _RTL_TEXTENC_H
#include "rtl/textenc.h"
#endif
#ifndef _URLOBJ_HXX
#include "tools/urlobj.hxx"
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

class ByteString;
class String;

namespace so3 {

/** A collection of static functions from tools/inc/urlobj.hxx (rev. 1.26) and
    svtools/inc/urihelper.hxx (rev. 1.2) that have since been removed, but need
    to remain available in so3 and binfilter.
 */
namespace StaticBaseUrl {

SO3_DLLPRIVATE String RelToAbs(
    ByteString const & rTheRelURIRef, bool bIgnoreFragment = false,
    INetURLObject::EncodeMechanism eEncodeMechanism
    = INetURLObject::WAS_ENCODED,
    INetURLObject::DecodeMechanism eDecodeMechanism
    = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
    INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

String RelToAbs(
    String const & rTheRelURIRef, bool bIgnoreFragment = false,
    INetURLObject::EncodeMechanism eEncodeMechanism
    = INetURLObject::WAS_ENCODED,
    INetURLObject::DecodeMechanism eDecodeMechanism
    = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
    INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

SO3_DLLPRIVATE String AbsToRel(
    ByteString const & rTheAbsURIRef,
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

SO3_DLLPRIVATE bool SetBaseURL(
    ByteString const & rTheBaseURIRef,
    INetURLObject::EncodeMechanism eMechanism = INetURLObject::WAS_ENCODED,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);

bool SetBaseURL(
    String const & rTheBaseURIRef,
    INetURLObject::EncodeMechanism eMechanism = INetURLObject::WAS_ENCODED,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);

String GetBaseURL(
    INetURLObject::DecodeMechanism eMechanism = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);

SO3_DLLPRIVATE String SmartRelToAbs(
    ByteString const & rTheRelURIRef, bool bIgnoreFragment = false,
    INetURLObject::EncodeMechanism eEncodeMechanism
    = INetURLObject::WAS_ENCODED,
    INetURLObject::DecodeMechanism eDecodeMechanism
    = INetURLObject::DECODE_TO_IURI,
    rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
    INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

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
