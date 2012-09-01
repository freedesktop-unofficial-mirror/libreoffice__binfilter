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

#ifndef _SO2DLL_HXX
#define _SO2DLL_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/pstm.hxx>
#include <tools/link.hxx>
#include <tools/globname.hxx>
#include <vector>

#include "bf_so3/so3dllapi.h"

/*************************************************************************
*************************************************************************/
class SotFactory;
class SvAdviseSinkIndex;
class WorkWindow;
class MDIWindow;
class ImpSO2Clipboard;
class ResMgr;
class SvSoIPCServer;
class SvIPCServerInfo;
class Impl_DeathTimer;
class Timer;

namespace binfilter
{
class SvInPlaceClient;
class SvInPlaceClientList;
class ImplSvEditObjectProtocol;
class SvInPlaceEnvironment;
class SvVerbList;
struct SvBindingData;
class SvObjectList;
class ImpFactory;

class  SvContainerEnvironment;
typedef ::std::vector< SvContainerEnvironment* > SvContainerEnvironmentList;

//=========================================================================
struct SO3_DLLPUBLIC ConvertTo_Impl
/*  [Beschreibung]

    In dieser Struktur werden Informationen "uber den Vorg"anger und den
    Nachfolger von Datenformaten und dazugeh"origen CLSId's gepflegt.
    Die Struktur kann nur in einem Array sinnvoll eingesetzt werden.
*/
{
    SvGlobalName    aName;          // CLSID    des Servers
    SvGlobalName    aSvName;        // Starview-Klasse die diese CLSID supported
    long            aFormat;        // Format

    ConvertTo_Impl() {};
    ConvertTo_Impl( const SvGlobalName & a1, long a2 )
        : aName( a1 )
        , aSvName( a1 )
        , aFormat( a2 )
    {}
    ConvertTo_Impl( const SvGlobalName & a1,
                    const SvGlobalName & rSvClass,
                    long a2 )
        : aName( a1 )
        , aSvName( rSvClass )
        , aFormat( a2 )
    {}
};
#define SO3_OFFICE_VERSIONS 5

class SO3_DLLPUBLIC SoDll
{
friend class ImpFactory;
friend class SvFactory;
friend class Impl_DeathTimer;
    BOOL            bInit;
    BOOL            bSelfInit;
    ResMgr*         pResMgr;

public:
    // Factories
    SotFactory *     pSvObjectFactory;
    SotFactory *     pSvStorageStreamFactory;
    SotFactory *     pSvStorageFactory;
    SotFactory *     pSvEmbeddedObjectFactory;
    SotFactory *     pSvEmbeddedClientFactory;
    SotFactory *     pSvInPlaceObjectFactory;
    SotFactory *     pSvPlugInObjectFactory;
    SotFactory *     pSvAppletObjectFactory;
    SotFactory *     pSvInPlaceClientFactory;
    SotFactory *     pSvPersistFactory;
    SotFactory *     pSvPseudoObjectFactory;
    SotFactory *     pSvSimplePersistFactory;
    SotFactory *     pSvObjectContainerFactory;
    SotFactory *     pSvFactory_ImplFactory;
    SotFactory *     pDfltPlugInFactory;
    SotFactory *     pDfltAppletFactory;
    SotFactory *     pSoBindingFactory;

    // Listen
    SvContainerEnvironmentList *pContEnvList;

    // InPlace-Bearbeitung
    SvInPlaceClientList *       pIPActiveClientList;
    SvInPlaceEnvironment *      pUIShowIPEnv;
    ImplSvEditObjectProtocol *  pIEOPDflt;

    // Sonstiges
    SvClassManager              aInfoClassMgr;
    SvGlobalName                aSvInterface;

    // PlugIn
    SvVerbList *                pPlugInVerbList;
    ULONG                       nPlugInDocFormat;

    // PlugIn
    SvVerbList *                pAppletVerbList;
    ULONG                       nAppletDocFormat;

    Timer *                     pDeathTimer;
    void *                      pDead;
    SvBindingData*              pBindingData;
    ConvertTo_Impl              (*pConvTable)[SO3_OFFICE_VERSIONS];
    USHORT                      nConvTableEntries;

                            SoDll();
                            ~SoDll();
    ResMgr *                GetResMgr();
    SvIPCServerInfo *       GetIPCServerInfo();

    static SoDll*           GetOrCreate();
};

}
#endif //_SO2DLL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
