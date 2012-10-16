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
//
#ifndef _BASMGR_HXX
#define _BASMGR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>
#include <bf_svtools/brdcst.hxx>

#include "sbstar.hxx"

#include <com/sun/star/script/XLibraryContainer.hpp>
#include <com/sun/star/script/XStarBasicAccess.hpp>


class SotStorage;

namespace binfilter {

// Basic XML Import/Export
com::sun::star::uno::Reference< com::sun::star::script::XStarBasicAccess >
    getStarBasicAccess( BasicManager* pMgr );

#define BASERR_ID_STDLIBOPEN            ERRCODE_BASMGR_STDLIBOPEN
#define BASERR_ID_STDLIBSAVE            ERRCODE_BASMGR_STDLIBSAVE
#define BASERR_ID_LIBLOAD               ERRCODE_BASMGR_LIBLOAD
#define BASERR_ID_LIBCREATE             ERRCODE_BASMGR_LIBCREATE
#define BASERR_ID_LIBSAVE               ERRCODE_BASMGR_LIBSAVE
#define BASERR_ID_LIBDEL                ERRCODE_BASMGR_LIBDEL
#define BASERR_ID_MGROPEN               ERRCODE_BASMGR_MGROPEN
#define BASERR_ID_MGRSAVE               ERRCODE_BASMGR_MGRSAVE
#define BASERR_ID_REMOVELIB             ERRCODE_BASMGR_REMOVELIB
#define BASERR_ID_UNLOADLIB             ERRCODE_BASMGR_UNLOADLIB

#define BASERR_REASON_OPENSTORAGE       0x0001
#define BASERR_REASON_OPENLIBSTORAGE    0x0002
#define BASERR_REASON_OPENMGRSTREAM     0x0004
#define BASERR_REASON_OPENLIBSTREAM     0x0008
#define BASERR_REASON_LIBNOTFOUND       0x0010
#define BASERR_REASON_STORAGENOTFOUND   0x0020
#define BASERR_REASON_BASICLOADERROR    0x0040
#define BASERR_REASON_NOSTORAGENAME     0x0080

#define BASERR_REASON_STDLIB            0x0100

class BasicError
{
private:
    ULONG   nErrorId;
    USHORT  nReason;
    String  aErrStr;

public:
            BasicError( const BasicError& rErr );
            BasicError( ULONG nId, USHORT nR, const String& rErrStr );

    ULONG   GetErrorId() const                  { return nErrorId; }
    USHORT  GetReason() const                   { return nReason; }
    String  GetErrorStr()                       { return aErrStr; }

    void    SetErrorId( ULONG n )               { nErrorId = n; }
    void    SetReason( USHORT n )               { nReason = n; }
    void    SetErrorStr( const String& rStr)    { aErrStr = rStr; }
};


//

class BasicLibs;
class ErrorManager;
class BasicLibInfo;
class BasicErrorManager;
namespace basic { class BasicManagerCleaner; }

// Library password handling for 5.0 documents
class OldBasicPassword
{
public:
    virtual void setLibraryPassword( const String& rLibraryName, const String& rPassword ) = 0;
    virtual String getLibraryPassword( const String& rLibraryName ) = 0;
    virtual void clearLibraryPassword( const String& rLibraryName ) = 0;
    virtual sal_Bool hasLibraryPassword( const String& rLibraryName ) = 0;

protected:
    ~OldBasicPassword() {}
};

struct LibraryContainerInfo
{
    com::sun::star::uno::Reference< com::sun::star::script::XLibraryContainer > mxScriptCont;
    com::sun::star::uno::Reference< com::sun::star::script::XLibraryContainer > mxDialogCont;
    OldBasicPassword* mpOldBasicPassword;

    LibraryContainerInfo
    (
        com::sun::star::uno::Reference< com::sun::star::script::XLibraryContainer > xScriptCont,
        com::sun::star::uno::Reference< com::sun::star::script::XLibraryContainer > xDialogCont,
        OldBasicPassword* pOldBasicPassword
    )
        : mxScriptCont( xScriptCont )
        , mxDialogCont( xDialogCont )
        , mpOldBasicPassword( pOldBasicPassword )
    {}
};

struct BasicManagerImpl;


#define LIB_NOTFOUND    0xFFFF

class BasicManager : public SfxBroadcaster
{
    friend class LibraryContainer_Impl;
    friend class StarBasicAccess_Impl;
    friend class BasMgrContainerListenerImpl;
    friend class basic::BasicManagerCleaner;

private:
    BasicLibs*          pLibs;
    BasicErrorManager*  pErrorMgr;

    String              aName;
    String              maStorageName;
    BOOL                bBasMgrModified;

    BasicManagerImpl*   mpImpl;

    void                Init();

protected:
    BOOL            ImpLoadLibary( BasicLibInfo* pLibInfo ) const;
    BOOL            ImpLoadLibary( BasicLibInfo* pLibInfo, SotStorage* pCurStorage, BOOL bInfosOnly = FALSE ) const;
    void            ImpCreateStdLib( StarBASIC* pParentFromStdLib );
    void            ImpMgrNotLoaded(  const String& rStorageName  );
    BasicLibInfo*   CreateLibInfo();
    void            LoadBasicManager( SotStorage& rStorage, const String& rBaseURL, BOOL bLoadBasics = TRUE );
    void            LoadOldBasicManager( SotStorage& rStorage );
    BOOL            ImplLoadBasic( SvStream& rStrm, StarBASICRef& rOldBasic ) const;
    BOOL            ImplEncryptStream( SvStream& rStream ) const;
    BasicLibInfo*   FindLibInfo( StarBASIC* pBasic ) const;
    void            CheckModules( StarBASIC* pBasic, BOOL bReference ) const;
    ~BasicManager();

public:
                    TYPEINFO();
                    BasicManager( SotStorage& rStorage, const String& rBaseURL, StarBASIC* pParentFromStdLib = NULL, String* pLibPath = NULL );
                    BasicManager( StarBASIC* pStdLib, String* pLibPath = NULL );

    /** deletes the given BasicManager instance

        This method is necessary since normally, BasicManager instances are owned by the BasicManagerRepository,
        and expected to be deleted by the repository only. However, there exists quite some legacy code,
        which needs to explicitly delete a BasicManager itself. This code must not use the (protected)
        destructor, but LegacyDeleteBasicManager.
    */
    static void     LegacyDeleteBasicManager( BasicManager*& _rpManager );

    void            SetStorageName( const String& rName )   { maStorageName = rName; }
    String          GetStorageName() const                  { return maStorageName; }
    void            SetName( const String& rName )          { aName = rName; }
    String          GetName() const                         { return aName; }


    static BOOL     HasBasicWithModules( const SotStorage& rStorage, const String& rBaseURL );

    USHORT          GetLibCount() const;
    StarBASIC*      GetLib( USHORT nLib ) const;
    StarBASIC*      GetLib( const String& rName ) const;
    USHORT          GetLibId( const String& rName ) const;

    void            Store( SotStorage&, const String& ) {}
    void            Store( SotStorage&, const String&, BOOL ){}

    String          GetLibName( USHORT nLib );

    /** announces the library containers which belong to this BasicManager

        The method will automatically add two global constants, BasicLibraries and DialogLibraries,
        to the BasicManager.
    */
    void            SetLibraryContainerInfo( LibraryContainerInfo* pInfo );

    BOOL            RemoveLib( USHORT nLib, BOOL bDelBasicFromStorage );
private:
    BOOL            IsReference( USHORT nLib );

    BOOL            SetLibName( USHORT nLib, const String& rName );

    StarBASIC*      GetStdLib() const;
    StarBASIC*      AddLib( SotStorage& rStorage, const String& rLibName, BOOL bReference );
    BOOL            RemoveLib( USHORT nLib );
    BOOL            HasLib( const String& rName ) const;

    StarBASIC*      CreateLibForLibContainer( const String& rLibName,
                        const com::sun::star::uno::Reference< com::sun::star::script::XLibraryContainer >&
                            xScriptCont );
    // For XML import/export:
    StarBASIC*      CreateLib( const String& rLibName );
    StarBASIC*      CreateLib( const String& rLibName, const String& Password,
                               const String& LinkTargetURL );
};

void SetAppBasicManager( BasicManager* pBasMgr );

}

#endif  //_BASMGR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
