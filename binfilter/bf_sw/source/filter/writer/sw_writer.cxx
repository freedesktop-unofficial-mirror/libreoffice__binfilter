/*************************************************************************
 *
 *  $RCSfile: sw_writer.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:52 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#define _SVSTDARR_STRINGSSORTDTOR
#include <svtools/svstdarr.hxx>

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif
#ifndef _SVX_IMPGRF_HXX //autogen
#include <bf_svx/impgrf.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _EEITEM_HXX
#include <bf_svx/eeitem.hxx>
#endif

#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _FORMAT_HXX
#include <format.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>          // fuer SwBookmark ...
#endif
#ifndef _NUMRULE_HXX //autogen
#include <numrule.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif

// Stringbuffer fuer die umgewandelten Zahlen
static sal_Char aNToABuf[] = "0000000000000000000000000";
#define NTOABUFLEN (sizeof(aNToABuf))

/*N*/ DECLARE_TABLE( SwBookmarkNodeTable, SvPtrarr* )

/*N*/ struct Writer_Impl
/*N*/ {
/*N*/   SvStringsSortDtor *pSrcArr, *pDestArr;
/*N*/   SvPtrarr* pFontRemoveLst, *pBkmkArr;
/*N*/   SwBookmarkNodeTable* pBkmkNodePos;
/*N*/
/*N*/   Writer_Impl( const SwDoc& rDoc );
/*N*/   ~Writer_Impl();
/*N*/
/*N*/   void RemoveFontList( SwDoc& rDoc );
//STRIP001  void InsertBkmk( const SwBookmark& rBkmk );
/*N*/ };

/*N*/ Writer_Impl::Writer_Impl( const SwDoc& rDoc )
/*N*/   : pSrcArr( 0 ), pDestArr( 0 ), pFontRemoveLst( 0 ), pBkmkNodePos( 0 )
/*N*/ {
/*N*/ }

/*N*/ Writer_Impl::~Writer_Impl()
/*N*/ {
/*N*/   delete pSrcArr;
/*N*/   delete pDestArr;
/*N*/   delete pFontRemoveLst;
/*N*/
/*N*/   if( pBkmkNodePos )
/*N*/   {
/*?*/       for( SvPtrarr* p = pBkmkNodePos->First(); p; p = pBkmkNodePos->Next() )
/*?*/           delete p;
/*?*/       delete pBkmkNodePos;
/*N*/   }
/*N*/ }

/*N*/ void Writer_Impl::RemoveFontList( SwDoc& rDoc )
/*N*/ {
/*N*/   ASSERT( pFontRemoveLst, "wo ist die FontListe?" );
/*N*/   for( USHORT i = pFontRemoveLst->Count(); i; )
/*N*/   {
/*N*/       SvxFontItem* pItem = (SvxFontItem*)(*pFontRemoveLst)[ --i ];
/*N*/       rDoc.GetAttrPool().Remove( *pItem );
/*N*/   }
/*N*/ }

//STRIP001 void Writer_Impl::InsertBkmk( const SwBookmark& rBkmk )
//STRIP001 {
//STRIP001  if( !pBkmkNodePos )
//STRIP001      pBkmkNodePos = new SwBookmarkNodeTable;
//STRIP001
//STRIP001  ULONG nNd = rBkmk.GetPos().nNode.GetIndex();
//STRIP001  SvPtrarr* pArr = pBkmkNodePos->Get( nNd );
//STRIP001  if( !pArr )
//STRIP001  {
//STRIP001      pArr = new SvPtrarr( 1, 4 );
//STRIP001      pBkmkNodePos->Insert( nNd, pArr );
//STRIP001  }
//STRIP001
//STRIP001  void* p = (void*)&rBkmk;
//STRIP001  pArr->Insert( p, pArr->Count() );
//STRIP001
//STRIP001  if( rBkmk.GetOtherPos() && rBkmk.GetOtherPos()->nNode != nNd )
//STRIP001  {
//STRIP001      nNd = rBkmk.GetOtherPos()->nNode.GetIndex();
//STRIP001      pArr = pBkmkNodePos->Get( nNd );
//STRIP001      if( !pArr )
//STRIP001      {
//STRIP001          pArr = new SvPtrarr( 1, 4 );
//STRIP001          pBkmkNodePos->Insert( nNd, pArr );
//STRIP001      }
//STRIP001      pArr->Insert( p, pArr->Count() );
//STRIP001  }
//STRIP001 }

/*
 * Dieses Modul ist die Zentrale-Sammelstelle fuer alle Write-Filter
 * und ist eine DLL !
 *
 * Damit der Writer mit den unterschiedlichen Writern arbeiten kann,
 * muessen fuer diese die Ausgabe-Funktionen der Inhalts tragenden
 * Objecte auf die verschiedenen Ausgabe-Funktionen gemappt werden.
 *
 * Dazu kann fuer jedes Object ueber den Which-Wert in einen Tabelle ge-
 * griffen werden, um seine Ausgabe-Funktion zu erfragen.
 * Diese Funktionen stehen in den entsprechenden Writer-DLL's.
 */

/*N*/ Writer::Writer()
/*N*/   : pImpl( 0 ), pStrm( 0 ), pOrigPam( 0 ), pOrigFileName( 0 ),
/*N*/   pCurPam(0), pDoc( 0 )
/*N*/ {
/*N*/   bWriteAll = bShowProgress = bUCS2_WithStartChar = TRUE;
/*N*/   bASCII_NoLastLineEnd = bASCII_ParaAsBlanc = bASCII_ParaAsCR =
/*N*/       bWriteClipboardDoc = bWriteOnlyFirstTable = bBlock =
/*N*/       bOrganizerMode = FALSE;
/*N*/ }

/*N*/ Writer::~Writer()
/*N*/ {
/*N*/ }

/*N*/ void Writer::ResetWriter()
/*N*/ {
/*N*/   if( pImpl && pImpl->pFontRemoveLst )
/*N*/       pImpl->RemoveFontList( *pDoc );
/*N*/   delete pImpl, pImpl = 0;
/*N*/
/*N*/   if( pCurPam )
/*N*/   {
/*N*/       while( pCurPam->GetNext() != pCurPam )
/*?*/           delete pCurPam->GetNext();
/*N*/       delete pCurPam;
/*N*/   }
/*N*/   pCurPam = 0;
/*N*/   pOrigFileName = 0;
/*N*/   pDoc = 0;
/*N*/   pStrm = 0;
/*N*/
/*N*/   bShowProgress = bUCS2_WithStartChar = TRUE;
/*N*/   bASCII_NoLastLineEnd = bASCII_ParaAsBlanc = bASCII_ParaAsCR =
/*N*/       bWriteClipboardDoc = bWriteOnlyFirstTable = bBlock =
/*N*/       bOrganizerMode = FALSE;
/*N*/ }

/*N*/ BOOL Writer::CopyNextPam( SwPaM ** ppPam )
/*N*/ {
/*N*/   if( (*ppPam)->GetNext() == pOrigPam )
/*N*/   {
/*N*/       *ppPam = pOrigPam;          // wieder auf den Anfangs-Pam setzen
/*N*/       return FALSE;               // Ende vom Ring
/*N*/   }
/*N*/
/*N*/   // ansonsten kopiere den die Werte aus dem naechsten Pam
/*?*/   *ppPam = ((SwPaM*)(*ppPam)->GetNext() );
/*?*/
/*?*/   *pCurPam->GetPoint() = *(*ppPam)->Start();
/*?*/   *pCurPam->GetMark() = *(*ppPam)->End();
/*?*/
/*?*/   return TRUE;
/*N*/ }

// suche die naechste Bookmark-Position aus der Bookmark-Tabelle

//STRIP001 USHORT Writer::FindPos_Bkmk( const SwPosition& rPos ) const
//STRIP001 {
//STRIP001  USHORT nRet = USHRT_MAX;
//STRIP001  const SwBookmarks& rBkmks = pDoc->GetBookmarks();
//STRIP001
//STRIP001  if( rBkmks.Count() )
//STRIP001  {
//STRIP001      SwBookmark aBkmk( rPos );
//STRIP001      USHORT nPos;
//STRIP001      if( rBkmks.Seek_Entry( &aBkmk, &nPos ))
//STRIP001      {
//STRIP001          // suche abwaerts nach weiteren Bookmarks auf der Cursor-Position
//STRIP001          while( 0 < nPos &&
//STRIP001              rBkmks[ nPos-1 ]->IsEqualPos( aBkmk ))
//STRIP001              --nPos;
//STRIP001      }
//STRIP001      else if( nPos < rBkmks.Count() )
//STRIP001          nRet = nPos;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


//STRIP001 SwPaM* Writer::NewSwPaM( SwDoc & rDoc, ULONG nStartIdx, ULONG nEndIdx,
//STRIP001                      BOOL bNodesArray ) const
//STRIP001 {
//STRIP001  SwNodes* pNds = bNodesArray ? &rDoc.GetNodes() : (SwNodes*)rDoc.GetUndoNds();
//STRIP001
//STRIP001  SwNodeIndex aStt( *pNds, nStartIdx );
//STRIP001  SwCntntNode* pCNode = aStt.GetNode().GetCntntNode();
//STRIP001  if( !pCNode && 0 == ( pCNode = pNds->GoNext( &aStt )) )
//STRIP001      ASSERT( !this, "An StartPos kein ContentNode mehr" );
//STRIP001
//STRIP001  SwPaM* pNew = new SwPaM( aStt );
//STRIP001  pNew->SetMark();
//STRIP001  aStt = nEndIdx;
//STRIP001  if( 0 == (pCNode = aStt.GetNode().GetCntntNode()) &&
//STRIP001      0 == (pCNode = pNds->GoPrevious( &aStt )) )
//STRIP001      ASSERT( !this, "An StartPos kein ContentNode mehr" );
//STRIP001  pCNode->MakeEndIndex( &pNew->GetPoint()->nContent );
//STRIP001  pNew->GetPoint()->nNode = aStt;
//STRIP001  return pNew;
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Stream-spezifisches
/*N*/ #ifndef PRODUCT
/*N*/ SvStream& Writer::Strm()
/*N*/ {
/*N*/   ASSERT( pStrm, "Oh-oh. Dies ist ein Storage-Writer. Gleich knallts!" );
/*N*/   return *pStrm;
/*N*/ }
/*N*/ #endif


//STRIP001 SvStream& Writer::OutHex( SvStream& rStrm, ULONG nHex, BYTE nLen )
//STRIP001 {                                                   // in einen Stream aus
//STRIP001  // Pointer an das Bufferende setzen
//STRIP001  sal_Char* pStr = aNToABuf + (NTOABUFLEN-1);
//STRIP001  for( BYTE n = 0; n < nLen; ++n )
//STRIP001  {
//STRIP001      *(--pStr) = (sal_Char)(nHex & 0xf ) + 48;
//STRIP001      if( *pStr > '9' )
//STRIP001          *pStr += 39;
//STRIP001      nHex >>= 4;
//STRIP001  }
//STRIP001  return rStrm << pStr;
//STRIP001 }

//STRIP001 SvStream& Writer::OutLong( SvStream& rStrm, long nVal )
//STRIP001 {
//STRIP001  // Pointer an das Bufferende setzen
//STRIP001  sal_Char* pStr = aNToABuf + (NTOABUFLEN-1);
//STRIP001
//STRIP001  int bNeg = nVal < 0;
//STRIP001  if( bNeg )
//STRIP001      nVal = -nVal;
//STRIP001
//STRIP001  do {
//STRIP001      *(--pStr) = (sal_Char)(nVal % 10 ) + 48;
//STRIP001      nVal /= 10;
//STRIP001  } while( nVal );
//STRIP001
//STRIP001  // Ist Zahl negativ, dann noch -
//STRIP001  if( bNeg )
//STRIP001      *(--pStr) = '-';
//STRIP001
//STRIP001  return rStrm << pStr;
//STRIP001 }

//STRIP001 SvStream& Writer::OutULong( SvStream& rStrm, ULONG nVal )
//STRIP001 {
//STRIP001  // Pointer an das Bufferende setzen
//STRIP001  sal_Char* pStr = aNToABuf + (NTOABUFLEN-1);
//STRIP001
//STRIP001  do {
//STRIP001      *(--pStr) = (sal_Char)(nVal % 10 ) + 48;
//STRIP001      nVal /= 10;
//STRIP001  } while ( nVal );
//STRIP001  return rStrm << pStr;
//STRIP001 }


/*N*/ ULONG Writer::Write( SwPaM& rPaM, SvStream& rStrm, const String* pFName )
/*N*/ {
/*N*/   pStrm = &rStrm;
/*N*/   pDoc = rPaM.GetDoc();
/*N*/   pOrigFileName = pFName;
/*N*/   pImpl = new Writer_Impl( *pDoc );
/*N*/
/*N*/   // PaM kopieren, damit er veraendert werden kann
/*N*/   pCurPam = new SwPaM( *rPaM.End(), *rPaM.Start() );
/*N*/   // zum Vergleich auf den akt. Pam sichern
/*N*/   pOrigPam = &rPaM;
/*N*/
/*N*/   ULONG nRet = WriteStream();
/*N*/
/*N*/   ResetWriter();
/*N*/
/*N*/   return nRet;
/*N*/ }

//STRIP001 ULONG Writer::Write( SwPaM& rPam, SfxMedium& rMed, const String* pFileName )
//STRIP001 {
//STRIP001  return IsStgWriter()
//STRIP001              ? Write( rPam, *rMed.GetStorage(), pFileName )
//STRIP001              : Write( rPam, *rMed.GetOutStream(), pFileName );
//STRIP001 }

/*N*/ ULONG Writer::Write( SwPaM& rPam, SvStorage&, const String* )
/*N*/ {
/*N*/   ASSERT( !this, "Schreiben in Storages auf einem Stream?" );
/*N*/   return ERR_SWG_WRITE_ERROR;
/*N*/ }


//STRIP001 BOOL Writer::CopyLocalFileToINet( String& rFileNm )
//STRIP001 {
//STRIP001  if( !pOrigFileName )                // can be happen, by example if we
//STRIP001      return FALSE;                   // write into the clipboard
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  INetURLObject aFileUrl( rFileNm ), aTargetUrl( *pOrigFileName );
//STRIP001
//STRIP001 // JP 01.11.00: what is the correct question for the portal??
//STRIP001 //   if( aFileUrl.GetProtocol() == aFileUrl.GetProtocol() )
//STRIP001 //       return bRet;
//STRIP001 // this is our old without the Mail-Export
//STRIP001     if( ! ( INET_PROT_FILE == aFileUrl.GetProtocol() &&
//STRIP001          INET_PROT_FILE != aTargetUrl.GetProtocol() &&
//STRIP001          INET_PROT_FTP <= aTargetUrl.GetProtocol() &&
//STRIP001          INET_PROT_NEWS >= aTargetUrl.GetProtocol() ) )
//STRIP001      return bRet;
//STRIP001
//STRIP001  if( pImpl->pSrcArr )
//STRIP001  {
//STRIP001      // wurde die Datei schon verschoben
//STRIP001      USHORT nPos;
//STRIP001      if( pImpl->pSrcArr->Seek_Entry( &rFileNm, &nPos ))
//STRIP001      {
//STRIP001          rFileNm = *(*pImpl->pDestArr)[ nPos ];
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pImpl->pSrcArr = new SvStringsSortDtor( 4, 4 );
//STRIP001      pImpl->pDestArr = new SvStringsSortDtor( 4, 4 );
//STRIP001  }
//STRIP001
//STRIP001  String *pSrc = new String( rFileNm );
//STRIP001  String *pDest = new String( aTargetUrl.GetPartBeforeLastName() );
//STRIP001  *pDest += aFileUrl.GetName();
//STRIP001
//STRIP001  SfxMedium aSrcFile( *pSrc, STREAM_READ, FALSE );
//STRIP001  SfxMedium aDstFile( *pDest, STREAM_WRITE | STREAM_SHARE_DENYNONE, FALSE );
//STRIP001
//STRIP001  *aDstFile.GetOutStream() << *aSrcFile.GetInStream();
//STRIP001
//STRIP001  aSrcFile.Close();
//STRIP001  aDstFile.Commit();
//STRIP001
//STRIP001  bRet = 0 == aDstFile.GetError();
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      pImpl->pSrcArr->Insert( pSrc );
//STRIP001      pImpl->pDestArr->Insert( pDest );
//STRIP001      rFileNm = *pDest;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      delete pSrc;
//STRIP001      delete pDest;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ void Writer::PutNumFmtFontsInAttrPool()
/*N*/ {
/*N*/   if( !pImpl )
/*?*/       pImpl = new Writer_Impl( *pDoc );
/*N*/
/*N*/   // dann gibt es noch in den NumRules ein paar Fonts
/*N*/   // Diese in den Pool putten. Haben sie danach einen RefCount > 1
/*N*/   // kann es wieder entfernt werden - ist schon im Pool
/*N*/   SfxItemPool& rPool = pDoc->GetAttrPool();
/*N*/   const SwNumRuleTbl& rListTbl = pDoc->GetNumRuleTbl();
/*N*/   const SwNumRule* pRule;
/*N*/   const SwNumFmt* pFmt;
/*N*/   const Font *pFont, *pDefFont = &SwNumRule::GetDefBulletFont();
/*N*/   BOOL bCheck = FALSE;
/*N*/
/*N*/   for( USHORT nGet = rListTbl.Count(); nGet; )
/*N*/       if( pDoc->IsUsed( *(pRule = rListTbl[ --nGet ] )))
/*?*/           for( BYTE nLvl = 0; nLvl < MAXLEVEL; ++nLvl )
/*?*/               if( SVX_NUM_CHAR_SPECIAL == (pFmt = &pRule->Get( nLvl ))->GetNumberingType() ||
/*?*/                   SVX_NUM_BITMAP == pFmt->GetNumberingType() )
/*?*/               {
/*?*/                   if( 0 == ( pFont = pFmt->GetBulletFont() ) )
/*?*/                       pFont = pDefFont;
/*?*/
/*?*/                   if( bCheck )
/*?*/                   {
/*?*/                       if( *pFont == *pDefFont )
/*?*/                           continue;
/*?*/                   }
/*?*/                   else if( *pFont == *pDefFont )
/*?*/                       bCheck = TRUE;
/*?*/
/*?*/                   _AddFontItem( rPool, SvxFontItem( pFont->GetFamily(),
/*?*/                               pFont->GetName(), pFont->GetStyleName(),
/*?*/                               pFont->GetPitch(), pFont->GetCharSet() ));
/*N*/               }
/*N*/ }

/*N*/ void Writer::PutEditEngFontsInAttrPool( BOOL bIncl_CJK_CTL )
/*N*/ {
/*N*/   if( !pImpl )
/*?*/       pImpl = new Writer_Impl( *pDoc );
/*N*/
/*N*/   SfxItemPool& rPool = pDoc->GetAttrPool();
/*N*/   if( rPool.GetSecondaryPool() )
/*N*/   {
/*N*/       _AddFontItems( rPool, EE_CHAR_FONTINFO );
/*N*/       if( bIncl_CJK_CTL )
/*N*/       {
/*N*/           _AddFontItems( rPool, EE_CHAR_FONTINFO_CJK );
/*N*/           _AddFontItems( rPool, EE_CHAR_FONTINFO_CTL );
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void Writer::PutCJKandCTLFontsInAttrPool()
//STRIP001 {
//STRIP001  if( !pImpl )
//STRIP001      pImpl = new Writer_Impl( *pDoc );
//STRIP001
//STRIP001  SfxItemPool& rPool = pDoc->GetAttrPool();
//STRIP001  _AddFontItems( rPool, RES_CHRATR_CJK_FONT );
//STRIP001  _AddFontItems( rPool, RES_CHRATR_CTL_FONT );
//STRIP001 }


/*N*/ void Writer::_AddFontItems( SfxItemPool& rPool, USHORT nW )
/*N*/ {
/*N*/   const SvxFontItem* pFont = (const SvxFontItem*)&rPool.GetDefaultItem( nW );
/*N*/   _AddFontItem( rPool, *pFont );
/*N*/
/*N*/   if( 0 != ( pFont = (const SvxFontItem*)rPool.GetPoolDefaultItem( nW )) )
/*N*/       _AddFontItem( rPool, *pFont );
/*N*/
/*N*/   USHORT nMaxItem = rPool.GetItemCount( nW );
/*N*/   for( USHORT nGet = 0; nGet < nMaxItem; ++nGet )
/*N*/       if( 0 != (pFont = (const SvxFontItem*)rPool.GetItem( nW, nGet )) )
/*N*/           _AddFontItem( rPool, *pFont );
/*N*/ }

/*N*/ void Writer::_AddFontItem( SfxItemPool& rPool, const SvxFontItem& rFont )
/*N*/ {
/*N*/   const SvxFontItem* pItem;
/*N*/   if( RES_CHRATR_FONT != rFont.Which() )
/*N*/   {
/*N*/       SvxFontItem aFont( rFont );
/*N*/       aFont.SetWhich( RES_CHRATR_FONT );
/*N*/       pItem = (SvxFontItem*)&rPool.Put( aFont );
/*N*/   }
/*N*/   else
/*?*/       pItem = (SvxFontItem*)&rPool.Put( rFont );
/*N*/
/*N*/   if( 1 < pItem->GetRefCount() )
/*N*/       rPool.Remove( *pItem );
/*N*/   else
/*N*/   {
/*N*/       if( !pImpl->pFontRemoveLst )
/*N*/           pImpl->pFontRemoveLst = new SvPtrarr( 0, 10 );
/*N*/
/*N*/       void* p = (void*)pItem;
/*N*/       pImpl->pFontRemoveLst->Insert( p, pImpl->pFontRemoveLst->Count() );
/*N*/   }
/*N*/ }

// build a bookmark table, which is sort by the node position. The
// OtherPos of the bookmarks also inserted.
//STRIP001 void Writer::CreateBookmarkTbl()
//STRIP001 {
//STRIP001  const SwBookmarks& rBkmks = pDoc->GetBookmarks();
//STRIP001  for( USHORT n = rBkmks.Count(); n; )
//STRIP001  {
//STRIP001      const SwBookmark& rBkmk = *rBkmks[ --n ];
//STRIP001      if( rBkmk.IsBookMark() )
//STRIP001          pImpl->InsertBkmk( rBkmk );
//STRIP001  }
//STRIP001 }


// search alle Bookmarks in the range and return it in the Array
//STRIP001 USHORT Writer::GetBookmarks( const SwCntntNode& rNd, xub_StrLen nStt,
//STRIP001                           xub_StrLen nEnd, SvPtrarr& rArr )
//STRIP001 {
//STRIP001  ASSERT( !rArr.Count(), "es sind noch Eintraege vorhanden" );
//STRIP001
//STRIP001  ULONG nNd = rNd.GetIndex();
//STRIP001  SvPtrarr* pArr = pImpl->pBkmkNodePos ? pImpl->pBkmkNodePos->Get( nNd ) : 0;
//STRIP001  if( pArr )
//STRIP001  {
//STRIP001      // there exist some bookmarks, search now all which is in the range
//STRIP001      if( !nStt && nEnd == rNd.Len() )
//STRIP001          // all
//STRIP001          rArr.Insert( pArr, 0 );
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT n;
//STRIP001          xub_StrLen nCntnt;
//STRIP001          for( n = 0; n < pArr->Count(); ++n )
//STRIP001          {
//STRIP001              void* p = (*pArr)[ n ];
//STRIP001              const SwBookmark& rBkmk = *(SwBookmark*)p;
//STRIP001              if( rBkmk.GetPos().nNode == nNd &&
//STRIP001                  (nCntnt = rBkmk.GetPos().nContent.GetIndex() ) >= nStt &&
//STRIP001                  nCntnt < nEnd )
//STRIP001              {
//STRIP001                  rArr.Insert( p, rArr.Count() );
//STRIP001              }
//STRIP001              else if( rBkmk.GetOtherPos() && nNd ==
//STRIP001                      rBkmk.GetOtherPos()->nNode.GetIndex() && (nCntnt =
//STRIP001                      rBkmk.GetOtherPos()->nContent.GetIndex() ) >= nStt &&
//STRIP001                      nCntnt < nEnd )
//STRIP001              {
//STRIP001                  rArr.Insert( p, rArr.Count() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return rArr.Count();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////

// Storage-spezifisches

//STRIP001 ULONG StgWriter::WriteStream()
//STRIP001 {
//STRIP001  ASSERT( !this, "Schreiben in Streams auf einem Storage?" );
//STRIP001  return ERR_SWG_WRITE_ERROR;
//STRIP001 }

/*N*/ ULONG StgWriter::Write( SwPaM& rPaM, SvStorage& rStg, const String* pFName )
/*N*/ {
/*N*/   pStrm = 0;
/*N*/   pStg = &rStg;
/*N*/   pDoc = rPaM.GetDoc();
/*N*/   pOrigFileName = pFName;
/*N*/   pImpl = new Writer_Impl( *pDoc );
/*N*/
/*N*/   // PaM kopieren, damit er veraendert werden kann
/*N*/   pCurPam = new SwPaM( *rPaM.End(), *rPaM.Start() );
/*N*/   // zum Vergleich auf den akt. Pam sichern
/*N*/   pOrigPam = &rPaM;
/*N*/
/*N*/   ULONG nRet = WriteStorage();
/*N*/
/*N*/   pStg = NULL;
/*N*/   ResetWriter();
/*N*/
/*N*/   return nRet;
/*N*/ }

