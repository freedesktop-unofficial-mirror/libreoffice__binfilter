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

#ifndef _SD_ANMINFO_HXX
#define _SD_ANMINFO_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/presentation/AnimationEffect.hpp>
#include <com/sun/star/presentation/AnimationSpeed.hpp>
#include <com/sun/star/presentation/ClickAction.hpp>

#include <bf_svx/svdobj.hxx>
#include <tools/color.hxx>
class Polygon;
class Point;
class SvStream;
namespace binfilter {

class SdrObjSurrogate;
class SdrObject;
class SdrPathObj;
class SdDrawDocument;

class SdAnimationInfo : public SdrObjUserData, public SfxListener
{
private:

    SdDrawDocument*         pDoc;

public:

    Polygon*                pPolygon;       // fuer nichtlinearen Pfad (unbenutzt)
    Point                   aStart;         // Startpunkt eines linearen Pfades (unbenutzt)
    Point                   aEnd;           // Endpunkt eines linearen Pfades (unbenutzt)
    ::com::sun::star::presentation::AnimationEffect         eEffect;        // Animationseffekt
    ::com::sun::star::presentation::AnimationEffect         eTextEffect;    // Animationseffekt fuer Textinhalt
    ::com::sun::star::presentation::AnimationSpeed          eSpeed;         // Geschwindigkeit der Animation
    BOOL                    bActive;        // eingeschaltet ?
    BOOL                    bDimPrevious;   // Objekt abblenden
    BOOL                    bIsMovie;       // wenn Gruppenobjekt, dann Sequenz aus den
    BOOL                    bDimHide;       // verstecken statt abblenden
    Color                   aBlueScreen;    // identifiziert "Hintergrundpixel"
    Color                   aDimColor;      // zum Abblenden des Objekts
    String                  aSoundFile;     // Pfad zum Soundfile in MSDOS-Notation
    BOOL                    bSoundOn;       // Sound ein/aus
    BOOL                    bPlayFull;      // Sound ganz abspielen
    SdrObjSurrogate*        pPathSuro;      // Surrogat fuer pPathObj
    SdrPathObj*             pPathObj;       // das Pfadobjekt
    ::com::sun::star::presentation::ClickAction             eClickAction;   // Aktion bei Mausklick
    ::com::sun::star::presentation::AnimationEffect         eSecondEffect;  // fuer Objekt ausblenden
    ::com::sun::star::presentation::AnimationSpeed          eSecondSpeed;   // fuer Objekt ausblenden
    String                  aSecondSoundFile; // fuer Objekt ausblenden
    BOOL                    bSecondSoundOn; // fuer Objekt ausblenden
    BOOL                    bSecondPlayFull;// fuer Objekt ausblenden
    String                  aBookmark;      // Sprung zu Objekt/Seite
    USHORT                  nVerb;          // fuer OLE-Objekt
    BOOL                    bInvisibleInPresentation;
    BOOL                    bIsShown;       // in der Show gerade sichtbar, NICHT PERSISTENT!
    BOOL                    bShow;          // Befehl: mit 1. Effekt zeigen (TRUE)
                                            // oder mit 2. Effekt entfernen (FALSE)
                                            // NICHT PERSISTENT!
    BOOL                    bDimmed;        // in der Show abgeblendet (TRUE) oder
                                            // nicht (TRUE)
                                            // NICHT PERSISTENT!
    ULONG                   nPresOrder;

                            SdAnimationInfo(SdDrawDocument* pTheDoc);
                            SdAnimationInfo(const SdAnimationInfo& rAnmInfo);
    virtual                 ~SdAnimationInfo();

    virtual SdrObjUserData* Clone(SdrObject* /*pObj*/) const {DBG_BF_ASSERT(0, "STRIP"); return NULL;}

    virtual void            ReadData(SvStream& rIn);

            // NULL loest die Verbindung zum Pfadobjekt
    virtual void            AfterRead();
};

} //namespace binfilter
#endif // _SD_ANMINFO_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
