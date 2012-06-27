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
#ifndef _GOODIES_IMAPCIRC_HXX
#define _GOODIES_IMAPCIRC_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/gen.hxx>

#include <bf_svtools/imapobj.hxx>

class Fraction;

namespace binfilter
{

class  IMapCircleObject : public IMapObject
{
    Point               aCenter;
    ULONG               nRadius;

    void                ImpConstruct( const Point& rCenter, ULONG nRad, BOOL bPixel );

protected:

    // Binaer-Im-/Export
    virtual void        WriteIMapObject( SvStream& rOStm ) const;
    virtual void        ReadIMapObject(  SvStream& rIStm );

public:

                        IMapCircleObject() {};
                        IMapCircleObject( const Point& rCenter, ULONG nRad,
                                          const String& rURL,
                                          const String& rAltText,
                                          const String& rDesc,
                                          const String& rTarget,
                                          const String& rName,
                                          BOOL bActive = TRUE,
                                          BOOL bPixelCoords = TRUE );
    virtual             ~IMapCircleObject() {};

    virtual UINT16      GetType() const;
    virtual BOOL        IsHit( const Point& rPoint ) const;

    Point               GetCenter( BOOL bPixelCoords = TRUE ) const;
    ULONG               GetRadius( BOOL bPixelCoords = TRUE ) const;

    // liefert das BoundRect des Kreis-Objektes in 1/100mm
    virtual Rectangle   GetBoundRect() const;

    void                Scale( const Fraction& rFractX, const Fraction& rFracY );

    using IMapObject::IsEqual;
    BOOL                IsEqual( const IMapCircleObject& rEqObj );
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
