/*************************************************************************
 *
 *  $RCSfile: sw_rdcont.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:33:11 $
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
#include "pam.hxx"

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#include "rdswg.hxx"
#include "swgpar.hxx"
#include "ndtxt.hxx"
#include "bookmrk.hxx"
#include "swtable.hxx"
#include "mdiexp.hxx"       // Progress
#include "swddetbl.hxx"
#include "swtblfmt.hxx"


//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

// Contents-Teil

// Wird ein Text in einen Absatz eingefuegt, wird der erste Absatz an den
// ersten Teil angefuegt, ohne die Formate zu uebernehmen. Alle anderen
// Absaetze uebernehmen die Formate, was auch den Rest des alten Absatzes
// betrifft.
// Falls bNode1 FALSE ist, wird ein evtl. vorhandener leerer Node nicht
// gefuellt. Dadurch laesst sich diese Methode fuer mehrere Contents
// verwenden.
// Falls bBlock TRUE ist, handelt es sich um das Einlesen eies Textblock-
// Inhalts. Hier gibt es keinen Section-ID und auch keine Registrierrung
// der Section!
// nInsFirstPara - beim Document einfuegen, muss der erste Absatz
//                  sonderbehandelt werden (Absatz Attribute!)

//STRIP001 typedef SwTableBox* SwTableBoxPtr;

//STRIP001 void SwSwgReader::InContents( BOOL bNode1, BOOL bBlock, USHORT nInsFirstPara )
//STRIP001 {
//STRIP001  USHORT nNodes, nId = IDX_NO_VALUE;
//STRIP001  USHORT nOldStatus = nStatus;
//STRIP001  // Beim Einlesen eines TB keine Bookmarks einlesen!
//STRIP001  // Auch sollen alle Autoformate (AttrSets) wiederverwendbar sein!
//STRIP001  if( bBlock )
//STRIP001  {
//STRIP001      ReleaseAttrSets();
//STRIP001      nStatus |= SWGSTAT_NO_BOOKMARKS | SWGSTAT_LOCALFMTS;
//STRIP001  }
//STRIP001  if( !bBlock )
//STRIP001      r >> nId;
//STRIP001  r >> nNodes;
//STRIP001  r.next();
//STRIP001
//STRIP001  // fuer die Sonderbehandlung des ersten/letzten Node beim "Datei/Einfuegen"
//STRIP001  USHORT nSaveInsFirstPara = nInsFirstPara;
//STRIP001
//STRIP001  // Bei einem echten Insert muss der aktuelle Node gesplittet werden,
//STRIP001  // Falls mehr als 1 Node eingelesen wird.
//STRIP001  BOOL bIns = BOOL( !bNew );
//STRIP001  BOOL bSplit = FALSE;
//STRIP001  SwTxtNode* pLast = NULL;
//STRIP001  SwNodeIndex aPos( pPaM->GetPoint()->nNode );
//STRIP001  xub_StrLen nOffset = pPaM->GetPoint()->nContent.GetIndex();
//STRIP001  SwNode* pStart = pDoc->GetNodes()[ aPos ];
//STRIP001  SwTxtNode* pNd = bNode1 ? pStart->GetTxtNode() : NULL;
//STRIP001  if( !bBlock )
//STRIP001  {
//STRIP001      RegisterSection( SwNodeIndex( *pStart->StartOfSectionNode() ), nId );
//STRIP001  }
//STRIP001  for( USHORT i = 1; i <= nNodes && r.good(); i++)
//STRIP001  {
//STRIP001      ::SetProgressState( r.tell(), pDoc->GetDocShell() );
//STRIP001
//STRIP001      switch( r.cur() )
//STRIP001      {
//STRIP001          case SWG_TEXTNODE:
//STRIP001              // Der Node muss gesplittet werden,
//STRIP001              // wenn mehrere Nodes inserted werden
//STRIP001              if( !bSplit && bIns && nNodes > 1 )
//STRIP001              {
//STRIP001                  if( pNd )
//STRIP001                  {
//STRIP001                      // natuerlich nur TextNodes splitten
//STRIP001                      SwPosition aSplitPos( aPos, SwIndex( pNd, nOffset ) );
//STRIP001                      pDoc->SplitNode( aSplitPos );
//STRIP001                      pLast = pNd;
//STRIP001                      aPos--;
//STRIP001                      pNd = pDoc->GetNodes()[ aPos ]->GetTxtNode();
//STRIP001                      bSplit = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( i == nNodes && pLast )
//STRIP001              {
//STRIP001                  // der letzte Node: nimm evtl. den gesplitteten
//STRIP001                  pNd = pLast;
//STRIP001                  if( nSaveInsFirstPara && pNd && pNd->GetTxt().Len() )
//STRIP001                      nInsFirstPara = 2;
//STRIP001              }
//STRIP001              FillTxtNode( pNd, aPos, nOffset, nInsFirstPara );
//STRIP001              pNd = NULL; nOffset = 0;
//STRIP001              nInsFirstPara = 0;
//STRIP001              break;
//STRIP001          case SWG_GRFNODE:
//STRIP001              InGrfNode( aPos );
//STRIP001              nInsFirstPara = 0;
//STRIP001              goto chknode;
//STRIP001          case SWG_OLENODE:
//STRIP001              InOleNode( aPos );
//STRIP001              // Falls ein TxtNode am Anfang war, weg damit!
//STRIP001              nInsFirstPara = 0;
//STRIP001          chknode:
//STRIP001              if( pNd )
//STRIP001                  pDoc->GetNodes().Delete( aPos );
//STRIP001              pNd = NULL;
//STRIP001              break;
//STRIP001          case SWG_TABLE: {
//STRIP001              // JP 20.05.94: Dok. einfuegen: wird als 1.Node eine
//STRIP001              //              Tabelle eingefuegt, dann immer splitten !!
//STRIP001              nInsFirstPara = 0;
//STRIP001              if( 1 == i && bIns )
//STRIP001              {
//STRIP001                  SwPosition aSplitPos( aPos, SwIndex( pNd, nOffset ) );
//STRIP001                  pDoc->SplitNode( aSplitPos );
//STRIP001                  nOffset = 0;    //  mit dem Offset hat sichs erledigt!
//STRIP001              }
//STRIP001              InTable( aPos );
//STRIP001              if( i != 1 ) pNd = NULL;
//STRIP001              } break;
//STRIP001          case SWG_TOXGROUP:
//STRIP001              InTOX( aPos, pNd );
//STRIP001              pNd = NULL;
//STRIP001              break;
//STRIP001          case SWG_TEXTBLOCK: {
//STRIP001              BYTE cFlag;
//STRIP001              r >> cFlag;
//STRIP001              if( !cFlag ) r.skipnext();
//STRIP001              else {
//STRIP001                  // TODO: unicode: check for 8 bit encoding
//STRIP001                  BYTE eCharSet = (BYTE) gsl_getSystemTextEncoding();
//STRIP001                  if( cFlag & 0x02 )
//STRIP001                    r >> eCharSet;
//STRIP001                  BYTE eSave = aHdr.cCodeSet;
//STRIP001                  aHdr.cCodeSet = eCharSet;
//STRIP001                  GetText();
//STRIP001                  GetText();
//STRIP001                  InContents( bNode1, TRUE );
//STRIP001                  aHdr.cCodeSet = eSave;
//STRIP001                  bNode1 = FALSE;
//STRIP001              }
//STRIP001          } break;
//STRIP001          case SWG_COMMENT:
//STRIP001              // Reste von TextBlocks
//STRIP001              r.skipnext(); break;
//STRIP001          case SWG_EOF:
//STRIP001              // sicherheitshalber
//STRIP001              r.undonext(); i = nNodes = 9999; break;
//STRIP001          default:
//STRIP001              // unbekannte Nodes
//STRIP001              Error(); r.skipnext();
//STRIP001      }
//STRIP001  }
//STRIP001  nStatus = nOldStatus;
//STRIP001 }

// Einlesen des puren Textes eines Content-Bereichs

//STRIP001 String SwSwgReader::InContentsText( BOOL bBlock )
//STRIP001 {
//STRIP001  USHORT nNodes, nId;
//STRIP001  String aText;
//STRIP001  if( !bBlock )
//STRIP001      r >> nId;
//STRIP001  r >> nNodes;
//STRIP001  r.next();
//STRIP001  for( USHORT i = 1; i <= nNodes && r.good(); i++)
//STRIP001  {
//STRIP001      switch( r.cur() )
//STRIP001      {
//STRIP001          case SWG_TEXTNODE:
//STRIP001              FillString( aText );
//STRIP001              break;
//STRIP001          case SWG_TABLE:     // Zur Zeit keine Tabellen
//STRIP001          case SWG_GRFNODE:
//STRIP001          case SWG_OLENODE:
//STRIP001          case SWG_TOXGROUP:
//STRIP001          case SWG_COMMENT:
//STRIP001              r.skipnext(); break;
//STRIP001          case SWG_TEXTBLOCK: {
//STRIP001              BYTE cFlag;
//STRIP001              r >> cFlag;
//STRIP001              if( !cFlag ) r.skipnext();
//STRIP001              else {
//STRIP001                  // TODO: unicode: check for 8 bit encoding
//STRIP001                  BYTE eCharSet = (BYTE) gsl_getSystemTextEncoding();
//STRIP001                  if( cFlag & 0x02 )
//STRIP001                    r >> eCharSet;
//STRIP001                  BYTE eSave = aHdr.cCodeSet;
//STRIP001                  aHdr.cCodeSet = eCharSet;
//STRIP001                  GetText();
//STRIP001                  GetText();
//STRIP001                  String aBlock = InContentsText( TRUE );
//STRIP001                  if( aText.Len() ) aText += ' ';
//STRIP001                  aText += aBlock;
//STRIP001                  aHdr.cCodeSet = eSave;
//STRIP001              }
//STRIP001          } break;
//STRIP001          default:
//STRIP001              // unbekannte Nodes
//STRIP001              Error(); r.skipnext();
//STRIP001      }
//STRIP001  }
//STRIP001  return aText;
//STRIP001 }

// Einfuegen einer nicht vorhandenen Contents-Section

//STRIP001 SwStartNode* SwSwgReader::InSection()
//STRIP001 {
//STRIP001  // Anlegen einer Section mit einem TextNode
//STRIP001  SwNodeIndex aStart( pDoc->GetNodes().GetEndOfAutotext() );
//STRIP001  SwStartNode* pSttNd = pDoc->GetNodes().MakeTextSection( aStart,
//STRIP001                              (SwStartNodeType)eStartNodeType,
//STRIP001                              (SwTxtFmtColl*) pDoc->GetDfltTxtFmtColl() );
//STRIP001  aStart = *pSttNd;
//STRIP001  FillSection( aStart );
//STRIP001  return pSttNd;
//STRIP001 }

// Fuellen einer vorhandenen Contents-Section
// Die Position zeigt auf den StartNode
// Der SwIndex zeigt hinterher auf den EndNode

//STRIP001 void SwSwgReader::FillSection( SwNodeIndex& rPos )
//STRIP001 {
//STRIP001  if( r.next() != SWG_CONTENTS )
//STRIP001  {
//STRIP001      Error();
//STRIP001      rPos = rPos.GetIndex() + 3; // skip section
//STRIP001      return;
//STRIP001  }
//STRIP001  // die Anzahl Nodes einlesen
//STRIP001  USHORT nId, nNodes;
//STRIP001  r >> nId >> nNodes;
//STRIP001  RegisterSection( rPos, nId );
//STRIP001  rPos++;
//STRIP001  SwCntntNode* pNode = pDoc->GetNodes()[ rPos ]->GetCntntNode();
//STRIP001  r.next();
//STRIP001  for( USHORT i = 1; i <= nNodes && r.good(); i++)
//STRIP001  {
//STRIP001      ::SetProgressState( r.tell(), pDoc->GetDocShell() );
//STRIP001      switch( r.cur() )
//STRIP001      {
//STRIP001          case SWG_TEXTNODE:
//STRIP001              FillTxtNode( (SwTxtNode*) pNode, rPos, 0 );
//STRIP001              pNode = NULL;
//STRIP001              break;
//STRIP001          case SWG_GRFNODE:
//STRIP001              InGrfNode( rPos );
//STRIP001              break;
//STRIP001          case SWG_OLENODE:
//STRIP001              InOleNode( rPos );
//STRIP001              break;
//STRIP001          case SWG_TABLE:
//STRIP001              InTable( rPos );
//STRIP001              break;
//STRIP001          case SWG_COMMENT:
//STRIP001              // Reste von TextBlocks
//STRIP001              r.skipnext(); break;
//STRIP001          default:
//STRIP001              // unbekannte Nodes
//STRIP001              Error(); r.skipnext();
//STRIP001      }
//STRIP001  }
//STRIP001  // Ueber den EndNode skippen
//STRIP001  rPos++;
//STRIP001
//STRIP001  // Eine Tabelle und eine Section koennen u.U. alleine
//STRIP001  // in einer Textsection existieren, d.h. es muss ggf.
//STRIP001  // der ueberfluessige Node entfernt werden!
//STRIP001  if( pNode && r.good() )
//STRIP001  {
//STRIP001      // Falls der aktuelle PaM auf diesen Node zeigt, den PaM
//STRIP001      // knallhart wegschieben. Ist erlaubt laut JP!
//STRIP001      if( pPaM )
//STRIP001      {
//STRIP001          if( pPaM->GetBound( TRUE ).nContent.GetIdxReg() == pNode )
//STRIP001              pPaM->GetBound( TRUE ).nContent.Assign( 0, 0 );
//STRIP001          if( pPaM->GetBound( FALSE ).nContent.GetIdxReg() == pNode )
//STRIP001              pPaM->GetBound( FALSE ).nContent.Assign( 0, 0 );
//STRIP001      }
//STRIP001      pDoc->GetNodes().Delete( SwNodeIndex( *pNode ) );
//STRIP001  }
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////

// Tabellen

// Zeilen und Boxen duerfen keine Rueckwaertsreferenz in andere
// Tabellen enthalten, also: Fixen!

//STRIP001 static long nFrmSizeAdj = 1;         // Divisionsfaktor fuer FrmSize

// Das Attribut darf im Prinzip nicht > 65535 werden, da sonst MAs
// Rechenroutinen baden gehen. Da einige alte Tabellen groessere Werte
// enthalten, setzt InTable() ggf. einen Divisionsfaktor, um den
// die gelesenen Werte heruntergeteilt werden. Normalerweise ist er 1.

//STRIP001 static void AdjustFrmSize( SwFrmFmt* pFmt )
//STRIP001 {
//STRIP001  if( pFmt && nFrmSizeAdj > 1
//STRIP001   && pFmt->GetAttrSet().GetItemState( RES_FRM_SIZE, FALSE ) == SFX_ITEM_SET )
//STRIP001  {
//STRIP001      SwFmtFrmSize aSz( pFmt->GetFrmSize() );
//STRIP001      if( aSz.GetSizeType() == ATT_VAR_SIZE )
//STRIP001      {
//STRIP001          aSz.SetWidth( aSz.GetWidth() / nFrmSizeAdj );
//STRIP001          aSz.SetHeight( aSz.GetHeight() / nFrmSizeAdj );
//STRIP001          pFmt->SetAttr( aSz );
//STRIP001      }
//STRIP001  }
//STRIP001 }

// Das uebergebene Array ist erst mal leer.
// Der Index zeigt auf den naechsten freien StartNode und wird
// auf den wiederum naechsten vorgeschoben.

//STRIP001 void SwSwgReader::InTableBox
//STRIP001   (SwTableBoxes& rBoxes, int idx,    // Array und Index
//STRIP001    SwTableLine* pUpper,              // uebergeordnete Zeile
//STRIP001    SwNodeIndex& rPos,
//STRIP001    const SwTable *pTable )           // Start-Index der Section
//STRIP001 {
//STRIP001  short nFrmFmt, nLines;
//STRIP001  r >> nFrmFmt >> nLines;
//STRIP001  // Frame-Format evtl. einlesen
//STRIP001  SwTableBoxFmt* pFmt = NULL;
//STRIP001  r.next();
//STRIP001  while( r.cur() == SWG_FRAMEFMT && r.good() )
//STRIP001  {
//STRIP001      // Das Attribut SwFmtFrmSize benoetigt diese Werte, um
//STRIP001      // seine Werte umzudrehen
//STRIP001      USHORT nOldLvl = nTblBoxLvl;
//STRIP001      nTblBoxLvl = nFmtLvl;
//STRIP001      pFmt = (SwTableBoxFmt*) InFormat( pDoc->MakeTableBoxFmt() );
//STRIP001      RegisterFmt( *pFmt, pTable );
//STRIP001      AdjustFrmSize( pFmt );
//STRIP001      nTblBoxLvl = nOldLvl;
//STRIP001  }
//STRIP001  // Frame-Format raussuchen
//STRIP001  if( !pFmt )
//STRIP001  {
//STRIP001      pFmt = (SwTableBoxFmt*) FindFmt( nFrmFmt, SWG_FRAMEFMT );
//STRIP001      if( !pFmt )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      if( pTable != FindTable( nFrmFmt ) )
//STRIP001      {
//STRIP001          // es MUSS ein neues Format angelegt werden!
//STRIP001          SwTableBoxFmt* pNew = pDoc->MakeTableBoxFmt();
//STRIP001          // Attribute hart hineinkopieren
//STRIP001          ((SfxItemSet&)pNew->GetAttrSet()).Put( pFmt->GetAttrSet() );
//STRIP001          pNew->nFmtId = nFrmFmt;
//STRIP001          ReRegisterFmt( *pFmt, *pNew, pTable );
//STRIP001          pFmt = pNew;
//STRIP001          AdjustFrmSize( pFmt );
//STRIP001          aFile.nFlags |= SWGF_NO_FRAMES;
//STRIP001      }
//STRIP001  }
//STRIP001  SwTableBoxPtr pBox;
//STRIP001  if( r.cur() == SWG_CONTENTS )
//STRIP001  {
//STRIP001      r.undonext();
//STRIP001      pBox = new SwTableBox( pFmt, rPos, pUpper );
//STRIP001      long nSaveFrmSizeAdj = nFrmSizeAdj; // Tabellen in FlyFrames
//STRIP001      FillSection( rPos );
//STRIP001      nFrmSizeAdj = nSaveFrmSizeAdj;      // zerstoeren nFrmSizeAdj!
//STRIP001  } else
//STRIP001      pBox = new SwTableBox( pFmt, nLines, pUpper );
//STRIP001  rBoxes.C40_INSERT( SwTableBox, pBox, (USHORT)idx );
//STRIP001  while( r.cur() == SWG_COMMENT || r.cur() == SWG_DATA ) r.skipnext();
//STRIP001  // Falls Zeilen vorhanden, diese ausgeben
//STRIP001  for( int i = 0; i < nLines && r.good(); i++)
//STRIP001  {
//STRIP001      if( r.cur() != SWG_TABLELINE )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      InTableLine( pBox->GetTabLines(), pBox, i, rPos, pTable );
//STRIP001  }
//STRIP001 }

// Einlesen einer Zeile

//STRIP001 void SwSwgReader::InTableLine
//STRIP001  ( SwTableLines& rLines, SwTableBoxPtr pUpper, int idx, SwNodeIndex& rPos,
//STRIP001    const SwTable *pTable )
//STRIP001 {
//STRIP001  short nFrmFmt, nBoxes;
//STRIP001  r >> nFrmFmt >> nBoxes;
//STRIP001  r.next();
//STRIP001  SwTableLineFmt* pFmt = NULL;
//STRIP001  // Frame-Format evtl. einlesen
//STRIP001  while( r.cur() == SWG_FRAMEFMT && r.good() )
//STRIP001  {
//STRIP001      pFmt = (SwTableLineFmt*) InFormat( pDoc->MakeTableLineFmt() );
//STRIP001      RegisterFmt( *pFmt, pTable );
//STRIP001 //       AdjustFrmSize( pFmt );
//STRIP001  }
//STRIP001  // Frame-Format raussuchen
//STRIP001  // Frame-Format raussuchen
//STRIP001  if( !pFmt )
//STRIP001  {
//STRIP001      pFmt = (SwTableLineFmt*) FindFmt( nFrmFmt, SWG_FRAMEFMT );
//STRIP001      if( !pFmt )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      if( pTable != FindTable( nFrmFmt ) )
//STRIP001      {
//STRIP001          // es MUSS ein neues Format angelegt werden!
//STRIP001          SwTableLineFmt* pNew = pDoc->MakeTableLineFmt();
//STRIP001          // Attribute hart hineinkopieren
//STRIP001          ((SfxItemSet&)pNew->GetAttrSet()).Put( pFmt->GetAttrSet() );
//STRIP001          pNew->nFmtId = nFrmFmt;
//STRIP001          ReRegisterFmt( *pFmt, *pNew, pTable );
//STRIP001          AdjustFrmSize( pFmt );
//STRIP001          pFmt = pNew;
//STRIP001          aFile.nFlags |= SWGF_NO_FRAMES;
//STRIP001      }
//STRIP001  }
//STRIP001  // Default-Werte setzen:
//STRIP001  SwTableLine* pLine = new SwTableLine( pFmt, nBoxes, pUpper);
//STRIP001  rLines.C40_INSERT( SwTableLine, pLine, (USHORT) idx );
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  while( r.cur() == SWG_COMMENT || r.cur() == SWG_DATA ) r.skipnext();
//STRIP001  // Und nun die einzelnen Zellen:
//STRIP001  for (int i = 0; i < nBoxes && r.good(); i++ )
//STRIP001  {
//STRIP001      if( r.cur() != SWG_TABLEBOX )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      InTableBox( rBoxes, i, pLine, rPos, pTable );
//STRIP001  }
//STRIP001
//STRIP001 }

// rPos zeigt anschliessend hinter die Tabelle

//STRIP001 void SwSwgReader::InTable( SwNodeIndex& rPos )
//STRIP001 {
//STRIP001  if( !bNew && pDoc->IsIdxInTbl( rPos ) )
//STRIP001  {
//STRIP001      r.skipnext(); return;
//STRIP001  }
//STRIP001  BYTE cFlags;
//STRIP001  USHORT nLines, nBoxes;
//STRIP001  r >> cFlags >> nLines >> nBoxes;
//STRIP001 //JP 16.02.99: ueberfluessiges Flag
//STRIP001 //   BOOL bModified = BOOL( ( cFlags & 0x01 ) != 0 );
//STRIP001  BOOL bHdRepeat = BOOL( ( cFlags & 0x02 ) != 0 );
//STRIP001  // Die Strukturen im Nodes-Array erzeugen
//STRIP001  // Erzeugen von:
//STRIP001  // TableNode..StartNode..TxtNode..EndNode.. (weitere Boxes) ..EndNode
//STRIP001  SwTableNode* pNd = pDoc->GetNodes().InsertTable( rPos, nBoxes,
//STRIP001                              (SwTxtFmtColl*)pDoc->GetDfltTxtFmtColl() );
//STRIP001  if( !pNd )
//STRIP001  {
//STRIP001      r.skip(); Error(); return;
//STRIP001  }
//STRIP001  rPos = *pNd;
//STRIP001  SwTable* pTbl = &pNd->GetTable();
//STRIP001 //JP 16.02.99: ueberfluessiges Flag
//STRIP001 //   if( bModified )
//STRIP001 //       pTbl->SetModified();
//STRIP001  pTbl->SetHeadlineRepeat( bHdRepeat );
//STRIP001  // Das Frame-Format der Tabelle einlesen
//STRIP001  USHORT nFrmFmt;
//STRIP001  r >> nFrmFmt;
//STRIP001  r.next();
//STRIP001  SwFrmFmt* pFmt = pDoc->MakeTblFrmFmt( pDoc->GetUniqueTblName(),
//STRIP001                                      pDoc->GetDfltFrmFmt() );
//STRIP001  if( aHdr.nVersion >= SWG_VER_LCLFMT )
//STRIP001  {
//STRIP001      while( r.cur() == SWG_FRAMEFMT && r.good() )
//STRIP001      {
//STRIP001          InFormat( pFmt );
//STRIP001          RegisterFmt( *pFmt, pTbl );
//STRIP001          nFrmFmt = IDX_NO_VALUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Wenn ein Frame-Fmt angegeben wurde, muss ein neues erzeugt werden.
//STRIP001  BOOL bGetTblSize = FALSE;
//STRIP001
//STRIP001  if( nFrmFmt != IDX_NO_VALUE )
//STRIP001  {
//STRIP001      SwFrmFmt* pLastFmt = (SwFrmFmt*) FindFmt( nFrmFmt, SWG_FRAMEFMT );
//STRIP001      if( !pLastFmt )
//STRIP001      {
//STRIP001 //JP 25.03.97: Bug ## - wenn keine TabellenAttribute gefunden werden
//STRIP001 //               dann setze die DefaultSize fuer eine Tabelle.
//STRIP001 //           Error(); return;
//STRIP001          // die Tabelle bekommt erstmal USHRT_MAX als default Size
//STRIP001          // die richtige Size wird am Ende von der 1. Line besorgt
//STRIP001          pFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, USHRT_MAX ));
//STRIP001          bGetTblSize = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Attribute hart hineinkopieren
//STRIP001          ((SfxItemSet&)pFmt->GetAttrSet()).Put( pLastFmt->GetAttrSet() );
//STRIP001          pFmt->nFmtId = nFrmFmt;
//STRIP001          ReRegisterFmt( *pLastFmt, *pFmt, pTbl );
//STRIP001          aFile.nFlags |= SWGF_NO_FRAMES;
//STRIP001      }
//STRIP001  }
//STRIP001  // Da einige FRMSIZE-Attribute zu grosse Werte enthalten,
//STRIP001  // muessen die Werte heruntergeteilt werden.
//STRIP001  nFrmSizeAdj = 1;
//STRIP001  if( SFX_ITEM_SET == pFmt->GetAttrSet().GetItemState(RES_FRM_SIZE, FALSE ))
//STRIP001  {
//STRIP001      SwFmtFrmSize aSz( pFmt->GetFrmSize() );
//STRIP001      SwTwips h = aSz.GetHeight();
//STRIP001      SwTwips w = aSz.GetWidth();
//STRIP001      while( h > 65535L || w > 65535L )
//STRIP001          w /= 2, h /= 2, nFrmSizeAdj *= 2;
//STRIP001      aSz.SetWidth( w );
//STRIP001      aSz.SetHeight( h );
//STRIP001      pFmt->SetAttr( aSz );
//STRIP001  }
//STRIP001  pFmt->Add( pTbl );
//STRIP001
//STRIP001  // Ist es eine DDE-Tabelle?
//STRIP001  SwDDEFieldType* pDDE = 0;
//STRIP001  if( r.cur() == SWG_FIELDTYPES )
//STRIP001  {
//STRIP001      pDDE = (SwDDEFieldType*) InFieldType();
//STRIP001      r.next();
//STRIP001  }
//STRIP001  // Vordefinierte Layout-Frames loeschen
//STRIP001  // beim Einfuegen stoeren diese zur Zeit
//STRIP001  if( !bNew ) pNd->DelFrms();
//STRIP001  // Die einzelnen Zeilen einlesen
//STRIP001  // aIdx zeigt auf den Startnode der ersten Box
//STRIP001  rPos = pNd->GetIndex() + 1;
//STRIP001
//STRIP001  while( r.cur() == SWG_COMMENT || r.cur() == SWG_DATA ) r.skipnext();
//STRIP001  SwTableLines& rLines = pTbl->GetTabLines();
//STRIP001  for (USHORT i = 0; i < nLines && r.good(); i++ )
//STRIP001  {
//STRIP001      if( r.cur() != SWG_TABLELINE )
//STRIP001      {
//STRIP001          Error(); return;
//STRIP001      }
//STRIP001      InTableLine( rLines, NULL, i, rPos, pTbl );
//STRIP001  }
//STRIP001
//STRIP001  if( bGetTblSize )
//STRIP001  {
//STRIP001      SwTwips nAktSize = 0;
//STRIP001      const SwTableBoxes& rBoxes = rLines[ 0 ]->GetTabBoxes();
//STRIP001      for( USHORT n = rBoxes.Count(); n; )
//STRIP001          nAktSize += rBoxes[ --n ]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001      //
//STRIP001      pFmt->LockModify();
//STRIP001      pFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nAktSize ));
//STRIP001      pFmt->UnlockModify();
//STRIP001  }
//STRIP001
//STRIP001  rPos = pNd->EndOfSectionIndex()+1;
//STRIP001  if( pDDE )
//STRIP001  {
//STRIP001      // tauschen am Node den Tabellen-Pointer aus
//STRIP001      SwDDETable* pNewTable = new SwDDETable( pNd->GetTable(),
//STRIP001                                              (SwDDEFieldType*) pDDE );
//STRIP001      pNd->SetNewTable( pNewTable, FALSE );
//STRIP001  }
//STRIP001
//STRIP001  // Layout-Frames wieder erzeugen, falls eingefuegt
//STRIP001  // und falls (MA #$.!) die Tbl nicht im FlyFrm ist
//STRIP001  if( !bNew && !nFlyLevel && !(SWGRD_FORCE & nOptions) )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *pNd->EndOfSectionNode() );
//STRIP001      pDoc->GetNodes().GoNext( &aIdx );
//STRIP001      pNd->MakeFrms( &aIdx );
//STRIP001  }
//STRIP001  nFrmSizeAdj = 1;
//STRIP001 }


// Registrieren einer Section. Der SwIndex zeigt auf den StartNode.

//STRIP001 USHORT SwSwgReader::RegisterSection( const SwNodeIndex& rIdx, USHORT nId )
//STRIP001 {
//STRIP001  SectionInfo* p;
//STRIP001  if( nSect == nSectSize )
//STRIP001  {
//STRIP001      // kein Platz mehr: um 128 erweitern
//STRIP001      p = new SectionInfo [ nSectSize + 128 ];
//STRIP001      memcpy( p, pSects, nSectSize * sizeof( SectionInfo ) );
//STRIP001      delete pSects;
//STRIP001      pSects = p;
//STRIP001      nSectSize += 128;
//STRIP001  }
//STRIP001  p = &pSects[ nSect ];
//STRIP001  p->nId = ( nId == IDX_NO_VALUE ) ? nSect : nId;
//STRIP001  // Nimm den ersten Node hinter dem StartNode.
//STRIP001  // Dadurch laesst sich StartOfSection() anwenden.
//STRIP001  p->pNode1 = pDoc->GetNodes()[ rIdx.GetIndex() + 1 ];
//STRIP001  nSect++;
//STRIP001  return p->nId;
//STRIP001
//STRIP001 }


