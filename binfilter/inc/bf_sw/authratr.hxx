/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: authratr.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:34:45 $
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

#ifndef _AUTHRATR_HXX
#define _AUTHRATR_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

namespace binfilter {

#define COL_NONE        TRGB_COLORDATA( 0x80, 0xFF, 0xFF, 0xFF )

class AuthorCharAttr
{
public:
    USHORT  nItemId;
    USHORT  nAttr;
    ULONG   nColor;

    AuthorCharAttr();

    inline BOOL operator == ( const AuthorCharAttr& rAttr ) const
    {
        return  nItemId == rAttr.nItemId && nAttr == rAttr.nAttr &&
                nColor == rAttr.nColor;
    }
};


} //namespace binfilter
#endif
