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

#include "durationhdl.hxx"


#include <com/sun/star/util/DateTime.hpp>

#include <rtl/ustrbuf.hxx>

#include "xmluconv.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;

// ---------------------------------------------------------------------------


sal_Bool XMLDurationMS16PropHdl_Impl::importXML(
        const OUString& rStrImpValue,
           Any& rValue,
        const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    DateTime aTime;
    if( !SvXMLUnitConverter::convertTime( aTime,  rStrImpValue ) )
        return false;

    const sal_Int16 nMS = ( ( aTime.Hours * 60 + aTime.Minutes ) * 60 + aTime.Seconds ) * 100 + aTime.HundredthSeconds;
    rValue <<= nMS;

    return sal_True;
}

sal_Bool XMLDurationMS16PropHdl_Impl::exportXML(
        OUString& rStrExpValue,
        const Any& rValue,
        const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    sal_Int16 nMS(0);

    if(rValue >>= nMS)
    {
        OUStringBuffer aOut;
        DateTime aTime( nMS, 0, 0, 0, 0, 0, 0 );
        SvXMLUnitConverter::convertTime( aOut, aTime );
        rStrExpValue = aOut.makeStringAndClear();
        return sal_True;
    }

    return sal_False;
}

XMLDurationMS16PropHdl_Impl::~XMLDurationMS16PropHdl_Impl()
{
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
