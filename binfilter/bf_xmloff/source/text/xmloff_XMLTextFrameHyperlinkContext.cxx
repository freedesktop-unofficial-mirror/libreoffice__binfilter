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

#include "xmlimp.hxx"
#include "nmspmap.hxx"
#include "xmlnmspe.hxx"
#include "xmluconv.hxx"
#include "XMLTextFrameContext.hxx"
#include "XMLTextFrameHyperlinkContext.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::beans;
using namespace ::binfilter::xmloff::token;

using rtl::OUString;

TYPEINIT1( XMLTextFrameHyperlinkContext, SvXMLImportContext );

XMLTextFrameHyperlinkContext::XMLTextFrameHyperlinkContext(
        SvXMLImport& rInImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList,
        TextContentAnchorType eATyp,
           Reference < XTextContent> *pTxtCntnt,
        TextContentAnchorType *pAnchrType ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    eAnchorType( eATyp ),
    pTextContent( pTxtCntnt ),
    pAnchorType( pAnchrType ),
    bMap( sal_False )
{
    OUString sShow;
    const SvXMLTokenMap& rTokenMap =
        GetImport().GetTextImport()->GetTextHyperlinkAttrTokenMap();

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        const OUString& rValue = xAttrList->getValueByIndex( i );

        OUString aLclLocalName;
        sal_uInt16 nLclPrefix =
            GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                            &aLclLocalName );
        switch( rTokenMap.Get( nLclPrefix, aLclLocalName ) )
        {
        case XML_TOK_TEXT_HYPERLINK_HREF:
            sHRef = GetImport().GetAbsoluteReference( rValue );
            break;
        case XML_TOK_TEXT_HYPERLINK_NAME:
            sName = rValue;
            break;
        case XML_TOK_TEXT_HYPERLINK_TARGET_FRAME:
            sTargetFrameName = rValue;
            break;
        case XML_TOK_TEXT_HYPERLINK_SHOW:
            sShow = rValue;
            break;
        case XML_TOK_TEXT_HYPERLINK_SERVER_MAP:
            {
                sal_Bool bTmp;
                if( rInImport.GetMM100UnitConverter().convertBool( bTmp,
                                                                  rValue ) )
                {
                    bMap = bTmp;
                }
            }
            break;
        }
    }

    if( sShow.getLength() && !sTargetFrameName.getLength() )
    {
        if( IsXMLToken( sShow, XML_NEW ) )
            sTargetFrameName =
                    OUString( RTL_CONSTASCII_USTRINGPARAM("_blank" ) );
        else if( IsXMLToken( sShow, XML_REPLACE ) )
            sTargetFrameName =
                    OUString( RTL_CONSTASCII_USTRINGPARAM("_self" ) );
    }
}

XMLTextFrameHyperlinkContext::~XMLTextFrameHyperlinkContext()
{
}

void XMLTextFrameHyperlinkContext::EndElement()
{
}

SvXMLImportContext *XMLTextFrameHyperlinkContext::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;
    XMLTextFrameContext *pTextFrameContext = 0;

    if( XML_NAMESPACE_DRAW == nInPrefix )
    {
        sal_uInt16 nFrameType = USHRT_MAX;
        if( IsXMLToken( rLocalName, XML_TEXT_BOX ) )
            nFrameType = XML_TEXT_FRAME_TEXTBOX;
        else if( IsXMLToken( rLocalName, XML_IMAGE ) )
            nFrameType = XML_TEXT_FRAME_GRAPHIC;
        else if( IsXMLToken( rLocalName, XML_OBJECT ) )
            nFrameType = XML_TEXT_FRAME_OBJECT;
        else if( IsXMLToken( rLocalName, XML_OBJECT_OLE ) )
            nFrameType = XML_TEXT_FRAME_OBJECT_OLE;
        else if( IsXMLToken( rLocalName, XML_APPLET) )
            nFrameType = XML_TEXT_FRAME_APPLET;
        else if( IsXMLToken( rLocalName, XML_PLUGIN ) )
            nFrameType = XML_TEXT_FRAME_PLUGIN;
        else if( IsXMLToken( rLocalName, XML_FLOATING_FRAME ) )
            nFrameType = XML_TEXT_FRAME_FLOATING_FRAME;

        if( USHRT_MAX != nFrameType )
            pTextFrameContext = new XMLTextFrameContext( GetImport(), nInPrefix,
                                                rLocalName, xAttrList,
                                                eAnchorType,
                                                nFrameType );
    }

    if( pTextFrameContext )
    {
        pTextFrameContext->SetHyperlink( sHRef, sName, sTargetFrameName, bMap );
        if( pAnchorType )
            *pAnchorType = pTextFrameContext->GetAnchorType();
        if( pTextContent )
            *pTextContent = pTextFrameContext->GetTextContent();
        pContext = pTextFrameContext;
    }
    else
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );

    return pContext;
}



}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
