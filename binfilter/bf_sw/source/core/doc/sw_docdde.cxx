/*************************************************************************
 *
 *  $RCSfile: sw_docdde.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:05:12 $
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

#include <stdlib.h>

// auto strip #ifndef _INTN_HXX
// auto strip #include <tools/intn.hxx>
// auto strip #endif
// auto strip #ifndef _APP_HXX
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#define _SVSTDARR_STRINGS
// auto strip #include <svtools/svstdarr.hxx>

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
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
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
//STRIP001  String sNm( GetAppCharClass().lower( rpBkmk->GetName() ));
//STRIP001  if( sNm.Equals( ((_FindItem*)pArgs)->rItem ) )
//STRIP001  {
//STRIP001      ((_FindItem*)pArgs)->pBkmk = rpBkmk;
//STRIP001      bRet = FALSE;
//STRIP001  }
//STRIP001
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



//STRIP001 BOOL SwDoc::GetData( const String& rItem, const String& rMimeType,
//STRIP001                   ::com::sun::star::uno::Any & rValue ) const
//STRIP001 {
//STRIP001  // haben wir ueberhaupt das Item vorraetig?
//STRIP001  String sItem( GetAppCharClass().lower( rItem ));
//STRIP001  _FindItem aPara( sItem );
//STRIP001  ((SwBookmarks&)*pBookmarkTbl).ForEach( 0, pBookmarkTbl->Count(),
//STRIP001                                          lcl_FindBookmark, &aPara );
//STRIP001  if( aPara.pBkmk )
//STRIP001  {
//STRIP001      // gefunden, als erfrage die Daten
//STRIP001      return SwServerObject( *aPara.pBkmk ).GetData( rValue, rMimeType );
//STRIP001  }
//STRIP001
//STRIP001  ((SwSectionFmts&)*pSectionFmtTbl).ForEach( 0, pSectionFmtTbl->Count(),
//STRIP001                                              lcl_FindSection, &aPara );
//STRIP001  if( aPara.pSectNd )
//STRIP001  {
//STRIP001      // gefunden, als erfrage die Daten
//STRIP001      return SwServerObject( *aPara.pSectNd ).GetData( rValue, rMimeType );
//STRIP001  }
//STRIP001
//STRIP001  ((SwFrmFmts*)pTblFrmFmtTbl)->ForEach( 0, pTblFrmFmtTbl->Count(),
//STRIP001                                          lcl_FindTable, &aPara );
//STRIP001  if( aPara.pTblNd )
//STRIP001  {
//STRIP001      return SwServerObject( *aPara.pTblNd ).GetData( rValue, rMimeType );
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }



//STRIP001 BOOL SwDoc::SetData( const String& rItem, const String& rMimeType,
//STRIP001                   const ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  // haben wir ueberhaupt das Item vorraetig?
//STRIP001  String sItem( GetAppCharClass().lower( rItem ));
//STRIP001  _FindItem aPara( sItem );
//STRIP001  pBookmarkTbl->ForEach( 0, pBookmarkTbl->Count(), lcl_FindBookmark, &aPara );
//STRIP001  if( aPara.pBkmk )
//STRIP001  {
//STRIP001      // gefunden, als erfrage die Daten
//STRIP001      return SwServerObject( *aPara.pBkmk ).SetData( rMimeType, rValue );
//STRIP001  }
//STRIP001
//STRIP001  pSectionFmtTbl->ForEach( 0, pSectionFmtTbl->Count(), lcl_FindSection, &aPara );
//STRIP001  if( aPara.pSectNd )
//STRIP001  {
//STRIP001      // gefunden, als erfrage die Daten
//STRIP001      return SwServerObject( *aPara.pSectNd ).SetData( rMimeType, rValue );
//STRIP001  }
//STRIP001
//STRIP001  pTblFrmFmtTbl->ForEach( 0, pTblFrmFmtTbl->Count(), lcl_FindTable, &aPara );
//STRIP001  if( aPara.pTblNd )
//STRIP001  {
//STRIP001      return SwServerObject( *aPara.pTblNd ).SetData( rMimeType, rValue );
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }



/*N*/ ::so3::SvLinkSource* SwDoc::CreateLinkSource( const String& rItem )
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
//STRIP001 /*?*/            if( 0 == (pObj = aPara.pBkmk->GetObject()) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pObj = new SwServerObject( *aPara.pBkmk );
//STRIP001 /*?*/                aPara.pBkmk->SetRefObject( pObj );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if( pObj->HasDataLinks() )
//STRIP001 /*?*/                return pObj;
//STRIP001 /*?*/            break;
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
//STRIP001 /*?*/            if( 0 == (pObj = aPara.pTblNd->GetTable().GetObject()) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pObj = new SwServerObject( *aPara.pTblNd );
//STRIP001 /*?*/                aPara.pTblNd->GetTable().SetRefObject( pObj );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if( pObj->HasDataLinks() )
//STRIP001 /*?*/                return pObj;
//STRIP001 /*?*/            break;
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
//STRIP001 /*?*/        String sName( sItem.Copy( 0, nPos ) );
//STRIP001 /*?*/        String sCmp( sItem.Copy( nPos + 1 ));
//STRIP001 /*?*/        rCC.toLower( sItem );
//STRIP001 /*?*/
//STRIP001 /*?*/        _FindItem aPara( sName );
//STRIP001 /*?*/
//STRIP001 /*?*/        if( sCmp.EqualsAscii( pMarkToTable ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rCC.toLower( sName );
//STRIP001 /*?*/            ((SwFrmFmts*)pTblFrmFmtTbl)->ForEach( 0, pTblFrmFmtTbl->Count(),
//STRIP001 /*?*/                                                    lcl_FindTable, &aPara );
//STRIP001 /*?*/            if( aPara.pTblNd )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rpRange = new SwNodeRange( *aPara.pTblNd, 0,
//STRIP001 /*?*/                                *aPara.pTblNd->EndOfSectionNode(), 1 );
//STRIP001 /*?*/                return TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if( sCmp.EqualsAscii( pMarkToFrame ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwNodeIndex* pIdx;
//STRIP001 /*?*/            SwNode* pNd;
//STRIP001 /*?*/            const SwFlyFrmFmt* pFlyFmt = FindFlyByName( sName );
//STRIP001 /*?*/            if( pFlyFmt &&
//STRIP001 /*?*/                0 != ( pIdx = (SwNodeIndex*)pFlyFmt->GetCntnt().GetCntntIdx() ) &&
//STRIP001 /*?*/                !( pNd = &pIdx->GetNode())->IsNoTxtNode() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rpRange = new SwNodeRange( *pNd, 1, *pNd->EndOfSectionNode() );
//STRIP001 /*?*/                return TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if( sCmp.EqualsAscii( pMarkToRegion ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            sItem = sName;              // wird unten behandelt !
//STRIP001 /*?*/            bWeiter = TRUE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if( sCmp.EqualsAscii( pMarkToOutline ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwPosition aPos( SwNodeIndex( (SwNodes&)GetNodes() ));
//STRIP001 /*?*/            if( GotoOutline( aPos, sName ))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwNode* pNd = &aPos.nNode.GetNode();
//STRIP001 /*?*/                BYTE nLvl = pNd->GetTxtNode()->GetTxtColl()->GetOutlineLevel();
//STRIP001 /*?*/
//STRIP001 /*?*/                const SwOutlineNodes& rOutlNds = GetNodes().GetOutLineNds();
//STRIP001 /*?*/                USHORT nPos;
//STRIP001 /*?*/                rOutlNds.Seek_Entry( pNd, &nPos );
//STRIP001 /*?*/                rpRange = new SwNodeRange( aPos.nNode, 0, aPos.nNode );
//STRIP001 /*?*/
//STRIP001 /*?*/                // dann suche jetzt noch das Ende vom Bereich
//STRIP001 /*?*/                for( ++nPos;
//STRIP001 /*?*/                        nPos < rOutlNds.Count() &&
//STRIP001 /*?*/                        nLvl < rOutlNds[ nPos ]->GetTxtNode()->
//STRIP001 /*?*/                                GetTxtColl()->GetOutlineLevel();
//STRIP001 /*?*/                    ++nPos )
//STRIP001 /*?*/                    ;       // es gibt keinen Block
//STRIP001 /*?*/
//STRIP001 /*?*/                if( nPos < rOutlNds.Count() )
//STRIP001 /*?*/                    rpRange->aEnd = *rOutlNds[ nPos ];
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    rpRange->aEnd = GetNodes().GetEndOfContent();
//STRIP001 /*?*/                return TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( !bWeiter )
//STRIP001 /*?*/            return FALSE;
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



/*?*/ extern "C" {
/*?*/   int
/*?*/ #if defined( WNT )
/*?*/   __cdecl
/*?*/ #endif
/*?*/ #if defined( ICC )
/*?*/   _Optlink
/*?*/ #endif
/*?*/       lcl_ServerNamesCmpNm( const void *pFirst, const void *pSecond)
/*?*/   {
/*?*/       const StringPtr pF = *(StringPtr*)pFirst;
/*?*/       const StringPtr pS = *(StringPtr*)pSecond;
/*?*/       ASSERT( pF && pS, "ungueltige Strings" );
/*?*/       StringCompare eCmp = pF->CompareTo( *pS );
/*?*/       return eCmp == COMPARE_EQUAL ? 0
/*?*/                           : eCmp == COMPARE_LESS ? 1 : -1;
/*?*/   }
/*?*/ }


//STRIP001 USHORT SwDoc::GetServerObjects( SvStrings& rStrArr ) const
//STRIP001 {
//STRIP001  USHORT n;
//STRIP001  for( n = pBookmarkTbl->Count(); n; )
//STRIP001  {
//STRIP001      SwBookmark* pBkmk = (*pBookmarkTbl)[ --n ];
//STRIP001      if( pBkmk->IsBookMark() && pBkmk->GetOtherPos() )
//STRIP001      {
//STRIP001          String* pNew = new String( pBkmk->GetName() );
//STRIP001          rStrArr.Insert( pNew, rStrArr.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  for( n = pSectionFmtTbl->Count(); n; )
//STRIP001  {
//STRIP001      SwSectionFmt* pFmt = (*pSectionFmtTbl)[ --n ];
//STRIP001      if( pFmt->IsInNodesArr() )
//STRIP001      {
//STRIP001          String* pNew = new String( pFmt->GetName() );
//STRIP001          rStrArr.Insert( pNew, rStrArr.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // und nochmal nach Namen sortieren:
//STRIP001  if( 0 != ( n = rStrArr.Count() ) )
//STRIP001      qsort( (void*)rStrArr.GetData(), n, sizeof( StringPtr ),
//STRIP001                                                  lcl_ServerNamesCmpNm );
//STRIP001
//STRIP001  return n;
//STRIP001 }




}
