/*************************************************************************
 *
 *  $RCSfile: sfx2_namecont.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:16 $
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
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINER_HPP_
#include <com/sun/star/container/XContainer.hpp>
#endif

#ifndef __RSC //autogen
#include <tools/errinf.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _RTL_URI_HXX_
#include <rtl/uri.hxx>
#endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#include <cppuhelper/typeprovider.hxx>
#include "namecont.hxx"

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#include <svtools/pathoptions.hxx>
#include <svtools/sfxecode.hxx>
#include <svtools/ehdl.hxx>
#include <basic/basmgr.hxx>


#ifndef _COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XExtendedDocumentHandler.hpp>
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
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_DEPLOYMENTEXCEPTION_HPP_
#include <com/sun/star/uno/DeploymentException.hpp>
#endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace com::sun::star::container;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::io;
using namespace com::sun::star::ucb;
using namespace com::sun::star::script;
using namespace com::sun::star::beans;
using namespace com::sun::star::xml::sax;
using namespace com::sun::star;
using namespace cppu;
using namespace rtl;
using namespace osl;


//============================================================================
// Implementation class NameContainer_Impl

namespace SfxContainer_Impl
{

// Methods XElementAccess
/*?*/ Type NameContainer_Impl::getElementType()
/*?*/   throw(RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP");  return mType;//STRIP001
//STRIP001  return mType;
/*?*/ }

/*N*/ sal_Bool NameContainer_Impl::hasElements()
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   sal_Bool bRet = (mnElementCount > 0);
/*N*/   return bRet;
/*N*/ }

// Methods XNameAccess
/*N*/ Any NameContainer_Impl::getByName( const OUString& aName )
/*N*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   NameContainerNameMap::iterator aIt = mHashMap.find( aName );
/*N*/   if( aIt == mHashMap.end() )
/*N*/   {
/*?*/       throw NoSuchElementException();
/*N*/   }
/*N*/   sal_Int32 iHashResult = (*aIt).second;
/*N*/   Any aRetAny = mValues.getConstArray()[ iHashResult ];
/*N*/   return aRetAny;
/*N*/ }

/*N*/ Sequence< OUString > NameContainer_Impl::getElementNames()
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   return mNames;
/*N*/ }

/*N*/ sal_Bool NameContainer_Impl::hasByName( const OUString& aName )
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   NameContainerNameMap::iterator aIt = mHashMap.find( aName );
/*N*/   sal_Bool bRet = ( aIt != mHashMap.end() );
/*N*/   return bRet;
/*N*/ }


// Methods XNameReplace
/*N*/ void NameContainer_Impl::replaceByName( const OUString& aName, const Any& aElement )
/*N*/   throw(IllegalArgumentException, NoSuchElementException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   Type aAnyType = aElement.getValueType();
/*N*/   if( mType != aAnyType )
/*?*/       throw IllegalArgumentException();
/*N*/
/*N*/   NameContainerNameMap::iterator aIt = mHashMap.find( aName );
/*N*/   if( aIt == mHashMap.end() )
/*N*/   {
/*?*/       throw NoSuchElementException();
/*N*/   }
/*N*/   sal_Int32 iHashResult = (*aIt).second;
/*N*/   Any aOldElement = mValues.getConstArray()[ iHashResult ];
/*N*/   mValues.getArray()[ iHashResult ] = aElement;
/*N*/
/*N*/
/*N*/   // Fire event
/*N*/   ContainerEvent aEvent;
/*N*/   aEvent.Source = mpxEventSource;
/*N*/   aEvent.Accessor <<= aName;
/*N*/   aEvent.Element = aElement;
/*N*/   aEvent.ReplacedElement = aOldElement;
/*N*/
/*N*/   OInterfaceIteratorHelper aIterator( maListenerContainer );
/*N*/   while( aIterator.hasMoreElements() )
/*N*/   {
/*?*/       Reference< XInterface > xIface = aIterator.next();
/*?*/       Reference< XContainerListener > xListener( xIface, UNO_QUERY );
/*?*/         try
/*?*/         {
/*?*/             xListener->elementReplaced( aEvent );
/*?*/         }
/*?*/         catch(RuntimeException&)
/*?*/         {
/*?*/             aIterator.remove();
/*?*/         }
/*N*/   }
/*N*/ }


// Methods XNameContainer
/*N*/ void NameContainer_Impl::insertByName( const OUString& aName, const Any& aElement )
/*N*/   throw(IllegalArgumentException, ElementExistException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   Type aAnyType = aElement.getValueType();
/*N*/   if( mType != aAnyType )
/*?*/       throw IllegalArgumentException();
/*N*/
/*N*/   NameContainerNameMap::iterator aIt = mHashMap.find( aName );
/*N*/   if( aIt != mHashMap.end() )
/*N*/   {
/*?*/       throw ElementExistException();
/*N*/   }
/*N*/
/*N*/   sal_Int32 nCount = mNames.getLength();
/*N*/   mNames.realloc( nCount + 1 );
/*N*/   mValues.realloc( nCount + 1 );
/*N*/   mNames.getArray()[ nCount ] = aName;
/*N*/   mValues.getArray()[ nCount ] = aElement;
/*N*/
/*N*/   mHashMap[ aName ] = nCount;
/*N*/   mnElementCount++;
/*N*/
/*N*/
/*N*/   // Fire event
/*N*/   ContainerEvent aEvent;
/*N*/   aEvent.Source = mpxEventSource;
/*N*/   aEvent.Accessor <<= aName;
/*N*/   aEvent.Element = aElement;
/*N*/
/*N*/   OInterfaceIteratorHelper aIterator( maListenerContainer );
/*N*/   while( aIterator.hasMoreElements() )
/*N*/   {
/*N*/       Reference< XInterface > xIface = aIterator.next();
/*N*/       Reference< XContainerListener > xListener( xIface, UNO_QUERY );
/*N*/         try
/*N*/         {
/*N*/             xListener->elementInserted( aEvent );
/*N*/         }
/*N*/         catch(RuntimeException&)
/*N*/         {
/*?*/             aIterator.remove();
/*N*/         }
/*N*/   }
/*N*/ }

/*?*/ void NameContainer_Impl::removeByName( const OUString& Name )
/*?*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  NameContainerNameMap::iterator aIt = mHashMap.find( Name );
//STRIP001  if( aIt == mHashMap.end() )
//STRIP001  {
//STRIP001      throw NoSuchElementException();
//STRIP001  }
//STRIP001
//STRIP001  sal_Int32 iHashResult = (*aIt).second;
//STRIP001  Any aOldElement = mValues.getConstArray()[ iHashResult ];
//STRIP001  mHashMap.erase( aIt );
//STRIP001  sal_Int32 iLast = mNames.getLength() - 1;
//STRIP001  if( iLast != iHashResult )
//STRIP001  {
//STRIP001      OUString* pNames = mNames.getArray();
//STRIP001      Any* pValues = mValues.getArray();
//STRIP001      pNames[ iHashResult ] = pNames[ iLast ];
//STRIP001      pValues[ iHashResult ] = pValues[ iLast ];
//STRIP001      mHashMap[ pNames[ iHashResult ] ] = iHashResult;
//STRIP001  }
//STRIP001  mNames.realloc( iLast );
//STRIP001  mValues.realloc( iLast );
//STRIP001  mnElementCount--;
//STRIP001
//STRIP001
//STRIP001  // Fire event
//STRIP001  ContainerEvent aEvent;
//STRIP001  aEvent.Source = mpxEventSource;
//STRIP001  aEvent.Accessor <<= Name;
//STRIP001  aEvent.Element = aOldElement;
//STRIP001
//STRIP001  OInterfaceIteratorHelper aIterator( maListenerContainer );
//STRIP001  while( aIterator.hasMoreElements() )
//STRIP001  {
//STRIP001      Reference< XInterface > xIface = aIterator.next();
//STRIP001      Reference< XContainerListener > xListener( xIface, UNO_QUERY );
//STRIP001         try
//STRIP001         {
//STRIP001             xListener->elementRemoved( aEvent );
//STRIP001         }
//STRIP001         catch(RuntimeException&)
//STRIP001         {
//STRIP001             aIterator.remove();
//STRIP001         }
//STRIP001  }
/*?*/ }


// Methods XContainer
/*N*/ void SAL_CALL NameContainer_Impl::addContainerListener( const Reference< XContainerListener >& xListener )
/*N*/   throw (RuntimeException)
/*N*/ {
/*N*/   if( !xListener.is() )
/*?*/       throw RuntimeException();
/*N*/   Reference< XInterface > xIface( xListener, UNO_QUERY );
/*N*/   maListenerContainer.addInterface( xIface );
/*N*/ }

/*?*/ void SAL_CALL NameContainer_Impl::removeContainerListener( const Reference< XContainerListener >& xListener )
/*?*/   throw (RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( !xListener.is() )
//STRIP001      throw RuntimeException();
//STRIP001  Reference< XInterface > xIface( xListener, UNO_QUERY );
//STRIP001  maListenerContainer.removeInterface( xIface );
/*?*/ }

}   // namespace SfxContainer_Impl


//============================================================================

// Implementation class SfxLibraryContainer_Impl

// Ctor
/*N*/ SfxLibraryContainer_Impl::SfxLibraryContainer_Impl( void )
/*N*/   : maNameContainer( getCppuType( (Reference< XNameAccess >*) NULL ) )
/*N*/   , mbModified( sal_False )
/*N*/     , mbOldInfoFormat( sal_False )
/*N*/     , mpBasMgr( NULL )
/*N*/     , mbOwnBasMgr( sal_False )
/*N*/ {
/*N*/   mxMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   if( !mxMSF.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't get ProcessServiceFactory\n" );
/*N*/   }
/*N*/
/*N*/   mxSFI = Reference< XSimpleFileAccess >( mxMSF->createInstance
/*N*/       ( OUString::createFromAscii( "com.sun.star.ucb.SimpleFileAccess" ) ), UNO_QUERY );
/*N*/   if( !mxSFI.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't create SimpleFileAccess component\n" );
/*N*/   }
/*N*/ }

/*N*/ SfxLibraryContainer_Impl::~SfxLibraryContainer_Impl()
/*N*/ {
/*N*/     if( mbOwnBasMgr )
/*?*/         delete mpBasMgr;
/*N*/ }


/*?*/ static void checkAndCopyFileImpl( const INetURLObject& rSourceFolderInetObj,
/*?*/                                 const INetURLObject& rTargetFolderInetObj,
/*?*/                                 const OUString& rCheckFileName,
/*?*/                                 const OUString& rCheckExtension,
/*?*/                                 Reference< XSimpleFileAccess > xSFI )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001  INetURLObject aTargetFolderInetObj( rTargetFolderInetObj );
//STRIP001  aTargetFolderInetObj.insertName( rCheckFileName, sal_True, INetURLObject::LAST_SEGMENT,
//STRIP001                                   sal_True, INetURLObject::ENCODE_ALL );
//STRIP001  aTargetFolderInetObj.setExtension( rCheckExtension );
//STRIP001  OUString aTargetFile = aTargetFolderInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001  if( !xSFI->exists( aTargetFile ) )
//STRIP001  {
//STRIP001      INetURLObject aSourceFolderInetObj( rSourceFolderInetObj );
//STRIP001      aSourceFolderInetObj.insertName( rCheckFileName, sal_True, INetURLObject::LAST_SEGMENT,
//STRIP001                                       sal_True, INetURLObject::ENCODE_ALL );
//STRIP001      aSourceFolderInetObj.setExtension( rCheckExtension );
//STRIP001      OUString aSourceFile = aSourceFolderInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001      xSFI->copy( aSourceFile, aTargetFile );
//STRIP001  }
/*?*/ }

/*N*/ sal_Bool SfxLibraryContainer_Impl::init(
/*N*/     const OUString& aInitialisationParam,
/*N*/     const OUString& aInfoFileName,
/*N*/     const OUString& aOldInfoFileName,
/*N*/     const OUString& aLibElementFileExtension,
/*N*/     const OUString& aLibrariesDir,
/*N*/     SotStorageRef xStorage )
/*N*/ {
/*N*/     maInitialisationParam = aInitialisationParam;
/*N*/   maInfoFileName = aInfoFileName;
/*N*/   maOldInfoFileName = aOldInfoFileName;
/*N*/   maLibElementFileExtension = aLibElementFileExtension;
/*N*/   maLibrariesDir = aLibrariesDir;
/*N*/
/*N*/     meInitMode = DEFAULT;
/*N*/     INetURLObject aInitUrlInetObj( maInitialisationParam );
/*N*/     OUString aInitFileName = aInitUrlInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/     if( aInitFileName.getLength() )
/*N*/     {
/*N*/         // We need a BasicManager to avoid problems
/*?*/         StarBASIC* pBas = new StarBASIC();
/*?*/         mpBasMgr = new BasicManager( pBas );
/*?*/         mbOwnBasMgr = sal_True;
/*?*/
/*?*/         OUString aExtension = aInitUrlInetObj.getExtension();
/*?*/         if( aExtension.compareToAscii( "xlc" ) == COMPARE_EQUAL )
/*?*/         {
/*?*/             meInitMode = CONTAINER_INIT_FILE;
/*?*/           INetURLObject aLibPathInetObj( aInitUrlInetObj );
/*?*/           aLibPathInetObj.removeSegment();
/*?*/           maLibraryPath = aLibPathInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*?*/         }
/*?*/         else if( aExtension.compareToAscii( "xlb" ) == COMPARE_EQUAL )
/*?*/         {
/*?*/             meInitMode = LIBRARY_INIT_FILE;
/*?*/           SotStorageRef xDummyStor;
/*?*/             ::xmlscript::LibDescriptor aLibDesc;
/*?*/             sal_Bool bReadIndexFile = implLoadLibraryIndexFile( NULL, aLibDesc, xDummyStor, aInitFileName );
/*?*/               return bReadIndexFile;
/*?*/         }
/*?*/         else
/*?*/         {
/*?*/             // Decide between old and new document
/*?*/             sal_Bool bOldStorage = SotStorage::IsOLEStorage( aInitFileName );
/*?*/             if( bOldStorage )
/*?*/             {
/*?*/                 meInitMode = OLD_BASIC_STORAGE;
/*?*/                 importFromOldStorage( aInitFileName );
/*?*/               return sal_True;
/*?*/             }
/*?*/             else
/*?*/             {
/*?*/                 meInitMode = OFFICE_DOCUMENT;
/*?*/                 xStorage = new SotStorage( sal_True, aInitFileName );
/*?*/             }
/*N*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         // Default pathes
/*N*/         maLibraryPath = SvtPathOptions().GetBasicPath();
/*N*/     }
/*N*/
/*N*/   Reference< XParser > xParser( mxMSF->createInstance(
/*N*/       OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Parser") ) ), UNO_QUERY );
/*N*/   if( !xParser.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't create sax parser component\n" );
/*N*/       return sal_False;
/*N*/   }
/*N*/
/*N*/   Reference< XInputStream > xInput;
/*N*/
/*N*/   mxStorage = xStorage;
/*N*/   sal_Bool bStorage = mxStorage.Is();
/*N*/   SotStorageRef xLibrariesStor;
/*N*/   SotStorageStreamRef xStream;
/*N*/   String aFileName;
/*N*/
/*N*/   int nPassCount = 1;
/*N*/   if( !bStorage && meInitMode == DEFAULT )
/*N*/       nPassCount = 2;
/*N*/   for( int nPass = 0 ; nPass < nPassCount ; nPass++ )
/*N*/   {
/*N*/       if( bStorage )
/*N*/       {
/*N*/           OSL_ENSURE( meInitMode == DEFAULT || meInitMode == OFFICE_DOCUMENT,
/*N*/               "### Wrong InitMode for document\n" );
/*N*/
/*N*/           xLibrariesStor = xStorage->OpenSotStorage( maLibrariesDir, STREAM_READ | STREAM_NOCREATE );
/*N*/           if( xLibrariesStor.Is() && xLibrariesStor->GetError() == ERRCODE_NONE )
/*N*/           {
/*?*/               aFileName = maInfoFileName;
/*?*/               aFileName += String( RTL_CONSTASCII_USTRINGPARAM("-lc.xml") );
/*?*/
/*?*/               xStream = xLibrariesStor->OpenSotStream( aFileName, STREAM_READ | STREAM_NOCREATE );
/*?*/               if( xStream->GetError() != ERRCODE_NONE )
/*?*/               {
/*?*/                   mbOldInfoFormat = true;
/*?*/
/*?*/                   // Check old version
/*?*/                   aFileName = maOldInfoFileName;
/*?*/                   aFileName += String( RTL_CONSTASCII_USTRINGPARAM(".xml") );
/*?*/                   xStream = xLibrariesStor->OpenSotStream( aFileName, STREAM_READ );
/*?*/
/*?*/                   if( xStream->GetError() != ERRCODE_NONE )
/*?*/                   {
/*?*/                       // Check for EA2 document version with wrong extensions
/*?*/                       aFileName = maOldInfoFileName;
/*?*/                       aFileName += String( RTL_CONSTASCII_USTRINGPARAM(".xli") );
/*?*/                       xStream = xLibrariesStor->OpenSotStream( aFileName, STREAM_READ );
/*?*/                   }
/*?*/               }
/*N*/
/*N*/               if( xStream->GetError() == ERRCODE_NONE )
/*N*/               {
/*N*/                   xInput = new utl::OInputStreamWrapper( *xStream );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           INetURLObject* pLibInfoInetObj = NULL;
/*N*/           if( meInitMode == CONTAINER_INIT_FILE )
/*N*/           {
/*?*/               aFileName = aInitFileName;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               if( nPass == 1 )
/*N*/                   pLibInfoInetObj = new INetURLObject( String(maLibraryPath).GetToken(0) );
/*N*/               else
/*N*/                   pLibInfoInetObj = new INetURLObject( String(maLibraryPath).GetToken(1) );
/*N*/               pLibInfoInetObj->insertName( maInfoFileName, sal_True, INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
/*N*/               pLibInfoInetObj->setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xlc") ) );
/*N*/               aFileName = pLibInfoInetObj->GetMainURL( INetURLObject::NO_DECODE );
/*N*/           }
/*N*/
/*N*/           try
/*N*/           {
/*N*/               xInput = mxSFI->openFileRead( aFileName );
/*N*/           }
/*N*/           catch( Exception& )
/*N*/           {
/*N*/               xInput.clear();
/*N*/                 if( nPass == 0 )
/*N*/                 {
/*N*/                   SfxErrorContext aEc( ERRCTX_SFX_LOADBASIC, aFileName );
/*N*/                     ULONG nErrorCode = ERRCODE_IO_GENERAL;
/*N*/                     ErrorHandler::HandleError( nErrorCode );
/*N*/                 }
/*N*/           }
/*N*/
/*N*/           // Old variant?
/*N*/           if( !xInput.is() && nPass == 0 )
/*?*/           {
/*?*/               INetURLObject aLibInfoInetObj( String(maLibraryPath).GetToken(1) );
/*?*/               aLibInfoInetObj.insertName( maOldInfoFileName, sal_True, INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
/*?*/               aLibInfoInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xli") ) );
/*?*/               aFileName = aLibInfoInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*?*/
/*?*/               try
/*?*/               {
/*?*/                   xInput = mxSFI->openFileRead( aFileName );
/*?*/                   mbOldInfoFormat = true;
/*?*/               }
/*?*/               catch( Exception& )
/*?*/               {
/*?*/                   xInput.clear();
/*?*/                   SfxErrorContext aEc( ERRCTX_SFX_LOADBASIC, aFileName );
/*?*/                     ULONG nErrorCode = ERRCODE_IO_GENERAL;
/*?*/                     ErrorHandler::HandleError( nErrorCode );
/*?*/               }
/*?*/           }
/*N*/
/*N*/           delete pLibInfoInetObj;
/*N*/       }
/*N*/
/*N*/       if( xInput.is() )
/*N*/         {
/*N*/           InputSource source;
/*N*/           source.aInputStream = xInput;
/*N*/           source.sSystemId    = aFileName;
/*N*/
/*N*/           // start parsing
/*N*/           ::xmlscript::LibDescriptorArray* pLibArray = new ::xmlscript::LibDescriptorArray();
/*N*/
/*N*/             try
/*N*/             {
/*N*/                 xParser->setDocumentHandler( ::xmlscript::importLibraryContainer( pLibArray ) );
/*N*/                 xParser->parseStream( source );
/*N*/             }
/*N*/             catch ( xml::sax::SAXException& e )
/*N*/             {
/*N*/                 OSL_ENSURE( 0, OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US ).getStr() );
/*N*/                 return sal_False;
/*N*/             }
/*N*/             catch ( io::IOException& e )
/*N*/             {
/*N*/                 OSL_ENSURE( 0, OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US ).getStr() );
/*N*/                 return sal_False;
/*N*/             }
/*N*/
/*N*/           sal_Int32 nLibCount = pLibArray->mnLibCount;
/*N*/           for( sal_Int32 i = 0 ; i < nLibCount ; i++ )
/*N*/           {
/*N*/               ::xmlscript::LibDescriptor& rLib = pLibArray->mpLibs[i];
/*N*/
/*N*/               // Check storage URL
/*N*/               OUString aStorageURL = rLib.aStorageURL;
/*N*/               if( !bStorage && !aStorageURL.getLength() && nPass == 0 )
/*N*/               {
/*N*/                   String aLibraryPath;
/*N*/                   if( meInitMode == CONTAINER_INIT_FILE )
/*N*/                       aLibraryPath = maLibraryPath;
/*N*/                   else
/*N*/                       aLibraryPath = String(maLibraryPath).GetToken(1);
/*N*/                   INetURLObject aInetObj( aLibraryPath );
/*N*/
/*N*/                   aInetObj.insertName( rLib.aName, sal_True, INetURLObject::LAST_SEGMENT,
/*N*/                       sal_True, INetURLObject::ENCODE_ALL );
/*N*/                   OUString aLibDirPath = aInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/                   if( mxSFI->isFolder( aLibDirPath ) )
/*N*/                   {
/*N*/                       rLib.aStorageURL = aLibDirPath;
/*N*/                       mbModified = sal_True;
/*N*/                   }
/*N*/                   else if( rLib.bLink )
/*N*/                   {
/*N*/                       // Check "share" path
/*N*/                       INetURLObject aShareInetObj( String(maLibraryPath).GetToken(0) );
/*N*/                       aShareInetObj.insertName( rLib.aName, sal_True, INetURLObject::LAST_SEGMENT,
/*N*/                           sal_True, INetURLObject::ENCODE_ALL );
/*N*/                       OUString aShareLibDirPath = aShareInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/                       if( mxSFI->isFolder( aShareLibDirPath ) )
/*N*/                       {
/*N*/                           rLib.aStorageURL = aShareLibDirPath;
/*N*/                           mbModified = sal_True;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               OUString aLibName = rLib.aName;
/*N*/
/*N*/               // If the same library name is used by the shared and the
/*N*/               // user lib container index files the user file wins
/*N*/               if( nPass == 1 && hasByName( aLibName ) )
/*N*/                   continue;
/*N*/
/*N*/               SfxLibrary_Impl* pImplLib;
/*N*/               if( rLib.bLink )
/*N*/               {
/*N*/                   Reference< XNameAccess > xLib =
/*N*/                       createLibraryLink( aLibName, rLib.aStorageURL, rLib.bReadOnly );
/*N*/                   pImplLib = static_cast< SfxLibrary_Impl* >( xLib.get() );
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   Reference< XNameContainer > xLib = createLibrary( aLibName );
/*N*/                   pImplLib = static_cast< SfxLibrary_Impl* >( xLib.get() );
/*N*/                   pImplLib->mbLoaded = sal_False;
/*N*/                   pImplLib->mbReadOnly = rLib.bReadOnly;
/*N*/                   if( !bStorage )
/*N*/                       checkStorageURL( rLib.aStorageURL, pImplLib->maLibInfoFileURL,
/*N*/                             pImplLib->maStorageURL, pImplLib->maUnexpandedStorageURL );
/*N*/               }
/*N*/
/*N*/               // Read library info files
/*N*/               if( !mbOldInfoFormat )
/*N*/               {
/*N*/                   SotStorageRef xLibraryStor;
/*N*/                       if( bStorage )
/*N*/                   {
/*?*/                       xLibraryStor = xLibrariesStor->OpenSotStorage( rLib.aName, STREAM_READ | STREAM_NOCREATE );
/*?*/                       if( !xLibraryStor.Is() || xLibraryStor->GetError() != ERRCODE_NONE )
/*?*/                       {
/*?*/                           OSL_ENSURE( 0, "### couln't open sub storage for library\n" );
/*?*/                           xLibraryStor = NULL;
/*N*/                       }
/*N*/                   }
/*N*/
/*N*/                   // Link is already initialised in createLibraryLink()
/*N*/                   if( !pImplLib->mbInitialised && (!bStorage || xLibraryStor.Is()) )
/*N*/                   {
/*N*/                       OUString aIndexFileName;
/*N*/                       sal_Bool bLoaded = implLoadLibraryIndexFile( pImplLib, rLib, xLibraryStor, aIndexFileName );
/*N*/                       if( bLoaded && aLibName != rLib.aName )
/*N*/                       {
/*N*/                           OSL_ENSURE( 0, "Different library names in library"
/*N*/                               " container and library info files!\n" );
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               else if( !bStorage )
/*N*/               {DBG_ASSERT(0, "STRIP");//STRIP001
/*N*/                   // Write new index file immediately because otherwise
/*N*/                   // the library elements will be lost when storing into
/*N*/                   // the new info format
//STRIP001 /*?*/                    SotStorageRef xStorage;
//STRIP001 /*?*/                    implStoreLibraryIndexFile( pImplLib, rLib, xStorage );
/*N*/               }
/*N*/
/*N*/               implImportLibDescriptor( pImplLib, rLib );
/*N*/
/*N*/               if( nPass == 1 )
/*N*/               {
/*?*/                   pImplLib->mbSharedIndexFile = sal_True;
/*?*/                   pImplLib->mbReadOnly = sal_True;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           // Keep flag for documents to force writing the new index files
/*N*/           if( !bStorage )
/*N*/               mbOldInfoFormat = sal_False;
/*N*/
/*N*/           delete pLibArray;
/*N*/         }
/*N*/       // Only in the first pass it's an error when no index file is found
/*N*/       else if( nPass == 0 )
/*N*/       {
/*N*/           return sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/     // #56666, upgrade installation 6.0 -> 6.1
/*N*/     if( meInitMode == DEFAULT )
/*N*/     {
/*N*/         INetURLObject aUserBasicInetObj( String(maLibraryPath).GetToken(1) );
/*N*/       OUString aStandardStr( RTL_CONSTASCII_USTRINGPARAM("Standard") );
/*N*/
/*N*/       static char str60FolderName_1[] = "__basic_60";
/*N*/       static char str60FolderName_2[] = "__basic_60_2";
/*N*/         INetURLObject aUserBasic60InetObj_1( aUserBasicInetObj );
/*N*/         aUserBasic60InetObj_1.removeSegment();
/*N*/       INetURLObject aUserBasic60InetObj_2 = aUserBasic60InetObj_1;
/*N*/       aUserBasic60InetObj_1.Append( str60FolderName_1 );
/*N*/       aUserBasic60InetObj_2.Append( str60FolderName_2 );
/*N*/
/*N*/       INetURLObject aUserBasic60InetObj = aUserBasic60InetObj_1;
/*N*/         String aFolder60 = aUserBasic60InetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/       bool bSecondTime = false;
/*N*/       if( mxSFI->isFolder( aFolder60 ) )
/*N*/       {
/*?*/           // #110101 Check if Standard folder exists and is complete
/*?*/           INetURLObject aUserBasicStandardInetObj( aUserBasicInetObj );
/*?*/           aUserBasicStandardInetObj.insertName( aStandardStr, sal_True, INetURLObject::LAST_SEGMENT,
/*?*/                                                 sal_True, INetURLObject::ENCODE_ALL );
/*?*/             INetURLObject aUserBasic60StandardInetObj( aUserBasic60InetObj );
/*?*/           aUserBasic60StandardInetObj.insertName( aStandardStr, sal_True, INetURLObject::LAST_SEGMENT,
/*?*/                                                     sal_True, INetURLObject::ENCODE_ALL );
/*?*/           OUString aStandardFolder60 = aUserBasic60StandardInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*?*/           if( mxSFI->isFolder( aStandardFolder60 ) )
/*?*/           {
/*?*/               OUString aXlbExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xlb") ) );
/*?*/               OUString aCheckFileName;
/*?*/
/*?*/               // Check if script.xlb exists
/*?*/               aCheckFileName = OUString( RTL_CONSTASCII_USTRINGPARAM("script") );
/*?*/               checkAndCopyFileImpl( aUserBasicStandardInetObj,
/*?*/                                     aUserBasic60StandardInetObj,
/*?*/                                     aCheckFileName, aXlbExtension, mxSFI );
/*?*/
/*?*/               // Check if dialog.xlb exists
/*?*/               aCheckFileName = OUString( RTL_CONSTASCII_USTRINGPARAM("dialog") );
/*?*/               checkAndCopyFileImpl( aUserBasicStandardInetObj,
/*?*/                                     aUserBasic60StandardInetObj,
/*?*/                                     aCheckFileName, aXlbExtension, mxSFI );
/*?*/
/*?*/               // Check if module1.xba exists
/*?*/               OUString aXbaExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xba") ) );
/*?*/               aCheckFileName = OUString( RTL_CONSTASCII_USTRINGPARAM("Module1") );
/*?*/               checkAndCopyFileImpl( aUserBasicStandardInetObj,
/*?*/                                     aUserBasic60StandardInetObj,
/*?*/                                     aCheckFileName, aXbaExtension, mxSFI );
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               String aStandardFolder = aUserBasicStandardInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*?*/               mxSFI->copy( aStandardFolder, aStandardFolder60 );
/*?*/           }
/*?*/
/*?*/           String aCopyToFolder60 = aUserBasic60InetObj_2.GetMainURL( INetURLObject::NO_DECODE );
/*?*/           mxSFI->copy( aFolder60, aCopyToFolder60 );
/*?*/       }
/*N*/       else
/*?*/       {
/*?*/           bSecondTime = true;
/*?*/           aUserBasic60InetObj = aUserBasic60InetObj_2;
/*?*/           aFolder60 = aUserBasic60InetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/       }
/*N*/       if( mxSFI->isFolder( aFolder60 ) )
/*?*/         {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001 /*?*/             SfxLibraryContainer_Impl* pCont60 = createInstanceImpl();
//STRIP001 /*?*/             Reference< XInterface > xRef = static_cast< XInterface* >( static_cast< OWeakObject* >(pCont60) );
//STRIP001 /*?*/
//STRIP001 /*?*/             // Rename folder __basic_60 to make storage URLs correct during initialisation
//STRIP001 /*?*/             String aFolderUserBasic = aUserBasicInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001 /*?*/             INetURLObject aUserBasicTmpInetObj( aUserBasicInetObj );
//STRIP001 /*?*/             aUserBasicTmpInetObj.removeSegment();
//STRIP001 /*?*/            aUserBasicTmpInetObj.Append( "__basic_tmp" );
//STRIP001 /*?*/             String aFolderTmp = aUserBasicTmpInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001 /*?*/             mxSFI->move( aFolderUserBasic, aFolderTmp );
//STRIP001 /*?*/             mxSFI->move( aFolder60, aFolderUserBasic );
//STRIP001 /*?*/
//STRIP001 /*?*/             INetURLObject aUserBasic60LibInfoInetObj( aUserBasicInetObj );
//STRIP001 /*?*/            aUserBasic60LibInfoInetObj.insertName( maInfoFileName, sal_True, INetURLObject::LAST_SEGMENT,
//STRIP001 /*?*/                                                    sal_True, INetURLObject::ENCODE_ALL );
//STRIP001 /*?*/            aUserBasic60LibInfoInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xlc") ) );
//STRIP001 /*?*/            OUString aLibInfoFileName = aUserBasic60LibInfoInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001 /*?*/             Sequence<Any> aInitSeq( 1 );
//STRIP001 /*?*/            aInitSeq.getArray()[0] <<= aLibInfoFileName;
//STRIP001 /*?*/             pCont60->initialize( aInitSeq );
//STRIP001 /*?*/
//STRIP001 /*?*/             // Rename folders back
//STRIP001 /*?*/             mxSFI->move( aFolderUserBasic, aFolder60 );
//STRIP001 /*?*/             mxSFI->move( aFolderTmp, aFolderUserBasic );
//STRIP001 /*?*/
//STRIP001 /*?*/             // Detect old share/basic folder to destinguish
//STRIP001 /*?*/             // between own links and links to wizards
//STRIP001 /*?*/             INetURLObject aOrgShareFolder60InetObj;
//STRIP001 /*?*/             if( pCont60->hasByName( aStandardStr ) )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 SfxLibrary_Impl* pImplLib = pCont60->getImplLib( aStandardStr );
//STRIP001 /*?*/                 aOrgShareFolder60InetObj = INetURLObject( pImplLib->maStorageURL );
//STRIP001 /*?*/                 for( int i = 0 ; i < 3 ; ++ i )
//STRIP001 /*?*/                     aOrgShareFolder60InetObj.removeSegment();
//STRIP001 /*?*/                aOrgShareFolder60InetObj.Append( "share" );
//STRIP001 /*?*/                aOrgShareFolder60InetObj.Append( "basic" );
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/            Sequence< OUString > aNames = pCont60->getElementNames();
//STRIP001 /*?*/            const OUString* pNames = aNames.getConstArray();
//STRIP001 /*?*/            sal_Int32 i, nNameCount = aNames.getLength();
//STRIP001 /*?*/
//STRIP001 /*?*/            for( i = 0 ; i < nNameCount ; i++ )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 OUString aLibName = pNames[ i ];
//STRIP001 /*?*/                 if( hasByName( aLibName ) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     if( aLibName == aStandardStr )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         SfxLibrary_Impl* pImplLib = getImplLib( aStandardStr );
//STRIP001 /*?*/                         INetURLObject aStandardFolderInetObj( pImplLib->maStorageURL );
//STRIP001 /*?*/                         String aStandardFolder = pImplLib->maStorageURL;
//STRIP001 /*?*/                        mxSFI->kill( aStandardFolder );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         continue;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                 SfxLibrary_Impl* pImplLib = pCont60->getImplLib( aLibName );
//STRIP001 /*?*/                 if( pImplLib->mbLink )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     INetURLObject aLink60InetObj( pImplLib->maStorageURL );
//STRIP001 /*?*/                     for( int i = 0 ; i < 3 ; ++ i )
//STRIP001 /*?*/                         aLink60InetObj.removeSegment();
//STRIP001 /*?*/                    aLink60InetObj.Append( "share" );
//STRIP001 /*?*/                    aLink60InetObj.Append( "basic" );
//STRIP001 /*?*/                     if( aLink60InetObj != aOrgShareFolder60InetObj )
//STRIP001 /*?*/                         createLibraryLink( aLibName, pImplLib->maStorageURL, pImplLib->mbReadOnly );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     // Move folder if not already done
//STRIP001 /*?*/                     INetURLObject aUserBasicLibFolderInetObj( aUserBasicInetObj );
//STRIP001 /*?*/                    aUserBasicLibFolderInetObj.Append( aLibName );
//STRIP001 /*?*/                     String aLibFolder = aUserBasicLibFolderInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001 /*?*/
//STRIP001 /*?*/                     INetURLObject aUserBasic60LibFolderInetObj( aUserBasic60InetObj );
//STRIP001 /*?*/                    aUserBasic60LibFolderInetObj.Append( aLibName );
//STRIP001 /*?*/                     String aLibFolder60 = aUserBasic60LibFolderInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( mxSFI->isFolder( aLibFolder60 ) && !mxSFI->isFolder( aLibFolder ) )
//STRIP001 /*?*/                         mxSFI->move( aLibFolder60, aLibFolder );
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( aLibName == aStandardStr )
//STRIP001 /*?*/                            maNameContainer.removeByName( aLibName );
//STRIP001 /*?*/
//STRIP001 /*?*/                     // Create library
//STRIP001 /*?*/                     Reference< XNameContainer > xLib = createLibrary( aLibName );
//STRIP001 /*?*/                        SfxLibrary_Impl* pNewLib = static_cast< SfxLibrary_Impl* >( xLib.get() );
//STRIP001 /*?*/                     pNewLib->mbLoaded = false;
//STRIP001 /*?*/                    pNewLib->mbModified = false;
//STRIP001 /*?*/                     checkStorageURL( aLibFolder, pNewLib->maLibInfoFileURL,
//STRIP001 /*?*/                         pNewLib->maStorageURL, pNewLib->maUnexpandedStorageURL );
//STRIP001 /*?*/
//STRIP001 /*?*/                     SotStorageRef xDummyStor;
//STRIP001 /*?*/                     ::xmlscript::LibDescriptor aLibDesc;
//STRIP001 /*?*/                     sal_Bool bReadIndexFile = implLoadLibraryIndexFile
//STRIP001 /*?*/                         ( pNewLib, aLibDesc, xDummyStor, pNewLib->maLibInfoFileURL );
//STRIP001 /*?*/                     implImportLibDescriptor( pNewLib, aLibDesc );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            mxSFI->kill( aFolder60 );
/*?*/         }
/*N*/     }
/*N*/
/*N*/   return sal_True;
/*N*/ }

// Handle maLibInfoFileURL and maStorageURL correctly
/*N*/ void SfxLibraryContainer_Impl::checkStorageURL( const OUString& aSourceURL,
/*N*/     OUString& aLibInfoFileURL, OUString& aStorageURL, OUString& aUnexpandedStorageURL )
/*N*/ {
/*N*/     OUString aExpandedSourceURL = expand_url( aSourceURL );
/*N*/     if( aExpandedSourceURL != aSourceURL )
/*?*/         aUnexpandedStorageURL = aSourceURL;
/*N*/
/*N*/   INetURLObject aInetObj( aExpandedSourceURL );
/*N*/     OUString aExtension = aInetObj.getExtension();
/*N*/     if( aExtension.compareToAscii( "xlb" ) == COMPARE_EQUAL )
/*N*/     {
/*N*/         // URL to xlb file
/*?*/       aLibInfoFileURL = aExpandedSourceURL;
/*?*/         aInetObj.removeSegment();
/*?*/       aStorageURL = aInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         // URL to library folder
/*N*/         aStorageURL = aExpandedSourceURL;
/*N*/       aInetObj.insertName( maInfoFileName, sal_True, INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
/*N*/       aInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xlb") ) );
/*N*/       aLibInfoFileURL = aInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/     }
/*N*/ }

/*N*/ SfxLibrary_Impl* SfxLibraryContainer_Impl::getImplLib( const String& rLibraryName )
/*N*/ {
/*N*/   Any aLibAny = maNameContainer.getByName( rLibraryName ) ;
/*N*/   Reference< XNameAccess > xNameAccess;
/*N*/   aLibAny >>= xNameAccess;
/*N*/   SfxLibrary_Impl* pImplLib = static_cast< SfxLibrary_Impl* >( xNameAccess.get() );
/*N*/     return pImplLib;
/*N*/ }


// Storing with password encryption

// Empty implementation, avoids unneccesary implementation in dlgcont.cxx
/*?*/ sal_Bool SfxLibraryContainer_Impl::implStorePasswordLibrary( SfxLibrary_Impl* pLib,
/*?*/     const OUString& aName, SotStorageRef xStorage )
/*?*/ {
/*?*/     return sal_False;
/*?*/ }

/*?*/ sal_Bool SfxLibraryContainer_Impl::implLoadPasswordLibrary
/*?*/     ( SfxLibrary_Impl* pLib, const OUString& Name, sal_Bool bVerifyPasswordOnly )
/*?*/         throw(WrappedTargetException, RuntimeException)
/*?*/ {
/*?*/     return sal_True;
/*?*/ }


#define EXPAND_PROTOCOL "vnd.sun.star.expand"
#define OUSTR(x) ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM(x) )

/*N*/ OUString SfxLibraryContainer_Impl::createAppLibraryFolder
/*N*/     ( SfxLibrary_Impl* pLib, const OUString& aName )
/*N*/ {
/*N*/   OUString aLibDirPath = pLib->maStorageURL;
/*N*/   if( !aLibDirPath.getLength() )
/*N*/     {
/*?*/       INetURLObject aInetObj( String(maLibraryPath).GetToken(1) );
/*?*/       aInetObj.insertName( aName, sal_True, INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
/*?*/         checkStorageURL( aInetObj.GetMainURL( INetURLObject::NO_DECODE ), pLib->maLibInfoFileURL,
/*?*/             pLib->maStorageURL, pLib->maUnexpandedStorageURL );
/*?*/       aLibDirPath = pLib->maStorageURL;
/*N*/     }
/*N*/
/*N*/   if( !mxSFI->isFolder( aLibDirPath ) )
/*N*/     {
/*N*/       try
/*N*/       {
/*?*/           mxSFI->createFolder( aLibDirPath );
/*N*/         }
/*N*/         catch( Exception& )
/*N*/         {}
/*N*/     }
/*N*/
/*N*/     return aLibDirPath;
/*N*/ }

// Storing
//STRIP001 void SfxLibraryContainer_Impl::implStoreLibrary( SfxLibrary_Impl* pLib,
//STRIP001  const OUString& aName, SotStorageRef xStorage )
//STRIP001 {
//STRIP001  sal_Bool bLink = pLib->mbLink;
//STRIP001  sal_Bool bStorage = xStorage.Is() && !bLink;
//STRIP001
//STRIP001  Sequence< OUString > aElementNames = pLib->getElementNames();
//STRIP001  sal_Int32 nNameCount = aElementNames.getLength();
//STRIP001  const OUString* pNames = aElementNames.getConstArray();
//STRIP001     OUString aLibDirPath;
//STRIP001
//STRIP001  if( bStorage )
//STRIP001  {
//STRIP001      for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001      {
//STRIP001          OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001          OUString aStreamName = aElementName;
//STRIP001          aStreamName += String( RTL_CONSTASCII_USTRINGPARAM(".xml") );
//STRIP001
//STRIP001          Any aElement = pLib->getByName( aElementName );
//STRIP001          if( isLibraryElementValid( aElement ) )
//STRIP001          {
//STRIP001              SotStorageStreamRef xElementStream = xStorage->OpenSotStream
//STRIP001                  ( aStreamName, STREAM_WRITE | STREAM_SHARE_DENYWRITE );
//STRIP001
//STRIP001              if( xElementStream->GetError() == ERRCODE_NONE )
//STRIP001              {
//STRIP001                  String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
//STRIP001                  OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
//STRIP001                  Any aAny;
//STRIP001                  aAny <<= aMime;
//STRIP001                  xElementStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001                     // #87671 Allow encryption
//STRIP001                  aPropName = String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("Encrypted") );
//STRIP001                  aAny <<= sal_True;
//STRIP001                  xElementStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001                  Reference< XOutputStream > xOutput =
//STRIP001                      new utl::OOutputStreamWrapper( *xElementStream );
//STRIP001                  writeLibraryElement( aElement, aElementName, xOutput );
//STRIP001                  xOutput->closeOutput();
//STRIP001
//STRIP001                  xElementStream->Commit();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          // Get Output stream
//STRIP001             aLibDirPath = createAppLibraryFolder( pLib, aName );
//STRIP001
//STRIP001          for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001          {
//STRIP001              OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001              INetURLObject aElementInetObj( aLibDirPath );
//STRIP001              aElementInetObj.insertName( aElementName, sal_False,
//STRIP001                  INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001              aElementInetObj.setExtension( maLibElementFileExtension );
//STRIP001              String aElementPath( aElementInetObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001
//STRIP001              Any aElement = pLib->getByName( aElementName );
//STRIP001              if( isLibraryElementValid( aElement ) )
//STRIP001              {
//STRIP001                  // TODO: Check modified
//STRIP001                  try
//STRIP001                  {
//STRIP001                      if( mxSFI->exists( aElementPath ) )
//STRIP001                          mxSFI->kill( aElementPath );
//STRIP001                      Reference< XOutputStream > xOutput = mxSFI->openFileWrite( aElementPath );
//STRIP001                      writeLibraryElement( aElement, aElementName, xOutput );
//STRIP001                      xOutput->closeOutput();
//STRIP001                     }
//STRIP001                  catch( Exception& )
//STRIP001                     {
//STRIP001                      SfxErrorContext aEc( ERRCTX_SFX_SAVEDOC, aElementPath );
//STRIP001                         ULONG nErrorCode = ERRCODE_IO_GENERAL;
//STRIP001                      ErrorHandler::HandleError( nErrorCode );
//STRIP001                     }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      catch( Exception& )
//STRIP001      //catch( Exception& e )
//STRIP001      {
//STRIP001          // TODO
//STRIP001          //throw e;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void SfxLibraryContainer_Impl::implStoreLibraryIndexFile( SfxLibrary_Impl* pLib,
//STRIP001  const ::xmlscript::LibDescriptor& rLib, SotStorageRef xStorage )
//STRIP001 {
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
//STRIP001  sal_Bool bLink = pLib->mbLink;
//STRIP001  sal_Bool bStorage = xStorage.Is() && !bLink;
//STRIP001
//STRIP001  // Write info file
//STRIP001  Reference< XOutputStream > xOut;
//STRIP001  SotStorageStreamRef xInfoStream;
//STRIP001  if( bStorage )
//STRIP001  {
//STRIP001      OUString aStreamName( maInfoFileName );
//STRIP001      aStreamName += String( RTL_CONSTASCII_USTRINGPARAM("-lb.xml") );
//STRIP001
//STRIP001      xInfoStream = xStorage->OpenSotStream( aStreamName,
//STRIP001          STREAM_WRITE | STREAM_SHARE_DENYWRITE );
//STRIP001
//STRIP001      if( xInfoStream->GetError() == ERRCODE_NONE )
//STRIP001      {
//STRIP001          String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
//STRIP001          OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
//STRIP001          Any aAny;
//STRIP001          aAny <<= aMime;
//STRIP001          xInfoStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001             // #87671 Allow encryption
//STRIP001          aPropName = String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("Encrypted") );
//STRIP001          aAny <<= sal_True;
//STRIP001          xInfoStream->SetProperty( aPropName, aAny );
//STRIP001
//STRIP001          xOut = new utl::OOutputStreamWrapper( *xInfoStream );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Create Output stream
//STRIP001         createAppLibraryFolder( pLib, rLib.aName );
//STRIP001         String aLibInfoPath = pLib->maLibInfoFileURL;
//STRIP001
//STRIP001      try
//STRIP001      {
//STRIP001          if( mxSFI->exists( aLibInfoPath ) )
//STRIP001              mxSFI->kill( aLibInfoPath );
//STRIP001          xOut = mxSFI->openFileWrite( aLibInfoPath );
//STRIP001         }
//STRIP001         catch( Exception& )
//STRIP001         {
//STRIP001          SfxErrorContext aEc( ERRCTX_SFX_SAVEDOC, aLibInfoPath );
//STRIP001             ULONG nErrorCode = ERRCODE_IO_GENERAL;
//STRIP001             ErrorHandler::HandleError( nErrorCode );
//STRIP001         }
//STRIP001
//STRIP001  }
//STRIP001  if( !xOut.is() )
//STRIP001  {
//STRIP001      OSL_ENSURE( 0, "### couln't open output stream\n" );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  Reference< XActiveDataSource > xSource( xHandler, UNO_QUERY );
//STRIP001  xSource->setOutputStream( xOut );
//STRIP001
//STRIP001     xmlscript::exportLibrary( xHandler, rLib );
//STRIP001
//STRIP001  if( xInfoStream.Is() )
//STRIP001      xInfoStream->Commit();
//STRIP001 }


/*N*/ sal_Bool SfxLibraryContainer_Impl::implLoadLibraryIndexFile(  SfxLibrary_Impl* pLib,
/*N*/     ::xmlscript::LibDescriptor& rLib, SotStorageRef xStorage, const OUString& aIndexFileName )
/*N*/ {
/*N*/   Reference< XParser > xParser( mxMSF->createInstance(
/*N*/       OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Parser") ) ), UNO_QUERY );
/*N*/   if( !xParser.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't create sax parser component\n" );
/*N*/       return sal_False;
/*N*/   }
/*N*/
/*N*/   sal_Bool bLink = sal_False;
/*N*/   sal_Bool bStorage = sal_False;
/*N*/     if( pLib )
/*N*/     {
/*N*/       bLink = pLib->mbLink;
/*N*/       bStorage = xStorage.Is() && !bLink;
/*N*/     }
/*N*/
/*N*/   // Read info file
/*N*/   Reference< XInputStream > xInput;
/*N*/   SotStorageStreamRef xInfoStream;
/*N*/   String aLibInfoPath;
/*N*/   if( bStorage )
/*N*/   {
/*?*/       aLibInfoPath = maInfoFileName;
/*?*/       aLibInfoPath += String( RTL_CONSTASCII_USTRINGPARAM("-lb.xml") );
/*?*/
/*?*/       xInfoStream = xStorage->OpenSotStream( aLibInfoPath, STREAM_READ );
/*?*/       if( xInfoStream->GetError() == ERRCODE_NONE )
/*?*/       {
/*?*/           xInput = new utl::OInputStreamWrapper( *xInfoStream );
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Create Input stream
/*N*/         String aLibInfoPath;
/*N*/
/*N*/         if( pLib )
/*N*/         {
/*N*/             createAppLibraryFolder( pLib, rLib.aName );
/*N*/             aLibInfoPath = pLib->maLibInfoFileURL;
/*N*/         }
/*N*/         else
/*?*/             aLibInfoPath = aIndexFileName;
/*N*/
/*N*/       try
/*N*/       {
/*N*/           xInput = mxSFI->openFileRead( aLibInfoPath );
/*N*/       }
/*N*/       catch( Exception& )
/*N*/       {
/*N*/             xInput.clear();
/*N*/           SfxErrorContext aEc( ERRCTX_SFX_LOADBASIC, aLibInfoPath );
/*N*/             ULONG nErrorCode = ERRCODE_IO_GENERAL;
/*N*/             ErrorHandler::HandleError( nErrorCode );
/*N*/       }
/*N*/   }
/*N*/   if( !xInput.is() )
/*N*/   {
/*N*/       // OSL_ENSURE( 0, "### couln't open input stream\n" );
/*N*/       return sal_False;
/*N*/   }
/*N*/
/*N*/
/*N*/   InputSource source;
/*N*/   source.aInputStream = xInput;
/*N*/   source.sSystemId    = aLibInfoPath;
/*N*/
/*N*/   // start parsing
/*N*/   try {
/*N*/       xParser->setDocumentHandler( ::xmlscript::importLibrary( rLib ) );
/*N*/       xParser->parseStream( source );
/*N*/   }
/*N*/   catch( Exception& e )
/*N*/   {
/*N*/       // throw WrappedTargetException( OUString::createFromAscii( "parsing error!\n" ),
/*N*/       //                              Reference< XInterface >(),
/*N*/       //                              makeAny( e ) );
/*N*/       OSL_ENSURE( 0, "Parsing error\n" );
/*N*/       SfxErrorContext aEc( ERRCTX_SFX_LOADBASIC, aLibInfoPath );
/*N*/         ULONG nErrorCode = ERRCODE_IO_GENERAL;
/*N*/         ErrorHandler::HandleError( nErrorCode );
/*N*/       return sal_False;
/*N*/   }
/*N*/
/*N*/     if( !pLib )
/*N*/     {
/*?*/       Reference< XNameContainer > xLib = createLibrary( rLib.aName );
/*?*/       pLib = static_cast< SfxLibrary_Impl* >( xLib.get() );
/*?*/       pLib->mbLoaded = sal_False;
/*?*/         rLib.aStorageURL = aIndexFileName;
/*?*/         checkStorageURL( rLib.aStorageURL, pLib->maLibInfoFileURL, pLib->maStorageURL,
/*?*/             pLib->maUnexpandedStorageURL );
/*?*/
/*?*/         implImportLibDescriptor( pLib, rLib );
/*N*/     }
/*N*/
/*N*/     return sal_True;
/*N*/ }

/*N*/ void SfxLibraryContainer_Impl::implImportLibDescriptor
/*N*/     ( SfxLibrary_Impl* pLib, ::xmlscript::LibDescriptor& rLib )
/*N*/ {
/*N*/     if( !pLib->mbInitialised )
/*N*/     {
/*N*/       sal_Int32 nElementCount = rLib.aElementNames.getLength();
/*N*/       const OUString* pElementNames = rLib.aElementNames.getConstArray();
/*N*/       Any aDummyElement = createEmptyLibraryElement();
/*N*/       for( sal_Int32 i = 0 ; i < nElementCount ; i++ )
/*N*/       {
/*N*/           pLib->maNameContainer.insertByName( pElementNames[i], aDummyElement );
/*N*/       }
/*N*/         pLib->mbPasswordProtected = rLib.bPasswordProtected;
/*N*/         pLib->mbReadOnly = rLib.bReadOnly;
/*N*/         pLib->mbModified = sal_False;
/*N*/
/*N*/         pLib->mbInitialised = sal_True;
/*N*/     }
/*N*/ }


/*N*/ void SfxLibraryContainer_Impl::storeLibraries( sal_Bool bComplete )
/*N*/ {
/*N*/   SotStorageRef xStorage;
/*N*/   storeLibraries_Impl( xStorage, bComplete );
/*N*/ }

/*N*/ void SfxLibraryContainer_Impl::storeLibrariesToStorage( SotStorageRef xStorage )
/*N*/ {
/*N*/   sal_Bool bComplete = sal_True;
/*N*/   storeLibraries_Impl( xStorage, bComplete );
/*N*/ }

// Methods of new XLibraryStorage interface?
/*N*/ void SfxLibraryContainer_Impl::storeLibraries_Impl( SotStorageRef xStorage, sal_Bool bComplete )
/*N*/ {
/*N*/   Sequence< OUString > aNames = maNameContainer.getElementNames();
/*N*/   const OUString* pNames = aNames.getConstArray();
/*N*/   sal_Int32 i, nNameCount = aNames.getLength();
/*N*/
/*N*/   // Don't count libs from shared index file
/*N*/   sal_Int32 nLibsToSave = nNameCount;
/*N*/   for( i = 0 ; i < nNameCount ; i++ )
/*N*/   {
/*N*/         SfxLibrary_Impl* pImplLib = getImplLib( pNames[ i ] );
/*N*/       if( pImplLib->mbSharedIndexFile )
/*N*/           nLibsToSave--;
/*N*/   }
/*N*/     if( !nLibsToSave )
/*N*/         return;
/*N*/
/*N*/   ::xmlscript::LibDescriptorArray* pLibArray = new ::xmlscript::LibDescriptorArray( nLibsToSave );
/*N*/
/*N*/   // Write to storage?
/*N*/   sal_Bool bStorage = xStorage.Is();
/*N*/   SotStorageRef xLibrariesStor;
/*N*/   SotStorageRef xSourceLibrariesStor;
/*N*/   if( bStorage )
/*N*/   {
/*N*/         // Don't write if only empty standard lib exists
/*N*/         if( nNameCount == 1 )
/*N*/         {
/*N*/             // Must be standard lib
/*N*/           Any aLibAny = maNameContainer.getByName( pNames[0] );
/*N*/           Reference< XNameAccess > xNameAccess;
/*N*/           aLibAny >>= xNameAccess;
/*N*/             if( !xNameAccess->hasElements() )
/*N*/                 return;
/*N*/         }
/*N*/
/*?*/       xLibrariesStor = xStorage->OpenUCBStorage( maLibrariesDir, STREAM_WRITE );
/*?*/       if( !xLibrariesStor.Is() || xLibrariesStor->GetError() != ERRCODE_NONE )
/*?*/       {
/*?*/           OSL_ENSURE( 0, "### couln't create libraries sub storage\n" );
/*?*/           return;
/*?*/       }
/*?*/
/*?*/         xSourceLibrariesStor = mxStorage->OpenSotStorage( maLibrariesDir, STREAM_READ | STREAM_NOCREATE );
/*?*/       if( !xSourceLibrariesStor.Is() || xSourceLibrariesStor->GetError() != ERRCODE_NONE )
/*?*/             xSourceLibrariesStor = NULL;
/*N*/   }
/*N*/
/*N*/   int iArray = 0;
/*N*/   for( i = 0 ; i < nNameCount ; i++ )
/*N*/   {
/*N*/         SfxLibrary_Impl* pImplLib = getImplLib( pNames[ i ] );
/*N*/       if( pImplLib->mbSharedIndexFile )
/*N*/           continue;
/*N*/       ::xmlscript::LibDescriptor& rLib = pLibArray->mpLibs[iArray];
/*N*/       rLib.aName = pNames[ i ];
/*N*/       iArray++;
/*N*/
/*N*/       rLib.bLink = pImplLib->mbLink;
/*N*/       rLib.aStorageURL = ( pImplLib->maUnexpandedStorageURL.getLength() ) ?
/*N*/             pImplLib->maUnexpandedStorageURL : pImplLib->maLibInfoFileURL;
/*N*/       rLib.bReadOnly = pImplLib->mbReadOnly;
/*N*/       rLib.bPasswordProtected = pImplLib->mbPasswordProtected;
/*N*/       rLib.aElementNames = pImplLib->getElementNames();
/*N*/
/*N*/       if( pImplLib->mbModified || bComplete )
/*N*/       {
/*N*/             // Can we copy the storage?
/*?*/             if( !mbOldInfoFormat && !pImplLib->mbModified && xSourceLibrariesStor.Is() )
/*?*/             {
/*?*/                 BOOL bRet = xSourceLibrariesStor->CopyTo
/*?*/                     ( rLib.aName, xLibrariesStor, rLib.aName );
/*?*/             }
/*?*/             else
/*?*/             {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                SotStorageRef xLibraryStor;
//STRIP001 /*?*/                if( bStorage )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    xLibraryStor = xLibrariesStor->OpenUCBStorage( rLib.aName, STREAM_WRITE );
//STRIP001 /*?*/                    if( !xLibraryStor.Is() || xLibraryStor->GetError() != ERRCODE_NONE )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        OSL_ENSURE( 0, "### couln't create sub storage for library\n" );
//STRIP001 /*?*/                        return;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                // Maybe lib is not loaded?!
//STRIP001 /*?*/                if( bComplete )
//STRIP001 /*?*/                    loadLibrary( rLib.aName );
//STRIP001 /*?*/
//STRIP001 /*?*/                if( pImplLib->mbPasswordProtected )
//STRIP001 /*?*/                    implStorePasswordLibrary( pImplLib, rLib.aName, xLibraryStor );
//STRIP001 /*?*/                     // TODO: Check return value
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                    implStoreLibrary( pImplLib, rLib.aName, xLibraryStor );
//STRIP001 /*?*/
//STRIP001 /*?*/                 implStoreLibraryIndexFile( pImplLib, rLib, xLibraryStor );
//STRIP001 /*?*/                if( bStorage )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    xLibraryStor->Commit();
//STRIP001 /*?*/                }
/*?*/             }
/*?*/
/*?*/           mbModified = sal_True;
/*?*/           pImplLib->mbModified = sal_False;
/*N*/       }
/*N*/
/*N*/         // For container info ReadOnly refers to mbReadOnlyLink
/*N*/       rLib.bReadOnly = pImplLib->mbReadOnlyLink;
/*N*/   }
/*N*/
/*N*/   if( !mbOldInfoFormat && !mbModified )
/*N*/       return;
/*N*/   mbModified = sal_False;
/*N*/     mbOldInfoFormat = sal_False;
/*N*/
/*N*/   // Write library container info
/*N*/   // Create sax writer
/*N*/   Reference< XExtendedDocumentHandler > xHandler(
/*N*/       mxMSF->createInstance(
/*N*/           OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer") ) ), UNO_QUERY );
/*N*/   if( !xHandler.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't create sax-writer component\n" );
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   // Write info file
/*N*/   Reference< XOutputStream > xOut;
/*N*/   SotStorageStreamRef xInfoStream;
/*N*/   if( bStorage )
/*N*/   {
/*?*/       OUString aStreamName( maInfoFileName );
/*?*/       aStreamName += String( RTL_CONSTASCII_USTRINGPARAM("-lc.xml") );
/*?*/
/*?*/       xInfoStream = xLibrariesStor->OpenSotStream( aStreamName,
/*?*/           STREAM_WRITE | STREAM_SHARE_DENYWRITE );
/*?*/
/*?*/       if( xInfoStream->GetError() == ERRCODE_NONE )
/*?*/       {
/*?*/           String aPropName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("MediaType") ) );
/*?*/           OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
/*?*/           Any aAny;
/*?*/           aAny <<= aMime;
/*?*/           xInfoStream->SetProperty( aPropName, aAny );
/*?*/
/*?*/             // #87671 Allow encryption
/*?*/           aPropName = String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM("Encrypted") );
/*?*/           aAny <<= sal_True;
/*?*/           xInfoStream->SetProperty( aPropName, aAny );
/*?*/
/*?*/           xOut = new utl::OOutputStreamWrapper( *xInfoStream );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Create Output stream
/*N*/       INetURLObject aLibInfoInetObj( String(maLibraryPath).GetToken(1) );
/*N*/       aLibInfoInetObj.insertName( maInfoFileName, sal_True, INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
/*N*/       aLibInfoInetObj.setExtension( OUString( RTL_CONSTASCII_USTRINGPARAM("xlc") ) );
/*N*/       String aLibInfoPath( aLibInfoInetObj.GetMainURL( INetURLObject::NO_DECODE ) );
/*N*/
/*N*/       try
/*N*/       {
/*N*/           if( mxSFI->exists( aLibInfoPath ) )
/*N*/               mxSFI->kill( aLibInfoPath );
/*N*/           xOut = mxSFI->openFileWrite( aLibInfoPath );
/*N*/         }
/*N*/         catch( Exception& )
/*N*/         {
/*?*/             xOut.clear();
/*?*/           SfxErrorContext aEc( ERRCTX_SFX_SAVEDOC, aLibInfoPath );
/*?*/             ULONG nErrorCode = ERRCODE_IO_GENERAL;
/*?*/             ErrorHandler::HandleError( nErrorCode );
/*N*/         }
/*N*/
/*N*/   }
/*N*/   if( !xOut.is() )
/*N*/   {
/*N*/       OSL_ENSURE( 0, "### couln't open output stream\n" );
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   Reference< XActiveDataSource > xSource( xHandler, UNO_QUERY );
/*N*/   xSource->setOutputStream( xOut );
/*N*/
/*N*/   xmlscript::exportLibraryContainer( xHandler, pLibArray );
/*N*/   if( xInfoStream.Is() )
/*?*/       xInfoStream->Commit();
/*N*/   if( xLibrariesStor.Is() )
/*?*/       xLibrariesStor->Commit();
/*N*/
/*N*/   delete pLibArray;
/*N*/ }


// Methods XElementAccess
/*?*/ Type SfxLibraryContainer_Impl::getElementType()
/*?*/   throw(RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); Type aType; return aType;//STRIP001
//STRIP001  return maNameContainer.getElementType();
/*?*/ }

/*?*/ sal_Bool SfxLibraryContainer_Impl::hasElements()
/*?*/   throw(RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  sal_Bool bRet = maNameContainer.hasElements();
//STRIP001  return bRet;
/*?*/ }

// Methods XNameAccess
/*N*/ Any SfxLibraryContainer_Impl::getByName( const OUString& aName )
/*N*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   Any aRetAny = maNameContainer.getByName( aName ) ;
/*N*/   return aRetAny;
/*N*/ }

/*N*/ Sequence< OUString > SfxLibraryContainer_Impl::getElementNames()
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   return maNameContainer.getElementNames();
/*N*/ }

/*N*/ sal_Bool SfxLibraryContainer_Impl::hasByName( const OUString& aName )
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   sal_Bool bRet = maNameContainer.hasByName( aName ) ;
/*N*/   return bRet;
/*N*/ }

// Methods XLibraryContainer
/*N*/ Reference< XNameContainer > SAL_CALL SfxLibraryContainer_Impl::createLibrary( const OUString& Name )
/*N*/       throw(IllegalArgumentException, ElementExistException, RuntimeException)
/*N*/ {
/*N*/   SfxLibrary_Impl* pNewLib = implCreateLibrary();
/*N*/     pNewLib->maLibElementFileExtension = maLibElementFileExtension;
/*N*/   Reference< XNameAccess > xNameAccess = static_cast< XNameAccess* >( pNewLib );
/*N*/   Any aElement;
/*N*/   aElement <<= xNameAccess;
/*N*/   maNameContainer.insertByName( Name, aElement );
/*N*/   mbModified = sal_True;
/*N*/     Reference< XNameContainer > xRet( xNameAccess, UNO_QUERY );
/*N*/   return xRet;
/*N*/ }

/*N*/ Reference< XNameAccess > SAL_CALL SfxLibraryContainer_Impl::createLibraryLink
/*N*/   ( const OUString& Name, const OUString& StorageURL, sal_Bool ReadOnly )
/*N*/       throw(IllegalArgumentException, ElementExistException, RuntimeException)
/*N*/ {
/*N*/   // TODO: Check other reasons to force ReadOnly status
/*N*/   //if( !ReadOnly )
/*N*/   //{
/*N*/   //}
/*N*/
/*N*/     OUString aLibInfoFileURL;
/*N*/     OUString aLibDirURL;
/*N*/     OUString aUnexpandedStorageURL;
/*N*/     checkStorageURL( StorageURL, aLibInfoFileURL, aLibDirURL, aUnexpandedStorageURL );
/*N*/
/*N*/
/*N*/   SfxLibrary_Impl* pNewLib = implCreateLibraryLink( aLibInfoFileURL, aLibDirURL, ReadOnly );
/*N*/     pNewLib->maLibElementFileExtension = maLibElementFileExtension;
/*N*/     pNewLib->maUnexpandedStorageURL = aUnexpandedStorageURL;
/*N*/
/*N*/     OUString aInitFileName;
/*N*/     SotStorageRef xDummyStor;
/*N*/     ::xmlscript::LibDescriptor aLibDesc;
/*N*/     sal_Bool bReadIndexFile = implLoadLibraryIndexFile( pNewLib, aLibDesc, xDummyStor, aInitFileName );
/*N*/     implImportLibDescriptor( pNewLib, aLibDesc );
/*N*/
/*N*/   Reference< XNameAccess > xRet = static_cast< XNameAccess* >( pNewLib );
/*N*/   Any aElement;
/*N*/   aElement <<= xRet;
/*N*/   maNameContainer.insertByName( Name, aElement );
/*N*/   mbModified = sal_True;
/*N*/   return xRet;
/*N*/ }

/*?*/ void SAL_CALL SfxLibraryContainer_Impl::removeLibrary( const OUString& Name )
/*?*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     // Get and hold library before removing
//STRIP001  Any aLibAny = maNameContainer.getByName( Name ) ;
//STRIP001  Reference< XNameAccess > xNameAccess;
//STRIP001  aLibAny >>= xNameAccess;
//STRIP001  SfxLibrary_Impl* pImplLib = static_cast< SfxLibrary_Impl* >( xNameAccess.get() );
//STRIP001  if( pImplLib->mbReadOnly && !pImplLib->mbLink )
//STRIP001      throw IllegalArgumentException();
//STRIP001
//STRIP001     // Remove from container
//STRIP001  maNameContainer.removeByName( Name );
//STRIP001  mbModified = sal_True;
//STRIP001
//STRIP001     // Delete library files, but not for linked libraries
//STRIP001     if( !pImplLib->mbLink )
//STRIP001     {
//STRIP001      if( mxStorage.Is() )
//STRIP001             return;
//STRIP001      Reference< XNameAccess > xNameAccess;
//STRIP001      aLibAny >>= xNameAccess;
//STRIP001      SfxLibrary_Impl* pImplLib = static_cast< SfxLibrary_Impl* >( xNameAccess.get() );
//STRIP001      if( xNameAccess->hasElements() )
//STRIP001      {
//STRIP001          Sequence< OUString > aNames = pImplLib->getElementNames();
//STRIP001          sal_Int32 nNameCount = aNames.getLength();
//STRIP001          const OUString* pNames = aNames.getConstArray();
//STRIP001          for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001          {
//STRIP001              OUString aElementName = pNames[ i ];
//STRIP001                 pImplLib->removeByName( aElementName );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001         // Delete index file
//STRIP001         createAppLibraryFolder( pImplLib, Name );
//STRIP001         String aLibInfoPath = pImplLib->maLibInfoFileURL;
//STRIP001      try
//STRIP001      {
//STRIP001          if( mxSFI->exists( aLibInfoPath ) )
//STRIP001              mxSFI->kill( aLibInfoPath );
//STRIP001         }
//STRIP001         catch( Exception& ) {}
//STRIP001
//STRIP001         // Delete folder if empty
//STRIP001      INetURLObject aInetObj( String(maLibraryPath).GetToken(1) );
//STRIP001      aInetObj.insertName( Name, sal_True, INetURLObject::LAST_SEGMENT,
//STRIP001          sal_True, INetURLObject::ENCODE_ALL );
//STRIP001      OUString aLibDirPath = aInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001      try
//STRIP001      {
//STRIP001          if( mxSFI->isFolder( aLibDirPath ) )
//STRIP001          {
//STRIP001                 Sequence< OUString > aContentSeq = mxSFI->getFolderContents( aLibDirPath, true );
//STRIP001              sal_Int32 nCount = aContentSeq.getLength();
//STRIP001              if( !nCount )
//STRIP001                  mxSFI->kill( aLibDirPath );
//STRIP001          }
//STRIP001         }
//STRIP001         catch( Exception& )
//STRIP001         {
//STRIP001         }
//STRIP001     }
/*?*/ }

/*N*/ sal_Bool SAL_CALL SfxLibraryContainer_Impl::isLibraryLoaded( const OUString& Name )
/*N*/   throw(NoSuchElementException, RuntimeException)
/*N*/ {
/*N*/     SfxLibrary_Impl* pImplLib = getImplLib( Name );
/*N*/   sal_Bool bRet = pImplLib->mbLoaded;
/*N*/   return bRet;
/*N*/ }


/*N*/ void SAL_CALL SfxLibraryContainer_Impl::loadLibrary( const OUString& Name )
/*N*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   Any aLibAny = maNameContainer.getByName( Name ) ;
/*N*/   Reference< XNameAccess > xNameAccess;
/*N*/   aLibAny >>= xNameAccess;
/*N*/   SfxLibrary_Impl* pImplLib = static_cast< SfxLibrary_Impl* >( xNameAccess.get() );
/*N*/
/*N*/     sal_Bool bLoaded = pImplLib->mbLoaded;
/*N*/   pImplLib->mbLoaded = sal_True;
/*N*/   if( !bLoaded && xNameAccess->hasElements() )
/*N*/   {
/*N*/         if( pImplLib->mbPasswordProtected )
/*N*/         {
/*N*/             implLoadPasswordLibrary( pImplLib, Name );
/*N*/             return;
/*N*/         }
/*N*/
/*N*/       sal_Bool bLink = pImplLib->mbLink;
/*N*/       sal_Bool bStorage = mxStorage.Is() && !bLink;
/*N*/
/*N*/       SotStorageRef xLibrariesStor;
/*N*/       SotStorageRef xLibraryStor;
/*N*/       SotStorageStreamRef xElementStream;
/*N*/       if( bStorage )
/*N*/       {
/*?*/             xLibrariesStor = mxStorage->OpenSotStorage( maLibrariesDir, STREAM_READ | STREAM_NOCREATE );
/*?*/           if( xLibrariesStor.Is() && xLibrariesStor->GetError() == ERRCODE_NONE )
/*?*/           {
/*?*/                 xLibraryStor = xLibrariesStor->OpenSotStorage( Name, STREAM_READ | STREAM_NOCREATE );
/*?*/           }
/*?*/           if( !xLibraryStor.Is() || xLibraryStor->GetError() != ERRCODE_NONE )
/*?*/           {
/*?*/               OSL_ENSURE( 0, "### couln't open sub storage for library\n" );
/*?*/               return;
/*?*/           }
/*N*/       }
/*N*/
/*N*/       Sequence< OUString > aNames = pImplLib->getElementNames();
/*N*/       sal_Int32 nNameCount = aNames.getLength();
/*N*/       const OUString* pNames = aNames.getConstArray();
/*N*/       for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
/*N*/       {
/*N*/           OUString aElementName = pNames[ i ];
/*N*/
/*N*/           OUString aFile;
/*N*/           if( bStorage )
/*N*/           {
/*?*/               aFile = aElementName;
/*?*/               aFile += String( RTL_CONSTASCII_USTRINGPARAM(".xml") );
/*?*/
/*?*/               xElementStream = xLibraryStor->OpenSotStream( aFile, STREAM_READ );
/*?*/               if( xElementStream->GetError() != ERRCODE_NONE )
/*?*/               {
/*?*/                   // Check for EA2 document version with wrong extensions
/*?*/                   aFile = aElementName;
/*?*/                   aFile += String( RTL_CONSTASCII_USTRINGPARAM(".") );
/*?*/                   aFile += maLibElementFileExtension;
/*?*/                   xElementStream = xLibraryStor->OpenSotStream( aFile, STREAM_READ );
/*?*/               }
/*?*/
/*?*/               if( !xElementStream.Is() || xElementStream->GetError() != ERRCODE_NONE )
/*?*/               {
/*?*/                   OSL_ENSURE( 0, "### couln't open library element stream\n" );
/*?*/                   return;
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               String aLibDirPath = pImplLib->maStorageURL;
/*N*/               INetURLObject aElementInetObj( aLibDirPath );
/*N*/               aElementInetObj.insertName( aElementName, sal_False,
/*N*/                   INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
/*N*/               aElementInetObj.setExtension( maLibElementFileExtension );
/*N*/               aFile = aElementInetObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/           }
/*N*/
/*N*/           Any aAny = importLibraryElement( aFile, xElementStream );
/*N*/           if( pImplLib->hasByName( aElementName ) )
/*N*/             {
/*N*/                 if( aAny.hasValue() )
/*N*/                   pImplLib->maNameContainer.replaceByName( aElementName, aAny );
/*N*/             }
/*N*/           else
/*N*/             {
/*?*/               pImplLib->maNameContainer.insertByName( aElementName, aAny );
/*N*/             }
/*N*/       }
/*N*/
/*N*/         pImplLib->mbModified = sal_False;
/*N*/   }
/*N*/ }

// Methods XLibraryContainer2
/*?*/ sal_Bool SAL_CALL SfxLibraryContainer_Impl::isLibraryLink( const OUString& Name )
/*?*/     throw (NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001  sal_Bool bRet = pImplLib->mbLink;
//STRIP001  return bRet;
/*?*/ }

/*?*/ OUString SAL_CALL SfxLibraryContainer_Impl::getLibraryLinkURL( const OUString& Name )
/*?*/     throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); OUString aRetStr;return aRetStr;//STRIP001
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001  sal_Bool bLink = pImplLib->mbLink;
//STRIP001  if( !bLink )
//STRIP001      throw IllegalArgumentException();
//STRIP001     OUString aRetStr = pImplLib->maLibInfoFileURL;
//STRIP001     return aRetStr;
/*?*/ }

/*?*/ sal_Bool SAL_CALL SfxLibraryContainer_Impl::isLibraryReadOnly( const OUString& Name )
/*?*/     throw (NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001  sal_Bool bRet = pImplLib->mbReadOnly || (pImplLib->mbLink && pImplLib->mbReadOnlyLink);
//STRIP001  return bRet;
/*?*/ }

/*?*/ void SAL_CALL SfxLibraryContainer_Impl::setLibraryReadOnly( const OUString& Name, sal_Bool bReadOnly )
/*?*/     throw (NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001     SfxLibrary_Impl* pImplLib = getImplLib( Name );
//STRIP001     if( pImplLib->mbLink )
//STRIP001     {
//STRIP001         if( pImplLib->mbReadOnlyLink != bReadOnly )
//STRIP001         {
//STRIP001             pImplLib->mbReadOnlyLink = bReadOnly;
//STRIP001             pImplLib->mbModified = sal_True;
//STRIP001             mbModified = sal_True;
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         if( pImplLib->mbReadOnly != bReadOnly )
//STRIP001         {
//STRIP001          pImplLib->mbReadOnly = bReadOnly;
//STRIP001             pImplLib->mbModified = sal_True;
//STRIP001         }
//STRIP001     }
/*?*/ }

/*?*/ void SAL_CALL SfxLibraryContainer_Impl::renameLibrary( const OUString& Name, const OUString& NewName )
/*?*/     throw (NoSuchElementException, ElementExistException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001  if( maNameContainer.hasByName( NewName ) )
//STRIP001      throw ElementExistException();
//STRIP001
//STRIP001     // Get and hold library before removing
//STRIP001  Any aLibAny = maNameContainer.getByName( Name ) ;
//STRIP001
//STRIP001     // Remove from container
//STRIP001  maNameContainer.removeByName( Name );
//STRIP001  mbModified = sal_True;
//STRIP001
//STRIP001     // Rename library folder, but not for linked libraries
//STRIP001  Reference< XNameAccess > xNameAccess;
//STRIP001  aLibAny >>= xNameAccess;
//STRIP001  SfxLibrary_Impl* pImplLib = static_cast< SfxLibrary_Impl* >( xNameAccess.get() );
//STRIP001     bool bMovedSuccessful = true;
//STRIP001
//STRIP001     // Rename files
//STRIP001     sal_Bool bStorage = mxStorage.Is();
//STRIP001     if( !bStorage && !pImplLib->mbLink )
//STRIP001     {
//STRIP001         bMovedSuccessful = false;
//STRIP001
//STRIP001      OUString aLibDirPath = pImplLib->maStorageURL;
//STRIP001
//STRIP001      INetURLObject aDestInetObj( String(maLibraryPath).GetToken(1) );
//STRIP001      aDestInetObj.insertName( NewName, sal_True, INetURLObject::LAST_SEGMENT,
//STRIP001          sal_True, INetURLObject::ENCODE_ALL );
//STRIP001      OUString aDestDirPath = aDestInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001         // Store new URL
//STRIP001         OUString aLibInfoFileURL = pImplLib->maLibInfoFileURL;
//STRIP001         checkStorageURL( aDestDirPath, pImplLib->maLibInfoFileURL, pImplLib->maStorageURL,
//STRIP001             pImplLib->maUnexpandedStorageURL );
//STRIP001
//STRIP001      try
//STRIP001      {
//STRIP001          if( mxSFI->isFolder( aLibDirPath ) )
//STRIP001          {
//STRIP001              if( !mxSFI->isFolder( aDestDirPath ) )
//STRIP001                  mxSFI->createFolder( aDestDirPath );
//STRIP001
//STRIP001                 // Move index file
//STRIP001              try
//STRIP001              {
//STRIP001                  if( mxSFI->exists( pImplLib->maLibInfoFileURL ) )
//STRIP001                      mxSFI->kill( pImplLib->maLibInfoFileURL );
//STRIP001                  mxSFI->move( aLibInfoFileURL, pImplLib->maLibInfoFileURL );
//STRIP001                 }
//STRIP001              catch( Exception& )
//STRIP001                 {
//STRIP001                 }
//STRIP001
//STRIP001              Sequence< OUString > aElementNames = xNameAccess->getElementNames();
//STRIP001              sal_Int32 nNameCount = aElementNames.getLength();
//STRIP001              const OUString* pNames = aElementNames.getConstArray();
//STRIP001              for( sal_Int32 i = 0 ; i < nNameCount ; i++ )
//STRIP001              {
//STRIP001                  OUString aElementName = pNames[ i ];
//STRIP001
//STRIP001                  INetURLObject aElementInetObj( aLibDirPath );
//STRIP001                  aElementInetObj.insertName( aElementName, sal_False,
//STRIP001                      INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001                  aElementInetObj.setExtension( maLibElementFileExtension );
//STRIP001                  String aElementPath( aElementInetObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001
//STRIP001                  INetURLObject aElementDestInetObj( aDestDirPath );
//STRIP001                  aElementDestInetObj.insertName( aElementName, sal_False,
//STRIP001                      INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001                  aElementDestInetObj.setExtension( maLibElementFileExtension );
//STRIP001                  String aDestElementPath( aElementDestInetObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001
//STRIP001                  try
//STRIP001                  {
//STRIP001                      if( mxSFI->exists( aDestElementPath ) )
//STRIP001                          mxSFI->kill( aDestElementPath );
//STRIP001                      mxSFI->move( aElementPath, aDestElementPath );
//STRIP001                     }
//STRIP001                  catch( Exception& )
//STRIP001                     {
//STRIP001                     }
//STRIP001              }
//STRIP001
//STRIP001                 // Delete folder if empty
//STRIP001                 Sequence< OUString > aContentSeq = mxSFI->getFolderContents( aLibDirPath, true );
//STRIP001              sal_Int32 nCount = aContentSeq.getLength();
//STRIP001              if( !nCount )
//STRIP001                 {
//STRIP001                      mxSFI->kill( aLibDirPath );
//STRIP001                 }
//STRIP001
//STRIP001                 bMovedSuccessful = true;
//STRIP001              pImplLib->mbModified = true;
//STRIP001          }
//STRIP001         }
//STRIP001         catch( Exception& )
//STRIP001         {
//STRIP001             // Restore old library
//STRIP001          maNameContainer.insertByName( Name, aLibAny ) ;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if( bMovedSuccessful )
//STRIP001          maNameContainer.insertByName( NewName, aLibAny ) ;
//STRIP001
/*?*/ }


// Methods XLibraryContainerPassword
/*?*/ sal_Bool SAL_CALL SfxLibraryContainer_Impl::isLibraryPasswordProtected( const OUString& Name )
/*?*/     throw (NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  return bRet;
/*?*/ }

/*?*/ sal_Bool SAL_CALL SfxLibraryContainer_Impl::isLibraryPasswordVerified( const OUString& Name )
/*?*/     throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return NULL;
//STRIP001  throw IllegalArgumentException();
/*?*/ }

/*?*/ sal_Bool SAL_CALL SfxLibraryContainer_Impl::verifyLibraryPassword
/*?*/     ( const OUString& Name, const OUString& Password )
/*?*/         throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); return NULL;
//STRIP001  throw IllegalArgumentException();
/*?*/ }

/*?*/ void SAL_CALL SfxLibraryContainer_Impl::changeLibraryPassword( const OUString& Name,
/*?*/     const OUString& OldPassword, const OUString& NewPassword )
/*?*/         throw (IllegalArgumentException, NoSuchElementException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP");
//STRIP001  throw IllegalArgumentException();
/*?*/ }

// Methods XContainer
/*N*/ void SAL_CALL SfxLibraryContainer_Impl::addContainerListener( const Reference< XContainerListener >& xListener )
/*N*/   throw (RuntimeException)
/*N*/ {
/*N*/   maNameContainer.setEventSource( static_cast< XInterface* >( (OWeakObject*)this ) );
/*N*/   maNameContainer.addContainerListener( xListener );
/*N*/ }

/*N*/ void SAL_CALL SfxLibraryContainer_Impl::removeContainerListener( const Reference< XContainerListener >& xListener )
/*N*/   throw (RuntimeException)
/*N*/ {
/*N*/   maNameContainer.removeContainerListener( xListener );
/*N*/ }


/*N*/ OUString SfxLibraryContainer_Impl::expand_url( const OUString& url )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     if (0 == url.compareToAscii( RTL_CONSTASCII_STRINGPARAM(EXPAND_PROTOCOL ":") ))
/*?*/     {
/*?*/         if( !mxMacroExpander.is() )
/*?*/         {
/*?*/             Reference< XPropertySet > xProps( mxMSF, UNO_QUERY );
/*?*/             OSL_ASSERT( xProps.is() );
/*?*/             if( xProps.is() )
/*?*/             {
/*?*/                 Reference< XComponentContext > xContext;
/*?*/                 xProps->getPropertyValue(
/*?*/                     OUString( RTL_CONSTASCII_USTRINGPARAM("DefaultContext") ) ) >>= xContext;
/*?*/                 OSL_ASSERT( xContext.is() );
/*?*/                 if( xContext.is() )
/*?*/                 {
/*?*/                     Reference< util::XMacroExpander > xExpander;
/*?*/                     xContext->getValueByName(
/*?*/                         OUSTR("/singletons/com.sun.star.util.theMacroExpander") ) >>= xExpander;
/*?*/                     if(! xExpander.is())
/*?*/                     {
/*?*/                         throw DeploymentException(
/*?*/                             OUSTR("no macro expander singleton available!"), Reference< XInterface >() );
/*?*/                     }
/*?*/                     MutexGuard guard( Mutex::getGlobalMutex() );
/*?*/                     if( !mxMacroExpander.is() )
/*?*/                     {
/*?*/                         mxMacroExpander = xExpander;
/*?*/                     }
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/
/*?*/         if( !mxMacroExpander.is() )
/*?*/             return url;
/*?*/
/*?*/         // cut protocol
/*?*/         OUString macro( url.copy( sizeof (EXPAND_PROTOCOL ":") -1 ) );
/*?*/         // decode uric class chars
/*?*/         macro = Uri::decode( macro, rtl_UriDecodeWithCharset, RTL_TEXTENCODING_UTF8 );
/*?*/         // expand macro string
/*?*/         OUString ret( mxMacroExpander->expandMacros( macro ) );
/*?*/         return ret;
/*?*/     }
/*N*/     else
/*N*/     {
/*N*/         return url;
/*N*/     }
/*N*/ }


//============================================================================

// Implementation class SfxLibrary_Impl

// Ctor
/*N*/ SfxLibrary_Impl::SfxLibrary_Impl( Type aType,
/*N*/                                   Reference< XMultiServiceFactory > xMSF,
/*N*/                                   Reference< XSimpleFileAccess > xSFI )
/*N*/   : OComponentHelper( m_mutex )
/*N*/     , mxMSF( xMSF )
/*N*/     , mxSFI( xSFI )
/*N*/   , maNameContainer( aType )
/*N*/   , mbLoaded( sal_True )
/*N*/   , mbModified( sal_True )
/*N*/     , mbInitialised( sal_False )
/*N*/     , mbLink( sal_False )
/*N*/   , mbReadOnly( sal_False )
/*N*/     , mbReadOnlyLink( sal_False )
/*N*/   , mbPasswordProtected( sal_False )
/*N*/   , mbPasswordVerified( sal_False )
/*N*/     , mbDoc50Password( sal_False )
/*N*/   , mbSharedIndexFile( sal_False )
/*N*/ {
/*N*/ }

/*N*/ SfxLibrary_Impl::SfxLibrary_Impl( Type aType,
/*N*/                                   Reference< XMultiServiceFactory > xMSF,
/*N*/                                   Reference< XSimpleFileAccess > xSFI ,
/*N*/                                   const OUString& aLibInfoFileURL,
/*N*/                                   const OUString& aStorageURL, sal_Bool ReadOnly )
/*N*/   : OComponentHelper( m_mutex )
/*N*/     , mxMSF( xMSF )
/*N*/     , mxSFI( xSFI )
/*N*/   , maNameContainer( aType )
/*N*/   , mbLoaded( sal_False )
/*N*/   , mbModified( sal_True )
/*N*/     , mbInitialised( sal_False )
/*N*/     , maLibInfoFileURL( aLibInfoFileURL )
/*N*/   , maStorageURL( aStorageURL )
/*N*/     , mbLink( sal_True )
/*N*/   , mbReadOnly( sal_False )
/*N*/     , mbReadOnlyLink( ReadOnly )
/*N*/   , mbPasswordProtected( sal_False )
/*N*/   , mbPasswordVerified( sal_False )
/*N*/     , mbDoc50Password( sal_False )
/*N*/   , mbSharedIndexFile( sal_False )
/*N*/ {
/*N*/ }


// Methods XInterface
/*N*/ Any SAL_CALL SfxLibrary_Impl::queryInterface( const Type& rType )
/*N*/   throw( RuntimeException )
/*N*/ {
/*N*/   Any aRet;

    /*
    if( mbReadOnly )
    {
        aRet = Any( ::cppu::queryInterface( rType,
            static_cast< XContainer * >( this ),
            static_cast< XNameAccess * >( this ) ) );
    }
    else
    {
    */
/*N*/       aRet = Any( ::cppu::queryInterface( rType,
/*N*/           static_cast< XContainer * >( this ),
/*N*/           static_cast< XNameContainer * >( this ),
/*N*/           static_cast< XNameAccess * >( this ) ) );
/*N*/   //}
/*N*/   if( !aRet.hasValue() )
/*N*/       aRet = OComponentHelper::queryInterface( rType );
/*N*/   return aRet;
/*N*/ }

// Methods XElementAccess
/*?*/ Type SfxLibrary_Impl::getElementType()
/*?*/   throw(RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); Type aType; return aType;
//STRIP001  return maNameContainer.getElementType();
/*?*/ }

/*N*/ sal_Bool SfxLibrary_Impl::hasElements()
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   sal_Bool bRet = maNameContainer.hasElements();
/*N*/   return bRet;
/*N*/ }

// Methods XNameAccess
/*N*/ Any SfxLibrary_Impl::getByName( const OUString& aName )
/*N*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   Any aRetAny = maNameContainer.getByName( aName ) ;
/*N*/   return aRetAny;
/*N*/ }

/*N*/ Sequence< OUString > SfxLibrary_Impl::getElementNames()
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   return maNameContainer.getElementNames();
/*N*/ }

/*N*/ sal_Bool SfxLibrary_Impl::hasByName( const OUString& aName )
/*N*/   throw(RuntimeException)
/*N*/ {
/*N*/   sal_Bool bRet = maNameContainer.hasByName( aName );
/*N*/   return bRet;
/*N*/ }

// Methods XNameReplace
/*?*/ void SfxLibrary_Impl::replaceByName( const OUString& aName, const Any& aElement )
/*?*/   throw(IllegalArgumentException, NoSuchElementException, WrappedTargetException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( mbReadOnly || (mbLink && mbReadOnlyLink) )
//STRIP001         throw RuntimeException();
//STRIP001
//STRIP001  maNameContainer.replaceByName( aName, aElement );
//STRIP001  mbModified = sal_True;
/*?*/ }


// Methods XNameContainer
/*N*/ void SfxLibrary_Impl::insertByName( const OUString& aName, const Any& aElement )
/*N*/   throw(IllegalArgumentException, ElementExistException, WrappedTargetException, RuntimeException)
/*N*/ {
/*N*/   if( mbReadOnly || (mbLink && mbReadOnlyLink) )
/*N*/         throw RuntimeException();
/*N*/
/*N*/   maNameContainer.insertByName( aName, aElement );
/*N*/   mbModified = sal_True;
/*N*/ }

/*?*/ void SfxLibrary_Impl::removeByName( const OUString& Name )
/*?*/   throw(NoSuchElementException, WrappedTargetException, RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( mbReadOnly || (mbLink && mbReadOnlyLink) )
//STRIP001         throw RuntimeException();
//STRIP001
//STRIP001  maNameContainer.removeByName( Name );
//STRIP001  mbModified = sal_True;
//STRIP001
//STRIP001     // Remove element file
//STRIP001  if( maStorageURL.getLength() )
//STRIP001  {
//STRIP001      INetURLObject aElementInetObj( maStorageURL );
//STRIP001      aElementInetObj.insertName( Name, sal_False,
//STRIP001          INetURLObject::LAST_SEGMENT, sal_True, INetURLObject::ENCODE_ALL );
//STRIP001      aElementInetObj.setExtension( maLibElementFileExtension );
//STRIP001      OUString aFile = aElementInetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001      try
//STRIP001      {
//STRIP001          if( mxSFI->exists( aFile ) )
//STRIP001              mxSFI->kill( aFile );
//STRIP001         }
//STRIP001         catch( Exception& )
//STRIP001         {
//STRIP001         }
//STRIP001  }
//STRIP001
/*?*/ }

// XTypeProvider
/*?*/ Sequence< Type > SfxLibrary_Impl::getTypes()
/*?*/   throw( RuntimeException )
/*?*/ {DBG_ASSERT(0, "STRIP"); Sequence< Type > aSequence; return aSequence;//STRIP001
//STRIP001  static OTypeCollection * s_pTypes_NameContainer = 0;
//STRIP001  static OTypeCollection * s_pTypes_NameAccess = 0;
//STRIP001     /*
//STRIP001  if( mbReadOnly )
//STRIP001  {
//STRIP001      if( !s_pTypes_NameAccess )
//STRIP001      {
//STRIP001          MutexGuard aGuard( Mutex::getGlobalMutex() );
//STRIP001          if( !s_pTypes_NameAccess )
//STRIP001          {
//STRIP001              static OTypeCollection s_aTypes_NameAccess(
//STRIP001                  ::getCppuType( (const Reference< XNameAccess > *)0 ),
//STRIP001                  ::getCppuType( (const Reference< XContainer > *)0 ),
//STRIP001                  OComponentHelper::getTypes() );
//STRIP001              s_pTypes_NameAccess = &s_aTypes_NameAccess;
//STRIP001          }
//STRIP001      }
//STRIP001      return s_pTypes_NameAccess->getTypes();
//STRIP001  }
//STRIP001  else
//STRIP001     */
//STRIP001  {
//STRIP001      if( !s_pTypes_NameContainer )
//STRIP001      {
//STRIP001          MutexGuard aGuard( Mutex::getGlobalMutex() );
//STRIP001          if( !s_pTypes_NameContainer )
//STRIP001          {
//STRIP001              static OTypeCollection s_aTypes_NameContainer(
//STRIP001                  ::getCppuType( (const Reference< XNameContainer > *)0 ),
//STRIP001                  ::getCppuType( (const Reference< XContainer > *)0 ),
//STRIP001                  OComponentHelper::getTypes() );
//STRIP001              s_pTypes_NameContainer = &s_aTypes_NameContainer;
//STRIP001          }
//STRIP001      }
//STRIP001      return s_pTypes_NameContainer->getTypes();
//STRIP001  }
/*?*/ }


/*?*/ Sequence< sal_Int8 > SfxLibrary_Impl::getImplementationId()
/*?*/   throw( RuntimeException )
/*?*/ {DBG_ASSERT(0, "STRIP"); Sequence< sal_Int8 > aSequence;return aSequence;//STRIP001
//STRIP001  static OImplementationId * s_pId_NameContainer = 0;
//STRIP001  static OImplementationId * s_pId_NameAccess = 0;
//STRIP001     /*
//STRIP001  if( mbReadOnly )
//STRIP001  {
//STRIP001      if( !s_pId_NameAccess )
//STRIP001      {
//STRIP001          MutexGuard aGuard( Mutex::getGlobalMutex() );
//STRIP001          if( !s_pId_NameAccess )
//STRIP001          {
//STRIP001              static OImplementationId s_aId_NameAccess;
//STRIP001              s_pId_NameAccess = &s_aId_NameAccess;
//STRIP001          }
//STRIP001      }
//STRIP001      return s_pId_NameAccess->getImplementationId();
//STRIP001  }
//STRIP001  else
//STRIP001     */
//STRIP001  {
//STRIP001      if( !s_pId_NameContainer )
//STRIP001      {
//STRIP001          MutexGuard aGuard( Mutex::getGlobalMutex() );
//STRIP001          if( !s_pId_NameContainer )
//STRIP001          {
//STRIP001              static OImplementationId s_aId_NameContainer;
//STRIP001              s_pId_NameContainer = &s_aId_NameContainer;
//STRIP001          }
//STRIP001      }
//STRIP001      return s_pId_NameContainer->getImplementationId();
//STRIP001  }
/*?*/ }


//============================================================================

// Methods XContainer
/*N*/ void SAL_CALL SfxLibrary_Impl::addContainerListener( const Reference< XContainerListener >& xListener )
/*N*/   throw (RuntimeException)
/*N*/ {
/*N*/   maNameContainer.setEventSource( static_cast< XInterface* >( (OWeakObject*)this ) );
/*N*/   maNameContainer.addContainerListener( xListener );
/*N*/ }

/*?*/ void SAL_CALL SfxLibrary_Impl::removeContainerListener( const Reference< XContainerListener >& xListener )
/*?*/   throw (RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  maNameContainer.removeContainerListener( xListener );
/*?*/ }

//============================================================================

