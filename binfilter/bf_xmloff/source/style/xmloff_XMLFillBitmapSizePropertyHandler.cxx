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


#include "xmluconv.hxx"

#include <rtl/ustrbuf.hxx>

#include "XMLFillBitmapSizePropertyHandler.hxx"

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::rtl;

XMLFillBitmapSizePropertyHandler::XMLFillBitmapSizePropertyHandler()
{
}

XMLFillBitmapSizePropertyHandler::~XMLFillBitmapSizePropertyHandler()
{
}

sal_Bool XMLFillBitmapSizePropertyHandler::importXML(
    const OUString& rStrImpValue,
    Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Int32 nValue;
    sal_Bool bRet;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) != -1 )
    {
        bRet = rUnitConverter.convertPercent( nValue, rStrImpValue );
        nValue *= -1;
    }
    else
    {
        bRet = rUnitConverter.convertMeasure( nValue, rStrImpValue );
    }

    if( bRet )
        rValue <<= nValue;

    return bRet;
}

sal_Bool XMLFillBitmapSizePropertyHandler::exportXML(
    OUString& rStrExpValue,
    const Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut;

    sal_Int32 nValue(0);
    if( rValue >>= nValue )
    {
        if( nValue < 0 )
        {
            rUnitConverter.convertPercent( aOut, -nValue );
        }
        else
        {
            rUnitConverter.convertMeasure( aOut, nValue );
        }

        rStrExpValue = aOut.makeStringAndClear();
        return sal_True;
    }

    return sal_False;
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
