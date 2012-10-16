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

#include "MetaImportComponent.hxx"

#include "xmlnmspe.hxx"


#include "xmlmetai.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

class SvXMLMetaDocumentContext : public SvXMLImportContext
{
private:
    ::com::sun::star::uno::Reference<
        ::com::sun::star::document::XDocumentInfo>  xDocInfo;

public:
    SvXMLMetaDocumentContext(SvXMLImport& rImport, USHORT nPrfx,
                            const ::rtl::OUString& rLName,
                            const ::com::sun::star::uno::Reference<
                                ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                            const ::com::sun::star::uno::Reference<
                                ::com::sun::star::document::XDocumentInfo>& rDocInfo);
    virtual ~SvXMLMetaDocumentContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
    virtual void EndElement();
};

SvXMLMetaDocumentContext::SvXMLMetaDocumentContext(SvXMLImport& rInImport,
                        USHORT nPrfx, const ::rtl::OUString& rLName,
                        const uno::Reference<xml::sax::XAttributeList>& /*xAttrList*/,
                        const uno::Reference<document::XDocumentInfo>& rDocInfo) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    xDocInfo(rDocInfo)
{
    // here are no attributes
}

SvXMLMetaDocumentContext::~SvXMLMetaDocumentContext()
{
}

SvXMLImportContext *SvXMLMetaDocumentContext::CreateChildContext( USHORT nInPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& /*xAttrList*/ )
{
    if (  (XML_NAMESPACE_OFFICE == nInPrefix) &&
         IsXMLToken(rLocalName, XML_META) )
    {
        return new SfxXMLMetaContext(GetImport(), nInPrefix, rLocalName, xDocInfo);
    }
    else
    {
        return new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
    }
}

void SvXMLMetaDocumentContext::EndElement()
{
}

//===========================================================================

// #110680#
XMLMetaImportComponent::XMLMetaImportComponent(
    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory) throw()
:   SvXMLImport(xServiceFactory)
{
}

XMLMetaImportComponent::~XMLMetaImportComponent() throw()
{
}


SvXMLImportContext* XMLMetaImportComponent::CreateContext(
    sal_uInt16 nPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference<xml::sax::XAttributeList > & xAttrList )
{
    if (  (XML_NAMESPACE_OFFICE == nPrefix) &&
         IsXMLToken(rLocalName, XML_DOCUMENT_META) )
    {
        return new SvXMLMetaDocumentContext(*this, nPrefix, rLocalName, xAttrList, xDocInfo);
    }
    else
    {
        return SvXMLImport::CreateContext(nPrefix, rLocalName, xAttrList);
    }
}

void SAL_CALL XMLMetaImportComponent::setTargetDocument( const uno::Reference< lang::XComponent >& xDoc )
    throw(lang::IllegalArgumentException, uno::RuntimeException)
{
    xDocInfo = uno::Reference< document::XDocumentInfo >::query( xDoc );
    if( !xDocInfo.is() )
        throw lang::IllegalArgumentException();
}

uno::Sequence< ::rtl::OUString > SAL_CALL
    XMLMetaImportComponent_getSupportedServiceNames()
        throw()
{
    const ::rtl::OUString aServiceName( RTL_CONSTASCII_USTRINGPARAM(
        "com.sun.star.document.XMLMetaImporter" ) );
    const uno::Sequence< ::rtl::OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

rtl::OUString SAL_CALL XMLMetaImportComponent_getImplementationName() throw()
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "XMLMetaImportComponent" ) );
}

uno::Reference< uno::XInterface > SAL_CALL XMLMetaImportComponent_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    // return (cppu::OWeakObject*)new XMLMetaImportComponent;
    return (cppu::OWeakObject*)new XMLMetaImportComponent(rSMgr);
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
