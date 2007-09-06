/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx__xoutbmp.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:48:39 $
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

#include <svtools/solar.hrc>
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
