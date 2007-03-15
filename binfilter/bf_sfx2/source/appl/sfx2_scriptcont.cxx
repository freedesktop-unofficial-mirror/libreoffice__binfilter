/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_scriptcont.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:22:52 $
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

#ifndef _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif


#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif

#ifndef _SFX_NAMECONT_HXX
#include "namecont.hxx"
#endif

#ifndef _BASMGR_HXX
#include "bf_basic/basmgr.hxx"
#endif

#include "scriptcont.hxx"

#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#ifndef _RTL_DIGEST_H_
#include <rtl/digest.h>
#endif

// For password functionality


#include <svtools/sfxecode.hxx>
#include <svtools/ehdl.hxx>
#include "bf_basic/basmgr.hxx"
#include <xmlscript/xmlmod_imexp.hxx>
#include <app.hxx>
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
// Implementation class SfxScriptLibraryContainer

/*N*/ sal_Bool SfxScriptLibraryContainer::init
/*N*/ ( const ::rtl::OUString& aInitialisationParam,
/*N*/   const ::rtl::OUString& aScriptLanguage,
/*N*/   BasicManager* pBasMgr, SotStorage* pStor )
/*N*/ {
/*N*/     maScriptLanguage = aScriptLanguage;
/*N*/     mpBasMgr = pBasMgr;
/*N*/     return SfxLibraryContainer_Impl::init(
/*N*/         aInitialisationParam,
/*N*/       OUString ( RTL_CONSTASCII_USTRINGPARAM("script") ),
/*N*/       OUString ( RTL_CONSTASCII_USTRINGPARAM("script") ),
/*N*/       OUString ( RTL_CONSTASCII_USTRINGPARAM("xba") ),
/*N*/       OUString ( RTL_CONSTASCII_USTRINGPARAM("Basic") ),
/*N*/         pStor );
/*N*/ }

// OldBasicPassword interface
void SfxScriptLibraryContainer::setLibraryPassword(
    const String& rLibraryName, const String& rPassword )
{
    try
    {
        SfxLibrary_Impl* pImplLib = getImplLib( rLibraryName );
        if ( rPassword.Len() )
        {
            pImplLib->mbDoc50Password = sal_True;
            pImplLib->mbPasswordProtected = sal_True;
            pImplLib->maPassword = rPassword;
        }
    }
    catch( NoSuchElementException& ) {}
}

/*N*/ String SfxScriptLibraryContainer::getLibraryPassword( const String& rLibraryName )
/*N*/ {
/*N*/     SfxLibrary_Impl* pImplLib = getImplLib( rLibraryName );
/*N*/     String aPassword;
/*N*/     if( pImplLib->mbPasswordVerified )
/*?*/         aPassword = pImplLib->maPassword;
/*N*/     return aPassword;
/*N*/ }

/*?*/ void SfxScriptLibraryContainer::clearLibraryPassword( const String& rLibraryName )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*N*/ sal_Bool SfxScriptLibraryContainer::hasLibraryPassword( const String& rLibraryName )
/*N*/ {
/*N*/     SfxLibrary_Impl* pImplLib = getImplLib( rLibraryName );
/*N*/     return pImplLib->mbPasswordProtected;
/*N*/ }


// Ctor for service
/*N*/ SfxScriptLibraryContainer::SfxScriptLibraryContainer( void )
/*N*/ {
/*N*/     // all initialisation has to be done
/*N*/     // by calling XInitialization::initialize
/*N*/ }

/*N*/ SfxScriptLibraryContainer::   SfxScriptLibraryContainer
/*N*/   ( const ::rtl::OUString& aScriptLanguage, BasicManager* pBasMgr, SotStorage* pStor )
/*N*/ {
/*N*/     OUString aInitialisationParam;
/*N*/     init( aInitialisationParam, aScriptLanguage, pBasMgr, pStor );
/*N*/ }

// Methods to get library instances of the correct type
/*N*/ SfxLibrary_Impl* SfxScriptLibraryContainer::implCreateLibrary( void )
/*N*/ {
/*N*/   SfxLibrary_Impl* pRet = (SfxLibrary_Impl*) new SfxScriptLibrary( mxMSF, mxSFI );
/*N*/   return pRet;
/*N*/ }

/*N*/ SfxLibrary_Impl* SfxScriptLibraryContainer::implCreateLibraryLink
/*N*/   ( const OUString& aLibInfoFileURL, const OUString& StorageURL, sal_Bool ReadOnly )
/*N*/ {
/*N*/   SfxLibrary_Impl* pRet =
/*N*/       (SfxLibrary_Impl*) new SfxScriptLibrary
/*N*/             ( mxMSF, mxSFI, aLibInfoFileURL, StorageURL, ReadOnly );
/*N*/   return pRet;
/*N*/ }

/*N*/ Any SAL_CALL SfxScriptLibraryContainer::createEmptyLibraryElement( void )
/*N*/ {
/*N*/   OUString aMod;
/*N*/   Any aRetAny;
/*N*/   aRetAny <<= aMod;
/*N*/   return aRetAny;
/*N*/ }

/*?*/ sal_Bool SAL_CALL SfxScriptLibraryContainer::isLibraryElementValid( Any aElement )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }

/*?*/ void SAL_CALL SfxScriptLibraryContainer::writeLibraryElement
/*?*/ (
/*?*/   Any aElement,
/*?*/   const OUString& aElementName,
/*?*/   Reference< XOutputStream > xOutput
/*?*/ )
/*?*/   throw(Exception)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }


/*N*/ Any SAL_CALL SfxScriptLibraryContainer::importLibraryElement
/*N*/   ( const OUString& aFile, SotStorageStreamRef xElementStream )
/*N*/ {
/*N*/   Any aRetAny;
/*N*/
/*N*/   Reference< XParser > xParser( mxMSF->createInstance(
/*N*/       OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Parser") ) ), UNO_QUERY );
/*N*/   if( !xParser.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't create sax parser component\n" );
/*N*/       return aRetAny;
/*N*/   }
/*N*/
/*N*/
/*N*/   // Read from storage?
/*N*/   sal_Bool bStorage = xElementStream.Is();
/*N*/   Reference< XInputStream > xInput;
/*N*/
/*N*/   if( bStorage )
/*N*/   {
/*?*/       xInput = new ::utl::OInputStreamWrapper( *xElementStream );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       try
/*N*/       {
/*N*/           xInput = mxSFI->openFileRead( aFile );
/*N*/       }
/*N*/       catch( Exception& )
/*N*/       //catch( Exception& e )
/*N*/       {
/*N*/           // TODO:
/*N*/           //throw WrappedTargetException( e );
/*N*/       }
/*N*/   }
/*N*/   if( !xInput.is() )
/*N*/       return aRetAny;
/*N*/
/*N*/   InputSource source;
/*N*/   source.aInputStream = xInput;
/*N*/   source.sSystemId    = aFile;
/*N*/
/*N*/   // start parsing
/*N*/   xmlscript::ModuleDescriptor aMod;
/*N*/
/*N*/     try
/*N*/     {
/*N*/       xParser->setDocumentHandler( ::xmlscript::importScriptModule( aMod ) );
/*N*/       xParser->parseStream( source );
/*N*/     }
/*N*/     catch( Exception& )
/*N*/     {
/*N*/       SfxErrorContext aEc( ERRCTX_SFX_LOADBASIC, aFile );
/*N*/         ULONG nErrorCode = ERRCODE_IO_GENERAL;
/*N*/         ErrorHandler::HandleError( nErrorCode );
/*N*/     }
/*N*/
/*N*/   aRetAny <<= aMod.aCode;
/*N*/
/*N*/   // TODO: Check language
/*N*/   // aMod.aLanguage
/*N*/   // aMod.aName ignored
/*N*/
/*N*/   return aRetAny;
/*N*/ }


/*?*/ void SAL_CALL SfxScriptLibraryContainer::importFromOldStorage( const ::rtl::OUString& aFile )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }


// Storing with password encryption

// Methods XLibraryContainerPassword
sal_Bool SAL_CALL SfxScriptLibraryContainer::isLibraryPasswordProtected( const OUString& Name )
    throw (NoSuchElementException, RuntimeException)
{
    SfxLibrary_Impl* pImplLib = getImplLib( Name );
    sal_Bool bRet = pImplLib->mbPasswordProtected;
    return bRet;
}

sal_Bool SAL_CALL SfxScriptLibraryContainer::isLibraryPasswordVerified( const OUString& Name )
    throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
{
    SfxLibrary_Impl* pImplLib = getImplLib( Name );
    if( !pImplLib->mbPasswordProtected )
        throw IllegalArgumentException();
    sal_Bool bRet = pImplLib->mbPasswordVerified;
    return bRet;
}

/*?*/ sal_Bool SAL_CALL SfxScriptLibraryContainer::verifyLibraryPassword
/*?*/     ( const OUString& Name, const OUString& Password )
/*?*/         throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;
/*?*/ }

/*?*/ void SAL_CALL SfxScriptLibraryContainer::changeLibraryPassword( const OUString& Name,
/*?*/     const OUString& OldPassword, const OUString& NewPassword )
/*?*/         throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }




// Impl methods
/*?*/ sal_Bool SfxScriptLibraryContainer::implStorePasswordLibrary( SfxLibrary_Impl* pLib,
/*?*/     const ::rtl::OUString& aName, SotStorageRef xStorage )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ sal_Bool SfxScriptLibraryContainer::implLoadPasswordLibrary
/*?*/     ( SfxLibrary_Impl* pLib, const OUString& Name, sal_Bool bVerifyPasswordOnly )
/*?*/         throw(WrappedTargetException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }


//============================================================================
// Methods XInitialization
/*?*/ void SAL_CALL SfxScriptLibraryContainer::initialize( const Sequence< Any >& aArguments )
/*?*/     throw (::com::sun::star::uno::Exception,
/*?*/            ::com::sun::star::uno::RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }


//============================================================================
// Service
/*N*/ SFX_IMPL_SINGLEFACTORY( SfxScriptLibraryContainer )

/*N*/ Sequence< OUString > SfxScriptLibraryContainer::impl_getStaticSupportedServiceNames()
/*N*/ {
/*N*/     static Sequence< OUString > seqServiceNames( 1 );
/*N*/     static sal_Bool bNeedsInit = sal_True;
/*N*/
/*N*/   MutexGuard aGuard( Mutex::getGlobalMutex() );
/*N*/     if( bNeedsInit )
/*N*/     {
/*N*/         OUString* pSeq = seqServiceNames.getArray();
/*N*/         pSeq[0] = OUString::createFromAscii( "com.sun.star.script.ScriptLibraryContainer" );
/*N*/         bNeedsInit = sal_False;
/*N*/     }
/*N*/     return seqServiceNames;
/*N*/ }

/*N*/ OUString SfxScriptLibraryContainer::impl_getStaticImplementationName()
/*N*/ {
/*N*/     static OUString aImplName;
/*N*/     static sal_Bool bNeedsInit = sal_True;
/*N*/
/*N*/   MutexGuard aGuard( Mutex::getGlobalMutex() );
/*N*/     if( bNeedsInit )
/*N*/     {
/*N*/         aImplName = OUString::createFromAscii( "com.sun.star.comp.sfx2.ScriptLibraryContainer" );
/*N*/         bNeedsInit = sal_False;
/*N*/     }
/*N*/     return aImplName;
/*N*/ }

/*N*/ Reference< XInterface > SAL_CALL SfxScriptLibraryContainer::impl_createInstance
/*N*/     ( const Reference< XMultiServiceFactory >& xServiceManager )
/*N*/         throw( Exception )
/*N*/ {
/*N*/     Reference< XInterface > xRet =
/*N*/         static_cast< XInterface* >( static_cast< OWeakObject* >(new SfxScriptLibraryContainer()) );
/*N*/     return xRet;
/*N*/ }

//============================================================================
// Service for application library container
/*N*/ SFX_IMPL_ONEINSTANCEFACTORY( SfxApplicationScriptLibraryContainer )

/*N*/ Sequence< OUString > SfxApplicationScriptLibraryContainer::impl_getStaticSupportedServiceNames()
/*N*/ {
/*N*/     static Sequence< OUString > seqServiceNames( 1 );
/*N*/     static sal_Bool bNeedsInit = sal_True;
/*N*/
/*N*/   MutexGuard aGuard( Mutex::getGlobalMutex() );
/*N*/     if( bNeedsInit )
/*N*/     {
/*N*/         OUString* pSeq = seqServiceNames.getArray();
/*N*/         pSeq[0] = OUString::createFromAscii( "com.sun.star.script.ApplicationScriptLibraryContainer" );
/*N*/         bNeedsInit = sal_False;
/*N*/     }
/*N*/     return seqServiceNames;
/*N*/ }

/*N*/ OUString SfxApplicationScriptLibraryContainer::impl_getStaticImplementationName()
/*N*/ {
/*N*/     static OUString aImplName;
/*N*/     static sal_Bool bNeedsInit = sal_True;
/*N*/
/*N*/   MutexGuard aGuard( Mutex::getGlobalMutex() );
/*N*/     if( bNeedsInit )
/*N*/     {
/*N*/         aImplName = OUString::createFromAscii( "com.sun.star.comp.sfx2.ApplicationScriptLibraryContainer" );
/*N*/         bNeedsInit = sal_False;
/*N*/     }
/*N*/     return aImplName;
/*N*/ }

/*N*/ Reference< XInterface > SAL_CALL SfxApplicationScriptLibraryContainer::impl_createInstance
/*N*/     ( const Reference< XMultiServiceFactory >& xServiceManager )
/*N*/         throw( Exception )
/*N*/ {
/*N*/   SFX_APP()->GetBasicManager();
/*N*/     Reference< XInterface > xRet =
/*N*/         Reference< XInterface >( SFX_APP()->GetBasicContainer(), UNO_QUERY );
/*N*/     return xRet;
/*N*/ }


//============================================================================

/*N*/ void SAL_CALL SfxScriptLibraryContainer::storeLibraries( sal_Bool bComplete )
/*N*/ {
/*N*/   SfxLibraryContainer_Impl::storeLibraries( bComplete );
/*N*/ }

/*N*/ void SAL_CALL SfxScriptLibraryContainer::storeLibrariesToStorage( SotStorageRef xStorage )
/*N*/ {
/*N*/   SfxLibraryContainer_Impl::storeLibrariesToStorage( xStorage );
/*N*/ }


//============================================================================
// Implementation class SfxScriptLibrary

// Ctor
/*N*/ SfxScriptLibrary::SfxScriptLibrary( Reference< XMultiServiceFactory > xMSF,
/*N*/                                     Reference< XSimpleFileAccess > xSFI )
/*N*/   : SfxLibrary_Impl( getCppuType( (const OUString *)0 ), xMSF, xSFI )
/*N*/     , mbLoadedSource( sal_False )
/*N*/     , mbLoadedBinary( sal_False )
/*N*/ {
/*N*/ }

/*N*/ SfxScriptLibrary::SfxScriptLibrary( Reference< XMultiServiceFactory > xMSF,
/*N*/                                     Reference< XSimpleFileAccess > xSFI,
/*N*/                                     const OUString& aLibInfoFileURL,
/*N*/                                     const OUString& aStorageURL,
/*N*/                                     sal_Bool ReadOnly )
/*N*/   : SfxLibrary_Impl( getCppuType( (const OUString *)0 ), xMSF, xSFI,
/*N*/                       aLibInfoFileURL, aStorageURL, ReadOnly)
/*N*/     , mbLoadedSource( sal_False )
/*N*/     , mbLoadedBinary( sal_False )
/*N*/ {
/*N*/ }

//============================================================================
}
