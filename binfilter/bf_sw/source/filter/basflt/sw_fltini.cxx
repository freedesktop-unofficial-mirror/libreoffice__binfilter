/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_fltini.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:26:12 $
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

#define _SVSTDARR_STRINGS

#include <string.h>
#include <stdio.h>          // sscanf

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _PARHTML_HXX //autogen
#include <svtools/parhtml.hxx>
#endif
#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _FLTINI_HXX
#include <fltini.hxx>
#endif
#ifndef _SW3IO_HXX
#include <sw3io.hxx>
#endif
#ifndef _W4WFLT_HXX
#include <w4wflt.hxx>           // AutoDetect
#endif
// enable implementation and members
#define IS_SW_DLL 1
#ifndef _IODETECT_HXX
#include <iodetect.hxx>
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
/*N*/
/*N*/   USHORT nCnt = 0;
/*N*/   _SetFltPtr( nCnt, (ReadSw3 = new Sw3Reader), FILTER_SW5 );
/*N*/   _SetFltPtr( nCnt, ReadSw3, FILTER_SW4 );
/*N*/   _SetFltPtr( nCnt, ReadSw3, FILTER_SW3 );
/*N*/   _SetFltPtr( nCnt, (ReadSwg = new SwgReader), FILTER_SWG );
/*N*/   _SetFltPtr( nCnt, ReadSwg, FILTER_SWGV );
/*N*/   _SetFltPtr( nCnt, (ReadAscii = new AsciiReader), FILTER_BAS );
/*N*/   _SetFltPtr( nCnt, ReadSwg, sSwg1 );
/*?*/   _SetFltPtr( nCnt, (ReadXML = new XMLReader), FILTER_XML );
/*N*/
/*N*/ #ifdef NEW_WW97_EXPORT
/*N*/ #endif
/*N*/
/*N*/ #ifdef DEBUG_SH
/*N*/ #endif // DEBUG_SH
/*N*/
/*N*/ #if !( defined(PRODUCT) || defined(MAC) || defined(PM2))
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


/*N*/ void GetSw3Writer( const String&, WriterRef& xRet )
/*N*/ {
/*N*/   xRet = new Sw3Writer;
/*N*/ }



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







 BOOL Writer::IsStgWriter() const { return FALSE; }
 BOOL Writer::IsSw3Writer() const { return FALSE; }


/*  */








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


/*  */






/*  */






/*  */



/*  */

/*
 Get a rtl_TextEncoding from its name
 */


/*
 Get the String name of an rtl_TextEncoding
 */






// for the automatic conversion (mail/news/...)
// The user data contains the options for the ascii import/export filter.
// The format is:
//  1. CharSet - as ascii chars
//  2. LineEnd - as CR/LR/CRLF
//  3. Fontname
//  4. Language
// the delimetercharacter is ","
//


/*N*/ void SwAsciiOptions::WriteUserData( String& rStr )
/*N*/ {
/*?*/   // 1. charset
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rStr = NameFromCharSet(eCharSet);
/*N*/ }
/* -----------------------------02.03.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/

}
