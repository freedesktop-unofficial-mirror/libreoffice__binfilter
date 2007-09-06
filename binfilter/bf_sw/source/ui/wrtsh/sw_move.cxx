/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_move.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:14:41 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


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

}
