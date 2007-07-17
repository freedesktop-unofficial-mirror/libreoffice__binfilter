/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appdde.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:34:37 $
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

#ifndef _SVDDE_HXX //autogen
#include <svtools/svdde.hxx>
#endif
#include <tools/urlobj.hxx>
#include <svtools/pathoptions.hxx>
#pragma hdrstop

#include "app.hxx"
#include "appdata.hxx"
#include "objsh.hxx"
#include "sfxsids.hrc"

#include <bf_sfx2/sfxuno.hxx>

namespace binfilter {

//========================================================================

/*N*/ String SfxDdeServiceName_Impl( const String& sIn )
/*N*/ {
/*N*/   ByteString sTemp = U2S( sIn );
/*N*/   ByteString sReturn;
/*N*/
/*N*/   for ( sal_uInt16 n = sTemp.Len(); n; --n )
/*N*/       if ( sTemp.Copy( n-1, 1 ).IsAlphaNumericAscii() )
/*N*/           sReturn += sTemp.GetChar(n-1);
/*N*/
/*N*/   return S2U( sReturn );
/*N*/ }


class ImplDdeService : public DdeService
{
public:
    ImplDdeService( const String& rNm )
        : DdeService( rNm )
    {}
    virtual BOOL MakeTopic( const String& );

    virtual String  Topics();
//  virtual String  Formats();
//  virtual String  SysItems();
//  virtual String  Status();

    virtual BOOL SysTopicExecute( const String* pStr );
};

class SfxDdeTriggerTopic_Impl : public DdeTopic
{
public:
    SfxDdeTriggerTopic_Impl()
    : DdeTopic( DEFINE_CONST_UNICODE("TRIGGER") )
    {}

    virtual BOOL Execute( const String* );
};

class SfxDdeDocTopic_Impl : public DdeTopic
{
public:
    SfxObjectShell* pSh;
    DdeData aData;
    ::com::sun::star::uno::Sequence< sal_Int8 > aSeq;

    SfxDdeDocTopic_Impl( SfxObjectShell* pShell )
        : DdeTopic( pShell->GetTitle(SFX_TITLE_FULLNAME) ), pSh( pShell )
    {}

    virtual DdeData* Get( ULONG );
    virtual BOOL Put( const DdeData* );
    virtual BOOL Execute( const String* );
    virtual BOOL StartAdviseLoop();
    virtual BOOL MakeItem( const String& rItem );

// wird benoetigt?
//  virtual void Connect( long n );
//  virtual void Disconnect( long n );
//  virtual void StopAdviseLoop();

};


SV_DECL_PTRARR( SfxDdeDocTopics_Impl, SfxDdeDocTopic_Impl * const, 4, 4 )
SV_IMPL_PTRARR( SfxDdeDocTopics_Impl, SfxDdeDocTopic_Impl * const )

//========================================================================


//-------------------------------------------------------------------------


//--------------------------------------------------------------------


//--------------------------------------------------------------------


//--------------------------------------------------------------------


//========================================================================

/*?*/ long SfxObjectShell::DdeExecute
/*?*/ (
/*?*/   const String&   rCmd        // in unserer BASIC-Syntax formuliert
/*?*/ )

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*?*/ long SfxObjectShell::DdeGetData
/*?*/ (
/*?*/   const String&   rItem,                      // das anzusprechende Item
/*?*/   const String& rMimeType,                    // in: Format
/*?*/   ::com::sun::star::uno::Any & rValue     // out: angeforderte Daten
/*?*/ )
{DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*?*/ long SfxObjectShell::DdeSetData
/*?*/ (
/*?*/   const String&   rItem,                      // das anzusprechende Item
/*?*/   const String& rMimeType,                    // in: Format
/*?*/   const ::com::sun::star::uno::Any & rValue   // out: angeforderte Daten
/*?*/ )
/*?*/
/*  [Beschreibung]

    Diese Methode kann vom Applikationsentwickler "uberladen werden,
    um an seine SfxObjectShell-Subklasse gerichtete DDE-Daten
    zu empfangen.

    Die Basisimplementierung nimmt keine Daten entgegen und liefert 0 zur"uck.
*/
/*?*/
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*?*/ ::so3::SvLinkSource* SfxObjectShell::DdeCreateLinkSource
/*?*/ (
/*?*/   const String&   rItem      // das zu erzeugende Item
/*?*/ )

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//========================================================================

/*N*/ BOOL SfxApplication::InitializeDde()
/*N*/ {
/*N*/   DBG_ASSERT( !pAppData_Impl->pDdeService,
/*N*/               "Dde kann nicht mehrfach initialisiert werden" )
/*N*/
/*N*/   pAppData_Impl->pDdeService = new ImplDdeService( Application::GetAppName() );
/*N*/   int nError = pAppData_Impl->pDdeService->GetError();
/*N*/   if( !nError )
/*N*/   {
/*N*/       pAppData_Impl->pDocTopics = new SfxDdeDocTopics_Impl;
/*N*/
/*N*/       // wir wollen auf jedenfall RTF unterstuetzen!
/*N*/       pAppData_Impl->pDdeService->AddFormat( FORMAT_RTF );
/*N*/
/*N*/       // Config-Pfad als Topic wegen Mehrfachstart
/*N*/         INetURLObject aOfficeLockFile( SvtPathOptions().GetUserConfigPath() );
/*N*/       aOfficeLockFile.insertName( DEFINE_CONST_UNICODE( "soffice.lck" ) );
/*N*/         String aService( SfxDdeServiceName_Impl(
/*N*/                   aOfficeLockFile.GetMainURL(INetURLObject::DECODE_TO_IURI) ) );
/*N*/       aService.ToUpperAscii();
/*N*/       pAppData_Impl->pDdeService2 = new ImplDdeService( aService );
/*N*/       pAppData_Impl->pTriggerTopic = new SfxDdeTriggerTopic_Impl;
/*N*/       pAppData_Impl->pDdeService2->AddTopic( *pAppData_Impl->pTriggerTopic );
/*N*/   }
/*N*/   return !nError;
/*N*/ }

/*N*/ void SfxAppData_Impl::DeInitDDE()
/*N*/ {
/*N*/     DELETEZ( pTriggerTopic );
/*N*/     DELETEZ( pDdeService2 );
/*N*/     DELETEZ( pDocTopics );
/*N*/     DELETEZ( pDdeService );
/*N*/ }

//--------------------------------------------------------------------


/*N*/ void SfxApplication::RemoveDdeTopic( SfxObjectShell* pSh )
/*N*/ {
// #i30187# DDE not needed for binfilter/*N*/   DBG_ASSERT( pAppData_Impl->pDocTopics, "es gibt gar keinen Dde-Service" )
/*N*/   //OV: Im Serverbetrieb ist DDE abgeklemmt!
/*N*/   if( !pAppData_Impl->pDocTopics )
/*N*/       return;
/*N*/
///*N*/     SfxDdeDocTopic_Impl* pTopic;
///*N*/     for( USHORT n = pAppData_Impl->pDocTopics->Count(); n; )
///*?*/         if( ( pTopic = (*pAppData_Impl->pDocTopics)[ --n ])->pSh == pSh )
///*?*/         {
///*?*/             pAppData_Impl->pDdeService->RemoveTopic( *pTopic );
///*?*/             pAppData_Impl->pDocTopics->DeleteAndDestroy( n );
///*?*/         }
/*N*/ }


/*N*/ DdeService* SfxApplication::GetDdeService()
/*N*/ {
/*N*/   return pAppData_Impl->pDdeService;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ BOOL ImplDdeService::MakeTopic( const String& rNm )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ String ImplDdeService::Topics()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); String aRet; return aRet;//STRIP001
/*?*/ }

/*?*/ BOOL ImplDdeService::SysTopicExecute( const String* pStr )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*?*/ BOOL SfxDdeTriggerTopic_Impl::Execute( const String* pStr )
{DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

//--------------------------------------------------------------------
/*?*/ DdeData* SfxDdeDocTopic_Impl::Get( ULONG nFormat )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::Put( const DdeData* pData )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::Execute( const String* pStr )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::MakeItem( const String& rItem )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::StartAdviseLoop()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }


}
