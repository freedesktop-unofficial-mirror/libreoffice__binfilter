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
#ifndef SC_XMLSORTI_HXX
#define SC_XMLSORTI_HXX

#include <bf_xmloff/xmlictxt.hxx>
#include <bf_xmloff/xmlimp.hxx>
#include <com/sun/star/util/SortField.hpp>
#include <com/sun/star/table/CellAddress.hpp>

#include "xmldrani.hxx"
namespace binfilter {

class ScXMLImport;

class ScXMLSortContext : public SvXMLImportContext
{
    ScXMLDatabaseRangeContext* pDatabaseRangeContext;

    ::com::sun::star::uno::Sequence < ::com::sun::star::util::SortField> aSortFields;
    ::com::sun::star::table::CellAddress aOutputPosition;
    ::rtl::OUString sCountry;
    ::rtl::OUString sLanguage;
    ::rtl::OUString sAlgorithm;
    sal_Int16   nUserListIndex;
    sal_Bool    bCopyOutputData : 1;
    sal_Bool    bBindFormatsToContent : 1;
    sal_Bool    bIsCaseSensitive : 1;
    sal_Bool    bEnabledUserList : 1;

    const ScXMLImport& GetScImport() const { return (const ScXMLImport&)GetImport(); }
    ScXMLImport& GetScImport() { return (ScXMLImport&)GetImport(); }

public:

    ScXMLSortContext( ScXMLImport& rImport, USHORT nPrfx,
                        const ::rtl::OUString& rLName,
                        const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDatabaseRangeContext* pTempDatabaseRangeContext);

    virtual ~ScXMLSortContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void EndElement();

    void AddSortField(const ::rtl::OUString& sFieldNumber, const ::rtl::OUString& sDataType, const ::rtl::OUString& sOrder);
};

class ScXMLSortByContext : public SvXMLImportContext
{
    ScXMLSortContext* pSortContext;

    ::rtl::OUString sFieldNumber;
    ::rtl::OUString sDataType;
    ::rtl::OUString sOrder;

    const ScXMLImport& GetScImport() const { return (const ScXMLImport&)GetImport(); }
    ScXMLImport& GetScImport() { return (ScXMLImport&)GetImport(); }

public:

    ScXMLSortByContext( ScXMLImport& rImport, USHORT nPrfx,
                        const ::rtl::OUString& rLName,
                        const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLSortContext* pTempSortContext);

    virtual ~ScXMLSortByContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void EndElement();
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
