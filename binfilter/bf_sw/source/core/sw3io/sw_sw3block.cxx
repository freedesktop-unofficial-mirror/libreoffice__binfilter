/*************************************************************************
 *
 *  $RCSfile: sw_sw3block.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:41:46 $
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

// auto strip #ifndef _VCL_VCLENUM_HXX
// auto strip #include <vcl/vclenum.hxx>
// auto strip #endif
// auto strip #ifndef _SV_FONT_HXX //autogen
// auto strip #include <vcl/font.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_TENCCVT_HXX //autogen
// auto strip #include <tools/tenccvt.hxx>
// auto strip #endif
// auto strip #ifndef _SVSTOR_HXX //autogen
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
// auto strip #ifndef _SOT_STORINFO_HXX //autogen
// auto strip #include <sot/storinfo.hxx>
// auto strip #endif
// auto strip #ifndef _SO_CLSIDS_HXX
// auto strip #include <so3/clsids.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_CHARCLASS_HXX
// auto strip #include <unotools/charclass.hxx>
// auto strip #endif
// auto strip #ifndef _SFXMACITEM_HXX
// auto strip #include <svtools/macitem.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _SW3IO_HXX
// auto strip #include <sw3io.hxx>
// auto strip #endif
#ifndef _SW3IMP_HXX
#include <sw3imp.hxx>
#endif
// auto strip #ifndef _SWBLOCKS_HXX
// auto strip #include <swblocks.hxx>
// auto strip #endif
// auto strip #ifndef _DOCSH_HXX
// auto strip #include <docsh.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _SHELLIO_HXX
// auto strip #include <shellio.hxx>
// auto strip #endif
// auto strip #ifndef _POOLFMT_HXX
// auto strip #include <poolfmt.hxx>
// auto strip #endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
namespace binfilter {

#define STREAM_STGREAD  ( STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE )
#define STREAM_STGWRITE ( STREAM_READ | STREAM_WRITE | STREAM_SHARE_DENYWRITE )

sal_Char __FAR_DATA N_BLOCKINFO[] = "AutotextInfo";

//STRIP001 void Sw3IoImp::InitBlockMode( SvStorage* pStg, BOOL bRdWr )
//STRIP001 {
//STRIP001  bBlock = TRUE;
//STRIP001  pBlkRoot = pStg;
//STRIP001  pRoot.Clear();
//STRIP001 }
//STRIP001
//STRIP001 void Sw3IoImp::ResetBlockMode()
//STRIP001 {
//STRIP001  bBlock = FALSE;
//STRIP001  pRoot.Clear();
//STRIP001  pBlkRoot.Clear();
//STRIP001 }

/*************************************************************************
*
*   Enumeration aller Textbausteine
*
*************************************************************************/

// Das Directory enthaelt die Kurz- und Langnamen der Bausteine. Die
// Bausteine selbst sind unter ihrem Kurznamen in eigenen Streams
// abgelegt. Die Namen selbst sind nach folgender Konvention aufgebaut:
// 1. Zeichen: #
// ! == 0x01
// / == 0x0F
// \ == 0x0C
// : == 0x0A
// . == 0x0E

//STRIP001 void lcl_EncryptBlockName( String& rName )
//STRIP001 {
//STRIP001  rName.Insert( '#', 0 );
//STRIP001  xub_StrLen nPos = 1;
//STRIP001  sal_Unicode pDelims[] = { '!', '/', ':', '.', '\\', 0 };
//STRIP001  while( STRING_NOTFOUND != ( nPos = rName.SearchChar( pDelims, nPos )))
//STRIP001  {
//STRIP001      rName.SetChar( nPos, rName.GetChar( nPos ) & 0x0f );
//STRIP001      ++nPos;
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void lcl_DecryptBlockName( String& rName )
//STRIP001 {
//STRIP001  if( '#' == rName.GetChar( 0 ) )
//STRIP001  {
//STRIP001      rName.Erase( 0, 1 );
//STRIP001
//STRIP001      sal_Unicode c;
//STRIP001      xub_StrLen nLen = rName.Len();
//STRIP001      while( nLen-- )
//STRIP001      {
//STRIP001          switch( rName.GetChar( nLen ) )
//STRIP001          {
//STRIP001          case 0x01:  c = '!';    break;
//STRIP001          case 0x0A:  c = ':';    break;
//STRIP001          case 0x0C:  c = '\\';   break;
//STRIP001          case 0x0E:  c = '.';    break;
//STRIP001          case 0x0F:  c = '/';    break;
//STRIP001          default:    c = 0;      break;
//STRIP001          }
//STRIP001          if( c )
//STRIP001              rName.SetChar( nLen, c );
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void Sw3IoImp::DetectAndSetFFVersion( SvStorage *pRoot )
//STRIP001 {
//STRIP001  ULONG nClipId = pRoot->GetFormat();
//STRIP001  ASSERT( SOT_FORMATSTR_ID_STARWRITER_30 == nClipId ||
//STRIP001          SOT_FORMATSTR_ID_STARWRITER_40 == nClipId ||
//STRIP001          SOT_FORMATSTR_ID_STARWRITER_50 == nClipId,
//STRIP001          "Textbaustein-Storage hat unzulaessige Clipboard-Id" );
//STRIP001
//STRIP001  if( SOT_FORMATSTR_ID_STARWRITER_30 == nClipId )
//STRIP001  {
//STRIP001      pRoot->SetVersion( SOFFICE_FILEFORMAT_31 );
//STRIP001  }
//STRIP001  else if( SOT_FORMATSTR_ID_STARWRITER_40 == nClipId ||
//STRIP001           SOT_FORMATSTR_ID_STARWRITERWEB_40 == nClipId ||
//STRIP001           SOT_FORMATSTR_ID_STARWRITERGLOB_40 == nClipId )
//STRIP001  {
//STRIP001      pRoot->SetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  }
//STRIP001  else if( SOT_FORMATSTR_ID_STARWRITER_50 == nClipId ||
//STRIP001           SOT_FORMATSTR_ID_STARWRITERWEB_50 == nClipId ||
//STRIP001           SOT_FORMATSTR_ID_STARWRITERGLOB_50 == nClipId )
//STRIP001  {
//STRIP001      pRoot->SetVersion( SOFFICE_FILEFORMAT_50 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ASSERT( !this, "Textbaustein hat unbekannte Clipboard-Id" );
//STRIP001      // In der 4.0-Auslieferung gab es eine Standard-Bau mit dieser
//STRIP001      // recht merkwuerdigen Clipboard-Id (geschrieben mit einer 332e)
//STRIP001      // (bug #49310#)
//STRIP001      SvGlobalName aWhatEver( 0xC24CC4E0, 0x73DF, 0x101B, 0x80, 0x4C,
//STRIP001                              0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD );
//STRIP001      if( aWhatEver == pRoot->GetClassName() )
//STRIP001      {
//STRIP001          ASSERT( !this, "Textbaustein hat merkwuerdigen Classname" );
//STRIP001          pRoot->SetVersion( SOFFICE_FILEFORMAT_31 );
//STRIP001      }
//STRIP001      else
//STRIP001          pRoot->SetVersion( SOFFICE_FILEFORMAT_50 );
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3IoImp::FirstBlockName( String& rShort, String& rLong )
//STRIP001 {
//STRIP001  delete pBlkList;
//STRIP001
//STRIP001  // This is just an initialization where we need any valid 1 byte
//STRIP001  // text encoding. It is used only if there are errors reading
//STRIP001  // at least the first text block. We assume the encoding that is used
//STRIP001  // for writing then, allthough this most probably is wrong.
//STRIP001  eBlkDirSet = GetSOStoreTextEncoding( gsl_getSystemTextEncoding(),
//STRIP001                                       SOFFICE_FILEFORMAT_50 );
//STRIP001
//STRIP001  if( pBlkRoot->IsStream( N_BLOCKDIR ) )
//STRIP001  {
//STRIP001      pBlkDir = pBlkRoot->OpenStream( N_BLOCKDIR, STREAM_STGREAD );
//STRIP001      if( pBlkDir->GetError() != SVSTREAM_OK )
//STRIP001      {
//STRIP001          pBlkDir.Clear();
//STRIP001          pBlkRoot->Remove( N_BLOCKDIR );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pBlkDir->SetBufferSize( SW3_BSR_BLKDIR );
//STRIP001
//STRIP001          String aDummy;
//STRIP001          InString( *pBlkDir, aDummy );
//STRIP001          if( aDummy.Len() )
//STRIP001          {
//STRIP001              // alter Stream (ohne Header)
//STRIP001              // Char-Set aus erstem Dokument holen
//STRIP001              SvStorageStreamRef pSaveBlkDir( pBlkDir );
//STRIP001              pBlkDir.Clear();
//STRIP001
//STRIP001              pBlkList = new SvStorageInfoList;
//STRIP001              nCurBlk  = -1;
//STRIP001              pBlkRoot->FillInfoList( pBlkList );
//STRIP001
//STRIP001              String aShort, aLong;
//STRIP001              if ( !NextBlockName( aShort, aLong ) )
//STRIP001                  eBlkDirSet = eSrcSet;
//STRIP001
//STRIP001              delete pBlkList; pBlkList = NULL;
//STRIP001              pBlkDir = pSaveBlkDir;
//STRIP001              pBlkDir->Seek( 0L );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // neuer Stream (mit Header)
//STRIP001              ULONG nOld = pBlkDir->Tell();
//STRIP001
//STRIP001              BYTE cLen, cSet;
//STRIP001              USHORT nVersion;
//STRIP001              *pBlkDir >> cLen >> nVersion >> cSet;
//STRIP001              eBlkDirSet = GetSOLoadTextEncoding( (rtl_TextEncoding)cSet,
//STRIP001                                                  SOFFICE_FILEFORMAT_50 );
//STRIP001
//STRIP001              ULONG nNew = pBlkDir->Tell();
//STRIP001              nOld += cLen;
//STRIP001              if( nOld != nNew )
//STRIP001                  pBlkDir->Seek( nOld );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pBlkList = new SvStorageInfoList;
//STRIP001      nCurBlk  = -1;
//STRIP001      pBlkRoot->FillInfoList( pBlkList );
//STRIP001  }
//STRIP001  return NextBlockName( rShort, rLong );
//STRIP001 }

// Der Fehlercode wird zurueckgeliefert. Das Ende der Liste
// wird durch einen leeren Short-Namen angezeigt.

//STRIP001 ULONG Sw3IoImp::NextBlockName( String& rShort, String& rLong )
//STRIP001 {
//STRIP001  ULONG n = 0;
//STRIP001  rShort.Erase();
//STRIP001  if( pBlkDir )
//STRIP001  {
//STRIP001      pBlkDir->ReadByteString( rShort, eBlkDirSet );
//STRIP001      pBlkDir->ReadByteString( rLong, eBlkDirSet );
//STRIP001      if( pBlkDir->IsEof() || pBlkDir->GetError() != SVSTREAM_OK )
//STRIP001      {
//STRIP001          n = ( pBlkDir->GetError() == SVSTREAM_OK )
//STRIP001            ? 0 : ERR_SWG_READ_ERROR;
//STRIP001          rShort.Erase();
//STRIP001          pBlkDir->SetBufferSize( 0 );
//STRIP001          pBlkDir.Clear();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !pBlkList )
//STRIP001          return 0;
//STRIP001      while( ++nCurBlk < (short) pBlkList->Count() )
//STRIP001      {
//STRIP001          SvStorageInfo& rInfo = pBlkList->GetObject( nCurBlk );
//STRIP001          String aShort = rInfo.GetName();
//STRIP001          if( '#' == aShort.GetChar( 0 ) )
//STRIP001          {
//STRIP001              Reset2();
//STRIP001              // Langnamen einlesen
//STRIP001              if( rInfo.IsStream() )
//STRIP001              {
//STRIP001                  // Kurzform!
//STRIP001                  pContents = pBlkRoot->OpenStream( aShort, STREAM_STGREAD );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pRoot = pBlkRoot->OpenStorage( aShort, STREAM_STGREAD );
//STRIP001
//STRIP001                  if( pRoot.Is() )
//STRIP001                      DetectAndSetFFVersion( pRoot );
//STRIP001
//STRIP001                  pContents = pRoot->OpenStream( N_DOC, STREAM_STGREAD );
//STRIP001              }
//STRIP001              pContents->SetBufferSize( SW3_BSR_CONTENTS_HEADER );
//STRIP001              if( pContents->GetError() == SVSTREAM_OK )
//STRIP001              {
//STRIP001                  pStrm = pContents;
//STRIP001                  bOut = FALSE;
//STRIP001                  InHeader();
//STRIP001                  n = nRes;
//STRIP001                  if( n )
//STRIP001                      break;
//STRIP001              }
//STRIP001              pStrm = NULL;
//STRIP001              pContents->SetBufferSize( 0 );
//STRIP001              pContents.Clear();
//STRIP001              pRoot.Clear();
//STRIP001              rShort = aShort;
//STRIP001              lcl_DecryptBlockName( rShort );
//STRIP001              rLong = aBlkName;
//STRIP001              return n;
//STRIP001          }
//STRIP001      }
//STRIP001      delete pBlkList; pBlkList = NULL;
//STRIP001  }
//STRIP001  return n;
//STRIP001 }

/*************************************************************************
*
*   I/O einzelner Textbausteine
*
*************************************************************************/

//STRIP001 ULONG Sw3IoImp::GetBlock( const String& rShort, sal_Bool bConvertMode )
//STRIP001 {
//STRIP001  ULONG n = 0;
//STRIP001  String aName ( rShort );
//STRIP001  lcl_EncryptBlockName( aName );
//STRIP001  if( pBlkRoot->IsStream( aName ) )
//STRIP001  {
//STRIP001      // Kurzform!
//STRIP001      ByteString aText;
//STRIP001      pContents = pBlkRoot->OpenStream( aName, STREAM_STGREAD );
//STRIP001      pContents->SetBufferSize( SW3_BSR_CONTENTS_FLAT );
//STRIP001      pStrm = pContents;
//STRIP001      bOut = FALSE;
//STRIP001      InHeader();
//STRIP001      OpenRec( SWG_BLOCKTEXT );
//STRIP001      pStrm->ReadByteString( aText );
//STRIP001      CloseRec( SWG_BLOCKTEXT );
//STRIP001      if( pBlkRoot->GetError() != SVSTREAM_OK
//STRIP001       || pStrm->GetError() != SVSTREAM_OK )
//STRIP001          n = ERR_SWG_READ_ERROR;
//STRIP001      else
//STRIP001          n = IsError( nRes ) ? nRes : 0;
//STRIP001      pStrm = NULL;
//STRIP001      pContents->SetBufferSize( 0 );
//STRIP001      pContents.Clear();
//STRIP001      if( !n )
//STRIP001          MakeBlockText( aText );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SvStorageRef refRoot = pBlkRoot->OpenStorage( aName, STREAM_STGREAD );
//STRIP001
//STRIP001      // Fuer 3.1-Textbausteine muss die FF-Version noch umgeschossen
//STRIP001      // werden.
//STRIP001      if( refRoot.Is() )
//STRIP001          DetectAndSetFFVersion( refRoot );
//STRIP001
//STRIP001      ClearPersist();
//STRIP001      SwPaM *pPaM = 0;
//STRIP001      if( bConvertMode )
//STRIP001      {
//STRIP001          SwNodeIndex aPos( pDoc->GetNodes().GetEndOfContent(), -1 );
//STRIP001          pPaM = new SwPaM( aPos );
//STRIP001      }
//STRIP001      n = rIo.Load( refRoot, pPaM );
//STRIP001      delete pPaM;
//STRIP001      if( !IsError( n ))
//STRIP001          n = 0;
//STRIP001  }
//STRIP001  return n;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3IoImp::GetBlockText( const String& rShort, String& rText )
//STRIP001 {
//STRIP001  ULONG n = 0;
//STRIP001  String aName( rShort );
//STRIP001  lcl_EncryptBlockName( aName );
//STRIP001  if( pBlkRoot->IsStream( aName ) )
//STRIP001  {
//STRIP001      // Kurzform!
//STRIP001      pContents = pBlkRoot->OpenStream( aName, STREAM_STGREAD );
//STRIP001      pContents->SetBufferSize( SW3_BSR_CONTENTS_FLAT );
//STRIP001      pStrm = pContents;
//STRIP001      bOut = FALSE;
//STRIP001      InHeader();
//STRIP001      OpenRec( SWG_BLOCKTEXT );
//STRIP001      InString( *pStrm, rText );
//STRIP001      CloseRec( SWG_BLOCKTEXT );
//STRIP001      if( pBlkRoot->GetError() != SVSTREAM_OK
//STRIP001       || pStrm->GetError() != SVSTREAM_OK )
//STRIP001          n = ERR_SWG_READ_ERROR;
//STRIP001      else
//STRIP001          n = IsError( nRes ) ? nRes : 0;
//STRIP001      pStrm = NULL;
//STRIP001      pContents->SetBufferSize( 0 );
//STRIP001      pContents.Clear();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pRoot = pBlkRoot->OpenStorage( aName, STREAM_STGREAD );
//STRIP001
//STRIP001      // Fuer 3.1-Textbausteine muss die FF-Version noch umgeschossen
//STRIP001      // werden.
//STRIP001      if( pRoot.Is() )
//STRIP001          DetectAndSetFFVersion( pRoot );
//STRIP001
//STRIP001      if( OpenStreams( FALSE ) )
//STRIP001      {
//STRIP001          pStrm = pContents;
//STRIP001          pStrm->SetBufferSize( SW3_BSR_CONTENTS );
//STRIP001          LoadDocText( rText );
//STRIP001          pStrm->SetBufferSize( 0 );
//STRIP001          pStrm = NULL;
//STRIP001          CheckStreams();
//STRIP001          n = IsError( nRes ) ? nRes : 0;
//STRIP001          CloseStreams();
//STRIP001      }
//STRIP001      else
//STRIP001          rText.Erase();              // bug fix #24980#
//STRIP001      pRoot.Clear();
//STRIP001  }
//STRIP001  return n;
//STRIP001 }
//STRIP001
//STRIP001 void Sw3IoImp::MakeBlockText( const ByteString& rText )
//STRIP001 {
//STRIP001  SwTxtNode* pTxtNode = pDoc->GetNodes()[ pDoc->GetNodes().GetEndOfContent().
//STRIP001                                      GetIndex() - 1 ]->GetTxtNode();
//STRIP001  //JP 18.09.98: Bug 56706 - Standard sollte zumindest gesetzt sein!
//STRIP001  if( pTxtNode->GetTxtColl() == pDoc->GetDfltTxtFmtColl() )
//STRIP001      pTxtNode->ChgFmtColl( pDoc->GetTxtCollFromPool( RES_POOLCOLL_STANDARD ));
//STRIP001
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  do {
//STRIP001      if( nPos )
//STRIP001      {
//STRIP001 //           SwIndex aSplitIdx( pTxtNode, pTxtNode->GetTxt().Len() );
//STRIP001 //           pTxtNode->SplitNode( SwPosition( *pTxtNode, aSplitIdx ));
//STRIP001
//STRIP001          pTxtNode = (SwTxtNode*)pTxtNode->AppendNode(
//STRIP001                                  SwPosition( *pTxtNode ));
//STRIP001      }
//STRIP001
//STRIP001      SwIndex aIdx( pTxtNode );
//STRIP001      ByteString sText8( rText.GetToken( 0, '\015', nPos ) );
//STRIP001      String sText( sText8, eSrcSet );
//STRIP001      pTxtNode->Insert( sText, aIdx );
//STRIP001      ConvertText( *pTxtNode, sText8, 0, 0, 0 );
//STRIP001
//STRIP001  } while( STRING_NOTFOUND != nPos );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3IoImp::GetBlockMacroTable( const String& rShort,
//STRIP001                                  SvxMacroTableDtor& rMacroTbl )
//STRIP001 {
//STRIP001  ULONG nRes = 0;
//STRIP001  String aName ( rShort );
//STRIP001  lcl_EncryptBlockName( aName );
//STRIP001  // Wenn der Baustein nur aus einem Stream besteht kann er auch keine
//STRIP001  // Macros enthalten.
//STRIP001  if( !pBlkRoot->IsStream( aName ) )
//STRIP001  {
//STRIP001      SvStorageRef xRoot = pBlkRoot->OpenStorage( aName, STREAM_STGREAD );
//STRIP001
//STRIP001      // Fuer 3.1-Textbausteine muss die FF-Version noch umgeschossen
//STRIP001      // werden.
//STRIP001      if( xRoot.Is() )
//STRIP001      {
//STRIP001          DetectAndSetFFVersion( xRoot );
//STRIP001          nRes = rIo.GetMacroTable( xRoot, rMacroTbl );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nRes;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////

//STRIP001 Sw3TextBlocks::Sw3TextBlocks( const String& rFile )
//STRIP001           : SwImpBlocks( rFile ), bAutocorrBlock( FALSE )
//STRIP001 {
//STRIP001  pDoc = new SwDoc;
//STRIP001  pDoc->AddLink();
//STRIP001  pIo3 = new Sw3Io( *pDoc );
//STRIP001  pImp = pIo3->GetImp();
//STRIP001  pDoc->DoUndo( FALSE );      // immer auf FALSE !!
//STRIP001
//STRIP001  BOOL bIsStg = SvStorage::IsStorageFile( rFile );
//STRIP001
//STRIP001  // erstmal versuchen schreibend zu oeffen:
//STRIP001  //  Klappt das, dann ist es kein ReadOnly Document
//STRIP001  SvStorageRef refStg = new SvStorage( aFile, STREAM_STD_READWRITE, STORAGE_TRANSACTED );
//STRIP001  bReadOnly = 0 != refStg->GetError();
//STRIP001  refStg.Clear();
//STRIP001
//STRIP001  if( !bIsStg || !aDateModified.GetDate() || !aTimeModified.GetTime() )
//STRIP001      Touch();        // falls neu angelegt -> neuen ZeitStempel besorgen
//STRIP001
//STRIP001  refStg = new SvStorage( rFile, STREAM_READ | STREAM_SHARE_DENYNONE );
//STRIP001
//STRIP001  pImp->InitBlockMode( refStg, TRUE );
//STRIP001
//STRIP001  if( bIsStg )
//STRIP001  {
//STRIP001      const CharClass& rCC = GetAppCharClass();
//STRIP001      String aShort, aLong;
//STRIP001      ULONG nErr = pImp->FirstBlockName( aShort, aLong );
//STRIP001      if( !nErr && aShort.Len() )
//STRIP001      {
//STRIP001          do {
//STRIP001              String aShortUpr( rCC.upper( aShort ) );
//STRIP001              SwBlockName* pNew = new SwBlockName( aShortUpr, aLong, 0L );
//STRIP001              aNames.C40_PTR_INSERT( SwBlockName, pNew );
//STRIP001          }
//STRIP001          while( 0 == ( nErr = pImp->NextBlockName( aShort, aLong ) )
//STRIP001                  && aShort.Len() );
//STRIP001      }
//STRIP001      ReadInfo();
//STRIP001  }
//STRIP001  pImp->ResetBlockMode();
//STRIP001 }
//STRIP001
//STRIP001 Sw3TextBlocks::Sw3TextBlocks( SvStorage& rStg )
//STRIP001  : SwImpBlocks( rStg.GetName() ),
//STRIP001  bAutocorrBlock( TRUE )
//STRIP001 {
//STRIP001 // JP 18.10.96: Kruecke fuer die SVX(SW)-Autokorrektur
//STRIP001 //               eine Namensliste gibt es nicht; es wird nur PutDoc/GetText
//STRIP001 //               benutzt!!!!
//STRIP001  pDoc = new SwDoc;
//STRIP001  pDoc->AddLink();
//STRIP001  pIo3 = new Sw3Io( *pDoc );
//STRIP001  pImp = pIo3->GetImp();
//STRIP001  pDoc->DoUndo( FALSE );      // immer auf FALSE !!
//STRIP001
//STRIP001  bReadOnly = FALSE;
//STRIP001  SvStorageRef refStg = &rStg;
//STRIP001  pImp->InitBlockMode( refStg, TRUE );
//STRIP001  ReadInfo();
//STRIP001 }
//STRIP001
//STRIP001 Sw3TextBlocks::~Sw3TextBlocks()
//STRIP001 {
//STRIP001  pImp->ResetBlockMode();
//STRIP001  if( pDoc && !pDoc->RemoveLink() )
//STRIP001      delete pDoc;
//STRIP001  delete pIo3;
//STRIP001 }
//STRIP001
//STRIP001 short Sw3TextBlocks::GetFileType ( void ) const
//STRIP001 {
//STRIP001  return SWBLK_SW3;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::Delete( USHORT )
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::Rename( USHORT, const String&, const String& )
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::CopyBlock( SwImpBlocks& rDestImp, String& rShort,
//STRIP001                                                  const String& rLong)
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 void Sw3TextBlocks::SetDoc ( SwDoc * pNewDoc )
//STRIP001 {
//STRIP001  pDoc = pNewDoc;
//STRIP001  pImp->SetDoc ( *pNewDoc );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::GetDoc( USHORT nIdx )
//STRIP001 {
//STRIP001  return pImp->GetBlock( aNames[ nIdx ]->aShort );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::GetDocForConversion( USHORT nIdx )
//STRIP001 {
//STRIP001  return pImp->GetBlock( aNames[ nIdx ]->aShort, sal_True );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::BeginPutDoc( const String& rShort, const String& rLong )
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::PutDoc()
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::GetText( USHORT nIdx, String& rText )
//STRIP001 {
//STRIP001  return pImp->GetBlockText( aNames[ nIdx ]->aShort, rText );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::GetText( const String& rShort, String& rText )
//STRIP001 {
//STRIP001  return pImp->GetBlockText( rShort, rText );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::PutText( const String&, const String&,
//STRIP001                              const String& )
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::MakeBlockList()
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }

// Textbaustein-Konversionsmode ein/ausschalten
// Das Flag verhindert das Commit auf die Root nach dem Schreiben
// eines Textbausteins; daher wird hier committed, wenn das
// Flag geloescht wird.

//STRIP001 ULONG Sw3TextBlocks::SetConvertMode( BOOL bOn )
//STRIP001 {
//STRIP001  if( bOn )
//STRIP001      pImp->nGblFlags |= SW3F_CONVBLOCK;
//STRIP001  else
//STRIP001  {
//STRIP001      pImp->nGblFlags &= ~SW3F_CONVBLOCK;
//STRIP001      if( pImp->pBlkRoot.Is() )
//STRIP001      {
//STRIP001          pImp->pBlkRoot->Commit();
//STRIP001          if( pImp->pBlkRoot->GetError() != SVSTREAM_OK )
//STRIP001              return ERR_SWG_WRITE_ERROR;
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }


// ggf. eine SvPersist-Instanz einrichten

/*N*/ BOOL Sw3IoImp::CheckPersist()
/*N*/ {
/*N*/   // Haben wir schon einen Persist?
/*N*/   if( pDoc->GetPersist() )
/*N*/       return TRUE;
        DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 /*?*/    pPersist = new Sw3Persist;
//STRIP001 /*?*/    if( pPersist->DoOwnerLoad( pRoot ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pDoc->SetPersist( pPersist );
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/        return FALSE;
/*N*/ }

// ggf. eine SvPersist-Instanz freigeben

//STRIP001 void Sw3IoImp::ClearPersist()
//STRIP001 {
//STRIP001  if( pPersist.Is() )
//STRIP001  {
//STRIP001      pDoc->SetPersist( NULL );
//STRIP001      pPersist.Clear();
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::OpenFile( BOOL bReadOnly )
//STRIP001 {
//STRIP001  if( bAutocorrBlock )
//STRIP001      return 0;
//STRIP001
//STRIP001  if( !bReadOnly )
//STRIP001      return ERR_SWG_OLD_GLOSSARY;
//STRIP001
//STRIP001  pImp->ResetBlockMode();
//STRIP001  SvStorageRef refStg = new SvStorage( aFile,
//STRIP001                                       (STREAM_READ | STREAM_SHARE_DENYNONE));
//STRIP001  pImp->InitBlockMode( refStg, TRUE );
//STRIP001  return refStg->GetError();
//STRIP001 }
//STRIP001
//STRIP001 void Sw3TextBlocks::CloseFile()
//STRIP001 {
//STRIP001  if( !bAutocorrBlock )
//STRIP001  {
//STRIP001      pImp->ResetBlockMode();
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 BOOL Sw3TextBlocks::IsOnlyTextBlock( const String& rShort ) const
//STRIP001 {
//STRIP001  String aShName( rShort );
//STRIP001  lcl_EncryptBlockName( aShName );
//STRIP001  return pImp->pBlkRoot->IsStream( aShName );
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::GetMacroTable( USHORT nIdx, SvxMacroTableDtor& rMacroTbl,
//STRIP001                                  sal_Bool bFileAlreadyOpen )
//STRIP001 {
//STRIP001  ULONG nRes = 0;
//STRIP001
//STRIP001  if ( bFileAlreadyOpen )
//STRIP001  {
//STRIP001      nRes = pImp->GetBlockMacroTable( aNames[nIdx]->aShort, rMacroTbl );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nRes = OpenFile( TRUE );
//STRIP001      if( 0 == nRes )
//STRIP001      {
//STRIP001          nRes = pImp->GetBlockMacroTable( aNames[nIdx]->aShort, rMacroTbl );
//STRIP001          CloseFile();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nRes;
//STRIP001 }
//STRIP001
//STRIP001 ULONG Sw3TextBlocks::SetMacroTable( USHORT,
//STRIP001                                  const SvxMacroTableDtor&,
//STRIP001                                  sal_Bool )
//STRIP001 {
//STRIP001  return ERR_SWG_OLD_GLOSSARY;
//STRIP001 }
//STRIP001
//STRIP001 void Sw3TextBlocks::ReadInfo()
//STRIP001 {
//STRIP001  const String sBlockInfo( String::CreateFromAscii(N_BLOCKINFO) );
//STRIP001  if( pImp->pBlkRoot.Is() && pImp->pBlkRoot->IsStream( sBlockInfo ) )
//STRIP001  {
//STRIP001      SvStorageStreamRef xStrm( pImp->pBlkRoot->OpenStream( sBlockInfo,
//STRIP001                                              STREAM_STGREAD ));
//STRIP001      xStrm->SetSize( 0 );
//STRIP001      xStrm->SetBufferSize( SW3_BSW_BLKDIR );
//STRIP001
//STRIP001      BYTE nLen, nChrSet;
//STRIP001      USHORT nVersion;
//STRIP001      *xStrm >> nLen              // Laenge des Headers
//STRIP001             >> nVersion          // Version des Streams
//STRIP001             >> nChrSet           // der Zeichensatz
//STRIP001             ;
//STRIP001
//STRIP001      xStrm->ReadByteString( aName, GetSOLoadTextEncoding( (rtl_TextEncoding)nChrSet, SOFFICE_FILEFORMAT_50 ) );
//STRIP001  }
//STRIP001 }

//////////////////////////////////////////////////////////////////////////

//STRIP001 Sw3Persist::Sw3Persist() : SvPersist()
//STRIP001 {}
//STRIP001
//STRIP001 void __EXPORT Sw3Persist::FillClass( SvGlobalName * pClassName,
//STRIP001                          ULONG * pClipFormat,
//STRIP001                          String * pAppName,
//STRIP001                          String * pLongUserName,
//STRIP001                          String * pUserName,
//STRIP001                          long nFileFormat ) const
//STRIP001 {
//STRIP001  //JP 12.02.97: es sollte erstmal versucht, ueber eine offene DocShell
//STRIP001  //              an diese Information zu gelangen. Dafuer muss der SFX
//STRIP001  //              herhalten.
//STRIP001  TypeId aTId( TYPE ( SwDocShell ));
//STRIP001
//STRIP001  // Irgendeine Shell suchen, die keine Web- oder Globaldokument
//STRIP001  // DocShell ist.
//STRIP001  SwDocShell* pObjSh = (SwDocShell*)SfxObjectShell::GetFirst( &aTId, FALSE );
//STRIP001  while( pObjSh && aTId != pObjSh->Type() )
//STRIP001      pObjSh = (SwDocShell*)SfxObjectShell::GetNext( *pObjSh, &aTId, FALSE );
//STRIP001
//STRIP001  if( pObjSh )
//STRIP001  {
//STRIP001      pObjSh->SwDocShell::FillClass( pClassName, pClipFormat, pAppName,
//STRIP001                                  pLongUserName, pUserName, nFileFormat );
//STRIP001      return ;
//STRIP001  }
//STRIP001
//STRIP001  // MUSS NOCH ANGEPASST WERDEN, IST GEHACKT!!!
//STRIP001 // 3.0
//STRIP001 //   0xDC5C7E40L, 0xB35C, 0x101B, 0x99, 0x61, 0x04, 0x02, 0x1C, 0x00, 0x70,0x02)
//STRIP001 //   pClassName->MakeId( "DC5C7E40-B35C-101B-9961-04021c007002" );
//STRIP001 // 4.0
//STRIP001 //   0x8b04e9b0,  0x420e, 0x11d0, 0xa4, 0x5e, 0x0,  0xa0, 0x24, 0x9d, 0x57,0xb1);
//STRIP001 //   pClassName->MakeId( "8B04E9B0-420E-11D0-A45E-00A0249D57B1" );
//STRIP001  *pClassName = SvGlobalName( BF_SO3_SW_CLASSID );
//STRIP001  pAppName->AssignAscii( "StarWriter 5.0" );
//STRIP001  pUserName->AssignAscii( "Text" );
//STRIP001  pLongUserName->AssignAscii( "StarOffice 6.0 Text" );
//STRIP001  *pClipFormat = SOT_FORMATSTR_ID_STARWRITER_60;
//STRIP001 }
//STRIP001
//STRIP001 BOOL __EXPORT Sw3Persist::Save()
//STRIP001 {
//STRIP001  if( SaveChilds() )
//STRIP001      return SvPersist::Save();
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL __EXPORT Sw3Persist::SaveCompleted( SvStorage * pStor )
//STRIP001 {
//STRIP001  if( SaveCompletedChilds( pStor ) )
//STRIP001      return SvPersist::SaveCompleted( pStor );
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }


}
