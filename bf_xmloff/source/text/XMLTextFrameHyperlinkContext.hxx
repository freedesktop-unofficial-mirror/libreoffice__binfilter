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

#ifndef _XMLTEXTFRAMEHYPERLINKCONTEXT_HXX
#define _XMLTEXTFRAMEHYPERLINKCONTEXT_HXX

#include <com/sun/star/text/TextContentAnchorType.hpp>
#include <com/sun/star/text/XTextFrame.hpp>

#include "xmlictxt.hxx"

namespace com { namespace sun { namespace star {
    namespace text { class XTextCursor; class XTextFrame; }
    namespace beans { class XPropertySet; }
} } }

namespace binfilter {

class XMLTextFrameHyperlinkContext : public SvXMLImportContext
{
    ::rtl::OUString              sHRef;
    ::rtl::OUString              sName;
    ::rtl::OUString              sTargetFrameName;
    ::com::sun::star::text::TextContentAnchorType eAnchorType;
    ::com::sun::star::uno::Reference <
        ::com::sun::star::text::XTextContent> *pTextContent;
    ::com::sun::star::text::TextContentAnchorType *pAnchorType;
    sal_Bool                    bMap;

public:

    TYPEINFO();

    XMLTextFrameHyperlinkContext( SvXMLImport& rImport,
            sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            ::com::sun::star::text::TextContentAnchorType eAnchorType,
            ::com::sun::star::uno::Reference <
                ::com::sun::star::text::XTextContent> *pTxtCntnt = 0 ,
            ::com::sun::star::text::TextContentAnchorType *pAnchrType = 0 );
    virtual ~XMLTextFrameHyperlinkContext();

    virtual void EndElement();

    SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                const ::rtl::OUString& rLocalName,
                 const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

};


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
