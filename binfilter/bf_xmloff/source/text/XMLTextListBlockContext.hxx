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

#ifndef _XMLTEXTLISTBLOCKCONTEXT_HXX
#define _XMLTEXTLISTBLOCKCONTEXT_HXX

#include <com/sun/star/container/XIndexReplace.hpp>

#include "xmlictxt.hxx"
namespace binfilter {

class XMLTextImportHelper;

class XMLTextListBlockContext : public SvXMLImportContext
{
    XMLTextImportHelper&    rTxtImport;

    ::com::sun::star::uno::Reference<
                ::com::sun::star::container::XIndexReplace > xNumRules;

    const ::rtl::OUString   sNumberingRules;
    ::rtl::OUString         sStyleName;
    SvXMLImportContextRef   xParentListBlock;
    sal_Int16               nLevel;
    sal_Int16               nLevels;
    sal_Bool                bOrdered : 1;
    sal_Bool                bRestartNumbering : 1;
    sal_Bool                bSetDefaults : 1;


public:

    TYPEINFO();

    XMLTextListBlockContext( SvXMLImport& rImport,
            XMLTextImportHelper& rTxtImp, sal_uInt16 nPrfx,
                const ::rtl::OUString& rLName,
                   const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
                sal_Bool bOrdered );
    virtual ~XMLTextListBlockContext();

    virtual void EndElement();

    SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                const ::rtl::OUString& rLocalName,
                 const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    const ::rtl::OUString& GetStyleName() const { return sStyleName; }
    sal_Int16 GetLevel() const { return nLevel; }
    sal_Bool IsRestartNumbering() const { return bRestartNumbering; }
    void ResetRestartNumbering() { bRestartNumbering = sal_False; }

//  sal_Bool HasGeneratedStyle() const { return xGenNumRule.is(); }
    const ::com::sun::star::uno::Reference <
        ::com::sun::star::container::XIndexReplace >& GetNumRules() const
        { return xNumRules; }
};


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
