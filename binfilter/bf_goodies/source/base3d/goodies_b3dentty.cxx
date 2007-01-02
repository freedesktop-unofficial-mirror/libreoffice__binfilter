/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: goodies_b3dentty.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 16:47:59 $
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

#ifndef _B3D_B3DENTITY_HXX
#include "b3dentty.hxx"
#endif

//#ifndef _B3D_B3DCOMMN_HXX
//#include "b3dcommn.hxx"
//#endif

#ifndef _B3D_B3DTRANS_HXX
#include "b3dtrans.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

namespace binfilter {
/*************************************************************************
|*
|* Flags auf Ausgangsposition
|*
\************************************************************************/

void B3dEntity::Reset()
{
    bValid = bNormalUsed = bTexCoorUsed = bDeviceCoor = FALSE;
    bEdgeFlag = TRUE;
}

/*************************************************************************
|*
|* Neuen Punkt an der stelle t des parametrisierten Vektors rOld1, rOld2
|* berechnen und fuellen
|*
\************************************************************************/

void B3dEntity::CalcInBetween(B3dEntity& rOld1, B3dEntity& rOld2, double t)
{
    // DeviceCoor der ersten Quelle benutzen, die Basis sollte
    // vorher abgeglichen sein
    SetDeviceCoor(rOld1.IsDeviceCoor());

    // Punktkoordinaten berechnen
    aPoint.CalcInBetween(rOld1.Point(), rOld2.Point(), t);
    SetValid();

    // PlaneNormal Koordinaten berechnen
    rOld1.PlaneNormal().Normalize();
    rOld2.PlaneNormal().Normalize();
    aPlaneNormal.CalcInBetween(rOld1.PlaneNormal(), rOld2.PlaneNormal(), t);
    aPlaneNormal.Normalize();

    // Vektor berechnen
    if(rOld1.IsNormalUsed() && rOld2.IsNormalUsed())
    {
        rOld1.Normal().Normalize();
        rOld2.Normal().Normalize();
        aNormal.CalcInBetween(rOld1.Normal(), rOld2.Normal(), t);
        aNormal.Normalize();
        SetNormalUsed();
    }

    // Texturkoordinaten berechnen
    if(rOld1.IsTexCoorUsed() && rOld2.IsTexCoorUsed())
    {
        aTexCoor.CalcInBetween(rOld1.TexCoor(), rOld2.TexCoor(), t);
        SetTexCoorUsed();
    }

    // EdgeVisible berechnen
    SetEdgeVisible(rOld1.IsEdgeVisible());

    // Farbe berechnen
    aColor.CalcInBetween(rOld1.Color(), rOld2.Color(), t);
}

/*************************************************************************
|*
|* Neuen Punkt in der Mitte des parametrisierten Vektors rOld1, rOld2
|* berechnen und fuellen
|*
\************************************************************************/

void B3dEntity::CalcMiddle(B3dEntity& rOld1, B3dEntity& rOld2)
{
    // DeviceCoor der ersten Quelle benutzen, die Basis sollte
    // vorher abgeglichen sein
    SetDeviceCoor(rOld1.IsDeviceCoor());

    // Punktkoordinaten berechnen
    aPoint.CalcMiddle(rOld1.Point(), rOld2.Point());
    SetValid();

    // PlaneNormal Koordinaten berechnen
    rOld1.PlaneNormal().Normalize();
    rOld2.PlaneNormal().Normalize();
    aPlaneNormal.CalcMiddle(rOld1.PlaneNormal(), rOld2.PlaneNormal());
    aPlaneNormal.Normalize();

    // Vektor berechnen
    if(rOld1.IsNormalUsed() && rOld2.IsNormalUsed())
    {
        rOld1.Normal().Normalize();
        rOld2.Normal().Normalize();
        aNormal.CalcMiddle(rOld1.Normal(), rOld2.Normal());
        aNormal.Normalize();
        SetNormalUsed();
    }

    // Texturkoordinaten berechnen
    if(rOld1.IsTexCoorUsed() && rOld2.IsTexCoorUsed())
    {
        aTexCoor.CalcMiddle(rOld1.TexCoor(), rOld2.TexCoor());
        SetTexCoorUsed();
    }

    // EdgeVisible berechnen
    SetEdgeVisible(rOld1.IsEdgeVisible());

    // Farbe berechnen
    aColor.CalcMiddle(rOld1.Color(), rOld2.Color());
}

/*************************************************************************
|*
|* Eine beliebige Transformation auf die Geometrie anwenden
|*
\************************************************************************/

void B3dEntity::Transform(const Matrix4D& rMat)
{
    aPoint *= rMat;
    if(bNormalUsed)
        rMat.RotateAndNormalize(aNormal);
}

/*************************************************************************
|*
|* Bucket fuer geometrische Daten
|*
\************************************************************************/

BASE3D_IMPL_BUCKET(B3dEntity, Bucket)

}//end of namespace binfilter

// eof
