/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SchXMLExport.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:50:12 $
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
#ifndef SCH_XMLEXPORT_HXX_
#define SCH_XMLEXPORT_HXX_

#ifndef _XMLOFF_SCH_XMLEXPORTHELPER_HXX_
#include <bf_xmloff/SchXMLExportHelper.hxx>
#endif
#ifndef _SCH_XMLAUTOSTYLEPOOLP_HXX_
#include "SchXMLAutoStylePoolP.hxx"
#endif
#ifndef _XMLOFF_XMLEXP_HXX
#include <bf_xmloff/xmlexp.hxx>
#endif
#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif
#ifndef _XMLOFF_PROPERTYSETMAPPER_HXX
#include <bf_xmloff/xmlprmap.hxx>
#endif
#ifndef _XMLOFF_PROPERTYHANDLERFACTORY_HXX
#include <bf_xmloff/prhdlfac.hxx>
#endif

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
