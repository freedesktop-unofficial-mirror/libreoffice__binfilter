/*************************************************************************
 *
 *  $RCSfile: sw_frmcrsr.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:35:41 $
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

#include "ndtxt.hxx"        // GetNode()
#include "pam.hxx"          // SwPosition
#include "frmtool.hxx"
#include "doc.hxx"
#include "viewopt.hxx"
#include "paratr.hxx"
#include "pagefrm.hxx"
#include "colfrm.hxx"
#include "txttypes.hxx"

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif

#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif

#ifndef _SVX_TSPTITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif

#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif

#ifndef _PORMULTI_HXX
#include <pormulti.hxx>     // SwMultiPortion
#endif

#include <unicode/ubidi.h>

#include "frmsh.hxx"
#include "txtcfg.hxx"
#include "txtfrm.hxx"       // SwTxtFrm
#include "inftxt.hxx"       // SwTxtSizeInfo
#include "itrtxt.hxx"       // SwTxtCursor
#include "crstate.hxx"      // SwTxtCursor
#include "viewsh.hxx"       // InvalidateWindows
#include "swfntcch.hxx"     // SwFontAccess
#include "flyfrm.hxx"

#if OSL_DEBUG_LEVEL > 1
#include "txtpaint.hxx"
#endif

#define MIN_OFFSET_STEP 10

/*
 * 1170-SurvivalKit: Wie gelangt man hinter das letzte Zeichen der Zeile.
 * - RightMargin verzichtet auf den Positionsausgleich mit -1
 * - GetCharRect liefert bei MV_RIGHTMARGIN ein GetEndCharRect
 * - GetEndCharRect setzt bRightMargin auf sal_True
 * - SwTxtCursor::bRightMargin wird per CharCrsrToLine auf sal_False gesetzt
 */

/*************************************************************************
 *                      GetAdjFrmAtPos()
 *************************************************************************/

/*N*/ SwTxtFrm *GetAdjFrmAtPos( SwTxtFrm *pFrm, const SwPosition &rPos,
/*N*/                           const sal_Bool bRightMargin, const sal_Bool bNoScroll = TRUE )
/*N*/ {
/*N*/   // 8810: vgl. 1170, RightMargin in der letzten Masterzeile...
/*N*/   const xub_StrLen nOffset = rPos.nContent.GetIndex();
/*N*/     SwTxtFrm *pFrmAtPos = pFrm;
/*N*/     if( !bNoScroll || pFrm->GetFollow() )
/*N*/     {
/*N*/         pFrmAtPos = pFrm->GetFrmAtPos( rPos );
/*N*/         if( nOffset < pFrmAtPos->GetOfst() &&
/*N*/             !pFrmAtPos->IsFollow() )
/*N*/         {
                DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/             xub_StrLen nNew = nOffset;
//STRIP001 /*?*/             if( nNew < MIN_OFFSET_STEP )
//STRIP001 /*?*/                 nNew = 0;
//STRIP001 /*?*/             else
//STRIP001 /*?*/                 nNew -= MIN_OFFSET_STEP;
//STRIP001 /*?*/             lcl_ChangeOffset( pFrmAtPos, nNew );
/*N*/         }
/*N*/     }
/*N*/   while( pFrm != pFrmAtPos )
/*N*/   {
/*?*/       pFrm = pFrmAtPos;
/*?*/       pFrm->GetFormatted();
/*?*/       pFrmAtPos = (SwTxtFrm*)pFrm->GetFrmAtPos( rPos );
/*N*/   }
/*N*/
/*N*/   if( nOffset && bRightMargin )
/*N*/   {
/*N*/         while( pFrmAtPos && pFrmAtPos->GetOfst() == nOffset &&
/*N*/                pFrmAtPos->IsFollow() )
/*N*/       {
/*?*/           pFrmAtPos->GetFormatted();
/*?*/           pFrmAtPos = pFrmAtPos->FindMaster();
/*N*/       }
/*N*/       ASSERT( pFrmAtPos, "+GetCharRect: no frame with my rightmargin" );
/*N*/   }
/*N*/   return pFrmAtPos ? pFrmAtPos : pFrm;
/*N*/ }

//STRIP001 sal_Bool lcl_ChangeOffset( SwTxtFrm* pFrm, xub_StrLen nNew )
//STRIP001 {
//STRIP001  // In Bereichen und ausserhalb von Flies wird nicht mehr gescrollt.
//STRIP001  ASSERT( !pFrm->IsFollow(), "Illegal Scrolling by Follow!" );
//STRIP001  if( pFrm->GetOfst() != nNew && !pFrm->IsInSct() )
//STRIP001  {
//STRIP001      SwFlyFrm *pFly = pFrm->FindFlyFrm();
//STRIP001      // Vorsicht, wenn z.B. bei einem spaltigen Rahmen die Groesse noch invalide ist,
//STRIP001      // duerfen wir nicht mal eben herumscrollen
//STRIP001      if ( ( pFly && pFly->IsValid() &&
//STRIP001           !pFly->GetNextLink() && !pFly->GetPrevLink() ) ||
//STRIP001           ( !pFly && pFrm->IsInTab() ) )
//STRIP001      {
//STRIP001          ViewShell* pVsh = pFrm->GetShell();
//STRIP001          if( pVsh )
//STRIP001          {
//STRIP001              if( pVsh->GetNext() != pVsh ||
//STRIP001                  ( pFrm->GetDrawObjs() && pFrm->GetDrawObjs()->Count() ) )
//STRIP001              {
//STRIP001                  if( !pFrm->GetOfst() )
//STRIP001                      return sal_False;
//STRIP001                  nNew = 0;
//STRIP001              }
//STRIP001              pFrm->SetOfst( nNew );
//STRIP001              pFrm->SetPara( 0 );
//STRIP001              pFrm->GetFormatted();
//STRIP001              if( pFrm->Frm().HasArea() )
//STRIP001              pFrm->GetShell()->InvalidateWindows( pFrm->Frm() );
//STRIP001              return sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

/*************************************************************************
 *                      GetFrmAtOfst(), GetFrmAtPos()
 *************************************************************************/

/*N*/ SwTxtFrm *SwTxtFrm::GetFrmAtOfst( const xub_StrLen nWhere )
/*N*/ {
/*N*/   SwTxtFrm *pRet = this;
/*N*/   while( pRet->HasFollow() && nWhere >= pRet->GetFollow()->GetOfst() )
/*?*/       pRet = pRet->GetFollow();
/*N*/   return pRet;
/*N*/ }

/*N*/ SwTxtFrm *SwTxtFrm::GetFrmAtPos( const SwPosition &rPos )
/*N*/ {
/*N*/   SwTxtFrm *pFoll = (SwTxtFrm*)this;
/*N*/   while( pFoll->GetFollow() )
/*N*/   {
/*N*/       if( rPos.nContent.GetIndex() > pFoll->GetFollow()->GetOfst() )
/*N*/           pFoll = pFoll->GetFollow();
/*N*/       else
/*N*/       {
/*N*/           if( rPos.nContent.GetIndex() == pFoll->GetFollow()->GetOfst()
/*N*/                && !SwTxtCursor::IsRightMargin() )
/*?*/                pFoll = pFoll->GetFollow();
/*N*/           else
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/   return pFoll;
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::GetCharRect()
 *************************************************************************/

/*
 * GetCharRect() findet die Characterzelle des Characters, dass
 * durch aPos beschrieben wird. GetCrsrOfst() findet den
 * umgekehrten Weg: Von einer Dokumentkoordinate zu einem Pam.
 * Beide sind virtuell in der Framebasisklasse und werden deshalb
 * immer angezogen.
 */

/*N*/ sal_Bool SwTxtFrm::GetCharRect( SwRect& rOrig, const SwPosition &rPos,
/*N*/                           SwCrsrMoveState *pCMS ) const
/*N*/ {
/*N*/     ASSERT( ! IsVertical() || ! IsSwapped(),"SwTxtFrm::GetCharRect with swapped frame" );
/*N*/
/*N*/     if( IsLocked() || IsHiddenNow() )
/*N*/       return sal_False;
/*N*/
/*N*/   //Erstmal den richtigen Frm finden, dabei muss beachtet werden, dass:
/*N*/   //- die gecachten Informationen verworfen sein koennen (GetPara() == 0)
/*N*/   //- das ein Follow gemeint sein kann
/*N*/   //- das die Kette der Follows dynamisch waechst; der in den wir
/*N*/   //  schliesslich gelangen muss aber Formatiert sein.
/*N*/
/*N*/   // opt: reading ahead erspart uns ein GetAdjFrmAtPos
/*N*/   const sal_Bool bRightMargin = pCMS && ( MV_RIGHTMARGIN == pCMS->eState );
/*N*/     const sal_Bool bNoScroll = pCMS && pCMS->bNoScroll;
/*N*/     SwTxtFrm *pFrm = GetAdjFrmAtPos( (SwTxtFrm*)this, rPos, bRightMargin,
/*N*/                                      bNoScroll );
/*N*/   pFrm->GetFormatted();
/*N*/   const SwFrm* pTmpFrm = (SwFrm*)pFrm->GetUpper();
/*N*/
/*N*/     SWRECTFN ( pFrm )
/*N*/     const SwTwips nUpperMaxY = (pTmpFrm->*fnRect->fnGetPrtBottom)();
/*N*/     const SwTwips nFrmMaxY = (pFrm->*fnRect->fnGetPrtBottom)();
/*N*/
/*N*/     // nMaxY is an absolute value
/*N*/     SwTwips nMaxY = bVert ?
/*N*/                     Max( nFrmMaxY, nUpperMaxY ) :
/*N*/                     Min( nFrmMaxY, nUpperMaxY );
/*N*/
/*N*/     sal_Bool bRet = sal_False;
/*N*/
/*N*/     if ( pFrm->IsEmpty() || ! (pFrm->Prt().*fnRect->fnGetHeight)() )
/*N*/   {
/*N*/       Point aPnt1 = pFrm->Frm().Pos() + pFrm->Prt().Pos();
/*N*/       SwTxtNode* pTxtNd = ((SwTxtFrm*)this)->GetTxtNode();
/*N*/       short nFirstOffset;
/*N*/       pTxtNd->GetFirstLineOfsWithNum( nFirstOffset );
/*N*/
/*N*/         Point aPnt2;
/*N*/         if ( bVert )
/*N*/         {
/*?*/             if( nFirstOffset > 0 )
/*?*/                 aPnt1.Y() += nFirstOffset;
/*?*/
/*?*/             if ( aPnt1.X() < nMaxY )
/*?*/                 aPnt1.X() = nMaxY;
/*?*/             aPnt2.X() = aPnt1.X() + pFrm->Prt().Width();
/*?*/             aPnt2.Y() = aPnt1.Y();
/*?*/             if( aPnt2.X() < nMaxY )
/*?*/                 aPnt2.X() = nMaxY;
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/             if( nFirstOffset > 0 )
/*N*/                 aPnt1.X() += nFirstOffset;
/*N*/
/*N*/             if( aPnt1.Y() > nMaxY )
/*N*/                 aPnt1.Y() = nMaxY;
/*N*/             aPnt2.X() = aPnt1.X();
/*N*/             aPnt2.Y() = aPnt1.Y() + pFrm->Prt().Height();
/*N*/             if( aPnt2.Y() > nMaxY )
/*N*/                 aPnt2.Y() = nMaxY;
/*N*/         }
/*N*/
/*N*/         rOrig = SwRect( aPnt1, aPnt2 );
/*N*/
/*N*/         if ( pCMS )
/*N*/       {
/*N*/           pCMS->aRealHeight.X() = 0;
/*N*/             pCMS->aRealHeight.Y() = bVert ? -rOrig.Width() : rOrig.Height();
/*N*/       }
/*N*/
/*N*/ #ifdef BIDI
/*N*/         if ( pFrm->IsRightToLeft() )
                {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/             pFrm->SwitchLTRtoRTL( rOrig );
/*N*/ #endif
/*N*/
/*N*/         bRet = sal_True;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if( !pFrm->HasPara() )
/*N*/           return sal_False;
/*N*/
/*N*/         SwFrmSwapper aSwapper( pFrm, sal_True );
/*N*/         if ( bVert )
                {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/             nMaxY = pFrm->SwitchVerticalToHorizontal( nMaxY );
/*N*/
/*N*/         sal_Bool bGoOn = sal_True;
/*N*/       xub_StrLen nOffset = rPos.nContent.GetIndex();
/*N*/       xub_StrLen nNextOfst;
/*N*/
/*N*/       do
/*N*/       {
/*N*/           {
/*N*/               SwTxtSizeInfo aInf( pFrm );
/*N*/               SwTxtCursor  aLine( pFrm, &aInf );
/*N*/               nNextOfst = aLine.GetEnd();
/*N*/               // Siehe Kommentar in AdjustFrm
/*N*/               // 1170: das letzte Zeichen der Zeile mitnehmen?
/*N*/               bRet = bRightMargin ? aLine.GetEndCharRect( &rOrig, nOffset, pCMS, nMaxY )
/*N*/                               : aLine.GetCharRect( &rOrig, nOffset, pCMS, nMaxY );
/*N*/           }
/*N*/
/*N*/ #ifdef BIDI
/*N*/             if ( pFrm->IsRightToLeft() )
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/                 pFrm->SwitchLTRtoRTL( rOrig );
/*N*/ #endif
/*N*/             if ( bVert )
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/                 pFrm->SwitchHorizontalToVertical( rOrig );
/*N*/
/*N*/             if( pFrm->IsUndersized() && pCMS && !pFrm->GetNext() &&
/*N*/                 (rOrig.*fnRect->fnGetBottom)() == nUpperMaxY &&
/*N*/                 pFrm->GetOfst() < nOffset &&
/*N*/                 !pFrm->IsFollow() && !bNoScroll &&
/*N*/                 pFrm->GetTxtNode()->GetTxt().Len() != nNextOfst )
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/              bGoOn = lcl_ChangeOffset( pFrm, nNextOfst );
/*N*/           else
/*N*/               bGoOn = sal_False;
/*N*/       } while ( bGoOn );
/*N*/
/*N*/         if ( pCMS )
/*N*/         {
/*N*/ #ifdef BIDI
/*N*/             if ( pFrm->IsRightToLeft() )
/*N*/             {
                    DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/                  if( pCMS->b2Lines && pCMS->p2Lines)
//STRIP001 /*?*/                  {
//STRIP001 /*?*/                      pFrm->SwitchLTRtoRTL( pCMS->p2Lines->aLine );
//STRIP001 /*?*/                      pFrm->SwitchLTRtoRTL( pCMS->p2Lines->aPortion );
//STRIP001 /*?*/                  }
/*N*/             }
/*N*/ #endif
/*N*/
/*N*/             if ( bVert )
/*N*/             {
/*?*/                 if ( pCMS->bRealHeight )
/*?*/                 {
/*?*/                     pCMS->aRealHeight.Y() = -pCMS->aRealHeight.Y();
/*?*/                     if ( pCMS->aRealHeight.Y() < 0 )
/*?*/                     {
/*?*/                         // writing direction is from top to bottom
/*?*/                         pCMS->aRealHeight.X() =  ( rOrig.Width() -
/*?*/                                                     pCMS->aRealHeight.X() +
/*?*/                                                     pCMS->aRealHeight.Y() );
/*?*/                     }
/*?*/                 }
/*?*/                 if( pCMS->b2Lines && pCMS->p2Lines)
/*?*/                 {
                        DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/                     pFrm->SwitchHorizontalToVertical( pCMS->p2Lines->aLine );
//STRIP001 /*?*/                     pFrm->SwitchHorizontalToVertical( pCMS->p2Lines->aPortion );
/*?*/                 }
/*N*/             }
/*N*/
/*N*/         }
/*N*/     }
/*N*/     if( bRet )
/*N*/     {
/*N*/         SwPageFrm *pPage = pFrm->FindPageFrm();
/*N*/         ASSERT( pPage, "Text esaped from page?" );
/*N*/         const SwTwips nOrigTop = (rOrig.*fnRect->fnGetTop)();
/*N*/         const SwTwips nPageTop = (pPage->Frm().*fnRect->fnGetTop)();
/*N*/         const SwTwips nPageBott = (pPage->Frm().*fnRect->fnGetBottom)();
/*N*/
/*N*/         // Following situation: if the frame is in an invalid sectionframe,
/*N*/         // it's possible that the frame is outside the page. If we restrict
/*N*/         // the cursor position to the page area, we enforce the formatting
/*N*/         // of the page, of the section frame and the frame himself.
/*N*/         if( (*fnRect->fnYDiff)( nPageTop, nOrigTop ) > 0 )
/*N*/             (rOrig.*fnRect->fnSetTop)( nPageTop );
/*N*/
/*N*/         if ( (*fnRect->fnYDiff)( nOrigTop, nPageBott ) > 0 )
/*?*/             (rOrig.*fnRect->fnSetTop)( nPageBott );
/*N*/     }
/*N*/
/*N*/     return bRet;
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::GetAutoPos()
 *************************************************************************/

/*
 * GetAutoPos() findet die Characterzelle des Characters, dass
 * durch aPos beschrieben wird und wird von autopositionierten Rahmen genutzt.
 */

/*N*/ sal_Bool SwTxtFrm::GetAutoPos( SwRect& rOrig, const SwPosition &rPos ) const
/*N*/ {
/*N*/   if( IsHiddenNow() )
/*N*/       return sal_False;
/*N*/
/*N*/   xub_StrLen nOffset = rPos.nContent.GetIndex();
/*N*/   SwTxtFrm *pFrm = ((SwTxtFrm*)this)->GetFrmAtOfst( nOffset );
/*N*/
/*N*/   pFrm->GetFormatted();
/*N*/   const SwFrm* pTmpFrm = (SwFrm*)pFrm->GetUpper();
/*N*/
/*N*/     SWRECTFN( pTmpFrm )
/*N*/     SwTwips nUpperMaxY = (pTmpFrm->*fnRect->fnGetPrtBottom)();
/*N*/
/*N*/     // nMaxY is in absolute value
/*N*/     SwTwips nMaxY = bVert ?
/*N*/                     Max( (pFrm->*fnRect->fnGetPrtBottom)(), nUpperMaxY ) :
/*N*/                     Min( (pFrm->*fnRect->fnGetPrtBottom)(), nUpperMaxY );
/*N*/
/*N*/     if ( pFrm->IsEmpty() || ! (pFrm->Prt().*fnRect->fnGetHeight)() )
/*N*/   {
/*N*/       Point aPnt1 = pFrm->Frm().Pos() + pFrm->Prt().Pos();
/*N*/         Point aPnt2;
/*N*/         if ( bVert )
/*N*/         {
/*?*/             if ( aPnt1.X() < nMaxY )
/*?*/                 aPnt1.X() = nMaxY;
/*?*/             aPnt2.X() = aPnt1.X() + pFrm->Prt().Width();
/*?*/             aPnt2.Y() = aPnt1.Y();
/*?*/             if( aPnt2.X() < nMaxY )
/*?*/                 aPnt2.X() = nMaxY;
/*?*/         }
/*?*/         else
/*?*/         {
/*N*/             if( aPnt1.Y() > nMaxY )
/*N*/                 aPnt1.Y() = nMaxY;
/*N*/             aPnt2.X() = aPnt1.X();
/*N*/             aPnt2.Y() = aPnt1.Y() + pFrm->Prt().Height();
/*N*/             if( aPnt2.Y() > nMaxY )
/*N*/                 aPnt2.Y() = nMaxY;
/*N*/         }
/*N*/       rOrig = SwRect( aPnt1, aPnt2 );
/*N*/       return sal_True;
/*N*/   }
/*N*/   else
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if( !pFrm->HasPara() )
//STRIP001 /*?*/            return sal_False;
//STRIP001 /*?*/
//STRIP001 /*?*/         SwFrmSwapper aSwapper( pFrm, sal_True );
//STRIP001 /*?*/         if ( bVert )
//STRIP001 /*?*/             nMaxY = pFrm->SwitchVerticalToHorizontal( nMaxY );
//STRIP001 /*?*/
//STRIP001 /*?*/         SwTxtSizeInfo aInf( pFrm );
//STRIP001 /*?*/         SwTxtCursor aLine( pFrm, &aInf );
//STRIP001 /*?*/         SwCrsrMoveState aTmpState( MV_SETONLYTEXT );
//STRIP001 /*?*/         aTmpState.bRealHeight = TRUE;
//STRIP001 /*?*/         if( aLine.GetCharRect( &rOrig, nOffset, &aTmpState, nMaxY ) )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             if( aTmpState.aRealHeight.X() >= 0 )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 rOrig.Pos().Y() += aTmpState.aRealHeight.X();
//STRIP001 /*?*/                 rOrig.Height( aTmpState.aRealHeight.Y() );
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/ #ifdef BIDI
//STRIP001 /*?*/             if ( pFrm->IsRightToLeft() )
//STRIP001 /*?*/                 pFrm->SwitchLTRtoRTL( rOrig );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( bVert )
//STRIP001 /*?*/                 pFrm->SwitchHorizontalToVertical( rOrig );
//STRIP001 /*?*/
//STRIP001 /*?*/             return TRUE;
//STRIP001 /*?*/         }
//STRIP001 /*?*/         return FALSE;
/*N*/   }
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::_GetCrsrOfst()
 *************************************************************************/

// Minimaler Abstand von nichtleeren Zeilen etwas weniger als 2 cm
#define FILL_MIN_DIST 1100

struct SwFillData
{
    SwRect aFrm;
    const SwCrsrMoveState *pCMS;
    SwPosition* pPos;
    const Point& rPoint;
    SwTwips nLineWidth;
    sal_Bool bFirstLine : 1;
    sal_Bool bInner     : 1;
    sal_Bool bColumn    : 1;
    sal_Bool bEmpty     : 1;
    SwFillData( const SwCrsrMoveState *pC, SwPosition* pP, const SwRect& rR,
        const Point& rPt ) : aFrm( rR ), pCMS( pC ), pPos( pP ), rPoint( rPt ),
        nLineWidth( 0 ), bFirstLine( sal_True ), bInner( sal_False ), bColumn( sal_False ),
        bEmpty( sal_True ){}
    const SwFillMode Mode() const { return pCMS->pFill->eMode; }
    const long X() const { return rPoint.X(); }
    const long Y() const { return rPoint.Y(); }
    const long Left() const { return aFrm.Left(); }
    const long Right() const { return aFrm.Right(); }
    const long Bottom() const { return aFrm.Bottom(); }
    SwRect& Frm() { return aFrm; }
    SwFillCrsrPos &Fill() const { return *pCMS->pFill; }
    void SetTab( MSHORT nNew ) { pCMS->pFill->nTabCnt = nNew; }
    void SetSpace( MSHORT nNew ) { pCMS->pFill->nSpaceCnt = nNew; }
    void SetOrient( const SwHoriOrient eNew ){ pCMS->pFill->eOrient = eNew; }
};

/*N*/ sal_Bool SwTxtFrm::_GetCrsrOfst(SwPosition* pPos, const Point& rPoint,
/*N*/                   const sal_Bool bChgFrm, const SwCrsrMoveState* pCMS ) const
/*N*/ {
/*N*/   // 8804: _GetCrsrOfst wird vom GetCrsrOfst und GetKeyCrsrOfst gerufen.
/*N*/   // In keinem Fall nur ein return sal_False.
/*N*/
/*N*/   if( IsLocked() || IsHiddenNow() )
/*N*/       return sal_False;
/*N*/
/*N*/   ((SwTxtFrm*)this)->GetFormatted();
/*N*/
/*N*/     Point aOldPoint( rPoint );
/*N*/
/*N*/     if ( IsVertical() )
/*N*/     {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         SwitchVerticalToHorizontal( (Point&)rPoint );
//STRIP001 /*?*/         ((SwTxtFrm*)this)->SwapWidthAndHeight();
/*N*/     }
/*N*/
/*N*/ #ifdef BIDI
/*N*/     if ( IsRightToLeft() )
/*?*/         {DBG_ASSERT(0, "STRIP"); }//STRIP001 SwitchRTLtoLTR( (Point&)rPoint );
/*N*/ #endif
/*N*/
/*N*/     SwFillData *pFillData = ( pCMS && pCMS->pFill ) ?
/*N*/                         new SwFillData( pCMS, pPos, Frm(), rPoint ) : NULL;
/*N*/
/*N*/     if ( IsEmpty() )
/*N*/   {
/*N*/       SwTxtNode* pTxtNd = ((SwTxtFrm*)this)->GetTxtNode();
/*N*/       pPos->nNode = *pTxtNd;
/*N*/       pPos->nContent.Assign( pTxtNd, 0 );
/*N*/       if( pCMS && pCMS->bFieldInfo )
/*N*/       {
/*?*/           SwTwips nDiff = rPoint.X() - Frm().Left() - Prt().Left();
/*?*/           if( nDiff > 50 || nDiff < 0 )
/*?*/               ((SwCrsrMoveState*)pCMS)->bPosCorr = sal_True;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwTxtSizeInfo aInf( (SwTxtFrm*)this );
/*N*/       SwTxtCursor  aLine( ((SwTxtFrm*)this), &aInf );
/*N*/
/*N*/       // Siehe Kommentar in AdjustFrm()
/*N*/       SwTwips nMaxY = Frm().Top() + Prt().Top() + Prt().Height();
/*N*/       aLine.TwipsToLine( rPoint.Y() );
/*N*/       while( aLine.Y() + aLine.GetLineHeight() > nMaxY )
/*N*/       {
/*?*/           DBG_LOOP;
/*?*/           if( !aLine.Prev() )
/*?*/               break;
/*N*/       }
/*N*/
/*N*/       if( aLine.GetDropLines() >= aLine.GetLineNr() && 1 != aLine.GetLineNr()
/*N*/           && rPoint.X() < aLine.FirstLeft() + aLine.GetDropLeft() )
/*N*/           while( aLine.GetLineNr() > 1 )
/*N*/               aLine.Prev();
/*N*/
/*N*/         xub_StrLen nOffset = aLine.GetCrsrOfst( pPos, rPoint, bChgFrm, pCMS );
/*N*/
/*N*/         if( pCMS && pCMS->eState == MV_NONE && aLine.GetEnd() == nOffset )
/*?*/             ((SwCrsrMoveState*)pCMS)->eState = MV_RIGHTMARGIN;
/*N*/
/*N*/   // 6776: pPos ist ein reiner IN-Parameter, der nicht ausgewertet werden darf.
/*N*/   // Das pIter->GetCrsrOfst returnt aus einer Verschachtelung mit STRING_LEN.
/*N*/   // Wenn SwTxtIter::GetCrsrOfst von sich aus weitere GetCrsrOfst
/*N*/   // ruft, so aendert sich nNode der Position. In solchen Faellen
/*N*/   // darf pPos nicht berechnet werden.
/*N*/       if( STRING_LEN != nOffset )
/*N*/       {
/*N*/ #ifdef USED
/*N*/           // 8626: bei Up/Down darf diese Zeile nicht verlassen werden.
/*N*/           if( pCMS && MV_UPDOWN == pCMS->eState )
/*N*/           {
/*N*/               const xub_StrLen nEnd = aLine.GetEnd();
/*N*/               if( nOffset >= nEnd && nEnd )
/*N*/               {
/*N*/                   // Man muss hinter das letzte Zeichen kommen duerfen?!
/*N*/                   nOffset = nEnd - 1;                 // UnitUp-Korrektur
/*N*/               }
/*N*/               else
/*N*/                   if( nOffset < aLine.GetStart() )
/*N*/                       nOffset = aLine.GetStart(); // UnitDown-Korrektur
/*N*/           }
/*N*/ #endif
/*N*/           SwTxtNode* pTxtNd = ((SwTxtFrm*)this)->GetTxtNode();
/*N*/           pPos->nNode = *pTxtNd;
/*N*/           pPos->nContent.Assign( pTxtNd, nOffset );
/*N*/           if( pFillData )
/*N*/           {
/*N*/               if( pTxtNd->GetTxt().Len() > nOffset ||
/*N*/                   rPoint.Y() < Frm().Top() )
/*N*/                   pFillData->bInner = sal_True;
/*N*/               pFillData->bFirstLine = aLine.GetLineNr() < 2;
/*N*/               if( pTxtNd->GetTxt().Len() )
/*N*/               {
/*?*/                   pFillData->bEmpty = sal_False;
/*?*/                   pFillData->nLineWidth = aLine.GetCurr()->Width();
/*N*/                 }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/     sal_Bool bChgFillData = sal_False;
/*N*/     if( pFillData && FindPageFrm()->Frm().IsInside( aOldPoint ) )
/*N*/     {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        FillCrsrPos( *pFillData );
//STRIP001 /*?*/         bChgFillData = sal_True;
/*N*/     }
/*N*/
/*N*/     if ( IsVertical() )
/*N*/     {
/*N*/         if ( bChgFillData )
/*N*/             SwitchHorizontalToVertical( pFillData->Fill().aCrsr.Pos() );
/*N*/         ((SwTxtFrm*)this)->SwapWidthAndHeight();
/*N*/     }
/*N*/
/*N*/     if ( IsRightToLeft() && bChgFillData )
/*N*/     {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/             SwitchLTRtoRTL( pFillData->Fill().aCrsr.Pos() );
//STRIP001 /*?*/             const SwHoriOrient eOrient = pFillData->pCMS->pFill->eOrient;
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( HORI_LEFT == eOrient )
//STRIP001 /*?*/                 pFillData->SetOrient( HORI_RIGHT );
//STRIP001 /*?*/             else if ( HORI_RIGHT == eOrient )
//STRIP001 /*?*/                 pFillData->SetOrient( HORI_LEFT );
/*N*/     }
/*N*/
/*N*/     (Point&)rPoint = aOldPoint;
/*N*/     delete pFillData;
/*N*/
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *                 virtual SwTxtFrm::GetCrsrOfst()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFrm::GetCrsrOfst(SwPosition* pPos, Point& rPoint,
/*N*/                           const SwCrsrMoveState* pCMS ) const
/*N*/ {
/*N*/   MSHORT nChgFrm = 2;
/*N*/   if( pCMS )
/*N*/   {
/*N*/       if( MV_UPDOWN == pCMS->eState )
/*N*/           nChgFrm = 0;
/*N*/       else if( MV_SETONLYTEXT == pCMS->eState ||
/*N*/                MV_TBLSEL == pCMS->eState )
/*N*/           nChgFrm = 1;
/*N*/   }
/*N*/     return _GetCrsrOfst( pPos, rPoint, nChgFrm != 0, pCMS );
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::LeftMargin()
 *************************************************************************/

/*
 * Layout-orientierte Cursorbewegungen
 */

/*
 * an den Zeilenanfang
 */

//STRIP001 sal_Bool SwTxtFrm::LeftMargin(SwPaM *pPam) const
//STRIP001 {
//STRIP001  if( ((const SwNode*)pPam->GetNode()) != GetNode() )
//STRIP001      pPam->GetPoint()->nNode = *((SwTxtFrm*)this)->GetTxtNode();
//STRIP001
//STRIP001  SwTxtFrm *pFrm = GetAdjFrmAtPos( (SwTxtFrm*)this, *pPam->GetPoint(),
//STRIP001                                   SwTxtCursor::IsRightMargin() );
//STRIP001  pFrm->GetFormatted();
//STRIP001  xub_StrLen nIndx;
//STRIP001  if ( pFrm->IsEmpty() )
//STRIP001      nIndx = 0;
//STRIP001  else
//STRIP001  {
//STRIP001      SwTxtSizeInfo aInf( pFrm );
//STRIP001      SwTxtCursor  aLine( pFrm, &aInf );
//STRIP001
//STRIP001      aLine.CharCrsrToLine(pPam->GetPoint()->nContent.GetIndex());
//STRIP001      nIndx = aLine.GetStart();
//STRIP001      if( pFrm->GetOfst() && !pFrm->IsFollow() && !aLine.GetPrev() )
//STRIP001      {
//STRIP001          lcl_ChangeOffset( pFrm, 0 );
//STRIP001          nIndx = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  pPam->GetPoint()->nContent = SwIndex( pFrm->GetTxtNode(), nIndx );
//STRIP001  SwTxtCursor::SetRightMargin( sal_False );
//STRIP001  return sal_True;
//STRIP001 }

/*************************************************************************
 *                      SwTxtFrm::RightMargin()
 *************************************************************************/

/*
 * An das Zeilenende:Das ist die Position vor dem letzten
 * Character in der Zeile. Ausnahme: In der letzten Zeile soll
 * der Cursor auch hinter dem letzten Character stehen koennen,
 * um Text anhaengen zu koennen.
 *
 */

//STRIP001 sal_Bool SwTxtFrm::RightMargin(SwPaM *pPam, sal_Bool bAPI) const
//STRIP001 {
//STRIP001  if( ((const SwNode*)pPam->GetNode()) != GetNode() )
//STRIP001      pPam->GetPoint()->nNode = *((SwTxtFrm*)this)->GetTxtNode();
//STRIP001
//STRIP001  SwTxtFrm *pFrm = GetAdjFrmAtPos( (SwTxtFrm*)this, *pPam->GetPoint(),
//STRIP001                                   SwTxtCursor::IsRightMargin() );
//STRIP001  pFrm->GetFormatted();
//STRIP001  xub_StrLen nRightMargin;
//STRIP001  if ( IsEmpty() )
//STRIP001      nRightMargin = 0;
//STRIP001  else
//STRIP001  {
//STRIP001      SwTxtSizeInfo aInf( pFrm );
//STRIP001      SwTxtCursor  aLine( pFrm, &aInf );
//STRIP001
//STRIP001      aLine.CharCrsrToLine(pPam->GetPoint()->nContent.GetIndex());
//STRIP001      nRightMargin = aLine.GetStart() + aLine.GetCurr()->GetLen();
//STRIP001
//STRIP001      // Harte Zeilenumbrueche lassen wir hinter uns.
//STRIP001      if( aLine.GetCurr()->GetLen() &&
//STRIP001          CH_BREAK == aInf.GetTxt().GetChar( nRightMargin - 1 ) )
//STRIP001          --nRightMargin;
//STRIP001      if( !bAPI && (aLine.GetNext() || pFrm->GetFollow()) )
//STRIP001      {
//STRIP001          while( nRightMargin > aLine.GetStart() &&
//STRIP001              ' ' == aInf.GetTxt().GetChar( nRightMargin - 1 ) )
//STRIP001              --nRightMargin;
//STRIP001      }
//STRIP001  }
//STRIP001  pPam->GetPoint()->nContent = SwIndex( pFrm->GetTxtNode(), nRightMargin );
//STRIP001  SwTxtCursor::SetRightMargin( !bAPI );
//STRIP001  return sal_True;
//STRIP001 }

/*************************************************************************
 *                      SwTxtFrm::_UnitUp()
 *************************************************************************/

//Die beiden folgenden Methoden versuchen zunaechst den Crsr in die
//nachste/folgende Zeile zu setzen. Gibt es im Frame keine vorhergehende/
//folgende Zeile, so wird der Aufruf an die Basisklasse weitergeleitet.
//Die Horizontale Ausrichtung des Crsr wird hinterher von der CrsrShell
//vorgenommen.

class SwSetToRightMargin
{
    sal_Bool bRight;
public:
    inline SwSetToRightMargin() : bRight( sal_False ) { }
    inline ~SwSetToRightMargin() { SwTxtCursor::SetRightMargin( bRight ); }
    inline void SetRight( const sal_Bool bNew ) { bRight = bNew; }
};

//STRIP001 sal_Bool SwTxtFrm::_UnitUp( SwPaM *pPam, const SwTwips nOffset,
//STRIP001                          sal_Bool bSetInReadOnly ) const
//STRIP001 {
//STRIP001  // 8626: Im Notfall den RightMargin setzen.
//STRIP001  SwSetToRightMargin aSet;
//STRIP001
//STRIP001  if( IsInTab() &&
//STRIP001      pPam->GetNode( sal_True )->StartOfSectionNode() !=
//STRIP001      pPam->GetNode( sal_False )->StartOfSectionNode() )
//STRIP001  {
//STRIP001      //Wenn der PaM in unterschiedlichen Boxen sitzt, so handelt es sich um
//STRIP001      //eine Tabellenselektion; diese wird von der Basisklasse abgearbeitet.
//STRIP001      return SwCntntFrm::UnitUp( pPam, nOffset, bSetInReadOnly );
//STRIP001  }
//STRIP001
//STRIP001  ((SwTxtFrm*)this)->GetFormatted();
//STRIP001  const xub_StrLen nPos = pPam->GetPoint()->nContent.GetIndex();
//STRIP001  SwRect aCharBox;
//STRIP001
//STRIP001  if( !IsEmpty() && !IsHiddenNow() )
//STRIP001  {
//STRIP001      xub_StrLen nFormat = STRING_LEN;
//STRIP001      do
//STRIP001      {
//STRIP001          if( nFormat != STRING_LEN && !IsFollow() )
//STRIP001              lcl_ChangeOffset( ((SwTxtFrm*)this), nFormat );
//STRIP001
//STRIP001          SwTxtSizeInfo aInf( (SwTxtFrm*)this );
//STRIP001          SwTxtCursor  aLine( ((SwTxtFrm*)this), &aInf );
//STRIP001
//STRIP001          // 8116: Flys ohne Umlauf und IsDummy(); hier wegoptimiert
//STRIP001          if( nPos )
//STRIP001              aLine.CharCrsrToLine( nPos );
//STRIP001          else
//STRIP001              aLine.Top();
//STRIP001
//STRIP001          const SwLineLayout *pPrevLine = aLine.GetPrevLine();
//STRIP001             const xub_StrLen nStart = aLine.GetStart();
//STRIP001             SwRect aCharBox;
//STRIP001             aLine.GetCharRect( &aCharBox, nPos );
//STRIP001
//STRIP001             sal_Bool bSecondOfDouble = ( aInf.IsMulti() && ! aInf.IsFirstMulti() );
//STRIP001             sal_Bool bPrevLine = ( pPrevLine && pPrevLine != aLine.GetCurr() );
//STRIP001
//STRIP001             if( !pPrevLine && !bSecondOfDouble && GetOfst() && !IsFollow() )
//STRIP001          {
//STRIP001              nFormat = GetOfst();
//STRIP001              xub_StrLen nDiff = aLine.GetLength();
//STRIP001              if( !nDiff )
//STRIP001                  nDiff = MIN_OFFSET_STEP;
//STRIP001              if( nFormat > nDiff )
//STRIP001                  nFormat -= nDiff;
//STRIP001              else
//STRIP001                  nFormat = 0;
//STRIP001              continue;
//STRIP001          }
//STRIP001
//STRIP001             // we select the target line for the cursor, in case we are in a
//STRIP001             // double line portion, prev line = curr line
//STRIP001             if( bPrevLine && !bSecondOfDouble )
//STRIP001             {
//STRIP001                 aLine.PrevLine();
//STRIP001                 while ( aLine.GetStart() == nStart &&
//STRIP001                         0 != ( pPrevLine = aLine.GetPrevLine() ) &&
//STRIP001                         pPrevLine != aLine.GetCurr() )
//STRIP001                     aLine.PrevLine();
//STRIP001             }
//STRIP001
//STRIP001             if ( bPrevLine || bSecondOfDouble )
//STRIP001             {
//STRIP001                 aCharBox.SSize().Width() /= 2;
//STRIP001                 aCharBox.Pos().X() = aCharBox.Pos().X() - 150;
//STRIP001
//STRIP001              // siehe Kommentar in SwTxtFrm::GetCrsrOfst()
//STRIP001 #ifndef PRODUCT
//STRIP001                 const ULONG nOldNode = pPam->GetPoint()->nNode.GetIndex();
//STRIP001 #endif
//STRIP001              // Der Node soll nicht gewechselt werden
//STRIP001              xub_StrLen nOfst = aLine.GetCrsrOfst( pPam->GetPoint(),
//STRIP001                                                  aCharBox.Pos(), sal_False );
//STRIP001              ASSERT( nOldNode == pPam->GetPoint()->nNode.GetIndex(),
//STRIP001                      "SwTxtFrm::UnitUp: illegal node change" )
//STRIP001
//STRIP001              // 7684: Wir stellen sicher, dass wir uns nach oben bewegen.
//STRIP001                 if( nOfst >= nStart && nStart && !bSecondOfDouble )
//STRIP001              {
//STRIP001                  // nOfst = nStart - 1;
//STRIP001                  nOfst = nStart;
//STRIP001                  aSet.SetRight( sal_True );
//STRIP001              }
//STRIP001              pPam->GetPoint()->nContent =
//STRIP001                    SwIndex( ((SwTxtFrm*)this)->GetTxtNode(), nOfst );
//STRIP001              return sal_True;
//STRIP001          }
//STRIP001
//STRIP001             if ( IsFollow() )
//STRIP001          {
//STRIP001              aLine.GetCharRect( &aCharBox, nPos );
//STRIP001              aCharBox.SSize().Width() /= 2;
//STRIP001          }
//STRIP001          break;
//STRIP001      } while ( sal_True );
//STRIP001  }
//STRIP001  /* Wenn this ein Follow ist und ein Prev miszlang, so
//STRIP001   * muessen wir in die letzte Zeile des Master ... und der sind wir.
//STRIP001   * Oder wir sind ein Follow mit Follow, dann muessen wir uns den
//STRIP001   * Master extra besorgen...
//STRIP001   */
//STRIP001  if ( IsFollow() )
//STRIP001  {
//STRIP001      const SwTxtFrm *pPrev = FindMaster();
//STRIP001      xub_StrLen nOffs = GetOfst();
//STRIP001      if( pPrev )
//STRIP001      {
//STRIP001          ViewShell *pSh = GetShell();
//STRIP001          sal_Bool bProtectedAllowed = pSh && pSh->GetViewOptions()->IsCursorInProtectedArea();
//STRIP001          const SwTxtFrm *pPrevPrev = pPrev;
//STRIP001          // Hier werden geschuetzte Frames und Frame ohne Inhalt ausgelassen
//STRIP001          while( pPrevPrev && ( pPrevPrev->GetOfst() == nOffs ||
//STRIP001                 ( !bProtectedAllowed && pPrevPrev->IsProtected() ) ) )
//STRIP001          {
//STRIP001              pPrev = pPrevPrev;
//STRIP001              nOffs = pPrev->GetOfst();
//STRIP001              if ( pPrevPrev->IsFollow() )
//STRIP001                  pPrevPrev = pPrev->FindMaster();
//STRIP001              else
//STRIP001                  pPrevPrev = NULL;
//STRIP001          }
//STRIP001          if ( !pPrevPrev )
//STRIP001              return pPrev->SwCntntFrm::UnitUp( pPam, nOffset, bSetInReadOnly );
//STRIP001          aCharBox.Pos().Y() = pPrevPrev->Frm().Bottom() - 1;
//STRIP001          return pPrevPrev->GetKeyCrsrOfst( pPam->GetPoint(), aCharBox.Pos() );
//STRIP001      }
//STRIP001  }
//STRIP001  return SwCntntFrm::UnitUp( pPam, nOffset, bSetInReadOnly );
//STRIP001 }

//
// Used for Bidi. nPos is the logical position in the string, bLeft indicates
// if left arrow or right arrow was pressed. The return values are:
// nPos: the new visual position
// bLeft: whether the break iterator has to add or subtract from the
//          current position
//STRIP001 void lcl_VisualMoveRecursion( const SwLineLayout& rCurrLine, xub_StrLen nIdx,
//STRIP001                               xub_StrLen& nPos, sal_Bool& bRight,
//STRIP001                               BYTE& nCrsrLevel, BYTE nDefaultDir )
//STRIP001 {
//STRIP001     const SwLinePortion* pPor = rCurrLine.GetFirstPortion();
//STRIP001     const SwLinePortion* pLast = 0;
//STRIP001
//STRIP001     // what's the current portion
//STRIP001     while ( pPor && nIdx + pPor->GetLen() <= nPos )
//STRIP001     {
//STRIP001         nIdx += pPor->GetLen();
//STRIP001         pLast = pPor;
//STRIP001         pPor = pPor->GetPortion();
//STRIP001     }
//STRIP001
//STRIP001     if ( bRight )
//STRIP001     {
//STRIP001         sal_Bool bRecurse = pPor && pPor->IsMultiPortion() &&
//STRIP001                            ((SwMultiPortion*)pPor)->IsBidi();
//STRIP001
//STRIP001         // 1. special case: at beginning of bidi portion
//STRIP001         if ( bRecurse && nIdx == nPos )
//STRIP001         {
//STRIP001             nPos += pPor->GetLen();
//STRIP001
//STRIP001             // leave bidi portion
//STRIP001             if ( nCrsrLevel != nDefaultDir )
//STRIP001             {
//STRIP001                 bRecurse = sal_False;
//STRIP001             }
//STRIP001             else
//STRIP001                 // special case:
//STRIP001                 // buffer: abcXYZ123 in LTR paragraph
//STRIP001                 // view:   abc123ZYX
//STRIP001                 // cursor is between c and X in the buffer and cursor level = 0
//STRIP001                 nCrsrLevel++;
//STRIP001         }
//STRIP001
//STRIP001         // 2. special case: at beginning of portion after bidi portion
//STRIP001         else if ( pLast && pLast->IsMultiPortion() &&
//STRIP001                  ((SwMultiPortion*)pLast)->IsBidi() && nIdx == nPos )
//STRIP001         {
//STRIP001             // enter bidi portion
//STRIP001             if ( nCrsrLevel != nDefaultDir )
//STRIP001             {
//STRIP001                 bRecurse = sal_True;
//STRIP001                 nIdx -= pLast->GetLen();
//STRIP001                 pPor = pLast;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // Recursion
//STRIP001         if ( bRecurse )
//STRIP001         {
//STRIP001             const SwLineLayout& rLine = ((SwMultiPortion*)pPor)->GetRoot();
//STRIP001             xub_StrLen nTmpPos = nPos - nIdx;
//STRIP001             sal_Bool bTmpForward = ! bRight;
//STRIP001             BYTE nTmpCrsrLevel = nCrsrLevel;
//STRIP001             lcl_VisualMoveRecursion( rLine, 0, nTmpPos, bTmpForward,
//STRIP001                                      nTmpCrsrLevel, nDefaultDir + 1 );
//STRIP001
//STRIP001             nPos = nTmpPos + nIdx;
//STRIP001             bRight = bTmpForward;
//STRIP001             nCrsrLevel = nTmpCrsrLevel;
//STRIP001         }
//STRIP001
//STRIP001         // go forward
//STRIP001         else
//STRIP001         {
//STRIP001             bRight = sal_True;
//STRIP001             nCrsrLevel = nDefaultDir;
//STRIP001         }
//STRIP001
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         sal_Bool bRecurse = pPor && pPor->IsMultiPortion() && ((SwMultiPortion*)pPor)->IsBidi();
//STRIP001
//STRIP001         // 1. special case: at beginning of bidi portion
//STRIP001         if ( bRecurse && nIdx == nPos )
//STRIP001         {
//STRIP001             // leave bidi portion
//STRIP001             if ( nCrsrLevel == nDefaultDir )
//STRIP001             {
//STRIP001                 bRecurse = sal_False;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // 2. special case: at beginning of portion after bidi portion
//STRIP001         else if ( pLast && pLast->IsMultiPortion() &&
//STRIP001                  ((SwMultiPortion*)pLast)->IsBidi() && nIdx == nPos )
//STRIP001         {
//STRIP001             nPos -= pLast->GetLen();
//STRIP001
//STRIP001             // enter bidi portion
//STRIP001             if ( nCrsrLevel % 2 == nDefaultDir % 2 )
//STRIP001             {
//STRIP001                 bRecurse = sal_True;
//STRIP001                 nIdx -= pLast->GetLen();
//STRIP001                 pPor = pLast;
//STRIP001
//STRIP001                 // special case:
//STRIP001                 // buffer: abcXYZ123 in LTR paragraph
//STRIP001                 // view:   abc123ZYX
//STRIP001                 // cursor is behind 3 in the buffer and cursor level = 2
//STRIP001                 if ( nDefaultDir + 2 == nCrsrLevel )
//STRIP001                     nPos += pLast->GetLen();
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // go forward
//STRIP001         if ( bRecurse )
//STRIP001         {
//STRIP001             const SwLineLayout& rLine = ((SwMultiPortion*)pPor)->GetRoot();
//STRIP001             xub_StrLen nTmpPos = nPos - nIdx;
//STRIP001             sal_Bool bTmpForward = ! bRight;
//STRIP001             BYTE nTmpCrsrLevel = nCrsrLevel;
//STRIP001             lcl_VisualMoveRecursion( rLine, 0, nTmpPos, bTmpForward,
//STRIP001                                      nTmpCrsrLevel, nDefaultDir + 1 );
//STRIP001
//STRIP001             // special case:
//STRIP001             // buffer: abcXYZ123 in LTR paragraph
//STRIP001             // view:   abc123ZYX
//STRIP001             // cursor is between Z and 1 in the buffer and cursor level = 2
//STRIP001             if ( nTmpPos == pPor->GetLen() && nTmpCrsrLevel == nDefaultDir + 1 )
//STRIP001             {
//STRIP001                 nTmpPos -= pPor->GetLen();
//STRIP001                 nTmpCrsrLevel = nDefaultDir;
//STRIP001                 bTmpForward = ! bTmpForward;
//STRIP001             }
//STRIP001
//STRIP001             nPos = nTmpPos + nIdx;
//STRIP001             bRight = bTmpForward;
//STRIP001             nCrsrLevel = nTmpCrsrLevel;
//STRIP001         }
//STRIP001
//STRIP001         // go backward
//STRIP001         else
//STRIP001         {
//STRIP001             bRight = sal_False;
//STRIP001             nCrsrLevel = nDefaultDir;
//STRIP001         }
//STRIP001     }
//STRIP001 }

//STRIP001 void SwTxtFrm::PrepareVisualMove( xub_StrLen& nPos, BYTE& nCrsrLevel,
//STRIP001                                   sal_Bool& bForward, sal_Bool bInsertCrsr )
//STRIP001 {
//STRIP001     if( IsEmpty() || IsHiddenNow() )
//STRIP001         return;
//STRIP001
//STRIP001     ((SwTxtFrm*)this)->GetFormatted();
//STRIP001
//STRIP001     SwTxtSizeInfo aInf( (SwTxtFrm*)this );
//STRIP001     SwTxtCursor  aLine( ((SwTxtFrm*)this), &aInf );
//STRIP001
//STRIP001     if( nPos )
//STRIP001         aLine.CharCrsrToLine( nPos );
//STRIP001     else
//STRIP001         aLine.Top();
//STRIP001
//STRIP001     const SwLineLayout* pLine = aLine.GetCurr();
//STRIP001     const xub_StrLen nStt = aLine.GetStart();
//STRIP001     const xub_StrLen nLen = pLine->GetLen();
//STRIP001
//STRIP001     // We have to distinguish between an insert and overwrite cursor:
//STRIP001     // The insert cursor position depends on the cursor level:
//STRIP001     // buffer:  abcXYZdef in LTR paragraph
//STRIP001     // display: abcZYXdef
//STRIP001     // If cursor is between c and X in the buffer and cursor level is 0,
//STRIP001     // the cursor blinks between c and Z and -> sets the cursor between Z and Y.
//STRIP001     // If the cursor level is 1, the cursor blinks between X and d and
//STRIP001     // -> sets the cursor between d and e.
//STRIP001     // The overwrite cursor simply travels to the next visual character.
//STRIP001     if ( bInsertCrsr )
//STRIP001     {
//STRIP001         lcl_VisualMoveRecursion( *pLine, nStt, nPos, bForward,
//STRIP001                                  nCrsrLevel, IsRightToLeft() ? 1 : 0 );
//STRIP001         return;
//STRIP001     }
//STRIP001
//STRIP001     const BYTE nDefaultDir = IsRightToLeft() ? UBIDI_RTL : UBIDI_LTR;
//STRIP001     const sal_Bool bVisualRight = ( nDefaultDir == UBIDI_LTR && bForward ) ||
//STRIP001                                   ( nDefaultDir == UBIDI_RTL && ! bForward );
//STRIP001
//STRIP001     //
//STRIP001     // Bidi functions from icu 2.0
//STRIP001     //
//STRIP001     const sal_Unicode* pLineString = GetTxtNode()->GetTxt().GetBuffer();
//STRIP001     pLine += nStt;
//STRIP001
//STRIP001     UErrorCode nError = U_ZERO_ERROR;
//STRIP001     UBiDi* pBidi = ubidi_openSized( nLen, 0, &nError );
//STRIP001     ubidi_setPara( pBidi, pLineString, nLen, nDefaultDir, NULL, &nError );
//STRIP001
//STRIP001     xub_StrLen nTmpPos;
//STRIP001     sal_Bool bOutOfBounds = sal_False;
//STRIP001
//STRIP001     if ( nPos < nStt + nLen )
//STRIP001     {
//STRIP001         nTmpPos = (xub_StrLen)ubidi_getVisualIndex( pBidi, nPos, &nError );
//STRIP001
//STRIP001         // visual indices are always LTR aligned
//STRIP001         if ( bVisualRight )
//STRIP001         {
//STRIP001             if ( nTmpPos + 1 < nStt + nLen )
//STRIP001                 ++nTmpPos;
//STRIP001             else
//STRIP001             {
//STRIP001                 nPos = nDefaultDir == UBIDI_RTL ? 0 : nStt + nLen;
//STRIP001                 bOutOfBounds = sal_True;
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             if ( nTmpPos )
//STRIP001                 --nTmpPos;
//STRIP001             else
//STRIP001             {
//STRIP001                 nPos = nDefaultDir == UBIDI_RTL ? nStt + nLen : 0;
//STRIP001                 bOutOfBounds = sal_True;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         nTmpPos = nDefaultDir == UBIDI_LTR ? nPos - 1 : 0;
//STRIP001     }
//STRIP001
//STRIP001     if ( ! bOutOfBounds )
//STRIP001     {
//STRIP001         nPos = (xub_StrLen)ubidi_getLogicalIndex( pBidi, nTmpPos, &nError );
//STRIP001
//STRIP001         if ( bForward )
//STRIP001         {
//STRIP001             if ( nPos )
//STRIP001                 --nPos;
//STRIP001             else
//STRIP001             {
//STRIP001                 ++nPos;
//STRIP001                 bForward = ! bForward;
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001             ++nPos;
//STRIP001     }
//STRIP001
//STRIP001     ubidi_close( pBidi );
//STRIP001 }

/*************************************************************************
 *                      SwTxtFrm::_UnitDown()
 *************************************************************************/

//STRIP001 sal_Bool SwTxtFrm::_UnitDown(SwPaM *pPam, const SwTwips nOffset,
//STRIP001                          sal_Bool bSetInReadOnly ) const
//STRIP001 {
//STRIP001
//STRIP001  if ( IsInTab() &&
//STRIP001      pPam->GetNode( sal_True )->StartOfSectionNode() !=
//STRIP001      pPam->GetNode( sal_False )->StartOfSectionNode() )
//STRIP001  {
//STRIP001      //Wenn der PaM in unterschiedlichen Boxen sitzt, so handelt es sich um
//STRIP001      //eine Tabellenselektion; diese wird von der Basisklasse abgearbeitet.
//STRIP001      return SwCntntFrm::UnitDown( pPam, nOffset, bSetInReadOnly );
//STRIP001  }
//STRIP001  ((SwTxtFrm*)this)->GetFormatted();
//STRIP001  const xub_StrLen nPos = pPam->GetPoint()->nContent.GetIndex();
//STRIP001  SwRect aCharBox;
//STRIP001  const SwCntntFrm *pFollow;
//STRIP001
//STRIP001     if ( IsVertical() )
//STRIP001         ((SwTxtFrm*)this)->SwapWidthAndHeight();
//STRIP001
//STRIP001  if ( !IsEmpty() && !IsHiddenNow() )
//STRIP001  {
//STRIP001      xub_StrLen nFormat = STRING_LEN;
//STRIP001      do
//STRIP001      {
//STRIP001          if( nFormat != STRING_LEN && !IsFollow() &&
//STRIP001              !lcl_ChangeOffset( ((SwTxtFrm*)this), nFormat ) )
//STRIP001              break;
//STRIP001
//STRIP001          SwTxtSizeInfo aInf( (SwTxtFrm*)this );
//STRIP001          SwTxtCursor  aLine( ((SwTxtFrm*)this), &aInf );
//STRIP001          nFormat = aLine.GetEnd();
//STRIP001
//STRIP001          aLine.CharCrsrToLine( nPos );
//STRIP001
//STRIP001             const SwLineLayout* pNextLine = aLine.GetNextLine();
//STRIP001             const xub_StrLen nStart = aLine.GetStart();
//STRIP001             SwRect aCharBox;
//STRIP001             aLine.GetCharRect( &aCharBox, nPos );
//STRIP001
//STRIP001             sal_Bool bFirstOfDouble = ( aInf.IsMulti() && aInf.IsFirstMulti() );
//STRIP001
//STRIP001             if( pNextLine || bFirstOfDouble )
//STRIP001          {
//STRIP001                 aCharBox.SSize().Width() /= 2;
//STRIP001 #ifndef PRODUCT
//STRIP001              // siehe Kommentar in SwTxtFrm::GetCrsrOfst()
//STRIP001                 const ULONG nOldNode = pPam->GetPoint()->nNode.GetIndex();
//STRIP001 #endif
//STRIP001                 if ( pNextLine && ! bFirstOfDouble )
//STRIP001                     aLine.NextLine();
//STRIP001
//STRIP001                 xub_StrLen nOfst = aLine.GetCrsrOfst( pPam->GetPoint(),
//STRIP001                               aCharBox.Pos(), sal_False );
//STRIP001              ASSERT( nOldNode == pPam->GetPoint()->nNode.GetIndex(),
//STRIP001                  "SwTxtFrm::UnitDown: illegal node change" )
//STRIP001
//STRIP001              // 7684: Wir stellen sicher, dass wir uns nach unten bewegen.
//STRIP001                 if( nOfst <= nStart && ! bFirstOfDouble )
//STRIP001                  nOfst = nStart + 1;
//STRIP001              pPam->GetPoint()->nContent =
//STRIP001                    SwIndex( ((SwTxtFrm*)this)->GetTxtNode(), nOfst );
//STRIP001
//STRIP001                 if ( IsVertical() )
//STRIP001                     ((SwTxtFrm*)this)->SwapWidthAndHeight();
//STRIP001
//STRIP001              return sal_True;
//STRIP001          }
//STRIP001          if( 0 != ( pFollow = GetFollow() ) )
//STRIP001          {   // geschuetzte Follows auslassen
//STRIP001              const SwCntntFrm* pTmp = pFollow;
//STRIP001              ViewShell *pSh = GetShell();
//STRIP001              if( !pSh || !pSh->GetViewOptions()->IsCursorInProtectedArea() )
//STRIP001              {
//STRIP001                  while( pFollow && pFollow->IsProtected() )
//STRIP001                  {
//STRIP001                      pTmp = pFollow;
//STRIP001                      pFollow = pFollow->GetFollow();
//STRIP001                  }
//STRIP001              }
//STRIP001              if( !pFollow ) // nur noch geschuetzte
//STRIP001                 {
//STRIP001                     if ( IsVertical() )
//STRIP001                         ((SwTxtFrm*)this)->SwapWidthAndHeight();
//STRIP001                     return pTmp->SwCntntFrm::UnitDown( pPam, nOffset, bSetInReadOnly );
//STRIP001                 }
//STRIP001
//STRIP001                 aLine.GetCharRect( &aCharBox, nPos );
//STRIP001              aCharBox.SSize().Width() /= 2;
//STRIP001          }
//STRIP001          else if( !IsFollow() )
//STRIP001          {
//STRIP001              xub_StrLen nTmpLen = aInf.GetTxt().Len();
//STRIP001              if( aLine.GetEnd() < nTmpLen )
//STRIP001              {
//STRIP001                  if( nFormat <= GetOfst() )
//STRIP001                  {
//STRIP001                      nFormat = Min( xub_StrLen( GetOfst() + MIN_OFFSET_STEP ),
//STRIP001                                     nTmpLen );
//STRIP001                      if( nFormat <= GetOfst() )
//STRIP001                          break;
//STRIP001                  }
//STRIP001                  continue;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      } while( sal_True );
//STRIP001  }
//STRIP001  else
//STRIP001      pFollow = GetFollow();
//STRIP001
//STRIP001     if ( IsVertical() )
//STRIP001         ((SwTxtFrm*)this)->SwapWidthAndHeight();
//STRIP001
//STRIP001  // Bei Follows schlagen wir eine Abkuerzung
//STRIP001  if( pFollow )
//STRIP001  {
//STRIP001      aCharBox.Pos().Y() = pFollow->Frm().Top() + 1;
//STRIP001      return ((SwTxtFrm*)pFollow)->GetKeyCrsrOfst( pPam->GetPoint(),
//STRIP001                                                   aCharBox.Pos() );
//STRIP001  }
//STRIP001  return SwCntntFrm::UnitDown( pPam, nOffset, bSetInReadOnly );
//STRIP001 }

/*************************************************************************
 *                   virtual SwTxtFrm::UnitUp()
 *************************************************************************/

//STRIP001 sal_Bool SwTxtFrm::UnitUp(SwPaM *pPam, const SwTwips nOffset,
//STRIP001                          sal_Bool bSetInReadOnly ) const
//STRIP001 {
//STRIP001  /* Im CrsrSh::Up() wird CntntNode::GetFrm() gerufen.
//STRIP001   * Dies liefert _immer_ den Master zurueck.
//STRIP001   * Um das Cursortravelling nicht zu belasten, korrigieren wir
//STRIP001   * hier im SwTxtFrm.
//STRIP001   * Wir ermittelt UnitUp fuer pFrm, pFrm ist entweder ein Master (=this)
//STRIP001   * oder ein Follow (!=this)
//STRIP001   */
//STRIP001  const SwTxtFrm *pFrm = GetAdjFrmAtPos( (SwTxtFrm*)this, *(pPam->GetPoint()),
//STRIP001                                         SwTxtCursor::IsRightMargin() );
//STRIP001  const sal_Bool bRet = pFrm->_UnitUp( pPam, nOffset, bSetInReadOnly );
//STRIP001
//STRIP001  // 8626: kein SwTxtCursor::SetRightMargin( sal_False );
//STRIP001  // statt dessen steht ein SwSetToRightMargin im _UnitUp
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
 *                   virtual SwTxtFrm::UnitDown()
 *************************************************************************/

//STRIP001 sal_Bool SwTxtFrm::UnitDown(SwPaM *pPam, const SwTwips nOffset,
//STRIP001                          sal_Bool bSetInReadOnly ) const
//STRIP001 {
//STRIP001  const SwTxtFrm *pFrm = GetAdjFrmAtPos((SwTxtFrm*)this, *(pPam->GetPoint()),
//STRIP001                                         SwTxtCursor::IsRightMargin() );
//STRIP001  const sal_Bool bRet = pFrm->_UnitDown( pPam, nOffset, bSetInReadOnly );
//STRIP001  SwTxtCursor::SetRightMargin( sal_False );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SwTxtFrm::FillCrsrPos( SwFillData& rFill ) const
//STRIP001 {
//STRIP001  if( !rFill.bColumn && GetUpper()->IsColBodyFrm() ) // ColumnFrms jetzt mit BodyFrm
//STRIP001  {
//STRIP001      const SwColumnFrm* pTmp =
//STRIP001          (SwColumnFrm*)GetUpper()->GetUpper()->GetUpper()->Lower(); // die 1. Spalte
//STRIP001      // der erste SwFrm im BodyFrm der ersten Spalte
//STRIP001      const SwFrm* pFrm = ((SwLayoutFrm*)pTmp->Lower())->Lower();
//STRIP001      MSHORT nNextCol = 0;
//STRIP001      // In welcher Spalte landen wir?
//STRIP001      while( rFill.X() > pTmp->Frm().Right() && pTmp->GetNext() )
//STRIP001      {
//STRIP001          pTmp = (SwColumnFrm*)pTmp->GetNext();
//STRIP001          if( ((SwLayoutFrm*)pTmp->Lower())->Lower() ) // ColumnFrms jetzt mit BodyFrm
//STRIP001          {
//STRIP001              pFrm = ((SwLayoutFrm*)pTmp->Lower())->Lower();
//STRIP001              nNextCol = 0;
//STRIP001          }
//STRIP001          else
//STRIP001              ++nNextCol; // leere Spalten erfordern Spaltenumbrueche
//STRIP001      }
//STRIP001      if( pTmp != GetUpper()->GetUpper() ) // Sind wir in einer anderen Spalte gelandet?
//STRIP001      {
//STRIP001          if( !pFrm )
//STRIP001              return;
//STRIP001          if( nNextCol )
//STRIP001          {
//STRIP001              while( pFrm->GetNext() )
//STRIP001                  pFrm = pFrm->GetNext();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              while( pFrm->GetNext() && pFrm->Frm().Bottom() < rFill.Y() )
//STRIP001                  pFrm = pFrm->GetNext();
//STRIP001          }
//STRIP001          // Kein Fuellen, wenn als letzter Frame in der anvisierten
//STRIP001          // Spalte kein Absatz, sondern z.B. eine Tabelle steht
//STRIP001          if( pFrm->IsTxtFrm() )
//STRIP001          {
//STRIP001              rFill.Fill().nColumnCnt = nNextCol;
//STRIP001              rFill.bColumn = sal_True;
//STRIP001              if( rFill.pPos )
//STRIP001              {
//STRIP001                  SwTxtNode* pTxtNd = ((SwTxtFrm*)pFrm)->GetTxtNode();
//STRIP001                  rFill.pPos->nNode = *pTxtNd;
//STRIP001                  rFill.pPos->nContent.Assign( pTxtNd, pTxtNd->GetTxt().Len() );
//STRIP001              }
//STRIP001              if( nNextCol )
//STRIP001              {
//STRIP001                  rFill.aFrm = pTmp->Prt();
//STRIP001                  rFill.aFrm += pTmp->Frm().Pos();
//STRIP001              }
//STRIP001              else
//STRIP001                  rFill.aFrm = pFrm->Frm();
//STRIP001              ((SwTxtFrm*)pFrm)->FillCrsrPos( rFill );
//STRIP001          }
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001  sal_Bool bFill = sal_True;
//STRIP001  SwFont *pFnt;
//STRIP001  SwTxtFmtColl* pColl = GetTxtNode()->GetTxtColl();
//STRIP001  MSHORT nFirst = GetTxtNode()->GetSwAttrSet().GetULSpace().GetLower();
//STRIP001  SwTwips nDiff = rFill.Y() - Frm().Bottom();
//STRIP001  if( nDiff < nFirst )
//STRIP001      nDiff = -1;
//STRIP001  else
//STRIP001      pColl = &pColl->GetNextTxtFmtColl();
//STRIP001  SwAttrSet aSet( ((SwDoc*)GetTxtNode()->GetDoc())->GetAttrPool(), aTxtFmtCollSetRange );
//STRIP001  const SwAttrSet* pSet = &pColl->GetAttrSet();
//STRIP001  ViewShell *pSh = GetShell();
//STRIP001  if( GetTxtNode()->HasSwAttrSet() )
//STRIP001  {
//STRIP001      aSet.Put( *GetTxtNode()->GetpSwAttrSet() );
//STRIP001      aSet.SetParent( pSet );
//STRIP001      pSet = &aSet;
//STRIP001         pFnt = new SwFont( pSet, GetNode()->GetDoc() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwFontAccess aFontAccess( pColl, pSh );
//STRIP001      pFnt = new SwFont( *aFontAccess.Get()->GetFont() );
//STRIP001      pFnt->ChkMagic( pSh, pFnt->GetActual() );
//STRIP001  }
//STRIP001  OutputDevice *pOut = pSh->GetOut();
//STRIP001  if ( !GetTxtNode()->GetDoc()->IsBrowseMode() ||
//STRIP001          ( pSh->GetViewOptions()->IsPrtFormat() ) )
//STRIP001         pOut = &GetTxtNode()->GetDoc()->GetRefDev();
//STRIP001
//STRIP001     pFnt->SetFntChg( sal_True );
//STRIP001  pFnt->ChgPhysFnt( pSh, pOut );
//STRIP001
//STRIP001  SwTwips nLineHeight = pFnt->GetHeight( pSh, pOut );
//STRIP001
//STRIP001  if( nLineHeight )
//STRIP001  {
//STRIP001      const SvxULSpaceItem &rUL = pSet->GetULSpace();
//STRIP001      SwTwips nDist = Max( rUL.GetLower(), rUL.GetUpper() );
//STRIP001      if( rFill.Fill().nColumnCnt )
//STRIP001      {
//STRIP001          rFill.aFrm.Height( nLineHeight );
//STRIP001          nDiff = rFill.Y() - rFill.Bottom();
//STRIP001          nFirst = 0;
//STRIP001      }
//STRIP001      else if( nDist < nFirst )
//STRIP001             nFirst -= (USHORT)nDist;
//STRIP001      else
//STRIP001          nFirst = 0;
//STRIP001      nDist = Max( nDist, long( GetLineSpace() ) );
//STRIP001      nDist += nLineHeight;
//STRIP001      nDiff -= nFirst;
//STRIP001
//STRIP001      if( nDiff > 0 )
//STRIP001      {
//STRIP001          nDiff /= nDist;
//STRIP001          rFill.Fill().nParaCnt = nDiff + 1;
//STRIP001          rFill.nLineWidth = 0;
//STRIP001          rFill.bInner = sal_False;
//STRIP001          rFill.bEmpty = sal_True;
//STRIP001          rFill.SetOrient( HORI_LEFT );
//STRIP001      }
//STRIP001      else
//STRIP001          nDiff = -1;
//STRIP001      if( rFill.bInner )
//STRIP001          bFill = sal_False;
//STRIP001      else
//STRIP001      {
//STRIP001          const SvxTabStopItem &rRuler = pSet->GetTabStops();
//STRIP001          const SvxLRSpaceItem &rLRSpace = pSet->GetLRSpace();
//STRIP001
//STRIP001          SwRect &rRect = rFill.Fill().aCrsr;
//STRIP001          rRect.Top( rFill.Bottom() + (nDiff+1) * nDist - nLineHeight );
//STRIP001          if( nFirst && nDiff > -1 )
//STRIP001              rRect.Top( rRect.Top() + nFirst );
//STRIP001          rRect.Height( nLineHeight );
//STRIP001          SwTwips nLeft = rFill.Left() + rLRSpace.GetLeft() +
//STRIP001                          GetTxtNode()->GetLeftMarginWithNum( sal_False );
//STRIP001          SwTwips nRight = rFill.Right() - rLRSpace.GetRight();
//STRIP001          SwTwips nCenter = ( nLeft + nRight ) / 2;
//STRIP001          rRect.Left( nLeft );
//STRIP001          if( FILL_MARGIN == rFill.Mode() )
//STRIP001          {
//STRIP001              if( rFill.bEmpty )
//STRIP001              {
//STRIP001                  rFill.SetOrient( HORI_LEFT );
//STRIP001                  if( rFill.X() < nCenter )
//STRIP001                  {
//STRIP001                      if( rFill.X() > ( nLeft + 2 * nCenter ) / 3 )
//STRIP001                      {
//STRIP001                          rFill.SetOrient( HORI_CENTER );
//STRIP001                          rRect.Left( nCenter );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else if( rFill.X() > ( nRight + 2 * nCenter ) / 3 )
//STRIP001                  {
//STRIP001                      rFill.SetOrient( HORI_RIGHT );
//STRIP001                      rRect.Left( nRight );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      rFill.SetOrient( HORI_CENTER );
//STRIP001                      rRect.Left( nCenter );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  bFill = sal_False;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwTwips nSpace;
//STRIP001              if( FILL_TAB != rFill.Mode() )
//STRIP001              {
//STRIP001 static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
//STRIP001                  const XubString aTmp( sDoubleSpace, RTL_TEXTENCODING_MS_1252 );
//STRIP001
//STRIP001                     SwDrawTextInfo aDrawInf( pSh, *pOut, 0, aTmp, 0, 2 );
//STRIP001                     nSpace = pFnt->_GetTxtSize( aDrawInf ).Width()/2;
//STRIP001              }
//STRIP001              if( rFill.X() >= nRight )
//STRIP001              {
//STRIP001                  if( FILL_INDENT != rFill.Mode() && ( rFill.bEmpty ||
//STRIP001                      rFill.X() > rFill.nLineWidth + FILL_MIN_DIST ) )
//STRIP001                  {
//STRIP001                      rFill.SetOrient( HORI_RIGHT );
//STRIP001                      rRect.Left( nRight );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bFill = sal_False;
//STRIP001              }
//STRIP001              else if( FILL_INDENT == rFill.Mode() )
//STRIP001              {
//STRIP001                  SwTwips nIndent = rFill.X();
//STRIP001                  if( !rFill.bEmpty || nIndent > nRight )
//STRIP001                      bFill = sal_False;
//STRIP001                  else
//STRIP001                  {
//STRIP001                      nIndent -= rFill.Left();
//STRIP001                      if( nIndent >= 0 && nSpace )
//STRIP001                      {
//STRIP001                          nIndent /= nSpace;
//STRIP001                          nIndent *= nSpace;
//STRIP001                          rFill.SetTab( MSHORT( nIndent ) );
//STRIP001                          rRect.Left( nIndent + rFill.Left() );
//STRIP001                      }
//STRIP001                      else
//STRIP001                          bFill = sal_False;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( rFill.X() > nLeft )
//STRIP001              {
//STRIP001                  SwTwips nTxtLeft = rFill.Left() + rLRSpace.GetTxtLeft() +
//STRIP001                                  GetTxtNode()->GetLeftMarginWithNum( sal_True );
//STRIP001                  rFill.nLineWidth += rFill.bFirstLine ? nLeft : nTxtLeft;
//STRIP001                  SwTwips nLeftTab = nLeft;
//STRIP001                  SwTwips nRightTab = nLeft;
//STRIP001                  MSHORT nSpaceCnt = 0;
//STRIP001                  MSHORT nTabCnt = 0;
//STRIP001                  MSHORT nIdx = 0;
//STRIP001                  do
//STRIP001                  {
//STRIP001                      nLeftTab = nRightTab;
//STRIP001                      if( nIdx < rRuler.Count() )
//STRIP001                      {
//STRIP001                          const SvxTabStop &rTabStop = rRuler.operator[](nIdx);
//STRIP001                          nRightTab = nTxtLeft + rTabStop.GetTabPos();
//STRIP001                          if( nLeftTab < nTxtLeft && nRightTab > nTxtLeft )
//STRIP001                              nRightTab = nTxtLeft;
//STRIP001                          else
//STRIP001                              ++nIdx;
//STRIP001                          if( nRightTab > rFill.nLineWidth )
//STRIP001                              ++nTabCnt;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          const SvxTabStopItem& rTab =
//STRIP001                              (const SvxTabStopItem &)pSet->
//STRIP001                              GetPool()->GetDefaultItem( RES_PARATR_TABSTOP );
//STRIP001                          MSHORT nDefTabDist = (MSHORT)rTab.GetStart()->GetTabPos();
//STRIP001                          nRightTab = nLeftTab - nTxtLeft;
//STRIP001                          nRightTab /= nDefTabDist;
//STRIP001                          nRightTab = nRightTab * nDefTabDist + nTxtLeft;
//STRIP001                          while ( nRightTab <= nLeftTab )
//STRIP001                              nRightTab += nDefTabDist;
//STRIP001                          if( nRightTab > rFill.nLineWidth )
//STRIP001                              ++nTabCnt;
//STRIP001                          while ( nRightTab < rFill.X() )
//STRIP001                          {
//STRIP001                              nRightTab += nDefTabDist;
//STRIP001                              if( nRightTab > rFill.nLineWidth )
//STRIP001                                  ++nTabCnt;
//STRIP001                          }
//STRIP001                          if( nLeftTab < nRightTab - nDefTabDist )
//STRIP001                              nLeftTab = nRightTab - nDefTabDist;
//STRIP001                      }
//STRIP001                      if( nRightTab > nRight )
//STRIP001                          nRightTab = nRight;
//STRIP001                  }
//STRIP001                  while( rFill.X() > nRightTab );
//STRIP001                  --nTabCnt;
//STRIP001                  if( FILL_TAB != rFill.Mode() )
//STRIP001                  {
//STRIP001                      if( nSpace > 0 )
//STRIP001                      {
//STRIP001                          if( !nTabCnt )
//STRIP001                              nLeftTab = rFill.nLineWidth;
//STRIP001                          while( nLeftTab < rFill.X() )
//STRIP001                          {
//STRIP001                              nLeftTab += nSpace;
//STRIP001                              ++nSpaceCnt;
//STRIP001                          }
//STRIP001                          if( nSpaceCnt )
//STRIP001                          {
//STRIP001                              nLeftTab -= nSpace;
//STRIP001                              --nSpaceCnt;
//STRIP001                          }
//STRIP001                          if( rFill.X() - nLeftTab > nRightTab - rFill.X() )
//STRIP001                          {
//STRIP001                              nSpaceCnt = 0;
//STRIP001                              ++nTabCnt;
//STRIP001                              rRect.Left( nRightTab );
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              if( rFill.X() - nLeftTab > nSpace/2 )
//STRIP001                              {
//STRIP001                                  ++nSpaceCnt;
//STRIP001                                  rRect.Left( nLeftTab + nSpace );
//STRIP001                              }
//STRIP001                              else
//STRIP001                                  rRect.Left( nLeftTab );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else if( rFill.X() - nLeftTab < nRightTab - rFill.X() )
//STRIP001                          rRect.Left( nLeftTab );
//STRIP001                      else
//STRIP001                      {
//STRIP001                          if( nRightTab >= nRight )
//STRIP001                          {
//STRIP001                              rFill.SetOrient( HORI_RIGHT );
//STRIP001                              rRect.Left( nRight );
//STRIP001                              nTabCnt = 0;
//STRIP001                              nSpaceCnt = 0;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              rRect.Left( nRightTab );
//STRIP001                              ++nTabCnt;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if( rFill.X() - nLeftTab < nRightTab - rFill.X() )
//STRIP001                          rRect.Left( nLeftTab );
//STRIP001                      else
//STRIP001                      {
//STRIP001                          if( nRightTab >= nRight )
//STRIP001                          {
//STRIP001                              rFill.SetOrient( HORI_RIGHT );
//STRIP001                              rRect.Left( nRight );
//STRIP001                              nTabCnt = 0;
//STRIP001                              nSpaceCnt = 0;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              rRect.Left( nRightTab );
//STRIP001                              ++nTabCnt;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  rFill.SetTab( nTabCnt );
//STRIP001                  rFill.SetSpace( nSpaceCnt );
//STRIP001                  if( bFill )
//STRIP001                  {
//STRIP001                      if( Abs( rFill.X() - nCenter ) <=
//STRIP001                          Abs( rFill.X() - rRect.Left() ) )
//STRIP001                      {
//STRIP001                          rFill.SetOrient( HORI_CENTER );
//STRIP001                          rFill.SetTab( 0 );
//STRIP001                          rFill.SetSpace( 0 );
//STRIP001                          rRect.Left( nCenter );
//STRIP001                      }
//STRIP001                      if( !rFill.bEmpty )
//STRIP001                          rFill.nLineWidth += FILL_MIN_DIST;
//STRIP001                      if( rRect.Left() < rFill.nLineWidth )
//STRIP001                          bFill = sal_False;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          // Gehen wir ueber die Unterkante der Seite/Spalte etc. hinaus?
//STRIP001          const SwFrm* pUp = GetUpper();
//STRIP001          if( pUp->IsInSct() )
//STRIP001          {
//STRIP001              if( pUp->IsSctFrm() )
//STRIP001                  pUp = pUp->GetUpper();
//STRIP001              else if( pUp->IsColBodyFrm() &&
//STRIP001                       pUp->GetUpper()->GetUpper()->IsSctFrm() )
//STRIP001                  pUp = pUp->GetUpper()->GetUpper()->GetUpper();
//STRIP001          }
//STRIP001             SWRECTFN( this )
//STRIP001             SwTwips nLimit = (pUp->*fnRect->fnGetPrtBottom)();
//STRIP001             SwTwips nRectBottom = rRect.Bottom();
//STRIP001             if ( bVert )
//STRIP001                 nRectBottom = SwitchHorizontalToVertical( nRectBottom );
//STRIP001
//STRIP001             if( (*fnRect->fnYDiff)( nLimit, nRectBottom ) < 0 )
//STRIP001              bFill = sal_False;
//STRIP001          else
//STRIP001              rRect.Width( 1 );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      bFill = sal_False;
//STRIP001  ((SwCrsrMoveState*)rFill.pCMS)->bFillRet = bFill;
//STRIP001  delete pFnt;
//STRIP001 }


