/*************************************************************************
 *
 *  $RCSfile: dlight3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:37 $
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

#ifndef _E3D_DLIGHT3D_HXX
#define _E3D_DLIGHT3D_HXX

#ifndef _E3D_LIGHT3D_HXX
#include <bf_svx/light3d.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* gerichtete Lichtquelle, aDirection zeigt ZUR Lichtquelle (also den
|* Lichtstrahlen entgegensetzt); die Position (geerbt von E3dLight) hat
|* auf die Lichtberechnung keinen Einfluss, sondern dient nur der
|* Anordnung in der Szene (fuer evtl. spaetere interaktive Bearbeitung)
|*
\************************************************************************/

class E3dDistantLight : public E3dLight
{
 protected:
    Vector3D aDirection;

    virtual void CreateLightObj();

 public:
    TYPEINFO();
    E3dDistantLight(const Vector3D& rPos,
                    const Vector3D& rDirection,
                    const Color&    rColor,
                    double          fLightIntensity = 1.0);

    E3dDistantLight() :
        aDirection(Vector3D(0, 1, 0))
    {
    }

    virtual ~E3dDistantLight();

    virtual UINT16 GetObjIdentifier() const;

    virtual FASTBOOL CalcLighting(Color& rNewColor,
                                  const Vector3D& rPnt,
                                  const Vector3D& rPntNormal,
                                  const Color& rPntColor);

    const Vector3D& GetDirection() const { return aDirection; }
    void SetDirection(const Vector3D& rNewDir);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

//STRIP001  virtual void operator=(const SdrObject&);
};

}//end of namespace binfilter
#endif          // _E3D_DLIGHT3D_HXX
