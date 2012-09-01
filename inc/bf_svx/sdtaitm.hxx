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
#ifndef _SDTAITM_HXX
#define _SDTAITM_HXX

#include <bf_svtools/eitem.hxx>

#include <bf_svx/svddef.hxx>
namespace binfilter {

//------------------------------
// class SdrTextVertAdjustItem
//------------------------------

// Implementiert werden zunaechst nur TOP und CENTER, neustens auch BOTTOM
enum SdrTextVertAdjust {SDRTEXTVERTADJUST_TOP,      // Kopfbuendig (so wie man es normalerweise kennt)
                        SDRTEXTVERTADJUST_CENTER,   // Zentriert (z.B. fuer die Titeltexte im Draw)
                        SDRTEXTVERTADJUST_BOTTOM,   // Fussbuendig
                        SDRTEXTVERTADJUST_BLOCK    // #103516# support vertical full with supported now
                        /*,SDRTEXTVERTADJUST_STRETCH*/}; // Auch die Buchstaben in der Hoehe verzerren (ni)

class SdrTextVertAdjustItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrTextVertAdjustItem(SdrTextVertAdjust eAdj=SDRTEXTVERTADJUST_TOP): SfxEnumItem(SDRATTR_TEXT_VERTADJUST,eAdj) {}
    SdrTextVertAdjustItem(SvStream& rIn)                               : SfxEnumItem(SDRATTR_TEXT_VERTADJUST,rIn)  {}
    virtual SfxPoolItem*      Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*      Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT            GetValueCount() const; // { return 5; }
            SdrTextVertAdjust GetValue() const      { return (SdrTextVertAdjust)SfxEnumItem::GetValue(); }

    virtual bool              QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool              PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

};

//------------------------------
// class SdrTextHorzAdjustItem
//------------------------------

enum SdrTextHorzAdjust {SDRTEXTHORZADJUST_LEFT,     // Linksbuendig verankert
                        SDRTEXTHORZADJUST_CENTER,   // Zentriert (z.B. fuer die Titeltexte im Draw)
                        SDRTEXTHORZADJUST_RIGHT,    // Rechtsbuendig verankert
                        SDRTEXTHORZADJUST_BLOCK    // So wie es frueher war: Gesamte Textrahmenbreite verwenden, Absatzformatierung macht wieder Sinn
                        /*,SDRTEXTHORZADJUST_STRETCH*/}; // FitToSize in X-Richtung (ni).

class SdrTextHorzAdjustItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrTextHorzAdjustItem(SdrTextHorzAdjust eAdj=SDRTEXTHORZADJUST_BLOCK): SfxEnumItem(SDRATTR_TEXT_HORZADJUST,eAdj) {}
    SdrTextHorzAdjustItem(SvStream& rIn)                                 : SfxEnumItem(SDRATTR_TEXT_HORZADJUST,rIn)  {}
    virtual SfxPoolItem*      Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*      Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT            GetValueCount() const; // { return 5; }
            SdrTextHorzAdjust GetValue() const      { return (SdrTextHorzAdjust)SfxEnumItem::GetValue(); }

    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual String  GetValueTextByPos(USHORT nPos) const;
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
