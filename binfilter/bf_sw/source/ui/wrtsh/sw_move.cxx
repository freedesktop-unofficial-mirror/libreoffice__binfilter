/*************************************************************************
 *
 *  $RCSfile: sw_move.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 19:40:59 $
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

// auto strip #ifndef _SFX_BINDINGS_HXX //autogen
// auto strip #include <bf_sfx2/bindings.hxx>
// auto strip #endif
// auto strip #ifndef _SFXVIEWFRM_HXX
// auto strip #include <bf_sfx2/viewfrm.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
// auto strip #ifndef _VIEW_HXX
// auto strip #include <view.hxx>
// auto strip #endif
// auto strip #ifndef _VIEWOPT_HXX
// auto strip #include <viewopt.hxx>
// auto strip #endif
// auto strip #ifndef _CRSSKIP_HXX
// auto strip #include <crsskip.hxx>
// auto strip #endif
namespace binfilter {

/*  Immer:
    -   Zuruecksetzen des Cursorstacks
    -   Timer nachtriggern
    -   gfs. GCAttr

    bei Selektion
    -   SttSelect()

    sonst
    -   EndSelect()
 */

const long nReadOnlyScrollOfst = 10;

//STRIP001 class ShellMoveCrsr
//STRIP001 {
//STRIP001  SwWrtShell* pSh;
//STRIP001  BOOL bAct;
//STRIP001 public:
//STRIP001  inline ShellMoveCrsr( SwWrtShell* pWrtSh, FASTBOOL bSel )
//STRIP001  {
//STRIP001      bAct = !pWrtSh->ActionPend() && (pWrtSh->GetFrmType(0,FALSE) & FRMTYPE_FLY_ANY);
//STRIP001      ( pSh = pWrtSh )->MoveCrsr( BOOL(bSel) );
//STRIP001      pWrtSh->GetView().GetViewFrame()->GetBindings().Invalidate(SID_HYPERLINK_GETLINK);
//STRIP001  }
//STRIP001  inline ~ShellMoveCrsr()
//STRIP001  {
//STRIP001      if( bAct )
//STRIP001      {
//STRIP001          //Die Action wird fuer das Scrollen in "einabsaetzigen" Rahmen mit
//STRIP001          //fester Hoehe gebraucht.
//STRIP001          pSh->StartAllAction();
//STRIP001          pSh->EndAllAction();
//STRIP001      }
//STRIP001  }
//STRIP001 };

//STRIP001 void SwWrtShell::MoveCrsr( FASTBOOL bWithSelect )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if ( IsGCAttr() )
//STRIP001  {
//STRIP001      GCAttr();
//STRIP001      ClearGCAttr();
//STRIP001  }
//STRIP001  if ( bWithSelect )
//STRIP001      SttSelect();
//STRIP001  else
//STRIP001  {
//STRIP001      EndSelect();
//STRIP001      (this->*fnKillSel)( 0, FALSE );
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SwWrtShell::SimpleMove( FNSimpleMove FnSimpleMove, FASTBOOL bSelect )
//STRIP001 {
//STRIP001  FASTBOOL nRet;
//STRIP001  if( bSelect )
//STRIP001  {
//STRIP001      SttCrsrMove();
//STRIP001      MoveCrsr( TRUE );
//STRIP001      nRet = (this->*FnSimpleMove)();
//STRIP001      EndCrsrMove();
//STRIP001  }
//STRIP001  else if( 0 != ( nRet = (this->*FnSimpleMove)() ) )
//STRIP001      MoveCrsr( FALSE );
//STRIP001  return nRet;
//STRIP001 }


/*N*/ FASTBOOL SwWrtShell::Left( USHORT nMode, FASTBOOL bSelect,
/*N*/                             USHORT nCount, BOOL bBasicCall, BOOL bVisual )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     if ( !bSelect && !bBasicCall && IsCrsrReadonly()  && !GetViewOptions()->IsSelectionInReadonly())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Point aTmp( VisArea().Pos() );
//STRIP001 /*?*/        aTmp.X() -= VisArea().Width() * nReadOnlyScrollOfst / 100;
//STRIP001 /*?*/        rView.SetVisArea( aTmp );
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/         return SwCrsrShell::Left( nCount, nMode, bVisual );
//STRIP001 /*?*/    }
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::Right( USHORT nMode, FASTBOOL bSelect,
/*N*/                             USHORT nCount, BOOL bBasicCall, BOOL bVisual )
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     if ( !bSelect && !bBasicCall && IsCrsrReadonly() && !GetViewOptions()->IsSelectionInReadonly() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Point aTmp( VisArea().Pos() );
//STRIP001 /*?*/        aTmp.X() += VisArea().Width() * nReadOnlyScrollOfst / 100;
//STRIP001 /*?*/        aTmp.X() = rView.SetHScrollMax( aTmp.X() );
//STRIP001 /*?*/        rView.SetVisArea( aTmp );
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/         return SwCrsrShell::Right( nCount, nMode, bVisual );
//STRIP001 /*?*/    }
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::Up( FASTBOOL bSelect, USHORT nCount, BOOL bBasicCall )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     if ( !bSelect && !bBasicCall && IsCrsrReadonly()  && !GetViewOptions()->IsSelectionInReadonly())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Point aTmp( VisArea().Pos() );
//STRIP001 /*?*/        aTmp.Y() -= VisArea().Height() * nReadOnlyScrollOfst / 100;
//STRIP001 /*?*/        rView.SetVisArea( aTmp );
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/        return SwCrsrShell::Up( nCount );
//STRIP001 /*?*/    }
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::Down( FASTBOOL bSelect, USHORT nCount, BOOL bBasicCall )
/*N*/  {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001      if ( !bSelect && !bBasicCall && IsCrsrReadonly() && !GetViewOptions()->IsSelectionInReadonly())
//STRIP001  {
//STRIP001      Point aTmp( VisArea().Pos() );
//STRIP001      aTmp.Y() += VisArea().Height() * nReadOnlyScrollOfst / 100;
//STRIP001      aTmp.Y() = rView.SetVScrollMax( aTmp.Y() );
//STRIP001      rView.SetVisArea( aTmp );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ShellMoveCrsr aTmp( this, bSelect );
//STRIP001      return SwCrsrShell::Down( nCount );
//STRIP001  }
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::LeftMargin( FASTBOOL bSelect, FASTBOOL bBasicCall )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 if ( !bSelect && !bBasicCall && IsCrsrReadonly() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Point aTmp( VisArea().Pos() );
//STRIP001 /*?*/        aTmp.X() = DOCUMENTBORDER;
//STRIP001 /*?*/        rView.SetVisArea( aTmp );
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/        return SwCrsrShell::LeftMargin();
//STRIP001 /*?*/    }
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::RightMargin( FASTBOOL bSelect, FASTBOOL bBasicCall  )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 if ( !bSelect && !bBasicCall && IsCrsrReadonly() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Point aTmp( VisArea().Pos() );
//STRIP001 /*?*/        aTmp.X() = GetDocSize().Width() - VisArea().Width() + DOCUMENTBORDER;
//STRIP001 /*?*/        if( DOCUMENTBORDER > aTmp.X() )
//STRIP001 /*?*/            aTmp.X() = DOCUMENTBORDER;
//STRIP001 /*?*/        rView.SetVisArea( aTmp );
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/        return SwCrsrShell::RightMargin(bBasicCall);
//STRIP001 /*?*/    }
/*N*/ }



//STRIP001 BOOL SwWrtShell::GoStart( BOOL bKeepArea, BOOL *pMoveTable,
//STRIP001                          BOOL bSelect, BOOL bDontMoveRegion )
//STRIP001 {
//STRIP001  if ( IsCrsrInTbl() )
//STRIP001  {
//STRIP001      const BOOL bBoxSelection = HasBoxSelection();
//STRIP001      if ( !bSelect )
//STRIP001          EnterStdMode();
//STRIP001      else
//STRIP001          SttSelect();
//STRIP001          // Tabellenzelle?
//STRIP001      if ( !bBoxSelection && (MoveSection( fnSectionCurr, fnSectionStart)
//STRIP001              || bDontMoveRegion))
//STRIP001      {
//STRIP001          if ( pMoveTable )
//STRIP001              *pMoveTable = FALSE;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001      if( MoveTable( fnTableCurr, fnTableStart ) || bDontMoveRegion )
//STRIP001      {
//STRIP001          if ( pMoveTable )
//STRIP001              *pMoveTable = TRUE;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001      else if( bBoxSelection && pMoveTable )
//STRIP001      {
//STRIP001          // JP 09.01.96: wir haben eine Boxselektion (oder leere Zelle)
//STRIP001          //              und wollen selektieren (pMoveTable wird im
//STRIP001          //              SelAll gesetzt). Dann darf die Tabelle nicht
//STRIP001          //              verlassen werden; sonst ist keine Selektion der
//STRIP001          //              gesamten Tabelle moeglich!
//STRIP001          *pMoveTable = TRUE;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( !bSelect )
//STRIP001      EnterStdMode();
//STRIP001  else
//STRIP001      SttSelect();
//STRIP001  const USHORT nFrmType = GetFrmType(0,FALSE);
//STRIP001  if ( FRMTYPE_FLY_ANY & nFrmType )
//STRIP001  {
//STRIP001      if( MoveSection( fnSectionCurr, fnSectionStart ) )
//STRIP001          return TRUE;
//STRIP001      else if ( FRMTYPE_FLY_FREE & nFrmType || bDontMoveRegion )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  if(( FRMTYPE_HEADER | FRMTYPE_FOOTER | FRMTYPE_FOOTNOTE ) & nFrmType )
//STRIP001  {
//STRIP001      if ( MoveSection( fnSectionCurr, fnSectionStart ) )
//STRIP001          return TRUE;
//STRIP001      else if ( bKeepArea )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  // Bereiche ???
//STRIP001  return SwCrsrShell::MoveRegion( fnRegionCurrAndSkip, fnRegionStart ) ||
//STRIP001         SwCrsrShell::SttDoc();
//STRIP001 }



//STRIP001 BOOL SwWrtShell::GoEnd(BOOL bKeepArea, BOOL *pMoveTable)
//STRIP001 {
//STRIP001  if ( pMoveTable && *pMoveTable )
//STRIP001      return MoveTable( fnTableCurr, fnTableEnd );
//STRIP001
//STRIP001  if ( IsCrsrInTbl() )
//STRIP001  {
//STRIP001      if ( MoveSection( fnSectionCurr, fnSectionEnd ) ||
//STRIP001           MoveTable( fnTableCurr, fnTableEnd ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const USHORT nFrmType = GetFrmType(0,FALSE);
//STRIP001      if ( FRMTYPE_FLY_ANY & nFrmType )
//STRIP001      {
//STRIP001          if ( MoveSection( fnSectionCurr, fnSectionEnd ) )
//STRIP001              return TRUE;
//STRIP001          else if ( FRMTYPE_FLY_FREE & nFrmType )
//STRIP001              return FALSE;
//STRIP001      }
//STRIP001      if(( FRMTYPE_HEADER | FRMTYPE_FOOTER | FRMTYPE_FOOTNOTE ) & nFrmType )
//STRIP001      {
//STRIP001          if ( MoveSection( fnSectionCurr, fnSectionEnd) )
//STRIP001              return TRUE;
//STRIP001          else if ( bKeepArea )
//STRIP001              return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Bereiche ???
//STRIP001  return SwCrsrShell::MoveRegion( fnRegionCurrAndSkip, fnRegionEnd ) ||
//STRIP001         SwCrsrShell::EndDoc();
//STRIP001 }



/*N*/ FASTBOOL SwWrtShell::SttDoc( FASTBOOL bSelect )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/    return GoStart(FALSE, 0, bSelect );
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::EndDoc( FASTBOOL bSelect)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/    return GoEnd();
/*N*/ }


/*N*/ FASTBOOL SwWrtShell::SttNxtPg( FASTBOOL bSelect )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/    return MovePage( fnPageNext, fnPageStart );
/*N*/ }



//STRIP001 FASTBOOL SwWrtShell::SttPrvPg( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect );
//STRIP001  return MovePage( fnPagePrev, fnPageStart );
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::EndNxtPg( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect );
//STRIP001  return MovePage( fnPageNext, fnPageEnd );
//STRIP001 }



/*N*/ FASTBOOL SwWrtShell::EndPrvPg( FASTBOOL bSelect )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/    return MovePage( fnPagePrev, fnPageEnd );
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::SttPg( FASTBOOL bSelect )
/*N*/ {
/*?*/DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/    return MovePage( fnPageCurr, fnPageStart );
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::EndPg( FASTBOOL bSelect )
/*N*/ {
/*?*/DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     ShellMoveCrsr aTmp( this, bSelect );
//STRIP001 /*?*/    return MovePage( fnPageCurr, fnPageEnd );
/*N*/ }



//STRIP001 FASTBOOL SwWrtShell::SttPara( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect );
//STRIP001  return MovePara( fnParaCurr, fnParaStart );
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::EndPara( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect );
//STRIP001  return MovePara(fnParaCurr,fnParaEnd);
//STRIP001 }


/*------------------------------------------------------------------------
 Beschreibung:  Spaltenweises Springen
 Parameter:     mit oder ohne SSelection
 Return:        Erfolg oder Misserfolg
------------------------------------------------------------------------*/



//STRIP001 FASTBOOL SwWrtShell::StartOfColumn( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect);
//STRIP001  return MoveColumn(fnColumnCurr, fnColumnStart);
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::EndOfColumn( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect);
//STRIP001  return MoveColumn(fnColumnCurr, fnColumnEnd);
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::StartOfNextColumn( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect);
//STRIP001  return MoveColumn( fnColumnNext, fnColumnStart);
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::EndOfNextColumn( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect);
//STRIP001  return MoveColumn(fnColumnNext, fnColumnEnd);
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::StartOfPrevColumn( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect);
//STRIP001  return MoveColumn(fnColumnPrev, fnColumnStart);
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::EndOfPrevColumn( FASTBOOL bSelect )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect);
//STRIP001  return MoveColumn(fnColumnPrev, fnColumnEnd);
//STRIP001 }



//STRIP001 BOOL SwWrtShell::PushCrsr(SwTwips lOffset, BOOL bSelect)
//STRIP001 {
//STRIP001  BOOL bDiff = FALSE;
//STRIP001  SwRect aOldRect( GetCharRect() ), aTmpArea( VisArea() );
//STRIP001
//STRIP001  //bDestOnStack besagt, ob ich den Cursor nicht an die aktuelle Position
//STRIP001  //setzen konnte, da in diesem Bereich kein Inhalt vorhanden ist.
//STRIP001  if( !bDestOnStack )
//STRIP001  {
//STRIP001      Point aPt( aOldRect.Center() );
//STRIP001
//STRIP001      if( !IsCrsrVisible() )
//STRIP001          // set CrsrPos to top-/bottom left pos. So the pagescroll is not
//STRIP001          // be dependent on the current cursor, but on the visarea.
//STRIP001          aPt.Y() = aTmpArea.Top() + aTmpArea.Height() / 2;
//STRIP001
//STRIP001      aPt.Y() += lOffset;
//STRIP001      aDest = GetCntntPos(aPt,lOffset > 0);
//STRIP001      aDest.X() = aPt.X();
//STRIP001      bDestOnStack = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //falls wir eine Rahmenselektion hatten, muss diese nach dem
//STRIP001  //fnSetCrsr entfernt werden und damit wir da wieder hinkommen
//STRIP001  //auf dem Stack gemerkt werden.
//STRIP001  BOOL bIsFrmSel = FALSE;
//STRIP001
//STRIP001  BOOL bIsObjSel = FALSE;
//STRIP001
//STRIP001  //Zielposition liegt jetzt innerhalb des sichtbaren Bereiches -->
//STRIP001  //Cursor an die Zielposition setzen; merken, dass keine Ziel-
//STRIP001  //position mehr auf dem Stack steht.
//STRIP001  //Der neue sichtbare Bereich wird zuvor ermittelt.
//STRIP001  aTmpArea.Pos().Y() += lOffset;
//STRIP001  if( aTmpArea.IsInside(aDest) )
//STRIP001  {
//STRIP001      if( bSelect )
//STRIP001          SttSelect();
//STRIP001      else
//STRIP001          EndSelect();
//STRIP001
//STRIP001      bIsFrmSel = IsFrmSelected();
//STRIP001      bIsObjSel = 0 != IsObjSelected();
//STRIP001
//STRIP001      // Rahmenselektion aufheben
//STRIP001      if( bIsFrmSel || bIsObjSel )
//STRIP001      {
//STRIP001          UnSelectFrm();
//STRIP001          LeaveSelFrmMode();
//STRIP001          if ( bIsObjSel )
//STRIP001          {
//STRIP001              GetView().SetDrawFuncPtr( NULL );
//STRIP001              GetView().LeaveDrawCreate();
//STRIP001          }
//STRIP001
//STRIP001          CallChgLnk();
//STRIP001      }
//STRIP001
//STRIP001      (this->*fnSetCrsr)( &aDest, TRUE );
//STRIP001
//STRIP001      bDiff = aOldRect != GetCharRect();
//STRIP001
//STRIP001      if( bIsFrmSel )
//STRIP001      {
//STRIP001 //           CallChgLnk();
//STRIP001          // bei Frames immer nur die obere Ecke nehmen, damit dieser
//STRIP001          // wieder selektiert werden kann
//STRIP001          aOldRect.SSize( 5, 5 );
//STRIP001      }
//STRIP001
//STRIP001          // Zuruecksetzen des Dest. SPoint Flags
//STRIP001      bDestOnStack = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  // Position auf den Stack; bDiff besagt, ob ein Unterschied zwischen
//STRIP001  // der alten und der neuen Cursorposition besteht.
//STRIP001  pCrsrStack = new CrsrStack( bDiff, bIsFrmSel, aOldRect.Center(),
//STRIP001                              lOffset, pCrsrStack );
//STRIP001  return !bDestOnStack && bDiff;
//STRIP001 }



/*N*/ BOOL SwWrtShell::PopCrsr(BOOL bUpdate, BOOL bSelect)
/*N*/ {
/*N*/   if( 0 == pCrsrStack)
/*N*/       return FALSE;

/*?*/   const BOOL bValidPos = pCrsrStack->bValidCurPos;
/*?*/   if( bUpdate && bValidPos )
/*?*/   {
/*?*/           // falls ein Vorgaenger auf dem Stack steht, dessen Flag fuer eine
/*?*/           // gueltige Position verwenden.
/*?*/       SwRect aTmpArea(VisArea());
/*?*/       aTmpArea.Pos().Y() -= pCrsrStack->lOffset;
/*?*/       if( aTmpArea.IsInside( pCrsrStack->aDocPos ) )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( bSelect )
//STRIP001 /*?*/                SttSelect();
//STRIP001 /*?*/            else
//STRIP001 /*?*/                EndSelect();
//STRIP001 /*?*/
//STRIP001 /*?*/            (this->*fnSetCrsr)(&pCrsrStack->aDocPos, !pCrsrStack->bIsFrmSel);
//STRIP001 /*?*/            if( pCrsrStack->bIsFrmSel && IsObjSelectable(pCrsrStack->aDocPos))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                HideCrsr();
//STRIP001 /*?*/                SelectObj( pCrsrStack->aDocPos );
//STRIP001 /*?*/                EnterSelFrmMode( &pCrsrStack->aDocPos );
//STRIP001 /*?*/            }
/*?*/       }
/*?*/           // Falls eine Verschiebung zwischen dem sichtbaren Bereich
/*?*/           // und der gemerkten Cursorpositionen auftritt, werden
/*?*/           // alle gemerkten Positionen weggeschmissen
/*?*/       else
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 _ResetCursorStack();
/*?*/           return FALSE;
/*?*/       }
/*?*/   }
/*?*/   CrsrStack *pTmp = pCrsrStack;
/*?*/   pCrsrStack = pCrsrStack->pNext;
/*?*/   delete pTmp;
/*?*/   if( 0 == pCrsrStack )
/*?*/   {
/*?*/       ePageMove = MV_NO;
/*?*/       bDestOnStack = FALSE;
/*?*/   }
/*?*/   return bValidPos;
/*N*/ }

/*
 * Zuruecksetzen aller gepushten Cursorpositionen; dieser werden nicht
 * zur Anzeige gebracht ( --> Kein Start-/EndAction!!)
 */



//STRIP001 void SwWrtShell::_ResetCursorStack()
//STRIP001 {
//STRIP001  CrsrStack *pTmp = pCrsrStack;
//STRIP001  while(pCrsrStack)
//STRIP001  {
//STRIP001      pTmp = pCrsrStack->pNext;
//STRIP001      delete pCrsrStack;
//STRIP001      pCrsrStack = pTmp;
//STRIP001  }
//STRIP001  ePageMove = MV_NO;
//STRIP001  bDestOnStack = FALSE;
//STRIP001 }
/**************

    falls kein Stack existiert --> Selektionen aufheben
    falls Stack && Richtungswechsel
        --> Cursor poppen und return
    sonst
        --> Cursor pushen
             Cursor umsetzen

***************/



//STRIP001 BOOL SwWrtShell::PageCrsr(SwTwips lOffset, BOOL bSelect)
//STRIP001 {
//STRIP001  // nichts tun, wenn ein Offset von 0 angegeben wurde
//STRIP001  if(!lOffset) return FALSE;
//STRIP001      // Diente mal dazu, eine Neuformatierung fuer das Layout
//STRIP001      // zu erzwingen.
//STRIP001      // Hat so nicht funktioniert, da der Cursor nicht gesetzt
//STRIP001      // wurde, da dies innerhalb einer Start- / EndActionklammerung
//STRIP001      // nicht geschieht.
//STRIP001      // Da am Ende nur ViewShell::EndAction() gerufen wird,
//STRIP001      // findet auch hier keine Aktualisierung der Anzeige
//STRIP001      // der Cursorposition statt.
//STRIP001      // Die CrsrShell- Actionklammerung kann nicht verwendet werden,
//STRIP001      // da sie immer zu einer Anzeige des Cursors fuehrt, also auch,
//STRIP001      // wenn nach dem Blaettern in einen Bereich ohne gueltige Position
//STRIP001      // geblaettert wurde.
//STRIP001      //  ViewShell::StartAction();
//STRIP001  PageMove eDir = lOffset > 0? MV_PAGE_DOWN: MV_PAGE_UP;
//STRIP001      // Richtungswechsel und Stack vorhanden
//STRIP001  if( eDir != ePageMove && ePageMove != MV_NO && PopCrsr( TRUE, bSelect ))
//STRIP001      return TRUE;
//STRIP001
//STRIP001  const BOOL bRet = PushCrsr(lOffset, bSelect);
//STRIP001  ePageMove = eDir;
//STRIP001  return bRet;
//STRIP001 }



/*N*/ BOOL SwWrtShell::GotoPage(USHORT nPage, BOOL bRecord)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ShellMoveCrsr aTmp( this, FALSE);
//STRIP001 /*?*/    if( SwCrsrShell::GotoPage(nPage) && bRecord)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if(IsSelFrmMode())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            UnSelectFrm();
//STRIP001 /*?*/            LeaveSelFrmMode();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        return TRUE;
//STRIP001 /*?*/    }
/*N*/   return FALSE;
/*N*/ }



//STRIP001 FASTBOOL SwWrtShell::GotoBookmark( USHORT nPos, BOOL bSelect, BOOL bStart )
//STRIP001 {
//STRIP001  ShellMoveCrsr aTmp( this, bSelect );
//STRIP001  return SwCrsrShell::GotoBookmark( nPos, bStart );
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::SelectTxtAttr( USHORT nWhich, const SwTxtAttr* pAttr )
//STRIP001 {
//STRIP001     BOOL bRet;
//STRIP001     {
//STRIP001         MV_KONTEXT(this);
//STRIP001         SttSelect();
//STRIP001         bRet = SwCrsrShell::SelectTxtAttr( nWhich, FALSE, pAttr );
//STRIP001     }
//STRIP001     EndSelect();
//STRIP001     return bRet;
//STRIP001 }



}
