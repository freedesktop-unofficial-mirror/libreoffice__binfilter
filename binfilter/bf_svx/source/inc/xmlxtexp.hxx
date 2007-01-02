/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlxtexp.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:27:02 $
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

#ifndef _SVX_XMLXTEXP_HXX
#define _SVX_XMLXTEXP_HXX

#ifndef _XMLOFF_XMLEXP_HXX
#include "bf_xmloff/xmlexp.hxx"
#endif

namespace rtl { class OUString; }
namespace com { namespace sun { namespace star {
    namespace frame { class XModel; }
    namespace uno { template<class X> class Reference; }
    namespace uno { class XInterface; }
    namespace container { class XNameContainer; }
    namespace document { class XGraphicObjectResolver; }
    namespace xml { namespace sax { class XDocumentHandler; } }
} } }
namespace binfilter {

class SvxXMLXTableExportComponent : public SvXMLExport
{
public:
    // #110680#
    SvxXMLXTableExportComponent(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
        const ::rtl::OUString& rFileName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler > & xHandler,
        const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > & xTable,
        ::com::sun::star::uno::Reference< ::com::sun::star::document::XGraphicObjectResolver >& xGrfResolver);

    ~SvxXMLXTableExportComponent();

    // methods without content:
    virtual void _ExportAutoStyles();
    virtual void _ExportMasterStyles();
    virtual void _ExportContent();

private:
    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > & mxTable;
};

}//end of namespace binfilter
#endif

