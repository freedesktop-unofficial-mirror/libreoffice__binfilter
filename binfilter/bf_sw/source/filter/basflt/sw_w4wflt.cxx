/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_w4wflt.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:38:13 $
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

#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
#include <unotools/localfilehelper.hxx>
#endif

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
#ifndef _UNOTOOLS_TEMPFILE_HXX
#include <unotools/tempfile.hxx>
#endif

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _W4WFLT_HXX
#include <w4wflt.hxx>
#endif

#ifndef _SWERROR_H
#include <swerror.h>
#endif

namespace binfilter {//STRIP009

#define ERR_DLL 9999

/*N*/ USHORT AutoDetec( const String& rFileName, USHORT & rVersion )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }

// Handler fuer die Prozentanzeige

#if defined( WIN ) || defined( WNT ) || defined( PM2 )

FNDisp W4WReadDisplayHandler( int nPercent )
{
// no progress display in binfilter!
//    ::binfilter::SetProgressState( nPercent  / 3, 0 );
    return 0;       // -1 fuehrt zu Abbruch
}

FNDisp W4WWriteDisplayHandler( int nPercent )
{
// no progress display in binfilter!
//    ::binfilter::SetProgressState( 67 + nPercent  / 3, 0 );
    return 0;       // -1 fuehrt zu Abbruch
}


#endif



// W4W speichert beim Laden vom File rFileName die Ausgabe in aTmpFile.
// der Filter wird ueber nFilter bestimmt.

ULONG LoadFile( const String& rFileName, USHORT nFilter,
                const String& rVersion, String & rTmpFile )
{
    rTmpFile = utl::TempFile::CreateTempName( 0 );
    String sNativeFileName(rTmpFile);
    USHORT nError = 1;

    rtl_TextEncoding eEnc = ::gsl_getSystemTextEncoding();
    ByteString sFileName( rFileName, eEnc ), sVersion( rVersion, eEnc ),
                sTmpFile( rTmpFile, eEnc );

    {
        String sTmp;
        if( utl::LocalFileHelper::ConvertPhysicalNameToURL( rTmpFile, sTmp ))
            rTmpFile = sTmp;
    }

#ifdef MAC

    nError = Call_MacRes( rFileName, nFilter, TRUE, rVersion, rTmpFile );

#else //MAC

    String aFormat;

#if defined( WIN ) || defined( WNT )
    aFormat += 'w';
    if( nFilter < 10 )
        aFormat += '0';
    if( nFilter < 100 )
        aFormat += '0';
    aFormat += String::CreateFromInt32( nFilter );
    aFormat += 'f';
#if defined( WIN )
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "16W" ));
#else   // WIN
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "32W" ));
#endif  // WIN
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".DLL" ));
#endif  // defined( WIN ) || defined( WNT )

#ifdef PM2
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
    if( nFilter < 10 )
        aFormat += '0';
    aFormat += String::CreateFromInt32( nFilter );
    aFormat += 'f';

    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".dll" ));
#endif  // PM2

#ifdef UNX
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
    if( nFilter < 10 )
        aFormat += '0';
    aFormat += String::CreateFromInt32( nFilter );
    aFormat += 'f';
#endif  // UNX

    SvtPathOptions aOpt;
    if( !aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER ) )
        return ERR_W4W_DLL_ERROR | ERROR_SW_READ_BASE;

    ByteString sFormat( aFormat, ::gsl_getSystemTextEncoding() );
#if defined( WIN ) || defined( WNT )

    ByteString aEmptyByteStr;
    HANDLE hDLL = LoadLibrary( (LPSTR)sFormat.GetBuffer() );
    if( hDLL >= (HANDLE)HINSTANCE_ERROR )
    {
        FNw4wf fnRead = (FNw4wf)GetProcAddress( (HINSTANCE)hDLL, (LPSTR)"w4wf" );
        if( fnRead )
            nError = (*fnRead)( (LPSTR)sFileName.GetBuffer(),
                                (LPSTR)sTmpFile.GetBuffer(),
                                (LPSTR)sVersion.GetBuffer(),
                                (LPSTR)aEmptyByteStr.GetBuffer(),
                                (FNDisplay)&W4WReadDisplayHandler
                                );

        FreeLibrary( (HINSTANCE)hDLL );
    }
#ifndef WIN     /* Bei Windows kommt schon eine System-Box hoch */
    else
        nError = ERR_DLL;
#endif

#endif //WIN || WNT

#ifdef PM2
    HMODULE hDLL;
    ByteString aEmptyByteStr;
    CHAR sLoadError[ 100 ];
    APIRET rc = DosLoadModule( (PSZ)sLoadError, sizeof( sLoadError ),
                                 (PSZ)sFormat.GetBuffer(), &hDLL );
    if( !rc )
    {
        PFN ppFN;
        ULONG nBitVers;

        if( 0 == ( rc = DosQueryProcType( hDLL, 0L, (PSZ)"w4wf", &nBitVers )) &&
        1 == nBitVers &&                // 32 Bit DLLs
        0 == ( rc = DosQueryProcAddr( hDLL, 0L, (PSZ)"w4wf", &ppFN )))
        {
            // die neuen 32 Bit DLLs
            FN32w4wf fnRead = (FN32w4wf)ppFN;
            nError = (*fnRead)( (PSZ)sFileName.GetBuffer(),
                            (PSZ)sTmpFile.GetBuffer(),
                            (PSZ)sVersion.GetBuffer(),
                            (PSZ)aEmptyByteStr.GetBuffer(),
                            (FN32Display)&W4WReadDisplayHandler
                            );
        }
//Bug 33334: Modul wird von OS/2 nie aus dem Speicher entfernt,
// W4W stoplter darueber --> also nie entfernen!
//JP 23.04.98: fuer den DCF-RFT-Filter unter OS/2 muss aber die DLL
//              freigegeben werden.
        if( 15 == nFilter )
            DosFreeModule( hDLL );
    }
    else
        nError = ERR_DLL;
#endif  // PM2

#ifdef UNX

    String aParam( aFormat );
    aParam += ' ';
    aParam += rFileName;
    aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -N -t=" ));
    aParam += sNativeFileName;
    aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -v" ));
    aParam += rVersion;

    ByteString sParam( aParam, ::gsl_getSystemTextEncoding() );

    nError = system( sParam.GetBuffer() );
#endif  // UNX
#endif  // MAC

static const ULONG nErrors[18]={
    0, ERR_SWG_READ_ERROR, ERR_SWG_READ_ERROR, ERR_W4W_WRITE_TMP_ERROR,
    ERR_W4W_WRITE_TMP_ERROR, ERR_SWG_FILE_FORMAT_ERROR,
    ERR_W4W_WRITE_TMP_ERROR, ERR_W4W_WRITE_TMP_ERROR,
    ERR_W4W_MEM | ERROR_SW_READ_BASE,
    ERR_SWG_FILE_FORMAT_ERROR, ERR_W4W_WRITE_FULL | ERROR_SW_READ_BASE,
    0, 0, 0,
    0, ERR_SW6_PASSWD, ERR_W4W_INTERNAL_ERROR | ERROR_SW_READ_BASE,
    0 };

    if ( nError != 12 )         // 12 ist nur Warning
    {
        if ( nError == ERR_DLL )
            return ERR_W4W_DLL_ERROR | ERROR_SW_READ_BASE;
        if ( nError>0 && nError<=17 )
            return nErrors[ nError ];
    }
    return 0;
}

// W4W liest beim Speichern vom File pFileName die Eingabe aus pTmpFile.
// der Filter wird ueber nFilter bestimmt.

ULONG SaveFile( const String& rFileName, const String& rTmpFile,
                USHORT nFilter, const String& rVersion )
{
    USHORT nError = 1;
    ByteString aEmptyByteStr;

    rtl_TextEncoding eEnc = ::gsl_getSystemTextEncoding();
    ByteString sFileName( rFileName, eEnc ), sVersion( rVersion, eEnc ),
               sTmpFile( rTmpFile, eEnc );

#ifdef MAC

    nError = Call_MacRes( rTmpFile, nFilter, FALSE, rVersion, rFileName );

#else //MAC

    String aFormat;

#if defined( WIN ) || defined( WNT )
    aFormat += 'w';
    if( nFilter < 10 )
        aFormat += '0';
    if( nFilter < 100 )
        aFormat += '0';
    aFormat += String::CreateFromInt32( nFilter );
    aFormat += 't';
#if defined( WIN )
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "16W" ));
#else   // WIN
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "32W" ));
#endif  // WIN
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".DLL" ));
#endif  // defined( WIN ) || defined( WNT )


#ifdef PM2
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
    if( nFilter < 10 )
        aFormat += '0';
    aFormat += String::CreateFromInt32( nFilter );
    aFormat += 't';

    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".dll" ));
#endif  // PM2

#ifdef UNX
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
    if( nFilter < 10 )
        aFormat += '0';
    aFormat += String::CreateFromInt32( nFilter );
    aFormat += 't';
#endif  // UNX

    SvtPathOptions aOpt;
    if( !aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER ))
        return ERR_W4W_DLL_ERROR | ERROR_SW_WRITE_BASE;

    ByteString sFormat( aFormat, ::gsl_getSystemTextEncoding() );
#if defined( WIN ) || defined( WNT )

    HANDLE hDLL = LoadLibrary( (LPSTR)sFormat.GetBuffer() );
    if( hDLL >= (HANDLE)HINSTANCE_ERROR )
    {
        FNw4wt fnSave = (FNw4wt)GetProcAddress( (HINSTANCE)hDLL, (LPSTR)"w4wt" );
        if( fnSave )
            nError = (*fnSave)( (LPSTR)sTmpFile.GetBuffer(),
                                (LPSTR)sFileName.GetBuffer(),
                                (LPSTR)sVersion.GetBuffer(),
                                (LPSTR)aEmptyByteStr.GetBuffer(),
                                (FNDisplay)&W4WWriteDisplayHandler );
        FreeLibrary( (HINSTANCE)hDLL );
    }
#ifndef WIN             /* Bei Windows kommt schon eine System-Box hoch */
    else
        nError = ERR_DLL;
#endif

#endif //WIN || WNT

#ifdef PM2
    HMODULE hDLL;
    CHAR sLoadError[ 100 ];
    APIRET rc = DosLoadModule( (PSZ)sLoadError, sizeof( sLoadError ),
                                 (PSZ)sFormat.GetStr(), &hDLL );
    if( !rc )
    {
        PFN ppFN;
        ULONG nBitVers;

        if( 0 == ( rc = DosQueryProcType( hDLL, 0L, (PSZ)"w4wt", &nBitVers )) &&
        1 == nBitVers &&                // 32 Bit DLLs
        0 == ( rc = DosQueryProcAddr( hDLL, 0L, (PSZ)"w4wt", &ppFN )))
        {
            // die neuen 32 Bit DLLs
            FN32w4wt fnSave = (FN32w4wt)ppFN;
            nError = (*fnSave)( (PSZ)sTmpFile.GetBuffer(),
                                (PSZ)sFileName.GetBuffer(),
                                (PSZ)sVersion.GetBuffer(),
                                (PSZ)aEmptyByteStr.GetBuffer(),
                                (FN32Display)&W4WWriteDisplayHandler
                                );
        }
//Bug 33334: Modul wird von OS/2 nie aus dem Speicher entfernt,
// W4W stoplter darueber --> also nie entfernen!
//      DosFreeModule( hDLL );
    }
    else
        nError = ERR_DLL;
#endif  // PM2

#ifdef UNX

    String aParam( aFormat );
    aParam += ' ';
    aParam += rFileName;
    aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -N -t=" ));
    aParam += rTmpFile;
    aParam.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " -v" ));
    aParam += rVersion;

    ByteString sParam( aParam, ::gsl_getSystemTextEncoding() );
    nError = system( sParam.GetBuffer() );

#endif  // UNX
#endif  // MAC

static const ULONG nErrors[18]={ 0,ERR_SWG_WRITE_ERROR,
    ERR_W4W_READ_TMP_ERROR, ERR_W4W_READ_TMP_ERROR, ERR_SWG_WRITE_ERROR,
    0, ERR_W4W_WRITE_TMP_ERROR, ERR_W4W_WRITE_TMP_ERROR,
    ERR_W4W_MEM | ERROR_SW_WRITE_BASE, 0,
    ERR_W4W_WRITE_FULL | ERROR_SW_WRITE_BASE,
    0, 0, 0,
    0, ERR_SW6_PASSWD, ERR_W4W_INTERNAL_ERROR | ERROR_SW_WRITE_BASE,
    0 };

    if ( nError != 12 )         // 12 ist nur Warning
    {
        if ( nError == ERR_DLL )
            return ERR_W4W_DLL_ERROR | ERROR_SW_WRITE_BASE;
        if ( nError>0 && nError<=17 )
            return nErrors[ nError ];
    }
    return 0;
}

FASTBOOL W4WDLLExist( W4WDLL_TYPE eType, USHORT nFilter )
{
#ifdef MAC
    return TRUE;            // dann beim CallMacRes feststellen
#else

    String aFormat;
    switch( eType )
    {
    case W4WDLL_EXPORT:
    case W4WDLL_IMPORT:
#if defined( PM2 ) || defined( UNX )
        aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "w4w" ));
        if( nFilter < 10 )
            aFormat += '0';
        aFormat += String::CreateFromInt32( nFilter );
        aFormat += W4WDLL_IMPORT ? 'f' : 't';
#endif // PM2 || UNX

#if defined( WIN ) || defined( WNT )
        aFormat += 'w';
        if( nFilter < 10 )
            aFormat += '0';
        if( nFilter < 100 )
            aFormat += '0';
        aFormat += String::CreateFromInt32( nFilter );
        aFormat += W4WDLL_IMPORT ? 'f' : 't';
#if defined( WIN )
        aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "16W" ));
#else   // WIN
        aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "32W" ));
#endif  // WIN

#endif  // WIN || WNT
        break;

    case W4WDLL_AUTODETEC:
        aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "autorec" ));
        break;
    }

#ifndef UNX
    aFormat.AppendAscii( RTL_CONSTASCII_STRINGPARAM( ".dll" ));
#endif  // UNX

    // Fehlerbehandlung oder fuer Systeme die keine W4W-Filter kennen
    SvtPathOptions aOpt;

    return aOpt.SearchFile( aFormat, SvtPathOptions::PATH_FILTER );
#endif  // MAC
}

}
