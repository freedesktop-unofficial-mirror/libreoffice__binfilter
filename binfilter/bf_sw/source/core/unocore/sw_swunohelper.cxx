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

#define _SVSTDARR_STRINGS

#include <com/sun/star/uno/Sequence.h>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/ucb/XContentIdentifier.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#include <com/sun/star/ucb/TransferInfo.hpp>
#include <com/sun/star/ucb/NameClash.hdl>
#include <com/sun/star/sdbc/XResultSet.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/util/DateTime.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <comphelper/processfactory.hxx>
#include <comphelper/types.hxx>
#include <tools/urlobj.hxx>
#include <tools/datetime.hxx>
#include <tools/debug.hxx>
#include <ucbhelper/contentidentifier.hxx>
#include <ucbhelper/contentbroker.hxx>
#include <ucbhelper/content.hxx>
#include <bf_svtools/svstdarr.hxx>

#include <swunohelper.hxx>
#include <osl/diagnose.h>
#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {
namespace SWUnoHelper {

sal_Int32 GetEnumAsInt32( const ::com::sun::star::uno::Any& rVal )
{
    sal_Int32 eVal;
    try
    {
        eVal = comphelper::getEnumAsINT32( rVal );
    }
    catch( ::com::sun::star::uno::Exception & )
    {
        eVal = 0;
        OSL_ENSURE( FALSE, "can't get EnumAsInt32" );
    }
    return eVal;
}

}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
