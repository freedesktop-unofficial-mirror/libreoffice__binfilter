/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swcomlib.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:00:17 $
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



#define _SWLIB_CXX

#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#ifndef _SWWDOCSH_HXX //autogen
#include <wdocsh.hxx>
#endif
#ifndef _SWGLOBDOCSH_HXX //autogen
#include <globdoc.hxx>
#endif
#ifndef _SHELLIO_HXX //autogen
#include <shellio.hxx>
#endif

#include <app.hrc>
#include <web.hrc>
#include <globdoc.hrc>
namespace binfilter {

#define C2S(cChar) String::CreateFromAscii(cChar)

extern char __FAR_DATA sHTML[];

SwDLL::SwDLL()
{
}

SwDLL::~SwDLL()
{
}
//-------------------------------------------------------------------------
void    SwDLL::PreExit()
{
}

//-------------------------------------------------------------------------
void    SwDLL::Init()
{
}
//-------------------------------------------------------------------------
void    SwDLL::Exit()
{
}
//-------------------------------------------------------------------------

void    SwDLL::FillStatusBar(StatusBar &rBar)
{
}

//-------------------------------------------------------------------------

ULONG   SwDLL::DetectFilter( SfxMedium& rMedium, const SfxFilter** ppFilter,
                            SfxFilterFlags nMust, SfxFilterFlags nDont )
{
    ULONG nRet = ERRCODE_NONE;
    const SfxFilter* pSavFilter = *ppFilter;

    do {
            // dann ueberpruefe mal ob der richtige ausgewaehlt wurde
        if( *ppFilter )
        {
            const String& rUData = (*ppFilter)->GetUserData();

            BOOL bTxtFilter = rUData.EqualsAscii( FILTER_TEXT, 0, 4 );

            if (SwIoSystem::IsFileFilter( rMedium, rUData ) && !bTxtFilter)
                break;

            //JP 08.06.98: Bugfix 50498
            if (bTxtFilter)
            {
                //JP 09.11.98: der SWDOS - Filter hat dieselbe Extension und
                // wird vom SFX vorgeschlagen. Das es auch eine Textdatei ist,
                // muss die hier ausgefilter werden!
                if (SwIoSystem::IsFileFilter( rMedium, C2S("SW6"), ppFilter))
                    break;
            }
        }

        if( SFX_FILTER_TEMPLATE & nMust )
        {
            // nur einen Vorlagen Filter
            BOOL bStorage = rMedium.IsStorage();
            if( bStorage && *ppFilter )
                break;
            else if( bStorage &&
                ( SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_XMLV), ppFilter ) ||
                  SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_SW5V), ppFilter ) ||
                  SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_SW4V), ppFilter ) ||
                  SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_SW3V), ppFilter ) ||
                  SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_XMLVW), ppFilter ) ||
                  SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_SWW5V), ppFilter ) ||
                  SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_SWW4V), ppFilter ) ))
                break;
            else if( !bStorage &&
                SwIoSystem::IsFileFilter( rMedium, C2S(FILTER_SWGV), ppFilter ) )
                break;

            nRet = ERRCODE_ABORT;
            break;
        }


        String aPrefFlt;
        if( *ppFilter )
        {
            aPrefFlt = (*ppFilter)->GetUserData();
            if( SwIoSystem::IsFileFilter( rMedium, aPrefFlt ) )
            {
                nRet = ERRCODE_NONE;
                break;
            }

            // beim Browsen soll keine Filterbox kommen, wenn das Dokument nicht
            // in den ersten paar Bytes HTML-Tags hat (MA/ST/...). Solche Dok.
            // erzeugen z.B. SearchEngines
//JP 20.07.00: from now on we are not a browser
//          else if( aPrefFlt == C2S(sHTML) )
//          {
//              nRet = ERRCODE_NONE;
//              break;
//          }
        }

        const SfxFilter* pTmp = SwIoSystem::GetFileFilter( rMedium.GetPhysicalName(),
                                                            aPrefFlt, &rMedium );
        if( !pTmp )
            nRet = ERRCODE_ABORT;


        else if( *ppFilter && (*ppFilter)->GetUserData().EqualsAscii( "W4W", 0, 3 )
                    && pTmp->GetUserData().EqualsAscii( FILTER_TEXT, 0, 4 ) )
        {
            // Bug 95262 - if the user (or short  detect) select a
            //              Word 4 Word filter, but the autodect of mastersoft
            //              can't detect it, we normally return the ascii filter
            //              But the user may have a change to use the W4W filter,
            //              so the SFX must show now a dialog with the 2 filters
            nRet = ERRCODE_SFX_CONSULTUSER;
            *ppFilter = pTmp;
        }
        // sollte der voreingestellte Filter ASCII sein und wir haben
        // ASCII erkannt, dann ist das ein gultiger Filter, ansonsten ist das
        // ein Fehler und wir wollen die Filterbox sehen
        else if( pTmp->GetUserData().EqualsAscii( FILTER_TEXT ))
        {
            // Bug 28974: "Text" erkannt, aber "Text Dos" "Text ..." eingestellt
            //  -> keine FilterBox, sondern den eingestellten Filter benutzen
            if( *ppFilter && (*ppFilter)->GetUserData().EqualsAscii( FILTER_TEXT, 0, 4 ))
                ;
            else
//          if( !*ppFilter || COMPARE_EQUAL != pTmp->GetUserData().Compare(
//              (*ppFilter)->GetUserData(), 4 ))
            {
//              nRet = ERRCODE_ABORT;
                *ppFilter = pTmp;
            }
        }
        else
        {
            //Bug 41417: JP 09.07.97: HTML auf die WebDocShell defaulten
            if( pTmp->GetUserData() != C2S(sHTML) ||
                SwWebDocShell::Factory().GetFilterContainer() ==
                pTmp->GetFilterContainer() ||
                0 == ( (*ppFilter) = SwIoSystem::GetFilterOfFormat( C2S(sHTML),
                     SwWebDocShell::Factory().GetFilterContainer() ) ))

                *ppFilter = pTmp;
        }

    } while( FALSE );

    if( ERRCODE_NONE == nRet && (
        nMust != ( (*ppFilter)->GetFilterFlags() & nMust ) ||
        0 != ( (*ppFilter)->GetFilterFlags() & nDont )) )
    {
        nRet = ERRCODE_ABORT;
        *ppFilter = pSavFilter;
    }
    return nRet;
}

//-------------------------------------------------------------------------

ULONG SwDLL::GlobDetectFilter( SfxMedium& rMedium, const SfxFilter **ppFilter,
                                ULONG nMust, ULONG nDont )
{
    ULONG nRet = ERRCODE_ABORT;
    const SfxFilter* pSavFilter = *ppFilter;
    do {
            // dann ueberpruefe mal ob der richtige ausgewaehlt wurde
        if( rMedium.IsStorage() )
        {
            SvStorageRef aStg = rMedium.GetStorage();

            if( *ppFilter &&
                aStg.Is() && SVSTREAM_OK == aStg->GetError() &&
                SwIoSystem::IsValidStgFilter( *aStg, **ppFilter ))
            {
                nRet = ERRCODE_NONE;
                break;
            }

            if( SFX_FILTER_TEMPLATE & nMust )
                break;

            const SfxFilter* pFltr;
            const SfxFactoryFilterContainer& rFltContainer =
                            *SwGlobalDocShell::Factory().GetFilterContainer();
            USHORT nFltrCount = rFltContainer.GetFilterCount();
            for( USHORT nCnt = 0; nCnt < nFltrCount; ++nCnt )
                if( (sal_Unicode)'C' == ( pFltr = rFltContainer.GetFilter( nCnt ))->GetUserData().GetChar(0) &&
                    aStg.Is() && SwIoSystem::IsValidStgFilter( *aStg, *pFltr ))
                {
                    *ppFilter = pFltr;
                    nRet = ERRCODE_NONE;
                    break;
                }
        }

    } while( FALSE );

    if( ERRCODE_NONE == nRet && (
        nMust != ( (*ppFilter)->GetFilterFlags() & nMust ) ||
        0 != ( (*ppFilter)->GetFilterFlags() & nDont )) )
    {
        nRet = ERRCODE_ABORT;
        *ppFilter = pSavFilter;
    }

    return nRet;
}

//-------------------------------------------------------------------------

SvGlobalName SwModuleDummy::GetID(USHORT nFileFormat)
{
    SvGlobalName aName;
    switch ( nFileFormat )
    {
        case SOFFICE_FILEFORMAT_31:
            aName = SvGlobalName( BF_SO3_SW_CLASSID_30 );
        break;
        case SOFFICE_FILEFORMAT_40:
            aName = SvGlobalName( BF_SO3_SW_CLASSID_40 );
        break;
        case SOFFICE_FILEFORMAT_50:
            aName = SvGlobalName( BF_SO3_SW_CLASSID_50 );
        break;
        case SOFFICE_FILEFORMAT_60:
            aName = SvGlobalName( BF_SO3_SW_CLASSID_60 );
        break;
    }
    return aName;
}

USHORT       SwModuleDummy::HasID(const SvGlobalName& rName)
{
    if (GetID(SOFFICE_FILEFORMAT_31) == rName)
        return SOFFICE_FILEFORMAT_31;

    if (GetID(SOFFICE_FILEFORMAT_40) == rName)
        return SOFFICE_FILEFORMAT_40;

    if (GetID(SOFFICE_FILEFORMAT_50) == rName)
        return SOFFICE_FILEFORMAT_50;

    if (GetID(SOFFICE_FILEFORMAT_60) == rName)
        return SOFFICE_FILEFORMAT_60;
    return 0;
}

/*-----------------18.03.98 08.09-------------------

--------------------------------------------------*/
SwModuleDummy::~SwModuleDummy()
{
}


}
