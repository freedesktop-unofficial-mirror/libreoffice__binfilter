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

#ifndef SC_XMLEXPORTDATABASERANGES_HXX
#define SC_XMLEXPORTDATABASERANGES_HXX

#include <com/sun/star/uno/Sequence.h>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/sheet/XSheetFilterDescriptor.hpp>
#include <com/sun/star/sheet/XSubTotalDescriptor.hpp>
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
namespace binfilter {

class ScXMLExport;
class ScDocument;
class ScMyEmptyDatabaseRangesContainer;

class ScXMLExportDatabaseRanges
{
    ScXMLExport&    rExport;
    ScDocument*     pDoc;

    void WriteImportDescriptor(const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue> aImportDescriptor);
    ::rtl::OUString getOperatorXML(const ::com::sun::star::sheet::FilterOperator aFilterOperator, const sal_Bool bUseRegularExpressions) const;
    void WriteCondition(const ::com::sun::star::sheet::TableFilterField& aFilterField, sal_Bool bIsCaseSensitive, sal_Bool bUseRegularExpressions);
    void WriteFilterDescriptor(const ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSheetFilterDescriptor>& xSheetFilterDescriptor, const ::rtl::OUString sDatabaseRangeName);
    void WriteSortDescriptor(const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue> aSortProperties);
    void WriteSubTotalDescriptor(const ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSubTotalDescriptor> xSubTotalDescriptor, const ::rtl::OUString sDatabaseRangeName);
public:
    ScXMLExportDatabaseRanges(ScXMLExport& rExport);
    ~ScXMLExportDatabaseRanges();
    ScMyEmptyDatabaseRangesContainer GetEmptyDatabaseRanges();
    void WriteDatabaseRanges(const ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSpreadsheetDocument>& xSpreadDoc);
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
