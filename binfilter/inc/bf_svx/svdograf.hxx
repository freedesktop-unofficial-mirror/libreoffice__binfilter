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

#ifndef _SVDOGRAF_HXX
#define _SVDOGRAF_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/graph.hxx>
#include <bf_svx/svdorect.hxx>
#include <bf_goodies/graphicobject.hxx>
namespace binfilter {
class BfGraphicObject;

// -----------
// - Defines -
// -----------

#define SDRGRAFOBJ_TRANSFORMATTR_NONE       0x00000000UL
#define SDRGRAFOBJ_TRANSFORMATTR_COLOR      0x00000001UL
#define SDRGRAFOBJ_TRANSFORMATTR_MIRROR     0x00000002UL
#define SDRGRAFOBJ_TRANSFORMATTR_ROTATE     0x00000004UL
#define SDRGRAFOBJ_TRANSFORMATTR_ALL        0xffffffffUL

// ---------------------
// - SdrGrafObjGeoData -
// ---------------------

class Animation;

class SdrGrafObjGeoData : public SdrRectObjGeoData
{
public:

    bool    bMirrored;

                SdrGrafObjGeoData() :
                    bMirrored( FALSE ) {}
};

// --------------
// - SdrGrafObj -
// --------------

class SdrGraphicLink;

class SdrGrafObj: public SdrRectObj
{

    friend class SdrGraphicLink;

protected:

    void                    ImpSetAttrToGrafInfo(); // Werte vom Pool kopieren
    void                    ImpSetGrafInfoToAttr(); // Werte in den Pool kopieren
    BfGraphicAttr           aGrafInfo;
    bool                    bCopyToPoolOnAfterRead;

    String                  aName;

    Rectangle               aCropRect;          // Wenn aCropRect nicht Empty ist, dann enthaelt es den sichtbaren
                                                // Ausschnitt der Grafik in logischen Eingeiten der Grafik! Also Bitmap->=Pixel
    String                  aFileName;          // Wenn es sich um einen Link handelt, steht hier der Dateiname drin.
    String                  aFilterName;
    BfGraphicObject*        pGraphic;           // Zur Beschleunigung von Bitmapausgaben, besonders von gedrehten.
    SdrGraphicLink*         pGraphicLink;       // Und hier noch ein Pointer fuer gelinkte Grafiken
    bool                    bMirrored;          // True bedeutet, die Grafik ist horizontal, d.h. ueber die Y-Achse gespiegelt auszugeben.
    ULONG                   nGrafStreamPos;

#if _SOLAR__PRIVATE

    void                    ImpLinkAnmeldung();
    void                    ImpLinkAbmeldung();
    void                    ImpPaintReplacement(OutputDevice* pOutDev, const XubString& rText, const Bitmap* pBmp, bool bFill) const;

    sal_Bool                ImpUpdateGraphicLink() const;

                            DECL_LINK( ImpSwapHdl, BfGraphicObject* );

#endif // __PRIVATE

public:

                            TYPEINFO();

                            SdrGrafObj();
                            SdrGrafObj(const Graphic& rGrf);
    virtual                 ~SdrGrafObj();

    void                    SetGraphicObject( const BfGraphicObject& rGrfObj );
    const BfGraphicObject&  GetGraphicObject() const;

    void                    SetGraphic(const Graphic& rGrf);
    const Graphic&          GetGraphic() const;

    GraphicType             GetGraphicType() const;

    void                    SetGrafStreamURL( const String& rGraphicStreamURL );
    String                  GetGrafStreamURL() const { return String(); } // DBG_BF_ASSERT

    void                    ForceSwapIn() const;
    void                    ForceSwapOut() const;

    void                    SetGraphicLink(const String& rFileName, const String& rFilterName);
    void                    ReleaseGraphicLink();
    bool                    IsLinkedGraphic() const { return (BOOL)aFileName.Len(); }

    const String&           GetFileName() const { return aFileName; }
    const String&           GetFilterName() const { return aFilterName; }



    virtual void            SetName(const String& rStr);
    virtual String          GetName() const;

    virtual UINT16          GetObjIdentifier() const;
    virtual bool            Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject*      CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;


    virtual void            operator=(const SdrObject& rObj);

    virtual void            NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void            NbcRotate(const Point& rRef, long nWink, double sn, double cs);
    virtual void            NbcSetSnapRect(const Rectangle& rRect);
    virtual void            NbcSetLogicRect(const Rectangle& rRect);
    virtual SdrObjGeoData*  NewGeoData() const;
    virtual void            SaveGeoData(SdrObjGeoData& rGeo) const;
    virtual void            RestartAnimation(SdrPageView* pPageView) const;

    virtual void            SetPage(SdrPage* pNewPage);
    virtual void            SetModel(SdrModel* pNewModel);
    virtual void            ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    void                    ReadDataTilV10(const SdrObjIOHeader& rHead, SvStream& rIn);

    void                    AdjustToMaxRect( const Rectangle& rMaxRect, BOOL bShrinkOnly );

    virtual void            SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                                        const SfxHint& rHint, const TypeId& rHintType );
    virtual void            ForceDefaultAttr();
    virtual void            NbcSetStyleSheet( SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr );

    // ItemSet access
    virtual SfxItemSet*     CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void            ItemSetChanged(const SfxItemSet& rSet);

    virtual void            AfterRead();

    BOOL                    IsMirrored() { return bMirrored; }
    void                    SetMirrored( sal_Bool _bMirrored ) { bMirrored = _bMirrored; }
};

}//end of namespace binfilter
#endif //_SVDOGRAF_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
