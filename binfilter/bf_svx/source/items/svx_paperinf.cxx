/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_paperinf.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:17:16 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

// include ---------------------------------------------------------------

#include <limits.h>


#ifndef _SVX_DIALOGS_HRC
#include "dialogs.hrc"
#endif
#ifndef _SVX_PAPERINF_HXX
#include "paperinf.hxx"
#endif
namespace binfilter {

#define SVX_PAPER_OFFSET    3   // Anfang: enum Paper A3 - SvxPaper A0; Diff=3

// STATIC DATA -----------------------------------------------------------

static Size __FAR_DATA aDinTab[] =
{
    Size(lA0Width,lA0Height),           // A0
    Size(lA1Width,lA1Height),           // A1
    Size(lA2Width,lA2Height),           // A2
    Size(lA3Width,lA3Height),           // A3
    Size(lA4Width,lA4Height),           // A4
    Size(lA5Width,lA5Height),           // A5
    Size(lB4Width, lB4Height),          // B4
    Size(lB5Width,lB5Height),           // B5
    Size(lLetterWidth,lLetterHeight),   // LETTER
    Size(lLegalWidth,lLegalHeight),     // LEGAL
    Size(lTabloidWidth,lTabloidHeight), // TABLOID
    Size(0, 0),                         // USER
    Size(lB6Width, lB6Height),          // B6
    Size(lC4Width, lC4Height),          // C4
    Size(lC5Width, lC5Height),          // C5
    Size(lC6Width, lC6Height),          // C6
    Size(lC65Width, lC65Height),        // C65
    Size(lDLWidth, lDLHeight),          // DL
    Size(lDiaWidth,lDiaHeight ),        // DIA
    Size(lScreenWidth, lScreenHeight),  // SCREEN
    Size(lAWidth, lAHeight),            // A
    Size(lBWidth, lBHeight),            // B
    Size(lCWidth, lCHeight),            // C
    Size(lDWidth, lDHeight),            // D
    Size(lEWidth, lEHeight),            // E
    Size(lExeWidth, lExeHeight),        // Executive
    Size(lLegal2Width, lLegal2Height),  // Legal2
    Size(lMonarchWidth, lMonarchHeight),// Monarch
    Size(lCom675Width, lCom675Height),  // COM-6 3/4
    Size(lCom9Width, lCom9Height),      // COM-9
    Size(lCom10Width, lCom10Height),    // COM-10
    Size(lCom11Width, lCom11Height),    // COM-11
    Size(lCom12Width, lCom12Height),    // COM-12
    Size(lKai16Width, lKai16Height),    // 16 kai
    Size(lKai32Width, lKai32Height),    // 32 kai
    Size(lKai32BigWidth, lKai32BigHeight), // 32 kai gross
    Size(lJISB4Width, lJISB4Height),       // B4 (JIS)
    Size(lJISB5Width, lJISB5Height),       // B5 (JIS)
    Size(lJISB6Width, lJISB6Height)        // B6 (JIS)
};

static const int nTabSize = sizeof(aDinTab) / sizeof(aDinTab[0]);

// -----------------------------------------------------------------------

/*N*/ long TwipsTo100thMM( long nIn )
/*N*/ {
/*N*/   long nRet = OutputDevice::LogicToLogic( nIn, MAP_TWIP, MAP_100TH_MM );
/*N*/   long nTmp = nRet % 10;
/*N*/
/*N*/   if ( nTmp )
/*N*/       nRet += 10 - nTmp;
/*N*/   return nRet;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ Size ConvertTo100thMM( Size& rSize )
/*N*/ {
/*N*/   // Convert form TWIPS to 100TH_MM
/*N*/   long nW = TwipsTo100thMM( rSize.Width() );
/*N*/   long nH = TwipsTo100thMM( rSize.Height() );
/*N*/
/*N*/   rSize.Width() = nW;
/*N*/   rSize.Height() = nH;
/*N*/   return rSize;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ long HundMMToTwips( long nIn )
/*N*/ {
/*N*/   long nRet = OutputDevice::LogicToLogic( nIn, MAP_100TH_MM, MAP_TWIP );
/*N*/   return nRet;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ Size ConvertToTwips( Size& rSize )
/*N*/ {
/*N*/   // Convert form TWIPS to 100TH_MM
/*N*/   long nW = HundMMToTwips( rSize.Width() );
/*N*/   long nH = HundMMToTwips( rSize.Height() );
/*N*/
/*N*/   rSize.Width() = nW;
/*N*/   rSize.Height() = nH;
/*N*/   return rSize;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxPaper GetPaper_Impl( const Size &rSize, MapUnit eUnit, BOOL bSloppy )
/*N*/ {
/*N*/   DBG_ASSERT( eUnit == MAP_TWIP || eUnit == MAP_100TH_MM,
/*N*/               "map unit not supported" );
/*N*/   Size aSize = rSize;
/*N*/
/*N*/   if ( eUnit == MAP_100TH_MM )
/*N*/       ConvertToTwips( aSize );
/*N*/
/*N*/   for ( USHORT i = 0; i < nTabSize; i++ )
/*N*/   {
/*N*/       if ( aDinTab[i] == aSize )
/*N*/           return (SvxPaper)i;
/*N*/       else if ( bSloppy )
/*N*/       {
/*N*/           long lDiffW = Abs(aDinTab[i].Width () - aSize.Width ()),
/*N*/                lDiffH = Abs(aDinTab[i].Height() - aSize.Height());
/*N*/
/*N*/           if ( lDiffW < 6 && lDiffH < 6 )
/*N*/               return (SvxPaper)i;
/*N*/       }
/*N*/   }
/*N*/   return SVX_PAPER_USER;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:   Ist der Printer gueltig
 --------------------------------------------------------------------*/

/*?*/ inline BOOL IsValidPrinter( const Printer* pPtr )
/*?*/ {
/*?*/   return pPtr->GetName().Len() ? TRUE : FALSE;
/*?*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Konvertierung eines SV-Defines fuer Papiergroesse in
                Twips.
                Funktioniert logischerweise nicht fuer User Groessen
                (ASSERT).
------------------------------------------------------------------------*/

/*N*/ Size SvxPaperInfo::GetPaperSize( SvxPaper ePaper, MapUnit eUnit )
/*N*/ {
/*N*/   DBG_ASSERT( ePaper < nTabSize, "Tabelle der Papiergroessen ueberindiziert" );
/*N*/   DBG_ASSERT( eUnit == MAP_TWIP || eUnit == MAP_100TH_MM, "this MapUnit not supported" );
/*N*/   Size aSize = aDinTab[ePaper];   // in Twips
/*N*/
/*N*/   if ( eUnit == MAP_100TH_MM )
/*N*/       ConvertTo100thMM( aSize );
/*N*/   return aSize;
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Papiergroesse der Druckers liefern, aligned auf
                die eigenen Groessen.
                Falls kein Printer im System eingestellt ist,
                wird DIN A4 Portrait als Defaultpapiergroesse geliefert.
------------------------------------------------------------------------*/

/*N*/ Size SvxPaperInfo::GetPaperSize( const Printer* pPrinter )
/*N*/ {
/*N*/   if ( !IsValidPrinter(pPrinter) )
/*?*/       return GetPaperSize( SVX_PAPER_A4 );
/*N*/   const SvxPaper ePaper = (SvxPaper)(pPrinter->GetPaper() + SVX_PAPER_OFFSET);
/*N*/
/*N*/   if ( ePaper == SVX_PAPER_USER )
/*N*/   {
/*N*/           // Orientation nicht beruecksichtigen, da durch SV bereits
/*N*/           // die richtigen Masze eingestellt worden sind.
/*N*/       Size aPaperSize = pPrinter->GetPaperSize();
/*N*/       const Size aInvalidSize;
/*N*/
/*N*/       if ( aPaperSize == aInvalidSize )
/*?*/           return GetPaperSize(SVX_PAPER_A4);
/*N*/       MapMode aMap1 = pPrinter->GetMapMode();
/*N*/       MapMode aMap2;
/*N*/
/*N*/       if ( aMap1 == aMap2 )
/*N*/           aPaperSize =
/*N*/               pPrinter->PixelToLogic( aPaperSize, MapMode( MAP_TWIP ) );
/*N*/       return aPaperSize;
/*N*/   }
/*N*/
/*N*/   const Orientation eOrient = pPrinter->GetOrientation();
/*N*/   Size aSize( GetPaperSize( ePaper ) );
/*N*/       // bei Landscape die Seiten tauschen, ist bei SV schon geschehen
/*N*/   if ( eOrient == ORIENTATION_LANDSCAPE )
/*?*/       Swap( aSize );
/*N*/   return aSize;
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Konvertierung einer Papiergroesse in Twips in das
                SV-Define. Ist bSloppy TRUE, so wird nur auf 1/10 mm genau
                verglichen.
------------------------------------------------------------------------*/


// -----------------------------------------------------------------------

/*N*/ SvxPaper SvxPaperInfo::GetSvxPaper( const Size &rSize, MapUnit eUnit, BOOL bSloppy )
/*N*/ {
/*N*/   return GetPaper_Impl( rSize, eUnit, bSloppy );
/*N*/ }

// -----------------------------------------------------------------------


/*------------------------------------------------------------------------
 Beschreibung:  String Repr"asentation f"ur die SV-Defines f"ur
                Papiergroessen.
------------------------------------------------------------------------*/



}
