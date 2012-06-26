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
#ifndef _SVX_ADJITEM_HXX
#define _SVX_ADJITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxenum.hxx>

#include <bf_svx/svxids.hrc>

#include <bf_svx/eeitem.hxx>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;
// class SvxAdjustItem ---------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt die Zeilenausrichtung.
*/
#define ADJUST_LASTBLOCK_VERSION        ((USHORT)0x0001)

class SvxAdjustItem : public SfxEnumItemInterface
{
    BOOL    bLeft      : 1;
    BOOL    bRight     : 1;
    BOOL    bCenter    : 1;
    BOOL    bBlock     : 1;

    // nur aktiv, wenn bBlock
    BOOL    bOneBlock : 1;
    BOOL    bLastCenter : 1;
    BOOL    bLastBlock : 1;

    friend SvStream& operator<<( SvStream&, SvxAdjustItem& ); //$ ostream

public:
    TYPEINFO();

    SvxAdjustItem( const SvxAdjust eAdjst = SVX_ADJUST_LEFT,
                   const USHORT nId = ITEMID_ADJUST );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;

    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT           GetValueCount() const { return 0; } // DBG_BF_ASSERT
    virtual USHORT           GetEnumValue()  const { return 0; } // DBG_BF_ASSERT
    virtual void             SetEnumValue( USHORT /* nNewVal */ ) {} // DBG_BF_ASSERT
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream& Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT           GetVersion( USHORT nFileVersion ) const;

    inline void SetOneWord( const SvxAdjust eType )
    {
        bOneBlock  = eType == SVX_ADJUST_BLOCK;
    }

    inline void SetLastBlock( const SvxAdjust eType )
    {
        bLastBlock = eType == SVX_ADJUST_BLOCK;
        bLastCenter = eType == SVX_ADJUST_CENTER;
    }

    inline void SetAdjust( const SvxAdjust eType )
    {
        bLeft = eType == SVX_ADJUST_LEFT;
        bRight = eType == SVX_ADJUST_RIGHT;
        bCenter = eType == SVX_ADJUST_CENTER;
        bBlock = eType == SVX_ADJUST_BLOCK;
    }

    inline SvxAdjust GetLastBlock() const
    {
        SvxAdjust eRet = SVX_ADJUST_LEFT;

        if ( bLastBlock )
            eRet = SVX_ADJUST_BLOCK;
        else if( bLastCenter )
            eRet = SVX_ADJUST_CENTER;
        return eRet;
    }

    inline SvxAdjust GetOneWord() const
    {
        SvxAdjust eRet = SVX_ADJUST_LEFT;

        if ( bBlock && bOneBlock )
            eRet = SVX_ADJUST_BLOCK;
        return eRet;
    }

    inline SvxAdjust GetAdjust() const
    {
        SvxAdjust eRet = SVX_ADJUST_LEFT;

        if ( bRight )
            eRet = SVX_ADJUST_RIGHT;
        else if ( bCenter )
            eRet = SVX_ADJUST_CENTER;
        else if ( bBlock )
            eRet = SVX_ADJUST_BLOCK;
        return eRet;
    }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
