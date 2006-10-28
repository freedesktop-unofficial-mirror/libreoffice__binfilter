/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: e3dcmpt.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:28:49 $
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

#ifndef _E3D_E3DIOCMPT_HXX
#define _E3D_E3DIOCMPT_HXX


#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif
class SvStream;
namespace binfilter {


#define E3DIOCOMPAT_VERSIONDONTKNOW (UINT16) 0xffff

class E3dIOCompat : public SdrDownCompat
{
private:
    UINT16  nVersion;

public:
            // nNewMode: STREAM_READ oder STREAM_WRITE
            // nVer:     nur beim Schreiben angeben
            E3dIOCompat(SvStream& rNewStream, USHORT nNewMode,
                        UINT16 nVer = E3DIOCOMPAT_VERSIONDONTKNOW);
            ~E3dIOCompat() {};

    UINT16  GetVersion() const { return nVersion; }
};

}//end of namespace binfilter
#endif      // _E3D_E3DIOCMPT_HXX


