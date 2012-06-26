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
#ifndef _SVX_ULSPITEM_HXX
#define _SVX_ULSPITEM_HXX

// include ---------------------------------------------------------------

#include <bf_svtools/poolitem.hxx>
#include <bf_svx/svxids.hrc>

namespace rtl
{
    class OUString;
}
namespace binfilter {

// class SvxULSpaceItem --------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt den oberen und unteren Rand einer Seite oder Absatz.
*/

#define ULSPACE_16_VERSION  ((USHORT)0x0001)

class SvxULSpaceItem : public SfxPoolItem
{
    USHORT nUpper;  //Oberer Rand
    USHORT nLower;  //Unterer Rand
    USHORT nPropUpper, nPropLower;      // relativ oder absolut (=100%)
public:
    TYPEINFO();

    SvxULSpaceItem( const USHORT nId = ITEMID_ULSPACE );
    SvxULSpaceItem( const USHORT nUp, const USHORT nLow,
                    const USHORT nId = ITEMID_ULSPACE );
    inline SvxULSpaceItem& operator=( const SvxULSpaceItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;

    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT           GetVersion( USHORT nFileVersion ) const;

    inline void SetUpper( const USHORT nU, const USHORT nProp = 100 );
    inline void SetLower( const USHORT nL, const USHORT nProp = 100 );

    void SetUpperValue( const USHORT nU ) { nUpper = nU; }
    void SetLowerValue( const USHORT nL ) { nLower = nL; }
    void SetPropUpper( const USHORT nU ) { nPropUpper = nU; }
    void SetPropLower( const USHORT nL ) { nPropLower = nL; }

    USHORT GetUpper() const { return nUpper; }
    USHORT GetLower() const { return nLower; }
    USHORT GetPropUpper() const { return nPropUpper; }
    USHORT GetPropLower() const { return nPropLower; }
};

inline SvxULSpaceItem &SvxULSpaceItem::operator=( const SvxULSpaceItem &rCpy )
{
    nUpper = rCpy.GetUpper();
    nLower = rCpy.GetLower();
    nPropUpper = rCpy.GetPropUpper();
    nPropLower = rCpy.GetPropLower();
    return *this;
}

inline void SvxULSpaceItem::SetUpper( const USHORT nU, const USHORT nProp )
{
    nUpper = USHORT((ULONG(nU) * nProp ) / 100); nPropUpper = nProp;
}
inline void SvxULSpaceItem::SetLower( const USHORT nL, const USHORT nProp )
{
    nLower = USHORT((ULONG(nL) * nProp ) / 100); nPropLower = nProp;
}

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
