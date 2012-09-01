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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "XMLShapePropertySetContext.hxx"
#include "xmlimp.hxx"
#include "xmlnumi.hxx"
#include "xmltabi.hxx"
#include "txtprmap.hxx"

#include "sdpropls.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

using rtl::OUString;

//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( XMLShapePropertySetContext, SvXMLPropertySetContext );

XMLShapePropertySetContext::XMLShapePropertySetContext(
                 SvXMLImport& rInImport, sal_uInt16 nPrfx,
                 const OUString& rLName,
                 const Reference< xml::sax::XAttributeList > & xAttrList,
                 ::std::vector< XMLPropertyState > &rProps,
                 const UniReference < SvXMLImportPropertyMapper > &rMap ) :
    SvXMLPropertySetContext( rInImport, nPrfx, rLName, xAttrList, rProps, rMap ),
    mnBulletIndex(-1)
{
}

XMLShapePropertySetContext::~XMLShapePropertySetContext()
{
}

void XMLShapePropertySetContext::EndElement()
{
    Reference< container::XIndexReplace > xNumRule;
    if( mxBulletStyle.Is() )
    {
        SvxXMLListStyleContext* pBulletStyle = (SvxXMLListStyleContext*)&mxBulletStyle;
        xNumRule = pBulletStyle->CreateNumRule( GetImport().GetModel() );
        pBulletStyle->FillUnoNumRule(xNumRule, NULL /* const SvI18NMap * ??? */ );
    }

    Any aAny;
    aAny <<= xNumRule;

    XMLPropertyState aPropState( mnBulletIndex, aAny );
    rProperties.push_back( aPropState );

    SvXMLPropertySetContext::EndElement();
}

SvXMLImportContext *XMLShapePropertySetContext::CreateChildContext(
                   sal_uInt16 nInPrefix,
                   const OUString& rLocalName,
                   const Reference< xml::sax::XAttributeList > & xAttrList,
                   ::std::vector< XMLPropertyState > &rInProperties,
                   const XMLPropertyState& rProp )
{
    SvXMLImportContext *pContext = 0;

    switch( xMapper->getPropertySetMapper()->GetEntryContextId( rProp.mnIndex ) )
    {
    case CTF_NUMBERINGRULES:
        mnBulletIndex = rProp.mnIndex;
        mxBulletStyle = pContext = new SvxXMLListStyleContext( GetImport(), nInPrefix, rLocalName, xAttrList );
        break;
    case CTF_TABSTOP:
        pContext = new SvxXMLTabStopImportContext( GetImport(), nInPrefix,
                                                   rLocalName, rProp,
                                                   rInProperties );
        break;
    }

    if( !pContext )
        pContext = SvXMLPropertySetContext::CreateChildContext( nInPrefix, rLocalName,
                                                            xAttrList,
                                                            rInProperties, rProp );

    return pContext;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
