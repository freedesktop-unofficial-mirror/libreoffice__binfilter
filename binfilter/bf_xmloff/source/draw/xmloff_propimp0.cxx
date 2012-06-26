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

#include <bf_tools/string.hxx>

#include <rtl/ustrbuf.hxx>

#include "propimp0.hxx"


#include <com/sun/star/util/DateTime.hpp>


#include <xmluconv.hxx>
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

//////////////////////////////////////////////////////////////////////////////
// implementation of graphic property Stroke


//////////////////////////////////////////////////////////////////////////////
// implementation of presentation page property Change

//////////////////////////////////////////////////////////////////////////////
// implementation of an effect duration property handler


XMLDurationPropertyHdl::~XMLDurationPropertyHdl()
{
}

sal_Bool XMLDurationPropertyHdl::importXML(
    const OUString& rStrImpValue,
    ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    util::DateTime aTime;
    SvXMLUnitConverter::convertTime( aTime,  rStrImpValue );

    const sal_Int32 nSeconds = ( aTime.Hours * 60 + aTime.Minutes ) * 60 + aTime.Seconds;
    rValue <<= nSeconds;

    return sal_True;
}

sal_Bool XMLDurationPropertyHdl::exportXML(
    OUString& rStrExpValue,
    const ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    sal_Int32 nVal = 0;

    if(rValue >>= nVal)
    {
        util::DateTime aTime( 0, (sal_uInt16)nVal, 0, 0, 0, 0, 0 );

        OUStringBuffer aOut;
        SvXMLUnitConverter::convertTime( aOut, aTime );
        rStrExpValue = aOut.makeStringAndClear();
        return sal_True;
    }

    return sal_False;
}

//////////////////////////////////////////////////////////////////////////////
// implementation of an opacity property handler


XMLOpacityPropertyHdl::~XMLOpacityPropertyHdl()
{
}

sal_Bool XMLOpacityPropertyHdl::importXML(
    const OUString& rStrImpValue,
    ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_Int32 nValue = 0;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) != -1 )
    {
        if( rUnitConverter.convertPercent( nValue, rStrImpValue ) )
        {
            rValue <<= sal_uInt16( nValue );
            bRet = sal_True;
        }
    }
    else
    {
        const String aStr( rStrImpValue );
        double fVal = aStr.ToDouble() * 100.0;
        rValue <<= sal_uInt16( fVal );
        bRet = sal_True;
    }

    return bRet;
}

sal_Bool XMLOpacityPropertyHdl::exportXML(
    OUString& rStrExpValue,
    const ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_uInt16 nVal = 0;

    if( rValue >>= nVal )
    {
        OUStringBuffer aOut;

        rUnitConverter.convertPercent( aOut, nVal );
        rStrExpValue = aOut.makeStringAndClear();
        bRet = sal_True;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////////////
// implementation of an text animation step amount

XMLTextAnimationStepPropertyHdl::~XMLTextAnimationStepPropertyHdl()
{
}

sal_Bool XMLTextAnimationStepPropertyHdl::importXML(
    const OUString& rStrImpValue,
    ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_Int32 nValue = 0;

    const OUString aPX( RTL_CONSTASCII_USTRINGPARAM( "px" ) );
    sal_Int32 nPos = rStrImpValue.indexOf( aPX );
    if( nPos != -1 )
    {
        if( rUnitConverter.convertNumber( nValue, rStrImpValue.copy( 0, nPos ) ) )
        {
            rValue <<= sal_Int16( -nValue );
            bRet = sal_True;
        }
    }
    else
    {
        if( rUnitConverter.convertMeasure( nValue, rStrImpValue ) )
        {
            rValue <<= sal_Int16( nValue );
            bRet = sal_True;
        }
    }

    return bRet;
}

sal_Bool XMLTextAnimationStepPropertyHdl::exportXML(
    OUString& rStrExpValue,
    const ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_Int16 nVal = 0;

    if( rValue >>= nVal )
    {
        OUStringBuffer aOut;

        if( nVal < 0 )
        {
            const OUString aPX( RTL_CONSTASCII_USTRINGPARAM( "px" ) );
            rUnitConverter.convertNumber( aOut, (sal_Int32)-nVal );
            aOut.append( aPX );
        }
        else
        {
            rUnitConverter.convertMeasure( aOut, nVal );
        }

        rStrExpValue = aOut.makeStringAndClear();
        bRet = sal_True;
    }

    return bRet;
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
