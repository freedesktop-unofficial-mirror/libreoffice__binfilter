/*************************************************************************
 *
 *  $RCSfile: glob.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:27 $
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

#ifndef _SCH_GLOB_HXX
#define _SCH_GLOB_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

#define DIA_SLOW    0
#define DIA_MEDIUM  1
#define DIA_FAST    2


#define SCH_IF_APP              SFX_INTERFACE_LIB + 2
#define SCH_IF_CHARTVIEWSHELL   SFX_INTERFACE_LIB + 3
#define SCH_IF_DOCSHELL         SFX_INTERFACE_LIB + 4
#define SCH_IF_STANDARDOBJBAR   SFX_INTERFACE_LIB + 5

#define SCH_IF_SCHAPP SFX_INTERFACE_SCH_START + 0

// Inventor-Ids fuer StarChart

const UINT32 SchInventor = UINT32('S')*0x00000001+
                           UINT32('C')*0x00000100+
                           UINT32('H')*0x00010000+
                           UINT32('U')*0x01000000;

// Object-Ids fuer StarChart

const UINT16 SCH_OBJGROUP_ID        = 1;
const UINT16 SCH_OBJECTID_ID        = 2;
const UINT16 SCH_OBJECTADJUST_ID    = 3;
const UINT16 SCH_DATAROW_ID             = 4;
const UINT16 SCH_DATAPOINT_ID       = 5;
const UINT16 SCH_LIGHTFACTOR_ID     = 6;
const UINT16 SCH_AXIS_ID                = 7;

} //namespace binfilter
#endif // _SCH_GLOB_HXX


