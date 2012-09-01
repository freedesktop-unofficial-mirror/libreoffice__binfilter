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

#include <XMLCalculationSettingsContext.hxx>
#include <com/sun/star/text/XTextDocument.hpp>
#include "xmlimp.hxx"
#include "nmspmap.hxx"
#include "xmlnmspe.hxx"
#include "xmluconv.hxx"
namespace binfilter {


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::text;
using namespace ::binfilter::xmloff::token;

using rtl::OUString;

XMLCalculationSettingsContext::XMLCalculationSettingsContext( SvXMLImport& rInImport,
                                    sal_uInt16 nInPrefix,
                                    const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                         ::com::sun::star::xml::sax::XAttributeList >& xAttrList )
    : SvXMLImportContext ( rInImport, nInPrefix, rLocalName )
    , nYear( 1930 )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nLclPrefix == XML_NAMESPACE_TABLE)
        {
            if ( IsXMLToken( aLclLocalName, XML_NULL_YEAR ) )
            {
                sal_Int32 nTemp;
                GetImport().GetMM100UnitConverter().convertNumber(nTemp, sValue);
                nYear= static_cast <sal_Int16> (nTemp);
            }
        }
    }
}

XMLCalculationSettingsContext::~XMLCalculationSettingsContext()
{
}
void XMLCalculationSettingsContext::EndElement()
{
    if (nYear != 1930 )
    {
        Reference < XTextDocument > xTextDoc ( GetImport().GetModel(), UNO_QUERY);
        if (xTextDoc.is())
        {
            Reference < XPropertySet > xPropSet ( xTextDoc, UNO_QUERY );
            OUString sTwoDigitYear ( RTL_CONSTASCII_USTRINGPARAM ( "TwoDigitYear" ) );
            Any aAny;
            aAny <<= nYear;
            xPropSet->setPropertyValue ( sTwoDigitYear, aAny );
        }
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
