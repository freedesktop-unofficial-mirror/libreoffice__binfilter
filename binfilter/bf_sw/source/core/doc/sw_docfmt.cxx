/*************************************************************************
 *
 *  $RCSfile: sw_docfmt.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:06:53 $
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

#define _ZFORLIST_DECLARE_TABLE
#define _SVSTDARR_USHORTSSORT
#define _SVSTDARR_USHORTS

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif
#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _SO2REF_HXX //autogen
#include <so3/so2ref.hxx>
#endif
#ifndef SO2_DECL_SVLINKNAME_DEFINED
#define SO2_DECL_SVLINKNAME_DEFINED
SO2_DECL_REF(SvLinkName)
#endif
#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_MISCCFG_HXX
#include <bf_sfx2/misccfg.hxx>
#endif
#ifndef _SVX_TSTPITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif
// auto strip #ifndef _SVX_LRSPITEM_HXX //autogen
// auto strip #include <bf_svx/lrspitem.hxx>
// auto strip #endif
#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif
#ifndef _ZFORLIST_HXX //autogen
#define _ZFORLIST_DECLARE_TABLE
#include <svtools/zforlist.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif


#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
// auto strip #ifndef _FMTHDFT_HXX //autogen
// auto strip #include <fmthdft.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCNTNT_HXX //autogen
// auto strip #include <fmtcntnt.hxx>
// auto strip #endif
// auto strip #ifndef _FRMATR_HXX
// auto strip #include <frmatr.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _ROOTFRM_HXX
// auto strip #include <rootfrm.hxx>
// auto strip #endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>            // fuer SwHyphenBug (in SetDefault)
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
// auto strip #ifndef _NDGRF_HXX
// auto strip #include <ndgrf.hxx>
// auto strip #endif
// auto strip #ifndef _PAGEDESC_HXX
// auto strip #include <pagedesc.hxx>           // Fuer Sonderbehandlung in InsFrmFmt
// auto strip #endif
#ifndef _ROLBCK_HXX
#include <rolbck.hxx>           // Undo-Attr
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>           // servieren: Veraenderungen erkennen
#endif
// auto strip #ifndef _TXATBASE_HXX
// auto strip #include <txatbase.hxx>
// auto strip #endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
// auto strip #ifndef _NUMRULE_HXX
// auto strip #include <numrule.hxx>
// auto strip #endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _REFFLD_HXX //autogen
#include <reffld.hxx>
#endif
#ifndef _TXTINET_HXX //autogen
#include <txtinet.hxx>
#endif
#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
// auto strip #ifndef _BREAKIT_HXX
// auto strip #include <breakit.hxx>
// auto strip #endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;

/*N*/ SV_IMPL_PTRARR(SwFrmFmts,SwFrmFmtPtr)
/*N*/ SV_IMPL_PTRARR(SwCharFmts,SwCharFmtPtr)

//Spezifische Frameformate (Rahmen)
/*N*/ SV_IMPL_PTRARR(SwSpzFrmFmts,SwFrmFmtPtr)

/*
 * interne Funktionen
 */

//STRIP001 BOOL SetTxtFmtCollNext( const SwTxtFmtCollPtr& rpTxtColl, void* pArgs )
//STRIP001 {
//STRIP001  SwTxtFmtColl *pDel = (SwTxtFmtColl*) pArgs;
//STRIP001  if ( &rpTxtColl->GetNextTxtFmtColl() == pDel )
//STRIP001  {
//STRIP001      rpTxtColl->SetNextTxtFmtColl( *rpTxtColl );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*
 * Zuruecksetzen der harten Formatierung fuer Text
 */

// Uebergabeparameter fuer _Rst und lcl_SetTxtFmtColl
struct ParaRstFmt
{
    SwFmtColl* pFmtColl;
    SwHistory* pHistory;
    const SwPosition *pSttNd, *pEndNd;
    const SfxItemSet* pDelSet;
    USHORT nWhich;
    BOOL bReset, bResetAll, bInclRefToxMark;

    ParaRstFmt( const SwPosition* pStt, const SwPosition* pEnd,
            SwHistory* pHst, USHORT nWhch = 0, const SfxItemSet* pSet = 0 )
        : pSttNd( pStt ), pEndNd( pEnd ), pHistory( pHst ), nWhich( nWhch ),
            pDelSet( pSet ), bResetAll( TRUE ), pFmtColl( 0 ),
            bInclRefToxMark( FALSE )
    {}

    ParaRstFmt( SwHistory* pHst )
        : pSttNd( 0 ), pEndNd( 0 ), pHistory( pHst ), nWhich( 0 ),
        pDelSet( 0 ), bResetAll( TRUE ), pFmtColl( 0 ),
        bInclRefToxMark( FALSE )
    {}
};

/* in pArgs steht die ChrFmtTablle vom Dokument
 * (wird bei Selectionen am Start/Ende und bei keiner SSelection benoetigt)
 */

/*N*/ BOOL lcl_RstTxtAttr( const SwNodePtr& rpNd, void* pArgs )
/*N*/ {
/*N*/   ParaRstFmt* pPara = (ParaRstFmt*)pArgs;
/*N*/   SwTxtNode * pTxtNode = (SwTxtNode*)rpNd->GetTxtNode();
/*N*/   if( pTxtNode && pTxtNode->GetpSwpHints() )
/*N*/   {
/*N*/       SwIndex aSt( pTxtNode, 0 );
/*N*/       USHORT nEnd = pTxtNode->Len();
/*N*/
/*N*/       if( &pPara->pSttNd->nNode.GetNode() == pTxtNode &&
/*N*/           pPara->pSttNd->nContent.GetIndex() )
/*?*/           aSt = pPara->pSttNd->nContent.GetIndex();
/*N*/
/*N*/       if( &pPara->pEndNd->nNode.GetNode() == rpNd )
/*N*/           nEnd = pPara->pEndNd->nContent.GetIndex();
/*N*/
/*N*/       if( pPara->pHistory )
/*N*/       {
/*N*/           // fuers Undo alle Attribute sichern
/*N*/           SwRegHistory aRHst( *pTxtNode, pPara->pHistory );
/*N*/           pTxtNode->GetpSwpHints()->Register( &aRHst );
/*N*/           pTxtNode->RstAttr( aSt, nEnd - aSt.GetIndex(), pPara->nWhich,
/*N*/                               pPara->pDelSet, pPara->bInclRefToxMark );
/*N*/           if( pTxtNode->GetpSwpHints() )
/*N*/               pTxtNode->GetpSwpHints()->DeRegister();
/*N*/       }
/*N*/       else
/*?*/           pTxtNode->RstAttr( aSt, nEnd - aSt.GetIndex(), pPara->nWhich,
/*?*/                               pPara->pDelSet, pPara->bInclRefToxMark );
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL lcl_RstAttr( const SwNodePtr& rpNd, void* pArgs )
/*N*/ {
/*N*/   ParaRstFmt* pPara = (ParaRstFmt*)pArgs;
/*N*/   SwCntntNode* pNode = (SwCntntNode*)rpNd->GetCntntNode();
/*N*/   if( pNode && pNode->GetpSwAttrSet() )
/*N*/   {
/*N*/       // das erhalten der Break-Attribute und der NumRule kommt nicht ins Undo
/*N*/       BOOL bLocked = pNode->IsModifyLocked();
/*N*/       pNode->LockModify();
/*N*/       SwDoc* pDoc = pNode->GetDoc();
/*N*/
/*N*/       SfxItemSet aSet( pDoc->GetAttrPool(),
/*N*/                           RES_PAGEDESC, RES_BREAK,
/*N*/                           RES_PARATR_NUMRULE, RES_PARATR_NUMRULE,
/*N*/                           RES_LR_SPACE, RES_LR_SPACE,
/*N*/                           0 );
/*N*/       SwAttrSet* pSet = pNode->GetpSwAttrSet();
/*N*/
/*N*/       USHORT __READONLY_DATA aSavIds[ 3 ] = { RES_PAGEDESC, RES_BREAK,
/*N*/                                               RES_PARATR_NUMRULE };
/*N*/
/*N*/       const SfxPoolItem* pItem;
/*N*/       for( USHORT n = 0; n < 3; ++n )
/*N*/           if( SFX_ITEM_SET == pSet->GetItemState( aSavIds[ n ], FALSE, &pItem ))
/*N*/           {
/*?*/               BOOL bSave = FALSE;
/*?*/               switch( aSavIds[ n ] )
/*?*/               {
/*?*/               case RES_PAGEDESC:
/*?*/                   bSave = 0 != ((SwFmtPageDesc*)pItem)->GetPageDesc();
/*?*/                   break;
/*?*/               case RES_BREAK:
/*?*/                   bSave = SVX_BREAK_NONE != ((SvxFmtBreakItem*)pItem)->GetBreak();
/*?*/                   break;
/*?*/               case RES_PARATR_NUMRULE:
/*?*/                   bSave = 0 != ((SwNumRuleItem*)pItem)->GetValue().Len();
/*?*/                   break;
/*?*/               }
/*?*/               if( bSave )
/*?*/               {
/*?*/                   aSet.Put( *pItem );
/*?*/                   pSet->ClearItem( aSavIds[n] );
/*?*/               }
/*N*/           }
/*N*/
/*N*/       if( !bLocked )
/*N*/           pNode->UnlockModify();
/*N*/
/*N*/       if( pPara )
/*N*/       {
/*N*/           SwRegHistory aRegH( pNode, *pNode, pPara->pHistory );
/*N*/
/*N*/           if( pPara->pDelSet && pPara->pDelSet->Count() )
/*N*/           {
/*?*/               SfxItemIter aIter( *pPara->pDelSet );
/*?*/               pItem = aIter.FirstItem();
/*?*/               while( TRUE )
/*?*/               {
/*?*/                   pNode->ResetAttr( pItem->Which() );
/*?*/                   if( aIter.IsAtEnd() )
/*?*/                       break;
/*?*/                   pItem = aIter.NextItem();
/*?*/               }
/*N*/           }
/*N*/           else if( pPara->bResetAll )
/*N*/               pNode->ResetAllAttr();
/*N*/           else
/*?*/               pNode->ResetAttr( RES_PARATR_BEGIN, POOLATTR_END - 1 );
/*N*/       }
/*N*/       else
/*?*/           pNode->ResetAllAttr();
/*N*/
/*N*/       if( aSet.Count() )
/*N*/       {
/*?*/           pNode->LockModify();
/*?*/           pNode->SetAttr( aSet );
/*?*/
/*?*/           if( !bLocked )
/*?*/               pNode->UnlockModify();
/*N*/       }
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

//STRIP001 void SwDoc::RstTxtAttr(const SwPaM &rRg, BOOL bInclRefToxMark )
//STRIP001 {
//STRIP001  SwHistory* pHst = 0;
//STRIP001  SwDataChanged aTmp( rRg, 0 );
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      SwUndoRstAttr* pUndo = new SwUndoRstAttr( rRg, RES_CHRFMT );
//STRIP001      pHst = pUndo->GetHistory();
//STRIP001      AppendUndo( pUndo );
//STRIP001  }
//STRIP001  const SwPosition *pStt = rRg.Start(), *pEnd = rRg.End();
//STRIP001  ParaRstFmt aPara( pStt, pEnd, pHst );
//STRIP001  aPara.bInclRefToxMark = bInclRefToxMark;
//STRIP001  GetNodes().ForEach( pStt->nNode.GetIndex(), pEnd->nNode.GetIndex()+1,
//STRIP001                      lcl_RstTxtAttr, &aPara );
//STRIP001  SetModified();
//STRIP001 }

/*M*/ void SwDoc::ResetAttr( const SwPaM &rRg, BOOL bTxtAttr,
/*M*/                       const SvUShortsSort* pAttrs )
/*M*/ {
/*M*/   SwPaM* pPam = (SwPaM*)&rRg;
/*M*/   BOOL bStopAttr = FALSE;
/*M*/   if( !bTxtAttr && pAttrs && pAttrs->Count() &&
/*M*/       RES_TXTATR_END > (*pAttrs)[ 0 ] )
/*M*/       bTxtAttr = TRUE;
/*M*/
/*M*/   if( !rRg.HasMark() )
/*M*/   {
/*M*/       SwTxtNode* pTxtNd = rRg.GetPoint()->nNode.GetNode().GetTxtNode();
/*M*/       if( !pTxtNd )
/*M*/           return ;
/*M*/
/*M*/       pPam = new SwPaM( *rRg.GetPoint() );
/*M*/
/*M*/       SwIndex& rSt = pPam->GetPoint()->nContent;
/*M*/       USHORT nMkPos, nPtPos = rSt.GetIndex();
/*M*/       const String& rStr = pTxtNd->GetTxt();
/*M*/
/*M*/       // JP 22.08.96: Sonderfall: steht der Crsr in einem URL-Attribut
/*M*/       //              dann wird dessen Bereich genommen
/*M*/       const SwTxtAttr* pURLAttr;
/*M*/       if( pTxtNd->HasHints() &&
/*M*/           0 != ( pURLAttr = pTxtNd->GetTxtAttr( rSt, RES_TXTATR_INETFMT ))
/*M*/           && pURLAttr->GetINetFmt().GetValue().Len() )
/*M*/       {
/*M*/           nMkPos = *pURLAttr->GetStart();
/*M*/           nPtPos = *pURLAttr->GetEnd();
/*M*/       }
/*M*/       else
/*M*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            Boundary aBndry;
//STRIP001 /*?*/            if( pBreakIt->xBreak.is() )
//STRIP001 /*?*/                aBndry = pBreakIt->xBreak->getWordBoundary(
//STRIP001 /*?*/                            pTxtNd->GetTxt(), nPtPos,
//STRIP001 /*?*/                            pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001 /*?*/                            WordType::ANY_WORD /*ANYWORD_IGNOREWHITESPACES*/,
//STRIP001 /*?*/                            TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/            if( aBndry.startPos < nPtPos && nPtPos < aBndry.endPos )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                nMkPos = (xub_StrLen)aBndry.startPos;
//STRIP001 /*?*/                nPtPos = (xub_StrLen)aBndry.endPos;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                nPtPos = nMkPos = rSt.GetIndex();
//STRIP001 /*?*/                if( bTxtAttr )
//STRIP001 /*?*/                    pTxtNd->DontExpandFmt( rSt, TRUE );
//STRIP001 /*?*/            }
/*M*/       }
/*M*/
/*M*/       rSt = nMkPos;
/*M*/       pPam->SetMark();
/*M*/       pPam->GetPoint()->nContent = nPtPos;
/*M*/   }
/*M*/
/*M*/   SwDataChanged aTmp( *pPam, 0 );
/*M*/   SwHistory* pHst = 0;
/*M*/   if( DoesUndo() )
/*M*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        ClearRedo();
//STRIP001 /*?*/        SwUndoRstAttr* pUndo = new SwUndoRstAttr( rRg,
//STRIP001 /*?*/                    bTxtAttr ? RES_CONDTXTFMTCOLL : RES_TXTFMTCOLL );
//STRIP001 /*?*/        if( pAttrs && pAttrs->Count() )
//STRIP001 /*?*/            pUndo->SetAttrs( *pAttrs );
//STRIP001 /*?*/        pHst = pUndo->GetHistory();
//STRIP001 /*?*/        AppendUndo( pUndo );
/*M*/   }
/*M*/
/*M*/   const SwPosition *pStt = pPam->Start(), *pEnd = pPam->End();
/*M*/   ParaRstFmt aPara( pStt, pEnd, pHst );
/*M*/
/*N*/     USHORT __FAR_DATA aResetableSetRange[] = {
/*N*/         RES_FRMATR_BEGIN, RES_FRMATR_END-1,
/*N*/         RES_CHRATR_BEGIN, RES_CHRATR_END-1,
/*N*/         RES_PARATR_BEGIN, RES_PARATR_END-1,
/*N*/         RES_TXTATR_CHARFMT, RES_TXTATR_CHARFMT,
/*N*/         RES_TXTATR_INETFMT, RES_TXTATR_INETFMT,
/*N*/         RES_TXTATR_CJK_RUBY, RES_TXTATR_UNKNOWN_CONTAINER,
/*N*/         RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
/*N*/         0
/*N*/     };
/*N*/
/*N*/   SfxItemSet aDelSet( GetAttrPool(), aResetableSetRange );
/*M*/   if( pAttrs && pAttrs->Count() )
/*M*/   {
/*M*/       for( USHORT n = pAttrs->Count(); n; )
/*M*/           if( POOLATTR_END > (*pAttrs)[ --n ] )
/*M*/               aDelSet.Put( *GetDfltAttr( (*pAttrs)[ n ] ));
/*M*/
/*M*/       if( aDelSet.Count() )
/*M*/           aPara.pDelSet = &aDelSet;
/*M*/   }
/*M*/
/*M*/   BOOL bAdd = TRUE;
/*M*/   SwNodeIndex aTmpStt( pStt->nNode );
/*M*/   SwNodeIndex aTmpEnd( pEnd->nNode );
/*M*/   if( pStt->nContent.GetIndex() )     // nur ein Teil
/*M*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        // dann spaeter aufsetzen und alle CharFmtAttr -> TxtFmtAttr
//STRIP001 /*?*/        SwTxtNode* pTNd = aTmpStt.GetNode().GetTxtNode();
//STRIP001 /*?*/        if( pTNd && pTNd->GetpSwAttrSet() && pTNd->GetpSwAttrSet()->Count() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SfxItemIter aIter( *pTNd->GetpSwAttrSet() );
//STRIP001 /*?*/            const SfxPoolItem* pItem = aIter.GetCurItem();
//STRIP001 /*?*/            while( TRUE )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if( IsInRange( aCharFmtSetRange, pItem->Which() ))
//STRIP001 /*?*/                {
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( !pTNd->pSwpHints )
//STRIP001 /*?*/                        pTNd->pSwpHints = new SwpHints;
//STRIP001 /*?*/
//STRIP001 /*?*/                     const SwTxtAttr* pTAttr = 0;
//STRIP001 /*?*/                     if ( ! pTNd->pSwpHints->Forget( 0, 0, pItem->Which(),
//STRIP001 /*?*/                                                     0, pTNd->GetTxt().Len() ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                         pTAttr = pTNd->MakeTxtAttr( *pItem, 0,
//STRIP001 /*?*/                                      pTNd->GetTxt().Len() );
//STRIP001 /*?*/
//STRIP001 /*?*/                        pTNd->pSwpHints->SwpHintsArr::Insert( pTAttr );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( pHst )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         SwRegHistory aRegH( pTNd, *pTNd, pHst );
//STRIP001 /*?*/                         pTNd->ResetAttr( pItem->Which() );
//STRIP001 /*?*/                         if ( pTAttr )
//STRIP001 /*?*/                             pHst->Add( pTAttr, aTmpStt.GetIndex(), TRUE );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                         pTNd->ResetAttr( pItem->Which() );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if( aIter.IsAtEnd() )
//STRIP001 /*?*/                    break;
//STRIP001 /*?*/                pItem = aIter.NextItem();
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        aTmpStt++;
/*M*/   }
/*M*/   if( pEnd->nContent.GetIndex() == pEnd->nNode.GetNode().GetCntntNode()->Len() )
/*M*/       // dann spaeter aufsetzen und alle CharFmtAttr -> TxtFmtAttr
/*M*/       aTmpEnd++, bAdd = FALSE;
/*M*/   else if( pStt->nNode != pEnd->nNode || !pStt->nContent.GetIndex() )
/*M*/   {
/*M*/       SwTxtNode* pTNd = aTmpEnd.GetNode().GetTxtNode();
/*M*/       if( pTNd && pTNd->GetpSwAttrSet() && pTNd->GetpSwAttrSet()->Count() )
/*M*/       {
/*M*/           SfxItemIter aIter( *pTNd->GetpSwAttrSet() );
/*M*/           const SfxPoolItem* pItem = aIter.GetCurItem();
/*M*/           while( TRUE )
/*M*/           {
/*M*/               if( IsInRange( aCharFmtSetRange, pItem->Which() ))
/*M*/               {
/*M*/                   SwTxtAttr* pTAttr = pTNd->MakeTxtAttr( *pItem, 0,
/*M*/                                               pTNd->GetTxt().Len() );
/*M*/                   if( !pTNd->pSwpHints )
/*M*/                       pTNd->pSwpHints = new SwpHints;
/*M*/                   pTNd->pSwpHints->SwpHintsArr::Insert( pTAttr );
/*M*/                   if( pHst )
/*M*/                   {
/*M*/                       SwRegHistory aRegH( pTNd, *pTNd, pHst );
/*M*/                       pTNd->ResetAttr( pItem->Which() );
/*M*/                       pHst->Add( pTAttr, aTmpEnd.GetIndex(), TRUE );
/*M*/                   }
/*M*/                   else
/*M*/                       pTNd->ResetAttr( pItem->Which() );
/*M*/               }
/*M*/               if( aIter.IsAtEnd() )
/*M*/                   break;
/*M*/               pItem = aIter.NextItem();
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/
/*M*/   if( aTmpStt < aTmpEnd )
/*M*/       GetNodes().ForEach( pStt->nNode, aTmpEnd, lcl_RstAttr, &aPara );
/*M*/   else if( !rRg.HasMark() )
/*M*/   {
/*M*/       aPara.bResetAll = FALSE;
/*M*/       ::binfilter::lcl_RstAttr( &pStt->nNode.GetNode(), &aPara );
/*M*/       aPara.bResetAll = TRUE;
/*M*/   }
/*M*/
/*M*/   if( bTxtAttr )
/*M*/   {
/*M*/       if( bAdd )
/*M*/           aTmpEnd++;
/*M*/       GetNodes().ForEach( pStt->nNode, aTmpEnd, lcl_RstTxtAttr, &aPara );
/*M*/   }
/*M*/
/*M*/   if( pPam != &rRg )
/*M*/       delete pPam;
/*M*/
/*M*/   SetModified();
/*M*/ }



// Einfuegen der Hints nach Inhaltsformen;
// wird in SwDoc::Insert(..., SwFmtHint &rHt) benutzt

/*N*/ BOOL InsAttr( SwDoc *pDoc, const SwPaM &rRg, const SfxItemSet& rChgSet,
/*N*/               USHORT nFlags, SwUndoAttr* pUndo )
/*N*/ {
/*N*/   // teil die Sets auf (fuer Selektion in Nodes)
/*N*/   SfxItemSet aCharSet( pDoc->GetAttrPool(),
/*N*/                       RES_CHRATR_BEGIN, RES_CHRATR_END-1,
/*N*/                       RES_TXTATR_CHARFMT, RES_TXTATR_CHARFMT,
/*N*/                       RES_TXTATR_INETFMT, RES_TXTATR_INETFMT,
/*N*/
/*N*/                       RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
/*N*/                       0 );
/*N*/   SfxItemSet aOtherSet( pDoc->GetAttrPool(),
/*N*/                       RES_PARATR_BEGIN, RES_PARATR_END-1,
/*N*/                       RES_FRMATR_BEGIN, RES_FRMATR_END-1,
/*N*/                       RES_GRFATR_BEGIN, RES_GRFATR_END-1,
/*N*/                       0 );
/*N*/
/*N*/   aCharSet.Put( rChgSet );
/*N*/   aOtherSet.Put( rChgSet );
/*N*/
/*N*/   SwHistory* pHistory = pUndo ? pUndo->GetHistory() : 0;
/*N*/   BOOL bRet = FALSE;
/*N*/   const SwPosition *pStt = rRg.Start(), *pEnd = rRg.End();
/*N*/   SwCntntNode* pNode = pStt->nNode.GetNode().GetCntntNode();
/*N*/
/*N*/   if( pNode && pNode->IsTxtNode() )
/*N*/   {
/*N*/       const SwIndex& rSt = pStt->nContent;
/*N*/
/*N*/       // Attribute ohne Ende haben keinen Bereich
/*N*/       {
/*N*/           SfxItemSet aTxtSet( pDoc->GetAttrPool(),
/*N*/                       RES_TXTATR_NOEND_BEGIN, RES_TXTATR_NOEND_END-1 );
/*N*/           aTxtSet.Put( rChgSet );
/*N*/           if( aTxtSet.Count() )
/*N*/           {
/*N*/               SwRegHistory( (SwTxtNode*)pNode, aTxtSet, rSt.GetIndex(),
/*N*/                               rSt.GetIndex(), nFlags, pHistory );
/*N*/               bRet = TRUE;
/*N*/
/*N*/               if( pDoc->IsRedlineOn() || (!pDoc->IsIgnoreRedline() &&
/*N*/                   pDoc->GetRedlineTbl().Count() ))
/*N*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwPaM aPam( pStt->nNode, pStt->nContent.GetIndex()-1,
//STRIP001 /*?*/                                pStt->nNode, pStt->nContent.GetIndex() );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( pUndo )
//STRIP001 /*?*/                        pUndo->SaveRedlineData( aPam, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( pDoc->IsRedlineOn() )
//STRIP001 /*?*/                        pDoc->AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        pDoc->SplitRedline( aPam );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // TextAttribute mit Ende expandieren nie ihren Bereich
/*N*/       {
/*N*/           // CharFmt wird gesondert behandelt !!!
/*N*/           // JP 22.08.96: URL-Attribute auch!!
/*N*/           SfxItemSet aTxtSet( pDoc->GetAttrPool(),
/*N*/                               RES_TXTATR_DUMMY4, RES_TXTATR_TOXMARK,
/*N*/                               RES_TXTATR_DUMMY5, RES_TXTATR_WITHEND_END-1,
/*N*/                               0 );
/*N*/
/*N*/           aTxtSet.Put( rChgSet );
/*N*/           if( aTxtSet.Count() )
/*N*/           {
/*N*/               USHORT nInsCnt = rSt.GetIndex();
/*N*/               USHORT nEnd = pStt->nNode == pEnd->nNode
/*N*/                               ? pEnd->nContent.GetIndex()
/*N*/                               : pNode->Len();
/*N*/               SwRegHistory( (SwTxtNode*)pNode, aTxtSet, nInsCnt,
/*N*/                               nEnd, nFlags, pHistory );
/*N*/               bRet = TRUE;
/*N*/
/*N*/               if( pDoc->IsRedlineOn() || (!pDoc->IsIgnoreRedline() &&
/*N*/                    pDoc->GetRedlineTbl().Count() ) )
/*N*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // wurde Text-Inhalt eingefuegt? (RefMark/TOXMarks ohne Ende)
//STRIP001 /*?*/                    BOOL bTxtIns = nInsCnt != rSt.GetIndex();
//STRIP001 /*?*/                    // wurde Inhalt eingefuegt oder ueber die Selektion gesetzt?
//STRIP001 /*?*/                    SwPaM aPam( pStt->nNode, bTxtIns ? nInsCnt + 1 : nEnd,
//STRIP001 /*?*/                                pStt->nNode, nInsCnt );
//STRIP001 /*?*/                    if( pUndo )
//STRIP001 /*?*/                        pUndo->SaveRedlineData( aPam, bTxtIns );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( pDoc->IsRedlineOn() )
//STRIP001 /*?*/                        pDoc->AppendRedline( new SwRedline( bTxtIns
//STRIP001 /*?*/                                ? REDLINE_INSERT : REDLINE_FORMAT, aPam ));
//STRIP001 /*?*/                    else if( bTxtIns )
//STRIP001 /*?*/                        pDoc->SplitRedline( aPam );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // bei PageDesc's, die am Node gesetzt werden, muss immer das
/*N*/   // Auto-Flag gesetzt werden!!
/*N*/   const SvxLRSpaceItem* pLRSpace = 0;
/*N*/   if( aOtherSet.Count() )
/*N*/   {
/*N*/       SwTableNode* pTblNd;
/*N*/       const SwFmtPageDesc* pDesc;
/*N*/       if( SFX_ITEM_SET == aOtherSet.GetItemState( RES_PAGEDESC,
/*N*/                       FALSE, (const SfxPoolItem**)&pDesc ))
/*N*/       {
/*N*/           if( pNode )
/*N*/           {
/*N*/               // Auto-Flag setzen, nur in Vorlagen ist ohne Auto !
/*N*/               SwFmtPageDesc aNew( *pDesc );
/*N*/               // Bug 38479: AutoFlag wird jetzt in der WrtShell gesetzt
/*N*/               // aNew.SetAuto();
/*N*/
/*N*/               // Tabellen kennen jetzt auch Umbrueche
/*N*/               if( 0 == (nFlags & SETATTR_APICALL) &&
/*N*/                   0 != ( pTblNd = pNode->FindTableNode() ) )
/*N*/               {
/*N*/                   // dann am Tabellen Format setzen
/*?*/                   SwFrmFmt* pFmt = pTblNd->GetTable().GetFrmFmt();
/*?*/                   SwRegHistory aRegH( pFmt, *pTblNd, pHistory );
/*?*/                   pFmt->SetAttr( aNew );
/*?*/               }
/*N*/               else
/*N*/               {
/*N*/                   SwRegHistory aRegH( pNode, *pNode, pHistory );
/*N*/                   pNode->SetAttr( aNew );
/*N*/               }
/*N*/           }
/*N*/           aOtherSet.ClearItem( RES_PAGEDESC );
/*N*/           if( !aOtherSet.Count() )
/*N*/               return TRUE;
/*N*/       }
/*N*/
/*N*/       // Tabellen kennen jetzt auch Umbrueche
/*N*/       const SvxFmtBreakItem* pBreak;
/*N*/       if( pNode && 0 == (nFlags & SETATTR_APICALL) &&
/*N*/           0 != (pTblNd = pNode->FindTableNode() ) &&
/*N*/           SFX_ITEM_SET == aOtherSet.GetItemState( RES_BREAK,
/*N*/                       FALSE, (const SfxPoolItem**)&pBreak ) )
/*N*/       {
/*?*/           // dann am Tabellen Format setzen
/*?*/           SwFrmFmt* pFmt = pTblNd->GetTable().GetFrmFmt();
/*?*/           SwRegHistory aRegH( pFmt, *pTblNd, pHistory );
/*?*/           pFmt->SetAttr( *pBreak );
/*?*/
/*?*/           aOtherSet.ClearItem( RES_BREAK );
/*?*/           if( !aOtherSet.Count() )
/*?*/               return TRUE;
/*N*/       }
/*N*/
/*N*/       // fuer Sonderbehandlung von LR-Space innerhalb einer Numerierung !!!
/*N*/       aOtherSet.GetItemState( RES_LR_SPACE, FALSE,
/*N*/                               (const SfxPoolItem**)&pLRSpace );
/*N*/
/*N*/       {
/*N*/           // wenns eine PoolNumRule ist, diese ggfs. anlegen
/*N*/           const SwNumRuleItem* pRule;
/*N*/           USHORT nPoolId;
/*N*/           if( SFX_ITEM_SET == aOtherSet.GetItemState( RES_PARATR_NUMRULE,
/*N*/                               FALSE, (const SfxPoolItem**)&pRule ) &&
/*N*/               !pDoc->FindNumRulePtr( pRule->GetValue() ) &&
/*N*/               USHRT_MAX != (nPoolId = SwStyleNameMapper::GetPoolIdFromUIName ( pRule->GetValue(),
/*N*/                               GET_POOLID_NUMRULE )) )
/*?*/               pDoc->GetNumRuleFromPool( nPoolId );
/*N*/       }
/*N*/
/*N*/   }
/*N*/
/*N*/   if( !rRg.HasMark() )        // kein Bereich
/*N*/   {
/*N*/       if( !pNode )
/*N*/           return bRet;
/*N*/
/*N*/       if( pNode->IsTxtNode() && aCharSet.Count() )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwTxtNode* pTxtNd = (SwTxtNode*)pNode;
//STRIP001 /*?*/            const SwIndex& rSt = pStt->nContent;
//STRIP001 /*?*/            USHORT nMkPos, nPtPos = rSt.GetIndex();
//STRIP001 /*?*/            const String& rStr = pTxtNd->GetTxt();
//STRIP001 /*?*/
//STRIP001 /*?*/            // JP 22.08.96: Sonderfall: steht der Crsr in einem URL-Attribut
//STRIP001 /*?*/            //              dann wird dessen Bereich genommen
//STRIP001 /*?*/            const SwTxtAttr* pURLAttr;
//STRIP001 /*?*/            if( pTxtNd->HasHints() &&
//STRIP001 /*?*/                0 != ( pURLAttr = pTxtNd->GetTxtAttr( rSt, RES_TXTATR_INETFMT ))
//STRIP001 /*?*/                && pURLAttr->GetINetFmt().GetValue().Len() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                nMkPos = *pURLAttr->GetStart();
//STRIP001 /*?*/                nPtPos = *pURLAttr->GetEnd();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                Boundary aBndry;
//STRIP001 /*?*/                if( pBreakIt->xBreak.is() )
//STRIP001 /*?*/                    aBndry = pBreakIt->xBreak->getWordBoundary(
//STRIP001 /*?*/                                pTxtNd->GetTxt(), nPtPos,
//STRIP001 /*?*/                                pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001 /*?*/                                WordType::ANY_WORD /*ANYWORD_IGNOREWHITESPACES*/,
//STRIP001 /*?*/                                TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/                if( aBndry.startPos < nPtPos && nPtPos < aBndry.endPos )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    nMkPos = (xub_StrLen)aBndry.startPos;
//STRIP001 /*?*/                    nPtPos = (xub_StrLen)aBndry.endPos;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    nPtPos = nMkPos = rSt.GetIndex();
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // erstmal die zu ueberschreibenden Attribute aus dem
//STRIP001 /*?*/            // SwpHintsArray entfernen, wenn die Selektion den gesamten
//STRIP001 /*?*/            // Absatz umspannt. (Diese Attribute werden als FormatAttr.
//STRIP001 /*?*/            // eingefuegt und verdraengen nie die TextAttr.!)
//STRIP001 /*?*/            if( !(nFlags & SETATTR_DONTREPLACE ) &&
//STRIP001 /*?*/                pTxtNd->HasHints() && !nMkPos && nPtPos == rStr.Len() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwIndex aSt( pTxtNd );
//STRIP001 /*?*/                if( pHistory )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // fuers Undo alle Attribute sichern
//STRIP001 /*?*/                    SwRegHistory aRHst( *pTxtNd, pHistory );
//STRIP001 /*?*/                    pTxtNd->GetpSwpHints()->Register( &aRHst );
//STRIP001 /*?*/                    pTxtNd->RstAttr( aSt, nPtPos, 0, &aCharSet );
//STRIP001 /*?*/                    if( pTxtNd->GetpSwpHints() )
//STRIP001 /*?*/                        pTxtNd->GetpSwpHints()->DeRegister();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    pTxtNd->RstAttr( aSt, nPtPos, 0, &aCharSet );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // eintragen des Attributes im Node erledigt die SwRegHistory !!
//STRIP001 /*?*/            SwRegHistory( (SwTxtNode*)pNode, aCharSet,
//STRIP001 /*?*/                            nMkPos, nPtPos, nFlags, pHistory );
//STRIP001 /*?*/            bRet = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/            if( pDoc->IsRedlineOn() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwPaM aPam( *pNode, nMkPos, *pNode, nPtPos );
//STRIP001 /*?*/
//STRIP001 /*?*/                if( pUndo )
//STRIP001 /*?*/                    pUndo->SaveRedlineData( aPam, FALSE );
//STRIP001 /*?*/                pDoc->AppendRedline( new SwRedline( REDLINE_FORMAT, aPam ));
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       if( aOtherSet.Count() )
/*N*/       {
/*?*/           SwRegHistory aRegH( pNode, *pNode, pHistory );
/*?*/           pNode->SetAttr( aOtherSet );
/*?*/           bRet = TRUE;
/*N*/       }
/*N*/       return bRet;
/*N*/   }
/*N*/
/*N*/   if( pDoc->IsRedlineOn() && aCharSet.Count() )
/*N*/   {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if( pUndo )
//STRIP001 /*?*/            pUndo->SaveRedlineData( rRg, FALSE );
//STRIP001 /*?*/        pDoc->AppendRedline( new SwRedline( REDLINE_FORMAT, rRg ));
/*N*/   }

    /* jetzt wenn Bereich */
/*N*/   ULONG nNodes = 0;
/*N*/
/*N*/   SwNodeIndex aSt( pDoc->GetNodes() );
/*N*/   SwNodeIndex aEnd( pDoc->GetNodes() );
/*N*/   SwIndex aCntEnd( pEnd->nContent );
/*N*/
/*N*/   if( pNode )
/*N*/   {
/*N*/       USHORT nLen = pNode->Len();
/*N*/       if( pStt->nNode != pEnd->nNode )
/*N*/           aCntEnd.Assign( pNode, nLen );
/*N*/
/*N*/       if( pStt->nContent.GetIndex() != 0 || aCntEnd.GetIndex() != nLen )
/*N*/       {
/*N*/           // eintragen des Attributes im Node erledigt die SwRegHistory !!
/*N*/           if( pNode->IsTxtNode() && aCharSet.Count() )
/*N*/           {
/*N*/               SwRegHistory( (SwTxtNode*)pNode, aCharSet,
/*N*/                               pStt->nContent.GetIndex(), aCntEnd.GetIndex(),
/*N*/                               nFlags, pHistory );
/*N*/           }
/*N*/
/*N*/           if( aOtherSet.Count() )
/*N*/           {
/*N*/               SwRegHistory aRegH( pNode, *pNode, pHistory );
/*N*/               pNode->SetAttr( aOtherSet );
/*N*/           }
/*N*/
/*N*/           // lediglich Selektion in einem Node.
/*N*/           if( pStt->nNode == pEnd->nNode )
/*N*/               return TRUE;
/*N*/           ++nNodes;
/*?*/           aSt.Assign( pStt->nNode.GetNode(), +1 );
/*N*/       }
/*N*/       else
/*N*/           aSt = pStt->nNode;
/*N*/       aCntEnd = pEnd->nContent; // aEnd wurde veraendert !!
/*N*/   }
/*N*/   else
/*N*/       aSt.Assign( pStt->nNode.GetNode(), +1 );
/*N*/
/*N*/   // aSt zeigt jetzt auf den ersten vollen Node
/*N*/
    /*
      * die Selektion umfasst mehr als einen Node
      */
/*N*/   if( pStt->nNode < pEnd->nNode )
/*N*/   {
/*N*/       pNode = pEnd->nNode.GetNode().GetCntntNode();
/*N*/       if(pNode)
/*N*/       {
/*N*/           USHORT nLen = pNode->Len();
/*N*/           if( aCntEnd.GetIndex() != nLen )
/*N*/           {
/*N*/           // eintragen des Attributes im Node erledigt die SwRegHistory !!
/*N*/               if( pNode->IsTxtNode() && aCharSet.Count() )
/*N*/               {
/*?*/                   SwRegHistory( (SwTxtNode*)pNode, aCharSet,
/*?*/                                   0, aCntEnd.GetIndex(), nFlags, pHistory );
/*N*/               }
/*N*/
/*N*/               if( aOtherSet.Count() )
/*N*/               {
/*N*/                   SwRegHistory aRegH( pNode, *pNode, pHistory );
/*N*/                   pNode->SetAttr( aOtherSet );
/*N*/               }
/*N*/
/*N*/               ++nNodes;
/*N*/               aEnd = pEnd->nNode;
/*N*/           }
/*N*/           else
/*?*/               aEnd.Assign( pEnd->nNode.GetNode(), +1 );
/*N*/       }
/*N*/       else
/*?*/           aEnd = pEnd->nNode;
/*N*/   }
/*N*/   else
/*N*/       aEnd.Assign( pEnd->nNode.GetNode(), +1 );
/*N*/
/*N*/   // aEnd zeigt jetzt HINTER den letzten voll Node
/*N*/
/*N*/   /* Bearbeitung der vollstaendig selektierten Nodes. */
/*N*/ // alle Attribute aus dem Set zuruecksetzen !!
/*N*/   if( aCharSet.Count() && !( SETATTR_DONTREPLACE & nFlags ) )
/*N*/   {
/*N*/
/*N*/       ParaRstFmt aPara( pStt, pEnd, pHistory, 0, &aCharSet );
/*N*/       pDoc->GetNodes().ForEach( aSt, aEnd, lcl_RstTxtAttr, &aPara );
/*N*/   }
/*N*/
/*N*/ #ifdef USED
/*N*/ //JP 30.10.96: siehe unten
/*N*/   // sollte ueber mehrere Nodes das SwFmtChrFmt gesetzt werden ??
/*N*/   const SfxPoolItem* pChrFmtItem = 0;
/*N*/   aCharSet.GetItemState( RES_TXTATR_CHARFMT, FALSE, &pChrFmtItem );
/*N*/ #endif
/*N*/   BOOL bCreateSwpHints =
/*N*/       SFX_ITEM_SET == aCharSet.GetItemState( RES_TXTATR_CHARFMT, FALSE ) ||
/*N*/       SFX_ITEM_SET == aCharSet.GetItemState( RES_TXTATR_INETFMT, FALSE );
/*N*/
/*N*/   for(; aSt < aEnd; aSt++ )
/*N*/   {
/*N*/       pNode = aSt.GetNode().GetCntntNode();
/*N*/       if( !pNode )
/*N*/           continue;
/*N*/
/*N*/       SwTxtNode* pTNd = pNode->GetTxtNode();
/*N*/       if( pHistory )
/*N*/       {
/*N*/           SwRegHistory aRegH( pNode, *pNode, pHistory );
/*N*/           SwpHints *pSwpHints;
/*N*/
/*N*/ #ifdef USED
/*N*/ //JP 30.10.96: Das loeschen der Zeichen erledigt schon das SwpHints-Array
/*N*/ //                Warum dann hier doppelt?
/*N*/ //                !!  Ausserdem ist die Sonderbehandlung fuer die
/*N*/ //                !!  Zeichenvorlage/INetAttribut falsch
/*N*/
/*N*/           // loesche alle Text-Attribute, die durch den Set "ersetzt" werden
/*N*/           if( pTNd && 0 != ( pSwpHints = pTNd->GetpSwpHints() ) &&
/*N*/               pSwpHints->Count() )
/*N*/           {
/*N*/               pSwpHints->Register( &aRegH );
/*N*/
/*N*/               for( USHORT n = pSwpHints->Count(); n;  )
/*N*/               {
/*N*/                   SwTxtAttr* pAttr = pSwpHints->GetHt( --n );
/*N*/                   if( !pAttr->GetEnd() || RES_CHRATR_END <= pAttr->Which() )
/*N*/                       continue;
/*N*/                   if( pChrFmtItem || SFX_ITEM_SET ==
/*N*/                               aCharSet.GetItemState( pAttr->Which() ) )
/*N*/                   {
/*N*/                       pTNd->Delete( pAttr, TRUE );
/*N*/                       if( !pTNd->GetpSwpHints() )
/*N*/                       {
/*N*/                           pSwpHints = 0;
/*N*/                           break;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               if( pSwpHints )
/*N*/                   pSwpHints->DeRegister();
/*N*/           }
/*N*/ #endif
/*N*/           if( pTNd && aCharSet.Count() )
/*N*/           {
/*N*/               pSwpHints = bCreateSwpHints ? &pTNd->GetOrCreateSwpHints()
/*N*/                                           : pTNd->GetpSwpHints();
/*N*/               if( pSwpHints )
/*N*/                   pSwpHints->Register( &aRegH );
/*N*/
/*N*/               pTNd->SetAttr( aCharSet, 0, pTNd->GetTxt().Len(), nFlags );
/*N*/               if( pSwpHints )
/*N*/                   pSwpHints->DeRegister();
/*N*/           }
/*N*/           if( aOtherSet.Count() )
/*N*/               pNode->SetAttr( aOtherSet );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if( pTNd && aCharSet.Count() )
/*?*/               pTNd->SetAttr( aCharSet, 0, pTNd->GetTxt().Len(), nFlags );
/*N*/           if( aOtherSet.Count() )
/*N*/               pNode->SetAttr( aOtherSet );
/*N*/       }
/*N*/       ++nNodes;
/*N*/   }
/*N*/
/*N*/   return nNodes != 0;
/*N*/ }


/*N*/ BOOL SwDoc::Insert( const SwPaM &rRg, const SfxPoolItem &rHt, USHORT nFlags )
/*N*/ {
/*N*/   SwDataChanged aTmp( rRg, 0 );
/*N*/   BOOL bRet;
/*N*/   SwUndoAttr* pUndoAttr = 0;
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       pUndoAttr = new SwUndoAttr( rRg, rHt, nFlags );
/*N*/   }
/*N*/
/*N*/   SfxItemSet aSet( GetAttrPool(), rHt.Which(), rHt.Which() );
/*N*/   aSet.Put( rHt );
/*N*/   bRet = InsAttr( this, rRg, aSet, nFlags, pUndoAttr );

/*  if( INSATTR_DONTEXPAND & nFlags )
    {
        USHORT nWhich = rHt.Which();
        const SwPosition* pPos = rRg.End();
        SwTxtNode* pTxtNd = GetNodes()[ pPos->nNode ]->GetTxtNode();
        SwpHints* pHts;
        if( pTxtNd && 0 != ( pHts = pTxtNd->GetpSwpHints()) )
        {
            USHORT nPos = pHts->GetEndCount();
            while( nPos )
            {
                SwTxtAttr *pTmp = pHts->GetEnd( --nPos );
                USHORT *pEnd = pTmp->GetEnd();
                if( !pEnd || *pEnd > nEnd )
                    continue;
                if( nEnd != *pEnd )
                    nPos = 0;
                else if( nWhich == pTmp->Which() )
                    pTmp->SetDontExpand( TRUE );
            }
        }
    }
*/
/*N*/   if( DoesUndo() )
/*N*/       AppendUndo( pUndoAttr );
/*N*/
/*N*/   if( bRet )
/*N*/       SetModified();
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL SwDoc::Insert( const SwPaM &rRg, const SfxItemSet &rSet, USHORT nFlags )
/*N*/ {
/*N*/   SwDataChanged aTmp( rRg, 0 );
/*N*/   SwUndoAttr* pUndoAttr = 0;
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       pUndoAttr = new SwUndoAttr( rRg, rSet );
/*N*/   }
/*N*/
/*N*/   BOOL bRet = InsAttr( this, rRg, rSet, nFlags, pUndoAttr );
/*N*/
/*N*/   if( DoesUndo() )
/*N*/       AppendUndo( pUndoAttr );
/*N*/
/*N*/   if( bRet )
/*N*/       SetModified();
/*N*/   return bRet;
/*N*/ }


    // Setze das Attribut im angegebenen Format. Ist Undo aktiv, wird
    // das alte in die Undo-History aufgenommen
/*N*/ void SwDoc::SetAttr( const SfxPoolItem& rAttr, SwFmt& rFmt )
/*N*/ {
/*N*/   SfxItemSet aSet( GetAttrPool(), rAttr.Which(), rAttr.Which() );
/*N*/   aSet.Put( rAttr );
/*N*/   SetAttr( aSet, rFmt );
/*N*/ }


    // Setze das Attribut im angegebenen Format. Ist Undo aktiv, wird
    // das alte in die Undo-History aufgenommen
/*N*/ void SwDoc::SetAttr( const SfxItemSet& rSet, SwFmt& rFmt )
/*N*/ {
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       _UndoFmtAttr aTmp( rFmt );
/*N*/       rFmt.SetAttr( rSet );
/*N*/       if( aTmp.pUndo )
/*N*/           AppendUndo( aTmp.pUndo );
/*N*/   }
/*N*/   else
/*?*/       rFmt.SetAttr( rSet );
/*N*/   SetModified();
/*N*/ }

/*N*/ int lcl_SetNewDefTabStops( SwTwips nOldWidth, SwTwips nNewWidth,
/*N*/                               SvxTabStopItem& rChgTabStop )
/*N*/ {
/*N*/   // dann aender bei allen TabStop die default's auf den neuen Wert
/*N*/   // !!! Achtung: hier wird immer auf dem PoolAttribut gearbeitet,
/*N*/   //              damit nicht in allen Sets die gleiche Berechnung
/*N*/   //              auf dem gleichen TabStop (gepoolt!) vorgenommen
/*N*/   //              wird. Als Modify wird ein FmtChg verschickt.
/*N*/
/*N*/   USHORT nOldCnt = rChgTabStop.Count();
/*N*/   if( !nOldCnt || nOldWidth == nNewWidth )
/*N*/       return FALSE;
/*N*/
/*N*/   // suche den Anfang der Defaults
/*N*/   SvxTabStop* pTabs = ((SvxTabStop*)rChgTabStop.GetStart())
/*N*/                       + (nOldCnt-1);
        USHORT n;
/*N*/   for( n = nOldCnt; n ; --n, --pTabs )
/*N*/       if( SVX_TAB_ADJUST_DEFAULT != pTabs->GetAdjustment() )
/*N*/           break;
/*N*/   ++n;
/*N*/   if( n < nOldCnt )   // die DefTabStops loeschen
/*?*/       rChgTabStop.Remove( n, nOldCnt - n );
/*N*/   return TRUE;
/*N*/ }

    // Setze das Attribut als neues default Attribut in diesem Dokument.
    // Ist Undo aktiv, wird das alte in die Undo-History aufgenommen
/*N*/ void SwDoc::SetDefault( const SfxPoolItem& rAttr )
/*N*/ {
/*N*/   SfxItemSet aSet( GetAttrPool(), rAttr.Which(), rAttr.Which() );
/*N*/   aSet.Put( rAttr );
/*N*/   SetDefault( aSet );
/*N*/ }

/*N*/ void SwDoc::SetDefault( const SfxItemSet& rSet )
/*N*/ {
/*N*/   if( !rSet.Count() )
/*N*/       return;
/*N*/
/*N*/   SwModify aCallMod( 0 );
/*N*/   SwAttrSet aOld( GetAttrPool(), rSet.GetRanges() ),
/*N*/           aNew( GetAttrPool(), rSet.GetRanges() );
/*N*/   SfxItemIter aIter( rSet );
/*N*/   register USHORT nWhich;
/*N*/   const SfxPoolItem* pItem = aIter.GetCurItem();
/*N*/   SfxItemPool* pSdrPool = GetAttrPool().GetSecondaryPool();
/*N*/   while( TRUE )
/*N*/   {
/*N*/       BOOL bCheckSdrDflt = FALSE;
/*N*/       nWhich = pItem->Which();
/*N*/       aOld.Put( GetAttrPool().GetDefaultItem( nWhich ) );
/*N*/       GetAttrPool().SetPoolDefaultItem( *pItem );
/*N*/       aNew.Put( GetAttrPool().GetDefaultItem( nWhich ) );
/*N*/
/*N*/       if( RES_CHRATR_BEGIN <= nWhich && RES_TXTATR_END > nWhich )
/*N*/       {
/*N*/           aCallMod.Add( pDfltTxtFmtColl );
/*N*/           aCallMod.Add( pDfltCharFmt );
/*N*/           bCheckSdrDflt = 0 != pSdrPool;
/*N*/       }
/*N*/       else if( RES_PARATR_BEGIN <= nWhich && RES_PARATR_END > nWhich )
/*N*/       {
/*N*/           aCallMod.Add( pDfltTxtFmtColl );
/*N*/           bCheckSdrDflt = 0 != pSdrPool;
/*N*/       }
/*N*/       else if( RES_GRFATR_BEGIN <= nWhich && RES_GRFATR_END > nWhich )
/*?*/           aCallMod.Add( pDfltGrfFmtColl );
/*?*/       else if( RES_FRMATR_BEGIN <= nWhich && RES_FRMATR_END > nWhich )
/*?*/       {
/*?*/           aCallMod.Add( pDfltGrfFmtColl );
/*?*/           aCallMod.Add( pDfltTxtFmtColl );
/*?*/           aCallMod.Add( pDfltFrmFmt );
/*?*/       }
/*?*/       else if( RES_BOXATR_BEGIN <= nWhich && RES_BOXATR_END > nWhich )
/*?*/           aCallMod.Add( pDfltFrmFmt );

        // copy also the defaults
/*N*/       if( bCheckSdrDflt )
/*N*/       {
/*N*/           USHORT nEdtWhich, nSlotId;
/*N*/           if( 0 != (nSlotId = GetAttrPool().GetSlotId( nWhich ) ) &&
/*N*/               nSlotId != nWhich &&
/*N*/               0 != (nEdtWhich = pSdrPool->GetWhich( nSlotId )) &&
/*N*/               nSlotId != nEdtWhich )
/*N*/           {
/*N*/               SfxPoolItem* pCpy = pItem->Clone();
/*N*/               pCpy->SetWhich( nEdtWhich );
/*N*/               pSdrPool->SetPoolDefaultItem( *pCpy );
/*N*/               delete pCpy;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if( aIter.IsAtEnd() )
/*N*/           break;
/*N*/       pItem = aIter.NextItem();
/*N*/   }
/*N*/
/*N*/   if( aNew.Count() && aCallMod.GetDepends() )
/*N*/   {
/*N*/       if( DoesUndo() )
/*N*/       {
/*N*/           ClearRedo();
/*N*/           AppendUndo( new SwUndoDefaultAttr( aOld ) );
/*N*/       }
/*N*/
/*N*/       const SfxPoolItem* pItem;
/*N*/       if( ( SFX_ITEM_SET ==
/*N*/                 aNew.GetItemState( RES_PARATR_TABSTOP, FALSE, &pItem ) ) &&
/*N*/           ((SvxTabStopItem*)pItem)->Count() )
/*N*/       {
/*N*/           // TabStop-Aenderungen behandeln wir erstmal anders:
/*N*/           // dann aender bei allen TabStop die dafault's auf den neuen Wert
/*N*/           // !!! Achtung: hier wird immer auf dem PoolAttribut gearbeitet,
/*N*/           //              damit nicht in allen Sets die gleiche Berechnung
/*N*/           //              auf dem gleichen TabStop (gepoolt!) vorgenommen
/*N*/           //              wird. Als Modify wird ein FmtChg verschickt.
/*N*/           SwTwips nNewWidth = (*(SvxTabStopItem*)pItem)[ 0 ].GetTabPos(),
/*N*/                   nOldWidth = ((SvxTabStopItem&)aOld.Get(RES_PARATR_TABSTOP))[ 0 ].GetTabPos();
/*N*/
/*N*/           int bChg = FALSE;
/*N*/           USHORT nMaxItems = GetAttrPool().GetItemCount( RES_PARATR_TABSTOP );
/*N*/           for( USHORT n = 0; n < nMaxItems; ++n )
/*N*/               if( 0 != (pItem = GetAttrPool().GetItem( RES_PARATR_TABSTOP, n ) ))
/*N*/                   bChg |= lcl_SetNewDefTabStops( nOldWidth, nNewWidth,
/*N*/                                               *(SvxTabStopItem*)pItem );
/*N*/
/*N*/           aNew.ClearItem( RES_PARATR_TABSTOP );
/*N*/           aOld.ClearItem( RES_PARATR_TABSTOP );
/*N*/           if( bChg )
/*N*/           {
/*N*/               SwFmtChg aChgFmt( pDfltCharFmt );
/*N*/               // dann sage mal den Frames bescheid
/*N*/               aCallMod.Modify( &aChgFmt, &aChgFmt );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( aNew.Count() && aCallMod.GetDepends() )
/*N*/   {
/*N*/       SwAttrSetChg aChgOld( aOld, aOld );
/*N*/       SwAttrSetChg aChgNew( aNew, aNew );
/*N*/       aCallMod.Modify( &aChgOld, &aChgNew );      // alle veraenderten werden verschickt
/*N*/   }
/*N*/
/*N*/   // und die default-Formate wieder beim Object austragen
/*N*/   SwClient* pDep;
/*N*/   while( 0 != ( pDep = (SwClient*)aCallMod.GetDepends()) )
/*N*/       aCallMod.Remove( pDep );
/*N*/
/*N*/   SetModified();
/*N*/ }

    // Erfrage das Default Attribut in diesem Dokument.
/*N*/ const SfxPoolItem& SwDoc::GetDefault( USHORT nFmtHint ) const
/*N*/ {
/*N*/   return GetAttrPool().GetDefaultItem( nFmtHint );
/*N*/ }

/*
 * Loeschen der Formate
 */
//STRIP001 void SwDoc::DelCharFmt(USHORT nFmt)
//STRIP001 {
//STRIP001  pCharFmtTbl->DeleteAndDestroy(nFmt);
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 void SwDoc::DelCharFmt( SwCharFmt *pFmt )
//STRIP001 {
//STRIP001  USHORT nFmt = pCharFmtTbl->GetPos( pFmt );
//STRIP001  ASSERT( USHRT_MAX != nFmt, "Fmt not found," );
//STRIP001  DelCharFmt( nFmt );
//STRIP001 }

/*N*/ void SwDoc::DelFrmFmt( SwFrmFmt *pFmt )
/*N*/ {
/*N*/   if( pFmt->ISA( SwTableBoxFmt ) || pFmt->ISA( SwTableLineFmt ))
/*N*/   {
/*?*/       ASSERT( !this, "Format steht nicht mehr im DocArray, "
/*?*/                      "kann per delete geloescht werden" );
/*?*/       delete pFmt;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //Das Format muss in einem der beiden Arrays stehen, in welchem
/*N*/       //werden wir schon merken.
/*N*/       USHORT nPos;
/*N*/       if ( USHRT_MAX != ( nPos = pFrmFmtTbl->GetPos( pFmt )) )
/*N*/           pFrmFmtTbl->DeleteAndDestroy( nPos );
/*N*/       else
/*N*/       {
/*N*/           nPos = GetSpzFrmFmts()->GetPos( pFmt );
/*N*/           ASSERT( nPos != USHRT_MAX, "FrmFmt not found." );
/*N*/           if( USHRT_MAX != nPos )
/*N*/               GetSpzFrmFmts()->DeleteAndDestroy( nPos );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SwDoc::DelTblFrmFmt( SwTableFmt *pFmt )
/*N*/ {
/*N*/   USHORT nPos = pTblFrmFmtTbl->GetPos( pFmt );
/*N*/   ASSERT( USHRT_MAX != nPos, "Fmt not found," );
/*N*/   pTblFrmFmtTbl->DeleteAndDestroy( nPos );
/*N*/ }

/*
 * Erzeugen der Formate
 */
/*N*/ SwFlyFrmFmt *SwDoc::MakeFlyFrmFmt( const String &rFmtName,
/*N*/                                   SwFrmFmt *pDerivedFrom )
/*N*/ {
/*N*/   SwFlyFrmFmt *pFmt = new SwFlyFrmFmt( GetAttrPool(), rFmtName, pDerivedFrom );
/*N*/   GetSpzFrmFmts()->Insert(pFmt, GetSpzFrmFmts()->Count());
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*N*/ SwDrawFrmFmt *SwDoc::MakeDrawFrmFmt( const String &rFmtName,
/*N*/                                    SwFrmFmt *pDerivedFrom )
/*N*/ {
/*N*/   SwDrawFrmFmt *pFmt = new SwDrawFrmFmt( GetAttrPool(), rFmtName, pDerivedFrom);
/*N*/   GetSpzFrmFmts()->Insert(pFmt,GetSpzFrmFmts()->Count());
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }


/*N*/ USHORT SwDoc::GetTblFrmFmtCount(BOOL bUsed) const
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    USHORT nCount = pTblFrmFmtTbl->Count();
//STRIP001  if(bUsed)
//STRIP001  {
//STRIP001      SwAutoFmtGetDocNode aGetHt( &aNodes );
//STRIP001      for ( USHORT i = nCount; i; )
//STRIP001      {
//STRIP001          if((*pTblFrmFmtTbl)[--i]->GetInfo( aGetHt ))
//STRIP001              --nCount;
//STRIP001      }
//STRIP001  }
//STRIP001  return nCount;
/*N*/ }


/*N*/ SwFrmFmt& SwDoc::GetTblFrmFmt(USHORT nFmt, BOOL bUsed ) const
/*N*/ {
/*?*/   USHORT nRemoved = 0;
/*?*/   if(bUsed)
/*?*/   {
/*?*/       SwAutoFmtGetDocNode aGetHt( &aNodes );
/*?*/       for ( USHORT i = 0; i <= nFmt; i++ )
/*?*/       {
/*?*/           while ( (*pTblFrmFmtTbl)[ i + nRemoved]->GetInfo( aGetHt ))
/*?*/           {
/*?*/               nRemoved++;
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/   return *((*pTblFrmFmtTbl)[nRemoved + nFmt]);
/*N*/}

/*N*/ SwTableFmt* SwDoc::MakeTblFrmFmt( const String &rFmtName,
/*N*/                                   SwFrmFmt *pDerivedFrom )
/*N*/ {
/*N*/   SwTableFmt* pFmt = new SwTableFmt( GetAttrPool(), rFmtName, pDerivedFrom );
/*N*/   pTblFrmFmtTbl->Insert( pFmt, pTblFrmFmtTbl->Count() );
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*N*/ SwFrmFmt *SwDoc::MakeFrmFmt(const String &rFmtName,
/*N*/                           SwFrmFmt *pDerivedFrom)
/*N*/ {
/*N*/   SwFrmFmt *pFmt = new SwFrmFmt( GetAttrPool(), rFmtName, pDerivedFrom );
/*N*/   pFrmFmtTbl->Insert( pFmt, pFrmFmtTbl->Count());
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*N*/ SwCharFmt *SwDoc::MakeCharFmt( const String &rFmtName,
/*N*/                               SwCharFmt *pDerivedFrom)
/*N*/ {
/*N*/   SwCharFmt *pFmt = new SwCharFmt( GetAttrPool(), rFmtName, pDerivedFrom );
/*N*/   pCharFmtTbl->Insert( pFmt, pCharFmtTbl->Count() );
/*N*/   pFmt->SetAuto( FALSE );
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }


/*
 * Erzeugen der FormatCollections
 */
// TXT

/*N*/ SwTxtFmtColl* SwDoc::MakeTxtFmtColl( const String &rFmtName,
/*N*/                                    SwTxtFmtColl *pDerivedFrom)
/*N*/ {
/*N*/   SwTxtFmtColl *pFmtColl = new SwTxtFmtColl( GetAttrPool(), rFmtName,
/*N*/                                               pDerivedFrom );
/*N*/   pTxtFmtCollTbl->Insert(pFmtColl, pTxtFmtCollTbl->Count());
/*N*/   pFmtColl->SetAuto( FALSE );
/*N*/   SetModified();
/*N*/   return pFmtColl;
/*N*/ }

//FEATURE::CONDCOLL
/*NBFF*/SwConditionTxtFmtColl* SwDoc::MakeCondTxtFmtColl( const String &rFmtName,
/*NBFF*/                                                SwTxtFmtColl *pDerivedFrom )
/*NBFF*/{
/*NBFF*/    SwConditionTxtFmtColl*pFmtColl = new SwConditionTxtFmtColl( GetAttrPool(),
/*NBFF*/                                                    rFmtName, pDerivedFrom );
/*NBFF*/    pTxtFmtCollTbl->Insert(pFmtColl, pTxtFmtCollTbl->Count());
/*NBFF*/    pFmtColl->SetAuto( FALSE );
/*NBFF*/    SetModified();
/*NBFF*/    return pFmtColl;
/*NBFF*/}
//FEATURE::CONDCOLL

// GRF

//STRIP001 SwGrfFmtColl* SwDoc::MakeGrfFmtColl( const String &rFmtName,
//STRIP001                                   SwGrfFmtColl *pDerivedFrom )
//STRIP001 {
//STRIP001  SwGrfFmtColl *pFmtColl = new SwGrfFmtColl( GetAttrPool(), rFmtName,
//STRIP001                                              pDerivedFrom );
//STRIP001  pGrfFmtCollTbl->Insert( pFmtColl, pGrfFmtCollTbl->Count() );
//STRIP001  pFmtColl->SetAuto( FALSE );
//STRIP001  SetModified();
//STRIP001  return pFmtColl;
//STRIP001 }

//STRIP001 void SwDoc::DelTxtFmtColl(USHORT nFmtColl)
//STRIP001 {
//STRIP001  ASSERT( nFmtColl, "Remove fuer Coll 0." );
//STRIP001
//STRIP001  // Wer hat die zu loeschende als Next
//STRIP001  SwTxtFmtColl *pDel = (*pTxtFmtCollTbl)[nFmtColl];
//STRIP001  if( pDfltTxtFmtColl == pDel )
//STRIP001      return;     // default nie loeschen !!
//STRIP001  // Die FmtColl austragen
//STRIP001  pTxtFmtCollTbl->Remove(nFmtColl);
//STRIP001  // Next korrigieren
//STRIP001  pTxtFmtCollTbl->ForEach( 1, pTxtFmtCollTbl->Count(),
//STRIP001                          &SetTxtFmtCollNext, pDel );
//STRIP001  delete pDel;
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 void SwDoc::DelTxtFmtColl( SwTxtFmtColl *pColl )
//STRIP001 {
//STRIP001  USHORT nFmt = pTxtFmtCollTbl->GetPos( pColl );
//STRIP001  ASSERT( USHRT_MAX != nFmt, "Collection not found," );
//STRIP001  DelTxtFmtColl( nFmt );
//STRIP001 }

//STRIP001 void SwDoc::DelGrfFmtColl(USHORT nFmtColl)
//STRIP001 {
//STRIP001  ASSERT( nFmtColl, "Remove fuer Coll 0." );
//STRIP001
//STRIP001  // Wer hat die zu loeschende als Next
//STRIP001  SwGrfFmtColl *pDel = (*pGrfFmtCollTbl)[nFmtColl];
//STRIP001  if( pDfltGrfFmtColl == pDel )
//STRIP001      return;     // default nie loeschen !!
//STRIP001  // Die FmtColl austragen
//STRIP001  pGrfFmtCollTbl->Remove(nFmtColl);
//STRIP001  delete pDel;
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 void SwDoc::DelGrfFmtColl( SwGrfFmtColl *pColl )
//STRIP001 {
//STRIP001  USHORT nFmt = pGrfFmtCollTbl->GetPos( pColl );
//STRIP001  ASSERT( USHRT_MAX != nFmt, "Collection not found," );
//STRIP001  DelGrfFmtColl( nFmt );
//STRIP001 }

/*N*/ BOOL lcl_SetTxtFmtColl( const SwNodePtr& rpNode, void* pArgs )
/*N*/ {
/*N*/   // ParaSetFmtColl * pPara = (ParaSetFmtColl*)pArgs;
/*N*/   SwCntntNode* pCNd = (SwCntntNode*)rpNode->GetTxtNode();
/*N*/   if( pCNd )
/*N*/   {
/*N*/       ParaRstFmt* pPara = (ParaRstFmt*)pArgs;
/*N*/       if ( pPara->bReset )
/*N*/           lcl_RstAttr( pCNd, pPara );
/*N*/
/*N*/       // erst in die History aufnehmen, damit ggfs. alte Daten
/*N*/       // gesichert werden koennen
/*N*/       if( pPara->pHistory )
/*N*/           pPara->pHistory->Add( pCNd->GetFmtColl(), pCNd->GetIndex(),
/*N*/                                   ND_TEXTNODE );
/*N*/
/*N*/       pCNd->ChgFmtColl( pPara->pFmtColl );
/*N*/       pPara->nWhich++;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SwDoc::SetTxtFmtColl(const SwPaM &rRg, SwTxtFmtColl *pFmt, BOOL bReset)
/*N*/ {
/*N*/   SwDataChanged aTmp( rRg, 0 );
/*N*/   const SwPosition *pStt = rRg.Start(), *pEnd = rRg.End();
/*N*/   SwHistory* pHst = 0;
/*N*/   BOOL bRet = TRUE;
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       SwUndoFmtColl* pUndo = new SwUndoFmtColl( rRg, pFmt );
/*N*/       pHst = pUndo->GetHistory();
/*N*/       AppendUndo( pUndo );
/*N*/   }
/*N*/
/*N*/   if( rRg.HasMark() )
/*N*/   {
/*N*/       ParaRstFmt aPara( pStt, pEnd, pHst );
/*N*/       aPara.pFmtColl = pFmt;
/*N*/       aPara.bReset = bReset;
/*N*/       GetNodes().ForEach( pStt->nNode.GetIndex(), pEnd->nNode.GetIndex()+1,
/*N*/                           lcl_SetTxtFmtColl, &aPara );
/*N*/       if( !aPara.nWhich )
/*N*/           bRet = FALSE;           // keinen gueltigen Node gefunden
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // ein enzelner Node:
/*N*/       SwCntntNode* pCNd = rRg.GetPoint()->nNode.GetNode().GetCntntNode();
/*N*/       if( pCNd )
/*N*/       {
/*N*/           if( bReset && pCNd->GetpSwAttrSet() )
/*N*/           {
/*?*/               ParaRstFmt aPara( pHst );
/*?*/               aPara.pFmtColl = pFmt;
/*?*/               lcl_RstAttr( pCNd, &aPara );
/*N*/           }
/*N*/
/*N*/           // erst in die History aufnehmen, damit ggfs. alte Daten
/*N*/           // gesichert werden koennen
/*N*/           if( pHst )
/*N*/               pHst->Add( pCNd->GetFmtColl(), pCNd->GetIndex(), ND_TEXTNODE );
/*N*/           pCNd->ChgFmtColl( pFmt );
/*N*/       }
/*N*/       else
/*N*/           bRet = FALSE;
/*N*/   }
/*N*/
/*N*/   if( bRet )
/*N*/       SetModified();
/*N*/   return bRet;
/*N*/ }


// ---- Kopiere die Formate in sich selbst (SwDoc) ----------------------

/*N*/ SwFmt* SwDoc::CopyFmt( const SwFmt& rFmt,
/*N*/                       const SvPtrarr& rFmtArr,
/*N*/                       FNCopyFmt fnCopyFmt, const SwFmt& rDfltFmt )
/*N*/ {
/*N*/   //  kein-Autoformat || default Format || Collection-Format
/*N*/   // dann suche danach.
/*N*/   if( !rFmt.IsAuto() || !rFmt.GetRegisteredIn() )
/*N*/       for( USHORT n = 0; n < rFmtArr.Count(); n++ )
/*N*/       {
/*N*/           // ist die Vorlage schon im Doc vorhanden ??
/*N*/           if( ((SwFmt*)rFmtArr[n])->GetName().Equals( rFmt.GetName() ))
/*N*/               return (SwFmt*)rFmtArr[n];
/*N*/       }
/*N*/
/*N*/   // suche erstmal nach dem "Parent"
/*N*/   SwFmt* pParent = (SwFmt*)&rDfltFmt;
/*N*/   if( rFmt.DerivedFrom() && pParent != rFmt.DerivedFrom() )
/*N*/       pParent = CopyFmt( *rFmt.DerivedFrom(), rFmtArr,
/*N*/                               fnCopyFmt, rDfltFmt );
/*N*/
/*N*/   // erzeuge das Format und kopiere die Attribute
/*?*/   SwFmt* pNewFmt = (this->*fnCopyFmt)( rFmt.GetName(), pParent );
/*?*/   pNewFmt->SetAuto( rFmt.IsAuto() );
/*?*/   pNewFmt->CopyAttrs( rFmt, TRUE );           // kopiere Attribute
/*?*/
/*?*/   pNewFmt->SetPoolFmtId( rFmt.GetPoolFmtId() );
/*?*/   pNewFmt->SetPoolHelpId( rFmt.GetPoolHelpId() );
/*?*/
/*?*/   // HelpFile-Id immer auf dflt setzen !!
/*?*/   pNewFmt->SetPoolHlpFileId( UCHAR_MAX );
/*?*/
/*?*/   return pNewFmt;
/*N*/ }

// ---- kopiere das Frame-Format --------
/*N*/ SwFrmFmt* SwDoc::CopyFrmFmt( const SwFrmFmt& rFmt )
/*N*/ {
/*N*/   return (SwFrmFmt*)CopyFmt( rFmt, *GetFrmFmts(),
/*N*/                               (FNCopyFmt)&SwDoc::MakeFrmFmt,
/*N*/                               *GetDfltFrmFmt() );
/*N*/ }

// ---- kopiere das Char-Format --------
/*N*/ SwCharFmt* SwDoc::CopyCharFmt( const SwCharFmt& rFmt )
/*N*/ {
/*N*/   return (SwCharFmt*)CopyFmt( rFmt, *GetCharFmts(),
/*N*/                               (FNCopyFmt)&SwDoc::MakeCharFmt,
/*N*/                               *GetDfltCharFmt() );
/*N*/ }


// --- Kopiere TextNodes ----

/*N*/ SwTxtFmtColl* SwDoc::CopyTxtColl( const SwTxtFmtColl& rColl )
/*N*/ {
/*N*/   SwTxtFmtColl* pNewColl = FindTxtFmtCollByName( rColl.GetName() );
/*N*/   if( pNewColl )
/*N*/       return pNewColl;

    // suche erstmal nach dem "Parent"
/*?*/   SwTxtFmtColl* pParent = pDfltTxtFmtColl;
/*?*/   if( pParent != rColl.DerivedFrom() )
/*?*/       pParent = CopyTxtColl( *(SwTxtFmtColl*)rColl.DerivedFrom() );
/*?*/

//FEATURE::CONDCOLL
/*?*/   if( RES_CONDTXTFMTCOLL == rColl.Which() )
/*?*/   {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   pNewColl = new SwConditionTxtFmtColl( GetAttrPool(), rColl.GetName(),
//STRIP001 /*?*/                                                pParent);
//STRIP001 /*?*/        pTxtFmtCollTbl->Insert( pNewColl, pTxtFmtCollTbl->Count() );
//STRIP001 /*?*/        pNewColl->SetAuto( FALSE );
//STRIP001 /*?*/        SetModified();
//STRIP001 /*?*/
//STRIP001 /*?*/        // Kopiere noch die Bedingungen
//STRIP001 /*?*/        ((SwConditionTxtFmtColl*)pNewColl)->SetConditions(
//STRIP001 /*?*/                            ((SwConditionTxtFmtColl&)rColl).GetCondColls() );
/*?*/   }
/*?*/   else
/*?*/ //FEATURE::CONDCOLL
/*?*/       pNewColl = MakeTxtFmtColl( rColl.GetName(), pParent );
/*?*/
/*?*/   // kopiere jetzt noch die Auto-Formate oder kopiere die Attribute
/*?*/   pNewColl->CopyAttrs( rColl, TRUE );
/*?*/
/*?*/   // setze noch den Outline-Level
/*?*/   if( NO_NUMBERING != rColl.GetOutlineLevel() )
/*?*/       pNewColl->SetOutlineLevel( rColl.GetOutlineLevel() );
/*?*/
/*?*/   pNewColl->SetPoolFmtId( rColl.GetPoolFmtId() );
/*?*/   pNewColl->SetPoolHelpId( rColl.GetPoolHelpId() );
/*?*/
/*?*/   // HelpFile-Id immer auf dflt setzen !!
/*?*/   pNewColl->SetPoolHlpFileId( UCHAR_MAX );
/*?*/
/*?*/   if( &rColl.GetNextTxtFmtColl() != &rColl )
/*?*/       pNewColl->SetNextTxtFmtColl( *CopyTxtColl( rColl.GetNextTxtFmtColl() ));
/*?*/
/*?*/   // ggfs. die NumRule erzeugen
/*?*/   if( this != rColl.GetDoc() )
/*?*/   {
/*?*/       const SfxPoolItem* pItem;
/*?*/       if( SFX_ITEM_SET == pNewColl->GetItemState( RES_PARATR_NUMRULE,
/*?*/           FALSE, &pItem ))
/*?*/       {
/*?*/           const SwNumRule* pRule;
/*?*/           const String& rName = ((SwNumRuleItem*)pItem)->GetValue();
/*?*/           if( rName.Len() &&
/*?*/               0 != ( pRule = rColl.GetDoc()->FindNumRulePtr( rName )) &&
/*?*/               !pRule->IsAutoRule() )
/*?*/           {
/*?*/               SwNumRule* pDestRule = FindNumRulePtr( rName );
/*?*/               if( pDestRule )
/*?*/                   pDestRule->SetInvalidRule( TRUE );
/*?*/               else
/*?*/                   MakeNumRule( rName, pRule );
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/   return pNewColl;
/*N*/ }

// --- Kopiere GrafikNodes ----

/*N*/ SwGrfFmtColl* SwDoc::CopyGrfColl( const SwGrfFmtColl& rColl )
/*N*/ {
/*N*/   SwGrfFmtColl* pNewColl = FindGrfFmtCollByName( rColl.GetName() );
/*N*/   if( pNewColl )
/*N*/       return pNewColl;

    // suche erstmal nach dem "Parent"
/*?*/   SwGrfFmtColl* pParent = pDfltGrfFmtColl;
/*?*/   if( pParent != rColl.DerivedFrom() )
/*?*/       pParent = CopyGrfColl( *(SwGrfFmtColl*)rColl.DerivedFrom() );
/*?*/
/*?*/   // falls nicht, so kopiere sie
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pNewColl = MakeGrfFmtColl( rColl.GetName(), pParent );
/*?*/
/*?*/   // noch die Attribute kopieren
/*?*/   pNewColl->CopyAttrs( rColl );
/*?*/
/*?*/   pNewColl->SetPoolFmtId( rColl.GetPoolFmtId() );
/*?*/   pNewColl->SetPoolHelpId( rColl.GetPoolHelpId() );
/*?*/
/*?*/   // HelpFile-Id immer auf dflt setzen !!
/*?*/   pNewColl->SetPoolHlpFileId( UCHAR_MAX );
/*?*/
/*?*/   return pNewColl;
/*N*/ }

//STRIP001 SwPageDesc* lcl_FindPageDesc( const SwPageDescs& rArr, const String& rName )
//STRIP001 {
//STRIP001  for( USHORT n = rArr.Count(); n; )
//STRIP001  {
//STRIP001      SwPageDesc* pDesc = rArr[ --n ];
//STRIP001      if( pDesc->GetName() == rName )
//STRIP001          return pDesc;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SwDoc::CopyFmtArr( const SvPtrarr& rSourceArr,
//STRIP001                      SvPtrarr& rDestArr,
//STRIP001                      FNCopyFmt fnCopyFmt,
//STRIP001                      SwFmt& rDfltFmt )
//STRIP001 {
//STRIP001  USHORT nSrc;
//STRIP001  SwFmt* pSrc, *pDest;
//STRIP001
//STRIP001  // 1. Schritt alle Formate anlegen (das 0. ueberspringen - Default!)
//STRIP001  for( nSrc = rSourceArr.Count(); nSrc > 1; )
//STRIP001  {
//STRIP001      pSrc = (SwFmt*)rSourceArr[ --nSrc ];
//STRIP001      if( pSrc->IsDefault() || pSrc->IsAuto() )
//STRIP001          continue;
//STRIP001
//STRIP001      if( 0 == FindFmtByName( rDestArr, pSrc->GetName() ) )
//STRIP001      {
//STRIP001          if( RES_CONDTXTFMTCOLL == pSrc->Which() )
//STRIP001              MakeCondTxtFmtColl( pSrc->GetName(), (SwTxtFmtColl*)&rDfltFmt );
//STRIP001          else
//STRIP001              (this->*fnCopyFmt)( pSrc->GetName(), &rDfltFmt );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // 2. Schritt alle Attribute kopieren, richtige Parents setzen
//STRIP001  for( nSrc = rSourceArr.Count(); nSrc > 1; )
//STRIP001  {
//STRIP001      pSrc = (SwFmt*)rSourceArr[ --nSrc ];
//STRIP001      if( pSrc->IsDefault() || pSrc->IsAuto() )
//STRIP001          continue;
//STRIP001
//STRIP001      pDest = FindFmtByName( rDestArr, pSrc->GetName() );
//STRIP001      pDest->SetAuto( FALSE );
//STRIP001 //       pDest->ResetAllAttr();
//STRIP001 //       pDest->CopyAttrs( *pSrc, TRUE );            // kopiere Attribute
//STRIP001 //JP 19.02.96: ist so wohl optimaler - loest ggfs. kein Modify aus!
//STRIP001      pDest->DelDiffs( *pSrc );
//STRIP001      pDest->SetAttr( pSrc->GetAttrSet() );       // kopiere Attribute
//STRIP001
//STRIP001      //JP 18.08.98: Bug 55115 - PageDescAttribute in diesem Fall doch
//STRIP001      //              kopieren
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if( &GetAttrPool() != pSrc->GetAttrSet().GetPool() &&
//STRIP001          SFX_ITEM_SET == pSrc->GetAttrSet().GetItemState(
//STRIP001          RES_PAGEDESC, FALSE, &pItem ) &&
//STRIP001          ((SwFmtPageDesc*)pItem)->GetPageDesc() )
//STRIP001      {
//STRIP001          SwFmtPageDesc aDesc( *(SwFmtPageDesc*)pItem );
//STRIP001          const String& rNm = aDesc.GetPageDesc()->GetName();
//STRIP001          SwPageDesc* pDesc = ::lcl_FindPageDesc( aPageDescs, rNm );
//STRIP001          if( !pDesc )
//STRIP001              pDesc = aPageDescs[ MakePageDesc( rNm ) ];
//STRIP001          pDesc->Add( &aDesc );
//STRIP001          pDest->SetAttr( aDesc );
//STRIP001      }
//STRIP001
//STRIP001      pDest->SetPoolFmtId( pSrc->GetPoolFmtId() );
//STRIP001      pDest->SetPoolHelpId( pSrc->GetPoolHelpId() );
//STRIP001
//STRIP001      // HelpFile-Id immer auf dflt setzen !!
//STRIP001      pDest->SetPoolHlpFileId( UCHAR_MAX );
//STRIP001
//STRIP001      if( pSrc->DerivedFrom() )
//STRIP001          pDest->SetDerivedFrom( FindFmtByName( rDestArr,
//STRIP001                                      pSrc->DerivedFrom()->GetName() ) );
//STRIP001      if( RES_TXTFMTCOLL == pSrc->Which() ||
//STRIP001          RES_CONDTXTFMTCOLL == pSrc->Which() )
//STRIP001      {
//STRIP001          SwTxtFmtColl* pSrcColl = (SwTxtFmtColl*)pSrc,
//STRIP001                      * pDstColl = (SwTxtFmtColl*)pDest;
//STRIP001          if( &pSrcColl->GetNextTxtFmtColl() != pSrcColl )
//STRIP001              pDstColl->SetNextTxtFmtColl( *(SwTxtFmtColl*)FindFmtByName(
//STRIP001                  rDestArr, pSrcColl->GetNextTxtFmtColl().GetName() ) );
//STRIP001
//STRIP001          // setze noch den Outline-Level
//STRIP001          if( NO_NUMBERING != pSrcColl->GetOutlineLevel() )
//STRIP001              pDstColl->SetOutlineLevel( pSrcColl->GetOutlineLevel() );
//STRIP001
//STRIP001 //FEATURE::CONDCOLL
//STRIP001          if( RES_CONDTXTFMTCOLL == pSrc->Which() )
//STRIP001              // Kopiere noch die Bedingungen
//STRIP001              // aber erst die alten loeschen!
//STRIP001              ((SwConditionTxtFmtColl*)pDstColl)->SetConditions(
//STRIP001                          ((SwConditionTxtFmtColl*)pSrc)->GetCondColls() );
//STRIP001 //FEATURE::CONDCOLL
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwDoc::_CopyPageDescHeaderFooter( BOOL bCpyHeader,
//STRIP001                              const SwFrmFmt& rSrcFmt, SwFrmFmt& rDestFmt )
//STRIP001 {
//STRIP001  // jetzt noch Header-/Footer-Attribute richtig behandeln
//STRIP001  // Contenten Nodes Dokumentuebergreifend kopieren!
//STRIP001  USHORT nAttr = bCpyHeader ? RES_HEADER : RES_FOOTER;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  if( SFX_ITEM_SET != rSrcFmt.GetAttrSet().GetItemState( nAttr, FALSE, &pItem ))
//STRIP001      return ;
//STRIP001
//STRIP001  // Im Header steht noch der Verweis auf das Format aus dem
//STRIP001  // anderen Document!!
//STRIP001  SfxPoolItem* pNewItem = pItem->Clone();
//STRIP001
//STRIP001  SwFrmFmt* pOldFmt;
//STRIP001  if( bCpyHeader )
//STRIP001       pOldFmt = ((SwFmtHeader*)pNewItem)->GetHeaderFmt();
//STRIP001  else
//STRIP001       pOldFmt = ((SwFmtFooter*)pNewItem)->GetFooterFmt();
//STRIP001
//STRIP001  if( pOldFmt )
//STRIP001  {
//STRIP001      SwFrmFmt* pNewFmt = new SwFrmFmt( GetAttrPool(), "CpyDesc",
//STRIP001                                          GetDfltFrmFmt() );
//STRIP001      pNewFmt->CopyAttrs( *pOldFmt, TRUE );
//STRIP001
//STRIP001      if( SFX_ITEM_SET == pNewFmt->GetAttrSet().GetItemState(
//STRIP001          RES_CNTNT, FALSE, &pItem ))
//STRIP001      {
//STRIP001          SwFmtCntnt* pCntnt = (SwFmtCntnt*)pItem;
//STRIP001          if( pCntnt->GetCntntIdx() )
//STRIP001          {
//STRIP001              SwNodeIndex aTmpIdx( GetNodes().GetEndOfAutotext() );
//STRIP001              const SwNodes& rSrcNds = rSrcFmt.GetDoc()->GetNodes();
//STRIP001              SwStartNode* pSttNd = GetNodes().MakeEmptySection( aTmpIdx,
//STRIP001                                              bCpyHeader
//STRIP001                                                  ? SwHeaderStartNode
//STRIP001                                                  : SwFooterStartNode );
//STRIP001              const SwNode& rCSttNd = pCntnt->GetCntntIdx()->GetNode();
//STRIP001              SwNodeRange aRg( rCSttNd, 0, *rCSttNd.EndOfSectionNode() );
//STRIP001              aTmpIdx = *pSttNd->EndOfSectionNode();
//STRIP001              rSrcNds._Copy( aRg, aTmpIdx );
//STRIP001              aTmpIdx = *pSttNd;
//STRIP001              rSrcFmt.GetDoc()->_CopyFlyInFly( aRg, aTmpIdx );
//STRIP001              pNewFmt->SetAttr( SwFmtCntnt( pSttNd ));
//STRIP001          }
//STRIP001          else
//STRIP001              pNewFmt->ResetAttr( RES_CNTNT );
//STRIP001      }
//STRIP001      if( bCpyHeader )
//STRIP001          pNewFmt->Add( (SwFmtHeader*)pNewItem );
//STRIP001      else
//STRIP001          pNewFmt->Add( (SwFmtFooter*)pNewItem );
//STRIP001      rDestFmt.SetAttr( *pNewItem );
//STRIP001  }
//STRIP001  delete pNewItem;
//STRIP001 }

/*N*/ void SwDoc::CopyPageDesc( const SwPageDesc& rSrcDesc, SwPageDesc& rDstDesc,
/*N*/                           BOOL bCopyPoolIds )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   FASTBOOL bNotifyLayout = FALSE;
//STRIP001
//STRIP001  rDstDesc.SetLandscape( rSrcDesc.GetLandscape() );
//STRIP001  rDstDesc.SetNumType( rSrcDesc.GetNumType() );
//STRIP001  if( rDstDesc.ReadUseOn() != rSrcDesc.ReadUseOn() )
//STRIP001  {
//STRIP001      rDstDesc.WriteUseOn( rSrcDesc.ReadUseOn() );
//STRIP001      bNotifyLayout = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if( bCopyPoolIds )
//STRIP001  {
//STRIP001      rDstDesc.SetPoolFmtId( rSrcDesc.GetPoolFmtId() );
//STRIP001      rDstDesc.SetPoolHelpId( rSrcDesc.GetPoolHelpId() );
//STRIP001      // HelpFile-Id immer auf dflt setzen !!
//STRIP001      rDstDesc.SetPoolHlpFileId( UCHAR_MAX );
//STRIP001  }
//STRIP001
//STRIP001  if( rSrcDesc.GetFollow() != &rSrcDesc )
//STRIP001  {
//STRIP001      SwPageDesc* pFollow = ::lcl_FindPageDesc( aPageDescs,
//STRIP001                                  rSrcDesc.GetFollow()->GetName() );
//STRIP001      if( !pFollow )
//STRIP001      {
//STRIP001          // dann mal kopieren
//STRIP001          USHORT nPos = MakePageDesc( rSrcDesc.GetFollow()->GetName() );
//STRIP001          pFollow = aPageDescs[ nPos ];
//STRIP001          CopyPageDesc( *rSrcDesc.GetFollow(), *pFollow );
//STRIP001      }
//STRIP001      rDstDesc.SetFollow( pFollow );
//STRIP001      bNotifyLayout = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // die Header/Footer-Attribute werden gesondert kopiert, die Content-
//STRIP001  // Sections muessen vollstaendig mitgenommen werden!
//STRIP001  {
//STRIP001      SfxItemSet aAttrSet( rSrcDesc.GetMaster().GetAttrSet() );
//STRIP001      aAttrSet.ClearItem( RES_HEADER );
//STRIP001      aAttrSet.ClearItem( RES_FOOTER );
//STRIP001
//STRIP001      rDstDesc.GetMaster().DelDiffs( aAttrSet );
//STRIP001      rDstDesc.GetMaster().SetAttr( aAttrSet );
//STRIP001
//STRIP001      aAttrSet.ClearItem();
//STRIP001      aAttrSet.Put( rSrcDesc.GetLeft().GetAttrSet() );
//STRIP001      aAttrSet.ClearItem( RES_HEADER );
//STRIP001      aAttrSet.ClearItem( RES_FOOTER );
//STRIP001
//STRIP001      rDstDesc.GetLeft().DelDiffs( aAttrSet );
//STRIP001      rDstDesc.GetLeft().SetAttr( aAttrSet );
//STRIP001  }
//STRIP001
//STRIP001  CopyHeader( rSrcDesc.GetMaster(), rDstDesc.GetMaster() );
//STRIP001  CopyFooter( rSrcDesc.GetMaster(), rDstDesc.GetMaster() );
//STRIP001  if( !rDstDesc.IsHeaderShared() )
//STRIP001      CopyHeader( rSrcDesc.GetLeft(), rDstDesc.GetLeft() );
//STRIP001  else
//STRIP001      rDstDesc.GetLeft().SetAttr( rDstDesc.GetMaster().GetHeader() );
//STRIP001
//STRIP001  if( !rDstDesc.IsFooterShared() )
//STRIP001      CopyFooter( rSrcDesc.GetLeft(), rDstDesc.GetLeft() );
//STRIP001  else
//STRIP001      rDstDesc.GetLeft().SetAttr( rDstDesc.GetMaster().GetFooter() );
//STRIP001
//STRIP001  if( bNotifyLayout && GetRootFrm() )
//STRIP001      //Layot benachrichtigen!
//STRIP001      GetRootFrm()->CheckPageDescs( (SwPageFrm*)GetRootFrm()->Lower() );
//STRIP001
//STRIP001  //Wenn sich FussnotenInfo veraendert, so werden die Seiten
//STRIP001  //angetriggert.
//STRIP001  if( !(rDstDesc.GetFtnInfo() == rSrcDesc.GetFtnInfo()) )
//STRIP001  {
//STRIP001      rDstDesc.SetFtnInfo( rSrcDesc.GetFtnInfo() );
//STRIP001      SwMsgPoolItem  aInfo( RES_PAGEDESC_FTNINFO );
//STRIP001      {
//STRIP001          SwClientIter aIter( rDstDesc.GetMaster() );
//STRIP001          for( SwClient* pLast = aIter.First(TYPE(SwFrm)); pLast;
//STRIP001                  pLast = aIter.Next() )
//STRIP001              pLast->Modify( &aInfo, 0 );
//STRIP001      }
//STRIP001      {
//STRIP001          SwClientIter aIter( rDstDesc.GetLeft() );
//STRIP001          for( SwClient* pLast = aIter.First(TYPE(SwFrm)); pLast;
//STRIP001                  pLast = aIter.Next() )
//STRIP001              pLast->Modify( &aInfo, 0 );
//STRIP001      }
//STRIP001  }
/*N*/ }

//STRIP001 void SwDoc::ReplaceStyles( SwDoc& rSource )
//STRIP001 {
//STRIP001  BOOL bIsUndo = DoesUndo();
//STRIP001  DoUndo( FALSE );
//STRIP001
//STRIP001  CopyFmtArr( *rSource.pCharFmtTbl, *pCharFmtTbl,
//STRIP001              (FNCopyFmt)&SwDoc::MakeCharFmt, *pDfltCharFmt );
//STRIP001  CopyFmtArr( *rSource.pFrmFmtTbl, *pFrmFmtTbl,
//STRIP001              (FNCopyFmt)&SwDoc::MakeFrmFmt, *pDfltFrmFmt );
//STRIP001  CopyFmtArr( *rSource.pTxtFmtCollTbl, *pTxtFmtCollTbl,
//STRIP001              (FNCopyFmt)&SwDoc::MakeTxtFmtColl, *pDfltTxtFmtColl );
//STRIP001
//STRIP001  // und jetzt noch die Seiten-Vorlagen
//STRIP001  USHORT nCnt = rSource.aPageDescs.Count();
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      // ein anderes Doc -> Numberformatter muessen gemergt werden
//STRIP001      SwTblNumFmtMerge aTNFM( rSource, *this );
//STRIP001
//STRIP001      // 1. Schritt alle Formate anlegen (das 0. ueberspringen - Default!)
//STRIP001      while( nCnt )
//STRIP001      {
//STRIP001          SwPageDesc *pSrc = rSource.aPageDescs[ --nCnt ];
//STRIP001          if( 0 == ::lcl_FindPageDesc( aPageDescs, pSrc->GetName() ) )
//STRIP001              MakePageDesc( pSrc->GetName() );
//STRIP001      }
//STRIP001
//STRIP001      // 2. Schritt alle Attribute kopieren, richtige Parents setzen
//STRIP001      for( nCnt = rSource.aPageDescs.Count(); nCnt; )
//STRIP001      {
//STRIP001          SwPageDesc *pSrc = rSource.aPageDescs[ --nCnt ];
//STRIP001          CopyPageDesc( *pSrc, *::lcl_FindPageDesc( aPageDescs, pSrc->GetName() ));
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //JP 08.04.99: und dann sind da noch die Numerierungs-Vorlagen
//STRIP001  nCnt = rSource.GetNumRuleTbl().Count();
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      const SwNumRuleTbl& rArr = rSource.GetNumRuleTbl();
//STRIP001      for( USHORT n = 0; n < nCnt; ++n )
//STRIP001      {
//STRIP001          const SwNumRule& rR = *rArr[ n ];
//STRIP001          if( !rR.IsAutoRule() )
//STRIP001          {
//STRIP001              SwNumRule* pNew = FindNumRulePtr( rR.GetName());
//STRIP001              if( pNew )
//STRIP001                  pNew->CopyNumRule( this, rR );
//STRIP001              else
//STRIP001                  MakeNumRule( rR.GetName(), &rR );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bIsUndo )
//STRIP001  {
//STRIP001      // es wurde am Nodes-Array gedreht!
//STRIP001      ClearRedo();
//STRIP001      DelAllUndoObj();
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001  DoUndo( bIsUndo );
//STRIP001 }

/*N*/ SwFmt* SwDoc::FindFmtByName( const SvPtrarr& rFmtArr,
/*N*/                                   const String& rName ) const
/*N*/ {
/*N*/   SwFmt* pFnd = 0;
/*N*/   for( USHORT n = 0; n < rFmtArr.Count(); n++ )
/*N*/   {
/*N*/       // ist die Vorlage schon im Doc vorhanden ??
/*N*/       if( ((SwFmt*)rFmtArr[n])->GetName() == rName )
/*N*/       {
/*N*/           pFnd = (SwFmt*)rFmtArr[n];
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   return pFnd;
/*N*/ }

//STRIP001 void SwDoc::MoveLeftMargin( const SwPaM& rPam, BOOL bRight, BOOL bModulus )
//STRIP001 {
//STRIP001  SwHistory* pHistory = 0;
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      SwUndoMoveLeftMargin* pUndo = new SwUndoMoveLeftMargin( rPam, bRight,
//STRIP001                                                              bModulus );
//STRIP001      pHistory = pUndo->GetHistory();
//STRIP001      AppendUndo( pUndo );
//STRIP001  }
//STRIP001
//STRIP001  const SvxTabStopItem& rTabItem = (SvxTabStopItem&)GetDefault( RES_PARATR_TABSTOP );
//STRIP001  USHORT nDefDist = rTabItem.Count() ? rTabItem[0].GetTabPos() : 1134;
//STRIP001  const SwPosition &rStt = *rPam.Start(), &rEnd = *rPam.End();
//STRIP001  SwNodeIndex aIdx( rStt.nNode );
//STRIP001  while( aIdx <= rEnd.nNode )
//STRIP001  {
//STRIP001      SwTxtNode* pTNd = aIdx.GetNode().GetTxtNode();
//STRIP001      if( pTNd )
//STRIP001      {
//STRIP001          SvxLRSpaceItem aLS( (SvxLRSpaceItem&)pTNd->SwCntntNode::GetAttr(
//STRIP001                                                      RES_LR_SPACE ) );
//STRIP001          USHORT nNext = aLS.GetTxtLeft();
//STRIP001          if( bModulus )
//STRIP001              nNext = ( nNext / nDefDist ) * nDefDist;
//STRIP001
//STRIP001          if( bRight )
//STRIP001              nNext += nDefDist;
//STRIP001          else if( nNext )
//STRIP001          {
//STRIP001              if( !bModulus && nDefDist > nNext )
//STRIP001                  nNext = 0;
//STRIP001              else
//STRIP001                  nNext -= nDefDist;
//STRIP001          }
//STRIP001          aLS.SetTxtLeft( nNext );
//STRIP001
//STRIP001          SwRegHistory aRegH( pTNd, *pTNd, pHistory );
//STRIP001          pTNd->SwCntntNode::SetAttr( aLS );
//STRIP001      }
//STRIP001      aIdx++;
//STRIP001  }
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 BOOL SwDoc::DontExpandFmt( const SwPosition& rPos, BOOL bFlag )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwTxtNode* pTxtNd = rPos.nNode.GetNode().GetTxtNode();
//STRIP001  if( pTxtNd )
//STRIP001  {
//STRIP001      bRet = pTxtNd->DontExpandFmt( rPos.nContent, bFlag );
//STRIP001      if( bRet && DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoDontExpandFmt( rPos ));
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ SwTableBoxFmt* SwDoc::MakeTableBoxFmt()
/*N*/ {
/*N*/   SwTableBoxFmt* pFmt = new SwTableBoxFmt( GetAttrPool(), aEmptyStr,
/*N*/                                               pDfltFrmFmt );
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*N*/ SwTableLineFmt* SwDoc::MakeTableLineFmt()
/*N*/ {
/*N*/   SwTableLineFmt* pFmt = new SwTableLineFmt( GetAttrPool(), aEmptyStr,
/*N*/                                               pDfltFrmFmt );
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*N*/ void SwDoc::_CreateNumberFormatter()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDoc::_CreateNumberFormatter" );
/*N*/
/*N*/   ASSERT( !pNumberFormatter, "ist doch schon vorhanden" );
/*N*/
/*N*/
/*N*/   LanguageType eLang = LANGUAGE_SYSTEM; //System::GetLanguage();
/*              ((const SvxLanguageItem&)GetAttrPool().
                    GetDefaultItem( RES_CHRATR_LANGUAGE )).GetLanguage();
*/
/*N*/   Reference< XMultiServiceFactory > xMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   pNumberFormatter = new SvNumberFormatter( xMSF, eLang );
/*N*/   pNumberFormatter->SetEvalDateFormat( NF_EVALDATEFORMAT_FORMAT_INTL );
/*N*/   pNumberFormatter->SetYear2000(SFX_APP()->GetMiscConfig()->GetYear2000());
/*N*/
/*N*/ }

/*N*/ SwTblNumFmtMerge::SwTblNumFmtMerge( const SwDoc& rSrc, SwDoc& rDest )
/*N*/   : pNFmt( 0 )
/*N*/ {
/*N*/   // ein anderes Doc -> Numberformatter muessen gemergt werden
/*N*/   SvNumberFormatter* pN;
/*N*/   if( &rSrc != &rDest && 0 != ( pN = ((SwDoc&)rSrc).GetNumberFormatter( FALSE ) ))
/*N*/       ( pNFmt = rDest.GetNumberFormatter( TRUE ))->MergeFormatter( *pN );
/*N*/
/*N*/   if( &rSrc != &rDest )
/*N*/       ((SwGetRefFieldType*)rSrc.GetSysFldType( RES_GETREFFLD ))->
/*N*/           MergeWithOtherDoc( rDest );
/*N*/ }

/*N*/ SwTblNumFmtMerge::~SwTblNumFmtMerge()
/*N*/ {
/*N*/   if( pNFmt )
/*N*/       pNFmt->ClearMergeTable();
/*N*/ }


//STRIP001 void SwDoc::SetTxtFmtCollByAutoFmt( const SwPosition& rPos, USHORT nPoolId,
//STRIP001                                  const SfxItemSet* pSet )
//STRIP001 {
//STRIP001  SwPaM aPam( rPos );
//STRIP001  SwTxtNode* pTNd = rPos.nNode.GetNode().GetTxtNode();
//STRIP001
//STRIP001  if( bIsAutoFmtRedline && pTNd )
//STRIP001  {
//STRIP001      // dann das Redline Object anlegen
//STRIP001      const SwTxtFmtColl& rColl = *pTNd->GetTxtColl();
//STRIP001      SwRedline* pRedl = new SwRedline( REDLINE_FMTCOLL, aPam );
//STRIP001      pRedl->SetMark();
//STRIP001
//STRIP001      // interressant sind nur die Items, die vom Set NICHT wieder
//STRIP001      // in den Node gesetzt werden. Also muss man die Differenz nehmen
//STRIP001      SwRedlineExtraData_FmtColl aExtraData( rColl.GetName(),
//STRIP001                                              rColl.GetPoolFmtId() );
//STRIP001      if( pSet && pTNd->GetpSwAttrSet() )
//STRIP001      {
//STRIP001          SfxItemSet aTmp( *pTNd->GetpSwAttrSet() );
//STRIP001          aTmp.Differentiate( *pSet );
//STRIP001          // das Adjust Item behalten wir extra
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == pTNd->GetpSwAttrSet()->GetItemState(
//STRIP001                  RES_PARATR_ADJUST, FALSE, &pItem ))
//STRIP001              aTmp.Put( *pItem );
//STRIP001          aExtraData.SetItemSet( aTmp );
//STRIP001      }
//STRIP001      pRedl->SetExtraData( &aExtraData );
//STRIP001
//STRIP001 // !!!!!!!!! Undo fehlt noch !!!!!!!!!!!!!!!!!!
//STRIP001      AppendRedline( pRedl );
//STRIP001  }
//STRIP001
//STRIP001  SetTxtFmtColl( aPam, GetTxtCollFromPool( nPoolId ) );
//STRIP001
//STRIP001  if( pSet && pTNd && pSet->Count() )
//STRIP001  {
//STRIP001      aPam.SetMark();
//STRIP001      aPam.GetMark()->nContent.Assign( pTNd, pTNd->GetTxt().Len() );
//STRIP001      Insert( aPam, *pSet );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwDoc::SetFmtItemByAutoFmt( const SwPaM& rPam, const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SwTxtNode* pTNd = rPam.GetPoint()->nNode.GetNode().GetTxtNode();
//STRIP001
//STRIP001  SwRedlineMode eOld = GetRedlineMode();
//STRIP001
//STRIP001  if( bIsAutoFmtRedline && pTNd )
//STRIP001  {
//STRIP001      // dann das Redline Object anlegen
//STRIP001      SwRedline* pRedl = new SwRedline( REDLINE_FORMAT, rPam );
//STRIP001      if( !pRedl->HasMark() )
//STRIP001          pRedl->SetMark();
//STRIP001
//STRIP001      // interressant sind nur die Items, die vom Set NICHT wieder
//STRIP001      // in den Node gesetzt werden. Also muss man die Differenz nehmen
//STRIP001      SwRedlineExtraData_Format aExtraData( rSet );
//STRIP001
//STRIP001 /*
//STRIP001      if( pSet && pTNd->GetpSwAttrSet() )
//STRIP001      {
//STRIP001          SfxItemSet aTmp( *pTNd->GetpSwAttrSet() );
//STRIP001          aTmp.Differentiate( *pSet );
//STRIP001          // das Adjust Item behalten wir extra
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == pTNd->GetpSwAttrSet()->GetItemState(
//STRIP001                  RES_PARATR_ADJUST, FALSE, &pItem ))
//STRIP001              aTmp.Put( *pItem );
//STRIP001          aExtraData.SetItemSet( aTmp );
//STRIP001      }
//STRIP001 */
//STRIP001      pRedl->SetExtraData( &aExtraData );
//STRIP001
//STRIP001 // !!!!!!!!! Undo fehlt noch !!!!!!!!!!!!!!!!!!
//STRIP001      AppendRedline( pRedl );
//STRIP001
//STRIP001      SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001  }
//STRIP001
//STRIP001  Insert( rPam, rSet, SETATTR_DONTEXPAND );
//STRIP001  SetRedlineMode_intern( eOld );
//STRIP001 }

}
