/*************************************************************************
 *
 *  $RCSfile: sw_sw3gsect.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:51 $
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
namespace binfilter {


//STRIP001 #pragma hdrstop
//STRIP001
//STRIP001 #define _SVSTDARR_STRINGSDTOR
//STRIP001 #define _SVSTDARR_STRINGS
//STRIP001 #include <svtools/svstdarr.hxx>
//STRIP001
//STRIP001 #ifndef _SFXMACITEM_HXX //autogen
//STRIP001 #include <svtools/macitem.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _TOOLS_TENCCVT_HXX //autogen
//STRIP001 #include <tools/tenccvt.hxx>
//STRIP001 #endif
//STRIP001
//STRIP001 #include "swerror.h"
//STRIP001 #include "sw3imp.hxx"
//STRIP001 #include "sw3ids.hxx"
//STRIP001 #include "sw3marks.hxx"
//STRIP001 #include "section.hxx"
//STRIP001
//STRIP001
//STRIP001 //////////////////////////////////////////////////////////////////////////////
//STRIP001
//STRIP001 ULONG Sw3IoImp::OpenStreamsForScan( SvStorage *pStor, BOOL bPageStyles )
//STRIP001 {
//STRIP001  pOldRoot = pRoot;
//STRIP001  pRoot = pStor;
//STRIP001
//STRIP001  USHORT nMode = STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE;
//STRIP001
//STRIP001  Reset();
//STRIP001
//STRIP001 //   pCurIosys = this;
//STRIP001
//STRIP001  if( !pRoot.Is() ||
//STRIP001      pRoot->GetError() != SVSTREAM_OK ||
//STRIP001      !pRoot->IsContained( N_DOC ) ||
//STRIP001      pRoot->IsStorage( N_DOC ) )
//STRIP001  {
//STRIP001      pRoot = pOldRoot;
//STRIP001      return ERR_SWG_READ_ERROR;
//STRIP001  }
//STRIP001
//STRIP001  pContents = pRoot->OpenStream( N_DOC, nMode );
//STRIP001  pPageStyles = bPageStyles ? pRoot->OpenStream( N_PAGESTYLES, nMode ) : 0;
//STRIP001
//STRIP001  if( pRoot->GetError() != SVSTREAM_OK ||
//STRIP001      !pContents.Is() || pContents->GetError() != SVSTREAM_OK ||
//STRIP001      ( bPageStyles && (!pPageStyles.Is() ||
//STRIP001                        pPageStyles->GetError() != SVSTREAM_OK) ) )
//STRIP001  {
//STRIP001      pContents.Clear();
//STRIP001      pPageStyles.Clear();
//STRIP001      pRoot = pOldRoot;
//STRIP001      pOldRoot.Clear();
//STRIP001      // kein Reset, weil wir ausser pOld-Root nichts veraendert haben
//STRIP001      return ERR_SWG_READ_ERROR;
//STRIP001  }
//STRIP001
//STRIP001  long nFFVersion = pRoot->GetVersion();
//STRIP001  ASSERT( nFFVersion == SOFFICE_FILEFORMAT_31 ||
//STRIP001          nFFVersion == SOFFICE_FILEFORMAT_40 ||
//STRIP001          nFFVersion == SOFFICE_FILEFORMAT_50,
//STRIP001          "Am Root-Storage ist keine FF-Version gesetzt!" );
//STRIP001
//STRIP001  // eSrcSet is set to the value og gsl_getSystemSetEncoding in Reset()
//STRIP001  // MIB 31.07.01: Setting the charset here does not make nuch sense.
//STRIP001  // However, the value set here will be replaced by the one stored in
//STRIP001  // the header before it is used.
//STRIP001  pContents->SetStreamCharSet( eSrcSet ),
//STRIP001  pContents->SetVersion( nFFVersion );
//STRIP001  if( pPageStyles.Is() )
//STRIP001  {
//STRIP001      pPageStyles->SetStreamCharSet( eSrcSet );
//STRIP001      pPageStyles->SetVersion( nFFVersion );
//STRIP001  }
//STRIP001  OutputMode( FALSE );
//STRIP001
//STRIP001  return 0;
//STRIP001 }
//STRIP001
//STRIP001 void Sw3IoImp::CloseStreamsForScan()
//STRIP001 {
//STRIP001  pContents.Clear();
//STRIP001  pPageStyles.Clear();
//STRIP001  Reset();
//STRIP001
//STRIP001  pRoot = pOldRoot;
//STRIP001  pOldRoot.Clear();
//STRIP001 }
//STRIP001
//STRIP001 BOOL Sw3IoImp::InHeaderForScan( BOOL bReadRecSizes )
//STRIP001 {
//STRIP001  BYTE cLen, cSet, cGUI;
//STRIP001  sal_Char cHdrSign[ 8 ];
//STRIP001  Reset2();
//STRIP001  OutputMode( FALSE );
//STRIP001
//STRIP001  if( pStrm->Read( cHdrSign, 7 ) != 7 || !CheckHeader(cHdrSign) )
//STRIP001  {
//STRIP001      Error( ERR_SW6_NOWRITER_FILE );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  *pStrm >> cLen;
//STRIP001
//STRIP001  UINT32 nRecSzPos;
//STRIP001  ULONG nOld = pStrm->Tell();
//STRIP001  INT32 nDummy32;
//STRIP001  // nDummy8 war fuer IRIX mal unsigned char. Wenn das nicht durch
//STRIP001  // geht ist das ein Problem in stream.h und solar.h, aber keines hier
//STRIP001  INT8 nCompatVer, nDummy8;
//STRIP001
//STRIP001  *pStrm >> nVersion >> nFileFlags >> nDummy32 >> nRecSzPos >> nDummy32
//STRIP001         >> nDummy8 >> nDummy8 >> nDummy8 >> nCompatVer;
//STRIP001  if( nCompatVer > SWG_CVERSION )
//STRIP001  {
//STRIP001      Error( ERR_SWG_NEW_VERSION );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  if( nFileFlags & SWGF_BAD_FILE )
//STRIP001  {
//STRIP001      Error( ERR_SWG_READ_ERROR );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  pStrm->Read( cPasswd, 16L );
//STRIP001  *pStrm >> cSet >> cGUI >> nDate >> nTime;
//STRIP001  eSrcSet = GetSOLoadTextEncoding( (rtl_TextEncoding) cSet,
//STRIP001                                   pStrm->GetVersion() );
//STRIP001  pStrm->SetStreamCharSet( eSrcSet );
//STRIP001  if( nFileFlags & SWGF_BLOCKNAME )
//STRIP001  {
//STRIP001      sal_Char cBuf[ 64 ];
//STRIP001      if( pStrm->Read( cBuf, 64 ) != 64 )
//STRIP001          pStrm->SetError( SVSTREAM_FILEFORMAT_ERROR );
//STRIP001  }
//STRIP001  ULONG nNew = pStrm->Tell();
//STRIP001  nOld += cLen;
//STRIP001  if( nOld != nNew )
//STRIP001      pStrm->Seek( nOld );
//STRIP001
//STRIP001 //   if( !CheckPasswd() )
//STRIP001 //       Error( ERRCODE_SFX_WRONGPASSWORD );
//STRIP001
//STRIP001  if( nRecSzPos!= 0 && bReadRecSizes && IsVersion(SWG_RECSIZES) )
//STRIP001      InRecSizes( nRecSzPos );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void Sw3IoImp::GetSectionList( SvStrings& rSectionList,
//STRIP001                             SvStringsDtor& rBookmarks )
//STRIP001 {
//STRIP001  if( !InHeaderForScan(TRUE) )
//STRIP001      return;
//STRIP001
//STRIP001  // Normales Lesen?
//STRIP001  BOOL bDone = BOOL( !Good() );
//STRIP001  while( !bDone )
//STRIP001  {
//STRIP001      BYTE cType = Peek();
//STRIP001      if( !Good() || pStrm->IsEof() )
//STRIP001          bDone = TRUE;
//STRIP001      else switch( cType )
//STRIP001      {
//STRIP001      case SWG_EOF:
//STRIP001          // fertig
//STRIP001          bDone = TRUE;
//STRIP001          break;
//STRIP001      case SWG_FLYFRAMES:
//STRIP001          {
//STRIP001              // die Seitengebundenen Rahmen durchforsten
//STRIP001              OpenRec( SWG_FLYFRAMES );
//STRIP001              while( BytesLeft() )
//STRIP001              {
//STRIP001                  if( SWG_FLYFMT == Peek() )
//STRIP001                      ScanFormat( SWG_FLYFMT, rSectionList, rBookmarks );
//STRIP001                  else
//STRIP001                      SkipRec();
//STRIP001              }
//STRIP001              CloseRec( SWG_FLYFRAMES );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_BOOKMARKS:
//STRIP001          {
//STRIP001              // die Bookmarks untersuchen
//STRIP001              OpenRec( SWG_BOOKMARKS );
//STRIP001              while( BytesLeft() )
//STRIP001              {
//STRIP001                  String aName, aDummy;
//STRIP001                  OpenRec( SWG_BOOKMARK );
//STRIP001                  InString( *pStrm, aDummy );
//STRIP001                  InString( *pStrm, aName );
//STRIP001                  // Hier kommen noch mehr Daten, die aber
//STRIP001                  // nicht benoetigt werden.
//STRIP001                  CloseRec( SWG_BOOKMARK );
//STRIP001
//STRIP001                  // Bookmarks einfuegen, aber nicht doppelt
//STRIP001                  for( USHORT i=0; i<rBookmarks.Count(); i++ )
//STRIP001                      if( *(rBookmarks[i]) == aName )
//STRIP001                          break;
//STRIP001
//STRIP001                  if( i==rBookmarks.Count() )
//STRIP001                      rBookmarks.Insert( new String(aName), i );
//STRIP001              }
//STRIP001              CloseRec( SWG_BOOKMARKS );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_PAGEDESCS:
//STRIP001          {
//STRIP001              // Seitenbeschreibungen lesen
//STRIP001              OpenRec( SWG_PAGEDESCS );
//STRIP001
//STRIP001              OpenFlagRec();
//STRIP001              USHORT nDesc;
//STRIP001              *pStrm >> nDesc;
//STRIP001              CloseFlagRec();
//STRIP001
//STRIP001              for( USHORT i = 0; i < nDesc; i++ )
//STRIP001              {
//STRIP001                  OpenRec( SWG_PAGEDESC );
//STRIP001
//STRIP001                  OpenFlagRec();
//STRIP001                  // Der Inhalt des Flag-Records ist uninteressant
//STRIP001                  CloseFlagRec();
//STRIP001
//STRIP001                  while( BytesLeft() )
//STRIP001                  {
//STRIP001                      if( SWG_ATTRSET == Peek() )
//STRIP001                      {
//STRIP001                          OpenRec( SWG_ATTRSET );
//STRIP001
//STRIP001                          while( BytesLeft() )
//STRIP001                              ScanAttr( rSectionList, rBookmarks );
//STRIP001
//STRIP001                          CloseRec( SWG_ATTRSET );
//STRIP001                      }
//STRIP001                      else
//STRIP001                          SkipRec();
//STRIP001                  }
//STRIP001                  CloseRec( SWG_PAGEDESC );
//STRIP001              }
//STRIP001
//STRIP001              CloseRec( SWG_PAGEDESCS );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_CONTENTS:
//STRIP001          // den Inhalt durchkaemmen
//STRIP001          ScanContents( rSectionList, rBookmarks );
//STRIP001          break;
//STRIP001      default:
//STRIP001          // hier werden wir wohl nichts finden
//STRIP001          SkipRec();
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void Sw3IoImp::ScanContents( SvStrings& rSectionList,
//STRIP001                           SvStringsDtor& rBookmarks )
//STRIP001 {
//STRIP001  UINT16 nDummy16;
//STRIP001  String aDummy;
//STRIP001
//STRIP001  OpenRec( SWG_CONTENTS );
//STRIP001
//STRIP001  if( IsVersion(SWG_LAYFRAMES) )
//STRIP001  {
//STRIP001      OpenFlagRec();
//STRIP001      CloseFlagRec();
//STRIP001  }
//STRIP001  else
//STRIP001      *pStrm >> nDummy16; // nNodes
//STRIP001
//STRIP001  while( BytesLeft() )
//STRIP001  {
//STRIP001      BYTE cType = Peek();
//STRIP001      switch( cType )
//STRIP001      {
//STRIP001      case SWG_TEXTNODE:
//STRIP001          {
//STRIP001              // Text-Nodes koennen absatz- und zeichengeb. Rahmen enthalten
//STRIP001              OpenRec( SWG_TEXTNODE );
//STRIP001              // Die Daten des Flag-Record werden automatisch ueberlesen.
//STRIP001              OpenFlagRec();
//STRIP001              CloseFlagRec();
//STRIP001
//STRIP001              InString( *pStrm, aDummy );
//STRIP001
//STRIP001              while( BytesLeft() )
//STRIP001              {
//STRIP001                  BYTE cTypeText = Peek();
//STRIP001                  switch( cTypeText )
//STRIP001                  {
//STRIP001                  case SWG_FLYFMT:
//STRIP001                      // Absatzgebundener FlyFrame
//STRIP001                      ScanFormat( SWG_FLYFMT, rSectionList, rBookmarks );
//STRIP001                      break;
//STRIP001                  case SWG_ATTRIBUTE:
//STRIP001                      // vielleicht ein Rahmen oder eine Fussnote?
//STRIP001                      ScanAttr( rSectionList, rBookmarks );
//STRIP001                      break;
//STRIP001                  case SWG_MARK:
//STRIP001                      {
//STRIP001                          // Hoppla, vielleicht eine Textmarke
//STRIP001                          OpenRec( SWG_MARK );
//STRIP001                          BYTE cType;
//STRIP001                          USHORT nId;
//STRIP001                          *pStrm >> cType >> nId;
//STRIP001                          // Ab hier kommen nur noch uninterssante Daten
//STRIP001                          CloseRec( SWG_MARK );
//STRIP001                          if( SW3_BOOK_MARK==cType &&
//STRIP001                              nId < rBookmarks.Count() )
//STRIP001                          {
//STRIP001                              // Ja, es ist noetig den String mit new
//STRIP001                              // nochmal anzulegen, denn der Ptr in
//STRIP001                              // rBookmarks ueberlebt den Aufruf von
//STRIP001                              // Sw3Io::GetSectionList nicht!
//STRIP001                              rSectionList.Insert(
//STRIP001                                  new String( *(rBookmarks[nId]) ),
//STRIP001                                          rSectionList.Count() );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  default:
//STRIP001                      // woanders werden wir nichts finden
//STRIP001                      SkipRec();
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              CloseRec( SWG_TEXTNODE );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_TABLE:
//STRIP001          {
//STRIP001              // Tabellen enthalten natuerlich Inhalt
//STRIP001              OpenRec( SWG_TABLE );
//STRIP001
//STRIP001              OpenFlagRec();
//STRIP001              CloseFlagRec();
//STRIP001
//STRIP001              // optionales Rahmenformt
//STRIP001              if( SWG_FRAMEFMT == Peek() )
//STRIP001                  SkipRec();
//STRIP001
//STRIP001              // optionales DDE-Feld
//STRIP001              if( SWG_FIELDTYPE == Peek() )
//STRIP001                  SkipRec();
//STRIP001
//STRIP001              // die Zeilen scannen
//STRIP001              while( BytesLeft() )
//STRIP001                  ScanTableLine( rSectionList, rBookmarks );
//STRIP001
//STRIP001              CloseRec( SWG_TABLE );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_SECTION:
//STRIP001          {
//STRIP001              // Juchhu! Da haben wir ja gefunden wonach wir suchen
//STRIP001              OpenRec( SWG_SECTION );
//STRIP001              String aName;
//STRIP001              InString( *pStrm, aName );
//STRIP001              InString( *pStrm, aDummy );
//STRIP001              OpenFlagRec();
//STRIP001              UINT16 nType;
//STRIP001              *pStrm >> nType;
//STRIP001              CloseFlagRec();
//STRIP001
//STRIP001              rSectionList.Insert( new String(aName), rSectionList.Count() );
//STRIP001
//STRIP001              // das Format ueberlesen
//STRIP001              SkipRec();
//STRIP001
//STRIP001              // jetzt kommt der Inhalt, wobei wir nicht an dem Inhalt
//STRIP001              // von gelinkten Sections interessiert sind
//STRIP001              if( CONTENT_SECTION == nType)
//STRIP001                  ScanContents( rSectionList, rBookmarks );
//STRIP001              else
//STRIP001                  SkipRec();
//STRIP001              // Ab hier kommen nur noch uninteressante Daten
//STRIP001              CloseRec( SWG_SECTION );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SWG_FLYFMT:
//STRIP001          ScanFormat( SWG_FLYFMT, rSectionList, rBookmarks );
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          // ueberall sonst werden wir nichts finden
//STRIP001          SkipRec();
//STRIP001      }
//STRIP001  }
//STRIP001  CloseRec( SWG_CONTENTS );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void Sw3IoImp::ScanTableLine( SvStrings& rSectionList,
//STRIP001                            SvStringsDtor& rBookmarks )
//STRIP001 {
//STRIP001  OpenRec( SWG_TABLELINE );
//STRIP001
//STRIP001  OpenFlagRec();
//STRIP001  CloseFlagRec();
//STRIP001
//STRIP001  // optionales Frame-Format
//STRIP001  if( SWG_FRAMEFMT == Peek() )
//STRIP001      SkipRec();
//STRIP001
//STRIP001  // die Zellen einlesen
//STRIP001  while( BytesLeft() )
//STRIP001  {
//STRIP001      OpenRec( SWG_TABLEBOX );
//STRIP001      OpenFlagRec();
//STRIP001      CloseFlagRec();
//STRIP001
//STRIP001      // optionales Frame-Format
//STRIP001      if( SWG_FRAMEFMT == Peek() )
//STRIP001          SkipRec();
//STRIP001
//STRIP001      if( SWG_CONTENTS == Peek() )
//STRIP001          // Edit-Box
//STRIP001          ScanContents( rSectionList, rBookmarks );
//STRIP001      else
//STRIP001      {
//STRIP001          // sonst die Zeilen durchsuchen
//STRIP001          while( BytesLeft() )
//STRIP001              ScanTableLine( rSectionList, rBookmarks );
//STRIP001      }
//STRIP001      CloseRec( SWG_TABLEBOX );
//STRIP001  }
//STRIP001
//STRIP001  CloseRec( SWG_TABLELINE );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void Sw3IoImp::ScanFormat( BYTE cKind,
//STRIP001                         SvStrings& rSectionList,
//STRIP001                         SvStringsDtor& rBookmarks )
//STRIP001 {
//STRIP001  USHORT nDummy16, nStrIdx = IDX_NO_VALUE;
//STRIP001  String aDummy;
//STRIP001
//STRIP001  if( !OpenRec( cKind ) )
//STRIP001  {
//STRIP001      CloseRec( SWG_EOF );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  BYTE cFlags = OpenFlagRec();
//STRIP001  *pStrm >> nDummy16 >> nDummy16;
//STRIP001  // 0x10 - Namensindex des Formats folgt
//STRIP001  // 0x20 - SdrObject-Referenz folgt
//STRIP001  if( cFlags & 0x10 )
//STRIP001      *pStrm >> nStrIdx;
//STRIP001  CloseFlagRec();
//STRIP001
//STRIP001  if( nStrIdx == IDX_NO_VALUE )
//STRIP001      InString( *pStrm, aDummy );
//STRIP001
//STRIP001  while( BytesLeft() )
//STRIP001  {
//STRIP001      if( SWG_ATTRSET == Peek() )
//STRIP001      {
//STRIP001          OpenRec( SWG_ATTRSET );
//STRIP001
//STRIP001          while( BytesLeft() )
//STRIP001              ScanAttr( rSectionList, rBookmarks );
//STRIP001
//STRIP001          CloseRec( SWG_ATTRSET );
//STRIP001      }
//STRIP001      else
//STRIP001          SkipRec();
//STRIP001  }
//STRIP001
//STRIP001  CloseRec( cKind );
//STRIP001 }
//STRIP001
//STRIP001 void Sw3IoImp::GetMacroTable( SvxMacroTableDtor& rMacroTbl )
//STRIP001 {
//STRIP001  if( !InHeaderForScan(TRUE) )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bDone = BOOL( !Good() );
//STRIP001  while( !bDone )
//STRIP001  {
//STRIP001      BYTE cType = Peek();
//STRIP001      if( !Good() || pStrm->IsEof() )
//STRIP001          bDone = TRUE;
//STRIP001      else switch( cType )
//STRIP001      {
//STRIP001      case SWG_EOF:
//STRIP001          bDone = TRUE;                   // fertig
//STRIP001          break;
//STRIP001      case SWG_MACROTBL:
//STRIP001          ScanMacroTbl( rMacroTbl );
//STRIP001          bDone = TRUE;                   // auch fertig
//STRIP001          break;
//STRIP001      default:
//STRIP001          // hier werden wir wohl nichts finden
//STRIP001          SkipRec();
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void Sw3IoImp::ScanMacroTbl( SvxMacroTableDtor& rMacroTbl )
//STRIP001 {
//STRIP001  OpenRec( SWG_MACROTBL );
//STRIP001  while( BytesLeft() )
//STRIP001  {
//STRIP001      OpenRec( SWG_MACRO );
//STRIP001      UINT16 nKey, nScriptType = STARBASIC;
//STRIP001      String aLib, aMac;
//STRIP001      *pStrm >> nKey;
//STRIP001      InString( *pStrm, aLib );
//STRIP001      InString( *pStrm, aMac );
//STRIP001
//STRIP001      if( SWG_SVXMACROS <= nVersion )
//STRIP001          *pStrm >> nScriptType;
//STRIP001      rMacroTbl.Insert( nKey, new SvxMacro( aMac, aLib,
//STRIP001                                            (ScriptType)nScriptType ) );
//STRIP001      CloseRec( SWG_MACRO );
//STRIP001  }
//STRIP001  CloseRec( SWG_MACROTBL );
//STRIP001 }



}
