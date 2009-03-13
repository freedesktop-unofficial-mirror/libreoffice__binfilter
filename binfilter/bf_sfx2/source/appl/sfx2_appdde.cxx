/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sfx2_appdde.cxx,v $
 * $Revision: 1.12 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _SVDDE_HXX //autogen
#include <bf_svtools/svdde.hxx>
#endif
#include <tools/urlobj.hxx>
#include <bf_svtools/pathoptions.hxx>
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "app.hxx"
#include "appdata.hxx"
#include "objsh.hxx"
#include "sfxsids.hrc"

#include <bf_sfx2/sfxuno.hxx>

namespace binfilter {

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

/*?*/ ::binfilter::SvLinkSource* SfxObjectShell::DdeCreateLinkSource
/*?*/ (
/*?*/   const String&   rItem      // das zu erzeugende Item
/*?*/ )

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//========================================================================

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
