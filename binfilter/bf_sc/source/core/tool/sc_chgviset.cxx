/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

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
            ::rtl::OUString search(rString);
/*N*/       utl::SearchParam aSearchParam( search,
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
/*N*/   aAuthorToShow = rStream.ReadUniOrByteString( rStream.GetStreamCharSet() );
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
/*N*/       aComment = rStream.ReadUniOrByteString( rStream.GetStreamCharSet() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       bIsComment = FALSE;
/*N*/       aComment.Erase();
/*N*/   }
/*N*/   SetTheComment(aComment);
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
