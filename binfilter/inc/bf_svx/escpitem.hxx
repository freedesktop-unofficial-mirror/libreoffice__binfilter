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
#ifndef _SVX_ESCPITEM_HXX
#define _SVX_ESCPITEM_HXX

#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxenum.hxx>
#include <bf_svx/svxids.hrc>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;
// class SvxEscapementItem -----------------------------------------------

#define DFLT_ESC_SUPER   33     // 1/3
#define DFLT_ESC_SUB    -33     // auch 1/3 fr"uher 8/100
#define DFLT_ESC_PROP    58
#define DFLT_ESC_AUTO_SUPER 101
#define DFLT_ESC_AUTO_SUB  -101

/*  [Beschreibung]

    Dieses Item beschreibt die Schrift-Position.
*/

class SvxEscapementItem : public SfxEnumItemInterface
{
    short nEsc;
    BYTE  nProp;
public:
    TYPEINFO();

    SvxEscapementItem( const USHORT nId = ITEMID_ESCAPEMENT );
    SvxEscapementItem( const short nEsc, const BYTE nProp,
                   const USHORT nId = ITEMID_ESCAPEMENT  );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;

    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream& Store(SvStream &rStream, USHORT) const { return rStream; }

    inline void SetEscapement( const SvxEscapement eNew )
    {
        if( SVX_ESCAPEMENT_OFF == eNew )
            nEsc = 0, nProp = 100;
        else
            if( SVX_ESCAPEMENT_SUPERSCRIPT == eNew )
                nEsc = DFLT_ESC_SUPER, nProp = DFLT_ESC_PROP;
            else
                nEsc = DFLT_ESC_SUB, nProp = DFLT_ESC_PROP;
    }

    inline short &GetEsc() { return nEsc; }
    inline short GetEsc() const { return nEsc; }

    inline BYTE &GetProp() { return nProp; }
    inline BYTE GetProp() const { return nProp; }

    inline SvxEscapementItem& operator=(const SvxEscapementItem& rEsc)
        {
            nEsc  = rEsc.GetEsc();
            nProp = rEsc.GetProp();
            return *this;
        }

    virtual USHORT          GetValueCount() const { return 0; } // DBG_BF_ASSERT
    virtual USHORT          GetEnumValue() const  { return 0; } // DBG_BF_ASSERT
    virtual void            SetEnumValue( USHORT /* nNewVal */ ) {} // DBG_BF_ASSERT
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
