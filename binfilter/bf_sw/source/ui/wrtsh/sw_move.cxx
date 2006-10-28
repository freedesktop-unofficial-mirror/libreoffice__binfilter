/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_move.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:35:22 $
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


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
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





/*N*/ FASTBOOL SwWrtShell::Left( USHORT nMode, FASTBOOL bSelect,
/*N*/                             USHORT nCount, BOOL bBasicCall, BOOL bVisual )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     if ( !bSelect && !bBasicCall && IsCrsrReadonly()  && !GetViewOptions()->IsSelectionInReadonly())
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::Right( USHORT nMode, FASTBOOL bSelect,
/*N*/                             USHORT nCount, BOOL bBasicCall, BOOL bVisual )
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     if ( !bSelect && !bBasicCall && IsCrsrReadonly() && !GetViewOptions()->IsSelectionInReadonly() )
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::Up( FASTBOOL bSelect, USHORT nCount, BOOL bBasicCall )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     if ( !bSelect && !bBasicCall && IsCrsrReadonly()  && !GetViewOptions()->IsSelectionInReadonly())
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::Down( FASTBOOL bSelect, USHORT nCount, BOOL bBasicCall )
/*N*/  {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001      if ( !bSelect && !bBasicCall && IsCrsrReadonly() && !GetViewOptions()->IsSelectionInReadonly())
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::LeftMargin( FASTBOOL bSelect, FASTBOOL bBasicCall )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 if ( !bSelect && !bBasicCall && IsCrsrReadonly() )
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::RightMargin( FASTBOOL bSelect, FASTBOOL bBasicCall  )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 if ( !bSelect && !bBasicCall && IsCrsrReadonly() )
/*N*/ }









/*N*/ FASTBOOL SwWrtShell::SttDoc( FASTBOOL bSelect )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::EndDoc( FASTBOOL bSelect)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
/*N*/ }


/*N*/ FASTBOOL SwWrtShell::SttNxtPg( FASTBOOL bSelect )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
/*N*/ }









/*N*/ FASTBOOL SwWrtShell::EndPrvPg( FASTBOOL bSelect )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ShellMoveCrsr aTmp( this, bSelect );
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::SttPg( FASTBOOL bSelect )
/*N*/ {
/*?*/DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     ShellMoveCrsr aTmp( this, bSelect );
/*N*/ }



/*N*/ FASTBOOL SwWrtShell::EndPg( FASTBOOL bSelect )
/*N*/ {
/*?*/DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001     ShellMoveCrsr aTmp( this, bSelect );
/*N*/ }








/*------------------------------------------------------------------------
 Beschreibung:  Spaltenweises Springen
 Parameter:     mit oder ohne SSelection
 Return:        Erfolg oder Misserfolg
------------------------------------------------------------------------*/
























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



/**************

    falls kein Stack existiert --> Selektionen aufheben
    falls Stack && Richtungswechsel
        --> Cursor poppen und return
    sonst
        --> Cursor pushen
             Cursor umsetzen

***************/






/*N*/ BOOL SwWrtShell::GotoPage(USHORT nPage, BOOL bRecord)
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ShellMoveCrsr aTmp( this, FALSE);
/*N*/   return FALSE;
/*N*/ }









}
