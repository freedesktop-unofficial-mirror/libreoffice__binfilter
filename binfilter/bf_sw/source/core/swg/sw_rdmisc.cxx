/*************************************************************************
 *
 *  $RCSfile: sw_rdmisc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:46:50 $
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


// auto strip #ifndef _COLOR_HXX //autogen
// auto strip #include <tools/color.hxx>
// auto strip #endif
// auto strip #ifndef _JOBSET_HXX //autogen
// auto strip #include <vcl/jobset.hxx>
// auto strip #endif
// auto strip #ifndef _SFXDOCINF_HXX //autogen
// auto strip #include <bf_sfx2/docinf.hxx>
// auto strip #endif
// auto strip #ifndef _SFXMACITEM_HXX //autogen
// auto strip #include <svtools/macitem.hxx>
// auto strip #endif

// auto strip #ifndef _FMTANCHR_HXX //autogen
// auto strip #include <fmtanchr.hxx>
// auto strip #endif
// auto strip #ifndef _FRMFMT_HXX //autogen
// auto strip #include <frmfmt.hxx>
// auto strip #endif
// auto strip #ifndef _DOCSTAT_HXX //autogen
// auto strip #include <docstat.hxx>
// auto strip #endif
#ifndef _FTNINFO_HXX //autogen
#include <ftninfo.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
// auto strip #ifndef _RDSWG_HXX
// auto strip #include <rdswg.hxx>
// auto strip #endif
// auto strip #ifndef _SWGPAR_HXX
// auto strip #include <swgpar.hxx>     // SWGRD_xxx-Flags
// auto strip #endif
// auto strip #ifndef _FRMIDS_HXX
// auto strip #include <frmids.hxx>
// auto strip #endif
// auto strip #ifndef _FLYPOS_HXX
// auto strip #include <flypos.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>      // Zeichen-Konversion
// auto strip #endif
namespace binfilter {

//using namespace ::com::sun::star;

//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

// FlyFrames

// Ein FlyFrame ist ein normales Frame-Format. Die Hints RES_CNTNT und
// RES_FLY_ANCHOR muessen allerdings noch verbunden werden. Wenn der
// ANCHOR-Hint eingelesen wird, wird die globale Variable nCntntCol
// besetzt.

//STRIP001 void SwSwgReader::InFlyFrame( const SwNodeIndex* pNdIdx )
//STRIP001 {
//STRIP001  BOOL bAtCnt = FALSE;
//STRIP001
//STRIP001  nCntntCol = 0;
//STRIP001  if( r.cur() != SWG_FLYFMT )
//STRIP001  {
//STRIP001      Error();
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  USHORT eSave_StartNodeType = eStartNodeType;
//STRIP001  eStartNodeType = SwFlyStartNode;
//STRIP001
//STRIP001  SwFrmFmt* pFmt = (SwFrmFmt*) InFormat( NULL );
//STRIP001  RegisterFmt( *pFmt );
//STRIP001  if( pNdIdx )
//STRIP001  {
//STRIP001      // Content und Anchor miteinander verbinden, wenn Node angegeben ist
//STRIP001      SwFmtAnchor aAnchor = pFmt->GetAnchor();
//STRIP001      USHORT nId = aAnchor.GetAnchorId();
//STRIP001      switch( nId )
//STRIP001      {
//STRIP001          case FLY_AT_CNTNT:
//STRIP001              bAtCnt = TRUE;
//STRIP001          case FLY_IN_CNTNT:
//STRIP001              {
//STRIP001                  SwCntntNode *pNode = pDoc->GetNodes() [ *pNdIdx ]->GetCntntNode();
//STRIP001                  if( pNode )
//STRIP001                  {
//STRIP001                      SwPosition aPos( *pNdIdx, SwIndex( pNode, nCntntCol ) );
//STRIP001                      aAnchor.SetAnchor( &aPos );
//STRIP001                      pFmt->SetAttr( aAnchor );
//STRIP001                  }
//STRIP001                  // Layout-Frames im Insert Mode fuer absatzgebundene
//STRIP001                  // Flys erzeugen
//STRIP001                  if( !bNew && bAtCnt )
//STRIP001                      pFmt->MakeFrms();
//STRIP001              }
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  //JP 01.04.97: wird nach dem Lesen durchs SwReader::Read eindeutig gemacht!
//STRIP001  if( pFmt->GetName().EqualsAscii("Fly") )
//STRIP001      pFmt->SetName( aEmptyStr );
//STRIP001
//STRIP001  eStartNodeType = eSave_StartNodeType;
//STRIP001 }

//STRIP001 void SwSwgReader::InFlyFrames( const SwNodeIndex* pNdIdx )
//STRIP001 {
//STRIP001  USHORT nFrm;
//STRIP001  r >> nFrm;
//STRIP001  r.next();
//STRIP001  for( USHORT i = 0; i < nFrm && r.good(); i++)
//STRIP001      InFlyFrame( pNdIdx );
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Makros


//STRIP001 void SwSwgReader::InGlobalMacroTbl()
//STRIP001 {
//STRIP001  short nMacro;
//STRIP001  r >> nMacro;
//STRIP001  for( short i = 0; i < nMacro; i++ )
//STRIP001  {
//STRIP001      USHORT nEvent;
//STRIP001      r >> nEvent;
//STRIP001      String aLib = GetText();
//STRIP001      String aMac = GetText();
//STRIP001      pDoc->SetGlobalMacro( nEvent, SvxMacro( aMac, aLib, STARBASIC ) );
//STRIP001  }
//STRIP001  r.next();
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Job-Setup

//STRIP001 void SwSwgReader::InJobSetup()
//STRIP001 {
//STRIP001  BYTE recid = r.cur();
//STRIP001  // Der alte Job-Setup ist nicht mehr zu erstellen.
//STRIP001  if( recid == SWG_JOBSETUP )
//STRIP001      r.skipnext();
//STRIP001  else
//STRIP001  {
//STRIP001      JobSetup aJobSetup;
//STRIP001      BOOL bDfltPrn = FALSE;
//STRIP001      r.Strm() >> bDfltPrn >> aJobSetup;
//STRIP001
//STRIP001      pDoc->SetJobsetup( aJobSetup );
//STRIP001 //JP 25.04.95: das Flag gibts nicht mehr:
//STRIP001 //       pDoc->UseDfltPrt( (BOOL)bDfltPrn );
//STRIP001      r.skipnext();
//STRIP001  }
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Dokument-Info

//STRIP001 void SwSwgReader::InDocInfo()
//STRIP001 {
//STRIP001  while( r.good() )
//STRIP001  {
//STRIP001      switch( r.next() )
//STRIP001      {
//STRIP001          case SWGINF_DBNAME:
//STRIP001              {
//STRIP001                  String aName = ParseText();
//STRIP001                  if( bNew )
//STRIP001                  {
//STRIP001                      if( aName.EqualsIgnoreCaseAscii( "ADRESSEN" ) )
//STRIP001                          aName.AssignAscii( "Address" );
//STRIP001                      SwDBData aData;
//STRIP001                      aData.sDataSource = aName;
//STRIP001                      pDoc->ChgDBData( aData );
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          case SWGINF_DOCSTAT:
//STRIP001              if( bNew )
//STRIP001              {
//STRIP001                  USHORT nPage, nPara;
//STRIP001                  SwDocStat aStat;
//STRIP001                  r >> aStat.nTbl >> aStat.nGrf >> aStat.nOLE
//STRIP001                    >> nPage >> nPara >> aStat.nWord
//STRIP001                    >> aStat.nChar;
//STRIP001                  aStat.nPage = nPage;
//STRIP001                  aStat.nPara = nPara;
//STRIP001                  aStat.bModified = FALSE;
//STRIP001                  aStat.pInternStat = NULL;
//STRIP001                  pDoc->SetDocStat( aStat );
//STRIP001                  break;
//STRIP001              } else r.skip(); // wird bei Einfuegen ignoriert
//STRIP001              break;
//STRIP001          case SWGINF_END:
//STRIP001              return;
//STRIP001          case SWGINF_LAYOUTPR: {
//STRIP001 //JP 25.04.95: SetLayoutPrtName gibts nicht mehr
//STRIP001              ParseText();
//STRIP001              } break;
//STRIP001          default:
//STRIP001              // wird ignoriert
//STRIP001              r.skip();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////


//STRIP001 Color SwSwgReader::InColor()
//STRIP001 {
//STRIP001  USHORT red, green, blue;
//STRIP001  r >> red >> green >> blue;
//STRIP001  Color aClr( BYTE(red >> 8), BYTE(green >> 8), BYTE( blue >> 8) );
//STRIP001  return aClr;
//STRIP001
//STRIP001 }


//STRIP001 void SwSwgReader::InPen(USHORT& nWidth, Color& rCol)
//STRIP001 {
//STRIP001  BYTE cStyle;
//STRIP001  r >> cStyle >> nWidth;
//STRIP001  rCol = InColor();
//STRIP001 }


//STRIP001 Color SwSwgReader::InBrush()
//STRIP001 {
//STRIP001  BYTE cStyle, cTransparent;
//STRIP001  r >> cStyle >> cTransparent;
//STRIP001
//STRIP001 //   Brush aBr( (BrushStyle) cStyle );
//STRIP001 //   aBr.SetTransparent( BOOL( cTransparent ) );
//STRIP001 //   aBr.SetColor( InColor() );
//STRIP001  Color aCol(InColor());
//STRIP001  Color aTmpFillColor(InColor());
//STRIP001
//STRIP001  return aCol;
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////


//STRIP001 void SwSwgReader::InFtnInfo()
//STRIP001 {
//STRIP001  SwFtnInfo aFtn;
//STRIP001  aFtn = pDoc->GetFtnInfo();
//STRIP001  aFtn.aQuoVadis = GetText();
//STRIP001  aFtn.aErgoSum = GetText();
//STRIP001  //Ab der 3.0 sind nur noch max. 30 Zeichen erlaubt.
//STRIP001  aFtn.aQuoVadis.Erase( 30 );
//STRIP001  aFtn.aErgoSum. Erase( 30 );
//STRIP001
//STRIP001  BYTE ePos, eNum, eType;
//STRIP001  USHORT nDesc, nCollIdx;
//STRIP001  if( ( aHdr.nVersion >= SWG_VER_COMPAT ) && ( r.next() != SWG_DATA ) )
//STRIP001  {
//STRIP001      Error(); return;
//STRIP001  }
//STRIP001  r >> ePos >> eNum >> eType >> nDesc;
//STRIP001  if( aHdr.nVersion >= SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      r >> nCollIdx;
//STRIP001      r.skip();
//STRIP001      if( nCollIdx != IDX_NO_VALUE )
//STRIP001      {
//STRIP001          nCollIdx |= IDX_COLLECTION;
//STRIP001          SwTxtFmtColl* pColl = (SwTxtFmtColl*) FindFmt( nCollIdx, 0 );
//STRIP001          if( pColl )
//STRIP001              aFtn.SetFtnTxtColl( *pColl );
//STRIP001      }
//STRIP001  }
//STRIP001  if( nLay )
//STRIP001      nLay = pLayIdx[ nDesc ].nActualIdx;
//STRIP001  aFtn.ChgPageDesc( (SwPageDesc*)&pDoc->GetPageDesc( nLay ) );
//STRIP001
//STRIP001  aFtn.ePos = (SwFtnPos) ePos;
//STRIP001  aFtn.eNum = (SwFtnNum) eNum;
//STRIP001  aFtn.aFmt.SetNumberingType(eType);
//STRIP001  pDoc->SetFtnInfo( aFtn );
//STRIP001  r.next();
//STRIP001 }

// Aufdroeseln des Comment-Records fuer kuenftige Erweiterungen

//STRIP001 void SwSwgReader::InComment()
//STRIP001 {
//STRIP001  BYTE cType;
//STRIP001  USHORT nVal;
//STRIP001  r >> cType;
//STRIP001  switch( cType ) {
//STRIP001      case SWG_XFTNCOLL: {
//STRIP001          // Fussnoten-Erweiterung: Nummer der TxtColl
//STRIP001          r >> nVal;
//STRIP001          nVal &= IDX_COLLECTION;
//STRIP001          SwTxtFmtColl* pColl = (SwTxtFmtColl*) FindFmt( nVal, 0 );
//STRIP001          if( pColl )
//STRIP001          {
//STRIP001              SwFtnInfo aFtn;
//STRIP001              aFtn = pDoc->GetFtnInfo();
//STRIP001              aFtn.SetFtnTxtColl( *pColl );
//STRIP001              pDoc->SetFtnInfo( aFtn );
//STRIP001          }
//STRIP001      } break;
//STRIP001      default:
//STRIP001          r.skip();
//STRIP001  }
//STRIP001  r.next();
//STRIP001 }

///////////////////////////////////////////////////////////////////////////

// Einlesen der statischen DocInfo

//STRIP001 static void InSfxStamp( swistream& r, SfxStamp& rStamp,
//STRIP001                      rtl_TextEncoding eCharSet )
//STRIP001 {
//STRIP001  r.long4();
//STRIP001  long nDate, nTime;
//STRIP001  sal_Char buf[ 32 ];
//STRIP001  r >> nDate >> nTime;
//STRIP001  r.get( buf, 32 );
//STRIP001  r.long3();
//STRIP001  Date d( nDate );
//STRIP001  Time t( nTime );
//STRIP001  String aName( buf, eCharSet );
//STRIP001  rStamp.SetTime( DateTime( d, t ) );
//STRIP001  rStamp.SetName( aName );
//STRIP001 }

//STRIP001 static void InSfxDocString
//STRIP001 ( swistream& r, String& rText, short nLen, rtl_TextEncoding eCharSet )
//STRIP001 {
//STRIP001  sal_Char buf[ 256 ];
//STRIP001  r.get( buf, nLen );
//STRIP001  String sTmp( buf, eCharSet );
//STRIP001  rText = sTmp;
//STRIP001 }

//STRIP001 void SwSwgReader::InStaticDocInfo( SfxDocumentInfo& rInfo )
//STRIP001 {
//STRIP001  long pos;
//STRIP001  USHORT n, i;
//STRIP001  BYTE cGUIType, cCharSet;
//STRIP001  // TODO: unicode: is this correct?
//STRIP001  rtl_TextEncoding eCharSet = gsl_getSystemTextEncoding();
//STRIP001  SfxStamp aStamp;
//STRIP001  String aText;
//STRIP001
//STRIP001  while( r.good() )
//STRIP001  {
//STRIP001      switch( r.next() )
//STRIP001      {
//STRIP001          case SWGINF_END:
//STRIP001              return;
//STRIP001          case SWGINF_SAVEINFO:
//STRIP001              pos = r.tell();
//STRIP001              r.skip();
//STRIP001              if( r.peek() == SWGINF_EXTINFO )
//STRIP001              {
//STRIP001                  r.next();
//STRIP001                  r >> cGUIType
//STRIP001                    >> cCharSet;
//STRIP001                  eCharSet = (rtl_TextEncoding) cCharSet;
//STRIP001              }
//STRIP001              r.seek( pos );
//STRIP001              InSfxStamp( r, aStamp, eCharSet );
//STRIP001              rInfo.SetCreated( aStamp );
//STRIP001              InSfxStamp( r, aStamp, eCharSet );
//STRIP001              rInfo.SetChanged( aStamp );
//STRIP001              InSfxStamp( r, aStamp, eCharSet );
//STRIP001              rInfo.SetPrinted( aStamp );
//STRIP001              // SwSwgInfo-Felder II: Titel, Autor etc
//STRIP001              InSfxDocString( r, aText, 64, eCharSet );
//STRIP001              rInfo.SetTitle( aText );
//STRIP001              InSfxDocString( r, aText, 64, eCharSet );
//STRIP001              rInfo.SetTheme( aText );
//STRIP001              InSfxDocString( r, aText, 256, eCharSet );
//STRIP001              rInfo.SetComment( aText );
//STRIP001              InSfxDocString( r, aText, 128, eCharSet );
//STRIP001              rInfo.SetKeywords( aText );
//STRIP001              // SwSwgInfo-Felder III: User-Keys
//STRIP001              r >> n;
//STRIP001              for( i = 0; i < n; i++ )
//STRIP001              {
//STRIP001                  String aKeys;
//STRIP001                  InSfxDocString( r, aText, 20, eCharSet );
//STRIP001                  InSfxDocString( r, aKeys, 20, eCharSet );
//STRIP001                  SfxDocUserKey aKey( aText, aKeys );
//STRIP001                  rInfo.SetUserKey( aKey, i );
//STRIP001              }
//STRIP001              break;
//STRIP001          default:
//STRIP001              // wird ignoriert
//STRIP001              r.skip();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 }

//STRIP001 void SwSwgReader::InDynamicDocInfo( SfxDocumentInfo& rInfo )
//STRIP001 {
//STRIP001  // Record suchen:
//STRIP001  if( r.next() == SWG_DOCUMENT )
//STRIP001  {
//STRIP001      r.skip();
//STRIP001      if( r.peek() == SWG_DYNDOCINFO )
//STRIP001      {
//STRIP001          r.next();
//STRIP001          long nextrec = r.getskip();
//STRIP001          long pos, d, t;
//STRIP001          BYTE cFlags = 0;
//STRIP001          while( r.tell() < nextrec && r.good() )
//STRIP001          {
//STRIP001              String aText;
//STRIP001              switch( r.next() )
//STRIP001              {
//STRIP001                  case SWGINF_TEMPLATE:
//STRIP001                      pos = r.getskip();
//STRIP001                      aText = GetText();
//STRIP001                      r.long4();
//STRIP001                      r >> d >> t;
//STRIP001                      r.long3();
//STRIP001                      if( r.tell() < pos ) r >> cFlags;
//STRIP001                      rInfo.SetTemplateDate( DateTime( Date( d ), Time( t ) ) );
//STRIP001                      rInfo.SetTemplateName( aText );
//STRIP001                      rInfo.SetTemplateFileName( aFileName );
//STRIP001                      rInfo.SetQueryLoadTemplate( BOOL( ( cFlags & 0x01 ) != 0 ) );
//STRIP001                      r.skip( pos ); break;
//STRIP001                  default:
//STRIP001                      r.skip();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwSwgReader::LoadDocInfo( SfxDocumentInfo& rInfo )
//STRIP001 {
//STRIP001  FileHeader aFile;
//STRIP001  long pos0 = r.tell();
//STRIP001
//STRIP001  memset( &aFile, 0, sizeof aFile );
//STRIP001  r.get( &aFile, 4 );
//STRIP001  // Die Signatur sollte schon stimmen!!!
//STRIP001  // Aber bitte nur die ersten drei Zeichen, um nicht abwaertskompatible
//STRIP001  // Versionen erkennen zu koennen.
//STRIP001  if( memcmp( ( const void*) &aFile.nSignature, SWG_SIGNATURE, 3 ) )
//STRIP001      return FALSE;
//STRIP001  r.long4();
//STRIP001  r >> aFile.nVersion
//STRIP001    >> aFile.nFlags
//STRIP001    >> aFile.nFree1
//STRIP001    >> aFile.nDocInfo;
//STRIP001  r.get( aFile.cPasswd, 16 );
//STRIP001  r.long3();
//STRIP001 //   rInfo.SetPasswd( BOOL( ( aFile.nFlags & SWGF_HAS_PASSWD ) != 0 ) );
//STRIP001  rInfo.SetPortableGraphics( BOOL( ( aFile.nFlags & SWGF_PORT_GRAF ) != 0 ) );
//STRIP001
//STRIP001  // Passwort in Stream eintragen
//STRIP001  if( aFile.nFlags & SWGF_HAS_PASSWD )
//STRIP001      r.copypasswd( aFile.cPasswd );
//STRIP001  // Die statische DocInfo lesen
//STRIP001  // Hot fix fuer Bug #4955 (Textbausteine mit geloeschten Bereichen)
//STRIP001  if( !aFile.nDocInfo ) aFile.nDocInfo = 0x5B;
//STRIP001  if( aFile.nVersion >= SWG_VER_FMTNAME )
//STRIP001  {
//STRIP001      r.seek( aFile.nDocInfo - 4 );
//STRIP001      InStaticDocInfo( rInfo );
//STRIP001  }
//STRIP001  if( aFile.nVersion >= SWG_VER_DOCINFO )
//STRIP001  {
//STRIP001      r.seek( pos0 + 32 /* sizeof( FileHeader ) in Datei */ );
//STRIP001      InDynamicDocInfo( rInfo );
//STRIP001      r.seek( pos0 );
//STRIP001  }
//STRIP001  return BOOL( r.good() );
//STRIP001 }



}
