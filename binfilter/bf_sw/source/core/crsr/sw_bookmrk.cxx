/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_bookmrk.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:42:21 $
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


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>
#endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>
#endif

#ifndef _ERRHDL_HXX //autogen
#include <errhdl.hxx>
#endif
namespace binfilter {

/*N*/ SV_IMPL_REF( SwServerObject )

/*N*/ SwBookmark::SwBookmark(const SwPosition& aPos, const KeyCode& rCode,
/*N*/                       const String& rName, const String& rShortName )
/*N*/   : SwModify( 0 ),
/*N*/   aStartMacro( aEmptyStr, aEmptyStr ),
/*N*/   aEndMacro  ( aEmptyStr, aEmptyStr ),
/*N*/   aCode(rCode),
/*N*/   aName(rName),
/*N*/   aShortName(rShortName),
/*N*/   pPos2( 0 ),
/*N*/   eMarkType( BOOKMARK )
/*N*/ {
/*N*/   pPos1 = new SwPosition(aPos);
/*N*/ }

// Beim Loeschen von Text werden Bookmarks mitgeloescht!


/*N*/ SwBookmark::~SwBookmark()
/*N*/ {
/*N*/   // falls wir noch der DDE-Bookmark sind, dann muss der aus dem
/*N*/   // Clipboard ausgetragen werden. Wird automatisch ueber DataChanged
/*N*/   // ausgeloest.
/*N*/   if( refObj.Is() )
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/
/*N*/   delete pPos1;
/*N*/   if( pPos2 )
/*N*/       delete pPos2;
/*N*/ }

// Vergleiche auf Basis der Dokumentposition

/*N*/ BOOL SwBookmark::operator<(const SwBookmark &rBM) const
/*N*/ {
/*N*/   const SwPosition* pThisPos = ( !pPos2 || *pPos1 <= *pPos2 ) ? pPos1 : pPos2;
/*N*/   const SwPosition* pBMPos = ( !rBM.pPos2 || *rBM.pPos1 <= *rBM.pPos2 )
/*N*/                                       ? rBM.pPos1 : rBM.pPos2;
/*N*/
/*N*/   return *pThisPos < *pBMPos;
/*N*/ }

/*N*/ BOOL SwBookmark::operator==(const SwBookmark &rBM) const
/*N*/ {
/*N*/   return (this == &rBM);
/*N*/ }


/*N*/ void SwBookmark::SetRefObject( SwServerObject* pObj )
/*N*/ {
/*N*/   refObj = pObj;
/*N*/ }



/*N*/ SwUNOMark::SwUNOMark( const SwPosition& aPos,
/*N*/               const KeyCode& rCode,
/*N*/               const String& rName,
/*N*/               const String& rShortName )
/*N*/   : SwBookmark( aPos, rCode, rName, rShortName )
/*N*/ {
/*N*/   eMarkType = UNO_BOOKMARK;
/*N*/ }

}
