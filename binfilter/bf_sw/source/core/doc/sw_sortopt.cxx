/*************************************************************************
 *
 *  $RCSfile: sw_sortopt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:11:00 $
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

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _LANG_HXX
#include <tools/lang.hxx>
#endif

#ifndef _SORTOPT_HXX
#include <sortopt.hxx>
#endif


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

/*N*/ SwSortKey::SwSortKey(USHORT nId, const String& rSrtType, SwSortOrder eOrder) :
/*N*/   eSortOrder( eOrder ),
/*N*/   sSortType( rSrtType ),
/*N*/   nColumnId( nId ),
/*N*/   bIsNumeric( 0 == rSrtType.Len() )
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



