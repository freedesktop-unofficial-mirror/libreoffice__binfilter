/*************************************************************************
 *
 *  $RCSfile: sw_pormulti.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:07 $
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

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _SVX_TWOLINESITEM_HXX
#include <bf_svx/twolinesitem.hxx>
#endif
#ifndef _SVX_CHARROTATEITEM_HXX
#include <bf_svx/charrotateitem.hxx>
#endif

#ifdef BIDI
#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>      // SwField
#endif
#endif

#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
#ifndef _FMTRUBY_HXX
#include <fmtruby.hxx>  // SwFmtRuby
#endif
#ifndef _TXTATR_HXX
#include <txtatr.hxx>   // SwTxtRuby
#endif
#ifndef _CHARFMT_HXX    // SwCharFmt
#include <charfmt.hxx>
#endif
#ifndef _TXTINET_HXX    // SwTxtINetFmt
#include <txtinet.hxx>
#endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _LAYFRM_HXX
#include <layfrm.hxx>       // GetUpper()
#endif
#ifndef _SW_PORTIONHANDLER_HXX
#include <SwPortionHandler.hxx>
#endif
#ifndef _PORMULTI_HXX
#include <pormulti.hxx>     // SwMultiPortion
#endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>       // SwTxtSizeInfo
#endif
#ifndef _ITRPAINT_HXX
#include <itrpaint.hxx>     // SwTxtPainter
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>      // SwViewOptions
#endif
#ifndef _ITRFORM2_HXX
#include <itrform2.hxx>     // SwTxtFormatter
#endif
#ifndef _PORFLD_HXX
#include <porfld.hxx>       // SwFldPortion
#endif
#ifndef _PORGLUE_HXX
#include <porglue.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
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
namespace binfilter {

using namespace ::com::sun::star;
extern sal_Bool IsUnderlineBreak( const SwLinePortion& rPor, const SwFont& rFnt );
extern BYTE WhichFont( xub_StrLen nIdx, const String* pTxt,
                       const SwScriptInfo* pSI );

/*-----------------10.10.00 15:23-------------------
 *  class SwMultiPortion
 *
 * A SwMultiPortion is not a simple portion,
 * it's a container, which contains almost a SwLineLayoutPortion.
 * This SwLineLayout could be followed by other textportions via pPortion
 * and by another SwLineLayout via pNext to realize a doubleline portion.
 * --------------------------------------------------*/

//STRIP001 SwMultiPortion::~SwMultiPortion()
//STRIP001 {
//STRIP001  delete pFldRest;
//STRIP001 }

//STRIP001 void SwMultiPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  ASSERT( FALSE,
//STRIP001  "Don't try SwMultiPortion::Paint, try SwTxtPainter::PaintMultiPortion" );
//STRIP001 }

/*-----------------13.10.00 16:21-------------------
 * Summarize the internal lines to calculate the (external) size.
 * The internal line has to calculate first.
 * --------------------------------------------------*/

//STRIP001 void SwMultiPortion::CalcSize( SwTxtFormatter& rLine, SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  Width( 0 );
//STRIP001  Height( 0 );
//STRIP001  SetAscent( 0 );
//STRIP001  SetFlyInCntnt( sal_False );
//STRIP001  SwLineLayout *pLay = &GetRoot();
//STRIP001  do
//STRIP001  {
//STRIP001      pLay->CalcLine( rLine, rInf );
//STRIP001      if( rLine.IsFlyInCntBase() )
//STRIP001          SetFlyInCntnt( sal_True );
//STRIP001      if( IsRuby() && ( OnTop() == ( pLay == &GetRoot() ) ) )
//STRIP001      {
//STRIP001          // An empty phonetic line don't need an ascent or a height.
//STRIP001          if( !pLay->Width() )
//STRIP001          {
//STRIP001              pLay->SetAscent( 0 );
//STRIP001              pLay->Height( 0 );
//STRIP001          }
//STRIP001          if( OnTop() )
//STRIP001              SetAscent( GetAscent() + pLay->Height() );
//STRIP001      }
//STRIP001      else
//STRIP001          SetAscent( GetAscent() + pLay->GetAscent() );
//STRIP001      Height( Height() + pLay->Height() );
//STRIP001      if( Width() < pLay->Width() )
//STRIP001          Width( pLay->Width() );
//STRIP001      pLay = pLay->GetNext();
//STRIP001  } while ( pLay );
//STRIP001  if( HasBrackets() )
//STRIP001  {
//STRIP001      KSHORT nTmp = ((SwDoubleLinePortion*)this)->GetBrackets()->nHeight;
//STRIP001      if( nTmp > Height() )
//STRIP001      {
//STRIP001          KSHORT nAdd = ( nTmp - Height() ) / 2;
//STRIP001             GetRoot().SetAscent( GetRoot().GetAscent() + nAdd );
//STRIP001             GetRoot().Height( GetRoot().Height() + nAdd );
//STRIP001          Height( nTmp );
//STRIP001      }
//STRIP001      nTmp = ((SwDoubleLinePortion*)this)->GetBrackets()->nAscent;
//STRIP001      if( nTmp > GetAscent() )
//STRIP001          SetAscent( nTmp );
//STRIP001  }
//STRIP001 }

//STRIP001 long SwMultiPortion::CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf )
//STRIP001  const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

#ifdef BIDI
//STRIP001 sal_Bool SwMultiPortion::ChgSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd )
//STRIP001     const
//STRIP001 {
//STRIP001     return sal_False;
//STRIP001 }
#endif

/*************************************************************************
 *              virtual SwMultiPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwMultiPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Text( GetLen(), GetWhichPor() );
//STRIP001 }

/*-----------------01.11.00 14:21-------------------
 * SwMultiPortion::ActualizeTabulator()
 * sets the tabulator-flag, if there's any tabulator-portion inside.
 * --------------------------------------------------*/

//STRIP001 void SwMultiPortion::ActualizeTabulator()
//STRIP001 {
//STRIP001  SwLinePortion* pPor = GetRoot().GetFirstPortion();
//STRIP001  // First line
//STRIP001  for( bTab1 = bTab2 = sal_False; pPor; pPor = pPor->GetPortion() )
//STRIP001      if( pPor->InTabGrp() )
//STRIP001          SetTab1( sal_True );
//STRIP001  if( GetRoot().GetNext() )
//STRIP001  {
//STRIP001      // Second line
//STRIP001      pPor = GetRoot().GetNext()->GetFirstPortion();
//STRIP001      do
//STRIP001      {
//STRIP001          if( pPor->InTabGrp() )
//STRIP001              SetTab2( sal_True );
//STRIP001          pPor = pPor->GetPortion();
//STRIP001      } while ( pPor );
//STRIP001  }
//STRIP001 }

/*-----------------16.02.01 12:07-------------------
 * SwRotatedPortion::SwRotatedPortion(..)
 * --------------------------------------------------*/

//STRIP001 SwRotatedPortion::SwRotatedPortion( const SwMultiCreator& rCreate,
//STRIP001     xub_StrLen nEnd, sal_Bool bRTL ) : SwMultiPortion( nEnd )
//STRIP001 {
//STRIP001  const SvxCharRotateItem* pRot = (SvxCharRotateItem*)rCreate.pItem;
//STRIP001  if( !pRot )
//STRIP001  {
//STRIP001      const SwTxtAttr& rAttr = *rCreate.pAttr;
//STRIP001      if( RES_CHRATR_ROTATE == rAttr.Which() )
//STRIP001          pRot = &rAttr.GetCharRotate();
//STRIP001      else
//STRIP001      {
//STRIP001          SwCharFmt* pFmt = NULL;
//STRIP001          if( RES_TXTATR_INETFMT == rAttr.Which() )
//STRIP001              pFmt = ((SwTxtINetFmt&)rAttr).GetCharFmt();
//STRIP001          else if( RES_TXTATR_CHARFMT == rAttr.Which() )
//STRIP001              pFmt = rAttr.GetCharFmt().GetCharFmt();
//STRIP001          if ( pFmt )
//STRIP001          {
//STRIP001              const SfxPoolItem* pItem;
//STRIP001              if( SFX_ITEM_SET == pFmt->GetAttrSet().
//STRIP001                  GetItemState( RES_CHRATR_ROTATE, TRUE, &pItem ) )
//STRIP001                  pRot = (SvxCharRotateItem*)pItem;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( pRot )
//STRIP001     {
//STRIP001         sal_uInt8 nDir;
//STRIP001         if ( bRTL )
//STRIP001             nDir = pRot->IsBottomToTop() ? 3 : 1;
//STRIP001         else
//STRIP001             nDir = pRot->IsBottomToTop() ? 1 : 3;
//STRIP001
//STRIP001         SetDirection( nDir );
//STRIP001     }
//STRIP001 }

#ifdef BIDI

/*---------------------------------------------------
 * SwBidiPortion::SwBidiPortion(..)
 * --------------------------------------------------*/

/*N*/ SwBidiPortion::SwBidiPortion( xub_StrLen nEnd, BYTE nLv )
/*N*/     : SwMultiPortion( nEnd ), nLevel( nLv )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/     SetBidi();
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( nLevel % 2 )
//STRIP001 /*?*/         SetDirection( DIR_RIGHT2LEFT );
//STRIP001 /*?*/     else
//STRIP001 /*?*/         SetDirection( DIR_LEFT2RIGHT );
/*N*/ }


//STRIP001 long SwBidiPortion::CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  return HasTabulator() ? 0 : GetSpaceCnt() * nSpaceAdd;
//STRIP001 }

//STRIP001 sal_Bool SwBidiPortion::ChgSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd ) const
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001     if( ! HasTabulator() && nSpaceAdd > 0 && pCurr->IsNoSpaceAdd() )
//STRIP001     {
//STRIP001         pCurr->CreateSpaceAdd();
//STRIP001         ( pCurr->GetSpaceAdd() )[0] = nSpaceAdd;
//STRIP001         bRet = sal_True;
//STRIP001     }
//STRIP001
//STRIP001     return bRet;
//STRIP001 }
#endif

/*-----------------01.11.00 14:22-------------------
 * SwDoubleLinePortion::SwDoubleLinePortion(..)
 * This constructor is for the continuation of a doubleline portion
 * in the next line.
 * It takes the same brackets and if the original has no content except
 * brackets, these will be deleted.
 * --------------------------------------------------*/

//STRIP001 SwDoubleLinePortion::SwDoubleLinePortion( SwDoubleLinePortion& rDouble,
//STRIP001                                           xub_StrLen nEnd ) :
//STRIP001     SwMultiPortion( nEnd ),
//STRIP001     pBracket( 0 )
//STRIP001 {
//STRIP001 #ifdef BIDI
//STRIP001     SetDirection( rDouble.GetDirection() );
//STRIP001 #endif
//STRIP001  SetDouble();
//STRIP001  if( rDouble.GetBrackets() )
//STRIP001  {
//STRIP001      SetBrackets( rDouble );
//STRIP001      // An empty multiportion needs no brackets.
//STRIP001      // Notice: GetLen() might be zero, if the multiportion contains
//STRIP001      // the second part of a field and the width might be zero, if
//STRIP001      // it contains a note only. In this cases the brackets are okay.
//STRIP001      // But if the length and the width are both zero, the portion
//STRIP001      // is really empty.
//STRIP001      if( rDouble.Width() ==  rDouble.BracketWidth() )
//STRIP001          rDouble.ClearBrackets();
//STRIP001  }
//STRIP001 }

/*-----------------01.11.00 14:22-------------------
 * SwDoubleLinePortion::SwDoubleLinePortion(..)
 * This constructor uses the textattribut to get the right brackets.
 * The textattribut could be a 2-line-attribute or a character- or
 * internetstyle, which contains the 2-line-attribute.
 * --------------------------------------------------*/

//STRIP001 SwDoubleLinePortion::SwDoubleLinePortion( const SwMultiCreator& rCreate,
//STRIP001  xub_StrLen nEnd ) : SwMultiPortion( nEnd ), pBracket( new SwBracket() )
//STRIP001 {
//STRIP001  SetDouble();
//STRIP001  const SvxTwoLinesItem* pTwo = (SvxTwoLinesItem*)rCreate.pItem;
//STRIP001  if( pTwo )
//STRIP001      pBracket->nStart = 0;
//STRIP001  else
//STRIP001  {
//STRIP001      const SwTxtAttr& rAttr = *rCreate.pAttr;
//STRIP001      pBracket->nStart = *rAttr.GetStart();
//STRIP001
//STRIP001      if( RES_CHRATR_TWO_LINES == rAttr.Which() )
//STRIP001          pTwo = &rAttr.Get2Lines();
//STRIP001      else
//STRIP001      {
//STRIP001          SwCharFmt* pFmt = NULL;
//STRIP001          if( RES_TXTATR_INETFMT == rAttr.Which() )
//STRIP001              pFmt = ((SwTxtINetFmt&)rAttr).GetCharFmt();
//STRIP001          else if( RES_TXTATR_CHARFMT == rAttr.Which() )
//STRIP001              pFmt = rAttr.GetCharFmt().GetCharFmt();
//STRIP001          if ( pFmt )
//STRIP001          {
//STRIP001              const SfxPoolItem* pItem;
//STRIP001              if( SFX_ITEM_SET == pFmt->GetAttrSet().
//STRIP001                  GetItemState( RES_CHRATR_TWO_LINES, TRUE, &pItem ) )
//STRIP001                  pTwo = (SvxTwoLinesItem*)pItem;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( pTwo )
//STRIP001  {
//STRIP001      pBracket->cPre = pTwo->GetStartBracket();
//STRIP001      pBracket->cPost = pTwo->GetEndBracket();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pBracket->cPre = 0;
//STRIP001      pBracket->cPost = 0;
//STRIP001  }
//STRIP001  BYTE nTmp = SW_SCRIPTS;
//STRIP001  if( pBracket->cPre > 255 )
//STRIP001  {
//STRIP001      String aTxt( pBracket->cPre );
//STRIP001         nTmp = WhichFont( 0, &aTxt, 0 );
//STRIP001  }
//STRIP001  pBracket->nPreScript = nTmp;
//STRIP001  nTmp = SW_SCRIPTS;
//STRIP001  if( pBracket->cPost > 255 )
//STRIP001  {
//STRIP001      String aTxt( pBracket->cPost );
//STRIP001         nTmp = WhichFont( 0, &aTxt, 0 );
//STRIP001     }
//STRIP001  pBracket->nPostScript = nTmp;
//STRIP001
//STRIP001  if( !pBracket->cPre && !pBracket->cPost )
//STRIP001  {
//STRIP001      delete pBracket;
//STRIP001      pBracket = 0;
//STRIP001  }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     // double line portions have the same direction as the frame directions
//STRIP001     if ( rCreate.nLevel % 2 )
//STRIP001         SetDirection( DIR_RIGHT2LEFT );
//STRIP001     else
//STRIP001         SetDirection( DIR_LEFT2RIGHT );
//STRIP001 #endif
//STRIP001 }


/*-----------------25.10.00 09:51-------------------
 * SwMultiPortion::PaintBracket paints the wished bracket,
 * if the multiportion has surrounding brackets.
 * The X-position of the SwTxtPaintInfo will be modified:
 * the open bracket sets position behind itself,
 * the close bracket in front of itself.
 * --------------------------------------------------*/

//STRIP001 void SwDoubleLinePortion::PaintBracket( SwTxtPaintInfo &rInf,
//STRIP001  short nSpaceAdd, sal_Bool bOpen ) const
//STRIP001 {
//STRIP001  sal_Unicode cCh = bOpen ? pBracket->cPre : pBracket->cPost;
//STRIP001  if( !cCh )
//STRIP001      return;
//STRIP001  KSHORT nChWidth = bOpen ? PreWidth() : PostWidth();
//STRIP001  if( !nChWidth )
//STRIP001      return;
//STRIP001  if( !bOpen )
//STRIP001      rInf.X( rInf.X() + Width() - PostWidth() +
//STRIP001          ( nSpaceAdd > 0 ? CalcSpacing( nSpaceAdd, rInf ) : 0 ) );
//STRIP001
//STRIP001  SwBlankPortion aBlank( cCh, sal_True );
//STRIP001  aBlank.SetAscent( pBracket->nAscent );
//STRIP001  aBlank.Width( nChWidth );
//STRIP001  aBlank.Height( pBracket->nHeight );
//STRIP001  {
//STRIP001      SwFont* pTmpFnt = new SwFont( *rInf.GetFont() );
//STRIP001      BYTE nAct = bOpen ? pBracket->nPreScript : pBracket->nPostScript;
//STRIP001      if( SW_SCRIPTS > nAct )
//STRIP001          pTmpFnt->SetActual( nAct );
//STRIP001      pTmpFnt->SetProportion( 100 );
//STRIP001      SwFontSave aSave( rInf, pTmpFnt );
//STRIP001      aBlank.Paint( rInf );
//STRIP001      delete pTmpFnt;
//STRIP001  }
//STRIP001  if( bOpen )
//STRIP001      rInf.X( rInf.X() + PreWidth() );
//STRIP001 }

/*-----------------25.10.00 16:26-------------------
 * SwDoubleLinePortion::SetBrackets creates the bracket-structur
 * and fills it, if not both characters are 0x00.
 * --------------------------------------------------*/

//STRIP001 void SwDoubleLinePortion::SetBrackets( const SwDoubleLinePortion& rDouble )
//STRIP001 {
//STRIP001  if( rDouble.pBracket )
//STRIP001  {
//STRIP001      pBracket = new SwBracket;
//STRIP001      pBracket->cPre = rDouble.pBracket->cPre;
//STRIP001      pBracket->cPost = rDouble.pBracket->cPost;
//STRIP001      pBracket->nPreScript = rDouble.pBracket->nPreScript;
//STRIP001      pBracket->nPostScript = rDouble.pBracket->nPostScript;
//STRIP001      pBracket->nStart = rDouble.pBracket->nStart;
//STRIP001  }
//STRIP001 }

/*-----------------25.10.00 16:29-------------------
 * SwDoubleLinePortion::FormatBrackets
 * calculates the size of the brackets => pBracket,
 * reduces the nMaxWidth-parameter ( minus bracket-width )
 * and moves the rInf-x-position behind the opening bracket.
 * --------------------------------------------------*/

//STRIP001 void SwDoubleLinePortion::FormatBrackets( SwTxtFormatInfo &rInf, SwTwips& nMaxWidth )
//STRIP001 {
//STRIP001  nMaxWidth -= rInf.X();
//STRIP001  SwFont* pTmpFnt = new SwFont( *rInf.GetFont() );
//STRIP001  pTmpFnt->SetProportion( 100 );
//STRIP001  pBracket->nAscent = 0;
//STRIP001  pBracket->nHeight = 0;
//STRIP001  if( pBracket->cPre )
//STRIP001  {
//STRIP001      String aStr( pBracket->cPre );
//STRIP001      BYTE nActualScr = pTmpFnt->GetActual();
//STRIP001      if( SW_SCRIPTS > pBracket->nPreScript )
//STRIP001          pTmpFnt->SetActual( pBracket->nPreScript );
//STRIP001      SwFontSave aSave( rInf, pTmpFnt );
//STRIP001      SwPosSize aSize = rInf.GetTxtSize( aStr );
//STRIP001      pBracket->nAscent = rInf.GetAscent();
//STRIP001      pBracket->nHeight = aSize.Height();
//STRIP001      pTmpFnt->SetActual( nActualScr );
//STRIP001      if( nMaxWidth > aSize.Width() )
//STRIP001      {
//STRIP001          pBracket->nPreWidth = aSize.Width();
//STRIP001          nMaxWidth -= aSize.Width();
//STRIP001          rInf.X( rInf.X() + aSize.Width() );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pBracket->nPreWidth = 0;
//STRIP001          nMaxWidth = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      pBracket->nPreWidth = 0;
//STRIP001  if( pBracket->cPost )
//STRIP001  {
//STRIP001      String aStr( pBracket->cPost );
//STRIP001      if( SW_SCRIPTS > pBracket->nPostScript )
//STRIP001          pTmpFnt->SetActual( pBracket->nPostScript );
//STRIP001      SwFontSave aSave( rInf, pTmpFnt );
//STRIP001      SwPosSize aSize = rInf.GetTxtSize( aStr );
//STRIP001      KSHORT nTmpAsc = rInf.GetAscent();
//STRIP001      if( nTmpAsc > pBracket->nAscent )
//STRIP001      {
//STRIP001          pBracket->nHeight += nTmpAsc - pBracket->nAscent;
//STRIP001          pBracket->nAscent = nTmpAsc;
//STRIP001      }
//STRIP001      if( aSize.Height() > pBracket->nHeight )
//STRIP001          pBracket->nHeight = aSize.Height();
//STRIP001      if( nMaxWidth > aSize.Width() )
//STRIP001      {
//STRIP001          pBracket->nPostWidth = aSize.Width();
//STRIP001          nMaxWidth -= aSize.Width();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pBracket->nPostWidth = 0;
//STRIP001          nMaxWidth = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      pBracket->nPostWidth = 0;
//STRIP001  nMaxWidth += rInf.X();
//STRIP001 }

/*-----------------26.10.00 10:36-------------------
 * SwDoubleLinePortion::CalcBlanks
 * calculates the number of blanks in each line and
 * the difference of the width of the two lines.
 * These results are used from the text adjustment.
 * --------------------------------------------------*/

//STRIP001 void SwDoubleLinePortion::CalcBlanks( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  SwLinePortion* pPor = GetRoot().GetFirstPortion();
//STRIP001  xub_StrLen nNull = 0;
//STRIP001  xub_StrLen nStart = rInf.GetIdx();
//STRIP001  SetTab1( sal_False );
//STRIP001  SetTab2( sal_False );
//STRIP001  for( nBlank1 = 0; pPor; pPor = pPor->GetPortion() )
//STRIP001  {
//STRIP001      if( pPor->InTxtGrp() )
//STRIP001          nBlank1 += ((SwTxtPortion*)pPor)->GetSpaceCnt( rInf, nNull );
//STRIP001      rInf.SetIdx( rInf.GetIdx() + pPor->GetLen() );
//STRIP001      if( pPor->InTabGrp() )
//STRIP001          SetTab1( sal_True );
//STRIP001  }
//STRIP001  nLineDiff = GetRoot().Width();
//STRIP001  if( GetRoot().GetNext() )
//STRIP001  {
//STRIP001      pPor = GetRoot().GetNext()->GetFirstPortion();
//STRIP001      nLineDiff -= GetRoot().GetNext()->Width();
//STRIP001  }
//STRIP001  for( nBlank2 = 0; pPor; pPor = pPor->GetPortion() )
//STRIP001  {
//STRIP001      if( pPor->InTxtGrp() )
//STRIP001          nBlank2 += ((SwTxtPortion*)pPor)->GetSpaceCnt( rInf, nNull );
//STRIP001      rInf.SetIdx( rInf.GetIdx() + pPor->GetLen() );
//STRIP001      if( pPor->InTabGrp() )
//STRIP001          SetTab2( sal_True );
//STRIP001  }
//STRIP001  rInf.SetIdx( nStart );
//STRIP001 }

//STRIP001 long SwDoubleLinePortion::CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  return HasTabulator() ? 0 : GetSpaceCnt() * nSpaceAdd;
//STRIP001 }

/*-----------------01.11.00 14:29-------------------
 * SwDoubleLinePortion::ChangeSpaceAdd(..)
 * merges the spaces for text adjustment from the inner and outer part.
 * Inside the doubleline portion the wider line has no spaceadd-array, the
 * smaller line has such an array to reach width of the wider line.
 * If the surrounding line has text adjustment and the doubleline portion
 * contains no tabulator, it is necessary to create/manipulate the inner
 * space arrays.
 * --------------------------------------------------*/

//STRIP001 #ifdef BIDI
//STRIP001 sal_Bool SwDoubleLinePortion::ChgSpaceAdd( SwLineLayout* pCurr,
//STRIP001                                            short nSpaceAdd ) const
//STRIP001 #else
//STRIP001 sal_Bool SwDoubleLinePortion::ChangeSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd )
//STRIP001 #endif
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  if( !HasTabulator() && nSpaceAdd > 0 )
//STRIP001  {
//STRIP001      if( pCurr->IsNoSpaceAdd() )
//STRIP001      {   // The wider line gets the spaceadd from the surrounding line direct
//STRIP001          pCurr->CreateSpaceAdd();
//STRIP001          ( pCurr->GetSpaceAdd() )[0] = nSpaceAdd;
//STRIP001          bRet = sal_True;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          xub_StrLen nMyBlank = GetSmallerSpaceCnt();
//STRIP001          xub_StrLen nOther = GetSpaceCnt();
//STRIP001          SwTwips nMultiSpace = pCurr->GetSpaceAdd()[0] * nMyBlank
//STRIP001                                + nOther * nSpaceAdd;
//STRIP001          if( nMyBlank )
//STRIP001              nMultiSpace /= nMyBlank;
//STRIP001          if( nMultiSpace < KSHRT_MAX )
//STRIP001          {
//STRIP001              pCurr->GetpSpaceAdd()->Insert(KSHORT(nMultiSpace),0);
//STRIP001              bRet = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
/*-----------------01.11.00 14:29-------------------
 * SwDoubleLinePortion::ResetSpaceAdd(..)
 * cancels the manipulation from SwDoubleLinePortion::ChangeSpaceAdd(..)
 * --------------------------------------------------*/

//STRIP001 void SwDoubleLinePortion::ResetSpaceAdd( SwLineLayout* pCurr )
//STRIP001 {
//STRIP001  pCurr->GetSpaceAdd().Remove(0);
//STRIP001  if( !pCurr->GetSpaceAdd().Count() )
//STRIP001      pCurr->FinishSpaceAdd();
//STRIP001 }
//STRIP001
//STRIP001 SwDoubleLinePortion::~SwDoubleLinePortion()
//STRIP001 {
//STRIP001  delete pBracket;
//STRIP001 }

#ifdef BIDI
/*-----------------13.11.00 14:50-------------------
 * SwRubyPortion::SwRubyPortion(..)
 * constructs a ruby portion, i.e. an additional text is displayed
 * beside the main text, e.g. phonetic characters.
 * --------------------------------------------------*/


//STRIP001 SwRubyPortion::SwRubyPortion( const SwRubyPortion& rRuby, xub_StrLen nEnd ) :
//STRIP001     SwMultiPortion( nEnd ),
//STRIP001     nRubyOffset( rRuby.GetRubyOffset() ),
//STRIP001     nAdjustment( rRuby.GetAdjustment() )
//STRIP001 {
//STRIP001     SetDirection( rRuby.GetDirection() ),
//STRIP001     SetTop( rRuby.OnTop() );
//STRIP001     SetRuby();
//STRIP001 }
#endif

/*-----------------13.11.00 14:50-------------------
 * SwRubyPortion::SwRubyPortion(..)
 * constructs a ruby portion, i.e. an additional text is displayed
 * beside the main text, e.g. phonetic characters.
 * --------------------------------------------------*/

//STRIP001 SwRubyPortion::SwRubyPortion( const SwMultiCreator& rCreate, const SwFont& rFnt,
//STRIP001                               const SwDoc& rDoc, xub_StrLen nEnd, xub_StrLen nOffs,
//STRIP001                               const sal_Bool* pForceRubyPos )
//STRIP001      : SwMultiPortion( nEnd )
//STRIP001 {
//STRIP001  SetRuby();
//STRIP001     ASSERT( SW_MC_RUBY == rCreate.nId, "Ruby expected" );
//STRIP001  ASSERT( RES_TXTATR_CJK_RUBY == rCreate.pAttr->Which(), "Wrong attribute" );
//STRIP001  const SwFmtRuby& rRuby = rCreate.pAttr->GetRuby();
//STRIP001  nAdjustment = rRuby.GetAdjustment();
//STRIP001  nRubyOffset = nOffs;
//STRIP001
//STRIP001     // in grid mode we force the ruby text to the upper or lower line
//STRIP001     if ( pForceRubyPos )
//STRIP001         SetTop( *pForceRubyPos );
//STRIP001     else
//STRIP001         SetTop( ! rRuby.GetPosition() );
//STRIP001
//STRIP001     const SwCharFmt* pFmt = ((SwTxtRuby*)rCreate.pAttr)->GetCharFmt();
//STRIP001  SwFont *pRubyFont;
//STRIP001  if( pFmt )
//STRIP001  {
//STRIP001      const SwAttrSet& rSet = pFmt->GetAttrSet();
//STRIP001      pRubyFont = new SwFont( rFnt );
//STRIP001         pRubyFont->SetDiffFnt( &rSet, &rDoc );
//STRIP001
//STRIP001         // we do not allow a vertical font for the ruby text
//STRIP001         pRubyFont->SetVertical( rFnt.GetOrientation() );
//STRIP001  }
//STRIP001  else
//STRIP001      pRubyFont = NULL;
//STRIP001  String aStr( rRuby.GetText(), nOffs, STRING_LEN );
//STRIP001  SwFldPortion *pFld = new SwFldPortion( aStr, pRubyFont );
//STRIP001     pFld->SetNextOffset( nOffs );
//STRIP001  pFld->SetFollow( sal_True );
//STRIP001
//STRIP001     if( OnTop() )
//STRIP001      GetRoot().SetPortion( pFld );
//STRIP001  else
//STRIP001  {
//STRIP001      GetRoot().SetNext( new SwLineLayout() );
//STRIP001      GetRoot().GetNext()->SetPortion( pFld );
//STRIP001  }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     // ruby portions have the same direction as the frame directions
//STRIP001     if ( rCreate.nLevel % 2 )
//STRIP001     {
//STRIP001         // switch right and left ruby adjustment in rtl environment
//STRIP001         if ( 0 == nAdjustment )
//STRIP001             nAdjustment = 2;
//STRIP001         else if ( 2 == nAdjustment )
//STRIP001             nAdjustment = 0;
//STRIP001
//STRIP001         SetDirection( DIR_RIGHT2LEFT );
//STRIP001     }
//STRIP001     else
//STRIP001         SetDirection( DIR_LEFT2RIGHT );
//STRIP001 #endif
//STRIP001 }

/*-----------------13.11.00 14:56-------------------
 * SwRubyPortion::_Adjust(..)
 * In ruby portion there are different alignments for
 * the ruby text and the main text.
 * Left, right, centered and two possibilities of block adjustment
 * The block adjustment is realized by spacing between the characteres,
 * either with a half space or no space in front of the first letter and
 * a half space at the end of the last letter.
 * Notice: the smaller line will be manipulated, normally it's the ruby line,
 * but it could be the main text, too.
 * If there is a tabulator in smaller line, no adjustment is possible.
 * --------------------------------------------------*/

//STRIP001 void SwRubyPortion::_Adjust( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  SwTwips nLineDiff = GetRoot().Width() - GetRoot().GetNext()->Width();
//STRIP001  xub_StrLen nOldIdx = rInf.GetIdx();
//STRIP001  if( !nLineDiff )
//STRIP001      return;
//STRIP001  SwLineLayout *pCurr;
//STRIP001  if( nLineDiff < 0 )
//STRIP001  {   // The first line has to be adjusted.
//STRIP001      if( GetTab1() )
//STRIP001          return;
//STRIP001      pCurr = &GetRoot();
//STRIP001      nLineDiff = -nLineDiff;
//STRIP001  }
//STRIP001  else
//STRIP001  {   // The second line has to be adjusted.
//STRIP001      if( GetTab2() )
//STRIP001          return;
//STRIP001      pCurr = GetRoot().GetNext();
//STRIP001      rInf.SetIdx( nOldIdx + GetRoot().GetLen() );
//STRIP001  }
//STRIP001  KSHORT nLeft = 0;   // the space in front of the first letter
//STRIP001  KSHORT nRight = 0;  // the space at the end of the last letter
//STRIP001  USHORT nSub = 0;
//STRIP001  switch ( nAdjustment )
//STRIP001  {
//STRIP001      case 1: nRight = nLineDiff/2;    // no break
//STRIP001      case 2: nLeft = nLineDiff - nRight; break;
//STRIP001      case 3: nSub = 1; // no break
//STRIP001      case 4:
//STRIP001      {
//STRIP001          xub_StrLen nCharCnt = 0;
//STRIP001          SwLinePortion *pPor;
//STRIP001          for( pPor = pCurr->GetFirstPortion(); pPor; pPor = pPor->GetPortion() )
//STRIP001          {
//STRIP001              if( pPor->InTxtGrp() )
//STRIP001                  ((SwTxtPortion*)pPor)->GetSpaceCnt( rInf, nCharCnt );
//STRIP001              rInf.SetIdx( rInf.GetIdx() + pPor->GetLen() );
//STRIP001          }
//STRIP001          if( nCharCnt > nSub )
//STRIP001          {
//STRIP001              SwTwips nCalc = nLineDiff / ( nCharCnt - nSub );
//STRIP001              short nTmp;
//STRIP001              if( nCalc < SHRT_MAX )
//STRIP001                  nTmp = -short(nCalc);
//STRIP001              else
//STRIP001                  nTmp = SHRT_MIN;
//STRIP001              pCurr->CreateSpaceAdd( nTmp );
//STRIP001              nLineDiff -= nCalc * ( nCharCnt - 1 );
//STRIP001          }
//STRIP001          if( nLineDiff > 1 )
//STRIP001          {
//STRIP001              nRight = nLineDiff/2;
//STRIP001              nLeft = nLineDiff - nRight;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      default: ASSERT( sal_False, "New ruby adjustment" );
//STRIP001  }
//STRIP001  if( nLeft || nRight )
//STRIP001  {
//STRIP001      if( !pCurr->GetPortion() )
//STRIP001          pCurr->SetPortion( new SwTxtPortion( *pCurr ) );
//STRIP001      SwMarginPortion *pMarg = new SwMarginPortion( 0 );
//STRIP001      if( nLeft )
//STRIP001      {
//STRIP001          pMarg->AddPrtWidth( nLeft );
//STRIP001          pMarg->SetPortion( pCurr->GetPortion() );
//STRIP001          pCurr->SetPortion( pMarg );
//STRIP001      }
//STRIP001      if( nRight )
//STRIP001      {
//STRIP001          pMarg = new SwMarginPortion( 0 );
//STRIP001          pMarg->AddPrtWidth( nRight );
//STRIP001          pCurr->FindLastPortion()->Append( pMarg );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     pCurr->Width( Width() );
//STRIP001  rInf.SetIdx( nOldIdx );
//STRIP001 }

/*-----------------08.11.00 14:14-------------------
 * CalcRubyOffset()
 * has to change the nRubyOffset, if there's a fieldportion
 * in the phonetic line.
 * The nRubyOffset is the position in the rubystring, where the
 * next SwRubyPortion has start the displaying of the phonetics.
 * --------------------------------------------------*/

//STRIP001 void SwRubyPortion::CalcRubyOffset()
//STRIP001 {
//STRIP001  const SwLineLayout *pCurr = &GetRoot();
//STRIP001  if( !OnTop() )
//STRIP001  {
//STRIP001      pCurr = pCurr->GetNext();
//STRIP001      if( !pCurr )
//STRIP001          return;
//STRIP001  }
//STRIP001  const SwLinePortion *pPor = pCurr->GetFirstPortion();
//STRIP001  const SwFldPortion *pFld = NULL;
//STRIP001  while( pPor )
//STRIP001  {
//STRIP001      if( pPor->InFldGrp() )
//STRIP001          pFld = (SwFldPortion*)pPor;
//STRIP001      pPor = pPor->GetPortion();
//STRIP001  }
//STRIP001  if( pFld )
//STRIP001  {
//STRIP001      if( pFld->HasFollow() )
//STRIP001          nRubyOffset = pFld->GetNextOffset();
//STRIP001      else
//STRIP001          nRubyOffset = STRING_LEN;
//STRIP001  }
//STRIP001 }

/*-----------------13.10.00 16:22-------------------
 * SwTxtSizeInfo::GetMultiCreator(..)
 * If we (e.g. the position rPos) are inside a two-line-attribute or
 * a ruby-attribute, the attribute will be returned in a SwMultiCreator-struct,
 * otherwise the function returns zero.
 * The rPos parameter is set to the end of the multiportion,
 * normally this is the end of the attribute,
 * but sometimes it is the start of another attribute, which finished or
 * interrupts the first attribute.
 * E.g. a ruby portion interrupts a 2-line-attribute, a 2-line-attribute
 * with different brackets interrupts another 2-line-attribute.
 * --------------------------------------------------*/

/*-----------------13.11.00 15:38-------------------
 * lcl_Has2Lines(..)
 * is a little help function for GetMultiCreator(..)
 * It extracts the 2-line-format from a 2-line-attribute or a character style.
 * The rValue is set to TRUE, if the 2-line-attribute's value is set and
 * no 2-line-format reference is passed. If there is a 2-line-format reference,
 * then the rValue is set only, if the 2-line-attribute's value is set _and_
 * the 2-line-formats has the same brackets.
 * --------------------------------------------------*/

/*N*/ sal_Bool lcl_Has2Lines( const SwTxtAttr& rAttr, const SvxTwoLinesItem* &rpRef,
/*N*/   sal_Bool &rValue )
/*N*/ {
/*N*/   if( RES_CHRATR_TWO_LINES == rAttr.Which() )
/*N*/   {
/*?*/       rValue = rAttr.Get2Lines().GetValue();
/*?*/       if( !rpRef )
/*?*/           rpRef = &rAttr.Get2Lines();
/*?*/       else if( rAttr.Get2Lines().GetEndBracket() != rpRef->GetEndBracket() ||
/*?*/           rAttr.Get2Lines().GetStartBracket() != rpRef->GetStartBracket() )
/*?*/           rValue = sal_False;
/*?*/       return sal_True;
/*N*/   }
/*N*/   SwCharFmt* pFmt = NULL;
/*N*/   if( RES_TXTATR_INETFMT == rAttr.Which() )
/*N*/       pFmt = ((SwTxtINetFmt&)rAttr).GetCharFmt();
/*N*/   else if( RES_TXTATR_CHARFMT == rAttr.Which() )
/*N*/       pFmt = rAttr.GetCharFmt().GetCharFmt();
/*N*/   if ( pFmt )
/*N*/   {
/*N*/       const SfxPoolItem* pItem;
/*N*/       if( SFX_ITEM_SET == pFmt->GetAttrSet().
/*N*/           GetItemState( RES_CHRATR_TWO_LINES, TRUE, &pItem ) )
/*N*/       {
/*?*/           rValue = ((SvxTwoLinesItem*)pItem)->GetValue();
/*?*/           if( !rpRef )
/*?*/               rpRef = (SvxTwoLinesItem*)pItem;
/*?*/           else if( ((SvxTwoLinesItem*)pItem)->GetEndBracket() !=
/*?*/                       rpRef->GetEndBracket() ||
/*?*/                       ((SvxTwoLinesItem*)pItem)->GetStartBracket() !=
/*?*/                       rpRef->GetStartBracket() )
/*?*/               rValue = sal_False;
/*?*/           return sal_True;
/*N*/       }
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

/*-----------------16.02.01 16:39-------------------
 * lcl_HasRotation(..)
 * is a little help function for GetMultiCreator(..)
 * It extracts the charrotation from a charrotate-attribute or a character style.
 * The rValue is set to TRUE, if the charrotate-attribute's value is set and
 * no charrotate-format reference is passed.
 * If there is a charrotate-format reference, then the rValue is set only,
 * if the charrotate-attribute's value is set _and_ identical
 * to the charrotate-format's value.
 * --------------------------------------------------*/

/*N*/ sal_Bool lcl_HasRotation( const SwTxtAttr& rAttr,
/*N*/   const SvxCharRotateItem* &rpRef, sal_Bool &rValue )
/*N*/ {
/*N*/   if( RES_CHRATR_ROTATE == rAttr.Which() )
/*N*/   {
/*?*/       rValue = 0 != rAttr.GetCharRotate().GetValue();
/*?*/       if( !rpRef )
/*?*/           rpRef = &rAttr.GetCharRotate();
/*?*/       else if( rAttr.GetCharRotate().GetValue() != rpRef->GetValue() )
/*?*/           rValue = sal_False;
/*?*/       return sal_True;
/*N*/   }
/*N*/   SwCharFmt* pFmt = NULL;
/*N*/   if( RES_TXTATR_INETFMT == rAttr.Which() )
/*N*/       pFmt = ((SwTxtINetFmt&)rAttr).GetCharFmt();
/*N*/   else if( RES_TXTATR_CHARFMT == rAttr.Which() )
/*N*/       pFmt = rAttr.GetCharFmt().GetCharFmt();
/*N*/   if ( pFmt )
/*N*/   {
/*N*/       const SfxPoolItem* pItem;
/*N*/       if( SFX_ITEM_SET == pFmt->GetAttrSet().
/*N*/           GetItemState( RES_CHRATR_ROTATE, TRUE, &pItem ) )
/*N*/       {
/*?*/           rValue = 0 != ((SvxCharRotateItem*)pItem)->GetValue();
/*?*/           if( !rpRef )
/*?*/               rpRef = (SvxCharRotateItem*)pItem;
/*?*/           else if( ((SvxCharRotateItem*)pItem)->GetValue() !=
/*?*/                       rpRef->GetValue() )
/*?*/               rValue = sal_False;
/*?*/           return sal_True;
/*N*/       }
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

/*N*/ #ifdef BIDI
/*N*/ SwMultiCreator* SwTxtSizeInfo::GetMultiCreator( xub_StrLen &rPos,
/*N*/                                                 SwMultiPortion* pMulti ) const
/*N*/ #else
/*N*/ SwMultiCreator* SwTxtSizeInfo::GetMultiCreator( xub_StrLen &rPos ) const
/*N*/ #endif
/*N*/ {
/*N*/ #ifdef BIDI
/*N*/     SwScriptInfo& rSI = ((SwParaPortion*)GetParaPortion())->GetScriptInfo();
/*N*/
/*N*/     // get the last embedding level
/*N*/     BYTE nCurrLevel;
/*N*/     if ( pMulti )
/*N*/     {
            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/         ASSERT( pMulti->IsBidi(), "Nested MultiPortion is not BidiPortion" )
//STRIP001 /*?*/         // level associated with bidi-portion;
//STRIP001 /*?*/         nCurrLevel = ((SwBidiPortion*)pMulti)->GetLevel();
/*N*/     }
/*N*/     else
/*N*/         // no nested bidi portion required
/*N*/         nCurrLevel = GetTxtFrm()->IsRightToLeft() ? 1 : 0;
/*N*/
/*N*/     // check if there is a field at rPos:
/*N*/     BYTE nNextLevel = nCurrLevel;
/*N*/     sal_Bool bFldBidi = sal_False;
/*N*/
/*N*/     if ( CH_TXTATR_BREAKWORD == GetChar( rPos ) )
/*N*/     {
                    bFldBidi = sal_True;
/*
         // examining the script of the field text should be sufficient
        // for 99% of all cases
         XubString aTxt = GetTxtFrm()->GetTxtNode()->GetExpandTxt( rPos, 1 );

         if ( pBreakIt->xBreak.is() && aTxt.Len() )
         {
             sal_Bool bFldDir = ( ::com::sun::star::i18n::ScriptType::COMPLEX ==
                                  pBreakIt->GetRealScriptOfText( aTxt, 0 ) );
             sal_Bool bCurrDir = ( 0 != ( nCurrLevel % 2 ) );
             if ( bFldDir != bCurrDir )
             {
                 nNextLevel = nCurrLevel + 1;
                 bFldBidi = sal_True;
             }
        }*/
/*N*/     }
/*N*/     else
/*N*/         nNextLevel = rSI.DirType( rPos );
/*N*/
/*N*/     if ( GetTxt().Len() != rPos && nNextLevel > nCurrLevel )
/*N*/     {
/*?*/         rPos = bFldBidi ? rPos + 1 : rSI.NextDirChg( rPos, &nCurrLevel );
/*?*/         if ( STRING_LEN == rPos )
/*?*/             return NULL;
/*?*/         SwMultiCreator *pRet = new SwMultiCreator;
/*?*/       pRet->pItem = NULL;
/*?*/         pRet->pAttr = NULL;
/*?*/         pRet->nId = SW_MC_BIDI;
/*?*/         pRet->nLevel = nCurrLevel + 1;
/*?*/       return pRet;
/*N*/     }
/*N*/
/*N*/     // a bidi portion can only contain other bidi portions
/*N*/     if ( pMulti )
/*N*/         return NULL;
/*N*/ #endif
/*N*/
/*N*/   const SvxCharRotateItem* pRotate = NULL;
/*N*/   const SfxPoolItem* pRotItem;
/*N*/   if( SFX_ITEM_SET == pFrm->GetTxtNode()->GetSwAttrSet().
/*N*/       GetItemState( RES_CHRATR_ROTATE, TRUE, &pRotItem ) &&
/*N*/       ((SvxCharRotateItem*)pRotItem)->GetValue() )
/*?*/       pRotate = (SvxCharRotateItem*)pRotItem;
/*N*/   else
/*N*/       pRotItem = NULL;
/*N*/   const SvxTwoLinesItem* p2Lines = NULL;
/*N*/   const SfxPoolItem* pItem;
/*N*/   if( SFX_ITEM_SET == pFrm->GetTxtNode()->GetSwAttrSet().
/*N*/       GetItemState( RES_CHRATR_TWO_LINES, TRUE, &pItem ) &&
/*N*/       ((SvxTwoLinesItem*)pItem)->GetValue() )
/*N*/       p2Lines = (SvxTwoLinesItem*)pItem;
/*N*/   else
/*N*/       pItem = NULL;
/*N*/
/*N*/   const SwpHints *pHints = pFrm->GetTxtNode()->GetpSwpHints();
/*N*/   if( !pHints && !p2Lines && !pRotate )
/*N*/       return NULL;
/*N*/   const SwTxtAttr *pRuby = NULL;
/*N*/   sal_Bool bTwo = sal_False;
/*N*/   sal_Bool bRot = sal_False;
/*N*/   USHORT n2Lines = USHRT_MAX;
/*N*/   USHORT nRotate = USHRT_MAX;
/*N*/   USHORT nCount = pHints ? pHints->Count() : 0;
/*N*/   USHORT i;
/*N*/   for( i = 0; i < nCount; ++i )
/*N*/   {
/*N*/       const SwTxtAttr *pTmp = (*pHints)[i];
/*N*/       xub_StrLen nStart = *pTmp->GetStart();
/*N*/       if( rPos < nStart )
/*N*/           break;
/*N*/       if( *pTmp->GetAnyEnd() > rPos )
/*N*/       {
/*N*/           if( RES_TXTATR_CJK_RUBY == pTmp->Which() )
/*N*/               pRuby = pTmp;
/*N*/           else
/*N*/           {
/*N*/               const SvxCharRotateItem* pRoTmp = NULL;
/*N*/               if( lcl_HasRotation( *pTmp, pRoTmp, bRot ) )
/*N*/               {
/*N*/                   nRotate = bRot ? i : nCount;
/*N*/                   pRotate = pRoTmp;
/*N*/               }
/*N*/               const SvxTwoLinesItem* p2Tmp = NULL;
/*N*/               if( lcl_Has2Lines( *pTmp, p2Tmp, bTwo ) )
/*N*/               {
/*N*/                   n2Lines = bTwo ? i : nCount;
/*N*/                   p2Lines = p2Tmp;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if( pRuby )
/*N*/   {   // The winner is ... a ruby attribute and so
/*N*/       // the end of the multiportion is the end of the ruby attribute.
/*?*/       rPos = *pRuby->GetEnd();
/*?*/       SwMultiCreator *pRet = new SwMultiCreator;
/*?*/       pRet->pItem = NULL;
/*?*/       pRet->pAttr = pRuby;
/*?*/       pRet->nId = SW_MC_RUBY;
/*?*/ #ifdef BIDI
/*?*/         pRet->nLevel = GetTxtFrm()->IsRightToLeft() ? 1 : 0;
/*?*/ #endif
/*?*/       return pRet;
/*N*/   }
/*N*/   if( n2Lines < nCount || ( pItem && pItem == p2Lines &&
/*N*/       rPos < GetTxt().Len() ) )
/*N*/   {   // The winner is a 2-line-attribute,
/*?*/       // the end of the multiportion depends on the following attributes...
/*?*/       SwMultiCreator *pRet = new SwMultiCreator;
/*?*/
/*?*/       // We note the endpositions of the 2-line attributes in aEnd as stack
/*?*/       SvXub_StrLens aEnd;
/*?*/
/*?*/       // The bOn flag signs the state of the last 2-line attribute in the
/*?*/       // aEnd-stack, it is compatible with the winner-attribute or
/*?*/       // it interrupts the other attribute.
/*?*/       sal_Bool bOn = sal_True;
/*?*/
/*?*/       if( n2Lines < nCount )
/*?*/       {
/*?*/           pRet->pItem = NULL;
/*?*/           pRet->pAttr = (*pHints)[n2Lines];
/*?*/           aEnd.Insert( *pRet->pAttr->GetEnd(), 0 );
/*?*/           if( pItem )
/*?*/           {
/*?*/               aEnd[ 0 ] = GetTxt().Len();
/*?*/               bOn = ((SvxTwoLinesItem*)pItem)->GetEndBracket() ==
/*?*/                       p2Lines->GetEndBracket() &&
/*?*/                     ((SvxTwoLinesItem*)pItem)->GetStartBracket() ==
/*?*/                       p2Lines->GetStartBracket();
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           pRet->pItem = pItem;
/*?*/           pRet->pAttr = NULL;
/*?*/           aEnd.Insert( GetTxt().Len(), 0 );
/*?*/       }
/*?*/       pRet->nId = SW_MC_DOUBLE;
/*?*/ #ifdef BIDI
/*?*/         pRet->nLevel = GetTxtFrm()->IsRightToLeft() ? 1 : 0;
/*?*/ #endif
/*?*/
/*?*/       // n2Lines is the index of the last 2-line-attribute, which contains
/*?*/       // the actual position.
/*?*/       i = 0;
/*?*/       // At this moment we know that at position rPos the "winner"-attribute
/*?*/       // causes a 2-line-portion. The end of the attribute is the end of the
/*?*/       // portion, if there's no interrupting attribute.
/*?*/       // There are two kinds of interruptors:
/*?*/       // - ruby attributes stops the 2-line-attribute, the end of the
/*?*/       //   multiline is the start of the ruby attribute
/*?*/       // - 2-line-attributes with value "Off" or with different brackets,
/*?*/       //   these attributes may interrupt the winner, but they could be
/*?*/       //   neutralized by another 2-line-attribute starting at the same
/*?*/       //   position with the same brackets as the winner-attribute.
/*?*/
/*?*/       // In the following loop rPos is the critical position and it will be
/*?*/       // evaluated, if at rPos starts a interrupting or a maintaining
/*?*/       // continuity attribute.
/*?*/       while( i < nCount )
/*?*/       {
/*?*/           const SwTxtAttr *pTmp = (*pHints)[i++];
/*?*/           if( *pTmp->GetAnyEnd() <= rPos )
/*?*/               continue;
/*?*/           if( rPos < *pTmp->GetStart() )
/*?*/           {
/*?*/               // If bOn is FALSE and the next attribute starts later than rPos
/*?*/               // the winner attribute is interrupted at rPos.
/*?*/               // If the start of the next atribute is behind the end of
/*?*/               // the last attribute on the aEnd-stack, this is the endposition
/*?*/               // on the stack is the end of the 2-line portion.
/*?*/               if( !bOn || aEnd[ aEnd.Count()-1 ] < *pTmp->GetStart() )
/*?*/                   break;
/*?*/               // At this moment, bOn is TRUE and the next attribute starts
/*?*/               // behind rPos, so we could move rPos to the next startpoint
/*?*/               rPos = *pTmp->GetStart();
/*?*/               // We clean up the aEnd-stack, endpositions equal to rPos are
/*?*/               // superfluous.
/*?*/               while( aEnd.Count() && aEnd[ aEnd.Count()-1 ] <= rPos )
/*?*/               {
/*?*/                   bOn = !bOn;
/*?*/                   aEnd.Remove( aEnd.Count()-1, 1 );
/*?*/               }
/*?*/               // If the endstack is empty, we simulate an attribute with
/*?*/               // state TRUE and endposition rPos
/*?*/               if( !aEnd.Count() )
/*?*/               {
/*?*/                   aEnd.Insert( rPos, 0 );
/*?*/                   bOn = sal_True;
/*?*/               }
/*?*/           }
/*?*/           // A ruby attribute stops the 2-line immediately
/*?*/           if( RES_TXTATR_CJK_RUBY == pTmp->Which() )
/*?*/               return pRet;
/*?*/           if( lcl_Has2Lines( *pTmp, p2Lines, bTwo ) )
/*?*/           {   // We have an interesting attribute..
/*?*/               if( bTwo == bOn )
/*?*/               {   // .. with the same state, so the last attribute could
/*?*/                   // be continued.
/*?*/                   if( aEnd[ aEnd.Count()-1 ] < *pTmp->GetEnd() )
/*?*/                       aEnd[ aEnd.Count()-1 ] = *pTmp->GetEnd();
/*?*/               }
/*?*/               else
/*?*/               {   // .. with a different state.
/*?*/                   bOn = bTwo;
/*?*/                   // If this is smaller than the last on the stack, we put
/*?*/                   // it on the stack. If it has the same endposition, the last
/*?*/                   // could be removed.
/*?*/                   if( aEnd[ aEnd.Count()-1 ] > *pTmp->GetEnd() )
/*?*/                       aEnd.Insert( *pTmp->GetEnd(), aEnd.Count() );
/*?*/                   else if( aEnd.Count() > 1 )
/*?*/                       aEnd.Remove( aEnd.Count()-1, 1 );
/*?*/                   else
/*?*/                       aEnd[ aEnd.Count()-1 ] = *pTmp->GetEnd();
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       if( bOn && aEnd.Count() )
/*?*/           rPos = aEnd[ aEnd.Count()-1 ];
/*?*/       return pRet;
/*N*/   }
/*N*/   if( nRotate < nCount || ( pRotItem && pRotItem == pRotate &&
/*N*/       rPos < GetTxt().Len() ) )
/*N*/   {   // The winner is a rotate-attribute,
/*?*/       // the end of the multiportion depends on the following attributes...
/*?*/       SwMultiCreator *pRet = new SwMultiCreator;
/*?*/       pRet->nId = SW_MC_ROTATE;
/*?*/
/*?*/       // We note the endpositions of the 2-line attributes in aEnd as stack
/*?*/       SvXub_StrLens aEnd;
/*?*/
/*?*/       // The bOn flag signs the state of the last 2-line attribute in the
/*?*/       // aEnd-stack, which could interrupts the winning rotation attribute.
/*?*/       sal_Bool bOn = pItem ? sal_True : sal_False;
/*?*/       aEnd.Insert( GetTxt().Len(), 0 );
/*?*/       // n2Lines is the index of the last 2-line-attribute, which contains
/*?*/       // the actual position.
/*?*/       i = 0;
/*?*/       xub_StrLen n2Start = rPos;
/*?*/       while( i < nCount )
/*?*/       {
/*?*/           const SwTxtAttr *pTmp = (*pHints)[i++];
/*?*/           if( *pTmp->GetAnyEnd() <= n2Start )
/*?*/               continue;
/*?*/           if( n2Start < *pTmp->GetStart() )
/*?*/           {
/*?*/               if( bOn || aEnd[ aEnd.Count()-1 ] < *pTmp->GetStart() )
/*?*/                   break;
/*?*/               n2Start = *pTmp->GetStart();
/*?*/               while( aEnd.Count() && aEnd[ aEnd.Count()-1 ] <= n2Start )
/*?*/               {
/*?*/                   bOn = !bOn;
/*?*/                   aEnd.Remove( aEnd.Count()-1, 1 );
/*?*/               }
/*?*/               if( !aEnd.Count() )
/*?*/               {
/*?*/                   aEnd.Insert( n2Start, 0 );
/*?*/                   bOn = sal_False;
/*?*/               }
/*?*/           }
/*?*/           // A ruby attribute stops immediately
/*?*/           if( RES_TXTATR_CJK_RUBY == pTmp->Which() )
/*?*/           {
/*?*/               bOn = sal_True;
/*?*/               break;
/*?*/           }
/*?*/           p2Lines = NULL;
/*?*/           if( lcl_Has2Lines( *pTmp, p2Lines, bTwo ) )
/*?*/           {
/*?*/               if( bTwo == bOn )
/*?*/               {
/*?*/                   if( aEnd[ aEnd.Count()-1 ] < *pTmp->GetEnd() )
/*?*/                       aEnd[ aEnd.Count()-1 ] = *pTmp->GetEnd();
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   bOn = bTwo;
/*?*/                   if( aEnd[ aEnd.Count()-1 ] > *pTmp->GetEnd() )
/*?*/                       aEnd.Insert( *pTmp->GetEnd(), aEnd.Count() );
/*?*/                   else if( aEnd.Count() > 1 )
/*?*/                       aEnd.Remove( aEnd.Count()-1, 1 );
/*?*/                   else
/*?*/                       aEnd[ aEnd.Count()-1 ] = *pTmp->GetEnd();
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       if( !bOn && aEnd.Count() )
/*?*/           n2Start = aEnd[ aEnd.Count()-1 ];
/*?*/
/*?*/       if( aEnd.Count() )
/*?*/           aEnd.Remove( 0, aEnd.Count() );
/*?*/
/*?*/       bOn = sal_True;
/*?*/       if( nRotate < nCount )
/*?*/       {
/*?*/           pRet->pItem = NULL;
/*?*/           pRet->pAttr = (*pHints)[nRotate];
/*?*/           aEnd.Insert( *pRet->pAttr->GetEnd(), 0 );
/*?*/           if( pRotItem )
/*?*/           {
/*?*/               aEnd[ 0 ] = GetTxt().Len();
/*?*/               bOn = ((SvxCharRotateItem*)pRotItem)->GetValue() ==
/*?*/                       pRotate->GetValue();
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           pRet->pItem = pRotItem;
/*?*/           pRet->pAttr = NULL;
/*?*/           aEnd.Insert( GetTxt().Len(), 0 );
/*?*/       }
/*?*/       i = 0;
/*?*/       while( i < nCount )
/*?*/       {
/*?*/           const SwTxtAttr *pTmp = (*pHints)[i++];
/*?*/           if( *pTmp->GetAnyEnd() <= rPos )
/*?*/               continue;
/*?*/           if( rPos < *pTmp->GetStart() )
/*?*/           {
/*?*/               if( !bOn || aEnd[ aEnd.Count()-1 ] < *pTmp->GetStart() )
/*?*/                   break;
/*?*/               rPos = *pTmp->GetStart();
/*?*/               while( aEnd.Count() && aEnd[ aEnd.Count()-1 ] <= rPos )
/*?*/               {
/*?*/                   bOn = !bOn;
/*?*/                   aEnd.Remove( aEnd.Count()-1, 1 );
/*?*/               }
/*?*/               if( !aEnd.Count() )
/*?*/               {
/*?*/                   aEnd.Insert( rPos, 0 );
/*?*/                   bOn = sal_True;
/*?*/               }
/*?*/           }
/*?*/           if( RES_TXTATR_CJK_RUBY == pTmp->Which() )
/*?*/           {
/*?*/               bOn = sal_False;
/*?*/               break;
/*?*/           }
/*?*/           if( lcl_HasRotation( *pTmp, pRotate, bTwo ) )
/*?*/           {
/*?*/               if( bTwo == bOn )
/*?*/               {
/*?*/                   if( aEnd[ aEnd.Count()-1 ] < *pTmp->GetEnd() )
/*?*/                       aEnd[ aEnd.Count()-1 ] = *pTmp->GetEnd();
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   bOn = bTwo;
/*?*/                   if( aEnd[ aEnd.Count()-1 ] > *pTmp->GetEnd() )
/*?*/                       aEnd.Insert( *pTmp->GetEnd(), aEnd.Count() );
/*?*/                   else if( aEnd.Count() > 1 )
/*?*/                       aEnd.Remove( aEnd.Count()-1, 1 );
/*?*/                   else
/*?*/                       aEnd[ aEnd.Count()-1 ] = *pTmp->GetEnd();
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       if( bOn && aEnd.Count() )
/*?*/           rPos = aEnd[ aEnd.Count()-1 ];
/*?*/       if( rPos > n2Start )
/*?*/           rPos = n2Start;
/*?*/       return pRet;
/*N*/   }
/*N*/   return NULL;
/*N*/ }

/*-----------------01.11.00 14:52-------------------
 * SwSpaceManipulator
 * is a little helper class to manage the spaceadd-arrays of the text adjustment
 * during a PaintMultiPortion.
 * The constructor prepares the array for the first line of multiportion,
 * the SecondLine-function restores the values for the first line and prepares
 * the second line.
 * The destructor restores the values of the last manipulation.
 * --------------------------------------------------*/

//STRIP001 class SwSpaceManipulator
//STRIP001 {
//STRIP001  SwTxtPaintInfo& rInfo;
//STRIP001  SwMultiPortion& rMulti;
//STRIP001  SvShorts *pOldSpaceAdd;
//STRIP001  MSHORT nOldSpIdx;
//STRIP001  short nSpaceAdd;
//STRIP001  sal_Bool bSpaceChg  : 1;
//STRIP001  sal_uInt8 nOldDir   : 2;
//STRIP001 public:
//STRIP001  SwSpaceManipulator( SwTxtPaintInfo& rInf, SwMultiPortion& rMult );
//STRIP001  ~SwSpaceManipulator();
//STRIP001  void SecondLine();
//STRIP001  inline short GetSpaceAdd() const { return nSpaceAdd; }
//STRIP001 };

//STRIP001 SwSpaceManipulator::SwSpaceManipulator( SwTxtPaintInfo& rInf,
//STRIP001  SwMultiPortion& rMult ) : rInfo( rInf ), rMulti( rMult )
//STRIP001 {
//STRIP001  pOldSpaceAdd = rInfo.GetpSpaceAdd();
//STRIP001  nOldSpIdx = rInfo.GetSpaceIdx();
//STRIP001  nOldDir = rInfo.GetDirection();
//STRIP001  rInfo.SetDirection( rMulti.GetDirection() );
//STRIP001  bSpaceChg = sal_False;
//STRIP001
//STRIP001     if( rMulti.IsDouble() )
//STRIP001  {
//STRIP001      nSpaceAdd = ( pOldSpaceAdd && !rMulti.HasTabulator() ) ?
//STRIP001                    rInfo.GetSpaceAdd() : 0;
//STRIP001      if( rMulti.GetRoot().GetpSpaceAdd() )
//STRIP001      {
//STRIP001          rInfo.SetSpaceAdd( rMulti.GetRoot().GetpSpaceAdd() );
//STRIP001          rInfo.ResetSpaceIdx();
//STRIP001          bSpaceChg = rMulti.ChgSpaceAdd( &rMulti.GetRoot(), nSpaceAdd );
//STRIP001      }
//STRIP001      else if( rMulti.HasTabulator() )
//STRIP001          rInfo.SetSpaceAdd( NULL );
//STRIP001  }
//STRIP001 #ifdef BIDI
//STRIP001     else if ( ! rMulti.IsBidi() )
//STRIP001 #else
//STRIP001  else
//STRIP001 #endif
//STRIP001  {
//STRIP001      rInfo.SetSpaceAdd( rMulti.GetRoot().GetpSpaceAdd() );
//STRIP001      rInfo.ResetSpaceIdx();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwSpaceManipulator::SecondLine()
//STRIP001 {
//STRIP001  if( bSpaceChg )
//STRIP001  {
//STRIP001      rInfo.GetpSpaceAdd()->Remove( 0 );
//STRIP001      bSpaceChg = sal_False;
//STRIP001  }
//STRIP001  SwLineLayout *pLay = rMulti.GetRoot().GetNext();
//STRIP001  if( pLay->GetpSpaceAdd() )
//STRIP001  {
//STRIP001      rInfo.SetSpaceAdd( pLay->GetpSpaceAdd() );
//STRIP001      rInfo.ResetSpaceIdx();
//STRIP001      bSpaceChg = rMulti.ChgSpaceAdd( pLay, nSpaceAdd );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rInfo.SetSpaceAdd( (!rMulti.IsDouble() || rMulti.HasTabulator() ) ?
//STRIP001                              0 : pOldSpaceAdd );
//STRIP001      rInfo.SetSpaceIdx( nOldSpIdx);
//STRIP001  }
//STRIP001 }

//STRIP001 SwSpaceManipulator::~SwSpaceManipulator()
//STRIP001 {
//STRIP001  if( bSpaceChg )
//STRIP001  {
//STRIP001      rInfo.GetpSpaceAdd()->Remove( 0 );
//STRIP001      bSpaceChg = sal_False;
//STRIP001  }
//STRIP001  rInfo.SetSpaceAdd( pOldSpaceAdd );
//STRIP001  rInfo.SetSpaceIdx( nOldSpIdx);
//STRIP001  rInfo.SetDirection( nOldDir );
//STRIP001 }

/*-----------------13.10.00 16:24-------------------
 * SwTxtPainter::PaintMultiPortion manages the paint for a SwMultiPortion.
 * External, for the calling function, it seems to be a normal Paint-function,
 * internal it is like a SwTxtFrm::Paint with multiple DrawTextLines
 * --------------------------------------------------*/

//STRIP001 #ifdef BIDI
//STRIP001 void SwTxtPainter::PaintMultiPortion( const SwRect &rPaint,
//STRIP001     SwMultiPortion& rMulti, const SwMultiPortion* pEnvPor )
//STRIP001 #else
//STRIP001 void SwTxtPainter::PaintMultiPortion( const SwRect &rPaint,
//STRIP001     SwMultiPortion& rMulti )
//STRIP001 #endif
//STRIP001 {
//STRIP001     GETGRID( pFrm->FindPageFrm() )
//STRIP001     const sal_Bool bHasGrid = pGrid && GetInfo().SnapToGrid();
//STRIP001     USHORT nGridWidth = 0;
//STRIP001     USHORT nRubyHeight = 0;
//STRIP001     sal_Bool bRubyTop = sal_False;
//STRIP001
//STRIP001     if ( bHasGrid )
//STRIP001     {
//STRIP001         nGridWidth = pGrid->GetBaseHeight();
//STRIP001         nRubyHeight = pGrid->GetRubyHeight();
//STRIP001         bRubyTop = ! pGrid->GetRubyTextBelow();
//STRIP001     }
//STRIP001
//STRIP001     // do not allow grid mode for first line in ruby portion
//STRIP001     const sal_Bool bRubyInGrid = bHasGrid && rMulti.IsRuby();
//STRIP001
//STRIP001     const USHORT nOldHeight = rMulti.Height();
//STRIP001     const sal_Bool bOldGridModeAllowed = GetInfo().SnapToGrid();
//STRIP001
//STRIP001     if ( bRubyInGrid )
//STRIP001     {
//STRIP001         GetInfo().SetSnapToGrid( ! bRubyTop );
//STRIP001         rMulti.Height( pCurr->Height() );
//STRIP001     }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     SwLayoutModeModifier aLayoutModeModifier( *GetInfo().GetOut() );
//STRIP001     BYTE nEnvDir, nThisDir, nFrmDir;
//STRIP001     if ( rMulti.IsBidi() )
//STRIP001     {
//STRIP001         // these values are needed for the calculation of the x coordinate
//STRIP001         // and the layout mode
//STRIP001         ASSERT( ! pEnvPor || pEnvPor->IsBidi(),
//STRIP001                 "Oh no, I expected a BidiPortion" )
//STRIP001         nFrmDir = GetInfo().GetTxtFrm()->IsRightToLeft() ? 1 : 0;
//STRIP001         nEnvDir = pEnvPor ? ((SwBidiPortion*)pEnvPor)->GetLevel() % 2 : nFrmDir;
//STRIP001         nThisDir = ((SwBidiPortion&)rMulti).GetLevel() % 2;
//STRIP001     }
//STRIP001 #endif
//STRIP001
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001     // only paint first level bidi portions
//STRIP001     if( rMulti.Width() > 1 && ! pEnvPor )
//STRIP001         GetInfo().DrawViewOpt( rMulti, POR_FLD );
//STRIP001 #endif
//STRIP001
//STRIP001     if ( bRubyInGrid )
//STRIP001         rMulti.Height( nOldHeight );
//STRIP001
//STRIP001     // do we have to repaint a post it portion?
//STRIP001     if( GetInfo().OnWin() && rMulti.GetPortion() &&
//STRIP001         ! rMulti.GetPortion()->Width() )
//STRIP001         rMulti.GetPortion()->PrePaint( GetInfo(), &rMulti );
//STRIP001
//STRIP001  // old values must be saved and restored at the end
//STRIP001  xub_StrLen nOldLen = GetInfo().GetLen();
//STRIP001  KSHORT nOldX = KSHORT(GetInfo().X());
//STRIP001     long nOldY = GetInfo().Y();
//STRIP001  xub_StrLen nOldIdx = GetInfo().GetIdx();
//STRIP001
//STRIP001  SwSpaceManipulator aManip( GetInfo(), rMulti );
//STRIP001
//STRIP001  SwFontSave *pFontSave;
//STRIP001  SwFont* pTmpFnt;
//STRIP001
//STRIP001  if( rMulti.IsDouble() )
//STRIP001  {
//STRIP001      pTmpFnt = new SwFont( *GetInfo().GetFont() );
//STRIP001      if( rMulti.IsDouble() )
//STRIP001      {
//STRIP001          SetPropFont( 50 );
//STRIP001          pTmpFnt->SetProportion( GetPropFont() );
//STRIP001      }
//STRIP001      pFontSave = new SwFontSave( GetInfo(), pTmpFnt, this );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pFontSave = NULL;
//STRIP001      pTmpFnt = NULL;
//STRIP001  }
//STRIP001
//STRIP001  if( rMulti.HasBrackets() )
//STRIP001  {
//STRIP001      xub_StrLen nOldIdx = GetInfo().GetIdx();
//STRIP001      GetInfo().SetIdx(((SwDoubleLinePortion&)rMulti).GetBrackets()->nStart);
//STRIP001      SeekAndChg( GetInfo() );
//STRIP001      ((SwDoubleLinePortion&)rMulti).PaintBracket( GetInfo(), 0, sal_True );
//STRIP001      GetInfo().SetIdx( nOldIdx );
//STRIP001  }
//STRIP001
//STRIP001  KSHORT nTmpX = KSHORT(GetInfo().X());
//STRIP001
//STRIP001  SwLineLayout* pLay = &rMulti.GetRoot();// the first line of the multiportion
//STRIP001  SwLinePortion* pPor = pLay->GetFirstPortion();//first portion of these line
//STRIP001     SwTwips nOfst = 0;
//STRIP001
//STRIP001     // GetInfo().Y() is the baseline from the surrounding line. We must switch
//STRIP001  // this temporary to the baseline of the inner lines of the multiportion.
//STRIP001     if( rMulti.HasRotation() )
//STRIP001     {
//STRIP001         if( rMulti.IsRevers() )
//STRIP001         {
//STRIP001             GetInfo().Y( nOldY - rMulti.GetAscent() );
//STRIP001             nOfst = nTmpX + rMulti.Width();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             GetInfo().Y( nOldY - rMulti.GetAscent() + rMulti.Height() );
//STRIP001             nOfst = nTmpX;
//STRIP001         }
//STRIP001     }
//STRIP001 #ifdef BIDI
//STRIP001     else if ( rMulti.IsBidi() )
//STRIP001     {
//STRIP001         // does the current bidi portion has the same direction
//STRIP001         // as its environment?
//STRIP001         if ( nEnvDir != nThisDir )
//STRIP001         {
//STRIP001             // different directions, we have to adjust the x coordinate
//STRIP001             SwTwips nMultiWidth = rMulti.Width() +
//STRIP001                     rMulti.CalcSpacing( GetInfo().GetSpaceAdd(), GetInfo() );
//STRIP001
//STRIP001             if ( nFrmDir == nThisDir )
//STRIP001                 GetInfo().X( GetInfo().X() - nMultiWidth );
//STRIP001             else
//STRIP001                 GetInfo().X( GetInfo().X() + nMultiWidth );
//STRIP001         }
//STRIP001
//STRIP001         nOfst = nOldY - rMulti.GetAscent();
//STRIP001
//STRIP001         // set layout mode
//STRIP001         aLayoutModeModifier.Modify( nThisDir );
//STRIP001     }
//STRIP001 #endif
//STRIP001     else
//STRIP001         nOfst = nOldY - rMulti.GetAscent();
//STRIP001
//STRIP001     sal_Bool bRest = pLay->IsRest();
//STRIP001  sal_Bool bFirst = sal_True;
//STRIP001
//STRIP001     ASSERT( 0 == GetInfo().GetUnderFnt() || rMulti.IsBidi(),
//STRIP001             " Only BiDi portions are allowed to use the common underlining font" )
//STRIP001
//STRIP001     do
//STRIP001  {
//STRIP001         if ( bHasGrid )
//STRIP001         {
//STRIP001             if( rMulti.HasRotation() )
//STRIP001             {
//STRIP001                 const USHORT nAdjustment = ( pLay->Height() - pPor->Height() ) / 2 +
//STRIP001                                             pPor->GetAscent();
//STRIP001                 if( rMulti.IsRevers() )
//STRIP001                     GetInfo().X( nOfst - nAdjustment );
//STRIP001                 else
//STRIP001                     GetInfo().X( nOfst + nAdjustment );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // special treatment for ruby portions in grid mode
//STRIP001                 SwTwips nAdjustment = 0;
//STRIP001                 if ( rMulti.IsRuby() )
//STRIP001                 {
//STRIP001                     if ( bRubyTop != ( pLay == &rMulti.GetRoot() ) )
//STRIP001                         // adjust base text
//STRIP001                         nAdjustment = ( pCurr->Height() - nRubyHeight - pPor->Height() ) / 2;
//STRIP001                     else if ( bRubyTop )
//STRIP001                         // adjust upper ruby text
//STRIP001                         nAdjustment = nRubyHeight - pPor->Height();
//STRIP001                     // else adjust lower ruby text
//STRIP001                 }
//STRIP001
//STRIP001                 GetInfo().Y( nOfst + nAdjustment + pPor->GetAscent() );
//STRIP001             }
//STRIP001         }
//STRIP001         else if( rMulti.HasRotation() )
//STRIP001         {
//STRIP001             if( rMulti.IsRevers() )
//STRIP001                 GetInfo().X( nOfst - AdjustBaseLine( *pLay, pPor, 0, 0, sal_True ) );
//STRIP001             else
//STRIP001                 GetInfo().X( nOfst + AdjustBaseLine( *pLay, pPor ) );
//STRIP001         }
//STRIP001         else
//STRIP001             GetInfo().Y( nOfst + AdjustBaseLine( *pLay, pPor ) );
//STRIP001
//STRIP001         sal_Bool bSeeked = sal_True;
//STRIP001      GetInfo().SetLen( pPor->GetLen() );
//STRIP001
//STRIP001         if( bRest && pPor->InFldGrp() && !pPor->GetLen() )
//STRIP001      {
//STRIP001          if( ((SwFldPortion*)pPor)->HasFont() )
//STRIP001              bSeeked = sal_False;
//STRIP001          else
//STRIP001              SeekAndChgBefore( GetInfo() );
//STRIP001      }
//STRIP001      else if( pPor->InTxtGrp() || pPor->InFldGrp() || pPor->InTabGrp() )
//STRIP001          SeekAndChg( GetInfo() );
//STRIP001      else if ( !bFirst && pPor->IsBreakPortion() && GetInfo().GetOpt().IsParagraph() )
//STRIP001      {
//STRIP001          if( GetRedln() )
//STRIP001              SeekAndChg( GetInfo() );
//STRIP001          else
//STRIP001              SeekAndChgBefore( GetInfo() );
//STRIP001      }
//STRIP001      else
//STRIP001             bSeeked = sal_False;
//STRIP001
//STRIP001      SwLinePortion *pNext = pPor->GetPortion();
//STRIP001      if(GetInfo().OnWin() && pNext && !pNext->Width() )
//STRIP001      {
//STRIP001          if ( !bSeeked )
//STRIP001              SeekAndChg( GetInfo() );
//STRIP001             pNext->PrePaint( GetInfo(), pPor );
//STRIP001      }
//STRIP001
//STRIP001         CheckSpecialUnderline( pPor );
//STRIP001         SwUnderlineFont* pUnderLineFnt = GetInfo().GetUnderFnt();
//STRIP001         if ( pUnderLineFnt )
//STRIP001         {
//STRIP001             if ( rMulti.IsDouble() )
//STRIP001                 pUnderLineFnt->GetFont().SetProportion( 50 );
//STRIP001             pUnderLineFnt->SetPos( GetInfo().GetPos() );
//STRIP001         }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if ( rMulti.IsBidi() )
//STRIP001         {
//STRIP001             // we do not allow any rotation inside a bidi portion
//STRIP001             SwFont* pFnt = GetInfo().GetFont();
//STRIP001             pFnt->SetVertical( 0, GetInfo().GetTxtFrm()->IsVertical() );
//STRIP001         }
//STRIP001
//STRIP001         if( pPor->IsMultiPortion() && ((SwMultiPortion*)pPor)->IsBidi() )
//STRIP001         {
//STRIP001             // but we do allow nested bidi portions
//STRIP001             ASSERT( rMulti.IsBidi(), "Only nesting of bidi portions is allowed" )
//STRIP001             PaintMultiPortion( rPaint, (SwMultiPortion&)*pPor, &rMulti );
//STRIP001         }
//STRIP001         else
//STRIP001             pPor->Paint( GetInfo() );
//STRIP001 #else
//STRIP001         pPor->Paint( GetInfo() );
//STRIP001 #endif
//STRIP001
//STRIP001         if( GetFnt()->IsURL() && pPor->InTxtGrp() )
//STRIP001          GetInfo().NotifyURL( *pPor );
//STRIP001
//STRIP001      bFirst &= !pPor->GetLen();
//STRIP001      if( pNext || !pPor->IsMarginPortion() )
//STRIP001          pPor->Move( GetInfo() );
//STRIP001
//STRIP001         pPor = pNext;
//STRIP001
//STRIP001      // If there's no portion left, we go to the next line
//STRIP001      if( !pPor && pLay->GetNext() )
//STRIP001      {
//STRIP001             pLay = pLay->GetNext();
//STRIP001             pPor = pLay->GetFirstPortion();
//STRIP001             bRest = pLay->IsRest();
//STRIP001             aManip.SecondLine();
//STRIP001
//STRIP001             // delete underline font
//STRIP001             delete GetInfo().GetUnderFnt();
//STRIP001             GetInfo().SetUnderFnt( 0 );
//STRIP001
//STRIP001             if( rMulti.HasRotation() )
//STRIP001             {
//STRIP001                 if( rMulti.IsRevers() )
//STRIP001                 {
//STRIP001                     nOfst += pLay->Height();
//STRIP001                     GetInfo().Y( nOldY - rMulti.GetAscent() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     nOfst -= pLay->Height();
//STRIP001                     GetInfo().Y( nOldY - rMulti.GetAscent() + rMulti.Height() );
//STRIP001                 }
//STRIP001             }
//STRIP001             else if ( bHasGrid && rMulti.IsRuby() )
//STRIP001             {
//STRIP001                 GetInfo().X( nTmpX );
//STRIP001                 if ( bRubyTop )
//STRIP001                 {
//STRIP001                     nOfst += nRubyHeight;
//STRIP001                     GetInfo().SetSnapToGrid( sal_True );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     nOfst += pCurr->Height() - nRubyHeight;
//STRIP001                     GetInfo().SetSnapToGrid( sal_False );
//STRIP001                 }
//STRIP001             } else
//STRIP001             {
//STRIP001                 GetInfo().X( nTmpX );
//STRIP001                 // We switch to the baseline of the next inner line
//STRIP001                 nOfst += rMulti.GetRoot().Height();
//STRIP001             }
//STRIP001      }
//STRIP001  } while( pPor );
//STRIP001
//STRIP001     if ( bRubyInGrid )
//STRIP001         GetInfo().SetSnapToGrid( bOldGridModeAllowed );
//STRIP001
//STRIP001     // delete underline font
//STRIP001     if ( ! rMulti.IsBidi() )
//STRIP001     {
//STRIP001         delete GetInfo().GetUnderFnt();
//STRIP001         GetInfo().SetUnderFnt( 0 );
//STRIP001     }
//STRIP001
//STRIP001     GetInfo().SetIdx( nOldIdx );
//STRIP001  GetInfo().Y( nOldY );
//STRIP001
//STRIP001  if( rMulti.HasBrackets() )
//STRIP001  {
//STRIP001      xub_StrLen nOldIdx = GetInfo().GetIdx();
//STRIP001      GetInfo().SetIdx(((SwDoubleLinePortion&)rMulti).GetBrackets()->nStart);
//STRIP001      SeekAndChg( GetInfo() );
//STRIP001      GetInfo().X( nOldX );
//STRIP001      ((SwDoubleLinePortion&)rMulti).PaintBracket( GetInfo(),
//STRIP001          aManip.GetSpaceAdd(), sal_False );
//STRIP001      GetInfo().SetIdx( nOldIdx );
//STRIP001  }
//STRIP001  // Restore the saved values
//STRIP001  GetInfo().X( nOldX );
//STRIP001  GetInfo().SetLen( nOldLen );
//STRIP001  delete pFontSave;
//STRIP001  delete pTmpFnt;
//STRIP001  SetPropFont( 0 );
//STRIP001 }

//STRIP001 sal_Bool lcl_ExtractFieldFollow( SwLineLayout* pLine, SwLinePortion* &rpFld )
//STRIP001 {
//STRIP001  SwLinePortion* pLast = pLine;
//STRIP001  rpFld = pLine->GetPortion();
//STRIP001  while( rpFld && !rpFld->InFldGrp() )
//STRIP001  {
//STRIP001      pLast = rpFld;
//STRIP001      rpFld = rpFld->GetPortion();
//STRIP001  }
//STRIP001  sal_Bool bRet = rpFld != 0;
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      if( ((SwFldPortion*)rpFld)->IsFollow() )
//STRIP001      {
//STRIP001          rpFld->Truncate();
//STRIP001          pLast->SetPortion( NULL );
//STRIP001      }
//STRIP001      else
//STRIP001          rpFld = NULL;
//STRIP001  }
//STRIP001  pLine->Truncate();
//STRIP001  return bRet;
//STRIP001 }

/*----------------------------------------------------
 *              lcl_TruncateMultiPortion
 * If a multi portion completely has to go to the
 * next line, this function is called to trunctate
 * the rest of the remaining multi portion
 * --------------------------------------------------*/

//STRIP001 void lcl_TruncateMultiPortion( SwMultiPortion& rMulti, SwTxtFormatInfo& rInf,
//STRIP001                                xub_StrLen nStartIdx )
//STRIP001 {
//STRIP001     rMulti.GetRoot().Truncate();
//STRIP001     rMulti.GetRoot().SetLen(0);
//STRIP001     rMulti.GetRoot().Width(0);
//STRIP001 //  rMulti.CalcSize( *this, aInf );
//STRIP001     if ( rMulti.GetRoot().GetNext() )
//STRIP001     {
//STRIP001         rMulti.GetRoot().GetNext()->Truncate();
//STRIP001         rMulti.GetRoot().GetNext()->SetLen( 0 );
//STRIP001         rMulti.GetRoot().GetNext()->Width( 0 );
//STRIP001     }
//STRIP001     rMulti.Width( 0 );
//STRIP001     rMulti.SetLen(0);
//STRIP001     rInf.SetIdx( nStartIdx );
//STRIP001 }

/*-----------------------------------------------------------------------------
 *              SwTxtFormatter::BuildMultiPortion
 * manages the formatting of a SwMultiPortion. External, for the calling
 * function, it seems to be a normal Format-function, internal it is like a
 * SwTxtFrm::_Format with multiple BuildPortions
 *---------------------------------------------------------------------------*/

//STRIP001 BOOL SwTxtFormatter::BuildMultiPortion( SwTxtFormatInfo &rInf,
//STRIP001  SwMultiPortion& rMulti )
//STRIP001 {
//STRIP001  SwTwips nMaxWidth = rInf.Width();
//STRIP001     KSHORT nOldX;
//STRIP001
//STRIP001  if( rMulti.HasBrackets() )
//STRIP001  {
//STRIP001      xub_StrLen nOldIdx = rInf.GetIdx();
//STRIP001      rInf.SetIdx( ((SwDoubleLinePortion&)rMulti).GetBrackets()->nStart );
//STRIP001      SeekAndChg( rInf );
//STRIP001         nOldX = KSHORT(GetInfo().X());
//STRIP001      ((SwDoubleLinePortion&)rMulti).FormatBrackets( rInf, nMaxWidth );
//STRIP001      rInf.SetIdx( nOldIdx );
//STRIP001  }
//STRIP001
//STRIP001  SeekAndChg( rInf );
//STRIP001  SwFontSave *pFontSave;
//STRIP001  if( rMulti.IsDouble() )
//STRIP001  {
//STRIP001      SwFont* pTmpFnt = new SwFont( *rInf.GetFont() );
//STRIP001      if( rMulti.IsDouble() )
//STRIP001      {
//STRIP001          SetPropFont( 50 );
//STRIP001          pTmpFnt->SetProportion( GetPropFont() );
//STRIP001      }
//STRIP001      pFontSave = new SwFontSave( rInf, pTmpFnt, this );
//STRIP001  }
//STRIP001  else
//STRIP001      pFontSave = NULL;
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     SwLayoutModeModifier aLayoutModeModifier( *GetInfo().GetOut() );
//STRIP001     if ( rMulti.IsBidi() )
//STRIP001     {
//STRIP001         // set layout mode
//STRIP001         aLayoutModeModifier.Modify( ! rInf.GetTxtFrm()->IsRightToLeft() );
//STRIP001     }
//STRIP001 #endif
//STRIP001
//STRIP001     SwTwips nTmpX = 0;
//STRIP001
//STRIP001     if( rMulti.HasRotation() )
//STRIP001     {
//STRIP001         // For nMaxWidth we take the height of the body frame
//STRIP001         // We set nTmpX (which is used for portion calculating) to the
//STRIP001         // current Y value
//STRIP001         const SwPageFrm* pPage = pFrm->FindPageFrm();
//STRIP001         ASSERT( pPage, "No page in frame!");
//STRIP001         const SwLayoutFrm* pUpperFrm = pPage;
//STRIP001
//STRIP001         if ( ! pFrm->IsInFtn() )
//STRIP001             pUpperFrm = pPage->FindBodyCont();
//STRIP001
//STRIP001         nMaxWidth = pUpperFrm ? ( rInf.GetTxtFrm()->IsVertical() ?
//STRIP001                                 pUpperFrm->Prt().Width() :
//STRIP001                                 pUpperFrm->Prt().Height() ) :
//STRIP001                     USHRT_MAX;
//STRIP001     }
//STRIP001     else
//STRIP001         nTmpX = rInf.X();
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     SwMultiPortion* pOldMulti = pMulti;
//STRIP001 #endif
//STRIP001
//STRIP001     pMulti = &rMulti;
//STRIP001  SwLineLayout *pOldCurr = pCurr;
//STRIP001  xub_StrLen nOldStart = GetStart();
//STRIP001  SwTwips nMinWidth = nTmpX + 1;
//STRIP001     SwTwips nActWidth = nMaxWidth;
//STRIP001     const xub_StrLen nStartIdx = rInf.GetIdx();
//STRIP001  xub_StrLen nMultiLen = rMulti.GetLen();
//STRIP001
//STRIP001  SwLinePortion *pFirstRest;
//STRIP001  SwLinePortion *pSecondRest;
//STRIP001  if( rMulti.IsFormatted() )
//STRIP001  {
//STRIP001      if( !lcl_ExtractFieldFollow( &rMulti.GetRoot(), pFirstRest )
//STRIP001          && rMulti.IsDouble() && rMulti.GetRoot().GetNext() )
//STRIP001          lcl_ExtractFieldFollow( rMulti.GetRoot().GetNext(), pFirstRest );
//STRIP001      if( !rMulti.IsDouble() && rMulti.GetRoot().GetNext() )
//STRIP001          lcl_ExtractFieldFollow( rMulti.GetRoot().GetNext(), pSecondRest );
//STRIP001      else
//STRIP001          pSecondRest = NULL;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pFirstRest = rMulti.GetRoot().GetPortion();
//STRIP001      pSecondRest = rMulti.GetRoot().GetNext() ?
//STRIP001                    rMulti.GetRoot().GetNext()->GetPortion() : NULL;
//STRIP001      if( pFirstRest )
//STRIP001          rMulti.GetRoot().SetPortion( NULL );
//STRIP001      if( pSecondRest )
//STRIP001          rMulti.GetRoot().GetNext()->SetPortion( NULL );
//STRIP001      rMulti.SetFormatted();
//STRIP001      nMultiLen -= rInf.GetIdx();
//STRIP001  }
//STRIP001
//STRIP001     // save some values
//STRIP001  const XubString* pOldTxt = &(rInf.GetTxt());
//STRIP001     const SwTwips nOldPaintOfst = rInf.GetPaintOfst();
//STRIP001
//STRIP001  XubString aMultiStr( rInf.GetTxt(), 0, nMultiLen + rInf.GetIdx() );
//STRIP001  rInf.SetTxt( aMultiStr );
//STRIP001  SwTxtFormatInfo aInf( rInf, rMulti.GetRoot(), nActWidth );
//STRIP001     // Do we allow break cuts? The FirstMulti-Flag is evaluated during
//STRIP001     // line break determination.
//STRIP001     sal_Bool bFirstMulti = rInf.GetIdx() != rInf.GetLineStart();
//STRIP001
//STRIP001  SwLinePortion *pNextFirst = NULL;
//STRIP001  SwLinePortion *pNextSecond = NULL;
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001     GETGRID( pFrm->FindPageFrm() )
//STRIP001     const sal_Bool bHasGrid = pGrid && GRID_LINES_CHARS == pGrid->GetGridType();
//STRIP001
//STRIP001     USHORT nGridWidth = 0;
//STRIP001     USHORT nRubyHeight = 0;
//STRIP001     sal_Bool bRubyTop = sal_False;
//STRIP001
//STRIP001     if ( bHasGrid )
//STRIP001     {
//STRIP001         nGridWidth = pGrid->GetBaseHeight();
//STRIP001         nRubyHeight = pGrid->GetRubyHeight();
//STRIP001         bRubyTop = ! pGrid->GetRubyTextBelow();
//STRIP001     }
//STRIP001
//STRIP001  do
//STRIP001  {
//STRIP001      pCurr = &rMulti.GetRoot();
//STRIP001      nStart = nStartIdx;
//STRIP001      bRet = FALSE;
//STRIP001      FormatReset( aInf );
//STRIP001      aInf.X( nTmpX );
//STRIP001      aInf.Width( KSHORT(nActWidth) );
//STRIP001      aInf.RealWidth( KSHORT(nActWidth) );
//STRIP001         aInf.SetFirstMulti( bFirstMulti );
//STRIP001         aInf.SetNumDone( rInf.IsNumDone() );
//STRIP001         aInf.SetFtnDone( rInf.IsFtnDone() );
//STRIP001
//STRIP001         if( pFirstRest )
//STRIP001      {
//STRIP001             ASSERT( pFirstRest->InFldGrp(), "BuildMulti: Fieldrest expected");
//STRIP001          SwFldPortion *pFld =
//STRIP001              ((SwFldPortion*)pFirstRest)->Clone(
//STRIP001                  ((SwFldPortion*)pFirstRest)->GetExp() );
//STRIP001          pFld->SetFollow( sal_True );
//STRIP001          aInf.SetRest( pFld );
//STRIP001      }
//STRIP001      aInf.SetRuby( rMulti.IsRuby() && rMulti.OnTop() );
//STRIP001
//STRIP001         // in grid mode we temporarily have to disable the grid for the ruby line
//STRIP001         const sal_Bool bOldGridModeAllowed = GetInfo().SnapToGrid();
//STRIP001         if ( bHasGrid && aInf.IsRuby() && bRubyTop )
//STRIP001             aInf.SetSnapToGrid( sal_False );
//STRIP001
//STRIP001         // If there's no more rubytext, then buildportion is forbidden
//STRIP001      if( pFirstRest || !aInf.IsRuby() )
//STRIP001          BuildPortions( aInf );
//STRIP001
//STRIP001         aInf.SetSnapToGrid( bOldGridModeAllowed );
//STRIP001
//STRIP001      rMulti.CalcSize( *this, aInf );
//STRIP001         pCurr->SetRealHeight( pCurr->Height() );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if( rMulti.IsBidi() )
//STRIP001         {
//STRIP001             pNextFirst = aInf.GetRest();
//STRIP001             break;
//STRIP001         }
//STRIP001 #endif
//STRIP001
//STRIP001      if( rMulti.HasRotation() && !rMulti.IsDouble() )
//STRIP001          break;
//STRIP001         // second line has to be formatted
//STRIP001         else if( pCurr->GetLen()<nMultiLen || rMulti.IsRuby() || aInf.GetRest())
//STRIP001      {
//STRIP001          xub_StrLen nFirstLen = pCurr->GetLen();
//STRIP001          delete pCurr->GetNext();
//STRIP001          pCurr->SetNext( new SwLineLayout() );
//STRIP001             pCurr = pCurr->GetNext();
//STRIP001          nStart = aInf.GetIdx();
//STRIP001          aInf.X( nTmpX );
//STRIP001          SwTxtFormatInfo aTmp( aInf, *pCurr, nActWidth );
//STRIP001          if( rMulti.IsRuby() )
//STRIP001          {
//STRIP001              aTmp.SetRuby( !rMulti.OnTop() );
//STRIP001              pNextFirst = aInf.GetRest();
//STRIP001              if( pSecondRest )
//STRIP001              {
//STRIP001                     ASSERT( pSecondRest->InFldGrp(), "Fieldrest expected");
//STRIP001                  SwFldPortion *pFld = ((SwFldPortion*)pSecondRest)->Clone(
//STRIP001                                  ((SwFldPortion*)pSecondRest)->GetExp() );
//STRIP001                  pFld->SetFollow( sal_True );
//STRIP001                  aTmp.SetRest( pFld );
//STRIP001              }
//STRIP001              if( !rMulti.OnTop() && nFirstLen < nMultiLen )
//STRIP001                  bRet = sal_True;
//STRIP001          }
//STRIP001          else
//STRIP001              aTmp.SetRest( aInf.GetRest() );
//STRIP001          aInf.SetRest( NULL );
//STRIP001
//STRIP001             // in grid mode we temporarily have to disable the grid for the ruby line
//STRIP001             if ( bHasGrid && aTmp.IsRuby() && ! bRubyTop )
//STRIP001                 aTmp.SetSnapToGrid( sal_False );
//STRIP001
//STRIP001             BuildPortions( aTmp );
//STRIP001
//STRIP001             aTmp.SetSnapToGrid( bOldGridModeAllowed );
//STRIP001
//STRIP001             rMulti.CalcSize( *this, aInf );
//STRIP001             rMulti.GetRoot().SetRealHeight( rMulti.GetRoot().Height() );
//STRIP001          pCurr->SetRealHeight( pCurr->Height() );
//STRIP001          if( rMulti.IsRuby() )
//STRIP001          {
//STRIP001              pNextSecond = aTmp.GetRest();
//STRIP001              if( pNextFirst )
//STRIP001                  bRet = sal_True;
//STRIP001          }
//STRIP001          else
//STRIP001              pNextFirst = aTmp.GetRest();
//STRIP001          if( ( !aTmp.IsRuby() && nFirstLen + pCurr->GetLen() < nMultiLen )
//STRIP001              || aTmp.GetRest() )
//STRIP001                 // our guess for width of multiportion was too small,
//STRIP001                 // text did not fit into multiportion
//STRIP001              bRet = sal_True;
//STRIP001      }
//STRIP001         if( rMulti.IsRuby() )
//STRIP001             break;
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001             // our guess for multiportion width was too small,
//STRIP001             // we set min to act
//STRIP001          nMinWidth = nActWidth;
//STRIP001          nActWidth = ( 3 * nMaxWidth + nMinWidth + 3 ) / 4;
//STRIP001             if ( nActWidth == nMaxWidth && rInf.GetLineStart() == rInf.GetIdx() )
//STRIP001             // we have too less space, we must allow break cuts
//STRIP001             // ( the first multi flag is considered during TxtPortion::_Format() )
//STRIP001                 bFirstMulti = sal_False;
//STRIP001             if( nActWidth <= nMinWidth )
//STRIP001              break;
//STRIP001      }
//STRIP001      else
//STRIP001         {
//STRIP001             // For Solaris, this optimisation can causes trouble:
//STRIP001             // Setting this to the portion width ( = rMulti.Width() )
//STRIP001             // can make GetTextBreak inside SwTxtGuess::Guess return to small
//STRIP001             // values. Therefore we add some extra twips.
//STRIP001             if( nActWidth > nTmpX + rMulti.Width() + 6 )
//STRIP001                 nActWidth = nTmpX + rMulti.Width() + 6;
//STRIP001             nMaxWidth = nActWidth;
//STRIP001          nActWidth = ( 3 * nMaxWidth + nMinWidth + 3 ) / 4;
//STRIP001          if( nActWidth >= nMaxWidth )
//STRIP001              break;
//STRIP001             // we do not allow break cuts during formatting
//STRIP001             bFirstMulti = sal_True;
//STRIP001      }
//STRIP001      delete pNextFirst;
//STRIP001      pNextFirst = NULL;
//STRIP001  } while ( TRUE );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     pMulti = pOldMulti;
//STRIP001 #else
//STRIP001  pMulti = NULL;
//STRIP001 #endif
//STRIP001
//STRIP001  pCurr = pOldCurr;
//STRIP001  nStart = nOldStart;
//STRIP001      SetPropFont( 0 );
//STRIP001
//STRIP001  rMulti.SetLen( rMulti.GetRoot().GetLen() + ( rMulti.GetRoot().GetNext() ?
//STRIP001      rMulti.GetRoot().GetNext()->GetLen() : 0 ) );
//STRIP001
//STRIP001  if( rMulti.IsDouble() )
//STRIP001  {
//STRIP001      ((SwDoubleLinePortion&)rMulti).CalcBlanks( rInf );
//STRIP001      if( ((SwDoubleLinePortion&)rMulti).GetLineDiff() )
//STRIP001      {
//STRIP001          SwLineLayout* pLine = &rMulti.GetRoot();
//STRIP001          if( ((SwDoubleLinePortion&)rMulti).GetLineDiff() > 0 )
//STRIP001          {
//STRIP001              rInf.SetIdx( nStartIdx + pLine->GetLen() );
//STRIP001              pLine = pLine->GetNext();
//STRIP001          }
//STRIP001          if( pLine )
//STRIP001          {
//STRIP001              GetInfo().SetMulti( sal_True );
//STRIP001              CalcNewBlock( pLine, NULL, rMulti.Width() );
//STRIP001              GetInfo().SetMulti( sal_False );
//STRIP001          }
//STRIP001          rInf.SetIdx( nStartIdx );
//STRIP001      }
//STRIP001      if( ((SwDoubleLinePortion&)rMulti).GetBrackets() )
//STRIP001         {
//STRIP001             rMulti.Width( rMulti.Width() +
//STRIP001                     ((SwDoubleLinePortion&)rMulti).BracketWidth() );
//STRIP001             GetInfo().X( nOldX );
//STRIP001         }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rMulti.ActualizeTabulator();
//STRIP001      if( rMulti.IsRuby() )
//STRIP001      {
//STRIP001          ((SwRubyPortion&)rMulti).Adjust( rInf );
//STRIP001          ((SwRubyPortion&)rMulti).CalcRubyOffset();
//STRIP001      }
//STRIP001  }
//STRIP001  if( rMulti.HasRotation() )
//STRIP001  {
//STRIP001      SwTwips nH = rMulti.Width();
//STRIP001      SwTwips nAsc = rMulti.GetAscent() + ( nH - rMulti.Height() )/2;
//STRIP001      if( nAsc > nH )
//STRIP001          nAsc = nH;
//STRIP001      else if( nAsc < 0 )
//STRIP001          nAsc = 0;
//STRIP001      rMulti.Width( rMulti.Height() );
//STRIP001      rMulti.Height( KSHORT(nH) );
//STRIP001      rMulti.SetAscent( KSHORT(nAsc) );
//STRIP001         bRet = ( rInf.GetPos().X() + rMulti.Width() > rInf.Width() ) &&
//STRIP001                  nStartIdx != rInf.GetLineStart();
//STRIP001  }
//STRIP001 #ifdef BIDI
//STRIP001     else if ( rMulti.IsBidi() )
//STRIP001     {
//STRIP001         // Calculate number of blanks for justified alignment
//STRIP001         SwLinePortion* pPor = rMulti.GetRoot().GetFirstPortion();
//STRIP001         xub_StrLen nStart = rInf.GetIdx();
//STRIP001         xub_StrLen nNull = 0;
//STRIP001         for( xub_StrLen nBlanks = 0; pPor; pPor = pPor->GetPortion() )
//STRIP001         {
//STRIP001             if( pPor->InTxtGrp() )
//STRIP001                 nBlanks += ((SwTxtPortion*)pPor)->GetSpaceCnt( rInf, nNull );
//STRIP001             else if ( pPor->IsMultiPortion() &&
//STRIP001                      ((SwMultiPortion*)pPor)->IsBidi() )
//STRIP001                 nBlanks += ((SwBidiPortion*)pPor)->GetSpaceCnt();
//STRIP001
//STRIP001             rInf.SetIdx( rInf.GetIdx() + pPor->GetLen() );
//STRIP001         }
//STRIP001         rInf.SetIdx( nStart );
//STRIP001         ((SwBidiPortion&)rMulti).SetSpaceCnt( nBlanks );
//STRIP001
//STRIP001         bRet = rMulti.GetLen() < nMultiLen || pNextFirst;
//STRIP001     }
//STRIP001 #endif
//STRIP001
//STRIP001
//STRIP001  // line break has to be performed!
//STRIP001     if( bRet )
//STRIP001     {
//STRIP001         ASSERT( !pNextFirst || pNextFirst->InFldGrp(),
//STRIP001             "BuildMultiPortion: Surprising restportion, field expected" );
//STRIP001         SwMultiPortion *pTmp;
//STRIP001         if( rMulti.IsDouble() )
//STRIP001             pTmp = new SwDoubleLinePortion( ((SwDoubleLinePortion&)rMulti),
//STRIP001                                             nMultiLen + rInf.GetIdx() );
//STRIP001         else if( rMulti.IsRuby() )
//STRIP001         {
//STRIP001             ASSERT( !pNextSecond || pNextSecond->InFldGrp(),
//STRIP001                 "BuildMultiPortion: Surprising restportion, field expected" );
//STRIP001
//STRIP001             if ( rInf.GetIdx() == rInf.GetLineStart() )
//STRIP001             {
//STRIP001                 // the ruby portion has to be split in two portions
//STRIP001 #ifdef BIDI
//STRIP001                 pTmp = new SwRubyPortion( ((SwRubyPortion&)rMulti),
//STRIP001                                           nMultiLen + rInf.GetIdx() );
//STRIP001 #else
//STRIP001                 pTmp = new SwRubyPortion( nMultiLen + rInf.GetIdx(),
//STRIP001                     ((SwRubyPortion&)rMulti).GetAdjustment(), !rMulti.OnTop(),
//STRIP001                     ((SwRubyPortion&)rMulti).GetRubyOffset() );
//STRIP001 #endif
//STRIP001
//STRIP001                 if( pNextSecond )
//STRIP001                 {
//STRIP001                     pTmp->GetRoot().SetNext( new SwLineLayout() );
//STRIP001                     pTmp->GetRoot().GetNext()->SetPortion( pNextSecond );
//STRIP001                 }
//STRIP001                 pTmp->SetFollowFld();
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // we try to keep our ruby portion together
//STRIP001                 lcl_TruncateMultiPortion( rMulti, rInf, nStartIdx );
//STRIP001                 pTmp = 0;
//STRIP001             }
//STRIP001         }
//STRIP001         else if( rMulti.HasRotation() )
//STRIP001         {
//STRIP001             // we try to keep our rotated portion together
//STRIP001             lcl_TruncateMultiPortion( rMulti, rInf, nStartIdx );
//STRIP001             pTmp = new SwRotatedPortion( nMultiLen + rInf.GetIdx(),
//STRIP001                                          rMulti.GetDirection() );
//STRIP001         }
//STRIP001 #ifdef BIDI
//STRIP001         // during a recursion of BuildMultiPortions we may not build
//STRIP001         // a new SwBidiPortion, this would cause a memory leak
//STRIP001         else if( rMulti.IsBidi() && ! pMulti )
//STRIP001      {
//STRIP001             if ( ! rMulti.GetLen() )
//STRIP001                 lcl_TruncateMultiPortion( rMulti, rInf, nStartIdx );
//STRIP001
//STRIP001             // If there is a HolePortion at the end of the bidi portion,
//STRIP001             // it has to be moved behind the bidi portion. Otherwise
//STRIP001             // the visual cursor travelling gets into trouble.
//STRIP001             SwLineLayout& aRoot = rMulti.GetRoot();
//STRIP001             SwLinePortion* pPor = aRoot.GetFirstPortion();
//STRIP001             while ( pPor )
//STRIP001             {
//STRIP001                 if ( pPor->GetPortion() && pPor->GetPortion()->IsHolePortion() )
//STRIP001                 {
//STRIP001                     SwLinePortion* pHolePor = pPor->GetPortion();
//STRIP001                     pPor->SetPortion( NULL );
//STRIP001                     aRoot.SetLen( aRoot.GetLen() - pHolePor->GetLen() );
//STRIP001                     rMulti.SetLen( rMulti.GetLen() - pHolePor->GetLen() );
//STRIP001                     rMulti.SetPortion( pHolePor );
//STRIP001                     break;
//STRIP001                 }
//STRIP001                 pPor = pPor->GetPortion();
//STRIP001             }
//STRIP001
//STRIP001             pTmp = new SwBidiPortion( nMultiLen + rInf.GetIdx(),
//STRIP001                                     ((SwBidiPortion&)rMulti).GetLevel() );
//STRIP001      }
//STRIP001 #endif
//STRIP001         else
//STRIP001             pTmp = NULL;
//STRIP001
//STRIP001         if ( ! rMulti.GetLen() && rInf.GetLast() )
//STRIP001         {
//STRIP001             SeekAndChgBefore( rInf );
//STRIP001             rInf.GetLast()->FormatEOL( rInf );
//STRIP001         }
//STRIP001
//STRIP001         if( pNextFirst && pTmp )
//STRIP001         {
//STRIP001             pTmp->SetFollowFld();
//STRIP001             pTmp->GetRoot().SetPortion( pNextFirst );
//STRIP001         }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         else
//STRIP001             // A follow field portion is still waiting. If nobody wants it,
//STRIP001             // we delete it.
//STRIP001             delete pNextFirst;
//STRIP001 #endif
//STRIP001
//STRIP001         rInf.SetRest( pTmp );
//STRIP001     }
//STRIP001
//STRIP001  rInf.SetTxt( *pOldTxt );
//STRIP001     rInf.SetPaintOfst( nOldPaintOfst );
//STRIP001     rInf.SetStop( aInf.IsStop() );
//STRIP001     rInf.SetNumDone( sal_True );
//STRIP001     rInf.SetFtnDone( sal_True );
//STRIP001  SeekAndChg( rInf );
//STRIP001  delete pFirstRest;
//STRIP001  delete pSecondRest;
//STRIP001  delete pFontSave;
//STRIP001  return bRet;
//STRIP001 }

/*-----------------08.11.00 09:29-------------------
 * SwTxtFormatter::MakeRestPortion(..)
 * When a fieldportion at the end of line breaks and needs a following
 * fieldportion in the next line, then the "restportion" of the formatinfo
 * has to be set. Normally this happens during the formatting of the first
 * part of the fieldportion.
 * But sometimes the formatting starts at the line with the following part,
 * exspecally when the following part is on the next page.
 * In this case the MakeRestPortion-function has to create the following part.
 * The first parameter is the line that contains possibly a first part
 * of a field. When the function finds such field part, it creates the right
 * restportion. This may be a multiportion, e.g. if the field is surrounded by
 * a doubleline- or ruby-portion.
 * The second parameter is the start index of the line.
 * --------------------------------------------------*/

/*N*/ SwLinePortion* SwTxtFormatter::MakeRestPortion( const SwLineLayout* pLine,
/*N*/   xub_StrLen nPos )
/*N*/ {
/*N*/   if( !nPos )
/*N*/       return NULL;
/*N*/   xub_StrLen nMultiPos = nPos - pLine->GetLen();
/*N*/   const SwMultiPortion *pTmpMulti = NULL;
/*N*/   const SwMultiPortion *pMulti = NULL;
/*N*/   const SwLinePortion* pPor = pLine->GetFirstPortion();
/*N*/   SwFldPortion *pFld = NULL;
/*N*/   while( pPor )
/*N*/   {
/*N*/       if( pPor->GetLen() )
/*N*/       {
/*N*/           if( !pMulti )
/*N*/           {
/*N*/               nMultiPos += pPor->GetLen();
/*N*/               pTmpMulti = NULL;
/*N*/           }
/*N*/       }
/*N*/       if( pPor->InFldGrp() )
/*N*/       {
/*?*/           if( !pMulti )
/*?*/               pTmpMulti = NULL;
/*?*/           pFld = (SwFldPortion*)pPor;
/*N*/       }
/*N*/       else if( pPor->IsMultiPortion() )
/*N*/       {
/*?*/ #ifdef BIDI
/*?*/             ASSERT( !pMulti || pMulti->IsBidi(),
/*?*/                     "Nested multiportions are forbidden." );
/*?*/ #else
/*?*/           ASSERT( !pMulti, "Nested multiportions are forbidden." );
/*?*/ #endif
/*?*/
/*?*/           pFld = NULL;
/*?*/           pTmpMulti = (SwMultiPortion*)pPor;
/*N*/       }
/*N*/       pPor = pPor->GetPortion();
/*N*/       // If the last portion is a multi-portion, we enter it
/*N*/       // and look for a field portion inside.
/*N*/       // If we are already in a multiportion, we could change to the
/*N*/       // next line
/*N*/       if( !pPor && pTmpMulti )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*N*/       {
//STRIP001 /*?*/            if( pMulti )
//STRIP001 /*?*/            {   // We're already inside the multiportion, let's take the second
//STRIP001 /*?*/                // line, if we are in a double line portion
//STRIP001 /*?*/                if( !pMulti->IsRuby() )
//STRIP001 /*?*/                    pPor = pMulti->GetRoot().GetNext();
//STRIP001 /*?*/                pTmpMulti = NULL;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {   // Now we enter a multiportion, in a ruby portion we take the
//STRIP001 /*?*/                // main line, not the phonetic line, in a doublelineportion we
//STRIP001 /*?*/                // starts with the first line.
//STRIP001 /*?*/                pMulti = pTmpMulti;
//STRIP001 /*?*/                nMultiPos -= pMulti->GetLen();
//STRIP001 /*?*/                if( pMulti->IsRuby() && pMulti->OnTop() )
//STRIP001 /*?*/                    pPor = pMulti->GetRoot().GetNext();
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    pPor = pMulti->GetRoot().GetFirstPortion();
//STRIP001 /*?*/            }
//STRIP001 /*N*/        }
/*N*/   }
/*N*/   if( pFld && !pFld->HasFollow() )
/*N*/       pFld = NULL;
/*N*/
/*N*/   SwLinePortion *pRest = NULL;
/*N*/   if( pFld )
/*N*/   {
/*?*/       const SwTxtAttr *pHint = GetAttr( nPos - 1 );
/*?*/       if( pHint && pHint->Which() == RES_TXTATR_FIELD )
/*?*/       {
/*?*/           pRest = NewFldPortion( GetInfo(), pHint );
/*?*/           if( pRest->InFldGrp() )
/*?*/               ((SwFldPortion*)pRest)->TakeNextOffset( pFld );
/*?*/           else
/*?*/           {
/*?*/               delete pRest;
/*?*/               pRest = NULL;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   if( !pMulti )
/*N*/       return pRest;
/*N*/ {DBG_BF_ASSERT(0, "STRIP");}
//STRIP001 /*?*/    nPos = nMultiPos + pMulti->GetLen();
//STRIP001 /*?*/ #ifdef BIDI
//STRIP001 /*?*/     SwMultiCreator* pCreate = GetInfo().GetMultiCreator( nMultiPos, 0 );
//STRIP001 /*?*/ #else
//STRIP001 /*?*/    SwMultiCreator* pCreate = GetInfo().GetMultiCreator( nMultiPos );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/     if ( !pCreate )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         ASSERT( !pMulti->GetLen(), "Multiportion without attribut?" );
//STRIP001 /*?*/         if ( nMultiPos )
//STRIP001 /*?*/             --nMultiPos;
//STRIP001 /*?*/ #ifdef BIDI
//STRIP001 /*?*/         pCreate = GetInfo().GetMultiCreator( --nMultiPos, 0 );
//STRIP001 /*?*/ #else
//STRIP001 /*?*/         pCreate = GetInfo().GetMultiCreator( --nMultiPos );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/    if( pRest || nMultiPos > nPos || ( pMulti->IsRuby() &&
//STRIP001 /*?*/        ((SwRubyPortion*)pMulti)->GetRubyOffset() < STRING_LEN ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        SwMultiPortion* pTmp;
//STRIP001 /*?*/        if( pMulti->IsDouble() )
//STRIP001 /*?*/            pTmp = new SwDoubleLinePortion( *pCreate, nMultiPos );
//STRIP001 /*?*/ #ifdef BIDI
//STRIP001 /*?*/         else if( pMulti->IsBidi() )
//STRIP001 /*?*/             pTmp = new SwBidiPortion( nMultiPos, pCreate->nLevel );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/        else if( pMulti->IsRuby() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             sal_Bool bRubyTop;
//STRIP001 /*?*/             sal_Bool* pRubyPos = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( GetInfo().SnapToGrid() )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 GETGRID( pFrm->FindPageFrm() )
//STRIP001 /*?*/                 if ( pGrid )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     bRubyTop = ! pGrid->GetRubyTextBelow();
//STRIP001 /*?*/                     pRubyPos = &bRubyTop;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/             pTmp = new SwRubyPortion( *pCreate, *GetInfo().GetFont(),
//STRIP001 /*?*/                     *GetInfo().GetDoc(), nMultiPos,
//STRIP001 /*?*/                     ((SwRubyPortion*)pMulti)->GetRubyOffset(), pRubyPos );
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else if( pMulti->HasRotation() )
//STRIP001 /*?*/            pTmp = new SwRotatedPortion( nMultiPos, pMulti->GetDirection() );
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            delete pCreate;
//STRIP001 /*?*/            return pRest;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        delete pCreate;
//STRIP001 /*?*/        pTmp->SetFollowFld();
//STRIP001 /*?*/        if( pRest )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwLineLayout *pLay = &pTmp->GetRoot();
//STRIP001 /*?*/            if( pTmp->IsRuby() && pTmp->OnTop() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pLay->SetNext( new SwLineLayout() );
//STRIP001 /*?*/                pLay = pLay->GetNext();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            pLay->SetPortion( pRest );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        return pTmp;
//STRIP001 /*?*/    }
/*?*/   return pRest;
/*N*/ }



/*-----------------23.10.00 10:47-------------------
 * SwTxtCursorSave notes the start and current line of a SwTxtCursor,
 * sets them to the values for GetCrsrOfst inside a multiportion
 * and restores them in the destructor.
 * --------------------------------------------------*/

//STRIP001 #ifdef BIDI
//STRIP001 SwTxtCursorSave::SwTxtCursorSave( SwTxtCursor* pTxtCursor,
//STRIP001     SwMultiPortion* pMulti, SwTwips nY, USHORT& nX, xub_StrLen nCurrStart,
//STRIP001     short nSpaceAdd )
//STRIP001 #else
//STRIP001 SwTxtCursorSave::SwTxtCursorSave( SwTxtCursor* pTxtCursor,
//STRIP001  SwMultiPortion* pMulti, SwTwips nY, xub_StrLen nCurrStart, short nSpaceAdd )
//STRIP001 #endif
//STRIP001 {
//STRIP001  pTxtCrsr = pTxtCursor;
//STRIP001  nStart = pTxtCursor->nStart;
//STRIP001  pTxtCursor->nStart = nCurrStart;
//STRIP001  pCurr = pTxtCursor->pCurr;
//STRIP001  pTxtCursor->pCurr = &pMulti->GetRoot();
//STRIP001     while( pTxtCursor->Y() + pTxtCursor->GetLineHeight() < nY &&
//STRIP001      pTxtCursor->Next() )
//STRIP001      ; // nothing
//STRIP001  nWidth = pTxtCursor->pCurr->Width();
//STRIP001  nOldProp = pTxtCursor->GetPropFont();
//STRIP001 #ifdef BIDI
//STRIP001     if ( pMulti->IsDouble() || pMulti->IsBidi() )
//STRIP001     {
//STRIP001      bSpaceChg = pMulti->ChgSpaceAdd( pTxtCursor->pCurr, nSpaceAdd );
//STRIP001
//STRIP001         USHORT nSpaceCnt;
//STRIP001         if ( pMulti->IsDouble() )
//STRIP001         {
//STRIP001             pTxtCursor->SetPropFont( 50 );
//STRIP001             nSpaceCnt = ((SwDoubleLinePortion*)pMulti)->GetSpaceCnt();
//STRIP001         }
//STRIP001         else
//STRIP001             nSpaceCnt = ((SwBidiPortion*)pMulti)->GetSpaceCnt();
//STRIP001
//STRIP001      if( nSpaceAdd > 0 && !pMulti->HasTabulator() )
//STRIP001             pTxtCursor->pCurr->Width( nWidth + nSpaceAdd * nSpaceCnt );
//STRIP001
//STRIP001         // For a BidiPortion we have to calculate the offset from the
//STRIP001         // end of the portion
//STRIP001         if ( nX && pMulti->IsBidi() )
//STRIP001             nX = pTxtCursor->pCurr->Width() - nX;
//STRIP001     }
//STRIP001 #else
//STRIP001  if( pMulti->IsDouble() )
//STRIP001  {
//STRIP001      pTxtCursor->SetPropFont( 50 );
//STRIP001      bSpaceChg = pMulti->ChgSpaceAdd( pTxtCursor->pCurr, nSpaceAdd );
//STRIP001      if( nSpaceAdd > 0 && !pMulti->HasTabulator() )
//STRIP001          pTxtCursor->pCurr->Width( nWidth + nSpaceAdd *
//STRIP001          ((SwDoubleLinePortion*)pMulti)->GetSpaceCnt() );
//STRIP001  }
//STRIP001 #endif
//STRIP001  else
//STRIP001      bSpaceChg = sal_False;
//STRIP001 }
//STRIP001
//STRIP001 SwTxtCursorSave::~SwTxtCursorSave()
//STRIP001 {
//STRIP001  if( bSpaceChg )
//STRIP001      SwDoubleLinePortion::ResetSpaceAdd( pTxtCrsr->pCurr );
//STRIP001  pTxtCrsr->pCurr->Width( KSHORT(nWidth) );
//STRIP001  pTxtCrsr->pCurr = pCurr;
//STRIP001  pTxtCrsr->nStart = nStart;
//STRIP001  pTxtCrsr->SetPropFont( nOldProp );
//STRIP001 }
//STRIP001
}
