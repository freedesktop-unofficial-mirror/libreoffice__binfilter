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

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/util/XURLTransformer.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/util/XFlushable.hpp>

#include <stdlib.h>

#include <tools/config.hxx>
#include <vcl/sound.hxx>
#include <vcl/msgbox.hxx>

#include <bf_tools/string.hxx>

#include <bf_svtools/itempool.hxx>
#include <bf_svtools/aeitem.hxx>
#include <bf_svtools/slstitm.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svtools/intitem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svtools/szitem.hxx>
#include <bf_svtools/undo.hxx>

#define _SVSTDARR_STRINGS
#include <bf_svtools/svstdarr.hxx>

#include <bf_svtools/ttprops.hxx>
#include <sfxsids.hrc>
#include <sot/exchange.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif


#include <bf_svtools/isethint.hxx>

#include <unotools/configmgr.hxx>
#include <tools/urlobj.hxx>
#include <tools/wldcrd.hxx>
#include <bf_svtools/saveopt.hxx>
#include <bf_svtools/helpopt.hxx>
#include <bf_svtools/undoopt.hxx>
#include <bf_svtools/securityoptions.hxx>
#include <bf_svtools/pathoptions.hxx>
#include <bf_svtools/inetoptions.hxx>
#include <bf_svtools/miscopt.hxx>
#include <vcl/toolbox.hxx>
#include <unotools/localfilehelper.hxx>
#include <comphelper/processfactory.hxx>
#include <rtl/ustrbuf.hxx>

#include "docfile.hxx"
#include "sfxtypes.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "request.hxx"
#include "evntconf.hxx"
#include "cfgmgr.hxx"
#include "appdata.hxx"
#include "misccfg.hxx"
#include "appimp.hxx"
#include "helper.hxx"   // SfxContentHelper::...
#include "app.hxx"

#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::beans;

//--------------------------------------------------------------------

/*N*/ SfxEventConfiguration* SfxApplication::GetEventConfig() const
/*N*/ {
/*N*/     if (!pAppData_Impl->pEventConfig)
/*N*/         pAppData_Impl->pEventConfig = new SfxEventConfiguration;
/*N*/     return pAppData_Impl->pEventConfig;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::NotifyEvent( const SfxEventHint& rEventHint, bool /*bSynchron*/ )
/*N*/ {
/*N*/     DBG_ASSERT(pAppData_Impl->pEventConfig,"Keine Events angemeldet!");
/*N*/
/*N*/     SfxObjectShell *pDoc = rEventHint.GetObjShell();
/*N*/     if ( pDoc )
/*N*/   {
/*N*/       if ( pDoc->IsPreview() )
/*N*/           return;
/*N*/   }
/*N*/
/*N*/     {
/*N*/         Broadcast(rEventHint);
/*N*/         if ( pDoc )
/*N*/             pDoc->Broadcast( rEventHint );
/*N*/     }
/*N*/ }

/*N*/ SfxMiscCfg* SfxApplication::GetMiscConfig()
/*N*/ {
/*N*/   if ( !pAppData_Impl->pMiscConfig )
/*N*/       pAppData_Impl->pMiscConfig = new SfxMiscCfg;
/*N*/
/*N*/   return pAppData_Impl->pMiscConfig;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
