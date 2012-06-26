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


#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/style/NumberingType.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include "XMLTextNumRuleInfo.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::style;

XMLTextNumRuleInfo::XMLTextNumRuleInfo() :
    sNumberingRules(RTL_CONSTASCII_USTRINGPARAM("NumberingRules")),
    sNumberingLevel(RTL_CONSTASCII_USTRINGPARAM("NumberingLevel")),
    sNumberingStartValue(RTL_CONSTASCII_USTRINGPARAM("NumberingStartValue")),
    sParaIsNumberingRestart(RTL_CONSTASCII_USTRINGPARAM("ParaIsNumberingRestart")),
    sNumberingType(RTL_CONSTASCII_USTRINGPARAM("NumberingType")),
    sIsNumbering(RTL_CONSTASCII_USTRINGPARAM("IsNumbering")),
    sNumberingIsNumber(RTL_CONSTASCII_USTRINGPARAM("NumberingIsNumber"))
{
    Reset();
}

void XMLTextNumRuleInfo::Set(
        const ::com::sun::star::uno::Reference <
            ::com::sun::star::text::XTextContent > & xTextContent )
{
    Reset();

    Reference< XPropertySet > xPropSet( xTextContent, UNO_QUERY );
    Reference< XPropertySetInfo > xPropSetInfo = xPropSet->getPropertySetInfo();

    Any aAny;

    // check if this paragraph supports a numbering
    if( !xPropSetInfo->hasPropertyByName( sNumberingLevel ) )
        return;

    if( xPropSetInfo->hasPropertyByName( sNumberingRules ) )
    {
        aAny = xPropSet->getPropertyValue( sNumberingRules );
        aAny >>= xNumRules;
    }

    if( xNumRules.is() )
    {
        Reference < XNamed > xNamed( xNumRules, UNO_QUERY );
        if( xNamed.is() )
        {
            bIsNamed = sal_True;
            sName = xNamed->getName();
        }

        aAny = xPropSet->getPropertyValue( sNumberingLevel );
        aAny >>= nLevel;

        bIsNumbered = sal_True;
        if( xPropSetInfo->hasPropertyByName( sNumberingIsNumber ) )
        {
            aAny = xPropSet->getPropertyValue( sNumberingIsNumber );
            bIsNumbered = *(sal_Bool *)aAny.getValue();
        }

        if( bIsNumbered )
        {
            if( xPropSetInfo->hasPropertyByName( sParaIsNumberingRestart ) )
            {
                aAny = xPropSet->getPropertyValue( sParaIsNumberingRestart );
                bIsRestart = *(sal_Bool *)aAny.getValue();
            }
            if( xPropSetInfo->hasPropertyByName( sNumberingStartValue ) )
            {
                aAny = xPropSet->getPropertyValue( sNumberingStartValue );
                aAny >>= nStartValue;
            }
        }

        OSL_ENSURE( nLevel < xNumRules->getCount(), "wrong num rule level" );
        if( nLevel >= xNumRules->getCount() )
        {
            Reset();
            return;
        }

        aAny = xNumRules->getByIndex( nLevel );
        Sequence<PropertyValue> aProps;
        aAny >>= aProps;
        const PropertyValue* pPropArray = aProps.getConstArray();
        sal_Int32 nCount = aProps.getLength();
        for( sal_Int32 i=0; i<nCount; i++ )
        {
            const beans::PropertyValue& rProp = pPropArray[i];

            if( rProp.Name == sNumberingType )
            {
                sal_Int16 nType(0);
                rProp.Value >>= nType;
                if( NumberingType::CHAR_SPECIAL != nType &&
                    NumberingType::BITMAP != nType )
                {
                    bIsOrdered = sal_True;
                }
                break;
            }
        }
        nLevel++;
    }
}



}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
