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
#ifndef _SVX_PROTITEM_HXX
#define _SVX_PROTITEM_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/poolitem.hxx>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;

// class SvxProtectItem --------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt, ob Inhalt, Groesse oder Position geschuetzt werden
sollen.
*/

class SvxProtectItem : public SfxPoolItem
{
    BOOL bCntnt :1;     //Inhalt geschuetzt
    BOOL bSize  :1;     //Groesse geschuetzt
    BOOL bPos   :1;     //Position geschuetzt

public:
    TYPEINFO();

    inline SvxProtectItem( const USHORT nId = ITEMID_PROTECT );
    inline SvxProtectItem &operator=( const SvxProtectItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;


    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &rStream, USHORT) const { return rStream; }

    BOOL IsCntntProtected() const { return bCntnt; }
    BOOL IsSizeProtected()  const { return bSize;  }
    BOOL IsPosProtected()   const { return bPos;   }
    void SetCntntProtect( BOOL bNew ) { bCntnt = bNew; }
    void SetSizeProtect ( BOOL bNew ) { bSize  = bNew; }
    void SetPosProtect  ( BOOL bNew ) { bPos   = bNew; }

    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
};

inline SvxProtectItem::SvxProtectItem( const USHORT nId )
    : SfxPoolItem( nId )
{
    bCntnt = bSize = bPos = FALSE;
}

inline SvxProtectItem &SvxProtectItem::operator=( const SvxProtectItem &rCpy )
{
    bCntnt = rCpy.IsCntntProtected();
    bSize  = rCpy.IsSizeProtected();
    bPos   = rCpy.IsPosProtected();
    return *this;
}

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
