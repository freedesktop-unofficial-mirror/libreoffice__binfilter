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


#include <chrhghdl.hxx>

#include "xmluconv.hxx"

#include "xmlehelp.hxx"

#include <rtl/ustrbuf.hxx>


namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// this is a copy of defines in svx/inc/escpitem.hxx
#define DFLT_ESC_PROP    58
#define DFLT_ESC_AUTO_SUPER 101
#define DFLT_ESC_AUTO_SUB  -101

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEscapementPropHdl
//

XMLCharHeightHdl::~XMLCharHeightHdl()
{
    // nothing to do
}

sal_Bool XMLCharHeightHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    double fSize;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) == -1 )
    {
        MapUnit eSrcUnit = SvXMLExportHelper::GetUnitFromString( rStrImpValue, MAP_POINT );
        if( SvXMLUnitConverter::convertDouble( fSize, rStrImpValue, eSrcUnit, MAP_POINT ))
        {
            rValue <<= (float)fSize;
            return sal_True;
        }
    }

    return sal_False;
}

sal_Bool XMLCharHeightHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    OUStringBuffer aOut;

    float fSize = 0;
    if( rValue >>= fSize )
    {
        SvXMLUnitConverter::convertDouble( aOut, (double)fSize, TRUE, MAP_POINT, MAP_POINT );
        aOut.append( sal_Unicode('p'));
        aOut.append( sal_Unicode('t'));
    }

    rStrExpValue = aOut.makeStringAndClear();
    return rStrExpValue.getLength() != 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEscapementHeightPropHdl
//

XMLCharHeightPropHdl::~XMLCharHeightPropHdl()
{
    // nothing to do
}

sal_Bool XMLCharHeightPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Int32 nPrc = 100;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) != -1 )
    {
        if( rUnitConverter.convertPercent( nPrc, rStrImpValue ) )
        {
            rValue <<= (sal_Int16)nPrc;
            return sal_True;
        }
    }

    return sal_False;
}

sal_Bool XMLCharHeightPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut( rStrExpValue );

    sal_Int16 nValue(0);
    if( rValue >>= nValue )
    {
        rUnitConverter.convertPercent( aOut, nValue );
    }

    rStrExpValue = aOut.makeStringAndClear();
    return rStrExpValue.getLength() != 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEscapementPropHdl
//

XMLCharHeightDiffHdl::~XMLCharHeightDiffHdl()
{
    // nothing to do
}

sal_Bool XMLCharHeightDiffHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    sal_Int32 nRel = 0;

    if( SvXMLUnitConverter::convertMeasure( nRel, rStrImpValue, MAP_POINT ) )
    {
        rValue <<= (float)nRel;
        return sal_True;
    }

    return sal_False;
}

sal_Bool XMLCharHeightDiffHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    OUStringBuffer aOut;

    float nRel = 0;
    if( (rValue >>= nRel) && (nRel != 0) )
    {
        SvXMLUnitConverter::convertMeasure( aOut, static_cast<sal_Int32>(nRel), MAP_POINT, MAP_POINT );
        rStrExpValue = aOut.makeStringAndClear();
    }

    return rStrExpValue.getLength() != 0;
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
