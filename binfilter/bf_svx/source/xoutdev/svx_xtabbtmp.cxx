/*************************************************************************
 *
 *  $RCSfile: svx_xtabbtmp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:46 $
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

#ifndef SVX_LIGHT

#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _SVX_XPROPERTYTABLE_HXX
#include "XPropertyTable.hxx"
#endif

#ifndef _UNTOOLS_UCBSTREAMHELPER_HXX
#include <unotools/ucbstreamhelper.hxx>
#endif

#include "xmlxtexp.hxx"
#include "xmlxtimp.hxx"

#endif

#include <tools/urlobj.hxx>
#include <vcl/virdev.hxx>
#include <svtools/itemset.hxx>
#include <bf_sfx2/docfile.hxx>
#include "dialogs.hrc"
#include "dialmgr.hxx"
#include "xtable.hxx"
#include "xiocomp.hxx"
#include "xpool.hxx"
#include "xoutx.hxx"
namespace binfilter {

#define GLOBALOVERFLOW

using namespace ::com::sun::star;
using namespace rtl;

sal_Unicode const pszExtBitmap[]  = {'s','o','b'};

static char const aChckBitmap[]  = { 0x04, 0x00, 'S','O','B','L'};  // very old
static char const aChckBitmap0[] = { 0x04, 0x00, 'S','O','B','0'};  // old
static char const aChckBitmap1[] = { 0x04, 0x00, 'S','O','B','1'};  // = 5.2
static char const aChckXML[]     = { 'P', 'K', 0x03, 0x04 };        // = 6.0

// -------------------
// class XBitmapTable
// -------------------

/*************************************************************************
|*
|* XBitmapTable::XBitmapTable()
|*
*************************************************************************/

/*N*/ XBitmapTable::XBitmapTable( const String& rPath,
/*N*/                           XOutdevItemPool* pInPool,
/*N*/                           USHORT nInitSize, USHORT nReSize ) :
/*N*/               XPropertyTable( rPath, pInPool, nInitSize, nReSize)
/*N*/ {
/*N*/   pBmpTable = new Table( nInitSize, nReSize );
/*N*/ }

/************************************************************************/

/*N*/ XBitmapTable::~XBitmapTable()
/*N*/ {
/*N*/ }

/************************************************************************/

/*N*/ XBitmapEntry* XBitmapTable::Replace(long nIndex, XBitmapEntry* pEntry )
/*N*/ {
/*N*/   return (XBitmapEntry*) XPropertyTable::Replace(nIndex, pEntry);
/*N*/ }

/************************************************************************/

/*N*/ XBitmapEntry* XBitmapTable::Remove(long nIndex)
/*N*/ {
/*N*/   return (XBitmapEntry*) XPropertyTable::Remove(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ XBitmapEntry* XBitmapTable::Get(long nIndex) const
/*N*/ {
/*N*/   return (XBitmapEntry*) XPropertyTable::Get(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapTable::Load()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapTable::Save()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapTable::Create()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapTable::CreateBitmapsForUI()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ Bitmap* XBitmapTable::CreateBitmapForUI( long nIndex, BOOL bDelete )
/*N*/ {
/*N*/   return( NULL );
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XBitmapTable::ImpStore( SvStream& rOut )
/*N*/ {
/*N*/   // Schreiben
/*N*/   rOut.SetStreamCharSet( gsl_getSystemTextEncoding() );
/*N*/
/*N*/   // Tabellentyp schreiben (0 = gesamte Tabelle)
/*N*/   // Version statt Tabellentyp, um auch alte Tabellen zu lesen
/*N*/   rOut << (long) -1;
/*N*/
/*N*/   // Anzahl der Eintraege
/*N*/   rOut << (long)Count();
/*N*/
/*N*/   // die Eintraege
/*N*/   XBitmapEntry* pEntry = (XBitmapEntry*)aTable.First();
/*N*/
/*N*/   for (long nIndex = 0; nIndex < Count(); nIndex++)
/*N*/   {
/*N*/       // Versionsverwaltung: Version 0
/*N*/       XIOCompat aIOC( rOut, STREAM_WRITE, 0 );
/*N*/
/*N*/       rOut << (long)aTable.GetCurKey();
/*N*/
/*N*/       // UNICODE: rOut << pEntry->GetName();
/*N*/       rOut.WriteByteString(pEntry->GetName());
/*N*/
/*N*/       rOut << pEntry->GetXBitmap().GetBitmap();
/*N*/       pEntry = (XBitmapEntry*)aTable.Next();
/*N*/   }
/*N*/
/*N*/   return rOut;
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XBitmapTable::ImpRead( SvStream& rIn )
/*N*/ {
/*N*/   // Lesen
/*N*/   rIn.SetStreamCharSet( RTL_TEXTENCODING_IBM_850 );
/*N*/
/*N*/   delete pBmpTable;
/*N*/   pBmpTable = new Table( 16, 16 );
/*N*/
/*N*/   XBitmapEntry* pEntry = NULL;
/*N*/   long        nType;
/*N*/   long        nCount;
/*N*/   long        nIndex;
/*N*/   String      aName;
/*N*/   Bitmap      aBitmap;
/*N*/
/*N*/   rIn >> nType;
/*N*/
/*N*/   // gesamte Tabelle?
/*N*/   if (nType == 0)
/*N*/   {
/*N*/       rIn >> nCount;
/*N*/       for (long nI = 0; nI < nCount; nI++)
/*N*/       {
/*N*/           rIn >> nIndex;
/*N*/
/*N*/           // UNICODE: rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           rIn >> aBitmap;
/*N*/
/*N*/           pEntry = new XBitmapEntry (aBitmap, aName);
/*N*/           Insert (nIndex, pEntry);
/*N*/       }
/*N*/   }
/*N*/   else // Version ab 3.00a
/*N*/   {
/*N*/       rIn >> nCount;
/*N*/       for (long nI = 0; nI < nCount; nI++)
/*N*/       {
/*N*/           // Versionsverwaltung
/*N*/           XIOCompat aIOC( rIn, STREAM_READ );
/*N*/
/*N*/           rIn >> nIndex;
/*N*/
/*N*/           // UNICODE: rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           rIn >> aBitmap;
/*N*/
/*N*/           if (aIOC.GetVersion() > 0)
/*N*/           {
/*N*/               // lesen neuer Daten ...
/*N*/           }
/*N*/
/*N*/           pEntry = new XBitmapEntry (aBitmap, aName);
/*N*/           Insert (nIndex, pEntry);
/*N*/       }
/*N*/   }
/*N*/   return( rIn );
/*N*/ }

// ------------------
// class XBitmapList
// ------------------

/*************************************************************************
|*
|* XBitmapList::XBitmapList()
|*
*************************************************************************/

/*N*/ XBitmapList::XBitmapList( const String& rPath,
/*N*/                           XOutdevItemPool* pInPool,
/*N*/                           USHORT nInitSize, USHORT nReSize ) :
/*N*/               XPropertyList( rPath, pInPool, nInitSize, nReSize)
/*N*/ {
    // pBmpList = new List( nInitSize, nReSize );
/*N*/ }

/************************************************************************/

/*N*/ XBitmapList::~XBitmapList()
/*N*/ {
/*N*/ }

/************************************************************************/

/*N*/ XBitmapEntry* XBitmapList::Replace(XBitmapEntry* pEntry, long nIndex )
/*N*/ {
/*N*/   return (XBitmapEntry*) XPropertyList::Replace(pEntry, nIndex);
/*N*/ }

/************************************************************************/

/*N*/ XBitmapEntry* XBitmapList::Remove(long nIndex)
/*N*/ {
/*N*/   return (XBitmapEntry*) XPropertyList::Remove(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ XBitmapEntry* XBitmapList::Get(long nIndex) const
/*N*/ {
/*N*/   return (XBitmapEntry*) XPropertyList::Get(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapList::Load()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if( bListDirty )
/*N*/   {
/*N*/       bListDirty = FALSE;
/*N*/
/*N*/       INetURLObject aURL( aPath );
/*N*/
/*N*/       if( INET_PROT_NOT_VALID == aURL.GetProtocol() )
/*N*/       {
/*N*/           DBG_ASSERT( !aPath.Len(), "invalid URL" );
/*N*/           return FALSE;
/*N*/       }
/*N*/
/*N*/       aURL.Append( aName );
/*N*/
/*N*/       if( !aURL.getExtension().Len() )
/*N*/           aURL.setExtension( String( pszExtBitmap, 3 ) );
/*N*/
/*N*/       // check if file exists, SfxMedium shows an errorbox else
/*N*/       {
/*N*/           ::com::sun::star::uno::Reference < ::com::sun::star::task::XInteractionHandler > xHandler;
/*N*/           SvStream* pIStm = ::utl::UcbStreamHelper::CreateStream( aURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_READ, xHandler );
/*N*/
/*N*/           sal_Bool bOk = pIStm && ( pIStm->GetError() == 0);
/*N*/
/*N*/           if( pIStm )
/*N*/               delete pIStm;
/*N*/
/*N*/           if( !bOk )
/*N*/               return sal_False;
/*N*/       }
/*N*/
/*N*/       {
/*N*/           SfxMedium aMedium( aURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_READ | STREAM_NOCREATE, TRUE );
/*N*/
/*N*/           SvStream* pStream = aMedium.GetInStream();
/*N*/           if( !pStream )
/*N*/               return( FALSE );
/*N*/
/*N*/           char aCheck[6];
/*N*/           pStream->Read( aCheck, 6 );
/*N*/
/*N*/           // Handelt es sich um die gew"unschte Tabelle?
/*N*/           if( memcmp( aCheck, aChckBitmap, sizeof( aChckBitmap ) ) == 0 ||
/*N*/               memcmp( aCheck, aChckBitmap0, sizeof( aChckBitmap0 ) ) == 0 ||
/*N*/               memcmp( aCheck, aChckBitmap1, sizeof( aChckBitmap1 ) ) == 0 )
/*N*/           {
/*N*/               ImpRead( *pStream );
/*N*/               return( pStream->GetError() == SVSTREAM_OK );
/*N*/           }
/*N*/           else if( memcmp( aCheck, aChckXML, sizeof( aChckXML ) ) != 0 )
/*N*/           {
/*N*/               return FALSE;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       uno::Reference< container::XNameContainer > xTable( SvxUnoXBitmapTable_createInstance( this ), uno::UNO_QUERY );
/*N*/       return SvxXMLXTableImport::load( aURL.GetMainURL( INetURLObject::NO_DECODE ), xTable );
/*N*/   }
/*N*/ #endif
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapList::Save()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return false;//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001
//STRIP001  INetURLObject aURL( aPath );
//STRIP001
//STRIP001  if( INET_PROT_NOT_VALID == aURL.GetProtocol() )
//STRIP001  {
//STRIP001      DBG_ASSERT( !aPath.Len(), "invalid URL" );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  aURL.Append( aName );
//STRIP001
//STRIP001  if( !aURL.getExtension().Len() )
//STRIP001      aURL.setExtension( String( pszExtBitmap, 3 ) );
//STRIP001
//STRIP001  uno::Reference< container::XNameContainer > xTable( SvxUnoXBitmapTable_createInstance( this ), uno::UNO_QUERY );
//STRIP001  return SvxXMLXTableExportComponent::save( aURL.GetMainURL( INetURLObject::NO_DECODE ), xTable );
//STRIP001
/*
    SfxMedium aMedium( aURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_WRITE | STREAM_TRUNC, TRUE );
    aMedium.IsRemote();

    SvStream* pStream = aMedium.GetOutStream();
    if( !pStream )
        return( FALSE );

    // UNICODE: *pStream << String( pszChckBitmap1, 4 );
    pStream->WriteByteString(String( pszChckBitmap1, 4 ));
    ImpStore( *pStream );

    aMedium.Close();
    aMedium.Commit();

    return( aMedium.GetError() == 0 );
*/
//STRIP001 #else
//STRIP001  return FALSE;
//STRIP001 #endif
/*N*/ }

/************************************************************************/
// Umgestellt am 27.07.95 auf XBitmap

/*N*/ BOOL XBitmapList::Create()
/*N*/ {
/*N*/   // Array der Bitmap
/*N*/   //-----------------------
/*N*/   // 00 01 02 03 04 05 06 07
/*N*/   // 08 09 10 11 12 13 14 15
/*N*/   // 16 17 18 19 20 21 22 23
/*N*/   // 24 25 26 27 28 29 30 31
/*N*/   // 32 33 34 35 36 37 38 39
/*N*/   // 40 41 42 43 44 45 46 47
/*N*/   // 48 49 50 51 52 53 54 55
/*N*/   // 56 57 58 59 60 61 62 63
/*N*/
/*N*/   String  aStr( SVX_RES( RID_SVXSTR_BITMAP ) );
/*N*/   Color   aColWhite( RGB_Color( COL_WHITE ) );
/*N*/   xub_StrLen nLen;
/*N*/   USHORT  aArray[64];
/*N*/
/*N*/   memset( aArray, 0, sizeof( aArray ) );
/*N*/   aStr.AppendAscii(" 1");
/*N*/   nLen = aStr.Len() - 1;
/*N*/   Insert( new XBitmapEntry( XOBitmap( aArray, aColWhite, aColWhite ), aStr ) );
/*N*/
/*N*/   aArray[ 0] = 1; aArray[ 9] = 1; aArray[18] = 1; aArray[27] = 1;
/*N*/   aArray[36] = 1; aArray[45] = 1; aArray[54] = 1; aArray[63] = 1;
/*N*/   aStr.SetChar(nLen, sal_Unicode('2'));
/*N*/   Insert( new XBitmapEntry( XOBitmap( aArray, RGB_Color( COL_BLACK ), aColWhite ), aStr ) );
/*N*/
/*N*/   aArray[ 7] = 1; aArray[14] = 1; aArray[21] = 1; aArray[28] = 1;
/*N*/   aArray[35] = 1; aArray[42] = 1; aArray[49] = 1; aArray[56] = 1;
/*N*/   aStr.SetChar(nLen, sal_Unicode('3'));
/*N*/   Insert( new XBitmapEntry( XOBitmap( aArray, RGB_Color( COL_LIGHTRED ), aColWhite ), aStr ) );
/*N*/
/*N*/   aArray[24] = 1; aArray[25] = 1; aArray[26] = 1;
/*N*/   aArray[29] = 1; aArray[30] = 1; aArray[31] = 1;
/*N*/   aStr.SetChar(nLen, sal_Unicode('4'));
/*N*/   Insert( new XBitmapEntry( XOBitmap( aArray, RGB_Color( COL_LIGHTBLUE ), aColWhite ), aStr ) );
/*N*/
/*N*/   return( TRUE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XBitmapList::CreateBitmapsForUI()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ Bitmap* XBitmapList::CreateBitmapForUI( long nIndex, BOOL bDelete )
/*N*/ {
/*N*/   return( NULL );
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XBitmapList::ImpStore( SvStream& rOut )
/*N*/ {
/*N*/   // Schreiben
/*N*/   rOut.SetStreamCharSet( gsl_getSystemTextEncoding() );
/*N*/
/*N*/   // Version !!!
/*N*/   rOut << (long)-2;
/*N*/
/*N*/   // Anzahl der Eintraege
/*N*/   rOut << (long)Count();
/*N*/
/*N*/   // die Eintraege
/*N*/   XBitmapEntry* pEntry = NULL;
/*N*/
/*N*/   for (long nIndex = 0; nIndex < Count(); nIndex++)
/*N*/   {
/*N*/       // Versionsverwaltung: Version 0
/*N*/       XIOCompat aIOC( rOut, STREAM_WRITE, 0 );
/*N*/
/*N*/       pEntry = Get(nIndex);
/*N*/       XOBitmap aXOBitmap( pEntry->GetXBitmap() );
/*N*/
/*N*/       // UNICODE: rOut << pEntry->GetName();
/*N*/       rOut.WriteByteString(pEntry->GetName());
/*N*/
/*N*/       rOut << (INT16) aXOBitmap.GetBitmapStyle();
/*N*/       rOut << (INT16) aXOBitmap.GetBitmapType();
/*N*/
/*N*/       if( aXOBitmap.GetBitmapType() == XBITMAP_IMPORT )
/*N*/       {
/*N*/           rOut << aXOBitmap.GetBitmap();
/*N*/       }
/*N*/       else if( aXOBitmap.GetBitmapType() == XBITMAP_8X8 )
/*N*/       {
/*N*/           USHORT* pArray = aXOBitmap.GetPixelArray();
/*N*/           for( USHORT i = 0; i < 64; i++ )
/*N*/               rOut << (USHORT) *( pArray + i );
/*N*/
/*N*/           rOut << aXOBitmap.GetPixelColor();
/*N*/           rOut << aXOBitmap.GetBackgroundColor();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return rOut;
/*N*/ }

/************************************************************************/

/*N*/ XubString& XBitmapList::ConvertName( XubString& rStrName )
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   for( USHORT i=0; i<(RID_SVXSTR_BMP_DEF_END-RID_SVXSTR_BMP_DEF_START+1) && !bFound; i++ )
/*N*/   {
/*N*/       XubString aStrDefName = SVX_RESSTR( RID_SVXSTR_BMP_DEF_START + i );
/*N*/       if( rStrName.Search( aStrDefName ) == 0 )
/*N*/       {
/*N*/           rStrName.Replace( 0, aStrDefName.Len(), SVX_RESSTR( RID_SVXSTR_BMP_START + i ) );
/*N*/           bFound = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return rStrName;
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XBitmapList::ImpRead( SvStream& rIn )
/*N*/ {
/*N*/   // Lesen
/*N*/   rIn.SetStreamCharSet( RTL_TEXTENCODING_IBM_850 );
/*N*/
/*N*/   delete pBmpList;
/*N*/   pBmpList = new List( 16, 16 );
/*N*/
/*N*/   XBitmapEntry* pEntry = NULL;
/*N*/   long        nCount;
/*N*/   String      aName;
/*N*/
/*N*/   rIn >> nCount; // Version oder Anzahl ?
/*N*/
/*N*/   if( nCount >= 0 ) // Erste Version
/*N*/   {
/*N*/       for( long nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/       {
/*N*/           // Behandlung der alten Bitmaps
/*N*/           Bitmap  aBmp;
/*N*/           XOBitmap    aXOBitmap;
/*N*/
/*N*/           // UNICODE: rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           aName = ConvertName( aName );
/*N*/           rIn >> aBmp;
/*N*/
/*N*/           aXOBitmap.SetBitmap( aBmp );
/*N*/           aXOBitmap.SetBitmapStyle( XBITMAP_TILE );
/*N*/
/*N*/           if( aBmp.GetSizePixel().Width() == 8 &&
/*N*/               aBmp.GetSizePixel().Height() == 8 )
/*N*/           {
/*N*/               aXOBitmap.SetBitmapType( XBITMAP_8X8 );
/*N*/               aXOBitmap.Bitmap2Array();
/*N*/           }
/*N*/           else
/*N*/               aXOBitmap.SetBitmapType( XBITMAP_IMPORT );
/*N*/
/*N*/           pEntry = new XBitmapEntry( aXOBitmap, aName );
/*N*/           Insert( pEntry, nIndex );
/*N*/       }
/*N*/   }
/*N*/   else if( nCount == -1 ) // Zweite Version
/*N*/   {
/*N*/       rIn >> nCount;
/*N*/       for( long nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/       {
/*N*/           // UNICODE: rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           aName = ConvertName( aName );
/*N*/
/*N*/           XOBitmap aXOBitmap;
/*N*/           INT16   iTmp;
/*N*/
/*N*/           rIn >> iTmp;
/*N*/           aXOBitmap.SetBitmapStyle( (XBitmapStyle) iTmp );
/*N*/           rIn >> iTmp;
/*N*/           aXOBitmap.SetBitmapType( (XBitmapType) iTmp );
/*N*/
/*N*/           if( aXOBitmap.GetBitmapType() == XBITMAP_IMPORT )
/*N*/           {
/*N*/               Bitmap aBmp;
/*N*/               rIn >> aBmp;
/*N*/               aXOBitmap.SetBitmap( aBmp );
/*N*/           }
/*N*/           else if( aXOBitmap.GetBitmapType() == XBITMAP_8X8 )
/*N*/           {
/*N*/               USHORT* pArray = new USHORT[ 64 ];
/*N*/               Color   aColor;
/*N*/
/*N*/               for( USHORT i = 0; i < 64; i++ )
/*N*/                   rIn >> *( pArray + i );
/*N*/               aXOBitmap.SetPixelArray( pArray );
/*N*/
/*N*/               rIn >> aColor;
/*N*/               aXOBitmap.SetPixelColor( aColor );
/*N*/               rIn >> aColor;
/*N*/               aXOBitmap.SetBackgroundColor( aColor );
/*N*/
/*N*/               delete []pArray;
/*N*/           }
/*N*/
/*N*/           pEntry = new XBitmapEntry( aXOBitmap, aName );
/*N*/           Insert( pEntry, nIndex );
/*N*/       }
/*N*/   }
/*N*/   else // Version ab 3.00a
/*N*/   {
/*N*/       rIn >> nCount;
/*N*/       for( long nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/       {
/*N*/           // Versionsverwaltung
/*N*/           XIOCompat aIOC( rIn, STREAM_READ );
/*N*/
/*N*/           // UNICODE: rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           aName = ConvertName( aName );
/*N*/
/*N*/           XOBitmap aXOBitmap;
/*N*/           INT16   iTmp;
/*N*/
/*N*/           rIn >> iTmp;
/*N*/           aXOBitmap.SetBitmapStyle( (XBitmapStyle) iTmp );
/*N*/           rIn >> iTmp;
/*N*/           aXOBitmap.SetBitmapType( (XBitmapType) iTmp );
/*N*/
/*N*/           if( aXOBitmap.GetBitmapType() == XBITMAP_IMPORT )
/*N*/           {
/*N*/               Bitmap aBmp;
/*N*/               rIn >> aBmp;
/*N*/               aXOBitmap.SetBitmap( aBmp );
/*N*/           }
/*N*/           else if( aXOBitmap.GetBitmapType() == XBITMAP_8X8 )
/*N*/           {
/*N*/               USHORT* pArray = new USHORT[ 64 ];
/*N*/               Color   aColor;
/*N*/
/*N*/               for( USHORT i = 0; i < 64; i++ )
/*N*/                   rIn >> *( pArray + i );
/*N*/               aXOBitmap.SetPixelArray( pArray );
/*N*/
/*N*/               rIn >> aColor;
/*N*/               aXOBitmap.SetPixelColor( aColor );
/*N*/               rIn >> aColor;
/*N*/               aXOBitmap.SetBackgroundColor( aColor );
/*N*/
/*N*/               delete []pArray;
/*N*/           }
/*N*/
/*N*/           if (aIOC.GetVersion() > 0)
/*N*/           {
/*N*/               // lesen neuer Daten ...
/*N*/           }
/*N*/
/*N*/           pEntry = new XBitmapEntry( aXOBitmap, aName );
/*N*/           Insert( pEntry, nIndex );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return( rIn );
/*N*/ }



}
