/*************************************************************************
 *
 *  $RCSfile: sw_fntcache.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:41 $
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

#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _PRINT_HXX //autogen
#include <vcl/print.hxx>
#endif
#ifndef _METRIC_HXX //autogen
#include <vcl/metric.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_CHARACTERITERATORMODE_HDL_
#include <com/sun/star/i18n/CharacterIteratorMode.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>       // Bildschirmabgleich
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>      // Bildschirmabgleich abschalten, ViewOption
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>       // CH_BLANK + CH_BULLET
#endif
#ifndef _WRONG_HXX
#include <wrong.hxx>
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>     // SwDrawTextInfo
#endif
#include "dbg_lay.hxx"
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // SwTxtFrm
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
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _ACCESSIBILITYOPTIONS_HXX
#include <accessibilityoptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif

// Enable this to use the helpclass SwRVPMark
#if OSL_DEBUG_LEVEL > 1
#ifndef _RVP_MARK_HXX
#include <rvp_mark.hxx>
#endif
#endif
namespace binfilter {

// globale Variablen, werden in FntCache.Hxx bekanntgegeben
// Der FontCache wird in TxtInit.Cxx _TXTINIT erzeugt und in _TXTEXIT geloescht
SwFntCache *pFntCache = NULL;
// Letzter Font, der durch ChgFntCache eingestellt wurde.
SwFntObj *pLastFont = NULL;
// Die "MagicNumber", die den Fonts zur Identifizierung verpasst wird
BYTE* pMagicNo = NULL;

Color *pWaveCol = 0;

long SwFntObj::nPixWidth;
MapMode* SwFntObj::pPixMap = NULL;
OutputDevice* SwFntObj::pPixOut = NULL;

extern USHORT UnMapDirection( USHORT nDir, const BOOL bVertFormat );

#ifdef _RVP_MARK_HXX

//STRIP001 void SwRVPMarker::Mark( const OutputDevice* pOut )
//STRIP001 {
//STRIP001  if( pOut )
//STRIP001  {
//STRIP001      Color aOldCol = pOut->GetLineColor();
//STRIP001      Color aBlack = Color( COL_BLACK );
//STRIP001      if( aOldCol != aBlack )
//STRIP001      {
//STRIP001          ((OutputDevice*)pOut)->SetLineColor( aBlack );
//STRIP001          ((OutputDevice*)pOut)->DrawChord( Rectangle(0,1,0,1),
//STRIP001                                            Point(), Point() );
//STRIP001          ((OutputDevice*)pOut)->SetLineColor( aOldCol );
//STRIP001      }
//STRIP001      else
//STRIP001          ((OutputDevice*)pOut)->DrawChord( Rectangle(0,1,0,1),
//STRIP001                                            Point(), Point() );
//STRIP001  }
//STRIP001 }

#endif

/*************************************************************************
|*
|*  SwFntCache::Flush()
|*
|*  Ersterstellung      AMA 16. Dez. 94
|*  Letzte Aenderung    AMA 16. Dez. 94
|*
|*************************************************************************/

/*N*/ void SwFntCache::Flush( )
/*N*/ {
/*N*/   if ( pLastFont )
/*N*/   {
/*N*/       pLastFont->Unlock();
/*N*/       pLastFont = NULL;
/*N*/   }
/*N*/   SwCache::Flush( );
/*N*/ }

/*************************************************************************
|*
|*  SwFntObj::SwFntObj(), ~SwFntObj()
|*
|*  Ersterstellung      AMA 7. Nov. 94
|*  Letzte Aenderung    AMA 7. Nov. 94
|*
|*************************************************************************/

/*N*/ SwFntObj::SwFntObj( const SwSubFont &rFont, const void *pOwner, ViewShell *pSh ) :
/*N*/   SwCacheObj( (void*)pOwner ),
/*N*/   aFont( rFont ),
/*N*/   pScrFont( NULL ),
/*N*/   pPrtFont( &aFont ),
/*N*/   pPrinter( NULL ),
/*N*/   nPropWidth( rFont.GetPropWidth() )
/*N*/ {
/*N*/   nZoom = pSh ? pSh->GetViewOptions()->GetZoom() : USHRT_MAX;
/*N*/   nLeading = USHRT_MAX;
/*N*/   nPrtAscent = USHRT_MAX;
/*N*/   nPrtHeight = USHRT_MAX;
/*N*/   bPaintBlank = ( UNDERLINE_NONE != aFont.GetUnderline()
/*N*/                 || STRIKEOUT_NONE != aFont.GetStrikeout() )
/*N*/                 && !aFont.IsWordLineMode();
/*N*/ }

/*N*/ SwFntObj::~SwFntObj()
/*N*/ {
/*N*/   if ( pScrFont != pPrtFont )
/*N*/       delete pScrFont;
/*N*/   if ( pPrtFont != &aFont )
/*?*/       delete pPrtFont;
/*N*/ }

/*N*/ void SwFntObj::CreatePrtFont( const OutputDevice& rPrt )
/*N*/ {
/*N*/     if ( nPropWidth != 100 && pPrinter != &rPrt )
/*N*/     {
/*?*/         if( pScrFont != pPrtFont )
/*?*/             delete pScrFont;
/*?*/         if( pPrtFont != &aFont )
/*?*/             delete pPrtFont;
/*?*/
/*?*/         const Font aOldFnt( rPrt.GetFont() );
/*?*/         ((OutputDevice&)rPrt).SetFont( aFont );
/*?*/         const FontMetric aWinMet( rPrt.GetFontMetric() );
/*?*/         ((OutputDevice&)rPrt).SetFont( aOldFnt );
/*?*/         long nWidth = ( aWinMet.GetSize().Width() * nPropWidth ) / 100;
/*?*/
/*?*/         if( !nWidth )
/*?*/             ++nWidth;
/*?*/         pPrtFont = new Font( aFont );
/*?*/         pPrtFont->SetSize( Size( nWidth, aFont.GetSize().Height() ) );
/*?*/         pScrFont = NULL;
/*N*/     }
/*N*/ }

/*************************************************************************
 *
 *  USHORT SwFntObj::GetAscent( const OutputDevice *pOut )
 *
 *  Ersterstellung      AMA 7. Nov. 94
 *  Letzte Aenderung    AMA 7. Nov. 94
 *
 *  Beschreibung: liefern den Ascent des Fonts auf dem
 *  gewuenschten Outputdevice zurueck, ggf. muss der Bildschirmfont erst
 *  erzeugt werden.
 *************************************************************************/

/*N*/ USHORT SwFntObj::GetAscent( const ViewShell *pSh, const OutputDevice *pOut )
/*N*/ {
/*N*/     // Condition for output font / refdev font adjustment
/*N*/     // 1. RefDef == OutDev (common printing, online layout)
/*N*/     // 2. Prospect/PagePreview pringing
/*N*/     // 3. PDF export from online layout
/*N*/     const OutputDevice* pRefDev = pOut;
/*N*/     if ( !pSh || ( pRefDev = &pSh->GetRefDev() ) == pOut ||
/*N*/          ( OUTDEV_PRINTER == pRefDev->GetOutDevType() &&
/*N*/            OUTDEV_PRINTER == pOut->GetOutDevType() ) ||
/*N*/          OUTDEV_WINDOW == pRefDev->GetOutDevType() )
/*N*/   {
/*N*/       if ( nPrtAscent == USHRT_MAX ) // DruckerAscent noch nicht bekannt?
/*N*/       {
/*N*/             CreatePrtFont( *pOut );
/*N*/           const Font aOldFnt( pRefDev->GetFont() );
/*N*/           ((OutputDevice*)pRefDev)->SetFont( *pPrtFont );
/*N*/           const FontMetric aOutMet( pRefDev->GetFontMetric() );
/*N*/           nPrtAscent = (USHORT) aOutMet.GetAscent();
/*N*/           ( (OutputDevice *)pRefDev )->SetFont( aOldFnt );
/*N*/       }
/*N*/       return nPrtAscent + nLeading;
/*N*/   }
/*N*/
/*N*/     CreateScrFont( pSh, *pOut );  // eventuell Bildschirmanpassung durchfuehren
/*N*/   return nScrAscent;
/*N*/ }

/*N*/ USHORT SwFntObj::GetHeight( const ViewShell *pSh, const OutputDevice *pOut )
/*N*/ {
/*N*/     // Condition for output font / refdev font adjustment
/*N*/     // 1. RefDef == OutDev (common printing, online layout)
/*N*/     // 2. Prospect/PagePreview pringing
/*N*/     // 3. PDF export from online layout
/*N*/     const OutputDevice* pRefDev = pOut;
/*N*/     if ( ! pSh || ( pRefDev = &pSh->GetRefDev() ) == pOut ||
/*N*/          ( OUTDEV_PRINTER == pRefDev->GetOutDevType() &&
/*N*/            OUTDEV_PRINTER == pOut->GetOutDevType() ) ||
/*N*/          OUTDEV_WINDOW == pRefDev->GetOutDevType()  )
/*N*/   {
/*N*/       if ( nPrtHeight == USHRT_MAX ) // PrinterHeight noch nicht bekannt?
/*N*/       {
/*N*/             CreatePrtFont( *pOut );
/*N*/           const Font aOldFnt( pRefDev->GetFont() );
/*N*/           ((OutputDevice*)pRefDev)->SetFont( *pPrtFont );
/*N*/           nPrtHeight = (USHORT)pRefDev->GetTextHeight();
/*N*/           ((OutputDevice *)pRefDev)->SetFont( aOldFnt );
/*N*/       }
/*N*/       return nPrtHeight + nLeading;
/*N*/   }
/*N*/
/*N*/     CreateScrFont( pSh, *pOut );  // eventuell Bildschirmanpassung durchfuehren
/*N*/   if ( nScrHeight == USHRT_MAX ) // ScreenHeight noch nicht bekannt?
/*N*/   {
/*N*/       const Font aOldFnt( pOut->GetFont() );
/*N*/       ((OutputDevice*)pOut)->SetFont( *pPrtFont );
/*N*/       nScrHeight = (USHORT)pOut->GetTextHeight();
/*N*/       ((OutputDevice*)pOut)->SetFont( aOldFnt );
/*N*/   }
/*N*/   return nScrHeight;
/*N*/ }

/*************************************************************************
 *
 *  SwFntObj::CreateScrFont( const ViewShell *pSh, const OutputDevice& rOut )
 *
 *  Ersterstellung      AMA 7. Nov. 94
 *  Letzte Aenderung    AMA 7. Nov. 94
 *
 *  pOut is the output device, not the reference device
 *
 *************************************************************************/

/*N*/ void SwFntObj::CreateScrFont( const ViewShell *pSh, const OutputDevice& rOut )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 static sal_Char __READONLY_DATA sStandardString[] = "Dies ist der Teststring";
//STRIP001
//STRIP001     if ( pScrFont )
//STRIP001         return;
//STRIP001
//STRIP001     // any changes to the output device are reset at the end of the function
//STRIP001     OutputDevice* pOut = (OutputDevice*)&rOut;
//STRIP001
//STRIP001     // Save old font
//STRIP001     Font aOldOutFont( pOut->GetFont() );
//STRIP001
//STRIP001     nScrHeight = USHRT_MAX;
//STRIP001
//STRIP001     // Condition for output font / refdev font adjustment
//STRIP001     ASSERT( pSh, "No shell available during ChooseFont" )
//STRIP001     OutputDevice* pPrt = &pSh->GetRefDev();
//STRIP001
//STRIP001 #ifdef MAC
//STRIP001
//STRIP001     if( pSh && ( !pSh->GetDoc()->IsBrowseMode() ||
//STRIP001                   pSh->GetViewOptions()->IsPrtFormat() ) )
//STRIP001     {
//STRIP001         CreatePrtFont( *pPrt );
//STRIP001         pPrinter = pPrt;
//STRIP001     }
//STRIP001
//STRIP001     bSymbol = CHARSET_SYMBOL == pPrtFont->GetCharSet();
//STRIP001     nLeading = 0;
//STRIP001     pScrFont = pPrtFont;
//STRIP001
//STRIP001 #else
//STRIP001
//STRIP001     if( pSh && ( !pSh->GetWin() || !pSh->GetDoc()->IsBrowseMode() ||
//STRIP001                   pSh->GetViewOptions()->IsPrtFormat() ) )
//STRIP001     {
//STRIP001         // After CreatePrtFont pPrtFont is the font which is actually used
//STRIP001         // by the reference device
//STRIP001         CreatePrtFont( *pPrt );
//STRIP001         pPrinter = pPrt;
//STRIP001
//STRIP001         // save old reference device font
//STRIP001         Font aOldPrtFnt( pPrt->GetFont() );
//STRIP001
//STRIP001         // set the font used at the reference device at the reference device
//STRIP001         // and the output device
//STRIP001      pPrt->SetFont( *pPrtFont );
//STRIP001         pOut->SetFont( *pPrtFont );
//STRIP001
//STRIP001         // This should be the default for pScrFont.
//STRIP001         pScrFont = pPrtFont;
//STRIP001
//STRIP001         FontMetric aMet = pPrt->GetFontMetric( );
//STRIP001         bSymbol = RTL_TEXTENCODING_SYMBOL == aMet.GetCharSet();
//STRIP001      if ( nLeading == USHRT_MAX )
//STRIP001      {
//STRIP001          long nTmpLeading = (long)aMet.GetLeading();
//STRIP001          if ( nTmpLeading < 5 )
//STRIP001          {
//STRIP001              GetAscent( pSh, pPrt );
//STRIP001              GuessLeading( pSh, aMet );
//STRIP001          }
//STRIP001          else
//STRIP001              nLeading = 0;
//STRIP001      }
//STRIP001
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      const XubString aDbgTxt1( pPrtFont->GetName() );
//STRIP001      const XubString aDbgTxt2( aMet.GetName() );
//STRIP001 #endif
//STRIP001
//STRIP001         if ( aMet.IsDeviceFont( ) )
//STRIP001      {
//STRIP001          if ( (RTL_TEXTENCODING_DONTKNOW == pPrtFont->GetCharSet() ||
//STRIP001                FAMILY_DONTKNOW  == pPrtFont->GetFamily()  ||
//STRIP001                PITCH_DONTKNOW   == pPrtFont->GetPitch()     ) &&
//STRIP001               (RTL_TEXTENCODING_DONTKNOW == aMet.GetCharSet()  ||
//STRIP001                FAMILY_DONTKNOW  == aMet.GetFamily()   ||
//STRIP001                PITCH_DONTKNOW   == aMet.GetPitch()      )    )
//STRIP001          {
//STRIP001              // Das folgende ist teuer, aber selten: ein unbekannter Font
//STRIP001              // kann vom Drucker nicht vernuenftig zugeordnet werden. Dann
//STRIP001              // nehmen wir eben das Mapping des Bildschirms in Anspruch und
//STRIP001              // setzen den Familyname, Charset und Pitch wie dort. Dieser
//STRIP001              // Font wird nun nochmals auf dem Drucker eingestellt.
//STRIP001              Font aFnt1 = pOut->GetFontMetric();
//STRIP001              Font aFnt2( *pPrtFont );
//STRIP001              aFnt2.SetCharSet( aFnt1.GetCharSet() );
//STRIP001              aFnt2.SetFamily( aFnt1.GetFamily() );
//STRIP001              aFnt2.SetPitch( aFnt1.GetPitch() );
//STRIP001              pPrt->SetFont( aFnt2 );
//STRIP001              aMet = pPrt->GetFontMetric( );
//STRIP001          }
//STRIP001
//STRIP001             const XubString aStandardStr( sStandardString,
//STRIP001              RTL_TEXTENCODING_MS_1252 );
//STRIP001
//STRIP001             // This is the reference width
//STRIP001             const long nOWidth = pPrt->GetTextWidth( aStandardStr );
//STRIP001
//STRIP001             // Let's have a look what's the difference to the width
//STRIP001             // calculated for the output device using the font set at the
//STRIP001             // reference device
//STRIP001          long nSWidth = nOWidth - pOut->GetTextWidth( aStandardStr );
//STRIP001          nScrHeight = (USHORT) pOut->GetTextHeight();
//STRIP001
//STRIP001          // Um Aerger mit dem Generic Printer aus dem Wege zu gehen.
//STRIP001          if( aMet.GetSize().Height() )
//STRIP001          {
//STRIP001              BOOL bScrSymbol;
//STRIP001              CharSet ePrtChSet = aMet.GetCharSet();
//STRIP001              // NoSymbol bedeutet, dass der Drucker sich fuer einen
//STRIP001              // Nicht-Symbol-Font entschieden hat.
//STRIP001              BOOL bNoSymbol = ( RTL_TEXTENCODING_DONTKNOW != ePrtChSet &&
//STRIP001                                 RTL_TEXTENCODING_SYMBOL != ePrtChSet );
//STRIP001              if ( bNoSymbol )
//STRIP001                  bScrSymbol = RTL_TEXTENCODING_SYMBOL ==
//STRIP001                               pOut->GetFontMetric().GetCharSet();
//STRIP001                 Size aTmp( aMet.GetSize() );
//STRIP001
//STRIP001                 if( aTmp.Width() && !pPrtFont->GetSize().Width() )
//STRIP001                 {
//STRIP001                     aTmp.Width() = 0;
//STRIP001                     aMet.SetSize( aTmp );
//STRIP001                 }
//STRIP001
//STRIP001                 // Now we set the metrics used at the reference device at the
//STRIP001                 // output device
//STRIP001                 pOut->SetFont( aMet );
//STRIP001
//STRIP001              if( bNoSymbol && ( bScrSymbol != ( RTL_TEXTENCODING_SYMBOL ==
//STRIP001                                      pOut->GetFontMetric().GetCharSet() ) ) )
//STRIP001              {
//STRIP001                  // Hier landen wir, wenn der Drucker keinen Symbolfont waehlt,
//STRIP001                  // aber genau einer der beiden Screenfonts ein Symbolfont ist.
//STRIP001                  // Wir nehmen dann eben den anderen.
//STRIP001                  if ( bScrSymbol )
//STRIP001                         pScrFont = new Font( aMet ); // mit Abgleich
//STRIP001                  else
//STRIP001                         pOut->SetFont( *pPrtFont ); // ohne Abgleich
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                     // Let's have a look what's the difference to the width
//STRIP001                     // calculated for the output device using the metrics set at
//STRIP001                     // the reference device
//STRIP001                     long nPWidth = nOWidth - pOut->GetTextWidth( aStandardStr );
//STRIP001
//STRIP001                     // We prefer smaller fonts
//STRIP001                     BYTE nNeg = 0;
//STRIP001                     if ( nSWidth<0 ) { nSWidth *= -2; nNeg = 1; }
//STRIP001                     if ( nPWidth<0 ) { nPWidth *= -2; nNeg |= 2; }
//STRIP001                  if ( nSWidth <= nPWidth )
//STRIP001                     {
//STRIP001                         // No adjustment, we take the same font for the output
//STRIP001                         // device like for the reference device
//STRIP001                         pOut->SetFont( *pPrtFont );
//STRIP001                         pScrFont = pPrtFont;
//STRIP001                         nPWidth = nSWidth;
//STRIP001                         nNeg &= 1;
//STRIP001                     }
//STRIP001                  else
//STRIP001                     {
//STRIP001                         // The metrics give a better result. So we build
//STRIP001                         // a new font for the output device based on the
//STRIP001                         // metrics used at the reference device
//STRIP001                         pScrFont = new Font( aMet ); // mit Abgleich
//STRIP001                         nSWidth = nPWidth;
//STRIP001                         nNeg &= 2;
//STRIP001                     }
//STRIP001
//STRIP001                     //
//STRIP001                     // now pScrFont is set to the better font and this should
//STRIP001                     // be set at the output device
//STRIP001                     //
//STRIP001
//STRIP001                     // we still have to check if the choosed font is not to wide
//STRIP001                     if( nNeg && nOWidth )
//STRIP001                     {
//STRIP001                         nPWidth *= 100;
//STRIP001                         nPWidth /= nOWidth;
//STRIP001
//STRIP001                         // if the screen font is too wide, we try to reduce
//STRIP001                         // the font height and get a smaller one
//STRIP001                         if( nPWidth > 25 )
//STRIP001                         {
//STRIP001                             if( nPWidth > 80 )
//STRIP001                                 nPWidth = 80;
//STRIP001                             nPWidth = 100 - nPWidth/4;
//STRIP001                             Size aTmp = pScrFont->GetSize();
//STRIP001                             aTmp.Height() *= nPWidth;
//STRIP001                             aTmp.Height() /= 100;
//STRIP001                             if( aTmp.Width() )
//STRIP001                             {
//STRIP001                                 aTmp.Width() *= nPWidth;
//STRIP001                                 aTmp.Width() /= 100;
//STRIP001                             }
//STRIP001                             Font *pNew = new Font( *pScrFont );
//STRIP001                             pNew->SetSize( aTmp );
//STRIP001                             pOut->SetFont( *pNew );
//STRIP001                             nPWidth = nOWidth -
//STRIP001                                       pOut->GetTextWidth( aStandardStr );
//STRIP001                             if( nPWidth < 0 ) { nPWidth *= -2; }
//STRIP001                             if( nPWidth < nSWidth )
//STRIP001                             {
//STRIP001                                 if( pScrFont != pPrtFont )
//STRIP001                                     delete pScrFont;
//STRIP001                                 pScrFont = pNew;
//STRIP001                             }
//STRIP001                             else
//STRIP001                             {
//STRIP001                                 delete pNew;
//STRIP001                                 pOut->SetFont( *pScrFont );
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001         // reset the original reference device font
//STRIP001         pPrt->SetFont( aOldPrtFnt );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      bSymbol = RTL_TEXTENCODING_SYMBOL == aFont.GetCharSet();
//STRIP001      if ( nLeading == USHRT_MAX )
//STRIP001          nLeading = 0;
//STRIP001         pScrFont = pPrtFont;
//STRIP001     }
//STRIP001
//STRIP001 #endif
//STRIP001
//STRIP001     // Zoomfaktor ueberpruefen, z.B. wg. PrtOle2 beim Speichern
//STRIP001  {
//STRIP001      // Sollte der Zoomfaktor des OutputDevices nicht mit dem der View-
//STRIP001      // Options uebereinstimmen, so darf dieser Font nicht gecacht
//STRIP001      // werden, deshalb wird der Zoomfaktor auf einen "ungueltigen" Wert
//STRIP001      // gesetzt.
//STRIP001      long nTmp;
//STRIP001      if( pOut->GetMapMode().GetScaleX().IsValid() &&
//STRIP001          pOut->GetMapMode().GetScaleY().IsValid() &&
//STRIP001          pOut->GetMapMode().GetScaleX() == pOut->GetMapMode().GetScaleY() )
//STRIP001      {
//STRIP001          nTmp = ( 100 * pOut->GetMapMode().GetScaleX().GetNumerator() ) /
//STRIP001                   pOut->GetMapMode().GetScaleX().GetDenominator();
//STRIP001      }
//STRIP001      else
//STRIP001          nTmp = 0;
//STRIP001      if( nTmp != nZoom )
//STRIP001          nZoom = USHRT_MAX - 1;
//STRIP001  }
//STRIP001
//STRIP001     nScrAscent = (USHORT)pOut->GetFontMetric().GetAscent();
//STRIP001
//STRIP001     // reset original output device font
//STRIP001     pOut->SetFont( aOldOutFont );
/*N*/ }


/*N*/ void SwFntObj::GuessLeading( const ViewShell *pSh, const FontMetric& rMet )
/*N*/ {
/*N*/ //  Wie waere es mit 50% des Descents (StarMath??):
/*N*/ //    nLeading = USHORT( aMet.GetDescent() / 2 );
/*N*/
/*N*/ #if defined(WNT) || defined(WIN) || defined(PM2)
/*N*/   OutputDevice *pWin = ( pSh && pSh->GetWin() ) ? pSh->GetWin() :
/*N*/                        GetpApp()->GetDefaultDevice();
/*N*/   if ( pWin )
/*N*/   {
/*N*/       MapMode aTmpMap( MAP_TWIP );
/*N*/       MapMode aOldMap = pWin->GetMapMode( );
/*N*/       pWin->SetMapMode( aTmpMap );
/*N*/       const Font aOldFnt( pWin->GetFont() );
/*N*/       pWin->SetFont( *pPrtFont );
/*N*/       const FontMetric aWinMet( pWin->GetFontMetric() );
/*N*/       const USHORT nWinHeight = USHORT( aWinMet.GetSize().Height() );
/*N*/       if( pPrtFont->GetName().Search( aWinMet.GetName() ) < USHRT_MAX )
/*N*/       {
/*N*/           // Wenn das Leading auf dem Window auch 0 ist, dann
/*N*/           // muss es auch so bleiben (vgl. StarMath!).
/*N*/           long nTmpLeading = (long)aWinMet.GetLeading();
/*N*/            // einen Versuch haben wir noch wg. 31003:
/*N*/           if( nTmpLeading <= 0 )
/*N*/           {
/*N*/               pWin->SetFont( rMet );
/*N*/               nTmpLeading = (long)pWin->GetFontMetric().GetLeading();
/*N*/               if( nTmpLeading < 0 )
/*N*/                   nLeading = 0;
/*N*/               else
/*N*/                   nLeading = USHORT(nTmpLeading);
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               nLeading = USHORT(nTmpLeading);
/*?*/               // Manta-Hack #50153#:
/*?*/               // Wer beim Leading luegt, luegt moeglicherweise auch beim
/*?*/               // Ascent/Descent, deshalb wird hier ggf. der Font ein wenig
/*?*/               // tiefergelegt, ohne dabei seine Hoehe zu aendern.
/*?*/               long nDiff = Min( rMet.GetDescent() - aWinMet.GetDescent(),
/*?*/                   aWinMet.GetAscent() - rMet.GetAscent() - nTmpLeading );
/*?*/               if( nDiff > 0 )
/*?*/               {
/*?*/                   ASSERT( nPrtAscent < USHRT_MAX, "GuessLeading: PrtAscent-Fault" );
/*?*/                   nPrtAscent += (USHORT)(( 2 * nDiff ) / 5);
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Wenn alle Stricke reissen, nehmen wir 15% der
/*N*/           // Hoehe, ein von CL empirisch ermittelter Wert.
/*?*/           nLeading = (nWinHeight * 15) / 100;
/*N*/       }
/*N*/       pWin->SetFont( aOldFnt );
/*N*/       pWin->SetMapMode( aOldMap );
/*N*/   }
/*N*/   else
/*N*/ #endif
/*N*/ #ifdef MAC
/*N*/       nLeading = (pPrtFont->GetSize().Height() * 15) / 100;
/*N*/ #else
/*N*/       nLeading = 0;
/*N*/ #endif
/*N*/ }

/*************************************************************************
 *
 *  void SwFntObj::SetDeviceFont( const OutputDevice *pOut ),
 *
 *  Ersterstellung      AMA 7. Nov. 94
 *  Letzte Aenderung    AMA 7. Nov. 94
 *
 *  Beschreibung: stellt den Font am gewuenschten OutputDevice ein,
 *  am Bildschirm muss eventuell erst den Abgleich durchgefuehrt werden.
 *
 *************************************************************************/

/*N*/ void SwFntObj::SetDevFont( const ViewShell *pSh, OutputDevice *pOut )
/*N*/ {
/*N*/     // Condition for output font / refdev font adjustment
    // 1. RefDef == OutDev (common printing, online layout)
    // 2. Prospect/PagePreview pringing
    // 3. PDF export from online layout
/*N*/     const OutputDevice* pRefDev = pOut;
/*N*/     if ( pSh && ( pRefDev = &pSh->GetRefDev() ) != pOut &&
/*N*/          ( OUTDEV_PRINTER != pRefDev->GetOutDevType() ||
/*N*/            OUTDEV_PRINTER != pOut->GetOutDevType() ) &&
/*N*/          OUTDEV_WINDOW != pRefDev->GetOutDevType() )
/*N*/     {
/*?*/         CreateScrFont( pSh, *pOut );
/*?*/         if( !GetScrFont()->IsSameInstance( pOut->GetFont() ) )
/*?*/             pOut->SetFont( *pScrFont );
/*?*/         if( pPrinter && ( !pPrtFont->IsSameInstance( pPrinter->GetFont() ) ) )
/*?*/             pPrinter->SetFont( *pPrtFont );
/*N*/     }
/*N*/     else
/*N*/   {
/*N*/         CreatePrtFont( *pOut );
/*N*/       if( !pPrtFont->IsSameInstance( pOut->GetFont() ) )
/*N*/           pOut->SetFont( *pPrtFont );
/*N*/       if ( nLeading == USHRT_MAX )
/*N*/       {
/*N*/           FontMetric aMet( pOut->GetFontMetric() );
/*N*/           bSymbol = RTL_TEXTENCODING_SYMBOL == aMet.GetCharSet();
/*N*/           long nTmpLead = (long)aMet.GetLeading();
/*N*/           if ( nTmpLead < 5 )
/*N*/           {
/*N*/               GetAscent( pSh, pOut );
/*N*/               GuessLeading( pSh, aMet );
/*N*/           }
/*N*/           else
/*N*/               nLeading = 0;
/*N*/       }
/*N*/   }
/*N*/ }

#define WRONG_SHOW_MIN 5
#define WRONG_SHOW_SMALL 11
#define WRONG_SHOW_MEDIUM 15

/*************************************************************************
 *
 * void SwFntObj::DrawText( ... )
 *
 *  Ersterstellung      AMA 16. Dez. 94
 *  Letzte Aenderung    AMA 16. Dez. 94
 *
 *  Beschreibung: Textausgabe
 *                  auf dem Bildschirm          => DrawTextArray
 *                  auf dem Drucker, !Kerning   => DrawText
 *                  auf dem Drucker + Kerning   => DrawStretchText
 *
 *************************************************************************/

//STRIP001 BYTE lcl_WhichPunctuation( xub_Unicode cChar )
//STRIP001 {
//STRIP001     if ( ( cChar < 0x3001 || cChar > 0x3002 ) &&
//STRIP001             ( cChar < 0x3008 || cChar > 0x3011 ) &&
//STRIP001             ( cChar < 0x3014 || cChar > 0x301F ) &&
//STRIP001               0xFF62 != cChar && 0xFF63 != cChar )
//STRIP001         // no punctuation
//STRIP001         return SwScriptInfo::NONE;
//STRIP001     else if ( 0x3001 == cChar || 0x3002 == cChar ||
//STRIP001               0x3009 == cChar || 0x300B == cChar ||
//STRIP001               0x300D == cChar || 0x300F == cChar ||
//STRIP001               0x3011 == cChar || 0x3015 == cChar ||
//STRIP001               0x3017 == cChar || 0x3019 == cChar ||
//STRIP001               0x301B == cChar || 0x301E == cChar ||
//STRIP001               0x301F == cChar || 0xFF63 == cChar )
//STRIP001         // right punctuation
//STRIP001         return SwScriptInfo::SPECIAL_RIGHT;
//STRIP001
//STRIP001     return SwScriptInfo::SPECIAL_LEFT;
//STRIP001 }

/*N*/ sal_Bool lcl_IsMonoSpaceFont( const OutputDevice* pOut )
/*N*/ {DBG_ASSERT(0, "STRIP"); return sal_False; //STRIP001
//STRIP001 /*?*/     if ( ! pOut )
//STRIP001 /*?*/         return sal_False;
//STRIP001 /*?*/
//STRIP001 /*?*/     const String aStr1( xub_Unicode( 0x3008 ) );
//STRIP001 /*?*/     const String aStr2( xub_Unicode( 0x307C ) );
//STRIP001 /*?*/ #ifndef PRODUCT
//STRIP001 /*?*/     const long nWidth1 = pOut->GetTextWidth( aStr1 );
//STRIP001 /*?*/     const long nWidth2 = pOut->GetTextWidth( aStr2 );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/     return pOut->GetTextWidth( aStr1 ) == pOut->GetTextWidth( aStr2 );
/*N*/ }

// ER 09.07.95 20:34
// mit -Ox Optimierung stuerzt's unter win95 ab
// JP 12.07.95: unter WNT auch (i386);       Alpha ??
// global optimization off
#if defined( WNT ) && defined( MSC ) //&& defined( W40 )
#pragma optimize("g",off)
#endif

//STRIP001 void SwFntObj::DrawText( SwDrawTextInfo &rInf )
//STRIP001 {
//STRIP001     OutputDevice* pRefDev = NULL;
//STRIP001     OutputDevice* pWin = NULL;
//STRIP001
//STRIP001     if ( rInf.GetShell() )
//STRIP001     {
//STRIP001         pRefDev = &rInf.GetShell()->GetRefDev();
//STRIP001         pWin = rInf.GetShell()->GetWin();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         ASSERT( sal_True, "DrawText without shell" )
//STRIP001         pRefDev = rInf.GetpOut();
//STRIP001     }
//STRIP001
//STRIP001     // true if pOut is the printer and the printer has been used for formatting
//STRIP001     const BOOL bPrt = OUTDEV_PRINTER == rInf.GetOut().GetOutDevType() &&
//STRIP001                       OUTDEV_PRINTER == pRefDev->GetOutDevType();
//STRIP001     const BOOL bBrowse = ( pWin &&
//STRIP001                            rInf.GetShell()->GetDoc()->IsBrowseMode() &&
//STRIP001                           !rInf.GetShell()->GetViewOptions()->IsPrtFormat() &&
//STRIP001                           !rInf.GetBullet() &&
//STRIP001                            ( rInf.GetSpace() || !rInf.GetKern() ) &&
//STRIP001                           !rInf.GetWrong() &&
//STRIP001                           !rInf.GetGreyWave() );
//STRIP001
//STRIP001     // bDirectPrint indicates that we can enter the branch which calls
//STRIP001     // the DrawText functions instead of calling the DrawTextArray functions
//STRIP001     const BOOL bDirectPrint = bPrt || bBrowse;
//STRIP001
//STRIP001     // Condition for output font / refdev font adjustment
//STRIP001     const BOOL bUseScrFont = pRefDev != rInf.GetpOut() &&
//STRIP001                              ( OUTDEV_PRINTER != pRefDev->GetOutDevType() ||
//STRIP001                                OUTDEV_PRINTER != rInf.GetpOut()->GetOutDevType() ) &&
//STRIP001                              OUTDEV_WINDOW != pRefDev->GetOutDevType();;
//STRIP001
//STRIP001     Font* pTmpFont = bUseScrFont ? pScrFont : pPrtFont;
//STRIP001
//STRIP001     //
//STRIP001     //  bDirectPrint and bUseScrFont should have these values:
//STRIP001     //
//STRIP001     //  Outdev / RefDef  | Printer | VirtPrinter | Window
//STRIP001     // ----------------------------------------------------
//STRIP001     //  Printer          | 1 - 0   | 0 - 1       | -
//STRIP001     // ----------------------------------------------------
//STRIP001     //  VirtPrinter/PDF  | 0 - 1   | 0 - 1       | -
//STRIP001     // ----------------------------------------------------
//STRIP001     //  Window/VirtWindow| 0 - 1   | 0 - 1       | 1 - 0
//STRIP001     //
//STRIP001     // Exception: During painting of a Writer OLE object, we do not have
//STRIP001     // a window. Therefore bUseSrcFont is always 0 in this case.
//STRIP001     //
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001
//STRIP001     const BOOL bNoAdjust = bPrt || ( pWin && rInf.GetShell()->GetDoc()->IsBrowseMode() &&
//STRIP001                                      !rInf.GetShell()->GetViewOptions()->IsPrtFormat() );
//STRIP001
//STRIP001     if ( OUTDEV_PRINTER == rInf.GetpOut()->GetOutDevType() )
//STRIP001     {
//STRIP001         // Printer output
//STRIP001         if ( OUTDEV_PRINTER == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 1 && bUseScrFont == 0, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else if ( OUTDEV_VIRDEV == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 0 && bUseScrFont == 1, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             ASSERT( sal_False, "Outdev Check failed" )
//STRIP001         }
//STRIP001     }
//STRIP001     else if ( OUTDEV_VIRDEV == rInf.GetpOut()->GetOutDevType() && ! pWin )
//STRIP001     {
//STRIP001         // PDF export
//STRIP001         if ( OUTDEV_PRINTER == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 0 && bUseScrFont == 1, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else if ( OUTDEV_VIRDEV == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 0 && bUseScrFont == 1, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             ASSERT( sal_False, "Outdev Check failed" )
//STRIP001         }
//STRIP001     }
//STRIP001     else if ( OUTDEV_WINDOW == rInf.GetpOut()->GetOutDevType() ||
//STRIP001                ( OUTDEV_VIRDEV == rInf.GetpOut()->GetOutDevType() && pWin ) )
//STRIP001     {
//STRIP001         // Window or virtual window
//STRIP001         if ( OUTDEV_PRINTER == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 0 && bUseScrFont == 1, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else if ( OUTDEV_VIRDEV == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 0 && bUseScrFont == 1, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else if ( OUTDEV_WINDOW == pRefDev->GetOutDevType() )
//STRIP001         {
//STRIP001             ASSERT( bNoAdjust == 1 && bUseScrFont == 0, "Outdev Check failed" )
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             ASSERT( sal_False, "Outdev Check failed" )
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001             ASSERT( sal_False, "Outdev Check failed" )
//STRIP001     }
//STRIP001
//STRIP001 #endif
//STRIP001
//STRIP001     // robust: better use the printer font instead of using no font at all
//STRIP001     ASSERT( pTmpFont, "No screen or printer font?" );
//STRIP001     if ( ! pTmpFont )
//STRIP001         pTmpFont = pPrtFont;
//STRIP001
//STRIP001     // HACK: UNDERLINE_WAVE darf nicht mehr missbraucht werden, daher
//STRIP001     // wird die graue Wellenlinie des ExtendedAttributSets zunaechst
//STRIP001     // in der Fontfarbe erscheinen.
//STRIP001
//STRIP001     const BOOL bSwitchH2V = rInf.GetFrm() && rInf.GetFrm()->IsVertical();
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     const BOOL bSwitchL2R = rInf.GetFrm() && rInf.GetFrm()->IsRightToLeft() &&
//STRIP001                             ! rInf.IsIgnoreFrmRTL();
//STRIP001     const ULONG nMode = rInf.GetpOut()->GetLayoutMode();
//STRIP001     const BOOL bBidiPor = ( bSwitchL2R !=
//STRIP001                             ( 0 != ( TEXT_LAYOUT_BIDI_RTL & nMode ) ) );
//STRIP001
//STRIP001     // be sure to have the correct layout mode at the printer
//STRIP001     if ( pPrinter )
//STRIP001     {
//STRIP001         pPrinter->SetLayoutMode( rInf.GetpOut()->GetLayoutMode() );
//STRIP001         pPrinter->SetDigitLanguage( rInf.GetpOut()->GetDigitLanguage() );
//STRIP001     }
//STRIP001 #endif
//STRIP001
//STRIP001     Point aPos( rInf.GetPos() );
//STRIP001     if( !bPrt )
//STRIP001     {
//STRIP001         if( rInf.GetpOut() != pPixOut || rInf.GetOut().GetMapMode() != *pPixMap )
//STRIP001         {
//STRIP001             *pPixMap = rInf.GetOut().GetMapMode();
//STRIP001             pPixOut = rInf.GetpOut();
//STRIP001             Size aTmp( 1, 1 );
//STRIP001             nPixWidth = rInf.GetOut().PixelToLogic( aTmp ).Width();
//STRIP001         }
//STRIP001
//STRIP001         aPos.X() += rInf.GetFrm()->IsRightToLeft() ? 0 : nPixWidth;
//STRIP001     }
//STRIP001
//STRIP001     Color aOldColor( pTmpFont->GetColor() );
//STRIP001     sal_Bool bChgColor = rInf.ApplyAutoColor( pTmpFont );
//STRIP001     if( !pTmpFont->IsSameInstance( rInf.GetOut().GetFont() ) )
//STRIP001         rInf.GetOut().SetFont( *pTmpFont );
//STRIP001     if ( bChgColor )
//STRIP001         pTmpFont->SetColor( aOldColor );
//STRIP001
//STRIP001     if ( STRING_LEN == rInf.GetLen() )
//STRIP001         rInf.SetLen( rInf.GetText().Len() );
//STRIP001
//STRIP001     if ( rInf.GetFrm() && rInf.SnapToGrid() && rInf.GetFont() &&
//STRIP001          SW_CJK == rInf.GetFont()->GetActual() )
//STRIP001     {
//STRIP001         GETGRID( rInf.GetFrm()->FindPageFrm() )
//STRIP001         if ( pGrid && GRID_LINES_CHARS == pGrid->GetGridType() )
//STRIP001         {
//STRIP001             const USHORT nGridWidth = pGrid->GetBaseHeight();
//STRIP001             long* pKernArray = new long[rInf.GetLen()];
//STRIP001
//STRIP001             if ( pPrinter )
//STRIP001                 pPrinter->GetTextArray( rInf.GetText(), pKernArray,
//STRIP001                                         rInf.GetIdx(), rInf.GetLen() );
//STRIP001             else
//STRIP001                 rInf.GetOut().GetTextArray( rInf.GetText(), pKernArray,
//STRIP001                                             rInf.GetIdx(), rInf.GetLen() );
//STRIP001
//STRIP001             long nWidthPerChar = pKernArray[ rInf.GetLen() - 1 ] / rInf.GetLen();
//STRIP001
//STRIP001             const ULONG i = nWidthPerChar ?
//STRIP001                                 ( nWidthPerChar - 1 ) / nGridWidth + 1:
//STRIP001                                 1;
//STRIP001
//STRIP001             nWidthPerChar = i * nGridWidth;
//STRIP001
//STRIP001             // position of first character, we take the printer position
//STRIP001             long nCharWidth = pKernArray[ 0 ];
//STRIP001             ULONG nHalfWidth = nWidthPerChar / 2;
//STRIP001
//STRIP001             long nNextFix;
//STRIP001
//STRIP001             // punctuation characters are not centered
//STRIP001             xub_Unicode cChar = rInf.GetText().GetChar( rInf.GetIdx() );
//STRIP001             BYTE nType = lcl_WhichPunctuation( cChar );
//STRIP001             switch ( nType )
//STRIP001             {
//STRIP001             case SwScriptInfo::NONE :
//STRIP001                 aPos.X() += ( nWidthPerChar - nCharWidth ) / 2;
//STRIP001                 nNextFix = nCharWidth / 2;
//STRIP001                 break;
//STRIP001             case SwScriptInfo::SPECIAL_RIGHT :
//STRIP001                 nNextFix = nHalfWidth;
//STRIP001                 break;
//STRIP001             default:
//STRIP001                 aPos.X() += nWidthPerChar - nCharWidth;
//STRIP001                 nNextFix = nCharWidth - nHalfWidth;
//STRIP001             }
//STRIP001
//STRIP001             // calculate offsets
//STRIP001             for ( xub_StrLen j = 1; j < rInf.GetLen(); ++j )
//STRIP001             {
//STRIP001                 long nScr = pKernArray[ j ] - pKernArray[ j - 1 ];
//STRIP001                 nNextFix += nWidthPerChar;
//STRIP001
//STRIP001                 // punctuation characters are not centered
//STRIP001                 cChar = rInf.GetText().GetChar( rInf.GetIdx() + j );
//STRIP001                 nType = lcl_WhichPunctuation( cChar );
//STRIP001                 switch ( nType )
//STRIP001                 {
//STRIP001                 case SwScriptInfo::NONE :
//STRIP001                     pKernArray[ j - 1 ] = nNextFix - ( nScr / 2 );
//STRIP001                     break;
//STRIP001                 case SwScriptInfo::SPECIAL_RIGHT :
//STRIP001                     pKernArray[ j - 1 ] = nNextFix - nHalfWidth;
//STRIP001                     break;
//STRIP001                 default:
//STRIP001                     pKernArray[ j - 1 ] = nNextFix + nHalfWidth - nScr;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             // the layout engine requires the total width of the output
//STRIP001             pKernArray[ rInf.GetLen() - 1 ] = rInf.GetWidth() -
//STRIP001                                               aPos.X() + rInf.GetPos().X() ;
//STRIP001
//STRIP001             if ( bSwitchH2V )
//STRIP001                 rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001
//STRIP001             rInf.GetOut().DrawTextArray( aPos, rInf.GetText(),
//STRIP001                 pKernArray, rInf.GetIdx(), rInf.GetLen() );
//STRIP001
//STRIP001             delete[] pKernArray;
//STRIP001             return;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // "No screen adj"
//STRIP001     if ( bDirectPrint )
//STRIP001     {
//STRIP001         const Fraction aTmp( 1, 1 );
//STRIP001         BOOL bStretch = rInf.GetWidth() && ( rInf.GetLen() > 1 ) && bPrt
//STRIP001                         && ( aTmp != rInf.GetOut().GetMapMode().GetScaleX() );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if ( bSwitchL2R )
//STRIP001             rInf.GetFrm()->SwitchLTRtoRTL( aPos );
//STRIP001 #endif
//STRIP001
//STRIP001         if ( bSwitchH2V )
//STRIP001             rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001
//STRIP001         // In the good old days we used to have a simple DrawText if the
//STRIP001         // output device is the printer. Now we need a DrawTextArray if
//STRIP001         // 1. KanaCompression is enabled
//STRIP001         // 2. Justified alignment
//STRIP001         // Simple kerning is handled by DrawStretchText
//STRIP001         if( rInf.GetSpace() || rInf.GetKanaComp() )
//STRIP001         {
//STRIP001             long *pKernArray = new long[ rInf.GetLen() ];
//STRIP001             rInf.GetOut().GetTextArray( rInf.GetText(), pKernArray,
//STRIP001                                        rInf.GetIdx(), rInf.GetLen() );
//STRIP001
//STRIP001             if( bStretch )
//STRIP001             {
//STRIP001                 xub_StrLen nZwi = rInf.GetLen() - 1;
//STRIP001                 long nDiff = rInf.GetWidth() - pKernArray[ nZwi ]
//STRIP001                              - rInf.GetLen() * rInf.GetKern();
//STRIP001                 long nRest = nDiff % nZwi;
//STRIP001                 long nAdd;
//STRIP001                 if( nRest < 0 )
//STRIP001                 {
//STRIP001                     nAdd = -1;
//STRIP001                     nRest += nZwi;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     nAdd = +1;
//STRIP001                     nRest = nZwi - nRest;
//STRIP001                 }
//STRIP001                 nDiff /= nZwi;
//STRIP001                 long nSum = nDiff;
//STRIP001                 for( xub_StrLen i = 0; i < nZwi; )
//STRIP001                 {
//STRIP001                     pKernArray[ i ] += nSum;
//STRIP001                     if( ++i == nRest )
//STRIP001                         nDiff += nAdd;
//STRIP001                     nSum += nDiff;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             //
//STRIP001             // Modify Array for special justifications
//STRIP001             //
//STRIP001             short nSpaceAdd = rInf.GetSpace();
//STRIP001             sal_Bool bSpecialJust = sal_False;
//STRIP001
//STRIP001             if ( rInf.GetFont() && rInf.GetLen() )
//STRIP001             {
//STRIP001                 const SwScriptInfo* pSI = rInf.GetScriptInfo();
//STRIP001                 const BYTE nActual = rInf.GetFont()->GetActual();
//STRIP001
//STRIP001                 // Kana Compression
//STRIP001                 if ( SW_CJK == nActual && rInf.GetKanaComp() &&
//STRIP001                      pSI && pSI->CountCompChg() &&
//STRIP001                      lcl_IsMonoSpaceFont( rInf.GetpOut() ) )
//STRIP001                 {
//STRIP001                     pSI->Compress( pKernArray, rInf.GetIdx(), rInf.GetLen(),
//STRIP001                                    rInf.GetKanaComp(),
//STRIP001                                    (USHORT)aFont.GetSize().Height(), &aPos );
//STRIP001                     bSpecialJust = sal_True;
//STRIP001                 }
//STRIP001
//STRIP001                 // Asian Justification
//STRIP001                 if ( SW_CJK == nActual && nSpaceAdd )
//STRIP001                 {
//STRIP001                     LanguageType aLang = rInf.GetFont()->GetLanguage( SW_CJK );
//STRIP001
//STRIP001                     if ( LANGUAGE_KOREAN != aLang && LANGUAGE_KOREAN_JOHAB != aLang )
//STRIP001                     {
//STRIP001                         long nSpaceSum = nSpaceAdd;
//STRIP001                         for ( USHORT nI = 0; nI < rInf.GetLen(); ++nI )
//STRIP001                         {
//STRIP001                             pKernArray[ nI ] += nSpaceSum;
//STRIP001                             nSpaceSum += nSpaceAdd;
//STRIP001                         }
//STRIP001
//STRIP001                         bSpecialJust = sal_True;
//STRIP001                         nSpaceAdd = 0;
//STRIP001                     }
//STRIP001                 }
//STRIP001
//STRIP001                 // Thai Justification
//STRIP001                 if ( SW_CTL == nActual && nSpaceAdd  )
//STRIP001                 {
//STRIP001
//STRIP001                     LanguageType aLang = rInf.GetFont()->GetLanguage( SW_CTL );
//STRIP001
//STRIP001                     if ( LANGUAGE_THAI == aLang )
//STRIP001                     {
//STRIP001                         SwScriptInfo::ThaiJustify( rInf.GetText(), pKernArray, 0,
//STRIP001                                                    rInf.GetIdx(), rInf.GetLen(),
//STRIP001                                                    nSpaceAdd );
//STRIP001
//STRIP001                         // adding space to blanks is already done
//STRIP001                         bSpecialJust = sal_True;
//STRIP001                         nSpaceAdd = 0;
//STRIP001                     }
//STRIP001                 }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001                 // Kashida Justification
//STRIP001                 if ( SW_CTL == nActual && nSpaceAdd )
//STRIP001                 {
//STRIP001                     if ( SwScriptInfo::IsArabicLanguage( rInf.GetFont()->
//STRIP001                                                          GetLanguage( SW_CTL ) ) )
//STRIP001                     {
//STRIP001                         if ( pSI && pSI->CountKashida() )
//STRIP001                             pSI->KashidaJustify( pKernArray, 0, rInf.GetIdx(),
//STRIP001                                                 rInf.GetLen(), nSpaceAdd );
//STRIP001
//STRIP001                         bSpecialJust = sal_True;
//STRIP001                         nSpaceAdd = 0;
//STRIP001                     }
//STRIP001                 }
//STRIP001 #endif
//STRIP001             }
//STRIP001
//STRIP001             long nKernSum = rInf.GetKern();
//STRIP001
//STRIP001             if ( bStretch || bPaintBlank || rInf.GetKern() || bSpecialJust )
//STRIP001             {
//STRIP001                 for( xub_StrLen i = 0; i < rInf.GetLen(); i++,
//STRIP001                      nKernSum += rInf.GetKern() )
//STRIP001                 {
//STRIP001                     if ( CH_BLANK == rInf.GetText().GetChar(rInf.GetIdx()+i) )
//STRIP001                         nKernSum += nSpaceAdd;
//STRIP001                     pKernArray[i] += nKernSum;
//STRIP001                 }
//STRIP001
//STRIP001              // Bei durch/unterstr. Blocksatz erfordert ein Blank am Ende
//STRIP001              // einer Textausgabe besondere Massnahmen:
//STRIP001              if( bPaintBlank && rInf.GetLen() && ( CH_BLANK ==
//STRIP001                  rInf.GetText().GetChar( rInf.GetIdx()+rInf.GetLen()-1 ) ) )
//STRIP001              {
//STRIP001                  // Wenn es sich um ein singulaeres, unterstrichenes Space
//STRIP001                  // handelt, muessen wir zwei ausgeben:
//STRIP001                  if( 1 == rInf.GetLen() )
//STRIP001                  {
//STRIP001                          pKernArray[0] = rInf.GetWidth() + nSpaceAdd;
//STRIP001
//STRIP001                      rInf.GetOut().DrawTextArray( aPos, rInf.GetText(),
//STRIP001                                                   pKernArray, rInf.GetIdx(), 1 );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                         pKernArray[ rInf.GetLen() - 2 ] += nSpaceAdd;
//STRIP001                         rInf.GetOut().DrawTextArray( aPos, rInf.GetText(),
//STRIP001                             pKernArray, rInf.GetIdx(), rInf.GetLen() );
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                     rInf.GetOut().DrawTextArray( aPos, rInf.GetText(),
//STRIP001                                                  pKernArray, rInf.GetIdx(), rInf.GetLen() );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 Point aTmpPos( aPos );
//STRIP001                 xub_StrLen j = 0;
//STRIP001                 xub_StrLen i;
//STRIP001                 for( i = 0; i < rInf.GetLen(); i++ )
//STRIP001                 {
//STRIP001                     if( CH_BLANK == rInf.GetText().GetChar( rInf.GetIdx()+i ) )
//STRIP001                     {
//STRIP001                         nKernSum += nSpaceAdd;
//STRIP001                         if( j < i )
//STRIP001                         rInf.GetOut().DrawText( aTmpPos, rInf.GetText(),
//STRIP001                                                 rInf.GetIdx() + j, i - j );
//STRIP001                         j = i + 1;
//STRIP001 #ifdef BIDI
//STRIP001                         SwTwips nAdd = pKernArray[ i ] + nKernSum;
//STRIP001                         if ( ( TEXT_LAYOUT_BIDI_STRONG | TEXT_LAYOUT_BIDI_RTL ) == nMode )
//STRIP001                             nAdd *= -1;
//STRIP001                         aTmpPos.X() = aPos.X() + nAdd;
//STRIP001 #else
//STRIP001                         aTmpPos.X() = aPos.X() + pKernArray[ i ] + nKernSum;
//STRIP001 #endif
//STRIP001                     }
//STRIP001                 }
//STRIP001                 if( j < i )
//STRIP001                     rInf.GetOut().DrawText( aTmpPos, rInf.GetText(),
//STRIP001                                             rInf.GetIdx() + j, i - j );
//STRIP001             }
//STRIP001             delete[] pKernArray;
//STRIP001         }
//STRIP001         else if( bStretch )
//STRIP001         {
//STRIP001             USHORT nTmpWidth = rInf.GetWidth();
//STRIP001             if( rInf.GetKern() && rInf.GetLen() && nTmpWidth > rInf.GetKern() )
//STRIP001                 nTmpWidth -= rInf.GetKern();
//STRIP001             rInf.GetOut().DrawStretchText( aPos, nTmpWidth,
//STRIP001                                            rInf.GetText(), rInf.GetIdx(), rInf.GetLen() );
//STRIP001         }
//STRIP001         else if( rInf.GetKern() )
//STRIP001         {
//STRIP001             long nTmpWidth = GetTextSize( rInf ).Width();
//STRIP001
//STRIP001             Color aOldColor( pTmpFont->GetColor() );
//STRIP001             sal_Bool bChgColor = rInf.ApplyAutoColor( pTmpFont );
//STRIP001
//STRIP001             if( bChgColor )
//STRIP001             {
//STRIP001                 if( !pTmpFont->IsSameInstance( rInf.GetOut().GetFont() ) )
//STRIP001                     rInf.GetOut().SetFont( *pTmpFont );
//STRIP001                 pTmpFont->SetColor( aOldColor );
//STRIP001             }
//STRIP001
//STRIP001             rInf.GetOut().DrawStretchText( aPos, (USHORT)nTmpWidth,
//STRIP001                                            rInf.GetText(), rInf.GetIdx(), rInf.GetLen() );
//STRIP001         }
//STRIP001         else
//STRIP001             rInf.GetOut().DrawText( aPos, rInf.GetText(),
//STRIP001                                     rInf.GetIdx(), rInf.GetLen() );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         const String* pStr = &rInf.GetText();
//STRIP001         String aStr( aEmptyStr );
//STRIP001         BOOL bBullet = rInf.GetBullet();
//STRIP001         if( bSymbol )
//STRIP001             bBullet = FALSE;
//STRIP001         long *pKernArray = new long[ rInf.GetLen() ];
//STRIP001         CreateScrFont( rInf.GetShell(), *rInf.GetpOut() );
//STRIP001         long nScrPos;
//STRIP001
//STRIP001         // get screen array
//STRIP001         long* pScrArray = new long[ rInf.GetLen() ];
//STRIP001         rInf.GetOut().GetTextArray( rInf.GetText(), pScrArray,
//STRIP001                                     rInf.GetIdx(), rInf.GetLen() );
//STRIP001
//STRIP001 // OLE: no printer available
//STRIP001 //        ASSERT( pPrinter, "DrawText needs pPrinter" )
//STRIP001         if ( pPrinter )
//STRIP001         {
//STRIP001             // pTmpFont has already been set as current font for rInf.GetOut()
//STRIP001             if ( pPrinter != rInf.GetpOut() || pTmpFont != pPrtFont )
//STRIP001             {
//STRIP001                 if( !pPrtFont->IsSameInstance( pPrinter->GetFont() ) )
//STRIP001                     pPrinter->SetFont( *pPrtFont );
//STRIP001             }
//STRIP001             pPrinter->GetTextArray( rInf.GetText(), pKernArray, rInf.GetIdx(),
//STRIP001                                     rInf.GetLen() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001 //            BOOL bRestore = FALSE;
//STRIP001 //            MapMode aOld( rInf.GetOut().GetMapMode() );
//STRIP001 //                if( rInf.GetZoom().GetNumerator() &&
//STRIP001 //                        rInf.GetZoom() != aOld.GetScaleX() )
//STRIP001 //                {
//STRIP001 //                        MapMode aNew( aOld );
//STRIP001 //                        aNew.SetScaleX( rInf.GetZoom() );
//STRIP001 //                        aNew.SetScaleY( rInf.GetZoom() );
//STRIP001 //                        rInf.GetOut().SetMapMode( aNew );
//STRIP001 //                        bRestore = TRUE;
//STRIP001 //                }
//STRIP001             rInf.GetOut().GetTextArray( rInf.GetText(), pKernArray,
//STRIP001                                         rInf.GetIdx(), rInf.GetLen() );
//STRIP001 //            if( bRestore )
//STRIP001 //                rInf.GetOut().SetMapMode( aOld );
//STRIP001         }
//STRIP001
//STRIP001         //
//STRIP001         // Modify Printer and ScreenArrays for special justifications
//STRIP001         //
//STRIP001         short nSpaceAdd = rInf.GetSpace();
//STRIP001
//STRIP001         if ( rInf.GetFont() && rInf.GetLen() )
//STRIP001         {
//STRIP001             const BYTE nActual = rInf.GetFont()->GetActual();
//STRIP001             const SwScriptInfo* pSI = rInf.GetScriptInfo();
//STRIP001
//STRIP001             // Kana Compression
//STRIP001             if ( SW_CJK == nActual && rInf.GetKanaComp() &&
//STRIP001                  pSI && pSI->CountCompChg() &&
//STRIP001                  lcl_IsMonoSpaceFont( rInf.GetpOut() ) )
//STRIP001             {
//STRIP001                 Point aTmpPos( aPos );
//STRIP001                 pSI->Compress( pScrArray, rInf.GetIdx(), rInf.GetLen(),
//STRIP001                                rInf.GetKanaComp(),
//STRIP001                                (USHORT)aFont.GetSize().Height(), &aTmpPos );
//STRIP001                 pSI->Compress( pKernArray, rInf.GetIdx(), rInf.GetLen(),
//STRIP001                                rInf.GetKanaComp(),
//STRIP001                                (USHORT)aFont.GetSize().Height(), &aPos );
//STRIP001             }
//STRIP001
//STRIP001             // Asian Justification
//STRIP001             if ( SW_CJK == nActual && nSpaceAdd )
//STRIP001             {
//STRIP001                 LanguageType aLang = rInf.GetFont()->GetLanguage( SW_CJK );
//STRIP001
//STRIP001                 if ( LANGUAGE_KOREAN != aLang && LANGUAGE_KOREAN_JOHAB != aLang )
//STRIP001                 {
//STRIP001                     long nSpaceSum = nSpaceAdd;
//STRIP001                     for ( USHORT nI = 0; nI < rInf.GetLen(); ++nI )
//STRIP001                     {
//STRIP001                         pKernArray[ nI ] += nSpaceSum;
//STRIP001                         pScrArray[ nI ] += nSpaceSum;
//STRIP001                         nSpaceSum += nSpaceAdd;
//STRIP001                     }
//STRIP001
//STRIP001                     nSpaceAdd = 0;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             // Thai Justification
//STRIP001             if ( SW_CTL == nActual && nSpaceAdd )
//STRIP001             {
//STRIP001                 LanguageType aLang = rInf.GetFont()->GetLanguage( SW_CTL );
//STRIP001
//STRIP001                 if ( LANGUAGE_THAI == aLang )
//STRIP001                 {
//STRIP001                     SwScriptInfo::ThaiJustify( rInf.GetText(), pKernArray,
//STRIP001                                                pScrArray, rInf.GetIdx(),
//STRIP001                                                rInf.GetLen(), nSpaceAdd );
//STRIP001
//STRIP001                     // adding space to blanks is already done
//STRIP001                     nSpaceAdd = 0;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001             // Kashida Justification
//STRIP001             if ( SW_CTL == nActual && nSpaceAdd )
//STRIP001             {
//STRIP001                 if ( SwScriptInfo::IsArabicLanguage( rInf.GetFont()->
//STRIP001                                                         GetLanguage( SW_CTL ) ) )
//STRIP001                 {
//STRIP001                     if ( pSI && pSI->CountKashida() )
//STRIP001                         pSI->KashidaJustify( pKernArray, pScrArray, rInf.GetIdx(),
//STRIP001                                              rInf.GetLen(), nSpaceAdd );
//STRIP001                     nSpaceAdd = 0;
//STRIP001                 }
//STRIP001             }
//STRIP001 #endif
//STRIP001         }
//STRIP001
//STRIP001         nScrPos = pScrArray[ 0 ];
//STRIP001
//STRIP001         if( bBullet )
//STRIP001         {
//STRIP001 #ifdef BIDI
//STRIP001             // !!! HACK !!!
//STRIP001             // The Arabic layout engine requires some context of the string
//STRIP001             // which should be painted.
//STRIP001             xub_StrLen nCopyStart = rInf.GetIdx();
//STRIP001             if ( nCopyStart )
//STRIP001                 --nCopyStart;
//STRIP001
//STRIP001             xub_StrLen nCopyLen = rInf.GetLen();
//STRIP001             if ( nCopyStart + nCopyLen < rInf.GetText().Len() )
//STRIP001                 ++nCopyLen;
//STRIP001
//STRIP001             aStr = rInf.GetText().Copy( nCopyStart, nCopyLen );
//STRIP001             pStr = &aStr;
//STRIP001
//STRIP001             xub_Unicode cBulletChar = CH_BULLET;
//STRIP001
//STRIP001             for( xub_StrLen i = 0; i < aStr.Len(); ++i )
//STRIP001                 if( CH_BLANK == aStr.GetChar( i ) )
//STRIP001                     aStr.SetChar( i, cBulletChar );
//STRIP001 #else
//STRIP001             aStr = rInf.GetText().Copy( rInf.GetIdx(), rInf.GetLen() );
//STRIP001             pStr = &aStr;
//STRIP001             for( xub_StrLen i = 0; i < aStr.Len(); ++i )
//STRIP001                 if( CH_BLANK == aStr.GetChar( i ) )
//STRIP001                     aStr.SetChar( i, CH_BULLET );
//STRIP001 #endif
//STRIP001
//STRIP001         }
//STRIP001
//STRIP001      xub_StrLen nCnt = rInf.GetText().Len();
//STRIP001      if ( nCnt < rInf.GetIdx() )
//STRIP001          nCnt = 0;
//STRIP001      else
//STRIP001          nCnt -= rInf.GetIdx();
//STRIP001      nCnt = Min( nCnt, rInf.GetLen() );
//STRIP001      long nKernSum = rInf.GetKern();
//STRIP001      xub_Unicode cChPrev = rInf.GetText().GetChar( rInf.GetIdx() );
//STRIP001
//STRIP001      // Wenn es sich um ein singulaeres, unterstrichenes Space
//STRIP001      // im Blocksatz handelt, muessen wir zwei ausgeben:
//STRIP001      if ( ( nCnt == 1 ) && rInf.GetSpace() && ( cChPrev == CH_BLANK ) )
//STRIP001      {
//STRIP001          pKernArray[0] = rInf.GetWidth() + rInf.GetSpace() + rInf.GetKern();
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001             if ( bSwitchL2R )
//STRIP001                 rInf.GetFrm()->SwitchLTRtoRTL( aPos );
//STRIP001 #endif
//STRIP001
//STRIP001             if ( bSwitchH2V )
//STRIP001                 rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001
//STRIP001             rInf.GetOut().DrawTextArray( aPos, rInf.GetText(),
//STRIP001                                          pKernArray, rInf.GetIdx(), 1 );
//STRIP001          if( bBullet )
//STRIP001              rInf.GetOut().DrawTextArray( aPos, *pStr, pKernArray,
//STRIP001                                              rInf.GetIdx() ? 1 : 0, 1 );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             xub_Unicode nCh;
//STRIP001
//STRIP001             // Bei Pairkerning waechst der Printereinfluss auf die Positionierung
//STRIP001             USHORT nMul = 3;
//STRIP001
//STRIP001             if ( pPrtFont->GetKerning() )
//STRIP001                 nMul = 1;
//STRIP001
//STRIP001             const USHORT nDiv = nMul+1;
//STRIP001
//STRIP001             // In nSpaceSum wird der durch Blocksatz auf die Spaces verteilte
//STRIP001             // Zwischenraum aufsummiert.
//STRIP001             // Die Spaces selbst werden im Normalfall in der Mitte des
//STRIP001             // Zwischenraums positioniert, deshalb die nSpace/2-Mimik.
//STRIP001             // Bei wortweiser Unterstreichung muessen sie am Anfang des
//STRIP001             // Zwischenraums stehen, damit dieser nicht unterstrichen wird.
//STRIP001             // Ein Space am Anfang oder am Ende des Textes muss allerdings
//STRIP001             // vor bzw. hinter den kompletten Zwischenraum gesetzt werden,
//STRIP001             // sonst wuerde das Durch-/Unterstreichen Luecken aufweisen.
//STRIP001             long nSpaceSum = 0;
//STRIP001             USHORT nHalfSpace = pPrtFont->IsWordLineMode() ? 0 : nSpaceAdd / 2;
//STRIP001             USHORT nOtherHalf = nSpaceAdd - nHalfSpace;
//STRIP001             if ( nSpaceAdd && ( cChPrev == CH_BLANK ) )
//STRIP001                 nSpaceSum = nHalfSpace;
//STRIP001             for ( xub_StrLen i=1; i<nCnt; ++i,nKernSum += rInf.GetKern() )
//STRIP001             {
//STRIP001                 nCh = rInf.GetText().GetChar( rInf.GetIdx() + i );
//STRIP001
//STRIP001                 ASSERT( pScrArray, "Where is the screen array?" )
//STRIP001                 long nScr;
//STRIP001                 nScr = pScrArray[ i ] - pScrArray[ i - 1 ];
//STRIP001
//STRIP001                 // Wenn vor uns ein (Ex-)SPACE ist, positionieren wir uns optimal,
//STRIP001                 // d.h. unseren rechten Rand auf die 100% Druckerposition,
//STRIP001                 // sind wir sogar selbst ein Ex-SPACE, so positionieren wir uns
//STRIP001                 // linksbuendig zur Druckerposition.
//STRIP001                 if ( nCh == CH_BLANK )
//STRIP001                 {
//STRIP001 #ifdef FONT_TEST_DEBUG
//STRIP001                     lcl_Pos( 3, nScrPos, nScr, pKernArray[i-1], pKernArray[i] );
//STRIP001 #else
//STRIP001                     nScrPos = pKernArray[i-1] + nScr;
//STRIP001 #endif
//STRIP001                     if ( cChPrev == CH_BLANK )
//STRIP001                         nSpaceSum += nOtherHalf;
//STRIP001                     if ( i + 1 == nCnt )
//STRIP001                         nSpaceSum += nSpaceAdd;
//STRIP001                     else
//STRIP001                         nSpaceSum += nHalfSpace;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if ( cChPrev == CH_BLANK )
//STRIP001                     {
//STRIP001 #ifdef FONT_TEST_DEBUG
//STRIP001                         lcl_Pos( 6, nScrPos, nScr, pKernArray[i-1], pKernArray[i] );
//STRIP001 #else
//STRIP001                         nScrPos = pKernArray[i-1] + nScr;
//STRIP001 #endif
//STRIP001                         // kein Pixel geht verloren:
//STRIP001                         nSpaceSum += nOtherHalf;
//STRIP001                     }
//STRIP001                     else if ( cChPrev == '-' )
//STRIP001 #ifdef FONT_TEST_DEBUG
//STRIP001                         lcl_Pos( 6, nScrPos, nScr, pKernArray[i-1], pKernArray[i] );
//STRIP001 #else
//STRIP001                         nScrPos = pKernArray[i-1] + nScr;
//STRIP001 #endif
//STRIP001                     else
//STRIP001                     {
//STRIP001 #ifdef FONT_TEST_DEBUG
//STRIP001                         lcl_Pos( 0, nScrPos, nScr, pKernArray[i-1], pKernArray[i] );
//STRIP001 #else
//STRIP001                         nScrPos += nScr;
//STRIP001                         nScrPos = ( nMul * nScrPos + pKernArray[i] ) / nDiv;
//STRIP001 #endif
//STRIP001                     }
//STRIP001                 }
//STRIP001                 cChPrev = nCh;
//STRIP001                 pKernArray[i-1] = nScrPos - nScr + nKernSum + nSpaceSum;
//STRIP001             }
//STRIP001
//STRIP001             // the layout engine requires the total width of the output
//STRIP001             pKernArray[ rInf.GetLen() - 1 ] += nKernSum + nSpaceSum;
//STRIP001
//STRIP001             if( rInf.GetGreyWave() )
//STRIP001             {
//STRIP001                 if( rInf.GetLen() )
//STRIP001                 {
//STRIP001                     long nHght = rInf.GetOut().LogicToPixel(
//STRIP001                                     pPrtFont->GetSize() ).Height();
//STRIP001                     if( WRONG_SHOW_MIN < nHght )
//STRIP001                     {
//STRIP001                         if ( rInf.GetOut().GetConnectMetaFile() )
//STRIP001                             rInf.GetOut().Push();
//STRIP001
//STRIP001                         USHORT nWave =
//STRIP001                             WRONG_SHOW_MEDIUM < nHght ? WAVE_NORMAL :
//STRIP001                             ( WRONG_SHOW_SMALL < nHght ? WAVE_SMALL :
//STRIP001                             WAVE_FLAT );
//STRIP001                         Color aCol( rInf.GetOut().GetLineColor() );
//STRIP001                         BOOL bColSave = aCol != *pWaveCol;
//STRIP001                         if ( bColSave )
//STRIP001                             rInf.GetOut().SetLineColor( *pWaveCol );
//STRIP001
//STRIP001                         Point aEnd;
//STRIP001                         long nKernVal = pKernArray[ USHORT( rInf.GetLen() - 1 ) ];
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001                         USHORT nDir = bBidiPor ?
//STRIP001                                         1800 :
//STRIP001                                         UnMapDirection(
//STRIP001                                             GetFont()->GetOrientation(),
//STRIP001                                             bSwitchH2V );
//STRIP001 #else
//STRIP001                         USHORT nDir =  UnMapDirection(
//STRIP001                                             GetFont()->GetOrientation(),
//STRIP001                                             bSwitchH2V );
//STRIP001 #endif
//STRIP001                         switch ( nDir )
//STRIP001                         {
//STRIP001                         case 0 :
//STRIP001                             aEnd.X() = rInf.GetPos().X() + nKernVal;
//STRIP001                             aEnd.Y() = rInf.GetPos().Y();
//STRIP001                             break;
//STRIP001                         case 900 :
//STRIP001                             aEnd.X() = rInf.GetPos().X();
//STRIP001                             aEnd.Y() = rInf.GetPos().Y() - nKernVal;
//STRIP001                             break;
//STRIP001                         case 1800 :
//STRIP001                             aEnd.X() = rInf.GetPos().X() - nKernVal;
//STRIP001                             aEnd.Y() = rInf.GetPos().Y();
//STRIP001                             break;
//STRIP001                         case 2700 :
//STRIP001                             aEnd.X() = rInf.GetPos().X();
//STRIP001                             aEnd.Y() = rInf.GetPos().Y() + nKernVal;
//STRIP001                             break;
//STRIP001                         }
//STRIP001
//STRIP001                         Point aPos( rInf.GetPos() );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001                         if ( bSwitchL2R )
//STRIP001                         {
//STRIP001                             rInf.GetFrm()->SwitchLTRtoRTL( aPos );
//STRIP001                             rInf.GetFrm()->SwitchLTRtoRTL( aEnd );
//STRIP001                         }
//STRIP001 #endif
//STRIP001
//STRIP001                         if ( bSwitchH2V )
//STRIP001                         {
//STRIP001                             rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001                             rInf.GetFrm()->SwitchHorizontalToVertical( aEnd );
//STRIP001                         }
//STRIP001                         rInf.GetOut().DrawWaveLine( aPos, aEnd, nWave );
//STRIP001
//STRIP001                         if ( bColSave )
//STRIP001                             rInf.GetOut().SetLineColor( aCol );
//STRIP001
//STRIP001                         if ( rInf.GetOut().GetConnectMetaFile() )
//STRIP001                             rInf.GetOut().Pop();
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             else if( rInf.GetWrong() && !bSymbol )
//STRIP001             {
//STRIP001                 if( rInf.GetLen() )
//STRIP001                 {
//STRIP001                     xub_StrLen nStart = rInf.GetIdx();
//STRIP001                     xub_StrLen nWrLen = rInf.GetLen();
//STRIP001                     if( rInf.GetWrong()->Check( nStart, nWrLen ) )
//STRIP001                     {
//STRIP001                         long nHght = rInf.GetOut().LogicToPixel(
//STRIP001                                          pPrtFont->GetSize() ).Height();
//STRIP001                         if( WRONG_SHOW_MIN < nHght )
//STRIP001                         {
//STRIP001                             if ( rInf.GetOut().GetConnectMetaFile() )
//STRIP001                                     rInf.GetOut().Push();
//STRIP001
//STRIP001                             USHORT nWave =
//STRIP001                                     WRONG_SHOW_MEDIUM < nHght ? WAVE_NORMAL :
//STRIP001                                     ( WRONG_SHOW_SMALL < nHght ? WAVE_SMALL :
//STRIP001                                     WAVE_FLAT );
//STRIP001
//STRIP001                             Color aCol( rInf.GetOut().GetLineColor() );
//STRIP001                             BOOL bColSave = aCol != SwViewOption::GetSpellColor();
//STRIP001                             if ( bColSave )
//STRIP001                                 rInf.GetOut().SetLineColor( SwViewOption::GetSpellColor() );
//STRIP001
//STRIP001                             do
//STRIP001                             {
//STRIP001                                 nStart -= rInf.GetIdx();
//STRIP001                                 Point aStart( rInf.GetPos() );
//STRIP001                                 Point aEnd;
//STRIP001                                 short nBlank = 0;
//STRIP001                                 const xub_StrLen nEnd = nStart + nWrLen;
//STRIP001
//STRIP001                                 if( nEnd < nCnt
//STRIP001                                     && CH_BLANK == rInf.GetText().GetChar( rInf.GetIdx() + nEnd ) )
//STRIP001                                 {
//STRIP001                                     if( nEnd + 1 == nCnt )
//STRIP001                                         nBlank -= rInf.GetSpace();
//STRIP001                                     else
//STRIP001                                         nBlank -= nHalfSpace;
//STRIP001                                 }
//STRIP001
//STRIP001                                 // determine start, end and length of wave line
//STRIP001                                 long nKernStart = nStart ?
//STRIP001                                                   pKernArray[ USHORT( nStart - 1 ) ] :
//STRIP001                                                   0;
//STRIP001                                 long nKernEnd = pKernArray[ USHORT( nEnd - 1 ) ];
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001                                 USHORT nDir = bBidiPor ?
//STRIP001                                               1800 :
//STRIP001                                               UnMapDirection(
//STRIP001                                                 GetFont()->GetOrientation(),
//STRIP001                                                 bSwitchH2V );
//STRIP001 #else
//STRIP001                                 USHORT nDir = UnMapDirection(
//STRIP001                                                 GetFont()->GetOrientation(),
//STRIP001                                                 bSwitchH2V );
//STRIP001 #endif
//STRIP001
//STRIP001                                 switch ( nDir )
//STRIP001                                 {
//STRIP001                                 case 0 :
//STRIP001                                     aStart.X() += nKernStart;
//STRIP001                                     aEnd.X() = nBlank + rInf.GetPos().X() + nKernEnd;
//STRIP001                                     aEnd.Y() = rInf.GetPos().Y();
//STRIP001                                     break;
//STRIP001                                 case 900 :
//STRIP001                                     aStart.Y() -= nKernStart;
//STRIP001                                     aEnd.X() = rInf.GetPos().X();
//STRIP001                                     aEnd.Y() = nBlank + rInf.GetPos().Y() - nKernEnd;
//STRIP001                                     break;
//STRIP001                                 case 1800 :
//STRIP001                                     aStart.X() -= nKernStart;
//STRIP001                                     aEnd.X() = rInf.GetPos().X() - nKernEnd - nBlank;
//STRIP001                                     aEnd.Y() = rInf.GetPos().Y();
//STRIP001                                     break;
//STRIP001                                 case 2700 :
//STRIP001                                     aStart.Y() += nKernStart;
//STRIP001                                     aEnd.X() = rInf.GetPos().X();
//STRIP001                                     aEnd.Y() = nBlank + rInf.GetPos().Y() + nKernEnd;
//STRIP001                                     break;
//STRIP001                                 }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001                                 if ( bSwitchL2R )
//STRIP001                                 {
//STRIP001                                     rInf.GetFrm()->SwitchLTRtoRTL( aStart );
//STRIP001                                     rInf.GetFrm()->SwitchLTRtoRTL( aEnd );
//STRIP001                                 }
//STRIP001 #endif
//STRIP001
//STRIP001                                 if ( bSwitchH2V )
//STRIP001                                 {
//STRIP001                                     rInf.GetFrm()->SwitchHorizontalToVertical( aStart );
//STRIP001                                     rInf.GetFrm()->SwitchHorizontalToVertical( aEnd );
//STRIP001                                 }
//STRIP001                                 rInf.GetOut().DrawWaveLine( aStart, aEnd, nWave );
//STRIP001                                 nStart = nEnd + rInf.GetIdx();
//STRIP001                                 nWrLen = rInf.GetIdx() + rInf.GetLen() - nStart;
//STRIP001                             }
//STRIP001                             while( nWrLen && rInf.GetWrong()->Check( nStart, nWrLen ) );
//STRIP001                             if ( bColSave )
//STRIP001                                 rInf.GetOut().SetLineColor( aCol );
//STRIP001
//STRIP001                             if ( rInf.GetOut().GetConnectMetaFile() )
//STRIP001                                 rInf.GetOut().Pop();
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             xub_StrLen nOffs = 0;
//STRIP001             xub_StrLen nLen = rInf.GetLen();
//STRIP001 #ifdef COMING_SOON
//STRIP001             if( aPos.X() < rInf.GetLeft() )
//STRIP001             {
//STRIP001                 while( nOffs < nLen &&
//STRIP001                     aPos.X() + pKernArray[ nOffs ] < rInf.GetLeft() )
//STRIP001                     ++nOffs;
//STRIP001                 if( nOffs < nLen )
//STRIP001                 {
//STRIP001                     --nLen;
//STRIP001                     while( nLen > nOffs &&
//STRIP001                         aPos.X() + pKernArray[ nLen ] > rInf.GetRight() )
//STRIP001                         --nLen;
//STRIP001                     ++nLen;
//STRIP001                     if( nOffs )
//STRIP001                         --nOffs;
//STRIP001                 }
//STRIP001                 if( nOffs )
//STRIP001                 {
//STRIP001                     long nDiff = pKernArray[ nOffs - 1 ];
//STRIP001                     aPos.X() += nDiff;
//STRIP001                     for( xub_StrLen nX = nOffs; nX < nLen; ++nX )
//STRIP001                         pKernArray[ nX ] -= nDiff;
//STRIP001                 }
//STRIP001             }
//STRIP001 #endif
//STRIP001             if( nOffs < nLen )
//STRIP001             {
//STRIP001 #ifdef BIDI
//STRIP001                 // If we paint bullets instead of spaces, we use a copy of
//STRIP001                 // the paragraph string. For the layout engine, the copy
//STRIP001                 // of the string has to be an environment of the range which
//STRIP001                 // is painted
//STRIP001                 register xub_StrLen nTmpIdx = bBullet ?
//STRIP001                                               ( rInf.GetIdx() ? 1 : 0 ) :
//STRIP001                                               rInf.GetIdx();
//STRIP001
//STRIP001                 if ( bSwitchL2R )
//STRIP001                     rInf.GetFrm()->SwitchLTRtoRTL( aPos );
//STRIP001 #else
//STRIP001                 register xub_StrLen nTmpIdx = bBullet ? 0 : rInf.GetIdx();
//STRIP001 #endif
//STRIP001
//STRIP001                 if ( bSwitchH2V )
//STRIP001                     rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001
//STRIP001                 rInf.GetOut().DrawTextArray( aPos, *pStr, pKernArray + nOffs,
//STRIP001                                              nTmpIdx + nOffs , nLen - nOffs );
//STRIP001             }
//STRIP001         }
//STRIP001         delete[] pScrArray;
//STRIP001         delete[] pKernArray;
//STRIP001     }
//STRIP001 }


// Optimierung war fuer DrawText() ausgeschaltet
#if defined( WNT ) && defined( MSC )    // && defined( W40 )
#pragma optimize("",on)
#endif


/*************************************************************************
 *
 *  Size SwFntObj::GetTextSize( const OutputDevice *pOut, const String &rTxt,
 *           const USHORT nIdx, const USHORT nLen, const short nKern = 0 );
 *
 *  Ersterstellung      AMA 16. Dez. 94
 *  Letzte Aenderung    AMA 16. Dez. 94
 *
 *  Beschreibung: ermittelt die TextSize (des Druckers)
 *
 *************************************************************************/

/*N*/ Size SwFntObj::GetTextSize( SwDrawTextInfo& rInf )
/*N*/ {
/*N*/   Size aTxtSize;
/*N*/   const xub_StrLen nLn = ( STRING_LEN != rInf.GetLen() ) ? rInf.GetLen() :
/*N*/                          rInf.GetText().Len();
/*N*/
/*N*/     // be sure to have the correct layout mode at the printer
/*N*/     if ( pPrinter )
/*N*/     {
/*N*/         pPrinter->SetLayoutMode( rInf.GetpOut()->GetLayoutMode() );
/*N*/         pPrinter->SetDigitLanguage( rInf.GetpOut()->GetDigitLanguage() );
/*N*/     }
/*N*/
/*N*/     if ( rInf.GetFrm() && nLn && rInf.SnapToGrid() && rInf.GetFont() &&
/*N*/          SW_CJK == rInf.GetFont()->GetActual() )
/*N*/     {
/*?*/         GETGRID( rInf.GetFrm()->FindPageFrm() )
/*?*/         if ( pGrid && GRID_LINES_CHARS == pGrid->GetGridType() )
/*?*/         {
/*?*/             const USHORT nGridWidth = pGrid->GetBaseHeight();
/*?*/
/*?*/             OutputDevice* pOutDev;
/*?*/
/*?*/             if ( pPrinter )
/*?*/             {
/*?*/                 if( !pPrtFont->IsSameInstance( pPrinter->GetFont() ) )
/*?*/                     pPrinter->SetFont(*pPrtFont);
/*?*/                 pOutDev = pPrinter;
/*?*/             }
/*?*/             else
/*?*/                 pOutDev = rInf.GetpOut();
/*?*/
/*?*/             aTxtSize.Width() =
/*?*/                     pOutDev->GetTextWidth( rInf.GetText(), rInf.GetIdx(), nLn );
/*?*/             aTxtSize.Height() = pOutDev->GetTextHeight() + nLeading;
/*?*/
/*?*/             long nWidthPerChar = aTxtSize.Width() / nLn;
/*?*/
/*?*/             const ULONG i = nWidthPerChar ?
/*?*/                                 ( nWidthPerChar - 1 ) / nGridWidth + 1:
/*?*/                                 1;
/*?*/
/*?*/             aTxtSize.Width() = i * nGridWidth * nLn;
/*?*/
/*?*/             rInf.SetKanaDiff( 0 );
/*?*/             return aTxtSize;
/*?*/         }
/*N*/     }
/*N*/
/*N*/     const BOOL bCompress = rInf.GetKanaComp() && nLn &&
/*N*/                            rInf.GetFont() &&
/*N*/                            SW_CJK == rInf.GetFont()->GetActual() &&
/*N*/                            rInf.GetScriptInfo() &&
/*N*/                            rInf.GetScriptInfo()->CountCompChg() &&
/*N*/                      lcl_IsMonoSpaceFont( rInf.GetpOut() );
/*N*/
/*N*/   ASSERT( !bCompress || ( rInf.GetScriptInfo() && rInf.GetScriptInfo()->
/*N*/           CountCompChg()), "Compression without info" );
/*N*/
/*N*/     // This is the part used e.g., for cursor travelling
/*N*/     // See condition for DrawText or DrawTextArray (bDirectPrint)
/*N*/     if ( pPrinter && pPrinter != rInf.GetpOut() )
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if( !pPrtFont->IsSameInstance( pPrinter->GetFont() ) )
//STRIP001 /*?*/            pPrinter->SetFont(*pPrtFont);
//STRIP001 /*?*/        aTxtSize.Width() = pPrinter->GetTextWidth( rInf.GetText(),
//STRIP001 /*?*/                                                    rInf.GetIdx(), nLn );
//STRIP001 /*?*/        aTxtSize.Height() = pPrinter->GetTextHeight();
//STRIP001 /*?*/        long *pKernArray = new long[nLn];
//STRIP001 /*?*/         CreateScrFont( rInf.GetShell(), *rInf.GetpOut() );
//STRIP001 /*?*/        if( !GetScrFont()->IsSameInstance( rInf.GetpOut()->GetFont() ) )
//STRIP001 /*?*/             rInf.GetpOut()->SetFont( *pScrFont );
//STRIP001 /*?*/        long nScrPos;
//STRIP001 /*?*/
//STRIP001 /*?*/         pPrinter->GetTextArray( rInf.GetText(), pKernArray, rInf.GetIdx(),nLn );
//STRIP001 /*?*/        if( bCompress )
//STRIP001 /*?*/             rInf.SetKanaDiff( rInf.GetScriptInfo()->Compress( pKernArray,
//STRIP001 /*?*/                rInf.GetIdx(), nLn, rInf.GetKanaComp(),
//STRIP001 /*?*/                (USHORT)aFont.GetSize().Height() ) );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            rInf.SetKanaDiff( 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( rInf.GetKanaDiff() )
//STRIP001 /*?*/             nScrPos = pKernArray[ nLn - 1 ];
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             long* pScrArray = new long[ rInf.GetLen() ];
//STRIP001 /*?*/             rInf.GetpOut()->GetTextArray( rInf.GetText(), pScrArray,
//STRIP001 /*?*/                                    rInf.GetIdx(), rInf.GetLen() );
//STRIP001 /*?*/             nScrPos = pScrArray[ 0 ];
//STRIP001 /*?*/             xub_StrLen nCnt = rInf.GetText().Len();
//STRIP001 /*?*/             if ( nCnt < rInf.GetIdx() )
//STRIP001 /*?*/                 nCnt=0;
//STRIP001 /*?*/             else
//STRIP001 /*?*/                 nCnt -= rInf.GetIdx();
//STRIP001 /*?*/             nCnt = Min (nCnt, nLn);
//STRIP001 /*?*/             xub_Unicode nChPrev = rInf.GetText().GetChar( rInf.GetIdx() );
//STRIP001 /*?*/
//STRIP001 /*?*/             xub_Unicode nCh;
//STRIP001 /*?*/
//STRIP001 /*?*/             // Bei Pairkerning waechst der Printereinfluss auf die Positionierung
//STRIP001 /*?*/             USHORT nMul = 3;
//STRIP001 /*?*/             if ( pPrtFont->GetKerning() )
//STRIP001 /*?*/                 nMul = 1;
//STRIP001 /*?*/             const USHORT nDiv = nMul+1;
//STRIP001 /*?*/             for( xub_StrLen i=1; i<nCnt; i++ )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 nCh = rInf.GetText().GetChar( rInf.GetIdx() + i );
//STRIP001 /*?*/                 long nScr;
//STRIP001 /*?*/                 nScr = pScrArray[ i ] - pScrArray[ i - 1 ];
//STRIP001 /*?*/                 if ( nCh == CH_BLANK )
//STRIP001 /*?*/                     nScrPos = pKernArray[i-1]+nScr;
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     if ( nChPrev == CH_BLANK || nChPrev == '-' )
//STRIP001 /*?*/                         nScrPos = pKernArray[i-1]+nScr;
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         nScrPos += nScr;
//STRIP001 /*?*/                         nScrPos = ( nMul * nScrPos + pKernArray[i] ) / nDiv;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 nChPrev = nCh;
//STRIP001 /*?*/                 pKernArray[i-1] = nScrPos - nScr;
//STRIP001 /*?*/             }
//STRIP001 /*?*/             delete[] pScrArray;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         delete[] pKernArray;
//STRIP001 /*?*/        aTxtSize.Width() = nScrPos;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         if( !pPrtFont->IsSameInstance( rInf.GetpOut()->GetFont() ) )
/*N*/             rInf.GetpOut()->SetFont( *pPrtFont );
/*N*/       if( bCompress )
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            long *pKernArray = new long[nLn];
//STRIP001 /*?*/             rInf.GetpOut()->GetTextArray( rInf.GetText(), pKernArray,
//STRIP001 /*?*/                                           rInf.GetIdx(), nLn );
//STRIP001 /*?*/             rInf.SetKanaDiff( rInf.GetScriptInfo()->Compress( pKernArray,
//STRIP001 /*?*/                rInf.GetIdx(), nLn, rInf.GetKanaComp(),
//STRIP001 /*?*/                (USHORT) aFont.GetSize().Height() ) );
//STRIP001 /*?*/            aTxtSize.Width() = pKernArray[ nLn - 1 ];
//STRIP001 /*?*/            delete[] pKernArray;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/             aTxtSize.Width() = rInf.GetpOut()->GetTextWidth( rInf.GetText(),
/*N*/                                                              rInf.GetIdx(), nLn );
/*N*/           rInf.SetKanaDiff( 0 );
/*N*/       }
/*N*/
/*N*/         aTxtSize.Height() = rInf.GetpOut()->GetTextHeight();
/*N*/   }
/*N*/
/*N*/   if ( rInf.GetKern() && nLn )
/*N*/       aTxtSize.Width() += ( nLn - 1 ) * long( rInf.GetKern() );
/*N*/
/*N*/   aTxtSize.Height() += nLeading;
/*N*/   return aTxtSize;
/*N*/ }


//STRIP001 xub_StrLen SwFntObj::GetCrsrOfst( SwDrawTextInfo &rInf )
//STRIP001 {
//STRIP001     short nSpaceAdd = rInf.GetSpace() ? rInf.GetSpace() : - rInf.GetSperren();
//STRIP001     short nKern = rInf.GetKern();
//STRIP001
//STRIP001     if( nSpaceAdd < 0 )
//STRIP001  {
//STRIP001      nKern -= nSpaceAdd;
//STRIP001      nSpaceAdd = 0;
//STRIP001  }
//STRIP001     long *pKernArray = new long[ rInf.GetLen() ];
//STRIP001
//STRIP001     if ( pPrinter )
//STRIP001     {
//STRIP001         pPrinter->SetLayoutMode( rInf.GetpOut()->GetLayoutMode() );
//STRIP001         pPrinter->SetDigitLanguage( rInf.GetpOut()->GetDigitLanguage() );
//STRIP001         pPrinter->GetTextArray( rInf.GetText(), pKernArray,
//STRIP001                                 rInf.GetIdx(), rInf.GetLen() );
//STRIP001     }
//STRIP001  else
//STRIP001         rInf.GetpOut()->GetTextArray( rInf.GetText(), pKernArray,
//STRIP001                             rInf.GetIdx(), rInf.GetLen() );
//STRIP001
//STRIP001     const SwScriptInfo* pSI = rInf.GetScriptInfo();
//STRIP001     if ( rInf.GetFont() && rInf.GetLen() )
//STRIP001     {
//STRIP001         const BYTE nActual = rInf.GetFont()->GetActual();
//STRIP001
//STRIP001         // Kana Compression
//STRIP001         if ( SW_CJK == nActual && rInf.GetKanaComp() &&
//STRIP001              pSI && pSI->CountCompChg() &&
//STRIP001              lcl_IsMonoSpaceFont( rInf.GetpOut() ) )
//STRIP001         {
//STRIP001             pSI->Compress( pKernArray, rInf.GetIdx(), rInf.GetLen(),
//STRIP001                            rInf.GetKanaComp(),
//STRIP001                            (USHORT) aFont.GetSize().Height() );
//STRIP001         }
//STRIP001
//STRIP001         // Asian Justification
//STRIP001         if ( SW_CJK == rInf.GetFont()->GetActual() )
//STRIP001         {
//STRIP001             LanguageType aLang = rInf.GetFont()->GetLanguage( SW_CJK );
//STRIP001
//STRIP001             if ( LANGUAGE_KOREAN != aLang && LANGUAGE_KOREAN_JOHAB != aLang )
//STRIP001             {
//STRIP001                 long nSpaceSum = rInf.GetSpace();
//STRIP001                 for ( USHORT nI = 0; nI < rInf.GetLen(); ++nI )
//STRIP001                 {
//STRIP001                     pKernArray[ nI ] += nSpaceSum;
//STRIP001                     nSpaceSum += rInf.GetSpace();
//STRIP001                 }
//STRIP001
//STRIP001                 nSpaceAdd = 0;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // Thai Justification
//STRIP001         if ( SW_CTL == nActual && nSpaceAdd )
//STRIP001         {
//STRIP001             LanguageType aLang = rInf.GetFont()->GetLanguage( SW_CTL );
//STRIP001
//STRIP001             if ( LANGUAGE_THAI == aLang )
//STRIP001             {
//STRIP001                 SwScriptInfo::ThaiJustify( rInf.GetText(), pKernArray, 0,
//STRIP001                                            rInf.GetIdx(), rInf.GetLen(),
//STRIP001                                            rInf.GetSpace() );
//STRIP001
//STRIP001                 // adding space to blanks is already done
//STRIP001                 nSpaceAdd = 0;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // Kashida Justification
//STRIP001         if ( SW_CTL == nActual && rInf.GetSpace() )
//STRIP001         {
//STRIP001             if ( SwScriptInfo::IsArabicLanguage( rInf.GetFont()->
//STRIP001                                                     GetLanguage( SW_CTL ) ) )
//STRIP001             {
//STRIP001                 if ( pSI && pSI->CountKashida() )
//STRIP001                     pSI->KashidaJustify( pKernArray, 0, rInf.GetIdx(), rInf.GetLen(),
//STRIP001                                          rInf.GetSpace() );
//STRIP001                 nSpaceAdd = 0;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  long nLeft = 0;
//STRIP001  long nRight = 0;
//STRIP001  xub_StrLen nCnt = 0;
//STRIP001  xub_StrLen nSpaceSum = 0;
//STRIP001  long nKernSum = 0;
//STRIP001
//STRIP001     if ( rInf.GetFrm() && rInf.GetLen() && rInf.SnapToGrid() &&
//STRIP001          rInf.GetFont() && SW_CJK == rInf.GetFont()->GetActual() )
//STRIP001     {
//STRIP001         GETGRID( rInf.GetFrm()->FindPageFrm() )
//STRIP001         if ( pGrid && GRID_LINES_CHARS == pGrid->GetGridType() )
//STRIP001         {
//STRIP001             const USHORT nGridWidth = pGrid->GetBaseHeight();
//STRIP001
//STRIP001             long nWidthPerChar = pKernArray[ rInf.GetLen() - 1 ] / rInf.GetLen();
//STRIP001
//STRIP001             ULONG i = nWidthPerChar ?
//STRIP001                         ( nWidthPerChar - 1 ) / nGridWidth + 1:
//STRIP001                         1;
//STRIP001
//STRIP001             nWidthPerChar = i * nGridWidth;
//STRIP001
//STRIP001             nCnt = (USHORT)(rInf.GetOfst() / nWidthPerChar);
//STRIP001             if ( 2 * ( rInf.GetOfst() - nCnt * nWidthPerChar ) > nWidthPerChar )
//STRIP001                 ++nCnt;
//STRIP001
//STRIP001             delete[] pKernArray;
//STRIP001             return nCnt;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     sal_uInt16 nItrMode = ::com::sun::star::i18n::CharacterIteratorMode::SKIPCELL;
//STRIP001     sal_Int32 nDone = 0;
//STRIP001     LanguageType aLang;
//STRIP001     sal_Bool bSkipCell = sal_False;
//STRIP001     xub_StrLen nIdx = rInf.GetIdx();
//STRIP001     xub_StrLen nLastIdx = nIdx;
//STRIP001     const xub_StrLen nEnd = rInf.GetIdx() + rInf.GetLen();
//STRIP001
//STRIP001     // skip character cells for complex scripts
//STRIP001     if ( rInf.GetFont() && SW_CTL == rInf.GetFont()->GetActual() &&
//STRIP001          pBreakIt->xBreak.is() )
//STRIP001     {
//STRIP001         aLang = rInf.GetFont()->GetLanguage();
//STRIP001         bSkipCell = sal_True;
//STRIP001     }
//STRIP001
//STRIP001     while ( ( nRight < long( rInf.GetOfst() ) ) && ( nIdx < nEnd ) )
//STRIP001  {
//STRIP001         if ( nSpaceAdd &&
//STRIP001              CH_BLANK == rInf.GetText().GetChar( nIdx ) )
//STRIP001             nSpaceSum += nSpaceAdd;
//STRIP001
//STRIP001         // go to next character (cell).
//STRIP001         nLastIdx = nIdx;
//STRIP001
//STRIP001         if ( bSkipCell )
//STRIP001         {
//STRIP001             nIdx = (xub_StrLen)pBreakIt->xBreak->nextCharacters( rInf.GetText(),
//STRIP001                         nIdx, pBreakIt->GetLocale( aLang ), nItrMode, 1, nDone );
//STRIP001             if ( nIdx <= nLastIdx )
//STRIP001                 break;
//STRIP001         }
//STRIP001         else
//STRIP001             ++nIdx;
//STRIP001
//STRIP001      nLeft = nRight;
//STRIP001         nRight = pKernArray[ nIdx - rInf.GetIdx() - 1 ] + nKernSum + nSpaceSum;
//STRIP001
//STRIP001         nKernSum += nKern;
//STRIP001  }
//STRIP001
//STRIP001     // step back if position is before the middle of the character
//STRIP001     // or if we do not want to go to the next character
//STRIP001     if ( nIdx > rInf.GetIdx() &&
//STRIP001          ( rInf.IsPosMatchesBounds() ||
//STRIP001            ( ( nRight > long( rInf.GetOfst() ) ) &&
//STRIP001              ( nRight - rInf.GetOfst() > rInf.GetOfst() - nLeft ) ) ) )
//STRIP001         nCnt = nLastIdx - rInf.GetIdx(); // first half
//STRIP001     else
//STRIP001         nCnt = nIdx - rInf.GetIdx(); // second half
//STRIP001
//STRIP001     if ( pSI )
//STRIP001         rInf.SetCursorBidiLevel( pSI->DirType( nLastIdx ) );
//STRIP001
//STRIP001  delete[] pKernArray;
//STRIP001  return nCnt;
//STRIP001 }


/*************************************************************************
|*
|*  SwFntAccess::SwFntAccess()
|*
|*  Ersterstellung      AMA 9. Nov. 94
|*  Letzte Aenderung    AMA 9. Nov. 94
|*
|*************************************************************************/

/*N*/ SwFntAccess::SwFntAccess( const void* &rMagic,
/*N*/               USHORT &rIndex, const void *pOwner, ViewShell *pSh,
/*N*/               BOOL bCheck ) :
/*N*/   SwCacheAccess( *pFntCache, rMagic, rIndex ),
/*N*/   pShell( pSh )
/*N*/ {
/*N*/   // Der benutzte CTor von SwCacheAccess sucht anhand rMagic+rIndex im Cache
/*N*/   if ( IsAvail() )
/*N*/   {
/*N*/       // Der schnellste Fall: ein bekannter Font ( rMagic ),
/*N*/       // bei dem Drucker und Zoom nicht ueberprueft werden brauchen.
/*N*/       if ( !bCheck )
/*N*/           return;
/*N*/
/*N*/       // Hier ist zwar der Font bekannt, muss aber noch ueberprueft werden.
/*N*/
/*N*/   }
/*N*/   else
/*N*/       // Hier ist der Font nicht bekannt, muss also gesucht werden.
/*N*/       bCheck = FALSE;
/*N*/
/*N*/
/*N*/     {
/*N*/         OutputDevice* pOut = 0;
/*N*/       USHORT nZoom = USHRT_MAX;
/*N*/
/*N*/         // Get the reference device
/*N*/         if ( pSh )
/*N*/         {
/*N*/             pOut = &pSh->GetRefDev();
/*N*/             nZoom = pSh->GetViewOptions()->GetZoom();
/*N*/         }
/*N*/
/*N*/       SwFntObj *pFntObj;
/*N*/       if ( bCheck )
/*N*/       {
/*N*/             pFntObj = Get();
/*N*/           if ( ( pFntObj->GetZoom( ) == nZoom ) &&
/*N*/                ( pFntObj->pPrinter == pOut ) &&
/*N*/                  pFntObj->GetPropWidth() ==
/*N*/                       ((SwSubFont*)pOwner)->GetPropWidth() )
/*N*/               return; // Die Ueberpruefung ergab: Drucker+Zoom okay.
/*N*/           pFntObj->Unlock( ); // Vergiss dies Objekt, es wurde leider
/*N*/           pObj = NULL;        // eine Drucker/Zoomaenderung festgestellt.
/*N*/       }
/*N*/
/*N*/         // Search by font comparison, quite expensive!
/*N*/         // Look for same font and same printer
/*N*/         pFntObj = pFntCache->First();
/*N*/       while ( pFntObj && !( pFntObj->aFont == *(Font *)pOwner &&
/*N*/                               pFntObj->GetZoom() == nZoom &&
/*N*/                               pFntObj->GetPropWidth() ==
/*N*/                               ((SwSubFont*)pOwner)->GetPropWidth() &&
/*N*/                               ( !pFntObj->pPrinter || pFntObj->pPrinter == pOut ) ) )
/*N*/           pFntObj = pFntCache->Next( pFntObj );
/*N*/
/*N*/       if( pFntObj && pFntObj->pPrinter != pOut )
/*N*/       {
/*N*/           // Wir haben zwar einen ohne Drucker gefunden, mal sehen, ob es
/*N*/           // auch noch einen mit identischem Drucker gibt.
/*N*/           SwFntObj *pTmpObj = pFntObj;
/*N*/           while( pTmpObj && !( pTmpObj->aFont == *(Font *)pOwner &&
/*N*/                  pTmpObj->GetZoom()==nZoom && pTmpObj->pPrinter==pOut &&
/*N*/                  pTmpObj->GetPropWidth() ==
/*N*/                       ((SwSubFont*)pOwner)->GetPropWidth() ) )
/*N*/               pTmpObj = pFntCache->Next( pTmpObj );
/*N*/           if( pTmpObj )
/*N*/               pFntObj = pTmpObj;
/*N*/       }
/*N*/
/*N*/         if ( !pFntObj ) // Font has not been found, create one
/*N*/       {
/*N*/           // Das Objekt muss neu angelegt werden, deshalb muss der Owner ein
/*N*/           // SwFont sein, spaeter wird als Owner die "MagicNumber" gehalten.
/*N*/           SwCacheAccess::pOwner = pOwner;
/*N*/           pFntObj = Get(); // hier wird via NewObj() angelegt und gelockt.
/*N*/           ASSERT(pFntObj, "No Font, no Fun.");
/*N*/       }
/*N*/         else  // Font has been found, so we lock it.
/*N*/       {
/*N*/           pFntObj->Lock();
/*N*/           if( pFntObj->pPrinter != pOut ) // Falls bis dato kein Drucker bekannt
/*N*/           {
/*N*/               ASSERT( !pFntObj->pPrinter, "SwFntAccess: Printer Changed" );
/*N*/                 pFntObj->CreatePrtFont( *pOut );
/*N*/               pFntObj->pPrinter = pOut;
/*N*/               pFntObj->pScrFont = NULL;
/*N*/               pFntObj->nLeading = USHRT_MAX;
/*N*/               pFntObj->nPrtAscent = USHRT_MAX;
/*N*/               pFntObj->nPrtHeight = USHRT_MAX;
/*N*/           }
/*N*/           pObj = pFntObj;
/*N*/       }
/*N*/
/*N*/       // egal, ob neu oder gefunden, ab jetzt ist der Owner vom Objekt eine
/*N*/       // MagicNumber und wird auch dem aufrufenden SwFont bekanntgegeben,
/*N*/       // ebenso der Index fuer spaetere direkte Zugriffe
/*N*/       rMagic = pFntObj->GetOwner();
/*N*/       SwCacheAccess::pOwner = rMagic;
/*N*/       rIndex = pFntObj->GetCachePos();
/*N*/   }
/*N*/ }

/*N*/ SwCacheObj *SwFntAccess::NewObj( )
/*N*/ {
/*N*/   // Ein neuer Font, eine neue "MagicNumber".
/*N*/   return new SwFntObj( *(SwSubFont *)pOwner, ++pMagicNo, pShell );
/*N*/ }

/*N*/ extern xub_StrLen lcl_CalcCaseMap( const SwFont& rFnt,
/*N*/                                    const XubString& rOrigString,
/*N*/                                    xub_StrLen nOfst,
/*N*/                                    xub_StrLen nLen,
/*N*/                                    xub_StrLen nIdx );

/*N*/ xub_StrLen SwFont::GetTxtBreak( SwDrawTextInfo& rInf, long nTextWidth )
/*N*/ {
/*N*/   ChgFnt( rInf.GetShell(), rInf.GetpOut() );
/*N*/
/*N*/     const BOOL bCompress = rInf.GetKanaComp() && rInf.GetLen() &&
/*N*/                            SW_CJK == GetActual() &&
/*N*/                            rInf.GetScriptInfo() &&
/*N*/                            rInf.GetScriptInfo()->CountCompChg() &&
/*N*/                      lcl_IsMonoSpaceFont( rInf.GetpOut() );
/*N*/
/*N*/     ASSERT( !bCompress || ( rInf.GetScriptInfo() && rInf.GetScriptInfo()->
/*N*/             CountCompChg()), "Compression without info" );
/*N*/
/*N*/   USHORT nTxtBreak = 0;
/*N*/   long nKern = 0;
/*N*/
/*N*/   USHORT nLn = ( rInf.GetLen() == STRING_LEN ? rInf.GetText().Len()
/*N*/                                              : rInf.GetLen() );
/*N*/
/*N*/     if ( rInf.GetFrm() && nLn && rInf.SnapToGrid() &&
/*N*/          rInf.GetFont() && SW_CJK == rInf.GetFont()->GetActual() )
/*N*/     {
/*?*/         GETGRID( rInf.GetFrm()->FindPageFrm() )
/*?*/         if ( pGrid && GRID_LINES_CHARS == pGrid->GetGridType() )
/*?*/         {
/*?*/             const USHORT nGridWidth = pGrid->GetBaseHeight();
/*?*/
/*?*/             long* pKernArray = new long[rInf.GetLen()];
/*?*/             rInf.GetOut().GetTextArray( rInf.GetText(), pKernArray,
/*?*/                                         rInf.GetIdx(), rInf.GetLen() );
/*?*/
/*?*/             long nWidthPerChar = pKernArray[ rInf.GetLen() - 1 ] / rInf.GetLen();
/*?*/
/*?*/             const ULONG i = nWidthPerChar ?
/*?*/                                 ( nWidthPerChar - 1 ) / nGridWidth + 1:
/*?*/                                 1;
/*?*/
/*?*/             nWidthPerChar = i * nGridWidth;
/*?*/             long nCurrPos = nWidthPerChar;
/*?*/
/*?*/             while( nTxtBreak < rInf.GetLen() && nTextWidth >= nCurrPos )
/*?*/             {
/*?*/                 nCurrPos += nWidthPerChar;
/*?*/                 ++nTxtBreak;
/*?*/             }
/*?*/
/*?*/             delete[] pKernArray;
/*?*/             return nTxtBreak + rInf.GetIdx();
/*N*/         }
/*N*/     }
/*N*/
/*N*/     if( aSub[nActual].IsCapital() && nLn )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 nTxtBreak = GetCapitalBreak( rInf.GetShell(), rInf.GetpOut(),
//STRIP001 /*?*/        rInf.GetScriptInfo(), rInf.GetText(), nTextWidth,0, rInf.GetIdx(),nLn );
/*N*/   else
/*N*/   {
/*N*/       nKern = CheckKerning();
/*N*/
/*N*/         const XubString* pTmpText;
/*N*/         XubString aTmpText;
/*N*/         xub_StrLen nTmpIdx;
/*N*/         xub_StrLen nTmpLen;
/*N*/         bool bTextReplaced = false;
/*N*/
/*N*/         if ( !aSub[nActual].IsCaseMap() )
/*N*/         {
/*N*/             pTmpText = &rInf.GetText();
/*N*/             nTmpIdx = rInf.GetIdx();
/*N*/             nTmpLen = nLn;
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/           const XubString aSnippet( rInf.GetText(), rInf.GetIdx(), nLn );
/*N*/             aTmpText = aSub[nActual].CalcCaseMap( aSnippet );
/*N*/             const bool bTitle = SVX_CASEMAP_TITEL == aSub[nActual].GetCaseMap() &&
/*N*/                                 pBreakIt->xBreak.is();
/*N*/
/*N*/             // Uaaaaahhhh!!! In title case mode, we would get wrong results
/*N*/             if ( bTitle && nLn )
/*N*/             {
/*N*/                 // check if rInf.GetIdx() is begin of word
/*N*/                 if ( !pBreakIt->xBreak->isBeginWord(
/*N*/                      rInf.GetText(), rInf.GetIdx(),
/*N*/                      pBreakIt->GetLocale( aSub[nActual].GetLanguage() ),
/*N*/                      ::com::sun::star::i18n::WordType::ANYWORD_IGNOREWHITESPACES ) )
/*N*/                 {
/*N*/                     // In this case, the beginning of aTmpText is wrong.
/*N*/                     XubString aSnippetTmp( aSnippet, 0, 1 );
/*N*/                     aSnippetTmp = aSub[nActual].CalcCaseMap( aSnippetTmp );
/*N*/                     aTmpText.Erase( 0, aSnippetTmp.Len() );
/*N*/                     aTmpText.Insert( aSnippet.GetChar( 0 ), 0 );
/*N*/                 }
/*N*/             }
/*N*/
/*N*/             pTmpText = &aTmpText;
/*N*/             nTmpIdx = 0;
/*N*/             nTmpLen = aTmpText.Len();
/*N*/             bTextReplaced = true;
/*N*/         }
/*N*/
/*N*/           if( rInf.GetHyphPos() )
/*N*/           nTxtBreak = rInf.GetpOut()->GetTextBreak( *pTmpText, nTextWidth,
/*N*/                                                       '-', *rInf.GetHyphPos(),
/*N*/                                                       nTmpIdx, nTmpLen, nKern );
/*N*/         else
/*N*/               nTxtBreak = rInf.GetpOut()->GetTextBreak( *pTmpText, nTextWidth,
/*N*/                                                       nTmpIdx, nTmpLen, nKern );
/*N*/
/*N*/         if ( bTextReplaced && STRING_LEN != nTxtBreak )
/*N*/         {
/*N*/             if ( nTmpLen != nLn )
/*N*/                 nTxtBreak = lcl_CalcCaseMap( *this, rInf.GetText(),
/*N*/                                              rInf.GetIdx(), nLn, nTxtBreak );
/*N*/             else
/*N*/                 nTxtBreak += rInf.GetIdx();
/*N*/         }
/*N*/   }
/*N*/
/*N*/     if ( ! bCompress )
/*N*/         return nTxtBreak;
/*N*/
/*N*/     nTxtBreak -= rInf.GetIdx();
/*N*/
/*N*/     if( nTxtBreak < nLn )
/*N*/   {
/*N*/         if( !nTxtBreak && nLn )
/*N*/           nLn = 1;
/*N*/       else if( nLn > 2 * nTxtBreak )
/*N*/           nLn = 2 * nTxtBreak;
/*N*/       long *pKernArray = new long[ nLn ];
/*N*/       rInf.GetOut().GetTextArray( rInf.GetText(), pKernArray,
/*N*/                                   rInf.GetIdx(), nLn );
/*N*/         if( rInf.GetScriptInfo()->Compress( pKernArray, rInf.GetIdx(), nLn,
/*N*/                           rInf.GetKanaComp(), (USHORT)GetHeight( nActual ) ) )
/*N*/       {
/*N*/           long nKernAdd = nKern;
/*N*/           xub_StrLen nTmpBreak = nTxtBreak;
/*N*/           if( nKern && nTxtBreak )
/*N*/               nKern *= nTxtBreak - 1;
/*N*/           while( nTxtBreak<nLn && nTextWidth >= pKernArray[nTxtBreak] +nKern )
/*N*/           {
/*N*/               nKern += nKernAdd;
/*N*/               ++nTxtBreak;
/*N*/           }
/*N*/           if( rInf.GetHyphPos() )
/*N*/               *rInf.GetHyphPos() += nTxtBreak - nTmpBreak; // It's not perfect
/*N*/       }
/*N*/       delete[] pKernArray;
/*N*/     }
/*N*/     nTxtBreak += rInf.GetIdx();
/*N*/
/*N*/     return nTxtBreak;
/*N*/ }

extern Color aGlobalRetoucheColor;

//STRIP001 sal_Bool SwDrawTextInfo::ApplyAutoColor( Font* pFnt )
//STRIP001 {
//STRIP001     const Font& rFnt = pFnt ? *pFnt : GetOut().GetFont();
//STRIP001     sal_Bool bPrt = GetShell() && ! GetShell()->GetWin();
//STRIP001     ColorData nNewColor = COL_BLACK;
//STRIP001     sal_Bool bChgFntColor = sal_False;
//STRIP001     sal_Bool bChgUnderColor = sal_False;
//STRIP001
//STRIP001     if( bPrt && GetShell() && GetShell()->GetViewOptions()->IsBlackFont() )
//STRIP001  {
//STRIP001         if ( COL_BLACK != rFnt.GetColor().GetColor() )
//STRIP001             bChgFntColor = sal_True;
//STRIP001
//STRIP001         if ( COL_BLACK != GetOut().GetTextLineColor().GetColor() )
//STRIP001             bChgUnderColor = sal_True;
//STRIP001  }
//STRIP001     else
//STRIP001     {
//STRIP001         // FontColor has to be changed if:
//STRIP001         // 1. FontColor = AUTO or 2. IsAlwaysAutoColor is set
//STRIP001         // UnderLineColor has to be changed if:
//STRIP001         // 1. IsAlwaysAutoColor is set
//STRIP001
//STRIP001         bChgUnderColor = ! bPrt && GetShell() &&
//STRIP001                 GetShell()->GetAccessibilityOptions()->IsAlwaysAutoColor();
//STRIP001
//STRIP001         bChgFntColor = COL_AUTO == rFnt.GetColor().GetColor() || bChgUnderColor;
//STRIP001
//STRIP001         if ( bChgFntColor )
//STRIP001         {
//STRIP001             // check if current background has a user defined setting
//STRIP001             const Color* pCol = GetFont() ? GetFont()->GetBackColor() : NULL;
//STRIP001             if( ! pCol || COL_TRANSPARENT == pCol->GetColor() )
//STRIP001             {
//STRIP001                 const SvxBrushItem* pItem;
//STRIP001                 SwRect aOrigBackRect;
//STRIP001
//STRIP001                 /// OD 21.08.2002
//STRIP001                 ///     consider, that [GetBackgroundBrush(...)] can set <pCol>
//STRIP001                 ///     - see implementation in /core/layout/paintfrm.cxx
//STRIP001                 /// OD 21.08.2002 #99657#
//STRIP001                 ///     There is a user defined setting for the background, if there
//STRIP001                 ///     is a background brush and its color is *not* "no fill"/"auto fill".
//STRIP001                 if( GetFrm()->GetBackgroundBrush( pItem, pCol, aOrigBackRect, FALSE ) )
//STRIP001                 {
//STRIP001                     if ( !pCol )
//STRIP001                     {
//STRIP001                         pCol = &pItem->GetColor();
//STRIP001                     }
//STRIP001
//STRIP001                     /// OD 30.08.2002 #99657#
//STRIP001                     /// determined color <pCol> can be <COL_TRANSPARENT>. Thus, check it.
//STRIP001                     if ( pCol->GetColor() == COL_TRANSPARENT)
//STRIP001                         pCol = NULL;
//STRIP001                 }
//STRIP001                 else
//STRIP001                     pCol = NULL;
//STRIP001             }
//STRIP001
//STRIP001             // no user defined color at paragraph or font background
//STRIP001             if ( ! pCol )
//STRIP001                 pCol = &aGlobalRetoucheColor;
//STRIP001
//STRIP001             if( GetShell() && GetShell()->GetWin() )
//STRIP001             {
//STRIP001                 // here we determine the prefered window text color for painting
//STRIP001                 const SwViewOption* pViewOption = GetShell()->GetViewOptions();
//STRIP001                 if(pViewOption->IsPagePreview() &&
//STRIP001                         !SW_MOD()->GetAccessibilityOptions().GetIsForPagePreviews())
//STRIP001                     nNewColor = COL_BLACK;
//STRIP001                 else
//STRIP001                     // we take the font color from the appearence page
//STRIP001                     nNewColor = SwViewOption::GetFontColor().GetColor();
//STRIP001             }
//STRIP001
//STRIP001             // change painting color depending of dark/bright background
//STRIP001             Color aTmpColor( nNewColor );
//STRIP001             if ( pCol->IsDark() && aTmpColor.IsDark() )
//STRIP001                 nNewColor = COL_WHITE;
//STRIP001             else if ( pCol->IsBright() && aTmpColor.IsBright() )
//STRIP001                 nNewColor = COL_BLACK;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( bChgFntColor || bChgUnderColor )
//STRIP001     {
//STRIP001         Color aNewColor( nNewColor );
//STRIP001
//STRIP001         if ( bChgFntColor )
//STRIP001         {
//STRIP001             if ( pFnt && aNewColor != pFnt->GetColor() )
//STRIP001             {
//STRIP001                 // only set the new color at the font passed as argument
//STRIP001                 pFnt->SetColor( aNewColor );
//STRIP001             }
//STRIP001             else if ( aNewColor != GetOut().GetFont().GetColor() )
//STRIP001             {
//STRIP001                 // set new font with new color at output device
//STRIP001                 Font aFont( rFnt );
//STRIP001                 aFont.SetColor( aNewColor );
//STRIP001                 GetOut().SetFont( aFont );
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // the underline color has to be set separately
//STRIP001         if ( bChgUnderColor )
//STRIP001         {
//STRIP001             // get current font color or color set at output device
//STRIP001             aNewColor = pFnt ? pFnt->GetColor() : GetOut().GetFont().GetColor();
//STRIP001             if ( aNewColor != GetOut().GetTextLineColor() )
//STRIP001                 GetOut().SetTextLineColor( aNewColor );
//STRIP001         }
//STRIP001
//STRIP001         return sal_True;
//STRIP001  }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

}
