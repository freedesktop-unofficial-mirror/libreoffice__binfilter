/*************************************************************************
 *
 *  $RCSfile: sc_docoptio.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:29 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

#include <vcl/svapp.hxx>
#include <svtools/zforlist.hxx>

#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Sequence.hxx>

#include "cfgids.hxx"
#include "docoptio.hxx"
#include "rechead.hxx"
#include "scresid.hxx"
#include "bf_sc.hrc"
#include "miscuno.hxx"
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

//------------------------------------------------------------------------

#define SC_VERSION ((USHORT)251)

//STRIP001 TYPEINIT1(ScTpCalcItem, SfxPoolItem);

//------------------------------------------------------------------------

//! these functions should be moved to some header file
//STRIP001 inline long TwipsToHMM(long nTwips)  { return (nTwips * 127 + 36) / 72; }
inline long HMMToTwips(long nHMM)   { return (nHMM * 72 + 63) / 127; }

//STRIP001 inline long TwipsToEvenHMM(long nTwips)  { return ( (nTwips * 127 + 72) / 144 ) * 2; }

//------------------------------------------------------------------------

/*N*/ USHORT lcl_GetDefaultTabDist()
/*N*/ {
/*N*/   if ( ScOptionsUtil::IsMetricSystem() )
/*N*/       return 709;                 // 1,25 cm
/*N*/   else
/*N*/       return 720;                 // 1/2"
/*N*/ }

//========================================================================
//      ScDocOptions - Dokument-Optionen
//========================================================================

/*N*/ ScDocOptions::ScDocOptions()
/*N*/ {
/*N*/   ResetDocOptions();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScDocOptions::ScDocOptions( const ScDocOptions& rCpy )
/*N*/       :   bIsIgnoreCase( rCpy.bIsIgnoreCase ),
/*N*/           bIsIter( rCpy.bIsIter ),
/*N*/           nIterCount( rCpy.nIterCount ),
/*N*/           fIterEps( rCpy.fIterEps ),
/*N*/           nPrecStandardFormat( rCpy.nPrecStandardFormat ),
/*N*/           nDay( rCpy.nDay ),
/*N*/           nMonth( rCpy.nMonth ),
/*N*/           nYear( rCpy.nYear ),
/*N*/           nYear2000( rCpy.nYear2000 ),
/*N*/           nTabDistance( rCpy.nTabDistance ),
/*N*/           bCalcAsShown( rCpy.bCalcAsShown ),
/*N*/           bMatchWholeCell( rCpy.bMatchWholeCell ),
/*N*/           bDoAutoSpell( rCpy.bDoAutoSpell ),
/*N*/             bLookUpColRowNames( rCpy.bLookUpColRowNames ),
/*N*/             bFormulaRegexEnabled( rCpy.bFormulaRegexEnabled )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScDocOptions::~ScDocOptions()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocOptions::Save(SvStream& rStream, BOOL bConfig) const
/*N*/ {
/*N*/   ScWriteHeader aHdr( rStream, 28 );
/*N*/
/*N*/   rStream << bIsIgnoreCase;
/*N*/   rStream << bIsIter;
/*N*/   rStream << nIterCount;
/*N*/   rStream << fIterEps;
/*N*/   rStream << nPrecStandardFormat;
/*N*/   rStream << nDay;
/*N*/   rStream << nMonth;
/*N*/   rStream << nYear;
/*N*/   rStream << nTabDistance;
/*N*/   rStream << bCalcAsShown;
/*N*/   rStream << bMatchWholeCell;
/*N*/   rStream << bDoAutoSpell;
/*N*/   rStream << bLookUpColRowNames;
/*N*/
/*N*/   if ( bConfig || rStream.GetVersion() > SOFFICE_FILEFORMAT_40 )      // nicht bei 4.0 Export
/*N*/   {
/*N*/       if ( !bConfig && 1901 <= nYear2000 && nYear2000 <= 1999 )
/*N*/       {   // fuer SO5 auf altes Format zweistellig abbilden
/*N*/           rStream << (USHORT) (nYear2000 - 1901);
/*N*/       }
/*N*/       else
/*N*/       {   // neues Format vierstellig, beliebiges Jahrhundert
/*N*/           // erzeugt in SO5 vor src513e ein Warning beim Laden
/*N*/           rStream << (USHORT) 29;     // Dummy, alter SO5 Default
/*N*/           rStream << nYear2000;       // echter Wert
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocOptions::Load(SvStream& rStream)
/*N*/ {
/*N*/   ScReadHeader aHdr( rStream );
/*N*/
/*N*/   rStream >> bIsIgnoreCase;
/*N*/   rStream >> bIsIter;
/*N*/   rStream >> nIterCount;
/*N*/   rStream >> fIterEps;
/*N*/   rStream >> nPrecStandardFormat;
/*N*/   rStream >> nDay;
/*N*/   rStream >> nMonth;
/*N*/   rStream >> nYear;
/*N*/   if ( aHdr.BytesLeft() )
/*N*/       rStream >> nTabDistance;
/*N*/   else
/*?*/       nTabDistance = lcl_GetDefaultTabDist();
/*N*/   if ( aHdr.BytesLeft() )
/*N*/       rStream >> bCalcAsShown;
/*N*/   else
/*N*/       bCalcAsShown = FALSE;
/*N*/   if ( aHdr.BytesLeft() )
/*N*/       rStream >> bMatchWholeCell;
/*N*/   else
/*N*/       bMatchWholeCell = FALSE;
/*N*/   if ( aHdr.BytesLeft() )
/*N*/       rStream >> bDoAutoSpell;
/*N*/   else
/*N*/       bDoAutoSpell = FALSE;
/*N*/   if ( aHdr.BytesLeft() )
/*N*/       rStream >> bLookUpColRowNames;
/*N*/   else
/*N*/       bLookUpColRowNames = TRUE;
/*N*/   if ( aHdr.BytesLeft() )
/*N*/   {
/*N*/       rStream >> nYear2000;       // SO5 ab 24.06.98
/*N*/       // SO51 ab src513e
/*N*/       if ( aHdr.BytesLeft() )
/*N*/           rStream >> nYear2000;   // der echte Wert
/*N*/       else
/*N*/           nYear2000 += 1901;      // altes zweistelliges auf neues vierstelliges
/*N*/   }
/*N*/   else
/*N*/       nYear2000 = 18 + 1901;      // alter Wert vor SO5
/*N*/ }

/*N*/ void ScDocOptions::ResetDocOptions()
/*N*/ {
/*N*/   bIsIgnoreCase       = FALSE;
/*N*/   bIsIter             = FALSE;
/*N*/   nIterCount          = 100;
/*N*/   fIterEps            = 1.0E-3;
/*N*/   nPrecStandardFormat = 2;
/*N*/   nDay                = 30;
/*N*/   nMonth              = 12;
/*N*/   nYear               = 1899;
/*N*/   nYear2000           = SvNumberFormatter::GetYear2000Default();
/*N*/   nTabDistance        = lcl_GetDefaultTabDist();
/*N*/   bCalcAsShown        = FALSE;
/*N*/   bMatchWholeCell     = TRUE;
/*N*/   bDoAutoSpell        = FALSE;
/*N*/   bLookUpColRowNames  = TRUE;
/*N*/     bFormulaRegexEnabled= TRUE;
/*N*/ }

//========================================================================
//      ScTpCalcItem - Daten fuer die CalcOptions-TabPage
//========================================================================

//STRIP001 ScTpCalcItem::ScTpCalcItem( USHORT nWhich ) : SfxPoolItem( nWhich )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScTpCalcItem::ScTpCalcItem( USHORT nWhich, const ScDocOptions& rOpt )
//STRIP001  :   SfxPoolItem ( nWhich ),
//STRIP001      theOptions  ( rOpt )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScTpCalcItem::ScTpCalcItem( const ScTpCalcItem& rItem )
//STRIP001  :   SfxPoolItem ( rItem ),
//STRIP001      theOptions  ( rItem.theOptions )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 __EXPORT ScTpCalcItem::~ScTpCalcItem()
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScTpCalcItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("ScTpCalcItem") );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScTpCalcItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScTpCalcItem& rPItem = (const ScTpCalcItem&)rItem;
//STRIP001
//STRIP001  return ( theOptions == rPItem.theOptions );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScTpCalcItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScTpCalcItem( *this );
//STRIP001 }

//==================================================================
//  Config Item containing document options
//==================================================================

#define CFGPATH_CALC        "Office.Calc/Calculate"

#define SCCALCOPT_ITER_ITER         0
#define SCCALCOPT_ITER_STEPS        1
#define SCCALCOPT_ITER_MINCHG       2
#define SCCALCOPT_DATE_DAY          3
#define SCCALCOPT_DATE_MONTH        4
#define SCCALCOPT_DATE_YEAR         5
#define SCCALCOPT_DECIMALS          6
#define SCCALCOPT_CASESENSITIVE     7
#define SCCALCOPT_PRECISION         8
#define SCCALCOPT_SEARCHCRIT        9
#define SCCALCOPT_FINDLABEL         10
#define SCCALCOPT_REGEX             11
#define SCCALCOPT_COUNT             12

#define CFGPATH_DOCLAYOUT   "Office.Calc/Layout/Other"

#define SCDOCLAYOUTOPT_TABSTOP      0
#define SCDOCLAYOUTOPT_COUNT        1


/*N*/ Sequence<OUString> ScDocCfg::GetCalcPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "IterativeReference/Iteration",     // SCCALCOPT_ITER_ITER
/*N*/       "IterativeReference/Steps",         // SCCALCOPT_ITER_STEPS
/*N*/       "IterativeReference/MinimumChange", // SCCALCOPT_ITER_MINCHG
/*N*/       "Other/Date/DD",                    // SCCALCOPT_DATE_DAY
/*N*/       "Other/Date/MM",                    // SCCALCOPT_DATE_MONTH
/*N*/       "Other/Date/YY",                    // SCCALCOPT_DATE_YEAR
/*N*/       "Other/DecimalPlaces",              // SCCALCOPT_DECIMALS
/*N*/       "Other/CaseSensitive",              // SCCALCOPT_CASESENSITIVE
/*N*/       "Other/Precision",                  // SCCALCOPT_PRECISION
/*N*/       "Other/SearchCriteria",             // SCCALCOPT_SEARCHCRIT
/*N*/         "Other/FindLabel",                  // SCCALCOPT_FINDLABEL
/*N*/         "Other/RegularExpressions"          // SCCALCOPT_REGEX
/*N*/   };
/*N*/   Sequence<OUString> aNames(SCCALCOPT_COUNT);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < SCCALCOPT_COUNT; i++)
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/
/*N*/   return aNames;
/*N*/ }

/*N*/ Sequence<OUString> ScDocCfg::GetLayoutPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "TabStop/NonMetric"         // SCDOCLAYOUTOPT_TABSTOP
/*N*/   };
/*N*/   Sequence<OUString> aNames(SCDOCLAYOUTOPT_COUNT);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < SCDOCLAYOUTOPT_COUNT; i++)
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/
/*N*/   //  adjust for metric system
/*N*/   if (ScOptionsUtil::IsMetricSystem())
/*N*/       pNames[SCDOCLAYOUTOPT_TABSTOP] = OUString::createFromAscii( "TabStop/Metric" );
/*N*/
/*N*/   return aNames;
/*N*/ }

/*N*/ ScDocCfg::ScDocCfg() :
/*N*/   aCalcItem( OUString::createFromAscii( CFGPATH_CALC ) ),
/*N*/   aLayoutItem( OUString::createFromAscii( CFGPATH_DOCLAYOUT ) )
/*N*/ {
/*N*/   sal_Int32 nIntVal;
/*N*/   double fDoubleVal;
/*N*/
/*N*/   Sequence<OUString> aNames;
/*N*/   Sequence<Any> aValues;
/*N*/   const Any* pValues = NULL;
/*N*/
/*N*/   USHORT nDateDay, nDateMonth, nDateYear;
/*N*/   GetDate( nDateDay, nDateMonth, nDateYear );
/*N*/
/*N*/   aNames = GetCalcPropertyNames();
/*N*/   aValues = aCalcItem.GetProperties(aNames);
/*N*/   aCalcItem.EnableNotification(aNames);
/*N*/   pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           DBG_ASSERT(pValues[nProp].hasValue(), "property value missing")
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case SCCALCOPT_ITER_ITER:
/*N*/                       SetIter( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCCALCOPT_ITER_STEPS:
/*N*/                       if (pValues[nProp] >>= nIntVal) SetIterCount( (USHORT) nIntVal );
/*N*/                       break;
/*N*/                   case SCCALCOPT_ITER_MINCHG:
/*N*/                       if (pValues[nProp] >>= fDoubleVal) SetIterEps( fDoubleVal );
/*N*/                       break;
/*N*/                   case SCCALCOPT_DATE_DAY:
/*N*/                       if (pValues[nProp] >>= nIntVal) nDateDay = (USHORT) nIntVal;
/*N*/                       break;
/*N*/                   case SCCALCOPT_DATE_MONTH:
/*N*/                       if (pValues[nProp] >>= nIntVal) nDateMonth = (USHORT) nIntVal;
/*N*/                       break;
/*N*/                   case SCCALCOPT_DATE_YEAR:
/*N*/                       if (pValues[nProp] >>= nIntVal) nDateYear = (USHORT) nIntVal;
/*N*/                       break;
/*N*/                   case SCCALCOPT_DECIMALS:
/*N*/                       if (pValues[nProp] >>= nIntVal) SetStdPrecision( (USHORT) nIntVal );
/*N*/                       break;
/*N*/                   case SCCALCOPT_CASESENSITIVE:
/*N*/                       // content is reversed
/*N*/                       SetIgnoreCase( !ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCCALCOPT_PRECISION:
/*N*/                       SetCalcAsShown( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCCALCOPT_SEARCHCRIT:
/*N*/                       SetMatchWholeCell( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCCALCOPT_FINDLABEL:
/*N*/                       SetLookUpColRowNames( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                     case SCCALCOPT_REGEX :
/*N*/                         SetFormulaRegexEnabled( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                         break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   aCalcItem.SetCommitLink( LINK( this, ScDocCfg, CalcCommitHdl ) );
/*N*/
/*N*/   SetDate( nDateDay, nDateMonth, nDateYear );
/*N*/
/*N*/   aNames = GetLayoutPropertyNames();
/*N*/   aValues = aLayoutItem.GetProperties(aNames);
/*N*/   aLayoutItem.EnableNotification(aNames);
/*N*/   pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           DBG_ASSERT(pValues[nProp].hasValue(), "property value missing")
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case SCDOCLAYOUTOPT_TABSTOP:
/*N*/                       // TabDistance in ScDocOptions is in twips
/*N*/                       if (pValues[nProp] >>= nIntVal)
/*N*/                           SetTabDistance( (USHORT) HMMToTwips( nIntVal ) );
/*N*/                       break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   aLayoutItem.SetCommitLink( LINK( this, ScDocCfg, LayoutCommitHdl ) );
/*N*/ }

/*N*/ IMPL_LINK( ScDocCfg, CalcCommitHdl, void *, EMPTYARG )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 Sequence<OUString> aNames = GetCalcPropertyNames();
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  USHORT nDateDay, nDateMonth, nDateYear;
//STRIP001  GetDate( nDateDay, nDateMonth, nDateYear );
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case SCCALCOPT_ITER_ITER:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], IsIter() );
//STRIP001              break;
//STRIP001          case SCCALCOPT_ITER_STEPS:
//STRIP001              pValues[nProp] <<= (sal_Int32) GetIterCount();
//STRIP001              break;
//STRIP001          case SCCALCOPT_ITER_MINCHG:
//STRIP001              pValues[nProp] <<= (double) GetIterEps();
//STRIP001              break;
//STRIP001          case SCCALCOPT_DATE_DAY:
//STRIP001              pValues[nProp] <<= (sal_Int32) nDateDay;
//STRIP001              break;
//STRIP001          case SCCALCOPT_DATE_MONTH:
//STRIP001              pValues[nProp] <<= (sal_Int32) nDateMonth;
//STRIP001              break;
//STRIP001          case SCCALCOPT_DATE_YEAR:
//STRIP001              pValues[nProp] <<= (sal_Int32) nDateYear;
//STRIP001              break;
//STRIP001          case SCCALCOPT_DECIMALS:
//STRIP001              pValues[nProp] <<= (sal_Int32) GetStdPrecision();
//STRIP001              break;
//STRIP001          case SCCALCOPT_CASESENSITIVE:
//STRIP001              // content is reversed
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], !IsIgnoreCase() );
//STRIP001              break;
//STRIP001          case SCCALCOPT_PRECISION:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], IsCalcAsShown() );
//STRIP001              break;
//STRIP001          case SCCALCOPT_SEARCHCRIT:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], IsMatchWholeCell() );
//STRIP001              break;
//STRIP001          case SCCALCOPT_FINDLABEL:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], IsLookUpColRowNames() );
//STRIP001              break;
//STRIP001             case SCCALCOPT_REGEX :
//STRIP001                 ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], IsFormulaRegexEnabled() );
//STRIP001      }
//STRIP001  }
//STRIP001  aCalcItem.PutProperties(aNames, aValues);
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK( ScDocCfg, LayoutCommitHdl, void *, EMPTYARG )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 Sequence<OUString> aNames = GetLayoutPropertyNames();
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case SCDOCLAYOUTOPT_TABSTOP:
//STRIP001              //  TabDistance in ScDocOptions is in twips
//STRIP001              //  use only even numbers, so defaults don't get changed
//STRIP001              //  by modifying other settings in the same config item
//STRIP001              pValues[nProp] <<= (sal_Int32) TwipsToEvenHMM( GetTabDistance() );
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  aLayoutItem.PutProperties(aNames, aValues);
//STRIP001
/*N*/   return 0;
/*N*/ }


//STRIP001 void ScDocCfg::SetOptions( const ScDocOptions& rNew )
//STRIP001 {
//STRIP001  *(ScDocOptions*)this = rNew;
//STRIP001
//STRIP001  aCalcItem.SetModified();
//STRIP001  aLayoutItem.SetModified();
//STRIP001 }


}
