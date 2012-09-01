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



#define _SVSTDARR_STRINGSDTOR

#include <bf_sfx2/event.hxx>
#include <bf_svtools/colorcfg.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svtools/whiter.hxx>
#include <bf_svtools/isethint.hxx>
#include <bf_svtools/ctloptions.hxx>


#include <horiornt.hxx>

#include <viewsh.hxx>
#include <cmdid.h>          // Funktion-Ids
#include <swmodule.hxx>
#include <wdocsh.hxx>
#include <doc.hxx>
#include <app.hrc>
#include <usrpref.hxx>
#include <prtopt.hxx>
#include <modcfg.hxx>
#include <fontcfg.hxx>
#include <barcfg.hxx>
#include <dbconfig.hxx>

#include <bf_sfx2/app.hxx>
#include <bf_svx/svxids.hrc>

// #107253#

using namespace ::com::sun::star;

#include <cfgid.h>

#include <shells.hrc>
#include "bf_so3/staticbaseurl.hxx"

namespace binfilter {

/*M*/ void SwModule::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint )
/*M*/ {
/*M*/   if( rHint.ISA( SfxEventHint ) )
/*M*/   {
/*M*/   }
/*M*/   else if(rHint.ISA(SfxItemSetHint))
/*M*/   {
/*M*/       if( SFX_ITEM_SET == ((SfxItemSetHint&)rHint).GetItemSet().
/*M*/                   GetItemState( SID_ATTR_ADDRESS, sal_False ))
/*M*/           bAuthorInitialised = FALSE;
/*M*/   }
/*M*/   else if(rHint.ISA(SfxSimpleHint))
/*M*/   {
/*M*/         ULONG nHintId = ((SfxSimpleHint&)rHint).GetId();
/*M*/         if(SFX_HINT_DEINITIALIZING == nHintId)
/*M*/         {
/*M*/             DELETEZ(pWebUsrPref);
/*M*/             DELETEZ(pUsrPref)   ;
/*M*/             DELETEZ(pModuleConfig);
/*M*/             DELETEZ(pPrtOpt)      ;
/*M*/             DELETEZ(pWebPrtOpt)   ;
/*M*/             DELETEZ(pStdFontConfig)     ;
/*M*/             DELETEZ(pAuthorNames)       ;
/*M*/             DELETEZ(pDBConfig);
/*M*/             EndListening(*pColorConfig);
/*M*/             DELETEZ(pColorConfig);
/*N*/             EndListening(*pCTLOptions);
/*N*/             DELETEZ(pCTLOptions);
/*M*/         }
/*M*/   }
/*M*/ }

/*N*/ SwDBConfig*   SwModule::GetDBConfig()
/*N*/ {
/*N*/   if(!pDBConfig)
/*N*/       pDBConfig = new SwDBConfig;
/*N*/   return pDBConfig;
/*N*/ }

/*N*/ ColorConfig& SwModule::GetColorConfig()
/*N*/ {
/*N*/     if(!pColorConfig)
/*N*/   {
/*N*/         pColorConfig = new ColorConfig;
/*N*/       SwViewOption::ApplyColorConfigValues(*pColorConfig);
/*N*/         StartListening(*pColorConfig);
/*N*/     }
/*N*/     return *pColorConfig;
/*N*/ }

SvtCTLOptions& SwModule::GetCTLOptions()
{
    if(!pCTLOptions)
    {
        pCTLOptions = new SvtCTLOptions;
        StartListening(*pCTLOptions);
    }
    return *pCTLOptions;
}

/*N*/ const SwMasterUsrPref *SwModule::GetUsrPref(sal_Bool bWeb) const
/*N*/ {
/*N*/   SwModule* pNonConstModule = (SwModule*)this;
/*N*/   if(bWeb && !pWebUsrPref)
/*N*/   {
/*N*/       // im Load der SwMasterUsrPref wird der SpellChecker gebraucht, dort darf
/*N*/       // er aber nicht angelegt werden #58256#
/*N*/       pNonConstModule->pWebUsrPref = new SwMasterUsrPref(TRUE);
/*N*/   }
/*N*/   else if(!bWeb && !pUsrPref)
/*N*/   {
/*N*/       pNonConstModule->pUsrPref = new SwMasterUsrPref(FALSE);
/*N*/   }
/*N*/   return  bWeb ? pWebUsrPref : pUsrPref;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
