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
#ifndef _XMLOFF_TEXTSTYLE_HXX_
#define _XMLOFF_TEXTSTYLE_HXX_

#include <bf_xmloff/styleexp.hxx>
#include <bf_xmloff/uniref.hxx>
namespace binfilter {

class XMLPropertySetMapper;

class XMLTextStyleExport : public XMLStyleExport
{
    UniReference < XMLPropertySetMapper > xParaPropMapper;

    void exportNumStyles( sal_Bool bUsed );

public:

    XMLTextStyleExport(
        SvXMLExport& rExp,
//      const ::com::sun::star::uno::Reference<
//              ::com::sun::star::xml::sax::XDocumentHandler > & rHandler,
//      const ::com::sun::star::uno::Reference<
//              ::com::sun::star::frame::XModel > & rModel,
        const ::rtl::OUString& rPoolStyleName,
//      const SvXMLNamespaceMap &rNamespaceMap,
//      MapUnit eDUnit,
        SvXMLAutoStylePoolP *pAutoStyleP=0 );
    virtual ~XMLTextStyleExport();

    void exportStyles( sal_Bool bUsed );

    UniReference < XMLPropertySetMapper >& getParaPropMapper();
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
