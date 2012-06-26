/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <com/sun/star/registry/MergeConflictException.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#include <comphelper/processfactory.hxx>
#include <comphelper/string.hxx>

#include <bf_so3/embobj.hxx>

#include <tools/config.hxx>
#include <bf_svtools/pathoptions.hxx>
#include <bf_svtools/moduleoptions.hxx>
#include <tools/urlobj.hxx>
#include <unotools/ucbstreamhelper.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "sfx.hrc"
#include "docfilt.hxx"
#include "docfac.hxx"
#include "fltfnc.hxx"
#include "appdata.hxx"
#include "arrdecl.hxx"
#include "app.hxx"
#include "module.hxx"
#include <sfxuno.hxx>

//added by jmeng for include sleep() function for i31251
#if ( defined UNX ) || ( defined OS2 )   //Unix
#include <unistd.h>
#endif
namespace binfilter {

//========================================================================

DECL_PTRARRAY( SfxViewFactoryArr_Impl, SfxViewFactory*, 2, 2 )

//========================================================================

/*N*/ DBG_NAME(SfxObjectFactory)
/*N*/ TYPEINIT1(SfxObjectFactory,SvFactory);

/*N*/ static SfxObjectFactoryArr_Impl* pObjFac = 0;

//========================================================================

/*N*/ struct SfxObjectFactory_Impl
/*N*/ {
/*N*/   SfxFilterArr_Impl           aFilterArr;     // Liste von <SFxFilter>n
/*N*/   ::rtl::OUString             aServiceName;
/*N*/   sal_Bool                    bInitFactoryCalled;
/*N*/   SfxVoidFunc                 pInitFactory;
/*N*/   SfxFactoryFilterContainer*  pFilterContainer;
/*N*/   SfxModule*                  pModule;
/*N*/   String                      aStandardTemplate;
/*N*/   sal_Bool                    bTemplateInitialized;
/*N*/   sal_uInt16                  nCreateNewSlotId;
/*N*/
/*N*/   SfxObjectFactory_Impl() :
/*N*/       bInitFactoryCalled  ( sal_False ),
/*N*/       pInitFactory        ( NULL ),
/*N*/       pFilterContainer    ( NULL ),
/*N*/       pModule             ( NULL ),
/*N*/       bTemplateInitialized( sal_False ),
/*N*/       nCreateNewSlotId    ( 0 ) {}
/*N*/
/*N*/   ~SfxObjectFactory_Impl()
/*N*/   {
/*N*/   }
/*N*/
/*N*/   void ClearAccMgr()
/*N*/   {
/*N*/   }
/*N*/ };

//========================================================================

/*N*/ SfxFactoryFilterContainer* SfxObjectFactory::GetFilterContainer(
/*N*/   sal_Bool bForceLoad ) const
/*N*/ {
/*N*/   if( bForceLoad )
/*N*/       ((SfxObjectFactory *)this)->DoInitFactory();
/*N*/   return pImpl->pFilterContainer;
/*N*/ }

/*N*/ void SfxObjectFactory::RegisterInitFactory(SfxVoidFunc pFunc)
/*N*/ {
/*N*/   pImpl->pInitFactory = pFunc;
/*N*/     DoInitFactory();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::DoInitFactory()
/*N*/ {
/*N*/   if(!pImpl->bInitFactoryCalled)
/*N*/   {
/*N*/       pImpl->bInitFactoryCalled = sal_True;
/*N*/       // FilterContainer Landen
/*N*/       GetFilterCount( );
/*N*/       (*pImpl->pInitFactory)();
/*N*/
/*N*/         // There are no filters for "dummy" factory!
/*N*/         if( pImpl->aServiceName.compareToAscii("dummy") != 0 )
/*N*/         {
/*N*/             DBG_ASSERT( pImpl->aServiceName.getLength(), "No service name - no filters!" );
/*N*/             SfxFilterContainer *pCont = GetFilterContainer();
/*N*/             pCont->ReadExternalFilters( pImpl->aServiceName );
/*N*/         }
/*N*/   }
/*N*/ }

/*N*/ sal_uInt16 SfxObjectFactory::GetFilterCount() const
/*N*/ {
/*N*/   ((SfxObjectFactory *)this)->DoInitFactory();
/*N*/   return pImpl->pFilterContainer->GetFilterCount();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const SfxFilter* SfxObjectFactory::GetFilter(sal_uInt16 i) const
/*N*/ {
/*N*/   ((SfxObjectFactory *)this)->DoInitFactory();
/*N*/   return pImpl->pFilterContainer->GetFilter( i );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxObjectShell *SfxObjectFactory::CreateObject(SfxObjectCreateMode eMode) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SfxObjectFactory, 0);
/*N*/   return (*fnCreate)(eMode);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SfxObjectFactory::Construct
/*N*/ (
/*N*/   sal_uInt16      nFactoryId,
/*N*/   SfxObjectCtor   fnCreateFnc,
/*N*/   SfxObjectShellFlags nFlagsP,
/*N*/   const char*     pName
/*N*/ )
/*N*/ {
/*N*/   DBG_CHKTHIS(SfxObjectFactory, 0);
/*N*/
/*N*/   nFlags = nFlagsP;
/*N*/   fnCreate = fnCreateFnc;
/*N*/   nId = nFactoryId;
/*N*/ //  pIniMgr = 0;
/*N*/   pShortName = pName;
/*N*/   pImpl->pFilterContainer = new SfxFactoryFilterContainer(
/*N*/       String::CreateFromAscii( pName ), *this );
/*N*/   SFX_APP()->GetFilterMatcher().AddContainer( pImpl->pFilterContainer );
/*N*/   if( !(nFlagsP & SFXOBJECTSHELL_DONTLOADFILTERS) )
/*N*/       pImpl->pFilterContainer->LoadFilters( String::CreateFromAscii( pName ) );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxObjectFactory::SfxObjectFactory
/*N*/ (
/*N*/   const SvGlobalName&     rName,
/*N*/     const String&         rClassName,
/*N*/   CreateInstanceType      funcCIT
/*N*/ )
/*N*/ :   SvFactory( rName, rClassName, funcCIT ),
/*N*/   nId( 0 ),
/*N*/   fnCreate( 0 ),
/*N*/   pShortName( 0 ),
/*N*/   pImpl( new SfxObjectFactory_Impl )
/*N*/ {
/*N*/     DBG_CTOR(SfxObjectFactory, 0);
/*N*/
/*N*/     /*SfxApplication* pApp =*/ SFX_APP();
/*N*/     RegisterObjectFactory_Impl(*this);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxObjectFactory::~SfxObjectFactory()
/*N*/ {
/*N*/   DBG_DTOR(SfxObjectFactory, 0);
/*N*/
/*N*/   const sal_uInt16 nCount = pImpl->aFilterArr.Count();
/*N*/   for ( sal_uInt16 i = 0; i < nCount; ++i )
/*?*/       delete pImpl->aFilterArr[i];
/*N*/   delete pImpl;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::RemoveAll_Impl()
/*N*/ {
/*N*/     for( USHORT n=0; n<pObjFac->Count(); )
/*N*/     {
/*N*/         SfxObjectFactoryPtr pFac = pObjFac->GetObject(n);
/*N*/         pObjFac->Remove( n );
/*N*/         delete pFac;
/*N*/     }
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxObjectFactory::ClearAll_Impl()
/*?*/ {
/*?*/     for( USHORT n=0; n<pObjFac->Count(); n++ )
/*?*/     {
/*?*/       // Clear accelerator manager as it uses the same global SfxMacroConfig object as
/*?*/       // the application class does. This can lead to problems by using a newly created
/*?*/       // SfxMacroConfig object that doesn't have any macros inside => an assertion occur!
/*?*/         SfxObjectFactoryPtr pFac = pObjFac->GetObject(n);
/*?*/         pFac->pImpl->ClearAccMgr();
/*?*/     }
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::SetModule_Impl( SfxModule *pMod )
/*N*/ {
/*N*/   pImpl->pModule = pMod;
/*N*/ }

/*?*/ const SfxObjectFactory* SfxObjectFactory::GetFactory( const String& rFactoryURL )
/*?*/ {
/*N*/   const SfxObjectFactory* pFactory = 0;
/*N*/   String aFact( rFactoryURL );
/*N*/   String aPrefix( DEFINE_CONST_UNICODE( "private:factory/" ) );
/*N*/   if ( aPrefix.Len() == aFact.Match( aPrefix ) )
/*N*/       // Aufruf m"oglich mit z.B. "swriter" oder "private:factory/swriter"
/*N*/       aFact.Erase( 0, aPrefix.Len() );
/*N*/   sal_uInt16 nPos = aFact.Search( '?' );
/*N*/
/*N*/   // Etwaige Parameter abschneiden
/*N*/   aFact.Erase( nPos, aFact.Len() );
/*N*/
/*N*/   /*SfxApplication *pApp =*/ SFX_APP();
/*N*/
/*N*/   // "swriter4" durch "swriter" ersetzen, zum Vergleichen uppercase verwenden
/*N*/   WildCard aSearchedFac( comphelper::string::remove(aFact, '4').toAsciiUpperCase() );
/*N*/   for( sal_uInt16 n = GetObjectFactoryCount_Impl(); !pFactory && n--; )
/*N*/   {
/*N*/       pFactory = &GetObjectFactory_Impl( n );
/*N*/       String aCompareTo = String::CreateFromAscii( pFactory->GetShortName() );
/*N*/       aCompareTo.ToUpperAscii();
/*N*/       if( !aSearchedFac.Matches( aCompareTo ) )
/*N*/           pFactory = 0;
/*N*/   }
/*N*/
/*N*/   return pFactory;
/*?*/ }

/*N*/ void SfxObjectFactory::SetDocumentServiceName( const ::rtl::OUString& rServiceName )
/*N*/ {
/*N*/  pImpl->aServiceName = rServiceName;
/*N*/ }

/*N*/ const ::rtl::OUString& SfxObjectFactory::GetDocumentServiceName() const
/*N*/ {
/*N*/   return pImpl->aServiceName;
/*N*/ }

/*N*/ void SfxObjectFactory::RegisterObjectFactory_Impl( SfxObjectFactory &rFac )
/*N*/ {
/*N*/   SfxObjectFactory *pFac = &rFac;
/*N*/     GetObjFacArray_Impl().Insert( pFac, GetObjFacArray_Impl().Count() );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ USHORT SfxObjectFactory::GetObjectFactoryCount_Impl()
/*N*/ {
/*N*/     return GetObjFacArray_Impl().Count();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const SfxObjectFactory &SfxObjectFactory::GetObjectFactory_Impl(USHORT i)
/*N*/ {
/*N*/   return *GetObjFacArray_Impl()[i];
/*N*/ }

/*N*/ const SfxObjectFactory& SfxObjectFactory::GetDefaultFactory()
/*N*/ {
/*N*/   const SfxObjectFactory &rFactory = GetObjectFactory_Impl(0);
/*N*/   return rFactory;
/*N*/ }

/*N*/ SfxObjectFactoryArr_Impl&   SfxObjectFactory::GetObjFacArray_Impl()
/*N*/ {
/*N*/     if ( !pObjFac )
/*N*/         pObjFac = new SfxObjectFactoryArr_Impl;
/*N*/     return *pObjFac;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
