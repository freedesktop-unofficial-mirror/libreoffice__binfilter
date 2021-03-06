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

#include <bf_svx/linkmgr.hxx>
#include <com/sun/star/uno/Sequence.h>

#include <horiornt.hxx>
#include <osl/diagnose.h>

#include <doc.hxx>
#include <swserv.hxx>
#include <swbaslnk.hxx>
#include <mvsave.hxx>
#include <bookmrk.hxx>
#include <pam.hxx>

#include <swerror.h>
namespace binfilter {

/*N*/ SV_IMPL_REF( SwServerObject )

/*N*/ SwServerObject::~SwServerObject()
/*N*/ {
/*N*/ }

/*N*/ BOOL SwServerObject::IsLinkInServer( const SwBaseLink* pChkLnk ) const
/*N*/ {
/*N*/   ULONG nSttNd = 0, nEndNd = 0;
/*N*/   xub_StrLen nStt = 0, nEnd = 0;
/*N*/   const SwNode* pNd = 0;
/*N*/   const SwNodes* pNds = 0;
/*N*/
/*N*/   switch( eType )
/*N*/   {
/*?*/   case BOOKMARK_SERVER:
/*?*/       if( CNTNT_TYPE.pBkmk->GetOtherPos() )
/*?*/       {
/*?*/           SwBookmark& rBkmk = *CNTNT_TYPE.pBkmk;
/*?*/           const SwPosition* pStt = &rBkmk.GetPos(),
/*?*/                           * pEnd = rBkmk.GetOtherPos();
/*?*/           if( *pStt > *pEnd )
/*?*/           {
/*?*/               const SwPosition* pTmp = pStt;
/*?*/               pStt = pEnd;
/*?*/               pEnd = pTmp;
/*?*/           }
/*?*/
/*?*/           nSttNd = pStt->nNode.GetIndex();
/*?*/           nStt = pStt->nContent.GetIndex();
/*?*/           nEndNd = pEnd->nNode.GetIndex();
/*?*/           nEnd = pEnd->nContent.GetIndex();
/*?*/           pNds = &pStt->nNode.GetNodes();
/*?*/       }
/*?*/       break;
/*?*/
/*?*/   case TABLE_SERVER:      pNd = CNTNT_TYPE.pTblNd;    break;
/*?*/   case SECTION_SERVER:    pNd = CNTNT_TYPE.pSectNd;   break;
/*?*/
/*N*/   case SECTION_SERVER+1:
/*N*/       return TRUE;
/*N*/   }
/*N*/
/*N*/   if( pNd )
/*N*/   {
/*N*/       nSttNd = pNd->GetIndex();
/*N*/       nEndNd = pNd->EndOfSectionIndex();
/*N*/       nStt = 0, nEnd = USHRT_MAX;
/*N*/       pNds = &pNd->GetNodes();
/*N*/   }
/*N*/
/*N*/   if( nSttNd && nEndNd )
/*N*/   {
/*N*/       // LinkManager besorgen:
/*N*/       const ::binfilter::SvBaseLinks& rLnks = pNds->GetDoc()->GetLinkManager().GetLinks();
/*N*/
/*N*/ // um Rekursionen zu Verhindern: ServerType umsetzen!
/*N*/ SwServerObject::ServerModes eSave = eType;
/*N*/ if( !pChkLnk )
/*N*/ // sowas sollte man nicht tun, wer weiss schon, wie gross ein enum ist
/*N*/ // ICC nimmt keinen int
/*N*/ // #41723#
/*N*/ //    *((int*)&eType) = SECTION_SERVER+1;
/*N*/   ((SwServerObject*)this)->eType = NONE_SERVER;
/*N*/       for( USHORT n = rLnks.Count(); n; )
/*N*/       {
/*N*/           const ::binfilter::SvBaseLink* pLnk = &(*rLnks[ --n ]);
/*N*/           if( pLnk && OBJECT_CLIENT_GRF != pLnk->GetObjType() &&
/*N*/               pLnk->ISA( SwBaseLink ) &&
/*N*/               !((SwBaseLink*)pLnk)->IsNoDataFlag() &&
/*N*/               ((SwBaseLink*)pLnk)->IsInRange( nSttNd, nEndNd, nStt, nEnd ))
/*N*/           {
/*N*/               if( pChkLnk )
/*N*/               {
/*N*/                   if( pLnk == pChkLnk ||
/*N*/                       ((SwBaseLink*)pLnk)->IsRecursion( pChkLnk ) )
/*N*/                       return TRUE;
/*N*/               }
/*N*/               else if( ((SwBaseLink*)pLnk)->IsRecursion( (SwBaseLink*)pLnk ) )
/*N*/                   ((SwBaseLink*)pLnk)->SetNoDataFlag();
/*N*/           }
/*N*/       }
/*N*/ if( !pChkLnk )
/*?*/   ((SwServerObject*)this)->eType = eSave;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ SwDataChanged::SwDataChanged( const SwPaM& rPam, USHORT nTyp )
/*N*/   : pPam( &rPam )
/*N*/   , pPos( 0 )
/*N*/   , pDoc( rPam.GetDoc() )
/*N*/   , nType( nTyp )
/*N*/ {
/*N*/   nNode = rPam.GetPoint()->nNode.GetIndex();
/*N*/   nCntnt = rPam.GetPoint()->nContent.GetIndex();
/*N*/ }

/*N*/ SwDataChanged::SwDataChanged( SwDoc* pDoc2, const SwPosition& rPos, USHORT nTyp )
/*N*/   : pPam( 0 )
/*N*/   , pPos( &rPos )
/*N*/   , pDoc( pDoc2 )
/*N*/   , nType( nTyp )
/*N*/ {
/*N*/   nNode = rPos.nNode.GetIndex();
/*N*/   nCntnt = rPos.nContent.GetIndex();
/*N*/ }
/*N*/

/*N*/ SwDataChanged::~SwDataChanged()
/*N*/ {
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
