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
#ifndef _SFXCFGITEM_HXX
#define _SFXCFGITEM_HXX
class SotStorage;
class String;
namespace binfilter {

class SfxConfigManager;
class SfxShell;

#define SFX_ITEMTYPE_ACCEL               1
#define SFX_ITEMTYPE_MENU                2
#define SFX_ITEMTYPE_TOOLBOX             3
#define SFX_ITEMTYPE_STATBAR             4
#define SFX_ITEMTYPE_DIALOGCONFIG        5
#define SFX_ITEMTYPE_IMAGELIST           6
#define SFX_ITEMTYPE_OPTIONS             7
#define SFX_ITEMTYPE_MAILCONFIG          8
#define SFX_ITEMTYPE_TOOLBOXCONFIG       9
#define SFX_ITEMTYPE_APPEVENTCONFIG     10
#define SFX_ITEMTYPE_DOCEVENTCONFIG     11
#define SFX_ITEMTYPE_PLUGINSTATUSBAR    12
#define SFX_ITEMTYPE_HTMLCONFIG         13
#define SFX_ITEMTYPE_AUTOCORRCONFIG     14
#define SFX_ITEMTYPE_SPELLCONFIG        15
#define SFX_ITEMTYPE_MISCCONFIG         16
#define SFX_ITEMTYPE_APPEARCONFIG       17
#define SFX_ITEMTYPE_SVXSEARCHPARAMS    18
#define SFX_ITEMTYPE_FILTERCONFIG       19

#define SFX_ITEMTYPE_INTERFACE_START    20
#define SFX_ITEMTYPE_INTERFACE_END     300
}//end of namespace binfilter
#include <bf_svtools/bf_solar.h>
namespace binfilter {
class SfxConfigItem
{
    SfxConfigManager*   m_pCfgMgr;
    const USHORT        m_nType;
    BOOL                m_bDefault : 1;
    BOOL                m_bModified : 1;
    BOOL                m_bInitialized : 1;

protected:
                        SfxConfigItem( USHORT nType, SfxConfigManager* pCfgMgr );
                        ~SfxConfigItem();

public:

    static String       GetStreamName( USHORT nType );
                        enum {
                            ERR_OK,
                            WARNING_VERSION,
                            ERR_READ
                        };

            BOOL        Initialize();
            BOOL        StoreConfig();
            void        Connect( SfxConfigManager* pMgr );

    virtual int         Load(SotStorage& rStorage) = 0;
    virtual BOOL        Store(SotStorage& rStorage) = 0;
    virtual String      GetStreamName() const = 0;
    virtual void        UseDefault() = 0;

            void        SetDefault( BOOL bOn = TRUE );
            void        SetModified( BOOL bSet = TRUE );

            BOOL        IsDefault() const
                        { return m_bDefault; }
            BOOL        IsModified()
                        { return m_bModified; }
            USHORT      GetType() const
                        { return m_nType; }
            void        ReleaseConfigManager()
                        { m_pCfgMgr = 0; }
    SfxConfigManager*   GetConfigManager() const
                        { return m_pCfgMgr; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
