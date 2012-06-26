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
#ifndef _XMLOFF_SCH_XMLEXPORTHELPER_HXX_
#define _XMLOFF_SCH_XMLEXPORTHELPER_HXX_

#include <bf_xmloff/uniref.hxx>
#include <rtl/ustrbuf.hxx>
#include <com/sun/star/util/XStringMapping.hpp>

#include "queue"

namespace com { namespace sun { namespace star {
    namespace chart {
        class XDiagram;
        class XChartDocument;
        class XChartDataArray;
        struct ChartSeriesAddress;
    }
    namespace drawing {
        class XShape;
        class XShapes;
    }
    namespace task {
        class XStatusIndicator;
    }
    namespace frame {
        class XModel;
    }
    namespace xml {
        namespace sax {
            class XAttributeList;
}}}}}
namespace binfilter {

class SvXMLAutoStylePoolP;
class XMLChartExportPropertyMapper;
class SvXMLExport;
class XMLPropertyHandlerFactory;
class XMLPropertySetMapper;

/** With this class you can export a <chart:chart> element containing
    its data as <table:table> element or without internal table. In
    the latter case you have to provide a table address mapper if the
    cell addressing set at the document is not in XML format.
 */
class SchXMLExportHelper : public UniRefBase
{
private:
    SvXMLExport& mrExport;
    SvXMLAutoStylePoolP& mrAutoStylePool;
    UniReference< XMLPropertyHandlerFactory > mxPropertyHandlerFactory;
    UniReference< XMLPropertySetMapper > mxPropertySetMapper;
    UniReference< XMLChartExportPropertyMapper > mxExpPropMapper;
    ::com::sun::star::uno::Reference< ::com::sun::star::util::XStringMapping > mxTableAddressMapper;

    ::rtl::OUString msTableName;
    ::rtl::OUStringBuffer msStringBuffer;
    ::rtl::OUString msString;
    sal_Int32 mnDomainAxes;
    sal_Int32 mnSeriesCount, mnSeriesLength;
    sal_Bool mbHasSeriesLabels, mbHasCategoryLabels;
    sal_Bool mbRowSourceColumns;

    ::rtl::OUString msChartAddress;
    ::rtl::OUString msTableNumberList;

    ::rtl::OUString msCLSID;

    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes > mxAdditionalShapes;

    /** first parseDocument: collect autostyles and store names in this queue
        second parseDocument: export content and use names from this queue
     */
    ::std::queue< ::rtl::OUString > maAutoStyleNameQueue;
    void CollectAutoStyle( const ::std::vector< XMLPropertyState >& aStates );
    void AddAutoStyleAttribute( const ::std::vector< XMLPropertyState >& aStates );

    SvXMLAutoStylePoolP& GetAutoStylePoolP() { return mrAutoStylePool; }

    /// if bExportContent is false the auto-styles are collected
    void parseDocument( ::com::sun::star::uno::Reference<
                            ::com::sun::star::chart::XChartDocument >& rChartDoc,
                        sal_Bool bExportContent,
                        sal_Bool bIncludeTable = sal_False );
    void exportTable( ::com::sun::star::uno::Reference<
                          ::com::sun::star::chart::XChartDataArray >& rData );
    void exportPlotArea( ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > xDiagram,
                         sal_Bool bExportContent,
                         sal_Bool bIncludeTable );
    void exportAxes( ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > xDiagram,
                     sal_Bool bExportContent );

    /// add svg position as attribute for current element
    void addPosition( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > xShape );
    /// add svg size as attribute for current element
    void addSize( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > xShape );
    /// fills the member msString with the appropriate String (i.e. "A3")
    void getCellAddress( sal_Int32 nCol, sal_Int32 nRow );
    /// exports a string as a paragraph element
    void exportText( const ::rtl::OUString& rText, bool bConvertTabsLFs = false );

public:
    SchXMLExportHelper( SvXMLExport& rExport,
                        SvXMLAutoStylePoolP& rASPool );

    // auto-styles
    /// parse chart and collect all auto-styles used in current pool
    void collectAutoStyles( ::com::sun::star::uno::Reference<
                            ::com::sun::star::chart::XChartDocument > rChartDoc );
    /// write the styles collected into the current pool as <style:style> elements
    void exportAutoStyles();

    // content
    /** set the string mapper that is used to convert the application format
        for cell addresses and cell range addresses into XML format

        If the mapper is set it is automatically used for conversion
        @deprecated
      */
    void setTableAddressMapper( ::com::sun::star::uno::Reference<
                                    ::com::sun::star::util::XStringMapping > xMapper )
        { mxTableAddressMapper = xMapper; }
    /** export the <chart:chart> element corresponding to rChartDoc
        if bIncludeTable is true, the chart data is exported as <table:table>
        element (inside the chart element).

        Otherwise the external references stored in the chart document are used
        for writing the corresponding attributes at series

        All attributes contained in xAttrList are written at the chart element,
        which ist the outer element of a chart. So these attributes can easily
        be parsed again by the container
     */
    void exportChart( ::com::sun::star::uno::Reference<
                          ::com::sun::star::chart::XChartDocument > rChartDoc,
                      sal_Bool bIncludeTable );

    /// returns the string corresponding to the current FileFormat CLSID for Chart
    const ::rtl::OUString& getChartCLSID();

    UniReference< XMLPropertySetMapper > GetPropertySetMapper() const { return mxPropertySetMapper; }

    void SetChartRangeAddress( const ::rtl::OUString& rAddress )
        { msChartAddress = rAddress; }
    void SetTableNumberList( const ::rtl::OUString& rList )
        { msTableNumberList = rList; }
};

}//end of namespace binfilter
#endif  // _XMLOFF_SCH_XMLEXPORTHELPER_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
