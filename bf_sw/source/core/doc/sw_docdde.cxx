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

#include <stdlib.h>

#include <tools/urlobj.hxx>

#define _SVSTDARR_STRINGS

#include <bf_svx/linkmgr.hxx>           // LinkManager
#include <unotools/charclass.hxx>

#include <fmtcntnt.hxx>

#include <horiornt.hxx>
#include <osl/diagnose.h>

#include <doc.hxx>
#include <swserv.hxx>           // fuer Server-Funktionalitaet
#include <bookmrk.hxx>          // fuer die Bookmarks
#include <section.hxx>          // fuer SwSectionFmt
#include <swtable.hxx>          // fuer SwTable
#include <pam.hxx>
#include <docary.hxx>
namespace binfilter {


struct _FindItem
{
    const String& rItem;
    SwBookmark* pBkmk;
    SwTableNode* pTblNd;
    SwSectionNode* pSectNd;

    _FindItem( const String& rS )
        : rItem( rS ), pBkmk( 0 ), pTblNd( 0 ), pSectNd( 0 )
    {}
};


/*N*/ BOOL lcl_FindBookmark( const SwBookmarkPtr& /*rpBkmk*/, void* /*pArgs*/ )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP");  // what does .foreach() do?
/*N*/   return TRUE;
/*N*/ }



/*N*/ BOOL lcl_FindSection( const SwSectionFmtPtr& rpSectFmt, void* pArgs )
/*N*/ {
/*N*/   SwSection* pSect = rpSectFmt->GetSection();
/*N*/   if( pSect )
/*N*/   {
/*N*/       String sNm( GetAppCharClass().lowercase( pSect->GetName() ));
/*N*/       if( sNm.Equals( ((_FindItem*)pArgs)->rItem ))
/*N*/       {
/*N*/           // gefunden, als erfrage die Daten
/*N*/           const SwNodeIndex* pIdx;
/*N*/           if( 0 != (pIdx = rpSectFmt->GetCntnt().GetCntntIdx() ) &&
/*N*/               &rpSectFmt->GetDoc()->GetNodes() == &pIdx->GetNodes() )
/*N*/           {
/*N*/               // eine Tabelle im normalen NodesArr
/*N*/               ((_FindItem*)pArgs)->pSectNd = pIdx->GetNode().GetSectionNode();
/*N*/               return FALSE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return TRUE;        // dann weiter
/*N*/ }



/*N*/ BOOL lcl_FindTable( const SwFrmFmtPtr& rpTableFmt, void* pArgs )
/*N*/ {
/*N*/   String sNm( GetAppCharClass().lowercase( rpTableFmt->GetName() ));
/*N*/   if( sNm.Equals( ((_FindItem*)pArgs)->rItem ))
/*N*/   {
/*?*/       SwTable* pTmpTbl;
/*?*/       SwTableBox* pFBox;
/*?*/       if( 0 != ( pTmpTbl = SwTable::FindTable( rpTableFmt ) ) &&
/*?*/           0 != ( pFBox = pTmpTbl->GetTabSortBoxes()[0] ) &&
/*?*/           pFBox->GetSttNd() &&
/*?*/           &rpTableFmt->GetDoc()->GetNodes() == &pFBox->GetSttNd()->GetNodes() )
/*?*/       {
/*?*/           // eine Tabelle im normalen NodesArr
/*?*/           ((_FindItem*)pArgs)->pTblNd = (SwTableNode*)
/*?*/                                       pFBox->GetSttNd()->FindTableNode();
/*?*/           return FALSE;
/*?*/       }
/*?*/ //nein!       // sollte der Namen schon passen, der Rest aber nicht, dann haben wir
/*?*/       // sie nicht. Die Namen sind immer eindeutig.
/*?*/   }
/*N*/   return TRUE;        // dann weiter
/*N*/ }



/*N*/ ::binfilter::SvLinkSource* SwDoc::CreateLinkSource( const String& rItem )
/*N*/ {
/*N*/   // haben wir ueberhaupt das Item vorraetig?
/*N*/   String sItem( GetAppCharClass().lowercase( rItem ));
/*N*/   _FindItem aPara( sItem );
/*N*/
/*N*/   SwServerObject* pObj;
/*N*/
/*N*/   do {    // middle check Loop
/*N*/       ((SwBookmarks&)*pBookmarkTbl).ForEach( 0, pBookmarkTbl->Count(),
/*N*/                                               lcl_FindBookmark, &aPara );
/*N*/
/*N*/       ((SwSectionFmts&)*pSectionFmtTbl).ForEach( 0, pSectionFmtTbl->Count(),
/*N*/                                                   lcl_FindSection, &aPara );
/*N*/       if( aPara.pSectNd )
/*N*/       {
/*N*/           // gefunden, also Hotlink einrichten
/*N*/           // sollten wir schon einer sein?
/*N*/           if( 0 == (pObj = aPara.pSectNd->GetSection().GetObject()) )
/*N*/           {
/*N*/               pObj = new SwServerObject( *aPara.pSectNd );
/*N*/               aPara.pSectNd->GetSection().SetRefObject( pObj );
/*N*/           }
/*N*/           else if( pObj->HasDataLinks() )
/*?*/               return pObj;
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       ((SwFrmFmts*)pTblFrmFmtTbl)->ForEach( 0, pTblFrmFmtTbl->Count(),
/*N*/                                               lcl_FindTable, &aPara );
/*?*/       // bis hierhin, also nicht vorhanden
/*?*/       return 0;
/*N*/   } while( FALSE );
/*N*/
/*N*/   // neu angelegt also ab in die Verwaltung
/*N*/   GetLinkManager().InsertServer( pObj );
/*N*/   return pObj;
/*N*/ }



/*N*/ BOOL SwDoc::SelectServerObj( const String& rStr, SwPaM*& rpPam,
/*N*/                           SwNodeRange*& rpRange ) const
/*N*/ {
/*N*/   // haben wir ueberhaupt das Item vorraetig?
/*N*/   rpPam = 0;
/*N*/   rpRange = 0;
/*N*/
/*N*/   String sItem( INetURLObject::decode( rStr, INET_HEX_ESCAPE,
/*N*/                                       INetURLObject::DECODE_WITH_CHARSET,
/*N*/                                       RTL_TEXTENCODING_UTF8 ));
/*N*/
/*N*/   const CharClass& rCC = GetAppCharClass();
/*N*/
/*N*/   // alte "Mechanik"
/*N*/   sItem = rCC.lowercase( sItem );
/*N*/   _FindItem aPara( sItem );
/*N*/   if( pBookmarkTbl->Count() )
/*N*/   {
/*N*/       ((SwBookmarks&)*pBookmarkTbl).ForEach( 0, pBookmarkTbl->Count(),
/*N*/                                           lcl_FindBookmark, &aPara );
/*N*/       if( aPara.pBkmk )
/*N*/       {
/*?*/           // gefunden, also erzeuge einen Bereich
/*?*/           if( aPara.pBkmk->GetOtherPos() )
/*?*/               // ein aufgespannter Bereich
/*?*/               rpPam = new SwPaM( aPara.pBkmk->GetPos(),
/*?*/                                   *aPara.pBkmk->GetOtherPos() );
/*?*/           return 0 != rpPam;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if( pSectionFmtTbl->Count() )
/*N*/   {
/*N*/       ((SwSectionFmts&)*pSectionFmtTbl).ForEach( 0, pSectionFmtTbl->Count(),
/*N*/                                               lcl_FindSection, &aPara );
/*N*/       if( aPara.pSectNd )
/*N*/       {
/*N*/           rpRange = new SwNodeRange( *aPara.pSectNd, 1,
/*N*/                                   *aPara.pSectNd->EndOfSectionNode() );
/*N*/           return TRUE;
/*N*/
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
