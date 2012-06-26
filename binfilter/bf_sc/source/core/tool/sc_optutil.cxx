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


#include "optutil.hxx"
#include "global.hxx"       // for pSysLocale

#include <bf_svtools/syslocale.hxx>
namespace binfilter {

//------------------------------------------------------------------

// static
/*N*/ BOOL ScOptionsUtil::IsMetricSystem()
/*N*/ {
/*N*/   //! which language should be used here - system language or installed office language?
/*N*/
/*N*/ //    MeasurementSystem eSys = Application::GetAppInternational().GetMeasurementSystem();
/*N*/     MeasurementSystem eSys = ScGlobal::pLocaleData->getMeasurementSystemEnum();
/*N*/
/*N*/   return ( eSys == MEASURE_METRIC );
/*N*/ }

//------------------------------------------------------------------

/*N*/ ScLinkConfigItem::ScLinkConfigItem( const ::rtl::OUString rSubTree ) :
/*N*/   ConfigItem( rSubTree )
/*N*/ {
/*N*/ }

/*N*/ void ScLinkConfigItem::SetCommitLink( const Link& rLink )
/*N*/ {
/*N*/   aCommitLink = rLink;
/*N*/ }

void  ScLinkConfigItem::Notify( const com::sun::star::uno::Sequence< rtl::OUString >& )
{
}

void  ScLinkConfigItem::Commit()
{
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
