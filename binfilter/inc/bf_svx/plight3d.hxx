/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: plight3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:52:45 $
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

#ifndef _E3D_PLIGHT3D_HXX
#define _E3D_PLIGHT3D_HXX

#ifndef _E3D_LIGHT3D_HXX
#include "light3d.hxx"
#endif
namespace binfilter {

/*************************************************************************
|*
|* Punktlichtquelle, die gleichmaessig in alle Richtungen strahlt, und
|* zwar von der von E3dLight geerbten Position aus
|*
\************************************************************************/

class E3dPointLight : public E3dLight
{
 protected:
    virtual void CreateLightObj();

 public:
    TYPEINFO();
    E3dPointLight(const Vector3D& rPos,
                  const Color&    rColor,
                  double          fLightIntensity = 1.0);

    E3dPointLight()
    {
    }

    virtual ~E3dPointLight();


    virtual FASTBOOL CalcLighting(Color& rNewColor,
                                  const Vector3D& rPnt,
                                  const Vector3D& rPntNormal,
                                  const Color& rPntColor);
};



}//end of namespace binfilter
#endif          // _E3D_PLIGHT3D_HXX
