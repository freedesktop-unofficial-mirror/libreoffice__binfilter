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

#ifndef _B3D_B3DCOLOR_HXX
#define _B3D_B3DCOLOR_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/color.hxx>

/*************************************************************************
|*
|* Farbklasse fuer 3D. Besitzt einige Funktionen mehr, als die normale
|* Farbe
|*
\************************************************************************/

namespace binfilter {
class B3dColor : public Color
{
public:
    B3dColor() : Color() {}
    B3dColor( ColorData nColor ) : Color(nColor) {}
    B3dColor( UINT8 nRed, UINT8 nGreen, UINT8 nBlue )
        : Color(nRed, nGreen, nBlue) {}
    B3dColor( UINT8 nTransparency, UINT8 nRed, UINT8 nGreen, UINT8 nBlue )
        : Color(nTransparency, nRed, nGreen, nBlue) {}
    B3dColor( const ResId& rResId ) : Color(rResId) {}
    B3dColor( const Color& rCol ) : Color(rCol) {}

    void CalcInBetween(Color& rOld1, Color& rOld2, double t);
    void CalcMiddle(Color& rOld1, Color& rOld2);

    // Addition, Subtraktion mit clamping
    B3dColor&   operator+=  (const B3dColor&);
    B3dColor&   operator-=  (const B3dColor&);
    B3dColor    operator+   (const B3dColor&) const;
    B3dColor    operator-   (const B3dColor&) const;

    // Multiplikation als Gewichtung, Anwendung einer Lampe
    // auf eine Farbe, Lampe als 2.Faktor
    B3dColor&   operator*=  (const B3dColor&);
    B3dColor    operator*   (const B3dColor&) const;

    // Multiplikation mit Faktor im Bereich [0.0 .. 1.0]
    B3dColor&   operator*=  (const double);
    B3dColor    operator*   (const double) const;

    // Zuweisung
    void operator=(const Color& rCol) { mnColor = rCol.GetColor(); }
};
}//end of namespace binfilter

#endif          // _B3D_B3DCOLOR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
