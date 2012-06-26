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

#include <vcl/virdev.hxx>

#include <bf_svtools/ehdl.hxx>

#include <bf_svx/eeitem.hxx>
#include <bf_svx/svdfield.hxx>
#include <bf_svx/outliner.hxx>

#define _SD_DLL                 // fuer SD_MOD()
#include "optsitem.hxx"
#include "bf_sd/docshell.hxx"
#include "drawdoc.hxx"
#include "glob.hrc"
#include "strings.hrc"

#include <legacysmgr/legacy_binfilters_smgr.hxx>

namespace binfilter {

TYPEINIT1( SdModuleDummy, SfxModule );
TYPEINIT1( SdModule, SdModuleDummy );

SFX_IMPL_MODULE_DLL(Sd)

SdModule::SdModule(SvFactory* pDrawObjFact, SvFactory* pGraphicObjFact)
: SdModuleDummy(SFX_APP()->CreateResManager("bf_sd"), FALSE, pDrawObjFact, pGraphicObjFact)
, pImpressOptions(NULL)
, pDrawOptions(NULL)
{
    SetName( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "StarDraw" ) ) );  // Nicht uebersetzen!
    StartListening( *SFX_APP() );

    mpErrorHdl = new SfxErrorHandler( RID_SD_ERRHDL,
                                         ERRCODE_AREA_SD,
                                         ERRCODE_AREA_SD_END,
                                         GetResMgr() );

    mpVirtualRefDevice = new VirtualDevice;
    mpVirtualRefDevice->SetMapMode( MAP_100TH_MM );
}

SdModule::~SdModule()
{
    delete mpErrorHdl;
    delete static_cast< VirtualDevice* >( mpVirtualRefDevice );
}

SfxModule* SdModuleDummy::Load()
{
    return (NULL);
}

SfxModule* SdModule::Load()
{
    return (this);
}

IMPL_LINK(SdModule, CalcFieldValueHdl, EditFieldInfo*, pInfo)
{
    if( pInfo )
    {
        const String aStr( RTL_CONSTASCII_USTRINGPARAM( "???" ) );
        pInfo->SetRepresentation( aStr );
    }

    return(0);
}

void SdModule::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint )
{
    if( rHint.ISA( SfxSimpleHint ) &&
        ( (SfxSimpleHint&) rHint ).GetId() == SFX_HINT_DEINITIALIZING )
    {
         delete pImpressOptions, pImpressOptions = NULL;
         delete pDrawOptions, pDrawOptions = NULL;
    }
}

void SdModule::Free()
{
}

SdOptions* SdModule::GetSdOptions(DocumentType eDocType)
{
    SdOptions* pOptions = NULL;
    if (eDocType == DOCUMENT_TYPE_DRAW)
    {
        if (!pDrawOptions)
            pDrawOptions = new SdOptions( SDCFG_DRAW );
        pOptions = pDrawOptions;
    }
    else if (eDocType == DOCUMENT_TYPE_IMPRESS)
    {
        if (!pImpressOptions)
            pImpressOptions = new SdOptions( SDCFG_IMPRESS );
        pOptions = pImpressOptions;
    }
    return(pOptions);
}

OutputDevice* SdModule::GetVirtualRefDevice (void)
{
    return mpVirtualRefDevice;
}

OutputDevice* SdModule::GetRefDevice (SdDrawDocShell& /*rDocShell*/)
{
    return GetVirtualRefDevice();
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
