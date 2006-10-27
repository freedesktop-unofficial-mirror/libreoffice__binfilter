/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edws.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:35:33 $
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


/******************************************************************************
 *                    void SwEditShell::SetModified()
 ******************************************************************************/


/******************************************************************************
 *                   void SwEditShell::ResetModified()
 ******************************************************************************/


/*N*/ void SwEditShell::ResetModified()
/*N*/ {
/*N*/   GetDoc()->ResetModified();
/*N*/ }


/******************************************************************************
 *                    void SwEditShell::StartAction()
 ******************************************************************************/


/******************************************************************************
 *                    void SwEditShell::EndAction()
 ******************************************************************************/


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



/******************************************************************************
 *              Zugriffsfunktionen fuer Filename-Behandlung
 ******************************************************************************/





/******************************************************************************
 *          Klasse fuer den automatisierten Aufruf von Start- und
 *                              EndCrsrMove();
 ******************************************************************************/






/*N*/ SwFrmFmt *SwEditShell::GetTableFmt()  // OPT: schnellster Test auf Tabelle?
/*N*/ {
/*N*/   const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/   return pTblNd ? (SwFrmFmt*)pTblNd->GetTable().GetFrmFmt() : 0;
/*N*/ }

// OPT: wieso 3x beim neuen Dokument







/*N*/ void SwEditShell::DoUndo( sal_Bool bOn )
/*N*/ { GetDoc()->DoUndo( bOn ); }









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





// AutoKorrektur - JP 27.01.94








}
