/*************************************************************************
 *
 *  $RCSfile: sw_docnum.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:51 $
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

#ifndef _DATE_HXX //autogen
#include <tools/date.hxx>
#endif
#ifndef _TIME_HXX //autogen
#include <tools/time.hxx>
#endif
#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif

#ifndef _FTNINFO_HXX //autogen
#include <ftninfo.hxx>
#endif
#ifndef _FTNIDX_HXX //autogen
#include <ftnidx.hxx>
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
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>       // pTOXBaseRing
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _ROLBCK_HXX
#include <rolbck.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif
#ifndef _SVX_ADJITEM_HXX
#include <bf_svx/adjitem.hxx>
#endif
namespace binfilter {

/*N*/ inline BYTE GetUpperLvlChg( BYTE nCurLvl, BYTE nLevel, USHORT nMask )
/*N*/ {
/*N*/   if( 1 < nLevel )
/*N*/   {
/*N*/       if( nCurLvl + 1 >= nLevel )
/*N*/           nCurLvl -= nLevel - 1;
/*N*/       else
/*N*/           nCurLvl = 0;
/*N*/   }
/*N*/   return (nMask - 1) & ~(( 1 << nCurLvl ) - 1);
/*N*/ }

/*N*/ void SwDoc::SetOutlineNumRule( const SwNumRule& rRule )
/*N*/ {
/*N*/   USHORT nChkLevel = 0, nChgFmtLevel = 0;
/*N*/   if( pOutlineRule )
/*N*/   {
/*N*/       USHORT nMask = 1;
/*N*/       for( BYTE n = 0; n < MAXLEVEL; ++n, nMask <<= 1 )
/*N*/       {
/*N*/           const SwNumFmt& rOld = pOutlineRule->Get( n ),
/*N*/                         & rNew = rRule.Get( n );
/*N*/           if( rOld != rNew )
/*N*/           {
/*N*/               nChgFmtLevel |= nMask;
/*N*/               if( rOld.GetAbsLSpace() != rNew.GetAbsLSpace() ||
/*N*/                   rOld.GetFirstLineOffset() != rNew.GetFirstLineOffset() )
/*N*/                   nChkLevel |= nMask;
/*N*/           }
/*N*/           else if( SVX_NUM_NUMBER_NONE > rNew.GetNumberingType() && 1 < rNew.GetIncludeUpperLevels() &&
/*N*/                   0 != (nChgFmtLevel & GetUpperLvlChg( n,
/*N*/                                           rNew.GetIncludeUpperLevels(), nMask )) )
/*?*/               nChgFmtLevel |= nMask;
/*N*/       }
/*N*/       (*pOutlineRule) = rRule;
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       nChgFmtLevel = nChkLevel = 0xffff;
/*?*/       pOutlineRule = new SwNumRule( rRule );
/*N*/   }
/*N*/   pOutlineRule->SetRuleType( OUTLINE_RULE );
/*N*/   pOutlineRule->SetName( String::CreateFromAscii(
/*N*/                                       SwNumRule::GetOutlineRuleName() ));

    // teste ob die evt. gesetzen CharFormate in diesem Document
    // definiert sind
/*N*/   pOutlineRule->CheckCharFmts( this );

    // losche aus dem Array alle Nodes, die ohne Outline Nummerierung sind
/*N*/   SwOutlineNodes& rArr = (SwOutlineNodes&)GetNodes().GetOutLineNds();
/*N*/   {
/*N*/       SwNodeNum aNoNum( NO_NUMBERING );
/*N*/       for( USHORT n = 0; n < rArr.Count(); ++n )
/*N*/       {
/*N*/           SwTxtNode* pTxtNd = rArr[n]->GetTxtNode();
/*N*/           if( pTxtNd && NO_NUMBERING == pTxtNd->GetTxtColl()->GetOutlineLevel() )
/*N*/           {
/*?*/               pTxtNd->UpdateOutlineNum( aNoNum );
/*?*/               rArr.Remove( n-- );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
    // suche alle Nodes, die neu aufgenommen werden muessen !!
    // (eigentlich koennte das auch per Modify am die Nodes propagiert
    // werden !! )
/*N*/   ULONG nStt = GetNodes().GetEndOfContent().StartOfSectionIndex();
        USHORT n=0;
/*N*/   for( n = 0; n < pTxtFmtCollTbl->Count(); ++n )
/*N*/   {
/*N*/       SwTxtFmtColl* pColl = (*pTxtFmtCollTbl)[ n ];
/*N*/       BYTE nLevel = pColl->GetOutlineLevel();
/*N*/       if( NO_NUMBERING != nLevel )
/*N*/       {
/*N*/ #ifndef NUM_RELSPACE
/*N*/           // JP 08.07.98: Einzuege aus der Outline uebernehmen.
/*N*/           //              ??Aber nur wenn sie veraendert wurden??
/*N*/           if( ( nLevel = GetRealLevel( nLevel )) < MAXLEVEL
/*N*/               /*&& 0 != (nChkLevel & (1 << nLevel ))*/ )
/*N*/           {
/*N*/               SvxLRSpaceItem aLR( (SvxLRSpaceItem&)pColl->GetAttr( RES_LR_SPACE ) );
/*N*/               const SwNumFmt& rNFmt = pOutlineRule->Get( nLevel );
/*N*/
/*N*/               // ohne Nummer immer ohne FirstLineOffset!!!!
/*N*/               short nFOfst;
/*N*/               if( pColl->GetOutlineLevel() & NO_NUMLEVEL )
/*N*/                   nFOfst = 0;
/*N*/               else
/*N*/                   nFOfst = rNFmt.GetFirstLineOffset();
/*N*/
/*N*/               if( aLR.GetTxtLeft() != rNFmt.GetAbsLSpace() ||
/*N*/                   aLR.GetTxtFirstLineOfst() != nFOfst )
/*N*/               {
/*N*/                   aLR.SetTxtFirstLineOfstValue( nFOfst );
/*N*/                   aLR.SetTxtLeft( rNFmt.GetAbsLSpace() );
/*N*/
/*N*/                   pColl->SetAttr( aLR );
/*N*/               }
/*N*/           }
/*N*/ #endif
/*N*/           SwClientIter aIter( *pColl );
/*N*/           for( SwTxtNode* pNd = (SwTxtNode*)aIter.First( TYPE( SwTxtNode ));
/*N*/                   pNd; pNd = (SwTxtNode*)aIter.Next() )
/*N*/               if( pNd->GetNodes().IsDocNodes() && nStt < pNd->GetIndex() )
/*N*/                   rArr.Insert( pNd );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   for( n = 0; n < rArr.Count(); ++n )
/*N*/   {
/*N*/       SwTxtNode* pNd = rArr[ n ]->GetTxtNode();
/*N*/       ASSERT( pNd, "was ist das fuer ein Node?" );
/*N*/       if( ( 1 << (pNd->GetTxtColl()->GetOutlineLevel() & ~NO_NUMLEVEL )
/*N*/           & nChgFmtLevel ))
/*?*/           pNd->NumRuleChgd();
/*N*/   }
/*N*/   GetNodes().UpdateOutlineNodes();        // update der Nummern
/*N*/
/*N*/   // gibt es Fussnoten && gilt Kapitelweises Nummerieren, dann updaten
/*N*/   if( GetFtnIdxs().Count() && FTNNUM_CHAPTER == GetFtnInfo().eNum )
/*?*/       GetFtnIdxs().UpdateAllFtn();
/*N*/
/*N*/   UpdateExpFlds();
/*N*/
/*N*/   SetModified();
/*N*/ }



    // Hoch-/Runterstufen
//STRIP001 BOOL SwDoc::OutlineUpDown( const SwPaM& rPam, short nOffset )
//STRIP001 {
//STRIP001  if( !GetNodes().GetOutLineNds().Count() || !nOffset )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // den Bereich feststellen
//STRIP001  const SwOutlineNodes& rOutlNds = GetNodes().GetOutLineNds();
//STRIP001  const SwNodePtr pSttNd = (SwNodePtr)&rPam.Start()->nNode.GetNode();
//STRIP001  const SwNodePtr pEndNd = (SwNodePtr)&rPam.End()->nNode.GetNode();
//STRIP001  USHORT nSttPos, nEndPos;
//STRIP001
//STRIP001  if( !rOutlNds.Seek_Entry( pSttNd, &nSttPos ) &&
//STRIP001      !nSttPos-- )
//STRIP001      // wir stehen in keiner "Outline-Section"
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( rOutlNds.Seek_Entry( pEndNd, &nEndPos ) )
//STRIP001      ++nEndPos;
//STRIP001
//STRIP001  // jetzt haben wir unseren Bereich im OutlineNodes-Array
//STRIP001  // dann prufe ersmal, ob nicht unterebenen aufgehoben werden
//STRIP001  // (Stufung ueber die Grenzen)
//STRIP001  register USHORT n;
//STRIP001
//STRIP001  // so, dann koennen wir:
//STRIP001  // 1. Vorlagen-Array anlegen
//STRIP001  SwTxtFmtColl* aCollArr[ MAXLEVEL ];
//STRIP001  memset( aCollArr, 0, sizeof( SwTxtFmtColl* ) * MAXLEVEL );
//STRIP001
//STRIP001  for( n = 0; n < pTxtFmtCollTbl->Count(); ++n )
//STRIP001  {
//STRIP001      BYTE nLevel = (*pTxtFmtCollTbl)[ n ]->GetOutlineLevel();
//STRIP001      if( nLevel < MAXLEVEL )
//STRIP001          aCollArr[ nLevel ] = (*pTxtFmtCollTbl)[ n ];
//STRIP001  }
//STRIP001
//STRIP001     /* --> #i13747#
//STRIP001
//STRIP001        Build a move table that states from which level an outline will
//STRIP001        be moved to which other level. */
//STRIP001
//STRIP001     /* the move table
//STRIP001
//STRIP001        aMoveArr[n] = m: replace aCollArr[n] with aCollArr[m]
//STRIP001     */
//STRIP001     int aMoveArr[MAXLEVEL];
//STRIP001     int nStep; // step size for searching in aCollArr: -1 or 1
//STRIP001     int nNum; // amount of steps for stepping in aCollArr
//STRIP001
//STRIP001     if (nOffset < 0)
//STRIP001     {
//STRIP001         nStep = -1;
//STRIP001         nNum = -nOffset;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         nStep = 1;
//STRIP001         nNum = nOffset;
//STRIP001     }
//STRIP001
//STRIP001     /* traverse aCollArr */
//STRIP001     for (n = 0; n < MAXLEVEL; n++)
//STRIP001     {
//STRIP001         /* If outline level n has an assigned paragraph style step
//STRIP001            nNum steps forwards (nStep == 1) or backwards (nStep ==
//STRIP001            -1).  One step is to go to the next non-null entry in
//STRIP001            aCollArr in the selected direction. If nNum steps were
//STRIP001            possible write the index of the entry found to aCollArr[n],
//STRIP001            i.e. outline level n will be replaced by outline level
//STRIP001            aCollArr[n].
//STRIP001
//STRIP001            If outline level n has no assigned paragraph style
//STRIP001            aMoveArr[n] is set to -1.
//STRIP001         */
//STRIP001         if (aCollArr[n] != NULL)
//STRIP001         {
//STRIP001             USHORT m = n;
//STRIP001             int nCount = nNum;
//STRIP001
//STRIP001             while (nCount > 0 && m + nStep >= 0 && m + nStep < MAXLEVEL)
//STRIP001             {
//STRIP001                 m += nStep;
//STRIP001
//STRIP001                 if (aCollArr[m] != NULL)
//STRIP001                     nCount--;
//STRIP001             }
//STRIP001
//STRIP001             if (nCount == 0)
//STRIP001                 aMoveArr[n] = m;
//STRIP001          else
//STRIP001              aMoveArr[n] = -1;
//STRIP001
//STRIP001         }
//STRIP001         else
//STRIP001             aMoveArr[n] = -1;
//STRIP001     }
//STRIP001
//STRIP001     /* If moving of the outline levels is applicable, i.e. for all
//STRIP001        outline levels occuring in the document there has to be a valid
//STRIP001        target outline level implied by aMoveArr. */
//STRIP001  bool bMoveApplicable = true;
//STRIP001  for (n = nSttPos; n < nEndPos; n++)
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd = rOutlNds[ n ]->GetTxtNode();
//STRIP001      SwTxtFmtColl* pColl = pTxtNd->GetTxtColl();
//STRIP001      int nLevel = pColl->GetOutlineLevel();
//STRIP001
//STRIP001      if (aMoveArr[nLevel] == -1)
//STRIP001          bMoveApplicable = false;
//STRIP001  }
//STRIP001
//STRIP001  if (! bMoveApplicable )
//STRIP001      return FALSE;
//STRIP001
//STRIP001     /* <-- #i13747 # */
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( new SwUndoOutlineLeftRight( rPam, nOffset ) );
//STRIP001  }
//STRIP001
//STRIP001  // 2. allen Nodes die neue Vorlage zuweisen
//STRIP001
//STRIP001  n = nSttPos;
//STRIP001  while( n < nEndPos)
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd = rOutlNds[ n ]->GetTxtNode();
//STRIP001      SwTxtFmtColl* pColl = pTxtNd->GetTxtColl();
//STRIP001
//STRIP001         ASSERT(pColl->GetOutlineLevel() < MAXLEVEL,
//STRIP001                "non outline node in outline nodes?");
//STRIP001
//STRIP001         int nLevel = pColl->GetOutlineLevel();
//STRIP001
//STRIP001         ASSERT(aMoveArr[nLevel] >= 0,
//STRIP001                "move table: current TxtColl not found when building table!");
//STRIP001
//STRIP001
//STRIP001         if (nLevel < MAXLEVEL && aMoveArr[nLevel] >= 0)
//STRIP001         {
//STRIP001             pColl = aCollArr[ aMoveArr[nLevel] ];
//STRIP001
//STRIP001          if (pColl != NULL)
//STRIP001              pColl = (SwTxtFmtColl*)pTxtNd->ChgFmtColl( pColl );
//STRIP001         }
//STRIP001
//STRIP001      n++;
//STRIP001      // Undo ???
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  return TRUE;
//STRIP001 }



    // Hoch-/Runter - Verschieben !
//STRIP001 BOOL SwDoc::MoveOutlinePara( const SwPaM& rPam, short nOffset )
//STRIP001 {
//STRIP001  // kein Verschiebung in den Sonderbereichen
//STRIP001  const SwPosition& rStt = *rPam.Start(),
//STRIP001                  & rEnd = &rStt == rPam.GetPoint() ? *rPam.GetMark()
//STRIP001                                                    : *rPam.GetPoint();
//STRIP001  if( !GetNodes().GetOutLineNds().Count() || !nOffset ||
//STRIP001      rStt.nNode.GetIndex() < aNodes.GetEndOfExtras().GetIndex() ||
//STRIP001      rEnd.nNode.GetIndex() < aNodes.GetEndOfExtras().GetIndex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nAktPos = 0;
//STRIP001  SwNodeIndex aSttRg( rStt.nNode ), aEndRg( rEnd.nNode );
//STRIP001
//STRIP001  // nach vorne  -> vom Start erfragen
//STRIP001  // nach hinten -> vom End erfragen
//STRIP001  if( 0 > nOffset )       // nach vorne
//STRIP001  {
//STRIP001      SwNode* pSrch = &aSttRg.GetNode();
//STRIP001      if( !GetNodes().GetOutLineNds().Seek_Entry( pSrch, &nAktPos ) )
//STRIP001      {
//STRIP001          if( !nAktPos-- )
//STRIP001              // wir stehen in keiner "Outline-Section"
//STRIP001              return FALSE;
//STRIP001
//STRIP001          // dann sollten wir den Start korrigieren !!!
//STRIP001          aSttRg = *GetNodes().GetOutLineNds()[ nAktPos ];
//STRIP001      }
//STRIP001
//STRIP001      pSrch = &aEndRg.GetNode();
//STRIP001      USHORT nTmp;
//STRIP001      if( GetNodes().GetOutLineNds().Seek_Entry( pSrch, &nTmp ))
//STRIP001          // wenn die Selection in einem OutlineNode endet, diesen noch
//STRIP001          // mitnehmen
//STRIP001          aEndRg++;
//STRIP001      else
//STRIP001      {
//STRIP001          aEndRg = nTmp < GetNodes().GetOutLineNds().Count()
//STRIP001                          ? *GetNodes().GetOutLineNds()[ nTmp ]
//STRIP001                          : GetNodes().GetEndOfContent();
//STRIP001      }
//STRIP001
//STRIP001      if( aEndRg == aSttRg )
//STRIP001          // kein Bereich, dann machen wir uns einen
//STRIP001          aEndRg++;
//STRIP001  }
//STRIP001  // nach hinten
//STRIP001  else
//STRIP001  {
//STRIP001      SwNode* pSrch = &aEndRg.GetNode();
//STRIP001      if( GetNodes().GetOutLineNds().Seek_Entry( pSrch, &nAktPos ) )
//STRIP001          ++nAktPos;
//STRIP001
//STRIP001      aEndRg = nAktPos < GetNodes().GetOutLineNds().Count()
//STRIP001                      ? *GetNodes().GetOutLineNds()[ nAktPos ]
//STRIP001                      : GetNodes().GetEndOfContent();
//STRIP001
//STRIP001      pSrch = &aSttRg.GetNode();
//STRIP001      USHORT nTmp;
//STRIP001      if( !GetNodes().GetOutLineNds().Seek_Entry( pSrch, &nTmp ) )
//STRIP001      {
//STRIP001          if( --nTmp )
//STRIP001              aSttRg = *GetNodes().GetOutLineNds()[ nTmp ];
//STRIP001          else
//STRIP001              aSttRg = *GetNodes().GetEndOfContent().StartOfSectionNode();
//STRIP001      }
//STRIP001  }
//STRIP001  // neue Position errechnen:
//STRIP001  const SwNode* pNd;
//STRIP001  if( nOffset < 0 && nAktPos < USHORT(-nOffset) )
//STRIP001      pNd = GetNodes().GetEndOfContent().StartOfSectionNode();
//STRIP001  else if( nAktPos + nOffset >= GetNodes().GetOutLineNds().Count() )
//STRIP001      pNd = &GetNodes().GetEndOfContent();
//STRIP001  else
//STRIP001      pNd = GetNodes().GetOutLineNds()[ nAktPos + nOffset ];
//STRIP001
//STRIP001  ULONG nNewPos = pNd->GetIndex();
//STRIP001
//STRIP001  ASSERT( aSttRg.GetIndex() > nNewPos || nNewPos >= aEndRg.GetIndex(),
//STRIP001              "Position liegt im MoveBereich" );
//STRIP001
//STRIP001  // wurde ein Position in den Sonderbereichen errechnet, dann
//STRIP001  // setze die Position auf den Dokumentanfang.
//STRIP001  // Sollten da Bereiche oder Tabellen stehen, so werden sie nach
//STRIP001  // hinten verschoben.
//STRIP001  nNewPos = Max( nNewPos, aNodes.GetEndOfExtras().GetIndex() + 2 );
//STRIP001
//STRIP001  long nOffs = nNewPos - ( 0 < nOffset ? aEndRg.GetIndex() : aSttRg.GetIndex());
//STRIP001  SwPaM aPam( aSttRg, aEndRg, 0, -1 );
//STRIP001  return MoveParagraph( aPam, nOffs, TRUE );
//STRIP001 }


//STRIP001 USHORT lcl_FindOutlineName( const SwNodes& rNds, const String& rName,
//STRIP001                          BOOL bExact )
//STRIP001 {
//STRIP001  USHORT nSavePos = USHRT_MAX;
//STRIP001  const SwOutlineNodes& rOutlNds = rNds.GetOutLineNds();
//STRIP001  for( USHORT n = 0; n < rOutlNds.Count(); ++n )
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd = rOutlNds[ n ]->GetTxtNode();
//STRIP001      String sTxt( pTxtNd->GetExpandTxt() );
//STRIP001      if( sTxt.Equals( rName ) )
//STRIP001      {
//STRIP001          // "exact" gefunden, setze Pos auf den Node
//STRIP001          nSavePos = n;
//STRIP001          break;
//STRIP001      }
//STRIP001      else if( !bExact && USHRT_MAX == nSavePos &&
//STRIP001                  COMPARE_EQUAL == sTxt.CompareTo( rName, rName.Len()) )
//STRIP001      {
//STRIP001          // dann vielleicht nur den den 1.Teil vom Text gefunden
//STRIP001          nSavePos = n;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nSavePos;
//STRIP001 }



//STRIP001 USHORT lcl_FindOutlineNum( const SwNodes& rNds, String& rName )
//STRIP001 {
//STRIP001  // Gueltig Nummern sind (immer nur Offsets!!!):
//STRIP001  //  ([Nummer]+\.)+  (als regulaerer Ausdruck!)
//STRIP001  //  (Nummer gefolgt von Punkt, zum 5 Wiederholungen)
//STRIP001  //  also: "1.1.", "1.", "1.1.1."
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  String sNum = rName.GetToken( 0, '.', nPos );
//STRIP001  if( STRING_NOTFOUND == nPos )
//STRIP001      return USHRT_MAX;           // ungueltige Nummer!!!
//STRIP001
//STRIP001  USHORT nLevelVal[ MAXLEVEL ];       // Nummern aller Levels
//STRIP001  memset( nLevelVal, 0, MAXLEVEL * sizeof( nLevelVal[0] ));
//STRIP001  BYTE nLevel = 0;
//STRIP001  String sName( rName );
//STRIP001
//STRIP001  while( STRING_NOTFOUND != nPos )
//STRIP001  {
//STRIP001      USHORT nVal = 0;
//STRIP001      sal_Unicode c;
//STRIP001      for( USHORT n = 0; n < sNum.Len(); ++n )
//STRIP001          if( '0' <= ( c = sNum.GetChar( n )) && c <= '9' )
//STRIP001          {
//STRIP001              nVal *= 10;  nVal += c - '0';
//STRIP001          }
//STRIP001          else if( nLevel )
//STRIP001              break;                      // "fast" gueltige Nummer
//STRIP001          else
//STRIP001              return USHRT_MAX;           // ungueltige Nummer!!!
//STRIP001
//STRIP001      if( MAXLEVEL > nLevel )
//STRIP001          nLevelVal[ nLevel++ ] = nVal;
//STRIP001
//STRIP001      sName.Erase( 0, nPos );
//STRIP001      nPos = 0;
//STRIP001      sNum = sName.GetToken( 0, '.', nPos );
//STRIP001         // #i4533# without this check all parts delimited by a dot are treated as outline numbers
//STRIP001         if(!ByteString(sNum, gsl_getSystemTextEncoding()).IsNumericAscii())
//STRIP001             nPos = STRING_NOTFOUND;
//STRIP001  }
//STRIP001  rName = sName;      // das ist der nachfolgende Text.
//STRIP001
//STRIP001  // alle Levels gelesen, dann suche mal im Document nach dieser
//STRIP001  // Gliederung:
//STRIP001  const SwOutlineNodes& rOutlNds = rNds.GetOutLineNds();
//STRIP001  // OS: ohne OutlineNodes lohnt die Suche nicht
//STRIP001  // und man spart sich einen Absturz #42958#
//STRIP001  if(!rOutlNds.Count())
//STRIP001      return USHRT_MAX;
//STRIP001  SwTxtNode* pNd;
//STRIP001  nPos = 0;
//STRIP001  BOOL bNextPos = FALSE;
//STRIP001  for( BYTE n = 0; n < nLevel; ++n )
//STRIP001  {
//STRIP001      USHORT nOff = nLevelVal[ n ];
//STRIP001      if( nOff )
//STRIP001      {
//STRIP001          USHORT nLastPos = nPos;
//STRIP001          if( bNextPos )
//STRIP001              ++nPos;
//STRIP001          bNextPos = FALSE;
//STRIP001          for( ; nPos < rOutlNds.Count(); ++nPos )
//STRIP001          {
//STRIP001              pNd = rOutlNds[ nPos ]->GetTxtNode();
//STRIP001              BYTE nLvl = pNd->GetTxtColl()->GetOutlineLevel();
//STRIP001              if( nLvl == n )
//STRIP001              {
//STRIP001                  nLastPos = nPos;
//STRIP001                  if( !--nOff )
//STRIP001                  {
//STRIP001                      bNextPos = TRUE; // auf jedenfall mit dem nachsten weiter
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( nLvl < n )     // nicht ueber den Level hinaus
//STRIP001              {
//STRIP001                  nPos = nLastPos;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001          if( nPos >= rOutlNds.Count() )
//STRIP001          {
//STRIP001              if( !n )                // auf oberster Ebene muss die
//STRIP001                  return USHRT_MAX;   // Nummer gefunden werden
//STRIP001              nPos = nLastPos;
//STRIP001          }
//STRIP001      }
//STRIP001      else if( nPos+1 < rOutlNds.Count() )
//STRIP001      {
//STRIP001          pNd = rOutlNds[ nPos+1 ]->GetTxtNode();
//STRIP001          if( n < pNd->GetTxtColl()->GetOutlineLevel() )
//STRIP001              ++nPos, bNextPos = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // jetzt sollte im nPos die richtige Position fuer den OutlineLevel
//STRIP001  // stehen:
//STRIP001  return nPos;
//STRIP001 }

    // zu diesem Gliederungspunkt


    // JP 13.06.96:
    // im Namen kann eine Nummer oder/und der Text stehen.
    // zuerst wird ueber die Nummer versucht den richtigen Eintrag zu finden.
    // Gibt es diesen, dann wird ueber den Text verglichen, od es der
    // gewuenschte ist. Ist das nicht der Fall, wird noch mal nur ueber den
    // Text gesucht. Wird dieser gefunden ist es der Eintrag. Ansonsten der,
    // der ueber die Nummer gefunden wurde.
    // Ist keine Nummer angegeben, dann nur den Text suchen.

//STRIP001 BOOL SwDoc::GotoOutline( SwPosition& rPos, const String& rName ) const
//STRIP001 {
//STRIP001  if( rName.Len() )
//STRIP001  {
//STRIP001      const SwOutlineNodes& rOutlNds = GetNodes().GetOutLineNds();
//STRIP001
//STRIP001      // 1. Schritt: ueber die Nummer:
//STRIP001      String sName( rName );
//STRIP001      USHORT nFndPos = ::lcl_FindOutlineNum( GetNodes(), sName );
//STRIP001      if( USHRT_MAX != nFndPos )
//STRIP001      {
//STRIP001          SwTxtNode* pNd = rOutlNds[ nFndPos ]->GetTxtNode();
//STRIP001             String sExpandedText = pNd->GetExpandTxt();
//STRIP001             //#i4533# leading numbers followed by a dot have been remove while
//STRIP001             //searching for the outline position
//STRIP001             //to compensate this they must be removed from the paragraphs text content, too
//STRIP001             USHORT nPos = 0;
//STRIP001             String sTempNum;
//STRIP001             while(sExpandedText.Len() && (sTempNum = sExpandedText.GetToken(0, '.', nPos)).Len() &&
//STRIP001                     STRING_NOTFOUND != nPos &&
//STRIP001                     ByteString(sTempNum, gsl_getSystemTextEncoding()).IsNumericAscii())
//STRIP001             {
//STRIP001                 sExpandedText.Erase(0, nPos);
//STRIP001                 nPos = 0;
//STRIP001             }
//STRIP001
//STRIP001             if( !sExpandedText.Equals( sName ) )
//STRIP001          {
//STRIP001              USHORT nTmp = ::lcl_FindOutlineName( GetNodes(), sName, TRUE );
//STRIP001              if( USHRT_MAX != nTmp )             // ueber den Namen gefunden
//STRIP001              {
//STRIP001                  nFndPos = nTmp;
//STRIP001                  pNd = rOutlNds[ nFndPos ]->GetTxtNode();
//STRIP001              }
//STRIP001          }
//STRIP001          rPos.nNode = *pNd;
//STRIP001          rPos.nContent.Assign( pNd, 0 );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001
//STRIP001      nFndPos = ::lcl_FindOutlineName( GetNodes(), rName, FALSE );
//STRIP001      if( USHRT_MAX != nFndPos )
//STRIP001      {
//STRIP001          SwTxtNode* pNd = rOutlNds[ nFndPos ]->GetTxtNode();
//STRIP001          rPos.nNode = *pNd;
//STRIP001          rPos.nContent.Assign( pNd, 0 );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SwDoc::SetOutlineLSpace( BYTE nLevel, short nFirstLnOfst, USHORT nLSpace )
/*N*/ {
/*N*/   if( MAXLEVEL >= nLevel )
/*N*/   {
/*N*/       const SwNumFmt& rNFmt = pOutlineRule->Get( nLevel );
/*N*/       if( nLSpace != rNFmt.GetAbsLSpace() ||
/*N*/           nFirstLnOfst != rNFmt.GetFirstLineOffset() )
/*N*/       {
/*N*/           SwNumFmt aFmt( rNFmt );
/*N*/           aFmt.SetAbsLSpace( nLSpace );
/*N*/           aFmt.SetFirstLineOffset( nFirstLnOfst );
/*N*/           pOutlineRule->Set( nLevel, aFmt );
/*N*/       }
/*N*/   }
/*N*/ }

/*  */

// --- Nummerierung -----------------------------------------

/*N*/ void SwNumRuleInfo::MakeList( SwDoc& rDoc )
/*N*/ {
/*N*/   SwModify* pMod;
/*N*/   const SfxPoolItem* pItem;
/*N*/   USHORT i, nMaxItems = rDoc.GetAttrPool().GetItemCount( RES_PARATR_NUMRULE);
/*N*/   for( i = 0; i < nMaxItems; ++i )
/*N*/       if( 0 != (pItem = rDoc.GetAttrPool().GetItem( RES_PARATR_NUMRULE, i ) ) &&
/*N*/           0 != ( pMod = (SwModify*)((SwNumRuleItem*)pItem)->GetDefinedIn()) &&
/*N*/           ((SwNumRuleItem*)pItem)->GetValue().Len() &&
/*N*/           ((SwNumRuleItem*)pItem)->GetValue() == rName )
/*N*/       {
/*N*/           if( pMod->IsA( TYPE( SwFmt )) )
/*?*/               pMod->GetInfo( *this );
/*N*/           else if( ((SwTxtNode*)pMod)->GetNodes().IsDocNodes() )
/*N*/               AddNode( *(SwTxtNode*)pMod );
/*N*/       }
/*N*/ }


/*N*/ void lcl_ChgNumRule( SwDoc& rDoc, const SwNumRule& rRule, SwHistory* pHist,
/*N*/                       SwNumRuleInfo* pRuleInfo = 0 )
/*N*/ {
/*N*/   SwNumRule* pOld = rDoc.FindNumRulePtr( rRule.GetName() );
/*N*/   ASSERT( pOld, "ohne die alte NumRule geht gar nichts" );
/*N*/
/*N*/   USHORT nChkLevel = 0, nChgFmtLevel = 0, nMask = 1;
/*N*/
        BYTE n=0;
/*N*/   for( n = 0; n < MAXLEVEL; ++n, nMask <<= 1 )
/*N*/   {
/*N*/       const SwNumFmt& rOldFmt = pOld->Get( n ),
/*N*/                     & rNewFmt = rRule.Get( n );
/*N*/
/*N*/       if( rOldFmt != rNewFmt )
/*N*/       {
/*N*/           nChgFmtLevel |= nMask;
/*N*/           if( rOldFmt.GetAbsLSpace() != rNewFmt.GetAbsLSpace() ||
/*N*/               rOldFmt.GetFirstLineOffset() != rNewFmt.GetFirstLineOffset() )
/*N*/               nChkLevel |= nMask;
/*N*/       }
/*N*/       else if( SVX_NUM_NUMBER_NONE > rNewFmt.GetNumberingType() && 1 < rNewFmt.GetIncludeUpperLevels() &&
/*N*/               0 != (nChgFmtLevel & GetUpperLvlChg( n, rNewFmt.GetIncludeUpperLevels(),nMask )) )
/*?*/           nChgFmtLevel |= nMask;
/*N*/   }
/*N*/
/*N*/   if( !nChgFmtLevel )         // es wurde nichts veraendert?
/*N*/   {
/*N*/       pOld->CheckCharFmts( &rDoc );
/*N*/       pOld->SetContinusNum( rRule.IsContinusNum() );
/*N*/       return ;
/*N*/   }
/*N*/
/*N*/   SwNumRuleInfo* pUpd;
/*N*/   if( !pRuleInfo )
/*N*/   {
/*N*/       pUpd = new SwNumRuleInfo( rRule.GetName() );
/*N*/       pUpd->MakeList( rDoc );
/*N*/   }
/*N*/   else
/*?*/       pUpd = pRuleInfo;
/*N*/
/*N*/   BYTE nLvl;
/*N*/   for( ULONG nFirst = 0, nLast = pUpd->GetList().Count();
/*N*/       nFirst < nLast; ++nFirst )
/*N*/   {
/*?*/       SwTxtNode* pTxtNd = pUpd->GetList().GetObject( nFirst );
/*?*/       if( pTxtNd->GetNum() && ( nLvl = (~NO_NUMLEVEL &
/*?*/           pTxtNd->GetNum()->GetLevel() ) ) < MAXLEVEL )
/*?*/       {
/*?*/           if( nChgFmtLevel & ( 1 << nLvl ))
/*?*/           {
/*?*/               pTxtNd->NumRuleChgd();
/*?*/
/*?*/ #ifndef NUM_RELSPACE
/*?*/               if( nChkLevel && (nChkLevel & ( 1 << nLvl )) &&
/*?*/                   pOld->IsRuleLSpace( *pTxtNd ) )
/*?*/                   pTxtNd->SetNumLSpace( TRUE );
/*?*/
/*?*/               if( pHist )
/*?*/               {
/*?*/                   const SfxPoolItem& rItem =
/*?*/                               pTxtNd->SwCntntNode::GetAttr( RES_LR_SPACE );
/*?*/                   pHist->Add( &rItem, &rItem, pTxtNd->GetIndex() );
/*?*/               }
/*?*/ #endif
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   for( n = 0; n < MAXLEVEL; ++n )
/*N*/       if( nChgFmtLevel & ( 1 << n ))
/*N*/           pOld->Set( n, rRule.GetNumFmt( n ));
/*N*/
/*N*/   pOld->CheckCharFmts( &rDoc );
/*N*/   pOld->SetInvalidRule( TRUE );
/*N*/   pOld->SetContinusNum( rRule.IsContinusNum() );
/*N*/
/*N*/   if( !pRuleInfo )
/*N*/       delete pUpd;
/*N*/ }

/*N*/ void SwDoc::SetNumRule( const SwPaM& rPam, const SwNumRule& rRule,
/*N*/                       sal_Bool bSetAbsLSpace, sal_Bool bCalledFromShell )
/*N*/ {
/*N*/   SwUndoInsNum* pUndo;
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       StartUndo( UNDO_START );        // Klammerung fuer die Attribute!
/*N*/       AppendUndo( pUndo = new SwUndoInsNum( rPam, rRule ) );
/*N*/   }
/*N*/   else
/*N*/       pUndo = 0;
/*N*/
/*N*/   ULONG nPamPos = rPam.Start()->nNode.GetIndex();
/*N*/   BOOL bSetItem = TRUE;
/*N*/   SwNumRule* pNew = FindNumRulePtr( rRule.GetName() );
/*N*/
/*N*/   if( !pNew )
/*N*/     {
/*N*/       pNew = (*pNumRuleTbl)[ MakeNumRule( rRule.GetName(), &rRule ) ];
/*N*/
        /* #109308# If called from a shell propagate an existing
            adjust item at the beginning am rPam into the new
            numbering rule. */
/*N*/         if (bCalledFromShell)
/*N*/         {
/*N*/             SwCntntNode * pCntntNode = rPam.GetCntntNode();
/*N*/
/*N*/             if (pCntntNode)
/*N*/             {
/*N*/                 SwAttrSet & rAttrSet = pCntntNode->GetSwAttrSet();
/*N*/                 const SfxPoolItem * pItem = NULL;
/*N*/
/*N*/                 if (SFX_ITEM_SET == rAttrSet.GetItemState(RES_PARATR_ADJUST,
/*N*/                                                           TRUE,
/*N*/                                                           &pItem))
/*N*/                     pNew->SetNumAdjust(((SvxAdjustItem *) pItem)->GetAdjust());
/*N*/             }
/*N*/         }
/*N*/
/*N*/     }
/*N*/   else if( rRule.IsAutoRule() && !(*pNew == rRule) )
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*N*/        // die Rule existiert schon, wurde aber veraendert. Dann muss hier
//STRIP001 /*N*/        // entschieden werden, in wie weit eine neue erzeugt wird oder
//STRIP001 /*N*/        // die aktuelle geupdatet wird.
//STRIP001 /*N*/
//STRIP001 /*N*/        // neue erzeugen wenn:
//STRIP001 /*N*/        //  - der Pam einen Bereich hat
//STRIP001 /*N*/        //  - Nodes existieren, die mit der Rule neu Starten
//STRIP001 /*N*/
//STRIP001 /*N*/        if( rPam.HasMark() )
//STRIP001 /*N*/            pNew = (*pNumRuleTbl)[ MakeNumRule( rRule.GetName(), &rRule ) ];
//STRIP001 /*N*/        else
//STRIP001 /*N*/        {
//STRIP001 /*N*/            SwNumRuleInfo aUpd( rRule.GetName() );
//STRIP001 /*N*/            aUpd.MakeList( *this );
//STRIP001 /*N*/
//STRIP001 /*N*/            // Position suchen und bestimme ob ein Node davor oder dahinter
//STRIP001 /*N*/            // einen Start erzwingt
//STRIP001 /*N*/            SwTxtNode* pTxtNd;
//STRIP001 /*N*/            ULONG nFndPos, nFirst, nLast;
//STRIP001 /*N*/
//STRIP001 /*N*/            if( TABLE_ENTRY_NOTFOUND != aUpd.GetList().SearchKey( nPamPos, &nFndPos ))
//STRIP001 /*N*/                ++nFndPos;
//STRIP001 /*N*/
//STRIP001 /*N*/            for( nLast = nFndPos; nLast < aUpd.GetList().Count(); ++nLast )
//STRIP001 /*N*/                if( ( pTxtNd = aUpd.GetList().GetObject( nLast ))->GetNum() &&
//STRIP001 /*N*/                    pTxtNd->GetNum()->IsStart() )
//STRIP001 /*N*/                    break;
//STRIP001 /*N*/            for( nFirst = nFndPos; nFirst; )
//STRIP001 /*N*/                if( ( pTxtNd = aUpd.GetList().GetObject( --nFirst ))->GetNum() &&
//STRIP001 /*N*/                    pTxtNd->GetNum()->IsStart() )
//STRIP001 /*N*/                    break;
//STRIP001 /*N*/
//STRIP001 /*N*/            bSetItem = FALSE;
//STRIP001 /*N*/            nPamPos = ULONG_MAX;
//STRIP001 /*N*/            if( !pNew->IsAutoRule() || nFirst || nLast != aUpd.GetList().Count() )
//STRIP001 /*N*/            {
//STRIP001 /*N*/                // dann neue Numerierung ueber diesen Bereich
//STRIP001 /*N*/                // definieren und den Start am Anfang/Ende zurueck setzen
//STRIP001 /*N*/                pTxtNd = aUpd.GetList().GetObject( nFirst );
//STRIP001 /*N*/                if( pTxtNd->GetNum()->IsStart() )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    ((SwNodeNum*)pTxtNd->GetNum())->SetStart( FALSE );
//STRIP001 /*N*/                    if( pUndo )
//STRIP001 /*N*/                        pUndo->SetSttNum( pTxtNd->GetIndex() );
//STRIP001 /*N*/                }
//STRIP001 /*N*/
//STRIP001 /*N*/                SwHistory* pHist = pUndo ? pUndo->GetHistory() : 0;
//STRIP001 /*N*/ #ifndef NUM_RELSPACE
//STRIP001 /*N*/                if( pHist )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    // die LRSpaces muessen zuerst gesichert werden
//STRIP001 /*N*/                    for( ULONG n = nFirst; n < nLast; ++n )
//STRIP001 /*N*/                    {
//STRIP001 /*N*/                        pTxtNd = aUpd.GetList().GetObject( n );
//STRIP001 /*N*/                        SfxPoolItem* pItem = (SfxPoolItem*)
//STRIP001 /*N*/                            &pTxtNd->SwCntntNode::GetAttr( RES_LR_SPACE );
//STRIP001 /*N*/                        pHist->Add( pItem, pItem, pTxtNd->GetIndex() );
//STRIP001 /*N*/                    }
//STRIP001 /*N*/                    pUndo->SetLRSpaceEndPos();
//STRIP001 /*N*/                }
//STRIP001 /*N*/ #endif
//STRIP001 /*N*/                SwRegHistory aRegH( pHist );
//STRIP001 /*N*/                SwNumRule* pOld = pNew;
//STRIP001 /*N*/                pNew = (*pNumRuleTbl)[ MakeNumRule( rRule.GetName(), &rRule ) ];
//STRIP001 /*N*/
//STRIP001 /*N*/                USHORT nChgFmtLevel = 0;
//STRIP001 /*N*/                for( BYTE n = 0; n < MAXLEVEL; ++n )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    const SwNumFmt& rOldFmt = pOld->Get( n ),
//STRIP001 /*N*/                                  & rNewFmt = rRule.Get( n );
//STRIP001 /*N*/
//STRIP001 /*N*/                    if( rOldFmt.GetAbsLSpace() != rNewFmt.GetAbsLSpace() ||
//STRIP001 /*N*/                        rOldFmt.GetFirstLineOffset() != rNewFmt.GetFirstLineOffset() )
//STRIP001 /*N*/                        nChgFmtLevel |= ( 1 << n );
//STRIP001 /*N*/                }
//STRIP001 /*N*/
//STRIP001 /*N*/                SwNumRuleItem aRule( pNew->GetName() );
//STRIP001 /*N*/                for( ; nFirst < nLast; ++nFirst )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    pTxtNd = aUpd.GetList().GetObject( nFirst );
//STRIP001 /*N*/
//STRIP001 /*N*/                    aRegH.RegisterInModify( pTxtNd, *pTxtNd );
//STRIP001 /*N*/
//STRIP001 /*N*/ #ifndef NUM_RELSPACE
//STRIP001 /*N*/                    BYTE nLvl = !pTxtNd->GetNum() ? NO_NUMBERING
//STRIP001 /*N*/                                    : pTxtNd->GetNum()->GetLevel() & ~NO_NUMLEVEL;
//STRIP001 /*N*/                    if( nLvl < MAXLEVEL && (nChgFmtLevel & ( 1 << nLvl )) &&
//STRIP001 /*N*/                        pOld->IsRuleLSpace( *pTxtNd ) )
//STRIP001 /*N*/                            pTxtNd->SetNumLSpace( TRUE );
//STRIP001 /*N*/ #endif
//STRIP001 /*N*/
//STRIP001 /*N*/                    pTxtNd->SwCntntNode::SetAttr( aRule );
//STRIP001 /*N*/                    pTxtNd->NumRuleChgd();
//STRIP001 /*N*/                }
//STRIP001 /*N*/            }
//STRIP001 /*N*/            else
//STRIP001 /*N*/            {
//STRIP001 /*N*/                // dann nur die Rule Updaten
//STRIP001 /*N*/                SwHistory* pHist = 0;
//STRIP001 /*N*/                if( pUndo )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    pUndo->SaveOldNumRule( *pNew );
//STRIP001 /*N*/                    pHist = pUndo->GetHistory();
//STRIP001 /*N*/                }
//STRIP001 /*N*/                ::lcl_ChgNumRule( *this, rRule, pHist, &aUpd );
//STRIP001 /*N*/                if( pUndo )
//STRIP001 /*N*/                    pUndo->SetLRSpaceEndPos();
//STRIP001 /*N*/            }
//STRIP001 /*N*/        }
/*N*/   }
/*N*/
/*N*/   if( bSetItem )
/*N*/   {
/*N*/ #ifndef NUM_RELSPACE
/*N*/       if( pUndo )
/*N*/       {
/*N*/           SwHistory* pHist = pUndo->GetHistory();
/*N*/           SwCntntNode* pCNd;
/*N*/           for( ULONG n = nPamPos, nEndPos = rPam.End()->nNode.GetIndex();
/*N*/                   n <= nEndPos; ++n )
/*N*/               if( 0 != ( pCNd = GetNodes()[ n ]->GetCntntNode() ))
/*N*/               {
/*N*/                   const SfxPoolItem& rItem = pCNd->GetAttr( RES_LR_SPACE );
/*N*/                   pHist->Add( &rItem, &rItem, n );
/*N*/               }
/*N*/           pUndo->SetLRSpaceEndPos();
/*N*/       }
/*N*/ #endif
/*N*/       Insert( rPam, SwNumRuleItem( pNew->GetName() ) );
/*N*/   }
/*N*/   UpdateNumRule( pNew->GetName(), nPamPos );
/*N*/
/*N*/   EndUndo( UNDO_END );
/*N*/
/*N*/   SetModified();
/*N*/ }

/*N*/ void SwDoc::SetNumRuleStart( const SwPosition& rPos, BOOL bFlag )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SwTxtNode* pTxtNd = rPos.nNode.GetNode().GetTxtNode();
//STRIP001  const SwNumRule* pRule;
//STRIP001  if( pTxtNd && pTxtNd->GetNum() && 0 != ( pRule = pTxtNd->GetNumRule() )
//STRIP001      && bFlag != pTxtNd->GetNum()->IsStart())
//STRIP001  {
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoNumRuleStart( rPos, bFlag ));
//STRIP001      }
//STRIP001      SwNodeNum aNum( *pTxtNd->GetNum() );
//STRIP001      aNum.SetStart( bFlag );
//STRIP001      pTxtNd->UpdateNum( aNum );
//STRIP001      UpdateNumRule( pRule->GetName(),
//STRIP001                      bFlag ? rPos.nNode.GetIndex() : ULONG_MAX );
//STRIP001      SetModified();
//STRIP001  }
/*N*/ }

/*N*/ void SwDoc::SetNodeNumStart( const SwPosition& rPos, USHORT nStt )
/*N*/ {
/*N*/   SwTxtNode* pTxtNd = rPos.nNode.GetNode().GetTxtNode();
/*N*/   const SwNumRule* pRule;
/*N*/   if( pTxtNd && pTxtNd->GetNum() && 0 != ( pRule = pTxtNd->GetNumRule() )
/*N*/       && nStt != pTxtNd->GetNum()->GetSetValue() )
/*N*/   {
/*N*/       if( DoesUndo() )
/*N*/       {
/*N*/           ClearRedo();
/*N*/           AppendUndo( new SwUndoNumRuleStart( rPos, nStt ));
/*N*/       }
/*N*/       SwNodeNum aNum( *pTxtNd->GetNum() );
/*N*/       aNum.SetSetValue( nStt );
/*N*/       pTxtNd->UpdateNum( aNum );
/*N*/       UpdateNumRule( pRule->GetName(), USHRT_MAX != nStt
/*N*/                           ? rPos.nNode.GetIndex() : ULONG_MAX );
/*N*/       SetModified();
/*N*/   }
/*N*/ }

    // loeschen geht nur, wenn die Rule niemand benutzt!
/*N*/ BOOL SwDoc::DelNumRule( const String& rName )
/*N*/ {
/*N*/   USHORT nPos = FindNumRule( rName );
/*N*/   if( USHRT_MAX != nPos && !IsUsed( *(*pNumRuleTbl)[ nPos ] ))
/*N*/   {
/*N*/       pNumRuleTbl->DeleteAndDestroy( nPos );
/*N*/       SetModified();
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ void SwDoc::ChgNumRuleFmts( const SwNumRule& rRule )
/*N*/ {
/*N*/   SwNumRule* pRule = FindNumRulePtr( rRule.GetName() );
/*N*/   if( pRule )
/*N*/   {
/*N*/       SwUndoInsNum* pUndo = 0;
/*N*/       SwHistory* pHistory = 0;
/*N*/       if( DoesUndo() && pRule->IsAutoRule() )
/*N*/       {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   ClearRedo();
//STRIP001 /*?*/            pUndo = new SwUndoInsNum( *pRule, rRule );
//STRIP001 /*?*/            pHistory = pUndo->GetHistory();
/*?*/           AppendUndo( pUndo );
/*N*/       }
/*N*/       ::binfilter::lcl_ChgNumRule( *this, rRule, pHistory );
/*N*/
/*N*/       if( pUndo )
/*?*/           {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pUndo->SetLRSpaceEndPos();
/*N*/
/*N*/       SetModified();
/*N*/   }
/*N*/ }

/*N*/ void SwDoc::StopNumRuleAnimations( OutputDevice* pOut )
/*N*/ {
/*N*/   for( USHORT n = GetNumRuleTbl().Count(); n; )
/*N*/   {
/*N*/       SwNumRuleInfo aUpd( GetNumRuleTbl()[ --n ]->GetName() );
/*N*/       aUpd.MakeList( *this );
/*N*/
/*N*/       for( ULONG nFirst = 0, nLast = aUpd.GetList().Count();
/*N*/               nFirst < nLast; ++nFirst )
/*N*/       {
/*N*/           SwTxtNode* pTNd = aUpd.GetList().GetObject( nFirst );
/*N*/
/*N*/           SwClientIter aIter( *pTNd );
/*N*/           for( SwFrm* pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) );
/*N*/                   pFrm; pFrm = (SwFrm*)aIter.Next() )
/*N*/               if( ((SwTxtFrm*)pFrm)->HasAnimation() )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 ((SwTxtFrm*)pFrm)->StopAnimation( pOut );
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 BOOL SwDoc::ReplaceNumRule( const SwPosition& rPos,
//STRIP001                          const String& rOldRule, const String& rNewRule )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwNumRule *pOldRule = FindNumRulePtr( rOldRule ),
//STRIP001            *pNewRule = FindNumRulePtr( rNewRule );
//STRIP001  if( pOldRule && pNewRule && pOldRule != pNewRule )
//STRIP001  {
//STRIP001      SwUndoInsNum* pUndo = 0;
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          StartUndo( UNDO_START );        // Klammerung fuer die Attribute!
//STRIP001          AppendUndo( pUndo = new SwUndoInsNum( rPos, *pNewRule, rOldRule ) );
//STRIP001      }
//STRIP001
//STRIP001      SwNumRuleInfo aUpd( rOldRule );
//STRIP001      aUpd.MakeList( *this );
//STRIP001
//STRIP001      // Position suchen und bestimme ob ein Node davor oder dahinter
//STRIP001      // einen Start erzwingt
//STRIP001      SwTxtNode* pTxtNd;
//STRIP001      ULONG nFndPos, nFirst, nLast;
//STRIP001
//STRIP001      if( TABLE_ENTRY_NOTFOUND != aUpd.GetList().SearchKey(
//STRIP001          rPos.nNode.GetIndex(), &nFndPos ))
//STRIP001          ++nFndPos;
//STRIP001
//STRIP001      for( nLast = nFndPos; nLast < aUpd.GetList().Count(); ++nLast )
//STRIP001          if( ( pTxtNd = aUpd.GetList().GetObject( nLast ))->GetNum() &&
//STRIP001              pTxtNd->GetNum()->IsStart() )
//STRIP001              break;
//STRIP001      for( nFirst = nFndPos; nFirst; )
//STRIP001          if( ( pTxtNd = aUpd.GetList().GetObject( --nFirst ))->GetNum() &&
//STRIP001              pTxtNd->GetNum()->IsStart() )
//STRIP001              break;
//STRIP001
//STRIP001      // dann neue Numerierung ueber diesen Bereich
//STRIP001      // definieren und den Start am Anfang/Ende zurueck setzen
//STRIP001      pTxtNd = aUpd.GetList().GetObject( nFirst );
//STRIP001      if( pTxtNd->GetNum()->IsStart() )
//STRIP001      {
//STRIP001          ((SwNodeNum*)pTxtNd->GetNum())->SetStart( FALSE );
//STRIP001          if( pUndo )
//STRIP001              pUndo->SetSttNum( pTxtNd->GetIndex() );
//STRIP001      }
//STRIP001
//STRIP001      SwRegHistory aRegH( pUndo ? pUndo->GetHistory() : 0 );
//STRIP001      USHORT nChgFmtLevel = 0;
//STRIP001      for( BYTE n = 0; n < MAXLEVEL; ++n )
//STRIP001      {
//STRIP001          const SwNumFmt& rOldFmt = pOldRule->Get( n ),
//STRIP001                          & rNewFmt = pNewRule->Get( n );
//STRIP001
//STRIP001          if( rOldFmt.GetAbsLSpace() != rNewFmt.GetAbsLSpace() ||
//STRIP001              rOldFmt.GetFirstLineOffset() != rNewFmt.GetFirstLineOffset() )
//STRIP001              nChgFmtLevel |= ( 1 << n );
//STRIP001      }
//STRIP001
//STRIP001      SwNumRuleItem aRule( rNewRule );
//STRIP001      for( ; nFirst < nLast; ++nFirst )
//STRIP001      {
//STRIP001          pTxtNd = aUpd.GetList().GetObject( nFirst );
//STRIP001
//STRIP001          aRegH.RegisterInModify( pTxtNd, *pTxtNd );
//STRIP001
//STRIP001 #ifndef NUM_RELSPACE
//STRIP001          BYTE nLvl = !pTxtNd->GetNum() ? NO_NUMBERING
//STRIP001                          : pTxtNd->GetNum()->GetLevel() & ~NO_NUMLEVEL;
//STRIP001          if( nLvl < MAXLEVEL && (nChgFmtLevel & ( 1 << nLvl )) &&
//STRIP001              pOldRule->IsRuleLSpace( *pTxtNd ) )
//STRIP001                  pTxtNd->SetNumLSpace( TRUE );
//STRIP001 #endif
//STRIP001
//STRIP001          pTxtNd->SwCntntNode::SetAttr( aRule );
//STRIP001          pTxtNd->NumRuleChgd();
//STRIP001      }
//STRIP001      EndUndo( UNDO_END );
//STRIP001      SetModified();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::NoNum( const SwPaM& rPam )
//STRIP001 {
//STRIP001 #if 0
//STRIP001 // Vielleich koennte man die Funktion auch so definieren:
//STRIP001 // den Bereich auf nicht Nummeriert setzen - sprich NO_NUMLEVEL.
//STRIP001 //
//STRIP001  ULONG nStt = rPam.GetPoint()->nNode.GetIndex(),
//STRIP001          nEnd = rPam.GetMark()->nNode.GetIndex();
//STRIP001  if( nStt > nEnd )
//STRIP001  {
//STRIP001      ULONG nTmp = nStt; nStt = nEnd; nEnd = nTmp;
//STRIP001  }
//STRIP001
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  const String* pName;
//STRIP001  String sNumRule;
//STRIP001  for( ; nStt <= nEnd; ++nStt )
//STRIP001  {
//STRIP001      SwTxtNode* pTNd = GetNodes()[ nStt ]->GetTxtNode();
//STRIP001      if( pTNd && 0 != ( pItem = pTNd->GetNoCondAttr(
//STRIP001          RES_PARATR_NUMRULE, TRUE ) ) &&
//STRIP001          ( pName = &((SwNumRuleItem*)pItem)->GetValue())->Len() )
//STRIP001      {
//STRIP001          SwNodeNum aNum;
//STRIP001          if( pTNd->GetNum() )
//STRIP001              aNum = *pTNd->GetNum();
//STRIP001          aNum.SetLevel( aNum.GetLevel() | NO_NUMLEVEL );
//STRIP001          pTNd->UpdateNum( aNum );
//STRIP001
//STRIP001          if( *pName != sNumRule )
//STRIP001          {
//STRIP001              sNumRule = *pName;
//STRIP001              SwNumRule* pRule = FindNumRulePtr( *pName );
//STRIP001              pRule->SetInvalidRule( TRUE );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // dann noch alle Updaten
//STRIP001  UpdateNumRule();
//STRIP001
//STRIP001  // irgendetwas wurde geupdatet
//STRIP001  return 0 != n;
//STRIP001 #else
//STRIP001
//STRIP001  BOOL bRet = SplitNode( *rPam.GetPoint() );
//STRIP001  // ist ueberhaupt Nummerierung im Spiel ?
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      // NoNum setzen und Upaten
//STRIP001      const SwNodeIndex& rIdx = rPam.GetPoint()->nNode;
//STRIP001      SwTxtNode* pNd = rIdx.GetNode().GetTxtNode();
//STRIP001      const SwNodeNum* pNum = pNd->GetNum();
//STRIP001      const SwNumRule* pRule = pNd->GetNumRule();
//STRIP001      if( pNum && pRule )
//STRIP001      {
//STRIP001          SwNodeNum aNum( *pNum );
//STRIP001          aNum.SetLevel( aNum.GetLevel() | NO_NUMLEVEL );
//STRIP001          pNd->UpdateNum( aNum );
//STRIP001 #ifndef NUM_RELSPACE
//STRIP001          pNd->SetNumLSpace( TRUE );
//STRIP001 #endif
//STRIP001          UpdateNumRule( pRule->GetName(), rIdx.GetIndex() );
//STRIP001          SetModified();
//STRIP001      }
//STRIP001      else
//STRIP001          bRet = FALSE;   // keine Nummerierung , ?? oder immer TRUE ??
//STRIP001  }
//STRIP001  return bRet;
//STRIP001
//STRIP001 #endif
//STRIP001 }

/*N*/ BOOL SwDoc::DelNumRules( const SwPaM& rPam )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ULONG nStt = rPam.GetPoint()->nNode.GetIndex(),
//STRIP001          nEnd = rPam.GetMark()->nNode.GetIndex();
//STRIP001  if( nStt > nEnd )
//STRIP001  {
//STRIP001      ULONG nTmp = nStt; nStt = nEnd; nEnd = nTmp;
//STRIP001  }
//STRIP001
//STRIP001  SwUndoDelNum* pUndo;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      AppendUndo( pUndo = new SwUndoDelNum( rPam ) );
//STRIP001  }
//STRIP001  else
//STRIP001      pUndo = 0;
//STRIP001
//STRIP001  SwRegHistory aRegH( pUndo ? pUndo->GetHistory() : 0 );
//STRIP001
//STRIP001  SwNumRuleItem aEmptyRule( aEmptyStr );
//STRIP001  SvxLRSpaceItem aLRSpace;
//STRIP001  String sNumRule;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  const String* pName;
//STRIP001  SwNumRule* pRule;
//STRIP001  const SwNode* pOutlNd = 0;
//STRIP001  for( ; nStt <= nEnd; ++nStt )
//STRIP001  {
//STRIP001      SwTxtNode* pTNd = GetNodes()[ nStt ]->GetTxtNode();
//STRIP001      if( pTNd && 0 != ( pItem = pTNd->GetNoCondAttr(
//STRIP001          RES_PARATR_NUMRULE, TRUE ) ) &&
//STRIP001          ( pName = &((SwNumRuleItem*)pItem)->GetValue())->Len() )
//STRIP001      {
//STRIP001          if( *pName != sNumRule )
//STRIP001          {
//STRIP001              sNumRule = *pName;
//STRIP001              pRule = FindNumRulePtr( *pName );
//STRIP001              pRule->SetInvalidRule( TRUE );
//STRIP001          }
//STRIP001
//STRIP001          // fuers Undo - Attribut Aenderungen merken
//STRIP001          aRegH.RegisterInModify( pTNd, *pTNd );
//STRIP001
//STRIP001          BOOL bResetNumRule = FALSE;
//STRIP001          const SwAttrSet* pAttrSet = pTNd->GetpSwAttrSet();
//STRIP001 #ifndef NUM_RELSPACE
//STRIP001          BYTE nLvl;
//STRIP001          const SvxLRSpaceItem* pLRSpace;
//STRIP001          if( pAttrSet && SFX_ITEM_SET == pAttrSet->GetItemState(
//STRIP001              RES_LR_SPACE, FALSE, (const SfxPoolItem**)&pLRSpace ) &&
//STRIP001              ( !pTNd->GetNum() ||
//STRIP001                (( nLvl = (~NO_NUMLEVEL & pTNd->GetNum()->GetLevel() )) <
//STRIP001                  MAXLEVEL && ( pRule->Get( nLvl ).GetAbsLSpace()
//STRIP001                                          == pLRSpace->GetTxtLeft() )) ))
//STRIP001          {
//STRIP001              if( pLRSpace->GetRight() )
//STRIP001              {
//STRIP001                  aLRSpace.SetRight( pLRSpace->GetRight() );
//STRIP001                  pTNd->SwCntntNode::SetAttr( aLRSpace );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pTNd->SwCntntNode::ResetAttr( RES_LR_SPACE );
//STRIP001                  pAttrSet = pTNd->GetpSwAttrSet();
//STRIP001              }
//STRIP001              bResetNumRule = TRUE;
//STRIP001          }
//STRIP001 #endif
//STRIP001          if( pUndo )
//STRIP001              pUndo->AddNode( *pTNd, bResetNumRule );
//STRIP001
//STRIP001          // kommt die Rule vom Node, dann Reseten, sonst auf leer setzen
//STRIP001          if( pAttrSet && SFX_ITEM_SET == pAttrSet->GetItemState(
//STRIP001              RES_PARATR_NUMRULE, FALSE ))
//STRIP001              pTNd->SwCntntNode::ResetAttr( RES_PARATR_NUMRULE );
//STRIP001          else
//STRIP001              pTNd->SwCntntNode::SetAttr( aEmptyRule );
//STRIP001
//STRIP001          pTNd->UpdateNum( SwNodeNum( NO_NUMBERING ));
//STRIP001
//STRIP001          if( RES_CONDTXTFMTCOLL == pTNd->GetFmtColl()->Which() )
//STRIP001              pTNd->ChkCondColl();
//STRIP001          else if( !pOutlNd && NO_NUMBERING !=
//STRIP001                  ((SwTxtFmtColl*)pTNd->GetFmtColl())->GetOutlineLevel() )
//STRIP001              pOutlNd = pTNd;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // dann noch alle Updaten
//STRIP001  UpdateNumRule();
//STRIP001
//STRIP001  if( pOutlNd )
//STRIP001      GetNodes().UpdtOutlineIdx( *pOutlNd );
//STRIP001
//STRIP001  // irgendetwas wurde geupdatet
//STRIP001  return 0 != sNumRule.Len();
/*N*/ }


    // zum naechsten/vorhergehenden Punkt auf gleicher Ebene

//STRIP001 BOOL lcl_IsNumOk( BYTE nSrchNum, BYTE& rLower, BYTE& rUpper,
//STRIP001                  BOOL bOverUpper, BYTE nNumber )
//STRIP001 {
//STRIP001  register BOOL bRet = FALSE;
//STRIP001  if( nNumber < MAXLEVEL )            // keine Nummerierung ueberspringen
//STRIP001  {
//STRIP001      if( bOverUpper ? nSrchNum == nNumber : nSrchNum >= nNumber )
//STRIP001          bRet = TRUE;
//STRIP001      else if( nNumber > rLower )
//STRIP001          rLower = nNumber;
//STRIP001      else if( nNumber < rUpper )
//STRIP001          rUpper = nNumber;
//STRIP001  }
//STRIP001  else if( nNumber & NO_NUMLEVEL )
//STRIP001  {
//STRIP001      nNumber &= ~NO_NUMLEVEL;
//STRIP001      if( bOverUpper ? FALSE : nSrchNum > nNumber )
//STRIP001          bRet = TRUE;
//STRIP001      else if( nNumber > rLower )
//STRIP001          rLower = nNumber;
//STRIP001      else if( nNumber < rUpper )
//STRIP001          rUpper = nNumber;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_IsValidPrevNextNumNode( const SwNodeIndex& rIdx )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwNode& rNd = rIdx.GetNode();
//STRIP001  switch( rNd.GetNodeType() )
//STRIP001  {
//STRIP001  case ND_ENDNODE:
//STRIP001      bRet = SwTableBoxStartNode == rNd.FindStartNode()->GetStartNodeType() ||
//STRIP001              rNd.FindStartNode()->IsSectionNode();
//STRIP001      break;
//STRIP001
//STRIP001  case ND_STARTNODE:
//STRIP001      bRet = SwTableBoxStartNode == ((SwStartNode&)rNd).GetStartNodeType();
//STRIP001      break;
//STRIP001
//STRIP001  case ND_SECTIONNODE:            // der ist erlaubt, also weiter
//STRIP001      bRet = TRUE;
//STRIP001      break;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_GotoNextPrevNum( SwPosition& rPos, BOOL bNext,
//STRIP001                          BOOL bOverUpper, BYTE* pUpper, BYTE* pLower )
//STRIP001 {
//STRIP001  const SwTxtNode* pNd = rPos.nNode.GetNode().GetTxtNode();
//STRIP001  const SwNumRule* pRule;
//STRIP001  if( !pNd || 0 == ( pRule = pNd->GetNumRule() ) || !pNd->GetNum() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  register BYTE nTmpNum = pNd->GetNum()->GetLevel(),
//STRIP001                nSrchNum = nTmpNum & ~NO_NUMLEVEL;
//STRIP001
//STRIP001  SwNodeIndex aIdx( rPos.nNode );
//STRIP001  if( nTmpNum & NO_NUMLEVEL )
//STRIP001  {
//STRIP001      // falls gerade mal NO_NUMLEVEL an ist, so such den vorherigen Node
//STRIP001      // mit Nummerierung
//STRIP001      BOOL bError = FALSE;
//STRIP001      do {
//STRIP001          aIdx--;
//STRIP001          if( aIdx.GetNode().IsTxtNode() )
//STRIP001          {
//STRIP001              pNd = aIdx.GetNode().GetTxtNode();
//STRIP001              if( pNd->GetNum() && pRule == pNd->GetNumRule() )
//STRIP001              {
//STRIP001                  nTmpNum = pNd->GetNum()->GetLevel();
//STRIP001                  if( !( nTmpNum & NO_NUMLEVEL &&
//STRIP001                       (( nTmpNum & ~NO_NUMLEVEL ) >= nSrchNum )) )
//STRIP001                      break;      // gefunden
//STRIP001              }
//STRIP001              else
//STRIP001                  bError = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001              bError = !lcl_IsValidPrevNextNumNode( aIdx );
//STRIP001
//STRIP001      } while( !bError );
//STRIP001      if( bError )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  BYTE nLower = nSrchNum, nUpper = nSrchNum;
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  const SwTxtNode* pLast;
//STRIP001  if( bNext )
//STRIP001      aIdx++, pLast = pNd;
//STRIP001  else
//STRIP001      aIdx--, pLast = 0;
//STRIP001
//STRIP001  while( bNext ? ( aIdx.GetIndex() < aIdx.GetNodes().Count() - 1 )
//STRIP001               : aIdx.GetIndex() )
//STRIP001  {
//STRIP001      if( aIdx.GetNode().IsTxtNode() )
//STRIP001      {
//STRIP001          pNd = aIdx.GetNode().GetTxtNode();
//STRIP001          if( pNd->GetNum() && pRule == pNd->GetNumRule() )
//STRIP001          {
//STRIP001              if( ::lcl_IsNumOk( nSrchNum, nLower, nUpper, bOverUpper,
//STRIP001                                  pNd->GetNum()->GetLevel() ))
//STRIP001              {
//STRIP001                  rPos.nNode = aIdx;
//STRIP001                  rPos.nContent.Assign( (SwTxtNode*)pNd, 0 );
//STRIP001                  bRet = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001              else
//STRIP001                  pLast = pNd;
//STRIP001          }
//STRIP001          else
//STRIP001              break;
//STRIP001      }
//STRIP001      else if( !lcl_IsValidPrevNextNumNode( aIdx ))
//STRIP001          break;
//STRIP001
//STRIP001      if( bNext )
//STRIP001          aIdx++;
//STRIP001      else
//STRIP001          aIdx--;
//STRIP001  }
//STRIP001
//STRIP001  if( !bRet && !bOverUpper && pLast )     // nicht ueber hoehere Nummmern, aber bis Ende
//STRIP001  {
//STRIP001      if( bNext )
//STRIP001      {
//STRIP001          rPos.nNode = aIdx;
//STRIP001          if( aIdx.GetNode().IsCntntNode() )
//STRIP001              rPos.nContent.Assign( aIdx.GetNode().GetCntntNode(), 0 );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rPos.nNode.Assign( *pLast );
//STRIP001          rPos.nContent.Assign( (SwTxtNode*)pLast, 0 );
//STRIP001      }
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      if( pUpper )
//STRIP001          *pUpper = nUpper;
//STRIP001      if( pLower )
//STRIP001          *pLower = nLower;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::GotoNextNum( SwPosition& rPos, BOOL bOverUpper,
//STRIP001                          BYTE* pUpper, BYTE* pLower  )
//STRIP001 {
//STRIP001    return ::lcl_GotoNextPrevNum( rPos, TRUE, bOverUpper, pUpper, pLower );
//STRIP001 }



//STRIP001 BOOL SwDoc::GotoPrevNum( SwPosition& rPos, BOOL bOverUpper,
//STRIP001                          BYTE* pUpper, BYTE* pLower  )
//STRIP001 {
//STRIP001    return ::lcl_GotoNextPrevNum( rPos, FALSE, bOverUpper, pUpper, pLower );
//STRIP001 }

/*N*/ BOOL SwDoc::NumUpDown( const SwPaM& rPam, BOOL bDown )
/*N*/ {
/*N*/   ULONG nStt = rPam.GetPoint()->nNode.GetIndex(),
/*N*/           nEnd = rPam.GetMark()->nNode.GetIndex();
/*N*/   if( nStt > nEnd )
/*N*/   {
/*?*/       ULONG nTmp = nStt; nStt = nEnd; nEnd = nTmp;
/*N*/   }
/*N*/
/*N*/   char nDiff = bDown ? 1 : -1;
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       AppendUndo( new SwUndoNumUpDown( rPam, nDiff ) );
/*N*/   }
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/   String sNumRule;
/*N*/   const SfxPoolItem* pItem;
/*N*/   const String* pName;
/*N*/   for( ; nStt <= nEnd; ++nStt )
/*N*/   {
/*N*/       SwTxtNode* pTNd = GetNodes()[ nStt ]->GetTxtNode();
/*N*/       if( pTNd && 0 != ( pItem = pTNd->GetNoCondAttr(
/*N*/           RES_PARATR_NUMRULE, TRUE ) ) &&
/*N*/           ( pName = &((SwNumRuleItem*)pItem)->GetValue())->Len() )
/*N*/       {
/*N*/           BYTE nLevel = pTNd->GetNum()->GetLevel();
/*N*/           if( ( -1 == nDiff && 0 < ( nLevel & ~NO_NUMLEVEL )) ||
/*N*/               ( 1 == nDiff && MAXLEVEL - 1 > ( nLevel & ~NO_NUMLEVEL ) ) )
/*N*/           {
/*N*/               nLevel += nDiff;
/*N*/               SwNodeNum aNum( *pTNd->GetNum() );
/*N*/               aNum.SetLevel( nLevel );
/*N*/
/*N*/               pTNd->UpdateNum( aNum );
/*N*/ #ifndef NUM_RELSPACE
/*N*/               pTNd->SetNumLSpace( TRUE );
/*N*/ #endif
/*N*/               if( *pName != sNumRule )
/*N*/               {
/*N*/                   sNumRule = *pName;
/*N*/                   SwNumRule* pRule = FindNumRulePtr( *pName );
/*N*/                   pRule->SetInvalidRule( TRUE );
/*N*/               }
/*N*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( bRet )
/*N*/   {
/*N*/       UpdateNumRule();
/*N*/       SetModified();
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 BOOL SwDoc::MoveParagraph( const SwPaM& rPam, long nOffset, BOOL bIsOutlMv )
//STRIP001 {
//STRIP001  const SwPosition *pStt = rPam.Start(), *pEnd = rPam.End();
//STRIP001
//STRIP001  ULONG nStIdx = pStt->nNode.GetIndex();
//STRIP001  ULONG nEndIdx = pEnd->nNode.GetIndex();
//STRIP001  ULONG nInStIdx, nInEndIdx;
//STRIP001  long nOffs = nOffset;
//STRIP001  if( nOffset > 0 )
//STRIP001  {
//STRIP001      nInEndIdx = nEndIdx;
//STRIP001      nEndIdx += nOffset;
//STRIP001      ++nOffs;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nInEndIdx = nStIdx - 1;
//STRIP001      nStIdx += nOffset;
//STRIP001  }
//STRIP001  nInStIdx = nInEndIdx + 1;
//STRIP001  // Folgende Absatzbloecke sollen vertauscht werden:
//STRIP001  // [ nStIdx, nInEndIdx ] mit [ nInStIdx, nEndIdx ]
//STRIP001
//STRIP001  SwNode *pStartNd = GetNodes()[ nStIdx ];
//STRIP001  SwNode *pEndNd = GetNodes()[ nEndIdx ];
//STRIP001  if( !pStartNd->IsCntntNode() || !pEndNd->IsCntntNode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pStartNd = pStartNd->FindStartNode();
//STRIP001  pEndNd = pEndNd->FindStartNode();
//STRIP001  // Es muss sich alles in einem Bereich abspielen
//STRIP001  if( pStartNd != pEndNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // auf Redlining testen - darf die Selektion ueberhaupt verschoben
//STRIP001  // werden?
//STRIP001  if( !IsIgnoreRedline() )
//STRIP001  {
//STRIP001      USHORT nRedlPos = GetRedlinePos( pStt->nNode.GetNode(), REDLINE_DELETE );
//STRIP001      if( USHRT_MAX != nRedlPos )
//STRIP001      {
//STRIP001          SwPosition aStPos( *pStt ), aEndPos( *pEnd );
//STRIP001          aStPos.nContent = 0;
//STRIP001          SwCntntNode* pCNd = pEnd->nNode.GetNode().GetCntntNode();
//STRIP001          aEndPos.nContent = pCNd ? pCNd->Len() : 1;
//STRIP001          BOOL bCheckDel = TRUE;
//STRIP001
//STRIP001          // es existiert fuer den Bereich irgendein Redline-Delete-Object
//STRIP001          for( ; nRedlPos < GetRedlineTbl().Count(); ++nRedlPos )
//STRIP001          {
//STRIP001              const SwRedline* pTmp = GetRedlineTbl()[ nRedlPos ];
//STRIP001              if( !bCheckDel || REDLINE_DELETE == pTmp->GetType() )
//STRIP001              {
//STRIP001                  const SwPosition *pRStt = pTmp->Start(), *pREnd = pTmp->End();
//STRIP001                  switch( ComparePosition( *pRStt, *pREnd, aStPos, aEndPos ))
//STRIP001                  {
//STRIP001                  case POS_COLLIDE_START:
//STRIP001                  case POS_BEHIND:            // Pos1 liegt hinter Pos2
//STRIP001                      nRedlPos = GetRedlineTbl().Count();
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_COLLIDE_END:
//STRIP001                  case POS_BEFORE:            // Pos1 liegt vor Pos2
//STRIP001                      break;
//STRIP001                  case POS_INSIDE:            // Pos1 liegt vollstaendig in Pos2
//STRIP001                      // ist erlaubt, aber checke dann alle nachfolgenden
//STRIP001                      // auf Ueberlappungen
//STRIP001                      bCheckDel = FALSE;
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OUTSIDE:           // Pos2 liegt vollstaendig in Pos1
//STRIP001                  case POS_EQUAL:             // Pos1 ist genauso gross wie Pos2
//STRIP001                  case POS_OVERLAP_BEFORE:    // Pos1 ueberlappt Pos2 am Anfang
//STRIP001                  case POS_OVERLAP_BEHIND:    // Pos1 ueberlappt Pos2 am Ende
//STRIP001                      return FALSE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  {
//STRIP001      // DataChanged vorm verschieben verschicken, dann bekommt
//STRIP001      // man noch mit, welche Objecte sich im Bereich befinden.
//STRIP001      // Danach koennen sie vor/hinter der Position befinden.
//STRIP001      SwDataChanged aTmp( rPam, 0 );
//STRIP001  }
//STRIP001
//STRIP001  SwNodeIndex aIdx( nOffset > 0 ? pEnd->nNode : pStt->nNode, nOffs );
//STRIP001  SwNodeRange aMvRg( pStt->nNode, 0, pEnd->nNode, +1 );
//STRIP001
//STRIP001  SwRedline* pOwnRedl = 0;
//STRIP001  if( IsRedlineOn() )
//STRIP001  {
//STRIP001      // wenn der Bereich komplett im eigenen Redline liegt, kann es
//STRIP001      // verschoben werden!
//STRIP001      USHORT nRedlPos = GetRedlinePos( pStt->nNode.GetNode(), REDLINE_INSERT );
//STRIP001      if( USHRT_MAX != nRedlPos )
//STRIP001      {
//STRIP001          SwRedline* pTmp = GetRedlineTbl()[ nRedlPos ];
//STRIP001          const SwPosition *pRStt = pTmp->Start(), *pREnd = pTmp->End();
//STRIP001          SwRedline aTmpRedl( REDLINE_INSERT, rPam );
//STRIP001          const SwCntntNode* pCEndNd = pEnd->nNode.GetNode().GetCntntNode();
//STRIP001          // liegt komplett im Bereich, und ist auch der eigene Redline?
//STRIP001          if( aTmpRedl.IsOwnRedline( *pTmp ) &&
//STRIP001              (pRStt->nNode < pStt->nNode ||
//STRIP001              (pRStt->nNode == pStt->nNode && !pRStt->nContent.GetIndex()) ) &&
//STRIP001              (pEnd->nNode < pREnd->nNode ||
//STRIP001              (pEnd->nNode == pREnd->nNode &&
//STRIP001               pCEndNd ? pREnd->nContent.GetIndex() == pCEndNd->Len()
//STRIP001                       : !pREnd->nContent.GetIndex() )) )
//STRIP001          {
//STRIP001              pOwnRedl = pTmp;
//STRIP001              if( nRedlPos + 1 < GetRedlineTbl().Count() )
//STRIP001              {
//STRIP001                  pTmp = GetRedlineTbl()[ nRedlPos+1 ];
//STRIP001                  if( *pTmp->Start() == *pREnd )
//STRIP001                      // dann doch nicht!
//STRIP001                      pOwnRedl = 0;
//STRIP001              }
//STRIP001
//STRIP001              if( pOwnRedl &&
//STRIP001                  !( pRStt->nNode <= aIdx && aIdx <= pREnd->nNode ))
//STRIP001              {
//STRIP001                  // nicht in sich selbst, dann auch nicht moven
//STRIP001                  pOwnRedl = 0;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( !pOwnRedl )
//STRIP001      {
//STRIP001          StartUndo( UNDO_START );
//STRIP001
//STRIP001          // zuerst das Insert, dann das Loeschen
//STRIP001          SwPosition aInsPos( aIdx );
//STRIP001          aInsPos.nContent.Assign( aIdx.GetNode().GetCntntNode(), 0 );
//STRIP001
//STRIP001          SwPaM aPam( pStt->nNode, aMvRg.aEnd );
//STRIP001
//STRIP001          SwPaM& rOrigPam = (SwPaM&)rPam;
//STRIP001          rOrigPam.DeleteMark();
//STRIP001          rOrigPam.GetPoint()->nNode = aIdx.GetIndex() - 1;
//STRIP001
//STRIP001          BOOL bDelLastPara = !aInsPos.nNode.GetNode().IsCntntNode();
//STRIP001
//STRIP001             /* #101076# When copying to a non-content node Copy will
//STRIP001                insert a paragraph before that node and insert before
//STRIP001                that inserted node. Copy creates an SwUndoInserts that
//STRIP001                does not cover the extra paragraph. Thus we insert the
//STRIP001                extra paragraph ourselves, _with_ correct undo
//STRIP001                information. */
//STRIP001             if (bDelLastPara)
//STRIP001             {
//STRIP001                 /* aInsPos points to the non-content node. Move it to
//STRIP001                    the previous content node. */
//STRIP001                 SwPaM aInsPam(aInsPos);
//STRIP001                 BOOL bMoved = aInsPam.Move(fnMoveBackward);
//STRIP001                 ASSERT(bMoved, "No content node found!");
//STRIP001
//STRIP001                 if (bMoved)
//STRIP001                 {
//STRIP001                     /* Append the new node after the content node
//STRIP001                        found. The new position to insert the moved
//STRIP001                        paragraph at is before the inserted
//STRIP001                        paragraph. */
//STRIP001                     AppendTxtNode(*aInsPam.GetPoint());
//STRIP001                     aInsPos = *aInsPam.GetPoint();
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001          Copy( aPam, aInsPos );
//STRIP001          if( bDelLastPara )
//STRIP001          {
//STRIP001              // dann muss der letzte leere Node wieder entfernt werden
//STRIP001              aIdx = aInsPos.nNode;
//STRIP001              SwCntntNode* pCNd = GetNodes().GoPrevious( &aInsPos.nNode );
//STRIP001              xub_StrLen nCLen = 0; if( pCNd ) nCLen = pCNd->Len();
//STRIP001              aInsPos.nContent.Assign( pCNd, nCLen );
//STRIP001
//STRIP001              // alle die im zu loeschenden Node stehen, mussen auf den
//STRIP001              // naechsten umgestezt werden
//STRIP001              SwPosition* pPos;
//STRIP001              for( USHORT n = 0; n < GetRedlineTbl().Count(); ++n )
//STRIP001              {
//STRIP001                  SwRedline* pTmp = GetRedlineTbl()[ n ];
//STRIP001                  if( ( pPos = &pTmp->GetBound(TRUE))->nNode == aIdx )
//STRIP001                  {
//STRIP001                      pPos->nNode++;
//STRIP001                      pPos->nContent.Assign( pPos->nNode.GetNode().GetCntntNode(),0);
//STRIP001                  }
//STRIP001                  if( ( pPos = &pTmp->GetBound(FALSE))->nNode == aIdx )
//STRIP001                  {
//STRIP001                      pPos->nNode++;
//STRIP001                      pPos->nContent.Assign( pPos->nNode.GetNode().GetCntntNode(),0);
//STRIP001                  }
//STRIP001              }
//STRIP001              CorrRel( aIdx, aInsPos, 0, FALSE );
//STRIP001
//STRIP001              pCNd->JoinNext();
//STRIP001          }
//STRIP001
//STRIP001          rOrigPam.GetPoint()->nNode++;
//STRIP001          rOrigPam.GetPoint()->nContent.Assign( rOrigPam.GetCntntNode(), 0 );
//STRIP001
//STRIP001          SwRedlineMode eOld = GetRedlineMode();
//STRIP001          checkRedlining(eOld);
//STRIP001          if( DoesUndo() )
//STRIP001          {
//STRIP001 //JP 06.01.98: MUSS noch optimiert werden!!!
//STRIP001 SetRedlineMode( REDLINE_ON | REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE );
//STRIP001              AppendUndo( new SwUndoRedlineDelete( aPam, UNDO_DELETE ));
//STRIP001          }
//STRIP001
//STRIP001             SwRedline* pNewRedline = new SwRedline( REDLINE_DELETE, aPam );
//STRIP001
//STRIP001             // #101654# prevent assertion from aPam's target being deleted
//STRIP001             // (Alternatively, one could just let aPam go out of scope, but
//STRIP001             //  that requires touching a lot of code.)
//STRIP001             aPam.GetBound(TRUE).nContent.Assign( NULL, 0 );
//STRIP001             aPam.GetBound(FALSE).nContent.Assign( NULL, 0 );
//STRIP001
//STRIP001             AppendRedline( pNewRedline );
//STRIP001
//STRIP001 //JP 06.01.98: MUSS noch optimiert werden!!!
//STRIP001 SetRedlineMode( eOld );
//STRIP001          EndUndo( UNDO_END );
//STRIP001          SetModified();
//STRIP001
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !pOwnRedl && !IsIgnoreRedline() && GetRedlineTbl().Count() )
//STRIP001  {
//STRIP001      SplitRedline( SwPaM( aIdx ));
//STRIP001  }
//STRIP001
//STRIP001  ULONG nRedlSttNd, nRedlEndNd;
//STRIP001  if( pOwnRedl )
//STRIP001  {
//STRIP001      const SwPosition *pRStt = pOwnRedl->Start(), *pREnd = pOwnRedl->End();
//STRIP001      nRedlSttNd = pRStt->nNode.GetIndex();
//STRIP001      nRedlEndNd = pREnd->nNode.GetIndex();
//STRIP001  }
//STRIP001
//STRIP001  SwUndoMoveNum* pUndo = 0;
//STRIP001  if( DoesUndo() )
//STRIP001      pUndo = new SwUndoMoveNum( rPam, nOffset, bIsOutlMv );
//STRIP001
//STRIP001
//STRIP001  Move( aMvRg, aIdx, DOC_MOVEREDLINES );
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndo->SetStartNode( rPam.Start()->nNode.GetIndex() );
//STRIP001      AppendUndo( pUndo );
//STRIP001  }
//STRIP001
//STRIP001  if( pOwnRedl )
//STRIP001  {
//STRIP001      SwPosition *pRStt = pOwnRedl->Start(), *pREnd = pOwnRedl->End();
//STRIP001      if( pRStt->nNode.GetIndex() != nRedlSttNd )
//STRIP001      {
//STRIP001          pRStt->nNode = nRedlSttNd;
//STRIP001          pRStt->nContent.Assign( pRStt->nNode.GetNode().GetCntntNode(),0);
//STRIP001      }
//STRIP001      if( pREnd->nNode.GetIndex() != nRedlEndNd )
//STRIP001      {
//STRIP001          pREnd->nNode = nRedlEndNd;
//STRIP001          SwCntntNode* pCNd = pREnd->nNode.GetNode().GetCntntNode();
//STRIP001          xub_StrLen nL = 0; if( pCNd ) nL = pCNd->Len();
//STRIP001          pREnd->nContent.Assign( pCNd, nL );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SwDoc::NumOrNoNum( const SwNodeIndex& rIdx, BOOL bDel, BOOL bOutline )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwNodeNum* pNum;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  const SwNumRule* pRule;
//STRIP001  SwTxtNode* pTNd = rIdx.GetNode().GetTxtNode();
//STRIP001
//STRIP001  if( pTNd &&
//STRIP001      ( bOutline
//STRIP001          ? (NO_NUMBERING != pTNd->GetTxtColl()->GetOutlineLevel() &&
//STRIP001             0 != ( pNum = pTNd->GetOutlineNum()) &&
//STRIP001             0 != ( pRule = GetOutlineNumRule()) )
//STRIP001          : ( 0 != (pItem = pTNd->GetNoCondAttr(RES_PARATR_NUMRULE,TRUE)) &&
//STRIP001              ((SwNumRuleItem*)pItem)->GetValue().Len() &&
//STRIP001              0 != ( pNum = pTNd->GetNum()) &&
//STRIP001              0 != ( pRule = FindNumRulePtr(
//STRIP001                  ((SwNumRuleItem*)pItem)->GetValue() )) )) &&
//STRIP001      (bDel ? 0 != ( pNum->GetLevel() & NO_NUMLEVEL )
//STRIP001           : 0 == ( pNum->GetLevel() & NO_NUMLEVEL ) ) &&
//STRIP001      SVX_NUM_NUMBER_NONE != pRule->Get( GetRealLevel(pNum->GetLevel()) ).GetNumberingType() )
//STRIP001  {
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoNumOrNoNum( rIdx, bDel, bOutline ) );
//STRIP001      }
//STRIP001      SwNodeNum aNum( *pNum );
//STRIP001      if( bDel )
//STRIP001          aNum.SetLevel( aNum.GetLevel() & ~NO_NUMLEVEL );
//STRIP001      else
//STRIP001          aNum.SetLevel( aNum.GetLevel() | NO_NUMLEVEL );
//STRIP001
//STRIP001      if( bOutline )
//STRIP001      {
//STRIP001          pTNd->UpdateOutlineNum( aNum );
//STRIP001          GetNodes().UpdtOutlineIdx( *pTNd );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pTNd->UpdateNum( aNum );
//STRIP001 #ifndef NUM_RELSPACE
//STRIP001          pTNd->SetNumLSpace( TRUE );
//STRIP001 #endif
//STRIP001          ((SwNumRule*)pRule)->SetInvalidRule( TRUE );
//STRIP001          UpdateNumRule( pRule->GetName(), rIdx.GetIndex() );
//STRIP001      }
//STRIP001      bRet = TRUE;
//STRIP001      SetModified();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ SwNumRule* SwDoc::GetCurrNumRule( const SwPosition& rPos ) const
/*N*/ {
/*N*/   SwNumRule* pRet = 0;
/*N*/   const SfxPoolItem* pItem;
/*N*/   SwTxtNode* pTNd = rPos.nNode.GetNode().GetTxtNode();
/*N*/
/*N*/   if( pTNd && 0 != ( pItem = pTNd->GetNoCondAttr( RES_PARATR_NUMRULE, TRUE ) ) &&
/*N*/       ((SwNumRuleItem*)pItem)->GetValue().Len() )
/*N*/       pRet = FindNumRulePtr( ((SwNumRuleItem*)pItem)->GetValue() );
/*N*/   return pRet;
/*N*/ }

/*N*/ USHORT SwDoc::FindNumRule( const String& rName ) const
/*N*/ {
/*N*/   for( USHORT n = pNumRuleTbl->Count(); n; )
/*N*/       if( (*pNumRuleTbl)[ --n ]->GetName() == rName )
/*N*/           return n;
/*
//JP 20.11.97: sollte man im Find neue Rule anlegen??
                erstmal nicht
    USHORT nPoolId = GetPoolId( rName, GET_POOLID_NUMRULE );
    if( USHRT_MAX != nPoolId )
    {
        SwDoc* pThis = (SwDoc*)this;
        SwNumRule* pR = pThis->GetNumRuleFromPool( nPoolId );
        for( n = pNumRuleTbl->Count(); n; )
            if( (*pNumRuleTbl)[ --n ] == pR )
                 return n;
    }
*/
/*N*/   return USHRT_MAX;
/*N*/ }

/*N*/ SwNumRule* SwDoc::FindNumRulePtr( const String& rName ) const
/*N*/ {
/*N*/   for( USHORT n = pNumRuleTbl->Count(); n; )
/*N*/       if( (*pNumRuleTbl)[ --n ]->GetName() == rName )
/*N*/           return (*pNumRuleTbl)[ n ];
/*N*/
/*
//JP 20.11.97: sollte man im Find neue Rule anlegen??
                 erstmal nicht
    USHORT nPoolId = GetPoolId( rName, GET_POOLID_NUMRULE );
     if( USHRT_MAX != nPoolId )
    {
         SwDoc* pThis = (SwDoc*)this;
        return pThis->GetNumRuleFromPool( nPoolId );
    }
*/
/*N*/   return 0;
/*N*/ }

/*N*/ USHORT SwDoc::MakeNumRule( const String &rName, const SwNumRule* pCpy )
/*N*/ {
/*N*/   SwNumRule* pNew;
/*N*/   if( pCpy )
/*N*/   {
/*N*/       pNew = new SwNumRule( *pCpy );
/*N*/       pNew->SetName( GetUniqueNumRuleName( &rName ));
/*N*/       if( pNew->GetName() != rName )
/*N*/       {
/*?*/           pNew->SetPoolFmtId( USHRT_MAX );
/*?*/           pNew->SetPoolHelpId( USHRT_MAX );
/*?*/           pNew->SetPoolHlpFileId( UCHAR_MAX );
/*N*/       }
/*N*/       pNew->CheckCharFmts( this );
/*N*/   }
/*N*/   else
/*N*/       pNew = new SwNumRule( GetUniqueNumRuleName( &rName ) );
/*N*/   USHORT nRet = pNumRuleTbl->Count();
/*N*/   pNumRuleTbl->Insert( pNew, nRet );
/*N*/   return nRet;
/*N*/ }
/*N*/
/*N*/ String SwDoc::GetUniqueNumRuleName( const String* pChkStr, BOOL bAutoNum ) const
/*N*/ {
/*N*/   String aName;
/*N*/   if( bAutoNum )
/*N*/   {
/*N*/       long n = Time().GetTime();
/*N*/       n += Date().GetDate();
/*N*/       aName = String::CreateFromInt32( n );
/*N*/       if( pChkStr && !pChkStr->Len() )
/*N*/           pChkStr = 0;
/*N*/   }
/*N*/   else if( pChkStr && pChkStr->Len() )
/*N*/       aName = *pChkStr;
/*N*/   else
/*N*/   {
/*?*/       pChkStr = 0;
/*?*/       aName = SW_RESSTR( STR_NUMRULE_DEFNAME );
/*N*/   }
/*N*/
/*N*/   USHORT nNum, nTmp, nFlagSize = ( pNumRuleTbl->Count() / 8 ) +2;
/*N*/   BYTE* pSetFlags = new BYTE[ nFlagSize ];
/*N*/   memset( pSetFlags, 0, nFlagSize );
/*N*/
/*N*/   xub_StrLen nNmLen = aName.Len();
/*N*/   if( !bAutoNum && pChkStr )
/*N*/   {
/*?*/       while( nNmLen-- && '0' <= aName.GetChar( nNmLen ) &&
/*?*/                          '9' >= aName.GetChar( nNmLen ) )
/*?*/           ; //nop
/*?*/
/*?*/       if( ++nNmLen < aName.Len() )
/*?*/       {
/*?*/           aName.Erase( nNmLen );
/*?*/           pChkStr = 0;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   const SwNumRule* pNumRule;
        USHORT n=0;
/*N*/   for( n = 0; n < pNumRuleTbl->Count(); ++n )
/*N*/       if( 0 != ( pNumRule = (*pNumRuleTbl)[ n ] ) )
/*N*/       {
/*N*/           const String& rNm = pNumRule->GetName();
/*N*/           if( rNm.Match( aName ) == nNmLen )
/*N*/           {
/*N*/               // Nummer bestimmen und das Flag setzen
/*N*/               nNum = rNm.Copy( nNmLen ).ToInt32();
/*N*/               if( nNum-- && nNum < pNumRuleTbl->Count() )
/*N*/                   pSetFlags[ nNum / 8 ] |= (0x01 << ( nNum & 0x07 ));
/*N*/           }
/*N*/           if( pChkStr && pChkStr->Equals( rNm ) )
/*N*/               pChkStr = 0;
/*N*/       }
/*N*/
/*N*/   if( !pChkStr )
/*N*/   {
/*N*/       // alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/       nNum = pNumRuleTbl->Count();
/*N*/       for( n = 0; n < nFlagSize; ++n )
/*N*/           if( 0xff != ( nTmp = pSetFlags[ n ] ))
/*N*/           {
/*N*/               // also die Nummer bestimmen
/*N*/               nNum = n * 8;
/*N*/               while( nTmp & 1 )
/*N*/                   ++nNum, nTmp >>= 1;
/*N*/               break;
/*N*/           }
/*N*/
/*N*/   }
/*N*/   delete [] pSetFlags;
/*N*/   if( pChkStr && pChkStr->Len() )
/*N*/       return *pChkStr;
/*N*/   return aName += String::CreateFromInt32( ++nNum );
/*N*/ }

/*N*/ const SwNode* lcl_FindBaseNode( const SwNode& rNd )
/*N*/ {
/*N*/   const SwNodes& rNds = rNd.GetNodes();
/*N*/   ULONG nNdIdx = rNd.GetIndex();
/*N*/   if( nNdIdx > rNds.GetEndOfExtras().GetIndex() )
/*N*/       return rNds.GetEndOfContent().FindStartNode();
/*N*/
/*N*/   const SwNode* pSttNd = rNds[ ULONG(0) ]->FindStartNode();
/*N*/   const SwNode* pNd = rNd.FindStartNode();
/*N*/   while( pSttNd != pNd->FindStartNode()->FindStartNode() )
/*?*/       pNd = pNd->FindStartNode();
/*N*/   return pNd;
/*N*/ }


/*N*/ void SwDoc::UpdateNumRule()
/*N*/ {
/*N*/   SwNumRuleTbl& rNmTbl = GetNumRuleTbl();
/*N*/   for( USHORT n = 0; n < rNmTbl.Count(); ++n )
/*N*/       if( rNmTbl[ n ]->IsInvalidRule() )
/*N*/           UpdateNumRule( rNmTbl[ n ]->GetName(), ULONG_MAX );
/*N*/ }
/*N*/
/*N*/ void SwDoc::UpdateNumRule( const String& rName, ULONG nUpdPos )
/*N*/ {
/*N*/   SwNumRuleInfo aUpd( rName );
/*N*/   aUpd.MakeList( *this );
/*N*/
/*N*/   if( ULONG_MAX == nUpdPos )
/*N*/       nUpdPos = 0;
/*N*/   else
/*N*/       aUpd.GetList().SearchKey( nUpdPos, &nUpdPos );
/*N*/
/*N*/   SwNumRule* pRule = FindNumRulePtr( rName );
/*N*/   if( nUpdPos < aUpd.GetList().Count() )
/*N*/   {
/*N*/       USHORT nInitLevels = USHRT_MAX; // Bitfeld fuer die Levels!
/*N*/                                       // TRUE: starte mit NumFmt Start
/*N*/       USHORT nNumVal = 0;
/*N*/       SwNodeNum aNum( 0 );
/*N*/
/*N*/       if( pRule->IsContinusNum() )
/*?*/           nNumVal = pRule->Get( 0 ).GetStart();
/*N*/
/*N*/       SwTxtNode* pStt = aUpd.GetList().GetObject( nUpdPos );
/*N*/       SwTxtNode* pPrev = nUpdPos ? aUpd.GetList().GetObject( nUpdPos-1 ) : 0;
/*N*/       const SwNode* pBaseNd = lcl_FindBaseNode( *pStt );
/*N*/       if( pPrev  && lcl_FindBaseNode( *pPrev ) == pBaseNd )
/*N*/       {
/*N*/           if( pPrev->GetNum() )
/*N*/           {
/*N*/               const SwNodeNum* pPrevNdNum = pPrev->GetNum();
/*N*/               if( pPrevNdNum->GetLevel() & NO_NUMLEVEL )
/*N*/               {
/*N*/                     // OD 10.12.2002 #106111# - use correct search level
/*N*/                     BYTE nSrchLvl = GetRealLevel( pStt->GetNum()->GetLevel() );
/*N*/                   pPrevNdNum = 0;
/*N*/                   ULONG nArrPos = nUpdPos-1;
/*N*/                   while( nArrPos-- )
/*N*/                   {
/*N*/                       pPrev = aUpd.GetList().GetObject( nArrPos );
/*N*/                       if( lcl_FindBaseNode( *pPrev ) != pBaseNd )
/*N*/                           break;
/*N*/
/*N*/                       if( 0 != ( pPrevNdNum = pPrev->GetNum() ))
/*N*/                       {
/*N*/                           // uebergeordnete Ebene
/*N*/                           if( nSrchLvl > (pPrevNdNum->GetLevel() &~ NO_NUMLEVEL))
/*N*/                           {
/*N*/                               pPrevNdNum = 0;
/*N*/                               break;
/*N*/                           }
/*N*/                           // gleiche Ebene und kein NO_NUMLEVEL
/*N*/                           if( nSrchLvl == (pPrevNdNum->GetLevel() &~ NO_NUMLEVEL)
/*N*/                               && !( pPrevNdNum->GetLevel() & NO_NUMLEVEL ))
/*N*/                               break;
/*N*/
/*N*/                           pPrevNdNum = 0;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               if( pPrevNdNum )
/*N*/               {
/*N*/                   aNum = *pPrevNdNum;
/*N*/                   aNum.SetStart( FALSE );
/*N*/                   aNum.SetSetValue( USHRT_MAX );
/*N*/               }
/*N*/           }
/*N*/           nInitLevels = 0;
/*N*/             // OD 10.12.2002 #106111# - sublevels have to be restarted.
/*N*/             for ( int nSubLvl = GetRealLevel( aNum.GetLevel() ) + 1; nSubLvl < MAXLEVEL; ++nSubLvl)
/*N*/                 nInitLevels |= ( 1 << nSubLvl );
/*N*/           nNumVal = aNum.GetLevelVal()[ GetRealLevel( aNum.GetLevel() ) ];
/*N*/       }
/*N*/
/*N*/       const SwNode* pOutlNd = 0;
/*N*/       for( ; nUpdPos < aUpd.GetList().Count(); ++nUpdPos )
/*N*/       {
/*N*/           pStt = aUpd.GetList().GetObject( nUpdPos );
/*N*/
/*N*/           const SwNode* pTmpBaseNd = lcl_FindBaseNode( *pStt );
/*N*/           if( pTmpBaseNd != pBaseNd )
/*N*/           {
/*?*/               aNum.SetLevel( 0 );
/*?*/               memset( aNum.GetLevelVal(), 0,
/*?*/                       (MAXLEVEL) * sizeof( aNum.GetLevelVal()[0]) );
/*?*/               pBaseNd = pTmpBaseNd;
/*N*/           }
/*N*/
/*N*/           BYTE nLevel = aNum.GetLevel();
/*N*/           BYTE nNdOldLvl = MAXLEVEL;
/*N*/           if( pStt->GetNum() )
/*N*/           {
/*N*/               if( NO_NUMBERING != pStt->GetNum()->GetLevel() )
/*N*/                   nNdOldLvl = nLevel = pStt->GetNum()->GetLevel();
/*N*/               if( pStt->GetNum()->IsStart() )
/*N*/               {
/*?*/                   aNum.SetStart( TRUE );
/*?*/                     // OD 10.12.2002 #106111# - correct reset of level numbers
/*?*/                     for ( int nSubLvl = nLevel; nSubLvl < MAXLEVEL; ++nSubLvl)
/*?*/                         aNum.GetLevelVal()[ nSubLvl ] = 0;
/*?*/                   if( pRule->IsContinusNum() )
/*?*/                   {
/*?*/                       nNumVal = pRule->Get( 0 ).GetStart();
/*?*/                       nInitLevels |= 1;
/*?*/                   }
/*?*/                   else
/*?*/                       nInitLevels |= ( 1 << GetRealLevel( nLevel ));
/*N*/               }
/*N*/                           else if( USHRT_MAX != pStt->GetNum()->GetSetValue() )
/*N*/               {
/*N*/                   aNum.SetSetValue( nNumVal = pStt->GetNum()->GetSetValue() );
/*N*/                     // OD 10.12.2002 #106111# - init <nInitLevels> for continues
/*N*/                     // numbering.
/*N*/                     if( pRule->IsContinusNum() )
/*N*/                         nInitLevels |= 1;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if( NO_NUMLEVEL & nLevel )      // NoNum mit Ebene
/*N*/           {
/*N*/               BYTE nPrevLvl = GetRealLevel( aNum.GetLevel() ),
/*N*/                   nCurrLvl = GetRealLevel( nLevel );
/*N*/
/*N*/               if( nPrevLvl < nCurrLvl )
/*N*/               {
/*N*/                   if( !(nInitLevels & ( 1 << nPrevLvl )) )
/*N*/                       ++nPrevLvl;
/*N*/                   for( ; nPrevLvl < nCurrLvl; ++nPrevLvl )
/*?*/                       nInitLevels |= ( 1 << nPrevLvl );
/*N*/               }
/*N*/
/*N*/               aNum.SetLevel( nLevel );
/*N*/               pStt->UpdateNum( aNum );
/*N*/           }
/*N*/           else if( NO_NUM != nLevel )
/*N*/           {
/*N*/               // beim Format mit Bitmap die Graphicen schon mal anfordern
/*N*/               const SwNumFmt* pNumFmt = pRule->GetNumFmt( GetRealLevel( nLevel ));
/*N*/               if( pNumFmt && SVX_NUM_BITMAP == pNumFmt->GetNumberingType() )
/*?*/                   pNumFmt->GetGraphic();
/*N*/
/*N*/               if( pRule->IsContinusNum() )
/*N*/               {
/*N*/                   if( !(nInitLevels & 1) &&
/*N*/                       !( pNumFmt && (SVX_NUM_CHAR_SPECIAL == pNumFmt->GetNumberingType() ||
/*N*/                                      SVX_NUM_BITMAP == pNumFmt->GetNumberingType() ||
/*N*/                                      SVX_NUM_NUMBER_NONE == pNumFmt->GetNumberingType() )))
/*?*/                       ++nNumVal;
/*?*/                   aNum.GetLevelVal()[ nLevel ] = nNumVal;
/*?*/                     // OD 10.12.2002 #106111# - reset <nInitLevels>
/*?*/                     nInitLevels &= ~1;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   BYTE nPrevLvl = GetRealLevel( aNum.GetLevel() );
/*N*/                   if( nPrevLvl < nLevel  )
/*N*/                   {
/*N*/                       // Erfrage wie geloescht werden soll:
/*N*/                       // z.B von Stufe 0 -> 1: 1 -> 0.1 ; wenn nStart = 1
/*N*/                       //  aber Stufe 1 -> 2: 1.1 -> 1.1.1 !!, nur 0.1 -> 0.0.1
/*N*/                       if( !(nInitLevels & ( 1 << nPrevLvl )) )
/*N*/                           ++nPrevLvl;
/*N*/
/*N*/                       for( int ii = nPrevLvl; ii < nLevel; ++ii )
/*N*/                       {
/*N*/                           nInitLevels &= ~( 1 << ii );
/*N*/                           aNum.GetLevelVal()[ ii ] =
/*N*/                                       pRule->Get( ii ).GetStart();
/*N*/                       }
/*N*/                       aNum.GetLevelVal()[ nLevel ] =
/*N*/                           USHRT_MAX == aNum.GetSetValue()
/*N*/                               ? pRule->Get( nLevel ).GetStart()
/*N*/                               : aNum.GetSetValue();
/*N*/                   }
/*N*/                   else if( USHRT_MAX != aNum.GetSetValue() )
/*N*/                       aNum.GetLevelVal()[ nLevel ] = aNum.GetSetValue();
/*N*/                   else if( nInitLevels & ( 1 << nLevel ))
/*N*/                       aNum.GetLevelVal()[ nLevel ] =
/*N*/                                       pRule->Get( nLevel ).GetStart();
/*N*/                   else
/*N*/                       aNum.GetLevelVal()[ nLevel ]++;
/*N*/               }
/*N*/               nInitLevels &= ~( 1 << nLevel );
/*N*/               aNum.SetLevel( nLevel );
/*N*/
/*N*/                 // OD 10.12.2002 #106111# - reset numbers of all sublevels and
/*N*/                 // note in <nInitLevels> that numbering of all sublevels have
/*N*/                 // to be restarted.
/*N*/                 for ( int nSubLvl = nLevel+1; nSubLvl < MAXLEVEL; ++nSubLvl)
/*N*/                 {
/*N*/                     aNum.GetLevelVal()[ nSubLvl ] = 0;
/*N*/                     nInitLevels |= ( 1 << nSubLvl );
/*N*/                 }
/*N*/
/*N*/               pStt->UpdateNum( aNum );
/*N*/           }
/*N*/
/*N*/ //FEATURE::CONDCOLL
/*N*/           BOOL bCheck = TRUE;
/*N*/           if( RES_CONDTXTFMTCOLL == pStt->GetFmtColl()->Which() )
/*N*/           {
/*N*/ //                SwFmtColl* pChgColl = pStt->GetCondFmtColl();
/*N*/               pStt->ChkCondColl();
/*
//JP 19.11.97:
// setzen der bedingten Vorlage aendert nichts an den Einzuegen, die bleiben
// als harte vorhanden
                if( pStt->GetCondFmtColl() )
                {
                    // es gab eine Aenderung -> harte Einzuege entfernen
                    if( pChgColl != pStt->GetCondFmtColl() )
                        pStt->ResetAttr( RES_LR_SPACE );
                    bCheck = FALSE;
                }
*/
            }
/*N*/           else if( !pOutlNd && NO_NUMBERING !=
/*N*/                   ((SwTxtFmtColl*)pStt->GetFmtColl())->GetOutlineLevel() )
/*N*/               pOutlNd = pStt;
/*N*/
/*N*/ //FEATURE::CONDCOLL
/*N*/
/*N*/ #ifndef NUM_RELSPACE
/*N*/           // hat sich eine Level - Aenderung ergeben, so setze jetzt die
/*N*/           // gueltigen Einzuege
/*N*/           if( bCheck && ( nLevel != nNdOldLvl || pStt->IsSetNumLSpace())
/*N*/               && GetRealLevel( nLevel ) < MAXLEVEL )
/*N*/           {
/*N*/               SvxLRSpaceItem aLR( ((SvxLRSpaceItem&)pStt->SwCntntNode::GetAttr(
/*N*/                                   RES_LR_SPACE )) );
/*N*/
/*N*/               const SwNumFmt& rNFmt = pRule->Get( GetRealLevel( nLevel ));
/*N*/
/*N*/               // ohne Nummer immer ohne FirstLineOffset!!!!
/*N*/               short nFOfst = rNFmt.GetFirstLineOffset();
/*N*/               if( nLevel & NO_NUMLEVEL ) nFOfst = 0;
/*N*/               aLR.SetTxtFirstLineOfstValue( nFOfst );
/*N*/               aLR.SetTxtLeft( rNFmt.GetAbsLSpace() );
/*N*/
/*N*/               pStt->SwCntntNode::SetAttr( aLR );
/*N*/           }
/*N*/           // Flag immer loeschen!
/*N*/           pStt->SetNumLSpace( FALSE );
/*N*/ #endif
/*N*/           aNum.SetStart( FALSE );
/*N*/           aNum.SetSetValue( USHRT_MAX );
/*N*/       }
/*N*/       if( pOutlNd )
/*?*/           GetNodes().UpdtOutlineIdx( *pOutlNd );
/*N*/   }
/*N*/
/*N*/   ASSERT( pRule, "die NumRule sollte schon vorhanden sein!" );
/*N*/   if( pRule )
/*N*/       pRule->SetInvalidRule( FALSE );
/*N*/ }



}
