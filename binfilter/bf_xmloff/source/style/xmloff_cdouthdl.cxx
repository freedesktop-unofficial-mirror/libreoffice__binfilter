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

#include <cdouthdl.hxx>


#include "xmluconv.hxx"

#include <rtl/ustrbuf.hxx>

#include <vcl/vclenum.hxx>


namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

SvXMLEnumMapEntry pXML_Crossedout_Enum[] =
{
    { XML_CROSSEDOUT_NONE,      STRIKEOUT_NONE },
    { XML_CROSSEDOUT_SINGLE,    STRIKEOUT_SINGLE },
    { XML_CROSSEDOUT_DOUBLE,    STRIKEOUT_DOUBLE },
    { XML_CROSSEDOUT_THICK,     STRIKEOUT_BOLD },
    { XML_CROSSEDOUT_SLASH,     STRIKEOUT_SLASH },
    { XML_CROSSEDOUT_CROSS,     STRIKEOUT_X }
};

///////////////////////////////////////////////////////////////////////////////
//
// class XMLPosturePropHdl
//

XMLCrossedOutPropHdl::~XMLCrossedOutPropHdl()
{
    // nothing to do
}

sal_Bool XMLCrossedOutPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_uInt16 eCross;

    if( ( bRet = rUnitConverter.convertEnum( eCross, rStrImpValue, pXML_Crossedout_Enum ) ) )
        rValue <<= (sal_Int16)eCross;

    return bRet;
}

sal_Bool XMLCrossedOutPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_Int16 nValue(0);
    OUStringBuffer aOut;

    if( rValue >>= nValue )
    {
        if( ( bRet = rUnitConverter.convertEnum( aOut, (sal_uInt16)nValue, pXML_Crossedout_Enum ) ) )
            rStrExpValue = aOut.makeStringAndClear();
    }

    return bRet;
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
