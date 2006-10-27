/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_deflt3d.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:47:54 $
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

#define ITEMID_COLOR            SID_ATTR_3D_LIGHTCOLOR


#ifndef _E3D_CUBE3D_HXX
#include "cube3d.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif


namespace binfilter {

/*************************************************************************
|*
|* Klasse zum verwalten der 3D-Default Attribute
|*
\************************************************************************/

// Konstruktor
/*N*/ E3dDefaultAttributes::E3dDefaultAttributes()
/*N*/ {
/*N*/   Reset();
/*N*/ }

/*N*/ void E3dDefaultAttributes::Reset()
/*N*/ {
/*N*/   // Compound-Objekt
/*N*/ //    aDefaultFrontMaterial;
/*N*/ //    aDefaultBackMaterial;
/*N*/   bDefaultCreateNormals = TRUE;
/*N*/   bDefaultCreateTexture = TRUE;
/*N*/   bDefaultUseDifferentBackMaterial = FALSE;
/*N*/
/*N*/   // Cube-Objekt
/*N*/   aDefaultCubePos = Vector3D(-500.0, -500.0, -500.0);
/*N*/   aDefaultCubeSize = Vector3D(1000.0, 1000.0, 1000.0);
/*N*/   nDefaultCubeSideFlags = CUBE_FULL;
/*N*/   bDefaultCubePosIsCenter = FALSE;
/*N*/
/*N*/   // Sphere-Objekt
/*N*/   aDefaultSphereCenter = Vector3D(0.0, 0.0, 0.0);
/*N*/   aDefaultSphereSize = Vector3D(1000.0, 1000.0, 1000.0);
/*N*/
/*N*/   // Lathe-Objekt
/*N*/   nDefaultLatheEndAngle = 3600;
/*N*/   fDefaultLatheScale = 1.0;
/*N*/   bDefaultLatheSmoothed = TRUE;
/*N*/   bDefaultLatheSmoothFrontBack = FALSE;
/*N*/   bDefaultLatheCharacterMode = FALSE;
/*N*/   bDefaultLatheCloseFront = TRUE;
/*N*/   bDefaultLatheCloseBack = TRUE;
/*N*/
/*N*/   // Extrude-Objekt
/*N*/   fDefaultExtrudeScale = 1.0;
/*N*/   bDefaultExtrudeSmoothed = TRUE;
/*N*/   bDefaultExtrudeSmoothFrontBack = FALSE;
/*N*/   bDefaultExtrudeCharacterMode = FALSE;
/*N*/   bDefaultExtrudeCloseFront = TRUE;
/*N*/   bDefaultExtrudeCloseBack = TRUE;
/*N*/
/*N*/   // Scene-Objekt
/*N*/ //    aDefaultLightGroup;
/*N*/   bDefaultDither = TRUE;
/*N*/ }
}
