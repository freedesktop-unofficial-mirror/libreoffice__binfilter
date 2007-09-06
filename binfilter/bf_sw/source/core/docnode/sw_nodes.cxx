/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_nodes.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:07:12 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <stdlib.h>

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _SWDDETBL_HXX
#include <swddetbl.hxx>
#endif
#ifndef _FRAME_HXX
#include <frame.hxx>
#endif
namespace binfilter {//STRIP009
/*N*/ extern FASTBOOL CheckNodesRange( const SwNodeIndex& rStt,
/*N*/                           const SwNodeIndex& rEnd, FASTBOOL bChkSection );

SV_DECL_PTRARR(SwSttNdPtrs,SwStartNode*,2,2)//STRIP008 ;
} //namespace binfilter

//#define JP_DEBUG
#ifdef JP_DEBUG
#endif
namespace binfilter {


// Funktion zum bestimmen des hoechsten Levels innerhalb des Bereiches


//-----------------------------------------------------------------------

/*******************************************************************
|*  SwNodes::SwNodes
|*
|*  Beschreibung
|*      Konstruktor; legt die vier Grundsektions (PostIts,
|*      Inserts, Icons, Inhalt) an
*******************************************************************/
/*N*/ SwNodes::SwNodes( SwDoc* pDocument )
/*N*/   : pMyDoc( pDocument ), pRoot( 0 )
/*N*/ {
/*N*/   bInNodesDel = bInDelUpdOutl = bInDelUpdNum = FALSE;
/*N*/
/*N*/   ASSERT( pMyDoc, "in welchem Doc stehe ich denn?" );
/*N*/
/*N*/   ULONG nPos = 0;
/*N*/   SwStartNode* pSttNd = new SwStartNode( *this, nPos++ );
/*N*/   pEndOfPostIts = new SwEndNode( *this, nPos++, *pSttNd );
/*N*/
/*N*/   SwStartNode* pTmp = new SwStartNode( *this, nPos++ );
/*N*/   pEndOfInserts = new SwEndNode( *this, nPos++, *pTmp );
/*N*/
/*N*/   pTmp = new SwStartNode( *this, nPos++ );
/*N*/   pTmp->pStartOfSection = pSttNd;
/*N*/   pEndOfAutotext = new SwEndNode( *this, nPos++, *pTmp );
/*N*/
/*N*/   pTmp = new SwStartNode( *this, nPos++ );
/*N*/   pTmp->pStartOfSection = pSttNd;
/*N*/   pEndOfRedlines = new SwEndNode( *this, nPos++, *pTmp );
/*N*/
/*N*/   pTmp = new SwStartNode( *this, nPos++ );
/*N*/   pTmp->pStartOfSection = pSttNd;
/*N*/   pEndOfContent = new SwEndNode( *this, nPos++, *pTmp );
/*N*/
/*N*/   pOutlineNds = new SwOutlineNodes;
/*N*/ }

/*******************************************************************
|*
|*  SwNodes::~SwNodes
|*
|*  Beschreibung
|*      dtor, loescht alle Nodes, deren Pointer in diesem dynamischen
|*      Array sind. Ist kein Problem, da Nodes ausserhalb dieses
|*      Arrays nicht erzeugt werden koennen und somit auch nicht
|*      in mehreren drin sein koennen
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/

/*N*/ SwNodes::~SwNodes()
/*N*/ {
/*N*/   delete pOutlineNds;
/*N*/
/*N*/   {
/*N*/       SwNode *pNode;
/*N*/       SwNodeIndex aNdIdx( *this );
/*N*/       while( TRUE )
/*N*/       {
/*N*/           pNode = &aNdIdx.GetNode();
/*N*/           if( pNode == pEndOfContent )
/*N*/               break;
/*N*/
/*N*/           aNdIdx++;
/*N*/           delete pNode;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // jetzt muessen alle SwNodeIndizies abgemeldet sein!!!
/*N*/   delete pEndOfContent;
/*N*/ }


// Sortier-Funktion fuer das Resort der OutlineNodes-Indizies. Wenn innerhalb
// des Nodes-Arrays Elemente verschoben werden, dann muessen die Indizies
// im Outline-Array wieder in die richtige Reihenfolge sortiert werden.



/*N*/ void SwNodes::ChgNode( SwNodeIndex& rDelPos, ULONG nSize,
/*N*/                       SwNodeIndex& rInsPos, BOOL bNewFrms )
/*N*/ {
/*N*/   // im UndoBereich brauchen wir keine Frames
/*N*/   SwNodes& rNds = rInsPos.GetNodes();
/*N*/   const SwNode* pPrevInsNd = rNds[ rInsPos.GetIndex() -1 ];
/*N*/
/*N*/   //JP 03.02.99: alle Felder als invalide erklaeren, aktu. erfolgt im
/*N*/   //              Idle-Handler des Docs
/*N*/   if( GetDoc()->SetFieldsDirty( TRUE, &rDelPos.GetNode(), nSize ) &&
/*N*/       rNds.GetDoc() != GetDoc() )
/*?*/       rNds.GetDoc()->SetFieldsDirty( TRUE );
/*N*/
/*N*/   //JP 12.03.99: 63293 - Nodes vom RedlineBereich NIE aufnehmen
/*N*/   ULONG nNd = rInsPos.GetIndex();
/*N*/   BOOL bInsOutlineIdx = !(
/*N*/           rNds.GetEndOfRedlines().FindStartNode()->GetIndex() < nNd &&
/*N*/           nNd < rNds.GetEndOfRedlines().GetIndex() );
/*N*/
/*N*/   if( &rNds == this )         // im gleichen Nodes-Array -> moven !!
/*N*/   {
/*?*/       // wird von vorne nach hinten gemovt, so wird nach vorne immer
/*?*/       // nachgeschoben, d.H. die Loeschposition ist immer gleich
/*?*/       USHORT nDiff = rDelPos.GetIndex() < rInsPos.GetIndex() ? 0 : 1;
/*?*/       int bOutlineNds = FALSE;
/*?*/
/*?*/       for( ULONG n = rDelPos.GetIndex(); nSize; n += nDiff, --nSize )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwNodeIndex aDelIdx( *this, n );
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       int bSavePersData = GetDoc()->GetUndoNds() == &rNds;
/*N*/       int bRestPersData = GetDoc()->GetUndoNds() == this;
/*N*/       SwDoc* pDestDoc = rNds.GetDoc() != GetDoc() ? rNds.GetDoc() : 0;
/*N*/       if( !bRestPersData && !bSavePersData && pDestDoc )
/*?*/           bSavePersData = bRestPersData = TRUE;
/*N*/
/*N*/       String sNumRule;
/*N*/       SwNodeIndex aInsPos( rInsPos );
/*N*/       for( ULONG n = 0; n < nSize; n++ )
/*N*/       {
/*N*/           SwNode* pNd = &rDelPos.GetNode();
/*N*/
/*N*/           // NoTextNode muessen ihre Persitenten Daten mitnehmen
/*N*/           if( pNd->IsNoTxtNode() )
/*N*/           {
/*?*/               if( bSavePersData )
/*?*/               {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     ((SwNoTxtNode*)pNd)->SavePersistentData();
/*N*/           }
/*N*/           else if( pNd->IsTxtNode() )
/*N*/           {
/*N*/               SwTxtNode* pTxtNd = (SwTxtNode*)pNd;
/*N*/               // loesche die Gliederungs-Indizies aus dem alten Nodes-Array
/*N*/               if( NO_NUMBERING != pTxtNd->GetTxtColl()->GetOutlineLevel() )
/*?*/                   pOutlineNds->Remove( pNd );
/*N*/
/*N*/               // muss die Rule kopiere werden?
/*N*/               if( pDestDoc )
/*N*/               {
/*?*/                   const SwNumRule* pNumRule = pTxtNd->GetNumRule();
/*?*/                   if( pNumRule && sNumRule != pNumRule->GetName() )
/*?*/                   {
/*?*/                       sNumRule = pNumRule->GetName();
/*?*/                       SwNumRule* pDestRule = pDestDoc->FindNumRulePtr( sNumRule );
/*?*/                       if( pDestRule )
/*?*/                           pDestRule->SetInvalidRule( TRUE );
/*?*/                       else
/*?*/                           pDestDoc->MakeNumRule( sNumRule, pNumRule );
/*?*/                   }
/*N*/               }
/*N*/               else
/*N*/                   // wenns ins UndoNodes-Array gemoved wird, sollten die
/*N*/                   // Numerierungen auch aktualisiert werden.
/*N*/                   pTxtNd->InvalidateNumRule();
/*N*/           }
/*N*/
/*N*/           RemoveNode( rDelPos.GetIndex(), 1, FALSE );     // Indizies verschieben !!
/*N*/           SwCntntNode * pCNd = pNd->GetCntntNode();
/*N*/           rNds.Insert( pNd, aInsPos );
/*N*/
/*N*/           if( pCNd )
/*N*/           {
/*N*/               SwTxtNode* pTxtNd = pCNd->GetTxtNode();
/*N*/               if( pTxtNd )
/*N*/               {
/*N*/                   const SwpHints* pHts = pTxtNd->GetpSwpHints();
/*N*/                   // setze die OultineNodes im neuen Nodes-Array
/*N*/                   if( bInsOutlineIdx && NO_NUMBERING !=
/*N*/                       pTxtNd->GetTxtColl()->GetOutlineLevel() )
/*?*/                       rNds.pOutlineNds->Insert( pTxtNd );
/*N*/
/*N*/                     // OD 21.01.2003 #106403# - invalidate numbering rule of
/*N*/                     // text node in the destination environment.
/*N*/                     pTxtNd->InvalidateNumRule();
/*N*/
/*N*/                   // Sonderbehandlung fuer die Felder!
/*N*/                   if( pHts && pHts->Count() )
/*N*/                   {
/*?*/                       const SwTxtAttr* pAttr;
/*?*/                       int bToUndo = &pDestDoc->GetNodes() != &rNds;
/*?*/                       for( USHORT i = pHts->Count(); i; )
/*?*/                       {
/*?*/                           USHORT nDelMsg = 0;
/*?*/                           switch( (pAttr = (*pHts)[ --i ])->Which() )
/*?*/                           {
/*?*/                           case RES_TXTATR_FIELD:
/*?*/                               {
/*?*/                                   SwTxtFld* pTxtFld = (SwTxtFld*)pAttr;
/*?*/                                   rNds.GetDoc()->InsDelFldInFldLst( !bToUndo,
/*?*/                                                               *pTxtFld );
/*?*/                                   const SwFieldType* pTyp = pTxtFld->GetFld().
/*?*/                                                           GetFld()->GetTyp();
/*?*/                                   if( RES_DDEFLD == pTyp->Which() )
/*?*/                                   {
/*?*/                                       if( bToUndo )
/*?*/                                           ((SwDDEFieldType*)pTyp)->DecRefCnt();
/*?*/                                       else
/*?*/                                           ((SwDDEFieldType*)pTyp)->IncRefCnt();
/*?*/                                   }
/*?*/                                   nDelMsg = RES_FIELD_DELETED;
/*?*/                               }
/*?*/                               break;
/*?*/                           case RES_TXTATR_FTN:
/*?*/                               nDelMsg = RES_FOOTNOTE_DELETED;
/*?*/                               break;
/*?*/
/*?*/                           case RES_TXTATR_TOXMARK:
/*?*/                               nDelMsg = RES_TOXMARK_DELETED;
/*?*/                               break;
/*?*/
/*?*/                           case RES_TXTATR_REFMARK:
/*?*/                               nDelMsg = RES_REFMARK_DELETED;
/*?*/                               break;
/*?*/                           }
/*?*/                           if( nDelMsg && bToUndo )
/*?*/                           {
/*?*/                               SwPtrMsgPoolItem aMsgHint( nDelMsg,
/*?*/                                                   (void*)&pAttr->GetAttr() );
/*?*/                               rNds.GetDoc()->GetUnoCallBack()->
/*?*/                                           Modify( &aMsgHint, &aMsgHint );
/*?*/                           }
/*?*/                       }
/*N*/                   }
/*N*/ //FEATURE::CONDCOLL
/*N*/                   if( RES_CONDTXTFMTCOLL == pTxtNd->GetTxtColl()->Which() )
/*N*/                       pTxtNd->ChkCondColl();
/*N*/ //FEATURE::CONDCOLL
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   // in unterschiedliche Docs gemoved ?
/*?*/                   // dann die Daten wieder persistent machen
/*?*/                   if( pCNd->IsNoTxtNode() && bRestPersData )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     ((SwNoTxtNode*)pCNd)->RestorePersistentData();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //JP 03.02.99: alle Felder als invalide erklaeren, aktu. erfolgt im
/*N*/   //              Idle-Handler des Docs
/*N*/   GetDoc()->SetFieldsDirty( TRUE );
/*N*/   if( rNds.GetDoc() != GetDoc() )
/*?*/       rNds.GetDoc()->SetFieldsDirty( TRUE );
/*N*/
/*N*/
/*N*/   if( bNewFrms )
/*N*/       bNewFrms = &GetDoc()->GetNodes() == (const SwNodes*)&rNds &&
/*N*/                   GetDoc()->GetRootFrm();
/*N*/   if( bNewFrms )
/*N*/   {
/*?*/       // Frames besorgen:
/*?*/       SwNodeIndex aIdx( *pPrevInsNd, 1 );
/*?*/       SwNodeIndex aFrmNdIdx( aIdx );
/*?*/       SwNode* pFrmNd = rNds.FindPrvNxtFrmNode( aFrmNdIdx,
/*?*/                                       rNds[ rInsPos.GetIndex() - 1 ] );
/*?*/
/*?*/       if( !pFrmNd && aFrmNdIdx > rNds.GetEndOfExtras().GetIndex() )
/*?*/       {
/*?*/           ASSERT( !this, "ob das so richtig ist ??" );
/*?*/           aFrmNdIdx = rNds.GetEndOfContent();
/*?*/           pFrmNd = rNds.GoPrevSection( &aFrmNdIdx, TRUE, FALSE );
/*?*/           if( pFrmNd && !((SwCntntNode*)pFrmNd)->GetDepends() )
/*?*/               pFrmNd = 0;
/*?*/
/*?*/ #ifndef PRODUCT
/*?*/           if( !pFrmNd )
/*?*/               ASSERT( !this, "ChgNode() - kein FrameNode gefunden" );
/*?*/ #endif
/*?*/       }
/*?*/       if( pFrmNd )
/*?*/           while( aIdx != rInsPos )
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
/*?*/           }
/*N*/   }
/*N*/ }


/***********************************************************************
|*
|*  SwNodes::Move
|*
|*  Beschreibung
|*  Move loescht die Node-Pointer ab und einschliesslich der Startposition
|*  bis zu und ausschliesslich der Endposition und fuegt sie an
|*  der vor der Zielposition ein.
|*  Wenn das Ziel vor dem ersten oder dem letzten zu bewegenden Element oder
|*  dazwischen liegt, geschieht nichts.
|*  Wenn der zu bewegende Bereich leer ist oder das Ende vor
|*  dem Anfang liegt, geschieht nichts.
|*
|*  Allg.: aRange beschreibt den Bereich  -exklusive- aEnd !!
|*              ( 1.Node: aStart, letzer Node: aEnd-1 !! )
|*
|*
|*
***********************************************************************/

/*N*/ BOOL SwNodes::_MoveNodes( const SwNodeRange& aRange, SwNodes & rNodes,
/*N*/                   const SwNodeIndex& aIndex, BOOL bNewFrms )
/*N*/ {
/*N*/   SwNode * pAktNode;
/*N*/   if( aIndex == 0 ||
/*N*/       ( (pAktNode = &aIndex.GetNode())->GetStartNode() &&
/*N*/         !pAktNode->StartOfSectionIndex() ))
/*?*/       return FALSE;
/*N*/
/*N*/   SwNodeRange aRg( aRange );
/*N*/
/*N*/   // "einfache" StartNodes oder EndNodes ueberspringen
/*N*/   while( ND_STARTNODE == (pAktNode = &aRg.aStart.GetNode())->GetNodeType()
/*N*/           || ( pAktNode->IsEndNode() &&
/*N*/               !pAktNode->pStartOfSection->IsSectionNode() ) )
/*?*/       aRg.aStart++;
/*N*/   aRg.aStart--;
/*N*/
/*N*/   // falls aEnd-1 auf keinem ContentNode steht, dann suche den vorherigen
/*N*/   aRg.aEnd--;
/*N*/   while( (( pAktNode = &aRg.aEnd.GetNode())->GetStartNode() &&
/*N*/           !pAktNode->IsSectionNode() ) ||
/*N*/           ( pAktNode->IsEndNode() &&
/*N*/           ND_STARTNODE == pAktNode->pStartOfSection->GetNodeType()) )
/*?*/       aRg.aEnd--;
/*N*/
/*N*/
/*N*/   // wird im selben Array's verschoben, dann ueberpruefe die Einfuegepos.
/*N*/   if( aRg.aStart >= aRg.aEnd )
/*?*/       return FALSE;
/*N*/
/*N*/   if( this == &rNodes )
/*N*/   {
/*?*/       if( ( aIndex.GetIndex()-1 >= aRg.aStart.GetIndex() &&
/*?*/             aIndex.GetIndex()-1 < aRg.aEnd.GetIndex()) ||
/*?*/           ( aIndex.GetIndex()-1 == aRg.aEnd.GetIndex() ) )
/*?*/           return FALSE;
/*N*/   }
/*N*/
/*N*/   USHORT nLevel = 0;                  // Level-Counter
/*N*/   ULONG nInsPos = 0;                  // Cnt fuer das TmpArray
/*N*/
/*N*/   // das Array bildet einen Stack, es werden alle StartOfSelction's gesichert
/*N*/   SwSttNdPtrs aSttNdStack( 1, 5 );
/*N*/
/*N*/   // setze den Start-Index
/*N*/   SwNodeIndex  aIdx( aIndex );
/*
    --- JP 17.11.94: sollte ueberholt sein, wird im ChgNode schon erledigt!
    BOOL bCorrNum = pSect && pSect->aStart.GetIndex() == aIdx.GetIndex();
*/
/*N*/
/*N*/   SwStartNode* pStartNode = aIdx.GetNode().pStartOfSection;
/*N*/   aSttNdStack.C40_INSERT( SwStartNode, pStartNode, 0 );
/*N*/ //    aSttNdStack.Insert( rNodes[ aIdx ]->pStartOfSection, 0 );
/*N*/   SwNodeRange aOrigInsPos( aIdx, -1, aIdx );      // Originale Insert Pos
/*N*/
/*N*/   //JP 16.01.98: SectionNodes: DelFrms/MakeFrms beim obersten SectionNode!
/*N*/   USHORT nSectNdCnt = 0;
/*N*/   BOOL bSaveNewFrms = bNewFrms;
/*N*/
/*N*/   // bis alles verschoben ist
/*N*/   while( aRg.aStart < aRg.aEnd )
/*N*/       switch( (pAktNode = &aRg.aEnd.GetNode())->GetNodeType() )
/*N*/       {
/*N*/       case ND_ENDNODE:
/*N*/           {
/*N*/               if( nInsPos )       // verschieb schon mal alle bis hier her
/*N*/               {
/*?*/                   // loeschen und kopieren. ACHTUNG: die Indizies ab
/*?*/                   // "aRg.aEnd+1" werden mit verschoben !!
/*?*/                   SwNodeIndex aSwIndex( aRg.aEnd, 1 );
/*?*/                   ChgNode( aSwIndex, nInsPos, aIdx, bNewFrms );
/*?*/                   aIdx -= nInsPos;
/*?*/                   nInsPos = 0;
/*N*/               }
/*N*/
/*N*/               SwStartNode* pSttNd = pAktNode->pStartOfSection;
/*N*/               if( pSttNd->IsTableNode() )
/*N*/               {
/*?*/                   SwTableNode* pTblNd = (SwTableNode*)pSttNd;
/*?*/
/*?*/                   // dann bewege die gesamte Tabelle/den Bereich !!
/*?*/                   nInsPos = (aRg.aEnd.GetIndex() -
/*?*/                                   pSttNd->GetIndex() )+1;
/*?*/                   aRg.aEnd -= nInsPos;
/*?*/
/*?*/                   //JP 12.03.99: 63293 - Nodes vom RedlineBereich NIE aufnehmen
/*?*/                   ULONG nNd = aIdx.GetIndex();
/*?*/                   BOOL bInsOutlineIdx = !( rNodes.GetEndOfRedlines().
/*?*/                           FindStartNode()->GetIndex() < nNd &&
/*?*/                           nNd < rNodes.GetEndOfRedlines().GetIndex() );
/*?*/
/*?*/                   if( bNewFrms )
/*?*/                       // loesche erstmal die Frames
/*?*/                       pTblNd->DelFrms();
/*?*/                   if( &rNodes == this )   // in sich selbst moven ??
/*?*/                   {
/*?*/                       // dann bewege alle Start/End/ContentNodes. Loesche
/*?*/                       // bei den ContentNodes auch die Frames !!
/*?*/                       pTblNd->pStartOfSection = aIdx.GetNode().pStartOfSection;
/*?*/                       for( ULONG n = 0; n < nInsPos; ++n )
/*?*/                       {
/*?*/                           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwNodeIndex aMvIdx( aRg.aEnd, 1 );
/*?*/                       }
/*?*/                   }
/*?*/                   else
/*?*/                   {
/*?*/                       // StartNode holen
/*?*/                       SwStartNode* pSttNode = aIdx.GetNode().GetStartNode();
/*?*/                       if( !pSttNode )
/*?*/                           pSttNode = aIdx.GetNode().pStartOfSection;
/*?*/
/*?*/                       // Hole alle Boxen mit Inhalt. Deren Indizies auf die
/*?*/                       // StartNodes muessen umgemeldet werden !!
/*?*/                       // (Array kopieren und alle gefunden wieder loeschen;
/*?*/                       //  erleichtert das suchen!!)
/*?*/                       SwNodeIndex aMvIdx( aRg.aEnd, 1 );
/*?*/                       for( ULONG n = 0; n < nInsPos; ++n )
/*?*/                       {
/*?*/                           SwNode* pNd = &aMvIdx.GetNode();
/*                          if( bNewFrms )
                            {
                                if( pNd->IsCntntNode() )
                                    ((SwCntntNode*)pNd)->DelFrms();
                                else if( pNd->IsSectionNode() )
                                    ((SwSectionNode*)pNd)->DelFrms();
                            }
*/
/*?*/                           BOOL bOutlNd = pNd->IsTxtNode() && NO_NUMBERING !=
/*?*/                               ((SwTxtNode*)pNd)->GetTxtColl()->GetOutlineLevel();
/*?*/                           // loesche die Gliederungs-Indizies aus
/*?*/                           // dem alten Nodes-Array
/*?*/                           if( bOutlNd )
/*?*/                               pOutlineNds->Remove( pNd );
/*?*/
/*?*/                           RemoveNode( aMvIdx.GetIndex(), 1, FALSE );
/*?*/                           pNd->pStartOfSection = pSttNode;
/*?*/                           rNodes.Insert( pNd, aIdx );
/*?*/
/*?*/                           // setze bei Start/EndNodes die richtigen Indizies
/*?*/                           if( bInsOutlineIdx && bOutlNd )
/*?*/                               // und setze sie im neuen Nodes-Array
/*?*/                               rNodes.pOutlineNds->Insert( pNd );
/*?*/                           else if( pNd->IsStartNode() )
/*?*/                               pSttNode = (SwStartNode*)pNd;
/*?*/                           else if( pNd->IsEndNode() )
/*?*/                           {
/*?*/                               pSttNode->pEndOfSection = (SwEndNode*)pNd;
/*?*/                               if( pSttNode->IsSectionNode() )
/*?*/                               {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     ((SwSectionNode*)pSttNode)->NodesArrChgd();
/*?*/                               pSttNode = pSttNode->pStartOfSection;
/*?*/                           }
/*?*/                       }
/*?*/
/*?*/                       if( pTblNd->GetTable().IsA( TYPE( SwDDETable ) ))
/*?*/                       {
/*?*/                           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwDDEFieldType* pTyp = ((SwDDETable&)pTblNd->
/*?*/                       }
/*?*/
/*?*/                       if( GetDoc()->GetUndoNds() == &rNodes )
/*?*/                       {
/*?*/                           SwFrmFmt* pTblFmt = pTblNd->GetTable().GetFrmFmt();
/*?*/                           SwPtrMsgPoolItem aMsgHint( RES_REMOVE_UNO_OBJECT,
/*?*/                                                       pTblFmt );
/*?*/                           pTblFmt->Modify( &aMsgHint, &aMsgHint );
/*?*/                       }
/*?*/                   }
/*?*/                   if( bNewFrms )
/*?*/                   {
/*?*/                       SwNodeIndex aTmp( aIdx );
/*?*/                       pTblNd->MakeFrms( &aTmp );
/*?*/                   }
/*?*/                   aIdx -= nInsPos;
/*?*/                   nInsPos = 0;
/*N*/               }
/*N*/               else if( pSttNd->GetIndex() < aRg.aStart.GetIndex() )
/*N*/               {
/*N*/                   // SectionNode: es wird nicht die gesamte Section
/*N*/                   //              verschoben, also bewege nur die
/*N*/                   //              ContentNodes
/*N*/                   // StartNode:   erzeuge an der Postion eine neue Section
/*N*/                   do {        // middle check loop
/*N*/                       if( !pSttNd->IsSectionNode() )
/*N*/                       {
/*?*/                           // Start und EndNode an der InsertPos erzeugen
/*?*/                           SwStartNode* pTmp = new SwStartNode( aIdx,
/*?*/                                                   ND_STARTNODE,
/*?*/ /*?? welcher NodeTyp ??*/
/*?*/                                                   SwNormalStartNode );
/*?*/
/*?*/                           nLevel++;           // den Index auf StartNode auf den Stack
/*?*/                           aSttNdStack.C40_INSERT( SwStartNode, pTmp, nLevel );
/*?*/
/*?*/                           // noch den EndNode erzeugen
/*?*/                           new SwEndNode( aIdx, *pTmp );
/*N*/                       }
/*N*/                       else if( (const SwNodes*)&rNodes ==
/*N*/                               GetDoc()->GetUndoNds() )
/*N*/                       {
/*N*/                           // im UndoNodes-Array spendieren wir einen
/*N*/                           // Platzhalter
/*N*/                           new SwNode( aIdx, ND_SECTIONDUMMY );
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*?*/                           // JP 18.5.2001: neue Section anlegen?? Bug 70454
/*?*/                           aRg.aEnd--;
/*?*/                           break;
/*N*/
/*N*/                       }
/*N*/
/*N*/                       aRg.aEnd--;
/*N*/                       aIdx--;
/*N*/                   } while( FALSE );
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   // Start und EndNode komplett verschieben
/*?*/ // s. u. SwIndex aOldStt( pSttNd->theIndex );
/*?*/ //JP 21.05.97: sollte der Start genau der Start des Bereiches sein, so muss
/*?*/ //                der Node auf jedenfall noch besucht werden!
/*?*/                   if( &aRg.aStart.GetNode() == pSttNd )
/*?*/                       --aRg.aStart;
/*?*/
/*?*/                   SwSectionNode* pSctNd = pSttNd->GetSectionNode();
/*?*/                   if( bNewFrms && pSctNd )
/*?*/                       pSctNd->DelFrms();
/*?*/
/*?*/                   RemoveNode( aRg.aEnd.GetIndex(), 1, FALSE ); // EndNode loeschen
/*?*/                   ULONG nSttPos = pSttNd->GetIndex();
/*?*/
/*?*/                   // dieser StartNode wird spaeter wieder entfernt!
/*?*/                   SwStartNode* pTmpSttNd = new SwStartNode( *this, nSttPos+1 );
/*?*/                   pTmpSttNd->pStartOfSection = pSttNd->pStartOfSection;
/*?*/
/*?*/                   RemoveNode( nSttPos, 1, FALSE ); // SttNode loeschen
/*?*/
/*?*/                   pSttNd->pStartOfSection = aIdx.GetNode().pStartOfSection;
/*?*/                   rNodes.Insert( pSttNd, aIdx  );
/*?*/                   rNodes.Insert( pAktNode, aIdx );
/*?*/                   aIdx--;
/*?*/                   pSttNd->pEndOfSection = (SwEndNode*)pAktNode;
/*?*/
/*?*/                   aRg.aEnd--;
/*?*/
/*?*/                   nLevel++;           // den Index auf StartNode auf den Stack
/*?*/                   aSttNdStack.C40_INSERT( SwStartNode, pSttNd, nLevel );
/*?*/
/*?*/                   // SectionNode muss noch ein paar Indizies ummelden
/*?*/                   if( pSctNd )
/*?*/                   {
/*?*/                       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pSctNd->NodesArrChgd();
/*?*/                   }
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/
/*N*/
/*N*/       case ND_SECTIONNODE:
/*?*/           if( !nLevel &&
/*?*/               ( (const SwNodes*)&rNodes == GetDoc()->GetUndoNds() ) )
/*?*/           {
/*?*/               // dann muss an der akt. InsPos ein SectionDummyNode
/*?*/               // eingefuegt werden
/*?*/               if( nInsPos )       // verschieb schon mal alle bis hier her
/*?*/               {
/*?*/                   // loeschen und kopieren. ACHTUNG: die Indizies ab
/*?*/                   // "aRg.aEnd+1" werden mit verschoben !!
/*?*/                   SwNodeIndex aSwIndex( aRg.aEnd, 1 );
/*?*/                   ChgNode( aSwIndex, nInsPos, aIdx, bNewFrms );
/*?*/                   aIdx -= nInsPos;
/*?*/                   nInsPos = 0;
/*?*/               }
/*?*/               new SwNode( aIdx, ND_SECTIONDUMMY );
/*?*/               aRg.aEnd--;
/*?*/               aIdx--;
/*?*/               break;
/*?*/           }
/*?*/           // kein break !!
/*?*/       case ND_TABLENODE:
/*?*/       case ND_STARTNODE:
/*?*/           {
/*?*/               // Bug #78589# - empty section -> nothing to do
/*?*/               //  and only if it's a top level section
/*?*/               if( !nInsPos && !nLevel )
/*?*/               {
/*?*/                   aRg.aEnd--;
/*?*/                   break;
/*?*/               }
/*?*/
/*?*/               if( !nLevel )       // es wird eine Stufe runter gestuft
/*?*/               {
/*?*/                   // erzeuge die Runterstufung
/*?*/                   SwNodeIndex aTmpSIdx( aOrigInsPos.aStart, 1 );
/*?*/                   SwStartNode* pTmpStt = new SwStartNode( aTmpSIdx,
/*?*/                               ND_STARTNODE,
/*?*/                               ((SwStartNode*)pAktNode)->GetStartNodeType() );
/*?*/
/*?*/                   aTmpSIdx--;
/*?*/
/*?*/                   SwNodeIndex aTmpEIdx( aOrigInsPos.aEnd );
/*?*/                   new SwEndNode( aTmpEIdx, *pTmpStt );
/*?*/                   aTmpEIdx--;
/*?*/                   aTmpSIdx++;
/*?*/
/*?*/                   // setze die StartOfSection richtig
/*?*/                   aRg.aEnd++;
/*?*/                   {
/*?*/                       SwNodeIndex aCntIdx( aRg.aEnd );
/*?*/                       for( register ULONG n = 0; n < nInsPos; n++, aCntIdx++)
/*?*/                           aCntIdx.GetNode().pStartOfSection = pTmpStt;
/*?*/                   }
/*?*/
/*?*/                   // Setze auch bei allen runtergestuften den richtigen StartNode
/*?*/                   while( aTmpSIdx < aTmpEIdx )
/*?*/                       if( 0 != (( pAktNode = &aTmpEIdx.GetNode())->GetEndNode()) )
/*?*/                           aTmpEIdx = pAktNode->StartOfSectionIndex();
/*?*/                       else
/*?*/                       {
/*?*/                           pAktNode->pStartOfSection = pTmpStt;
/*?*/                           aTmpEIdx--;
/*?*/                       }
/*?*/
/*?*/                   aIdx--;                 // hinter den eingefuegten StartNode
/*?*/                   aRg.aEnd--;             // vor den StartNode
/*?*/                   // kopiere jetzt das Array. ACHTUNG: die Indizies ab
/*?*/                   // "aRg.aEnd+1" werden mit verschoben !!
/*?*/                   SwNodeIndex aSwIndex( aRg.aEnd, 1 );
/*?*/                   ChgNode( aSwIndex, nInsPos, aIdx, bNewFrms );
/*?*/                   aIdx -= nInsPos+1;
/*?*/                   nInsPos = 0;
/*?*/               }
/*?*/               else                // es wurden alle Nodes innerhalb eines
/*?*/               {                   // Start- und End-Nodes verschoben
/*?*/                   ASSERT( pAktNode == aSttNdStack[nLevel] ||
/*?*/                           ( pAktNode->IsStartNode() &&
/*?*/                               aSttNdStack[nLevel]->IsSectionNode()),
/*?*/                            "falscher StartNode" );
/*?*/
/*?*/                   SwNodeIndex aSwIndex( aRg.aEnd, 1 );
/*?*/                   ChgNode( aSwIndex, nInsPos, aIdx, bNewFrms );
/*?*/                   aIdx -= nInsPos+1;      // vor den eingefuegten StartNode
/*?*/                   nInsPos = 0;
/*?*/
/*?*/                   // loesche nur noch den Pointer aus dem Nodes-Array.
/*?*/ //                    RemoveNode( aRg.aEnd.GetIndex(), 1, FALSE );
/*?*/                   RemoveNode( aRg.aEnd.GetIndex(), 1, TRUE );
/*?*/                   aRg.aEnd--;
/*?*/
/*?*/                   SwSectionNode* pSectNd = aSttNdStack[ nLevel ]->GetSectionNode();
/*?*/                   if( pSectNd && !--nSectNdCnt )
/*?*/                   {
/*?*/                       SwNodeIndex aTmp( *pSectNd );
/*?*/                       pSectNd->MakeFrms( &aTmp );
/*?*/                       bNewFrms = bSaveNewFrms;
/*?*/                   }
/*?*/                   aSttNdStack.Remove( nLevel );   // vom Stack loeschen
/*?*/                   nLevel--;
/*?*/               }
/*?*/
/*?*/               // loesche alle entstehenden leeren Start-/End-Node-Paare
/*?*/               SwNode* pTmpNode = (*this)[ aRg.aEnd.GetIndex()+1 ]->GetEndNode();
/*?*/               if( pTmpNode && ND_STARTNODE == (pAktNode = &aRg.aEnd.GetNode())
/*?*/                   ->GetNodeType() && pAktNode->StartOfSectionIndex() &&
/*?*/                   pTmpNode->FindStartNode() == pAktNode )
/*?*/               {
/*?*/                   DelNodes( aRg.aEnd, 2 );
/*?*/                   aRg.aEnd--;
/*?*/               }
/*?*/ //                aRg.aEnd--;
/*?*/           }
/*?*/           break;
/*N*/
/*N*/       case ND_TEXTNODE:
/*N*/       case ND_GRFNODE:
/*N*/       case ND_OLENODE:
/*N*/           {
/*N*/               if( bNewFrms && pAktNode->GetCntntNode() )
/*N*/                   ((SwCntntNode*)pAktNode)->DelFrms();
/*N*/
/*N*/               pAktNode->pStartOfSection = aSttNdStack[ nLevel ];
/*N*/               nInsPos++;
/*N*/               aRg.aEnd--;
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case ND_SECTIONDUMMY:
/*?*/           if( (const SwNodes*)this == GetDoc()->GetUndoNds() )
/*?*/           {
/*?*/               if( &rNodes == this )       // innerhalb vom UndoNodesArray
/*?*/               {
/*?*/                   // mit verschieben
/*?*/                   pAktNode->pStartOfSection = aSttNdStack[ nLevel ];
/*?*/                   nInsPos++;
/*?*/               }
/*?*/               else    // in ein "normales" Nodes-Array verschieben
/*?*/               {
/*?*/                   // dann muss an der akt. InsPos auch ein SectionNode
/*?*/                   // (Start/Ende) stehen; dann diesen ueberspringen.
/*?*/                   // Andernfalls nicht weiter beachten.
/*?*/                   if( nInsPos )       // verschieb schon mal alle bis hier her
/*?*/                   {
/*?*/                       // loeschen und kopieren. ACHTUNG: die Indizies ab
/*?*/                       // "aRg.aEnd+1" werden mit verschoben !!
/*?*/                       SwNodeIndex aSwIndex( aRg.aEnd, 1 );
/*?*/                       ChgNode( aSwIndex, nInsPos, aIdx, bNewFrms );
/*?*/                       aIdx -= nInsPos;
/*?*/                       nInsPos = 0;
/*?*/                   }
/*?*/                   SwNode* pTmpNd = &aIdx.GetNode();
/*?*/                   if( pTmpNd->IsSectionNode() ||
/*?*/                       pTmpNd->FindStartNode()->IsSectionNode() )
/*?*/                       aIdx--; // ueberspringen
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/               ASSERT( FALSE, "wie kommt diser Node ins Nodes-Array??" );
/*?*/           aRg.aEnd--;
/*?*/           break;
/*?*/
/*?*/       default:
/*?*/           ASSERT( FALSE, "was ist das fuer ein Node??" );
/*?*/           break;
/*N*/       }
/*N*/
/*N*/   if( nInsPos )                           // kopiere den Rest
/*N*/   {
/*N*/       // der Rest muesste so stimmen
/*N*/       SwNodeIndex aSwIndex( aRg.aEnd, 1 );
/*N*/       ChgNode( aSwIndex, nInsPos, aIdx, bNewFrms );
/*N*/   }
/*N*/   aRg.aEnd++;                     // wieder exklusive Ende
/*N*/
/*N*/   // loesche alle leeren Start-/End-Node-Paare
/*N*/   if( ( pAktNode = &aRg.aStart.GetNode())->GetStartNode() &&
/*N*/       pAktNode->StartOfSectionIndex() &&
/*N*/       aRg.aEnd.GetNode().GetEndNode() )
/*?*/           DelNodes( aRg.aStart, 2 );
/*N*/
/*N*/   // rufe jetzt noch das Update fuer die Gliederung/Nummerierung auf
/*N*/   aOrigInsPos.aStart++;
/*N*/   // im gleichen Nodes-Array verschoben ??,
/*N*/   // dann von oben nach unten das Update aufrufen !!
/*N*/   if( this == &rNodes &&
/*N*/       aRg.aEnd.GetIndex() >= aOrigInsPos.aStart.GetIndex() )
/*N*/   {
/*?*/       UpdtOutlineIdx( aOrigInsPos.aStart.GetNode() );
/*?*/       UpdtOutlineIdx( aRg.aEnd.GetNode() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       UpdtOutlineIdx( aRg.aEnd.GetNode() );
/*N*/       rNodes.UpdtOutlineIdx( aOrigInsPos.aStart.GetNode() );
/*N*/   }
/*N*/
/*N*/ #ifdef JP_DEBUG
/*N*/   {
/*N*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 /*?*/ extern Writer* GetDebugWriter(const String&);
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   return TRUE;
/*N*/ }


/*******************************************************************
|*
|*  SwNodes::SectionDown
|*
|*  Beschreibung
|*    SectionDown() legt ein Paar von Start- und EndSection-Node
|*    (andere Nodes koennen dazwischen liegen) an.
|*
|*    Zustand des SRange beim Verlassen der Funktion: nStart ist der
|*    Index des ersten Node hinter dem Start Section Node, nEnd ist
|*    der Index des End Section Nodes. Beispiel: Wird Insert Section
|*    mehrmals hintereinander aufgerufen, so werden mehrere
|*    unmittelbar geschachtelte Sections (keine Content Nodes
|*    zwischen Start- bzw. End Nodes) angelegt.
|*
|*  Allg.: aRange beschreibt den Bereich  -exklusive- aEnd !!
|*              ( 1.Node: aStart, letzer Node: aEnd-1 !! )
|*
|*  Parameter
|*      SwRange &rRange
|*          IO:
|*          IN
|*          rRange.aStart: Einfuegeposition des StartNodes
|*          rRange.aEnd: Einfuegeposition des EndNodes
|*          OUT
|*          rRange.aStart: steht hinter dem eingefuegten Startnode
|*          rRange.aEnd: steht auf dem eingefuegen Endnode
|*
|*  Ausnahmen
|*   1. SRange-Anfang und SRange-Ende muessen auf dem gleichen Level sein
|*   2. duerfen nicht auf dem obersten Level sein
|*      Ist dies nicht der Fall, wird die
|*      Funktion durch Aufruf von ERR_RAISE verlassen.
|*
|*  Debug-Funktionen
|*      die Debugging Tools geben rRange beim Eintritt und beim
|*      Verlassen der Funktion aus
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/
/*N*/ void SwNodes::SectionDown(SwNodeRange *pRange, SwStartNodeType eSttNdTyp )
/*N*/ {
/*N*/   if( pRange->aStart >= pRange->aEnd ||
/*N*/       pRange->aEnd >= Count() ||
/*N*/       !CheckNodesRange( pRange->aStart, pRange->aEnd ))
/*?*/       return;
/*N*/
/*N*/   // Ist der Anfang vom Bereich vor oder auf einem EndNode, so loesche
/*N*/   // diesen, denn sonst wuerden leere S/E-Nodes oder E/S-Nodes enstehen.
/*N*/   // Bei anderen Nodes wird eine neuer StartNode eingefuegt
/*N*/   SwNode * pAktNode = &pRange->aStart.GetNode();
/*N*/   SwNodeIndex aTmpIdx( *pAktNode->StartOfSectionNode() );
/*N*/
/*N*/   if( pAktNode->GetEndNode() )
/*?*/       DelNodes( pRange->aStart, 1 );      // verhinder leere Section
/*N*/   else
/*N*/   {
/*N*/       // fuege einen neuen StartNode ein
/*N*/       SwNode* pSttNd = new SwStartNode( pRange->aStart, ND_STARTNODE, eSttNdTyp );
/*N*/       pRange->aStart = *pSttNd;
/*N*/       aTmpIdx = pRange->aStart;
/*N*/   }
/*N*/
/*N*/   // Ist das Ende vom Bereich vor oder auf einem StartNode, so loesche
/*N*/   // diesen, denn sonst wuerden leere S/E-Nodes oder E/S-Nodes enstehen
/*N*/   // Bei anderen Nodes wird eine neuer EndNode eingefuegt
/*N*/   pRange->aEnd--;
/*N*/   if( pRange->aEnd.GetNode().GetStartNode() )
/*?*/       DelNodes( pRange->aEnd, 1 );
/*N*/   else
/*N*/   {
/*N*/       pRange->aEnd++;
/*N*/       // fuege einen neuen EndNode ein
/*N*/       new SwEndNode( pRange->aEnd, *pRange->aStart.GetNode().GetStartNode() );
/*N*/   }
/*N*/   pRange->aEnd--;
/*N*/
/*N*/   SectionUpDown( aTmpIdx, pRange->aEnd );
/*N*/ }

/*******************************************************************
|*
|*  SwNodes::SectionUp
|*
|*  Beschreibung
|*      Der von rRange umspannte Bereich wird auf die naechst hoehere
|*      Ebene gehoben. Das geschieht dadurch, dass bei
|*      rRange.aStart ein Endnode und bei rRange.aEnd ein
|*      Startnode eingefuegt wird. Die Indices fuer den Bereich
|*      innerhalb von rRange werden geupdated.
|*
|*  Allg.: aRange beschreibt den Bereich  -exklusive- aEnd !!
|*              ( 1.Node: aStart, letzer Node: aEnd-1 !! )
|*
|*  Parameter
|*      SwRange &rRange
|*          IO:
|*          IN
|*          rRange.aStart: Anfang des hoeher zubewegenden Bereiches
|*          rRange.aEnd:   der 1.Node hinter dem Bereich
|*          OUT
|*          rRange.aStart:  an der ersten Position innerhalb des
|*                          hochbewegten Bereiches
|*          rRange.aEnd:    an der letzten Position innerhalb des
|*                          hochbewegten Bereiches
|*
|*  Debug-Funktionen
|*      die Debugging Tools geben rRange beim Eintritt und beim
|*      Verlassen der Funktion aus
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/


/*************************************************************************
|*
|*  SwNodes::SectionUpDown()
|*
|*  Beschreibung
|*      Methode setzt die Indizies die bei SectionUp oder SectionDwon
|*      veraendert wurden wieder richtig, sodass die Ebenen wieder
|*      Konsistent sind.
|*
|*    Parameter
|*                      SwIndex & aStart        StartNode !!!
|*                      SwIndex & aEnd          EndPunkt
|*
|*    Ersterstellung    JP 23.04.91
|*    Letzte Aenderung  JP 23.04.91
|*
*************************************************************************/
/*N*/ void SwNodes::SectionUpDown( const SwNodeIndex & aStart, const SwNodeIndex & aEnd )
/*N*/ {
/*N*/   SwNode * pAktNode;
/*N*/   SwNodeIndex aTmpIdx( aStart, +1 );
/*N*/   // das Array bildet einen Stack, es werden alle StartOfSelction's gesichert
/*N*/   SwSttNdPtrs aSttNdStack( 1, 5 );
/*N*/   SwStartNode* pTmp = aStart.GetNode().GetStartNode();
/*N*/   aSttNdStack.C40_INSERT( SwStartNode, pTmp, 0 );
/*N*/
/*N*/   // durchlaufe bis der erste zu aendernde Start-Node gefunden wurde
/*N*/   // ( Es wird vom eingefuegten EndNode bis nach vorne die Indexe gesetzt )
/*N*/   for( ;; aTmpIdx++ )
/*N*/   {
/*N*/       pAktNode = &aTmpIdx.GetNode();
/*N*/       pAktNode->pStartOfSection = aSttNdStack[ aSttNdStack.Count()-1 ];
/*N*/
/*N*/       if( pAktNode->GetStartNode() )
/*N*/       {
/*?*/           pTmp = (SwStartNode*)pAktNode;
/*?*/           aSttNdStack.C40_INSERT( SwStartNode, pTmp, aSttNdStack.Count() );
/*N*/       }
/*N*/       else if( pAktNode->GetEndNode() )
/*N*/       {
/*N*/           SwStartNode* pSttNd = aSttNdStack[ aSttNdStack.Count() - 1 ];
/*N*/           pSttNd->pEndOfSection = (SwEndNode*)pAktNode;
/*N*/           aSttNdStack.Remove( aSttNdStack.Count() - 1 );
/*N*/           if( aSttNdStack.Count() )
/*?*/               continue;       // noch genuegend EndNodes auf dem Stack
/*N*/
/*N*/           else if( aTmpIdx < aEnd )   // Uebergewicht an StartNodes
/*N*/               // ist das Ende noch nicht erreicht, so hole den Start von
/*N*/               // der uebergeordneten Section
/*N*/           {
/*?*/               aSttNdStack.C40_INSERT( SwStartNode, pSttNd->pStartOfSection, 0 );
/*N*/           }
/*N*/           else    // wenn ueber den Bereich hinaus, dann Ende
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/ }




/*******************************************************************
|*
|*  SwNodes::Delete
|*
|*  Beschreibung
|*      Spezielle Implementierung der Delete-Funktion des
|*      variablen Array. Diese spezielle Implementierung ist
|*      notwendig, da durch das Loeschen von Start- bzw.
|*      Endnodes Inkonsistenzen entstehen koennen. Diese werden
|*      durch diese Funktion beseitigt.
|*
|*  Parameter
|*      IN
|*      SwIndex &rIndex bezeichnet die Position, an der
|*      geloescht wird
|*      rIndex ist nach Aufruf der Funktion unveraendert (Kopie?!)
|*      USHORT nNodes bezeichnet die Anzahl der zu loeschenden
|*      Nodes; ist auf 1 defaulted
|*
|*  Debug-Funktionen
|*      geben beim Eintritt in die Funktion Position und Anzahl
|*      der zu loeschenden Nodes aus.
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/
/*N*/ void SwNodes::Delete(const SwNodeIndex &rIndex, ULONG nNodes)
/*N*/ {
/*N*/   USHORT nLevel = 0;                      // Level-Counter
/*N*/   SwNode * pAktNode;
/*N*/
/*N*/   ULONG nCnt = Count() - rIndex.GetIndex() - 1;
/*N*/   if( nCnt > nNodes ) nCnt = nNodes;
/*N*/
/*N*/   if( nCnt == 0 )         // keine Anzahl -> return
/*?*/       return;
/*N*/
/*N*/   SwNodeRange aRg( rIndex, 0, rIndex, nCnt-1 );
/*N*/   // ueberprufe ob rIndex..rIndex + nCnt ueber einen Bereich hinausragt !!
/*N*/   if( ( !aRg.aStart.GetNode().StartOfSectionIndex() &&
/*N*/           !aRg.aStart.GetIndex() ) ||
/*N*/           ! CheckNodesRange( aRg.aStart, aRg.aEnd ) )
/*?*/       return;
/*N*/
/*N*/
/*N*/   // falls aEnd auf keinem ContentNode steht, dann suche den vorherigen
/*N*/   while( ( pAktNode = &aRg.aEnd.GetNode())->GetStartNode() ||
/*N*/            ( pAktNode->GetEndNode() &&
/*N*/               !pAktNode->pStartOfSection->IsTableNode() ))
/*?*/       aRg.aEnd--;
/*N*/
/*N*/   nCnt = 0;
/*N*/   // Start erhoehen, damit auf < abgefragt wird. ( bei <= kann es zu
/*N*/   // Problemen fuehren; ist aEnd == aStart und wird aEnd geloscht,
/*N*/   // so ist aEnd <= aStart
/*N*/   aRg.aStart--;
/*N*/
/*N*/   BOOL bSaveInNodesDel = bInNodesDel;
/*N*/   bInNodesDel = TRUE;
/*N*/   BOOL bUpdateOutline = FALSE;
/*N*/
/*N*/   // bis alles geloescht ist
/*N*/   while( aRg.aStart < aRg.aEnd )
/*N*/   {
/*N*/       pAktNode = &aRg.aEnd.GetNode();
/*N*/
/*N*/       if( pAktNode->GetEndNode() )
/*N*/       {
/*N*/           // die gesamte Section loeschen ?
/*N*/           if( pAktNode->StartOfSectionIndex() > aRg.aStart.GetIndex() )
/*N*/           {
/*N*/               SwTableNode* pTblNd = pAktNode->pStartOfSection->GetTableNode();
/*N*/               if( pTblNd )
/*N*/                   pTblNd->DelFrms();
/*N*/
/*N*/               SwNode *pNd, *pChkNd = pAktNode->pStartOfSection;
/*N*/               USHORT nIdxPos;
/*N*/               do {
/*N*/                   pNd = &aRg.aEnd.GetNode();
/*N*/
/*N*/                   if( pNd->IsTxtNode() )
/*N*/                   {
/*N*/                       if( NO_NUMBERING !=
/*N*/                       ((SwTxtNode*)pNd)->GetTxtColl()->GetOutlineLevel() &&
/*N*/                       pOutlineNds->Seek_Entry( pNd, &nIdxPos ))
/*N*/                       {
/*?*/                           // loesche die Gliederungs-Indizies.
/*?*/                           pOutlineNds->Remove( nIdxPos );
/*?*/                           bUpdateOutline = TRUE;
/*N*/                       }
/*N*/                   }
/*N*/                   else if( pNd->IsEndNode() &&
/*N*/                           pNd->pStartOfSection->IsTableNode() )
/*N*/                       ((SwTableNode*)pNd->pStartOfSection)->DelFrms();
/*N*/
/*N*/                   aRg.aEnd--;
/*N*/                   nCnt++;
/*N*/
/*N*/               } while( pNd != pChkNd );
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               RemoveNode( aRg.aEnd.GetIndex()+1, nCnt, TRUE );    // loesche
/*?*/               nCnt = 0;
/*?*/               aRg.aEnd--;             // vor den EndNode
/*?*/               nLevel++;
/*N*/           }
/*N*/       }
/*N*/       else if( pAktNode->GetStartNode() )   // StartNode gefunden
/*N*/       {
/*?*/           if( nLevel == 0 )       // es wird eine Stufe runter gestuft
/*?*/           {
/*?*/               if( nCnt )
/*?*/               {
/*?*/                   // loesche jetzt das Array
/*?*/                   aRg.aEnd++;
/*?*/                   RemoveNode( aRg.aEnd.GetIndex(), nCnt, TRUE );
/*?*/                   nCnt = 0;
/*?*/               }
/*?*/           }
/*?*/           else    // es werden alle Nodes Innerhalb eines Start- und
/*?*/           {       // End-Nodes geloescht, loesche mit Start/EndNode
/*?*/               RemoveNode( aRg.aEnd.GetIndex(), nCnt + 2, TRUE );          // loesche Array
/*?*/               nCnt = 0;
/*?*/               nLevel--;
/*?*/           }
/*?*/
/*?*/           // nach dem loeschen kann aEnd auf einem EndNode stehen
/*?*/           // loesche alle leeren Start-/End-Node-Paare
/*?*/           SwNode* pTmpNode = aRg.aEnd.GetNode().GetEndNode();
/*?*/           aRg.aEnd--;
/*?*/           while(  pTmpNode &&
/*?*/                   ( pAktNode = &aRg.aEnd.GetNode())->GetStartNode() &&
/*?*/                   pAktNode->StartOfSectionIndex() )
/*?*/           {
/*?*/               // loesche den EndNode und StartNode
/*?*/               DelNodes( aRg.aEnd, 2 );
/*?*/               pTmpNode = aRg.aEnd.GetNode().GetEndNode();
/*?*/               aRg.aEnd--;
/*?*/           }
/*N*/       }
/*N*/       else        // normaler Node, also ins TmpArray einfuegen
/*N*/       {
/*N*/           SwTxtNode* pTxtNd = pAktNode->GetTxtNode();
/*N*/           if( pTxtNd )
/*N*/           {
/*N*/               if( NO_NUMBERING != pTxtNd->GetTxtColl()->GetOutlineLevel() )
/*N*/               {                   // loesche die Gliederungs-Indizies.
/*N*/                   pOutlineNds->Remove( pTxtNd );
/*N*/                   bUpdateOutline = TRUE;
/*N*/               }
/*N*/               pTxtNd->InvalidateNumRule();
/*N*/           }
/*N*/           else if( pAktNode->IsCntntNode() )
/*?*/               ((SwCntntNode*)pAktNode)->InvalidateNumRule();
/*N*/
/*N*/           aRg.aEnd--;
/*N*/           nCnt++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aRg.aEnd++;
/*N*/   if( nCnt != 0 )
/*N*/       RemoveNode( aRg.aEnd.GetIndex(), nCnt, TRUE );              // loesche den Rest
/*N*/
/*N*/   // loesche alle leeren Start-/End-Node-Paare
/*N*/   while( aRg.aEnd.GetNode().GetEndNode() &&
/*N*/           ( pAktNode = &aRg.aStart.GetNode())->GetStartNode() &&
/*N*/           pAktNode->StartOfSectionIndex() )
/*N*/   // aber ja keinen der heiligen 5.
/*N*/   {
/*?*/       DelNodes( aRg.aStart, 2 );  // loesche den Start- und EndNode
/*?*/       aRg.aStart--;
/*N*/   }
/*N*/
/*N*/   bInNodesDel = bSaveInNodesDel;
/*N*/
/*N*/   if( !bInNodesDel )
/*N*/   {
/*N*/       // rufe jetzt noch das Update fuer die Gliederung/Nummerierung auf
/*N*/       if( bUpdateOutline || bInDelUpdOutl )
/*N*/       {
/*N*/           UpdtOutlineIdx( aRg.aEnd.GetNode() );
/*N*/           bInDelUpdOutl = FALSE;
/*N*/       }
/*N*/
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       if( bUpdateOutline )
/*?*/           bInDelUpdOutl = TRUE;
/*N*/   }
/*N*/ }

/*******************************************************************
|*
|*  SwNodes::GetSectionLevel
|*
|*  Beschreibung
|*      Die Funktion liefert den Sectionlevel an der durch
|*      aIndex bezeichneten Position. Die Funktion ruft die
|*      GetSectionlevel-Funktion des durch aIndex bezeichneten
|*      Nodes. Diese ist eine virtuelle Funktion, die fuer
|*      Endnodes speziell implementiert werden musste.
|*      Die Sectionlevels werden ermittelt, indem rekursiv durch
|*      die Nodesstruktur (jeweils zum naechsten theEndOfSection)
|*      gegangen wird, bis die oberste Ebene erreicht ist
|*      (theEndOfSection == 0)
|*
|*  Parameter
|*      aIndex bezeichnet die Position des Nodes, dessen
|*      Sectionlevel ermittelt werden soll. Hier wird eine Kopie
|*      uebergeben, da eine Veraenderung der Variablen in der
|*      rufenden Funktion nicht wuenschenswert ist.
|*
|*  Ausnahmen
|*      Der erste Node im Array  sollte immer ein Startnode sein.
|*      Dieser erfaehrt in der Funktion SwNodes::GetSectionLevel()
|*      eine Sonderbehandlung; es wird davon ausgegangen, dass der
|*      erste Node auch ein Startnode ist.
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/

/*N*/ void SwNodes::GoStartOfSection(SwNodeIndex *pIdx) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void SwNodes::GoEndOfSection(SwNodeIndex *pIdx) const
/*N*/ {
/*N*/   // falls er vor einem Endnode steht --> nichts tun
/*N*/   if( !pIdx->GetNode().IsEndNode() )
/*N*/       (*pIdx) = *pIdx->GetNode().EndOfSectionNode();
/*N*/ }

/*N*/ SwCntntNode* SwNodes::GoNext(SwNodeIndex *pIdx) const
/*N*/ {
/*N*/   if( pIdx->GetIndex() >= Count() - 1 )
/*?*/       return 0;
/*N*/
/*N*/   SwNodeIndex aTmp(*pIdx, +1);
/*N*/   SwNode* pNd;
/*N*/   while( aTmp < Count()-1 && 0 == ( pNd = &aTmp.GetNode())->IsCntntNode() )
/*N*/       aTmp++;
/*N*/
/*N*/   if( aTmp == Count()-1 )
/*N*/       pNd = 0;
/*N*/   else
/*N*/       (*pIdx) = aTmp;
/*N*/   return (SwCntntNode*)pNd;
/*N*/ }

/*N*/ SwCntntNode* SwNodes::GoPrevious(SwNodeIndex *pIdx) const
/*N*/ {
/*N*/   if( !pIdx->GetIndex() )
/*?*/       return 0;
/*N*/
/*N*/   SwNodeIndex aTmp( *pIdx, -1 );
/*N*/   SwNode* pNd;
/*N*/   while( aTmp.GetIndex() && 0 == ( pNd = &aTmp.GetNode())->IsCntntNode() )
/*N*/       aTmp--;
/*N*/
/*N*/   if( !aTmp.GetIndex() )
/*?*/       pNd = 0;
/*N*/   else
/*N*/       (*pIdx) = aTmp;
/*N*/   return (SwCntntNode*)pNd;
/*N*/ }

/*N*/ SwNode* SwNodes::GoNextWithFrm(SwNodeIndex *pIdx) const
/*N*/ {
/*N*/   if( pIdx->GetIndex() >= Count() - 1 )
/*?*/       return 0;
/*N*/
/*N*/   SwNodeIndex aTmp(*pIdx, +1);
/*N*/   SwNode* pNd;
/*N*/   while( aTmp < Count()-1 )
/*N*/   {
/*N*/       pNd = &aTmp.GetNode();
/*N*/       SwModify *pMod = 0;
/*N*/       if ( pNd->IsCntntNode() )
/*N*/           pMod = (SwCntntNode*)pNd;
/*N*/       else if ( pNd->IsTableNode() )
/*N*/           pMod = ((SwTableNode*)pNd)->GetTable().GetFrmFmt();
/*N*/       else if( pNd->IsEndNode() && !pNd->FindStartNode()->IsSectionNode() )
/*N*/       {
/*N*/           pNd = 0;
/*N*/           break;
/*N*/       }
/*N*/       if ( pMod && pMod->GetDepends() )
/*N*/       {
/*N*/           SwClientIter aIter( *pMod );
/*N*/           if( aIter.First( TYPE(SwFrm) ) )
/*N*/               break;
/*N*/       }
/*N*/       aTmp++;
/*N*/   }
/*N*/   if( aTmp == Count()-1 )
/*N*/       pNd = 0;
/*N*/   else if( pNd )
/*N*/       (*pIdx) = aTmp;
/*N*/   return pNd;
/*N*/ }




/*************************************************************************
|*
|*    BOOL SwNodes::CheckNodesRange()
|*
|*    Beschreibung
|*      Teste ob der uebergene SRange nicht ueber die Grenzen der
|*      einzelnen Bereiche (PosIts, Autotext, Content, Icons und Inserts )
|*      hinaus reicht.
|*      Nach Wahrscheinlichkeit des Ranges sortiert.
|*
|*  Alg.: Da festgelegt ist, das aRange.aEnd den 1.Node hinter dem Bereich
|*        bezeichnet, wird hier auf aEnd <= End.. getestet !!
|*
|*    Parameter         SwIndex &   Start-Index vom Bereich
|*                      SwIndex &   End-Index vom Bereich
|*                      BOOL        TRUE:   Start+End in gleicher Section!
|*                                  FALSE:  Start+End in verschiedenen Sect.
|*    Return-Wert       BOOL        TRUE:   gueltiger SRange
|*                                  FALSE:  ungueltiger SRange
|*
|*    Ersterstellung    JP 23.04.91
|*    Letzte Aenderung  JP 18.06.92
|*
*************************************************************************/

/*N*/ inline int TstIdx( ULONG nSttIdx, ULONG nEndIdx, ULONG nStt, ULONG nEnd )
/*N*/ {
/*N*/   return nStt < nSttIdx && nEnd >= nSttIdx &&
/*N*/           nStt < nEndIdx && nEnd >= nEndIdx;
/*N*/ }

/*N*/ BOOL SwNodes::CheckNodesRange( const SwNodeIndex& rStt, const SwNodeIndex& rEnd ) const
/*N*/ {
/*N*/   ULONG nStt = rStt.GetIndex(), nEnd = rEnd.GetIndex();
/*N*/   if( TstIdx( nStt, nEnd, pEndOfContent->StartOfSectionIndex(),
/*N*/               pEndOfContent->GetIndex() )) return TRUE;
/*?*/   if( TstIdx( nStt, nEnd, pEndOfAutotext->StartOfSectionIndex(),
/*?*/               pEndOfAutotext->GetIndex() )) return TRUE;
/*?*/   if( TstIdx( nStt, nEnd, pEndOfPostIts->StartOfSectionIndex(),
/*?*/               pEndOfPostIts->GetIndex() )) return TRUE;
/*?*/   if( TstIdx( nStt, nEnd, pEndOfInserts->StartOfSectionIndex(),
/*?*/               pEndOfInserts->GetIndex() )) return TRUE;
/*?*/   if( TstIdx( nStt, nEnd, pEndOfRedlines->StartOfSectionIndex(),
/*?*/               pEndOfRedlines->GetIndex() )) return TRUE;
/*?*/
/*?*/   return FALSE;       // liegt irgendwo dazwischen, FEHLER
/*N*/ }


/*************************************************************************
|*
|*    void SwNodes::DelNodes()
|*
|*    Beschreibung
|*      Loesche aus den NodesArray ab einer Position entsprechend Node's.
|*
|*    Parameter         SwIndex &   Der Startpunkt im Nodes-Array
|*                      USHORT      die Anzahl
|*
|*    Ersterstellung    JP 23.04.91
|*    Letzte Aenderung  JP 23.04.91
|*
*************************************************************************/
/*N*/ void SwNodes::DelNodes( const SwNodeIndex & rStart, ULONG nCnt )
/*N*/ {
/*N*/   int bUpdateNum = 0;
/*N*/   ULONG nSttIdx = rStart.GetIndex();
/*N*/
/*N*/   if( !nSttIdx && nCnt == GetEndOfContent().GetIndex()+1 )
/*N*/   {
/*N*/       // es wird das gesamte Nodes-Array zerstoert, man ist im Doc DTOR!
/*N*/       // Die initialen Start-/End-Nodes duerfen nur im SwNodes-DTOR
/*N*/       // zerstoert werden!
/*N*/       SwNode* aEndNdArr[] = { pEndOfContent,
/*N*/                               pEndOfPostIts, pEndOfInserts,
/*N*/                               pEndOfAutotext, pEndOfRedlines,
/*N*/                               0
/*N*/                             };
/*N*/
/*N*/       SwNode** ppEndNdArr = aEndNdArr;
/*N*/       while( *ppEndNdArr )
/*N*/       {
/*N*/           nSttIdx = (*ppEndNdArr)->StartOfSectionIndex() + 1;
/*N*/           ULONG nEndIdx = (*ppEndNdArr)->GetIndex();
/*N*/
/*N*/           if( nSttIdx != nEndIdx )
/*N*/               RemoveNode( nSttIdx, nEndIdx - nSttIdx, TRUE );
/*N*/
/*N*/           ++ppEndNdArr;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for( ULONG n = nSttIdx, nEnd = nSttIdx + nCnt; n < nEnd; ++n )
/*N*/       {
/*N*/           SwNode* pNd = (*this)[ n ];
/*N*/
/*N*/           if( pNd->IsTxtNode() &&
/*N*/               NO_NUMBERING != ((SwTxtNode*)pNd)->GetTxtColl()->GetOutlineLevel() )
/*N*/           {                   // loesche die Gliederungs-Indizies.
/*?*/               USHORT nIdxPos;
/*?*/               if( pOutlineNds->Seek_Entry( pNd, &nIdxPos ))
/*?*/               {
/*?*/                   pOutlineNds->Remove( nIdxPos );
/*?*/                   bUpdateNum = 1;
/*?*/               }
/*N*/           }
/*N*/           if( pNd->IsCntntNode() )
/*N*/               ((SwCntntNode*)pNd)->InvalidateNumRule();
/*N*/       }
/*N*/       RemoveNode( nSttIdx, nCnt, TRUE );
/*N*/
/*N*/       // rufe noch das Update fuer die Gliederungsnumerierung auf
/*N*/       if( bUpdateNum )
/*?*/           UpdtOutlineIdx( rStart.GetNode() );
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*    USHORT HighestLevel( SwNodes & rNodes, const SwNodeRange & rRange )
|*
|*    Beschreibung
|*      Berechne den hoehsten Level innerhalb des Bereiches
|*
|*    Parameter         SwNodes &   das Node-Array
|*                      SwNodeRange &   der zu ueberpruefende Bereich
|*    Return            USHORT      der hoechste Level
|*
|*    Ersterstellung    JP 24.04.91
|*    Letzte Aenderung  JP 24.04.91
|*
*************************************************************************/




/*************************************************************************
|*
|*    SwNodes::Move()
|*
|*    Beschreibung
|*    Parameter         SwPaM&      zu kopierender Bereich
|*                      SwNodes&    in dieses Nodes-Array
|*                      SwPosition& auf diese Position im Nodes-Array
|*    Ersterstellung    JP 09.07.92
|*    Letzte Aenderung  JP 09.07.92
|*
*************************************************************************/



/*************************************************************************
|*
|*    SwNodes::_Copy()
|*
|*    Beschreibung
|*    Parameter         SwNodeRange&    zu kopierender Bereich
|*                      SwDoc&      in dieses Dokument
|*                      SwIndex&    auf diese Position im Nodes-Array
|*    Ersterstellung    JP 11.11.92
|*    Letzte Aenderung  JP 11.11.92
|*
*************************************************************************/

/*N*/ inline BYTE MaxLvl( BYTE nMin, BYTE nMax, short nNew )
/*N*/ {
/*N*/   return (BYTE)(nNew < nMin ? nMin : nNew > nMax ? nMax : nNew);
/*N*/ }

/*N*/ void SwNodes::_CopyNodes( const SwNodeRange& rRange,
/*N*/           const SwNodeIndex& rIndex, BOOL bNewFrms, BOOL bTblInsDummyNode ) const
/*N*/ {
/*N*/   SwDoc* pDoc = rIndex.GetNode().GetDoc();
/*N*/
/*N*/   SwNode * pAktNode;
/*N*/   if( rIndex == 0 ||
/*N*/       ( (pAktNode = &rIndex.GetNode())->GetStartNode() &&
/*N*/         !pAktNode->StartOfSectionIndex() ))
/*?*/       return;
/*N*/
/*N*/   SwNodeRange aRg( rRange );
/*N*/
/*N*/   // "einfache" StartNodes oder EndNodes ueberspringen
/*N*/   while( ND_STARTNODE == (pAktNode = (*this)[ aRg.aStart ])->GetNodeType()
/*N*/           || ( pAktNode->IsEndNode() &&
/*N*/               !pAktNode->pStartOfSection->IsSectionNode() ) )
/*N*/       aRg.aStart++;
/*N*/
/*N*/   // falls aEnd-1 auf keinem ContentNode steht, dann suche den vorherigen
/*N*/   aRg.aEnd--;
/*N*/   while( (( pAktNode = (*this)[ aRg.aEnd ])->GetStartNode() &&
/*N*/           !pAktNode->IsSectionNode() ) ||
/*N*/           ( pAktNode->IsEndNode() &&
/*N*/           ND_STARTNODE == pAktNode->pStartOfSection->GetNodeType()) )
/*N*/       aRg.aEnd--;
/*N*/   aRg.aEnd++;
/*N*/
/*N*/   // wird im selben Array's verschoben, dann ueberpruefe die Einfuegepos.
/*N*/   if( aRg.aStart >= aRg.aEnd )
/*?*/       return;
/*N*/
/*N*/   if( this == &pDoc->GetNodes() &&
/*N*/       rIndex.GetIndex() >= aRg.aStart.GetIndex() &&
/*N*/       rIndex.GetIndex() < aRg.aEnd.GetIndex() )
/*?*/           return;
/*N*/
/*N*/   SwNodeIndex aInsPos( rIndex );
/*N*/   SwNodeIndex aOrigInsPos( rIndex, -1 );          // Originale Insert Pos
/*N*/   USHORT nLevel = 0;                          // Level-Counter
/*N*/
/*N*/   for( ULONG nNodeCnt = aRg.aEnd.GetIndex() - aRg.aStart.GetIndex();
/*N*/           nNodeCnt > 0; --nNodeCnt )
/*N*/   {
/*N*/       pAktNode = &aRg.aStart.GetNode();
/*N*/       switch( pAktNode->GetNodeType() )
/*N*/       {
/*N*/       case ND_TABLENODE:
/*N*/           // dann kopiere mal den TableNode
/*N*/           // Tabelle in Tabelle kopieren ?
/*N*/           // Tabell in Fussnote kopieren ?
/*N*/           if( pDoc->IsIdxInTbl( aInsPos ) ||
/*N*/               ( aInsPos < pDoc->GetNodes().GetEndOfInserts().GetIndex() &&
/*N*/                   pDoc->GetNodes().GetEndOfInserts().StartOfSectionIndex()
/*N*/                   < aInsPos.GetIndex() ))
/*N*/           {
/*?*/               nNodeCnt -=
/*?*/                   ( pAktNode->EndOfSectionIndex() -
/*?*/                       aRg.aStart.GetIndex() );
/*?*/
/*?*/               // dann alle Nodes der Tabelle in die akt. Zelle kopieren
/*?*/               // fuer den TabellenNode einen DummyNode einfuegen?
/*?*/               if( bTblInsDummyNode )
/*?*/                   new SwNode( aInsPos, ND_SECTIONDUMMY );
/*?*/
/*?*/               for( aRg.aStart++; aRg.aStart.GetIndex() <
/*?*/                   pAktNode->EndOfSectionIndex();
/*?*/                   aRg.aStart++ )
/*?*/               {
/*?*/                   // fuer den Box-StartNode einen DummyNode einfuegen?
/*?*/                   if( bTblInsDummyNode )
/*?*/                       new SwNode( aInsPos, ND_SECTIONDUMMY );
/*?*/
/*?*/                   SwStartNode* pSttNd = aRg.aStart.GetNode().GetStartNode();
/*?*/                   _CopyNodes( SwNodeRange( *pSttNd, + 1,
/*?*/                                           *pSttNd->EndOfSectionNode() ),
/*?*/                               aInsPos, bNewFrms, FALSE );
/*?*/
/*?*/                   // fuer den Box-EndNode einen DummyNode einfuegen?
/*?*/                   if( bTblInsDummyNode )
/*?*/                       new SwNode( aInsPos, ND_SECTIONDUMMY );
/*?*/                   aRg.aStart = *pSttNd->EndOfSectionNode();
/*?*/               }
/*?*/               // fuer den TabellenEndNode einen DummyNode einfuegen?
/*?*/               if( bTblInsDummyNode )
/*?*/                   new SwNode( aInsPos, ND_SECTIONDUMMY );
/*?*/               aRg.aStart = *pAktNode->EndOfSectionNode();
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               SwNodeIndex nStt( aInsPos, -1 );
/*N*/               SwTableNode* pTblNd = ((SwTableNode*)pAktNode)->
/*N*/                                       MakeCopy( pDoc, aInsPos );
/*N*/               nNodeCnt -= aInsPos.GetIndex() - nStt.GetIndex() -2;
/*N*/
/*N*/               aRg.aStart = pAktNode->EndOfSectionIndex();
/*N*/
/*N*/               if( bNewFrms && pTblNd )
/*N*/               {
/*N*/                   nStt = aInsPos;
/*N*/                   pTblNd->MakeFrms( &nStt );
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case ND_SECTIONNODE:            // SectionNode
/*?*/           // der gesamte Bereich oder nur ein Teil ??
/*?*/           if( pAktNode->EndOfSectionIndex() < aRg.aEnd.GetIndex() )
/*?*/           {
/*?*/               // also der gesamte, lege einen neuen SectionNode an
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwNodeIndex nStt( aInsPos, -1 );
/*?*/           }
/*?*/           break;
/*?*/
/*N*/       case ND_STARTNODE:              // StartNode gefunden
/*N*/           {
/*N*/               SwStartNode* pTmp = new SwStartNode( aInsPos, ND_STARTNODE,
/*N*/                           ((SwStartNode*)pAktNode)->GetStartNodeType() );
/*N*/               new SwEndNode( aInsPos, *pTmp );
/*N*/               aInsPos--;
/*N*/               nLevel++;
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case ND_ENDNODE:
/*N*/           if( nLevel )                        // vollstaendige Section
/*N*/           {
/*N*/               --nLevel;
/*N*/               aInsPos++;                      // EndNode schon vorhanden
/*N*/           }
/*N*/           else if( !pAktNode->pStartOfSection->IsSectionNode() )
/*N*/           {
/*N*/               // erzeuge eine Section an der originalen InsertPosition
/*N*/               SwNodeRange aTmpRg( aOrigInsPos, 1, aInsPos );
/*N*/               pDoc->GetNodes().SectionDown( &aTmpRg,
/*N*/                       pAktNode->pStartOfSection->GetStartNodeType() );
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case ND_TEXTNODE:
/*N*/       case ND_GRFNODE:
/*N*/       case ND_OLENODE:
/*N*/           {
/*N*/               SwCntntNode* pNew = ((SwCntntNode*)pAktNode)->MakeCopy(
/*N*/                                           pDoc, aInsPos );
/*N*/               if( !bNewFrms )         // dflt. werden die Frames immer angelegt
/*N*/                   pNew->DelFrms();
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case ND_SECTIONDUMMY:
/*?*/           if( (const SwNodes*)this == GetDoc()->GetUndoNds() )
/*?*/           {
/*?*/               // dann muss an der akt. InsPos auch ein SectionNode
/*?*/               // (Start/Ende) stehen; dann diesen ueberspringen.
/*?*/               // Andernfalls nicht weiter beachten.
/*?*/               SwNode* pTmpNd = pDoc->GetNodes()[ aInsPos ];
/*?*/               if( pTmpNd->IsSectionNode() ||
/*?*/                   pTmpNd->FindStartNode()->IsSectionNode() )
/*?*/                   aInsPos++;  // ueberspringen
/*?*/           }
/*?*/           else
/*?*/               ASSERT( FALSE, "wie kommt diser Node ins Nodes-Array??" );
/*?*/           break;
/*?*/
/*?*/       default:
/*?*/           ASSERT( FALSE, "weder Start-/End-/Content-Node, unbekannter Typ" );
/*N*/       }
/*N*/       aRg.aStart++;
/*N*/   }
/*N*/
/*N*/
/*N*/ #ifdef JP_DEBUG
/*N*/   {
/*N*/           extern Writer* GetDebugWriter(const String&);
/*N*/
/*N*/       Writer* pWriter = GetDebugWriter(aEmptyStr);
/*N*/       if( pWriter )
/*N*/       {
/*N*/           int nError;
/*N*/           SvFileStream aStrm( "c:\\$$copy.db", STREAM_WRITE );
/*N*/           SwWriter aWriter( aStrm, *pMyDoc );
/*N*/           aWriter.Write( &nError, pWriter );
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/ }

/*N*/ void SwNodes::_DelDummyNodes( const SwNodeRange& rRg )
/*N*/ {
/*N*/   SwNodeIndex aIdx( rRg.aStart );
/*N*/   while( aIdx.GetIndex() < rRg.aEnd.GetIndex() )
/*N*/   {
/*N*/       if( ND_SECTIONDUMMY == aIdx.GetNode().GetNodeType() )
/*?*/           RemoveNode( aIdx.GetIndex(), 1, TRUE );
/*N*/       else
/*N*/           aIdx++;
/*N*/   }
/*N*/ }

/*N*/ SwStartNode* SwNodes::MakeEmptySection( const SwNodeIndex& rIdx,
/*N*/                                       SwStartNodeType eSttNdTyp )
/*N*/ {
/*N*/   SwStartNode* pSttNd = new SwStartNode( rIdx, ND_STARTNODE, eSttNdTyp );
/*N*/   new SwEndNode( rIdx, *pSttNd );
/*N*/   return pSttNd;
/*N*/ }


/*N*/ SwStartNode* SwNodes::MakeTextSection( const SwNodeIndex & rWhere,
/*N*/                                       SwStartNodeType eSttNdTyp,
/*N*/                                       SwTxtFmtColl *pColl,
/*N*/                                       SwAttrSet* pAutoAttr )
/*N*/ {
/*N*/   SwStartNode* pSttNd = new SwStartNode( rWhere, ND_STARTNODE, eSttNdTyp );
/*N*/   new SwEndNode( rWhere, *pSttNd );
/*N*/   MakeTxtNode( SwNodeIndex( rWhere, - 1 ), pColl, pAutoAttr );
/*N*/   return pSttNd;
/*N*/ }

    // zum naechsten Content-Node, der nicht geschuetzt oder versteckt ist
    // (beides auf FALSE ==> GoNext/GoPrevious!!!)
/*N*/ SwCntntNode* SwNodes::GoNextSection( SwNodeIndex * pIdx,
/*N*/                           int bSkipHidden, int bSkipProtect ) const
/*N*/ {
/*N*/   int bFirst = TRUE;
/*N*/   SwNodeIndex aTmp( *pIdx );
/*N*/   const SwNode* pNd;
/*N*/   while( aTmp < Count() - 1 )
/*N*/   {
/*N*/       if( ND_SECTIONNODE == ( pNd = (*this)[aTmp])->GetNodeType() )
/*N*/       {
/*N*/           const SwSection& rSect = ((SwSectionNode*)pNd)->GetSection();
/*N*/           if( (bSkipHidden && rSect.IsHiddenFlag()) ||
/*N*/               (bSkipProtect && rSect.IsProtectFlag()) )
/*N*/               // dann diese Section ueberspringen
/*?*/               aTmp = *pNd->EndOfSectionNode();
/*N*/           bFirst = FALSE;
/*N*/       }
/*N*/       else if( bFirst )
/*N*/       {
/*N*/           bFirst = FALSE;
/*N*/           if( pNd->pStartOfSection->IsSectionNode() )
/*N*/           {
/*N*/               const SwSection& rSect = ((SwSectionNode*)pNd->
/*N*/                               pStartOfSection)->GetSection();
/*N*/               if( (bSkipHidden && rSect.IsHiddenFlag()) ||
/*N*/                   (bSkipProtect && rSect.IsProtectFlag()) )
/*N*/                   // dann diese Section ueberspringen
/*N*/                   aTmp = *pNd->EndOfSectionNode();
/*N*/           }
/*N*/       }
/*N*/       else if( ND_CONTENTNODE & pNd->GetNodeType() )
/*N*/       {
/*N*/           const SwSectionNode* pSectNd;
/*N*/           if( ( bSkipHidden || bSkipProtect ) &&
/*N*/               0 != (pSectNd = pNd->FindSectionNode() ) &&
/*N*/               ( ( bSkipHidden && pSectNd->GetSection().IsHiddenFlag() ) ||
/*N*/                 ( bSkipProtect && pSectNd->GetSection().IsProtectFlag() )) )
/*N*/           {
/*?*/               aTmp = *pSectNd->EndOfSectionNode();
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               (*pIdx) = aTmp;
/*N*/               return (SwCntntNode*)pNd;
/*N*/           }
/*N*/       }
/*N*/       aTmp++;
/*N*/       bFirst = FALSE;
/*N*/   }
/*?*/   return 0;
/*N*/ }

/*N*/ SwCntntNode* SwNodes::GoPrevSection( SwNodeIndex * pIdx,
/*N*/                           int bSkipHidden, int bSkipProtect ) const
/*N*/ {
/*N*/   int bFirst = TRUE;
/*N*/   SwNodeIndex aTmp( *pIdx );
/*N*/   const SwNode* pNd;
/*N*/   while( aTmp > 0 )
/*N*/   {
/*N*/       if( ND_ENDNODE == ( pNd = (*this)[aTmp])->GetNodeType() )
/*N*/       {
/*N*/           if( pNd->pStartOfSection->IsSectionNode() )
/*N*/           {
/*N*/               const SwSection& rSect = ((SwSectionNode*)pNd->
/*N*/                                           pStartOfSection)->GetSection();
/*N*/               if( (bSkipHidden && rSect.IsHiddenFlag()) ||
/*N*/                   (bSkipProtect && rSect.IsProtectFlag()) )
/*N*/                   // dann diese Section ueberspringen
/*?*/                   aTmp = *pNd->StartOfSectionNode();
/*N*/           }
/*N*/           bFirst = FALSE;
/*N*/       }
/*N*/       else if( bFirst )
/*N*/       {
/*N*/           bFirst = FALSE;
/*N*/           if( pNd->pStartOfSection->IsSectionNode() )
/*N*/           {
/*?*/               const SwSection& rSect = ((SwSectionNode*)pNd->
/*?*/                               pStartOfSection)->GetSection();
/*?*/               if( (bSkipHidden && rSect.IsHiddenFlag()) ||
/*?*/                   (bSkipProtect && rSect.IsProtectFlag()) )
/*?*/                   // dann diese Section ueberspringen
/*?*/                   aTmp = *pNd->StartOfSectionNode();
/*N*/           }
/*N*/       }
/*N*/       else if( ND_CONTENTNODE & pNd->GetNodeType() )
/*N*/       {
/*N*/           const SwSectionNode* pSectNd;
/*N*/           if( ( bSkipHidden || bSkipProtect ) &&
/*N*/               0 != (pSectNd = pNd->FindSectionNode() ) &&
/*N*/               ( ( bSkipHidden && pSectNd->GetSection().IsHiddenFlag() ) ||
/*N*/                 ( bSkipProtect && pSectNd->GetSection().IsProtectFlag() )) )
/*N*/           {
/*?*/               aTmp = *pSectNd;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               (*pIdx) = aTmp;
/*N*/               return (SwCntntNode*)pNd;
/*N*/           }
/*N*/       }
/*N*/       aTmp--;
/*N*/   }
/*N*/   return 0;
/*N*/ }


    // suche den vorhergehenden [/nachfolgenden ] ContentNode oder
    // TabellenNode mit Frames. Wird kein Ende angeben, dann wird mit
    // dem FrameIndex begonnen; ansonsten, wird mit dem vor rFrmIdx und
    // dem hintern pEnd die Suche gestartet. Sollte kein gueltiger Node
    // gefunden werden, wird 0 returnt. rFrmIdx zeigt auf dem Node mit
    // Frames
/*N*/ SwNode* SwNodes::FindPrvNxtFrmNode( SwNodeIndex& rFrmIdx,
/*N*/                                   const SwNode* pEnd ) const
/*N*/ {
/*N*/   SwNode* pFrmNd = 0;
/*N*/
/*N*/   // habe wir gar kein Layout, vergiss es
/*N*/   if( GetDoc()->GetRootFrm() )
/*N*/   {
/*N*/       SwNode* pSttNd = &rFrmIdx.GetNode();
/*N*/
/*N*/       // wird in eine versteckte Section verschoben ??
/*N*/       SwSectionNode* pSectNd = pSttNd->IsSectionNode()
/*N*/                   ? pSttNd->FindStartNode()->FindSectionNode()
/*N*/                   : pSttNd->FindSectionNode();
/*N*/       if( !( pSectNd && pSectNd->GetSection().CalcHiddenFlag()/*IsHiddenFlag()*/ ) )
/*N*/       {
/*N*/           SwNodeIndex aIdx( rFrmIdx );
/*N*/           SwNode* pNd;
/*N*/           if( pEnd )
/*N*/           {
/*N*/               aIdx--;
/*N*/               pNd = &aIdx.GetNode();
/*N*/           }
/*N*/           else
/*?*/               pNd = pSttNd;
/*N*/
/*N*/           if( ( pFrmNd = pNd )->IsCntntNode() )
/*N*/               rFrmIdx = aIdx;
/*N*/
/*N*/               // suche nach vorne/hinten nach einem Content Node
/*N*/           else if( 0 != ( pFrmNd = GoPrevSection( &aIdx, TRUE, FALSE )) &&
/*N*/                   ::binfilter::CheckNodesRange( aIdx, rFrmIdx, TRUE ) &&
/*N*/                   // nach vorne nie aus der Tabelle hinaus!
/*N*/                   pFrmNd->FindTableNode() == pSttNd->FindTableNode() &&
/*N*/                   // Bug 37652: nach hinten nie aus der Tabellenzelle hinaus!
/*N*/                   (!pFrmNd->FindTableNode() || pFrmNd->FindTableBoxStartNode()
/*N*/                       == pSttNd->FindTableBoxStartNode() ) &&
/*N*/                    (!pSectNd || pSttNd->IsSectionNode() ||
/*N*/                     pSectNd->GetIndex() < pFrmNd->GetIndex())
/*N*/                   )
/*N*/           {
/*N*/               rFrmIdx = aIdx;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               if( pEnd )
/*N*/                   aIdx = pEnd->GetIndex() + 1;
/*N*/               else
/*?*/                   aIdx = rFrmIdx;
/*N*/
/*N*/               // JP 19.09.93: aber nie die Section dafuer verlassen !!
/*N*/               if( ( pEnd && ( pFrmNd = &aIdx.GetNode())->IsCntntNode() ) ||
/*N*/                   ( 0 != ( pFrmNd = GoNextSection( &aIdx, TRUE, FALSE )) &&
/*N*/                   ::binfilter::CheckNodesRange( aIdx, rFrmIdx, TRUE ) &&
/*N*/                   // JP 27.01.99: wenn der "Start"Node ein TabellenNode ist,
/*N*/                   // dann kann der dahinter liegende nie der gleiche sein!
/*N*/                   ( pSttNd->IsTableNode() ||
/*N*/                     ( pFrmNd->FindTableNode() == pSttNd->FindTableNode() &&
/*N*/                       // Bug 37652: nach hinten nie aus der Tabellenzelle hinaus!
/*N*/                       (!pFrmNd->FindTableNode() || pFrmNd->FindTableBoxStartNode()
/*N*/                       == pSttNd->FindTableBoxStartNode() ))) &&
/*N*/                    (!pSectNd || pSttNd->IsSectionNode() ||
/*N*/                     pSectNd->EndOfSectionIndex() > pFrmNd->GetIndex())
/*N*/                   ))
/*N*/               {
/*N*/                   //JP 18.02.99: Undo von Merge einer Tabelle mit der
/*N*/                   // der vorherigen, wenn dahinter auch noch eine steht
/*N*/                   // falls aber der Node in einer Tabelle steht, muss
/*N*/                   // natuerlich dieser returnt werden, wenn der SttNode eine
/*N*/                   // Section oder Tabelle ist!
/*N*/                   SwTableNode* pTblNd;
/*N*/                   if( ( pSttNd->IsTableNode() ) &&
/*N*/                       0 != ( pTblNd = pFrmNd->FindTableNode() ))
/*N*/                   {
/*?*/                       pFrmNd = pTblNd;
/*?*/                       rFrmIdx = *pFrmNd;
/*N*/                   }
/*N*/                   else
/*N*/                       rFrmIdx = aIdx;
/*N*/               }
/*N*/               else if( pNd->IsEndNode() && pNd->FindStartNode()->IsTableNode() )
/*N*/               {
/*?*/                   pFrmNd = pNd->FindStartNode();
/*?*/                   rFrmIdx = *pFrmNd;
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   if( pEnd )
/*?*/                       aIdx = pEnd->GetIndex() + 1;
/*?*/                   else
/*?*/                       aIdx = rFrmIdx.GetIndex() + 1;
/*?*/
/*?*/                   if( (pFrmNd = &aIdx.GetNode())->IsTableNode() )
/*?*/                       rFrmIdx = aIdx;
/*?*/                   else
/*?*/                   {
/*?*/                       pFrmNd = 0;
/*?*/
/*?*/                       // is there some sectionnodes before a tablenode?
/*?*/                       while( aIdx.GetNode().IsSectionNode() )
/*?*/                       {
/*?*/                           const SwSection& rSect = aIdx.GetNode().
/*?*/                               GetSectionNode()->GetSection();
/*?*/                           if( rSect.IsHiddenFlag() )
/*?*/                               aIdx = aIdx.GetNode().EndOfSectionIndex()+1;
/*?*/                           else
/*?*/                               aIdx++;
/*?*/                       }
/*?*/                       if( aIdx.GetNode().IsTableNode() )
/*?*/                       {
/*?*/                           rFrmIdx = aIdx;
/*?*/                           pFrmNd = &aIdx.GetNode();
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return pFrmNd;
/*N*/ }


/*N*/ void SwNodes::ForEach( const SwNodeIndex& rStart, const SwNodeIndex& rEnd,
/*N*/                   FnForEach_SwNodes fnForEach, void* pArgs )
/*N*/ {
/*N*/   BigPtrArray::ForEach( rStart.GetIndex(), rEnd.GetIndex(),
/*N*/                           (FnForEach) fnForEach, pArgs );
/*N*/ }

/*N*/ struct _TempBigPtrEntry : public BigPtrEntry
/*N*/ {
/*N*/   _TempBigPtrEntry() {}
/*N*/ };


/*N*/ void SwNodes::RemoveNode( ULONG nDelPos, ULONG nSize, FASTBOOL bDel )
/*N*/ {
/*N*/   ULONG nEnd = nDelPos + nSize;
/*N*/   SwNode* pNew = (*this)[ nEnd ];
/*N*/
/*N*/   if( pRoot )
/*N*/   {
/*N*/       SwNodeIndex *p = pRoot;
/*N*/       while( p )
/*N*/       {
/*N*/           ULONG nIdx = p->GetIndex();
/*N*/           SwNodeIndex* pNext = p->pNext;
/*N*/           if( nDelPos <= nIdx && nIdx < nEnd )
/*N*/               (*p) = *pNew;
/*N*/
/*N*/           p = pNext;
/*N*/       }
/*N*/
/*N*/       p = pRoot->pPrev;
/*N*/       while( p )
/*N*/       {
/*?*/           ULONG nIdx = p->GetIndex();
/*?*/           SwNodeIndex* pPrev = p->pPrev;
/*?*/           if( nDelPos <= nIdx && nIdx < nEnd )
/*?*/               (*p) = *pNew;
/*?*/
/*?*/           p = pPrev;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( bDel )
/*N*/   {
/*N*/       ULONG nCnt = nSize;
/*N*/       SwNode *pDel = (*this)[ nDelPos+nCnt-1 ], *pPrev = (*this)[ nDelPos+nCnt-2 ];
/*N*/
/*N*/ #if 1
/*N*/ // temp. Object setzen
/*N*/       //JP 24.08.98: muessten eigentlich einzeln removed werden, weil
/*N*/       //      das Remove auch rekursiv gerufen werden kann, z.B. bei
/*N*/       //      zeichengebundenen Rahmen. Da aber dabei viel zu viel
/*N*/       //      ablaueft, wird hier ein temp. Objekt eingefuegt, das
/*N*/       //      dann mit dem Remove wieder entfernt wird.
/*N*/       // siehe Bug 55406
/*N*/       _TempBigPtrEntry aTempEntry;
/*N*/       BigPtrEntry* pTempEntry = &aTempEntry;
/*N*/
/*N*/       while( nCnt-- )
/*N*/       {
/*N*/           delete pDel;
/*N*/           pDel = pPrev;
/*N*/           ULONG nPrevNdIdx = pPrev->GetIndex();
/*N*/           BigPtrArray::Replace( nPrevNdIdx+1, pTempEntry );
/*N*/           if( nCnt )
/*N*/               pPrev = (*this)[ nPrevNdIdx  - 1 ];
/*N*/       }
/*N*/       nDelPos = pDel->GetIndex() + 1;
/*N*/   }
/*N*/ #else
/*N*/ // nach jedem Del ein Remove rufen - teuer!
/*N*/       //JP 24.08.98: muessen leider einzeln removed werden, weil das
/*N*/       //              auch rekursiv gerufen wird - zeichengeb. Flys!
/*N*/       // siehe Bug 55406
/*N*/       while( nCnt-- )
/*N*/       {
/*N*/           delete pDel;
/*N*/           pDel = pPrev;
/*N*/           ULONG nPrevNdIdx = pPrev->GetIndex();
/*N*/           BigPtrArray::Remove( nPrevNdIdx+1, 1 );
/*N*/           if( nCnt )
/*N*/               pPrev = (*this)[ nPrevNdIdx  - 1 ];
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/ #endif
/*N*/
/*N*/   BigPtrArray::Remove( nDelPos, nSize );
/*N*/ }

/*N*/ void SwNodes::RegisterIndex( SwNodeIndex& rIdx )
/*N*/ {
/*N*/   if( !pRoot )        // noch keine Root gesetzt?
/*N*/   {
/*N*/       pRoot = &rIdx;
/*N*/       pRoot->pPrev = 0;
/*N*/       pRoot->pNext = 0;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // immer hinter die Root haengen
/*N*/       rIdx.pNext = pRoot->pNext;
/*N*/       pRoot->pNext = &rIdx;
/*N*/       rIdx.pPrev = pRoot;
/*N*/       if( rIdx.pNext )
/*N*/           rIdx.pNext->pPrev = &rIdx;
/*N*/   }
/*N*/ }

/*N*/ void SwNodes::DeRegisterIndex( SwNodeIndex& rIdx )
/*N*/ {
/*N*/   register SwNodeIndex* pN = rIdx.pNext;
/*N*/   register SwNodeIndex* pP = rIdx.pPrev;
/*N*/
/*N*/   if( pRoot == &rIdx )
/*N*/       pRoot = pP ? pP : pN;
/*N*/
/*N*/   if( pP )
/*N*/       pP->pNext = pN;
/*N*/   if( pN )
/*N*/       pN->pPrev = pP;
/*N*/
/*N*/   rIdx.pNext = 0;
/*N*/   rIdx.pPrev = 0;
/*N*/ }

/*N*/ void SwNodes::Insert( const SwNodePtr pNode, const SwNodeIndex& rPos )
/*N*/ {
/*N*/   const ElementPtr pIns = pNode;
/*N*/   BigPtrArray::Insert( pIns, rPos.GetIndex() );
/*N*/ }

/*N*/ void SwNodes::Insert(const SwNodePtr pNode, ULONG nPos)
/*N*/ {
/*N*/   const ElementPtr pIns = pNode;
/*N*/   BigPtrArray::Insert( pIns, nPos );
/*N*/ }

    // #i31620#
    SwNode * SwNodes::operator[](int n) const
    {
        return operator[]((ULONG) n);
    }
}
