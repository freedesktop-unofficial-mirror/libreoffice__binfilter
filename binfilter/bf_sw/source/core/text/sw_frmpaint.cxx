/*************************************************************************
 *
 *  $RCSfile: sw_frmpaint.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:06 $
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

#ifndef _SV_SOUND_HXX //autogen
#include <vcl/sound.hxx>
#endif

#ifndef _SHL_HXX
#include <tools/shl.hxx> // SW_MOD
#endif

#ifndef _SVX_PGRDITEM_HXX
#include <bf_svx/pgrditem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> // SwPageDesc
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif

#ifndef _FMTLINE_HXX
#include <fmtline.hxx>
#endif
#ifndef _LINEINFO_HXX
#include <lineinfo.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>  // SwViewImp
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>  // SwViewOption
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>  // DrawGraphic
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _TXTCFG_HXX
#include <txtcfg.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // SwTxtFrm
#endif
#ifndef _ITRPAINT_HXX
#include <itrpaint.hxx>     // SwTxtPainter
#endif
#ifndef _TXTPAINT_HXX
#include <txtpaint.hxx>     // SwSaveClip
#endif
#ifndef _TXTCACHE_HXX
#include <txtcache.hxx> // SwTxtLineAccess
#endif
#ifndef _SWFNTCCH_HXX
#include <swfntcch.hxx> // SwFontAccess
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx> // SwDrawTextInfo
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>   // SwFlyFrm
#endif
#ifndef _REDLNITR_HXX
#include <redlnitr.hxx> // SwRedlineItr
#endif
#ifndef _DOC_HXX
#include <doc.hxx>      // SwDoc
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx> // SW_MOD
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>   // SwTabFrm (Redlining)
#endif
#include "scrrect.hxx"
namespace binfilter {


// steht im number.cxx
extern const sal_Char __FAR_DATA sBulletFntName[];

extern FASTBOOL bOneBeepOnly;

sal_Bool bInitFont = sal_True;

#define REDLINE_DISTANCE 567/4
#define REDLINE_MINDIST  567/10

//STRIP001 class SwExtraPainter
//STRIP001 {
//STRIP001  SwSaveClip aClip;
//STRIP001  SwRect aRect;
//STRIP001     const SwTxtFrm* pTxtFrm;
//STRIP001  ViewShell *pSh;
//STRIP001  SwFont* pFnt;
//STRIP001  const SwLineNumberInfo &rLineInf;
//STRIP001  SwTwips nX;
//STRIP001  SwTwips nRedX;
//STRIP001  ULONG nLineNr;
//STRIP001  MSHORT nDivider;
//STRIP001  sal_Bool bGoLeft;
//STRIP001  sal_Bool bLineNum;
//STRIP001  inline sal_Bool IsClipChg() { return aClip.IsChg(); }
//STRIP001 public:
//STRIP001  SwExtraPainter( const SwTxtFrm *pFrm, ViewShell *pVwSh,
//STRIP001      const SwLineNumberInfo &rLnInf, const SwRect &rRct, MSHORT nStart,
//STRIP001      SwHoriOrient eHor, sal_Bool bLnNm );
//STRIP001  ~SwExtraPainter() { delete pFnt; }
//STRIP001  inline SwFont* GetFont() const { return pFnt; }
//STRIP001  inline void IncLineNr() { ++nLineNr; }
//STRIP001  inline sal_Bool HasNumber() { return !( nLineNr % rLineInf.GetCountBy() ); }
//STRIP001  inline HasDivider() { if( !nDivider ) return sal_False;
//STRIP001      return !(nLineNr % rLineInf.GetDividerCountBy()); }
//STRIP001
//STRIP001  void PaintExtra( SwTwips nY, long nAsc, long nMax, sal_Bool bRed );
//STRIP001  void PaintRedline( SwTwips nY, long nMax );
//STRIP001 };
//STRIP001
//STRIP001
//STRIP001 SwExtraPainter::SwExtraPainter( const SwTxtFrm *pFrm, ViewShell *pVwSh,
//STRIP001  const SwLineNumberInfo &rLnInf, const SwRect &rRct, MSHORT nStart,
//STRIP001  SwHoriOrient eHor, sal_Bool bLnNm )
//STRIP001     : pTxtFrm( pFrm), pSh( pVwSh ), pFnt( 0 ), rLineInf( rLnInf ), aRect( rRct ),
//STRIP001    aClip( pVwSh->GetWin() || pFrm->IsUndersized() ? pVwSh->GetOut() : 0 ),
//STRIP001    nLineNr( 1L ), bLineNum( bLnNm )
//STRIP001 {
//STRIP001  if( pFrm->IsUndersized() )
//STRIP001  {
//STRIP001      SwTwips nBottom = pFrm->Frm().Bottom();
//STRIP001      if( aRect.Bottom() > nBottom )
//STRIP001          aRect.Bottom( nBottom );
//STRIP001  }
//STRIP001  MSHORT nVirtPageNum = 0;
//STRIP001  if( bLineNum )
//STRIP001  {   /* initialisiert die Member, die bei Zeilennumerierung notwendig sind:
//STRIP001
//STRIP001          nDivider,   wie oft ist ein Teilerstring gewuenscht, 0 == nie;
//STRIP001          nX,         X-Position der Zeilennummern;
//STRIP001          pFnt,       der Font der Zeilennummern;
//STRIP001          nLineNr,    die erste Zeilennummer;
//STRIP001      bLineNum wird ggf.wieder auf sal_False gesetzt, wenn die Numerierung sich
//STRIP001      komplett ausserhalb des Paint-Rechtecks aufhaelt. */
//STRIP001      nDivider = rLineInf.GetDivider().Len() ? rLineInf.GetDividerCountBy() : 0;
//STRIP001      nX = pFrm->Frm().Left();
//STRIP001      SwCharFmt* pFmt = rLineInf.GetCharFmt( *((SwDoc*)pFrm->GetNode()->GetDoc()) );
//STRIP001      ASSERT( pFmt, "PaintExtraData without CharFmt" );
//STRIP001         pFnt = new SwFont( &pFmt->GetAttrSet(), pFrm->GetTxtNode()->GetDoc() );
//STRIP001      pFnt->Invalidate();
//STRIP001      pFnt->ChgPhysFnt( pSh, pSh->GetOut() );
//STRIP001         pFnt->SetVertical( 0, pFrm->IsVertical() );
//STRIP001      nLineNr += pFrm->GetAllLines() - pFrm->GetThisLines();
//STRIP001      LineNumberPosition ePos = rLineInf.GetPos();
//STRIP001      if( ePos != LINENUMBER_POS_LEFT && ePos != LINENUMBER_POS_RIGHT )
//STRIP001      {
//STRIP001          if( pFrm->FindPageFrm()->OnRightPage() )
//STRIP001          {
//STRIP001              nVirtPageNum = 1;
//STRIP001              ePos = ePos == LINENUMBER_POS_INSIDE ?
//STRIP001                      LINENUMBER_POS_LEFT : LINENUMBER_POS_RIGHT;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nVirtPageNum = 2;
//STRIP001              ePos = ePos == LINENUMBER_POS_OUTSIDE ?
//STRIP001                      LINENUMBER_POS_LEFT : LINENUMBER_POS_RIGHT;
//STRIP001          }
//STRIP001      }
//STRIP001      if( LINENUMBER_POS_LEFT == ePos )
//STRIP001      {
//STRIP001          bGoLeft = sal_True;
//STRIP001          nX -= rLineInf.GetPosFromLeft();
//STRIP001             if( nX < aRect.Left() )
//STRIP001              bLineNum = sal_False;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          bGoLeft = sal_False;
//STRIP001          nX += pFrm->Frm().Width() + rLineInf.GetPosFromLeft();
//STRIP001          if( nX > aRect.Right() )
//STRIP001              bLineNum = sal_False;
//STRIP001      }
//STRIP001  }
//STRIP001  if( eHor != HORI_NONE )
//STRIP001  {
//STRIP001      if( HORI_INSIDE == eHor || HORI_OUTSIDE == eHor )
//STRIP001      {
//STRIP001          if( !nVirtPageNum )
//STRIP001              nVirtPageNum = pFrm->FindPageFrm()->OnRightPage() ? 1 : 2;
//STRIP001          if( nVirtPageNum % 2 )
//STRIP001              eHor = eHor == HORI_INSIDE ? HORI_LEFT : HORI_RIGHT;
//STRIP001          else
//STRIP001              eHor = eHor == HORI_OUTSIDE ? HORI_LEFT : HORI_RIGHT;
//STRIP001      }
//STRIP001      const SwFrm* pTmpFrm = pFrm->FindTabFrm();
//STRIP001      if( !pTmpFrm )
//STRIP001          pTmpFrm = pFrm;
//STRIP001      nRedX = HORI_LEFT == eHor ? pTmpFrm->Frm().Left() - REDLINE_DISTANCE :
//STRIP001          pTmpFrm->Frm().Right() + REDLINE_DISTANCE;
//STRIP001  }
//STRIP001 }

/*************************************************************************
 * SwExtraPainter::PaintExtra()
 **************************************************************************/

//STRIP001 void SwExtraPainter::PaintExtra( SwTwips nY, long nAsc, long nMax, sal_Bool bRed )
//STRIP001 {
//STRIP001  //Zeilennummer ist staerker als der Teiler
//STRIP001  XubString aTmp( HasNumber() ? rLineInf.GetNumType().GetNumStr( nLineNr )
//STRIP001                              : rLineInf.GetDivider() );
//STRIP001
//STRIP001     SwDrawTextInfo aDrawInf( pSh, *pSh->GetOut(), 0, aTmp, 0, aTmp.Len() );
//STRIP001  aDrawInf.SetSpace( 0 );
//STRIP001  aDrawInf.SetWrong( NULL );
//STRIP001  aDrawInf.SetLeft( 0 );
//STRIP001  aDrawInf.SetRight( LONG_MAX );
//STRIP001     aDrawInf.SetFrm( pTxtFrm );
//STRIP001     aDrawInf.SetFont( pFnt );
//STRIP001     aDrawInf.SetSnapToGrid( sal_False );
//STRIP001 #ifdef BIDI
//STRIP001     aDrawInf.SetIgnoreFrmRTL( sal_True );
//STRIP001 #endif
//STRIP001
//STRIP001  sal_Bool bTooBig = pFnt->GetSize( pFnt->GetActual() ).Height() > nMax &&
//STRIP001              pFnt->GetHeight( pSh, pSh->GetOut() ) > nMax;
//STRIP001  SwFont* pTmpFnt;
//STRIP001  if( bTooBig )
//STRIP001  {
//STRIP001      pTmpFnt = new SwFont( *GetFont() );
//STRIP001      if( nMax >= 20 )
//STRIP001      {
//STRIP001          nMax *= 17;
//STRIP001          nMax /= 20;
//STRIP001      }
//STRIP001      pTmpFnt->SetSize( Size( 0, nMax ), pTmpFnt->GetActual() );
//STRIP001  }
//STRIP001  else
//STRIP001      pTmpFnt = GetFont();
//STRIP001     Point aTmpPos( nX, nY );
//STRIP001     aTmpPos.Y() += nAsc;
//STRIP001  sal_Bool bPaint = sal_True;
//STRIP001  if( !IsClipChg() )
//STRIP001  {
//STRIP001         Size aSize = pTmpFnt->_GetTxtSize( aDrawInf );
//STRIP001      if( bGoLeft )
//STRIP001          aTmpPos.X() -= aSize.Width();
//STRIP001         // calculate rectangle containing the line number
//STRIP001         SwRect aRct( Point( aTmpPos.X(),
//STRIP001                          aTmpPos.Y() - pTmpFnt->GetAscent( pSh, pSh->GetOut() )
//STRIP001                           ), aSize );
//STRIP001      if( !aRect.IsInside( aRct ) )
//STRIP001      {
//STRIP001          if( aRct.Intersection( aRect ).IsEmpty() )
//STRIP001              bPaint = sal_False;
//STRIP001          else
//STRIP001                 aClip.ChgClip( aRect, pTxtFrm );
//STRIP001      }
//STRIP001  }
//STRIP001  else if( bGoLeft )
//STRIP001         aTmpPos.X() -= pTmpFnt->_GetTxtSize( aDrawInf ).Width();
//STRIP001  aDrawInf.SetPos( aTmpPos );
//STRIP001  if( bPaint )
//STRIP001      pTmpFnt->_DrawText( aDrawInf );
//STRIP001
//STRIP001  if( bTooBig )
//STRIP001      delete pTmpFnt;
//STRIP001  if( bRed )
//STRIP001  {
//STRIP001      long nDiff = bGoLeft ? nRedX - nX : nX - nRedX;
//STRIP001      if( nDiff > REDLINE_MINDIST )
//STRIP001          PaintRedline( nY, nMax );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwExtraPainter::PaintRedline( SwTwips nY, long nMax )
//STRIP001 {
//STRIP001  Point aStart( nRedX, nY );
//STRIP001  Point aEnd( nRedX, nY + nMax );
//STRIP001
//STRIP001  if( !IsClipChg() )
//STRIP001  {
//STRIP001      SwRect aRct( aStart, aEnd );
//STRIP001      if( !aRect.IsInside( aRct ) )
//STRIP001      {
//STRIP001          if( aRct.Intersection( aRect ).IsEmpty() )
//STRIP001              return;
//STRIP001             aClip.ChgClip( aRect, pTxtFrm );
//STRIP001      }
//STRIP001  }
//STRIP001  const Color aOldCol( pSh->GetOut()->GetLineColor() );
//STRIP001  pSh->GetOut()->SetLineColor( SW_MOD()->GetRedlineMarkColor() );
//STRIP001
//STRIP001     if ( pTxtFrm->IsVertical() )
//STRIP001     {
//STRIP001         pTxtFrm->SwitchHorizontalToVertical( aStart );
//STRIP001         pTxtFrm->SwitchHorizontalToVertical( aEnd );
//STRIP001     }
//STRIP001
//STRIP001  pSh->GetOut()->DrawLine( aStart, aEnd );
//STRIP001  pSh->GetOut()->SetLineColor( aOldCol );
//STRIP001 }

//STRIP001 void SwTxtFrm::PaintExtraData( const SwRect &rRect ) const
//STRIP001 {
//STRIP001  if( Frm().Top() > rRect.Bottom() || Frm().Bottom() < rRect.Top() )
//STRIP001      return;
//STRIP001  const SwTxtNode& rTxtNode = *GetTxtNode();
//STRIP001     const SwDoc* pDoc = rTxtNode.GetDoc();
//STRIP001     const SwLineNumberInfo &rLineInf = pDoc->GetLineNumberInfo();
//STRIP001  const SwFmtLineNumber &rLineNum = GetAttrSet()->GetLineNumber();
//STRIP001  sal_Bool bLineNum = !IsInTab() && rLineInf.IsPaintLineNumbers() &&
//STRIP001             ( !IsInFly() || rLineInf.IsCountInFlys() ) && rLineNum.IsCount();
//STRIP001  SwHoriOrient eHor = (SwHoriOrient)SW_MOD()->GetRedlineMarkPos();
//STRIP001     if( eHor != HORI_NONE && !::IsShowChanges( pDoc->GetRedlineMode() ) )
//STRIP001         eHor = HORI_NONE;
//STRIP001  sal_Bool bRedLine = eHor != HORI_NONE;
//STRIP001  if ( bLineNum || bRedLine )
//STRIP001  {
//STRIP001      if( IsLocked() || IsHiddenNow() || !Prt().Height() )
//STRIP001          return;
//STRIP001      ViewShell *pSh = GetShell();
//STRIP001
//STRIP001         SWAP_IF_NOT_SWAPPED( this )
//STRIP001         SwRect rOldRect( rRect );
//STRIP001
//STRIP001         if ( IsVertical() )
//STRIP001             SwitchVerticalToHorizontal( (SwRect&)rRect );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         SwLayoutModeModifier aLayoutModeModifier( *pSh->GetOut() );
//STRIP001         aLayoutModeModifier.Modify( sal_False );
//STRIP001 #endif
//STRIP001
//STRIP001      SwExtraPainter aExtra( this, pSh, rLineInf, rRect,
//STRIP001             rLineNum.GetStartValue(), eHor, bLineNum );
//STRIP001
//STRIP001      if( HasPara() )
//STRIP001      {
//STRIP001          SwTxtFrmLocker aLock((SwTxtFrm*)this);
//STRIP001
//STRIP001          SwTxtLineAccess aAccess( (SwTxtFrm*)this );
//STRIP001          SwParaPortion *pPara = aAccess.GetPara();
//STRIP001
//STRIP001             SwTxtPaintInfo aInf( (SwTxtFrm*)this, rRect );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001             aLayoutModeModifier.Modify( sal_False );
//STRIP001 #endif
//STRIP001
//STRIP001          SwTxtPainter  aLine( (SwTxtFrm*)this, &aInf );
//STRIP001          sal_Bool bNoDummy = !aLine.GetNext(); // Nur eine Leerzeile!
//STRIP001
//STRIP001          while( aLine.Y() + aLine.GetLineHeight() <= rRect.Top() )
//STRIP001          {
//STRIP001              if( !aLine.GetCurr()->IsDummy() &&
//STRIP001                  ( rLineInf.IsCountBlankLines() ||
//STRIP001                    aLine.GetCurr()->HasCntnt() ) )
//STRIP001                  aExtra.IncLineNr();
//STRIP001              if( !aLine.Next() )
//STRIP001                 {
//STRIP001                     (SwRect&)rRect = rOldRect;
//STRIP001                     UNDO_SWAP( this )
//STRIP001                     return;
//STRIP001                 }
//STRIP001          }
//STRIP001
//STRIP001          long nBottom = rRect.Bottom();
//STRIP001
//STRIP001          sal_Bool bNoPrtLine;
//STRIP001          if( !( bNoPrtLine = 0 == GetMinPrtLine() ) )
//STRIP001          {
//STRIP001              while ( aLine.Y() < GetMinPrtLine() )
//STRIP001              {
//STRIP001                  if( ( rLineInf.IsCountBlankLines() || aLine.GetCurr()->HasCntnt() )
//STRIP001                      && !aLine.GetCurr()->IsDummy() )
//STRIP001                      aExtra.IncLineNr();
//STRIP001                  if( !aLine.Next() )
//STRIP001                      break;
//STRIP001              }
//STRIP001              bNoPrtLine = aLine.Y() >= GetMinPrtLine();
//STRIP001          }
//STRIP001          if( bNoPrtLine )
//STRIP001          {
//STRIP001              do
//STRIP001              {
//STRIP001                  if( bNoDummy || !aLine.GetCurr()->IsDummy() )
//STRIP001                  {
//STRIP001                      sal_Bool bRed = bRedLine && aLine.GetCurr()->HasRedline();
//STRIP001                      if( rLineInf.IsCountBlankLines() || aLine.GetCurr()->HasCntnt() )
//STRIP001                      {
//STRIP001                          if( bLineNum &&
//STRIP001                              ( aExtra.HasNumber() || aExtra.HasDivider() ) )
//STRIP001                          {
//STRIP001                              KSHORT nTmpHeight, nTmpAscent;
//STRIP001                              aLine.CalcAscentAndHeight( nTmpAscent, nTmpHeight );
//STRIP001                              aExtra.PaintExtra( aLine.Y(), nTmpAscent,
//STRIP001                                  nTmpHeight, bRed );
//STRIP001                              bRed = sal_False;
//STRIP001                          }
//STRIP001                          aExtra.IncLineNr();
//STRIP001                      }
//STRIP001                      if( bRed )
//STRIP001                          aExtra.PaintRedline( aLine.Y(), aLine.GetLineHeight() );
//STRIP001                  }
//STRIP001              } while( aLine.Next() && aLine.Y() <= nBottom );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             bRedLine &= ( MSHRT_MAX!=pDoc->GetRedlinePos(rTxtNode) );
//STRIP001
//STRIP001          if( bLineNum && rLineInf.IsCountBlankLines() &&
//STRIP001              ( aExtra.HasNumber() || aExtra.HasDivider() ) )
//STRIP001          {
//STRIP001              aExtra.PaintExtra( Frm().Top()+Prt().Top(), aExtra.GetFont()
//STRIP001                  ->GetAscent( pSh, pSh->GetOut() ), Prt().Height(), bRedLine );
//STRIP001          }
//STRIP001          else if( bRedLine )
//STRIP001              aExtra.PaintRedline( Frm().Top()+Prt().Top(), Prt().Height() );
//STRIP001      }
//STRIP001
//STRIP001         (SwRect&)rRect = rOldRect;
//STRIP001         UNDO_SWAP( this )
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                      SwTxtFrm::Paint()
 *************************************************************************/

/*N*/ SwRect SwTxtFrm::Paint()
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   const SwTwips nDbgY = Frm().Top();
/*N*/ #endif
/*N*/
/*N*/   // finger layout
/*N*/   ASSERT( GetValidPosFlag(), "+SwTxtFrm::Paint: no Calc()" );
/*N*/
/*N*/   SwRect aRet( Prt() );
/*N*/   if ( IsEmpty() || !HasPara() )
/*N*/       aRet += Frm().Pos();
/*N*/   else
/*N*/   {
/*N*/       // AMA: Wir liefern jetzt mal das richtige Repaintrechteck zurueck,
/*N*/       //      d.h. als linken Rand den berechneten PaintOfst!
/*N*/       SwRepaint *pRepaint = GetPara()->GetRepaint();
/*N*/       long l;
/*N*/       if( pRepaint->GetOfst() )
/*N*/           pRepaint->Left( pRepaint->GetOfst() );
/*N*/
/*N*/       l = pRepaint->GetRightOfst();
/*N*/       if( l && ( pRepaint->GetOfst() || l > pRepaint->Right() ) )
/*N*/            pRepaint->Right( l );
/*N*/       pRepaint->SetOfst( 0 );
/*N*/       aRet = *pRepaint;
/*N*/
/*N*/ #ifdef BIDI
/*N*/         if ( IsRightToLeft() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/             SwitchLTRtoRTL( aRet );
/*N*/ #endif
/*N*/         if ( IsVertical() )
/*N*/             SwitchHorizontalToVertical( aRet );
/*N*/   }
/*N*/   ResetRepaint();
/*N*/
/*N*/     return aRet;
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::Paint()
 *************************************************************************/

//STRIP001 sal_Bool SwTxtFrm::PaintEmpty( const SwRect &rRect, sal_Bool bCheck ) const
//STRIP001 {
//STRIP001  ViewShell *pSh = GetShell();
//STRIP001  if( pSh && ( pSh->GetViewOptions()->IsParagraph() || bInitFont ) )
//STRIP001  {
//STRIP001      bInitFont = sal_False;
//STRIP001      SwTxtFly aTxtFly( this );
//STRIP001      aTxtFly.SetTopRule();
//STRIP001      SwRect aRect;
//STRIP001      if( bCheck && aTxtFly.IsOn() && aTxtFly.IsAnyObj( aRect ) )
//STRIP001          return sal_False;
//STRIP001         else if( pSh->GetWin() )
//STRIP001      {
//STRIP001          SwFont *pFnt;
//STRIP001          const SwTxtNode& rTxtNode = *GetTxtNode();
//STRIP001          if ( rTxtNode.HasSwAttrSet() )
//STRIP001          {
//STRIP001              const SwAttrSet *pAttrSet = &( rTxtNode.GetSwAttrSet() );
//STRIP001                 pFnt = new SwFont( pAttrSet, GetTxtNode()->GetDoc() );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001 //FEATURE::CONDCOLL
//STRIP001 //                   SwFontAccess aFontAccess( GetTxtNode()->GetFmtColl() );
//STRIP001              SwFontAccess aFontAccess( &rTxtNode.GetAnyFmtColl(), pSh );
//STRIP001 //FEATURE::CONDCOLL
//STRIP001              pFnt = new SwFont( *aFontAccess.Get()->GetFont() );
//STRIP001          }
//STRIP001
//STRIP001          const SwDoc* pDoc = rTxtNode.GetDoc();
//STRIP001          if( ::IsShowChanges( pDoc->GetRedlineMode() ) )
//STRIP001          {
//STRIP001              MSHORT nRedlPos = pDoc->GetRedlinePos( rTxtNode );
//STRIP001                 if( MSHRT_MAX != nRedlPos )
//STRIP001                 {
//STRIP001                     SwAttrHandler aAttrHandler;
//STRIP001                     aAttrHandler.Init( GetTxtNode()->GetSwAttrSet(),
//STRIP001                                        *GetTxtNode()->GetDoc(), NULL );
//STRIP001                     SwRedlineItr aRedln( rTxtNode, *pFnt, aAttrHandler, nRedlPos, sal_True );
//STRIP001                 }
//STRIP001          }
//STRIP001
//STRIP001          if( pSh->GetViewOptions()->IsParagraph() && Prt().Height() )
//STRIP001          {
//STRIP001              if( RTL_TEXTENCODING_SYMBOL == pFnt->GetCharSet( SW_LATIN ) &&
//STRIP001                  COMPARE_EQUAL != pFnt->GetName( SW_LATIN ).
//STRIP001                                          CompareToAscii( sBulletFntName ) )
//STRIP001              {
//STRIP001                  pFnt->SetFamily( FAMILY_DONTKNOW, SW_LATIN );
//STRIP001                  pFnt->SetName( String::CreateFromAscii( sBulletFntName ),
//STRIP001                                  SW_LATIN );
//STRIP001                  pFnt->SetStyleName( aEmptyStr, SW_LATIN );
//STRIP001                  pFnt->SetCharSet( RTL_TEXTENCODING_SYMBOL, SW_LATIN );
//STRIP001              }
//STRIP001                 pFnt->SetVertical( 0, IsVertical() );
//STRIP001                 SwFrmSwapper aSwapper( this, sal_True );
//STRIP001                              SwLayoutModeModifier aLayoutModeModifier( *pSh->GetOut() );
//STRIP001                 aLayoutModeModifier.Modify( IsRightToLeft() );
//STRIP001
//STRIP001                 pFnt->Invalidate();
//STRIP001              pFnt->ChgPhysFnt( pSh, pSh->GetOut() );
//STRIP001              Point aPos = Frm().Pos() + Prt().Pos();
//STRIP001
//STRIP001              const SvxLRSpaceItem &rSpace =
//STRIP001                  GetTxtNode()->GetSwAttrSet().GetLRSpace();
//STRIP001
//STRIP001                 if ( rSpace.GetTxtFirstLineOfst() > 0 )
//STRIP001                     aPos.X() += rSpace.GetTxtFirstLineOfst();
//STRIP001
//STRIP001              SwSaveClip *pClip;
//STRIP001              if( IsUndersized() )
//STRIP001              {
//STRIP001                  pClip = new SwSaveClip( pSh->GetOut() );
//STRIP001                  pClip->ChgClip( rRect );
//STRIP001              }
//STRIP001              else
//STRIP001                     pClip = NULL;
//STRIP001
//STRIP001                 aPos.Y() += pFnt->GetAscent( pSh, pSh->GetOut() );
//STRIP001
//STRIP001                 if ( GetTxtNode()->GetSwAttrSet().GetParaGrid().GetValue() &&
//STRIP001                      IsInDocBody() )
//STRIP001                 {
//STRIP001                     GETGRID( FindPageFrm() )
//STRIP001                     if ( pGrid )
//STRIP001                     {
//STRIP001                         // center character in grid line
//STRIP001                         aPos.Y() += ( pGrid->GetBaseHeight() -
//STRIP001                                       pFnt->GetHeight( pSh, pSh->GetOut() ) ) / 2;
//STRIP001
//STRIP001                         if ( ! pGrid->GetRubyTextBelow() )
//STRIP001                             aPos.Y() += pGrid->GetRubyHeight();
//STRIP001                     }
//STRIP001                 }
//STRIP001
//STRIP001                 const XubString aTmp( CH_PAR );
//STRIP001                 SwDrawTextInfo aDrawInf( pSh, *pSh->GetOut(), 0, aTmp, 0, 1 );
//STRIP001              aDrawInf.SetLeft( rRect.Left() );
//STRIP001              aDrawInf.SetRight( rRect.Right() );
//STRIP001              aDrawInf.SetPos( aPos );
//STRIP001              aDrawInf.SetSpace( 0 );
//STRIP001                 aDrawInf.SetKanaComp( 0 );
//STRIP001                 aDrawInf.SetWrong( NULL );
//STRIP001                 aDrawInf.SetFrm( this );
//STRIP001                 aDrawInf.SetFont( pFnt );
//STRIP001                 aDrawInf.SetSnapToGrid( sal_False );
//STRIP001
//STRIP001              pFnt->_DrawText( aDrawInf );
//STRIP001              delete pClip;
//STRIP001          }
//STRIP001          delete pFnt;
//STRIP001          return sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      return sal_True;
//STRIP001  return sal_False;
//STRIP001 }

/*************************************************************************
 *                      SwTxtFrm::Paint()
 *************************************************************************/

//STRIP001 void SwTxtFrm::Paint(const SwRect &rRect ) const
//STRIP001 {
//STRIP001  ResetRepaint();
//STRIP001  DBG_LOOP_RESET;
//STRIP001  if( !IsEmpty() || !PaintEmpty( rRect, sal_True ) )
//STRIP001  {
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      const SwTwips nDbgY = Frm().Top();
//STRIP001 #endif
//STRIP001
//STRIP001 #ifdef DBGTXT
//STRIP001      if( IsDbg( this ) )
//STRIP001          DBTXTFRM << "Paint()" << endl;
//STRIP001 #endif
//STRIP001         if( IsLocked() || IsHiddenNow() || ! Prt().HasArea() )
//STRIP001             return;
//STRIP001
//STRIP001      //Kann gut sein, dass mir der IdleCollector mir die gecachten
//STRIP001      //Informationen entzogen hat.
//STRIP001      if( !HasPara() )
//STRIP001      {
//STRIP001          ASSERT( GetValidPosFlag(), "+SwTxtFrm::Paint: no Calc()" );
//STRIP001          ((SwTxtFrm*)this)->GetFormatted();
//STRIP001          if( IsEmpty() )
//STRIP001          {
//STRIP001              PaintEmpty( rRect, sal_False );
//STRIP001              return;
//STRIP001          }
//STRIP001          if( !HasPara() )
//STRIP001          {
//STRIP001              ASSERT( !this, "+SwTxtFrm::Paint: missing format information" );
//STRIP001              return;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Waehrend wir painten, wollen wir nicht gestoert werden.
//STRIP001      // Aber erst hinter dem Format() !
//STRIP001      SwTxtFrmLocker aLock((SwTxtFrm*)this);
//STRIP001
//STRIP001      //Hier wird ggf. nur der Teil des TxtFrm ausgegeben, der sich veraendert
//STRIP001      //hat und der in dem Bereich liegt, dessen Ausgabe angefordert wurde.
//STRIP001      //Man kann jetzt auf die Idee kommen, dass der Bereich rRect ausgegeben
//STRIP001      //werden _muss_ obwohl rRepaint gesetzt ist; in der Tat kann dieses
//STRIP001      //Problem nicht formal vermieden werden. Gluecklicherweise koennen
//STRIP001      //wir davon ausgehen, dass rRepaint immer dann leer ist, wenn der Frm
//STRIP001      //komplett gepainted werden muss.
//STRIP001      SwTxtLineAccess aAccess( (SwTxtFrm*)this );
//STRIP001      SwParaPortion *pPara = aAccess.GetPara();
//STRIP001
//STRIP001      SwRepaint &rRepaint = *(pPara->GetRepaint());
//STRIP001
//STRIP001      // Das Recycling muss abgeschaltet werden, wenn wir uns im
//STRIP001      // FlyCntFrm befinden, weil ein DrawRect fuer die Retusche der
//STRIP001      // Zeile aufgerufen wird.
//STRIP001      if( rRepaint.GetOfst() )
//STRIP001      {
//STRIP001          const SwFlyFrm *pFly = FindFlyFrm();
//STRIP001          if( pFly && pFly->IsFlyInCntFrm() )
//STRIP001              rRepaint.SetOfst( 0 );
//STRIP001      }
//STRIP001
//STRIP001      // Hier holen wir uns den String fuer die Ausgabe, besonders
//STRIP001      // die Laenge ist immer wieder interessant.
//STRIP001
//STRIP001         // Rectangle
//STRIP001         ASSERT( ! IsSwapped(), "A frame is swapped before Paint" );
//STRIP001         SwRect aOldRect( rRect );
//STRIP001
//STRIP001         SWAP_IF_NOT_SWAPPED( this )
//STRIP001
//STRIP001         if ( IsVertical() )
//STRIP001             SwitchVerticalToHorizontal( (SwRect&)rRect );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if ( IsRightToLeft() )
//STRIP001             SwitchRTLtoLTR( (SwRect&)rRect );
//STRIP001 #endif
//STRIP001
//STRIP001         ViewShell *pSh = GetShell();
//STRIP001      SwTxtPaintInfo aInf( (SwTxtFrm*)this, rRect );
//STRIP001      aInf.SetWrongList( ( (SwTxtNode*)GetTxtNode() )->GetWrong() );
//STRIP001      aInf.GetTxtFly()->SetTopRule();
//STRIP001
//STRIP001      SwTxtPainter  aLine( (SwTxtFrm*)this, &aInf );
//STRIP001      // Eine Optimierung, die sich lohnt: wenn kein freifliegender Frame
//STRIP001      // in unsere Zeile ragt, schaltet sich der SwTxtFly einfach ab:
//STRIP001      aInf.GetTxtFly()->Relax();
//STRIP001
//STRIP001      OutputDevice *pOut = aInf.GetOut();
//STRIP001      const sal_Bool bOnWin = pSh->GetWin() != 0;
//STRIP001
//STRIP001      SwSaveClip aClip( bOnWin || IsUndersized() ? pOut : 0 );
//STRIP001
//STRIP001      // Ausgabeschleife: Fuer jede Zeile ... (die noch zu sehen ist) ...
//STRIP001      // rRect muss angepasst werden (Top+1, Bottom-1), weil der Iterator
//STRIP001      // die Zeilen nahtlos aneinanderfuegt.
//STRIP001      aLine.TwipsToLine( rRect.Top() + 1 );
//STRIP001      long nBottom = rRect.Bottom();
//STRIP001
//STRIP001      sal_Bool bNoPrtLine;
//STRIP001      if( !( bNoPrtLine = 0 == GetMinPrtLine() ) )
//STRIP001      {
//STRIP001          while ( aLine.Y() < GetMinPrtLine() && aLine.Next() )
//STRIP001              ;
//STRIP001          bNoPrtLine = aLine.Y() >= GetMinPrtLine();
//STRIP001      }
//STRIP001      if( bNoPrtLine )
//STRIP001      {
//STRIP001          do
//STRIP001          {   DBG_LOOP;
//STRIP001              aLine.DrawTextLine( rRect, aClip, IsUndersized() );
//STRIP001
//STRIP001          } while( aLine.Next() && aLine.Y() <= nBottom );
//STRIP001      }
//STRIP001
//STRIP001      // Einmal reicht:
//STRIP001      if( aLine.IsPaintDrop() )
//STRIP001      {
//STRIP001 #if NIE
//STRIP001          if( !bRetouche )
//STRIP001          {
//STRIP001              const SvxBrushItem *pItem; SwRect aOrigRect;
//STRIP001              GetBackgroundBrush( pItem, aOrigRect, sal_False, sal_True );
//STRIP001              aInf.SetBack( pItem, aOrigRect );
//STRIP001          }
//STRIP001 #endif
//STRIP001          aLine.PaintDropPortion();
//STRIP001      }
//STRIP001
//STRIP001 #ifdef USED
//STRIP001      if( pSh && pSh->GetViewOptions()->IsTest2() )
//STRIP001          aInf.GetTxtFly()->ShowContour( pOut );
//STRIP001 #endif
//STRIP001
//STRIP001      if( rRepaint.HasArea() )
//STRIP001          rRepaint.Clear();
//STRIP001
//STRIP001         UNDO_SWAP( this )
//STRIP001         (SwRect&)rRect = aOldRect;
//STRIP001
//STRIP001         ASSERT( ! IsSwapped(), "A frame is swapped after Paint" );
//STRIP001     }
//STRIP001 }

//STRIP001 void SwTxtFrm::CriticalLines( const OutputDevice& rOut, SwStripes &rStripes,
//STRIP001  long nOffs)
//STRIP001 {
//STRIP001     ASSERT( ! IsVertical() || ! IsSwapped(),
//STRIP001         "SwTxtFrm::CriticalLines with swapped frame" );
//STRIP001     SWRECTFN( this )
//STRIP001     long nFrmHeight;
//STRIP001
//STRIP001  GetFormatted();
//STRIP001  if( HasPara() )
//STRIP001  {
//STRIP001         const long nTopMargin = (this->*fnRect->fnGetTopMargin)();
//STRIP001         SwStripe aStripe( (Frm().*fnRect->fnGetTop)(), nTopMargin );
//STRIP001         if ( nTopMargin )
//STRIP001      {
//STRIP001          rStripes.Insert( aStripe, rStripes.Count() );
//STRIP001             // OD 06.11.2002 #104171#,#103931# - consider vertical layout
//STRIP001             if ( bVert )
//STRIP001                 aStripe.Y() -= nTopMargin;
//STRIP001             else
//STRIP001                 // OD 06.11.2002 #104171#,#103931# - *add* top margin to Y.
//STRIP001                 aStripe.Y() += nTopMargin;
//STRIP001      }
//STRIP001      SwLineLayout* pLay = GetPara();
//STRIP001      do
//STRIP001      {
//STRIP001             SwTwips nBase = aStripe.GetY() +
//STRIP001                            ( bVert ? -pLay->GetAscent() : pLay->GetAscent() );
//STRIP001
//STRIP001             long nLogToPixBase, nLogToPixSum, nLogToPixOffs;
//STRIP001
//STRIP001             if ( bVert )
//STRIP001             {
//STRIP001                 nLogToPixBase = rOut.LogicToPixel( Point( nBase, 0 ) ).X();
//STRIP001                 nLogToPixSum = rOut.LogicToPixel( Point( nBase + nOffs, 0 ) ).X();
//STRIP001                 nLogToPixOffs = -rOut.LogicToPixel( Size( nOffs, 0 ) ).Width();
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 nLogToPixBase = rOut.LogicToPixel( Point( 0, nBase ) ).Y();
//STRIP001                 nLogToPixSum = rOut.LogicToPixel( Point( 0, nBase - nOffs ) ).Y();
//STRIP001                 nLogToPixOffs = rOut.LogicToPixel( Size( 0, nOffs ) ).Height();
//STRIP001             }
//STRIP001
//STRIP001             if( nLogToPixBase != nLogToPixSum + nLogToPixOffs )
//STRIP001          {
//STRIP001              aStripe.Height() = pLay->GetRealHeight();
//STRIP001              rStripes.Insert( aStripe, rStripes.Count() );
//STRIP001          }
//STRIP001             aStripe.Y() += ( bVert ? -pLay->GetRealHeight() :
//STRIP001                                       pLay->GetRealHeight() );
//STRIP001          pLay = pLay->GetNext();
//STRIP001      } while( pLay );
//STRIP001
//STRIP001         const long nBottomMargin = (this->*fnRect->fnGetBottomMargin)();
//STRIP001         if( nBottomMargin )
//STRIP001      {
//STRIP001
//STRIP001             aStripe.Height() = nBottomMargin;
//STRIP001          rStripes.Insert( aStripe, rStripes.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001     else if( nFrmHeight = (Frm().*fnRect->fnGetHeight)() )
//STRIP001         rStripes.Insert( SwStripe( (Frm().*fnRect->fnGetTop)(), nFrmHeight ),
//STRIP001                          rStripes.Count() );
//STRIP001 }
}
