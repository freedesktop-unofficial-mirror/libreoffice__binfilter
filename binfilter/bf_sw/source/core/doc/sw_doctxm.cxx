/*************************************************************************
 *
 *  $RCSfile: sw_doctxm.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:52 $
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

#include <limits.h>

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#define _SVSTDARR_STRINGSSORT
#include <svtools/svstdarr.hxx>
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _SVX_TSPTITEM_HXX
#include <bf_svx/tstpitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SOT_CLSIDS_HXX
#include <sot/clsids.hxx>
#endif

#ifndef _SWDOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _TXTTXMRK_HXX
#include <txttxmrk.hxx>
#endif
#ifndef _FMTINFMT_HXX
#include <fmtinfmt.hxx>
#endif
#ifndef _FMTPDSC_HXX
#include <fmtpdsc.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _FMTFSIZE_HXX
#include <fmtfsize.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>
#endif
#ifndef _TXMSRT_HXX
#include <txmsrt.hxx>
#endif
#ifndef _ROLBCK_HXX
#include <rolbck.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _FCHRFMT_HXX
#include <fchrfmt.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX
#include <txtfld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _CHPFLD_HXX
#include <chpfld.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
#ifndef _NODE2LAY_HXX
#include <node2lay.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
namespace binfilter {

const sal_Unicode cNumRepl      = '@';
const sal_Unicode cEndPageNum   = '~';
const sal_Char __FAR_DATA sPageDeli[] = ", ";

/*N*/ SV_IMPL_PTRARR(SwTOXSortTabBases, SwTOXSortTabBasePtr)

/*N*/ TYPEINIT2( SwTOXBaseSection, SwTOXBase, SwSection );  // fuers RTTI

struct LinkStruct
{
    SwFmtINetFmt    aINetFmt;
    xub_StrLen nStartTextPos, nEndTextPos;

    LinkStruct( const String& rURL, xub_StrLen nStart, xub_StrLen nEnd )
        : aINetFmt( rURL, aEmptyStr),
        nStartTextPos( nStart),
        nEndTextPos(nEnd) {}
};

typedef LinkStruct* LinkStructPtr;
//STRIP001 SV_DECL_PTRARR(LinkStructArr, LinkStructPtr, 0, 5 )//STRIP008 ;
//STRIP001 SV_IMPL_PTRARR(LinkStructArr, LinkStructPtr)

//STRIP001 USHORT SwDoc::GetTOIKeys( SwTOIKeyType eTyp, SvStringsSort& rArr ) const
//STRIP001 {
//STRIP001  if( rArr.Count() )
//STRIP001      rArr.Remove( USHORT(0), rArr.Count() );
//STRIP001
//STRIP001  // dann mal ueber den Pool und alle Primary oder Secondary heraussuchen
//STRIP001  const SwTxtTOXMark* pMark;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  USHORT i, nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_TOXMARK );
//STRIP001  for( i = 0; i < nMaxItems; ++i )
//STRIP001      if( 0 != (pItem = GetAttrPool().GetItem( RES_TXTATR_TOXMARK, i ) ) &&
//STRIP001          TOX_INDEX == ((SwTOXMark*)pItem)->GetTOXType()->GetType() &&
//STRIP001          0 != ( pMark = ((SwTOXMark*)pItem)->GetTxtTOXMark() ) &&
//STRIP001          pMark->GetpTxtNd() &&
//STRIP001          pMark->GetpTxtNd()->GetNodes().IsDocNodes() )
//STRIP001      {
//STRIP001          const String* pStr;
//STRIP001          if( TOI_PRIMARY == eTyp )
//STRIP001              pStr = &((SwTOXMark*)pItem)->GetPrimaryKey();
//STRIP001          else
//STRIP001              pStr = &((SwTOXMark*)pItem)->GetSecondaryKey();
//STRIP001
//STRIP001          if( pStr->Len() )
//STRIP001              rArr.Insert( (StringPtr)pStr );
//STRIP001      }
//STRIP001
//STRIP001  return rArr.Count();
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: aktuelle Verzeichnismarkierungen ermitteln
 --------------------------------------------------------------------*/


/*N*/ USHORT SwDoc::GetCurTOXMark( const SwPosition& rPos,
/*N*/                               SwTOXMarks& rArr ) const
/*N*/ {
/*N*/   // suche an der Position rPos nach allen SwTOXMark's
/*N*/   SwTxtNode* pTxtNd = GetNodes()[ rPos.nNode ]->GetTxtNode();
/*N*/   // kein TextNode oder kein HintsArray vorhanden ??
/*N*/   if( !pTxtNd || !pTxtNd->GetpSwpHints() )
/*N*/       return 0;
/*N*/
/*N*/   const SwpHints & rHts = *pTxtNd->GetpSwpHints();
/*N*/   const SwTxtAttr* pHt;
/*N*/   xub_StrLen nSttIdx;
/*N*/   const xub_StrLen *pEndIdx;
/*N*/
/*N*/   xub_StrLen nAktPos = rPos.nContent.GetIndex();
/*N*/
/*N*/   for( USHORT n = 0; n < rHts.Count(); ++n )
/*N*/   {
/*N*/       if( RES_TXTATR_TOXMARK != (pHt = rHts[n])->Which() )
/*N*/           continue;
/*N*/       if( ( nSttIdx = *pHt->GetStart() ) < nAktPos )
/*N*/       {
/*N*/           // pruefe Ende mit ab
/*N*/           if( 0 == ( pEndIdx = pHt->GetEnd() ) ||
/*N*/               *pEndIdx <= nAktPos )
/*N*/               continue;       // weiter suchen
/*N*/       }
/*N*/       else if( nSttIdx > nAktPos )
/*N*/           // ist Start vom Hint groesser als rPos, dann abbrechen. Denn
/*N*/           // die Attribute sind nach Start sortiert !
/*N*/           break;
/*N*/
/*?*/       const SwTOXMark* pTMark = &pHt->GetTOXMark();
/*?*/       rArr.Insert( pTMark, rArr.Count() );
/*N*/   }
/*N*/   return rArr.Count();
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: Marke loeschen
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::Delete( SwTOXMark* pTOXMark )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   // hole den TextNode und
//STRIP001  SwTxtTOXMark* pTxtTOXMark = pTOXMark->GetTxtTOXMark();
//STRIP001  ASSERT( pTxtTOXMark, "Kein TxtTOXMark, kann nicht geloescht werden" );
//STRIP001
//STRIP001  SwTxtNode& rTxtNd = (SwTxtNode&)pTxtTOXMark->GetTxtNode();
//STRIP001  ASSERT( rTxtNd.GetpSwpHints(), "kann nicht geloescht werden" );
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      // fuers Undo die Attribute sichern
//STRIP001      ClearRedo();
//STRIP001      SwUndoRstAttr* pUndo = new SwUndoRstAttr( *this, SwPosition( rTxtNd,
//STRIP001                          SwIndex( &rTxtNd, *pTxtTOXMark->GetStart() ) ),
//STRIP001                                  RES_TXTATR_TOXMARK );
//STRIP001      AppendUndo( pUndo );
//STRIP001
//STRIP001      SwRegHistory aRHst( rTxtNd, pUndo->GetHistory() );
//STRIP001      rTxtNd.GetpSwpHints()->Register( &aRHst );
//STRIP001      rTxtNd.Delete( pTxtTOXMark, TRUE );
//STRIP001      if( rTxtNd.GetpSwpHints() )
//STRIP001          rTxtNd.GetpSwpHints()->DeRegister();
//STRIP001  }
//STRIP001  else
//STRIP001      rTxtNd.Delete( pTxtTOXMark, TRUE );
//STRIP001  SetModified();
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: Traveln zwischen TOXMarks
 --------------------------------------------------------------------*/

//STRIP001 class CompareNodeCntnt
//STRIP001 {
//STRIP001  ULONG nNode;
//STRIP001  xub_StrLen nCntnt;
//STRIP001 public:
//STRIP001  CompareNodeCntnt( ULONG nNd, xub_StrLen nCnt )
//STRIP001      : nNode( nNd ), nCntnt( nCnt ) {}
//STRIP001
//STRIP001  int operator==( const CompareNodeCntnt& rCmp )
//STRIP001      { return nNode == rCmp.nNode && nCntnt == rCmp.nCntnt; }
//STRIP001  int operator!=( const CompareNodeCntnt& rCmp )
//STRIP001      { return nNode != rCmp.nNode || nCntnt != rCmp.nCntnt; }
//STRIP001  int operator< ( const CompareNodeCntnt& rCmp )
//STRIP001      { return nNode < rCmp.nNode ||
//STRIP001          ( nNode == rCmp.nNode && nCntnt < rCmp.nCntnt); }
//STRIP001  int operator<=( const CompareNodeCntnt& rCmp )
//STRIP001      { return nNode < rCmp.nNode ||
//STRIP001          ( nNode == rCmp.nNode && nCntnt <= rCmp.nCntnt); }
//STRIP001  int operator> ( const CompareNodeCntnt& rCmp )
//STRIP001      { return nNode > rCmp.nNode ||
//STRIP001          ( nNode == rCmp.nNode && nCntnt > rCmp.nCntnt); }
//STRIP001  int operator>=( const CompareNodeCntnt& rCmp )
//STRIP001      { return nNode > rCmp.nNode ||
//STRIP001          ( nNode == rCmp.nNode && nCntnt >= rCmp.nCntnt); }
//STRIP001 };

//STRIP001 const SwTOXMark& SwDoc::GotoTOXMark( const SwTOXMark& rCurTOXMark,
//STRIP001                                  SwTOXSearch eDir, BOOL bInReadOnly )
//STRIP001 {
//STRIP001  const SwTxtTOXMark* pMark = rCurTOXMark.GetTxtTOXMark();
//STRIP001  ASSERT(pMark, "pMark==0 Ungueltige TxtTOXMark");
//STRIP001
//STRIP001  const SwTxtNode *pTOXSrc = pMark->GetpTxtNd();
//STRIP001
//STRIP001  CompareNodeCntnt aAbsIdx( pTOXSrc->GetIndex(), *pMark->GetStart() );
//STRIP001  CompareNodeCntnt aPrevPos( 0, 0 );
//STRIP001  CompareNodeCntnt aNextPos( ULONG_MAX, STRING_NOTFOUND );
//STRIP001  CompareNodeCntnt aMax( 0, 0 );
//STRIP001  CompareNodeCntnt aMin( ULONG_MAX, STRING_NOTFOUND );
//STRIP001
//STRIP001  const SwTOXMark*    pNew    = 0;
//STRIP001  const SwTOXMark*    pMax    = &rCurTOXMark;
//STRIP001  const SwTOXMark*    pMin    = &rCurTOXMark;
//STRIP001
//STRIP001  const SwModify* pType = rCurTOXMark.GetRegisteredIn();
//STRIP001  SwClientIter    aIter( *(SwModify*)pType );
//STRIP001
//STRIP001  const SwTOXMark* pTOXMark;
//STRIP001  const SwCntntFrm* pCFrm;
//STRIP001  Point aPt;
//STRIP001  for( pTOXMark = (SwTOXMark*)aIter.First( TYPE( SwTOXMark )); pTOXMark;
//STRIP001       pTOXMark = (SwTOXMark*)aIter.Next() )
//STRIP001  {
//STRIP001      if( pTOXMark != &rCurTOXMark &&
//STRIP001          0 != ( pMark = pTOXMark->GetTxtTOXMark()) &&
//STRIP001          0 != ( pTOXSrc = pMark->GetpTxtNd() ) &&
//STRIP001          0 != ( pCFrm = pTOXSrc->GetFrm( &aPt, 0, FALSE )) &&
//STRIP001          ( bInReadOnly || !pCFrm->IsProtected() ))
//STRIP001      {
//STRIP001          CompareNodeCntnt aAbsNew( pTOXSrc->GetIndex(), *pMark->GetStart() );
//STRIP001          switch( eDir )
//STRIP001          {
//STRIP001              //Die untenstehenden etwas komplizierter ausgefallen Ausdruecke
//STRIP001              //dienen dazu auch ueber Eintraege auf der selben (!) Position
//STRIP001              //traveln zu koennen. Wenn einer Zeit hat mag er sie mal
//STRIP001              //optimieren.
//STRIP001
//STRIP001          case TOX_SAME_PRV:
//STRIP001              if( pTOXMark->GetText() != rCurTOXMark.GetText() )
//STRIP001                  break;
//STRIP001              /* no break here */
//STRIP001          case TOX_PRV:
//STRIP001              if ( (aAbsNew < aAbsIdx && aAbsNew > aPrevPos &&
//STRIP001                    aPrevPos != aAbsIdx && aAbsNew != aAbsIdx ) ||
//STRIP001                   (aAbsIdx == aAbsNew &&
//STRIP001                    (ULONG(&rCurTOXMark) > ULONG(pTOXMark) &&
//STRIP001                     (!pNew ||
//STRIP001                      (pNew && (aPrevPos < aAbsIdx ||
//STRIP001                                ULONG(pNew) < ULONG(pTOXMark)))))) ||
//STRIP001                   (aPrevPos == aAbsNew && aAbsIdx != aAbsNew &&
//STRIP001                    ULONG(pTOXMark) > ULONG(pNew)) )
//STRIP001              {
//STRIP001                  pNew = pTOXMark;
//STRIP001                  aPrevPos = aAbsNew;
//STRIP001                  if ( aAbsNew >= aMax )
//STRIP001                  {
//STRIP001                      aMax = aAbsNew;
//STRIP001                      pMax = pTOXMark;
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOX_SAME_NXT:
//STRIP001              if( pTOXMark->GetText() != rCurTOXMark.GetText() )
//STRIP001                  break;
//STRIP001              /* no break here */
//STRIP001          case TOX_NXT:
//STRIP001              if ( (aAbsNew > aAbsIdx && aAbsNew < aNextPos &&
//STRIP001                    aNextPos != aAbsIdx && aAbsNew != aAbsIdx ) ||
//STRIP001                   (aAbsIdx == aAbsNew &&
//STRIP001                    (ULONG(&rCurTOXMark) < ULONG(pTOXMark) &&
//STRIP001                     (!pNew ||
//STRIP001                      (pNew && (aNextPos > aAbsIdx ||
//STRIP001                                ULONG(pNew) > ULONG(pTOXMark)))))) ||
//STRIP001                   (aNextPos == aAbsNew && aAbsIdx != aAbsNew &&
//STRIP001                    ULONG(pTOXMark) < ULONG(pNew)) )
//STRIP001              {
//STRIP001                  pNew = pTOXMark;
//STRIP001                  aNextPos = aAbsNew;
//STRIP001                  if ( aAbsNew <= aMin )
//STRIP001                  {
//STRIP001                      aMin = aAbsNew;
//STRIP001                      pMin = pTOXMark;
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  // kein Nachfolger wurde gefunden
//STRIP001  // Min oder Max benutzen
//STRIP001  if(!pNew)
//STRIP001  {
//STRIP001      switch(eDir)
//STRIP001      {
//STRIP001      case TOX_PRV:
//STRIP001      case TOX_SAME_PRV:
//STRIP001          pNew = pMax;
//STRIP001          break;
//STRIP001      case TOX_NXT:
//STRIP001      case TOX_SAME_NXT:
//STRIP001          pNew = pMin;
//STRIP001          break;
//STRIP001      default:
//STRIP001          pNew = &rCurTOXMark;
//STRIP001      }
//STRIP001  }
//STRIP001  return *pNew;
//STRIP001 }

/*  */

/*N*/ const SwTOXBaseSection* SwDoc::InsertTableOf( const SwPosition& rPos,
/*N*/                                               const SwTOXBase& rTOX,
/*N*/                                               const SfxItemSet* pSet,
/*N*/                                               BOOL bExpand )
/*N*/ {
/*N*/   StartUndo( UNDO_INSTOX );
/*N*/
/*N*/   SwTOXBaseSection* pNew = new SwTOXBaseSection( rTOX );
/*N*/   String sSectNm( rTOX.GetTOXName() );
/*N*/   sSectNm = GetUniqueTOXBaseName( *rTOX.GetTOXType(), &sSectNm );
/*N*/   pNew->SetTOXName(sSectNm);
/*N*/   pNew->SwSection::SetName(sSectNm);
/*N*/   SwPaM aPam( rPos );
/*N*/   SwSection* pSect = Insert( aPam, *pNew, pSet, FALSE );
/*N*/   if( pSect )
/*N*/   {
/*N*/       SwSectionNode* pSectNd = pSect->GetFmt()->GetSectionNode();
/*N*/       SwSection* pCl = pNew;
/*N*/       pSect->GetFmt()->Add( pCl );
/*N*/       pSectNd->SetNewSection( pNew );
/*N*/
/*N*/       if( bExpand )
/*N*/         {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001             // OD 19.03.2003 #106329# - add value for 2nd parameter = true to
//STRIP001             // indicate, that a creation of a new table of content has to be performed.
//STRIP001             // Value of 1st parameter = default value.
//STRIP001             pNew->Update( 0, true );
/*N*/         }
/*N*/       else if( 1 == rTOX.GetTitle().Len() && IsInReading() )
/*N*/       // insert title of TOX
/*N*/       {
/*?*/           // then insert the headline section
/*?*/           SwNodeIndex aIdx( *pSectNd, +1 );
/*?*/
/*?*/           SwTxtNode* pHeadNd = GetNodes().MakeTxtNode( aIdx,
/*?*/                           GetTxtCollFromPool( RES_POOLCOLL_STANDARD ) );
/*?*/
/*?*/           String sNm( pNew->GetTOXName() );
/*?*/ // ??Resource
/*?*/ sNm.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "_Head" ));
/*?*/
/*?*/           SwSection aSect( TOX_HEADER_SECTION, sNm );
/*?*/
/*?*/           SwNodeIndex aStt( *pHeadNd ); aIdx--;
/*?*/           SwSectionFmt* pSectFmt = MakeSectionFmt( 0 );
/*?*/           GetNodes().InsertSection( aStt, *pSectFmt, aSect, &aIdx,
/*?*/                                               TRUE, FALSE );
/*?*/       }
/*N*/   }
/*N*/   else
/*?*/       delete pNew, pNew = 0;

/*N*/   EndUndo( UNDO_INSTOX );
/*N*/
/*N*/   return pNew;
/*N*/ }



/*N*/ const SwTOXBaseSection* SwDoc::InsertTableOf( ULONG nSttNd, ULONG nEndNd,
/*N*/                                               const SwTOXBase& rTOX,
/*N*/                                               const SfxItemSet* pSet )
/*N*/ {
/*N*/   // check for recursiv TOX
/*N*/   SwNode* pNd = GetNodes()[ nSttNd ];
/*N*/   SwSectionNode* pSectNd = pNd->FindSectionNode();
/*N*/   while( pSectNd )
/*N*/   {
/*?*/       SectionType eT = pSectNd->GetSection().GetType();
/*?*/       if( TOX_HEADER_SECTION == eT || TOX_CONTENT_SECTION == eT )
/*?*/           return 0;
/*?*/       pSectNd = pSectNd->FindStartNode()->FindSectionNode();
/*N*/   }
/*N*/
/*N*/   // create SectionNode around the Nodes
/*N*/   SwTOXBaseSection* pNew = new SwTOXBaseSection( rTOX );
/*N*/
/*N*/   String sSectNm( rTOX.GetTOXName() );
/*N*/   sSectNm = GetUniqueTOXBaseName(*rTOX.GetTOXType(), &sSectNm);
/*N*/   pNew->SetTOXName(sSectNm);
/*N*/   pNew->SwSection::SetName(sSectNm);
/*N*/
/*N*/   SwNodeIndex aStt( GetNodes(), nSttNd ), aEnd( GetNodes(), nEndNd );
/*N*/   SwSectionFmt* pFmt = MakeSectionFmt( 0 );
/*N*/   if(pSet)
/*?*/       pFmt->SetAttr(*pSet);
/*N*/
/*N*/ //    --aEnd;     // im InsertSection ist Ende inclusive
/*N*/
/*N*/   pSectNd = GetNodes().InsertSection( aStt, *pFmt, *pNew, &aEnd );
/*N*/   if( pSectNd )
/*N*/   {
/*N*/       SwSection* pCl = pNew;
/*N*/       pFmt->Add( pCl );
/*N*/       pSectNd->SetNewSection( pNew );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       delete pNew, pNew = 0;
/*?*/       DelSectionFmt( pFmt );
/*N*/   }
/*N*/
/*N*/   return pNew;
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: Aktuelles Verzeichnis ermitteln
 --------------------------------------------------------------------*/

/*N*/ const SwTOXBase* SwDoc::GetCurTOX( const SwPosition& rPos ) const
/*N*/ {
/*N*/   const SwNode& rNd = rPos.nNode.GetNode();
/*N*/   const SwSectionNode* pSectNd = rNd.FindSectionNode();
/*N*/   while( pSectNd )
/*N*/   {
/*N*/       SectionType eT = pSectNd->GetSection().GetType();
/*N*/       if( TOX_CONTENT_SECTION == eT )
/*N*/       {
/*N*/           ASSERT( pSectNd->GetSection().ISA( SwTOXBaseSection ),
/*N*/                   "keine TOXBaseSection!" );
/*N*/           SwTOXBaseSection& rTOXSect = (SwTOXBaseSection&)
/*N*/                                               pSectNd->GetSection();
/*N*/           return &rTOXSect;
/*N*/       }
/*?*/       pSectNd = pSectNd->FindStartNode()->FindSectionNode();
/*N*/   }
/*N*/   return 0;
/*N*/ }
/* -----------------01.09.99 16:01-------------------

 --------------------------------------------------*/
/*N*/ const SwAttrSet& SwDoc::GetTOXBaseAttrSet(const SwTOXBase& rTOXBase) const
/*N*/ {
/*N*/   ASSERT( rTOXBase.ISA( SwTOXBaseSection ), "no TOXBaseSection!" );
/*N*/   const SwTOXBaseSection& rTOXSect = (const SwTOXBaseSection&)rTOXBase;
/*N*/   SwSectionFmt* pFmt = rTOXSect.GetFmt();
/*N*/   ASSERT( pFmt, "invalid TOXBaseSection!" );
/*N*/   return pFmt->GetAttrSet();
/*N*/ }
/* -----------------02.09.99 07:48-------------------

 --------------------------------------------------*/
//STRIP001 const SwTOXBase* SwDoc::GetDefaultTOXBase( TOXTypes eTyp, BOOL bCreate )
//STRIP001 {
//STRIP001  SwTOXBase** prBase;
//STRIP001  switch(eTyp)
//STRIP001  {
//STRIP001  case  TOX_CONTENT:          prBase = &pDefTOXBases->pContBase; break;
//STRIP001  case  TOX_INDEX:            prBase = &pDefTOXBases->pIdxBase;  break;
//STRIP001  case  TOX_USER:             prBase = &pDefTOXBases->pUserBase; break;
//STRIP001  case  TOX_TABLES:           prBase = &pDefTOXBases->pTblBase;  break;
//STRIP001  case  TOX_OBJECTS:          prBase = &pDefTOXBases->pObjBase;  break;
//STRIP001  case  TOX_ILLUSTRATIONS:    prBase = &pDefTOXBases->pIllBase;  break;
//STRIP001  case  TOX_AUTHORITIES:      prBase = &pDefTOXBases->pAuthBase; break;
//STRIP001  }
//STRIP001  if(!(*prBase) && bCreate)
//STRIP001  {
//STRIP001      SwForm aForm(eTyp);
//STRIP001      const SwTOXType* pType = GetTOXType(eTyp, 0);
//STRIP001      (*prBase) = new SwTOXBase(pType, aForm, 0, pType->GetTypeName());
//STRIP001  }
//STRIP001  return (*prBase);
//STRIP001 }
/* -----------------02.09.99 08:06-------------------

 --------------------------------------------------*/
//STRIP001 void SwDoc::SetDefaultTOXBase(const SwTOXBase& rBase)
//STRIP001 {
//STRIP001  SwTOXBase** prBase;
//STRIP001  switch(rBase.GetType())
//STRIP001  {
//STRIP001  case  TOX_CONTENT:          prBase = &pDefTOXBases->pContBase; break;
//STRIP001  case  TOX_INDEX:            prBase = &pDefTOXBases->pIdxBase;  break;
//STRIP001  case  TOX_USER:             prBase = &pDefTOXBases->pUserBase; break;
//STRIP001  case  TOX_TABLES:           prBase = &pDefTOXBases->pTblBase;  break;
//STRIP001  case  TOX_OBJECTS:          prBase = &pDefTOXBases->pObjBase;  break;
//STRIP001  case  TOX_ILLUSTRATIONS:    prBase = &pDefTOXBases->pIllBase;  break;
//STRIP001  case  TOX_AUTHORITIES:      prBase = &pDefTOXBases->pAuthBase; break;
//STRIP001  }
//STRIP001  if(*prBase)
//STRIP001      delete (*prBase);
//STRIP001  (*prBase) = new SwTOXBase(rBase);
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Verzeichnis loeschen
 --------------------------------------------------------------------*/


/*N*/ BOOL SwDoc::DeleteTOX( const SwTOXBase& rTOXBase, BOOL bDelNodes )
/*N*/ {
/*N*/  DBG_BF_ASSERT(0, "STRIP"); return TRUE;//STRIP001    // its only delete the TOX, not the nodes
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ASSERT( rTOXBase.ISA( SwTOXBaseSection ), "keine TOXBaseSection!" );
//STRIP001
//STRIP001  const SwTOXBaseSection& rTOXSect = (const SwTOXBaseSection&)rTOXBase;
//STRIP001  SwSectionFmt* pFmt = rTOXSect.GetFmt();
//STRIP001  if( pFmt )
//STRIP001  {
//STRIP001      StartUndo( UNDO_CLEARTOXRANGE );
//STRIP001
//STRIP001      /* Save the start node of the TOX' section. */
//STRIP001      SwSectionNode * pMyNode = pFmt->GetSectionNode();
//STRIP001      /* Save start node of section's surrounding. */
//STRIP001      SwNode * pStartNd = pMyNode->FindStartNode();
//STRIP001
//STRIP001      /* Look for point where to move the cursors in the area to
//STRIP001         delete to. This is done by first searching forward from the
//STRIP001         end of the TOX' section. If no content node is found behind
//STRIP001         the TOX one is searched before it. If this is not
//STRIP001         successfull, too, insert new text node behind the end of
//STRIP001         the TOX' section. The cursors from the TOX' section will be
//STRIP001         moved to the content node found or the new text node. */
//STRIP001
//STRIP001      /* Set PaM to end of TOX' section and search following content node.
//STRIP001
//STRIP001         aSearchPam will contain the point where to move the cursors
//STRIP001         to. */
//STRIP001      SwPaM aSearchPam(*pMyNode->EndOfSectionNode());
//STRIP001      SwPosition aEndPos(*pStartNd->EndOfSectionNode(), 0);
//STRIP001      if (! aSearchPam.Move() /* no content node found */
//STRIP001          || *aSearchPam.GetPoint() >= aEndPos /* content node found
//STRIP001                                                  outside surrounding */
//STRIP001          )
//STRIP001      {
//STRIP001          /* Set PaM to beginning of TOX' section and search previous
//STRIP001             content node */
//STRIP001          SwPaM aTmpPam(*pMyNode);
//STRIP001          aSearchPam = aTmpPam;
//STRIP001          SwPosition aStartPos(*pStartNd, 0);
//STRIP001
//STRIP001          if ( ! aSearchPam.Move(fnMoveBackward) /* no content node found */
//STRIP001               || *aSearchPam.GetPoint() <= aStartPos  /* content node
//STRIP001                                                          found outside
//STRIP001                                                          surrounding */
//STRIP001               )
//STRIP001          {
//STRIP001              /* There is no content node in the surrounding of
//STRIP001                 TOX'. Append text node behind TOX' section. */
//STRIP001
//STRIP001              SwPosition aInsPos(*pMyNode->EndOfSectionNode(), 0);
//STRIP001              AppendTxtNode(aInsPos);
//STRIP001
//STRIP001              SwPaM aTmpPam1(aInsPos);
//STRIP001              aSearchPam = aTmpPam1;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      /* PaM containing the TOX. */
//STRIP001      SwPaM aPam(*pMyNode->EndOfSectionNode(), *pMyNode);
//STRIP001
//STRIP001      /* Move cursors contained in TOX to point determined above. */
//STRIP001      PaMCorrAbs(aPam, *aSearchPam.GetPoint());
//STRIP001
//STRIP001      if( !bDelNodes )
//STRIP001      {
//STRIP001          SwSections aArr( 0, 4 );
//STRIP001          USHORT nCnt = pFmt->GetChildSections( aArr, SORTSECT_NOT, FALSE );
//STRIP001          for( USHORT n = 0; n < nCnt; ++n )
//STRIP001          {
//STRIP001              SwSection* pSect = aArr[ n ];
//STRIP001              if( TOX_HEADER_SECTION == pSect->GetType() )
//STRIP001              {
//STRIP001                  DelSectionFmt( pSect->GetFmt(), bDelNodes );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      DelSectionFmt( pFmt, bDelNodes );
//STRIP001
//STRIP001      EndUndo( UNDO_CLEARTOXRANGE );
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung:  Verzeichnistypen verwalten
 --------------------------------------------------------------------*/

/*N*/ USHORT SwDoc::GetTOXTypeCount(TOXTypes eTyp) const
/*N*/ {
/*N*/   const SwTOXTypePtr * ppTTypes = pTOXTypes->GetData();
/*N*/   USHORT nCnt = 0;
/*N*/   for( USHORT n = 0; n < pTOXTypes->Count(); ++n, ++ppTTypes )
/*N*/       if( eTyp == (*ppTTypes)->GetType() )
/*N*/           ++nCnt;
/*N*/   return nCnt;
/*N*/ }
/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ const SwTOXType* SwDoc::GetTOXType( TOXTypes eTyp, USHORT nId ) const
/*N*/ {
/*N*/   const SwTOXTypePtr * ppTTypes = pTOXTypes->GetData();
/*N*/   USHORT nCnt = 0;
/*N*/   for( USHORT n = 0; n < pTOXTypes->Count(); ++n, ++ppTTypes )
/*N*/       if( eTyp == (*ppTTypes)->GetType() && nCnt++ == nId )
/*N*/           return (*ppTTypes);
/*N*/   return 0;
/*N*/ }

#ifdef USED


//STRIP001 BOOL SwDoc::DeleteTOXType(TOXTypes eTyp, USHORT nId)
//STRIP001 {
//STRIP001  // was passiert mit den Abhaengigen ??
//STRIP001  //  - alle Marken und alle Verzeichnisse aus dem Text loeschen ??
//STRIP001  SwTOXType* pTOXTyp = (SwTOXType*)GetTOXType( eTyp, nId );
//STRIP001
//STRIP001  ASSERT( !pTOXTyp->GetDepends(), "noch Marken/Verzeichnisse am Typ" );
//STRIP001  delete pTOXTyp;     // ???
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

#endif

/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ const SwTOXType* SwDoc::InsertTOXType( const SwTOXType& rTyp )
/*N*/ {
/*N*/   SwTOXType * pNew = new SwTOXType( rTyp );
/*N*/   pTOXTypes->Insert( pNew, pTOXTypes->Count() );
/*N*/   return pNew;
/*N*/ }
/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ String SwDoc::GetUniqueTOXBaseName( const SwTOXType& rType,
/*N*/                                   const String* pChkStr ) const
/*N*/ {
/*N*/   if(pChkStr && !pChkStr->Len())
/*N*/       pChkStr = 0;
/*N*/   String aName( rType.GetTypeName() );
/*N*/   xub_StrLen nNmLen = aName.Len();
/*N*/
/*N*/   USHORT nNum, nTmp, nFlagSize = ( pSectionFmtTbl->Count() / 8 ) +2;
/*N*/   BYTE* pSetFlags = new BYTE[ nFlagSize ];
/*N*/   memset( pSetFlags, 0, nFlagSize );
/*N*/
/*N*/   const SwSectionNode* pSectNd;
/*N*/   const SwSection* pSect;
        USHORT n=0;
/*N*/   for( n = 0; n < pSectionFmtTbl->Count(); ++n )
/*N*/       if( 0 != ( pSectNd = (*pSectionFmtTbl)[ n ]->GetSectionNode( FALSE ) )&&
/*N*/            TOX_CONTENT_SECTION == (pSect = &pSectNd->GetSection())->GetType())
/*N*/       {
/*N*/           const String& rNm = pSect->GetName();
/*N*/           if( rNm.Match( aName ) == nNmLen )
/*N*/           {
/*N*/               // Nummer bestimmen und das Flag setzen
/*N*/               nNum = (USHORT)rNm.Copy( nNmLen ).ToInt32();
/*N*/               if( nNum-- && nNum < pSectionFmtTbl->Count() )
/*N*/                   pSetFlags[ nNum / 8 ] |= (0x01 << ( nNum & 0x07 ));
/*N*/           }
/*N*/           if( pChkStr && pChkStr->Equals( rNm ) )
/*N*/               pChkStr = 0;
/*N*/       }
/*N*/
/*N*/   if( !pChkStr )
/*N*/   {
/*N*/       // alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/       nNum = pSectionFmtTbl->Count();
/*N*/       for( n = 0; n < nFlagSize; ++n )
/*N*/           if( 0xff != ( nTmp = pSetFlags[ n ] ))
/*N*/           {
/*N*/               // also die Nummer bestimmen
/*N*/               nNum = n * 8;
/*N*/               while( nTmp & 1 )
/*N*/                   ++nNum, nTmp >>= 1;
/*N*/               break;
/*N*/           }
/*N*/   }
/*N*/   delete [] pSetFlags;
/*N*/   if( pChkStr )
/*N*/       return *pChkStr;
/*N*/   return aName += String::CreateFromInt32( ++nNum );
/*N*/ }

/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ BOOL SwDoc::SetTOXBaseName(const SwTOXBase& rTOXBase, const String& rName)
/*N*/ {
/*N*/   ASSERT( rTOXBase.ISA( SwTOXBaseSection ),
/*N*/                   "keine TOXBaseSection!" );
/*N*/   SwTOXBaseSection* pTOX = (SwTOXBaseSection*)&rTOXBase;
/*N*/
/*N*/   String sTmp = GetUniqueTOXBaseName(*rTOXBase.GetTOXType(), &rName);
/*N*/   BOOL bRet = sTmp == rName;
/*N*/   if(bRet)
/*N*/   {
/*?*/       pTOX->SetTOXName(rName);
/*?*/       pTOX->SwTOXBaseSection::SetName(rName);
/*?*/       SetModified();
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
//STRIP001 void SwDoc::SetTOXBaseProtection(const SwTOXBase& rTOXBase, BOOL bProtect)
//STRIP001 {
//STRIP001  ASSERT( rTOXBase.ISA( SwTOXBaseSection ),
//STRIP001                  "keine TOXBaseSection!" );
//STRIP001  SwTOXBaseSection* pTOX = (SwTOXBaseSection*)&rTOXBase;
//STRIP001  if(bProtect != pTOX->IsProtected())
//STRIP001  {
//STRIP001      pTOX->SetProtect(bProtect);
//STRIP001      pTOX->SetProtected(bProtect);
//STRIP001      SetModified();
//STRIP001  }
//STRIP001 }


/*  */

//STRIP001 const SwTxtNode* lcl_FindChapterNode( const SwNode& rNd, BYTE nLvl = 0 )
//STRIP001 {
//STRIP001  const SwNode* pNd = &rNd;
//STRIP001  if( pNd->GetNodes().GetEndOfExtras().GetIndex() > pNd->GetIndex() )
//STRIP001  {
//STRIP001      // then find the "Anchor" (Body) position
//STRIP001      Point aPt;
//STRIP001      SwNode2Layout aNode2Layout( *pNd, pNd->GetIndex() );
//STRIP001      const SwFrm* pFrm = aNode2Layout.GetFrm( &aPt, 0, FALSE );
//STRIP001
//STRIP001      if( pFrm )
//STRIP001      {
//STRIP001          SwPosition aPos( *pNd );
//STRIP001          pNd = GetBodyTxtNode( *pNd->GetDoc(), aPos, *pFrm );
//STRIP001          ASSERT( pNd,    "wo steht der Absatz" );
//STRIP001      }
//STRIP001  }
//STRIP001  return pNd ? pNd->FindOutlineNodeOfLevel( nLvl ) : 0;
//STRIP001 }


/*--------------------------------------------------------------------
     Beschreibung: Verzeichnis-Klasse
 --------------------------------------------------------------------*/

/*N*/ SwTOXBaseSection::SwTOXBaseSection( const SwTOXBase& rBase )
/*N*/   : SwTOXBase( rBase ), SwSection( TOX_CONTENT_SECTION, aEmptyStr )
/*N*/ {
/*N*/   SetProtect( rBase.IsProtected() );
/*N*/   SwSection::SetName( GetTOXName() );
/*N*/ }


/*N*/ SwTOXBaseSection::~SwTOXBaseSection()
/*N*/ {
/*N*/ }


//STRIP001 BOOL SwTOXBaseSection::SetPosAtStartEnd( SwPosition& rPos, BOOL bAtStart ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwSectionNode* pSectNd = GetFmt()->GetSectionNode();
//STRIP001  if( pSectNd )
//STRIP001  {
//STRIP001      SwCntntNode* pCNd;
//STRIP001      xub_StrLen nC = 0;
//STRIP001      if( bAtStart )
//STRIP001      {
//STRIP001          rPos.nNode = *pSectNd;
//STRIP001          pCNd = pSectNd->GetDoc()->GetNodes().GoNext( &rPos.nNode );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rPos.nNode = *pSectNd->EndOfSectionNode();
//STRIP001          pCNd = pSectNd->GetDoc()->GetNodes().GoPrevious( &rPos.nNode );
//STRIP001          if( pCNd ) nC = pCNd->Len();
//STRIP001      }
//STRIP001      rPos.nContent.Assign( pCNd, nC );
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Verzeichnisinhalt zusammensammeln
 --------------------------------------------------------------------*/

/*N*/ void SwTOXBaseSection::Update(const SfxItemSet* pAttr,
/*N*/                               const bool        _bNewTOX )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwSectionNode* pSectNd;
//STRIP001  if( !SwTOXBase::GetRegisteredIn()->GetDepends() ||
//STRIP001      !GetFmt() || 0 == (pSectNd = GetFmt()->GetSectionNode() ) ||
//STRIP001      !pSectNd->GetNodes().IsDocNodes() ||
//STRIP001      IsHiddenFlag() )
//STRIP001      return;
//STRIP001
//STRIP001  if(pAttr)
//STRIP001      GetFmt()->SetAttr(*pAttr);
//STRIP001
//STRIP001  SwDoc* pDoc = (SwDoc*)pSectNd->GetDoc();
//STRIP001     // OD 18.03.2003 #106329# - determine default page description, which
//STRIP001     // will be used by the content nodes, if no approriate one is found.
//STRIP001     const SwPageDesc* pDefaultPageDesc;
//STRIP001     {
//STRIP001         pDefaultPageDesc =
//STRIP001             pSectNd->GetSection().GetFmt()->GetPageDesc().GetPageDesc();
//STRIP001         if ( !_bNewTOX && !pDefaultPageDesc )
//STRIP001         {
//STRIP001             // determine page description of table-of-content
//STRIP001             sal_uInt32 nPgDescNdIdx = pSectNd->GetIndex() + 1;
//STRIP001             sal_uInt32* pPgDescNdIdx = &nPgDescNdIdx;
//STRIP001             pDefaultPageDesc = pSectNd->FindPageDesc( FALSE, pPgDescNdIdx );
//STRIP001             if ( nPgDescNdIdx < pSectNd->GetIndex() )
//STRIP001             {
//STRIP001                 pDefaultPageDesc = 0;
//STRIP001             }
//STRIP001         }
//STRIP001         // OD 28.04.2003 #109166# - consider end node of content section in the
//STRIP001         // node array.
//STRIP001         if ( !pDefaultPageDesc &&
//STRIP001              ( pSectNd->EndOfSectionNode()->GetIndex() <
//STRIP001                  (pSectNd->GetNodes().GetEndOfContent().GetIndex() - 1) )
//STRIP001            )
//STRIP001         {
//STRIP001             // determine page description of content after table-of-content
//STRIP001             SwNodeIndex aIdx( *(pSectNd->EndOfSectionNode()) );
//STRIP001             const SwCntntNode* pNdAfterTOX = pSectNd->GetNodes().GoNext( &aIdx );
//STRIP001             const SwAttrSet& aNdAttrSet = pNdAfterTOX->GetSwAttrSet();
//STRIP001             const SvxBreak eBreak = aNdAttrSet.GetBreak().GetBreak();
//STRIP001             if ( !( eBreak == SVX_BREAK_PAGE_BEFORE ||
//STRIP001                     eBreak == SVX_BREAK_PAGE_BOTH )
//STRIP001                )
//STRIP001             {
//STRIP001                 pDefaultPageDesc = pNdAfterTOX->FindPageDesc( FALSE );
//STRIP001             }
//STRIP001         }
//STRIP001         // OD 28.04.2003 #109166# - consider start node of content section in
//STRIP001         // the node array.
//STRIP001         if ( !pDefaultPageDesc &&
//STRIP001              ( pSectNd->GetIndex() >
//STRIP001                  (pSectNd->GetNodes().GetEndOfContent().StartOfSectionIndex() + 1) )
//STRIP001            )
//STRIP001         {
//STRIP001             // determine page description of content before table-of-content
//STRIP001             SwNodeIndex aIdx( *pSectNd );
//STRIP001             pDefaultPageDesc =
//STRIP001                 pSectNd->GetNodes().GoPrevious( &aIdx )->FindPageDesc( FALSE );
//STRIP001
//STRIP001         }
//STRIP001         if ( !pDefaultPageDesc )
//STRIP001         {
//STRIP001             // determine default page description
//STRIP001             pDefaultPageDesc = &pDoc->GetPageDesc( 0 );
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     pDoc->SetModified();
//STRIP001
//STRIP001  // get current Language
//STRIP001     SwTOXInternational aIntl(  GetLanguage(),
//STRIP001                                TOX_INDEX == GetTOXType()->GetType() ?
//STRIP001                                GetOptions() : 0,
//STRIP001                                GetSortAlgorithm() );
//STRIP001
//STRIP001  aSortArr.DeleteAndDestroy( 0, aSortArr.Count() );
//STRIP001
//STRIP001  // find the first layout node for this TOX, if it only find the content
//STRIP001  // in his own chapter
//STRIP001  const SwTxtNode* pOwnChapterNode = IsFromChapter()
//STRIP001          ? ::lcl_FindChapterNode( *pSectNd, 0 )
//STRIP001          : 0;
//STRIP001
//STRIP001  SwNode2Layout aN2L( *pSectNd );
//STRIP001  ((SwSectionNode*)pSectNd)->DelFrms();
//STRIP001
//STRIP001  // remove old content an insert one empty textnode (to hold the layout!)
//STRIP001  SwTxtNode* pFirstEmptyNd;
//STRIP001  {
//STRIP001      pDoc->DeleteRedline( *pSectNd );
//STRIP001
//STRIP001      SwNodeIndex aSttIdx( *pSectNd, +1 );
//STRIP001      SwNodeIndex aEndIdx( *pSectNd->EndOfSectionNode() );
//STRIP001      pFirstEmptyNd = pDoc->GetNodes().MakeTxtNode( aEndIdx,
//STRIP001                      pDoc->GetTxtCollFromPool( RES_POOLCOLL_TEXT ) );
//STRIP001
//STRIP001      {
//STRIP001          // Task 70995 - save and restore PageDesc and Break Attributes
//STRIP001          SwNodeIndex aNxtIdx( aSttIdx );
//STRIP001          const SwCntntNode* pCNd = aNxtIdx.GetNode().GetCntntNode();
//STRIP001          if( !pCNd )
//STRIP001              pCNd = pDoc->GetNodes().GoNext( &aNxtIdx );
//STRIP001          if( pCNd->GetpSwAttrSet() )
//STRIP001          {
//STRIP001              SfxItemSet aBrkSet( pDoc->GetAttrPool(), aBreakSetRange );
//STRIP001              aBrkSet.Put( *pCNd->GetpSwAttrSet() );
//STRIP001              if( aBrkSet.Count() )
//STRIP001                  pFirstEmptyNd->SwCntntNode::SetAttr( aBrkSet );
//STRIP001          }
//STRIP001      }
//STRIP001      aEndIdx--;
//STRIP001      SwPosition aPos( aEndIdx, SwIndex( pFirstEmptyNd, 0 ));
//STRIP001      pDoc->CorrAbs( aSttIdx, aEndIdx, aPos, TRUE );
//STRIP001
//STRIP001      // delete all before
//STRIP001      DelFlyInRange( aSttIdx, aEndIdx );
//STRIP001      _DelBookmarks( aSttIdx, aEndIdx );
//STRIP001
//STRIP001      pDoc->GetNodes().Delete( aSttIdx, aEndIdx.GetIndex() - aSttIdx.GetIndex() );
//STRIP001
//STRIP001  }
//STRIP001
//STRIP001  //
//STRIP001  // insert title of TOX
//STRIP001  if( GetTitle().Len() )
//STRIP001  {
//STRIP001      // then insert the headline section
//STRIP001      SwNodeIndex aIdx( *pSectNd, +1 );
//STRIP001
//STRIP001      SwTxtNode* pHeadNd = pDoc->GetNodes().MakeTxtNode( aIdx,
//STRIP001                              GetTxtFmtColl( FORM_TITLE ) );
//STRIP001      pHeadNd->Insert( GetTitle(), SwIndex( pHeadNd ));
//STRIP001
//STRIP001      String sNm( GetTOXName() );
//STRIP001 // ??Resource
//STRIP001 sNm.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "_Head" ));
//STRIP001
//STRIP001      SwSection aSect( TOX_HEADER_SECTION, sNm );
//STRIP001
//STRIP001      SwNodeIndex aStt( *pHeadNd ); aIdx--;
//STRIP001      SwSectionFmt* pSectFmt = pDoc->MakeSectionFmt( 0 );
//STRIP001      pDoc->GetNodes().InsertSection( aStt, *pSectFmt, aSect, &aIdx,
//STRIP001                                      TRUE, FALSE );
//STRIP001  }
//STRIP001
//STRIP001  // jetzt waere ein prima Zeitpunkt, um die Numerierung zu updaten
//STRIP001  pDoc->UpdateNumRule();
//STRIP001
//STRIP001  if( GetCreateType() & TOX_MARK )
//STRIP001      UpdateMarks( aIntl, pOwnChapterNode );
//STRIP001
//STRIP001  if( GetCreateType() & TOX_OUTLINELEVEL )
//STRIP001      UpdateOutline( pOwnChapterNode );
//STRIP001
//STRIP001  if( GetCreateType() & TOX_TEMPLATE )
//STRIP001      UpdateTemplate( pOwnChapterNode );
//STRIP001
//STRIP001  if( GetCreateType() & TOX_OLE ||
//STRIP001          TOX_OBJECTS == SwTOXBase::GetType())
//STRIP001      UpdateCntnt( TOX_OLE, pOwnChapterNode );
//STRIP001
//STRIP001  if( GetCreateType() & TOX_TABLE ||
//STRIP001          (TOX_TABLES == SwTOXBase::GetType() && IsFromObjectNames()) )
//STRIP001      UpdateTable( pOwnChapterNode );
//STRIP001
//STRIP001  if( GetCreateType() & TOX_GRAPHIC ||
//STRIP001      (TOX_ILLUSTRATIONS == SwTOXBase::GetType() && IsFromObjectNames()))
//STRIP001      UpdateCntnt( TOX_GRAPHIC, pOwnChapterNode );
//STRIP001
//STRIP001  if( GetSequenceName().Len() && !IsFromObjectNames() &&
//STRIP001      (TOX_TABLES == SwTOXBase::GetType() ||
//STRIP001       TOX_ILLUSTRATIONS == SwTOXBase::GetType() ) )
//STRIP001      UpdateSequence( pOwnChapterNode );
//STRIP001
//STRIP001  if( GetCreateType() & TOX_FRAME )
//STRIP001      UpdateCntnt( TOX_FRAME, pOwnChapterNode );
//STRIP001
//STRIP001  if(TOX_AUTHORITIES == SwTOXBase::GetType())
//STRIP001      UpdateAuthorities( pOwnChapterNode, aIntl );
//STRIP001
//STRIP001  // Bei Bedarf Alphadelimitter einfuegen (nur bei Stichwoertern)
//STRIP001  //
//STRIP001  if( TOX_INDEX == SwTOXBase::GetType() &&
//STRIP001      ( GetOptions() & TOI_ALPHA_DELIMITTER ) )
//STRIP001      InsertAlphaDelimitter( aIntl );
//STRIP001
//STRIP001  // sortierte Liste aller Verzeichnismarken und Verzeichnisbereiche
//STRIP001  void* p = 0;
//STRIP001  String* pStr = 0;
//STRIP001  USHORT nCnt = 0, nFormMax = GetTOXForm().GetFormMax();
//STRIP001  SvStringsDtor aStrArr( (BYTE)nFormMax );
//STRIP001  SvPtrarr aCollArr( (BYTE)nFormMax );
//STRIP001  for( ; nCnt < nFormMax; ++nCnt )
//STRIP001  {
//STRIP001      aCollArr.Insert( p, nCnt );
//STRIP001      aStrArr.Insert( pStr, nCnt );
//STRIP001  }
//STRIP001
//STRIP001  SwNodeIndex aInsPos( *pFirstEmptyNd, 1 );
//STRIP001  for( nCnt = 0; nCnt < aSortArr.Count(); ++nCnt )
//STRIP001  {
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001      // setze den Text in das Verzeichniss
//STRIP001      USHORT nLvl = aSortArr[ nCnt ]->GetLevel();
//STRIP001      SwTxtFmtColl* pColl = (SwTxtFmtColl*)aCollArr[ nLvl ];
//STRIP001      if( !pColl )
//STRIP001      {
//STRIP001          pColl = GetTxtFmtColl( nLvl );
//STRIP001          aCollArr.Remove( nLvl );
//STRIP001          p = pColl;
//STRIP001          aCollArr.Insert( p , nLvl );
//STRIP001      }
//STRIP001
//STRIP001      // Generierung: dynamische TabStops setzen
//STRIP001      SwTxtNode* pTOXNd = pDoc->GetNodes().MakeTxtNode( aInsPos , pColl );
//STRIP001      aSortArr[ nCnt ]->pTOXNd = pTOXNd;
//STRIP001
//STRIP001      // Generierung: Form auswerten und Platzhalter
//STRIP001      //              fuer die Seitennummer eintragen
//STRIP001      //if it is a TOX_INDEX and the SwForm IsCommaSeparated()
//STRIP001      // then a range of entries must be generated into one paragraph
//STRIP001      USHORT nRange = 1;
//STRIP001      if(TOX_INDEX == SwTOXBase::GetType() &&
//STRIP001              GetTOXForm().IsCommaSeparated() &&
//STRIP001              aSortArr[nCnt]->GetType() == TOX_SORT_INDEX)
//STRIP001      {
//STRIP001          const SwTOXMark& rMark = aSortArr[nCnt]->pTxtMark->GetTOXMark();
//STRIP001          const String sPrimKey = rMark.GetPrimaryKey();
//STRIP001          const String sSecKey = rMark.GetSecondaryKey();
//STRIP001          const SwTOXMark* pNextMark = 0;
//STRIP001          while(aSortArr.Count() > (nCnt + nRange)&&
//STRIP001                  aSortArr[nCnt + nRange]->GetType() == TOX_SORT_INDEX &&
//STRIP001                  0 != (pNextMark = &(aSortArr[nCnt + nRange]->pTxtMark->GetTOXMark())) &&
//STRIP001                  pNextMark->GetPrimaryKey() == sPrimKey &&
//STRIP001                  pNextMark->GetSecondaryKey() == sSecKey)
//STRIP001              nRange++;
//STRIP001      }
//STRIP001         // OD 18.03.2003 #106329# - pass node index of table-of-content section
//STRIP001         // and default page description to method <GenerateText(..)>.
//STRIP001         GenerateText( nCnt, nRange, aStrArr, pSectNd->GetIndex(), pDefaultPageDesc );
//STRIP001      nCnt += nRange - 1;
//STRIP001  }
//STRIP001
//STRIP001  // delete the first dummy node and remove all Cursor into the prev node
//STRIP001  aInsPos = *pFirstEmptyNd;
//STRIP001  {
//STRIP001      SwPaM aCorPam( *pFirstEmptyNd );
//STRIP001      aCorPam.GetPoint()->nContent.Assign( pFirstEmptyNd, 0 );
//STRIP001      if( !aCorPam.Move( fnMoveForward ) )
//STRIP001          aCorPam.Move( fnMoveBackward );
//STRIP001      SwNodeIndex aEndIdx( aInsPos, 1 );
//STRIP001      pDoc->CorrAbs( aInsPos, aEndIdx, *aCorPam.GetPoint(), TRUE );
//STRIP001
//STRIP001      // Task 70995 - save and restore PageDesc and Break Attributes
//STRIP001      if( pFirstEmptyNd->GetpSwAttrSet() )
//STRIP001      {
//STRIP001          if( GetTitle().Len() )
//STRIP001              aEndIdx = *pSectNd;
//STRIP001          else
//STRIP001              aEndIdx = *pFirstEmptyNd;
//STRIP001          SwCntntNode* pCNd = pDoc->GetNodes().GoNext( &aEndIdx );
//STRIP001          pCNd->SetAttr( *pFirstEmptyNd->GetpSwAttrSet() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // now create the new Frames
//STRIP001  ULONG nIdx = pSectNd->GetIndex();
//STRIP001  // don't delete if index is empty
//STRIP001  if(nIdx + 2 < pSectNd->EndOfSectionIndex())
//STRIP001      pDoc->GetNodes().Delete( aInsPos, 1 );
//STRIP001
//STRIP001  aN2L.RestoreUpperFrms( pDoc->GetNodes(), nIdx, nIdx + 1 );
//STRIP001  if(pDoc->GetRootFrm())
//STRIP001      SwFrm::CheckPageDescs( (SwPageFrm*)pDoc->GetRootFrm()->Lower() );
//STRIP001
//STRIP001  SetProtect( SwTOXBase::IsProtected() );
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: AlphaDelimitter einfuegen
 --------------------------------------------------------------------*/


//STRIP001 void SwTOXBaseSection::InsertAlphaDelimitter( const SwTOXInternational& rIntl )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  String sDeli, sLastDeli;
//STRIP001  USHORT  i = 0;
//STRIP001  while( i < aSortArr.Count() )
//STRIP001  {
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001      USHORT nLevel = aSortArr[i]->GetLevel();
//STRIP001
//STRIP001      // Alpha-Delimitter ueberlesen
//STRIP001      if( nLevel == FORM_ALPHA_DELIMITTER )
//STRIP001          continue;
//STRIP001
//STRIP001         String sMyString, sMyStringReading;
//STRIP001         aSortArr[i]->GetTxt( sMyString, sMyStringReading );
//STRIP001
//STRIP001         sDeli = rIntl.GetIndexKey( sMyString, sMyStringReading,
//STRIP001                                    aSortArr[i]->GetLocale() );
//STRIP001
//STRIP001      // Delimitter schon vorhanden ??
//STRIP001      if( sDeli.Len() && sLastDeli != sDeli )
//STRIP001      {
//STRIP001          // alle kleiner Blank wollen wir nicht haben -> sind Sonderzeichen
//STRIP001          if( ' ' <= sDeli.GetChar( 0 ) )
//STRIP001          {
//STRIP001                 SwTOXCustom* pCst = new SwTOXCustom( sDeli, FORM_ALPHA_DELIMITTER,
//STRIP001                                                      rIntl, aSortArr[i]->GetLocale() );
//STRIP001              aSortArr.Insert( pCst, i++ );
//STRIP001          }
//STRIP001          sLastDeli = sDeli;
//STRIP001      }
//STRIP001
//STRIP001      // Skippen bis gleibhes oder kleineres Level erreicht ist
//STRIP001      do {
//STRIP001          i++;
//STRIP001      } while (i < aSortArr.Count() && aSortArr[i]->GetLevel() > nLevel);
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Template  auswerten
 --------------------------------------------------------------------*/

//STRIP001 SwTxtFmtColl* SwTOXBaseSection::GetTxtFmtColl( USHORT nLevel )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  const String& rName = GetTOXForm().GetTemplate( nLevel );
//STRIP001  SwTxtFmtColl* pColl = rName.Len() ? pDoc->FindTxtFmtCollByName(rName) :0;
//STRIP001  if( !pColl )
//STRIP001  {
//STRIP001      USHORT nPoolFmt;
//STRIP001      const TOXTypes eType = SwTOXBase::GetType();
//STRIP001      switch( eType )
//STRIP001      {
//STRIP001      case TOX_INDEX:         nPoolFmt = RES_POOLCOLL_TOX_IDXH;       break;
//STRIP001      case TOX_USER:
//STRIP001          if( nLevel < 6 )
//STRIP001              nPoolFmt = RES_POOLCOLL_TOX_USERH;
//STRIP001          else
//STRIP001              nPoolFmt = RES_POOLCOLL_TOX_USER6 - 6;
//STRIP001          break;
//STRIP001      break;
//STRIP001      case TOX_ILLUSTRATIONS: nPoolFmt = RES_POOLCOLL_TOX_ILLUSH;     break;
//STRIP001      case TOX_OBJECTS:       nPoolFmt = RES_POOLCOLL_TOX_OBJECTH;    break;
//STRIP001      case TOX_TABLES:        nPoolFmt = RES_POOLCOLL_TOX_TABLESH;    break;
//STRIP001      case TOX_AUTHORITIES:   nPoolFmt = RES_POOLCOLL_TOX_AUTHORITIESH; break;
//STRIP001
//STRIP001      case TOX_CONTENT:
//STRIP001          // im Content Bereich gibt es einen Sprung!
//STRIP001          if( nLevel < 6 )
//STRIP001              nPoolFmt = RES_POOLCOLL_TOX_CNTNTH;
//STRIP001          else
//STRIP001              nPoolFmt = RES_POOLCOLL_TOX_CNTNT6 - 6;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if(eType == TOX_AUTHORITIES && nLevel)
//STRIP001          nPoolFmt = nPoolFmt + 1;
//STRIP001      else if(eType == TOX_INDEX && nLevel)
//STRIP001      {
//STRIP001          //pool: Level 1,2,3, Delimiter
//STRIP001          //SwForm: Delimiter, Level 1,2,3
//STRIP001          nPoolFmt += 1 == nLevel ? nLevel + 3 : nLevel - 1;
//STRIP001      }
//STRIP001      else
//STRIP001          nPoolFmt += nLevel;
//STRIP001      pColl = pDoc->GetTxtCollFromPool( nPoolFmt );
//STRIP001  }
//STRIP001  return pColl;
//STRIP001 }


/*--------------------------------------------------------------------
     Beschreibung: Aus Markierungen erzeugen
 --------------------------------------------------------------------*/

//STRIP001 void SwTOXBaseSection::UpdateMarks( const SwTOXInternational& rIntl,
//STRIP001                                  const SwTxtNode* pOwnChapterNode )
//STRIP001 {
//STRIP001  const SwModify* pType = SwTOXBase::GetRegisteredIn();
//STRIP001  if( !pType->GetDepends() )
//STRIP001      return;
//STRIP001
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  TOXTypes eTOXTyp = GetTOXType()->GetType();
//STRIP001  SwClientIter aIter( *(SwModify*)pType );
//STRIP001
//STRIP001  SwTxtTOXMark* pTxtMark;
//STRIP001  SwTOXMark* pMark;
//STRIP001  for( pMark = (SwTOXMark*)aIter.First( TYPE( SwTOXMark )); pMark;
//STRIP001      pMark = (SwTOXMark*)aIter.Next() )
//STRIP001  {
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001      if( pMark->GetTOXType()->GetType() == eTOXTyp &&
//STRIP001          0 != ( pTxtMark = pMark->GetTxtTOXMark() ) )
//STRIP001      {
//STRIP001          const SwTxtNode* pTOXSrc = pTxtMark->GetpTxtNd();
//STRIP001          // nur TOXMarks einfuegen die im Doc stehen
//STRIP001          // nicht die, die im UNDO stehen
//STRIP001          //
//STRIP001          // if selected use marks from the same chapter only
//STRIP001          if( pTOXSrc->GetNodes().IsDocNodes() &&
//STRIP001              pTOXSrc->GetTxt().Len() && pTOXSrc->GetDepends() &&
//STRIP001              pTOXSrc->GetFrm() &&
//STRIP001              (!IsFromChapter() ||
//STRIP001                  ::lcl_FindChapterNode( *pTOXSrc, 0 ) == pOwnChapterNode ))
//STRIP001          {
//STRIP001              SwTOXSortTabBase* pBase = 0;
//STRIP001              if(TOX_INDEX == eTOXTyp)
//STRIP001              {
//STRIP001                  // Stichwortverzeichnismarkierung
//STRIP001                     ::com::sun::star::lang::Locale aLocale;
//STRIP001                     if ( pBreakIt->xBreak.is() )
//STRIP001                     {
//STRIP001                         aLocale = pBreakIt->GetLocale(
//STRIP001                                         pTOXSrc->GetLang( *pTxtMark->GetStart() ) );
//STRIP001                     }
//STRIP001
//STRIP001                  pBase = new SwTOXIndex( *pTOXSrc, pTxtMark,
//STRIP001                                             GetOptions(), FORM_ENTRY, rIntl, aLocale );
//STRIP001                  InsertSorted(pBase);
//STRIP001                  if(GetOptions() & TOI_KEY_AS_ENTRY &&
//STRIP001                      pTxtMark->GetTOXMark().GetPrimaryKey().Len())
//STRIP001                  {
//STRIP001                      pBase = new SwTOXIndex( *pTOXSrc, pTxtMark,
//STRIP001                                                 GetOptions(), FORM_PRIMARY_KEY, rIntl, aLocale );
//STRIP001                      InsertSorted(pBase);
//STRIP001                      if(pTxtMark->GetTOXMark().GetSecondaryKey().Len())
//STRIP001                      {
//STRIP001                          pBase = new SwTOXIndex( *pTOXSrc, pTxtMark,
//STRIP001                                                     GetOptions(), FORM_SECONDARY_KEY, rIntl, aLocale );
//STRIP001                          InsertSorted(pBase);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( TOX_USER == eTOXTyp ||
//STRIP001                  pMark->GetLevel() <= GetLevel())
//STRIP001              {   // Inhaltsberzeichnismarkierung
//STRIP001                  // also used for user marks
//STRIP001                  pBase = new SwTOXContent( *pTOXSrc, pTxtMark, rIntl );
//STRIP001                  InsertSorted(pBase);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*--------------------------------------------------------------------
     Beschreibung:  Verzeichnisinhalt aus Gliederungsebene generieren
 --------------------------------------------------------------------*/


//STRIP001 void SwTOXBaseSection::UpdateOutline( const SwTxtNode* pOwnChapterNode )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  SwNodes& rNds = pDoc->GetNodes();
//STRIP001
//STRIP001  const SwOutlineNodes& rOutlNds = rNds.GetOutLineNds();
//STRIP001  for( USHORT n = 0; n < rOutlNds.Count(); ++n )
//STRIP001  {
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001      SwTxtNode* pTxtNd = rOutlNds[ n ]->GetTxtNode();
//STRIP001      if( pTxtNd && pTxtNd->Len() && pTxtNd->GetDepends() &&
//STRIP001          USHORT(pTxtNd->GetTxtColl()->GetOutlineLevel()+1) <= GetLevel() &&
//STRIP001          pTxtNd->GetFrm() &&
//STRIP001          ( !IsFromChapter() ||
//STRIP001             ::lcl_FindChapterNode( *pTxtNd, 0 ) == pOwnChapterNode ))
//STRIP001      {
//STRIP001             SwTOXPara * pNew = new SwTOXPara( *pTxtNd, TOX_OUTLINELEVEL );
//STRIP001          InsertSorted( pNew );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Verzeichnisinhalt aus Vorlagenbereichen generieren
 --------------------------------------------------------------------*/

//STRIP001 void SwTOXBaseSection::UpdateTemplate( const SwTxtNode* pOwnChapterNode )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  for(USHORT i = 0; i < MAXLEVEL; i++)
//STRIP001  {
//STRIP001      String sTmpStyleNames = GetStyleNames(i);
//STRIP001      USHORT nTokenCount = sTmpStyleNames.GetTokenCount(TOX_STYLE_DELIMITER);
//STRIP001      for( USHORT nStyle = 0; nStyle < nTokenCount; ++nStyle )
//STRIP001      {
//STRIP001          SwTxtFmtColl* pColl = pDoc->FindTxtFmtCollByName(
//STRIP001                                  sTmpStyleNames.GetToken( nStyle,
//STRIP001                                                  TOX_STYLE_DELIMITER ));
//STRIP001          //TODO: no outline Collections in content indexes if OutlineLevels are already included
//STRIP001          if( !pColl ||
//STRIP001              ( TOX_CONTENT == SwTOXBase::GetType() &&
//STRIP001                GetCreateType() & TOX_OUTLINELEVEL &&
//STRIP001                NO_NUMBERING != pColl->GetOutlineLevel() ) )
//STRIP001              continue;
//STRIP001
//STRIP001          SwClientIter aIter( *pColl );
//STRIP001          SwTxtNode* pTxtNd = (SwTxtNode*)aIter.First( TYPE( SwTxtNode ));
//STRIP001          for( ; pTxtNd; pTxtNd = (SwTxtNode*)aIter.Next() )
//STRIP001          {
//STRIP001              ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001              if( pTxtNd->GetTxt().Len() && pTxtNd->GetFrm() &&
//STRIP001                  pTxtNd->GetNodes().IsDocNodes() &&
//STRIP001                  ( !IsFromChapter() || pOwnChapterNode ==
//STRIP001                      ::lcl_FindChapterNode( *pTxtNd, 0 ) ) )
//STRIP001              {
//STRIP001                  SwTOXPara * pNew = new SwTOXPara( *pTxtNd, TOX_TEMPLATE, i + 1 );
//STRIP001                  InsertSorted(pNew);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/* -----------------14.07.99 09:59-------------------
    Description: generate content from sequence fields
 --------------------------------------------------*/
//STRIP001 void SwTOXBaseSection::UpdateSequence( const SwTxtNode* pOwnChapterNode )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  SwFieldType* pSeqFld = pDoc->GetFldType(RES_SETEXPFLD, GetSequenceName());
//STRIP001  if(!pSeqFld)
//STRIP001      return;
//STRIP001
//STRIP001  SwClientIter aIter( *pSeqFld );
//STRIP001  SwFmtFld* pFmtFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
//STRIP001  for( ; pFmtFld; pFmtFld = (SwFmtFld*)aIter.Next() )
//STRIP001  {
//STRIP001      const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001      if(!pTxtFld)
//STRIP001          continue;
//STRIP001      const SwTxtNode& rTxtNode = pTxtFld->GetTxtNode();
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001      if( rTxtNode.GetTxt().Len() && rTxtNode.GetFrm() &&
//STRIP001          rTxtNode.GetNodes().IsDocNodes() &&
//STRIP001          ( !IsFromChapter() ||
//STRIP001              ::lcl_FindChapterNode( rTxtNode, 0 ) == pOwnChapterNode ) )
//STRIP001      {
//STRIP001          SwTOXPara * pNew = new SwTOXPara( rTxtNode, TOX_SEQUENCE, 1 );
//STRIP001          //set indexes if the number or the reference text are to be displayed
//STRIP001          if( GetCaptionDisplay() == CAPTION_TEXT )
//STRIP001          {
//STRIP001              pNew->SetStartIndex(
//STRIP001                  SwGetExpField::GetReferenceTextPos( *pFmtFld, *pDoc ));
//STRIP001          }
//STRIP001          else if(GetCaptionDisplay() == CAPTION_NUMBER)
//STRIP001          {
//STRIP001              pNew->SetEndIndex(*pTxtFld->GetStart() + 1);
//STRIP001          }
//STRIP001          InsertSorted(pNew);
//STRIP001      }
//STRIP001  }
//STRIP001 }
/* -----------------15.09.99 14:18-------------------

 --------------------------------------------------*/
//STRIP001 void SwTOXBaseSection::UpdateAuthorities( const SwTxtNode* pOwnChapterNode,
//STRIP001                                          const SwTOXInternational& rIntl )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  SwFieldType* pAuthFld = pDoc->GetFldType(RES_AUTHORITY, aEmptyStr);
//STRIP001  if(!pAuthFld)
//STRIP001      return;
//STRIP001
//STRIP001  SwClientIter aIter( *pAuthFld );
//STRIP001  SwFmtFld* pFmtFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
//STRIP001  for( ; pFmtFld; pFmtFld = (SwFmtFld*)aIter.Next() )
//STRIP001  {
//STRIP001      const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001      //undo
//STRIP001      if(!pTxtFld)
//STRIP001          continue;
//STRIP001      const SwTxtNode& rTxtNode = pTxtFld->GetTxtNode();
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001 //       const SwTxtNode* pChapterCompareNode = 0;
//STRIP001
//STRIP001      if( rTxtNode.GetTxt().Len() && rTxtNode.GetFrm() &&
//STRIP001          rTxtNode.GetNodes().IsDocNodes() /*&&
//STRIP001          (!IsFromChapter() || pChapterCompareNode == pOwnChapterNode) */)
//STRIP001      {
//STRIP001             //#106485# the body node has to be used!
//STRIP001             SwCntntFrm *pFrm = rTxtNode.GetFrm();
//STRIP001             SwPosition aFldPos(rTxtNode);
//STRIP001             const SwTxtNode* pTxtNode = 0;
//STRIP001             if(pFrm && !pFrm->IsInDocBody())
//STRIP001                 pTxtNode = GetBodyTxtNode( *pDoc, aFldPos, *pFrm );
//STRIP001             if(!pTxtNode)
//STRIP001                 pTxtNode = &rTxtNode;
//STRIP001             SwTOXAuthority* pNew = new SwTOXAuthority( *pTxtNode, *pFmtFld, rIntl );
//STRIP001
//STRIP001          InsertSorted(pNew);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung:  Verzeichnisinhalt aus Inhaltsformen generieren
                    OLE, Grafik, Frame
                    Achtung: Spezielle Section !
 --------------------------------------------------------------------*/
/*
            nPos = pNd->GetIndex();
            if( nPos < pNd->GetNodes().GetEndOfExtras().GetIndex() )
            {
                // dann die "Anker" (Body) Position holen.
                Point aPt;
                const SwCntntFrm* pFrm = pNd->GetFrm( &aPt, 0, FALSE );
                if( pFrm )
                {
                    SwPosition aPos( *pNd );
                    SwDoc* pDoc = (SwDoc*)pNd->GetDoc();
#ifndef PRODUCT
                    ASSERT( GetBodyTxtNode( pDoc, aPos, pFrm ),
                            "wo steht der Absatz" );
#else
                    GetBodyTxtNode( pDoc, aPos, pFrm );
#endif
                    nPos = aPos.nNode.GetIndex();
                    nCntPos = aPos.nContent.GetIndex();
                }
            }



 */

//STRIP001 long lcl_IsSOObject( const SvGlobalName& rFactoryNm )
//STRIP001 {
//STRIP001  static struct _SoObjType {
//STRIP001      long nFlag;
//STRIP001      // GlobalNameId
//STRIP001      struct _GlobalNameIds {
//STRIP001          UINT32 n1;
//STRIP001          USHORT n2, n3;
//STRIP001          BYTE b8, b9, b10, b11, b12, b13, b14, b15;
//STRIP001         } aGlNmIds[4];
//STRIP001  } aArr[] = {
//STRIP001      { TOO_MATH,
//STRIP001             {BF_SO3_SM_CLASSID_60, BF_SO3_SM_CLASSID_50,
//STRIP001                 BF_SO3_SM_CLASSID_40, BF_SO3_SM_CLASSID_30 }},
//STRIP001      { TOO_CHART,
//STRIP001             {BF_SO3_SCH_CLASSID_60, BF_SO3_SCH_CLASSID_50,
//STRIP001                 BF_SO3_SCH_CLASSID_40, BF_SO3_SCH_CLASSID_30 }},
//STRIP001      { TOO_CALC,
//STRIP001             {BF_SO3_SC_CLASSID_60, BF_SO3_SC_CLASSID_50,
//STRIP001                 BF_SO3_SC_CLASSID_40, BF_SO3_SC_CLASSID_30 }},
//STRIP001      { TOO_DRAW_IMPRESS,
//STRIP001             {BF_SO3_SIMPRESS_CLASSID_60, BF_SO3_SIMPRESS_CLASSID_50,
//STRIP001                 BF_SO3_SIMPRESS_CLASSID_40, BF_SO3_SIMPRESS_CLASSID_30 }},
//STRIP001      { TOO_DRAW_IMPRESS,
//STRIP001             {BF_SO3_SDRAW_CLASSID_60, BF_SO3_SDRAW_CLASSID_50 }},
//STRIP001      { 0,0 }
//STRIP001  };
//STRIP001
//STRIP001  long nRet = 0;
//STRIP001  for( const _SoObjType* pArr = aArr; !nRet && pArr->nFlag; ++pArr )
//STRIP001         for ( int n = 0; n < 4; ++n )
//STRIP001      {
//STRIP001          const _SoObjType::_GlobalNameIds& rId = pArr->aGlNmIds[ n ];
//STRIP001          if( !rId.n1 )
//STRIP001              break;
//STRIP001          SvGlobalName aGlbNm( rId.n1, rId.n2, rId.n3,
//STRIP001                      rId.b8, rId.b9, rId.b10, rId.b11,
//STRIP001                      rId.b12, rId.b13, rId.b14, rId.b15 );
//STRIP001          if( rFactoryNm == aGlbNm )
//STRIP001          {
//STRIP001              nRet = pArr->nFlag;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SwTOXBaseSection::UpdateCntnt( SwTOXElement eType,
//STRIP001                                  const SwTxtNode* pOwnChapterNode )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  SwNodes& rNds = pDoc->GetNodes();
//STRIP001  // auf den 1. Node der 1. Section
//STRIP001  ULONG nIdx = rNds.GetEndOfAutotext().StartOfSectionIndex() + 2,
//STRIP001       nEndIdx = rNds.GetEndOfAutotext().GetIndex();
//STRIP001
//STRIP001  while( nIdx < nEndIdx )
//STRIP001  {
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001      SwNode* pNd = rNds[ nIdx ];
//STRIP001      SwCntntNode* pCNd = 0;
//STRIP001      switch( eType )
//STRIP001      {
//STRIP001      case TOX_FRAME:
//STRIP001          if( !pNd->IsNoTxtNode() )
//STRIP001          {
//STRIP001              pCNd = pNd->GetCntntNode();
//STRIP001              if( !pCNd )
//STRIP001              {
//STRIP001                  SwNodeIndex aTmp( *pNd );
//STRIP001                  pCNd = rNds.GoNext( &aTmp );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      case TOX_GRAPHIC:
//STRIP001          if( pNd->IsGrfNode() )
//STRIP001              pCNd = (SwCntntNode*)pNd;
//STRIP001          break;
//STRIP001      case TOX_OLE:
//STRIP001          if( pNd->IsOLENode() )
//STRIP001          {
//STRIP001              BOOL bInclude = TRUE;
//STRIP001              if(TOX_OBJECTS == SwTOXBase::GetType())
//STRIP001              {
//STRIP001                  SwOLENode* pOLENode = pNd->GetOLENode();
//STRIP001                  long nOLEOptions = GetOLEOptions();
//STRIP001                  SwOLEObj& rOLEObj = pOLENode->GetOLEObj();
//STRIP001
//STRIP001                  if( rOLEObj.IsOleRef() )    //Noch nicht geladen
//STRIP001                  {
//STRIP001                      const SotFactory* pFact = rOLEObj.GetOleRef()->GetSvFactory();
//STRIP001                      long nObj = ::lcl_IsSOObject( *pFact );
//STRIP001                      bInclude = ( nOLEOptions & TOO_OTHER )
//STRIP001                                      ? 0 == nObj
//STRIP001                                      : 0 != (nOLEOptions & nObj);
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      DBG_ERROR("OLE-object nicht geladen?");
//STRIP001                      bInclude = FALSE;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if(bInclude)
//STRIP001                  pCNd = (SwCntntNode*)pNd;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if( pCNd )
//STRIP001      {
//STRIP001          //find node in body text
//STRIP001          Point aPt;
//STRIP001          const SwCntntFrm* pFrm = pCNd->GetFrm( &aPt, 0, FALSE );
//STRIP001          USHORT nSetLevel = USHRT_MAX;
//STRIP001
//STRIP001          if( IsLevelFromChapter() )
//STRIP001          {
//STRIP001              const SwTxtNode* pOutlNd = ::lcl_FindChapterNode( *pCNd,
//STRIP001                                                      MAXLEVEL - 1 );
//STRIP001              if( pOutlNd )
//STRIP001              {
//STRIP001                  USHORT nTmp = pOutlNd->GetTxtColl()->GetOutlineLevel();
//STRIP001                  if( nTmp < NO_NUMBERING )
//STRIP001                      nSetLevel = nTmp + 1;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( pCNd->GetFrm() && ( !IsFromChapter() ||
//STRIP001                  ::lcl_FindChapterNode( *pCNd, 0 ) == pOwnChapterNode ))
//STRIP001          {
//STRIP001              SwTOXPara * pNew = new SwTOXPara( *pCNd, eType,
//STRIP001                          USHRT_MAX != nSetLevel ? nSetLevel : FORM_ALPHA_DELIMITTER );
//STRIP001              InsertSorted( pNew );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      nIdx = pNd->FindStartNode()->EndOfSectionIndex() + 2;   // 2 == End-/StartNode
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung:  Tabelleneintraege zusammensuchen
 --------------------------------------------------------------------*/

//STRIP001 void SwTOXBaseSection::UpdateTable( const SwTxtNode* pOwnChapterNode )
//STRIP001 {
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  SwNodes& rNds = pDoc->GetNodes();
//STRIP001  const SwFrmFmts& rArr = *pDoc->GetTblFrmFmts();
//STRIP001
//STRIP001  for( USHORT n = 0; n < rArr.Count(); ++n )
//STRIP001  {
//STRIP001      ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001      SwTable* pTmpTbl = SwTable::FindTable( rArr[ n ] );
//STRIP001      SwTableBox* pFBox;
//STRIP001      if( pTmpTbl && 0 != (pFBox = pTmpTbl->GetTabSortBoxes()[0] ) &&
//STRIP001          pFBox->GetSttNd() && pFBox->GetSttNd()->GetNodes().IsDocNodes() )
//STRIP001      {
//STRIP001          const SwTableNode* pTblNd = pFBox->GetSttNd()->FindTableNode();
//STRIP001          SwNodeIndex aCntntIdx( *pTblNd, 1 );
//STRIP001
//STRIP001          SwCntntNode* pCNd;
//STRIP001          while( 0 != ( pCNd = rNds.GoNext( &aCntntIdx ) ) &&
//STRIP001              aCntntIdx.GetIndex() < pTblNd->EndOfSectionIndex() )
//STRIP001          {
//STRIP001              if( pCNd->GetFrm() && (!IsFromChapter() ||
//STRIP001                  ::lcl_FindChapterNode( *pCNd, 0 ) == pOwnChapterNode ))
//STRIP001              {
//STRIP001                  SwTOXTable * pNew = new SwTOXTable( *pCNd );
//STRIP001                  if( IsLevelFromChapter() )
//STRIP001                  {
//STRIP001                      const SwTxtNode* pOutlNd =
//STRIP001                          ::lcl_FindChapterNode( *pCNd, MAXLEVEL - 1 );
//STRIP001                      if( pOutlNd )
//STRIP001                      {
//STRIP001                          USHORT nTmp = pOutlNd->GetTxtColl()->GetOutlineLevel();
//STRIP001                          if( nTmp < NO_NUMBERING )
//STRIP001                              pNew->SetLevel( nTmp + 1 );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  InsertSorted(pNew);
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung:  String generieren anhand der Form
                    SonderZeichen 0-31 und 255 entfernen
 --------------------------------------------------------------------*/

//STRIP001 String lcl_GetNumString( const SwTOXSortTabBase& rBase )
//STRIP001 {
//STRIP001  String sRet;
//STRIP001
//STRIP001  if( !rBase.pTxtMark && rBase.aTOXSources.Count() > 0 )
//STRIP001  {   // nur wenn es keine Marke ist
//STRIP001      const SwTxtNode* pNd = rBase.aTOXSources[0].pNd->GetTxtNode();
//STRIP001      if( pNd )
//STRIP001      {
//STRIP001          const SwNodeNum* pNum;
//STRIP001          const SwNumRule* pRule;
//STRIP001
//STRIP001          if( (( 0 != ( pNum = pNd->GetNum() ) &&
//STRIP001                  0 != ( pRule = pNd->GetNumRule() )) ||
//STRIP001                  ( 0 != ( pNum = pNd->GetOutlineNum() ) &&
//STRIP001                  0 != ( pRule = pNd->GetDoc()->GetOutlineNumRule() ) ) ) &&
//STRIP001              pNum->GetLevel() < MAXLEVEL )
//STRIP001              sRet = pRule->MakeNumString( *pNum );
//STRIP001      }
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

// OD 18.03.2003 #106329# - add parameter <_TOXSectNdIdx> and <_pDefaultPageDesc>
// in order to control, which page description is used, no appropriate one is found.
//STRIP001 void SwTOXBaseSection::GenerateText( USHORT nArrayIdx,
//STRIP001                                      USHORT nCount,
//STRIP001                                      SvStringsDtor& rTabForms,
//STRIP001                                      const sal_uInt32   _nTOXSectNdIdx,
//STRIP001                                      const SwPageDesc*  _pDefaultPageDesc )
//STRIP001 {
//STRIP001  LinkStructArr   aLinkArr;
//STRIP001  SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
//STRIP001  ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001
//STRIP001  //pTOXNd is only set at the first mark
//STRIP001  SwTxtNode* pTOXNd = (SwTxtNode*)aSortArr[nArrayIdx]->pTOXNd;
//STRIP001  String& rTxt = (String&)pTOXNd->GetTxt();
//STRIP001  rTxt.Erase();
//STRIP001  for(USHORT nIndex = nArrayIdx; nIndex < nArrayIdx + nCount; nIndex++)
//STRIP001  {
//STRIP001      if(nIndex > nArrayIdx)
//STRIP001          rTxt.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ", " )); // comma separation
//STRIP001      // String mit dem Pattern aus der Form initialisieren
//STRIP001      const SwTOXSortTabBase& rBase = *aSortArr[nIndex];
//STRIP001      USHORT nLvl = rBase.GetLevel();
//STRIP001      ASSERT( nLvl < GetTOXForm().GetFormMax(), "ungueltiges FORM_LEVEL");
//STRIP001
//STRIP001      SvxTabStopItem aTStops( 0, 0 );
//STRIP001      xub_StrLen nLinkStartPosition = STRING_NOTFOUND;
//STRIP001         String  sLinkCharacterStyle; //default to "Default" character style - which is none
//STRIP001      String sURL;
//STRIP001      // create an enumerator
//STRIP001      SwFormTokenEnumerator aTokenEnum = GetTOXForm().CreateTokenEnumerator(nLvl);
//STRIP001      // remove text from node
//STRIP001      while(aTokenEnum.HasNextToken())
//STRIP001      {
//STRIP001          SwFormToken aToken = aTokenEnum.GetNextToken();
//STRIP001          xub_StrLen nStartCharStyle = rTxt.Len();
//STRIP001          switch( aToken.eTokenType )
//STRIP001          {
//STRIP001          case TOKEN_ENTRY_NO:
//STRIP001              // fuer Inhaltsverzeichnis Numerierung
//STRIP001              rTxt.Insert( lcl_GetNumString( rBase ));
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_ENTRY_TEXT:
//STRIP001              {
//STRIP001                  SwIndex aIdx( pTOXNd, rTxt.Len() );
//STRIP001                  rBase.FillText( *pTOXNd, aIdx );
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_ENTRY:
//STRIP001              {
//STRIP001                  // fuer Inhaltsverzeichnis Numerierung
//STRIP001                  rTxt.Insert( lcl_GetNumString( rBase ));
//STRIP001
//STRIP001                  SwIndex aIdx( pTOXNd, rTxt.Len() );
//STRIP001                  rBase.FillText( *pTOXNd, aIdx );
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_TAB_STOP:
//STRIP001              rTxt.Append('\t');
//STRIP001              //
//STRIP001              if(SVX_TAB_ADJUST_END > aToken.eTabAlign)
//STRIP001              {
//STRIP001                  const SvxLRSpaceItem& rLR = (SvxLRSpaceItem&)pTOXNd->
//STRIP001                                      SwCntntNode::GetAttr( RES_LR_SPACE );
//STRIP001
//STRIP001                  long nTabPosition = aToken.nTabStopPosition;
//STRIP001                  if( !GetTOXForm().IsRelTabPos() && rLR.GetTxtLeft() )
//STRIP001                      nTabPosition -= rLR.GetTxtLeft();
//STRIP001                  aTStops.Insert( SvxTabStop( nTabPosition,
//STRIP001                                              SVX_TAB_ADJUST_LEFT,
//STRIP001                                              cDfltDecimalChar,
//STRIP001                                              aToken.cTabFillChar ));
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  const SwPageDesc* pPageDesc = ((SwFmtPageDesc&)pTOXNd->
//STRIP001                              SwCntntNode::GetAttr( RES_PAGEDESC )).GetPageDesc();
//STRIP001
//STRIP001                  BOOL bCallFindRect = TRUE;
//STRIP001                  long nRightMargin;
//STRIP001                  if( pPageDesc )
//STRIP001                  {
//STRIP001                      const SwFrm* pFrm = pTOXNd->GetFrm( 0, 0, TRUE );
//STRIP001                      if( !pFrm || 0 == ( pFrm = pFrm->FindPageFrm() ) ||
//STRIP001                          pPageDesc != ((SwPageFrm*)pFrm)->GetPageDesc() )
//STRIP001                          // dann muss man ueber den PageDesc gehen
//STRIP001                          bCallFindRect = FALSE;
//STRIP001                  }
//STRIP001
//STRIP001                  SwRect aNdRect;
//STRIP001                  if( bCallFindRect )
//STRIP001                      aNdRect = pTOXNd->FindLayoutRect( TRUE );
//STRIP001
//STRIP001                  if( aNdRect.IsEmpty() )
//STRIP001                  {
//STRIP001                      // dann hilft alles nichts, wir muessen ueber die Seiten-
//STRIP001                      // vorlage gehen.
//STRIP001                         // OD 18.03.2003 #106329# - call
//STRIP001                         sal_uInt32 nPgDescNdIdx = pTOXNd->GetIndex() + 1;
//STRIP001                         sal_uInt32* pPgDescNdIdx = &nPgDescNdIdx;
//STRIP001                         pPageDesc = pTOXNd->FindPageDesc( FALSE, pPgDescNdIdx );
//STRIP001                         if ( !pPageDesc ||
//STRIP001                              *pPgDescNdIdx < _nTOXSectNdIdx )
//STRIP001                         {
//STRIP001                             // use default page description, if none is found
//STRIP001                             // or the found one is given by a node before the
//STRIP001                             // table-of-content section.
//STRIP001                             pPageDesc = _pDefaultPageDesc;
//STRIP001                         }
//STRIP001
//STRIP001                      const SwFrmFmt& rPgDscFmt = pPageDesc->GetMaster();
//STRIP001                      nRightMargin = rPgDscFmt.GetFrmSize().GetWidth() -
//STRIP001                                      rPgDscFmt.GetLRSpace().GetLeft() -
//STRIP001                                      rPgDscFmt.GetLRSpace().GetRight();
//STRIP001                  }
//STRIP001                  else
//STRIP001                      nRightMargin = aNdRect.Width();
//STRIP001                  aTStops.Insert( SvxTabStop( nRightMargin,SVX_TAB_ADJUST_RIGHT,
//STRIP001                                              cDfltDecimalChar,
//STRIP001                                              aToken.cTabFillChar ));
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_TEXT:
//STRIP001              rTxt.Append( aToken.sText );
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_PAGE_NUMS:
//STRIP001                  // Platzhalter fuer Seitennummer(n) es wird nur der erste beachtet
//STRIP001                  //
//STRIP001              {
//STRIP001                  // Die Anzahl der gleichen Eintrage bestimmt die Seitennummern-Pattern
//STRIP001                  //
//STRIP001                  USHORT nSize = rBase.aTOXSources.Count();
//STRIP001                  if( nSize > 0 )
//STRIP001                  {
//STRIP001                      String aInsStr( cNumRepl );
//STRIP001                      for(USHORT i=1; i < nSize; ++i)
//STRIP001                      {
//STRIP001                          aInsStr.AppendAscii( sPageDeli );
//STRIP001                          aInsStr += cNumRepl;
//STRIP001                      }
//STRIP001                      aInsStr += cEndPageNum;
//STRIP001                      rTxt.Append( aInsStr );
//STRIP001                  }
//STRIP001 //                       // Tab entfernen, wenn keine Seitennummer
//STRIP001 //                   else if( rTxt.Len() && '\t' == rTxt.GetChar( rTxt.Len() - 1 ))
//STRIP001 //                       rTxt.Erase( rTxt.Len()-1, 1 );
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_CHAPTER_INFO:
//STRIP001              {
//STRIP001                  // ein bischen trickreich: suche irgend einen Frame
//STRIP001                  const SwTOXSource* pTOXSource = 0;
//STRIP001                  if(rBase.aTOXSources.Count())
//STRIP001                      pTOXSource = &rBase.aTOXSources[0];
//STRIP001                  if( pTOXSource && pTOXSource->pNd && pTOXSource->pNd->IsTxtNode() )
//STRIP001                  {
//STRIP001                      const SwCntntFrm* pFrm = pTOXSource->pNd->GetFrm();
//STRIP001                      if( pFrm )
//STRIP001                      {
//STRIP001                          SwChapterFieldType aFldTyp;
//STRIP001                          SwChapterField aFld( &aFldTyp, aToken.nChapterFormat );
//STRIP001                          aFld.SetLevel( MAXLEVEL - 1 );
//STRIP001                          aFld.ChangeExpansion( pFrm, (SwTxtNode*)pTOXSource->pNd, TRUE );
//STRIP001
//STRIP001                          if(CF_NUMBER == aToken.nChapterFormat)
//STRIP001                              rTxt.Insert(aFld.GetNumber());
//STRIP001                          else if(CF_NUM_TITLE == aToken.nChapterFormat)
//STRIP001                          {
//STRIP001                              rTxt += aFld.GetNumber();
//STRIP001                              rTxt += ' ';
//STRIP001                              rTxt += aFld.GetTitle();
//STRIP001                          }
//STRIP001                          else if(CF_TITLE == aToken.nChapterFormat)
//STRIP001                              rTxt += aFld.GetTitle();
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_LINK_START:
//STRIP001              nLinkStartPosition = rTxt.Len();
//STRIP001                 sLinkCharacterStyle = aToken.sCharStyleName;
//STRIP001             break;
//STRIP001
//STRIP001          case TOKEN_LINK_END:
//STRIP001                  //TODO: only paired start/end tokens are valid
//STRIP001              if( STRING_NOTFOUND != nLinkStartPosition)
//STRIP001              {
//STRIP001                  SwIndex aIdx( pTOXNd, nLinkStartPosition );
//STRIP001                  //pTOXNd->Erase( aIdx, SwForm::nFormLinkSttLen );
//STRIP001                  xub_StrLen nEnd = rTxt.Len();
//STRIP001
//STRIP001                  if( !sURL.Len() )
//STRIP001                  {
//STRIP001                      sURL = rBase.GetURL();
//STRIP001                      if( !sURL.Len() )
//STRIP001                          break;
//STRIP001                  }
//STRIP001                     LinkStruct* pNewLink = new LinkStruct(sURL, nLinkStartPosition,
//STRIP001                                                     nEnd);
//STRIP001                     pNewLink->aINetFmt.SetVisitedFmt(sLinkCharacterStyle);
//STRIP001                     pNewLink->aINetFmt.SetINetFmt(sLinkCharacterStyle);
//STRIP001                     if(sLinkCharacterStyle.Len())
//STRIP001                     {
//STRIP001                         USHORT nPoolId =
//STRIP001                             SwStyleNameMapper::GetPoolIdFromUIName( sLinkCharacterStyle, GET_POOLID_CHRFMT );
//STRIP001                         pNewLink->aINetFmt.SetVisitedFmtId(nPoolId);
//STRIP001                         pNewLink->aINetFmt.SetINetFmtId(nPoolId);
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         pNewLink->aINetFmt.SetVisitedFmtId(USHRT_MAX);
//STRIP001                         pNewLink->aINetFmt.SetINetFmtId(USHRT_MAX);
//STRIP001                     }
//STRIP001                     aLinkArr.Insert( pNewLink, aLinkArr.Count() );
//STRIP001                  nLinkStartPosition = STRING_NOTFOUND;
//STRIP001                     sLinkCharacterStyle.Erase();
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case TOKEN_AUTHORITY:
//STRIP001              {
//STRIP001                  ToxAuthorityField eField = (ToxAuthorityField)aToken.nAuthorityField;
//STRIP001                  SwIndex aIdx( pTOXNd, rTxt.Len() );
//STRIP001                  rBase.FillText( *pTOXNd, aIdx, eField );
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if( aToken.sCharStyleName.Len() )
//STRIP001          {
//STRIP001              SwCharFmt* pCharFmt;
//STRIP001              if( USHRT_MAX != aToken.nPoolId )
//STRIP001                  pCharFmt = pDoc->GetCharFmtFromPool( aToken.nPoolId );
//STRIP001              else
//STRIP001                  pCharFmt = pDoc->FindCharFmtByName( aToken.sCharStyleName);
//STRIP001
//STRIP001              if(pCharFmt)
//STRIP001                  pTOXNd->Insert( SwFmtCharFmt( pCharFmt ), nStartCharStyle,
//STRIP001                                  rTxt.Len(), SETATTR_DONTEXPAND );
//STRIP001          }
//STRIP001      }
//STRIP001      pTOXNd->SwCntntNode::SetAttr( aTStops );
//STRIP001  }
//STRIP001
//STRIP001  if(aLinkArr.Count())
//STRIP001      for(USHORT i = 0; i < aLinkArr.Count(); ++i )
//STRIP001      {
//STRIP001          LinkStruct* pTmp = aLinkArr.GetObject(i);
//STRIP001          pTOXNd->Insert( pTmp->aINetFmt, pTmp->nStartTextPos,
//STRIP001                          pTmp->nEndTextPos);
//STRIP001      }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Seitennummer errechnen und nach dem Formatieren
                   eintragen
 --------------------------------------------------------------------*/

/*N*/ void SwTOXBaseSection::UpdatePageNum()
/*N*/ {
/*N*/   if( !aSortArr.Count() )
/*N*/       return ;

    // die aktuellen Seitennummern ins Verzeichnis eintragen
/*?*/   SwPageFrm*  pAktPage    = 0;
/*?*/   USHORT      nPage       = 0;
/*?*/   SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
/*?*/
/*?*/     SwTOXInternational aIntl( GetLanguage(),
/*?*/                               TOX_INDEX == GetTOXType()->GetType() ?
/*?*/                               GetOptions() : 0,
/*?*/                               GetSortAlgorithm() );
/*?*/
/*?*/   for( USHORT nCnt = 0; nCnt < aSortArr.Count(); ++nCnt )
/*?*/   {
//STRIP001 /*?*/        // Schleife ueber alle SourceNodes
//STRIP001 /*?*/        SvUShorts aNums;        //Die Seitennummern
//STRIP001 /*?*/        SvPtrarr  aDescs;       //Die PageDescriptoren passend zu den Seitennummern.
//STRIP001 /*?*/        SvUShorts* pMainNums = 0; // contains page numbers of main entries
//STRIP001 /*?*/
//STRIP001 /*?*/        // process run in lines
//STRIP001 /*?*/        USHORT nRange = 0;
//STRIP001 /*?*/        if(GetTOXForm().IsCommaSeparated() &&
//STRIP001 /*?*/                aSortArr[nCnt]->GetType() == TOX_SORT_INDEX)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            const SwTOXMark& rMark = aSortArr[nCnt]->pTxtMark->GetTOXMark();
//STRIP001 /*?*/            const String sPrimKey = rMark.GetPrimaryKey();
//STRIP001 /*?*/            const String sSecKey = rMark.GetSecondaryKey();
//STRIP001 /*?*/            const SwTOXMark* pNextMark = 0;
//STRIP001 /*?*/            while(aSortArr.Count() > (nCnt + nRange)&&
//STRIP001 /*?*/                    aSortArr[nCnt + nRange]->GetType() == TOX_SORT_INDEX &&
//STRIP001 /*?*/                    0 != (pNextMark = &(aSortArr[nCnt + nRange]->pTxtMark->GetTOXMark())) &&
//STRIP001 /*?*/                    pNextMark->GetPrimaryKey() == sPrimKey &&
//STRIP001 /*?*/                    pNextMark->GetSecondaryKey() == sSecKey)
//STRIP001 /*?*/                nRange++;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/            nRange = 1;
//STRIP001 /*?*/
//STRIP001 /*?*/        for(USHORT nRunInEntry = nCnt; nRunInEntry < nCnt + nRange; nRunInEntry++)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwTOXSortTabBase* pSortBase = aSortArr[nRunInEntry];
//STRIP001 /*?*/            USHORT nSize = pSortBase->aTOXSources.Count();
//STRIP001 /*?*/            for( USHORT j = 0; j < nSize; ++j )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ::binfilter::SetProgressState( 0, pDoc->GetDocShell() );
//STRIP001 /*?*/
//STRIP001 /*?*/                SwTOXSource& rTOXSource = pSortBase->aTOXSources[j];
//STRIP001 /*?*/                if( rTOXSource.pNd )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwCntntFrm* pFrm = rTOXSource.pNd->GetFrm();
//STRIP001 /*?*/                     ASSERT( pFrm || pDoc->IsUpdateTOX(), "TOX, no Frame found");
//STRIP001 /*?*/                     if( !pFrm )
//STRIP001 /*?*/                         continue;
//STRIP001 /*?*/                    if( pFrm->IsTxtFrm() && ((SwTxtFrm*)pFrm)->HasFollow() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // dann suche den richtigen heraus
//STRIP001 /*?*/                        SwTxtFrm* pNext = (SwTxtFrm*)pFrm;
//STRIP001 /*?*/                        while( 0 != ( pNext = (SwTxtFrm*)pFrm->GetFollow() )
//STRIP001 /*?*/                                && rTOXSource.nPos >= pNext->GetOfst() )
//STRIP001 /*?*/                            pFrm = pNext;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    SwPageFrm*  pTmpPage = pFrm->FindPageFrm();
//STRIP001 /*?*/                    if( pTmpPage != pAktPage )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        nPage       = pTmpPage->GetVirtPageNum();
//STRIP001 /*?*/                        pAktPage    = pTmpPage;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    // sortiert einfuegen
//STRIP001 /*?*/                    for( USHORT i = 0; i < aNums.Count() && aNums[i] < nPage; ++i )
//STRIP001 /*?*/                        ;
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( i >= aNums.Count() || aNums[ i ] != nPage )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        aNums.Insert( nPage, i );
//STRIP001 /*?*/                        aDescs.Insert( (void*)pAktPage->GetPageDesc(), i );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    // is it a main entry?
//STRIP001 /*?*/                    if(TOX_SORT_INDEX == pSortBase->GetType() &&
//STRIP001 /*?*/                        rTOXSource.bMainEntry)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if(!pMainNums)
//STRIP001 /*?*/                            pMainNums = new SvUShorts;
//STRIP001 /*?*/                        pMainNums->Insert(nPage, pMainNums->Count());
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            // einfuegen der Seitennummer in den Verzeichnis-Text-Node
//STRIP001 /*?*/            const SwTOXSortTabBase* pBase = aSortArr[ nCnt ];
//STRIP001 /*?*/            if(pBase->pTOXNd)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                const SwTxtNode* pTxtNd = pBase->pTOXNd->GetTxtNode();
//STRIP001 /*?*/                ASSERT( pTxtNd, "kein TextNode, falsches Verzeichnis" );
//STRIP001 /*?*/
//STRIP001 /*?*/                _UpdatePageNum( (SwTxtNode*)pTxtNd, aNums, aDescs, pMainNums,
//STRIP001 /*?*/                                aIntl );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            DELETEZ(pMainNums);
//STRIP001 /*?*/            aNums.Remove(0, aNums.Count());
//STRIP001 /*?*/        }
/*?*/   }
/*?*/   // nach dem Setzen der richtigen Seitennummer, das Mapping-Array
/*?*/   // wieder loeschen !!
/*?*/   aSortArr.DeleteAndDestroy( 0, aSortArr.Count() );
/*N*/ }


/*--------------------------------------------------------------------
     Beschreibung: Austausch der Seitennummer-Platzhalter
 --------------------------------------------------------------------*/

// search for the page no in the array of main entry page numbers
//STRIP001 BOOL lcl_HasMainEntry( const SvUShorts* pMainEntryNums, USHORT nToFind )
//STRIP001 {
//STRIP001  for(USHORT i = 0; pMainEntryNums && i < pMainEntryNums->Count(); ++i)
//STRIP001      if(nToFind == (*pMainEntryNums)[i])
//STRIP001          return TRUE;
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SwTOXBaseSection::_UpdatePageNum( SwTxtNode* pNd,
//STRIP001                                  const SvUShorts& rNums,
//STRIP001                                  const SvPtrarr & rDescs,
//STRIP001                                  const SvUShorts* pMainEntryNums,
//STRIP001                                  const SwTOXInternational& rIntl )
//STRIP001 {
//STRIP001  //collect starts end ends of main entry character style
//STRIP001  SvUShorts* pCharStyleIdx = pMainEntryNums ? new SvUShorts : 0;
//STRIP001
//STRIP001  String sSrchStr( cNumRepl ); sSrchStr.AppendAscii( sPageDeli ) += cNumRepl;
//STRIP001  xub_StrLen nStartPos = pNd->GetTxt().Search( sSrchStr );
//STRIP001  ( sSrchStr = cNumRepl ) += cEndPageNum;
//STRIP001  xub_StrLen nEndPos = pNd->GetTxt().Search( sSrchStr );
//STRIP001
//STRIP001  if( STRING_NOTFOUND == nEndPos || !rNums.Count() )
//STRIP001      return;
//STRIP001
//STRIP001  if( STRING_NOTFOUND == nStartPos || nStartPos > nEndPos)
//STRIP001      nStartPos = nEndPos;
//STRIP001
//STRIP001  USHORT nOld = rNums[0],
//STRIP001         nBeg = nOld,
//STRIP001         nCount  = 0;
//STRIP001  String aNumStr( SvxNumberType( ((SwPageDesc*)rDescs[0])->GetNumType() ).
//STRIP001                  GetNumStr( nBeg ) );
//STRIP001  if( pCharStyleIdx && lcl_HasMainEntry( pMainEntryNums, nBeg ))
//STRIP001  {
//STRIP001      USHORT nTemp = 0;
//STRIP001      pCharStyleIdx->Insert( nTemp, pCharStyleIdx->Count());
//STRIP001  }
//STRIP001
//STRIP001  // Platzhalter loeschen
//STRIP001  SwIndex aPos(pNd, nStartPos);
//STRIP001  const SwFmtCharFmt* pPageNoCharFmt = 0;
//STRIP001  SwpHints* pHints = pNd->GetpSwpHints();
//STRIP001  if(pHints)
//STRIP001      for(USHORT nHintIdx = 0; nHintIdx < pHints->GetStartCount(); nHintIdx++)
//STRIP001      {
//STRIP001          SwTxtAttr* pAttr = pHints->GetStart(nHintIdx);
//STRIP001          xub_StrLen nTmpEnd = pAttr->GetEnd() ? *pAttr->GetEnd() : 0;
//STRIP001          if( nStartPos >= *pAttr->GetStart() &&
//STRIP001              (nStartPos + 2) <= nTmpEnd &&
//STRIP001              pAttr->Which() == RES_TXTATR_CHARFMT)
//STRIP001          {
//STRIP001              pPageNoCharFmt = &pAttr->GetCharFmt();
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  pNd->Erase(aPos, nEndPos - nStartPos + 2);
//STRIP001
//STRIP001  for(USHORT i = 1; i < rNums.Count(); ++i)
//STRIP001  {
//STRIP001      SvxNumberType aType( ((SwPageDesc*)rDescs[i])->GetNumType() );
//STRIP001      if( TOX_INDEX == SwTOXBase::GetType() )
//STRIP001      {   // Zusammenfassen f. ff.
//STRIP001          // Alle folgenden aufaddieren
//STRIP001          // break up if main entry starts or ends and
//STRIP001          // insert a char style index
//STRIP001          BOOL bMainEntryChanges = lcl_HasMainEntry(pMainEntryNums, nOld)
//STRIP001                  != lcl_HasMainEntry(pMainEntryNums, rNums[i]);
//STRIP001
//STRIP001          if(nOld == rNums[i]-1 && !bMainEntryChanges &&
//STRIP001              0 != (GetOptions() & (TOI_FF|TOI_DASH)))
//STRIP001              nCount++;
//STRIP001          else
//STRIP001          {
//STRIP001              // ff. f. alten Wert flushen
//STRIP001              if(GetOptions() & TOI_FF)
//STRIP001              {
//STRIP001                  if ( nCount >= 1 )
//STRIP001                      aNumStr += rIntl.GetFollowingText( nCount > 1 );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if(nCount >= 2 )
//STRIP001                      aNumStr += '-';
//STRIP001                  else if(nCount == 1 )
//STRIP001                      aNumStr.AppendAscii( sPageDeli );
//STRIP001 //#58127# Wenn nCount == 0, dann steht die einzige Seitenzahl schon im aNumStr!
//STRIP001                  if(nCount)
//STRIP001                      aNumStr += aType.GetNumStr( nBeg + nCount );
//STRIP001              }
//STRIP001
//STRIP001              // neuen String anlegen
//STRIP001              nBeg     = rNums[i];
//STRIP001              aNumStr.AppendAscii( sPageDeli );
//STRIP001              //the change of the character style must apply after sPageDeli is appended
//STRIP001              if(pCharStyleIdx && bMainEntryChanges)
//STRIP001                  pCharStyleIdx->Insert(aNumStr.Len(),
//STRIP001                                                  pCharStyleIdx->Count());
//STRIP001              aNumStr += aType.GetNumStr( nBeg );
//STRIP001              nCount   = 0;
//STRIP001          }
//STRIP001          nOld = rNums[i];
//STRIP001      }
//STRIP001      else
//STRIP001      {   // Alle Nummern eintragen
//STRIP001          aNumStr += aType.GetNumStr( USHORT(rNums[i]) );
//STRIP001          if(i != (rNums.Count()-1))
//STRIP001              aNumStr.AppendAscii( sPageDeli );
//STRIP001      }
//STRIP001  }
//STRIP001  // Bei Ende und ff. alten Wert flushen
//STRIP001  if( TOX_INDEX == SwTOXBase::GetType() )
//STRIP001  {
//STRIP001      if(GetOptions() & TOI_FF)
//STRIP001      {
//STRIP001          if( nCount >= 1 )
//STRIP001              aNumStr += rIntl.GetFollowingText( nCount > 1 );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(nCount >= 2)
//STRIP001              aNumStr +='-';
//STRIP001          else if(nCount == 1)
//STRIP001              aNumStr.AppendAscii( sPageDeli );
//STRIP001 //#58127# Wenn nCount == 0, dann steht die einzige Seitenzahl schon im aNumStr!
//STRIP001          if(nCount)
//STRIP001              aNumStr += SvxNumberType( ((SwPageDesc*)rDescs[i-1])->
//STRIP001                              GetNumType() ).GetNumStr( nBeg+nCount );
//STRIP001      }
//STRIP001  }
//STRIP001  pNd->Insert( aNumStr, aPos, INS_EMPTYEXPAND );
//STRIP001  if(pPageNoCharFmt)
//STRIP001  {
//STRIP001      SwDoc* pDoc = pNd->GetDoc();
//STRIP001      SwFmtCharFmt aCharFmt(pPageNoCharFmt->GetCharFmt());
//STRIP001      pNd->Insert(aCharFmt, nStartPos, nStartPos + aNumStr.Len(), SETATTR_DONTEXPAND);
//STRIP001  }
//STRIP001
//STRIP001  //now the main entries should get there character style
//STRIP001  if(pCharStyleIdx && pCharStyleIdx->Count() && GetMainEntryCharStyle().Len())
//STRIP001  {
//STRIP001      // eventually the last index must me appended
//STRIP001      if(pCharStyleIdx->Count()&0x01)
//STRIP001          pCharStyleIdx->Insert(aNumStr.Len(), pCharStyleIdx->Count());
//STRIP001
//STRIP001      //search by name
//STRIP001      SwDoc* pDoc = pNd->GetDoc();
//STRIP001      USHORT nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( GetMainEntryCharStyle(), GET_POOLID_CHRFMT );
//STRIP001      SwCharFmt* pCharFmt = 0;
//STRIP001      if(USHRT_MAX != nPoolId)
//STRIP001          pCharFmt = pDoc->GetCharFmtFromPool(nPoolId);
//STRIP001      else
//STRIP001          pCharFmt = pDoc->FindCharFmtByName( GetMainEntryCharStyle() );
//STRIP001      if(!pCharFmt)
//STRIP001          pCharFmt = pDoc->MakeCharFmt(GetMainEntryCharStyle(), 0);
//STRIP001
//STRIP001      //find the page numbers in aNumStr and set the character style
//STRIP001      xub_StrLen nOffset = pNd->GetTxt().Len() - aNumStr.Len();
//STRIP001      SwFmtCharFmt aCharFmt(pCharFmt);
//STRIP001      for(USHORT i = 0; i < pCharStyleIdx->Count(); i += 2)
//STRIP001      {
//STRIP001          xub_StrLen nStartIdx = (*pCharStyleIdx)[i] + nOffset;
//STRIP001          xub_StrLen nEndIdx = (*pCharStyleIdx)[i + 1]  + nOffset;
//STRIP001          pNd->Insert(aCharFmt, nStartIdx, nEndIdx, SETATTR_DONTEXPAND);
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001  delete pCharStyleIdx;
//STRIP001 }


/*--------------------------------------------------------------------
     Beschreibung: Sortiert einfuegen in das SortArr
 --------------------------------------------------------------------*/

//STRIP001 void SwTOXBaseSection::InsertSorted(SwTOXSortTabBase* pNew)
//STRIP001 {
//STRIP001  Range aRange(0, aSortArr.Count());
//STRIP001  if( TOX_INDEX == SwTOXBase::GetType() && pNew->pTxtMark )
//STRIP001  {
//STRIP001      const SwTOXMark& rMark = pNew->pTxtMark->GetTOXMark();
//STRIP001      // Schluessel auswerten
//STRIP001      // Den Bereich ermitteln, in dem einzufuegen ist
//STRIP001      if( 0 == (GetOptions() & TOI_KEY_AS_ENTRY) &&
//STRIP001          rMark.GetPrimaryKey().Len() )
//STRIP001      {
//STRIP001             aRange = GetKeyRange( rMark.GetPrimaryKey(),
//STRIP001                                   rMark.GetPrimaryKeyReading(),
//STRIP001                                   *pNew, FORM_PRIMARY_KEY, aRange );
//STRIP001
//STRIP001             if( rMark.GetSecondaryKey().Len() )
//STRIP001                 aRange = GetKeyRange( rMark.GetSecondaryKey(),
//STRIP001                                       rMark.GetSecondaryKeyReading(),
//STRIP001                                       *pNew, FORM_SECONDARY_KEY, aRange );
//STRIP001      }
//STRIP001  }
//STRIP001  //search for identical entries and remove the trailing one
//STRIP001  if(TOX_AUTHORITIES == SwTOXBase::GetType())
//STRIP001  {
//STRIP001      for(short i = (short)aRange.Min(); i < (short)aRange.Max(); ++i)
//STRIP001      {
//STRIP001          SwTOXSortTabBase* pOld = aSortArr[i];
//STRIP001          if(*pOld == *pNew)
//STRIP001          {
//STRIP001              if(*pOld < *pNew)
//STRIP001              {
//STRIP001                  delete pNew;
//STRIP001                  return;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // remove the old content
//STRIP001                  aSortArr.DeleteAndDestroy( i, 1 );
//STRIP001                  aRange.Max()--;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // find position and insert
//STRIP001  //
//STRIP001  for(short i = (short)aRange.Min(); i < (short)aRange.Max(); ++i)
//STRIP001  {   // nur auf gleicher Ebene pruefen
//STRIP001      //
//STRIP001      SwTOXSortTabBase* pOld = aSortArr[i];
//STRIP001      if(*pOld == *pNew)
//STRIP001      {
//STRIP001          if(TOX_AUTHORITIES != SwTOXBase::GetType())
//STRIP001          {
//STRIP001              // Eigener Eintrag fuer Doppelte oder Keywords
//STRIP001              //
//STRIP001              if( pOld->GetType() == TOX_SORT_CUSTOM &&
//STRIP001                  pNew->GetOptions() & TOI_KEY_AS_ENTRY)
//STRIP001                  continue;
//STRIP001
//STRIP001              if(!(pNew->GetOptions() & TOI_SAME_ENTRY))
//STRIP001              {   // Eigener Eintrag
//STRIP001                  aSortArr.Insert(pNew, i );
//STRIP001                  return;
//STRIP001              }
//STRIP001              // Eintrag schon vorhanden in Referenzliste aufnehmen
//STRIP001              pOld->aTOXSources.Insert( pNew->aTOXSources[0],
//STRIP001                                          pOld->aTOXSources.Count() );
//STRIP001
//STRIP001              delete pNew;
//STRIP001              return;
//STRIP001          }
//STRIP001 #ifdef DBG_UTIL
//STRIP001          else
//STRIP001              DBG_ERROR("Bibliography entries cannot be found here")
//STRIP001 #endif
//STRIP001      }
//STRIP001      if(*pNew < *pOld)
//STRIP001          break;
//STRIP001  }
//STRIP001  // SubLevel Skippen
//STRIP001  while( TOX_INDEX == SwTOXBase::GetType() && i < aRange.Max() &&
//STRIP001        aSortArr[i]->GetLevel() > pNew->GetLevel() )
//STRIP001      i++;
//STRIP001
//STRIP001  // An Position i wird eingefuegt
//STRIP001  aSortArr.Insert(pNew, i );
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Schluessel-Bereich suchen und evtl einfuegen
 --------------------------------------------------------------------*/

//STRIP001 Range SwTOXBaseSection::GetKeyRange(const String& rStr, const String& rStrReading,
//STRIP001                                     const SwTOXSortTabBase& rNew,
//STRIP001                                     USHORT nLevel, const Range& rRange )
//STRIP001 {
//STRIP001     const SwTOXInternational& rIntl = *rNew.pTOXIntl;
//STRIP001  String sToCompare(rStr);
//STRIP001     String sToCompareReading(rStrReading);
//STRIP001
//STRIP001  if( 0 != (TOI_INITIAL_CAPS & GetOptions()) )
//STRIP001  {
//STRIP001      String sUpper( rIntl.ToUpper( sToCompare, 0 ));
//STRIP001      sToCompare.Erase( 0, 1 ).Insert( sUpper, 0 );
//STRIP001  }
//STRIP001
//STRIP001  ASSERT(rRange.Min() >= 0 && rRange.Max() >= 0, "Min Max < 0");
//STRIP001
//STRIP001  const USHORT nMin = (USHORT)rRange.Min();
//STRIP001  const USHORT nMax = (USHORT)rRange.Max();
//STRIP001
//STRIP001  USHORT nOptions = GetOptions();
//STRIP001  BOOL bIgnoreCase = ( nOptions & TOI_SAME_ENTRY ) &&
//STRIP001                      0 == ( nOptions & TOI_CASE_SENSITIVE );
//STRIP001
//STRIP001  for(USHORT i = nMin; i < nMax; ++i)
//STRIP001  {
//STRIP001      SwTOXSortTabBase* pBase = aSortArr[i];
//STRIP001
//STRIP001         String sMyString, sMyStringReading;
//STRIP001         pBase->GetTxt( sMyString, sMyStringReading );
//STRIP001
//STRIP001         if( rIntl.IsEqual( sMyString, sMyStringReading, pBase->GetLocale(),
//STRIP001                            sToCompare, sToCompareReading, rNew.GetLocale() )  &&
//STRIP001                     pBase->GetLevel() == nLevel &&
//STRIP001                     pBase->GetType() == TOX_SORT_CUSTOM )
//STRIP001          break;
//STRIP001  }
//STRIP001  if(i == nMax)
//STRIP001  {   // Falls nicht vorhanden erzeugen und einfuegen
//STRIP001      //
//STRIP001         SwTOXCustom* pKey = new SwTOXCustom( sToCompare, nLevel, rIntl,
//STRIP001                                              rNew.GetLocale() );
//STRIP001      for(i = nMin; i < nMax; ++i)
//STRIP001      {
//STRIP001          if(nLevel == aSortArr[i]->GetLevel() &&  *pKey < *(aSortArr[i]))
//STRIP001              break;
//STRIP001      }
//STRIP001      aSortArr.Insert(pKey, i );
//STRIP001  }
//STRIP001  USHORT nStart = i+1;
//STRIP001  USHORT nEnd   = aSortArr.Count();
//STRIP001
//STRIP001  // Ende des Bereiches suchen
//STRIP001  for(i = nStart; i < aSortArr.Count(); ++i)
//STRIP001  {
//STRIP001      if(aSortArr[i]->GetLevel() <= nLevel)
//STRIP001      {   nEnd = i;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return Range(nStart, nEnd);
//STRIP001 }


/*N*/ BOOL SwTOXBase::IsTOXBaseInReadonly() const
/*N*/ {
/*N*/   const SwTOXBaseSection *pSect = PTR_CAST(SwTOXBaseSection, this);
/*N*/   BOOL bRet = FALSE;
/*N*/   const SwSectionNode* pSectNode;
/*N*/   if(pSect && pSect->GetFmt() &&
/*N*/           0 != (pSectNode = pSect->GetFmt()->GetSectionNode()))
/*N*/   {
/*N*/       const SwDocShell* pDocSh;
/*N*/       bRet = (0 != (pDocSh = pSectNode->GetDoc()->GetDocShell()) &&
/*N*/                                                   pDocSh->IsReadOnly()) ||
/*N*/           (0 != (pSectNode = pSectNode->FindStartNode()->FindSectionNode())&&
/*N*/                   pSectNode->GetSection().IsProtectFlag());
/*N*/
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/* -----------------17.08.99 13:29-------------------

 --------------------------------------------------*/
//STRIP001 const SfxItemSet* SwTOXBase::GetAttrSet() const
//STRIP001 {
//STRIP001  const SwTOXBaseSection *pSect = PTR_CAST(SwTOXBaseSection, this);
//STRIP001  if(pSect && pSect->GetFmt())
//STRIP001      return &pSect->GetFmt()->GetAttrSet();
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SwTOXBase::SetAttrSet( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SwTOXBaseSection *pSect = PTR_CAST(SwTOXBaseSection, this);
//STRIP001  if( pSect && pSect->GetFmt() )
//STRIP001      pSect->GetFmt()->SetAttr( rSet );
//STRIP001 }

//STRIP001 BOOL SwTOXBase::GetInfo( SfxPoolItem& rInfo ) const
//STRIP001 {
//STRIP001  switch( rInfo.Which() )
//STRIP001  {
//STRIP001  case RES_CONTENT_VISIBLE:
//STRIP001      {
//STRIP001          SwTOXBaseSection *pSect = PTR_CAST(SwTOXBaseSection, this);
//STRIP001          if( pSect && pSect->GetFmt() )
//STRIP001              pSect->GetFmt()->GetInfo( rInfo );
//STRIP001      }
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*  */


}
