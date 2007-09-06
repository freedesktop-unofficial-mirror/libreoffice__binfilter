/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_editdbg.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:35:16 $
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

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif
#ifndef _EEITEMID_HXX
#include "eeitemid.hxx"
#endif





#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

#include <editdoc.hxx>
namespace binfilter {

#if defined( DBG_UTIL ) || ( OSL_DEBUG_LEVEL > 1 )









/*N*/ BOOL CheckOrderedList( CharAttribArray& rAttribs, BOOL bStart )
/*N*/ {
/*N*/   USHORT nPrev = 0;
/*N*/   for ( USHORT nAttr = 0; nAttr < rAttribs.Count(); nAttr++ )
/*N*/   {
/*N*/       EditCharAttrib* pAttr = rAttribs[nAttr];
/*N*/       USHORT nCur = bStart ? pAttr->GetStart() : pAttr->GetEnd();
/*N*/       if ( nCur < nPrev )
/*N*/           return FALSE;
/*N*/
/*N*/       nPrev = nCur;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

#endif

}
