/*************************************************************************
 *
 *  $RCSfile: sw_txtdrop.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:35:37 $
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

#ifndef _SV_METRIC_HXX //autogen
#include <vcl/metric.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>   // Format()
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>  // SwViewOption
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif
#ifndef _PORDROP_HXX
#include <pordrop.hxx>
#endif
#ifndef _ITRFORM2_HXX
#include <itrform2.hxx>
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>
#endif
#ifndef _TXTPAINT_HXX
#include <txtpaint.hxx> // SwSaveClip
#endif
#ifndef _TXTFLY_HXX
#include <txtfly.hxx>   // Format()
#endif
#ifndef _BLINK_HXX
#include <blink.hxx>    // pBlink
#endif
#ifndef _TXATBASE_HXX
#include <txatbase.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HPP_
#include <com/sun/star/i18n/WordType.hpp>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif

using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star;

/*************************************************************************
 *                lcl_IsDropFlyInter
 *
 *  Calculates if a drop caps portion intersects with a fly
 *  The width and height of the drop caps portion are passed as arguments,
 *  the position is calculated from the values in rInf
 *************************************************************************/

/*N*/ sal_Bool lcl_IsDropFlyInter( const SwTxtFormatInfo &rInf,
/*N*/                              USHORT nWidth, USHORT nHeight )
/*N*/ {
/*N*/     const SwTxtFly *pTxtFly = rInf.GetTxtFly();
/*N*/     if( pTxtFly && pTxtFly->IsOn() )
/*N*/     {
/*N*/         SwRect aRect( rInf.GetTxtFrm()->Frm().Pos(), Size( nWidth, nHeight) );
/*N*/         aRect.Pos() += rInf.GetTxtFrm()->Prt().Pos();
/*N*/         aRect.Pos().X() += rInf.X();
/*N*/         aRect.Pos().Y() = rInf.Y();
/*N*/         aRect = pTxtFly->GetFrm( aRect );
/*N*/         return aRect.HasArea();
/*N*/     }
/*N*/
/*N*/     return sal_False;
/*N*/ }

/*************************************************************************
 *                class SwDropSave
 *************************************************************************/

class SwDropSave
{
    SwTxtPaintInfo* pInf;
    xub_StrLen nIdx;
    xub_StrLen nLen;
    long nX;
    long nY;

public:
    SwDropSave( const SwTxtPaintInfo &rInf );
    ~SwDropSave();
};

/*N*/ SwDropSave::SwDropSave( const SwTxtPaintInfo &rInf ) :
/*N*/         pInf( ((SwTxtPaintInfo*)&rInf) ), nIdx( rInf.GetIdx() ),
/*N*/         nLen( rInf.GetLen() ), nX( rInf.X() ), nY( rInf.Y() )
/*N*/ {
/*N*/ }

/*N*/ SwDropSave::~SwDropSave()
/*N*/ {
/*N*/     pInf->SetIdx( nIdx );
/*N*/     pInf->SetLen( nLen );
/*N*/     pInf->X( nX );
/*N*/     pInf->Y( nY );
/*N*/ }

/*************************************************************************
 *                SwDropPortionPart DTor
 *************************************************************************/

/*N*/ SwDropPortionPart::~SwDropPortionPart()
/*N*/ {
/*N*/     if ( pFollow )
/*N*/         delete pFollow;
/*N*/     delete pFnt;
/*N*/ }

/*************************************************************************
 *                SwDropPortion CTor, DTor
 *************************************************************************/

/*N*/ SwDropPortion::SwDropPortion( const MSHORT nLineCnt,
/*N*/                               const KSHORT nDropHeight,
/*N*/                               const KSHORT nDropDescent,
/*N*/                               const KSHORT nDistance )
/*N*/   : pPart( 0 ),
/*N*/     nLines( nLineCnt ),
/*N*/   nDropHeight(nDropHeight),
/*N*/   nDropDescent(nDropDescent),
/*N*/   nDistance(nDistance),
/*N*/   nX(0),
/*N*/   nFix(0)
/*N*/ {
/*N*/     SetWhichPor( POR_DROP );
/*N*/ }

/*N*/ SwDropPortion::~SwDropPortion()
/*N*/ {
/*N*/     delete pPart;
/*N*/   if( pBlink )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/      pBlink->Delete( this );
/*N*/ }

/*N*/ sal_Bool SwTxtSizeInfo::_HasHint( const SwTxtNode* pTxtNode, xub_StrLen nPos )
/*N*/ {
/*N*/   const SwpHints *pHints = pTxtNode->GetpSwpHints();
/*N*/   if( !pHints )
/*N*/       return sal_False;
/*N*/   for( MSHORT i = 0; i < pHints->Count(); ++i )
/*N*/   {
/*N*/       const SwTxtAttr *pPos = (*pHints)[i];
/*N*/       xub_StrLen nStart = *pPos->GetStart();
/*N*/       if( nPos < nStart )
/*N*/           return sal_False;
/*N*/       if( nPos == nStart && !pPos->GetEnd() )
/*N*/           return sal_True;
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *                    SwTxtNode::GetDropLen()
 *
 * nWishLen = 0 indicates that we want a whole word
 *************************************************************************/

/*N*/ MSHORT SwTxtNode::GetDropLen( MSHORT nWishLen ) const
/*N*/ {
/*N*/     xub_StrLen nEnd = GetTxt().Len();
/*N*/     if( nWishLen && nWishLen < nEnd )
/*N*/         nEnd = nWishLen;
/*N*/
/*N*/     if ( ! nWishLen && pBreakIt->xBreak.is() )
/*N*/     {
/*N*/         // find first word
/*?*/         const SwAttrSet& rAttrSet = GetSwAttrSet();
/*?*/         const USHORT nTxtScript = pBreakIt->GetRealScriptOfText( GetTxt(), 0 );
/*?*/
/*?*/         LanguageType eLanguage;
/*?*/
/*?*/         switch ( nTxtScript )
/*?*/         {
/*?*/         case i18n::ScriptType::ASIAN :
/*?*/             eLanguage = rAttrSet.GetCJKLanguage().GetLanguage();
/*?*/             break;
/*?*/         case i18n::ScriptType::COMPLEX :
/*?*/             eLanguage = rAttrSet.GetCTLLanguage().GetLanguage();
/*?*/             break;
/*?*/         default :
/*?*/             eLanguage = rAttrSet.GetLanguage().GetLanguage();
/*?*/             break;
/*?*/         }
/*?*/
/*?*/         Boundary aBound =
/*?*/             pBreakIt->xBreak->getWordBoundary( GetTxt(), 0,
/*?*/             pBreakIt->GetLocale( eLanguage ), WordType::DICTIONARY_WORD, sal_True );
/*?*/
/*?*/         nEnd = (xub_StrLen)aBound.endPos;
/*N*/     }
/*N*/
/*N*/     xub_StrLen i = 0;
/*N*/     for( ; i < nEnd; ++i )
/*N*/     {
/*N*/         xub_Unicode cChar = GetTxt().GetChar( i );
/*N*/         if( CH_TAB == cChar || CH_BREAK == cChar ||
/*N*/             (( CH_TXTATR_BREAKWORD == cChar || CH_TXTATR_INWORD == cChar )
/*N*/                 && SwTxtSizeInfo::_HasHint( this, i ) ) )
/*N*/             break;
/*N*/     }
/*N*/     return i;
/*N*/ }

/*************************************************************************
 *                    SwDropPortion::PaintTxt()
 *************************************************************************/

// Die Breite manipulieren, sonst werden die Buchstaben gestretcht

//STRIP001 void SwDropPortion::PaintTxt( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001     if ( rInf.OnWin() &&
//STRIP001         !rInf.GetOpt().IsPagePreview() && !rInf.GetOpt().IsReadonly() && SwViewOption::IsFieldShadings()    )
//STRIP001         rInf.DrawBackground( *this );
//STRIP001
//STRIP001     ASSERT( nDropHeight && pPart && nLines != 1, "Drop Portion painted twice" );
//STRIP001
//STRIP001     const SwDropPortionPart* pCurrPart = GetPart();
//STRIP001     const xub_StrLen nOldLen = GetLen();
//STRIP001
//STRIP001     const SwTwips nBasePosY  = rInf.Y();
//STRIP001     ((SwTxtPaintInfo&)rInf).Y( nBasePosY + nY );
//STRIP001     SwDropSave aSave( rInf );
//STRIP001              // for text inside drop portions we let vcl handle the text directions
//STRIP001     SwLayoutModeModifier aLayoutModeModifier( *rInf.GetOut() );
//STRIP001     aLayoutModeModifier.SetAuto();
//STRIP001
//STRIP001     while ( pCurrPart )
//STRIP001     {
//STRIP001         ((SwDropPortion*)this)->SetLen( pCurrPart->GetLen() );
//STRIP001         ((SwTxtPaintInfo&)rInf).SetLen( pCurrPart->GetLen() );
//STRIP001         SwFontSave aSave( rInf, &pCurrPart->GetFont() );
//STRIP001
//STRIP001         SwTxtPortion::Paint( rInf );
//STRIP001
//STRIP001         ((SwTxtPaintInfo&)rInf).SetIdx( rInf.GetIdx() + pCurrPart->GetLen() );
//STRIP001         ((SwTxtPaintInfo&)rInf).X( rInf.X() + pCurrPart->GetWidth() );
//STRIP001         pCurrPart = pCurrPart->GetFollow();
//STRIP001     }
//STRIP001
//STRIP001     ((SwTxtPaintInfo&)rInf).Y( nBasePosY );
//STRIP001     ((SwDropPortion*)this)->SetLen( nOldLen );
//STRIP001 }

/*************************************************************************
 *                   SwDropPortion::Paint()
 *************************************************************************/

//STRIP001 void SwDropPortion::PaintDrop( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001     // ganz normale Ausgabe wird während des normalen Paints erledigt
//STRIP001     if( ! nDropHeight || ! pPart || nLines == 1 )
//STRIP001      return;
//STRIP001
//STRIP001  // Luegenwerte einstellen!
//STRIP001     const KSHORT nOldHeight = Height();
//STRIP001     const KSHORT nOldWidth  = Width();
//STRIP001     const KSHORT nOldAscent = GetAscent();
//STRIP001     const SwTwips nOldPosY  = rInf.Y();
//STRIP001     const KSHORT nOldPosX   = (KSHORT)rInf.X();
//STRIP001  const SwParaPortion *pPara = rInf.GetParaPortion();
//STRIP001  const Point aOutPos( nOldPosX + nX, nOldPosY - pPara->GetAscent()
//STRIP001                       - pPara->GetRealHeight() + pPara->Height() );
//STRIP001  // Retusche nachholen.
//STRIP001
//STRIP001     // Set baseline
//STRIP001     ((SwTxtPaintInfo&)rInf).Y( aOutPos.Y() + nDropHeight );
//STRIP001
//STRIP001     // for background
//STRIP001     ((SwDropPortion*)this)->Height( nDropHeight + nDropDescent );
//STRIP001     ((SwDropPortion*)this)->Width( Width() - nX );
//STRIP001     ((SwDropPortion*)this)->SetAscent( nDropHeight );
//STRIP001
//STRIP001  // Clipregion auf uns einstellen!
//STRIP001  // Und zwar immer, und nie mit dem bestehenden ClipRect
//STRIP001  // verrechnen, weil dies auf die Zeile eingestellt sein koennte.
//STRIP001
//STRIP001  SwRect aClipRect;
//STRIP001  if ( rInf.OnWin() )
//STRIP001  {
//STRIP001      aClipRect = SwRect( aOutPos, SvLSize() );
//STRIP001      aClipRect.Intersection( rInf.GetPaintRect() );
//STRIP001  }
//STRIP001  SwSaveClip aClip( (OutputDevice*)rInf.GetOut() );
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001     aClip.ChgClip( aClipRect, rInf.GetTxtFrm() );
//STRIP001 #else
//STRIP001  aClip.ChgClip( aClipRect );
//STRIP001 #endif
//STRIP001     // Das machen, was man sonst nur macht ...
//STRIP001     PaintTxt( rInf );
//STRIP001
//STRIP001     // Alte Werte sichern
//STRIP001     ((SwDropPortion*)this)->Height( nOldHeight );
//STRIP001     ((SwDropPortion*)this)->Width( nOldWidth );
//STRIP001     ((SwDropPortion*)this)->SetAscent( nOldAscent );
//STRIP001     ((SwTxtPaintInfo&)rInf).Y( nOldPosY );
//STRIP001 }

/*************************************************************************
 *              virtual SwDropPortion::Paint()
 *************************************************************************/

//STRIP001 void SwDropPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  // ganz normale Ausgabe wird hier erledigt.
//STRIP001     if( ! nDropHeight || ! pPart || 1 == nLines )
//STRIP001     {
//STRIP001         if ( rInf.OnWin() &&
//STRIP001             !rInf.GetOpt().IsPagePreview() && !rInf.GetOpt().IsReadonly() && SwViewOption::IsFieldShadings()       )
//STRIP001             rInf.DrawBackground( *this );
//STRIP001
//STRIP001      // make sure that font is not rotated
//STRIP001      SwFont* pTmpFont = 0;
//STRIP001         if ( rInf.GetFont()->GetOrientation( rInf.GetTxtFrm()->IsVertical() ) )
//STRIP001      {
//STRIP001          pTmpFont = new SwFont( *rInf.GetFont() );
//STRIP001          pTmpFont->SetVertical( 0, rInf.GetTxtFrm()->IsVertical() );
//STRIP001      }
//STRIP001
//STRIP001      SwFontSave aSave( rInf, pTmpFont );
//STRIP001         // for text inside drop portions we let vcl handle the text directions
//STRIP001         SwLayoutModeModifier aLayoutModeModifier( *rInf.GetOut() );
//STRIP001         aLayoutModeModifier.SetAuto();
//STRIP001
//STRIP001      SwTxtPortion::Paint( rInf );
//STRIP001         delete pTmpFont;
//STRIP001     }
//STRIP001 }

/*************************************************************************
 *                virtual Format()
 *************************************************************************/


/*N*/ sal_Bool SwDropPortion::FormatTxt( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   const xub_StrLen nOldLen = GetLen();
/*N*/   const xub_StrLen nOldInfLen = rInf.GetLen();
/*N*/   const sal_Bool bFull = SwTxtPortion::Format( rInf );
/*N*/   if( bFull )
/*N*/   {
/*N*/       // sieht zwar Scheisse aus, aber was soll man schon machen?
/*?*/       rInf.SetUnderFlow( 0 );
/*?*/       Truncate();
/*?*/       SetLen( nOldLen );
/*?*/       rInf.SetLen( nOldInfLen );
/*N*/   }
/*N*/   return bFull;
/*N*/ }

/*************************************************************************
 *                virtual GetTxtSize()
 *************************************************************************/


//STRIP001 SwPosSize SwDropPortion::GetTxtSize( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001     USHORT nX = 0;
//STRIP001     xub_StrLen nIdx = 0;
//STRIP001
//STRIP001     const SwDropPortionPart* pCurrPart = GetPart();
//STRIP001
//STRIP001     // skip parts
//STRIP001     while ( pCurrPart && nIdx + pCurrPart->GetLen() < rInf.GetLen() )
//STRIP001     {
//STRIP001         nX += pCurrPart->GetWidth();
//STRIP001         nIdx += pCurrPart->GetLen();
//STRIP001         pCurrPart = pCurrPart->GetFollow();
//STRIP001     }
//STRIP001
//STRIP001     xub_StrLen nOldIdx = rInf.GetIdx();
//STRIP001     xub_StrLen nOldLen = rInf.GetLen();
//STRIP001
//STRIP001     ((SwTxtSizeInfo&)rInf).SetIdx( nIdx );
//STRIP001     ((SwTxtSizeInfo&)rInf).SetLen( rInf.GetLen() - nIdx );
//STRIP001
//STRIP001     // robust
//STRIP001     SwFontSave aSave( rInf, pCurrPart ? &pCurrPart->GetFont() : 0 );
//STRIP001     SwPosSize aPosSize( SwTxtPortion::GetTxtSize( rInf ) );
//STRIP001     aPosSize.Width( aPosSize.Width() + nX );
//STRIP001
//STRIP001     ((SwTxtSizeInfo&)rInf).SetIdx( nOldIdx );
//STRIP001     ((SwTxtSizeInfo&)rInf).SetLen( nOldLen );
//STRIP001
//STRIP001     return aPosSize;
//STRIP001 }

/*************************************************************************
 *                virtual GetCrsrOfst()
 *************************************************************************/

//STRIP001 xub_StrLen SwDropPortion::GetCrsrOfst( const KSHORT nOfst ) const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
 *                SwTxtFormatter::CalcDropHeight()
 *************************************************************************/

/*N*/ void SwTxtFormatter::CalcDropHeight( const MSHORT nLines )
/*N*/  {
/*N*/   const SwLinePortion *const pOldCurr = GetCurr();
/*N*/   KSHORT nDropHght = 0;
/*N*/   KSHORT nAscent = 0;
/*N*/   KSHORT nHeight = 0;
/*N*/   KSHORT nDropLns = 0;
/*N*/   sal_Bool bRegisterOld = IsRegisterOn();
/*N*/   bRegisterOn = sal_False;
/*N*/
/*N*/   Top();
/*N*/
/*N*/   while( GetCurr()->IsDummy() )
/*N*/   {
/*N*/       if ( !Next() )
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   // Wenn wir nur eine Zeile haben returnen wir 0
/*N*/   if( GetNext() || GetDropLines() == 1 )
/*N*/   {
/*N*/       for( ; nDropLns < nLines; nDropLns++ )
/*N*/       {
/*N*/           if ( GetCurr()->IsDummy() )
/*N*/               break;
/*N*/           else
/*N*/           {
/*N*/               CalcAscentAndHeight( nAscent, nHeight );
/*N*/               nDropHght += nHeight;
/*N*/               bRegisterOn = bRegisterOld;
/*N*/           }
/*N*/           if ( !Next() )
/*N*/           {
/*N*/               nDropLns++; // Fix: 11356
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // In der letzten Zeile plumpsen wir auf den Zeilenascent!
/*N*/       nDropHght -= nHeight;
/*N*/       nDropHght += nAscent;
/*N*/       Top();
/*N*/   }
/*N*/   bRegisterOn = bRegisterOld;
/*N*/   SetDropDescent( nHeight - nAscent );
/*N*/   SetDropHeight( nDropHght );
/*N*/   SetDropLines( nDropLns );
/*N*/   // Alte Stelle wiederfinden!
/*N*/   while( pOldCurr != GetCurr() )
/*N*/   {
/*N*/       if( !Next() )
/*N*/       {
/*N*/           ASSERT( !this, "SwTxtFormatter::_CalcDropHeight: left Toulouse" );
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/  }

/*************************************************************************
 *                SwTxtFormatter::GuessDropHeight()
 *
 *  Wir schaetzen mal, dass die Fonthoehe sich nicht aendert und dass
 *  erst mindestens soviele Zeilen gibt, wie die DropCap-Einstellung angibt.
 *
 *************************************************************************/



/*N*/ void SwTxtFormatter::GuessDropHeight( const MSHORT nLines )
/*N*/ {
/*N*/   ASSERT( nLines, "GuessDropHeight: Give me more Lines!" );
/*N*/   KSHORT nAscent = 0;
/*N*/   KSHORT nHeight = 0;
/*N*/   SetDropLines( nLines );
/*N*/   if ( GetDropLines() > 1 )
/*N*/   {
/*N*/       CalcRealHeight();
/*N*/       CalcAscentAndHeight( nAscent, nHeight );
/*N*/   }
/*N*/   SetDropDescent( nHeight - nAscent );
/*N*/   SetDropHeight( nHeight * nLines - GetDropDescent() );
/*N*/ }

/*************************************************************************
 *                SwTxtFormatter::NewDropPortion
 *************************************************************************/

/*N*/ SwDropPortion *SwTxtFormatter::NewDropPortion( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   if( !pDropFmt )
/*N*/       return 0;
/*N*/
/*N*/   xub_StrLen nPorLen = pDropFmt->GetWholeWord() ? 0 : pDropFmt->GetChars();
/*N*/     nPorLen = pFrm->GetTxtNode()->GetDropLen( nPorLen );
/*N*/   if( !nPorLen )
/*N*/   {
/*?*/       ((SwTxtFormatter*)this)->ClearDropFmt();
/*?*/       return 0;
/*N*/   }
/*N*/
/*N*/   SwDropPortion *pDropPor = 0;
/*N*/
/*N*/   // erste oder zweite Runde?
/*N*/   if ( !( GetDropHeight() || IsOnceMore() ) )
/*N*/   {
/*N*/       if ( GetNext() )
/*?*/             CalcDropHeight( pDropFmt->GetLines() );
/*N*/       else
/*N*/             GuessDropHeight( pDropFmt->GetLines() );
/*N*/   }
/*N*/
/*N*/     // the DropPortion
/*N*/     if( GetDropHeight() )
/*?*/         pDropPor = new SwDropPortion( GetDropLines(), GetDropHeight(),
/*N*/                                       GetDropDescent(), pDropFmt->GetDistance() );
/*N*/   else
/*N*/         pDropPor = new SwDropPortion( 0,0,0,pDropFmt->GetDistance() );
/*N*/
/*N*/     pDropPor->SetLen( nPorLen );
/*N*/
/*N*/     // If it was not possible to create a proper drop cap portion
/*N*/     // due to avoiding endless loops. We return a drop cap portion
/*N*/     // with an empty SwDropCapPart. For these portions the current
/*N*/     // font is used.
/*N*/     if ( GetDropLines() < 2 )
/*N*/     {
/*?*/         ((SwTxtFormatter*)this)->SetPaintDrop( sal_True );
/*?*/         return pDropPor;
/*N*/     }
/*N*/
/*N*/     // build DropPortionParts:
/*N*/     ASSERT( ! rInf.GetIdx(), "Drop Portion not at 0 position!" );
/*N*/     xub_StrLen nIdx = rInf.GetIdx();
/*N*/     xub_StrLen nNextChg = 0;
/*N*/     const SwCharFmt* pFmt = pDropFmt->GetCharFmt();
/*N*/     SwDropPortionPart* pCurrPart = 0;
/*N*/
/*N*/     while ( nNextChg  < nPorLen )
/*N*/     {
/*N*/         // check for attribute changes and if the portion has to split:
/*N*/         Seek( nNextChg );
/*N*/
/*N*/         // the font is deleted in the destructor of the drop portion part
/*N*/         SwFont* pTmpFnt = new SwFont( *rInf.GetFont() );
/*N*/         if ( pFmt )
/*N*/         {
/*N*/             const SwAttrSet& rSet = pFmt->GetAttrSet();
/*N*/             pTmpFnt->SetDiffFnt( &rSet, rInf.GetDoc() );
/*N*/         }
/*N*/
/*N*/         // we do not allow a vertical font for the drop portion
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/         pTmpFnt->SetVertical( 0, rInf.GetTxtFrm()->IsVertical() );
/*N*/ #else
/*N*/         pTmpFnt->SetVertical( 0 );
/*N*/ #endif
/*N*/
/*N*/         // find next attribute change / script change
/*N*/         const xub_StrLen nIdx = nNextChg;
/*N*/         xub_StrLen nNextAttr = Min( GetNextAttr(), rInf.GetTxt().Len() );
/*N*/         nNextChg = pScriptInfo->NextScriptChg( nIdx );
/*N*/         if( nNextChg > nNextAttr )
/*N*/             nNextChg = nNextAttr;
/*N*/         if ( nNextChg > nPorLen )
/*N*/             nNextChg = nPorLen;
/*N*/
/*N*/         SwDropPortionPart* pPart =
/*N*/                 new SwDropPortionPart( *pTmpFnt, nNextChg - nIdx );
/*N*/
/*N*/         if ( ! pCurrPart )
/*N*/             pDropPor->SetPart( pPart );
/*N*/         else
/*?*/             pCurrPart->SetFollow( pPart );
/*N*/
/*N*/         pCurrPart = pPart;
/*N*/     }
/*N*/
/*N*/   ((SwTxtFormatter*)this)->SetPaintDrop( sal_True );
/*N*/   return pDropPor;
/*N*/ }

/*************************************************************************
 *                SwTxtPainter::PaintDropPortion()
 *************************************************************************/



//STRIP001 void SwTxtPainter::PaintDropPortion()
//STRIP001 {
//STRIP001  const SwDropPortion *pDrop = GetInfo().GetParaPortion()->FindDropPortion();
//STRIP001  ASSERT( pDrop, "DrapCop-Portion not available." );
//STRIP001  if( !pDrop )
//STRIP001      return;
//STRIP001
//STRIP001  const SwTwips nOldY = GetInfo().Y();
//STRIP001
//STRIP001  Top();
//STRIP001
//STRIP001  GetInfo().SetSpaceAdd( pCurr->GetpSpaceAdd() );
//STRIP001  GetInfo().ResetSpaceIdx();
//STRIP001     GetInfo().SetKanaComp( pCurr->GetpKanaComp() );
//STRIP001     GetInfo().ResetKanaIdx();
//STRIP001
//STRIP001  // 8047: Drops und Dummies
//STRIP001  while( !pCurr->GetLen() && Next() )
//STRIP001      ;
//STRIP001
//STRIP001  // MarginPortion und Adjustment!
//STRIP001  const SwLinePortion *pPor = pCurr->GetFirstPortion();
//STRIP001  KSHORT nX = 0;
//STRIP001  while( pPor && !pPor->IsDropPortion() )
//STRIP001  {
//STRIP001      nX += pPor->Width();
//STRIP001      pPor = pPor->GetPortion();
//STRIP001  }
//STRIP001  Point aLineOrigin( GetTopLeft() );
//STRIP001
//STRIP001 #ifdef NIE
//STRIP001  // Retusche nachholen...
//STRIP001  if( nX )
//STRIP001  {
//STRIP001      const Point aPoint( Left(), Y() );
//STRIP001      const Size  aSize( nX - 1, GetDropHeight()+GetDropDescent() );
//STRIP001      SwRect aRetouche( aPoint, aSize );
//STRIP001      GetInfo().DrawRect( aRetouche );
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  aLineOrigin.X() += nX;
//STRIP001  KSHORT nTmpAscent, nTmpHeight;
//STRIP001  CalcAscentAndHeight( nTmpAscent, nTmpHeight );
//STRIP001  aLineOrigin.Y() += nTmpAscent;
//STRIP001  GetInfo().SetIdx( GetStart() );
//STRIP001  GetInfo().SetPos( aLineOrigin );
//STRIP001  GetInfo().SetLen( pDrop->GetLen() );
//STRIP001
//STRIP001  pDrop->PaintDrop( GetInfo() );
//STRIP001
//STRIP001  GetInfo().Y( nOldY );
//STRIP001 }

/*************************************************************************
 *                      clas SwDropCapCache
 *
 * Da die Berechnung der Fontgroesse der Initialen ein teures Geschaeft ist,
 * wird dies durch einen DropCapCache geschleust.
 *************************************************************************/

#define DROP_CACHE_SIZE 10

class SwDropCapCache
{
    long aMagicNo[ DROP_CACHE_SIZE ];
    XubString aTxt[ DROP_CACHE_SIZE ];
    USHORT aFactor[ DROP_CACHE_SIZE ];
    KSHORT aWishedHeight[ DROP_CACHE_SIZE ];
    short aDescent[ DROP_CACHE_SIZE ];
    MSHORT nIndex;
public:
    SwDropCapCache();
    ~SwDropCapCache(){}
    void CalcFontSize( SwDropPortion* pDrop, SwTxtFormatInfo &rInf );
};

/*************************************************************************
 *                  SwDropCapCache Ctor / Dtor
 *************************************************************************/

/*N*/ SwDropCapCache::SwDropCapCache() : nIndex( 0 )
/*N*/ {
/*N*/   memset( &aMagicNo, 0, sizeof(aMagicNo) );
/*N*/   memset( &aWishedHeight, 0, sizeof(aWishedHeight) );
/*N*/ }

/*N*/ void SwDropPortion::DeleteDropCapCache()
/*N*/ {
/*N*/   delete pDropCapCache;
/*N*/ }

/*************************************************************************
 *                  SwDropCapCache::CalcFontSize
 *************************************************************************/

/*N*/ void SwDropCapCache::CalcFontSize( SwDropPortion* pDrop, SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   const void* pFntNo;
/*N*/     MSHORT nTmpIdx = 0;
/*N*/
/*N*/     ASSERT( pDrop->GetPart(),"DropPortion without part during font calculation");
/*N*/
/*N*/     SwDropPortionPart* pCurrPart = pDrop->GetPart();
/*N*/     const sal_Bool bUseCache = ! pCurrPart->GetFollow();
/*N*/     xub_StrLen nIdx = rInf.GetIdx();
/*N*/     XubString aStr( rInf.GetTxt(), nIdx, pCurrPart->GetLen() );
/*N*/
/*N*/     long nAscent = 0;
/*N*/     long nDescent = 0;
/*N*/     long nFactor = -1;
/*N*/
/*N*/     if ( bUseCache )
/*N*/     {
/*N*/         SwFont& rFnt = pCurrPart->GetFont();
/*N*/         rFnt.ChkMagic( rInf.GetVsh(), rFnt.GetActual() );
/*N*/         rFnt.GetMagic( pFntNo, nTmpIdx, rFnt.GetActual() );
/*N*/
/*N*/         nTmpIdx = 0;
/*N*/
/*N*/         while( nTmpIdx < DROP_CACHE_SIZE &&
/*N*/             ( aTxt[ nTmpIdx ] != aStr || aMagicNo[ nTmpIdx ] != long(pFntNo) ||
/*N*/             aWishedHeight[ nTmpIdx ] != pDrop->GetDropHeight() ) )
/*N*/             ++nTmpIdx;
/*N*/     }
/*N*/
/*N*/     // we have to calculate a new font scaling factor if
/*N*/     // 1. we did not find a scaling factor in the cache or
/*N*/     // 2. we are not allowed to use the cache because the drop portion
/*N*/     //    consists of more than one part
/*N*/     if( nTmpIdx >= DROP_CACHE_SIZE || ! bUseCache )
/*N*/     {
/*N*/         ++nIndex;
/*N*/         nIndex %= DROP_CACHE_SIZE;
/*N*/         nTmpIdx = nIndex;
/*N*/
/*N*/         long nWishedHeight = pDrop->GetDropHeight();
/*N*/
/*N*/         // find out biggest font size for initial scaling factor
/*N*/         long nMaxFontHeight = 0;
/*N*/         while ( pCurrPart )
/*N*/         {
/*N*/             const SwFont& rFnt = pCurrPart->GetFont();
/*N*/             const long nCurrHeight = rFnt.GetHeight( rFnt.GetActual() );
/*N*/             if ( nCurrHeight > nMaxFontHeight )
/*N*/                 nMaxFontHeight = nCurrHeight;
/*N*/
/*N*/             pCurrPart = pCurrPart->GetFollow();
/*N*/         }
/*N*/
/*N*/         nFactor = ( 1000 * nWishedHeight ) / nMaxFontHeight;
/*N*/
/*N*/         if ( bUseCache )
/*N*/         {
/*N*/             // save keys for cache
/*N*/             aMagicNo[ nTmpIdx ] = long(pFntNo);
/*N*/             aTxt[ nTmpIdx ] = aStr;
/*N*/             aWishedHeight[ nTmpIdx ] = KSHORT(nWishedHeight);
/*N*/             // save initial scaling factor
/*N*/             aFactor[ nTmpIdx ] = (USHORT)nFactor;
/*N*/         }
/*N*/
/*N*/         sal_Bool bGrow = ( pDrop->GetLen() != 0 );
/*N*/
/*N*/         // for growing controll
/*N*/         long nMax = KSHRT_MAX;
/*N*/         long nMin = nFactor / 2;
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/         long nGrow = 0;
/*N*/ #endif
/*N*/
/*N*/         sal_Bool bWinUsed = sal_False;
/*N*/         Font aOldFnt;
/*N*/         MapMode aOldMap( MAP_TWIP );
/*N*/         OutputDevice *pOut = rInf.GetOut();
/*N*/         OutputDevice *pWin;
/*N*/         if( rInf.GetVsh() && rInf.GetVsh()->GetWin() )
/*N*/             pWin = rInf.GetVsh()->GetWin();
/*N*/         else
/*?*/             pWin = GetpApp()->GetDefaultDevice();
/*N*/
/*N*/         while( bGrow )
/*N*/         {
/*N*/             // reset pCurrPart to first part
/*N*/             pCurrPart = pDrop->GetPart();
/*N*/             sal_Bool bFirstGlyphRect = sal_True;
/*N*/             sal_Bool bHaveGlyphRect = sal_False;
/*N*/             Rectangle aCommonRect, aRect;
/*N*/
/*N*/             while ( pCurrPart )
/*N*/             {
/*N*/                 // current font
/*N*/                 SwFont& rFnt = pCurrPart->GetFont();
/*N*/
/*N*/                 // Get height including proportion
/*N*/                 const USHORT nCurrHeight =
/*N*/                          (USHORT)rFnt.GetHeight( rFnt.GetActual() );
/*N*/
/*N*/                 // Get without proportion
/*N*/                 const BYTE nOldProp = rFnt.GetPropr();
/*N*/                 rFnt.SetProportion( 100 );
/*N*/                 Size aOldSize = Size( 0, rFnt.GetHeight( rFnt.GetActual() ) );
/*N*/
/*N*/                 Size aNewSize( 0, ( nFactor * nCurrHeight ) / 1000 );
/*N*/                 rFnt.SetSize( aNewSize, rFnt.GetActual() );
/*N*/                 rFnt.ChgPhysFnt( rInf.GetVsh(), pOut );
/*N*/                 nAscent = rFnt.GetAscent( rInf.GetVsh(), pOut ) -
/*N*/                           rFnt.GetLeading( rInf.GetVsh(), pOut );
/*N*/
/*N*/                 // Wir besorgen uns das alle Buchstaben umfassende Rechteck:
/*N*/                 bHaveGlyphRect = pOut->GetTextBoundRect( aRect, rInf.GetTxt(), 0,
/*N*/                                      nIdx, pCurrPart->GetLen() ) &&
/*N*/                                  ! aRect.IsEmpty();
/*N*/
/*N*/                 if ( ! bHaveGlyphRect )
/*N*/                 {
/*?*/                     // getting glyph boundaries failed for some reason,
/*?*/                     // we take the window for calculating sizes
/*?*/                     if ( pWin )
/*?*/                     {
/*?*/                         if ( ! bWinUsed )
/*?*/                         {
/*?*/                             bWinUsed = sal_True;
/*?*/                             aOldMap = pWin->GetMapMode( );
/*?*/                             pWin->SetMapMode( MapMode( MAP_TWIP ) );
/*?*/                             aOldFnt = pWin->GetFont();
/*?*/                         }
/*?*/                         pWin->SetFont( rFnt.GetActualFont() );
/*?*/
/*?*/                         bHaveGlyphRect = pWin->GetTextBoundRect( aRect, rInf.GetTxt(), 0,
/*?*/                                             nIdx, pCurrPart->GetLen() ) &&
/*?*/                                         ! aRect.IsEmpty();
/*?*/                     }
/*?*/                     if ( bHaveGlyphRect )
/*?*/                     {
/*?*/                         FontMetric aWinMet( pWin->GetFontMetric() );
/*?*/                         nAscent = (KSHORT) aWinMet.GetAscent();
/*?*/                     }
/*?*/                     else
/*?*/                     // We do not have a window or our window could not
/*?*/                     // give us glyph boundaries.
/*?*/                         aRect = Rectangle( Point( 0, 0 ), Size( 0, nAscent ) );
/*N*/                 }
/*N*/
/*N*/                 // Now we (hopefully) have a bounding rectangle for the
/*N*/                 // glyphs of the current portion and the ascent of the current
/*N*/                 // font
/*N*/
/*N*/                 // reset font size and proportion
/*N*/                 rFnt.SetSize( aOldSize, rFnt.GetActual() );
/*N*/                 rFnt.SetProportion( nOldProp );
/*N*/
/*N*/                 if ( bFirstGlyphRect )
/*N*/                 {
/*N*/                     aCommonRect = aRect;
/*N*/                     bFirstGlyphRect = sal_False;
/*N*/                 }
/*N*/                 else
/*?*/                     aCommonRect.Union( aRect );
/*N*/
/*N*/                 nIdx += pCurrPart->GetLen();
/*N*/                 pCurrPart = pCurrPart->GetFollow();
/*N*/             }
/*N*/
/*N*/             // now we have a union ( aCommonRect ) of all glyphs with
/*N*/             // respect to a common baseline : 0
/*N*/
/*N*/             // get descent and ascent from union
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/             if ( rInf.GetTxtFrm()->IsVertical() )
/*N*/             {
/*?*/                 nDescent = aCommonRect.Left();
/*?*/                 nAscent = aCommonRect.Right();
/*?*/
/*?*/                 if ( nDescent < 0 )
/*?*/                     nDescent = -nDescent;
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 nDescent = aCommonRect.Bottom();
/*N*/                 nAscent = aCommonRect.Top();
/*N*/             }
/*N*/ #else
/*N*/             nDescent = aCommonRect.Bottom();
/*N*/             nAscent = aCommonRect.Top();
/*N*/ #endif
/*N*/             if ( nAscent < 0 )
/*N*/                 nAscent = -nAscent;
/*N*/
/*N*/             const long nHght = nAscent + nDescent;
/*N*/             if ( nHght )
/*N*/             {
/*N*/                 if ( nHght > nWishedHeight )
/*N*/                     nMax = nFactor;
/*N*/                 else
/*N*/                 {
/*N*/                     if ( bUseCache )
/*N*/                         aFactor[ nTmpIdx ] = (USHORT)nFactor;
/*N*/                     nMin = nFactor;
/*N*/                 }
/*N*/
/*N*/                 nFactor = ( nFactor * nWishedHeight ) / nHght;
/*N*/                 bGrow = ( nFactor > nMin ) && ( nFactor < nMax );
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/                 if ( bGrow )
/*N*/                     nGrow++;
/*N*/ #endif
/*N*/                 nIdx = rInf.GetIdx();
/*N*/             }
/*N*/             else
/*N*/                 bGrow = sal_False;
/*N*/         }
/*N*/
/*N*/         if ( bWinUsed )
/*N*/         {
/*N*/             // reset window if it has been used
/*?*/             pWin->SetMapMode( aOldMap );
/*?*/             pWin->SetFont( aOldFnt );
/*N*/         }
/*N*/
/*N*/         if ( bUseCache )
/*N*/             aDescent[ nTmpIdx ] = -short( nDescent );
/*N*/     }
/*N*/
/*N*/     pCurrPart = pDrop->GetPart();
/*N*/
/*N*/     // did made any new calculations or did we use the cache?
/*N*/     if ( -1 == nFactor )
/*N*/     {
/*N*/         nFactor = aFactor[ nTmpIdx ];
/*N*/         nDescent = aDescent[ nTmpIdx ];
/*N*/     }
/*N*/     else
/*N*/         nDescent = -nDescent;
/*N*/
/*N*/     while ( pCurrPart )
/*N*/     {
/*N*/         // scale current font
/*N*/         SwFont& rFnt = pCurrPart->GetFont();
/*N*/         Size aNewSize( 0, ( nFactor * rFnt.GetHeight( rFnt.GetActual() ) ) / 1000 );
/*N*/
/*N*/         const BYTE nOldProp = rFnt.GetPropr();
/*N*/         rFnt.SetProportion( 100 );
/*N*/         rFnt.SetSize( aNewSize, rFnt.GetActual() );
/*N*/         rFnt.SetProportion( nOldProp );
/*N*/
/*N*/         pCurrPart = pCurrPart->GetFollow();
/*N*/     }
/*N*/     pDrop->SetY( (short)nDescent );
/*N*/ }

/*************************************************************************
 *                virtual Format()
 *************************************************************************/

//STRIP001 sal_Bool SwDropPortion::Format( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  sal_Bool bFull = sal_False;
//STRIP001     Fix( (USHORT)rInf.X() );
//STRIP001
//STRIP001     SwLayoutModeModifier aLayoutModeModifier( *rInf.GetOut() );
//STRIP001     aLayoutModeModifier.SetAuto();
//STRIP001
//STRIP001     if( nDropHeight && pPart && nLines!=1 )
//STRIP001  {
//STRIP001      if( !pDropCapCache )
//STRIP001          pDropCapCache = new SwDropCapCache();
//STRIP001
//STRIP001         // adjust font sizes to fit into the rectangle
//STRIP001         pDropCapCache->CalcFontSize( this, rInf );
//STRIP001
//STRIP001         const long nOldX = rInf.X();
//STRIP001         {
//STRIP001             SwDropSave aSave( rInf );
//STRIP001             SwDropPortionPart* pCurrPart = pPart;
//STRIP001
//STRIP001             while ( pCurrPart )
//STRIP001             {
//STRIP001                 rInf.SetLen( pCurrPart->GetLen() );
//STRIP001                 SwFont& rFnt = pCurrPart->GetFont();
//STRIP001                 {
//STRIP001                     SwFontSave aSave( rInf, &rFnt );
//STRIP001                     bFull = FormatTxt( rInf );
//STRIP001
//STRIP001                     if ( bFull )
//STRIP001                         break;
//STRIP001                 }
//STRIP001
//STRIP001                 SwTwips nTmpWidth =
//STRIP001                         ( InSpaceGrp() && rInf.GetSpaceAdd() ) ?
//STRIP001                         Width() + CalcSpacing( rInf.GetSpaceAdd(), rInf ) :
//STRIP001                         Width();
//STRIP001
//STRIP001                 // set values
//STRIP001                 pCurrPart->SetWidth( (USHORT)nTmpWidth );
//STRIP001
//STRIP001                 // Move
//STRIP001                 rInf.SetIdx( rInf.GetIdx() + pCurrPart->GetLen() );
//STRIP001                 rInf.X( rInf.X() + nTmpWidth );
//STRIP001                 pCurrPart = pCurrPart->GetFollow();
//STRIP001             }
//STRIP001
//STRIP001             Width( (USHORT)(rInf.X() - nOldX) );
//STRIP001         }
//STRIP001
//STRIP001         // reset my length
//STRIP001         SetLen( rInf.GetLen() );
//STRIP001
//STRIP001         // 7631, 7633: bei Ueberlappungen mit Flys ist Schluss.
//STRIP001         if( ! bFull )
//STRIP001             bFull = lcl_IsDropFlyInter( rInf, Width(), nDropHeight );
//STRIP001
//STRIP001         if( bFull )
//STRIP001      {
//STRIP001          // Durch FormatTxt kann nHeight auf 0 gesetzt worden sein
//STRIP001          if ( !Height() )
//STRIP001              Height( rInf.GetTxtHeight() );
//STRIP001
//STRIP001             // Jetzt noch einmal der ganze Spass
//STRIP001             nDropHeight = nLines = 0;
//STRIP001             delete pPart;
//STRIP001             pPart = NULL;
//STRIP001
//STRIP001             // meanwhile use normal formatting
//STRIP001             bFull = SwTxtPortion::Format( rInf );
//STRIP001      }
//STRIP001      else
//STRIP001          rInf.SetDropInit( sal_True );
//STRIP001
//STRIP001         Height( rInf.GetTxtHeight() );
//STRIP001         SetAscent( rInf.GetAscent() );
//STRIP001  }
//STRIP001  else
//STRIP001      bFull = SwTxtPortion::Format( rInf );
//STRIP001
//STRIP001  if( bFull )
//STRIP001      nDistance = 0;
//STRIP001  else
//STRIP001  {
//STRIP001      const KSHORT nWant = Width() + GetDistance();
//STRIP001         const KSHORT nRest = (USHORT)(rInf.Width() - rInf.X());
//STRIP001         if( ( nWant > nRest ) ||
//STRIP001             lcl_IsDropFlyInter( rInf, Width() + GetDistance(), nDropHeight ) )
//STRIP001          nDistance = 0;
//STRIP001
//STRIP001      Width( Width() + nDistance );
//STRIP001  }
//STRIP001  return bFull;
//STRIP001 }

