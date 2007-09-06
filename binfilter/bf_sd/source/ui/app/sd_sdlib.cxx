/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdlib.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:21:59 $
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

#if SUPD <= 611
#endif

#include <so3/clsids.hxx>
#include <bf_svx/svxids.hrc>
#include <bf_svx/impgrf.hxx>

#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFXECODE_HXX //autogen
#include <svtools/sfxecode.hxx>
#endif
#ifndef _FILTER_CONFIG_ITEM_HXX_
#include <svtools/FilterConfigItem.hxx>
#endif
#ifndef _SOT_FORMATS_HXX //autogen
#include <sot/formats.hxx>
#endif

#ifndef _COM_SUN_STAR_UTIL_XARCHIVER_HPP_
#include <com/sun/star/util/XArchiver.hpp>
#endif

using namespace ::rtl;
using namespace ::com::sun::star;


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "sddll.hxx"

//STRIP009 #ifdef UNX
//STRIP009 #define DLL_NAME SVLIBRARY( "sd" )
//STRIP009 #else
#include "sddll0.hxx"         // wird durchs Makefile generiert
//STRIP009 #endif

#include "grdocsh.hxx"
#include "res_bmp.hrc"
#include "strings.hrc"
#include "app.hrc"
#include "strmname.h"


#ifndef _OFF_OFAIDS_HRC
#include <bf_offmgr/ofaids.hrc>
#endif

#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

/*N*/ TYPEINIT1( SdModuleDummy, SfxModule );

/*N*/ SFX_IMPL_MODULE_LIB(Sd, UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( DLL_NAME ) ) )

/*************************************************************************
|*
|* Impress-ObjectFactory registrieren
|*
\************************************************************************/

/*N*/ SFX_IMPL_OBJECTFACTORY_MOD(SdDrawDocShell, SFXOBJECTSHELL_STD_NORMAL, simpress,
/*N*/                          SvGlobalName(BF_SO3_SIMPRESS_CLASSID), Sd, UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( DLL_NAME ) ) ) //STRIP002
/*N*/ {
/*N*/   SdDrawDocShell::Factory().SetDocumentServiceName( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.presentation.PresentationDocument" ) ) );
/*N*/   SdDrawDocShell::Factory().GetFilterContainer()->SetDetectFilter( &SdDLL::DetectFilter );
/*N*/ }



/*************************************************************************
|*
|* Draw-ObjectFactory registrieren
|*
\************************************************************************/

/*N*/ SFX_IMPL_OBJECTFACTORY_MOD(SdGraphicDocShell, SFXOBJECTSHELL_STD_NORMAL, sdraw,
/*N*/                          SvGlobalName(BF_SO3_SDRAW_CLASSID), Sd, UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( DLL_NAME ) ) ) //STRIP002
/*N*/ {
/*N*/   SdGraphicDocShell::Factory().SetDocumentServiceName( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.DrawingDocument" ) ) );
/*N*/   SdGraphicDocShell::Factory().GetFilterContainer()->SetDetectFilter( &SdDLL::DetectFilter );
/*N*/ }


/*************************************************************************
|*
|* Ctor
|* the ctor is called at the beginning of SfxApplication-subclass::Main()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

/*N*/ SdDLL::SdDLL()
/*N*/ {
/*N*/ }



/*************************************************************************
|*
|* Dtor
|* the dtor is called at the end of SfxApplication-subclass::Main()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

/*N*/ SdDLL::~SdDLL()
/*N*/ {
/*N*/ }



/*************************************************************************
|*
|* LibInit
|* method is called before Application::Execute()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

/*N*/ void SdDLL::LibInit()
/*N*/ {
/*N*/   // in most cases you must initialize your document-factory here
/*N*/   SfxApplication* pApp = SFX_APP();
/*N*/
/*N*/   // create a dummy-module for Object-Factory-Pointer
/*N*/   SfxObjectFactory *p1 = NULL;
/*N*/   if(SvtModuleOptions().IsImpress())
/*N*/   {
/*N*/       SdDrawDocShell::RegisterFactory(SDT_SD_DOCFACTPRIO);
/*N*/       p1 = &SdDrawDocShell::Factory();
/*N*/   }

/*N*/   SfxObjectFactory *p2 = NULL;
/*N*/   if(SvtModuleOptions().IsDraw())
/*N*/   {
/*N*/       SdGraphicDocShell::RegisterFactory(SDT_SD_DOCFACTPRIO);
/*N*/       p2 = &SdGraphicDocShell::Factory();
/*N*/   }
/*N*/
/*N*/     SD_MOD() = new SdModuleDummy( NULL, TRUE, p1, p2 );
/*N*/ }



/*************************************************************************
|*
|* LibExit
|* this method is called after Application::Execute()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

/*N*/ void SdDLL::LibExit()
/*N*/ {
/*N*/   // Innerhalb von FreeLibSd wird Exit() gerufen
/*N*/   FreeLibSd();
/*N*/
/*N*/   // destroy the dummy-module with Object-Factory-Pointer
/*N*/   DELETEZ( SD_MOD() );
/*N*/ }


/*************************************************************************
|*
|* Filter bestimmen
|* (wird fuer normales Laden eines Dokuments mit nClass == USHRT_MAX gerufen)
|*
\************************************************************************/

/*N*/ ULONG __EXPORT SdDLL::DetectFilter(SfxMedium& rMedium, const SfxFilter** pFilter,
/*N*/                         SfxFilterFlags nMust, SfxFilterFlags nDont)
/*N*/ {
/*N*/   ULONG nReturn = ERRCODE_ABORT;  // Erkennung fehlgeschlagen, Filter ungueltig
/*N*/   BOOL bStorage = FALSE;
/*N*/
/*N*/   if( *pFilter && (*pFilter)->GetFilterFlags() & SFX_FILTER_PACKED )
/*N*/   {
/*N*/       uno::Reference< lang::XMultiServiceFactory > xSMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/       uno::Reference< util::XArchiver > xPacker( xSMgr->createInstance( OUString::createFromAscii( "com.sun.star.util.Archiver" ) ), uno::UNO_QUERY );
/*N*/       if( xPacker.is() )
/*N*/       {
/*N*/           // extract extra data
/*N*/           OUString aPath( rMedium.GetOrigURL() );
/*N*/           OUString aExtraData( xPacker->getExtraData( aPath ) );
/*N*/           const OUString aSig1= OUString::createFromAscii( "private:" );
/*N*/           String aTmp;
/*N*/           aTmp += sal_Unicode( '?' );
/*N*/           aTmp += (*pFilter)->GetFilterContainer()->GetName();
/*N*/           const OUString aSig2( aTmp );
/*N*/           INT32 nIndex1 = aExtraData.indexOf( aSig1 );
/*N*/           INT32 nIndex2 = aExtraData.indexOf( aSig2 );
/*N*/           if( nIndex1 == 0 && nIndex2 != -1 )
/*N*/               return ERRCODE_NONE;
/*N*/       }
/*N*/   }
/*N*/   else if (rMedium.GetError() == SVSTREAM_OK)
/*N*/   {
/*N*/       if (rMedium.IsStorage())
/*N*/       {
/*N*/           bStorage = TRUE;
/*N*/           // Storage
/*N*/           SvStorage* pStorage = rMedium.GetStorage();
/*N*/           if ( pStorage == NULL ) return ULONG_MAX;
/*N*/
/*N*/
/*N*/           // Erkennung ueber contained streams (StarDraw 3.0)
/*N*/           if( ( pStorage->IsContained( pStarDrawDoc ) && pStorage->IsStream( pStarDrawDoc ) ) ||
/*N*/               ( pStorage->IsContained( pStarDrawDoc3 ) && pStorage->IsStream( pStarDrawDoc3 ) ) )
/*N*/           {
/*N*/               const SfxFilter* pFilt = NULL;
/*N*/               SfxFilterMatcher& rMatcher = SFX_APP()->GetFilterMatcher();
/*N*/               SfxFilterContainer *pDraw = rMatcher.GetContainer(
/*N*/                                           UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "sdraw" ) ) ); // Name kennt ihr besser
/*N*/               SfxFilterContainer *pImpr = rMatcher.GetContainer(
/*N*/                                           UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "simpress" ) )); // dito
/*N*/               ULONG nStorFmt = pStorage->GetFormat();
/*N*/               if (*pFilter)
/*N*/               {
/*N*/                   if ( (*pFilter)->GetFilterContainer() == pDraw)
/*N*/                   {
/*N*/                       if(SvtModuleOptions().IsDraw())
/*N*/                       {
/*N*/                           pFilt = pDraw->GetFilter4ClipBoardId( nStorFmt );
/*N*/                           nReturn = ERRCODE_SFX_FORCEQUIET;
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           pFilt = pImpr->GetFilter4ClipBoardId( nStorFmt );
/*N*/                           nReturn = ERRCODE_SFX_FORCEQUIET;
/*N*/                       }
/*N*/                   }
/*N*/                   else if ( (*pFilter)->GetFilterContainer() == pImpr)
/*N*/                   {
/*N*/                       if(SvtModuleOptions().IsImpress())
/*N*/                       {
/*N*/                           pFilt = pImpr->GetFilter4ClipBoardId( nStorFmt );
/*N*/                           nReturn = ERRCODE_SFX_FORCEQUIET;
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           pFilt = pDraw->GetFilter4ClipBoardId( nStorFmt );
/*N*/                           nReturn = ERRCODE_SFX_FORCEQUIET;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               else if(SvtModuleOptions().IsImpress())
/*N*/               {
/*N*/                   pFilt = pImpr->GetFilter4ClipBoardId( nStorFmt );
/*N*/                   nReturn = ERRCODE_NONE;
/*N*/               }
/*N*/               else if(SvtModuleOptions().IsDraw())
/*N*/               {
/*N*/                   pFilt = pDraw->GetFilter4ClipBoardId( nStorFmt );
/*N*/                   nReturn = ERRCODE_NONE;
/*N*/               }
/*N*/
/*N*/               if (pFilt &&
/*N*/                   (pFilt->GetFilterFlags() & nMust) == nMust &&
/*N*/                   (pFilt->GetFilterFlags() & nDont) == 0)
/*N*/               {
/*N*/                   *pFilter = pFilt;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   *pFilter = NULL;
/*N*/                   nReturn = ERRCODE_NONE;
/*N*/               }
/*N*/           }
/*N*/           else if(SvtModuleOptions().IsImpress())
/*N*/           {
/*N*/               // Erkennung ueber contained streams (PowerPoint 97-Filter)
/*N*/               String aStreamName = UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "PowerPoint Document" ) );
/*N*/
/*N*/               if (pStorage->IsContained( aStreamName ) && pStorage->IsStream( aStreamName ) )
/*N*/               {
/*N*/                   String aFileName(rMedium.GetName());
/*N*/                   aFileName.ToUpperAscii();
/*N*/
/*N*/                   if( aFileName.SearchAscii( ".POT" ) == STRING_NOTFOUND )
/*N*/                       *pFilter = SFX_APP()->GetFilter(SdDrawDocShell::Factory(), pFilterPowerPoint97);
/*N*/                   else
/*N*/                       *pFilter = SFX_APP()->GetFilter(SdDrawDocShell::Factory(), pFilterPowerPoint97Template);
/*N*/
/*N*/                   return ERRCODE_NONE;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // XML filter(s)
/*N*/       if( *pFilter )
/*N*/       {
/*N*/           ::rtl::OUString aName = (*pFilter)->GetFilterName();
/*N*/
/*N*/           if( aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("StarOffice XML (Draw)")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("StarOffice XML (Impress)")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("draw_StarOffice_XML_Impress")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("impress_StarOffice_XML_Draw")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("impress_StarOffice_XML_Impress_Template")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("draw_StarOffice_XML_Draw_Template")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("draw_StarOffice_XML_Draw")) ||
/*N*/               aName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("impress_StarOffice_XML_Impress")))
/*N*/           {
/*N*/               if( rMedium.IsStorage() )
/*N*/               {
/*N*/                   SvStorage* pStorage = rMedium.GetStorage();
/*N*/
/*N*/                   nReturn = ERRCODE_ABORT;
/*N*/
/*N*/                   if( pStorage && ( pStorage->IsStream( pStarDrawXMLContent ) || pStorage->IsStream( pStarDrawOldXMLContent ) ) )
/*N*/                   {
/*N*/                       const ULONG nStorageFormat = pStorage->GetFormat();
/*N*/                       if( nStorageFormat == 0 ||
/*N*/                           nStorageFormat == SOT_FORMATSTR_ID_STARIMPRESS_60 ||
/*N*/                           nStorageFormat == SOT_FORMATSTR_ID_STARDRAW_60  )
/*N*/                       {
/*N*/                           nReturn = ERRCODE_NONE;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       String aFileName(rMedium.GetName());
/*N*/       aFileName.ToUpperAscii();
/*N*/
/*N*/       if (nReturn == ERRCODE_ABORT)
/*N*/       {
/*N*/           if( bStorage )         // aber keine Clipboard-Id #55337#
/*N*/           {
/*N*/               *pFilter = NULL;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // Vektorgraphik?
/*N*/               SvStream* pStm = rMedium.GetInStream();
/*N*/
/*N*/               if( !pStm )
/*N*/                   nReturn = ERRCODE_IO_GENERAL;
/*N*/               else
/*N*/               {
/*N*/                   pStm->Seek( STREAM_SEEK_TO_BEGIN );
/*N*/
/*N*/                   const String        aFileName( rMedium.GetURLObject().GetMainURL( INetURLObject::NO_DECODE ) );
/*N*/                   GraphicDescriptor   aDesc( *pStm, &aFileName );
/*N*/                   GraphicFilter*      pGrfFilter = GetGrfFilter();
/*N*/
/*N*/                   if( !aDesc.Detect( FALSE ) )
/*N*/                   {
/*N*/                       *pFilter = NULL;
/*N*/                       nReturn = ERRCODE_ABORT;
/*N*/                       INetURLObject aURL( aFileName );
/*N*/                       if( aURL.getExtension().equalsIgnoreAsciiCaseAscii( "cgm" ) )
/*N*/                       {
/*N*/                           sal_uInt8 n8;
/*N*/                           pStm->Seek( STREAM_SEEK_TO_BEGIN );
/*N*/                           *pStm >> n8;
/*N*/                           if ( ( n8 & 0xf0 ) == 0 )       // we are supporting binary cgm format only, so
/*N*/                           {                               // this is a small test to exclude cgm text
/*N*/                               const String aName = UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "CGM - Computer Graphics Metafile" ) );
/*N*/                               *pFilter = SFX_APP()->GetFilter( SdDrawDocShell::Factory(), aName );
/*N*/                               nReturn = ERRCODE_NONE;
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       if( SvtModuleOptions().IsDraw() )
/*N*/                       {
/*N*/                           String aShortName( aDesc.GetImportFormatShortName( aDesc.GetFileFormat() ) );
/*N*/                           const String aName( pGrfFilter->GetImportFormatTypeName( pGrfFilter->GetImportFormatNumberForShortName( aShortName ) ) );
/*N*/
/*N*/                             if ( *pFilter && aShortName.EqualsIgnoreCaseAscii( "PCD" ) )    // there is a multiple pcd selection possible
/*N*/                             {
/*N*/                                 sal_Int32 nBase = 2;    // default Base0
/*N*/                                 String aFilterTypeName( (*pFilter)->GetRealTypeName() );
/*N*/                                 if ( aFilterTypeName.CompareToAscii( "pcd_Photo_CD_Base4" ) == COMPARE_EQUAL )
/*N*/                                     nBase = 1;
/*N*/                                 else if ( aFilterTypeName.CompareToAscii( "pcd_Photo_CD_Base16" ) == COMPARE_EQUAL )
/*N*/                                     nBase = 0;
/*N*/                               String aFilterConfigPath( RTL_CONSTASCII_USTRINGPARAM( "Office.Common/Filter/Graphic/Import/PCD" ) );
/*N*/                                 FilterConfigItem aFilterConfigItem( aFilterConfigPath );
/*N*/                                 aFilterConfigItem.WriteInt32( String( RTL_CONSTASCII_USTRINGPARAM( "Resolution" ) ), nBase );
/*N*/                             }
/*N*/
/*N*/                           *pFilter = SFX_APP()->GetFilter( SdGraphicDocShell::Factory(), aName );
/*N*/                           nReturn = ERRCODE_NONE;
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           nReturn = ERRCODE_ABORT;
/*N*/                           *pFilter = NULL;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nReturn = rMedium.GetError();
/*N*/   }
/*N*/
/*N*/   return nReturn;
/*N*/ }



/*************************************************************************
|*
|* Modul laden
|*
\************************************************************************/

SfxModule* SdModuleDummy::Load()
{
    return (LoadLibSd() ? SD_MOD() : NULL);
}




/*************************************************************************
|*
|* GetID(), ID zu einer Fileformat-Version liefern
|*
\************************************************************************/

SvGlobalName SdModuleDummy::GetID(USHORT nFileFormat)
{
    SvGlobalName aName;

    switch (nFileFormat)
    {
        case SOFFICE_FILEFORMAT_60:
        {
            aName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_60);
        }
        break;

        case SOFFICE_FILEFORMAT_50:
        {
            aName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_50);
        }
        break;

        case SOFFICE_FILEFORMAT_40:
        {
            aName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_40);
        }
        break;

        case SOFFICE_FILEFORMAT_31:
        {
            aName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_30);
        }
        break;

        default:
        {
            DBG_ASSERT(FALSE, "Unbekanntes Fileformat!");
        }
        break;
    }

    return aName;
}


/*************************************************************************
|*
|* HasID(), zu einer ID die Fileformat-Version liefern
|*
\************************************************************************/

USHORT SdModuleDummy::HasID(const SvGlobalName& rName)
{
    USHORT nRet = 0;

    if (GetID(SOFFICE_FILEFORMAT_31) == rName)
    {
        // Draw 3.1
        nRet = SOFFICE_FILEFORMAT_31;
    }
    else if (GetID(SOFFICE_FILEFORMAT_40) == rName)
    {
        // Impress 4.0
        nRet = SOFFICE_FILEFORMAT_40;
    }
    else if (GetID(SOFFICE_FILEFORMAT_50) == rName)
    {
        // Impress 5.0
        nRet = SOFFICE_FILEFORMAT_50;
    }
    else if (SvGlobalName(BF_SO3_SDRAW_CLASSID_50) == rName)
    {
        // Draw 5.0
        nRet = SOFFICE_FILEFORMAT_50;
    }
    else if (GetID(SOFFICE_FILEFORMAT_60) == rName)
    {
        // Impress 6.0
        nRet = SOFFICE_FILEFORMAT_60;
    }
    else if (SvGlobalName(BF_SO3_SDRAW_CLASSID_60) == rName)
    {
        // Draw 6.0
        nRet = SOFFICE_FILEFORMAT_60;
    }

    return(nRet);
}
}
