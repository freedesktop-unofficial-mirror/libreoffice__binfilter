/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_MetaExportComponent.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:50:55 $
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

#ifndef _XMLOFF_METAEXPORTCOMPONENT_HXX
#include "MetaExportComponent.hxx"
#endif







// #110680#
//#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
//#include <comphelper/processfactory.hxx>
//#endif


#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif


#ifndef _XMLOFF_XMLMETAE_HXX
#include "xmlmetae.hxx"
#endif

namespace binfilter {


using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

// #110680#
XMLMetaExportComponent::XMLMetaExportComponent(
    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory)
:   SvXMLExport( xServiceFactory, MAP_INCH, XML_META )
{
}

XMLMetaExportComponent::~XMLMetaExportComponent()
{
}

sal_uInt32 XMLMetaExportComponent::exportDoc( enum XMLTokenEnum eClass )
{
    GetDocHandler()->startDocument();
    {
        GetAttrList().AddAttribute(
            GetNamespaceMap().GetAttrNameByKey( XML_NAMESPACE_DC ),
            GetNamespaceMap().GetNameByKey( XML_NAMESPACE_DC ) );
        GetAttrList().AddAttribute(
            GetNamespaceMap().GetAttrNameByKey( XML_NAMESPACE_META ),
            GetNamespaceMap().GetNameByKey( XML_NAMESPACE_META ) );
        GetAttrList().AddAttribute(
            GetNamespaceMap().GetAttrNameByKey( XML_NAMESPACE_OFFICE ),
            GetNamespaceMap().GetNameByKey( XML_NAMESPACE_OFFICE ) );

        SvXMLElementExport aDocElem( *this, XML_NAMESPACE_OFFICE, XML_DOCUMENT_META,
                        sal_True, sal_True );
        {

            SvXMLElementExport aElem( *this, XML_NAMESPACE_OFFICE, XML_META,
                            sal_True, sal_True );
            SfxXMLMetaExport aMeta( *this, GetModel() );
            aMeta.Export();
        }
    }
    GetDocHandler()->endDocument();
    return 0;
}

// methods without content:
void XMLMetaExportComponent::_ExportAutoStyles() {}
void XMLMetaExportComponent::_ExportMasterStyles() {}
void XMLMetaExportComponent::_ExportContent() {}


uno::Sequence< ::rtl::OUString > SAL_CALL XMLMetaExportComponent_getSupportedServiceNames()
    throw()
{
    const ::rtl::OUString aServiceName(
        RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.XMLMetaExporter" ) );
    const uno::Sequence< ::rtl::OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

rtl::OUString SAL_CALL XMLMetaExportComponent_getImplementationName() throw()
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "XMLMetaExportComponent" ) );
}

uno::Reference< uno::XInterface > SAL_CALL XMLMetaExportComponent_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    // return (cppu::OWeakObject*)new XMLMetaExportComponent;
    return (cppu::OWeakObject*)new XMLMetaExportComponent(rSMgr);
}

}//end of namespace binfilter
