/*************************************************************************
 *
 *  $RCSfile: sw_rdswg.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:47:36 $
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
// auto strip #ifndef _SFXDOCINF_HXX //autogen
// auto strip #include <bf_sfx2/docinf.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_FONTITEM_HXX //autogen
// auto strip #include <bf_svx/fontitem.hxx>
// auto strip #endif

// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
// auto strip #ifndef _RDSWG_HXX
// auto strip #include <rdswg.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>      // Zeichen-Konversion
// auto strip #endif
// auto strip #ifndef _PAGEDESC_HXX
// auto strip #include <pagedesc.hxx>
// auto strip #endif
// auto strip #ifndef _SWGPAR_HXX
// auto strip #include <swgpar.hxx>     // SWGRD_xxx-Flags
// auto strip #endif
// auto strip #ifndef _FRMIDS_HXX
// auto strip #include <frmids.hxx>
// auto strip #endif
// auto strip #ifndef _MDIEXP_HXX
// auto strip #include <mdiexp.hxx>     // Progress
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _POOLFMT_HXX
// auto strip #include <poolfmt.hxx>
// auto strip #endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif
namespace binfilter {



//////////////////////////////////////////////////////////////////////////////

// CodeSet-Konvertierung ab Version 22:

//////////////////////////////////////////////////////////////////////////////

//STRIP001 SwSwgReader::SwSwgReader
//STRIP001  ( SwDoc *pSwDoc, const SwPaM* pSwPaM, SvStream& rStream,
//STRIP001    const String& rFileName, BOOL bNewDoc )
//STRIP001  : pDoc( pSwDoc ), r( rStream ), aFileName( rFileName ), bNew(bNewDoc),
//STRIP001  pNdOrigTxt( 0 )
//STRIP001 {
//STRIP001  nCntntCol  = 0;
//STRIP001  nErrno     = 0;
//STRIP001  pCollIdx   = NULL;
//STRIP001  pLayIdx    = NULL;
//STRIP001  pFmts      = NULL;
//STRIP001  pPageLinks = NULL;
//STRIP001  pRules     = NULL;
//STRIP001  pFrms      = NULL;
//STRIP001  pSects     = NULL;
//STRIP001  pLastSect  = NULL;
//STRIP001  pLanguages = NULL;
//STRIP001  pTables    = NULL;
//STRIP001  nColl      =
//STRIP001  nLay       =
//STRIP001  nNamedFmt  =
//STRIP001  nFrm       =
//STRIP001  nFrmSize   =
//STRIP001  nSect      =
//STRIP001  nSectSize  =
//STRIP001  nTbl       =
//STRIP001  nTblSize   =
//STRIP001  nRules     =
//STRIP001  nLang      =
//STRIP001  nLangSize  =
//STRIP001  nFmtLvl    =
//STRIP001  nStatus    = 0;
//STRIP001  nTblBoxLvl = -1;
//STRIP001  nDocStart  = r.tell();
//STRIP001  nOptions   =
//STRIP001  nFrmFlags  =
//STRIP001  nFlyLevel  =
//STRIP001  nPage1     =
//STRIP001  nFlagBits  = 0;
//STRIP001  nHelpFileId= UCHAR_MAX;
//STRIP001  nNextDoc   = 0;
//STRIP001  pPaM       = NULL;
//STRIP001  pUpper     = NULL;
//STRIP001  pMaster    = NULL;
//STRIP001  pInfo      = new SfxDocumentInfo;
//STRIP001
//STRIP001  eStartNodeType = SwNormalStartNode;
//STRIP001
//STRIP001  if( pSwPaM )
//STRIP001  {
//STRIP001      pPaM = new SwPaM( *pSwPaM->GetPoint() );
//STRIP001      SwTxtNode *pTxtNode = pPaM->GetNode()->GetTxtNode();
//STRIP001
//STRIP001      // Ist das ein SwPaM auf einen TextNode?
//STRIP001      if( !pTxtNode )
//STRIP001      {
//STRIP001          // Ist keiner, dann machen wir uns einen
//STRIP001          pTxtNode=pDoc->GetNodes().MakeTxtNode(pPaM->GetPoint()->nNode,
//STRIP001                   (SwTxtFmtColl*) pDoc->GetDfltTxtFmtColl() );
//STRIP001          // Da zeigt jetzt auch der StartIdx hin
//STRIP001          pPaM->GetPoint()->nNode-=1;
//STRIP001      }
//STRIP001      if( !bNewDoc ) nPage1 = pPaM->GetPageNum() - 1;
//STRIP001  }
//STRIP001 }

//STRIP001 SwSwgReader::~SwSwgReader()
//STRIP001 {
//STRIP001  while( pPageLinks )
//STRIP001  {
//STRIP001      PageDescLink* p = pPageLinks->pLink;
//STRIP001      delete pPageLinks;
//STRIP001      pPageLinks = p;
//STRIP001  }
//STRIP001  delete pInfo;
//STRIP001  delete pFmts;
//STRIP001  delete pFrms;
//STRIP001  delete pCollIdx;
//STRIP001  delete pLayIdx;
//STRIP001  delete pRules;
//STRIP001  delete pSects;
//STRIP001  delete pLanguages;
//STRIP001  delete pPaM;
//STRIP001  delete pTables;
//STRIP001 }

//STRIP001 BOOL SwSwgReader::CheckPasswd( const String& rPass )
//STRIP001 {
//STRIP001  return r.setpasswd( rPass ) &&
//STRIP001         BOOL( memcmp( aFile.cPasswd, r.getpasswd(), PASSWDLEN ) == 0 );
//STRIP001 }

//STRIP001 void SwSwgReader::Error( ULONG nCode )
//STRIP001 {
//STRIP001  ASSERT( !this, "Formatfehler in Datei entdeckt" );
//STRIP001  nErrno = nCode ? (nCode | ERROR_SW_READ_BASE ) : ERR_SWG_FILE_FORMAT_ERROR;
//STRIP001  r.setbad();
//STRIP001 }

//STRIP001 short SwSwgReader::LayoutIdx( short n )
//STRIP001 {
//STRIP001  return( pLayIdx && (USHORT) n < nLay ) ? pLayIdx[ n ].nActualIdx : 0;
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////

// Laden des Dateikopfes
// Vor Version 0x0011 wird nur die Signatur gelesen.

//STRIP001 void SwSwgReader::LoadFileHeader()
//STRIP001 {
//STRIP001  memset( &aFile, 0, sizeof aFile );
//STRIP001  r.seek ( 0 );
//STRIP001  r.get( &aFile.nSignature, 4 );
//STRIP001  // Eine Textbausteindatei darf auch leer sein
//STRIP001  if( r.eof() )
//STRIP001  {
//STRIP001      // in diesem Fall den Header initialisieren
//STRIP001      memset( &aFile, 0, sizeof aFile );
//STRIP001      memcpy( &aFile.nSignature, SWG_SIGNATURE, 4 );
//STRIP001      aFile.nVersion = SWG_VERSION;
//STRIP001      return;
//STRIP001  }
//STRIP001  // Die Signatur sollte schon stimmen!!!
//STRIP001  // Aber bittte nur die ersten drei Zeichen, um nicht abwaertskompatible
//STRIP001  // Versionen erkennen zu koennen.
//STRIP001  else if( memcmp( ( const void*) &aFile.nSignature, SWG_SIGNATURE, 3 ) )
//STRIP001  {
//STRIP001      Error(); return;
//STRIP001  }
//STRIP001
//STRIP001  r.long4();
//STRIP001  r >> aFile.nVersion
//STRIP001    >> aFile.nFlags
//STRIP001    >> aFile.nFree1
//STRIP001    >> aFile.nDocInfo;
//STRIP001  r.get( aFile.cPasswd, 16 );
//STRIP001  r.long3();
//STRIP001  // Passwort in Stream eintragen
//STRIP001  if( aFile.nFlags & SWGF_HAS_PASSWD )
//STRIP001      r.copypasswd( aFile.cPasswd );
//STRIP001 //MA Erstmal abklemmen!!!!!!!!!!!!!!!!!!!!!!
//STRIP001 //JP 12.09.96: Bug 31264 - zum PageDesc Abpruefen brauchen wir das Flag aber
//STRIP001 //MIB: there is no flag to not load the layout any longer, it is loaded always.
//STRIP001 //   aFile.nFlags |= SWGF_NO_FRAMES;
//STRIP001  r.seek ( 0 );
//STRIP001  LoadDocInfo( *pInfo );
//STRIP001  r.seek ( 0x20 );
//STRIP001  if( pDoc )
//STRIP001  {
//STRIP001      if( aFile.nFlags & SWGF_HAS_PGNUMS ) pDoc->SetPageNums();
//STRIP001  }
//STRIP001 }

// Laden der Header-Informationen
// Ab Version 0x0011 ist der Header Bestandtail eines SWG_DOCUMENT-Records.
// Die Position zeigt auf den Beginn der Infos, also entweder hinter die
// Version (s.o.) oder auf den Beginn des SWG_DOCUMENT-Records.

//STRIP001 void SwSwgReader::LoadHeader()
//STRIP001 {
//STRIP001  memset( &aHdr, 0, sizeof aHdr );
//STRIP001  r.next();
//STRIP001  // Evtl. den Dynamischen DocInfo-Record auch skippen
//STRIP001  nNextDoc = r.getskip();
//STRIP001  // Achtung: Es gibt tatsaechlich Docs, die hier was unsinniges haben!
//STRIP001  long siz = r.filesize();
//STRIP001  if( nNextDoc < 0 || nNextDoc > siz )
//STRIP001      nNextDoc = siz;
//STRIP001  r.skip();
//STRIP001  if( r.next() == SWG_DYNDOCINFO )
//STRIP001      nNextDoc = r.getskip();
//STRIP001  r.seek( nDocStart );
//STRIP001  r.next();
//STRIP001  r >> aHdr.nFlags
//STRIP001    >> aHdr.nVersion;
//STRIP001  r.get( aHdr.cAttrTab, 8 );
//STRIP001  r.get( aHdr.cAttrSiz, 8 );
//STRIP001  r.long4();
//STRIP001  r >> aHdr.cCodeSet
//STRIP001    >> aHdr.nNumRules
//STRIP001    >> aHdr.nDocVersion
//STRIP001    >> aHdr.cGUIType
//STRIP001    >> aHdr.cReserved[ 0 ]
//STRIP001    >> aHdr.cReserved[ 1 ]
//STRIP001    >> aHdr.cReserved[ 2 ]
//STRIP001    >> aHdr.nDocInfoOffset
//STRIP001    >> aHdr.nLayoutOffset
//STRIP001    >> aHdr.nDate
//STRIP001    >> aHdr.nTime;
//STRIP001  r.long3();
//STRIP001  if( aHdr.nDocInfoOffset ) aHdr.nDocInfoOffset += nDocStart;
//STRIP001  if( aHdr.nLayoutOffset )  aHdr.nLayoutOffset  += nDocStart;
//STRIP001  nRecStart = r.tell();
//STRIP001
//STRIP001  // Hot fix fuer Tesxtbausteine, wo der DocInfo-Ptr im Dateikopf
//STRIP001  // verlorengegangen ist (Bugid 4955): Ptr aus Dokument-Hdr
//STRIP001  // restaurieren
//STRIP001  if( !aFile.nDocInfo ) aFile.nDocInfo = aHdr.nDocInfoOffset + 8;
//STRIP001 }

// Einlesen eines Strings mit Check und Konvertierung

//STRIP001 String SwSwgReader::GetText( BOOL bReq )
//STRIP001 {
//STRIP001  String aRes;
//STRIP001  if( r.next() != SWG_TEXT )
//STRIP001  {
//STRIP001      if( bReq )
//STRIP001          Error();
//STRIP001      else
//STRIP001          r.undonext();
//STRIP001  } else
//STRIP001      aRes = ParseText();
//STRIP001  return aRes;
//STRIP001 }

//STRIP001 ByteString SwSwgReader::GetAsciiText( BOOL bReq )
//STRIP001 {
//STRIP001  ByteString aRes;
//STRIP001  if( r.next() != SWG_TEXT )
//STRIP001  {
//STRIP001      if( bReq )
//STRIP001          Error();
//STRIP001      else
//STRIP001          r.undonext();
//STRIP001  } else
//STRIP001      aRes = r.text();
//STRIP001  return aRes;
//STRIP001 }

// Einlesen und Konvertierung eines Strings in den Native-Zeichensatz
// Der Record-Header SWG_TEXT ist bereits eingelesen

//STRIP001 String SwSwgReader::ParseText()
//STRIP001 {
//STRIP001  String aOrig( r.text(), (rtl_TextEncoding)aHdr.cCodeSet );
//STRIP001  return aOrig;
//STRIP001 }

/*void SwSwgReader::ConvertLineTerminators( String& rText, GUIType eFrom )
{

    GUIType eTo = System::GetGUIType();
    if( eFrom != GUI_DONTKNOW && eFrom != eTo )
    {
        String aFrom, aTo;
        short nFrom = 1, nTo = 1;
        switch( eFrom )
        {
            case GUI_WINDOWS:
            case GUI_WINDOWSNT:
            case GUI_PM:        aFrom = "\x0D\x0A"; nFrom = 2; break;
            case GUI_MAC:       aFrom = "\x0D"; break;
            default:            aFrom = "\x0A";
        }
        switch( eTo )
        {
            case GUI_WINDOWS:
            case GUI_WINDOWSNT:
            case GUI_PM:        aTo = "\x0D\x0A"; nTo = 2; break;
            case GUI_MAC:       aTo = "\x0D"; break;
            default:            aTo = "\x0A";
        }
        USHORT nPos = 0;
        for( ;; )
        {
            nPos = rText.Search( aFrom, nPos );
            if( nPos == STRING_NOTFOUND ) break;
            rText.Erase( nPos, nFrom );
            rText.Insert( aTo, nPos );
            nPos += nTo;
        }
    }
}*/

/////////////////////////////////////////////////////////////////////////////

//STRIP001 void _ReadFrm_Rect( swistream& r )
//STRIP001 {
//STRIP001  BYTE sizes;
//STRIP001  r >> sizes;
//STRIP001  int nSkip = 0;
//STRIP001  for( USHORT i = 0; i < 4; i++, sizes <<= 2 )
//STRIP001  {
//STRIP001      switch( sizes & 0xC0 )
//STRIP001      {
//STRIP001      case 0x40:
//STRIP001          nSkip += 2;
//STRIP001          break;
//STRIP001      case 0x80:
//STRIP001          nSkip += 3;
//STRIP001          break;
//STRIP001      case 0xC0:
//STRIP001          nSkip += 4;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  r.seek( r.tell() + nSkip );
//STRIP001 }

//STRIP001 void _ReadFrm_LayFrm( swistream& r, USHORT nVersion )
//STRIP001 {
//STRIP001  BYTE nB, nFrmFlag;
//STRIP001  USHORT nU;
//STRIP001
//STRIP001  // Byte vom Frm
//STRIP001  r >> nFrmFlag >> nB;
//STRIP001  if( nVersion >= FRMVER_EXTINFO && ( nB & 0x80 ) )
//STRIP001      r >> nB;
//STRIP001  if( nVersion >= FRMVER_EXTINFO )
//STRIP001      // Eventuelle Zusatz-Bits entfernen
//STRIP001      while( nB & 0x80 ) r >> nB;
//STRIP001
//STRIP001  // Frame-Rect einlesen (mit Addieren des Upper-Starts, falls vorhanden)
//STRIP001  _ReadFrm_Rect( r );
//STRIP001  if( nFrmFlag & FRMF_PRINT )
//STRIP001      _ReadFrm_Rect( r );
//STRIP001
//STRIP001  // Dann Frame-ID eintragen
//STRIP001  // Version 1 hatte FRMF_HASID nicht bei FRMF_HASFOLLOW gesetzt
//STRIP001  if( nFrmFlag & ( FRMF_HASFOLLOW | FRMF_HASID ) )
//STRIP001      r >> nU;
//STRIP001  if( nFrmFlag & FRMF_ISFOLLOW )
//STRIP001      r >> nU;
//STRIP001
//STRIP001  // Byte vom LayoutFrm
//STRIP001  r >> nU;
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Der Returnwert ist der errno-Fehlercode

//STRIP001 ULONG SwSwgReader::Read( USHORT nOpt )
//STRIP001 {
//STRIP001  nOptions = nOpt;
//STRIP001  if( !pPaM
//STRIP001   || ( aFile.nVersion < SWG_VER_PORTGRF )
//STRIP001   || ( aFile.nFlags & SWGF_BAD_FILE ) )
//STRIP001      return ERR_SWG_READ_ERROR;
//STRIP001
//STRIP001  nDocStart  = r.tell();
//STRIP001
//STRIP001  nErrno = 0;
//STRIP001  BOOL bUndo = pDoc->DoesUndo();
//STRIP001  // Kein Undo bei neuem Dokument!
//STRIP001  USHORT nInsFirstPara = 0;
//STRIP001  if( bNew )
//STRIP001      pDoc->DoUndo( FALSE );
//STRIP001  else
//STRIP001  {
//STRIP001      SwTxtNode *pTxtNode=pDoc->GetNodes()[pPaM->GetPoint()->nNode]->GetTxtNode();
//STRIP001      // Ist das ein SwPaM auf einen TextNode?
//STRIP001      if( pTxtNode && pTxtNode->GetTxt().Len() )
//STRIP001          nInsFirstPara = 1;
//STRIP001  }
//STRIP001
//STRIP001  LoadHeader();
//STRIP001
//STRIP001  // Den Vorlagen-Namen aus der DocInfo am Doc registrieren,
//STRIP001  // falls ueberhaupt einer da ist
//STRIP001  if( pInfo->GetTemplateName().Len() )
//STRIP001      nHelpFileId = pDoc->SetDocPattern( pInfo->GetTemplateName() );
//STRIP001
//STRIP001  // Es wird angenommen, dass das Layout 5% der Ladezeit belegt.
//STRIP001  long nEnd = aHdr.nLayoutOffset ? aHdr.nLayoutOffset : nNextDoc;
//STRIP001  nEnd = ( nEnd * 105 ) / 100;
//STRIP001  ::StartProgress( STR_STATSTR_SWGREAD, nDocStart, nEnd, pDoc->GetDocShell() );
//STRIP001
//STRIP001  // Default-Collection registrieren
//STRIP001  SwTxtFmtColl* pColl = pDoc->GetTxtCollFromPool( RES_POOLCOLL_STANDARD );
//STRIP001  pColl->nFmtId = IDX_COLLECTION + 0;
//STRIP001  RegisterFmt( *pColl );
//STRIP001
//STRIP001  // Erst einmal die Link-Optionen weg
//STRIP001  nOptions &= 0xF0FF;
//STRIP001
//STRIP001  // Auf gehts:
//STRIP001  BOOL bDone = FALSE;
//STRIP001  BOOL bNode1 = TRUE;
//STRIP001  r.next();
//STRIP001  while( !bDone && r.good() && !IsError( nErrno ) && ( r.tell() < nNextDoc ) )
//STRIP001  {
//STRIP001      BYTE ch = r.cur();
//STRIP001      switch( (int) ch ) {
//STRIP001          case SWG_EOF:
//STRIP001              if( ( nOptions == SWGRD_NORMAL )
//STRIP001               && ( r.next() == (BYTE) SWG_DOCINFO ) )
//STRIP001                  InDocInfo();
//STRIP001              bDone = TRUE; break;
//STRIP001          case SWG_DOCINFO:
//STRIP001              InDocInfo(); r.next(); break;
//STRIP001          case SWG_NAMEDFMTS:
//STRIP001              InNamedFmts( nOptions );
//STRIP001              break;
//STRIP001          case SWG_JOBSETUP:
//STRIP001          case SWG_NEWJOBSETUP:
//STRIP001              if( nOptions == SWGRD_NORMAL ) InJobSetup();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_OUTLINE:
//STRIP001              if( nOptions == SWGRD_NORMAL )
//STRIP001                  InOutlineRule();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_NUMRULES:
//STRIP001              if( nOptions == SWGRD_NORMAL )
//STRIP001                  InTxtNumRule();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_MACROTBL:
//STRIP001              if( nOptions & SWGRD_MACROS )
//STRIP001              {
//STRIP001                  InGlobalMacroTbl();
//STRIP001                  if( nOptions == SWGRD_MACROS ) bDone = TRUE;
//STRIP001              } else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_LAYOUT:
//STRIP001              if( nOptions & SWGRD_PAGEFMTS )
//STRIP001              {
//STRIP001                  InPageDescs();
//STRIP001                  if( nOptions == SWGRD_PAGEFMTS ) bDone = TRUE;
//STRIP001              } else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_DFLTFMTS:
//STRIP001              if( nOptions & SWGRD_PARAFMTS ) InDfltFmts();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_FIELDTYPES:
//STRIP001              if( nOptions == SWGRD_NORMAL ) InFieldTypes();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_COLLECTIONS:
//STRIP001              if( nOptions & SWGRD_PARAFMTS ) InTxtFmtColls();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_FLYFRAMES:
//STRIP001              if( nOptions == SWGRD_NORMAL ) InFlyFrames( NULL );
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_FOOTINFO:
//STRIP001              // globale Fussnoten-Info
//STRIP001              if( nOptions == SWGRD_NORMAL ) InFtnInfo();
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_CONTENTS:
//STRIP001              if( nOptions == SWGRD_NORMAL )
//STRIP001                  InContents( bNode1, FALSE, nInsFirstPara );
//STRIP001              else
//STRIP001                  r.skipnext();
//STRIP001              nInsFirstPara = 0; bNode1 = FALSE;
//STRIP001              break;
//STRIP001          case SWG_FRAMES:
//STRIP001
//STRIP001              if( !( aFile.nFlags & SWGF_NO_FRAMES )
//STRIP001                  && bNew && ( nOptions == SWGRD_NORMAL ) )
//STRIP001              {
//STRIP001                  // Offene Seitenbeschreibungen in Formaten aufloesen
//STRIP001                  // (falls noch nicht geschehen)
//STRIP001                  ResolvePageDescLinks();
//STRIP001
//STRIP001                  // Teste ob das Layout auf der 1. Seite einen anderen
//STRIP001                  // PageDesc definiert hat das Doc. Dann nehme den aus
//STRIP001                  // dem Layout! Bug 31264
//STRIP001                  SwNodeIndex aIdx( pDoc->GetNodes().GetEndOfExtras(), 1 );
//STRIP001                  SwCntntNode* pCNd = pDoc->GetNodes().GoNext( &aIdx );
//STRIP001                  if( pCNd && SFX_ITEM_SET != pCNd->GetSwAttrSet().
//STRIP001                      GetItemState(RES_PAGEDESC) && !pCNd->FindTableNode())
//STRIP001                  {
//STRIP001                      // es ist keiner gesetzt, dann muss das Layout auch
//STRIP001                      // der Meinung sein, den Standard zu benutzen!
//STRIP001                      USHORT nVersion;
//STRIP001                      r >> nVersion;
//STRIP001                      if( nVersion >= FRMVER_NEWFLY )
//STRIP001                      {
//STRIP001                          USHORT nU;
//STRIP001                          BYTE nId;
//STRIP001                          r >> nId;
//STRIP001                          if( FRMID_ROOT == nId )
//STRIP001                          {
//STRIP001                              _ReadFrm_LayFrm( r, nVersion );
//STRIP001                              r >> nId
//STRIP001                                >> nU;    // in nU sollte die Seiten stehen!
//STRIP001                              if( nU )
//STRIP001                              {
//STRIP001                                  r >> nId;
//STRIP001                                  if( FRMID_PAGE == nId )
//STRIP001                                  {
//STRIP001                                      _ReadFrm_LayFrm( r, nVersion );
//STRIP001                                      r >> nId >> nU;
//STRIP001                                      // in nU steht der gesuchte PageDesc!
//STRIP001                                      SwPageDesc* pDesc = &FindPageDesc( nU );
//STRIP001                                      if( pDesc && pDesc != &pDoc->_GetPageDesc( 0 ) )
//STRIP001                                      {
//STRIP001                                          // dann am Node setzen!!
//STRIP001                                          pCNd->SetAttr( SwFmtPageDesc( pDesc ) );
//STRIP001                                          ASSERT( !this, "LayoutPageDesc am Doc setzen" );
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_COMMENT:
//STRIP001              InComment(); break;
//STRIP001          default:
//STRIP001              r.skipnext();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Offene Seitenbeschreibungen in Formaten aufloesen
//STRIP001  // (falls noch nicht geschehen)
//STRIP001  ResolvePageDescLinks();
//STRIP001  // Bug 9714: Der CharSet an den Fonts muss geaendert werden, wenn
//STRIP001  // es der globale CharSet ist
//STRIP001  USHORT nMaxItems = pDoc->GetAttrPool().GetItemCount( RES_CHRATR_FONT );
//STRIP001  rtl_TextEncoding eSysCharSet = gsl_getSystemTextEncoding();
//STRIP001  SvxFontItem* pItem;
//STRIP001  for( USHORT n = 0; n < nMaxItems; ++n )
//STRIP001  {
//STRIP001      pItem = (SvxFontItem*) pDoc->GetAttrPool().GetItem( RES_CHRATR_FONT, n );
//STRIP001      if( pItem && pItem->GetCharSet() == (rtl_TextEncoding)aHdr.cCodeSet )
//STRIP001          pItem->GetCharSet() = eSysCharSet;
//STRIP001  }
//STRIP001  ClearFmtIds();
//STRIP001  pDoc->DoUndo( bUndo );
//STRIP001  if( !IsError( nErrno ) )
//STRIP001  {
//STRIP001      pDoc->SetGlossDoc( BOOL( ( aFile.nFlags & SWGF_HAS_BLOCKS ) != 0 ) );
//STRIP001      if( aFile.nVersion > SWG_VERSION )
//STRIP001          nErrno = WARN_SWG_FEATURES_LOST | WARN_SW_READ_BASE;
//STRIP001  }
//STRIP001
//STRIP001  EndProgress( pDoc->GetDocShell() );
//STRIP001
//STRIP001  // Expr-Felder in Shared-Formaten?
//STRIP001 //   if( nStatus & SWGSTAT_UPDATEEXPR )
//STRIP001 //       pDoc->SetUpdateExpFldStat();
//STRIP001  if( !IsError( nErrno ))
//STRIP001  {
//STRIP001      if( nOptions == SWGRD_NORMAL )
//STRIP001      {
//STRIP001          // Neues Doc gelesen
//STRIP001          if( bNew )
//STRIP001              pDoc->SetLoaded( TRUE );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Nachladen von Vorlagen etc.
//STRIP001
//STRIP001          // falls wir die OutlineLevel veraendert haben (Volagen geladen),
//STRIP001          // dann muss am Doc ein Update auf die neuen Nummern erfolgen !!
//STRIP001          if( (SWGRD_FORCE & nOptions) && pDoc->GetOutlineNumRule() )
//STRIP001              pDoc->SetOutlineNumRule( *pDoc->GetOutlineNumRule() );
//STRIP001
//STRIP001          pDoc->SetModified();
//STRIP001      }
//STRIP001  }
//STRIP001  if( bNew )
//STRIP001      pDoc->SetInfo( *pInfo );
//STRIP001  pDoc->SetNewDoc( FALSE );
//STRIP001  return nErrno;
//STRIP001 }

// Einlesen einer Textblock-Datei
// Hier wird alles ausser dem Inhalt eingelesen.
// Der Inhalt wird nach SWG_TEXTBLOCK-Records durchsucht.
// Dabei werden in allen Textbloecken die Referenzzaehler fuer Formate
// inkrementiert.

// Ansonsten ist die Funktion analog zu Read().

//STRIP001 ULONG SwSwgReader::Scan( SwBlockNames* pNames )
//STRIP001 {
//STRIP001  if( ( aFile.nVersion < SWG_VER_PORTGRF )
//STRIP001   || ( aFile.nFlags & SWGF_BAD_FILE ) )
//STRIP001      return ERR_SWG_READ_ERROR;
//STRIP001  nDocStart = r.tell();
//STRIP001  nErrno = 0;
//STRIP001
//STRIP001  LoadHeader();
//STRIP001
//STRIP001  // Default-Collection registrieren
//STRIP001  SwTxtFmtColl* pColl = (*pDoc->GetTxtFmtColls())[ 0 ];
//STRIP001  pColl->nFmtId = IDX_COLLECTION + 0;
//STRIP001  RegisterFmt( *pColl );
//STRIP001
//STRIP001  // Auf gehts:
//STRIP001  BOOL bDone = FALSE;
//STRIP001  r.next();
//STRIP001  while( !bDone && r.good() && !IsError( nErrno ) && ( r.tell() < nNextDoc ) )
//STRIP001  {
//STRIP001      BYTE ch = r.cur();
//STRIP001      switch( (int) ch )
//STRIP001      {
//STRIP001          case SWG_EOF:           bDone = TRUE; break;
//STRIP001          case SWG_DOCINFO:       InDocInfo(); r.next(); break;
//STRIP001          case SWG_NAMEDFMTS:     InNamedFmts( SWGRD_NORMAL ); break;
//STRIP001          case SWG_OUTLINE:       InOutlineRule(); break;
//STRIP001          case SWG_MACROTBL:      InGlobalMacroTbl(); break;
//STRIP001          case SWG_LAYOUT:        InPageDescs(); break;
//STRIP001          case SWG_DFLTFMTS:      InDfltFmts(); break;
//STRIP001          case SWG_FIELDTYPES:    InFieldTypes(); break;
//STRIP001          case SWG_COLLECTIONS:   InTxtFmtColls(); break;
//STRIP001          case SWG_FOOTINFO:      InFtnInfo(); break;
//STRIP001          case SWG_CONTENTS:      ScanContents( pNames ); break;
//STRIP001          default:                r.skipnext();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  r.skip( nNextDoc );
//STRIP001  // Offene Seitenbeschreibungen in Formaten aufloesen
//STRIP001  // (falls noch nicht geschehen)
//STRIP001  ResolvePageDescLinks();
//STRIP001  ClearFmtIds();
//STRIP001  return nErrno;
//STRIP001 }



}
