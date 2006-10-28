/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ifaceids.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:39:06 $
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
#ifndef _SVX_IFACEIDS_HXX
#define _SVX_IFACEIDS_HXX

// -----------------------------------------------------------------------

namespace binfilter {

#if SUPD<=342

#define SVX_INTERFACE_BASIDE_DOCSH      (SFX_INTERFACE_LIB+ 0)
#define SVX_INTERFACE_BASIDE_VIEWSH     (SFX_INTERFACE_LIB+ 1)

#define SVX_INTERFACE_SCH_START         (SFX_INTERFACE_LIB+ 2)
#define SVX_INTERFACE_SCH_END           (SFX_INTERFACE_LIB+ 9)

#define SVX_INTERFACE_SIM_START         (SFX_INTERFACE_LIB+10)
#define SVX_INTERFACE_SIM_END           (SFX_INTERFACE_LIB+15)

#define SVX_INTERFACE_SBA_START         (SFX_INTERFACE_LIB+16)
#define SVX_INTERFACE_SBA_END           (SFX_INTERFACE_LIB+47)

#define SVX_INTERFACE_SMA_START         (SFX_INTERFACE_LIB+64)
#define SVX_INTERFACE_SMA_END           (SFX_INTERFACE_LIB+67)

#else

#define SVX_INTERFACE_BASIDE_DOCSH      (SFX_INTERFACE_IDE_START+ 0)
#define SVX_INTERFACE_BASIDE_VIEWSH     (SFX_INTERFACE_IDE_START+ 1)

#define HID_INTERFACE_BASIDE_VIEWSH     SVX_INTERFACE_BASIDE_VIEWSH

#define SVX_INTERFACE_FORM_SH           (SFX_INTERFACE_IDE_END+ 1)

#endif

}//end of namespace binfilter
#endif

