/*************************************************************************
 *
 *  $RCSfile: sch_schopt.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 12:50:23 $
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

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
// header for SvStream
// auto strip #ifndef _STREAM_HXX
// auto strip #include <tools/stream.hxx>
// auto strip #endif
// header for SAL_STATIC_CAST
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#include "schopt.hxx"

// auto strip #include "cfgids.hxx"
// auto strip #include "defines.hxx"            // for ROW_COLOR_COUNT
#include "schresid.hxx"
#include "strings.hrc"
namespace binfilter {

using namespace ::com::sun::star;

#define SCH_OPTIONS_VERSION_001     USHORT( 1 )

//STRIP001 TYPEINIT1( SchColorTableItem, SfxPoolItem );

// --------------------
// class SchColorTable
// --------------------
/*N*/ SchColorTable::SchColorTable()
/*N*/ {
/*N*/ }

//STRIP001 SchColorTable::SchColorTable( const SchColorTable& rOther ) :
//STRIP001      Table( rOther )
//STRIP001 {
//STRIP001 }

/*N*/ BOOL SchColorTable::Insert( ULONG nKey, XColorEntry* pEntry )
/*N*/ {
/*N*/   return Table::Insert( nKey, (void*)pEntry );
/*N*/ }

//STRIP001 BOOL SchColorTable::RemoveAndDestroy( ULONG nKey )
//STRIP001 {
//STRIP001  XColorEntry* pOldEntry = SAL_STATIC_CAST( XColorEntry*, Table::Remove( nKey ) );
//STRIP001  if( pOldEntry )
//STRIP001  {
//STRIP001      delete pOldEntry;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL SchColorTable::ReplaceAndDestroy( ULONG nKey, XColorEntry* pEntry )
//STRIP001 {
//STRIP001  XColorEntry* pOldEntry = SAL_STATIC_CAST( XColorEntry*, Table::Replace( nKey, (void*)pEntry ) );
//STRIP001  if( pOldEntry )
//STRIP001  {
//STRIP001      delete pOldEntry;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SchColorTable::ClearAndDestroy()
/*N*/ {
/*N*/   for( ULONG i = Count(); i; )
/*N*/       delete Get( --i );
/*N*/   Clear();
/*N*/ }

/*N*/ XColorEntry* SchColorTable::Get( ULONG nKey ) const
/*N*/ {
/*N*/   return SAL_STATIC_CAST( XColorEntry*, Table::Get( nKey ) );
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

//STRIP001 void SchColorTable::UseDefault()
//STRIP001 {
//STRIP001  ColorData aColors[ 12 ] = {
//STRIP001      RGB_COLORDATA( 0x99,  0x99, 0xff ),
//STRIP001      RGB_COLORDATA( 0x99,  0x33, 0x66 ),
//STRIP001      RGB_COLORDATA( 0xff,  0xff, 0xcc ),
//STRIP001      RGB_COLORDATA( 0xcc,  0xff, 0xff ),
//STRIP001      RGB_COLORDATA( 0x66,  0x00, 0x66 ),
//STRIP001      RGB_COLORDATA( 0xff,  0x80, 0x80 ),
//STRIP001      RGB_COLORDATA( 0x00,  0x66, 0xcc ),
//STRIP001      RGB_COLORDATA( 0xcc,  0xcc, 0xff ),
//STRIP001      RGB_COLORDATA( 0x00,  0x00, 0x80 ),
//STRIP001      RGB_COLORDATA( 0xff,  0x00, 0xff ),
//STRIP001      RGB_COLORDATA( 0x00,  0xff, 0xff ),
//STRIP001      RGB_COLORDATA( 0xff,  0xff, 0x00 )
//STRIP001  };
//STRIP001
//STRIP001  ClearAndDestroy();
//STRIP001
//STRIP001  String aResName( SchResId( STR_DIAGRAM_ROW ));
//STRIP001  String aPrefix, aPostfix, aName;
//STRIP001  xub_StrLen nPos = aResName.SearchAscii( "$(ROW)" );
//STRIP001  if( nPos != STRING_NOTFOUND )
//STRIP001  {
//STRIP001      aPrefix = String( aResName, 0, nPos );
//STRIP001      aPostfix = String( aResName, nPos + sizeof( "$(ROW)" ) - 1, STRING_LEN );
//STRIP001  }
//STRIP001  else
//STRIP001      aPrefix = aResName;
//STRIP001
//STRIP001  for( sal_Int32 i=0; i<ROW_COLOR_COUNT; i++ )
//STRIP001  {
//STRIP001      aName = aPrefix;
//STRIP001      aName.Append( String::CreateFromInt32( i + 1 ));
//STRIP001      aName.Append( aPostfix );
//STRIP001
//STRIP001      Insert( i, new XColorEntry( aColors[ i%12 ], aName ) );
//STRIP001  }
//STRIP001 }

// ====================
// class SchOptions
// ====================

/*N*/ SchOptions::SchOptions() :
/*N*/       ::utl::ConfigItem( ::rtl::OUString::createFromAscii( "Office.Chart" )),
/*N*/       mbIsInitialized( FALSE )
/*N*/ {
/*N*/   maPropertyNames.realloc( 1 );
/*N*/   maPropertyNames[ 0 ] = ::rtl::OUString::createFromAscii( "DefaultColor/Series" );
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

//STRIP001 void SchOptions::SetDefaultColors( const SchColorTable& aCol )
//STRIP001 {
//STRIP001  maDefColors = aCol;
//STRIP001  SetModified();
//STRIP001 }

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
/*N*/       String aResName( SchResId( STR_DIAGRAM_ROW ));
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
/*N*/           aCol.SetColor( SAL_STATIC_CAST( ColorData, aColorSeq[ i ] ));
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

//STRIP001 void SchOptions::Commit()
//STRIP001 {
//STRIP001  uno::Sequence< ::rtl::OUString > aNames = GetPropertyNames();
//STRIP001  uno::Sequence< uno::Any > aValues( aNames.getLength());
//STRIP001
//STRIP001  if( aValues.getLength() >= 1 )
//STRIP001  {
//STRIP001      // 1. default colors for series
//STRIP001      // convert list to sequence
//STRIP001      const sal_Int32 nCount = maDefColors.Count();
//STRIP001      uno::Sequence< sal_Int64 > aColors( nCount );
//STRIP001      for( sal_Int32 i=0; i < nCount; i++ )
//STRIP001          aColors[ i ] = maDefColors.GetColorData( i );
//STRIP001
//STRIP001      aValues[ 0 ] <<= aColors;
//STRIP001  }
//STRIP001
//STRIP001  PutProperties( aNames, aValues );
//STRIP001 }

// --------------------
// class SchColorTableItem
// --------------------

//STRIP001 SchColorTableItem::SchColorTableItem( USHORT nWhich, const SchColorTable& aTable ) :
//STRIP001      SfxPoolItem( nWhich ),
//STRIP001      SchColorTable( aTable )
//STRIP001 {
//STRIP001 }

//STRIP001 SchColorTableItem::SchColorTableItem( const SchColorTableItem& rOther ) :
//STRIP001      SfxPoolItem( rOther ),
//STRIP001      SchColorTable( rOther )
//STRIP001 {
//STRIP001 }

//STRIP001 SfxPoolItem* __EXPORT SchColorTableItem::Clone( SfxItemPool *pPool ) const
//STRIP001 {
//STRIP001  return new SchColorTableItem( *this );
//STRIP001 }

//STRIP001 int __EXPORT SchColorTableItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rAttr ), "SchColorTableItem::operator== : types differ" );
//STRIP001
//STRIP001  return SchColorTable::operator==( (const SchColorTable&)(const SchColorTableItem&)rAttr );
//STRIP001 }

//STRIP001 void __EXPORT SchColorTableItem::SetOptions( SchOptions* pOpts ) const
//STRIP001 {
//STRIP001  if( pOpts )
//STRIP001  {
//STRIP001      pOpts->SetDefaultColors( *this );
//STRIP001  }
//STRIP001 }


}
