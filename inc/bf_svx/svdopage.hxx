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

#ifndef _SVDOPAGE_HXX
#define _SVDOPAGE_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdobj.hxx>
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrPageObj : public SdrObject
{
    SfxItemSet*             mpPageItemSet;
    sal_uInt16              nPageNum;
    BOOL                    bPainting;  // Verriegelungsflag
    BOOL                    bNotifying; // Verriegelungsflag

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

public:
    TYPEINFO();
    SdrPageObj(USHORT nNewPageNum=0);
    ~SdrPageObj();
    using SdrObject::operator=;

    virtual void SetModel(SdrModel* pNewModel);
    USHORT GetPageNum() const { return nPageNum; }
    void SetPageNum(USHORT nNewPageNum)
        { NbcSetPageNum(nNewPageNum); SetChanged(); SendRepaintBroadcast(GetBoundRect()); }
    void NbcSetPageNum(USHORT nNewPageNum) { nPageNum=nNewPageNum; }

    virtual UINT16 GetObjIdentifier() const;


    virtual const Rectangle& GetBoundRect() const;
    virtual const Rectangle& GetSnapRect() const;
    virtual const Rectangle& GetLogicRect() const;
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);
    virtual const SfxItemSet& GetItemSet() const;
    // #86481# simply ignore item setting on page objects
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOPAGE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
