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

#include <com/sun/star/text/XTextColumns.hpp>
#include <com/sun/star/style/VerticalAlignment.hpp>


#include "xmlnmspe.hxx"
#include "xmluconv.hxx"
#include "xmlexp.hxx"

#include "XMLTextColumnsExport.hxx"
namespace binfilter {

using namespace ::com::sun::star::style;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::binfilter::xmloff::token;

using rtl::OUString;
using rtl::OUStringBuffer;


XMLTextColumnsExport::XMLTextColumnsExport( SvXMLExport& rExp ) :
    rExport( rExp ),
    sSeparatorLineIsOn(RTL_CONSTASCII_USTRINGPARAM("SeparatorLineIsOn")),
    sSeparatorLineWidth(RTL_CONSTASCII_USTRINGPARAM("SeparatorLineWidth")),
    sSeparatorLineColor(RTL_CONSTASCII_USTRINGPARAM("SeparatorLineColor")),
    sSeparatorLineRelativeHeight(RTL_CONSTASCII_USTRINGPARAM("SeparatorLineRelativeHeight")),
    sSeparatorLineVerticalAlignment(RTL_CONSTASCII_USTRINGPARAM("SeparatorLineVerticalAlignment")),
    sIsAutomatic(RTL_CONSTASCII_USTRINGPARAM("IsAutomatic")),
    sAutomaticDistance(RTL_CONSTASCII_USTRINGPARAM("AutomaticDistance"))
{
}

void XMLTextColumnsExport::exportXML( const Any& rAny )
{
    Reference < XTextColumns > xColumns;
    rAny >>= xColumns;

    Sequence < TextColumn > aColumns = xColumns->getColumns();
    const TextColumn *pColumns = aColumns.getArray();
    sal_Int32 nCount = aColumns.getLength();

    OUStringBuffer sValue;
    GetExport().GetMM100UnitConverter().convertNumber( sValue, nCount );
    GetExport().AddAttribute( XML_NAMESPACE_FO, XML_COLUMN_COUNT,
                              sValue.makeStringAndClear() );

    // handle 'automatic' columns
    Reference < XPropertySet > xPropSet( xColumns, UNO_QUERY );
    if( xPropSet.is() )
    {
        Any aAny = xPropSet->getPropertyValue( sIsAutomatic );
        if ( *(sal_Bool*)aAny.getValue() )
        {
            aAny = xPropSet->getPropertyValue( sAutomaticDistance );
            sal_Int32 nDistance = 0;
            aAny >>= nDistance;
            OUStringBuffer aBuffer;
            GetExport().GetMM100UnitConverter().convertMeasure(
                aBuffer, nDistance );
            GetExport().AddAttribute( XML_NAMESPACE_FO,
                                      XML_COLUMN_GAP,
                                      aBuffer.makeStringAndClear() );
        }
    }

    SvXMLElementExport aElem( GetExport(), XML_NAMESPACE_STYLE, XML_COLUMNS,
                              sal_True, sal_True );

    if( xPropSet.is() )
    {
        Any aAny = xPropSet->getPropertyValue( sSeparatorLineIsOn );
        if( *(sal_Bool *)aAny.getValue() )
        {
            // style:width
            aAny = xPropSet->getPropertyValue( sSeparatorLineWidth );
            sal_Int32 nWidth(0);
            aAny >>= nWidth;
            GetExport().GetMM100UnitConverter().convertMeasure( sValue,
                                                                nWidth );
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_WIDTH,
                                      sValue.makeStringAndClear() );

            // style:color
            aAny = xPropSet->getPropertyValue( sSeparatorLineColor );
            sal_Int32 nColor(0);
            aAny >>= nColor;
            GetExport().GetMM100UnitConverter().convertColor( sValue,
                                                              nColor );
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_COLOR,
                                      sValue.makeStringAndClear() );

            // style:height
            aAny = xPropSet->getPropertyValue( sSeparatorLineRelativeHeight );
            sal_Int8 nHeight(0);
            aAny >>= nHeight;
            GetExport().GetMM100UnitConverter().convertPercent( sValue,
                                                                nHeight );
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_HEIGHT,
                                      sValue.makeStringAndClear() );

            // style:vertical-align
            aAny = xPropSet->getPropertyValue( sSeparatorLineVerticalAlignment );
            VerticalAlignment eVertAlign;
            aAny >>= eVertAlign;

            enum XMLTokenEnum eStr = XML_TOKEN_INVALID;
            switch( eVertAlign )
            {
            case VerticalAlignment_MIDDLE: eStr = XML_MIDDLE; break;
            case VerticalAlignment_BOTTOM: eStr = XML_BOTTOM; break;
            default: break;
            }

            if( eStr != XML_TOKEN_INVALID)
                GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                          XML_VERTICAL_ALIGN, eStr );

            // style:column-sep
            SvXMLElementExport aLclElem( GetExport(), XML_NAMESPACE_STYLE,
                                      XML_COLUMN_SEP,
                                      sal_True, sal_True );
        }
    }

    while( nCount-- )
    {
        // style:rel-width
        GetExport().GetMM100UnitConverter().convertNumber( sValue,
                                                       pColumns->Width );
        sValue.append( (sal_Unicode)'*' );
        GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_REL_WIDTH,
                                  sValue.makeStringAndClear() );

        // fo:margin-left
        GetExport().GetMM100UnitConverter().convertMeasure( sValue,
                                                       pColumns->LeftMargin );
        GetExport().AddAttribute( XML_NAMESPACE_FO, XML_MARGIN_LEFT,
                                       sValue.makeStringAndClear() );

        // fo:margin-right
        GetExport().GetMM100UnitConverter().convertMeasure( sValue,
                                                       pColumns->RightMargin );
        GetExport().AddAttribute( XML_NAMESPACE_FO, XML_MARGIN_RIGHT,
                                    sValue.makeStringAndClear() );

        // style:column
        SvXMLElementExport aLclElem( GetExport(), XML_NAMESPACE_STYLE, XML_COLUMN,
                                  sal_True, sal_True );
        pColumns++;
    }
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
