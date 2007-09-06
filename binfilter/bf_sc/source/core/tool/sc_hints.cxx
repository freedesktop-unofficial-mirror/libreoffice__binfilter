/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_hints.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:46:22 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "hints.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1(ScPaintHint, SfxHint);
/*N*/ TYPEINIT1(ScUpdateRefHint, SfxHint);
/*N*/ TYPEINIT1(ScPointerChangedHint, SfxHint);
/*N*/ TYPEINIT1(ScLinkRefreshedHint, SfxHint);
/*N*/ TYPEINIT1(ScAutoStyleHint, SfxHint);

// -----------------------------------------------------------------------
//      ScPaintHint - Angabe, was neu gezeichnet werden muss
// -----------------------------------------------------------------------

/*N*/ ScPaintHint::ScPaintHint() :
/*N*/   aRange( 0,0,0, MAXCOL,MAXROW,MAXTAB ),
/*N*/   nParts( PAINT_ALL ),
/*N*/   bPrint( TRUE )
/*N*/ {
/*N*/ }

/*N*/ ScPaintHint::ScPaintHint( const ScRange& rRng, USHORT nPaint ) :
/*N*/   aRange( rRng ),
/*N*/   nParts( nPaint ),
/*N*/   bPrint( TRUE )
/*N*/ {
/*N*/ }

/*N*/ ScPaintHint::~ScPaintHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScUpdateRefHint - Referenz-Updaterei
// -----------------------------------------------------------------------

/*N*/ ScUpdateRefHint::ScUpdateRefHint( UpdateRefMode eMode, const ScRange& rR,
/*N*/                                   short nX, short nY, short nZ ) :
/*N*/   eUpdateRefMode( eMode ),
/*N*/   aRange( rR ),
/*N*/   nDx( nX ),
/*N*/   nDy( nY ),
/*N*/   nDz( nZ )
/*N*/ {
/*N*/ }

/*N*/ ScUpdateRefHint::~ScUpdateRefHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScPointerChangedHint - Pointer ist ungueltig geworden
// -----------------------------------------------------------------------

/*N*/ ScPointerChangedHint::ScPointerChangedHint( USHORT nF ) :
/*N*/   nFlags( nF )
/*N*/ {
/*N*/ }

/*N*/ ScPointerChangedHint::~ScPointerChangedHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScLinkRefreshedHint - a link has been refreshed
// -----------------------------------------------------------------------

/*N*/ ScLinkRefreshedHint::ScLinkRefreshedHint() :
/*N*/   nLinkType( SC_LINKREFTYPE_NONE ),
/*N*/   nDdeMode( 0 )
/*N*/ {
/*N*/ }

/*N*/ ScLinkRefreshedHint::~ScLinkRefreshedHint()
/*N*/ {
/*N*/ }

/*N*/ void ScLinkRefreshedHint::SetSheetLink( const String& rSourceUrl )
/*N*/ {
/*N*/   nLinkType = SC_LINKREFTYPE_SHEET;
/*N*/   aUrl = rSourceUrl;
/*N*/ }


/*N*/ void ScLinkRefreshedHint::SetAreaLink( const ScAddress& rPos )
/*N*/ {
/*N*/   nLinkType = SC_LINKREFTYPE_AREA;
/*N*/   aDestPos = rPos;
/*N*/ }

// -----------------------------------------------------------------------
//      ScAutoStyleHint - STYLE() function has been called
// -----------------------------------------------------------------------






}
