/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: linetype.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:13:28 $
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
#ifndef _LINETYPE_HXX
#define _LINETYPE_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

/*--------------------------------------------------------------------
     Beschreibung: Ein Linientyp wird durch die 3 Werte festgelegt
 --------------------------------------------------------------------*/

enum SwLineWidth
{
    LIN_0   = 0,
    LIN_1   = 1,
    LIN_2   = 20,
    LIN_3   = 50,
    LIN_4   = 80,
    LIN_5   = 100
};

struct SwLineType
{
    USHORT nIn;
    USHORT nOut;
    USHORT nDist;
};

USHORT             GetLineTypeCount();
const SwLineType&  GetLineType(USHORT nIdx);

} //namespace binfilter
#endif // _LINETYPE_HXX
