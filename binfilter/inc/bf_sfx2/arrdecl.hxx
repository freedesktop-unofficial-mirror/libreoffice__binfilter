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
#ifndef _SFX_ARRDECL_HXX
#define _SFX_ARRDECL_HXX

#include <vector>

#include <bf_svtools/svarray.hxx>
#include "bf_sfx2/minarray.hxx"
namespace binfilter {

class SfxObjectShell;
SV_DECL_PTRARR( SfxObjectShellArr_Impl, SfxObjectShell*, 4, 4 )

class SfxObjectFactory;
typedef SfxObjectFactory* SfxObjectFactoryPtr;
SV_DECL_PTRARR( SfxObjectFactoryArr_Impl, SfxObjectFactoryPtr, 3, 3 )

class SfxModule;
SV_DECL_PTRARR( SfxModuleArr_Impl, SfxModule*, 2, 2 )

class SfxFilter;
DECL_PTRARRAY( SfxFilterArr_Impl, SfxFilter*, 4, 4 )

typedef ::std::vector<  SfxFilter* > SfxFilterList_Impl;

class SfxSlot;
typedef SfxSlot* SfxSlotPtr;
SV_DECL_PTRARR( SfxSlotArr_Impl, SfxSlotPtr, 20, 20 )

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
