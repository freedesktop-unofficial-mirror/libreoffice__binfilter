/*************************************************************************
 *
 *  $RCSfile: svx_paperinf.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:03 $
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

// include ---------------------------------------------------------------

#include <limits.h>

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _SVX_DIALOGS_HRC
#include "dialogs.hrc"
#endif
#ifndef _SVX_PAPERINF_HXX
#include "paperinf.hxx"
#endif
#ifndef _SVX_DIALMGR_HXX
#include "dialmgr.hxx"
#endif

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

//STRIP001 SvxPaper SvxPaperInfo::GetPaper( const Size &rSize, MapUnit eUnit, BOOL bSloppy )
//STRIP001 {
//STRIP001  return GetPaper_Impl( rSize, eUnit, bSloppy );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxPaper SvxPaperInfo::GetSvxPaper( const Size &rSize, MapUnit eUnit, BOOL bSloppy )
/*N*/ {
/*N*/   return GetPaper_Impl( rSize, eUnit, bSloppy );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 Paper SvxPaperInfo::GetSvPaper( const Size &rSize, MapUnit eUnit,
//STRIP001                              BOOL bSloppy )
//STRIP001 {
//STRIP001  Paper eRet = PAPER_USER;
//STRIP001  SvxPaper ePaper = GetPaper_Impl( rSize, eUnit, bSloppy );
//STRIP001
//STRIP001  switch ( ePaper )
//STRIP001  {
//STRIP001      case SVX_PAPER_A3:      eRet = PAPER_A3;                        break;
//STRIP001      case SVX_PAPER_A4:      eRet = PAPER_A4;                        break;
//STRIP001      case SVX_PAPER_A5:      eRet = PAPER_A5;                        break;
//STRIP001      case SVX_PAPER_B4:      eRet = PAPER_B4;                        break;
//STRIP001      case SVX_PAPER_B5:      eRet = PAPER_B5;                        break;
//STRIP001      case SVX_PAPER_LETTER:  eRet = PAPER_LETTER;                    break;
//STRIP001      case SVX_PAPER_LEGAL:   eRet = PAPER_LEGAL;                     break;
//STRIP001      case SVX_PAPER_TABLOID: eRet = PAPER_TABLOID;                   break;
//STRIP001  }
//STRIP001
//STRIP001  return eRet;
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  String Repr"asentation f"ur die SV-Defines f"ur
                Papiergroessen.
------------------------------------------------------------------------*/

//STRIP001 String SvxPaperInfo::GetName( SvxPaper ePaper )
//STRIP001 {
//STRIP001  USHORT  nResId = 0;
//STRIP001
//STRIP001  switch ( ePaper )
//STRIP001  {
//STRIP001      case SVX_PAPER_A0:          nResId = RID_SVXSTR_PAPER_A0;       break;
//STRIP001      case SVX_PAPER_A1:          nResId = RID_SVXSTR_PAPER_A1;       break;
//STRIP001      case SVX_PAPER_A2:          nResId = RID_SVXSTR_PAPER_A2;       break;
//STRIP001      case SVX_PAPER_A3:          nResId = RID_SVXSTR_PAPER_A3;       break;
//STRIP001      case SVX_PAPER_A4:          nResId = RID_SVXSTR_PAPER_A4;       break;
//STRIP001      case SVX_PAPER_A5:          nResId = RID_SVXSTR_PAPER_A5;       break;
//STRIP001      case SVX_PAPER_B4:          nResId = RID_SVXSTR_PAPER_B4;       break;
//STRIP001      case SVX_PAPER_B5:          nResId = RID_SVXSTR_PAPER_B5;       break;
//STRIP001      case SVX_PAPER_LETTER:      nResId = RID_SVXSTR_PAPER_LETTER;   break;
//STRIP001      case SVX_PAPER_LEGAL:       nResId = RID_SVXSTR_PAPER_LEGAL;    break;
//STRIP001      case SVX_PAPER_TABLOID:     nResId = RID_SVXSTR_PAPER_TABLOID;  break;
//STRIP001      case SVX_PAPER_USER:        nResId = RID_SVXSTR_PAPER_USER;     break;
//STRIP001      case SVX_PAPER_B6:          nResId = RID_SVXSTR_PAPER_B6;       break;
//STRIP001      case SVX_PAPER_C4:          nResId = RID_SVXSTR_PAPER_C4;       break;
//STRIP001      case SVX_PAPER_C5:          nResId = RID_SVXSTR_PAPER_C5;       break;
//STRIP001      case SVX_PAPER_C6:          nResId = RID_SVXSTR_PAPER_C6;       break;
//STRIP001      case SVX_PAPER_C65:         nResId = RID_SVXSTR_PAPER_C65;      break;
//STRIP001      case SVX_PAPER_DL:          nResId = RID_SVXSTR_PAPER_DL;       break;
//STRIP001      case SVX_PAPER_DIA:         nResId = RID_SVXSTR_PAPER_DIA;      break;
//STRIP001      case SVX_PAPER_SCREEN:      nResId = RID_SVXSTR_PAPER_SCREEN;   break;
//STRIP001      case SVX_PAPER_A:           nResId = RID_SVXSTR_PAPER_A;        break;
//STRIP001      case SVX_PAPER_B:           nResId = RID_SVXSTR_PAPER_B;        break;
//STRIP001      case SVX_PAPER_C:           nResId = RID_SVXSTR_PAPER_C;        break;
//STRIP001      case SVX_PAPER_D:           nResId = RID_SVXSTR_PAPER_D;        break;
//STRIP001      case SVX_PAPER_E:           nResId = RID_SVXSTR_PAPER_E;        break;
//STRIP001      case SVX_PAPER_EXECUTIVE:   nResId = RID_SVXSTR_PAPER_EXECUTIVE;break;
//STRIP001      case SVX_PAPER_LEGAL2:      nResId = RID_SVXSTR_PAPER_LEGAL2;   break;
//STRIP001      case SVX_PAPER_MONARCH:     nResId = RID_SVXSTR_PAPER_MONARCH;  break;
//STRIP001      case SVX_PAPER_COM675:      nResId = RID_SVXSTR_PAPER_COM675;   break;
//STRIP001      case SVX_PAPER_COM9:        nResId = RID_SVXSTR_PAPER_COM9;     break;
//STRIP001      case SVX_PAPER_COM10:       nResId = RID_SVXSTR_PAPER_COM10;    break;
//STRIP001      case SVX_PAPER_COM11:       nResId = RID_SVXSTR_PAPER_COM11;    break;
//STRIP001      case SVX_PAPER_COM12:       nResId = RID_SVXSTR_PAPER_COM12;    break;
//STRIP001      case SVX_PAPER_KAI16:       nResId = RID_SVXSTR_PAPER_KAI16;    break;
//STRIP001      case SVX_PAPER_KAI32:       nResId = RID_SVXSTR_PAPER_KAI32;    break;
//STRIP001      case SVX_PAPER_KAI32BIG:    nResId = RID_SVXSTR_PAPER_KAI32BIG; break;
//STRIP001      case SVX_PAPER_B4_JIS:      nResId = RID_SVXSTR_PAPER_B4_JIS;   break;
//STRIP001      case SVX_PAPER_B5_JIS:      nResId = RID_SVXSTR_PAPER_B5_JIS;   break;
//STRIP001      case SVX_PAPER_B6_JIS:      nResId = RID_SVXSTR_PAPER_B6_JIS;   break;
//STRIP001
//STRIP001      default: DBG_ERRORFILE( "unknown papersize" );
//STRIP001  }
//STRIP001
//STRIP001  return ( nResId > 0 ) ? String( SVX_RES( nResId ) ) : String();
//STRIP001 }


