/*************************************************************************
 *
 *  $RCSfile: sw_rdfmts.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:33:12 $
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

#include <hintids.hxx>

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>
#endif
#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_TSPTITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#ifndef _NUMRULE_HXX //autogen
#include <numrule.hxx>
#endif
#include "doc.hxx"
#include "docary.hxx"
#include "rdswg.hxx"
#include "swgpar.hxx"       // SWGRD_xxx-Flags
#include "poolfmt.hxx"
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif

// Maximale Anzahl verarbeitbarer Formate

//STRIP001 #define MAXFMTS (USHORT) ( 65000L / sizeof( FmtInfo ) )

// Diese Klasse steht als leerer Format-Container zur Verfuegung,
// der beliebig gefuellt werden kann.

//STRIP001 class SwFmtContainer : public SwFmt
//STRIP001 {
//STRIP001 public:
//STRIP001  SwFmtContainer( SwDoc& rDoc )
//STRIP001  : SwFmt( rDoc.GetAttrPool(), String(), RES_CHRATR_BEGIN, RES_GRFATR_END,
//STRIP001           0, 0 )
//STRIP001  {}
//STRIP001 };

//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

//STRIP001 static SwFmt* _GetUserPoolFmt( USHORT nId, const SvPtrarr* pFmtArr );

// Formatbeschreibungen

// Einlesen eines AttrSets
// Dies war frueher mal ein AutoFormat und ist als solches in der
// Datei abgelegt. Die Autoformat-Hierarchien werden hier entsprechend
// aufgeloest. Die Attribute werden als SwAttrs-Array registriert.
// Returnwert: das Format-ID des AttrSets

//STRIP001 USHORT SwSwgReader::InAttrSet( SwAttrSet& rSet )
//STRIP001 {
//STRIP001  // Format einlesen
//STRIP001  USHORT nFmtId, nDerived;
//STRIP001  if( aHdr.nVersion >= SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      if( r.next() != SWG_DATA ) Error();
//STRIP001      else r >> nDerived >> nFmtId;
//STRIP001      r.skipnext();   // Rest kann weg
//STRIP001      r.skip();       // Name kann weg
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      BYTE cFlags;
//STRIP001      r >> nDerived >> nFmtId;
//STRIP001      r.next(); r.skip(); // Name kann weg
//STRIP001      r >> cFlags;
//STRIP001  }
//STRIP001  // Attribute einlesen
//STRIP001  SfxItemSet* pSet = rSet.Clone( FALSE );
//STRIP001  if( r.next() == SWG_COMMENT ) r.skipnext();
//STRIP001  if( r.cur() == SWG_FMTHINTS )
//STRIP001  {
//STRIP001      UINT16 nHt;
//STRIP001      r >> nHt;
//STRIP001 //       else
//STRIP001      {
//STRIP001          r.next();
//STRIP001          for( USHORT i = 0; i < nHt && r.good(); i++ )
//STRIP001          {
//STRIP001              InHint( *pSet );
//STRIP001              r.next();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( ( nDerived & IDX_TYPEMASK ) == IDX_NAMEDFMT )
//STRIP001      nDerived = IDX_DFLT_VALUE;
//STRIP001  const SfxItemSet* pParent =
//STRIP001      ( nDerived == IDX_DFLT_VALUE || nDerived == IDX_NO_VALUE )
//STRIP001                       ? NULL : FindAttrSet( nDerived );
//STRIP001  pSet->SetParent( pParent );
//STRIP001  rSet.Put( *pSet );
//STRIP001  RegisterAttrSet( pSet, nFmtId );
//STRIP001  if( pParent )
//STRIP001      FillAttrSet( rSet, nDerived );
//STRIP001  return nFmtId;
//STRIP001 }

//STRIP001 void SwSwgReader::FillAttrSet( SwAttrSet& rSet, USHORT nFmtId )
//STRIP001 {
//STRIP001  const SfxItemSet* pParent =
//STRIP001      ( nFmtId == IDX_DFLT_VALUE || nFmtId == IDX_NO_VALUE )
//STRIP001      ? NULL : FindAttrSet( nFmtId );
//STRIP001  // Das uebergebene AttrSet wird mit allen Attributen gefuellt
//STRIP001  while( pParent )
//STRIP001  {
//STRIP001      if( pParent->Count() )
//STRIP001      {
//STRIP001          SfxItemIter aIter( *pParent );
//STRIP001          const SfxPoolItem* pAttr = aIter.GetCurItem();
//STRIP001          for( USHORT i = 0; i < pParent->Count(); i++ )
//STRIP001          {
//STRIP001              // nur setzen, wenn nicht frisch eingelesen!
//STRIP001              if( rSet.GetItemState( pAttr->Which(), FALSE ) != SFX_ITEM_SET )
//STRIP001                  rSet.Put( *pAttr );
//STRIP001              pAttr = aIter.NextItem();
//STRIP001          }
//STRIP001      }
//STRIP001      pParent = pParent->GetParent();
//STRIP001  }
//STRIP001 }

// Einlesen des Attribut-Sets eines CntntNodes

//STRIP001 USHORT SwSwgReader::InAttrSet( SwCntntNode& rNd )
//STRIP001 {
//STRIP001  USHORT nFmtId;
//STRIP001  if( rNd.GetDepends() )
//STRIP001  {
//STRIP001      SwAttrSet aTmpSet( pDoc->GetAttrPool(), aTxtNodeSetRange );
//STRIP001      nFmtId = InAttrSet( aTmpSet );
//STRIP001      if( aTmpSet.Count() )
//STRIP001          rNd.SetAttr( aTmpSet );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !rNd.GetpSwAttrSet() )
//STRIP001          rNd.NewAttrSet( pDoc->GetAttrPool() );
//STRIP001      nFmtId = InAttrSet( *rNd.GetpSwAttrSet() );
//STRIP001  }
//STRIP001  return nFmtId;
//STRIP001 }

// Ein Format einlesen
// Hier wird das Format auch erzeugt.
// Wird auch von Hints verwendet!

//STRIP001 SwFmt* SwSwgReader::InFormat( SwFmt* pFmt, USHORT* pParentId )
//STRIP001 {
//STRIP001  BYTE cFmtKind = r.cur();
//STRIP001  r.getskip();
//STRIP001  BYTE nHelpFid = (BYTE) nHelpFileId;
//STRIP001  USHORT nHelpId = USHRT_MAX;
//STRIP001  BYTE cFlags;
//STRIP001  USHORT nFmtId;
//STRIP001  if( cFmtKind == SWG_FLYFMT ) nFlyLevel++;
//STRIP001  nFmtLvl++;
//STRIP001
//STRIP001  String aName( String::CreateFromAscii("dummy") );
//STRIP001  USHORT nDerived, nPoolId = IDX_NO_VALUE;
//STRIP001  if( aHdr.nVersion >= SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      if( r.next() != SWG_DATA ) Error();
//STRIP001      else r >> nDerived >> nFmtId >> nPoolId;
//STRIP001      // Korrektur fuer aeltere Pool-Ids:
//STRIP001      if( aHdr.nVersion <= SWG_VER_FRAMES3 ) nPoolId = IDX_NO_VALUE;
//STRIP001      else if( nPoolId < IDX_SPECIAL )
//STRIP001          // USER-Feld verkleinern
//STRIP001          nPoolId &= 0xBFFF;
//STRIP001      // Flag Bits:
//STRIP001      // 0x01 - Autoformat (tot)
//STRIP001      // 0x02 - Breakformat (tot)
//STRIP001      // 0x04 - Help ID folgt
//STRIP001      // 0x08 - Pattern-Name fuer Help folgt
//STRIP001      // 0x10 - Format-ID folgt, das bereits den Pattern-Namen hat
//STRIP001      r >> cFlags;
//STRIP001      if( cFlags & 0x04 )
//STRIP001      {
//STRIP001          BYTE n;
//STRIP001          r >> n;
//STRIP001          nHelpId = (UCHAR_MAX == n ? USHRT_MAX : (USHORT)n);
//STRIP001      }
//STRIP001      if( cFlags & 0x08 )
//STRIP001      {
//STRIP001          String aPattern = GetText();
//STRIP001          if( aPattern.Len() )
//STRIP001              nHelpFid = (BYTE) pDoc->SetDocPattern( aPattern );
//STRIP001      }
//STRIP001      if( cFlags & 0x10 )
//STRIP001      {
//STRIP001          USHORT nHelpFmt;
//STRIP001          r >> nHelpFmt;
//STRIP001          SwFmt* pHelpFmt = FindFmt( nHelpFmt, 0 );
//STRIP001          if( pHelpFmt )
//STRIP001              nHelpFid = pHelpFmt->GetPoolHlpFileId();
//STRIP001      }
//STRIP001      r.skip();
//STRIP001      aName = GetText();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      r >> nDerived >> nFmtId;
//STRIP001      aName = GetText();
//STRIP001      r >> cFlags;
//STRIP001  }
//STRIP001  // Freundlicherweise treten wir hier 1 Bit an ST ab, der es
//STRIP001  // im PageDesc benoetigt (Version 1.x)
//STRIP001  nFlagBits = cFlags >> 4;
//STRIP001
//STRIP001  // Format erzeugen
//STRIP001  if( !pFmt ) {
//STRIP001      switch( cFmtKind )
//STRIP001      {
//STRIP001          case SWG_FREEFMT:
//STRIP001              // Freifliegende Frameformate werden von Headers
//STRIP001              // und Footers verwendet.
//STRIP001              pFmt = new SwFrmFmt( pDoc->GetAttrPool(), aName,
//STRIP001                                   pDoc->GetDfltFrmFmt() );
//STRIP001              break;
//STRIP001          case SWG_FRAMEFMT:
//STRIP001              if( IDX_NO_VALUE != nPoolId )
//STRIP001              {
//STRIP001                  if( IsPoolUserFmt( nPoolId ) )
//STRIP001                  {
//STRIP001                      // wir suchen uns das richtige Format
//STRIP001                      if( 0 == ( pFmt = _GetUserPoolFmt( nPoolId,
//STRIP001                                              pDoc->GetFrmFmts() )) )
//STRIP001                          pFmt = _GetUserPoolFmt( nPoolId,
//STRIP001                                              pDoc->GetSpzFrmFmts() );
//STRIP001                      ASSERT( pFmt, "Format not found." );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pFmt = pDoc->GetFrmFmtFromPool( nPoolId );
//STRIP001              }
//STRIP001              if( !pFmt )
//STRIP001              {
//STRIP001                  if( IDX_DFLT_VALUE != nDerived && pParentId )
//STRIP001                  {
//STRIP001                      *pParentId = nDerived & ~IDX_TYPEMASK;
//STRIP001                      SwFmt* pParent = 0;
//STRIP001                      if( pFmts && pFmts[ *pParentId ].cFmt & FINFO_FORMAT )
//STRIP001                          pParent = pFmts[ *pParentId ].pFmt;
//STRIP001                      pFmt = pDoc->MakeFrmFmt( aName, (SwFrmFmt*)pParent );
//STRIP001                      if( pParent )
//STRIP001                          *pParentId = USHRT_MAX;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pFmt = pDoc->MakeFrmFmt( aName,
//STRIP001                              (SwFrmFmt*)FindFmt( nDerived, cFmtKind ));
//STRIP001              }
//STRIP001              else
//STRIP001                  pFmt->ResetAllAttr();
//STRIP001              break;
//STRIP001          case SWG_CHARFMT:
//STRIP001              if( IDX_NO_VALUE != nPoolId )
//STRIP001              {
//STRIP001                  if( IsPoolUserFmt( nPoolId ) )
//STRIP001                      // wir suchen uns das richtige Format
//STRIP001                      pFmt = _GetUserPoolFmt( nPoolId, pDoc->GetCharFmts());
//STRIP001                  else
//STRIP001                      pFmt = pDoc->GetCharFmtFromPool( nPoolId );
//STRIP001              }
//STRIP001              if( !pFmt )
//STRIP001              {
//STRIP001                  if( IDX_DFLT_VALUE != nDerived && pParentId )
//STRIP001                  {
//STRIP001                      *pParentId = nDerived & ~IDX_TYPEMASK;
//STRIP001                      SwFmt* pParent = 0;
//STRIP001                      if( pFmts && pFmts[ *pParentId ].cFmt & FINFO_FORMAT )
//STRIP001                          pParent = pFmts[ *pParentId ].pFmt;
//STRIP001                      pFmt = pDoc->MakeCharFmt( aName, (SwCharFmt*)pParent );
//STRIP001                      if( pParent )
//STRIP001                          *pParentId = USHRT_MAX;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pFmt = pDoc->MakeCharFmt( aName,
//STRIP001                          (SwCharFmt*) FindFmt( nDerived, cFmtKind ) );
//STRIP001              }
//STRIP001              else
//STRIP001                  pFmt->ResetAllAttr();
//STRIP001              break;
//STRIP001          case SWG_FLYFMT:
//STRIP001              pFmt = pDoc->MakeFlyFrmFmt( aName,
//STRIP001                      (SwFlyFrmFmt*) FindFmt( nDerived, cFmtKind ) );
//STRIP001          break;
//STRIP001      }
//STRIP001  } else if( nDerived != IDX_NO_VALUE )
//STRIP001      pFmt->SetDerivedFrom( FindFmt( nDerived, cFmtKind ) );
//STRIP001
//STRIP001  pFmt->nFmtId = nFmtId;
//STRIP001  pFmt->SetPoolHelpId( nHelpId );
//STRIP001  pFmt->SetPoolHlpFileId( nHelpFid );
//STRIP001  pFmt->SetAuto( BOOL( ( cFlags & 0x01 ) != 0 ) );
//STRIP001  if( nPoolId != IDX_NO_VALUE ) pFmt->SetPoolFmtId( nPoolId );
//STRIP001
//STRIP001  if( r.next() == SWG_COMMENT ) r.skipnext();
//STRIP001  if( r.cur() == SWG_FMTHINTS )
//STRIP001  {
//STRIP001      SwAttrSet aSet( pDoc->GetAttrPool(), RES_CHRATR_BEGIN, RES_GRFATR_END );
//STRIP001      short nHt;
//STRIP001      r >> nHt;
//STRIP001      if( nHt < 0 ) Error(), r.skipnext();
//STRIP001      else {
//STRIP001          r.next();
//STRIP001          for( int i = 0; i < nHt && r.good(); i++ )
//STRIP001          {
//STRIP001              InHint( aSet );
//STRIP001              r.next();
//STRIP001              // Wurde ein PageDesc-Attr gelesen? Dann das Format
//STRIP001              // im PageDescLink noch nachtragen!
//STRIP001              if( pPageLinks && !pPageLinks->pFmt )
//STRIP001              {
//STRIP001                  pPageLinks->pFmt = pFmt;
//STRIP001                  pPageLinks->cFmt = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pFmt->SetAttr( aSet );
//STRIP001  }
//STRIP001
//STRIP001  if( cFmtKind == SWG_FLYFMT )
//STRIP001  {
//STRIP001      nFlyLevel--;
//STRIP001      // Hot fix: Umsetzen des Attributes ATT_VAR_SIZE in ATT_MIN_SIZE
//STRIP001      // im Hint SwFmtFrmSize innerhalb von FlyFrames
//STRIP001      // MIB 18.11.96: und ausserdem noch die Groesse und Position
//STRIP001      // an die neuen Abstaende nach aussen anpassen
//STRIP001      SwFrmFmt* pFrmFmt = (SwFrmFmt*) pFmt;
//STRIP001
//STRIP001      const SvxLRSpaceItem& rLRSpace = pFrmFmt->GetLRSpace();
//STRIP001      const SvxULSpaceItem& rULSpace = pFrmFmt->GetULSpace();
//STRIP001
//STRIP001      const SwFmtFrmSize& rFrmSize = pFmt->GetFrmSize();
//STRIP001      Size aConvSize(
//STRIP001          rFrmSize.GetSizeConvertedFromSw31( &rLRSpace,
//STRIP001                                              &rULSpace ) );
//STRIP001
//STRIP001      if( rFrmSize.GetSize() != aConvSize ||
//STRIP001          rFrmSize.GetSizeType() == ATT_VAR_SIZE )
//STRIP001      {
//STRIP001          SwFmtFrmSize aFrmSize( rFrmSize );
//STRIP001          aFrmSize.SetSize( aConvSize );
//STRIP001          if( aFrmSize.GetSizeType() == ATT_VAR_SIZE )
//STRIP001              aFrmSize.SetSizeType( ATT_MIN_SIZE );
//STRIP001
//STRIP001          pFrmFmt->SetAttr( aFrmSize );
//STRIP001      }
//STRIP001
//STRIP001      const SwFmtHoriOrient& rHori = pFmt->GetHoriOrient();
//STRIP001      SwTwips nConvPos =
//STRIP001          rHori.GetPosConvertedFromSw31( &rLRSpace );
//STRIP001      if( rHori.GetPos() != nConvPos )
//STRIP001      {
//STRIP001          SwFmtHoriOrient aHori( rHori );
//STRIP001          aHori.SetPos( nConvPos );
//STRIP001          pFrmFmt->SetAttr( aHori );
//STRIP001      }
//STRIP001
//STRIP001      const SwFmtVertOrient& rVert = pFmt->GetVertOrient();
//STRIP001      nConvPos = rVert.GetPosConvertedFromSw31( &rULSpace );
//STRIP001      if( rVert.GetPos() != nConvPos )
//STRIP001      {
//STRIP001          SwFmtVertOrient aVert( rVert );
//STRIP001          aVert.SetPos( nConvPos );
//STRIP001          pFrmFmt->SetAttr( aVert );
//STRIP001      }
//STRIP001  }
//STRIP001  nFmtLvl--;
//STRIP001  return pFmt;
//STRIP001 }

// Testen, ob ein Format einen Pool-Formatnamen hat.Dies fuehrt bei alten
// Dokumenten dazu, dass das Pool-ID gesetzt wird.

//STRIP001 BOOL SwSwgReader::TestPoolFmt( SwFmt& rFmt, int eFlags )
//STRIP001 {
//STRIP001  USHORT nPoolId = rFmt.GetPoolFmtId();
//STRIP001  if( aHdr.nVersion <= SWG_VER_FRAMES3 && nPoolId == IDX_NO_VALUE )
//STRIP001  {
//STRIP001      nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( rFmt.GetName(),
//STRIP001                      (SwGetPoolIdFromName)eFlags );
//STRIP001      if( nPoolId != USHRT_MAX ) {
//STRIP001          rFmt.SetPoolFmtId( nPoolId );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

// Suchen eines benannten Frame- oder Zeichenformats
// Falls ein gleichnamiges Format existiert wie das uebergebene,
// wird dieser Ptr zurueckgeliefert, sonst NULL,

//STRIP001 static SwFmt* _findframefmt( const SwDoc* pDoc, const SwFmt* pFmt )
//STRIP001 {
//STRIP001  USHORT nArrLen = pDoc->GetFrmFmts()->Count();
//STRIP001  for( USHORT j = 0; j < nArrLen; j++ )
//STRIP001  {
//STRIP001      SwFmt* pFmt2 = (*pDoc->GetFrmFmts())[ j ];
//STRIP001      if( ( pFmt != pFmt2 )
//STRIP001        && ( pFmt->GetName() == pFmt2->GetName() ) )
//STRIP001          return pFmt2;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001
//STRIP001 }


//STRIP001 static SwFmt* _findcharfmt( const SwDoc* pDoc, const SwFmt* pFmt )
//STRIP001 {
//STRIP001  USHORT nArrLen = pDoc->GetCharFmts()->Count();
//STRIP001  for( USHORT j = 0; j < nArrLen; j++ )
//STRIP001  {
//STRIP001      SwFmt* pFmt2 = (*pDoc->GetCharFmts())[ j ];
//STRIP001      if( ( pFmt != pFmt2 )
//STRIP001        && ( pFmt->GetName() == pFmt2->GetName() ) )
//STRIP001          return pFmt2;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001
//STRIP001 }

// Eine Text-Collection einlesen

//STRIP001 void lcl_sw3io__ConvertNumTabStop( SvxTabStopItem& rTStop, long nOffset );

//STRIP001 void SwSwgReader::InTxtFmtColl( short nIdx )
//STRIP001 {
//STRIP001  BOOL bForceRead = BOOL( ( nOptions != SWGRD_NORMAL )
//STRIP001                       && ( nOptions & SWGRD_PARAFMTS )
//STRIP001                       && ( nOptions & SWGRD_FORCE ) );
//STRIP001  long skipit = r.getskip();
//STRIP001  SwTxtFmtColl* pColl = NULL;
//STRIP001  BYTE nLevel;
//STRIP001  USHORT nDerived = IDX_NO_VALUE, nFollow = IDX_NO_VALUE;
//STRIP001  USHORT nCharRef = IDX_NO_VALUE, nPoolId = IDX_NO_VALUE;
//STRIP001  String aName;
//STRIP001  if( aHdr.nVersion >= SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      if( r.next() != SWG_DATA )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      r >> nLevel >> nDerived >> nFollow >> nCharRef >> nPoolId;
//STRIP001      // Korrektur fuer aeltere Pool-Ids:
//STRIP001      if( aHdr.nVersion <= SWG_VER_FRAMES3 ) nPoolId = IDX_DFLT_VALUE;
//STRIP001      else if( nPoolId < IDX_SPECIAL )
//STRIP001          // USER-Feld verkleinern
//STRIP001          nPoolId &= 0xBFFF;
//STRIP001      r.skip();
//STRIP001      aName = GetText();
//STRIP001  } else {
//STRIP001      r >> nLevel;
//STRIP001      aName = GetText();
//STRIP001      r >> nDerived >> nFollow;
//STRIP001      if( aHdr.nVersion >= SWG_VER_COLLREF )
//STRIP001          r >> nCharRef;
//STRIP001  }
//STRIP001
//STRIP001  // Fehler: Unbenannte Vorlage; Defaultnamen vergeben
//STRIP001  if( !aName.Len() )
//STRIP001  {
//STRIP001      static short n = 1;
//STRIP001      aName.AssignAscii( "NoName" );
//STRIP001      aName += String::CreateFromInt32( n++ );
//STRIP001  }
//STRIP001
//STRIP001  // Gibt es diese Coll bereits?
//STRIP001  USHORT nArrLen = pDoc->GetTxtFmtColls()->Count();
//STRIP001  USHORT n;
//STRIP001  // Erste Runde: Ist bei alten Dokumenten der Name ein Poolformatname?
//STRIP001  if( aHdr.nVersion < SWG_VER_COMPAT || nPoolId == IDX_DFLT_VALUE )
//STRIP001  {
//STRIP001      nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_TXTCOLL );
//STRIP001      if( nPoolId == USHRT_MAX ) nPoolId = IDX_NO_VALUE;
//STRIP001  }
//STRIP001  // Zweite Runde: Nach dem Pool-ID suchen ( falls definiert! )
//STRIP001  if( nPoolId != IDX_NO_VALUE && !IsPoolUserFmt( nPoolId ))
//STRIP001    for( n = 0; n < nArrLen; n++ )
//STRIP001    {
//STRIP001      SwTxtFmtColl* pCur = (*pDoc->GetTxtFmtColls())[ n ];
//STRIP001      if( pCur->GetPoolFmtId() == nPoolId )
//STRIP001      {
//STRIP001          pColl = pCur;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  // Dritte Runde: Pool-Vorlage anfordern, falls moeglich
//STRIP001  if( !pColl && nPoolId != IDX_NO_VALUE && !IsPoolUserFmt( nPoolId ))
//STRIP001  {
//STRIP001      pColl = pDoc->GetTxtCollFromPool( nPoolId );
//STRIP001      ASSERT( pColl, "Keine TxtColl fuer PoolId gefunden" );
//STRIP001      if( !pColl )
//STRIP001          nPoolId = IDX_NO_VALUE;
//STRIP001  }
//STRIP001  // Vierte Runde: Ueber den Namen suchen
//STRIP001  if( !pColl )
//STRIP001    for( n = 0; n < nArrLen; n++ )
//STRIP001    {
//STRIP001      SwTxtFmtColl* pCur = (*pDoc->GetTxtFmtColls())[ n ];
//STRIP001      if( pCur->GetName() == aName )
//STRIP001          pColl = pCur;
//STRIP001      // Bei Einfuegen von Vorlagen muss ggf. der Outline-Level geloescht
//STRIP001      // werden, wenn bereits eine Vorlage mit diesem Level existiert.
//STRIP001      if( pCur->GetOutlineLevel() == nLevel )
//STRIP001          nLevel = NO_NUMBERING;
//STRIP001  }
//STRIP001
//STRIP001  // Falls es sie gibt, muessen die Formate neu erstellt werden.
//STRIP001  // In Insert Mode darf die Coll jedoch nicht veraendert werden!
//STRIP001
//STRIP001  if( !pColl || ( nPoolId != IDX_NO_VALUE ) )
//STRIP001  {
//STRIP001      if( !pColl )
//STRIP001      {
//STRIP001          SwTxtFmtColl* pDer = (*pDoc->GetTxtFmtColls())[ 0 ];
//STRIP001          pColl = pDoc->MakeTxtFmtColl( aName, pDer );
//STRIP001      }
//STRIP001      pCollIdx[ nIdx ].nDerived = nDerived | IDX_COLLECTION;
//STRIP001      pCollIdx[ nIdx ].nFollow  = nFollow | IDX_COLLECTION;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Soll die Collection dennoch glesen werden?
//STRIP001      // Durch einen OT-Bug kommt es vor, dass eine Coll mehrfach
//STRIP001      // vorhanden ist. Wenn dies der Fall ist, nicht einlesen.
//STRIP001      BOOL bRead = bForceRead;
//STRIP001      // Die vorhandene Standardvorlage wird bei neuem Doc immer
//STRIP001      // uebergeplaettet.
//STRIP001      if( bNew && ( nIdx == 1 ) ) bRead = TRUE;
//STRIP001      if( !bRead )
//STRIP001      {
//STRIP001          // Also doch nicht einlesen
//STRIP001          pCollIdx[ nIdx ].nDerived =
//STRIP001          pCollIdx[ nIdx ].nFollow = IDX_NO_VALUE;
//STRIP001          pColl->nFmtId = IDX_COLLECTION + nIdx;
//STRIP001          RegisterFmt( *pColl );
//STRIP001          r.skip( skipit ); r.next(); return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pColl->nFmtId = IDX_COLLECTION + nIdx;
//STRIP001  pColl->SetOutlineLevel( nLevel );
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001  pColl->ResetAllAttr();
//STRIP001  // HACK: So lange es die Referenz nicht gibt, wird das benannte
//STRIP001  // Format in das eigene CharFmt kopiert. Muss hier geschehen,
//STRIP001  // da Set() den Inhalt loescht.
//STRIP001  if( nCharRef != IDX_NO_VALUE )
//STRIP001  {
//STRIP001      SwCharFmt* pCfmt = (SwCharFmt*) FindFmt( nCharRef, SWG_CHARFMT );
//STRIP001      if( pCfmt && !pCfmt->IsDefault() )
//STRIP001      {
//STRIP001          SfxItemSet& rColl = (SfxItemSet&) pColl->GetAttrSet();
//STRIP001          rColl.Set( pCfmt->GetAttrSet() );
//STRIP001      }
//STRIP001  }
//STRIP001  r.next();
//STRIP001  while( !bDone ) {
//STRIP001      switch( r.cur() ) {
//STRIP001          case SWG_FRAMEFMT:
//STRIP001          case SWG_PARAFMT:
//STRIP001          case SWG_CHARFMT:
//STRIP001              // Bei CharFmts an den Hot fix denken, dass bei
//STRIP001              // Namensgleichheit mit einem benannten Format
//STRIP001              // kein Format gelesen, sondern statt dessen das
//STRIP001              // benannte Format angebunden wird!
//STRIP001              InFormat( pColl );
//STRIP001              break;
//STRIP001          case SWG_COMMENT:
//STRIP001              if( r.tell() < skipit ) r.skipnext();
//STRIP001          default:
//STRIP001              bDone = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  if( nPoolId != IDX_NO_VALUE )
//STRIP001      pColl->SetPoolFmtId( nPoolId );
//STRIP001
//STRIP001  const SwNumRule *pOutline = pDoc->GetOutlineNumRule();
//STRIP001  if( nLevel < MAXLEVEL && pOutline )
//STRIP001  {
//STRIP001      const SwNumFmt& rFmt = pOutline->Get( nLevel );
//STRIP001      const SvxLRSpaceItem& rLRSpace = pColl->GetLRSpace();
//STRIP001      if( rFmt.GetAbsLSpace() != rLRSpace.GetTxtLeft() ||
//STRIP001          rFmt.GetFirstLineOffset() != rLRSpace.GetTxtFirstLineOfst() )
//STRIP001      {
//STRIP001          SwNumFmt aFmt( rFmt );
//STRIP001          aFmt.SetAbsLSpace( rLRSpace.GetTxtLeft() );
//STRIP001          aFmt.SetFirstLineOffset( rLRSpace.GetTxtFirstLineOfst() );
//STRIP001
//STRIP001          SwNumRule aOutline( *pOutline );
//STRIP001          aOutline.Set( nLevel, aFmt );
//STRIP001          pDoc->SetOutlineNumRule( aOutline );
//STRIP001      }
//STRIP001
//STRIP001 #ifdef NUM_RELSPACE
//STRIP001      // Den linken-Einzug in der Vorlage auf 0 setzen, damit
//STRIP001      // er nicht doppelt gezaehlt wird. Wenn das
//STRIP001      SvxLRSpaceItem aLRSpace( rLRSpace );
//STRIP001      USHORT nOldLSpace = rLRSpace.GetTxtLeft();
//STRIP001      aLRSpace.SetTxtFirstLineOfst( 0 );
//STRIP001      aLRSpace.SetTxtLeft( 0U );
//STRIP001      SwFmt *pParFmt = pColl->DerivedFrom();
//STRIP001      if( pParFmt && pParFmt->GetLRSpace() == aLRSpace )
//STRIP001          pColl->ResetAttr( RES_LR_SPACE );
//STRIP001      else if( aLRSpace != rLRSpace )
//STRIP001          pColl->SetAttr( aLRSpace );
//STRIP001      if( nOldLSpace != 0 )
//STRIP001      {
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == pColl->GetAttrSet().GetItemState(
//STRIP001                                      RES_PARATR_TABSTOP, TRUE, &pItem ))
//STRIP001          {
//STRIP001              SvxTabStopItem aTStop( *(SvxTabStopItem*)pItem );
//STRIP001              lcl_sw3io__ConvertNumTabStop( aTStop, nOldLSpace );
//STRIP001              pColl->SetAttr( aTStop );
//STRIP001          }
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001  RegisterFmt( *pColl );
//STRIP001 }

// Alle Collections einlesen


//STRIP001 void SwSwgReader::InTxtFmtColls()
//STRIP001 {
//STRIP001  r >> nColl;
//STRIP001  if( nColl ) {
//STRIP001      // Format-Indextabelle erzeugen
//STRIP001      TxtCollInfo* p =
//STRIP001      pCollIdx = new TxtCollInfo[ nColl + 1 ];
//STRIP001      for( USHORT i = 0; i <= nColl; i++, p++ )
//STRIP001      {
//STRIP001          p->nDerived =
//STRIP001          p->nFollow  = IDX_NO_VALUE;
//STRIP001      }
//STRIP001      r.next();
//STRIP001      for( i = 1; i <= nColl && r.good(); i++ )
//STRIP001          InTxtFmtColl( i );
//STRIP001      p = pCollIdx + 1;
//STRIP001      for( i = 1; i <= nColl && r.good(); i++, p++ )
//STRIP001      {
//STRIP001          SwTxtFmtColl* pCur = (SwTxtFmtColl*) FindFmt( IDX_COLLECTION + i, 0 );
//STRIP001          if( pCur )
//STRIP001          {
//STRIP001              // Derived setzen
//STRIP001              USHORT nIdx = p->nDerived;
//STRIP001              if( nIdx != IDX_NO_VALUE )
//STRIP001              {
//STRIP001                  // dann ist die Coll abhaengig
//STRIP001                  SwTxtFmtColl* pParent = (SwTxtFmtColl*) FindFmt( nIdx, 0 );
//STRIP001                  pCur->SetDerivedFrom( pParent );
//STRIP001              }
//STRIP001              // Next setzen
//STRIP001              nIdx = p->nFollow;
//STRIP001              if( nIdx != IDX_NO_VALUE )
//STRIP001              {
//STRIP001                  SwTxtFmtColl* pNext = (SwTxtFmtColl*) FindFmt( nIdx, 0 );
//STRIP001                  pCur->SetNextTxtFmtColl( *pNext );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  } else r.next();
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Einlesen der Default- und Autoformate


//STRIP001 void SwSwgReader::InDfltFmts()
//STRIP001 {
//STRIP001  if( !bNew )
//STRIP001  {
//STRIP001      // Einfuegen: Defaultformate lassen!
//STRIP001      r.skipnext();
//STRIP001      return;
//STRIP001  }
//STRIP001  r.next();
//STRIP001  BOOL bDone = FALSE;
//STRIP001  while( !bDone && r.good() )
//STRIP001  {
//STRIP001      switch( r.cur() )
//STRIP001      {
//STRIP001      case SWG_FRAMEFMT:
//STRIP001      case SWG_CHARFMT:
//STRIP001      case SWG_PARAFMT:
//STRIP001      case SWG_GRFFMT:
//STRIP001          {
//STRIP001              SwFmtContainer aContainer( *pDoc );
//STRIP001              InFormat( &aContainer );
//STRIP001              if( aContainer.GetAttrSet().Count() )
//STRIP001              {
//STRIP001                  SfxItemIter aIter( aContainer.GetAttrSet() );
//STRIP001                  while( TRUE )
//STRIP001                  {
//STRIP001                      const SfxPoolItem* pItem = aIter.GetCurItem();
//STRIP001                      pDoc->GetAttrPool().SetPoolDefaultItem( *pItem );
//STRIP001
//STRIP001                      if( aIter.IsAtEnd() )
//STRIP001                          break;
//STRIP001                      pItem = aIter.NextItem();
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          bDone = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

// Einlesen der benannten Formate.

// Die Optionen lassen eine gezielte Auswahl zu.


//STRIP001 void SwSwgReader::InNamedFmts( USHORT nOptions )
//STRIP001 {
//STRIP001  SvPtrarr aFmtArr;   //JP 29.09.95: sind die Parents noch nicht eingelesen
//STRIP001  SvUShorts aIdArr;   // dann am Ende alle Verbinden
//STRIP001
//STRIP001  USHORT i, n;
//STRIP001  r >> n;
//STRIP001  nNamedFmt = 0;
//STRIP001  r.next();
//STRIP001  for( i = 0; i < n && r.good(); i++ )
//STRIP001  {
//STRIP001      BYTE cType = r.cur();
//STRIP001      if( cType < SWG_LEFTFMT || cType > SWG_GRFFMT )
//STRIP001      {
//STRIP001          Error(); break;
//STRIP001      }
//STRIP001      // das geht hier OK, da das Format in jedem Fall gefuellt wird,
//STRIP001      // wenn es durch Text benoetigt werden sollte.
//STRIP001      SwFmt* pFmt = NULL;
//STRIP001      SwFmt* pFmt2;
//STRIP001      USHORT nParentId = USHRT_MAX;
//STRIP001      switch( cType )
//STRIP001      {
//STRIP001          case SWG_CHARFMT:
//STRIP001              if( nOptions & SWGRD_CHARFMTS )
//STRIP001              {
//STRIP001                  pFmt = InFormat( NULL, &nParentId );
//STRIP001                  TestPoolFmt( *pFmt, GET_POOLID_CHRFMT );
//STRIP001                  pFmt2 = _findcharfmt( pDoc, pFmt );
//STRIP001                  if( pFmt2 )
//STRIP001                  {
//STRIP001                      // Format bereits dem Namen nach drin
//STRIP001                      // Entweder ueberbuegeln oder vergessen
//STRIP001                      if( nOptions & SWGRD_FORCE )
//STRIP001                          *pFmt2 = *pFmt;
//STRIP001
//STRIP001                      // Registrierung umsetzen !!
//STRIP001                      ReRegisterFmt( *pFmt, *pFmt2 );
//STRIP001                      pDoc->DelCharFmt( (SwCharFmt*) pFmt );
//STRIP001                      pFmt = pFmt2;
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      RegisterFmt( *pFmt );
//STRIP001                      if( USHRT_MAX != nParentId )
//STRIP001                      {
//STRIP001                          // muss am Ende den richtigen Parent bekommen!
//STRIP001                          void* pPtr = pFmt;
//STRIP001                          aFmtArr.Insert( pPtr, aFmtArr.Count() );
//STRIP001                          aIdArr.Insert( nParentId, aIdArr.Count() );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          case SWG_FRAMEFMT:
//STRIP001              if( nOptions & SWGRD_FRAMEFMTS )
//STRIP001              {
//STRIP001                  pFmt = InFormat( NULL, &nParentId );
//STRIP001                  TestPoolFmt( *pFmt, GET_POOLID_FRMFMT );
//STRIP001                  pFmt2 = _findframefmt( pDoc, pFmt );
//STRIP001                  if( pFmt2 )
//STRIP001                  {
//STRIP001                      // Format bereits dem Namen nach drin,
//STRIP001                      // Entweder ueberbuegeln oder vergessen
//STRIP001                      if( nOptions & SWGRD_FORCE )
//STRIP001                          *pFmt2 = *pFmt;
//STRIP001
//STRIP001                      // Registrierung umsetzen !!
//STRIP001                      ReRegisterFmt( *pFmt, *pFmt2 );
//STRIP001                      pDoc->DelFrmFmt( (SwFrmFmt*) pFmt );
//STRIP001                      pFmt = pFmt2;
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      RegisterFmt( *pFmt );
//STRIP001                      if( USHRT_MAX != nParentId )
//STRIP001                      {
//STRIP001                          // muss am Ende den richtigen Parent bekommen!
//STRIP001                          void* pPtr = pFmt;
//STRIP001                          aFmtArr.Insert( pPtr, aFmtArr.Count() );
//STRIP001                          aIdArr.Insert( nParentId, aIdArr.Count() );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              else r.skipnext();
//STRIP001              break;
//STRIP001          default:
//STRIP001              r.skipnext();
//STRIP001      }
//STRIP001      if( pFmt )
//STRIP001          nNamedFmt++;
//STRIP001  }
//STRIP001
//STRIP001  if( pFmts )
//STRIP001  for( i = aFmtArr.Count(); i; )
//STRIP001  {
//STRIP001      SwFmt* pFmt = (SwFmt*)aFmtArr[ --i ];
//STRIP001      SwFmt* pParent;
//STRIP001      if( pFmts[ n = aIdArr[ i ] ].cFmt & FINFO_FORMAT )
//STRIP001          pParent = pFmts[ n ].pFmt;
//STRIP001      else if( RES_CHRFMT == pFmt->Which() )
//STRIP001          pParent = pDoc->GetDfltCharFmt();
//STRIP001      else
//STRIP001          pParent = pDoc->GetDfltFrmFmt();
//STRIP001
//STRIP001      pFmt->SetDerivedFrom( pParent );
//STRIP001  }
//STRIP001 }

// Registrieren eines Formats
// Das Format wird mit seinem Wert in der Tabelle registriert.
// Die Collection-Formate wwerden an das Ende der Tabelle gehaengt, da
// die Format-ID sich mit den anderen IDs ueberschneiden.

//STRIP001 void SwSwgReader::RegisterFmt( SwFmt& rFmt, const SwTable *pTable )
//STRIP001 {
//STRIP001  USHORT nIdx = rFmt.nFmtId;
//STRIP001  if( nIdx == IDX_NO_VALUE || nIdx == IDX_DFLT_VALUE )
//STRIP001      return;
//STRIP001  // Collection-Index?
//STRIP001  if( ( nIdx & IDX_TYPEMASK ) == IDX_COLLECTION )
//STRIP001      nIdx = MAXFMTS - 1 - ( nIdx & ~IDX_TYPEMASK );
//STRIP001  else
//STRIP001      nIdx &= ~IDX_TYPEMASK;
//STRIP001  // Array eingerichtet?
//STRIP001  if( !pFmts ) {
//STRIP001      pFmts = new FmtInfo[ MAXFMTS ];
//STRIP001      memset( pFmts, 0, MAXFMTS * sizeof( FmtInfo ) );
//STRIP001  }
//STRIP001  // Bereits registriert?
//STRIP001  ASSERT( pFmts[ nIdx ].pFmt == 0, "Format bereits registriert!" );
//STRIP001
//STRIP001  pFmts[ nIdx ].pFmt = &rFmt;
//STRIP001  pFmts[ nIdx ].cFmt = FINFO_FORMAT;
//STRIP001  if( nStatus & SWGSTAT_LOCALFMTS )
//STRIP001      pFmts[ nIdx ].cFmt |= FINFO_LOCAL;
//STRIP001
//STRIP001  if( pTable )
//STRIP001      RegisterTable( nIdx, pTable );
//STRIP001 }

// Registrieren eines AttrSets
// Ein AttrSet wird u.U. mehrfach registeriert, da es die Rolle
// der drei Autoformate am Node uebernommen hat.

//STRIP001 void SwSwgReader::RegisterAttrSet( SfxItemSet* pSet, USHORT nIdx )
//STRIP001 {
//STRIP001  if( nIdx == IDX_NO_VALUE || nIdx == IDX_DFLT_VALUE )
//STRIP001      return;
//STRIP001  // Array eingerichtet?
//STRIP001  if( !pFmts ) {
//STRIP001      pFmts = new FmtInfo[ MAXFMTS ];
//STRIP001      memset( pFmts, 0, MAXFMTS * sizeof( FmtInfo ) );
//STRIP001  }
//STRIP001  // Bereits registriert?
//STRIP001  ASSERT( pFmts[ nIdx ].pSet == 0, "AttrSet bereits registriert!" );
//STRIP001  pFmts[ nIdx ].pSet = pSet;
//STRIP001  pFmts[ nIdx ].cFmt = 0;
//STRIP001  if( nStatus & SWGSTAT_LOCALFMTS )
//STRIP001      pFmts[ nIdx ].cFmt |= FINFO_LOCAL;
//STRIP001 }

// Freigabe aller Autoformate (AttrSets) vor dem Einlesen
// eines neuen Textbausteins (da die Autoformat-Nummern neu vergeben
// werden koennen)

//STRIP001 void SwSwgReader::ReleaseAttrSets()
//STRIP001 {
//STRIP001  FmtInfo* p = pFmts;
//STRIP001  if( p )
//STRIP001  {
//STRIP001      for( USHORT i = 0; i < MAXFMTS; i++, p++ )
//STRIP001      {
//STRIP001          if( p->cFmt & FINFO_LOCAL )
//STRIP001          {
//STRIP001              if( ! (p->cFmt & FINFO_FORMAT) )
//STRIP001                  delete p->pSet;
//STRIP001              p->pSet = NULL;
//STRIP001              p->cFmt = 0;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  delete pTables; pTables = 0;
//STRIP001 }

// Finden eines Formats nach Index

//STRIP001 SwFmt* SwSwgReader::FindFmt( USHORT nIdx, BYTE cKind )
//STRIP001 {
//STRIP001  SwFmt* pFmt = NULL;
//STRIP001  switch( nIdx )
//STRIP001  {
//STRIP001      case IDX_NO_VALUE:
//STRIP001          return NULL;    // Direkter Abbruch, kein Assert
//STRIP001      case IDX_COLUMN:
//STRIP001          pFmt = pDoc->GetColumnContFmt(); break;
//STRIP001      case IDX_EMPTYPAGE:
//STRIP001          pFmt = pDoc->GetEmptyPageFmt(); break;
//STRIP001      case IDX_DFLT_VALUE:
//STRIP001          switch( cKind )
//STRIP001          {
//STRIP001              case SWG_MASTERFMT:
//STRIP001              case SWG_LEFTFMT:
//STRIP001              case SWG_FLYFMT:
//STRIP001              case SWG_FREEFMT:
//STRIP001              case SWG_FRAMEFMT:
//STRIP001                  pFmt = pDoc->GetDfltFrmFmt(); break;
//STRIP001              case SWG_CHARFMT:
//STRIP001              case SWG_PARAFMT:
//STRIP001                  pFmt = pDoc->GetDfltCharFmt(); break;
//STRIP001              case SWG_GRFFMT:
//STRIP001                  pFmt = (SwFmt*) pDoc->GetDfltGrfFmtColl(); break;
//STRIP001              case 0:
//STRIP001                  return NULL;    // Direkter Abbruch, kein Assert
//STRIP001          } break;
//STRIP001      default:
//STRIP001          // Collection-Index?
//STRIP001          if( ( nIdx & IDX_TYPEMASK ) == IDX_COLLECTION )
//STRIP001              nIdx = MAXFMTS - 1 - ( nIdx & ~IDX_TYPEMASK );
//STRIP001          else
//STRIP001              nIdx &= ~IDX_TYPEMASK;
//STRIP001          if( pFmts && pFmts[ nIdx ].cFmt & FINFO_FORMAT )
//STRIP001              pFmt = pFmts[ nIdx ].pFmt;
//STRIP001  }
//STRIP001  ASSERT( pFmt, "Format-ID unbekannt" );
//STRIP001  return pFmt;
//STRIP001 }

// Finden eines AttrSets nach Index

//STRIP001 SfxItemSet* SwSwgReader::FindAttrSet( USHORT nIdx )
//STRIP001 {
//STRIP001  // Standard-Werte
//STRIP001  if( nIdx == IDX_NO_VALUE || nIdx == IDX_DFLT_VALUE )
//STRIP001      return NULL;
//STRIP001  // Nicht von Autofmt abgeleitet?
//STRIP001  // dann gibt es keine Ableitung
//STRIP001  if( ( nIdx & IDX_TYPEMASK ) != IDX_AUTOFMT )
//STRIP001      return NULL;
//STRIP001  nIdx &= ~IDX_TYPEMASK;
//STRIP001  SfxItemSet* pSet = NULL;
//STRIP001  if( pFmts && !( pFmts[ nIdx ].cFmt & FINFO_FORMAT ) )
//STRIP001      pSet = pFmts[ nIdx ].pSet;
//STRIP001  ASSERT( pSet, "Format-ID (AttrSet) unbekannt" );
//STRIP001  return pSet;
//STRIP001 }

//STRIP001 static SwFmt* _GetUserPoolFmt( USHORT nId, const SvPtrarr* pFmtArr )
//STRIP001 {
//STRIP001  SwFmt* pFmt;
//STRIP001  for( USHORT n = 0; n < pFmtArr->Count(); ++n )
//STRIP001      if( nId == (pFmt = (SwFmt*)(*pFmtArr)[n])->GetPoolFmtId() )
//STRIP001          return pFmt;
//STRIP001  return 0;
//STRIP001 }

// Re-Registrierung eines Formats mit neuem Index
// wird bei shared Hdr/Ftr-Formaten in InPageDesc() verwendet
// Der Eintrag fuer pFmtOld wird auf pFmtNew gesetzt, so dass spaetere
// Referenzen auf den Index pFmtNew liefern

//STRIP001 void SwSwgReader::ReRegisterFmt( const SwFmt& rFmtOld, const SwFmt& rFmtNew,
//STRIP001                               const SwTable *pTable)
//STRIP001 {
//STRIP001  USHORT nIdx = rFmtOld.nFmtId;
//STRIP001  if( !nIdx )
//STRIP001      nIdx = rFmtNew.nFmtId;
//STRIP001  ((SwFmt&)rFmtNew).nFmtId = nIdx;
//STRIP001  ASSERT( nIdx, "Format nicht registriert" );
//STRIP001  nIdx &= ~IDX_TYPEMASK;
//STRIP001  ASSERT( !( pFmts[ nIdx ].cFmt & FINFO_FORMAT ) ||
//STRIP001          !pFmts[ nIdx ].pSet ||
//STRIP001          pFmts[ nIdx ].pFmt == (SwFmt*) &rFmtNew ||
//STRIP001          (pTable && pTable != FindTable(nIdx)),
//STRIP001          "Bereits ein AttrSet definiert!" );
//STRIP001  pFmts[ nIdx ].pFmt = (SwFmt*) &rFmtNew;
//STRIP001  pFmts[ nIdx ].cFmt = FINFO_FORMAT;
//STRIP001  if( nStatus & SWGSTAT_LOCALFMTS )
//STRIP001      pFmts[ nIdx ].cFmt |= FINFO_LOCAL;
//STRIP001
//STRIP001  if( pTable )
//STRIP001      RegisterTable( nIdx, pTable );
//STRIP001 }

// Entfernen aller Format-IDs, damit der Writer nicht
// durcheinander kommt (er vergibt neue IDs)

//STRIP001 void SwSwgReader::ClearFmtIds()
//STRIP001 {
//STRIP001  FmtInfo* p = pFmts;
//STRIP001  for( USHORT i = 0; i < MAXFMTS; i++, p++ )
//STRIP001  {
//STRIP001      if( p->cFmt & FINFO_FORMAT )
//STRIP001          p->pFmt->nFmtId = 0;
//STRIP001      else
//STRIP001          delete p->pSet, p->pSet = NULL;
//STRIP001  }
//STRIP001  delete pTables; pTables = 0;
//STRIP001 }

//STRIP001 void SwSwgReader::RegisterTable( USHORT nIdx, const SwTable *pTable )
//STRIP001 {
//STRIP001  if( !pTables )
//STRIP001      pTables = new SwgTables;
//STRIP001  while( pTables->Count() <= nIdx )
//STRIP001      pTables->Insert( (const SwTable *)0, pTables->Count() );
//STRIP001  pTables->Replace( pTable, nIdx );
//STRIP001 }

//STRIP001 const SwTable *SwSwgReader::FindTable( USHORT nIdx )
//STRIP001 {
//STRIP001  const SwTable *pRet = 0;
//STRIP001  if( pTables && nIdx < pTables->Count() )
//STRIP001      pRet = (*pTables)[nIdx];
//STRIP001
//STRIP001  return pRet;
//STRIP001 }


