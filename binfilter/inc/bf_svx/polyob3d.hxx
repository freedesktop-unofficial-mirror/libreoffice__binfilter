/*************************************************************************
 *
 *  $RCSfile: polyob3d.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:37 $
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

#ifndef _E3D_POLYOB3D_HXX
#define _E3D_POLYOB3D_HXX

#ifndef _E3D_OBJ3D_HXX
#include <bf_svx/obj3d.hxx>
#endif
#ifndef _POLY3D_HXX
#include <bf_svx/poly3d.hxx>
#endif

/*************************************************************************
|*
\************************************************************************/

class E3dPolyObj : public E3dObject
{
 protected:
    PolyPolygon3D   aPolyPoly3D;
    PolyPolygon3D   aPolyNormals3D;
    PolyPolygon3D   aPolyTexture3D;
    Vector3D        aNormal;

    BOOL    bDoubleSided : 1;
    BOOL    bBackSideVisible : 1;
    BOOL    bLighted : 1;
    BOOL    bOwnAttrs;
    BOOL    bOwnStyle;
    long    nObjectnumber;  // default ist -1;

    // [FG]: Zwecks schreiben des Formates der 3.1 Version
    //       Diese Funktionen werden nur von ReadData31 und WriteData31
    //       aufgerufen.
    void WriteData31(SvStream& rOut) const;
    void ReadData31(const SdrObjIOHeader& rHead, SvStream& rIn);

public:
    TYPEINFO();
    E3dPolyObj(const PolyPolygon3D& rPoly3D, FASTBOOL bDblSided = FALSE,
                                             FASTBOOL bLight = TRUE);
    E3dPolyObj(const PolyPolygon3D& rPoly3D, const PolyPolygon3D& rVector3D,
                                             FASTBOOL bDblSided = FALSE,
                                             FASTBOOL bLight = TRUE);
    E3dPolyObj(const PolyPolygon3D& rPoly3D, const PolyPolygon3D& rVector3D,
                                             const PolyPolygon3D& rNormal3D,
                                             FASTBOOL bDblSided = FALSE,
                                             FASTBOOL bLight = TRUE);
    E3dPolyObj(const Vector3D& rP1, const Vector3D& rP2);
    E3dPolyObj();
    virtual ~E3dPolyObj();

    virtual UINT16  GetObjIdentifier() const;
//STRIP001  virtual USHORT  GetPointCount () const;
    void SetPolyPolygon3D(const PolyPolygon3D& rNewPolyPoly3D);
    const PolyPolygon3D& GetPolyPolygon3D() const { return aPolyPoly3D; }

    void SetPolyNormals3D(const PolyPolygon3D& rNewPolyPoly3D);
    const PolyPolygon3D& GetPolyNormals3D() const { return aPolyNormals3D; }

    void SetPolyTexture3D(const PolyPolygon3D& rNewPolyPoly3D);
    const PolyPolygon3D& GetPolyTexture3D() const { return aPolyTexture3D; }

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".
//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

    virtual const   Rectangle& GetBoundRect() const;
//STRIP001  virtual void CreateWireframe(Polygon3D& rWirePoly,
//STRIP001      const Matrix4D* pTf = NULL,
//STRIP001      E3dDragDetail eDetail = E3DDETAIL_DEFAULT);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

//STRIP001  virtual void operator=(const SdrObject&);

//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    virtual SdrObjGeoData *NewGeoData() const;
    virtual void          SaveGeoData(SdrObjGeoData &rGeo) const;
    virtual void          RestGeoData(const SdrObjGeoData &rGeo);
    virtual void          SetPage(SdrPage *pNewPage);
    virtual void          SetModel(SdrModel *pNewModel);
    virtual SdrLayerID    GetLayer() const;
    virtual void          NbcSetLayer(SdrLayerID nLayer);
//STRIP001  virtual void          NbcSetStyleSheet(SfxStyleSheet *pNewStyleSheet,
//STRIP001                                         FASTBOOL      bDontRemoveHardAttr);
    virtual SfxStyleSheet *GetStyleSheet() const;

    BOOL OwnAttrs() const { return bOwnAttrs; }
    BOOL &OwnAttrs() { return bOwnAttrs; }
    BOOL OwnStyle() const { return bOwnStyle; }
    BOOL &OwnStyle() { return bOwnStyle; }

    BOOL DoubleSided () const { return bDoubleSided; }
    void SetDoubleSided (BOOL bNewDoubleSided) { bDoubleSided = bNewDoubleSided; }

    long  GetObjectnumber () const { return nObjectnumber; }
    void  SetObjectnumber (long value) { nObjectnumber = value; }

    const Vector3D& GetNormal() { return aNormal; }
};

#endif          // _E3D_POLYOB3D_HXX
