/*************************************************************************
 *
 *  $RCSfile: sw_doclay.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:11:12 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SVDMODEL_HXX //autogen
#include <bf_svx/svdmodel.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifndef _SVX_KEEPITEM_HXX //autogen
#include <bf_svx/keepitem.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_SHADITEM_HXX //autogen
#include <bf_svx/shaditem.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_OPAQITEM_HXX //autogen
#include <bf_svx/opaqitem.hxx>
#endif
#ifndef _SVX_PRNTITEM_HXX //autogen
#include <bf_svx/prntitem.hxx>
#endif
#ifndef _SVX_FMGLOB_HXX
#include <bf_svx/fmglob.hxx>
#endif
#ifndef _SVDOUNO_HXX //autogen
#include <bf_svx/svdouno.hxx>
#endif
#ifndef _SVX_FMPAGE_HXX
#include <bf_svx/fmpage.hxx>
#endif
#ifndef _SVX_FRMDIRITEM_HXX
#include <bf_svx/frmdiritem.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTSRND_HXX //autogen
#include <fmtsrnd.hxx>
#endif
#ifndef _FMTFLCNT_HXX //autogen
#include <fmtflcnt.hxx>
#endif
#ifndef _FRMCNCT_HXX //autogen
#include <fmtcnct.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _DCONTACT_HXX //autogen
#include <dcontact.hxx>
#endif
#ifndef _TXTFLCNT_HXX //autogen
#include <txtflcnt.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>   // fuer Expression-Felder
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _NDNOTXT_HXX
#include <ndnotxt.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _FLYPOS_HXX
#include <flypos.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>       // InsertLabel
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>      // PoolVorlagen-Id's
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _FLDUPDE_HXX
#include <fldupde.hxx>
#endif
#ifndef _TXTFTN_HXX
#include <txtftn.hxx>
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif

#ifndef _COMCORE_HRC
#include <comcore.hrc>      // STR-ResId's
#endif

// #i11176#
#ifndef _UNOFRAME_HXX
#include <unoframe.hxx>
#endif

using namespace ::com::sun::star;
using namespace ::rtl;

#define DEF_FLY_WIDTH    2268   //Defaultbreite fuer FlyFrms    (2268 == 4cm)

/* #109161# */
static bool lcl_IsItemSet(const SwCntntNode & rNode, USHORT which)
{
    bool bResult = false;

    if (SFX_ITEM_SET == rNode.GetSwAttrSet().GetItemState(which))
        bResult = true;

    return bResult;
}

/*************************************************************************
|*
|*  SwDoc::MakeLayoutFmt()
|*
|*  Beschreibung        Erzeugt ein neues Format das in seinen Einstellungen
|*      Defaultmaessig zu dem Request passt. Das Format wird in das
|*      entsprechende Formate-Array gestellt.
|*      Wenn bereits ein passendes Format existiert, so wird dies
|*      zurueckgeliefert.
|*  Ersterstellung      MA 22. Sep. 92
|*  Letzte Aenderung    JP 08.05.98
|*
|*************************************************************************/

/*N*/ SwFrmFmt *SwDoc::MakeLayoutFmt( RndStdIds eRequest, SwFrmFmt* pFrmFmt,
/*N*/                               const SfxItemSet* pSet )
/*N*/ {
/*N*/   SwFrmFmt *pFmt = 0;
/*N*/   const sal_Bool bMod = IsModified();
/*N*/   sal_Bool bHeader = sal_False;
/*N*/
/*N*/   switch ( eRequest )
/*N*/   {
/*N*/   case RND_STD_HEADER:
/*N*/   case RND_STD_HEADERL:
/*N*/   case RND_STD_HEADERR:
/*N*/       {
/*N*/           bHeader = sal_True;
/*N*/           // kein break, es geht unten weiter
/*N*/       }
/*N*/   case RND_STD_FOOTER:
/*N*/   case RND_STD_FOOTERL:
/*N*/   case RND_STD_FOOTERR:
/*N*/       {
/*N*/
/*N*/ //JP erstmal ein Hack, solange keine Flys/Headers/Footers Undofaehig sind
/*N*/ if( DoesUndo() )
/*N*/   DelAllUndoObj();
/*N*/
/*N*/           pFmt = new SwFrmFmt( GetAttrPool(),
/*N*/                               (bHeader ? "Header" : "Footer"),
/*N*/                               GetDfltFrmFmt() );
/*N*/
/*N*/           SwNodeIndex aTmpIdx( GetNodes().GetEndOfAutotext() );
/*N*/           SwStartNode* pSttNd = GetNodes().MakeTextSection( aTmpIdx,
/*N*/                               bHeader ? SwHeaderStartNode : SwFooterStartNode,
/*N*/                               GetTxtCollFromPool(
/*N*/                               bHeader
/*N*/                                   ? ( eRequest == RND_STD_HEADERL
/*N*/                                       ? RES_POOLCOLL_HEADERL
/*N*/                                       : eRequest == RND_STD_HEADERR
/*N*/                                           ? RES_POOLCOLL_HEADERR
/*N*/                                           : RES_POOLCOLL_HEADER )
/*N*/                                   : ( eRequest == RND_STD_FOOTERL
/*N*/                                       ? RES_POOLCOLL_FOOTERL
/*N*/                                       : eRequest == RND_STD_FOOTERR
/*N*/                                           ? RES_POOLCOLL_FOOTERR
/*N*/                                           : RES_POOLCOLL_FOOTER )
/*N*/                                   ) );
/*N*/           pFmt->SetAttr( SwFmtCntnt( pSttNd ));
/*N*/
/*N*/           if( pSet )      // noch ein paar Attribute setzen ?
/*N*/               pFmt->SetAttr( *pSet );
/*N*/
/*N*/ // JP: warum zuruecksetzen ???    Doc. ist doch veraendert ???
/*N*/ // bei den Fly auf jedenfall verkehrt !!
/*N*/           if ( !bMod )
/*?*/               ResetModified();
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case RND_DRAW_OBJECT:
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 pFmt = MakeDrawFrmFmt( aEmptyStr, GetDfltFrmFmt() );
//STRIP001 /*?*/            if( pSet )      // noch ein paar Attribute setzen ?
//STRIP001 /*?*/                pFmt->SetAttr( *pSet );
//STRIP001 /*?*/
//STRIP001 /*?*/            if( DoesUndo() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ClearRedo();
//STRIP001 /*?*/                AppendUndo( new SwUndoInsLayFmt( pFmt ));
//STRIP001 /*?*/            }
/*?*/       }
/*?*/       break;
/*?*/
/*?*/ #ifndef PRODUCT
/*?*/   case FLY_PAGE:
/*?*/   case FLY_AUTO_CNTNT:
/*?*/   case FLY_AT_FLY:
/*?*/   case FLY_AT_CNTNT:
/*?*/   case FLY_IN_CNTNT:
/*?*/       ASSERT( !this,
/*?*/               "neue Schnittstelle benutzen: SwDoc::MakeFlySection!" );
/*?*/       break;
/*?*/ #endif
/*?*/
/*?*/   default:
/*?*/       ASSERT( !this,
/*?*/               "Layoutformat mit ungueltigem Request angefordert." );
/*?*/
/*N*/   }
/*N*/   return pFmt;
/*N*/ }
/*************************************************************************
|*
|*  SwDoc::DelLayoutFmt()
|*
|*  Beschreibung        Loescht das angegebene Format, der Inhalt wird mit
|*      geloescht.
|*  Ersterstellung      MA 23. Sep. 92
|*  Letzte Aenderung    MA 05. Feb. 93
|*
|*************************************************************************/

/*N*/ void SwDoc::DelLayoutFmt( SwFrmFmt *pFmt )
/*N*/ {
/*N*/   //Verkettung von Rahmen muss ggf. zusammengefuehrt werden.
/*N*/   //Bevor die Frames vernichtet werden, damit die Inhalte der Rahmen
/*N*/   //ggf. entsprechend gerichtet werden.
/*N*/   const SwFmtChain &rChain = pFmt->GetChain();
/*N*/   if ( rChain.GetPrev() )
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  SwFmtChain aChain( rChain.GetPrev()->GetChain() );
//STRIP001 /*?*/        aChain.SetNext( rChain.GetNext() );
//STRIP001 /*?*/        SetAttr( aChain, *rChain.GetPrev() );
/*N*/   }
/*N*/   if ( rChain.GetNext() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SwFmtChain aChain( rChain.GetNext()->GetChain() );
//STRIP001 /*?*/        aChain.SetPrev( rChain.GetPrev() );
//STRIP001 /*?*/        SetAttr( aChain, *rChain.GetNext() );
/*N*/   }

/*N*/   const SwNodeIndex* pCntIdx = pFmt->GetCntnt().GetCntntIdx();
/*N*/   if( pCntIdx && !DoesUndo() )
/*N*/   {
/*N*/       //Verbindung abbauen, falls es sich um ein OLE-Objekt handelt.
/*N*/       SwOLENode* pOLENd = GetNodes()[ pCntIdx->GetIndex()+1 ]->GetOLENode();
/*N*/       if( pOLENd && pOLENd->GetOLEObj().IsOleRef() )
/*N*/       {
/*N*/           SwDoc* pDoc = (SwDoc*)pFmt->GetDoc();
/*N*/           if( pDoc )
/*N*/           {
/*N*/               SvPersist* p = pDoc->GetPersist();
/*N*/               if( p )     // muss da sein
/*N*/               {
/*N*/                   SvInfoObjectRef aRef( p->Find( pOLENd->GetOLEObj().GetName() ) );
/*N*/                   if( aRef.Is() )
/*N*/                       aRef->SetObj(0);
/*N*/               }
/*N*/           }
/*N*/
/*N*/           pOLENd->GetOLEObj().GetOleRef()->DoClose();
/*N*/           pOLENd->GetOLEObj().GetOleRef().Clear();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //Frms vernichten.
/*N*/   pFmt->DelFrms();

    // erstmal sind nur Fly's Undofaehig
/*N*/   const sal_uInt16 nWh = pFmt->Which();
/*N*/   if( DoesUndo() && (RES_FLYFRMFMT == nWh || RES_DRAWFRMFMT == nWh) )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 // erstmal werden alle Undo - Objecte geloescht.
//STRIP001 /*?*/        ClearRedo();
//STRIP001 /*?*/        AppendUndo( new SwUndoDelLayFmt( pFmt ));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //Inhalt Loeschen.
/*N*/       if( pCntIdx )
/*N*/       {
/*N*/
/*N*/ //JP erstmal ein Hack, solange keine Headers/Footers Undofaehig sind
/*N*/ if( DoesUndo() )
/*?*/   DelAllUndoObj();
/*N*/
/*N*/           SwNode *pNode = &pCntIdx->GetNode();
/*N*/           ((SwFmtCntnt&)pFmt->GetAttr( RES_CNTNT )).SetNewCntntIdx( 0 );
/*N*/           DeleteSection( pNode );
/*N*/       }
/*N*/
/*N*/       // ggfs. bei Zeichengebundenen Flys das Zeichen loeschen
/*N*/       const SwFmtAnchor& rAnchor = pFmt->GetAnchor();
/*N*/       if( FLY_IN_CNTNT == rAnchor.GetAnchorId() && rAnchor.GetCntntAnchor())
/*N*/       {
/*N*/           const SwPosition* pPos = rAnchor.GetCntntAnchor();
/*N*/           SwTxtNode *pTxtNd = pPos->nNode.GetNode().GetTxtNode();
/*N*/           SwTxtFlyCnt* pAttr;
/*N*/
/*N*/           // Attribut steht noch im TextNode, loeschen
/*N*/           if( pTxtNd && 0 != ( pAttr = ((SwTxtFlyCnt*)pTxtNd->GetTxtAttr(
/*N*/                                           pPos->nContent.GetIndex() ))) &&
/*N*/               pAttr->GetFlyCnt().GetFrmFmt() == pFmt )
/*N*/           {
/*?*/               // Pointer auf 0, nicht loeschen
/*?*/               ((SwFmtFlyCnt&)pAttr->GetFlyCnt()).SetFlyFmt();
/*?*/               SwIndex aIdx( pPos->nContent );
/*?*/               pTxtNd->Erase( aIdx, 1 );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       DelFrmFmt( pFmt );
/*N*/   }
/*N*/   SetModified();
/*N*/ }

/*************************************************************************
|*
|*  SwDoc::CopyLayoutFmt()
|*
|*  Beschreibung        Kopiert das angegebene Format pSrc in pDest und
|*                      returnt pDest. Wenn es noch kein pDest gibt, wird
|*                      eins angelegt.
|*                      JP: steht das Source Format in einem anderen
|*                          Dokument, so kopiere auch dann noch richtig !!
|*                          Vom chaos::Anchor-Attribut wird die Position immer
|*                          auf 0 gesetzt !!!
|*
|*  Ersterstellung      BP 18.12.92
|*  Letzte Aenderung    MA 17. Jul. 96
|*
|*************************************************************************/

/*N*/ SwFrmFmt *SwDoc::CopyLayoutFmt( const SwFrmFmt& rSource,
/*N*/                               const SwFmtAnchor& rNewAnchor,
/*N*/                               sal_Bool bSetTxtFlyAtt, sal_Bool bMakeFrms )
/*N*/ {
/*N*/     const bool bFly = RES_FLYFRMFMT == rSource.Which();
/*N*/     const bool bDraw = RES_DRAWFRMFMT == rSource.Which();
/*N*/     ASSERT( bFly || bDraw, "this method only works for fly or draw" );
/*N*/
/*N*/   SwDoc* pSrcDoc = (SwDoc*)rSource.GetDoc();
/*N*/
/*N*/     // #108784# may we copy this object?
/*N*/     // We may, unless it's 1) it's a control (and therfore a draw)
/*N*/     //                     2) anchored in a header/footer
/*N*/     //                     3) anchored (to paragraph?)
/*N*/     bool bMayNotCopy = false;
/*N*/     if( bDraw )
/*N*/     {
/*N*/         const SwDrawContact* pDrawContact =
/*N*/             static_cast<const SwDrawContact*>( rSource.FindContactObj() );
/*N*/
/*N*/         bMayNotCopy =
/*N*/             ( FLY_AT_CNTNT == rNewAnchor.GetAnchorId() ||
/*N*/               FLY_AT_FLY == rNewAnchor.GetAnchorId() ||
/*N*/               FLY_AUTO_CNTNT == rNewAnchor.GetAnchorId() ) &&
/*N*/             rNewAnchor.GetCntntAnchor() &&
/*N*/             IsInHeaderFooter( rNewAnchor.GetCntntAnchor()->nNode ) &&
/*N*/             pDrawContact != NULL  &&
/*N*/             pDrawContact->GetMaster() != NULL  &&
/*N*/             CheckControlLayer( pDrawContact->GetMaster() );
/*N*/     }
/*N*/
/*N*/     // just return if we can't copy this
/*N*/     if( bMayNotCopy )
/*N*/         return NULL;
/*N*/
/*N*/   SwFrmFmt* pDest = GetDfltFrmFmt();
/*N*/   if( rSource.GetRegisteredIn() != pSrcDoc->GetDfltFrmFmt() )
/*N*/       pDest = CopyFrmFmt( *(SwFrmFmt*)rSource.GetRegisteredIn() );
/*N*/   if( bFly )
/*N*/   {
/*N*/       // #i11176#
/*N*/       // To do a correct cloning concerning the ZOrder for all objects
/*N*/       // it is necessary to actually create a draw object for fly frames, too.
/*N*/       // These are then added to the DrawingLayer (which needs to exist).
/*N*/       // Together with correct sorting of all drawinglayer based objects
/*N*/       // before cloning ZOrder transfer works correctly then.
/*N*/       SwFlyFrmFmt *pFormat = MakeFlyFrmFmt( rSource.GetName(), pDest );
/*N*/       pDest = pFormat;
/*N*/
/*N*/       SwXFrame::GetOrCreateSdrObject(pFormat);
/*N*/   }
/*N*/   else
/*N*/       pDest = MakeDrawFrmFmt( aEmptyStr, pDest );
/*N*/
/*N*/   // alle anderen/neue Attribute kopieren.
/*N*/   pDest->CopyAttrs( rSource );
/*N*/
/*N*/   //Chains werden nicht kopiert.
/*N*/   pDest->ResetAttr( RES_CHAIN );
/*N*/
/*N*/   if( bFly )
/*N*/   {
/*N*/       //Der Inhalt wird dupliziert.
/*N*/       const SwNode& rCSttNd = rSource.GetCntnt().GetCntntIdx()->GetNode();
/*N*/       SwNodeRange aRg( rCSttNd, 1, *rCSttNd.EndOfSectionNode() );
/*N*/
/*N*/       SwNodeIndex aIdx( GetNodes().GetEndOfAutotext() );
/*N*/       SwStartNode* pSttNd = GetNodes().MakeEmptySection( aIdx, SwFlyStartNode );
/*N*/
/*N*/       // erst den chaos::Anchor/CntntIndex setzen, innerhalb des Kopierens
/*N*/       // auf die Werte zugegriffen werden kann (DrawFmt in Kopf-/Fusszeilen)
/*N*/       aIdx = *pSttNd;
/*N*/       SwFmtCntnt aAttr( rSource.GetCntnt() );
/*N*/       aAttr.SetNewCntntIdx( &aIdx );
/*N*/       pDest->SetAttr( aAttr );
/*N*/       pDest->SetAttr( rNewAnchor );
/*N*/
/*N*/       if( !bCopyIsMove || this != pSrcDoc )
/*N*/       {
/*N*/           if( bInReading )
/*N*/               pDest->SetName( aEmptyStr );
/*N*/           else
/*N*/           {
/*N*/               // Teste erstmal ob der Name schon vergeben ist.
/*N*/               // Wenn ja -> neuen generieren
/*N*/               sal_Int8 nNdTyp = aRg.aStart.GetNode().GetNodeType();
/*N*/
/*N*/               String sOld( pDest->GetName() );
/*N*/               pDest->SetName( aEmptyStr );
/*N*/               if( FindFlyByName( sOld, nNdTyp ) )     // einen gefunden
/*N*/                   switch( nNdTyp )
/*N*/                   {
/*N*/                   case ND_GRFNODE:    sOld = GetUniqueGrfName();      break;
/*N*/                   case ND_OLENODE:    sOld = GetUniqueOLEName();      break;
/*N*/                   default:            sOld = GetUniqueFrameName();    break;
/*N*/                   }
/*N*/
/*N*/               pDest->SetName( sOld );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if( DoesUndo() )
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            ClearRedo();
//STRIP001 /*?*/            AppendUndo( new SwUndoInsLayFmt( pDest ));
/*N*/       }
/*N*/
/*N*/       // sorge dafuer das auch Fly's in Fly's kopiert werden
/*N*/       aIdx = *pSttNd->EndOfSectionNode();
/*N*/       pSrcDoc->CopyWithFlyInFly( aRg, aIdx, sal_False, sal_True, sal_True );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       ASSERT( RES_DRAWFRMFMT == rSource.Which(), "Weder Fly noch Draw." );
/*N*/       SwDrawContact *pContact = (SwDrawContact *)rSource.FindContactObj();
/*N*/
/*N*/       pContact = new SwDrawContact( (SwDrawFrmFmt*)pDest,
/*N*/                               CloneSdrObj( *pContact->GetMaster(),
/*N*/                                       bCopyIsMove && this == pSrcDoc ) );
/*N*/
/*N*/       if( pDest->GetAnchor() == rNewAnchor )
/*N*/         {
/*N*/             // OD 03.07.2003 #108784# - do *not* connect to layout, if
/*N*/             // a <MakeFrms> will not be called.
/*N*/             if ( bMakeFrms )
/*N*/             {
/*N*/                 pContact->ConnectToLayout( &rNewAnchor );
/*N*/             }
/*N*/         }
/*N*/       else
/*N*/           pDest->SetAttr( rNewAnchor );
/*N*/
/*N*/       if( DoesUndo() )
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            ClearRedo();
//STRIP001 /*?*/            AppendUndo( new SwUndoInsLayFmt( pDest ));
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( bSetTxtFlyAtt && FLY_IN_CNTNT == rNewAnchor.GetAnchorId() )
/*N*/   {
/*N*/       SwPosition* pPos = (SwPosition*)rNewAnchor.GetCntntAnchor();
/*N*/       pPos->nNode.GetNode().GetTxtNode()->Insert(SwFmtFlyCnt( pDest ),
/*N*/                                           pPos->nContent.GetIndex(), 0 );
/*N*/   }
/*N*/
/*N*/   if( bMakeFrms )
/*N*/       pDest->MakeFrms();
/*N*/
/*N*/   return pDest;
/*N*/ }

/*N*/ SdrObject* SwDoc::CloneSdrObj( const SdrObject& rObj, sal_Bool bMoveWithinDoc,
/*N*/                               sal_Bool bInsInPage )
/*N*/ {
/*N*/   SdrPage *pPg = MakeDrawModel()->GetPage( 0 );
/*N*/   if( !pPg )
/*N*/   {
/*?*/       pPg = GetDrawModel()->AllocPage( sal_False );
/*?*/       GetDrawModel()->InsertPage( pPg );
/*N*/   }
/*N*/
/*N*/   SdrObject *pObj = rObj.Clone();
/*N*/   if( bMoveWithinDoc && FmFormInventor == pObj->GetObjInventor() )
/*N*/   {
/*?*/       // bei Controls muss der Name erhalten bleiben
/*?*/       uno::Reference< awt::XControlModel >  xModel = ((SdrUnoObj*)pObj)->GetUnoControlModel();
/*?*/       sal_Bool bModel = xModel.is();
/*?*/       uno::Any aVal;
/*?*/       uno::Reference< beans::XPropertySet >  xSet(xModel, uno::UNO_QUERY);
/*?*/       OUString sName( rtl::OUString::createFromAscii("Name") );
/*?*/       if( xSet.is() )
/*?*/           aVal = xSet->getPropertyValue( sName );
/*?*/       if( bInsInPage )
/*?*/           pPg->InsertObject( pObj );
/*?*/       if( xSet.is() )
/*?*/           xSet->setPropertyValue( sName, aVal );
/*N*/   }
/*N*/   else if( bInsInPage )
/*N*/       pPg->InsertObject( pObj );
/*N*/
/*N*/     // OD 02.07.2003 #108784# - for drawing objects: set layer of cloned object
/*N*/     // to invisible layer
/*N*/     SdrLayerID nLayerIdForClone = rObj.GetLayer();
/*N*/     if ( !pObj->ISA(SwFlyDrawObj) &&
/*N*/          !pObj->ISA(SwVirtFlyDrawObj) &&
/*N*/          !IS_TYPE(SdrObject,pObj) )
/*N*/     {
/*N*/         if ( IsVisibleLayerId( nLayerIdForClone ) )
/*N*/         {
/*N*/             nLayerIdForClone = GetInvisibleLayerIdByVisibleOne( nLayerIdForClone );
/*N*/         }
/*N*/     }
/*N*/     pObj->SetLayer( nLayerIdForClone );
/*N*/
/*N*/
/*N*/   return pObj;
/*N*/ }

/*N*/ SwFlyFrmFmt* SwDoc::_MakeFlySection( const SwPosition& rAnchPos,
/*N*/                                   const SwCntntNode& rNode,
/*N*/                                   RndStdIds eRequestId,
/*N*/                                   const SfxItemSet* pFlySet,
/*N*/                                   SwFrmFmt* pFrmFmt )
/*N*/ {
/*N*/   if( !pFrmFmt )
/*?*/       pFrmFmt = GetFrmFmtFromPool( RES_POOLFRM_FRAME );
/*N*/
/*N*/   String sName;
/*N*/   if( !bInReading )
/*N*/       switch( rNode.GetNodeType() )
/*N*/       {
/*N*/       case ND_GRFNODE:        sName = GetUniqueGrfName();     break;
/*N*/       case ND_OLENODE:        sName = GetUniqueOLEName();     break;
/*N*/       default:                sName = GetUniqueFrameName();       break;
/*N*/       }
/*N*/   SwFlyFrmFmt* pFmt = MakeFlyFrmFmt( sName, pFrmFmt );
/*N*/
/*N*/   //Inhalt erzeugen und mit dem Format verbinden.
/*N*/   //CntntNode erzeugen und in die Autotextsection stellen
/*N*/   SwNodeRange aRange( GetNodes().GetEndOfAutotext(), -1,
/*N*/                       GetNodes().GetEndOfAutotext() );
/*N*/   GetNodes().SectionDown( &aRange, SwFlyStartNode );
/*N*/
/*N*/   pFmt->SetAttr( SwFmtCntnt( rNode.StartOfSectionNode() ));
/*N*/
/*N*/
/*N*/   const SwFmtAnchor* pAnchor = 0;
/*N*/   if( pFlySet )
/*N*/   {
/*N*/       pFlySet->GetItemState( RES_ANCHOR, sal_False,
/*N*/                               (const SfxPoolItem**)&pAnchor );
/*N*/       if( SFX_ITEM_SET == pFlySet->GetItemState( RES_CNTNT, sal_False ))
/*N*/       {
/*?*/           SfxItemSet aTmpSet( *pFlySet );
/*?*/           aTmpSet.ClearItem( RES_CNTNT );
/*?*/           pFmt->SetAttr( aTmpSet );
/*N*/       }
/*N*/       else
/*N*/           pFmt->SetAttr( *pFlySet );
/*N*/   }

    // Anker noch nicht gesetzt ?
/*N*/   RndStdIds eAnchorId = pAnchor ? pAnchor->GetAnchorId()
/*N*/                                 : pFmt->GetAnchor().GetAnchorId();
/*N*/   if( !pAnchor ||
/*N*/       (FLY_PAGE != pAnchor->GetAnchorId() &&
/*N*/         //Nur Page und nicht:
/*N*/ //          FLY_AT_CNTNT == pAnchor->GetAnchorId() ||
/*N*/ //          FLY_IN_CNTNT == pAnchor->GetAnchorId() ||
/*N*/ //          FLY_AT_FLY == pAnchor->GetAnchorId() ||
/*N*/ //          FLY_AUTO_CNTNT == pAnchor->GetAnchorId() ) &&
/*N*/       !pAnchor->GetCntntAnchor() ))
/*N*/   {
/*N*/       // dann setze ihn, wird im Undo gebraucht
/*N*/       SwFmtAnchor aAnch( pFmt->GetAnchor() );
/*N*/       if( pAnchor && FLY_AT_FLY == pAnchor->GetAnchorId() )
/*N*/       {
/*?*/           SwPosition aPos( *rAnchPos.nNode.GetNode().FindFlyStartNode() );
/*?*/           aAnch.SetAnchor( &aPos );
/*?*/           eAnchorId = FLY_AT_FLY;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if( eRequestId != aAnch.GetAnchorId() &&
/*N*/               SFX_ITEM_SET != pFmt->GetItemState( RES_ANCHOR, sal_True ) )
/*?*/               aAnch.SetType( eRequestId );
/*N*/
/*N*/           eAnchorId = aAnch.GetAnchorId();
/*N*/           if ( FLY_PAGE != eAnchorId )
/*N*/           //Nur Page und nicht:
/*N*/ //            if( FLY_AT_CNTNT == eAnchorId || FLY_IN_CNTNT == eAnchorId ||
/*N*/ //                FLY_AT_FLY == eAnchorId || FLY_AUTO_CNTNT == eAnchorId )
/*N*/               aAnch.SetAnchor( &rAnchPos );
/*N*/       }
/*N*/       pFmt->SetAttr( aAnch );
/*N*/   }
/*N*/   else
/*N*/       eAnchorId = pFmt->GetAnchor().GetAnchorId();
/*N*/
/*N*/   if( FLY_IN_CNTNT == eAnchorId )
/*N*/   {
/*N*/       xub_StrLen nStt = rAnchPos.nContent.GetIndex();
/*N*/       rAnchPos.nNode.GetNode().GetTxtNode()->Insert(
/*N*/                                       SwFmtFlyCnt( pFmt ), nStt, nStt );
/*N*/   }
/*N*/
/*N*/   if( SFX_ITEM_SET != pFmt->GetAttrSet().GetItemState( RES_FRM_SIZE ))
/*N*/   {
/*?*/       SwFmtFrmSize aFmtSize( ATT_VAR_SIZE, 0, DEF_FLY_WIDTH );
/*?*/       const SwNoTxtNode* pNoTxtNode = rNode.GetNoTxtNode();
/*?*/       if( pNoTxtNode )
/*?*/       {
/*?*/           //Groesse einstellen.
/*?*/           Size aSize( pNoTxtNode->GetTwipSize() );
/*?*/           if( MINFLY > aSize.Width() )
/*?*/               aSize.Width() = DEF_FLY_WIDTH;
/*?*/           aFmtSize.SetWidth( aSize.Width() );
/*?*/           if( aSize.Height() )
/*?*/           {
/*?*/               aFmtSize.SetHeight( aSize.Height() );
/*?*/               aFmtSize.SetSizeType( ATT_FIX_SIZE );
/*?*/           }
/*?*/       }
/*?*/       pFmt->SetAttr( aFmtSize );
/*N*/   }

    // Frames anlegen
/*N*/   if( GetRootFrm() )
/*N*/       pFmt->MakeFrms();           // ???
/*N*/
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       AppendUndo( new SwUndoInsLayFmt( pFmt ));
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*N*/ SwFlyFrmFmt* SwDoc::MakeFlySection( RndStdIds eAnchorType,
/*N*/                                   const SwPosition* pAnchorPos,
/*N*/                                   const SfxItemSet* pFlySet,
/*N*/                                   SwFrmFmt* pFrmFmt, BOOL bCalledFromShell )
/*N*/ {
/*N*/   SwFlyFrmFmt* pFmt = 0;
/*N*/   sal_Bool bCallMake = sal_True;
/*N*/   if( !pAnchorPos && FLY_PAGE != eAnchorType )
/*N*/   {
/*N*/       const SwFmtAnchor* pAnch;
/*N*/       if( (pFlySet && SFX_ITEM_SET == pFlySet->GetItemState(
/*N*/               RES_ANCHOR, sal_False, (const SfxPoolItem**)&pAnch )) ||
/*N*/           ( pFrmFmt && SFX_ITEM_SET == pFrmFmt->GetItemState(
/*N*/               RES_ANCHOR, sal_True, (const SfxPoolItem**)&pAnch )) )
/*N*/       {
/*?*/           if( FLY_PAGE != pAnch->GetAnchorId() &&
/*?*/               0 == ( pAnchorPos = pAnch->GetCntntAnchor() ) )
/*?*/               bCallMake = sal_False;
/*N*/       }
/*N*/   }

/*N*/   if( bCallMake )
/*N*/   {
/*N*/       if( !pFrmFmt )
/*?*/           pFrmFmt = GetFrmFmtFromPool( RES_POOLFRM_FRAME );
/*N*/
/*N*/       sal_uInt16 nCollId = IsHTMLMode() ? RES_POOLCOLL_TEXT : RES_POOLCOLL_FRAME;
/*N*/
        /* #109161# If there exists no adjust item in the paragraph
            style for the content node of the new fly section
            propagate an existing adjust item at the anchor to the new
            content node. */
/*N*/         SwCntntNode * pNewTxtNd = GetNodes().MakeTxtNode
/*N*/             (SwNodeIndex( GetNodes().GetEndOfAutotext()),
/*N*/              GetTxtCollFromPool( nCollId ));
/*N*/         SwCntntNode * pAnchorNode = pAnchorPos->nNode.GetNode().GetCntntNode();
/*N*/
/*N*/         const SfxPoolItem * pItem = NULL;
/*N*/
/*N*/         if (bCalledFromShell && !lcl_IsItemSet(*pNewTxtNd, RES_PARATR_ADJUST) &&
/*N*/             SFX_ITEM_SET == pAnchorNode->GetSwAttrSet().
/*N*/             GetItemState(RES_PARATR_ADJUST, TRUE, &pItem))
/*N*/             static_cast<SwCntntNode *>(pNewTxtNd)->SetAttr(*pItem);
/*N*/
/*N*/       pFmt = _MakeFlySection( *pAnchorPos, *pNewTxtNd,
/*N*/                               eAnchorType, pFlySet, pFrmFmt );
/*N*/   }
/*N*/   return pFmt;
/*N*/ }

//STRIP001 SwFlyFrmFmt* SwDoc::MakeFlyAndMove( const SwPaM& rPam, const SfxItemSet& rSet,
//STRIP001                                  const SwSelBoxes* pSelBoxes,
//STRIP001                                  SwFrmFmt *pParent )
//STRIP001 {
//STRIP001  SwFmtAnchor& rAnch = (SwFmtAnchor&)rSet.Get( RES_ANCHOR );
//STRIP001
//STRIP001  StartUndo( UNDO_INSLAYFMT );
//STRIP001
//STRIP001  SwFlyFrmFmt* pFmt = MakeFlySection( rAnch.GetAnchorId(), rPam.GetPoint(),
//STRIP001                                      &rSet, pParent );
//STRIP001
//STRIP001  // Wenn Inhalt selektiert ist, so wird dieser jetzt zum Inhalt des
//STRIP001  // neuen Rahmen. Sprich er wird in die entspr. Sektion des NodesArr
//STRIP001  //gemoved.
//STRIP001
//STRIP001  if( pFmt )
//STRIP001  {
//STRIP001      do {        // middle check loop
//STRIP001          const SwFmtCntnt &rCntnt = pFmt->GetCntnt();
//STRIP001          ASSERT( rCntnt.GetCntntIdx(), "Kein Inhalt vorbereitet." );
//STRIP001          SwNodeIndex aIndex( *(rCntnt.GetCntntIdx()), 1 );
//STRIP001          SwCntntNode *pNode = aIndex.GetNode().GetCntntNode();
//STRIP001
//STRIP001          // ACHTUNG: nicht einen Index auf dem Stack erzeugen, sonst
//STRIP001          //          kann der CntntnNode am Ende nicht geloscht werden !!
//STRIP001          SwPosition aPos( aIndex );
//STRIP001          aPos.nContent.Assign( pNode, 0 );
//STRIP001
//STRIP001          if( pSelBoxes && pSelBoxes->Count() )
//STRIP001          {
//STRIP001              // Tabellenselection
//STRIP001              // kopiere Teile aus einer Tabelle: lege eine Tabelle mit der
//STRIP001              // Breite der Originalen an und move (kopiere/loesche) die
//STRIP001              // selektierten Boxen. Die Groessen werden prozentual
//STRIP001              // korrigiert.
//STRIP001
//STRIP001              SwTableNode* pTblNd = (SwTableNode*)(*pSelBoxes)[0]->
//STRIP001                                              GetSttNd()->FindTableNode();
//STRIP001              if( !pTblNd )
//STRIP001                  break;
//STRIP001
//STRIP001              SwTable& rTbl = pTblNd->GetTable();
//STRIP001
//STRIP001              // ist die gesamte Tabelle selektiert ?
//STRIP001              if( pSelBoxes->Count() == rTbl.GetTabSortBoxes().Count() )
//STRIP001              {
//STRIP001                  // verschiebe die gesamte Tabelle
//STRIP001                  SwNodeRange aRg( *pTblNd, 0, *pTblNd->EndOfSectionNode(), 1 );
//STRIP001
//STRIP001                  // wird die gesamte Tabelle verschoben und steht diese
//STRIP001                  // in einem FlyFrame, dann erzeuge dahinter einen neuen
//STRIP001                  // TextNode. Dadurch bleibt dieser Fly erhalten !
//STRIP001                  if( aRg.aEnd.GetNode().IsEndNode() )
//STRIP001                      GetNodes().MakeTxtNode( aRg.aStart,
//STRIP001                                  (SwTxtFmtColl*)GetDfltTxtFmtColl() );
//STRIP001
//STRIP001                  Move( aRg, aPos.nNode );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rTbl.MakeCopy( this, aPos, *pSelBoxes );
//STRIP001                  rTbl.DeleteSel( this, *pSelBoxes );
//STRIP001              }
//STRIP001
//STRIP001              // wenn Tabelle im Rahmen, dann ohne nachfolgenden TextNode
//STRIP001              aIndex = rCntnt.GetCntntIdx()->GetNode().EndOfSectionIndex() - 1;
//STRIP001              ASSERT( aIndex.GetNode().GetTxtNode(),
//STRIP001                      "hier sollte ein TextNode stehen" );
//STRIP001              aPos.nContent.Assign( 0, 0 );       // Index abmelden !!
//STRIP001              GetNodes().Delete( aIndex, 1 );
//STRIP001
//STRIP001 //JP erstmal ein Hack, solange keine Flys/Headers/Footers Undofaehig sind
//STRIP001 if( DoesUndo() ) // werden erstmal alle Undo - Objecte geloescht.
//STRIP001  DelAllUndoObj();
//STRIP001
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001 /*
//STRIP001              // alle Pams verschieben
//STRIP001              SwPaM* pTmp = (SwPaM*)&rPam;
//STRIP001              do {
//STRIP001                  if( pTmp->HasMark() &&
//STRIP001                      *pTmp->GetPoint() != *pTmp->GetMark() )
//STRIP001                      MoveAndJoin( *pTmp, aPos );
//STRIP001              } while( &rPam != ( pTmp = (SwPaM*)pTmp->GetNext() ) );
//STRIP001 */
//STRIP001              // copy all Pams and then delete all
//STRIP001              SwPaM* pTmp = (SwPaM*)&rPam;
//STRIP001              BOOL bOldFlag = bCopyIsMove, bOldUndo = bUndo;
//STRIP001              bCopyIsMove = TRUE;
//STRIP001              bUndo = FALSE;
//STRIP001              do {
//STRIP001                  if( pTmp->HasMark() &&
//STRIP001                      *pTmp->GetPoint() != *pTmp->GetMark() )
//STRIP001                      Copy( *pTmp, aPos );
//STRIP001              } while( &rPam != ( pTmp = (SwPaM*)pTmp->GetNext() ) );
//STRIP001              bCopyIsMove = bOldFlag;
//STRIP001              bUndo = bOldUndo;
//STRIP001
//STRIP001              pTmp = (SwPaM*)&rPam;
//STRIP001              do {
//STRIP001                  if( pTmp->HasMark() &&
//STRIP001                      *pTmp->GetPoint() != *pTmp->GetMark() )
//STRIP001                      DeleteAndJoin( *pTmp );
//STRIP001              } while( &rPam != ( pTmp = (SwPaM*)pTmp->GetNext() ) );
//STRIP001          }
//STRIP001      } while( sal_False );
//STRIP001  }
//STRIP001
//STRIP001  SetModified();
//STRIP001
//STRIP001  EndUndo( UNDO_INSLAYFMT );
//STRIP001
//STRIP001  return pFmt;
//STRIP001 }


    //Einfuegen eines DrawObjectes. Das Object muss bereits im DrawModel
    // angemeldet sein.
/*N*/ SwDrawFrmFmt* SwDoc::Insert( const SwPaM &rRg,
/*N*/                            SdrObject& rDrawObj,
/*N*/                            const SfxItemSet* pFlyAttrSet,
/*N*/                            SwFrmFmt* pDefFmt )
/*N*/ {
/*N*/   SwDrawFrmFmt *pFmt = MakeDrawFrmFmt( aEmptyStr,
/*N*/                                       pDefFmt ? pDefFmt : GetDfltFrmFmt() );
/*N*/
/*N*/   const SwFmtAnchor* pAnchor = 0;
/*N*/   if( pFlyAttrSet )
/*N*/   {
/*N*/       pFlyAttrSet->GetItemState( RES_ANCHOR, sal_False,
/*N*/                                   (const SfxPoolItem**)&pAnchor );
/*N*/       pFmt->SetAttr( *pFlyAttrSet );
/*N*/   }
/*N*/
/*N*/   RndStdIds eAnchorId = pAnchor ? pAnchor->GetAnchorId()
/*N*/                                 : pFmt->GetAnchor().GetAnchorId();
/*N*/
/*N*/   // Anker noch nicht gesetzt ?
/*N*/   // DrawObjecte duerfen niemals in Kopf-/Fusszeilen landen.
/*N*/   sal_Bool bIsAtCntnt = FLY_PAGE != eAnchorId;
/*N*/ //                      FLY_AT_CNTNT == eAnchorId || FLY_IN_CNTNT == eAnchorId ||
/*N*/ //                      FLY_AT_FLY == eAnchorId || FLY_AUTO_CNTNT == eAnchorId;
/*N*/
/*N*/   const SwNodeIndex* pChkIdx = 0;
/*N*/   if( !pAnchor )
/*N*/     {
/*N*/       pChkIdx = &rRg.GetPoint()->nNode;
/*N*/     }
/*N*/   else if( bIsAtCntnt )
/*N*/     {
/*N*/       pChkIdx = pAnchor->GetCntntAnchor()
/*N*/                   ? &pAnchor->GetCntntAnchor()->nNode
/*N*/                   : &rRg.GetPoint()->nNode;
/*N*/     }
/*N*/
/*N*/     // OD 24.06.2003 #108784# - allow drawing objects in header/footer, but
/*N*/     // control objects aren't allowed in header/footer.
/*N*/     if( pChkIdx &&
/*N*/         ::CheckControlLayer( &rDrawObj ) &&
/*N*/         IsInHeaderFooter( *pChkIdx ) )
/*N*/     {
/*N*/        pFmt->SetAttr( SwFmtAnchor( eAnchorId = FLY_PAGE ) );
/*N*/     }
/*N*/   else if( !pAnchor || (bIsAtCntnt && !pAnchor->GetCntntAnchor() ))
/*N*/   {
/*N*/       // dann setze ihn, wird im Undo gebraucht
/*N*/       SwFmtAnchor aAnch( pAnchor ? *pAnchor : pFmt->GetAnchor() );
/*N*/       eAnchorId = aAnch.GetAnchorId();
/*N*/       if( FLY_AT_FLY == eAnchorId )
/*N*/       {
/*?*/           SwPosition aPos( *rRg.GetNode()->FindFlyStartNode() );
/*?*/           aAnch.SetAnchor( &aPos );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aAnch.SetAnchor( rRg.GetPoint() );
/*N*/           if( FLY_PAGE == eAnchorId )
/*N*/           {
/*?*/               eAnchorId = rDrawObj.ISA( SdrUnoObj )
/*?*/                                   ? FLY_IN_CNTNT : FLY_AT_CNTNT;
/*?*/               aAnch.SetType( eAnchorId );
/*?*/           }
/*N*/       }
/*N*/       pFmt->SetAttr( aAnch );
/*N*/   }
/*N*/
/*N*/   // bei als Zeichen gebundenen Draws das Attribut im Absatz setzen
/*N*/   if( FLY_IN_CNTNT == eAnchorId )
/*N*/   {
/*N*/       xub_StrLen nStt = rRg.GetPoint()->nContent.GetIndex();
/*N*/       rRg.GetPoint()->nNode.GetNode().GetTxtNode()->Insert(
/*N*/                                       SwFmtFlyCnt( pFmt ), nStt, nStt );
/*N*/   }
/*N*/
/*N*/   new SwDrawContact( pFmt, &rDrawObj );
/*N*/
/*N*/   // ggfs. Frames anlegen
/*N*/   if( GetRootFrm() )
/*N*/       pFmt->MakeFrms();
/*N*/
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       AppendUndo( new SwUndoInsLayFmt( pFmt ));
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return pFmt;
/*N*/ }

/*************************************************************************
|*
|*  SwDoc::GetAllFlyFmts
|*
|*  Ersterstellung      MA 14. Jul. 93
|*  Letzte Aenderung    MD 23. Feb. 95
|*
|*************************************************************************/

/*sal_Bool TstFlyRange( const SwPaM* pPam, sal_uInt32 nFlyPos )
{
    sal_Bool bOk = sal_False;
    const SwPaM* pTmp = pPam;
    do {
        bOk = pTmp->Start()->nNode.GetIndex() < nFlyPos &&
                pTmp->End()->nNode.GetIndex() > nFlyPos;
    } while( !bOk && pPam != ( pTmp = (const SwPaM*)pTmp->GetNext() ));
    return bOk;
}
*/
/* -----------------------------04.04.00 10:55--------------------------------
    paragraph frames - o.k. if the PaM includes the paragraph from the beginning
                       to the beginning of the next paragraph at least
    frames at character - o.k. if the pam start at least at the same position
                         as the frame
 ---------------------------------------------------------------------------*/
//STRIP001 sal_Bool TstFlyRange( const SwPaM* pPam, const SwPosition* pFlyPos,
//STRIP001                      RndStdIds nAnchorId )
//STRIP001 {
//STRIP001  sal_Bool bOk = FALSE;
//STRIP001  const SwPaM* pTmp = pPam;
//STRIP001  do {
//STRIP001      const sal_uInt32 nFlyIndex = pFlyPos->nNode.GetIndex();
//STRIP001      const SwPosition* pPaMStart = pTmp->Start();
//STRIP001      const SwPosition* pPaMEnd = pTmp->End();
//STRIP001      const sal_uInt32 nPamStartIndex = pPaMStart->nNode.GetIndex();
//STRIP001      const sal_uInt32 nPamEndIndex = pPaMEnd->nNode.GetIndex();
//STRIP001      if(FLY_AT_CNTNT == nAnchorId)
//STRIP001          bOk = (nPamStartIndex < nFlyIndex && nPamEndIndex > nFlyIndex) ||
//STRIP001             (((nPamStartIndex == nFlyIndex) && (pPaMStart->nContent.GetIndex() == 0)) &&
//STRIP001             (nPamEndIndex > nFlyIndex));
//STRIP001      else
//STRIP001      {
//STRIP001          xub_StrLen nFlyContentIndex = pFlyPos->nContent.GetIndex();
//STRIP001          xub_StrLen nPamEndContentIndex = pPaMEnd->nContent.GetIndex();
//STRIP001          bOk = (nPamStartIndex < nFlyIndex &&
//STRIP001              (( nPamEndIndex > nFlyIndex )||
//STRIP001               ((nPamEndIndex == nFlyIndex) &&
//STRIP001                   (nPamEndContentIndex > nFlyContentIndex))) )
//STRIP001              ||
//STRIP001                  (((nPamStartIndex == nFlyIndex) &&
//STRIP001                    (pPaMStart->nContent.GetIndex() <= nFlyContentIndex)) &&
//STRIP001                      ((nPamEndIndex > nFlyIndex) ||
//STRIP001                      (nPamEndContentIndex > nFlyContentIndex )));
//STRIP001      }
//STRIP001
//STRIP001  } while( !bOk && pPam != ( pTmp = (const SwPaM*)pTmp->GetNext() ));
//STRIP001  return bOk;
//STRIP001 }


/*N*/ void SwDoc::GetAllFlyFmts( SwPosFlyFrms& rPosFlyFmts,
/*N*/                          const SwPaM* pCmpRange, sal_Bool bDrawAlso ) const
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  SwPosFlyFrm *pFPos = 0;
//STRIP001  const SwPosition* pAPos;
//STRIP001  SwFrmFmt *pFly;
//STRIP001
//STRIP001  // erstmal alle Absatzgebundenen einsammeln
//STRIP001  for( sal_uInt16 n = 0; n < GetSpzFrmFmts()->Count(); ++n )
//STRIP001  {
//STRIP001      pFly = (*GetSpzFrmFmts())[ n ];
//STRIP001      sal_Bool bDrawFmt = bDrawAlso ? RES_DRAWFRMFMT == pFly->Which() : sal_False;
//STRIP001      sal_Bool bFlyFmt = RES_FLYFRMFMT == pFly->Which();
//STRIP001      if( bFlyFmt || bDrawFmt )
//STRIP001      {
//STRIP001          const SwFmtAnchor& rAnchor = pFly->GetAnchor();
//STRIP001          if( ( FLY_AT_CNTNT == rAnchor.GetAnchorId() ||
//STRIP001              FLY_AT_FLY == rAnchor.GetAnchorId() ||
//STRIP001              FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ) &&
//STRIP001              0 != ( pAPos = rAnchor.GetCntntAnchor()) )
//STRIP001          {
//STRIP001              if( pCmpRange &&
//STRIP001                  !TstFlyRange( pCmpRange, pAPos, rAnchor.GetAnchorId() ))
//STRIP001                      continue;       // kein gueltiger FlyFrame
//STRIP001              pFPos = new SwPosFlyFrm( pAPos->nNode, pFly, rPosFlyFmts.Count() );
//STRIP001              rPosFlyFmts.Insert( pFPos );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // kein Layout oder nur ein Teil, dann wars das
//STRIP001  // Seitenbezogen Flys nur, wenn vollstaendig "gewuenscht" wird !
//STRIP001  if( !GetRootFrm() || pCmpRange )
//STRIP001      return;
//STRIP001
//STRIP001  pFPos = 0;
//STRIP001  SwPageFrm *pPage = (SwPageFrm*)GetRootFrm()->GetLower();
//STRIP001  while( pPage )
//STRIP001  {
//STRIP001      if( pPage->GetSortedObjs() )
//STRIP001      {
//STRIP001          SwSortDrawObjs &rObjs = *pPage->GetSortedObjs();
//STRIP001          for( sal_uInt16 i = 0; i < rObjs.Count(); ++i)
//STRIP001          {
//STRIP001              SdrObject *pO = rObjs[i];
//STRIP001              SwVirtFlyDrawObj *pObj = pO->IsWriterFlyFrame() ?
//STRIP001                                                  (SwVirtFlyDrawObj*)pO : 0;
//STRIP001              if( pObj )
//STRIP001                  pFly = pObj->GetFlyFrm()->GetFmt();
//STRIP001              else if ( bDrawAlso )
//STRIP001                  pFly = ::FindFrmFmt( rObjs[i] );
//STRIP001              else
//STRIP001                  continue;
//STRIP001
//STRIP001              const SwFmtAnchor& rAnchor = pFly->GetAnchor();
//STRIP001              if( FLY_AT_CNTNT != rAnchor.GetAnchorId() &&
//STRIP001                  FLY_AT_FLY != rAnchor.GetAnchorId() &&
//STRIP001                  FLY_AUTO_CNTNT != rAnchor.GetAnchorId() )
//STRIP001              {
//STRIP001                  const SwCntntFrm * pCntntFrm = pPage->FindFirstBodyCntnt();
//STRIP001                  if ( !pCntntFrm )
//STRIP001                  {
//STRIP001                      //Oops! Eine leere Seite. Damit der Rahmen nicht ganz
//STRIP001                      //verlorengeht (RTF) suchen wir schnell den letzen
//STRIP001                      //Cntnt der vor der Seite steht.
//STRIP001                      SwPageFrm *pPrv = (SwPageFrm*)pPage->GetPrev();
//STRIP001                      while ( !pCntntFrm && pPrv )
//STRIP001                      {
//STRIP001                          pCntntFrm = pPrv->FindFirstBodyCntnt();
//STRIP001                          pPrv = (SwPageFrm*)pPrv->GetPrev();
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( pCntntFrm )
//STRIP001                  {
//STRIP001                      SwNodeIndex aIdx( *pCntntFrm->GetNode() );
//STRIP001                      pFPos = new SwPosFlyFrm( aIdx, pFly, rPosFlyFmts.Count() );
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( pFPos )
//STRIP001              {
//STRIP001                  rPosFlyFmts.Insert( pFPos );
//STRIP001                  pFPos = 0;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  }
/*N*/ }

/*************************************************************************
|*
|*  SwDoc::InsertLabel()
|*
|*  Ersterstellung      MA 11. Feb. 94
|*  Letzte Aenderung    MA 12. Nov. 97
|*
|*************************************************************************/

/* #i6447# changed behaviour if lcl_CpyAttr:

   If the old item set contains the item to set (no inheritance) copy the item
   into the new set.

   If the old item set contains the item by inheritance and the new set
   contains the item, too:
      If the two items differ copy the item from the old set to the new set.

   Otherwise the new set will not be changed.
*/

//STRIP001 void lcl_CpyAttr( SfxItemSet &rNewSet, const SfxItemSet &rOldSet, sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  const SfxPoolItem *pOldItem = NULL, *pNewItem = NULL;
//STRIP001
//STRIP001     rOldSet.GetItemState( nWhich, sal_False, &pOldItem);
//STRIP001  if (pOldItem != NULL)
//STRIP001      rNewSet.Put( *pOldItem );
//STRIP001     else
//STRIP001     {
//STRIP001         pOldItem = rOldSet.GetItem( nWhich, sal_True);
//STRIP001         if (pOldItem != NULL)
//STRIP001         {
//STRIP001             pNewItem = rNewSet.GetItem( nWhich, sal_True);
//STRIP001             if (pNewItem != NULL)
//STRIP001             {
//STRIP001                 if (*pOldItem != *pNewItem)
//STRIP001                     rNewSet.Put( *pOldItem );
//STRIP001             }
//STRIP001             else
//STRIP001                 ASSERT(0, "What am I doing here?");
//STRIP001         }
//STRIP001         else
//STRIP001             ASSERT(0, "What am I doing here?");
//STRIP001     }
//STRIP001
//STRIP001 }


//STRIP001 SwFlyFrmFmt* SwDoc::InsertLabel( const SwLabelType eType, const String &rTxt,
//STRIP001          const sal_Bool bBefore, const sal_uInt16 nId, const sal_uInt32 nNdIdx,
//STRIP001          const sal_Bool bCpyBrd )
//STRIP001 {
//STRIP001  sal_Bool bWasUndo = DoesUndo();
//STRIP001  SwUndoInsertLabel* pUndo = 0;
//STRIP001  if( bWasUndo )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndo = new SwUndoInsertLabel( eType, rTxt, bBefore, nId, bCpyBrd );
//STRIP001      DoUndo( sal_False );
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool bTable = sal_False;    //Um etwas Code zu sparen.
//STRIP001
//STRIP001  //Erstmal das Feld bauen, weil ueber den Namen die TxtColl besorgt werden
//STRIP001  //muss
//STRIP001  ASSERT( nId < GetFldTypes()->Count(), "FldType ueberindiziert." );
//STRIP001  SwFieldType *pType = (*GetFldTypes())[nId];
//STRIP001  ASSERT( pType->Which() == RES_SETEXPFLD, "Falsche Id fuer Label" );
//STRIP001  SwSetExpField aFld( (SwSetExpFieldType*)pType, aEmptyStr, SVX_NUM_ARABIC);
//STRIP001
//STRIP001  SwTxtFmtColl *pColl = 0;
//STRIP001  for( sal_uInt16 i = pTxtFmtCollTbl->Count(); i; )
//STRIP001  {
//STRIP001      if( (*pTxtFmtCollTbl)[ --i ]->GetName() == pType->GetName() )
//STRIP001      {
//STRIP001          pColl = (*pTxtFmtCollTbl)[i];
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  if( !pColl )
//STRIP001  {
//STRIP001      ASSERT( !this, "TxtCollection fuer Label nicht gefunden." );
//STRIP001      pColl = GetTxtCollFromPool( RES_POOLCOLL_TEXT );
//STRIP001  }
//STRIP001
//STRIP001  SwTxtNode *pNew = 0;
//STRIP001  SwFlyFrmFmt* pNewFmt = 0;
//STRIP001
//STRIP001  switch ( eType )
//STRIP001  {
//STRIP001      case LTYPE_TABLE:
//STRIP001          bTable = sal_True;
//STRIP001          /* Kein Break hier */
//STRIP001      case LTYPE_FLY:
//STRIP001          //Am Anfang/Ende der Fly-Section den entsprechenden Node mit Feld
//STRIP001          //einfuegen (Frame wird automatisch erzeugt).
//STRIP001          {
//STRIP001              SwStartNode *pSttNd = GetNodes()[nNdIdx]->GetStartNode();
//STRIP001              ASSERT( pSttNd, "Kein StartNode in InsertLabel." );
//STRIP001              sal_uInt32 nNode;
//STRIP001              if( bBefore )
//STRIP001              {
//STRIP001                  nNode = pSttNd->GetIndex();
//STRIP001                  if( !bTable )
//STRIP001                      ++nNode;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  nNode = pSttNd->EndOfSectionIndex();
//STRIP001                  if( bTable )
//STRIP001                      ++nNode;
//STRIP001              }
//STRIP001
//STRIP001              if( pUndo )
//STRIP001                  pUndo->SetNodePos( nNode );
//STRIP001
//STRIP001              //Node fuer Beschriftungsabsatz erzeugen.
//STRIP001              SwNodeIndex aIdx( GetNodes(), nNode );
//STRIP001              pNew = GetNodes().MakeTxtNode( aIdx, pColl );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case LTYPE_OBJECT:
//STRIP001          {
//STRIP001              //Rahmen zerstoeren, neuen Rahmen einfuegen, entsprechenden
//STRIP001              // Node mit Feld in den neuen Rahmen, den alten Rahmen mit
//STRIP001              // dem Object (Grafik/Ole) absatzgebunden in den neuen Rahmen,
//STRIP001              // Frames erzeugen.
//STRIP001
//STRIP001              //Erstmal das Format zum Fly besorgen und das Layout entkoppeln.
//STRIP001              SwFrmFmt *pOldFmt = GetNodes()[nNdIdx]->GetFlyFmt();
//STRIP001              ASSERT( pOldFmt, "Format des Fly nicht gefunden." );
//STRIP001              pOldFmt->DelFrms();
//STRIP001
//STRIP001              pNewFmt = MakeFlyFrmFmt( GetUniqueFrameName(),
//STRIP001                                  GetFrmFmtFromPool( RES_POOLFRM_FRAME ));
//STRIP001
//STRIP001                 /* #i6447#: Only the selected items are copied from the old
//STRIP001                    format. */
//STRIP001              SfxItemSet* pNewSet = pNewFmt->GetAttrSet().Clone( sal_True );
//STRIP001
//STRIP001
//STRIP001              //Diejenigen Attribute uebertragen die auch gesetzt sind,
//STRIP001              //andere sollen weiterhin aus den Vorlagen gueltig werden.
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_PRINT );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_OPAQUE );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_PROTECT );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_SURROUND );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_VERT_ORIENT );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_HORI_ORIENT );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_LR_SPACE );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_UL_SPACE );
//STRIP001              lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_BACKGROUND );
//STRIP001              if( bCpyBrd )
//STRIP001              {
//STRIP001                  // JP 07.07.99: Bug 67029 - if at Grafik no BoxItem but
//STRIP001                  //              in the new Format is any, then set the
//STRIP001                  //              default item in the new Set. Because
//STRIP001                  //              the Size of the Grafik have never been
//STRIP001                  //              changed!
//STRIP001                  const SfxPoolItem *pItem;
//STRIP001                  if( SFX_ITEM_SET == pOldFmt->GetAttrSet().
//STRIP001                          GetItemState( RES_BOX, sal_True, &pItem ))
//STRIP001                      pNewSet->Put( *pItem );
//STRIP001                  else if( SFX_ITEM_SET == pNewFmt->GetAttrSet().
//STRIP001                          GetItemState( RES_BOX, sal_True ))
//STRIP001                      pNewSet->Put( *GetDfltAttr( RES_BOX ) );
//STRIP001
//STRIP001                  if( SFX_ITEM_SET == pOldFmt->GetAttrSet().
//STRIP001                          GetItemState( RES_SHADOW, sal_True, &pItem ))
//STRIP001                      pNewSet->Put( *pItem );
//STRIP001                  else if( SFX_ITEM_SET == pNewFmt->GetAttrSet().
//STRIP001                          GetItemState( RES_SHADOW, sal_True ))
//STRIP001                      pNewSet->Put( *GetDfltAttr( RES_SHADOW ) );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  //Die Attribute hart setzen, weil sie sonst aus der
//STRIP001                  // Vorlage kommen koenten und dann passt die
//STRIP001                  // Grossenberechnung nicht mehr.
//STRIP001                  pNewSet->Put( SvxBoxItem() );
//STRIP001                  pNewSet->Put( SvxShadowItem() );
//STRIP001              }
//STRIP001
//STRIP001              //Anker immer uebertragen, ist sowieso ein hartes Attribut.
//STRIP001              pNewSet->Put( pOldFmt->GetAnchor() );
//STRIP001
//STRIP001              //In der Hoehe soll der neue Varabel sein!
//STRIP001              SwFmtFrmSize aFrmSize( pOldFmt->GetFrmSize() );
//STRIP001              aFrmSize.SetSizeType( ATT_MIN_SIZE );
//STRIP001              pNewSet->Put( aFrmSize );
//STRIP001
//STRIP001              SwStartNode* pSttNd = GetNodes().MakeTextSection(
//STRIP001                          SwNodeIndex( GetNodes().GetEndOfAutotext() ),
//STRIP001                          SwFlyStartNode, pColl );
//STRIP001              pNewSet->Put( SwFmtCntnt( pSttNd ));
//STRIP001
//STRIP001              pNewFmt->SetAttr( *pNewSet );
//STRIP001
//STRIP001              //Bei InCntnt's wird es spannend: Das TxtAttribut muss
//STRIP001              //vernichtet werden. Leider reisst dies neben den Frms auch
//STRIP001              //noch das Format mit in sein Grab. Um dass zu unterbinden
//STRIP001              //loesen wir vorher die Verbindung zwischen Attribut und Format.
//STRIP001
//STRIP001              const SwFmtAnchor& rAnchor = pNewFmt->GetAnchor();
//STRIP001              if( FLY_IN_CNTNT == rAnchor.GetAnchorId() )
//STRIP001              {
//STRIP001                  const SwPosition *pPos = rAnchor.GetCntntAnchor();
//STRIP001                  SwTxtNode *pTxtNode = pPos->nNode.GetNode().GetTxtNode();
//STRIP001                  ASSERT( pTxtNode->HasHints(), "Missing FlyInCnt-Hint." );
//STRIP001                  const xub_StrLen nIdx = pPos->nContent.GetIndex();
//STRIP001                  SwTxtAttr *pHnt = pTxtNode->GetTxtAttr( nIdx, RES_TXTATR_FLYCNT );
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001                  ASSERT( pHnt && pHnt->Which() == RES_TXTATR_FLYCNT,
//STRIP001                              "Missing FlyInCnt-Hint." );
//STRIP001                  ASSERT( pHnt && ((SwFmtFlyCnt&)pHnt->GetFlyCnt()).
//STRIP001                              GetFrmFmt() == pOldFmt,
//STRIP001                              "Wrong TxtFlyCnt-Hint." );
//STRIP001 #endif
//STRIP001                  ((SwFmtFlyCnt&)pHnt->GetFlyCnt()).SetFlyFmt( pNewFmt );
//STRIP001              }
//STRIP001
//STRIP001
//STRIP001              //Der Alte soll keinen Umlauf haben, und er soll oben/mittig
//STRIP001              //ausgerichtet sein.
//STRIP001              //Ausserdem soll die Breite 100% betragen und bei Aenderungen
//STRIP001              //Die Hoehe mit anpassen.
//STRIP001              pNewSet->ClearItem();
//STRIP001
//STRIP001              pNewSet->Put( SwFmtSurround( SURROUND_NONE ) );
//STRIP001              pNewSet->Put( SvxOpaqueItem( RES_OPAQUE, sal_True ) );
//STRIP001              pNewSet->Put( SwFmtVertOrient( VERT_TOP ) );
//STRIP001              pNewSet->Put( SwFmtHoriOrient( HORI_CENTER ) );
//STRIP001
//STRIP001              aFrmSize = pOldFmt->GetFrmSize();
//STRIP001              aFrmSize.SetWidthPercent( 100 );
//STRIP001              aFrmSize.SetHeightPercent( 255 );
//STRIP001              pNewSet->Put( aFrmSize );
//STRIP001
//STRIP001              //Die Attribute setzen wir hart, weil sie sonst aus der Vorlage
//STRIP001              //kommen koenten und dann passt die Grossenberechnung nicht mehr.
//STRIP001              if( bCpyBrd )
//STRIP001              {
//STRIP001                  pNewSet->Put( SvxBoxItem() );
//STRIP001                  pNewSet->Put( SvxShadowItem() );
//STRIP001              }
//STRIP001              pNewSet->Put( SvxLRSpaceItem() );
//STRIP001              pNewSet->Put( SvxULSpaceItem() );
//STRIP001
//STRIP001              //Der Alte ist absatzgebunden, und zwar am Absatz im neuen.
//STRIP001              SwFmtAnchor aAnch( FLY_AT_CNTNT );
//STRIP001              SwNodeIndex aAnchIdx( *pNewFmt->GetCntnt().GetCntntIdx(), 1 );
//STRIP001              pNew = aAnchIdx.GetNode().GetTxtNode();
//STRIP001              SwPosition aPos( aAnchIdx );
//STRIP001              aAnch.SetAnchor( &aPos );
//STRIP001              pNewSet->Put( aAnch );
//STRIP001
//STRIP001              if( pUndo )
//STRIP001                  pUndo->SetFlys( *pOldFmt, *pNewSet, *pNewFmt );
//STRIP001              else
//STRIP001                  pOldFmt->SetAttr( *pNewSet );
//STRIP001
//STRIP001              delete pNewSet;
//STRIP001
//STRIP001              //Nun nur noch die Flys erzeugen lassen. Das ueberlassen
//STRIP001              //wir vorhanden Methoden (insb. fuer InCntFlys etwas aufwendig).
//STRIP001              pNewFmt->MakeFrms();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          ASSERT( !this, "Neuer LabelType?." );
//STRIP001  }
//STRIP001  ASSERT( pNew, "No Label inserted" );
//STRIP001
//STRIP001  if( pNew )
//STRIP001  {
//STRIP001      //String aufbereiten
//STRIP001      String aTxt( aFld.GetTyp()->GetName() );
//STRIP001      aTxt += ' ';
//STRIP001      xub_StrLen nIdx = aTxt.Len();
//STRIP001      aTxt += rTxt;
//STRIP001
//STRIP001      //String einfuegen
//STRIP001      SwIndex aIdx( pNew, 0 );
//STRIP001      pNew->Insert( aTxt, aIdx );
//STRIP001
//STRIP001      //Feld einfuegen
//STRIP001      pNew->Insert( SwFmtFld( aFld ), nIdx, nIdx );
//STRIP001
//STRIP001      if ( bTable )
//STRIP001      {
//STRIP001          if ( bBefore )
//STRIP001          {
//STRIP001              if ( !pNew->GetSwAttrSet().GetKeep().GetValue()  )
//STRIP001                  pNew->SwCntntNode::SetAttr( SvxFmtKeepItem( sal_True ) );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwTableNode *pNd = GetNodes()[nNdIdx]->GetStartNode()->GetTableNode();
//STRIP001              SwTable &rTbl = pNd->GetTable();
//STRIP001              if ( !rTbl.GetFrmFmt()->GetKeep().GetValue() )
//STRIP001                  rTbl.GetFrmFmt()->SetAttr( SvxFmtKeepItem( sal_True ) );
//STRIP001              if ( pUndo )
//STRIP001                  pUndo->SetUndoKeep();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001      AppendUndo( pUndo );
//STRIP001  else
//STRIP001      DelAllUndoObj();
//STRIP001  DoUndo( bWasUndo );
//STRIP001
//STRIP001  return pNewFmt;
//STRIP001 }

/*************************************************************************
|*
|*  SwDoc::InsertDrawLabel()
|*
|*  Ersterstellung      MIB 7. Dez. 98
|*  Letzte Aenderung    MIB 7. Dez. 98
|*
|*************************************************************************/

//STRIP001 SwFlyFrmFmt* SwDoc::InsertDrawLabel( const String &rTxt,
//STRIP001                                   const sal_uInt16 nId,
//STRIP001                                   SdrObject& rSdrObj )
//STRIP001 {
//STRIP001
//STRIP001  SwDrawContact *pContact = (SwDrawContact*)GetUserCall( &rSdrObj );
//STRIP001  ASSERT( RES_DRAWFRMFMT == pContact->GetFmt()->Which(),
//STRIP001          "Kein DrawFrmFmt" );
//STRIP001  if( !pContact )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwDrawFrmFmt *pOldFmt = (SwDrawFrmFmt *)pContact->GetFmt();
//STRIP001  if( !pOldFmt )
//STRIP001      return 0;
//STRIP001
//STRIP001  sal_Bool bWasUndo = DoesUndo();
//STRIP001  sal_Bool bWasNoDrawUndo = IsNoDrawUndoObj();
//STRIP001  SwUndoInsertLabel* pUndo = 0;
//STRIP001  if( bWasUndo )
//STRIP001  {
//STRIP001      ClearRedo();
//STRIP001      pUndo = new SwUndoInsertLabel( LTYPE_DRAW, rTxt, sal_False, nId, sal_False );
//STRIP001      DoUndo( sal_False );
//STRIP001      SetNoDrawUndoObj( sal_True );
//STRIP001  }
//STRIP001
//STRIP001  // Erstmal das Feld bauen, weil ueber den Namen die TxtColl besorgt
//STRIP001  // werden muss
//STRIP001  ASSERT( nId < GetFldTypes()->Count(), "FldType ueberindiziert." );
//STRIP001  SwFieldType *pType = (*GetFldTypes())[nId];
//STRIP001  ASSERT( pType->Which() == RES_SETEXPFLD, "Falsche Id fuer Label" );
//STRIP001  SwSetExpField aFld( (SwSetExpFieldType*)pType, aEmptyStr,
//STRIP001                      SVX_NUM_ARABIC);
//STRIP001
//STRIP001  SwTxtFmtColl *pColl = FindTxtFmtCollByName( pType->GetName() );
//STRIP001  if( !pColl )
//STRIP001  {
//STRIP001      ASSERT( !this, "TxtCollection fuer Label nicht gefunden." );
//STRIP001      pColl = GetTxtCollFromPool( RES_POOLCOLL_TEXT );
//STRIP001  }
//STRIP001
//STRIP001  SwTxtNode *pNew = 0;
//STRIP001  SwFlyFrmFmt *pNewFmt = 0;
//STRIP001
//STRIP001  // Rahmen zerstoeren, neuen Rahmen einfuegen, entsprechenden
//STRIP001  // Node mit Feld in den neuen Rahmen, den alten Rahmen mit
//STRIP001  // dem Object (Grafik/Ole) absatzgebunden in den neuen Rahmen,
//STRIP001  // Frames erzeugen.
//STRIP001
//STRIP001  pOldFmt->DelFrms();
//STRIP001
//STRIP001  //Bei InCntnt's wird es spannend: Das TxtAttribut muss
//STRIP001  //vernichtet werden. Leider reisst dies neben den Frms auch
//STRIP001  //noch das Format mit in sein Grab. Um dass zu unterbinden
//STRIP001  //loesen wir vorher die Verbindung zwischen Attribut und Format.
//STRIP001  SfxItemSet* pNewSet = pOldFmt->GetAttrSet().Clone( sal_False );
//STRIP001
//STRIP001  // Ggf. Groesse und Position des Rahmens schuetzen
//STRIP001  if ( rSdrObj.IsMoveProtect() || rSdrObj.IsResizeProtect() )
//STRIP001  {
//STRIP001      SvxProtectItem aProtect;
//STRIP001      aProtect.SetCntntProtect( sal_False );
//STRIP001      aProtect.SetPosProtect( rSdrObj.IsMoveProtect() );
//STRIP001      aProtect.SetSizeProtect( rSdrObj.IsResizeProtect() );
//STRIP001      pNewSet->Put( aProtect );
//STRIP001  }
//STRIP001
//STRIP001  // Umlauf uebernehmen
//STRIP001  lcl_CpyAttr( *pNewSet, pOldFmt->GetAttrSet(), RES_SURROUND );
//STRIP001
//STRIP001  // Den Rahmen ggf. in den Hintergrund schicken.
//STRIP001  sal_Int8 nLayerId = rSdrObj.GetLayer();
//STRIP001     // OD 02.07.2003 #108784# - consider 'invisible' hell layer.
//STRIP001  if ( GetHellId() != nLayerId &&
//STRIP001      GetInvisibleHellId() != nLayerId )
//STRIP001  {
//STRIP001      SvxOpaqueItem aOpaque;
//STRIP001      aOpaque.SetValue( sal_True );
//STRIP001      pNewSet->Put( aOpaque );
//STRIP001  }
//STRIP001
//STRIP001  // Position uebernehmen
//STRIP001  Point aPoint( rSdrObj.GetRelativePos() );
//STRIP001  SwFmtVertOrient aVert( aPoint.B(), VERT_NONE, FRAME );
//STRIP001  SwFmtHoriOrient aHori( aPoint.A(), HORI_NONE, FRAME );
//STRIP001  pNewSet->Put( aVert );
//STRIP001  pNewSet->Put( aHori );
//STRIP001
//STRIP001  pNewSet->Put( pOldFmt->GetAnchor() );
//STRIP001
//STRIP001  //In der Hoehe soll der neue Varabel sein!
//STRIP001      Size aSz( rSdrObj.GetBoundRect().GetSize() );
//STRIP001  SwFmtFrmSize aFrmSize( ATT_MIN_SIZE, aSz.Width(), aSz.Height() );
//STRIP001  pNewSet->Put( aFrmSize );
//STRIP001
//STRIP001  // Abstaende auf den neuen Rahmen uebertragen. Eine Umrandung
//STRIP001  // gibt es beu Zeichen-Objekten nicht, also muss sie geloescht
//STRIP001  // werden.
//STRIP001  // MA: Falsch sie wird nicht gesetzt, denn die aus der Vorlage
//STRIP001  // soll ruhig wirksam werden
//STRIP001  pNewSet->Put( pOldFmt->GetLRSpace() );
//STRIP001  pNewSet->Put( pOldFmt->GetULSpace() );
//STRIP001
//STRIP001  SwStartNode* pSttNd = GetNodes().MakeTextSection(
//STRIP001              SwNodeIndex( GetNodes().GetEndOfAutotext() ),
//STRIP001              SwFlyStartNode, pColl );
//STRIP001
//STRIP001  pNewFmt = MakeFlyFrmFmt( GetUniqueFrameName(),
//STRIP001                      GetFrmFmtFromPool( RES_POOLFRM_FRAME ));
//STRIP001
//STRIP001  // JP 28.10.99: Bug 69487 - set border and shadow to default if the
//STRIP001  //              template contains any.
//STRIP001  if( SFX_ITEM_SET == pNewFmt->GetAttrSet().GetItemState( RES_BOX, sal_True ))
//STRIP001      pNewSet->Put( *GetDfltAttr( RES_BOX ) );
//STRIP001
//STRIP001  if( SFX_ITEM_SET == pNewFmt->GetAttrSet().GetItemState(RES_SHADOW,sal_True))
//STRIP001      pNewSet->Put( *GetDfltAttr( RES_SHADOW ) );
//STRIP001
//STRIP001  pNewFmt->SetAttr( SwFmtCntnt( pSttNd ));
//STRIP001  pNewFmt->SetAttr( *pNewSet );
//STRIP001
//STRIP001  const SwFmtAnchor& rAnchor = pNewFmt->GetAnchor();
//STRIP001  if( FLY_IN_CNTNT == rAnchor.GetAnchorId() )
//STRIP001  {
//STRIP001      const SwPosition *pPos = rAnchor.GetCntntAnchor();
//STRIP001      SwTxtNode *pTxtNode = pPos->nNode.GetNode().GetTxtNode();
//STRIP001      ASSERT( pTxtNode->HasHints(), "Missing FlyInCnt-Hint." );
//STRIP001      const xub_StrLen nIdx = pPos->nContent.GetIndex();
//STRIP001      SwTxtAttr *pHnt = pTxtNode->GetTxtAttr( nIdx, RES_TXTATR_FLYCNT );
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001      ASSERT( pHnt && pHnt->Which() == RES_TXTATR_FLYCNT,
//STRIP001                  "Missing FlyInCnt-Hint." );
//STRIP001      ASSERT( pHnt && ((SwFmtFlyCnt&)pHnt->GetFlyCnt()).
//STRIP001                  GetFrmFmt() == (SwFrmFmt*)pOldFmt,
//STRIP001                  "Wrong TxtFlyCnt-Hint." );
//STRIP001 #endif
//STRIP001      ((SwFmtFlyCnt&)pHnt->GetFlyCnt()).SetFlyFmt( pNewFmt );
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  //Der Alte soll keinen Umlauf haben, und er soll oben/mittig
//STRIP001  //ausgerichtet sein.
//STRIP001  pNewSet->ClearItem();
//STRIP001
//STRIP001  pNewSet->Put( SwFmtSurround( SURROUND_NONE ) );
//STRIP001  if( nLayerId == GetHellId() )
//STRIP001      rSdrObj.SetLayer( GetHeavenId() );
//STRIP001     // OD 02.07.2003 #108784# - consider drawing objects in 'invisible' hell layer
//STRIP001     else if( nLayerId == GetInvisibleHellId() )
//STRIP001         rSdrObj.SetLayer( GetInvisibleHeavenId() );
//STRIP001  pNewSet->Put( SvxLRSpaceItem() );
//STRIP001  pNewSet->Put( SvxULSpaceItem() );
//STRIP001
//STRIP001  rSdrObj.SetRelativePos( Point(0,0) );
//STRIP001
//STRIP001  //Der Alte ist absatzgebunden, und zwar am Absatz im neuen.
//STRIP001  SwFmtAnchor aAnch( FLY_AT_CNTNT );
//STRIP001  SwNodeIndex aAnchIdx( *pNewFmt->GetCntnt().GetCntntIdx(), 1 );
//STRIP001  pNew = aAnchIdx.GetNode().GetTxtNode();
//STRIP001  SwPosition aPos( aAnchIdx );
//STRIP001  aAnch.SetAnchor( &aPos );
//STRIP001  pNewSet->Put( aAnch );
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      pUndo->SetFlys( *pOldFmt, *pNewSet, *pNewFmt );
//STRIP001      pUndo->SetDrawObj( aPoint, nLayerId );
//STRIP001  }
//STRIP001  else
//STRIP001      pOldFmt->SetAttr( *pNewSet );
//STRIP001
//STRIP001  delete pNewSet;
//STRIP001
//STRIP001  //Nun nur noch die Flys erzeugen lassen. Das ueberlassen
//STRIP001  //wir vorhanden Methoden (insb. fuer InCntFlys etwas aufwendig).
//STRIP001  pNewFmt->MakeFrms();
//STRIP001
//STRIP001  ASSERT( pNew, "No Label inserted" );
//STRIP001
//STRIP001  if( pNew )
//STRIP001  {
//STRIP001      //String aufbereiten
//STRIP001      String aTxt( aFld.GetTyp()->GetName() );
//STRIP001      aTxt += ' ';
//STRIP001      xub_StrLen nIdx = aTxt.Len();
//STRIP001      aTxt += rTxt;
//STRIP001
//STRIP001      //String einfuegen
//STRIP001      SwIndex aIdx( pNew, 0 );
//STRIP001      pNew->Insert( aTxt, aIdx );
//STRIP001
//STRIP001      //Feld einfuegen
//STRIP001      pNew->Insert( SwFmtFld( aFld ), nIdx, nIdx );
//STRIP001  }
//STRIP001
//STRIP001  if( pUndo )
//STRIP001  {
//STRIP001      AppendUndo( pUndo );
//STRIP001      SetNoDrawUndoObj( bWasNoDrawUndo );
//STRIP001  }
//STRIP001  else
//STRIP001      DelAllUndoObj();
//STRIP001  DoUndo( bWasUndo );
//STRIP001
//STRIP001  return pNewFmt;
//STRIP001 }

/*************************************************************************
|*
|*  SwDoc::DoIdleJobs()
|*
|*  Ersterstellung      OK 30.03.94
|*  Letzte Aenderung    MA 09. Jun. 95
|*
|*************************************************************************/

/*N*/ IMPL_LINK( SwDoc, DoIdleJobs, Timer *, pTimer )
/*N*/ {
/*N*/ #ifdef TIMELOG
/*N*/   static ::rtl::Logfile* pModLogFile = 0;
/*N*/   if( !pModLogFile )
/*N*/       pModLogFile = new ::rtl::Logfile( "First DoIdleJobs" );
/*N*/ #endif
/*N*/
/*N*/   if( !SfxProgress::GetActiveProgress( pDocShell ) &&
/*N*/       GetRootFrm() && GetRootFrm()->GetCurrShell() )
/*N*/   {
/*N*/       ViewShell *pSh, *pStartSh;
/*N*/       pSh = pStartSh = GetRootFrm()->GetCurrShell();
/*N*/       do {
/*N*/           if( pSh->ActionPend() )
/*N*/               return 0;
/*N*/           pSh = (ViewShell*)pSh->GetNext();
/*N*/       } while( pSh != pStartSh );
/*N*/
/*N*/       sal_uInt16 nFldUpdFlag;
/*N*/       if( GetRootFrm()->IsIdleFormat() )
/*N*/           GetRootFrm()->GetCurrShell()->LayoutIdle();
/*N*/       else if( ( AUTOUPD_FIELD_ONLY == ( nFldUpdFlag = GetFldUpdateFlags() )
/*N*/                   || AUTOUPD_FIELD_AND_CHARTS == nFldUpdFlag ) &&
/*N*/               GetUpdtFlds().IsFieldsDirty() &&
/*N*/               !GetUpdtFlds().IsInUpdateFlds() &&
/*N*/               !IsExpFldsLocked()
/*N*/               // das umschalten der Feldname fuehrt zu keinem Update der
/*N*/               // Felder, also der "Hintergrund-Update" immer erfolgen
/*N*/               /* && !pStartSh->GetViewOptions()->IsFldName()*/ )
/*N*/       {
/*N*/           // chaos::Action-Klammerung!
/*N*/           GetUpdtFlds().SetInUpdateFlds( sal_True );
/*N*/
/*N*/           GetRootFrm()->StartAllAction();
/*N*/
/*N*/           GetSysFldType( RES_CHAPTERFLD )->Modify( 0, 0 );    // KapitelFld
/*N*/           UpdateExpFlds( 0, sal_False );      // Expression-Felder Updaten
/*N*/           UpdateTblFlds();                // Tabellen
/*N*/           UpdateRefFlds();                // Referenzen
/*N*/
/*N*/           if( AUTOUPD_FIELD_AND_CHARTS == nFldUpdFlag )
/*N*/               aChartTimer.Start();
/*N*/
/*N*/           GetRootFrm()->EndAllAction();
/*N*/
/*N*/           GetUpdtFlds().SetInUpdateFlds( sal_False );
/*N*/           GetUpdtFlds().SetFieldsDirty( sal_False );
/*N*/       }
/*N*/   }
/*N*/ #ifdef TIMELOG
/*N*/   if( pModLogFile && 1 != (long)pModLogFile )
/*N*/       delete pModLogFile, ((long&)pModLogFile) = 1;
/*N*/ #endif
/*N*/   return 0;
/*N*/ }

//STRIP001 IMPL_STATIC_LINK( SwDoc, BackgroundDone, SvxBrushItem*, EMPTYARG )
//STRIP001 {
//STRIP001  ViewShell *pSh, *pStartSh;
//STRIP001  pSh = pStartSh = pThis->GetRootFrm()->GetCurrShell();
//STRIP001  if( pStartSh )
//STRIP001      do {
//STRIP001          if( pSh->GetWin() )
//STRIP001          {
//STRIP001              //Fuer Repaint mir virtuellen Device sorgen.
//STRIP001              pSh->LockPaint();
//STRIP001              pSh->UnlockPaint( sal_True );
//STRIP001          }
//STRIP001          pSh = (ViewShell*)pSh->GetNext();
//STRIP001      } while( pSh != pStartSh );
//STRIP001  return 0;
//STRIP001 }

/*N*/ String lcl_GetUniqueFlyName( const SwDoc* pDoc, sal_uInt16 nDefStrId )
/*N*/ {
/*N*/   ResId aId( nDefStrId, pSwResMgr );
/*N*/   String aName( aId );
/*N*/   xub_StrLen nNmLen = aName.Len();
/*N*/
/*N*/   const SwSpzFrmFmts& rFmts = *pDoc->GetSpzFrmFmts();
/*N*/
/*N*/   sal_uInt16 nNum, nTmp, nFlagSize = ( rFmts.Count() / 8 ) +2;
/*N*/   sal_uInt8* pSetFlags = new sal_uInt8[ nFlagSize ];
/*N*/   memset( pSetFlags, 0, nFlagSize );
/*N*/
/*N*/   for( sal_uInt16 n = 0; n < rFmts.Count(); ++n )
/*N*/   {
/*N*/       const SwFrmFmt* pFlyFmt = rFmts[ n ];
/*N*/       if( RES_FLYFRMFMT == pFlyFmt->Which() &&
/*N*/           pFlyFmt->GetName().Match( aName ) == nNmLen )
/*N*/       {
/*N*/           // Nummer bestimmen und das Flag setzen
/*N*/           nNum = pFlyFmt->GetName().Copy( nNmLen ).ToInt32();
/*N*/           if( nNum-- && nNum < rFmts.Count() )
/*N*/               pSetFlags[ nNum / 8 ] |= (0x01 << ( nNum & 0x07 ));
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/   nNum = rFmts.Count();
/*N*/   for( n = 0; n < nFlagSize; ++n )
/*N*/       if( 0xff != ( nTmp = pSetFlags[ n ] ))
/*N*/       {
/*N*/           // also die Nummer bestimmen
/*N*/           nNum = n * 8;
/*N*/           while( nTmp & 1 )
/*N*/               ++nNum, nTmp >>= 1;
/*N*/           break;
/*N*/       }
/*N*/
/*N*/   __DELETE( nFlagSize ) pSetFlags;
/*N*/   return aName += String::CreateFromInt32( ++nNum );
/*N*/ }

/*N*/ String SwDoc::GetUniqueGrfName() const
/*N*/ {
/*N*/   return ::lcl_GetUniqueFlyName( this, STR_GRAPHIC_DEFNAME );
/*N*/ }

/*N*/ String SwDoc::GetUniqueOLEName() const
/*N*/ {
/*N*/   return ::lcl_GetUniqueFlyName( this, STR_OBJECT_DEFNAME );
/*N*/ }

/*N*/ String SwDoc::GetUniqueFrameName() const
/*N*/ {
/*N*/   return ::lcl_GetUniqueFlyName( this, STR_FRAME_DEFNAME );
/*N*/ }

/*N*/ const SwFlyFrmFmt* SwDoc::FindFlyByName( const String& rName, sal_Int8 nNdTyp ) const
/*N*/ {
/*N*/   const SwSpzFrmFmts& rFmts = *GetSpzFrmFmts();
/*N*/   for( sal_uInt16 n = rFmts.Count(); n; )
/*N*/   {
/*N*/       const SwFrmFmt* pFlyFmt = rFmts[ --n ];
/*N*/       const SwNodeIndex* pIdx;
/*N*/       if( RES_FLYFRMFMT == pFlyFmt->Which() && pFlyFmt->GetName() == rName &&
/*N*/           0 != ( pIdx = pFlyFmt->GetCntnt().GetCntntIdx() ) &&
/*N*/           pIdx->GetNode().GetNodes().IsDocNodes() )
/*N*/       {
/*?*/           if( nNdTyp )
/*?*/           {
/*?*/               // dann noch auf den richtigen Node-Typ abfragen
/*?*/               const SwNode* pNd = GetNodes()[ pIdx->GetIndex()+1 ];
/*?*/               if( nNdTyp == ND_TEXTNODE
/*?*/                       ? !pNd->IsNoTxtNode()
/*?*/                       : nNdTyp == pNd->GetNodeType() )
/*?*/                   return (SwFlyFrmFmt*)pFlyFmt;
/*?*/           }
/*?*/           else
/*?*/               return (SwFlyFrmFmt*)pFlyFmt;
/*?*/       }
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ void SwDoc::SetFlyName( SwFlyFrmFmt& rFmt, const String& rName )
/*N*/ {
/*N*/   String sName( rName );
/*N*/   if( !rName.Len() || FindFlyByName( rName ) )
/*N*/   {
/*?*/       sal_uInt16 nTyp = STR_FRAME_DEFNAME;
/*?*/       const SwNodeIndex* pIdx = rFmt.GetCntnt().GetCntntIdx();
/*?*/       if( pIdx && pIdx->GetNode().GetNodes().IsDocNodes() )
/*?*/           switch( GetNodes()[ pIdx->GetIndex() + 1 ]->GetNodeType() )
/*?*/           {
/*?*/           case ND_GRFNODE:    nTyp = STR_GRAPHIC_DEFNAME; break;
/*?*/           case ND_OLENODE:    nTyp = STR_OBJECT_DEFNAME;  break;
/*?*/           }
/*?*/       sName = ::lcl_GetUniqueFlyName( this, nTyp );
/*N*/   }
/*N*/   rFmt.SetName( sName, sal_True );
/*N*/ }

/*N*/ void SwDoc::SetAllUniqueFlyNames()
/*N*/ {
/*N*/   sal_uInt16 n, nFlyNum = 0, nGrfNum = 0, nOLENum = 0;
/*N*/
/*N*/   ResId nFrmId( STR_FRAME_DEFNAME, pSwResMgr ),
/*N*/         nGrfId( STR_GRAPHIC_DEFNAME, pSwResMgr ),
/*N*/         nOLEId( STR_OBJECT_DEFNAME, pSwResMgr );
/*N*/   String sFlyNm( nFrmId );
/*N*/   String sGrfNm( nGrfId );
/*N*/   String sOLENm( nOLEId );
/*N*/
/*N*/   if( 255 < ( n = GetSpzFrmFmts()->Count() ))
/*N*/       n = 255;
/*N*/   SwSpzFrmFmts aArr( (sal_Int8)n, 10 );
/*N*/   SwFrmFmtPtr pFlyFmt;
/*N*/   sal_Bool bLoadedFlag = sal_True;            // noch etwas fuers Layout
/*N*/
/*N*/   for( n = GetSpzFrmFmts()->Count(); n; )
/*N*/   {
/*N*/       if( RES_FLYFRMFMT == (pFlyFmt = (*GetSpzFrmFmts())[ --n ])->Which() )
/*N*/       {
/*N*/           sal_uInt16 *pNum = 0;
/*N*/           xub_StrLen nLen;
/*N*/           const String& rNm = pFlyFmt->GetName();
/*N*/           if( rNm.Len() )
/*N*/           {
/*N*/               if( rNm.Match( sGrfNm ) == ( nLen = sGrfNm.Len() ))
/*?*/                   pNum = &nGrfNum;
/*N*/               else if( rNm.Match( sFlyNm ) == ( nLen = sFlyNm.Len() ))
/*N*/                   pNum = &nFlyNum;
/*N*/               else if( rNm.Match( sOLENm ) == ( nLen = sOLENm.Len() ))
/*?*/                   pNum = &nOLENum;
/*N*/
/*N*/               if( pNum && *pNum < ( nLen = rNm.Copy( nLen ).ToInt32() ))
/*N*/                   *pNum = nLen;
/*N*/           }
/*N*/           else
/*N*/               // das wollen wir nachher setzen
/*?*/               aArr.Insert( pFlyFmt, aArr.Count() );
/*N*/
/*N*/       }
/*N*/       if( bLoadedFlag )
/*N*/       {
/*N*/           const SwFmtAnchor& rAnchor = pFlyFmt->GetAnchor();
/*N*/           if( ( FLY_PAGE == rAnchor.GetAnchorId() &&
/*N*/                   rAnchor.GetCntntAnchor() ) ||
/*N*/               // oder werden DrawObjecte rel. zu irgendetwas ausgerichtet?
/*N*/               ( RES_DRAWFRMFMT == pFlyFmt->Which() && (
/*N*/                   SFX_ITEM_SET == pFlyFmt->GetItemState(
/*N*/                                       RES_VERT_ORIENT )||
/*N*/                   SFX_ITEM_SET == pFlyFmt->GetItemState(
/*N*/                                       RES_HORI_ORIENT ))) )
/*N*/               bLoadedFlag = sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   const SwNodeIndex* pIdx;
/*N*/
/*N*/   for( n = aArr.Count(); n; )
/*?*/       if( 0 != ( pIdx = ( pFlyFmt = aArr[ --n ])->GetCntnt().GetCntntIdx() )
/*?*/           && pIdx->GetNode().GetNodes().IsDocNodes() )
/*?*/       {
/*?*/           sal_uInt16 nNum;
/*?*/           String sNm;
/*?*/           switch( GetNodes()[ pIdx->GetIndex() + 1 ]->GetNodeType() )
/*?*/           {
/*?*/           case ND_GRFNODE:
/*?*/               sNm = sGrfNm;
/*?*/               nNum = ++nGrfNum;
/*?*/               break;
/*?*/           case ND_OLENODE:
/*?*/               sNm = sOLENm;
/*?*/               nNum = ++nOLENum;
/*?*/               break;
/*?*/           default:
/*?*/               sNm = sFlyNm;
/*?*/               nNum = ++nFlyNum;
/*?*/               break;
/*?*/           }
/*?*/           pFlyFmt->SetName( sNm += String::CreateFromInt32( nNum ));
/*?*/       }
/*N*/   aArr.Remove( 0, aArr.Count() );
/*N*/
/*N*/   if( GetFtnIdxs().Count() )
/*N*/   {
/*N*/       SwTxtFtn::SetUniqueSeqRefNo( *this );
/*N*/       SwNodeIndex aTmp( GetNodes() );
/*N*/       GetFtnIdxs().UpdateFtn( aTmp );
/*N*/   }
/*N*/
/*N*/   // neues Document und keine seitengebundenen Rahmen/DrawObjecte gefunden,
/*N*/   // die an einem Node verankert sind.
/*N*/   if( bLoadedFlag )
/*N*/       SetLoaded( sal_True );
/*N*/ }

/*N*/ sal_Bool SwDoc::IsInHeaderFooter( const SwNodeIndex& rIdx ) const
/*N*/ {
/*N*/   // gibt es ein Layout, dann ueber das laufen!!
/*N*/   //  (Das kann dann auch Fly in Fly in Kopfzeile !)
/*N*/   // MIB 9.2.98: Wird auch vom sw3io benutzt, um festzustellen, ob sich
/*N*/   // ein Redline-Objekt in einer Kopf- oder Fusszeile befindet. Da
/*N*/   // Redlines auch an Start- und Endnodes haengen, muss der Index nicht
/*N*/   // unbedingt der eines Content-Nodes sein.
/*N*/   SwNode* pNd = &rIdx.GetNode();
/*N*/   if( pNd->IsCntntNode() && pLayout )
/*N*/   {
/*N*/       SwFrm *pFrm = pNd->GetCntntNode()->GetFrm();
/*N*/       if( pFrm )
/*N*/       {
/*N*/           SwFrm *pUp = pFrm->GetUpper();
/*N*/           while ( pUp && !pUp->IsHeaderFrm() && !pUp->IsFooterFrm() )
/*N*/           {
/*N*/               if ( pUp->IsFlyFrm() )
/*N*/                   pUp = ((SwFlyFrm*)pUp)->GetAnchor();
/*N*/               pUp = pUp->GetUpper();
/*N*/           }
/*N*/           if ( pUp )
/*N*/               return sal_True;
/*N*/
/*N*/           return sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/
/*N*/   const SwNode* pFlyNd = pNd->FindFlyStartNode();
/*N*/   while( pFlyNd )
/*N*/   {
/*N*/       // dann ueber den Anker nach oben "hangeln"
/*N*/       for( sal_uInt16 n = 0; n < GetSpzFrmFmts()->Count(); ++n )
/*N*/       {
/*N*/           const SwFrmFmt* pFmt = (*GetSpzFrmFmts())[ n ];
/*N*/           const SwNodeIndex* pIdx = pFmt->GetCntnt().GetCntntIdx();
/*N*/           if( pIdx && pFlyNd == &pIdx->GetNode() )
/*N*/           {
/*N*/               const SwFmtAnchor& rAnchor = pFmt->GetAnchor();
/*N*/               if( FLY_PAGE == rAnchor.GetAnchorId() ||
/*N*/                   !rAnchor.GetCntntAnchor() )
/*N*/                   return sal_False;
/*N*/
/*N*/               pNd = &rAnchor.GetCntntAnchor()->nNode.GetNode();
/*N*/               pFlyNd = pNd->FindFlyStartNode();
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/       if( n >= GetSpzFrmFmts()->Count() )
/*N*/       {
/*N*/           ASSERT( bInReading, "Fly-Section aber kein Format gefunden" );
/*N*/           return sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return 0 != pNd->FindHeaderStartNode() ||
/*N*/           0 != pNd->FindFooterStartNode();
/*N*/ }

#ifdef BIDI

/*N*/ short SwDoc::GetTextDirection( const SwPosition& rPos,
/*N*/                                const Point* pPt ) const
/*N*/ {
/*N*/     short nRet;
/*N*/   Point aPt;
/*N*/   if( pPt )
/*N*/       aPt = *pPt;
/*N*/
/*N*/   SwCntntNode *pNd = rPos.nNode.GetNode().GetCntntNode();
/*N*/   SwCntntFrm *pFrm;
/*N*/
/*N*/   if( pNd && 0 != (pFrm = pNd->GetFrm( &aPt, &rPos )) )
/*N*/     {
/*N*/         if ( pFrm->IsVertical() )
/*N*/         {
/*?*/             if ( pFrm->IsRightToLeft() )
/*?*/                 nRet = FRMDIR_VERT_TOP_LEFT;
/*?*/             else
/*?*/                 nRet = FRMDIR_VERT_TOP_RIGHT;
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/             if ( pFrm->IsRightToLeft() )
/*?*/                 nRet = FRMDIR_HORI_RIGHT_TOP;
/*N*/             else
/*?*/                 nRet = FRMDIR_HORI_LEFT_TOP;
/*N*/         }
/*N*/     }
/*N*/     else
/*N*/   {
/*?*/       const SvxFrameDirectionItem* pItem = 0;
/*?*/       if( pNd )
/*?*/       {
/*?*/           // in a flyframe? Then look at that for the correct attribute
/*?*/           const SwFrmFmt* pFlyFmt = pNd->GetFlyFmt();
/*?*/           while( pFlyFmt )
/*?*/           {
/*?*/               pItem = &pFlyFmt->GetFrmDir();
/*?*/               if( FRMDIR_ENVIRONMENT == pItem->GetValue() )
/*?*/               {
/*?*/                   pItem = 0;
/*?*/                   const SwFmtAnchor* pAnchor = &pFlyFmt->GetAnchor();
/*?*/                   if( FLY_PAGE != pAnchor->GetAnchorId() &&
/*?*/                       pAnchor->GetCntntAnchor() )
/*?*/                       pFlyFmt = pAnchor->GetCntntAnchor()->nNode.
/*?*/                                           GetNode().GetFlyFmt();
/*?*/                   else
/*?*/                       pFlyFmt = 0;
/*?*/               }
/*?*/               else
/*?*/                   pFlyFmt = 0;
/*?*/           }
/*?*/
/*?*/           if( !pItem )
/*?*/           {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001  const SwPageDesc* pPgDsc = pNd->FindPageDesc( FALSE );
//STRIP001 /*?*/                if( pPgDsc )
//STRIP001 /*?*/                    pItem = &pPgDsc->GetMaster().GetFrmDir();
/*?*/           }
/*?*/       }
/*?*/       if( !pItem )
/*?*/           pItem = (SvxFrameDirectionItem*)&GetAttrPool().GetDefaultItem(
/*?*/                                                           RES_FRAMEDIR );
/*?*/         nRet = pItem->GetValue();
/*?*/   }
/*N*/     return nRet;
/*N*/ }

//STRIP001 sal_Bool SwDoc::IsInVerticalText( const SwPosition& rPos, const Point* pPt ) const
//STRIP001 {
//STRIP001     const short nDir = GetTextDirection( rPos, pPt );
//STRIP001     return FRMDIR_VERT_TOP_RIGHT == nDir || FRMDIR_VERT_TOP_LEFT == nDir;
//STRIP001 }

#else

//STRIP001 sal_Bool SwDoc::IsInVerticalText( const SwPosition& rPos, const Point* pPt ) const
//STRIP001 {
//STRIP001  sal_Bool bRet;
//STRIP001  Point aPt;
//STRIP001  if( pPt )
//STRIP001      aPt = *pPt;
//STRIP001
//STRIP001  SwCntntNode *pNd = rPos.nNode.GetNode().GetCntntNode();
//STRIP001  SwCntntFrm *pFrm;
//STRIP001
//STRIP001  if( pNd && 0 != (pFrm = pNd->GetFrm( &aPt, &rPos )) )
//STRIP001      bRet = pFrm->IsVertical();
//STRIP001  else
//STRIP001  {
//STRIP001      const SvxFrameDirectionItem* pItem = 0;
//STRIP001      if( pNd )
//STRIP001      {
//STRIP001          // in a flyframe? Then look at that for the correct attribute
//STRIP001          const SwFrmFmt* pFlyFmt = pNd->GetFlyFmt();
//STRIP001          while( pFlyFmt )
//STRIP001          {
//STRIP001              pItem = &pFlyFmt->GetFrmDir();
//STRIP001              if( FRMDIR_ENVIRONMENT == pItem->GetValue() )
//STRIP001              {
//STRIP001                  pItem = 0;
//STRIP001                  const SwFmtAnchor* pAnchor = &pFlyFmt->GetAnchor();
//STRIP001                  if( FLY_PAGE != pAnchor->GetAnchorId() &&
//STRIP001                      pAnchor->GetCntntAnchor() )
//STRIP001                      pFlyFmt = pAnchor->GetCntntAnchor()->nNode.
//STRIP001                                          GetNode().GetFlyFmt();
//STRIP001                  else
//STRIP001                      pFlyFmt = 0;
//STRIP001              }
//STRIP001              else
//STRIP001                  pFlyFmt = 0;
//STRIP001          }
//STRIP001
//STRIP001          if( !pItem )
//STRIP001          {
//STRIP001              const SwPageDesc* pPgDsc = pNd->FindPageDesc( FALSE );
//STRIP001              if( pPgDsc )
//STRIP001                  pItem = &pPgDsc->GetMaster().GetFrmDir();
//STRIP001          }
//STRIP001      }
//STRIP001      if( !pItem )
//STRIP001          pItem = (SvxFrameDirectionItem*)&GetAttrPool().GetDefaultItem(
//STRIP001                                                          RES_FRAMEDIR );
//STRIP001      bRet = FRMDIR_VERT_TOP_RIGHT == pItem->GetValue() ||
//STRIP001             FRMDIR_VERT_TOP_LEFT == pItem->GetValue();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

#endif
