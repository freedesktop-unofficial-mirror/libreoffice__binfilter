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
#ifndef _SFXMODULE_HXX
#define _SFXMODULE_HXX  // intern
#define _SFXMOD_HXX     // extern

#include <bf_sfx2/shell.hxx>

#include <sal/types.h>

class ResMgr;

namespace binfilter {

class SfxObjectFactory;
class SfxObjectFactory;
class SfxModuleArr_Impl;
class SfxModule_Impl;
class SfxSlotPool;

class ISfxModule
{
public:
    virtual                 ~ISfxModule(){};
    virtual ResMgr*         GetResMgr() = 0;
};

//====================================================================

class SfxModule : public SfxShell, public ISfxModule
{
private:
    ResMgr*                     pResMgr;
    sal_Bool                    bDummy : 1;

protected:
    virtual sal_Bool                QueryUnload();

public:
                                TYPEINFO();

                                SfxModule( ResMgr* pMgrP, sal_Bool bDummy,
                                    SfxObjectFactory* pFactoryP, ... );
                                ~SfxModule();

    virtual SfxModule*          Load();
    virtual void                Free();
    sal_Bool                        IsLoaded() const { return !bDummy; }

    virtual ResMgr*             GetResMgr();

#if _SOLAR__PRIVATE
    static SfxModuleArr_Impl&   GetModules_Impl();
#endif
};

#define SFX_IMPL_MODULE_LIBRARY( LibName )                                  \
                                                                            \
        extern "C" void _CDECLARE_ Init##LibName##Dll()                     \
        {                                                                   \
            LibName##DLL::Init();                                           \
        }                                                                   \
        extern "C" void _CDECLARE_ DeInit##LibName##Dll()                   \
        {                                                                   \
            LibName##DLL::Exit();                                           \
        }

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
