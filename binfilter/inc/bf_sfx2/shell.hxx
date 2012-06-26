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
#ifndef _SFX_SHELL_HXX
#define _SFX_SHELL_HXX

#include <tools/debug.hxx>
#include <tools/rtti.hxx>
#include <bf_svtools/brdcst.hxx>

#include <bf_tools/string.hxx>

namespace binfilter {

class SfxItemPool;
class SfxPoolItem;


struct SfxShell_Impl;

typedef SfxPoolItem* SfxPoolItemPtr;
SV_DECL_PTRARR_DEL( SfxItemPtrArray, SfxPoolItemPtr, 4, 4 )
typedef SfxItemPtrArray SfxItemArray_Impl;

//====================================================================

class SfxShell: public SfxBroadcaster
{
    friend class SfxObjectItem;

    SfxShell_Impl*              pImp;
    SfxItemPool*                pPool;
    String                      aName;

private:
                                SfxShell( const SfxShell & ); // n.i.
    SfxShell&                   operator = ( const SfxShell & ); // n.i.

protected:
                                SfxShell();
public:
                                TYPEINFO();
    virtual                     ~SfxShell();

    void                        SetName( const String &rName ) { aName = rName; }
    const String&               GetName() const { return aName; }

    SfxItemPool&                GetPool() const { return *pPool; }
    void                        SetPool( SfxItemPool *pNewPool ) { pPool = pNewPool; }

    const SfxPoolItem*          GetItem( USHORT nSlotId ) const;
    void                        PutItem( const SfxPoolItem& rItem );
    void                        RemoveItem( USHORT nSlotId );
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
