/*************************************************************************
 *
 *  $RCSfile: def3d.hxx,v $
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

#ifndef _SVX_DEF3D_HXX
#define _SVX_DEF3D_HXX

class Vector3D;

#ifndef _INC_MATH
#include <math.h>
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

const double fPiDiv180 = 0.01745329251994;
const double EPSILON = 1e-06;

#define DEG2RAD(fAngle) (fPiDiv180 * (fAngle))

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ 3D-Hilfsfunktionen +++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

FASTBOOL Do3DEdgesIntersect(const Vector3D& rV1a, const Vector3D& rV1b,
                            const Vector3D& rV2a, const Vector3D& rV2b);

enum E3dDragDetail { E3DDETAIL_DEFAULT = 0,
                     E3DDETAIL_ONEBOX,
                     E3DDETAIL_ALLBOXES,
                     E3DDETAIL_ALLLINES
};

enum E3dDragConstraint { E3DDRAG_CONSTR_X   = 0x0001,
                         E3DDRAG_CONSTR_Y   = 0x0002,
                         E3DDRAG_CONSTR_Z   = 0x0004,
                         E3DDRAG_CONSTR_XY  = 0x0003,
                         E3DDRAG_CONSTR_XZ  = 0x0005,
                         E3DDRAG_CONSTR_YZ  = 0x0006,
                         E3DDRAG_CONSTR_XYZ = 0x0007
};

}//end of namespace binfilter
#endif
