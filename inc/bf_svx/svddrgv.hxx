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

#ifndef _SVDDRGV_HXX
#define _SVDDRGV_HXX

#include <bf_svtools/bf_solar.h>
#include <bf_svx/svdxcgv.hxx>

namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAGVIEW
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrDragView: public SdrExchangeView
{
    friend class                SdrPageView;

protected:
    unsigned                    bMarkedHitMovesAlways : 1; // Persistent
    unsigned                    bDragStripes : 1;    // Persistent
    unsigned                    bNoDragHdl : 1;      // Persistent - Handles waehrend des Draggens verstecken
    unsigned                    bMirrRefDragObj : 1; // Persistent - Waehrend des Draggens der Spiegelachse die gespiegelten Objekte als Xor zeigen
    unsigned                    bSolidDragging : 1;  // Dragging und Create in Echtzeit erlaubt
    unsigned                    bDragWithCopy : 1;
    unsigned                    bNoDragXorPolys : 1;

private:
    void ImpClearVars();

protected:
    virtual void WriteRecords(SvStream& rOut) const;
    virtual BOOL ReadRecord(const SdrIOHeader& rViewHead, const SdrNamedSubRecord& rSubHead, SvStream& rIn);

public:
    SdrDragView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    virtual ~SdrDragView();

    virtual void ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const;
    virtual BOOL IsAction() const;
    virtual void BrkAction();

    // Interaktives einfuegen eines neuen Punktes. nIdx=0 => vor dem ersten Punkt.
    BOOL IsInsObjPoint() const { return FALSE; }    // DBG_BF_ASSERT

    // Begrenzungslinien ueber's gesamte Win waehrend des Draggens
    // Persistent. Default=FALSE.
    void SetDragStripes(BOOL bOn);
    BOOL IsDragStripes() const { return bDragStripes; }

    // Beim Draggen werden i.d.R. die Konturen der markierten Objekte
    // als Xor-Polygone dargestellt. Wird dieses Flag hier gesetzt,
    // wird (z.B. bei Mehrfachselektion) nur ein Xor-Frame gezeichnet.
    // Bei objektspeziefischem Dragging (Polygonpunkte,Eckenradius,...
    // hat diese Einstellung keine Auswirkung.
    // Auch waerend des Draggens umschaltbar.
    // Default=Off
    void SetNoDragXorPolys(BOOL bOn);
    BOOL IsNoDragXorPolys() const { return bNoDragXorPolys; }

    void SetSolidDragging(BOOL bOn) { bSolidDragging = bOn; }
    BOOL IsSolidDragging() const { return bSolidDragging; }

    // Ist ein spezieller Dragmode eingeschaltet, wie Rotate, Mirror oder Crook,
    // dann leitet ein Hit auf das markierte Objekt genau dieses Dragging ein.
    // Setzt man MarkedHitMovesAlways auf TRUE, so leitet ein Hit auf das
    // markierte Objekt immer ein Moven ein, unabhaengig vom gesetzten DragMode.
    // Dieses Flag ist persistent und sollte von der App fuer den Anwender
    // konfigurierbar sein!
    void SetMarkedHitMovesAlways(BOOL bOn) { bMarkedHitMovesAlways = bOn; }
    BOOL IsMarkedHitMovesAlways() const { return bMarkedHitMovesAlways; }
};

}//end of namespace binfilter
#endif //_SVDDRGV_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
