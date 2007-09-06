/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: goodies_b3dvolum.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:29:44 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _B3D_VOLUM_HXX
#include "b3dvolum.hxx"
#endif

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
