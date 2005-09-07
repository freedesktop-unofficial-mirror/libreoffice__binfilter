/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hiranges.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:54:19 $
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

#ifndef SC_HIRANGES_HXX
#define SC_HIRANGES_HXX

#ifndef _COLOR_HXX //autogen
#include <tools/color.hxx>
#endif

// auto strip #ifndef SC_SCGLOB_HXX
// auto strip #include "global.hxx"
// auto strip #endif
#include <tools/debug.hxx> //STRIP001
namespace binfilter {
//==================================================================

//STRIP001 struct ScHighlightEntry
//STRIP001 {
//STRIP001  ScRange     aRef;
//STRIP001  Color       aColor;
//STRIP001
//STRIP001  ScHighlightEntry( const ScRange& rR, const Color& rC ) :
//STRIP001      aRef(rR), aColor(rC) {}
//STRIP001 };

class ScHighlightRanges
{
//STRIP001  List        aEntries;

public:
            ScHighlightRanges(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScHighlightRanges();
//STRIP001          ~ScHighlightRanges();
//STRIP001
//STRIP001  ULONG   Count() const                       { return aEntries.Count(); }
//STRIP001  void    Insert( ScHighlightEntry* pNew )    { aEntries.Insert(pNew, LIST_APPEND); }
//STRIP001  ScHighlightEntry* GetObject( ULONG nIndex ) const
//STRIP001                      { return (ScHighlightEntry*)aEntries.GetObject(nIndex); }
};



} //namespace binfilter
#endif


