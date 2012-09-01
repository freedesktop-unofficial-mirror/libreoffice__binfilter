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
#ifndef _LNKBASE_HXX
#define _LNKBASE_HXX

#include <bf_svtools/bf_solar.h>
#include <bf_tools/string.hxx>

#include <sot/exchange.hxx>
#include <tools/ref.hxx>
#include <bf_so3/linksrc.hxx>

#include "bf_so3/so3dllapi.h"

namespace com { namespace sun { namespace star { namespace uno
{
    class Any;
    //class Type;
}}}}

namespace binfilter
{

struct ImplBaseLinkData;
class SvLinkManager;
class SvLinkSource;

#ifndef OBJECT_DDE_EXTERN
#define OBJECT_INTERN       0x00
//#define   OBJECT_SO_EXTERN    0x01
#define OBJECT_DDE_EXTERN   0x02
#endif

#define OBJECT_CLIENT_SO            0x80 // ein Link
#define OBJECT_CLIENT_DDE           0x81
//#define   OBJECT_CLIENT_OLE           0x82 // ein Ole-Link
//#define   OBJECT_CLIENT_OLE_CACHE     0x83 // ein Ole-Link mit SvEmbeddedObject
#define OBJECT_CLIENT_FILE          0x90
#define OBJECT_CLIENT_GRF           0x91

enum so3link {
    // Ole2 compatibel und persistent
    LINKUPDATE_ALWAYS = 1,
    LINKUPDATE_ONCALL = 3,

    LINKUPDATE_END      // dummy!
};

class SO3_DLLPUBLIC SvBaseLink : public SvRefBase
{
    friend class SvLinkManager;
    friend class SvLinkSource;
private:
    SvLinkSourceRef         xObj;
    String                  aLinkName;
    SvLinkManager*          pLinkMgr;
    USHORT                  nObjType;
    BOOL                    bVisible : 1;
    BOOL                    bSynchron : 1;
    BOOL                    bUseCache : 1;      // fuer GrafikLinks!

protected:
    void            SetObjType( USHORT );

                    // setzen des LinkSourceName ohne aktion
    SO3_DLLPRIVATE void         SetName( const String & rLn );

    ImplBaseLinkData* pImplData;

                    SvBaseLink( USHORT nLinkType, ULONG nContentType = FORMAT_STRING );
    virtual         ~SvBaseLink();

    void            _GetRealObject( BOOL bConnect = TRUE );

    SO3_DLLPRIVATE SvLinkSource*    GetRealObject()
                    {
                        if( !xObj.Is() )
                            _GetRealObject();
                        return xObj;
                    }

public:
                    TYPEINFO();
                    // ask JP
    virtual void    Closed();

    USHORT          GetObjType() const { return nObjType; }

    SvLinkSource*   GetObj() const  { return xObj; }

    void            SetLinkSourceName( const String & rName );
    String          GetLinkSourceName() const;

    virtual void    DataChanged( const String & rMimeType,
                                const ::com::sun::star::uno::Any & rValue );

    void            SetUpdateMode( USHORT );
    USHORT          GetUpdateMode() const;
    ULONG           GetContentType() const;
    BOOL            SetContentType( ULONG nType );

    SvLinkManager*  GetLinkManager()            { return pLinkMgr; }
    const SvLinkManager* GetLinkManager() const { return pLinkMgr; }

    BOOL            Update();
    void            Disconnect();

    virtual BOOL    Edit( Window* );

        // soll der Link im Dialog angezeigt werden ? (Links im Link im ...)
    BOOL            IsVisible() const           { return bVisible; }
    void            SetVisible( BOOL bFlag )    { bVisible = bFlag; }
        // soll der Link synchron oder asynchron geladen werden?
    BOOL            IsSynchron() const          { return bSynchron; }
    void            SetSynchron( BOOL bFlag )   { bSynchron = bFlag; }

    BOOL            IsUseCache() const          { return bUseCache; }
    void            SetUseCache( BOOL bFlag )   { bUseCache = bFlag; }
};

SV_DECL_IMPL_REF(SvBaseLink);

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
