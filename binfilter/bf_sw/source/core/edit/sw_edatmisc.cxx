/*************************************************************************
 *
 *  $RCSfile: sw_edatmisc.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:19:35 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>      // fuer aNodes
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>      // fuer SwPaM
// auto strip #endif
// auto strip #ifndef _EDIMP_HXX
// auto strip #include <edimp.hxx>    // fuer MACROS
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>   // fuer die UndoIds
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>    // fuer Get-/ChgFmt Set-/GetAttrXXX
// auto strip #endif
namespace binfilter {



/*************************************
 * harte Formatierung (Attribute)
 *************************************/


//STRIP001 void SwEditShell::ResetAttr()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  BOOL bUndoGroup = GetCrsr()->GetNext() != GetCrsr();
//STRIP001  if( bUndoGroup )
//STRIP001      GetDoc()->StartUndo(UNDO_RESETATTR);
//STRIP001
//STRIP001      FOREACHPAM_START(this)
//STRIP001          // if ( PCURCRSR->HasMark() )
//STRIP001              GetDoc()->ResetAttr(*PCURCRSR);
//STRIP001      FOREACHPAM_END()
//STRIP001
//STRIP001  if( bUndoGroup )
//STRIP001      GetDoc()->EndUndo(UNDO_RESETATTR);
//STRIP001  CallChgLnk();
//STRIP001  EndAllAction();
//STRIP001 }



//STRIP001 void SwEditShell::GCAttr()
//STRIP001 {
//STRIP001 //JP 04.02.97: wozu eine Action-Klammerung - ein Formatierung sollte nicht
//STRIP001 //               ausgeloest werden, so dass es hier ueberfluessig ist.
//STRIP001 //               Sonst Probleme im MouseBut.DownHdl - Bug 35562
//STRIP001 //   StartAllAction();
//STRIP001  FOREACHPAM_START(this)
//STRIP001      SwTxtNode *pTxtNode;
//STRIP001      if ( !PCURCRSR->HasMark() )
//STRIP001      {
//STRIP001          if( 0 != (pTxtNode = GetDoc()->GetNodes()[
//STRIP001                              PCURCRSR->GetPoint()->nNode]->GetTxtNode()))
//STRIP001              pTxtNode->GCAttr();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          const SwNodeIndex& rEnd = PCURCRSR->End()->nNode;
//STRIP001          SwNodeIndex aIdx( PCURCRSR->Start()->nNode );
//STRIP001          SwNode* pNd = &aIdx.GetNode();
//STRIP001          do {
//STRIP001              if( pNd->IsTxtNode() )
//STRIP001                  ((SwTxtNode*)pNd)->GCAttr();
//STRIP001          }
//STRIP001          while( 0 != ( pNd = GetDoc()->GetNodes().GoNext( &aIdx )) &&
//STRIP001                  aIdx <= rEnd );
//STRIP001      }
//STRIP001  FOREACHPAM_END()
//STRIP001 //   EndAllAction();
//STRIP001 }

// Setze das Attribut als neues default Attribut im Dokument.


//STRIP001 void SwEditShell::SetDefault( const SfxPoolItem& rFmtHint )
//STRIP001 {
//STRIP001  // 7502: Action-Klammerung
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetDefault( rFmtHint );
//STRIP001  EndAllAction();
//STRIP001 }

/*

void SwEditShell::SetDefault( const SfxItemSet& rSet )
{
    // 7502: Action-Klammerung
    StartAllAction();
    GetDoc()->SetDefault( rSet );
    EndAllAction();
}
*/

// Erfrage das Default Attribut in diesem Dokument.

/*N*/ const SfxPoolItem& SwEditShell::GetDefault( USHORT nFmtHint ) const
/*N*/ {
/*N*/   return GetDoc()->GetDefault( nFmtHint );
/*N*/
/*N*/ }


//STRIP001 void SwEditShell::SetAttr( const SfxPoolItem& rHint, USHORT nFlags )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )     // Ring von Cursorn
//STRIP001  {
//STRIP001      FASTBOOL bIsTblMode = IsTableMode();
//STRIP001      GetDoc()->StartUndo(UNDO_INSATTR);
//STRIP001
//STRIP001      FOREACHPAM_START(this)
//STRIP001          if( PCURCRSR->HasMark() && ( bIsTblMode ||
//STRIP001              *PCURCRSR->GetPoint() != *PCURCRSR->GetMark() ))
//STRIP001              GetDoc()->Insert(*PCURCRSR, rHint, nFlags );
//STRIP001      FOREACHPAM_END()
//STRIP001
//STRIP001      GetDoc()->EndUndo(UNDO_INSATTR);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !HasSelection() )
//STRIP001          UpdateAttr();
//STRIP001      GetDoc()->Insert( *pCrsr, rHint, nFlags );
//STRIP001  }
//STRIP001  EndAllAction();
//STRIP001 }


//STRIP001 void SwEditShell::SetAttr( const SfxItemSet& rSet, USHORT nFlags )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() != pCrsr )     // Ring von Cursorn
//STRIP001  {
//STRIP001      FASTBOOL bIsTblMode = IsTableMode();
//STRIP001      GetDoc()->StartUndo(UNDO_INSATTR);
//STRIP001
//STRIP001      FOREACHPAM_START(this)
//STRIP001          if( PCURCRSR->HasMark() && ( bIsTblMode ||
//STRIP001              *PCURCRSR->GetPoint() != *PCURCRSR->GetMark() ))
//STRIP001              GetDoc()->Insert(*PCURCRSR, rSet, nFlags );
//STRIP001      FOREACHPAM_END()
//STRIP001
//STRIP001      GetDoc()->EndUndo(UNDO_INSATTR);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !HasSelection() )
//STRIP001          UpdateAttr();
//STRIP001      GetDoc()->Insert( *pCrsr, rSet, nFlags );
//STRIP001  }
//STRIP001  EndAllAction();
//STRIP001 }




}
