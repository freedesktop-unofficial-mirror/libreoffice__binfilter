/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: volume3d.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:23:56 $
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

#ifndef _VOLUME3D_HXX
#define _VOLUME3D_HXX

#ifndef _B3D_VOLUM_HXX
#include <bf_goodies/b3dvolum.hxx>
#endif
namespace binfilter {
class Matrix4D;

//************************************************************
//   Vorausdeklarationen
//************************************************************

class Polygon3D;
class XPolygon;
class XPolyPolygon;
class Vol3DPointIterator;

/*************************************************************************
|*
|* dreidimensionales Volumen, symmetrisch zu den Koordinatenachsen
|*
\************************************************************************/

class Volume3D : public B3dVolume
{
public:
    Volume3D(const Vector3D& rPos, const Vector3D& r3DSize, BOOL bPosIsCenter = TRUE);
    Volume3D();

    // Zuweisungsoperator, um B3dVolumes an Volume3D zuweisen zu koennen
    void operator=(const B3dVolume& rVol)
    {
        aMinVec = rVol.MinVec();
        aMaxVec = rVol.MaxVec();
    }
    Volume3D    GetTransformVolume(const Matrix4D& rTfMatrix) const;
};

/*************************************************************************
|*
|* Iterator, der die Eckpunkte eines Volumens berechnet; wenn eine Matrix
|* uebergeben wird, werden die Punkte damit transformiert
|*
\************************************************************************/

class Vol3DPointIterator
{
protected:
    const Volume3D&             rVolume;
    const Matrix4D*             pTransform;
    Vector3D                    a3DExtent;
    UINT16                      nIndex;

public:
    Vol3DPointIterator(const Volume3D& rVol, const Matrix4D* pTf = NULL);

    BOOL Next(Vector3D& rVec);
    void Reset() { nIndex = 0; }
};

}//end of namespace binfilter
#endif          // _VOLUME3D_HXX
