/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: w4wflt.hxx,v $
 * $Revision: 1.4 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
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
