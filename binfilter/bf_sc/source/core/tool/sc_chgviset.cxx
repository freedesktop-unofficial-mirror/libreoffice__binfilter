/*************************************************************************
 *
 *  $RCSfile: sc_chgviset.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: er $ $Date: 2004-03-30 13:22:06 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

#include <unotools/textsearch.hxx>

#include "chgviset.hxx"
#include "rechead.hxx"
#include "chgtrack.hxx"
#include <tools/debug.hxx>//STRIP001
namespace binfilter {
// -----------------------------------------------------------------------
/*N*/ ScChangeViewSettings::~ScChangeViewSettings()
/*N*/ {
/*N*/   if(pCommentSearcher!=NULL)
/*?*/       delete pCommentSearcher;
/*N*/ }

//STRIP001 ScChangeViewSettings::ScChangeViewSettings( const ScChangeViewSettings& r )
//STRIP001 {
//STRIP001  SetTheComment(r.aComment);
//STRIP001
//STRIP001  aFirstDateTime  =r.aFirstDateTime;
//STRIP001  aLastDateTime   =r.aLastDateTime;
//STRIP001  aAuthorToShow   =r.aAuthorToShow;
//STRIP001  aRangeList      =r.aRangeList;
//STRIP001  eDateMode       =r.eDateMode;
//STRIP001  bShowIt         =r.bShowIt;
//STRIP001  bIsDate         =r.bIsDate;
//STRIP001  bIsAuthor       =r.bIsAuthor;
//STRIP001  bIsComment      =r.bIsComment;
//STRIP001  bIsRange        =r.bIsRange;
//STRIP001  bEveryoneButMe  =r.bEveryoneButMe;
//STRIP001  bShowAccepted   =r.bShowAccepted;
//STRIP001  bShowRejected   =r.bShowRejected;
//STRIP001
//STRIP001 }

//STRIP001 ScChangeViewSettings& ScChangeViewSettings::operator=( const ScChangeViewSettings& r )
//STRIP001 {
//STRIP001  SetTheComment(r.aComment);
//STRIP001
//STRIP001  aFirstDateTime  =r.aFirstDateTime;
//STRIP001  aLastDateTime   =r.aLastDateTime;
//STRIP001  aAuthorToShow   =r.aAuthorToShow;
//STRIP001  aRangeList      =r.aRangeList;
//STRIP001  eDateMode       =r.eDateMode;
//STRIP001  bShowIt         =r.bShowIt;
//STRIP001  bIsDate         =r.bIsDate;
//STRIP001  bIsAuthor       =r.bIsAuthor;
//STRIP001  bIsComment      =r.bIsComment;
//STRIP001  bIsRange        =r.bIsRange;
//STRIP001  bEveryoneButMe  =r.bEveryoneButMe;
//STRIP001  bShowAccepted   =r.bShowAccepted;
//STRIP001  bShowRejected   =r.bShowRejected;
//STRIP001
//STRIP001  return *this;
//STRIP001 }

//STRIP001 BOOL ScChangeViewSettings::IsValidComment(const String* pCommentStr) const
//STRIP001 {
//STRIP001  BOOL nTheFlag=TRUE;
//STRIP001
//STRIP001  if(pCommentSearcher!=NULL)
//STRIP001  {
//STRIP001      xub_StrLen nStartPos = 0;
//STRIP001      xub_StrLen nEndPos = pCommentStr->Len();
//STRIP001
//STRIP001      nTheFlag=pCommentSearcher->SearchFrwrd( *pCommentStr, &nStartPos, &nEndPos);
//STRIP001  }
//STRIP001  return nTheFlag;
//STRIP001 }

/*N*/ void ScChangeViewSettings::SetTheComment(const String& rString)
/*N*/ {
/*N*/   aComment=rString;
/*N*/   if(pCommentSearcher!=NULL)
/*N*/   {
/*N*/       delete pCommentSearcher;
/*N*/       pCommentSearcher=NULL;
/*N*/   }
/*N*/
/*N*/   if(rString.Len()>0)
/*N*/   {
/*N*/       utl::SearchParam aSearchParam( rString,
/*N*/           utl::SearchParam::SRCH_REGEXP,FALSE,FALSE,FALSE );
/*N*/
/*N*/       pCommentSearcher = new utl::TextSearch( aSearchParam, *ScGlobal::pCharClass );
/*N*/   }
/*N*/ }

/*N*/ void ScChangeViewSettings::Load( SvStream& rStream, USHORT nVer )
/*N*/ {
/*N*/   ScReadHeader aHdr( rStream );
/*N*/
/*N*/   BYTE nByte;
/*N*/   UINT32 nDT;
/*N*/   rStream >> bShowIt;
/*N*/   rStream >> bIsDate;
/*N*/   rStream >> nByte; eDateMode = (ScChgsDateMode)nByte;
/*N*/   rStream >> nDT; aFirstDateTime.SetDate( nDT );
/*N*/   rStream >> nDT; aFirstDateTime.SetTime( nDT );
/*N*/   rStream >> nDT; aLastDateTime.SetDate( nDT );
/*N*/   rStream >> nDT; aLastDateTime.SetTime( nDT );
/*N*/   rStream >> bIsAuthor;
/*N*/   rStream >> bEveryoneButMe;
/*N*/   rStream.ReadByteString( aAuthorToShow, rStream.GetStreamCharSet() );
/*N*/   rStream >> bIsRange;
/*N*/   aRangeList.Load( rStream, nVer );
/*N*/   if ( aHdr.BytesLeft() )
/*N*/   {
/*N*/       rStream >> bShowAccepted;
/*N*/       rStream >> bShowRejected;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       bShowAccepted = FALSE;
/*N*/       bShowRejected = FALSE;
/*N*/   }
/*N*/
/*N*/   // Zusaetzlich Kommentar-Informationen lesen (src509)
/*N*/   if ( aHdr.BytesLeft() )  //#59103#
/*N*/   {
/*N*/       rStream >> bIsComment;
/*N*/       rStream.ReadByteString( aComment, rStream.GetStreamCharSet() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       bIsComment = FALSE;
/*N*/       aComment.Erase();
/*N*/   }
/*N*/   SetTheComment(aComment);
/*N*/ }

/*N*/ void ScChangeViewSettings::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   ScWriteHeader aHdr( rStream, 42 );      // Groesse, wenn String und RangeList leer sind
/*N*/
/*N*/   rStream << bShowIt;
/*N*/   rStream << bIsDate;
/*N*/   rStream << (BYTE) eDateMode;
/*N*/   rStream << (UINT32) aFirstDateTime.GetDate();
/*N*/   rStream << (UINT32) aFirstDateTime.GetTime();
/*N*/   rStream << (UINT32) aLastDateTime.GetDate();
/*N*/   rStream << (UINT32) aLastDateTime.GetTime();
/*N*/   rStream << bIsAuthor;
/*N*/   rStream << bEveryoneButMe;
/*N*/   rStream.WriteByteString( aAuthorToShow, rStream.GetStreamCharSet() );
/*N*/   rStream << bIsRange;
/*N*/   aRangeList.Store( rStream );
/*N*/   rStream << bShowAccepted;
/*N*/   rStream << bShowRejected;
/*N*/
/*N*/   // Zusaetzlich Kommentar-Informationen schreiben (src509)
/*N*/   if(bIsComment || aComment.Len()>0) //#59103#
/*N*/   {
/*N*/       rStream << bIsComment;
/*N*/       rStream.WriteByteString( aComment, rStream.GetStreamCharSet() );
/*N*/   }
/*N*/ }


//STRIP001 void ScChangeViewSettings::AdjustDateMode( const ScDocument& rDoc )
//STRIP001 {
//STRIP001     switch ( eDateMode )
//STRIP001     {    // corresponds with ScViewUtil::IsActionShown
//STRIP001         case SCDM_DATE_EQUAL :
//STRIP001         case SCDM_DATE_NOTEQUAL :
//STRIP001             aFirstDateTime.SetTime( 0 );
//STRIP001             aLastDateTime = aFirstDateTime;
//STRIP001             aLastDateTime.SetTime( 23595999 );
//STRIP001             break;
//STRIP001         case SCDM_DATE_SAVE:
//STRIP001         {
//STRIP001             const ScChangeAction* pLast = 0;
//STRIP001             ScChangeTrack* pTrack = rDoc.GetChangeTrack();
//STRIP001             if ( pTrack )
//STRIP001             {
//STRIP001                 pLast = pTrack->GetLastSaved();
//STRIP001                 if ( pLast )
//STRIP001                 {
//STRIP001                     aFirstDateTime = pLast->GetDateTime();
//STRIP001 #if 0
//STRIP001 // This would be the proper handling. But since the SvxTPFilter dialog uses
//STRIP001 // DateField/TimeField, and the filter dialog is used in ScAcceptChgDlg as the
//STRIP001 // controlling instance, and the TimeFields are used there without seconds or
//STRIP001 // 100ths, we'd display some extra entries between the floor of the minute and
//STRIP001 // the start of the next minute.
//STRIP001                     // add one 100th second to point past last saved
//STRIP001                     aFirstDateTime += Time( 0, 0, 0, 1 );
//STRIP001 #else
//STRIP001                     // Set the next minute as the start time and assume that
//STRIP001                     // the document isn't saved, reloaded, edited and filter set
//STRIP001                     // all together during the gap between those two times.
//STRIP001                     aFirstDateTime += Time( 0, 1 );
//STRIP001                     aFirstDateTime.SetSec(0);
//STRIP001                     aFirstDateTime.Set100Sec(0);
//STRIP001 #endif
//STRIP001                 }
//STRIP001             }
//STRIP001             if ( !pLast )
//STRIP001             {
//STRIP001                 aFirstDateTime.SetDate( 18990101 );
//STRIP001                 aFirstDateTime.SetTime( 0 );
//STRIP001             }
//STRIP001             aLastDateTime = Date();
//STRIP001             aLastDateTime.SetYear( aLastDateTime.GetYear() + 100 );
//STRIP001         }
//STRIP001         break;
//STRIP001     }
//STRIP001 }

}
