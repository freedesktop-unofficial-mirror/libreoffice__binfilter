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

#ifndef _SVDOVIRT_HXX
#define _SVDOVIRT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdobj.hxx>
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   SdrVirtObj
//
// Achtung! Das virtuelle Objekt ist noch nicht bis in alle Feinheiten
// durchprogrammiert und getestet. Z.Zt. kommt es nur in abgeleiteter
// beim Writer zum Einsatz.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrVirtObj : public SdrObject
{
protected:
    SdrObject&                  rRefObj; // Referenziertes Zeichenobjekt
    Rectangle                   aSnapRect;
    Point                       aHack;   // f. GetPoint()

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

    virtual SdrObjGeoData* NewGeoData() const;
    virtual void SaveGeoData(SdrObjGeoData& rGeo) const;
    virtual void RestGeoData(const SdrObjGeoData& rGeo);

public:
    TYPEINFO();
    SdrVirtObj(SdrObject& rNewObj);
    virtual ~SdrVirtObj();
    using SdrObject::operator=;
    virtual SdrObject& ReferencedObj();
    virtual const SdrObject& GetReferencedObj() const;
    virtual void SetModel(SdrModel* pNewModel);

    virtual UINT32 GetObjInventor() const;
    virtual UINT16 GetObjIdentifier() const;
    virtual SdrObjList* GetSubList() const;

    virtual void SetChanged();


    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);

    virtual void Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);

    virtual void RecalcSnapRect();


    virtual long GetRotateAngle() const;
    virtual long GetShearAngle(bool bVertical=FALSE) const;


    virtual void NbcSetPoint(const Point& rPnt, USHORT i);


    // ItemSet access
    virtual const SfxItemSet& GetItemSet() const;
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);
    virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    virtual void AfterRead();

    // OD 30.06.2003 #108784# - virtual <GetOffset()> returns Point(0,0)
    virtual const Point GetOffset() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOVIRT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
