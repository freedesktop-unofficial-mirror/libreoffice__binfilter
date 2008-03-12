/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_docdde.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:54:17 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <stdlib.h>

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#define _SVSTDARR_STRINGS

#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>           // LinkManager
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>           // fuer Server-Funktionalitaet
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>          // fuer die Bookmarks
#endif
#ifndef _SECTION_HXX
#include <section.hxx>          // fuer SwSectionFmt
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>          // fuer SwTable
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
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

    void ClearObj()
    {
        if( pBkmk )
            pBkmk->SetRefObject( 0 );
        else if( pSectNd )
            pSectNd->GetSection().SetRefObject( 0 );
        else if( pTblNd )
            pTblNd->GetTable().SetRefObject( 0 );
    }
};


/*N*/ BOOL lcl_FindBookmark( const SwBookmarkPtr& rpBkmk, void* pArgs )
/*N*/ {
/*N*/   BOOL bRet = TRUE; DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return bRet;
/*N*/ }



/*N*/ BOOL lcl_FindSection( const SwSectionFmtPtr& rpSectFmt, void* pArgs )
/*N*/ {
/*N*/   SwSection* pSect = rpSectFmt->GetSection();
/*N*/   if( pSect )
/*N*/   {
/*N*/       String sNm( GetAppCharClass().lower( pSect->GetName() ));
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
/*N*/ //nein!!          // sollte der Namen schon passen, der Rest aber nicht, dann haben wir
/*N*/           // sie nicht. Die Namen sind immer eindeutig.
/*N*/       }
/*N*/   }
/*N*/   return TRUE;        // dann weiter
/*N*/ }



/*N*/ BOOL lcl_FindTable( const SwFrmFmtPtr& rpTableFmt, void* pArgs )
/*N*/ {
/*N*/   String sNm( GetAppCharClass().lower( rpTableFmt->GetName() ));
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
/*N*/   String sItem( GetAppCharClass().lower( rItem ));
/*N*/   _FindItem aPara( sItem );
/*N*/
/*N*/   SwServerObject* pObj;
/*N*/
/*N*/   do {    // middle check Loop
/*N*/       ((SwBookmarks&)*pBookmarkTbl).ForEach( 0, pBookmarkTbl->Count(),
/*N*/                                               lcl_FindBookmark, &aPara );
/*N*/       if( aPara.pBkmk && aPara.pBkmk->GetOtherPos() )
/*N*/       {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   // gefunden, also Hotlink einrichten
/*?*/           // sollten wir schon einer sein?
/*N*/       }
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
/*N*/       if( aPara.pTblNd )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // gefunden, also Hotlink einrichten
/*?*/           // sollten wir schon einer sein?
/*?*/       }
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
/*N*/   xub_StrLen nPos = sItem.Search( cMarkSeperator );
/*N*/
/*N*/   const CharClass& rCC = GetAppCharClass();
/*N*/
/*N*/   // Erweiterung fuer die Bereiche, nicht nur Bookmarks/Bereiche linken,
/*N*/   // sondern auch Rahmen(Text!), Tabellen, Gliederungen:
/*N*/   if( STRING_NOTFOUND != nPos )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bWeiter = FALSE;
/*N*/   }
/*N*/
/*N*/   // alte "Mechanik"
/*N*/   rCC.toLower( sItem );
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
