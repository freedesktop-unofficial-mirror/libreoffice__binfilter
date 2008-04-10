/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svx__xoutbmp.cxx,v $
 * $Revision: 1.10 $
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

#include <bf_svtools/solar.hrc>
#include "impgrf.hxx"
#include "xoutbmp.hxx"
namespace binfilter {

// -----------
// - Defines -
// -----------

#define FORMAT_BMP  String(RTL_CONSTASCII_USTRINGPARAM("bmp"))
#define FORMAT_GIF  String(RTL_CONSTASCII_USTRINGPARAM("gif"))
#define FORMAT_JPG  String(RTL_CONSTASCII_USTRINGPARAM("jpg"))
#define FORMAT_PNG  String(RTL_CONSTASCII_USTRINGPARAM("png"))

// --------------
// - XOutBitmap -
// --------------

GraphicFilter* XOutBitmap::pGrfFilter = NULL;

// -----------------------------------------------------------------------------

/*N*/ #ifdef _MSC_VER
/*N*/ #pragma optimize ( "", off )
/*N*/ #endif
/*N*/
/*N*/ // SJ: bIgnoreOptions is not used anymore
/*N*/
/*N*/ USHORT XOutBitmap::ExportGraphic( const Graphic& rGraphic, const INetURLObject& rURL,
/*N*/                                 GraphicFilter& rFilter, const USHORT nFormat,
/*N*/                                 BOOL bIgnoreOptions,
/*N*/                                 const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >* pFilterData )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }
}
