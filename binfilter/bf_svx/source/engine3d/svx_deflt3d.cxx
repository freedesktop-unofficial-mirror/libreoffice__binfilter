/*************************************************************************
 *
 *  $RCSfile: svx_deflt3d.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:45 $
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

#define ITEMID_COLOR            SID_ATTR_3D_LIGHTCOLOR

#ifndef _E3D_DEFLT3D_HXX
#include "deflt3d.hxx"
#endif

#ifndef _E3D_CUBE3D_HXX
#include "cube3d.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif

#ifndef _SVX_COLRITEM_HXX
#include "colritem.hxx"
#endif

#ifndef _SVXE3DITEM_HXX
#include "e3ditem.hxx"
#endif

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
