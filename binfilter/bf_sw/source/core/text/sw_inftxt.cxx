/*************************************************************************
 *
 *  $RCSfile: sw_inftxt.cxx,v $
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

#include <com/sun/star/uno/Sequence.h>

#ifndef _SVTOOLS_LINGUPROPS_HXX_
#include <svtools/linguprops.hxx>
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVTOOLS_CTLOPTIONS_HXX
#include <svtools/ctloptions.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVX_HYZNITEM_HXX //autogen
#include <bf_svx/hyznitem.hxx>
#endif
#ifndef _SVX_ESCPITEM_HXX //autogen
#include <bf_svx/escpitem.hxx>
#endif
#ifndef _SVX_HNGPNCTITEM_HXX
#include <bf_svx/hngpnctitem.hxx>
#endif
#ifndef _SVX_SRIPTSPACEITEM_HXX
#include <bf_svx/scriptspaceitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_SPLWRAP_HXX
#include <bf_svx/splwrap.hxx>
#endif
#ifndef _SVX_PGRDITEM_HXX
#include <bf_svx/pgrditem.hxx>
#endif
#ifndef _LINGUISTIC_LNGPROPS_HHX_
#include <bf_linguistic/lngprops.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _SVX_FORBIDDENRULEITEM_HXX
#include <bf_svx/forbiddenruleitem.hxx>
#endif
#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
#ifndef _SWMODULE_HXX //autogen
#include <swmodule.hxx>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>  // SwViewOptions
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>  // DrawGraphic
#endif
#ifndef _DOC_HXX
#include <doc.hxx>      // SwDoc
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>   // SwFmtDrop
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>  // SwRootFrm
#endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>   // SwTxtInfo
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>   // SwFont
#endif
#ifndef _TXTFLY_HXX
#include <txtfly.hxx>   // SwTxtPaintInfo
#endif
#ifndef _BLINK_HXX
#include <blink.hxx>    // SwBlink
#endif
#ifndef _NOTEURL_HXX
#include <noteurl.hxx>  // SwNoteURL
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx> // SwDrawTextInfo
#endif
#ifndef _PORFTN_HXX
#include <porftn.hxx>   // SwFtnPortion
#endif
#ifndef _PORRST_HXX
#include <porrst.hxx>       // SwHangingPortion
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _ITRATR_HXX
#include <itratr.hxx>
#endif
#ifndef _ACCESSIBILITYOPTIONS_HXX
#include <accessibilityoptions.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::linguistic2;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;

#define C2U(cChar) ::rtl::OUString::createFromAscii(cChar)
#define CHAR_UNDERSCORE ((sal_Unicode)0x005F)
#define CHAR_LEFT_ARROW ((sal_Unicode)0x25C0)
#define CHAR_RIGHT_ARROW ((sal_Unicode)0x25B6)
#define CHAR_TAB ((sal_Unicode)0x2192)
#define CHAR_TAB_RTL ((sal_Unicode)0x2190)
#define CHAR_LINEBREAK ((sal_Unicode)0x21B5)
#define CHAR_LINEBREAK_RTL ((sal_Unicode)0x21B3)

#ifdef BIDI
#define DRAW_SPECIAL_OPTIONS_CENTER 1
#define DRAW_SPECIAL_OPTIONS_ROTATE 2
#endif

// steht im number.cxx
extern const sal_Char __FAR_DATA sBulletFntName[];

// OD 24.01.2003 #106593# - no longer needed, included in <frmtool.hxx>
//extern void MA_FASTCALL SwAlignRect( SwRect &rRect, ViewShell *pSh );

#ifndef PRODUCT
// Test2: WYSIWYG++
// Test4: WYSIWYG debug
static sal_Bool bDbgLow = sal_False;
#endif

#ifndef PRODUCT

//STRIP001 sal_Bool SwTxtSizeInfo::IsOptCalm() const { return !GetOpt().IsTest3(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptLow() const { return bDbgLow; }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptDbg() const { return GetOpt().IsTest4(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest1() const { return GetOpt().IsTest1(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest2() const { return GetOpt().IsTest2(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest3() const { return GetOpt().IsTest3(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest4() const { return GetOpt().IsTest4(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest5() const { return GetOpt().IsTest5(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest6() const { return GetOpt().IsTest6(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest7() const { return GetOpt().IsTest7(); }
//STRIP001
//STRIP001 sal_Bool SwTxtSizeInfo::IsOptTest8() const { return GetOpt().IsTest8(); }

#endif

/*************************************************************************
 *                      SwLineInfo::SwLineInfo()
 *************************************************************************/

/*N*/ void SwLineInfo::CtorInit( const SwAttrSet& rAttrSet )
/*N*/ {
/*N*/   pRuler = &rAttrSet.GetTabStops();
/*N*/   pSpace = &rAttrSet.GetLineSpacing();
/*N*/     nVertAlign = rAttrSet.GetParaVertAlign().GetValue();
/*N*/     nDefTabStop = MSHRT_MAX;
/*N*/ }

/*************************************************************************
 *                      SwTxtInfo::CtorInit()
 *************************************************************************/

/*N*/ void SwTxtInfo::CtorInit( SwTxtFrm *pFrm )
/*N*/ {
/*N*/   pPara = pFrm->GetPara();
/*N*/   nTxtStart = pFrm->GetOfst();
/*N*/   if( !pPara )
/*N*/   {
/*?*/       ASSERT( pPara, "+SwTxtInfo::CTOR: missing paragraph information" );
/*?*/       pFrm->Format();
/*?*/       pPara = pFrm->GetPara();
/*N*/   }
/*N*/ }

/*N*/ SwTxtInfo::SwTxtInfo( const SwTxtInfo &rInf )
/*N*/   : pPara( ((SwTxtInfo&)rInf).GetParaPortion() ),
/*N*/     nTxtStart( rInf.GetTxtStart() )
/*N*/ { }


#ifndef PRODUCT
/*************************************************************************
 *                      ChkOutDev()
 *************************************************************************/

/*N*/ void ChkOutDev( const SwTxtSizeInfo &rInf )
/*N*/ {
/*N*/     if ( !rInf.GetVsh() )
/*N*/         return;
/*N*/
/*N*/     const OutputDevice *pOut = rInf.GetOut();
/*N*/     const OutputDevice *pWin = rInf.GetVsh()->GetWin();
/*N*/     const OutputDevice *pRef = rInf.GetRefDev();
/*N*/     ASSERT( pOut && pRef, "ChkOutDev: invalid output devices" )
/*N*/ }
/*N*/ #endif    // PRODUCT


/*N*/ inline xub_StrLen GetMinLen( const SwTxtSizeInfo &rInf )
/*N*/ {
/*N*/   const xub_StrLen nInfLen = rInf.GetIdx() + rInf.GetLen();
/*N*/   return Min( rInf.GetTxt().Len(), nInfLen );
/*N*/ }


/*N*/ SwTxtSizeInfo::SwTxtSizeInfo( const SwTxtSizeInfo &rNew )
/*N*/   : SwTxtInfo( rNew ),
/*N*/       pKanaComp(((SwTxtSizeInfo&)rNew).GetpKanaComp()),
/*N*/       pVsh(((SwTxtSizeInfo&)rNew).GetVsh()),
/*N*/     pOut(((SwTxtSizeInfo&)rNew).GetOut()),
/*N*/       pRef(((SwTxtSizeInfo&)rNew).GetRefDev()),
/*N*/     pFnt(((SwTxtSizeInfo&)rNew).GetFont()),
/*N*/       pUnderFnt(((SwTxtSizeInfo&)rNew).GetUnderFnt()),
/*N*/     pFrm(rNew.pFrm),
/*N*/     pOpt(&rNew.GetOpt()),
/*N*/     pTxt(&rNew.GetTxt()),
/*N*/     nIdx(rNew.GetIdx()),
/*N*/     nLen(rNew.GetLen()),
/*N*/       nKanaIdx( rNew.GetKanaIdx() ),
/*N*/     bOnWin( rNew.OnWin() ),
/*N*/     bNotEOL( rNew.NotEOL() ),
/*N*/     bURLNotify( rNew.URLNotify() ),
/*N*/     bStopUnderFlow( rNew.StopUnderFlow() ),
/*N*/       bFtnInside( rNew.IsFtnInside() ),
/*N*/     bMulti( rNew.IsMulti() ),
/*N*/     bFirstMulti( rNew.IsFirstMulti() ),
/*N*/     bRuby( rNew.IsRuby() ),
/*N*/     bHanging( rNew.IsHanging() ),
/*N*/     bScriptSpace( rNew.HasScriptSpace() ),
/*N*/     bForbiddenChars( rNew.HasForbiddenChars() ),
/*N*/       bSnapToGrid( rNew.SnapToGrid() ),
/*N*/     nDirection( rNew.GetDirection() )
/*N*/ {
/*N*/ #ifndef PRODUCT
/*N*/   ChkOutDev( *this );
/*N*/ #endif
/*N*/ }

/*N*/ void SwTxtSizeInfo::CtorInit( SwTxtFrm *pFrame, SwFont *pNewFnt,
/*N*/                  const xub_StrLen nNewIdx, const xub_StrLen nNewLen )
/*N*/ {
/*N*/     pKanaComp = NULL;
/*N*/     nKanaIdx = 0;
/*N*/   pFrm = pFrame;
/*N*/   SwTxtInfo::CtorInit( pFrm );
/*N*/   const SwTxtNode *pNd = pFrm->GetTxtNode();
/*N*/   pVsh = pFrm->GetShell();
/*N*/
/*N*/     // Get the output and reference device
/*N*/     if ( pVsh )
/*N*/     {
/*N*/         pOut = pVsh->GetOut();
/*N*/         pRef = &pVsh->GetRefDev();
/*N*/         bOnWin = pVsh->GetWin() || OUTDEV_WINDOW == pOut->GetOutDevType();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         //Zugriff ueber StarONE, es muss keine Shell existieren oder aktiv sein.
/*N*/         if ( pNd->GetDoc()->IsBrowseMode() ) //?!?!?!?
/*N*/             //in Ermangelung eines Besseren kann hier ja wohl nur noch das
/*N*/             //AppWin genommen werden?
/*N*/             pOut = GetpApp()->GetDefaultDevice();
/*N*/         else
/*N*/             pOut = pNd->GetDoc()->GetPrt(); //Muss es geben (oder sal_True uebergeben?)
/*N*/         pRef = pOut;
/*N*/     }
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/     ChkOutDev( *this );
/*N*/ #endif
/*N*/
/*N*/     // Set default layout mode ( LTR or RTL ).
/*N*/     if ( pFrm->IsRightToLeft() )
/*N*/     {
/*N*/         pOut->SetLayoutMode( TEXT_LAYOUT_BIDI_STRONG | TEXT_LAYOUT_BIDI_RTL );
/*N*/         pRef->SetLayoutMode( TEXT_LAYOUT_BIDI_STRONG | TEXT_LAYOUT_BIDI_RTL );
/*N*/         nDirection = DIR_RIGHT2LEFT;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         pOut->SetLayoutMode( TEXT_LAYOUT_BIDI_STRONG );
/*N*/         pRef->SetLayoutMode( TEXT_LAYOUT_BIDI_STRONG );
/*N*/         nDirection = DIR_LEFT2RIGHT;
/*N*/     }
/*N*/
/*N*/     LanguageType eLang;
/*N*/     const SvtCTLOptions& rCTLOptions = SW_MOD()->GetCTLOptions();
/*N*/     if ( SvtCTLOptions::NUMERALS_HINDI == rCTLOptions.GetCTLTextNumerals() )
/*N*/         eLang = LANGUAGE_ARABIC;
/*N*/     else if ( SvtCTLOptions::NUMERALS_ARABIC == rCTLOptions.GetCTLTextNumerals() )
/*N*/         eLang = LANGUAGE_ENGLISH;
/*N*/     else
/*N*/         eLang = (LanguageType)::binfilter::GetAppLanguage();
/*N*/
/*N*/     pOut->SetDigitLanguage( eLang );
/*N*/     pRef->SetDigitLanguage( eLang );
/*N*/
/*N*/     //
/*N*/     // The Options
/*N*/     //
/*N*/     pOpt = pVsh ?
/*N*/            pVsh->GetViewOptions() :
/*N*/            SW_MOD()->GetViewOption(pNd->GetDoc()->IsHTMLMode()); //Options vom Module wg. StarONE
/*N*/
/*N*/     // bURLNotify wird gesetzt, wenn MakeGraphic dies vorbereitet
/*N*/     // TODO: Aufdröseln
/*N*/     bURLNotify = pNoteURL && !bOnWin;
/*N*/ //    bURLNotify = pNoteURL && !bOnWin
/*N*/ //        && (pOut && OUTDEV_PRINTER != pOut->GetOutDevType());
/*N*/
/*N*/     SetSnapToGrid( pNd->GetSwAttrSet().GetParaGrid().GetValue() &&
/*N*/                    pFrm->IsInDocBody() );
/*N*/
/*N*/     pFnt = pNewFnt;
/*N*/     pUnderFnt = 0;
/*N*/     pTxt = &pNd->GetTxt();
/*N*/
/*N*/   nIdx = nNewIdx;
/*N*/   nLen = nNewLen;
/*N*/   bNotEOL = sal_False;
/*N*/     bStopUnderFlow = bFtnInside = sal_False;
/*N*/   bMulti = bFirstMulti = bRuby = bHanging = bScriptSpace =
/*N*/       bForbiddenChars = sal_False;
/*N*/ #ifndef BIDI
/*N*/     nDirection = DIR_LEFT2RIGHT;
/*N*/ #endif
/*N*/
/*N*/   SetLen( GetMinLen( *this ) );
/*N*/ }

/*N*/ SwTxtSizeInfo::SwTxtSizeInfo( const SwTxtSizeInfo &rNew, const XubString &rTxt,
/*N*/                             const xub_StrLen nIdx, const xub_StrLen nLen )
/*N*/   : SwTxtInfo( rNew ),
/*N*/       pKanaComp(((SwTxtSizeInfo&)rNew).GetpKanaComp()),
/*N*/     pVsh(((SwTxtSizeInfo&)rNew).GetVsh()),
/*N*/     pOut(((SwTxtSizeInfo&)rNew).GetOut()),
/*N*/       pRef(((SwTxtSizeInfo&)rNew).GetRefDev()),
/*N*/     pFnt(((SwTxtSizeInfo&)rNew).GetFont()),
/*N*/       pUnderFnt(((SwTxtSizeInfo&)rNew).GetUnderFnt()),
/*N*/     pFrm( rNew.pFrm ),
/*N*/     pOpt(&rNew.GetOpt()),
/*N*/     pTxt(&rTxt),
/*N*/     nIdx(nIdx),
/*N*/     nLen(nLen),
/*N*/       nKanaIdx( rNew.GetKanaIdx() ),
/*N*/     bOnWin( rNew.OnWin() ),
/*N*/     bNotEOL( rNew.NotEOL() ),
/*N*/     bURLNotify( rNew.URLNotify() ),
/*N*/     bStopUnderFlow( rNew.StopUnderFlow() ),
/*N*/       bFtnInside( rNew.IsFtnInside() ),
/*N*/     bMulti( rNew.IsMulti() ),
/*N*/     bFirstMulti( rNew.IsFirstMulti() ),
/*N*/     bRuby( rNew.IsRuby() ),
/*N*/     bHanging( rNew.IsHanging() ),
/*N*/     bScriptSpace( rNew.HasScriptSpace() ),
/*N*/     bForbiddenChars( rNew.HasForbiddenChars() ),
/*N*/       bSnapToGrid( rNew.SnapToGrid() ),
/*N*/     nDirection( rNew.GetDirection() )
/*N*/ {
/*N*/ #ifndef PRODUCT
/*N*/   ChkOutDev( *this );
/*N*/ #endif
/*N*/   SetLen( GetMinLen( *this ) );
/*N*/ }

/*************************************************************************
 *                      SwTxtSizeInfo::SelectFont()
 *************************************************************************/

/*N*/ void SwTxtSizeInfo::SelectFont()
/*N*/ {
/*N*/   // 8731: Der Weg muss ueber ChgPhysFnt gehen, sonst geraet
/*N*/   // der FontMetricCache durcheinander. In diesem Fall steht pLastMet
/*N*/   // auf dem alten Wert.
/*N*/   // Falsch: GetOut()->SetFont( GetFont()->GetFnt() );
/*N*/   GetFont()->Invalidate();
/*N*/   GetFont()->ChgPhysFnt( pVsh, GetOut() );
/*N*/ }

/*************************************************************************
 *                      SwTxtSizeInfo::NoteAnimation()
 *************************************************************************/

//STRIP001 void SwTxtSizeInfo::NoteAnimation() const
//STRIP001 {
//STRIP001     if( OnWin() )
//STRIP001         SwRootFrm::FlushVout();
//STRIP001
//STRIP001     ASSERT( pOut == pVsh->GetOut(),
//STRIP001             "SwTxtSizeInfo::NoteAnimation() changed pOut" )
//STRIP001 }

/*************************************************************************
 *                      SwTxtSizeInfo::GetTxtSize()
 *************************************************************************/

/*N*/ SwPosSize SwTxtSizeInfo::GetTxtSize( OutputDevice* pOutDev,
/*N*/                                      const SwScriptInfo* pSI,
/*N*/                                      const XubString& rTxt,
/*N*/                                    const xub_StrLen nIdx,
/*N*/                                      const xub_StrLen nLen,
/*N*/                                      const USHORT nComp ) const
/*N*/ {
/*N*/     SwDrawTextInfo aDrawInf( pVsh, *pOutDev, pSI, rTxt, nIdx, nLen );
/*N*/     aDrawInf.SetFrm( pFrm );
/*N*/     aDrawInf.SetFont( pFnt );
/*N*/     aDrawInf.SetSnapToGrid( SnapToGrid() );
/*N*/     aDrawInf.SetKanaComp( nComp );
/*N*/     SwPosSize aSize = pFnt->_GetTxtSize( aDrawInf );
/*N*/     return aSize;
/*N*/ }

/*************************************************************************
 *                      SwTxtSizeInfo::GetTxtSize()
 *************************************************************************/

/*N*/ SwPosSize SwTxtSizeInfo::GetTxtSize() const
/*N*/ {
/*N*/     const SwScriptInfo& rSI =
/*N*/                      ( (SwParaPortion*)GetParaPortion() )->GetScriptInfo();
/*N*/
/*N*/     // in some cases, compression is not allowed or surpressed for
/*N*/     // performance reasons
/*N*/     USHORT nComp =( SW_CJK == GetFont()->GetActual() &&
/*N*/                     rSI.CountCompChg() &&
/*N*/                     ! IsMulti() ) ?
/*N*/                     GetKanaComp() :
/*N*/                                 0 ;
/*N*/
/*N*/     SwDrawTextInfo aDrawInf( pVsh, *pOut, &rSI, *pTxt, nIdx, nLen );
/*N*/     aDrawInf.SetFrm( pFrm );
/*N*/     aDrawInf.SetFont( pFnt );
/*N*/     aDrawInf.SetSnapToGrid( SnapToGrid() );
/*N*/     aDrawInf.SetKanaComp( nComp );
/*N*/     return pFnt->_GetTxtSize( aDrawInf );
/*N*/ }

/*************************************************************************
 *                      SwTxtSizeInfo::GetTxtSize()
 *************************************************************************/

/*N*/ void SwTxtSizeInfo::GetTxtSize( const SwScriptInfo* pSI, const xub_StrLen nIdx,
/*N*/                                 const xub_StrLen nLen, const USHORT nComp,
/*N*/                                 USHORT& nMinSize, USHORT& nMaxSizeDiff ) const
/*N*/ {
/*N*/     SwDrawTextInfo aDrawInf( pVsh, *pOut, pSI, *pTxt, nIdx, nLen );
/*N*/     aDrawInf.SetFrm( pFrm );
/*N*/     aDrawInf.SetFont( pFnt );
/*N*/     aDrawInf.SetSnapToGrid( SnapToGrid() );
/*N*/     aDrawInf.SetKanaComp( nComp );
/*N*/     SwPosSize aSize = pFnt->_GetTxtSize( aDrawInf );
/*N*/     nMaxSizeDiff = (USHORT)aDrawInf.GetKanaDiff();
/*N*/     nMinSize = aSize.Width();
/*N*/ }

/*************************************************************************
 *                      SwTxtSizeInfo::GetTxtBreak()
 *************************************************************************/

//STRIP001 xub_StrLen SwTxtSizeInfo::GetTxtBreak( const long nLineWidth,
//STRIP001                                        const xub_StrLen nMaxLen ) const
//STRIP001 {
//STRIP001     const SwScriptInfo& rSI =
//STRIP001                      ( (SwParaPortion*)GetParaPortion() )->GetScriptInfo();
//STRIP001
//STRIP001     // in some cases, compression is not allowed or surpressed for
//STRIP001     // performance reasons
//STRIP001     USHORT nComp =( SW_CJK == GetFont()->GetActual() &&
//STRIP001                     rSI.CountCompChg() &&
//STRIP001                     ! IsMulti() ) ?
//STRIP001                     GetKanaComp() :
//STRIP001                                 0 ;
//STRIP001
//STRIP001     ASSERT( pRef == pOut, "GetTxtBreak is supposed to use the RefDev" )
//STRIP001     SwDrawTextInfo aDrawInf( pVsh, *pOut, &rSI, *pTxt, nIdx, nMaxLen );
//STRIP001     aDrawInf.SetFrm( pFrm );
//STRIP001     aDrawInf.SetFont( pFnt );
//STRIP001     aDrawInf.SetSnapToGrid( SnapToGrid() );
//STRIP001     aDrawInf.SetKanaComp( nComp );
//STRIP001     aDrawInf.SetHyphPos( 0 );
//STRIP001     return pFnt->GetTxtBreak( aDrawInf, nLineWidth );
//STRIP001 }

/*************************************************************************
 *                      SwTxtSizeInfo::GetTxtBreak()
 *************************************************************************/

/*N*/ xub_StrLen SwTxtSizeInfo::GetTxtBreak( const long nLineWidth,
/*N*/                                        const xub_StrLen nMaxLen,
/*N*/                                        const USHORT nComp ) const
/*N*/ {
/*N*/     const SwScriptInfo& rScriptInfo =
/*N*/                      ( (SwParaPortion*)GetParaPortion() )->GetScriptInfo();
/*N*/
/*N*/     ASSERT( pRef == pOut, "GetTxtBreak is supposed to use the RefDev" )
/*N*/     SwDrawTextInfo aDrawInf( pVsh, *pOut, &rScriptInfo,
/*N*/                              *pTxt, GetIdx(), nMaxLen );
/*N*/     aDrawInf.SetFrm( pFrm );
/*N*/     aDrawInf.SetFont( pFnt );
/*N*/     aDrawInf.SetSnapToGrid( SnapToGrid() );
/*N*/     aDrawInf.SetKanaComp( nComp );
/*N*/     aDrawInf.SetHyphPos( 0 );
/*N*/
/*N*/     return pFnt->GetTxtBreak( aDrawInf, nLineWidth );
/*N*/ }

/*************************************************************************
 *                      SwTxtSizeInfo::GetTxtBreak()
 *************************************************************************/

/*N*/ xub_StrLen SwTxtSizeInfo::GetTxtBreak( const long nLineWidth,
/*N*/                                        const xub_StrLen nMaxLen,
/*N*/                                        const USHORT nComp,
/*N*/                                        xub_StrLen& rExtraCharPos ) const
/*N*/ {
/*N*/     const SwScriptInfo& rScriptInfo =
/*N*/                      ( (SwParaPortion*)GetParaPortion() )->GetScriptInfo();
/*N*/
/*N*/     ASSERT( pRef == pOut, "GetTxtBreak is supposed to use the RefDev" )
/*N*/     SwDrawTextInfo aDrawInf( pVsh, *pOut, &rScriptInfo,
/*N*/                              *pTxt, GetIdx(), nMaxLen );
/*N*/     aDrawInf.SetFrm( pFrm );
/*N*/     aDrawInf.SetFont( pFnt );
/*N*/     aDrawInf.SetSnapToGrid( SnapToGrid() );
/*N*/     aDrawInf.SetKanaComp( nComp );
/*N*/     aDrawInf.SetHyphPos( &rExtraCharPos );
/*N*/
/*N*/     return pFnt->GetTxtBreak( aDrawInf, nLineWidth );
/*N*/ }

/*************************************************************************
 *                     SwTxtPaintInfo::CtorInit()
 *************************************************************************/

/*N*/ void SwTxtPaintInfo::CtorInit( SwTxtFrm *pFrame, const SwRect &rPaint )
/*N*/ {
/*N*/   SwTxtSizeInfo::CtorInit( pFrame );
/*N*/   aTxtFly.CtorInit( pFrame ),
/*N*/   aPaintRect = rPaint;
/*N*/   nSpaceIdx = 0;
/*N*/   pSpaceAdd = NULL;
/*N*/   pWrongList = NULL;
/*N*/ #ifdef PRODUCT
/*N*/   pBrushItem = 0;
/*N*/ #else
/*N*/   pBrushItem = ((SvxBrushItem*)-1);
/*N*/ #endif
/*N*/ }

//STRIP001 SwTxtPaintInfo::SwTxtPaintInfo( const SwTxtPaintInfo &rInf, const XubString &rTxt )
//STRIP001  : SwTxtSizeInfo( rInf, rTxt ),
//STRIP001    aTxtFly( *rInf.GetTxtFly() ),
//STRIP001    aPos( rInf.GetPos() ),
//STRIP001    aPaintRect( rInf.GetPaintRect() ),
//STRIP001    nSpaceIdx( rInf.GetSpaceIdx() ),
//STRIP001    pSpaceAdd( rInf.GetpSpaceAdd() ),
//STRIP001    pWrongList( rInf.GetpWrongList() ),
//STRIP001       pBrushItem( rInf.GetBrushItem() )
//STRIP001 { }

/*N*/ SwTxtPaintInfo::SwTxtPaintInfo( const SwTxtPaintInfo &rInf )
/*N*/   : SwTxtSizeInfo( rInf ),
/*N*/     aTxtFly( *rInf.GetTxtFly() ),
/*N*/     aPos( rInf.GetPos() ),
/*N*/     aPaintRect( rInf.GetPaintRect() ),
/*N*/     nSpaceIdx( rInf.GetSpaceIdx() ),
/*N*/     pSpaceAdd( rInf.GetpSpaceAdd() ),
/*N*/     pWrongList( rInf.GetpWrongList() ),
/*N*/       pBrushItem( rInf.GetBrushItem() )
/*N*/ { }

extern Color aGlobalRetoucheColor;

/*************************************************************************
 *                          lcl_IsDarkBackground
 *
 * Returns if the current background color is dark.
 *************************************************************************/

//STRIP001 sal_Bool lcl_IsDarkBackground( const SwTxtPaintInfo& rInf )
//STRIP001 {
//STRIP001     const Color* pCol = rInf.GetFont()->GetBackColor();
//STRIP001     if( ! pCol || COL_TRANSPARENT == pCol->GetColor() )
//STRIP001     {
//STRIP001         const SvxBrushItem* pItem;
//STRIP001         SwRect aOrigBackRect;
//STRIP001
//STRIP001         /// OD 21.08.2002
//STRIP001         ///     consider, that [GetBackgroundBrush(...)] can set <pCol>
//STRIP001         ///     - see implementation in /core/layout/paintfrm.cxx
//STRIP001         /// OD 21.08.2002 #99657#
//STRIP001         ///     There is a background color, if there is a background brush and
//STRIP001         ///     its color is *not* "no fill"/"auto fill".
//STRIP001         if( rInf.GetTxtFrm()->GetBackgroundBrush( pItem, pCol, aOrigBackRect, FALSE ) )
//STRIP001         {
//STRIP001             if ( !pCol )
//STRIP001                 pCol = &pItem->GetColor();
//STRIP001
//STRIP001             /// OD 30.08.2002 #99657#
//STRIP001             /// determined color <pCol> can be <COL_TRANSPARENT>. Thus, check it.
//STRIP001             if ( pCol->GetColor() == COL_TRANSPARENT)
//STRIP001                 pCol = NULL;
//STRIP001         }
//STRIP001         else
//STRIP001             pCol = NULL;
//STRIP001     }
//STRIP001
//STRIP001
//STRIP001     if( !pCol )
//STRIP001         pCol = &aGlobalRetoucheColor;
//STRIP001
//STRIP001     return pCol->IsDark();
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::_DrawText()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::_DrawText( const XubString &rText, const SwLinePortion &rPor,
//STRIP001                          const xub_StrLen nStart, const xub_StrLen nLen,
//STRIP001                          const sal_Bool bKern, const sal_Bool bWrong )
//STRIP001 {
//STRIP001  if( !nLen )
//STRIP001      return;
//STRIP001     if( GetFont()->IsBlink() && OnWin() && rPor.Width() )
//STRIP001  {
//STRIP001         // check if accessibility options allow blinking portions:
//STRIP001         const ViewShell* pSh = GetTxtFrm()->GetShell();
//STRIP001         if ( pSh && ! pSh->GetAccessibilityOptions()->IsStopAnimatedText() &&
//STRIP001              ! pSh->IsPreView() )
//STRIP001         {
//STRIP001             if( !pBlink )
//STRIP001                 pBlink = new SwBlink();
//STRIP001
//STRIP001          Point aPoint( aPos );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001             if ( GetTxtFrm()->IsRightToLeft() )
//STRIP001                 GetTxtFrm()->SwitchLTRtoRTL( aPoint );
//STRIP001
//STRIP001          if ( TEXT_LAYOUT_BIDI_STRONG != GetOut()->GetLayoutMode() )
//STRIP001                 aPoint.X() -= rPor.Width();
//STRIP001 #endif
//STRIP001
//STRIP001             if ( GetTxtFrm()->IsVertical() )
//STRIP001                 GetTxtFrm()->SwitchHorizontalToVertical( aPoint );
//STRIP001
//STRIP001             pBlink->Insert( aPoint, &rPor, GetTxtFrm(), pFnt->GetOrientation() );
//STRIP001
//STRIP001             if( !pBlink->IsVisible() )
//STRIP001                 return;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             delete pBlink;
//STRIP001             pBlink = NULL;
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  short nSpaceAdd = ( rPor.IsBlankPortion() || rPor.IsDropPortion() ||
//STRIP001                      rPor.InNumberGrp() ) ? 0 : GetSpaceAdd();
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001
//STRIP001     // The SwScriptInfo is useless if we are inside a field portion
//STRIP001     SwScriptInfo* pSI = 0;
//STRIP001     if ( ! rPor.InFldGrp() )
//STRIP001         pSI = &GetParaPortion()->GetScriptInfo();
//STRIP001
//STRIP001     // in some cases, kana compression is not allowed or surpressed for
//STRIP001     // performance reasons
//STRIP001     USHORT nComp = 0;
//STRIP001     if ( ! IsMulti() )
//STRIP001         nComp = GetKanaComp();
//STRIP001
//STRIP001  const sal_Bool bBullet = OnWin() && GetOpt().IsBlank() && IsNoSymbol();
//STRIP001  sal_Bool bTmpWrong = bWrong && OnWin() && GetOpt().IsOnlineSpell()
//STRIP001                           && !GetOpt().IsHideSpell();
//STRIP001     SwParaPortion* pPara = GetParaPortion();
//STRIP001     ASSERT( pPara, "No paragraph!");
//STRIP001     SwDrawTextInfo aDrawInf( pFrm->GetShell(), *pOut, pSI, rText, nStart, nLen,
//STRIP001                              rPor.Width(), bBullet );
//STRIP001
//STRIP001 #else
//STRIP001
//STRIP001     const SwScriptInfo& rSI =
//STRIP001                      ( (SwParaPortion*)GetParaPortion() )->GetScriptInfo();
//STRIP001
//STRIP001     // in some cases, compression is not allowed or surpressed for
//STRIP001     // performance reasons
//STRIP001     USHORT nComp =( SW_CJK == GetFont()->GetActual() &&
//STRIP001                     rSI.CountCompChg() &&
//STRIP001                     ! IsMulti() &&
//STRIP001                     ! rPor.InFldGrp() ) ?
//STRIP001                     GetKanaComp() :
//STRIP001                                 0 ;
//STRIP001
//STRIP001  const sal_Bool bBullet = OnWin() && GetOpt().IsBlank() && IsNoSymbol();
//STRIP001  sal_Bool bTmpWrong = bWrong && OnWin() && GetOpt().IsOnlineSpell()
//STRIP001                           && !GetOpt().IsHideSpell();
//STRIP001     SwParaPortion* pPara = GetParaPortion();
//STRIP001     ASSERT( pPara, "No paragraph!");
//STRIP001     SwDrawTextInfo aDrawInf( pFrm->GetShell(), *pOut, &pPara->GetScriptInfo(),
//STRIP001                              rText, nStart, nLen, rPor.Width(), bBullet );
//STRIP001
//STRIP001 #endif
//STRIP001
//STRIP001  aDrawInf.SetLeft( GetPaintRect().Left() );
//STRIP001  aDrawInf.SetRight( GetPaintRect().Right() );
//STRIP001     aDrawInf.SetUnderFnt( pUnderFnt );
//STRIP001  aDrawInf.SetSpace( nSpaceAdd );
//STRIP001     aDrawInf.SetKanaComp( nComp );
//STRIP001
//STRIP001     // the font is used to identify the current script via nActual
//STRIP001     aDrawInf.SetFont( pFnt );
//STRIP001     // the frame is used to identify the orientation
//STRIP001     aDrawInf.SetFrm( GetTxtFrm() );
//STRIP001     // we have to know if the paragraph should snap to grid
//STRIP001     aDrawInf.SetSnapToGrid( SnapToGrid() );
//STRIP001     // for underlining we must know when not to add extra space behind
//STRIP001     // a character in justified mode
//STRIP001     aDrawInf.SetSpaceStop( ! rPor.GetPortion() ||
//STRIP001                              rPor.GetPortion()->InFixMargGrp() ||
//STRIP001                              rPor.GetPortion()->IsHolePortion() );
//STRIP001
//STRIP001  if( GetTxtFly()->IsOn() )
//STRIP001  {
//STRIP001      // aPos muss als TopLeft vorliegen, weil die ClipRects sonst
//STRIP001      // nicht berechnet werden koennen.
//STRIP001      const Point aPoint( aPos.X(), aPos.Y() - rPor.GetAscent() );
//STRIP001      const Size aSize( rPor.Width(), rPor.Height() );
//STRIP001      aDrawInf.SetFont( pFnt );
//STRIP001      aDrawInf.SetPos( aPoint );
//STRIP001      aDrawInf.SetSize( aSize );
//STRIP001      aDrawInf.SetAscent( rPor.GetAscent() );
//STRIP001      aDrawInf.SetKern( bKern ? rPor.Width() : 0 );
//STRIP001      aDrawInf.SetSpace( nSpaceAdd );
//STRIP001         aDrawInf.SetKanaComp( nComp );
//STRIP001      aDrawInf.SetWrong( bTmpWrong ? pWrongList : NULL );
//STRIP001      GetTxtFly()->DrawTextOpaque( aDrawInf );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aDrawInf.SetPos( aPos );
//STRIP001      if( bKern )
//STRIP001          pFnt->_DrawStretchText( aDrawInf );
//STRIP001      else
//STRIP001      {
//STRIP001          aDrawInf.SetWrong( bTmpWrong ? pWrongList : NULL );
//STRIP001          aDrawInf.SetSpace( nSpaceAdd );
//STRIP001             aDrawInf.SetKanaComp( nComp );
//STRIP001          pFnt->_DrawText( aDrawInf );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                          lcl_CalcRect()
 *************************************************************************/

//STRIP001 void lcl_CalcRect( const SwTxtPaintInfo* pInf, const SwLinePortion& rPor,
//STRIP001                    SwRect* pRect, SwRect* pIntersect )
//STRIP001 {
//STRIP001  Size aSize( rPor.Width(), rPor.Height() );
//STRIP001  if( rPor.IsHangingPortion() )
//STRIP001      aSize.Width() = ((SwHangingPortion&)rPor).GetInnerWidth();
//STRIP001  if( rPor.InSpaceGrp() && pInf->GetSpaceAdd() )
//STRIP001  {
//STRIP001      SwTwips nAdd = rPor.CalcSpacing( pInf->GetSpaceAdd(), *pInf );
//STRIP001      if( rPor.InFldGrp() && pInf->GetSpaceAdd() < 0 && nAdd )
//STRIP001          nAdd += pInf->GetSpaceAdd();
//STRIP001      aSize.Width() += nAdd;
//STRIP001  }
//STRIP001
//STRIP001  Point aPoint;
//STRIP001
//STRIP001     if( pInf->IsRotated() )
//STRIP001  {
//STRIP001      long nTmp = aSize.Width();
//STRIP001      aSize.Width() = aSize.Height();
//STRIP001      aSize.Height() = nTmp;
//STRIP001         if ( 1 == pInf->GetDirection() )
//STRIP001         {
//STRIP001             aPoint.A() = pInf->X() - rPor.GetAscent();
//STRIP001             aPoint.B() = pInf->Y() - aSize.Height();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             aPoint.A() = pInf->X() - rPor.Height() + rPor.GetAscent();
//STRIP001             aPoint.B() = pInf->Y();
//STRIP001         }
//STRIP001     }
//STRIP001  else
//STRIP001  {
//STRIP001         aPoint.A() = pInf->X();
//STRIP001      aPoint.B() = pInf->Y() - rPor.GetAscent();
//STRIP001  }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     // Adjust x coordinate if we are inside a bidi portion
//STRIP001     const BOOL bFrmDir = pInf->GetTxtFrm()->IsRightToLeft();
//STRIP001     BOOL bCounterDir = ( ! bFrmDir && DIR_RIGHT2LEFT == pInf->GetDirection() ) ||
//STRIP001                        (   bFrmDir && DIR_LEFT2RIGHT == pInf->GetDirection() );
//STRIP001
//STRIP001     if ( bCounterDir )
//STRIP001         aPoint.A() -= aSize.Width();
//STRIP001 #endif
//STRIP001
//STRIP001     SwRect aRect( aPoint, aSize );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     if ( pInf->GetTxtFrm()->IsRightToLeft() )
//STRIP001         pInf->GetTxtFrm()->SwitchLTRtoRTL( aRect );
//STRIP001 #endif
//STRIP001
//STRIP001     if ( pInf->GetTxtFrm()->IsVertical() )
//STRIP001         pInf->GetTxtFrm()->SwitchHorizontalToVertical( aRect );
//STRIP001
//STRIP001     if ( pRect )
//STRIP001         *pRect = aRect;
//STRIP001
//STRIP001     if( aRect.HasArea() && pIntersect )
//STRIP001  {
//STRIP001      ::SwAlignRect( aRect, (ViewShell*)pInf->GetVsh() );
//STRIP001
//STRIP001      if ( pInf->GetOut()->IsClipRegion() )
//STRIP001      {
//STRIP001          SwRect aClip( pInf->GetOut()->GetClipRegion().GetBoundRect() );
//STRIP001          aRect.Intersection( aClip );
//STRIP001      }
//STRIP001
//STRIP001         *pIntersect = aRect;
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                          lcl_DrawSpecial
 *
 * Draws a special portion, e.g., line break portion, tab portion.
 * rPor - The portion
 * rRect - The rectangle surrounding the character
 * pCol     - Specify a color for the character
 * bCenter  - Draw the character centered, otherwise left aligned
 * bRotate  - Rotate the character if character rotation is set
 *************************************************************************/

//STRIP001 #ifdef BIDI
//STRIP001 void lcl_DrawSpecial( const SwTxtPaintInfo& rInf, const SwLinePortion& rPor,
//STRIP001                       SwRect& rRect, const Color* pCol, sal_Unicode cChar,
//STRIP001                       BYTE nOptions )
//STRIP001 {
//STRIP001     sal_Bool bCenter = 0 != ( nOptions & DRAW_SPECIAL_OPTIONS_CENTER );
//STRIP001     sal_Bool bRotate = 0 != ( nOptions & DRAW_SPECIAL_OPTIONS_ROTATE );
//STRIP001
//STRIP001     // rRect is given in absolute coordinates
//STRIP001     if ( rInf.GetTxtFrm()->IsRightToLeft() )
//STRIP001         rInf.GetTxtFrm()->SwitchRTLtoLTR( rRect );
//STRIP001 #else
//STRIP001 void lcl_DrawSpecial( const SwTxtPaintInfo& rInf, const SwLinePortion& rPor,
//STRIP001                       SwRect& rRect, const Color* pCol, sal_Unicode cChar,
//STRIP001                       sal_Bool bCenter, sal_Bool bRotate )
//STRIP001 {
//STRIP001 #endif
//STRIP001     if ( rInf.GetTxtFrm()->IsVertical() )
//STRIP001         rInf.GetTxtFrm()->SwitchVerticalToHorizontal( rRect );
//STRIP001
//STRIP001     const SwFont* pOldFnt = rInf.GetFont();
//STRIP001
//STRIP001     // Font is generated only once:
//STRIP001     static SwFont* pFnt = 0;
//STRIP001     if ( ! pFnt )
//STRIP001     {
//STRIP001         pFnt = new SwFont( *pOldFnt );
//STRIP001         pFnt->SetFamily( FAMILY_DONTKNOW, pFnt->GetActual() );
//STRIP001         pFnt->SetName( XubString::CreateFromAscii( sBulletFntName ), pFnt->GetActual() );
//STRIP001         pFnt->SetStyleName( aEmptyStr, pFnt->GetActual() );
//STRIP001         pFnt->SetCharSet( RTL_TEXTENCODING_SYMBOL, pFnt->GetActual() );
//STRIP001     }
//STRIP001
//STRIP001     // Some of the current values are set at the font:
//STRIP001     if ( ! bRotate )
//STRIP001         pFnt->SetVertical( 0, rInf.GetTxtFrm()->IsVertical() );
//STRIP001     else
//STRIP001         pFnt->SetVertical( pOldFnt->GetOrientation() );
//STRIP001
//STRIP001     if ( pCol )
//STRIP001         pFnt->SetColor( *pCol );
//STRIP001     else
//STRIP001         pFnt->SetColor( pOldFnt->GetColor() );
//STRIP001
//STRIP001     Size aFontSize( 0, SPECIAL_FONT_HEIGHT );
//STRIP001     pFnt->SetSize( aFontSize, pFnt->GetActual() );
//STRIP001
//STRIP001     ((SwTxtPaintInfo&)rInf).SetFont( pFnt );
//STRIP001
//STRIP001     // The maximum width depends on the current orientation
//STRIP001     const USHORT nDir = pFnt->GetOrientation( rInf.GetTxtFrm()->IsVertical() );
//STRIP001     SwTwips nMaxWidth;
//STRIP001     switch ( nDir )
//STRIP001     {
//STRIP001     case 0 :
//STRIP001         nMaxWidth = rRect.Width();
//STRIP001         break;
//STRIP001     case 900 :
//STRIP001     case 2700 :
//STRIP001         nMaxWidth = rRect.Height();
//STRIP001         break;
//STRIP001     default:
//STRIP001         ASSERT( sal_False, "Unknown direction set at font" )
//STRIP001         break;
//STRIP001     }
//STRIP001
//STRIP001     // check if char fits into rectangle
//STRIP001     const XubString aTmp( cChar );
//STRIP001     aFontSize = rInf.GetTxtSize( aTmp ).SvLSize();
//STRIP001     while ( aFontSize.Width() > nMaxWidth )
//STRIP001     {
//STRIP001         SwTwips nFactor = ( 100 * aFontSize.Width() ) / nMaxWidth;
//STRIP001         const SwTwips nOldWidth = aFontSize.Width();
//STRIP001
//STRIP001         // new height for font
//STRIP001         const BYTE nAct = pFnt->GetActual();
//STRIP001         aFontSize.Height() = ( 100 * pFnt->GetSize( nAct ).Height() ) / nFactor;
//STRIP001         aFontSize.Width() = ( 100 * pFnt->GetSize( nAct).Width() ) / nFactor;
//STRIP001
//STRIP001         pFnt->SetSize( aFontSize, nAct );
//STRIP001
//STRIP001         aFontSize = rInf.GetTxtSize( aTmp ).SvLSize();
//STRIP001
//STRIP001         if ( aFontSize.Width() >= nOldWidth )
//STRIP001             break;
//STRIP001     }
//STRIP001
//STRIP001     const Point aOldPos( rInf.GetPos() );
//STRIP001
//STRIP001     // adjust values so that tab is vertically and horizontally centered
//STRIP001     SwTwips nX = rRect.Left();
//STRIP001     SwTwips nY = rRect.Top();
//STRIP001     switch ( nDir )
//STRIP001     {
//STRIP001     case 0 :
//STRIP001         if ( bCenter )
//STRIP001             nX += ( rRect.Width() - aFontSize.Width() ) / 2;
//STRIP001         nY += ( rRect.Height() - aFontSize.Height() ) / 2 + rInf.GetAscent();
//STRIP001         break;
//STRIP001     case 900 :
//STRIP001         if ( bCenter )
//STRIP001             nX += ( rRect.Width() - aFontSize.Height() ) / 2 + rInf.GetAscent();
//STRIP001         nY += ( rRect.Height() + aFontSize.Width() ) / 2;
//STRIP001         break;
//STRIP001     case 2700 :
//STRIP001         if ( bCenter )
//STRIP001             nX += ( rRect.Width() + aFontSize.Height() ) / 2 - rInf.GetAscent();
//STRIP001         nY += ( rRect.Height() - aFontSize.Width() ) / 2;
//STRIP001         break;
//STRIP001     }
//STRIP001
//STRIP001     Point aTmpPos( nX, nY );
//STRIP001     ((SwTxtPaintInfo&)rInf).SetPos( aTmpPos );
//STRIP001 #ifdef BIDI
//STRIP001     USHORT nOldWidth = rPor.Width();
//STRIP001     ((SwLinePortion&)rPor).Width( (USHORT)aFontSize.Width() );
//STRIP001     rInf.DrawText( aTmp, rPor );
//STRIP001     ((SwLinePortion&)rPor).Width( nOldWidth );
//STRIP001 #else
//STRIP001     rInf.DrawText( aTmp, rPor );
//STRIP001 #endif
//STRIP001     ((SwTxtPaintInfo&)rInf).SetFont( (SwFont*)pOldFnt );
//STRIP001     ((SwTxtPaintInfo&)rInf).SetPos( aOldPos );
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::DrawRect()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::DrawRect( const SwRect &rRect, sal_Bool bNoGraphic,
//STRIP001                             sal_Bool bRetouche ) const
//STRIP001 {
//STRIP001  if ( OnWin() || !bRetouche )
//STRIP001  {
//STRIP001      if( aTxtFly.IsOn() )
//STRIP001          ((SwTxtPaintInfo*)this)->GetTxtFly()->
//STRIP001              DrawFlyRect( pOut, rRect, *this, bNoGraphic );
//STRIP001      else if ( bNoGraphic )
//STRIP001          pOut->DrawRect( rRect.SVRect() );
//STRIP001      else
//STRIP001      {
//STRIP001          ASSERT( ((SvxBrushItem*)-1) != pBrushItem, "DrawRect: Uninitialized BrushItem!" );
//STRIP001          ::DrawGraphic( pBrushItem, pOut, aItemRect, rRect );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::DrawTab()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::DrawTab( const SwLinePortion &rPor ) const
//STRIP001 {
//STRIP001  if( OnWin() )
//STRIP001  {
//STRIP001         SwRect aRect;
//STRIP001
//STRIP001         lcl_CalcRect( this, rPor, &aRect, 0 );
//STRIP001
//STRIP001         if ( ! aRect.HasArea() )
//STRIP001             return;
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         const sal_Unicode cChar = GetTxtFrm()->IsRightToLeft() ?
//STRIP001                                   CHAR_TAB_RTL : CHAR_TAB;
//STRIP001         const BYTE nOptions = DRAW_SPECIAL_OPTIONS_CENTER |
//STRIP001                               DRAW_SPECIAL_OPTIONS_ROTATE;
//STRIP001         lcl_DrawSpecial( *this, rPor, aRect, 0, cChar, nOptions );
//STRIP001 #else
//STRIP001         lcl_DrawSpecial( *this, rPor, aRect, 0, CHAR_TAB, sal_True, sal_True );
//STRIP001 #endif
//STRIP001
//STRIP001     }
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::DrawLineBreak()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::DrawLineBreak( const SwLinePortion &rPor ) const
//STRIP001 {
//STRIP001  if( OnWin() )
//STRIP001  {
//STRIP001      KSHORT nOldWidth = rPor.Width();
//STRIP001         ((SwLinePortion&)rPor).Width( ((SwBreakPortion&)rPor).GetRestWidth() );
//STRIP001
//STRIP001         SwRect aRect;
//STRIP001
//STRIP001         lcl_CalcRect( this, rPor, &aRect, 0 );
//STRIP001
//STRIP001      if( aRect.HasArea() )
//STRIP001         {
//STRIP001 #ifdef BIDI
//STRIP001             const sal_Unicode cChar = GetTxtFrm()->IsRightToLeft() ?
//STRIP001                                       CHAR_LINEBREAK_RTL : CHAR_LINEBREAK;
//STRIP001             const BYTE nOptions = 0;
//STRIP001             lcl_DrawSpecial( *this, rPor, aRect, 0, cChar, nOptions );
//STRIP001 #else
//STRIP001             lcl_DrawSpecial( *this, rPor, aRect, 0, CHAR_LINEBREAK,
//STRIP001                              sal_False, sal_False );
//STRIP001 #endif
//STRIP001         }
//STRIP001
//STRIP001         ((SwLinePortion&)rPor).Width( nOldWidth );
//STRIP001  }
//STRIP001 }


/*************************************************************************
 *                     SwTxtPaintInfo::DrawRedArrow()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::DrawRedArrow( const SwLinePortion &rPor ) const
//STRIP001 {
//STRIP001     Size aSize( SPECIAL_FONT_HEIGHT, SPECIAL_FONT_HEIGHT );
//STRIP001     SwRect aRect( ((SwArrowPortion&)rPor).GetPos(), aSize );
//STRIP001     sal_Unicode cChar;
//STRIP001     if( ((SwArrowPortion&)rPor).IsLeft() )
//STRIP001  {
//STRIP001      aRect.Pos().Y() += 20 - GetAscent();
//STRIP001      aRect.Pos().X() += 20;
//STRIP001         if( aSize.Height() > rPor.Height() )
//STRIP001             aRect.Height( rPor.Height() );
//STRIP001         cChar = CHAR_LEFT_ARROW;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         if( aSize.Height() > rPor.Height() )
//STRIP001             aRect.Height( rPor.Height() );
//STRIP001      aRect.Pos().Y() -= aRect.Height() + 20;
//STRIP001      aRect.Pos().X() -= aRect.Width() + 20;
//STRIP001         cChar = CHAR_RIGHT_ARROW;
//STRIP001  }
//STRIP001
//STRIP001     if ( GetTxtFrm()->IsVertical() )
//STRIP001         GetTxtFrm()->SwitchHorizontalToVertical( aRect );
//STRIP001
//STRIP001  Color aCol( COL_LIGHTRED );
//STRIP001
//STRIP001     if( aRect.HasArea() )
//STRIP001     {
//STRIP001 #ifdef BIDI
//STRIP001         const BYTE nOptions = 0;
//STRIP001         lcl_DrawSpecial( *this, rPor, aRect, &aCol, cChar, nOptions );
//STRIP001 #else
//STRIP001         lcl_DrawSpecial( *this, rPor, aRect, &aCol, cChar, sal_False, sal_False );
//STRIP001 #endif
//STRIP001     }
//STRIP001 }


/*************************************************************************
 *                     SwTxtPaintInfo::DrawPostIts()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::DrawPostIts( const SwLinePortion &rPor, sal_Bool bScript ) const
//STRIP001 {
//STRIP001  if( OnWin() && pOpt->IsPostIts() )
//STRIP001  {
//STRIP001         Size aSize;
//STRIP001         Point aTmp;
//STRIP001
//STRIP001         const USHORT nPostItsWidth = pOpt->GetPostItsWidth( GetOut() );
//STRIP001         const USHORT nFontHeight = pFnt->GetHeight( pVsh, GetOut() );
//STRIP001         const USHORT nFontAscent = pFnt->GetAscent( pVsh, GetOut() );
//STRIP001
//STRIP001         switch ( pFnt->GetOrientation( GetTxtFrm()->IsVertical() ) )
//STRIP001         {
//STRIP001         case 0 :
//STRIP001             aSize.Width() = nPostItsWidth;
//STRIP001             aSize.Height() = nFontHeight;
//STRIP001             aTmp.X() = aPos.X();
//STRIP001             aTmp.Y() = aPos.Y() - nFontAscent;
//STRIP001             break;
//STRIP001         case 900 :
//STRIP001             aSize.Height() = nPostItsWidth;
//STRIP001             aSize.Width() = nFontHeight;
//STRIP001             aTmp.X() = aPos.X() - nFontAscent;
//STRIP001             aTmp.Y() = aPos.Y();
//STRIP001             break;
//STRIP001         case 2700 :
//STRIP001             aSize.Height() = nPostItsWidth;
//STRIP001             aSize.Width() = nFontHeight;
//STRIP001             aTmp.X() = aPos.X() - nFontHeight +
//STRIP001                                   nFontAscent;
//STRIP001             aTmp.Y() = aPos.Y();
//STRIP001             break;
//STRIP001         }
//STRIP001
//STRIP001         SwRect aTmpRect( aTmp, aSize );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if ( GetTxtFrm()->IsRightToLeft() )
//STRIP001             GetTxtFrm()->SwitchLTRtoRTL( aTmpRect );
//STRIP001 #endif
//STRIP001
//STRIP001         if ( GetTxtFrm()->IsVertical() )
//STRIP001             GetTxtFrm()->SwitchHorizontalToVertical( aTmpRect );
//STRIP001
//STRIP001         const Rectangle aRect( aTmpRect.SVRect() );
//STRIP001         pOpt->PaintPostIts( (OutputDevice*)GetOut(), aRect, bScript );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::DrawBackGround()
 *************************************************************************/
//STRIP001 void SwTxtPaintInfo::DrawBackground( const SwLinePortion &rPor ) const
//STRIP001 {
//STRIP001  ASSERT( OnWin(), "SwTxtPaintInfo::DrawBackground: printer polution ?" );
//STRIP001
//STRIP001     SwRect aIntersect;
//STRIP001
//STRIP001     lcl_CalcRect( this, rPor, 0, &aIntersect );
//STRIP001
//STRIP001     if ( aIntersect.HasArea() )
//STRIP001  {
//STRIP001      OutputDevice *pOut = (OutputDevice*)GetOut();
//STRIP001         sal_Bool bChgColor = sal_False;
//STRIP001
//STRIP001         // For dark background we do not want to have a filled rectangle
//STRIP001         if ( GetVsh() && GetVsh()->GetWin() && lcl_IsDarkBackground( *this ) )
//STRIP001         {
//STRIP001             const StyleSettings& rS = GetVsh()->GetWin()->
//STRIP001                                       GetSettings().GetStyleSettings();
//STRIP001
//STRIP001             Color aCol( SwViewOption::GetFontColor().GetColor() );
//STRIP001             Color aOldColor( pOut->GetLineColor() );
//STRIP001
//STRIP001             if ( 0 != ( bChgColor = aOldColor != aCol ) )
//STRIP001                 pOut->SetLineColor( aCol );
//STRIP001
//STRIP001             DrawRect( aIntersect, sal_True );
//STRIP001
//STRIP001             if ( bChgColor )
//STRIP001                 pOut->SetLineColor( aOldColor );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             Color aCol( SwViewOption::GetFieldShadingsColor() );
//STRIP001             Color aOldColor( pOut->GetFillColor() );
//STRIP001
//STRIP001             if( 0 != ( bChgColor = aOldColor != aCol ) )
//STRIP001                 pOut->SetFillColor( aCol );
//STRIP001
//STRIP001             DrawRect( aIntersect, sal_True );
//STRIP001
//STRIP001             if ( bChgColor )
//STRIP001                 pOut->SetFillColor( aOldColor );
//STRIP001         }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwTxtPaintInfo::_DrawBackBrush( const SwLinePortion &rPor ) const
//STRIP001 {
//STRIP001  ASSERT( pFnt->GetBackColor(), "DrawBackBrush: Lost Color" );
//STRIP001
//STRIP001     SwRect aIntersect;
//STRIP001
//STRIP001     lcl_CalcRect( this, rPor, 0, &aIntersect );
//STRIP001
//STRIP001     if ( aIntersect.HasArea() )
//STRIP001  {
//STRIP001      OutputDevice *pOut = (OutputDevice*)GetOut();
//STRIP001      const Color aOldColor( pOut->GetFillColor() );
//STRIP001      sal_Bool bChgColor;
//STRIP001      if( 0 != ( bChgColor = aOldColor != *pFnt->GetBackColor() ) )
//STRIP001          pOut->SetFillColor( *pFnt->GetBackColor() );
//STRIP001         DrawRect( aIntersect, sal_True, sal_False );
//STRIP001      if( bChgColor )
//STRIP001          pOut->SetFillColor( aOldColor );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::DrawViewOpt()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::DrawViewOpt( const SwLinePortion &rPor,
//STRIP001                                const MSHORT nWhich ) const
//STRIP001 {
//STRIP001  if( OnWin() && !IsMulti() )
//STRIP001  {
//STRIP001      sal_Bool bDraw = sal_False;
//STRIP001      switch( nWhich )
//STRIP001      {
//STRIP001             case POR_FTN:
//STRIP001          case POR_QUOVADIS:
//STRIP001          case POR_NUMBER:
//STRIP001          case POR_FLD:
//STRIP001          case POR_URL:
//STRIP001             case POR_HIDDEN:
//STRIP001             case POR_TOX:
//STRIP001             case POR_REF :
//STRIP001                 if ( !GetOpt().IsPagePreview() &&
//STRIP001                             !GetOpt().IsReadonly() &&\
//STRIP001                             SwViewOption::IsFieldShadings() )
//STRIP001                     bDraw = sal_True;
//STRIP001             break;
//STRIP001          case POR_TAB:       if ( GetOpt().IsTab() )     bDraw = sal_True; break;
//STRIP001          case POR_SOFTHYPH:  if ( GetOpt().IsSoftHyph() )bDraw = sal_True; break;
//STRIP001             case POR_BLANK:     if ( GetOpt().IsHardBlank())bDraw = sal_True; break;
//STRIP001          default:
//STRIP001          {
//STRIP001              ASSERT( !this, "SwTxtPaintInfo::DrawViewOpt: don't know how to draw this" );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bDraw )
//STRIP001          DrawBackground( rPor );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                     SwTxtPaintInfo::_NotifyURL()
 *************************************************************************/

//STRIP001 void SwTxtPaintInfo::_NotifyURL( const SwLinePortion &rPor ) const
//STRIP001 {
//STRIP001  ASSERT( pNoteURL, "NotifyURL: pNoteURL gone with the wind!" );
//STRIP001
//STRIP001     SwRect aIntersect;
//STRIP001
//STRIP001     lcl_CalcRect( this, rPor, 0, &aIntersect );
//STRIP001
//STRIP001     if( aIntersect.HasArea() )
//STRIP001  {
//STRIP001      SwTxtNode *pNd = (SwTxtNode*)GetTxtFrm()->GetTxtNode();
//STRIP001      SwIndex aIndex( pNd, GetIdx() );
//STRIP001      SwTxtAttr *pAttr = pNd->GetTxtAttr( aIndex, RES_TXTATR_INETFMT );
//STRIP001      if( pAttr )
//STRIP001      {
//STRIP001          const SwFmtINetFmt& rFmt = pAttr->GetINetFmt();
//STRIP001          pNoteURL->InsertURLNote( rFmt.GetValue(), rFmt.GetTargetFrame(),
//STRIP001                 aIntersect );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                  lcl_InitHyphValues()
 *************************************************************************/

/*N*/ static void lcl_InitHyphValues( PropertyValues &rVals,
/*N*/           INT16 nMinLeading, INT16 nMinTrailing )
/*N*/ {
/*N*/   INT32 nLen = rVals.getLength();
/*N*/
/*N*/   if (0 == nLen)  // yet to be initialized?
/*N*/   {
/*N*/       rVals.realloc( 2 );
/*N*/       PropertyValue *pVal = rVals.getArray();
/*N*/
/*N*/       pVal[0].Name    = C2U( UPN_HYPH_MIN_LEADING );
/*N*/       pVal[0].Handle  = UPH_HYPH_MIN_LEADING;
/*N*/       pVal[0].Value   <<= nMinLeading;
/*N*/
/*N*/       pVal[1].Name    = C2U( UPN_HYPH_MIN_TRAILING );
/*N*/       pVal[1].Handle  = UPH_HYPH_MIN_TRAILING;
/*N*/       pVal[1].Value   <<= nMinTrailing;
/*N*/   }
/*N*/   else if (2 == nLen) // already initialized once?
/*N*/   {
/*?*/       PropertyValue *pVal = rVals.getArray();
/*?*/       pVal[0].Value <<= nMinLeading;
/*?*/       pVal[1].Value <<= nMinTrailing;
/*?*/   }
/*?*/   else
/*?*/       DBG_ERROR( "unxpected size of sequence" );
/*N*/ }

/*************************************************************************
 *                  SwTxtFormatInfo::GetHyphValues()
 *************************************************************************/
/*N*/
/*N*/ const PropertyValues & SwTxtFormatInfo::GetHyphValues() const
/*N*/ {
/*N*/   DBG_ASSERT( 2 == aHyphVals.getLength(),
/*N*/           "hyphenation values not yet initialized" );
/*N*/   return aHyphVals;
/*N*/ }

/*************************************************************************
 *                  SwTxtFormatInfo::InitHyph()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFormatInfo::InitHyph( const sal_Bool bAutoHyph )
/*N*/ {
/*N*/   const SwAttrSet& rAttrSet = GetTxtFrm()->GetTxtNode()->GetSwAttrSet();
/*N*/   SetHanging( rAttrSet.GetHangingPunctuation().GetValue() );
/*N*/   SetScriptSpace( rAttrSet.GetScriptSpace().GetValue() );
/*N*/   SetForbiddenChars( rAttrSet.GetForbiddenRule().GetValue() );
/*N*/   const SvxHyphenZoneItem &rAttr = rAttrSet.GetHyphenZone();
/*N*/   MaxHyph() = rAttr.GetMaxHyphens();
/*N*/   sal_Bool bAuto = bAutoHyph || rAttr.IsHyphen();
/*N*/   if( bAuto || bInterHyph )
/*N*/   {
/*N*/       nHyphStart = nHyphWrdStart = STRING_LEN;
/*N*/       nHyphWrdLen = 0;
/*N*/
/*N*/       INT16 nMinLeading  = Max(rAttr.GetMinLead(), sal_uInt8(2));
/*N*/       INT16 nMinTrailing = rAttr.GetMinTrail();
/*N*/       lcl_InitHyphValues( aHyphVals, nMinLeading, nMinTrailing);
/*N*/   }
/*N*/   return bAuto;
/*N*/ }

/*************************************************************************
 *                  SwTxtFormatInfo::CtorInit()
 *************************************************************************/

/*N*/ void SwTxtFormatInfo::CtorInit( SwTxtFrm *pNewFrm, const sal_Bool bNewInterHyph,
/*N*/                               const sal_Bool bNewQuick, const sal_Bool bTst )
/*N*/ {
/*N*/   SwTxtPaintInfo::CtorInit( pNewFrm, SwRect() );
/*N*/
/*N*/   bQuick = bNewQuick;
/*N*/   bInterHyph = bNewInterHyph;
/*N*/
/*N*/   //! needs to be done in this order
/*N*/   nMinLeading     = 2;
/*N*/   nMinTrailing    = 2;
/*N*/   nMinWordLength  = 0;
/*N*/   bAutoHyph = InitHyph();
/*N*/
/*N*/   bIgnoreFly = sal_False;
/*N*/     bFakeLineStart = sal_False;
/*N*/   bShift = sal_False;
/*N*/   bDropInit = sal_False;
/*N*/   bTestFormat = bTst;
/*N*/   nLeft = 0;
/*N*/   nRight = 0;
/*N*/   nFirst = 0;
/*N*/   nRealWidth = 0;
/*N*/   nForcedLeftMargin = 0;
/*N*/   pRest = 0;
/*N*/   nLineHeight = 0;
/*N*/     nLineNettoHeight = 0;
/*N*/   SetLineStart(0);
/*N*/   Init();
/*N*/ }

/*************************************************************************
 *                  SwTxtFormatInfo::IsHyphenate()
 *************************************************************************/
// Trennen oder nicht trennen, das ist hier die Frage:
// - in keinem Fall trennen, wenn der Hyphenator ERROR zurueckliefert,
//   oder wenn als Sprache NOLANGUAGE eingestellt ist.
// - ansonsten immer trennen, wenn interaktive Trennung vorliegt
// - wenn keine interakt. Trennung, dann nur trennen, wenn im ParaFmt
//   automatische Trennung eingestellt ist.

/*N*/ sal_Bool SwTxtFormatInfo::IsHyphenate() const
/*N*/ {
/*N*/   if( !bInterHyph && !bAutoHyph )
/*N*/       return sal_False;
/*N*/
/*N*/   LanguageType eTmp = GetFont()->GetLanguage();
/*N*/   if( LANGUAGE_DONTKNOW == eTmp || LANGUAGE_NONE == eTmp )
/*N*/       return sal_False;
/*N*/
/*N*/   uno::Reference< XHyphenator > xHyph = ::binfilter::GetHyphenator();
/*N*/   if (bInterHyph && xHyph.is())
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SvxSpellWrapper::CheckHyphLang( xHyph, eTmp );
/*N*/
/*N*/   if( !xHyph.is() || !xHyph->hasLocale( pBreakIt->GetLocale(eTmp) ) )
/*N*/       return sal_False;
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *                  SwTxtFormatInfo::GetDropFmt()
 *************************************************************************/

// Dropcaps vom SwTxtFormatter::CTOR gerufen.
/*N*/ const SwFmtDrop *SwTxtFormatInfo::GetDropFmt() const
/*N*/ {
/*N*/   const SwFmtDrop *pDrop = &GetTxtFrm()->GetTxtNode()->GetSwAttrSet().GetDrop();
/*N*/   if( 1 >= pDrop->GetLines() ||
/*N*/       ( !pDrop->GetChars() && !pDrop->GetWholeWord() ) )
/*N*/       pDrop = 0;
/*N*/   return pDrop;
/*N*/ }

/*************************************************************************
 *                      SwTxtFormatInfo::Init()
 *************************************************************************/

/*N*/ void SwTxtFormatInfo::Init()
/*N*/ {
/*N*/   // Nicht initialisieren: pRest, nLeft, nRight, nFirst, nRealWidth
/*N*/   X(0);
/*N*/   bArrowDone = bFull = bFtnDone = bErgoDone = bNumDone = bNoEndHyph =
/*N*/       bNoMidHyph = bStop = bNewLine = bUnderFlow = sal_False;
/*N*/
/*N*/     // generally we do not allow number portions in follows, except...
/*N*/     if ( GetTxtFrm()->IsFollow() )
/*N*/     {
/*N*/         const SwTxtFrm* pMaster = GetTxtFrm()->FindMaster();
/*N*/         const SwLinePortion* pPara = pMaster->GetPara();
/*N*/
/*N*/         // there is a master for this follow and the master does not have
/*N*/         // any contents (especially it does not have a number portion)
/*N*/         bNumDone = ! pPara ||
/*N*/                    ! ((SwParaPortion*)pPara)->GetFirstPortion()->IsFlyPortion();
/*N*/     }
/*N*/
/*N*/   pRoot = 0;
/*N*/   pLast = 0;
/*N*/   pFly = 0;
/*N*/   pLastFld = 0;
/*N*/   pLastTab = 0;
/*N*/   pUnderFlow = 0;
/*N*/   cTabDecimal = 0;
/*N*/   nWidth = nRealWidth;
/*N*/   nForcedLeftMargin = 0;
/*N*/   nSoftHyphPos = 0;
/*N*/     nUnderScorePos = STRING_LEN;
/*N*/   cHookChar = 0;
/*N*/   SetIdx(0);
/*N*/   SetLen( GetTxt().Len() );
/*N*/   SetPaintOfst(0);
/*N*/ }

/*-----------------16.10.00 11:39-------------------
 * There are a few differences between a copy constructor
 * and the following constructor for multi-line formatting.
 * The root is the first line inside the multi-portion,
 * the line start is the actual position in the text,
 * the line width is the rest width from the surrounding line
 * and the bMulti and bFirstMulti-flag has to be set correctly.
 * --------------------------------------------------*/

//STRIP001 SwTxtFormatInfo::SwTxtFormatInfo( const SwTxtFormatInfo& rInf,
//STRIP001  SwLineLayout& rLay, SwTwips nActWidth ) : SwTxtPaintInfo( rInf )
//STRIP001 {
//STRIP001  pRoot = &rLay;
//STRIP001  pLast = &rLay;
//STRIP001  pFly = NULL;
//STRIP001  pLastFld = NULL;
//STRIP001  pUnderFlow = NULL;
//STRIP001  pRest = NULL;
//STRIP001  pLastTab = NULL;
//STRIP001
//STRIP001  nSoftHyphPos = 0;
//STRIP001     nUnderScorePos = STRING_LEN;
//STRIP001     nHyphStart = 0;
//STRIP001  nHyphWrdStart = 0;
//STRIP001  nHyphWrdLen = 0;
//STRIP001  nLineStart = rInf.GetIdx();
//STRIP001  nLeft = rInf.nLeft;
//STRIP001  nRight = rInf.nRight;
//STRIP001  nFirst = rInf.nLeft;
//STRIP001  nRealWidth = KSHORT(nActWidth);
//STRIP001  nWidth = nRealWidth;
//STRIP001  nLineHeight = 0;
//STRIP001     nLineNettoHeight = 0;
//STRIP001  nForcedLeftMargin = 0;
//STRIP001
//STRIP001  nMinLeading = 0;
//STRIP001  nMinTrailing = 0;
//STRIP001  nMinWordLength = 0;
//STRIP001  bFull = FALSE;
//STRIP001  bFtnDone = TRUE;
//STRIP001  bErgoDone = TRUE;
//STRIP001  bNumDone = TRUE;
//STRIP001  bStop = FALSE;
//STRIP001  bNewLine = TRUE;
//STRIP001  bShift  = FALSE;
//STRIP001  bUnderFlow = FALSE;
//STRIP001  bInterHyph = FALSE;
//STRIP001  bAutoHyph = FALSE;
//STRIP001  bDropInit = FALSE;
//STRIP001  bQuick  = rInf.bQuick;
//STRIP001  bNoEndHyph  = FALSE;
//STRIP001  bNoMidHyph  = FALSE;
//STRIP001  bIgnoreFly = FALSE;
//STRIP001     bFakeLineStart = FALSE;
//STRIP001
//STRIP001  cTabDecimal = 0;
//STRIP001  cHookChar = 0;
//STRIP001  nMaxHyph = 0;
//STRIP001  bTestFormat = rInf.bTestFormat;
//STRIP001  SetMulti( sal_True );
//STRIP001     SetFirstMulti( rInf.IsFirstMulti() );
//STRIP001 }

/*************************************************************************
 *                 SwTxtFormatInfo::_CheckFtnPortion()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFormatInfo::_CheckFtnPortion( SwLineLayout* pCurr )
/*N*/ {
/*N*/   KSHORT nHeight = pCurr->GetRealHeight();
/*N*/   SwLinePortion *pPor = pCurr->GetPortion();
/*N*/   sal_Bool bRet = sal_False;
/*N*/   while( pPor )
/*N*/   {
/*N*/       if( pPor->IsFtnPortion() && nHeight > ((SwFtnPortion*)pPor)->Orig() )
/*N*/       {
/*?*/           bRet = sal_True;
/*?*/           SetLineHeight( nHeight );
/*?*/             SetLineNettoHeight( pCurr->Height() );
/*?*/           break;
/*N*/       }
/*N*/       pPor = pPor->GetPortion();
/*N*/   }
/*N*/   return bRet;
/*N*/ }




/*************************************************************************
 *                 SwTxtFormatInfo::ScanPortionEnd()
 *************************************************************************/
/*N*/ xub_StrLen SwTxtFormatInfo::ScanPortionEnd( const xub_StrLen nStart,
/*N*/                                             const xub_StrLen nEnd )
/*N*/ {
/*N*/   cHookChar = 0;
/*N*/   const xub_Unicode cTabDec = GetLastTab() ? (sal_Unicode)GetTabDecimal() : 0;
/*N*/   xub_StrLen i = nStart;
/*N*/
/*N*/     // Removed for i7288. bSkip used to be passed from SwFldPortion::Format
/*N*/     // as IsFollow(). Therefore more than one special character was not
/*N*/     // handled correctly at the beginning of follow fields.
/*N*/ //    if ( bSkip && i < nEnd )
/*N*/ //       ++i;
/*N*/
/*N*/   for( ; i < nEnd; ++i )
/*N*/   {
/*N*/       const xub_Unicode cPos = GetChar( i );
/*N*/       switch( cPos )
/*N*/       {
/*N*/       case CH_TXTATR_BREAKWORD:
/*N*/       case CH_TXTATR_INWORD:
/*N*/           if( !HasHint( i ))
/*N*/               break;
/*N*/           // no break;
/*N*/
/*N*/       case CHAR_SOFTHYPHEN:
/*N*/       case CHAR_HARDHYPHEN:
/*N*/       case CHAR_HARDBLANK:
/*N*/       case CH_TAB:
/*N*/       case CH_BREAK:
/*N*/           cHookChar = cPos;
/*N*/           return i;
/*N*/
/*N*/         case CHAR_UNDERSCORE:
/*N*/             if ( STRING_LEN == nUnderScorePos )
/*N*/                 nUnderScorePos = i;
/*N*/             break;
/*N*/
/*N*/         default:
/*N*/           if( cTabDec == cPos )
/*N*/           {
/*N*/               ASSERT( cPos, "Unexspected end of string" );
/*N*/               if( cPos ) // robust
/*N*/               {
/*N*/                   cHookChar = cPos;
/*N*/                   return i;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return i;
/*N*/ }

/*N*/ BOOL SwTxtFormatInfo::LastKernPortion()
/*N*/ {
/*N*/   if( GetLast() )
/*N*/   {
/*N*/       if( GetLast()->IsKernPortion() )
/*N*/           return TRUE;
/*N*/       if( GetLast()->Width() || ( GetLast()->GetLen() &&
/*N*/           !GetLast()->IsHolePortion() ) )
/*N*/           return FALSE;
/*N*/   }
/*N*/   SwLinePortion* pPor = GetRoot();
/*N*/   SwLinePortion *pKern = NULL;
/*N*/   while( pPor )
/*N*/   {
/*N*/       if( pPor->IsKernPortion() )
/*N*/           pKern = pPor;
/*N*/       else if( pPor->Width() || ( pPor->GetLen() && !pPor->IsHolePortion() ) )
/*N*/           pKern = NULL;
/*N*/       pPor = pPor->GetPortion();
/*N*/   }
/*N*/   if( pKern )
/*N*/   {
/*?*/       SetLast( pKern );
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
 *                      class SwTxtSlot
 *************************************************************************/

/*N*/ SwTxtSlot::SwTxtSlot( const SwTxtSizeInfo *pNew, const SwLinePortion *pPor )
/*N*/ {
/*N*/   bOn = pPor->GetExpTxt( *pNew, aTxt );
/*N*/
/*N*/   // Der Text wird ausgetauscht...
/*N*/   if( bOn )
/*N*/   {
/*N*/       pInf = (SwTxtSizeInfo*)pNew;
/*N*/       nIdx = pInf->GetIdx();
/*N*/       nLen = pInf->GetLen();
/*N*/       pInf->SetLen( pPor->GetLen() );
/*N*/       pOldTxt = &(pInf->GetTxt());
/*N*/       pInf->SetTxt( aTxt );
/*N*/       pInf->SetIdx( 0 );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                       SwTxtSlot::~SwTxtSlot()
 *************************************************************************/

/*N*/ SwTxtSlot::~SwTxtSlot()
/*N*/ {
/*N*/   if( bOn )
/*N*/   {
/*N*/       pInf->SetTxt( *pOldTxt );
/*N*/       pInf->SetIdx( nIdx );
/*N*/       pInf->SetLen( nLen );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                      class SwTxtSlotLen
 *************************************************************************/

/*N*/ SwTxtSlotLen::SwTxtSlotLen( const SwTxtSizeInfo *pNew, const SwLinePortion *pPor,
/*N*/   const sal_Char *pCh )
/*N*/ {
/*N*/   if( pCh )
/*N*/   {
/*?*/       aTxt = XubString( pCh, RTL_TEXTENCODING_MS_1252 );
/*?*/       bOn = sal_True;
/*N*/   }
/*N*/   else
/*N*/       bOn = pPor->GetExpTxt( *pNew, aTxt );
/*N*/
/*N*/   // Der Text wird ausgetauscht...
/*N*/   if( bOn )
/*N*/   {
/*N*/       pInf = (SwTxtSizeInfo*)pNew;
/*N*/       nIdx = pInf->GetIdx();
/*N*/       nLen = pInf->GetLen();
/*N*/       pOldTxt = &(pInf->GetTxt());
/*N*/       pInf->SetTxt( aTxt );
/*N*/       pInf->SetIdx( 0 );
/*N*/       pInf->SetLen( pInf->GetTxt().Len() );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                       SwTxtSlotLen::~SwTxtSlotLen()
 *************************************************************************/

/*N*/ SwTxtSlotLen::~SwTxtSlotLen()
/*N*/ {
/*N*/   if( bOn )
/*N*/   {
/*N*/       pInf->SetTxt( *pOldTxt );
/*N*/       pInf->SetIdx( nIdx );
/*N*/       pInf->SetLen( nLen );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                     SwFontSave::SwFontSave()
 *************************************************************************/

/*N*/ SwFontSave::SwFontSave( const SwTxtSizeInfo &rInf, SwFont *pNew,
/*N*/       SwAttrIter* pItr )
/*N*/       : pFnt( pNew ? ((SwTxtSizeInfo&)rInf).GetFont() : 0 )
/*N*/ {
/*N*/   if( pFnt )
/*N*/   {
/*N*/       pInf = &((SwTxtSizeInfo&)rInf);
/*N*/         // In these cases we temporarily switch to the new font:
/*N*/         // 1. the fonts have a different magic number
/*N*/         // 2. they have different script types
/*N*/         // 3. their background colors differ (this is not covered by 1.)
/*N*/       if( pFnt->DifferentMagic( pNew, pFnt->GetActual() ) ||
/*N*/             pNew->GetActual() != pFnt->GetActual() ||
/*N*/             ( ! pNew->GetBackColor() && pFnt->GetBackColor() ) ||
/*N*/             ( pNew->GetBackColor() && ! pFnt->GetBackColor() ) ||
/*N*/             ( pNew->GetBackColor() && pFnt->GetBackColor() &&
/*N*/               ( *pNew->GetBackColor() != *pFnt->GetBackColor() ) ) )
/*N*/       {
/*N*/           pNew->SetTransparent( sal_True );
/*N*/           pNew->SetAlign( ALIGN_BASELINE );
/*N*/           pInf->SetFont( pNew );
/*N*/       }
/*N*/       else
/*N*/           pFnt = 0;
/*N*/       pNew->Invalidate();
/*N*/       pNew->ChgPhysFnt( pInf->GetVsh(), pInf->GetOut() );
/*N*/       if( pItr && pItr->GetFnt() == pFnt )
/*N*/       {
/*?*/           pIter = pItr;
/*?*/           pIter->SetFnt( pNew );
/*N*/       }
/*N*/       else
/*N*/           pIter = NULL;
/*N*/   }
/*N*/ }

/*************************************************************************
 *                     SwFontSave::~SwFontSave()
 *************************************************************************/

/*N*/ SwFontSave::~SwFontSave()
/*N*/ {
/*N*/   if( pFnt )
/*N*/   {
/*N*/       // SwFont zurueckstellen
/*N*/       pFnt->Invalidate();
/*N*/       pInf->SetFont( pFnt );
/*N*/       if( pIter )
/*N*/       {
/*?*/           pIter->SetFnt( pFnt );
/*?*/           pIter->nPos = STRING_LEN;
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
 *                     SwDefFontSave::SwDefFontSave()
 *************************************************************************/

//STRIP001 SwDefFontSave::SwDefFontSave( const SwTxtSizeInfo &rInf )
//STRIP001      : pFnt( ((SwTxtSizeInfo&)rInf).GetFont()  )
//STRIP001 {
//STRIP001  BOOL bAlter = pFnt->GetFixKerning() ||
//STRIP001       ( RTL_TEXTENCODING_SYMBOL == pFnt->GetCharSet(pFnt->GetActual()) )
//STRIP001      ;
//STRIP001
//STRIP001     const sal_Bool bFamily = bAlter && COMPARE_EQUAL !=
//STRIP001             pFnt->GetName( pFnt->GetActual() ).CompareToAscii( sBulletFntName );
//STRIP001     const sal_Bool bRotation = (sal_Bool)pFnt->GetOrientation() &&
//STRIP001                                 ! rInf.GetTxtFrm()->IsVertical();
//STRIP001
//STRIP001     if( bFamily || bRotation )
//STRIP001  {
//STRIP001      pNewFnt = new SwFont( *pFnt );
//STRIP001
//STRIP001         if ( bFamily )
//STRIP001         {
//STRIP001             pNewFnt->SetFamily( FAMILY_DONTKNOW, pFnt->GetActual() );
//STRIP001             pNewFnt->SetName( XubString::CreateFromAscii( sBulletFntName ),
//STRIP001                               pFnt->GetActual() );
//STRIP001             pNewFnt->SetStyleName( aEmptyStr, pFnt->GetActual() );
//STRIP001             pNewFnt->SetCharSet( RTL_TEXTENCODING_SYMBOL, pFnt->GetActual() );
//STRIP001             pNewFnt->SetFixKerning( 0 );
//STRIP001         }
//STRIP001
//STRIP001         if ( bRotation )
//STRIP001             pNewFnt->SetVertical( 0, rInf.GetTxtFrm()->IsVertical() );
//STRIP001
//STRIP001         pInf = &((SwTxtSizeInfo&)rInf);
//STRIP001      pNewFnt->Invalidate();
//STRIP001      pInf->SetFont( pNewFnt );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pFnt = 0;
//STRIP001      pNewFnt = 0;
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                     SwDefFontSave::~SwDefFontSave()
 *************************************************************************/

//STRIP001 SwDefFontSave::~SwDefFontSave()
//STRIP001 {
//STRIP001  if( pFnt )
//STRIP001  {
//STRIP001      delete pNewFnt;
//STRIP001      // SwFont zurueckstellen
//STRIP001      pFnt->Invalidate();
//STRIP001      pInf->SetFont( pFnt );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                  SwTxtFormatInfo::ChgHyph()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFormatInfo::ChgHyph( const sal_Bool bNew )
/*N*/ {
/*N*/   const sal_Bool bOld = bAutoHyph;
/*N*/   if( bAutoHyph != bNew )
/*N*/   {
/*N*/       bAutoHyph = bNew;
/*N*/       InitHyph( bNew );
/*N*/       // 5744: Sprache am Hyphenator einstellen.
/*N*/       if( pFnt )
/*N*/           pFnt->ChgPhysFnt( pVsh, pOut );
/*N*/   }
/*N*/   return bOld;
/*N*/ }


}
