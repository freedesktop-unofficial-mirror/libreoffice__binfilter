/*************************************************************************
 *
 *  $RCSfile: sw_edws.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:23:11 $
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


#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #ifndef _ACORRECT_HXX
// auto strip #include <acorrect.hxx>
// auto strip #endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>
// auto strip #endif
namespace binfilter {

/********************************************************
 * Ctor/Dtor
 ********************************************************/
// verkleideter Copy-Constructor


/*N*/ SwEditShell::SwEditShell( SwEditShell& rEdSH, Window *pWin )
/*N*/   : SwCrsrShell( rEdSH, pWin )
/*N*/ {
/*N*/ }

// ctor/dtor


/*N*/ SwEditShell::SwEditShell( SwDoc& rDoc, Window *pWin, SwRootFrm *pRootFrm,
/*N*/                           const SwViewOption *pOpt )
/*N*/   : SwCrsrShell( rDoc, pWin, pRootFrm, pOpt)
/*N*/ {
/*N*/   GetDoc()->DoUndo();
/*N*/ }


/*N*/ SwEditShell::~SwEditShell() // USED
/*N*/ {
/*N*/ }

/******************************************************************************
 *                  sal_Bool SwEditShell::IsModified() const
 ******************************************************************************/


//STRIP001 sal_Bool SwEditShell::IsModified() const
//STRIP001 {
//STRIP001  return GetDoc()->IsModified();
//STRIP001 }
/******************************************************************************
 *                    void SwEditShell::SetModified()
 ******************************************************************************/


//STRIP001 void SwEditShell::SetModified()
//STRIP001 {
//STRIP001  GetDoc()->SetModified();
//STRIP001 }
/******************************************************************************
 *                   void SwEditShell::ResetModified()
 ******************************************************************************/


/*N*/ void SwEditShell::ResetModified()
/*N*/ {
/*N*/   GetDoc()->ResetModified();
/*N*/ }

//STRIP001 void SwEditShell::SetUndoNoResetModified()
//STRIP001 {
//STRIP001  GetDoc()->SetModified();
//STRIP001  GetDoc()->SetUndoNoResetModified();
//STRIP001 }

//STRIP001 #ifdef USED
/******************************************************************************
 *                    void SwEditShell::StartAction()
 ******************************************************************************/


//STRIP001 void SwEditShell::StartAction()  // OPT: ganz wech
//STRIP001 {
//STRIP001  SwCrsrShell::StartAction();
//STRIP001 }
/******************************************************************************
 *                    void SwEditShell::EndAction()
 ******************************************************************************/


//STRIP001 void SwEditShell::EndAction()
//STRIP001 {
//STRIP001  SwCrsrShell::EndAction();
//STRIP001 }
//STRIP001 #endif
/******************************************************************************
 *                 void SwEditShell::StartAllAction()
 ******************************************************************************/


/*N*/ void SwEditShell::StartAllAction()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do {
/*N*/       if( pSh->IsA( TYPE( SwEditShell ) ) )
/*N*/           ((SwEditShell*)pSh)->StartAction();
/*N*/       else
/*?*/           pSh->StartAction();
/*N*/       pSh = (ViewShell *)pSh->GetNext();
/*N*/   } while(pSh != this);
/*N*/ }
/******************************************************************************
 *                  void SwEditShell::EndAllAction()
 ******************************************************************************/


/*N*/ void SwEditShell::EndAllAction()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do {
/*N*/       if( pSh->IsA( TYPE( SwEditShell ) ) )
/*N*/           ((SwEditShell*)pSh)->EndAction();
/*N*/       else
/*?*/           pSh->EndAction();
/*N*/       pSh = (ViewShell *)pSh->GetNext();
/*N*/   } while(pSh != this);
/*N*/ }

/******************************************************************************
 *                  void SwEditShell::CalcLayout()
 ******************************************************************************/


/*N*/ void SwEditShell::CalcLayout()
/*N*/ {
/*N*/   StartAllAction();
/*N*/   ViewShell::CalcLayout();
/*N*/
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {
/*N*/       if ( pSh->GetWin() )
/*N*/           pSh->GetWin()->Invalidate();
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/
/*N*/   EndAllAction();
/*N*/ }

/******************************************************************************
 *                      Inhaltsform bestimmen, holen
 ******************************************************************************/
// OPT: wird fuer jedes Attribut gerufen?


/*N*/ sal_uInt16 SwEditShell::GetCntType() const
/*N*/ {
/*N*/   // nur noch am SPoint ist der Inhalt interessant
/*N*/   sal_uInt16 nRet = 0;
/*N*/   if( IsTableMode() )
/*?*/       nRet = CNT_TXT;
/*N*/   else
/*N*/       switch( GetCrsr()->GetNode()->GetNodeType() )
/*N*/       {
/*N*/       case ND_TEXTNODE:   nRet = CNT_TXT; break;
/*?*/       case ND_GRFNODE:    nRet = CNT_GRF; break;
/*?*/       case ND_OLENODE:    nRet = CNT_OLE; break;
/*N*/       }
/*N*/
/*N*/   ASSERT( nRet, ERR_OUTOFSCOPE );
/*N*/   return nRet;
/*N*/ }

//------------------------------------------------------------------------------


//STRIP001 sal_Bool SwEditShell::HasOtherCnt() const
//STRIP001 {
//STRIP001  const SwNodes &rNds = GetDoc()->GetNodes();
//STRIP001  const SwNode *pNd;
//STRIP001  return GetDoc()->GetSpzFrmFmts()->Count() ||
//STRIP001          1 != (( pNd = &rNds.GetEndOfInserts() )->GetIndex() -
//STRIP001              pNd->StartOfSectionIndex() ) ||
//STRIP001          1 != (( pNd = &rNds.GetEndOfAutotext() )->GetIndex() -
//STRIP001              pNd->StartOfSectionIndex() );
//STRIP001 }

/******************************************************************************
 *              Zugriffsfunktionen fuer Filename-Behandlung
 ******************************************************************************/


//STRIP001 SwActKontext::SwActKontext(SwEditShell *pShell)
//STRIP001  : pSh(pShell)
//STRIP001 {
//STRIP001  pSh->StartAction();
//STRIP001 }


//STRIP001 SwActKontext::~SwActKontext()
//STRIP001 {
//STRIP001  pSh->EndAction();
//STRIP001 }

/******************************************************************************
 *          Klasse fuer den automatisierten Aufruf von Start- und
 *                              EndCrsrMove();
 ******************************************************************************/


//STRIP001 SwMvKontext::SwMvKontext(SwEditShell *pShell ) : pSh(pShell)
//STRIP001 {
//STRIP001  pSh->SttCrsrMove();
//STRIP001 }


//STRIP001 SwMvKontext::~SwMvKontext()
//STRIP001 {
//STRIP001  pSh->EndCrsrMove();
//STRIP001 }


/*N*/ SwFrmFmt *SwEditShell::GetTableFmt()  // OPT: schnellster Test auf Tabelle?
/*N*/ {
/*N*/   const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/   return pTblNd ? (SwFrmFmt*)pTblNd->GetTable().GetFrmFmt() : 0;
/*N*/ }

// OPT: wieso 3x beim neuen Dokument


//STRIP001 sal_uInt16 SwEditShell::GetTOXTypeCount(TOXTypes eTyp) const
//STRIP001 {
//STRIP001  return pDoc->GetTOXTypeCount(eTyp);
//STRIP001 }


//STRIP001 void SwEditShell::InsertTOXType(const SwTOXType& rTyp)
//STRIP001 {
//STRIP001  pDoc->InsertTOXType(rTyp);
//STRIP001 }



/*N*/ void SwEditShell::DoUndo( sal_Bool bOn )
/*N*/ { GetDoc()->DoUndo( bOn ); }


//STRIP001 sal_Bool SwEditShell::DoesUndo() const
//STRIP001 { return GetDoc()->DoesUndo(); }


//STRIP001 void SwEditShell::DoGroupUndo( sal_Bool bOn )
//STRIP001 { GetDoc()->DoGroupUndo( bOn ); }


//STRIP001 sal_Bool SwEditShell::DoesGroupUndo() const
//STRIP001 { return GetDoc()->DoesGroupUndo(); }


//STRIP001 void SwEditShell::DelAllUndoObj()
//STRIP001 {
//STRIP001  GetDoc()->DelAllUndoObj();
//STRIP001 }

// Zusammenfassen von Kontinuierlichen Insert/Delete/Overwrite von
// Charaktern. Default ist sdbcx::Group-Undo.

// setzt Undoklammerung auf, liefert nUndoId der Klammerung


/*N*/ sal_uInt16 SwEditShell::StartUndo( sal_uInt16 nUndoId )
/*N*/ { return GetDoc()->StartUndo( nUndoId ); }

// schliesst Klammerung der nUndoId, nicht vom UI benutzt


/*N*/ sal_uInt16 SwEditShell::EndUndo(sal_uInt16 nUndoId)
/*N*/ { return GetDoc()->EndUndo(nUndoId); }

// liefert die Id der letzten undofaehigen Aktion zurueck
// fuellt ggf. VARARR mit sdbcx::User-UndoIds


/*N*/ sal_uInt16 SwEditShell::GetUndoIds(String* pStr,SwUndoIds *pUndoIds) const
/*N*/ { return GetDoc()->GetUndoIds(pStr,pUndoIds); }

// liefert die Id der letzten Redofaehigen Aktion zurueck
// fuellt ggf. VARARR mit RedoIds


/*N*/ sal_uInt16 SwEditShell::GetRedoIds(String* pStr,SwUndoIds *pRedoIds) const
/*N*/ { return GetDoc()->GetRedoIds(pStr,pRedoIds); }

// liefert die Id der letzten Repeatfaehigen Aktion zurueck
// fuellt ggf. VARARR mit RedoIds


//STRIP001 sal_uInt16 SwEditShell::GetRepeatIds(String* pStr, SwUndoIds *pRedoIds) const
//STRIP001 { return GetDoc()->GetRepeatIds(pStr,pRedoIds); }



// AutoKorrektur - JP 27.01.94
//STRIP001 void SwEditShell::AutoCorrect( SvxAutoCorrect& rACorr, sal_Bool bInsert,
//STRIP001                              sal_Unicode cChar )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  SwTxtNode* pTNd = pCrsr->GetNode()->GetTxtNode();
//STRIP001
//STRIP001  SwAutoCorrDoc aSwAutoCorrDoc( *this, *pCrsr, cChar );
//STRIP001  rACorr.AutoCorrect( aSwAutoCorrDoc,
//STRIP001                  pTNd->GetTxt(), pCrsr->GetPoint()->nContent.GetIndex(),
//STRIP001                  cChar, bInsert );
//STRIP001  if( cChar )
//STRIP001      SaveTblBoxCntnt( pCrsr->GetPoint() );
//STRIP001  EndAllAction();
//STRIP001 }


//STRIP001 void SwEditShell::SetNewDoc(sal_Bool bNew)
//STRIP001 {
//STRIP001  GetDoc()->SetNewDoc(bNew);
//STRIP001 }


//STRIP001 sal_Bool SwEditShell::GetPrevAutoCorrWord( SvxAutoCorrect& rACorr, String& rWord )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  sal_Bool bRet;
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  xub_StrLen nPos = pCrsr->GetPoint()->nContent.GetIndex();
//STRIP001  SwTxtNode* pTNd = pCrsr->GetNode()->GetTxtNode();
//STRIP001  if( pTNd && nPos )
//STRIP001  {
//STRIP001      SwAutoCorrDoc aSwAutoCorrDoc( *this, *pCrsr, 0 );
//STRIP001      bRet = rACorr.GetPrevAutoCorrWord( aSwAutoCorrDoc,
//STRIP001                                          pTNd->GetTxt(), nPos, rWord );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = sal_False;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 SwAutoCompleteWord& SwEditShell::GetAutoCompleteWords()
//STRIP001 {
//STRIP001  return SwDoc::GetAutoCompleteWords();
//STRIP001 }



}
