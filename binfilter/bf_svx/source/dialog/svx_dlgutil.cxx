/*************************************************************************
 *
 *  $RCSfile: svx_dlgutil.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:21:42 $
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
 *  WITHOUT WARRUNTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRUNTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
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

// auto strip #ifndef _SHL_HXX
// auto strip #include <tools/shl.hxx>
// auto strip #endif
// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif

// auto strip #ifndef _UNO_LINGU_HXX
// auto strip #include <unolingu.hxx>
// auto strip #endif

// auto strip #include <svtools/itemset.hxx>
// auto strip #include <bf_sfx2/viewfrm.hxx>
// auto strip #include <bf_sfx2/objsh.hxx>

#pragma hdrstop

#include "dialogs.hrc"

#include "dlgutil.hxx"
// auto strip #include "dialmgr.hxx"
// auto strip #include "langtab.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

//STRIP001 String GetLanguageString( LanguageType eType )
//STRIP001 {
//STRIP001  static const SvxLanguageTable aLangTable;
//STRIP001  return aLangTable.GetString( eType );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 String GetDicInfoStr( const String& rName, const USHORT nLang, const BOOL bNeg )
//STRIP001 {
//STRIP001  INetURLObject aURLObj;
//STRIP001  aURLObj.SetSmartProtocol( INET_PROT_FILE );
//STRIP001  aURLObj.SetSmartURL( rName, INetURLObject::ENCODE_ALL );
//STRIP001  String aTmp( aURLObj.GetBase() );
//STRIP001  aTmp += sal_Unicode( ' ' );
//STRIP001
//STRIP001  if ( bNeg )
//STRIP001  {
//STRIP001      sal_Char const sTmp[] = " (-) ";
//STRIP001      aTmp.AppendAscii( sTmp );
//STRIP001  }
//STRIP001
//STRIP001  if ( LANGUAGE_NONE == nLang )
//STRIP001      aTmp += String( ResId( RID_SVXSTR_LANGUAGE_ALL, DIALOG_MGR() ) );
//STRIP001  else
//STRIP001  {
//STRIP001      aTmp += sal_Unicode( '[' );
//STRIP001      aTmp += ::GetLanguageString( (LanguageType)nLang );
//STRIP001      aTmp += sal_Unicode( ']' );
//STRIP001  }
//STRIP001
//STRIP001  return aTmp;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SetFieldUnit( MetricField& rField, FieldUnit eUnit, BOOL bAll )
//STRIP001 {
//STRIP001  long nFirst = rField.Denormalize( rField.GetFirst( FUNIT_TWIP ) );
//STRIP001  long nLast = rField.Denormalize( rField.GetLast( FUNIT_TWIP ) );
//STRIP001  long nMin = rField.Denormalize( rField.GetMin( FUNIT_TWIP ) );
//STRIP001  long nMax = rField.Denormalize( rField.GetMax( FUNIT_TWIP ) );
//STRIP001
//STRIP001  if ( !bAll )
//STRIP001  {
//STRIP001      switch ( eUnit )
//STRIP001      {
//STRIP001          case FUNIT_M:
//STRIP001          case FUNIT_KM:
//STRIP001              eUnit = FUNIT_CM;
//STRIP001              break;
//STRIP001
//STRIP001          case FUNIT_FOOT:
//STRIP001          case FUNIT_MILE:
//STRIP001              eUnit = FUNIT_INCH;
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  rField.SetUnit( eUnit );
//STRIP001  switch( eUnit )
//STRIP001  {
//STRIP001      case FUNIT_MM:
//STRIP001          rField.SetSpinSize( 50 );
//STRIP001          break;
//STRIP001
//STRIP001      case FUNIT_INCH:
//STRIP001          rField.SetSpinSize( 2 );
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          rField.SetSpinSize( 10 );
//STRIP001  }
//STRIP001
//STRIP001  if ( FUNIT_POINT == eUnit && rField.GetDecimalDigits() > 1 )
//STRIP001      rField.SetDecimalDigits( 1 );
//STRIP001  else
//STRIP001      rField.SetDecimalDigits( 2 );
//STRIP001
//STRIP001  if ( !bAll )
//STRIP001  {
//STRIP001      rField.SetFirst( rField.Normalize( nFirst ), FUNIT_TWIP );
//STRIP001      rField.SetLast( rField.Normalize( nLast ), FUNIT_TWIP );
//STRIP001      rField.SetMin( rField.Normalize( nMin ), FUNIT_TWIP );
//STRIP001      rField.SetMax( rField.Normalize( nMax ), FUNIT_TWIP );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SetFieldUnit( MetricBox& rBox, FieldUnit eUnit, BOOL bAll )
//STRIP001 {
//STRIP001  long nMin = rBox.Denormalize( rBox.GetMin( FUNIT_TWIP ) );
//STRIP001  long nMax = rBox.Denormalize( rBox.GetMax( FUNIT_TWIP ) );
//STRIP001
//STRIP001  if ( !bAll )
//STRIP001  {
//STRIP001      switch ( eUnit )
//STRIP001      {
//STRIP001          case FUNIT_M:
//STRIP001          case FUNIT_KM:
//STRIP001              eUnit = FUNIT_CM;
//STRIP001              break;
//STRIP001
//STRIP001          case FUNIT_FOOT:
//STRIP001          case FUNIT_MILE:
//STRIP001              eUnit = FUNIT_INCH;
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  rBox.SetUnit( eUnit );
//STRIP001
//STRIP001  if ( FUNIT_POINT == eUnit && rBox.GetDecimalDigits() > 1 )
//STRIP001      rBox.SetDecimalDigits( 1 );
//STRIP001  else
//STRIP001      rBox.SetDecimalDigits( 2 );
//STRIP001
//STRIP001  if ( !bAll )
//STRIP001  {
//STRIP001      rBox.SetMin( rBox.Normalize( nMin ), FUNIT_TWIP );
//STRIP001      rBox.SetMax( rBox.Normalize( nMax ), FUNIT_TWIP );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ FieldUnit GetModuleFieldUnit( const SfxItemSet* pSet )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   FieldUnit eUnit = FUNIT_INCH;
//STRIP001  const SfxPoolItem* pItem = NULL;
//STRIP001  if ( pSet && SFX_ITEM_SET == pSet->GetItemState( SID_ATTR_METRIC, FALSE, &pItem ) )
//STRIP001      eUnit = (FieldUnit)( (const SfxUInt16Item*)pItem )->GetValue();
//STRIP001  else
//STRIP001  {
//STRIP001      SfxViewFrame* pFrame = SfxViewFrame::Current();
//STRIP001      SfxObjectShell* pSh = NULL;
//STRIP001      if ( pFrame )
//STRIP001          pSh = pFrame->GetObjectShell();
//STRIP001         if ( pSh )  // #93209# the object shell is not always available during reload
//STRIP001         {
//STRIP001          SfxModule* pModule = pSh->GetModule();
//STRIP001          if ( pModule )
//STRIP001          {
//STRIP001              const SfxPoolItem* pItem = pModule->GetItem( SID_ATTR_METRIC );
//STRIP001              if ( pItem )
//STRIP001                  eUnit = (FieldUnit)( (SfxUInt16Item*)pItem )->GetValue();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              DBG_ERRORFILE( "GetModuleFieldUnit(): no module found" );
//STRIP001          }
//STRIP001         }
//STRIP001  }
/*N*/   return eUnit;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SetMetricValue( MetricField& rField, long nCoreValue, SfxMapUnit eUnit )
//STRIP001 {
//STRIP001  long nVal = OutputDevice::LogicToLogic( nCoreValue, (MapUnit)eUnit, MAP_100TH_MM );
//STRIP001  nVal = rField.Normalize( nVal );
//STRIP001  rField.SetValue( nVal, FUNIT_100TH_MM );
//STRIP001
//STRIP001 /*
//STRIP001  if ( SFX_MAPUNIT_100TH_MM == eUnit )
//STRIP001  {
//STRIP001      FieldUnit eFUnit = ( (MetricField&)rField ).GetUnit();
//STRIP001      USHORT nDigits = rField.GetDecimalDigits();
//STRIP001
//STRIP001      if ( FUNIT_MM == eFUnit )
//STRIP001      {
//STRIP001          if ( 0 == nDigits )
//STRIP001              lCoreValue /= 100;
//STRIP001          else if ( 1 == nDigits )
//STRIP001              lCoreValue /= 10;
//STRIP001          else if ( nDigits > 2 )
//STRIP001          {
//STRIP001              DBG_ERROR( "too much decimal digits" );
//STRIP001              return;
//STRIP001          }
//STRIP001          rField.SetValue( lCoreValue, FUNIT_MM );
//STRIP001          return;
//STRIP001      }
//STRIP001      else if ( FUNIT_CM == eFUnit )
//STRIP001      {
//STRIP001          if ( 0 == nDigits )
//STRIP001              lCoreValue /= 1000;
//STRIP001          else if ( 1 == nDigits )
//STRIP001              lCoreValue /= 100;
//STRIP001          else if ( 2 == nDigits )
//STRIP001              lCoreValue /= 10;
//STRIP001          else if ( nDigits > 3 )
//STRIP001          {
//STRIP001              DBG_ERROR( "too much decimal digits" );
//STRIP001              return;
//STRIP001          }
//STRIP001          rField.SetValue( lCoreValue, FUNIT_CM );
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001  rField.SetValue( rField.Normalize(
//STRIP001      ConvertValueToUnit( lCoreValue, eUnit ) ), MapToFieldUnit( eUnit ) );
//STRIP001 */
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long GetCoreValue( const MetricField& rField, SfxMapUnit eUnit )
//STRIP001 {
//STRIP001  long nVal = rField.GetValue( FUNIT_100TH_MM );
//STRIP001  long nUnitVal = OutputDevice::LogicToLogic( nVal, MAP_100TH_MM, (MapUnit)eUnit );
//STRIP001  nUnitVal = rField.Denormalize( nUnitVal );
//STRIP001  return nUnitVal;
//STRIP001
//STRIP001 /*
//STRIP001  long nRet = rField.GetValue( MapToFieldUnit( eUnit ) );
//STRIP001  FieldUnit eFUnit = ( (MetricField&)rField ).GetUnit();
//STRIP001  USHORT nDigits = rField.GetDecimalDigits();
//STRIP001  DBG_ASSERT( nDigits <= 2, "decimal digits > 2!" );
//STRIP001
//STRIP001  switch ( eUnit )
//STRIP001  {
//STRIP001      case SFX_MAPUNIT_100TH_MM:
//STRIP001      {
//STRIP001          if ( 2 == nDigits )
//STRIP001              return nRet;
//STRIP001          else if ( 1 == nDigits )
//STRIP001              return nRet * 10;
//STRIP001          else
//STRIP001              return nRet * 100;
//STRIP001      }
//STRIP001
//STRIP001      case SFX_MAPUNIT_TWIP:
//STRIP001      {
//STRIP001          if ( 2 == nDigits )
//STRIP001          {
//STRIP001              long nMod = 100;
//STRIP001              long nTmp = nRet % nMod;
//STRIP001
//STRIP001              if ( nTmp >= 49 )
//STRIP001                  nRet += 100 - nTmp;
//STRIP001              return nRet / 100;
//STRIP001          }
//STRIP001          else if ( 1 == nDigits )
//STRIP001          {
//STRIP001              long nMod = 10;
//STRIP001              long nTmp = nRet % nMod;
//STRIP001
//STRIP001              if ( nTmp >= 4 )
//STRIP001                  nRet += 10 - nTmp;
//STRIP001              return nRet / 10;
//STRIP001          }
//STRIP001          else
//STRIP001              return nRet;
//STRIP001      }
//STRIP001
//STRIP001      default:
//STRIP001          DBG_ERROR( "this unit is not implemented" );
//STRIP001          return 0;
//STRIP001  }
//STRIP001 */
//STRIP001
//STRIP001 /*!!!
//STRIP001  return ConvertValueToMap( rField.Denormalize(
//STRIP001      rField.GetValue( MapToFieldUnit( eUnit ) ) ), eUnit );
//STRIP001 */
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ long CalcToUnit( float nIn, SfxMapUnit eUnit )
/*N*/ {
/*N*/   // nIn ist in Points
/*N*/
/*N*/   DBG_ASSERT( eUnit == SFX_MAPUNIT_TWIP       ||
/*N*/               eUnit == SFX_MAPUNIT_100TH_MM   ||
/*N*/               eUnit == SFX_MAPUNIT_10TH_MM    ||
/*N*/               eUnit == SFX_MAPUNIT_MM         ||
/*N*/               eUnit == SFX_MAPUNIT_CM, "this unit is not implemented" );
/*N*/
/*N*/   float nTmp = nIn;
/*N*/
/*N*/   if ( SFX_MAPUNIT_TWIP != eUnit )
/*N*/       nTmp = nIn * 10 / 567;
/*N*/
/*N*/   switch ( eUnit )
/*N*/   {
/*N*/       case SFX_MAPUNIT_100TH_MM:  nTmp *= 100; break;
/*?*/       case SFX_MAPUNIT_10TH_MM:   nTmp *= 10;  break;
/*?*/       case SFX_MAPUNIT_MM:                     break;
/*?*/       case SFX_MAPUNIT_CM:        nTmp /= 10;  break;
/*N*/   }
/*N*/
/*N*/   nTmp *= 20;
/*N*/   long nRet = (long)nTmp;
/*N*/   return nRet;
/*N*/ //!   return (long)(nTmp * 20);
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ long ItemToControl( long nIn, SfxMapUnit eItem, SfxFieldUnit eCtrl )
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001     long nOut = 0;
//STRIP001
//STRIP001  switch ( eItem )
//STRIP001  {
//STRIP001      case SFX_MAPUNIT_100TH_MM:
//STRIP001      case SFX_MAPUNIT_10TH_MM:
//STRIP001      case SFX_MAPUNIT_MM:
//STRIP001      {
//STRIP001          if ( eItem == SFX_MAPUNIT_10TH_MM )
//STRIP001              nIn /= 10;
//STRIP001          else if ( eItem == SFX_MAPUNIT_100TH_MM )
//STRIP001              nIn /= 100;
//STRIP001          nOut = TransformMetric( nIn, FUNIT_MM, (FieldUnit)eCtrl );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_CM:
//STRIP001      {
//STRIP001          nOut = TransformMetric( nIn, FUNIT_CM, (FieldUnit)eCtrl );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_1000TH_INCH:
//STRIP001      case SFX_MAPUNIT_100TH_INCH:
//STRIP001      case SFX_MAPUNIT_10TH_INCH:
//STRIP001      case SFX_MAPUNIT_INCH:
//STRIP001      {
//STRIP001          if ( eItem == SFX_MAPUNIT_10TH_INCH )
//STRIP001              nIn /= 10;
//STRIP001          else if ( eItem == SFX_MAPUNIT_100TH_INCH )
//STRIP001              nIn /= 100;
//STRIP001          else if ( eItem == SFX_MAPUNIT_1000TH_INCH )
//STRIP001              nIn /= 1000;
//STRIP001          nOut = TransformMetric( nIn, FUNIT_INCH, (FieldUnit)eCtrl );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_POINT:
//STRIP001      {
//STRIP001          nOut = TransformMetric( nIn, FUNIT_POINT, (FieldUnit)eCtrl );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_TWIP:
//STRIP001      {
//STRIP001          nOut = TransformMetric( nIn, FUNIT_TWIP, (FieldUnit)eCtrl );
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001  return nOut;
/*?*/ }

// -----------------------------------------------------------------------

//STRIP001 long ControlToItem( long nIn, SfxFieldUnit eCtrl, SfxMapUnit eItem )
//STRIP001 {
//STRIP001  return ItemToControl( nIn, eItem, eCtrl );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 FieldUnit MapToFieldUnit( const SfxMapUnit eUnit )
//STRIP001 {
//STRIP001  switch ( eUnit )
//STRIP001  {
//STRIP001      case SFX_MAPUNIT_100TH_MM:
//STRIP001      case SFX_MAPUNIT_10TH_MM:
//STRIP001      case SFX_MAPUNIT_MM:
//STRIP001          return FUNIT_MM;
//STRIP001
//STRIP001      case SFX_MAPUNIT_CM:
//STRIP001          return FUNIT_CM;
//STRIP001
//STRIP001      case SFX_MAPUNIT_1000TH_INCH:
//STRIP001      case SFX_MAPUNIT_100TH_INCH:
//STRIP001      case SFX_MAPUNIT_10TH_INCH:
//STRIP001      case SFX_MAPUNIT_INCH:
//STRIP001          return FUNIT_INCH;
//STRIP001
//STRIP001      case SFX_MAPUNIT_POINT:
//STRIP001          return FUNIT_POINT;
//STRIP001
//STRIP001      case SFX_MAPUNIT_TWIP:
//STRIP001          return FUNIT_TWIP;
//STRIP001  }
//STRIP001  return FUNIT_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 MapUnit FieldToMapUnit( const SfxFieldUnit eUnit )
//STRIP001 {
//STRIP001  return MAP_APPFONT;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long ConvertValueToMap( long nVal, SfxMapUnit eUnit )
//STRIP001 {
//STRIP001  long nNew = nVal;
//STRIP001
//STRIP001  switch ( eUnit )
//STRIP001  {
//STRIP001      case SFX_MAPUNIT_10TH_MM:
//STRIP001      case SFX_MAPUNIT_10TH_INCH:
//STRIP001          nNew *= 10;
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_100TH_MM:
//STRIP001      case SFX_MAPUNIT_100TH_INCH:
//STRIP001          nNew *= 100;
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_1000TH_INCH:
//STRIP001          nNew *= 1000;
//STRIP001  }
//STRIP001  return nNew;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long ConvertValueToUnit( long nVal, SfxMapUnit eUnit )
//STRIP001 {
//STRIP001  long nNew = nVal;
//STRIP001
//STRIP001  switch ( eUnit )
//STRIP001  {
//STRIP001      case SFX_MAPUNIT_10TH_MM:
//STRIP001      case SFX_MAPUNIT_10TH_INCH:
//STRIP001          nNew /= 10;
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_100TH_MM:
//STRIP001      case SFX_MAPUNIT_100TH_INCH:
//STRIP001          nNew /= 100;
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_MAPUNIT_1000TH_INCH:
//STRIP001          nNew /= 1000;
//STRIP001  }
//STRIP001  return nNew;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ long CalcToPoint( long nIn, SfxMapUnit eUnit, USHORT nFaktor )
/*N*/ {
/*N*/   DBG_ASSERT( eUnit == SFX_MAPUNIT_TWIP       ||
/*N*/               eUnit == SFX_MAPUNIT_100TH_MM   ||
/*N*/               eUnit == SFX_MAPUNIT_10TH_MM    ||
/*N*/               eUnit == SFX_MAPUNIT_MM         ||
/*N*/               eUnit == SFX_MAPUNIT_CM, "this unit is not implemented" );
/*N*/
/*N*/   long nRet = 0;
/*N*/
/*N*/   if ( SFX_MAPUNIT_TWIP == eUnit )
/*N*/       nRet = nIn;
/*N*/   else
/*N*/       nRet = nIn * 567;
/*N*/
/*N*/   switch ( eUnit )
/*N*/   {
/*N*/       case SFX_MAPUNIT_100TH_MM:  nRet /= 100; break;
/*?*/       case SFX_MAPUNIT_10TH_MM:   nRet /= 10;  break;
/*?*/       case SFX_MAPUNIT_MM:                     break;
/*?*/       case SFX_MAPUNIT_CM:        nRet *= 10;  break;
/*N*/   }
/*N*/
/*N*/   // ggf. aufrunden
/*N*/   if ( SFX_MAPUNIT_TWIP != eUnit )
/*N*/   {
/*N*/       long nMod = 10;
/*N*/       long nTmp = nRet % nMod;
/*N*/
/*N*/       if ( nTmp >= 4 )
/*N*/           nRet += 10 - nTmp;
/*N*/       nRet /= 10;
/*N*/   }
/*N*/   return nRet * nFaktor / 20;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 long CMToTwips( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 567 ) && nIn >= ( LONG_MIN / 567 ) )
//STRIP001      nRet = nIn * 567;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long MMToTwips( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 567 ) && nIn >= ( LONG_MIN / 567 ) )
//STRIP001      nRet = nIn * 567 / 10;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long InchToTwips( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 1440 ) && nIn >= ( LONG_MIN / 1440 ) )
//STRIP001      nRet = nIn * 1440;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PointToTwips( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 20 ) && nIn >= ( LONG_MIN / 20 ) )
//STRIP001      nRet = nIn * 20;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PicaToTwips( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 240 ) && nIn >= ( LONG_MIN / 240 ) )
//STRIP001      nRet = nIn * 240;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long TwipsToCM( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 567;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long InchToCM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 254 ) && nIn >= ( LONG_MIN / 254 ) )
//STRIP001      nRet = nIn * 254 / 100;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long MMToCM( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 10;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PointToCM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 20 ) && nIn >= ( LONG_MIN / 20 ) )
//STRIP001      nRet = nIn * 20 / 567;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PicaToCM( long nIn)
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 12 / 20 ) && nIn >= ( LONG_MIN / 12 / 20 ) )
//STRIP001      nRet = nIn * 12 * 20 / 567;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long TwipsToMM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 10 ) && nIn >= ( LONG_MIN / 10 ) )
//STRIP001      nRet = nIn * 10 / 566;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long CMToMM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 10 ) && nIn >= ( LONG_MIN / 10 ) )
//STRIP001      nRet = nIn * 10;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long InchToMM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 254 ) && nIn >= ( LONG_MIN / 254 ) )
//STRIP001      nRet = nIn * 254 / 10;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PointToMM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 200 ) && nIn >= ( LONG_MIN / 200 ) )
//STRIP001      nRet = nIn * 200 / 567;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PicaToMM( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 12 / 200 ) && nIn >= ( LONG_MIN / 12 / 200 ) )
//STRIP001      nRet = nIn * 12 * 200 / 567;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long TwipsToInch( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 1440;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long CMToInch( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 100 ) && nIn >= ( LONG_MIN / 100 ) )
//STRIP001      nRet = nIn * 100 / 254;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long MMToInch( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 10 ) && nIn >= ( LONG_MIN / 10 ) )
//STRIP001      nRet = nIn * 10 / 254;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PointToInch( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 72;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PicaToInch( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 6;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long TwipsToPoint( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 20;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long InchToPoint( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 72 ) && nIn >= ( LONG_MIN / 72 ) )
//STRIP001      nRet = nIn * 72;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long CMToPoint( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 567 ) && nIn >= ( LONG_MIN / 567 ) )
//STRIP001      nRet = nIn * 567 / 20;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long MMToPoint( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 567 ) && nIn >= ( LONG_MIN / 567 ) )
//STRIP001      nRet = nIn * 567 / 200;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PicaToPoint( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 12;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long TwipsToPica( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn / 240;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long InchToPica( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 6 ) && nIn >= ( LONG_MIN / 6 ) )
//STRIP001      nRet = nIn * 6;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long PointToPica( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 12 ) && nIn >= ( LONG_MIN / 12 ) )
//STRIP001      nRet = nIn * 12;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long CMToPica( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 567 ) && nIn >= ( LONG_MIN / 567 ) )
//STRIP001      nRet = nIn * 567 / 20 / 12;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long MMToPica( long nIn )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001  if ( nIn <= ( LONG_MAX / 567 ) && nIn >= ( LONG_MIN / 567 ) )
//STRIP001      nRet = nIn * 567 / 200 / 12;
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 long Nothing( long nIn )
//STRIP001 {
//STRIP001  long nRet = nIn;
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 FUNC_CONVERT ConvertTable[6][6] =
//STRIP001 {
//STRIP001 //  CM,          MM          INCH         POINT        PICAS=32     TWIPS
//STRIP001  Nothing,    CMToMM,     CMToInch,    CMToPoint,   CMToPica,    CMToTwips,
//STRIP001  MMToCM,     Nothing,    MMToInch,    MMToPoint,   MMToPica,    MMToTwips,
//STRIP001  InchToCM,   InchToMM,   Nothing,     InchToPoint, InchToPica,  InchToTwips,
//STRIP001  PointToCM,  PointToMM,  PointToInch, Nothing,     PointToPica, PointToTwips,
//STRIP001  PicaToCM,   PicaToMM,   PicaToInch,  PicaToPoint, Nothing,     PicaToTwips,
//STRIP001  TwipsToCM,  TwipsToMM,  TwipsToInch, TwipsToPoint,TwipsToPica, Nothing
//STRIP001 };

// -----------------------------------------------------------------------

//STRIP001 long TransformMetric( long nVal, FieldUnit aOld, FieldUnit aNew )
//STRIP001 {
//STRIP001  if ( aOld == FUNIT_NONE   || aNew == FUNIT_NONE ||
//STRIP001       aOld == FUNIT_CUSTOM || aNew == FUNIT_CUSTOM )
//STRIP001  {
//STRIP001      return nVal;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nOld = 0;
//STRIP001  USHORT nNew = 0;
//STRIP001
//STRIP001  switch ( aOld )
//STRIP001  {
//STRIP001      case FUNIT_CM:
//STRIP001          nOld = 0; break;
//STRIP001      case FUNIT_MM:
//STRIP001          nOld = 1; break;
//STRIP001      case FUNIT_INCH:
//STRIP001          nOld = 2; break;
//STRIP001      case FUNIT_POINT:
//STRIP001          nOld = 3; break;
//STRIP001      case FUNIT_PICA:
//STRIP001          nOld = 4; break;
//STRIP001      case FUNIT_TWIP:
//STRIP001          nOld = 5; break;
//STRIP001  }
//STRIP001
//STRIP001  switch ( aNew )
//STRIP001  {
//STRIP001      case FUNIT_CM:
//STRIP001          nNew = 0; break;
//STRIP001      case FUNIT_MM:
//STRIP001          nNew = 1; break;
//STRIP001      case FUNIT_INCH:
//STRIP001          nNew = 2; break;
//STRIP001      case FUNIT_POINT:
//STRIP001          nNew = 3; break;
//STRIP001      case FUNIT_PICA:
//STRIP001          nNew = 4; break;
//STRIP001      case FUNIT_TWIP:
//STRIP001          nNew = 5; break;
//STRIP001  }
//STRIP001  return ConvertTable[nOld][nNew]( nVal );
//STRIP001 }

//STRIP001 String ConvertPosSizeToIniString( const Point& rPos, const Size& rSize )
//STRIP001 {
//STRIP001     String aRet = String::CreateFromInt32( rPos.X() );
//STRIP001  aRet += '/';
//STRIP001     aRet += String::CreateFromInt32( rPos.Y() );
//STRIP001  aRet += '/';
//STRIP001     aRet += String::CreateFromInt32( rSize.Width() );
//STRIP001  aRet += '/';
//STRIP001     aRet += String::CreateFromInt32( rSize.Height() );
//STRIP001     return aRet;
//STRIP001 }

//STRIP001 sal_Bool ConvertIniStringToPosSize( const String& rIniStr, Point& rPos, Size& rSize )
//STRIP001 {
//STRIP001  if ( rIniStr.GetTokenCount('/') != 4 )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  USHORT nIdx = 0;
//STRIP001  rPos.X() = rIniStr.GetToken( 0, '/', nIdx ).ToInt32();
//STRIP001  rPos.Y() = rIniStr.GetToken( 0, '/', nIdx ).ToInt32();
//STRIP001  rSize.Width() = rIniStr.GetToken( 0, '/', nIdx ).ToInt32();
//STRIP001  rSize.Height() = rIniStr.GetToken( 0, '/', nIdx ).ToInt32();
//STRIP001
//STRIP001  // negative sizes are invalid
//STRIP001  if ( rSize.Width() < 0 || rSize.Height() < 0 )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  return sal_True;
//STRIP001 }

}
