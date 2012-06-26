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

#include "xmlbasici.hxx"

#include "attrlist.hxx"
#include "nmspmap.hxx"
#include "xmlimp.hxx"

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;


//.........................................................................
namespace binfilter
{
//.........................................................................

    // =============================================================================
    // XMLBasicImportContext
    // =============================================================================

    XMLBasicImportContext::XMLBasicImportContext( SvXMLImport& rInImport, USHORT nPrfx, const ::rtl::OUString& rLName,
            const Reference< frame::XModel >& rxModel )
        :SvXMLImportContext( rInImport, nPrfx, rLName )
        ,m_xModel( rxModel )
    {
        Reference< lang::XMultiServiceFactory > xMSF = GetImport().getServiceFactory();
        if ( xMSF.is() )
        {
            m_xHandler.set( xMSF->createInstance(
                ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.XMLBasicImporter" ) ) ),
                UNO_QUERY );
        }

        if ( m_xHandler.is() )
        {
            Reference< document::XImporter > xImporter( m_xHandler, UNO_QUERY );
            if ( xImporter.is() )
            {
                Reference< lang::XComponent > xComp( m_xModel, UNO_QUERY );
                xImporter->setTargetDocument( xComp );
            }
        }
    }

    // -----------------------------------------------------------------------------

    XMLBasicImportContext::~XMLBasicImportContext()
    {
    }

    // -----------------------------------------------------------------------------

    SvXMLImportContext* XMLBasicImportContext::CreateChildContext(
        USHORT nInPrefix, const ::rtl::OUString& rLocalName,
        const Reference< xml::sax::XAttributeList >& /*rxAttrList*/ )
    {
        SvXMLImportContext* pContext = 0;

        if ( m_xHandler.is() )
            pContext = new XMLBasicImportChildContext( GetImport(), nInPrefix, rLocalName, m_xHandler );

        if ( !pContext )
            pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );

        return pContext;
    }

    // -----------------------------------------------------------------------------

    void XMLBasicImportContext::StartElement(
        const Reference< xml::sax::XAttributeList >& rxAttrList )
    {
        if ( m_xHandler.is() )
        {
            m_xHandler->startDocument();

            // copy namespace declarations
            SvXMLAttributeList* pAttrList = new SvXMLAttributeList( rxAttrList );
            Reference< xml::sax::XAttributeList > xAttrList( pAttrList );
            const SvXMLNamespaceMap& rNamespaceMap = GetImport().GetNamespaceMap();
            sal_uInt16 nPos = rNamespaceMap.GetFirstKey();
            while ( nPos != USHRT_MAX )
            {
                ::rtl::OUString aAttrName( rNamespaceMap.GetAttrNameByKey( nPos ) );
                if ( xAttrList->getValueByName( aAttrName ).getLength() == 0 )
                    pAttrList->AddAttribute( aAttrName, rNamespaceMap.GetNameByKey( nPos ) );
                nPos = rNamespaceMap.GetNextKey( nPos );
            }

            m_xHandler->startElement(
                GetImport().GetNamespaceMap().GetQNameByKey( GetPrefix(), GetLocalName() ),
                xAttrList );
        }
    }

    // -----------------------------------------------------------------------------

    void XMLBasicImportContext::EndElement()
    {
        if ( m_xHandler.is() )
        {
            m_xHandler->endElement(
                GetImport().GetNamespaceMap().GetQNameByKey( GetPrefix(), GetLocalName() ) );
            m_xHandler->endDocument();
        }
    }

    // -----------------------------------------------------------------------------

    void XMLBasicImportContext::Characters( const ::rtl::OUString& rChars )
    {
        if ( m_xHandler.is() )
            m_xHandler->characters( rChars );
    }


    // =============================================================================
    // XMLBasicImportChildContext
    // =============================================================================

    XMLBasicImportChildContext::XMLBasicImportChildContext( SvXMLImport& rInImport, USHORT nPrfx, const ::rtl::OUString& rLName,
            const Reference< xml::sax::XDocumentHandler >& rxHandler )
        :SvXMLImportContext( rInImport, nPrfx, rLName )
        ,m_xHandler( rxHandler )
    {
    }

    // -----------------------------------------------------------------------------

    XMLBasicImportChildContext::~XMLBasicImportChildContext()
    {
    }

    // -----------------------------------------------------------------------------

    SvXMLImportContext* XMLBasicImportChildContext::CreateChildContext(
        USHORT nInPrefix, const ::rtl::OUString& rLocalName,
        const Reference< xml::sax::XAttributeList >& /*xAttrList*/ )
    {
        return new XMLBasicImportChildContext( GetImport(), nInPrefix, rLocalName, m_xHandler );
    }

    // -----------------------------------------------------------------------------

    void XMLBasicImportChildContext::StartElement(
        const Reference< xml::sax::XAttributeList >& xAttrList )
    {
        if ( m_xHandler.is() )
        {
            m_xHandler->startElement(
                GetImport().GetNamespaceMap().GetQNameByKey( GetPrefix(), GetLocalName() ),
                xAttrList );
        }
    }

    // -----------------------------------------------------------------------------

    void XMLBasicImportChildContext::EndElement()
    {
        if ( m_xHandler.is() )
        {
            m_xHandler->endElement(
                GetImport().GetNamespaceMap().GetQNameByKey( GetPrefix(), GetLocalName() ) );
        }
    }

    // -----------------------------------------------------------------------------

    void XMLBasicImportChildContext::Characters( const ::rtl::OUString& rChars )
    {
        if ( m_xHandler.is() )
            m_xHandler->characters( rChars );
    }

    // -----------------------------------------------------------------------------

//.........................................................................
}   // namespace binfilter
//.........................................................................

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
