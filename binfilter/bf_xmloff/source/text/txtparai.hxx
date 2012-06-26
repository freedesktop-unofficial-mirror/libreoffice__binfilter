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
#ifndef _XMLOFF_TEXTPARAI_HXX_
#define _XMLOFF_TEXTPARAI_HXX_


#include <com/sun/star/uno/Reference.h>

#include "xmlictxt.hxx"
namespace com { namespace sun { namespace star {
namespace text {  class XTextRange; }
namespace xml { namespace sax { class XAttributeList; } }
} } }
namespace binfilter {

class XMLHints_Impl;

#define CONV_FROM_STAR_BATS 1
#define CONV_FROM_STAR_MATH 2
#define CONV_STAR_FONT_FLAGS_VALID 4

class XMLParaContext : public SvXMLImportContext
{
    ::com::sun::star::uno::Reference <
        ::com::sun::star::text::XTextRange > xStart;    // xub_StrLen nStart;
    ::rtl::OUString             sStyleName;
    sal_Int8                nOutlineLevel;
    XMLHints_Impl           *pHints;
    sal_Bool                bIgnoreLeadingSpace;
    sal_Bool                bHeading;
    sal_uInt8               nStarFontsConvFlags;

public:

    TYPEINFO();

    XMLParaContext( SvXMLImport& rImport,
            sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            sal_Bool bHeading );

    virtual ~XMLParaContext();

    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    virtual void Characters( const ::rtl::OUString& rChars );

};


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
