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
#ifndef _SXMTPITM_HXX
#define _SXMTPITM_HXX

#include <bf_svx/svddef.hxx>

#include <bf_svtools/eitem.hxx>
namespace binfilter {

enum SdrMeasureTextHPos {SDRMEASURE_TEXTHAUTO,SDRMEASURE_TEXTLEFTOUTSIDE,SDRMEASURE_TEXTINSIDE,SDRMEASURE_TEXTRIGHTOUTSIDE};
enum SdrMeasureTextVPos {SDRMEASURE_TEXTVAUTO,SDRMEASURE_ABOVE,SDRMEASURETEXT_BREAKEDLINE,SDRMEASURE_BELOW,SDRMEASURETEXT_VERTICALCENTERED};

//------------------------------
// class SdrMeasureTextHPosItem
//------------------------------
class SdrMeasureTextHPosItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrMeasureTextHPosItem(SdrMeasureTextHPos ePos=SDRMEASURE_TEXTHAUTO): SfxEnumItem(SDRATTR_MEASURETEXTHPOS,ePos) {}
    SdrMeasureTextHPosItem(SvStream& rIn)                               : SfxEnumItem(SDRATTR_MEASURETEXTHPOS,rIn)    {}
    virtual SfxPoolItem*   Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*   Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT         GetValueCount() const; // { return 4; }
            SdrMeasureTextHPos GetValue() const { return (SdrMeasureTextHPos)SfxEnumItem::GetValue(); }


};

//------------------------------
// class SdrMeasureTextVPosItem
//------------------------------
class SdrMeasureTextVPosItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrMeasureTextVPosItem(SdrMeasureTextVPos ePos=SDRMEASURE_TEXTVAUTO): SfxEnumItem(SDRATTR_MEASURETEXTVPOS,ePos) {}
    SdrMeasureTextVPosItem(SvStream& rIn)                               : SfxEnumItem(SDRATTR_MEASURETEXTVPOS,rIn)    {}
    virtual SfxPoolItem*   Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*   Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT         GetValueCount() const; // { return 5; }
            SdrMeasureTextVPos GetValue() const { return (SdrMeasureTextVPos)SfxEnumItem::GetValue(); }


};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
