/*************************************************************************
 *
 *  $RCSfile: svx_xtabhtch.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:54:11 $
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

#ifndef SVX_LIGHT

// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif
#ifndef _SVX_XPROPERTYTABLE_HXX
#include "XPropertyTable.hxx"
#endif
#ifndef _UNTOOLS_UCBSTREAMHELPER_HXX
#include <unotools/ucbstreamhelper.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

// auto strip #include "xmlxtexp.hxx"
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
#include "dlgutil.hxx"

#ifndef _SVX_XFLHTIT_HXX //autogen
#include <xflhtit.hxx>
#endif

#ifndef _SVX_XFLCLIT_HXX //autogen
#include <xflclit.hxx>
#endif

#ifndef SVX_XFILLIT0_HXX //autogen
#include <xfillit0.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;

sal_Unicode const pszExtHatch[]  = {'s','o','h'};

char const aChckHatch[]  = { 0x04, 0x00, 'S','O','H','L'};  // < 5.2
char const aChckHatch0[] = { 0x04, 0x00, 'S','O','H','0'};  // = 5.2
char const aChckXML[]    = { '<', '?', 'x', 'm', 'l' };     // = 6.0

// ------------------
// class XHatchTable
// ------------------

/*************************************************************************
|*
|* XHatchTable::XHatchTable()
|*
*************************************************************************/

/*N*/ XHatchTable::XHatchTable( const String& rPath,
/*N*/                           XOutdevItemPool* pInPool,
/*N*/                           USHORT nInitSize, USHORT nReSize ) :
/*N*/               XPropertyTable( rPath, pInPool, nInitSize, nReSize)
/*N*/ {
/*N*/   pBmpTable = new Table( nInitSize, nReSize );
/*N*/ }

/************************************************************************/

/*N*/ XHatchTable::~XHatchTable()
/*N*/ {
/*N*/ }

/************************************************************************/

/*N*/ XHatchEntry* XHatchTable::Replace(long nIndex, XHatchEntry* pEntry )
/*N*/ {
/*N*/   return (XHatchEntry*) XPropertyTable::Replace(nIndex, pEntry);
/*N*/ }

/************************************************************************/

/*N*/ XHatchEntry* XHatchTable::Remove(long nIndex)
/*N*/ {
/*N*/   return (XHatchEntry*) XPropertyTable::Remove(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ XHatchEntry* XHatchTable::Get(long nIndex) const
/*N*/ {
/*N*/   return (XHatchEntry*) XPropertyTable::Get(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchTable::Load()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchTable::Save()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchTable::Create()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchTable::CreateBitmapsForUI()
/*N*/ {
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ Bitmap* XHatchTable::CreateBitmapForUI( long nIndex, BOOL bDelete )
/*N*/ {
/*N*/   return( NULL );
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XHatchTable::ImpStore( SvStream& rOut )
/*N*/ {
/*N*/   // Schreiben
/*N*/   rOut.SetStreamCharSet( gsl_getSystemTextEncoding() );
/*N*/
/*N*/   // Tabellentyp schreiben (0 = gesamte Tabelle)
/*N*/   rOut << (long)0;
/*N*/
/*N*/   // Anzahl der Eintraege
/*N*/   rOut << (long)Count();
/*N*/
/*N*/   // die Eintraege
/*N*/   XHatchEntry* pEntry = (XHatchEntry*)aTable.First();;
/*N*/   for (long nIndex = 0; nIndex < Count(); nIndex++)
/*N*/   {
/*N*/       rOut << (long)aTable.GetCurKey();
/*N*/
/*N*/       // UNICODE: rOut << pEntry->GetName();
/*N*/       rOut.WriteByteString(pEntry->GetName());
/*N*/
/*N*/       XHatch& rHatch = pEntry->GetHatch();
/*N*/       rOut << (long)rHatch.GetHatchStyle();
/*N*/       rOut << rHatch.GetColor().GetRed();
/*N*/       rOut << rHatch.GetColor().GetGreen();
/*N*/       rOut << rHatch.GetColor().GetBlue();
/*N*/       rOut << rHatch.GetDistance();
/*N*/       rOut << rHatch.GetAngle();
/*N*/       pEntry = (XHatchEntry*)aTable.Next();
/*N*/   }
/*N*/
/*N*/   return rOut;
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XHatchTable::ImpRead( SvStream& rIn )
/*N*/ {
/*N*/   // Lesen
/*N*/   rIn.SetStreamCharSet( RTL_TEXTENCODING_IBM_850 );
/*N*/
/*N*/   delete pBmpTable;
/*N*/   pBmpTable = new Table( 16, 16 );
/*N*/
/*N*/   XHatchEntry* pEntry = NULL;
/*N*/   long        nType;
/*N*/   long        nCount;
/*N*/   long        nIndex;
/*N*/   XubString   aName;
/*N*/
/*N*/   long        nStyle;
/*N*/   USHORT      nRed;
/*N*/   USHORT      nGreen;
/*N*/   USHORT      nBlue;
/*N*/   long        nDistance;
/*N*/   long        nAngle;
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
/*N*/           rIn >> nStyle;
/*N*/           rIn >> nRed;
/*N*/           rIn >> nGreen;
/*N*/           rIn >> nBlue;
/*N*/           rIn >> nDistance;
/*N*/           rIn >> nAngle;
/*N*/
/*N*/           Color aColor ( (BYTE) nRed, (BYTE) nGreen, (BYTE) nBlue);
/*N*/           XHatch aHatch(aColor, (XHatchStyle)nStyle, nDistance, nAngle);
/*N*/           pEntry = new XHatchEntry (aHatch, aName);
/*N*/           Insert (nIndex, pEntry);
/*N*/       }
/*N*/   }
/*N*/   return( rIn );
/*N*/ }

// -----------------
// class XHatchList
// -----------------

/*************************************************************************
|*
|* XHatchList::XHatchList()
|*
*************************************************************************/

/*N*/ XHatchList::XHatchList( const String& rPath,
/*N*/                           XOutdevItemPool* pInPool,
/*N*/                           USHORT nInitSize, USHORT nReSize ) :
/*N*/               XPropertyList   ( rPath, pInPool, nInitSize, nReSize),
/*N*/               pVD             ( NULL ),
/*N*/               pXOut           ( NULL ),
/*N*/               pXFSet          ( NULL )
/*N*/ {
/*N*/   pBmpList = new List( nInitSize, nReSize );
/*N*/ }

/************************************************************************/

/*N*/ XHatchList::~XHatchList()
/*N*/ {
/*N*/   if( pVD )    delete pVD;
/*N*/   if( pXOut )  delete pXOut;
/*N*/   if( pXFSet ) delete pXFSet;
/*N*/ }

/************************************************************************/

/*N*/ XHatchEntry* XHatchList::Replace(XHatchEntry* pEntry, long nIndex )
/*N*/ {
/*N*/   return (XHatchEntry*) XPropertyList::Replace(pEntry, nIndex);
/*N*/ }

/************************************************************************/

/*N*/ XHatchEntry* XHatchList::Remove(long nIndex)
/*N*/ {
/*N*/   return (XHatchEntry*) XPropertyList::Remove(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ XHatchEntry* XHatchList::Get(long nIndex) const
/*N*/ {
/*N*/   return (XHatchEntry*) XPropertyList::Get(nIndex, 0);
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchList::Load()
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
/*N*/           aURL.setExtension( String( pszExtHatch, 3 ) );
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
/*N*/           SvStream* pStream = aMedium.GetInStream();
/*N*/           if( !pStream )
/*N*/               return( FALSE );
/*N*/
/*N*/           char aCheck[6];
/*N*/           pStream->Read( aCheck, 6 );
/*N*/
/*N*/           // Handelt es sich um die gew"unschte Tabelle?
/*N*/           if( memcmp( aCheck, aChckHatch, sizeof( aChckHatch ) ) == 0 ||
/*N*/               memcmp( aCheck, aChckHatch0, sizeof( aChckHatch0 ) ) == 0 )
/*N*/           {
/*N*/               ImpRead( *pStream );
/*N*/               return( pStream->GetError() == SVSTREAM_OK );
/*N*/           }
/*N*/           else if( memcmp( aCheck, aChckXML, sizeof( aChckXML ) ) != 0 )
/*N*/           {
/*N*/               return FALSE;
/*N*/           }
/*N*/
/*N*/       }
/*N*/
/*N*/       uno::Reference< container::XNameContainer > xTable( SvxUnoXHatchTable_createInstance( this ), uno::UNO_QUERY );
/*N*/       return SvxXMLXTableImport::load( aURL.GetMainURL( INetURLObject::NO_DECODE ), xTable );
/*N*/   }
/*N*/ #endif
/*N*/   return( FALSE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchList::Save()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return false;
//STRIP001 #ifndef SVX_LIGHT
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
//STRIP001      aURL.setExtension( String( pszExtHatch, 3 ) );
//STRIP001
//STRIP001  uno::Reference< container::XNameContainer > xTable( SvxUnoXHatchTable_createInstance( this ), uno::UNO_QUERY );
//STRIP001  return SvxXMLXTableExportComponent::save( aURL.GetMainURL( INetURLObject::NO_DECODE ), xTable );
//STRIP001
/*
    SfxMedium aMedium( aURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_WRITE | STREAM_TRUNC, TRUE );
    aMedium.IsRemote();

    SvStream* pStream = aMedium.GetOutStream();
    if( !pStream )
        return( FALSE );

    // UNICODE: *pStream << String( pszChckHatch0, 4 );
    pStream->WriteByteString(String( pszChckHatch0, 4 ));

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

/*N*/ BOOL XHatchList::Create()
/*N*/ {
/*N*/   XubString aStr( SVX_RES( RID_SVXSTR_HATCH ) );
/*N*/   xub_StrLen nLen;
/*N*/
/*N*/   aStr.AppendAscii(" 1");
/*N*/   nLen = aStr.Len() - 1;
/*N*/   Insert(new XHatchEntry(XHatch(RGB_Color(COL_BLACK),XHATCH_SINGLE,100,  0),aStr));
/*N*/   aStr.SetChar(nLen, sal_Unicode('2'));
/*N*/   Insert(new XHatchEntry(XHatch(RGB_Color(COL_RED  ),XHATCH_DOUBLE, 80,450),aStr));
/*N*/   aStr.SetChar(nLen, sal_Unicode('3'));
/*N*/   Insert(new XHatchEntry(XHatch(RGB_Color(COL_BLUE ),XHATCH_TRIPLE,120,  0),aStr));
/*N*/
/*N*/   return( TRUE );
/*N*/ }

/************************************************************************/

/*N*/ BOOL XHatchList::CreateBitmapsForUI()
/*N*/ {
/*N*/   for( long i = 0; i < Count(); i++)
/*N*/   {
/*N*/       Bitmap* pBmp = CreateBitmapForUI( i, FALSE );
/*N*/       DBG_ASSERT( pBmp, "XHatchList: Bitmap(UI) konnte nicht erzeugt werden!" );
/*N*/
/*N*/       if( pBmp )
/*N*/           pBmpList->Insert( pBmp, i );
/*N*/   }
/*N*/   // Loeschen, da JOE den Pool vorm Dtor entfernt!
/*N*/   if( pVD )   { delete pVD;   pVD = NULL;     }
/*N*/   if( pXOut ) { delete pXOut; pXOut = NULL;   }
/*N*/   if( pXFSet ){ delete pXFSet; pXFSet = NULL; }
/*N*/
/*N*/   return( TRUE );
/*N*/ }

/************************************************************************/

/*N*/ Bitmap* XHatchList::CreateBitmapForUI( long nIndex, BOOL bDelete )
/*N*/ {
/*N*/   Point   aZero;
/*N*/
/*N*/   if( !pVD ) // und pXOut und pXFSet
/*N*/   {
/*N*/       pVD = new VirtualDevice;
/*N*/       DBG_ASSERT( pVD, "XHatchList: Konnte kein VirtualDevice erzeugen!" );
/*N*/       //pVD->SetMapMode( MAP_100TH_MM );
/*N*/       //pVD->SetOutputSize( pVD->PixelToLogic( Size( BITMAP_WIDTH, BITMAP_HEIGHT ) ) );
/*N*/       pVD->SetOutputSizePixel( Size( BITMAP_WIDTH, BITMAP_HEIGHT ) );
/*N*/
/*N*/       pXOut = new XOutputDevice( pVD );
/*N*/       DBG_ASSERT( pVD, "XHatchList: Konnte kein XOutDevice erzeugen!" );
/*N*/
/*N*/       pXFSet = new XFillAttrSetItem( pXPool );
/*N*/       DBG_ASSERT( pVD, "XHatchList: Konnte kein XFillAttrSetItem erzeugen!" );
/*N*/   }
/*N*/
/*N*/   if( Application::GetSettings().GetStyleSettings().GetHighContrastMode() != 0 )
/*N*/       pVD->SetDrawMode( OUTPUT_DRAWMODE_CONTRAST );
/*N*/   else
/*N*/       pVD->SetDrawMode( OUTPUT_DRAWMODE_COLOR );
/*N*/
/*N*/   // Damit die Schraffuren mit Rahmen angezeigt werden:
/*N*/   // MapMode-Aenderungen (100th mm <--> Pixel)
/*N*/   Size aPixelSize = pVD->GetOutputSizePixel();
/*N*/   pVD->SetMapMode( MAP_PIXEL );
/*N*/
/*N*/   pXFSet->GetItemSet().Put( XFillStyleItem( XFILL_SOLID ) );
/*N*/   pXFSet->GetItemSet().Put( XFillColorItem( String(), RGB_Color( COL_WHITE ) ) );
/*N*/
/*N*/ //-/  pXOut->SetFillAttr( *pXFSet );
/*N*/   pXOut->SetFillAttr( pXFSet->GetItemSet() );
/*N*/
/*N*/   // #73550#
/*N*/   pXOut->OverrideLineColor( Color( COL_BLACK ) );
/*N*/
/*N*/   pXOut->DrawRect( Rectangle( aZero, aPixelSize ) );
/*N*/
/*N*/   pVD->SetMapMode( MAP_100TH_MM );
/*N*/   Size aVDSize = pVD->GetOutputSize();
/*N*/   // 1 Pixel (Rahmen) abziehen
/*N*/   aVDSize.Width() -= (long) ( aVDSize.Width() / aPixelSize.Width() + 1 );
/*N*/   aVDSize.Height() -= (long) ( aVDSize.Height() / aPixelSize.Height() + 1 );
/*N*/
/*N*/   pXFSet->GetItemSet().Put( XFillStyleItem( XFILL_HATCH ) );
/*N*/   pXFSet->GetItemSet().Put( XFillHatchItem( String(), Get( nIndex )->GetHatch() ) );

//-/    pXOut->SetFillAttr( *pXFSet );
/*N*/   pXOut->SetFillAttr( pXFSet->GetItemSet() );
/*N*/
/*N*/   pXOut->DrawRect( Rectangle( aZero, aVDSize ) );
/*N*/
/*N*/   Bitmap* pBitmap = new Bitmap( pVD->GetBitmap( aZero, pVD->GetOutputSize() ) );
/*N*/
/*N*/   // Loeschen, da JOE den Pool vorm Dtor entfernt!
/*N*/   if( bDelete )
/*N*/   {
/*N*/       if( pVD )   { delete pVD;   pVD = NULL;     }
/*N*/       if( pXOut ) { delete pXOut; pXOut = NULL;   }
/*N*/       if( pXFSet ){ delete pXFSet; pXFSet = NULL; }
/*N*/   }
/*N*/
/*N*/   return( pBitmap );
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XHatchList::ImpStore( SvStream& rOut )
/*N*/ {
/*N*/   // Schreiben
/*N*/   rOut.SetStreamCharSet( gsl_getSystemTextEncoding() );
/*N*/
/*N*/   // Version statt Anzahl, um auch alte Tabellen zu lesen
/*N*/   rOut << (long) -1;
/*N*/
/*N*/   // Anzahl der Eintraege
/*N*/   rOut << (long)Count();
/*N*/
/*N*/   // die Eintraege
/*N*/   XHatchEntry* pEntry = NULL;
/*N*/   for (long nIndex = 0; nIndex < Count(); nIndex++)
/*N*/   {
/*N*/       // Versionsverwaltung: Version 0
/*N*/       XIOCompat aIOC( rOut, STREAM_WRITE, 0 );
/*N*/
/*N*/       pEntry = Get(nIndex);
/*N*/
/*N*/       // UNICODE: rOut << pEntry->GetName();
/*N*/       rOut.WriteByteString(pEntry->GetName());
/*N*/
/*N*/       XHatch& rHatch = pEntry->GetHatch();
/*N*/       rOut << (long)rHatch.GetHatchStyle();
/*N*/       USHORT nCol = rHatch.GetColor().GetRed();
/*N*/       nCol = nCol << 8;
/*N*/       rOut << nCol;
/*N*/
/*N*/       nCol = rHatch.GetColor().GetGreen();
/*N*/       nCol = nCol << 8;
/*N*/       rOut << nCol;
/*N*/
/*N*/       nCol = rHatch.GetColor().GetBlue();
/*N*/       nCol = nCol << 8;
/*N*/       rOut << nCol;
/*N*/       rOut << rHatch.GetDistance();
/*N*/       rOut << rHatch.GetAngle();
/*N*/   }
/*N*/
/*N*/   return rOut;
/*N*/ }

/************************************************************************/

/*N*/ XubString& XHatchList::ConvertName( XubString& rStrName )
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   for( USHORT i=0; i<(RID_SVXSTR_HATCH_DEF_END-RID_SVXSTR_HATCH_DEF_START+1) && !bFound; i++ )
/*N*/   {
/*N*/       XubString aStrDefName = SVX_RESSTR( RID_SVXSTR_HATCH_DEF_START + i );
/*N*/       if( rStrName.Search( aStrDefName ) == 0 )
/*N*/       {
/*N*/           rStrName.Replace( 0, aStrDefName.Len(), SVX_RESSTR( RID_SVXSTR_HATCH_START + i ) );
/*N*/           bFound = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return rStrName;
/*N*/ }

/************************************************************************/

/*N*/ SvStream& XHatchList::ImpRead( SvStream& rIn )
/*N*/ {
/*N*/   // Lesen
/*N*/   rIn.SetStreamCharSet( RTL_TEXTENCODING_IBM_850 );
/*N*/
/*N*/   delete pBmpList;
/*N*/   pBmpList = new List( 16, 16 );
/*N*/
/*N*/   XHatchEntry* pEntry = NULL;
/*N*/   long        nCount;
/*N*/   XubString       aName;
/*N*/
/*N*/   long        nStyle;
/*N*/   USHORT      nRed;
/*N*/   USHORT      nGreen;
/*N*/   USHORT      nBlue;
/*N*/   long        nDistance;
/*N*/   long        nAngle;
/*N*/   Color       aColor;
/*N*/
/*N*/   rIn >> nCount;
/*N*/
/*N*/   if( nCount >= 0 ) // Alte Tabellen (bis 3.00)
/*N*/   {
/*N*/       for( long nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/       {
/*N*/           // UNICODE:rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           aName = ConvertName( aName );
/*N*/           rIn >> nStyle;
/*N*/           rIn >> nRed;
/*N*/           rIn >> nGreen;
/*N*/           rIn >> nBlue;
/*N*/           rIn >> nDistance;
/*N*/           rIn >> nAngle;
/*N*/
/*N*/           aColor = Color( (BYTE) ( nRed   >> 8 ),
/*N*/                           (BYTE) ( nGreen >> 8 ),
/*N*/                           (BYTE) ( nBlue  >> 8 ) );
/*N*/           XHatch aHatch(aColor, (XHatchStyle)nStyle, nDistance, nAngle);
/*N*/           pEntry = new XHatchEntry (aHatch, aName);
/*N*/           Insert (pEntry, nIndex);
/*N*/       }
/*N*/   }
/*N*/   else // ab 3.00a
/*N*/   {
/*N*/       rIn >> nCount;
/*N*/
/*N*/       for( long nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/       {
/*N*/           // Versionsverwaltung
/*N*/           XIOCompat aIOC( rIn, STREAM_READ );
/*N*/
/*N*/           // UNICODE: rIn >> aName;
/*N*/           rIn.ReadByteString(aName);
/*N*/
/*N*/           aName = ConvertName( aName );
/*N*/           rIn >> nStyle;
/*N*/           rIn >> nRed;
/*N*/           rIn >> nGreen;
/*N*/           rIn >> nBlue;
/*N*/           rIn >> nDistance;
/*N*/           rIn >> nAngle;
/*N*/
/*N*/           if (aIOC.GetVersion() > 0)
/*N*/           {
/*N*/               // lesen neuer Daten ...
/*N*/           }
/*N*/
/*N*/           aColor = Color( (BYTE) ( nRed   >> 8 ),
/*N*/                           (BYTE) ( nGreen >> 8 ),
/*N*/                           (BYTE) ( nBlue  >> 8 ) );
/*N*/           XHatch aHatch(aColor, (XHatchStyle)nStyle, nDistance, nAngle);
/*N*/           pEntry = new XHatchEntry (aHatch, aName);
/*N*/           Insert (pEntry, nIndex);
/*N*/       }
/*N*/   }
/*N*/   return( rIn );
/*N*/ }



}
