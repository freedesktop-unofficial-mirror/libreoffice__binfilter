/*************************************************************************
 *
 *  $RCSfile: sfx2_printer.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:20 $
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

#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif
#ifndef _SV_METRIC_HXX //autogen
#include <vcl/metric.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _SV_PRINTDLG_HXX_ //autogen
#include <svtools/printdlg.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PRINTWARNINGOPTIONS_HXX
#include <svtools/printwarningoptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PRINTOPTIONS_HXX
#include <svtools/printoptions.hxx>
#endif
#include <vector>

#pragma hdrstop

#include "printer.hxx"
#include "printopt.hxx"
#include "sfxtypes.hxx"
#include "prnmon.hxx"
#include "viewsh.hxx"
#include "tabdlg.hxx"
#include "sfxresid.hxx"
#include "view.hrc"
namespace binfilter {

#ifdef MSC
// der ist buggy
#define NEW_OBJECTS(Class, nCount) ((Class*) new char[ sizeof(Class) * (nCount) ])
#else
#define NEW_OBJECTS(Class, nCount) (new Class[nCount])
#endif


//STRIP001 USHORT SfxFontSizeInfo::pStaticSizes[] =
//STRIP001 {
//STRIP001 #ifdef MAC
//STRIP001  90,
//STRIP001 #else
//STRIP001  60,
//STRIP001  80,
//STRIP001 #endif
//STRIP001  100,
//STRIP001  120,
//STRIP001  140,
//STRIP001  180,
//STRIP001  240,
//STRIP001  360,
//STRIP001  480,
//STRIP001  600,
//STRIP001  720
//STRIP001 };

//--------------------------------------------------------------------

/*N*/ SV_DECL_PTRARR_DEL(SfxFontArr_Impl,SfxFont*,10,5)

// struct SfxPrinter_Impl ------------------------------------------------

/*N*/ struct SfxPrinter_Impl
/*N*/ {
/*N*/   SfxFontArr_Impl*    mpFonts;
/*N*/   BOOL                mbAll;
/*N*/   BOOL                mbSelection;
/*N*/   BOOL                mbFromTo;
/*N*/   BOOL                mbRange;
/*N*/
/*N*/   SfxPrinter_Impl() :
/*N*/       mpFonts     ( NULL ),
/*N*/       mbAll       ( TRUE ),
/*N*/       mbSelection ( TRUE ),
/*N*/       mbFromTo    ( TRUE ),
/*N*/       mbRange     ( TRUE ) {}
/*N*/   ~SfxPrinter_Impl() { delete mpFonts; }
/*N*/ };

/*N*/ #define FONTS()   pImpl->mpFonts

//STRIP001 struct SfxPrintOptDlg_Impl
//STRIP001 {
//STRIP001 #if SUPD <= 640
//STRIP001  HelpButton*     mpHelpBtn;
//STRIP001 #endif
//STRIP001  sal_Bool        mbHelpDisabled;
//STRIP001
//STRIP001  SfxPrintOptDlg_Impl() :
//STRIP001 #if SUPD <= 640
//STRIP001      mpHelpBtn       ( NULL ),
//STRIP001 #endif
//STRIP001      mbHelpDisabled  ( sal_False ) {}
//STRIP001 };

//--------------------------------------------------------------------

//STRIP001 SfxFontSizeInfo::SfxFontSizeInfo( const SfxFont &rFont,
//STRIP001                                const OutputDevice &rDevice ) :
//STRIP001
//STRIP001  pSizes(0),
//STRIP001  nSizes(0),
//STRIP001  bScalable(TRUE)
//STRIP001
//STRIP001 {
//STRIP001  if ( 0 == rDevice.GetDevFontCount() )
//STRIP001      bScalable = FALSE;
//STRIP001  else
//STRIP001  {
//STRIP001      OutputDevice &rDev = (OutputDevice&) rDevice;
//STRIP001      Font aFont(rFont.GetName(), Size(0,12));
//STRIP001      aFont.SetFamily(rFont.GetFamily());
//STRIP001      aFont.SetPitch(rFont.GetPitch());
//STRIP001      aFont.SetCharSet(rFont.GetCharSet());
//STRIP001
//STRIP001      // verfuegbare Groessen in die Liste eintragen, Groesse in 10tel Punkt
//STRIP001      USHORT nSizeCount = rDev.GetDevFontSizeCount(aFont);
//STRIP001      pSizes = NEW_OBJECTS(Size, nSizeCount);
//STRIP001      const MapMode aOldMapMode = rDev.GetMapMode();
//STRIP001      MapMode aMap(aOldMapMode);
//STRIP001      aMap.SetMapUnit(MAP_POINT);
//STRIP001      const Fraction aTen(1, 10);
//STRIP001      aMap.SetScaleX(aTen);
//STRIP001      aMap.SetScaleY(aTen);
//STRIP001      rDev.SetMapMode(aMap);
//STRIP001
//STRIP001      // Es gibt Fonts mit Bitmaps und skalierbaren Groessen
//STRIP001      // In diesem Fall wird der Fonts als skalierbar behandelt.
//STRIP001      BOOL bFoundScalable = FALSE;
//STRIP001      for ( USHORT i = 0; i < nSizeCount; ++i )
//STRIP001      {
//STRIP001          const Size aSize( rDev.GetDevFontSize(aFont, i) );
//STRIP001          if ( aSize.Height() != 0 )
//STRIP001              pSizes[nSizes++] = aSize;
//STRIP001          else
//STRIP001              bFoundScalable |= TRUE;
//STRIP001      }
//STRIP001      if( !bFoundScalable )
//STRIP001          bScalable = FALSE;
//STRIP001      else
//STRIP001      {
//STRIP001          // statische Font-Sizes verwenden
//STRIP001          __DELETE(nSizeCount) pSizes;
//STRIP001          nSizes = 0;
//STRIP001      }
//STRIP001      rDev.SetMapMode(aOldMapMode);
//STRIP001  }
//STRIP001
//STRIP001  if ( 0 == nSizes )
//STRIP001  {
//STRIP001      nSizes = sizeof(pStaticSizes) / sizeof(USHORT);
//STRIP001      pSizes = NEW_OBJECTS(Size, nSizes);
//STRIP001      for ( USHORT nPos = 0; nPos <nSizes; ++nPos )
//STRIP001         pSizes[nPos] = Size( 0, pStaticSizes[nPos] );
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxFontSizeInfo::~SfxFontSizeInfo()
//STRIP001 {
//STRIP001  __DELETE(nSizes) pSizes;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 BOOL SfxFontSizeInfo::HasSize(const Size &rSize) const
//STRIP001 {
//STRIP001  if ( bScalable )
//STRIP001      return TRUE;
//STRIP001  for ( USHORT i = 0; i < nSizes; ++i)
//STRIP001      if ( pSizes[i] == rSize )
//STRIP001          return TRUE;
//STRIP001  return FALSE;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ SfxFont::SfxFont( const FontFamily eFontFamily, const String& aFontName,
/*N*/                 const FontPitch eFontPitch, const CharSet eFontCharSet ):
/*N*/   aName( aFontName ),
/*N*/   eFamily( eFontFamily ),
/*N*/       ePitch( eFontPitch ),
/*N*/   eCharSet( eFontCharSet )
/*N*/ {
/*N*/ }

// class SfxPrinter ------------------------------------------------------

/*N*/ SfxPrinter* SfxPrinter::Create( SvStream& rStream, SfxItemSet* pOptions )

/*  [Beschreibung]

    Erzeugt einen <SfxPrinter> aus dem Stream. Geladen wird genaugenommen
    nur ein JobSetup. Falls ein solcher Drucker auf dem System nicht
    verf"augbar ist, wird das Original als Orig-JobSetup gemerkt und
    ein "anhlicher exisitierender Drucker genommen.

    Die 'pOptions' werden in den erzeugten SfxPrinter "ubernommen,
    der Returnwert geh"ort dem Caller.
*/

/*N*/ {
/*N*/   // JobSetup laden
/*N*/   JobSetup aFileJobSetup;
/*N*/   rStream >> aFileJobSetup;
/*N*/
/*N*/   // Drucker erzeugen
/*N*/   SfxPrinter *pPrinter = new SfxPrinter( pOptions, aFileJobSetup );
/*N*/   return pPrinter;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SvStream& SfxPrinter::Store( SvStream& rStream ) const

/*  [Beschreibung]

    Speichert das verwendete JobSetup des <SfxPrinter>s.
*/

/*N*/ {
/*N*/   return ( rStream << GetJobSetup() );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::SfxPrinter( SfxItemSet* pTheOptions ) :

/*  [Beschreibung]

    Dieser Ctor erzeugt einen Standard-Drucker.
*/

/*N*/   pOptions( pTheOptions ),
/*N*/   bKnown(sal_True)

/*N*/ {
/*N*/   pImpl = new SfxPrinter_Impl;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::SfxPrinter( SfxItemSet* pTheOptions,
/*N*/                       const JobSetup& rTheOrigJobSetup ) :

/*N*/   Printer         ( rTheOrigJobSetup.GetPrinterName() ),
/*N*/   pOptions        ( pTheOptions )

/*N*/ {
/*N*/   pImpl = new SfxPrinter_Impl;
/*N*/   bKnown = GetName() == rTheOrigJobSetup.GetPrinterName();
/*N*/
/*N*/   if ( bKnown )
/*N*/       SetJobSetup( rTheOrigJobSetup );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::SfxPrinter( SfxItemSet* pTheOptions,
/*N*/                       const String& rPrinterName ) :
/*N*/
/*N*/   Printer         ( rPrinterName ),
/*N*/   pOptions        ( pTheOptions ),
/*N*/   bKnown          ( GetName() == rPrinterName )
/*N*/
/*N*/ {
/*N*/   pImpl = new SfxPrinter_Impl;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 SfxPrinter::SfxPrinter( const SfxPrinter& rPrinter ) :
//STRIP001
//STRIP001  Printer ( rPrinter.GetName() ),
//STRIP001  pOptions( rPrinter.GetOptions().Clone() ),
//STRIP001  bKnown  ( rPrinter.IsKnown() )
//STRIP001 {
//STRIP001  SetJobSetup( rPrinter.GetJobSetup() );
//STRIP001  SetPrinterProps( &rPrinter );
//STRIP001  SetMapMode( rPrinter.GetMapMode() );
//STRIP001
//STRIP001  pImpl = new SfxPrinter_Impl;
//STRIP001  pImpl->mbAll = rPrinter.pImpl->mbAll;
//STRIP001  pImpl->mbSelection = rPrinter.pImpl->mbSelection;
//STRIP001  pImpl->mbFromTo = rPrinter.pImpl->mbFromTo;
//STRIP001  pImpl->mbRange = rPrinter.pImpl->mbRange;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxPrinter* SfxPrinter::Clone() const
//STRIP001 {
//STRIP001  if ( IsDefPrinter() )
//STRIP001  {
//STRIP001      SfxPrinter *pNewPrinter;
//STRIP001      pNewPrinter = new SfxPrinter( GetOptions().Clone() );
//STRIP001      pNewPrinter->SetJobSetup( GetJobSetup() );
//STRIP001      pNewPrinter->SetPrinterProps( this );
//STRIP001      pNewPrinter->SetMapMode( GetMapMode() );
//STRIP001      pNewPrinter->pImpl->mbAll = pImpl->mbAll;
//STRIP001      pNewPrinter->pImpl->mbSelection =pImpl->mbSelection;
//STRIP001      pNewPrinter->pImpl->mbFromTo = pImpl->mbFromTo;
//STRIP001      pNewPrinter->pImpl->mbRange =pImpl->mbRange;
//STRIP001      return pNewPrinter;
//STRIP001  }
//STRIP001  else
//STRIP001      return new SfxPrinter( *this );
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::~SfxPrinter()
/*N*/ {
/*N*/   delete pOptions;
/*N*/   delete pImpl;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxPrinter::SetOptions( const SfxItemSet &rNewOptions )
/*N*/ {
/*N*/   pOptions->Set(rNewOptions);
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxPrinter::EnableRange( USHORT nRange )
//STRIP001 {
//STRIP001  PrintDialogRange eRange = (PrintDialogRange)nRange;
//STRIP001
//STRIP001  if ( eRange == PRINTDIALOG_ALL )
//STRIP001      pImpl->mbAll = TRUE;
//STRIP001  else if ( eRange == PRINTDIALOG_SELECTION )
//STRIP001      pImpl->mbSelection = TRUE;
//STRIP001  else if ( eRange == PRINTDIALOG_FROMTO )
//STRIP001      pImpl->mbFromTo = TRUE;
//STRIP001  else if ( eRange == PRINTDIALOG_RANGE )
//STRIP001      pImpl->mbRange = TRUE;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxPrinter::DisableRange( USHORT nRange )
//STRIP001 {
//STRIP001  PrintDialogRange eRange = (PrintDialogRange)nRange;
//STRIP001
//STRIP001  if ( eRange == PRINTDIALOG_ALL )
//STRIP001      pImpl->mbAll = FALSE;
//STRIP001  else if ( eRange == PRINTDIALOG_SELECTION )
//STRIP001      pImpl->mbSelection = FALSE;
//STRIP001  else if ( eRange == PRINTDIALOG_FROMTO )
//STRIP001      pImpl->mbFromTo = FALSE;
//STRIP001  else if ( eRange == PRINTDIALOG_RANGE )
//STRIP001      pImpl->mbRange = FALSE;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 BOOL SfxPrinter::IsRangeEnabled( USHORT nRange ) const
//STRIP001 {
//STRIP001  PrintDialogRange eRange = (PrintDialogRange)nRange;
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if ( eRange == PRINTDIALOG_ALL )
//STRIP001      bRet = pImpl->mbAll;
//STRIP001  else if ( eRange == PRINTDIALOG_SELECTION )
//STRIP001      bRet = pImpl->mbSelection;
//STRIP001  else if ( eRange == PRINTDIALOG_FROMTO )
//STRIP001      bRet = pImpl->mbFromTo;
//STRIP001  else if ( eRange == PRINTDIALOG_RANGE )
//STRIP001      bRet = pImpl->mbRange;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ SV_IMPL_PTRARR(SfxFontArr_Impl,SfxFont*)

//--------------------------------------------------------------------

//STRIP001 const SfxFont* SfxFindFont_Impl( const SfxFontArr_Impl& rArr,
//STRIP001                               const String& rName )
//STRIP001 {
//STRIP001  const USHORT nCount = rArr.Count();
//STRIP001  for ( USHORT i = 0; i < nCount; ++i )
//STRIP001  {
//STRIP001      const SfxFont *pFont = rArr[i];
//STRIP001      if ( pFont->GetName() == rName )
//STRIP001          return pFont;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxPrinter::UpdateFonts_Impl()
//STRIP001 {
//STRIP001  VirtualDevice *pVirDev = 0;
//STRIP001  const OutputDevice *pOut = this;
//STRIP001
//STRIP001      // falls kein Drucker gefunden werden konnte, ein
//STRIP001      // temp. Device erzeugen fuer das Erfragen der Fonts
//STRIP001  if( !IsValid() )
//STRIP001      pOut = pVirDev = new VirtualDevice;
//STRIP001
//STRIP001  const USHORT nCount = pOut->GetDevFontCount();
//STRIP001  FONTS() =  new SfxFontArr_Impl((BYTE)nCount);
//STRIP001
//STRIP001  std::vector< Font > aNonRegularFonts;
//STRIP001  for(USHORT i = 0;i < nCount;++i)
//STRIP001  {
//STRIP001      Font aFont(pOut->GetDevFont(i));
//STRIP001      if ( (aFont.GetItalic() != ITALIC_NONE) ||
//STRIP001           (aFont.GetWeight() != WEIGHT_MEDIUM) )
//STRIP001      {
//STRIP001          // First: Don't add non-regular fonts. The font name is not unique so we have
//STRIP001          // to filter the device font list.
//STRIP001          aNonRegularFonts.push_back( aFont );
//STRIP001      }
//STRIP001      else if ( FONTS()->Count() == 0 ||
//STRIP001           (*FONTS())[FONTS()->Count()-1]->GetName() != aFont.GetName() )
//STRIP001      {
//STRIP001          DBG_ASSERT(0 == SfxFindFont_Impl(*FONTS(), aFont.GetName()), "Doppelte Fonts vom SV-Device!");
//STRIP001          SfxFont* pTmp = new SfxFont( aFont.GetFamily(), aFont.GetName(),
//STRIP001                                       aFont.GetPitch(), aFont.GetCharSet() );
//STRIP001          FONTS()->C40_INSERT(SfxFont, pTmp, FONTS()->Count());
//STRIP001      }
//STRIP001  }
//STRIP001  delete pVirDev;
//STRIP001
//STRIP001  // Try to add all non-regular fonts. It could be that there was no regular font
//STRIP001  // with the same name added.
//STRIP001  std::vector< Font >::const_iterator pIter;
//STRIP001  for ( pIter = aNonRegularFonts.begin(); pIter != aNonRegularFonts.end(); pIter++ )
//STRIP001  {
//STRIP001      if ( SfxFindFont_Impl( *FONTS(), pIter->GetName() ) == 0 )
//STRIP001      {
//STRIP001          SfxFont* pTmp = new SfxFont( pIter->GetFamily(), pIter->GetName(),
//STRIP001                                       pIter->GetPitch(), pIter->GetCharSet() );
//STRIP001          FONTS()->C40_INSERT( SfxFont, pTmp, FONTS()->Count() );
//STRIP001         }
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 USHORT SfxPrinter::GetFontCount()
//STRIP001 {
//STRIP001  if ( !FONTS() )
//STRIP001      UpdateFonts_Impl();
//STRIP001  return FONTS()->Count();
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 const SfxFont* SfxPrinter::GetFont( USHORT nNo ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( FONTS(), "bitte erst GetFontCount() abfragen!" );
//STRIP001  return (*FONTS())[ nNo ];
//STRIP001 }

//--------------------------------------------------------------------

/*?*/ const SfxFont* SfxPrinter::GetFontByName( const String &rFontName )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  if ( !FONTS() )
//STRIP001      UpdateFonts_Impl();
//STRIP001  return SfxFindFont_Impl(*FONTS(), rFontName);
/*?*/ }

//--------------------------------------------------------------------

//STRIP001 BOOL SfxPrinter::InitJob( Window* pUIParent, BOOL bDocumentContainsTransparentObjects )
//STRIP001 {
//STRIP001     const SvtPrinterOptions     aPrinterOpt;
//STRIP001     const SvtPrintFileOptions   aPrintFileOpt;
//STRIP001     const SvtBasePrintOptions*  pPrinterOpt = &aPrinterOpt;
//STRIP001     const SvtBasePrintOptions*  pPrintFileOpt = &aPrintFileOpt;
//STRIP001     PrinterOptions              aNewPrinterOptions;
//STRIP001     BOOL                        bRet = TRUE;
//STRIP001
//STRIP001     ( ( IsPrintFileEnabled() && GetPrintFile().Len() ) ? pPrintFileOpt : pPrinterOpt )->GetPrinterOptions( aNewPrinterOptions );
//STRIP001
//STRIP001  if( bDocumentContainsTransparentObjects && !aNewPrinterOptions.IsReduceTransparency() )
//STRIP001  {
//STRIP001      if ( !Application::IsHeadlessModeEnabled() )
//STRIP001      {
//STRIP001          SvtPrintWarningOptions aWarnOpt;
//STRIP001
//STRIP001          if( aWarnOpt.IsTransparency() )
//STRIP001          {
//STRIP001              TransparencyPrintWarningBox aWarnBox( pUIParent );
//STRIP001              const USHORT                nRet = aWarnBox.Execute();
//STRIP001
//STRIP001              if( nRet == RET_CANCEL )
//STRIP001                  bRet = FALSE;
//STRIP001              else
//STRIP001              {
//STRIP001                  aNewPrinterOptions.SetReduceTransparency( nRet != RET_NO );
//STRIP001                  aWarnOpt.SetTransparency( !aWarnBox.IsNoWarningChecked() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     if( bRet )
//STRIP001         SetPrinterOptions( aNewPrinterOptions );
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxPrintOptionsDialog::SfxPrintOptionsDialog( Window *pParent,
//STRIP001                                            SfxViewShell *pViewShell,
//STRIP001                                            const SfxItemSet *pSet ) :
//STRIP001
//STRIP001  ModalDialog( pParent, WinBits( WB_STDMODAL | WB_3DLOOK ) ),
//STRIP001
//STRIP001  aOkBtn      ( this ),
//STRIP001  aCancelBtn  ( this ),
//STRIP001 #if SUPD > 640
//STRIP001  aHelpBtn    ( this ),
//STRIP001 #endif
//STRIP001  pDlgImpl    ( new SfxPrintOptDlg_Impl ),
//STRIP001  pViewSh     ( pViewShell ),
//STRIP001  pOptions    ( pSet->Clone() ),
//STRIP001  pPage       ( NULL )
//STRIP001
//STRIP001 {
//STRIP001 #if SUPD <= 640
//STRIP001  pDlgImpl->mpHelpBtn = new HelpButton( this );
//STRIP001 #endif
//STRIP001  SetText( SfxResId( STR_PRINT_OPTIONS_TITLE ) );
//STRIP001
//STRIP001  // TabPage einh"angen
//STRIP001  pPage = pViewSh->CreatePrintOptionsPage( this, *pOptions );
//STRIP001  DBG_ASSERT( pPage, "CreatePrintOptions != SFX_VIEW_HAS_PRINTOPTIONS" );
//STRIP001  pPage->Reset( *pOptions );
//STRIP001  SetHelpId( pPage->GetHelpId() );
//STRIP001  pPage->Show();
//STRIP001
//STRIP001  // Dialoggr"o\se bestimmen
//STRIP001     Size a6Sz = LogicToPixel( Size( 6, 6 ), MAP_APPFONT );
//STRIP001  Size aBtnSz = LogicToPixel( Size( 50, 14 ), MAP_APPFONT );
//STRIP001     Size aOutSz( pPage->GetSizePixel() );
//STRIP001  aOutSz.Height() += 6;
//STRIP001     long nWidth = aBtnSz.Width();
//STRIP001     nWidth += a6Sz.Width();
//STRIP001     aOutSz.Width() += nWidth;
//STRIP001  if ( aOutSz.Height() < 90 )
//STRIP001      // mindestens die H"ohe der 3 Buttons
//STRIP001      aOutSz.Height() = 90;
//STRIP001  SetOutputSizePixel( aOutSz );
//STRIP001
//STRIP001  // set position and size of the buttons
//STRIP001     Point aBtnPos( aOutSz.Width() - aBtnSz.Width() - a6Sz.Width(), a6Sz.Height() );
//STRIP001  aOkBtn.SetPosSizePixel( aBtnPos, aBtnSz );
//STRIP001  aBtnPos.Y() += aBtnSz.Height() + ( a6Sz.Height() / 2 );
//STRIP001  aCancelBtn.SetPosSizePixel( aBtnPos, aBtnSz );
//STRIP001  aBtnPos.Y() += aBtnSz.Height() + a6Sz.Height();
//STRIP001 #if SUPD > 640
//STRIP001  aHelpBtn.SetPosSizePixel( aBtnPos, aBtnSz );
//STRIP001 #else
//STRIP001  pDlgImpl->mpHelpBtn->SetPosSizePixel( aBtnPos, aBtnSz );
//STRIP001 #endif
//STRIP001
//STRIP001  aCancelBtn.Show();
//STRIP001  aOkBtn.Show();
//STRIP001 #if SUPD > 640
//STRIP001  aHelpBtn.Show();
//STRIP001 #else
//STRIP001  pDlgImpl->mpHelpBtn->Show();
//STRIP001 #endif
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxPrintOptionsDialog::~SfxPrintOptionsDialog()
//STRIP001 {
//STRIP001 #if SUPD <= 640
//STRIP001  delete pDlgImpl->mpHelpBtn;
//STRIP001 #endif
//STRIP001  delete pDlgImpl;
//STRIP001  delete pPage;
//STRIP001  delete pOptions;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 short SfxPrintOptionsDialog::Execute()
//STRIP001 {
//STRIP001  short nRet = ModalDialog::Execute();
//STRIP001  if ( nRet == RET_OK )
//STRIP001      pPage->FillItemSet( *pOptions );
//STRIP001  else
//STRIP001      pPage->Reset( *pOptions );
//STRIP001  return nRet;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 long SfxPrintOptionsDialog::Notify( NotifyEvent& rNEvt )
//STRIP001 {
//STRIP001  if ( rNEvt.GetType() == EVENT_KEYINPUT )
//STRIP001  {
//STRIP001      if ( rNEvt.GetKeyEvent()->GetKeyCode().GetCode() == KEY_F1 && pDlgImpl->mbHelpDisabled )
//STRIP001          return 1; // help disabled -> <F1> does nothing
//STRIP001  }
//STRIP001
//STRIP001  return ModalDialog::Notify( rNEvt );
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxPrintOptionsDialog::DisableHelp()
//STRIP001 {
//STRIP001  pDlgImpl->mbHelpDisabled = sal_True;
//STRIP001
//STRIP001 #if SUPD > 640
//STRIP001  aHelpBtn.Disable();
//STRIP001 #else
//STRIP001  pDlgImpl->mpHelpBtn->Disable();
//STRIP001 #endif
//STRIP001 }

}
