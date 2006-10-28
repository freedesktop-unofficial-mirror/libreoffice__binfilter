/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dlight3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:27:53 $
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

};

}//end of namespace binfilter
#endif          // _E3D_DLIGHT3D_HXX
