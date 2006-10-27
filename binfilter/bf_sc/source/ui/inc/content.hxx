/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: content.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:03:12 $
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

#ifndef SC_CONTENT_HXX
#define SC_CONTENT_HXX

#ifndef _SVTREEBOX_HXX //autogen
#include <svtools/svtreebx.hxx>
#endif

namespace binfilter {

/*N*/ #define SC_CONTENT_ROOT           0
/*N*/ #define SC_CONTENT_TABLE      1
/*N*/ #define SC_CONTENT_RANGENAME  2
/*N*/ #define SC_CONTENT_DBAREA     3
/*N*/ #define SC_CONTENT_GRAPHIC        4
/*N*/ #define SC_CONTENT_OLEOBJECT  5
/*N*/ #define SC_CONTENT_NOTE           6
/*N*/ #define SC_CONTENT_AREALINK       7
/*N*/ #define SC_CONTENT_DRAWING        8
/*N*/ #define SC_CONTENT_COUNT      9

const ULONG SC_CONTENT_NOCHILD  = ~0UL;

//
//  TreeListBox fuer Inhalte
//





} //namespace binfilter
#endif // SC_NAVIPI_HXX

