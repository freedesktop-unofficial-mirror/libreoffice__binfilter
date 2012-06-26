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

#include <bf_svtools/solar.hrc>
#include "dialdll.hxx"
#include "dialmgr.hxx"
#define ITEMID_BRUSH 1
#include "brshitem.hxx"


#include <vcl/svapp.hxx>



#include <bf_svtools/filter.hxx>

#include <bf_svtools/wallitem.hxx>
namespace binfilter {

// struct DialogsResMgr --------------------------------------------------
/*N*/ DialogsResMgr::DialogsResMgr()
/*N*/ : pResMgr(0),
/*N*/   pGrapicFilter(0)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   ByteString aName( "bf_svx" );
/*N*/ #else
/*N*/   ByteString aName( "bf_svl" );
/*N*/ #endif
/*N*/     pResMgr = ResMgr::CreateResMgr( aName.GetBuffer(), Application::GetSettings().GetUILocale() );
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ DialogsResMgr::~DialogsResMgr()
/*N*/ {
/*N*/   delete pGrapicFilter;
/*N*/   delete pResMgr;
/*N*/ }

// class SvxDialogDll ----------------------------------------------------
/*N*/ SvxDialogDll::SvxDialogDll()
/*N*/ {
/*N*/   DBG_ASSERT( !(*GetAppData(BF_SHL_SVX)), "Ctor, but pointer not null" );
/*N*/
/*N*/   (*(DialogsResMgr**)GetAppData(BF_SHL_SVX)) = new DialogsResMgr;
/*N*/   SvxBrushItem::InitSfxLink();
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ SvxDialogDll::~SvxDialogDll()
/*N*/ {
/*N*/   DBG_ASSERT( (*GetAppData(BF_SHL_SVX)), "Dtor, pointer == null" );
/*N*/
/*N*/   delete (*(DialogsResMgr**)GetAppData(BF_SHL_SVX));
/*N*/   (*(DialogsResMgr**)GetAppData(BF_SHL_SVX)) = 0;
/*N*/   delete SfxBrushItemLink::Get();
/*N*/   (*(SfxBrushItemLink**)GetAppData(SHL_BRUSHITEM)) = 0;
/*N*/ }

// -----------------------------------------------------------------------


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
