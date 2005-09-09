/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: polygn3d.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:11:38 $
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

#ifndef _E3D_POLYGON3D_HXX
#define _E3D_POLYGON3D_HXX

#ifndef _E3D_OBJ3D_HXX
#include <bf_svx/obj3d.hxx>
#endif

#ifndef _POLY3D_HXX
#include <bf_svx/poly3d.hxx>
#endif
namespace binfilter {

class E3dPolygonObj : public E3dCompoundObject
{
private:
    // Parameter
    PolyPolygon3D   aPolyPoly3D;
    PolyPolygon3D   aPolyNormals3D;
    PolyPolygon3D   aPolyTexture3D;
    BOOL            bLineOnly;

    void CreateDefaultNormals();
    void CreateDefaultTexture();

public:
    void SetPolyPolygon3D(const PolyPolygon3D& rNewPolyPoly3D);
    void SetPolyNormals3D(const PolyPolygon3D& rNewPolyPoly3D);
    void SetPolyTexture3D(const PolyPolygon3D& rNewPolyPoly3D);

    TYPEINFO();

    E3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        BOOL bLinOnly=FALSE);
    E3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D, BOOL bLinOnly=FALSE);
    E3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D, const PolyPolygon3D& rNormal3D, BOOL bLinOnly=FALSE);
    E3dPolygonObj(E3dDefaultAttributes& rDefault, const Vector3D& rP1,
        const Vector3D& rP2, BOOL bLinOnly=TRUE);

    E3dPolygonObj();
    virtual ~E3dPolygonObj();

    const PolyPolygon3D& GetPolyPolygon3D() const { return aPolyPoly3D; }
    const PolyPolygon3D& GetPolyNormals3D() const { return aPolyNormals3D; }
    const PolyPolygon3D& GetPolyTexture3D() const { return aPolyTexture3D; }

    virtual UINT16 GetObjIdentifier() const;
//STRIP001  virtual void CreateWireframe(Polygon3D& rWirePoly, const Matrix4D* pTf = NULL,
//STRIP001      E3dDragDetail eDetail = E3DDETAIL_DEFAULT);
//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

//STRIP001  virtual void operator=(const SdrObject&);
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // Geometrieerzeugung
//STRIP001  virtual void CreateGeometry();

    // Give out simple line geometry
//STRIP001  virtual void GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const;

    // LineOnly?
    BOOL GetLineOnly() { return bLineOnly; }
    void SetLineOnly(BOOL bNew);
};

}//end of namespace binfilter
#endif          // _E3D_POLYGON3D_HXX
