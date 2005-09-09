/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xiocomp.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:34:28 $
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


#ifndef _XIOCOMP_HXX
#define _XIOCOMP_HXX

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif
class SvStream;
namespace binfilter {

// -------------------
// class XIOCompat
// -------------------

#define XIOCOMPAT_VERSIONDONTKNOW (UINT16)0xffff

class XIOCompat : public SdrDownCompat
{
private:
    UINT16 nVersion;

public:
                // nNewMode: STREAM_READ oder STREAM_WRITE
                // nVer:     nur beim Schreiben angeben
            XIOCompat( SvStream& rNewStream, USHORT nNewMode,
                       UINT16 nVer = XIOCOMPAT_VERSIONDONTKNOW );
            ~XIOCompat() {};
    UINT16  GetVersion() const { return nVersion; }
};



}//end of namespace binfilter
#endif // _XIOCOMP_HXX
