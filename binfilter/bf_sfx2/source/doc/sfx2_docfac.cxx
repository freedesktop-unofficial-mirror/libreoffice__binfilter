/*************************************************************************
 *
 *  $RCSfile: sfx2_docfac.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:56 $
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

#ifndef _COM_SUN_STAR_REGISTRY_MERGECONFLICTEXCEPTION_HPP_
#include <com/sun/star/registry/MergeConflictException.hpp>
#endif
#ifndef _COM_SUN_STAR_REGISTRY_XSIMPLEREGISTRY_HPP_
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#endif
#ifndef _UNOTOOLS_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _EMBOBJ_HXX //autogen
#include <so3/embobj.hxx>
#endif

#include <vcl/config.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/moduleoptions.hxx>
#include <tools/urlobj.hxx>
#include <unotools/ucbstreamhelper.hxx>

#pragma hdrstop

#include "sfx.hrc"
#include "docfilt.hxx"
#include "docfac.hxx"
#include "viewfac.hxx"
#include "fltfnc.hxx"
#include "appdata.hxx"
#include "arrdecl.hxx"
#include "app.hxx"
#include "module.hxx"
#include "mnumgr.hxx"
#include "accmgr.hxx"
#include <sfxresid.hxx>
#include <sfxuno.hxx>
#include "doc.hrc"

//========================================================================

DECL_PTRARRAY( SfxViewFactoryArr_Impl, SfxViewFactory*, 2, 2 );

//========================================================================

/*N*/ DBG_NAME(SfxObjectFactory);
/*N*/ TYPEINIT1(SfxObjectFactory,SvFactory);

/*N*/ static SfxObjectFactoryArr_Impl* pObjFac = 0;

//========================================================================

/*N*/ struct SfxObjectFactory_Impl
/*N*/ {
/*N*/   SfxViewFactoryArr_Impl      aViewFactoryArr;// Liste von <SfxViewFactory>s
/*N*/   SfxFilterArr_Impl           aFilterArr;     // Liste von <SFxFilter>n
/*N*/   ResId*                      pMenuBarResId;
/*N*/   ResId*                      pPluginMenuBarResId;
/*N*/   ResId*                      pAccelResId;
/*N*/   ResId*                      pNameResId;
/*N*/   String                      aHelpFile;
/*N*/   String                      aHelpPIFile;
/*N*/   ::rtl::OUString             aServiceName;
/*N*/   sal_Bool                    bInitFactoryCalled;
/*N*/   SfxVoidFunc                 pInitFactory;
/*N*/   SfxFactoryFilterContainer*  pFilterContainer;
/*N*/   SfxModule*                  pModule;
/*N*/   SfxAcceleratorManager*      pAccMgr;
/*N*/   sal_uInt16                  nImageId;
/*N*/   sal_Bool                    bOwnsAccel;
/*N*/   String                      aStandardTemplate;
/*N*/   sal_Bool                    bTemplateInitialized;
/*N*/   sal_uInt16                  nCreateNewSlotId;
/*N*/
/*N*/   SfxObjectFactory_Impl() :
/*N*/       pMenuBarResId       ( NULL ),
/*N*/       pPluginMenuBarResId ( NULL ),
/*N*/       pAccelResId         ( NULL ),
/*N*/       pNameResId          ( NULL ),
/*N*/       bInitFactoryCalled  ( sal_False ),
/*N*/       pInitFactory        ( NULL ),
/*N*/       pFilterContainer    ( NULL ),
/*N*/       pModule             ( NULL ),
/*N*/       pAccMgr             ( NULL ),
/*N*/       nImageId            ( 0 ),
/*N*/       bTemplateInitialized( sal_False ),
/*N*/       nCreateNewSlotId    ( 0 ) {}
/*N*/
/*N*/   ~SfxObjectFactory_Impl()
/*N*/   {
/*N*/       delete pMenuBarResId;
/*N*/       delete pPluginMenuBarResId;
/*N*/       delete pAccelResId;
/*N*/       // Jetzt vom FilterMatcher
/*N*/       // delete pFilterContainer;
/*N*/         if ( bOwnsAccel )
/*N*/             delete pAccMgr;
/*N*/   }
/*N*/
/*N*/   void ClearAccMgr()
/*N*/   {
/*N*/       if ( bOwnsAccel )
/*N*/         {
/*N*/             delete pAccMgr;
/*N*/           pAccMgr = 0;
/*N*/       }
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

/*?*/ void SfxObjectFactory::RegisterFilter
/*?*/ (
/*?*/   const String&       rName,          // Klartext-Name f"ur Anzeige im Dialog
/*?*/   const String&       rWildcard,      // Default-Wildcards
/*?*/   SfxFilterFlags      eType,          // SFX_FILTER_...
/*?*/   sal_uInt32               lFormat,        // Clipboard-Format
/*?*/   const String&       rMacType,       // 4-Byte-Type f"ur Apple Macintosh
/*?*/   const String&       rTypeName,      // String-Type f"ur OS/2
/*?*/   sal_uInt16              nIconId,        // Resource-Id f"ur Icon
/*?*/   const String&       rMimeType,
/*?*/   const String&       rUserData       // zum Wiedererkennen oder (frei verwendbar)
/*?*/ )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(SfxObjectFactory, 0);
//STRIP001  sal_uInt16 nDemo = SFX_APP()->GetDemoKind();
//STRIP001
//STRIP001  SfxFilter* pFilter = new SfxFilter(
//STRIP001      rName, rWildcard, eType, lFormat, rMacType,
//STRIP001      rTypeName, nIconId, rMimeType, pImpl->pFilterContainer, rUserData );
//STRIP001 /*   if( nDemo != SFX_DEMOKIND_DEMO && nDemo != SFX_DEMOKIND_INVALID ||
//STRIP001      pFilter->IsOwnFormat() )*/
//STRIP001  // Jetzt immer uebernehmen, da es keine Demo mehr gibt. Sonst bei Ablauf
//STRIP001  // Absturz in sba
//STRIP001  pImpl->pFilterContainer->AddFilter(
//STRIP001      pFilter, pImpl->pFilterContainer->GetFilterCount() );
//STRIP001 /*   else
//STRIP001      delete pFilter;*/
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::DoInitFactory()
/*N*/ {
/*N*/   if(!pImpl->bInitFactoryCalled)
/*N*/   {
/*N*/       pImpl->bInitFactoryCalled = sal_True;
/*N*/       // FilterContainer Landen
/*N*/       GetFilterCount( );
/*N*/       (*pImpl->pInitFactory)();
/*N*/       String aShortName( String::CreateFromAscii( pShortName ) );
/*N*/       aShortName.ToLowerAscii();
/*N*/       if ( aShortName.EqualsAscii( "swriter" ) )
/*N*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SW );
/*N*/       else if ( aShortName.EqualsAscii( "swriter/web" ) )
/*N*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SWWEB );
/*N*/       else if ( aShortName.EqualsAscii( "swriter/globaldocument" ) )
/*N*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SWGLOB );
/*N*/       else if ( aShortName.EqualsAscii( "scalc" ) )
/*N*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SC );
/*N*/       else if ( aShortName.EqualsAscii( "simpress" ) )
/*N*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SI );
/*N*/       else if ( aShortName.EqualsAscii( "sdraw" ) )
/*N*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SD );
/*N*/       else if ( aShortName.EqualsAscii( "message" ) )
/*?*/           pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_MESSAGE );
/*N*/
/*N*/         // There are no filters for "dummy" factory!
/*N*/         if( pImpl->aServiceName.compareToAscii("dummy") != 0 )
/*N*/         {
/*N*/             DBG_ASSERT( pImpl->aServiceName.getLength(), "No service name - no filters!" )
/*N*/             SfxFilterContainer *pCont = GetFilterContainer();
/*N*/             pCont->ReadExternalFilters( pImpl->aServiceName );
/*N*/         }
/*N*/   }
/*N*/ }

/*N*/ IMPL_LINK_INLINE( SfxObjectFactory, InitFactoryHdl, void*, EMPTYARG,
/*N*/ {
/*N*/   SFX_APP()->Get_Impl()->aPendingInitFactories.Remove( this );
/*N*/   DoInitFactory();
/*N*/   return 0;
/*N*/ }
/*N*/ )

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
/*N*/
/*N*/   pImpl->aHelpFile = String::CreateFromAscii(pShortName);
/*N*/   pImpl->aHelpFile.Erase( 8 );
/*N*/   pImpl->aHelpPIFile = String(pImpl->aHelpFile,0,3);
/*N*/   pImpl->aHelpPIFile += DEFINE_CONST_UNICODE( "hlppi" );
/*N*/   pImpl->aHelpFile += DEFINE_CONST_UNICODE( ".hlp" );
/*N*/   pImpl->aHelpPIFile += DEFINE_CONST_UNICODE( ".hlp" );
/*N*/     pImpl->bOwnsAccel = sal_False;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxObjectFactory::SfxObjectFactory
/*N*/ (
/*N*/   const SvGlobalName&     rName,
/*N*/     const String&         rClassName,
/*N*/   CreateInstanceType      funcCIT
/*N*/ )
/*N*/ :   SvFactory( rName, rClassName, funcCIT ),
/*N*/   fnCreate( 0 ),
/*N*/   nId( 0 ),
/*N*/ //  pIniMgr( 0 ),
/*N*/   pShortName( 0 ),
/*N*/   pImpl( new SfxObjectFactory_Impl )
/*N*/ {
/*N*/   DBG_CTOR(SfxObjectFactory, 0);
/*N*/
/*N*/   SfxApplication* pApp = SFX_APP();
/*N*/     RegisterObjectFactory_Impl(*this);
/*N*/     pApp->InsertLateInitHdl( LINK( this, SfxObjectFactory, InitFactoryHdl ) );
/*N*/   pApp->Get_Impl()->aPendingInitFactories.Insert( this );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxObjectFactory::~SfxObjectFactory()
/*N*/ {
/*N*/   DBG_DTOR(SfxObjectFactory, 0);
/*N*/
/*N*/   const sal_uInt16 nCount = pImpl->aFilterArr.Count();
/*N*/   for ( sal_uInt16 i = 0; i < nCount; ++i )
/*?*/       delete pImpl->aFilterArr[i];
/*N*/   delete pImpl->pNameResId;
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

/*N*/ void SfxObjectFactory::RegisterViewFactory
/*N*/ (
/*N*/   SfxViewFactory &rFactory
/*N*/ )
/*N*/ {
/*N*/   sal_uInt16 nPos;
/*N*/   for ( nPos = 0;
/*N*/         nPos < pImpl->aViewFactoryArr.Count() &&
/*N*/         pImpl->aViewFactoryArr[nPos]->GetOrdinal() <= rFactory.GetOrdinal();
/*N*/         ++nPos )
/*N*/   /* empty loop */;
/*N*/   pImpl->aViewFactoryArr.Insert(nPos, &rFactory);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ sal_uInt16 SfxObjectFactory::GetViewFactoryCount() const
/*N*/ {
/*N*/   return pImpl->aViewFactoryArr.Count();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxViewFactory& SfxObjectFactory::GetViewFactory(sal_uInt16 i) const
/*N*/ {
/*N*/   return *pImpl->aViewFactoryArr[i];
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::RegisterMenuBar( const ResId& rId )
/*N*/ {
/*N*/   delete pImpl->pMenuBarResId;
/*N*/   pImpl->pMenuBarResId = new ResId( rId );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::RegisterPluginMenuBar( const ResId& rId )
/*N*/ {
/*N*/   delete pImpl->pPluginMenuBarResId;
/*N*/   pImpl->pPluginMenuBarResId = new ResId( rId );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const ResId* SfxObjectFactory::GetMenuBarId() const
/*N*/ {
/*N*/   return pImpl->pMenuBarResId;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ const ResId* SfxObjectFactory::GetPluginMenuBarId() const
/*?*/ {
/*?*/   return pImpl->pPluginMenuBarResId;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ const ResId* SfxObjectFactory::GetAccelId() const
/*N*/ {
/*N*/   return pImpl->pAccelResId;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::RegisterAccel( const ResId& rId )
/*N*/ {
/*N*/   DBG_ASSERT( !pImpl->pAccelResId, "SfxObjectFactory: double registration of Accel" );
/*N*/   pImpl->pAccelResId = new ResId(rId);
/*N*/ }

//--------------------------------------------------------------------

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::RegisterHelpFile( const String& rString )
/*N*/ {
/*N*/   pImpl->aHelpFile = rString;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 const String& SfxObjectFactory::GetHelpFile() const
//STRIP001 {
//STRIP001  return pImpl->aHelpFile;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ void SfxObjectFactory::RegisterHelpPIFile( const String& rString )
/*N*/ {
/*N*/   pImpl->aHelpPIFile = rString;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 const String& SfxObjectFactory::GetHelpPIFile() const
//STRIP001 {
//STRIP001  return pImpl->aHelpPIFile;
//STRIP001 }

/*N*/ SfxModule* SfxObjectFactory::GetModule() const
/*N*/ {
/*N*/   return pImpl->pModule;
/*N*/ }

/*N*/ SfxAcceleratorManager* SfxObjectFactory::GetAccMgr_Impl()
/*N*/ {
/*N*/   if ( !pImpl->pAccMgr && pImpl->pAccelResId )
/*N*/   {
/*N*/       // factories in the same module may share their accelerators
/*N*/       SfxApplication *pApp = SFX_APP();
/*N*/         SfxObjectFactoryArr_Impl& rArr = GetObjFacArray_Impl();
/*N*/       sal_uInt32 nCount = rArr.Count();
/*N*/       const ResId& rMyId = *GetAccelId();
/*N*/       for ( sal_uInt32 n=0; n<nCount; n++ )
/*N*/       {
/*N*/           SfxObjectFactory *pFact = rArr[(sal_uInt16)n];
/*N*/           if ( pFact == this )
/*N*/               break;
/*N*/           const ResId *pId = pFact->pImpl->pAccelResId;
/*N*/           if ( pId &&
/*N*/               pId->GetId() == rMyId.GetId() &&
/*N*/               pId->GetResMgr() == rMyId.GetResMgr() )
/*N*/           {
/*N*/               pImpl->pAccMgr = pFact->GetAccMgr_Impl();
/*N*/               return pImpl->pAccMgr;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // create accelerator manager
/*N*/         pImpl->pAccMgr = new SfxAcceleratorManager( rMyId, SFX_APP()->GetConfigManager_Impl() );
/*N*/       pImpl->bOwnsAccel = sal_True;
/*N*/   }
/*N*/
/*N*/   return pImpl->pAccMgr;
/*N*/ }

/*N*/ void SfxObjectFactory::SetModule_Impl( SfxModule *pMod )
/*N*/ {
/*N*/   pImpl->pModule = pMod;
/*N*/ }

/*N*/ void SfxObjectFactory::SetExplorerImageId( sal_uInt16 nImageId )
/*N*/ {
/*N*/   pImpl->nImageId = nImageId;
/*N*/ }

//STRIP001 sal_uInt16 SfxObjectFactory::GetExplorerImageId() const
//STRIP001 {
//STRIP001  return pImpl->nImageId;
//STRIP001 }

/*?*/ void SfxObjectFactory::SetStandardTemplate( const String& rFactoryURL, const String& rTemplate )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const SfxObjectFactory* pFactory = SfxObjectFactory::GetFactory( rFactoryURL );
//STRIP001  if ( pFactory )
//STRIP001  {
//STRIP001      ((SfxObjectFactory*)pFactory)->pImpl->aStandardTemplate = rTemplate;
//STRIP001      SvtModuleOptions aModOpt;
//STRIP001      SvtModuleOptions::EFactory eFac = SvtModuleOptions::E_WRITER;
//STRIP001      if ( SvtModuleOptions::ClassifyFactoryByName( pFactory->GetDocumentServiceName(), eFac ) )
//STRIP001          aModOpt.SetFactoryStandardTemplate( eFac, rTemplate );
//STRIP001  }
/*?*/ }

/*N*/ const String& SfxObjectFactory::GetStandardTemplate() const
/*N*/ {
/*N*/   if ( !pImpl->bTemplateInitialized )
/*N*/   {
/*N*/       pImpl->bTemplateInitialized = sal_True;
/*N*/       SvtModuleOptions aModOpt;
/*N*/       SvtModuleOptions::EFactory eFac = SvtModuleOptions::E_WRITER;
/*N*/       if ( SvtModuleOptions::ClassifyFactoryByName( GetDocumentServiceName(), eFac ) )
/*N*/           pImpl->aStandardTemplate = aModOpt.GetFactoryStandardTemplate( eFac );
/*N*/   }
/*N*/
/*N*/   return pImpl->aStandardTemplate;
/*N*/ }

/*?*/ const SfxObjectFactory* SfxObjectFactory::GetFactory( const String& rFactoryURL )
/*?*/ { // #dochnoetig# DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
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
/*N*/   SfxApplication *pApp = SFX_APP();
/*N*/
/*N*/   // "swriter4" durch "swriter" ersetzen, zum Vergleichen uppercase verwenden
/*N*/   WildCard aSearchedFac( aFact.EraseAllChars('4').ToUpperAscii() );
/*N*/     for( sal_uInt16 n = GetObjectFactoryCount_Impl(); !pFactory && n--; )
/*N*/   {
/*N*/         pFactory = &GetObjectFactory_Impl( n );
/*N*/       String aCompareTo = String::CreateFromAscii( pFactory->GetShortName() );
/*N*/       aCompareTo.ToUpperAscii();
/*N*/       if( !aSearchedFac.Matches( aCompareTo ) )
/*N*/           pFactory = 0;
/*N*/   }
/*N*/
/*N*/   return pFactory;
/*?*/ }

/*?*/ const SfxFilter* SfxObjectFactory::GetTemplateFilter() const
/*?*/ {DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  USHORT nFilterCount = pImpl->pFilterContainer->GetFilterCount();
//STRIP001  USHORT nVersion = 0;
//STRIP001  const SfxFilter *pFilter = NULL;
//STRIP001  for( int n=0; n<nFilterCount; n++)
//STRIP001  {
//STRIP001      const SfxFilter *pTemp = pImpl->pFilterContainer->GetFilter(n);
//STRIP001      if( pTemp && pTemp->IsOwnFormat() && pTemp->IsOwnTemplateFormat() && ( pTemp->GetVersion() > nVersion ) )
//STRIP001      {
//STRIP001          pFilter = pTemp;
//STRIP001          nVersion = pTemp->GetVersion();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pFilter;
/*?*/ }

/*N*/ void SfxObjectFactory::SetCreateNewSlotId( sal_uInt16 nId )
/*N*/ {
/*N*/   pImpl->nCreateNewSlotId = nId;
/*N*/ }

/*N*/ sal_uInt16 SfxObjectFactory::GetCreateNewSlotId() const
/*N*/ {
/*N*/   return pImpl->nCreateNewSlotId;
/*N*/ }

//STRIP001 void SfxObjectFactory::SetDocumentTypeNameResource( const ResId& rId )
//STRIP001 {
//STRIP001  DBG_ASSERT( !pImpl->pNameResId, "UI-Namensresource mehrfach gesetzt!" );
//STRIP001  pImpl->pNameResId = new ResId( rId );
//STRIP001 }

//STRIP001 String SfxObjectFactory::GetDocumentTypeName() const
//STRIP001 {
//STRIP001  ((SfxObjectFactory*)this)->DoInitFactory();
//STRIP001  if ( pImpl->pNameResId )
//STRIP001      return String( *pImpl->pNameResId );
//STRIP001  return String();
//STRIP001 }

/*N*/ void SfxObjectFactory::SetDocumentServiceName( const ::rtl::OUString& rServiceName )
/*N*/ {
/*N*/   pImpl->aServiceName = rServiceName;
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

/*?*/ sal_Bool SfxObjectFactory::HasObjectFactories()
/*?*/ {
/*?*/     return ( GetObjFacArray_Impl().Count() != 0 );
/*?*/ }

/*N*/ SfxObjectFactoryArr_Impl&   SfxObjectFactory::GetObjFacArray_Impl()
/*N*/ {
/*N*/     if ( !pObjFac )
/*N*/         pObjFac = new SfxObjectFactoryArr_Impl;
/*N*/     return *pObjFac;
/*N*/ }

/*?*/ String SfxObjectFactory::GetModuleName() const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SvtModuleOptions::EFactory eFac = SvtModuleOptions::E_WRITER;
//STRIP001     if ( SvtModuleOptions::ClassifyFactoryByName( GetDocumentServiceName(), eFac ) )
//STRIP001         return SvtModuleOptions().GetModuleName( eFac );
//STRIP001     else
/*?*/         return String();
/*?*/ }
