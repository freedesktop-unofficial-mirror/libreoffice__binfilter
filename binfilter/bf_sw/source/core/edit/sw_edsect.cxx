/*************************************************************************
 *
 *  $RCSfile: sw_edsect.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:22:59 $
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

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>       // fuer die UndoIds
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _EDIMP_HXX
#include <edimp.hxx>
#endif

#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>      // SwSectionFrm
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>       // SwCntntFrm
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>       // SwTabFrm
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>      // SwRootFrm
#endif
namespace binfilter {


    // SS fuer Bereiche
//STRIP001 const SwSection* SwEditShell::InsertSection( const SwSection& rNew,
//STRIP001                                           const SfxItemSet* pAttr )
//STRIP001 {
//STRIP001  const SwSection* pRet = 0;
//STRIP001  if( !IsTableMode() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      GetDoc()->StartUndo( UNDO_INSSECTION );
//STRIP001
//STRIP001      FOREACHPAM_START(this)
//STRIP001          const SwSection* pNew = GetDoc()->Insert( *PCURCRSR,
//STRIP001                                                      rNew, pAttr );
//STRIP001          if( !pRet )
//STRIP001              pRet = pNew;
//STRIP001      FOREACHPAM_END()
//STRIP001
//STRIP001      // Undo-Klammerung hier beenden
//STRIP001      GetDoc()->EndUndo( UNDO_INSSECTION );
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }


//STRIP001 BOOL SwEditShell::IsInsRegionAvailable() const
//STRIP001 {
//STRIP001  SwPaM* pCrsr;
//STRIP001  if( IsTableMode() || ( pCrsr = GetCrsr() )->GetNext() != pCrsr )
//STRIP001      return FALSE;
//STRIP001  if( pCrsr->HasMark() )
//STRIP001      return 0 != GetDoc()->IsInsRegionAvailable( *pCrsr );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


/*N*/ const SwSection* SwEditShell::GetCurrSection() const
/*N*/ {
/*N*/   if( IsTableMode() )
/*?*/       return 0;
/*N*/
/*N*/   return GetDoc()->GetCurrSection( *GetCrsr()->GetPoint() );
/*N*/ }

/*-----------------17.03.99 11:53-------------------
 * SwEditShell::GetAnySection liefert den fuer Spalten
 * zustaendigen Bereich, bei Fussnoten kann es nicht der
 * Bereich innerhalb der Fussnote sein.
 * --------------------------------------------------*/

//STRIP001 const SwSection* SwEditShell::GetAnySection( BOOL bOutOfTab, const Point* pPt ) const
//STRIP001 {
//STRIP001     SwFrm *pFrm;
//STRIP001  if ( pPt )
//STRIP001  {
//STRIP001      SwPosition aPos( *GetCrsr()->GetPoint() );
//STRIP001      Point aPt( *pPt );
//STRIP001      GetLayout()->GetCrsrOfst( &aPos, aPt );
//STRIP001      SwCntntNode *pNd = aPos.nNode.GetNode().GetCntntNode();
//STRIP001      pFrm = pNd->GetFrm( pPt );
//STRIP001  }
//STRIP001  else
//STRIP001      pFrm = GetCurrFrm( FALSE );
//STRIP001
//STRIP001  if( bOutOfTab && pFrm )
//STRIP001      pFrm = pFrm->FindTabFrm();
//STRIP001  if( pFrm && pFrm->IsInSct() )
//STRIP001  {
//STRIP001      SwSectionFrm* pSect = pFrm->FindSctFrm();
//STRIP001      ASSERT( pSect, "GetAnySection: Where's my Sect?" );
//STRIP001      if( pSect->IsInFtn() && pSect->GetUpper()->IsInSct() )
//STRIP001      {
//STRIP001          pSect = pSect->GetUpper()->FindSctFrm();
//STRIP001          ASSERT( pSect, "GetAnySection: Where's my SectFrm?" );
//STRIP001      }
//STRIP001      return pSect->GetSection();
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 USHORT SwEditShell::GetSectionFmtCount() const
//STRIP001 {
//STRIP001  return GetDoc()->GetSections().Count();
//STRIP001 }


/*N*/ BOOL SwEditShell::IsAnySectionInDoc( BOOL bChkReadOnly, BOOL bChkHidden, BOOL bChkTOX ) const
/*N*/ {
/*N*/   const SwSectionFmts& rFmts = GetDoc()->GetSections();
/*N*/   USHORT nCnt = rFmts.Count();
        USHORT n=0;
/*N*/   for( n = 0; n < nCnt; ++n )
/*N*/   {
/*N*/       SectionType eTmpType;
/*N*/       const SwSectionFmt* pFmt = rFmts[ n ];
/*N*/       if( pFmt->IsInNodesArr() &&
/*N*/           (bChkTOX  ||
/*N*/               (eTmpType = pFmt->GetSection()->GetType()) != TOX_CONTENT_SECTION
/*N*/               && TOX_HEADER_SECTION != eTmpType ))
/*N*/       {
/*N*/           const SwSection& rSect = *rFmts[ n ]->GetSection();
/*N*/           if( (!bChkReadOnly && !bChkHidden ) ||
/*N*/               (bChkReadOnly && rSect.IsProtectFlag() ) ||
/*N*/               (bChkHidden && rSect.IsHiddenFlag() ) )
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/   return n != nCnt;
/*N*/ }

//STRIP001 USHORT SwEditShell::GetSectionFmtPos( const SwSectionFmt& rFmt ) const
//STRIP001 {
//STRIP001  SwSectionFmt* pFmt = (SwSectionFmt*)&rFmt;
//STRIP001  return GetDoc()->GetSections().GetPos( pFmt );
//STRIP001 }

//STRIP001 const SwSectionFmt& SwEditShell::GetSectionFmt( USHORT nFmt ) const
//STRIP001 {
//STRIP001  return *GetDoc()->GetSections()[ nFmt ];
//STRIP001 }


//STRIP001 void SwEditShell::DelSectionFmt( USHORT nFmt )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->DelSectionFmt( GetDoc()->GetSections()[ nFmt ] );
//STRIP001  // rufe das AttrChangeNotify auf der UI-Seite.
//STRIP001  CallChgLnk();
//STRIP001  EndAllAction();
//STRIP001 }


//STRIP001 void SwEditShell::ChgSection( USHORT nSect, const SwSection& rSect,
//STRIP001                              const SfxItemSet* pAttr )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->ChgSection( nSect, rSect, pAttr );
//STRIP001  // rufe das AttrChangeNotify auf der UI-Seite.
//STRIP001  CallChgLnk();
//STRIP001  EndAllAction();
//STRIP001 }

//STRIP001 void SwEditShell::ChgSectionPasswd(
//STRIP001      const ::com::sun::star::uno::Sequence <sal_Int8>& rNew,
//STRIP001         const SwSection& rSection )
//STRIP001 {
//STRIP001     GetDoc()->ChgSectionPasswd( rNew, rSection );
//STRIP001 }


//STRIP001 String SwEditShell::GetUniqueSectionName( const String* pChkStr ) const
//STRIP001 {
//STRIP001  return GetDoc()->GetUniqueSectionName( pChkStr );
//STRIP001 }

//STRIP001 void SwEditShell::SetSectionAttr( const SfxItemSet& rSet,
//STRIP001                                  SwSectionFmt* pSectFmt )
//STRIP001 {
//STRIP001  if( pSectFmt )
//STRIP001      _SetSectionAttr( *pSectFmt, rSet );
//STRIP001  else
//STRIP001  {
//STRIP001      // for all section in the selection
//STRIP001
//STRIP001      FOREACHPAM_START(this)
//STRIP001
//STRIP001          const SwPosition* pStt = PCURCRSR->Start(),
//STRIP001                          * pEnd = PCURCRSR->End();
//STRIP001
//STRIP001          const SwSectionNode* pSttSectNd = pStt->nNode.GetNode().FindSectionNode(),
//STRIP001                             * pEndSectNd = pEnd->nNode.GetNode().FindSectionNode();
//STRIP001
//STRIP001          if( pSttSectNd || pEndSectNd )
//STRIP001          {
//STRIP001              if( pSttSectNd )
//STRIP001                  _SetSectionAttr( *pSttSectNd->GetSection().GetFmt(),
//STRIP001                                  rSet );
//STRIP001              if( pEndSectNd && pSttSectNd != pEndSectNd )
//STRIP001                  _SetSectionAttr( *pEndSectNd->GetSection().GetFmt(),
//STRIP001                                  rSet );
//STRIP001
//STRIP001              if( pSttSectNd && pEndSectNd )
//STRIP001              {
//STRIP001                  SwNodeIndex aSIdx( pStt->nNode );
//STRIP001                  SwNodeIndex aEIdx( pEnd->nNode );
//STRIP001                  if( pSttSectNd->EndOfSectionIndex() <
//STRIP001                      pEndSectNd->GetIndex() )
//STRIP001                  {
//STRIP001                      aSIdx = pSttSectNd->EndOfSectionIndex() + 1;
//STRIP001                      aEIdx = *pEndSectNd;
//STRIP001                  }
//STRIP001
//STRIP001                  while( aSIdx < aEIdx )
//STRIP001                  {
//STRIP001                      if( 0 != (pSttSectNd = aSIdx.GetNode().GetSectionNode())
//STRIP001                          || ( aSIdx.GetNode().IsEndNode() &&
//STRIP001                              0 != ( pSttSectNd = aSIdx.GetNode().
//STRIP001                                  FindStartNode()->GetSectionNode())) )
//STRIP001                          _SetSectionAttr( *pSttSectNd->GetSection().GetFmt(),
//STRIP001                                          rSet );
//STRIP001                      aSIdx++;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001      FOREACHPAM_END()
//STRIP001  }
//STRIP001 }

//STRIP001 void SwEditShell::_SetSectionAttr( SwSectionFmt& rSectFmt,
//STRIP001                                  const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  if(SFX_ITEM_SET == rSet.GetItemState(RES_CNTNT, FALSE))
//STRIP001  {
//STRIP001      SfxItemSet aSet(rSet);
//STRIP001      aSet.ClearItem(RES_CNTNT);
//STRIP001      GetDoc()->SetAttr( aSet, rSectFmt );
//STRIP001  }
//STRIP001  else
//STRIP001      GetDoc()->SetAttr( rSet, rSectFmt );
//STRIP001
//STRIP001  // rufe das AttrChangeNotify auf der UI-Seite.
//STRIP001  CallChgLnk();
//STRIP001  EndAllAction();
//STRIP001 }

// search inside the cursor selection for full selected sections.
// if any part of section in the selection return 0.
// if more than one in the selection return the count
//STRIP001 USHORT SwEditShell::GetFullSelectedSectionCount() const
//STRIP001 {
//STRIP001  USHORT nRet = 0;
//STRIP001  FOREACHPAM_START(this)
//STRIP001
//STRIP001      const SwPosition* pStt = PCURCRSR->Start(),
//STRIP001                      * pEnd = PCURCRSR->End();
//STRIP001      const SwCntntNode* pCNd;
//STRIP001      // check the selection, if Start at Node begin and End at Node end
//STRIP001      if( pStt->nContent.GetIndex() ||
//STRIP001          ( 0 == ( pCNd = pEnd->nNode.GetNode().GetCntntNode() )) ||
//STRIP001          pCNd->Len() != pEnd->nContent.GetIndex() )
//STRIP001      {
//STRIP001          nRet = 0;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001 // !!!!!!!!!!!!!!!!!!!!!!!!!!
//STRIP001 // what about table at start or end ?
//STRIP001 //       There is no selection possible!
//STRIP001 // What about only a table inside the section ?
//STRIP001 //       There is only a table selection possible!
//STRIP001
//STRIP001      SwNodeIndex aSIdx( pStt->nNode, -1 ), aEIdx( pEnd->nNode, +1 );
//STRIP001      if( !aSIdx.GetNode().IsSectionNode() ||
//STRIP001          !aEIdx.GetNode().IsEndNode() ||
//STRIP001          !aEIdx.GetNode().FindStartNode()->IsSectionNode() )
//STRIP001      {
//STRIP001          nRet = 0;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      ++nRet;
//STRIP001      if( &aSIdx.GetNode() != aEIdx.GetNode().FindStartNode() )
//STRIP001          ++nRet;
//STRIP001
//STRIP001  FOREACHPAM_END()
//STRIP001  return nRet;
//STRIP001 }


/**
 * Find the suitable node for a special insert (alt-enter).
 * This should enable inserting text before/after sections and tables.
 *
 * A node is found if:
 * 1) the innermost table/section is not in a write-protected area
 * 2) pCurrentPos is at or just before an end node
 *    (or at or just after a start node)
 * 3) there are only start/end nodes between pCurrentPos and the innermost
 *    table/section
 *
 * If a suitable node is found, an SwNode* is returned; else it is NULL.
 */
//STRIP001 const SwNode* lcl_SpecialInsertNode(const SwPosition* pCurrentPos)
//STRIP001 {
//STRIP001     const SwNode* pReturn = NULL;
//STRIP001
//STRIP001     // the current position
//STRIP001     //    const SwPosition* pCurrentPos = GetCrsr()->GetPoint();
//STRIP001     DBG_ASSERT( pCurrentPos != NULL, "Strange, we have no position!" );
//STRIP001     const SwNode& rCurrentNode = pCurrentPos->nNode.GetNode();
//STRIP001
//STRIP001
//STRIP001     // find innermost section or table.  At the end of this scope,
//STRIP001     // pInntermostNode contain the section/table before/after which we should
//STRIP001     // insert our empty paragraph, or it will be NULL if none is found.
//STRIP001     const SwNode* pInnermostNode = NULL;
//STRIP001     {
//STRIP001         const SwNode* pTableNode = rCurrentNode.FindTableNode();
//STRIP001         const SwNode* pSectionNode = rCurrentNode.FindSectionNode();
//STRIP001
//STRIP001         // find the table/section which is close
//STRIP001         if( pTableNode == NULL )
//STRIP001             pInnermostNode = pSectionNode;
//STRIP001         else if ( pSectionNode == NULL )
//STRIP001             pInnermostNode = pTableNode;
//STRIP001         else
//STRIP001         {
//STRIP001             // compare and choose the larger one
//STRIP001             pInnermostNode =
//STRIP001                 ( pSectionNode->GetIndex() > pTableNode->GetIndex() )
//STRIP001                 ? pSectionNode : pTableNode;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // The previous version had a check to skip empty read-only sections. Those
//STRIP001     // shouldn't occur, so we only need to check whether our pInnermostNode is
//STRIP001     // inside a protected area.
//STRIP001
//STRIP001     // Now, pInnermostNode is NULL or the innermost section or table node.
//STRIP001     if( (pInnermostNode != NULL) && !pInnermostNode->IsProtect() )
//STRIP001     {
//STRIP001         DBG_ASSERT( pInnermostNode->IsTableNode() ||
//STRIP001                     pInnermostNode->IsSectionNode(), "wrong node found" );
//STRIP001         DBG_ASSERT( ( pInnermostNode->GetIndex() <= rCurrentNode.GetIndex() )&&
//STRIP001                     ( pInnermostNode->EndOfSectionNode()->GetIndex() >=
//STRIP001                       rCurrentNode.GetIndex() ), "wrong node found" );
//STRIP001
//STRIP001         // we now need to find the possible start/end positions
//STRIP001
//STRIP001         // we found a start if
//STRIP001         // - we're at or just before a start node
//STRIP001         // - there are only start nodes between the current and pInnermostNode
//STRIP001         SwNodeIndex aBegin( pCurrentPos->nNode );
//STRIP001         if( rCurrentNode.IsCntntNode() &&
//STRIP001             (pCurrentPos->nContent.GetIndex() == 0))
//STRIP001             aBegin--;
//STRIP001         while( (aBegin != pInnermostNode->GetIndex()) &&
//STRIP001                aBegin.GetNode().IsStartNode() )
//STRIP001             aBegin--;
//STRIP001         bool bStart = ( aBegin == pInnermostNode->GetIndex() );
//STRIP001
//STRIP001         // we found an end if
//STRIP001         // - we're at or just before an end node
//STRIP001         // - there are only end nodes between the current node and
//STRIP001         //   pInnermostNode's end node
//STRIP001         SwNodeIndex aEnd( pCurrentPos->nNode );
//STRIP001         if( rCurrentNode.IsCntntNode() &&
//STRIP001             ( pCurrentPos->nContent.GetIndex() ==
//STRIP001               rCurrentNode.GetCntntNode()->Len() ) )
//STRIP001             aEnd++;
//STRIP001         while( (aEnd != pInnermostNode->EndOfSectionNode()->GetIndex()) &&
//STRIP001                aEnd.GetNode().IsEndNode() )
//STRIP001             aEnd++;
//STRIP001         bool bEnd = ( aEnd == pInnermostNode->EndOfSectionNode()->GetIndex() );
//STRIP001
//STRIP001         // evalutate result: if both start + end, end is preferred
//STRIP001         if( bEnd )
//STRIP001             pReturn = pInnermostNode->EndOfSectionNode();
//STRIP001         else if ( bStart )
//STRIP001             pReturn = pInnermostNode;
//STRIP001         // else pReturn = NULL;
//STRIP001     }
//STRIP001     // else: pReturn = NULL
//STRIP001
//STRIP001
//STRIP001     DBG_ASSERT( ( pReturn == NULL ) || pReturn->IsStartNode() ||
//STRIP001                                        pReturn->IsEndNode(),
//STRIP001                 "SpecialInsertNode failed" );
//STRIP001     return pReturn;
//STRIP001 }


/** a node can be special-inserted (alt-Enter) whenever lcl_SpecialInsertNode
    finds a suitable position
*/
//STRIP001 bool SwEditShell::CanSpecialInsert() const
//STRIP001 {
//STRIP001     return NULL != lcl_SpecialInsertNode( GetCrsr()->GetPoint() );
//STRIP001 }


/** check whether a node cen be special-inserted (alt-Enter), and do so. Return
    whether insertion was possible.
 */
//STRIP001 bool SwEditShell::DoSpecialInsert()
//STRIP001 {
//STRIP001     bool bRet = false;
//STRIP001
//STRIP001     // get current node
//STRIP001     SwPosition* pCursorPos = GetCrsr()->GetPoint();
//STRIP001     const SwNode* pInsertNode = lcl_SpecialInsertNode( pCursorPos );
//STRIP001     if( pInsertNode != NULL )
//STRIP001     {
//STRIP001      StartAllAction();
//STRIP001
//STRIP001         // adjust insert position to insert before start nodes and after end
//STRIP001         // nodes
//STRIP001         SwNodeIndex aInsertIndex( *pInsertNode,
//STRIP001                                   pInsertNode->IsStartNode() ? -1 : 0 );
//STRIP001         SwPosition aInsertPos( aInsertIndex );
//STRIP001
//STRIP001         // insert a new text node, and set the cursor
//STRIP001      bRet = GetDoc()->AppendTxtNode( aInsertPos );
//STRIP001      *pCursorPos = aInsertPos;
//STRIP001
//STRIP001      // call AttrChangeNotify for the UI
//STRIP001      CallChgLnk();
//STRIP001
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

}
