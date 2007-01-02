/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_sortopt.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:46:13 $
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

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef INCLUDED_I18NPOOL_LANG_H
#include <i18npool/lang.h>
#endif

#ifndef _SORTOPT_HXX
#include <sortopt.hxx>
#endif
namespace binfilter {


/*N*/ SV_IMPL_PTRARR(SwSortKeys, SwSortKey*)

/*--------------------------------------------------------------------
    Beschreibung:   Sortier-Schluessel
 --------------------------------------------------------------------*/

/*N*/ SwSortKey::SwSortKey() :
/*N*/   eSortOrder( SRT_ASCENDING ),
/*N*/   nColumnId( 0 ),
/*N*/   bIsNumeric( TRUE )
/*N*/ {
/*N*/ }

/*N*/ SwSortKey::SwSortKey(const SwSortKey& rOld) :
/*N*/   eSortOrder( rOld.eSortOrder ),
/*N*/   sSortType( rOld.sSortType ),
/*N*/   nColumnId( rOld.nColumnId ),
/*N*/   bIsNumeric( rOld.bIsNumeric )
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Sortieroptionen fuers Sortieren
 --------------------------------------------------------------------*/


/*N*/ SwSortOptions::SwSortOptions()
/*?*/   : //STRIP001 eDirection( SRT_ROWS ),
/*N*/   nLanguage( LANGUAGE_SYSTEM ),
/*N*/   cDeli( 9 ),
/*N*/   bTable( FALSE ),
/*N*/   bIgnoreCase( FALSE )
/*N*/ {
/*N*/ }


/*N*/ SwSortOptions::SwSortOptions(const SwSortOptions& rOpt) :
/*N*/   eDirection( rOpt.eDirection ),
/*N*/   cDeli( rOpt.cDeli ),
/*N*/   nLanguage( rOpt.nLanguage ),
/*N*/   bTable( rOpt.bTable ),
/*N*/   bIgnoreCase( rOpt.bIgnoreCase )
/*N*/ {
/*N*/   for( USHORT i=0; i < rOpt.aKeys.Count(); ++i )
/*N*/   {
/*N*/       SwSortKey* pNew = new SwSortKey(*rOpt.aKeys[i]);
/*N*/       aKeys.C40_INSERT( SwSortKey, pNew, aKeys.Count());
/*N*/   }
/*N*/ }


/*N*/ SwSortOptions::~SwSortOptions()
/*N*/ {
/*N*/   aKeys.DeleteAndDestroy(0, aKeys.Count());
/*N*/ }



}
