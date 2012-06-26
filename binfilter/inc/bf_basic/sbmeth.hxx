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

#ifndef _SB_SBMETH_HXX
#define _SB_SBMETH_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/errcode.hxx>
#include "sbxmeth.hxx"
#include "sbdef.hxx"

namespace binfilter {

class SbModule;
class SbMethodImpl;

class SbMethod : public SbxMethod
{
    friend class SbiRuntime;
    friend class SbiFactory;
    friend class SbModule;
    friend class SbClassModuleObject;
    friend class SbiCodeGen;
    friend class SbJScriptMethod;
    friend class SbIfaceMapperMethod;

    SbMethodImpl* mpSbMethodImpl;           // Impl data

    SbModule* pMod;
    USHORT    nDebugFlags;
    USHORT    nLine1, nLine2;
    UINT32    nStart;
    BOOL      bInvalid;
    SbMethod( const String&, SbxDataType, SbModule* );
    SbMethod( const SbMethod& );
    virtual BOOL LoadData( SvStream&, USHORT );
    virtual BOOL StoreData( SvStream& ) const {return FALSE;}
    virtual ~SbMethod();

public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_BASICMETHOD,2);
    TYPEINFO();
    virtual SbxInfo* GetInfo();
    SbModule* GetModule()                { return pMod;        }
    UINT32    GetId() const              { return nStart;      }
    USHORT    GetDebugFlags()            { return nDebugFlags; }
    void      SetDebugFlags( USHORT n )  { nDebugFlags = n;    }

    // Schnittstelle zum Ausfuehren einer Methode aus den Applikationen
    virtual ErrCode Call( SbxValue* pRet = NULL );
    virtual void Broadcast( ULONG nHintId );
};

#ifndef __SB_SBMETHODREF_HXX
#define __SB_SBMETHODREF_HXX
SV_DECL_IMPL_REF(SbMethod)
#endif


class SbIfaceMapperMethod : public SbMethod
{
    friend class SbiRuntime;

    SbMethodRef mxImplMeth;

public:
    TYPEINFO();
    SbIfaceMapperMethod( const String& rName, SbMethod* pImplMeth )
        : SbMethod( rName, pImplMeth->GetType(), NULL )
        , mxImplMeth( pImplMeth )
    {}
    virtual ~SbIfaceMapperMethod();
    SbMethod* getImplMethod( void )
        { return mxImplMeth; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
