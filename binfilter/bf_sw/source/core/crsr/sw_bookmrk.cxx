/*************************************************************************
 *
 *  $RCSfile: sw_bookmrk.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:48:20 $
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

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
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

//STRIP001 TYPEINIT1( SwBookmark, SwModify );  //rtti


/*N*/ SwBookmark::SwBookmark(const SwPosition& aPos)
/*N*/   : SwModify( 0 ),
/*N*/   aStartMacro( aEmptyStr, aEmptyStr ),
/*N*/   aEndMacro  ( aEmptyStr, aEmptyStr ),
/*N*/   pPos2( 0 ),
/*N*/   eMarkType( BOOKMARK )
/*N*/ {
/*N*/   pPos1 = new SwPosition( aPos );
/*N*/ }


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
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if( DDE_BOOKMARK == eMarkType && refObj->HasDataLinks() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ::so3::SvLinkSource* p = &refObj;
//STRIP001 /*?*/            p->SendDataChanged();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        refObj->SetNoServer();
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

//STRIP001 BOOL SwBookmark::IsEqualPos( const SwBookmark &rBM ) const
//STRIP001 {
//STRIP001  const SwPosition* pThisPos = ( !pPos2 || *pPos1 <= *pPos2 ) ? pPos1 : pPos2;
//STRIP001  const SwPosition* pBMPos = ( !rBM.pPos2 || *rBM.pPos1 <= *rBM.pPos2 )
//STRIP001                                      ? rBM.pPos1 : rBM.pPos2;
//STRIP001
//STRIP001  return *pThisPos == *pBMPos;
//STRIP001 }

/*N*/ void SwBookmark::SetRefObject( SwServerObject* pObj )
/*N*/ {
/*N*/   refObj = pObj;
/*N*/ }


//STRIP001 SwMark::SwMark( const SwPosition& aPos,
//STRIP001              const KeyCode& rCode,
//STRIP001              const String& rName,
//STRIP001              const String& rShortName )
//STRIP001  : SwBookmark( aPos, rCode, rName, rShortName )
//STRIP001 {
//STRIP001  eMarkType = MARK;
//STRIP001 }

/*N*/ SwUNOMark::SwUNOMark( const SwPosition& aPos,
/*N*/               const KeyCode& rCode,
/*N*/               const String& rName,
/*N*/               const String& rShortName )
/*N*/   : SwBookmark( aPos, rCode, rName, rShortName )
/*N*/ {
/*N*/   eMarkType = UNO_BOOKMARK;
/*N*/ }

}
