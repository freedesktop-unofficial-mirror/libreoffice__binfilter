/*************************************************************************
 *
 *  $RCSfile: sw_fltini.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:23:04 $
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

#pragma hdrstop

#define _SVSTDARR_STRINGS

#include <string.h>
#include <stdio.h>          // sscanf

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _LANG_HXX
#include <tools/lang.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _PARHTML_HXX //autogen
#include <svtools/parhtml.hxx>
#endif
#include <svtools/svstdarr.hxx>
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_TSPTITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _FLTINI_HXX
#include <fltini.hxx>
#endif
#ifndef _SWGPAR_HXX
#include <swgpar.hxx>           // fuer den SW/G Parser
#endif
#ifndef _SW3IO_HXX
#include <sw3io.hxx>
#endif
#ifndef _W4WFLT_HXX
#include <w4wflt.hxx>           // AutoDetect
#endif
#ifndef _IODETECT_HXX
#include <iodetect.hxx>
#endif
#ifndef _HINTS_HXX //autogen
#include <hints.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen wg. SvxBoxItem
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SWFLTOPT_HXX
#include <swfltopt.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

SwRead ReadRtf = 0, ReadAscii = 0, ReadSwg = 0, ReadSw3 = 0,
        ReadHTML = 0, ReadXML = 0;

/*N*/ inline BOOL IsDocShellRegistered() { return 0 != SwDocShell::_GetInterface(); }

/*N*/ IO_DETECT_IMPL1
/*N*/ IO_DETECT_IMPL2
/*N*/ IO_DETECT_IMPL3
/*N*/ IO_DETECT_IMPL4


/*N*/ inline void _SetFltPtr( USHORT& rPos, SwRead pReader
/*N*/                       , const sal_Char* pNm
/* pNm optimiert der Compiler weg, wird nur in der nicht PRODUCT benoetigt! */
/*N*/                       )
/*N*/ {
/*N*/   ASSERT( !strcmp( aReaderWriter[ rPos ].pName, pNm ), "falscher Filter" );
/*N*/   aReaderWriter[ rPos++ ].pReader = pReader;
/*N*/ }

/*N*/ void _InitFilter()
/*N*/ {
//STRIP001 /*N*/    SwRead pRd, pWW8Rd = new WW8Reader;
/*N*/
/*N*/   USHORT nCnt = 0;
/*N*/   _SetFltPtr( nCnt, (ReadSw3 = new Sw3Reader), FILTER_SW5 );
/*N*/   _SetFltPtr( nCnt, ReadSw3, FILTER_SW4 );
/*N*/   _SetFltPtr( nCnt, ReadSw3, FILTER_SW3 );
/*N*/   _SetFltPtr( nCnt, (ReadSwg = new SwgReader), FILTER_SWG );
/*N*/   _SetFltPtr( nCnt, ReadSwg, FILTER_SWGV );
//STRIP001 /*?*/    _SetFltPtr( nCnt, (ReadRtf = new RtfReader), FILTER_RTF );
//STRIP001 /*?*/    _SetFltPtr( nCnt, new Sw6Reader, sSwDos );
/*N*/   _SetFltPtr( nCnt, (ReadAscii = new AsciiReader), FILTER_BAS );
//STRIP001 /*N*/    _SetFltPtr( nCnt, pWW8Rd, sWW6 );
//STRIP001 /*N*/    _SetFltPtr( nCnt, pWW8Rd, FILTER_WW8 );
//STRIP001 /*N*/    _SetFltPtr( nCnt, new W4WReader, FILTER_W4W );
//STRIP001 /*N*/    _SetFltPtr( nCnt, ReadRtf, sRtfWH );
//STRIP001 /*N*/    _SetFltPtr( nCnt, ( pRd = new ExcelReader ), sCExcel );
//STRIP001 /*N*/    _SetFltPtr( nCnt, pRd, sExcel );
//STRIP001 /*N*/    _SetFltPtr( nCnt, new LotusReader, sLotusD );
//STRIP001 /*?*/    _SetFltPtr( nCnt, (ReadHTML = new HTMLReader), sHTML);
//STRIP001 /*N*/    _SetFltPtr( nCnt, new WW1Reader, sWW1 );
//STRIP001 /*N*/    _SetFltPtr( nCnt, pWW8Rd, sWW5 );
/*N*/   _SetFltPtr( nCnt, ReadSwg, sSwg1 );
/*?*/   _SetFltPtr( nCnt, (ReadXML = new XMLReader), FILTER_XML );
/*N*/
/*N*/ #ifdef NEW_WW97_EXPORT
//STRIP001 /*?*/    aReaderWriter[ 8 ].fnGetWriter =  &::GetWW8Writer;
//STRIP001 /*?*/    aReaderWriter[ 9 ].fnGetWriter = &::GetWW8Writer;
/*N*/ #endif
/*N*/
/*N*/ #ifdef DEBUG_SH
//STRIP001 /*N*/    _SetFltPtr( nCnt, new Internal_W4WReader, sW4W_Int);
/*N*/ #endif // DEBUG_SH
/*N*/
/*N*/ #if !( defined(PRODUCT) || defined(MAC) || defined(PM2))
//STRIP001 /*N*/    nCnt += 2;      // haben keine Reader sind nur EXPORT!
/*N*/ #endif
/*N*/
/*N*/     _SetFltPtr( nCnt, ReadAscii, FILTER_TEXT );
/*N*/
/*N*/   ASSERT( MAXFILTER == nCnt, "Anzahl Filter ungleich der Definierten" );
/*N*/ }




/*N*/ void _FinitFilter()
/*N*/ {
/*N*/   // die Reader vernichten
/*N*/   for( USHORT n = 0; n < MAXFILTER; ++n )
/*N*/   {
/*N*/       SwIoDetect& rIo = aReaderWriter[n];
/*N*/       if( rIo.bDelReader && rIo.pReader )
/*N*/           delete rIo.pReader;
/*N*/   }
/*N*/ }


/*  */

/*N*/ void SwIoSystem::GetWriter( const String& rFltName, WriterRef& xRet )
/*N*/ {
/*N*/   for( USHORT n = 0; n < MAXFILTER; ++n )
/*N*/       if( aReaderWriter[n].IsFilter( rFltName ) )
/*N*/       {
/*N*/           aReaderWriter[n].GetWriter( rFltName, xRet );
/*N*/           break;
/*N*/       }
/*N*/ }


//STRIP001 SwRead SwIoSystem::GetReader( const String& rFltName )
//STRIP001 {
//STRIP001  SwRead pRead = 0;
//STRIP001  for( USHORT n = 0; n < MAXFILTER; ++n )
//STRIP001      if( aReaderWriter[n].IsFilter( rFltName ) )
//STRIP001      {
//STRIP001          pRead = aReaderWriter[n].GetReader();
//STRIP001          // fuer einige Reader noch eine Sonderbehandlung:
//STRIP001          pRead->SetFltName( rFltName );
//STRIP001          break;
//STRIP001      }
//STRIP001  return pRead;
//STRIP001 }

        // suche ueber den Filtertext den Filtereintrag
/*N*/ const SfxFilter* SwIoSystem::GetFilterOfFilterTxt( const String& rFilterNm,
/*N*/                               const SfxFactoryFilterContainer* pCnt )
/*N*/ {
/*N*/   const SfxFactoryFilterContainer* pFltCnt = pCnt ? pCnt :
/*N*/       ( IsDocShellRegistered()
/*N*/           ? SwDocShell::Factory().GetFilterContainer()
/*N*/           : SwWebDocShell::Factory().GetFilterContainer() );
/*N*/
/*N*/   do {
/*N*/       if( pFltCnt )
/*N*/       {
/*N*/           const SfxFilter* pFilter;
/*N*/           USHORT nCount = pFltCnt->GetFilterCount();
/*N*/           for( USHORT i = 0; i < nCount; ++i )
/*N*/               if( ( pFilter = pFltCnt->GetFilter( i ))->GetFilterName() == rFilterNm )
/*N*/                   return pFilter;
/*N*/       }
/*?*/       if( pCnt || pFltCnt == SwWebDocShell::Factory().GetFilterContainer())
/*?*/           break;
/*?*/       pFltCnt = SwWebDocShell::Factory().GetFilterContainer();
/*?*/   } while( TRUE );
/*?*/
/*?*/   return 0;
/*N*/ }


/*  */

/////////////// die Storage Reader/Writer ////////////////////////////////

//STRIP001 #if 0    // SH: WW8-Writer als Fake ueber WW6-Writer
//STRIP001 Writer* GetWW8Writer( const String& )
//STRIP001 {
//STRIP001  ASSERT( FALSE, "WinWord 97 - Writer ist noch nicht implementiert" );
//STRIP001  return 0;
//STRIP001 }
//STRIP001 #endif

/*N*/ void GetSw3Writer( const String&, WriterRef& xRet )
/*N*/ {
/*N*/   xRet = new Sw3Writer;
/*N*/ }


//STRIP001 ULONG StgReader::OpenMainStream( SvStorageStreamRef& rRef, USHORT& rBuffSize )
//STRIP001 {
//STRIP001  ULONG nRet = ERR_SWG_READ_ERROR;
//STRIP001  ASSERT( pStg, "wo ist mein Storage?" );
//STRIP001  const SfxFilter* pFltr = SwIoSystem::GetFilterOfFormat( aFltName );
//STRIP001  if( pFltr )
//STRIP001  {
//STRIP001      rRef = pStg->OpenStream( SwIoSystem::GetSubStorageName( *pFltr ),
//STRIP001                                  STREAM_READ | STREAM_SHARE_DENYALL );
//STRIP001
//STRIP001      if( rRef.Is() )
//STRIP001      {
//STRIP001          if( SVSTREAM_OK == rRef->GetError() )
//STRIP001          {
//STRIP001              USHORT nOld = rRef->GetBufferSize();
//STRIP001              rRef->SetBufferSize( rBuffSize );
//STRIP001              rBuffSize = nOld;
//STRIP001              nRet = 0;
//STRIP001          }
//STRIP001          else
//STRIP001              nRet = rRef->GetError();
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/*  */


/*N*/ ULONG Sw3Reader::Read( SwDoc &rDoc, SwPaM &rPam, const String & )
/*N*/ {
/*N*/   ULONG nRet;
/*N*/   if( pStg && pIO )
/*N*/   {
/*N*/       // TRUE: Vorlagen ueberschreiben
/*N*/       pIO->SetReadOptions( aOpt,TRUE );
/*N*/       if( !bInsertMode )
/*N*/       {
/*N*/           // Im Laden-Modus darf der PaM-Content-Teil nicht
/*N*/           // in den Textbereich zeigen (Nodes koennen geloescht werden)
/*N*/           rPam.GetBound( TRUE ).nContent.Assign( 0, 0 );
/*N*/           rPam.GetBound( FALSE ).nContent.Assign( 0, 0 );
/*N*/       }
/*N*/       nRet = pIO->Load( pStg, bInsertMode ? &rPam : 0 );
/*N*/       aOpt.ResetAllFmtsOnly();
/*N*/       pIO->SetReadOptions( aOpt, TRUE );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       ASSERT( !this, "Sw3-Read ohne Storage und/oder IO-System" );
/*?*/       nRet = ERR_SWG_READ_ERROR;
/*N*/   }
/*N*/   return nRet;
/*N*/ }

    // read the sections of the document, which is equal to the medium.
    // returns the count of it
//STRIP001 USHORT Sw3Reader::GetSectionList( SfxMedium& rMedium,
//STRIP001                                  SvStrings& rStrings ) const
//STRIP001 {
//STRIP001  SvStorageRef aStg( rMedium.GetStorage() );
//STRIP001  const SfxFilter* pFlt = rMedium.GetFilter();
//STRIP001  ASSERT( pFlt && pFlt->GetVersion(),
//STRIP001                              "Kein Filter oder Filter ohne FF-Version" );
//STRIP001  if( pFlt && pFlt->GetVersion() )
//STRIP001      aStg->SetVersion( (long)pFlt->GetVersion() );
//STRIP001
//STRIP001  if( pIO )
//STRIP001      pIO->GetSectionList( &aStg, rStrings );
//STRIP001  return rStrings.Count();
//STRIP001 }


/*N*/ ULONG Sw3Writer::WriteStorage()
/*N*/ {
/*N*/   ULONG nRet;
/*N*/   if( pIO )
/*N*/   {
/*N*/       // der gleiche Storage -> Save, sonst SaveAs aufrufen
/*N*/       if( !bSaveAs )
/*?*/           nRet = pIO->Save( pOrigPam, bWriteAll );
/*N*/       else
/*N*/           nRet = pIO->SaveAs( pStg, pOrigPam, bWriteAll );
/*N*/
/*N*/       pIO = 0;        // nach dem Schreiben ist der Pointer ungueltig !!
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       ASSERT( !this, "Sw3-Writer ohne IO-System" )
/*?*/       nRet = ERR_SWG_WRITE_ERROR;
/*N*/   }
/*N*/   return nRet;
/*N*/ }

//STRIP001 BOOL Sw3Writer::IsSw3Writer() const { return TRUE; }


//STRIP001 void Writer::SetPasswd( const String& ) {}


//STRIP001 void Writer::SetVersion( const String&, long ) {}


 BOOL Writer::IsStgWriter() const { return FALSE; }
 BOOL Writer::IsSw3Writer() const { return FALSE; }

//STRIP001 BOOL StgWriter::IsStgWriter() const { return TRUE; }

/*  */


//STRIP001 ULONG SwgReader::Read( SwDoc &rDoc, SwPaM &rPam, const String& rFileName )
//STRIP001 {
//STRIP001  if( !pStrm )
//STRIP001  {
//STRIP001      ASSERT( !this, "SWG-Read ohne Stream" );
//STRIP001      return ERR_SWG_READ_ERROR;
//STRIP001  }
//STRIP001  SwSwgParser *pSwgParser = new SwSwgParser( &rDoc, &rPam, pStrm,
//STRIP001                                              rFileName, !bInsertMode );
//STRIP001  USHORT nBits = SWGRD_NORMAL;
//STRIP001  SwgReader* pRdr = (SwgReader*) ReadSwg;
//STRIP001  if( pRdr->aOpt.IsFmtsOnly() )
//STRIP001  {
//STRIP001      nBits = 0;
//STRIP001      if( pRdr->aOpt.IsFrmFmts()   ) nBits |= SWGRD_FRAMEFMTS;
//STRIP001      if( pRdr->aOpt.IsTxtFmts()   ) nBits |= SWGRD_CHARFMTS | SWGRD_PARAFMTS;
//STRIP001      if( pRdr->aOpt.IsPageDescs() ) nBits |= SWGRD_PAGEFMTS;
//STRIP001      if( !pRdr->aOpt.IsMerge() )
//STRIP001          nBits |= SWGRD_FORCE;
//STRIP001  }
//STRIP001  ULONG nRet = pSwgParser->CallParser( nBits );
//STRIP001  delete pSwgParser;
//STRIP001
//STRIP001  // die Flags muessen natuerlich wieder geloescht werden!
//STRIP001  pRdr->aOpt.ResetAllFmtsOnly();
//STRIP001
//STRIP001  return nRet;
//STRIP001 }


//STRIP001 BOOL SwReader::NeedsPasswd( const Reader& rOptions )
//STRIP001 {
//STRIP001  BOOL bRes = FALSE;
//STRIP001  if( &rOptions == ReadSwg )
//STRIP001  {
//STRIP001      if( !pStrm && pMedium && !pMedium->IsStorage() )
//STRIP001          pStrm = pMedium->GetInStream();
//STRIP001
//STRIP001      ASSERT( pStrm, "Passwort-Test ohne Stream" );
//STRIP001      if( pStrm )
//STRIP001      {
//STRIP001          SwSwgParser *pSwgParser = new SwSwgParser( pStrm );
//STRIP001          bRes = pSwgParser->NeedsPasswd();
//STRIP001          delete pSwgParser;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRes;
//STRIP001 }


//STRIP001 BOOL SwReader::CheckPasswd( const String& rPasswd, const Reader& rOptions )
//STRIP001 {
//STRIP001  BOOL bRes = TRUE;
//STRIP001  if( &rOptions == ReadSwg )
//STRIP001  {
//STRIP001      if( !pStrm && pMedium && !pMedium->IsStorage() )
//STRIP001          pStrm = pMedium->GetInStream();
//STRIP001
//STRIP001      ASSERT( pStrm, "Passwort-Check ohne Stream" );
//STRIP001      if( pStrm )
//STRIP001      {
//STRIP001          SwSwgParser *pSwgParser = new SwSwgParser( pStrm );
//STRIP001          bRes = pSwgParser->CheckPasswd( rPasswd );
//STRIP001          delete pSwgParser;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRes;
//STRIP001 }


/*  */

//-----------------------------------------------------------------------
// Filter Flags lesen, wird von WW8 / W4W / EXCEL / LOTUS benutzt.
//-----------------------------------------------------------------------

/*
<FilterFlags>
        <Excel_Lotus>
                <MinRow cfg:type="long">0</MinRow>
                <MaxRow cfg:type="long">0</MaxRow>
                <MinCol cfg:type="long">0</MinCol>
                <MaxCol cfg:type="long">0</MaxCol>
        </Excel_Lotus>
        <W4W>
                <W4WHD cfg:type="long">0</W4WHD>
                <W4WFT cfg:type="long">0</W4WFT>
                <W4W000 cfg:type="long">0</W4W000>
        </W4W>
        <WinWord>
                <WW1F cfg:type="long">0</WW1F>
                <WW cfg:type="long">0</WW>
                <WW8 cfg:type="long">0</WW8>
                <WWF cfg:type="long">0</WWF>
                <WWFA0 cfg:type="long">0</WWFA0>
                <WWFA1 cfg:type="long">0</WWFA1>
                <WWFA2 cfg:type="long">0</WWFA2>
                <WWFB0 cfg:type="long">0</WWFB0>
                <WWFB1 cfg:type="long">0</WWFB1>
                <WWFB2 cfg:type="long">0</WWFB2>
                <WWFLX cfg:type="long">0</WWFLX>
                <WWFLY cfg:type="long">0</WWFLY>
                <WWFT cfg:type="long">0</WWFT>
                <WWWR cfg:type="long">0</WWWR>
        </WinWord>
        <Writer>
                <SW3Imp cfg:type="long">0</SW3Imp>
        </Writer>
</FilterFlags>
*/

/*N*/ #define FILTER_OPTION_ROOT        String::CreateFromAscii( \
/*N*/               RTL_CONSTASCII_STRINGPARAM( "Office.Writer/FilterFlags" ) )

//STRIP001 SwFilterOptions::SwFilterOptions()
//STRIP001  : ConfigItem( FILTER_OPTION_ROOT )
//STRIP001 {
//STRIP001 }

/*N*/ SwFilterOptions::SwFilterOptions( sal_uInt16 nCnt, const sal_Char** ppNames,
/*N*/                               sal_uInt32* pValues )
/*N*/   : ConfigItem( FILTER_OPTION_ROOT )
/*N*/ {
/*N*/   GetValues( nCnt, ppNames, pValues );
/*N*/ }

/*N*/ void SwFilterOptions::GetValues( sal_uInt16 nCnt, const sal_Char** ppNames,
/*N*/                                   sal_uInt32* pValues )
/*N*/ {
/*N*/   Sequence<OUString> aNames( nCnt );
/*N*/   OUString* pNames = aNames.getArray();
        USHORT n=0;
/*N*/   for( n = 0; n < nCnt; ++n )
/*N*/       pNames[ n ] = OUString::createFromAscii( ppNames[ n ] );
/*N*/   Sequence<Any> aValues = GetProperties( aNames );
/*N*/
/*N*/   if( nCnt == aValues.getLength() )
/*N*/   {
/*N*/       const Any* pAnyValues = aValues.getConstArray();
/*N*/       for( n = 0; n < nCnt; ++n )
/*N*/           pValues[ n ] = pAnyValues[ n ].hasValue()
/*N*/                           ? *(sal_uInt32*)pAnyValues[ n ].getValue()
/*N*/                           : 0;
/*N*/   }
/*N*/   else
/*?*/       for( n = 0; n < nCnt; ++n )
/*?*/           pValues[ n ] = 0;
/*N*/ }

//STRIP001 sal_Bool SwFilterOptions::CheckNodeContentExist( const sal_Char* pNode,
//STRIP001                                               const sal_Char* pCntnt )
//STRIP001 {
//STRIP001  Sequence<OUString> aNames( GetNodeNames(
//STRIP001                                      OUString::createFromAscii( pNode )));
//STRIP001  sal_Bool bExist = sal_False;
//STRIP001  const OUString* pNames = aNames.getConstArray();
//STRIP001  for( long n = 0, nEnd = aNames.getLength(); n < nEnd; ++n, ++pNames )
//STRIP001      if( !pNames->compareToAscii( pCntnt ))
//STRIP001      {
//STRIP001          bExist = sal_True;
//STRIP001          break;
//STRIP001      }
//STRIP001  return bExist;
//STRIP001 }

/*  */


//STRIP001 void LotusReader::SetFltName( const String& rFltNm )
//STRIP001 {
//STRIP001  eCodeSet = rFltNm.EqualsAscii( sLotusD ) ? RTL_TEXTENCODING_IBM_850
//STRIP001                                           : RTL_TEXTENCODING_MS_1252;
//STRIP001 }


//STRIP001 void StgReader::SetFltName( const String& rFltNm )
//STRIP001 {
//STRIP001  if( SW_STORAGE_READER & GetReaderType() )
//STRIP001      aFltName = rFltNm;
//STRIP001 }


/*  */

//STRIP001 SwRelNumRuleSpaces::SwRelNumRuleSpaces( SwDoc& rDoc, BOOL bNDoc )
//STRIP001  : bNewDoc( bNDoc )
//STRIP001 {
//STRIP001  pNumRuleTbl = new SwNumRuleTbl( 8, 8 );
//STRIP001  if( !bNDoc )
//STRIP001      pNumRuleTbl->Insert( &rDoc.GetNumRuleTbl(), 0 );
//STRIP001 }

//STRIP001 SwRelNumRuleSpaces::~SwRelNumRuleSpaces()
//STRIP001 {
//STRIP001  if( pNumRuleTbl )
//STRIP001  {
//STRIP001      pNumRuleTbl->Remove( 0, pNumRuleTbl->Count() );
//STRIP001      delete pNumRuleTbl;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwRelNumRuleSpaces::SetNumRelSpaces( SwDoc& rDoc )
//STRIP001 {
//STRIP001  SwNumRuleTbl* pRuleTbl = bNewDoc ? &rDoc.GetNumRuleTbl() : pNumRuleTbl;
//STRIP001  if( !bNewDoc )
//STRIP001  {
//STRIP001      // jetzt alle schon vorhanden NumRules aus dem Array entfernen,
//STRIP001      // damit nur die neuen angepasst werden
//STRIP001      SwNumRuleTbl aNumRuleTbl;
//STRIP001      aNumRuleTbl.Insert( pRuleTbl, 0 );
//STRIP001      pRuleTbl->Remove( 0, pRuleTbl->Count() );
//STRIP001      const SwNumRuleTbl& rRuleTbl = rDoc.GetNumRuleTbl();
//STRIP001      SwNumRule* pRule;
//STRIP001
//STRIP001      for( USHORT n = 0; n < rRuleTbl.Count(); ++n )
//STRIP001          if( USHRT_MAX == aNumRuleTbl.GetPos( ( pRule = rRuleTbl[ n ] )))
//STRIP001              // war noch nicht vorhanden, also neu
//STRIP001              pRuleTbl->Insert( pRule, pRuleTbl->Count() );
//STRIP001
//STRIP001      aNumRuleTbl.Remove( 0, aNumRuleTbl.Count() );
//STRIP001  }
//STRIP001
//STRIP001  if( pRuleTbl )
//STRIP001  {
//STRIP001      for( USHORT n = pRuleTbl->Count(); n; )
//STRIP001      {
//STRIP001          SwNumRule* pRule = (*pRuleTbl)[ --n ];
//STRIP001          // Rule noch gueltig und am Doc vorhanden?
//STRIP001          if( USHRT_MAX != rDoc.GetNumRuleTbl().GetPos( pRule ))
//STRIP001          {
//STRIP001              SwNumRuleInfo aUpd( pRule->GetName() );
//STRIP001              aUpd.MakeList( rDoc );
//STRIP001
//STRIP001              // bei allen nmumerierten Absaetzen vom linken Rand
//STRIP001              // den absoluten Wert des NumFormates abziehen
//STRIP001              for( ULONG nUpdPos = 0; nUpdPos < aUpd.GetList().Count();
//STRIP001                  ++nUpdPos )
//STRIP001              {
//STRIP001                  SwTxtNode* pNd = aUpd.GetList().GetObject( nUpdPos );
//STRIP001                  SetNumLSpace( *pNd, *pRule );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pNumRuleTbl )
//STRIP001  {
//STRIP001      pNumRuleTbl->Remove( 0, pNumRuleTbl->Count() );
//STRIP001      delete pNumRuleTbl, pNumRuleTbl = 0;
//STRIP001  }
//STRIP001
//STRIP001  if( bNewDoc )
//STRIP001  {
//STRIP001      SetOultineRelSpaces( SwNodeIndex( rDoc.GetNodes() ),
//STRIP001                          SwNodeIndex( rDoc.GetNodes().GetEndOfContent()));
//STRIP001  }
//STRIP001 }

//STRIP001 void SwRelNumRuleSpaces::SetOultineRelSpaces( const SwNodeIndex& rStt,
//STRIP001                                          const SwNodeIndex& rEnd )
//STRIP001 {
//STRIP001  SwDoc* pDoc = rStt.GetNode().GetDoc();
//STRIP001  const SwOutlineNodes& rOutlNds = pDoc->GetNodes().GetOutLineNds();
//STRIP001  if( rOutlNds.Count() )
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      rOutlNds.Seek_Entry( &rStt.GetNode(), &nPos );
//STRIP001      for( ; nPos < rOutlNds.Count() &&
//STRIP001              rOutlNds[ nPos ]->GetIndex() < rEnd.GetIndex(); ++nPos )
//STRIP001      {
//STRIP001          SwTxtNode* pNd = rOutlNds[ nPos ]->GetTxtNode();
//STRIP001          if( pNd->GetOutlineNum() && !pNd->GetNumRule() )
//STRIP001              SetNumLSpace( *pNd, *pDoc->GetOutlineNumRule() );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwRelNumRuleSpaces::SetNumLSpace( SwTxtNode& rNd, const SwNumRule& rRule )
//STRIP001 {
//STRIP001  BOOL bOutlineRule = OUTLINE_RULE == rRule.GetRuleType();
//STRIP001  BYTE nLvl;
//STRIP001  {
//STRIP001      SwNodeNum aNdNum( 0 );
//STRIP001      const SwNodeNum* pNum;
//STRIP001      if( bOutlineRule )
//STRIP001      {
//STRIP001          if( 0 == ( pNum = rNd.GetOutlineNum() ))
//STRIP001              pNum = rNd.UpdateOutlineNum( aNdNum );
//STRIP001      }
//STRIP001      else if( 0 == ( pNum = rNd.GetNum() ))
//STRIP001          pNum = rNd.UpdateNum( aNdNum );
//STRIP001      nLvl = GetRealLevel( pNum->GetLevel() );
//STRIP001  }
//STRIP001  const SwNumFmt& rFmt = rRule.Get( nLvl );
//STRIP001  const SvxLRSpaceItem& rLR = rNd.GetSwAttrSet().GetLRSpace();
//STRIP001
//STRIP001  SvxLRSpaceItem aLR( rLR );
//STRIP001  aLR.SetTxtFirstLineOfst( 0 );
//STRIP001
//STRIP001  // sagt der Node, das die Numerierung den Wert vorgibt?
//STRIP001  if( !bOutlineRule && rNd.IsSetNumLSpace() )
//STRIP001      aLR.SetTxtLeft( 0 );
//STRIP001  else
//STRIP001  {
//STRIP001      long nLeft = rFmt.GetAbsLSpace(), nParaLeft = rLR.GetTxtLeft();
//STRIP001      if( 0 < rLR.GetTxtFirstLineOfst() )
//STRIP001          nParaLeft += rLR.GetTxtFirstLineOfst();
//STRIP001      else if( nParaLeft >= nLeft )
//STRIP001          // #82963#/#82962#: set correct paragraph indent
//STRIP001          nParaLeft -= nLeft;
//STRIP001      else
//STRIP001          //#83154#, Don't think any of the older #80856# bugfix code is
//STRIP001          //relevent anymore.
//STRIP001          nParaLeft = rLR.GetTxtLeft()+rLR.GetTxtFirstLineOfst();
//STRIP001      aLR.SetTxtLeft( nParaLeft );
//STRIP001  }
//STRIP001
//STRIP001  if( aLR.GetTxtLeft() != rLR.GetTxtLeft() )
//STRIP001  {
//STRIP001      //bevor rLR geloescht wird!
//STRIP001      long nOffset = rLR.GetTxtLeft() - aLR.GetTxtLeft();
//STRIP001      rNd.SwCntntNode::SetAttr( aLR );
//STRIP001
//STRIP001      // Tabs anpassen !!
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if( SFX_ITEM_SET == rNd.GetSwAttrSet().GetItemState(
//STRIP001              RES_PARATR_TABSTOP, TRUE, &pItem ))
//STRIP001      {
//STRIP001          SvxTabStopItem aTStop( *(SvxTabStopItem*)pItem );
//STRIP001          for( USHORT n = 0; n < aTStop.Count(); ++n )
//STRIP001          {
//STRIP001              SvxTabStop& rTab = (SvxTabStop&)aTStop[ n ];
//STRIP001              if( SVX_TAB_ADJUST_DEFAULT != rTab.GetAdjustment() )
//STRIP001              {
//STRIP001                  if( !rTab.GetTabPos() )
//STRIP001                  {
//STRIP001                      aTStop.Remove( n );
//STRIP001                      --n;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      rTab.GetTabPos() += nOffset;
//STRIP001              }
//STRIP001          }
//STRIP001          rNd.SwCntntNode::SetAttr( aTStop );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*  */


//STRIP001 void CalculateFlySize( SfxItemSet& rFlySet, SwNodeIndex& rAnchor,
//STRIP001                        SwTwips nPageWidth )
//STRIP001 {
//STRIP001  const SfxPoolItem* pItem = 0;
//STRIP001  if( SFX_ITEM_SET != rFlySet.GetItemState( RES_FRM_SIZE, TRUE, &pItem ) ||
//STRIP001      MINFLY > ((SwFmtFrmSize*)pItem)->GetWidth() )
//STRIP001  {
//STRIP001      SwFmtFrmSize aSz( (SwFmtFrmSize&) (pItem ? *pItem
//STRIP001                                  : rFlySet.Get( RES_FRM_SIZE, TRUE )) );
//STRIP001
//STRIP001      SwTwips nWidth;
//STRIP001      // dann die Breite des Flys selbst bestimmen. Ist eine Tabelle
//STRIP001      // defininiert, dann benutze deren Breite, sonst die Breite der
//STRIP001      // Seite
//STRIP001      const SwTableNode* pTblNd = rAnchor.GetNode().FindTableNode();
//STRIP001      if( pTblNd )
//STRIP001          nWidth = pTblNd->GetTable().GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      else
//STRIP001          nWidth = nPageWidth;
//STRIP001
//STRIP001      const SwNodeIndex* pSttNd = ((SwFmtCntnt&)rFlySet.Get( RES_CNTNT )).
//STRIP001                                  GetCntntIdx();
//STRIP001      if( pSttNd )
//STRIP001      {
//STRIP001          BOOL bOnlyOneNode = TRUE;
//STRIP001          ULONG nMinFrm = 0;
//STRIP001          ULONG nMaxFrm = 0;
//STRIP001          SwTxtNode* pFirstTxtNd = 0;
//STRIP001          SwNodeIndex aIdx( *pSttNd, 1 );
//STRIP001          SwNodeIndex aEnd( *pSttNd->GetNode().EndOfSectionNode() );
//STRIP001          while( aIdx < aEnd )
//STRIP001          {
//STRIP001              SwTxtNode *pTxtNd = aIdx.GetNode().GetTxtNode();
//STRIP001              if( pTxtNd )
//STRIP001              {
//STRIP001                  if( !pFirstTxtNd )
//STRIP001                      pFirstTxtNd = pTxtNd;
//STRIP001                  else if( pFirstTxtNd != pTxtNd )
//STRIP001                  {
//STRIP001                      // forget it
//STRIP001                      bOnlyOneNode = FALSE;
//STRIP001                      break;
//STRIP001                  }
//STRIP001
//STRIP001                  ULONG nAbsMinCnts;
//STRIP001                  pTxtNd->GetMinMaxSize( aIdx.GetIndex(), nMinFrm,
//STRIP001                                          nMaxFrm, nAbsMinCnts );
//STRIP001              }
//STRIP001              aIdx++;
//STRIP001          }
//STRIP001
//STRIP001          if( bOnlyOneNode )
//STRIP001          {
//STRIP001              if( nMinFrm < MINLAY && pFirstTxtNd )
//STRIP001              {
//STRIP001                  // if the first node dont contained any content, then
//STRIP001                  // insert one char in it calc again and delete once again
//STRIP001                  SwIndex aNdIdx( pFirstTxtNd );
//STRIP001                  pFirstTxtNd->Insert( String::CreateFromAscii(
//STRIP001                          RTL_CONSTASCII_STRINGPARAM( "MM" )), aNdIdx );
//STRIP001                  ULONG nAbsMinCnts;
//STRIP001                  pFirstTxtNd->GetMinMaxSize( pFirstTxtNd->GetIndex(),
//STRIP001                                          nMinFrm, nMaxFrm, nAbsMinCnts );
//STRIP001                  aNdIdx -= 2;
//STRIP001                  pFirstTxtNd->Erase( aNdIdx, 2 );
//STRIP001              }
//STRIP001
//STRIP001              // Umrandung und Abstand zum Inhalt beachten
//STRIP001              const SvxBoxItem& rBoxItem = (SvxBoxItem&)rFlySet.Get( RES_BOX );
//STRIP001              USHORT nLine = BOX_LINE_LEFT;
//STRIP001              for( int i = 0; i < 2; ++i )
//STRIP001              {
//STRIP001                  const SvxBorderLine* pLn = rBoxItem.GetLine( nLine );
//STRIP001                  if( pLn )
//STRIP001                  {
//STRIP001                      USHORT nWidth = pLn->GetOutWidth() + pLn->GetInWidth();
//STRIP001                      nWidth += rBoxItem.GetDistance( nLine );
//STRIP001                      nMinFrm += nWidth;
//STRIP001                      nMaxFrm += nWidth;
//STRIP001                  }
//STRIP001                  nLine = BOX_LINE_RIGHT;
//STRIP001              }
//STRIP001
//STRIP001              // Mindestbreite fuer Inhalt einhalten
//STRIP001              if( nMinFrm < MINLAY )
//STRIP001                  nMinFrm = MINLAY;
//STRIP001              if( nMaxFrm < MINLAY )
//STRIP001                  nMaxFrm = MINLAY;
//STRIP001
//STRIP001              if( nWidth > (USHORT)nMaxFrm )
//STRIP001                  nWidth = nMaxFrm;
//STRIP001              else if( nWidth > (USHORT)nMinFrm )
//STRIP001                  nWidth = nMinFrm;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( MINFLY > nWidth )
//STRIP001          nWidth = MINFLY;
//STRIP001
//STRIP001      aSz.SetWidth( nWidth );
//STRIP001      if( MINFLY > aSz.GetHeight() )
//STRIP001          aSz.SetHeight( MINFLY );
//STRIP001      rFlySet.Put( aSz );
//STRIP001  }
//STRIP001  else if( MINFLY > ((SwFmtFrmSize*)pItem)->GetHeight() )
//STRIP001  {
//STRIP001      SwFmtFrmSize aSz( *(SwFmtFrmSize*)pItem );
//STRIP001      aSz.SetHeight( MINFLY );
//STRIP001      rFlySet.Put( aSz );
//STRIP001  }
//STRIP001 }

/*  */
//STRIP001 struct CharSetNameMap
//STRIP001 {
//STRIP001     rtl_TextEncoding eCode;
//STRIP001     const sal_Char* pName;
//STRIP001 };

//STRIP001 const CharSetNameMap *GetCharSetNameMap()
//STRIP001 {
//STRIP001     static const CharSetNameMap aMapArr[] =
//STRIP001     {
//STRIP001 #   define IMPLENTRY(X) { RTL_TEXTENCODING_##X, "" #X "" }
//STRIP001         IMPLENTRY(DONTKNOW),
//STRIP001         IMPLENTRY(MS_1252),
//STRIP001         IMPLENTRY(APPLE_ROMAN),
//STRIP001         IMPLENTRY(IBM_437),
//STRIP001         IMPLENTRY(IBM_850),
//STRIP001         IMPLENTRY(IBM_860),
//STRIP001         IMPLENTRY(IBM_861),
//STRIP001         IMPLENTRY(IBM_863),
//STRIP001         IMPLENTRY(IBM_865),
//STRIP001         IMPLENTRY(SYMBOL),
//STRIP001         IMPLENTRY(ASCII_US),
//STRIP001         IMPLENTRY(ISO_8859_1),
//STRIP001         IMPLENTRY(ISO_8859_2),
//STRIP001         IMPLENTRY(ISO_8859_3),
//STRIP001         IMPLENTRY(ISO_8859_4),
//STRIP001         IMPLENTRY(ISO_8859_5),
//STRIP001         IMPLENTRY(ISO_8859_6),
//STRIP001         IMPLENTRY(ISO_8859_7),
//STRIP001         IMPLENTRY(ISO_8859_8),
//STRIP001         IMPLENTRY(ISO_8859_9),
//STRIP001         IMPLENTRY(ISO_8859_14),
//STRIP001         IMPLENTRY(ISO_8859_15),
//STRIP001         IMPLENTRY(IBM_737),
//STRIP001         IMPLENTRY(IBM_775),
//STRIP001         IMPLENTRY(IBM_852),
//STRIP001         IMPLENTRY(IBM_855),
//STRIP001         IMPLENTRY(IBM_857),
//STRIP001         IMPLENTRY(IBM_862),
//STRIP001         IMPLENTRY(IBM_864),
//STRIP001         IMPLENTRY(IBM_866),
//STRIP001         IMPLENTRY(IBM_869),
//STRIP001         IMPLENTRY(MS_874),
//STRIP001         IMPLENTRY(MS_1250),
//STRIP001         IMPLENTRY(MS_1251),
//STRIP001         IMPLENTRY(MS_1253),
//STRIP001         IMPLENTRY(MS_1254),
//STRIP001         IMPLENTRY(MS_1255),
//STRIP001         IMPLENTRY(MS_1256),
//STRIP001         IMPLENTRY(MS_1257),
//STRIP001         IMPLENTRY(MS_1258),
//STRIP001         IMPLENTRY(APPLE_ARABIC),
//STRIP001         IMPLENTRY(APPLE_CENTEURO),
//STRIP001         IMPLENTRY(APPLE_CROATIAN),
//STRIP001         IMPLENTRY(APPLE_CYRILLIC),
//STRIP001         IMPLENTRY(APPLE_DEVANAGARI),
//STRIP001         IMPLENTRY(APPLE_FARSI),
//STRIP001         IMPLENTRY(APPLE_GREEK),
//STRIP001         IMPLENTRY(APPLE_GUJARATI),
//STRIP001         IMPLENTRY(APPLE_GURMUKHI),
//STRIP001         IMPLENTRY(APPLE_HEBREW),
//STRIP001         IMPLENTRY(APPLE_ICELAND),
//STRIP001         IMPLENTRY(APPLE_ROMANIAN),
//STRIP001         IMPLENTRY(APPLE_THAI),
//STRIP001         IMPLENTRY(APPLE_TURKISH),
//STRIP001         IMPLENTRY(APPLE_UKRAINIAN),
//STRIP001         IMPLENTRY(APPLE_CHINSIMP),
//STRIP001         IMPLENTRY(APPLE_CHINTRAD),
//STRIP001         IMPLENTRY(APPLE_JAPANESE),
//STRIP001         IMPLENTRY(APPLE_KOREAN),
//STRIP001         IMPLENTRY(MS_932),
//STRIP001         IMPLENTRY(MS_936),
//STRIP001         IMPLENTRY(MS_949),
//STRIP001         IMPLENTRY(MS_950),
//STRIP001         IMPLENTRY(SHIFT_JIS),
//STRIP001         IMPLENTRY(GB_2312),
//STRIP001         IMPLENTRY(GBT_12345),
//STRIP001         IMPLENTRY(GBK),
//STRIP001         IMPLENTRY(BIG5),
//STRIP001         IMPLENTRY(EUC_JP),
//STRIP001         IMPLENTRY(EUC_CN),
//STRIP001         IMPLENTRY(EUC_TW),
//STRIP001         IMPLENTRY(ISO_2022_JP),
//STRIP001         IMPLENTRY(ISO_2022_CN),
//STRIP001         IMPLENTRY(KOI8_R),
//STRIP001         IMPLENTRY(KOI8_U),
//STRIP001         IMPLENTRY(UTF7),
//STRIP001         IMPLENTRY(UTF8),
//STRIP001         IMPLENTRY(ISO_8859_10),
//STRIP001         IMPLENTRY(ISO_8859_13),
//STRIP001         IMPLENTRY(EUC_KR),
//STRIP001         IMPLENTRY(ISO_2022_KR),
//STRIP001         IMPLENTRY(JIS_X_0201),
//STRIP001         IMPLENTRY(JIS_X_0208),
//STRIP001         IMPLENTRY(JIS_X_0212),
//STRIP001         IMPLENTRY(MS_1361),
//STRIP001         IMPLENTRY(GB_18030),
//STRIP001         IMPLENTRY(BIG5_HKSCS),
//STRIP001         IMPLENTRY(TIS_620),
//STRIP001         IMPLENTRY(UCS4),
//STRIP001         IMPLENTRY(UCS2),
//STRIP001         IMPLENTRY(UNICODE),
//STRIP001         {0,0}       //Last
//STRIP001     };
//STRIP001     return &aMapArr[0];
//STRIP001 }
/*
 Get a rtl_TextEncoding from its name
 */
//STRIP001 rtl_TextEncoding CharSetFromName(const String& rChrSetStr)
//STRIP001 {
//STRIP001     const CharSetNameMap *pStart = GetCharSetNameMap();
//STRIP001     rtl_TextEncoding nRet = pStart->eCode;
//STRIP001
//STRIP001     for(const CharSetNameMap *pMap = pStart; pMap->pName; ++pMap)
//STRIP001     {
//STRIP001         if(rChrSetStr.EqualsIgnoreCaseAscii(pMap->pName))
//STRIP001         {
//STRIP001             nRet = pMap->eCode;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     ASSERT(nRet != pStart->eCode, "TXT: That was an unknown language!");
//STRIP001
//STRIP001  return nRet;
//STRIP001 }


/*
 Get the String name of an rtl_TextEncoding
 */
//STRIP001 String NameFromCharSet(rtl_TextEncoding nChrSet)
//STRIP001 {
//STRIP001     const CharSetNameMap *pStart = GetCharSetNameMap();
//STRIP001     const char *pRet = pStart->pName;
//STRIP001
//STRIP001     for(const CharSetNameMap *pMap = pStart; pMap->pName; ++pMap)
//STRIP001     {
//STRIP001         if (nChrSet == pMap->eCode)
//STRIP001         {
//STRIP001             pRet = pMap->pName;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     ASSERT(pRet != pStart->pName, "TXT: That was an unknown language!");
//STRIP001
//STRIP001     return String::CreateFromAscii(pRet);
//STRIP001 }

//STRIP001 struct LangNameMap
//STRIP001 {
//STRIP001     LanguageType nId;
//STRIP001     const sal_Char* pLanguageNm;
//STRIP001 };

//STRIP001 const LangNameMap *GetLangNameMap()
//STRIP001 {
//STRIP001     static const LangNameMap aMapArr[] =
//STRIP001     {
//STRIP001         {LANGUAGE_DONTKNOW,                  "DONTKNOW"              },
//STRIP001         {LANGUAGE_NONE,                      "NONE"                  },
//STRIP001         {LANGUAGE_SYSTEM,                    "SYSTEM"                },
//STRIP001         {LANGUAGE_AFRIKAANS,             "AFRIKAANS"             },
//STRIP001         {LANGUAGE_ALBANIAN,                  "ALBANIAN"              },
//STRIP001         {LANGUAGE_ARABIC,                    "ARABIC"                },
//STRIP001         {LANGUAGE_ARABIC_SAUDI_ARABIA,       "ARABIC (SAUDI ARABIA)" },
//STRIP001         {LANGUAGE_ARABIC_IRAQ,               "ARABIC (IRAQ)"         },
//STRIP001         {LANGUAGE_ARABIC_EGYPT,              "ARABIC (EGYPT)"        },
//STRIP001         {LANGUAGE_ARABIC_LIBYA,              "ARABIC (LIBYA)"        },
//STRIP001         {LANGUAGE_ARABIC_ALGERIA,            "ARABIC (ALGERIA)"      },
//STRIP001         {LANGUAGE_ARABIC_MOROCCO,            "ARABIC (MOROCCO)"      },
//STRIP001         {LANGUAGE_ARABIC_TUNISIA,            "ARABIC (TUNISIA)"      },
//STRIP001         {LANGUAGE_ARABIC_OMAN,               "ARABIC (OMAN)"         },
//STRIP001         {LANGUAGE_ARABIC_YEMEN,              "ARABIC (YEMEN)"        },
//STRIP001         {LANGUAGE_ARABIC_SYRIA,              "ARABIC (SYRIA)"        },
//STRIP001         {LANGUAGE_ARABIC_JORDAN,         "ARABIC (JORDAN)"       },
//STRIP001         {LANGUAGE_ARABIC_LEBANON,            "ARABIC (LEBANON)"      },
//STRIP001         {LANGUAGE_ARABIC_KUWAIT,         "ARABIC (KUWAIT)"       },
//STRIP001         {LANGUAGE_ARABIC_UAE,                "ARABIC (UAE)"          },
//STRIP001         {LANGUAGE_ARABIC_BAHRAIN,            "ARABIC (BAHRAIN)"      },
//STRIP001         {LANGUAGE_ARABIC_QATAR,              "ARABIC (QATAR)"        },
//STRIP001         {LANGUAGE_ARMENIAN,                  "ARMENIAN"              },
//STRIP001         {LANGUAGE_ASSAMESE,                  "ASSAMESE"              },
//STRIP001         {LANGUAGE_AZERI,                 "AZERI"                 },
//STRIP001         {LANGUAGE_AZERI_LATIN,               "AZERI (LATIN)"         },
//STRIP001         {LANGUAGE_AZERI_CYRILLIC,            "AZERI (CYRILLIC)"      },
//STRIP001         {LANGUAGE_BASQUE,                    "BASQUE"                },
//STRIP001         {LANGUAGE_BELARUSIAN,                "BELARUSIAN"            },
//STRIP001         {LANGUAGE_BENGALI,                   "BENGALI"               },
//STRIP001         {LANGUAGE_BULGARIAN,             "BULGARIAN"             },
//STRIP001         {LANGUAGE_BURMESE,                  "BURMESE"               },
//STRIP001         {LANGUAGE_CATALAN,                   "CATALAN"               },
//STRIP001         {LANGUAGE_CHINESE,                   "CHINESE"               },
//STRIP001         {LANGUAGE_CHINESE_TRADITIONAL,       "CHINESE (TRADITIONAL)" },
//STRIP001         {LANGUAGE_CHINESE_SIMPLIFIED,        "CHINESE (SIMPLIFIED)"  },
//STRIP001         {LANGUAGE_CHINESE_HONGKONG,          "CHINESE (HONGKONG)"    },
//STRIP001         {LANGUAGE_CHINESE_SINGAPORE,     "CHINESE (SINGAPORE)"   },
//STRIP001         {LANGUAGE_CHINESE_MACAU,         "CHINESE (MACAU)"       },
//STRIP001         {LANGUAGE_CZECH,                 "CZECH"                 },
//STRIP001         {LANGUAGE_DANISH,                    "DANISH"                },
//STRIP001         {LANGUAGE_DUTCH,                 "DUTCH"                 },
//STRIP001         {LANGUAGE_DUTCH_BELGIAN,         "DUTCH_BELGIAN"         },
//STRIP001         {LANGUAGE_ENGLISH,                   "ENGLISH"               },
//STRIP001         {LANGUAGE_ENGLISH_US,                "ENGLISH (US)"          },
//STRIP001         {LANGUAGE_ENGLISH_UK,                "ENGLISH (UK)"          },
//STRIP001         {LANGUAGE_ENGLISH_AUS,               "ENGLISH (AUS)"         },
//STRIP001         {LANGUAGE_ENGLISH_CAN,               "ENGLISH (CAN)"         },
//STRIP001         {LANGUAGE_ENGLISH_NZ,                "ENGLISH (NZ)"          },
//STRIP001         {LANGUAGE_ENGLISH_EIRE,              "ENGLISH (EIRE)"        },
//STRIP001         {LANGUAGE_ENGLISH_SAFRICA,           "ENGLISH (SAFRICA)"     },
//STRIP001         {LANGUAGE_ENGLISH_JAMAICA,           "ENGLISH (JAMAICA)"     },
//STRIP001         {LANGUAGE_ENGLISH_CARRIBEAN,     "ENGLISH (CARRIBEAN)"   },
//STRIP001         {LANGUAGE_ENGLISH_BELIZE,            "ENGLISH (BELIZE)"      },
//STRIP001         {LANGUAGE_ENGLISH_TRINIDAD,          "ENGLISH (TRINIDAD)"    },
//STRIP001         {LANGUAGE_ENGLISH_ZIMBABWE,          "ENGLISH (ZIMBABWE)"    },
//STRIP001         {LANGUAGE_ENGLISH_PHILIPPINES,       "ENGLISH (PHILIPPINES)" },
//STRIP001         {LANGUAGE_ESTONIAN,                  "ESTONIAN"              },
//STRIP001         {LANGUAGE_FAEROESE,                  "FAEROESE"              },
//STRIP001         {LANGUAGE_FARSI,                 "FARSI"                 },
//STRIP001         {LANGUAGE_FINNISH,                   "FINNISH"               },
//STRIP001         {LANGUAGE_FRENCH,                    "FRENCH"                },
//STRIP001         {LANGUAGE_FRENCH_BELGIAN,            "FRENCH (BELGIAN)"      },
//STRIP001         {LANGUAGE_FRENCH_CANADIAN,           "FRENCH (CANADIAN)"     },
//STRIP001         {LANGUAGE_FRENCH_SWISS,              "FRENCH (SWISS)"        },
//STRIP001         {LANGUAGE_FRENCH_LUXEMBOURG,     "FRENCH (LUXEMBOURG)"   },
//STRIP001         {LANGUAGE_FRENCH_MONACO,         "FRENCH (MONACO)"       },
//STRIP001         {LANGUAGE_FRENCH_WEST_INDIES,        "FRENCH (WEST INDIES)"  },
//STRIP001         {LANGUAGE_FRENCH_REUNION,            "FRENCH (REUNION)"      },
//STRIP001         {LANGUAGE_FRENCH_ZAIRE,              "FRENCH (ZAIRE)"        },
//STRIP001         {LANGUAGE_FRENCH_SENEGAL,            "FRENCH (SENEGAL)"      },
//STRIP001         {LANGUAGE_FRENCH_CAMEROON,           "FRENCH (CAMEROON)"     },
//STRIP001         {LANGUAGE_FRENCH_COTE_D_IVOIRE,      "FRENCH (COTE D IVOIRE)"},
//STRIP001         {LANGUAGE_FRENCH_MALI,               "FRENCH (MALI)"         },
//STRIP001         {LANGUAGE_FRISIAN_NETHERLANDS,       "FRISIAN (NETHERLANDS)" },
//STRIP001         {LANGUAGE_GAELIC_SCOTLAND,           "GAELIC (SCOTLAND)"     },
//STRIP001         {LANGUAGE_GAELIC_IRELAND,            "GAELIC (IRELAND)"      },
//STRIP001         {LANGUAGE_GALICIAN,                  "GALICIAN"              },
//STRIP001         {LANGUAGE_GEORGIAN,              "GEORGIAN"              },
//STRIP001         {LANGUAGE_GERMAN,                    "GERMAN"                },
//STRIP001         {LANGUAGE_GERMAN_SWISS,              "GERMAN (SWISS)"        },
//STRIP001         {LANGUAGE_GERMAN_AUSTRIAN,           "GERMAN (AUSTRIAN)"     },
//STRIP001         {LANGUAGE_GERMAN_LUXEMBOURG,     "GERMAN (LUXEMBOURG)"   },
//STRIP001         {LANGUAGE_GERMAN_LIECHTENSTEIN,      "GERMAN (LIECHTENSTEIN)"},
//STRIP001         {LANGUAGE_GREEK,                 "GREEK"                 },
//STRIP001         {LANGUAGE_GUJARATI,                  "GUJARATI"              },
//STRIP001         {LANGUAGE_HEBREW,                    "HEBREW"                },
//STRIP001         {LANGUAGE_HINDI,                 "HINDI"                 },
//STRIP001         {LANGUAGE_HUNGARIAN,             "HUNGARIAN"             },
//STRIP001         {LANGUAGE_ICELANDIC,             "ICELANDIC"             },
//STRIP001         {LANGUAGE_INDONESIAN,                "INDONESIAN"            },
//STRIP001         {LANGUAGE_ITALIAN,                   "ITALIAN"               },
//STRIP001         {LANGUAGE_ITALIAN_SWISS,         "ITALIAN (SWISS)"       },
//STRIP001         {LANGUAGE_JAPANESE,                  "JAPANESE"              },
//STRIP001         {LANGUAGE_KANNADA,                   "KANNADA"               },
//STRIP001         {LANGUAGE_KASHMIRI,                  "KASHMIRI"              },
//STRIP001         {LANGUAGE_KASHMIRI_INDIA,            "KASHMIRI (INDIA)"      },
//STRIP001         {LANGUAGE_KAZAK,                 "KAZAK"                 },
//STRIP001         {LANGUAGE_KHMER,                 "KHMER"                 },
//STRIP001         {LANGUAGE_KIRGHIZ,                   "KIRGHIZ"               },
//STRIP001         {LANGUAGE_KONKANI,                   "KONKANI"               },
//STRIP001         {LANGUAGE_KOREAN,                    "KOREAN"                },
//STRIP001         {LANGUAGE_KOREAN_JOHAB,              "KOREAN (JOHAB)"        },
//STRIP001         {LANGUAGE_LAO,                       "LAO"                   },
//STRIP001         {LANGUAGE_LATVIAN,                   "LATVIAN"               },
//STRIP001         {LANGUAGE_LITHUANIAN,                "LITHUANIAN"            },
//STRIP001         {LANGUAGE_LITHUANIAN_CLASSIC,        "LITHUANIAN (CLASSIC)"  },
//STRIP001         {LANGUAGE_MACEDONIAN,                "MACEDONIAN"            },
//STRIP001         {LANGUAGE_MALAY,                 "MALAY"                 },
//STRIP001         {LANGUAGE_MALAY_MALAYSIA,            "MALAY (MALAYSIA)"      },
//STRIP001         {LANGUAGE_MALAY_BRUNEI_DARUSSALAM,  "MALAY (BRUNEI DARUSSALAM)"},
//STRIP001         {LANGUAGE_MALAYALAM,             "MALAYALAM"             },
//STRIP001         {LANGUAGE_MALTESE,                   "MALTESE"               },
//STRIP001         {LANGUAGE_MANIPURI,                  "MANIPURI"              },
//STRIP001         {LANGUAGE_MARATHI,                   "MARATHI"               },
//STRIP001         {LANGUAGE_MONGOLIAN,             "MONGOLIAN"             },
//STRIP001         {LANGUAGE_NEPALI,                    "NEPALI"                },
//STRIP001         {LANGUAGE_NEPALI_INDIA,              "NEPALI (INDIA)"        },
//STRIP001         {LANGUAGE_NORWEGIAN,             "NORWEGIAN"             },
//STRIP001         {LANGUAGE_NORWEGIAN_BOKMAL,          "NORWEGIAN (BOKMAL)"    },
//STRIP001         {LANGUAGE_NORWEGIAN_NYNORSK,     "NORWEGIAN (NYNORSK)"   },
//STRIP001         {LANGUAGE_ORIYA,                 "ORIYA"                 },
//STRIP001         {LANGUAGE_POLISH,                    "POLISH"                },
//STRIP001         {LANGUAGE_PORTUGUESE,                "PORTUGUESE"            },
//STRIP001         {LANGUAGE_PORTUGUESE_BRAZILIAN,      "PORTUGUESE (BRAZILIAN)"},
//STRIP001         {LANGUAGE_PUNJABI,                   "PUNJABI"               },
//STRIP001         {LANGUAGE_RHAETO_ROMAN,              "RHAETO (ROMAN)"        },
//STRIP001         {LANGUAGE_ROMANIAN,                  "ROMANIAN"              },
//STRIP001         {LANGUAGE_ROMANIAN_MOLDOVA,         "ROMANIAN (MOLDOVA)"    },
//STRIP001         {LANGUAGE_RUSSIAN,                   "RUSSIAN"               },
//STRIP001         {LANGUAGE_RUSSIAN_MOLDOVA,           "RUSSIAN (MOLDOVA)"     },
//STRIP001         {LANGUAGE_SAMI_LAPPISH,              "SAMI (LAPPISH)"        },
//STRIP001         {LANGUAGE_SANSKRIT,                  "SANSKRIT"              },
//STRIP001         {LANGUAGE_SERBIAN,                   "SERBIAN"               },
//STRIP001         {LANGUAGE_CROATIAN,                  "CROATIAN"              },
//STRIP001         {LANGUAGE_SERBIAN_LATIN,         "SERBIAN (LATIN)"       },
//STRIP001         {LANGUAGE_SERBIAN_CYRILLIC,          "SERBIAN (CYRILLIC)"    },
//STRIP001         {LANGUAGE_SESOTHO,                   "SESOTHO"               },
//STRIP001         {LANGUAGE_SINDHI,                    "SINDHI"                },
//STRIP001         {LANGUAGE_SLOVAK,                    "SLOVAK"                },
//STRIP001         {LANGUAGE_SLOVENIAN,             "SLOVENIAN"             },
//STRIP001         {LANGUAGE_SORBIAN,                   "SORBIAN"               },
//STRIP001         {LANGUAGE_SPANISH,                   "SPANISH"               },
//STRIP001         {LANGUAGE_SPANISH_MEXICAN,           "SPANISH (MEXICAN)"     },
//STRIP001         {LANGUAGE_SPANISH_MODERN,            "SPANISH (MODERN)"      },
//STRIP001         {LANGUAGE_SPANISH_GUATEMALA,     "SPANISH (GUATEMALA)"   },
//STRIP001         {LANGUAGE_SPANISH_COSTARICA,     "SPANISH (COSTARICA)"   },
//STRIP001         {LANGUAGE_SPANISH_PANAMA,            "SPANISH (PANAMA)"      },
//STRIP001         {LANGUAGE_SPANISH_DOMINICAN_REPUBLIC,"SPANISH (DOMINICAN REPUBLIC)"},
//STRIP001         {LANGUAGE_SPANISH_VENEZUELA,        "SPANISH (VENEZUELA)"    },
//STRIP001         {LANGUAGE_SPANISH_COLOMBIA,         "SPANISH (COLOMBIA)" },
//STRIP001         {LANGUAGE_SPANISH_PERU,             "SPANISH (PERU)"     },
//STRIP001         {LANGUAGE_SPANISH_ARGENTINA,        "SPANISH (ARGENTINA)"    },
//STRIP001         {LANGUAGE_SPANISH_ECUADOR,          "SPANISH (ECUADOR)"      },
//STRIP001         {LANGUAGE_SPANISH_CHILE,            "SPANISH (CHILE)"        },
//STRIP001         {LANGUAGE_SPANISH_URUGUAY,          "SPANISH (URUGUAY)"      },
//STRIP001         {LANGUAGE_SPANISH_PARAGUAY,         "SPANISH (PARAGUAY)" },
//STRIP001         {LANGUAGE_SPANISH_BOLIVIA,          "SPANISH (BOLIVIA)"      },
//STRIP001         {LANGUAGE_SPANISH_EL_SALVADOR,      "SPANISH (EL SALVADOR)"  },
//STRIP001         {LANGUAGE_SPANISH_HONDURAS,         "SPANISH (HONDURAS)" },
//STRIP001         {LANGUAGE_SPANISH_NICARAGUA,        "SPANISH (NICARAGUA)"    },
//STRIP001         {LANGUAGE_SPANISH_PUERTO_RICO,      "SPANISH (PUERTO RICO)"  },
//STRIP001         {LANGUAGE_SWAHILI,                  "SWAHILI"                },
//STRIP001         {LANGUAGE_SWEDISH,                  "SWEDISH"                },
//STRIP001         {LANGUAGE_SWEDISH_FINLAND,          "SWEDISH (FINLAND)"      },
//STRIP001         {LANGUAGE_TAJIK,                    "TAJIK"                  },
//STRIP001         {LANGUAGE_TAMIL,                    "TAMIL"                  },
//STRIP001         {LANGUAGE_TATAR,                    "TATAR"                  },
//STRIP001         {LANGUAGE_TELUGU,                   "TELUGU"                 },
//STRIP001         {LANGUAGE_THAI,                     "THAI"                   },
//STRIP001         {LANGUAGE_TIBETAN,                  "TIBETAN"                },
//STRIP001         {LANGUAGE_TSONGA,                   "TSONGA"             },
//STRIP001         {LANGUAGE_TSWANA,                   "TSWANA"             },
//STRIP001         {LANGUAGE_TURKISH,                  "TURKISH"                },
//STRIP001         {LANGUAGE_TURKMEN,                  "TURKMEN"                },
//STRIP001         {LANGUAGE_UKRAINIAN,                "UKRAINIAN"              },
//STRIP001         {LANGUAGE_URDU,                     "URDU"                   },
//STRIP001         {LANGUAGE_URDU_PAKISTAN,            "URDU (PAKISTAN)"        },
//STRIP001         {LANGUAGE_URDU_INDIA,               "URDU (INDIA)"           },
//STRIP001         {LANGUAGE_UZBEK,                    "UZBEK"                  },
//STRIP001         {LANGUAGE_UZBEK_LATIN,              "UZBEK (LATIN)"          },
//STRIP001         {LANGUAGE_UZBEK_CYRILLIC,           "UZBEK (CYRILLIC)"       },
//STRIP001         {LANGUAGE_VENDA,                    "VENDA"                  },
//STRIP001         {LANGUAGE_VIETNAMESE,               "VIETNAMESE"             },
//STRIP001         {LANGUAGE_WELSH,                    "WELSH"                  },
//STRIP001         {LANGUAGE_XHOSA,                    "XHOSA"                  },
//STRIP001         {LANGUAGE_ZULU,                     "ZULU"                   },
//STRIP001         {0,0}       //Last
//STRIP001     };
//STRIP001     return &aMapArr[0];
//STRIP001 }

//STRIP001 static LanguageType LanguageFromName(const String& rLngStr)
//STRIP001 {
//STRIP001     const LangNameMap *pStart = GetLangNameMap();
//STRIP001     LanguageType nRet = pStart->nId;
//STRIP001
//STRIP001     for (const LangNameMap *pMap = pStart; pMap->pLanguageNm; ++pMap)
//STRIP001     {
//STRIP001         if (rLngStr.EqualsIgnoreCaseAscii(pMap->pLanguageNm))
//STRIP001         {
//STRIP001             nRet = pMap->nId;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     ASSERT(nRet != pStart->nId, "TXT: That was an unknown language!");
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 static String NameFromLanguage(LanguageType nLang)
//STRIP001 {
//STRIP001     const LangNameMap *pStart = GetLangNameMap();
//STRIP001     const sal_Char *pRet = pStart->pLanguageNm;
//STRIP001
//STRIP001     for (const LangNameMap *pMap = pStart; pMap->pLanguageNm; ++pMap)
//STRIP001     {
//STRIP001         if (nLang == pMap->nId)
//STRIP001         {
//STRIP001             pRet = pMap->pLanguageNm;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     ASSERT(pRet != pStart->pLanguageNm, "TXT: That was an unknown language!");
//STRIP001
//STRIP001     return String::CreateFromAscii(pRet);
//STRIP001 }


// for the automatic conversion (mail/news/...)
// The user data contains the options for the ascii import/export filter.
// The format is:
//  1. CharSet - as ascii chars
//  2. LineEnd - as CR/LR/CRLF
//  3. Fontname
//  4. Language
// the delimetercharacter is ","
//

//STRIP001 void SwAsciiOptions::ReadUserData( const String& rStr )
//STRIP001 {
//STRIP001  xub_StrLen nToken = 0;
//STRIP001  USHORT nCnt = 0;
//STRIP001  String sToken;
//STRIP001  do {
//STRIP001      if( 0 != (sToken = rStr.GetToken( 0, ',', nToken )).Len() )
//STRIP001      {
//STRIP001          switch( nCnt )
//STRIP001          {
//STRIP001          case 0:     // CharSet
//STRIP001                 eCharSet = CharSetFromName(sToken);
//STRIP001              break;
//STRIP001          case 1:     // LineEnd
//STRIP001              if( sToken.EqualsIgnoreCaseAscii( "CRLF" ))
//STRIP001                  eCRLF_Flag = LINEEND_CRLF;
//STRIP001              else if( sToken.EqualsIgnoreCaseAscii( "LF" ))
//STRIP001                  eCRLF_Flag = LINEEND_LF;
//STRIP001              else
//STRIP001                  eCRLF_Flag = LINEEND_CR;
//STRIP001              break;
//STRIP001          case 2:     // fontname
//STRIP001              sFont = sToken;
//STRIP001              break;
//STRIP001          case 3:     // Language
//STRIP001                 nLanguage = LanguageFromName(sToken);
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      ++nCnt;
//STRIP001  } while( STRING_NOTFOUND != nToken );
//STRIP001 }

/*N*/ void SwAsciiOptions::WriteUserData( String& rStr )
/*N*/ {
/*?*/   // 1. charset
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 rStr = NameFromCharSet(eCharSet);
//STRIP001 /*?*/    rStr += ',';
//STRIP001 /*?*/
//STRIP001 /*?*/    // 2. LineEnd
//STRIP001 /*?*/    switch(eCRLF_Flag)
//STRIP001 /*?*/    {
//STRIP001 /*?*/         case LINEEND_CRLF:
//STRIP001 /*?*/             rStr.AppendAscii( "CRLF" );
//STRIP001 /*?*/             break;
//STRIP001 /*?*/         case LINEEND_CR:
//STRIP001 /*?*/             rStr.AppendAscii(  "CR" );
//STRIP001 /*?*/             break;
//STRIP001 /*?*/         case LINEEND_LF:
//STRIP001 /*?*/             rStr.AppendAscii(  "LF" );
//STRIP001 /*?*/             break;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    rStr += ',';
//STRIP001 /*?*/
//STRIP001 /*?*/    // 3. Fontname
//STRIP001 /*?*/    rStr += sFont;
//STRIP001 /*?*/    rStr += ',';
//STRIP001 /*?*/
//STRIP001 /*?*/    // 4. Language
//STRIP001 /*?*/    if (nLanguage)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        String sTmp = NameFromLanguage(nLanguage);
//STRIP001 /*?*/        rStr += sTmp;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    rStr += ',';
/*N*/ }
/* -----------------------------02.03.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Color ConvertBrushStyle(const Color& rCol, const Color& rFillCol, BYTE nStyle)
//STRIP001 {
//STRIP001  Color aColor = rCol;
//STRIP001  switch ( nStyle )
//STRIP001  {
//STRIP001  case SW_SV_BRUSH_25:
//STRIP001      {
//STRIP001          ULONG   nRed    = aColor.GetRed();
//STRIP001          ULONG   nGreen  = aColor.GetGreen();
//STRIP001          ULONG   nBlue   = aColor.GetBlue();
//STRIP001          nRed   += (ULONG)(rFillCol.GetRed())*2;
//STRIP001          nGreen += (ULONG)(rFillCol.GetGreen())*2;
//STRIP001          nBlue  += (ULONG)(rFillCol.GetBlue())*2;
//STRIP001          aColor = Color( (BYTE)(nRed/3), (BYTE)(nGreen/3), (BYTE)(nBlue/3) );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SW_SV_BRUSH_50:
//STRIP001      {
//STRIP001          ULONG   nRed    = aColor.GetRed();
//STRIP001          ULONG   nGreen  = aColor.GetGreen();
//STRIP001          ULONG   nBlue   = aColor.GetBlue();
//STRIP001          nRed   += (ULONG)(rFillCol.GetRed());
//STRIP001          nGreen += (ULONG)(rFillCol.GetGreen());
//STRIP001          nBlue  += (ULONG)(rFillCol.GetBlue());
//STRIP001          aColor = Color( (BYTE)(nRed/2), (BYTE)(nGreen/2), (BYTE)(nBlue/2) );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SW_SV_BRUSH_75:
//STRIP001      {
//STRIP001          ULONG   nRed    = aColor.GetRed()*2;
//STRIP001          ULONG   nGreen  = aColor.GetGreen()*2;
//STRIP001          ULONG   nBlue   = aColor.GetBlue()*2;
//STRIP001          nRed   += (ULONG)(rFillCol.GetRed());
//STRIP001          nGreen += (ULONG)(rFillCol.GetGreen());
//STRIP001          nBlue  += (ULONG)(rFillCol.GetBlue());
//STRIP001          aColor = Color( (BYTE)(nRed/3), (BYTE)(nGreen/3), (BYTE)(nBlue/3) );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SW_SV_BRUSH_NULL:
//STRIP001          aColor = Color( COL_TRANSPARENT );
//STRIP001  }
//STRIP001
//STRIP001  return aColor;
//STRIP001 }

}
