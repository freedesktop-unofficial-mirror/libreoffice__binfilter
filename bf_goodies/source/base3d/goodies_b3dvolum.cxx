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

#include "b3dvolum.hxx"

namespace binfilter {
/*************************************************************************
|*
|* Konstruktor 1:                                               |
|* rPos: Zentrum oder minimale Koordinate links, unten, hinten  |__
|*       (abhaengig von bPosIsCenter)                          /
|*
\************************************************************************/

B3dVolume::B3dVolume(const Vector3D& rPos, const Vector3D& r3DSize,
                    BOOL bPosIsCenter)
{
    if ( bPosIsCenter ) aMinVec = rPos - r3DSize / 2;
    else                aMinVec = rPos;

    aMaxVec = aMinVec + r3DSize;
}

/*************************************************************************
|*
|* Konstruktor 2 - leeres Volumen, Werte als ungueltig markieren
|*
\************************************************************************/

B3dVolume::B3dVolume() :
    aMinVec( DBL_MAX, DBL_MAX, DBL_MAX),
    aMaxVec(-DBL_MAX,-DBL_MAX,-DBL_MAX)
{
}

/*************************************************************************
|*
|* Volumen zuruecksetzen
|*
\************************************************************************/

void B3dVolume::Reset()
{
    aMinVec = Vector3D( DBL_MAX, DBL_MAX, DBL_MAX);
    aMaxVec = Vector3D(-DBL_MAX,-DBL_MAX,-DBL_MAX);
}

/*************************************************************************
|*
|* testen, ob Volumen vollstaendig gueltige Werte enthaelt
|*
\************************************************************************/

BOOL B3dVolume::IsValid() const
{
    return ( aMinVec.X() !=  DBL_MAX && aMinVec.Y() !=  DBL_MAX &&
             aMinVec.Z() !=  DBL_MAX && aMaxVec.X() != -DBL_MAX &&
             aMaxVec.Y() != -DBL_MAX && aMaxVec.Z() != -DBL_MAX );
}

/*************************************************************************
|*
|* einen 3D-Vektor in das Volumen einschliessen
|*
\************************************************************************/

B3dVolume& B3dVolume::Union(const B3dVolume& rVol2)
{
    if ( rVol2.IsValid() )
    {
        aMinVec.Min(rVol2.aMinVec);
        aMaxVec.Max(rVol2.aMaxVec);
    }
    return *this;
}

/*************************************************************************
|*
|* Vereinigung mit Vector3D
|*
\************************************************************************/

B3dVolume& B3dVolume::Union(const Vector3D& rVec)
{
    aMinVec.Min(rVec);
    aMaxVec.Max(rVec);
    return *this;
}

/*************************************************************************
|*
|* Stream-In-Operator fuer B3dVolume
|*
\************************************************************************/

SvStream& operator>>(SvStream& rIStream, B3dVolume& rB3dVolume)
{
    rIStream >> rB3dVolume.aMinVec;
    rIStream >> rB3dVolume.aMaxVec;

    return rIStream;
}

/*************************************************************************
|*
|* Stream-Out-Operator fuer B3dVolume
|*
\************************************************************************/

SvStream& operator<<(SvStream& rOStream, const B3dVolume& rB3dVolume)
{
    rOStream << rB3dVolume.aMinVec;
    rOStream << rB3dVolume.aMaxVec;

    return rOStream;
}


}//end of namespace binfilter

// eof

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
