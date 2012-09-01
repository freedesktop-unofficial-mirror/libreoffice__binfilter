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
#ifndef _LINKSRC_HXX
#define _LINKSRC_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/ref.hxx>
#include <tools/rtti.hxx>

#ifndef _SAL_CONFIG_H
#include <sal/config.h>
#define _SAL_CONFIG_H
#endif

#include "bf_so3/so3dllapi.h"

namespace com { namespace sun { namespace star { namespace uno
{
    class Any;
    //class Type;
}}}}
class Window;

#ifndef ADVISEMODE_NODATA
// Muessen die gleichen Werte wie Ole2 ADVF_* sein
#define ADVISEMODE_NODATA       0x01
//#define ADVISEMODE_PRIMEFIRST   0x02
#define ADVISEMODE_ONLYONCE     0x04
//#define ADVISEMODE_DATAONSTOP   0x40
#endif

namespace binfilter
{

class String;
class SvBaseLink;
struct SvLinkSource_Impl;

class SO3_DLLPUBLIC SvLinkSource : public SvRefBase
{
private:
    SvLinkSource_Impl * pImpl; // compatible area
public:
                        TYPEINFO();

                        SvLinkSource();
    virtual             ~SvLinkSource();

//  SvBaseLink*         GetDataBaseLink() const;
    BOOL                HasDataLinks( const SvBaseLink* = 0 ) const;

    void                Closed();

    void                SetUpdateTimeout( ULONG nTime );
                        // notify the sink, the mime type is not
                        // a selection criterion
    void                DataChanged( const String & rMimeType,
                                    const ::com::sun::star::uno::Any & rVal );
    void                SendDataChanged();
    void                NotifyDataChanged();

    virtual BOOL        Connect( SvBaseLink * );
    virtual BOOL        GetData( ::com::sun::star::uno::Any & rData /*out param*/,
                                const String & rMimeType,
                                BOOL bSynchron = FALSE );

                        // TRUE => waitinmg for data
    virtual BOOL        IsPending() const;
                        // TRUE => data complete loaded
    virtual BOOL        IsDataComplete() const;

    virtual String      Edit( Window *, SvBaseLink * );

    void                AddDataAdvise( SvBaseLink *, const String & rMimeType,
                                        USHORT nAdviceMode );
    void                RemoveAllDataAdvise( SvBaseLink * );

    void                AddConnectAdvise( SvBaseLink * );
    void                RemoveConnectAdvise( SvBaseLink * );
};

SV_DECL_IMPL_REF(SvLinkSource);

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
