/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: binding.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:41:22 $
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
#ifndef _BINDING_HXX
#define _BINDING_HXX

#ifndef __RSC

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

namespace binfilter {
typedef ULONG SvBindStatus;

typedef ULONG SvStatusCallbackType;
#define SVBSCF_FIRSTDATANOTIFICATION          0x01
#define SVBSCF_LASTDATANOTIFICATION           0x02
#define SVBSCF_INTERMEDIATEDATANOTIFICATION   0x03
#define SVBSCF_RELOADAVAILABLENOTIFICATION    0x04
#define SVBSCF_NEWPARTAVAILABLENOTIFICATION   0x08

typedef ULONG SvBindMode;
#define SVBIND_ASYNC             0x01
#define SVBIND_ASYNCSTORAGE      0x02
#define SVBIND_NEWESTVERSION     0x04
#define SVBIND_SUCCESSONERRORDOC 0x08

enum SvBindAction
{
    BINDACTION_GET    = 0,
    BINDACTION_POST   = 0x1,
    BINDACTION_PUT    = 0x2,
    BINDACTION_CUSTOM = 0x3
};

}

#endif /* __RSC */

#endif /* _BINDING_HXX */
