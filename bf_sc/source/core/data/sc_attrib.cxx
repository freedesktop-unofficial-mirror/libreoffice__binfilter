/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifdef _MSC_VER
#pragma hdrstop
#endif



#include <com/sun/star/util/CellProtection.hpp>

#include "scitems.hxx"
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/boxitem.hxx>
#include <bf_svx/editobj.hxx>



#include <bf_svx/itemdata.hxx>

#include <tools/date.hxx>

#include <tools/time.hxx>

#include <bf_svx/flditem.hxx>

#include "attrib.hxx"
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

/*N*/ ScMergeAttr::~ScMergeAttr()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ int ScMergeAttr::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( Which() != rItem.Which() || Type() == rItem.Type(), "which ==, type !=" );
/*N*/   return (Which() == rItem.Which())
/*N*/            && (nColMerge == ((ScMergeAttr&)rItem).nColMerge)
/*N*/            && (nRowMerge == ((ScMergeAttr&)rItem).nRowMerge);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScMergeAttr::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new ScMergeAttr(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScMergeAttr::Create( SvStream& rStream, USHORT /*nVer*/ ) const
/*N*/ {
/*N*/   INT16   nCol;
/*N*/   INT16   nRow;
/*N*/   rStream >> nCol;
/*N*/   rStream >> nRow;
/*N*/   return new ScMergeAttr(nCol,nRow);
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

/*N*/ ScMergeFlagAttr::~ScMergeFlagAttr()
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

/*N*/ ScProtectionAttr::~ScProtectionAttr()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ bool ScProtectionAttr::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
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
/*N*/             OSL_FAIL("Wrong MemberID!");
/*N*/             return false;
/*N*/     }
/*N*/
/*N*/   return true;
/*N*/ }

/*N*/ bool ScProtectionAttr::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   bool bRet = false;
/*N*/   sal_Bool bVal = sal_False;
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
/*N*/                 bRet = true;
/*N*/             }
/*N*/             else
/*N*/                 OSL_FAIL("exception - wrong argument");
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
/*N*/             OSL_FAIL("Wrong MemberID!");
/*N*/     }
/*N*/
/*N*/   return bRet;
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ int ScProtectionAttr::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( Which() != rItem.Which() || Type() == rItem.Type(), "which ==, type !=" );
/*N*/   return (Which() == rItem.Which())
/*N*/            && (bProtection == ((ScProtectionAttr&)rItem).bProtection)
/*N*/            && (bHideFormula == ((ScProtectionAttr&)rItem).bHideFormula)
/*N*/            && (bHideCell == ((ScProtectionAttr&)rItem).bHideCell)
/*N*/            && (bHidePrint == ((ScProtectionAttr&)rItem).bHidePrint);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScProtectionAttr::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new ScProtectionAttr(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScProtectionAttr::Create( SvStream& rStream, USHORT /*n*/ ) const
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


// -----------------------------------------------------------------------
//      ScRangeItem - Tabellenbereich
// -----------------------------------------------------------------------

/*N*/ int ScRangeItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   return ( aRange == ( (ScRangeItem&)rAttr ).aRange );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* ScRangeItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScRangeItem( *this );
/*N*/ }

//------------------------------------------------------------------------


//-----------------------------------------------------------------------

/*N*/ USHORT ScRangeItem::GetVersion( USHORT /*nFileVersion*/ ) const
/*N*/ {
/*N*/   return 2;
/*N*/ }


/*N*/ SfxPoolItem* ScRangeItem::Create( SvStream& rStream, USHORT nVersion ) const
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
/*N*/           OSL_FAIL( "ScRangeItem::Create: Unknown Version!" );
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

/*N*/ ScTableListItem::~ScTableListItem()
/*N*/ {
/*N*/   delete [] pTabArr;
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ int ScTableListItem::operator==( const SfxPoolItem& rAttr ) const
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

/*N*/ SfxPoolItem* ScTableListItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScTableListItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* ScTableListItem::Create( SvStream& rStrm, USHORT ) const
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
/*N*/   while (( p = (USHORT*)aList.Remove() ))
/*N*/       delete p;
/*N*/
/*N*/   return pNewItem;
/*N*/ }

// -----------------------------------------------------------------------


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
//      ScPageHFItem - Daten der Kopf-/Fu?eilen
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

/*N*/ ScPageHFItem::~ScPageHFItem()
/*N*/ {
/*N*/   delete pLeftArea;
/*N*/   delete pCenterArea;
/*N*/   delete pRightArea;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ bool ScPageHFItem::QueryValue( uno::Any& rVal, BYTE /*nMemberId*/ ) const
/*N*/ {
/*N*/   uno::Reference<sheet::XHeaderFooterContent> xContent =
/*N*/       new ScHeaderFooterContentObj( pLeftArea, pCenterArea, pRightArea );
/*N*/
/*N*/   rVal <<= xContent;
/*N*/   return true;
/*N*/ }

/*N*/ bool ScPageHFItem::PutValue( const uno::Any& rVal, BYTE /*nMemberId*/ )
/*N*/ {
/*N*/   bool bRet = false;
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
/*N*/               bRet = true;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (!bRet)
/*N*/   {
/*N*/       OSL_FAIL("exception - wrong argument");
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ String ScPageHFItem::GetValueText() const
/*N*/ {
/*N*/   return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScPageHFItem"));
/*N*/ }

//------------------------------------------------------------------------

/*N*/ int ScPageHFItem::operator==( const SfxPoolItem& rItem ) const
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

/*N*/ SfxPoolItem* ScPageHFItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScPageHFItem( *this );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ USHORT ScPageHFItem::GetVersion( USHORT /*nFileVersion*/ ) const
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
/*N*/           rEng.QuickInsertField( SvxFieldItem(SvxDateField(Date( Date::SYSTEM),SVXDATETYPE_VAR)), aSel );
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

/*N*/ SfxPoolItem* ScPageHFItem::Create( SvStream& rStream, USHORT nVer ) const
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

/*N*/ void ScPageHFItem::SetLeftArea( const EditTextObject& rNew )
/*N*/ {
/*N*/   delete pLeftArea;
/*N*/   pLeftArea = rNew.Clone();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScPageHFItem::SetCenterArea( const EditTextObject& rNew )
/*N*/ {
/*N*/   delete pCenterArea;
/*N*/   pCenterArea = rNew.Clone();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScPageHFItem::SetRightArea( const EditTextObject& rNew )
/*N*/ {
/*N*/   delete pRightArea;
/*N*/   pRightArea = rNew.Clone();
/*N*/ }

/*N*/ void ScPageHFItem::SetArea( EditTextObject *pNew, int nArea )
/*N*/ {
/*N*/   switch ( nArea )
/*N*/   {
/*N*/       case SC_HF_LEFTAREA:    delete pLeftArea;   pLeftArea   = pNew; break;
/*N*/       case SC_HF_CENTERAREA:  delete pCenterArea; pCenterArea = pNew; break;
/*N*/       case SC_HF_RIGHTAREA:   delete pRightArea;  pRightArea  = pNew; break;
/*N*/       default:
/*N*/           OSL_FAIL( "New Area?" );
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

/*N*/ ScViewObjectModeItem::~ScViewObjectModeItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------


//------------------------------------------------------------------------

/*N*/ USHORT ScViewObjectModeItem::GetValueCount() const
/*N*/ {
/*N*/   return 3;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScViewObjectModeItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScViewObjectModeItem( *this );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ USHORT ScViewObjectModeItem::GetVersion( USHORT /*nFileVersion*/ ) const
/*N*/ {
/*N*/   return 1;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScViewObjectModeItem::Create(
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

/*N*/ String ScDoubleItem::GetValueText() const
/*N*/ {
/*N*/   return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScDoubleItem"));
/*N*/ }

//------------------------------------------------------------------------

/*N*/ int ScDoubleItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
/*N*/     const ScDoubleItem& _rItem = (const ScDoubleItem&)rItem;
/*N*/   return int(nValue == _rItem.nValue);
/*N*/         //int(nValue == ((const ScDoubleItem&)rItem).nValue);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScDoubleItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new ScDoubleItem( *this );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* ScDoubleItem::Create( SvStream& rStream, USHORT /*nVer*/ ) const
/*N*/ {
/*N*/   double nTmp=0;
/*N*/   rStream >> nTmp;
/*N*/
/*N*/   ScDoubleItem* pItem = new ScDoubleItem( Which(), nTmp );
/*N*/
/*N*/   return pItem;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScDoubleItem::~ScDoubleItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
