/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svstor.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:28:36 $
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

#ifndef _SVSTOR_HXX
#define _SVSTOR_HXX

#ifndef _IFACE_HXX
#include <bf_so3/iface.hxx>
#endif
#ifndef _SOT_STORAGE_HXX
#include <sot/storage.hxx>
#endif

#include <bf_so3/so2defs.hxx>

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

#ifdef SvStorage
#undef SvStorage
#undef SvStorageRef
#undef SvStorageStream
#undef SvStorageStreamRef
#endif

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
                        SvStorageStream( const String &,
                                     StreamMode = STREAM_STD_READWRITE,
                                     StorageMode = 0 );
                        SvStorageStream( BaseStorageStream *pStm );
                        SvStorageStream();
                        SO2_DECL_STANDARD_CLASS_DLL(SvStorageStream,SOAPP)

    virtual USHORT      IsA() const;
                        using SvStream::SyncSvStream;
    virtual void        SyncSvStream();

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
class  SvStorageInfoList;
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

    static BOOL         IsStorageFile( const String & rFileName );
    const String &      GetName() const;

                        // eigener Datenbereich
    void                SetClass( const SvGlobalName & rClass,
                                  ULONG bOriginalClipFormat,
                                  const String & rUserTypeName );
    void                SetConvertClass( const SvGlobalName & rConvertClass,
                                         ULONG bOriginalClipFormat,
                                         const String & rUserTypeName );
    SvGlobalName        GetClassName();// Typ der Daten im Storage
    ULONG               GetFormat();
    String              GetUserName();
    BOOL                ShouldConvert();

                        // Liste aller Elemente
    void                FillInfoList( SvStorageInfoList * ) const;
    BOOL                CopyTo( SotStorage * pDestStg );
    BOOL                Commit();
    BOOL                Revert();

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
                        // Abfrage auf Storage oder Stream
    BOOL                IsStream( const String & rEleName ) const;
    BOOL                IsStorage( const String & rEleName ) const;
    BOOL                IsContained( const String & rEleName ) const;
                        // Element loeschen
    BOOL                Remove( const String & rEleName );
                        // Elementnamen aendern
    BOOL                Rename( const String & rEleName,
                                const String & rNewName );
    BOOL                CopyTo( const String & rEleName, SotStorage * pDest,
                                const String & rNewName );
    BOOL                MoveTo( const String & rEleName, SotStorage * pDest,
                                const String & rNewName );
};

#ifndef SO2_DECL_SVSTORAGE_DEFINED
#define SO2_DECL_SVSTORAGE_DEFINED
SO2_DECL_REF(SvStorage)
#endif
SO2_IMPL_REF(SvStorage)

#endif // _SVSTOR_HXX
