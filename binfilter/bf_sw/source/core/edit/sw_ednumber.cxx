/*************************************************************************
 *
 *  $RCSfile: sw_ednumber.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:56 $
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
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _EDIMP_HXX
#include <edimp.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
namespace binfilter {



/*N*/ SV_IMPL_VARARR_SORT( _SwPamRanges, SwPamRange )


//STRIP001 SwPamRanges::SwPamRanges( const SwPaM& rRing )
//STRIP001 {
//STRIP001  const SwPaM* pTmp = &rRing;
//STRIP001  do {
//STRIP001      Insert( pTmp->GetMark()->nNode, pTmp->GetPoint()->nNode );
//STRIP001  } while( &rRing != ( pTmp = (const SwPaM*)pTmp->GetNext() ));
//STRIP001 }


//STRIP001 void SwPamRanges::Insert( const SwNodeIndex& rIdx1, const SwNodeIndex& rIdx2 )
//STRIP001 {
//STRIP001  SwPamRange aRg( rIdx1.GetIndex(), rIdx2.GetIndex() );
//STRIP001  if( aRg.nEnd < aRg.nStart )
//STRIP001  {   aRg.nStart = aRg.nEnd; aRg.nEnd = rIdx1.GetIndex(); }
//STRIP001
//STRIP001  USHORT nPos = 0;
//STRIP001  const SwPamRange* pTmp;
//STRIP001  if( Count() && Seek_Entry( aRg, &nPos ))        // suche Insert Position
//STRIP001  {
//STRIP001      // ist der im Array stehende kleiner ??
//STRIP001      if( ( pTmp = GetData()+ nPos )->nEnd < aRg.nEnd )
//STRIP001      {
//STRIP001          aRg.nEnd = pTmp->nEnd;
//STRIP001          Remove( nPos, 1 );      // zusammenfassen
//STRIP001      }
//STRIP001      else
//STRIP001          return;     // ende, weil schon alle zusammengefasst waren
//STRIP001  }
//STRIP001
//STRIP001  BOOL bEnde;
//STRIP001  do {
//STRIP001      bEnde = TRUE;
//STRIP001
//STRIP001      // mit dem Vorgaenger zusammenfassen ??
//STRIP001      if( nPos > 0 )
//STRIP001      {
//STRIP001          if( ( pTmp = GetData()+( nPos-1 ))->nEnd == aRg.nStart
//STRIP001              || pTmp->nEnd+1 == aRg.nStart )
//STRIP001          {
//STRIP001              aRg.nStart = pTmp->nStart;
//STRIP001              bEnde = FALSE;
//STRIP001              Remove( --nPos, 1 );        // zusammenfassen
//STRIP001          }
//STRIP001          // SSelection im Bereich ??
//STRIP001          else if( pTmp->nStart <= aRg.nStart && aRg.nEnd <= pTmp->nEnd )
//STRIP001              return;
//STRIP001      }
//STRIP001          // mit dem Nachfolger zusammenfassen ??
//STRIP001      if( nPos < Count() )
//STRIP001      {
//STRIP001          if( ( pTmp = GetData() + nPos )->nStart == aRg.nEnd ||
//STRIP001              pTmp->nStart == aRg.nEnd+1 )
//STRIP001          {
//STRIP001              aRg.nEnd = pTmp->nEnd;
//STRIP001              bEnde = FALSE;
//STRIP001              Remove( nPos, 1 );      // zusammenfassen
//STRIP001          }
//STRIP001
//STRIP001          // SSelection im Bereich ??
//STRIP001          else if( pTmp->nStart <= aRg.nStart && aRg.nEnd <= pTmp->nEnd )
//STRIP001              return;
//STRIP001      }
//STRIP001  } while( !bEnde );
//STRIP001
//STRIP001  _SwPamRanges::Insert( aRg );
//STRIP001 }



//STRIP001 SwPaM& SwPamRanges::SetPam( USHORT nArrPos, SwPaM& rPam )
//STRIP001 {
//STRIP001  ASSERT_ID( nArrPos < Count(), ERR_VAR_IDX );
//STRIP001  const SwPamRange& rTmp = *(GetData() + nArrPos );
//STRIP001  rPam.GetPoint()->nNode = rTmp.nStart;
//STRIP001  rPam.GetPoint()->nContent.Assign( rPam.GetCntntNode(), 0 );
//STRIP001  rPam.SetMark();
//STRIP001  rPam.GetPoint()->nNode = rTmp.nEnd;
//STRIP001  rPam.GetPoint()->nContent.Assign( rPam.GetCntntNode(), 0 );
//STRIP001  return rPam;
//STRIP001 }



// Numerierung Outline Regelwerk


//STRIP001 void SwEditShell::SetOutlineNumRule(const SwNumRule& rRule)
//STRIP001 {
//STRIP001  StartAllAction();       // Klammern fuers Updaten !!
//STRIP001  GetDoc()->SetOutlineNumRule(rRule);
//STRIP001  EndAllAction();
//STRIP001 }


//STRIP001 const SwNumRule* SwEditShell::GetOutlineNumRule() const
//STRIP001 {
//STRIP001  return GetDoc()->GetOutlineNumRule();
//STRIP001 }

// setzt, wenn noch keine Numerierung, sonst wird geaendert
// arbeitet mit alten und neuen Regeln, nur Differenzen aktualisieren

// Absaetze ohne Numerierung, aber mit Einzuegen

//STRIP001 BOOL SwEditShell::NoNum()
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )         // Mehrfachselektion ?
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001          bRet = bRet && GetDoc()->NoNum( aRangeArr.SetPam( n, aPam ));
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = GetDoc()->NoNum( *pCrsr );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }
// Loeschen, Splitten der Aufzaehlungsliste


//STRIP001 BOOL SwEditShell::DelNumRules()
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )         // Mehrfachselektion ?
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001          bRet = bRet && GetDoc()->DelNumRules( aRangeArr.SetPam( n, aPam ) );
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = GetDoc()->DelNumRules( *pCrsr );
//STRIP001
//STRIP001  // rufe das AttrChangeNotify auf der UI-Seite. Sollte eigentlich
//STRIP001  // ueberfluessig sein, aber VB hatte darueber eine Bugrep.
//STRIP001  CallChgLnk();
//STRIP001
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

// Hoch-/Runterstufen


//STRIP001 BOOL SwEditShell::NumUpDown( BOOL bDown )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  BOOL bRet = TRUE;
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() == pCrsr )         // keine Mehrfachselektion ?
//STRIP001      bRet = GetDoc()->NumUpDown( *pCrsr, bDown );
//STRIP001  else
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001          bRet = bRet && GetDoc()->NumUpDown( aRangeArr.SetPam( n, aPam ), bDown );
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }



//STRIP001 BOOL SwEditShell::MoveParagraph( long nOffset )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM *pCrsr = GetCrsr();
//STRIP001  if( !pCrsr->HasMark() )
//STRIP001  {
//STRIP001      // sorge dafuer, das Bound1 und Bound2 im gleichen Node stehen
//STRIP001      pCrsr->SetMark();
//STRIP001      pCrsr->DeleteMark();
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet = GetDoc()->MoveParagraph( *pCrsr, nOffset );
//STRIP001
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SwEditShell::GetCurrentOutlineLevels( sal_uInt8& rUpper, sal_uInt8& rLower )
//STRIP001 {
//STRIP001     SwPaM* pCrsr = GetCrsr();
//STRIP001  SwPaM aCrsr( *pCrsr->Start() );
//STRIP001  aCrsr.SetMark();
//STRIP001  if( pCrsr->HasMark() )
//STRIP001      *aCrsr.GetPoint() = *pCrsr->End();
//STRIP001     GetDoc()->GotoNextNum( *aCrsr.GetPoint(), FALSE,
//STRIP001                             &rUpper, &rLower );
//STRIP001 }

//STRIP001 BOOL SwEditShell::MoveNumParas( BOOL bUpperLower, BOOL bUpperLeft )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  // auf alle Selektionen ??
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  SwPaM aCrsr( *pCrsr->Start() );
//STRIP001  aCrsr.SetMark();
//STRIP001
//STRIP001  if( pCrsr->HasMark() )
//STRIP001      *aCrsr.GetPoint() = *pCrsr->End();
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  BYTE nUpperLevel, nLowerLevel;
//STRIP001  if( GetDoc()->GotoNextNum( *aCrsr.GetPoint(), FALSE,
//STRIP001                              &nUpperLevel, &nLowerLevel ))
//STRIP001  {
//STRIP001      if( bUpperLower )
//STRIP001      {
//STRIP001          // ueber die naechste Nummerierung
//STRIP001          long nOffset = 0;
//STRIP001          const SwNode* pNd;
//STRIP001
//STRIP001          if( bUpperLeft )        // verschiebe nach oben
//STRIP001          {
//STRIP001              SwPosition aPos( *aCrsr.GetMark() );
//STRIP001              if( GetDoc()->GotoPrevNum( aPos, FALSE ) )
//STRIP001                  nOffset = aPos.nNode.GetIndex() -
//STRIP001                          aCrsr.GetMark()->nNode.GetIndex();
//STRIP001              else
//STRIP001              {
//STRIP001                  ULONG nStt = aPos.nNode.GetIndex(), nIdx = nStt - 1;
//STRIP001                  while( nIdx && (
//STRIP001                      ( pNd = GetDoc()->GetNodes()[ nIdx ])->IsSectionNode() ||
//STRIP001                      ( pNd->IsEndNode() && pNd->FindStartNode()->IsSectionNode())))
//STRIP001                      --nIdx;
//STRIP001                  if( GetDoc()->GetNodes()[ nIdx ]->IsTxtNode() )
//STRIP001                      nOffset = nIdx - nStt;
//STRIP001              }
//STRIP001          }
//STRIP001          else                    // verschiebe nach unten
//STRIP001          {
//STRIP001              const SwNumRule* pOrig = aCrsr.GetNode(FALSE)->GetTxtNode()->GetNumRule();
//STRIP001              if( aCrsr.GetNode()->IsTxtNode() &&
//STRIP001                  pOrig == aCrsr.GetNode()->GetTxtNode()->GetNumRule() )
//STRIP001              {
//STRIP001                  ULONG nStt = aCrsr.GetPoint()->nNode.GetIndex(), nIdx = nStt+1;
//STRIP001                  while( nIdx < GetDoc()->GetNodes().Count()-1 && (
//STRIP001                      ( pNd = GetDoc()->GetNodes()[ nIdx ])->IsSectionNode() ||
//STRIP001                      ( pNd->IsEndNode() && pNd->FindStartNode()->IsSectionNode()) ||
//STRIP001                      ( pNd->IsTxtNode() && pOrig == ((SwTxtNode*)pNd)->GetNumRule() &&
//STRIP001                          ((SwTxtNode*)pNd)->GetNum() &&
//STRIP001                          (((SwTxtNode*)pNd)->GetNum()->GetLevel() & ~NO_NUMLEVEL) > nUpperLevel )) )
//STRIP001                      ++nIdx;
//STRIP001                  if( nStt == nIdx || !GetDoc()->GetNodes()[ nIdx ]->IsTxtNode() )
//STRIP001                      nOffset = 1;
//STRIP001                  else
//STRIP001                      nOffset = nIdx - nStt;
//STRIP001              }
//STRIP001              else
//STRIP001                  nOffset = 1;
//STRIP001          }
//STRIP001
//STRIP001          if( nOffset )
//STRIP001          {
//STRIP001              aCrsr.Move( fnMoveBackward, fnGoNode );
//STRIP001              bRet = GetDoc()->MoveParagraph( aCrsr, nOffset );
//STRIP001          }
//STRIP001      }
//STRIP001      else if( bUpperLeft ? nUpperLevel : nLowerLevel+1 < MAXLEVEL )
//STRIP001      {
//STRIP001          aCrsr.Move( fnMoveBackward, fnGoNode );
//STRIP001          bRet = GetDoc()->NumUpDown( aCrsr, !bUpperLeft );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

// Abfrage von Oultine Informationen:


//STRIP001 USHORT SwEditShell::GetOutlineCnt() const
//STRIP001 {
//STRIP001  return GetDoc()->GetNodes().GetOutLineNds().Count();
//STRIP001 }


//STRIP001 BYTE SwEditShell::GetOutlineLevel( USHORT nIdx ) const
//STRIP001 {
//STRIP001  const SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  const SwTxtFmtColl* pColl = rNds.GetOutLineNds()[ nIdx ]->GetTxtNode()->GetTxtColl();
//STRIP001  return pColl->GetOutlineLevel();
//STRIP001 }


//STRIP001 String SwEditShell::GetOutlineText( USHORT nIdx, BOOL bWithNum ) const
//STRIP001 {
//STRIP001  const SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  return rNds.GetOutLineNds()[ nIdx ]->GetTxtNode()->GetExpandTxt( 0, STRING_LEN, bWithNum );
//STRIP001 }


//STRIP001 BOOL SwEditShell::OutlineUpDown( short nOffset )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  BOOL bRet = TRUE;
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() == pCrsr )         // keine Mehrfachselektion ?
//STRIP001      bRet = GetDoc()->OutlineUpDown( *pCrsr, nOffset );
//STRIP001  else
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001          bRet = bRet && GetDoc()->OutlineUpDown(
//STRIP001                                  aRangeArr.SetPam( n, aPam ), nOffset );
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SwEditShell::MoveOutlinePara( short nOffset )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  BOOL bRet = GetDoc()->MoveOutlinePara( *GetCrsr(), nOffset );
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

// Outlines and SubOutline are ReadOnly?
//STRIP001 BOOL SwEditShell::IsProtectedOutlinePara() const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwNode& rNd = GetCrsr()->Start()->nNode.GetNode();
//STRIP001  if( rNd.IsTxtNode() )
//STRIP001  {
//STRIP001      const SwOutlineNodes& rOutlNd = GetDoc()->GetNodes().GetOutLineNds();
//STRIP001      SwNodePtr pNd = (SwNodePtr)&rNd;
//STRIP001      BOOL bFirst = TRUE;
//STRIP001      USHORT nPos;
//STRIP001      BYTE nLvl;
//STRIP001      if( !rOutlNd.Seek_Entry( pNd, &nPos ) && nPos )
//STRIP001          --nPos;
//STRIP001
//STRIP001      for( ; nPos < rOutlNd.Count(); ++nPos )
//STRIP001      {
//STRIP001          SwNodePtr pNd = rOutlNd[ nPos ];
//STRIP001          BYTE nTmpLvl = GetRealLevel( pNd->GetTxtNode()->
//STRIP001                                  GetTxtColl()->GetOutlineLevel() );
//STRIP001          if( bFirst )
//STRIP001          {
//STRIP001              nLvl = nTmpLvl;
//STRIP001              bFirst = FALSE;
//STRIP001          }
//STRIP001          else if( nLvl >= nTmpLvl )
//STRIP001              break;
//STRIP001
//STRIP001          if( pNd->IsProtect() )
//STRIP001          {
//STRIP001              bRet = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 #ifndef PRODUCT
//STRIP001  else
//STRIP001  {
//STRIP001      ASSERT(!this, "Cursor not on an outline node" );
//STRIP001  }
//STRIP001 #endif
//STRIP001  return bRet;
//STRIP001 }

/** Test whether outline may be moved (bCopy == false)
 *                           or copied (bCopy == true)
 * Verify these conditions:
 * 1) outline must be within main body (and not in redline)
 * 2) outline must not be within table
 * 3) if bCopy is set, outline must not be write protected
 */
//STRIP001 BOOL lcl_IsOutlineMoveAndCopyable( const SwDoc* pDoc, USHORT nIdx, bool bCopy )
//STRIP001 {
//STRIP001  const SwNodes& rNds = pDoc->GetNodes();
//STRIP001  const SwNode* pNd = rNds.GetOutLineNds()[ nIdx ];
//STRIP001  return pNd->GetIndex() >= rNds.GetEndOfExtras().GetIndex() &&   // 1) body
//STRIP001             !pNd->FindTableNode() &&                                // 2) table
//STRIP001             ( bCopy || !pNd->IsProtect() );                         // 3) write
//STRIP001 }

//STRIP001 BOOL SwEditShell::IsOutlineMovable( USHORT nIdx ) const
//STRIP001 {
//STRIP001     return lcl_IsOutlineMoveAndCopyable( GetDoc(), nIdx, false );
//STRIP001 }

//STRIP001 BOOL SwEditShell::IsOutlineCopyable( USHORT nIdx ) const
//STRIP001 {
//STRIP001     return lcl_IsOutlineMoveAndCopyable( GetDoc(), nIdx, true );
//STRIP001 }


//STRIP001 BOOL SwEditShell::NumOrNoNum( BOOL bNumOn, BOOL bChkStart, BOOL bOutline )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() == pCrsr && !pCrsr->HasMark() &&
//STRIP001      ( !bChkStart || !pCrsr->GetPoint()->nContent.GetIndex()) )
//STRIP001  {
//STRIP001      StartAllAction();       // Klammern fuers Updaten !!
//STRIP001      bRet = GetDoc()->NumOrNoNum( pCrsr->GetPoint()->nNode, bNumOn, bOutline );
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SwEditShell::IsNoNum( BOOL bChkStart, BOOL bOutline ) const
//STRIP001 {
//STRIP001  // ein Backspace im Absatz ohne Nummer wird zum Delete
//STRIP001  const SwTxtNode* pTxtNd;
//STRIP001  const SwNodeNum* pNum;
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001
//STRIP001  return pCrsr->GetNext() == pCrsr && !pCrsr->HasMark() &&
//STRIP001      (!bChkStart || !pCrsr->GetPoint()->nContent.GetIndex()) &&
//STRIP001      0 != ( pTxtNd = pCrsr->GetNode()->GetTxtNode()) &&
//STRIP001      ( bOutline ? (NO_NUMBERING != pTxtNd->GetTxtColl()->GetOutlineLevel() &&
//STRIP001                    0 != (pNum = pTxtNd->GetOutlineNum() ))
//STRIP001                 : (pTxtNd->GetNumRule() &&
//STRIP001                    0 != (pNum = pTxtNd->GetNum() ) )) &&
//STRIP001      0 != ( pNum->GetLevel() & NO_NUMLEVEL );
//STRIP001 }


//STRIP001 const SwNodeNum* SwEditShell::GetOutlineNum( USHORT nIdx ) const
//STRIP001 {
//STRIP001  const SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  return rNds.GetOutLineNds()[ nIdx ]->GetTxtNode()->GetOutlineNum();
//STRIP001 }


/*N*/ BYTE SwEditShell::GetNumLevel( BOOL* pHasChilds ) const
/*N*/ {
/*N*/   // gebe die akt. Ebene zurueck, auf der sich der Point vom Cursor befindet
/*N*/   BYTE nLevel = NO_NUMBERING;
/*N*/
/*N*/   SwPaM* pCrsr = GetCrsr();
/*N*/   const SwTxtNode* pTxtNd = pCrsr->GetNode()->GetTxtNode();
/*N*/   const SwNumRule* pRule = pTxtNd->GetNumRule();
/*N*/   if( pRule && pTxtNd->GetNum() )
/*N*/   {
/*N*/       nLevel = pTxtNd->GetNum()->GetLevel();
/*N*/       if( pHasChilds )
/*N*/       {
/*?*/           *pHasChilds = FALSE;
/*?*/           // dann teste ob die NumSection noch weitere UnterEbenen hat:
/*?*/           // zuerst ueber alle TextNodes und falls da nichts gefunden
/*?*/           // wurde, ueber die Formate und deren GetInfo bis zu den Nodes
/*?*/
/*?*/           BYTE nLvl = nLevel & ~NO_NUMLEVEL;
/*?*/           if( nLvl + 1 < MAXLEVEL )
/*?*/           {
/*?*/               const String& rRule = pRule->GetName();
/*?*/               SwModify* pMod;
/*?*/               const SfxPoolItem* pItem;
/*?*/               USHORT i, nMaxItems = GetDoc()->GetAttrPool().GetItemCount( RES_PARATR_NUMRULE);
/*?*/               for( i = 0; i < nMaxItems; ++i )
/*?*/                   if( 0 != (pItem = GetDoc()->GetAttrPool().GetItem( RES_PARATR_NUMRULE, i ) ) &&
/*?*/                       0 != ( pMod = (SwModify*)((SwNumRuleItem*)pItem)->GetDefinedIn()) &&
/*?*/                       ((SwNumRuleItem*)pItem)->GetValue().Len() &&
/*?*/                       ((SwNumRuleItem*)pItem)->GetValue() == rRule &&
/*?*/                       pMod->IsA( TYPE( SwTxtNode )) &&
/*?*/                       ((SwTxtNode*)pMod)->GetNodes().IsDocNodes() &&
/*?*/                       ((SwTxtNode*)pMod)->GetNum() &&
/*?*/                       nLvl < ( ((SwTxtNode*)pMod)->GetNum()->GetLevel() & ~NO_NUMLEVEL) )
/*?*/                   {
/*?*/                       *pHasChilds = TRUE;
/*?*/                       break;
/*?*/                   }
/*?*/
/*?*/               if( !*pHasChilds )
/*?*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwNRuleLowerLevel aHnt( rRule, nLvl );
//STRIP001 /*?*/                    for( i = 0; i < nMaxItems; ++i )
//STRIP001 /*?*/                        if( 0 != (pItem = GetDoc()->GetAttrPool().GetItem( RES_PARATR_NUMRULE, i ) ) &&
//STRIP001 /*?*/                            0 != ( pMod = (SwModify*)((SwNumRuleItem*)pItem)->GetDefinedIn()) &&
//STRIP001 /*?*/                            ((SwNumRuleItem*)pItem)->GetValue().Len() &&
//STRIP001 /*?*/                            ((SwNumRuleItem*)pItem)->GetValue() == rRule &&
//STRIP001 /*?*/                            pMod->IsA( TYPE( SwFmt )) &&
//STRIP001 /*?*/                            !pMod->GetInfo( aHnt ))
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            *pHasChilds = TRUE;
//STRIP001 /*?*/                            break;
//STRIP001 /*?*/                        }
/*?*/               }
/*?*/
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return nLevel;
/*N*/ }

/*N*/ const SwNumRule* SwEditShell::GetCurNumRule() const
/*N*/ {
/*N*/   return GetDoc()->GetCurrNumRule( *GetCrsr()->GetPoint() );
/*N*/ }

//STRIP001 BOOL SwEditShell::IsUsed( const SwNumRule& rRule ) const
//STRIP001 {
//STRIP001  return GetDoc()->IsUsed( rRule );
//STRIP001 }

//STRIP001 SwNumRule* SwEditShell::GetNumRuleFromPool( USHORT nId )
//STRIP001 {
//STRIP001  return GetDoc()->GetNumRuleFromPool( nId );
//STRIP001 }

//STRIP001 void SwEditShell::SetCurNumRule( const SwNumRule& rRule )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )         // Mehrfachselektion ?
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001             /* #109308# adapt to new signature of SetNumRule */
//STRIP001          GetDoc()->SetNumRule( aRangeArr.SetPam( n, aPam ), rRule,
//STRIP001                                   sal_False, sal_True );
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  else
//STRIP001         /* #109308# adapt to new signature of SetNumRule */
//STRIP001      GetDoc()->SetNumRule( *pCrsr, rRule, sal_False, sal_True );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001 }

//STRIP001 String SwEditShell::GetUniqueNumRuleName( const String* pChkStr, BOOL bAutoNum ) const
//STRIP001 {
//STRIP001  return GetDoc()->GetUniqueNumRuleName( pChkStr, bAutoNum );
//STRIP001 }

//STRIP001 void SwEditShell::ChgNumRuleFmts( const SwNumRule& rRule )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->ChgNumRuleFmts( rRule );
//STRIP001  EndAllAction();
//STRIP001 }

//STRIP001 BOOL SwEditShell::ReplaceNumRule( const String& rOldRule, const String& rNewRule )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  BOOL bRet = GetDoc()->ReplaceNumRule( *GetCrsr()->GetPoint(), rOldRule, rNewRule );
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SwEditShell::SetNumRuleStart( BOOL bFlag )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )         // Mehrfachselektion ?
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001          GetDoc()->SetNumRuleStart( *aRangeArr.SetPam( n, aPam ).GetPoint(), bFlag );
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  else
//STRIP001      GetDoc()->SetNumRuleStart( *pCrsr->GetPoint(), bFlag );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001 }

//STRIP001 BOOL SwEditShell::IsNumRuleStart() const
//STRIP001 {
//STRIP001  const SwTxtNode* pTxtNd = GetCrsr()->GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pTxtNd->GetNum() && pTxtNd->GetNumRule() )
//STRIP001      return pTxtNd->GetNum()->IsStart();
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SwEditShell::SetNodeNumStart( USHORT nStt )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )         // Mehrfachselektion ?
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_START );
//STRIP001      SwPamRanges aRangeArr( *pCrsr );
//STRIP001      SwPaM aPam( *pCrsr->GetPoint() );
//STRIP001      for( USHORT n = 0; n < aRangeArr.Count(); ++n )
//STRIP001          GetDoc()->SetNodeNumStart( *aRangeArr.SetPam( n, aPam ).GetPoint(), nStt );
//STRIP001      GetDoc()->EndUndo( UNDO_END );
//STRIP001  }
//STRIP001  else
//STRIP001      GetDoc()->SetNodeNumStart( *pCrsr->GetPoint(), nStt );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001 }

//STRIP001 USHORT SwEditShell::IsNodeNumStart() const
//STRIP001 {
//STRIP001  const SwTxtNode* pTxtNd = GetCrsr()->GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pTxtNd->GetNum() && pTxtNd->GetNumRule() )
//STRIP001      return pTxtNd->GetNum()->GetSetValue();
//STRIP001  return USHRT_MAX;
//STRIP001 }




}
