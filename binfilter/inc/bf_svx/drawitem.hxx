/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drawitem.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:28:16 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SVX_DRAWITEM_HXX
#define _SVX_DRAWITEM_HXX

// include ---------------------------------------------------------------

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


    virtual int             operator==( const SfxPoolItem& ) const;
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


    virtual int             operator==( const SfxPoolItem& ) const;
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


    virtual int             operator==( const SfxPoolItem& ) const;
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


    virtual int             operator==( const SfxPoolItem& ) const;
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


    virtual int             operator==( const SfxPoolItem& ) const;
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

