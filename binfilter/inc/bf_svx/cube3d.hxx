/*************************************************************************
 *
 *  $RCSfile: cube3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:35 $
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

#ifndef _E3D_CUBE3D_HXX
#define _E3D_CUBE3D_HXX

#ifndef _E3D_OBJ3D_HXX
#include <bf_svx/obj3d.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|*                                                              |
|* 3D-Quader erzeugen; aPos: Zentrum oder links, unten, hinten  |__
|*                           (abhaengig von bPosIsCenter)      /
|* Mit nSideFlags kann angegeben werden, ob nur ein Teil der
|* Quaderflaechen erzeugt werden kann; die entsprechenden Bits
|* sind in dem enum definiert. Das Flag bDblSided legt fest,
|* ob die erzeugten Flaechen doppelseitig sind (nur sinnvoll,
|* wenn nicht alle Flaechen erzeugt wurden).
|*
\************************************************************************/

enum { CUBE_BOTTOM = 0x0001, CUBE_BACK = 0x0002, CUBE_LEFT = 0x0004,
       CUBE_TOP = 0x0008, CUBE_RIGHT = 0x0010, CUBE_FRONT = 0x0020,
       CUBE_FULL = 0x003F, CUBE_OPEN_TB = 0x0036, CUBE_OPEN_LR = 0x002B,
       CUBE_OPEN_FB = 0x001D };

class E3dCubeObj : public E3dCompoundObject
{
private:
    // Zur Geometrieerzeugung eines Cubes notwendige
    // Parameter
    Vector3D            aCubePos;
    Vector3D            aCubeSize;
    UINT16              nSideFlags;

    // BOOLeans
    unsigned            bPosIsCenter            : 1;

protected:
    void SetDefaultAttributes(E3dDefaultAttributes& rDefault);

public:
    TYPEINFO();
    E3dCubeObj(E3dDefaultAttributes& rDefault, Vector3D aPos, const Vector3D& r3DSize);
    E3dCubeObj();

    virtual UINT16 GetObjIdentifier() const;
    virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

//STRIP001  virtual void operator=(const SdrObject&);
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // Geometrieerzeugung
    virtual void CreateGeometry();

    // Give out simple line geometry
//STRIP001  virtual void GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const;

    // Lokale Parameter setzen mit Geometrieneuerzeugung
    void SetCubePos(const Vector3D& rNew);
    const Vector3D& GetCubePos() { return aCubePos; }

    void SetCubeSize(const Vector3D& rNew);
    const Vector3D& GetCubeSize() { return aCubeSize; }

    void SetPosIsCenter(BOOL bNew);
    BOOL GetPosIsCenter() { return (BOOL)bPosIsCenter; }

//STRIP001  void SetSideFlags(UINT16 nNew);
    UINT16 GetSideFlags() { return nSideFlags; }

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".
//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;
};

}//end of namespace binfilter
#endif          // _E3D_CUBE3D_HXX
