/*************************************************************************
 *
 *  $RCSfile: sw_rdnum.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:33:04 $
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

#ifndef _GDIOBJ_HXX //autogen
#include <vcl/gdiobj.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SV_FONT_HXX //autogen
#include <vcl/font.hxx>
#endif

#include "doc.hxx"
#include "pam.hxx"
#include "rdswg.hxx"
#include "ndtxt.hxx"
#include "numrule.hxx"
#include "poolfmt.hxx"



//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

// Numerierungs-Format
//STRIP001 extern BYTE lcl_sw3io__GetIncludeUpperLevel( BOOL bInclUpperLevel );

//STRIP001 void SwSwgReader::InNumFmt( SwNumFmt& rFmt )
//STRIP001 {
//STRIP001  // Flags:
//STRIP001  // 0x01 - Praefix-String vorhanden
//STRIP001  // 0x02 - Postfix-String vorhanden
//STRIP001  // 0x04 - Bullet-Font vorhanden
//STRIP001  sal_Char bFlags, eType, cBullet, bInclUpperLevel, eNumAdjust;
//STRIP001  USHORT nFmt, nStart;
//STRIP001  String aFontName;
//STRIP001  sal_Char eFamily, ePitch, eCharSet = RTL_TEXTENCODING_SYMBOL;
//STRIP001  long nLSpace, nFirstLineOffset;
//STRIP001  if( aHdr.nVersion >= SWG_VER_COMPAT )
//STRIP001  {
//STRIP001      rFmt.SetPrefix( GetText() );
//STRIP001      rFmt.SetSuffix( GetText() );
//STRIP001      aFontName = GetText();
//STRIP001      BOOL bOk = TRUE;
//STRIP001      if( r.next() != SWG_DATA ) bOk = FALSE, Error();
//STRIP001      r >> bFlags
//STRIP001        >> nFmt
//STRIP001        >> eType
//STRIP001        >> cBullet
//STRIP001        >> bInclUpperLevel
//STRIP001        >> nStart
//STRIP001        >> eNumAdjust
//STRIP001        >> nLSpace
//STRIP001        >> nFirstLineOffset
//STRIP001        >> eFamily
//STRIP001        >> ePitch
//STRIP001        >> eCharSet;
//STRIP001      if( bOk ) r.skip();
//STRIP001  } else {
//STRIP001      r >> bFlags
//STRIP001        >> nFmt
//STRIP001        >> eType
//STRIP001        >> cBullet
//STRIP001        >> bInclUpperLevel
//STRIP001        >> nStart
//STRIP001        >> eNumAdjust
//STRIP001        >> nLSpace
//STRIP001        >> nFirstLineOffset;
//STRIP001      if( bFlags & 0x01 )
//STRIP001          rFmt.SetPrefix( GetText() );
//STRIP001      if( bFlags & 0x02 )
//STRIP001          rFmt.SetSuffix( GetText() );
//STRIP001      if( bFlags & 0x04 )
//STRIP001      {
//STRIP001          aFontName = GetText();
//STRIP001          r >> eFamily >> ePitch >> eCharSet;
//STRIP001      }
//STRIP001  }
//STRIP001  if( RTL_TEXTENCODING_DONTKNOW == eCharSet )
//STRIP001      eCharSet = RTL_TEXTENCODING_SYMBOL;
//STRIP001  sal_Unicode cBull = ByteString::ConvertToUnicode( cBullet, eCharSet );
//STRIP001  if( !cBull )
//STRIP001      cBull = cBulletChar;
//STRIP001  rFmt.SetNumberingType( eType );
//STRIP001  rFmt.SetBulletChar( cBull );
//STRIP001  rFmt.SetIncludeUpperLevels( lcl_sw3io__GetIncludeUpperLevel(bInclUpperLevel) );
//STRIP001  rFmt.SetStart( nStart );
//STRIP001  rFmt.SetNumAdjust( SvxAdjust( eNumAdjust ) );
//STRIP001  rFmt.SetAbsLSpace( (USHORT)nLSpace );
//STRIP001  rFmt.SetFirstLineOffset( (short)nFirstLineOffset );
//STRIP001  if( bFlags & 0x04 )
//STRIP001  {
//STRIP001      Font aFont;
//STRIP001      aFont.SetName( aFontName );
//STRIP001      aFont.SetFamily( FontFamily( eFamily ) );
//STRIP001      aFont.SetPitch( FontPitch( ePitch ) );
//STRIP001      aFont.SetCharSet( rtl_TextEncoding( eCharSet ) );
//STRIP001      rFmt.SetBulletFont( &aFont );
//STRIP001  }
//STRIP001  r.next();
//STRIP001 }

// Numerierungs-Regel

//STRIP001 SwNumRule* SwSwgReader::InNumRule()
//STRIP001 {
//STRIP001  sal_Char eType, nFmt, cFmt[ MAXLEVEL ];
//STRIP001  r >> eType >> nFmt;
//STRIP001  // C 8.0 bug:
//STRIP001  SwNumRuleType eTemp = (SwNumRuleType) eType;
//STRIP001  SwNumRule* pRule = new SwNumRule( pDoc->GetUniqueNumRuleName(), eTemp );
//STRIP001  for( int i = 0; i < nFmt; i++ )
//STRIP001      r >> cFmt[ i ];
//STRIP001  r.next();
//STRIP001  for( i = 0; r.good() && i < nFmt; i++ )
//STRIP001  {
//STRIP001      SwNumFmt aFmt;
//STRIP001      if( r.cur() != SWG_NUMFMT )
//STRIP001      {
//STRIP001          Error(); delete pRule; return NULL;
//STRIP001      }
//STRIP001      aFmt.SetBulletFont( NULL );
//STRIP001      InNumFmt( aFmt );
//STRIP001      if( !r )
//STRIP001      {
//STRIP001          delete pRule; return NULL;
//STRIP001      }
//STRIP001      pRule->Set( (USHORT) cFmt[ i ], aFmt );
//STRIP001  }
//STRIP001  if( pRule )
//STRIP001  {
//STRIP001      if( aHdr.nVersion < SWG_VER_POOLID3 )
//STRIP001      {
//STRIP001          static short __READONLY_DATA aOldFI[ 5 ] =  { -227, -397, -567, -737, -936 };
//STRIP001          static short __READONLY_DATA aOldLft[ 5 ] = { 567, 964, 1474, 567*4, 3204 };
//STRIP001
//STRIP001          // Alte Dokumente: Fehlende Formate nachtragen
//STRIP001          for( i = 0; i < MAXLEVEL; i++ )
//STRIP001              if( !pRule->GetNumFmt( i ) )
//STRIP001              {
//STRIP001                  SwNumFmt aFmt( pRule->Get( i ) );
//STRIP001                  aFmt.SetIncludeUpperLevels( MAXLEVEL );
//STRIP001                  aFmt.SetAbsLSpace( aOldLft[ i ] );
//STRIP001                  aFmt.SetFirstLineOffset( aOldFI[ i ] );
//STRIP001                  aFmt.SetNumberingType(SVX_NUM_ARABIC);
//STRIP001                  if( i )
//STRIP001                      aFmt.SetSuffix( aEmptyStr );
//STRIP001                  pRule->Set( i, aFmt );
//STRIP001              }
//STRIP001      }
//STRIP001 #if 0
//STRIP001      // fuer alle Ebenen aus der abs. eine rel. Angabe errechnen
//STRIP001      // MIB 13.01.98: Brauchen wir mit der neuen Numerierung nicht
//STRIP001      // mehr.
//STRIP001      USHORT nLSpace = 0;
//STRIP001      for( i = 0; i < MAXLEVEL; ++i )
//STRIP001      {
//STRIP001          SwNumFmt* pFmt = (SwNumFmt*)pRule->GetNumFmt( i );
//STRIP001          if( !pFmt )
//STRIP001              nLSpace =  (i + 1) * lNumIndent;
//STRIP001          else
//STRIP001          {
//STRIP001              pFmt->SetLSpace( !i ? 0 : pFmt->GetAbsLSpace() - nLSpace );
//STRIP001              nLSpace = pFmt->GetAbsLSpace();
//STRIP001          }
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001  return pRule;
//STRIP001 }

// Outline-Numerierung


//STRIP001 void SwSwgReader::InOutlineRule()
//STRIP001 {
//STRIP001  SwNumRule* pRule = InNumRule();
//STRIP001  if( pRule )
//STRIP001  {
//STRIP001      pRule->SetName( String::CreateFromAscii(
//STRIP001                              SwNumRule::GetOutlineRuleName() ) );
//STRIP001      if( aHdr.nVersion < SWG_VER_POOLIDS )
//STRIP001      {
//STRIP001          // Alte Dokumente: Fehlende Formate nachtragen
//STRIP001          for( short i = 0; i < MAXLEVEL; i++ )
//STRIP001          {
//STRIP001              if( !pRule->GetNumFmt( i ) )
//STRIP001              {
//STRIP001                  SwNumFmt aFmt( pRule->Get( i ) );
//STRIP001                  aFmt.SetNumberingType(SVX_NUM_ARABIC);
//STRIP001                  pRule->Set( i, aFmt );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      //JP 18.01.96: Alle Ueberschriften sind normalerweise ohne
//STRIP001      //              Kapitelnummer. Darum hier explizit abschalten
//STRIP001      //              weil das Default jetzt wieder auf AN ist.
//STRIP001      // und UeberschirftBasis ohne Einrueckung!
//STRIP001 //JP 10.03.96: und wieder alles zurueck
//STRIP001 #if 0
//STRIP001      SwTxtFmtColl* pCol = pDoc->GetTxtCollFromPool( RES_POOLCOLL_HEADLINE_BASE );
//STRIP001      pCol->ResetAttr( RES_LR_SPACE );
//STRIP001
//STRIP001      for( short i = 0; i < MAXLEVEL; i++ )
//STRIP001      {
//STRIP001          if( !pRule->GetNumFmt( i ) )
//STRIP001          {
//STRIP001              SwNumFmt aFmt( pRule->Get( i ) );
//STRIP001              aFmt.eType = NUMBER_NONE;
//STRIP001              pRule->Set( i, aFmt );
//STRIP001          }
//STRIP001      }
//STRIP001 #endif
//STRIP001      pDoc->SetOutlineNumRule( *pRule );
//STRIP001      delete pRule;
//STRIP001  }
//STRIP001 }


// Numerierungs-Regelwerk
// Dieses Regelwerk wird nach dem Einlesen der Nodes eingelesen.
// Zu diesem Zeitpunkt sollte das Index-Array pRules bereits mit den
// gueltigen Bereichen fuer die Regeln gefuellt sein

// (siehe SwSwgReader::UpdateRuleRange())

//STRIP001 void lcl_sw3io__ConvertNumLRSpace( SwTxtNode& rTxtNd, const SwNumRule& rNumRule,
//STRIP001                                 BYTE nLevel, BOOL bTabStop );

//STRIP001 void SwSwgReader::InTxtNumRule()
//STRIP001 {
//STRIP001  USHORT n;
//STRIP001  r >> n;
//STRIP001  if( n != nRules )
//STRIP001  {
//STRIP001      Error(); return;
//STRIP001  }
//STRIP001  r.next();
//STRIP001  for( USHORT i = 0; i < n; i++ )
//STRIP001  {
//STRIP001      SwTxtNode* pBgn = pRules[ i ].pBgn;
//STRIP001      SwTxtNode* pEnd = pRules[ i ].pEnd;
//STRIP001      if( r.cur() != SWG_NUMRULE || !pBgn )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      // Rules einlesen
//STRIP001      SwNumRule* pRule = InNumRule();
//STRIP001      if( !pRule ) break;
//STRIP001
//STRIP001      SwPaM aPaM( *pBgn, 0, *pEnd, 0 );
//STRIP001      SwNodeIndex aBgnIdx( *pBgn );
//STRIP001      const SwNodeIndex& rEndIdx = aPaM.GetPoint()->nNode;
//STRIP001      // jetzt noch die Nodes mit den Rules verbinden
//STRIP001      BYTE nPrevLevel = 0;
//STRIP001      do {
//STRIP001          SwTxtNode* pNd = aBgnIdx.GetNode().GetTxtNode();
//STRIP001          if( pNd )
//STRIP001          {
//STRIP001              if( pNd->GetNum() )
//STRIP001              {
//STRIP001                  SwNodeNum *pNum = (SwNodeNum*) pNd->GetNum();
//STRIP001
//STRIP001                  //JP 19.03.96: NO_NUM gibt es nicht mehr, dafuer gibts
//STRIP001                  //              jetzt NO_NUMLEVEL
//STRIP001                  if( NO_NUM == pNum->GetLevel() )
//STRIP001                      pNum->SetLevel( nPrevLevel | NO_NUMLEVEL );
//STRIP001                  else
//STRIP001                      nPrevLevel = pNum->GetLevel();
//STRIP001 #ifdef NUM_RELSPACE
//STRIP001                  lcl_sw3io__ConvertNumLRSpace( *pNd, *pRule,
//STRIP001                                                 pNum->GetLevel(), TRUE );
//STRIP001 #endif
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // Hot fix bei Loechern im Bereich:
//STRIP001                  pNd->UpdateNum( SwNodeNum( nPrevLevel | NO_NUMLEVEL ) );
//STRIP001                  ASSERT( FALSE, "SW/G-Reader: Luecke im NumRule-Bereich!" );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              Error(); break;
//STRIP001          }
//STRIP001          aBgnIdx += 1;
//STRIP001      } while( aBgnIdx.GetIndex() <= rEndIdx.GetIndex() );
//STRIP001
//STRIP001      pDoc->SetNumRule( aPaM, *pRule );
//STRIP001      delete pRule;
//STRIP001  }
//STRIP001 }

// Update des Bereichs einer Numerierungsregel

//STRIP001 void SwSwgReader::UpdateRuleRange( USHORT nIdx, SwTxtNode* pNd )
//STRIP001 {
//STRIP001  // Evtl. den Puffer fuer die NumRules-Bereiche einrichten
//STRIP001  if( !pRules && aHdr.nNumRules )
//STRIP001  {
//STRIP001      nRules = aHdr.nNumRules;
//STRIP001      pRules = new NumRuleInfo[ nRules ];
//STRIP001      for( USHORT i = 0; i < nRules; i++ )
//STRIP001          pRules[ i ].pBgn =
//STRIP001          pRules[ i ].pEnd = NULL;
//STRIP001  }
//STRIP001  if( nIdx >= nRules ) return;
//STRIP001  // Node-Nummer fuer PaM-SRange updaten:
//STRIP001  NumRuleInfo* p = &pRules[ nIdx ];
//STRIP001  if( !p->pBgn )
//STRIP001     p->pBgn = p->pEnd = pNd;
//STRIP001  else
//STRIP001     p->pEnd = pNd;
//STRIP001 }



