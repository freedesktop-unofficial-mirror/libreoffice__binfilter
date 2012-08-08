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
#ifndef _SVX_DRAWITEM_HXX
#define _SVX_DRAWITEM_HXX

namespace binfilter {

//==================================================================
//  SvxColorTableItem
//==================================================================

#ifdef ITEMID_COLOR_TABLE
class XColorTable;

class SvxColorTableItem: public SfxPoolItem
{
    XColorTable*            pColorTable;

public:
                            TYPEINFO();
                            SvxColorTableItem();
                            SvxColorTableItem( XColorTable* pTable,
                                    USHORT nWhich = ITEMID_COLOR_TABLE );
                            SvxColorTableItem( const SvxColorTableItem& );


    virtual int             operator==( const SfxPoolItem& ) const { return 0; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    XColorTable*            GetColorTable() const { return pColorTable; }
    void                    SetColorTable( XColorTable* pTable ) {
                                    pColorTable = pTable; }
};

#endif

//==================================================================
//  SvxGradientListItem
//==================================================================

#ifdef ITEMID_GRADIENT_LIST
class XGradientList;

class SvxGradientListItem: public SfxPoolItem
{
    XGradientList*              pGradientList;

public:
                            TYPEINFO();
                            SvxGradientListItem();
                            SvxGradientListItem( XGradientList* pList,
                                    USHORT nWhich = ITEMID_GRADIENT_LIST );
                            SvxGradientListItem( const SvxGradientListItem& );


    virtual int             operator==( const SfxPoolItem& ) const { return 0; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    XGradientList*          GetGradientList() const { return pGradientList; }
    void                    SetGradientList( XGradientList* pList ) {
                                    pGradientList = pList; }
};

#endif

//==================================================================
//  SvxHatchListItem
//==================================================================

#ifdef ITEMID_HATCH_LIST
class XHatchList;

class SvxHatchListItem: public SfxPoolItem
{
    XHatchList*             pHatchList;

public:
                            TYPEINFO();
                            SvxHatchListItem();
                            SvxHatchListItem( XHatchList* pList,
                                    USHORT nWhich = ITEMID_HATCH_LIST );
                            SvxHatchListItem( const SvxHatchListItem& );


    virtual int             operator==( const SfxPoolItem& ) const { return 0; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    XHatchList*             GetHatchList() const { return pHatchList; }
    void                    SetHatchList( XHatchList* pList ) {
                                    pHatchList = pList; }
};

#endif

//==================================================================
//  SvxBitmapListItem
//==================================================================

#ifdef ITEMID_BITMAP_LIST
class XBitmapList;

class SvxBitmapListItem: public SfxPoolItem
{
    XBitmapList*                pBitmapList;

public:
                            TYPEINFO();
                            SvxBitmapListItem();
                            SvxBitmapListItem( XBitmapList* pBL,
                                    USHORT nWhich = ITEMID_BITMAP_LIST );
                            SvxBitmapListItem( const SvxBitmapListItem& );


    virtual int             operator==( const SfxPoolItem& ) const { return 0; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    XBitmapList*            GetBitmapList() const { return pBitmapList; }
    void                    SetBitmapList( XBitmapList* pList ) {
                                    pBitmapList = pList; }
};

#endif

//==================================================================
//  SvxDashListItem
//==================================================================

#ifdef ITEMID_DASH_LIST
class XDashList;

class SvxDashListItem: public SfxPoolItem
{
    XDashList*              pDashList;

public:
                            TYPEINFO();
                            SvxDashListItem();
                            SvxDashListItem( XDashList* pList,
                                    USHORT nWhich = ITEMID_DASH_LIST );
                            SvxDashListItem( const SvxDashListItem& );


    virtual int             operator==( const SfxPoolItem& ) const { return 0; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    XDashList*              GetDashList() const { return pDashList; }
    void                    SetDashList( XDashList* pList ) {
                                    pDashList = pList; }
};

#endif

//==================================================================
//  SvxLineEndListItem
//==================================================================

#ifdef ITEMID_LINEEND_LIST
class XLineEndList;

class SvxLineEndListItem: public SfxPoolItem
{
    XLineEndList*           pLineEndList;

public:
                            TYPEINFO();
                            SvxLineEndListItem();
                            SvxLineEndListItem( XLineEndList* pList,
                                    USHORT nWhich = ITEMID_LINEEND_LIST );
                            SvxLineEndListItem( const SvxLineEndListItem& );


    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    XLineEndList*           GetLineEndList() const { return pLineEndList; }
    void                    SetLineEndList( XLineEndList* pList ) {
                                    pLineEndList = pList; }
};

#endif

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
