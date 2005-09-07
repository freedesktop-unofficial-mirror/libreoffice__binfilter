/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_impex.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:10:21 $
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

// System - Includes -----------------------------------------------------

class StarBASIC;

#ifdef PCH
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

#ifndef PCH
#include "bf_sc.hrc"
#define GLOBALOVERFLOW
#endif

// INCLUDE ---------------------------------------------------------------

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// auto strip #include <tools/list.hxx>
// auto strip #include <tools/string.hxx>
// auto strip #include <rtl/math.hxx>
// auto strip #include <svtools/htmlout.hxx>
#include <svtools/zforlist.hxx>
#define _SVSTDARR_ULONGS
// auto strip #include <svtools/svstdarr.hxx>
#include <sot/formats.hxx>
// auto strip #include <bf_sfx2/mieclip.hxx>
// auto strip #include <unotools/charclass.hxx>
// auto strip #include <unotools/collatorwrapper.hxx>
// auto strip #include <unotools/calendarwrapper.hxx>
#ifndef _COM_SUN_STAR_I18N_CALENDARFIELDINDEX_HPP_
#include <com/sun/star/i18n/CalendarFieldIndex.hpp>
#endif
// auto strip #ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
// auto strip #include <unotools/transliterationwrapper.hxx>
// auto strip #endif

// auto strip #include "global.hxx"
#include "docsh.hxx"
// auto strip #include "undoblk.hxx"
// auto strip #include "rangenam.hxx"
// auto strip #include "viewdata.hxx"
// auto strip #include "tabvwsh.hxx"
// auto strip #include "filter.hxx"
#include "asciiopt.hxx"
#include "cell.hxx"
// auto strip #include "rtfimp.hxx"
// auto strip #include "htmlimp.hxx"
// auto strip #include "docoptio.hxx"
#include "progress.hxx"
// auto strip #include "scitems.hxx"
// auto strip #include "editable.hxx"

#include "impex.hxx"

#include "globstr.hrc"

// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif

// auto strip #ifndef _SV_SVAPP_HXX //autogen
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
#ifndef _OSL_ENDIAN_H_
#include <osl/endian.h>
#endif
namespace binfilter {

//========================================================================


// Gesamtdokument ohne Undo


/*N*/ ScImportExport::ScImportExport( ScDocument* p )
/*N*/   : pDoc( p ), pDocSh( PTR_CAST(ScDocShell,p->GetDocumentShell()) ),
/*N*/     nSizeLimit( 0 ), bSingle( TRUE ), bAll( TRUE ), bUndo( FALSE ),
/*N*/     cSep( '\t' ), cStr( '"' ), bFormulas( FALSE ), bIncludeFiltered( TRUE ),
/*N*/     bOverflow( FALSE )
/*N*/ {
/*N*/   pUndoDoc = NULL;
/*N*/   pExtOptions = NULL;
/*N*/ }

// Insert am Punkt ohne Bereichschecks


//STRIP001 ScImportExport::ScImportExport( ScDocument* p, const ScAddress& rPt )
//STRIP001  : pDoc( p ), pDocSh( PTR_CAST(ScDocShell,p->GetDocumentShell()) ),
//STRIP001    aRange( rPt ),
//STRIP001    nSizeLimit( 0 ), bSingle( TRUE ), bAll( FALSE ), bUndo( BOOL( pDocSh != NULL ) ),
//STRIP001    cSep( '\t' ), cStr( '"' ), bFormulas( FALSE ), bIncludeFiltered( TRUE ),
//STRIP001    bOverflow( FALSE )
//STRIP001 {
//STRIP001  pUndoDoc = NULL;
//STRIP001  pExtOptions = NULL;
//STRIP001 }


//  ctor with a range is only used for export
//! ctor with a string (and bSingle=TRUE) is also used for DdeSetData

//STRIP001 ScImportExport::ScImportExport( ScDocument* p, const ScRange& r )
//STRIP001  : pDoc( p ), pDocSh( PTR_CAST(ScDocShell,p->GetDocumentShell()) ),
//STRIP001    aRange( r ),
//STRIP001    nSizeLimit( 0 ), bSingle( FALSE ), bAll( FALSE ), bUndo( BOOL( pDocSh != NULL ) ),
//STRIP001    cSep( '\t' ), cStr( '"' ), bFormulas( FALSE ), bIncludeFiltered( TRUE ),
//STRIP001    bOverflow( FALSE )
//STRIP001 {
//STRIP001  pUndoDoc = NULL;
//STRIP001  pExtOptions = NULL;
//STRIP001  // Zur Zeit nur in einer Tabelle!
//STRIP001  aRange.aEnd.SetTab( aRange.aStart.Tab() );
//STRIP001 }

// String auswerten: Entweder Bereich, Punkt oder Gesamtdoc (bei Fehler)
// Falls eine View existiert, wird die TabNo der View entnommen!


//STRIP001 ScImportExport::ScImportExport( ScDocument* p, const String& rPos )
//STRIP001  : pDoc( p ), pDocSh( PTR_CAST(ScDocShell,p->GetDocumentShell()) ),
//STRIP001    nSizeLimit( 0 ), bSingle( TRUE ), bAll( FALSE ), bUndo( BOOL( pDocSh != NULL ) ),
//STRIP001    cSep( '\t' ), cStr( '"' ), bFormulas( FALSE ), bIncludeFiltered( TRUE ),
//STRIP001    bOverflow( FALSE )
//STRIP001 {
//STRIP001  pUndoDoc = NULL;
//STRIP001  pExtOptions = NULL;
//STRIP001
//STRIP001  USHORT nTab = ScDocShell::GetCurTab();
//STRIP001  aRange.aStart.SetTab( nTab );
//STRIP001  String aPos( rPos );
//STRIP001  //  Benannter Bereich?
//STRIP001  ScRangeName* pRange = pDoc->GetRangeName();
//STRIP001  if( pRange )
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      if( pRange->SearchName( aPos, nPos ) )
//STRIP001      {
//STRIP001          ScRangeData* pData = (*pRange)[ nPos ];
//STRIP001          if( pData->HasType( RT_REFAREA )
//STRIP001              || pData->HasType( RT_ABSAREA )
//STRIP001              || pData->HasType( RT_ABSPOS ) )
//STRIP001              pData->GetSymbol( aPos );                   // mit dem Inhalt weitertesten
//STRIP001      }
//STRIP001  }
//STRIP001  // Bereich?
//STRIP001  if( aRange.Parse( aPos, pDoc ) & SCA_VALID )
//STRIP001      bSingle = FALSE;
//STRIP001  // Zelle?
//STRIP001  else if( aRange.aStart.Parse( aPos, pDoc ) & SCA_VALID )
//STRIP001      aRange.aEnd = aRange.aStart;
//STRIP001  else
//STRIP001      bAll = TRUE;
//STRIP001 }


/*N*/ ScImportExport::~ScImportExport()
/*N*/ {
/*N*/   delete pUndoDoc;
/*N*/   delete pExtOptions;
/*N*/ }


/*N*/ void ScImportExport::SetExtOptions( const ScAsciiOptions& rOpt )
/*N*/ {
/*N*/   if ( pExtOptions )
/*N*/       *pExtOptions = rOpt;
/*N*/   else
/*N*/       pExtOptions = new ScAsciiOptions( rOpt );
/*N*/
/*N*/   //  "normale" Optionen uebernehmen
/*N*/
/*N*/   cSep = rOpt.GetFieldSeps().GetChar(0);
/*N*/   cStr = rOpt.GetTextSep();
/*N*/ }


//STRIP001 BOOL ScImportExport::IsFormatSupported( ULONG nFormat )
//STRIP001 {
//STRIP001  return BOOL( nFormat == FORMAT_STRING
//STRIP001            || nFormat == SOT_FORMATSTR_ID_SYLK
//STRIP001            || nFormat == SOT_FORMATSTR_ID_LINK
//STRIP001            || nFormat == SOT_FORMATSTR_ID_HTML
//STRIP001            || nFormat == SOT_FORMATSTR_ID_HTML_SIMPLE
//STRIP001            || nFormat == SOT_FORMATSTR_ID_DIF );
//STRIP001 }


//////////////////////////////////////////////////////////////////////////////

// Vorbereitung fuer Undo: Undo-Dokument erzeugen


//STRIP001 BOOL ScImportExport::StartPaste()
//STRIP001 {
//STRIP001  if ( !bAll )
//STRIP001  {
//STRIP001      ScEditableTester aTester( pDoc, aRange );
//STRIP001      if ( !aTester.IsEditable() )
//STRIP001      {
//STRIP001          InfoBox aInfoBox(Application::GetDefDialogParent(),
//STRIP001                              ScGlobal::GetRscString( aTester.GetMessageId() ) );
//STRIP001          aInfoBox.Execute();
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  if( bUndo && pDocSh && pDoc->IsUndoEnabled())
//STRIP001  {
//STRIP001      pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      pUndoDoc->InitUndo( pDoc, aRange.aStart.Tab(), aRange.aEnd.Tab() );
//STRIP001      pDoc->CopyToDocument( aRange, IDF_ALL, FALSE, pUndoDoc );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

// Nachbereitung Insert: Undo/Redo-Aktionen erzeugen, Invalidate/Repaint


//STRIP001 void ScImportExport::EndPaste()
//STRIP001 {
//STRIP001  BOOL bHeight = pDocSh && pDocSh->AdjustRowHeight(
//STRIP001                  aRange.aStart.Row(), aRange.aEnd.Row(), aRange.aStart.Tab() );
//STRIP001
//STRIP001  if( pUndoDoc && pDoc->IsUndoEnabled() )
//STRIP001  {
//STRIP001      ScDocument* pRedoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      pRedoDoc->InitUndo( pDoc, aRange.aStart.Tab(), aRange.aEnd.Tab() );
//STRIP001      pDoc->CopyToDocument( aRange, IDF_ALL, FALSE, pRedoDoc );
//STRIP001      ScMarkData aDestMark;
//STRIP001      aDestMark.SelectOneTable( aRange.aStart.Tab() );
//STRIP001      pDocSh->GetUndoManager()->AddUndoAction(
//STRIP001          new ScUndoPaste( pDocSh,
//STRIP001              aRange.aStart.Col(), aRange.aStart.Row(), aRange.aStart.Tab(),
//STRIP001              aRange.aEnd.Col(), aRange.aEnd.Row(), aRange.aEnd.Tab(), aDestMark,
//STRIP001              pUndoDoc, pRedoDoc, IDF_ALL, NULL,NULL,NULL,NULL ) );
//STRIP001  }
//STRIP001  pUndoDoc = NULL;
//STRIP001  if( pDocSh )
//STRIP001  {
//STRIP001      if (!bHeight)
//STRIP001          pDocSh->PostPaint( aRange, PAINT_GRID );    // AdjustRowHeight paintet evtl. selber
//STRIP001      pDocSh->SetDocumentModified();
//STRIP001  }
//STRIP001  ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
//STRIP001  if ( pViewSh )
//STRIP001      pViewSh->UpdateInputHandler();
//STRIP001
//STRIP001 }

/////////////////////////////////////////////////////////////////////////////


//STRIP001 #if 0
//STRIP001 BOOL ScImportExport::ImportData( SvData& rData )
//STRIP001 {
//STRIP001  ULONG nFmt = rData.GetFormat();
//STRIP001  if ( nFmt == SOT_FORMATSTR_ID_HTML_SIMPLE )
//STRIP001  {
//STRIP001      MSE40HTMLClipFormatObj aMSE40ClpObj;
//STRIP001      if ( aMSE40ClpObj.GetData( rData ) )
//STRIP001      {
//STRIP001          SvStream* pStream = aMSE40ClpObj.GetStream();
//STRIP001          return ImportStream( *pStream, nFmt );
//STRIP001      }
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      void* pMem;
//STRIP001      ULONG nSize = rData.GetMinMemorySize();
//STRIP001      rData.GetData( &pMem, TRANSFER_REFERENCE );
//STRIP001      if( nFmt == FORMAT_STRING
//STRIP001              || nFmt == FORMAT_RTF
//STRIP001              || nFmt == SOT_FORMATSTR_ID_SYLK
//STRIP001              || nFmt == SOT_FORMATSTR_ID_HTML
//STRIP001              || nFmt == SOT_FORMATSTR_ID_DIF )
//STRIP001      {
//STRIP001          //! String? Unicode??
//STRIP001
//STRIP001          // Stringende ermitteln!
//STRIP001          sal_Char* pBegin = (sal_Char*) pMem;
//STRIP001          sal_Char* pEnd   = (sal_Char*) pMem + nSize;
//STRIP001
//STRIP001          nSize = 0;
//STRIP001          while( pBegin != pEnd && *pBegin != '\0' )
//STRIP001              pBegin++, nSize++;
//STRIP001          // #72909# MT says only STRING has to be zero-terminated
//STRIP001          DBG_ASSERT( pBegin != pEnd || nFmt != FORMAT_STRING, "non zero-terminated String" )
//STRIP001      }
//STRIP001      SvMemoryStream aStrm( pMem, nSize, STREAM_READ );
//STRIP001      return ImportStream( aStrm, nFmt );
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 #endif

//STRIP001 BOOL ScImportExport::ImportData( const String& rMimeType,
//STRIP001                   const ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  DBG_ASSERT( !this, "Implementation is missing" );
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ScImportExport::ExportData( const String& rMimeType,
//STRIP001                               ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  SvMemoryStream aStrm;
//STRIP001  if( ExportStream( aStrm,
//STRIP001              SotExchange::GetFormatIdFromMimeType( rMimeType ) ))
//STRIP001  {
//STRIP001      aStrm << (BYTE) 0;
//STRIP001      rValue <<= ::com::sun::star::uno::Sequence< sal_Int8 >(
//STRIP001                                      (sal_Int8*)aStrm.GetData(),
//STRIP001                                      aStrm.Seek( STREAM_SEEK_TO_END ) );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


// static
//STRIP001 inline void ScImportExport::SetNoEndianSwap( SvStream& rStrm )
//STRIP001 {
//STRIP001 #ifdef OSL_BIGENDIAN
//STRIP001  rStrm.SetNumberFormatInt( NUMBERFORMAT_INT_BIGENDIAN );
//STRIP001 #else
//STRIP001  rStrm.SetNumberFormatInt( NUMBERFORMAT_INT_LITTLEENDIAN );
//STRIP001 #endif
//STRIP001 }


//STRIP001 BOOL ScImportExport::ImportString( const ::rtl::OUString& rText, ULONG nFmt )
//STRIP001 {
//STRIP001  switch ( nFmt )
//STRIP001  {
//STRIP001      // formats supporting unicode
//STRIP001      case FORMAT_STRING :
//STRIP001      {
//STRIP001             SvMemoryStream aStrm( (void*)rText.getStr(), rText.getLength() * sizeof(sal_Unicode), STREAM_READ );
//STRIP001          aStrm.SetStreamCharSet( RTL_TEXTENCODING_UNICODE );
//STRIP001          SetNoEndianSwap( aStrm );       //! no swapping in memory
//STRIP001          return ImportStream( aStrm, nFmt );
//STRIP001          // ImportStream must handle RTL_TEXTENCODING_UNICODE
//STRIP001      }
//STRIP001      break;
//STRIP001      default:
//STRIP001      {
//STRIP001          rtl_TextEncoding eEnc = gsl_getSystemTextEncoding();
//STRIP001             ::rtl::OString aTmp( rText.getStr(), rText.getLength(), eEnc );
//STRIP001             SvMemoryStream aStrm( (void*)aTmp.getStr(), aTmp.getLength() * sizeof(sal_Char), STREAM_READ );
//STRIP001          aStrm.SetStreamCharSet( eEnc );
//STRIP001          SetNoEndianSwap( aStrm );       //! no swapping in memory
//STRIP001          return ImportStream( aStrm, nFmt );
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL ScImportExport::ExportString( ::rtl::OUString& rText, ULONG nFmt )
//STRIP001 {
//STRIP001  DBG_ASSERT( nFmt == FORMAT_STRING, "ScImportExport::ExportString: Unicode not supported for other formats than FORMAT_STRING" );
//STRIP001  if ( nFmt != FORMAT_STRING )
//STRIP001  {
//STRIP001      rtl_TextEncoding eEnc = gsl_getSystemTextEncoding();
//STRIP001      ByteString aTmp;
//STRIP001      BOOL bOk = ExportByteString( aTmp, eEnc, nFmt );
//STRIP001      rText = UniString( aTmp, eEnc );
//STRIP001      return bOk;
//STRIP001  }
//STRIP001  //  nSizeLimit not needed for OUString
//STRIP001
//STRIP001  SvMemoryStream aStrm;
//STRIP001  aStrm.SetStreamCharSet( RTL_TEXTENCODING_UNICODE );
//STRIP001  SetNoEndianSwap( aStrm );       //! no swapping in memory
//STRIP001  if( ExportStream( aStrm, nFmt ) )
//STRIP001  {
//STRIP001      aStrm << (sal_Unicode) 0;
//STRIP001      aStrm.Seek( STREAM_SEEK_TO_END );
//STRIP001
//STRIP001      rText = ::rtl::OUString( (const sal_Unicode*) aStrm.GetData() );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  rText = ::rtl::OUString();
//STRIP001  return FALSE;
//STRIP001
//STRIP001  // ExportStream must handle RTL_TEXTENCODING_UNICODE
//STRIP001 }


//STRIP001 BOOL ScImportExport::ExportByteString( ByteString& rText, rtl_TextEncoding eEnc, ULONG nFmt )
//STRIP001 {
//STRIP001  DBG_ASSERT( eEnc != RTL_TEXTENCODING_UNICODE, "ScImportExport::ExportByteString: Unicode not supported" );
//STRIP001  if ( eEnc == RTL_TEXTENCODING_UNICODE )
//STRIP001      eEnc = gsl_getSystemTextEncoding();
//STRIP001
//STRIP001  if (!nSizeLimit)
//STRIP001      nSizeLimit = STRING_MAXLEN;
//STRIP001
//STRIP001  SvMemoryStream aStrm;
//STRIP001  aStrm.SetStreamCharSet( eEnc );
//STRIP001  SetNoEndianSwap( aStrm );       //! no swapping in memory
//STRIP001  if( ExportStream( aStrm, nFmt ) )
//STRIP001  {
//STRIP001      aStrm << (sal_Char) 0;
//STRIP001      aStrm.Seek( STREAM_SEEK_TO_END );
//STRIP001      // Sicherheits-Check:
//STRIP001      if( aStrm.Tell() <= (ULONG) STRING_MAXLEN )
//STRIP001      {
//STRIP001          rText = (const sal_Char*) aStrm.GetData();
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  rText.Erase();
//STRIP001  return FALSE;
//STRIP001 }


/*N*/ BOOL ScImportExport::ImportStream( SvStream& rStrm, ULONG nFmt )
/*N*/ {
/*N*/   if( nFmt == FORMAT_STRING )
/*N*/   {
/*N*/       if( ExtText2Doc( rStrm ) )      // pExtOptions auswerten
/*N*/           return TRUE;
/*N*/   }
/*N*/   if( nFmt == SOT_FORMATSTR_ID_SYLK )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( Sylk2Doc( rStrm ) )
/*?*/           return TRUE;
/*N*/   }
/*N*/   if( nFmt == SOT_FORMATSTR_ID_DIF )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( Dif2Doc( rStrm ) )
/*?*/           return TRUE;
/*N*/   }
/*N*/   if( nFmt == FORMAT_RTF )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( RTF2Doc( rStrm ) )
/*?*/           return TRUE;
/*N*/   }
/*N*/   if( nFmt == SOT_FORMATSTR_ID_LINK )
/*N*/       return TRUE;            // Link-Import?
/*N*/   if ( nFmt == SOT_FORMATSTR_ID_HTML )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( HTML2Doc( rStrm ) )
/*?*/           return TRUE;
/*N*/   }
/*N*/   if ( nFmt == SOT_FORMATSTR_ID_HTML_SIMPLE )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 MSE40HTMLClipFormatObj aMSE40ClpObj;              // needed to skip the header data
//STRIP001 /*?*/        SvStream* pHTML = aMSE40ClpObj.IsValid( rStrm );
//STRIP001 /*?*/        if ( pHTML && HTML2Doc( *pHTML ) )
/*?*/           return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }


//STRIP001 BOOL ScImportExport::ExportStream( SvStream& rStrm, ULONG nFmt )
//STRIP001 {
//STRIP001  if( nFmt == FORMAT_STRING )
//STRIP001  {
//STRIP001      if( Doc2Text( rStrm ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  if( nFmt == SOT_FORMATSTR_ID_SYLK )
//STRIP001  {
//STRIP001      if( Doc2Sylk( rStrm ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  if( nFmt == SOT_FORMATSTR_ID_DIF )
//STRIP001  {
//STRIP001      if( Doc2Dif( rStrm ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  if( nFmt == SOT_FORMATSTR_ID_LINK && !bAll )
//STRIP001  {
//STRIP001      String aDocName;
//STRIP001      if ( pDoc->IsClipboard() )
//STRIP001          aDocName = ScGlobal::GetClipDocName();
//STRIP001      else
//STRIP001      {
//STRIP001          SfxObjectShell* pShell = pDoc->GetDocumentShell();
//STRIP001          if (pShell)
//STRIP001              aDocName = pShell->GetTitle( SFX_TITLE_FULLNAME );
//STRIP001      }
//STRIP001
//STRIP001      DBG_ASSERT( aDocName.Len(), "ClipBoard document has no name! :-/" );
//STRIP001      if( aDocName.Len() )
//STRIP001      {
//STRIP001          String aRefName;
//STRIP001          USHORT nFlags = SCA_VALID | SCA_TAB_3D;
//STRIP001          if( bSingle )
//STRIP001              aRange.aStart.Format( aRefName, nFlags, pDoc );
//STRIP001          else
//STRIP001          {
//STRIP001              if( aRange.aStart.Tab() != aRange.aEnd.Tab() )
//STRIP001                  nFlags |= SCA_TAB2_3D;
//STRIP001              aRange.Format( aRefName, nFlags, pDoc );
//STRIP001          }
//STRIP001          String aAppName = Application::GetAppName();
//STRIP001
//STRIP001          WriteUnicodeOrByteString( rStrm, aAppName, TRUE );
//STRIP001          WriteUnicodeOrByteString( rStrm, aDocName, TRUE );
//STRIP001          WriteUnicodeOrByteString( rStrm, aRefName, TRUE );
//STRIP001          if ( rStrm.GetStreamCharSet() == RTL_TEXTENCODING_UNICODE )
//STRIP001              rStrm << sal_Unicode(0);
//STRIP001          else
//STRIP001              rStrm << sal_Char(0);
//STRIP001          return BOOL( rStrm.GetError() == SVSTREAM_OK );
//STRIP001      }
//STRIP001  }
//STRIP001  if( nFmt == SOT_FORMATSTR_ID_HTML )
//STRIP001  {
//STRIP001      if( Doc2HTML( rStrm ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  if( nFmt == FORMAT_RTF )
//STRIP001  {
//STRIP001      if( Doc2RTF( rStrm ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }


//static
//STRIP001 void ScImportExport::WriteUnicodeOrByteString( SvStream& rStrm, const String& rString, BOOL bZero )
//STRIP001 {
//STRIP001  rtl_TextEncoding eEnc = rStrm.GetStreamCharSet();
//STRIP001  if ( eEnc == RTL_TEXTENCODING_UNICODE )
//STRIP001  {
//STRIP001      if ( !IsEndianSwap( rStrm ) )
//STRIP001          rStrm.Write( rString.GetBuffer(), rString.Len() * sizeof(sal_Unicode) );
//STRIP001      else
//STRIP001      {
//STRIP001          const sal_Unicode* p = rString.GetBuffer();
//STRIP001          const sal_Unicode* const pStop = p + rString.Len();
//STRIP001          while ( p < pStop )
//STRIP001          {
//STRIP001              rStrm << *p;
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bZero )
//STRIP001          rStrm << sal_Unicode(0);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ByteString aByteStr( rString, eEnc );
//STRIP001      rStrm << aByteStr.GetBuffer();
//STRIP001      if ( bZero )
//STRIP001          rStrm << sal_Char(0);
//STRIP001  }
//STRIP001 }


// static
//STRIP001 void ScImportExport::WriteUnicodeOrByteEndl( SvStream& rStrm )
//STRIP001 {
//STRIP001  if ( rStrm.GetStreamCharSet() == RTL_TEXTENCODING_UNICODE )
//STRIP001  {   // same as endl() but unicode
//STRIP001      switch ( rStrm.GetLineDelimiter() )
//STRIP001      {
//STRIP001          case LINEEND_CR :
//STRIP001              rStrm << sal_Unicode(_CR);
//STRIP001          break;
//STRIP001          case LINEEND_LF :
//STRIP001              rStrm << sal_Unicode(_LF);
//STRIP001          break;
//STRIP001          default:
//STRIP001              rStrm << sal_Unicode(_CR) << sal_Unicode(_LF);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      endl( rStrm );
//STRIP001 }


enum DoubledQuoteMode
{
    DQM_KEEP,       // both are taken
    DQM_ESCAPE,     // escaped quote, one is taken, one ignored
    DQM_CONCAT,     // first is end, next is start, both ignored => strings combined
    DQM_SEPARATE    // end one string and begin next
};

/*N*/ const sal_Unicode* lcl_ScanString( const sal_Unicode* p, String& rString,
/*N*/           sal_Unicode cStr, DoubledQuoteMode eMode )
/*N*/ {
/*N*/   p++;    //! jump over opening quote
/*N*/   BOOL bCont;
/*N*/   do
/*N*/   {
/*N*/       bCont = FALSE;
/*N*/       const sal_Unicode* p0 = p;
/*N*/       for( ;; )
/*N*/       {
/*N*/           if( !*p )
/*N*/               break;
/*N*/           if( *p == cStr )
/*N*/           {
/*N*/               if ( *++p != cStr )
/*N*/                   break;
/*N*/               // doubled quote char
/*N*/               switch ( eMode )
/*N*/               {
/*N*/                   case DQM_KEEP :
/*N*/                       p++;            // both for us (not breaking for-loop)
/*N*/                   break;
/*N*/                   case DQM_ESCAPE :
/*N*/                       p++;            // one for us (breaking for-loop)
/*N*/                       bCont = TRUE;   // and more
/*N*/                   break;
/*N*/                   case DQM_CONCAT :
/*N*/                       if ( p0+1 < p )
/*N*/                           rString.Append( p0, (p-1) - p0 );   // first part
/*N*/                       p0 = ++p;       // text of next part starts here
/*N*/                   break;
/*N*/                   case DQM_SEPARATE :
/*N*/                                       // positioned on next opening quote
/*N*/                   break;
/*N*/               }
/*N*/               if ( eMode == DQM_ESCAPE || eMode == DQM_SEPARATE )
/*N*/                   break;
/*N*/           }
/*N*/           else
/*N*/               p++;
/*N*/       }
/*N*/       if ( p0 < p )
/*N*/           rString.Append( p0, ((*p || *(p-1) == cStr) ? p-1 : p) - p0 );
/*N*/   } while ( bCont );
/*N*/   return p;
/*N*/ }


//STRIP001 void lcl_WriteString( SvStream& rStrm, String& rString, sal_Unicode cStr )
//STRIP001 {
//STRIP001  xub_StrLen n = 0;
//STRIP001  while( ( n = rString.Search( cStr, n ) ) != STRING_NOTFOUND )
//STRIP001  {
//STRIP001      rString.Insert( cStr, n );
//STRIP001      n += 2;
//STRIP001  }
//STRIP001
//STRIP001  rString.Insert( cStr, 0 );
//STRIP001  rString.Append( cStr );
//STRIP001
//STRIP001  ScImportExport::WriteUnicodeOrByteString( rStrm, rString );
//STRIP001 }

//STRIP001 inline void lcl_WriteSimpleString( SvStream& rStrm, const String& rString )
//STRIP001 {
//STRIP001  ScImportExport::WriteUnicodeOrByteString( rStrm, rString );
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////


//STRIP001 BOOL ScImportExport::Text2Doc( SvStream& rStrm )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001
//STRIP001  USHORT nStartCol = aRange.aStart.Col();
//STRIP001  USHORT nStartRow = aRange.aStart.Row();
//STRIP001  USHORT nEndCol = aRange.aEnd.Col();
//STRIP001  USHORT nEndRow = aRange.aEnd.Row();
//STRIP001  ULONG  nOldPos = rStrm.Tell();
//STRIP001  if ( rStrm.GetStreamCharSet() == RTL_TEXTENCODING_UNICODE )
//STRIP001      rStrm.StartReadingUnicodeText();
//STRIP001  BOOL   bData = BOOL( !bSingle );
//STRIP001  if( !bSingle)
//STRIP001      bOk = StartPaste();
//STRIP001
//STRIP001  while( bOk )
//STRIP001  {
//STRIP001      ByteString aByteLine;
//STRIP001      String aLine, aCell;
//STRIP001      USHORT nRow = nStartRow;
//STRIP001      rStrm.Seek( nOldPos );
//STRIP001      for( ;; )
//STRIP001      {
//STRIP001          rStrm.ReadUniOrByteStringLine( aLine );
//STRIP001          if( rStrm.IsEof() )
//STRIP001              break;
//STRIP001          USHORT nCol = nStartCol;
//STRIP001          const sal_Unicode* p = aLine.GetBuffer();
//STRIP001          while( *p )
//STRIP001          {
//STRIP001              aCell.Erase();
//STRIP001              if( *p == cStr )
//STRIP001              {
//STRIP001                  p = lcl_ScanString( p, aCell, cStr, DQM_KEEP );
//STRIP001                  while( *p && *p != cSep )
//STRIP001                      p++;
//STRIP001                  if( *p )
//STRIP001                      p++;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  const sal_Unicode* q = p;
//STRIP001                  while( *p && *p != cSep )
//STRIP001                      p++;
//STRIP001                  aCell.Assign( q, p - q );
//STRIP001                  if( *p )
//STRIP001                      p++;
//STRIP001              }
//STRIP001              if (nCol<=MAXCOL && nRow<=MAXROW )
//STRIP001              {
//STRIP001                  if( bSingle )
//STRIP001                  {
//STRIP001                      if (nCol>nEndCol) nEndCol = nCol;
//STRIP001                      if (nRow>nEndRow) nEndRow = nRow;
//STRIP001                  }
//STRIP001                  if( bData && nCol <= nEndCol && nRow <= nEndRow )
//STRIP001                      pDoc->SetString( nCol, nRow, aRange.aStart.Tab(), aCell );
//STRIP001              }
//STRIP001              else                            // zuviele Spalten/Zeilen
//STRIP001                  bOverflow = TRUE;           // beim Import Warnung ausgeben
//STRIP001              ++nCol;
//STRIP001          }
//STRIP001          ++nRow;
//STRIP001      }
//STRIP001
//STRIP001      if( !bData )
//STRIP001      {
//STRIP001          aRange.aEnd.SetCol( nEndCol );
//STRIP001          aRange.aEnd.SetRow( nEndRow );
//STRIP001          bOk = StartPaste();
//STRIP001          bData = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  EndPaste();
//STRIP001  return bOk;
//STRIP001 }

        //
        //  erweiterter Ascii-Import
        //


/*M*/ void lcl_PutString( ScDocument* pDoc, USHORT nCol, USHORT nRow, USHORT nTab,
/*M*/                   const String& rStr, BYTE nColFormat,
/*M*/                     ::utl::TransliterationWrapper& rTransliteration,
/*M*/                   CalendarWrapper& rCalendar,
/*M*/                     ::utl::TransliterationWrapper* pSecondTransliteration,
/*M*/                   CalendarWrapper* pSecondCalendar )
/*M*/ {
/*M*/   if ( nColFormat == SC_COL_SKIP || !rStr.Len() || nCol > MAXCOL || nRow > MAXROW )
/*M*/       return;
/*M*/
/*M*/   if ( nColFormat == SC_COL_TEXT )
/*M*/   {
/*M*/       pDoc->PutCell( nCol, nRow, nTab, new ScStringCell( rStr ) );
/*M*/       return;
/*M*/   }
/*M*/
/*M*/   if ( nColFormat == SC_COL_ENGLISH )
/*M*/   {
/*M*/       //! SetString mit Extra-Flag ???
/*M*/
/*M*/       SvNumberFormatter* pFormatter = pDoc->GetFormatTable();
/*M*/       ULONG nEnglish = pFormatter->GetStandardIndex(LANGUAGE_ENGLISH_US);
/*M*/       double fVal;
/*M*/       if ( pFormatter->IsNumberFormat( rStr, nEnglish, fVal ) )
/*M*/       {
/*M*/           //  Zahlformat wird nicht auf englisch gesetzt
/*M*/           pDoc->SetValue( nCol, nRow, nTab, fVal );
/*M*/           return;
/*M*/       }
/*M*/       //  sonst weiter mit SetString
/*M*/   }
/*M*/   else if ( nColFormat != SC_COL_STANDARD )                   // Datumsformate
/*M*/   {
/*M*/       //  nach genau drei Teilen suchen
/*M*/
/*M*/       xub_StrLen nLen = rStr.Len();
/*M*/       xub_StrLen nStart[3];
/*M*/       xub_StrLen nEnd[3];
/*M*/       USHORT nFound = 0;
/*M*/       BOOL bInNum = FALSE;
/*M*/       for ( xub_StrLen nPos=0; nPos<nLen; nPos++ )
/*M*/       {
/*M*/           if ( ScGlobal::pCharClass->isLetterNumeric( rStr, nPos ) )
/*M*/           {
/*M*/               if (!bInNum)
/*M*/               {
/*M*/                   if ( nFound >= 3 )
/*M*/                       break;                  // zuviele Teile
/*M*/                   bInNum = TRUE;
/*M*/                   nStart[nFound] = nPos;
/*M*/                   ++nFound;
/*M*/               }
/*M*/               nEnd[nFound-1] = nPos;
/*M*/           }
/*M*/           else
/*M*/               bInNum = FALSE;
/*M*/       }
/*M*/
/*M*/       USHORT nDP, nMP, nYP;
/*M*/       switch ( nColFormat )
/*M*/       {
/*M*/           case SC_COL_YMD: nDP = 2; nMP = 1; nYP = 0; break;
/*M*/           case SC_COL_MDY: nDP = 1; nMP = 0; nYP = 2; break;
/*M*/           case SC_COL_DMY:
/*M*/           default:         nDP = 0; nMP = 1; nYP = 2; break;
/*M*/       }
/*M*/
/*M*/       if ( nFound == 1 )
/*M*/       {
/*M*/           //  try to break one number (without separators) into date fields
/*M*/
/*M*/           xub_StrLen nDateStart = nStart[0];
/*M*/           xub_StrLen nDateLen = nEnd[0] + 1 - nDateStart;
/*M*/
/*M*/           if ( nDateLen >= 5 && nDateLen <= 8 &&
/*M*/                   ScGlobal::pCharClass->isNumeric( rStr.Copy( nDateStart, nDateLen ) ) )
/*M*/           {
/*M*/               //  6 digits: 2 each for day, month, year
/*M*/               //  8 digits: 4 for year, 2 each for day and month
/*M*/               //  5 or 7 digits: first field is shortened by 1
/*M*/
/*M*/               BOOL bLongYear = ( nDateLen >= 7 );
/*M*/               BOOL bShortFirst = ( nDateLen == 5 || nDateLen == 7 );
/*M*/
/*M*/               USHORT nFieldStart = nDateStart;
/*M*/               for (USHORT nPos=0; nPos<3; nPos++)
/*M*/               {
/*M*/                   USHORT nFieldEnd = nFieldStart + 1;     // default: 2 digits
/*M*/                   if ( bLongYear && nPos == nYP )
/*M*/                       nFieldEnd += 2;                     // 2 extra digits for long year
/*M*/                   if ( bShortFirst && nPos == 0 )
/*M*/                       --nFieldEnd;                        // first field shortened?
/*M*/
/*M*/                   nStart[nPos] = nFieldStart;
/*M*/                   nEnd[nPos]   = nFieldEnd;
/*M*/                   nFieldStart  = nFieldEnd + 1;
/*M*/               }
/*M*/               nFound = 3;
/*M*/           }
/*M*/       }
/*M*/
/*M*/       if ( nFound == 3 )              // exactly 3 parts found?
/*M*/       {
/*M*/           using namespace ::com::sun::star;
/*M*/           BOOL bSecondCal = FALSE;
/*M*/           USHORT nDay  = (USHORT) rStr.Copy( nStart[nDP], nEnd[nDP]+1-nStart[nDP] ).ToInt32();
/*M*/           USHORT nYear = (USHORT) rStr.Copy( nStart[nYP], nEnd[nYP]+1-nStart[nYP] ).ToInt32();
/*M*/           String aMStr = rStr.Copy( nStart[nMP], nEnd[nMP]+1-nStart[nMP] );
/*M*/           sal_Int16 nMonth = (sal_Int16) aMStr.ToInt32();
/*M*/           if (!nMonth)
/*M*/           {
/*M*/                 static const String aSeptCorrect( RTL_CONSTASCII_USTRINGPARAM( "SEPT" ) );
/*M*/                 static const String aSepShortened( RTL_CONSTASCII_USTRINGPARAM( "SEP" ) );
/*M*/               uno::Sequence< i18n::CalendarItem > xMonths;
/*M*/               sal_Int32 i, nLen;
/*M*/               //  first test all month names from local international
/*M*/               xMonths = rCalendar.getMonths();
/*M*/               nLen = xMonths.getLength();
/*M*/               for (i=0; i<nLen && !nMonth; i++)
/*M*/               {
/*M*/                     if ( rTransliteration.isEqual( aMStr, xMonths[i].FullName ) ||
/*M*/                          rTransliteration.isEqual( aMStr, xMonths[i].AbbrevName ) )
/*M*/                       nMonth = i+1;
/*M*/                     else if ( i == 8 && rTransliteration.isEqual( aSeptCorrect,
/*M*/                                 xMonths[i].AbbrevName ) &&
/*M*/                             rTransliteration.isEqual( aMStr, aSepShortened ) )
/*M*/                     {   // #102136# correct English abbreviation is SEPT,
/*M*/                         // but data mostly contains SEP only
/*M*/                         nMonth = i+1;
/*M*/                     }
/*M*/               }
/*M*/               //  if none found, then test english month names
/*M*/                 if ( !nMonth && pSecondCalendar && pSecondTransliteration )
/*M*/               {
/*M*/                   xMonths = pSecondCalendar->getMonths();
/*M*/                   nLen = xMonths.getLength();
/*M*/                   for (i=0; i<nLen && !nMonth; i++)
/*M*/                   {
/*M*/                         if ( pSecondTransliteration->isEqual( aMStr, xMonths[i].FullName ) ||
/*M*/                              pSecondTransliteration->isEqual( aMStr, xMonths[i].AbbrevName ) )
/*M*/                       {
/*M*/                           nMonth = i+1;
/*M*/                           bSecondCal = TRUE;
/*M*/                       }
/*M*/                         else if ( i == 8 && pSecondTransliteration->isEqual(
/*M*/                                     aMStr, aSepShortened ) )
/*M*/                         {   // #102136# correct English abbreviation is SEPT,
/*M*/                             // but data mostly contains SEP only
/*M*/                           nMonth = i+1;
/*M*/                           bSecondCal = TRUE;
/*M*/                         }
/*M*/                   }
/*M*/               }
/*M*/           }
/*M*/
/*M*/           SvNumberFormatter* pFormatter = pDoc->GetFormatTable();
/*M*/           if ( nYear < 100 )
/*M*/               nYear = pFormatter->ExpandTwoDigitYear( nYear );
/*M*/
/*M*/           CalendarWrapper* pCalendar = (bSecondCal ? pSecondCalendar : &rCalendar);
/*M*/           sal_Int16 nNumMonths = pCalendar->getNumberOfMonthsInYear();
/*M*/           if ( nDay && nMonth && nDay<=31 && nMonth<=nNumMonths )
/*M*/           {
/*M*/               --nMonth;
/*M*/               pCalendar->setValue( i18n::CalendarFieldIndex::DAY_OF_MONTH, nDay );
/*M*/               pCalendar->setValue( i18n::CalendarFieldIndex::MONTH, nMonth );
/*M*/               pCalendar->setValue( i18n::CalendarFieldIndex::YEAR, nYear );
/*N*/                 // #i14974# The imported value should have no fractional value, so set the
/*N*/                 // time fields to zero (ICU calendar instance defaults to current date/time)
/*N*/                 pCalendar->setValue( i18n::CalendarFieldIndex::HOUR, 0 );
/*N*/                 pCalendar->setValue( i18n::CalendarFieldIndex::MINUTE, 0 );
/*N*/                 pCalendar->setValue( i18n::CalendarFieldIndex::SECOND, 0 );
/*N*/                 pCalendar->setValue( i18n::CalendarFieldIndex::MILLISECOND, 0 );
/*M*/                 if ( pCalendar->isValid() )
/*M*/                 {
/*M*/                     double fDiff = DateTime(*pFormatter->GetNullDate()) -
/*M*/                         pCalendar->getEpochStart();
/*N*/                     // #i14974# must use getLocalDateTime to get the same
/*N*/                     // date values as set above
/*N*/                     double fDays = pCalendar->getLocalDateTime();
/*M*/                     fDays -= fDiff;
/*M*/
/*M*/                     LanguageType eLatin, eCjk, eCtl;
/*M*/                     pDoc->GetLanguage( eLatin, eCjk, eCtl );
/*M*/                     LanguageType eDocLang = eLatin;     //! which language for date formats?
/*M*/
/*M*/                     long nFormat = pFormatter->GetStandardFormat( NUMBERFORMAT_DATE, eDocLang );
/*M*/
/*M*/                     pDoc->PutCell( nCol, nRow, nTab, new ScValueCell(fDays), nFormat, FALSE );
/*M*/
/*M*/                     return;     // success
/*M*/                 }
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/
/*M*/   //  Standard oder Datum nicht erkannt -> SetString
/*M*/
/*M*/   pDoc->SetString( nCol, nRow, nTab, rStr );
/*M*/ }


//STRIP001 String lcl_GetFixed( const String& rLine, xub_StrLen nStart, xub_StrLen nNext )
//STRIP001 {
//STRIP001  xub_StrLen nLen = rLine.Len();
//STRIP001  if (nNext > nLen)
//STRIP001      nNext = nLen;
//STRIP001  if ( nNext <= nStart )
//STRIP001      return EMPTY_STRING;
//STRIP001
//STRIP001  const sal_Unicode* pStr = rLine.GetBuffer();
//STRIP001
//STRIP001  xub_StrLen nSpace = nNext;
//STRIP001  while ( nSpace > nStart && pStr[nSpace-1] == ' ' )
//STRIP001      --nSpace;
//STRIP001
//STRIP001  return rLine.Copy( nStart, nSpace-nStart );
//STRIP001 }


/*N*/ BOOL ScImportExport::ExtText2Doc( SvStream& rStrm )
/*N*/ {
/*N*/   if (!pExtOptions)
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 return Text2Doc( rStrm );
/*N*/
/*N*/   ULONG nOldPos = rStrm.Tell();
/*N*/   rStrm.Seek( STREAM_SEEK_TO_END );
/*N*/   ScProgress aProgress( pDocSh, ScGlobal::GetRscString( STR_LOAD_DOC ), rStrm.Tell() - nOldPos );
/*N*/   rStrm.Seek( nOldPos );
/*N*/   if ( rStrm.GetStreamCharSet() == RTL_TEXTENCODING_UNICODE )
/*?*/       rStrm.StartReadingUnicodeText();
/*N*/
/*N*/   BOOL bOld = ScColumn::bDoubleAlloc;
/*N*/   ScColumn::bDoubleAlloc = TRUE;
/*N*/
/*N*/   DBG_ASSERT( !bUndo, "ExtText2Doc mit Undo noch nicht implementiert!" );
/*N*/   USHORT nStartCol = aRange.aStart.Col();
/*N*/   USHORT nStartRow = aRange.aStart.Row();
/*N*/   USHORT nTab = aRange.aStart.Tab();
/*N*/
/*N*/   BOOL    bFixed          = pExtOptions->IsFixedLen();
/*N*/   const sal_Unicode* pSeps = pExtOptions->GetFieldSeps().GetBuffer();
/*N*/   BOOL    bMerge          = pExtOptions->IsMergeSeps();
/*N*/   USHORT  nInfoCount      = pExtOptions->GetInfoCount();
/*N*/   const xub_StrLen* pColStart = pExtOptions->GetColStart();
/*N*/   const BYTE* pColFormat  = pExtOptions->GetColFormat();
/*N*/   long nSkipLines = pExtOptions->GetStartRow();
/*N*/
/*N*/   LanguageType eLatin, eCjk, eCtl;
/*N*/   pDoc->GetLanguage( eLatin, eCjk, eCtl );
/*N*/   LanguageType eDocLang = eLatin;                 //! which language for date formats?
/*N*/
/*N*/   // For date recognition
/*N*/     ::utl::TransliterationWrapper aTransliteration(
/*N*/         pDoc->GetServiceManager(), SC_TRANSLITERATION_IGNORECASE );
/*N*/     aTransliteration.loadModuleIfNeeded( eDocLang );
/*N*/   CalendarWrapper aCalendar( pDoc->GetServiceManager() );
/*N*/   aCalendar.loadDefaultCalendar(
/*N*/       SvNumberFormatter::ConvertLanguageToLocale( eDocLang ) );
/*N*/     ::utl::TransliterationWrapper* pEnglishTransliteration = NULL;
/*N*/   CalendarWrapper* pEnglishCalendar = NULL;
/*N*/   if ( eDocLang != LANGUAGE_ENGLISH_US )
/*N*/   {
/*?*/         pEnglishTransliteration = new ::utl::TransliterationWrapper (
/*?*/             pDoc->GetServiceManager(), SC_TRANSLITERATION_IGNORECASE );
/*?*/         aTransliteration.loadModuleIfNeeded( LANGUAGE_ENGLISH_US );
/*?*/       pEnglishCalendar = new CalendarWrapper ( pDoc->GetServiceManager() );
/*?*/       pEnglishCalendar->loadDefaultCalendar(
/*?*/           SvNumberFormatter::ConvertLanguageToLocale( LANGUAGE_ENGLISH_US ) );
/*N*/   }
/*N*/
/*N*/   String aLine, aCell;
/*N*/   USHORT i;
/*N*/   USHORT nRow = nStartRow;
/*N*/
/*N*/   while(--nSkipLines>0)
/*N*/   {
/*?*/       rStrm.ReadUniOrByteStringLine( aLine );     // content is ignored
/*?*/       if ( rStrm.IsEof() )
/*?*/           break;
/*N*/   }
/*N*/   for( ;; )
/*N*/   {
/*N*/       rStrm.ReadUniOrByteStringLine( aLine );
/*N*/       if ( rStrm.IsEof() )
/*N*/           break;
/*N*/
/*N*/       xub_StrLen nLineLen = aLine.Len();
/*N*/       USHORT nCol = nStartCol;
/*N*/       if ( bFixed )               //  Feste Satzlaenge
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 for ( i=0; i<nInfoCount; i++ )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( pColFormat[i] != SC_COL_SKIP )     // sonst auch nCol nicht hochzaehlen
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    xub_StrLen nStart = pColStart[i];
//STRIP001 /*?*/                    xub_StrLen nNext = ( i+1 < nInfoCount ) ? pColStart[i+1] : nLineLen;
//STRIP001 /*?*/                    aCell = lcl_GetFixed( aLine, nStart, nNext );
//STRIP001 /*?*/                    lcl_PutString( pDoc, nCol, nRow, nTab, aCell, pColFormat[i],
//STRIP001 /*?*/                         aTransliteration, aCalendar, pEnglishTransliteration, pEnglishCalendar );
//STRIP001 /*?*/                    ++nCol;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       else                        //  Nach Trennzeichen suchen
/*N*/       {
/*N*/           USHORT nSourceCol = 0;
/*N*/           USHORT nInfoStart = 0;
/*N*/           const sal_Unicode* p = aLine.GetBuffer();
/*N*/           while (*p)
/*N*/           {
/*N*/               p = ScImportExport::ScanNextFieldFromString( p, aCell, cStr, pSeps, bMerge );
/*N*/
/*N*/               BYTE nFmt = SC_COL_STANDARD;
/*N*/               for ( i=nInfoStart; i<nInfoCount; i++ )
/*N*/               {
/*N*/                   if ( pColStart[i] == nSourceCol + 1 )       // pColStart ist 1-basiert
/*N*/                   {
/*N*/                       nFmt = pColFormat[i];
/*N*/                       nInfoStart = i + 1;     // ColInfos sind in Reihenfolge
/*N*/                       break;  // for
/*N*/                   }
/*N*/               }
/*N*/               if ( nFmt != SC_COL_SKIP )
/*N*/               {
/*N*/                   lcl_PutString( pDoc, nCol, nRow, nTab, aCell, nFmt,
/*N*/                         aTransliteration, aCalendar, pEnglishTransliteration, pEnglishCalendar );
/*N*/                   ++nCol;
/*N*/               }
/*N*/
/*N*/               ++nSourceCol;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       aProgress.SetStateOnPercent( rStrm.Tell() - nOldPos );
/*N*/       ++nRow;
/*N*/       if ( nRow > MAXROW )
/*N*/       {
/*N*/           bOverflow = TRUE;           // beim Import Warnung ausgeben
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ScColumn::bDoubleAlloc = bOld;
/*N*/   pDoc->DoColResize( nTab, 0, MAXCOL, 0 );
/*N*/
/*N*/     delete pEnglishTransliteration;
/*N*/   delete pEnglishCalendar;
/*N*/
/*N*/   return TRUE;
/*N*/ }


// static
/*N*/ const sal_Unicode* ScImportExport::ScanNextFieldFromString( const sal_Unicode* p,
/*N*/       String& rField, sal_Unicode cStr, const sal_Unicode* pSeps, BOOL bMergeSeps )
/*N*/ {
/*N*/   rField.Erase();
/*N*/   if ( *p == cStr )           // String in Anfuehrungszeichen
/*N*/   {
/*N*/       p = lcl_ScanString( p, rField, cStr, DQM_ESCAPE );
/*N*/       while ( *p && !ScGlobal::UnicodeStrChr( pSeps, *p ) )
/*N*/           p++;
/*N*/       if( *p )
/*N*/           p++;
/*N*/   }
/*N*/   else                        // bis zum Trennzeichen
/*N*/   {
/*N*/       const sal_Unicode* p0 = p;
/*N*/       while ( *p && !ScGlobal::UnicodeStrChr( pSeps, *p ) )
/*N*/           p++;
/*N*/       rField.Append( p0, p - p0 );
/*N*/       if( *p )
/*N*/           p++;
/*N*/   }
/*N*/   if ( bMergeSeps )           // folgende Trennzeichen ueberspringen
/*N*/   {
/*?*/       while ( *p && ScGlobal::UnicodeStrChr( pSeps, *p ) )
/*?*/           p++;
/*N*/   }
/*N*/   return p;
/*N*/ }

        //
        //
        //


//STRIP001 BOOL ScImportExport::Doc2Text( SvStream& rStrm )
//STRIP001 {
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  USHORT nStartCol = aRange.aStart.Col();
//STRIP001  USHORT nStartRow = aRange.aStart.Row();
//STRIP001  USHORT nEndCol = aRange.aEnd.Col();
//STRIP001  USHORT nEndRow = aRange.aEnd.Row();
//STRIP001  String aCell;
//STRIP001
//STRIP001  for (nRow = nStartRow; nRow <= nEndRow; nRow++)
//STRIP001  {
//STRIP001      if (bIncludeFiltered || !pDoc->IsFiltered( nRow, aRange.aStart.Tab() ))
//STRIP001      {
//STRIP001          for (nCol = nStartCol; nCol <= nEndCol; nCol++)
//STRIP001          {
//STRIP001              CellType eType;
//STRIP001              pDoc->GetCellType( nCol, nRow, aRange.aStart.Tab(), eType );
//STRIP001              switch (eType)
//STRIP001              {
//STRIP001                  case CELLTYPE_FORMULA:
//STRIP001                  {
//STRIP001                      if (bFormulas)
//STRIP001                      {
//STRIP001                          pDoc->GetFormula( nCol, nRow, aRange.aStart.Tab(), aCell, TRUE );
//STRIP001                          if( aCell.Search( cSep ) != STRING_NOTFOUND )
//STRIP001                              lcl_WriteString( rStrm, aCell, cStr );
//STRIP001                          else
//STRIP001                              lcl_WriteSimpleString( rStrm, aCell );
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          pDoc->GetString( nCol, nRow, aRange.aStart.Tab(), aCell );
//STRIP001                          if( aCell.Search( cSep ) != STRING_NOTFOUND )
//STRIP001                              lcl_WriteString( rStrm, aCell, cStr );
//STRIP001                          else
//STRIP001                              lcl_WriteSimpleString( rStrm, aCell );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  break;
//STRIP001                  case CELLTYPE_VALUE:
//STRIP001                  {
//STRIP001                      pDoc->GetString( nCol, nRow, aRange.aStart.Tab(), aCell );
//STRIP001                      lcl_WriteSimpleString( rStrm, aCell );
//STRIP001                  }
//STRIP001                  break;
//STRIP001                  case CELLTYPE_NOTE:
//STRIP001                  case CELLTYPE_NONE:
//STRIP001                  break;
//STRIP001                  default:
//STRIP001                  {
//STRIP001                      pDoc->GetString( nCol, nRow, aRange.aStart.Tab(), aCell );
//STRIP001                      if( aCell.Search( cSep ) != STRING_NOTFOUND )
//STRIP001                          lcl_WriteString( rStrm, aCell, cStr );
//STRIP001                      else
//STRIP001                          lcl_WriteSimpleString( rStrm, aCell );
//STRIP001                  }
//STRIP001              }
//STRIP001              if( nCol < nEndCol )
//STRIP001                  lcl_WriteSimpleString( rStrm, String(cSep) );
//STRIP001          }
//STRIP001 //           if( nRow < nEndRow )
//STRIP001              WriteUnicodeOrByteEndl( rStrm );
//STRIP001          if( rStrm.GetError() != SVSTREAM_OK )
//STRIP001              break;
//STRIP001          if( nSizeLimit && rStrm.Tell() > nSizeLimit )
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return BOOL( rStrm.GetError() == SVSTREAM_OK );
//STRIP001 }


//STRIP001 BOOL ScImportExport::Sylk2Doc( SvStream& rStrm )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  BOOL bMyDoc = FALSE;
//STRIP001
//STRIP001  // US-English separators for StringToDouble
//STRIP001  sal_Unicode cDecSep = '.';
//STRIP001  sal_Unicode cGrpSep = ',';
//STRIP001
//STRIP001  USHORT nStartCol = aRange.aStart.Col();
//STRIP001  USHORT nStartRow = aRange.aStart.Row();
//STRIP001  USHORT nEndCol = aRange.aEnd.Col();
//STRIP001  USHORT nEndRow = aRange.aEnd.Row();
//STRIP001  ULONG nOldPos = rStrm.Tell();
//STRIP001  BOOL bData = BOOL( !bSingle );
//STRIP001     SvULongs aFormats;
//STRIP001
//STRIP001  if( !bSingle)
//STRIP001      bOk = StartPaste();
//STRIP001
//STRIP001  while( bOk )
//STRIP001  {
//STRIP001      String aLine;
//STRIP001         String aText;
//STRIP001      ByteString aByteLine;
//STRIP001      USHORT nCol = nStartCol;
//STRIP001      USHORT nRow = nStartRow;
//STRIP001         USHORT nRefCol, nRefRow;
//STRIP001         nRefCol = nRefRow = 1;
//STRIP001      rStrm.Seek( nOldPos );
//STRIP001      for( ;; )
//STRIP001      {
//STRIP001          //! allow unicode
//STRIP001          rStrm.ReadLine( aByteLine );
//STRIP001          aLine = String( aByteLine, rStrm.GetStreamCharSet() );
//STRIP001          if( rStrm.IsEof() )
//STRIP001              break;
//STRIP001          const sal_Unicode* p = aLine.GetBuffer();
//STRIP001          sal_Unicode cTag = *p++;
//STRIP001             if( cTag == 'C' )       // Content
//STRIP001          {
//STRIP001              if( *p++ != ';' )
//STRIP001                  return FALSE;
//STRIP001              while( *p )
//STRIP001              {
//STRIP001                  sal_Unicode ch = *p++;
//STRIP001                  ch = ScGlobal::ToUpperAlpha( ch );
//STRIP001                  switch( ch )
//STRIP001                  {
//STRIP001                      case 'X':
//STRIP001                          nCol = String( p ).ToInt32() + nStartCol - 1;
//STRIP001                          break;
//STRIP001                      case 'Y':
//STRIP001                          nRow = String( p ).ToInt32() + nStartRow - 1;
//STRIP001                          break;
//STRIP001                         case 'C':
//STRIP001                             nRefCol = String( p ).ToInt32() + nStartCol - 1;
//STRIP001                          break;
//STRIP001                         case 'R':
//STRIP001                             nRefRow = String( p ).ToInt32() + nStartRow - 1;
//STRIP001                          break;
//STRIP001                      case 'K':
//STRIP001                         {
//STRIP001                             if( !bSingle &&
//STRIP001                                     ( nCol < nStartCol || nCol > nEndCol
//STRIP001                                       || nRow < nStartRow || nRow > nEndRow
//STRIP001                                       || nCol > MAXCOL || nRow > MAXROW ) )
//STRIP001                              break;
//STRIP001                          if( !bData )
//STRIP001                          {
//STRIP001                              if( nRow > nEndRow )
//STRIP001                                  nEndRow = nRow;
//STRIP001                              if( nCol > nEndCol )
//STRIP001                                  nEndCol = nCol;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                             BOOL bText;
//STRIP001                             if( *p == '"' )
//STRIP001                             {
//STRIP001                                 bText = TRUE;
//STRIP001                                 aText = '\'';       // force string cell
//STRIP001                                 p = lcl_ScanString( p, aText, '"', DQM_ESCAPE );
//STRIP001                             }
//STRIP001                             else
//STRIP001                                 bText = FALSE;
//STRIP001                             const sal_Unicode* q = p;
//STRIP001                             while( *q && *q != ';' )
//STRIP001                                 q++;
//STRIP001                             if ( !(*q == ';' && *(q+1) == 'I') )
//STRIP001                             {   // don't ignore value
//STRIP001                                 if( bText )
//STRIP001                                     pDoc->SetString( nCol, nRow, aRange.aStart.Tab(), aText );
//STRIP001                                 else
//STRIP001                                 {
//STRIP001                                     double fVal = rtl_math_uStringToDouble( p,
//STRIP001                                             aLine.GetBuffer() + aLine.Len(),
//STRIP001                                             cDecSep, cGrpSep, NULL, NULL );
//STRIP001                                     pDoc->SetValue( nCol, nRow, aRange.aStart.Tab(), fVal );
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         break;
//STRIP001                      case 'E':
//STRIP001                         case 'M':
//STRIP001                         {
//STRIP001                             if ( ch == 'M' )
//STRIP001                             {
//STRIP001                                 if ( nRefCol < nCol )
//STRIP001                                     nRefCol = nCol;
//STRIP001                                 if ( nRefRow < nRow )
//STRIP001                                     nRefRow = nRow;
//STRIP001                                 if ( !bData )
//STRIP001                                 {
//STRIP001                                     if( nRefRow > nEndRow )
//STRIP001                                         nEndRow = nRefRow;
//STRIP001                                     if( nRefCol > nEndCol )
//STRIP001                                         nEndCol = nRefCol;
//STRIP001                                 }
//STRIP001                             }
//STRIP001                          if( !bMyDoc || !bData )
//STRIP001                              break;
//STRIP001                             aText = '=';
//STRIP001                          if( *p == '"' )
//STRIP001                                 p = lcl_ScanString( p, aText, '"', DQM_ESCAPE );
//STRIP001                          else
//STRIP001                          {
//STRIP001                                 const sal_Unicode* q = p;
//STRIP001                                 while( *p && *p != ';' )
//STRIP001                                     p++;
//STRIP001                                 aText.Append( q, p-q );
//STRIP001                          }
//STRIP001                             ScAddress aPos( nCol, nRow, aRange.aStart.Tab() );
//STRIP001                             ScCompiler aComp( pDoc, aPos );
//STRIP001                             aComp.SetCompileEnglish( TRUE );
//STRIP001                             ScTokenArray* pCode = aComp.CompileString( aText );
//STRIP001                             if ( ch == 'M' )
//STRIP001                             {
//STRIP001                                 ScMarkData aMark;
//STRIP001                                 aMark.SelectTable( aPos.Tab(), TRUE );
//STRIP001                                 pDoc->InsertMatrixFormula( nCol, nRow, nRefCol,
//STRIP001                                     nRefRow, aMark, EMPTY_STRING, pCode );
//STRIP001                             }
//STRIP001                             else
//STRIP001                             {
//STRIP001                                 ScFormulaCell* pFCell = new ScFormulaCell( pDoc, aPos, pCode, 0 );
//STRIP001                                 pDoc->PutCell( aPos, pFCell );
//STRIP001                             }
//STRIP001                             delete pCode;   // ctor/InsertMatrixFormula did copy TokenArray
//STRIP001                         }
//STRIP001                         break;
//STRIP001                  }
//STRIP001                  while( *p && *p != ';' )
//STRIP001                      p++;
//STRIP001                  if( *p )
//STRIP001                      p++;
//STRIP001              }
//STRIP001          }
//STRIP001             else if( cTag == 'F' )      // Format
//STRIP001             {
//STRIP001                 if( *p++ != ';' )
//STRIP001                     return FALSE;
//STRIP001                 sal_Int32 nFormat = -1;
//STRIP001                 while( *p )
//STRIP001                 {
//STRIP001                     sal_Unicode ch = *p++;
//STRIP001                     ch = ScGlobal::ToUpperAlpha( ch );
//STRIP001                     switch( ch )
//STRIP001                     {
//STRIP001                         case 'X':
//STRIP001                             nCol = String( p ).ToInt32() + nStartCol - 1;
//STRIP001                             break;
//STRIP001                         case 'Y':
//STRIP001                             nRow = String( p ).ToInt32() + nStartRow - 1;
//STRIP001                             break;
//STRIP001                         case 'P' :
//STRIP001                             if ( bData )
//STRIP001                             {
//STRIP001                                 // F;P<n> sets format code of P;P<code> at
//STRIP001                                 // current position, or at ;X;Y if specified.
//STRIP001                                 // Note that ;X;Y may appear after ;P
//STRIP001                                 const sal_Unicode* p0 = p;
//STRIP001                                 while( *p && *p != ';' )
//STRIP001                                     p++;
//STRIP001                                 String aNumber( p0, p - p0 );
//STRIP001                                 nFormat = aNumber.ToInt32();
//STRIP001                             }
//STRIP001                             break;
//STRIP001                     }
//STRIP001                     while( *p && *p != ';' )
//STRIP001                         p++;
//STRIP001                     if( *p )
//STRIP001                         p++;
//STRIP001                 }
//STRIP001                 if ( !bData )
//STRIP001                 {
//STRIP001                     if( nRow > nEndRow )
//STRIP001                         nEndRow = nRow;
//STRIP001                     if( nCol > nEndCol )
//STRIP001                         nEndCol = nCol;
//STRIP001                 }
//STRIP001                 if ( 0 <= nFormat && nFormat < aFormats.Count() )
//STRIP001                 {
//STRIP001                     ULONG nKey = aFormats[(USHORT)nFormat];
//STRIP001                     pDoc->ApplyAttr( nCol, nRow, aRange.aStart.Tab(),
//STRIP001                             SfxUInt32Item( ATTR_VALUE_FORMAT, nKey ) );
//STRIP001                 }
//STRIP001             }
//STRIP001             else if( cTag == 'P' )
//STRIP001             {
//STRIP001                 if ( bData && *p == ';' && *(p+1) == 'P' )
//STRIP001                 {
//STRIP001                     String aCode( p+2 );
//STRIP001                     // unescape doubled semicolons
//STRIP001                     xub_StrLen nPos = 0;
//STRIP001                     String aSemicolon( RTL_CONSTASCII_USTRINGPARAM(";;"));
//STRIP001                     while ( (nPos = aCode.Search( aSemicolon, nPos )) != STRING_NOTFOUND )
//STRIP001                         aCode.Erase( nPos++, 1 );
//STRIP001                     // get rid of Xcl escape characters
//STRIP001                     nPos = 0;
//STRIP001                     while ( (nPos = aCode.Search( sal_Unicode(0x1b), nPos )) != STRING_NOTFOUND )
//STRIP001                         aCode.Erase( nPos, 1 );
//STRIP001                     xub_StrLen nCheckPos;
//STRIP001                     short nType;
//STRIP001                     ULONG nKey;
//STRIP001                     pDoc->GetFormatTable()->PutandConvertEntry(
//STRIP001                         aCode, nCheckPos, nType, nKey, LANGUAGE_ENGLISH_US,
//STRIP001                         ScGlobal::eLnge );
//STRIP001                     if ( nCheckPos )
//STRIP001                         nKey = 0;
//STRIP001                     aFormats.Insert( nKey, aFormats.Count() );
//STRIP001                 }
//STRIP001             }
//STRIP001             else if( cTag == 'I' && *p == 'D' )
//STRIP001          {
//STRIP001              aLine.Erase( 0, 4 );
//STRIP001              bMyDoc = aLine.EqualsAscii( "SCALC3" );
//STRIP001          }
//STRIP001          else if( cTag == 'E' )                      // Ende
//STRIP001              break;
//STRIP001      }
//STRIP001      if( !bData )
//STRIP001      {
//STRIP001          aRange.aEnd.SetCol( nEndCol );
//STRIP001          aRange.aEnd.SetRow( nEndRow );
//STRIP001          bOk = StartPaste();
//STRIP001          bData = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  EndPaste();
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScImportExport::Doc2Sylk( SvStream& rStrm )
//STRIP001 {
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  USHORT nStartCol = aRange.aStart.Col();
//STRIP001  USHORT nStartRow = aRange.aStart.Row();
//STRIP001  USHORT nEndCol = aRange.aEnd.Col();
//STRIP001  USHORT nEndRow = aRange.aEnd.Row();
//STRIP001  String aCellStr;
//STRIP001  String aValStr;
//STRIP001  lcl_WriteSimpleString( rStrm,
//STRIP001          String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM( "ID;PSCALC3" )) );
//STRIP001  WriteUnicodeOrByteEndl( rStrm );
//STRIP001
//STRIP001  for (nRow = nStartRow; nRow <= nEndRow; nRow++)
//STRIP001  {
//STRIP001      for (nCol = nStartCol; nCol <= nEndCol; nCol++)
//STRIP001      {
//STRIP001          String aBufStr;
//STRIP001          double nVal;
//STRIP001          BOOL bForm = FALSE;
//STRIP001          USHORT r = nRow - nStartRow + 1;
//STRIP001          USHORT c = nCol - nStartCol + 1;
//STRIP001             ScBaseCell* pCell;
//STRIP001             pDoc->GetCell( nCol, nRow, aRange.aStart.Tab(), pCell );
//STRIP001             CellType eType = (pCell ? pCell->GetCellType() : CELLTYPE_NONE);
//STRIP001          switch( eType )
//STRIP001          {
//STRIP001              case CELLTYPE_FORMULA:
//STRIP001                  bForm = bFormulas;
//STRIP001                  if( pDoc->HasValueData( nCol, nRow, aRange.aStart.Tab()) )
//STRIP001                      goto hasvalue;
//STRIP001                  else
//STRIP001                      goto hasstring;
//STRIP001
//STRIP001              case CELLTYPE_VALUE:
//STRIP001              hasvalue:
//STRIP001                  pDoc->GetValue( nCol, nRow, aRange.aStart.Tab(), nVal );
//STRIP001
//STRIP001                     aValStr = ::rtl::math::doubleToUString( nVal,
//STRIP001                             rtl_math_StringFormat_Automatic,
//STRIP001                             rtl_math_DecimalPlaces_Max, '.', TRUE );
//STRIP001
//STRIP001                  aBufStr.AssignAscii(RTL_CONSTASCII_STRINGPARAM( "C;X" ));
//STRIP001                  aBufStr += String::CreateFromInt32( c );
//STRIP001                  aBufStr.AppendAscii(RTL_CONSTASCII_STRINGPARAM( ";Y" ));
//STRIP001                  aBufStr += String::CreateFromInt32( r );
//STRIP001                  aBufStr.AppendAscii(RTL_CONSTASCII_STRINGPARAM( ";K" ));
//STRIP001                  aBufStr += aValStr;
//STRIP001                  lcl_WriteSimpleString( rStrm, aBufStr );
//STRIP001                  goto checkformula;
//STRIP001
//STRIP001              case CELLTYPE_STRING:
//STRIP001              case CELLTYPE_EDIT:
//STRIP001              hasstring:
//STRIP001                  pDoc->GetString( nCol, nRow, aRange.aStart.Tab(), aCellStr );
//STRIP001
//STRIP001                  aBufStr.AssignAscii(RTL_CONSTASCII_STRINGPARAM( "C;X" ));
//STRIP001                  aBufStr += String::CreateFromInt32( c );
//STRIP001                  aBufStr.AppendAscii(RTL_CONSTASCII_STRINGPARAM( ";Y" ));
//STRIP001                  aBufStr += String::CreateFromInt32( r );
//STRIP001                  aBufStr.AppendAscii(RTL_CONSTASCII_STRINGPARAM( ";K" ));
//STRIP001                  lcl_WriteSimpleString( rStrm, aBufStr );
//STRIP001                  lcl_WriteString( rStrm, aCellStr, '"' );
//STRIP001
//STRIP001              checkformula:
//STRIP001                  if( bForm )
//STRIP001                  {
//STRIP001                         const ScFormulaCell* pFCell =
//STRIP001                             static_cast<const ScFormulaCell*>(pCell);
//STRIP001                         switch ( pFCell->GetMatrixFlag() )
//STRIP001                         {
//STRIP001                             case MM_REFERENCE :
//STRIP001                                 aCellStr.Erase();
//STRIP001                             break;
//STRIP001                             default:
//STRIP001                                 pFCell->GetEnglishFormula( aCellStr );
//STRIP001                         }
//STRIP001                         if ( pFCell->GetMatrixFlag() != MM_NONE &&
//STRIP001                                 aCellStr.Len() > 2 &&
//STRIP001                                 aCellStr.GetChar(0) == '{' &&
//STRIP001                                 aCellStr.GetChar(aCellStr.Len()-1) == '}' )
//STRIP001                         {   // cut off matrix {} characters
//STRIP001                             aCellStr.Erase(aCellStr.Len()-1,1);
//STRIP001                             aCellStr.Erase(0,1);
//STRIP001                         }
//STRIP001                         if ( aCellStr.GetChar(0) == '=' )
//STRIP001                             aCellStr.Erase(0,1);
//STRIP001                         String aPrefix;
//STRIP001                         switch ( pFCell->GetMatrixFlag() )
//STRIP001                         {
//STRIP001                             case MM_FORMULA :
//STRIP001                             {   // diff expression with 'M' M$-extension
//STRIP001                                 USHORT nC, nR;
//STRIP001                                 pFCell->GetMatColsRows( nC, nR );
//STRIP001                                 nC += c - 1;
//STRIP001                                 nR += r - 1;
//STRIP001                                 aPrefix.AssignAscii( RTL_CONSTASCII_STRINGPARAM( ";R" ) );
//STRIP001                                 aPrefix += String::CreateFromInt32( nR );
//STRIP001                                 aPrefix.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ";C" ) );
//STRIP001                                 aPrefix += String::CreateFromInt32( nC );
//STRIP001                                 aPrefix.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ";M" ) );
//STRIP001                             }
//STRIP001                             break;
//STRIP001                             case MM_REFERENCE :
//STRIP001                             {   // diff expression with 'I' M$-extension
//STRIP001                                 ScAddress aPos;
//STRIP001                                 pFCell->GetMatrixOrigin( aPos );
//STRIP001                                 aPrefix.AssignAscii( RTL_CONSTASCII_STRINGPARAM( ";I;R" ) );
//STRIP001                                 aPrefix += String::CreateFromInt32( aPos.Row() - nStartRow + 1 );
//STRIP001                                 aPrefix.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ";C" ) );
//STRIP001                                 aPrefix += String::CreateFromInt32( aPos.Col() - nStartCol + 1 );
//STRIP001                             }
//STRIP001                             break;
//STRIP001                             default:
//STRIP001                                 // formula Expression
//STRIP001                                 aPrefix.AssignAscii( RTL_CONSTASCII_STRINGPARAM( ";E" ) );
//STRIP001                         }
//STRIP001                         lcl_WriteSimpleString( rStrm, aPrefix );
//STRIP001                         if ( aCellStr.Len() )
//STRIP001                         {
//STRIP001                             if( aCellStr.Search( ';' ) != STRING_NOTFOUND )
//STRIP001                                 lcl_WriteString( rStrm, aCellStr, '"' );
//STRIP001                             else
//STRIP001                                 lcl_WriteSimpleString( rStrm, aCellStr );
//STRIP001                         }
//STRIP001                  }
//STRIP001                  WriteUnicodeOrByteEndl( rStrm );
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  lcl_WriteSimpleString( rStrm, String( 'E' ) );
//STRIP001  WriteUnicodeOrByteEndl( rStrm );
//STRIP001  return BOOL( rStrm.GetError() == SVSTREAM_OK );
//STRIP001 }


//STRIP001 BOOL ScImportExport::Doc2HTML( SvStream& rStrm )
//STRIP001 {
//STRIP001     // CharSet is ignored in ScExportHTML, read from Load/Save HTML options
//STRIP001     ScExportHTML( rStrm, pDoc, aRange, RTL_TEXTENCODING_DONTKNOW, bAll,
//STRIP001         aStreamPath, aNonConvertibleChars );
//STRIP001  return BOOL( rStrm.GetError() == SVSTREAM_OK );
//STRIP001 }

//STRIP001 BOOL ScImportExport::Doc2RTF( SvStream& rStrm )
//STRIP001 {
//STRIP001  //  CharSet is ignored in ScExportRTF
//STRIP001  ScExportRTF( rStrm, pDoc, aRange, RTL_TEXTENCODING_DONTKNOW );
//STRIP001  return BOOL( rStrm.GetError() == SVSTREAM_OK );
//STRIP001 }


//STRIP001 BOOL ScImportExport::Doc2Dif( SvStream& rStrm )
//STRIP001 {
//STRIP001  // for DIF in the clipboard, IBM_850 is always used
//STRIP001  ScExportDif( rStrm, pDoc, aRange, RTL_TEXTENCODING_IBM_850 );
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScImportExport::Dif2Doc( SvStream& rStrm )
//STRIP001 {
//STRIP001  USHORT nTab = aRange.aStart.Tab();
//STRIP001  ScDocument* pImportDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001  pImportDoc->InitUndo( pDoc, nTab, nTab );
//STRIP001
//STRIP001  // for DIF in the clipboard, IBM_850 is always used
//STRIP001  ScImportDif( rStrm, pImportDoc, aRange.aStart, RTL_TEXTENCODING_IBM_850 );
//STRIP001
//STRIP001  USHORT nEndCol, nEndRow;
//STRIP001  pImportDoc->GetCellArea( nTab, nEndCol, nEndRow );
//STRIP001  aRange.aEnd = ScAddress( nEndCol, nEndRow, nTab );
//STRIP001
//STRIP001  BOOL bOk = StartPaste();
//STRIP001  if (bOk)
//STRIP001  {
//STRIP001      USHORT nFlags = IDF_ALL & ~IDF_STYLES;
//STRIP001      pDoc->DeleteAreaTab( aRange, nFlags );
//STRIP001      pImportDoc->CopyToDocument( aRange, nFlags, FALSE, pDoc );
//STRIP001      EndPaste();
//STRIP001  }
//STRIP001
//STRIP001  delete pImportDoc;
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScImportExport::RTF2Doc( SvStream& rStrm )
//STRIP001 {
//STRIP001  ScRTFImport aImp( pDoc, aRange );
//STRIP001  aImp.Read( rStrm );
//STRIP001  aRange = aImp.GetRange();
//STRIP001
//STRIP001  BOOL bOk = StartPaste();
//STRIP001  if (bOk)
//STRIP001  {
//STRIP001      USHORT nFlags = IDF_ALL & ~IDF_STYLES;
//STRIP001      pDoc->DeleteAreaTab( aRange, nFlags );
//STRIP001      aImp.WriteToDocument();
//STRIP001      EndPaste();
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScImportExport::HTML2Doc( SvStream& rStrm )
//STRIP001 {
//STRIP001  ScHTMLImport aImp( pDoc, aRange );
//STRIP001  aImp.Read( rStrm );
//STRIP001  aRange = aImp.GetRange();
//STRIP001
//STRIP001  BOOL bOk = StartPaste();
//STRIP001  if (bOk)
//STRIP001  {
//STRIP001      //  ScHTMLImport may call ScDocument::InitDrawLayer, resulting in
//STRIP001      //  a DrawLayer but no DrawView -> create DrawLayer and View here
//STRIP001      if (pDocSh)
//STRIP001          pDocSh->MakeDrawLayer();
//STRIP001
//STRIP001      USHORT nFlags = IDF_ALL & ~IDF_STYLES;
//STRIP001      pDoc->DeleteAreaTab( aRange, nFlags );
//STRIP001      aImp.WriteToDocument();
//STRIP001      EndPaste();
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


}
