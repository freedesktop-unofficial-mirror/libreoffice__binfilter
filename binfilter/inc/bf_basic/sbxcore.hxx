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

#ifndef _SBXCORE_HXX
#define _SBXCORE_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/rtti.hxx>
#include <tools/ref.hxx>

#include <tools/debug.hxx>

#include "sbxdef.hxx"

class SvStream;
class String;
class UniString;
namespace rtl { class OUString; }

// Das nachfolgende Makro definiert die vier  (fuenf) notwendigen Methoden
// innerhalb eines SBX-Objekts. LoadPrivateData() und StorePrivateData()
// muessen selbst implementiert werden. Sie sind fuer das Laden/Speichern
// der Daten der abgeleiteten Klasse notwendig. Load() und Store() duerfen
// nicht ueberlagert werden.

// Diese Version des Makros definiert keine Load/StorePrivateData()-Methoden

#define SBX_DECL_PERSIST_NODATA( nCre, nSbxId, nVer )       \
    virtual UINT32 GetCreator() const { return nCre;   }    \
    virtual UINT16 GetVersion() const { return nVer;   }    \
    virtual UINT16 GetSbxId() const   { return nSbxId; }

// Diese Version des Makros definiert Load/StorePrivateData()-Methoden

#define SBX_DECL_PERSIST( nCre, nSbxId, nVer )              \
    virtual BOOL LoadPrivateData( SvStream&, USHORT );      \
    virtual BOOL StorePrivateData( SvStream& ) const;       \
    SBX_DECL_PERSIST_NODATA( nCre, nSbxId, nVer )

namespace binfilter {

class SbxBase;
class SbxFactory;
class SbxObject;

class SbxBaseImpl;

class SbxBase : virtual public SvRefBase
{
    SbxBaseImpl* mpSbxBaseImpl; // Impl data

    virtual BOOL LoadData( SvStream&, USHORT );
    virtual BOOL StoreData( SvStream& ) const {return FALSE;}
protected:
    USHORT nFlags;          // Flag-Bits

    SbxBase();
    SbxBase( const SbxBase& );
    SbxBase& operator=( const SbxBase& );
    virtual ~SbxBase();
    SBX_DECL_PERSIST(0,0,0);
public:
    TYPEINFO();
    inline void     SetFlags( USHORT n );
    inline USHORT   GetFlags() const;
    inline void     SetFlag( USHORT n );
    inline void     ResetFlag( USHORT n );
    inline BOOL     IsSet( USHORT n ) const;
    inline BOOL     IsReset( USHORT n ) const;
    inline BOOL     CanRead() const;
    inline BOOL     CanWrite() const;
    inline BOOL     IsModified() const;
    inline BOOL     IsConst() const;
    inline BOOL     IsHidden() const;
    inline BOOL     IsVisible() const;

    virtual BOOL IsFixed() const;
    virtual void SetModified( BOOL );

    virtual SbxDataType  GetType()  const;
    virtual SbxClassType GetClass() const;

    virtual void Clear();

    static SbxBase* Load( SvStream& );
    static void Skip( SvStream& );
    BOOL Store( SvStream& ) {return FALSE;}
    virtual BOOL LoadCompleted();
    virtual BOOL StoreCompleted();

    static SbxError GetError();
    static void SetError( SbxError );
    static BOOL IsError();
    static void ResetError();

    // Setzen der Factory fuer Load/Store/Create
    static void AddFactory( SbxFactory* );
    static void RemoveFactory( SbxFactory* );

    static SbxBase* Create( UINT16, UINT32=SBXCR_SBX );
    static SbxObject* CreateObject( const rtl::OUString& );
    // Sbx-Loesung als Ersatz fuer SfxBroadcaster::Enable()
    static BOOL StaticIsEnabledBroadcasting( void );
};

#ifndef SBX_BASE_DECL_DEFINED
#define SBX_BASE_DECL_DEFINED
SV_DECL_REF(SbxBase)
#endif

inline void SbxBase::SetFlags( USHORT n )
{ nFlags = n; }

inline USHORT SbxBase::GetFlags() const
{ return nFlags; }

inline void SbxBase::SetFlag( USHORT n )
{ nFlags |= n; }

inline void SbxBase::ResetFlag( USHORT n )
{ nFlags &= ~n; }

inline BOOL SbxBase::IsSet( USHORT n ) const
{ return BOOL( ( nFlags & n ) != 0 ); }

inline BOOL SbxBase::IsReset( USHORT n ) const
{ return BOOL( ( nFlags & n ) == 0 ); }

inline BOOL SbxBase::CanRead() const
{ return IsSet( SBX_READ ); }

inline BOOL SbxBase::CanWrite() const
{ return IsSet( SBX_WRITE ); }

inline BOOL SbxBase::IsModified() const
{ return IsSet( SBX_MODIFIED ); }

inline BOOL SbxBase::IsConst() const
{ return IsSet( SBX_CONST ); }

inline BOOL SbxBase::IsHidden() const
{ return IsSet( SBX_HIDDEN ); }

inline BOOL SbxBase::IsVisible() const
{ return IsReset( SBX_INVISIBLE ); }

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
