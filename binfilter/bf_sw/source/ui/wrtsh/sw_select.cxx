/*************************************************************************
 *
 *  $RCSfile: sw_select.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:58:55 $
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

#ifndef _SFX_BINDINGS_HXX //autogen
#include <bf_sfx2/bindings.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _SVX_SCRIPTTYPEITEM_HXX
#include <bf_svx/scripttypeitem.hxx>
#endif


#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _BASESH_HXX
#include <basesh.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _INITUI_HXX
#include <initui.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>                   // fuer Undo-Ids
#endif
#ifndef _SWEVENT_HXX
#include <swevent.hxx>
#endif
#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif

#if OSL_DEBUG_LEVEL > 1
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#endif
namespace binfilter {

namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }

using namespace ::com::sun::star::util;


static long nStartDragX = 0, nStartDragY = 0;
static BOOL  bStartDrag = FALSE;

//STRIP001 BOOL SwWrtShell::SelNearestWrd()
//STRIP001 {
//STRIP001  MV_KONTEXT(this);
//STRIP001  if( !IsInWrd() && !IsEndWrd() && !IsSttWrd() )
//STRIP001      PrvWrd();
//STRIP001  if( IsEndWrd() )
//STRIP001      Left(CRSR_SKIP_CELLS, FALSE, 1, FALSE );
//STRIP001  return SelWrd();
//STRIP001 }



//STRIP001 BOOL SwWrtShell::SelWrd(const Point *pPt, BOOL )
//STRIP001 {
//STRIP001  BOOL bRet;
//STRIP001  {
//STRIP001      MV_KONTEXT(this);
//STRIP001      SttSelect();
//STRIP001      bRet = SwCrsrShell::SelectWord( pPt );
//STRIP001  }
//STRIP001  EndSelect();
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      bSelWrd = TRUE;
//STRIP001      if(pPt)
//STRIP001          aStart = *pPt;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*
BOOL SwWrtShell::SelSentence(const Point *pPt, BOOL )
{
    {
        MV_KONTEXT(this);
        ClearMark();
        if(!_BwdSentence()) {
            return FALSE;
        }
        SttSelect();
        if(!_FwdSentence()) {
            EndSelect();
            return FALSE;
        }
    }
    EndSelect();
    return TRUE;
}

*/



//STRIP001 void SwWrtShell::SelLine(const Point *pPt, BOOL )
//STRIP001 {
//STRIP001  {
//STRIP001      MV_KONTEXT(this);
//STRIP001      ClearMark();
//STRIP001      SwCrsrShell::LeftMargin();
//STRIP001      SttSelect();
//STRIP001      SwCrsrShell::RightMargin();
//STRIP001  }
//STRIP001  EndSelect();
//STRIP001  if(pPt)
//STRIP001      aStart = *pPt;
//STRIP001  bSelLn = TRUE;
//STRIP001  bSelWrd = FALSE;    // SelWord abschalten, sonst geht kein SelLine weiter
//STRIP001 }



//STRIP001 long SwWrtShell::SelAll()
//STRIP001 {
//STRIP001     const BOOL bLockedView = IsViewLocked();
//STRIP001     LockView( TRUE );
//STRIP001
//STRIP001     {
//STRIP001      MV_KONTEXT(this);
//STRIP001      BOOL bMoveTable = FALSE;
//STRIP001      if( !HasWholeTabSelection() )
//STRIP001      {
//STRIP001          if ( IsSelection() && IsCrsrPtAtEnd() )
//STRIP001              SwapPam();
//STRIP001          Push();
//STRIP001          BOOL bIsFullSel = !MoveSection( fnSectionCurr, fnSectionStart);
//STRIP001          SwapPam();
//STRIP001          bIsFullSel &= !MoveSection( fnSectionCurr, fnSectionEnd);
//STRIP001          Pop(FALSE);
//STRIP001          GoStart(TRUE, &bMoveTable, FALSE, !bIsFullSel);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          EnterStdMode();
//STRIP001          SwCrsrShell::SttDoc();
//STRIP001      }
//STRIP001      SttSelect();
//STRIP001      GoEnd(TRUE, &bMoveTable);
//STRIP001  }
//STRIP001  EndSelect();
//STRIP001
//STRIP001     LockView( bLockedView );
//STRIP001
//STRIP001  return 1;
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Textsuche
------------------------------------------------------------------------*/


//STRIP001 ULONG SwWrtShell::SearchPattern( const SearchOptions& rSearchOpt,
//STRIP001                              SwDocPositions eStt, SwDocPositions eEnd,
//STRIP001                              FindRanges eFlags, int bReplace )
//STRIP001 {
//STRIP001      // keine Erweiterung bestehender Selektionen
//STRIP001  if(!(eFlags & FND_IN_SEL))
//STRIP001      ClearMark();
//STRIP001     BOOL bCancel = FALSE;
//STRIP001     ULONG nRet = Find( rSearchOpt, eStt, eEnd, bCancel, eFlags, bReplace );
//STRIP001     if(bCancel)
//STRIP001     {
//STRIP001         Undo(0, 1);
//STRIP001         nRet = ULONG_MAX;
//STRIP001     }
//STRIP001     return nRet;
//STRIP001 }
/*------------------------------------------------------------------------
 Beschreibung:  Suche nach Vorlagen
------------------------------------------------------------------------*/



//STRIP001 ULONG SwWrtShell::SearchTempl( const String &rTempl,
//STRIP001                             SwDocPositions eStt, SwDocPositions eEnd,
//STRIP001                             FindRanges eFlags, const String* pReplTempl )
//STRIP001 {
//STRIP001      // keine Erweiterung bestehender Selektionen
//STRIP001  if(!(eFlags & FND_IN_SEL))
//STRIP001      ClearMark();
//STRIP001  SwTxtFmtColl *pColl = GetParaStyle(rTempl, SwWrtShell::GETSTYLE_CREATESOME);
//STRIP001  SwTxtFmtColl *pReplaceColl = 0;
//STRIP001  if( pReplTempl )
//STRIP001      pReplaceColl = GetParaStyle(*pReplTempl, SwWrtShell::GETSTYLE_CREATESOME );
//STRIP001
//STRIP001     BOOL bCancel = FALSE;
//STRIP001     ULONG nRet = Find(pColl? *pColl: GetDfltTxtFmtColl(),
//STRIP001                             eStt,eEnd, bCancel, eFlags, pReplaceColl);
//STRIP001     if(bCancel)
//STRIP001     {
//STRIP001         Undo(0, 1);
//STRIP001         nRet = ULONG_MAX;
//STRIP001     }
//STRIP001  return nRet;
//STRIP001 }

// Suche nach Attributen ----------------------------------------------------



//STRIP001 ULONG SwWrtShell::SearchAttr( const SfxItemSet& rFindSet, BOOL bNoColls,
//STRIP001                              SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001                              FindRanges eFlags, const SearchOptions* pSearchOpt,
//STRIP001                              const SfxItemSet* pReplaceSet )
//STRIP001 {
//STRIP001  // Keine Erweiterung bestehender Selektionen
//STRIP001  if (!(eFlags & FND_IN_SEL))
//STRIP001      ClearMark();
//STRIP001
//STRIP001  // Suchen
//STRIP001     BOOL bCancel = FALSE;
//STRIP001  ULONG nRet = Find( rFindSet, bNoColls, eStart, eEnde, bCancel, eFlags, pSearchOpt, pReplaceSet);
//STRIP001
//STRIP001     if(bCancel)
//STRIP001     {
//STRIP001         Undo(0, 1);
//STRIP001         nRet = ULONG_MAX;
//STRIP001     }
//STRIP001  return nRet;
//STRIP001 }

// ---------- Selektionsmodi ----------



//STRIP001 void SwWrtShell::PushMode()
//STRIP001 {
//STRIP001  pModeStack = new ModeStack( pModeStack, bIns, bExtMode, bAddMode );
//STRIP001 }



//STRIP001 void SwWrtShell::PopMode()
//STRIP001 {
//STRIP001  if ( 0 == pModeStack )
//STRIP001      return;
//STRIP001
//STRIP001  if ( bExtMode && !pModeStack->bExt )
//STRIP001      LeaveExtMode();
//STRIP001  if ( bAddMode && !pModeStack->bAdd )
//STRIP001      LeaveAddMode();
//STRIP001  bIns = pModeStack->bIns;
//STRIP001
//STRIP001  ModeStack *pTmp = pModeStack->pNext;
//STRIP001  delete pModeStack;
//STRIP001  pModeStack = pTmp;
//STRIP001 }

/*
 * Zwei Methoden fuer das Cursorsetzen; die erste mappt auf die
 * gleichnamige Methoden an der CursorShell, die zweite hebt
 * zuerst alle Selektionen auf.
 */



/*N*/ long SwWrtShell::SetCrsr(const Point *pPt, BOOL bTextOnly)
/*N*/ {
        /*
        * eine gfs.  bestehende Selektion an der Position des
        * Mausklicks aufheben
        */
/*?*/           DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001  if(!IsInSelect() && ChgCurrPam(*pPt)) {
//STRIP001      ClearMark();
//STRIP001  }
//STRIP001  return SwCrsrShell::SetCrsr(*pPt, bTextOnly);
/*N*/ }


//STRIP001 long SwWrtShell::SetCrsrKillSel(const Point *pPt, BOOL bTextOnly )
//STRIP001 {
//STRIP001  ACT_KONTEXT(this);
//STRIP001  ResetSelect(pPt,FALSE);
//STRIP001  return SwCrsrShell::SetCrsr(*pPt, bTextOnly);
//STRIP001 }



/*N*/ void SwWrtShell::UnSelectFrm()
/*N*/ {
/*N*/     // Rahmenselektion aufheben mit garantiert ungueltiger Position
/*N*/   Point aPt(LONG_MIN, LONG_MIN);
/*N*/     SelectObj(aPt, 0);
/*N*/   SwTransferable::ClearSelection( *this );
/*N*/ }

/*
 * Aufheben aller Selektionen
 */



//STRIP001 long SwWrtShell::ResetSelect(const Point *,BOOL)
//STRIP001 {
//STRIP001  if(IsSelFrmMode())
//STRIP001  {
//STRIP001      UnSelectFrm();
//STRIP001      LeaveSelFrmMode();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      /*  ACT_KONTEXT() macht eine Action auf -
//STRIP001          um im Basicablauf keine Probleme mit der
//STRIP001          Shellumschaltung zu bekommen, darf
//STRIP001          GetChgLnk().Call() erst nach
//STRIP001          EndAction() gerufen werden.
//STRIP001      */
//STRIP001      {
//STRIP001          ACT_KONTEXT(this);
//STRIP001          bSelWrd = bSelLn = FALSE;
//STRIP001          KillPams();
//STRIP001          ClearMark();
//STRIP001          fnKillSel = &SwWrtShell::Ignore;
//STRIP001          fnSetCrsr = &SwWrtShell::SetCrsr;
//STRIP001      }
//STRIP001      /*
//STRIP001          * nach dem Aufheben aller Selektionen koennte ein Update der
//STRIP001          * Attr-Controls notwendig sein.
//STRIP001      */
//STRIP001      GetChgLnk().Call(this);
//STRIP001  }
//STRIP001  SwTransferable::ClearSelection( *this );
//STRIP001  return 1;
//STRIP001 }



/*
 * tue nichts
 */
/*N*/ long SwWrtShell::Ignore(const Point *, BOOL ) {
/*N*/   return 1;
/*N*/ }

/*
 * Start eines Selektionsvorganges.
 */



//STRIP001 void SwWrtShell::SttSelect()
//STRIP001 {
//STRIP001  if(bInSelect)
//STRIP001      return;
//STRIP001  if(!HasMark())
//STRIP001      SetMark();
//STRIP001  fnKillSel = &SwWrtShell::Ignore;
//STRIP001  fnSetCrsr = &SwWrtShell::SetCrsr;
//STRIP001  bInSelect = TRUE;
//STRIP001  SwTransferable::CreateSelection( *this );
//STRIP001 }
/*
 * Ende eines Selektionsvorganges.
 */



//STRIP001 void SwWrtShell::EndSelect()
//STRIP001 {
//STRIP001  if(!bInSelect || bExtMode)
//STRIP001      return;
//STRIP001  bInSelect = FALSE;
//STRIP001  (this->*fnLeaveSelect)(0,FALSE);
//STRIP001  if(!bAddMode) {
//STRIP001      fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001      fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001  }
//STRIP001 }
/* Methode, um eine bestehende wortweise oder zeilenweise Selektion
 * zu erweitern.
 */

//STRIP001 inline BOOL operator<(const Point &rP1,const Point &rP2)
//STRIP001 {
//STRIP001  return rP1.Y() < rP2.Y() || (rP1.Y() == rP2.Y() && rP1.X() < rP2.X());
//STRIP001 }



//STRIP001 long SwWrtShell::ExtSelWrd(const Point *pPt, BOOL )
//STRIP001 {
//STRIP001  MV_KONTEXT(this);
//STRIP001  if( IsTableMode() )
//STRIP001      return 1;
//STRIP001
//STRIP001  // Bug 66823: actual crsr has in additional mode no selection?
//STRIP001  // Then destroy the actual an go to prev, this will be expand
//STRIP001  if( !HasMark() && GoPrevCrsr() )
//STRIP001  {
//STRIP001      BOOL bHasMark = HasMark(); // thats wrong!
//STRIP001      GoNextCrsr();
//STRIP001      if( bHasMark )
//STRIP001      {
//STRIP001          DestroyCrsr();
//STRIP001          GoPrevCrsr();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // check the direction of the selection with the new point
//STRIP001  BOOL bRet = FALSE, bMoveCrsr = TRUE, bToTop;
//STRIP001  SwCrsrShell::SelectWord( &aStart );     // select the startword
//STRIP001  SwCrsrShell::Push();                    // save the cursor
//STRIP001  SwCrsrShell::SetCrsr( *pPt );           // and check the direction
//STRIP001
//STRIP001  switch( SwCrsrShell::CompareCursor( StackMkCurrPt ))
//STRIP001  {
//STRIP001  case -1:    bToTop = FALSE;     break;
//STRIP001  case 1:     bToTop = TRUE;      break;
//STRIP001  default:    bMoveCrsr = FALSE;  break;
//STRIP001  }
//STRIP001
//STRIP001  SwCrsrShell::Pop( FALSE );              // retore the saved cursor
//STRIP001
//STRIP001  if( bMoveCrsr )
//STRIP001  {
//STRIP001      // select to Top but cursor select to Bottom? or
//STRIP001      // select to Bottom but cursor select to Top?       --> swap the cursor
//STRIP001      if( bToTop )
//STRIP001          SwapPam();
//STRIP001
//STRIP001      SwCrsrShell::Push();                // save cur cursor
//STRIP001      if( SwCrsrShell::SelectWord( pPt )) // select the current word
//STRIP001      {
//STRIP001          if( bToTop )
//STRIP001              SwapPam();
//STRIP001          ::com::bine();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwCrsrShell::Pop( FALSE );
//STRIP001          if( bToTop )
//STRIP001              SwapPam();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = TRUE;
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 long SwWrtShell::ExtSelLn(const Point *pPt, BOOL )
//STRIP001 {
//STRIP001  MV_KONTEXT(this);
//STRIP001  SwCrsrShell::SetCrsr(*pPt);
//STRIP001  if( IsTableMode() )
//STRIP001      return 1;
//STRIP001
//STRIP001  // Bug 66823: actual crsr has in additional mode no selection?
//STRIP001  // Then destroy the actual an go to prev, this will be expand
//STRIP001  if( !HasMark() && GoPrevCrsr() )
//STRIP001  {
//STRIP001      BOOL bHasMark = HasMark(); // thats wrong!
//STRIP001      GoNextCrsr();
//STRIP001      if( bHasMark )
//STRIP001      {
//STRIP001          DestroyCrsr();
//STRIP001          GoPrevCrsr();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // ggfs. den Mark der Selektion anpassen
//STRIP001  BOOL bToTop = !IsCrsrPtAtEnd();
//STRIP001  SwapPam();
//STRIP001
//STRIP001  // der "Mark" muss am Zeilenende/-anfang stehen
//STRIP001  if( bToTop ? !IsAtRightMargin() : !IsAtLeftMargin() )
//STRIP001  {
//STRIP001      if( bToTop )
//STRIP001      {
//STRIP001          if( !IsEndPara() )
//STRIP001              SwCrsrShell::Right(1,CRSR_SKIP_CHARS);
//STRIP001          SwCrsrShell::RightMargin();
//STRIP001      }
//STRIP001      else
//STRIP001          SwCrsrShell::LeftMargin();
//STRIP001  }
//STRIP001  SwapPam();
//STRIP001
//STRIP001  return bToTop ? SwCrsrShell::LeftMargin() : SwCrsrShell::RightMargin();
//STRIP001 }


/*
 * zurueck in den Standard Mode: kein Mode, keine Selektionen.
 */

/*N*/ void SwWrtShell::EnterStdMode()
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 if(bAddMode)
//STRIP001 /*?*/        LeaveAddMode();
//STRIP001 /*?*/    bExtMode = FALSE;
//STRIP001 /*?*/    bInSelect = FALSE;
//STRIP001 /*?*/     if(IsSelFrmMode())
//STRIP001 /*?*/     {
//STRIP001 /*?*/         UnSelectFrm();
//STRIP001 /*?*/         LeaveSelFrmMode();
//STRIP001 /*?*/     }
//STRIP001 /*?*/     else
//STRIP001 /*?*/     {
//STRIP001          /*  ACT_KONTEXT() opens and action which has to be
//STRIP001              closed prior to the call of
//STRIP001             GetChgLnk().Call()
//STRIP001          */
//STRIP001 /*?*/         {
//STRIP001 /*?*/             ACT_KONTEXT(this);
//STRIP001 /*?*/             bSelWrd = bSelLn = FALSE;
//STRIP001 /*?*/             KillPams();
//STRIP001 /*?*/             ClearMark();
//STRIP001 /*?*/             fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001 /*?*/             fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/     SwTransferable::ClearSelection( *this );
/*N*/ }

/*
 * Extended Mode
 */



//STRIP001 void SwWrtShell::EnterExtMode()
//STRIP001 {
//STRIP001  bExtMode = TRUE;
//STRIP001  bAddMode = FALSE;
//STRIP001  SttSelect();
//STRIP001 }



//STRIP001 void SwWrtShell::LeaveExtMode()
//STRIP001 {
//STRIP001  bExtMode = FALSE;
//STRIP001  EndSelect();
//STRIP001 }
/*
 * Ende einer Selektion; falls die Selektion leer ist,
 * ClearMark().
 */



/*N*/ long SwWrtShell::SttLeaveSelect(const Point *, BOOL )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001      if(SwCrsrShell::HasSelection() && !IsSelTblCells() && bClearMark) {
//STRIP001      return 0;
//STRIP001  }
//STRIP001 //   if( IsSelTblCells() ) aSelTblLink.Call(this);
//STRIP001  ClearMark();
/*N*/   return 1;
/*N*/ }
/*
 * Verlassen des Selektionsmodus in Additional Mode
 */



//STRIP001 long SwWrtShell::AddLeaveSelect(const Point *, BOOL )
//STRIP001 {
//STRIP001  if(IsTableMode()) LeaveAddMode();
//STRIP001  else if(SwCrsrShell::HasSelection())
//STRIP001      CreateCrsr();
//STRIP001  return 1;
//STRIP001 }
/*
 * Additional Mode
 */



//STRIP001 void SwWrtShell::EnterAddMode()
//STRIP001 {
//STRIP001  if(IsTableMode()) return;
//STRIP001  fnLeaveSelect = &SwWrtShell::AddLeaveSelect;
//STRIP001  fnKillSel = &SwWrtShell::Ignore;
//STRIP001  fnSetCrsr = &SwWrtShell::SetCrsr;
//STRIP001  bAddMode = TRUE;
//STRIP001  bExtMode = FALSE;
//STRIP001  if(SwCrsrShell::HasSelection())
//STRIP001      CreateCrsr();
//STRIP001 }



//STRIP001 void SwWrtShell::LeaveAddMode()
//STRIP001 {
//STRIP001  fnLeaveSelect = &SwWrtShell::SttLeaveSelect;
//STRIP001  fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001  fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001  bAddMode = FALSE;
//STRIP001 }

// Einfuegemodus



//STRIP001 void SwWrtShell::SetInsMode( BOOL bOn )
//STRIP001 {
//STRIP001  bIns = bOn;
//STRIP001  SwCrsrShell::SetOverwriteCrsr( !bIns );
//STRIP001  const SfxBoolItem aTmp( SID_ATTR_INSERT, bIns );
//STRIP001  GetView().GetViewFrame()->GetBindings().SetState( aTmp );
//STRIP001  StartAction();
//STRIP001  EndAction();
//STRIP001 }

/*
 * Rahmen bearbeiten
 */


//STRIP001 long SwWrtShell::BeginFrmDrag(const Point *pPt, BOOL)
//STRIP001 {
//STRIP001  fnDrag = &SwFEShell::Drag;
//STRIP001  if(bStartDrag)
//STRIP001  {
//STRIP001      Point aTmp( nStartDragX, nStartDragY );
//STRIP001      SwFEShell::BeginDrag( &aTmp, FALSE );
//STRIP001  }
//STRIP001  else
//STRIP001      SwFEShell::BeginDrag( pPt, FALSE );
//STRIP001  return 1;
//STRIP001 }



/*N*/ void SwWrtShell::EnterSelFrmMode(const Point *pPos)
/*N*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); //STRIP001    if(pPos)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        nStartDragX = pPos->X();
//STRIP001 /*?*/        nStartDragY = pPos->Y();
//STRIP001 /*?*/        bStartDrag = TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    bNoEdit = bLayoutMode = TRUE;
//STRIP001 /*?*/    HideCrsr();
//STRIP001 /*?*/
//STRIP001 /*?*/        // gleicher Aufruf von BeginDrag an der SwFEShell
//STRIP001 /*?*/    fnDrag          = &SwWrtShell::BeginFrmDrag;
//STRIP001 /*?*/    fnEndDrag       = &SwWrtShell::UpdateLayoutFrm;
//STRIP001 /*?*/    SwBaseShell::SetFrmMode( FLY_DRAG_START, this );
/*N*/ }



/*N*/ void SwWrtShell::LeaveSelFrmMode()
/*N*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); //STRIP001    fnDrag          = &SwWrtShell::BeginDrag;
//STRIP001 /*?*/    fnEndDrag       = &SwWrtShell::EndDrag;
//STRIP001 /*?*/    bLayoutMode = FALSE;
//STRIP001 /*?*/    bStartDrag = FALSE;
//STRIP001 /*?*/    Edit();
//STRIP001 /*?*/    SwBaseShell::SetFrmMode( FLY_DRAG_END, this );
/*N*/ }
/*------------------------------------------------------------------------
 Beschreibung:  Rahmengebundenes Macro ausfuehren
------------------------------------------------------------------------*/



/*N*/ IMPL_LINK( SwWrtShell, ExecFlyMac, void *, pFlyFmt )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  const SwFrmFmt *pFmt = pFlyFmt ? (SwFrmFmt*)pFlyFmt : GetFlyFrmFmt();
//STRIP001  ASSERT(pFmt, kein FrameFormat.);
//STRIP001  const SvxMacroItem &rFmtMac = pFmt->GetMacro();
//STRIP001
//STRIP001  if(rFmtMac.HasMacro(SW_EVENT_OBJECT_SELECT))
//STRIP001  {
//STRIP001      const SvxMacro &rMac = rFmtMac.GetMacro(SW_EVENT_OBJECT_SELECT);
//STRIP001      if( IsFrmSelected() )
//STRIP001          bLayoutMode = TRUE;
//STRIP001      CallChgLnk();
//STRIP001      ExecMacro( rMac );
//STRIP001  }
/*N*/   return 0;
/*N*/ }



//STRIP001 long SwWrtShell::UpdateLayoutFrm(const Point *pPt, BOOL )
//STRIP001 {
//STRIP001      // voerst Dummy
//STRIP001  SwFEShell::EndDrag( pPt, FALSE );
//STRIP001  fnDrag = &SwWrtShell::BeginFrmDrag;
//STRIP001  return 1;
//STRIP001 }

/*
 * Handler fuer das Togglen der Modi. Liefern alten Mode zurueck.
 */



//STRIP001 long SwWrtShell::ToggleAddMode()
//STRIP001 {
//STRIP001  bAddMode ? LeaveAddMode(): EnterAddMode();
//STRIP001  return !bAddMode;
//STRIP001 }



//STRIP001 long SwWrtShell::ToggleExtMode()
//STRIP001 {
//STRIP001  bExtMode ? LeaveExtMode() : EnterExtMode();
//STRIP001  return !bExtMode;
//STRIP001 }
/*
 * Draggen im Standard Modus (Selektieren von Inhalt)
 */



/*N*/ long SwWrtShell::BeginDrag(const Point *pPt, BOOL )
/*N*/ {
DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001  if(bSelWrd)
//STRIP001  {
//STRIP001      bInSelect = TRUE;
//STRIP001      if( !IsCrsrPtAtEnd() )
//STRIP001          SwapPam();
//STRIP001
//STRIP001      fnDrag = &SwWrtShell::ExtSelWrd;
//STRIP001      fnSetCrsr = &SwWrtShell::Ignore;
//STRIP001  }
//STRIP001  else if(bSelLn)
//STRIP001  {
//STRIP001      bInSelect = TRUE;
//STRIP001      fnDrag = &SwWrtShell::ExtSelLn;
//STRIP001      fnSetCrsr = &SwWrtShell::Ignore;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      fnDrag = &SwWrtShell::Drag;
//STRIP001      SttSelect();
//STRIP001  }
//STRIP001
//STRIP001  return 1;
/*N*/ }



//STRIP001 long SwWrtShell::Drag(const Point *, BOOL )
//STRIP001 {
//STRIP001  if( IsSelTblCells() )
//STRIP001      aSelTblLink.Call(this);
//STRIP001
//STRIP001  return 1;
//STRIP001 }



/*N*/ long SwWrtShell::EndDrag(const Point *pPt, BOOL )
/*N*/ {
DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001  fnDrag = &SwWrtShell::BeginDrag;
//STRIP001  if( IsExtSel() )
//STRIP001      LeaveExtSel();
//STRIP001
//STRIP001  if( IsSelTblCells() )
//STRIP001      aSelTblLink.Call(this);
//STRIP001  EndSelect();
//STRIP001  return 1;
/*N*/ }
/*------------------------------------------------------------------------
 Beschreibung:  Selektion einer Tabellenzeile / Spalte
------------------------------------------------------------------------*/



//STRIP001 FASTBOOL SwWrtShell::SelectTableRow()
//STRIP001 {
//STRIP001  if ( SelTblRow() )
//STRIP001  {
//STRIP001      fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001      fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::SelectTableCol()
//STRIP001 {
//STRIP001  if ( SelTblCol() )
//STRIP001  {
//STRIP001      fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001      fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:    Prueft, ob eine Wortselektion vorliegt.
                  Gemaess den Regeln fuer intelligentes Cut / Paste
                  werden umgebende Spaces rausgeschnitten.
 Return:          Liefert Art der Wortselektion zurueck.
------------------------------------------------------------------------*/



//STRIP001 int SwWrtShell::IntelligentCut(int nSelection, BOOL bCut)
//STRIP001 {
//STRIP001      // kein intelligentes Drag and Drop bei Mehrfachselektion
//STRIP001      // es existieren mehrere Cursor, da ein zweiter bereits
//STRIP001      // an die Zielposition gesetzt wurde
//STRIP001  if( IsAddMode() || !(nSelection & SEL_TXT) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  String sTxt;
//STRIP001  CharClass& rCC = GetAppCharClass();
//STRIP001
//STRIP001      // wenn das erste und das letzte Zeichen kein Wortzeichen ist,
//STRIP001      // ist kein Wort selektiert.
//STRIP001  sal_Unicode cPrev = GetChar(FALSE);
//STRIP001  sal_Unicode cNext = GetChar(TRUE, -1);
//STRIP001     if( !cPrev || !cNext ||
//STRIP001      !rCC.isLetterNumeric( ( sTxt = cPrev), 0 ) ||
//STRIP001      !rCC.isLetterNumeric( ( sTxt = cNext), 0 ) )
//STRIP001      return NO_WORD;
//STRIP001
//STRIP001  cPrev = GetChar(FALSE, -1);
//STRIP001  cNext = GetChar(TRUE);
//STRIP001
//STRIP001  int cWord = NO_WORD;
//STRIP001      // ist ein Wort selektiert?
//STRIP001  if(!cWord && cPrev && cNext &&
//STRIP001      CH_TXTATR_BREAKWORD != cPrev && CH_TXTATR_INWORD != cPrev &&
//STRIP001      CH_TXTATR_BREAKWORD != cNext && CH_TXTATR_INWORD != cNext &&
//STRIP001      !rCC.isLetterNumeric( ( sTxt = cPrev), 0 ) &&
//STRIP001      !rCC.isLetterNumeric( ( sTxt = cNext), 0 ) )
//STRIP001     cWord = WORD_NO_SPACE;
//STRIP001
//STRIP001  if(cWord == WORD_NO_SPACE && ' ' == cPrev )
//STRIP001  {
//STRIP001      cWord = WORD_SPACE_BEFORE;
//STRIP001          // Space davor loeschen
//STRIP001      if(bCut)
//STRIP001      {
//STRIP001          Push();
//STRIP001          if(IsCrsrPtAtEnd())
//STRIP001              SwapPam();
//STRIP001          ClearMark();
//STRIP001          SetMark();
//STRIP001          SwCrsrShell::Left(1,CRSR_SKIP_CHARS);
//STRIP001          SwFEShell::Delete();
//STRIP001          Pop( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001  else if(cWord == WORD_NO_SPACE && cNext == ' ')
//STRIP001  {
//STRIP001      cWord = WORD_SPACE_AFTER;
//STRIP001          // Space dahinter loeschen
//STRIP001      if(bCut) {
//STRIP001          Push();
//STRIP001          if(!IsCrsrPtAtEnd()) SwapPam();
//STRIP001          ClearMark();
//STRIP001          SetMark();
//STRIP001          SwCrsrShell::Right(1,CRSR_SKIP_CHARS);
//STRIP001          SwFEShell::Delete();
//STRIP001          Pop( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001  return cWord;
//STRIP001 }



    // jump to the next / previous hyperlink - inside text and also
    // on graphics
//STRIP001 FASTBOOL SwWrtShell::SelectNextPrevHyperlink( BOOL bNext )
//STRIP001 {
//STRIP001  StartAction();
//STRIP001  FASTBOOL bRet = SwCrsrShell::SelectNxtPrvHyperlink( bNext );
//STRIP001  if( !bRet )
//STRIP001  {
//STRIP001      // will we have this feature?
//STRIP001      EnterStdMode();
//STRIP001      if( bNext )
//STRIP001          SwCrsrShell::SttDoc();
//STRIP001      else
//STRIP001          SwCrsrShell::EndDoc();
//STRIP001      bRet = SwCrsrShell::SelectNxtPrvHyperlink( bNext );
//STRIP001  }
//STRIP001  EndAction();
//STRIP001
//STRIP001  BOOL bCreateXSelection = FALSE;
//STRIP001  const FASTBOOL bFrmSelected = IsFrmSelected() || IsObjSelected();
//STRIP001  if( IsSelection() )
//STRIP001  {
//STRIP001      if ( bFrmSelected )
//STRIP001          UnSelectFrm();
//STRIP001
//STRIP001      // Funktionspointer fuer das Aufheben der Selektion setzen
//STRIP001      // bei Cursor setzen
//STRIP001      fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001      fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001      bCreateXSelection = TRUE;
//STRIP001  }
//STRIP001  else if( bFrmSelected )
//STRIP001  {
//STRIP001      EnterSelFrmMode();
//STRIP001      bCreateXSelection = TRUE;
//STRIP001  }
//STRIP001  else if( (CNT_GRF | CNT_OLE ) & GetCntType() )
//STRIP001  {
//STRIP001      SelectObj( GetCharRect().Pos() );
//STRIP001      EnterSelFrmMode();
//STRIP001      bCreateXSelection = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if( bCreateXSelection )
//STRIP001      SwTransferable::CreateSelection( *this );
//STRIP001
//STRIP001  return bRet;
//STRIP001 }


/* fuer den Erhalt der Selektion wird nach SetMark() der Cursor
 * nach links bewegt, damit er durch das Einfuegen von Text nicht
 * verschoben wird.  Da auf der CORE-Seite am aktuellen Cursor
 * eine bestehende Selektion aufgehoben wird, wird der Cursor auf
 * den Stack gepushed. Nach dem Verschieben werden sie wieder
 * zusammengefasst. */



#if 0
//STRIP001 long SwWrtShell::MoveText(const Point *pPt,BOOL)
//STRIP001 {
//STRIP001      // ueber einer bestehenden Selektion kein D&D
//STRIP001  if(ChgCurrPam(*pPt)) {
//STRIP001      LeaveDDMode();
//STRIP001      bTStart = bDD = FALSE;
//STRIP001      return 0;
//STRIP001  }
//STRIP001      // Create-Crsr muss nicht immer sein !!
//STRIP001      // im Add-Mode benutze den letzen, sonst erzeuge einen neuen
//STRIP001  if(!IsAddMode()) SwCrsrShell::CreateCrsr();
//STRIP001  SwCrsrShell::SetCrsr(*pPt);
//STRIP001      // kein D&D auf andere Inhaltsformen als Text
//STRIP001  const int nSelection = GetSelectionType();
//STRIP001  if(SEL_TXT != GetCntType()) {
//STRIP001      if(!IsAddMode()) {
//STRIP001          SwCrsrShell::DestroyCrsr();
//STRIP001          GoPrevCrsr();
//STRIP001      }
//STRIP001      LeaveDDMode();
//STRIP001      bTStart = bDD = FALSE;
//STRIP001      return 0;
//STRIP001  }
//STRIP001      // SSelection vor Start/ EndAction erfragen
//STRIP001  StartUndo(UNDO_INSERT);
//STRIP001  StartAllAction();
//STRIP001  GoPrevCrsr();
//STRIP001  const int cWord = IntelligentCut(nSelection);
//STRIP001  GoNextCrsr();
//STRIP001  const BOOL bInWrd = IsInWrd() || IsEndWrd();
//STRIP001  const BOOL bSttWrd = IsSttWrd();
//STRIP001  SwEditShell::Move();
//STRIP001
//STRIP001  // nach dem Move sind alle Crsr geloescht und eine SSelection
//STRIP001  // umschliesst den verschobenen Bereich
//STRIP001
//STRIP001  if(bInWrd && ( cWord == WORD_SPACE_AFTER || cWord == WORD_SPACE_BEFORE)) {
//STRIP001      if(!bSttWrd) SwapPam();
//STRIP001      SwEditShell::Insert(' ');
//STRIP001      if(!bSttWrd) SwapPam();
//STRIP001  }
//STRIP001  LeaveDDMode();
//STRIP001  bTStart = bDD = FALSE;
//STRIP001  EndAllAction();
//STRIP001  EndUndo(UNDO_INSERT);
//STRIP001  return 1;
//STRIP001 }
#endif

}
