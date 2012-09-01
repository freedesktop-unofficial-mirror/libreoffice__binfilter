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


#include <horiornt.hxx>

#include <bf_sfx2/docfile.hxx>
#include <bf_svtools/inethist.hxx>

#include <fmtinfmt.hxx>
#include <txtinet.hxx>
#include <doc.hxx>
#include <visiturl.hxx>
#include <hints.hxx>
#include <ndtxt.hxx>
#include <viscrs.hxx>
#include <docsh.hxx>
namespace binfilter {


/*N*/ SwURLStateChanged::SwURLStateChanged( const SwDoc* pD )
/*N*/   : pDoc( pD )
/*N*/ {
/*N*/   StartListening( *INetURLHistory::GetOrCreate() );
/*N*/ }

/*N*/ SwURLStateChanged::~SwURLStateChanged()
/*N*/ {
/*N*/   EndListening( *INetURLHistory::GetOrCreate() );
/*N*/ }

/*N*/ void SwURLStateChanged::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& /*rHint*/ )
/*N*/ {
/*N*/ }

    // erfrage ob die URL besucht war. Uebers Doc, falls nur ein Bookmark
    // angegeben ist. Dann muss der Doc. Name davor gesetzt werden!
/*N*/ BOOL SwDoc::IsVisitedURL( const String& rURL ) const
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   static long nTmp = 0;
/*N*/   ++nTmp;
/*N*/ #endif
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/   if( rURL.Len() )
/*N*/   {
/*N*/       INetURLHistory *pHist = INetURLHistory::GetOrCreate();
/*N*/       if( '#' == rURL.GetChar( 0 ) && pDocShell && pDocShell->GetMedium() )
/*N*/       {
/*N*/           INetURLObject aIObj( pDocShell->GetMedium()->GetURLObject() );
/*N*/           aIObj.SetMark( rURL.Copy( 1 ) );
/*N*/           bRet = pHist->QueryUrl( aIObj );
/*N*/       }
/*N*/       else
/*N*/           bRet = pHist->QueryUrl( rURL );
/*N*/
/*N*/       // dann  wollen wird auch ueber Statusaenderungen in der History
/*N*/       // informiert werden!
/*N*/       if( !pURLStateChgd )
/*N*/       {
/*N*/           SwDoc* pD = (SwDoc*)this;
/*N*/           pD->pURLStateChgd = new SwURLStateChanged( this );
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
