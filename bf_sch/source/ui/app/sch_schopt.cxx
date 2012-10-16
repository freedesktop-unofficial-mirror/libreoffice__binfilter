/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <com/sun/star/uno/Sequence.hxx>

#include "schopt.hxx"

#include "schresid.hxx"
#include "strings.hrc"
namespace binfilter {

using namespace ::com::sun::star;

#define SCH_OPTIONS_VERSION_001     USHORT( 1 )


// --------------------
// class SchColorTable
// --------------------
/*N*/ SchColorTable::SchColorTable()
/*N*/ {
/*N*/ }


/*N*/ BOOL SchColorTable::Insert( ULONG nKey, XColorEntry* pEntry )
/*N*/ {
/*N*/   return Table::Insert( nKey, (void*)pEntry );
/*N*/ }



/*N*/ void SchColorTable::ClearAndDestroy()
/*N*/ {
/*N*/   for( ULONG i = Count(); i; )
/*N*/       delete Get( --i );
/*N*/   Clear();
/*N*/ }

/*N*/ XColorEntry* SchColorTable::Get( ULONG nKey ) const
/*N*/ {
/*N*/   return (static_cast< XColorEntry* >(Table::Get( nKey )) );
/*N*/ }

/*N*/ Color SchColorTable::GetColor( ULONG nKey ) const
/*N*/ {
/*N*/   XColorEntry* pEntry = Get( nKey );
/*N*/   if( pEntry )
/*N*/       return pEntry->GetColor();
/*N*/
/*N*/   return COL_BLACK;
/*N*/ }

/*N*/ ColorData SchColorTable::GetColorData( ULONG nKey ) const
/*N*/ {
/*N*/   return GetColor( nKey ).GetRGBColor();
/*N*/ }


// ====================
// class SchOptions
// ====================

/*N*/ SchOptions::SchOptions() :
/*N*/       ::utl::ConfigItem( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Office.Chart" ))),
/*N*/       mbIsInitialized( FALSE )
/*N*/ {
/*N*/   maPropertyNames.realloc( 1 );
/*N*/   maPropertyNames[ 0 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DefaultColor/Series" ));
/*N*/ }

/*N*/ SchOptions::~SchOptions()
/*N*/ {
/*N*/   maDefColors.ClearAndDestroy();
/*N*/ }

/*N*/ const SchColorTable& SchOptions::GetDefaultColors()
/*N*/ {
/*N*/   if( ! mbIsInitialized )
/*N*/   {
/*N*/       mbIsInitialized = RetrieveOptions();
/*N*/   }
/*N*/
/*N*/   return maDefColors;
/*N*/ }


/*N*/ BOOL SchOptions::RetrieveOptions()
/*N*/ {
/*N*/   // get sequence containing all properties
/*N*/
/*N*/   uno::Sequence< ::rtl::OUString > aNames = GetPropertyNames();
/*N*/   uno::Sequence< uno::Any > aProperties( aNames.getLength());
/*N*/   aProperties = GetProperties( aNames );
/*N*/
/*N*/   if( aProperties.getLength() == aNames.getLength())
/*N*/   {
/*N*/       // 1. default colors for series
/*N*/       maDefColors.ClearAndDestroy();
/*N*/       uno::Sequence< sal_Int64 > aColorSeq;
/*N*/       aProperties[ 0 ] >>= aColorSeq;
/*N*/
/*N*/       sal_Int32 nCount = aColorSeq.getLength();
/*N*/       Color aCol;
/*N*/
/*N*/       // create strings for entry names
/*N*/       String aResName( SchResId( STR_DIAGRAM_ROW ).toString() );
/*N*/       String aPrefix, aPostfix, aName;
/*N*/       xub_StrLen nPos = aResName.SearchAscii( "$(ROW)" );
/*N*/       if( nPos != STRING_NOTFOUND )
/*N*/       {
/*N*/           aPrefix = String( aResName, 0, nPos );
/*N*/           aPostfix = String( aResName, nPos + sizeof( "$(ROW)" ) - 1, STRING_LEN );
/*N*/       }
/*N*/       else
/*?*/           aPrefix = aResName;
/*N*/
/*N*/       // set color values
/*N*/       for( sal_Int32 i=0; i < nCount; i++ )
/*N*/       {
/*N*/           aCol.SetColor( (static_cast< ColorData >( aColorSeq[ i ] ) ));
/*N*/
/*N*/           aName = aPrefix;
/*N*/           aName.Append( String::CreateFromInt32( i + 1 ));
/*N*/           aName.Append( aPostfix );
/*N*/
/*N*/           maDefColors.Insert( i, new XColorEntry( aCol, aName ) );
/*N*/       }
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

void SchOptions::Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& /*rPropertyNames*/ ) {}
void SchOptions::Commit() {}


// --------------------
// class SchColorTableItem
// --------------------







}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
