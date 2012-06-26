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
#ifndef _SFXCFGMGR_HXX
#define _SFXCFGMGR_HXX

#include <bf_so3/svstor.hxx>
class SvStream;
class String;
namespace binfilter {

class SfxObjectShell;
class SfxConfigItem;
class SfxConfigItemArr_Impl;
struct SfxConfigItem_Impl;
class SfxConfigManager
{
private:
    SotStorageRef   m_xStorage;
    SfxObjectShell* pObjShell;
    SfxConfigItemArr_Impl* pItemArr;
    USHORT          nErrno;

                    // to prevent from using
                    SfxConfigManager( const SfxConfigManager& );
                    const SfxConfigManager& operator=( const SfxConfigManager& );

    BOOL            LoadConfiguration( SotStorage& rStorage );

public:
                    enum Error {
                        ERR_NO,
                        ERR_READ,
                        ERR_WRITE,
                        ERR_OPEN,
                        ERR_FILETYPE,
                        ERR_VERSION,
                        ERR_IMPORT,
                        ERR_EXPORT
                    };

    static String   GetStorageName();
    static BOOL     HasConfiguration( SotStorage& rStorage );

                    // construct a configmanager from a storage
                    // pStor == NULL means default config manager ( soffice.cfg )
                    SfxConfigManager( SotStorage* pStor = NULL );

                    // construct a configmanager from a documents' storage
                    SfxConfigManager( SfxObjectShell& rDoc );
                    ~SfxConfigManager();

    void            AddConfigItem( SfxConfigItem& rCItem );
    void            RemoveConfigItem( SfxConfigItem& rCItem );
    SfxConfigItem*  GetNextItem( SfxConfigItem& rCItem );
    USHORT          GetErrorCode()
                    { return nErrno; }

    BOOL            LoadConfigItem( SfxConfigItem& );
    BOOL            StoreAlwaysConfigItem( SfxConfigItem& );

    SfxObjectShell* GetObjectShell() const
                    { return pObjShell; }
};

}//end of namespace binfilter
#endif // #ifndef _SFXCFGMGR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
