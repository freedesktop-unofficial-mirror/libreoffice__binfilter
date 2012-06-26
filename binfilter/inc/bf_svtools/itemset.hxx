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
#ifndef _SFXITEMSET_HXX
#define _SFXITEMSET_HXX

#include <cstdarg>  // std::va_list and friends

#include <bf_svtools/poolitem.hxx>
#include <tools/rtti.hxx>
#include <bf_svtools/bf_solar.h>

class SvStream;

namespace binfilter
{

class SfxItemPool;
class SfxPoolItem;

typedef SfxPoolItem const** SfxItemArray;

#define USHORT_ARG int

#ifdef MI_HATS_REPARIERT
#ifndef DBG
#ifdef DBG_UTILx
#define DBG(s) s
#define _pChildCount(THIS)  (  *(USHORT**)SfxPointerServer::GetServer()->GetPointer(THIS) )
#define _pChildCountCtor    ( (*(USHORT**)SfxPointerServer::GetServer()->CreatePointer(this)) = new USHORT )
#define _pChildCountDtor    ( SfxPointerServer::GetServer()->ReleasePointer(this) )
#else
#define DBG(s)
#endif
#endif
#else
#ifdef DBG
#undef DBG
#endif
#define DBG(s)
#endif

//========================================================================

#define SFX_ITEMSET_GET( rSet, pItem, ItemType, nSlotId, bDeep ) \
    const ItemType *pItem = (const ItemType*) \
                            (rSet).GetItem( nSlotId, bDeep, TYPE(ItemType) )

//========================================================================

class  SfxItemSet
{
    friend class SfxItemIter;

    SfxItemPool*                _pPool;         // der verwendete Pool
    const SfxItemSet*           _pParent;       // Ableitung
    SfxItemArray                _aItems;        // Item-Feld
    USHORT*                     _pWhichRanges;  // Array von Which-Bereichen
    USHORT                      _nCount;        // Anzahl Items

    //---------------------------------------------------------------------
#ifndef _SFXITEMS_HXX

friend class SfxItemPoolCache;
friend class SfxAllItemSet;
friend const char *DbgCheckItemSet( const void* );

private:
     void                       InitRanges_Impl(const USHORT *nWhichPairTable);
     void                       InitRanges_Impl(va_list pWhich, USHORT n1, USHORT n2, USHORT n3);
     void                       InitRanges_Impl(USHORT nWh1, USHORT nWh2);

public:
    SfxItemArray                GetItems_Impl() const { return _aItems; }

#endif
    //---------------------------------------------------------------------

private:
    const SfxItemSet&           operator=(const SfxItemSet &);   // n.i.!!

protected:
    // Notification-Callback
    virtual void                Changed( const SfxPoolItem& rOld, const SfxPoolItem& rNew );

    // direkte Put-Methode
    int                         PutDirect(const SfxPoolItem &rItem);

public:
                                SfxItemSet( const SfxItemSet& );

                                SfxItemSet( SfxItemPool&, BOOL bTotalPoolRanges = FALSE );
                                SfxItemSet( SfxItemPool&, USHORT nWhich1, USHORT nWhich2 );
                                SfxItemSet( SfxItemPool&, USHORT_ARG nWh1, USHORT_ARG nWh2, USHORT_ARG nNull, ... );
                                SfxItemSet( SfxItemPool&, const USHORT* nWhichPairTable );
    virtual                     ~SfxItemSet();

    virtual SfxItemSet *        Clone(BOOL bItems = TRUE, SfxItemPool *pToPool = 0) const;

    // Items erfragen
    USHORT                      Count() const { return _nCount; }
    USHORT                      TotalCount() const;

    virtual const SfxPoolItem&  Get( USHORT nWhich, BOOL bSrchInParent = TRUE ) const;
    const SfxPoolItem*          GetItem( USHORT nWhich, BOOL bSrchInParent = TRUE,
                                         TypeId aItemType = 0 ) const;

    // Which-Wert des Items an der Position nPos erfragen
    USHORT                      GetWhichByPos(USHORT nPos) const;

    // Item-Status erfragen
    SfxItemState                GetItemState(   USHORT nWhich,
                                                BOOL bSrchInParent = TRUE,
                                                const SfxPoolItem **ppItem = 0 ) const;

    virtual void                DisableItem(USHORT nWhich);
    virtual void                InvalidateItem( USHORT nWhich );
    virtual USHORT              ClearItem( USHORT nWhich = 0);
    virtual void                ClearInvalidItems( BOOL bHardDefault = FALSE );
            void                InvalidateAllItems(); HACK(via nWhich = 0)

    inline void                 SetParent( const SfxItemSet* pNew );

    // Items hinzufuegen, loeschen etc.
    virtual const SfxPoolItem*  Put( const SfxPoolItem&, USHORT nWhich );
    const SfxPoolItem*          Put( const SfxPoolItem& rItem )
                                { return Put(rItem, rItem.Which()); }
    virtual int                 Put( const SfxItemSet&,
                                     BOOL bInvalidAsDefault = TRUE );
    void                        PutExtended( const SfxItemSet&,
                                             SfxItemState eDontCareAs = SFX_ITEM_UNKNOWN,
                                             SfxItemState eDefaultAs = SFX_ITEM_UNKNOWN );

    virtual int                 Set( const SfxItemSet&, BOOL bDeep = TRUE );

    virtual void                Intersect( const SfxItemSet& rSet );
    virtual void                MergeValues( const SfxItemSet& rSet, BOOL bOverwriteDefaults = FALSE );
    virtual void                Differentiate( const SfxItemSet& rSet );
    virtual void                MergeValue( const SfxPoolItem& rItem, BOOL bOverwriteDefaults = FALSE  );

    SfxItemPool*                GetPool() const { return _pPool; }
    const USHORT*               GetRanges() const { return _pWhichRanges; }
    const SfxItemSet*           GetParent() const { return _pParent; }

    virtual SvStream &          Load( SvStream &, bool bDirect = FALSE,
                                      const SfxItemPool *pRefPool = 0 );
    virtual SvStream & Store( SvStream &rStream, bool /*bDirect*/ = FALSE ) const { return rStream; }

    virtual int                 operator==(const SfxItemSet &) const;
};

// --------------- Inline Implementierungen ------------------------

inline void SfxItemSet::SetParent( const SfxItemSet* pNew )
{
    DBG( if (_pParent) --*_pChildCount(_pParent) );
    _pParent = pNew;
    DBG( if (_pParent) ++*_pChildCount(_pParent) );
}

//========================================================================

class  SfxAllItemSet: public SfxItemSet

/*  versteht alle Ranges; werden durch das Putten der Items
    automatisch angepasst
*/

{
    SfxVoidItem                 aDefault;
    USHORT                      nFree;

public:
                                SfxAllItemSet( SfxItemPool &rPool );
                                SfxAllItemSet( const SfxItemSet & );
                                SfxAllItemSet( const SfxAllItemSet & );

    virtual SfxItemSet *        Clone( BOOL bItems = TRUE, SfxItemPool *pToPool = 0 ) const;
    virtual const SfxPoolItem*  Put( const SfxPoolItem&, USHORT nWhich );
    const SfxPoolItem*          Put( const SfxPoolItem& rItem )
    { return Put(rItem, rItem.Which()); }
    virtual int                 Put( const SfxItemSet&,
                                     BOOL bInvalidAsDefault = TRUE );
};

}

#endif // #ifndef _SFXITEMSET_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
