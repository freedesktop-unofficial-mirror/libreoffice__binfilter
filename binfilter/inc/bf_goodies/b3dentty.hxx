/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: b3dentty.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:17:29 $
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
#define _B3D_B3DENTITY_HXX

#ifndef _B3D_B3DCOLOR_HXX
#include "b3dcolor.hxx"
#endif

#ifndef _B3D_POINT4D_HXX
#include "point4d.hxx"
#endif

#ifndef _B3D_BUCKET_HXX
#include "bucket.hxx"
#endif

namespace binfilter {

/*************************************************************************
|*
|* Merkt sich einen Punkt plus Normale plus Texturkoordinate
|* (in Zukunft noch weitere Attribute, bsp. Farbe, Kante, Linienmodus
|*
\************************************************************************/

//class Base3DCommon;
//class Base3D;
class B3dTransformationSet;
class Matrix4D;

class B3dEntity
{
private:
    // Data defining this point, it's normal and texture coordinates
    Point4D                 aPoint;
    Vector3D                aNormal;
    Vector3D                aPlaneNormal;
    Vector3D                aTexCoor;
    B3dColor                aColor;

    // Ist die diesem Punkt folgende Kante sichtbar ?
    UINT8                   bEdgeFlag;

    // BOOLEAN flags
    // Gueltigkeit der geometrischen Daten
    unsigned                bValid          : 1;

    // Wird eine Normale verwendet ?
    unsigned                bNormalUsed     : 1;

    // Wird eine Texturkoordinate verwendet ?
    unsigned                bTexCoorUsed    : 1;

    // Sind die geometrischen Daten schon in DeviceKoordinaten
    // umgerechnet ?
    unsigned                bDeviceCoor     : 1;

public:
    B3dEntity() { Reset(); }

    BOOL IsValid() { return bValid; }
    void SetValid(BOOL bNew=TRUE) { bValid = bNew; }

    BOOL IsNormalUsed() { return bNormalUsed; }
    void SetNormalUsed(BOOL bNew=TRUE) { bNormalUsed = bNew; }

    BOOL IsTexCoorUsed() { return bTexCoorUsed; }
    void SetTexCoorUsed(BOOL bNew=TRUE) { bTexCoorUsed = bNew; }

    BOOL IsDeviceCoor() { return bDeviceCoor; }
    void SetDeviceCoor(BOOL bNew=TRUE) { bDeviceCoor = bNew; }

    BOOL IsEdgeVisible() { return bEdgeFlag; }
    void SetEdgeVisible(BOOL bNew=TRUE) { bEdgeFlag = bNew; }

    Point4D& Point() { return aPoint; }
    Vector3D& Normal() { return aNormal; }
    Vector3D& PlaneNormal() { return aPlaneNormal; }
    Vector3D& TexCoor() { return aTexCoor; }
    B3dColor& Color() { return aColor; }
    UINT8& EdgeFlag() { return bEdgeFlag; }

    double GetX() { return aPoint.X(); }
    void SetX(double fNew) { aPoint.X() = fNew; }

    double GetY() { return aPoint.Y(); }
    void SetY(double fNew) { aPoint.Y() = fNew; }

    double GetZ() { return aPoint.Z(); }
    void SetZ(double fNew) { aPoint.Z() = fNew; }

    void Reset();

    void Copy(B3dEntity& rEnt);
    void ToDeviceCoor(B3dTransformationSet* pSet)
        { if(!IsDeviceCoor()) ImplToDeviceCoor(pSet); }
    void To3DCoor(B3dTransformationSet* pSet)
        { if(IsDeviceCoor()) ImplTo3DCoor(pSet); }

    void ForceEqualBase(B3dTransformationSet* pSet, B3dEntity& rOld);
    void ForceEqualBase(B3dTransformationSet* pSet, B3dEntity& rOld1,
        B3dEntity& rOld2);
    void CalcInBetween(B3dEntity& rOld1,
        B3dEntity& rOld2, double t);
    void CalcMiddle(B3dEntity& rOld1,
        B3dEntity& rOld2);
    void CalcMiddle(B3dEntity& rOld1,
        B3dEntity& rOld2, B3dEntity& rOld3);

    // Eine beliebige Transformation auf die Geometrie anwenden
    void Transform(const Matrix4D&);

protected:
    void ImplToDeviceCoor(B3dTransformationSet* pSet);
    void ImplTo3DCoor(B3dTransformationSet* pSet);
};

/*************************************************************************
|*
|* Bucket fuer geometrische Daten
|*
\************************************************************************/

BASE3D_DECL_BUCKET(B3dEntity, Bucket)

}//end of namespace binfilter

#endif          // _B3D_B3DENTITY_HXX
