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

#include"xmlnmspe.hxx"

#include "ximpgrp.hxx"



#include "eventimp.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_EVENTS;
using ::binfilter::xmloff::token::XML_GLUE_POINT;

//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLGroupShapeContext, SvXMLImportContext );

SdXMLGroupShapeContext::SdXMLGroupShapeContext(
    SvXMLImport& rInImport,
    USHORT nPrfx, const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList,
    uno::Reference< drawing::XShapes >& rShapes)
:   SdXMLShapeContext( rInImport, nPrfx, rLocalName, xAttrList, rShapes )
{
}

//////////////////////////////////////////////////////////////////////////////

SdXMLGroupShapeContext::~SdXMLGroupShapeContext()
{
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext* SdXMLGroupShapeContext::CreateChildContext( USHORT nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext* pContext = 0L;

    if( nInPrefix == XML_NAMESPACE_OFFICE && IsXMLToken( rLocalName, XML_EVENTS ) )
    {
        pContext = new SdXMLEventsContext( GetImport(), nInPrefix, rLocalName, xAttrList, mxShape );
    }
    else if( nInPrefix == XML_NAMESPACE_DRAW && IsXMLToken( rLocalName, XML_GLUE_POINT ) )
    {
        addGluePoint( xAttrList );
    }
    else
    {
        // call GroupChildContext function at common ShapeImport
        pContext = GetImport().GetShapeImport()->CreateGroupChildContext(
            GetImport(), nInPrefix, rLocalName, xAttrList, mxChilds);
    }

    // call parent when no own context was created
    if(!pContext)
        pContext = SvXMLImportContext::CreateChildContext(
        nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLGroupShapeContext::StartElement(const uno::Reference< xml::sax::XAttributeList>& /*xAttrList*/)
{
    // create new group shape and add it to rShapes, use it
    // as base for the new group import
    AddShape( "com.sun.star.drawing.GroupShape" );

    if(mxShape.is())
    {
        SetStyle( false );

        mxChilds = uno::Reference< drawing::XShapes >::query( mxShape );
        if( mxChilds.is() )
            GetImport().GetShapeImport()->pushGroupForSorting( mxChilds );
    }

    GetImport().GetShapeImport()->finishShape( mxShape, mxAttrList, mxShapes );
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLGroupShapeContext::EndElement()
{
    if( mxChilds.is() )
        GetImport().GetShapeImport()->popGroupAndSort();
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
