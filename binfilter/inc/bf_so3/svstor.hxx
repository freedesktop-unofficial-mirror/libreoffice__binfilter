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

#ifndef _SVSTOR_HXX
#define _SVSTOR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/iface.hxx>
#include <sot/storage.hxx>

#include <bf_so3/so2defs.hxx>

#include "bf_so3/so3dllapi.h"

#ifdef SvStorage
#undef SvStorage
#undef SvStorageRef
#undef SvStorageStream
#undef SvStorageStreamRef
#endif

namespace binfilter {

class SvStorage;
class StorageStream;

class SO3_DLLPUBLIC SvStorageStream : virtual public SvObject, public SotStorageStream
{
friend class SvStorage;
friend class ImpStream;
    void *   pObjI;      // Zeiger auf das Speichermedium
    void  *  pRelease;   // OLE-Spec, wenn Erzeuger zerstoert
    SO3_DLLPRIVATE virtual ULONG       GetData( void* pData, ULONG nSize );
    SO3_DLLPRIVATE virtual ULONG       PutData( const void* pData, ULONG nSize );
    SO3_DLLPRIVATE virtual ULONG       SeekPos( ULONG nPos );
    SO3_DLLPRIVATE virtual void        FlushData();
protected:
    SO3_DLLPRIVATE                  ~SvStorageStream();
public:
    static void         Ole2SvStreamMode( ULONG nOleMode,
                                        StreamMode *, StorageMode * );
    static ULONG        Sv2OleStreamMode( StreamMode, StorageMode );
                        SvStorageStream( BaseStorageStream *pStm );
                        SvStorageStream();
                        SO2_DECL_STANDARD_CLASS_DLL(SvStorageStream,SOAPP)

    virtual USHORT      IsA() const;

    virtual void        SetSize( ULONG nNewSize );
    virtual BOOL        Commit();
    virtual BOOL        Revert();
};
#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif
SO2_IMPL_REF(SvStorageStream)

//============================================================================
//============================================================================
//============================================================================
class  ImpPersistFile;
class  Storage;
class SO3_DLLPUBLIC SvStorage : virtual public SvObject, public SotStorage
{
friend class SvStorageStream;
friend class ImpPersistFile;
    void     *  pRelease;  // OLE-Spec, wenn Erzeuger zerstoert
    void *      pObjI;     // Zeiger auf das Speichermedium
protected:
    SO3_DLLPRIVATE                  ~SvStorage();
public:
                        SvStorage( const String &,
                                   StreamMode = STREAM_STD_READWRITE,
                                   StorageMode = 0 );
                        SvStorage( BOOL bUCBStorage, const String &,
                                   StreamMode = STREAM_STD_READWRITE,
                                   StorageMode = 0 );
                        SvStorage( BaseStorage * );
                        SvStorage( SvStream & rStm );
                        SvStorage( BOOL bUCBStorage, SvStream & rStm );
                        SvStorage( SvStream * pStm, BOOL bDelete );
                        SvStorage();
                        SO2_DECL_STANDARD_CLASS_DLL(SvStorage,SOAPP)

                        /* Element Methoden     */
                        // Stream mit Verbindung zu Storage erzeugen,
                        // in etwa eine Parent-Child Beziehung
    SotStorageStream *  OpenSotStream( const String & rEleName,
                                    StreamMode = STREAM_STD_READWRITE,
                                    StorageMode = 0 );
    SotStorage *        OpenSotStorage( const String & rEleName,
                                    StreamMode = STREAM_STD_READWRITE,
                                    StorageMode = STORAGE_TRANSACTED );
    SvStorageStream *   OpenStream( const String & rEleName,
                                    StreamMode a = STREAM_STD_READWRITE,
                                    StorageMode b = 0 )
                        { return (SvStorageStream*)OpenSotStream( rEleName, a, b ); }
    SvStorage *         OpenStorage( const String & rEleName,
                                    StreamMode a = STREAM_STD_READWRITE,
                                    StorageMode b = STORAGE_TRANSACTED )
                        { return (SvStorage*)OpenSotStorage( rEleName, a, b ); }
    SvStorage *        OpenUCBStorage( const String & rEleName,
                                    StreamMode = STREAM_STD_READWRITE,
                                    StorageMode = STORAGE_TRANSACTED );
    SvStorage *        OpenOLEStorage( const String & rEleName,
                                    StreamMode = STREAM_STD_READWRITE,
                                    StorageMode = STORAGE_TRANSACTED );
};

#ifndef SO2_DECL_SVSTORAGE_DEFINED
#define SO2_DECL_SVSTORAGE_DEFINED
SO2_DECL_REF(SvStorage)
#endif
//SO2_IMPL_REF(SvStorage)

inline SvStorageRef::SvStorageRef( const SvStorageRef & rObj )
{
    pObj = rObj.pObj; if( pObj ) { pObj->AddNextRef(); }
}

inline SvStorageRef::SvStorageRef( SvStorage * pObjP )
{
    pObj = pObjP; if( pObj ) { pObj->AddRef(); }
}

inline void SvStorageRef::Clear()
{
    if( pObj )
    {
        SvStorage* const pRefObj = pObj;
        pObj = 0;
        pRefObj->ReleaseReference();
    }
}
inline SvStorageRef::~SvStorageRef()
{
    if( pObj ) { pObj->ReleaseReference(); }
}

inline SvStorageRef & SvStorageRef::operator = ( const SvStorageRef & rObj )
{
    if( rObj.pObj ) rObj.pObj->AddNextRef();
    SvStorage* const pRefObj = pObj;
    pObj = rObj.pObj;
    if( pRefObj )
    {
        pRefObj->ReleaseReference();
    }
    return *this;
}
inline SvStorageRef & SvStorageRef::operator = ( SvStorage * pObjP )
{
    return *this = SvStorageRef( pObjP );
}

inline SvStorageRef::SvStorageRef( const SotObjectRef & r )
{
    pObj = (SvStorage *)SvStorage::ClassFactory()->CastAndAddRef( &r );
}
inline SvStorageRef::SvStorageRef( SotObject * pObjP )
{
    pObj = (SvStorage *)SvStorage::ClassFactory()->CastAndAddRef( pObjP );
}

}

#endif // _SVSTOR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
