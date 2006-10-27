/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_misc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 19:05:15 $
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

#pragma hdrstop

#include "sfxtypes.hxx"
namespace binfilter {

//--------------------------------------------------------------------

#if defined(DBG_UTIL) && ( defined(WNT) || defined(OS2) )
unsigned SfxStack::nLevel = 0;
#endif

//--------------------------------------------------------------------


/*N*/ String SfxStringEncode( const String &rSource, const char *pKey  )
/*N*/ {
/*N*/   String aRet;
/*N*/   String aCoded(rSource);
/*ASMUSS
    // codieren
    USHORT nCode = 0;
    for ( USHORT n1 = 0; n1 < aCoded.Len(); ++n1 )
    {
        aCoded[n1] ^= pKey[nCode];
        if ( !pKey[++nCode] )
            nCode = 0;
    }

    // als reine Buchstabenfolge darstellen
    for ( USHORT n2 = 0; n2 < aCoded.Len(); ++n2 )
    {
        aRet += (char) ( 'a' + ((aCoded[n2] & 0xF0) >> 4) );
        aRet += (char) ( 'a' +  (aCoded[n2] & 0xF) );
    }
*/
/*N*/   return aRet;
/*N*/ }


}
