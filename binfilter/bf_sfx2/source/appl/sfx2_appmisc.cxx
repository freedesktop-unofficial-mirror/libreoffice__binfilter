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

#include <vcl/status.hxx>
#include <vcl/msgbox.hxx>
#include <bf_svtools/whiter.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svtools/intitem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svtools/filter.hxx>
#include <bf_svtools/internaloptions.hxx>
#include <bf_svtools/pathoptions.hxx>

#include <com/sun/star/registry/InvalidRegistryException.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/util/XURLTransformer.hpp>
#include <com/sun/star/frame/XFramesSupplier.hpp>
#include <com/sun/star/uno/Reference.h>
#include <tools/config.hxx>
#include <tools/rcid.h>
#include <osl/mutex.hxx>
#ifdef _MSC_VER
#pragma hdrstop
#endif
#include <unotools/configmgr.hxx>
#include <com/sun/star/frame/XDesktop.hpp>

#include <unotools/ucbstreamhelper.hxx>
#include <framework/menuconfiguration.hxx>
#include <comphelper/processfactory.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/bootstrap.hxx>
#include <bf_svtools/moduleoptions.hxx>
#include <osl/file.hxx>

#include "app.hxx"
#include "appdata.hxx"
#include "cfgmgr.hxx"

#include <bf_svtools/imgdef.hxx>

#include "docfac.hxx"
#include "docfile.hxx"
#include "docfilt.hxx"
#include "request.hxx"
#include "fcontnr.hxx"
#include "sfx.hrc"
#include "module.hxx"
#include "openflag.hxx"
#include "appimp.hxx"

#include <legacysmgr/legacy_binfilters_smgr.hxx>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;

//===================================================================
namespace binfilter {


/*N*/ SfxProgress* SfxApplication::GetProgress() const
/*N*/ {
/*N*/     return pAppData_Impl->pProgress;
/*N*/ }

/*N*/ SfxCancelManager *SfxApplication::GetCancelManager() const
/*N*/ {
/*N*/   if ( !pAppData_Impl->pCancelMgr )
/*N*/   {
/*N*/       pAppData_Impl->pCancelMgr = new SfxCancelManager;
/*N*/   }
/*N*/   return pAppData_Impl->pCancelMgr;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
