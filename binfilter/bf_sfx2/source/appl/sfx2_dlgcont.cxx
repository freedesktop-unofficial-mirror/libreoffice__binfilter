/*************************************************************************
 *
 *  $RCSfile: sfx2_dlgcont.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:06 $
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

#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_INPUTSOURCE_HPP_
#include <com/sun/star/xml/sax/InputSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XSIMPLEFILEACCESS_HPP_
#include <com/sun/star/ucb/XSimpleFileAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif


#include "dlgcont.hxx"

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#include <svtools/pathoptions.hxx>
#include <xmlscript/xmldlg_imexp.hxx>
#include <app.hxx>

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star::container;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::script;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star;
using namespace cppu;
using namespace rtl;
using namespace osl;


//============================================================================
// Implementation class SfxDialogLibraryContainer

/*N*/ sal_Bool SfxDialogLibraryContainer::init
/*N*/     ( const ::rtl::OUString& aInitialisationParam, SotStorage* pStor )
/*N*/ {
/*N*/     return SfxLibraryContainer_Impl::init(
/*N*/           aInitialisationParam,
/*N*/           OUString ( RTL_CONSTASCII_USTRINGPARAM("dialog") ),
/*N*/         OUString ( RTL_CONSTASCII_USTRINGPARAM("dialogs") ),
/*N*/         OUString ( RTL_CONSTASCII_USTRINGPARAM("xdl") ),
/*N*/         OUString ( RTL_CONSTASCII_USTRINGPARAM("Dialogs") ),
/*N*/           pStor );
/*N*/ }

// Ctor for service
//STRIP001 SfxDialogLibraryContainer::SfxDialogLibraryContainer( void )
//STRIP001 {
//STRIP001     // all initialisation has to be done
//STRIP001     // by calling XInitialization::initialize
//STRIP001 }

/*N*/ SfxDialogLibraryContainer::SfxDialogLibraryContainer( SotStorage* pStor )
/*N*/ {
/*N*/     OUString aInitialisationParam;
/*N*/     init( aInitialisationParam, pStor );
/*N*/ }

// Methods to get library instances of the correct type
/*N*/ SfxLibrary_Impl* SfxDialogLibraryContainer::implCreateLibrary( void )
/*N*/ {
/*N*/   SfxLibrary_Impl* pRet = (SfxLibrary_Impl*) new SfxDialogLibrary( mxMSF, mxSFI );
/*N*/   return pRet;
/*N*/ }

/*N*/ SfxLibrary_Impl* SfxDialogLibraryContainer::implCreateLibraryLink
/*N*/   ( const OUString& aLibInfoFileURL, const OUString& StorageURL, sal_Bool ReadOnly )
/*N*/ {
/*N*/   SfxLibrary_Impl* pRet =
/*N*/       (SfxLibrary_Impl*) new SfxDialogLibrary
/*N*/             ( mxMSF, mxSFI, aLibInfoFileURL, StorageURL, ReadOnly );
/*N*/   return pRet;
/*N*/ }

/*N*/ Any SAL_CALL SfxDialogLibraryContainer::createEmptyLibraryElement( void )
/*N*/ {
/*N*/   Reference< XInputStreamProvider > xISP;
/*N*/   Any aRetAny;
/*N*/   aRetAny <<= xISP;
/*N*/   return aRetAny;
/*N*/ }

/*?*/ sal_Bool SAL_CALL SfxDialogLibraryContainer::isLibraryElementValid( Any aElement )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  Reference< XInputStreamProvider > xISP;
//STRIP001  aElement >>= xISP;
//STRIP001  sal_Bool bRet = xISP.is();
//STRIP001  return bRet;
/*?*/ }

/*?*/ void SAL_CALL SfxDialogLibraryContainer::writeLibraryElement
/*?*/ (
/*?*/   Any aElement,
/*?*/   const OUString& aElementName,
/*?*/   Reference< XOutputStream > xOutput
/*?*/ )
/*?*/   throw(Exception)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  Reference< XInputStreamProvider > xISP;
//STRIP001  aElement >>= xISP;
//STRIP001  if( !xISP.is() )
//STRIP001      return;
//STRIP001
//STRIP001  Reference< XInputStream > xInput( xISP->createInputStream() );
//STRIP001  Sequence< sal_Int8 > bytes;
//STRIP001  sal_Int32 nRead = xInput->readBytes( bytes, xInput->available() );
//STRIP001  for (;;)
//STRIP001  {
//STRIP001      if( nRead )
//STRIP001          xOutput->writeBytes( bytes );
//STRIP001
//STRIP001      nRead = xInput->readBytes( bytes, 1024 );
//STRIP001      if (! nRead)
//STRIP001          break;
//STRIP001  }
//STRIP001  xInput->closeInput();
/*?*/ }


/*?*/ Any SAL_CALL SfxDialogLibraryContainer::importLibraryElement
/*?*/   ( const OUString& aFile, SotStorageStreamRef xElementStream )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); Any aAny; return aAny;//STRIP001
//STRIP001  Any aRetAny;
//STRIP001
//STRIP001  // TODO: Member because later it will be a component
//STRIP001  Reference< XMultiServiceFactory > xMSF( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001  if( !xMSF.is() )
//STRIP001  {
//STRIP001      OSL_ENSURE( 0, "### couln't get ProcessServiceFactory\n" );
//STRIP001      return aRetAny;
//STRIP001  }
//STRIP001
//STRIP001  Reference< XParser > xParser( xMSF->createInstance(
//STRIP001      OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Parser") ) ), UNO_QUERY );
//STRIP001  if( !xParser.is() )
//STRIP001  {
//STRIP001      OSL_ENSURE( 0, "### couln't create sax parser component\n" );
//STRIP001      return aRetAny;
//STRIP001  }
//STRIP001
//STRIP001  Reference< XNameContainer > xDialogModel( xMSF->createInstance
//STRIP001      ( OUString(RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.awt.UnoControlDialogModel" ) ) ), UNO_QUERY );
//STRIP001  if( !xDialogModel.is() )
//STRIP001  {
//STRIP001      OSL_ENSURE( 0, "### couln't create com.sun.star.awt.UnoControlDialogModel component\n" );
//STRIP001      return aRetAny;
//STRIP001  }
//STRIP001
//STRIP001  // Read from storage?
//STRIP001  sal_Bool bStorage = xElementStream.Is();
//STRIP001  Reference< XInputStream > xInput;
//STRIP001
//STRIP001  if( bStorage )
//STRIP001  {
//STRIP001      xInput = new utl::OInputStreamWrapper( *xElementStream );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          xInput = mxSFI->openFileRead( aFile );
//STRIP001      }
//STRIP001      catch( Exception& )
//STRIP001      //catch( Exception& e )
//STRIP001      {
//STRIP001          // TODO:
//STRIP001          //throw WrappedTargetException( e );
//STRIP001      }
//STRIP001  }
//STRIP001  if( !xInput.is() )
//STRIP001      return aRetAny;
//STRIP001
//STRIP001     Reference< XComponentContext > xContext;
//STRIP001     Reference< beans::XPropertySet > xProps( xMSF, UNO_QUERY );
//STRIP001     OSL_ASSERT( xProps.is() );
//STRIP001     OSL_VERIFY( xProps->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DefaultContext")) ) >>= xContext );
//STRIP001
//STRIP001  InputSource source;
//STRIP001  source.aInputStream = xInput;
//STRIP001  source.sSystemId    = aFile;
//STRIP001
//STRIP001  // start parsing
//STRIP001  xParser->setDocumentHandler( ::xmlscript::importDialogModel( xDialogModel, xContext ) );
//STRIP001  xParser->parseStream( source );
//STRIP001
//STRIP001  // Create InputStream, TODO: Implement own InputStreamProvider
//STRIP001  // to avoid creating the DialogModel here!
//STRIP001  Reference< XInputStreamProvider > xISP = ::xmlscript::exportDialogModel( xDialogModel, xContext );
//STRIP001  aRetAny <<= xISP;
//STRIP001  return aRetAny;
/*?*/ }

/*?*/ void SAL_CALL SfxDialogLibraryContainer::importFromOldStorage( const ::rtl::OUString& aFile )
/*?*/ {
/*?*/     // Nothing to do here, old dialogs cannot be imported
/*?*/ }

//STRIP001 SfxLibraryContainer_Impl* SfxDialogLibraryContainer::createInstanceImpl( void )
//STRIP001 {
//STRIP001     return new SfxDialogLibraryContainer();
//STRIP001 }


//============================================================================
// Methods XInitialization
/*?*/ void SAL_CALL SfxDialogLibraryContainer::initialize( const Sequence< Any >& aArguments )
/*?*/     throw (::com::sun::star::uno::Exception,
/*?*/            ::com::sun::star::uno::RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  sal_Int32 nArgCount = aArguments.getLength();
//STRIP001  OSL_ENSURE( nArgCount, "SfxDialogLibraryContainer::initialize() called with no arguments\n" );
//STRIP001
//STRIP001     OUString aInitialisationParam;
//STRIP001     if( nArgCount )
//STRIP001     {
//STRIP001         const Any* pArgs = aArguments.getConstArray();
//STRIP001         pArgs[0] >>= aInitialisationParam;
//STRIP001      OSL_ENSURE( aInitialisationParam.getLength(),
//STRIP001             "SfxDialogLibraryContainer::initialize() called with empty url\n" );
//STRIP001     }
//STRIP001
//STRIP001     init( aInitialisationParam );
/*?*/ }


//============================================================================
// Service
/*N*/ SFX_IMPL_SINGLEFACTORY( SfxDialogLibraryContainer )

/*?*/ Sequence< OUString > SfxDialogLibraryContainer::impl_getStaticSupportedServiceNames()
/*?*/ {DBG_BF_ASSERT(0, "STRIP");Sequence< OUString > seqServiceNames;return seqServiceNames; //STRIP001
//STRIP001     static Sequence< OUString > seqServiceNames( 1 );
//STRIP001     static sal_Bool bNeedsInit = sal_True;
//STRIP001
//STRIP001  MutexGuard aGuard( Mutex::getGlobalMutex() );
//STRIP001     if( bNeedsInit )
//STRIP001     {
//STRIP001         OUString* pSeq = seqServiceNames.getArray();
//STRIP001         pSeq[0] = OUString::createFromAscii( "com.sun.star.script.DialogLibraryContainer" );
//STRIP001         bNeedsInit = sal_False;
//STRIP001     }
//STRIP001     return seqServiceNames;
/*?*/ }

/*N*/ OUString SfxDialogLibraryContainer::impl_getStaticImplementationName()
/*N*/ {
/*N*/     static OUString aImplName;
/*N*/     static sal_Bool bNeedsInit = sal_True;
/*N*/
/*N*/   MutexGuard aGuard( Mutex::getGlobalMutex() );
/*N*/     if( bNeedsInit )
/*N*/     {
/*N*/         aImplName = OUString::createFromAscii( "com.sun.star.comp.sfx2.DialogLibraryContainer" );
/*N*/         bNeedsInit = sal_False;
/*N*/     }
/*N*/     return aImplName;
/*N*/ }

/*N*/ Reference< XInterface > SAL_CALL SfxDialogLibraryContainer::impl_createInstance
/*N*/     ( const Reference< XMultiServiceFactory >& xServiceManager )
/*N*/         throw( Exception )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001     Reference< XInterface > xRet =
//STRIP001         static_cast< XInterface* >( static_cast< OWeakObject* >(new SfxDialogLibraryContainer()) );
//STRIP001     return xRet;
/*N*/ }


//============================================================================
// Service for application library container
/*N*/ SFX_IMPL_ONEINSTANCEFACTORY( SfxApplicationDialogLibraryContainer )

/*N*/ Sequence< OUString > SfxApplicationDialogLibraryContainer::impl_getStaticSupportedServiceNames()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/     static Sequence< OUString > seqServiceNames( 1 );
//STRIP001     static sal_Bool bNeedsInit = sal_True;
//STRIP001
//STRIP001  MutexGuard aGuard( Mutex::getGlobalMutex() );
//STRIP001     if( bNeedsInit )
//STRIP001     {
//STRIP001         OUString* pSeq = seqServiceNames.getArray();
//STRIP001         pSeq[0] = OUString::createFromAscii( "com.sun.star.script.ApplicationDialogLibraryContainer" );
//STRIP001         bNeedsInit = sal_False;
//STRIP001     }
/*N*/     return seqServiceNames;
/*N*/ }

/*N*/ OUString SfxApplicationDialogLibraryContainer::impl_getStaticImplementationName()
/*N*/ {
/*N*/     static OUString aImplName;
/*N*/     static sal_Bool bNeedsInit = sal_True;
/*N*/
/*N*/   MutexGuard aGuard( Mutex::getGlobalMutex() );
/*N*/     if( bNeedsInit )
/*N*/     {
/*N*/         aImplName = OUString::createFromAscii( "com.sun.star.comp.sfx2.ApplicationDialogLibraryContainer" );
/*N*/         bNeedsInit = sal_False;
/*N*/     }
/*N*/     return aImplName;
/*N*/ }

/*N*/ Reference< XInterface > SAL_CALL SfxApplicationDialogLibraryContainer::impl_createInstance
/*N*/     ( const Reference< XMultiServiceFactory >& xServiceManager )
/*N*/         throw( Exception )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  SFX_APP()->GetBasicManager();
//STRIP001     Reference< XInterface > xRet =
//STRIP001         Reference< XInterface >( SFX_APP()->GetDialogContainer(), UNO_QUERY );
//STRIP001     return xRet;
/*N*/ }


//============================================================================
// Implementation class SfxDialogLibrary

// Ctor
/*N*/ SfxDialogLibrary::SfxDialogLibrary( Reference< XMultiServiceFactory > xMSF,
/*N*/                                     Reference< XSimpleFileAccess > xSFI )
/*N*/   : SfxLibrary_Impl( getCppuType( (const Reference< XInputStreamProvider > *)0 ), xMSF, xSFI )
/*N*/ {
/*N*/ }

/*N*/ SfxDialogLibrary::SfxDialogLibrary( Reference< XMultiServiceFactory > xMSF,
/*N*/                                     Reference< XSimpleFileAccess > xSFI,
/*N*/                                     const OUString& aLibInfoFileURL,
/*N*/                                     const OUString& aStorageURL,
/*N*/                                     sal_Bool ReadOnly )
/*N*/   : SfxLibrary_Impl( getCppuType( (const Reference< XInputStreamProvider > *)0 ),
/*N*/                        xMSF, xSFI, aLibInfoFileURL, aStorageURL, ReadOnly)
/*N*/ {
/*N*/ }

//============================================================================

}
