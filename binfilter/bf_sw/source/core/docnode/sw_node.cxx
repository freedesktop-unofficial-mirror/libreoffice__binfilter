/*************************************************************************
 *
 *  $RCSfile: sw_node.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:54 $
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

#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_CHARACTERITERATORMODE_HDL_
#include <com/sun/star/i18n/CharacterIteratorMode.hdl>
#endif

#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTANCHR_HXX
#include <fmtanchr.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _FTNFRM_HXX //autogen
#include <ftnfrm.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SWCACHE_HXX
#include <swcache.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _LAYFRM_HXX
#include <layfrm.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>  // SwTabFrm
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _FMTFTN_HXX
#include <fmtftn.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _PAGEFRM_HXX //autogen
#include <pagefrm.hxx>
#endif
#ifndef _NODE2LAY_HXX
#include <node2lay.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _PAGEDESC_HXX //autogen
#include <pagedesc.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
namespace binfilter {
using namespace ::com::sun::star::i18n;

/*N*/ TYPEINIT2( SwCntntNode, SwModify, SwIndexReg )

/*******************************************************************
|*
|*  SwNode::GetSectionLevel
|*
|*  Beschreibung
|*      Die Funktion liefert den Sectionlevel an der durch
|*      aIndex bezeichneten Position.
|*
|*      Die Logik ist wie folgt:   ( S -> Start, E -> End, C -> CntntNode)
|*          Level   0       E
|*                  1   S  E
|*                  2    SC
|*
|*      alle EndNodes der GrundSection haben den Level 0
|*      alle StartNodes der GrundSection haben den Level 1
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Aenderung:  JP  11.08.93
|*      keine Rekursion mehr !!
|*
*******************************************************************/


//STRIP001 USHORT SwNode::GetSectionLevel() const
//STRIP001 {
//STRIP001  // EndNode einer Grund-Section ?? diese sind immer 0 !!
//STRIP001  if( IsEndNode() && 0 == pStartOfSection->StartOfSectionIndex() )
//STRIP001      return 0;
//STRIP001
//STRIP001  USHORT nLevel;
//STRIP001  const SwNode* pNode = IsStartNode() ? this : pStartOfSection;
//STRIP001  for( nLevel = 1; 0 != pNode->StartOfSectionIndex(); ++nLevel )
//STRIP001      pNode = pNode->pStartOfSection;
//STRIP001  return IsEndNode() ? nLevel-1 : nLevel;
//STRIP001 }

/*******************************************************************
|*
|*  SwNode::SwNode
|*
|*  Beschreibung
|*      Konstruktor; dieser fuegt einen Node in das Array rNodes
|*      an der Position rWhere ein. Dieser bekommt als
|*      theEndOfSection den EndOfSection-Index des Nodes
|*      unmittelbar vor ihm. Falls er sich an der Position 0
|*      innerhalb des variablen Arrays befindet, wird
|*      theEndOfSection 0 (der neue selbst).
|*
|*  Parameter
|*      IN
|*      rNodes bezeichnet das variable Array, in das der Node
|*      eingefuegt werden soll
|*      IN
|*      rWhere bezeichnet die Position innerhalb dieses Arrays,
|*      an der der Node eingefuegt werden soll
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/


/*N*/ SwNode::SwNode( const SwNodeIndex &rWhere, const BYTE nNdType )
/*N*/   : pStartOfSection( 0 ), nNodeType( nNdType )
/*N*/ {
/*N*/   bWrongDirty = bACmplWrdDirty = TRUE;
/*N*/   bSetNumLSpace = bIgnoreDontExpand = FALSE;
/*N*/   nAFmtNumLvl = 0;
/*N*/
/*N*/   SwNodes& rNodes = (SwNodes&)rWhere.GetNodes();
/*N*/   SwNode* pInsNd = this;      // der MAC kann this nicht einfuegen !!
/*N*/   if( rWhere.GetIndex() )
/*N*/   {
/*N*/       SwNode* pNd = rNodes[ rWhere.GetIndex() -1 ];
/*N*/       rNodes.Insert( pInsNd, rWhere );
/*N*/       if( 0 == ( pStartOfSection = pNd->GetStartNode()) )
/*N*/       {
/*N*/           pStartOfSection = pNd->pStartOfSection;
/*N*/           if( pNd->GetEndNode() )     // EndNode ? Section ueberspringen!
/*N*/           {
/*N*/               pNd = pStartOfSection;
/*N*/               pStartOfSection = pNd->pStartOfSection;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       rNodes.Insert( pInsNd, rWhere );
/*?*/       pStartOfSection = (SwStartNode*)this;
/*N*/   }
/*N*/ }

/*N*/ SwNode::SwNode( SwNodes& rNodes, ULONG nPos, const BYTE nNdType )
/*N*/   : pStartOfSection( 0 ), nNodeType( nNdType )
/*N*/ {
/*N*/   bWrongDirty = bACmplWrdDirty = TRUE;
/*N*/   bSetNumLSpace = bIgnoreDontExpand = FALSE;
/*N*/   nAFmtNumLvl = 0;
/*N*/
/*N*/   SwNode* pInsNd = this;      // der MAC kann this nicht einfuegen !!
/*N*/   if( nPos )
/*N*/   {
/*N*/       SwNode* pNd = rNodes[ nPos - 1 ];
/*N*/       rNodes.Insert( pInsNd, nPos );
/*N*/       if( 0 == ( pStartOfSection = pNd->GetStartNode()) )
/*N*/       {
/*N*/           pStartOfSection = pNd->pStartOfSection;
/*N*/           if( pNd->GetEndNode() )     // EndNode ? Section ueberspringen!
/*N*/           {
/*N*/               pNd = pStartOfSection;
/*N*/               pStartOfSection = pNd->pStartOfSection;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rNodes.Insert( pInsNd, nPos );
/*N*/       pStartOfSection = (SwStartNode*)this;
/*N*/   }
/*N*/ }

/*N*/ SwNode::~SwNode()
/*N*/ {
/*N*/ }

// suche den TabellenNode, in dem dieser steht. Wenn in keiner
// Tabelle wird 0 returnt.


/*N*/ SwTableNode* SwNode::FindTableNode()
/*N*/ {
/*N*/   if( IsTableNode() )
/*N*/       return GetTableNode();
/*N*/   SwStartNode* pTmp = pStartOfSection;
/*N*/   while( !pTmp->IsTableNode() && pTmp->GetIndex() )
/*N*/ #if defined( ALPHA ) && defined( UNX )
/*?*/       pTmp = ((SwNode*)pTmp)->pStartOfSection;
/*N*/ #else
/*N*/       pTmp = pTmp->pStartOfSection;
/*N*/ #endif
/*N*/   return pTmp->GetTableNode();
/*N*/ }


// liegt der Node im Sichtbarenbereich der Shell ?
//STRIP001 BOOL SwNode::IsVisible( ViewShell* pSh ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwCntntNode* pNd;
//STRIP001
//STRIP001  if( ND_STARTNODE & nNodeType )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *this );
//STRIP001      pNd = GetNodes().GoNext( &aIdx );
//STRIP001  }
//STRIP001  else if( ND_ENDNODE & nNodeType )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *EndOfSectionNode() );
//STRIP001      pNd = GetNodes().GoPrevious( &aIdx );
//STRIP001  }
//STRIP001  else
//STRIP001      pNd = GetCntntNode();
//STRIP001
//STRIP001  const SwFrm* pFrm;
//STRIP001  if( pNd && 0 != ( pFrm = pNd->GetFrm( 0, 0, FALSE ) ) )
//STRIP001  {
//STRIP001      if( !pSh )
//STRIP001          // dann die Shell vom Doc besorgen:
//STRIP001          GetDoc()->GetEditShell( &pSh );
//STRIP001
//STRIP001      if( pSh )
//STRIP001      {
//STRIP001          if ( pFrm->IsInTab() )
//STRIP001              pFrm = pFrm->FindTabFrm();
//STRIP001
//STRIP001          if( !pFrm->IsValid() )
//STRIP001              do
//STRIP001              {   pFrm = pFrm->FindPrev();
//STRIP001              } while ( pFrm && !pFrm->IsValid() );
//STRIP001
//STRIP001          if( !pFrm || pSh->VisArea().IsOver( pFrm->Frm() ) )
//STRIP001              bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL SwNode::IsInProtectSect() const
/*N*/ {
/*N*/   const SwNode* pNd = ND_SECTIONNODE == nNodeType ? pStartOfSection : this;
/*N*/   const SwSectionNode* pSectNd = pNd->FindSectionNode();
/*N*/   return pSectNd && pSectNd->GetSection().IsProtectFlag();
/*N*/ }

    // befindet sich der Node in irgendetwas geschuetzten ?
    // (Bereich/Rahmen/Tabellenzellen/... incl. des Ankers bei
    //  Rahmen/Fussnoten/..)
/*N*/ BOOL SwNode::IsProtect() const
/*N*/ {
/*N*/   const SwNode* pNd = ND_SECTIONNODE == nNodeType ? pStartOfSection : this;
/*N*/   const SwStartNode* pSttNd = pNd->FindSectionNode();
/*N*/   if( pSttNd && ((SwSectionNode*)pSttNd)->GetSection().IsProtectFlag() )
/*N*/       return TRUE;
/*N*/
/*N*/   if( 0 != ( pSttNd = FindTableBoxStartNode() ) )
/*N*/   {
/*N*/       SwCntntFrm* pCFrm;
/*N*/       if( IsCntntNode() && 0 != (pCFrm = ((SwCntntNode*)this)->GetFrm() ))
/*N*/           return pCFrm->IsProtected();
/*N*/
/*N*/       const SwTableBox* pBox = pSttNd->FindTableNode()->GetTable().
/*N*/                                       GetTblBox( pSttNd->GetIndex() );
/*N*/       if( pBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
/*?*/           return TRUE;
/*N*/   }
/*N*/
/*N*/   SwFrmFmt* pFlyFmt = GetFlyFmt();
/*N*/   if( pFlyFmt )
/*N*/   {
/*N*/       if( pFlyFmt->GetProtect().IsCntntProtected() )
/*?*/           return TRUE;
/*N*/       const SwFmtAnchor& rAnchor = pFlyFmt->GetAnchor();
/*N*/       return rAnchor.GetCntntAnchor()
/*N*/               ? rAnchor.GetCntntAnchor()->nNode.GetNode().IsProtect()
/*N*/               : FALSE;
/*N*/   }
/*N*/
/*N*/   if( 0 != ( pSttNd = FindFootnoteStartNode() ) )
/*N*/   {
/*?*/       const SwTxtFtn* pTFtn = GetDoc()->GetFtnIdxs().SeekEntry(
/*?*/                               SwNodeIndex( *pSttNd ) );
/*?*/       if( pTFtn )
/*?*/           return pTFtn->GetTxtNode().IsProtect();
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

    // suche den PageDesc, mit dem dieser Node formatiert ist. Wenn das
    // Layout vorhanden ist wird ueber das gesucht, ansonsten gibt es nur
    // die harte Tour ueber die Nodes nach vorne suchen!!
//STRIP001 const SwPageDesc* SwNode::FindPageDesc( BOOL bCalcLay,
//STRIP001                                         sal_uInt32* pPgDescNdIdx ) const
//STRIP001 {
//STRIP001     // OD 18.03.2003 #106329#
//STRIP001     if ( !GetNodes().IsDocNodes() )
//STRIP001     {
//STRIP001         return 0;
//STRIP001     }
//STRIP001
//STRIP001     const SwPageDesc* pPgDesc = 0;
//STRIP001
//STRIP001     const SwCntntNode* pNd;
//STRIP001     if( ND_STARTNODE & nNodeType )
//STRIP001     {
//STRIP001         SwNodeIndex aIdx( *this );
//STRIP001         pNd = GetNodes().GoNext( &aIdx );
//STRIP001     }
//STRIP001     else if( ND_ENDNODE & nNodeType )
//STRIP001     {
//STRIP001         SwNodeIndex aIdx( *EndOfSectionNode() );
//STRIP001         pNd = GetNodes().GoPrevious( &aIdx );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pNd = GetCntntNode();
//STRIP001         if( pNd )
//STRIP001             pPgDesc = ((SwFmtPageDesc&)pNd->GetAttr( RES_PAGEDESC )).GetPageDesc();
//STRIP001     }
//STRIP001
//STRIP001     // geht es uebers Layout?
//STRIP001     if( !pPgDesc )
//STRIP001     {
//STRIP001         const SwFrm* pFrm;
//STRIP001         const SwPageFrm* pPage;
//STRIP001         if( pNd && 0 != ( pFrm = pNd->GetFrm( 0, 0, bCalcLay ) ) &&
//STRIP001             0 != ( pPage = pFrm->FindPageFrm() ) )
//STRIP001         {
//STRIP001             pPgDesc = pPage->GetPageDesc();
//STRIP001             // OD 18.03.2003 #106329#
//STRIP001             if ( pPgDescNdIdx )
//STRIP001             {
//STRIP001                 *pPgDescNdIdx = pNd->GetIndex();
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if( !pPgDesc )
//STRIP001     {
//STRIP001         // dann also uebers Nodes-Array
//STRIP001         const SwDoc* pDoc = GetDoc();
//STRIP001         const SwNode* pNd = this;
//STRIP001         const SwStartNode* pSttNd;
//STRIP001         if( pNd->GetIndex() < GetNodes().GetEndOfExtras().GetIndex() &&
//STRIP001             0 != ( pSttNd = pNd->FindFlyStartNode() ) )
//STRIP001         {
//STRIP001             // dann erstmal den richtigen Anker finden
//STRIP001             const SwFrmFmt* pFmt = 0;
//STRIP001             const SwSpzFrmFmts& rFmts = *pDoc->GetSpzFrmFmts();
//STRIP001             for( USHORT n = 0; n < rFmts.Count(); ++n )
//STRIP001             {
//STRIP001                 SwFrmFmt* pFrmFmt = rFmts[ n ];
//STRIP001                 const SwFmtCntnt& rCntnt = pFrmFmt->GetCntnt();
//STRIP001                 if( rCntnt.GetCntntIdx() &&
//STRIP001                     &rCntnt.GetCntntIdx()->GetNode() == (SwNode*)pSttNd )
//STRIP001                 {
//STRIP001                     pFmt = pFrmFmt;
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             if( pFmt )
//STRIP001             {
//STRIP001                 const SwFmtAnchor* pAnchor = &pFmt->GetAnchor();
//STRIP001                 if( FLY_PAGE != pAnchor->GetAnchorId() &&
//STRIP001                     pAnchor->GetCntntAnchor() )
//STRIP001                 {
//STRIP001                     pNd = &pAnchor->GetCntntAnchor()->nNode.GetNode();
//STRIP001                     const SwNode* pFlyNd = pNd->FindFlyStartNode();
//STRIP001                     while( pFlyNd )
//STRIP001                     {
//STRIP001                         // dann ueber den Anker nach oben "hangeln"
//STRIP001                         for( n = 0; n < rFmts.Count(); ++n )
//STRIP001                         {
//STRIP001                             const SwFrmFmt* pFrmFmt = rFmts[ n ];
//STRIP001                             const SwNodeIndex* pIdx = pFrmFmt->GetCntnt().
//STRIP001                                                         GetCntntIdx();
//STRIP001                             if( pIdx && pFlyNd == &pIdx->GetNode() )
//STRIP001                             {
//STRIP001                                 if( pFmt == pFrmFmt )
//STRIP001                                 {
//STRIP001                                     pNd = pFlyNd;
//STRIP001                                     pFlyNd = 0;
//STRIP001                                     break;
//STRIP001                                 }
//STRIP001                                 pAnchor = &pFrmFmt->GetAnchor();
//STRIP001                                 if( FLY_PAGE == pAnchor->GetAnchorId() ||
//STRIP001                                     !pAnchor->GetCntntAnchor() )
//STRIP001                                 {
//STRIP001                                     pFlyNd = 0;
//STRIP001                                     break;
//STRIP001                                 }
//STRIP001
//STRIP001                                 pFlyNd = pAnchor->GetCntntAnchor()->nNode.
//STRIP001                                         GetNode().FindFlyStartNode();
//STRIP001                                 break;
//STRIP001                             }
//STRIP001                         }
//STRIP001                         if( n >= rFmts.Count() )
//STRIP001                         {
//STRIP001                             ASSERT( !this, "Fly-Section aber kein Format gefunden" );
//STRIP001                             return FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             // in pNd sollte jetzt der richtige Anker Node stehen oder
//STRIP001             // immer noch der this
//STRIP001         }
//STRIP001
//STRIP001         if( pNd->GetIndex() < GetNodes().GetEndOfExtras().GetIndex() )
//STRIP001         {
//STRIP001             if( pNd->GetIndex() > GetNodes().GetEndOfAutotext().GetIndex() )
//STRIP001             {
//STRIP001                 pPgDesc = &pDoc->GetPageDesc( 0 );
//STRIP001                 pNd = 0;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // suche den Body Textnode
//STRIP001                 if( 0 != ( pSttNd = pNd->FindHeaderStartNode() ) ||
//STRIP001                     0 != ( pSttNd = pNd->FindFooterStartNode() ))
//STRIP001                 {
//STRIP001                     // dann in den PageDescs diesen StartNode suchen
//STRIP001                     USHORT nId;
//STRIP001                     UseOnPage eAskUse;
//STRIP001                     if( SwHeaderStartNode == pSttNd->GetStartNodeType())
//STRIP001                     {
//STRIP001                         nId = RES_HEADER;
//STRIP001                         eAskUse = PD_HEADERSHARE;
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         nId = RES_FOOTER;
//STRIP001                         eAskUse = PD_FOOTERSHARE;
//STRIP001                     }
//STRIP001
//STRIP001                     for( USHORT n = pDoc->GetPageDescCnt(); n && !pPgDesc; )
//STRIP001                     {
//STRIP001                         const SwPageDesc& rPgDsc = pDoc->GetPageDesc( --n );
//STRIP001                         const SwFrmFmt* pFmt = &rPgDsc.GetMaster();
//STRIP001                         int nStt = 0, nLast = 1;
//STRIP001                         if( !( eAskUse & rPgDsc.ReadUseOn() )) ++nLast;
//STRIP001
//STRIP001                         for( ; nStt < nLast; ++nStt, pFmt = &rPgDsc.GetLeft() )
//STRIP001                         {
//STRIP001                             const SwFmtHeader& rHdFt = (SwFmtHeader&)
//STRIP001                                                     pFmt->GetAttr( nId );
//STRIP001                             if( rHdFt.GetHeaderFmt() )
//STRIP001                             {
//STRIP001                                 const SwFmtCntnt& rCntnt =
//STRIP001                                     rHdFt.GetHeaderFmt()->GetCntnt();
//STRIP001                                 if( rCntnt.GetCntntIdx() &&
//STRIP001                                     &rCntnt.GetCntntIdx()->GetNode() ==
//STRIP001                                     (SwNode*)pSttNd )
//STRIP001                                 {
//STRIP001                                     pPgDesc = &rPgDsc;
//STRIP001                                     break;
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001
//STRIP001                     if( !pPgDesc )
//STRIP001                         pPgDesc = &pDoc->GetPageDesc( 0 );
//STRIP001                     pNd = 0;
//STRIP001                 }
//STRIP001                 else if( 0 != ( pSttNd = pNd->FindFootnoteStartNode() ))
//STRIP001                 {
//STRIP001                     // der Anker kann nur im Bodytext sein
//STRIP001                     const SwTxtFtn* pTxtFtn;
//STRIP001                     const SwFtnIdxs& rFtnArr = pDoc->GetFtnIdxs();
//STRIP001                     for( USHORT n = 0; n < rFtnArr.Count(); ++n )
//STRIP001                         if( 0 != ( pTxtFtn = rFtnArr[ n ])->GetStartNode() &&
//STRIP001                             (SwNode*)pSttNd ==
//STRIP001                             &pTxtFtn->GetStartNode()->GetNode() )
//STRIP001                         {
//STRIP001                             pNd = &pTxtFtn->GetTxtNode();
//STRIP001                             break;
//STRIP001                         }
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     // kann jetzt nur noch ein Seitengebundener Fly sein
//STRIP001                     // oder irgendetwas neueres.
//STRIP001                     // Hier koennen wir nur noch den Standard returnen
//STRIP001                     ASSERT( pNd->FindFlyStartNode(),
//STRIP001                             "wo befindet sich dieser Node?" );
//STRIP001
//STRIP001                     pPgDesc = &pDoc->GetPageDesc( 0 );
//STRIP001                     pNd = 0;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         if( pNd )
//STRIP001         {
//STRIP001             SwFindNearestNode aInfo( *pNd );
//STRIP001             // dann ueber alle Nodes aller PageDesc
//STRIP001             const SfxPoolItem* pItem;
//STRIP001             USHORT i, nMaxItems = pDoc->GetAttrPool().GetItemCount( RES_PAGEDESC );
//STRIP001             for( i = 0; i < nMaxItems; ++i )
//STRIP001                 if( 0 != (pItem = pDoc->GetAttrPool().GetItem( RES_PAGEDESC, i ) ) &&
//STRIP001                     ((SwFmtPageDesc*)pItem)->GetDefinedIn() )
//STRIP001                 {
//STRIP001                     const SwModify* pMod = ((SwFmtPageDesc*)pItem)->GetDefinedIn();
//STRIP001                     if( pMod->ISA( SwCntntNode ) )
//STRIP001                         aInfo.CheckNode( *(SwCntntNode*)pMod );
//STRIP001                     else if( pMod->ISA( SwFmt ))
//STRIP001                         ((SwFmt*)pMod)->GetInfo( aInfo );
//STRIP001                 }
//STRIP001
//STRIP001             if( 0 != ( pNd = aInfo.GetFoundNode() ))
//STRIP001             {
//STRIP001                 if( pNd->IsCntntNode() )
//STRIP001                     pPgDesc = ((SwFmtPageDesc&)pNd->GetCntntNode()->
//STRIP001                                 GetAttr( RES_PAGEDESC )).GetPageDesc();
//STRIP001                 else if( pNd->IsTableNode() )
//STRIP001                     pPgDesc = pNd->GetTableNode()->GetTable().
//STRIP001                             GetFrmFmt()->GetPageDesc().GetPageDesc();
//STRIP001                 else if( pNd->IsSectionNode() )
//STRIP001                     pPgDesc = pNd->GetSectionNode()->GetSection().
//STRIP001                             GetFmt()->GetPageDesc().GetPageDesc();
//STRIP001                 // OD 18.03.2003 #106329#
//STRIP001                 if ( pPgDescNdIdx )
//STRIP001                 {
//STRIP001                     *pPgDescNdIdx = pNd->GetIndex();
//STRIP001                 }
//STRIP001             }
//STRIP001             if( !pPgDesc )
//STRIP001                 pPgDesc = &pDoc->GetPageDesc( 0 );
//STRIP001         }
//STRIP001     }
//STRIP001  return pPgDesc;
//STRIP001 }


    // falls der Node in einem Fly steht, dann wird das entsprechende Format
    // returnt
/*N*/ SwFrmFmt* SwNode::GetFlyFmt() const
/*N*/ {
/*N*/   SwFrmFmt* pRet = 0;
/*N*/   const SwNode* pSttNd = FindFlyStartNode();
/*N*/   if( pSttNd )
/*N*/   {
/*N*/       if( IsCntntNode() )
/*N*/       {
/*N*/           SwClientIter aIter( *(SwCntntNode*)this );
/*N*/           SwClient* pCli = aIter.First( TYPE( SwCntntFrm ));
/*N*/           if( pCli )
/*N*/               pRet = ((SwCntntFrm*)pCli)->FindFlyFrm()->GetFmt();
/*N*/       }
/*N*/       if( !pRet )
/*N*/       {
/*N*/           // dann gibts noch harten steinigen Weg uebers Dokument:
/*N*/           const SwSpzFrmFmts& rFrmFmtTbl = *GetDoc()->GetSpzFrmFmts();
/*N*/           for( USHORT n = 0; n < rFrmFmtTbl.Count(); ++n )
/*N*/           {
/*N*/               SwFrmFmt* pFmt = rFrmFmtTbl[n];
/*N*/               const SwFmtCntnt& rCntnt = pFmt->GetCntnt();
/*N*/               if( rCntnt.GetCntntIdx() &&
/*N*/                   &rCntnt.GetCntntIdx()->GetNode() == pSttNd )
/*N*/               {
/*N*/                   pRet = pFmt;
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return pRet;
/*N*/ }

//STRIP001 const SwFrmFmt* SwNode::GetFrmFmt() const
//STRIP001 {
//STRIP001  const SwFrmFmt* pRet = 0;
//STRIP001  const SwNode* pNd = FindStartNode();
//STRIP001  ASSERT( pNd, "SwNode::GetFrmFmt(): Missing StartNode" );
//STRIP001  if( pNd->IsSectionNode() )
//STRIP001      pRet = ((SwSectionNode*)pNd)->GetSection().GetFmt();
//STRIP001  else if( pNd->IsTableNode() )
//STRIP001      pRet = ((SwTableNode*)pNd)->GetTable().GetFrmFmt();
//STRIP001  else switch( ((SwStartNode*)pNd)->GetStartNodeType() )
//STRIP001  {
//STRIP001      case SwNormalStartNode: break;
//STRIP001      case SwTableBoxStartNode: pRet = pNd->FindTableNode()->GetTable().GetTblBox(
//STRIP001                                       pNd->GetIndex() )->GetFrmFmt(); break;
//STRIP001      case SwFlyStartNode: pRet = GetFlyFmt(); break;
//STRIP001      case SwFootnoteStartNode: pRet = GetDoc()->GetDfltFrmFmt(); break;
//STRIP001      case SwHeaderStartNode: break;
//STRIP001      case SwFooterStartNode: break;
//STRIP001      default: ASSERT( FALSE, "GetFrmFmt(): New StartNodeType?" );
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

/*N*/ SwTableBox* SwNode::GetTblBox() const
/*N*/ {
/*N*/   SwTableBox* pBox = 0;
/*N*/   const SwNode* pSttNd = FindTableBoxStartNode();
/*N*/   if( pSttNd )
/*N*/       pBox = (SwTableBox*)pSttNd->FindTableNode()->GetTable().GetTblBox(
/*N*/                                                   pSttNd->GetIndex() );
/*N*/   return pBox;
/*N*/ }

/*N*/ SwStartNode* SwNode::FindSttNodeByType( SwStartNodeType eTyp )
/*N*/ {
/*N*/   SwStartNode* pTmp = IsStartNode() ? (SwStartNode*)this : pStartOfSection;
/*N*/
/*N*/   while( eTyp != pTmp->GetStartNodeType() && pTmp->GetIndex() )
/*N*/ #if defined( ALPHA ) && defined( UNX )
/*?*/       pTmp = ((SwNode*)pTmp)->pStartOfSection;
/*N*/ #else
/*N*/       pTmp = pTmp->pStartOfSection;
/*N*/ #endif
/*N*/   return eTyp == pTmp->GetStartNodeType() ? pTmp : 0;
/*N*/ }

/*N*/ const SwTxtNode* SwNode::FindOutlineNodeOfLevel( BYTE nLvl ) const
/*N*/ {
/*N*/   const SwTxtNode* pRet = 0;
/*N*/   const SwOutlineNodes& rONds = GetNodes().GetOutLineNds();
/*N*/   if( MAXLEVEL > nLvl && rONds.Count() )
/*N*/   {
/*N*/       USHORT nPos;
/*N*/       SwNode* pNd = (SwNode*)this;
/*N*/       BOOL bCheckFirst = FALSE;
/*N*/       if( !rONds.Seek_Entry( pNd, &nPos ))
/*N*/       {
/*N*/           if( nPos )
/*N*/               nPos = nPos-1;
/*N*/           else
/*?*/               bCheckFirst = TRUE;
/*N*/       }
/*N*/
/*N*/       if( bCheckFirst )
/*N*/       {
/*?*/           // der 1.GliederungsNode liegt hinter dem Fragenden. Dann
/*?*/           // teste mal, ob dieser auf der gleichen Seite steht. Wenn
/*?*/           // nicht, ist das ein ungueltiger. Bug 61865
/*?*/           pRet = rONds[0]->GetTxtNode();
/*?*/
/*?*/           const SwCntntNode* pCNd = GetCntntNode();
/*?*/
/*?*/           Point aPt( 0, 0 );
/*?*/           const SwFrm* pFrm = pRet->GetFrm( &aPt, 0, FALSE ),
/*?*/                      * pMyFrm = pCNd ? pCNd->GetFrm( &aPt, 0, FALSE ) : 0;
/*?*/           const SwPageFrm* pPgFrm = pFrm ? pFrm->FindPageFrm() : 0;
/*?*/           if( pPgFrm && pMyFrm &&
/*?*/               pPgFrm->Frm().Top() > pMyFrm->Frm().Top() )
/*?*/           {
/*?*/               // der Fragende liegt vor der Seite, also ist er ungueltig
/*?*/               pRet = 0;
/*?*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // oder ans Feld und von dort holen !!
/*N*/           while( nPos && nLvl < ( pRet = rONds[nPos]->GetTxtNode() )
/*N*/                   ->GetTxtColl()->GetOutlineLevel() )
/*N*/               --nPos;
/*N*/
/*N*/           if( !nPos )     // bei 0 gesondert holen !!
/*N*/               pRet = rONds[0]->GetTxtNode();
/*N*/       }
/*N*/   }
/*N*/   return pRet;
/*N*/ }

// is the node the first and/or last node of a section?
// This information is used for the export filters. Our layout never have a
// distance before or after if the node is the first or last in a section.

//STRIP001 inline IsValidNextPrevNd( const SwNode& rNd )
//STRIP001 {
//STRIP001  return ND_TABLENODE == rNd.GetNodeType() ||
//STRIP001         ( ND_CONTENTNODE & rNd.GetNodeType() ) ||
//STRIP001          ( ND_ENDNODE == rNd.GetNodeType() && rNd.StartOfSectionNode() &&
//STRIP001          ND_TABLENODE == rNd.StartOfSectionNode()->GetNodeType() );
//STRIP001 }

//STRIP001 BYTE SwNode::HasPrevNextLayNode() const
//STRIP001 {
//STRIP001  BYTE nRet = 0;
//STRIP001  if( IsValidNextPrevNd( *this ))
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *this, -1 );
//STRIP001      if( IsValidNextPrevNd( aIdx.GetNode() ))
//STRIP001          nRet |= ND_HAS_PREV_LAYNODE;
//STRIP001      aIdx += 2;
//STRIP001      if( IsValidNextPrevNd( aIdx.GetNode() ))
//STRIP001          nRet |= ND_HAS_NEXT_LAYNODE;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/*******************************************************************
|*
|*  SwNode::StartOfSection
|*
|*  Beschreibung
|*      Die Funktion liefert die StartOfSection des Nodes.
|*
|*  Parameter
|*      IN
|*      rNodes bezeichnet das variable Array, in dem sich der Node
|*      befindet
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/


/*N*/ SwStartNode::SwStartNode( const SwNodeIndex &rWhere, const BYTE nNdType,
/*N*/                           SwStartNodeType eSttNd )
/*N*/   : SwNode( rWhere, nNdType ), eSttNdTyp( eSttNd )
/*N*/ {
/*N*/   // erstmal temporaer, bis der EndNode eingefuegt wird.
/*N*/   pEndOfSection = (SwEndNode*)this;
/*N*/ }

/*N*/ SwStartNode::SwStartNode( SwNodes& rNodes, ULONG nPos )
/*N*/   : SwNode( rNodes, nPos, ND_STARTNODE ), eSttNdTyp( SwNormalStartNode )
/*N*/ {
/*N*/   // erstmal temporaer, bis der EndNode eingefuegt wird.
/*N*/   pEndOfSection = (SwEndNode*)this;
/*N*/ }


/*N*/ void SwStartNode::CheckSectionCondColl() const
/*N*/ {
/*N*/ //FEATURE::CONDCOLL
/*N*/   SwNodeIndex aIdx( *this );
/*N*/   ULONG nEndIdx = EndOfSectionIndex();
/*N*/   const SwNodes& rNds = GetNodes();
/*N*/   SwCntntNode* pCNd;
/*N*/   while( 0 != ( pCNd = rNds.GoNext( &aIdx )) && pCNd->GetIndex() < nEndIdx )
/*N*/       pCNd->ChkCondColl();
/*N*/ //FEATURE::CONDCOLL
/*N*/ }

/*******************************************************************
|*
|*  SwEndNode::SwEndNode
|*
|*  Beschreibung
|*      Konstruktor; dieser fuegt einen Node in das Array rNodes
|*      an der Position aWhere ein. Der
|*      theStartOfSection-Pointer wird entsprechend gesetzt,
|*      und der EndOfSection-Pointer des zugehoerigen
|*      Startnodes -- durch rStartOfSection bezeichnet --
|*      wird auf diesen Node gesetzt.
|*
|*  Parameter
|*      IN
|*      rNodes bezeichnet das variable Array, in das der Node
|*      eingefuegt werden soll
|*      IN
|*      aWhere bezeichnet die Position innerhalb dieses Arrays,
|*      an der der Node eingefuegt werden soll
|*      !!!!!!!!!!!!
|*      Es wird eine Kopie uebergeben!
|*
|*  Ersterstellung
|*      VER0100 vb 901214
|*
|*  Stand
|*      VER0100 vb 901214
|*
*******************************************************************/


/*N*/ SwEndNode::SwEndNode( const SwNodeIndex &rWhere, SwStartNode& rSttNd )
/*N*/   : SwNode( rWhere, ND_ENDNODE )
/*N*/ {
/*N*/   pStartOfSection = &rSttNd;
/*N*/   pStartOfSection->pEndOfSection = this;
/*N*/ }

/*N*/ SwEndNode::SwEndNode( SwNodes& rNds, ULONG nPos, SwStartNode& rSttNd )
/*N*/   : SwNode( rNds, nPos, ND_ENDNODE )
/*N*/ {
/*N*/   pStartOfSection = &rSttNd;
/*N*/   pStartOfSection->pEndOfSection = this;
/*N*/ }



// --------------------
// SwCntntNode
// --------------------


/*N*/ SwCntntNode::SwCntntNode( const SwNodeIndex &rWhere, const BYTE nNdType,
/*N*/                           SwFmtColl *pColl )
/*N*/   : SwNode( rWhere, nNdType ),
/*N*/   pAttrSet( 0 ),
/*N*/   pCondColl( 0 ),
/*N*/   SwModify( pColl )    // CrsrsShell, FrameFmt
/*N*/ #ifdef OLD_INDEX
/*N*/   ,SwIndexReg(2)
/*N*/ #endif
/*N*/ {
/*N*/ }


/*N*/ SwCntntNode::~SwCntntNode()
/*N*/ {
/*N*/   // Die Basisklasse SwClient vom SwFrm nimmt sich aus
/*N*/   // der Abhaengikeitsliste raus!
/*N*/   // Daher muessen alle Frames in der Abhaengigkeitsliste geloescht werden.
/*N*/   if( GetDepends() )
/*N*/       DelFrms();
/*N*/
/*N*/   if( pAttrSet )
/*N*/       delete pAttrSet;
/*N*/   if( pCondColl )
/*?*/       delete pCondColl;
/*N*/ }


/*N*/ void SwCntntNode::Modify( SfxPoolItem* pOldValue, SfxPoolItem* pNewValue )
/*N*/ {
/*N*/   USHORT nWhich = pOldValue ? pOldValue->Which() :
/*N*/                   pNewValue ? pNewValue->Which() : 0 ;
/*N*/   BOOL bNumRuleSet = FALSE, bCallModify = TRUE;
/*N*/   String sNumRule, sOldNumRule;
/*N*/   const SfxPoolItem* pItem;
/*N*/
/*N*/   switch( nWhich )
/*N*/   {
/*N*/   case RES_OBJECTDYING :
/*N*/       {
/*?*/           SwFmt * pFmt = (SwFmt *) ((SwPtrMsgPoolItem *)pNewValue)->pObject;
/*?*/
/*?*/           // nicht umhaengen wenn dieses das oberste Format ist !!
/*?*/           if( pRegisteredIn == pFmt )
/*?*/           {
/*?*/               if( pFmt->GetRegisteredIn() )
/*?*/               {
/*?*/                   // wenn Parent, dann im neuen Parent wieder anmelden
/*?*/                   ((SwModify*)pFmt->GetRegisteredIn())->Add( this );
/*?*/                   if ( pAttrSet )
/*?*/                       pAttrSet->SetParent(
/*?*/                               &((SwFmt*)GetRegisteredIn())->GetAttrSet() );
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   // sonst auf jeden Fall beim sterbenden abmelden
/*?*/                   ((SwModify*)GetRegisteredIn())->Remove( this );
/*?*/                   if ( pAttrSet )
/*?*/                       pAttrSet->SetParent( 0 );
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/       break;
/*N*/
/*N*/
/*N*/   case RES_FMT_CHG:
/*N*/       // falls mein Format Parent umgesetzt wird, dann melde ich
/*N*/       // meinen Attrset beim Neuen an.
/*N*/
/*N*/       // sein eigenes Modify ueberspringen !!
/*N*/       if( pAttrSet &&
/*N*/           ((SwFmtChg*)pNewValue)->pChangedFmt == GetRegisteredIn() )
/*N*/       {
/*N*/           // den Set an den neuen Parent haengen
/*N*/           pAttrSet->SetParent( GetRegisteredIn() ?
/*N*/               &((SwFmt*)GetRegisteredIn())->GetAttrSet() : 0 );
/*N*/       }
/*N*/       if( GetNodes().IsDocNodes() && IsTxtNode() )
/*N*/       {
/*N*/           if( 0 != ( pItem = GetNoCondAttr( RES_PARATR_NUMRULE, TRUE )))
/*N*/           {
/*?*/               bNumRuleSet = TRUE;
/*?*/               sNumRule = ((SwNumRuleItem*)pItem)->GetValue();
/*N*/           }
/*N*/           sOldNumRule = ((SwFmtChg*)pOldValue)->pChangedFmt->GetNumRule().GetValue();
/*N*/       }
/*N*/       break;
/*N*/ //FEATURE::CONDCOLL
/*N*/   case RES_CONDCOLL_CONDCHG:
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( ((SwCondCollCondChg*)pNewValue)->pChangedFmt == GetRegisteredIn() &&
//STRIP001 /*?*/            &GetNodes() == &GetDoc()->GetNodes() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ChkCondColl();
//STRIP001 /*?*/        }
/*?*/       return ;    // nicht an die Basisklasse / Frames weitergeben
/*N*/ //FEATURE::CONDCOLL
/*N*/
/*N*/   case RES_ATTRSET_CHG:
/*N*/       if( GetNodes().IsDocNodes() && IsTxtNode() )
/*N*/       {
/*N*/           if( SFX_ITEM_SET == ((SwAttrSetChg*)pNewValue)->GetChgSet()->GetItemState(
/*N*/               RES_PARATR_NUMRULE, FALSE, &pItem ))
/*N*/           {
/*N*/               bNumRuleSet = TRUE;
/*N*/               sNumRule = ((SwNumRuleItem*)pItem)->GetValue();
/*N*/           }
/*N*/           if( SFX_ITEM_SET == ((SwAttrSetChg*)pOldValue)->GetChgSet()->GetItemState(
/*N*/               RES_PARATR_NUMRULE, FALSE, &pItem ))
/*N*/               sOldNumRule = ((SwNumRuleItem*)pItem)->GetValue();
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case RES_PARATR_NUMRULE:
/*?*/       if( GetNodes().IsDocNodes() && IsTxtNode() )
/*?*/       {
/*?*/           if( pNewValue )
/*?*/           {
/*?*/               bNumRuleSet = TRUE;
/*?*/               sNumRule = ((SwNumRuleItem*)pNewValue)->GetValue();
/*?*/           }
/*?*/           if( pOldValue )
/*?*/               sOldNumRule = ((SwNumRuleItem*)pOldValue)->GetValue();
/*?*/       }
/*?*/       break;
/*?*/   }
/*N*/
/*N*/   if( bNumRuleSet )
/*N*/   {
/*N*/       if( sNumRule.Len() )
/*N*/       {
/*N*/           if( !((SwTxtNode*)this)->GetNum() )
/*N*/               ((SwTxtNode*)this)->UpdateNum( SwNodeNum(0) );
/*N*/ #ifndef NUM_RELSPACE
/*N*/           SetNumLSpace( TRUE );
/*N*/ #endif
/*N*/           SwNumRule* pRule = GetDoc()->FindNumRulePtr( sNumRule );
/*N*/           if( !pRule )
/*N*/           {
/*?*/               USHORT nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( sNumRule, GET_POOLID_NUMRULE );
/*?*/               if( USHRT_MAX != nPoolId )
/*?*/                   pRule = GetDoc()->GetNumRuleFromPool( nPoolId );
/*N*/           }
/*N*/           if( pRule )
/*N*/               pRule->SetInvalidRule( TRUE );
/*N*/       }
/*N*/       else if( ((SwTxtNode*)this)->GetNum() )
/*N*/       {
/*?*/           bCallModify = FALSE;
/*?*/           SwModify::Modify( pOldValue, pNewValue );
/*?*/           ((SwTxtNode*)this)->UpdateNum( SwNodeNum(NO_NUMBERING) );
/*?*/ #ifndef NUM_RELSPACE
/*?*/           SetNumLSpace( TRUE );
/*?*/ #endif
/*N*/       }
/*N*/   }
/*N*/   if( sOldNumRule.Len() && sNumRule != sOldNumRule )
/*N*/   {
/*?*/       SwNumRule* pRule = GetDoc()->FindNumRulePtr( sOldNumRule );
/*?*/       if( pRule )
/*?*/           pRule->SetInvalidRule( TRUE );
/*N*/   }
/*N*/
/*N*/   if( bCallModify )
/*N*/       SwModify::Modify( pOldValue, pNewValue );
/*N*/ }

/*N*/ BOOL SwCntntNode::InvalidateNumRule()
/*N*/ {
/*N*/   SwNumRule* pRule = 0;
/*N*/   const SfxPoolItem* pItem;
/*N*/   if( GetNodes().IsDocNodes() &&
/*N*/       0 != ( pItem = GetNoCondAttr( RES_PARATR_NUMRULE, TRUE )) &&
/*N*/       ((SwNumRuleItem*)pItem)->GetValue().Len() &&
/*N*/       0 != (pRule = GetDoc()->FindNumRulePtr(
/*N*/                               ((SwNumRuleItem*)pItem)->GetValue() ) ) )
/*N*/   {
/*N*/       pRule->SetInvalidRule( TRUE );
/*N*/   }
/*N*/   return 0 != pRule;
/*N*/ }


/*N*/ SwCntntFrm *SwCntntNode::GetFrm( const Point* pPoint,
/*N*/                               const SwPosition *pPos,
/*N*/                               const BOOL bCalcFrm ) const
/*N*/ {
/*N*/   return (SwCntntFrm*) ::binfilter::GetFrmOfModify( *(SwModify*)this, FRM_CNTNT,
/*N*/                                           pPoint, pPos, bCalcFrm );
/*N*/ }

//STRIP001 SwRect SwCntntNode::FindLayoutRect( const BOOL bPrtArea, const Point* pPoint,
//STRIP001                                  const BOOL bCalcFrm ) const
//STRIP001 {
//STRIP001  SwRect aRet;
//STRIP001  SwCntntFrm* pFrm = (SwCntntFrm*)::GetFrmOfModify( *(SwModify*)this,
//STRIP001                                          FRM_CNTNT, pPoint, 0, bCalcFrm );
//STRIP001  if( pFrm )
//STRIP001      aRet = bPrtArea ? pFrm->Prt() : pFrm->Frm();
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 SwRect SwCntntNode::FindPageFrmRect( const BOOL bPrtArea, const Point* pPoint,
//STRIP001                                  const BOOL bCalcFrm ) const
//STRIP001 {
//STRIP001  SwRect aRet;
//STRIP001  SwFrm* pFrm = ::GetFrmOfModify( *(SwModify*)this,
//STRIP001                                          FRM_CNTNT, pPoint, 0, bCalcFrm );
//STRIP001  if( pFrm && 0 != ( pFrm = pFrm->FindPageFrm() ))
//STRIP001      aRet = bPrtArea ? pFrm->Prt() : pFrm->Frm();
//STRIP001  return aRet;
//STRIP001 }

/*N*/ xub_StrLen SwCntntNode::Len() const { return 0; }



/*N*/ SwFmtColl *SwCntntNode::ChgFmtColl( SwFmtColl *pNewColl )
/*N*/ {
/*N*/   ASSERT( pNewColl, Collectionpointer ist 0. );
/*N*/   SwFmtColl *pOldColl = GetFmtColl();
/*N*/   if( pNewColl != pOldColl )
/*N*/   {
/*N*/       pNewColl->Add( this );
/*N*/
/*N*/       // setze den Parent von unseren Auto-Attributen auf die neue
/*N*/       // Collection:
/*N*/       if( pAttrSet )
/*?*/           pAttrSet->SetParent( &pNewColl->GetAttrSet() );
/*N*/
/*N*/ //FEATURE::CONDCOLL
/*N*/       // HACK: hier muss die entsprechend der neuen Vorlage die Bedingungen
/*N*/       //      neu ueberprueft werden!
/*N*/       if( TRUE /*pNewColl */ )
/*N*/       {
/*N*/           SetCondFmtColl( 0 );
/*N*/       }
/*N*/ //FEATURE::CONDCOLL
/*N*/
/*N*/       if( !IsModifyLocked() )
/*N*/       {
/*N*/           SwFmtChg aTmp1( pOldColl );
/*N*/           SwFmtChg aTmp2( pNewColl );
/*N*/ //            SwModify::Modify( &aTmp1, &aTmp2 );
/*N*/           // damit alles was im Modify passiert hier nicht noch impl.
/*N*/           // werden muss
/*N*/           SwCntntNode::Modify( &aTmp1, &aTmp2 );
/*N*/       }
/*N*/   }
/*N*/   if ( IsInCache() )
/*N*/   {
/*?*/       SwFrm::GetCache().Delete( this );
/*?*/       SetInCache( FALSE );
/*N*/   }
/*N*/   return pOldColl;
/*N*/ }


/*N*/ BOOL SwCntntNode::GoNext(SwIndex * pIdx, USHORT nMode ) const
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/   if( pIdx->GetIndex() < Len() )
/*N*/   {
/*N*/       if( !IsTxtNode() )
/*?*/           (*pIdx)++;
/*N*/       else
/*N*/       {
/*N*/           const SwTxtNode& rTNd = *GetTxtNode();
/*N*/           xub_StrLen nPos = pIdx->GetIndex();
/*N*/           if( pBreakIt->xBreak.is() )
/*N*/           {
/*N*/               sal_Int32 nDone = 0;
/*N*/               sal_uInt16 nItrMode = CRSR_SKIP_CHARS == nMode
/*N*/                                   ? CharacterIteratorMode::SKIPCONTROLCHARACTER
/*N*/                                   : CharacterIteratorMode::SKIPCELL;
/*N*/               nPos = pBreakIt->xBreak->nextCharacters( rTNd.GetTxt(), nPos,
/*N*/                               pBreakIt->GetLocale( rTNd.GetLang( nPos ) ),
/*N*/                               nItrMode, 1, nDone );
/*N*/               if( 1 == nDone )
/*N*/                   *pIdx = nPos;
/*N*/               else
/*?*/                   bRet = FALSE;
/*N*/           }
/*N*/           else if( nPos < rTNd.GetTxt().Len() )
/*?*/               (*pIdx)++;
/*N*/           else
/*?*/               bRet = FALSE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       bRet = FALSE;
/*N*/   return bRet;
/*N*/ }


/*N*/ BOOL SwCntntNode::GoPrevious(SwIndex * pIdx, USHORT nMode ) const
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/   if( pIdx->GetIndex() > 0 )
/*N*/   {
/*N*/       if( !IsTxtNode() )
/*?*/           (*pIdx)--;
/*N*/       else
/*N*/       {
/*N*/           const SwTxtNode& rTNd = *GetTxtNode();
/*N*/           xub_StrLen nPos = pIdx->GetIndex();
/*N*/           if( pBreakIt->xBreak.is() )
/*N*/           {
/*N*/               sal_Int32 nDone = 0;
/*N*/               sal_uInt16 nItrMode = CRSR_SKIP_CHARS == nMode
/*N*/                               ? CharacterIteratorMode::SKIPCONTROLCHARACTER
/*N*/                               : CharacterIteratorMode::SKIPCELL;
/*N*/               nPos = pBreakIt->xBreak->previousCharacters( rTNd.GetTxt(), nPos,
/*N*/                               pBreakIt->GetLocale( rTNd.GetLang( nPos ) ),
/*N*/                               nItrMode, 1, nDone );
/*N*/               if( 1 == nDone )
/*N*/                   *pIdx = nPos;
/*N*/               else
/*?*/                   bRet = FALSE;
/*N*/           }
/*N*/           else if( nPos )
/*?*/               (*pIdx)--;
/*N*/           else
/*?*/               bRet = FALSE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       bRet = FALSE;
/*N*/   return bRet;
/*N*/ }


/*
 * Methode erzeugt fuer den vorhergehenden Node alle Ansichten vom
 * Dokument. Die erzeugten Contentframes werden in das entsprechende
 * Layout gehaengt.
 */


/*N*/ void SwCntntNode::MakeFrms( SwCntntNode& rNode )
/*N*/ {
/*N*/   ASSERT( &rNode != this,
/*N*/           "Kein Contentnode oder Copy-Node und neuer Node identisch." );
/*N*/
/*N*/   if( !GetDepends() || &rNode == this )   // gibt es ueberhaupt Frames ??
/*?*/       return;
/*N*/
/*N*/   SwFrm *pFrm, *pNew;
/*N*/   SwLayoutFrm *pUpper;
/*N*/   // Frames anlegen fuer Nodes, die vor oder hinter der Tabelle stehen ??
/*N*/   ASSERT( FindTableNode() == rNode.FindTableNode(), "Table confusion" )
/*N*/
/*N*/   SwNode2Layout aNode2Layout( *this, rNode.GetIndex() );
/*N*/
/*N*/   while( 0 != (pUpper = aNode2Layout.UpperFrm( pFrm, rNode )) )
/*N*/   {
/*N*/       pNew = rNode.MakeFrm();
/*N*/       pNew->Paste( pUpper, pFrm );
/*N*/   }
/*N*/ }

/*
 * Methode loescht fuer den Node alle Ansichten vom
 * Dokument. Die Contentframes werden aus dem entsprechenden
 * Layout ausgehaengt.
 */


/*N*/ void SwCntntNode::DelFrms()
/*N*/ {
/*N*/   if( !GetDepends() )
/*N*/       return;
/*N*/
/*N*/   SwClientIter aIter( *this );
/*N*/   SwCntntFrm *pFrm;
/*N*/
/*N*/   for( pFrm = (SwCntntFrm*)aIter.First( TYPE(SwCntntFrm)); pFrm;
/*N*/        pFrm = (SwCntntFrm*)aIter.Next() )
/*N*/   {
/*N*/         if( pFrm->HasFollow() )
/*N*/             pFrm->GetFollow()->_SetIsFollow( pFrm->IsFollow() );
/*N*/         if( pFrm->IsFollow() )
/*N*/         {
/*?*/             SwCntntFrm* pMaster = (SwTxtFrm*)pFrm->FindMaster();
/*?*/             pMaster->SetFollow( pFrm->GetFollow() );
/*?*/             pFrm->_SetIsFollow( FALSE );
/*N*/         }
/*N*/       pFrm->SetFollow( 0 );//Damit er nicht auf dumme Gedanken kommt.
/*N*/                               //Andernfalls kann es sein, dass ein Follow
/*N*/                               //vor seinem Master zerstoert wird, der Master
/*N*/                               //greift dann ueber den ungueltigen
/*N*/                               //Follow-Pointer auf fremdes Memory zu.
/*N*/                               //Die Kette darf hier zerknauscht werden, weil
/*N*/                               //sowieso alle zerstoert werden.
/*N*/       if( pFrm->GetUpper() && pFrm->IsInFtn() && !pFrm->GetIndNext() &&
/*N*/           !pFrm->GetIndPrev() )
/*N*/       {
/*?*/           SwFtnFrm *pFtn = pFrm->FindFtnFrm();
/*?*/           ASSERT( pFtn, "You promised a FtnFrm?" );
/*?*/           SwCntntFrm* pCFrm;
/*?*/           if( !pFtn->GetFollow() && !pFtn->GetMaster() &&
/*?*/               0 != ( pCFrm = pFtn->GetRefFromAttr()) && pCFrm->IsFollow() )
/*?*/           {
/*?*/               ASSERT( pCFrm->IsTxtFrm(), "NoTxtFrm has Footnote?" );
/*?*/               ((SwTxtFrm*)pCFrm->FindMaster())->Prepare( PREP_FTN_GONE );
/*?*/           }
/*N*/       }
/*N*/       pFrm->Cut();
/*N*/       delete pFrm;
/*N*/   }
/*N*/   if( IsTxtNode() )
/*N*/   {
/*N*/       ((SwTxtNode*)this)->SetWrong( NULL );
/*N*/       SetWrongDirty( TRUE );
/*N*/       SetAutoCompleteWordDirty( TRUE );
/*N*/   }
/*N*/ }


//STRIP001 SwCntntNode *SwCntntNode::JoinNext()
//STRIP001 {
//STRIP001  return this;
//STRIP001 }


//STRIP001 SwCntntNode *SwCntntNode::JoinPrev()
//STRIP001 {
//STRIP001  return this;
//STRIP001 }



    // erfrage vom Modify Informationen
/*N*/ BOOL SwCntntNode::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   const SwNumRuleItem* pItem;
/*N*/   switch( rInfo.Which() )
/*N*/   {
/*N*/   case RES_AUTOFMT_DOCNODE:
/*N*/       if( &GetNodes() == ((SwAutoFmtGetDocNode&)rInfo).pNodes )
/*N*/       {
/*N*/           ((SwAutoFmtGetDocNode&)rInfo).pCntntNode = this;
/*N*/           return FALSE;
/*N*/       }
/*N*/       break;
/*?*/   case RES_GETNUMNODES:
/*?*/       if( IsTxtNode() && 0 != ( pItem = (SwNumRuleItem*)GetNoCondAttr(
/*?*/           RES_PARATR_NUMRULE, TRUE )) &&
/*?*/           pItem->GetValue().Len() &&
/*?*/           pItem->GetValue() == ((SwNumRuleInfo&)rInfo).GetName() &&
/*?*/           GetNodes().IsDocNodes() )
/*?*/       {
/*?*/           ((SwNumRuleInfo&)rInfo).AddNode( *(SwTxtNode*)this );
/*?*/       }
/*?*/       return TRUE;
/*?*/
/*?*/   case RES_GETLOWERNUMLEVEL:
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( IsTxtNode() && ((SwTxtNode*)this)->GetNum() &&
//STRIP001 /*?*/            0 != ( pItem = (SwNumRuleItem*)GetNoCondAttr(
//STRIP001 /*?*/            RES_PARATR_NUMRULE, TRUE )) && pItem->GetValue().Len() &&
//STRIP001 /*?*/            pItem->GetValue() == ((SwNRuleLowerLevel&)rInfo).GetName() &&
//STRIP001 /*?*/            (((SwTxtNode*)this)->GetNum()->GetLevel() & ~NO_NUMLEVEL)
//STRIP001 /*?*/                > ((SwNRuleLowerLevel&)rInfo).GetLevel() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/        }
/*?*/       break;
/*?*/
/*?*/   case RES_FINDNEARESTNODE:
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( ((SwFmtPageDesc&)GetAttr( RES_PAGEDESC )).GetPageDesc() )
//STRIP001 /*?*/            ((SwFindNearestNode&)rInfo).CheckNode( *this );
/*?*/       return TRUE;
/*?*/
/*?*/   case RES_CONTENT_VISIBLE:
/*?*/       {
/*?*/           ((SwPtrMsgPoolItem&)rInfo).pObject =
/*?*/               SwClientIter( *(SwCntntNode*)this ).First( TYPE(SwFrm) );
/*?*/       }
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   return SwModify::GetInfo( rInfo );
/*N*/ }


    // setze ein Attribut
/*N*/ BOOL SwCntntNode::SetAttr(const SfxPoolItem& rAttr )
/*N*/ {
/*N*/   if( !pAttrSet )         // lasse von den entsprechenden Nodes die
/*N*/       NewAttrSet( GetDoc()->GetAttrPool() );      // AttrSets anlegen
/*N*/
/*N*/   ASSERT( pAttrSet, "warum wurde kein AttrSet angelegt?" );
/*N*/
/*N*/   if ( IsInCache() )
/*N*/   {
/*N*/       SwFrm::GetCache().Delete( this );
/*N*/       SetInCache( FALSE );
/*N*/   }
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/   // wenn Modify gelockt ist, werden keine Modifies verschickt
/*N*/   if( IsModifyLocked() ||
/*N*/       ( !GetDepends() &&  RES_PARATR_NUMRULE != rAttr.Which() ))
/*N*/   {
/*N*/       if( 0 != ( bRet = (0 != pAttrSet->Put( rAttr )) ))
/*N*/           // einige Sonderbehandlungen fuer Attribute
/*N*/           pAttrSet->SetModifyAtAttr( this );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwAttrSet aOld( *pAttrSet->GetPool(), pAttrSet->GetRanges() ),
/*N*/                   aNew( *pAttrSet->GetPool(), pAttrSet->GetRanges() );
/*N*/       if( 0 != ( bRet = pAttrSet->Put_BC( rAttr, &aOld, &aNew ) ))
/*N*/       {
/*N*/           // einige Sonderbehandlungen fuer Attribute
/*N*/           pAttrSet->SetModifyAtAttr( this );
/*N*/
/*N*/           SwAttrSetChg aChgOld( *pAttrSet, aOld );
/*N*/           SwAttrSetChg aChgNew( *pAttrSet, aNew );
/*N*/           Modify( &aChgOld, &aChgNew );       // alle veraenderten werden verschickt
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }


/*N*/ BOOL SwCntntNode::SetAttr( const SfxItemSet& rSet )
/*N*/ {
/*N*/   if( !pAttrSet )         // lasse von den entsprechenden Nodes die
/*N*/       NewAttrSet( GetDoc()->GetAttrPool() );      // AttrSets anlegen
/*N*/
/*N*/   if ( IsInCache() )
/*N*/   {
/*N*/       SwFrm::GetCache().Delete( this );
/*N*/       SetInCache( FALSE );
/*N*/   }
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   // wenn Modify gelockt ist, werden keine Modifies verschickt
/*N*/   if( IsModifyLocked() || ( !GetDepends() &&
/*N*/       SFX_ITEM_SET != rSet.GetItemState( RES_PARATR_NUMRULE, FALSE )) )
/*N*/   {
/*N*/       // einige Sonderbehandlungen fuer Attribute
/*N*/       if( 0 != (bRet = (0 != pAttrSet->Put( rSet ))) )
/*N*/           pAttrSet->SetModifyAtAttr( this );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwAttrSet aOld( *pAttrSet->GetPool(), pAttrSet->GetRanges() ),
/*N*/                   aNew( *pAttrSet->GetPool(), pAttrSet->GetRanges() );
/*N*/       if( 0 != (bRet = pAttrSet->Put_BC( rSet, &aOld, &aNew )) )
/*N*/       {
/*N*/           // einige Sonderbehandlungen fuer Attribute
/*N*/           pAttrSet->SetModifyAtAttr( this );
/*N*/           SwAttrSetChg aChgOld( *pAttrSet, aOld );
/*N*/           SwAttrSetChg aChgNew( *pAttrSet, aNew );
/*N*/           Modify( &aChgOld, &aChgNew );       // alle veraenderten werden verschickt
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

// Nimmt den Hint mit nWhich aus dem Delta-Array


/*N*/ BOOL SwCntntNode::ResetAttr( USHORT nWhich1, USHORT nWhich2 )
/*N*/ {
/*N*/   if( !pAttrSet )
/*?*/       return FALSE;
/*N*/
/*N*/   if ( IsInCache() )
/*N*/   {
/*?*/       SwFrm::GetCache().Delete( this );
/*?*/       SetInCache( FALSE );
/*N*/   }
/*N*/
/*N*/   // wenn Modify gelockt ist, werden keine Modifies verschickt
/*N*/   if( IsModifyLocked() )
/*N*/   {
/*?*/       USHORT nDel = (!nWhich2 || nWhich2 < nWhich1)
/*?*/               ? pAttrSet->ClearItem( nWhich1 )
/*?*/               : pAttrSet->ClearItem_BC( nWhich1, nWhich2 );
/*?*/
/*?*/       if( !pAttrSet->Count() )    // leer, dann loeschen
/*?*/           DELETEZ( pAttrSet );
/*?*/       return 0 != nDel;
/*N*/   }
/*N*/
/*N*/   // sollte kein gueltiger Bereich definiert sein ?
/*N*/   if( !nWhich2 || nWhich2 < nWhich1 )
/*N*/       nWhich2 = nWhich1;      // dann setze auf 1. Id, nur dieses Item
/*N*/
/*N*/   SwAttrSet aOld( *pAttrSet->GetPool(), pAttrSet->GetRanges() ),
/*N*/               aNew( *pAttrSet->GetPool(), pAttrSet->GetRanges() );
/*N*/   BOOL bRet = 0 != pAttrSet->ClearItem_BC( nWhich1, nWhich2, &aOld, &aNew );
/*N*/
/*N*/   if( bRet )
/*N*/   {
/*N*/       SwAttrSetChg aChgOld( *pAttrSet, aOld );
/*N*/       SwAttrSetChg aChgNew( *pAttrSet, aNew );
/*N*/       Modify( &aChgOld, &aChgNew );       // alle veraenderten werden verschickt
/*N*/
/*N*/       if( !pAttrSet->Count() )    // leer, dann loeschen
/*N*/           DELETEZ( pAttrSet );
/*N*/   }
/*N*/   return bRet;
/*N*/ }
//STRIP001 BOOL SwCntntNode::ResetAttr( const SvUShorts& rWhichArr )
//STRIP001 {
//STRIP001  if( !pAttrSet )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( IsInCache() )
//STRIP001  {
//STRIP001      SwFrm::GetCache().Delete( this );
//STRIP001      SetInCache( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  // wenn Modify gelockt ist, werden keine Modifies verschickt
//STRIP001  USHORT nDel = 0;
//STRIP001  if( IsModifyLocked() )
//STRIP001  {
//STRIP001      for( USHORT n = 0, nEnd = rWhichArr.Count(); n < nEnd; ++n )
//STRIP001          if( pAttrSet->ClearItem( rWhichArr[ n ] ))
//STRIP001              ++nDel;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwAttrSet aOld( *pAttrSet->GetPool(), pAttrSet->GetRanges() ),
//STRIP001                  aNew( *pAttrSet->GetPool(), pAttrSet->GetRanges() );
//STRIP001
//STRIP001      for( USHORT n = 0, nEnd = rWhichArr.Count(); n < nEnd; ++n )
//STRIP001          if( pAttrSet->ClearItem_BC( rWhichArr[ n ], &aOld, &aNew ))
//STRIP001              ++nDel;
//STRIP001
//STRIP001      if( nDel )
//STRIP001      {
//STRIP001          SwAttrSetChg aChgOld( *pAttrSet, aOld );
//STRIP001          SwAttrSetChg aChgNew( *pAttrSet, aNew );
//STRIP001          Modify( &aChgOld, &aChgNew );       // alle veraenderten werden verschickt
//STRIP001      }
//STRIP001  }
//STRIP001  if( !pAttrSet->Count() )    // leer, dann loeschen
//STRIP001      DELETEZ( pAttrSet );
//STRIP001  return 0 != nDel ;
//STRIP001 }


/*N*/ USHORT SwCntntNode::ResetAllAttr()
/*N*/ {
/*N*/   if( !pAttrSet )
/*N*/       return 0;
/*N*/
/*N*/   if ( IsInCache() )
/*N*/   {
/*?*/       SwFrm::GetCache().Delete( this );
/*?*/       SetInCache( FALSE );
/*N*/   }
/*N*/
/*N*/   // wenn Modify gelockt ist, werden keine Modifies verschickt
/*N*/   if( IsModifyLocked() )
/*N*/   {
/*?*/       USHORT nDel = pAttrSet->ClearItem( 0 );
/*?*/       if( !pAttrSet->Count() )    // leer, dann loeschen
/*?*/           DELETEZ( pAttrSet );
/*?*/       return nDel;
/*N*/   }
/*N*/
/*N*/   SwAttrSet aOld( *pAttrSet->GetPool(), pAttrSet->GetRanges() ),
/*N*/               aNew( *pAttrSet->GetPool(), pAttrSet->GetRanges() );
/*N*/   BOOL bRet = 0 != pAttrSet->ClearItem_BC( 0, &aOld, &aNew );
/*N*/
/*N*/   if( bRet )
/*N*/   {
/*N*/       SwAttrSetChg aChgOld( *pAttrSet, aOld );
/*N*/       SwAttrSetChg aChgNew( *pAttrSet, aNew );
/*N*/       Modify( &aChgOld, &aChgNew );       // alle veraenderten werden verschickt
/*N*/
/*N*/       if( !pAttrSet->Count() )    // leer, dann loeschen
/*N*/           DELETEZ( pAttrSet );
/*N*/   }
/*N*/   return aNew.Count();
/*N*/ }


/*N*/ BOOL SwCntntNode::GetAttr( SfxItemSet& rSet, BOOL bInParent ) const
/*N*/ {
/*N*/   if( rSet.Count() )
/*?*/       rSet.ClearItem();
/*N*/
/*N*/   const SwAttrSet& rAttrSet = GetSwAttrSet();
/*N*/   if( bInParent )
/*N*/       return rSet.Set( rAttrSet, TRUE ) ? TRUE : FALSE;
/*N*/
/*?*/   rSet.Put( rAttrSet );
/*?*/   return rSet.Count() ? TRUE : FALSE;
/*N*/ }

/*N*/ const SfxPoolItem* SwCntntNode::GetNoCondAttr( USHORT nWhich,
/*N*/                                               BOOL bInParents ) const
/*N*/ {
/*N*/   const SfxPoolItem* pFnd = 0;
/*N*/   if( pCondColl && pCondColl->GetRegisteredIn() )
/*N*/   {
/*?*/       if( !pAttrSet || ( SFX_ITEM_SET != pAttrSet->GetItemState(
/*?*/                   nWhich, FALSE, &pFnd ) && bInParents ))
/*?*/           ((SwFmt*)GetRegisteredIn())->GetItemState( nWhich, bInParents, &pFnd );
/*N*/   }
/*N*/   else
/*N*/       GetSwAttrSet().GetItemState( nWhich, bInParents, &pFnd );
/*N*/   return pFnd;
/*N*/ }

    // koennen 2 Nodes zusammengefasst werden ?
    // in pIdx kann die 2. Position returnt werden.
/*N*/ int SwCntntNode::CanJoinNext( SwNodeIndex* pIdx ) const
/*N*/ {
/*N*/   const SwNodes& rNds = GetNodes();
/*N*/   BYTE nNdType = GetNodeType();
/*N*/   SwNodeIndex aIdx( *this, 1 );
/*N*/
/*N*/   const SwNode* pNd = this;
/*N*/   while( aIdx < rNds.Count()-1 &&
/*N*/       (( pNd = &aIdx.GetNode())->IsSectionNode() ||
/*N*/           ( pNd->IsEndNode() && pNd->FindStartNode()->IsSectionNode() )))
/*N*/       aIdx++;
/*N*/
/*N*/   if( pNd->GetNodeType() != nNdType || rNds.Count()-1 == aIdx.GetIndex() )
/*N*/       return FALSE;
/*N*/   if( pIdx )
/*N*/       *pIdx = aIdx;
/*N*/   return TRUE;
/*N*/ }


    // koennen 2 Nodes zusammengefasst werden ?
    // in pIdx kann die 2. Position returnt werden.
/*N*/ int SwCntntNode::CanJoinPrev( SwNodeIndex* pIdx ) const
/*N*/ {
/*N*/   const SwNodes& rNds = GetNodes();
/*N*/   BYTE nNdType = GetNodeType();
/*N*/   SwNodeIndex aIdx( *this, -1 );
/*N*/
/*N*/   const SwNode* pNd = this;
/*N*/   while( aIdx.GetIndex() &&
/*N*/       (( pNd = &aIdx.GetNode())->IsSectionNode() ||
/*N*/           ( pNd->IsEndNode() && pNd->FindStartNode()->IsSectionNode() )))
/*?*/       aIdx--;
/*N*/
/*N*/   if( pNd->GetNodeType() != nNdType || 0 == aIdx.GetIndex() )
/*?*/       return FALSE;
/*N*/   if( pIdx )
/*N*/       *pIdx = aIdx;
/*N*/   return TRUE;
/*N*/ }


//FEATURE::CONDCOLL


/*N*/ void SwCntntNode::SetCondFmtColl( SwFmtColl* pColl )
/*N*/ {
/*N*/   if( (!pColl && pCondColl) || ( pColl && !pCondColl ) ||
/*N*/       ( pColl && pColl != pCondColl->GetRegisteredIn() ) )
/*N*/   {
/*?*/       SwFmtColl* pOldColl = GetCondFmtColl();
/*?*/       delete pCondColl;
/*?*/       if( pColl )
/*?*/           pCondColl = new SwDepend( this, pColl );
/*?*/       else
/*?*/           pCondColl = 0;
/*?*/
/*?*/       if( pAttrSet )
/*?*/       {
/*?*/ // Attrset beibehalten oder loeschen??
/*?*/ // 13.04.99: Bisher wurden er geloescht, jetzt wird er beibehalten.
/*?*/ //             #64637#: Beim Laden eines Dokuments wird die bedingte
/*?*/ //             Vorlage nach dem Laden der harten Attribute gesetzt. Deshalb
/*?*/ //             wurden die harten Attribute geloescht.
/*?*/
/*?*/           pAttrSet->SetParent( &GetAnyFmtColl().GetAttrSet() );
/*?*/ // steht im docfmt.cxx
/*?*/ //extern BOOL lcl_RstAttr( const SwNodePtr&, void* );
/*?*/ //            lcl_RstAttr( this, 0 );
/*?*/ //            if( pAttrSet && !pAttrSet->Count() )
/*?*/ //                delete pAttrSet, pAttrSet = 0;
/*?*/       }
/*?*/
/*?*/       if( !IsModifyLocked() )
/*?*/       {
/*?*/           SwFmtChg aTmp1( pOldColl ? pOldColl : GetFmtColl() );
/*?*/           SwFmtChg aTmp2( pColl ? pColl : GetFmtColl() );
/*?*/           SwModify::Modify( &aTmp1, &aTmp2 );
/*?*/       }
/*?*/       if( IsInCache() )
/*?*/       {
/*?*/           SwFrm::GetCache().Delete( this );
/*?*/           SetInCache( FALSE );
/*?*/       }
/*N*/   }
/*N*/ }


/*N*/ BOOL SwCntntNode::IsAnyCondition( SwCollCondition& rTmp ) const
/*N*/ {
/*N*/   const SwNodes& rNds = GetNodes();
/*N*/   {
/*N*/       int nCond = 0;
/*N*/       const SwStartNode* pSttNd = FindStartNode();
/*N*/       while( pSttNd )
/*N*/       {
/*N*/           switch( pSttNd->GetNodeType() )
/*N*/           {
/*?*/           case ND_TABLENODE:      nCond = PARA_IN_TABLEBODY; break;
/*N*/           case ND_SECTIONNODE:    nCond = PARA_IN_SECTION; break;
/*N*/
/*N*/           default:
/*N*/               switch( pSttNd->GetStartNodeType() )
/*N*/               {
/*N*/               case SwTableBoxStartNode:
/*N*/                   {
/*N*/                       nCond = PARA_IN_TABLEBODY;
/*N*/                       const SwTableNode* pTblNd = pSttNd->FindTableNode();
/*N*/                       const SwTableBox* pBox;
/*N*/                       if( pTblNd && 0 != ( pBox = pTblNd->GetTable().
/*N*/                           GetTblBox( pSttNd->GetIndex() ) ) &&
/*N*/                           pBox->IsInHeadline( &pTblNd->GetTable() ) )
/*N*/                           nCond = PARA_IN_TABLEHEAD;
/*N*/                   }
/*N*/                   break;
/*N*/               case SwFlyStartNode:        nCond = PARA_IN_FRAME; break;
/*N*/               case SwFootnoteStartNode:
/*?*/                   {
/*?*/                       nCond = PARA_IN_FOOTENOTE;
/*?*/                       const SwFtnIdxs& rFtnArr = rNds.GetDoc()->GetFtnIdxs();
/*?*/                       const SwTxtFtn* pTxtFtn;
/*?*/                       const SwNode* pSrchNd = pSttNd;
/*?*/
/*?*/                       for( USHORT n = 0; n < rFtnArr.Count(); ++n )
/*?*/                           if( 0 != ( pTxtFtn = rFtnArr[ n ])->GetStartNode() &&
/*?*/                               pSrchNd == &pTxtFtn->GetStartNode()->GetNode() )
/*?*/                           {
/*?*/                               if( pTxtFtn->GetFtn().IsEndNote() )
/*?*/                                   nCond = PARA_IN_ENDNOTE;
/*?*/                               break;
/*?*/                           }
/*?*/                   }
/*?*/                   break;
/*?*/               case SwHeaderStartNode:     nCond = PARA_IN_HEADER; break;
/*?*/               case SwFooterStartNode:     nCond = PARA_IN_FOOTER; break;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if( nCond )
/*N*/           {
/*N*/               rTmp.SetCondition( (Master_CollConditions)nCond, 0 );
/*N*/               return TRUE;
/*N*/           }
/*N*/           pSttNd = pSttNd->GetIndex()
/*N*/                       ? pSttNd->FindStartNode()
/*N*/                       : 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   {
/*N*/       USHORT nPos;
/*N*/       const SwOutlineNodes& rOutlNds = rNds.GetOutLineNds();
/*N*/       if( rOutlNds.Count() )
/*N*/       {
/*N*/           if( !rOutlNds.Seek_Entry( (SwCntntNode*)this, &nPos ) && nPos )
/*N*/               --nPos;
/*N*/           if( nPos < rOutlNds.Count() &&
/*N*/               rOutlNds[ nPos ]->GetIndex() < GetIndex() )
/*N*/           {
/*N*/               SwTxtNode* pOutlNd = rOutlNds[ nPos ]->GetTxtNode();
/*N*/
/*N*/               if( pOutlNd->GetOutlineNum() && !pOutlNd->GetNumRule() )
/*N*/               {
/*N*/                   rTmp.SetCondition( PARA_IN_OUTLINE,
/*N*/                                   pOutlNd->GetOutlineNum()->GetLevel() );
/*N*/                   return TRUE;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }


/*N*/ void SwCntntNode::ChkCondColl()
/*N*/ {
/*N*/   // zur Sicherheit abfragen
/*N*/   if( RES_CONDTXTFMTCOLL == GetFmtColl()->Which() )
/*N*/   {
/*N*/       SwCollCondition aTmp( 0, 0, 0 );
/*N*/       const SwCollCondition* pCColl;
/*N*/
/*N*/       if( IsAnyCondition( aTmp ) && 0 != ( pCColl =
/*N*/               ((SwConditionTxtFmtColl*)GetFmtColl())->HasCondition( aTmp )))
/*?*/           SetCondFmtColl( pCColl->GetTxtFmtColl() );
/*N*/       else
/*N*/       {
/*N*/           if( IsTxtNode() && ((SwTxtNode*)this)->GetNumRule() &&
/*N*/                   ((SwTxtNode*)this)->GetNum() )
/*N*/           {
/*N*/               // steht in einer Numerierung
/*N*/               // welcher Level?
/*N*/               aTmp.SetCondition( PARA_IN_LIST,
/*N*/                               ((SwTxtNode*)this)->GetNum()->GetLevel() );
/*N*/               pCColl = ((SwConditionTxtFmtColl*)GetFmtColl())->
/*N*/                               HasCondition( aTmp );
/*N*/           }
/*N*/           else
/*N*/               pCColl = 0;
/*N*/
/*N*/           if( pCColl )
/*?*/               SetCondFmtColl( pCColl->GetTxtFmtColl() );
/*N*/           else if( pCondColl )
/*?*/               SetCondFmtColl( 0 );
/*N*/       }
/*N*/   }
/*N*/ }

//FEATURE::CONDCOLL
// Metoden aus Node.hxx - erst hier ist der TxtNode bekannt !!
// os: nur fuer ICC, da der zum optimieren zu dumm ist
/*N*/ #ifdef ICC
/*N*/ SwTxtNode   *SwNode::GetTxtNode()
/*N*/ {
/*N*/    return ND_TEXTNODE == nNodeType ? (SwTxtNode*)this : 0;
/*N*/ }
/*N*/ const SwTxtNode   *SwNode::GetTxtNode() const
/*N*/ {
/*N*/    return ND_TEXTNODE == nNodeType ? (const SwTxtNode*)this : 0;
/*N*/ }
/*N*/ #endif




}
