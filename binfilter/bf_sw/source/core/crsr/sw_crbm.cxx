/*************************************************************************
 *
 *  $RCSfile: sw_crbm.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:48:21 $
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

#include "doc.hxx"
#include "crsrsh.hxx"
#include "ndtxt.hxx"
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif

#include "bookmrk.hxx"
#include "callnk.hxx"
#include "swcrsr.hxx"
namespace binfilter {


/*
 * Methoden der SwCrsrShell fuer Bookmark
 */


// am CurCrsr.SPoint
//STRIP001 FASTBOOL SwCrsrShell::SetBookmark( const KeyCode& rCode, const String& rName,
//STRIP001                              const String& rShortName, BOOKMARK_TYPE eMark )
//STRIP001 {
//STRIP001  StartAction();
//STRIP001  FASTBOOL bRet = 0 != pDoc->MakeBookmark( *GetCrsr(), rCode, rName,
//STRIP001                                          rShortName, eMark);
//STRIP001  EndAction();
//STRIP001  return bRet;
//STRIP001 }
// setzt CurCrsr.SPoint


//STRIP001 FASTBOOL SwCrsrShell::GotoBookmark(USHORT nPos, BOOL bAtStart)
//STRIP001 {
//STRIP001  // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  FASTBOOL bRet = TRUE;
//STRIP001  SwCallLink aLk( *this );
//STRIP001
//STRIP001  SwBookmark* pBkmk = pDoc->GetBookmarks()[ nPos ];
//STRIP001  SwCursor* pCrsr = GetSwCrsr();
//STRIP001  SwCrsrSaveState aSaveState( *pCrsr );
//STRIP001
//STRIP001  if( pBkmk->GetOtherPos() )
//STRIP001  {
//STRIP001      if( bAtStart )
//STRIP001          *pCrsr->GetPoint() = *pBkmk->GetOtherPos() < pBkmk->GetPos()
//STRIP001                                  ? *pBkmk->GetOtherPos()
//STRIP001                                  : pBkmk->GetPos();
//STRIP001      else
//STRIP001          *pCrsr->GetPoint() = *pBkmk->GetOtherPos() > pBkmk->GetPos()
//STRIP001                                  ? *pBkmk->GetOtherPos()
//STRIP001                                  : pBkmk->GetPos();
//STRIP001  }
//STRIP001  else
//STRIP001      *pCrsr->GetPoint() = pBkmk->GetPos();
//STRIP001
//STRIP001  if( pCrsr->IsSelOvr( SELOVER_CHECKNODESSECTION | SELOVER_TOGGLE ) )
//STRIP001  {
//STRIP001      pCrsr->DeleteMark();
//STRIP001      pCrsr->RestoreSavePos();
//STRIP001      bRet = FALSE;
//STRIP001  }
//STRIP001  else
//STRIP001      UpdateCrsr(SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE|SwCrsrShell::READONLY);
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::GotoBookmark(USHORT nPos)
//STRIP001 {
//STRIP001  // Crsr-Moves ueberwachen, evt. Link callen
//STRIP001  FASTBOOL bRet = TRUE;
//STRIP001  SwCallLink aLk( *this );
//STRIP001  SwBookmark* pBkmk = pDoc->GetBookmarks()[ nPos ];
//STRIP001  SwCursor* pCrsr = GetSwCrsr();
//STRIP001  SwCrsrSaveState aSaveState( *pCrsr );
//STRIP001
//STRIP001  *pCrsr->GetPoint() = pBkmk->GetPos();
//STRIP001  if( pBkmk->GetOtherPos() )
//STRIP001  {
//STRIP001      pCrsr->SetMark();
//STRIP001      *pCrsr->GetMark() = *pBkmk->GetOtherPos();
//STRIP001      if( *pCrsr->GetMark() > *pCrsr->GetPoint() )
//STRIP001          pCrsr->Exchange();
//STRIP001  }
//STRIP001
//STRIP001  if( pCrsr->IsSelOvr( SELOVER_CHECKNODESSECTION | SELOVER_TOGGLE ) )
//STRIP001  {
//STRIP001      pCrsr->DeleteMark();
//STRIP001      pCrsr->RestoreSavePos();
//STRIP001      bRet = FALSE;
//STRIP001  }
//STRIP001  else
//STRIP001      UpdateCrsr(SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE|SwCrsrShell::READONLY);
//STRIP001  return bRet;
//STRIP001 }
// TRUE, wenn's noch eine gab


//STRIP001 FASTBOOL SwCrsrShell::GoNextBookmark()
//STRIP001 {
//STRIP001  SwBookmark aBM(*GetCrsr()->GetPoint());
//STRIP001  USHORT nPos;
//STRIP001  const SwBookmarks& rBkmks = pDoc->GetBookmarks();
//STRIP001  rBkmks.Seek_Entry( &aBM, &nPos );
//STRIP001  if ( nPos == rBkmks.Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // alle die Inhaltlich auf der gleichen Position stehen, ueberspringen
//STRIP001  while( aBM.IsEqualPos( *rBkmks[ nPos ] ))
//STRIP001      if( ++nPos == rBkmks.Count() )
//STRIP001          return FALSE;
//STRIP001
//STRIP001  while( !GotoBookmark( nPos ))
//STRIP001      if( ++nPos == rBkmks.Count() )
//STRIP001          return FALSE;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 FASTBOOL SwCrsrShell::GoPrevBookmark()
//STRIP001 {
//STRIP001  const SwBookmarks& rBkmks = pDoc->GetBookmarks();
//STRIP001  if ( !rBkmks.Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nPos;
//STRIP001  SwCursor* pCrsr = GetSwCrsr();
//STRIP001  SwBookmark aBM( *pCrsr->GetPoint() );
//STRIP001  rBkmks.Seek_Entry( &aBM, &nPos );
//STRIP001
//STRIP001  const SwBookmark* pBkmk;
//STRIP001  // alle die Inhaltlich auf der gleichen Position stehen, ueberspringen
//STRIP001  do {
//STRIP001      if ( nPos == 0 )
//STRIP001          return FALSE;
//STRIP001  } while( aBM < *(pBkmk = rBkmks[--nPos]) || aBM.IsEqualPos( *pBkmk ));
//STRIP001
//STRIP001  SwCallLink aLk( *this );
//STRIP001  SwCrsrSaveState aSaveState( *pCrsr );
//STRIP001
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  do {
//STRIP001      pBkmk = rBkmks[ nPos ];
//STRIP001
//STRIP001      *pCrsr->GetPoint() = pBkmk->GetPos();
//STRIP001      if( pBkmk->GetOtherPos() )
//STRIP001      {
//STRIP001          pCrsr->SetMark();
//STRIP001          *pCrsr->GetMark() = *pBkmk->GetOtherPos();
//STRIP001          if( *pCrsr->GetMark() < *pCrsr->GetPoint() )
//STRIP001              pCrsr->Exchange();
//STRIP001      }
//STRIP001      if( !pCrsr->IsSelOvr( SELOVER_CHECKNODESSECTION | SELOVER_TOGGLE ) )
//STRIP001      {
//STRIP001          UpdateCrsr(SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE|SwCrsrShell::READONLY);
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001  } while( !bRet && nPos-- );
//STRIP001
//STRIP001  if( !bRet )
//STRIP001  {
//STRIP001      pCrsr->DeleteMark();
//STRIP001      pCrsr->RestoreSavePos();
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }



//STRIP001 USHORT SwCrsrShell::GetBookmarkCnt(BOOL bBkmrk) const
//STRIP001 {
//STRIP001  return pDoc->GetBookmarkCnt(bBkmrk);
//STRIP001 }


//STRIP001 SwBookmark& SwCrsrShell::GetBookmark(USHORT nPos, BOOL bBkmrk)
//STRIP001 {
//STRIP001  return pDoc->GetBookmark(nPos, bBkmrk);
//STRIP001 }


//STRIP001 void SwCrsrShell::DelBookmark(USHORT nPos)
//STRIP001 {
//STRIP001  StartAction();
//STRIP001  pDoc->DelBookmark(nPos);
//STRIP001  EndAction();
//STRIP001 }


//STRIP001 void SwCrsrShell::DelBookmark( const String& rName )
//STRIP001 {
//STRIP001  StartAction();
//STRIP001  pDoc->DelBookmark( rName );
//STRIP001  EndAction();
//STRIP001 }


/*N*/ USHORT SwCrsrShell::FindBookmark( const String& rName )
/*N*/ {
/*N*/   return pDoc->FindBookmark( rName );
/*N*/ }


        // erzeugt einen eindeutigen Namen. Der Name selbst muss vorgegeben
        // werden, es wird dann bei gleichen Namen nur durchnumeriert.
//STRIP001 void SwCrsrShell::MakeUniqueBookmarkName( String& rName )
//STRIP001 {
//STRIP001  pDoc->MakeUniqueBookmarkName( rName );
//STRIP001 }



}
