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

#ifndef _SVDCAPT_HXX
#define _SVDCAPT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdorect.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrCaptionSetItem;
class ImpCaptParams;

#define SDRSETITEM_CAPTION_ATTR     SDRSETITEM_ATTR_COUNT

//************************************************************
//   Hilfsklasse SdrCaptObjGeoData
//************************************************************

class SdrCaptObjGeoData : public SdrRectObjGeoData
{
public:
    Polygon                     aTailPoly;
};

//************************************************************
//   SdrCaptionObj
//************************************************************

class SdrCaptionObj : public SdrRectObj
{
    friend class                SdrTextObj; // fuer ImpRecalcTail() bei AutoGrow

protected:
    Polygon                     aTailPoly;  // das ganze Polygon des Schwanzes
    sal_Bool                    mbSpecialTextBoxShadow; // for calc special shadow, default FALSE

private:
    void ImpGetCaptParams(ImpCaptParams& rPara) const;
    void ImpCalcTail3(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
    void ImpCalcTail (const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
    void ImpRecalcTail();

public:
    TYPEINFO();
    SdrCaptionObj();
    virtual ~SdrCaptionObj();
    using SdrRectObj::operator=;

    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();

    // for calc: special shadow only for text box
    void SetSpecialTextBoxShadow() { mbSpecialTextBoxShadow = TRUE; }


    virtual void SetModel(SdrModel* pNewModel);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);

    virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);

    virtual void NbcSetAnchorPos(const Point& rPnt);
    virtual const Point& GetAnchorPos() const;

    virtual void RecalcSnapRect();
    virtual const Rectangle& GetSnapRect() const;
    virtual void NbcSetSnapRect(const Rectangle& rRect);


public:

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    const Point& GetTailPos() const;
    void SetTailPos(const Point& rPos);
    void NbcSetTailPos(const Point& rPos);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOCAPT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
