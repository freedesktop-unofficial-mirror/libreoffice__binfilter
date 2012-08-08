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
#ifndef _SVX_ALGITEM_HXX
#define _SVX_ALGITEM_HXX

#include <bf_svx/svxids.hrc>

#include <bf_svtools/poolitem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxenum.hxx>
class SvStream;


namespace binfilter {


//------------------------------------------------------------------------

#ifdef ITEMID_HORJUSTIFY

class SvxHorJustifyItem: public SfxEnumItem
{
public:
    TYPEINFO();

    SvxHorJustifyItem(
        const SvxCellHorJustify eJustify = SVX_HOR_JUSTIFY_STANDARD,
        const USHORT nId = ITEMID_HORJUSTIFY );


    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVer ) const;

    inline  SvxHorJustifyItem& operator=(const SvxHorJustifyItem& rHorJustify)
            {
                SetValue( rHorJustify.GetValue() );
                return *this;
            }
};

#endif

//------------------------------------------------------------------------

#ifdef ITEMID_VERJUSTIFY

class SvxVerJustifyItem: public SfxEnumItem
{
public:
    TYPEINFO();

    SvxVerJustifyItem(
        const SvxCellVerJustify eJustify = SVX_VER_JUSTIFY_STANDARD,
        const USHORT nId = ITEMID_VERJUSTIFY );


    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVer ) const;

    inline  SvxVerJustifyItem& operator=(const SvxVerJustifyItem& rVerJustify)
            {
                SetValue( rVerJustify.GetValue() );
                return *this;
            }
};

#endif

//------------------------------------------------------------------------

#ifdef ITEMID_ORIENTATION

class SvxOrientationItem: public SfxEnumItem
{
public:
    TYPEINFO();

    SvxOrientationItem(
        const SvxCellOrientation eOrientation = SVX_ORIENTATION_STANDARD,
        const USHORT nId = ITEMID_ORIENTATION );


    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVer ) const;

    inline  SvxOrientationItem& operator=(const SvxOrientationItem& rOrientation)
            {
                SetValue( rOrientation.GetValue() );
                return *this;
            }
};

#endif

//------------------------------------------------------------------------

#ifdef ITEMID_MARGIN

class SvxMarginItem: public SfxPoolItem
{
    INT16       nLeftMargin;
    INT16       nTopMargin;
    INT16       nRightMargin;
    INT16       nBottomMargin;
public:
    TYPEINFO();
    SvxMarginItem( const USHORT nId = ITEMID_MARGIN );
    SvxMarginItem( INT16 nLeft, INT16 nTop = 0,
                   INT16 nRight = 0, INT16 nBottom = 0,
                   const USHORT nId = ITEMID_MARGIN );
    SvxMarginItem( const SvxMarginItem& );


    virtual int              operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create( SvStream& rStream, USHORT nVer ) const;
    virtual SvStream& Store( SvStream& rStream, USHORT ) const { return rStream; }

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

            INT16           GetLeftMargin() const {return nLeftMargin; }
            INT16           GetTopMargin() const {return nTopMargin; }
            INT16           GetRightMargin() const {return nRightMargin; }
            INT16           GetBottomMargin() const {return nBottomMargin; }

    inline  SvxMarginItem& operator=(const SvxMarginItem& rMargin)
            {
                nLeftMargin = rMargin.nLeftMargin;
                nTopMargin = rMargin.nTopMargin;
                nRightMargin = rMargin.nRightMargin;
                nBottomMargin = rMargin.nBottomMargin;
                return *this;
            }
};

#endif

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
