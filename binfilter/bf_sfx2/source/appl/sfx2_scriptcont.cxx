/*************************************************************************
 *
 *  $RCSfile: sfx2_scriptcont.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:07 $
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
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XSIMPLEFILEACCESS_HPP_
#include <com/sun/star/ucb/XSimpleFileAccess.hpp>
#endif

#include <com/sun/star/script/XStarBasicAccess.hpp>
#include <com/sun/star/script/XStarBasicModuleInfo.hpp>
#include <com/sun/star/script/XStarBasicLibraryInfo.hpp>


#include "scriptcont.hxx"

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _RTL_DIGEST_H_
#include <rtl/digest.h>
#endif

// For password functionality
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif


#include <svtools/pathoptions.hxx>
#include <svtools/sfxecode.hxx>
#include <svtools/ehdl.hxx>
#include <basic/basmgr.hxx>
#include <basic/sbmod.hxx>
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
/*?*/ void SfxScriptLibraryContainer::setLibraryPassword
/*?*/     ( const String& rLibraryName, const String& rPassword )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     try
//STRIP001     {
//STRIP001         SfxLibrary_Impl* pImplLib = getImplLib( rLibraryName );
//STRIP001         if( rPassword.Len() )
//STRIP001         {
//STRIP001          pImplLib->mbDoc50Password = sal_True;
//STRIP001             pImplLib->mbPasswordProtected = sal_True;
//STRIP001             pImplLib->maPassword = rPassword;
//STRIP001         }
//STRIP001     }
//STRIP001     catch( NoSuchElementException& ) {}
/*?*/ }

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
//STRIP001     try
//STRIP001     {
//STRIP001         SfxLibrary_Impl* pImplLib = getImplLib( rLibraryName );
//STRIP001      pImplLib->mbDoc50Password = sal_False;
//STRIP001         pImplLib->mbPasswordProtected = sal_False;
//STRIP001         pImplLib->maPassword = OUString();
//STRIP001     }
//STRIP001     catch( NoSuchElementException& ) {}
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
//STRIP001  OUString aMod;
//STRIP001  aElement >>= aMod;
//STRIP001  sal_Bool bRet = (aMod.getLength() > 0);
//STRIP001  return bRet;
/*?*/ }

/*?*/ void SAL_CALL SfxScriptLibraryContainer::writeLibraryElement
/*?*/ (
/*?*/   Any aElement,
/*?*/   const OUString& aElementName,
/*?*/   Reference< XOutputStream > xOutput
/*?*/ )
/*?*/   throw(Exception)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // Create sax writer
//STRIP001  Reference< XExtendedDocumentHandler > xHandler(
//STRIP001      mxMSF->createInstance(
//STRIP001          OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer") ) ), UNO_QUERY );
//STRIP001  if( !xHandler.is() )
//STRIP001  {
//STRIP001      OSL_ENSURE( 0, "### couln't create sax-writer component\n" );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  Reference< XActiveDataSource > xSource( xHandler, UNO_QUERY );
//STRIP001  xSource->setOutputStream( xOutput );
//STRIP001
//STRIP001  xmlscript::ModuleDescriptor aMod;
//STRIP001  aMod.aName = aElementName;
//STRIP001  aMod.aLanguage = maScriptLanguage;
//STRIP001  aElement >>= aMod.aCode;
//STRIP001  xmlscript::exportScriptModule( xHandler, aMod );
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

//STRIP001 SfxLibraryContainer_Impl* SfxScriptLibraryContainer::createInstanceImpl( void )
//STRIP001 {
//STRIP001     return new SfxScriptLibraryContainer();
//STRIP001 }

/*?*/ void SAL_CALL SfxScriptLibraryContainer::importFromOldStorage( const ::rtl::OUString& aFile )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SotStorageRef xStorage = new SotStorage( sal_False, aFile );
//STRIP001  if( xStorage.Is() && xStorage->GetError() == ERRCODE_NONE )
//STRIP001     {
//STRIP001         // We need a BasicManager to avoid problems
//STRIP001         // StarBASIC* pBas = new StarBASIC();
//STRIP001         BasicManager* pBasicManager = new BasicManager( *(SotStorage*)xStorage );
//STRIP001
//STRIP001         // Set info
//STRIP001         Reference< XLibraryContainer > xBasicCont =
//STRIP001             static_cast< XLibraryContainer* >( this );
//STRIP001         Reference< XLibraryContainer > xDialogCont;
//STRIP001      LibraryContainerInfo* pInfo = new LibraryContainerInfo
//STRIP001             ( xBasicCont, xDialogCont, static_cast< OldBasicPassword* >( this ) );
//STRIP001      pBasicManager->SetLibraryContainerInfo( pInfo );
//STRIP001
//STRIP001         // Now the libraries should be copied to this SfxScriptLibraryContainer
//STRIP001         delete pBasicManager;
//STRIP001     }
/*?*/ }


// Storing with password encryption

// Methods XLibraryContainerPassword
/*?*/ sal_Bool SAL_CALL SfxScriptLibraryContainer::isLibraryPasswordProtected( const OUString& Name )
/*?*/     throw (NoSuchElementException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001  sal_Bool bRet = pImplLib->mbPasswordProtected;
//STRIP001  return bRet;
/*?*/ }

/*?*/ sal_Bool SAL_CALL SfxScriptLibraryContainer::isLibraryPasswordVerified( const OUString& Name )
/*?*/     throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001  if( !pImplLib->mbPasswordProtected )
//STRIP001      throw IllegalArgumentException();
//STRIP001  sal_Bool bRet = pImplLib->mbPasswordVerified;
//STRIP001  return bRet;
/*?*/ }

/*?*/ sal_Bool SAL_CALL SfxScriptLibraryContainer::verifyLibraryPassword
/*?*/     ( const OUString& Name, const OUString& Password )
/*?*/         throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001  if( !pImplLib->mbPasswordProtected || pImplLib->mbPasswordVerified )
//STRIP001      throw IllegalArgumentException();
//STRIP001
//STRIP001     // Test password
//STRIP001     sal_Bool bSuccess = sal_False;
//STRIP001     if( pImplLib->mbDoc50Password )
//STRIP001     {
//STRIP001         bSuccess = ( Password == pImplLib->maPassword );
//STRIP001         if( bSuccess )
//STRIP001             pImplLib->mbPasswordVerified = sal_True;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pImplLib->maPassword = Password;
//STRIP001         bSuccess = implLoadPasswordLibrary( pImplLib, Name, sal_True );
//STRIP001         if( bSuccess )
//STRIP001         {
//STRIP001             // The library gets modified by verifiying the password, because other-
//STRIP001             // wise for saving the storage would be copied and that doesn't work
//STRIP001             // with mtg's storages when the password is verified
//STRIP001             pImplLib->mbModified = sal_True;
//STRIP001             pImplLib->mbPasswordVerified = sal_True;
//STRIP001
//STRIP001             // Reload library to get source
//STRIP001             if( pImplLib->mbLoaded )
//STRIP001                 implLoadPasswordLibrary( pImplLib, Name );
//STRIP001         }
//STRIP001     }
//STRIP001  return bSuccess;
/*?*/ }

/*?*/ void SAL_CALL SfxScriptLibraryContainer::changeLibraryPassword( const OUString& Name,
/*?*/     const OUString& OldPassword, const OUString& NewPassword )
/*?*/         throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001     if( OldPassword == NewPassword )
//STRIP001         return;
//STRIP001
//STRIP001     sal_Bool bOldPassword = ( OldPassword.getLength() > 0 );
//STRIP001     sal_Bool bNewPassword = ( NewPassword.getLength() > 0 );
//STRIP001  sal_Bool bStorage = mxStorage.Is() && !pImplLib->mbLink;
//STRIP001
//STRIP001     if( pImplLib->mbReadOnly || (bOldPassword && !pImplLib->mbPasswordProtected) )
//STRIP001      throw IllegalArgumentException();
//STRIP001
//STRIP001     // Library must be loaded
//STRIP001  loadLibrary( Name );
//STRIP001
//STRIP001     sal_Bool bKillCryptedFiles = sal_False;
//STRIP001     sal_Bool bKillUncryptedFiles = sal_False;
//STRIP001
//STRIP001     // Remove or change password?
//STRIP001     if( bOldPassword )
//STRIP001     {
//STRIP001         if( isLibraryPasswordVerified( Name ) )
//STRIP001         {
//STRIP001             if( pImplLib->maPassword != OldPassword )
//STRIP001                  throw IllegalArgumentException();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             if( !verifyLibraryPassword( Name, OldPassword ) )
//STRIP001                  throw IllegalArgumentException();
//STRIP001
//STRIP001             // Reload library to get source
//STRIP001             // Should be done in verifyLibraryPassword loadLibrary( Name );
//STRIP001         }
//STRIP001
//STRIP001         if( !bNewPassword )
//STRIP001         {
//STRIP001             pImplLib->mbPasswordProtected = sal_False;
//STRIP001             pImplLib->mbPasswordVerified = sal_False;
//STRIP001             pImplLib->maPassword = OUString();
//STRIP001
//STRIP001          mbModified = sal_True;
//STRIP001             pImplLib->mbModified = sal_True;
//STRIP001
//STRIP001             if( !bStorage && !pImplLib->mbDoc50Password )
//STRIP001             {
//STRIP001                 // Store application basic uncrypted
//STRIP001                 SotStorageRef xStorage;
//STRIP001                 storeLibraries_Impl( xStorage, sal_False );
//STRIP001                 bKillCryptedFiles = sal_True;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // Set new password?
//STRIP001     if( bNewPassword )
//STRIP001     {
//STRIP001         pImplLib->mbPasswordProtected = sal_True;
//STRIP001         pImplLib->mbPasswordVerified = sal_True;
//STRIP001         pImplLib->maPassword = NewPassword;
//STRIP001
//STRIP001      mbModified = sal_True;
//STRIP001         pImplLib->mbModified = sal_True;
//STRIP001
//STRIP001         if( !bStorage && !pImplLib->mbDoc50Password )
//STRIP001         {
//STRIP001             // Store applictaion basic crypted
//STRIP001             SotStorageRef xStorage;
//STRIP001             storeLibraries_Impl( xStorage, sal_False );
//STRIP001             bKillUncryptedFiles = sal_True;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if( bKillCryptedFiles || bKillUncryptedFiles )
//STRIP001     {
//STRIP001      Sequence< OUString > aElementNames = pImplLib->getElementNames();
//STRIP001      sal_Int32 nNameCount = aElementNames.getLength();
//STRIP001      const OUString* pNames = aElementNames.getConstArray();
//STRIP001         OUString aLibDirPath = createAppLibraryFolder( pImplLib, Name );
//STRIP001      try
//STRIP001      {
//STRIP001          for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001          {
//STRIP001              OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001              INetURLObject aElementInetObj( aLibDirPath );
//STRIP001              aElementInetObj.insertName( aElementName, sal_False,
//STRIP001                  INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001                 if( bKillUncryptedFiles )
//STRIP001                  aElementInetObj.setExtension( maLibElementFileExtension );
//STRIP001                 else
//STRIP001                  aElementInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("pba") ) );
//STRIP001              String aElementPath( aElementInetObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001
//STRIP001              if( mxSFI->exists( aElementPath ) )
//STRIP001                  mxSFI->kill( aElementPath );
//STRIP001          }
//STRIP001      }
//STRIP001         catch( Exception& ) {}
//STRIP001     }
/*?*/ }


//STRIP001 void setStreamKey( SotStorageStreamRef xStream, const ByteString& rKey )
//STRIP001 {
//STRIP001     ByteString aKey( rKey );
//STRIP001     sal_uInt8 aBuffer[RTL_DIGEST_LENGTH_SHA1];
//STRIP001     rtlDigestError nError = rtl_digest_SHA1( aKey.GetBuffer(), aKey.Len(), aBuffer, RTL_DIGEST_LENGTH_SHA1 );
//STRIP001     if ( nError == rtl_Digest_E_None )
//STRIP001     {
//STRIP001         sal_uInt8* pBuffer = aBuffer;
//STRIP001         ::com::sun::star::uno::Sequence < sal_Int8 > aSequ( (sal_Int8*) pBuffer, RTL_DIGEST_LENGTH_SHA1 );
//STRIP001         ::com::sun::star::uno::Any aAny;
//STRIP001         aAny <<= aSequ;
//STRIP001         xStream->SetProperty( ::rtl::OUString::createFromAscii("EncryptionKey"), aAny );
//STRIP001     }
//STRIP001 }


// Impl methods
/*?*/ sal_Bool SfxScriptLibraryContainer::implStorePasswordLibrary( SfxLibrary_Impl* pLib,
/*?*/     const ::rtl::OUString& aName, SotStorageRef xStorage )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     BasicManager* pBasicMgr = getBasicManager();
//STRIP001     StarBASIC* pBasicLib = pBasicMgr->GetLib( aName );
//STRIP001     if( !pBasicLib )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  Sequence< OUString > aElementNames = pLib->getElementNames();
//STRIP001  sal_Int32 nNameCount = aElementNames.getLength();
//STRIP001  const OUString* pNames = aElementNames.getConstArray();
//STRIP001
//STRIP001  sal_Bool bLink = pLib->mbLink;
//STRIP001  sal_Bool bStorage = xStorage.Is() && !bLink;
//STRIP001  if( bStorage )
//STRIP001  {
//STRIP001      for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001      {
//STRIP001          OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001             // Write binary image stream
//STRIP001          SbModule* pMod = pBasicLib->FindModule( aElementName );
//STRIP001          if( pMod )
//STRIP001             {
//STRIP001              //OUString aCodeStreamName( RTL_CONSTASCII_USTRINGPARAM("code.bin") );
//STRIP001              OUString aCodeStreamName = aElementName;
//STRIP001              aCodeStreamName += String( RTL_CONSTASCII_USTRINGPARAM(".bin") );
//STRIP001
//STRIP001                 SotStorageStreamRef xCodeStream = xStorage->OpenSotStream
//STRIP001                     ( aCodeStreamName, STREAM_WRITE | STREAM_SHARE_DENYWRITE | STREAM_TRUNC );
//STRIP001
//STRIP001              if( xCodeStream->GetError() == ERRCODE_NONE )
//STRIP001              {
//STRIP001                     SvMemoryStream aMemStream;
//STRIP001                     BOOL bStore = pMod->StoreBinaryData( aMemStream );
//STRIP001
//STRIP001                     // TODO? Store Id to check password?
//STRIP001
//STRIP001                     sal_Int32 nSize = (sal_Int32)aMemStream.Tell();
//STRIP001                     Sequence< sal_Int8 > aBinSeq( nSize );
//STRIP001                     sal_Int8* pData = aBinSeq.getArray();
//STRIP001                  ::rtl_copyMemory( pData, aMemStream.GetData(), nSize );
//STRIP001
//STRIP001                     Reference< XOutputStream > xOut = new utl::OOutputStreamWrapper( *xCodeStream );
//STRIP001                     xOut->writeBytes( aBinSeq );
//STRIP001                  xOut->closeOutput();
//STRIP001                 }
//STRIP001          }
//STRIP001
//STRIP001
//STRIP001          if( pLib->mbPasswordVerified || pLib->mbDoc50Password )
//STRIP001             {
//STRIP001              Any aElement = pLib->getByName( aElementName );
//STRIP001              if( isLibraryElementValid( aElement ) )
//STRIP001              {
//STRIP001                  OUString aSourceStreamName = aElementName;
//STRIP001                  aSourceStreamName += String( RTL_CONSTASCII_USTRINGPARAM(".xml") );
//STRIP001                  SotStorageStreamRef xSourceStream = xStorage->OpenSotStream
//STRIP001                      ( aSourceStreamName, STREAM_WRITE | STREAM_SHARE_DENYWRITE );
//STRIP001
//STRIP001                  if( xSourceStream->GetError() == ERRCODE_NONE )
//STRIP001                  {
//STRIP001                      String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
//STRIP001                      OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
//STRIP001                      Any aAny;
//STRIP001                      aAny <<= aMime;
//STRIP001                      xSourceStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001                         // Set encryption key
//STRIP001                      ByteString aByteKey( OUStringToOString( pLib->maPassword, RTL_TEXTENCODING_ASCII_US ) );
//STRIP001                         setStreamKey( xSourceStream, aByteKey );
//STRIP001
//STRIP001                         // #87671 Allow encryption
//STRIP001                      aPropName = String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("Encrypted") );
//STRIP001                      aAny <<= sal_True;
//STRIP001                      xSourceStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001                      Reference< XOutputStream > xOutput =
//STRIP001                          new utl::OOutputStreamWrapper( *xSourceStream );
//STRIP001                      writeLibraryElement( aElement, aElementName, xOutput );
//STRIP001                      xOutput->closeOutput();
//STRIP001
//STRIP001                      xSourceStream->Commit();
//STRIP001                  }
//STRIP001              }
//STRIP001             }
//STRIP001             else    // !mbPasswordVerified
//STRIP001             {
//STRIP001                 // TODO
//STRIP001                 // What to do if not verified?! In any case it's already loaded here
//STRIP001             }
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001     // Application libraries have only to be saved if the password
//STRIP001     // is verified because otherwise they can't be modified
//STRIP001  else if( pLib->mbPasswordVerified )
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001             OUString aLibDirPath = createAppLibraryFolder( pLib, aName );
//STRIP001
//STRIP001          for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001          {
//STRIP001              OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001              INetURLObject aElementInetObj( aLibDirPath );
//STRIP001              aElementInetObj.insertName( aElementName, sal_False,
//STRIP001                  INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001              aElementInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("pba") ) );
//STRIP001              String aElementPath = aElementInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001              Any aElement = pLib->getByName( aElementName );
//STRIP001              if( isLibraryElementValid( aElement ) )
//STRIP001              {
//STRIP001                     SotStorageRef xElementRootStorage = new SotStorage( sal_True, aElementPath );
//STRIP001
//STRIP001                     // Write binary image stream
//STRIP001                  SbModule* pMod = pBasicLib->FindModule( aElementName );
//STRIP001                  if( pMod )
//STRIP001                     {
//STRIP001                      OUString aCodeStreamName( RTL_CONSTASCII_USTRINGPARAM("code.bin") );
//STRIP001
//STRIP001                      SotStorageStreamRef xCodeStream = xElementRootStorage->OpenSotStream
//STRIP001                             ( aCodeStreamName, STREAM_WRITE | STREAM_SHARE_DENYWRITE | STREAM_TRUNC );
//STRIP001
//STRIP001                      if( xCodeStream->GetError() == ERRCODE_NONE )
//STRIP001                      {
//STRIP001                             SvMemoryStream aMemStream;
//STRIP001                             BOOL bStore = pMod->StoreBinaryData( aMemStream );
//STRIP001
//STRIP001                             // TODO? Store Id to check password?
//STRIP001
//STRIP001                             sal_Int32 nSize = (sal_Int32)aMemStream.Tell();
//STRIP001                             Sequence< sal_Int8 > aBinSeq( nSize );
//STRIP001                             sal_Int8* pData = aBinSeq.getArray();
//STRIP001                          ::rtl_copyMemory( pData, aMemStream.GetData(), nSize );
//STRIP001
//STRIP001                          Reference< XOutputStream > xOut = new utl::OOutputStreamWrapper( *xCodeStream );
//STRIP001                             xOut->writeBytes( aBinSeq );
//STRIP001                          xOut->closeOutput();
//STRIP001                         }
//STRIP001                  }
//STRIP001
//STRIP001                     // Set encryption key
//STRIP001                  ByteString aByteKey( OUStringToOString( pLib->maPassword, RTL_TEXTENCODING_ASCII_US ) );
//STRIP001                     xElementRootStorage->SetKey( aByteKey );
//STRIP001
//STRIP001                     // Write encrypted source stream
//STRIP001                  OUString aSourceStreamName( RTL_CONSTASCII_USTRINGPARAM("source.xml") );
//STRIP001                  SotStorageStreamRef xSourceStream = xElementRootStorage->OpenSotStream
//STRIP001                         ( aSourceStreamName, STREAM_WRITE | STREAM_SHARE_DENYWRITE | STREAM_TRUNC );
//STRIP001
//STRIP001                  if( xSourceStream->GetError() == ERRCODE_NONE )
//STRIP001                  {
//STRIP001                      String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
//STRIP001                      OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
//STRIP001                      Any aAny;
//STRIP001                      aAny <<= aMime;
//STRIP001                      xSourceStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001                         // #87671 Allow encryption
//STRIP001                      aPropName = String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("Encrypted") );
//STRIP001                      aAny <<= sal_True;
//STRIP001                      xSourceStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001                      Reference< XOutputStream > xOut = new utl::OOutputStreamWrapper( *xSourceStream );
//STRIP001                      writeLibraryElement( aElement, aElementName, xOut );
//STRIP001                      xOut->closeOutput();
//STRIP001                  }
//STRIP001
//STRIP001
//STRIP001                     // Storage Dtor commits too, that makes problems
//STRIP001                     // xElementRootStorage->Commit();
//STRIP001              }
//STRIP001
//STRIP001          }
//STRIP001      }
//STRIP001      catch( Exception& )
//STRIP001      {
//STRIP001          //throw e;
//STRIP001      }
//STRIP001  }
//STRIP001     return sal_True;
/*?*/ }

/*?*/ sal_Bool SfxScriptLibraryContainer::implLoadPasswordLibrary
/*?*/     ( SfxLibrary_Impl* pLib, const OUString& Name, sal_Bool bVerifyPasswordOnly )
/*?*/         throw(WrappedTargetException, RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  sal_Bool bLink = pLib->mbLink;
//STRIP001  sal_Bool bStorage = mxStorage.Is() && !bLink;
//STRIP001
//STRIP001     // Already loaded? Then only verifiedPassword can change something
//STRIP001  SfxScriptLibrary* pScriptLib = static_cast< SfxScriptLibrary* >( pLib );
//STRIP001     if( pScriptLib->mbLoaded )
//STRIP001     {
//STRIP001         if( pScriptLib->mbLoadedBinary && !bVerifyPasswordOnly &&
//STRIP001             (pScriptLib->mbLoadedSource || !pLib->mbPasswordVerified) )
//STRIP001                 return sal_False;
//STRIP001     }
//STRIP001
//STRIP001     StarBASIC* pBasicLib = NULL;
//STRIP001     sal_Bool bLoadBinary = sal_False;
//STRIP001     if( !pScriptLib->mbLoadedBinary && !bVerifyPasswordOnly && !pLib->mbPasswordVerified )
//STRIP001     {
//STRIP001         BasicManager* pBasicMgr = getBasicManager();
//STRIP001         sal_Bool bLoaded = pScriptLib->mbLoaded;
//STRIP001         pScriptLib->mbLoaded = sal_True;        // Necessary to get lib
//STRIP001         pBasicLib = pBasicMgr->GetLib( Name );
//STRIP001         pScriptLib->mbLoaded = bLoaded;    // Restore flag
//STRIP001         if( !pBasicLib )
//STRIP001          return sal_False;
//STRIP001
//STRIP001         bLoadBinary = sal_True;
//STRIP001         pScriptLib->mbLoadedBinary = sal_True;
//STRIP001     }
//STRIP001
//STRIP001     sal_Bool bLoadSource = sal_False;
//STRIP001     if( !pScriptLib->mbLoadedSource && pLib->mbPasswordVerified && !bVerifyPasswordOnly )
//STRIP001     {
//STRIP001         bLoadSource = sal_True;
//STRIP001         pScriptLib->mbLoadedSource = sal_True;
//STRIP001     }
//STRIP001
//STRIP001  Sequence< OUString > aElementNames = pLib->getElementNames();
//STRIP001  sal_Int32 nNameCount = aElementNames.getLength();
//STRIP001  const OUString* pNames = aElementNames.getConstArray();
//STRIP001
//STRIP001  if( bStorage )
//STRIP001     {
//STRIP001      SotStorageRef xLibrariesStor;
//STRIP001      SotStorageRef xLibraryStor;
//STRIP001      if( bStorage )
//STRIP001      {
//STRIP001             xLibrariesStor = mxStorage->OpenSotStorage( maLibrariesDir, STREAM_READ | STREAM_NOCREATE );
//STRIP001          if( xLibrariesStor.Is() && xLibrariesStor->GetError() == ERRCODE_NONE )
//STRIP001          {
//STRIP001                 xLibraryStor = xLibrariesStor->OpenSotStorage( Name, STREAM_READ | STREAM_NOCREATE );
//STRIP001          }
//STRIP001          if( !xLibraryStor.Is() || xLibraryStor->GetError() != ERRCODE_NONE )
//STRIP001          {
//STRIP001              OSL_ENSURE( 0, "### couln't open sub storage for library\n" );
//STRIP001              return sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001      {
//STRIP001          OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001             // Load binary
//STRIP001             if( bLoadBinary )
//STRIP001             {
//STRIP001              SbModule* pMod = pBasicLib->FindModule( aElementName );
//STRIP001                 if( !pMod )
//STRIP001                 {
//STRIP001                  pMod = pBasicLib->MakeModule( aElementName, String() );
//STRIP001                  pBasicLib->SetModified( FALSE );
//STRIP001                 }
//STRIP001
//STRIP001              //OUString aCodeStreamName( RTL_CONSTASCII_USTRINGPARAM("code.bin") );
//STRIP001              OUString aCodeStreamName= aElementName;
//STRIP001              aCodeStreamName += String( RTL_CONSTASCII_USTRINGPARAM(".bin") );
//STRIP001                 SotStorageStreamRef xCodeStream = xLibraryStor->OpenSotStream
//STRIP001                     ( aCodeStreamName, STREAM_READ );
//STRIP001
//STRIP001              if( xCodeStream->GetError() == ERRCODE_NONE )
//STRIP001              {
//STRIP001                     BOOL bRet = pMod->LoadBinaryData( *static_cast< SvStream* >( xCodeStream ) );
//STRIP001                     // TODO: Check return value
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             // Load source
//STRIP001             if( bLoadSource || bVerifyPasswordOnly )
//STRIP001             {
//STRIP001                 // Access encrypted source stream
//STRIP001              OUString aSourceStreamName = aElementName;
//STRIP001              aSourceStreamName += String( RTL_CONSTASCII_USTRINGPARAM(".xml") );
//STRIP001              ByteString aByteKey( OUStringToOString( pLib->maPassword, RTL_TEXTENCODING_ASCII_US ) );
//STRIP001              SotStorageStreamRef xSourceStream = xLibraryStor->OpenEncryptedSotStream
//STRIP001                  ( aSourceStreamName, aByteKey, STREAM_READ );
//STRIP001
//STRIP001                 // TODO: helper function to be used together with application basic
//STRIP001              if( xSourceStream->GetError() == ERRCODE_NONE )
//STRIP001                 {
//STRIP001                     if( bVerifyPasswordOnly )
//STRIP001                     {
//STRIP001                         // Check start of xml file
//STRIP001                         // TODO: Use password check functionality when available
//STRIP001                         char pTest[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
//STRIP001                         sal_Int32 nLen = strlen( pTest );
//STRIP001                         char* pBuf = new char[ nLen + 1 ];
//STRIP001                         pBuf[nLen] = 0;
//STRIP001                         sal_Int32 nRead = xSourceStream->Read( pBuf, nLen );
//STRIP001                         sal_Bool bRet = sal_True;
//STRIP001                         if( nRead != nLen || strcmp( pBuf, pTest ) != 0 )
//STRIP001                             bRet = sal_False;
//STRIP001                         delete pBuf;
//STRIP001                         return bRet;
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                      Any aAny = importLibraryElement( aSourceStreamName, xSourceStream );
//STRIP001                      if( pLib->hasByName( aElementName ) )
//STRIP001                         {
//STRIP001                             if( aAny.hasValue() )
//STRIP001                              pLib->maNameContainer.replaceByName( aElementName, aAny );
//STRIP001                         }
//STRIP001                      else
//STRIP001                         {
//STRIP001                          pLib->maNameContainer.insertByName( aElementName, aAny );
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001      try
//STRIP001      {
//STRIP001             OUString aLibDirPath = createAppLibraryFolder( pLib, Name );
//STRIP001
//STRIP001          for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001          {
//STRIP001              OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001              INetURLObject aElementInetObj( aLibDirPath );
//STRIP001              aElementInetObj.insertName( aElementName, sal_False,
//STRIP001                  INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001              aElementInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("pba") ) );
//STRIP001              String aElementPath = aElementInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001                 SotStorageRef xElementRootStorage = new SotStorage( sal_True, aElementPath );
//STRIP001              if( xElementRootStorage->GetError() == ERRCODE_NONE )
//STRIP001              {
//STRIP001                     // Load binary
//STRIP001                     if( bLoadBinary )
//STRIP001                     {
//STRIP001                      SbModule* pMod = pBasicLib->FindModule( aElementName );
//STRIP001                         if( !pMod )
//STRIP001                         {
//STRIP001                          pMod = pBasicLib->MakeModule( aElementName, String() );
//STRIP001                          pBasicLib->SetModified( FALSE );
//STRIP001                         }
//STRIP001
//STRIP001                      OUString aCodeStreamName( RTL_CONSTASCII_USTRINGPARAM("code.bin") );
//STRIP001                      SotStorageStreamRef xCodeStream = xElementRootStorage->OpenSotStream
//STRIP001                             ( aCodeStreamName, STREAM_READ );
//STRIP001
//STRIP001                      if( xCodeStream->GetError() == ERRCODE_NONE )
//STRIP001                      {
//STRIP001                             BOOL bRet = pMod->LoadBinaryData( *static_cast< SvStream* >( xCodeStream ) );
//STRIP001                             // TODO: Check return value
//STRIP001                         }
//STRIP001                     }
//STRIP001
//STRIP001                     // Load source
//STRIP001                     if( bLoadSource || bVerifyPasswordOnly )
//STRIP001                     {
//STRIP001                         // Set encrytion key
//STRIP001                      ByteString aByteKey( OUStringToOString( pLib->maPassword, RTL_TEXTENCODING_ASCII_US ) );
//STRIP001                         xElementRootStorage->SetKey( aByteKey );
//STRIP001
//STRIP001                         // Access encrypted source stream
//STRIP001                      OUString aSourceStreamName( RTL_CONSTASCII_USTRINGPARAM("source.xml") );
//STRIP001                         SotStorageStreamRef xSourceStream =
//STRIP001                             xElementRootStorage->OpenSotStream( aSourceStreamName, STREAM_READ );
//STRIP001
//STRIP001                         // TODO: helper function to be used together with application basic
//STRIP001                      if( xSourceStream->GetError() == ERRCODE_NONE )
//STRIP001                         {
//STRIP001                             if( bVerifyPasswordOnly )
//STRIP001                             {
//STRIP001                                 // Check start of xml file
//STRIP001                                 // TODO: Use password check functionality when available
//STRIP001                                 char pTest[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
//STRIP001                                 sal_Int32 nLen = strlen( pTest );
//STRIP001                                 char* pBuf = new char[ nLen + 1 ];
//STRIP001                                 pBuf[nLen] = 0;
//STRIP001                                 sal_Int32 nRead = xSourceStream->Read( pBuf, nLen );
//STRIP001                                 sal_Bool bRet = sal_True;
//STRIP001                                 if( nRead != nLen || strcmp( pBuf, pTest ) != 0 )
//STRIP001                                     bRet = sal_False;
//STRIP001                                 delete pBuf;
//STRIP001                                 return bRet;
//STRIP001                             }
//STRIP001                             else
//STRIP001                             {
//STRIP001                              Any aAny = importLibraryElement( aSourceStreamName, xSourceStream );
//STRIP001                              if( pLib->hasByName( aElementName ) )
//STRIP001                                 {
//STRIP001                                     if( aAny.hasValue() )
//STRIP001                                      pLib->maNameContainer.replaceByName( aElementName, aAny );
//STRIP001                                 }
//STRIP001                              else
//STRIP001                                 {
//STRIP001                                  pLib->maNameContainer.insertByName( aElementName, aAny );
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001      catch( Exception& )
//STRIP001      {
//STRIP001          // TODO
//STRIP001          //throw e;
//STRIP001      }
//STRIP001     }
//STRIP001
//STRIP001     // If the password is verified the library must remain modified, because
//STRIP001     // otherwise for saving the storage would be copied and that doesn't work
//STRIP001     // with mtg's storages when the password is verified
//STRIP001     if( !pLib->mbPasswordVerified )
//STRIP001         pLib->mbModified = sal_False;
//STRIP001     return sal_True;
/*?*/ }


//============================================================================
// Methods XInitialization
/*?*/ void SAL_CALL SfxScriptLibraryContainer::initialize( const Sequence< Any >& aArguments )
/*?*/     throw (::com::sun::star::uno::Exception,
/*?*/            ::com::sun::star::uno::RuntimeException)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  sal_Int32 nArgCount = aArguments.getLength();
//STRIP001  OSL_ENSURE( nArgCount, "SfxDialogLibraryContainer::initialize() called with no arguments\n" );
//STRIP001
//STRIP001     OUString aInitialisationParam;
//STRIP001     OUString aScriptLanguage;
//STRIP001     if( nArgCount )
//STRIP001     {
//STRIP001         const Any* pArgs = aArguments.getConstArray();
//STRIP001         pArgs[0] >>= aInitialisationParam;
//STRIP001      OSL_ENSURE( aInitialisationParam.getLength(),
//STRIP001             "SfxDialogLibraryContainer::initialize() called with empty url\n" );
//STRIP001
//STRIP001         if( nArgCount > 1 )
//STRIP001             pArgs[1] >>= aInitialisationParam;
//STRIP001         else
//STRIP001             aScriptLanguage = OUString::createFromAscii( "StarBasic" );
//STRIP001     }
//STRIP001
//STRIP001     init( aInitialisationParam, aScriptLanguage );
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
