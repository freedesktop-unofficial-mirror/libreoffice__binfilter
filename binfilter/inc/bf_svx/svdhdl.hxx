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

#ifndef _SVDHDL_HXX
#define _SVDHDL_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/gen.hxx>

#include <vcl/pointr.hxx>

#include <tools/contnr.hxx>

#include <bf_svx/svdoedge.hxx>

class VirtualDevice;
class OutputDevice;
class Region;
class Window;

namespace binfilter {

class SdrObject;
class SdrPageView;
class SdrHdlBitmapSet;
class SdrMarkView;

////////////////////////////////////////////////////////////////////////////////////////////////////

// Jedes Objekt muss in der Lage seine Handles zu erzeugen. Diese werden dann
// bei einer Selektion abgeholt, bei der View angemeldet und sichtbar gemacht.
// Wird ein Handle von der Maus beruehrt (IsHit()), so wird von der View der
// entsprechende Mauszeiger vom Handle abgeholt und der App auf Anfrage zum
// reinschalten uebergeben.
// Handles wie z.B. der Rotationsmittelpunkt oder die Spiegelachse werden von
// der View generiert, wenn vom Controller der entsprechende Transformations-
// Modus selektiert wird.
// HDL_MOVE...HDL_LWRGT muessen im enum immer zusammen stehen bleiben!

enum SdrHdlKind
{
    HDL_MOVE,       // Handle zum Verschieben des Objekts
    HDL_UPLFT,      // Oben links
    HDL_UPPER,      // Oben
    HDL_UPRGT,      // Oben rechts
    HDL_LEFT,       // Links
    HDL_RIGHT,      // Rechts
    HDL_LWLFT,      // Unten links
    HDL_LOWER,      // Unten
    HDL_LWRGT,      // Unten rechts
    HDL_POLY,       // Punktselektion an Polygon oder Bezierkurve
    HDL_BWGT,       // Gewicht an einer Bezierkurve
    HDL_CIRC,       // Winkel an Kreissegmenten, Eckenradius am Rect
    HDL_REF1,       // Referenzpunkt 1, z.B. Rotationsmitte
    HDL_REF2,       // Referenzpunkt 2, z.B. Endpunkt der Spiegelachse
    HDL_MIRX,       // Die Spiegelachse selbst
    HDL_GLUE,       // GluePoint
    HDL_ANCHOR,     // anchor symbol (SD, SW)
    HDL_TRNS,       // interactive transparence
    HDL_GRAD,       // interactive gradient
    HDL_COLR,       // interactive color
    HDL_USER,
    HDL_ANCHOR_TR   // #101688# Anchor handle with (0,0) at top right for SW
};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum BitmapColorIndex
{
    LightGreen,
    Cyan,
    LightCyan,
    Red,
    LightRed
};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum BitmapMarkerKind
{
    Rect_7x7,
    Rect_9x9,
    Rect_11x11,
    Rect_13x13,
    Circ_7x7,
    Circ_9x9,
    Circ_11x11,
    Elli_7x9,
    Elli_9x11,
    Elli_9x7,
    Elli_11x9,
    RectPlus_7x7,
    RectPlus_9x9,
    RectPlus_11x11,
    Crosshair,
    Glue,
    Anchor,

    // #98388# add AnchorPressed to be able to aninate anchor control, too.
    AnchorPressed,

    // #101688# AnchorTR for SW
    AnchorTR,
    AnchorPressedTR
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrHdl
{
    friend class                SdrMarkView; // fuer den Zugriff auf nObjHdlNum
public:
    virtual ~SdrHdl();

    SdrHdlKind GetKind() const { return HDL_MOVE; }
    SdrObject* GetObj() const { return NULL;  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#define SDR_HANDLE_COLOR_SIZE_NORMAL            Size(13, 13)
#define SDR_HANDLE_COLOR_SIZE_SELECTED          Size(17, 17)


////////////////////////////////////////////////////////////////////////////////////////////////////



class ImplHdlListData;

class SdrHdlList
{
protected:
    ImplHdlListData*            pImpl;

    Container                   aList;
    USHORT                      nHdlSize;

    unsigned                    bRotateShear : 1;
    unsigned                    bDistortShear : 1;
    unsigned                    bMoveOutside : 1;      // Handles nach aussen ruecken (fuer TextEdit)

private:
    SdrHdlList(const SdrHdlList&): aList(1024,64,64)  {}
    void operator=(const SdrHdlList&)                 {}
    BOOL operator==(const SdrHdlList&) const      { return FALSE; }
    BOOL operator!=(const SdrHdlList&) const      { return FALSE; }

public:
    SdrHdlList(SdrMarkView* pV);
    ~SdrHdlList();
    void Clear();

    // Access to View
    SdrMarkView* GetView() const;

    // Sortierung: 1.Level Erst Refpunkt-Handles, dann normale Handles, dann Glue, dann User, dann Plushandles
    //             2.Level PageView (Pointer)
    //             3.Level Position (x+y)
    ULONG   GetHdlCount() const                 { return aList.Count(); }
    SdrHdl* GetHdl(ULONG nNum) const            { return (SdrHdl*)(aList.GetObject(nNum)); }
    USHORT  GetHdlSize() const                  { return nHdlSize; }

    BOOL    IsMoveOutside() const               { return bMoveOutside; }

    void    SetRotateShear(BOOL bOn)            { bRotateShear = bOn; }
    BOOL    IsRotateShear() const               { return bRotateShear; }

    void    SetDistortShear(BOOL bOn)           { bDistortShear = bOn; }
    BOOL    IsDistortShear() const              { return bDistortShear; }
};

}//end of namespace binfilter
#endif //_SVDHDL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
