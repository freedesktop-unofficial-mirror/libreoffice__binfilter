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

#include <tools/debug.hxx>
#include <com/sun/star/document/XEventsSupplier.hpp>
#include "xmlnmspe.hxx"
#include "XMLEventsImportContext.hxx"
#include "XMLShapePropertySetContext.hxx"
#include "XMLTextColumnsContext.hxx"
#include "XMLBackgroundImageContext.hxx"
#include "txtprmap.hxx"

#include "XMLTextShapeStyleContext.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::beans;
using namespace ::binfilter::xmloff::token;

class XMLTextShapePropertySetContext_Impl : public XMLShapePropertySetContext
{
public:
    XMLTextShapePropertySetContext_Impl( SvXMLImport& rInImport, sal_uInt16 nPrfx,
        const OUString& rLName,
        const Reference< XAttributeList >& xAttrList,
        ::std::vector< XMLPropertyState > &rProps,
        const UniReference < SvXMLImportPropertyMapper > &rMap );

    virtual ~XMLTextShapePropertySetContext_Impl();

    using SvXMLPropertySetContext::CreateChildContext;

    virtual SvXMLImportContext *CreateChildContext( USHORT nInPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList >& xAttrList,
        ::std::vector< XMLPropertyState > &rProperties,
        const XMLPropertyState& rProp);
};

XMLTextShapePropertySetContext_Impl::XMLTextShapePropertySetContext_Impl(
                 SvXMLImport& rInImport, sal_uInt16 nPrfx,
                 const OUString& rLName,
                 const Reference< XAttributeList > & xAttrList,
                 ::std::vector< XMLPropertyState > &rProps,
                 const UniReference < SvXMLImportPropertyMapper > &rMap ) :
    XMLShapePropertySetContext( rInImport, nPrfx, rLName, xAttrList, rProps,
                                rMap )
{
}

XMLTextShapePropertySetContext_Impl::~XMLTextShapePropertySetContext_Impl()
{
}

SvXMLImportContext *XMLTextShapePropertySetContext_Impl::CreateChildContext(
                   sal_uInt16 nInPrefix,
                   const OUString& rLocalName,
                   const Reference< XAttributeList > & xAttrList,
                   ::std::vector< XMLPropertyState > &rInProperties,
                   const XMLPropertyState& rProp )
{
    SvXMLImportContext *pContext = 0;

    switch( xMapper->getPropertySetMapper()
                    ->GetEntryContextId( rProp.mnIndex ) )
    {
    case CTF_TEXTCOLUMNS:
        pContext = new XMLTextColumnsContext( GetImport(), nInPrefix,
                                                   rLocalName, xAttrList, rProp,
                                                   rInProperties );
        break;

    case CTF_BACKGROUND_URL:
        DBG_ASSERT( rProp.mnIndex >= 3 &&
                    CTF_BACKGROUND_TRANSPARENCY ==
                        xMapper->getPropertySetMapper()
                        ->GetEntryContextId( rProp.mnIndex-3 ) &&
                    CTF_BACKGROUND_POS  == xMapper->getPropertySetMapper()
                        ->GetEntryContextId( rProp.mnIndex-2 ) &&
                    CTF_BACKGROUND_FILTER  == xMapper->getPropertySetMapper()
                        ->GetEntryContextId( rProp.mnIndex-1 ),
                    "invalid property map!");
        pContext =
            new XMLBackgroundImageContext( GetImport(), nInPrefix,
                                           rLocalName, xAttrList,
                                           rProp,
                                           rProp.mnIndex-2,
                                           rProp.mnIndex-1,
                                           rProp.mnIndex-3,
                                           rProperties );
        break;
    }

    if( !pContext )
        pContext = XMLShapePropertySetContext::CreateChildContext(
                        nInPrefix, rLocalName, xAttrList, rProperties, rProp );

    return pContext;
}

//-----------------------------------------------------------------------------

void XMLTextShapeStyleContext::SetAttribute( sal_uInt16 nPrefixKey,
                                        const OUString& rLocalName,
                                        const OUString& rValue )
{
    if( XML_NAMESPACE_STYLE == nPrefixKey &&
        IsXMLToken( rLocalName, XML_AUTO_UPDATE ) )
    {
          if( IsXMLToken( rValue, XML_TRUE ) )
            bAutoUpdate = sal_True;
    }
    else
    {
        XMLShapeStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
    }
}

TYPEINIT1( XMLTextShapeStyleContext, XMLShapeStyleContext );

XMLTextShapeStyleContext::XMLTextShapeStyleContext( SvXMLImport& rInImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList,
        SvXMLStylesContext& rStyles, sal_uInt16 nInFamily,
        sal_Bool /*bDefaultStyle*/ ) :
    XMLShapeStyleContext( rInImport, nPrfx, rLName, xAttrList, rStyles,
                          nInFamily ),
    sIsAutoUpdate( RTL_CONSTASCII_USTRINGPARAM( "IsAutoUpdate" ) ),
    bAutoUpdate( sal_False )
{
}

XMLTextShapeStyleContext::~XMLTextShapeStyleContext()
{
}

SvXMLImportContext *XMLTextShapeStyleContext::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix &&
        IsXMLToken( rLocalName, XML_PROPERTIES ) )
    {
        UniReference < SvXMLImportPropertyMapper > xImpPrMap =
            GetStyles()->GetImportPropertyMapper( GetFamily() );
        if( xImpPrMap.is() )
        {
            pContext = new XMLTextShapePropertySetContext_Impl(
                    GetImport(), nInPrefix, rLocalName, xAttrList,
                    GetProperties(), xImpPrMap );
        }
    }
    else if ( (XML_NAMESPACE_OFFICE == nInPrefix) &&
              IsXMLToken( rLocalName, XML_EVENTS ) )
    {
        // create and remember events import context
        // (for delayed processing of events)
        pContext = new XMLEventsImportContext( GetImport(), nInPrefix,
                                                   rLocalName);
        xEventContext = pContext;
    }

    if( !pContext )
        pContext = XMLShapeStyleContext::CreateChildContext( nInPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}

void XMLTextShapeStyleContext::CreateAndInsert( sal_Bool bOverwrite )
{
    XMLShapeStyleContext::CreateAndInsert( bOverwrite );
    Reference < XStyle > xLclStyle = GetStyle();
    if( !xLclStyle.is() || !(bOverwrite || IsNew()) )
        return;

    Reference < XPropertySet > xPropSet( xLclStyle, UNO_QUERY );
    Reference< XPropertySetInfo > xPropSetInfo =
                xPropSet->getPropertySetInfo();
    if( xPropSetInfo->hasPropertyByName( sIsAutoUpdate ) )
    {
        Any aAny;
        sal_Bool bTmp = bAutoUpdate;
        aAny.setValue( &bTmp, ::getBooleanCppuType() );
        xPropSet->setPropertyValue( sIsAutoUpdate, aAny );
    }

    // tell the style about it's events (if applicable)
    if( xEventContext.Is() )
    {
        // set event suppplier and release reference to context
        Reference<XEventsSupplier> xEventsSupplier(xLclStyle, UNO_QUERY);
        ((XMLEventsImportContext *)&xEventContext)->SetEvents(xEventsSupplier);
        xEventContext = 0;
    }
}


void XMLTextShapeStyleContext::Finish( sal_Bool bOverwrite )
{
    XMLPropStyleContext::Finish( bOverwrite );
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
