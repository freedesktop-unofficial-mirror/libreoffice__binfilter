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

#ifndef _SVDOATTR_HXX
#define _SVDOATTR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/xfillit0.hxx>

#include <bf_svx/xflasit.hxx>

#include <bf_svx/xlineit0.hxx>

#include <bf_svx/xlnasit.hxx>

#include <bf_svx/svdobj.hxx>

#include <bf_svx/svdattr.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SfxPoolItem;
class SfxSetItem;
class SfxItemSet;
class SfxItemPool;

class SdrOutliner;

//************************************************************
//   SdrAttrObj
//************************************************************

class SdrAttrObj : public SdrObject
{
    friend class                SdrOutliner;

protected:
    Rectangle                   maSnapRect;
    SfxStyleSheet               *mpStyleSheet;
    SfxItemSet                  *mpObjectItemSet;

    void ImpDeleteItemSet();
    void ImpForceItemSet();

protected:
    // Strichstaerke ermitteln. Keine Linie -> 0.
    INT32 ImpGetLineWdt() const;

    // Feststellen, wieviel wegen der Linienenden auf's BoundRect draufaddiert werden muss.
    INT32 ImpGetLineEndAdd() const;

    // HitTest auf's Linienende
    // ueber nSin/nCos wird der Winkel vorgegeben

    // Schattenabstand ermitteln. FALSE=Kein Schatten.
    bool ImpGetShadowDist(sal_Int32& nXDist, sal_Int32& nYDist) const;

    // ggf. Schattenversatz zum BoundRect draufaddieren
    void ImpAddShadowToBoundRect();

    // Line und Fill Attribute fuer Schatten setzen.
    // Return=FALSE: kein Schatten attributiert.
    bool ImpSetShadowAttributes( const SfxItemSet& rSet, SfxItemSet& rShadowSet ) const;

    // Zuhoeren, ob sich ein StyleSheet aendert
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);
    virtual void RemoveStyleSheet();
    virtual void AddStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);

    // aus NULL-AttrPointern Pointer auf defaults machen
    virtual void ForceDefaultAttr();
    SdrAttrObj();
    virtual ~SdrAttrObj();

public:
    TYPEINFO();

    // Feststellen, ob bFilledObj && Fuellung!=FillNone
    BOOL HasFill() const;

    // Feststellen, ob Linie!=LineNone
    BOOL HasLine() const;

    virtual const Rectangle& GetSnapRect() const;
    virtual void operator=(const SdrObject& rObj);
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    virtual void SetModel(SdrModel* pNewModel);

    // ItemSet access
    virtual const SfxItemSet& GetItemSet() const;
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // syntactical sugar for ItemSet accesses
    const SfxItemSet& GetUnmergedItemSet() const;

    // t support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual SfxStyleSheet* GetStyleSheet() const;
    virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);
    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);


    // ItemPool fuer dieses Objekt wechseln
    virtual void MigrateItemPool(SfxItemPool* pSrcPool, SfxItemPool* pDestPool, SdrModel* pNewModel = NULL );
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOATTR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
