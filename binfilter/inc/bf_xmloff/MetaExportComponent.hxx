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

#ifndef _XMLOFF_METAEXPORTCOMPONENT_HXX
#define _XMLOFF_METAEXPORTCOMPONENT_HXX

#include "xmlexp.hxx"
namespace binfilter {

class XMLMetaExportComponent : public SvXMLExport
{
public:
    // #110680#
    // XMLMetaExportComponent();
    XMLMetaExportComponent(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory
        );

    ~XMLMetaExportComponent();

protected:
    // export the events off all autotexts
    virtual sal_uInt32 exportDoc(
        enum ::binfilter::xmloff::token::XMLTokenEnum eClass = xmloff::token::XML_TOKEN_INVALID );

    // methods without content:
    virtual void _ExportAutoStyles();
    virtual void _ExportMasterStyles();
    virtual void _ExportContent();
};

// global functions to support the component

::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL
    XMLMetaExportComponent_getSupportedServiceNames()
    throw();

::rtl::OUString SAL_CALL XMLMetaExportComponent_getImplementationName()
    throw();

::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL
    XMLMetaExportComponent_createInstance(
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::lang::XMultiServiceFactory > & )
    throw( ::com::sun::star::uno::Exception );

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
