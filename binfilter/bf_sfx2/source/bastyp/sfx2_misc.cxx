/*************************************************************************
 *
 *  $RCSfile: sfx2_misc.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:09 $
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

#pragma hdrstop

#include "sfxtypes.hxx"

//--------------------------------------------------------------------

#if defined(DBG_UTIL) && ( defined(WNT) || defined(OS2) )
unsigned SfxStack::nLevel = 0;
#endif

//--------------------------------------------------------------------

//STRIP001 String SearchAndReplace( const String &rSource,
//STRIP001                       const String &rToReplace,
//STRIP001                       const String &rReplacement )
//STRIP001 {
//STRIP001  String aTarget( rSource );
//STRIP001  USHORT nPos = rSource.Search( rToReplace );
//STRIP001  if ( nPos != STRING_NOTFOUND )
//STRIP001  {
//STRIP001      aTarget.Erase( nPos, rToReplace.Len() );
//STRIP001      return aTarget.Insert( rReplacement, nPos );
//STRIP001  }
//STRIP001  return rSource;
//STRIP001 }
//STRIP001
//STRIP001 //--------------------------------------------------------------------

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

//STRIP001 //--------------------------------------------------------------------
//STRIP001
//STRIP001 String SfxStringDecode( const String &rSource, const char *pKey  )
//STRIP001 {
//STRIP001  // Output-Buffer aufbereiten
//STRIP001  String aRet;/*ASMUSS
//STRIP001  aRet.AllocStrBuf( rSource.Len() / 2 );
//STRIP001
//STRIP001  // Buchstabenfolge in normale Zeichen wandeln
//STRIP001  USHORT nTo = 0;
//STRIP001  for ( USHORT n1 = 0; n1 < rSource.Len(); n1 += 2)
//STRIP001      aRet[nTo++] = (unsigned char)
//STRIP001                      ( ( ( rSource[n1] - 'a' ) << 4 ) +
//STRIP001                        ( ( rSource[ USHORT(n1+1) ] - 'a' ) ) );
//STRIP001
//STRIP001  // decodieren
//STRIP001  USHORT nCode = 0;
//STRIP001  for ( USHORT n2 = 0; n2 < aRet.Len(); ++n2 )
//STRIP001  {
//STRIP001      aRet[n2] ^= pKey[nCode];
//STRIP001      if ( !pKey[++nCode] )
//STRIP001          nCode = 0;
//STRIP001  }
//STRIP001 */
//STRIP001  return aRet;
//STRIP001 }
//STRIP001

