/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cfgmgr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:41:58 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
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

