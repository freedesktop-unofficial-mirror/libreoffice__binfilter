/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: impgrf.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:39:35 $
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
#ifndef _SVX_IMPGRF_HXX
#define _SVX_IMPGRF_HXX

// include ---------------------------------------------------------------

#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif

namespace binfilter {

// Funktionen ------------------------------------------------------------

// returnt einen static Graphic-Filter, wird einmalig angelegt,
// steht immer zur Verfuegung, DARF NIE geloescht werden!!!!
GraphicFilter* GetGrfFilter();
USHORT  FillFilter( GraphicFilter& rFilter );

// class SvxImportGraphicDialog ------------------------------------------
#ifndef SV_NODIALOG

#define ENABLE_STANDARD         ((USHORT)0x0001)    // Standard-Button
#define ENABLE_LINK             ((USHORT)0x0002)    // Verkn"upfungs-Box
#define ENABLE_STD_AND_LINK     (ENABLE_STANDARD | ENABLE_LINK)
#define ENABLE_PROPERTY         ((USHORT)0x0004)    // Eigenschaften-Button
#define ENABLE_ALL              ((USHORT)0x0007)    // alle
#define ENABLE_PROP_WITHOUTLINK ((USHORT)0x0008)    // Eigenschaften ohne Link
#define ENABLE_EMPTY_FILENAMES  ((USHORT)0x0010)    // Leere Dateinamen zulassen

#endif  // SV_NODIALOG

}//end of namespace binfilter
#endif
