/*************************************************************************
 *
 *  $RCSfile: sc_attrib.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:25:56 $
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

// INCLUDE ---------------------------------------------------------------


#ifndef _COM_SUN_STAR_UTIL_CELLPROTECTION_HPP_
#include <com/sun/star/util/CellProtection.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XPROTECTABLE_HPP_
#include <com/sun/star/util/XProtectable.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXT_HPP_
#include <com/sun/star/text/XText.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/boxitem.hxx>
#include <bf_svx/editdata.hxx>
#include <bf_svx/editeng.hxx>
#include <bf_svx/editobj.hxx>
#include <bf_svx/flditem.hxx>
#include <svtools/args.hxx>

#include "attrib.hxx"
#include "global.hxx"
#include "editutil.hxx"
#include "bf_sc.hrc"
#include "globstr.hrc"

#include "textuno.hxx"  // ScHeaderFooterContentObj
namespace binfilter {

using namespace ::com::sun::star;

//------------------------------------------------------------------------

/*N*/ TYPEINIT1(ScMergeAttr,            SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(ScProtectionAttr,     SfxPoolItem);
/*N*/ TYPEINIT1(ScRangeItem,            SfxPoolItem);
/*N*/ TYPEINIT1(ScTableListItem,        SfxPoolItem);
/*N*/ TYPEINIT1(ScPageHFItem,       SfxPoolItem);
/*N*/ TYPEINIT1(ScViewObjectModeItem, SfxEnumItem);
/*N*/ TYPEINIT1(ScDoubleItem,       SfxPoolItem);

//------------------------------------------------------------------------

//
//      allgemeine Hilfsfunktionen
//

/*N*/ BOOL HasPriority( const SvxBorderLine* pThis, const SvxBorderLine* pOther )
/*N*/ {
/*N*/ //      DBG_ASSERT( pThis || pOther, "LineAttr == 0" );
/*N*/
/*N*/   if (!pThis)
/*N*/       return FALSE;
/*N*/   if (!pOther)
/*N*/       return TRUE;
/*N*/
/*N*/   USHORT nThisSize = pThis->GetOutWidth() + pThis->GetDistance() + pThis->GetInWidth();
/*N*/   USHORT nOtherSize = pOther->GetOutWidth() + pOther->GetDistance() + pOther->GetInWidth();
/*N*/
/*N*/   if (nThisSize > nOtherSize)
/*N*/       return TRUE;
/*N*/   else if (nThisSize < nOtherSize)
/*N*/       return FALSE;
/*N*/   else
/*N*/   {
/*N*/       if ( pOther->GetInWidth() && !pThis->GetInWidth() )
/*N*/           return TRUE;
/*N*/       else if ( pThis->GetInWidth() && !pOther->GetInWidth() )
/*N*/           return FALSE;
/*N*/       else
/*N*/       {
/*N*/           return TRUE;            //! ???
/*N*/       }
/*N*/   }
/*N*/ }


//
//      Item - Implementierungen
//

//------------------------------------------------------------------------
// Merge
//------------------------------------------------------------------------

/*N*/ ScMergeAttr::ScMergeAttr():
/*N*/   SfxPoolItem(ATTR_MERGE),
/*N*/   nColMerge(0),
/*N*/   nRowMerge(0)
/*N*/ {}

//------------------------------------------------------------------------

/*N*/ ScMergeAttr::ScMergeAttr( INT16 nCol, INT16 nRow):
/*N*/   SfxPoolItem(ATTR_MERGE),
/*N*/   nColMerge(nCol),
/*N*/   nRowMerge(nRow)
/*N*/ {}

//------------------------------------------------------------------------

/*N*/ ScMergeAttr::ScMergeAttr(const ScMergeAttr& rItem):
/*N*/   SfxPoolItem(ATTR_MERGE)
/*N*/ {
/*N*/   nColMerge = rItem.nColMerge;
/*N*/   nRowMerge = rItem.nRowMerge;
/*N*/ }

/*N*/ __EXPORT ScMergeAttr::~ScMergeAttr()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScMergeAttr::GetValueText() const
//STRIP001 {
//STRIP001  String aString( '(' );
//STRIP001  aString += String::CreateFromInt32( nColMerge );
//STRIP001  aString += ',';
//STRIP001  aString += String::CreateFromInt32( nRowMerge );
//STRIP001  aString += ')';
//STRIP001  return aString;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ int __EXPORT ScMergeAttr::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( Which() != rItem.Which() || Type() == rItem.Type(), "which ==, type !=" );
/*N*/   return (Which() == rItem.Which())
/*N*/            && (nColMerge == ((ScMergeAttr&)rItem).nColMerge)
/*N*/            && (nRowMerge == ((ScMergeAttr&)rItem).nRowMerge);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScMergeAttr::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new ScMergeAttr(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScMergeAttr::Create( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   INT16   nCol;
/*N*/   INT16   nRow;
/*N*/   rStream >> nCol;
/*N*/   rStream >> nRow;
/*N*/   return new ScMergeAttr(nCol,nRow);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvStream& __EXPORT ScMergeAttr::Store( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   rStream << nColMerge;
/*N*/   rStream << nRowMerge;
/*N*/   return rStream;
/*N*/ }

//------------------------------------------------------------------------
// MergeFlag
//------------------------------------------------------------------------

/*N*/ ScMergeFlagAttr::ScMergeFlagAttr():
/*N*/   SfxInt16Item(ATTR_MERGE_FLAG, 0)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScMergeFlagAttr::ScMergeFlagAttr(INT16 nFlags):
/*N*/   SfxInt16Item(ATTR_MERGE_FLAG, nFlags)
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScMergeFlagAttr::~ScMergeFlagAttr()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------
// Protection
//------------------------------------------------------------------------

/*N*/ ScProtectionAttr::ScProtectionAttr():
/*N*/   SfxPoolItem(ATTR_PROTECTION),
/*N*/   bProtection(TRUE),
/*N*/   bHideFormula(FALSE),
/*N*/   bHideCell(FALSE),
/*N*/   bHidePrint(FALSE)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScProtectionAttr::ScProtectionAttr( BOOL bProtect, BOOL bHFormula,
/*N*/                                   BOOL bHCell, BOOL bHPrint):
/*N*/   SfxPoolItem(ATTR_PROTECTION),
/*N*/   bProtection(bProtect),
/*N*/   bHideFormula(bHFormula),
/*N*/   bHideCell(bHCell),
/*N*/   bHidePrint(bHPrint)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScProtectionAttr::ScProtectionAttr(const ScProtectionAttr& rItem):
/*N*/   SfxPoolItem(ATTR_PROTECTION)
/*N*/ {
/*N*/   bProtection  = rItem.bProtection;
/*N*/   bHideFormula = rItem.bHideFormula;
/*N*/   bHideCell    = rItem.bHideCell;
/*N*/   bHidePrint   = rItem.bHidePrint;
/*N*/ }

/*N*/ __EXPORT ScProtectionAttr::~ScProtectionAttr()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL __EXPORT ScProtectionAttr::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/     switch ( nMemberId  )
/*N*/     {
/*N*/         case 0 :
/*N*/         {
/*N*/             util::CellProtection aProtection;
/*N*/             aProtection.IsLocked        = bProtection;
/*N*/             aProtection.IsFormulaHidden = bHideFormula;
/*N*/             aProtection.IsHidden        = bHideCell;
/*N*/             aProtection.IsPrintHidden   = bHidePrint;
/*N*/             rVal <<= aProtection;
/*N*/             break;
/*N*/         }
/*N*/         case MID_1 :
/*N*/             rVal <<= (sal_Bool ) bProtection; break;
/*N*/         case MID_2 :
/*N*/             rVal <<= (sal_Bool ) bHideFormula; break;
/*N*/         case MID_3 :
/*N*/             rVal <<= (sal_Bool ) bHideCell; break;
/*N*/         case MID_4 :
/*N*/             rVal <<= (sal_Bool ) bHidePrint; break;
/*N*/         default:
/*N*/             DBG_ERROR("Wrong MemberID!")
/*N*/             return FALSE;
/*N*/     }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL __EXPORT ScProtectionAttr::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/     sal_Bool bVal;
/*N*/   nMemberId &= ~CONVERT_TWIPS;
/*N*/     switch ( nMemberId )
/*N*/     {
/*N*/         case 0 :
/*N*/         {
/*N*/             util::CellProtection aProtection;
/*N*/             if ( rVal >>= aProtection )
/*N*/             {
/*N*/                 bProtection  = aProtection.IsLocked;
/*N*/                 bHideFormula = aProtection.IsFormulaHidden;
/*N*/                 bHideCell    = aProtection.IsHidden;
/*N*/                 bHidePrint   = aProtection.IsPrintHidden;
/*N*/                 bRet = TRUE;
/*N*/             }
/*N*/             else
/*N*/                 DBG_ERROR("exception - wrong argument");
/*N*/             break;
/*N*/         }
/*N*/         case MID_1 :
/*N*/             bRet = (rVal >>= bVal); if (bRet) bProtection=bVal; break;
/*N*/         case MID_2 :
/*N*/             bRet = (rVal >>= bVal); if (bRet) bHideFormula=bVal; break;
/*N*/         case MID_3 :
/*N*/             bRet = (rVal >>= bVal); if (bRet) bHideCell=bVal; break;
/*N*/         case MID_4 :
/*N*/             bRet = (rVal >>= bVal); if (bRet) bHidePrint=bVal; break;
/*N*/         default:
/*N*/             DBG_ERROR("Wrong MemberID!");
/*N*/     }
/*N*/
/*N*/   return bRet;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScProtectionAttr::GetValueText() const
//STRIP001 {
//STRIP001  String aValue;
//STRIP001  String aStrYes ( ScGlobal::GetRscString(STR_YES) );
//STRIP001  String aStrNo  ( ScGlobal::GetRscString(STR_NO) );
//STRIP001  sal_Unicode cDelim = ',';
//STRIP001
//STRIP001  aValue  = '(';
//STRIP001  aValue += (bProtection  ? aStrYes : aStrNo);    aValue += cDelim;
//STRIP001  aValue += (bHideFormula ? aStrYes : aStrNo);    aValue += cDelim;
//STRIP001  aValue += (bHideCell    ? aStrYes : aStrNo);    aValue += cDelim;
//STRIP001  aValue += (bHidePrint   ? aStrYes : aStrNo);
//STRIP001  aValue += ')';
//STRIP001
//STRIP001  return aValue;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation __EXPORT ScProtectionAttr::GetPresentation
//STRIP001  (
//STRIP001      SfxItemPresentation ePres,
//STRIP001      SfxMapUnit eCoreMetric,
//STRIP001      SfxMapUnit ePresMetric,
//STRIP001      String& rText,
//STRIP001         const IntlWrapper* pIntl
//STRIP001  ) const
//STRIP001 {
//STRIP001  String aStrYes  ( ScGlobal::GetRscString(STR_YES) );
//STRIP001  String aStrNo   ( ScGlobal::GetRscString(STR_NO) );
//STRIP001  String aStrSep   = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM( ": " ));
//STRIP001  String aStrDelim = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM( ", " ));
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          rText = GetValueText();
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText  = ScGlobal::GetRscString(STR_PROTECTION); rText += aStrSep;
//STRIP001          rText += (bProtection ? aStrYes : aStrNo);       rText += aStrDelim;
//STRIP001          rText += ScGlobal::GetRscString(STR_FORMULAS);   rText += aStrSep;
//STRIP001          rText += (!bHideFormula ? aStrYes : aStrNo);     rText += aStrDelim;
//STRIP001          rText += ScGlobal::GetRscString(STR_HIDE);       rText += aStrSep;
//STRIP001          rText += (bHideCell ? aStrYes : aStrNo);         rText += aStrDelim;
//STRIP001          rText += ScGlobal::GetRscString(STR_PRINT);      rText += aStrSep;
//STRIP001          rText += (!bHidePrint ? aStrYes : aStrNo);
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ int __EXPORT ScProtectionAttr::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( Which() != rItem.Which() || Type() == rItem.Type(), "which ==, type !=" );
/*N*/   return (Which() == rItem.Which())
/*N*/            && (bProtection == ((ScProtectionAttr&)rItem).bProtection)
/*N*/            && (bHideFormula == ((ScProtectionAttr&)rItem).bHideFormula)
/*N*/            && (bHideCell == ((ScProtectionAttr&)rItem).bHideCell)
/*N*/            && (bHidePrint == ((ScProtectionAttr&)rItem).bHidePrint);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScProtectionAttr::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new ScProtectionAttr(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScProtectionAttr::Create( SvStream& rStream, USHORT n ) const
/*N*/ {
/*N*/   BOOL bProtect;
/*N*/   BOOL bHFormula;
/*N*/   BOOL bHCell;
/*N*/   BOOL bHPrint;
/*N*/
/*N*/   rStream >> bProtect;
/*N*/   rStream >> bHFormula;
/*N*/   rStream >> bHCell;
/*N*/   rStream >> bHPrint;
/*N*/
/*N*/   return new ScProtectionAttr(bProtect,bHFormula,bHCell,bHPrint);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvStream& __EXPORT ScProtectionAttr::Store( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   rStream << bProtection;
/*N*/   rStream << bHideFormula;
/*N*/   rStream << bHideCell;
/*N*/   rStream << bHidePrint;
/*N*/
/*N*/   return rStream;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL ScProtectionAttr::SetProtection( BOOL bProtect)
//STRIP001 {
//STRIP001  bProtection =  bProtect;
//STRIP001  return TRUE;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScProtectionAttr::SetHideFormula( BOOL bHFormula)
//STRIP001 {
//STRIP001  bHideFormula = bHFormula;
//STRIP001  return TRUE;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScProtectionAttr::SetHideCell( BOOL bHCell)
//STRIP001 {
//STRIP001  bHideCell = bHCell;
//STRIP001  return TRUE;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScProtectionAttr::SetHidePrint( BOOL bHPrint)
//STRIP001 {
//STRIP001  bHidePrint = bHPrint;
//STRIP001  return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------
//      ScRangeItem - Tabellenbereich
// -----------------------------------------------------------------------

//STRIP001 void __EXPORT ScRangeItem::Record( SfxArguments& rArgs ) const
//STRIP001 {
//STRIP001  const ScAddress& rStart = aRange.aStart;
//STRIP001  const ScAddress& rEnd   = aRange.aEnd;
//STRIP001
//STRIP001  rArgs.AppendInteger( rStart.Col() );
//STRIP001  rArgs.AppendInteger( rStart.Row() );
//STRIP001  rArgs.AppendInteger( rStart.Tab() );
//STRIP001  rArgs.AppendInteger( rEnd  .Col() );
//STRIP001  rArgs.AppendInteger( rEnd  .Row() );
//STRIP001  rArgs.AppendInteger( rEnd.Tab() );
//STRIP001  rArgs.AppendInteger( nFlags );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxArgumentError __EXPORT ScRangeItem::Construct( USHORT nId, const SfxArguments& rArgs )
//STRIP001 {
//STRIP001  if ( rArgs.Count() < 7 )
//STRIP001      return SFX_ARGUMENT_ERROR( rArgs.Count(), SFX_ERR_ARGUMENT_EXPECTED );
//STRIP001  if ( rArgs.Count() > 7 )
//STRIP001      return SFX_ARGUMENT_ERROR( rArgs.Count()-1, SFX_ERR_TOO_MANY_ARGUMENTS );
//STRIP001
//STRIP001  ScAddress& rStart = aRange.aStart;
//STRIP001  ScAddress& rEnd   = aRange.aEnd;
//STRIP001
//STRIP001  SetWhich( nId );
//STRIP001  rStart.SetCol( rArgs.Get( 0 ).GetInteger() );
//STRIP001  rStart.SetRow( rArgs.Get( 1 ).GetInteger() );
//STRIP001  rStart.SetTab( rArgs.Get( 2 ).GetInteger() );
//STRIP001  rEnd  .SetCol( rArgs.Get( 3 ).GetInteger() );
//STRIP001  rEnd  .SetRow( rArgs.Get( 4 ).GetInteger() );
//STRIP001  rEnd  .SetTab( rArgs.Get( 5 ).GetInteger() );
//STRIP001  nFlags = (USHORT)rArgs.Get( 6 ).GetInteger();
//STRIP001
//STRIP001  return 0;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ int __EXPORT ScRangeItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return ( aRange == ( (ScRangeItem&)rAttr ).aRange );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScRangeItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScRangeItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation __EXPORT ScRangeItem::GetPresentation
//STRIP001  (
//STRIP001      SfxItemPresentation ePres,
//STRIP001      SfxMapUnit          eCoreUnit,
//STRIP001      SfxMapUnit          ePresUnit,
//STRIP001      String&             rText,
//STRIP001         const IntlWrapper* pIntl
//STRIP001  ) const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      rText  = ScGlobal::GetRscString(STR_AREA);
//STRIP001      rText.AppendAscii(RTL_CONSTASCII_STRINGPARAM( ": " ));
//STRIP001 //       break;// Durchfallen !!!
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      {
//STRIP001          String aText;
//STRIP001          aRange.Format( aText );
//STRIP001          rText += aText;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

//-----------------------------------------------------------------------

/*N*/ USHORT __EXPORT ScRangeItem::GetVersion( USHORT nFileVersion ) const
/*N*/ {
/*N*/   return 2;
/*N*/ }

//-----------------------------------------------------------------------

/*N*/ SvStream& __EXPORT ScRangeItem::Store( SvStream& rStrm, USHORT nVer ) const
/*N*/ {
/*N*/   rStrm << aRange;
/*N*/   rStrm << nFlags;
/*N*/
/*N*/   return rStrm;
/*N*/ }

//-----------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScRangeItem::Create( SvStream& rStream, USHORT nVersion ) const
/*N*/ {
/*N*/   ScRange aNewRange;
/*N*/   BOOL    nNewFlags = FALSE;
/*N*/
/*N*/   switch ( nVersion )
/*N*/   {
/*N*/       case 2:
/*N*/           rStream >> aNewRange;
/*N*/           rStream >> nNewFlags;
/*N*/           break;
/*N*/
/*N*/       case 1:
/*N*/           rStream >> aNewRange;
/*N*/           nNewFlags = 0;
/*N*/           break;
/*N*/
/*N*/       case 0:
/*N*/           {
/*N*/               // alte Version mit ScArea -> 5 USHORTs lesen
/*N*/               ScAddress&  rStart = aNewRange.aStart;
/*N*/               ScAddress&  rEnd   = aNewRange.aEnd;
/*N*/               USHORT      n;
/*N*/
/*N*/               rStream >> n;
/*N*/
/*N*/               if ( n > MAXTAB )
/*N*/               {
/*N*/                   nNewFlags = SCR_ALLTABS;
/*N*/                   rStart.SetTab( 0 ); rEnd.SetTab( 0 );
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   nNewFlags = 0;
/*N*/                   rStart.SetTab( n ); rEnd.SetTab( n );
/*N*/               }
/*N*/
/*N*/               rStream >> n; rStart.SetCol( n );
/*N*/               rStream >> n; rStart.SetRow( n );
/*N*/               rStream >> n; rEnd  .SetCol( n );
/*N*/               rStream >> n; rEnd  .SetRow( n );
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           DBG_ERROR( "ScRangeItem::Create: Unknown Version!" );
/*N*/   }
/*N*/
/*N*/   return ( new ScRangeItem( Which(), aNewRange, nNewFlags ) );
/*N*/ }


// -----------------------------------------------------------------------
//      ScTableListItem - Liste von Tabellen(-nummern)
// -----------------------------------------------------------------------

/*N*/ ScTableListItem::ScTableListItem( const ScTableListItem& rCpy )
/*N*/   :   SfxPoolItem ( rCpy.Which() ),
/*N*/       nCount      ( rCpy.nCount )
/*N*/ {
/*N*/   if ( nCount > 0 )
/*N*/   {
/*N*/       pTabArr = new USHORT [nCount];
/*N*/
/*N*/       for ( USHORT i=0; i<nCount; i++ )
/*N*/           pTabArr[i] = rCpy.pTabArr[i];
/*N*/   }
/*N*/   else
/*N*/       pTabArr = NULL;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScTableListItem::ScTableListItem( const USHORT nWhich, const List& rList )
/*N*/   :   SfxPoolItem ( nWhich ),
/*N*/       nCount      ( 0 ),
/*N*/       pTabArr     ( NULL )
/*N*/ {
/*N*/   SetTableList( rList );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ __EXPORT ScTableListItem::~ScTableListItem()
/*N*/ {
/*N*/   delete [] pTabArr;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void __EXPORT ScTableListItem::Record( SfxArguments& rArgs ) const
//STRIP001 {
//STRIP001  rArgs.AppendInteger( nCount );
//STRIP001
//STRIP001  if ( nCount>0 && pTabArr )
//STRIP001      for ( USHORT i=0; i<nCount; i++ )
//STRIP001          rArgs.AppendInteger( pTabArr[i] );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxArgumentError __EXPORT ScTableListItem::Construct( USHORT nId, const SfxArguments& rArgs )
//STRIP001 {
//STRIP001  USHORT nCount = rArgs.Get( 0 ).GetInteger();
//STRIP001
//STRIP001  if ( pTabArr )
//STRIP001      delete [] pTabArr, pTabArr = NULL;
//STRIP001
//STRIP001  if ( nCount > 0 )
//STRIP001  {
//STRIP001      if ( rArgs.Count()-1 < nCount )
//STRIP001          return SFX_ARGUMENT_ERROR( rArgs.Count(), SFX_ERR_ARGUMENT_EXPECTED );
//STRIP001      if ( rArgs.Count()-1 > nCount )
//STRIP001          return SFX_ARGUMENT_ERROR( rArgs.Count()-1, SFX_ERR_TOO_MANY_ARGUMENTS );
//STRIP001
//STRIP001      SetWhich( nId );
//STRIP001      pTabArr = new USHORT [nCount];
//STRIP001
//STRIP001      for ( USHORT i=0; i<nCount; i++ )
//STRIP001          pTabArr[i] = rArgs.Get( i+1 ).GetInteger();
//STRIP001  }
//STRIP001
//STRIP001  return 0;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ScTableListItem& ScTableListItem::operator=( const ScTableListItem& rCpy )
//STRIP001 {
//STRIP001  delete [] pTabArr;
//STRIP001
//STRIP001  if ( rCpy.nCount > 0 )
//STRIP001  {
//STRIP001      pTabArr = new USHORT [rCpy.nCount];
//STRIP001      for ( USHORT i=0; i<rCpy.nCount; i++ )
//STRIP001          pTabArr[i] = rCpy.pTabArr[i];
//STRIP001  }
//STRIP001  else
//STRIP001      pTabArr = NULL;
//STRIP001
//STRIP001  nCount = rCpy.nCount;
//STRIP001
//STRIP001  return *this;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ int __EXPORT ScTableListItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   ScTableListItem&    rCmp   = (ScTableListItem&)rAttr;
/*N*/   BOOL                bEqual = (nCount == rCmp.nCount);
/*N*/
/*N*/   if ( nCount > 0 )
/*N*/   {
/*N*/       USHORT  i=0;
/*N*/
/*N*/       bEqual = ( pTabArr && rCmp.pTabArr );
/*N*/
/*N*/       while ( bEqual && i<nCount )
/*N*/       {
/*N*/           bEqual = ( pTabArr[i] == rCmp.pTabArr[i] );
/*N*/           i++;
/*N*/       }
/*N*/   }
/*N*/   return bEqual;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScTableListItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScTableListItem( *this );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation __EXPORT ScTableListItem::GetPresentation
//STRIP001  (
//STRIP001      SfxItemPresentation ePres,
//STRIP001      SfxMapUnit          eCoreUnit,
//STRIP001      SfxMapUnit          ePresUnit,
//STRIP001      String&             rText,
//STRIP001         const IntlWrapper* pIntl
//STRIP001  ) const
//STRIP001 {
//STRIP001  const sal_Unicode cDelim = ',';
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          {
//STRIP001          rText  = '(';
//STRIP001          if ( nCount>0 && pTabArr )
//STRIP001              for ( USHORT i=0; i<nCount; i++ )
//STRIP001              {
//STRIP001                  rText += String::CreateFromInt32( pTabArr[i] );
//STRIP001                  if ( i<(nCount-1) )
//STRIP001                      rText += cDelim;
//STRIP001              }
//STRIP001          rText += ')';
//STRIP001          }
//STRIP001          return ePres;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001  }
//STRIP001
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//-----------------------------------------------------------------------

/*N*/ SvStream& __EXPORT ScTableListItem::Store( SvStream& rStrm, USHORT nVer ) const
/*N*/ {
/*N*/   rStrm << nCount;
/*N*/
/*N*/   if ( nCount>0 && pTabArr )
/*N*/       for ( USHORT i=0; i<nCount; i++ )
/*N*/               rStrm << pTabArr[i];
/*N*/
/*N*/   return rStrm;
/*N*/ }

//-----------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScTableListItem::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/   ScTableListItem* pNewItem;
/*N*/   List             aList;
/*N*/   USHORT*          p;
/*N*/   USHORT           nTabCount;
/*N*/   USHORT           nTabNo;
/*N*/
/*N*/   rStrm >> nTabCount;
/*N*/
/*N*/   if ( nTabCount > 0 )
/*N*/   {
/*N*/       for ( USHORT i=0; i<nTabCount; i++ )
/*N*/       {
/*N*/           rStrm >> nTabNo;
/*N*/           aList.Insert( new USHORT(nTabNo) );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pNewItem = new ScTableListItem( Which(), aList );
/*N*/
/*N*/   aList.First();
/*N*/   while ( p = (USHORT*)aList.Remove() )
/*N*/       delete p;
/*N*/
/*N*/   return pNewItem;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 BOOL ScTableListItem::GetTableList( List& aList ) const
//STRIP001 {
//STRIP001  for ( USHORT i=0; i<nCount; i++ )
//STRIP001      aList.Insert( new USHORT( pTabArr[i] ) );
//STRIP001
//STRIP001  return ( nCount > 0 );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void ScTableListItem::SetTableList( const List& rList )
/*N*/ {
/*N*/   nCount = (USHORT)rList.Count();
/*N*/
/*N*/   delete [] pTabArr;
/*N*/
/*N*/   if ( nCount > 0 )
/*N*/   {
/*N*/       pTabArr = new USHORT [nCount];
/*N*/
/*N*/       for ( USHORT i=0; i<nCount; i++ )
/*N*/           pTabArr[i] = *( (USHORT*)rList.GetObject( i ) );
/*N*/   }
/*N*/   else
/*N*/       pTabArr = NULL;
/*N*/ }


// -----------------------------------------------------------------------
//      ScPageHFItem - Daten der Kopf-/Fußzeilen
// -----------------------------------------------------------------------

/*N*/ ScPageHFItem::ScPageHFItem( USHORT nWhich )
/*N*/   :   SfxPoolItem ( nWhich ),
/*N*/       pLeftArea   ( NULL ),
/*N*/       pCenterArea ( NULL ),
/*N*/       pRightArea  ( NULL )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScPageHFItem::ScPageHFItem( const ScPageHFItem& rItem )
/*N*/   :   SfxPoolItem ( rItem ),
/*N*/       pLeftArea   ( NULL ),
/*N*/       pCenterArea ( NULL ),
/*N*/       pRightArea  ( NULL )
/*N*/ {
/*N*/   if ( rItem.pLeftArea )
/*N*/       pLeftArea = rItem.pLeftArea->Clone();
/*N*/   if ( rItem.pCenterArea )
/*N*/       pCenterArea = rItem.pCenterArea->Clone();
/*N*/   if ( rItem.pRightArea )
/*N*/       pRightArea = rItem.pRightArea->Clone();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScPageHFItem::~ScPageHFItem()
/*N*/ {
/*N*/   delete pLeftArea;
/*N*/   delete pCenterArea;
/*N*/   delete pRightArea;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL __EXPORT ScPageHFItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   uno::Reference<sheet::XHeaderFooterContent> xContent =
/*N*/       new ScHeaderFooterContentObj( pLeftArea, pCenterArea, pRightArea );
/*N*/
/*N*/   rVal <<= xContent;
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL __EXPORT ScPageHFItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   uno::Reference<sheet::XHeaderFooterContent> xContent;
/*N*/   if ( rVal >>= xContent )
/*N*/   {
/*N*/       if ( xContent.is() )
/*N*/       {
/*N*/           ScHeaderFooterContentObj* pImp =
/*N*/                   ScHeaderFooterContentObj::getImplementation( xContent );
/*N*/           if (pImp)
/*N*/           {
/*N*/               const EditTextObject* pImpLeft = pImp->GetLeftEditObject();
/*N*/               delete pLeftArea;
/*N*/               pLeftArea = pImpLeft ? pImpLeft->Clone() : NULL;
/*N*/
/*N*/               const EditTextObject* pImpCenter = pImp->GetCenterEditObject();
/*N*/               delete pCenterArea;
/*N*/               pCenterArea = pImpCenter ? pImpCenter->Clone() : NULL;
/*N*/
/*N*/               const EditTextObject* pImpRight = pImp->GetRightEditObject();
/*N*/               delete pRightArea;
/*N*/               pRightArea = pImpRight ? pImpRight->Clone() : NULL;
/*N*/
/*N*/               if ( !pLeftArea || !pCenterArea || !pRightArea )
/*N*/               {
/*?*/                   // keine Texte auf NULL stehen lassen
/*?*/                   ScEditEngineDefaulter aEngine( EditEngine::CreatePool(), TRUE );
/*?*/                   if (!pLeftArea)
/*?*/                       pLeftArea = aEngine.CreateTextObject();
/*?*/                   if (!pCenterArea)
/*?*/                       pCenterArea = aEngine.CreateTextObject();
/*?*/                   if (!pRightArea)
/*?*/                       pRightArea = aEngine.CreateTextObject();
/*N*/               }
/*N*/
/*N*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (!bRet)
/*N*/   {
/*N*/       DBG_ERROR("exception - wrong argument");
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ String __EXPORT ScPageHFItem::GetValueText() const
/*N*/ {
/*N*/   return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScPageHFItem"));
/*N*/ }

//------------------------------------------------------------------------

/*N*/ int __EXPORT ScPageHFItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
/*N*/
/*N*/   const ScPageHFItem& r = (const ScPageHFItem&)rItem;
/*N*/
/*N*/   return    ScGlobal::EETextObjEqual(pLeftArea,   r.pLeftArea)
/*N*/          && ScGlobal::EETextObjEqual(pCenterArea, r.pCenterArea)
/*N*/          && ScGlobal::EETextObjEqual(pRightArea,  r.pRightArea);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScPageHFItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScPageHFItem( *this );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ USHORT __EXPORT ScPageHFItem::GetVersion( USHORT nFileVersion ) const
/*N*/ {
/*N*/   // 0 = ohne Feldbefehle
/*N*/   // 1 = Titel bzw. Dateiname mit SvxFileField
/*N*/   // 2 = Pfad und/oder Dateiname mit SvxExtFileField, Titel mit SvxFileField
/*N*/   return 2;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void lcl_SetSpace( String& rStr, const ESelection& rSel )
/*N*/ {
/*N*/   // Text durch ein Leerzeichen ersetzen, damit Positionen stimmen:
/*N*/
/*N*/   xub_StrLen nLen = rSel.nEndPos-rSel.nStartPos;
/*N*/   rStr.Erase( rSel.nStartPos, nLen-1 );
/*N*/   rStr.SetChar( rSel.nStartPos, ' ' );
/*N*/ }

/*N*/ BOOL lcl_ConvertFields(EditEngine& rEng, const String* pCommands)
/*N*/ {
/*N*/   BOOL bChange = FALSE;
/*N*/   USHORT nParCnt = rEng.GetParagraphCount();
/*N*/   for (USHORT nPar = 0; nPar<nParCnt; nPar++)
/*N*/   {
/*N*/       String aStr = rEng.GetText( nPar );
/*N*/       xub_StrLen nPos;
/*N*/
/*N*/       while ((nPos = aStr.Search(pCommands[0])) != STRING_NOTFOUND)
/*N*/       {
/*N*/           ESelection aSel( nPar,nPos, nPar,nPos+pCommands[0].Len() );
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxPageField()), aSel );
/*N*/           lcl_SetSpace(aStr, aSel ); bChange = TRUE;
/*N*/       }
/*N*/       while ((nPos = aStr.Search(pCommands[1])) != STRING_NOTFOUND)
/*N*/       {
/*N*/           ESelection aSel( nPar,nPos, nPar,nPos+pCommands[1].Len() );
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxPagesField()), aSel );
/*N*/           lcl_SetSpace(aStr, aSel ); bChange = TRUE;
/*N*/       }
/*N*/       while ((nPos = aStr.Search(pCommands[2])) != STRING_NOTFOUND)
/*N*/       {
/*N*/           ESelection aSel( nPar,nPos, nPar,nPos+pCommands[2].Len() );
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxDateField(Date(),SVXDATETYPE_VAR)), aSel );
/*N*/           lcl_SetSpace(aStr, aSel ); bChange = TRUE;
/*N*/       }
/*N*/       while ((nPos = aStr.Search(pCommands[3])) != STRING_NOTFOUND)
/*N*/       {
/*N*/           ESelection aSel( nPar,nPos, nPar,nPos+pCommands[3].Len() );
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxTimeField()), aSel );
/*N*/           lcl_SetSpace(aStr, aSel ); bChange = TRUE;
/*N*/       }
/*N*/       while ((nPos = aStr.Search(pCommands[4])) != STRING_NOTFOUND)
/*N*/       {
/*N*/           ESelection aSel( nPar,nPos, nPar,nPos+pCommands[4].Len() );
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxFileField()), aSel );
/*N*/           lcl_SetSpace(aStr, aSel ); bChange = TRUE;
/*N*/       }
/*N*/       while ((nPos = aStr.Search(pCommands[5])) != STRING_NOTFOUND)
/*N*/       {
/*N*/           ESelection aSel( nPar,nPos, nPar,nPos+pCommands[5].Len() );
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxTableField()), aSel );
/*N*/           lcl_SetSpace(aStr, aSel ); bChange = TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bChange;
/*N*/ }

#define SC_FIELD_COUNT  6

/*N*/ SfxPoolItem* __EXPORT ScPageHFItem::Create( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   EditTextObject* pLeft   = EditTextObject::Create(rStream);
/*N*/   EditTextObject* pCenter = EditTextObject::Create(rStream);
/*N*/   EditTextObject* pRight  = EditTextObject::Create(rStream);
/*N*/
/*N*/   DBG_ASSERT( pLeft && pCenter && pRight, "Error reading ScPageHFItem" );
/*N*/
/*N*/   if ( pLeft == NULL   || pLeft->GetParagraphCount() == 0 ||
/*N*/        pCenter == NULL || pCenter->GetParagraphCount() == 0 ||
/*N*/        pRight == NULL  || pRight->GetParagraphCount() == 0 )
/*N*/   {
/*?*/       //  If successfully loaded, each object contains at least one paragraph.
/*?*/       //  Excel import in 5.1 created broken TextObjects (#67442#) that are
/*?*/       //  corrected here to avoid saving wrong files again (#90487#).
/*?*/
/*?*/       ScEditEngineDefaulter aEngine( EditEngine::CreatePool(), TRUE );
/*?*/       if ( pLeft == NULL || pLeft->GetParagraphCount() == 0 )
/*?*/       {
/*?*/           delete pLeft;
/*?*/           pLeft = aEngine.CreateTextObject();
/*?*/       }
/*?*/       if ( pCenter == NULL || pCenter->GetParagraphCount() == 0 )
/*?*/       {
/*?*/           delete pCenter;
/*?*/           pCenter = aEngine.CreateTextObject();
/*?*/       }
/*?*/       if ( pRight == NULL || pRight->GetParagraphCount() == 0 )
/*?*/       {
/*?*/           delete pRight;
/*?*/           pRight = aEngine.CreateTextObject();
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if ( nVer < 1 )             // alte Feldbefehle umsetzen
/*N*/   {
/*N*/       USHORT i;
/*N*/       const String& rDel = ScGlobal::GetRscString( STR_HFCMD_DELIMITER );
/*N*/       String aCommands[SC_FIELD_COUNT];
/*N*/       for (i=0; i<SC_FIELD_COUNT; i++)
/*N*/           aCommands[i] = rDel;
/*N*/       aCommands[0] += ScGlobal::GetRscString(STR_HFCMD_PAGE);
/*N*/       aCommands[1] += ScGlobal::GetRscString(STR_HFCMD_PAGES);
/*N*/       aCommands[2] += ScGlobal::GetRscString(STR_HFCMD_DATE);
/*N*/       aCommands[3] += ScGlobal::GetRscString(STR_HFCMD_TIME);
/*N*/       aCommands[4] += ScGlobal::GetRscString(STR_HFCMD_FILE);
/*N*/       aCommands[5] += ScGlobal::GetRscString(STR_HFCMD_TABLE);
/*N*/       for (i=0; i<SC_FIELD_COUNT; i++)
/*N*/           aCommands[i] += rDel;
/*N*/
/*N*/       ScEditEngineDefaulter aEngine( EditEngine::CreatePool(), TRUE );
/*N*/       aEngine.SetText(*pLeft);
/*N*/       if (lcl_ConvertFields(aEngine,aCommands))
/*N*/       {
/*?*/           delete pLeft;
/*?*/           pLeft = aEngine.CreateTextObject();
/*N*/       }
/*N*/       aEngine.SetText(*pCenter);
/*N*/       if (lcl_ConvertFields(aEngine,aCommands))
/*N*/       {
/*?*/           delete pCenter;
/*?*/           pCenter = aEngine.CreateTextObject();
/*N*/       }
/*N*/       aEngine.SetText(*pRight);
/*N*/       if (lcl_ConvertFields(aEngine,aCommands))
/*N*/       {
/*?*/           delete pRight;
/*?*/           pRight = aEngine.CreateTextObject();
/*N*/       }
/*N*/   }
/*N*/   else if ( nVer < 2 )
/*N*/   {   // nichts tun, SvxFileField nicht gegen SvxExtFileField austauschen
/*N*/   }
/*N*/
/*N*/   ScPageHFItem* pItem = new ScPageHFItem( Which() );
/*N*/   pItem->SetArea( pLeft,    SC_HF_LEFTAREA   );
/*N*/   pItem->SetArea( pCenter, SC_HF_CENTERAREA );
/*N*/   pItem->SetArea( pRight,  SC_HF_RIGHTAREA  );
/*N*/
/*N*/   return pItem;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ class ScFieldChangerEditEngine : public ScEditEngineDefaulter
/*N*/ {
/*N*/   TypeId      aExtFileId;
/*N*/   USHORT      nConvPara;
/*N*/   xub_StrLen  nConvPos;
/*N*/   BOOL        bConvert;
/*N*/
/*N*/ public:
/*N*/               ScFieldChangerEditEngine( SfxItemPool* pEnginePool, BOOL bDeleteEnginePool );
/*N*/   virtual     ~ScFieldChangerEditEngine() {}
/*N*/
/*N*/   virtual String  CalcFieldValue( const SvxFieldItem& rField, USHORT nPara,
/*N*/                                   USHORT nPos, Color*& rTxtColor,
/*N*/                                   Color*& rFldColor );
/*N*/
/*N*/   BOOL            ConvertFields();
/*N*/ };
/*N*/
/*N*/ ScFieldChangerEditEngine::ScFieldChangerEditEngine( SfxItemPool* pEnginePool,
/*N*/           BOOL bDeleteEnginePool ) :
/*N*/       ScEditEngineDefaulter( pEnginePool, bDeleteEnginePool ),
/*N*/       aExtFileId( TYPE( SvxExtFileField ) ),
/*N*/       nConvPara( 0 ),
/*N*/       nConvPos( 0 ),
/*N*/       bConvert( FALSE )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ String ScFieldChangerEditEngine::CalcFieldValue( const SvxFieldItem& rField,
/*N*/           USHORT nPara, USHORT nPos, Color*& rTxtColor, Color*& rFldColor )
/*N*/ {
/*N*/   const SvxFieldData* pFieldData = rField.GetField();
/*N*/   if ( pFieldData && pFieldData->Type() == aExtFileId )
/*N*/   {
/*N*/       bConvert = TRUE;
/*N*/       nConvPara = nPara;
/*N*/       nConvPos = nPos;
/*N*/   }
/*N*/   return EMPTY_STRING;
/*N*/ }
/*N*/
/*N*/ BOOL ScFieldChangerEditEngine::ConvertFields()
/*N*/ {
/*N*/   BOOL bConverted = FALSE;
/*N*/   do
/*N*/   {
/*N*/       bConvert = FALSE;
/*N*/       UpdateFields();
/*N*/       if ( bConvert )
/*N*/       {
/*N*/           ESelection aSel( nConvPara, nConvPos, nConvPara, nConvPos+1 );
/*N*/           QuickInsertField( SvxFileField(), aSel );
/*N*/           bConverted = TRUE;
/*N*/       }
/*N*/   } while ( bConvert );
/*N*/   return bConverted;
/*N*/ }

/*N*/ void lcl_StoreOldFields( ScFieldChangerEditEngine& rEngine,
/*N*/           const EditTextObject* pArea, SvStream& rStream )
/*N*/ {
/*N*/   rEngine.SetText( *pArea );
/*N*/   if ( rEngine.ConvertFields() )
/*N*/   {
/*N*/       EditTextObject* pObj = rEngine.CreateTextObject();
/*N*/       pObj->Store( rStream );
/*N*/       delete pObj;
/*N*/   }
/*N*/   else
/*N*/       pArea->Store( rStream );
/*N*/ }

/*N*/ SvStream& __EXPORT ScPageHFItem::Store( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   if ( pLeftArea && pCenterArea && pRightArea )
/*N*/   {
/*N*/       if ( rStream.GetVersion() < SOFFICE_FILEFORMAT_50 )
/*N*/       {
/*N*/           ScFieldChangerEditEngine aEngine( EditEngine::CreatePool(), TRUE );
/*N*/           lcl_StoreOldFields( aEngine, pLeftArea, rStream );
/*N*/           lcl_StoreOldFields( aEngine, pCenterArea, rStream );
/*N*/           lcl_StoreOldFields( aEngine, pRightArea, rStream );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pLeftArea->Store(rStream);
/*N*/           pCenterArea->Store(rStream);
/*N*/           pRightArea->Store(rStream);
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       //  soll eigentlich nicht sein, kommt aber vor, wenn das Default-Item
/*?*/       //  fuer ein ItemSet kopiert wird (#61826#) ...
/*?*/
/*?*/       ScFieldChangerEditEngine aEngine( EditEngine::CreatePool(), TRUE );
/*?*/       EditTextObject* pEmpytObj = aEngine.CreateTextObject();
/*?*/
/*?*/       DBG_ASSERT( pEmpytObj, "Error creating empty EditTextObject :-(" );
/*?*/
/*?*/       if ( rStream.GetVersion() < SOFFICE_FILEFORMAT_50 )
/*?*/       {
/*?*/           if ( pLeftArea )
/*?*/               lcl_StoreOldFields( aEngine, pLeftArea, rStream );
/*?*/           else
/*?*/               pEmpytObj->Store( rStream );
/*?*/
/*?*/           if ( pCenterArea )
/*?*/               lcl_StoreOldFields( aEngine, pCenterArea, rStream );
/*?*/           else
/*?*/               pEmpytObj->Store( rStream );
/*?*/
/*?*/           if ( pRightArea )
/*?*/               lcl_StoreOldFields( aEngine, pRightArea, rStream );
/*?*/           else
/*?*/               pEmpytObj->Store( rStream );
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           (pLeftArea   ? pLeftArea   : pEmpytObj )->Store(rStream);
/*?*/           (pCenterArea ? pCenterArea : pEmpytObj )->Store(rStream);
/*?*/           (pRightArea  ? pRightArea  : pEmpytObj )->Store(rStream);
/*?*/       }
/*?*/
/*?*/       delete pEmpytObj;
/*N*/   }
/*N*/
/*N*/   return rStream;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void __EXPORT ScPageHFItem::SetLeftArea( const EditTextObject& rNew )
/*N*/ {
/*N*/   delete pLeftArea;
/*N*/   pLeftArea = rNew.Clone();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void __EXPORT ScPageHFItem::SetCenterArea( const EditTextObject& rNew )
/*N*/ {
/*N*/   delete pCenterArea;
/*N*/   pCenterArea = rNew.Clone();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void __EXPORT ScPageHFItem::SetRightArea( const EditTextObject& rNew )
/*N*/ {
/*N*/   delete pRightArea;
/*N*/   pRightArea = rNew.Clone();
/*N*/ }

/*N*/ void __EXPORT ScPageHFItem::SetArea( EditTextObject *pNew, int nArea )
/*N*/ {
/*N*/   switch ( nArea )
/*N*/   {
/*N*/       case SC_HF_LEFTAREA:    delete pLeftArea;   pLeftArea   = pNew; break;
/*N*/       case SC_HF_CENTERAREA:  delete pCenterArea; pCenterArea = pNew; break;
/*N*/       case SC_HF_RIGHTAREA:   delete pRightArea;  pRightArea  = pNew; break;
/*N*/       default:
/*N*/           DBG_ERROR( "New Area?" );
/*N*/   }
/*N*/ }

//-----------------------------------------------------------------------
//  ScViewObjectModeItem - Darstellungsmodus von ViewObjekten
//-----------------------------------------------------------------------

/*N*/ ScViewObjectModeItem::ScViewObjectModeItem( USHORT nWhich )
/*N*/   : SfxEnumItem( nWhich, VOBJ_MODE_SHOW )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScViewObjectModeItem::ScViewObjectModeItem( USHORT nWhich, ScVObjMode eMode )
/*N*/   : SfxEnumItem( nWhich, eMode )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScViewObjectModeItem::~ScViewObjectModeItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation __EXPORT ScViewObjectModeItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper* pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  String  aDel = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(": "));
//STRIP001  rText.Erase();
//STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      switch( Which() )
//STRIP001      {
//STRIP001          case SID_SCATTR_PAGE_CHARTS:
//STRIP001          rText  = ScGlobal::GetRscString(STR_VOBJ_CHART);
//STRIP001          rText += aDel;
//STRIP001          break;
//STRIP001
//STRIP001          case SID_SCATTR_PAGE_OBJECTS:
//STRIP001          rText  = ScGlobal::GetRscString(STR_VOBJ_OBJECT);
//STRIP001          rText += aDel;
//STRIP001          break;
//STRIP001
//STRIP001          case SID_SCATTR_PAGE_DRAWINGS:
//STRIP001          rText  = ScGlobal::GetRscString(STR_VOBJ_DRAWINGS);
//STRIP001          rText += aDel;
//STRIP001          break;
//STRIP001
//STRIP001          default:
//STRIP001          ePres = SFX_ITEM_PRESENTATION_NAMELESS;//das geht immer!
//STRIP001          break;
//STRIP001      }
//STRIP001 //       break; // DURCHFALLEN!!!
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      rText += ScGlobal::GetRscString(STR_VOBJ_MODE_SHOW+GetValue());
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  return ePres;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScViewObjectModeItem::GetValueText( USHORT nVal ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( nVal <= VOBJ_MODE_DUMMY, "enum overflow!" );
//STRIP001
//STRIP001  return ScGlobal::GetRscString( STR_VOBJ_MODE_SHOW + nVal );
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ USHORT __EXPORT ScViewObjectModeItem::GetValueCount() const
/*N*/ {
/*N*/   return 3;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScViewObjectModeItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScViewObjectModeItem( *this );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ USHORT __EXPORT ScViewObjectModeItem::GetVersion( USHORT nFileVersion ) const
/*N*/ {
/*N*/   return 1;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScViewObjectModeItem::Create(
/*N*/                                   SvStream&   rStream,
/*N*/                                   USHORT      nVersion ) const
/*N*/ {
/*N*/   if ( nVersion == 0 )
/*N*/   {
/*N*/       // alte Version mit AllEnumItem -> mit Mode "Show" erzeugen
/*N*/       return new ScViewObjectModeItem( Which() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       USHORT nVal;
/*N*/       rStream >> nVal;
/*N*/       return new ScViewObjectModeItem( Which(), (ScVObjMode)nVal );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------
//      double
// -----------------------------------------------------------------------

/*N*/ ScDoubleItem::ScDoubleItem( USHORT nWhich, double nVal )
/*N*/   :   SfxPoolItem ( nWhich ),
/*N*/       nValue  ( nVal )
/*N*/ {
/*N*/ }
/*N*/
//------------------------------------------------------------------------

/*N*/ ScDoubleItem::ScDoubleItem( const ScDoubleItem& rItem )
/*N*/   :   SfxPoolItem ( rItem )
/*N*/ {
/*N*/       nValue = rItem.nValue;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ String __EXPORT ScDoubleItem::GetValueText() const
/*N*/ {
/*N*/   return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScDoubleItem"));
/*N*/ }

//------------------------------------------------------------------------

/*N*/ int __EXPORT ScDoubleItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
/*N*/     const ScDoubleItem& _rItem = (const ScDoubleItem&)rItem;
/*N*/   return int(nValue == _rItem.nValue);
/*N*/         //int(nValue == ((const ScDoubleItem&)rItem).nValue);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScDoubleItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScDoubleItem( *this );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* __EXPORT ScDoubleItem::Create( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   double nTmp=0;
/*N*/   rStream >> nTmp;
/*N*/
/*N*/   ScDoubleItem* pItem = new ScDoubleItem( Which(), nTmp );
/*N*/
/*N*/   return pItem;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvStream& __EXPORT ScDoubleItem::Store( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/   rStream << nValue;
/*N*/
/*N*/   return rStream;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScDoubleItem::~ScDoubleItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------




}
