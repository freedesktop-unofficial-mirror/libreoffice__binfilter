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
#ifndef SCH_XMLEXPORT_HXX_
#define SCH_XMLEXPORT_HXX_

#include <bf_xmloff/SchXMLExportHelper.hxx>
#include "SchXMLAutoStylePoolP.hxx"
#include <bf_xmloff/xmlexp.hxx>
#include <bf_xmloff/uniref.hxx>
#include <bf_xmloff/xmlprmap.hxx>
#include <bf_xmloff/prhdlfac.hxx>

namespace com { namespace sun { namespace star {
    namespace chart {
        class XDiagram;
        class XChartDocument;
        class XChartDataArray;
        struct ChartSeriesAddress;
    }
    namespace drawing {
        class XShape;
    }
    namespace task {
        class XStatusIndicator;
    }
}}}
namespace binfilter {

class SvXMLAutoStylePoolP;
class SvXMLUnitConverter;
class XMLChartExportPropertyMapper;

// ------------------------------------------
// export class for a complete chart document
// ------------------------------------------

class SchXMLExport : public SvXMLExport
{
private:
    ::com::sun::star::uno::Reference< ::com::sun::star::task::XStatusIndicator > mxStatusIndicator;
    SchXMLAutoStylePoolP maAutoStylePool;

    SchXMLExportHelper maExportHelper;

protected:
    virtual void _ExportStyles( sal_Bool bUsed );
    virtual void _ExportAutoStyles();
    virtual void _ExportMasterStyles();
    virtual void _ExportContent();

public:
    // #110680#
    SchXMLExport(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory,
        sal_uInt16 nExportFlags = EXPORT_ALL );
    virtual ~SchXMLExport();

    UniReference< XMLPropertySetMapper > GetPropertySetMapper() const { return maExportHelper.GetPropertySetMapper(); }

    // XServiceInfo ( : SvXMLExport )
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw( ::com::sun::star::uno::RuntimeException );
};

}//end of namespace binfilter
#endif  // SCH_XMLEXPORT_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
