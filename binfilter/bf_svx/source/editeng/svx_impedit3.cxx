/*************************************************************************
 *
 *  $RCSfile: svx_impedit3.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:22:52 $
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

#include <eeng_pch.hxx>

#ifndef _SV_GDIMTF_HXX
#include <vcl/gdimtf.hxx>
#endif

#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>

#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#pragma hdrstop

#include <adjitem.hxx>
#include <tstpitem.hxx>
#include <lspcitem.hxx>

#include <flditem.hxx>

#include <impedit.hxx>
#include <editeng.hxx>
#include <editview.hxx>
#include <txtrange.hxx>
#include <cscoitem.hxx>
#include <colritem.hxx>
#include <udlnitem.hxx>
#include <fhgtitem.hxx>
#include <kernitem.hxx>
#include <lrspitem.hxx>
#include <ulspitem.hxx>
#include <fontitem.hxx>
#include <wghtitem.hxx>
#include <postitem.hxx>
#include <langitem.hxx>
#include <scriptspaceitem.hxx>
#include <charscaleitem.hxx>

#include <svtools/colorcfg.hxx>

#include <forbiddencharacterstable.hxx>

#include <unotools/localedatawrapper.hxx>

#include <unolingu.hxx>

#include <math.h>

#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif

#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif

#ifndef _SV_METRIC_HXX //autogen
#include <vcl/metric.hxx>
#endif

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HPP_
#include <com/sun/star/i18n/ScriptType.hpp>
#endif

#ifndef _COM_SUN_STAR_TEXT_CHARACTERCOMPRESSIONTYPE_HPP_
#include <com/sun/star/text/CharacterCompressionType.hpp>
#endif

#include <comphelper/processfactory.hxx>

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::linguistic2;

/*N*/ SV_DECL_VARARR_SORT( SortedPositions, sal_uInt32, 16, 8 )//STRIP008 ;
/*N*/ SV_IMPL_VARARR_SORT( SortedPositions, sal_uInt32 );

#define CH_HYPH     '-'

#define RESDIFF     10

#define WRONG_SHOW_MIN       5
#define WRONG_SHOW_SMALL    11
#define WRONG_SHOW_MEDIUM   15

struct TabInfo
{
    BOOL        bValid;

    SvxTabStop  aTabStop;
    xub_StrLen  nCharPos;
    USHORT      nTabPortion;
    long        nStartPosX;
    long        nTabPos;

    TabInfo::TabInfo() { bValid = FALSE; }
};

//STRIP001 Point Rotate( const Point& rPoint, short nOrientation, const Point& rOrigin )
//STRIP001 {
//STRIP001  double nRealOrientation = nOrientation*F_PI1800;
//STRIP001  double nCos = cos( nRealOrientation );
//STRIP001  double nSin = sin( nRealOrientation );
//STRIP001
//STRIP001  Point aRotatedPos;
//STRIP001  Point aTranslatedPos( rPoint );
//STRIP001
//STRIP001  // Translation
//STRIP001  aTranslatedPos -= rOrigin;
//STRIP001
//STRIP001  // Rotation...
//STRIP001  aRotatedPos.X() = (long)   ( nCos*aTranslatedPos.X() + nSin*aTranslatedPos.Y() );
//STRIP001  aRotatedPos.Y() = (long) - ( nSin*aTranslatedPos.X() - nCos*aTranslatedPos.Y() );
//STRIP001  aTranslatedPos = aRotatedPos;
//STRIP001
//STRIP001  // Translation...
//STRIP001  aTranslatedPos += rOrigin;
//STRIP001  return aTranslatedPos;
//STRIP001 }

//STRIP001 BYTE GetCharTypeForCompression( xub_Unicode cChar )
//STRIP001 {
//STRIP001     switch ( cChar )
//STRIP001     {
//STRIP001         case 0x3008: case 0x300A: case 0x300C: case 0x300E:
//STRIP001         case 0x3010: case 0x3014: case 0x3016: case 0x3018:
//STRIP001         case 0x301A: case 0x301D:
//STRIP001         {
//STRIP001             return CHAR_PUNCTUATIONRIGHT;
//STRIP001         }
//STRIP001         case 0x3001: case 0x3002: case 0x3009: case 0x300B:
//STRIP001         case 0x300D: case 0x300F: case 0x3011: case 0x3015:
//STRIP001         case 0x3017: case 0x3019: case 0x301B: case 0x301E:
//STRIP001         case 0x301F:
//STRIP001         {
//STRIP001             return CHAR_PUNCTUATIONLEFT;
//STRIP001         }
//STRIP001         default:
//STRIP001         {
//STRIP001             return ( ( 0x3040 <= cChar ) && ( 0x3100 > cChar ) ) ? CHAR_KANA : CHAR_NORMAL;
//STRIP001         }
//STRIP001     }
//STRIP001 }

//STRIP001 void lcl_DrawRedLines( OutputDevice* pOutDev, long nFontHeight, const Point& rPnt, sal_uInt16 nIndex, sal_uInt16 nMaxEnd, const long* pDXArray, WrongList* pWrongs, short nOrientation, const Point& rOrigin, BOOL bVertical )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  // Aber nur, wenn Font nicht zu klein...
//STRIP001  long nHght = pOutDev->LogicToPixel( Size( 0, nFontHeight ) ).Height();
//STRIP001  if( WRONG_SHOW_MIN < nHght )
//STRIP001  {
//STRIP001      sal_uInt16 nStyle;
//STRIP001      if( WRONG_SHOW_MEDIUM < nHght )
//STRIP001          nStyle = WAVE_NORMAL;
//STRIP001      else if( WRONG_SHOW_SMALL < nHght )
//STRIP001          nStyle = WAVE_SMALL;
//STRIP001      else
//STRIP001          nStyle = WAVE_FLAT;
//STRIP001
//STRIP001      sal_uInt16 nEnd, nStart = nIndex;
//STRIP001      sal_Bool bWrong = pWrongs->NextWrong( nStart, nEnd );
//STRIP001      while ( bWrong )
//STRIP001      {
//STRIP001          if ( nStart >= nMaxEnd )
//STRIP001              break;
//STRIP001
//STRIP001          if ( nStart < nIndex )  // Wurde korrigiert
//STRIP001              nStart = nIndex;
//STRIP001          if ( nEnd > nMaxEnd )
//STRIP001              nEnd = nMaxEnd;
//STRIP001          Point aPnt1( rPnt );
//STRIP001          if ( bVertical && ( nStyle != WAVE_FLAT ) )
//STRIP001          {
//STRIP001              // VCL doesn't know that the text is vertical, and is manipulating
//STRIP001              // the positions a little bit in y direction...
//STRIP001              long nOnePixel = pOutDev->PixelToLogic( Size( 0, 1 ) ).Height();
//STRIP001              long nCorrect = ( nStyle == WAVE_NORMAL ) ? 2*nOnePixel : nOnePixel;
//STRIP001              aPnt1.Y() -= nCorrect;
//STRIP001              aPnt1.X() -= nCorrect;
//STRIP001          }
//STRIP001          if ( nStart > nIndex )
//STRIP001          {
//STRIP001              if ( !bVertical )
//STRIP001                  aPnt1.X() += pDXArray[ nStart - nIndex - 1 ];
//STRIP001              else
//STRIP001                  aPnt1.Y() += pDXArray[ nStart - nIndex - 1 ];
//STRIP001          }
//STRIP001          Point aPnt2( rPnt );
//STRIP001          DBG_ASSERT( nEnd > nIndex, "RedLine: aPnt2?" );
//STRIP001          if ( !bVertical )
//STRIP001              aPnt2.X() += pDXArray[ nEnd - nIndex - 1 ];
//STRIP001          else
//STRIP001              aPnt2.Y() += pDXArray[ nEnd - nIndex - 1 ];
//STRIP001          if ( nOrientation )
//STRIP001          {
//STRIP001              aPnt1 = Rotate( aPnt1, nOrientation, rOrigin );
//STRIP001              aPnt2 = Rotate( aPnt2, nOrientation, rOrigin );
//STRIP001          }
//STRIP001
//STRIP001          pOutDev->DrawWaveLine( aPnt1, aPnt2, nStyle );
//STRIP001
//STRIP001          nStart = nEnd+1;
//STRIP001          if ( nEnd < nMaxEnd )
//STRIP001              bWrong = pWrongs->NextWrong( nStart, nEnd );
//STRIP001          else
//STRIP001              bWrong = sal_False;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001 }

//STRIP001 Point lcl_ImplCalcRotatedPos( Point rPos, Point rOrigin, double nSin, double nCos )
//STRIP001 {
//STRIP001  Point aRotatedPos;
//STRIP001  // Translation...
//STRIP001  Point aTranslatedPos( rPos);
//STRIP001  aTranslatedPos -= rOrigin;
//STRIP001
//STRIP001  aRotatedPos.X() = (long)   ( nCos*aTranslatedPos.X() + nSin*aTranslatedPos.Y() );
//STRIP001  aRotatedPos.Y() = (long) - ( nSin*aTranslatedPos.X() - nCos*aTranslatedPos.Y() );
//STRIP001  aTranslatedPos = aRotatedPos;
//STRIP001  // Translation...
//STRIP001  aTranslatedPos += rOrigin;
//STRIP001
//STRIP001  return aTranslatedPos;
//STRIP001 }

//STRIP001 sal_Bool lcl_IsLigature( xub_Unicode cCh, xub_Unicode cNextCh ) // For Kashidas from sw/source/core/text/porlay.txt
//STRIP001 {
//STRIP001             // Lam + Alef
//STRIP001     return ( 0x644 == cCh && 0x627 == cNextCh ) ||
//STRIP001             // Beh + Reh
//STRIP001            ( 0x628 == cCh && 0x631 == cNextCh );
//STRIP001 }

//STRIP001 sal_Bool lcl_ConnectToPrev( xub_Unicode cCh, xub_Unicode cPrevCh )  // For Kashidas from sw/source/core/text/porlay.txt
//STRIP001 {
//STRIP001     // Alef, Dal, Thal, Reh, Zain, and Waw do not connect to the left
//STRIP001     sal_Bool bRet = 0x627 != cPrevCh && 0x62F != cPrevCh && 0x630 != cPrevCh &&
//STRIP001                     0x631 != cPrevCh && 0x632 != cPrevCh && 0x648 != cPrevCh;
//STRIP001
//STRIP001     // check for ligatures cPrevChar + cChar
//STRIP001     if ( bRet )
//STRIP001         bRet = ! lcl_IsLigature( cPrevCh, cCh );
//STRIP001
//STRIP001     return bRet;
//STRIP001 }


// ----------------------------------------------------------------------
//  class ImpEditEngine
//  ----------------------------------------------------------------------
/*N*/ void ImpEditEngine::UpdateViews( EditView* pCurView )
/*N*/ {
/*N*/   if ( !GetUpdateMode() || IsFormatting() || aInvalidRec.IsEmpty() )
/*N*/       return;
/*N*/
/*N*/   DBG_ASSERT( IsFormatted(), "UpdateViews: Doc nicht formatiert!" );
/*N*/
/*N*/   for ( sal_uInt16 nView = 0; nView < aEditViews.Count(); nView++ )
/*N*/   {
/*N*/       EditView* pView = aEditViews[nView];
/*N*/       DBG_CHKOBJ( pView, EditView, 0 );
/*N*/       pView->HideCursor();
/*N*/
/*N*/       Rectangle aClipRec( aInvalidRec );
/*N*/       Rectangle aVisArea( pView->GetVisArea() );
/*N*/       aClipRec.Intersection( aVisArea );
/*N*/
/*N*/       if ( !aClipRec.IsEmpty() )
/*N*/       {
/*N*/           // in Fensterkoordinaten umwandeln....
/*N*/           aClipRec = pView->pImpEditView->GetWindowPos( aClipRec );
/*N*/
/*N*/           if ( ( pView == pCurView )  )
/*N*/               Paint( pView->pImpEditView, aClipRec, sal_True );
/*N*/           else
/*N*/               pView->GetWindow()->Invalidate( aClipRec );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( pCurView )
/*N*/   {
/*N*/       sal_Bool bGotoCursor = pCurView->pImpEditView->DoAutoScroll();
/*N*/       pCurView->ShowCursor( bGotoCursor );
/*N*/   }
/*N*/
/*N*/   aInvalidRec = Rectangle();
/*N*/   CallStatusHdl();
/*N*/ }

/*N*/ IMPL_LINK( ImpEditEngine, OnlineSpellHdl, Timer *, EMPTYARG )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( !Application::AnyInput( INPUT_KEYBOARD ) && GetUpdateMode() && IsFormatted() )
//STRIP001      DoOnlineSpelling();
//STRIP001  else
//STRIP001      aOnlineSpellTimer.Start();
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK_INLINE_START( ImpEditEngine, IdleFormatHdl, Timer *, EMPTYARG )
/*N*/ {
//STRIP001 /*?*/    aIdleFormatter.ResetRestarts();
//STRIP001 /*?*/    FormatAndUpdate( aIdleFormatter.GetView() );
/*N*/   return 0;
/*N*/ }
/*N*/ IMPL_LINK_INLINE_END( ImpEditEngine, IdleFormatHdl, Timer *, EMPTYARG )

/*N*/ void ImpEditEngine::CheckIdleFormatter()
/*N*/ {
/*N*/   aIdleFormatter.ForceTimeout();
/*N*/   // Falls kein Idle, aber trotzdem nicht formatiert:
/*N*/   if ( !IsFormatted() )
/*N*/       FormatDoc();
/*N*/ }

/*N*/ void ImpEditEngine::FormatFullDoc()
/*N*/ {
/*N*/   for ( sal_uInt16 nPortion = 0; nPortion < GetParaPortions().Count(); nPortion++ )
/*N*/       GetParaPortions()[nPortion]->MarkSelectionInvalid( 0, GetParaPortions()[nPortion]->GetNode()->Len() );
/*N*/   FormatDoc();
/*N*/ }

/*N*/ void ImpEditEngine::FormatDoc()
/*N*/ {
/*N*/   if ( !GetUpdateMode() || IsFormatting() )
/*N*/       return;
/*N*/
/*N*/     EnterBlockNotifications();
/*N*/
/*N*/   bIsFormatting = sal_True;
/*N*/
/*N*/   // Dann kann ich auch den Spell-Timer starten...
/*N*/   if ( GetStatus().DoOnlineSpelling() )
/*?*/       StartOnlineSpellTimer();
/*N*/
/*N*/   long nY = 0;
/*N*/   sal_Bool bGrow = sal_False;
/*N*/
/*N*/   Font aOldFont( GetRefDevice()->GetFont() );
/*N*/
/*N*/   // Hier schon, damit nicht jedesmal in CreateLines...
/*N*/   sal_Bool bMapChanged = ImpCheckRefMapMode();
/*N*/
/*N*/   aInvalidRec = Rectangle();  // leermachen
/*N*/   for ( sal_uInt16 nPara = 0; nPara < GetParaPortions().Count(); nPara++ )
/*N*/   {
/*N*/       ParaPortion* pParaPortion = GetParaPortions().GetObject( nPara );
/*N*/       if ( pParaPortion->MustRepaint() || ( pParaPortion->IsInvalid() && pParaPortion->IsVisible() ) )
/*N*/       {
/*N*/           if ( pParaPortion->IsInvalid() )
/*N*/           {
/*N*/               sal_Bool bChangedByDerivedClass = GetEditEnginePtr()->FormattingParagraph( nPara );
/*N*/               if ( bChangedByDerivedClass )
/*N*/               {
/*?*/                   pParaPortion->GetTextPortions().Reset();
/*?*/                   pParaPortion->MarkSelectionInvalid( 0, pParaPortion->GetNode()->Len() );
/*N*/               }
/*N*/           }
/*N*/           // bei MustRepaint() sollte keine Formatierung noetig sein!
/*N*/           // 23.1.95: Evtl. ist sie durch eine andere Aktion aber doch
/*N*/           // ungueltig geworden!
/*N*/ //            if ( pParaPortion->MustRepaint() || CreateLines( nPara ) )
/*N*/           if ( ( pParaPortion->MustRepaint() && !pParaPortion->IsInvalid() )
/*N*/                   || CreateLines( nPara, nY ) )
/*N*/           {
/*N*/               if ( !bGrow && GetTextRanger() )
/*N*/               {
/*?*/                   // Bei einer Aenderung der Hoehe muss alles weiter unten
/*?*/                   // neu formatiert werden...
/*?*/                   for ( sal_uInt16 n = nPara+1; n < GetParaPortions().Count(); n++ )
/*?*/                   {
/*?*/                       ParaPortion* pPP = GetParaPortions().GetObject( n );
/*?*/                       pPP->MarkSelectionInvalid( 0, pPP->GetNode()->Len() );
/*?*/                       pPP->GetLines().Reset();
/*?*/                   }
/*N*/               }
/*N*/               bGrow = sal_True;
/*N*/               if ( IsCallParaInsertedOrDeleted() )
/*N*/                   GetEditEnginePtr()->ParagraphHeightChanged( nPara );
/*N*/               pParaPortion->SetMustRepaint( sal_False );
/*N*/           }
/*N*/
/*N*/           // InvalidRec nur einmal setzen...
/*N*/           if ( aInvalidRec.IsEmpty() )
/*N*/           {
/*N*/               // Bei Paperwidth 0 (AutoPageSize) bleibt es sonst Empty()...
/*N*/               long nWidth = Max( (long)1, ( !IsVertical() ? aPaperSize.Width() : aPaperSize.Height() ) );
/*N*/               Range aInvRange( GetInvalidYOffsets( pParaPortion ) );
/*N*/               aInvalidRec = Rectangle( Point( 0, nY+aInvRange.Min() ),
/*N*/                   Size( nWidth, aInvRange.Len() ) );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               aInvalidRec.Bottom() = nY + pParaPortion->GetHeight();
/*N*/           }
/*N*/       }
/*N*/       else if ( bGrow )
/*N*/       {
/*?*/           aInvalidRec.Bottom() = nY + pParaPortion->GetHeight();
/*N*/       }
/*N*/       nY += pParaPortion->GetHeight();
/*N*/   }
/*N*/
/*N*/   // Man kann auch durch UpdateMode An=>AUS=>AN in die Formatierung gelangen...
/*N*/   // Optimierung erst nach Vobis-Auslieferung aktivieren...
/*N*/ //    if ( !aInvalidRec.IsEmpty() )
/*N*/   {
/*N*/       sal_uInt32 nNewHeight = CalcTextHeight();
/*N*/       long nDiff = nNewHeight - nCurTextHeight;
/*N*/       if ( nDiff )
/*N*/           aStatus.GetStatusWord() |= !IsVertical() ? EE_STAT_TEXTHEIGHTCHANGED : EE_STAT_TEXTWIDTHCHANGED;
/*N*/       if ( nNewHeight < nCurTextHeight )
/*N*/       {
/*N*/           aInvalidRec.Bottom() = (long)Max( nNewHeight, nCurTextHeight );
/*N*/           if ( aInvalidRec.IsEmpty() )
/*N*/           {
/*?*/               aInvalidRec.Top() = 0;
/*?*/               // Left und Right werden nicht ausgewertet, aber wegen IsEmpty gesetzt.
/*?*/               aInvalidRec.Left() = 0;
/*?*/               aInvalidRec.Right() = !IsVertical() ? aPaperSize.Width() : aPaperSize.Height();
/*N*/           }
/*N*/       }
/*N*/
/*N*/       nCurTextHeight = nNewHeight;
/*N*/
/*N*/       if ( aStatus.AutoPageSize() )
/*N*/           CheckAutoPageSize();
/*N*/       else if ( nDiff )
/*N*/       {
/*N*/           for ( sal_uInt16 nView = 0; nView < aEditViews.Count(); nView++ )
/*N*/           {
/*N*/               EditView* pView = aEditViews[nView];
/*N*/               ImpEditView* pImpView = pView->pImpEditView;
/*N*/               if ( pImpView->DoAutoHeight() )
/*N*/               {
/*?*/                   DBG_ASSERT(0, "STRIP"); //STRIP001 Size aSz( pImpView->GetOutputArea().GetWidth(), nCurTextHeight );
//STRIP001 /*?*/                    if ( aSz.Height() > aMaxAutoPaperSize.Height() )
//STRIP001 /*?*/                        aSz.Height() = aMaxAutoPaperSize.Height();
//STRIP001 /*?*/                    else if ( aSz.Height() < aMinAutoPaperSize.Height() )
//STRIP001 /*?*/                        aSz.Height() = aMinAutoPaperSize.Height();
//STRIP001 /*?*/                    pImpView->ResetOutputArea( Rectangle(
//STRIP001 /*?*/                        pImpView->GetOutputArea().TopLeft(), aSz ) );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( aStatus.DoRestoreFont() )
/*?*/       GetRefDevice()->SetFont( aOldFont );
/*N*/   bIsFormatting = sal_False;
/*N*/   bFormatted = sal_True;
/*N*/
/*N*/   if ( bMapChanged )
/*N*/       GetRefDevice()->Pop();
/*N*/
/*N*/   CallStatusHdl();    // Falls Modified...
/*N*/
/*N*/     LeaveBlockNotifications();
/*N*/ }

/*N*/ sal_Bool ImpEditEngine::ImpCheckRefMapMode()
/*N*/ {
/*N*/   sal_Bool bChange = sal_False;
/*N*/
/*N*/   if ( aStatus.DoFormat100() )
/*N*/   {
/*N*/       MapMode aMapMode( GetRefDevice()->GetMapMode() );
/*N*/       if ( aMapMode.GetScaleX().GetNumerator() != aMapMode.GetScaleX().GetDenominator() )
/*N*/           bChange = sal_True;
/*N*/       else if ( aMapMode.GetScaleY().GetNumerator() != aMapMode.GetScaleY().GetDenominator() )
/*N*/           bChange = sal_True;
/*N*/
/*N*/       if ( bChange )
/*N*/       {
/*N*/           Fraction Scale1( 1, 1 );
/*N*/           aMapMode.SetScaleX( Scale1 );
/*N*/           aMapMode.SetScaleY( Scale1 );
/*N*/           GetRefDevice()->Push();
/*N*/           GetRefDevice()->SetMapMode( aMapMode );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bChange;
/*N*/ }

/*N*/ void ImpEditEngine::CheckAutoPageSize()
/*N*/ {
/*N*/   Size aPrevPaperSize( GetPaperSize() );
/*N*/   if ( GetStatus().AutoPageWidth() )
/*N*/       aPaperSize.Width() = (long) !IsVertical() ? CalcTextWidth( TRUE ) : GetTextHeight();
/*N*/   if ( GetStatus().AutoPageHeight() )
/*N*/       aPaperSize.Height() = (long) !IsVertical() ? GetTextHeight() : CalcTextWidth( TRUE );
/*N*/
/*N*/   SetValidPaperSize( aPaperSize );    //Min, Max beruecksichtigen
/*N*/
/*N*/   if ( aPaperSize != aPrevPaperSize )
/*N*/   {
/*N*/       if ( ( !IsVertical() && ( aPaperSize.Width() != aPrevPaperSize.Width() ) )
/*N*/            || ( IsVertical() && ( aPaperSize.Height() != aPrevPaperSize.Height() ) ) )
/*N*/       {
/*N*/           // Falls davor zentriert/rechts oder Tabs...
/*N*/           aStatus.GetStatusWord() |= !IsVertical() ? EE_STAT_TEXTWIDTHCHANGED : EE_STAT_TEXTHEIGHTCHANGED;
/*N*/           for ( sal_uInt16 nPara = 0; nPara < GetParaPortions().Count(); nPara++ )
/*N*/           {
/*N*/               // Es brauchen nur Absaetze neu formatiert werden,
/*N*/               // die nicht linksbuendig sind.
/*N*/               // Die Hoehe kann sich hier nicht mehr aendern.
/*N*/               ParaPortion* pParaPortion = GetParaPortions().GetObject( nPara );
/*N*/               ContentNode* pNode = pParaPortion->GetNode();
/*N*/               SvxAdjust eJustification = GetJustification( nPara );
/*N*/               if ( eJustification != SVX_ADJUST_LEFT )
/*N*/               {
/*N*/                   pParaPortion->MarkSelectionInvalid( 0, pNode->Len() );
/*N*/                   CreateLines( nPara, 0 );    // 0: Bei AutoPageSize kein TextRange!
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       Size aInvSize = aPaperSize;
/*N*/       if ( aPaperSize.Width() < aPrevPaperSize.Width() )
/*?*/           aInvSize.Width() = aPrevPaperSize.Width();
/*N*/       if ( aPaperSize.Height() < aPrevPaperSize.Height() )
/*N*/           aInvSize.Height() = aPrevPaperSize.Height();
/*N*/
/*N*/       Size aSz( aInvSize );
/*N*/       if ( IsVertical() )
/*N*/       {
/*?*/           aSz.Width() = aInvSize.Height();
/*?*/           aSz.Height() = aInvSize.Width();
/*N*/       }
/*N*/       aInvalidRec = Rectangle( Point(), aSz );
/*N*/
/*N*/
/*N*/       for ( sal_uInt16 nView = 0; nView < aEditViews.Count(); nView++ )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 EditView* pView = aEditViews[nView];
//STRIP001 /*?*/            pView->pImpEditView->RecalcOutputArea();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ sal_Bool ImpEditEngine::CreateLines( USHORT nPara, sal_uInt32 nStartPosY )
/*N*/ {
/*N*/   ParaPortion* pParaPortion = GetParaPortions().GetObject( nPara );
/*N*/
/*N*/   // sal_Bool: Aenderung der Hoehe des Absatzes Ja/Nein - sal_True/sal_False
/*N*/   DBG_ASSERT( pParaPortion->GetNode(), "Portion ohne Node in CreateLines" );
/*N*/   DBG_ASSERT( pParaPortion->IsVisible(), "Unsichtbare Absaetze nicht formatieren!" );
/*N*/   DBG_ASSERT( pParaPortion->IsInvalid(), "CreateLines: Portion nicht invalid!" );
/*N*/
/*N*/   BOOL bProcessingEmptyLine = ( pParaPortion->GetNode()->Len() == 0 );
/*N*/   BOOL bEmptyNodeWithPolygon = ( pParaPortion->GetNode()->Len() == 0 ) && GetTextRanger();
/*N*/
/*N*/   // ---------------------------------------------------------------
/*N*/   // Schnelle Sonderbehandlung fuer leere Absaetze...
/*N*/   // ---------------------------------------------------------------
/*N*/   if ( ( pParaPortion->GetNode()->Len() == 0 ) && !GetTextRanger() )
/*N*/   {
/*N*/       // schnelle Sonderbehandlung...
/*N*/       if ( pParaPortion->GetTextPortions().Count() )
/*N*/           pParaPortion->GetTextPortions().Reset();
/*N*/       if ( pParaPortion->GetLines().Count() )
/*N*/           pParaPortion->GetLines().Reset();
/*N*/       CreateAndInsertEmptyLine( pParaPortion, nStartPosY );
/*N*/       return FinishCreateLines( pParaPortion );
/*N*/   }
/*N*/
/*N*/   // ---------------------------------------------------------------
/*N*/   // Initialisierung......
/*N*/   // ---------------------------------------------------------------
/*N*/
/*N*/   // Immer fuer 100% formatieren:
/*N*/   sal_Bool bMapChanged = ImpCheckRefMapMode();
/*N*/
/*N*/   if ( pParaPortion->GetLines().Count() == 0 )
/*N*/   {
/*N*/       EditLine* pL = new EditLine;
/*N*/       pParaPortion->GetLines().Insert( pL, 0 );
/*N*/   }
/*N*/
/*N*/   // ---------------------------------------------------------------
/*N*/   // Absatzattribute holen......
/*N*/   // ---------------------------------------------------------------
/*N*/   ContentNode* const pNode = pParaPortion->GetNode();
/*N*/
/*N*/     BOOL bRightToLeftPara = IsRightToLeft( nPara );
/*N*/
/*N*/     SvxAdjust eJustification = GetJustification( nPara );
/*N*/   sal_Bool bHyphenatePara = ((const SfxBoolItem&)pNode->GetContentAttribs().GetItem( EE_PARA_HYPHENATE )).GetValue();
/*N*/   const SvxLRSpaceItem& rLRItem = GetLRSpaceItem( pNode );
/*N*/   const SvxLineSpacingItem& rLSItem = (const SvxLineSpacingItem&) pNode->GetContentAttribs().GetItem( EE_PARA_SBL );
/*N*/   const BOOL bScriptSpace = ((const SvxScriptSpaceItem&) pNode->GetContentAttribs().GetItem( EE_PARA_ASIANCJKSPACING )).GetValue();
/*N*/
/*N*/ //    const sal_uInt16 nInvalidEnd = ( pParaPortion->GetInvalidDiff() > 0 )
/*N*/ //        ? pParaPortion->GetInvalidPosStart() + pParaPortion->GetInvalidDiff()
/*N*/ //        : pNode->Len();
/*N*/   const short nInvalidDiff = pParaPortion->GetInvalidDiff();
/*N*/   const sal_uInt16 nInvalidStart = pParaPortion->GetInvalidPosStart();
/*N*/   const sal_uInt16 nInvalidEnd =  nInvalidStart + Abs( nInvalidDiff );
/*N*/
/*N*/   sal_Bool bQuickFormat = sal_False;
/*N*/   if ( !bEmptyNodeWithPolygon && !HasScriptType( nPara, i18n::ScriptType::COMPLEX ) )
/*N*/   {
/*N*/       if ( ( pParaPortion->IsSimpleInvalid() ) && ( nInvalidDiff > 0 ) &&
/*N*/            ( pNode->Search( CH_FEATURE, nInvalidStart ) > nInvalidEnd ) )
/*N*/       {
/*N*/           bQuickFormat = sal_True;
/*N*/       }
/*N*/       else if ( ( pParaPortion->IsSimpleInvalid() ) && ( nInvalidDiff < 0 ) )
/*N*/       {
/*?*/           // pruefen, ob loeschen ueber Portiongrenzen erfolgte...
/*?*/           sal_uInt16 nStart = nInvalidStart;  // DOPPELT !!!!!!!!!!!!!!!
/*?*/           sal_uInt16 nEnd = nStart - nInvalidDiff;  // neg.
/*?*/           bQuickFormat = sal_True;
/*?*/           sal_uInt16 nPos = 0;
/*?*/           sal_uInt16 nPortions = pParaPortion->GetTextPortions().Count();
/*?*/           for ( sal_uInt16 nTP = 0; nTP < nPortions; nTP++ )
/*?*/           {
/*?*/               // Es darf kein Start/Ende im geloeschten Bereich liegen.
/*?*/               TextPortion* const pTP = pParaPortion->GetTextPortions()[ nTP ];
/*?*/               nPos += pTP->GetLen();
/*?*/               if ( ( nPos > nStart ) && ( nPos < nEnd ) )
/*?*/               {
/*?*/                   bQuickFormat = sal_False;
/*?*/                   break;
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/     // SW disables TEXT_LAYOUT_COMPLEX_DISABLED, so maybe I have to enable it...
/*N*/     ULONG nOldLayoutMode = GetRefDevice()->GetLayoutMode();
/*N*/
/*N*/     ImplInitLayoutMode( GetRefDevice(), nPara, 0xFFFF );
/*N*/
/*N*/   sal_uInt16 nRealInvalidStart = nInvalidStart;
/*N*/
/*N*/     if ( bEmptyNodeWithPolygon )
/*N*/   {
/*?*/       TextPortion* pDummyPortion = new TextPortion( 0 );
/*?*/       pParaPortion->GetTextPortions().Reset();
/*?*/       pParaPortion->GetTextPortions().Insert( pDummyPortion, 0 );
/*N*/   }
/*N*/   else if ( bQuickFormat )
/*N*/   {
/*N*/       // schnellere Methode:
/*N*/       RecalcTextPortion( pParaPortion, nInvalidStart, nInvalidDiff );
/*N*/   }
/*N*/   else    // nRealInvalidStart kann vor InvalidStart liegen, weil Portions geloescht....
/*N*/     {
/*N*/       CreateTextPortions( pParaPortion, nRealInvalidStart );
/*N*/     }
/*N*/
/*N*/
/*N*/   // ---------------------------------------------------------------
/*N*/   // Zeile mit InvalidPos suchen, eine Zeile davor beginnen...
/*N*/   // Zeilen flaggen => nicht removen !
/*N*/   // ---------------------------------------------------------------
/*N*/
/*N*/   sal_uInt16 nLine = pParaPortion->GetLines().Count()-1;
/*N*/   for ( sal_uInt16 nL = 0; nL <= nLine; nL++ )
/*N*/   {
/*N*/       EditLine* pLine = pParaPortion->GetLines().GetObject( nL );
/*N*/       if ( pLine->GetEnd() > nRealInvalidStart )  // nicht nInvalidStart!
/*N*/       {
/*N*/           nLine = nL;
/*N*/           break;
/*N*/       }
/*N*/       pLine->SetValid();
/*N*/   }
/*N*/   // Eine Zeile davor beginnen...
/*N*/   // Wenn ganz hinten getippt wird, kann sich die Zeile davor nicht aendern.
/*N*/   if ( nLine && ( !pParaPortion->IsSimpleInvalid() || ( nInvalidEnd < pNode->Len() ) || ( nInvalidDiff <= 0 ) ) )
/*N*/       nLine--;
/*N*/
/*N*/   EditLine* pLine = pParaPortion->GetLines().GetObject( nLine );
/*N*/
/*N*/   static Rectangle aZeroArea = Rectangle( Point(), Point() );
/*N*/   Rectangle aBulletArea( aZeroArea );
/*N*/   if ( !nLine )
/*N*/   {
/*N*/       aBulletArea = GetEditEnginePtr()->GetBulletArea( GetParaPortions().GetPos( pParaPortion ) );
/*N*/       if ( aBulletArea.Right() > 0 )
/*N*/           pParaPortion->SetBulletX( (sal_uInt16) GetXValue( aBulletArea.Right() ) );
/*N*/       else
/*N*/           pParaPortion->SetBulletX( 0 ); // Falls Bullet falsch eingestellt.
/*N*/   }
/*N*/
/*N*/   // ---------------------------------------------------------------
/*N*/   // Ab hier alle Zeilen durchformatieren...
/*N*/   // ---------------------------------------------------------------
/*N*/   sal_uInt16 nDelFromLine = 0xFFFF;
/*N*/   sal_Bool bLineBreak = sal_False;
/*N*/
/*N*/   sal_uInt16 nIndex = pLine->GetStart();
/*N*/   EditLine aSaveLine( *pLine );
/*N*/   SvxFont aTmpFont( pNode->GetCharAttribs().GetDefFont() );
/*N*/
/*N*/   sal_Bool bCalcCharPositions = sal_True;
/*N*/   long* pBuf = new long[ pNode->Len() ];
/*N*/
/*N*/   sal_Bool bSameLineAgain = sal_False;    // Fuer TextRanger, wenn sich die Hoehe aendert.
/*N*/   TabInfo aCurrentTab;
/*N*/
/*N*/   BOOL bForceOneRun = bEmptyNodeWithPolygon;
/*N*/     BOOL bCompressedChars = FALSE;
/*N*/
/*N*/   while ( ( nIndex < pNode->Len() ) || bForceOneRun )
/*N*/   {
/*N*/       bForceOneRun = FALSE;
/*N*/
/*N*/       sal_Bool bEOL = sal_False;
/*N*/       sal_Bool bEOC = sal_False;
/*N*/       sal_uInt16 nPortionStart = 0;
/*N*/       sal_uInt16 nPortionEnd = 0;
/*N*/
/*N*/       long nStartX = GetXValue( rLRItem.GetTxtLeft() );
/*N*/       if ( nIndex == 0 )
/*N*/       {
/*N*/           long nFI = GetXValue( rLRItem.GetTxtFirstLineOfst() );
/*N*/           nStartX += nFI;
/*N*/
/*N*/           if ( !nLine && ( pParaPortion->GetBulletX() > nStartX ) )
/*N*/           {
/*N*/               nStartX -= nFI; // Vielleicht reicht der LI?
/*N*/               if ( pParaPortion->GetBulletX() > nStartX )
/*N*/                   nStartX = pParaPortion->GetBulletX();
/*N*/           }
/*N*/       }
/*N*/
/*N*/
/*N*/       long nMaxLineWidth;
/*N*/       if ( !IsVertical() )
/*N*/           nMaxLineWidth = aStatus.AutoPageWidth() ? aMaxAutoPaperSize.Width() : aPaperSize.Width();
/*N*/       else
/*?*/           nMaxLineWidth = aStatus.AutoPageHeight() ? aMaxAutoPaperSize.Height() : aPaperSize.Height();
/*N*/
/*N*/       nMaxLineWidth -= GetXValue( rLRItem.GetRight() );
/*N*/       nMaxLineWidth -= nStartX;
/*N*/
/*N*/       // Wenn PaperSize == long_max, kann ich keinen neg. Erstzeileneinzug
/*N*/       // abziehen (Overflow)
/*N*/       if ( ( nMaxLineWidth < 0 ) && ( nStartX < 0 ) )
/*?*/           nMaxLineWidth = ( !IsVertical() ? aPaperSize.Width() : aPaperSize.Height() ) - GetXValue( rLRItem.GetRight() );
/*N*/
/*N*/       // Wenn jetzt noch kleiner 0, kann es nur der rechte Rand sein.
/*N*/       if ( nMaxLineWidth <= 0 )
/*?*/           nMaxLineWidth = 1;
/*N*/
/*N*/       // Problem: Da eine Zeile _vor_ der ungueltigen Position mit der
/*N*/       // Formatierung begonnen wird, werden hier leider auch die Positionen
/*N*/       // neu bestimmt...
/*N*/       // Loesungsansatz:
/*N*/       // Die Zeile davor kann nur groesser werden, nicht kleiner
/*N*/       // => ...
/*N*/       if ( bCalcCharPositions )
/*N*/           pLine->GetCharPosArray().Remove( 0, pLine->GetCharPosArray().Count() );
/*N*/
/*N*/       sal_uInt16 nTmpPos = nIndex;
/*N*/       sal_uInt16 nTmpPortion = pLine->GetStartPortion();
/*N*/       long nTmpWidth = 0;
/*N*/       long nXWidth = nMaxLineWidth;
/*N*/       if ( nXWidth <= nTmpWidth ) // while muss 1x durchlaufen werden
/*?*/           nXWidth = nTmpWidth+1;
/*N*/
/*N*/       SvLongsPtr pTextRanges = 0;
/*N*/       long nTextExtraYOffset = 0;
/*N*/       long nTextXOffset = 0;
/*N*/       long nTextLineHeight = 0;
/*N*/       if ( GetTextRanger() )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 GetTextRanger()->SetVertical( IsVertical() );
//STRIP001 /*?*/
//STRIP001 /*?*/            long nTextY = nStartPosY + GetEditCursor( pParaPortion, pLine->GetStart() ).Top();
//STRIP001 /*?*/            if ( !bSameLineAgain )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SeekCursor( pNode, nTmpPos+1, aTmpFont );
//STRIP001 /*?*/                aTmpFont.SetPhysFont( GetRefDevice() );
//STRIP001 /*?*/                nTextLineHeight = aTmpFont.GetPhysTxtSize( GetRefDevice(), String() ).Height();
//STRIP001 /*?*/                // Metriken koennen groesser sein
//STRIP001 /*?*/                FormatterFontMetric aTempFormatterMetrics;
//STRIP001 /*?*/                RecalcFormatterFontMetrics( aTempFormatterMetrics, aTmpFont );
//STRIP001 /*?*/                sal_uInt16 nLineHeight = aTempFormatterMetrics.GetHeight();
//STRIP001 /*?*/                if ( nLineHeight > nTextLineHeight )
//STRIP001 /*?*/                    nTextLineHeight = nLineHeight;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nTextLineHeight = pLine->GetHeight();
//STRIP001 /*?*/
//STRIP001 /*?*/            nXWidth = 0;
//STRIP001 /*?*/            while ( !nXWidth )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                long nYOff = nTextY + nTextExtraYOffset;
//STRIP001 /*?*/                long nYDiff = nTextLineHeight;
//STRIP001 /*?*/                if ( IsVertical() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    long nMaxPolygonX = GetTextRanger()->GetBoundRect().Right();
//STRIP001 /*?*/                    nYOff = nMaxPolygonX-nYOff;
//STRIP001 /*?*/                    nYDiff = -nTextLineHeight;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                pTextRanges = GetTextRanger()->GetTextRanges( Range( nYOff, nYOff + nYDiff ) );
//STRIP001 /*?*/                DBG_ASSERT( pTextRanges, "GetTextRanges?!" );
//STRIP001 /*?*/                long nMaxRangeWidth = 0;
//STRIP001 /*?*/                // Den breitesten Bereich verwenden...
//STRIP001 /*?*/                // Der breiteste Bereich koennte etwas verwirren, also
//STRIP001 /*?*/                // generell den ersten. Am besten mal richtig mit Luecken.
//STRIP001 /*?*/ //             for ( sal_uInt16 n = 0; n < pTextRanges->Count(); )
//STRIP001 /*?*/                if ( pTextRanges->Count() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    sal_uInt16 n = 0;
//STRIP001 /*?*/                    long nA = pTextRanges->GetObject( n++ );
//STRIP001 /*?*/                    long nB = pTextRanges->GetObject( n++ );
//STRIP001 /*?*/                    DBG_ASSERT( nA <= nB, "TextRange verdreht?" );
//STRIP001 /*?*/                    long nW = nB - nA;
//STRIP001 /*?*/                    if ( nW > nMaxRangeWidth )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        nMaxRangeWidth = nW;
//STRIP001 /*?*/                        nTextXOffset = nA;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                nXWidth = nMaxRangeWidth;
//STRIP001 /*?*/                if ( nXWidth )
//STRIP001 /*?*/                    nMaxLineWidth = nXWidth - nStartX - GetXValue( rLRItem.GetRight() );
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // Weiter unten im Polygon versuchen.
//STRIP001 /*?*/                    // Unterhalb des Polygons die Paperbreite verwenden.
//STRIP001 /*?*/                    nTextExtraYOffset += Max( (long)(nTextLineHeight / 10), (long)1 );
//STRIP001 /*?*/                    if ( ( nTextY + nTextExtraYOffset  ) > GetTextRanger()->GetBoundRect().Bottom() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        nXWidth = !IsVertical() ? GetPaperSize().Width() : GetPaperSize().Height();
//STRIP001 /*?*/                        if ( !nXWidth ) // AutoPaperSize
//STRIP001 /*?*/                            nXWidth = 0x7FFFFFFF;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*N*/
/*N*/       // Portion suchen, die nicht mehr in Zeile passt....
/*N*/       TextPortion* pPortion;
/*N*/       sal_Bool bBrokenLine = sal_False;
/*N*/       bLineBreak = sal_False;
/*N*/       EditCharAttrib* pNextFeature = pNode->GetCharAttribs().FindFeature( pLine->GetStart() );
/*N*/       while ( ( nTmpWidth < nXWidth ) && !bEOL && ( nTmpPortion < pParaPortion->GetTextPortions().Count() ) )
/*N*/       {
/*N*/           nPortionStart = nTmpPos;
/*N*/           pPortion = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*N*/           if ( pPortion->GetKind() == PORTIONKIND_HYPHENATOR )
/*N*/           {
/*?*/               // Portion wegschmeissen, ggf. die davor korrigieren, wenn
/*?*/               // die Hyph-Portion ein Zeichen geschluckt hat...
/*?*/               pParaPortion->GetTextPortions().Remove( nTmpPortion );
/*?*/               if ( nTmpPortion && pPortion->GetLen() )
/*?*/               {
/*?*/                   nTmpPortion--;
/*?*/                   TextPortion* pPrev = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*?*/                   DBG_ASSERT( pPrev->GetKind() == PORTIONKIND_TEXT, "Portion?!" );
/*?*/                   nTmpWidth -= pPrev->GetSize().Width();
/*?*/                   nTmpPos -= pPrev->GetLen();
/*?*/                   pPrev->SetLen( pPrev->GetLen() + pPortion->GetLen() );
/*?*/                   pPrev->GetSize().Width() = (-1);
/*?*/               }
/*?*/               delete pPortion;
/*?*/               DBG_ASSERT( nTmpPortion < pParaPortion->GetTextPortions().Count(), "Keine Portion mehr da!" );
/*?*/               pPortion = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*N*/           }
/*N*/           DBG_ASSERT( pPortion->GetKind() != PORTIONKIND_HYPHENATOR, "CreateLines: Hyphenator-Portion!" );
/*N*/           DBG_ASSERT( pPortion->GetLen() || bProcessingEmptyLine, "Leere Portion in CreateLines ?!" );
/*N*/           if ( pNextFeature && ( pNextFeature->GetStart() == nTmpPos ) )
/*N*/           {
/*N*/               sal_uInt16 nWhich = pNextFeature->GetItem()->Which();
/*N*/               switch ( nWhich )
/*N*/               {
/*N*/                   case EE_FEATURE_TAB:
/*N*/                   {
/*N*/                       long nOldTmpWidth = nTmpWidth;
/*N*/
/*N*/                       // Tab-Pos suchen...
/*N*/                       long nCurPos = nTmpWidth+nStartX;
/*N*/ //                        nCurPos -= rLRItem.GetTxtLeft();    // Tabs relativ zu LI
/*N*/                       // Skalierung rausrechnen
/*N*/                       if ( aStatus.DoStretch() && ( nStretchX != 100 ) )
/*?*/                           nCurPos = nCurPos*100/nStretchX;
/*N*/
/*N*/                       aCurrentTab.aTabStop = pNode->GetContentAttribs().FindTabStop( nCurPos - rLRItem.GetTxtLeft(), aEditDoc.GetDefTab() );
/*N*/                       aCurrentTab.nTabPos = GetXValue( (long) ( aCurrentTab.aTabStop.GetTabPos() + rLRItem.GetTxtLeft() ) );
/*N*/                       aCurrentTab.bValid = FALSE;
/*N*/
/*N*/                         // Switch direction in R2L para...
/*N*/                         if ( bRightToLeftPara )
/*N*/                         {
/*?*/                             if ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_RIGHT )
/*?*/                                 aCurrentTab.aTabStop.GetAdjustment() = SVX_TAB_ADJUST_LEFT;
/*?*/                             else if ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_LEFT )
/*?*/                                 aCurrentTab.aTabStop.GetAdjustment() = SVX_TAB_ADJUST_RIGHT;
/*N*/                         }
/*N*/
/*N*/                         if ( ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_RIGHT ) ||
/*N*/                            ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_CENTER ) ||
/*N*/                            ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_DECIMAL ) )
/*N*/                       {
/*N*/                           // Bei LEFT/DEFAULT wird dieses Tab nicht mehr betrachtet.
/*N*/                           aCurrentTab.bValid = TRUE;
/*N*/                           aCurrentTab.nStartPosX = nTmpWidth;
/*N*/                           aCurrentTab.nCharPos = nTmpPos;
/*N*/                           aCurrentTab.nTabPortion = nTmpPortion;
/*N*/                       }
/*N*/
/*N*/                       pPortion->GetKind() = PORTIONKIND_TAB;
/*N*/                       pPortion->SetExtraValue( aCurrentTab.aTabStop.GetFill() );
/*N*/                       pPortion->GetSize().Width() = aCurrentTab.nTabPos - (nTmpWidth+nStartX);
/*N*/
/*N*/                         // #90520# Height needed...
/*N*/                         SeekCursor( pNode, nTmpPos+1, aTmpFont );
/*N*/                         pPortion->GetSize().Height() = aTmpFont.QuickGetTextSize( GetRefDevice(), String(), 0, 0, NULL ).Height();
/*N*/
/*N*/                       DBG_ASSERT( pPortion->GetSize().Width() >= 0, "Tab falsch berechnet!" );
/*N*/
/*N*/                       nTmpWidth = aCurrentTab.nTabPos-nStartX;
/*N*/
/*N*/                       // Wenn dies das erste Token in der Zeile ist,
/*N*/                       // und nTmpWidth > aPaperSize.Width, habe ich eine
/*N*/                       // Endlos-Schleife!
/*N*/                       if ( ( nTmpWidth >= nXWidth ) && ( nTmpPortion == pLine->GetStartPortion() ) )
/*N*/                       {
/*?*/                           // Aber was jetzt ?
/*?*/                           // Tab passend machen
/*?*/                           pPortion->GetSize().Width() = nXWidth-nOldTmpWidth;
/*?*/                           nTmpWidth = nXWidth-1;
/*?*/                           bEOL = sal_True;
/*?*/                           bBrokenLine = sal_True;
/*N*/                       }
/*N*/                       pLine->GetCharPosArray().Insert( pPortion->GetSize().Width(), nTmpPos-pLine->GetStart() );
/*N*/                         bCompressedChars = FALSE;
/*N*/                   }
/*N*/                   break;
/*N*/                   case EE_FEATURE_LINEBR:
/*N*/                   {
/*N*/                       DBG_ASSERT( pPortion, "?!" );
/*N*/                       pPortion->GetSize().Width() = 0;
/*N*/                       bEOL = sal_True;
/*N*/                       bLineBreak = sal_True;
/*N*/                       pPortion->GetKind() = PORTIONKIND_LINEBREAK;
/*N*/                         bCompressedChars = FALSE;
/*N*/                       pLine->GetCharPosArray().Insert( pPortion->GetSize().Width(), nTmpPos-pLine->GetStart() );
/*N*/                   }
/*N*/                   break;
/*N*/                   case EE_FEATURE_FIELD:
/*N*/                   {
/*N*/                       long nCurWidth = nTmpWidth;
/*N*/                       SeekCursor( pNode, nTmpPos+1, aTmpFont );
/*N*/                       sal_Unicode cChar = 0;  // later: NBS?
/*N*/                       aTmpFont.SetPhysFont( GetRefDevice() );
/*N*/                       String aFieldValue = cChar ? String(cChar) : ((EditCharAttribField*)pNextFeature)->GetFieldValue();
/*N*/                       if ( bCalcCharPositions || !pPortion->HasValidSize() )
/*N*/                       {
/*N*/                           pPortion->GetSize() = aTmpFont.QuickGetTextSize( GetRefDevice(), aFieldValue, 0, aFieldValue.Len(), 0 );
/*N*/                           // Damit kein Scrollen bei ueberlangen Feldern
/*N*/                           if ( pPortion->GetSize().Width() > nXWidth )
/*?*/                               pPortion->GetSize().Width() = nXWidth;
/*N*/                       }
/*N*/                       nTmpWidth += pPortion->GetSize().Width();
/*N*/                       pLine->GetCharPosArray().Insert( pPortion->GetSize().Width(), nTmpPos-pLine->GetStart() );
/*N*/                       pPortion->GetKind() = cChar ? PORTIONKIND_TEXT : PORTIONKIND_FIELD;
/*N*/                       // Wenn dies das erste Token in der Zeile ist,
/*N*/                       // und nTmpWidth > aPaperSize.Width, habe ich eine
/*N*/                       // Endlos-Schleife!
/*N*/                       if ( ( nTmpWidth >= nXWidth ) && ( nTmpPortion == pLine->GetStartPortion() ) )
/*N*/                       {
/*?*/                           nTmpWidth = nXWidth-1;
/*?*/                           bEOL = sal_True;
/*?*/                           bBrokenLine = sal_True;
/*N*/                       }
/*N*/                         // Compression in Fields????
/*N*/                         // I think this could be a little bit difficult and is not very usefull
/*N*/                         bCompressedChars = FALSE;
/*N*/                   }
/*N*/                   break;
/*N*/                   default:    DBG_ERROR( "Was fuer ein Feature ?" );
/*N*/               }
/*N*/               pNextFeature = pNode->GetCharAttribs().FindFeature( pNextFeature->GetStart() + 1  );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               DBG_ASSERT( pPortion->GetLen() || bProcessingEmptyLine, "Empty Portion - Extra Space?!" );
/*N*/               SeekCursor( pNode, nTmpPos+1, aTmpFont );
/*N*/               aTmpFont.SetPhysFont( GetRefDevice() );
/*N*/               if ( bCalcCharPositions || !pPortion->HasValidSize() )
/*N*/                   pPortion->GetSize() = aTmpFont.QuickGetTextSize( GetRefDevice(), *pParaPortion->GetNode(), nTmpPos, pPortion->GetLen(), pBuf );
/*N*/
/*N*/                 if ( bCalcCharPositions )
/*N*/               {
/*N*/                   sal_uInt16 nLen = pPortion->GetLen();
/*N*/                   // Es wird am Anfang generell das Array geplaettet
/*N*/                   // => Immer einfach schnelles insert.
/*N*/                   sal_uInt16 nPos = nTmpPos - pLine->GetStart();
/*N*/                   pLine->GetCharPosArray().Insert( pBuf, nLen, nPos );
/*N*/               }
/*N*/
/*N*/                 // And now check for Compression:
/*N*/                 if ( pPortion->GetLen() && GetAsianCompressionMode() )
/*?*/                 {DBG_ASSERT(0, "STRIP");} //STRIP001     bCompressedChars |= ImplCalcAsianCompression( pNode, pPortion, nTmpPos, (long*)pLine->GetCharPosArray().GetData() + (nTmpPos-pLine->GetStart()), 10000, FALSE );
/*N*/
/*N*/               nTmpWidth += pPortion->GetSize().Width();
/*N*/
/*N*/                 pPortion->SetRightToLeft( GetRightToLeft( nPara, nTmpPos+1 ) );
/*N*/
/*N*/                 USHORT nPortionEnd = nTmpPos + pPortion->GetLen();
/*N*/                 if( bScriptSpace && ( nPortionEnd < pNode->Len() ) && ( nTmpWidth < nXWidth ) && IsScriptChange( EditPaM( pNode, nPortionEnd ) ) )
/*N*/               {
/*N*/                     BOOL bAllow = FALSE;
/*N*/                     USHORT nScriptTypeLeft = GetScriptType( EditPaM( pNode, nPortionEnd ) );
/*N*/                     USHORT nScriptTypeRight = GetScriptType( EditPaM( pNode, nPortionEnd+1 ) );
/*N*/                     if ( ( nScriptTypeLeft == i18n::ScriptType::ASIAN ) || ( nScriptTypeRight == i18n::ScriptType::ASIAN ) )
/*N*/                         bAllow = TRUE;
/*N*/
/*N*/                     // No spacing within L2R/R2L nesting
/*N*/                     if ( bAllow )
/*N*/                     {
/*?*/                       long nExtraSpace = pPortion->GetSize().Height()/5;
/*?*/                         nExtraSpace = GetXValue( nExtraSpace );
/*?*/                       pPortion->GetSize().Width() += nExtraSpace;
/*?*/                       nTmpWidth += nExtraSpace;
/*N*/                     }
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if ( aCurrentTab.bValid && ( nTmpPortion != aCurrentTab.nTabPortion ) )
/*N*/           {
/*N*/               long nWidthAfterTab = 0;
/*N*/               for ( USHORT n = aCurrentTab.nTabPortion+1; n <= nTmpPortion; n++  )
/*N*/               {
/*N*/                   TextPortion* pTP = pParaPortion->GetTextPortions().GetObject( n );
/*N*/                   nWidthAfterTab += pTP->GetSize().Width();
/*N*/               }
/*N*/               long nW;    // Length before tab position
/*N*/               if ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_RIGHT )
/*N*/                 {
/*N*/                   nW = nWidthAfterTab;
/*N*/                 }
/*N*/               else if ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_CENTER )
/*N*/                 {
/*?*/                   nW = nWidthAfterTab/2;
/*N*/                 }
/*N*/               else if ( aCurrentTab.aTabStop.GetAdjustment() == SVX_TAB_ADJUST_DECIMAL )
/*N*/               {
/*?*/                   nW = nWidthAfterTab;
/*?*/                   String aText = GetSelected( EditSelection(  EditPaM( pParaPortion->GetNode(), nTmpPos ),
/*?*/                                                               EditPaM( pParaPortion->GetNode(), nTmpPos + pPortion->GetLen() ) ) );
/*?*/                   USHORT nDecPos = aText.Search( aCurrentTab.aTabStop.GetDecimal() );
/*?*/                   if ( nDecPos != STRING_NOTFOUND )
/*?*/                   {
/*?*/                       nW -= pParaPortion->GetTextPortions().GetObject( nTmpPortion )->GetSize().Width();
/*?*/                         nW += aTmpFont.QuickGetTextSize( GetRefDevice(), *pParaPortion->GetNode(), nTmpPos, nDecPos, NULL ).Width();
/*?*/                       aCurrentTab.bValid = FALSE;
/*?*/                   }
/*N*/               }
/*N*/                 else
/*N*/                 {
/*N*/                     DBG_ERROR( "CreateLines: Tab not handled!" );
/*N*/                 }
/*N*/               long nMaxW = aCurrentTab.nTabPos - aCurrentTab.nStartPosX - nStartX;
/*N*/               if ( nW >= nMaxW )
/*N*/               {
/*?*/                   nW = nMaxW;
/*?*/                   aCurrentTab.bValid = FALSE;
/*N*/               }
/*N*/               TextPortion* pTabPortion = pParaPortion->GetTextPortions().GetObject( aCurrentTab.nTabPortion );
/*N*/               pTabPortion->GetSize().Width() = aCurrentTab.nTabPos - aCurrentTab.nStartPosX - nW - nStartX;
/*N*/               nTmpWidth = aCurrentTab.nStartPosX + pTabPortion->GetSize().Width() + nWidthAfterTab;
/*N*/           }
/*N*/
/*N*/           nTmpPos += pPortion->GetLen();
/*N*/           nPortionEnd = nTmpPos;
/*N*/           nTmpPortion++;
/*N*/           if ( aStatus.OneCharPerLine() )
/*N*/               bEOL = sal_True;
/*N*/       }
/*N*/
/*N*/       aCurrentTab.bValid = FALSE;
/*N*/
/*N*/       // das war evtl. eine Portion zu weit:
/*N*/       sal_Bool bFixedEnd = sal_False;
/*N*/       if ( aStatus.OneCharPerLine() )
/*N*/       {
/*?*/           // Zustand vor Portion: ( bis auf nTmpWidth )
/*?*/           nPortionEnd = nTmpPos;
/*?*/           nTmpPos -= pPortion->GetLen();
/*?*/           nPortionStart = nTmpPos;
/*?*/           nTmpPortion--;
/*?*/
/*?*/           bEOL = sal_True;
/*?*/           bEOC = sal_False;
/*?*/
/*?*/           // Und jetzt genau ein Zeichen:
/*?*/           nTmpPos++;
/*?*/           nTmpPortion++;
/*?*/           nPortionEnd = nTmpPortion;
/*?*/           // Eine Nicht-Feature-Portion muss gebrochen werden
/*?*/           if ( pPortion->GetLen() > 1 )
/*?*/           {
/*?*/               DBG_ASSERT( pPortion->GetKind() == PORTIONKIND_TEXT, "Len>1, aber keine TextPortion?" );
/*?*/               nTmpWidth -= pPortion->GetSize().Width();
/*?*/               sal_uInt16 nP = SplitTextPortion( pParaPortion, nTmpPos, pLine );
/*?*/               TextPortion* p = pParaPortion->GetTextPortions().GetObject( nP );
/*?*/               DBG_ASSERT( p, "Portion ?!" );
/*?*/               nTmpWidth += p->GetSize().Width();
/*?*/           }
/*N*/       }
/*N*/       else if ( nTmpWidth >= nXWidth )
/*N*/       {
/*N*/           nPortionEnd = nTmpPos;
/*N*/           nTmpPos -= pPortion->GetLen();
/*N*/           nPortionStart = nTmpPos;
/*N*/           nTmpPortion--;
/*N*/           bEOL = sal_False;
/*N*/           bEOC = sal_False;
/*N*/           switch ( pPortion->GetKind() )
/*N*/           {
/*N*/               case PORTIONKIND_TEXT:
/*N*/               {
/*N*/                   nTmpWidth -= pPortion->GetSize().Width();
/*N*/               }
/*N*/               break;
/*N*/               case PORTIONKIND_FIELD:
/*N*/               case PORTIONKIND_TAB:
/*N*/               {
/*?*/                   nTmpWidth -= pPortion->GetSize().Width();
/*?*/                   bEOL = sal_True;
/*?*/                   bFixedEnd = sal_True;
/*N*/               }
/*N*/               break;
/*N*/               default:
/*N*/               {
/*?*/                   // Ein Feature wird nicht umgebrochen:
/*?*/                   DBG_ASSERT( ( pPortion->GetKind() == PORTIONKIND_LINEBREAK ), "Was fuer ein Feature ?" );
/*?*/                   bEOL = sal_True;
/*?*/                   bFixedEnd = sal_True;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           bEOL = sal_True;
/*N*/           bEOC = sal_True;
/*N*/           pLine->SetEnd( nPortionEnd );
/*N*/           DBG_ASSERT( pParaPortion->GetTextPortions().Count(), "Keine TextPortions?" );
/*N*/           pLine->SetEndPortion( (sal_uInt16)pParaPortion->GetTextPortions().Count() - 1 );
/*N*/       }
/*N*/
/*N*/       if ( aStatus.OneCharPerLine() )
/*N*/       {
/*?*/           pLine->SetEnd( nPortionEnd );
/*?*/           pLine->SetEndPortion( nTmpPortion-1 );
/*N*/       }
/*N*/       else if ( bFixedEnd )
/*N*/       {
/*N*/           pLine->SetEnd( nPortionStart );
/*N*/           pLine->SetEndPortion( nTmpPortion-1 );
/*N*/       }
/*N*/       else if ( bLineBreak || bBrokenLine )
/*N*/       {
/*N*/           pLine->SetEnd( nPortionStart+1 );
/*N*/           pLine->SetEndPortion( nTmpPortion-1 );
/*N*/           bEOC = sal_False; // wurde oben gesetzt, vielleich mal die if's umstellen?
/*N*/       }
/*N*/       else if ( !bEOL )
/*N*/       {
/*N*/           DBG_ASSERT( (nPortionEnd-nPortionStart) == pPortion->GetLen(), "Doch eine andere Portion?!" );
/*N*/           long nRemainingWidth = nMaxLineWidth - nTmpWidth;
/*N*/           sal_Bool bCanHyphenate = ( aTmpFont.GetCharSet() != RTL_TEXTENCODING_SYMBOL );
/*N*/             if ( bCompressedChars && ( pPortion->GetLen() > 1 ) && pPortion->GetExtraInfos() && pPortion->GetExtraInfos()->bCompressed )
/*N*/             {
/*?*/                 // I need the manipulated DXArray for determining the break postion...
/*?*/                 DBG_ASSERT(0, "STRIP"); //STRIP001 ImplCalcAsianCompression( pNode, pPortion, nPortionStart, (long*)pLine->GetCharPosArray().GetData() + (nPortionStart-pLine->GetStart()), 10000, TRUE );
/*N*/             }
/*N*/           ImpBreakLine( pParaPortion, pLine, pPortion, nPortionStart,
/*N*/                                           nRemainingWidth, bCanHyphenate && bHyphenatePara );
/*N*/       }
/*N*/
/*N*/       // ------------------------------------------------------------------
/*N*/       // Zeile fertig => justieren
/*N*/       // ------------------------------------------------------------------
/*N*/
/*N*/       // CalcTextSize sollte besser durch ein kontinuierliches
/*N*/       // Registrieren ersetzt werden !
/*N*/       Size aTextSize = pLine->CalcTextSize( *pParaPortion );
/*N*/
/*N*/       if ( aTextSize.Height() == 0 )
/*N*/       {
/*?*/           SeekCursor( pNode, pLine->GetStart()+1, aTmpFont );
/*?*/           aTmpFont.SetPhysFont( pRefDev );
/*?*/           aTextSize.Height() = aTmpFont.GetPhysTxtSize( pRefDev, String() ).Height();
/*?*/           pLine->SetHeight( (sal_uInt16)aTextSize.Height() );
/*N*/       }
/*N*/
/*N*/
/*N*/       // Die Fontmetriken koennen nicht kontinuierlich berechnet werden,
/*N*/       // wenn der Font sowieso eingestellt ist, weil ggf. ein grosser Font
/*N*/       // erst nach dem Umbrechen ploetzlich in der naechsten Zeile landet
/*N*/       // => Font-Metriken zu gross.
/*N*/       FormatterFontMetric aFormatterMetrics;
/*N*/       sal_uInt16 nTPos = pLine->GetStart();
/*N*/       for ( sal_uInt16 nP = pLine->GetStartPortion(); nP <= pLine->GetEndPortion(); nP++ )
/*N*/       {
/*N*/           TextPortion* pTP = pParaPortion->GetTextPortions().GetObject( nP );
/*N*/             // #95819# problem with hard font height attribute, when everthing but the line break has this attribute
/*N*/             if ( pTP->GetKind() != PORTIONKIND_LINEBREAK )
/*N*/             {
/*N*/               SeekCursor( pNode, nTPos+1, aTmpFont );
/*N*/               aTmpFont.SetPhysFont( GetRefDevice() );
/*N*/               RecalcFormatterFontMetrics( aFormatterMetrics, aTmpFont );
/*N*/             }
/*N*/           nTPos += pTP->GetLen();
/*N*/       }
/*N*/       sal_uInt16 nLineHeight = aFormatterMetrics.GetHeight();
/*N*/       if ( nLineHeight > pLine->GetHeight() )
/*N*/           pLine->SetHeight( nLineHeight );
/*N*/       pLine->SetMaxAscent( aFormatterMetrics.nMaxAscent );
/*N*/
/*N*/       bSameLineAgain = sal_False;
/*N*/       if ( GetTextRanger() && ( pLine->GetHeight() > nTextLineHeight ) )
/*N*/       {
/*N*/           // Nochmal mit der anderen Groesse aufsetzen!
/*?*/           bSameLineAgain = sal_True;
/*N*/       }
/*N*/
/*N*/
/*N*/       if ( !aStatus.IsOutliner() )
/*N*/       {
/*N*/           if ( rLSItem.GetLineSpaceRule() == SVX_LINE_SPACE_MIN )
/*N*/           {
/*?*/               sal_uInt16 nMinHeight = GetYValue( rLSItem.GetLineHeight() );
/*?*/               sal_uInt16 nTxtHeight = pLine->GetHeight();
/*?*/               if ( nTxtHeight < nMinHeight )
/*?*/               {
/*?*/                   // Der Ascent muss um die Differenz angepasst werden:
/*?*/                   long nDiff = nMinHeight - nTxtHeight;
/*?*/                   pLine->SetMaxAscent( (sal_uInt16)(pLine->GetMaxAscent() + nDiff) );
/*?*/                   pLine->SetHeight( nMinHeight, nTxtHeight );
/*?*/               }
/*N*/           }
/*N*/           else if ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_PROP )
/*N*/           {
/*N*/               if ( nPara || ( pLine->GetStartPortion() != 0 ) ) // Nicht die aller erste Zeile
/*N*/               {
/*N*/                     // #100508# There are documents with PropLineSpace 0, why?
/*N*/                     if ( rLSItem.GetPropLineSpace() && ( rLSItem.GetPropLineSpace() != 100 ) )
/*N*/                     {
/*N*/                       sal_uInt16 nTxtHeight = pLine->GetHeight();
/*N*/                       sal_uInt32 nH = nTxtHeight;
/*N*/                       nH *= rLSItem.GetPropLineSpace();
/*N*/                       nH /= 100;
/*N*/                       // Der Ascent muss um die Differenz angepasst werden:
/*N*/                       long nDiff = pLine->GetHeight() - nH;
/*N*/                       if ( nDiff > pLine->GetMaxAscent() )
/*?*/                           nDiff = pLine->GetMaxAscent();
/*N*/                       pLine->SetMaxAscent( (sal_uInt16)(pLine->GetMaxAscent() - nDiff) );
/*N*/                       pLine->SetHeight( (sal_uInt16)nH, nTxtHeight );
/*N*/                     }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/
/*N*/       // #80582# - Bullet should not influence line height
/*N*/ //        if ( !nLine )
/*N*/ //        {
/*N*/ //            long nBulletHeight = aBulletArea.GetHeight();
/*N*/ //            if ( nBulletHeight > (long)pLine->GetHeight() )
/*N*/ //            {
/*N*/ //                long nDiff =  nBulletHeight - (long)pLine->GetHeight();
/*N*/ //                // nDiff auf oben und unten verteilen.
/*N*/ //                pLine->SetMaxAscent( (sal_uInt16)(pLine->GetMaxAscent() + nDiff/2) );
/*N*/ //                pLine->SetHeight( (sal_uInt16)nBulletHeight );
/*N*/ //            }
/*N*/ //        }
/*N*/
/*N*/       if ( ( !IsVertical() && aStatus.AutoPageWidth() ) ||
/*N*/            ( IsVertical() && aStatus.AutoPageHeight() ) )
/*N*/       {
/*N*/           // Wenn die Zeile in die aktuelle Papierbreite passt, muss
/*N*/           // diese Breite fuer die Ausrichting verwendet werden.
/*N*/           // Wenn sie nicht passt oder sie die Papierbreite aendert,
/*N*/           // wird bei Justification != LEFT sowieso noch mal formatiert.
/*N*/           long nMaxLineWidthFix = ( !IsVertical() ? aPaperSize.Width() : aPaperSize.Height() )
/*N*/                                       - GetXValue( rLRItem.GetRight() ) - nStartX;
/*N*/           if ( aTextSize.Width() < nMaxLineWidthFix )
/*N*/               nMaxLineWidth = nMaxLineWidthFix;
/*N*/       }
/*N*/
/*N*/         if ( bCompressedChars )
/*N*/         {
/*?*/             long nRemainingWidth = nMaxLineWidth - aTextSize.Width();
/*?*/             if ( nRemainingWidth > 0 )
/*?*/             {
/*?*/                 DBG_ASSERT(0, "STRIP"); //STRIP001 ImplExpandCompressedPortions( pLine, pParaPortion, nRemainingWidth );
//STRIP001 /*?*/                 aTextSize = pLine->CalcTextSize( *pParaPortion );
/*?*/             }
/*N*/         }
/*N*/
/*N*/         if ( pLine->IsHangingPunctuation() )
/*N*/       {
/*?*/           // Width from HangingPunctuation was set to 0 in ImpBreakLine,
/*?*/           // check for rel width now, maybe create compression...
/*?*/           long n = nMaxLineWidth - aTextSize.Width();
/*?*/           TextPortion* pTP = pParaPortion->GetTextPortions().GetObject( pLine->GetEndPortion() );
/*?*/           sal_uInt16 nPosInArray = pLine->GetEnd()-1-pLine->GetStart();
/*?*/           long nNewValue = ( nPosInArray ? pLine->GetCharPosArray()[ nPosInArray-1 ] : 0 ) + n;
/*?*/           pLine->GetCharPosArray()[ nPosInArray ] = nNewValue;
/*?*/           pTP->GetSize().Width() += n;
/*N*/       }
/*N*/
/*N*/         pLine->SetTextWidth( aTextSize.Width() );
/*N*/         switch ( eJustification )
/*N*/       {
/*N*/           case SVX_ADJUST_CENTER:
/*N*/           {
/*N*/               long n = ( nMaxLineWidth - aTextSize.Width() ) / 2;
/*N*/               n += nStartX;  // Einrueckung bleibt erhalten.
/*N*/               if ( n > 0 )
/*N*/                   pLine->SetStartPosX( (sal_uInt16)n );
/*N*/               else
/*N*/                   pLine->SetStartPosX( 0 );
/*N*/
/*N*/           }
/*N*/           break;
/*N*/           case SVX_ADJUST_RIGHT:
/*N*/           {
/*N*/               // Bei automatisch umgebrochenen Zeilen, die ein Blank
/*N*/               // am Ende enthalten, darf das Blank nicht ausgegeben werden!
/*N*/
/*N*/               long n = nMaxLineWidth - aTextSize.Width();
/*N*/               n += nStartX;  // Einrueckung bleibt erhalten.
/*N*/               if ( n > 0 )
/*N*/                   pLine->SetStartPosX( (sal_uInt16)n );
/*N*/               else
/*?*/                   pLine->SetStartPosX( 0 );
/*N*/           }
/*N*/           break;
/*N*/           case SVX_ADJUST_BLOCK:
/*N*/           {
/*N*/               long nRemainingSpace = nMaxLineWidth - aTextSize.Width();
/*N*/               pLine->SetStartPosX( (sal_uInt16)nStartX );
/*N*/               if ( !bEOC && ( nRemainingSpace > 0 ) ) // nicht die letzte Zeile...
/*N*/                   ImpAdjustBlocks( pParaPortion, pLine, nRemainingSpace );
/*N*/           }
/*N*/           break;
/*N*/           default:
/*N*/           {
/*N*/               pLine->SetStartPosX( (sal_uInt16)nStartX ); // FI, LI
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       // -----------------------------------------------------------------
/*N*/       // pruefen, ob die Zeile neu ausgegeben werden muss...
/*N*/       // -----------------------------------------------------------------
/*N*/       pLine->SetInvalid();
/*N*/
/*N*/       // Wenn eine Portion umgebrochen wurde sind ggf. viel zu viele Positionen
/*N*/       // im CharPosArray:
/*N*/       if ( bCalcCharPositions )
/*N*/       {
/*N*/           sal_uInt16 nLen = pLine->GetLen();
/*N*/           sal_uInt16 nCount = pLine->GetCharPosArray().Count();
/*N*/           if ( nCount > nLen )
/*N*/               pLine->GetCharPosArray().Remove( nLen, nCount-nLen );
/*N*/       }
/*N*/
/*N*/       if ( GetTextRanger() )
/*N*/       {
/*?*/           if ( nTextXOffset )
/*?*/               pLine->SetStartPosX( (sal_uInt16) ( pLine->GetStartPosX() + nTextXOffset ) );
/*?*/           if ( nTextExtraYOffset )
/*?*/           {
/*?*/               pLine->SetHeight( (sal_uInt16) ( pLine->GetHeight() + nTextExtraYOffset ), 0, pLine->GetHeight() );
/*?*/               pLine->SetMaxAscent( (sal_uInt16) ( pLine->GetMaxAscent() + nTextExtraYOffset ) );
/*?*/           }
/*N*/       }
/*N*/
/*N*/       // Fuer kleiner 0 noch ueberlegen!
/*N*/       if ( pParaPortion->IsSimpleInvalid() /* && ( nInvalidDiff > 0 ) */ )
/*N*/       {
/*N*/           // Aenderung durch einfache Textaenderung...
/*N*/           // Formatierung nicht abbrechen, da Portions evtl. wieder
/*N*/           // gesplittet werden muessen!
/*N*/           // Wenn irgendwann mal abbrechbar, dann fogende Zeilen Validieren!
/*N*/           // Aber ggf. als Valid markieren, damit weniger Ausgabe...
/*N*/           if ( pLine->GetEnd() < nInvalidStart )
/*N*/           {
/*?*/               if ( *pLine == aSaveLine )
/*?*/               {
/*?*/                   pLine->SetValid();
/*?*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               sal_uInt16 nStart = pLine->GetStart();
/*N*/               sal_uInt16 nEnd = pLine->GetEnd();
/*N*/
/*N*/               if ( nStart > nInvalidEnd )
/*N*/               {
/*?*/                   if ( ( ( nStart-nInvalidDiff ) == aSaveLine.GetStart() ) &&
/*?*/                           ( ( nEnd-nInvalidDiff ) == aSaveLine.GetEnd() ) )
/*?*/                   {
/*?*/                       pLine->SetValid();
/*?*/                       if ( bCalcCharPositions && bQuickFormat )
/*?*/                       {
/*?*/                           bCalcCharPositions = sal_False;
/*?*/                           bLineBreak = sal_False;
/*?*/                           pParaPortion->CorrectValuesBehindLastFormattedLine( nLine );
/*?*/                           break;
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/               else if ( bCalcCharPositions && bQuickFormat && ( nEnd > nInvalidEnd) )
/*N*/               {
/*N*/                   // Wenn die ungueltige Zeile so endet, dass die naechste an
/*N*/                   // der 'gleichen' Textstelle wie vorher beginnt, also nicht
/*N*/                   // anders umgebrochen wird, brauche ich dort auch nicht die
/*N*/                   // textbreiten neu bestimmen:
/*N*/                   if ( nEnd == ( aSaveLine.GetEnd() + nInvalidDiff ) )
/*N*/                   {
/*N*/                       bCalcCharPositions = sal_False;
/*N*/                       bLineBreak = sal_False;
/*N*/                       pParaPortion->CorrectValuesBehindLastFormattedLine( nLine );
/*N*/                       break;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( !bSameLineAgain )
/*N*/       {
/*N*/           nIndex = pLine->GetEnd();   // naechste Zeile Start = letzte Zeile Ende
/*N*/                                       // weil nEnd hinter das letzte Zeichen zeigt!
/*N*/
/*N*/           sal_uInt16 nEndPortion = pLine->GetEndPortion();
/*N*/
/*N*/           // Naechste Zeile oder ggf. neue Zeile....
/*N*/           pLine = 0;
/*N*/           if ( nLine < pParaPortion->GetLines().Count()-1 )
/*N*/               pLine = pParaPortion->GetLines().GetObject( ++nLine );
/*N*/           if ( pLine && ( nIndex >= pNode->Len() ) )
/*N*/           {
/*N*/               nDelFromLine = nLine;
/*N*/               break;
/*N*/           }
/*N*/           if ( !pLine )
/*N*/           {
/*N*/               if ( nIndex < pNode->Len() )
/*N*/               {
/*N*/                   pLine = new EditLine;
/*N*/                   pParaPortion->GetLines().Insert( pLine, ++nLine );
/*N*/               }
/*N*/               else if ( nIndex && bLineBreak && GetTextRanger() )
/*N*/               {
/*?*/                   // normaly CreateAndInsertEmptyLine would be called, but I want to use
/*?*/                   // CreateLines, so I need Polygon code only here...
/*?*/                   TextPortion* pDummyPortion = new TextPortion( 0 );
/*?*/                   pParaPortion->GetTextPortions().Insert( pDummyPortion, pParaPortion->GetTextPortions().Count() );
/*?*/                   pLine = new EditLine;
/*?*/                   pParaPortion->GetLines().Insert( pLine, ++nLine );
/*?*/                   bForceOneRun = TRUE;
/*?*/                   bProcessingEmptyLine = TRUE;
/*N*/               }
/*N*/           }
/*N*/           if ( pLine )
/*N*/           {
/*N*/               aSaveLine = *pLine;
/*N*/               pLine->SetStart( nIndex );
/*N*/               pLine->SetEnd( nIndex );
/*N*/               pLine->SetStartPortion( nEndPortion+1 );
/*N*/               pLine->SetEndPortion( nEndPortion+1 );
/*N*/           }
/*N*/       }
/*N*/   }   // while ( Index < Len )
/*N*/
/*N*/   if ( nDelFromLine != 0xFFFF )
/*N*/       pParaPortion->GetLines().DeleteFromLine( nDelFromLine );
/*N*/
/*N*/   DBG_ASSERT( pParaPortion->GetLines().Count(), "Keine Zeile nach CreateLines!" );
/*N*/
/*N*/   if ( bLineBreak == sal_True )
/*N*/       CreateAndInsertEmptyLine( pParaPortion, nStartPosY );
/*N*/
/*N*/   delete[] pBuf;
/*N*/
/*N*/   sal_Bool bHeightChanged = FinishCreateLines( pParaPortion );
/*N*/
/*N*/   if ( bMapChanged )
/*?*/       GetRefDevice()->Pop();
/*N*/
/*N*/     GetRefDevice()->SetLayoutMode( nOldLayoutMode );
/*N*/
/*N*/   return bHeightChanged;
/*N*/ }

/*N*/ void ImpEditEngine::CreateAndInsertEmptyLine( ParaPortion* pParaPortion, sal_uInt32 nStartPosY )
/*N*/ {
/*N*/   DBG_ASSERT( !GetTextRanger(), "Don't use CreateAndInsertEmptyLine with a polygon!" );
/*N*/
/*N*/   EditLine* pTmpLine = new EditLine;
/*N*/   pTmpLine->SetStart( pParaPortion->GetNode()->Len() );
/*N*/   pTmpLine->SetEnd( pParaPortion->GetNode()->Len() );
/*N*/   pParaPortion->GetLines().Insert( pTmpLine, pParaPortion->GetLines().Count() );
/*N*/
/*N*/   sal_Bool bLineBreak = pParaPortion->GetNode()->Len() ? sal_True : sal_False;
/*N*/   const SvxLRSpaceItem& rLRItem = GetLRSpaceItem( pParaPortion->GetNode() );
/*N*/   const SvxLineSpacingItem& rLSItem = (const SvxLineSpacingItem&)pParaPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL );
/*N*/   short nStartX = GetXValue( (short)(rLRItem.GetTxtLeft() + rLRItem.GetTxtFirstLineOfst()) );
/*N*/
/*N*/   Rectangle aBulletArea = Rectangle( Point(), Point() );
/*N*/   if ( bLineBreak == sal_True )
/*N*/   {
/*N*/       nStartX = (short)GetXValue( rLRItem.GetTxtLeft() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aBulletArea = GetEditEnginePtr()->GetBulletArea( GetParaPortions().GetPos( pParaPortion ) );
/*N*/       if ( aBulletArea.Right() > 0 )
/*?*/           pParaPortion->SetBulletX( (sal_uInt16) GetXValue( aBulletArea.Right() ) );
/*N*/       else
/*N*/           pParaPortion->SetBulletX( 0 ); // Falls Bullet falsch eingestellt.
/*N*/       if ( pParaPortion->GetBulletX() > nStartX )
/*N*/       {
/*?*/           nStartX = (short)GetXValue( rLRItem.GetTxtLeft() );
/*?*/           if ( pParaPortion->GetBulletX() > nStartX )
/*?*/               nStartX = pParaPortion->GetBulletX();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   SvxFont aTmpFont;
/*N*/   SeekCursor( pParaPortion->GetNode(), bLineBreak ? pParaPortion->GetNode()->Len() : 0, aTmpFont );
/*N*/   aTmpFont.SetPhysFont( pRefDev );
/*N*/
/*N*/   TextPortion* pDummyPortion = new TextPortion( 0 );
/*N*/   pDummyPortion->GetSize() = aTmpFont.GetPhysTxtSize( pRefDev, String() );
/*N*/   pParaPortion->GetTextPortions().Insert( pDummyPortion, pParaPortion->GetTextPortions().Count() );
/*N*/   FormatterFontMetric aFormatterMetrics;
/*N*/   RecalcFormatterFontMetrics( aFormatterMetrics, aTmpFont );
/*N*/   pTmpLine->SetMaxAscent( aFormatterMetrics.nMaxAscent );
/*N*/   pTmpLine->SetHeight( (sal_uInt16) pDummyPortion->GetSize().Height() );
/*N*/   sal_uInt16 nLineHeight = aFormatterMetrics.GetHeight();
/*N*/   if ( nLineHeight > pTmpLine->GetHeight() )
/*N*/       pTmpLine->SetHeight( nLineHeight );
/*N*/
/*N*/   if ( !aStatus.IsOutliner() )
/*N*/   {
/*N*/         USHORT nPara = GetParaPortions().GetPos( pParaPortion );
/*N*/       SvxAdjust eJustification = GetJustification( nPara );
/*N*/       long nMaxLineWidth = !IsVertical() ? aPaperSize.Width() : aPaperSize.Height();
/*N*/       nMaxLineWidth -= GetXValue( rLRItem.GetRight() );
/*N*/       long nTextXOffset = 0;
/*N*/       if ( nMaxLineWidth < 0 )
/*N*/           nMaxLineWidth = 1;
/*N*/       if ( eJustification ==  SVX_ADJUST_CENTER )
/*N*/           nStartX = nMaxLineWidth / 2;
/*N*/       else if ( eJustification ==  SVX_ADJUST_RIGHT )
/*?*/           nStartX = (short)nMaxLineWidth;
/*N*/
/*N*/       nStartX += (short)nTextXOffset;
/*N*/   }
/*N*/
/*N*/   pTmpLine->SetStartPosX( nStartX );
/*N*/
/*N*/   if ( !aStatus.IsOutliner() )
/*N*/   {
/*N*/       if ( rLSItem.GetLineSpaceRule() == SVX_LINE_SPACE_MIN )
/*N*/       {
/*?*/           sal_uInt16 nMinHeight = rLSItem.GetLineHeight();
/*?*/           sal_uInt16 nTxtHeight = pTmpLine->GetHeight();
/*?*/           if ( nTxtHeight < nMinHeight )
/*?*/           {
/*?*/               // Der Ascent muss um die Differenz angepasst werden:
/*?*/               long nDiff = nMinHeight - nTxtHeight;
/*?*/               pTmpLine->SetMaxAscent( (sal_uInt16)(pTmpLine->GetMaxAscent() + nDiff) );
/*?*/               pTmpLine->SetHeight( nMinHeight, nTxtHeight );
/*?*/           }
/*N*/       }
/*N*/       else if ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_PROP )
/*N*/       {
/*?*/             USHORT nPara = GetParaPortions().GetPos( pParaPortion );
/*?*/           if ( nPara || ( pTmpLine->GetStartPortion() != 0 ) ) // Nicht die aller erste Zeile
/*?*/           {
/*?*/                 // #100508# There are documents with PropLineSpace 0, why?
/*?*/                 if ( rLSItem.GetPropLineSpace() && ( rLSItem.GetPropLineSpace() != 100 ) )
/*?*/                 {
/*?*/                   sal_uInt16 nTxtHeight = pTmpLine->GetHeight();
/*?*/                   sal_uInt32 nH = nTxtHeight;
/*?*/                   nH *= rLSItem.GetPropLineSpace();
/*?*/                   nH /= 100;
/*?*/                   // Der Ascent muss um die Differenz angepasst werden:
/*?*/                   long nDiff = pTmpLine->GetHeight() - nH;
/*?*/                   if ( nDiff > pTmpLine->GetMaxAscent() )
/*?*/                       nDiff = pTmpLine->GetMaxAscent();
/*?*/                   pTmpLine->SetMaxAscent( (sal_uInt16)(pTmpLine->GetMaxAscent() - nDiff) );
/*?*/                   pTmpLine->SetHeight( (sal_uInt16)nH, nTxtHeight );
/*?*/                 }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( !bLineBreak )
/*N*/   {
/*N*/       long nMinHeight = aBulletArea.GetHeight();
/*N*/       if ( nMinHeight > (long)pTmpLine->GetHeight() )
/*N*/       {
/*?*/           long nDiff = nMinHeight - (long)pTmpLine->GetHeight();
/*?*/           // nDiff auf oben und unten verteilen.
/*?*/           pTmpLine->SetMaxAscent( (sal_uInt16)(pTmpLine->GetMaxAscent() + nDiff/2) );
/*?*/           pTmpLine->SetHeight( (sal_uInt16)nMinHeight );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // -2: Die neue ist bereits eingefuegt.
/*N*/       EditLine* pLastLine = pParaPortion->GetLines().GetObject( pParaPortion->GetLines().Count()-2 );
/*N*/       DBG_ASSERT( pLastLine, "Weicher Umbruch, keine Zeile ?!" );
/*N*/       DBG_ASSERT( pLastLine->GetEnd() == pParaPortion->GetNode()->Len(), "Doch anders?" );
/*N*/ //        pTmpLine->SetStart( pLastLine->GetEnd() );
/*N*/ //        pTmpLine->SetEnd( pLastLine->GetEnd() );
/*N*/       sal_uInt16 nPos = (sal_uInt16) pParaPortion->GetTextPortions().Count() - 1 ;
/*N*/       pTmpLine->SetStartPortion( nPos );
/*N*/       pTmpLine->SetEndPortion( nPos );
/*N*/   }
/*N*/ }

/*N*/ sal_Bool ImpEditEngine::FinishCreateLines( ParaPortion* pParaPortion )
/*N*/ {
/*N*/ //    CalcCharPositions( pParaPortion );
/*N*/   pParaPortion->SetValid();
/*N*/   long nOldHeight = pParaPortion->GetHeight();
/*N*/ //    sal_uInt16 nPos = GetParaPortions().GetPos( pParaPortion );
/*N*/ //    DBG_ASSERT( nPos != USHRT_MAX, "FinishCreateLines: Portion nicht in Liste!" );
/*N*/ //    ParaPortion* pPrev = nPos ? GetParaPortions().GetObject( nPos-1 ) : 0;
/*N*/   CalcHeight( pParaPortion );
/*N*/
/*N*/   DBG_ASSERT( pParaPortion->GetTextPortions().Count(), "FinishCreateLines: Keine Text-Portion?" );
/*N*/   sal_Bool bRet = ( pParaPortion->GetHeight() != nOldHeight );
/*N*/   return bRet;
/*N*/ }

/*N*/ void ImpEditEngine::ImpBreakLine( ParaPortion* pParaPortion, EditLine* pLine, TextPortion* pPortion, sal_uInt16 nPortionStart, long nRemainingWidth, sal_Bool bCanHyphenate )
/*N*/ {
/*N*/   ContentNode* const pNode = pParaPortion->GetNode();
/*N*/
/*N*/   sal_uInt16 nBreakInLine = nPortionStart - pLine->GetStart();
/*N*/   sal_uInt16 nMax = nBreakInLine + pPortion->GetLen();
/*N*/   while ( ( nBreakInLine < nMax ) && ( pLine->GetCharPosArray()[nBreakInLine] < nRemainingWidth ) )
/*N*/       nBreakInLine++;
/*N*/
/*N*/     sal_uInt16 nMaxBreakPos = nBreakInLine + pLine->GetStart();
/*N*/       sal_uInt16 nBreakPos = 0xFFFF;
/*N*/
/*N*/     sal_Bool bCompressBlank = sal_False;
/*N*/     sal_Bool bHyphenated = sal_False;
/*N*/     sal_Bool bHangingPunctuation = sal_False;
/*N*/   sal_Unicode cAlternateReplChar = 0;
/*N*/   sal_Unicode cAlternateExtraChar = 0;
/*N*/
/*N*/     if ( ( nMaxBreakPos < ( nMax + pLine->GetStart() ) ) && ( pNode->GetChar( nMaxBreakPos ) == ' ' ) )
/*N*/     {
/*N*/         // Break behind the blank, blank will be compressed...
/*N*/         nBreakPos = nMaxBreakPos + 1;
/*N*/         bCompressBlank = sal_True;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/       sal_uInt16 nMinBreakPos = pLine->GetStart();
/*N*/       USHORT nAttrs = pNode->GetCharAttribs().GetAttribs().Count();
/*N*/       for ( USHORT nAttr = nAttrs; nAttr; )
/*N*/       {
/*N*/           EditCharAttrib* pAttr = pNode->GetCharAttribs().GetAttribs()[--nAttr];
/*N*/           if ( pAttr->IsFeature() && ( pAttr->GetEnd() > nMinBreakPos ) && ( pAttr->GetEnd() <= nMaxBreakPos ) )
/*N*/           {
/*N*/               nMinBreakPos = pAttr->GetEnd();
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       lang::Locale aLocale = GetLocale( EditPaM( pNode, nMaxBreakPos ) );
/*N*/
/*N*/       Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
/*N*/       OUString aText( *pNode );
/*N*/       Reference< XHyphenator > xHyph;
/*N*/       if ( bCanHyphenate )
/*N*/           xHyph = GetHyphenator();
/*N*/       i18n::LineBreakHyphenationOptions aHyphOptions( xHyph, Sequence< PropertyValue >(), 1 );
/*N*/       i18n::LineBreakUserOptions aUserOptions;
/*N*/
/*N*/       const i18n::ForbiddenCharacters* pForbidden = GetForbiddenCharsTable()->GetForbiddenCharacters( SvxLocaleToLanguage( aLocale ), TRUE );
/*N*/       aUserOptions.forbiddenBeginCharacters = pForbidden->beginLine;
/*N*/       aUserOptions.forbiddenEndCharacters = pForbidden->endLine;
/*N*/       aUserOptions.applyForbiddenRules = ((const SfxBoolItem&)pNode->GetContentAttribs().GetItem( EE_PARA_FORBIDDENRULES )).GetValue();
/*N*/       aUserOptions.allowPunctuationOutsideMargin = ((const SfxBoolItem&)pNode->GetContentAttribs().GetItem( EE_PARA_HANGINGPUNCTUATION )).GetValue();
/*N*/       aUserOptions.allowHyphenateEnglish = FALSE;
/*N*/
/*N*/       i18n::LineBreakResults aLBR = xBI->getLineBreak( *pNode, nMaxBreakPos, aLocale, nMinBreakPos, aHyphOptions, aUserOptions );
/*N*/       nBreakPos = (USHORT)aLBR.breakIndex;
/*N*/
/*N*/       // BUG in I18N - under special condition (break behind field, #87327#) breakIndex is < nMinBreakPos
/*N*/         if ( nBreakPos < nMinBreakPos )
/*N*/         {
/*N*/             nBreakPos = nMinBreakPos;
/*N*/         }
/*N*/         else if ( ( nBreakPos > nMaxBreakPos ) && !aUserOptions.allowPunctuationOutsideMargin )
/*N*/         {
/*N*/             DBG_ERROR( "I18N: XBreakIterator::getLineBreak returns position > Max" );
/*N*/             nBreakPos = nMaxBreakPos;
/*N*/         }
/*N*/
/*N*/         // #101795# nBreakPos can never be outside the portion, even not with hangig punctuation
/*N*/         if ( nBreakPos > nMaxBreakPos )
/*N*/             nBreakPos = nMaxBreakPos;
/*N*/
/*N*/         // BUG in I18N - the japanese dot is in the next line!
/*N*/         // !!!    Testen!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/         if ( (nBreakPos + ( aUserOptions.allowPunctuationOutsideMargin ? 0 : 1 ) ) <= nMaxBreakPos )
/*N*/       {
/*N*/           sal_Unicode cFirstInNextLine = ( (nBreakPos+1) < pNode->Len() ) ? pNode->GetChar( nBreakPos ) : 0;
/*N*/           if ( cFirstInNextLine == 12290 )
/*N*/               nBreakPos++;
/*N*/         }
/*N*/
/*N*/       bHangingPunctuation = ( nBreakPos > nMaxBreakPos ) ? sal_True : sal_False;
/*N*/       pLine->SetHangingPunctuation( bHangingPunctuation );
/*N*/
/*N*/     #ifndef SVX_LIGHT
/*N*/       // Egal ob Trenner oder nicht: Das Wort nach dem Trenner durch
/*N*/       // die Silbentrennung jagen...
/*N*/       // nMaxBreakPos ist das letzte Zeichen was in die Zeile passt,
/*N*/       // nBreakPos ist der Wort-Anfang
/*N*/       // Ein Problem gibt es, wenn das Dok so schmal ist, dass ein Wort
/*N*/       // auf mehr als Zwei Zeilen gebrochen wird...
/*N*/       if ( !bHangingPunctuation && bCanHyphenate && GetHyphenator().is() )
/*N*/       {
/*N*/             i18n::Boundary aBoundary = xBI->getWordBoundary( *pNode, nBreakPos, GetLocale( EditPaM( pNode, nBreakPos ) ), ::com::sun::star::i18n::WordType::DICTIONARY_WORD, sal_True );
/*N*/ //            sal_uInt16 nWordStart = nBreakPos;
/*N*/           sal_uInt16 nBreakPos_OLD = nBreakPos;
/*N*/           sal_uInt16 nWordStart = nBreakPos;
/*N*/             sal_uInt16 nWordEnd = (USHORT) aBoundary.endPos;
/*N*/             DBG_ASSERT( nWordEnd > nWordStart, "ImpBreakLine: Start >= End?" );
/*N*/
/*N*/             USHORT nWordLen = nWordEnd - nWordStart;
/*N*/           if ( ( nWordEnd >= nMaxBreakPos ) && ( nWordLen > 3 ) )
/*N*/           {
/*N*/                 // #104415# May happen, because getLineBreak may differ from getWordBoudary with DICTIONARY_WORD
/*N*/               // DBG_ASSERT( nWordEnd >= nMaxBreakPos, "Hyph: Break?" );
/*N*/               String aWord( *pNode, nWordStart, nWordLen );
/*N*/               sal_uInt16 nMinTrail = nWordEnd-nMaxBreakPos+1;     //+1: Vor dem angeknacksten Buchstaben
/*N*/               Reference< XHyphenatedWord > xHyphWord;
/*N*/               if (xHyphenator.is())
/*N*/                   xHyphWord = xHyphenator->hyphenate( aWord, aLocale, aWord.Len() - nMinTrail, Sequence< PropertyValue >() );
/*N*/               if (xHyphWord.is())
/*N*/               {
/*N*/                   sal_Bool bAlternate = xHyphWord->isAlternativeSpelling();
/*N*/                   sal_uInt16 nWordLen = 1 + xHyphWord->getHyphenPos();
/*N*/
/*N*/                   if ( ( nWordLen >= 2 ) && ( (nWordStart+nWordLen) >= (pLine->GetStart() + 2 ) ) )
/*N*/                   {
/*N*/                       if ( !bAlternate )
/*N*/                       {
/*N*/                           bHyphenated = sal_True;
/*N*/                           nBreakPos = nWordStart + nWordLen;
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*?*/                           String aAlt( xHyphWord->getHyphenatedWord() );
/*?*/
/*?*/                           // Wir gehen von zwei Faellen aus, die nun
/*?*/                           // vorliegen koennen:
/*?*/                           // 1) packen wird zu pak-ken
/*?*/                           // 2) Schiffahrt wird zu Schiff-fahrt
/*?*/                           // In Fall 1 muss ein Zeichen ersetzt werden,
/*?*/                           // in Fall 2 wird ein Zeichen hinzugefuegt.
/*?*/                           // Die Identifikation wird erschwert durch Worte wie
/*?*/                           // "Schiffahrtsbrennesseln", da der Hyphenator alle
/*?*/                           // Position des Wortes auftrennt und "Schifffahrtsbrennnesseln"
/*?*/                           // ermittelt. Wir koennen also eigentlich nicht unmittelbar vom
/*?*/                           // Index des AlternativWord auf aWord schliessen.
/*?*/
/*?*/                           // Das ganze geraffel wird durch eine Funktion am
/*?*/                           // Hyphenator vereinfacht werden, sobald AMA sie einbaut...
/*?*/                           sal_uInt16 nAltStart = nWordLen - 1;
/*?*/                           sal_uInt16 nTxtStart = nAltStart - (aAlt.Len() - aWord.Len());
/*?*/                           sal_uInt16 nTxtEnd = nTxtStart;
/*?*/                           sal_uInt16 nAltEnd = nAltStart;
/*?*/
/*?*/                           // Die Bereiche zwischen den nStart und nEnd ist
/*?*/                           // die Differenz zwischen Alternativ- und OriginalString.
/*?*/                           while( nTxtEnd < aWord.Len() && nAltEnd < aAlt.Len() &&
/*?*/                                  aWord.GetChar(nTxtEnd) != aAlt.GetChar(nAltEnd) )
/*?*/                           {
/*?*/                               ++nTxtEnd;
/*?*/                               ++nAltEnd;
/*?*/                           }
/*?*/
/*?*/                           // Wenn ein Zeichen hinzugekommen ist, dann bemerken wir es jetzt:
/*?*/                           if( nAltEnd > nTxtEnd && nAltStart == nAltEnd &&
/*?*/                               aWord.GetChar( nTxtEnd ) == aAlt.GetChar(nAltEnd) )
/*?*/                           {
/*?*/                               ++nAltEnd;
/*?*/                               ++nTxtStart;
/*?*/                               ++nTxtEnd;
/*?*/                           }
/*?*/
/*?*/                           DBG_ASSERT( ( nAltEnd - nAltStart ) == 1, "Alternate: Falsche Annahme!" );
/*?*/
/*?*/                           if ( nTxtEnd > nTxtStart )
/*?*/                               cAlternateReplChar = aAlt.GetChar( nAltStart );
/*?*/                           else
/*?*/                               cAlternateExtraChar = aAlt.GetChar( nAltStart );
/*?*/
/*?*/                           bHyphenated = sal_True;
/*?*/                           nBreakPos = nWordStart + nTxtStart;
/*?*/                           if ( cAlternateReplChar )
/*?*/                               nBreakPos++;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/     #endif // !SVX_LIGHT
/*N*/
/*N*/       if ( nBreakPos <= pLine->GetStart() )
/*N*/       {
/*N*/           // keine Trenner in Zeile => abhacken !
/*N*/           nBreakPos = nMaxBreakPos;
/*N*/           // MT: I18N nextCharacters !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/           if ( nBreakPos <= pLine->GetStart() )
/*N*/               nBreakPos = pLine->GetStart() + 1;  // Sonst Endlosschleife!
/*N*/       }
/*N*/     }
/*N*/
/*N*/     // die angeknackste Portion ist die End-Portion
/*N*/   pLine->SetEnd( nBreakPos );
/*N*/
/*N*/     sal_uInt16 nEndPortion = SplitTextPortion( pParaPortion, nBreakPos, pLine );
/*N*/
/*N*/   if ( !bCompressBlank && !bHangingPunctuation )
/*N*/   {
/*N*/       // #96187# When justification is not SVX_ADJUST_LEFT, it's important to compress
/*N*/       // the trailing space even if there is enough room for the space...
/*N*/       // Don't check for SVX_ADJUST_LEFT, doesn't matter to compress in this case too...
/*N*/       DBG_ASSERT( nBreakPos > pLine->GetStart(), "ImpBreakLines - BreakPos not expected!" );
/*N*/       if ( pNode->GetChar( nBreakPos-1 ) == ' ' )
/*N*/           bCompressBlank = sal_True;
/*N*/   }
/*N*/
/*N*/   if ( bCompressBlank || bHangingPunctuation )
/*N*/   {
/*N*/       TextPortion* pTP = pParaPortion->GetTextPortions().GetObject( nEndPortion );
/*N*/       DBG_ASSERT( pTP->GetKind() == PORTIONKIND_TEXT, "BlankRubber: Keine TextPortion!" );
/*N*/       DBG_ASSERT( nBreakPos > pLine->GetStart(), "SplitTextPortion am Anfang der Zeile?" );
/*N*/       sal_uInt16 nPosInArray = nBreakPos - 1 - pLine->GetStart();
/*N*/       pTP->GetSize().Width() = ( nPosInArray && ( pTP->GetLen() > 1 ) ) ? pLine->GetCharPosArray()[ nPosInArray-1 ] : 0;
/*N*/         pLine->GetCharPosArray()[ nPosInArray ] = pTP->GetSize().Width();
/*N*/   }
/*N*/   else if ( bHyphenated )
/*N*/   {
/*N*/       // Eine Portion fuer den Trenner einbauen...
/*N*/       TextPortion* pHyphPortion = new TextPortion( 0 );
/*N*/       pHyphPortion->GetKind() = PORTIONKIND_HYPHENATOR;
/*N*/       String aHyphText( CH_HYPH );
/*N*/       if ( cAlternateReplChar )
/*N*/       {
/*?*/           TextPortion* pPrev = pParaPortion->GetTextPortions().GetObject( nEndPortion );
/*?*/           DBG_ASSERT( pPrev && pPrev->GetLen(), "Hyphenate: Prev portion?!" );
/*?*/           pPrev->SetLen( pPrev->GetLen() - 1 );
/*?*/           pHyphPortion->SetLen( 1 );
/*?*/           pHyphPortion->SetExtraValue( cAlternateReplChar );
/*?*/           // Breite der Portion davor korrigieren:
/*?*/           pPrev->GetSize().Width() =
/*?*/               pLine->GetCharPosArray()[ nBreakPos-1 - pLine->GetStart() - 1 ];
/*N*/       }
/*N*/       else if ( cAlternateExtraChar )
/*N*/       {
/*?*/           pHyphPortion->SetExtraValue( cAlternateExtraChar );
/*?*/           aHyphText.Insert( cAlternateExtraChar, 0 );
/*N*/       }
/*N*/
/*N*/       // Breite der Hyph-Portion ermitteln:
/*N*/       SvxFont aFont;
/*N*/       SeekCursor( pParaPortion->GetNode(), nBreakPos, aFont );
/*N*/       aFont.SetPhysFont( GetRefDevice() );
/*N*/       pHyphPortion->GetSize().Height() = GetRefDevice()->GetTextHeight();
/*N*/       pHyphPortion->GetSize().Width() = GetRefDevice()->GetTextWidth( aHyphText );
/*N*/
/*N*/       pParaPortion->GetTextPortions().Insert( pHyphPortion, ++nEndPortion );
/*N*/   }
/*N*/   pLine->SetEndPortion( nEndPortion );
/*N*/ }

/*N*/ void ImpEditEngine::ImpAdjustBlocks( ParaPortion* pParaPortion, EditLine* pLine, long nRemainingSpace )
/*N*/ {
/*N*/   DBG_ASSERT( nRemainingSpace > 0, "AdjustBlocks: Etwas zuwenig..." );
/*N*/   DBG_ASSERT( pLine, "AdjustBlocks: Zeile ?!" );
/*N*/   if ( ( nRemainingSpace < 0 ) || pLine->IsEmpty() )
/*N*/       return ;
/*N*/
/*N*/   const USHORT nFirstChar = pLine->GetStart();
/*N*/   const USHORT nLastChar = pLine->GetEnd() -1;    // Last zeigt dahinter
/*N*/     ContentNode* pNode = pParaPortion->GetNode();
/*N*/
/*N*/   DBG_ASSERT( nLastChar < pNode->Len(), "AdjustBlocks: Out of range!" );
/*N*/
/*N*/   // Search blanks or Kashidas...
/*N*/     SvUShorts aPositions;
/*N*/   USHORT nChar;
/*N*/   for ( nChar = nFirstChar; nChar <= nLastChar; nChar++ )
/*N*/   {
/*N*/       if ( pNode->GetChar(nChar) == ' ' )
/*N*/         {
/*N*/             // Don't use blank if language is arabic
/*N*/             LanguageType eLang = GetLanguage( EditPaM( pNode, nChar ) );
/*N*/             if ( eLang != LANGUAGE_ARABIC )
/*N*/                 aPositions.Insert( nChar, aPositions.Count() );
/*N*/         }
/*N*/   }
/*N*/
/*N*/     // Kashidas ?
/*N*/     ImpFindKashidas( pNode, nFirstChar, nLastChar, aPositions );
/*N*/
/*N*/
/*N*/   if ( !aPositions.Count() )
/*N*/       return;
/*N*/
/*N*/   // Wenn das letzte Zeichen ein Blank ist, will ich es nicht haben!
/*N*/   // Die Breite muss auf die Blocker davor verteilt werden...
/*N*/   // Aber nicht, wenn es das einzige ist
/*N*/   if ( ( pNode->GetChar( nLastChar ) == ' ' ) && ( aPositions.Count() > 1 ) && ( GetLanguage( EditPaM( pNode, nLastChar ) ) != LANGUAGE_ARABIC ) )
/*N*/   {
/*N*/         aPositions.Remove( aPositions.Count()-1, 1 );
/*N*/       USHORT nPortionStart, nPortion;
/*N*/       nPortion = pParaPortion->GetTextPortions().FindPortion( nLastChar+1, nPortionStart );
/*N*/       TextPortion* pLastPortion = pParaPortion->GetTextPortions()[ nPortion ];
/*N*/       long nRealWidth = pLine->GetCharPosArray()[nLastChar-nFirstChar];
/*N*/       long nBlankWidth = nRealWidth;
/*N*/       if ( nLastChar > nPortionStart )
/*N*/           nBlankWidth -= pLine->GetCharPosArray()[nLastChar-nFirstChar-1];
/*N*/       // Evtl. ist das Blank schon in ImpBreakLine abgezogen worden:
/*N*/       if ( nRealWidth == pLastPortion->GetSize().Width() )
/*N*/       {
/*N*/           // Beim letzten Zeichen muss die Portion hinter dem Blank aufhoeren
/*N*/           // => Korrektur vereinfachen:
/*N*/           DBG_ASSERT( ( nPortionStart + pLastPortion->GetLen() ) == ( nLastChar+1 ), "Blank doch nicht am Portion-Ende?!" );
/*N*/           pLastPortion->GetSize().Width() -= nBlankWidth;
/*N*/           nRemainingSpace += nBlankWidth;
/*N*/       }
/*N*/       pLine->GetCharPosArray()[nLastChar-nFirstChar] -= nBlankWidth;
/*N*/   }
/*N*/
/*N*/     USHORT nGaps = aPositions.Count();
/*N*/   const long nMore4Everyone = nRemainingSpace / nGaps;
/*N*/   long nSomeExtraSpace = nRemainingSpace - nMore4Everyone*nGaps;
/*N*/
/*N*/   DBG_ASSERT( nSomeExtraSpace < (long)nGaps, "AdjustBlocks: ExtraSpace zu gross" );
/*N*/   DBG_ASSERT( nSomeExtraSpace >= 0, "AdjustBlocks: ExtraSpace < 0 " );
/*N*/
/*N*/   // Die Positionen im Array und die Portion-Breiten korrigieren:
/*N*/   // Letztes Zeichen wird schon nicht mehr beachtet...
/*N*/     for ( USHORT n = 0; n < aPositions.Count(); n++ )
/*N*/   {
/*N*/         nChar = aPositions[n];
/*N*/       if ( nChar < nLastChar )
/*N*/       {
/*N*/           USHORT nPortionStart, nPortion;
/*N*/           nPortion = pParaPortion->GetTextPortions().FindPortion( nChar, nPortionStart );
/*N*/           TextPortion* pLastPortion = pParaPortion->GetTextPortions()[ nPortion ];
/*N*/
/*N*/           // Die Breite der Portion:
/*N*/           pLastPortion->GetSize().Width() += nMore4Everyone;
/*N*/           if ( nSomeExtraSpace )
/*N*/               pLastPortion->GetSize().Width()++;
/*N*/
/*N*/           // Correct positions in array
/*N*/             // Even for kashidas just change positions, VCL will then draw the kashida automaticly
/*N*/           USHORT nPortionEnd = nPortionStart + pLastPortion->GetLen();
/*N*/           for ( USHORT n = nChar; n < nPortionEnd; n++ )
/*N*/           {
/*N*/               pLine->GetCharPosArray()[n-nFirstChar] += nMore4Everyone;
/*N*/               if ( nSomeExtraSpace )
/*N*/                   pLine->GetCharPosArray()[n-nFirstChar]++;
/*N*/           }
/*N*/
/*N*/           if ( nSomeExtraSpace )
/*N*/               nSomeExtraSpace--;
/*N*/       }
/*N*/   }
/*N*/
/*N*/     // Now the text width contains the extra width...
/*N*/     pLine->SetTextWidth( pLine->GetTextWidth() + nRemainingSpace );
/*N*/ }

/*N*/ void ImpEditEngine::ImpFindKashidas( ContentNode* pNode, USHORT nStart, USHORT nEnd, SvUShorts& rArray )
/*N*/ {
/*N*/     // the search has to be performed on a per word base
/*N*/
/*N*/     EditSelection aWordSel( EditPaM( pNode, nStart ) );
/*N*/     aWordSel = SelectWord( aWordSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
/*N*/     if ( aWordSel.Min().GetIndex() < nStart )
/*N*/        aWordSel.Min().GetIndex() = nStart;
/*N*/
/*N*/     while ( ( aWordSel.Min().GetNode() == pNode ) && ( aWordSel.Min().GetIndex() < nEnd ) )
/*N*/     {
/*N*/         if ( aWordSel.Max().GetIndex() > nEnd )
/*N*/            aWordSel.Max().GetIndex() = nEnd;
/*N*/
/*N*/         String aWord = GetSelected( aWordSel );
/*N*/         xub_StrLen nIdx = 0;
/*N*/         xub_StrLen nKashidaPos = STRING_LEN;
/*N*/         xub_Unicode cCh;
/*N*/         xub_Unicode cPrevCh = 0;
/*N*/
/*N*/         while ( nIdx < aWord.Len() )
/*N*/         {
/*N*/             cCh = aWord.GetChar( nIdx );
/*N*/
/*N*/             // 1. Priority:
/*N*/             // after user inserted kashida
/*N*/             if ( 0x640 == cCh )
/*N*/             {
/*?*/                 nKashidaPos = aWordSel.Min().GetIndex() + nIdx;
/*?*/                 break;
/*N*/             }
/*N*/
/*N*/             // 2. Priority:
/*N*/             // after a Seen or Sad
/*N*/             if ( nIdx + 1 < aWord.Len() &&
/*N*/                  ( 0x633 == cCh || 0x635 == cCh ) )
/*N*/             {
/*?*/                 nKashidaPos = aWordSel.Min().GetIndex() + nIdx;
/*?*/                 break;
/*N*/             }
/*N*/
/*N*/             // 3. Priority:
/*N*/             // before final form of Teh Marbuta, Hah, Dal
/*N*/             // 4. Priority:
/*N*/             // before final form of Alef, Lam or Kaf
/*N*/             if ( nIdx && nIdx + 1 == aWord.Len() &&
/*N*/                  ( 0x629 == cCh || 0x62D == cCh || 0x62F == cCh ||
/*N*/                    0x627 == cCh || 0x644 == cCh || 0x643 == cCh ) )
/*N*/             {
/*?*/                 DBG_ASSERT(0, "STRIP"); //STRIP001 DBG_ASSERT( 0 != cPrevCh, "No previous character" )
//STRIP001 /*?*/
//STRIP001 /*?*/                 // check if character is connectable to previous character,
//STRIP001 /*?*/                 if ( lcl_ConnectToPrev( cCh, cPrevCh ) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     nKashidaPos = aWordSel.Min().GetIndex() + nIdx - 1;
//STRIP001 /*?*/                     break;
//STRIP001 /*?*/                 }
/*N*/             }
/*N*/
/*N*/             // 5. Priority:
/*N*/             // before media Bah
/*N*/             if ( nIdx && nIdx + 1 < aWord.Len() && 0x628 == cCh )
/*N*/             {
/*?*/                 DBG_ASSERT( 0 != cPrevCh, "No previous character" )
/*?*/
/*?*/                 // check if next character is Reh, Yeh or Alef Maksura
/*?*/                 xub_Unicode cNextCh = aWord.GetChar( nIdx + 1 );
/*?*/
/*?*/                 if ( 0x631 == cNextCh || 0x64A == cNextCh ||
/*?*/                      0x649 == cNextCh )
/*?*/                 {
/*?*/                     DBG_ASSERT(0, "STRIP"); //STRIP001 // check if character is connectable to previous character,
//STRIP001 /*?*/                     if ( lcl_ConnectToPrev( cCh, cPrevCh ) )
//STRIP001 /*?*/                         nKashidaPos = aWordSel.Min().GetIndex() + nIdx - 1;
/*?*/                 }
/*N*/             }
/*N*/
/*N*/             // 6. Priority:
/*N*/             // other connecting possibilities
/*N*/             if ( nIdx && nIdx + 1 == aWord.Len() &&
/*N*/                  0x60C <= cCh && 0x6FE >= cCh )
/*N*/             {
/*?*/                 DBG_ASSERT(0, "STRIP"); //STRIP001 DBG_ASSERT( 0 != cPrevCh, "No previous character" )
//STRIP001 /*?*/
//STRIP001 /*?*/                 // check if character is connectable to previous character,
//STRIP001 /*?*/                 if ( lcl_ConnectToPrev( cCh, cPrevCh ) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     // only choose this position if we did not find
//STRIP001 /*?*/                     // a better one:
//STRIP001 /*?*/                     if ( STRING_LEN == nKashidaPos )
//STRIP001 /*?*/                         nKashidaPos = aWordSel.Min().GetIndex() + nIdx - 1;
//STRIP001 /*?*/                     break;
//STRIP001 /*?*/                 }
/*N*/             }
/*N*/
/*N*/             // Do not consider Fathatan, Dammatan, Kasratan, Fatha,
/*N*/             // Damma, Kasra, Shadda and Sukun when checking if
/*N*/             // a character can be connected to previous character.
/*N*/             if ( cCh < 0x64B || cCh > 0x652 )
/*N*/                 cPrevCh = cCh;
/*N*/
/*N*/             ++nIdx;
/*N*/         } // end of current word
/*N*/
/*N*/         if ( STRING_LEN != nKashidaPos )
/*?*/             rArray.Insert( nKashidaPos, rArray.Count() );
/*N*/
/*N*/         aWordSel = WordRight( aWordSel.Max(), ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
/*N*/         aWordSel = SelectWord( aWordSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
/*N*/     }
/*N*/ }

/*N*/ sal_uInt16 ImpEditEngine::SplitTextPortion( ParaPortion* pPortion, sal_uInt16 nPos, EditLine* pCurLine )
/*N*/ {
/*N*/   DBG_ASSERT( pPortion, "SplitTextPortion: Welche ?" );
/*N*/
/*N*/   // Die Portion bei nPos wird geplittet, wenn bei nPos nicht
/*N*/   // sowieso ein Wechsel ist
/*N*/   if ( nPos == 0 )
/*N*/       return 0;
/*N*/
/*N*/   sal_uInt16 nSplitPortion;
/*N*/   sal_uInt16 nTmpPos = 0;
/*N*/   TextPortion* pTextPortion = 0;
/*N*/   sal_uInt16 nPortions = pPortion->GetTextPortions().Count();
/*N*/   for ( nSplitPortion = 0; nSplitPortion < nPortions; nSplitPortion++ )
/*N*/   {
/*N*/       TextPortion* pTP = pPortion->GetTextPortions().GetObject(nSplitPortion);
/*N*/       nTmpPos += pTP->GetLen();
/*N*/       if ( nTmpPos >= nPos )
/*N*/       {
/*N*/           if ( nTmpPos == nPos )  // dann braucht nichts geteilt werden
/*N*/           {
/*N*/               // Skip Portions with ExtraSpace
/*N*/ //                while ( ( (nSplitPortion+1) < nPortions ) && (pPortion->GetTextPortions().GetObject(nSplitPortion+1)->GetKind() == PORTIONKIND_EXTRASPACE ) )
/*N*/ //                    nSplitPortion++;
/*N*/
/*N*/               return nSplitPortion;
/*N*/           }
/*N*/           pTextPortion = pTP;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   DBG_ASSERT( pTextPortion, "Position ausserhalb des Bereichs!" );
/*N*/   DBG_ASSERT( pTextPortion->GetKind() == PORTIONKIND_TEXT, "SplitTextPortion: Keine TextPortion!" );
/*N*/
/*N*/   sal_uInt16 nOverlapp = nTmpPos - nPos;
/*N*/   pTextPortion->GetLen() -= nOverlapp;
/*N*/   TextPortion* pNewPortion = new TextPortion( nOverlapp );
/*N*/   pPortion->GetTextPortions().Insert( pNewPortion, nSplitPortion+1 );
/*N*/   // Groessen setzen:
/*N*/   if ( pCurLine )
/*N*/   {
/*N*/       // Kein neues GetTextSize, sondern Werte aus Array verwenden:
/*N*/       DBG_ASSERT( nPos > pCurLine->GetStart(), "SplitTextPortion am Anfang der Zeile?" );
/*N*/       pTextPortion->GetSize().Width() = pCurLine->GetCharPosArray()[ nPos-pCurLine->GetStart()-1 ];
/*N*/
/*N*/         if ( pTextPortion->GetExtraInfos() && pTextPortion->GetExtraInfos()->bCompressed )
/*N*/         {
/*?*/             // We need the original size from the portion
/*?*/             DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nTxtPortionStart = pPortion->GetTextPortions().GetStartPos( nSplitPortion );
//STRIP001 /*?*/                SvxFont aTmpFont( pPortion->GetNode()->GetCharAttribs().GetDefFont() );
//STRIP001 /*?*/            SeekCursor( pPortion->GetNode(), nTxtPortionStart+1, aTmpFont );
//STRIP001 /*?*/            aTmpFont.SetPhysFont( GetRefDevice() );
//STRIP001 /*?*/            Size aSz = aTmpFont.QuickGetTextSize( GetRefDevice(), *pPortion->GetNode(), nTxtPortionStart, pTextPortion->GetLen(), NULL );
//STRIP001 /*?*/             pTextPortion->GetExtraInfos()->nOrgWidth = aSz.Width();
/*N*/         }
/*N*/   }
/*N*/   else
/*?*/       pTextPortion->GetSize().Width() = (-1);
/*N*/
/*N*/   return nSplitPortion;
/*N*/ }

/*N*/ void ImpEditEngine::CreateTextPortions( ParaPortion* pParaPortion, sal_uInt16& rStart /* , sal_Bool bCreateBlockPortions */ )
/*N*/ {
/*N*/   sal_uInt16 nStartPos = rStart;
/*N*/   ContentNode* pNode = pParaPortion->GetNode();
/*N*/   DBG_ASSERT( pNode->Len(), "CreateTextPortions sollte nicht fuer leere Absaetze verwendet werden!" );
/*N*/
/*N*/   SortedPositions aPositions;
/*N*/   aPositions.Insert( (sal_uInt32) 0 );
/*N*/
/*N*/   sal_uInt16 nAttr = 0;
/*N*/   EditCharAttrib* pAttrib = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
/*N*/   while ( pAttrib )
/*N*/   {
/*N*/       // Start und Ende in das Array eintragen...
/*N*/       // Die InsertMethode laesst keine doppelten Werte zu....
/*N*/       aPositions.Insert( pAttrib->GetStart() );
/*N*/       aPositions.Insert( pAttrib->GetEnd() );
/*N*/       nAttr++;
/*N*/       pAttrib = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
/*N*/   }
/*N*/   aPositions.Insert( pNode->Len() );
/*N*/
/*N*/   if ( !pParaPortion->aScriptInfos.Count() )
/*?*/       ((ImpEditEngine*)this)->InitScriptTypes( GetParaPortions().GetPos( pParaPortion ) );
/*N*/
/*N*/   const ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/   for ( USHORT nT = 0; nT < rTypes.Count(); nT++ )
/*N*/       aPositions.Insert( rTypes[nT].nStartPos );
/*N*/
/*N*/     const WritingDirectionInfos& rWritingDirections = pParaPortion->aWritingDirectionInfos;
/*N*/   for ( USHORT nD = 0; nD < rWritingDirections.Count(); nD++ )
/*?*/       aPositions.Insert( rWritingDirections[nD].nStartPos );
/*N*/
/*N*/   if ( mpIMEInfos && mpIMEInfos->nLen && mpIMEInfos->pAttribs && ( mpIMEInfos->aPos.GetNode() == pNode ) )
/*N*/   {
/*?*/       sal_uInt16 nLastAttr = 0xFFFF;
/*?*/       for( sal_uInt16 n = 0; n < mpIMEInfos->nLen; n++ )
/*?*/       {
/*?*/           if ( mpIMEInfos->pAttribs[n] != nLastAttr )
/*?*/           {
/*?*/               aPositions.Insert( mpIMEInfos->aPos.GetIndex() + n );
/*?*/               nLastAttr = mpIMEInfos->pAttribs[n];
/*?*/           }
/*?*/       }
/*?*/       aPositions.Insert( mpIMEInfos->aPos.GetIndex() + mpIMEInfos->nLen );
/*N*/   }
/*N*/
/*N*/   // Ab ... loeschen:
/*N*/   // Leider muss die Anzahl der TextPortions mit aPositions.Count()
/*N*/   // nicht uebereinstimmen, da evtl. Zeilenumbrueche...
/*N*/   sal_uInt16 nPortionStart = 0;
/*N*/   sal_uInt16 nInvPortion = 0;
/*N*/   sal_uInt16 nP; for ( nP = 0; nP < pParaPortion->GetTextPortions().Count(); nP++ )
/*N*/   {
/*N*/       TextPortion* pTmpPortion = pParaPortion->GetTextPortions().GetObject(nP);
/*N*/       nPortionStart += pTmpPortion->GetLen();
/*N*/       if ( nPortionStart >= nStartPos )
/*N*/       {
/*N*/           nPortionStart -= pTmpPortion->GetLen();
/*N*/           rStart = nPortionStart;
/*N*/           nInvPortion = nP;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   DBG_ASSERT( nP < pParaPortion->GetTextPortions().Count() || !pParaPortion->GetTextPortions().Count(), "Nichts zum loeschen: CreateTextPortions" );
/*N*/   if ( nInvPortion && ( nPortionStart+pParaPortion->GetTextPortions().GetObject(nInvPortion)->GetLen() > nStartPos ) )
/*N*/   {
/*?*/       // lieber eine davor...
/*?*/       // Aber nur wenn es mitten in der Portion war, sonst ist es evtl.
/*?*/       // die einzige in der Zeile davor !
/*?*/       nInvPortion--;
/*?*/       nPortionStart -= pParaPortion->GetTextPortions().GetObject(nInvPortion)->GetLen();
/*N*/   }
/*N*/   pParaPortion->GetTextPortions().DeleteFromPortion( nInvPortion );
/*N*/
/*N*/   // Eine Portion kann auch durch einen Zeilenumbruch entstanden sein:
/*N*/   aPositions.Insert( nPortionStart );
/*N*/
/*N*/   sal_uInt16 nInvPos;
/*N*/   sal_Bool bFound = aPositions.Seek_Entry( nPortionStart, &nInvPos );
/*N*/   DBG_ASSERT( bFound && ( nInvPos < (aPositions.Count()-1) ), "InvPos ?!" );
/*N*/   for ( sal_uInt16 i = nInvPos+1; i < aPositions.Count(); i++ )
/*N*/   {
/*N*/       TextPortion* pNew = new TextPortion( (sal_uInt16)aPositions[i] - (sal_uInt16)aPositions[i-1] );
/*N*/       pParaPortion->GetTextPortions().Insert( pNew, pParaPortion->GetTextPortions().Count());
/*N*/   }
/*N*/
/*N*/   DBG_ASSERT( pParaPortion->GetTextPortions().Count(), "Keine Portions?!" );
/*N*/ #ifdef EDITDEBUG
/*N*/   DBG_ASSERT( pParaPortion->DbgCheckTextPortions(), "Portions kaputt?" );
/*N*/ #endif
/*N*/ }

/*N*/ void ImpEditEngine::RecalcTextPortion( ParaPortion* pParaPortion, sal_uInt16 nStartPos, short nNewChars )
/*N*/ {
/*N*/   DBG_ASSERT( pParaPortion->GetTextPortions().Count(), "Keine Portions!" );
/*N*/   DBG_ASSERT( nNewChars, "RecalcTextPortion mit Diff == 0" );
/*N*/
/*N*/   ContentNode* const pNode = pParaPortion->GetNode();
/*N*/   if ( nNewChars > 0 )
/*N*/   {
/*N*/       // Wenn an nStartPos ein Attribut beginnt/endet, faengt eine neue Portion
/*N*/       // an, ansonsten wird die Portion an nStartPos erweitert.
/*N*/
/*N*/       if ( pNode->GetCharAttribs().HasBoundingAttrib( nStartPos ) || IsScriptChange( EditPaM( pNode, nStartPos ) ) )
/*N*/       {
/*N*/           sal_uInt16 nNewPortionPos = 0;
/*N*/           if ( nStartPos )
/*?*/               nNewPortionPos = SplitTextPortion( pParaPortion, nStartPos ) + 1;
/*N*/
/*N*/           // Eine leere Portion kann hier stehen, wenn der Absatz leer war,
/*N*/           // oder eine Zeile durch einen harten Zeilenumbruch entstanden ist.
/*N*/           if ( ( nNewPortionPos < pParaPortion->GetTextPortions().Count() ) &&
/*N*/                   !pParaPortion->GetTextPortions()[nNewPortionPos]->GetLen() )
/*N*/           {
/*N*/               DBG_ASSERT( pParaPortion->GetTextPortions()[nNewPortionPos]->GetKind() == PORTIONKIND_TEXT, "Leere Portion war keine TextPortion!" );
/*N*/               pParaPortion->GetTextPortions()[nNewPortionPos]->GetLen() += nNewChars;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               TextPortion* pNewPortion = new TextPortion( nNewChars );
/*N*/               pParaPortion->GetTextPortions().Insert( pNewPortion, nNewPortionPos );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           sal_uInt16 nPortionStart;
/*N*/           const sal_uInt16 nTP = pParaPortion->GetTextPortions().
/*N*/               FindPortion( nStartPos, nPortionStart );
/*N*/           TextPortion* const pTP = pParaPortion->GetTextPortions()[ nTP ];
/*N*/           DBG_ASSERT( pTP, "RecalcTextPortion: Portion nicht gefunden"  );
/*N*/           pTP->GetLen() += nNewChars;
/*N*/           pTP->GetSize().Width() = (-1);
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       // Portion schrumpfen oder ggf. entfernen.
/*?*/       // Vor Aufruf dieser Methode muss sichergestellt sein, dass
/*?*/       // keine Portions in dem geloeschten Bereich lagen!
/*?*/
/*?*/       // Es darf keine reinragende oder im Bereich startende Portion geben,
/*?*/       // also muss nStartPos <= nPos <= nStartPos - nNewChars(neg.) sein
/*?*/       sal_uInt16 nPortion = 0;
/*?*/       sal_uInt16 nPos = 0;
/*?*/       sal_uInt16 nEnd = nStartPos-nNewChars;
/*?*/       sal_uInt16 nPortions = pParaPortion->GetTextPortions().Count();
/*?*/       TextPortion* pTP = 0;
/*?*/       for ( nPortion = 0; nPortion < nPortions; nPortion++ )
/*?*/       {
/*?*/           pTP = pParaPortion->GetTextPortions()[ nPortion ];
/*?*/           if ( ( nPos+pTP->GetLen() ) > nStartPos )
/*?*/           {
/*?*/               DBG_ASSERT( nPos <= nStartPos, "Start falsch!" );
/*?*/               DBG_ASSERT( nPos+pTP->GetLen() >= nEnd, "End falsch!" );
/*?*/               break;
/*?*/           }
/*?*/           nPos += pTP->GetLen();
/*?*/       }
/*?*/       DBG_ASSERT( pTP, "RecalcTextPortion: Portion nicht gefunden" );
/*?*/       if ( ( nPos == nStartPos ) && ( (nPos+pTP->GetLen()) == nEnd ) )
/*?*/       {
/*?*/           // Portion entfernen;
/*?*/           BYTE nType = pTP->GetKind();
/*?*/           pParaPortion->GetTextPortions().Remove( nPortion );
/*?*/           delete pTP;
/*?*/           if ( nType == PORTIONKIND_LINEBREAK )
/*?*/           {
/*?*/               TextPortion* pNext = pParaPortion->GetTextPortions()[ nPortion ];
/*?*/               if ( pNext && !pNext->GetLen() )
/*?*/               {
/*?*/                   // Dummy-Portion entfernen
/*?*/                   pParaPortion->GetTextPortions().Remove( nPortion );
/*?*/                   delete pNext;
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           DBG_ASSERT( pTP->GetLen() > (-nNewChars), "Portion zu klein zum schrumpfen!" );
/*?*/           pTP->GetLen() += nNewChars;
/*?*/       }
/*?*/
/*?*/       // ganz am Schluss darf keine HYPHENATOR-Portion stehen bleiben...
/*?*/       DBG_ASSERT( pParaPortion->GetTextPortions().Count(), "RecalcTextPortions: Keine mehr da!" );
/*?*/       sal_uInt16 nLastPortion = pParaPortion->GetTextPortions().Count() - 1;
/*?*/       pTP = pParaPortion->GetTextPortions().GetObject( nLastPortion );
/*?*/       if ( pTP->GetKind() == PORTIONKIND_HYPHENATOR )
/*?*/       {
/*?*/           // Portion wegschmeissen, ggf. die davor korrigieren, wenn
/*?*/           // die Hyph-Portion ein Zeichen geschluckt hat...
/*?*/           pParaPortion->GetTextPortions().Remove( nLastPortion );
/*?*/           if ( nLastPortion && pTP->GetLen() )
/*?*/           {
/*?*/               TextPortion* pPrev = pParaPortion->GetTextPortions().GetObject( nLastPortion - 1 );
/*?*/               DBG_ASSERT( pPrev->GetKind() == PORTIONKIND_TEXT, "Portion?!" );
/*?*/               pPrev->SetLen( pPrev->GetLen() + pTP->GetLen() );
/*?*/               pPrev->GetSize().Width() = (-1);
/*?*/           }
/*?*/           delete pTP;
/*?*/       }
/*N*/   }
/*N*/ #ifdef EDITDEBUG
/*N*/   DBG_ASSERT( pParaPortion->DbgCheckTextPortions(), "Portions kaputt?" );
/*N*/ #endif
/*N*/ }

/*N*/ void ImpEditEngine::SetTextRanger( TextRanger* pRanger )
/*N*/ {
/*N*/   if ( pTextRanger != pRanger )
/*N*/   {
/*?*/       delete pTextRanger;
/*?*/       pTextRanger = pRanger;
/*?*/
/*?*/       for ( sal_uInt16 nPara = 0; nPara < GetParaPortions().Count(); nPara++ )
/*?*/       {
/*?*/           ParaPortion* pParaPortion = GetParaPortions().GetObject( nPara );
/*?*/           pParaPortion->MarkSelectionInvalid( 0, pParaPortion->GetNode()->Len() );
/*?*/           pParaPortion->GetLines().Reset();
/*?*/       }
/*?*/
/*?*/       FormatFullDoc();
/*?*/       UpdateViews( GetActiveView() );
/*?*/       if ( GetUpdateMode() && GetActiveView() )
/*?*/           pActiveView->ShowCursor( sal_False, sal_False );
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::SetVertical( BOOL bVertical )
/*N*/ {
/*N*/   if ( IsVertical() != bVertical )
/*N*/   {
/*?*/       GetEditDoc().SetVertical( bVertical );
/*?*/       sal_Bool bUseCharAttribs = ( aStatus.GetControlWord() & EE_CNTRL_USECHARATTRIBS ) ? sal_True : sal_False;
/*?*/       GetEditDoc().CreateDefFont( bUseCharAttribs );
/*?*/       if ( IsFormatted() )
/*?*/       {
/*?*/           FormatFullDoc();
/*?*/           UpdateViews( GetActiveView() );
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::SeekCursor( ContentNode* pNode, sal_uInt16 nPos, SvxFont& rFont, OutputDevice* pOut, sal_uInt16 nIgnoreWhich )
/*N*/ {
/*N*/   // Es war mal geplant, SeekCursor( nStartPos, nEndPos, ... ), damit nur
/*N*/   // ab der StartPosition neu gesucht wird.
/*N*/   // Problem: Es mussten zwei Listen beruecksichtigt/gefuehrt werden:
/*N*/   // OrderedByStart,OrderedByEnd.
/*N*/
/*N*/   if ( nPos > pNode->Len() )
/*N*/       nPos = pNode->Len();
/*N*/
/*N*/   rFont = pNode->GetCharAttribs().GetDefFont();
/*N*/
/*N*/   short nScriptType = GetScriptType( EditPaM( pNode, nPos ) );
/*N*/   if ( ( nScriptType == i18n::ScriptType::ASIAN ) || ( nScriptType == i18n::ScriptType::COMPLEX ) )
/*N*/   {
/*N*/       const SvxFontItem& rFontItem = (const SvxFontItem&)pNode->GetContentAttribs().GetItem( GetScriptItemId( EE_CHAR_FONTINFO, nScriptType ) );
/*N*/       rFont.SetName( rFontItem.GetFamilyName() );
/*N*/       rFont.SetFamily( rFontItem.GetFamily() );
/*N*/       rFont.SetPitch( rFontItem.GetPitch() );
/*N*/       rFont.SetCharSet( rFontItem.GetCharSet() );
/*N*/       Size aSz( rFont.GetSize() );
/*N*/       aSz.Height() = ((const SvxFontHeightItem&)pNode->GetContentAttribs().GetItem( GetScriptItemId( EE_CHAR_FONTHEIGHT, nScriptType ) ) ).GetHeight();
/*N*/       rFont.SetSize( aSz );
/*N*/       rFont.SetWeight( ((const SvxWeightItem&)pNode->GetContentAttribs().GetItem( GetScriptItemId( EE_CHAR_WEIGHT, nScriptType ))).GetWeight() );
/*N*/       rFont.SetItalic( ((const SvxPostureItem&)pNode->GetContentAttribs().GetItem( GetScriptItemId( EE_CHAR_ITALIC, nScriptType ))).GetPosture() );
/*N*/       rFont.SetLanguage( ((const SvxLanguageItem&)pNode->GetContentAttribs().GetItem( GetScriptItemId( EE_CHAR_LANGUAGE, nScriptType ))).GetLanguage() );
/*N*/   }
/*N*/
/*N*/   sal_uInt16 nRelWidth = ((const SvxCharScaleWidthItem&)pNode->GetContentAttribs().GetItem( EE_CHAR_FONTWIDTH)).GetValue();
/*N*/
/*N*/   if ( pOut )
/*N*/   {
/*N*/       const SvxUnderlineItem& rTextLineColor = (const SvxUnderlineItem&)pNode->GetContentAttribs().GetItem( EE_CHAR_UNDERLINE );
/*N*/       if ( rTextLineColor.GetColor() != COL_TRANSPARENT )
/*?*/           pOut->SetTextLineColor( rTextLineColor.GetColor() );
/*N*/       else
/*N*/           pOut->SetTextLineColor();
/*N*/   }
/*N*/
/*N*/   const SvxLanguageItem* pCJKLanguageItem = NULL;
/*N*/
/*N*/   if ( aStatus.UseCharAttribs() )
/*N*/   {
/*N*/       const CharAttribArray& rAttribs = pNode->GetCharAttribs().GetAttribs();
/*N*/       sal_uInt16 nAttr = 0;
/*N*/       EditCharAttrib* pAttrib = GetAttrib( rAttribs, nAttr );
/*N*/       while ( pAttrib && ( pAttrib->GetStart() <= nPos ) )
/*N*/       {
/*N*/           // Beim Seeken nicht die Attr beruecksichtigen, die dort beginnen!
/*N*/           // Leere Attribute werden beruecksichtigt( verwendet), da diese
/*N*/           // gerade eingestellt wurden.
/*N*/           // 12.4.95: Doch keine Leeren Attribute verwenden:
/*N*/           // - Wenn gerade eingestellt und leer => keine Auswirkung auf Font
/*N*/           // In einem leeren Absatz eingestellte Zeichen werden sofort wirksam.
/*N*/           if ( ( pAttrib->Which() != nIgnoreWhich ) &&
/*N*/                ( ( ( pAttrib->GetStart() < nPos ) && ( pAttrib->GetEnd() >= nPos ) )
/*N*/                    || ( !pNode->Len() ) ) )
/*N*/           {
/*N*/               DBG_ASSERT( ( pAttrib->Which() >= EE_CHAR_START ) && ( pAttrib->Which() <= EE_FEATURE_END ), "Unglueltiges Attribut in Seek() " );
/*N*/               if ( IsScriptItemValid( pAttrib->Which(), nScriptType ) )
/*N*/                 {
/*N*/                   pAttrib->SetFont( rFont, pOut );
/*N*/                     // #i1550# hard color attrib should win over text color from field
/*N*/                     if ( pAttrib->Which() == EE_FEATURE_FIELD )
/*N*/                     {
/*N*/                         EditCharAttrib* pColorAttr = pNode->GetCharAttribs().FindAttrib( EE_CHAR_COLOR, nPos );
/*N*/                         if ( pColorAttr )
/*N*/                           pColorAttr->SetFont( rFont, pOut );
/*N*/                     }
/*N*/                 }
/*N*/               if ( pAttrib->Which() == EE_CHAR_FONTWIDTH )
/*N*/                   nRelWidth = ((const SvxCharScaleWidthItem*)pAttrib->GetItem())->GetValue();
/*N*/               if ( pAttrib->Which() == EE_CHAR_LANGUAGE_CJK )
/*N*/                   pCJKLanguageItem = (const SvxLanguageItem*) pAttrib->GetItem();
/*N*/           }
/*N*/           pAttrib = GetAttrib( rAttribs, ++nAttr );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( !pCJKLanguageItem )
/*N*/       pCJKLanguageItem = (const SvxLanguageItem*) &pNode->GetContentAttribs().GetItem( EE_CHAR_LANGUAGE_CJK );
/*N*/
/*N*/   rFont.SetCJKContextLanguage( pCJKLanguageItem->GetLanguage() );
/*N*/
/*N*/   if ( rFont.GetKerning() && IsKernAsianPunctuation() && ( nScriptType == i18n::ScriptType::ASIAN ) )
/*?*/       rFont.SetKerning( rFont.GetKerning() | KERNING_ASIAN );
/*N*/
/*N*/   if ( aStatus.DoNotUseColors() )
/*N*/   {
/*?*/       // Hack fuer DL,weil JOE staendig die Pooldefaults verbiegt!
/*?*/       // const SvxColorItem& rColorItem = (const SvxColorItem&)aEditDoc.GetItemPool().GetDefaultItem( EE_CHAR_COLOR );
/*?*/       rFont.SetColor( /* rColorItem.GetValue() */ COL_BLACK );
/*N*/   }
/*N*/
/*N*/   if ( aStatus.DoStretch() || ( nRelWidth != 100 ) )
/*N*/   {
/*N*/       // Fuer das aktuelle Ausgabegeraet, weil es sonst bei einem
/*N*/       // Drucker als RefDev auf dem Bildschirm #?!@' aussieht!
/*N*/       OutputDevice* pDev = pOut ? pOut : GetRefDevice();
/*N*/       rFont.SetPhysFont( pDev );
/*N*/       FontMetric aMetric( pDev->GetFontMetric() );
/*N*/       // Fuer die Hoehe nicht die Metriken nehmen, da das bei
/*N*/       // Hoch-/Tiefgestellt schief geht.
/*N*/       Size aRealSz( aMetric.GetSize().Width(), rFont.GetSize().Height() );
/*N*/       if ( aStatus.DoStretch() )
/*N*/       {
/*?*/           if ( nStretchY != 100 )
/*?*/           {
/*?*/               aRealSz.Height() *= nStretchY;
/*?*/               aRealSz.Height() /= 100;
/*?*/           }
/*?*/           if ( nStretchX != 100 )
/*?*/           {
/*?*/               aRealSz.Width() *= nStretchX;
/*?*/               aRealSz.Width() /= 100;
/*?*/
/*?*/               // Auch das Kerning: (long wegen Zwischenergebnis)
/*?*/               long nKerning = rFont.GetFixKerning();
/*
                Die Ueberlegung war: Wenn neg. Kerning, aber StretchX = 200
                => Nicht das Kerning verdoppelt, also die Buchstaben weiter
                zusammenziehen
                ---------------------------
                Kern    StretchX    =>Kern
                ---------------------------
                 >0     <100        < (Proportional)
                 <0     <100        < (Proportional)
                 >0     >100        > (Proportional)
                 <0     >100        < (Der Betrag, also Antiprop)
*/
/*?*/               if ( ( nKerning < 0  ) && ( nStretchX > 100 ) )
/*?*/               {
/*?*/                   // Antiproportional
/*?*/                   nKerning *= 100;
/*?*/                   nKerning /= nStretchX;
/*?*/               }
/*?*/               else if ( nKerning )
/*?*/               {
/*?*/                   // Proportional
/*?*/                   nKerning *= nStretchX;
/*?*/                   nKerning /= 100;
/*?*/               }
/*?*/               rFont.SetFixKerning( (short)nKerning );
/*?*/           }
/*N*/       }
/*N*/       if ( nRelWidth != 100 )
/*N*/       {
/*N*/           aRealSz.Width() *= nRelWidth;
/*N*/           aRealSz.Width() /= 100;
/*N*/       }
/*N*/       rFont.SetSize( aRealSz );
/*N*/       // Font wird nicht restauriert...
/*N*/   }
/*N*/
/*N*/   if ( ( ( rFont.GetColor() == COL_AUTO ) || ( IsForceAutoColor() ) ) && pOut )
/*N*/   {
/*N*/         if ( IsAutoColorEnabled() && ( pOut->GetOutDevType() != OUTDEV_PRINTER ) )
/*N*/         {
/*N*/             // Never use WindowTextColor on the printer
/*N*/           rFont.SetColor( GetAutoColor() );
/*N*/         }
/*N*/         else
/*N*/         {
/*?*/           if ( ( GetBackgroundColor() != COL_AUTO ) && GetBackgroundColor().IsDark() )
/*?*/                 rFont.SetColor( COL_WHITE );
/*?*/             else
/*?*/                 rFont.SetColor( COL_BLACK );
/*N*/         }
/*N*/   }
/*N*/
/*N*/   if ( mpIMEInfos && mpIMEInfos->pAttribs && ( mpIMEInfos->aPos.GetNode() == pNode ) &&
/*N*/       ( nPos > mpIMEInfos->aPos.GetIndex() ) && ( nPos <= ( mpIMEInfos->aPos.GetIndex() + mpIMEInfos->nLen ) ) )
/*N*/   {
/*?*/       sal_uInt16 nAttr = mpIMEInfos->pAttribs[ nPos - mpIMEInfos->aPos.GetIndex() - 1 ];
/*?*/       if ( nAttr & EXTTEXTINPUT_ATTR_UNDERLINE )
/*?*/           rFont.SetUnderline( UNDERLINE_SINGLE );
/*?*/       else if ( nAttr & EXTTEXTINPUT_ATTR_BOLDUNDERLINE )
/*?*/           rFont.SetUnderline( UNDERLINE_BOLD );
/*?*/       else if ( nAttr & EXTTEXTINPUT_ATTR_DOTTEDUNDERLINE )
/*?*/           rFont.SetUnderline( UNDERLINE_DOTTED );
/*?*/       else if ( nAttr & EXTTEXTINPUT_ATTR_DASHDOTUNDERLINE )
/*?*/           rFont.SetUnderline( UNDERLINE_DOTTED );
/*?*/       else if ( nAttr & EXTTEXTINPUT_ATTR_REDTEXT )
/*?*/           rFont.SetColor( Color( COL_RED ) );
/*?*/       else if ( nAttr & EXTTEXTINPUT_ATTR_HALFTONETEXT )
/*?*/           rFont.SetColor( Color( COL_LIGHTGRAY ) );
/*?*/       if ( nAttr & EXTTEXTINPUT_ATTR_HIGHLIGHT )
/*?*/       {
/*?*/           const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
/*?*/           rFont.SetColor( rStyleSettings.GetHighlightTextColor() );
/*?*/           rFont.SetFillColor( rStyleSettings.GetHighlightColor() );
/*?*/           rFont.SetTransparent( FALSE );
/*?*/       }
/*?*/       else if ( nAttr & EXTTEXTINPUT_ATTR_GRAYWAVELINE )
/*?*/       {
/*?*/           rFont.SetUnderline( UNDERLINE_WAVE );
/*?*/           if( pOut )
/*?*/               pOut->SetTextLineColor( Color( COL_LIGHTGRAY ) );
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::RecalcFormatterFontMetrics( FormatterFontMetric& rCurMetrics, SvxFont& rFont )
/*N*/ {
/*N*/   // Fuer Zeilenhoehe bei Hoch/Tief erstmal ohne Propr!
/*N*/   sal_uInt16 nPropr = rFont.GetPropr();
/*N*/   DBG_ASSERT( ( nPropr == 100 ) || rFont.GetEscapement(), "Propr ohne Escape?!" );
/*N*/   if ( nPropr != 100 )
/*N*/   {
/*N*/       rFont.SetPropr( 100 );
/*N*/       rFont.SetPhysFont( pRefDev );
/*N*/   }
/*N*/   FontMetric aMetric( pRefDev->GetFontMetric() );
/*N*/
/*N*/   sal_uInt16 nAscent = (sal_uInt16)aMetric.GetAscent();
/*N*/   sal_uInt16 nDescent = (sal_uInt16)aMetric.GetDescent();
/*N*/   sal_uInt16 nLeading = ( aMetric.GetIntLeading() > 0 ) ? (sal_uInt16)aMetric.GetIntLeading() : 0;
/*N*/   // Fonts ohne Leading bereiten Probleme
/*N*/   if ( ( nLeading == 0 ) && ( pRefDev->GetOutDevType() == OUTDEV_PRINTER ) )
/*N*/   {
/*N*/       // Da schaun wir mal, was fuer eine Leading ich auf dem
/*N*/       // Bildschirm erhalte
/*N*/       VirtualDevice* pVDev = GetVirtualDevice( pRefDev->GetMapMode() );
/*N*/       rFont.SetPhysFont( pVDev );
/*N*/       aMetric = pVDev->GetFontMetric();
/*N*/
/*N*/       // Damit sich die Leading nicht wieder rausrechnet,
/*N*/       // wenn die ganze Zeile den Font hat, nTmpLeading.
/*N*/
/*N*/       // 4/96: Kommt bei HP Laserjet 4V auch nicht hin
/*N*/       // => Werte komplett vom Bildschirm holen.
/*N*/ //        sal_uInt16 nTmpLeading = (sal_uInt16)aMetric.GetIntLeading();
/*N*/ //        nAscent += nTmpLeading;
/*N*/       nAscent = (sal_uInt16)aMetric.GetAscent();
/*N*/       nDescent = (sal_uInt16)aMetric.GetDescent();
/*N*/ //        nLeading = (sal_uInt16)aMetric.GetIntLeading();
/*N*/   }
/*N*/   if ( nAscent > rCurMetrics.nMaxAscent )
/*N*/       rCurMetrics.nMaxAscent = nAscent;
/*N*/   if ( nDescent > rCurMetrics.nMaxDescent )
/*N*/       rCurMetrics.nMaxDescent= nDescent;
/*N*/
/*N*/   // Sonderbehandlung Hoch/Tief:
/*N*/   if ( rFont.GetEscapement() )
/*N*/   {
/*N*/       // Jetzt unter Beruecksichtigung von Escape/Propr
/*N*/       // Ascent oder Descent ggf vergroessern
/*N*/       short nDiff = (short)(rFont.GetSize().Height()*rFont.GetEscapement()/100L);
/*N*/       if ( rFont.GetEscapement() > 0 )
/*N*/       {
/*N*/           nAscent = (sal_uInt16) (((long)nAscent)*nPropr/100 + nDiff);
/*N*/           if ( nAscent > rCurMetrics.nMaxAscent )
/*N*/               rCurMetrics.nMaxAscent = nAscent;
/*N*/       }
/*N*/       else    // muss < 0 sein
/*N*/       {
/*N*/           nDescent = (sal_uInt16) (((long)nDescent)*nPropr/100 - nDiff);
/*N*/           if ( nDescent > rCurMetrics.nMaxDescent )
/*N*/               rCurMetrics.nMaxDescent= nDescent;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::Paint( OutputDevice* pOutDev, Rectangle aClipRec, Point aStartPos, sal_Bool bStripOnly, short nOrientation )
/*N*/ {
/*N*/   if ( !GetUpdateMode() && !bStripOnly )
/*N*/       return;
/*N*/
/*N*/   if ( !IsFormatted() )
/*?*/       FormatDoc();
/*N*/
/*N*/   long nFirstVisXPos = - pOutDev->GetMapMode().GetOrigin().X();
/*N*/   long nFirstVisYPos = - pOutDev->GetMapMode().GetOrigin().Y();
/*N*/
/*N*/   EditLine* pLine;
/*N*/   Point aTmpPos;
/*N*/     Point aRedLineTmpPos;
/*N*/   DBG_ASSERT( GetParaPortions().Count(), "Keine ParaPortion?!" );
/*N*/   SvxFont aTmpFont( GetParaPortions()[0]->GetNode()->GetCharAttribs().GetDefFont() );
/*N*/   Font aOldFont( pOutDev->GetFont() );
/*N*/   // Bei gedrehtem Text wird aStartPos als TopLeft angesehen, da andere
/*N*/   // Informationen fehlen, und sowieso das ganze Object ungescrollt
/*N*/   // dargestellt wird.
/*N*/   // Das Rechteck ist unendlich gross.
/*N*/   Point aOrigin( aStartPos );
/*N*/   double nCos, nSin;
/*N*/   if ( nOrientation )
/*N*/   {
/*?*/       double nRealOrientation = nOrientation*F_PI1800;
/*?*/       nCos = cos( nRealOrientation );
/*?*/       nSin = sin( nRealOrientation );
/*N*/   }
/*N*/
/*N*/   // Fuer OnlineSpelling:
/*N*/ //    EditPaM aCursorPos;
/*N*/ //    if( GetStatus().DoOnlineSpelling() && pActiveView )
/*N*/ //        aCurPos = pActiveView->pImpEditView->GetEditSelections().Max();
/*N*/
/*N*/   // --------------------------------------------------
/*N*/   // Ueber alle Absaetze...
/*N*/   // --------------------------------------------------
/*N*/   for ( sal_uInt16 n = 0; n < GetParaPortions().Count(); n++ )
/*N*/   {
/*N*/       ParaPortion* pPortion = GetParaPortions().GetObject( n );
/*N*/       DBG_ASSERT( pPortion, "NULL-Pointer in TokenList in Paint" );
/*N*/       // falls beim Tippen Idle-Formatierung, asynchrones Paint.
/*N*/       // Unsichtbare Portions koennen ungueltig sein.
/*N*/       if ( pPortion->IsVisible() && pPortion->IsInvalid() )
/*N*/           return;
/*N*/       long nParaHeight = pPortion->GetHeight();
/*N*/       sal_uInt16 nIndex = 0;
/*N*/       if ( pPortion->IsVisible() && (
/*N*/               ( !IsVertical() && ( ( aStartPos.Y() + nParaHeight ) > aClipRec.Top() ) ) ||
/*N*/               ( IsVertical() && ( ( aStartPos.X() - nParaHeight ) < aClipRec.Right() ) ) ) )
/*N*/
/*N*/       {
/*N*/           // --------------------------------------------------
/*N*/           // Ueber die Zeilen des Absatzes...
/*N*/           // --------------------------------------------------
/*N*/           sal_uInt16 nLines = pPortion->GetLines().Count();
/*N*/           sal_uInt16 nLastLine = nLines-1;
/*N*/
/*N*/           if ( !IsVertical() )
/*N*/               aStartPos.Y() += pPortion->GetFirstLineOffset();
/*N*/           else
/*?*/               aStartPos.X() -= pPortion->GetFirstLineOffset();
/*N*/
/*N*/             Point aParaStart( aStartPos );
/*N*/
/*N*/             const SvxLineSpacingItem& rLSItem = ((const SvxLineSpacingItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL ));
/*N*/           sal_uInt16 nSBL = ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_FIX )
/*N*/                               ? GetYValue( rLSItem.GetInterLineSpace() ) : 0;
/*N*/           for ( sal_uInt16 nLine = 0; nLine < nLines; nLine++ )
/*N*/           {
/*N*/               pLine = pPortion->GetLines().GetObject(nLine);
/*N*/               DBG_ASSERT( pLine, "NULL-Pointer im Zeileniterator in UpdateViews" );
/*N*/               aTmpPos = aStartPos;
/*N*/               if ( !IsVertical() )
/*N*/               {
/*N*/                   aTmpPos.X() += pLine->GetStartPosX();
/*N*/                   aTmpPos.Y() += pLine->GetMaxAscent();
/*N*/                   aStartPos.Y() += pLine->GetHeight();
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   aTmpPos.Y() += pLine->GetStartPosX();
/*?*/                   aTmpPos.X() -= pLine->GetMaxAscent();
/*?*/                   aStartPos.X() -= pLine->GetHeight();
/*N*/               }
/*N*/
/*N*/               if ( ( !IsVertical() && ( aStartPos.Y() > aClipRec.Top() ) )
/*N*/                   || ( IsVertical() && aStartPos.X() < aClipRec.Right() ) )
/*N*/               {
/*N*/                   if ( ( nLine == 0 ) && !bStripOnly )    // erste Zeile
/*N*/                   {
/*N*/                       // VERT???
/*N*/                       GetEditEnginePtr()->PaintingFirstLine( n, aParaStart, aTmpPos.Y(), aOrigin, nOrientation, pOutDev );
/*N*/                   }
/*N*/                   // --------------------------------------------------
/*N*/                   // Ueber die Portions der Zeile...
/*N*/                   // --------------------------------------------------
/*N*/                   nIndex = pLine->GetStart();
/*N*/                   for ( sal_uInt16 y = pLine->GetStartPortion(); y <= pLine->GetEndPortion(); y++ )
/*N*/                   {
/*N*/                       DBG_ASSERT( pPortion->GetTextPortions().Count(), "Zeile ohne Textportion im Paint!" );
/*N*/                       TextPortion* pTextPortion = pPortion->GetTextPortions().GetObject( y );
/*N*/                       DBG_ASSERT( pTextPortion, "NULL-Pointer im Portioniterator in UpdateViews" );
/*N*/
/*N*/                         long nPortionXOffset = GetPortionXOffset( pPortion, pLine, y );
/*N*/                       if ( !IsVertical() )
/*N*/                         {
/*N*/                           aTmpPos.X() = aStartPos.X() + nPortionXOffset;
/*N*/                             if ( aTmpPos.X() > aClipRec.Right() )
/*N*/                                 break;    // Keine weitere Ausgabe in Zeile noetig
/*N*/                         }
/*N*/                       else
/*N*/                         {
/*?*/                           aTmpPos.Y() = aStartPos.Y() + nPortionXOffset;
/*?*/                             if ( aTmpPos.Y() > aClipRec.Bottom() )
/*?*/                                 break;    // Keine weitere Ausgabe in Zeile noetig
/*N*/                         }
/*N*/
/*N*/                         // R2L replaces with obove...
/*N*/                         // New position after processing R2L text...
/*N*/ // R2L                        if ( nR2LWidth && !pTextPortion->GetRightToLeft() )
/*N*/ // R2L                        {
/*N*/ // R2L                            if ( !IsVertical() )
/*N*/ // R2L                                aTmpPos.X() += nR2LWidth;
/*N*/ // R2L                            else
/*N*/ // R2L                                aTmpPos.Y() += nR2LWidth;
/*N*/ // R2L
/*N*/ // R2L                            nR2LWidth = 0;
/*N*/ // R2L                        }
/*N*/
/*N*/                       switch ( pTextPortion->GetKind() )
/*N*/                       {
/*N*/                           case PORTIONKIND_TEXT:
/*N*/                           case PORTIONKIND_FIELD:
/*N*/                           case PORTIONKIND_HYPHENATOR:
/*N*/                             {
/*N*/                               SeekCursor( pPortion->GetNode(), nIndex+1, aTmpFont, pOutDev );
/*N*/
/*N*/                                 BOOL bDrawFrame = FALSE;
/*N*/
/*N*/                                 if ( ( pTextPortion->GetKind() == PORTIONKIND_FIELD ) && !aTmpFont.IsTransparent() &&
/*N*/                                      ( GetBackgroundColor() != COL_AUTO ) && GetBackgroundColor().IsDark() &&
/*N*/                                      ( IsAutoColorEnabled() && ( pOutDev->GetOutDevType() != OUTDEV_PRINTER ) ) )
/*N*/                               {
/*?*/                                     aTmpFont.SetTransparent( TRUE );
/*?*/                                     pOutDev->SetFillColor();
/*?*/                                     pOutDev->SetLineColor( GetAutoColor() );
/*?*/                                     bDrawFrame = TRUE;
/*N*/                               }
/*N*/
/*N*/ #ifdef EDITDEBUG
/*N*/                               if ( pTextPortion->GetKind() == PORTIONKIND_HYPHENATOR )
/*N*/                               {
/*N*/                                   aTmpFont.SetFillColor( COL_LIGHTGRAY );
/*N*/                                   aTmpFont.SetTransparent( sal_False );
/*N*/                               }
/*N*/                                 if ( pTextPortion->GetRightToLeft()  )
/*N*/                               {
/*N*/                                   aTmpFont.SetFillColor( COL_LIGHTGRAY );
/*N*/                                   aTmpFont.SetTransparent( sal_False );
/*N*/                               }
/*N*/                                 else if ( GetScriptType( EditPaM( pPortion->GetNode(), nIndex+1 ) ) == i18n::ScriptType::COMPLEX )
/*N*/                               {
/*N*/                                   aTmpFont.SetFillColor( COL_LIGHTCYAN );
/*N*/                                   aTmpFont.SetTransparent( sal_False );
/*N*/                               }
/*N*/ #endif
/*N*/                               aTmpFont.SetPhysFont( pOutDev );
/*N*/
/*N*/                                 ULONG nOldLayoutMode = pOutDev->GetLayoutMode();
/*N*/                                 ImplInitLayoutMode( pOutDev, n, nIndex );
/*N*/
/*N*/                               XubString aText;
/*N*/                                 USHORT nTextStart = 0;
/*N*/                                 USHORT nTextLen = 0;
/*N*/                               const long* pDXArray = 0;
/*N*/                               long* pTmpDXArray = 0;
/*N*/
/*N*/                               if ( pTextPortion->GetKind() == PORTIONKIND_TEXT )
/*N*/                               {
/*N*/                                   aText = *pPortion->GetNode();
/*N*/                                     nTextStart = nIndex;
/*N*/                                     nTextLen = pTextPortion->GetLen();
/*N*/                                   pDXArray = pLine->GetCharPosArray().GetData()+( nIndex-pLine->GetStart() );
/*N*/                               }
/*N*/                               else if ( pTextPortion->GetKind() == PORTIONKIND_FIELD )
/*N*/                               {
/*?*/                                   EditCharAttrib* pAttr = pPortion->GetNode()->GetCharAttribs().FindFeature( nIndex );
/*?*/                                   DBG_ASSERT( pAttr, "Feld nicht gefunden" );
/*?*/                                   DBG_ASSERT( pAttr && pAttr->GetItem()->ISA( SvxFieldItem ), "Feld vom falschen Typ!" );
/*?*/                                   aText = ((EditCharAttribField*)pAttr)->GetFieldValue();
/*?*/                                     nTextStart = 0;
/*?*/                                     nTextLen = aText.Len();
/*?*/
/*?*/                                   pTmpDXArray = new long[ aText.Len() ];
/*?*/                                   pDXArray = pTmpDXArray;
/*?*/                                   Font aOldFont( GetRefDevice()->GetFont() );
/*?*/                                   aTmpFont.SetPhysFont( GetRefDevice() );
/*?*/                                   aTmpFont.QuickGetTextSize( GetRefDevice(), aText, 0, aText.Len(), pTmpDXArray );
/*?*/                                   if ( aStatus.DoRestoreFont() )
/*?*/                                       GetRefDevice()->SetFont( aOldFont );
/*?*/
/*?*/                                   // add a meta file comment if we record to a metafile
/*?*/                                   GDIMetaFile* pMtf = pOutDev->GetConnectMetaFile();
/*?*/                                   if( pMtf )
/*?*/                                   {
/*?*/                                       SvxFieldItem* pFieldItem = PTR_CAST( SvxFieldItem, pAttr->GetItem() );
/*?*/
/*?*/                                       if( pFieldItem )
/*?*/                                       {
/*?*/                                           const SvxFieldData* pFieldData = pFieldItem->GetField();
/*?*/                                           if( pFieldData )
/*?*/                                               {DBG_ASSERT(0, "STRIP");}//STRIP001 pMtf->AddAction( pFieldData->createBeginComment() );
/*?*/                                       }
/*?*/                                   }
/*?*/
/*?*/                               }
/*N*/                               else if ( pTextPortion->GetKind() == PORTIONKIND_HYPHENATOR )
/*N*/                               {
/*N*/                                   if ( pTextPortion->GetExtraValue() )
/*N*/                                       aText = pTextPortion->GetExtraValue();
/*N*/                                   aText += CH_HYPH;
/*N*/                                     nTextStart = 0;
/*N*/                                     nTextLen = aText.Len();
/*N*/                               }
/*N*/
/*N*/                               long nTxtWidth = pTextPortion->GetSize().Width();
/*N*/
/*N*/                               Point aOutPos( aTmpPos );
/*N*/                                 aRedLineTmpPos = aTmpPos;
/*N*/ //L2R                                if ( pTextPortion->GetRightToLeft() )
/*N*/ //L2R                                {
/*N*/ //L2R                                    sal_uInt16 nNextPortion = y+1;
/*N*/ //L2R                                    while ( nNextPortion <= pLine->GetEndPortion() )
/*N*/ //L2R                                    {
/*N*/ //L2R                                     TextPortion* pNextTextPortion = pPortion->GetTextPortions().GetObject( nNextPortion );
/*N*/ //L2R                                        if ( pNextTextPortion->GetRightToLeft() )
/*N*/ //L2R                                        {
/*N*/ //L2R                                         if ( !IsVertical() )
/*N*/ //L2R                                                aOutPos.X() += pNextTextPortion->GetSize().Width();
/*N*/ //L2R                                         else
/*N*/ //L2R                                                aOutPos.Y() += pNextTextPortion->GetSize().Width();
/*N*/ //L2R                                        }
/*N*/ //L2R                                        else
/*N*/ //L2R                                            break;
/*N*/ //L2R                                        nNextPortion++;
/*N*/ //L2R                                    }
/*N*/ //L2R                                }
/*N*/                               if ( bStripOnly )
/*N*/                               {
/*N*/                                   // VERT???
/*N*/                                   GetEditEnginePtr()->DrawingText( aOutPos, aText, nTextStart, nTextLen, pDXArray, aTmpFont, n, nIndex, pTextPortion->GetRightToLeft() );
/*N*/                               }
/*N*/                               else
/*N*/                               {
/*N*/                                   short nEsc = aTmpFont.GetEscapement();
/*N*/                                   if ( nOrientation )
/*N*/                                   {
/*?*/                                       DBG_ASSERT(0, "STRIP"); //STRIP001 // Bei Hoch/Tief selbst Hand anlegen:
//STRIP001 /*?*/                                        if ( aTmpFont.GetEscapement() )
//STRIP001 /*?*/                                        {
//STRIP001 /*?*/                                             long nDiff = aTmpFont.GetSize().Height() * aTmpFont.GetEscapement() / 100L;
//STRIP001 /*?*/                                             if ( !IsVertical() )
//STRIP001 /*?*/                                                aOutPos.Y() -= nDiff;
//STRIP001 /*?*/                                             else
//STRIP001 /*?*/                                                 aOutPos.X() += nDiff;
//STRIP001 /*?*/                                             aRedLineTmpPos = aOutPos;
//STRIP001 /*?*/                                            aTmpFont.SetEscapement( 0 );
//STRIP001 /*?*/                                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                                         aOutPos = lcl_ImplCalcRotatedPos( aOutPos, aOrigin, nSin, nCos );
//STRIP001 /*?*/                                        aTmpFont.SetOrientation( aTmpFont.GetOrientation()+nOrientation );
//STRIP001 /*?*/                                        aTmpFont.SetPhysFont( pOutDev );
//STRIP001 /*?*/
/*N*/                                   }
/*N*/                                   // nur ausgeben, was im sichtbaren Bereich beginnt:
/*N*/                                   // Wichtig, weil Bug bei einigen Grafikkarten bei transparentem Font, Ausgabe bei neg.
/*N*/                                   if ( nOrientation || ( !IsVertical() && ( ( aTmpPos.X() + nTxtWidth ) >= nFirstVisXPos ) )
/*N*/                                           || ( IsVertical() && ( ( aTmpPos.Y() + nTxtWidth ) >= nFirstVisYPos ) ) )
/*N*/                                   {
/*N*/                                       if ( nEsc && ( ( aTmpFont.GetUnderline() != UNDERLINE_NONE ) ) )
/*N*/                                       {
/*?*/                                           // Das Hoch/Tief ohne Underline malen, das Underline
/*?*/                                           // auf der BaseLine der Original-Fonthoehe ausgeben...
/*?*/
/*?*/                                           // Aber nur, wenn davor auch Unterstrichen!
/*?*/                                           sal_Bool bSpecialUnderline = sal_False;
/*?*/                                           EditCharAttrib* pPrev = pPortion->GetNode()->GetCharAttribs().FindAttrib( EE_CHAR_ESCAPEMENT, nIndex );
/*?*/                                           if ( pPrev )
/*?*/                                           {
/*?*/                                               SvxFont aDummy;
/*?*/                                               // Unterstreichung davor?
/*?*/                                               if ( pPrev->GetStart() )
/*?*/                                               {
/*?*/                                                   SeekCursor( pPortion->GetNode(), pPrev->GetStart(), aDummy );
/*?*/                                                   if ( aDummy.GetUnderline() != UNDERLINE_NONE )
/*?*/                                                       bSpecialUnderline = sal_True;
/*?*/                                               }
/*?*/                                               if ( !bSpecialUnderline && ( pPrev->GetEnd() < pPortion->GetNode()->Len() ) )
/*?*/                                               {
/*?*/                                                   SeekCursor( pPortion->GetNode(), pPrev->GetEnd()+1, aDummy );
/*?*/                                                   if ( aDummy.GetUnderline() != UNDERLINE_NONE )
/*?*/                                                       bSpecialUnderline = sal_True;
/*?*/                                               }
/*?*/                                           }
/*?*/                                           if ( bSpecialUnderline )
/*?*/                                           {
/*?*/                                               DBG_ASSERT(0, "STRIP"); //STRIP001 Size aSz = aTmpFont.GetPhysTxtSize( pOutDev, aText, nTextStart, nTextLen );
//STRIP001 /*?*/                                                BYTE nProp = aTmpFont.GetPropr();
//STRIP001 /*?*/                                                aTmpFont.SetEscapement( 0 );
//STRIP001 /*?*/                                                aTmpFont.SetPropr( 100 );
//STRIP001 /*?*/                                                aTmpFont.SetPhysFont( pOutDev );
//STRIP001 /*?*/                                                String aBlanks;
//STRIP001 /*?*/                                                aBlanks.Fill( nTextLen, ' ' );
//STRIP001 /*?*/                                                Point aUnderlinePos( aOutPos );
//STRIP001 /*?*/                                                if ( nOrientation )
//STRIP001 /*?*/                                                {DBG_ASSERT(0, "STRIP");} //STRIP001    aUnderlinePos = lcl_ImplCalcRotatedPos( aTmpPos, aOrigin, nSin, nCos );
//STRIP001 /*?*/                                                pOutDev->DrawStretchText( aUnderlinePos, aSz.Width(), aBlanks, 0, nTextLen );
//STRIP001 /*?*/
//STRIP001 /*?*/                                                aTmpFont.SetUnderline( UNDERLINE_NONE );
//STRIP001 /*?*/                                                if ( !nOrientation )
//STRIP001 /*?*/                                                    aTmpFont.SetEscapement( nEsc );
//STRIP001 /*?*/                                                aTmpFont.SetPropr( nProp );
//STRIP001 /*?*/                                                aTmpFont.SetPhysFont( pOutDev );
/*?*/                                           }
/*N*/                                       }
/*N*/                                         Point aRealOutPos( aOutPos );
/*N*/                                         if ( ( pTextPortion->GetKind() == PORTIONKIND_TEXT )
/*N*/                                                && pTextPortion->GetExtraInfos() && pTextPortion->GetExtraInfos()->bCompressed
/*N*/                                                && pTextPortion->GetExtraInfos()->bFirstCharIsRightPunktuation )
/*N*/                                         {
/*?*/                                             aRealOutPos.X() += pTextPortion->GetExtraInfos()->nPortionOffsetX;
/*N*/                                         }
/*N*/
/*N*/                                       aTmpFont.QuickDrawText( pOutDev, aRealOutPos, aText, nTextStart, nTextLen, pDXArray );
/*N*/                                         if ( bDrawFrame )
/*N*/                                         {
/*?*/                                             Point aTopLeft( aTmpPos );
/*?*/                                             aTopLeft.Y() -= pLine->GetMaxAscent();
/*?*/                                           if ( nOrientation )
/*?*/                                           {DBG_ASSERT(0, "STRIP");} //STRIP001       aTopLeft = lcl_ImplCalcRotatedPos( aTopLeft, aOrigin, nSin, nCos );
/*?*/                                             Rectangle aRect( aTopLeft, pTextPortion->GetSize() );
/*?*/                                             pOutDev->DrawRect( aRect );
/*N*/                                         }
/*N*/                                   }
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/                                   if ( GetStatus().DoOnlineSpelling() && GetStatus().DoDrawRedLines() && pPortion->GetNode()->GetWrongList()->HasWrongs() && pTextPortion->GetLen() )
/*N*/                                   {
/*?*/ {DBG_ASSERT(0, "STRIP"); }//STRIP001 /*?*/                                         {//#105750# adjust LinePos for superscript or subscript text
//STRIP001 /*?*/                                             short nEsc = aTmpFont.GetEscapement();
//STRIP001 /*?*/                                             if( nEsc )
//STRIP001 /*?*/                                             {
//STRIP001 /*?*/                                                 long nShift = ((nEsc*long(aTmpFont.GetSize().Height()))/ 100L);
//STRIP001 /*?*/                                                 if( !IsVertical() )
//STRIP001 /*?*/                                                     aRedLineTmpPos.Y() -= nShift;
//STRIP001 /*?*/                                                 else
//STRIP001 /*?*/                                                     aRedLineTmpPos.X() += nShift;
//STRIP001 /*?*/                                             }
//STRIP001 /*?*/                                         }
//STRIP001 /*?*/                                        Color aOldColor( pOutDev->GetLineColor() );
//STRIP001 /*?*/                                         pOutDev->SetLineColor( Color( GetColorConfig().GetColorValue( svtools::SPELL ).nColor ) );
//STRIP001 /*?*/                                        lcl_DrawRedLines( pOutDev, aTmpFont.GetSize().Height(), aRedLineTmpPos, nIndex, nIndex + pTextPortion->GetLen(), pDXArray, pPortion->GetNode()->GetWrongList(), nOrientation, aOrigin, IsVertical() );
//STRIP001 /*?*/                                        pOutDev->SetLineColor( aOldColor );
/*N*/                                   }
/*N*/ #endif // !SVX_LIGHT
/*N*/                               }
/*N*/
/*N*/                                 pOutDev->SetLayoutMode( nOldLayoutMode );
/*N*/
/*N*/                                 if ( pTmpDXArray )
/*?*/                                   delete[] pTmpDXArray;
/*N*/
/*N*/ // R2L                                if ( !pTextPortion->GetRightToLeft() )
/*N*/ // R2L                                {
/*N*/ // R2L                                    if ( !IsVertical() )
/*N*/ // R2L                                        aTmpPos.X() += nTxtWidth;
/*N*/ // R2L                                    else
/*N*/ // R2L                                        aTmpPos.Y() += nTxtWidth;
/*N*/ // R2L                                }
/*N*/ // R2L                                else
/*N*/ // R2L                                {
/*N*/ // R2L                                    nR2LWidth += nTxtWidth;
/*N*/ // R2L                                }
/*N*/
/*N*/                               if ( pTextPortion->GetKind() == PORTIONKIND_FIELD )
/*N*/                               {
/*?*/                                   EditCharAttrib* pAttr = pPortion->GetNode()->GetCharAttribs().FindFeature( nIndex );
/*?*/                                   DBG_ASSERT( pAttr, "Feld nicht gefunden" );
/*?*/                                   DBG_ASSERT( pAttr && pAttr->GetItem()->ISA( SvxFieldItem ), "Feld vom falschen Typ!" );
/*?*/
/*?*/                                   // add a meta file comment if we record to a metafile
/*?*/                                   GDIMetaFile* pMtf = pOutDev->GetConnectMetaFile();
/*?*/                                   if( pMtf )
/*?*/                                   {
/*?*/                                       SvxFieldItem* pFieldItem = PTR_CAST( SvxFieldItem, pAttr->GetItem() );
/*?*/
/*?*/                                       if( pFieldItem )
/*?*/                                       {
/*?*/                                           const SvxFieldData* pFieldData = pFieldItem->GetField();
/*?*/                                           if( pFieldData )
/*?*/                                               {DBG_ASSERT(0, "STRIP");}//STRIP001 pMtf->AddAction( pFieldData->createEndComment() );
/*?*/                                       }
/*?*/                                   }
/*?*/
/*N*/                               }
/*N*/
/*N*/                           }
/*N*/                           break;
/*N*/ //                            case PORTIONKIND_EXTRASPACE:
/*N*/                           case PORTIONKIND_TAB:
/*N*/                           {
/*?*/                               if ( pTextPortion->GetExtraValue() && ( pTextPortion->GetExtraValue() != ' ' ) )
/*?*/                               {
/*?*/                                     SeekCursor( pPortion->GetNode(), nIndex+1, aTmpFont, pOutDev );
/*?*/                                   aTmpFont.SetTransparent( sal_False );
/*?*/                                   aTmpFont.SetEscapement( 0 );
/*?*/                                   aTmpFont.SetPhysFont( pOutDev );
/*?*/                                   long nCharWidth = aTmpFont.QuickGetTextSize( pOutDev, pTextPortion->GetExtraValue(), 0, 1, NULL ).Width();
/*?*/                                   long nChars = pTextPortion->GetSize().Width() / nCharWidth;
/*?*/                                   if ( nChars < 2 )
/*?*/                                       nChars = 2; // wird durch DrawStretchText gestaucht.
/*?*/                                   else if ( nChars == 2 )
/*?*/                                       nChars = 3; // sieht besser aus
/*?*/
/*?*/                                   String aText;
/*?*/                                   aText.Fill( (USHORT)nChars, pTextPortion->GetExtraValue() );
/*?*/                                   pOutDev->DrawStretchText( aTmpPos, pTextPortion->GetSize().Width(), aText );
/*?*/                               }
/*?*/ // R2L                                if ( !IsVertical() )
/*?*/ // R2L                                    aTmpPos.X() += pTextPortion->GetSize().Width();
/*?*/ // R2L                                else
/*?*/ // R2L                                    aTmpPos.Y() += pTextPortion->GetSize().Width();
/*N*/                           }
/*N*/                           break;
/*N*/                       }
/*N*/ // R2L                        if ( !IsVertical() && ( aTmpPos.X() > aClipRec.Right() ) )
/*N*/ // R2L                            break;  // Keine weitere Ausgabe in Zeile noetig
/*N*/ // R2L                        else if ( IsVertical() && ( aTmpPos.Y() > aClipRec.Bottom() ) )
/*N*/ // R2L                            break;  // Keine weitere Ausgabe in Zeile noetig
/*N*/                       nIndex += pTextPortion->GetLen();
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               if ( ( nLine != nLastLine ) && !aStatus.IsOutliner() )
/*N*/               {
/*?*/                   if ( !IsVertical() )
/*?*/                       aStartPos.Y() += nSBL;
/*?*/                   else
/*?*/                       aStartPos.X() -= nSBL;
/*N*/               }
/*N*/
/*N*/               // keine sichtbaren Aktionen mehr?
/*N*/               if ( !IsVertical() && ( aStartPos.Y() >= aClipRec.Bottom() ) )
/*N*/                   break;
/*N*/               else if ( IsVertical() && ( aStartPos.X() <= aClipRec.Left() ) )
/*N*/                   break;
/*N*/           }
/*N*/
/*N*/           if ( !aStatus.IsOutliner() )
/*N*/           {
/*N*/               const SvxULSpaceItem& rULItem = (const SvxULSpaceItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_ULSPACE );
/*N*/               long nUL = GetYValue( rULItem.GetLower() );
/*N*/               if ( !IsVertical() )
/*N*/                   aStartPos.Y() += nUL;
/*N*/               else
/*N*/                   aStartPos.X() -= nUL;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           if ( !IsVertical() )
/*?*/               aStartPos.Y() += nParaHeight;
/*?*/           else
/*?*/               aStartPos.X() -= nParaHeight;
/*N*/       }
/*N*/
/*N*/       // keine sichtbaren Aktionen mehr?
/*N*/       if ( !IsVertical() && ( aStartPos.Y() > aClipRec.Bottom() ) )
/*N*/           break;
/*N*/       if ( IsVertical() && ( aStartPos.X() < aClipRec.Left() ) )
/*N*/           break;
/*N*/   }
/*N*/   if ( aStatus.DoRestoreFont() )
/*?*/       pOutDev->SetFont( aOldFont );
/*N*/ }

/*N*/ void ImpEditEngine::Paint( ImpEditView* pView, const Rectangle& rRec, sal_Bool bUseVirtDev )
/*N*/ {
/*N*/   DBG_ASSERT( pView, "Keine View - Kein Paint!" );
/*N*/   DBG_CHKOBJ( GetEditEnginePtr(), EditEngine, 0 );
/*N*/
/*N*/   if ( !GetUpdateMode() || IsInUndo() )
/*N*/       return;
/*N*/
/*N*/   // Schnittmenge aus Paintbereich und OutputArea.
/*N*/   Rectangle aClipRec( pView->GetOutputArea() );
/*N*/   aClipRec.Intersection( rRec );
/*N*/
/*N*/   Window* pOutWin = pView->GetWindow();
/*N*/
/*N*/   if ( bUseVirtDev )
/*N*/   {
/*N*/       Rectangle aClipRecPixel( pOutWin->LogicToPixel( aClipRec ) );
/*N*/       if ( !IsVertical() )
/*N*/       {
/*N*/           // etwas mehr, falls abgerundet!
/*N*/           aClipRecPixel.Right() += 1;
/*N*/           aClipRecPixel.Bottom() += 1;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           aClipRecPixel.Left() -= 1;
/*?*/           aClipRecPixel.Bottom() += 1;
/*N*/       }
/*N*/
/*N*/       // Wenn aClipRecPixel > XXXX, dann invalidieren ?!
/*N*/
/*N*/       VirtualDevice* pVDev = GetVirtualDevice( pOutWin->GetMapMode() );
/*N*/       pVDev->SetDigitLanguage( GetRefDevice()->GetDigitLanguage() );
/*N*/
/*N*/       pVDev->SetBackground( pView->GetBackgroundColor() );
/*N*/
/*N*/       sal_Bool bVDevValid = sal_True;
/*N*/       Size aOutSz( pVDev->GetOutputSizePixel() );
/*N*/       if ( (  aOutSz.Width() < aClipRecPixel.GetWidth() ) ||
/*N*/            (  aOutSz.Height() < aClipRecPixel.GetHeight() ) )
/*N*/       {
/*N*/           bVDevValid = pVDev->SetOutputSizePixel( aClipRecPixel.GetSize() );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Das VirtDev kann bei einem Resize sehr gross werden =>
/*N*/           // irgendwann mal kleiner machen!
/*N*/           if ( ( aOutSz.Height() > ( aClipRecPixel.GetHeight() + RESDIFF ) ) ||
/*N*/                ( aOutSz.Width() > ( aClipRecPixel.GetWidth() + RESDIFF ) ) )
/*N*/           {
/*?*/               bVDevValid = pVDev->SetOutputSizePixel( aClipRecPixel.GetSize() );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pVDev->Erase();
/*N*/           }
/*N*/       }
/*N*/       DBG_ASSERT( bVDevValid, "VDef konnte nicht vergroessert werden!" );
/*N*/       if ( !bVDevValid )
/*N*/       {
/*?*/           Paint( pView, rRec, sal_False /* ohne VDev */ );
/*?*/           return;
/*N*/       }
/*N*/
/*N*/       // PaintRect fuer VDev nicht mit alignter Groesse,
/*N*/       // da sonst die Zeile darunter auch ausgegeben werden muss:
/*N*/       Rectangle aTmpRec( Point( 0, 0 ), aClipRec.GetSize() );
/*N*/
/*N*/       aClipRec = pOutWin->PixelToLogic( aClipRecPixel );
/*N*/       Point aStartPos;
/*N*/       if ( !IsVertical() )
/*N*/       {
/*N*/           aStartPos = aClipRec.TopLeft();
/*N*/           aStartPos = pView->GetDocPos( aStartPos );
/*N*/           aStartPos.X() *= (-1);
/*N*/           aStartPos.Y() *= (-1);
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           aStartPos = aClipRec.TopRight();
/*?*/           Point aDocPos( pView->GetDocPos( aStartPos ) );
/*?*/           aStartPos.X() = aClipRec.GetSize().Width() + aDocPos.Y();
/*?*/           aStartPos.Y() = -aDocPos.X();
/*N*/       }
/*N*/
/*N*/       Paint( pVDev, aTmpRec, aStartPos );
/*N*/
/*N*/       sal_Bool bClipRegion;
/*N*/       Region aOldRegion;
/*N*/       MapMode aOldMapMode;
/*N*/       if ( GetTextRanger() )
/*N*/       {
/*?*/           // Some problems here with push/pop, why?!
/*?*/ //            pOutWin->Push( PUSH_CLIPREGION|PUSH_MAPMODE );
/*?*/           bClipRegion = pOutWin->IsClipRegion();
/*?*/           aOldRegion = pOutWin->GetClipRegion();
/*?*/           // Wie bekomme ich das Polygon an die richtige Stelle????
/*?*/           // Das Polygon bezieht sich auf die View, nicht auf das Window
/*?*/           // => Origin umsetzen...
/*?*/           aOldMapMode = pOutWin->GetMapMode();
/*?*/           Point aOrigin = aOldMapMode.GetOrigin();
/*?*/           Point aViewPos = pView->GetOutputArea().TopLeft();
/*?*/           aOrigin.Move( aViewPos.X(), aViewPos.Y() );
/*?*/           aClipRec.Move( -aViewPos.X(), -aViewPos.Y() );
/*?*/           MapMode aNewMapMode( aOldMapMode );
/*?*/           aNewMapMode.SetOrigin( aOrigin );
/*?*/           pOutWin->SetMapMode( aNewMapMode );
/*?*/           pOutWin->SetClipRegion( Region( GetTextRanger()->GetPolyPolygon() ) );
/*N*/       }
/*N*/
/*N*/       pOutWin->DrawOutDev( aClipRec.TopLeft(), aClipRec.GetSize(),
/*N*/                           Point(0,0), aClipRec.GetSize(), *pVDev );
/*N*/
/*N*/       if ( GetTextRanger() )
/*N*/       {
/*?*/ //            pOutWin->Pop();
/*?*/           if ( bClipRegion )
/*?*/               pOutWin->SetClipRegion( aOldRegion );
/*?*/           else
/*?*/               pOutWin->SetClipRegion();
/*?*/           pOutWin->SetMapMode( aOldMapMode );
/*N*/       }
/*N*/
/*N*/
/*N*/       pView->DrawSelection();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       Point aStartPos;
/*?*/       if ( !IsVertical() )
/*?*/       {
/*?*/           aStartPos = pView->GetOutputArea().TopLeft();
/*?*/           aStartPos.X() -= pView->GetVisDocLeft();
/*?*/           aStartPos.Y() -= pView->GetVisDocTop();
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           aStartPos = pView->GetOutputArea().TopRight();
/*?*/           aStartPos.X() += pView->GetVisDocTop();
/*?*/           aStartPos.Y() -= pView->GetVisDocLeft();
/*?*/       }
/*?*/
/*?*/       // Wenn Doc-Breite < OutputArea,Width, nicht umgebrochene Felder,
/*?*/       // stehen die Felder sonst ber, wenn > Zeile.
/*?*/       // ( Oben nicht, da dort bereits Doc-Breite von Formatierung mit drin )
/*?*/       if ( !IsVertical() && ( pView->GetOutputArea().GetWidth() > GetPaperSize().Width() ) )
/*?*/       {
/*?*/           long nMaxX = pView->GetOutputArea().Left() + GetPaperSize().Width();
/*?*/           if ( aClipRec.Left() > nMaxX )
/*?*/               return;
/*?*/           if ( aClipRec.Right() > nMaxX )
/*?*/               aClipRec.Right() = nMaxX;
/*?*/       }
/*?*/
/*?*/       sal_Bool bClipRegion = pOutWin->IsClipRegion();
/*?*/       Region aOldRegion = pOutWin->GetClipRegion();
/*?*/       pOutWin->IntersectClipRegion( aClipRec );
/*?*/
/*?*/       Paint( pOutWin, aClipRec, aStartPos );
/*?*/
/*?*/       if ( bClipRegion )
/*?*/           pOutWin->SetClipRegion( aOldRegion );
/*?*/       else
/*?*/           pOutWin->SetClipRegion();
/*?*/
/*?*/       pView->DrawSelection();
/*N*/   }
/*N*/
/*N*/ }

//STRIP001 void ImpEditEngine::InsertContent( ContentNode* pNode, sal_uInt16 nPos )
//STRIP001 {
//STRIP001  DBG_ASSERT( pNode, "NULL-Poointer in InsertContent! " );
//STRIP001  DBG_ASSERT( IsInUndo(), "InsertContent nur fuer Undo()!" );
//STRIP001  ParaPortion* pNew = new ParaPortion( pNode );
//STRIP001  GetParaPortions().Insert( pNew, nPos );
//STRIP001  aEditDoc.Insert( pNode, nPos );
//STRIP001  if ( IsCallParaInsertedOrDeleted() )
//STRIP001      GetEditEnginePtr()->ParagraphInserted( nPos );
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::SplitContent( sal_uInt16 nNode, sal_uInt16 nSepPos )
//STRIP001 {
//STRIP001  ContentNode* pNode = aEditDoc.SaveGetObject( nNode );
//STRIP001  DBG_ASSERT( pNode, "Ungueltiger Node in SplitContent" );
//STRIP001  DBG_ASSERT( IsInUndo(), "SplitContent nur fuer Undo()!" );
//STRIP001  DBG_ASSERT( nSepPos <= pNode->Len(), "Index im Wald: SplitContent" );
//STRIP001  EditPaM aPaM( pNode, nSepPos );
//STRIP001  return ImpInsertParaBreak( aPaM );
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::ConnectContents( sal_uInt16 nLeftNode, sal_Bool bBackward )
//STRIP001 {
//STRIP001  ContentNode* pLeftNode = aEditDoc.SaveGetObject( nLeftNode );
//STRIP001  ContentNode* pRightNode = aEditDoc.SaveGetObject( nLeftNode+1 );
//STRIP001  DBG_ASSERT( pLeftNode, "Ungueltiger linker Node in ConnectContents" );
//STRIP001  DBG_ASSERT( pRightNode, "Ungueltiger rechter Node in ConnectContents" );
//STRIP001  DBG_ASSERT( IsInUndo(), "ConnectContent nur fuer Undo()!" );
//STRIP001  return ImpConnectParagraphs( pLeftNode, pRightNode, bBackward );
//STRIP001 }

/*N*/ void ImpEditEngine::SetUpdateMode( sal_Bool bUp, EditView* pCurView, sal_Bool bForceUpdate )
/*N*/ {
/*N*/   sal_Bool bChanged = ( GetUpdateMode() != bUp );
/*N*/
/*N*/   // Beim Umschalten von sal_True auf sal_False waren alle Selektionen sichtbar,
/*N*/   // => Wegmalen
/*N*/   // Umgekehrt waren alle unsichtbar => malen
/*N*/
/*N*/ //    DrawAllSelections();    sieht im Outliner schlecht aus !
/*N*/ //    EditView* pView = aEditViewList.First();
/*N*/ //    while ( pView )
/*N*/ //    {
/*N*/ //        DBG_CHKOBJ( pView, EditView, 0 );
/*N*/ //        pView->pImpEditView->DrawSelection();
/*N*/ //        pView = aEditViewList.Next();
/*N*/ //    }
/*N*/
/*N*/   // Wenn !bFormatted, also z.B. nach SetText, braucht bei UpdateMode sal_True
/*N*/   // nicht sofort formatiert werden, weil warscheinlich noch Text kommt.
/*N*/   // Spaetestens bei einem Paint / CalcTextWidth wird formatiert.
/*N*/
/*N*/   bUpdate = bUp;
/*N*/   if ( bUpdate && ( bChanged || bForceUpdate ) )
/*N*/       FormatAndUpdate( pCurView );
/*N*/ }

//STRIP001 void ImpEditEngine::ShowParagraph( sal_uInt16 nParagraph, sal_Bool bShow )
//STRIP001 {
//STRIP001  ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nParagraph );
//STRIP001  DBG_ASSERT( pPPortion, "ShowParagraph: Absatz existiert nicht!" );
//STRIP001  if ( pPPortion && ( pPPortion->IsVisible() != bShow ) )
//STRIP001  {
//STRIP001      pPPortion->SetVisible( bShow );
//STRIP001
//STRIP001      if ( !bShow )
//STRIP001      {
//STRIP001          // Als deleted kenzeichnen, damit keine Selektion auf diesem
//STRIP001          // Absatz beginnt oder endet...
//STRIP001          DeletedNodeInfo* pDelInfo = new DeletedNodeInfo( (sal_uInt32)pPPortion->GetNode(), nParagraph );
//STRIP001          aDeletedNodes.Insert( pDelInfo, aDeletedNodes.Count() );
//STRIP001          UpdateSelections();
//STRIP001          // Dann kriege ich den unteren Bereich nicht invalidiert,
//STRIP001          // wenn UpdateMode = sal_False!
//STRIP001          // Wenn doch, dann vor SetVisible auf sal_False merken!
//STRIP001 //           nCurTextHeight -= pPPortion->GetHeight();
//STRIP001      }
//STRIP001
//STRIP001      if ( bShow && ( pPPortion->IsInvalid() || !pPPortion->nHeight ) )
//STRIP001      {
//STRIP001          if ( !GetTextRanger() )
//STRIP001          {
//STRIP001              if ( pPPortion->IsInvalid() )
//STRIP001              {
//STRIP001                  Font aOldFont( GetRefDevice()->GetFont() );
//STRIP001                  CreateLines( nParagraph, 0 );   // 0: Kein TextRanger
//STRIP001                  if ( aStatus.DoRestoreFont() )
//STRIP001                      GetRefDevice()->SetFont( aOldFont );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  CalcHeight( pPPortion );
//STRIP001              }
//STRIP001              nCurTextHeight += pPPortion->GetHeight();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nCurTextHeight = 0x7fffffff;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pPPortion->SetMustRepaint( sal_True );
//STRIP001      if ( GetUpdateMode() && !IsInUndo() && !GetTextRanger() )
//STRIP001      {
//STRIP001          aInvalidRec = Rectangle(    Point( 0, GetParaPortions().GetYOffset( pPPortion ) ),
//STRIP001                                      Point( GetPaperSize().Width(), nCurTextHeight ) );
//STRIP001          UpdateViews( GetActiveView() );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 sal_Bool ImpEditEngine::IsParagraphVisible( sal_uInt16 nParagraph )
//STRIP001 {
//STRIP001  ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nParagraph );
//STRIP001  DBG_ASSERT( pPPortion, "IsParagraphVisible: Absatz existiert nicht!" );
//STRIP001  if ( pPPortion )
//STRIP001      return pPPortion->IsVisible();
//STRIP001  return sal_False;
//STRIP001 }

//STRIP001 EditSelection ImpEditEngine::MoveParagraphs( Range aOldPositions, sal_uInt16 nNewPos, EditView* pCurView )
//STRIP001 {
//STRIP001  DBG_ASSERT( GetParaPortions().Count() != 0, "Keine Absaetze gefunden: MoveParagraphs" );
//STRIP001  if ( GetParaPortions().Count() == 0 )
//STRIP001      return EditSelection();
//STRIP001  aOldPositions.Justify();
//STRIP001
//STRIP001  EditSelection aSel( ImpMoveParagraphs( aOldPositions, nNewPos ) );
//STRIP001
//STRIP001  if ( nNewPos >= GetParaPortions().Count() )
//STRIP001      nNewPos = GetParaPortions().Count() - 1;
//STRIP001
//STRIP001  // Dort, wo der Absatz eingefuegt wurde, muss richtig gepainted werden:
//STRIP001  // Dort, wo der Absatz entfernt wurde, muss richtig gepainted werden:
//STRIP001  // ( Und dazwischen entsprechend auch...)
//STRIP001  if ( pCurView && ( GetUpdateMode() == sal_True ) )
//STRIP001  {
//STRIP001      // in diesem Fall kann ich direkt neu malen, ohne die
//STRIP001      // Portions zu Invalidieren.
//STRIP001      sal_uInt16 nFirstPortion = Min( (sal_uInt16)aOldPositions.Min(), nNewPos );
//STRIP001      sal_uInt16 nLastPortion = Max( (sal_uInt16)aOldPositions.Max(), nNewPos );
//STRIP001
//STRIP001      ParaPortion* pUpperPortion = GetParaPortions().SaveGetObject( nFirstPortion );
//STRIP001      ParaPortion* pLowerPortion = GetParaPortions().SaveGetObject( nLastPortion );
//STRIP001
//STRIP001      aInvalidRec = Rectangle();  // leermachen
//STRIP001      aInvalidRec.Left() = 0;
//STRIP001      aInvalidRec.Right() = aPaperSize.Width();
//STRIP001      aInvalidRec.Top() = GetParaPortions().GetYOffset( pUpperPortion );
//STRIP001      aInvalidRec.Bottom() = GetParaPortions().GetYOffset( pLowerPortion ) + pLowerPortion->GetHeight();
//STRIP001
//STRIP001      UpdateViews( pCurView );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // aber der oberen ungueltigen Position neu painten...
//STRIP001      sal_uInt16 nFirstInvPara = Min( (sal_uInt16)aOldPositions.Min(), nNewPos );
//STRIP001      InvalidateFromParagraph( nFirstInvPara );
//STRIP001  }
//STRIP001  return aSel;
//STRIP001 }

//STRIP001 void ImpEditEngine::InvalidateFromParagraph( sal_uInt16 nFirstInvPara )
//STRIP001 {
//STRIP001  // Es werden nicht die folgenden Absaetze invalidiert,
//STRIP001  // da ResetHeight() => Groessenanderung => alles folgende wird
//STRIP001  // sowieso neu ausgegeben.
//STRIP001  ParaPortion* pTmpPortion;
//STRIP001  if ( nFirstInvPara != 0 )
//STRIP001  {
//STRIP001      pTmpPortion = GetParaPortions().GetObject( nFirstInvPara-1 );
//STRIP001      pTmpPortion->MarkInvalid( pTmpPortion->GetNode()->Len(), 0 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pTmpPortion = GetParaPortions().GetObject( 0 );
//STRIP001      pTmpPortion->MarkSelectionInvalid( 0, pTmpPortion->GetNode()->Len() );
//STRIP001  }
//STRIP001  pTmpPortion->ResetHeight();
//STRIP001 }

/*N*/ IMPL_LINK_INLINE_START( ImpEditEngine, StatusTimerHdl, Timer *, EMPTYARG )
/*N*/ {
/*N*/   CallStatusHdl();
/*N*/   return 0;
/*N*/ }
/*N*/ IMPL_LINK_INLINE_END( ImpEditEngine, StatusTimerHdl, Timer *, EMPTYARG )

/*N*/ void ImpEditEngine::CallStatusHdl()
/*N*/ {
/*N*/   if ( aStatusHdlLink.IsSet() && aStatus.GetStatusWord() )
/*N*/   {
/*N*/       // Der Status muss vor Call zurueckgesetzt werden,
/*N*/       // da im Hdl evtl. weitere Fags gesetzt werden...
/*N*/       EditStatus aTmpStatus( aStatus );
/*N*/       aStatus.Clear();
/*N*/       aStatusHdlLink.Call( &aTmpStatus );
/*N*/       aStatusTimer.Stop();    // Falls von Hand gerufen...
/*N*/   }
/*N*/ }

//STRIP001 ContentNode* ImpEditEngine::GetPrevVisNode( ContentNode* pCurNode )
//STRIP001 {
//STRIP001  ParaPortion* pPortion = FindParaPortion( pCurNode );
//STRIP001  DBG_ASSERT( pPortion, "GetPrevVisibleNode: Keine passende Portion!" );
//STRIP001  pPortion = GetPrevVisPortion( pPortion );
//STRIP001  if ( pPortion )
//STRIP001      return pPortion->GetNode();
//STRIP001  return 0;
//STRIP001 }

//STRIP001 ContentNode* ImpEditEngine::GetNextVisNode( ContentNode* pCurNode )
//STRIP001 {
//STRIP001  ParaPortion* pPortion = FindParaPortion( pCurNode );
//STRIP001  DBG_ASSERT( pPortion, "GetNextVisibleNode: Keine passende Portion!" );
//STRIP001  pPortion = GetNextVisPortion( pPortion );
//STRIP001  if ( pPortion )
//STRIP001      return pPortion->GetNode();
//STRIP001  return 0;
//STRIP001 }

//STRIP001 ParaPortion* ImpEditEngine::GetPrevVisPortion( ParaPortion* pCurPortion )
//STRIP001 {
//STRIP001  sal_uInt16 nPara = GetParaPortions().GetPos( pCurPortion );
//STRIP001  DBG_ASSERT( nPara < GetParaPortions().Count() , "Portion nicht gefunden: GetPrevVisPortion" );
//STRIP001  ParaPortion* pPortion = nPara ? GetParaPortions()[--nPara] : 0;
//STRIP001  while ( pPortion && !pPortion->IsVisible() )
//STRIP001      pPortion = nPara ? GetParaPortions()[--nPara] : 0;
//STRIP001
//STRIP001  return pPortion;
//STRIP001 }

//STRIP001 ParaPortion* ImpEditEngine::GetNextVisPortion( ParaPortion* pCurPortion )
//STRIP001 {
//STRIP001  sal_uInt16 nPara = GetParaPortions().GetPos( pCurPortion );
//STRIP001  DBG_ASSERT( nPara < GetParaPortions().Count() , "Portion nicht gefunden: GetPrevVisNode" );
//STRIP001  ParaPortion* pPortion = GetParaPortions().SaveGetObject( ++nPara );
//STRIP001  while ( pPortion && !pPortion->IsVisible() )
//STRIP001      pPortion = GetParaPortions().SaveGetObject( ++nPara );
//STRIP001
//STRIP001  return pPortion;
//STRIP001 }

/*N*/ EditPaM ImpEditEngine::InsertParagraph( sal_uInt16 nPara )
/*N*/ {
/*N*/   EditPaM aPaM;
/*N*/   if ( nPara != 0 )
/*N*/   {
/*N*/       ContentNode* pNode = GetEditDoc().SaveGetObject( nPara-1 );
/*N*/       if ( !pNode )
/*?*/           pNode = GetEditDoc().SaveGetObject( GetEditDoc().Count() - 1 );
/*N*/       DBG_ASSERT( pNode, "Kein einziger Absatz in InsertParagraph ?" );
/*N*/       aPaM = EditPaM( pNode, pNode->Len() );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       ContentNode* pNode = GetEditDoc().SaveGetObject( 0 );
/*?*/       aPaM = EditPaM( pNode, 0 );
/*N*/   }
/*N*/
/*N*/   return ImpInsertParaBreak( aPaM );
/*N*/ }

/*N*/ EditSelection* ImpEditEngine::SelectParagraph( sal_uInt16 nPara )
/*N*/ {
/*N*/   EditSelection* pSel = 0;
/*N*/   ContentNode* pNode = GetEditDoc().SaveGetObject( nPara );
/*N*/   DBG_ASSERTWARNING( pNode, "Absatz existiert nicht: SelectParagraph" );
/*N*/   if ( pNode )
/*N*/       pSel = new EditSelection( EditPaM( pNode, 0 ), EditPaM( pNode, pNode->Len() ) );
/*N*/
/*N*/   return pSel;
/*N*/ }

/*N*/ void ImpEditEngine::FormatAndUpdate( EditView* pCurView )
/*N*/ {
/*N*/   if ( bDowning )
/*N*/       return ;
/*N*/
/*N*/   if ( IsInUndo() )
/*?*/       IdleFormatAndUpdate( pCurView );
/*N*/   else
/*N*/   {
/*N*/       FormatDoc();
/*N*/       UpdateViews( pCurView );
/*N*/   }
/*N*/ }

//STRIP001 void ImpEditEngine::SetFlatMode( sal_Bool bFlat )
//STRIP001 {
//STRIP001  if ( bFlat != aStatus.UseCharAttribs() )
//STRIP001      return;
//STRIP001
//STRIP001  if ( !bFlat )
//STRIP001      aStatus.TurnOnFlags( EE_CNTRL_USECHARATTRIBS );
//STRIP001  else
//STRIP001      aStatus.TurnOffFlags( EE_CNTRL_USECHARATTRIBS );
//STRIP001
//STRIP001  aEditDoc.CreateDefFont( !bFlat );
//STRIP001
//STRIP001  FormatFullDoc();
//STRIP001  UpdateViews( (EditView*) 0);
//STRIP001  if ( pActiveView )
//STRIP001      pActiveView->ShowCursor();
//STRIP001 }

/*N*/ void ImpEditEngine::SetCharStretching( sal_uInt16 nX, sal_uInt16 nY )
/*N*/ {
/*N*/   if ( !IsVertical() )
/*N*/   {
/*N*/       nStretchX = nX;
/*N*/       nStretchY = nY;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nStretchX = nY;
/*N*/       nStretchY = nX;
/*N*/   }
/*N*/
/*N*/   if ( aStatus.DoStretch() )
/*N*/   {
/*?*/       FormatFullDoc();
/*?*/       UpdateViews( GetActiveView() );
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::DoStretchChars( sal_uInt16 nX, sal_uInt16 nY )
/*N*/ {
/*N*/   UndoActionStart( EDITUNDO_STRETCH );
/*N*/   sal_uInt16 nParas = GetEditDoc().Count();
/*N*/   for ( sal_uInt16 nPara = 0; nPara < nParas; nPara++ )
/*N*/   {
/*N*/       ContentNode* pNode = GetEditDoc()[nPara];
/*N*/       SfxItemSet aTmpSet( pNode->GetContentAttribs().GetItems() );
/*N*/
/*N*/       if ( nX != 100 )
/*N*/       {
/*N*/           // Fontbreite
/*N*/           SvxCharScaleWidthItem* pNewWidth = (SvxCharScaleWidthItem*) pNode->GetContentAttribs().GetItem( EE_CHAR_FONTWIDTH ).Clone();
/*N*/           sal_uInt32 nProp = pNewWidth->GetValue();   // sal_uInt32, kann temporaer gross werden
/*N*/           nProp *= nX;
/*N*/           nProp /= 100;
/*N*/           pNewWidth->SetValue( (sal_uInt16)nProp );
/*N*/           aTmpSet.Put( *pNewWidth );
/*N*/           delete pNewWidth;
/*N*/
/*N*/           // Kerning:
/*N*/           const SvxKerningItem& rKerningItem =
/*N*/               (const SvxKerningItem&)pNode->GetContentAttribs().GetItem( EE_CHAR_KERNING );
/*N*/           SvxKerningItem* pNewKerning = (SvxKerningItem*)rKerningItem.Clone();
/*N*/           long nKerning = pNewKerning->GetValue();
/*N*/           if ( nKerning > 0 )
/*N*/           {
/*N*/               nKerning *= nX;
/*N*/               nKerning /= 100;
/*N*/           }
/*N*/           else if ( nKerning < 0 )
/*N*/           {
/*N*/               // Bei Negativen Werten:
/*N*/               // Bei Stretching > 100 muessen die Werte kleiner werden und umgekehrt.
/*N*/               nKerning *= 100;
/*N*/               nKerning /= nX;
/*N*/           }
/*N*/           pNewKerning->SetValue( (short)nKerning );
/*N*/           aTmpSet.Put( *pNewKerning);
/*N*/           delete pNewKerning;
/*N*/       }
/*N*/       else
/*N*/           aTmpSet.ClearItem( EE_CHAR_FONTWIDTH );
/*N*/
/*N*/       if ( nY != 100 )
/*N*/       {
/*N*/           // Fonthoehe
/*N*/           for ( int nItem = 0; nItem < 3; nItem++ )
/*N*/           {
/*N*/               USHORT nItemId = EE_CHAR_FONTHEIGHT;
/*N*/               if ( nItem == 1 )
/*N*/                   nItemId = EE_CHAR_FONTHEIGHT_CJK;
/*N*/               else if ( nItem == 2 )
/*N*/                   nItemId = EE_CHAR_FONTHEIGHT_CTL;
/*N*/
/*N*/               const SvxFontHeightItem& rHeightItem =
/*N*/                   (const SvxFontHeightItem&)pNode->GetContentAttribs().GetItem( nItemId );
/*N*/               SvxFontHeightItem* pNewHeight = (SvxFontHeightItem*)rHeightItem.Clone();
/*N*/               sal_uInt32 nHeight = pNewHeight->GetHeight();
/*N*/               nHeight *= nY;
/*N*/               nHeight /= 100;
/*N*/               pNewHeight->SetHeightValue( nHeight );
/*N*/               aTmpSet.Put( *pNewHeight );
/*N*/               delete pNewHeight;
/*N*/           }
/*N*/
/*N*/           // Absatzabstaende
/*N*/           const SvxULSpaceItem& rULSpaceItem =
/*N*/               (const SvxULSpaceItem&)pNode->GetContentAttribs().GetItem( EE_PARA_ULSPACE );
/*N*/           SvxULSpaceItem* pNewUL = (SvxULSpaceItem*)rULSpaceItem.Clone();
/*N*/           sal_uInt32 nUpper = pNewUL->GetUpper();
/*N*/           nUpper *= nY;
/*N*/           nUpper /= 100;
/*N*/           pNewUL->SetUpper( (sal_uInt16)nUpper );
/*N*/           sal_uInt32 nLower = pNewUL->GetLower();
/*N*/           nLower *= nY;
/*N*/           nLower /= 100;
/*N*/           pNewUL->SetLower( (sal_uInt16)nLower );
/*N*/           aTmpSet.Put( *pNewUL );
/*N*/           delete pNewUL;
/*N*/       }
/*N*/       else
/*N*/           aTmpSet.ClearItem( EE_CHAR_FONTHEIGHT );
/*N*/
/*N*/       SetParaAttribs( nPara, aTmpSet );
/*N*/
/*N*/       // harte Attribute:
/*N*/       sal_uInt16 nLastEnd = 0;    // damit nach entfernen und neu nicht nochmal
/*N*/       CharAttribArray& rAttribs = pNode->GetCharAttribs().GetAttribs();
/*N*/       sal_uInt16 nAttribs = rAttribs.Count();
/*N*/       for ( sal_uInt16 nAttr = 0; nAttr < nAttribs; nAttr++ )
/*N*/       {
/*N*/           EditCharAttrib* pAttr = rAttribs[nAttr];
/*N*/           if ( pAttr->GetStart() >= nLastEnd )
/*N*/           {
/*N*/               sal_uInt16 nWhich = pAttr->Which();
/*N*/               SfxPoolItem* pNew = 0;
/*N*/               if ( nWhich == EE_CHAR_FONTHEIGHT )
/*N*/               {
/*N*/                   SvxFontHeightItem* pNewHeight = (SvxFontHeightItem*)pAttr->GetItem()->Clone();
/*N*/                   sal_uInt32 nHeight = pNewHeight->GetHeight();
/*N*/                   nHeight *= nY;
/*N*/                   nHeight /= 100;
/*N*/                   pNewHeight->SetHeightValue( nHeight );
/*N*/                   pNew = pNewHeight;
/*N*/               }
/*N*/               else if ( nWhich == EE_CHAR_FONTWIDTH )
/*N*/               {
/*N*/                   SvxCharScaleWidthItem* pNewWidth = (SvxCharScaleWidthItem*)pAttr->GetItem()->Clone();
/*N*/                   sal_uInt32 nProp = pNewWidth->GetValue();
/*N*/                   nProp *= nX;
/*N*/                   nProp /= 100;
/*N*/                   pNewWidth->SetValue( (sal_uInt16)nProp );
/*N*/                   pNew = pNewWidth;
/*N*/               }
/*N*/               else if ( nWhich == EE_CHAR_KERNING )
/*N*/               {
/*N*/                   SvxKerningItem* pNewKerning = (SvxKerningItem*)pAttr->GetItem()->Clone();
/*N*/                   long nKerning = pNewKerning->GetValue();
/*N*/                   if ( nKerning > 0 )
/*N*/                   {
/*N*/                       nKerning *= nX;
/*N*/                       nKerning /= 100;
/*N*/                   }
/*N*/                   else if ( nKerning < 0 )
/*N*/                   {
/*N*/                       // Bei Negativen Werten:
/*N*/                       // Bei Stretching > 100 muessen die Werte kleiner werden und umgekehrt.
/*N*/                       nKerning *= 100;
/*N*/                       nKerning /= nX;
/*N*/                   }
/*N*/                   pNewKerning->SetValue( (short)nKerning );
/*N*/                   pNew = pNewKerning;
/*N*/               }
/*N*/               if ( pNew )
/*N*/               {
/*N*/                   SfxItemSet aTmpSet( GetEmptyItemSet() );
/*N*/                   aTmpSet.Put( *pNew );
/*N*/                   SetAttribs( EditSelection( EditPaM( pNode, pAttr->GetStart() ),
/*N*/                       EditPaM( pNode, pAttr->GetEnd() ) ), aTmpSet );
/*N*/
/*N*/                   nLastEnd = pAttr->GetEnd();
/*N*/                   delete pNew;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   UndoActionEnd( EDITUNDO_STRETCH );
/*N*/ }

/*N*/ const SvxLRSpaceItem& ImpEditEngine::GetLRSpaceItem( ContentNode* pNode )
/*N*/ {
/*N*/     return (const SvxLRSpaceItem&)pNode->GetContentAttribs().GetItem( aStatus.IsOutliner() ? EE_PARA_OUTLLRSPACE : EE_PARA_LRSPACE );
/*N*/ }

/*N*/ void ImpEditEngine::ImplInitLayoutMode( OutputDevice* pOutDev, USHORT nPara, USHORT nIndex )
/*N*/ {
/*N*/     BOOL bCTL = FALSE;
/*N*/     BYTE bR2L = FALSE;
/*N*/     if ( nIndex == 0xFFFF )
/*N*/     {
/*N*/         bCTL = HasScriptType( nPara, i18n::ScriptType::COMPLEX );
/*N*/         bR2L = IsRightToLeft( nPara );
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         ContentNode* pNode = GetEditDoc().SaveGetObject( nPara );
/*N*/         short nScriptType = GetScriptType( EditPaM( pNode, nIndex+1 ) );
/*N*/         bCTL = nScriptType == i18n::ScriptType::COMPLEX;
/*N*/         bR2L = GetRightToLeft( nPara, nIndex );
/*N*/     }
/*N*/
/*N*/     ULONG nLayoutMode = pOutDev->GetLayoutMode();
/*N*/
/*N*/     // We always use the left postion for DrawText()
/*N*/     nLayoutMode &= ~(TEXT_LAYOUT_BIDI_RTL);
/*N*/
/*N*/     if ( !bCTL && !bR2L)
/*N*/     {
/*?*/         // No CTL/Bidi checking neccessary
/*?*/         nLayoutMode |= ( TEXT_LAYOUT_COMPLEX_DISABLED | TEXT_LAYOUT_BIDI_STRONG );
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         // CTL/Bidi checking neccessary
/*N*/         // Don't use BIDI_STRONG, VCL must do some checks.
/*N*/         nLayoutMode &= ~( TEXT_LAYOUT_COMPLEX_DISABLED | TEXT_LAYOUT_BIDI_STRONG );
/*N*/
/*N*/         if ( bR2L )
/*N*/             nLayoutMode |= TEXT_LAYOUT_BIDI_RTL|TEXT_LAYOUT_TEXTORIGIN_LEFT;
/*N*/     }
/*N*/
/*N*/     pOutDev->SetLayoutMode( nLayoutMode );
/*N*/
/*N*/ }

/*N*/ Reference < i18n::XBreakIterator > ImpEditEngine::ImplGetBreakIterator()
/*N*/ {
/*N*/   if ( !xBI.is() )
/*N*/   {
/*N*/       Reference< lang::XMultiServiceFactory > xMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/       Reference < XInterface > xI = xMSF->createInstance( OUString::createFromAscii( "com.sun.star.i18n.BreakIterator" ) );
/*N*/       if ( xI.is() )
/*N*/       {
/*N*/           Any x = xI->queryInterface( ::getCppuType((const Reference< i18n::XBreakIterator >*)0) );
/*N*/           x >>= xBI;
/*N*/       }
/*N*/   }
/*N*/   return xBI;
/*N*/ }

/*N*/ Color ImpEditEngine::GetAutoColor() const
/*N*/ {
/*N*/   Color aColor = const_cast<ImpEditEngine*>(this)->GetColorConfig().GetColorValue( svtools::FONTCOLOR ).nColor;
/*N*/
/*N*/   if ( GetBackgroundColor() != COL_AUTO )
/*N*/   {
/*?*/         if ( GetBackgroundColor().IsDark() && aColor.IsDark() )
/*?*/           aColor = COL_WHITE;
/*?*/         else if ( GetBackgroundColor().IsBright() && aColor.IsBright() )
/*?*/           aColor = COL_BLACK;
/*N*/   }
/*N*/
/*N*/   return aColor;
/*N*/ }


//STRIP001 BOOL ImpEditEngine::ImplCalcAsianCompression( ContentNode* pNode, TextPortion* pTextPortion, USHORT nStartPos, long* pDXArray, USHORT n100thPercentFromMax, BOOL bManipulateDXArray )
//STRIP001 {
//STRIP001     DBG_ASSERT( GetAsianCompressionMode(), "ImplCalcAsianCompression - Why?" );
//STRIP001     DBG_ASSERT( pTextPortion->GetLen(), "ImplCalcAsianCompression - Empty Portion?" );
//STRIP001
//STRIP001     // Percent is 1/100 Percent...
//STRIP001
//STRIP001     if ( n100thPercentFromMax == 10000 )
//STRIP001         pTextPortion->SetExtraInfos( NULL );
//STRIP001
//STRIP001     BOOL bCompressed = FALSE;
//STRIP001
//STRIP001  if ( GetScriptType( EditPaM( pNode, nStartPos+1 ) ) == i18n::ScriptType::ASIAN )
//STRIP001     {
//STRIP001         long nNewPortionWidth = pTextPortion->GetSize().Width();
//STRIP001         USHORT nPortionLen = pTextPortion->GetLen();
//STRIP001         for ( USHORT n = 0; n < nPortionLen; n++ )
//STRIP001         {
//STRIP001             BYTE nType = GetCharTypeForCompression( pNode->GetChar( n+nStartPos ) );
//STRIP001
//STRIP001             BOOL bCompressPunctuation = ( nType == CHAR_PUNCTUATIONLEFT ) || ( nType == CHAR_PUNCTUATIONRIGHT );
//STRIP001             BOOL bCompressKana = ( nType == CHAR_KANA ) && ( GetAsianCompressionMode() == text::CharacterCompressionType::PUNCTUATION_AND_KANA );
//STRIP001
//STRIP001             // create Extra infos only if needed...
//STRIP001             if ( bCompressPunctuation || bCompressKana )
//STRIP001             {
//STRIP001                 if ( !pTextPortion->GetExtraInfos() )
//STRIP001                 {
//STRIP001                     ExtraPortionInfo* pExtraInfos = new ExtraPortionInfo;
//STRIP001                     pTextPortion->SetExtraInfos( pExtraInfos );
//STRIP001                     pExtraInfos->nOrgWidth = pTextPortion->GetSize().Width();
//STRIP001                     pExtraInfos->nAsianCompressionTypes = CHAR_NORMAL;
//STRIP001                 }
//STRIP001                 pTextPortion->GetExtraInfos()->nMaxCompression100thPercent = n100thPercentFromMax;
//STRIP001                 pTextPortion->GetExtraInfos()->nAsianCompressionTypes |= nType;
//STRIP001 //                pTextPortion->GetExtraInfos()->nCompressedChars++;
//STRIP001
//STRIP001                 long nOldCharWidth;
//STRIP001                 if ( (n+1) < nPortionLen )
//STRIP001                 {
//STRIP001                     nOldCharWidth = pDXArray[n];
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if ( bManipulateDXArray )
//STRIP001                         nOldCharWidth = nNewPortionWidth - pTextPortion->GetExtraInfos()->nPortionOffsetX;
//STRIP001                     else
//STRIP001                         nOldCharWidth = pTextPortion->GetExtraInfos()->nOrgWidth;
//STRIP001                 }
//STRIP001                 nOldCharWidth -= ( n ? pDXArray[n-1] : 0 );
//STRIP001
//STRIP001                 long nCompress = 0;
//STRIP001
//STRIP001                 if ( bCompressPunctuation )
//STRIP001                 {
//STRIP001                     // pTextPortion->GetExtraInfos()->nComressionWeight += 5;
//STRIP001                     nCompress = nOldCharWidth / 2;
//STRIP001                 }
//STRIP001                 else // Kana
//STRIP001                 {
//STRIP001                     // pTextPortion->GetExtraInfos()->nComressionWeight += 1;
//STRIP001                     nCompress = nOldCharWidth / 10;
//STRIP001                 }
//STRIP001
//STRIP001                 if ( n100thPercentFromMax != 10000 )
//STRIP001                 {
//STRIP001                     nCompress *= n100thPercentFromMax;
//STRIP001                     nCompress /= 10000;
//STRIP001                 }
//STRIP001
//STRIP001                 if ( nCompress )
//STRIP001                 {
//STRIP001                     bCompressed = TRUE;
//STRIP001                     nNewPortionWidth -= nCompress;
//STRIP001                     pTextPortion->GetExtraInfos()->bCompressed = TRUE;
//STRIP001
//STRIP001
//STRIP001                     // Special handling for rightpunctuation: For the 'compression' we must
//STRIP001                     // start th eoutput before the normal char position....
//STRIP001                     if ( bManipulateDXArray && ( pTextPortion->GetLen() > 1 ) )
//STRIP001                     {
//STRIP001                         if ( !pTextPortion->GetExtraInfos()->pOrgDXArray )
//STRIP001                             pTextPortion->GetExtraInfos()->SaveOrgDXArray( pDXArray, pTextPortion->GetLen()-1 );
//STRIP001
//STRIP001                         if ( nType == CHAR_PUNCTUATIONRIGHT )
//STRIP001                         {
//STRIP001                             // If it's the first char, I must handle it in Paint()...
//STRIP001                             if ( n )
//STRIP001                             {
//STRIP001                                 // -1: No entry for the last character
//STRIP001                                 for ( USHORT i = n-1; i < (nPortionLen-1); i++ )
//STRIP001                                     pDXArray[i] -= nCompress;
//STRIP001                             }
//STRIP001                             else
//STRIP001                             {
//STRIP001                                 pTextPortion->GetExtraInfos()->bFirstCharIsRightPunktuation = TRUE;
//STRIP001                                 pTextPortion->GetExtraInfos()->nPortionOffsetX = -nCompress;
//STRIP001                             }
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             // -1: No entry for the last character
//STRIP001                             for ( USHORT i = n; i < (nPortionLen-1); i++ )
//STRIP001                                 pDXArray[i] -= nCompress;
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         if ( bCompressed && ( n100thPercentFromMax == 10000 ) )
//STRIP001             pTextPortion->GetExtraInfos()->nWidthFullCompression = nNewPortionWidth;
//STRIP001
//STRIP001         pTextPortion->GetSize().Width() = nNewPortionWidth;
//STRIP001
//STRIP001         if ( pTextPortion->GetExtraInfos() && ( n100thPercentFromMax != 10000 ) )
//STRIP001         {
//STRIP001             // Maybe rounding errors in nNewPortionWidth, assure that width not bigger than expected
//STRIP001             long nShrink = pTextPortion->GetExtraInfos()->nOrgWidth - pTextPortion->GetExtraInfos()->nWidthFullCompression;
//STRIP001             nShrink *= n100thPercentFromMax;
//STRIP001             nShrink /= 10000;
//STRIP001             long nNewWidth = pTextPortion->GetExtraInfos()->nOrgWidth - nShrink;
//STRIP001             if ( nNewWidth < pTextPortion->GetSize().Width() )
//STRIP001             pTextPortion->GetSize().Width() = nNewWidth;
//STRIP001         }
//STRIP001     }
//STRIP001     return bCompressed;
//STRIP001 }


//STRIP001 void ImpEditEngine::ImplExpandCompressedPortions( EditLine* pLine, ParaPortion* pParaPortion, long nRemainingWidth )
//STRIP001 {
//STRIP001     BOOL bFoundCompressedPortion = FALSE;
//STRIP001     long nCompressed = 0;
//STRIP001     long nCompressWeight = 0;
//STRIP001     TextPortionList aCompressedPortions;
//STRIP001
//STRIP001     USHORT nPortion = pLine->GetEndPortion();
//STRIP001     TextPortion* pTP = pParaPortion->GetTextPortions()[ nPortion ];
//STRIP001     while ( pTP && ( pTP->GetKind() == PORTIONKIND_TEXT ) )
//STRIP001     {
//STRIP001         if ( pTP->GetExtraInfos() && pTP->GetExtraInfos()->bCompressed )
//STRIP001         {
//STRIP001             bFoundCompressedPortion = TRUE;
//STRIP001             nCompressed += pTP->GetExtraInfos()->nOrgWidth - pTP->GetSize().Width();
//STRIP001             aCompressedPortions.Insert( pTP, aCompressedPortions.Count() );
//STRIP001         }
//STRIP001         pTP = ( nPortion > pLine->GetStartPortion() ) ? pParaPortion->GetTextPortions()[ --nPortion ] : NULL;
//STRIP001     }
//STRIP001
//STRIP001     if ( bFoundCompressedPortion )
//STRIP001     {
//STRIP001         long nCompressPercent = 0;
//STRIP001         if ( nCompressed > nRemainingWidth )
//STRIP001         {
//STRIP001             nCompressPercent = nCompressed - nRemainingWidth;
//STRIP001             DBG_ASSERT( nCompressPercent < 200000, "ImplExpandCompressedPortions - Overflow!" );
//STRIP001             nCompressPercent *= 10000;
//STRIP001             nCompressPercent /= nCompressed;
//STRIP001         }
//STRIP001
//STRIP001         for ( USHORT n = 0; n < aCompressedPortions.Count(); n++ )
//STRIP001         {
//STRIP001             pTP = aCompressedPortions[n];
//STRIP001             pTP->GetExtraInfos()->bCompressed = FALSE;
//STRIP001             pTP->GetSize().Width() = pTP->GetExtraInfos()->nOrgWidth;
//STRIP001             if ( nCompressPercent )
//STRIP001             {
//STRIP001                 USHORT nTxtPortion = pParaPortion->GetTextPortions().GetPos( pTP );
//STRIP001                 USHORT nTxtPortionStart = pParaPortion->GetTextPortions().GetStartPos( nTxtPortion );
//STRIP001                 DBG_ASSERT( nTxtPortionStart >= pLine->GetStart(), "Portion doesn't belong to the line!!!" );
//STRIP001                 long* pDXArray = (long*)pLine->GetCharPosArray().GetData()+( nTxtPortionStart-pLine->GetStart() );
//STRIP001                 if ( pTP->GetExtraInfos()->pOrgDXArray )
//STRIP001                     memcpy( pDXArray, pTP->GetExtraInfos()->pOrgDXArray, (pTP->GetLen()-1)*sizeof(long) );
//STRIP001                 ImplCalcAsianCompression( pParaPortion->GetNode(), pTP, nTxtPortionStart, pDXArray, (USHORT)nCompressPercent, TRUE );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     aCompressedPortions.Remove( 0, aCompressedPortions.Count() );
//STRIP001 }
}
