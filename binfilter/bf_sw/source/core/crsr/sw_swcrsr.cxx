/*************************************************************************
 *
 *  $RCSfile: sw_swcrsr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:49 $
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

#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_CHARTYPE_HDL
#include <com/sun/star/i18n/CharType.hdl>
#endif


#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _SVTOOLS_CTLOPTIONS_HXX
#include <svtools/ctloptions.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _SWTBLFMT_HXX //autogen
#include <swtblfmt.hxx>
#endif
#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _UNOCRSR_HXX
#include <unocrsr.hxx>
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
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>
#endif
#ifndef _CRSTATE_HXX
#include <crstate.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>           // ...Percent()
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>          // ResId fuer Statusleiste
#endif
namespace binfilter {

using namespace ::com::sun::star::i18n;

static const USHORT coSrchRplcThreshold = 60000;

struct _PercentHdl
{
    SwDocShell* pDSh;
    ULONG nActPos;
    BOOL bBack, bNodeIdx;

    _PercentHdl( ULONG nStt, ULONG nEnd, SwDocShell* pSh )
        : pDSh( pSh )
    {
        nActPos = nStt;
        if( 0 != ( bBack = (nStt > nEnd )) )
        {
            ULONG n = nStt; nStt = nEnd; nEnd = n;
        }
        ::binfilter::StartProgress( STR_STATSTR_SEARCH, nStt, nEnd, 0 );
    }

    _PercentHdl( const SwPaM& rPam )
        : pDSh( (SwDocShell*)rPam.GetDoc()->GetDocShell() )
    {
        ULONG nStt, nEnd;
        if( rPam.GetPoint()->nNode == rPam.GetMark()->nNode )
        {
            bNodeIdx = FALSE;
            nStt = rPam.GetMark()->nContent.GetIndex();
            nEnd = rPam.GetPoint()->nContent.GetIndex();
        }
        else
        {
            nStt = rPam.GetMark()->nNode.GetIndex();
            nEnd = rPam.GetPoint()->nNode.GetIndex();
        }
        nActPos = nStt;
        if( 0 != ( bBack = (nStt > nEnd )) )
        {
            ULONG n = nStt; nStt = nEnd; nEnd = n;
        }
        ::binfilter::StartProgress( STR_STATSTR_SEARCH, nStt, nEnd, pDSh );
    }

    ~_PercentHdl()                      { ::binfilter::EndProgress( pDSh ); }

    void NextPos( ULONG nPos ) const
    { ::binfilter::SetProgressState( bBack ? nActPos - nPos : nPos, pDSh ); }

    void NextPos( SwPosition& rPos ) const
        {
            ULONG nPos;
            if( bNodeIdx )
                nPos = rPos.nNode.GetIndex();
            else
                nPos = rPos.nContent.GetIndex();
            ::binfilter::SetProgressState( bBack ? nActPos - nPos : nPos, pDSh );
        }
};

/*N*/ SwCursor::SwCursor( const SwPosition &rPos, SwPaM* pRing )
/*N*/       : SwPaM( rPos, pRing ), pSavePos( 0 ), nCursorBidiLevel( 0 )
/*N*/ {
/*N*/ }

//STRIP001 SwCursor::SwCursor( SwCursor& rCpy )
//STRIP001     : SwPaM( rCpy ), pSavePos( 0 ), nCursorBidiLevel( rCpy.nCursorBidiLevel )
//STRIP001 {
//STRIP001 }

/*N*/ SwCursor::~SwCursor()
/*N*/ {
/*N*/   while( pSavePos )
/*N*/   {
/*?*/       _SwCursor_SavePos* pNext = pSavePos->pNext;
/*?*/       delete pSavePos;
/*?*/       pSavePos = pNext;
/*N*/   }
/*N*/ }

//STRIP001 SwCursor* SwCursor::Create( SwPaM* pRing ) const
//STRIP001 {
//STRIP001  return new SwCursor( *GetPoint(), pRing );
//STRIP001 }

/*N*/ SwCursor::operator SwTableCursor* ()      { return 0; }
/*N*/ SwCursor::operator SwShellCrsr* ()            { return 0; }
/*N*/ SwCursor::operator SwShellTableCrsr* ()       { return 0; }
/*N*/ SwCursor::operator SwUnoCrsr* ()          { return 0; }
/*N*/ SwCursor::operator SwUnoTableCrsr* ()     { return 0; }


// Sicher die aktuelle Position, damit ggfs. auf diese zurueck
// gefallen werden kann. Die SavePos Objekte werden als Stack verwaltet,
// damit das auch alles bei verschachtelten Aufrufen funktioniert.
// Das CreateNewSavePos ist virtual, damit abgeleitete Klassen vom Cursor
// gegebenenfalls eigene SaveObjecte anlegen und in den virtuellen
// Check-Routinen verwenden koennen.

/*N*/ void SwCursor::SaveState()
/*N*/ {
/*N*/   _SwCursor_SavePos* pNew = CreateNewSavePos();
/*N*/   pNew->pNext = pSavePos;
/*N*/   pSavePos = pNew;
/*N*/ }

/*N*/ void SwCursor::RestoreState()
/*N*/ {
/*N*/   _SwCursor_SavePos* pDel = pSavePos;
/*N*/   pSavePos = pSavePos->pNext;
/*N*/   delete pDel;
/*N*/ }

/*N*/ _SwCursor_SavePos* SwCursor::CreateNewSavePos() const
/*N*/ {
/*N*/   return new _SwCursor_SavePos( *this );
/*N*/ }

// stelle fest, ob sich der Point ausserhalb des Content-Bereichs
// vom Nodes-Array befindet
//STRIP001 FASTBOOL SwCursor::IsNoCntnt() const
//STRIP001 {
//STRIP001  return GetPoint()->nNode.GetIndex() <
//STRIP001          GetDoc()->GetNodes().GetEndOfExtras().GetIndex();
//STRIP001 }


/*N*/ FASTBOOL SwCursor::IsSelOvr( int eFlags )
/*N*/ {
/*N*/   SwTableCursor* pTblCrsr = *this;
/*N*/   SwDoc* pDoc = GetDoc();
/*N*/   SwNodes& rNds = pDoc->GetNodes();
/*N*/
/*N*/   BOOL bSkipOverHiddenSections, bSkipOverProtectSections;
/*N*/   SwUnoCrsr* pUnoCrsr = *this;
/*N*/   if( pUnoCrsr )
/*N*/   {
/*N*/       bSkipOverHiddenSections = pUnoCrsr->IsSkipOverHiddenSections();
/*N*/       bSkipOverProtectSections = pUnoCrsr->IsSkipOverProtectSections();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       bSkipOverHiddenSections = TRUE;
/*?*/       bSkipOverProtectSections = !IsReadOnlyAvailable();
/*N*/   }

    // Bereiche vom Nodes-Array ueberpruefen
/*N*/   if( (SELOVER_CHECKNODESSECTION & eFlags) && pTblCrsr && HasMark() )
/*N*/   {
/*?*/       SwNodeIndex aOldPos( rNds, pSavePos->nNode );
/*?*/       if( !CheckNodesRange( aOldPos, GetPoint()->nNode, TRUE ))
/*?*/       {
/*?*/           GetPoint()->nNode = aOldPos;
/*?*/           GetPoint()->nContent.Assign( GetCntntNode(), pSavePos->nCntnt );
/*?*/           return TRUE;
/*?*/       }
/*N*/   }

// neu: Bereiche ueberpruefen
// Anfang
/*N*/   if( pSavePos->nNode != GetPoint()->nNode.GetIndex() &&
/*N*/       //JP 28.10.97: Bug 45129 - im UI-ReadOnly ist alles erlaubt
/*N*/       ( !pDoc->GetDocShell() || !pDoc->GetDocShell()->IsReadOnlyUI() ))
/*N*/   {
/*N*/       // teste doch mal die neuen Sections:
/*N*/       SwNodeIndex& rPtIdx = GetPoint()->nNode;
/*N*/       const SwSectionNode* pSectNd = rPtIdx.GetNode().FindSectionNode();
/*N*/       if( pSectNd &&
/*N*/           ((bSkipOverHiddenSections && pSectNd->GetSection().IsHiddenFlag() ) ||
/*N*/            (bSkipOverProtectSections && pSectNd->GetSection().IsProtectFlag() )))
/*N*/       {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001       if( 0 == ( SELOVER_CHANGEPOS & eFlags ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // dann wars das schon
//STRIP001 /*?*/                RestoreSavePos();
//STRIP001 /*?*/                return TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // dann setze den Cursor auf die neue Position:
//STRIP001 /*?*/            SwNodeIndex aIdx( rPtIdx );
//STRIP001 /*?*/            xub_StrLen nCntntPos = pSavePos->nCntnt;
//STRIP001 /*?*/            int bGoNxt = pSavePos->nNode < rPtIdx.GetIndex();
//STRIP001 /*?*/            SwCntntNode* pCNd = bGoNxt
//STRIP001 /*?*/                    ? rNds.GoNextSection( &rPtIdx, bSkipOverHiddenSections, bSkipOverProtectSections)
//STRIP001 /*?*/                    : rNds.GoPrevSection( &rPtIdx, bSkipOverHiddenSections, bSkipOverProtectSections);
//STRIP001 /*?*/            if( !pCNd && ( SELOVER_ENABLEREVDIREKTION & eFlags ))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                bGoNxt = !bGoNxt;
//STRIP001 /*?*/                pCNd = bGoNxt ? rNds.GoNextSection( &rPtIdx, bSkipOverHiddenSections, bSkipOverProtectSections)
//STRIP001 /*?*/                              : rNds.GoPrevSection( &rPtIdx, bSkipOverHiddenSections, bSkipOverProtectSections);
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            int bIsValidPos = 0 != pCNd;
//STRIP001 /*?*/            FASTBOOL bValidNodesRange = bIsValidPos &&
//STRIP001 /*?*/                                    ::CheckNodesRange( rPtIdx, aIdx, TRUE );
//STRIP001 /*?*/            if( !bValidNodesRange )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rPtIdx = pSavePos->nNode;
//STRIP001 /*?*/                if( 0 == ( pCNd = rPtIdx.GetNode().GetCntntNode() ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    bIsValidPos = FALSE;
//STRIP001 /*?*/                    nCntntPos = 0;
//STRIP001 /*?*/                    rPtIdx = aIdx;
//STRIP001 /*?*/                    if( 0 == ( pCNd = rPtIdx.GetNode().GetCntntNode() ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // dann auf den Anfang vom Doc
//STRIP001 /*?*/                        rPtIdx = rNds.GetEndOfExtras();
//STRIP001 /*?*/                        pCNd = rNds.GoNext( &rPtIdx );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // ContentIndex noch anmelden:
//STRIP001 /*?*/            xub_StrLen nTmpPos = bIsValidPos ? (bGoNxt ? 0 : pCNd->Len()) : nCntntPos;
//STRIP001 /*?*/            GetPoint()->nContent.Assign( pCNd, nTmpPos );
//STRIP001 /*?*/            if( !bIsValidPos || !bValidNodesRange ||
//STRIP001 /*?*/                // sollten wir in einer Tabelle gelandet sein?
//STRIP001 /*?*/                IsInProtectTable( TRUE ) )
//STRIP001 /*?*/                return TRUE;
/*N*/       }

        // oder sollte eine geschuetzte Section innerhalb der Selektion liegen?
/*N*/       if( HasMark() && bSkipOverProtectSections)
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ULONG nSttIdx = GetMark()->nNode.GetIndex(),
//STRIP001 /*?*/                  nEndIdx = GetPoint()->nNode.GetIndex();
//STRIP001 /*?*/            if( nEndIdx <= nSttIdx )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ULONG nTmp = nSttIdx;
//STRIP001 /*?*/                nSttIdx = nEndIdx;
//STRIP001 /*?*/                nEndIdx = nTmp;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            const SwSectionFmts& rFmts = pDoc->GetSections();
//STRIP001 /*?*/            for( USHORT n = 0; n < rFmts.Count(); ++n )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                const SwSectionFmt* pFmt = rFmts[n];
//STRIP001 /*?*/                const SvxProtectItem& rProtect = pFmt->GetProtect();
//STRIP001 /*?*/                if( rProtect.IsCntntProtected() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    const SwFmtCntnt& rCntnt = pFmt->GetCntnt(FALSE);
//STRIP001 /*?*/                    ASSERT( rCntnt.GetCntntIdx(), "wo ist der SectionNode?" );
//STRIP001 /*?*/                    ULONG nIdx = rCntnt.GetCntntIdx()->GetIndex();
//STRIP001 /*?*/                    if( nSttIdx <= nIdx && nEndIdx >= nIdx )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // ist es keine gelinkte Section, dann kann sie auch
//STRIP001 /*?*/                        // nicht mitselektiert werden
//STRIP001 /*?*/                        const SwSection& rSect = *pFmt->GetSection();
//STRIP001 /*?*/                        if( CONTENT_SECTION == rSect.GetType() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            RestoreSavePos();
//STRIP001 /*?*/                            return TRUE;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*?*/
/*N*/   }
// Ende
// neu: Bereiche ueberpruefen

/*N*/   const SwNode* pNd = &GetPoint()->nNode.GetNode();
/*N*/   if( pNd->IsCntntNode() && 0 == (SwUnoCrsr*)*this )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwCntntFrm* pFrm = ((SwCntntNode*)pNd)->GetFrm();
//STRIP001 /*?*/        if( pFrm && pFrm->IsValid() && 0 == pFrm->Frm().Height() &&
//STRIP001 /*?*/            0 != ( SELOVER_CHANGEPOS & eFlags ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // skip to the next / prev valida paragraph with a layout
//STRIP001 /*?*/            SwNodeIndex& rPtIdx = GetPoint()->nNode;
//STRIP001 /*?*/            int bGoNxt = pSavePos->nNode < rPtIdx.GetIndex();
//STRIP001 /*?*/            while( 0 != ( pFrm = ( bGoNxt ? pFrm->GetNextCntntFrm()
//STRIP001 /*?*/                                          : pFrm->GetPrevCntntFrm() )) &&
//STRIP001 /*?*/                    0 == pFrm->Frm().Height() )
//STRIP001 /*?*/                ;
//STRIP001 /*?*/
//STRIP001 /*?*/            SwCntntNode* pCNd;
//STRIP001 /*?*/            if( pFrm && 0 != (pCNd = (SwCntntNode*)pFrm->GetNode()) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // set this cntntNode as new position
//STRIP001 /*?*/                rPtIdx = *pCNd;
//STRIP001                 pNd = pCNd;
//STRIP001 /*?*/
//STRIP001 /*?*/                // ContentIndex noch anmelden:
//STRIP001 /*?*/                xub_StrLen nTmpPos = bGoNxt ? 0 : pCNd->Len();
//STRIP001 /*?*/                GetPoint()->nContent.Assign( pCNd, nTmpPos );
//STRIP001
//STRIP001 /*?*/                    // sollten wir in einer Tabelle gelandet sein?
//STRIP001 /*?*/                if( IsInProtectTable( TRUE ) )
//STRIP001 /*?*/                    pFrm = 0;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( !pFrm )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            DeleteMark();
//STRIP001 /*?*/            RestoreSavePos();
//STRIP001 /*?*/            return TRUE;        // ohne Frames geht gar nichts!
//STRIP001 /*?*/        }
/*N*/   }

    // darf der Cursor in geschuetzen "Nodes" stehen?
/*N*/   if( 0 == ( SELOVER_CHANGEPOS & eFlags ) && !IsAtValidPos() )
/*N*/   {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   DeleteMark();
//STRIP001 /*?*/        RestoreSavePos();
//STRIP001 /*?*/        return TRUE;
/*N*/   }

/*N*/   if( !HasMark() )
/*N*/       return FALSE;
/*N*/
/*N*/   //JP 19.08.98: teste mal auf ungueltige Selektion - sprich ueber
/*N*/   //              GrundSections:
/*N*/   if( !::binfilter::CheckNodesRange( GetMark()->nNode, GetPoint()->nNode, TRUE ))
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 DeleteMark();
//STRIP001 /*?*/        RestoreSavePos();
//STRIP001 /*?*/        return TRUE;        // ohne Frames geht gar nichts!
/*N*/   }

/*N*/   const SwTableNode* pPtNd = pNd->FindTableNode();

/*N*/   if( (pNd = &GetMark()->nNode.GetNode())->IsCntntNode() &&
/*N*/       !((SwCntntNode*)pNd)->GetFrm() && 0 == (SwUnoCrsr*)*this )
/*N*/   {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   DeleteMark();
//STRIP001 /*?*/        RestoreSavePos();
//STRIP001 /*?*/        return TRUE;        // ohne Frames geht gar nichts!
/*N*/   }

/*N*/   const SwTableNode* pMrkNd = pNd->FindTableNode();
/*N*/
/*N*/   // beide in keinem oder beide im gleichen TableNode
/*N*/   if( ( !pMrkNd && !pPtNd ) || pPtNd == pMrkNd )
/*N*/       return FALSE;

    // in unterschiedlichen Tabellen oder nur Mark in der Tabelle
/*?*/   if( ( pPtNd && pMrkNd ) || pMrkNd )
/*?*/   {                       // dann lasse das nicht zu, alte Pos zurueck
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   RestoreSavePos();
//STRIP001 /*?*/        // Crsr bleibt an der alten Position
//STRIP001 /*?*/        return TRUE;
/*?*/   }

    // ACHTUNG: dieses kann nicht im TableMode geschehen !!
/*?*/   if( pPtNd )     // nur Point in Tabelle, dann gehe hinter/vor diese
/*?*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( SELOVER_CHANGEPOS & eFlags )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            FASTBOOL bSelTop = GetPoint()->nNode.GetIndex() <
//STRIP001 /*?*/                    (( SELOVER_TOGGLE & eFlags ) ? pSavePos->nNode
//STRIP001 /*?*/                                                 : GetMark()->nNode.GetIndex());
//STRIP001 /*?*/
//STRIP001 /*?*/            do {
//STRIP001 /*?*/                // in Schleife fuer Tabelle hinter Tabelle
//STRIP001 /*?*/                ULONG nSEIdx = pPtNd->EndOfSectionIndex();
//STRIP001 /*?*/                ULONG nSttEndTbl = nSEIdx + 1; // dflt. Sel. nach unten
//STRIP001 /*?*/
//STRIP001 /*?*/                if( bSelTop )                               // Sel. nach oben
//STRIP001 /*?*/                    nSttEndTbl = rNds[ nSEIdx ]->StartOfSectionIndex() - 1;
//STRIP001 /*?*/
//STRIP001 /*?*/                GetPoint()->nNode = nSttEndTbl;
//STRIP001 /*?*/                const SwNode* pNd = GetNode();
//STRIP001
//STRIP001 /*?*/                if( pNd->IsSectionNode() || ( pNd->IsEndNode() &&
//STRIP001 /*?*/                    pNd->FindStartNode()->IsSectionNode() ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // die lassen wir zu:
//STRIP001 /*?*/                    pNd = bSelTop
//STRIP001 /*?*/                        ? rNds.GoPrevSection( &GetPoint()->nNode,TRUE,FALSE )
//STRIP001 /*?*/                        : rNds.GoNextSection( &GetPoint()->nNode,TRUE,FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/                     /* #i12312# Handle failure of Go{Prev|Next}Section */
//STRIP001 /*?*/                     if ( 0 == pNd)
//STRIP001 /*?*/                         break;
//STRIP001
//STRIP001 /*?*/                    if( 0 != ( pPtNd = pNd->FindTableNode() ))
//STRIP001 /*?*/                        continue;
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if( pNd->IsCntntNode() &&       // ist es ein ContentNode ??
//STRIP001 /*?*/                    ::CheckNodesRange( GetMark()->nNode,
//STRIP001 /*?*/                                       GetPoint()->nNode, TRUE ))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwCntntNode* pCNd = (SwCntntNode*)pNd;
//STRIP001 /*?*/                    xub_StrLen nTmpPos = bSelTop ? pCNd->Len() : 0;
//STRIP001 /*?*/                    GetPoint()->nContent.Assign( pCNd, nTmpPos );
//STRIP001 /*?*/                    return FALSE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if( bSelTop
//STRIP001 /*?*/                    ? ( !pNd->IsEndNode() || 0 == ( pPtNd = pNd->FindTableNode() ))
//STRIP001 /*?*/                    : 0 == ( pPtNd = pNd->GetTableNode() ))
//STRIP001 /*?*/                    break;
//STRIP001 /*?*/            } while( TRUE );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // dann verbleibe auf der alten Position
//STRIP001 /*?*/        RestoreSavePos();
//STRIP001 /*?*/        return TRUE;        // Crsr bleibt an der alten Position
/*?*/   }
/*?*/   return FALSE;       // was bleibt noch ??
/*N*/ }

#if defined( UNX ) || defined( MAC )
#define IDX     (*pCellStt)
#else
#define IDX     aCellStt
#endif


/*N*/ FASTBOOL SwCursor::IsInProtectTable( FASTBOOL bMove, FASTBOOL bChgCrsr )
/*N*/ {
/*N*/   // stehe ich in einer Tabelle ??
/*N*/   SwDoc* pDoc = GetDoc();
/*N*/   SwCntntNode* pCNd = GetCntntNode();
/*N*/   if( !pCNd || pSavePos->nNode == GetPoint()->nNode.GetIndex() ||
/*N*/       !pCNd->FindTableNode() ||
/*N*/       !pCNd->IsProtect() ||
/*N*/       IsReadOnlyAvailable() )
/*N*/       return FALSE;

/*?*/   if( !bMove )
/*?*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( bChgCrsr )
//STRIP001 /*?*/            // dann verbleibe auf der alten Position
//STRIP001 /*?*/            RestoreSavePos();
//STRIP001 /*?*/        return TRUE;        // Crsr bleibt an der alten Position
/*?*/   }
/*?*/
/*?*/   // wir stehen in einer geschuetzten TabellenZelle
/*?*/   // von Oben nach Unten Traveln ?
/*?*/   if( pSavePos->nNode < GetPoint()->nNode.GetIndex() )
/*?*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // suche die naechste "gueltige" Box
/*?*/
//STRIP001 /*?*/        // folgt nach dem EndNode der Zelle ein weiterer StartNode, dann
//STRIP001 /*?*/        // gibt es auch eine naechste Zelle
//STRIP001 /*?*/ #if defined( UNX ) || defined( MAC )
//STRIP001 /*?*/        SwNodeIndex* pCellStt = new SwNodeIndex( *GetNode()->
//STRIP001 /*?*/                        FindTableBoxStartNode()->EndOfSectionNode(), 1 );
//STRIP001 /*?*/ #else
//STRIP001 /*?*/        SwNodeIndex aCellStt( *GetNode()->FindTableBoxStartNode()->EndOfSectionNode(), 1 );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/        FASTBOOL bProt = TRUE;
//STRIP001 /*?*/ GoNextCell:
//STRIP001 /*?*/        do {
//STRIP001 /*?*/            if( !IDX.GetNode().IsStartNode() )
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            IDX++;
//STRIP001 /*?*/            if( 0 == ( pCNd = IDX.GetNode().GetCntntNode() ))
//STRIP001 /*?*/                pCNd = IDX.GetNodes().GoNext( &IDX );
//STRIP001 /*?*/            if( 0 == ( bProt = pCNd->IsProtect() ))
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            IDX.Assign( *pCNd->FindTableBoxStartNode()->EndOfSectionNode(), 1 );
//STRIP001 /*?*/        } while( bProt );
//STRIP001 /*?*/
//STRIP001 /*?*/ SetNextCrsr:
//STRIP001 /*?*/        if( !bProt )        // eine freie Zelle gefunden
//STRIP001 /*?*/        {
//STRIP001 /*?*/            GetPoint()->nNode = IDX;
//STRIP001 /*?*/ #if defined( UNX ) || defined( MAC )
//STRIP001 /*?*/            delete pCellStt;
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/            SwCntntNode* pCNd = GetCntntNode();
//STRIP001 /*?*/            if( pCNd )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001 /*?*/                return FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            return IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        // am Ende der Tabelle, also setze hinter diese
//STRIP001 /*?*/        IDX++;     // auf den naechsten Node
//STRIP001 /*?*/        SwNode* pNd;
//STRIP001 /*?*/        if( ( pNd = &IDX.GetNode())->IsEndNode() || HasMark())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // Tabelle allein in einem FlyFrame oder SSelection,
//STRIP001 /*?*/            // dann verbleibe auf der alten Position
//STRIP001 /*?*/            if( bChgCrsr )
//STRIP001 /*?*/                RestoreSavePos();
//STRIP001 /*?*/ #if defined( UNX ) || defined( MAC )
//STRIP001 /*?*/            delete pCellStt;
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/            return TRUE;        // Crsr bleibt an der alten Position
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if( pNd->IsTableNode() && IDX++ )
//STRIP001 /*?*/            goto GoNextCell;
//STRIP001 /*?*/
//STRIP001 /*?*/        bProt = FALSE;      // Index steht jetzt auf einem ContentNode
//STRIP001 /*?*/        goto SetNextCrsr;
/*?*/   }
/*?*/
/*?*/   // suche die vorherige "gueltige" Box
/*?*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // liegt vor dem StartNode der Zelle ein weiterer EndNode, dann
/*?*/       // gibt es auch eine vorherige Zelle
//STRIP001 /*?*/ #if defined( UNX ) || defined( MAC )
//STRIP001 /*?*/        SwNodeIndex* pCellStt = new SwNodeIndex(
//STRIP001 /*?*/                    *GetNode()->FindTableBoxStartNode(), -1 );
//STRIP001 /*?*/ #else
//STRIP001 /*?*/        SwNodeIndex aCellStt( *GetNode()->FindTableBoxStartNode(), -1 );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/        SwNode* pNd;
//STRIP001 /*?*/        FASTBOOL bProt = TRUE;
//STRIP001 /*?*/ GoPrevCell:
//STRIP001 /*?*/        do {
//STRIP001 /*?*/            if( !( pNd = &IDX.GetNode())->IsEndNode() )
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            IDX.Assign( *pNd->StartOfSectionNode(), +1 );
//STRIP001 /*?*/            if( 0 == ( pCNd = IDX.GetNode().GetCntntNode() ))
//STRIP001 /*?*/                pCNd = pNd->GetNodes().GoNext( &IDX );
//STRIP001 /*?*/            if( 0 == ( bProt = pCNd->IsProtect() ))
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            IDX.Assign( *pNd->FindTableBoxStartNode(), -1 );
//STRIP001 /*?*/        } while( bProt );
//STRIP001 /*?*/
//STRIP001 /*?*/ SetPrevCrsr:
//STRIP001 /*?*/        if( !bProt )        // eine freie Zelle gefunden
//STRIP001 /*?*/        {
//STRIP001 /*?*/            GetPoint()->nNode = IDX;
//STRIP001 /*?*/ #if defined( UNX ) || defined( MAC )
//STRIP001 /*?*/            delete pCellStt;
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/            SwCntntNode* pCNd = GetCntntNode();
//STRIP001 /*?*/            if( pCNd )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001 /*?*/                return FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            return IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        // am Start der Tabelle, also setze vor diese
//STRIP001 /*?*/        IDX--;     // auf den naechsten Node
//STRIP001 /*?*/        if( ( pNd = &IDX.GetNode())->IsStartNode() || HasMark() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // Tabelle allein in einem FlyFrame oder Selektion,
//STRIP001 /*?*/            // dann verbleibe auf der alten Position
//STRIP001 /*?*/            if( bChgCrsr )
//STRIP001 /*?*/                RestoreSavePos();
//STRIP001 /*?*/ #if defined( UNX ) || defined( MAC )
//STRIP001 /*?*/            delete pCellStt;
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/            return TRUE;        // Crsr bleibt an der alten Position
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if( pNd->StartOfSectionNode()->IsTableNode() && IDX-- )
//STRIP001 /*?*/            goto GoPrevCell;
//STRIP001 /*?*/
//STRIP001 /*?*/        bProt = FALSE;      // Index steht jetzt auf einem ContentNode
//STRIP001 /*?*/        goto SetPrevCrsr;
/*?*/   }
/*?*/
/*?*/   ASSERT( FALSE, "sollte nie erreicht werden oder??" );
/*?*/   return  FALSE;
/*N*/ }

// TRUE: an die Position kann der Cursor gesetzt werden
/*N*/ FASTBOOL SwCursor::IsAtValidPos( BOOL bPoint ) const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001     const SwDoc* pDoc = GetDoc();
//STRIP001  const SwPosition* pPos = bPoint ? GetPoint() : GetMark();
//STRIP001  const SwNode* pNd = &pPos->nNode.GetNode();
//STRIP001
//STRIP001  if( pNd->IsCntntNode() && !((SwCntntNode*)pNd)->GetFrm() &&
//STRIP001      0 == (const SwUnoCrsr*)*this )
//STRIP001      return FALSE;
//STRIP001
//STRIP001      //JP 28.10.97: Bug 45129 - im UI-ReadOnly ist alles erlaubt
//STRIP001  if( !pDoc->GetDocShell() || !pDoc->GetDocShell()->IsReadOnlyUI() )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  BOOL bCrsrInReadOnly = IsReadOnlyAvailable();
//STRIP001  if( !bCrsrInReadOnly && pNd->IsProtect() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwSectionNode* pSectNd = pNd->FindSectionNode();
//STRIP001  if( pSectNd && (pSectNd->GetSection().IsHiddenFlag() ||
//STRIP001                  ( !bCrsrInReadOnly && pSectNd->GetSection().IsProtectFlag() )))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  return TRUE;
/*N*/ }

/*N*/ void SwCursor::SaveTblBoxCntnt( const SwPosition* )   {}

// setze den SRange fuer das Suchen im Dokument
//STRIP001 SwMoveFnCollection* SwCursor::MakeFindRange( SwDocPositions nStart,
//STRIP001                              SwDocPositions nEnd, SwPaM* pRange ) const
//STRIP001 {
//STRIP001  pRange->SetMark();
//STRIP001  FillFindPos( nStart, *pRange->GetMark() );
//STRIP001  FillFindPos( nEnd, *pRange->GetPoint() );
//STRIP001
//STRIP001  // bestimme die Richtung, in der zu suchen ist
//STRIP001  // ( GetPoint > GetMark -> vorwaerts, sonst rueckwaerts )
//STRIP001  return ( DOCPOS_START == nStart || DOCPOS_OTHERSTART == nStart ||
//STRIP001            (DOCPOS_CURR == nStart &&
//STRIP001              (DOCPOS_END == nEnd || DOCPOS_OTHEREND == nEnd ) ))
//STRIP001              ? fnMoveForward : fnMoveBackward;
//STRIP001 }


//STRIP001 ULONG lcl_FindSelection( SwFindParas& rParas, SwCursor* pCurCrsr,
//STRIP001                      SwMoveFn fnMove, SwCursor*& pFndRing,
//STRIP001                      SwPaM& aRegion, FindRanges eFndRngs,
//STRIP001                         FASTBOOL bInReadOnly, BOOL& bCancel )
//STRIP001 {
//STRIP001  SwDoc* pDoc = pCurCrsr->GetDoc();
//STRIP001  FASTBOOL bDoesUndo = pDoc->DoesUndo();
//STRIP001  int nFndRet = 0;
//STRIP001  ULONG nFound = 0;
//STRIP001  int bSrchBkwrd = fnMove == fnMoveBackward, bEnde = FALSE;
//STRIP001  SwPaM *pTmpCrsr = pCurCrsr, *pSaveCrsr = pCurCrsr;
//STRIP001
//STRIP001  // nur beim ShellCrsr einen Prgogressbar erzeugen
//STRIP001  BOOL bIsUnoCrsr = 0 != (SwUnoCrsr*)*pCurCrsr;
//STRIP001  _PercentHdl* pPHdl = 0;
//STRIP001  USHORT nCrsrCnt = 0;
//STRIP001  if( FND_IN_SEL & eFndRngs )
//STRIP001  {
//STRIP001      while( pCurCrsr != ( pTmpCrsr = (SwPaM*)pTmpCrsr->GetNext() ))
//STRIP001          ++nCrsrCnt;
//STRIP001      if( nCrsrCnt && !bIsUnoCrsr )
//STRIP001          pPHdl = new _PercentHdl( 0, nCrsrCnt, pDoc->GetDocShell() );
//STRIP001  }
//STRIP001
//STRIP001  do {
//STRIP001      aRegion.SetMark();
//STRIP001      // egal in welche Richtung, SPoint ist immer groesser als Mark,
//STRIP001      // wenn der Suchbereich gueltig ist !!
//STRIP001      SwPosition *pSttPos = aRegion.GetMark(),
//STRIP001                      *pEndPos = aRegion.GetPoint();
//STRIP001      *pSttPos = *pTmpCrsr->Start();
//STRIP001      *pEndPos = *pTmpCrsr->End();
//STRIP001      if( bSrchBkwrd )
//STRIP001          aRegion.Exchange();
//STRIP001
//STRIP001      if( !nCrsrCnt && !pPHdl && !bIsUnoCrsr )
//STRIP001          pPHdl = new _PercentHdl( aRegion );
//STRIP001
//STRIP001      // solange gefunden und nicht auf gleicher Position haengen bleibt
//STRIP001      while(  *pSttPos <= *pEndPos &&
//STRIP001              0 != ( nFndRet = rParas.Find( pCurCrsr, fnMove,
//STRIP001                                          &aRegion, bInReadOnly )) &&
//STRIP001              ( !pFndRing ||
//STRIP001                  *pFndRing->GetPoint() != *pCurCrsr->GetPoint() ||
//STRIP001                  *pFndRing->GetMark() != *pCurCrsr->GetMark() ))
//STRIP001      {
//STRIP001          if( !( FIND_NO_RING & nFndRet ))
//STRIP001          {
//STRIP001              // Bug 24084: Ring richtig herum aufbauen -> gleiche Mimik
//STRIP001              //            wie beim CreateCrsr !!!!
//STRIP001
//STRIP001              SwCursor* pNew = pCurCrsr->Create( pFndRing );
//STRIP001              if( !pFndRing )
//STRIP001                  pFndRing = pNew;
//STRIP001
//STRIP001              pNew->SetMark();
//STRIP001              *pNew->GetMark() = *pCurCrsr->GetMark();
//STRIP001          }
//STRIP001
//STRIP001          ++nFound;
//STRIP001
//STRIP001          if( !( eFndRngs & FND_IN_SELALL) )
//STRIP001          {
//STRIP001              bEnde = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001             if( coSrchRplcThreshold == nFound && pDoc->DoesUndo()
//STRIP001                 && rParas.IsReplaceMode())
//STRIP001          {
//STRIP001                 short nRet = pCurCrsr->MaxReplaceArived();
//STRIP001                 if( RET_YES == nRet )
//STRIP001                 {
//STRIP001                     pDoc->DelAllUndoObj();
//STRIP001                     pDoc->DoUndo( FALSE );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     bEnde = TRUE;
//STRIP001                     if(RET_CANCEL == nRet)
//STRIP001                     {
//STRIP001                         bCancel = TRUE;
//STRIP001                         //unwind() ??
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001          if( bSrchBkwrd )
//STRIP001              // bewege pEndPos vor den gefundenen Bereich
//STRIP001              *pEndPos = *pCurCrsr->Start();
//STRIP001          else
//STRIP001              // bewege pSttPos hinter den gefundenen Bereich
//STRIP001              *pSttPos = *pCurCrsr->End();
//STRIP001
//STRIP001          if( *pSttPos == *pEndPos )      // im Bereich, aber am Ende
//STRIP001              break;                      // fertig
//STRIP001
//STRIP001          if( !nCrsrCnt && !bIsUnoCrsr )
//STRIP001              pPHdl->NextPos( *aRegion.GetMark() );
//STRIP001      }
//STRIP001
//STRIP001      if( bEnde || !( eFndRngs & ( FND_IN_SELALL | FND_IN_SEL )) )
//STRIP001          break;
//STRIP001
//STRIP001      pTmpCrsr = ((SwPaM*)pTmpCrsr->GetNext());
//STRIP001      if( nCrsrCnt && !bIsUnoCrsr )
//STRIP001          pPHdl->NextPos( ++pPHdl->nActPos );
//STRIP001
//STRIP001  } while( pTmpCrsr != pSaveCrsr );
//STRIP001
//STRIP001  if( nFound && !pFndRing )       // falls kein Ring aufgebaut werden soll
//STRIP001      pFndRing = pCurCrsr->Create();
//STRIP001
//STRIP001  delete pPHdl;
//STRIP001  pDoc->DoUndo( bDoesUndo );
//STRIP001  return nFound;
//STRIP001 }


//STRIP001 int lcl_MakeSelFwrd( const SwNode& rSttNd, const SwNode& rEndNd,
//STRIP001                      SwPaM& rPam, int bFirst )
//STRIP001 {
//STRIP001  if( rSttNd.GetIndex() + 1 == rEndNd.GetIndex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwNodes& rNds = rPam.GetDoc()->GetNodes();
//STRIP001  rPam.DeleteMark();
//STRIP001  SwCntntNode* pCNd;
//STRIP001  if( !bFirst )
//STRIP001  {
//STRIP001      rPam.GetPoint()->nNode = rSttNd;
//STRIP001      pCNd = rNds.GoNext( &rPam.GetPoint()->nNode );
//STRIP001      if( !pCNd )
//STRIP001          return FALSE;
//STRIP001      pCNd->MakeStartIndex( &rPam.GetPoint()->nContent );
//STRIP001  }
//STRIP001  else if( rSttNd.GetIndex() > rPam.GetPoint()->nNode.GetIndex() ||
//STRIP001           rPam.GetPoint()->nNode.GetIndex() >= rEndNd.GetIndex() )
//STRIP001      return FALSE;       // steht nicht in dieser Section
//STRIP001
//STRIP001  rPam.SetMark();
//STRIP001  rPam.GetPoint()->nNode = rEndNd;
//STRIP001  pCNd = rNds.GoPrevious( &rPam.GetPoint()->nNode );
//STRIP001  if( !pCNd )
//STRIP001      return FALSE;
//STRIP001  pCNd->MakeEndIndex( &rPam.GetPoint()->nContent );
//STRIP001
//STRIP001  return *rPam.GetMark() < *rPam.GetPoint();
//STRIP001 }


//STRIP001 int lcl_MakeSelBkwrd( const SwNode& rSttNd, const SwNode& rEndNd,
//STRIP001                      SwPaM& rPam, int bFirst )
//STRIP001 {
//STRIP001  if( rEndNd.GetIndex() + 1 == rSttNd.GetIndex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwNodes& rNds = rPam.GetDoc()->GetNodes();
//STRIP001  rPam.DeleteMark();
//STRIP001  SwCntntNode* pCNd;
//STRIP001  if( !bFirst )
//STRIP001  {
//STRIP001      rPam.GetPoint()->nNode = rSttNd;
//STRIP001      pCNd = rNds.GoPrevious( &rPam.GetPoint()->nNode );
//STRIP001      if( !pCNd )
//STRIP001          return FALSE;
//STRIP001      pCNd->MakeEndIndex( &rPam.GetPoint()->nContent );
//STRIP001  }
//STRIP001  else if( rEndNd.GetIndex() > rPam.GetPoint()->nNode.GetIndex() ||
//STRIP001           rPam.GetPoint()->nNode.GetIndex() >= rSttNd.GetIndex() )
//STRIP001      return FALSE;       // steht nicht in dieser Section
//STRIP001
//STRIP001  rPam.SetMark();
//STRIP001  rPam.GetPoint()->nNode = rEndNd;
//STRIP001  pCNd = rNds.GoNext( &rPam.GetPoint()->nNode );
//STRIP001  if( !pCNd )
//STRIP001      return FALSE;
//STRIP001  pCNd->MakeStartIndex( &rPam.GetPoint()->nContent );
//STRIP001
//STRIP001  return *rPam.GetPoint() < *rPam.GetMark();
//STRIP001 }


// diese Methode "sucht" fuer alle Anwendungsfaelle, denn in SwFindParas
// steht immer die richtigen Parameter und die entsprechende Find-Methode

/*M*/ ULONG SwCursor::FindAll( SwFindParas& rParas,
/*M*/                           SwDocPositions nStart, SwDocPositions nEnde,
/*M*/                             FindRanges eFndRngs, BOOL& bCancel )
/*M*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001 /*?*/     bCancel = FALSE;
//STRIP001 /*?*/     SwCrsrSaveState aSaveState( *this );
//STRIP001 /*?*/
//STRIP001 /*?*/    // Region erzeugen, ohne das diese in den Ring aufgenommen wird !
//STRIP001 /*?*/    SwPaM aRegion( *GetPoint() );
//STRIP001 /*?*/    SwMoveFn fnMove = MakeFindRange( nStart, nEnde, &aRegion );
//STRIP001 /*?*/
//STRIP001 /*?*/    ULONG nFound = 0;
//STRIP001 /*?*/    int bMvBkwrd = fnMove == fnMoveBackward;
//STRIP001 /*?*/    FASTBOOL bInReadOnly = IsReadOnlyAvailable();
//STRIP001 /*?*/
//STRIP001 /*?*/    SwCursor* pFndRing = 0;
//STRIP001 /*?*/    SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001 /*?*/
//STRIP001 /*?*/    // suche in Bereichen ?
//STRIP001 /*?*/    if( FND_IN_SEL & eFndRngs )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // String nicht im Bereich gefunden, dann erhalte alle Bereiche,
//STRIP001 /*?*/        // der Cursor beleibt unveraendert
//STRIP001 /*?*/        if( 0 == ( nFound = lcl_FindSelection( rParas, this, fnMove,
//STRIP001 /*?*/                                                pFndRing, aRegion, eFndRngs,
//STRIP001 /*?*/                                                 bInReadOnly, bCancel ) ))
//STRIP001 /*?*/            return nFound;
//STRIP001 /*?*/
//STRIP001 /*?*/        // der String wurde ein- bis mehrmals gefunden. Das steht alles
//STRIP001 /*?*/        // im neuen Crsr-Ring. Darum hebe erstmal den alten Ring auf
//STRIP001 /*?*/        while( GetNext() != this )
//STRIP001 /*?*/            delete GetNext();
//STRIP001 /*?*/
//STRIP001 /*?*/        *GetPoint() = *pFndRing->GetPoint();
//STRIP001 /*?*/        SetMark();
//STRIP001 /*?*/        *GetMark() = *pFndRing->GetMark();
//STRIP001 /*?*/        pFndRing->MoveRingTo( this );
//STRIP001 /*?*/        delete pFndRing;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if( FND_IN_OTHER & eFndRngs )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // Cursor als Kopie vom akt. und in den Ring aufnehmen
//STRIP001 /*?*/        // Verkettung zeigt immer auf den zuerst erzeugten, also vorwaerts
//STRIP001 /*?*/        SwCursor* pSav = Create( this );    // sicher den aktuellen Crsr
//STRIP001 /*?*/
//STRIP001 /*?*/        // wenn schon ausserhalb vom Bodytext, suche von der Position,
//STRIP001 /*?*/        // ansonsten beginne mit der 1. GrundSection
//STRIP001 /*?*/        if( bMvBkwrd
//STRIP001 /*?*/            ? lcl_MakeSelBkwrd( rNds.GetEndOfExtras(),
//STRIP001 /*?*/                    *rNds.GetEndOfPostIts().StartOfSectionNode(),
//STRIP001 /*?*/                     *this, rNds.GetEndOfExtras().GetIndex() >=
//STRIP001 /*?*/                    GetPoint()->nNode.GetIndex() )
//STRIP001 /*?*/            : lcl_MakeSelFwrd( *rNds.GetEndOfPostIts().StartOfSectionNode(),
//STRIP001 /*?*/                    rNds.GetEndOfExtras(), *this,
//STRIP001 /*?*/                    rNds.GetEndOfExtras().GetIndex() >=
//STRIP001 /*?*/                    GetPoint()->nNode.GetIndex() ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nFound = lcl_FindSelection( rParas, this, fnMove, pFndRing,
//STRIP001 /*?*/                                         aRegion, eFndRngs, bInReadOnly, bCancel );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( !nFound )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // den alten wieder zurueck
//STRIP001 /*?*/            *GetPoint() = *pSav->GetPoint();
//STRIP001 /*?*/            if( pSav->HasMark() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SetMark();
//STRIP001 /*?*/                *GetMark() = *pSav->GetMark();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                DeleteMark();
//STRIP001 /*?*/            return 0;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        delete pSav;
//STRIP001 /*?*/        if( !( FND_IN_SELALL & eFndRngs ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // es sollte nur einer gesucht werden, also fuege in dazu
//STRIP001 /*?*/            // egal in welche Richtung, SPoint ist immer groesser als Mark,
//STRIP001 /*?*/            // wenn der Suchbereich gueltig ist !!
//STRIP001 /*?*/            *GetPoint() = *pFndRing->GetPoint();
//STRIP001 /*?*/            SetMark();
//STRIP001 /*?*/            *GetMark() = *pFndRing->GetMark();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // es  wurde ein- bis mehrmals gefunden. Das steht alles
//STRIP001 /*?*/            // im neuen Crsr-Ring. Darum hebe erstmal den alten Ring auf
//STRIP001 /*?*/            while( GetNext() != this )
//STRIP001 /*?*/                delete GetNext();
//STRIP001 /*?*/
//STRIP001 /*?*/            *GetPoint() = *pFndRing->GetPoint();
//STRIP001 /*?*/            SetMark();
//STRIP001 /*?*/            *GetMark() = *pFndRing->GetMark();
//STRIP001 /*?*/            pFndRing->MoveRingTo( this );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        delete pFndRing;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if( FND_IN_SELALL & eFndRngs )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        SwCursor* pSav = Create( this );    // sicher den aktuellen Crsr
//STRIP001 /*?*/
//STRIP001 /*?*/        const SwNode* pSttNd = ( FND_IN_BODYONLY & eFndRngs )
//STRIP001 /*?*/                            ? rNds.GetEndOfContent().StartOfSectionNode()
//STRIP001 /*?*/                            : rNds.GetEndOfPostIts().StartOfSectionNode();
//STRIP001 /*?*/
//STRIP001 /*?*/        if( bMvBkwrd
//STRIP001 /*?*/            ? lcl_MakeSelBkwrd( rNds.GetEndOfContent(), *pSttNd,*this, FALSE )
//STRIP001 /*?*/            : lcl_MakeSelFwrd( *pSttNd, rNds.GetEndOfContent(), *this, FALSE ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nFound = lcl_FindSelection( rParas, this, fnMove, pFndRing,
//STRIP001 /*?*/                                         aRegion, eFndRngs, bInReadOnly, bCancel );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( !nFound )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // den alten wieder zurueck
//STRIP001 /*?*/            *GetPoint() = *pSav->GetPoint();
//STRIP001 /*?*/            if( pSav->HasMark() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SetMark();
//STRIP001 /*?*/                *GetMark() = *pSav->GetMark();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                DeleteMark();
//STRIP001 /*?*/            return 0;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        // es  wurde ein- bis mehrmals gefunden. Das steht alles
//STRIP001 /*?*/        // im neuen Crsr-Ring. Darum hebe erstmal den alten Ring auf
//STRIP001 /*?*/        delete pSav;
//STRIP001 /*?*/
//STRIP001 /*?*/        while( GetNext() != this )
//STRIP001 /*?*/            delete GetNext();
//STRIP001 /*?*/
//STRIP001 /*?*/        *GetPoint() = *pFndRing->GetPoint();
//STRIP001 /*?*/        SetMark();
//STRIP001 /*?*/        *GetMark() = *pFndRing->GetMark();
//STRIP001 /*?*/        pFndRing->MoveRingTo( this );
//STRIP001 /*?*/        delete pFndRing;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // ist ein GetMark gesetzt, dann wird bei gefundenem Object
//STRIP001 /*?*/        // der GetMark beibehalten !! Dadurch kann ein Bereich mit der Suche
//STRIP001 /*?*/        // aufgespannt werden.
//STRIP001 /*?*/        SwPosition aMarkPos( *GetMark() );
//STRIP001 /*?*/        int bMarkPos = HasMark() && !eFndRngs;
//STRIP001 /*?*/
//STRIP001 /*?*/        if( 0 != (nFound = rParas.Find( this, fnMove,
//STRIP001 /*?*/                                        &aRegion, bInReadOnly ) ? 1 : 0)
//STRIP001 /*?*/            && bMarkPos )
//STRIP001 /*?*/            *GetMark() = aMarkPos;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( nFound && SwCursor::IsSelOvr( SELOVER_TOGGLE ) )
//STRIP001 /*?*/        nFound = 0;
//STRIP001 /*?*/    return nFound;
/*M*/ }


//STRIP001 void SwCursor::FillFindPos( SwDocPositions ePos, SwPosition& rPos ) const
//STRIP001 {
//STRIP001  BOOL bIsStart = TRUE;
//STRIP001  SwCntntNode* pCNd = 0;
//STRIP001  SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001
//STRIP001  switch( ePos )
//STRIP001  {
//STRIP001  case DOCPOS_START:
//STRIP001      rPos.nNode = *rNds.GetEndOfContent().StartOfSectionNode();
//STRIP001      pCNd = rNds.GoNext( &rPos.nNode );
//STRIP001      break;
//STRIP001
//STRIP001  case DOCPOS_END:
//STRIP001      rPos.nNode = rNds.GetEndOfContent();
//STRIP001      pCNd = rNds.GoPrevious( &rPos.nNode );
//STRIP001      bIsStart = FALSE;
//STRIP001      break;
//STRIP001
//STRIP001  case DOCPOS_OTHERSTART:
//STRIP001      rPos.nNode = *rNds[ ULONG(0) ];
//STRIP001      pCNd = rNds.GoNext( &rPos.nNode );
//STRIP001      break;
//STRIP001
//STRIP001  case DOCPOS_OTHEREND:
//STRIP001      rPos.nNode = *rNds.GetEndOfContent().StartOfSectionNode();
//STRIP001      pCNd = rNds.GoPrevious( &rPos.nNode );
//STRIP001      bIsStart = FALSE;
//STRIP001      break;
//STRIP001
//STRIP001 //   case DOCPOS_CURR:
//STRIP001  default:
//STRIP001      rPos = *GetPoint();
//STRIP001  }
//STRIP001
//STRIP001  if( pCNd )
//STRIP001  {
//STRIP001      xub_StrLen nCPos = 0;
//STRIP001      if( !bIsStart )
//STRIP001          nCPos = pCNd->Len();
//STRIP001      rPos.nContent.Assign( pCNd, nCPos );
//STRIP001  }
//STRIP001 }

//STRIP001 short SwCursor::MaxReplaceArived()
//STRIP001 {
//STRIP001     return RET_YES;
//STRIP001 }

/*N*/ FASTBOOL SwCursor::IsStartWord() const
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001      bRet = pBreakIt->xBreak->isBeginWord(
//STRIP001                          pTxtNd->GetTxt(), nPtPos,
//STRIP001                          pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos )),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES );
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

/*N*/ FASTBOOL SwCursor::IsEndWord() const
/*N*/ {
     FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001      bRet = pBreakIt->xBreak->isEndWord(
//STRIP001                          pTxtNd->GetTxt(), nPtPos,
//STRIP001                          pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES );
//STRIP001
//STRIP001  }
/*N*/ return bRet;
/*N*/ }

//STRIP001 FASTBOOL SwCursor::IsInWord() const
//STRIP001 {
//STRIP001     FASTBOOL bRet = FALSE;
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001         Boundary aBoundary = pBreakIt->xBreak->getWordBoundary(
//STRIP001                          pTxtNd->GetTxt(), nPtPos,
//STRIP001                          pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES,
//STRIP001                             TRUE );
//STRIP001
//STRIP001         bRet = aBoundary.startPos != aBoundary.endPos &&
//STRIP001                 aBoundary.startPos <= nPtPos &&
//STRIP001                     nPtPos <= aBoundary.endPos;
//STRIP001         if(bRet)
//STRIP001         {
//STRIP001             const CharClass& rCC = GetAppCharClass();
//STRIP001             bRet = rCC.isLetterNumeric( pTxtNd->GetTxt(), aBoundary.startPos );
//STRIP001         }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ FASTBOOL SwCursor::GoStartWord()
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSave( *this );
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001      nPtPos = (xub_StrLen)pBreakIt->xBreak->getWordBoundary(
//STRIP001                          pTxtNd->GetTxt(), nPtPos,
//STRIP001                          pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES,
//STRIP001                          FALSE ).startPos;
//STRIP001
//STRIP001      if( 0 <= nPtPos && nPtPos < pTxtNd->GetTxt().Len() )
//STRIP001      {
//STRIP001          GetPoint()->nContent = nPtPos;
//STRIP001          if( !IsSelOvr() )
//STRIP001              bRet = TRUE;
//STRIP001      }
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

/*N*/ FASTBOOL SwCursor::GoEndWord()
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSave( *this );
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001      nPtPos = (xub_StrLen)pBreakIt->xBreak->getWordBoundary(
//STRIP001                          pTxtNd->GetTxt(), nPtPos,
//STRIP001                          pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES,
//STRIP001                          TRUE ).endPos;
//STRIP001
//STRIP001      if( 0 <= nPtPos && nPtPos <= pTxtNd->GetTxt().Len() &&
//STRIP001          GetPoint()->nContent.GetIndex() != nPtPos )
//STRIP001      {
//STRIP001          GetPoint()->nContent = nPtPos;
//STRIP001          if( !IsSelOvr() )
//STRIP001              bRet = TRUE;
//STRIP001      }
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

/*N*/ FASTBOOL SwCursor::GoNextWord()
/*N*/ {
/*?*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSave( *this );
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001      nPtPos = (xub_StrLen)pBreakIt->xBreak->nextWord(
//STRIP001                              pTxtNd->GetTxt(), nPtPos,
//STRIP001                  pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos, 1 ) ),
//STRIP001                  WordType::ANYWORD_IGNOREWHITESPACES ).startPos;
//STRIP001
//STRIP001      if( 0 <= nPtPos && nPtPos < pTxtNd->GetTxt().Len() )
//STRIP001      {
//STRIP001          GetPoint()->nContent = nPtPos;
//STRIP001          if( !IsSelOvr() )
//STRIP001              bRet = TRUE;
//STRIP001      }
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

/*N*/ FASTBOOL SwCursor::GoPrevWord()
/*N*/ {
/*?*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSave( *this );
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001         const xub_StrLen nPtStart = nPtPos;
//STRIP001
//STRIP001         if( nPtPos )
//STRIP001             --nPtPos;
//STRIP001      nPtPos = (xub_StrLen)pBreakIt->xBreak->previousWord(
//STRIP001                                 pTxtNd->GetTxt(), nPtStart,
//STRIP001             pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos, 1 ) ),
//STRIP001                     WordType::ANYWORD_IGNOREWHITESPACES ).startPos;
//STRIP001
//STRIP001      if( 0 <= nPtPos && nPtPos < pTxtNd->GetTxt().Len() )
//STRIP001      {
//STRIP001          GetPoint()->nContent = nPtPos;
//STRIP001          if( !IsSelOvr() )
//STRIP001              bRet = TRUE;
//STRIP001      }
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

//STRIP001 FASTBOOL SwCursor::SelectWord( const Point* pPt )
//STRIP001 {
//STRIP001  SwCrsrSaveState aSave( *this );
//STRIP001
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  BOOL bForward = TRUE;
//STRIP001  DeleteMark();
//STRIP001  SwRootFrm* pLayout;
//STRIP001  if( pPt && 0 != (pLayout = GetDoc()->GetRootFrm()) )
//STRIP001  {
//STRIP001      // set the cursor to the layout position
//STRIP001      Point aPt( *pPt );
//STRIP001      pLayout->GetCrsrOfst( GetPoint(), aPt );
//STRIP001  }
//STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001      Boundary aBndry( pBreakIt->xBreak->getWordBoundary(
//STRIP001                          pTxtNd->GetTxt(), nPtPos,
//STRIP001                          pBreakIt->GetLocale( pTxtNd->GetLang( nPtPos ) ),
//STRIP001                           WordType::ANYWORD_IGNOREWHITESPACES,
//STRIP001                          bForward ));
//STRIP001
//STRIP001      if( aBndry.startPos != aBndry.endPos )
//STRIP001      {
//STRIP001          GetPoint()->nContent = (xub_StrLen)aBndry.endPos;
//STRIP001          if( !IsSelOvr() )
//STRIP001          {
//STRIP001              SetMark();
//STRIP001              GetMark()->nContent = (xub_StrLen)aBndry.startPos;
//STRIP001              if( !IsSelOvr() )
//STRIP001                  bRet = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bRet )
//STRIP001  {
//STRIP001      DeleteMark();
//STRIP001      RestoreSavePos();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//-----------------------------------------------------------------------------
/*N*/ FASTBOOL SwCursor::GoSentence( SentenceMoveType eMoveType )
/*N*/ {
/*?*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  const SwTxtNode* pTxtNd = GetNode()->GetTxtNode();
//STRIP001  if( pTxtNd && pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSave( *this );
//STRIP001      xub_StrLen nPtPos = GetPoint()->nContent.GetIndex();
//STRIP001      switch ( eMoveType )
//STRIP001      {
//STRIP001      case END_SENT:
//STRIP001      case NEXT_SENT:
//STRIP001          nPtPos = (xub_StrLen)pBreakIt->xBreak->endOfSentence(
//STRIP001                                  pTxtNd->GetTxt(),
//STRIP001                                  nPtPos, pBreakIt->GetLocale(
//STRIP001                                              pTxtNd->GetLang( nPtPos ) ));
//STRIP001          break;
//STRIP001      case START_SENT:
//STRIP001      case PREV_SENT:
//STRIP001          nPtPos = (xub_StrLen)pBreakIt->xBreak->beginOfSentence(
//STRIP001                                  pTxtNd->GetTxt(),
//STRIP001                                  nPtPos, pBreakIt->GetLocale(
//STRIP001                                          pTxtNd->GetLang( nPtPos ) ));
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if( 0 <= nPtPos && nPtPos < pTxtNd->GetTxt().Len() )
//STRIP001      {
//STRIP001          GetPoint()->nContent = nPtPos;
//STRIP001          if( !IsSelOvr() )
//STRIP001              bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
/*N*/ }


/*N*/ FASTBOOL SwCursor::LeftRight( BOOL bLeft, USHORT nCnt, USHORT nMode,
/*N*/                               BOOL bVisualAllowed, BOOL bInsertCrsr )
/*N*/ {
/*N*/   SwTableCursor* pTblCrsr = (SwTableCursor*)*this;
/*N*/   if( pTblCrsr )
/*N*/       return bLeft ? pTblCrsr->GoPrevCell( nCnt )
/*N*/                    : pTblCrsr->GoNextCell( nCnt );
/*N*/
/*N*/     // calculate cursor bidi level
/*N*/     const SwCntntFrm* pSttFrm = NULL;
/*N*/     SwNode& rNode = GetPoint()->nNode.GetNode();
/*N*/     const BOOL bDoNotSetBidiLevel = 0 != (SwUnoCrsr*)*this;
/*N*/
/*N*/     if ( ! bDoNotSetBidiLevel )
/*N*/     {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         if( rNode.IsTxtNode() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             const SwTxtNode& rTNd = *rNode.GetTxtNode();
//STRIP001 /*?*/             SwIndex& rIdx = GetPoint()->nContent;
//STRIP001 /*?*/             xub_StrLen nPos = rIdx.GetIndex();
//STRIP001 /*?*/
//STRIP001 /*?*/             SvtCTLOptions& rCTLOptions = SW_MOD()->GetCTLOptions();
//STRIP001 /*?*/             if ( bVisualAllowed && rCTLOptions.IsCTLFontEnabled() &&
//STRIP001 /*?*/                  SvtCTLOptions::MOVEMENT_VISUAL ==
//STRIP001 /*?*/                  rCTLOptions.GetCTLCursorMovement() )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 // for visual cursor travelling (used in bidi layout)
//STRIP001 /*?*/                 // we first have to convert the logic to a visual position
//STRIP001 /*?*/                 Point aPt;
//STRIP001 /*?*/                 pSttFrm = rTNd.GetFrm( &aPt, GetPoint() );
//STRIP001 /*?*/                 if( pSttFrm )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     BYTE nCrsrLevel = GetCrsrBidiLevel();
//STRIP001 /*?*/                     sal_Bool bForward = ! bLeft;
//STRIP001 /*?*/                     ((SwTxtFrm*)pSttFrm)->PrepareVisualMove( nPos, nCrsrLevel,
//STRIP001 /*?*/                                                              bForward, bInsertCrsr );
//STRIP001 /*?*/                     rIdx = nPos;
//STRIP001 /*?*/                     SetCrsrBidiLevel( nCrsrLevel );
//STRIP001 /*?*/                     bLeft = ! bForward;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/             else
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 const SwScriptInfo* pSI = SwScriptInfo::GetScriptInfo( rTNd );
//STRIP001 /*?*/                 if ( pSI )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     const xub_StrLen nMoveOverPos = bLeft ?
//STRIP001 /*?*/                                                    ( nPos ? nPos - 1 : 0 ) :
//STRIP001 /*?*/                                                     nPos;
//STRIP001 /*?*/                     SetCrsrBidiLevel( pSI->DirType( nMoveOverPos ) );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
/*N*/     }
/*N*/
/*N*/   // kann der Cursor n-mal weiterverschoben werden ?
/*N*/     SwCrsrSaveState aSave( *this );
/*N*/     SwMoveFn fnMove = bLeft ? fnMoveBackward : fnMoveForward;
/*N*/     SwGoInDoc fnGo = CRSR_SKIP_CELLS == nMode ? fnGoCntntCells : fnGoCntnt;
/*N*/     while( nCnt && Move( fnMove, fnGo ) )
/*N*/         --nCnt;
/*N*/
/*N*/     // here come some special rules for visual cursor travelling
/*N*/     if ( pSttFrm )
/*N*/     {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         SwNode& rTmpNode = GetPoint()->nNode.GetNode();
//STRIP001 /*?*/         if ( &rTmpNode != &rNode && rTmpNode.IsTxtNode() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             Point aPt;
//STRIP001 /*?*/             const SwCntntFrm* pEndFrm = ((SwTxtNode&)rTmpNode).GetFrm( &aPt, GetPoint() );
//STRIP001 /*?*/             if ( pEndFrm )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 if ( ! pEndFrm->IsRightToLeft() != ! pSttFrm->IsRightToLeft() )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     if ( ! bLeft )
//STRIP001 /*?*/                         pEndFrm->RightMargin( this );
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                         pEndFrm->LeftMargin( this );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
/*N*/     }
/*N*/
/*N*/   return 0 == nCnt && !IsInProtectTable( TRUE ) &&
/*N*/           !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
/*N*/ }

/*N*/ FASTBOOL SwCursor::UpDown( BOOL bUp, USHORT nCnt,
/*N*/                           Point* pPt, long nUpDownX )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 SwTableCursor* pTblCrsr = (SwTableCursor*)*this;
//STRIP001     sal_Bool bAdjustTableCrsr = sal_False;
//STRIP001
//STRIP001  // vom Tabellen Crsr Point/Mark in der gleichen Box ??
//STRIP001  // dann stelle den Point an den Anfang der Box
//STRIP001  if( pTblCrsr && GetNode( TRUE )->FindStartNode() ==
//STRIP001                     GetNode( FALSE )->FindStartNode() )
//STRIP001     {
//STRIP001         if ( End() != GetPoint() )
//STRIP001             Exchange();
//STRIP001         bAdjustTableCrsr = sal_True;
//STRIP001     }
//STRIP001
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  Point aPt;
//STRIP001  if( pPt )
//STRIP001      aPt = *pPt;
//STRIP001  SwCntntFrm* pFrm = GetCntntNode()->GetFrm( &aPt, GetPoint() );
//STRIP001
//STRIP001  if( pFrm )
//STRIP001  {
//STRIP001      SwCrsrSaveState aSave( *this );
//STRIP001
//STRIP001      if( !pPt )
//STRIP001      {
//STRIP001          SwRect aTmpRect;
//STRIP001          pFrm->GetCharRect( aTmpRect, *GetPoint() );
//STRIP001          aPt = aTmpRect.Pos();
//STRIP001             nUpDownX = pFrm->IsVertical() ?
//STRIP001                        aPt.Y() - pFrm->Frm().Top() :
//STRIP001                        aPt.X() - pFrm->Frm().Left();
//STRIP001      }
//STRIP001
//STRIP001      // Bei Fussnoten ist auch die Bewegung in eine andere Fussnote erlaubt.
//STRIP001      // aber keine Selection!!
//STRIP001      const FASTBOOL bChkRange = pFrm->IsInFtn() && !HasMark()
//STRIP001                                  ? FALSE : TRUE;
//STRIP001      const SwPosition aOldPos( *GetPoint() );
//STRIP001      BOOL bInReadOnly = IsReadOnlyAvailable();
//STRIP001
//STRIP001         if ( bAdjustTableCrsr && !bUp )
//STRIP001         {
//STRIP001             // Special case: We have a table cursor but the start box
//STRIP001             // has more than one paragraph. If we want to go down, we have to
//STRIP001             // set the point to the last frame in the table box. This is
//STRIP001             // only necessary if we do not already have a table selection
//STRIP001             const SwStartNode* pTblNd = GetNode( TRUE )->FindTableBoxStartNode();
//STRIP001             ASSERT( pTblNd, "pTblCrsr without SwTableNode?" )
//STRIP001
//STRIP001             if ( pTblNd ) // safety first
//STRIP001             {
//STRIP001                 const SwNode* pEndNd = pTblNd->EndOfSectionNode();
//STRIP001                 GetPoint()->nNode = *pEndNd;
//STRIP001                 pTblCrsr->Move( fnMoveBackward, fnGoNode );
//STRIP001                  pFrm = GetCntntNode()->GetFrm( &aPt, GetPoint() );
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         while( nCnt &&
//STRIP001                (bUp ? pFrm->UnitUp( this, nUpDownX, bInReadOnly )
//STRIP001                  : pFrm->UnitDown( this, nUpDownX, bInReadOnly ) ) &&
//STRIP001              CheckNodesRange( aOldPos.nNode, GetPoint()->nNode, bChkRange ))
//STRIP001      {
//STRIP001              pFrm = GetCntntNode()->GetFrm( &aPt, GetPoint() );
//STRIP001          --nCnt;
//STRIP001      }
//STRIP001
//STRIP001      if( !nCnt && !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS ) )  // die gesamte Anzahl durchlaufen ?
//STRIP001      {
//STRIP001          if( !pTblCrsr )
//STRIP001          {
//STRIP001              // dann versuche den Cursor auf die Position zu setzen,
//STRIP001              // auf halber Heohe vom Char-Rectangle
//STRIP001              pFrm = GetCntntNode()->GetFrm( &aPt, GetPoint() );
//STRIP001              SwCrsrMoveState eTmpState( MV_UPDOWN );
//STRIP001              eTmpState.bSetInReadOnly = bInReadOnly;
//STRIP001              SwRect aTmpRect;
//STRIP001              pFrm->GetCharRect( aTmpRect, *GetPoint(), &eTmpState );
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001                 if ( pFrm->IsVertical() )
//STRIP001                 {
//STRIP001                     aPt.X() = aTmpRect.Center().X();
//STRIP001                     pFrm->Calc();
//STRIP001                     aPt.Y() = pFrm->Frm().Top() + nUpDownX;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aPt.Y() = aTmpRect.Center().Y();
//STRIP001                     pFrm->Calc();
//STRIP001                     aPt.X() = pFrm->Frm().Left() + nUpDownX;
//STRIP001                 }
//STRIP001 #else
//STRIP001                 aPt.Y() = aTmpRect.Center().Y();
//STRIP001              pFrm->Calc();
//STRIP001              aPt.X() = pFrm->Frm().Left() + nUpDownX;
//STRIP001 #endif
//STRIP001              pFrm->GetCrsrOfst( GetPoint(), aPt, &eTmpState );
//STRIP001          }
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          *GetPoint() = aOldPos;
//STRIP001
//STRIP001         // calculate cursor bidi level
//STRIP001         const BOOL bDoNotSetBidiLevel = 0 != (SwUnoCrsr*)*this;
//STRIP001
//STRIP001         if ( ! bDoNotSetBidiLevel )
//STRIP001         {
//STRIP001             SwNode& rNode = GetPoint()->nNode.GetNode();
//STRIP001             if ( rNode.IsTxtNode() )
//STRIP001             {
//STRIP001                 const SwScriptInfo* pSI = SwScriptInfo::GetScriptInfo( (SwTxtNode&)rNode );
//STRIP001                 if ( pSI )
//STRIP001                 {
//STRIP001                     SwIndex& rIdx = GetPoint()->nContent;
//STRIP001                     xub_StrLen nPos = rIdx.GetIndex();
//STRIP001
//STRIP001                     if( nPos && nPos < ((SwTxtNode&)rNode).GetTxt().Len() )
//STRIP001                     {
//STRIP001                         const BYTE nCurrLevel = pSI->DirType( nPos );
//STRIP001                         const BYTE nPrevLevel = pSI->DirType( nPos - 1 );
//STRIP001
//STRIP001                         if ( nCurrLevel % 2 != nPrevLevel % 2 )
//STRIP001                         {
//STRIP001                             // set cursor level to the lower of the two levels
//STRIP001                             SetCrsrBidiLevel( Min( nCurrLevel, nPrevLevel ) );
//STRIP001                         }
//STRIP001                         else
//STRIP001                             SetCrsrBidiLevel( nCurrLevel );
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001  return bRet;
/*N*/ }

//STRIP001 FASTBOOL SwCursor::LeftRightMargin( BOOL bLeft, BOOL bAPI )
//STRIP001 {
//STRIP001  Point aPt;
//STRIP001  SwCntntFrm * pFrm = GetCntntNode()->GetFrm( &aPt, GetPoint() );
//STRIP001
//STRIP001     // calculate cursor bidi level
//STRIP001     if ( pFrm )
//STRIP001         SetCrsrBidiLevel( pFrm->IsRightToLeft() ? 1 : 0 );
//STRIP001
//STRIP001  return pFrm && (bLeft ? pFrm->LeftMargin( this )
//STRIP001                        : pFrm->RightMargin( this, bAPI ));
//STRIP001 }

/*N*/ FASTBOOL SwCursor::IsAtLeftRightMargin( BOOL bLeft, BOOL bAPI ) const
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 FASTBOOL bRet = FALSE;
//STRIP001  Point aPt;
//STRIP001  SwCntntFrm * pFrm = GetCntntNode()->GetFrm( &aPt, GetPoint() );
//STRIP001  if( pFrm )
//STRIP001  {
//STRIP001      SwPaM aPam( *GetPoint() );
//STRIP001      if( !bLeft && aPam.GetPoint()->nContent.GetIndex() )
//STRIP001          aPam.GetPoint()->nContent--;
//STRIP001      bRet = (bLeft ? pFrm->LeftMargin( &aPam )
//STRIP001                    : pFrm->RightMargin( &aPam, bAPI ))
//STRIP001              && *aPam.GetPoint() == *GetPoint();
//STRIP001  }
//STRIP001  return bRet;
/*N*/ }

//STRIP001 FASTBOOL SwCursor::SttEndDoc( BOOL bStt )
//STRIP001 {
//STRIP001  SwCrsrSaveState aSave( *this );
//STRIP001
//STRIP001  // Springe beim Selektieren nie ueber Section-Grenzen !!
//STRIP001  // kann der Cursor weiterverschoben werden ?
//STRIP001  SwMoveFn fnMove = bStt ? fnMoveBackward : fnMoveForward;
//STRIP001  FASTBOOL bRet = (!HasMark() || !IsNoCntnt() ) &&
//STRIP001                  Move( fnMove, fnGoDoc ) &&
//STRIP001                  !IsInProtectTable( TRUE ) &&
//STRIP001                  !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS |
//STRIP001                              SELOVER_ENABLEREVDIREKTION );
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SwCursor::GoPrevNextCell( BOOL bNext, USHORT nCnt )
//STRIP001 {
//STRIP001  const SwTableNode* pTblNd = GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // liegt vor dem StartNode der Cell ein weiterer EndNode, dann
//STRIP001  // gibt es auch eine vorherige Celle
//STRIP001  SwCrsrSaveState aSave( *this );
//STRIP001  SwNodeIndex& rPtIdx = GetPoint()->nNode;
//STRIP001  if( bNext )
//STRIP001  {
//STRIP001      while( nCnt-- )
//STRIP001      {
//STRIP001          SwNodeIndex aCellIdx( *rPtIdx.GetNode().FindTableBoxStartNode()->
//STRIP001                                  EndOfSectionNode(), 1 );
//STRIP001          if( !aCellIdx.GetNode().IsStartNode() )
//STRIP001              return FALSE;
//STRIP001          rPtIdx = aCellIdx;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      while( nCnt-- )
//STRIP001      {
//STRIP001          SwNodeIndex aCellIdx( *rPtIdx.GetNode().FindTableBoxStartNode(),-1);
//STRIP001          if( !aCellIdx.GetNode().IsEndNode() )
//STRIP001              return FALSE;
//STRIP001
//STRIP001          rPtIdx = *aCellIdx.GetNode().StartOfSectionNode();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rPtIdx++;
//STRIP001  if( !rPtIdx.GetNode().IsCntntNode() )
//STRIP001      GetDoc()->GetNodes().GoNextSection( &rPtIdx, TRUE, FALSE );
//STRIP001  GetPoint()->nContent.Assign( GetCntntNode(), 0 );
//STRIP001
//STRIP001  return !IsInProtectTable( TRUE );
//STRIP001 }

//STRIP001 FASTBOOL SwCursor::GotoTable( const String& rName )
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  // Tabellenselektion oder ueberhaupt Selection ?
//STRIP001  // Das ist eine ungueltige Action !
//STRIP001  if( !(SwTableCursor*)*this && !HasMark() )
//STRIP001  {
//STRIP001      SwTable* pTmpTbl = SwTable::FindTable( GetDoc()->FindTblFmtByName( rName ) );
//STRIP001      if( pTmpTbl )
//STRIP001      {
//STRIP001          // eine Tabelle im normalen NodesArr
//STRIP001          SwCrsrSaveState aSave( *this );
//STRIP001          GetPoint()->nNode = *pTmpTbl->GetTabSortBoxes()[ 0 ]->
//STRIP001                              GetSttNd()->FindTableNode();
//STRIP001          Move( fnMoveForward, fnGoCntnt );
//STRIP001          bRet = !IsSelOvr();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ FASTBOOL SwCursor::GotoTblBox( const String& rName )
/*N*/ {
/*N*/   FASTBOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  const SwTableNode* pTblNd = GetPoint()->nNode.GetNode().FindTableNode();
//STRIP001  if( pTblNd )
//STRIP001  {
//STRIP001      // erfrage die Box, mit dem Nanen
//STRIP001      const SwTableBox* pTblBox = pTblNd->GetTable().GetTblBox( rName );
//STRIP001      if( pTblBox && pTblBox->GetSttNd() &&
//STRIP001          ( !pTblBox->GetFrmFmt()->GetProtect().IsCntntProtected() ||
//STRIP001            IsReadOnlyAvailable() ) )
//STRIP001      {
//STRIP001          SwCrsrSaveState aSave( *this );
//STRIP001          GetPoint()->nNode = *pTblBox->GetSttNd();
//STRIP001          Move( fnMoveForward, fnGoCntnt );
//STRIP001          bRet = !IsSelOvr();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
/*N*/ }

/*N*/ FASTBOOL SwCursor::MovePara(SwWhichPara fnWhichPara, SwPosPara fnPosPara )
/*N*/ {
/*N*/   //JP 28.8.2001: for optimization test something before
/*N*/   const SwNode* pNd;
/*N*/   if( fnWhichPara == fnParaCurr ||
/*N*/       (( pNd = &GetPoint()->nNode.GetNode())->IsTxtNode() &&
/*N*/         pNd->GetNodes()[ pNd->GetIndex() +
/*N*/                   (fnWhichPara == fnParaNext ? 1 : -1 ) ]->IsTxtNode() ) )
/*N*/   {
/*N*/       return (*fnWhichPara)( *this, fnPosPara );
/*N*/   }
/*N*/   // else we must use the SaveStructure, because the next/prev is not
/*N*/   // a same node type.
/*N*/   SwCrsrSaveState aSave( *this );
/*N*/   return (*fnWhichPara)( *this, fnPosPara ) &&
/*N*/           !IsInProtectTable( TRUE ) &&
/*N*/           !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
/*N*/ }


/*N*/ FASTBOOL SwCursor::MoveSection( SwWhichSection fnWhichSect,
/*N*/                               SwPosSection fnPosSect)
/*N*/ {
/*N*/   SwCrsrSaveState aSave( *this );
/*N*/   return (*fnWhichSect)( *this, fnPosSect ) &&
/*N*/           !IsInProtectTable( TRUE ) &&
/*N*/           !IsSelOvr( SELOVER_TOGGLE | SELOVER_CHANGEPOS );
/*N*/ }

/*
    FASTBOOL MoveTable( SwWhichTable, SwPosTable );
    FASTBOOL MoveColumn( SwWhichColumn, SwPosColumn );
    FASTBOOL MoveRegion( SwWhichRegion, SwPosRegion );
*/

//STRIP001 void SwCursor::RestoreSavePos()      // Point auf die SavePos setzen
//STRIP001 {
//STRIP001  if( pSavePos )
//STRIP001  {
//STRIP001      GetPoint()->nNode = pSavePos->nNode;
//STRIP001      GetPoint()->nContent.Assign( GetCntntNode(), pSavePos->nCntnt );
//STRIP001  }
//STRIP001 }


/*  */

/*N*/SwTableCursor::SwTableCursor( const SwPosition &rPos, SwPaM* pRing )
/*N*/   : SwCursor( rPos, pRing )
/*N*/{
/*N*/   bParked = FALSE;
/*N*/   bChg = FALSE;
/*N*/   nTblPtNd = 0, nTblMkNd = 0;
/*N*/   nTblPtCnt = 0, nTblMkCnt = 0;
/*N*/}

/*N*/ SwTableCursor::~SwTableCursor() {}

/*N*/ SwTableCursor::operator SwTableCursor* () { return this; }

//STRIP001 BOOL lcl_SeekEntry( const SwSelBoxes& rTmp, const SwStartNode* pSrch, USHORT& rFndPos )
//STRIP001 {
//STRIP001  ULONG nIdx = pSrch->GetIndex();
//STRIP001
//STRIP001  register USHORT nO = rTmp.Count(), nM, nU = 0;
//STRIP001  if( nO > 0 )
//STRIP001  {
//STRIP001      nO--;
//STRIP001      while( nU <= nO )
//STRIP001      {
//STRIP001          nM = nU + ( nO - nU ) / 2;
//STRIP001          if( rTmp[ nM ]->GetSttNd() == pSrch )
//STRIP001          {
//STRIP001              rFndPos = nM;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001          else if( rTmp[ nM ]->GetSttIdx() < nIdx )
//STRIP001              nU = nM + 1;
//STRIP001          else if( nM == 0 )
//STRIP001              return FALSE;
//STRIP001          else
//STRIP001              nO = nM - 1;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


/*N*/  SwCursor* SwTableCursor::MakeBoxSels( SwCursor* pAktCrsr )
/*N*/  {
DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001   if( bChg )      // ???
//STRIP001  {
//STRIP001      if( bParked )
//STRIP001      {
//STRIP001          // wieder in den Inhalt schieben
//STRIP001          Exchange();
//STRIP001          Move( fnMoveForward );
//STRIP001          Exchange();
//STRIP001          Move( fnMoveForward );
//STRIP001          bParked = FALSE;
//STRIP001      }
//STRIP001
//STRIP001      bChg = FALSE;
//STRIP001
//STRIP001      // temp Kopie anlegen, damit alle Boxen, fuer die schon Cursor
//STRIP001      // existieren, entfernt werden koennen.
//STRIP001      SwSelBoxes aTmp;
//STRIP001      aTmp.Insert( &aSelBoxes );
//STRIP001
//STRIP001      //Jetzt die Alten und die neuen abgleichen.
//STRIP001      SwNodes& rNds = pAktCrsr->GetDoc()->GetNodes();
//STRIP001      USHORT nPos;
//STRIP001      const SwStartNode* pSttNd;
//STRIP001      SwPaM* pCur = pAktCrsr;
//STRIP001      do {
//STRIP001          BOOL bDel = FALSE;
//STRIP001          pSttNd = pCur->GetPoint()->nNode.GetNode().FindTableBoxStartNode();
//STRIP001          if( !pCur->HasMark() || !pSttNd ||
//STRIP001              pSttNd != pCur->GetMark()->nNode.GetNode().FindTableBoxStartNode() )
//STRIP001              bDel = TRUE;
//STRIP001
//STRIP001          else if( lcl_SeekEntry( aTmp, pSttNd, nPos ))
//STRIP001          {
//STRIP001              SwNodeIndex aIdx( *pSttNd, 1 );
//STRIP001              const SwNode* pNd = &aIdx.GetNode();
//STRIP001              if( !pNd->IsCntntNode() )
//STRIP001                  pNd = rNds.GoNextSection( &aIdx, TRUE, FALSE );
//STRIP001
//STRIP001              SwPosition* pPos = pCur->GetMark();
//STRIP001              if( pNd != &pPos->nNode.GetNode() )
//STRIP001                  pPos->nNode = *pNd;
//STRIP001              pPos->nContent.Assign( (SwCntntNode*)pNd, 0 );
//STRIP001
//STRIP001              aIdx.Assign( *pSttNd->EndOfSectionNode(), - 1 );
//STRIP001              if( !( pNd = &aIdx.GetNode())->IsCntntNode() )
//STRIP001                  pNd = rNds.GoPrevSection( &aIdx, TRUE, FALSE );
//STRIP001
//STRIP001              pPos = pCur->GetPoint();
//STRIP001              if( pNd != &pPos->nNode.GetNode() )
//STRIP001                  pPos->nNode = *pNd;
//STRIP001              pPos->nContent.Assign( (SwCntntNode*)pNd, ((SwCntntNode*)pNd)->Len() );
//STRIP001
//STRIP001              aTmp.Remove( nPos );
//STRIP001          }
//STRIP001          else
//STRIP001              bDel = TRUE;
//STRIP001
//STRIP001          pCur = (SwPaM*)pCur->GetNext();
//STRIP001          if( bDel )
//STRIP001          {
//STRIP001              SwPaM* pDel = (SwPaM*)pCur->GetPrev();
//STRIP001 /*
//STRIP001 JP 20.07.98: der alte Code geht mit dem UNO-TableCrsr nicht
//STRIP001              if( pDel == pAktCrsr )
//STRIP001              {
//STRIP001                  if( pAktCrsr->GetNext() == pAktCrsr )
//STRIP001                  {
//STRIP001                      pAktCrsr->DeleteMark();
//STRIP001                      break;      // es gibt nichts mehr zu loeschen!
//STRIP001                  }
//STRIP001                  pAktCrsr = (SwCursor*)pDel->GetPrev();
//STRIP001              }
//STRIP001              delete pDel;
//STRIP001 */
//STRIP001
//STRIP001              if( pDel == pAktCrsr )
//STRIP001                  pAktCrsr->DeleteMark();
//STRIP001              else
//STRIP001                  delete pDel;
//STRIP001          }
//STRIP001      } while ( pAktCrsr != pCur );
//STRIP001
//STRIP001      for( nPos = 0; nPos < aTmp.Count(); ++nPos )
//STRIP001      {
//STRIP001          pSttNd = aTmp[ nPos ]->GetSttNd();
//STRIP001
//STRIP001          SwNodeIndex aIdx( *pSttNd, 1 );
//STRIP001          const SwNode* pNd = &aIdx.GetNode();
//STRIP001          if( !pNd->IsCntntNode() )
//STRIP001              pNd = rNds.GoNextSection( &aIdx, TRUE, FALSE );
//STRIP001
//STRIP001          SwPaM* pNew;
//STRIP001          if( pAktCrsr->GetNext() == pAktCrsr && !pAktCrsr->HasMark() )
//STRIP001          {
//STRIP001              pNew = pAktCrsr;
//STRIP001              pNew->GetPoint()->nNode = *pNd;
//STRIP001              pNew->GetPoint()->nContent.Assign( (SwCntntNode*)pNd, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pNew = pAktCrsr->Create( pAktCrsr );
//STRIP001              pNew->GetPoint()->nNode = *pNd;
//STRIP001              pNew->GetPoint()->nContent.Assign( (SwCntntNode*)pNd, 0 );
//STRIP001          }
//STRIP001          pNew->SetMark();
//STRIP001
//STRIP001          SwPosition* pPos = pNew->GetPoint();
//STRIP001          pPos->nNode.Assign( *pSttNd->EndOfSectionNode(), - 1 );
//STRIP001          if( !( pNd = &pPos->nNode.GetNode())->IsCntntNode() )
//STRIP001              pNd = rNds.GoPrevSection( &pPos->nNode, TRUE, FALSE );
//STRIP001
//STRIP001          pPos->nContent.Assign( (SwCntntNode*)pNd, ((SwCntntNode*)pNd)->Len() );
//STRIP001      }
//STRIP001  }
//STRIP001  return pAktCrsr;
/*N*/ }


/*N*/ void SwTableCursor::InsertBox( const SwTableBox& rTblBox )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwTableBox* pBox = (SwTableBox*)&rTblBox;
//STRIP001  aSelBoxes.Insert( pBox );
//STRIP001  bChg = TRUE;
/*N*/ }

//STRIP001 FASTBOOL SwTableCursor::IsCrsrMovedUpdt()
//STRIP001 {
//STRIP001  if( !IsCrsrMoved() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  nTblMkNd = GetMark()->nNode.GetIndex();
//STRIP001  nTblPtNd = GetPoint()->nNode.GetIndex();
//STRIP001  nTblMkCnt = GetMark()->nContent.GetIndex();
//STRIP001  nTblPtCnt = GetPoint()->nContent.GetIndex();
//STRIP001  return TRUE;
//STRIP001 }


// Parke den Tabellen-Cursor auf dem StartNode der Boxen.
//STRIP001 void SwTableCursor::ParkCrsr()
//STRIP001 {
//STRIP001  // Index aus dem TextNode abmelden
//STRIP001  SwNode* pNd = &GetPoint()->nNode.GetNode();
//STRIP001  if( !pNd->IsStartNode() )
//STRIP001      pNd = pNd->StartOfSectionNode();
//STRIP001  GetPoint()->nNode = *pNd;
//STRIP001  GetPoint()->nContent.Assign( 0, 0 );
//STRIP001
//STRIP001  pNd = &GetMark()->nNode.GetNode();
//STRIP001  if( !pNd->IsStartNode() )
//STRIP001      pNd = pNd->StartOfSectionNode();
//STRIP001  GetMark()->nNode = *pNd;
//STRIP001  GetMark()->nContent.Assign( 0, 0 );
//STRIP001
//STRIP001  bChg = TRUE;
//STRIP001  bParked = TRUE;
//STRIP001 }


//STRIP001 FASTBOOL SwTableCursor::HasReadOnlyBoxSel() const
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001  for( USHORT n = aSelBoxes.Count(); n;  )
//STRIP001      if( aSelBoxes[ --n ]->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  return bRet;
//STRIP001 }


}
