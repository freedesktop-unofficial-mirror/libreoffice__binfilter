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

#ifndef _SVDGLEV_HXX
#define _SVDGLEV_HXX

#include <bf_svtools/bf_solar.h>

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#include <bf_svx/svdhdl.hxx>

#include <bf_svx/svdpoev.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrGluePoint;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GLUE EDIT VIEW
//
//  Editieren von Klebepunkten an den Objekten (Klebepunkte fuer Verbinder)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrGlueEditView: public SdrPolyEditView
{
    void ImpClearVars();

    // Markierte Klebepunkte kopieren und anstelle der alten markieren
    typedef void (*PGlueDoFunc)(SdrGluePoint&, const SdrObject* pObj, const void*, const void*, const void*, const void*, const void*);
    typedef void (*PGlueTrFunc)(Point&, const void*, const void*, const void*, const void*, const void*);

public:
    SdrGlueEditView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    virtual ~SdrGlueEditView();

    // Durch den Parameter nThisEsc uebergibt man die Richtung, die man
    // checken bzw. setzen/loeschen will.
    // Moegliche Werte fuer nThisEsc sind z.Zt.
    // SDRESC_LEFT, SDRESC_RIGHT, SDRESC_TOP und SDRESC_BOTTOM
    BOOL IsSetMarkedGluePointsEscDirPossible() const { return !IsReadOnly() && HasMarkedGluePoints(); }

    // Checken/setzen, ob die Klebepunktpositionen relativ zur
    // Objektgroesse sind (Percent=TRUE) oder nicht (Percent=FALSE)
    BOOL IsSetMarkedGluePointsPercentPossible() const { return !IsReadOnly() && HasMarkedGluePoints(); }

    // bVert=FALSE: Horizontales Alignment checken/setzen
    //      SDRHORZALIGN_CENTER
    //      SDRHORZALIGN_LEFT
    //      SDRHORZALIGN_RIGHT
    //      SDRHORZALIGN_DONTCARE (nur bei Get())
    // bVert=TRUE: Vertikales Alignment checken/setzen
    //      SDRVERTALIGN_CENTER
    //      SDRVERTALIGN_TOP
    //      SDRVERTALIGN_BOTTOM
    //      SDRVERTALIGN_DONTCARE (nur bei Get())

    // Alle merkierten Klebepunkte entfernen

    void MirrorMarkedGluePoints(const Point& rRef1, const Point& rRef2, BOOL bCopy=FALSE);
    void MirrorMarkedGluePointsHorizontal(BOOL bCopy=FALSE);
    void MirrorMarkedGluePointsVertical(BOOL bCopy=FALSE);
    void ShearMarkedGluePoints(const Point& rRef, long nWink, BOOL bVShear=FALSE, BOOL bCopy=FALSE);
    void CrookMarkedGluePoints(const Point& rRef, const Point& rRad, SdrCrookMode eMode, BOOL bVertical=FALSE, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);
    void DistortMarkedGluePoints(const Rectangle& rRef, const XPolygon& rDistortedRect, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);

    void AlignMarkedGluePoints(SdrHorAlign eHor, SdrVertAlign eVert);
};

}//end of namespace binfilter
#endif //_SVDGLEV_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
