/*************************************************************************
 *
 *  $RCSfile: volume3d.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:45 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _VOLUME3D_HXX
#define _VOLUME3D_HXX

#ifndef _B3D_VOLUM_HXX
#include <goodies/b3dvolum.hxx>
#endif

//************************************************************
//   Vorausdeklarationen
//************************************************************

class Polygon3D;
class XPolygon;
class XPolyPolygon;
class Matrix4D;
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
//STRIP001  void CreateWireframe(Polygon3D& rPoly3D, const Matrix4D* pTf = NULL) const;
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

#endif          // _VOLUME3D_HXX
