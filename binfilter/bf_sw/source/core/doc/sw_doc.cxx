/*************************************************************************
 *
 *  $RCSfile: sw_doc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: os $ $Date: 2004-04-22 15:41:14 $
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

#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif
#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif
#ifndef _SFXDOCINF_HXX //autogen
#include <bf_sfx2/docinf.hxx>
#endif
#ifndef _SVX_KEEPITEM_HXX //autogen
#include <bf_svx/keepitem.hxx>
#endif
#ifndef _SVX_CSCOITEM_HXX //autogen
#include <bf_svx/cscoitem.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef SMDLL0_HXX //autogen
#include <bf_starmath/smdll0.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#ifndef _SWMODULE_HXX //autogen
#include <swmodule.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTRFMRK_HXX //autogen
#include <fmtrfmrk.hxx>
#endif
#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _TXTINET_HXX //autogen
#include <txtinet.hxx>
#endif
#ifndef _TXTRFMRK_HXX //autogen
#include <txtrfmrk.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _LINKENUM_HXX
#include <linkenum.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>           // fuer die UndoIds
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> //DTor
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _ROLBCK_HXX
#include <rolbck.hxx>           // Undo-Attr
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>          // fuer die Bookmarks
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>           // fuer die Verzeichnisse
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>          // PoolVorlagen-Id's
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>           // fuer Server-Funktionalitaet
#endif
#ifndef _WRONG_HXX
#include <wrong.hxx>            // fuer OnlineSpell-Invalidierung
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>
#endif
#ifndef _ACORRECT_HXX
#include <acorrect.hxx>         // Autokorrektur
#endif
#ifndef _SECTION_HXX
#include <section.hxx>          //
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>           // Statusanzeige
#endif
#ifndef _DOCSTAT_HXX
#include <docstat.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _FLDUPDE_HXX
#include <fldupde.hxx>
#endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif

#ifndef _STATSTR_HRC
#include <statstr.hrc>          // StatLine-String
#endif
namespace binfilter {

// Seiten-Deskriptoren
/*N*/ SV_IMPL_PTRARR(SwPageDescs,SwPageDescPtr);
// Autoren
// IMPL_PTRREGARR_NOTL(Authors,Author) USED?
// Verzeichnisse
/*N*/ SV_IMPL_PTRARR( SwTOXTypes, SwTOXTypePtr )
// FeldTypen
/*N*/ SV_IMPL_PTRARR( SwFldTypes, SwFldTypePtr)


/*
 * Dokumenteditieren (Doc-SS) zum Fuellen des Dokuments
 * durch den RTF Parser und fuer die EditShell.
 */
/*N*/ void SwDoc::ChgDBData(const SwDBData& rNewData)
/*N*/ {
/*N*/   if( rNewData != aDBData )
/*N*/   {
/*N*/       aDBData = rNewData;
/*N*/       SetModified();
/*N*/   }
/*N*/   GetSysFldType(RES_DBNAMEFLD)->UpdateFlds();
/*N*/ }

/*N*/ BOOL SwDoc::SplitNode( const SwPosition &rPos, BOOL bChkTableStart )
/*N*/ {
/*N*/   SwCntntNode *pNode = rPos.nNode.GetNode().GetCntntNode();
/*N*/   if(0 == pNode)
/*N*/       return FALSE;
/*N*/
/*N*/   {
/*N*/       // Bug 26675:   DataChanged vorm loeschen verschicken, dann bekommt
/*N*/       //          man noch mit, welche Objecte sich im Bereich befinden.
/*N*/       //          Danach koennen sie vor/hinter der Position befinden.
/*N*/       SwDataChanged aTmp( this, rPos, 0 );
/*N*/   }
/*N*/
/*N*/   SwUndoSplitNode* pUndo = 0;
/*N*/   if ( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       // einfuegen vom Undo-Object, z.Z. nur beim TextNode
/*N*/       if( pNode->IsTxtNode() )
/*N*/           AppendUndo( pUndo = new SwUndoSplitNode( this, rPos, bChkTableStart  ));
/*N*/   }
/*N*/
/*N*/   //JP 28.01.97: Sonderfall fuer SplitNode am Tabellenanfang:
/*N*/   //              steht die am Doc/Fly/Footer/..-Anfang oder direkt
/*N*/   //              hinter einer Tabelle, dann fuege davor
/*N*/   //              einen Absatz ein
/*N*/   if( bChkTableStart && !rPos.nContent.GetIndex() && pNode->IsTxtNode() )
/*N*/   {
/*?*/       ULONG nPrevPos = rPos.nNode.GetIndex() - 1;
/*?*/       const SwTableNode* pTblNd;
/*?*/       const SwNode* pNd = GetNodes()[ nPrevPos ];
/*?*/       if( pNd->IsStartNode() &&
/*?*/           SwTableBoxStartNode == ((SwStartNode*)pNd)->GetStartNodeType() &&
/*?*/           0 != ( pTblNd = GetNodes()[ --nPrevPos ]->GetTableNode() ) &&
/*?*/           ((( pNd = GetNodes()[ --nPrevPos ])->IsStartNode() &&
/*?*/              SwTableBoxStartNode != ((SwStartNode*)pNd)->GetStartNodeType() )
/*?*/              || ( pNd->IsEndNode() && pNd->FindStartNode()->IsTableNode() )
/*?*/              || pNd->IsCntntNode() ))
/*?*/       {
/*?*/           if( pNd->IsCntntNode() )
/*?*/           {
/*?*/               //JP 30.04.99 Bug 65660:
/*?*/               // ausserhalb des normalen BodyBereiches gibt es keine
/*?*/               // Seitenumbrueche, also ist das hier kein gueltige
/*?*/               // Bedingung fuers einfuegen eines Absatzes
/*?*/               if( nPrevPos < GetNodes().GetEndOfExtras().GetIndex() )
/*?*/                   pNd = 0;
/*?*/               else
/*?*/               {
/*?*/                   // Dann nur, wenn die Tabelle Umbrueche traegt!
/*?*/                   const SwFrmFmt* pFrmFmt = pTblNd->GetTable().GetFrmFmt();
/*?*/                   if( SFX_ITEM_SET != pFrmFmt->GetItemState(RES_PAGEDESC, FALSE) &&
/*?*/                       SFX_ITEM_SET != pFrmFmt->GetItemState( RES_BREAK, FALSE ) )
/*?*/                       pNd = 0;
/*?*/               }
/*?*/           }
/*?*/
/*?*/           if( pNd )
/*?*/           {
/*?*/               SwTxtNode* pTxtNd = GetNodes().MakeTxtNode(
/*?*/                                       SwNodeIndex( *pTblNd ),
/*?*/                                       GetTxtCollFromPool( RES_POOLCOLL_TEXT ));
/*?*/               if( pTxtNd )
/*?*/               {
/*?*/                   ((SwPosition&)rPos).nNode = pTblNd->GetIndex()-1;
/*?*/                   ((SwPosition&)rPos).nContent.Assign( pTxtNd, 0 );
/*?*/
/*?*/                   // nur im BodyBereich den SeitenUmbruch/-Vorlage umhaengem
/*?*/                   if( nPrevPos > GetNodes().GetEndOfExtras().GetIndex() )
/*?*/                   {
/*?*/                       SwFrmFmt* pFrmFmt = pTblNd->GetTable().GetFrmFmt();
/*?*/                       const SfxPoolItem *pItem;
/*?*/                       if( SFX_ITEM_SET == pFrmFmt->GetItemState( RES_PAGEDESC,
/*?*/                           FALSE, &pItem ) )
/*?*/                       {
/*?*/                           pTxtNd->SwCntntNode::SetAttr( *pItem );
/*?*/                           pFrmFmt->ResetAttr( RES_PAGEDESC );
/*?*/                       }
/*?*/                       if( SFX_ITEM_SET == pFrmFmt->GetItemState( RES_BREAK,
/*?*/                           FALSE, &pItem ) )
/*?*/                       {
/*?*/                           pTxtNd->SwCntntNode::SetAttr( *pItem );
/*?*/                           pFrmFmt->ResetAttr( RES_BREAK );
/*?*/                       }
/*?*/                   }
/*?*/
/*?*/                   if( pUndo )
/*?*/                       pUndo->SetTblFlag();
/*?*/                   SetModified();
/*?*/                   return TRUE;
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   SvULongs aBkmkArr( 15, 15 );
/*N*/   _SaveCntntIdx( this, rPos.nNode.GetIndex(), rPos.nContent.GetIndex(),
/*N*/                   aBkmkArr, SAVEFLY_SPLIT );
/*N*/   if( 0 != ( pNode = pNode->SplitNode( rPos ) ))
/*N*/   {
/*N*/       // verschiebe noch alle Bookmarks/TOXMarks/FlyAtCnt
/*N*/       if( aBkmkArr.Count() )
/*?*/   {   DBG_ASSERT(0, "STRIP"); }//STRIP001     _RestoreCntntIdx( this, aBkmkArr, rPos.nNode.GetIndex()-1, 0, TRUE );
/*N*/
/*N*/       if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 SwPaM aPam( rPos );
//STRIP001 /*?*/            aPam.SetMark();
//STRIP001 /*?*/            aPam.Move( fnMoveBackward );
//STRIP001 /*?*/            if( IsRedlineOn() )
//STRIP001 /*?*/                AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/            else
//STRIP001 /*?*/                SplitRedline( aPam );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SwDoc::AppendTxtNode( SwPosition& rPos )
/*N*/ {
    /*
     * Neuen Node vor EndOfContent erzeugen.
     */
/*N*/   SwTxtNode *pCurNode = GetNodes()[ rPos.nNode ]->GetTxtNode();
/*N*/   if( !pCurNode )
/*N*/   {
/*?*/       // dann kann ja einer angelegt werden!
/*?*/       SwNodeIndex aIdx( rPos.nNode, 1 );
/*?*/       pCurNode = GetNodes().MakeTxtNode( aIdx,
/*?*/                       GetTxtCollFromPool( RES_POOLCOLL_STANDARD ));
/*N*/   }
/*N*/   else
/*N*/       pCurNode = (SwTxtNode*)pCurNode->AppendNode( rPos );
/*N*/
/*N*/   rPos.nNode++;
/*N*/   rPos.nContent.Assign( pCurNode, 0 );
/*N*/
/*N*/   if( DoesUndo() )
/*N*/   {
/*N*/       ClearRedo();
/*N*/       AppendUndo( new SwUndoInsert( rPos.nNode ));
/*N*/   }
/*N*/
/*N*/   if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SwPaM aPam( rPos );
//STRIP001 /*?*/        aPam.SetMark();
//STRIP001 /*?*/        aPam.Move( fnMoveBackward );
//STRIP001 /*?*/        if( IsRedlineOn() )
//STRIP001 /*?*/            AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/        else
//STRIP001 /*?*/            SplitRedline( aPam );
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SwDoc::Insert( const SwPaM &rRg, const String &rStr, BOOL bHintExpand )
/*N*/ {
/*N*/   if( DoesUndo() )
/*N*/       ClearRedo();
/*N*/
/*N*/   const SwPosition* pPos = rRg.GetPoint();
/*N*/
/*N*/   if( pACEWord )                  // Aufnahme in die Autokorrektur
/*N*/   {
/*?*/       if( 1 == rStr.Len() && pACEWord->IsDeleted() )
/*?*/        {DBG_ASSERT(0, "STRIP");} //STRIP001   pACEWord->CheckChar( *pPos, rStr.GetChar( 0 ) );
/*?*/       delete pACEWord, pACEWord = 0;
/*N*/   }
/*N*/
/*N*/   SwTxtNode *pNode = pPos->nNode.GetNode().GetTxtNode();
/*N*/   if(!pNode)
/*N*/       return FALSE;

/*N*/   const USHORT nInsMode = bHintExpand ? INS_EMPTYEXPAND
/*N*/                                    : INS_NOHINTEXPAND;
/*N*/   SwDataChanged aTmp( rRg, 0 );
/*N*/
/*N*/   if( !DoesUndo() || !DoesGroupUndo() )
/*N*/   {
/*N*/       pNode->Insert( rStr, pPos->nContent, nInsMode );
/*N*/
/*N*/       if( DoesUndo() )
/*N*/           AppendUndo( new SwUndoInsert( pPos->nNode,
/*N*/                                   pPos->nContent.GetIndex(), rStr.Len() ));
/*N*/   }
/*N*/   else
/*N*/   {           // ist Undo und Gruppierung eingeschaltet, ist alles anders !
/*?*/       USHORT nUndoSize = pUndos->Count();
/*?*/       xub_StrLen nInsPos = pPos->nContent.GetIndex();
/*?*/       SwUndoInsert * pUndo;
/*?*/       CharClass& rCC = GetAppCharClass();
/*?*/
/*?*/       if( 0 == nUndoSize || UNDO_INSERT !=
/*?*/               ( pUndo = (SwUndoInsert*)(*pUndos)[ --nUndoSize ])->GetId() ||
/*?*/           !pUndo->CanGrouping( *pPos ))
/*?*/       {
/*?*/           pUndo = new SwUndoInsert( pPos->nNode, nInsPos, 0,
/*?*/                           !rCC.isLetterNumeric( rStr, 0 ) );
/*?*/           AppendUndo( pUndo );
/*?*/       }
/*?*/
/*?*/       for( xub_StrLen i = 0; i < rStr.Len(); ++i )
/*?*/       {
/*?*/           nInsPos++;
/*?*/           // wenn CanGrouping() TRUE returnt, ist schon alles erledigt
/*?*/           if( !pUndo->CanGrouping( rStr.GetChar( i ) ))
/*?*/           {
/*?*/               pUndo = new SwUndoInsert( pPos->nNode, nInsPos,  1,
/*?*/                           !rCC.isLetterNumeric( rStr, i ) );
/*?*/               AppendUndo( pUndo );
/*?*/           }
/*?*/       }
/*?*/       pNode->Insert( rStr, pPos->nContent, nInsMode );
/*N*/   }
/*N*/
/*N*/   if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SwPaM aPam( pPos->nNode, aTmp.GetCntnt(),
//STRIP001 /*?*/                    pPos->nNode, pPos->nContent.GetIndex());
//STRIP001 /*?*/        if( IsRedlineOn() )
//STRIP001 /*?*/            AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/        else
//STRIP001 /*?*/            SplitRedline( aPam );
/*N*/   }
/*N*/
/*N*/   SetModified();
/*N*/   return TRUE;
/*N*/ }

/*N*/ SwFlyFrmFmt* SwDoc::_InsNoTxtNode( const SwPosition& rPos, SwNoTxtNode* pNode,
/*N*/                                   const SfxItemSet* pFlyAttrSet,
/*N*/                                   const SfxItemSet* pGrfAttrSet,
/*N*/                                   SwFrmFmt* pFrmFmt)
/*N*/ {
/*N*/   SwFlyFrmFmt *pFmt = 0;
/*N*/   if( pNode )
/*N*/   {
/*N*/       pFmt = _MakeFlySection( rPos, *pNode, FLY_AT_CNTNT,
/*N*/                               pFlyAttrSet, pFrmFmt );
/*N*/       if( pGrfAttrSet )
/*N*/           pNode->SetAttr( *pGrfAttrSet );
/*N*/   }
/*N*/   return pFmt;
/*N*/ }

/*N*/ SwFlyFrmFmt* SwDoc::Insert( const SwPaM &rRg,
/*N*/                           const String& rGrfName,
/*N*/                           const String& rFltName,
/*N*/                           const Graphic* pGraphic,
/*N*/                           const SfxItemSet* pFlyAttrSet,
/*N*/                           const SfxItemSet* pGrfAttrSet,
/*N*/                           SwFrmFmt* pFrmFmt )
/*N*/ {
/*N*/   if( !pFrmFmt )
/*?*/       pFrmFmt = GetFrmFmtFromPool( RES_POOLFRM_GRAPHIC );
/*N*/   return _InsNoTxtNode( *rRg.GetPoint(), GetNodes().MakeGrfNode(
/*N*/                           SwNodeIndex( GetNodes().GetEndOfAutotext() ),
/*N*/                           rGrfName, rFltName, pGraphic,
/*N*/                           pDfltGrfFmtColl ),
/*N*/                           pFlyAttrSet, pGrfAttrSet, pFrmFmt );
/*N*/ }
/*N*/ SwFlyFrmFmt* SwDoc::Insert( const SwPaM &rRg, const GraphicObject& rGrfObj,
/*N*/                           const SfxItemSet* pFlyAttrSet,
/*N*/                           const SfxItemSet* pGrfAttrSet,
/*N*/                           SwFrmFmt* pFrmFmt )
/*N*/ {
/*N*/   if( !pFrmFmt )
/*?*/       pFrmFmt = GetFrmFmtFromPool( RES_POOLFRM_GRAPHIC );
/*N*/   return _InsNoTxtNode( *rRg.GetPoint(), GetNodes().MakeGrfNode(
/*N*/                           SwNodeIndex( GetNodes().GetEndOfAutotext() ),
/*N*/                           rGrfObj, pDfltGrfFmtColl ),
/*N*/                           pFlyAttrSet, pGrfAttrSet, pFrmFmt );
/*N*/ }

/*N*/ SwFlyFrmFmt* SwDoc::Insert(const SwPaM &rRg, SvInPlaceObject *pObj,
/*N*/                       const SfxItemSet* pFlyAttrSet,
/*N*/                       const SfxItemSet* pGrfAttrSet,
/*N*/                       SwFrmFmt* pFrmFmt )
/*N*/ {
/*N*/   if( !pFrmFmt )
/*N*/   {
/*N*/       USHORT nId = RES_POOLFRM_OLE;
/*N*/
/*N*/       FASTBOOL bMath = SmModuleDummy::HasID( *pObj->GetSvFactory() );
/*N*/         if ( bMath )
/*?*/           nId = RES_POOLFRM_FORMEL;
/*N*/
/*N*/       pFrmFmt = GetFrmFmtFromPool( nId );
/*N*/   }
/*N*/   return _InsNoTxtNode( *rRg.GetPoint(), GetNodes().MakeOLENode(
/*N*/                           SwNodeIndex( GetNodes().GetEndOfAutotext() ),
/*N*/                           pObj,
/*N*/                           pDfltGrfFmtColl ),
/*N*/                           pFlyAttrSet, pGrfAttrSet,
/*N*/                           pFrmFmt );
/*N*/ }

/*N*/ SwFlyFrmFmt* SwDoc::InsertOLE(const SwPaM &rRg, String& rObjName,
/*N*/                       const SfxItemSet* pFlyAttrSet,
/*N*/                       const SfxItemSet* pGrfAttrSet,
/*N*/                       SwFrmFmt* pFrmFmt )
/*N*/ {
/*N*/   if( !pFrmFmt )
/*N*/       pFrmFmt = GetFrmFmtFromPool( RES_POOLFRM_OLE );
/*N*/
/*N*/   return _InsNoTxtNode( *rRg.GetPoint(), GetNodes().MakeOLENode(
/*N*/                           SwNodeIndex( GetNodes().GetEndOfAutotext() ),
/*N*/                           rObjName,
/*N*/                           pDfltGrfFmtColl ),
/*N*/                           pFlyAttrSet, pGrfAttrSet,
/*N*/                           pFrmFmt );
/*N*/ }


//STRIP001 String SwDoc::GetCurWord( SwPaM& rPaM )
//STRIP001 {
//STRIP001  SwTxtNode *pNd = rPaM.GetNode()->GetTxtNode();
//STRIP001  if( pNd )
//STRIP001      return pNd->GetCurWord(rPaM.GetPoint()->nContent.GetIndex());
//STRIP001  return aEmptyStr;
//STRIP001 }


/*************************************************************************
|*                SwDoc::GetFldType()
|*    Beschreibung: liefert den am Doc eingerichteten Feldtypen zurueck
*************************************************************************/

/*N*/ SwFieldType *SwDoc::GetSysFldType( const USHORT eWhich ) const
/*N*/ {
/*N*/   for( register int i = 0; i < INIT_FLDTYPES; i++ )
/*N*/       if( eWhich == (*pFldTypes)[i]->Which() )
/*N*/           return (*pFldTypes)[i];
/*N*/   return 0;
/*N*/ }

//----- Macro ---------------------------------------------------------

//STRIP001 BOOL SwDoc::HasGlobalMacro( USHORT nEvent ) const
//STRIP001 {
//STRIP001  return pMacroTable->IsKeyValid(nEvent);
//STRIP001 }

//STRIP001 const SvxMacro& SwDoc::GetGlobalMacro( USHORT nEvent ) const
//STRIP001 {
//STRIP001  ASSERT(pMacroTable->IsKeyValid(nEvent), "Get fuer nicht ex. Macro");
//STRIP001  return *(pMacroTable->Get(nEvent));
//STRIP001 }

void SwDoc::SetGlobalMacro( USHORT nEvent, const SvxMacro& rMacro )
{
    SvxMacro *pMacro;
    SetModified();
    if ( 0 != (pMacro=pMacroTable->Get(nEvent)) )
    {
        delete pMacro;
        pMacroTable->Replace(nEvent, new SvxMacro(rMacro));
        return;
    }
    pMacroTable->Insert(nEvent, new SvxMacro(rMacro));
}

//STRIP001 BOOL SwDoc::DelGlobalMacro(USHORT nEvent)
//STRIP001 {
//STRIP001  SetModified();
//STRIP001  SvxMacro *pMacro = pMacroTable->Remove(nEvent);
//STRIP001  delete pMacro;
//STRIP001  return (pMacro != 0);
//STRIP001 }

/*************************************************************************
 *             void SetDocStat( const SwDocStat& rStat );
 *************************************************************************/

/*N*/ void SwDoc::SetDocStat( const SwDocStat& rStat )
/*N*/ {
/*N*/   *pDocStat = rStat;
/*N*/ }


/*M*/ sal_uInt16 SwDoc::GetPageCount() const
/*M*/ {
/*M*/     return GetRootFrm() ? GetRootFrm()->GetPageNum() : 0;
/*M*/ }

/*M*/ const Size SwDoc::GetPageSize( sal_uInt16 nPageNum ) const
/*M*/ {
/*M*/     Size aSize;
/*M*/     if( GetRootFrm() && nPageNum )
/*M*/     {
/*M*/         const SwPageFrm* pPage = static_cast<const SwPageFrm*>
/*M*/                                  (GetRootFrm()->Lower());
/*M*/         while( --nPageNum && pPage->GetNext() )
/*M*/             pPage = static_cast<const SwPageFrm*>( pPage->GetNext() );
/*M*/         if( pPage->IsEmptyPage() && pPage->GetNext() )
/*M*/             pPage = static_cast<const SwPageFrm*>( pPage->GetNext() );
/*M*/         aSize = pPage->Frm().SSize();
/*M*/     }
/*M*/     return aSize;
/*M*/ }


/*************************************************************************
 *            void UpdateDocStat( const SwDocStat& rStat );
 *************************************************************************/

/*M*/ void SwDoc::UpdateDocStat( SwDocStat& rStat )
/*M*/ {
/*M*/   if( rStat.bModified )
/*M*/   {
/*M*/       rStat.Reset();
/*M*/       rStat.nPara = 0;        // Default ist auf 1 !!
/*M*/       SwNode* pNd;
/*M*/
/*M*/       for( ULONG n = GetNodes().Count(); n; )
/*M*/           switch( ( pNd = GetNodes()[ --n ])->GetNodeType() )
/*M*/           {
/*M*/             case ND_TEXTNODE:
/*M*/                 {
/*M*/                     const String& rStr = ((SwTxtNode*)pNd)->GetTxt();
/*M*/
/*M*/                     if( rStr.Len() && pBreakIt->xBreak.is() )
/*M*/                     {
/*M*/                         SwScanner aScanner( *((SwTxtNode*)pNd), NULL,
/*M*/                                             ::com::sun::star::i18n::WordType::WORD_COUNT,
/*M*/                                             0, rStr.Len(), sal_False, sal_False );
/*M*/
/*M*/                         while ( aScanner.NextWord() )
/*M*/                         {
/*M*/                             if ( aScanner.GetLen() > 1 ||
/*M*/                                  CH_TXTATR_BREAKWORD != rStr.GetChar( aScanner.GetBegin() ) )
/*M*/                                 ++rStat.nWord;
/*M*/                         }
/*M*/                     }
/*M*/                     rStat.nChar += rStr.Len();
/*M*/                     ++rStat.nPara;
/*M*/                 }
/*M*/                 break;
/*M*/           case ND_TABLENODE:      ++rStat.nTbl;   break;
/*M*/           case ND_GRFNODE:        ++rStat.nGrf;   break;
/*M*/           case ND_OLENODE:        ++rStat.nOLE;   break;
/*M*/           case ND_SECTIONNODE:    break;
/*M*/           }
/*M*/
/*M*/       rStat.nPage     = GetRootFrm() ? GetRootFrm()->GetPageNum() : 0;
/*M*/       rStat.bModified = FALSE;
/*M*/       SetDocStat( rStat );
/*M*/       // event. Stat. Felder Updaten
/*M*/       SwFieldType *pType = GetSysFldType(RES_DOCSTATFLD);
/*M*/       pType->UpdateFlds();
/*M*/   }
/*M*/ }


// Dokument - Info

/*N*/ void SwDoc::DocInfoChgd( const SfxDocumentInfo& rInfo )
/*N*/ {
/*N*/   delete pSwgInfo;
/*N*/   pSwgInfo = new SfxDocumentInfo(rInfo);
/*N*/
/*N*/   GetSysFldType( RES_DOCINFOFLD )->UpdateFlds();
/*N*/   GetSysFldType( RES_TEMPLNAMEFLD )->UpdateFlds();
/*N*/   SetModified();
/*N*/ }

    // returne zum Namen die im Doc gesetzte Referenz
/*N*/ const SwFmtRefMark* SwDoc::GetRefMark( const String& rName ) const
/*N*/ {
/*N*/   const SfxPoolItem* pItem;
/*N*/   USHORT nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_REFMARK );
/*N*/   for( USHORT n = 0; n < nMaxItems; ++n )
/*N*/   {
/*N*/       if( 0 == (pItem = GetAttrPool().GetItem( RES_TXTATR_REFMARK, n ) ))
/*N*/           continue;
/*N*/
/*N*/       const SwFmtRefMark* pFmtRef = (SwFmtRefMark*)pItem;
/*N*/       const SwTxtRefMark* pTxtRef = pFmtRef->GetTxtRefMark();
/*N*/       if( pTxtRef && &pTxtRef->GetTxtNode().GetNodes() == &GetNodes() &&
/*N*/           rName.Equals( pFmtRef->GetRefName() ) )
/*N*/           return pFmtRef;
/*N*/   }
/*N*/   return 0;
/*N*/ }

    // returne die RefMark per Index - fuer Uno
//STRIP001 const SwFmtRefMark* SwDoc::GetRefMark( USHORT nIndex ) const
//STRIP001 {
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  const SwTxtRefMark* pTxtRef;
//STRIP001  const SwFmtRefMark* pRet = 0;
//STRIP001
//STRIP001  USHORT nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_REFMARK );
//STRIP001  USHORT nCount = 0;
//STRIP001  for( USHORT n = 0; n < nMaxItems; ++n )
//STRIP001      if( 0 != (pItem = GetAttrPool().GetItem( RES_TXTATR_REFMARK, n )) &&
//STRIP001          0 != (pTxtRef = ((SwFmtRefMark*)pItem)->GetTxtRefMark()) &&
//STRIP001          &pTxtRef->GetTxtNode().GetNodes() == &GetNodes() )
//STRIP001      {
//STRIP001          if(nCount == nIndex)
//STRIP001          {
//STRIP001              pRet = (SwFmtRefMark*)pItem;
//STRIP001              break;
//STRIP001          }
//STRIP001          nCount++;
//STRIP001      }
//STRIP001    return pRet;
//STRIP001 }

    // returne die Namen aller im Doc gesetzten Referenzen
    //JP 24.06.96: Ist der ArrayPointer 0 dann returne nur, ob im Doc. eine
    //              RefMark gesetzt ist
    // OS 25.06.96: ab jetzt wird immer die Anzahl der Referenzen returnt
/*N*/ USHORT SwDoc::GetRefMarks( SvStringsDtor* pNames ) const
/*N*/ {
/*N*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001   const SfxPoolItem* pItem;
//STRIP001  const SwTxtRefMark* pTxtRef;
//STRIP001
//STRIP001  USHORT nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_REFMARK );
//STRIP001  USHORT nCount = 0;
//STRIP001  for( USHORT n = 0; n < nMaxItems; ++n )
//STRIP001      if( 0 != (pItem = GetAttrPool().GetItem( RES_TXTATR_REFMARK, n )) &&
//STRIP001          0 != (pTxtRef = ((SwFmtRefMark*)pItem)->GetTxtRefMark()) &&
//STRIP001          &pTxtRef->GetTxtNode().GetNodes() == &GetNodes() )
//STRIP001      {
//STRIP001          if( pNames )
//STRIP001          {
//STRIP001              String* pTmp = new String( ((SwFmtRefMark*)pItem)->GetRefName() );
//STRIP001              pNames->Insert( pTmp, nCount );
//STRIP001          }
//STRIP001          nCount ++;
//STRIP001      }
//STRIP001
//STRIP001  return nCount;
/*N*/ }

/*N*/ void SwDoc::SetModified()
/*N*/ {
/*N*/   // dem Link wird der Status returnt, wie die Flags waren und werden
/*N*/   //  Bit 0:  -> alter Zustand
/*N*/   //  Bit 1:  -> neuer Zustand
/*N*/   long nCall = bModified ? 3 : 2;
/*N*/   bModified = TRUE;
/*N*/   pDocStat->bModified = TRUE;
/*N*/   if( aOle2Link.IsSet() )
/*N*/   {
/*N*/       bInCallModified = TRUE;
/*N*/       aOle2Link.Call( (void*)nCall );
/*N*/       bInCallModified = FALSE;
/*N*/   }
/*N*/
/*N*/   if( pACEWord && !pACEWord->IsDeleted() )
/*?*/       delete pACEWord, pACEWord = 0;
/*N*/ }

/*N*/ void SwDoc::ResetModified()
/*N*/ {
/*N*/   // dem Link wird der Status returnt, wie die Flags waren und werden
/*N*/   //  Bit 0:  -> alter Zustand
/*N*/   //  Bit 1:  -> neuer Zustand
/*N*/   long nCall = bModified ? 1 : 0;
/*N*/   bModified = FALSE;
/*N*/   nUndoSavePos = nUndoPos;
/*N*/   if( nCall && aOle2Link.IsSet() )
/*N*/   {
/*N*/       bInCallModified = TRUE;
/*N*/       aOle2Link.Call( (void*)nCall );
/*N*/       bInCallModified = FALSE;
/*N*/   }
/*N*/ }


/*N*/ void SwDoc::ReRead( SwPaM& rPam, const String& rGrfName,
/*N*/                   const String& rFltName, const Graphic* pGraphic,
/*N*/                   const GraphicObject* pGrafObj )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  SwGrfNode *pGrfNd;
//STRIP001  if( ( !rPam.HasMark()
//STRIP001       || rPam.GetPoint()->nNode.GetIndex() == rPam.GetMark()->nNode.GetIndex() )
//STRIP001       && 0 != ( pGrfNd = rPam.GetPoint()->nNode.GetNode().GetGrfNode() ) )
//STRIP001  {
//STRIP001      if( DoesUndo() )
//STRIP001      {
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( new SwUndoReRead( rPam, *pGrfNd ) );
//STRIP001      }
//STRIP001
//STRIP001      // Weil nicht bekannt ist, ob sich die Grafik spiegeln laesst,
//STRIP001      // immer das SpiegelungsAttribut zuruecksetzen
//STRIP001      if( RES_DONT_MIRROR_GRF != pGrfNd->GetSwAttrSet().
//STRIP001                                              GetMirrorGrf().GetValue() )
//STRIP001          pGrfNd->SetAttr( SwMirrorGrf() );
//STRIP001
//STRIP001      pGrfNd->ReRead( rGrfName, rFltName, pGraphic, pGrafObj, TRUE );
//STRIP001      SetModified();
//STRIP001  }
/*N*/ }

/*N*/ BOOL lcl_SpellAgain( const SwNodePtr& rpNd, void* pArgs )
/*N*/ {
/*N*/   SwTxtNode *pTxtNode = (SwTxtNode*)rpNd->GetTxtNode();
/*N*/   BOOL bOnlyWrong = *(BOOL*)pArgs;
/*N*/   if( pTxtNode )
/*N*/   {
/*N*/       if( bOnlyWrong )
/*N*/       {
/*N*/           if( pTxtNode->GetWrong() &&
/*N*/               pTxtNode->GetWrong()->InvalidateWrong() )
/*?*/               pTxtNode->SetWrongDirty( TRUE );
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           pTxtNode->SetWrongDirty( TRUE );
/*?*/           if( pTxtNode->GetWrong() )
/*?*/               pTxtNode->GetWrong()->SetInvalid( 0, STRING_LEN );
/*N*/       }
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
 *      SwDoc::SpellItAgainSam( BOOL bInvalid, BOOL bOnlyWrong )
 *
 * stoesst das Spelling im Idle-Handler wieder an.
 * Wird bInvalid als TRUE uebergeben, so werden zusaetzlich die WrongListen
 * an allen Nodes invalidiert und auf allen Seiten das SpellInvalid-Flag
 * gesetzt.
 * Mit bOnlyWrong kann man dann steuern, ob nur die Bereiche mit falschen
 * Woertern oder die kompletten Bereiche neu ueberprueft werden muessen.
 ************************************************************************/

/*N*/ void SwDoc::SpellItAgainSam( BOOL bInvalid, BOOL bOnlyWrong )
/*N*/ {
/*N*/   ASSERT( GetRootFrm(), "SpellAgain: Where's my RootFrm?" );
/*N*/   if( bInvalid )
/*N*/   {
/*N*/       SwPageFrm *pPage = (SwPageFrm*)GetRootFrm()->Lower();
/*N*/       while ( pPage )
/*N*/       {
/*N*/           pPage->InvalidateSpelling();
/*N*/           pPage = (SwPageFrm*)pPage->GetNext();
/*N*/       }
/*N*/       GetNodes().ForEach( lcl_SpellAgain, &bOnlyWrong );
/*N*/   }
/*N*/   GetRootFrm()->SetIdleFlags();
/*N*/ }

//STRIP001 void SwDoc::InvalidateAutoCompleteFlag()
//STRIP001 {
//STRIP001  if( GetRootFrm() )
//STRIP001  {
//STRIP001      SwPageFrm *pPage = (SwPageFrm*)GetRootFrm()->Lower();
//STRIP001      while ( pPage )
//STRIP001      {
//STRIP001          pPage->InvalidateAutoCompleteWords();
//STRIP001          pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001      }
//STRIP001      for( ULONG nNd = 1, nCnt = GetNodes().Count(); nNd < nCnt; ++nNd )
//STRIP001          GetNodes()[ nNd ]->SetAutoCompleteWordDirty( TRUE );
//STRIP001      GetRootFrm()->SetIdleFlags();
//STRIP001  }
//STRIP001 }

//STRIP001 const SwFmtINetFmt* SwDoc::FindINetAttr( const String& rName ) const
//STRIP001 {
//STRIP001  const SwFmtINetFmt* pItem;
//STRIP001  const SwTxtINetFmt* pTxtAttr;
//STRIP001  const SwTxtNode* pTxtNd;
//STRIP001  USHORT n, nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_INETFMT );
//STRIP001  for( n = 0; n < nMaxItems; ++n )
//STRIP001      if( 0 != (pItem = (SwFmtINetFmt*)GetAttrPool().GetItem(
//STRIP001          RES_TXTATR_INETFMT, n ) ) &&
//STRIP001          pItem->GetName().Equals( rName ) &&
//STRIP001          0 != ( pTxtAttr = pItem->GetTxtINetFmt()) &&
//STRIP001          0 != ( pTxtNd = pTxtAttr->GetpTxtNode() ) &&
//STRIP001          &pTxtNd->GetNodes() == &GetNodes() )
//STRIP001      {
//STRIP001          return pItem;
//STRIP001      }
//STRIP001
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SwDoc::Summary( SwDoc* pExtDoc, BYTE nLevel, BYTE nPara, BOOL bImpress )
//STRIP001 {
//STRIP001  const SwOutlineNodes& rOutNds = GetNodes().GetOutLineNds();
//STRIP001  if( pExtDoc && rOutNds.Count() )
//STRIP001  {
//STRIP001      USHORT i;
//STRIP001      ::StartProgress( STR_STATSTR_SUMMARY, 0, rOutNds.Count(), GetDocShell() );
//STRIP001      SwNodeIndex aEndOfDoc( pExtDoc->GetNodes().GetEndOfContent(), -1 );
//STRIP001      for( i = 0; i < rOutNds.Count(); ++i )
//STRIP001      {
//STRIP001          ::binfilter::SetProgressState( i, GetDocShell() );
//STRIP001          ULONG nIndex = rOutNds[ i ]->GetIndex();
//STRIP001          BYTE nLvl = ((SwTxtNode*)GetNodes()[ nIndex ])->GetTxtColl()
//STRIP001                       ->GetOutlineLevel();
//STRIP001          if( nLvl > nLevel )
//STRIP001              continue;
//STRIP001          USHORT nEndOfs = 1;
//STRIP001          BYTE nWish = nPara;
//STRIP001          ULONG nNextOutNd = i + 1 < rOutNds.Count() ?
//STRIP001              rOutNds[ i + 1 ]->GetIndex() : GetNodes().Count();
//STRIP001          BOOL bKeep = FALSE;
//STRIP001          while( ( nWish || bKeep ) && nIndex + nEndOfs < nNextOutNd &&
//STRIP001                 GetNodes()[ nIndex + nEndOfs ]->IsTxtNode() )
//STRIP001          {
//STRIP001              SwTxtNode* pTxtNode = (SwTxtNode*)GetNodes()[ nIndex+nEndOfs ];
//STRIP001              if( pTxtNode->GetTxt().Len() && nWish )
//STRIP001                  --nWish;
//STRIP001              bKeep = pTxtNode->GetSwAttrSet().GetKeep().GetValue();
//STRIP001              ++nEndOfs;
//STRIP001          }
//STRIP001
//STRIP001          SwNodeRange aRange( *rOutNds[ i ], 0, *rOutNds[ i ], nEndOfs );
//STRIP001          GetNodes()._Copy( aRange, aEndOfDoc );
//STRIP001      }
//STRIP001      const SwTxtFmtColls *pColl = pExtDoc->GetTxtFmtColls();
//STRIP001      for( i = 0; i < pColl->Count(); ++i )
//STRIP001          (*pColl)[ i ]->ResetAttr( RES_PAGEDESC, RES_BREAK );
//STRIP001      SwNodeIndex aIndx( pExtDoc->GetNodes().GetEndOfExtras() );
//STRIP001      ++aEndOfDoc;
//STRIP001      while( aIndx < aEndOfDoc )
//STRIP001      {
//STRIP001          SwNode *pNode;
//STRIP001          BOOL bDelete = FALSE;
//STRIP001          if( (pNode = &aIndx.GetNode())->IsTxtNode() )
//STRIP001          {
//STRIP001              SwTxtNode *pNd = (SwTxtNode*)pNode;
//STRIP001              if( pNd->HasSwAttrSet() )
//STRIP001                  pNd->ResetAttr( RES_PAGEDESC, RES_BREAK );
//STRIP001              if( bImpress )
//STRIP001              {
//STRIP001                  SwTxtFmtColl* pColl = pNd->GetTxtColl();
//STRIP001                  USHORT nHeadLine = pColl->GetOutlineLevel()==NO_NUMBERING ?
//STRIP001                              RES_POOLCOLL_HEADLINE2 : RES_POOLCOLL_HEADLINE1;
//STRIP001                  pColl = pExtDoc->GetTxtCollFromPool( nHeadLine );
//STRIP001                  pNd->ChgFmtColl( pColl );
//STRIP001              }
//STRIP001              if( !pNd->Len() &&
//STRIP001                  pNd->StartOfSectionIndex()+2 < pNd->EndOfSectionIndex() )
//STRIP001              {
//STRIP001                  bDelete = TRUE;
//STRIP001                  pExtDoc->GetNodes().Delete( aIndx );
//STRIP001              }
//STRIP001          }
//STRIP001          if( !bDelete )
//STRIP001              ++aIndx;
//STRIP001      }
//STRIP001      ::EndProgress( GetDocShell() );
//STRIP001  }
//STRIP001 }

    // loesche den nicht sichtbaren Content aus dem Document, wie z.B.:
    // versteckte Bereiche, versteckte Absaetze
//STRIP001 BOOL SwDoc::RemoveInvisibleContent()
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  StartUndo( UIUNDO_DELETE_INVISIBLECNTNT );
//STRIP001
//STRIP001  {
//STRIP001      SwTxtNode* pTxtNd;
//STRIP001      SwClientIter aIter( *GetSysFldType( RES_HIDDENPARAFLD ) );
//STRIP001      for( SwFmtFld* pFmtFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
//STRIP001              pFmtFld; pFmtFld = (SwFmtFld*)aIter.Next() )
//STRIP001          if( pFmtFld->GetTxtFld() &&
//STRIP001              0 != ( pTxtNd = (SwTxtNode*)pFmtFld->GetTxtFld()->GetpTxtNode() ) &&
//STRIP001              pTxtNd->GetpSwpHints() && !pTxtNd->GetpSwpHints()->IsVisible() &&
//STRIP001              &pTxtNd->GetNodes() == &GetNodes() )
//STRIP001          {
//STRIP001              bRet = TRUE;
//STRIP001              // ein versteckter Absatz -> entfernen oder Inhalt loeschen?
//STRIP001              SwPaM aPam( *pTxtNd, 0, *pTxtNd, pTxtNd->GetTxt().Len() );
//STRIP001
//STRIP001              if( 2 != pTxtNd->EndOfSectionIndex() -
//STRIP001                      pTxtNd->StartOfSectionIndex() )
//STRIP001              {
//STRIP001                  aPam.DeleteMark();
//STRIP001                  DelFullPara( aPam );
//STRIP001              }
//STRIP001              else
//STRIP001                  Delete( aPam );
//STRIP001          }
//STRIP001  }
//STRIP001
//STRIP001  {
//STRIP001      // dann noch alle versteckten Bereiche loeschen/leeren
//STRIP001      SwSectionFmts aSectFmts;
//STRIP001      SwSectionFmts& rSectFmts = GetSections();
//STRIP001      for( USHORT n = rSectFmts.Count(); n; )
//STRIP001      {
//STRIP001          SwSectionFmt* pSectFmt = rSectFmts[ --n ];
//STRIP001          SwSection* pSect = pSectFmt->GetSection();
//STRIP001          if( pSect->CalcHiddenFlag() )
//STRIP001          {
//STRIP001              SwSection* pParent = pSect, *pTmp;
//STRIP001              while( 0 != (pTmp = pParent->GetParent() ))
//STRIP001              {
//STRIP001                  if( pTmp->IsHiddenFlag() )
//STRIP001                      pSect = pTmp;
//STRIP001                  pParent = pTmp;
//STRIP001              }
//STRIP001
//STRIP001              if( USHRT_MAX == aSectFmts.GetPos( pSect->GetFmt() ) )
//STRIP001                  aSectFmts.Insert( pSect->GetFmt(), 0 );
//STRIP001          }
//STRIP001          if( pSect->GetCondition().Len() )
//STRIP001          {
//STRIP001              SwSection aSect( pSect->GetType(), pSect->GetName() );
//STRIP001              aSect = *pSect;
//STRIP001              aSect.SetCondition( aEmptyStr );
//STRIP001              aSect.SetHidden( FALSE );
//STRIP001              ChgSection( n, aSect );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( 0 != ( n = aSectFmts.Count() ))
//STRIP001      {
//STRIP001          while( n )
//STRIP001          {
//STRIP001              SwSectionFmt* pSectFmt = aSectFmts[ --n ];
//STRIP001              SwSectionNode* pSectNd = pSectFmt->GetSectionNode();
//STRIP001              if( pSectNd )
//STRIP001              {
//STRIP001                  bRet = TRUE;
//STRIP001                  SwPaM aPam( *pSectNd );
//STRIP001
//STRIP001                  if( pSectNd->FindStartNode()->StartOfSectionIndex() ==
//STRIP001                      pSectNd->GetIndex() - 1 &&
//STRIP001                      pSectNd->FindStartNode()->EndOfSectionIndex() ==
//STRIP001                      pSectNd->EndOfSectionIndex() + 1 )
//STRIP001                  {
//STRIP001                      // nur den Inhalt loeschen
//STRIP001                      SwCntntNode* pCNd = GetNodes().GoNext(
//STRIP001                                              &aPam.GetPoint()->nNode );
//STRIP001                      aPam.GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001                      aPam.SetMark();
//STRIP001                      aPam.GetPoint()->nNode = *pSectNd->EndOfSectionNode();
//STRIP001                      pCNd = GetNodes().GoPrevious(
//STRIP001                                              &aPam.GetPoint()->nNode );
//STRIP001                      aPam.GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001
//STRIP001                      Delete( aPam );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      // die gesamte Section loeschen
//STRIP001                      aPam.SetMark();
//STRIP001                      aPam.GetPoint()->nNode = *pSectNd->EndOfSectionNode();
//STRIP001                      DelFullPara( aPam );
//STRIP001                  }
//STRIP001
//STRIP001              }
//STRIP001          }
//STRIP001          aSectFmts.Remove( 0, aSectFmts.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001      SetModified();
//STRIP001  EndUndo( UIUNDO_DELETE_INVISIBLECNTNT );
//STRIP001  return bRet;
//STRIP001 }

    // embedded alle lokalen Links (Bereiche/Grafiken)
//STRIP001 BOOL SwDoc::EmbedAllLinks()
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SvxLinkManager& rLnkMgr = GetLinkManager();
//STRIP001  const ::so3::SvBaseLinks& rLnks = rLnkMgr.GetLinks();
//STRIP001  if( rLnks.Count() )
//STRIP001  {
//STRIP001      BOOL bDoesUndo = DoesUndo();
//STRIP001      DoUndo( FALSE );
//STRIP001
//STRIP001      for( USHORT n = 0; n < rLnks.Count(); ++n )
//STRIP001      {
//STRIP001          ::so3::SvBaseLink* pLnk = &(*rLnks[ n ]);
//STRIP001          if( pLnk &&
//STRIP001              ( OBJECT_CLIENT_GRF == pLnk->GetObjType() ||
//STRIP001                OBJECT_CLIENT_FILE == pLnk->GetObjType() ) &&
//STRIP001              pLnk->ISA( SwBaseLink ) )
//STRIP001          {
//STRIP001              ::so3::SvBaseLinkRef xLink = pLnk;
//STRIP001              USHORT nCount = rLnks.Count();
//STRIP001
//STRIP001              String sFName;
//STRIP001              rLnkMgr.GetDisplayNames( xLink, 0, &sFName, 0, 0 );
//STRIP001
//STRIP001              INetURLObject aURL( sFName );
//STRIP001              if( INET_PROT_FILE == aURL.GetProtocol() ||
//STRIP001                  INET_PROT_CID == aURL.GetProtocol() )
//STRIP001              {
//STRIP001                  // dem Link sagen, das er aufgeloest wird!
//STRIP001                  xLink->Closed();
//STRIP001
//STRIP001                  // falls einer vergessen hat sich auszutragen
//STRIP001                  if( xLink.Is() )
//STRIP001                      rLnkMgr.Remove( xLink );
//STRIP001
//STRIP001                  if( nCount != rLnks.Count() + 1 )
//STRIP001                      n = 0;      // wieder von vorne anfangen, es wurden
//STRIP001                                  // mehrere Links entfernt
//STRIP001                  bRet = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      DelAllUndoObj();
//STRIP001      DoUndo( bDoesUndo );
//STRIP001      SetModified();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwDoc::IsInsTblFormatNum() const
//STRIP001 {
//STRIP001  return SW_MOD()->IsInsTblFormatNum(IsHTMLMode());
//STRIP001 }

//STRIP001 BOOL SwDoc::IsInsTblChangeNumFormat() const
//STRIP001 {
//STRIP001  return SW_MOD()->IsInsTblChangeNumFormat(IsHTMLMode());
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwDoc::IsInsTblAlignNum() const
//STRIP001 {
//STRIP001  return SW_MOD()->IsInsTblAlignNum(IsHTMLMode());
//STRIP001 }


/*N*/ USHORT SwDoc::GetLinkUpdMode() const
/*N*/ {
/*N*/   USHORT nRet = nLinkUpdMode;
/*N*/   if( GLOBALSETTING == nRet )
/*N*/       nRet = SW_MOD()->GetLinkUpdMode(IsHTMLMode());
/*N*/   return nRet;
/*N*/ }

/*N*/ USHORT SwDoc::GetFldUpdateFlags() const
/*N*/ {
/*N*/   USHORT nRet = nFldUpdMode;
/*N*/   if( AUTOUPD_GLOBALSETTING == nRet )
/*N*/       nRet = SW_MOD()->GetFldUpdateFlags(IsHTMLMode());
/*N*/   return nRet;
/*N*/ }

        // setze das InsertDB als Tabelle Undo auf:
//STRIP001 void SwDoc::AppendUndoForInsertFromDB( const SwPaM& rPam, BOOL bIsTable )
//STRIP001 {
//STRIP001  if( bIsTable )
//STRIP001  {
//STRIP001      const SwTableNode* pTblNd = rPam.GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001      if( pTblNd )
//STRIP001      {
//STRIP001          SwUndoCpyTbl* pUndo = new SwUndoCpyTbl;
//STRIP001          pUndo->SetTableSttIdx( pTblNd->GetIndex() );
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001  }
//STRIP001  else if( rPam.HasMark() )
//STRIP001  {
//STRIP001      SwUndoCpyDoc* pUndo = new SwUndoCpyDoc( rPam );
//STRIP001      pUndo->SetInsertRange( rPam, FALSE );
//STRIP001      AppendUndo( pUndo );
//STRIP001  }
//STRIP001 }



}
