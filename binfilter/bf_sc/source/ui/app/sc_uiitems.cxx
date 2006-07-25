/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_uiitems.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-07-25 08:03:44 $
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

#pragma hdrstop


#include "userlist.hxx"
#include "uiitems.hxx"
#include "dpsave.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

/*N*/ TYPEINIT1(ScSortItem,           SfxPoolItem);
/*N*/ TYPEINIT1(ScQueryItem,          SfxPoolItem);
/*N*/ TYPEINIT1(ScSubTotalItem,       SfxPoolItem);
/*N*/ TYPEINIT1(ScUserListItem,       SfxPoolItem);
/*N*/ TYPEINIT1(ScConsolidateItem,    SfxPoolItem);
/*N*/ TYPEINIT1(ScPivotItem,            SfxPoolItem);
/*N*/ TYPEINIT1(ScSolveItem,            SfxPoolItem);

/*N*/ TYPEINIT1(ScTablesHint,           SfxHint);
/*N*/ TYPEINIT1(ScEditViewHint,     SfxHint);
/*N*/ TYPEINIT1(ScIndexHint,            SfxHint);


// -----------------------------------------------------------------------
//  ScTablesHint - Views anpassen, wenn Tabellen eingefuegt / geloescht
// -----------------------------------------------------------------------

/*N*/ ScTablesHint::ScTablesHint(USHORT nNewId, USHORT nTable1, USHORT nTable2) :
/*N*/   nId( nNewId ),
/*N*/   nTab1( nTable1 ),
/*N*/   nTab2( nTable2 )
/*N*/ {
/*N*/ }

/*N*/ ScTablesHint::~ScTablesHint()
/*N*/ {
/*N*/ }


// -----------------------------------------------------------------------
//  ScIndexHint
// -----------------------------------------------------------------------

/*N*/ ScIndexHint::ScIndexHint(USHORT nNewId, USHORT nIdx) :
/*N*/   nId( nNewId ),
/*N*/   nIndex( nIdx )
/*N*/ {
/*N*/ }

/*N*/ ScIndexHint::~ScIndexHint()
/*N*/ {
/*N*/ }


// -----------------------------------------------------------------------
//      ScEditViewHint - neue EditView fuer Cursorposition anlegen
// -----------------------------------------------------------------------

/*N*/ ScEditViewHint::ScEditViewHint() :
/*N*/   aCursorPos( 0,0,0 ),
/*N*/   pEditEngine( NULL )
/*N*/ {
/*N*/ }

/*N*/ ScEditViewHint::ScEditViewHint( ScEditEngineDefaulter* pEngine, const ScAddress& rCurPos ) :
/*N*/   aCursorPos( rCurPos ),
/*N*/   pEditEngine( pEngine )
/*N*/ {
/*N*/ }

/*N*/ ScEditViewHint::~ScEditViewHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScSortItem - Daten fuer den Sortierdialog
// -----------------------------------------------------------------------

/*N*/ ScSortItem::ScSortItem( USHORT              nWhich,
/*N*/                       ScViewData*         ptrViewData,
/*N*/                       const ScSortParam*  pSortData ) :
/*N*/       SfxPoolItem ( nWhich ),
/*N*/       pViewData   ( ptrViewData )
/*N*/ {
/*N*/   if ( pSortData ) theSortData = *pSortData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSortItem::ScSortItem( USHORT              nWhich,
/*N*/                       const ScSortParam*  pSortData ) :
/*N*/       SfxPoolItem ( nWhich ),
/*N*/       pViewData   ( NULL )
/*N*/ {
/*N*/   if ( pSortData ) theSortData = *pSortData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSortItem::ScSortItem( const ScSortItem& rItem ) :
/*N*/       SfxPoolItem ( rItem ),
/*N*/       pViewData   ( rItem.pViewData ),
/*N*/       theSortData ( rItem.theSortData )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScSortItem::~ScSortItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScSortItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("SortItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScSortItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScSortItem& rOther = (const ScSortItem&)rItem;
//STRIP001
//STRIP001  return (   (pViewData   == rOther.pViewData)
//STRIP001          && (theSortData == rOther.theSortData) );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScSortItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScSortItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------
//      ScQueryItem - Daten fuer den Filterdialog
// -----------------------------------------------------------------------

/*N*/ ScQueryItem::ScQueryItem( USHORT                nWhich,
/*N*/                         ScViewData*           ptrViewData,
/*N*/                         const ScQueryParam*   pQueryData ) :
/*N*/       SfxPoolItem ( nWhich ),
/*N*/       bIsAdvanced ( FALSE ),
/*N*/       pViewData   ( ptrViewData )
/*N*/ {
/*N*/   if ( pQueryData ) theQueryData = *pQueryData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScQueryItem::ScQueryItem( USHORT                nWhich,
/*N*/                         const ScQueryParam*   pQueryData ) :
/*N*/       SfxPoolItem ( nWhich ),
/*N*/       bIsAdvanced ( FALSE ),
/*N*/       pViewData   ( NULL )
/*N*/ {
/*N*/   if ( pQueryData ) theQueryData = *pQueryData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScQueryItem::ScQueryItem( const ScQueryItem& rItem ) :
/*N*/       SfxPoolItem ( rItem ),
/*N*/       bIsAdvanced ( rItem.bIsAdvanced ),
/*N*/       aAdvSource  ( rItem.aAdvSource ),
/*N*/       pViewData   ( rItem.pViewData ),
/*N*/       theQueryData( rItem.theQueryData )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScQueryItem::~ScQueryItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 void ScQueryItem::SetAdvancedQuerySource(const ScRange* pSource)
//STRIP001 {
//STRIP001  if (pSource)
//STRIP001  {
//STRIP001      aAdvSource = *pSource;
//STRIP001      bIsAdvanced = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      bIsAdvanced = FALSE;
//STRIP001 }

//STRIP001 BOOL ScQueryItem::GetAdvancedQuerySource(ScRange& rSource) const
//STRIP001 {
//STRIP001  rSource = aAdvSource;
//STRIP001  return bIsAdvanced;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScQueryItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("QueryItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScQueryItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScQueryItem& rQueryItem = (const ScQueryItem&)rItem;
//STRIP001
//STRIP001  return (   (pViewData    == rQueryItem.pViewData)
//STRIP001          && (bIsAdvanced  == rQueryItem.bIsAdvanced)
//STRIP001          && (aAdvSource   == rQueryItem.aAdvSource)
//STRIP001          && (theQueryData == rQueryItem.theQueryData) );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScQueryItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScQueryItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------
//      ScSubTotalItem - Daten fuer den Zwischenergebnisdialog
// -----------------------------------------------------------------------

/*N*/ ScSubTotalItem::ScSubTotalItem( USHORT                nWhich,
/*N*/                               ScViewData*             ptrViewData,
/*N*/                               const ScSubTotalParam*  pSubTotalData ) :
/*N*/       SfxPoolItem ( nWhich ),
/*N*/       pViewData   ( ptrViewData )
/*N*/ {
/*N*/   if ( pSubTotalData ) theSubTotalData = *pSubTotalData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSubTotalItem::ScSubTotalItem( USHORT                nWhich,
/*N*/                               const ScSubTotalParam*  pSubTotalData ) :
/*N*/       SfxPoolItem ( nWhich ),
/*N*/       pViewData   ( NULL )
/*N*/ {
/*N*/   if ( pSubTotalData ) theSubTotalData = *pSubTotalData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSubTotalItem::ScSubTotalItem( const ScSubTotalItem& rItem ) :
/*N*/       SfxPoolItem     ( rItem ),
/*N*/       pViewData       ( rItem.pViewData ),
/*N*/       theSubTotalData ( rItem.theSubTotalData )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScSubTotalItem::~ScSubTotalItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScSubTotalItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("SubTotalItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScSubTotalItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScSubTotalItem& rSTItem = (const ScSubTotalItem&)rItem;
//STRIP001
//STRIP001  return (   (pViewData       == rSTItem.pViewData)
//STRIP001          && (theSubTotalData == rSTItem.theSubTotalData) );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScSubTotalItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScSubTotalItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------
//      ScUserListItem - Transporter fuer den Benutzerlisten-TabPage
// -----------------------------------------------------------------------

/*N*/ ScUserListItem::ScUserListItem( USHORT nWhich )
/*N*/   :   SfxPoolItem ( nWhich ),
/*N*/       pUserList   ( NULL )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScUserListItem::ScUserListItem( const ScUserListItem& rItem )
/*N*/   :   SfxPoolItem ( rItem )
/*N*/ {
/*N*/   if ( rItem.pUserList )
/*N*/       pUserList = new ScUserList( *(rItem.pUserList) );
/*N*/   else
/*N*/       pUserList = NULL;
/*N*/ }

/*N*/ __EXPORT ScUserListItem::~ScUserListItem()
/*N*/ {
/*N*/   delete pUserList;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScUserListItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScUserListItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScUserListItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScUserListItem& r = (const ScUserListItem&)rItem;
//STRIP001  BOOL bEqual = FALSE;
//STRIP001
//STRIP001  if ( !pUserList || !(r.pUserList) )
//STRIP001      bEqual = ( !pUserList && !(r.pUserList) );
//STRIP001  else
//STRIP001      bEqual = ( *pUserList == *(r.pUserList) );
//STRIP001
//STRIP001  return bEqual;
//STRIP001 }


//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScUserListItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScUserListItem( *this );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScUserListItem::SetUserList( const ScUserList& rUserList )
//STRIP001 {
//STRIP001  delete pUserList;
//STRIP001  pUserList = new ScUserList( rUserList );
//STRIP001 }

// -----------------------------------------------------------------------
//      ScConsolidateItem - Daten fuer den Konsolidieren-Dialog
// -----------------------------------------------------------------------

/*N*/ ScConsolidateItem::ScConsolidateItem(
/*N*/                           USHORT                      nWhich,
/*N*/                           const ScConsolidateParam*   pConsolidateData ) :
/*N*/       SfxPoolItem ( nWhich )
/*N*/ {
/*N*/   if ( pConsolidateData ) theConsData = *pConsolidateData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScConsolidateItem::ScConsolidateItem( const ScConsolidateItem& rItem ) :
/*N*/       SfxPoolItem ( rItem ),
/*N*/       theConsData ( rItem.theConsData )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScConsolidateItem::~ScConsolidateItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScConsolidateItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScConsolidateItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScConsolidateItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScConsolidateItem& rCItem = (const ScConsolidateItem&)rItem;
//STRIP001
//STRIP001  return ( theConsData == rCItem.theConsData);
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScConsolidateItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScConsolidateItem( *this );
//STRIP001 }


// -----------------------------------------------------------------------
//      ScPivotItem - Daten fuer den Pivot-Dialog
// -----------------------------------------------------------------------

/*N*/ ScPivotItem::ScPivotItem( USHORT nWhich, const ScDPSaveData* pData,
/*N*/                            const ScRange* pRange, BOOL bNew ) :
/*N*/       SfxPoolItem ( nWhich )
/*N*/ {
/*N*/   //  pSaveData must always exist
/*N*/   if ( pData )
/*?*/       pSaveData = new ScDPSaveData(*pData);
/*N*/   else
/*N*/       pSaveData = new ScDPSaveData;
/*N*/   if ( pRange ) aDestRange = *pRange;
/*N*/   bNewSheet = bNew;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScPivotItem::ScPivotItem( const ScPivotItem& rItem ) :
/*N*/       SfxPoolItem ( rItem ),
/*N*/       aDestRange  ( rItem.aDestRange ),
/*N*/       bNewSheet   ( rItem.bNewSheet )
/*N*/ {
/*N*/   DBG_ASSERT(rItem.pSaveData, "pSaveData");
/*N*/   pSaveData = new ScDPSaveData(*rItem.pSaveData);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScPivotItem::~ScPivotItem()
/*N*/ {
/*N*/   delete pSaveData;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScPivotItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScPivotItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScPivotItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScPivotItem& rPItem = (const ScPivotItem&)rItem;
//STRIP001  DBG_ASSERT( pSaveData && rPItem.pSaveData, "pSaveData" );
//STRIP001  return ( *pSaveData == *rPItem.pSaveData &&
//STRIP001           aDestRange == rPItem.aDestRange &&
//STRIP001           bNewSheet  == rPItem.bNewSheet );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScPivotItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScPivotItem( *this );
//STRIP001 }


// -----------------------------------------------------------------------
//      ScSolveItem - Daten fuer den Solver-Dialog
// -----------------------------------------------------------------------

/*N*/ ScSolveItem::ScSolveItem( USHORT              nWhich,
/*N*/                         const ScSolveParam*   pSolveData )
/*N*/   :   SfxPoolItem ( nWhich )
/*N*/ {
/*N*/   if ( pSolveData ) theSolveData = *pSolveData;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSolveItem::ScSolveItem( const ScSolveItem& rItem )
/*N*/   :   SfxPoolItem     ( rItem ),
/*N*/       theSolveData    ( rItem.theSolveData )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScSolveItem::~ScSolveItem()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String __EXPORT ScSolveItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("ScSolveItem"));
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int __EXPORT ScSolveItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScSolveItem& rPItem = (const ScSolveItem&)rItem;
//STRIP001
//STRIP001  return ( theSolveData == rPItem.theSolveData );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT ScSolveItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScSolveItem( *this );
//STRIP001 }
}
