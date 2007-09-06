/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_chgviset.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:44:09 $
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

#include <unotools/textsearch.hxx>

#include "chgviset.hxx"
#include "rechead.hxx"
namespace binfilter {
// -----------------------------------------------------------------------
/*N*/ ScChangeViewSettings::~ScChangeViewSettings()
/*N*/ {
/*N*/   if(pCommentSearcher!=NULL)
/*?*/       delete pCommentSearcher;
/*N*/ }


// #i49161# this is needed to save documents with change tracking
ScChangeViewSettings& ScChangeViewSettings::operator=( const ScChangeViewSettings& r )
{
    SetTheComment(r.aComment);

    aFirstDateTime  =r.aFirstDateTime;
    aLastDateTime   =r.aLastDateTime;
    aAuthorToShow   =r.aAuthorToShow;
    aRangeList      =r.aRangeList;
    eDateMode       =r.eDateMode;
    bShowIt         =r.bShowIt;
    bIsDate         =r.bIsDate;
    bIsAuthor       =r.bIsAuthor;
    bIsComment      =r.bIsComment;
    bIsRange        =r.bIsRange;
    bEveryoneButMe  =r.bEveryoneButMe;
    bShowAccepted   =r.bShowAccepted;
    bShowRejected   =r.bShowRejected;

    return *this;
}


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



}
