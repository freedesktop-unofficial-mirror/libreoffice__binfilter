/*************************************************************************
 *
 *  $RCSfile: sw_porrst.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:35:28 $
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

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVX_LSPCITEM_HXX //autogen
#include <bf_svx/lspcitem.hxx>
#endif
#ifndef _SVX_ADJITEM_HXX //autogen
#include <bf_svx/adjitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_PGRDITEM_HXX
#include <bf_svx/pgrditem.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>    // SwTxtNode
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>  // SwPageFrm
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>   // ASSERT
#endif
#ifndef _SW_PORTIONHANDLER_HXX
#include <SwPortionHandler.hxx>
#endif
#ifndef _TXTCFG_HXX
#include <txtcfg.hxx>
#endif
#ifndef _PORRST_HXX
#include <porrst.hxx>
#endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>
#endif
#ifndef _TXTPAINT_HXX
#include <txtpaint.hxx> // ClipVout
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>   // SwTxtFrm
#endif
#ifndef _SWFNTCCH_HXX
#include <swfntcch.hxx> // SwFontAccess
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> // SwPageDesc
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _REDLNITR_HXX
#include <redlnitr.hxx> // SwRedlineItr
#endif
#ifndef _PORFLY_HXX
#include <porfly.hxx>   // SwFlyPortion
#endif
#ifndef _ATRHNDL_HXX
#include <atrhndl.hxx>
#endif
/*************************************************************************
 *                      class SwTmpEndPortion
 *************************************************************************/

SwTmpEndPortion::SwTmpEndPortion( const SwLinePortion &rPortion )
{
    DBG_ASSERT(0, "STRIP"); //STRIP001 Height( rPortion.Height() );
//STRIP001  SetAscent( rPortion.GetAscent() );
//STRIP001  SetWhichPor( POR_TMPEND );
}

/*************************************************************************
 *                 virtual SwTmpEndPortion::Paint()
 *************************************************************************/

//STRIP001 void SwTmpEndPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( rInf.OnWin() && rInf.GetOpt().IsParagraph() )
//STRIP001  {
//STRIP001      SwDefFontSave aSave( rInf );
//STRIP001      const XubString aTmp( CH_PAR );
//STRIP001      rInf.DrawText( aTmp, *this );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                      class SwBreakPortion
 *************************************************************************/
/*N*/ SwBreakPortion::SwBreakPortion( const SwLinePortion &rPortion )
/*N*/     : SwLinePortion( rPortion ), nRestWidth( 0 )
/*N*/ {
/*N*/   nLineLength = 1;
/*N*/   SetWhichPor( POR_BRK );
/*N*/ }

//STRIP001 xub_StrLen SwBreakPortion::GetCrsrOfst( const KSHORT ) const
//STRIP001 { return 0; }
//STRIP001
//STRIP001 KSHORT SwBreakPortion::GetViewWidth( const SwTxtSizeInfo &rInf ) const
//STRIP001 { return 0; }

/*N*/ SwLinePortion *SwBreakPortion::Compress()
/*N*/ { return (GetPortion() && GetPortion()->InTxtGrp() ? 0 : this); }

//STRIP001 void SwBreakPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001     if( rInf.OnWin() && rInf.GetOpt().IsLineBreak() )
//STRIP001  {
//STRIP001         USHORT nViewWidth = ((SwBreakPortion*)this)->CalcViewWidth( rInf );
//STRIP001
//STRIP001      if( nViewWidth && nViewWidth <= nRestWidth )
//STRIP001          rInf.DrawLineBreak( *this );
//STRIP001     }
//STRIP001 }

/*************************************************************************
 *                  SwBreakPortion::CalcViewWidth()
 *************************************************************************/

//STRIP001 USHORT SwBreakPortion::CalcViewWidth( const SwTxtSizeInfo &rInf )
//STRIP001 {
//STRIP001  ASSERT( rInf.GetOpt().IsLineBreak(), "SwBreakPortion::CalcViewWidth: zombie" );
//STRIP001  // Im Mormalfall folgt auf ein Break keine weitere Portion, nur wenn im Blocksatz
//STRIP001  // auch die letzte Zeile im Blocksatz ist, folgt eine Marginportion der Breite 0,
//STRIP001  // ist die Zeile zentriert, so folgt eine Marginportion mit Breite > 0.
//STRIP001  if( GetPortion() )
//STRIP001  {
//STRIP001      if( GetPortion()->IsFlyPortion() )
//STRIP001      {
//STRIP001          short nTmp = ((SwFlyPortion*)GetPortion())->GetPrtGlue();
//STRIP001          nRestWidth = nTmp > 0 ? nTmp : 0;
//STRIP001      }
//STRIP001      else
//STRIP001          nRestWidth = GetPortion()->Width();
//STRIP001  }
//STRIP001     USHORT nViewWidth = 0;
//STRIP001
//STRIP001     // The view width is not depending on the zoom factor anymore.
//STRIP001     if( rInf.OnWin() && nRestWidth )
//STRIP001         nViewWidth = LINE_BREAK_WIDTH;
//STRIP001
//STRIP001     return nViewWidth;
//STRIP001 }

/*************************************************************************
 *                 virtual SwBreakPortion::Format()
 *************************************************************************/

/*N*/ sal_Bool SwBreakPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/     nRestWidth = (USHORT)(rInf.Width() - rInf.X());
/*N*/   register const SwLinePortion *pRoot = rInf.GetRoot();
/*N*/   Width( 0 );
/*N*/   Height( pRoot->Height() );
/*N*/   SetAscent( pRoot->GetAscent() );
/*N*/   if ( rInf.GetIdx()+1 == rInf.GetTxt().Len() )
/*N*/       rInf.SetNewLine( sal_True );
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *              virtual SwBreakPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwBreakPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Text( GetLen(), GetWhichPor() );
//STRIP001 }


/*N*/ SwKernPortion::SwKernPortion( SwLinePortion &rPortion, short nKrn,
/*N*/                               sal_Bool bBG, sal_Bool bGK ) :
/*N*/     nKern( nKrn ), bBackground( bBG ), bGridKern( bGK )
/*N*/ {
/*N*/   Height( rPortion.Height() );
/*N*/   SetAscent( rPortion.GetAscent() );
/*N*/   nLineLength = 0;
/*N*/   SetWhichPor( POR_KERN );
/*N*/   if( nKern > 0 )
/*N*/       Width( nKern );
/*N*/   rPortion.Insert( this );
/*N*/ }

//STRIP001 SwKernPortion::SwKernPortion( const SwLinePortion& rPortion ) :
//STRIP001     nKern( 0 ), bBackground( sal_False ), bGridKern( sal_True )
//STRIP001 {
//STRIP001  Height( rPortion.Height() );
//STRIP001  SetAscent( rPortion.GetAscent() );
//STRIP001
//STRIP001  nLineLength = 0;
//STRIP001  SetWhichPor( POR_KERN );
//STRIP001 }

/*N*/ void SwKernPortion::Paint( const SwTxtPaintInfo &rInf ) const
/*N*/ {
            DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   if( Width() )
//STRIP001  {
//STRIP001         // bBackground is set for Kerning Portions between two fields
//STRIP001         if ( bBackground )
//STRIP001             rInf.DrawViewOpt( *this, POR_FLD );
//STRIP001
//STRIP001      rInf.DrawBackBrush( *this );
//STRIP001
//STRIP001         // do we have to repaint a post it portion?
//STRIP001         if( rInf.OnWin() && pPortion && !pPortion->Width() )
//STRIP001             pPortion->PrePaint( rInf, this );
//STRIP001
//STRIP001      if( rInf.GetFont()->IsPaintBlank() )
//STRIP001      {
//STRIP001 static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
//STRIP001          // Tabs mit Fuellung
//STRIP001          if( rInf.OnWin() ) // Keine Luecken am Bildschirm
//STRIP001              ((SwKernPortion*)this)->Width( Width() + 12 );
//STRIP001          XubString aTxt( sDoubleSpace, RTL_TEXTENCODING_MS_1252 );
//STRIP001          rInf.DrawText( aTxt, *this, 0, 2, sal_True );
//STRIP001          if( rInf.OnWin() )
//STRIP001              ((SwKernPortion*)this)->Width( Width() - 12 );
//STRIP001      }
//STRIP001  }
/*N*/ }

/*N*/ void SwKernPortion::FormatEOL( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/     if ( bGridKern )
/*N*/         return;
/*N*/
/*N*/     if( rInf.GetLast() == this )
/*N*/       rInf.SetLast( FindPrevPortion( rInf.GetRoot() ) );
/*N*/   if( nKern < 0 )
/*N*/       Width( -nKern );
/*N*/   else
/*N*/       Width( 0 );
/*N*/   rInf.GetLast()->FormatEOL( rInf );
/*N*/ }

/*N*/ SwArrowPortion::SwArrowPortion( const SwLinePortion &rPortion ) :
/*N*/   bLeft( sal_True )
/*N*/ {
/*N*/ DBG_ASSERT(0, "STRIP"); //STRIP001    Height( rPortion.Height() );
//STRIP001  SetAscent( rPortion.GetAscent() );
//STRIP001  nLineLength = 0;
//STRIP001  SetWhichPor( POR_ARROW );
/*N*/ }

/*N*/ SwArrowPortion::SwArrowPortion( const SwTxtPaintInfo &rInf )
/*N*/   : bLeft( sal_False )
/*N*/ {
  DBG_ASSERT(0, "STRIP"); //STRIP001   Height( (USHORT)(rInf.GetTxtFrm()->Prt().Height()) );
//STRIP001  aPos.X() = rInf.GetTxtFrm()->Frm().Left() +
//STRIP001             rInf.GetTxtFrm()->Prt().Right();
//STRIP001  aPos.Y() = rInf.GetTxtFrm()->Frm().Top() +
//STRIP001             rInf.GetTxtFrm()->Prt().Bottom();
/*N*/ }

/*N*/ void SwArrowPortion::Paint( const SwTxtPaintInfo &rInf ) const
/*N*/ {
/*N*/       DBG_ASSERT(0, "STRIP");  //STRIP001     ((SwArrowPortion*)this)->aPos = rInf.GetPos();
/*N*/ }

/*N*/ SwLinePortion *SwArrowPortion::Compress() { return this; }

/*N*/ SwTwips SwTxtFrm::EmptyHeight() const
/*N*/ {
/*N*/     ASSERT( ! IsVertical() || ! IsSwapped(),"SwTxtFrm::EmptyHeight with swapped frame" );
/*N*/
/*N*/     SwFont *pFnt;
/*N*/   const SwTxtNode& rTxtNode = *GetTxtNode();
/*N*/   ViewShell *pSh = GetShell();
/*N*/   if ( rTxtNode.HasSwAttrSet() )
/*N*/   {
/*N*/       const SwAttrSet *pAttrSet = &( rTxtNode.GetSwAttrSet() );
/*N*/         pFnt = new SwFont( pAttrSet, GetTxtNode()->GetDoc() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwFontAccess aFontAccess( &rTxtNode.GetAnyFmtColl(), pSh);
/*N*/         pFnt = new SwFont( *aFontAccess.Get()->GetFont() );
/*N*/       pFnt->ChkMagic( pSh, pFnt->GetActual() );
/*N*/   }
/*N*/
/*N*/     if ( IsVertical() )
/*?*/         pFnt->SetVertical( 2700 );
/*N*/
/*N*/   OutputDevice *pOut = pSh ? pSh->GetOut() : 0;
/*N*/   if ( !pOut || !rTxtNode.GetDoc()->IsBrowseMode() ||
/*N*/        ( pSh->GetViewOptions()->IsPrtFormat() ) )
/*N*/   {
/*N*/         pOut = &rTxtNode.GetDoc()->GetRefDev();
/*N*/   }
/*N*/
/*N*/   const SwDoc* pDoc = rTxtNode.GetDoc();
/*N*/   if( ::IsShowChanges( pDoc->GetRedlineMode() ) )
/*N*/   {
/*N*/       MSHORT nRedlPos = pDoc->GetRedlinePos( rTxtNode );
/*N*/         if( MSHRT_MAX != nRedlPos )
/*N*/         {
                DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/             SwAttrHandler aAttrHandler;
//STRIP001 /*?*/             aAttrHandler.Init( GetTxtNode()->GetSwAttrSet(),
//STRIP001 /*?*/                               *GetTxtNode()->GetDoc(), NULL );
//STRIP001 /*?*/             SwRedlineItr aRedln( rTxtNode, *pFnt, aAttrHandler,
//STRIP001 /*?*/                                  nRedlPos, sal_True );
/*N*/         }
/*N*/     }
/*N*/
/*N*/   SwTwips nRet;
/*N*/   if( !pOut )
/*?*/         nRet = IsVertical() ?
/*?*/                Prt().SSize().Width() + 1 :
/*?*/                Prt().SSize().Height() + 1;
/*N*/   else
/*N*/   {
/*N*/       pFnt->SetFntChg( sal_True );
/*N*/       pFnt->ChgPhysFnt( pSh, pOut );
/*N*/       nRet = pFnt->GetHeight( pSh, pOut );
/*N*/   }
/*N*/   delete pFnt;
/*N*/   return nRet;
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::FormatEmpty()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFrm::FormatEmpty()
/*N*/ {
/*N*/     ASSERT( ! IsVertical() || ! IsSwapped(),"SwTxtFrm::FormatEmpty with swapped frame" );
/*N*/
/*N*/   if ( HasFollow() || GetTxtNode()->GetpSwpHints() ||
/*N*/       0 != GetTxtNode()->GetNumRule() ||
/*N*/       0 != GetTxtNode()->GetOutlineNum() ||
/*N*/        IsInFtn() || ( HasPara() && GetPara()->IsPrepMustFit() ) )
/*N*/       return sal_False;
/*N*/   const SwAttrSet& aSet = GetTxtNode()->GetSwAttrSet();
/*N*/ #ifdef BIDI
/*N*/     const USHORT nAdjust = aSet.GetAdjust().GetAdjust();
/*N*/     if( ( ( ! IsRightToLeft() && ( SVX_ADJUST_LEFT != nAdjust ) ) ||
/*N*/           (   IsRightToLeft() && ( SVX_ADJUST_RIGHT != nAdjust ) ) ) ||
/*N*/           aSet.GetRegister().GetValue() )
/*N*/ #else
/*N*/   if( SVX_ADJUST_LEFT != aSet.GetAdjust().GetAdjust()
/*N*/       || aSet.GetRegister().GetValue() )
/*N*/ #endif
/*N*/       return sal_False;
/*N*/   const SvxLineSpacingItem &rSpacing = aSet.GetLineSpacing();
/*N*/   if( SVX_LINE_SPACE_MIN == rSpacing.GetLineSpaceRule() ||
/*N*/       SVX_LINE_SPACE_FIX == rSpacing.GetLineSpaceRule() ||
/*N*/       aSet.GetLRSpace().IsAutoFirst() )
/*N*/       return sal_False;
/*N*/   else
/*N*/   {
/*N*/         SwTxtFly aTxtFly( this );
/*N*/       SwRect aRect;
/*N*/       sal_Bool bFirstFlyCheck = 0 != Prt().Height();
/*N*/       if ( bFirstFlyCheck &&
/*N*/            aTxtFly.IsOn() && aTxtFly.IsAnyObj( aRect ) )
/*N*/           return sal_False;
/*N*/       else
/*N*/       {
/*N*/             SwTwips nHeight = EmptyHeight();
/*N*/
/*N*/             if ( GetTxtNode()->GetSwAttrSet().GetParaGrid().GetValue() &&
/*N*/                  IsInDocBody() )
/*N*/             {
/*N*/                 GETGRID( FindPageFrm() )
/*N*/                 if ( pGrid )
/*?*/                     nHeight = pGrid->GetBaseHeight() + pGrid->GetRubyHeight();
/*N*/             }
/*N*/
/*N*/             SWRECTFN( this )
/*N*/             const SwTwips nChg = nHeight - (Prt().*fnRect->fnGetHeight)();
/*N*/
/*N*/             if( !nChg )
/*N*/               SetUndersized( sal_False );
/*N*/           AdjustFrm( nChg );
/*N*/
/*N*/           if( HasBlinkPor() )
/*N*/           {
/*?*/               ClearPara();
/*?*/               ResetBlinkPor();
/*N*/           }
/*N*/           SetCacheIdx( MSHRT_MAX );
/*N*/           if( !IsEmpty() )
/*N*/           {
/*N*/               SetEmpty( sal_True );
/*N*/               SetCompletePaint();
/*N*/           }
/*N*/           if( !bFirstFlyCheck &&
/*N*/                aTxtFly.IsOn() && aTxtFly.IsAnyObj( aRect ) )
/*N*/                return sal_False;
/*N*/           return sal_True;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ sal_Bool SwTxtFrm::FillRegister( SwTwips& rRegStart, KSHORT& rRegDiff )
/*N*/ {
/*N*/   const SwFrm *pFrm = this;
/*N*/   rRegDiff = 0;
/*N*/   while( !( ( FRM_BODY | FRM_FLY )
/*N*/          & pFrm->GetType() ) && pFrm->GetUpper() )
/*N*/       pFrm = pFrm->GetUpper();
/*N*/   if( ( FRM_BODY| FRM_FLY ) & pFrm->GetType() )
/*N*/   {
/*N*/         SWRECTFN( pFrm )
/*N*/         rRegStart = (pFrm->*fnRect->fnGetPrtTop)();
/*N*/       pFrm = pFrm->FindPageFrm();
/*N*/       if( pFrm->IsPageFrm() )
/*N*/       {
/*N*/           SwPageDesc* pDesc = ((SwPageFrm*)pFrm)->FindPageDesc();
/*N*/           if( pDesc )
/*N*/           {
/*N*/               rRegDiff = pDesc->GetRegHeight();
/*N*/               if( !rRegDiff )
/*N*/               {
/*N*/                   const SwTxtFmtColl *pFmt = pDesc->GetRegisterFmtColl();
/*N*/                   if( pFmt )
/*N*/                   {
/*N*/                       const SvxLineSpacingItem &rSpace = pFmt->GetLineSpacing();
/*N*/                       if( SVX_LINE_SPACE_FIX == rSpace.GetLineSpaceRule() )
/*N*/                       {
/*?*/                           rRegDiff = rSpace.GetLineHeight();
/*?*/                           pDesc->SetRegHeight( rRegDiff );
/*?*/                           pDesc->SetRegAscent( ( 4 * rRegDiff ) / 5 );
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           ViewShell *pSh = GetShell();
/*N*/                           SwFontAccess aFontAccess( pFmt, pSh );
/*N*/                           SwFont aFnt( *aFontAccess.Get()->GetFont() );
/*N*/                           OutputDevice *pOut = 0;
/*N*/                           if( !GetTxtNode()->GetDoc()->IsBrowseMode() ||
/*N*/                               (pSh && pSh->GetViewOptions()->IsPrtFormat()) )
/*N*/                                 pOut = &GetTxtNode()->GetDoc()->GetRefDev();
/*N*/                             if( pSh && !pOut )
/*?*/                               pOut = pSh->GetWin();
/*N*/                           if( !pOut )
/*?*/                               pOut = GetpApp()->GetDefaultDevice();
/*N*/                           MapMode aOldMap( pOut->GetMapMode() );
/*N*/                           pOut->SetMapMode( MapMode( MAP_TWIP ) );
/*N*/                           aFnt.ChgFnt( pSh, pOut );
/*N*/                           rRegDiff = aFnt.GetHeight( pSh, pOut );
/*N*/                           KSHORT nNettoHeight = rRegDiff;
/*N*/                           switch( rSpace.GetLineSpaceRule() )
/*N*/                           {
/*N*/                               case SVX_LINE_SPACE_AUTO:
/*N*/                               break;
/*N*/                               case SVX_LINE_SPACE_MIN:
/*N*/                               {
/*N*/                                   if( rRegDiff < KSHORT( rSpace.GetLineHeight() ) )
/*N*/                                       rRegDiff = rSpace.GetLineHeight();
/*N*/                                   break;
/*N*/                               }
/*N*/                               default: ASSERT(
/*N*/                               sal_False, ": unknown LineSpaceRule" );
/*N*/                           }
/*N*/                           switch( rSpace.GetInterLineSpaceRule() )
/*N*/                           {
/*N*/                               case SVX_INTER_LINE_SPACE_OFF:
/*N*/                               break;
/*?*/                               case SVX_INTER_LINE_SPACE_PROP:
/*?*/                               {
/*?*/                                   long nTmp = rSpace.GetPropLineSpace();
/*?*/                                   if( nTmp < 50 )
/*?*/                                       nTmp = nTmp ? 50 : 100;
/*?*/                                   nTmp *= rRegDiff;
/*?*/                                   nTmp /= 100;
/*?*/                                   if( !nTmp )
/*?*/                                       ++nTmp;
/*?*/                                   rRegDiff = (KSHORT)nTmp;
/*?*/                                   nNettoHeight = rRegDiff;
/*?*/                                   break;
/*?*/                               }
/*?*/                               case SVX_INTER_LINE_SPACE_FIX:
/*?*/                               {
/*?*/                                   rRegDiff += rSpace.GetInterLineSpace();
/*?*/                                   nNettoHeight = rRegDiff;
/*?*/                                   break;
/*?*/                               }
/*?*/                               default: ASSERT( sal_False, ": unknown InterLineSpaceRule" );
/*N*/                           }
/*N*/                           pDesc->SetRegHeight( rRegDiff );
/*N*/                           pDesc->SetRegAscent( rRegDiff - nNettoHeight +
/*N*/                                                aFnt.GetAscent( pSh, pOut ) );
/*N*/                           pOut->SetMapMode( aOldMap );
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/                 const long nTmpDiff = pDesc->GetRegAscent() - rRegDiff;
/*N*/                 if ( bVert )
/*?*/                     rRegStart -= nTmpDiff;
/*N*/                 else
/*N*/                     rRegStart += nTmpDiff;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return ( 0 != rRegDiff );
/*N*/ }
