/*************************************************************************
 *
 *  $RCSfile: sw_w4wflt.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:19:30 $
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

// auto strip #ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
// auto strip #include <svtools/pathoptions.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
// auto strip #include <unotools/localfilehelper.hxx>
// auto strip #endif
// auto strip #ifndef _OSL_MODULE_HXX_
// auto strip #include <osl/module.hxx>
// auto strip #endif
// auto strip #ifndef _OSL_FILE_HXX_
// auto strip #include <osl/file.hxx>
// auto strip #endif

// -------------------------------------------------------------------

#ifdef MAC

#include <mac_start.h>
#include <Resources.h>
#include <Memory.h>
#include <Signal.h>
#include <Types.h>
#include <Strings.h>
#include <mac_end.h>

typedef int (*FNDisplay)(int);
# define FNDisp int
typedef int(**CHand)( void*, void*, void*, void*, void* );

#endif

// -------------------------------------------------------------------

#ifdef UNX
#include <stdlib.h>
#endif

// -------------------------------------------------------------------

#ifdef PM2
#define INCL_DOS                // fuer bsedos.h <- os2.h <- svpm.h <- sysdep.hxx
#endif

// -------------------------------------------------------------------

#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif
// auto strip #ifndef _UNOTOOLS_TEMPFILE_HXX
// auto strip #include <unotools/tempfile.hxx>
// auto strip #endif

// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
// auto strip #ifndef _MDIEXP_HXX
// auto strip #include <mdiexp.hxx>
// auto strip #endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif
// auto strip #ifndef _W4WFLT_HXX
// auto strip #include <w4wflt.hxx>
// auto strip #endif

#ifndef _SWERROR_H
#include <swerror.h>
#endif


#define C2U(s) ::rtl::OUString::createFromAscii(s)
#define CREATE_CONST_ASC(s) String::CreateFromAscii( \
    RTL_CONSTASCII_STRINGPARAM(s))
// ---------------------------------------------------------------------

#if defined( WIN ) || defined( WNT )

// Typen fuer die Funktion der W4W-DLL
#include <tools/svwin.h>
typedef int ( FAR PASCAL *FNDisplay)( int );

#ifdef WIN
#define FNDisp _loadds FAR PASCAL
#else
#define FNDisp FAR PASCAL
#endif // WIN

typedef int (FAR PASCAL *FNautorec)( LPSTR, int, LPINT );
typedef int (FAR PASCAL *FNw4wt)( LPSTR, LPSTR, LPSTR, LPSTR, FNDisplay );
typedef int (FAR PASCAL *FNw4wf)( LPSTR, LPSTR, LPSTR, LPSTR, FNDisplay );

#endif      // defined( WIN ) || defined( WNT )

// ---------------------------------------------------------------------

#ifdef PM2

// definition for the INSO Filters
#include <os2.h>
namespace binfilter {

#define FNDisp int

typedef int ( _System *FN32Display)( int );
typedef int ( _System *FN32autorec)( PSZ, int, int FAR* );
typedef int ( _System *FN32w4wt)( PSZ, PSZ, PSZ, PSZ, FN32Display );
typedef int ( _System *FN32w4wf)( PSZ, PSZ, PSZ, PSZ, FN32Display );
} //namespace binfilter
#endif // PM2
namespace binfilter {//STRIP009
// ---------------------------------------------------------------------

//Same as osl::Module, except will search for its modules in the filter subdir
//STRIP001 class filterModule : public osl::Module
//STRIP001 {
//STRIP001 public:
//STRIP001  sal_Bool filterLoad(String &rStr);
//STRIP001 };

//STRIP001 sal_Bool filterModule::filterLoad(String &rStr)
//STRIP001 {
//STRIP001  sal_Bool bRet=sal_False;
//STRIP001  SvtPathOptions aOpt;
//STRIP001  if (aOpt.SearchFile(rStr, SvtPathOptions::PATH_FILTER))
//STRIP001  {
//STRIP001      ::rtl::OUString aPathURL;
//STRIP001      osl::FileBase::getFileURLFromSystemPath(::rtl::OUString(rStr),aPathURL);
//STRIP001      bRet = load(aPathURL);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 #define ERR_DLL 9999

// calls the autodetect DLL from INSO and
// return the detected filter and version

// !! THIS function is for the DLL and EXE - code !!
/*N*/ USHORT AutoDetec( const String& rFileName, USHORT & rVersion )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001 /*N*/        ByteString aFileNm( rFileName, ::gsl_getSystemTextEncoding() );
//STRIP001 /*N*/    USHORT nFileType = 0;
//STRIP001 /*N*/
//STRIP001 /*N*/ #if defined( WIN ) || defined( WNT ) || defined( PM2 ) || defined ( MAC )
//STRIP001 /*N*/ #   ifdef MAC
//STRIP001 /*N*/    // bei den Demos gab es kein autorec - Programm
//STRIP001 /*N*/ #   else   // MAC
//STRIP001 /*N*/    String aAutoRecDLL(CREATE_CONST_ASC("autorec.dll"));
//STRIP001 /*N*/    SvtPathOptions aOpt;
//STRIP001 /*N*/    if( !aOpt.SearchFile( aAutoRecDLL, SvtPathOptions::PATH_FILTER ))
//STRIP001 /*N*/        return 0;
//STRIP001 /*N*/
//STRIP001 /*N*/    ByteString sAutoRecDllNm( aAutoRecDLL, ::gsl_getSystemTextEncoding() );
//STRIP001 /*N*/ #      if defined( WIN ) || defined( WNT )
//STRIP001 /*N*/    HANDLE hDLL = LoadLibrary( (LPSTR)sAutoRecDllNm.GetBuffer() );
//STRIP001 /*N*/    if( hDLL >= (HANDLE)HINSTANCE_ERROR )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        FNautorec fnAutorec = (FNautorec)GetProcAddress( (HINSTANCE)hDLL,
//STRIP001 /*N*/                                                    (LPSTR)"autorec" );
//STRIP001 /*N*/
//STRIP001 /*N*/        long nVersion = 0;
//STRIP001 /*N*/        if( fnAutorec )
//STRIP001 /*N*/            nFileType = (*fnAutorec)( (LPSTR)aFileNm.GetBuffer(),
//STRIP001 /*N*/                                        0,
//STRIP001 /*N*/                                        (LPINT)&nVersion );
//STRIP001 /*N*/        rVersion = (USHORT)nVersion;
//STRIP001 /*N*/        FreeLibrary( (HINSTANCE)hDLL );
//STRIP001 /*N*/    }
//STRIP001 /*N*/ #       endif  // defined( WIN ) || defined( WNT )
//STRIP001 /*N*/ #       ifdef PM2
//STRIP001 /*N*/    HMODULE hDLL;
//STRIP001 /*N*/    CHAR sLoadError[ 100 ];
//STRIP001 /*N*/    APIRET rc = DosLoadModule( (PSZ)sLoadError, sizeof( sLoadError ),
//STRIP001 /*N*/                                 (PSZ)sAutoRecDllNm.Buffer(), &hDLL );
//STRIP001 /*N*/    if( !rc )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        PFN ppFN;
//STRIP001 /*N*/        ULONG nBitVers;
//STRIP001 /*N*/
//STRIP001 /*N*/    if( 0 == ( rc = DosQueryProcType( hDLL, 0L, (PSZ)"autorec", &nBitVers )) &&
//STRIP001 /*N*/            1 == nBitVers &&            // 32 Bit DDLs
//STRIP001 /*N*/        0 == ( rc = DosQueryProcAddr( hDLL, 0L, (PSZ)"autorec", &ppFN )))
//STRIP001 /*N*/        {
//STRIP001 /*N*/            int nVers;
//STRIP001 /*N*/            FN32autorec fnAutorec = (FN32autorec)ppFN;
//STRIP001 /*N*/            nFileType = (*fnAutorec)( (PSZ)aFileNm.GetBuffer(),
//STRIP001 /*N*/                                       0,
//STRIP001 /*N*/                                      &nVers );
//STRIP001 /*N*/            rVersion = nVers;
//STRIP001 /*N*/        }
//STRIP001 /*N*/ //Bug 33334: Modul wird von OS/2 nie aus dem Speicher entfernt,
//STRIP001 /*N*/ // W4W stoplter darueber --> also nie entfernen!
//STRIP001 /*N*/ //     DosFreeModule( hDLL );
//STRIP001 /*N*/    }
//STRIP001 /*N*/ #       endif  // PM2
//STRIP001 /*N*/ #   endif  // MAC
//STRIP001 /*N*/ #else
//STRIP001 /*N*/     //This is the nice modern code, the other stuff is a bit awful, but for
//STRIP001 /*N*/     //some reason the different platforms had different argument lists from
//STRIP001 /*N*/     //eachother, so we can't have super clean code :-(
//STRIP001 /*N*/     filterModule aAutoRec;
//STRIP001 /*N*/     String aTmpStr(CREATE_CONST_ASC(SVLIBRARY("autorec")));
//STRIP001 /*N*/     if (aAutoRec.filterLoad(aTmpStr))
//STRIP001 /*N*/     {
//STRIP001 /*N*/        typedef int (*autorec_t)(const char*, int*);
//STRIP001 /*N*/        if (autorec_t autorec = (autorec_t)aAutoRec.getSymbol(C2U("autorec")))
//STRIP001 /*N*/         {
//STRIP001 /*N*/             int nVersion;
//STRIP001 /*N*/             if (nFileType = (USHORT)autorec(aFileNm.GetBuffer(), &nVersion))
//STRIP001 /*N*/                 rVersion = (USHORT)nVersion;
//STRIP001 /*N*/         }
//STRIP001 /*N*/     }
//STRIP001 /*N*/ #endif
//STRIP001 /*N*/
//STRIP001 /*N*/    if( nFileType == 31 )   // Autorec-Bug umpopeln: Eine ASCII-Datei, die nur
//STRIP001 /*N*/        nFileType = 1;      // aus sehr vielen CRs besteht,
//STRIP001 /*N*/                            // wird als VAX Mass-11 erkannt
//STRIP001 /*N*/
//STRIP001 /*N*/    return nFileType == (USHORT)-1 ? 0 : nFileType;
/*N*/ }


// --------------------------------------------------------------------------

//STRIP001 #ifdef _DLL_

//STRIP001 #ifdef MAC

//STRIP001 static short Call_MacRes( const String& rFromFileName, USHORT nFilter, BOOL bFrom,
//STRIP001                        const String& rVersion, const String & rToFileName )
//STRIP001 {
//STRIP001  short nRefNo = 0, nError = 0;
//STRIP001  USHORT nMacFilter = nFilter * 10 + 2;
//STRIP001  if ( bFrom ) nMacFilter--;
//STRIP001  // beim Mac ist alles anders:  Letzte Ziffer = 1 entspricht from,
//STRIP001  // Letzte Ziffer = 2 entspricht to
//STRIP001
//STRIP001  String aFormat(CREATE_CONST_ASC("w4w"));
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat.AppendAscii( "00" );
//STRIP001  else if( nFilter < 100 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += nFilter;
//STRIP001
//STRIP001  if( bFrom )
//STRIP001      aFormat.AppendAscii( ".f" );
//STRIP001  else
//STRIP001      aFormat.AppendAscii( ".t" );
//STRIP001
//STRIP001  SvtPathOptions aOpt;
//STRIP001  if( !aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER ))
//STRIP001      return ERR_DLL;
//STRIP001
//STRIP001  Str255  aMacStr;        // registriere den W4W-Filter im MAC-Resource System
//STRIP001  strncpy( (char*)aMacStr+1, aFormat, sizeof(aMacStr) - 2 );
//STRIP001     aMacStr[sizeof(aMacStr) -1] = 0;
//STRIP001  aMacStr[0] = aFormat.Len() < 255 : aFormat.Len() : 254;
//STRIP001  nRefNo = OpenResFile( aMacStr );
//STRIP001
//STRIP001  CHand zConv = (CHand) GetResource( 'CONV', nMacFilter );
//STRIP001  if( zConv )                             // Rufe Code-Resource (aehnlich DLL)
//STRIP001  {
//STRIP001      HLock((Handle) zConv);
//STRIP001 #ifdef __powerc
//STRIP001      ProcInfoType theProcInfo = kCStackBased
//STRIP001                              | RESULT_SIZE(SIZE_CODE(sizeof(int)))
//STRIP001                              | STACK_ROUTINE_PARAMETER( 1, SIZE_CODE( sizeof( void* ) ) )
//STRIP001                              | STACK_ROUTINE_PARAMETER( 2, SIZE_CODE( sizeof( void* ) ) )
//STRIP001                              | STACK_ROUTINE_PARAMETER( 3, SIZE_CODE( sizeof( void* ) ) )
//STRIP001                              | STACK_ROUTINE_PARAMETER( 4, SIZE_CODE( sizeof( void* ) ) )
//STRIP001                              | STACK_ROUTINE_PARAMETER( 5, SIZE_CODE( sizeof( void* ) ) );
//STRIP001      UniversalProcPtr pMyProc = NewRoutineDescriptor( (long (*)())*zConv, theProcInfo, kM68kISA );
//STRIP001      nError = CallUniversalProc(     pMyProc,
//STRIP001                                  theProcInfo,
//STRIP001                                  (void*)rFromFileName.GetStr(),
//STRIP001                                  (void*)rToFileName.GetStr(),
//STRIP001                                  (void*)rVersion.GetStr(),
//STRIP001                                  aEmptyStr.GetStr(),
//STRIP001                                  0 );
//STRIP001 //neu:   (void*)&W4WReadDisplayHandler );
//STRIP001      DisposeRoutineDescriptor( pMyProc )
//STRIP001 #else    // __powerc
//STRIP001      nError = (**zConv)( (void*)rFromFileName.GetStr(),
//STRIP001                          (void*)rToFileName.GetStr(),
//STRIP001                          (void*)rVersion.GetStr(),
//STRIP001                          aEmptyStr.GetStr(),
//STRIP001 //neu:   (void*)&W4WReadDisplayHandler );
//STRIP001                          0 );
//STRIP001 #endif   // __powerc
//STRIP001      HUnlock((Handle) zConv);
//STRIP001      ReleaseResource((Handle) zConv);
//STRIP001  }
//STRIP001  else
//STRIP001      nError = ERR_DLL;
//STRIP001
//STRIP001  if ( nRefNo > 0 )
//STRIP001      CloseResFile( nRefNo );
//STRIP001  return nError;
//STRIP001 }

//STRIP001 #endif  // MAC


// Handler fuer die Prozentanzeige

//STRIP001 #if defined( WIN ) || defined( WNT ) || defined( PM2 )

//STRIP001 FNDisp W4WReadDisplayHandler( int nPercent )
//STRIP001 {
//STRIP001  ::binfilter::SetProgressState( nPercent  / 3, 0 );
//STRIP001  return 0;       // -1 fuehrt zu Abbruch
//STRIP001 }

//STRIP001 FNDisp W4WWriteDisplayHandler( int nPercent )
//STRIP001 {
//STRIP001  ::binfilter::SetProgressState( 67 + nPercent  / 3, 0 );
//STRIP001  return 0;       // -1 fuehrt zu Abbruch
//STRIP001 }


//STRIP001 #endif



// W4W speichert beim Laden vom File rFileName die Ausgabe in aTmpFile.
// der Filter wird ueber nFilter bestimmt.

//STRIP001 ULONG LoadFile( const String& rFileName, USHORT nFilter,
//STRIP001              const String& rVersion, String & rTmpFile )
//STRIP001 {
//STRIP001  rTmpFile = utl::TempFile::CreateTempName( 0 );
//STRIP001  String sNativeFileName(rTmpFile);
//STRIP001  USHORT nError = 1;
//STRIP001
//STRIP001  rtl_TextEncoding eEnc = ::gsl_getSystemTextEncoding();
//STRIP001  ByteString sFileName( rFileName, eEnc ), sVersion( rVersion, eEnc ),
//STRIP001              sTmpFile( rTmpFile, eEnc );
//STRIP001
//STRIP001  {
//STRIP001      String sTmp;
//STRIP001      if( utl::LocalFileHelper::ConvertPhysicalNameToURL( rTmpFile, sTmp ))
//STRIP001          rTmpFile = sTmp;
//STRIP001  }
//STRIP001
//STRIP001 #ifdef MAC
//STRIP001
//STRIP001  nError = Call_MacRes( rFileName, nFilter, TRUE, rVersion, rTmpFile );
//STRIP001
//STRIP001 #else //MAC
//STRIP001
//STRIP001  String aFormat;
//STRIP001
//STRIP001 #if defined( WIN ) || defined( WNT )
//STRIP001  aFormat += 'w';
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat += '0';
//STRIP001  if( nFilter < 100 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += String::CreateFromInt32( nFilter );
//STRIP001  aFormat += 'f';
//STRIP001 #if defined( WIN )
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "16W" ));
//STRIP001 #else    // WIN
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "32W" ));
//STRIP001 #endif   // WIN
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".DLL" ));
//STRIP001 #endif   // defined( WIN ) || defined( WNT )
//STRIP001
//STRIP001 #ifdef PM2
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += String::CreateFromInt32( nFilter );
//STRIP001  aFormat += 'f';
//STRIP001
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".dll" ));
//STRIP001 #endif   // PM2
//STRIP001
//STRIP001 #ifdef UNX
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += String::CreateFromInt32( nFilter );
//STRIP001  aFormat += 'f';
//STRIP001 #endif   // UNX
//STRIP001
//STRIP001  SvtPathOptions aOpt;
//STRIP001  if( !aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER ) )
//STRIP001      return ERR_W4W_DLL_ERROR | ERROR_SW_READ_BASE;
//STRIP001
//STRIP001  ByteString sFormat( aFormat, ::gsl_getSystemTextEncoding() );
//STRIP001 #if defined( WIN ) || defined( WNT )
//STRIP001
//STRIP001  HANDLE hDLL = LoadLibrary( (LPSTR)sFormat.GetBuffer() );
//STRIP001  if( hDLL >= (HANDLE)HINSTANCE_ERROR )
//STRIP001  {
//STRIP001      FNw4wf fnRead = (FNw4wf)GetProcAddress( (HINSTANCE)hDLL, (LPSTR)"w4wf" );
//STRIP001      if( fnRead )
//STRIP001          nError = (*fnRead)( (LPSTR)sFileName.GetBuffer(),
//STRIP001                              (LPSTR)sTmpFile.GetBuffer(),
//STRIP001                              (LPSTR)sVersion.GetBuffer(),
//STRIP001                              (LPSTR)aEmptyByteStr.GetBuffer(),
//STRIP001                              (FNDisplay)&W4WReadDisplayHandler
//STRIP001                              );
//STRIP001
//STRIP001      FreeLibrary( (HINSTANCE)hDLL );
//STRIP001  }
//STRIP001 #ifndef WIN     /* Bei Windows kommt schon eine System-Box hoch */
//STRIP001  else
//STRIP001      nError = ERR_DLL;
//STRIP001 #endif
//STRIP001
//STRIP001 #endif //WIN || WNT
//STRIP001
//STRIP001 #ifdef PM2
//STRIP001  HMODULE hDLL;
//STRIP001  CHAR sLoadError[ 100 ];
//STRIP001  APIRET rc = DosLoadModule( (PSZ)sLoadError, sizeof( sLoadError ),
//STRIP001                               (PSZ)sFormat.GetBuffer(), &hDLL );
//STRIP001  if( !rc )
//STRIP001  {
//STRIP001      PFN ppFN;
//STRIP001      ULONG nBitVers;
//STRIP001
//STRIP001      if( 0 == ( rc = DosQueryProcType( hDLL, 0L, (PSZ)"w4wf", &nBitVers )) &&
//STRIP001      1 == nBitVers &&                // 32 Bit DLLs
//STRIP001      0 == ( rc = DosQueryProcAddr( hDLL, 0L, (PSZ)"w4wf", &ppFN )))
//STRIP001      {
//STRIP001          // die neuen 32 Bit DLLs
//STRIP001          FN32w4wf fnRead = (FN32w4wf)ppFN;
//STRIP001          nError = (*fnRead)( (PSZ)sFileName.GetBuffer(),
//STRIP001                          (PSZ)sTmpFile.GetBuffer(),
//STRIP001                          (PSZ)sVersion.GetBuffer(),
//STRIP001                          (PSZ)aEmptyByteStr.GetBuffer(),
//STRIP001                          (FN32Display)&W4WReadDisplayHandler
//STRIP001                          );
//STRIP001      }
//STRIP001 //Bug 33334: Modul wird von OS/2 nie aus dem Speicher entfernt,
//STRIP001 // W4W stoplter darueber --> also nie entfernen!
//STRIP001 //JP 23.04.98: fuer den DCF-RFT-Filter unter OS/2 muss aber die DLL
//STRIP001 //               freigegeben werden.
//STRIP001      if( 15 == nFilter )
//STRIP001          DosFreeModule( hDLL );
//STRIP001  }
//STRIP001  else
//STRIP001      nError = ERR_DLL;
//STRIP001 #endif  // PM2
//STRIP001
//STRIP001 #ifdef UNX
//STRIP001
//STRIP001  String aParam( aFormat );
//STRIP001  aParam += ' ';
//STRIP001  aParam += rFileName;
//STRIP001  aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -N -t=" ));
//STRIP001  aParam += sNativeFileName;
//STRIP001  aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -v" ));
//STRIP001  aParam += rVersion;
//STRIP001
//STRIP001  ByteString sParam( aParam, ::gsl_getSystemTextEncoding() );
//STRIP001
//STRIP001  nError = system( sParam.GetBuffer() );
//STRIP001 #endif  // UNX
//STRIP001 #endif  // MAC
//STRIP001
//STRIP001 static const ULONG nErrors[18]={
//STRIP001  0, ERR_SWG_READ_ERROR, ERR_SWG_READ_ERROR, ERR_W4W_WRITE_TMP_ERROR,
//STRIP001  ERR_W4W_WRITE_TMP_ERROR, ERR_SWG_FILE_FORMAT_ERROR,
//STRIP001  ERR_W4W_WRITE_TMP_ERROR, ERR_W4W_WRITE_TMP_ERROR,
//STRIP001  ERR_W4W_MEM | ERROR_SW_READ_BASE,
//STRIP001  ERR_SWG_FILE_FORMAT_ERROR, ERR_W4W_WRITE_FULL | ERROR_SW_READ_BASE,
//STRIP001  0, 0, 0,
//STRIP001  0, ERR_SW6_PASSWD, ERR_W4W_INTERNAL_ERROR | ERROR_SW_READ_BASE,
//STRIP001  0 };
//STRIP001
//STRIP001  if ( nError != 12 )         // 12 ist nur Warning
//STRIP001  {
//STRIP001      if ( nError == ERR_DLL )
//STRIP001          return ERR_W4W_DLL_ERROR | ERROR_SW_READ_BASE;
//STRIP001      if ( nError>0 && nError<=17 )
//STRIP001          return nErrors[ nError ];
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

// W4W liest beim Speichern vom File pFileName die Eingabe aus pTmpFile.
// der Filter wird ueber nFilter bestimmt.

//STRIP001 ULONG SaveFile( const String& rFileName, const String& rTmpFile,
//STRIP001              USHORT nFilter, const String& rVersion )
//STRIP001 {
//STRIP001  USHORT nError = 1;
//STRIP001
//STRIP001  rtl_TextEncoding eEnc = ::gsl_getSystemTextEncoding();
//STRIP001  ByteString sFileName( rFileName, eEnc ), sVersion( rVersion, eEnc ),
//STRIP001             sTmpFile( rTmpFile, eEnc );
//STRIP001
//STRIP001 #ifdef MAC
//STRIP001
//STRIP001  nError = Call_MacRes( rTmpFile, nFilter, FALSE, rVersion, rFileName );
//STRIP001
//STRIP001 #else //MAC
//STRIP001
//STRIP001  String aFormat;
//STRIP001
//STRIP001 #if defined( WIN ) || defined( WNT )
//STRIP001  aFormat += 'w';
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat += '0';
//STRIP001  if( nFilter < 100 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += String::CreateFromInt32( nFilter );
//STRIP001  aFormat += 't';
//STRIP001 #if defined( WIN )
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "16W" ));
//STRIP001 #else    // WIN
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "32W" ));
//STRIP001 #endif   // WIN
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".DLL" ));
//STRIP001 #endif   // defined( WIN ) || defined( WNT )
//STRIP001
//STRIP001
//STRIP001 #ifdef PM2
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += String::CreateFromInt32( nFilter );
//STRIP001  aFormat += 't';
//STRIP001
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".dll" ));
//STRIP001 #endif   // PM2
//STRIP001
//STRIP001 #ifdef UNX
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
//STRIP001  if( nFilter < 10 )
//STRIP001      aFormat += '0';
//STRIP001  aFormat += String::CreateFromInt32( nFilter );
//STRIP001  aFormat += 't';
//STRIP001 #endif   // UNX
//STRIP001
//STRIP001  SvtPathOptions aOpt;
//STRIP001  if( !aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER ))
//STRIP001      return ERR_W4W_DLL_ERROR | ERROR_SW_WRITE_BASE;
//STRIP001
//STRIP001  ByteString sFormat( aFormat, ::gsl_getSystemTextEncoding() );
//STRIP001 #if defined( WIN ) || defined( WNT )
//STRIP001
//STRIP001  HANDLE hDLL = LoadLibrary( (LPSTR)sFormat.GetBuffer() );
//STRIP001  if( hDLL >= (HANDLE)HINSTANCE_ERROR )
//STRIP001  {
//STRIP001      FNw4wt fnSave = (FNw4wt)GetProcAddress( (HINSTANCE)hDLL, (LPSTR)"w4wt" );
//STRIP001      if( fnSave )
//STRIP001          nError = (*fnSave)( (LPSTR)sTmpFile.GetBuffer(),
//STRIP001                              (LPSTR)sFileName.GetBuffer(),
//STRIP001                              (LPSTR)sVersion.GetBuffer(),
//STRIP001                              (LPSTR)aEmptyByteStr.GetBuffer(),
//STRIP001                              (FNDisplay)&W4WWriteDisplayHandler );
//STRIP001      FreeLibrary( (HINSTANCE)hDLL );
//STRIP001  }
//STRIP001 #ifndef WIN             /* Bei Windows kommt schon eine System-Box hoch */
//STRIP001  else
//STRIP001      nError = ERR_DLL;
//STRIP001 #endif
//STRIP001
//STRIP001 #endif //WIN || WNT
//STRIP001
//STRIP001 #ifdef PM2
//STRIP001  HMODULE hDLL;
//STRIP001  CHAR sLoadError[ 100 ];
//STRIP001  APIRET rc = DosLoadModule( (PSZ)sLoadError, sizeof( sLoadError ),
//STRIP001                               (PSZ)sFormat.GetStr(), &hDLL );
//STRIP001  if( !rc )
//STRIP001  {
//STRIP001      PFN ppFN;
//STRIP001      ULONG nBitVers;
//STRIP001
//STRIP001      if( 0 == ( rc = DosQueryProcType( hDLL, 0L, (PSZ)"w4wt", &nBitVers )) &&
//STRIP001      1 == nBitVers &&                // 32 Bit DLLs
//STRIP001      0 == ( rc = DosQueryProcAddr( hDLL, 0L, (PSZ)"w4wt", &ppFN )))
//STRIP001      {
//STRIP001          // die neuen 32 Bit DLLs
//STRIP001          FN32w4wt fnSave = (FN32w4wt)ppFN;
//STRIP001          nError = (*fnSave)( (PSZ)sTmpFile.GetBuffer(),
//STRIP001                              (PSZ)sFileName.GetBuffer(),
//STRIP001                              (PSZ)sVersion.GetBuffer(),
//STRIP001                              (PSZ)aEmptyByteStr.GetBuffer(),
//STRIP001                              (FN32Display)&W4WWriteDisplayHandler
//STRIP001                              );
//STRIP001      }
//STRIP001 //Bug 33334: Modul wird von OS/2 nie aus dem Speicher entfernt,
//STRIP001 // W4W stoplter darueber --> also nie entfernen!
//STRIP001 //       DosFreeModule( hDLL );
//STRIP001  }
//STRIP001  else
//STRIP001      nError = ERR_DLL;
//STRIP001 #endif  // PM2
//STRIP001
//STRIP001 #ifdef UNX
//STRIP001
//STRIP001  String aParam( aFormat );
//STRIP001  aParam += ' ';
//STRIP001  aParam += rFileName;
//STRIP001  aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -N -t=" ));
//STRIP001  aParam += rTmpFile;
//STRIP001  aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -v" ));
//STRIP001  aParam += rVersion;
//STRIP001
//STRIP001  ByteString sParam( aParam, ::gsl_getSystemTextEncoding() );
//STRIP001  nError = system( sParam.GetBuffer() );
//STRIP001
//STRIP001 #endif  // UNX
//STRIP001 #endif  // MAC
//STRIP001
//STRIP001 static const ULONG nErrors[18]={ 0,ERR_SWG_WRITE_ERROR,
//STRIP001  ERR_W4W_READ_TMP_ERROR, ERR_W4W_READ_TMP_ERROR, ERR_SWG_WRITE_ERROR,
//STRIP001  0, ERR_W4W_WRITE_TMP_ERROR, ERR_W4W_WRITE_TMP_ERROR,
//STRIP001  ERR_W4W_MEM | ERROR_SW_WRITE_BASE, 0,
//STRIP001  ERR_W4W_WRITE_FULL | ERROR_SW_WRITE_BASE,
//STRIP001  0, 0, 0,
//STRIP001  0, ERR_SW6_PASSWD, ERR_W4W_INTERNAL_ERROR | ERROR_SW_WRITE_BASE,
//STRIP001  0 };
//STRIP001
//STRIP001  if ( nError != 12 )         // 12 ist nur Warning
//STRIP001  {
//STRIP001      if ( nError == ERR_DLL )
//STRIP001          return ERR_W4W_DLL_ERROR | ERROR_SW_WRITE_BASE;
//STRIP001      if ( nError>0 && nError<=17 )
//STRIP001          return nErrors[ nError ];
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 FASTBOOL W4WDLLExist( W4WDLL_TYPE eType, USHORT nFilter )
//STRIP001 {
//STRIP001 #ifdef MAC
//STRIP001  return TRUE;            // dann beim CallMacRes feststellen
//STRIP001 #else
//STRIP001
//STRIP001  String aFormat;
//STRIP001  switch( eType )
//STRIP001  {
//STRIP001  case W4WDLL_EXPORT:
//STRIP001  case W4WDLL_IMPORT:
//STRIP001 #if defined( PM2 ) || defined( UNX )
//STRIP001      aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
//STRIP001      if( nFilter < 10 )
//STRIP001          aFormat += '0';
//STRIP001      aFormat += String::CreateFromInt32( nFilter );
//STRIP001      aFormat += W4WDLL_IMPORT ? 'f' : 't';
//STRIP001 #endif // PM2 || UNX
//STRIP001
//STRIP001 #if defined( WIN ) || defined( WNT )
//STRIP001      aFormat += 'w';
//STRIP001      if( nFilter < 10 )
//STRIP001          aFormat += '0';
//STRIP001      if( nFilter < 100 )
//STRIP001          aFormat += '0';
//STRIP001      aFormat += String::CreateFromInt32( nFilter );
//STRIP001      aFormat += W4WDLL_IMPORT ? 'f' : 't';
//STRIP001 #if defined( WIN )
//STRIP001      aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "16W" ));
//STRIP001 #else    // WIN
//STRIP001      aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "32W" ));
//STRIP001 #endif   // WIN
//STRIP001
//STRIP001 #endif   // WIN || WNT
//STRIP001      break;
//STRIP001
//STRIP001  case W4WDLL_AUTODETEC:
//STRIP001      aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "autorec" ));
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001 #ifndef UNX
//STRIP001  aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".dll" ));
//STRIP001 #endif  // UNX
//STRIP001
//STRIP001  // Fehlerbehandlung oder fuer Systeme die keine W4W-Filter kennen
//STRIP001  SvtPathOptions aOpt;
//STRIP001
//STRIP001  return aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER );
//STRIP001 #endif   // MAC
//STRIP001 }

//STRIP001 #endif   // _DLL_
}
