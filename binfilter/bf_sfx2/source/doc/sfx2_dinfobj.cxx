/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_dinfobj.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:23:55 $
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

//#include <string.h>

#pragma hdrstop

#include "app.hxx"
#include "objface.hxx"
#include "sfxsids.hrc"
#include "docinf.hxx"
#include "docfile.hxx"
#include "openflag.hxx"
#include "dinfobj.hxx"
#include "fcontnr.hxx"

#ifndef _SBXCLASS_HXX //autogen
#include "bf_basic/sbx.hxx"
#endif
//========================================================================

#define DocumentInfo
namespace binfilter {
#include "sfxslots.hxx"

#define aTypeLibInfo aDocumentInfoTypeLibImpl

//=========================================================================

SfxDocumentInfoObject_Impl::SfxDocumentInfoObject_Impl()
:   SvDispatch( DEFINE_CONST_UNICODE( "DocumentInfo" ) ),
    pMedium(0)
{
    // Sbx-Flags
    SetType( SbxOBJECT );
    SetFlag( SBX_FIXED );
    SetFlag( SBX_DONTSTORE );
    ResetFlag( SBX_WRITE );
}

//--------------------------------------------------------------------

SfxDocumentInfoObject_Impl::~SfxDocumentInfoObject_Impl()
{
    delete pMedium;
}

//--------------------------------------------------------------------

SvGlobalName SfxDocumentInfoObject_Impl::GetTypeName() const
{
    SvGlobalName aName;
    aName.MakeId( String::CreateFromAscii( aTypeLibInfo.pShellUId ) );
    return aName;
}

//--------------------------------------------------------------------

BOOL SfxDocumentInfoObject_Impl::FillTypeLibInfo( String * pName,
                                      USHORT * pMajor, USHORT * pMinor ) const
{
    *pName  = String::CreateFromAscii( aTypeLibInfo.pTypeLibName );
    *pMajor = aTypeLibInfo.nMajorVer;
    *pMinor = aTypeLibInfo.nMinorVer;
    return TRUE;
}

//------------------------------------------------------------------------

void SfxDocumentInfoObject_Impl::Notify( SfxBroadcaster& rBC,
                                         const SfxHint& rHint )

/*  [Beschreibung]

    Diese Klasse ist nicht von SfxShellObject abgeleitet, da keine
    SfxShell die Verarbeitung "ubernimmt. Das Ansprechen der Properties
    und Methoden arbeitet daher auch via Notify().
*/

{
    // vor Selbstzerst"orung sch"utzen
    DBG_ASSERT( GetRefCount() != SV_NO_DELETE_REFCOUNT,
                "notify on unreferenced object => dying!!!" )
    SbxObjectRef xSelfRef( this );

    const SbxHint* pHint = PTR_CAST(SbxHint,&rHint);
    if( pHint )
    {
        // Art des Hint und SID auswerten
        ULONG nHint = pHint ? pHint->GetId() : 0;
        SbxVariable* pVar = pHint->GetVar();
        BOOL bRead = BOOL( nHint == SBX_HINT_DATAWANTED &&
                           pVar->GetClass() == SbxCLASS_PROPERTY );
        BOOL bWrite = BOOL( nHint == SBX_HINT_DATACHANGED &&
                            pVar->GetClass() == SbxCLASS_PROPERTY );
        BOOL bCall = BOOL( nHint == SBX_HINT_DATAWANTED &&
                           pVar->GetClass() == SbxCLASS_METHOD );
        INT16 nSID = (INT16) ( pVar->GetUserData() & 0xFFFF );

        // Methode Load?
        if ( bCall && ( SID_DOCINFO_LOAD == nSID ) )
        {
            // ggf. altes Medium freigeben
            if ( pMedium )
                DELETEZ(pMedium);

            // 1. Parameter ist Dateiname
            SbxArray *pArgs = pVar->GetParameters();
            if ( !pArgs )
            {
                // Parameter fehlt
                pVar->PutBool( FALSE );
                return;
            }

            // Medium erstellen
            String aName( pArgs->Get(1)->GetString() );
            pMedium = new SfxMedium( aName, SFX_STREAM_READWRITE, TRUE );
            if ( !pMedium->GetStorage() )
            {
                // Datei existiert nicht oder ist kein Storage
                pVar->PutBool( FALSE );
                return;
            }

            // Storage "offnen
            SvStorageRef xStor = pMedium->GetStorage();
            if ( !xStor.Is() || SVSTREAM_OK != pMedium->GetError() )
            {
                // Fallback auf r/o
                delete pMedium;
                pMedium = new SfxMedium( aName, SFX_STREAM_READONLY, TRUE );
                xStor = pMedium->GetStorage();

                // konnte jetzt ge"offnet werden?
                if ( !xStor.Is() || SVSTREAM_OK != pMedium->GetError() )
                {
                    pVar->PutBool( FALSE );
                    return;
                }
            }

            // Filter-Detection wegen FileFormat-Version
            const SfxFilter *pFilter = 0;
            if ( 0 != SFX_APP()->GetFilterMatcher().GuessFilter( *pMedium, &pFilter ) ||
                 !pFilter )
            {
                // unbekannted Dateiformat
                pVar->PutBool( FALSE );
                return;
            }

            xStor->SetVersion( pFilter->GetVersion() );

            // DocInfo laden
            BOOL bOK = aDocInfo().Load( xStor );
            pVar->PutBool( bOK );
            if ( bOK )
                aDocInfo.SetValue( aName );
            return;
        }

        // Methode Save?
        else if ( bCall && ( SID_DOCINFO_SAVE == nSID ) )
        {
            // existiert ein Medium?
            if ( !pMedium )
            {
                // ohne Medium kein Speichern
                pVar->PutBool( FALSE );
                return;
            }

            // ggf. Filter-Detection wegen FileFormat-Version
            const SfxFilter *pFilter = 0;
            SFX_APP()->GetFilterMatcher().GuessFilter( *pMedium, &pFilter );

            // Storage "offnen
            SvStorageRef xStor = pMedium->GetStorage();
            xStor->SetVersion( pFilter
                                ? pFilter->GetVersion()
                                : SOFFICE_FILEFORMAT_CURRENT );
            // DocInfo speichern
            BOOL bOK = aDocInfo().Save( xStor ) && xStor->Commit();
            pVar->PutBool( bOK );
            return;
        }

        // Property auslesen?
        else if ( bRead && ( SID_DOCINFO == nSID ) )
        {
            aDocInfo.FillVariable( *pVar, SFX_MAPUNIT_MM, SFX_MAPUNIT_MM );
            return;
        }

        // Property setzen?
        else if ( bWrite && SID_DOCINFO == nSID )
        {
            aDocInfo.SetVariable( *pVar, SFX_MAPUNIT_MM, SFX_MAPUNIT_MM );
            return;
        }
    }

    SvDispatch::SFX_NOTIFY( rBC, rBCType, rHint, rHintType );
}


}
