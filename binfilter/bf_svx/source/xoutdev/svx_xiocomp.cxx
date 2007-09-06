/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_xiocomp.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:49:05 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <tools/debug.hxx>
#include "xiocomp.hxx"
namespace binfilter {

#define GLOBALOVERFLOW

/*************************************************************************
|*
|* Beschreibung: Verwaltungsklasse fuer Blocklaengen und Versionsnummern
|* Konstruktor, schreibt bzw. liest Versionsnummer
|*
\************************************************************************/

/*N*/ XIOCompat::XIOCompat( SvStream& rNewStream, USHORT nNewMode, UINT16 nVer )
/*N*/          : SdrDownCompat( rNewStream, nNewMode, TRUE ),
/*N*/            nVersion( nVer )
/*N*/ {
/*N*/   if( nNewMode == STREAM_WRITE )
/*N*/   {
/*N*/       DBG_ASSERT(nVer != XIOCOMPAT_VERSIONDONTKNOW,
/*N*/                  "kann unbekannte Version nicht schreiben");
/*N*/       rNewStream << nVersion;
/*N*/   }
/*N*/   else if( nNewMode == STREAM_READ )
/*N*/   {
/*N*/       DBG_ASSERT(nVer == XIOCOMPAT_VERSIONDONTKNOW,
/*N*/                  "Lesen mit Angabe der Version ist Quatsch!");
/*N*/       rNewStream >> nVersion;
/*N*/   }
/*N*/ }



}
