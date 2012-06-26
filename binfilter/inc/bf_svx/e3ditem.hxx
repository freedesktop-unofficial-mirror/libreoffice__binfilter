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

#ifndef _SVXE3DITEM_HXX
#define _SVXE3DITEM_HXX

#include <bf_svtools/poolitem.hxx>
#include <bf_goodies/vector3d.hxx>
class SvStream;
namespace binfilter {

#ifndef _SVXVECT3DITEM_HXX
#define _SVXVECT3DITEM_HXX


DBG_NAMEEX(SvxVector3DItem)

class SvxVector3DItem: public SfxPoolItem
{
    Vector3D                aVal;

public:
                            TYPEINFO();
                            SvxVector3DItem() {}
                            SvxVector3DItem( USHORT nWhich, const Vector3D& rVal );
                            SvxVector3DItem( const SvxVector3DItem& );
                            ~SvxVector3DItem()
                            {
                                DBG_DTOR(SvxVector3DItem, 0);
                            }

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVersion) const;
    virtual SvStream& Store(SvStream &rStream, USHORT) const { return rStream; }

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    const Vector3D&         GetValue() const { return aVal; }
            void            SetValue( const Vector3D& rNewVal ) {
                                 DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
                                 aVal = rNewVal;
                             }

    virtual USHORT GetVersion (USHORT nFileFormatVersion) const;
};

#endif

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
