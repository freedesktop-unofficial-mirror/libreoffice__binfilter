/*************************************************************************
 *
 *  $RCSfile: sw_shellio.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-01-11 11:45:56 $
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
#include <hintids.hxx>

// auto strip #ifndef _DATE_HXX
// auto strip #include <tools/date.hxx>
// auto strip #endif
// auto strip #ifndef _TIME_HXX
// auto strip #include <tools/time.hxx>
// auto strip #endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef SVTOOLS_FSTATHELPER_HXX
#include <svtools/fstathelper.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _SVX_LRSPITEM_HXX //autogen
// auto strip #include <bf_svx/lrspitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_ULSPITEM_HXX //autogen
// auto strip #include <bf_svx/ulspitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_BOXITEM_HXX //autogen
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _SVX_PAPERINF_HXX //autogen
#include <bf_svx/paperinf.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _NODE_HXX //autogen
// auto strip #include <node.hxx>
// auto strip #endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
// auto strip #ifndef _SHELLIO_HXX
// auto strip #include <shellio.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _DOCSH_HXX
// auto strip #include <docsh.hxx>
// auto strip #endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>           // fuer Undo Insert-Dokument
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>           // fuer Undo Insert-Dokument
#endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
// auto strip #ifndef _TBLSEL_HXX
// auto strip #include <tblsel.hxx>
// auto strip #endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
// auto strip #ifndef _POOLFMT_HXX
// auto strip #include <poolfmt.hxx>
// auto strip #endif
#ifndef _FLTINI_HXX
#include <fltini.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
// auto strip #ifndef _SW3IO_HXX
// auto strip #include <sw3io.hxx>
// auto strip #endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _LINKENUM_HXX
#include <linkenum.hxx>
#endif
#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_UPDATEDOCMODE_HPP_
#include <com/sun/star/document/UpdateDocMode.hpp>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {

using namespace ::com::sun::star;

//////////////////////////////////////////////////////////////////////////

/*N*/ ULONG SwReader::Read( const Reader& rOptions )
/*N*/ {
/*N*/   // Variable uebertragen
/*N*/   Reader* po = (Reader*) &rOptions;
/*N*/   po->pStrm = pStrm;
/*N*/   po->pStg  = pStg;
/*N*/   po->bInsertMode = 0 != pCrsr;
/*N*/
/*N*/   // ist ein Medium angegeben, dann aus diesem die Streams besorgen
/*N*/   if( 0 != (po->pMedium = pMedium ) &&
/*?*/       1 ) //STRIP001 !po->SetStrmStgPtr() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 po->SetReadUTF8( FALSE );
//STRIP001 /*?*/        po->SetBlockMode( FALSE );
//STRIP001 /*?*/        po->SetOrganizerMode( FALSE );
//STRIP001 /*?*/         po->SetIgnoreHTMLComments( FALSE );
//STRIP001 /*?*/        return ERR_SWG_FILE_FORMAT_ERROR;
/*N*/   }
/*N*/
/*N*/   ULONG nError = 0L;
/*N*/
/*N*/   GetDoc();
/*N*/
/*N*/   // am Sw3-Reader noch den pIo-Pointer "loeschen"
/*N*/   if( po == ReadSw3 && pDoc->GetDocShell() &&
/*N*/       ((Sw3Reader*)po)->GetSw3Io() != pDoc->GetDocShell()->GetIoSystem() )
/*N*/           ((Sw3Reader*)po)->SetSw3Io( pDoc->GetDocShell()->GetIoSystem() );
/*N*/
/*N*/   // waehrend des einlesens kein OLE-Modified rufen
/*N*/   Link aOLELink( pDoc->GetOle2Link() );
/*N*/   pDoc->SetOle2Link( Link() );
/*N*/
/*N*/   pDoc->bInReading = TRUE;
/*N*/
/*N*/   SwPaM *pPam;
/*N*/   if( pCrsr )
/*?*/       pPam = pCrsr;
/*N*/   else
/*N*/   {
/*N*/       // Wenn der Reader nicht mit einem Shell konstruiert wurde,
/*N*/       // selber einen Pam machen.
/*N*/       SwNodeIndex nNode( pDoc->GetNodes().GetEndOfContent(), -1 );
/*N*/       pPam = new SwPaM( nNode );
/*N*/       // Bei Web-Dokumenten wird die Default-Vorlage schon im InitNew
/*N*/       // gesetzt und braucht deshalb nicht nochmal gesetzt zu werden.
/*N*/       // Das gilt natuerlich nicht, wenn der Filter nicht der HTML-Filter
/*N*/       // ist oder im ConvertFrom zuvor ein SetTemplateName gerufen
/*N*/       // wurde.
/*N*/       if( !pDoc->IsHTMLMode() || ReadHTML != po || !po->pTemplate  )
/*N*/           po->SetTemplate( *pDoc );
/*N*/   }
/*N*/
/*N*/   // Pams sind ringfoermig verkettet. Aufhoeren, wenn man wieder beim
/*N*/   // ersten ist.
/*N*/   SwPaM *pEnd = pPam;
/*N*/   SwUndoInsDoc* pUndo = 0L;
/*N*/
/*N*/   BOOL bReadPageDescs = FALSE;
/*N*/   BOOL bDocUndo = pDoc->DoesUndo();
/*N*/   BOOL bSaveUndo = bDocUndo && pCrsr;
/*N*/   if( bSaveUndo )
/*N*/   {
/*?*/       // das Einlesen von Seitenvorlagen ist nicht Undofaehig!
/*?*/       if( 0 != ( bReadPageDescs = po->aOpt.IsPageDescs() ) )
/*?*/       {
/*?*/           bSaveUndo = FALSE;
/*?*/           pDoc->DelAllUndoObj();
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           pDoc->ClearRedo();
/*?*/           pDoc->StartUndo( UNDO_INSDOKUMENT );
/*?*/       }
/*N*/   }
/*N*/   pDoc->DoUndo( FALSE );
/*N*/
/*N*/   SwNodeIndex aSplitIdx( pDoc->GetNodes() );
/*N*/
/*N*/   SwRedlineMode eOld = pDoc->GetRedlineMode();
/*N*/   pDoc->SetRedlineMode_intern( REDLINE_IGNORE );
/*N*/
/*N*/   // Array von FlyFormaten
/*N*/   SwSpzFrmFmts aFlyFrmArr;
/*N*/   // only read templates? then ignore multi selection!
/*N*/   BOOL bFmtsOnly = po->aOpt.IsFmtsOnly();
/*N*/
/*N*/   while( TRUE )
/*N*/   {
/*N*/       if( bSaveUndo )
/*?*/           pUndo = new SwUndoInsDoc( *pPam );
/*N*/
/*N*/       SwPaM* pUndoPam = 0L;
/*N*/       if( bDocUndo || pCrsr )
/*N*/       {
/*?*/           // Pam auf den Node davor setzen damit er nicht mit verschoben wird
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwNodeIndex& rTmp = pPam->GetPoint()->nNode;
//STRIP001 /*?*/            pUndoPam = new SwPaM( rTmp, rTmp, 0, -1 );
/*N*/       }
/*N*/
/*N*/       // Speicher mal alle Fly's
/*N*/       if( pCrsr )
/*?*/           aFlyFrmArr.Insert( pDoc->GetSpzFrmFmts(), 0L );
/*N*/
/*N*/       xub_StrLen nSttCntnt = pPam->GetPoint()->nContent.GetIndex();
/*N*/
/*N*/       // damit fuer alle Reader die Ende-Position immer stimmt, hier
/*N*/       // pflegen.
/*N*/       SwCntntNode* pCNd = pPam->GetCntntNode();
/*N*/       xub_StrLen nEndCntnt = pCNd ? pCNd->Len() - nSttCntnt : 0;
/*N*/       SwNodeIndex aEndPos( pPam->GetPoint()->nNode, 1 );
/*N*/
/*N*/       nError = po->Read( *pDoc, *pPam, aFileName );
/*N*/
/*N*/       if( !IsError( nError ))     // dann setzen wir das Ende mal richtig
/*N*/       {
/*N*/           aEndPos--;
/*N*/           pCNd = aEndPos.GetNode().GetCntntNode();
/*N*/           if( !pCNd && 0 == ( pCNd = pDoc->GetNodes().GoPrevious( &aEndPos ) ))
/*?*/               pCNd = pDoc->GetNodes().GoNext( &aEndPos );
/*N*/
/*N*/           pPam->GetPoint()->nNode = aEndPos;
/*N*/           xub_StrLen nLen = pCNd->Len();
/*N*/           if( nLen < nEndCntnt )
/*?*/               nEndCntnt = 0;
/*N*/           else
/*N*/               nEndCntnt = nLen - nEndCntnt;
/*N*/           pPam->GetPoint()->nContent.Assign( pCNd, nEndCntnt );
/*N*/       }
/*N*/
/*N*/       if( pCrsr )
/*N*/       {
/*?*/           *pUndoPam->GetMark() = *pPam->GetPoint();
/*?*/           pUndoPam->GetPoint()->nNode++;
/*?*/           SwNode* pNd = pUndoPam->GetNode();
/*?*/           if( pNd->IsCntntNode() )
/*?*/               pUndoPam->GetPoint()->nContent.Assign(
/*?*/                                   (SwCntntNode*)pNd, nSttCntnt );
/*?*/           else
/*?*/               pUndoPam->GetPoint()->nContent.Assign( 0, 0 );
/*?*/
/*?*/           int bChkHeaderFooter = pNd->FindHeaderStartNode() ||
/*?*/                                  pNd->FindFooterStartNode();
/*?*/
/*?*/           // Suche alle neuen Fly's und speicher sie als einzelne Undo
/*?*/           // Objecte
/*?*/           for( USHORT n = 0; n < pDoc->GetSpzFrmFmts()->Count(); ++n )
/*?*/           {
/*?*/               SwFrmFmt* pFrmFmt = (*pDoc->GetSpzFrmFmts())[ n ];
/*?*/               const SwFmtAnchor& rAnchor = pFrmFmt->GetAnchor();
/*?*/               if( USHRT_MAX == aFlyFrmArr.GetPos( pFrmFmt) )
/*?*/               {
/*?*/                   if( FLY_PAGE == rAnchor.GetAnchorId() ||
/*?*/                       ( FLY_AT_CNTNT == rAnchor.GetAnchorId() &&
/*?*/                           rAnchor.GetCntntAnchor() &&
/*?*/                           ( pUndoPam->GetPoint()->nNode ==
/*?*/                           rAnchor.GetCntntAnchor()->nNode ||
/*?*/                           pUndoPam->GetMark()->nNode ==
/*?*/                           rAnchor.GetCntntAnchor()->nNode ) ) )
/*?*/                   {
/*?*/                       if( bChkHeaderFooter &&
/*?*/                           FLY_AT_CNTNT == rAnchor.GetAnchorId() &&
/*?*/                           RES_DRAWFRMFMT == pFrmFmt->Which() )
/*?*/                       {
/*?*/                           // DrawObjecte in Kopf-/Fusszeilen ist nicht
/*?*/                           // erlaubt!
/*?*/                           pFrmFmt->DelFrms();
/*?*/                           pDoc->DelFrmFmt( pFrmFmt );
/*?*/                           --n;
/*?*/                       }
/*?*/                       else
/*?*/                       {
/*?*/                           if( bSaveUndo )
/*?*/                           {
/*?*/                               pDoc->SetRedlineMode_intern( eOld );
/*?*/                               pDoc->AppendUndo( new SwUndoInsLayFmt( pFrmFmt ) );
/*?*/                               pDoc->SetRedlineMode_intern( REDLINE_IGNORE );
/*?*/                           }
/*?*/                           if( pFrmFmt->GetDepends() )
/*?*/                           {
/*?*/                               // beim Insert legen Draw-Objecte einen Frame an
/*?*/                               // also weg damit.
/*?*/                               pFrmFmt->DelFrms();
/*?*/                           }
/*?*/
/*?*/                           if( FLY_PAGE == rAnchor.GetAnchorId() )
/*?*/                           {
/*?*/                               if( !rAnchor.GetCntntAnchor() )
/*?*/                               {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pFrmFmt->MakeFrms();
/*?*/                               else if( pCrsr )
/*?*/                                   // seitengebundene Flys eingefuegt, dann schalte
/*?*/                                   // die Optimierungs-Flags vom SwDoc ab. Sonst
/*?*/                                   // werden die Flys nicht an der Position erzeugt.
/*?*/                                   pDoc->SetLoaded( FALSE );
/*?*/                           }
/*?*/                           else
/*?*/                           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pFrmFmt->MakeFrms();
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           if( aFlyFrmArr.Count() )
/*?*/               aFlyFrmArr.Remove( 0, aFlyFrmArr.Count() );
/*?*/
/*?*/           pDoc->SetRedlineMode_intern( eOld );
/*?*/           if( pDoc->IsRedlineOn() )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pDoc->AppendRedline( new SwRedline( REDLINE_INSERT, *pUndoPam ));
/*?*/           else
/*?*/           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pDoc->SplitRedline( *pUndoPam );
/*?*/           pDoc->SetRedlineMode_intern( REDLINE_IGNORE );
/*N*/       }
/*N*/       if( bSaveUndo )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pDoc->SetRedlineMode_intern( eOld );
//STRIP001 /*?*/            pUndo->SetInsertRange( *pUndoPam, FALSE );
//STRIP001 /*?*/            pDoc->AppendUndo( pUndo );
//STRIP001 /*?*/            pDoc->SetRedlineMode_intern( REDLINE_IGNORE );
/*N*/       }
/*N*/
/*N*/       delete pUndoPam;
/*N*/
/*N*/       pPam = (SwPaM *) pPam->GetNext();
/*N*/       if( pPam == pEnd )
/*N*/           break;
/*N*/
/*N*/       // only read templates? then ignore multi selection! Bug 68593
/*?*/       if( bFmtsOnly )
/*?*/           break;
/*?*/
        /*
         * !!! man muss selbst den Status vom Stream zuruecksetzen. !!!
         *     Beim seekg wird der akt. Status, eof- und bad-Bit
         *     gesetzt, warum weiss keiner
         */
/*?*/       if( pStrm )
/*?*/       {
/*?*/           pStrm->Seek(0);
/*?*/           pStrm->ResetError();
/*?*/       }
/*N*/   }
/*N*/
/*N*/   pDoc->bInReading = FALSE;
/*N*/   pDoc->SetAllUniqueFlyNames();
/*N*/
/*N*/   if( bReadPageDescs )
/*?*/       pDoc->DoUndo( TRUE );
/*N*/   else
/*N*/   {
/*N*/       pDoc->DoUndo( bDocUndo );
/*N*/       if( bSaveUndo )
/*N*/       {
/*?*/           pDoc->SetRedlineMode_intern( eOld );
/*?*/           pDoc->EndUndo( UNDO_INSDOKUMENT );
/*?*/           pDoc->SetRedlineMode_intern( REDLINE_IGNORE );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Wenn der Pam nur fuers Lesen konstruiert wurde, jetzt zerstoeren.
/*N*/   if( !pCrsr )
/*N*/   {
/*N*/       delete pPam;          // ein neues aufgemacht.
/*N*/
/*N*/       // alle Links updaten und Fehler melden
/*N*/       // (die Graphic-Links nicht, passiert ueber unseren Grafik-Cache!!)
/*N*/       // JP 20.03.96: aber nicht wenn die DocShell als INTERNAL
/*N*/       //              construiert wurde (FileLinks in FileLinks in ...)
/*N*/       // JP 27.06.96: wenn internal, dann nie Updaten! (rekursionen werden
/*N*/       //              sonst nicht erkannt! ( Bug )
/*N*/
/*N*/       SfxObjectCreateMode eMode;
/*N*/       USHORT nLinkMode = pDoc->GetLinkUpdMode();
/*N*/         USHORT nUpdateDocMode = pDoc->GetDocShell()->GetUpdateDocMode();
/*N*/         if( pDoc->GetDocShell() &&
/*N*/                 (nLinkMode != NEVER ||  document::UpdateDocMode::FULL_UPDATE == nUpdateDocMode) &&
/*N*/           pDoc->GetLinkManager().GetLinks().Count() &&
/*N*/           SFX_CREATE_MODE_INTERNAL !=
/*N*/                       ( eMode = pDoc->GetDocShell()->GetCreateMode()) &&
/*N*/           SFX_CREATE_MODE_ORGANIZER != eMode &&
/*N*/           SFX_CREATE_MODE_PREVIEW != eMode &&
/*N*/           !pDoc->GetDocShell()->IsPreview() )
/*N*/       {
/*N*/           ViewShell* pVSh = 0;
/*N*/             BOOL bAskUpdate = nLinkMode == MANUAL;
/*N*/             BOOL bUpdate = TRUE;
/*N*/             switch(nUpdateDocMode)
/*N*/             {
/*N*/                 case document::UpdateDocMode::NO_UPDATE:   bUpdate = FALSE;break;
/*N*/                 case document::UpdateDocMode::QUIET_UPDATE:bAskUpdate = FALSE; break;
/*N*/                 case document::UpdateDocMode::FULL_UPDATE: bAskUpdate = TRUE; break;
/*N*/ //                case document::UpdateDocMode::ACCORDING_TO_CONFIG:break;
/*N*/             }
/*N*/             if(bUpdate)
/*N*/             {
/*N*/                 SfxMedium* pMedium = pDoc->GetDocShell()->GetMedium();
/*N*/                 SfxFrame* pFrm = pMedium ? pMedium->GetLoadTargetFrame() : 0;
/*N*/                 Window* pDlgParent = pFrm ? &pFrm->GetWindow() : 0;
/*N*/                 if( pDoc->GetRootFrm() && !pDoc->GetEditShell( &pVSh ) && !pVSh )
/*N*/                 {
/*N*/                     ViewShell aVSh( *pDoc, 0, 0 );
/*N*/
/*N*/                     SET_CURR_SHELL( &aVSh );
/*N*/                     pDoc->GetLinkManager().UpdateAllLinks( bAskUpdate , TRUE, FALSE, pDlgParent );
/*N*/                 }
/*N*/                 else
/*N*/                     pDoc->GetLinkManager().UpdateAllLinks( bAskUpdate, TRUE, FALSE, pDlgParent );
/*N*/             }
/*N*/       }
/*N*/
/*N*/       eOld = (SwRedlineMode)(pDoc->GetRedlineMode() & ~REDLINE_IGNORE);
/*N*/
/*N*/       pDoc->SetFieldsDirty( FALSE );
/*N*/   }
/*N*/
/*N*/   pDoc->SetRedlineMode_intern( eOld );
/*N*/   pDoc->SetOle2Link( aOLELink );
/*N*/
/*N*/   if( pCrsr )                 // das Doc ist jetzt modifiziert
/*N*/       pDoc->SetModified();
/*N*/
/*N*/   if( po == ReadSw3 )         // am Sw3-Reader noch den pIo-Pointer "loeschen"
/*N*/       ((Sw3Reader*)po)->SetSw3Io( 0 );
/*N*/
/*N*/   po->SetReadUTF8( FALSE );
/*N*/   po->SetBlockMode( FALSE );
/*N*/   po->SetOrganizerMode( FALSE );
/*N*/     po->SetIgnoreHTMLComments( FALSE );
/*N*/   return nError;
/*N*/ }


/*
 * Konstruktoren, Destruktor
 */

// Initiales Einlesben


//STRIP001 SwReader::SwReader( SvStream& rStrm, const String& rFileName, SwDoc *pDoc )
//STRIP001  : SwDocFac( pDoc ),
//STRIP001  pStrm( &rStrm ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( 0 ),
//STRIP001  aFileName( rFileName ),
//STRIP001  pCrsr( 0 )
//STRIP001 {
//STRIP001 }


/*N*/ SwReader::SwReader( SvStorage& rStg, const String& rFileName, SwDoc *pDoc )
/*N*/   : SwDocFac( pDoc ),
/*N*/   pStrm( 0 ),
/*N*/   pStg( &rStg ),
/*N*/   pMedium( 0 ),
/*N*/   aFileName( rFileName ),
/*N*/   pCrsr( 0 )
/*N*/ {
/*N*/ }


//STRIP001 SwReader::SwReader( SfxMedium& rMedium, const String& rFileName, SwDoc *pDoc )
//STRIP001  : SwDocFac( pDoc ),
//STRIP001  pStrm( 0 ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( &rMedium ),
//STRIP001  aFileName( rFileName ),
//STRIP001  pCrsr( 0 )
//STRIP001 {
//STRIP001 }

// In ein existierendes Dokument einlesen

//STRIP001 SwReader::SwReader( SvStream& rStrm, const String& rFileName, SwPaM& rPam )
//STRIP001  : SwDocFac( rPam.GetDoc() ),
//STRIP001  aFileName( rFileName ),
//STRIP001  pStrm( &rStrm ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( 0 ),
//STRIP001  pCrsr( &rPam  )
//STRIP001 {
//STRIP001 }

//STRIP001 SwReader::SwReader( SvStorage& rStg, const String& rFileName, SwPaM& rPam )
//STRIP001  : SwDocFac( rPam.GetDoc() ),
//STRIP001  aFileName( rFileName ),
//STRIP001  pStg( &rStg ),
//STRIP001  pStrm( 0 ),
//STRIP001  pMedium( 0 ),
//STRIP001  pCrsr( &rPam )
//STRIP001 {
//STRIP001 }


//STRIP001 SwReader::SwReader( SfxMedium& rMedium, const String& rFileName, SwPaM& rPam )
//STRIP001  : SwDocFac( rPam.GetDoc() ),
//STRIP001  aFileName( rFileName ),
//STRIP001  pStg( 0 ),
//STRIP001  pStrm( 0 ),
//STRIP001  pMedium( &rMedium ),
//STRIP001  pCrsr( &rPam )
//STRIP001 {
//STRIP001 }


/*N*/ Reader::Reader()
/*N*/   : pStrm(0), pStg(0), pMedium(0), pTemplate(0),
/*N*/   bTmplBrowseMode( FALSE ), bInsertMode( FALSE ),
/*N*/   bReadUTF8( FALSE ), bBlockMode( FALSE ), bOrganizerMode( FALSE ),
/*N*/     bHasAskTemplateName( FALSE ), bIgnoreHTMLComments( FALSE )
/*N*/ {
/*N*/ }

/*N*/ Reader::~Reader()
/*N*/ {
/*N*/   delete pTemplate;
/*N*/ }

/*N*/ String Reader::GetTemplateName() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

// Die Filter-Vorlage laden, setzen und wieder freigeben
/*N*/ SwDoc* Reader::GetTemplateDoc()
/*N*/ {
/*N*/   if( !bHasAskTemplateName )
/*N*/   {
/*N*/       SetTemplateName( GetTemplateName() );
/*N*/       bHasAskTemplateName = TRUE;
/*N*/   }
/*N*/
/*N*/   if( !aTemplateNm.Len() )
/*N*/       ClearTemplate();
/*N*/   else
/*N*/   {
/*?*/       INetURLObject aTDir( so3::StaticBaseUrl::SmartRelToAbs(aTemplateNm) );
/*?*/       DateTime aCurrDateTime;
/*?*/       BOOL bLoad = FALSE;
/*?*/
/*?*/       // Wenn das Template schon mal geladen wurde, nur einmal pro
/*?*/       // Minute nachschauen, ob es geaendert wurde.
/*?*/       if( !pTemplate || aCurrDateTime >= aChkDateTime )
/*?*/       {
/*?*/           Date aTstDate;
/*?*/           Time aTstTime;
/*?*/           if( FStatHelper::GetModifiedDateTimeOfFile(
/*?*/                           aTDir.GetMainURL( INetURLObject::NO_DECODE ),
/*?*/                           &aTstDate, &aTstTime ) &&
/*?*/               ( !pTemplate || aDStamp != aTstDate || aTStamp != aTstTime ))
/*?*/           {
/*?*/               bLoad = TRUE;
/*?*/               aDStamp = aTstDate;
/*?*/               aTStamp = aTstTime;
/*?*/           }
/*?*/
/*?*/           // Erst in einer Minute wieder mal nachschauen, ob sich die
/*?*/           // Vorlage geaendert hat.
/*?*/           aChkDateTime = aCurrDateTime;
/*?*/           aChkDateTime += Time( 0L, 1L );
/*?*/       }
/*?*/
/*?*/       if( bLoad )
/*?*/       {
/*?*/           ClearTemplate();
/*?*/           ASSERT( !pTemplate, "Who holds the template doc?" );
/*?*/
/*?*/           SvStorageRef xStor( new SvStorage( aTDir.GetFull(), STREAM_READ ));
/*?*/           ULONG nFormat = xStor->GetFormat();
/*?*/           long nVersion = SOFFICE_FILEFORMAT_60;
/*?*/           switch( nFormat )
/*?*/           {
/*?*/           case SOT_FORMATSTR_ID_STARWRITER_50:
/*?*/           case SOT_FORMATSTR_ID_STARWRITERGLOB_50:
/*?*/           case SOT_FORMATSTR_ID_STARWRITERWEB_50:
/*?*/               nVersion = SOFFICE_FILEFORMAT_50;
/*?*/               break;
/*?*/           case SOT_FORMATSTR_ID_STARWRITER_40:
/*?*/           case SOT_FORMATSTR_ID_STARWRITERGLOB_40:
/*?*/           case SOT_FORMATSTR_ID_STARWRITERWEB_40:
/*?*/               nVersion = SOFFICE_FILEFORMAT_40;
/*?*/               break;
/*?*/           case SOT_FORMATSTR_ID_STARWRITER_30:
/*?*/               nVersion = SOFFICE_FILEFORMAT_31;
/*?*/               break;
/*?*/           }
/*?*/           if( nVersion >= SOFFICE_FILEFORMAT_60 )
/*?*/           {
/*?*/               // #95605#: If the writer module is not installed,
/*?*/               // we cannot create a SwDocShell. We could create a
/*?*/               // SwWebDocShell however, because this exists always
/*?*/               // for the help.
/*?*/               SvtModuleOptions aModuleOptions;
/*?*/               if( aModuleOptions.IsWriter() )
/*?*/               {
/*?*/                   SwDocShell *pDocSh =
/*?*/                       new SwDocShell ( SFX_CREATE_MODE_INTERNAL );
/*?*/                   SvEmbeddedObjectRef xDocSh = pDocSh;
/*?*/                   if( pDocSh->DoInitNew( 0 ) )
/*?*/                   {
/*?*/                       pTemplate = pDocSh->GetDoc();
/*?*/                       pTemplate->SetOle2Link( Link() );
/*?*/                       pTemplate->DoUndo( FALSE );     // always FALSE
/*?*/                       pTemplate->SetBrowseMode( bTmplBrowseMode );
/*?*/                       pTemplate->RemoveAllFmtLanguageDependencies();
/*?*/
/*?*/                       ReadXML->SetOrganizerMode( TRUE );
/*?*/                       SwReader aRdr( *xStor, aEmptyStr, pTemplate );
/*?*/                       aRdr.Read( *ReadXML );
/*?*/                       ReadXML->SetOrganizerMode( FALSE );
/*?*/
/*?*/                       pTemplate->AddLink();
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pTemplate = new SwDoc;
//STRIP001 /*?*/                pTemplate->AddLink();
//STRIP001 /*?*/
//STRIP001 /*?*/                // sicher ist sicher
//STRIP001 /*?*/                pTemplate->SetBrowseMode( bTmplBrowseMode );
//STRIP001 /*?*/                pTemplate->RemoveAllFmtLanguageDependencies();
//STRIP001 /*?*/
//STRIP001 /*?*/                xStor->SetVersion( nVersion );
//STRIP001 /*?*/
//STRIP001 /*?*/                Sw3Io aIO( *pTemplate );
//STRIP001 /*?*/                aIO.LoadStyles( xStor );
/*?*/           }
/*?*/       }
/*?*/
/*?*/       ASSERT( !pTemplate || FStatHelper::IsDocument(
/*?*/               aTDir.GetMainURL( INetURLObject::NO_DECODE ) ) ||
/*?*/               aTemplateNm.EqualsAscii( "$$Dummy$$" ),
/*?*/               "TemplatePtr but no template exist!" );
/*N*/   }
/*N*/
/*N*/   return pTemplate;
/*N*/ }

/*N*/ BOOL Reader::SetTemplate( SwDoc& rDoc )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   GetTemplateDoc();
/*N*/   if( pTemplate )
/*N*/   {
/*?*/       rDoc.RemoveAllFmtLanguageDependencies();
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rDoc.ReplaceStyles( *pTemplate );
//STRIP001 /*?*/        rDoc.SetFixFields();
//STRIP001 /*?*/        bRet = TRUE;
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

/*N*/ void Reader::ClearTemplate()
/*N*/ {
/*N*/   if( pTemplate )
/*N*/   {
/*?*/       if( 0 == pTemplate->RemoveLink() )
/*?*/           delete pTemplate,
/*?*/       pTemplate = 0;
/*N*/   }
/*N*/ }

/*N*/ void Reader::SetTemplateName( const String& rDir )
/*N*/ {
/*N*/   if( rDir.Len() && aTemplateNm != rDir )
/*N*/   {
/*?*/       ClearTemplate();
/*?*/       aTemplateNm = rDir;
/*N*/   }
/*N*/ }

//STRIP001 void Reader::MakeHTMLDummyTemplateDoc()
//STRIP001 {
//STRIP001  ClearTemplate();
//STRIP001  pTemplate = new SwDoc;
//STRIP001  pTemplate->AddLink();
//STRIP001  pTemplate->SetBrowseMode( bTmplBrowseMode );
//STRIP001  pTemplate->GetPrt( TRUE );
//STRIP001  pTemplate->RemoveAllFmtLanguageDependencies();
//STRIP001  aChkDateTime = Date( 1, 1, 2300 );  // 2300. Jahrtausend sollte reichen
//STRIP001  aTemplateNm.AssignAscii( "$$Dummy$$" );
//STRIP001 }

// alle die die Streams / Storages nicht geoeffnet brauchen,
// muessen die Methode ueberladen
//STRIP001 int Reader::SetStrmStgPtr()
//STRIP001 {
//STRIP001  ASSERT( pMedium, "Wo ist das Medium??" );
//STRIP001
//STRIP001  if( pMedium->IsStorage() )
//STRIP001  {
//STRIP001      if( SW_STORAGE_READER & GetReaderType() )
//STRIP001      {
//STRIP001          pStg = pMedium->GetStorage();
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else if( SW_STREAM_READER & GetReaderType() )
//STRIP001  {
//STRIP001      pStrm = pMedium->GetInStream();
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 int Reader::GetReaderType()
//STRIP001 {
//STRIP001  return SW_STREAM_READER;
//STRIP001 }


//STRIP001 void Reader::SetFltName( const String& )
//STRIP001 {
//STRIP001 }


//STRIP001 void Reader::SetNoOutlineNum( SwDoc& rDoc )
//STRIP001 {
//STRIP001  // JP 10.03.96: jetzt wieder keine Nummerierung in den Vorlagen
//STRIP001
//STRIP001 #if 0
//STRIP001  //JP 18.01.96: Alle Ueberschriften sind normalerweise ohne
//STRIP001  //              Kapitelnummer. Darum hier explizit abschalten
//STRIP001  //              weil das Default jetzt wieder auf AN ist.
//STRIP001  SwNumRules aRules( OUTLINE_RULES );
//STRIP001  if( rDoc.GetOutlineNumRules() )
//STRIP001      aRules = *rDoc.GetOutlineNumRules();
//STRIP001  for( BYTE n = 0; n < MAXLEVEL; ++n )
//STRIP001  {
//STRIP001      SwNumFmt aFmt( aRules.Get( n ) );
//STRIP001      aFmt.eType = NUMBER_NONE;
//STRIP001      aRules.Set( n, aFmt );
//STRIP001  }
//STRIP001  rDoc.SetOutlineNumRules( aRules );
//STRIP001
//STRIP001  // und UeberschirftBasis ohne Einrueckung!
//STRIP001  SwTxtFmtColl* pCol = rDoc.GetTxtCollFromPoolSimple
//STRIP001         ( RES_POOLCOLL_HEADLINE_BASE, FALSE );
//STRIP001  pCol->ResetAttr( RES_LR_SPACE );
//STRIP001 #endif
//STRIP001 }


//STRIP001 void Reader::ResetFrmFmtAttrs( SfxItemSet &rFrmSet )
//STRIP001 {
//STRIP001  rFrmSet.Put( SvxLRSpaceItem() );
//STRIP001  rFrmSet.Put( SvxULSpaceItem() );
//STRIP001  rFrmSet.Put( SvxBoxItem() );
//STRIP001 }


//STRIP001 void Reader::ResetFrmFmts( SwDoc& rDoc )
//STRIP001 {
//STRIP001  for( USHORT i=0; i<3; i++ )
//STRIP001  {
//STRIP001      USHORT nPoolId;
//STRIP001      switch( i )
//STRIP001      {
//STRIP001      case 0: nPoolId = RES_POOLFRM_FRAME;    break;
//STRIP001      case 1: nPoolId = RES_POOLFRM_GRAPHIC;  break;
//STRIP001      case 2: nPoolId = RES_POOLFRM_OLE;      break;
//STRIP001      }
//STRIP001
//STRIP001      SwFrmFmt *pFrmFmt = rDoc.GetFrmFmtFromPool( nPoolId );
//STRIP001
//STRIP001      pFrmFmt->ResetAttr( RES_LR_SPACE );
//STRIP001      pFrmFmt->ResetAttr( RES_UL_SPACE );
//STRIP001      pFrmFmt->ResetAttr( RES_BOX );
//STRIP001  }
//STRIP001 }

    // read the sections of the document, which is equal to the medium.
    // returns the count of it
//STRIP001 USHORT Reader::GetSectionList( SfxMedium&, SvStrings& ) const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

// ------------------------------------------------
//STRIP001 BOOL SwReader::HasGlossaries( const Reader& rOptions )
//STRIP001 {
//STRIP001  // Variable uebertragen
//STRIP001  Reader* po = (Reader*) &rOptions;
//STRIP001  po->pStrm = pStrm;
//STRIP001  po->pStg  = pStg;
//STRIP001  po->bInsertMode = FALSE;
//STRIP001
//STRIP001  // ist ein Medium angegeben, dann aus diesem die Streams besorgen
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( !( 0 != (po->pMedium = pMedium ) && !po->SetStrmStgPtr() ))
//STRIP001      bRet = po->HasGlossaries();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwReader::ReadGlossaries( const Reader& rOptions,
//STRIP001                              SwTextBlocks& rBlocks, BOOL bSaveRelFiles )
//STRIP001 {
//STRIP001  // Variable uebertragen
//STRIP001  Reader* po = (Reader*) &rOptions;
//STRIP001  po->pStrm = pStrm;
//STRIP001  po->pStg  = pStg;
//STRIP001  po->bInsertMode = FALSE;
//STRIP001
//STRIP001  // ist ein Medium angegeben, dann aus diesem die Streams besorgen
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( !( 0 != (po->pMedium = pMedium ) && !po->SetStrmStgPtr() ))
//STRIP001      bRet = po->ReadGlossaries( rBlocks, bSaveRelFiles );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL Reader::HasGlossaries() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL Reader::ReadGlossaries( SwTextBlocks&, BOOL ) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

// ------------------------------------------------

//STRIP001 int StgReader::GetReaderType()
//STRIP001 {
//STRIP001  return SW_STORAGE_READER;
//STRIP001 }




/*
 * Writer
 */

/*
 * Konstruktoren, Destruktoren sind inline (inc/shellio.hxx).
 */


//STRIP001 SwWriter::SwWriter( SvStream& rStrm, SwCrsrShell &rShell, BOOL bWriteAll )
//STRIP001  : pStrm( &rStrm ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( 0 ),
//STRIP001  pShell( &rShell ),
//STRIP001  pOutPam( 0 ),
//STRIP001  rDoc( *rShell.GetDoc() ),
//STRIP001  bWriteAll( bWriteAll )
//STRIP001 {
//STRIP001 }


//STRIP001 SwWriter::SwWriter(SvStream& rStrm,SwDoc &rDoc)
//STRIP001  :pStrm( &rStrm ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( 0 ),
//STRIP001  pShell( 0 ),
//STRIP001  pOutPam( 0 ),
//STRIP001  rDoc( rDoc ),
//STRIP001  bWriteAll( TRUE )
//STRIP001 {
//STRIP001 }


/*N*/ SwWriter::SwWriter( SvStream& rStrm, SwPaM& rPam, BOOL bWriteAll )
/*N*/   : pStrm( &rStrm ),
/*N*/   pStg( 0 ),
/*N*/   pMedium( 0 ),
/*N*/   pShell( 0 ),
/*N*/   pOutPam( &rPam ),
/*N*/   rDoc( *rPam.GetDoc() ),
/*N*/   bWriteAll( bWriteAll )
/*N*/ {
/*N*/ }

/*

SwWriter::SwWriter( SvStorage& rStg, SwCrsrShell &rShell, BOOL bWriteAll )
    : pStrm( 0 ),
    pStg( &rStg ),
    pMedium( 0 ),
    pShell( &rShell ),
    pOutPam( 0 ),
    rDoc( *rShell.GetDoc() ),
    bWriteAll( bWriteAll )
{
}
*/


/*N*/ SwWriter::SwWriter(SvStorage& rStg,SwDoc &rDoc)
/*N*/   :pStrm( 0 ),
/*N*/   pStg( &rStg ),
/*N*/   pMedium( 0 ),
/*N*/   pShell( 0 ),
/*N*/   pOutPam( 0 ),
/*N*/   rDoc( rDoc ),
/*N*/   bWriteAll( TRUE )
/*N*/ {
/*N*/ }
/*

SwWriter::SwWriter( SvStorage& rStg, SwPaM& rPam, BOOL bWriteAll )
    : pStrm( 0 ),
    pStg( &rStg ),
    pMedium( 0 ),
    pShell( 0 ),
    pOutPam( &rPam ),
    rDoc( *rPam.GetDoc() ),
    bWriteAll( bWriteAll )
{
}
*/

//STRIP001 SwWriter::SwWriter( SfxMedium& rMedium, SwCrsrShell &rShell, BOOL bWriteAll )
//STRIP001  : pStrm( 0 ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( &rMedium ),
//STRIP001  pShell( &rShell ),
//STRIP001  pOutPam( 0 ),
//STRIP001  rDoc( *rShell.GetDoc() ),
//STRIP001  bWriteAll( bWriteAll )
//STRIP001 {
//STRIP001 }


//STRIP001 SwWriter::SwWriter( SfxMedium& rMedium, SwDoc &rDoc)
//STRIP001  :pStrm( 0 ),
//STRIP001  pStg( 0 ),
//STRIP001  pMedium( &rMedium ),
//STRIP001  pShell( 0 ),
//STRIP001  pOutPam( 0 ),
//STRIP001  rDoc( rDoc ),
//STRIP001  bWriteAll( TRUE )
//STRIP001 {
//STRIP001 }

/*

SwWriter::SwWriter( SfxMedium& rMedium, SwPaM& rPam, BOOL bWriteAll )
    : pStrm( 0 ),
    pStg( 0 ),
    pShell( 0 ),
    pMedium( &rMedium ),
    pOutPam( &rPam ),
    rDoc( *rPam.GetDoc() ),
    bWriteAll( bWriteAll )
{
}
*/


/*N*/ ULONG SwWriter::Write( WriterRef& rxWriter, const String* pRealFileName )
/*N*/ {
/*N*/   BOOL bHasMark = FALSE;
/*N*/   SwPaM * pPam;
/*N*/
/*N*/   SwDoc *pDoc = 0L;
/*N*/     SvEmbeddedObjectRef* pRefForDocSh = 0;
/*N*/
/*N*/   if ( pShell && !bWriteAll && pShell->IsTableMode() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 bWriteAll = TRUE;
//STRIP001 /*?*/        pDoc = new SwDoc;
//STRIP001 /*?*/        pDoc->AddLink();
//STRIP001 /*?*/         pRefForDocSh = new SvEmbeddedObjectRef();
//STRIP001 /*?*/         pDoc->SetRefForDocShell( pRefForDocSh );
//STRIP001 /*?*/
//STRIP001 /*?*/        // kopiere Teile aus einer Tabelle: lege eine Tabelle mit der Breite
//STRIP001 /*?*/        // von der Originalen an und kopiere die selectierten Boxen.
//STRIP001 /*?*/        // Die Groessen werden prozentual korrigiert.
//STRIP001 /*?*/
//STRIP001 /*?*/        // lasse ueber das Layout die Boxen suchen
//STRIP001 /*?*/        SwSelBoxes aBoxes;
//STRIP001 /*?*/        GetTblSel( *pShell, aBoxes );
//STRIP001 /*?*/        SwTableNode* pTblNd = (SwTableNode*)aBoxes[0]->GetSttNd()->FindStartNode();
//STRIP001 /*?*/        SwNodeIndex aIdx( pDoc->GetNodes().GetEndOfExtras(), 2 );
//STRIP001 /*?*/        SwCntntNode *pNd = aIdx.GetNode().GetCntntNode();
//STRIP001 /*?*/        ASSERT( pNd, "Node not found" );
//STRIP001 /*?*/        SwPosition aPos( aIdx, SwIndex( pNd ) );
//STRIP001 /*?*/        pTblNd->GetTable().MakeCopy( pDoc, aPos, aBoxes );
/*N*/   }
/*N*/
/*N*/   if( !bWriteAll && ( pShell || pOutPam ))
/*N*/   {
/*N*/       if( pShell )
/*?*/           pPam = pShell->GetCrsr();
/*N*/       else
/*N*/           pPam = pOutPam;
/*N*/
/*N*/       SwPaM *pEnd = pPam;
/*N*/
/*N*/       // Erste Runde: Nachsehen, ob eine Selektion besteht.
/*N*/       while(TRUE)
/*N*/       {
/*N*/           bHasMark = bHasMark || pPam->HasMark();
/*N*/           pPam = (SwPaM *) pPam->GetNext();
/*N*/           if(bHasMark || pPam == pEnd)
/*N*/               break;
/*N*/       }
/*N*/
/*N*/       // Wenn keine Selektion besteht, eine ueber das ganze Dokument aufspannen.
/*N*/       if(!bHasMark)
/*N*/       {
/*?*/           if( pShell )
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pShell->Push();
//STRIP001 /*?*/                pShell->SttDoc();
//STRIP001 /*?*/                pShell->SetMark();
//STRIP001 /*?*/                pShell->EndDoc();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               pPam = new SwPaM( *pPam );
/*?*/               pPam->Move( fnMoveBackward, fnGoDoc );
/*?*/               pPam->SetMark();
/*?*/               pPam->Move( fnMoveForward, fnGoDoc );
/*?*/           }
/*N*/       }
/*N*/       // pPam ist immer noch der akt. Cursor !!
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // keine Shell oder alles schreiben -> eigenen Pam erzeugen
/*N*/       SwDoc* pOutDoc = pDoc ? pDoc : &rDoc;
/*N*/       pPam = new SwPaM( pOutDoc->GetNodes().GetEndOfContent() );
/*N*/       pPam->Move( fnMoveBackward, fnGoDoc );
/*N*/       pPam->SetMark();
/*N*/       pPam->Move( fnMoveForward, fnGoDoc );
/*N*/   }
/*N*/
/*N*/   rxWriter->bWriteAll = bWriteAll;
/*N*/   SwDoc* pOutDoc = pDoc ? pDoc : &rDoc;
/*N*/
/*N*/   // falls der Standart PageDesc. immer noch auf initalen Werten steht
/*N*/   // (wenn z.B. kein Drucker gesetzt wurde) dann setze jetzt auf DIN A4
/*N*/   if( !pOutDoc->GetPrt() )
/*N*/   {
/*?*/       const SwPageDesc& rPgDsc = pOutDoc->GetPageDesc( 0L );
/*?*/       //const SwPageDesc& rPgDsc = *pOutDoc->GetPageDescFromPool( RES_POOLPAGE_STANDARD );;
/*?*/       const SwFmtFrmSize& rSz = rPgDsc.GetMaster().GetFrmSize();
/*?*/       // Clipboard-Dokument wird immer ohne Drucker angelegt, so ist
/*?*/       // der Std.PageDesc immer aug LONG_MAX !! Mappe dann auf DIN A4
/*?*/       if( LONG_MAX == rSz.GetHeight() || LONG_MAX == rSz.GetWidth() )
/*?*/       {
/*?*/           SwPageDesc aNew( rPgDsc );
/*?*/           SwFmtFrmSize aNewSz( rSz );
/*?*/           aNewSz.SetHeight( lA4Height );
/*?*/           aNewSz.SetWidth( lA4Width );
/*?*/           aNew.GetMaster().SetAttr( aNewSz );
/*?*/           pOutDoc->ChgPageDesc( 0, aNew );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   SwEditShell* pESh = pOutDoc->GetEditShell();
/*N*/   if( pESh )
/*N*/       pESh->StartAllAction();
/*N*/
/*N*/   BOOL bWasPurgeOle = pOutDoc->IsPurgeOLE();
/*N*/   pOutDoc->SetPurgeOLE( FALSE );
/*N*/
/*N*/   ULONG nError = 0;
/*N*/   if( pMedium )
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     nError = rxWriter->Write( *pPam, *pMedium, pRealFileName );
/*N*/   else if( pStg )
/*N*/       nError = rxWriter->Write( *pPam, *pStg, pRealFileName );
/*N*/   else if( pStrm )
/*N*/       nError = rxWriter->Write( *pPam, *pStrm, pRealFileName );
/*N*/
/*N*/   pOutDoc->SetPurgeOLE( bWasPurgeOle );
/*N*/   if( pESh )
/*N*/       pESh->EndAllAction();
/*N*/
/*N*/   // Falls nur zum Schreiben eine Selektion aufgespannt wurde, vor der
/*N*/   // Rueckkehr den alten Crsr wieder herstellen.
/*N*/   if( !bWriteAll && ( pShell || pOutPam ))
/*N*/   {
/*N*/       if(!bHasMark)
/*N*/       {
/*?*/           if( pShell )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pShell->Pop( FALSE );
/*?*/           else
/*?*/               delete pPam;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       delete pPam;            // loesche den hier erzeugten Pam
/*N*/       // Alles erfolgreich geschrieben? Sag' das dem Dokument!
/*N*/       if( !IsError( nError ) && !pDoc )
/*N*/           rDoc.ResetModified();
/*N*/   }
/*N*/
/*N*/   if ( pDoc )
/*N*/   {
/*N*/         delete pRefForDocSh;
/*?*/       if ( !pDoc->RemoveLink() )
/*?*/           delete pDoc;
/*?*/       bWriteAll = FALSE;
/*N*/   }
/*N*/
/*N*/   return nError;
/*N*/ }


/*  */

// ----------------------------------------------------------------------


/*N*/ BOOL SetHTMLTemplate( SwDoc & rDoc )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 //STRIP001   // Vorlagennamen von den Sfx-HTML-Filter besorgen!!!
//STRIP001  if( !ReadHTML->GetTemplateDoc() )
//STRIP001      ReadHTML->MakeHTMLDummyTemplateDoc();
//STRIP001
//STRIP001  BOOL bRet = ReadHTML->SetTemplate( rDoc );
//STRIP001
//STRIP001  SwNodes& rNds = rDoc.GetNodes();
//STRIP001  SwNodeIndex aIdx( rNds.GetEndOfExtras(), 1 );
//STRIP001  SwCntntNode* pCNd = rNds.GoNext( &aIdx );
//STRIP001  if( pCNd )
//STRIP001  {
//STRIP001      pCNd->SetAttr
//STRIP001             ( SwFmtPageDesc(rDoc.GetPageDescFromPoolSimple(RES_POOLPAGE_HTML,
//STRIP001                                                            FALSE) ) );
//STRIP001      pCNd->ChgFmtColl( rDoc.GetTxtCollFromPoolSimple( RES_POOLCOLL_TEXT,
//STRIP001                                                          FALSE ));
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
/*N*/ }


}
