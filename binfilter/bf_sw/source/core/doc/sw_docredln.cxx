/*************************************************************************
 *
 *  $RCSfile: sw_docredln.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-25 09:53:59 $
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

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _SFX_ITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDARR_HXX
#include <ndarr.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
namespace binfilter {

#ifdef PRODUCT

    #define _CHECK_REDLINE( pDoc )

#else

    // helper function for lcl_CheckRedline
    // make sure that pPos->nContent points into pPos->nNode
    // (or into the 'special' no-content-node-IndexReg)
//STRIP001     void lcl_CheckPosition( const SwPosition* pPos )
//STRIP001     {
//STRIP001         SwPosition aComparePos( *pPos );
//STRIP001         aComparePos.nContent.Assign(
//STRIP001             aComparePos.nNode.GetNode().GetCntntNode(), 0 );
//STRIP001         ASSERT( pPos->nContent.GetIdxReg() == aComparePos.nContent.GetIdxReg(),
//STRIP001                 "redline table corrupted: illegal position" );
//STRIP001     }

//STRIP001     void lcl_CheckPam( const SwPaM* pPam )
//STRIP001     {
//STRIP001         ASSERT( pPam != NULL, "illegal argument" );
//STRIP001         lcl_CheckPosition( pPam->GetPoint() );
//STRIP001         lcl_CheckPosition( pPam->GetMark() );
//STRIP001     }

    // check validity of the redline table. Checks redline bounds, and make
    // sure the redlines are sorted and non-overlapping.
/*N*/   void lcl_CheckRedline( const SwDoc* pDoc )
/*N*/   {
/*N*/       const SwRedlineTbl& rTbl = pDoc->GetRedlineTbl();
/*N*/
/*N*/         // verify valid redline positions
/*N*/       for( USHORT i = 0; i < rTbl.Count(); ++i )
/*?*/             {DBG_ASSERT(0, "STRIP");} //STRIP001 lcl_CheckPam( rTbl[ i ] );
/*N*/
/*N*/         for( USHORT j = 0; j < rTbl.Count(); ++j )
/*N*/         {
/*N*/             // check for empty redlines
/*N*/             ASSERT( ( *(rTbl[j]->GetPoint()) != *(rTbl[j]->GetMark()) ) ||
/*N*/                     ( rTbl[j]->GetContentIdx() != NULL ),
/*N*/                     "redline table corrupted: empty redline" );
/*N*/       }
/*N*/
/*N*/         // verify proper redline sorting
/*N*/       for( USHORT n = 1; n < rTbl.Count(); ++n )
/*N*/       {
/*?*/           const SwRedline* pPrev = rTbl[ n-1 ];
/*?*/             const SwRedline* pCurrent = rTbl[ n ];
/*?*/
/*?*/             // check redline sorting
/*?*/             ASSERT( *pPrev->Start() <= *pCurrent->Start(),
/*?*/                     "redline table corrupted: not sorted correctly" );
/*?*/
/*?*/             // check for overlapping redlines
/*?*/             ASSERT( *pPrev->End() <= *pCurrent->Start(),
/*?*/                     "redline table corrupted: overlapping redlines" );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   #define _CHECK_REDLINE( pDoc ) lcl_CheckRedline( pDoc );
/*N*/
/*N*/ #endif

/*N*/ SV_IMPL_OP_PTRARR_SORT( _SwRedlineTbl, SwRedlinePtr )

/*N*/ void SwDoc::SetRedlineMode( USHORT eMode )
/*N*/ {
/*N*/   if( eRedlineMode != eMode )
/*N*/   {
/*N*/       if( (REDLINE_SHOW_MASK & eRedlineMode) != (REDLINE_SHOW_MASK & eMode)
/*N*/           || 0 == (REDLINE_SHOW_MASK & eMode) )
/*N*/       {
/*N*/           // und dann alles verstecken, anzeigen
/*N*/           void (SwRedline::*pFnc)( USHORT ) = 0;
/*N*/
/*N*/           switch( REDLINE_SHOW_MASK & eMode )
/*N*/           {
/*N*/           case REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE:
/*N*/               pFnc = &SwRedline::Show;
/*N*/               break;
/*N*/           case REDLINE_SHOW_INSERT:
/*N*/               pFnc = &SwRedline::Hide;
/*N*/               break;
/*N*/           case REDLINE_SHOW_DELETE:
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 pFnc = &SwRedline::ShowOriginal;
/*?*/               break;
/*N*/
/*N*/           default:
/*N*/               pFnc = &SwRedline::Hide;
/*N*/               eMode |= REDLINE_SHOW_INSERT;
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           _CHECK_REDLINE( this )
/*N*/
/*N*/           if( pFnc )
/*N*/               for( USHORT nLoop = 1; nLoop <= 2; ++nLoop )
/*N*/                   for( USHORT i = 0; i < pRedlineTbl->Count(); ++i )
/*N*/                       ((*pRedlineTbl)[ i ]->*pFnc)( nLoop );
/*N*/           _CHECK_REDLINE( this )
/*N*/       }
/*N*/       eRedlineMode = (SwRedlineMode)eMode;
/*N*/   }
/*N*/ }

//STRIP001 inline BOOL IsPrevPos( const SwPosition rPos1, const SwPosition rPos2 )
//STRIP001 {
//STRIP001  const SwCntntNode* pCNd;
//STRIP001  return !rPos2.nContent.GetIndex() &&
//STRIP001          rPos2.nNode.GetIndex() - 1 == rPos1.nNode.GetIndex() &&
//STRIP001          0 != ( pCNd = rPos1.nNode.GetNode().GetCntntNode() )
//STRIP001              ? rPos1.nContent.GetIndex() == pCNd->Len()
//STRIP001              : 0;
//STRIP001 }

/*

Text heisst, nicht von Redline "verseuchter" Text.

Verhalten von Insert-Redline:
    - im Text                           - Redline Object einfuegen
    - im InsertRedline (eigenes)        - ignorieren, bestehendes wird
                                          aufgespannt
    - im InsertRedline (andere)         - Insert Redline aufsplitten
                                          Redline Object einfuegen
    - in DeleteRedline                  - Delete Redline aufsplitten oder
                                          am Ende/Anfang verschieben

Verhalten von Delete-Redline:
    - im Text                           - Redline Object einfuegen
    - im DeleteRedline (eigenes/andere) - ignorieren
    - im InsertRedline (eigenes)        - ignorieren, Zeichen aber loeschen
    - im InsertRedline (andere)         - Insert Redline aufsplitten
                                          Redline Object einfuegen
    - Ueberlappung von Text und         - Text in eigenen Insert loeschen,
      eigenem Insert                      im andereren Text aufspannen (bis
                                          zum Insert!
    - Ueberlappung von Text und         - Redline Object einfuegen, der
      anderem Insert                      andere Insert wird vom Delete
                                          ueberlappt
*/

/*N*/ BOOL SwDoc::AppendRedline( SwRedline* pNewRedl, BOOL bCallDelete )
/*N*/ {
DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001 //STRIP001  _CHECK_REDLINE( this )
//STRIP001
//STRIP001  if( IsRedlineOn() && !IsShowOriginal( eRedlineMode ) &&
//STRIP001       pNewRedl->GetAuthorString().Len() )
//STRIP001  {
//STRIP001      pNewRedl->InvalidateRange();
//STRIP001
//STRIP001      if( bIsAutoFmtRedline )
//STRIP001      {
//STRIP001          pNewRedl->SetAutoFmtFlag();
//STRIP001          if( pAutoFmtRedlnComment && pAutoFmtRedlnComment->Len() )
//STRIP001          {
//STRIP001              pNewRedl->SetComment( *pAutoFmtRedlnComment );
//STRIP001              pNewRedl->SetSeqNo( nAutoFmtRedlnCommentNo );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      BOOL bCompress = FALSE;
//STRIP001      SwPosition* pStt = pNewRedl->Start(),
//STRIP001                * pEnd = pStt == pNewRedl->GetPoint() ? pNewRedl->GetMark()
//STRIP001                                                      : pNewRedl->GetPoint();
//STRIP001      USHORT n = 0;
//STRIP001          // zur StartPos das erste Redline suchen
//STRIP001      if( !GetRedline( *pStt, &n ) && n )
//STRIP001          --n;
//STRIP001
//STRIP001      for( ; pNewRedl && n < pRedlineTbl->Count(); ++n )
//STRIP001      {
//STRIP001
//STRIP001 #ifdef DVO_TEST
//STRIP001          _CHECK_REDLINE( this )
//STRIP001 #endif
//STRIP001
//STRIP001          SwRedline* pRedl = (*pRedlineTbl)[ n ];
//STRIP001          SwPosition* pRStt = pRedl->Start(),
//STRIP001                    * pREnd = pRStt == pRedl->GetPoint() ? pRedl->GetMark()
//STRIP001                                                         : pRedl->GetPoint();
//STRIP001
//STRIP001             // #i8518# remove empty redlines while we're at it
//STRIP001             if( ( *pRStt == *pREnd ) &&
//STRIP001                 ( pRedl->GetContentIdx() == NULL ) )
//STRIP001             {
//STRIP001                 pRedlineTbl->DeleteAndDestroy(n);
//STRIP001                 continue;
//STRIP001             }
//STRIP001
//STRIP001          SwComparePosition eCmpPos = ComparePosition( *pStt, *pEnd, *pRStt, *pREnd );
//STRIP001
//STRIP001          switch( pNewRedl->GetType() )
//STRIP001          {
//STRIP001          case REDLINE_INSERT:
//STRIP001              switch( pRedl->GetType() )
//STRIP001              {
//STRIP001              case REDLINE_INSERT:
//STRIP001                  if( pRedl->IsOwnRedline( *pNewRedl ) )
//STRIP001                  {
//STRIP001                      bool bDelete = false;
//STRIP001
//STRIP001                      // ggfs. verschmelzen?
//STRIP001                      if( (( POS_BEHIND == eCmpPos &&
//STRIP001                                IsPrevPos( *pREnd, *pStt ) ) ||
//STRIP001                           ( POS_COLLIDE_START == eCmpPos ) ||
//STRIP001                              ( POS_OVERLAP_BEHIND == eCmpPos ) ) &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ) &&
//STRIP001                          ( n+1 >= pRedlineTbl->Count() ||
//STRIP001                           *(*pRedlineTbl)[ n+1 ]->Start() != *pREnd ))
//STRIP001                      {
//STRIP001                          pRedl->SetEnd( *pEnd, pREnd );
//STRIP001                          if( !pRedl->HasValidRange() )
//STRIP001                          {
//STRIP001                              // neu einsortieren
//STRIP001                              pRedlineTbl->Remove( n );
//STRIP001                              pRedlineTbl->Insert( pRedl );
//STRIP001                          }
//STRIP001
//STRIP001                          bDelete = true;
//STRIP001                      }
//STRIP001                      else if( (( POS_BEFORE == eCmpPos &&
//STRIP001                                  IsPrevPos( *pEnd, *pRStt ) ) ||
//STRIP001                                ( POS_COLLIDE_END == eCmpPos ) ||
//STRIP001                                   ( POS_OVERLAP_BEFORE == eCmpPos ) ) &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ) &&
//STRIP001                          ( !n ||
//STRIP001                           *(*pRedlineTbl)[ n-1 ]->End() != *pRStt ))
//STRIP001                      {
//STRIP001                          pRedl->SetStart( *pStt, pRStt );
//STRIP001                          // neu einsortieren
//STRIP001                          pRedlineTbl->Remove( n );
//STRIP001                          pRedlineTbl->Insert( pRedl );
//STRIP001
//STRIP001                          bDelete = true;
//STRIP001                      }
//STRIP001                      else if ( POS_OUTSIDE == eCmpPos )
//STRIP001                      {
//STRIP001                          // #107164# own insert-over-insert
//STRIP001                          // redlines: just scrap the inside ones
//STRIP001                          pRedlineTbl->Remove( n );
//STRIP001                          pRedlineTbl->Insert( pRedl );
//STRIP001
//STRIP001                          bDelete = true;
//STRIP001                      }
//STRIP001                      // <- #107164#
//STRIP001                      else if( POS_OVERLAP_BEHIND == eCmpPos )
//STRIP001                      {
//STRIP001                          *pStt = *pREnd;
//STRIP001                      }
//STRIP001                      else if( POS_OVERLAP_BEFORE == eCmpPos )
//STRIP001                      {
//STRIP001                          *pEnd = *pRStt;
//STRIP001                      }
//STRIP001                      else if( POS_INSIDE == eCmpPos || POS_EQUAL == eCmpPos)
//STRIP001                          bDelete = true;
//STRIP001
//STRIP001                      if( bDelete )
//STRIP001                      {
//STRIP001                          delete pNewRedl, pNewRedl = 0;
//STRIP001                          bCompress = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else if( POS_INSIDE == eCmpPos )
//STRIP001                  {
//STRIP001                      // aufsplitten
//STRIP001                      if( *pEnd != *pREnd )
//STRIP001                      {
//STRIP001                          SwRedline* pCpy = new SwRedline( *pRedl );
//STRIP001                          pCpy->SetStart( *pEnd );
//STRIP001                          pRedlineTbl->Insert( pCpy );
//STRIP001                      }
//STRIP001                      pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      if( !pRedl->HasValidRange() )
//STRIP001                      {
//STRIP001                          // neu einsortieren
//STRIP001                          pRedlineTbl->Remove( n );
//STRIP001                          pRedlineTbl->Insert( pRedl );
//STRIP001                      }
//STRIP001                  }
//STRIP001                     else if ( POS_OUTSIDE == eCmpPos )
//STRIP001                     {
//STRIP001                         // #102366# handle overlapping redlines in broken
//STRIP001                         // documents
//STRIP001
//STRIP001                         // split up the new redline, since it covers the
//STRIP001                         // existing redline. Insert the first part, and
//STRIP001                         // progress with the remainder as usual
//STRIP001                         SwRedline* pSplit = new SwRedline( *pNewRedl );
//STRIP001                         pSplit->SetEnd( *pRStt );
//STRIP001                         pNewRedl->SetStart( *pREnd );
//STRIP001                         pRedlineTbl->Insert( pSplit );
//STRIP001                     }
//STRIP001                     else if ( POS_OVERLAP_BEHIND == eCmpPos )
//STRIP001                     {
//STRIP001                         // #107164# handle overlapping redlines in broken
//STRIP001                         // documents
//STRIP001                         pNewRedl->SetStart( *pREnd );
//STRIP001                     }
//STRIP001                     else if ( POS_OVERLAP_BEFORE == eCmpPos )
//STRIP001                     {
//STRIP001                         // #107164# handle overlapping redlines in broken
//STRIP001                         // documents
//STRIP001                         pNewRedl->SetEnd( *pRStt );
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case REDLINE_DELETE:
//STRIP001                  if( POS_INSIDE == eCmpPos )
//STRIP001                  {
//STRIP001                      // aufsplitten
//STRIP001                      SwRedline* pCpy = new SwRedline( *pRedl );
//STRIP001                      pCpy->SetStart( *pEnd );
//STRIP001                      pRedlineTbl->Insert( pCpy );
//STRIP001                      pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      if( !pRedl->HasValidRange() )
//STRIP001                      {
//STRIP001                          // neu einsortieren
//STRIP001                          pRedlineTbl->Remove( n );
//STRIP001                          pRedlineTbl->Insert( pRedl, n );
//STRIP001                      }
//STRIP001                  }
//STRIP001                     else if ( POS_OUTSIDE == eCmpPos )
//STRIP001                     {
//STRIP001                         // #102366# handle overlapping redlines in broken
//STRIP001                         // documents
//STRIP001
//STRIP001                         // split up the new redline, since it covers the
//STRIP001                         // existing redline. Insert the first part, and
//STRIP001                         // progress with the remainder as usual
//STRIP001                         SwRedline* pSplit = new SwRedline( *pNewRedl );
//STRIP001                         pSplit->SetEnd( *pRStt );
//STRIP001                         pNewRedl->SetStart( *pREnd );
//STRIP001                         pRedlineTbl->Insert( pSplit );
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case REDLINE_FORMAT:
//STRIP001                  switch( eCmpPos )
//STRIP001                  {
//STRIP001                  case POS_OVERLAP_BEFORE:
//STRIP001                      pRedl->SetStart( *pEnd, pRStt );
//STRIP001                      // neu einsortieren
//STRIP001                      pRedlineTbl->Remove( n );
//STRIP001                      pRedlineTbl->Insert( pRedl, n );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OVERLAP_BEHIND:
//STRIP001                      pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_EQUAL:
//STRIP001                  case POS_OUTSIDE:
//STRIP001                      // ueberlappt den akt. komplett oder hat gleiche
//STRIP001                      // Ausdehung, dann muss der alte geloescht werden
//STRIP001                      pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_INSIDE:
//STRIP001                      // ueberlappt den akt. komplett, dann muss
//STRIP001                      // der neue gesplittet oder verkuertzt werden
//STRIP001                      if( *pEnd != *pREnd )
//STRIP001                      {
//STRIP001                          SwRedline* pNew = new SwRedline( *pRedl );
//STRIP001                          pNew->SetStart( *pEnd );
//STRIP001                          pRedl->SetEnd( *pStt, pREnd );
//STRIP001                          AppendRedline( pNew, bCallDelete );
//STRIP001                          n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                      }
//STRIP001                      else
//STRIP001                          pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case REDLINE_DELETE:
//STRIP001              switch( pRedl->GetType() )
//STRIP001              {
//STRIP001              case REDLINE_DELETE:
//STRIP001                  switch( eCmpPos )
//STRIP001                  {
//STRIP001                  case POS_OUTSIDE:
//STRIP001                      {
//STRIP001                          // ueberlappt den akt. komplett
//STRIP001                          // dann muss der neue gesplittet werden
//STRIP001                          if( *pEnd != *pREnd )
//STRIP001                          {
//STRIP001                              SwRedline* pNew = new SwRedline( *pNewRedl );
//STRIP001                              pNew->SetStart( *pREnd );
//STRIP001                              pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                              AppendRedline( pNew, bCallDelete );
//STRIP001                              n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                          }
//STRIP001                          else
//STRIP001                              pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                      }
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_INSIDE:
//STRIP001                  case POS_EQUAL:
//STRIP001                      delete pNewRedl, pNewRedl = 0;
//STRIP001                      bCompress = TRUE;
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OVERLAP_BEFORE:
//STRIP001                  case POS_OVERLAP_BEHIND:
//STRIP001                      if( pRedl->IsOwnRedline( *pNewRedl ) &&
//STRIP001 //                           1 == pRedl->GetStackCount() &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ))
//STRIP001                      {
//STRIP001                          // dann kann das zusammengefasst werden, sprich
//STRIP001                          // der neue deckt das schon ab.
//STRIP001                          if( POS_OVERLAP_BEHIND == eCmpPos )
//STRIP001                              pNewRedl->SetStart( *pRStt, pStt );
//STRIP001                          else
//STRIP001                              pNewRedl->SetEnd( *pREnd, pEnd );
//STRIP001                          pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      }
//STRIP001                      else if( POS_OVERLAP_BEHIND == eCmpPos )
//STRIP001                          pNewRedl->SetStart( *pREnd, pStt );
//STRIP001                      else
//STRIP001                          pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_COLLIDE_START:
//STRIP001                  case POS_COLLIDE_END:
//STRIP001                      if( pRedl->IsOwnRedline( *pNewRedl ) &&
//STRIP001 //                           1 == pRedl->GetStackCount() &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ) )
//STRIP001                      {
//STRIP001                          if( IsHideChanges( eRedlineMode ))
//STRIP001                          {
//STRIP001                              // dann erstmal sichtbar machen, bevor
//STRIP001                              // die zusammengefasst werden koennen!
//STRIP001                              // Damit pNew auch beim Verschieben der
//STRIP001                              // Indizies behandelt wird, erstmal
//STRIP001                              // temporaer einfuegen
//STRIP001                              pRedlineTbl->SavePtrInArr( pNewRedl );
//STRIP001                              pRedl->Show();
//STRIP001                              pRedlineTbl->Remove( pRedlineTbl->GetPos(pNewRedl ));
//STRIP001                              pRStt = pRedl->Start();
//STRIP001                              pREnd = pRedl->End();
//STRIP001                          }
//STRIP001
//STRIP001                          // dann kann das zusammengefasst werden, sprich
//STRIP001                          // der neue deckt das schon ab.
//STRIP001                          if( POS_COLLIDE_START == eCmpPos )
//STRIP001                              pNewRedl->SetStart( *pRStt, pStt );
//STRIP001                          else
//STRIP001                              pNewRedl->SetEnd( *pREnd, pEnd );
//STRIP001
//STRIP001                             // delete current (below), and restart process with
//STRIP001                             // previous
//STRIP001                             USHORT nToBeDeleted = n;
//STRIP001                             n--;
//STRIP001
//STRIP001                             // #107359# Do it again, Sam!
//STRIP001                             // If you can do it for them, you can do it for me.
//STRIP001                             if( *(pNewRedl->Start()) <= *pREnd )
//STRIP001                             {
//STRIP001                                 // Whoooah, we just extended the new 'redline'
//STRIP001                                 // beyond previous redlines, so better start
//STRIP001                                 // again. Of course this is not supposed to
//STRIP001                                 // happen, and in an ideal world it doesn't,
//STRIP001                                 // but unfortunately this code is buggy and
//STRIP001                                 // totally rotten so it does happen and we
//STRIP001                                 // better fix it.
//STRIP001                                 n = -1;
//STRIP001                             }
//STRIP001
//STRIP001                             pRedlineTbl->DeleteAndDestroy( nToBeDeleted );
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case REDLINE_INSERT:
//STRIP001                  if( pRedl->IsOwnRedline( *pNewRedl ) )
//STRIP001                  {
//STRIP001                      SwRedlineMode eOld = eRedlineMode;
//STRIP001                      if( eOld & REDLINE_DONTCOMBINE_REDLINES )
//STRIP001                          break;
//STRIP001
//STRIP001 // auf NONE setzen, damit das Delete::Redo die RedlineDaten wieder richtig
//STRIP001 // zusammen fasst! Der ShowMode muss erhalten bleiben!
//STRIP001                      eRedlineMode = (SwRedlineMode)(eOld & ~(REDLINE_ON | REDLINE_IGNORE));
//STRIP001                      switch( eCmpPos )
//STRIP001                      {
//STRIP001                      case POS_EQUAL:
//STRIP001                          bCompress = TRUE;
//STRIP001                          pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                          // kein break!
//STRIP001
//STRIP001                      case POS_INSIDE:
//STRIP001                          if( bCallDelete )
//STRIP001                          {
//STRIP001                              eRedlineMode = (SwRedlineMode)
//STRIP001                                  (eRedlineMode | REDLINE_IGNOREDELETE_REDLINES);
//STRIP001
//STRIP001                                 // #98863# DeleteAndJoin does not yield the
//STRIP001                                 // desired result if there is no paragraph to
//STRIP001                                 // join with, i.e. at the end of the document.
//STRIP001                                 // For this case, we completely delete the
//STRIP001                                 // paragraphs (if, of course, we also start on
//STRIP001                                 // a paragraph boundary).
//STRIP001                                 if( (pStt->nContent == 0) &&
//STRIP001                                     pEnd->nNode.GetNode().IsEndNode() )
//STRIP001                                 {
//STRIP001                                     pEnd->nNode--;
//STRIP001                                     pEnd->nContent.Assign(
//STRIP001                                         pEnd->nNode.GetNode().GetTxtNode(), 0);
//STRIP001                                     DelFullPara( *pNewRedl );
//STRIP001                                 }
//STRIP001                                 else
//STRIP001                                     DeleteAndJoin( *pNewRedl );
//STRIP001
//STRIP001                              bCompress = TRUE;
//STRIP001                          }
//STRIP001                          delete pNewRedl, pNewRedl = 0;
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OUTSIDE:
//STRIP001                          {
//STRIP001                              pRedlineTbl->Remove( n-- );
//STRIP001                              // damit pNew auch beim Verschieben der Indizies
//STRIP001                              // behandelt wird, erstmal temp. einfuegen
//STRIP001                              if( bCallDelete )
//STRIP001                              {
//STRIP001                                  pRedlineTbl->SavePtrInArr( pNewRedl );
//STRIP001                                  DeleteAndJoin( *pRedl );
//STRIP001                                  USHORT nFnd = pRedlineTbl->GetPos(pNewRedl );
//STRIP001                                  if( USHRT_MAX != nFnd )
//STRIP001                                      pRedlineTbl->Remove( nFnd );
//STRIP001                                  else
//STRIP001                                      pNewRedl = 0;
//STRIP001                              }
//STRIP001                              delete pRedl;
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OVERLAP_BEFORE:
//STRIP001                          {
//STRIP001                              SwPaM aPam( *pRStt, *pEnd );
//STRIP001
//STRIP001                              if( *pEnd == *pREnd )
//STRIP001                                  pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  pRedl->SetStart( *pEnd, pRStt );
//STRIP001                                  // neu einsortieren
//STRIP001                                  pRedlineTbl->Remove( n );
//STRIP001                                  pRedlineTbl->Insert( pRedl, n );
//STRIP001                              }
//STRIP001
//STRIP001                              if( bCallDelete )
//STRIP001                              {
//STRIP001                                  // damit pNew auch beim Verschieben der Indizies
//STRIP001                                  // behandelt wird, erstmal temp. einfuegen
//STRIP001                                  pRedlineTbl->SavePtrInArr( pNewRedl );
//STRIP001                                  DeleteAndJoin( aPam );
//STRIP001                                  USHORT nFnd = pRedlineTbl->GetPos(pNewRedl );
//STRIP001                                  if( USHRT_MAX != nFnd )
//STRIP001                                      pRedlineTbl->Remove( nFnd );
//STRIP001                                  else
//STRIP001                                      pNewRedl = 0;
//STRIP001                                  n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                              }
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OVERLAP_BEHIND:
//STRIP001                          {
//STRIP001                              SwPaM aPam( *pStt, *pREnd );
//STRIP001
//STRIP001                              if( *pStt == *pRStt )
//STRIP001                                  pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                              else
//STRIP001                                  pRedl->SetEnd( *pStt, pREnd );
//STRIP001
//STRIP001                              if( bCallDelete )
//STRIP001                              {
//STRIP001                                  // damit pNew auch beim Verschieben der Indizies
//STRIP001                                  // behandelt wird, erstmal temp. einfuegen
//STRIP001                                  pRedlineTbl->SavePtrInArr( pNewRedl );
//STRIP001                                  DeleteAndJoin( aPam );
//STRIP001                                  USHORT nFnd = pRedlineTbl->GetPos(pNewRedl );
//STRIP001                                  if( USHRT_MAX != nFnd )
//STRIP001                                      pRedlineTbl->Remove( nFnd );
//STRIP001                                  else
//STRIP001                                      pNewRedl = 0;
//STRIP001                                  n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                              }
//STRIP001                          }
//STRIP001                          break;
//STRIP001                      }
//STRIP001
//STRIP001                      eRedlineMode = eOld;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                         // it may be necessary to split the existing redline in
//STRIP001                         // two. In this case, pRedl will be changed to cover
//STRIP001                         // only part of it's former range, and pNew will cover
//STRIP001                         // the remainder.
//STRIP001                      SwRedline* pNew = 0;
//STRIP001
//STRIP001                      switch( eCmpPos )
//STRIP001                      {
//STRIP001                      case POS_EQUAL:
//STRIP001                          {
//STRIP001                              pRedl->PushData( *pNewRedl );
//STRIP001                              delete pNewRedl, pNewRedl = 0;
//STRIP001                              if( IsHideChanges( eRedlineMode ))
//STRIP001                                  pRedl->Hide();
//STRIP001                              bCompress = TRUE;
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_INSIDE:
//STRIP001                          {
//STRIP001                              pNewRedl->PushData( *pRedl, FALSE );
//STRIP001                              if( *pRStt == *pStt )
//STRIP001                              {
//STRIP001                                  pRedl->SetStart( *pEnd, pRStt );
//STRIP001                                  // neu einsortieren
//STRIP001                                  pRedlineTbl->Remove( n );
//STRIP001                                  pRedlineTbl->Insert( pRedl, n );
//STRIP001                              }
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  if( *pREnd == *pEnd )
//STRIP001                                      pRedl->SetEnd( *pStt, pREnd );
//STRIP001                                  else
//STRIP001                                  {
//STRIP001                                      pNew = new SwRedline( *pRedl );
//STRIP001                                      pNew->SetStart( *pEnd );
//STRIP001                                      pRedl->SetEnd( *pStt, pREnd );
//STRIP001                                  }
//STRIP001                                  if( !pRedl->HasValidRange() )
//STRIP001                                  {
//STRIP001                                      // neu einsortieren
//STRIP001                                      pRedlineTbl->Remove( n );
//STRIP001                                      pRedlineTbl->Insert( pRedl, n );
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OUTSIDE:
//STRIP001                          {
//STRIP001                              pNew = new SwRedline( *pNewRedl );
//STRIP001                              pRedl->PushData( *pNewRedl );
//STRIP001
//STRIP001                              pNew->SetEnd( *pRStt );
//STRIP001                              pNewRedl->SetStart( *pREnd, pStt );
//STRIP001                              bCompress = TRUE;
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OVERLAP_BEFORE:
//STRIP001                          {
//STRIP001                              if( *pEnd == *pREnd )
//STRIP001                              {
//STRIP001                                  pRedl->PushData( *pNewRedl );
//STRIP001                                  pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                                  if( IsHideChanges( eRedlineMode ))
//STRIP001                                  {
//STRIP001                                      pRedlineTbl->SavePtrInArr( pNewRedl );
//STRIP001                                      pRedl->Hide();
//STRIP001                                      pRedlineTbl->Remove(
//STRIP001                                          pRedlineTbl->GetPos(pNewRedl ));
//STRIP001                                  }
//STRIP001                              }
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  pNew = new SwRedline( *pRedl );
//STRIP001                                  pNew->PushData( *pNewRedl );
//STRIP001                                  pNew->SetEnd( *pEnd );
//STRIP001                                  pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                                  pRedl->SetStart( *pNew->End(), pRStt ) ;
//STRIP001                                  // neu einsortieren
//STRIP001                                  pRedlineTbl->Remove( n );
//STRIP001                                  pRedlineTbl->Insert( pRedl );
//STRIP001                              }
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OVERLAP_BEHIND:
//STRIP001                          {
//STRIP001                              if( *pStt == *pRStt )
//STRIP001                              {
//STRIP001                                  pRedl->PushData( *pNewRedl );
//STRIP001                                  pNewRedl->SetStart( *pREnd, pStt );
//STRIP001                                  if( IsHideChanges( eRedlineMode ))
//STRIP001                                  {
//STRIP001                                      pRedlineTbl->SavePtrInArr( pNewRedl );
//STRIP001                                      pRedl->Hide();
//STRIP001                                      pRedlineTbl->Remove(
//STRIP001                                          pRedlineTbl->GetPos(pNewRedl ));
//STRIP001                                  }
//STRIP001                              }
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  pNew = new SwRedline( *pRedl );
//STRIP001                                  pNew->PushData( *pNewRedl );
//STRIP001                                  pNew->SetStart( *pStt );
//STRIP001                                  pNewRedl->SetStart( *pREnd, pStt );
//STRIP001                                  pRedl->SetEnd( *pNew->Start(), pREnd );
//STRIP001                                  if( !pRedl->HasValidRange() )
//STRIP001                                  {
//STRIP001                                      // neu einsortieren
//STRIP001                                      pRedlineTbl->Remove( n );
//STRIP001                                      pRedlineTbl->Insert( pRedl );
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001                          break;
//STRIP001                      }
//STRIP001
//STRIP001                         // insert the pNew part (if it exists)
//STRIP001                      if( pNew )
//STRIP001                      {
//STRIP001                             // AppendRedline( pNew, bCallDelete );
//STRIP001                             sal_Bool bRet = pRedlineTbl->Insert( pNew );
//STRIP001
//STRIP001                             // pNew must be deleted if Insert() wasn't
//STRIP001                             // successful. But that can't happen, since pNew is
//STRIP001                             // part of the original pRedl redline.
//STRIP001                          ASSERT( bRet, "Can't insert existing redline?" );
//STRIP001
//STRIP001                             // restart (now with pRedl being split up)
//STRIP001                          n = (USHORT)-1;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case REDLINE_FORMAT:
//STRIP001                  switch( eCmpPos )
//STRIP001                  {
//STRIP001                  case POS_OVERLAP_BEFORE:
//STRIP001                      pRedl->SetStart( *pEnd, pRStt );
//STRIP001                      // neu einsortieren
//STRIP001                      pRedlineTbl->Remove( n );
//STRIP001                      pRedlineTbl->Insert( pRedl, n );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OVERLAP_BEHIND:
//STRIP001                      pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_EQUAL:
//STRIP001                  case POS_OUTSIDE:
//STRIP001                      // ueberlappt den akt. komplett oder hat gleiche
//STRIP001                      // Ausdehung, dann muss der alte geloescht werden
//STRIP001                      pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_INSIDE:
//STRIP001                      // ueberlappt den akt. komplett, dann muss
//STRIP001                      // der neue gesplittet oder verkuertzt werden
//STRIP001                      if( *pEnd != *pREnd )
//STRIP001                      {
//STRIP001                          SwRedline* pNew = new SwRedline( *pRedl );
//STRIP001                          pNew->SetStart( *pEnd );
//STRIP001                          pRedl->SetEnd( *pStt, pREnd );
//STRIP001                          AppendRedline( pNew, bCallDelete );
//STRIP001                          n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                      }
//STRIP001                      else
//STRIP001                          pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case REDLINE_FORMAT:
//STRIP001              switch( pRedl->GetType() )
//STRIP001              {
//STRIP001              case REDLINE_INSERT:
//STRIP001              case REDLINE_DELETE:
//STRIP001                  switch( eCmpPos )
//STRIP001                  {
//STRIP001                  case POS_OVERLAP_BEFORE:
//STRIP001                      pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OVERLAP_BEHIND:
//STRIP001                      pNewRedl->SetStart( *pREnd, pStt );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_EQUAL:
//STRIP001                  case POS_INSIDE:
//STRIP001                      delete pNewRedl, pNewRedl = 0;
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OUTSIDE:
//STRIP001                      // ueberlappt den akt. komplett, dann muss
//STRIP001                      // der neue gesplittet oder verkuertzt werden
//STRIP001                      if( *pEnd != *pREnd )
//STRIP001                      {
//STRIP001                          SwRedline* pNew = new SwRedline( *pNewRedl );
//STRIP001                          pNew->SetStart( *pREnd );
//STRIP001                          pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                          AppendRedline( pNew, bCallDelete );
//STRIP001                          n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                      }
//STRIP001                      else
//STRIP001                          pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case REDLINE_FORMAT:
//STRIP001                  switch( eCmpPos )
//STRIP001                  {
//STRIP001                  case POS_OUTSIDE:
//STRIP001                  case POS_EQUAL:
//STRIP001                      {
//STRIP001                          // ueberlappt den akt. komplett oder hat gleiche
//STRIP001                          // Ausdehung, dann muss der alte geloescht werden
//STRIP001                          pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      }
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_INSIDE:
//STRIP001                      if( pRedl->IsOwnRedline( *pNewRedl ) &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ))
//STRIP001                          // ein eigenes kann komplett ignoriert werden
//STRIP001                          delete pNewRedl, pNewRedl = 0;
//STRIP001
//STRIP001                      else if( *pREnd == *pEnd )
//STRIP001                          // ansonsten nur den akt. verkuerzen
//STRIP001                          pRedl->SetEnd( *pStt, pREnd );
//STRIP001                      else if( *pRStt == *pStt )
//STRIP001                      {
//STRIP001                          // ansonsten nur den akt. verkuerzen
//STRIP001                          pRedl->SetStart( *pEnd, pRStt );
//STRIP001                          // neu einsortieren
//STRIP001                          pRedlineTbl->Remove( n );
//STRIP001                          pRedlineTbl->Insert( pRedl, n );
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // liegt komplett im akt.
//STRIP001                          // dann muss der gesplittet werden
//STRIP001                          SwRedline* pNew = new SwRedline( *pRedl );
//STRIP001                          pNew->SetStart( *pEnd );
//STRIP001                          pRedl->SetEnd( *pStt, pREnd );
//STRIP001                          AppendRedline( pNew, bCallDelete );
//STRIP001                          n = (USHORT)-1;     // neu Aufsetzen
//STRIP001                      }
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_OVERLAP_BEFORE:
//STRIP001                  case POS_OVERLAP_BEHIND:
//STRIP001                      if( pRedl->IsOwnRedline( *pNewRedl ) &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ))
//STRIP001                      {
//STRIP001                          // dann kann das zusammengefasst werden, sprich
//STRIP001                          // der neue deckt das schon ab.
//STRIP001                          if( POS_OVERLAP_BEHIND == eCmpPos )
//STRIP001                              pNewRedl->SetStart( *pRStt, pStt );
//STRIP001                          else
//STRIP001                              pNewRedl->SetEnd( *pREnd, pEnd );
//STRIP001                          pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      }
//STRIP001                      else if( POS_OVERLAP_BEHIND == eCmpPos )
//STRIP001                          pNewRedl->SetStart( *pREnd, pStt );
//STRIP001                      else
//STRIP001                          pNewRedl->SetEnd( *pRStt, pEnd );
//STRIP001                      break;
//STRIP001
//STRIP001                  case POS_COLLIDE_END:
//STRIP001                      if( pRedl->IsOwnRedline( *pNewRedl ) &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ) && n &&
//STRIP001                          *(*pRedlineTbl)[ n-1 ]->End() < *pStt )
//STRIP001                      {
//STRIP001                          // dann kann das zusammengefasst werden, sprich
//STRIP001                          // der neue deckt das schon ab.
//STRIP001                          pNewRedl->SetEnd( *pREnd, pEnd );
//STRIP001                          pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  case POS_COLLIDE_START:
//STRIP001                      if( pRedl->IsOwnRedline( *pNewRedl ) &&
//STRIP001                          pRedl->CanCombine( *pNewRedl ) &&
//STRIP001                          n+1 < pRedlineTbl->Count() &&
//STRIP001                          *(*pRedlineTbl)[ n+1 ]->Start() < *pEnd )
//STRIP001                      {
//STRIP001                          // dann kann das zusammengefasst werden, sprich
//STRIP001                          // der neue deckt das schon ab.
//STRIP001                          pNewRedl->SetStart( *pRStt, pStt );
//STRIP001                          pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001
//STRIP001          case REDLINE_FMTCOLL:
//STRIP001              // wie soll das verhalten sein????
//STRIP001              // erstmal so einfuegen
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( pNewRedl )
//STRIP001          pRedlineTbl->Insert( pNewRedl );
//STRIP001
//STRIP001      if( bCompress )
//STRIP001          ::com::pressRedlines();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( bCallDelete && REDLINE_DELETE == pNewRedl->GetType() )
//STRIP001      {
//STRIP001          SwRedlineMode eOld = eRedlineMode;
//STRIP001 // auf NONE setzen, damit das Delete::Redo die RedlineDaten wieder richtig
//STRIP001 // zusammen fasst! Der ShowMode muss erhalten bleiben!
//STRIP001          eRedlineMode = (SwRedlineMode)(eOld & ~(REDLINE_ON | REDLINE_IGNORE));
//STRIP001          DeleteAndJoin( *pNewRedl );
//STRIP001          eRedlineMode = eOld;
//STRIP001      }
//STRIP001      delete pNewRedl, pNewRedl = 0;
//STRIP001  }
//STRIP001  _CHECK_REDLINE( this )
//STRIP001
//STRIP001  return 0 != pNewRedl;
/*N*/ }


//STRIP001 void SwDoc::CompressRedlines()
//STRIP001 {
//STRIP001  _CHECK_REDLINE( this )
//STRIP001
//STRIP001  void (SwRedline::*pFnc)(USHORT) = 0;
//STRIP001  switch( REDLINE_SHOW_MASK & eRedlineMode )
//STRIP001  {
//STRIP001  case REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE:
//STRIP001      pFnc = &SwRedline::Show;
//STRIP001      break;
//STRIP001  case REDLINE_SHOW_INSERT:
//STRIP001      pFnc = &SwRedline::Hide;
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  // versuche gleiche zusammenzufassen
//STRIP001  for( USHORT n = 1; n < pRedlineTbl->Count(); ++n )
//STRIP001  {
//STRIP001      SwRedline* pPrev = (*pRedlineTbl)[ n-1 ],
//STRIP001                  * pCur = (*pRedlineTbl)[ n ];
//STRIP001      const SwPosition* pPrevStt = pPrev->Start(),
//STRIP001                      * pPrevEnd = pPrevStt == pPrev->GetPoint()
//STRIP001                          ? pPrev->GetMark() : pPrev->GetPoint();
//STRIP001      const SwPosition* pCurStt = pCur->Start(),
//STRIP001                      * pCurEnd = pCurStt == pCur->GetPoint()
//STRIP001                          ? pCur->GetMark() : pCur->GetPoint();
//STRIP001      if( *pPrevEnd == *pCurStt && pPrev->CanCombine( *pCur ) &&
//STRIP001          pPrevStt->nNode.GetNode().FindStartNode() ==
//STRIP001          pCurEnd->nNode.GetNode().FindStartNode() &&
//STRIP001          !pCurEnd->nNode.GetNode().FindStartNode()->IsTableNode() )
//STRIP001      {
//STRIP001          // dann koennen die zusammen gefasst werden
//STRIP001          pPrev->Show();
//STRIP001          pCur->Show();
//STRIP001
//STRIP001          pPrev->SetEnd( *pCur->End() );
//STRIP001          pRedlineTbl->DeleteAndDestroy( n );
//STRIP001          --n;
//STRIP001          if( pFnc )
//STRIP001              (pPrev->*pFnc)(0);
//STRIP001      }
//STRIP001  }
//STRIP001  _CHECK_REDLINE( this )
//STRIP001 }

//STRIP001 BOOL SwDoc::SplitRedline( const SwPaM& rRange )
//STRIP001 {
//STRIP001  BOOL bChg = FALSE;
//STRIP001  USHORT n = 0;
//STRIP001  const SwPosition* pStt = rRange.Start(),
//STRIP001                * pEnd = pStt == rRange.GetPoint() ? rRange.GetMark()
//STRIP001                                                   : rRange.GetPoint();
//STRIP001  GetRedline( *pStt, &n );
//STRIP001  for( ; n < pRedlineTbl->Count() ; ++n )
//STRIP001  {
//STRIP001      SwRedline* pTmp = (*pRedlineTbl)[ n ];
//STRIP001      SwPosition* pTStt = pTmp->Start(),
//STRIP001                * pTEnd = pTStt == pTmp->GetPoint() ? pTmp->GetMark()
//STRIP001                                                    : pTmp->GetPoint();
//STRIP001      if( *pTStt <= *pStt && *pStt <= *pTEnd &&
//STRIP001          *pTStt <= *pEnd && *pEnd <= *pTEnd )
//STRIP001      {
//STRIP001          bChg = TRUE;
//STRIP001          int nn = 0;
//STRIP001          if( *pStt == *pTStt )
//STRIP001              nn += 1;
//STRIP001          if( *pEnd == *pTEnd )
//STRIP001              nn += 2;
//STRIP001
//STRIP001          SwRedline* pNew = 0;
//STRIP001          switch( nn )
//STRIP001          {
//STRIP001          case 0:
//STRIP001              pNew = new SwRedline( *pTmp );
//STRIP001              pTmp->SetEnd( *pStt, pTEnd );
//STRIP001              pNew->SetStart( *pEnd );
//STRIP001              break;
//STRIP001
//STRIP001          case 1:
//STRIP001              *pTStt = *pEnd;
//STRIP001              break;
//STRIP001
//STRIP001          case 2:
//STRIP001              *pTEnd = *pStt;
//STRIP001              break;
//STRIP001
//STRIP001          case 3:
//STRIP001              pTmp->InvalidateRange();
//STRIP001              pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001              pTmp = 0;
//STRIP001              break;
//STRIP001          }
//STRIP001          if( pTmp && !pTmp->HasValidRange() )
//STRIP001          {
//STRIP001              // neu einsortieren
//STRIP001              pRedlineTbl->Remove( n );
//STRIP001              pRedlineTbl->Insert( pTmp, n );
//STRIP001          }
//STRIP001          if( pNew )
//STRIP001              pRedlineTbl->Insert( pNew, n );
//STRIP001      }
//STRIP001      else if( *pEnd < *pTStt )
//STRIP001          break;
//STRIP001  }
//STRIP001  return bChg;
//STRIP001 }

/*N*/ BOOL SwDoc::DeleteRedline( const SwPaM& rRange, BOOL bSaveInUndo,
/*N*/                           USHORT nDelType )
/*N*/ {
/*N*/   if( REDLINE_IGNOREDELETE_REDLINES & eRedlineMode ||
/*N*/       !rRange.HasMark() || *rRange.GetMark() == *rRange.GetPoint() )
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bChg = FALSE;
/*N*/
/*N*/   if( bSaveInUndo && DoesUndo() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SwUndoRedline* pUndo = new SwUndoRedline( UNDO_REDLINE, rRange );
//STRIP001 /*?*/        if( pUndo->GetRedlSaveCount() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ClearRedo();
//STRIP001 /*?*/            AppendUndo( pUndo );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/            delete pUndo;
/*N*/   }
/*N*/
/*N*/   const SwPosition* pStt = rRange.Start(),
/*N*/                   * pEnd = pStt == rRange.GetPoint() ? rRange.GetMark()
/*N*/                                                      : rRange.GetPoint();
/*N*/   USHORT n = 0;
/*N*/   GetRedline( *pStt, &n );
/*N*/   for( ; n < pRedlineTbl->Count() ; ++n )
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  SwRedline* pRedl = (*pRedlineTbl)[ n ];
//STRIP001 /*?*/        if( USHRT_MAX != nDelType && nDelType != pRedl->GetType() )
//STRIP001 /*?*/            continue;
//STRIP001 /*?*/
//STRIP001 /*?*/        SwPosition* pRStt = pRedl->Start(),
//STRIP001 /*?*/                  * pREnd = pRStt == pRedl->GetPoint() ? pRedl->GetMark()
//STRIP001 /*?*/                                                       : pRedl->GetPoint();
//STRIP001 /*?*/        BOOL bDel = FALSE;
//STRIP001 /*?*/        switch( ComparePosition( *pStt, *pEnd, *pRStt, *pREnd ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/        case POS_EQUAL:
//STRIP001 /*?*/        case POS_OUTSIDE:
//STRIP001 /*?*/            bDel = TRUE;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case POS_OVERLAP_BEFORE:
//STRIP001 /*?*/            if( *pEnd == *pREnd )
//STRIP001 /*?*/                bDel = TRUE;
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pRedl->InvalidateRange();
//STRIP001 /*?*/                pRedl->SetStart( *pEnd, pRStt );
//STRIP001 /*?*/                // neu einsortieren
//STRIP001 /*?*/                pRedlineTbl->Remove( n );
//STRIP001 /*?*/                pRedlineTbl->Insert( pRedl );
//STRIP001 /*?*/                --n;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case POS_OVERLAP_BEHIND:
//STRIP001 /*?*/            if( *pStt == *pRStt )
//STRIP001 /*?*/                bDel = TRUE;
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pRedl->InvalidateRange();
//STRIP001 /*?*/                pRedl->SetEnd( *pStt, pREnd );
//STRIP001 /*?*/                if( !pRedl->HasValidRange() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // neu einsortieren
//STRIP001 /*?*/                    pRedlineTbl->Remove( n );
//STRIP001 /*?*/                    pRedlineTbl->Insert( pRedl );
//STRIP001 /*?*/                    --n;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case POS_INSIDE:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // der muss gesplittet werden
//STRIP001 /*?*/                pRedl->InvalidateRange();
//STRIP001 /*?*/                if( *pRStt == *pStt )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pRedl->SetStart( *pEnd, pRStt );
//STRIP001 /*?*/                    // neu einsortieren
//STRIP001 /*?*/                    pRedlineTbl->Remove( n );
//STRIP001 /*?*/                    pRedlineTbl->Insert( pRedl );
//STRIP001 /*?*/                    --n;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwRedline* pCpy;
//STRIP001 /*?*/                    if( *pREnd != *pEnd )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pCpy = new SwRedline( *pRedl );
//STRIP001 /*?*/                        pCpy->SetStart( *pEnd );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        pCpy = 0;
//STRIP001 /*?*/                    pRedl->SetEnd( *pStt, pREnd );
//STRIP001 /*?*/                    if( !pRedl->HasValidRange() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // neu einsortieren
//STRIP001 /*?*/                        pRedlineTbl->Remove( pRedlineTbl->GetPos( pRedl ));
//STRIP001 /*?*/                        pRedlineTbl->Insert( pRedl );
//STRIP001 /*?*/                        --n;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    if( pCpy )
//STRIP001 /*?*/                        pRedlineTbl->Insert( pCpy );
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case POS_COLLIDE_END:
//STRIP001 /*?*/        case POS_BEFORE:
//STRIP001 /*?*/            n = pRedlineTbl->Count();
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( bDel )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pRedl->InvalidateRange();
//STRIP001 /*?*/            pRedlineTbl->DeleteAndDestroy( n-- );
//STRIP001 /*?*/            bChg = TRUE;
//STRIP001 /*?*/        }
/*N*/   }
/*N*/
/*N*/   if( bChg )
/*N*/       SetModified();
/*N*/
/*N*/   return bChg;
/*N*/ }

/*N*/ BOOL SwDoc::DeleteRedline( const SwStartNode& rNode, BOOL bSaveInUndo,
/*N*/                           USHORT nDelType )
/*N*/ {
/*N*/   return DeleteRedline( SwPaM( *rNode.EndOfSectionNode(), rNode ),
/*N*/                           bSaveInUndo, nDelType );
/*N*/ }

//STRIP001 void SwDoc::DeleteRedline( USHORT nPos )
//STRIP001 {
//STRIP001  SwRedline* pTmp = (*pRedlineTbl)[ nPos ];
//STRIP001  pTmp->InvalidateRange();
//STRIP001  pRedlineTbl->DeleteAndDestroy( nPos );
//STRIP001 }

/*N*/ USHORT SwDoc::GetRedlinePos( const SwNode& rNd, USHORT nType ) const
/*N*/ {
/*N*/   const ULONG nNdIdx = rNd.GetIndex();
/*N*/   for( USHORT n = 0; n < pRedlineTbl->Count() ; ++n )
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  const SwRedline* pTmp = (*pRedlineTbl)[ n ];
//STRIP001 /*?*/        ULONG nPt = pTmp->GetPoint()->nNode.GetIndex(),
//STRIP001 /*?*/              nMk = pTmp->GetMark()->nNode.GetIndex();
//STRIP001 /*?*/        if( nPt < nMk ) { long nTmp = nMk; nMk = nPt; nPt = nTmp; }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( ( USHRT_MAX == nType || nType == pTmp->GetType()) &&
//STRIP001 /*?*/            nMk <= nNdIdx && nNdIdx <= nPt )
//STRIP001 /*?*/            return n;
//STRIP001 /*?*/
//STRIP001 /*?*/        if( nMk > nNdIdx )
//STRIP001 /*?*/            break;
/*N*/   }
/*N*/   return USHRT_MAX;
/*N*/ }

/*N*/ const SwRedline* SwDoc::GetRedline( const SwPosition& rPos,
/*N*/                                   USHORT* pFndPos ) const
/*N*/ {
/*N*/   register USHORT nO = pRedlineTbl->Count(), nM, nU = 0;
/*N*/   if( nO > 0 )
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  nO--;
//STRIP001 /*?*/        while( nU <= nO )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nM = nU + ( nO - nU ) / 2;
//STRIP001 /*?*/            const SwRedline* pRedl = (*pRedlineTbl)[ nM ];
//STRIP001 /*?*/            const SwPosition* pStt = pRedl->Start();
//STRIP001 /*?*/            const SwPosition* pEnd = pStt == pRedl->GetPoint()
//STRIP001 /*?*/                                        ? pRedl->GetMark()
//STRIP001 /*?*/                                        : pRedl->GetPoint();
//STRIP001 /*?*/            if( pEnd == pStt
//STRIP001 /*?*/                    ? *pStt == rPos
//STRIP001 /*?*/                    : ( *pStt <= rPos && rPos < *pEnd ) )
//STRIP001 /*?*/            {
//STRIP001                 /* #107318# returned wrong redline */
//STRIP001              while( nM && rPos <= *(*pRedlineTbl)[ nM - 1 ]->End() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    --nM;
//STRIP001 /*?*/                    pRedl = (*pRedlineTbl)[ nM ];
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if( pFndPos )
//STRIP001 /*?*/                    *pFndPos = nM;
//STRIP001 /*?*/                return pRedl;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if( *pEnd <= rPos )
//STRIP001 /*?*/                nU = nM + 1;
//STRIP001 /*?*/            else if( nM == 0 )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if( pFndPos )
//STRIP001 /*?*/                    *pFndPos = nU;
//STRIP001 /*?*/                return 0;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nO = nM - 1;
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   if( pFndPos )
/*N*/       *pFndPos = nU;
/*N*/   return 0;
/*N*/ }

typedef BOOL (*Fn_AcceptReject)( SwRedlineTbl& rArr, USHORT& rPos,
                        BOOL bCallDelete,
                        const SwPosition* pSttRng,
                        const SwPosition* pEndRng);

//STRIP001 BOOL lcl_AcceptRedline( SwRedlineTbl& rArr, USHORT& rPos,
//STRIP001                      BOOL bCallDelete,
//STRIP001                      const SwPosition* pSttRng = 0,
//STRIP001                      const SwPosition* pEndRng = 0 )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  SwRedline* pRedl = rArr[ rPos ];
//STRIP001  SwPosition *pRStt = 0, *pREnd = 0;
//STRIP001  SwComparePosition eCmp = POS_OUTSIDE;
//STRIP001  if( pSttRng && pEndRng )
//STRIP001  {
//STRIP001      pRStt = pRedl->Start();
//STRIP001      pREnd = pRedl->End();
//STRIP001      eCmp = ComparePosition( *pSttRng, *pEndRng, *pRStt, *pREnd );
//STRIP001  }
//STRIP001
//STRIP001  pRedl->InvalidateRange();
//STRIP001
//STRIP001  switch( pRedl->GetType() )
//STRIP001  {
//STRIP001  case REDLINE_INSERT:
//STRIP001  case REDLINE_FORMAT:
//STRIP001      {
//STRIP001          BOOL bCheck = FALSE, bReplace = FALSE;
//STRIP001          switch( eCmp )
//STRIP001          {
//STRIP001          case POS_INSIDE:
//STRIP001              if( *pSttRng == *pRStt )
//STRIP001                  pRedl->SetStart( *pEndRng, pRStt );
//STRIP001              else
//STRIP001              {
//STRIP001                  if( *pEndRng != *pREnd )
//STRIP001                  {
//STRIP001                      // aufsplitten
//STRIP001                      SwRedline* pNew = new SwRedline( *pRedl );
//STRIP001                      pNew->SetStart( *pEndRng );
//STRIP001                      rArr.Insert( pNew ); ++rPos;
//STRIP001                  }
//STRIP001                  pRedl->SetEnd( *pSttRng, pREnd );
//STRIP001                  bCheck = TRUE;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OVERLAP_BEFORE:
//STRIP001              pRedl->SetStart( *pEndRng, pRStt );
//STRIP001              bReplace = TRUE;
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OVERLAP_BEHIND:
//STRIP001              pRedl->SetEnd( *pSttRng, pREnd );
//STRIP001              bCheck = TRUE;
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OUTSIDE:
//STRIP001          case POS_EQUAL:
//STRIP001              rArr.DeleteAndDestroy( rPos-- );
//STRIP001              break;
//STRIP001
//STRIP001          default:
//STRIP001              bRet = FALSE;
//STRIP001          }
//STRIP001
//STRIP001          if( bReplace || ( bCheck && !pRedl->HasValidRange() ))
//STRIP001          {
//STRIP001              // neu einsortieren
//STRIP001              rArr.Remove( rArr.GetPos( pRedl ));
//STRIP001              rArr.Insert( pRedl );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  case REDLINE_DELETE:
//STRIP001      {
//STRIP001          SwDoc& rDoc = *pRedl->GetDoc();
//STRIP001          const SwPosition *pDelStt = 0, *pDelEnd = 0;
//STRIP001          BOOL bDelRedl = FALSE;
//STRIP001          switch( eCmp )
//STRIP001          {
//STRIP001          case POS_INSIDE:
//STRIP001              if( bCallDelete )
//STRIP001              {
//STRIP001                  pDelStt = pSttRng;
//STRIP001                  pDelEnd = pEndRng;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OVERLAP_BEFORE:
//STRIP001              if( bCallDelete )
//STRIP001              {
//STRIP001                  pDelStt = pRStt;
//STRIP001                  pDelEnd = pEndRng;
//STRIP001              }
//STRIP001              break;
//STRIP001          case POS_OVERLAP_BEHIND:
//STRIP001              if( bCallDelete )
//STRIP001              {
//STRIP001                  pDelStt = pREnd;
//STRIP001                  pDelEnd = pSttRng;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OUTSIDE:
//STRIP001          case POS_EQUAL:
//STRIP001              {
//STRIP001                  rArr.Remove( rPos-- );
//STRIP001                  bDelRedl = TRUE;
//STRIP001                  if( bCallDelete )
//STRIP001                  {
//STRIP001                      pDelStt = pRedl->Start();
//STRIP001                      pDelEnd = pRedl->End();
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          default:
//STRIP001              bRet = FALSE;
//STRIP001          }
//STRIP001
//STRIP001          if( pDelStt && pDelEnd )
//STRIP001          {
//STRIP001              SwPaM aPam( *pDelStt, *pDelEnd );
//STRIP001              SwCntntNode* pCSttNd = pDelStt->nNode.GetNode().GetCntntNode();
//STRIP001              SwCntntNode* pCEndNd = pDelEnd->nNode.GetNode().GetCntntNode();
//STRIP001
//STRIP001              if( bDelRedl )
//STRIP001                  delete pRedl;
//STRIP001
//STRIP001              SwRedlineMode eOld = rDoc.GetRedlineMode();
//STRIP001              rDoc.SetRedlineMode_intern( eOld & ~(REDLINE_ON | REDLINE_IGNORE) );
//STRIP001
//STRIP001              if( pCSttNd && pCEndNd )
//STRIP001                  rDoc.DeleteAndJoin( aPam );
//STRIP001              else
//STRIP001              {
//STRIP001                  rDoc.Delete( aPam );
//STRIP001
//STRIP001                  if( pCSttNd && !pCEndNd )
//STRIP001                  {
//STRIP001                      aPam.GetBound( TRUE ).nContent.Assign( 0, 0 );
//STRIP001                      aPam.GetBound( FALSE ).nContent.Assign( 0, 0 );
//STRIP001                      aPam.DeleteMark();
//STRIP001                      rDoc.DelFullPara( aPam );
//STRIP001                  }
//STRIP001              }
//STRIP001              rDoc.SetRedlineMode_intern( eOld );
//STRIP001          }
//STRIP001          else if( bDelRedl )
//STRIP001              delete pRedl;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case REDLINE_FMTCOLL:
//STRIP001      rArr.DeleteAndDestroy( rPos-- );
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_RejectRedline( SwRedlineTbl& rArr, USHORT& rPos,
//STRIP001                      BOOL bCallDelete,
//STRIP001                      const SwPosition* pSttRng = 0,
//STRIP001                      const SwPosition* pEndRng = 0 )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  SwRedline* pRedl = rArr[ rPos ];
//STRIP001  SwPosition *pRStt = 0, *pREnd = 0;
//STRIP001  SwComparePosition eCmp = POS_OUTSIDE;
//STRIP001  if( pSttRng && pEndRng )
//STRIP001  {
//STRIP001      pRStt = pRedl->Start();
//STRIP001      pREnd = pRedl->End();
//STRIP001      eCmp = ComparePosition( *pSttRng, *pEndRng, *pRStt, *pREnd );
//STRIP001  }
//STRIP001
//STRIP001  pRedl->InvalidateRange();
//STRIP001
//STRIP001  switch( pRedl->GetType() )
//STRIP001  {
//STRIP001  case REDLINE_INSERT:
//STRIP001      {
//STRIP001          SwDoc& rDoc = *pRedl->GetDoc();
//STRIP001          const SwPosition *pDelStt = 0, *pDelEnd = 0;
//STRIP001          BOOL bDelRedl = FALSE;
//STRIP001          switch( eCmp )
//STRIP001          {
//STRIP001          case POS_INSIDE:
//STRIP001              if( bCallDelete )
//STRIP001              {
//STRIP001                  pDelStt = pSttRng;
//STRIP001                  pDelEnd = pEndRng;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OVERLAP_BEFORE:
//STRIP001              if( bCallDelete )
//STRIP001              {
//STRIP001                  pDelStt = pRStt;
//STRIP001                  pDelEnd = pEndRng;
//STRIP001              }
//STRIP001              break;
//STRIP001          case POS_OVERLAP_BEHIND:
//STRIP001              if( bCallDelete )
//STRIP001              {
//STRIP001                  pDelStt = pREnd;
//STRIP001                  pDelEnd = pSttRng;
//STRIP001              }
//STRIP001              break;
//STRIP001          case POS_OUTSIDE:
//STRIP001          case POS_EQUAL:
//STRIP001              {
//STRIP001                  // dann den Bereich wieder loeschen
//STRIP001                  rArr.Remove( rPos-- );
//STRIP001                  bDelRedl = TRUE;
//STRIP001                  if( bCallDelete )
//STRIP001                  {
//STRIP001                      pDelStt = pRedl->Start();
//STRIP001                      pDelEnd = pRedl->End();
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          default:
//STRIP001              bRet = FALSE;
//STRIP001          }
//STRIP001          if( pDelStt && pDelEnd )
//STRIP001          {
//STRIP001              SwPaM aPam( *pDelStt, *pDelEnd );
//STRIP001
//STRIP001              SwCntntNode* pCSttNd = pDelStt->nNode.GetNode().GetCntntNode();
//STRIP001              SwCntntNode* pCEndNd = pDelEnd->nNode.GetNode().GetCntntNode();
//STRIP001
//STRIP001              if( bDelRedl )
//STRIP001                  delete pRedl;
//STRIP001
//STRIP001              SwRedlineMode eOld = rDoc.GetRedlineMode();
//STRIP001              rDoc.SetRedlineMode_intern( eOld & ~(REDLINE_ON | REDLINE_IGNORE) );
//STRIP001
//STRIP001              if( pCSttNd && pCEndNd )
//STRIP001                  rDoc.DeleteAndJoin( aPam );
//STRIP001              else
//STRIP001              {
//STRIP001                  rDoc.Delete( aPam );
//STRIP001
//STRIP001                  if( pCSttNd && !pCEndNd )
//STRIP001                  {
//STRIP001                      aPam.GetBound( TRUE ).nContent.Assign( 0, 0 );
//STRIP001                      aPam.GetBound( FALSE ).nContent.Assign( 0, 0 );
//STRIP001                      aPam.DeleteMark();
//STRIP001                      rDoc.DelFullPara( aPam );
//STRIP001                  }
//STRIP001              }
//STRIP001              rDoc.SetRedlineMode_intern( eOld );
//STRIP001          }
//STRIP001          else if( bDelRedl )
//STRIP001              delete pRedl;
//STRIP001      }
//STRIP001      break;
//STRIP001  case REDLINE_DELETE:
//STRIP001      {
//STRIP001          SwRedline* pNew = 0;
//STRIP001          BOOL bCheck = FALSE, bReplace = FALSE;
//STRIP001
//STRIP001          switch( eCmp )
//STRIP001          {
//STRIP001          case POS_INSIDE:
//STRIP001              {
//STRIP001                  if( 1 < pRedl->GetStackCount() )
//STRIP001                  {
//STRIP001                      pNew = new SwRedline( *pRedl );
//STRIP001                      pNew->PopData();
//STRIP001                  }
//STRIP001                  if( *pSttRng == *pRStt )
//STRIP001                  {
//STRIP001                      pRedl->SetStart( *pEndRng, pRStt );
//STRIP001                      bReplace = TRUE;
//STRIP001                      if( pNew )
//STRIP001                          pNew->SetEnd( *pEndRng );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if( *pEndRng != *pREnd )
//STRIP001                      {
//STRIP001                          // aufsplitten
//STRIP001                          SwRedline* pCpy = new SwRedline( *pRedl );
//STRIP001                          pCpy->SetStart( *pEndRng );
//STRIP001                          rArr.Insert( pCpy ); ++rPos;
//STRIP001                          if( pNew )
//STRIP001                              pNew->SetEnd( *pEndRng );
//STRIP001                      }
//STRIP001
//STRIP001                      pRedl->SetEnd( *pSttRng, pREnd );
//STRIP001                      bCheck = TRUE;
//STRIP001                      if( pNew )
//STRIP001                          pNew->SetStart( *pSttRng );
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OVERLAP_BEFORE:
//STRIP001              if( 1 < pRedl->GetStackCount() )
//STRIP001              {
//STRIP001                  pNew = new SwRedline( *pRedl );
//STRIP001                  pNew->PopData();
//STRIP001              }
//STRIP001              pRedl->SetStart( *pEndRng, pRStt );
//STRIP001              bReplace = TRUE;
//STRIP001              if( pNew )
//STRIP001                  pNew->SetEnd( *pEndRng );
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OVERLAP_BEHIND:
//STRIP001              if( 1 < pRedl->GetStackCount() )
//STRIP001              {
//STRIP001                  pNew = new SwRedline( *pRedl );
//STRIP001                  pNew->PopData();
//STRIP001              }
//STRIP001              pRedl->SetEnd( *pSttRng, pREnd );
//STRIP001              bCheck = TRUE;
//STRIP001              if( pNew )
//STRIP001                  pNew->SetStart( *pSttRng );
//STRIP001              break;
//STRIP001
//STRIP001          case POS_OUTSIDE:
//STRIP001          case POS_EQUAL:
//STRIP001              if( !pRedl->PopData() )
//STRIP001                  // das RedlineObject loeschen reicht
//STRIP001                  rArr.DeleteAndDestroy( rPos-- );
//STRIP001              break;
//STRIP001
//STRIP001          default:
//STRIP001              bRet = FALSE;
//STRIP001          }
//STRIP001
//STRIP001          if( pNew )
//STRIP001          {
//STRIP001              rArr.Insert( pNew ); ++rPos;
//STRIP001          }
//STRIP001
//STRIP001          if( bReplace || ( bCheck && !pRedl->HasValidRange() ))
//STRIP001          {
//STRIP001              // neu einsortieren
//STRIP001              rArr.Remove( rArr.GetPos( pRedl ));
//STRIP001              rArr.Insert( pRedl );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case REDLINE_FORMAT:
//STRIP001  case REDLINE_FMTCOLL:
//STRIP001      {
//STRIP001          if( pRedl->GetExtraData() )
//STRIP001              pRedl->GetExtraData()->Reject( *pRedl );
//STRIP001          rArr.DeleteAndDestroy( rPos-- );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 const SwRedline* lcl_FindCurrRedline( const SwPosition& rSttPos,
//STRIP001                                      USHORT& rPos,
//STRIP001                                      BOOL bNext = TRUE )
//STRIP001 {
//STRIP001  const SwRedline* pFnd = 0;
//STRIP001  const SwRedlineTbl& rArr = rSttPos.nNode.GetNode().GetDoc()->GetRedlineTbl();
//STRIP001  for( ; rPos < rArr.Count() ; ++rPos )
//STRIP001  {
//STRIP001      const SwRedline* pTmp = rArr[ rPos ];
//STRIP001      if( pTmp->HasMark() && pTmp->IsVisible() )
//STRIP001      {
//STRIP001          const SwPosition* pRStt = pTmp->Start(),
//STRIP001                    * pREnd = pRStt == pTmp->GetPoint() ? pTmp->GetMark()
//STRIP001                                                        : pTmp->GetPoint();
//STRIP001          if( bNext ? *pRStt <= rSttPos : *pRStt < rSttPos )
//STRIP001          {
//STRIP001              if( bNext ? *pREnd > rSttPos : *pREnd >= rSttPos )
//STRIP001              {
//STRIP001                  pFnd = pTmp;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  return pFnd;
//STRIP001 }


//STRIP001 BOOL lcl_AcceptRejectRedl( Fn_AcceptReject fn_AcceptReject,
//STRIP001                          SwRedlineTbl& rArr, BOOL bCallDelete,
//STRIP001                          const SwPaM& rPam )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  USHORT n = 0;
//STRIP001  const SwPosition* pStt = rPam.Start(),
//STRIP001                  * pEnd = pStt == rPam.GetPoint() ? rPam.GetMark()
//STRIP001                                                   : rPam.GetPoint();
//STRIP001  const SwRedline* pFnd = lcl_FindCurrRedline( *pStt, n, TRUE );
//STRIP001  if( pFnd &&     // neu ein Teil davon?
//STRIP001      ( *pFnd->Start() != *pStt || *pFnd->End() > *pEnd ))
//STRIP001  {
//STRIP001      // dann nur die TeilSelektion aufheben
//STRIP001      if( (*fn_AcceptReject)( rArr, n, bCallDelete, pStt, pEnd ))
//STRIP001          bRet = TRUE;
//STRIP001      ++n;
//STRIP001  }
//STRIP001
//STRIP001  for( ; n < rArr.Count(); ++n )
//STRIP001  {
//STRIP001      SwRedline* pTmp = rArr[ n ];
//STRIP001      if( pTmp->HasMark() && pTmp->IsVisible() )
//STRIP001      {
//STRIP001          if( *pTmp->End() <= *pEnd )
//STRIP001          {
//STRIP001              if( (*fn_AcceptReject)( rArr, n, bCallDelete, 0, 0 ))
//STRIP001                  bRet = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( *pTmp->Start() < *pEnd )
//STRIP001              {
//STRIP001                  // dann nur in der TeilSelektion aufheben
//STRIP001                  if( (*fn_AcceptReject)( rArr, n, bCallDelete, pStt, pEnd ))
//STRIP001                      bRet = TRUE;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void lcl_AdjustRedlineRange( SwPaM& rPam )
//STRIP001 {
//STRIP001  // die Selektion steht nur im ContentBereich. Wenn es aber Redlines
//STRIP001  // davor oder dahinter auf nicht ContentNodes stehen, dann erweiter die
//STRIP001  // die Selection auf diese
//STRIP001  SwPosition* pStt = rPam.Start(),
//STRIP001            * pEnd = pStt == rPam.GetPoint() ? rPam.GetMark()
//STRIP001                                             : rPam.GetPoint();
//STRIP001  SwDoc* pDoc = rPam.GetDoc();
//STRIP001  if( !pStt->nContent.GetIndex() &&
//STRIP001      !pDoc->GetNodes()[ pStt->nNode.GetIndex() - 1 ]->IsCntntNode() )
//STRIP001  {
//STRIP001      const SwRedline* pRedl = pDoc->GetRedline( *pStt );
//STRIP001      if( pRedl )
//STRIP001      {
//STRIP001          const SwPosition* pRStt = pRedl->Start();
//STRIP001          if( !pRStt->nContent.GetIndex() && pRStt->nNode.GetIndex() ==
//STRIP001              pStt->nNode.GetIndex() - 1 )
//STRIP001              *pStt = *pRStt;
//STRIP001      }
//STRIP001  }
//STRIP001  if( pEnd->nNode.GetNode().IsCntntNode() &&
//STRIP001      !pDoc->GetNodes()[ pEnd->nNode.GetIndex() + 1 ]->IsCntntNode() &&
//STRIP001      pEnd->nContent.GetIndex() == pEnd->nNode.GetNode().GetCntntNode()->Len()    )
//STRIP001  {
//STRIP001      const SwRedline* pRedl = pDoc->GetRedline( *pEnd );
//STRIP001      if( pRedl )
//STRIP001      {
//STRIP001          const SwPosition* pREnd = pRedl->End();
//STRIP001          if( !pREnd->nContent.GetIndex() && pREnd->nNode.GetIndex() ==
//STRIP001              pEnd->nNode.GetIndex() + 1 )
//STRIP001              *pEnd = *pREnd;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL SwDoc::AcceptRedline( USHORT nPos, BOOL bCallDelete )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  // aufjedenfall auf sichtbar umschalten
//STRIP001  if( (REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE) !=
//STRIP001      (REDLINE_SHOW_MASK & eRedlineMode) )
//STRIP001      SetRedlineMode( REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE | eRedlineMode );
//STRIP001
//STRIP001  SwRedline* pTmp = (*pRedlineTbl)[ nPos ];
//STRIP001  if( pTmp->HasMark() && pTmp->IsVisible() )
//STRIP001  {
//STRIP001      if( DoesUndo() )
//STRIP001          StartUndo( UNDO_ACCEPT_REDLINE );
//STRIP001
//STRIP001      int nLoopCnt = 2;
//STRIP001      USHORT nSeqNo = pTmp->GetSeqNo();
//STRIP001
//STRIP001      do {
//STRIP001
//STRIP001          if( DoesUndo() )
//STRIP001              AppendUndo( new SwUndoAcceptRedline( *pTmp ));
//STRIP001
//STRIP001          bRet |= lcl_AcceptRedline( *pRedlineTbl, nPos, bCallDelete );
//STRIP001
//STRIP001          if( nSeqNo )
//STRIP001          {
//STRIP001              if( USHRT_MAX == nPos )
//STRIP001                  nPos = 0;
//STRIP001              USHORT nFndPos = 2 == nLoopCnt
//STRIP001                                  ? pRedlineTbl->FindNextSeqNo( nSeqNo, nPos )
//STRIP001                                  : pRedlineTbl->FindPrevSeqNo( nSeqNo, nPos );
//STRIP001              if( USHRT_MAX != nFndPos || ( 0 != ( --nLoopCnt ) &&
//STRIP001                  USHRT_MAX != ( nFndPos =
//STRIP001                      pRedlineTbl->FindPrevSeqNo( nSeqNo, nPos ))) )
//STRIP001                  pTmp = (*pRedlineTbl)[ nPos = nFndPos ];
//STRIP001              else
//STRIP001                  nLoopCnt = 0;
//STRIP001          }
//STRIP001          else
//STRIP001              nLoopCnt = 0;
//STRIP001
//STRIP001      } while( nLoopCnt );
//STRIP001
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          ::com::pressRedlines();
//STRIP001          SetModified();
//STRIP001      }
//STRIP001
//STRIP001      if( DoesUndo() )
//STRIP001          EndUndo( UNDO_ACCEPT_REDLINE );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::AcceptRedline( const SwPaM& rPam, BOOL bCallDelete )
//STRIP001 {
//STRIP001  // aufjedenfall auf sichtbar umschalten
//STRIP001  if( (REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE) !=
//STRIP001      (REDLINE_SHOW_MASK & eRedlineMode) )
//STRIP001      SetRedlineMode( REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE | eRedlineMode );
//STRIP001
//STRIP001  // die Selektion steht nur im ContentBereich. Wenn es aber Redlines
//STRIP001  // davor oder dahinter auf nicht ContentNodes stehen, dann erweiter die
//STRIP001  // die Selection auf diese
//STRIP001  SwPaM aPam( *rPam.GetMark(), *rPam.GetPoint() );
//STRIP001  lcl_AdjustRedlineRange( aPam );
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      StartUndo( UNDO_ACCEPT_REDLINE );
//STRIP001      AppendUndo( new SwUndoAcceptRedline( aPam ));
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet = lcl_AcceptRejectRedl( lcl_AcceptRedline, *pRedlineTbl,
//STRIP001                                      bCallDelete, aPam );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      ::com::pressRedlines();
//STRIP001      SetModified();
//STRIP001  }
//STRIP001  if( DoesUndo() )
//STRIP001      EndUndo( UNDO_ACCEPT_REDLINE );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::RejectRedline( USHORT nPos, BOOL bCallDelete )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  // aufjedenfall auf sichtbar umschalten
//STRIP001  if( (REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE) !=
//STRIP001      (REDLINE_SHOW_MASK & eRedlineMode) )
//STRIP001      SetRedlineMode( REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE | eRedlineMode );
//STRIP001
//STRIP001  SwRedline* pTmp = (*pRedlineTbl)[ nPos ];
//STRIP001  if( pTmp->HasMark() && pTmp->IsVisible() )
//STRIP001  {
//STRIP001      if( DoesUndo() )
//STRIP001          StartUndo( UNDO_REJECT_REDLINE );
//STRIP001
//STRIP001      int nLoopCnt = 2;
//STRIP001      USHORT nSeqNo = pTmp->GetSeqNo();
//STRIP001
//STRIP001      do {
//STRIP001
//STRIP001          if( DoesUndo() )
//STRIP001              AppendUndo( new SwUndoRejectRedline( *pTmp ));
//STRIP001
//STRIP001          bRet |= lcl_RejectRedline( *pRedlineTbl, nPos, bCallDelete );
//STRIP001
//STRIP001          if( nSeqNo )
//STRIP001          {
//STRIP001              if( USHRT_MAX == nPos )
//STRIP001                  nPos = 0;
//STRIP001              USHORT nFndPos = 2 == nLoopCnt
//STRIP001                                  ? pRedlineTbl->FindNextSeqNo( nSeqNo, nPos )
//STRIP001                                  : pRedlineTbl->FindPrevSeqNo( nSeqNo, nPos );
//STRIP001              if( USHRT_MAX != nFndPos || ( 0 != ( --nLoopCnt ) &&
//STRIP001                  USHRT_MAX != ( nFndPos =
//STRIP001                          pRedlineTbl->FindPrevSeqNo( nSeqNo, nPos ))) )
//STRIP001                  pTmp = (*pRedlineTbl)[ nPos = nFndPos ];
//STRIP001              else
//STRIP001                  nLoopCnt = 0;
//STRIP001          }
//STRIP001          else
//STRIP001              nLoopCnt = 0;
//STRIP001
//STRIP001      } while( nLoopCnt );
//STRIP001
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          ::com::pressRedlines();
//STRIP001          SetModified();
//STRIP001      }
//STRIP001
//STRIP001      if( DoesUndo() )
//STRIP001          EndUndo( UNDO_REJECT_REDLINE );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwDoc::RejectRedline( const SwPaM& rPam, BOOL bCallDelete )
//STRIP001 {
//STRIP001  // aufjedenfall auf sichtbar umschalten
//STRIP001  if( (REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE) !=
//STRIP001      (REDLINE_SHOW_MASK & eRedlineMode) )
//STRIP001      SetRedlineMode( REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE | eRedlineMode );
//STRIP001
//STRIP001  // die Selektion steht nur im ContentBereich. Wenn es aber Redlines
//STRIP001  // davor oder dahinter auf nicht ContentNodes stehen, dann erweiter die
//STRIP001  // die Selection auf diese
//STRIP001  SwPaM aPam( *rPam.GetMark(), *rPam.GetPoint() );
//STRIP001  lcl_AdjustRedlineRange( aPam );
//STRIP001
//STRIP001  if( DoesUndo() )
//STRIP001  {
//STRIP001      StartUndo( UNDO_REJECT_REDLINE );
//STRIP001      AppendUndo( new SwUndoRejectRedline( aPam ));
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet = lcl_AcceptRejectRedl( lcl_RejectRedline, *pRedlineTbl,
//STRIP001                                      bCallDelete, aPam );
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      ::com::pressRedlines();
//STRIP001      SetModified();
//STRIP001  }
//STRIP001  if( DoesUndo() )
//STRIP001      EndUndo( UNDO_REJECT_REDLINE );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 const SwRedline* SwDoc::SelNextRedline( SwPaM& rPam ) const
//STRIP001 {
//STRIP001  rPam.DeleteMark();
//STRIP001  rPam.SetMark();
//STRIP001
//STRIP001  SwPosition& rSttPos = *rPam.GetPoint();
//STRIP001  SwPosition aSavePos( rSttPos );
//STRIP001  BOOL bRestart;
//STRIP001
//STRIP001  // sollte die StartPos auf dem letzen gueligen ContentNode stehen,
//STRIP001  // dann aufjedenfall das naechste Redline nehmen
//STRIP001  USHORT n = 0;
//STRIP001  const SwRedline* pFnd = lcl_FindCurrRedline( rSttPos, n, TRUE );
//STRIP001  if( pFnd )
//STRIP001  {
//STRIP001      const SwPosition* pEnd = pFnd->End();
//STRIP001      if( !pEnd->nNode.GetNode().IsCntntNode() )
//STRIP001      {
//STRIP001          SwNodeIndex aTmp( pEnd->nNode );
//STRIP001          SwCntntNode* pCNd = GetNodes().GoPrevSection( &aTmp );
//STRIP001          if( !pCNd || ( aTmp == rSttPos.nNode &&
//STRIP001              pCNd->Len() == rSttPos.nContent.GetIndex() ))
//STRIP001              pFnd = 0;
//STRIP001      }
//STRIP001      if( pFnd )
//STRIP001          rSttPos = *pFnd->End();
//STRIP001  }
//STRIP001
//STRIP001  do {
//STRIP001      bRestart = FALSE;
//STRIP001
//STRIP001      for( ; !pFnd && n < pRedlineTbl->Count(); ++n )
//STRIP001      {
//STRIP001          pFnd = (*pRedlineTbl)[ n ];
//STRIP001          if( pFnd->HasMark() && pFnd->IsVisible() )
//STRIP001          {
//STRIP001              *rPam.GetMark() = *pFnd->Start();
//STRIP001              rSttPos = *pFnd->End();
//STRIP001              break;
//STRIP001          }
//STRIP001          else
//STRIP001              pFnd = 0;
//STRIP001      }
//STRIP001
//STRIP001      if( pFnd )
//STRIP001      {
//STRIP001          // alle vom gleichen Typ und Author, die hinter einander liegen
//STRIP001          // zu einer Selektion zusammenfassen.
//STRIP001          const SwPosition* pPrevEnd = pFnd->End();
//STRIP001          while( ++n < pRedlineTbl->Count() )
//STRIP001          {
//STRIP001              const SwRedline* pTmp = (*pRedlineTbl)[ n ];
//STRIP001              if( pTmp->HasMark() && pTmp->IsVisible() )
//STRIP001              {
//STRIP001                  const SwPosition *pRStt;
//STRIP001                  if( pFnd->GetType() == pTmp->GetType() &&
//STRIP001                      pFnd->GetAuthor() == pTmp->GetAuthor() &&
//STRIP001                      ( *pPrevEnd == *( pRStt = pTmp->Start() ) ||
//STRIP001                        IsPrevPos( *pPrevEnd, *pRStt )) )
//STRIP001                  {
//STRIP001                      pPrevEnd = pTmp->End();
//STRIP001                      rSttPos = *pPrevEnd;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( pFnd )
//STRIP001      {
//STRIP001          const SwRedline* pSaveFnd = pFnd;
//STRIP001
//STRIP001          SwCntntNode* pCNd;
//STRIP001          SwNodeIndex* pIdx = &rPam.GetMark()->nNode;
//STRIP001          if( !pIdx->GetNode().IsCntntNode() &&
//STRIP001              0 != ( pCNd = GetNodes().GoNextSection( pIdx )) )
//STRIP001          {
//STRIP001              if( *pIdx <= rPam.GetPoint()->nNode )
//STRIP001                  rPam.GetMark()->nContent.Assign( pCNd, 0 );
//STRIP001              else
//STRIP001                  pFnd = 0;
//STRIP001          }
//STRIP001
//STRIP001          if( pFnd )
//STRIP001          {
//STRIP001              pIdx = &rPam.GetPoint()->nNode;
//STRIP001              if( !pIdx->GetNode().IsCntntNode() &&
//STRIP001                  0 != ( pCNd = GetNodes().GoPrevSection( pIdx )) )
//STRIP001              {
//STRIP001                  if( *pIdx >= rPam.GetMark()->nNode )
//STRIP001                      rPam.GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001                  else
//STRIP001                      pFnd = 0;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( !pFnd || *rPam.GetMark() == *rPam.GetPoint() )
//STRIP001          {
//STRIP001              if( n < pRedlineTbl->Count() )
//STRIP001              {
//STRIP001                  bRestart = TRUE;
//STRIP001                  *rPam.GetPoint() = *pSaveFnd->End();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rPam.DeleteMark();
//STRIP001                  *rPam.GetPoint() = aSavePos;
//STRIP001              }
//STRIP001              pFnd = 0;
//STRIP001          }
//STRIP001      }
//STRIP001  } while( bRestart );
//STRIP001
//STRIP001  return pFnd;
//STRIP001 }

//STRIP001 const SwRedline* SwDoc::SelPrevRedline( SwPaM& rPam ) const
//STRIP001 {
//STRIP001  rPam.DeleteMark();
//STRIP001  rPam.SetMark();
//STRIP001
//STRIP001  SwPosition& rSttPos = *rPam.GetPoint();
//STRIP001  SwPosition aSavePos( rSttPos );
//STRIP001  BOOL bRestart;
//STRIP001
//STRIP001  // sollte die StartPos auf dem ersten gueligen ContentNode stehen,
//STRIP001  // dann aufjedenfall das vorherige Redline nehmen
//STRIP001  USHORT n = 0;
//STRIP001  const SwRedline* pFnd = lcl_FindCurrRedline( rSttPos, n, FALSE );
//STRIP001  if( pFnd )
//STRIP001  {
//STRIP001      const SwPosition* pStt = pFnd->Start();
//STRIP001      if( !pStt->nNode.GetNode().IsCntntNode() )
//STRIP001      {
//STRIP001          SwNodeIndex aTmp( pStt->nNode );
//STRIP001          SwCntntNode* pCNd = GetNodes().GoNextSection( &aTmp );
//STRIP001          if( !pCNd || ( aTmp == rSttPos.nNode &&
//STRIP001              !rSttPos.nContent.GetIndex() ))
//STRIP001              pFnd = 0;
//STRIP001      }
//STRIP001      if( pFnd )
//STRIP001          rSttPos = *pFnd->Start();
//STRIP001  }
//STRIP001
//STRIP001  do {
//STRIP001      bRestart = FALSE;
//STRIP001
//STRIP001      while( !pFnd && 0 < n )
//STRIP001      {
//STRIP001          pFnd = (*pRedlineTbl)[ --n ];
//STRIP001          if( pFnd->HasMark() && pFnd->IsVisible() )
//STRIP001          {
//STRIP001              *rPam.GetMark() = *pFnd->End();
//STRIP001              rSttPos = *pFnd->Start();
//STRIP001          }
//STRIP001          else
//STRIP001              pFnd = 0;
//STRIP001      }
//STRIP001
//STRIP001      if( pFnd )
//STRIP001      {
//STRIP001          // alle vom gleichen Typ und Author, die hinter einander liegen
//STRIP001          // zu einer Selektion zusammenfassen.
//STRIP001          const SwPosition* pNextStt = pFnd->Start();
//STRIP001          while( 0 < n )
//STRIP001          {
//STRIP001              const SwRedline* pTmp = (*pRedlineTbl)[ --n ];
//STRIP001              if( pTmp->HasMark() && pTmp->IsVisible() )
//STRIP001              {
//STRIP001                  const SwPosition *pREnd;
//STRIP001                  if( pFnd->GetType() == pTmp->GetType() &&
//STRIP001                      pFnd->GetAuthor() == pTmp->GetAuthor() &&
//STRIP001                      ( *pNextStt == *( pREnd = pTmp->End() ) ||
//STRIP001                        IsPrevPos( *pREnd, *pNextStt )) )
//STRIP001                  {
//STRIP001                      pNextStt = pTmp->Start();
//STRIP001                      rSttPos = *pNextStt;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      ++n;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( pFnd )
//STRIP001      {
//STRIP001          const SwRedline* pSaveFnd = pFnd;
//STRIP001
//STRIP001          SwCntntNode* pCNd;
//STRIP001          SwNodeIndex* pIdx = &rPam.GetMark()->nNode;
//STRIP001          if( !pIdx->GetNode().IsCntntNode() &&
//STRIP001              0 != ( pCNd = GetNodes().GoPrevSection( pIdx )) )
//STRIP001          {
//STRIP001              if( *pIdx >= rPam.GetPoint()->nNode )
//STRIP001                  rPam.GetMark()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001              else
//STRIP001                  pFnd = 0;
//STRIP001          }
//STRIP001
//STRIP001          if( pFnd )
//STRIP001          {
//STRIP001              pIdx = &rPam.GetPoint()->nNode;
//STRIP001              if( !pIdx->GetNode().IsCntntNode() &&
//STRIP001                  0 != ( pCNd = GetNodes().GoNextSection( pIdx )) )
//STRIP001              {
//STRIP001                  if( *pIdx <= rPam.GetMark()->nNode )
//STRIP001                      rPam.GetPoint()->nContent.Assign( pCNd, 0 );
//STRIP001                  else
//STRIP001                      pFnd = 0;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( !pFnd || *rPam.GetMark() == *rPam.GetPoint() )
//STRIP001          {
//STRIP001              if( n )
//STRIP001              {
//STRIP001                  bRestart = TRUE;
//STRIP001                  *rPam.GetPoint() = *pSaveFnd->Start();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rPam.DeleteMark();
//STRIP001                  *rPam.GetPoint() = aSavePos;
//STRIP001              }
//STRIP001              pFnd = 0;
//STRIP001          }
//STRIP001      }
//STRIP001  } while( bRestart );
//STRIP001
//STRIP001  return pFnd;
//STRIP001 }

// Kommentar am Redline setzen
//STRIP001 BOOL SwDoc::SetRedlineComment( const SwPaM& rPaM, const String& rS )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwPosition* pStt = rPaM.Start(),
//STRIP001                  * pEnd = pStt == rPaM.GetPoint() ? rPaM.GetMark()
//STRIP001                                                   : rPaM.GetPoint();
//STRIP001  USHORT n = 0;
//STRIP001  if( lcl_FindCurrRedline( *pStt, n, TRUE ) )
//STRIP001  {
//STRIP001      for( ; n < pRedlineTbl->Count(); ++n )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          SwRedline* pTmp = (*pRedlineTbl)[ n ];
//STRIP001          if( pStt != pEnd && *pTmp->Start() > *pEnd )
//STRIP001              break;
//STRIP001
//STRIP001          pTmp->SetComment( rS );
//STRIP001          if( *pTmp->End() >= *pEnd )
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  if( bRet )
//STRIP001      SetModified();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

// legt gebenenfalls einen neuen Author an
/*N*/ USHORT SwDoc::GetRedlineAuthor()
/*N*/ {
/*N*/ return SW_MOD()->GetRedlineAuthor(); //SW50.SDW
/*N*/ }

    // fuer die Reader usw. - neuen Author in die Tabelle eintragen
/*N*/ USHORT SwDoc::InsertRedlineAuthor( const String& rNew )
/*N*/ {
/*N*/ return SW_MOD()->InsertRedlineAuthor(rNew); //SW50.SDW
/*N*/ }

//STRIP001 void SwDoc::UpdateRedlineAttr()
//STRIP001 {
//STRIP001  const SwRedlineTbl& rTbl = GetRedlineTbl();
//STRIP001  for( USHORT n = 0; n < rTbl.Count(); ++n )
//STRIP001  {
//STRIP001      SwRedline* pRedl = rTbl[ n ];
//STRIP001      if( pRedl->IsVisible() )
//STRIP001          pRedl->InvalidateRange();
//STRIP001  }
//STRIP001 }

    // setze Kommentar-Text fuers Redline, das dann per AppendRedline
    // hereinkommt. Wird vom Autoformat benutzt. 0-Pointer setzt den Modus
    // wieder zurueck. Pointer wird nicht kopiert, muss also gueltig bleiben!
//STRIP001 void SwDoc::SetAutoFmtRedlineComment( const String* pTxt, USHORT nSeqNo )
//STRIP001 {
//STRIP001  bIsAutoFmtRedline = 0 != pTxt;
//STRIP001  if( pTxt )
//STRIP001  {
//STRIP001      if( !pAutoFmtRedlnComment )
//STRIP001          pAutoFmtRedlnComment = new String( *pTxt );
//STRIP001      else
//STRIP001          *pAutoFmtRedlnComment = *pTxt;
//STRIP001  }
//STRIP001  else if( pAutoFmtRedlnComment )
//STRIP001      delete pAutoFmtRedlnComment, pAutoFmtRedlnComment = 0;
//STRIP001
//STRIP001  nAutoFmtRedlnCommentNo = nSeqNo;
//STRIP001 }

/*N*/ void SwDoc::SetRedlinePasswd(
/*N*/           const ::com::sun::star::uno::Sequence <sal_Int8>& rNew )
/*N*/ {
/*N*/   aRedlinePasswd = rNew;
/*N*/   SetModified();
/*N*/ }

/*  */

/*N*/ BOOL SwRedlineTbl::Insert( SwRedlinePtr& p, BOOL bIns ) //SW50.SDW
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   if( p->HasValidRange() )
/*N*/   {
/*N*/       bRet = _SwRedlineTbl::Insert( p );
//STRIP001      p->CallDisplayFunc();
/*N*/   }
/*N*/   else if( bIns )
/*N*/       bRet = InsertWithValidRanges( p );
/*N*/   else
/*N*/   {
/*N*/       ASSERT( !this, "Redline: falscher Bereich" );
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 BOOL SwRedlineTbl::Insert( SwRedlinePtr& p, USHORT& rP, BOOL bIns )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( p->HasValidRange() )
//STRIP001  {
//STRIP001      bRet = _SwRedlineTbl::Insert( p, rP );
//STRIP001      p->CallDisplayFunc();
//STRIP001  }
//STRIP001  else if( bIns )
//STRIP001      bRet = InsertWithValidRanges( p, &rP );
//STRIP001  else
//STRIP001  {
//STRIP001      ASSERT( !this, "Redline: falscher Bereich" );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL SwRedlineTbl::InsertWithValidRanges( SwRedlinePtr& p, USHORT* pInsPos ) //SW50.SDW
/*N*/ {
/*N*/   // erzeuge aus den Selektion gueltige "Teilbereiche".
/*N*/   BOOL bAnyIns = FALSE;
/*N*/   SwPosition* pStt = p->Start(),
/*N*/             * pEnd = pStt == p->GetPoint() ? p->GetMark() : p->GetPoint();
/*N*/   SwPosition aNewStt( *pStt );
/*N*/   SwNodes& rNds = aNewStt.nNode.GetNodes();
/*N*/   SwCntntNode* pC;
/*N*/
/*N*/   if( !aNewStt.nNode.GetNode().IsCntntNode() )
/*N*/   {
/*N*/       pC = rNds.GoNext( &aNewStt.nNode );
/*N*/       if( pC )
/*N*/           aNewStt.nContent.Assign( pC, 0 );
/*N*/       else
/*N*/           aNewStt.nNode = rNds.GetEndOfContent();
/*N*/   }
/*N*/
/*N*/   SwRedline* pNew = 0;
/*N*/   USHORT nInsPos;
/*N*/
/*N*/   if( aNewStt < *pEnd )
/*N*/       do {
/*N*/           if( !pNew )
/*N*/               pNew = new SwRedline( p->GetRedlineData(), aNewStt );
/*N*/           else
/*N*/           {
/*N*/               pNew->DeleteMark();
/*N*/               *pNew->GetPoint() = aNewStt;
/*N*/           }
/*N*/
/*N*/           pNew->SetMark();
/*N*/           GoEndSection( pNew->GetPoint() );
/*N*/           if( *pNew->GetPoint() > *pEnd )
/*N*/           {
/*N*/               BOOL bWeiter = TRUE;
/*N*/               pC = 0;
/*N*/               if( aNewStt.nNode != pEnd->nNode )
/*N*/                   do {
/*N*/                       SwNode& rCurNd = aNewStt.nNode.GetNode();
/*N*/                       if( rCurNd.IsStartNode() )
/*N*/                       {
/*N*/                           if( rCurNd.EndOfSectionIndex() < pEnd->nNode.GetIndex() )
/*N*/                               aNewStt.nNode = *rCurNd.EndOfSectionNode();
/*N*/                           else
/*N*/                               break;
/*N*/                       }
/*N*/                       else if( rCurNd.IsCntntNode() )
/*N*/                           pC = rCurNd.GetCntntNode();
/*N*/                       aNewStt.nNode++;
/*N*/                   } while( aNewStt.nNode.GetIndex() < pEnd->nNode.GetIndex() );
/*N*/
/*N*/               if( aNewStt.nNode == pEnd->nNode )
/*N*/                   aNewStt.nContent = pEnd->nContent;
/*N*/               else if( pC )
/*N*/               {
/*N*/                   aNewStt.nNode = *pC;
/*N*/                   aNewStt.nContent.Assign( pC, pC->Len() );
/*N*/               }
/*N*/
/*N*/               if( aNewStt <= *pEnd )
/*N*/                   *pNew->GetPoint() = aNewStt;
/*N*/           }
/*N*/           else
/*N*/               aNewStt = *pNew->GetPoint();
/*N*/
/*N*/           if( *pNew->GetPoint() != *pNew->GetMark() &&
/*N*/               _SwRedlineTbl::Insert( pNew, nInsPos ) )
/*N*/           {
//STRIP001              pNew->CallDisplayFunc();
/*N*/               bAnyIns = TRUE;
/*N*/               pNew = 0;
/*N*/               if( pInsPos && *pInsPos < nInsPos )
/*N*/                   *pInsPos = nInsPos;
/*N*/           }
/*N*/
/*N*/           if( aNewStt >= *pEnd ||
/*N*/               0 == (pC = rNds.GoNext( &aNewStt.nNode )) )
/*N*/               break;
/*N*/
/*N*/           aNewStt.nContent.Assign( pC, 0 );
/*N*/
/*N*/       } while( aNewStt < *pEnd );
/*N*/
/*N*/   delete pNew;
/*N*/   delete p, p = 0;
/*N*/   return bAnyIns;
/*N*/ }

/*N*/ void SwRedlineTbl::Remove( USHORT nP, USHORT nL ) //SW50.SDW
/*N*/ {
/*N*/   SwDoc* pDoc = 0;
/*N*/   if( !nP && nL && nL == _SwRedlineTbl::Count() )
/*N*/       pDoc = _SwRedlineTbl::GetObject( 0 )->GetDoc();
/*N*/
/*N*/   _SwRedlineTbl::Remove( nP, nL );
/*N*/
/*N*/   ViewShell* pSh;
/*N*/   if( pDoc && !pDoc->IsInDtor() && pDoc->GetRootFrm() &&
/*N*/       0 != ( pSh = pDoc->GetRootFrm()->GetCurrShell()) )
/*N*/       pSh->InvalidateWindows( SwRect( 0, 0, LONG_MAX, LONG_MAX ) );
/*N*/ }

//STRIP001 void SwRedlineTbl::DeleteAndDestroy( USHORT nP, USHORT nL )
//STRIP001 {
//STRIP001  SwDoc* pDoc = 0;
//STRIP001  if( !nP && nL && nL == _SwRedlineTbl::Count() )
//STRIP001      pDoc = _SwRedlineTbl::GetObject( 0 )->GetDoc();
//STRIP001
//STRIP001  _SwRedlineTbl::DeleteAndDestroy( nP, nL );
//STRIP001
//STRIP001  ViewShell* pSh;
//STRIP001  if( pDoc && !pDoc->IsInDtor() && pDoc->GetRootFrm() &&
//STRIP001      0 != ( pSh = pDoc->GetRootFrm()->GetCurrShell()) )
//STRIP001      pSh->InvalidateWindows( SwRect( 0, 0, LONG_MAX, LONG_MAX ) );
//STRIP001 }

// suche den naechsten oder vorherigen Redline mit dergleichen Seq.No
// Mit dem Lookahead kann die Suche eingeschraenkt werden. 0 oder
// USHRT_MAX suchen im gesamten Array.
//STRIP001 USHORT SwRedlineTbl::FindNextOfSeqNo( USHORT nSttPos, USHORT nLookahead ) const
//STRIP001 {
//STRIP001 #if 0
//STRIP001  USHORT nRet = USHRT_MAX, nEnd,
//STRIP001         nSeqNo = _SwRedlineTbl::GetObject( nSttPos )->GetSeqNo();
//STRIP001  if( nSeqNo )
//STRIP001  {
//STRIP001      nEnd = _SwRedlineTbl::Count();
//STRIP001      if( nLookahead && USHRT_MAX != nLookahead &&
//STRIP001          nSttPos + nLookahead < _SwRedlineTbl::Count() )
//STRIP001          nEnd = nSttPos + nLookahead;
//STRIP001
//STRIP001      while( ++nSttPos < nEnd )
//STRIP001          if( nSeqNo == _SwRedlineTbl::GetObject( nSttPos )->GetSeqNo() )
//STRIP001          {
//STRIP001              nRet = nSttPos;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 #else
//STRIP001  return nSttPos + 1 < _SwRedlineTbl::Count()
//STRIP001              ? FindNextSeqNo( _SwRedlineTbl::GetObject( nSttPos )
//STRIP001                                  ->GetSeqNo(), nSttPos+1, nLookahead )
//STRIP001              : USHRT_MAX;
//STRIP001 #endif
//STRIP001 }

//STRIP001 USHORT SwRedlineTbl::FindPrevOfSeqNo( USHORT nSttPos, USHORT nLookahead ) const
//STRIP001 {
//STRIP001 #if 0
//STRIP001  USHORT nRet = USHRT_MAX, nEnd,
//STRIP001         nSeqNo = _SwRedlineTbl::GetObject( nSttPos )->GetSeqNo();
//STRIP001  if( nSeqNo )
//STRIP001  {
//STRIP001      nEnd = 0;
//STRIP001      if( nLookahead && USHRT_MAX != nLookahead && nSttPos > nLookahead )
//STRIP001          nEnd = nSttPos - nLookahead;
//STRIP001
//STRIP001      while( nSttPos-- > nEnd )
//STRIP001          if( nSeqNo == _SwRedlineTbl::GetObject( nSttPos )->GetSeqNo() )
//STRIP001          {
//STRIP001              nRet = nSttPos;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 #else
//STRIP001  return nSttPos ? FindPrevSeqNo( _SwRedlineTbl::GetObject(
//STRIP001                                      nSttPos )->GetSeqNo(),
//STRIP001                                  nSttPos-1, nLookahead )
//STRIP001                 : USHRT_MAX;
//STRIP001 #endif
//STRIP001 }

//STRIP001 USHORT SwRedlineTbl::FindNextSeqNo( USHORT nSeqNo, USHORT nSttPos,
//STRIP001                                  USHORT nLookahead ) const
//STRIP001 {
//STRIP001  USHORT nRet = USHRT_MAX, nEnd;
//STRIP001  if( nSeqNo && nSttPos < _SwRedlineTbl::Count() )
//STRIP001  {
//STRIP001      nEnd = _SwRedlineTbl::Count();
//STRIP001      if( nLookahead && USHRT_MAX != nLookahead &&
//STRIP001          nSttPos + nLookahead < _SwRedlineTbl::Count() )
//STRIP001          nEnd = nSttPos + nLookahead;
//STRIP001
//STRIP001      for( ; nSttPos < nEnd; ++nSttPos )
//STRIP001          if( nSeqNo == _SwRedlineTbl::GetObject( nSttPos )->GetSeqNo() )
//STRIP001          {
//STRIP001              nRet = nSttPos;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 USHORT SwRedlineTbl::FindPrevSeqNo( USHORT nSeqNo, USHORT nSttPos,
//STRIP001                                  USHORT nLookahead ) const
//STRIP001 {
//STRIP001  USHORT nRet = USHRT_MAX, nEnd;
//STRIP001  if( nSeqNo && nSttPos < _SwRedlineTbl::Count() )
//STRIP001  {
//STRIP001      nEnd = 0;
//STRIP001      if( nLookahead && USHRT_MAX != nLookahead && nSttPos > nLookahead )
//STRIP001          nEnd = nSttPos - nLookahead;
//STRIP001
//STRIP001      ++nSttPos;
//STRIP001      while( nSttPos > nEnd )
//STRIP001          if( nSeqNo == _SwRedlineTbl::GetObject( --nSttPos )->GetSeqNo() )
//STRIP001          {
//STRIP001              nRet = nSttPos;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/*  */

/*?*/SwRedlineExtraData::~SwRedlineExtraData()
/*?*/{
/*?*/}

//STRIP001 void SwRedlineExtraData::Accept( SwPaM& ) const
//STRIP001 {
//STRIP001 }

//STRIP001 void SwRedlineExtraData::Reject( SwPaM& ) const
//STRIP001 {
//STRIP001 }

/*?*/int SwRedlineExtraData::operator == ( const SwRedlineExtraData& ) const
/*?*/{
/*?*/   return FALSE;
/*?*/}


//STRIP001 SwRedlineExtraData_FmtColl::SwRedlineExtraData_FmtColl( const String& rColl,
//STRIP001                                              USHORT nPoolFmtId,
//STRIP001                                              const SfxItemSet* pItemSet )
//STRIP001  : sFmtNm( rColl ), nPoolId( nPoolFmtId ), pSet( 0 )
//STRIP001 {
//STRIP001  if( pItemSet && pItemSet->Count() )
//STRIP001      pSet = new SfxItemSet( *pItemSet );
//STRIP001 }

//STRIP001 SwRedlineExtraData_FmtColl::~SwRedlineExtraData_FmtColl()
//STRIP001 {
//STRIP001  delete pSet;
//STRIP001 }

//STRIP001 SwRedlineExtraData* SwRedlineExtraData_FmtColl::CreateNew() const
//STRIP001 {
//STRIP001  return new SwRedlineExtraData_FmtColl( sFmtNm, nPoolId, pSet );
//STRIP001 }

//STRIP001 void SwRedlineExtraData_FmtColl::Reject( SwPaM& rPam ) const
//STRIP001 {
//STRIP001  SwDoc* pDoc = rPam.GetDoc();
//STRIP001
//STRIP001 // was ist mit Undo ? ist das abgeschaltet ??
//STRIP001  SwTxtFmtColl* pColl = USHRT_MAX == nPoolId
//STRIP001                          ? pDoc->FindTxtFmtCollByName( sFmtNm )
//STRIP001                          : pDoc->GetTxtCollFromPool( nPoolId );
//STRIP001  if( pColl )
//STRIP001      pDoc->SetTxtFmtColl( rPam, pColl, FALSE );
//STRIP001
//STRIP001  if( pSet )
//STRIP001  {
//STRIP001      rPam.SetMark();
//STRIP001      SwPosition& rMark = *rPam.GetMark();
//STRIP001      SwTxtNode* pTNd = rMark.nNode.GetNode().GetTxtNode();
//STRIP001      if( pTNd )
//STRIP001      {
//STRIP001          rMark.nContent.Assign( pTNd, pTNd->GetTxt().Len() );
//STRIP001
//STRIP001          if( pTNd->GetpSwAttrSet() )
//STRIP001          {
//STRIP001              // nur die setzen, die nicht mehr vorhanden sind. Andere
//STRIP001              // koennen jetzt veraendert drin stehen, aber die werden
//STRIP001              // nicht angefasst.
//STRIP001              SfxItemSet aTmp( *pSet );
//STRIP001              aTmp.Differentiate( *pTNd->GetpSwAttrSet() );
//STRIP001              pDoc->Insert( rPam, aTmp );
//STRIP001          }
//STRIP001          else
//STRIP001              pDoc->Insert( rPam, *pSet );
//STRIP001      }
//STRIP001      rPam.DeleteMark();
//STRIP001  }
//STRIP001 }

//STRIP001 int SwRedlineExtraData_FmtColl::operator == ( const SwRedlineExtraData& r) const
//STRIP001 {
//STRIP001  const SwRedlineExtraData_FmtColl& rCmp = (SwRedlineExtraData_FmtColl&)r;
//STRIP001  return sFmtNm == rCmp.sFmtNm && nPoolId == rCmp.nPoolId &&
//STRIP001          ( ( !pSet && !rCmp.pSet ) ||
//STRIP001             ( pSet && rCmp.pSet && *pSet == *rCmp.pSet ) );
//STRIP001 }

//STRIP001 void SwRedlineExtraData_FmtColl::SetItemSet( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  delete pSet;
//STRIP001  if( rSet.Count() )
//STRIP001      pSet = new SfxItemSet( rSet );
//STRIP001  else
//STRIP001      pSet = 0;
//STRIP001 }


//STRIP001 SwRedlineExtraData_Format::SwRedlineExtraData_Format( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SfxItemIter aIter( rSet );
//STRIP001  const SfxPoolItem* pItem = aIter.FirstItem();
//STRIP001  while( TRUE )
//STRIP001  {
//STRIP001      aWhichIds.Insert( pItem->Which(), aWhichIds.Count() );
//STRIP001      if( aIter.IsAtEnd() )
//STRIP001          break;
//STRIP001      pItem = aIter.NextItem();
//STRIP001  }
//STRIP001 }

//STRIP001 SwRedlineExtraData_Format::SwRedlineExtraData_Format(
//STRIP001      const SwRedlineExtraData_Format& rCpy )
//STRIP001  : aWhichIds( (BYTE)rCpy.aWhichIds.Count() )
//STRIP001 {
//STRIP001  aWhichIds.Insert( &rCpy.aWhichIds, 0 );
//STRIP001 }

//STRIP001 SwRedlineExtraData_Format::~SwRedlineExtraData_Format()
//STRIP001 {
//STRIP001 }

//STRIP001 SwRedlineExtraData* SwRedlineExtraData_Format::CreateNew() const
//STRIP001 {
//STRIP001  return new SwRedlineExtraData_Format( *this );
//STRIP001 }

//STRIP001 void SwRedlineExtraData_Format::Reject( SwPaM& rPam ) const
//STRIP001 {
//STRIP001  SwDoc* pDoc = rPam.GetDoc();
//STRIP001
//STRIP001  SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001  pDoc->SetRedlineMode_intern( eOld & ~(REDLINE_ON | REDLINE_IGNORE) );
//STRIP001
//STRIP001  // eigentlich muesste hier das Attribut zurueck gesetzt werden!!!
//STRIP001  for( USHORT n = 0, nEnd = aWhichIds.Count(); n < nEnd; ++n )
//STRIP001      pDoc->Insert( rPam, *GetDfltAttr( aWhichIds[ n ] ), SETATTR_DONTEXPAND );
//STRIP001
//STRIP001  pDoc->SetRedlineMode_intern( eOld );
//STRIP001 }

//STRIP001 int SwRedlineExtraData_Format::operator == ( const SwRedlineExtraData& rCmp ) const
//STRIP001 {
//STRIP001  int nRet = 1;
//STRIP001  USHORT n = 0, nEnd = aWhichIds.Count();
//STRIP001  if( nEnd != ((SwRedlineExtraData_Format&)rCmp).aWhichIds.Count() )
//STRIP001      nRet = 0;
//STRIP001  else
//STRIP001      for( ; n < nEnd; ++n )
//STRIP001          if( ((SwRedlineExtraData_Format&)rCmp).aWhichIds[n] != aWhichIds[n])
//STRIP001          {
//STRIP001              nRet = 0;
//STRIP001              break;
//STRIP001          }
//STRIP001  return nRet;
//STRIP001 }

/*  */

/*?*/SwRedlineData::SwRedlineData( SwRedlineType eT, USHORT nAut )
/*?*/   : eType( eT ), pNext( 0 ), nAuthor( nAut ), pExtraData( 0 ), nSeqNo( 0 )
/*?*/{
/*?*/   aStamp.SetSec( 0 );
/*?*/   aStamp.Set100Sec( 0 );
/*?*/}

/*?*/SwRedlineData::SwRedlineData( const SwRedlineData& rCpy, BOOL bCpyNext )
/*?*/   : nAuthor( rCpy.nAuthor ), eType( rCpy.eType ), aStamp( rCpy.aStamp ),
/*?*/   sComment( rCpy.sComment ), nSeqNo( rCpy.nSeqNo ),
/*?*/   pExtraData( rCpy.pExtraData ? rCpy.pExtraData->CreateNew() : 0 ),
/*?*/   pNext( (bCpyNext && rCpy.pNext) ? new SwRedlineData( *rCpy.pNext ) : 0 )
/*?*/{
/*?*/}

    // fuer sw3io: pNext geht in eigenen Besitz ueber!
/*?*/SwRedlineData::SwRedlineData( SwRedlineType eT, USHORT nAut, const DateTime& rDT,
/*?*/                  const String& rCmnt, SwRedlineData *pNxt,
/*?*/                  SwRedlineExtraData* pData )
/*?*/   : eType( eT ), pNext( pNxt ), nAuthor( nAut ), aStamp( rDT ),
/*?*/     sComment( rCmnt ), pExtraData( pData ), nSeqNo( 0 )
/*?*/{
/*?*/}

/*?*/SwRedlineData::~SwRedlineData()
/*?*/{
/*?*/   delete pExtraData;
/*?*/   delete pNext;
/*?*/}

    // ExtraData wird kopiert, der Pointer geht also NICHT in den Besitz
    // des RedlineObjectes!
/*?*/void SwRedlineData::SetExtraData( const SwRedlineExtraData* pData )
/*?*/{
/*?*/   delete pExtraData;
/*?*/
/*?*/   if( pData )
/*?*/       pExtraData = pData->CreateNew();
/*?*/   else
/*?*/       pExtraData = 0;
/*?*/}

/*  */

/*?*/SwRedline::SwRedline( SwRedlineType eTyp, const SwPaM& rPam )
/*?*/   : SwPaM( *rPam.GetMark(), *rPam.GetPoint() ),
/*?*/   pCntntSect( 0 ),
/*?*/   pRedlineData( new SwRedlineData( eTyp, GetDoc()->GetRedlineAuthor() ) )
/*?*/{
/*?*/   bDelLastPara = bIsLastParaDelete = FALSE;
/*?*/   bIsVisible = TRUE;
/*?*/   if( !rPam.HasMark() )
/*?*/       DeleteMark();
/*?*/}

/*?*/SwRedline::SwRedline( SwRedlineType eTyp, const SwPosition& rPos )
/*?*/   : SwPaM( rPos ),
/*?*/   pCntntSect( 0 ),
/*?*/   pRedlineData( new SwRedlineData( eTyp, GetDoc()->GetRedlineAuthor() ) )
/*?*/{
/*?*/   bDelLastPara = bIsLastParaDelete = FALSE;
/*?*/   bIsVisible = TRUE;
/*?*/}

/*?*/SwRedline::SwRedline( const SwRedlineData& rData, const SwPaM& rPam )
/*?*/   : SwPaM( *rPam.GetMark(), *rPam.GetPoint() ),
/*?*/   pCntntSect( 0 ),
/*?*/   pRedlineData( new SwRedlineData( rData ))
/*?*/{
/*?*/   bDelLastPara = bIsLastParaDelete = FALSE;
/*?*/   bIsVisible = TRUE;
/*?*/   if( !rPam.HasMark() )
/*?*/       DeleteMark();
/*?*/}

/*?*/SwRedline::SwRedline( const SwRedlineData& rData, const SwPosition& rPos )
/*?*/   : SwPaM( rPos ),
/*?*/   pCntntSect( 0 ),
/*?*/   pRedlineData( new SwRedlineData( rData ))
/*?*/{
/*?*/   bDelLastPara = bIsLastParaDelete = FALSE;
/*?*/   bIsVisible = TRUE;
/*?*/}

/*?*/SwRedline::SwRedline( const SwRedline& rCpy )
/*?*/   : SwPaM( *rCpy.GetMark(), *rCpy.GetPoint() ),
/*?*/   pCntntSect( 0 ),
/*?*/   pRedlineData( new SwRedlineData( *rCpy.pRedlineData ))
/*?*/{
/*?*/   bDelLastPara = bIsLastParaDelete = FALSE;
/*?*/   bIsVisible = TRUE;
/*?*/   if( !rCpy.HasMark() )
/*?*/       DeleteMark();
/*?*/}

/*?*/SwRedline::~SwRedline()
/*?*/{
/*?*/   if( pCntntSect )
/*?*/   {
/*?*/       // dann den Content Bereich loeschen
/*?*/       if( !GetDoc()->IsInDtor() )
/*?*/           GetDoc()->DeleteSection( &pCntntSect->GetNode() );
/*?*/       delete pCntntSect;
/*?*/   }
/*?*/   delete pRedlineData;
/*?*/}

// liegt eine gueltige Selektion vor?
/*N*/ BOOL SwRedline::HasValidRange() const //SW50.SDW
/*N*/ {
/*N*/   const SwNode* pPtNd = &GetPoint()->nNode.GetNode(),
/*N*/               * pMkNd = &GetMark()->nNode.GetNode();
/*N*/   if( pPtNd->FindStartNode() == pMkNd->FindStartNode() &&
/*N*/       !pPtNd->FindStartNode()->IsTableNode() &&
/*N*/       // JP 18.5.2001: Bug 87222 - invalid if points on the end of content
/*N*/         // DVO 25.03.2002: #96530# end-of-content only invalid if no content
/*N*/         //                 index exists
/*N*/       ( pPtNd != pMkNd || GetContentIdx() != NULL ||
/*N*/           pPtNd != &pPtNd->GetNodes().GetEndOfContent() )
/*N*/       )
/*N*/       return TRUE;
/*N*/   return FALSE;
/*N*/ }

//STRIP001 void SwRedline::CallDisplayFunc( USHORT nLoop )
//STRIP001 {
//STRIP001  switch( REDLINE_SHOW_MASK & GetDoc()->GetRedlineMode() )
//STRIP001  {
//STRIP001  case REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE:
//STRIP001      Show( nLoop );
//STRIP001      break;
//STRIP001  case REDLINE_SHOW_INSERT:
//STRIP001      Hide( nLoop );
//STRIP001      break;
//STRIP001  case REDLINE_SHOW_DELETE:
//STRIP001      ShowOriginal( nLoop );
//STRIP001      break;
//STRIP001  }
//STRIP001 }

/*N*/ void SwRedline::Show( USHORT nLoop )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( 1 <= nLoop )
//STRIP001  {
//STRIP001      SwDoc* pDoc = GetDoc();
//STRIP001      SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001      pDoc->SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001      BOOL bUndo = pDoc->DoesUndo();
//STRIP001      pDoc->DoUndo( FALSE );
//STRIP001
//STRIP001      switch( GetType() )
//STRIP001      {
//STRIP001      case REDLINE_INSERT:            // Inhalt wurde eingefuegt
//STRIP001          bIsVisible = TRUE;
//STRIP001          MoveFromSection();
//STRIP001          break;
//STRIP001
//STRIP001      case REDLINE_DELETE:            // Inhalt wurde geloescht
//STRIP001          bIsVisible = TRUE;
//STRIP001          MoveFromSection();
//STRIP001          break;
//STRIP001
//STRIP001      case REDLINE_FORMAT:            // Attributierung wurde angewendet
//STRIP001      case REDLINE_TABLE:             // TabellenStruktur wurde veraendert
//STRIP001          InvalidateRange();
//STRIP001          break;
//STRIP001      }
//STRIP001      pDoc->SetRedlineMode_intern( eOld );
//STRIP001      pDoc->DoUndo( bUndo );
//STRIP001  }
/*N*/ }

/*N*/ void SwRedline::Hide( USHORT nLoop )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwDoc* pDoc = GetDoc();
//STRIP001  SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001  pDoc->SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001  BOOL bUndo = pDoc->DoesUndo();
//STRIP001  pDoc->DoUndo( FALSE );
//STRIP001
//STRIP001  switch( GetType() )
//STRIP001  {
//STRIP001  case REDLINE_INSERT:            // Inhalt wurde eingefuegt
//STRIP001      bIsVisible = TRUE;
//STRIP001      if( 1 <= nLoop )
//STRIP001          MoveFromSection();
//STRIP001      break;
//STRIP001
//STRIP001  case REDLINE_DELETE:            // Inhalt wurde geloescht
//STRIP001      bIsVisible = FALSE;
//STRIP001      switch( nLoop )
//STRIP001      {
//STRIP001      case 0: MoveToSection();    break;
//STRIP001      case 1: CopyToSection();    break;
//STRIP001      case 2: DelCopyOfSection(); break;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case REDLINE_FORMAT:            // Attributierung wurde angewendet
//STRIP001  case REDLINE_TABLE:             // TabellenStruktur wurde veraendert
//STRIP001      if( 1 <= nLoop )
//STRIP001          InvalidateRange();
//STRIP001      break;
//STRIP001  }
//STRIP001  pDoc->SetRedlineMode_intern( eOld );
//STRIP001  pDoc->DoUndo( bUndo );
/*N*/ }

//STRIP001 void SwRedline::ShowOriginal( USHORT nLoop )
//STRIP001 {
//STRIP001  SwDoc* pDoc = GetDoc();
//STRIP001  SwRedlineMode eOld = pDoc->GetRedlineMode();
//STRIP001  pDoc->SetRedlineMode_intern( eOld | REDLINE_IGNORE );
//STRIP001  BOOL bUndo = pDoc->DoesUndo();
//STRIP001  pDoc->DoUndo( FALSE );
//STRIP001
//STRIP001  // bestimme den Type, ist der erste auf Stack
//STRIP001  for( SwRedlineData* pCur = pRedlineData; pCur->pNext; )
//STRIP001      pCur = pCur->pNext;
//STRIP001
//STRIP001  switch( pCur->eType )
//STRIP001  {
//STRIP001  case REDLINE_INSERT:            // Inhalt wurde eingefuegt
//STRIP001      bIsVisible = FALSE;
//STRIP001      switch( nLoop )
//STRIP001      {
//STRIP001      case 0: MoveToSection();    break;
//STRIP001      case 1: CopyToSection();    break;
//STRIP001      case 2: DelCopyOfSection(); break;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case REDLINE_DELETE:            // Inhalt wurde geloescht
//STRIP001      bIsVisible = TRUE;
//STRIP001      if( 1 <= nLoop )
//STRIP001          MoveFromSection();
//STRIP001      break;
//STRIP001
//STRIP001  case REDLINE_FORMAT:            // Attributierung wurde angewendet
//STRIP001  case REDLINE_TABLE:             // TabellenStruktur wurde veraendert
//STRIP001      if( 1 <= nLoop )
//STRIP001          InvalidateRange();
//STRIP001      break;
//STRIP001  }
//STRIP001  pDoc->SetRedlineMode_intern( eOld );
//STRIP001  pDoc->DoUndo( bUndo );
//STRIP001 }


//STRIP001 void SwRedline::InvalidateRange()        // das Layout anstossen
//STRIP001 {
//STRIP001  ULONG nSttNd = GetMark()->nNode.GetIndex(),
//STRIP001          nEndNd = GetPoint()->nNode.GetIndex();
//STRIP001  USHORT nSttCnt = GetMark()->nContent.GetIndex(),
//STRIP001          nEndCnt = GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001  if( nSttNd > nEndNd || ( nSttNd == nEndNd && nSttCnt > nEndCnt ))
//STRIP001  {
//STRIP001      ULONG nTmp = nSttNd; nSttNd = nEndNd; nEndNd = nTmp;
//STRIP001      nTmp = nSttCnt; nSttCnt = nEndCnt; nEndCnt = (USHORT)nTmp;
//STRIP001  }
//STRIP001
//STRIP001  SwUpdateAttr aHt( 0, 0, RES_FMT_CHG );
//STRIP001  SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  SwNode* pNd;
//STRIP001  for( ULONG n = nSttNd; n <= nEndNd; ++n )
//STRIP001      if( ND_TEXTNODE == ( pNd = rNds[ n ] )->GetNodeType() )
//STRIP001      {
//STRIP001          aHt.nStart = n == nSttNd ? nSttCnt : 0;
//STRIP001          aHt.nEnd = n == nEndNd ? nEndCnt : ((SwTxtNode*)pNd)->GetTxt().Len();
//STRIP001          ((SwTxtNode*)pNd)->Modify( &aHt, &aHt );
//STRIP001      }
//STRIP001 }

/*************************************************************************
 *                      SwRedline::CalcStartEnd()
 * Calculates the start and end position of the intersection rTmp and
 * text node nNdIdx
 *************************************************************************/

//STRIP001 void SwRedline::CalcStartEnd( USHORT nNdIdx, USHORT& nStart, USHORT& nEnd ) const
//STRIP001 {
//STRIP001     const SwPosition *pRStt = Start(), *pREnd = End();
//STRIP001  if( pRStt->nNode < nNdIdx )
//STRIP001  {
//STRIP001      if( pREnd->nNode > nNdIdx )
//STRIP001      {
//STRIP001          nStart = 0;             // Absatz ist komplett enthalten
//STRIP001          nEnd = STRING_LEN;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ASSERT( pREnd->nNode == nNdIdx,
//STRIP001              "SwRedlineItr::Seek: GetRedlinePos Error" );
//STRIP001          nStart = 0;             // Absatz wird vorne ueberlappt
//STRIP001          nEnd = pREnd->nContent.GetIndex();
//STRIP001      }
//STRIP001  }
//STRIP001  else if( pRStt->nNode == nNdIdx )
//STRIP001  {
//STRIP001      nStart = pRStt->nContent.GetIndex();
//STRIP001      if( pREnd->nNode == nNdIdx )
//STRIP001          nEnd = pREnd->nContent.GetIndex(); // Innerhalb des Absatzes
//STRIP001      else
//STRIP001          nEnd = STRING_LEN;      // Absatz wird hinten ueberlappt
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nStart = STRING_LEN;
//STRIP001      nEnd = STRING_LEN;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwRedline::MoveToSection()
//STRIP001 {
//STRIP001  if( !pCntntSect )
//STRIP001  {
//STRIP001      const SwPosition* pStt = Start(),
//STRIP001                      * pEnd = pStt == GetPoint() ? GetMark() : GetPoint();
//STRIP001
//STRIP001      SwDoc* pDoc = GetDoc();
//STRIP001      SwPaM aPam( *pStt, *pEnd );
//STRIP001      SwCntntNode* pCSttNd = pStt->nNode.GetNode().GetCntntNode();
//STRIP001      SwCntntNode* pCEndNd = pEnd->nNode.GetNode().GetCntntNode();
//STRIP001
//STRIP001      BOOL bNoLastPara = FALSE;
//STRIP001
//STRIP001      if( !pCSttNd )
//STRIP001      {
//STRIP001          // damit die Indizies der anderen Redlines nicht mitverschoben
//STRIP001          // werden, diese aufs Ende setzen (ist exclusive).
//STRIP001          const SwRedlineTbl& rTbl = pDoc->GetRedlineTbl();
//STRIP001          for( USHORT n = 0; n < rTbl.Count(); ++n )
//STRIP001          {
//STRIP001              SwRedline* pRedl = rTbl[ n ];
//STRIP001              if( pRedl->GetBound(TRUE) == *pStt )
//STRIP001                  pRedl->GetBound(TRUE) = *pEnd;
//STRIP001              if( pRedl->GetBound(FALSE) == *pStt )
//STRIP001                  pRedl->GetBound(FALSE) = *pEnd;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      SwStartNode* pSttNd;
//STRIP001      SwNodes& rNds = pDoc->GetNodes();
//STRIP001      if( pCSttNd || pCEndNd )
//STRIP001      {
//STRIP001          SwTxtFmtColl* pColl = (pCSttNd && pCSttNd->IsTxtNode() )
//STRIP001                                  ? ((SwTxtNode*)pCSttNd)->GetTxtColl()
//STRIP001                                  : (pCEndNd && pCEndNd->IsTxtNode() )
//STRIP001                                      ? ((SwTxtNode*)pCEndNd)->GetTxtColl()
//STRIP001                                      : pDoc->GetTxtCollFromPool(
//STRIP001                                              RES_POOLCOLL_STANDARD );
//STRIP001
//STRIP001          pSttNd = rNds.MakeTextSection( SwNodeIndex( rNds.GetEndOfRedlines() ),
//STRIP001                                          SwNormalStartNode, pColl );
//STRIP001          SwTxtNode* pTxtNd = rNds[ pSttNd->GetIndex() + 1 ]->GetTxtNode();
//STRIP001
//STRIP001          SwNodeIndex aNdIdx( *pTxtNd );
//STRIP001          SwPosition aPos( aNdIdx, SwIndex( pTxtNd ));
//STRIP001          if( pCSttNd && pCEndNd )
//STRIP001              pDoc->MoveAndJoin( aPam, aPos );
//STRIP001          else
//STRIP001          {
//STRIP001              if( pCSttNd && !pCEndNd )
//STRIP001                  bDelLastPara = TRUE;
//STRIP001              pDoc->Move( aPam, aPos );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pSttNd = rNds.MakeEmptySection( SwNodeIndex( rNds.GetEndOfRedlines() ),
//STRIP001                                          SwNormalStartNode );
//STRIP001
//STRIP001          SwPosition aPos( *pSttNd->EndOfSectionNode() );
//STRIP001          pDoc->Move( aPam, aPos );
//STRIP001      }
//STRIP001      pCntntSect = new SwNodeIndex( *pSttNd );
//STRIP001
//STRIP001      if( pStt == GetPoint() )
//STRIP001          Exchange();
//STRIP001
//STRIP001      DeleteMark();
//STRIP001  }
//STRIP001  else
//STRIP001      InvalidateRange();
//STRIP001 }

//STRIP001 void SwRedline::CopyToSection()
//STRIP001 {
//STRIP001  if( !pCntntSect )
//STRIP001  {
//STRIP001      const SwPosition* pStt = Start(),
//STRIP001                      * pEnd = pStt == GetPoint() ? GetMark() : GetPoint();
//STRIP001
//STRIP001      SwCntntNode* pCSttNd = pStt->nNode.GetNode().GetCntntNode();
//STRIP001      SwCntntNode* pCEndNd = pEnd->nNode.GetNode().GetCntntNode();
//STRIP001
//STRIP001      SwStartNode* pSttNd;
//STRIP001      SwDoc* pDoc = GetDoc();
//STRIP001      SwNodes& rNds = pDoc->GetNodes();
//STRIP001
//STRIP001      BOOL bSaveCopyFlag = pDoc->IsCopyIsMove(),
//STRIP001           bSaveRdlMoveFlg = pDoc->IsRedlineMove();
//STRIP001      pDoc->SetCopyIsMove( TRUE );
//STRIP001
//STRIP001         // #100619# The IsRedlineMove() flag causes the behaviour of the
//STRIP001         // SwDoc::_CopyFlyInFly method to change, which will eventually be
//STRIP001         // called by the pDoc->Copy line below (through SwDoc::_Copy,
//STRIP001         // SwDoc::CopyWithFlyInFly). This rather obscure bugfix was introduced
//STRIP001         // for #63198# and #64896#, and apparently never really worked.
//STRIP001      pDoc->SetRedlineMove( pStt->nContent == 0 );
//STRIP001
//STRIP001      if( pCSttNd )
//STRIP001      {
//STRIP001          SwTxtFmtColl* pColl = (pCSttNd && pCSttNd->IsTxtNode() )
//STRIP001                                  ? ((SwTxtNode*)pCSttNd)->GetTxtColl()
//STRIP001                                  : pDoc->GetTxtCollFromPool(
//STRIP001                                              RES_POOLCOLL_STANDARD );
//STRIP001
//STRIP001          pSttNd = rNds.MakeTextSection( SwNodeIndex( rNds.GetEndOfRedlines() ),
//STRIP001                                          SwNormalStartNode, pColl );
//STRIP001
//STRIP001          SwNodeIndex aNdIdx( *pSttNd, 1 );
//STRIP001          SwTxtNode* pTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001          SwPosition aPos( aNdIdx, SwIndex( pTxtNd ));
//STRIP001          pDoc->Copy( *this, aPos );
//STRIP001
//STRIP001          // JP 08.10.98: die Vorlage vom EndNode ggfs. mit uebernehmen
//STRIP001          //              - ist im Doc::Copy nicht erwuenscht
//STRIP001          if( pCEndNd && pCEndNd != pCSttNd )
//STRIP001          {
//STRIP001              SwCntntNode* pDestNd = aPos.nNode.GetNode().GetCntntNode();
//STRIP001              if( pDestNd )
//STRIP001              {
//STRIP001                  if( pDestNd->IsTxtNode() && pCEndNd->IsTxtNode() )
//STRIP001                      ((SwTxtNode*)pCEndNd)->CopyCollFmt(
//STRIP001                                          *(SwTxtNode*)pDestNd );
//STRIP001                  else
//STRIP001                      pDestNd->ChgFmtColl( pCEndNd->GetFmtColl() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pSttNd = rNds.MakeEmptySection( SwNodeIndex( rNds.GetEndOfRedlines() ),
//STRIP001                                          SwNormalStartNode );
//STRIP001
//STRIP001          if( pCEndNd )
//STRIP001          {
//STRIP001              SwPosition aPos( *pSttNd->EndOfSectionNode() );
//STRIP001              pDoc->Copy( *this, aPos );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwNodeIndex aInsPos( *pSttNd->EndOfSectionNode() );
//STRIP001              SwNodeRange aRg( pStt->nNode, 0, pEnd->nNode, 1 );
//STRIP001              pDoc->CopyWithFlyInFly( aRg, aInsPos );
//STRIP001          }
//STRIP001      }
//STRIP001      pCntntSect = new SwNodeIndex( *pSttNd );
//STRIP001
//STRIP001      pDoc->SetCopyIsMove( bSaveCopyFlag );
//STRIP001      pDoc->SetRedlineMove( bSaveRdlMoveFlg );
//STRIP001  }
//STRIP001 }

//STRIP001 static bool lcl_PamIsFullPara(const SwPaM & rPam)
//STRIP001 {
//STRIP001     const SwPosition* pStt = rPam.Start(),
//STRIP001         * pEnd = pStt == rPam.GetPoint() ? rPam.GetMark() :
//STRIP001         rPam.GetPoint();
//STRIP001
//STRIP001     return pStt->nNode != pEnd->nNode && pStt->nContent.GetIndex() == 0 &&
//STRIP001         pEnd->nContent.GetIndex() == 0;
//STRIP001 }

//STRIP001 void SwRedline::DelCopyOfSection()
//STRIP001 {
//STRIP001  if( pCntntSect )
//STRIP001  {
//STRIP001      const SwPosition* pStt = Start(),
//STRIP001                      * pEnd = pStt == GetPoint() ? GetMark() : GetPoint();
//STRIP001
//STRIP001      SwDoc* pDoc = GetDoc();
//STRIP001      SwPaM aPam( *pStt, *pEnd );
//STRIP001      SwCntntNode* pCSttNd = pStt->nNode.GetNode().GetCntntNode();
//STRIP001      SwCntntNode* pCEndNd = pEnd->nNode.GetNode().GetCntntNode();
//STRIP001
//STRIP001      if( !pCSttNd )
//STRIP001      {
//STRIP001          // damit die Indizies der anderen Redlines nicht mitverschoben
//STRIP001          // werden, diese aufs Ende setzen (ist exclusive).
//STRIP001          const SwRedlineTbl& rTbl = pDoc->GetRedlineTbl();
//STRIP001          for( USHORT n = 0; n < rTbl.Count(); ++n )
//STRIP001          {
//STRIP001              SwRedline* pRedl = rTbl[ n ];
//STRIP001              if( pRedl->GetBound(TRUE) == *pStt )
//STRIP001                  pRedl->GetBound(TRUE) = *pEnd;
//STRIP001              if( pRedl->GetBound(FALSE) == *pStt )
//STRIP001                  pRedl->GetBound(FALSE) = *pEnd;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      SwNodes& rNds = pDoc->GetNodes();
//STRIP001      if( pCSttNd && pCEndNd )
//STRIP001          pDoc->DeleteAndJoin( aPam );
//STRIP001      else if( pCSttNd || pCEndNd )
//STRIP001      {
//STRIP001          if( pCSttNd && !pCEndNd )
//STRIP001              bDelLastPara = TRUE;
//STRIP001          pDoc->Delete( aPam );
//STRIP001
//STRIP001          if( bDelLastPara )
//STRIP001          {
//STRIP001                 // #100611# To prevent dangling references to the paragraph to
//STRIP001                 // be deleted, redline that point into this paragraph should be
//STRIP001                 // moved to the new end position. Since redlines in the redline
//STRIP001                 // table are sorted and the pEnd position is an endnode (see
//STRIP001                 // bDelLastPara condition above), only redlines before the
//STRIP001                 // current ones can be affected.
//STRIP001              const SwRedlineTbl& rTbl = pDoc->GetRedlineTbl();
//STRIP001              USHORT n = rTbl.GetPos( this );
//STRIP001                 ASSERT( n != USHRT_MAX, "How strange. We don't exist!" );
//STRIP001              for( BOOL bBreak = FALSE; !bBreak && n > 0; )
//STRIP001              {
//STRIP001                     --n;
//STRIP001                  bBreak = TRUE;
//STRIP001                  if( rTbl[ n ]->GetBound(TRUE) == *aPam.GetPoint() )
//STRIP001                  {
//STRIP001                      rTbl[ n ]->GetBound(TRUE) = *pEnd;
//STRIP001                      bBreak = FALSE;
//STRIP001                  }
//STRIP001                  if( rTbl[ n ]->GetBound(FALSE) == *aPam.GetPoint() )
//STRIP001                  {
//STRIP001                      rTbl[ n ]->GetBound(FALSE) = *pEnd;
//STRIP001                      bBreak = FALSE;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              SwPosition aEnd( *pEnd );
//STRIP001              *GetPoint() = *pEnd;
//STRIP001              *GetMark() = *pEnd;
//STRIP001              DeleteMark();
//STRIP001
//STRIP001              aPam.GetBound( TRUE ).nContent.Assign( 0, 0 );
//STRIP001              aPam.GetBound( FALSE ).nContent.Assign( 0, 0 );
//STRIP001              aPam.DeleteMark();
//STRIP001              pDoc->DelFullPara( aPam );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          pDoc->Delete( aPam );
//STRIP001
//STRIP001      if( pStt == GetPoint() )
//STRIP001          Exchange();
//STRIP001
//STRIP001      DeleteMark();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwRedline::MoveFromSection()
//STRIP001 {
//STRIP001  if( pCntntSect )
//STRIP001  {
//STRIP001      SwDoc* pDoc = GetDoc();
//STRIP001      const SwRedlineTbl& rTbl = pDoc->GetRedlineTbl();
//STRIP001      SvPtrarr aBeforeArr( 16, 16 ), aBehindArr( 16, 16 );
//STRIP001      USHORT nMyPos = rTbl.GetPos( this );
//STRIP001      ASSERT( this, "this nicht im Array?" );
//STRIP001      register BOOL bBreak = FALSE;
//STRIP001
//STRIP001      for( USHORT n = nMyPos+1; !bBreak && n < rTbl.Count(); ++n )
//STRIP001      {
//STRIP001          bBreak = TRUE;
//STRIP001          if( rTbl[ n ]->GetBound(TRUE) == *GetPoint() )
//STRIP001          {
//STRIP001              void* pTmp = &rTbl[ n ]->GetBound(TRUE);
//STRIP001              aBehindArr.Insert( pTmp, aBehindArr.Count());
//STRIP001              bBreak = FALSE;
//STRIP001          }
//STRIP001          if( rTbl[ n ]->GetBound(FALSE) == *GetPoint() )
//STRIP001          {
//STRIP001              void* pTmp = &rTbl[ n ]->GetBound(FALSE);
//STRIP001              aBehindArr.Insert( pTmp, aBehindArr.Count() );
//STRIP001              bBreak = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      for( bBreak = FALSE, n = nMyPos; !bBreak && n ; )
//STRIP001      {
//STRIP001          --n;
//STRIP001          bBreak = TRUE;
//STRIP001          if( rTbl[ n ]->GetBound(TRUE) == *GetPoint() )
//STRIP001          {
//STRIP001              void* pTmp = &rTbl[ n ]->GetBound(TRUE);
//STRIP001              aBeforeArr.Insert( pTmp, aBeforeArr.Count() );
//STRIP001              bBreak = FALSE;
//STRIP001          }
//STRIP001          if( rTbl[ n ]->GetBound(FALSE) == *GetPoint() )
//STRIP001          {
//STRIP001              void* pTmp = &rTbl[ n ]->GetBound(FALSE);
//STRIP001              aBeforeArr.Insert( pTmp, aBeforeArr.Count() );
//STRIP001              bBreak = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      {
//STRIP001          BOOL bAddFlag = TRUE;
//STRIP001          SwPaM aPam( pCntntSect->GetNode(),
//STRIP001                      *pCntntSect->GetNode().EndOfSectionNode(), 1,
//STRIP001                      ( bDelLastPara ? -2 : -1 ) );
//STRIP001          SwCntntNode* pCNd = aPam.GetCntntNode();
//STRIP001          if( pCNd )
//STRIP001              aPam.GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001          else
//STRIP001              aPam.GetPoint()->nNode++;
//STRIP001
//STRIP001          SwFmtColl* pColl = pCNd && aPam.GetPoint()->nNode !=
//STRIP001                                      aPam.GetMark()->nNode
//STRIP001                              ? pCNd->GetFmtColl() : 0;
//STRIP001
//STRIP001          SwNodeIndex aNdIdx( GetPoint()->nNode, -1 );
//STRIP001          USHORT nPos = GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001          SwPosition aPos( *GetPoint() );
//STRIP001          if( bDelLastPara && *aPam.GetPoint() == *aPam.GetMark() )
//STRIP001          {
//STRIP001              aPos.nNode--;
//STRIP001
//STRIP001              pDoc->AppendTxtNode( aPos );
//STRIP001          }
//STRIP001          else
//STRIP001              pDoc->Move( aPam, aPos, DOC_MOVEALLFLYS );
//STRIP001
//STRIP001          SetMark();
//STRIP001          *GetPoint() = aPos;
//STRIP001          GetMark()->nNode = aNdIdx.GetIndex() + 1;
//STRIP001          pCNd = GetMark()->nNode.GetNode().GetCntntNode();
//STRIP001          GetMark()->nContent.Assign( pCNd, nPos );
//STRIP001
//STRIP001          if( bDelLastPara )
//STRIP001          {
//STRIP001              GetPoint()->nNode++;
//STRIP001              GetPoint()->nContent.Assign( pCNd = GetCntntNode(), 0 );
//STRIP001              bDelLastPara = FALSE;
//STRIP001          }
//STRIP001          else if( pColl )
//STRIP001              pCNd = GetCntntNode();
//STRIP001
//STRIP001          if( pColl && pCNd )
//STRIP001              pCNd->ChgFmtColl( pColl );
//STRIP001      }
//STRIP001      pDoc->DeleteSection( &pCntntSect->GetNode() );
//STRIP001      delete pCntntSect, pCntntSect = 0;
//STRIP001
//STRIP001         // #100611# adjustment of redline table positions must take start and
//STRIP001         // end into account, not point and mark.
//STRIP001      for( n = 0; n < aBeforeArr.Count(); ++n )
//STRIP001          *(SwPosition*)aBeforeArr[ n ] = *Start();
//STRIP001      for( n = 0; n < aBehindArr.Count(); ++n )
//STRIP001          *(SwPosition*)aBehindArr[ n ] = *End();
//STRIP001  }
//STRIP001  else
//STRIP001      InvalidateRange();
//STRIP001 }

// fuers Undo
/*N*/ void SwRedline::SetContentIdx( const SwNodeIndex* pIdx )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   if( pIdx && !pCntntSect )
//STRIP001  {
//STRIP001      pCntntSect = new SwNodeIndex( *pIdx );
//STRIP001      bIsVisible = FALSE;
//STRIP001  }
//STRIP001  else if( !pIdx && pCntntSect )
//STRIP001  {
//STRIP001      delete pCntntSect, pCntntSect = 0;
//STRIP001      bIsVisible = FALSE;
//STRIP001  }
//STRIP001 #ifndef PRODUCT
//STRIP001  else
//STRIP001      ASSERT( !this, "das ist keine gueltige Operation" );
//STRIP001 #endif
/*N*/ }

//STRIP001 BOOL SwRedline::CanCombine( const SwRedline& rRedl ) const
//STRIP001 {
//STRIP001  return  IsVisible() && rRedl.IsVisible() &&
//STRIP001          pRedlineData->CanCombine( *rRedl.pRedlineData );
//STRIP001 }

//STRIP001 void SwRedline::PushData( const SwRedline& rRedl, BOOL bOwnAsNext )
//STRIP001 {
//STRIP001 //   SwRedlineData* pNew = new SwRedlineData( rRedl.GetType(),
//STRIP001 //                                            rRedl.GetAuthor() );
//STRIP001  SwRedlineData* pNew = new SwRedlineData( *rRedl.pRedlineData, FALSE );
//STRIP001  if( bOwnAsNext )
//STRIP001  {
//STRIP001      pNew->pNext = pRedlineData;
//STRIP001      pRedlineData = pNew;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pNew->pNext = pRedlineData->pNext;
//STRIP001      pRedlineData->pNext = pNew;
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwRedline::PopData()
//STRIP001 {
//STRIP001  if( !pRedlineData->pNext )
//STRIP001      return FALSE;
//STRIP001  SwRedlineData* pCur = pRedlineData;
//STRIP001  pRedlineData = pCur->pNext;
//STRIP001  pCur->pNext = 0;
//STRIP001  delete pCur;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 USHORT SwRedline::GetStackCount() const
//STRIP001 {
//STRIP001  USHORT nRet = 1;
//STRIP001  for( SwRedlineData* pCur = pRedlineData; pCur->pNext; ++nRet )
//STRIP001      pCur = pCur->pNext;
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 USHORT SwRedline::GetAuthor( USHORT nPos ) const
//STRIP001 {
//STRIP001  for( SwRedlineData* pCur = pRedlineData; nPos && pCur->pNext; --nPos )
//STRIP001      pCur = pCur->pNext;
//STRIP001  ASSERT( !nPos, "Pos angabe ist zu gross" );
//STRIP001  return pCur->nAuthor;
//STRIP001 }

/*?*/const String& SwRedline::GetAuthorString( USHORT nPos ) const
/*?*/{
/*?*/   for( SwRedlineData* pCur = pRedlineData; nPos && pCur->pNext; --nPos )
/*?*/       pCur = pCur->pNext;
/*?*/   ASSERT( !nPos, "Pos angabe ist zu gross" );
/*?*/   return SW_MOD()->GetRedlineAuthor(pCur->nAuthor);
/*?*/}

//STRIP001 const DateTime& SwRedline::GetTimeStamp( USHORT nPos ) const
//STRIP001 {
//STRIP001  for( SwRedlineData* pCur = pRedlineData; nPos && pCur->pNext; --nPos )
//STRIP001      pCur = pCur->pNext;
//STRIP001  ASSERT( !nPos, "Pos angabe ist zu gross" );
//STRIP001  return pCur->aStamp;
//STRIP001 }

//STRIP001 SwRedlineType SwRedline::GetRealType( USHORT nPos ) const
//STRIP001 {
//STRIP001  for( SwRedlineData* pCur = pRedlineData; nPos && pCur->pNext; --nPos )
//STRIP001      pCur = pCur->pNext;
//STRIP001  ASSERT( !nPos, "Pos angabe ist zu gross" );
//STRIP001  return pCur->eType;
//STRIP001 }

//STRIP001 const String& SwRedline::GetComment( USHORT nPos ) const
//STRIP001 {
//STRIP001  for( SwRedlineData* pCur = pRedlineData; nPos && pCur->pNext; --nPos )
//STRIP001      pCur = pCur->pNext;
//STRIP001  ASSERT( !nPos, "Pos angabe ist zu gross" );
//STRIP001  return pCur->sComment;
//STRIP001 }

/*N*/ int SwRedline::operator==( const SwRedline& rCmp ) const
/*N*/ {
/*N*/   return this == &rCmp;
/*N*/ }

/*N*/ int SwRedline::operator<( const SwRedline& rCmp ) const
/*N*/ {
/*N*/       BOOL nResult = FALSE;
/*N*/
/*N*/     if (*Start() < *rCmp.Start())
/*N*/         nResult = TRUE;
/*N*/     else if (*Start() == *rCmp.Start())
/*N*/         if (*End() < *rCmp.End())
/*N*/             nResult = TRUE;
/*N*/
/*N*/     return nResult;
/*N*/ }
}
