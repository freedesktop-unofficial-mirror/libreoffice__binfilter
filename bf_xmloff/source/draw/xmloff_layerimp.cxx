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

#include <com/sun/star/drawing/XLayerManager.hpp>
#include <com/sun/star/drawing/XLayerSupplier.hpp>



#include "xmlimp.hxx"

#include "xmlnmspe.hxx"


#include "nmspmap.hxx"

#include "layerimp.hxx"
namespace binfilter {

using namespace ::std;
using namespace ::cppu;
using namespace ::com::sun::star;
using namespace ::com::sun::star::xml;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_NAME;

using rtl::OUString;


TYPEINIT1( SdXMLLayerSetContext, SvXMLImportContext );

SdXMLLayerSetContext::SdXMLLayerSetContext( SvXMLImport& rInImport, sal_uInt16 nPrfx,   const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& /*xAttrList*/)
: SvXMLImportContext(rInImport, nPrfx, rLocalName)
{
    Reference< XLayerSupplier > xLayerSupplier( rInImport.GetModel(), UNO_QUERY );
    DBG_ASSERT( xLayerSupplier.is(), "XModel is not supporting XLayerSupplier!" );
    if( xLayerSupplier.is() )
        mxLayerManager = xLayerSupplier->getLayerManager();
}

SdXMLLayerSetContext::~SdXMLLayerSetContext()
{
}

SvXMLImportContext * SdXMLLayerSetContext::CreateChildContext( USHORT nInPrefix, const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    if( mxLayerManager.is() )
    {
        const OUString strName( RTL_CONSTASCII_USTRINGPARAM( "Name" ) );

        OUString aName;

        const sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
        for(sal_Int16 i=0; i < nAttrCount; i++)
        {
            OUString aLclLocalName;
            if( GetImport().GetNamespaceMap().GetKeyByAttrName( xAttrList->getNameByIndex( i ), &aLclLocalName ) == XML_NAMESPACE_DRAW )
            {
                const OUString sValue( xAttrList->getValueByIndex( i ) );

                if( IsXMLToken( aLclLocalName, XML_NAME ) )
                {
                    aName = sValue;
                }
            }
        }

        DBG_ASSERT( aName.getLength(), "draw:layer element without draw:name!" );
        if( aName.getLength() )
        {
            Reference< XPropertySet > xLayer;

            if( mxLayerManager->hasByName( aName ) )
            {
                mxLayerManager->getByName( aName ) >>= xLayer;
                DBG_ASSERT( xLayer.is(), "failed to get existing XLayer!" );
            }
            else
            {
                Reference< XLayerManager > xLayerManager( mxLayerManager, UNO_QUERY );
                if( xLayerManager.is() )
                    xLayer = Reference< XPropertySet >::query( xLayerManager->insertNewByIndex( xLayerManager->getCount() ) );
                DBG_ASSERT( xLayer.is(), "failed to create new XLayer!" );

                if( xLayer.is() )
                {
                    Any aAny;
                    aAny <<= aName;
                    xLayer->setPropertyValue( strName, aAny );
                }
            }
        }
    }

    return new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
