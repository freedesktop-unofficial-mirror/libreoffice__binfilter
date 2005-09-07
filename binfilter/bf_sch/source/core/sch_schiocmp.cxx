/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_schiocmp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 21:59:58 $
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

#ifndef _DEBUG_HXX
#include <tools/debug.hxx>
#endif
#include "schiocmp.hxx"
namespace binfilter {


//  CTOR: writes/reads version number

/*N*/ SchIOCompat::SchIOCompat( SvStream& rNewStream, USHORT nNewMode,
/*N*/                         UINT16 nVer ) :
/*N*/       SdrDownCompat( rNewStream, nNewMode, TRUE ),
/*N*/       nVersion( nVer )
/*N*/ {
/*N*/   switch( nNewMode )
/*N*/   {
/*N*/       case STREAM_WRITE:
/*N*/           DBG_ASSERT( nVer != SCHIOCOMPAT_VERSIONDONTKNOW,
/*N*/                       "Requesting writing of unknown File Version" );
/*N*/           rNewStream << nVersion;
/*N*/           break;
/*N*/
/*N*/       case STREAM_READ:
/*N*/           DBG_ASSERT( nVer == SCHIOCOMPAT_VERSIONDONTKNOW,
/*N*/                       "Requesting reading of unknown File Version" );
/*N*/           rNewStream >> nVersion;
/*N*/           break;
/*N*/   }
/*N*/ }



}
