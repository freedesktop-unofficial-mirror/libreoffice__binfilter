/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: w4wflt.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 03:17:41 $
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
#ifndef _W4WFLT_HXX
#define _W4WFLT_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class String;
namespace binfilter {



// suche fuer das File den enstsprechenden Filter Typ
// und die Version
USHORT AutoDetec( const String& rFileName, USHORT & rVersion );

// W4W speichert beim Laden vom File pFileName die Ausgabe in pTmpFile.
// (das Tempfile wird hier anleget!)
// der Filter wird ueber nFilter bestimmt.
ULONG LoadFile( const String& rFileName, USHORT nFilter,
                const String& rVersion, String & rTmpFile );

// W4W liest beim Speichern vom File pFileName die Eingabe aus pTmpFile.
// der Filter wird ueber nFilter bestimmt.
ULONG SaveFile( const String& rFileName, const String& rTmpFile,
                USHORT nFilter, const String& rVersion );

enum W4WDLL_TYPE { W4WDLL_EXPORT, W4WDLL_IMPORT, W4WDLL_AUTODETEC };
FASTBOOL W4WDLLExist( W4WDLL_TYPE eType, USHORT nFilter = 0 );


} //namespace binfilter
#endif  // _W4WFLT_HXX
