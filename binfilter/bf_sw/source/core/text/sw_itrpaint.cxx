/*************************************************************************
 *
 *  $RCSfile: sw_itrpaint.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:20 $
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

#include "hintids.hxx"
#include "flyfrm.hxx"     // SwFlyInCntFrm
#include "viewopt.hxx"  // SwViewOptions
#include "errhdl.hxx"
#include "txtatr.hxx"  // SwINetFmt

#ifndef _SV_MULTISEL_HXX //autogen
#include <tools/multisel.hxx>
#endif
#ifndef _SVX_ESCPITEM_HXX //autogen
#include <bf_svx/escpitem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif

#ifndef _TXTINET_HXX //autogen
#include <txtinet.hxx>
#endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>      // SwField
#endif
#ifndef _FMTHBSH_HXX //autogen
#include <fmthbsh.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> // SwPageDesc
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif

#include "flyfrms.hxx"
#include "viewsh.hxx"
#include "txtcfg.hxx"
#include "itrpaint.hxx"
#include "txtfrm.hxx"   // pFrm
#include "txtfly.hxx"
#include "swfont.hxx"
#include "txtpaint.hxx"
#include "portab.hxx"   // SwTabPortion::IsFilled
#include "porfly.hxx"     // SwFlyCntPortion
#include "porfld.hxx"   // SwGrfNumPortion
#include "frmfmt.hxx"   // LRSpace
#include "txatbase.hxx" // SwTxtAttr
#include "charfmt.hxx"  // SwFmtCharFmt
#include "redlnitr.hxx" // SwRedlineItr
#include "porrst.hxx"   // SwArrowPortion
#include "pormulti.hxx"
namespace binfilter {

/*************************************************************************
 *                  IsUnderlineBreak
 *
 * Returns, if we have an underline breaking situation
 * Adding some more conditions here means you also have to change them
 * in SwTxtPainter::CheckSpecialUnderline
 *************************************************************************/
/*N*/ sal_Bool IsUnderlineBreak( const SwLinePortion& rPor, const SwFont& rFnt )
/*N*/ {
/*N*/     return UNDERLINE_NONE == rFnt.GetUnderline() ||
/*N*/            rPor.IsFlyPortion() || rPor.IsFlyCntPortion() ||
/*N*/            rPor.IsBreakPortion() || rPor.IsMarginPortion() ||
/*N*/            rPor.IsHolePortion() ||
/*N*/           ( rPor.IsMultiPortion() && ! ((SwMultiPortion&)rPor).IsBidi() ) ||
/*N*/            rFnt.GetEscapement() < 0 || rFnt.IsWordLineMode() ||
/*N*/            SVX_CASEMAP_KAPITAELCHEN == rFnt.GetCaseMap();
/*N*/ }

/*************************************************************************
 *                  SwTxtPainter::CtorInit()
 *************************************************************************/
/*N*/ void SwTxtPainter::CtorInit( SwTxtFrm *pFrm, SwTxtPaintInfo *pNewInf )
/*N*/ {
/*N*/   SwTxtCursor::CtorInit( pFrm, pNewInf );
/*N*/   pInf = pNewInf;
/*N*/   SwFont *pFnt = GetFnt();
/*N*/   GetInfo().SetFont( pFnt );
/*N*/ #ifndef PRODUCT
/*N*/   if( ALIGN_BASELINE != pFnt->GetAlign() )
/*N*/   {
/*?*/       ASSERT( ALIGN_BASELINE == pFnt->GetAlign(),
/*?*/               "+SwTxtPainter::CTOR: font alignment revolution" );
/*?*/       pFnt->SetAlign( ALIGN_BASELINE );
/*N*/   }
/*N*/ #endif
/*N*/   bPaintDrop = sal_False;
/*N*/ }


/*************************************************************************
 *                    SwTxtPainter::CalcPaintOfst()
 *************************************************************************/
//STRIP001 SwLinePortion *SwTxtPainter::CalcPaintOfst( const SwRect &rPaint )
//STRIP001 //STRIP001 {
//STRIP001  SwLinePortion *pPor = pCurr->GetFirstPortion();
//STRIP001  GetInfo().SetPaintOfst( 0 );
//STRIP001  SwTwips nPaintOfst = rPaint.Left();
//STRIP001
//STRIP001  // nPaintOfst wurde exakt auf das Ende eingestellt, deswegen <=
//STRIP001  // nPaintOfst ist dokumentglobal, deswegen nLeftMar aufaddieren
//STRIP001  // const KSHORT nLeftMar = KSHORT(GetLeftMargin());
//STRIP001  // 8310: painten von LineBreaks in leeren Zeilen.
//STRIP001  if( nPaintOfst && pCurr->Width() )
//STRIP001  {
//STRIP001      SwLinePortion *pLast = 0;
//STRIP001      // 7529 und 4757: nicht <= nPaintOfst
//STRIP001      while( pPor && GetInfo().X() + pPor->Width() + (pPor->Height()/2)
//STRIP001                     < nPaintOfst )
//STRIP001      {
//STRIP001          DBG_LOOP;
//STRIP001          if( pPor->InSpaceGrp() && GetInfo().GetSpaceAdd() )
//STRIP001          {
//STRIP001              long nTmp = GetInfo().X() +pPor->Width() +
//STRIP001                  pPor->CalcSpacing( GetInfo().GetSpaceAdd(), GetInfo() );
//STRIP001              if( nTmp + (pPor->Height()/2) >= nPaintOfst )
//STRIP001                  break;
//STRIP001              GetInfo().X( nTmp );
//STRIP001              GetInfo().SetIdx( GetInfo().GetIdx() + pPor->GetLen() );
//STRIP001          }
//STRIP001          else
//STRIP001              pPor->Move( GetInfo() );
//STRIP001          pLast = pPor;
//STRIP001          pPor = pPor->GetPortion();
//STRIP001      }
//STRIP001
//STRIP001 #ifndef USED
//STRIP001      // 7529: bei PostIts auch pLast returnen.
//STRIP001      if( pLast && !pLast->Width() && pLast->IsPostItsPortion() )
//STRIP001      {
//STRIP001          pPor = pLast;
//STRIP001          GetInfo().SetIdx( GetInfo().GetIdx() - pPor->GetLen() );
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001  return pPor;
//STRIP001 }

/*************************************************************************
 *                    SwTxtPainter::DrawTextLine()
 *
 * Es gibt zwei Moeglichkeiten bei transparenten Font auszugeben:
 * 1) DrawRect auf die ganze Zeile und die DrawText hinterher
 *    (objektiv schnell, subjektiv langsam).
 * 2) Fuer jede Portion ein DrawRect mit anschliessendem DrawText
 *    ausgefuehrt (objektiv langsam, subjektiv schnell).
 * Da der User in der Regel subjektiv urteilt, wird die 2. Methode
 * als Default eingestellt.
 *************************************************************************/
//STRIP001 void SwTxtPainter::DrawTextLine( const SwRect &rPaint, SwSaveClip &rClip,
//STRIP001                               const sal_Bool bUnderSz )
//STRIP001 {
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001 //    USHORT nFntHeight = GetInfo().GetFont()->GetHeight( GetInfo().GetVsh(), GetInfo().GetOut() );
//STRIP001 //    USHORT nFntAscent = GetInfo().GetFont()->GetAscent( GetInfo().GetVsh(), GetInfo().GetOut() );
//STRIP001 #endif
//STRIP001
//STRIP001     // Adjustierung ggf. nachholen
//STRIP001  GetAdjusted();
//STRIP001  GetInfo().SetSpaceAdd( pCurr->GetpSpaceAdd() );
//STRIP001  GetInfo().ResetSpaceIdx();
//STRIP001     GetInfo().SetKanaComp( pCurr->GetpKanaComp() );
//STRIP001     GetInfo().ResetKanaIdx();
//STRIP001  // Die Groesse des Frames
//STRIP001  GetInfo().SetIdx( GetStart() );
//STRIP001  GetInfo().SetPos( GetTopLeft() );
//STRIP001
//STRIP001  const sal_Bool bDrawInWindow = GetInfo().OnWin();
//STRIP001
//STRIP001  // 6882: Leerzeilen duerfen nicht wegoptimiert werden bei Paragraphzeichen.
//STRIP001  const sal_Bool bEndPor = GetInfo().GetOpt().IsParagraph() && !GetInfo().GetTxt().Len();
//STRIP001
//STRIP001  SwLinePortion *pPor = bEndPor ? pCurr->GetFirstPortion() : CalcPaintOfst( rPaint );
//STRIP001
//STRIP001  // Optimierung!
//STRIP001  const SwTwips nMaxRight = Min( rPaint.Right(), Right() );
//STRIP001  const SwTwips nTmpLeft = GetInfo().X();
//STRIP001  if( !bEndPor && nTmpLeft >= nMaxRight )
//STRIP001      return;
//STRIP001
//STRIP001  // DropCaps!
//STRIP001  // 7538: natuerlich auch auf dem Drucker
//STRIP001  if( !bPaintDrop )
//STRIP001  {
//STRIP001      // 8084: Optimierung, weniger Painten.
//STRIP001      // AMA: Durch 8084 wurde 7538 wiederbelebt!
//STRIP001      // bDrawInWindow entfernt, damit DropCaps auch gedruckt werden
//STRIP001      bPaintDrop = pPor == pCurr->GetFirstPortion()
//STRIP001                   && GetDropLines() >= GetLineNr();
//STRIP001  }
//STRIP001
//STRIP001  KSHORT nTmpHeight, nTmpAscent;
//STRIP001  CalcAscentAndHeight( nTmpAscent, nTmpHeight );
//STRIP001
//STRIP001  // bClip entscheidet darueber, ob geclippt werden muss.
//STRIP001  // Das Ganze muss vor der Retusche stehen
//STRIP001
//STRIP001  sal_Bool bClip = ( bDrawInWindow || bUnderSz ) && !rClip.IsChg();
//STRIP001  if( bClip && pPor )
//STRIP001  {
//STRIP001      // Wenn TopLeft oder BottomLeft der Line ausserhalb liegen,
//STRIP001      // muss geclippt werden. Die Ueberpruefung auf Right() erfolgt
//STRIP001      // in der folgenden Ausgabeschleife...
//STRIP001
//STRIP001      if( GetInfo().GetPos().X() < rPaint.Left() ||
//STRIP001          GetInfo().GetPos().Y() < rPaint.Top() ||
//STRIP001          GetInfo().GetPos().Y() + nTmpHeight > rPaint.Top() + rPaint.Height() )
//STRIP001      {
//STRIP001          bClip = sal_False;
//STRIP001             rClip.ChgClip( rPaint, pFrm, pCurr->HasUnderscore() );
//STRIP001      }
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      static sal_Bool bClipAlways = sal_False;
//STRIP001      if( bClip && bClipAlways )
//STRIP001      {   bClip = sal_False;
//STRIP001          rClip.ChgClip( rPaint );
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  // Alignment:
//STRIP001  sal_Bool bPlus = sal_False;
//STRIP001  OutputDevice *pOut = GetInfo().GetOut();
//STRIP001  Point aPnt1( nTmpLeft, GetInfo().GetPos().Y() );
//STRIP001  if ( aPnt1.X() < rPaint.Left() )
//STRIP001      aPnt1.X() = rPaint.Left();
//STRIP001  if ( aPnt1.Y() < rPaint.Top() )
//STRIP001      aPnt1.Y() = rPaint.Top();
//STRIP001  Point aPnt2( GetInfo().GetPos().X() + nMaxRight - GetInfo().X(),
//STRIP001               GetInfo().GetPos().Y() + nTmpHeight );
//STRIP001  if ( aPnt2.X() > rPaint.Right() )
//STRIP001      aPnt2.X() = rPaint.Right();
//STRIP001  if ( aPnt2.Y() > rPaint.Bottom() )
//STRIP001  {
//STRIP001      aPnt2.Y() = rPaint.Bottom();
//STRIP001      bPlus = sal_True;
//STRIP001  }
//STRIP001
//STRIP001  const SwRect aLineRect( aPnt1, aPnt2 );
//STRIP001
//STRIP001  if( pCurr->IsClipping() )
//STRIP001  {
//STRIP001         rClip.ChgClip( aLineRect, pFrm );
//STRIP001      bClip = sal_False;
//STRIP001  }
//STRIP001
//STRIP001  if( !pPor && !bEndPor )
//STRIP001  {
//STRIP001 #ifdef DBGTXT
//STRIP001      aDbstream << "PAINTER: done nothing" << endl;
//STRIP001 #endif
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  // Baseline-Ausgabe auch bei nicht-TxtPortions (vgl. TabPor mit Fill)
//STRIP001     // if no special vertical alignment is used,
//STRIP001     // we calculate Y value for the whole line
//STRIP001     GETGRID( GetTxtFrm()->FindPageFrm() )
//STRIP001     const sal_Bool bAdjustBaseLine =
//STRIP001         GetLineInfo().HasSpecialAlign( GetTxtFrm()->IsVertical() ) ||
//STRIP001                                      ( 0 != pGrid );
//STRIP001     const SwTwips nLineBaseLine = GetInfo().GetPos().Y() + nTmpAscent;
//STRIP001     if ( ! bAdjustBaseLine )
//STRIP001         GetInfo().Y( nLineBaseLine );
//STRIP001
//STRIP001  // 7529: PostIts prepainten
//STRIP001  if( GetInfo().OnWin() && pPor && !pPor->Width() )
//STRIP001  {
//STRIP001      SeekAndChg( GetInfo() );
//STRIP001
//STRIP001         if( bAdjustBaseLine )
//STRIP001         {
//STRIP001             const SwTwips nOldY = GetInfo().Y();
//STRIP001
//STRIP001             GetInfo().Y( GetInfo().GetPos().Y() + AdjustBaseLine( *pCurr, 0,
//STRIP001                 GetInfo().GetFont()->GetHeight( GetInfo().GetVsh(), pOut ),
//STRIP001                 GetInfo().GetFont()->GetAscent( GetInfo().GetVsh(), pOut )
//STRIP001             ) );
//STRIP001
//STRIP001             pPor->PrePaint( GetInfo(), pPor );
//STRIP001             GetInfo().Y( nOldY );
//STRIP001         }
//STRIP001         else
//STRIP001             pPor->PrePaint( GetInfo(), pPor );
//STRIP001  }
//STRIP001
//STRIP001  // 7923: EndPortions geben auch Zeichen aus, deswegen den Fnt wechseln!
//STRIP001  if( bEndPor )
//STRIP001      SeekStartAndChg( GetInfo() );
//STRIP001
//STRIP001  sal_Bool bRest = pCurr->IsRest();
//STRIP001  sal_Bool bFirst = sal_True;
//STRIP001
//STRIP001  SwArrowPortion *pArrow = NULL;
//STRIP001     // Reference portion for the paragraph end portion
//STRIP001     SwLinePortion* pEndTempl = pCurr->GetFirstPortion();
//STRIP001
//STRIP001  while( pPor )
//STRIP001  {
//STRIP001      DBG_LOOP;
//STRIP001      sal_Bool bSeeked = sal_True;
//STRIP001      GetInfo().SetLen( pPor->GetLen() );
//STRIP001
//STRIP001         const SwTwips nOldY = GetInfo().Y();
//STRIP001
//STRIP001         if ( bAdjustBaseLine )
//STRIP001         {
//STRIP001             GetInfo().Y( GetInfo().GetPos().Y() + AdjustBaseLine( *pCurr, pPor ) );
//STRIP001
//STRIP001             // we store the last portion, because a possible paragraph
//STRIP001             // end character has the same font as this portion
//STRIP001             // (only in special vertical alignment case, otherwise the first
//STRIP001             // portion of the line is used)
//STRIP001             if ( pPor->Width() && pPor->InTxtGrp() )
//STRIP001                 pEndTempl = pPor;
//STRIP001         }
//STRIP001
//STRIP001      // Ein Sonderfall sind GluePortions, die Blanks ausgeben.
//STRIP001
//STRIP001      // 6168: Der Rest einer FldPortion zog sich die Attribute der naechsten
//STRIP001      // Portion an, dies wird durch SeekAndChgBefore vermieden:
//STRIP001      if( ( bRest && pPor->InFldGrp() && !pPor->GetLen() ) )
//STRIP001          SeekAndChgBefore( GetInfo() );
//STRIP001      else if ( pPor->IsQuoVadisPortion() )
//STRIP001      {
//STRIP001          xub_StrLen nOffset = GetInfo().GetIdx();
//STRIP001          SeekStartAndChg( GetInfo(), sal_True );
//STRIP001          if( GetRedln() && pCurr->HasRedline() )
//STRIP001              GetRedln()->Seek( *pFnt, nOffset, 0 );
//STRIP001      }
//STRIP001      else if( pPor->InTxtGrp() || pPor->InFldGrp() || pPor->InTabGrp() )
//STRIP001          SeekAndChg( GetInfo() );
//STRIP001      else if ( !bFirst && pPor->IsBreakPortion() && GetInfo().GetOpt().IsParagraph() )
//STRIP001      {
//STRIP001          // Paragraphzeichen sollten den gleichen Font wie das Zeichen vor
//STRIP001          // haben, es sei denn, es gibt Redlining in dem Absatz.
//STRIP001          if( GetRedln() )
//STRIP001              SeekAndChg( GetInfo() );
//STRIP001          else
//STRIP001              SeekAndChgBefore( GetInfo() );
//STRIP001      }
//STRIP001      else
//STRIP001          bSeeked = sal_False;
//STRIP001
//STRIP001 //       bRest = sal_False;
//STRIP001
//STRIP001      // Wenn das Ende der Portion hinausragt, wird geclippt.
//STRIP001      // Es wird ein Sicherheitsabstand von Height-Halbe aufaddiert,
//STRIP001      // damit die TTF-"f" nicht im Seitenrand haengen...
//STRIP001         if( bClip &&
//STRIP001             GetInfo().X() + pPor->Width() + ( pPor->Height() / 2 ) > nMaxRight )
//STRIP001         {
//STRIP001             bClip = sal_False;
//STRIP001             rClip.ChgClip( rPaint, pFrm, pCurr->HasUnderscore() );
//STRIP001      }
//STRIP001
//STRIP001      // Portions, die "unter" dem Text liegen wie PostIts
//STRIP001      SwLinePortion *pNext = pPor->GetPortion();
//STRIP001         if( GetInfo().OnWin() && pNext && !pNext->Width() )
//STRIP001      {
//STRIP001          // Fix 11289: Felder waren hier ausgeklammert wg. Last!=Owner beim
//STRIP001          // Laden von Brief.sdw. Jetzt sind die Felder wieder zugelassen,
//STRIP001          // durch bSeeked wird Last!=Owner vermieden.
//STRIP001          if ( !bSeeked )
//STRIP001              SeekAndChg( GetInfo() );
//STRIP001             pNext->PrePaint( GetInfo(), pPor );
//STRIP001      }
//STRIP001
//STRIP001         // We calculate a separate font for underlining.
//STRIP001         CheckSpecialUnderline( pPor, bAdjustBaseLine ? nOldY : 0 );
//STRIP001         SwUnderlineFont* pUnderLineFnt = GetInfo().GetUnderFnt();
//STRIP001         if ( pUnderLineFnt )
//STRIP001         {
//STRIP001             const Point aTmpPoint( GetInfo().X(),
//STRIP001                                    bAdjustBaseLine ?
//STRIP001                                    pUnderLineFnt->GetPos().Y() :
//STRIP001                                    nLineBaseLine );
//STRIP001             pUnderLineFnt->SetPos( aTmpPoint );
//STRIP001         }
//STRIP001
//STRIP001
//STRIP001         // in extended input mode we do not want a common underline font.
//STRIP001         SwUnderlineFont* pOldUnderLineFnt = 0;
//STRIP001         if ( GetRedln() && GetRedln()->ExtOn() )
//STRIP001         {
//STRIP001             pOldUnderLineFnt = GetInfo().GetUnderFnt();
//STRIP001             GetInfo().SetUnderFnt( 0 );
//STRIP001         }
//STRIP001
//STRIP001         if( pPor->IsMultiPortion() )
//STRIP001          PaintMultiPortion( rPaint, (SwMultiPortion&)*pPor );
//STRIP001         else
//STRIP001             pPor->Paint( GetInfo() );
//STRIP001
//STRIP001         // reset underline font
//STRIP001         if ( pOldUnderLineFnt )
//STRIP001             GetInfo().SetUnderFnt( pOldUnderLineFnt );
//STRIP001
//STRIP001         // reset (for special vertical alignment)
//STRIP001         GetInfo().Y( nOldY );
//STRIP001
//STRIP001         if( GetFnt()->IsURL() && pPor->InTxtGrp() )
//STRIP001          GetInfo().NotifyURL( *pPor );
//STRIP001
//STRIP001      bFirst &= !pPor->GetLen();
//STRIP001      if( pNext || !pPor->IsMarginPortion() )
//STRIP001          pPor->Move( GetInfo() );
//STRIP001      if( pPor->IsArrowPortion() && GetInfo().OnWin() && !pArrow )
//STRIP001          pArrow = (SwArrowPortion*)pPor;
//STRIP001
//STRIP001         pPor = !bDrawInWindow && GetInfo().X() > nMaxRight ? 0 : pNext;
//STRIP001  }
//STRIP001
//STRIP001     // delete underline font
//STRIP001     delete GetInfo().GetUnderFnt();
//STRIP001     GetInfo().SetUnderFnt( 0 );
//STRIP001
//STRIP001     // paint remaining stuff
//STRIP001  if( bDrawInWindow )
//STRIP001  {
//STRIP001         // If special vertical alignment is enabled, GetInfo().Y() is the
//STRIP001         // top of the current line. Therefore is has to be adjusted for
//STRIP001         // the painting of the remaining stuff. We first store the old value.
//STRIP001         const SwTwips nOldY = GetInfo().Y();
//STRIP001
//STRIP001         if( !GetNextLine() &&
//STRIP001          GetInfo().GetVsh() && !GetInfo().GetVsh()->IsPreView() &&
//STRIP001          GetInfo().GetOpt().IsParagraph() && !GetTxtFrm()->GetFollow() &&
//STRIP001          GetInfo().GetIdx() >= GetInfo().GetTxt().Len() )
//STRIP001      {
//STRIP001             const SwTmpEndPortion aEnd( *pEndTempl );
//STRIP001             GetFnt()->ChgPhysFnt( GetInfo().GetVsh(), pOut );
//STRIP001
//STRIP001             if ( bAdjustBaseLine )
//STRIP001                 GetInfo().Y( GetInfo().GetPos().Y()
//STRIP001                            + AdjustBaseLine( *pCurr, &aEnd ) );
//STRIP001
//STRIP001             aEnd.Paint( GetInfo() );
//STRIP001             GetInfo().Y( nOldY );
//STRIP001         }
//STRIP001         if( GetInfo().GetVsh() && !GetInfo().GetVsh()->IsPreView() )
//STRIP001         {
//STRIP001             const sal_Bool bNextUndersized =
//STRIP001                 ( GetTxtFrm()->GetNext() &&
//STRIP001                   0 == GetTxtFrm()->GetNext()->Prt().Height() &&
//STRIP001                   GetTxtFrm()->GetNext()->IsTxtFrm() &&
//STRIP001                   ((SwTxtFrm*)GetTxtFrm()->GetNext())->IsUndersized() ) ;
//STRIP001
//STRIP001             if( bUnderSz || bNextUndersized )
//STRIP001          {
//STRIP001                 if ( bAdjustBaseLine )
//STRIP001                     GetInfo().Y( GetInfo().GetPos().Y() + pCurr->GetAscent() );
//STRIP001
//STRIP001                 if( pArrow )
//STRIP001                     GetInfo().DrawRedArrow( *pArrow );
//STRIP001
//STRIP001                 // GetInfo().Y() must be current baseline.
//STRIP001                 SwTwips nDiff = GetInfo().Y() + nTmpHeight - nTmpAscent - GetTxtFrm()->Frm().Bottom();
//STRIP001                 if( ( nDiff > 0 &&
//STRIP001                       ( GetEnd() < GetInfo().GetTxt().Len() ||
//STRIP001                         ( nDiff > nTmpHeight/2 && GetPrevLine() ) ) ) ||
//STRIP001                     nDiff >= 0 && bNextUndersized )
//STRIP001
//STRIP001                 {
//STRIP001                     SwArrowPortion aArrow( GetInfo() );
//STRIP001                     GetInfo().DrawRedArrow( aArrow );
//STRIP001                 }
//STRIP001
//STRIP001                 GetInfo().Y( nOldY );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     if( pCurr->IsClipping() )
//STRIP001         rClip.ChgClip( rPaint, pFrm );
//STRIP001 }

//STRIP001 void SwTxtPainter::CheckSpecialUnderline( const SwLinePortion* pPor,
//STRIP001                                           long nAdjustBaseLine )
//STRIP001 {
//STRIP001     // Check if common underline should not be continued.
//STRIP001     if ( IsUnderlineBreak( *pPor, *pFnt ) )
//STRIP001     {
//STRIP001         // delete underline font
//STRIP001         delete GetInfo().GetUnderFnt();
//STRIP001         GetInfo().SetUnderFnt( 0 );
//STRIP001         return;
//STRIP001     }
//STRIP001
//STRIP001     // If current underline matches the common underline font, we continue
//STRIP001     // to use the common underline font.
//STRIP001     if ( GetInfo().GetUnderFnt() &&
//STRIP001          GetInfo().GetUnderFnt()->GetFont().GetUnderline() ==
//STRIP001          GetFnt()->GetUnderline() )
//STRIP001          return;
//STRIP001
//STRIP001     // calculate the new common underline font
//STRIP001     SwFont* pUnderlineFnt = 0;
//STRIP001     Point aCommonBaseLine;
//STRIP001
//STRIP001     Range aRange( 0, GetInfo().GetTxt().Len() );
//STRIP001     MultiSelection aUnderMulti( aRange );
//STRIP001
//STRIP001     ASSERT( GetFnt() && UNDERLINE_NONE != GetFnt()->GetUnderline(),
//STRIP001             "CheckSpecialUnderline without underlined font" )
//STRIP001     const SwFont* pParaFnt = GetAttrHandler().GetFont();
//STRIP001     if( pParaFnt && pParaFnt->GetUnderline() == GetFnt()->GetUnderline() )
//STRIP001         aUnderMulti.SelectAll();
//STRIP001
//STRIP001     SwTxtAttr* pTxtAttr;
//STRIP001     if( HasHints() )
//STRIP001  {
//STRIP001      sal_Bool bINet = sal_False;
//STRIP001         sal_Bool bUnder = sal_False;
//STRIP001      MSHORT nTmp = 0;
//STRIP001
//STRIP001         while( nTmp < pHints->GetStartCount() )
//STRIP001      {
//STRIP001          pTxtAttr = pHints->GetStart( nTmp++ );
//STRIP001          sal_Bool bUnderSelect;
//STRIP001          switch ( pTxtAttr->Which() )
//STRIP001          {
//STRIP001              case RES_CHRATR_UNDERLINE:
//STRIP001              {
//STRIP001                  bUnder = sal_True;
//STRIP001                     bUnderSelect = pFnt->GetUnderline() == pTxtAttr->GetUnderline().
//STRIP001                                                            GetUnderline();
//STRIP001              }
//STRIP001              break;
//STRIP001              case RES_TXTATR_INETFMT: bINet = sal_True;
//STRIP001              case RES_TXTATR_CHARFMT:
//STRIP001              {
//STRIP001                  SwCharFmt* pFmt;
//STRIP001                  const SfxPoolItem* pItem;
//STRIP001                  if( bINet )
//STRIP001                  {
//STRIP001                      pFmt = ((SwTxtINetFmt*)pTxtAttr)->GetCharFmt();
//STRIP001                      bINet = sal_False;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pFmt = pTxtAttr->GetCharFmt().GetCharFmt();
//STRIP001                  if ( pFmt )
//STRIP001                  {
//STRIP001                      if( SFX_ITEM_SET == pFmt->GetAttrSet().
//STRIP001                          GetItemState( RES_CHRATR_UNDERLINE, sal_True, &pItem ) )
//STRIP001                      {
//STRIP001                             bUnderSelect = pFnt->GetUnderline() ==
//STRIP001                                  ((SvxUnderlineItem*)pItem)->GetUnderline();
//STRIP001                          bUnder = sal_True;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001             if( bUnder )
//STRIP001          {
//STRIP001              xub_StrLen nSt = *pTxtAttr->GetStart();
//STRIP001              xub_StrLen nEnd = *pTxtAttr->GetEnd();
//STRIP001              if( nEnd > nSt )
//STRIP001              {
//STRIP001                  Range aTmp( nSt, nEnd - 1 );
//STRIP001                  if( bUnder )
//STRIP001                      aUnderMulti.Select( aTmp, bUnderSelect );
//STRIP001              }
//STRIP001              bUnder = sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001     }
//STRIP001
//STRIP001     MSHORT i;
//STRIP001     xub_StrLen nIndx = GetInfo().GetIdx();
//STRIP001     long nUnderStart = 0;
//STRIP001     long nUnderEnd = 0;
//STRIP001     MSHORT nCnt = (MSHORT)aUnderMulti.GetRangeCount();
//STRIP001
//STRIP001     // find the underline range the current portion is contained in
//STRIP001     for( i = 0; i < nCnt; ++i )
//STRIP001     {
//STRIP001         const Range& rRange = aUnderMulti.GetRange( i );
//STRIP001         if( nUnderEnd == rRange.Min() )
//STRIP001             nUnderEnd = rRange.Max();
//STRIP001         else if( nIndx >= rRange.Min() )
//STRIP001         {
//STRIP001             nUnderStart = rRange.Min();
//STRIP001             nUnderEnd = rRange.Max();
//STRIP001         }
//STRIP001         else
//STRIP001             break;
//STRIP001     }
//STRIP001
//STRIP001     // restrict start and end to current line
//STRIP001     if ( GetStart() > nUnderStart )
//STRIP001         nUnderStart = GetStart();
//STRIP001
//STRIP001     if ( GetEnd() && GetEnd() <= nUnderEnd )
//STRIP001         nUnderEnd = GetEnd() - 1;
//STRIP001
//STRIP001
//STRIP001     // check, if underlining is not isolated
//STRIP001     if ( nIndx + GetInfo().GetLen() < nUnderEnd + 1 )
//STRIP001     {
//STRIP001         //
//STRIP001         // here starts the algorithm for calculating the underline font
//STRIP001         //
//STRIP001         SwScriptInfo& rScriptInfo = GetInfo().GetParaPortion()->GetScriptInfo();
//STRIP001         SwAttrIter aIter( *(SwTxtNode*)GetInfo().GetTxtFrm()->GetTxtNode(),
//STRIP001                           rScriptInfo );
//STRIP001
//STRIP001         xub_StrLen nTmpIdx = nIndx;
//STRIP001         ULONG nSumWidth = 0;
//STRIP001         ULONG nSumHeight = 0;
//STRIP001         ULONG nBold = 0;
//STRIP001         const ULONG nPorWidth = pPor->Width();
//STRIP001         USHORT nMaxBaseLineOfst = 0;
//STRIP001
//STRIP001         while( nTmpIdx <= nUnderEnd && pPor )
//STRIP001         {
//STRIP001             if ( pPor->IsFlyPortion() || pPor->IsFlyCntPortion() ||
//STRIP001                 pPor->IsBreakPortion() || pPor->IsMarginPortion() ||
//STRIP001                 pPor->IsHolePortion() ||
//STRIP001                 ( pPor->IsMultiPortion() && ! ((SwMultiPortion*)pPor)->IsBidi() ) )
//STRIP001                 break;
//STRIP001
//STRIP001             aIter.Seek( nTmpIdx );
//STRIP001
//STRIP001             if ( aIter.GetFnt()->GetEscapement() < 0 || pFnt->IsWordLineMode() ||
//STRIP001                  SVX_CASEMAP_KAPITAELCHEN == pFnt->GetCaseMap() )
//STRIP001                 break;
//STRIP001
//STRIP001             if ( ! aIter.GetFnt()->GetEscapement() )
//STRIP001             {
//STRIP001                 nSumWidth += pPor->Width();
//STRIP001                 const ULONG nFontHeight = aIter.GetFnt()->GetHeight();
//STRIP001
//STRIP001                 // If we do not have a common baseline we take the baseline
//STRIP001                 // and the font of the lowest portion.
//STRIP001                 if ( nAdjustBaseLine )
//STRIP001                 {
//STRIP001                     USHORT nTmpBaseLineOfst = AdjustBaseLine( *pCurr, pPor );
//STRIP001                     if ( nMaxBaseLineOfst < nTmpBaseLineOfst )
//STRIP001                     {
//STRIP001                         nMaxBaseLineOfst = nTmpBaseLineOfst;
//STRIP001                         nSumHeight = nFontHeight;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 // in horizontal layout we build a weighted sum of the heights
//STRIP001                 else
//STRIP001                     nSumHeight += pPor->Width() * nFontHeight;
//STRIP001
//STRIP001                 if ( WEIGHT_NORMAL != aIter.GetFnt()->GetWeight() )
//STRIP001                     nBold += pPor->Width();
//STRIP001             }
//STRIP001
//STRIP001             nTmpIdx += pPor->GetLen();
//STRIP001             pPor = pPor->GetPortion();
//STRIP001         }
//STRIP001
//STRIP001         // resulting height
//STRIP001         if ( nSumWidth && nSumWidth != nPorWidth )
//STRIP001         {
//STRIP001             const ULONG nNewFontHeight = nAdjustBaseLine ?
//STRIP001                                          nSumHeight :
//STRIP001                                          nSumHeight / nSumWidth;
//STRIP001
//STRIP001             pUnderlineFnt = new SwFont( *GetInfo().GetFont() );
//STRIP001
//STRIP001             // font height
//STRIP001             const BYTE nActual = pUnderlineFnt->GetActual();
//STRIP001             pUnderlineFnt->SetSize( Size( pUnderlineFnt->GetSize( nActual ).Width(),
//STRIP001                                           nNewFontHeight ), nActual );
//STRIP001
//STRIP001             // font weight
//STRIP001             if ( 2 * nBold > nSumWidth )
//STRIP001                 pUnderlineFnt->SetWeight( WEIGHT_BOLD, nActual );
//STRIP001             else
//STRIP001                 pUnderlineFnt->SetWeight( WEIGHT_NORMAL, nActual );
//STRIP001
//STRIP001             // common base line
//STRIP001             aCommonBaseLine.Y() = nAdjustBaseLine + nMaxBaseLineOfst;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // an escaped redlined portion should also have a special underlining
//STRIP001     if( ! pUnderlineFnt && pFnt->GetEscapement() > 0 && GetRedln() &&
//STRIP001         GetRedln()->ChkSpecialUnderline() )
//STRIP001         pUnderlineFnt = new SwFont( *pFnt );
//STRIP001
//STRIP001     delete GetInfo().GetUnderFnt();
//STRIP001
//STRIP001     if ( pUnderlineFnt )
//STRIP001     {
//STRIP001         pUnderlineFnt->SetProportion( 100 );
//STRIP001         pUnderlineFnt->SetEscapement( 0 );
//STRIP001         pUnderlineFnt->SetStrikeout( STRIKEOUT_NONE );
//STRIP001         const Color aFillColor( COL_TRANSPARENT );
//STRIP001         pUnderlineFnt->SetFillColor( aFillColor );
//STRIP001
//STRIP001         GetInfo().SetUnderFnt( new SwUnderlineFont( *pUnderlineFnt,
//STRIP001                                                      aCommonBaseLine ) );
//STRIP001     }
//STRIP001     else
//STRIP001         // I'm sorry, we do not have a special underlining font for you.
//STRIP001         GetInfo().SetUnderFnt( 0 );
//STRIP001 }
}
