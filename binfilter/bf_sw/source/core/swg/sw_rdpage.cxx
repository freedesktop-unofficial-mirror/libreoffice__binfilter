/*************************************************************************
 *
 *  $RCSfile: sw_rdpage.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:33:14 $
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

#include "doc.hxx"

#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif

#include "rdswg.hxx"
#include "pagedesc.hxx"
#include "swgpar.hxx"       // SWGRD_XXX
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif

//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

// Hinzufuegen eines neuen PageDesc-Links

//STRIP001 void SwSwgReader::AddPageDescLink( const String& rName, USHORT nOff )
//STRIP001 {
//STRIP001  // Eventuell das Flag-Bit setzen,
//STRIP001  // dass Seitennummern vorkommen
//STRIP001  // Dies wird fuer aeltere Docs benoetigt
//STRIP001  if( nOff & 0x7FFF )
//STRIP001      aFile.nFlags |= SWGF_HAS_PGNUMS,
//STRIP001      pDoc->SetPageNums();
//STRIP001  PageDescLink* p = new PageDescLink( rName, nOff );
//STRIP001  p->pLink = pPageLinks;
//STRIP001  pPageLinks = p;
//STRIP001
//STRIP001 }

// Aufloesen aller Seitenbeschreibungs-Links

//STRIP001 void SwSwgReader::ResolvePageDescLinks()
//STRIP001 {
//STRIP001  while( pPageLinks )
//STRIP001  {
//STRIP001      PageDescLink* p = pPageLinks;
//STRIP001      pPageLinks = p->pLink;
//STRIP001      USHORT nArrLen = pDoc->GetPageDescCnt();
//STRIP001      for( USHORT i = 0; i < nArrLen; i++)
//STRIP001      {
//STRIP001          const SwPageDesc& rDesc = pDoc->GetPageDesc( i );
//STRIP001          if( rDesc.GetName() == String( *p ) )
//STRIP001              break;
//STRIP001      }
//STRIP001      // falls nicht da, Standardlayout nehmen
//STRIP001      if( i == nArrLen ) i = 0;
//STRIP001      // Bit 0x8000 im Offset besagt, dass bAuto zu setzen ist
//STRIP001      SwFmtPageDesc aAttr( &pDoc->GetPageDesc( i ) );
//STRIP001      aAttr.SetNumOffset( p->nOffset & 0x7FFF );
//STRIP001      if( p->cFmt )
//STRIP001          p->pFmt->SetAttr( aAttr );
//STRIP001      else
//STRIP001          p->pSet->Put( aAttr );
//STRIP001      delete p;
//STRIP001  }
//STRIP001 }

// Suchen einer Seitenbeschreibung

//STRIP001 SwPageDesc& SwSwgReader::FindPageDesc( USHORT nIdx )
//STRIP001 {
//STRIP001  PageDescInfo* pDescs = &pLayIdx[ nIdx ];
//STRIP001  return pDoc->_GetPageDesc( pDescs->nActualIdx );
//STRIP001
//STRIP001 }

// Fussnoten-Info

//STRIP001 void SwSwgReader::InPageFtnInfo( SwPageFtnInfo& rFtn )
//STRIP001 {
//STRIP001  long nHeight, nTopDist, nBottomDist, nNum, nDenom;
//STRIP001  short nAdjust, nPenWidth;
//STRIP001  r >> nHeight
//STRIP001    >> nTopDist
//STRIP001    >> nBottomDist
//STRIP001    >> nAdjust
//STRIP001    >> nNum >> nDenom
//STRIP001    >> nPenWidth;
//STRIP001  Color aPenColor = InColor();
//STRIP001  rFtn.SetHeight( (SwTwips) nHeight );
//STRIP001  rFtn.SetTopDist( (SwTwips) nTopDist );
//STRIP001  rFtn.SetBottomDist( (SwTwips) nBottomDist );
//STRIP001  rFtn.SetAdj( (SwFtnAdj) nAdjust );
//STRIP001  Fraction f( nNum, nDenom );
//STRIP001  rFtn.SetWidth( f );
//STRIP001  rFtn.SetLineColor(aPenColor );
//STRIP001  rFtn.SetLineWidth(nPenWidth );
//STRIP001  r.next();
//STRIP001 }

// Seiten-Deskriptor

//STRIP001 #define FORCEREAD ( SWGRD_PAGEFMTS & SWGRD_FORCE )

//STRIP001 void SwSwgReader::InPageDesc( short nIdx )
//STRIP001 {
//STRIP001  long nextrec = r.getskip();
//STRIP001  short nFollow, nUsedOn;
//STRIP001  BYTE bHdrShare, bFtrShare, bLandscape = FALSE;
//STRIP001  USHORT nPoolId = IDX_NO_VALUE;
//STRIP001  sal_Char nNumType;
//STRIP001  String aName;
//STRIP001
//STRIP001  if( !r ) return;
//STRIP001
//STRIP001  aName = GetText( FALSE );
//STRIP001  if( ( aHdr.nVersion >= SWG_VER_COMPAT ) && ( r.next() != SWG_DATA ) )
//STRIP001  {
//STRIP001      Error(); return;
//STRIP001  }
//STRIP001  r >> nFollow >> nNumType >> nUsedOn >> bHdrShare >> bFtrShare;
//STRIP001  if( aHdr.nVersion >= SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      BYTE cFlags;
//STRIP001      r >> cFlags;
//STRIP001      if( aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001          r >> nPoolId;
//STRIP001      // Korrektur fuer aeltere Dokumente
//STRIP001      if( aHdr.nVersion <= SWG_VER_FRAMES3 )
//STRIP001      {
//STRIP001          nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_PAGEDESC );
//STRIP001          if( nPoolId == USHRT_MAX ) nPoolId = IDX_NO_VALUE;
//STRIP001      }
//STRIP001      else if( nPoolId < IDX_SPECIAL )
//STRIP001          // USER-Feld verkleinern
//STRIP001          nPoolId &= 0xBFFF;
//STRIP001      r.skip();
//STRIP001      bLandscape = BOOL( ( cFlags & 0x01 ) != 0 );
//STRIP001  }
//STRIP001
//STRIP001  PageDescInfo* pDescs = pLayIdx;
//STRIP001  // Ist es eine Poolvorlage und ist diese evtl. bereits eingelesen?
//STRIP001  // Dann das Pool-ID loeschen
//STRIP001  if( nPoolId != IDX_NO_VALUE )
//STRIP001    for( USHORT i = 0; i < nLay; i++, pDescs++ )
//STRIP001    {
//STRIP001      if( pDescs->nPoolId == nPoolId )
//STRIP001      {
//STRIP001          nPoolId = IDX_NO_VALUE; break;
//STRIP001      }
//STRIP001    }
//STRIP001  pDescs = &pLayIdx[ nIdx ];
//STRIP001  SwPageDesc* pDesc = NULL;
//STRIP001  // Ist bei alten Dokumenten der Name ein Poolformatname?
//STRIP001  if( aHdr.nVersion < SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_PAGEDESC );
//STRIP001      if( nPoolId == USHRT_MAX ) nPoolId = IDX_NO_VALUE;
//STRIP001  }
//STRIP001  if( nPoolId != IDX_NO_VALUE )
//STRIP001  {
//STRIP001      // Es ist eine Pool-Beschreibung. Falls eingefuegt wird,
//STRIP001      // dann bitte diese Beschreibung verwenden und nix weiter machen
//STRIP001      if( ( nOptions & FORCEREAD ) != FORCEREAD ) {
//STRIP001          // Ist sie ueberhaupt da?
//STRIP001          USHORT nArrLen = pDoc->GetPageDescCnt();
//STRIP001          for( USHORT n = 0; n < nArrLen; n++ )
//STRIP001          {
//STRIP001              pDesc = &pDoc->_GetPageDesc( n );
//STRIP001              if( pDesc->GetPoolFmtId() == nPoolId )
//STRIP001              {
//STRIP001                  nIdx = n; break;
//STRIP001              }
//STRIP001          }
//STRIP001          if( n < nArrLen )
//STRIP001          {
//STRIP001              r.skip( nextrec ); r.next();
//STRIP001              pDescs->nPoolId = nPoolId;
//STRIP001              pDescs->nActualIdx = nIdx;
//STRIP001              pDescs->nFollow = nFollow;
//STRIP001              // Formate muessen nicht registriert werden,
//STRIP001              // da Frames nie geladen werden, wenn es sich um das
//STRIP001              // Einfuegen von Text handelt
//STRIP001              return;
//STRIP001          } else pDesc = NULL;
//STRIP001      } else {
//STRIP001          // Neues Dokument: PageDesc anfordern und Index finden
//STRIP001          pDesc = pDoc->GetPageDescFromPool( nPoolId );
//STRIP001          USHORT nArrLen = pDoc->GetPageDescCnt();
//STRIP001          for( USHORT n = 0; n < nArrLen; n++ )
//STRIP001          {
//STRIP001              if( &pDoc->GetPageDesc( n ) == pDesc )
//STRIP001              {
//STRIP001                  nIdx = n; break;
//STRIP001              }
//STRIP001          }
//STRIP001          ASSERT( n < nArrLen, "Pool-PageDesc nicht gefunden" );
//STRIP001      }
//STRIP001  } else {
//STRIP001      // Keine Poolvorlage:
//STRIP001      // Gibt es diese Beschreibung bereits?
//STRIP001      USHORT nArrLen = pDoc->GetPageDescCnt();
//STRIP001      for( USHORT n = 0; n < nArrLen; n++ )
//STRIP001      {
//STRIP001          SwPageDesc& rCur = pDoc->_GetPageDesc( n );
//STRIP001          if( rCur.GetName() == aName )
//STRIP001          {
//STRIP001              // Ueberplaetten von Vorlagen?
//STRIP001              // Dank eines Bugs von OT koennen Vorlagen mehrfach in
//STRIP001              // einem Doc vorkommen. Da Seitenvorlagen "by name"
//STRIP001              // referenziert werden, ist dies fuer den Textteil OK.
//STRIP001              // Nur die Layout-Infos koennen u.U. baden gehen.
//STRIP001              if( ( bNew && nIdx != 0 )
//STRIP001                || ( ( nOptions & FORCEREAD ) != FORCEREAD ) )
//STRIP001              {
//STRIP001                  // Dann den Index eintragen und abbrechen
//STRIP001                  r.skip( nextrec ); r.next();
//STRIP001                  pDescs->nPoolId = nPoolId;
//STRIP001                  pDescs->nActualIdx = n;
//STRIP001                  pDescs->nFollow = nFollow;
//STRIP001                  // Formate muessen nicht registriert werden,
//STRIP001                  // da Frames nie geladen werden, wenn es sich um das
//STRIP001                  // Einfuegen von Text handelt
//STRIP001                  return;
//STRIP001              } else {
//STRIP001                  nIdx = n;
//STRIP001                  pDesc = &rCur;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( !pDesc )
//STRIP001  {
//STRIP001      nIdx = pDoc->MakePageDesc( aName );
//STRIP001      pDesc = &pDoc->_GetPageDesc( nIdx );
//STRIP001  }
//STRIP001  pDescs->nPoolId = nPoolId;
//STRIP001  pDescs->nActualIdx = nIdx;
//STRIP001  pDescs->nFollow = nFollow;
//STRIP001  SvxNumberType aType;
//STRIP001  aType.SetNumberingType(nNumType);
//STRIP001  pDesc->SetNumType( aType );
//STRIP001 //   Steckt im UseOn drin
//STRIP001 //   pDesc->ChgHeaderShare( BOOL( bHdrShare ) );
//STRIP001 //   pDesc->ChgFooterShare( BOOL( bFtrShare ) );
//STRIP001  pDesc->WriteUseOn( UseOnPage( nUsedOn ) );
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001  pDesc->ResetAllMasterAttr();
//STRIP001  pDesc->ResetAllLeftAttr();
//STRIP001  r.next();
//STRIP001  // Header und Footer sind Shared-Formate
//STRIP001  nStatus |= SWGSTAT_SHAREDFMT;
//STRIP001  while( !bDone )
//STRIP001    switch( r.cur() ) {
//STRIP001      case SWG_FOOTINFO:
//STRIP001          // Vorsicht: SWG_FOOTINFO kann auch auf dem TopLevel
//STRIP001          // vorkommen!
//STRIP001          if( r.tell() > nextrec ) bDone = TRUE;
//STRIP001          else InPageFtnInfo( pDesc->GetFtnInfo() ); break;
//STRIP001      case SWG_MASTERFMT:
//STRIP001          InFormat( &pDesc->GetMaster() );
//STRIP001          RegisterFmt( pDesc->GetMaster() );
//STRIP001          break;
//STRIP001      case SWG_LEFTFMT:
//STRIP001          InFormat( &pDesc->GetLeft() );
//STRIP001          RegisterFmt( pDesc->GetLeft() );
//STRIP001          break;
//STRIP001      case SWG_JOBSETUP:
//STRIP001      case SWG_COMMENT:
//STRIP001          r.skipnext(); break;
//STRIP001      default:
//STRIP001          bDone = TRUE;
//STRIP001  }
//STRIP001  nStatus &= ~SWGSTAT_SHAREDFMT;
//STRIP001
//STRIP001  // ST special: 1 Bit des Masterfmts wird fuer Landscape verwendet!
//STRIP001  // Dies auch nur bis Version 1.x!
//STRIP001  if( aHdr.nVersion < SWG_VER_COMPAT )
//STRIP001      bLandscape = BOOL( nFlagBits & 0x01 );
//STRIP001  pDesc->SetLandscape( bLandscape );
//STRIP001  if( nPoolId != IDX_NO_VALUE )
//STRIP001      pDesc->SetPoolFmtId( nPoolId );
//STRIP001
//STRIP001  // Hdr/Ftr-Formate umsetzen:
//STRIP001  // Gleichzeitig muessen (bei aelteren Dateien) die vorher
//STRIP001  // eingelesenen Left-Hdr/Ftr-Formate neu registriert werden,
//STRIP001  // damit die Frame-Leseroutinen den rechten Bezug haben.
//STRIP001  // Die erste Frame-Version darf gar nicht mehr laden, da die Content-
//STRIP001  // Section des ueberbratenen Formats verschwindet!
//STRIP001  if( pDesc->IsHeaderShared() )
//STRIP001  {
//STRIP001      const SwFmtHeader& rFmtM = pDesc->GetMaster().GetHeader();
//STRIP001      const SwFmtHeader& rFmtL = pDesc->GetLeft().GetHeader();
//STRIP001      const SwFmt* pFmt1 = rFmtL.GetHeaderFmt();
//STRIP001      const SwFmt* pFmt2 = rFmtM.GetHeaderFmt();
//STRIP001      if( pFmt1 && pFmt2 )
//STRIP001          ReRegisterFmt( *pFmt1, *pFmt2 );
//STRIP001      pDesc->GetLeft().SetAttr( rFmtM );
//STRIP001  }
//STRIP001  if( pDesc->IsFooterShared() )
//STRIP001  {
//STRIP001      const SwFmtFooter& rFmtM = pDesc->GetMaster().GetFooter();
//STRIP001      const SwFmtFooter& rFmtL = pDesc->GetLeft().GetFooter();
//STRIP001      const SwFmt* pFmt1 = rFmtL.GetFooterFmt();
//STRIP001      const SwFmt* pFmt2 = rFmtM.GetFooterFmt();
//STRIP001      if( pFmt1 && pFmt2 )
//STRIP001          ReRegisterFmt( *pFmt1, *pFmt2 );
//STRIP001      pDesc->GetLeft().SetAttr( rFmtM );
//STRIP001  }
//STRIP001 }


//STRIP001 void SwSwgReader::InPageDescs()
//STRIP001 {
//STRIP001  USHORT nDesc;
//STRIP001  r >> nDesc;
//STRIP001  r.next();
//STRIP001  if( nDesc > 0 )
//STRIP001  {
//STRIP001      nLay = nDesc;
//STRIP001      PageDescInfo* p =
//STRIP001      pLayIdx = new PageDescInfo[ nDesc ];
//STRIP001      // einlesen
//STRIP001      for( USHORT i = 0; i < nDesc && r.good(); i++, p++ )
//STRIP001      {
//STRIP001          p->nActualIdx = 0;
//STRIP001          p->nPoolId =
//STRIP001          p->nFollow = IDX_NO_VALUE;
//STRIP001      }
//STRIP001      for( i = 0; i < nDesc && r.good(); i++ )
//STRIP001          InPageDesc( i );
//STRIP001      // Follows aufloesen
//STRIP001      p = pLayIdx;
//STRIP001      for( i = 0; i < nDesc; i++, p++ )
//STRIP001      {
//STRIP001          if( p->nFollow != IDX_NO_VALUE )
//STRIP001          {
//STRIP001              SwPageDesc& rDesc = pDoc->_GetPageDesc( p->nActualIdx );
//STRIP001              rDesc.SetFollow
//STRIP001              ( &pDoc->GetPageDesc( LayoutIdx( p->nFollow ) ) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else Error();
//STRIP001 }



