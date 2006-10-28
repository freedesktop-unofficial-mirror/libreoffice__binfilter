/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: polysc3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:53:52 $
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

#ifndef _E3D_POLYSC3D_HXX
#define _E3D_POLYSC3D_HXX

#ifndef _SVDPAGE_HXX
#include <bf_svx/svdpage.hxx>
#endif

#ifndef _E3D_SCENE3D_HXX
#include <bf_svx/scene3d.hxx>
#endif

#ifndef _B3D_HMATRIX_HXX
#include <goodies/hmatrix.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* 3D-Szene mit Darstellung durch 2D-Polygone
|*
\************************************************************************/

class E3dPolyScene : public E3dScene
{
public:
    TYPEINFO();
    E3dPolyScene();
    E3dPolyScene(E3dDefaultAttributes& rDefault);

    virtual UINT16 GetObjIdentifier() const;

    // Zeichenmethode
    virtual FASTBOOL Paint(ExtOutputDevice&, const SdrPaintInfoRec&) const;

    // Die Kontur fuer TextToContour


protected:



};

}//end of namespace binfilter
#endif          // _E3D_POLYSC3D_HXX
