/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: cfgmgr.hxx,v $
 * $Revision: 1.6 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
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
    BOOL            bModified;

                    // to prevent from using
                    SfxConfigManager( const SfxConfigManager& );
                    const SfxConfigManager& operator=( const SfxConfigManager& );

    BOOL            LoadConfiguration( SotStorage& rStorage );
    BOOL            StoreConfiguration_Impl( SotStorage* pStorage=NULL );

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
    String          GetURL();

                    // construct a configmanager from a storage
                    // pStor == NULL means default config manager ( soffice.cfg )
                    SfxConfigManager( SotStorage* pStor = NULL );

                    // construct a configmanager from a documents' storage
                    SfxConfigManager( SfxObjectShell& rDoc );
                    ~SfxConfigManager();

    SotStorage*     GetConfigurationStorage( SotStorage* );

    void            AddConfigItem( SfxConfigItem& rCItem );
    void            RemoveConfigItem( SfxConfigItem& rCItem );
    void            CopyConfigItem( SfxConfigManager& rMgr, USHORT nId );
    void            RemovePersistentConfigItem( USHORT nType );
    SfxConfigItem*  GetNextItem( SfxConfigItem& rCItem );
    BOOL            HasConfigItem( USHORT nType );
    void            ResetConfigItem( USHORT nType );
    USHORT          GetErrorCode()
                    { return nErrno; }

                    // store the whole configuration into a storage
                    // pStore == NULL means store into own storage
    BOOL            StoreConfiguration( SotStorage* pStorage=NULL );

    BOOL            LoadConfigItem( SfxConfigItem& );
    BOOL            StoreConfigItem( SfxConfigItem& );
    BOOL            StoreAlwaysConfigItem( SfxConfigItem& );

                    // Reload all items of given type
    void            ReInitialize( USHORT nType );
    void            ReConnect( USHORT nType, SfxConfigManager* );

                    // Reload all items using a special stream
    void            ReInitialize( const String& rStreamName );

                    // Reload all items of given type except one
    void            ReInitialize( SfxConfigItem* );

    void            SetModified(BOOL);
    BOOL            IsModified()
                    { return bModified; }
    SfxObjectShell* GetObjectShell() const
                    { return pObjShell; }
};

}//end of namespace binfilter
#endif // #ifndef _SFXCFGMGR_HXX

