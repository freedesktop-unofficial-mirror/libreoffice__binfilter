/*************************************************************************
 *
 *  $RCSfile: sfx2_sfxbasemodel.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:53 $
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

//________________________________________________________________________________________________________
//  my own includes
//________________________________________________________________________________________________________

#ifndef _SFX_SFXBASEMODEL_HXX_
#include <sfxbasemodel.hxx>
#endif

//________________________________________________________________________________________________________
//  include of other projects
//________________________________________________________________________________________________________

#ifndef _COM_SUN_STAR_VIEW_XPRINTJOB_HPP_
#include <com/sun/star/view/XPrintJob.hpp>
#endif

#ifndef _COM_SUN_STAR_VIEW_XSELECTIONSUPPLIER_HPP_
#include <com/sun/star/view/XSelectionSupplier.hpp>
#endif

#ifndef _COM_SUN_STAR_AWT_SIZE_HPP_
#include <com/sun/star/awt/Size.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_ILLEGALARGUMENTEXCEPTION_HPP_
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_ILLEGALARGUMENTIOEXCEPTION_HPP_
#include <com/sun/star/frame/IllegalArgumentIOException.hpp>
#endif

#ifndef _COM_SUN_STAR_VIEW_PAPERFORMAT_HPP_
#include <com/sun/star/view/PaperFormat.hpp>
#endif

#ifndef _COM_SUN_STAR_VIEW_PAPERORIENTATION_HPP_
#include <com/sun/star/view/PaperOrientation.hpp>
#endif

#ifndef _CPPUHELPER_INTERFACECONTAINER_HXX_
#include <cppuhelper/interfacecontainer.hxx>
#endif

#ifndef _UNOTOOLS_PROCESSFACTORY_HXX
#include <comphelper/processfactory.hxx>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif

#ifndef _COM_SUN_STAR_UCB_NAMECLASH_HPP_
#include <com/sun/star/ucb/NameClash.hpp>
#endif

#ifndef _UNO_MAPPING_HXX_
#include <uno/mapping.hxx>
#endif

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

#ifndef _SFXSTRITEM_HXX
#include <svtools/stritem.hxx>
#endif

#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif

#ifndef _SFXENUMITEM_HXX
#include <svtools/eitem.hxx>
#endif

#include <svtools/sbx.hxx>
#include <basic/sbuno.hxx>

#ifndef _OSL_FILE_HXX_
#include <osl/file.hxx>
#endif

#ifndef _THREAD_HXX_
#include <osl/thread.hxx>
#endif

#ifndef _URLOBJ_HXX_
#include <tools/urlobj.hxx>
#endif

#ifndef _UNOTOOLS_TEMPFILE_HXX_
#include <unotools/tempfile.hxx>
#endif

#ifndef _UNOTOOLS_LOCALFILEHELPER_HXX_
#include <unotools/localfilehelper.hxx>
#endif

#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif

#include <vos/mutex.hxx>
#include <vcl/salctype.hxx>
#include <svtools/printdlg.hxx>

//________________________________________________________________________________________________________
//  includes of my own project
//________________________________________________________________________________________________________

#ifndef _SFX_SFXUNO_HXX
#include <sfxuno.hxx>
#endif

#ifndef _SFX_OBJSHIMP_HXX
#include <objshimp.hxx>
#endif

#ifndef _SFXVIEWFRM_HXX
#include <viewfrm.hxx>
#endif

#ifndef _SFXVIEWSH_HXX
#include <viewsh.hxx>
#endif

#ifndef _SFXDOCFILE_HXX
#include <docfile.hxx>
#endif

#ifndef _SFXDISPATCH_HXX
#include <dispatch.hxx>
#endif

#ifndef _SFXREQUEST_HXX
#include <request.hxx>
#endif

#ifndef _SFX_OBJUNO_HXX
#include <objuno.hxx>
#endif

#ifndef _SFX_PRINTER_HXX
#include <printer.hxx>
#endif

#ifndef _SFX_BASMGR_HXX
#include <basmgr.hxx>
#endif

#ifndef _SFXEVENT_HXX
#include <event.hxx>
#endif

#ifndef _SFX_EVENTSUPPLIER_HXX_
#include <eventsupplier.hxx>
#endif

#ifndef _SFX_EVENTCONF_HXX
#include <evntconf.hxx>
#endif

#ifndef _SFX_INTERNO_HXX
#include <interno.hxx>
#endif

#ifndef _SFX_HRC
#include "sfx.hrc"
#endif


#include "topfrm.hxx"
#include "appdata.hxx"
#include "loadenv.hxx"
#include "docfac.hxx"
#include "fcontnr.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

//________________________________________________________________________________________________________
//  defines
//________________________________________________________________________________________________________

#define SfxIOException_Impl( nErr )             ::com::sun::star::io::IOException()

#define XFRAME                                  ::com::sun::star::frame::XFrame
#define XINTERFACE                              ::com::sun::star::uno::XInterface
#define OMULTITYPEINTERFACECONTAINERHELPER      ::cppu::OMultiTypeInterfaceContainerHelper
#define UNO_QUERY                               ::com::sun::star::uno::UNO_QUERY
#define DISPOSEDEXCEPTION                       ::com::sun::star::lang::DisposedException
#define MAPPING                                 ::com::sun::star::uno::Mapping
#define XSELECTIONSUPPLIER                      ::com::sun::star::view::XSelectionSupplier
#define ANY                                     ::com::sun::star::uno::Any
#define ILLEGALARGUMENTEXCEPTION                ::com::sun::star::lang::IllegalArgumentException
#define ILLEGALARGUMENTIOEXCEPTION              ::com::sun::star::frame::IllegalArgumentIOException
#define DOUBLEINITIALIZATIONEXCEPTION           ::com::sun::star::frame::DoubleInitializationException
#define OINTERFACECONTAINERHELPER               ::cppu::OInterfaceContainerHelper
#define OINTERFACEITERATORHELPER                ::cppu::OInterfaceIteratorHelper
#define SIZE                                    ::com::sun::star::awt::Size
#define PAPERFORMAT                             ::com::sun::star::view::PaperFormat
#define PAPERORIENTATION                        ::com::sun::star::view::PaperOrientation
#define OTYPECOLLECTION                         ::cppu::OTypeCollection
#define OIMPLEMENTATIONID                       ::cppu::OImplementationId
#define MUTEXGUARD                              ::osl::MutexGuard
#define XINDEXCONTAINER                         ::com::sun::star::container::XIndexContainer
#define UNSUPPORTEDFLAVOREXCEPTION              ::com::sun::star::datatransfer::UnsupportedFlavorException
#define XPRINTJOBLISTENER                       ::com::sun::star::view::XPrintJobListener

//________________________________________________________________________________________________________
//  namespaces
//________________________________________________________________________________________________________


// Don't use using ... here, because there are at least two classes with the same name in use

//using namespace ::osl                             ;
//using namespace ::rtl                             ;
//using namespace ::cppu                            ;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
//using namespace ::com::sun::star::container       ;
//using namespace ::com::sun::star::frame           ;
//using namespace ::com::sun::star::document        ;
//using namespace ::com::sun::star::lang            ;
//using namespace ::com::sun::star::util            ;
//using namespace ::com::sun::star::view            ;
//using namespace ::com::sun::star::beans           ;

//________________________________________________________________________________________________________
//  impl. declarations
//________________________________________________________________________________________________________

struct IMPL_SfxBaseModel_DataContainer
{
    SfxObjectShellRef                               m_pObjectShell          ;
    //SfxObjectShellLock                                m_pObjectShellLock      ;
    OUSTRING                                        m_sURL                  ;
    sal_uInt16                                      m_nControllerLockCount  ;
    OMULTITYPEINTERFACECONTAINERHELPER              m_aInterfaceContainer   ;
    REFERENCE< XINTERFACE >                         m_xParent               ;
    REFERENCE< XCONTROLLER >                        m_xCurrent              ;
    REFERENCE< XDOCUMENTINFO >                      m_xDocumentInfo         ;
    REFERENCE< XSTARBASICACCESS >                   m_xStarBasicAccess      ;
    REFERENCE< XNAMEREPLACE >                       m_xEvents               ;
    SEQUENCE< PROPERTYVALUE>                        m_seqArguments          ;
    SEQUENCE< REFERENCE< XCONTROLLER > >            m_seqControllers        ;
    REFERENCE< XINDEXACCESS >                       m_contViewData          ;
       LoadEnvironment_Impl*                            m_pLoader               ;
    sal_Bool                                        m_bLoadDone             ;
    sal_Bool                                        m_bLoadState            ;
    sal_Bool                                        m_bClosed               ;
    sal_Bool                                        m_bClosing              ;
    REFERENCE< com::sun::star::view::XPrintJob>     m_xPrintJob             ;
    ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > m_aPrintOptions;

    IMPL_SfxBaseModel_DataContainer::IMPL_SfxBaseModel_DataContainer(   MUTEX&          aMutex          ,
                                                                        SfxObjectShell* pObjectShell    )
            :   m_pObjectShell          ( pObjectShell  )
//          ,   m_pObjectShellLock      ( pObjectShell  )
            ,   m_sURL                  ( String()      )
            ,   m_nControllerLockCount  ( 0             )
            ,   m_aInterfaceContainer   ( aMutex        )
            ,   m_pLoader               ( NULL          )
            ,   m_bLoadDone             ( sal_False     )
            ,   m_bLoadState            ( sal_False     )
            ,   m_bClosed               ( sal_False     )
            ,   m_bClosing              ( sal_False     )
    {
    }
} ;

/*?*/ SIZE impl_Size_Object2Struct( const Size& aSize )
/*?*/ {
/*?*/   SIZE aReturnValue;
/*?*/
/*?*/   aReturnValue.Width  = aSize.Width()  ;
/*?*/   aReturnValue.Height = aSize.Height() ;
/*?*/
/*?*/   return aReturnValue ;
/*?*/ }

/*?*/ Size impl_Size_Struct2Object( const SIZE& aSize )
/*?*/ {
/*?*/   Size aReturnValue;
/*?*/
/*?*/   aReturnValue.Width()  = aSize.Width  ;
/*?*/   aReturnValue.Height() = aSize.Height ;
/*?*/
/*?*/   return aReturnValue ;
/*?*/ }

extern void* getEnhMetaFileFromGDI_Impl( const GDIMetaFile* pGDIMeta );
extern void* getWinMetaFileFromGDI_Impl( const GDIMetaFile* pGDIMeta, const Size& aMetaSize );
extern SvMemoryStream* getMetaMemStrFromGDI_Impl( const GDIMetaFile* pGDIMeta, sal_uInt32 nFormat );
extern sal_Bool supportsMetaFileHandle_Impl();

//STRIP001 class SfxPrintJob_Impl : public cppu::WeakImplHelper1
//STRIP001 <
//STRIP001  com::sun::star::view::XPrintJob
//STRIP001 >
//STRIP001 {
//STRIP001      IMPL_SfxBaseModel_DataContainer* m_pData;
//STRIP001
//STRIP001 public:
//STRIP001      SfxPrintJob_Impl( IMPL_SfxBaseModel_DataContainer* pData );
//STRIP001      virtual Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL getPrintOptions(  ) throw (RuntimeException);
//STRIP001      virtual Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL getPrinter(  ) throw (RuntimeException);
//STRIP001      virtual Reference< ::com::sun::star::view::XPrintable > SAL_CALL getPrintable(  ) throw (RuntimeException);
//STRIP001      virtual void SAL_CALL cancelJob() throw (RuntimeException);
//STRIP001 };

//STRIP001 SfxPrintJob_Impl::SfxPrintJob_Impl( IMPL_SfxBaseModel_DataContainer* pData )
//STRIP001  : m_pData( pData )
//STRIP001 {
//STRIP001 }

//STRIP001 Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL SfxPrintJob_Impl::getPrintOptions() throw (RuntimeException)
//STRIP001 {
//STRIP001  return m_pData->m_aPrintOptions;
//STRIP001 }

//STRIP001 Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL SfxPrintJob_Impl::getPrinter() throw (RuntimeException)
//STRIP001 {
//STRIP001  Reference < view::XPrintable > xPrintable( m_pData->m_pObjectShell->GetModel(), UNO_QUERY );
//STRIP001  if ( xPrintable.is() )
//STRIP001      return xPrintable->getPrinter();
//STRIP001  return Sequence< ::com::sun::star::beans::PropertyValue >();
//STRIP001 }

//STRIP001 Reference< ::com::sun::star::view::XPrintable > SAL_CALL SfxPrintJob_Impl::getPrintable() throw (RuntimeException)
//STRIP001 {
//STRIP001  Reference < view::XPrintable > xPrintable( m_pData->m_pObjectShell->GetModel(), UNO_QUERY );
//STRIP001  return xPrintable;
//STRIP001 }

//STRIP001 void SAL_CALL SfxPrintJob_Impl::cancelJob() throw (RuntimeException)
//STRIP001 {
//STRIP001  m_pData->m_pObjectShell->Broadcast( SfxPrintingHint( -2, NULL, NULL ) );
//STRIP001 }

//________________________________________________________________________________________________________
//  constructor
//________________________________________________________________________________________________________

/*N*/ SfxBaseModel::SfxBaseModel( SfxObjectShell *pObjectShell )
/*N*/ : IMPL_SfxBaseModel_MutexContainer()
/*N*/ , m_pData( new IMPL_SfxBaseModel_DataContainer( m_aMutex, pObjectShell ) )
/*N*/ {
/*N*/   if ( pObjectShell != NULL )
/*N*/   {
/*N*/       StartListening( *pObjectShell ) ;
/*N*/   }
/*N*/ }

//________________________________________________________________________________________________________
//  destructor
//________________________________________________________________________________________________________

/*N*/ SfxBaseModel::~SfxBaseModel()
/*N*/ {
/*N*/ }

//________________________________________________________________________________________________________
//  XInterface
//________________________________________________________________________________________________________

/*N*/ ANY SAL_CALL SfxBaseModel::queryInterface( const UNOTYPE& rType ) throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // Attention:
/*N*/   //  Don't use mutex or guard in this method!!! Is a method of XInterface.
/*N*/
/*N*/   // Ask for my own supported interfaces ...
/*N*/   ANY aReturn( ::cppu::queryInterface(    rType                                           ,
/*N*/                                           static_cast< XTYPEPROVIDER*         > ( this )  ,
/*N*/                                           static_cast< XCHILD*                > ( this )  ,
/*N*/                                           static_cast< XDOCUMENTINFOSUPPLIER* > ( this )  ,
/*N*/                                           static_cast< XEVENTLISTENER*        > ( this )  ,
/*N*/                                           static_cast< XMODEL*                > ( this )  ,
/*N*/                                           static_cast< XMODIFIABLE*           > ( this )  ,
/*N*/                                             static_cast< XCOMPONENT*            > ( this )  ,
/*N*/                                           static_cast< XPRINTABLE*            > ( this )  ,
/*N*/                                           static_cast< XSTARBASICACCESS*      > ( this )  ,
/*N*/                                             static_cast< XSTORABLE*             > ( this )  ,
/*N*/                                             static_cast< XLOADABLE*             > ( this )  ,
/*N*/                                             static_cast< XCLOSEABLE*            > ( this )  ) );
/*N*/
/*N*/   if ( aReturn.hasValue() == sal_False )
/*N*/   {
/*N*/       aReturn = ::cppu::queryInterface(   rType                                           ,
/*N*/                                             static_cast< XMODIFYBROADCASTER*    > ( this )  ,
/*N*/                                             static_cast< XTRANSFERABLE*    > ( this )  ,
/*N*/                                           static_cast< XPRINTJOBBROADCASTER*  > ( this )  ,
/*N*/                                           static_cast< XCLOSEBROADCASTER*     > ( this )  ,
/*N*/                                             static_cast< XVIEWDATASUPPLIER*     > ( this )  ,
/*N*/                                           static_cast< XEVENTBROADCASTER*     > ( this )  ,
/*N*/                                           static_cast< XEVENTSSUPPLIER*       > ( this )  ) ;
/*N*/   }
/*N*/   // If searched interface supported by this class ...
/*N*/   if ( aReturn.hasValue() == sal_True )
/*N*/   {
/*N*/       // ... return this information.
/*N*/       return aReturn ;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Else; ... ask baseclass for interfaces!
/*N*/       return OWeakObject::queryInterface( rType ) ;
/*N*/   }
/*N*/ }

//________________________________________________________________________________________________________
//  XInterface
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::acquire() throw( )
/*N*/ {
/*N*/   // Attention:
/*N*/   //  Don't use mutex or guard in this method!!! Is a method of XInterface.
/*N*/
/*N*/   // Forward to baseclass
/*N*/   OWeakObject::acquire() ;
/*N*/ }

//________________________________________________________________________________________________________
//  XInterface
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::release() throw( )
/*N*/ {
/*N*/   // Attention:
/*N*/   //  Don't use mutex or guard in this method!!! Is a method of XInterface.
/*N*/
/*N*/   // Forward to baseclass
/*N*/   OWeakObject::release() ;
/*N*/ }

//________________________________________________________________________________________________________
//  XTypeProvider
//________________________________________________________________________________________________________

/*N*/ SEQUENCE< UNOTYPE > SAL_CALL SfxBaseModel::getTypes() throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // Optimize this method !
/*N*/   // We initialize a static variable only one time. And we don't must use a mutex at every call!
/*N*/   // For the first call; pTypeCollection is NULL - for the second call pTypeCollection is different from NULL!
/*N*/   static OTYPECOLLECTION* pTypeCollection = NULL ;
/*N*/
/*N*/   if ( pTypeCollection == NULL )
/*N*/   {
/*N*/       // Ready for multithreading; get global mutex for first call of this method only! see before
/*N*/       MUTEXGUARD aGuard( MUTEX::getGlobalMutex() ) ;
/*N*/
/*N*/       // Control these pointer again ... it can be, that another instance will be faster then these!
/*N*/       if ( pTypeCollection == NULL )
/*N*/       {
/*N*/           // Create a static typecollection ...
/*N*/             static OTYPECOLLECTION aTypeCollectionFirst( ::getCppuType(( const REFERENCE< XTYPEPROVIDER          >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XCHILD                 >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XDOCUMENTINFOSUPPLIER  >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XEVENTLISTENER         >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XMODEL                 >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XMODIFIABLE            >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XPRINTABLE             >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XSTORABLE              >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XLOADABLE              >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XCLOSEABLE             >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XSTARBASICACCESS       >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XEVENTBROADCASTER      >*)NULL ) );
/*N*/
/*N*/             static OTYPECOLLECTION aTypeCollection     ( ::getCppuType(( const REFERENCE< XVIEWDATASUPPLIER      >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XTRANSFERABLE          >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XPRINTJOBBROADCASTER   >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XEVENTSSUPPLIER        >*)NULL ) ,
/*N*/                                                          ::getCppuType(( const REFERENCE< XCLOSEBROADCASTER      >*)NULL ) ,
/*N*/                                                          aTypeCollectionFirst.getTypes()                                   );
/*N*/
/*N*/           // ... and set his address to static pointer!
/*N*/           pTypeCollection = &aTypeCollection ;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return pTypeCollection->getTypes() ;
/*N*/ }

//________________________________________________________________________________________________________
//  XTypeProvider
//________________________________________________________________________________________________________

/*N*/ SEQUENCE< sal_Int8 > SAL_CALL SfxBaseModel::getImplementationId() throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // Create one Id for all instances of this class.
/*N*/   // Use ethernet address to do this! (sal_True)
/*N*/
/*N*/   // Optimize this method
/*N*/   // We initialize a static variable only one time. And we don't must use a mutex at every call!
/*N*/   // For the first call; pID is NULL - for the second call pID is different from NULL!
/*N*/   static OIMPLEMENTATIONID* pID = NULL ;
/*N*/
/*N*/   if ( pID == NULL )
/*N*/   {
/*N*/       // Ready for multithreading; get global mutex for first call of this method only! see before
/*N*/       MUTEXGUARD aGuard( MUTEX::getGlobalMutex() ) ;
/*N*/
/*N*/       // Control these pointer again ... it can be, that another instance will be faster then these!
/*N*/       if ( pID == NULL )
/*N*/       {
/*N*/           // Create a new static ID ...
/*N*/           static OIMPLEMENTATIONID aID( sal_False ) ;
/*N*/           // ... and set his address to static pointer!
/*N*/           pID = &aID ;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return pID->getImplementationId() ;
/*N*/ }

//________________________________________________________________________________________________________
//  XStarBasicAccess
//________________________________________________________________________________________________________

/*N*/ REFERENCE< XSTARBASICACCESS > implGetStarBasicAccess( SfxObjectShell* pObjectShell )
/*N*/ {
/*N*/   REFERENCE< XSTARBASICACCESS > xRet;
/*N*/   if( pObjectShell )
/*N*/   {
/*N*/       BasicManager* pMgr = pObjectShell->GetBasicManager();
/*N*/       xRet = getStarBasicAccess( pMgr );
/*N*/   }
/*N*/   return xRet;
/*N*/ }

/*N*/ REFERENCE< XNAMECONTAINER > SAL_CALL SfxBaseModel::getLibraryContainer() throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   REFERENCE< XSTARBASICACCESS >& rxAccess = m_pData->m_xStarBasicAccess;
/*N*/   if( !rxAccess.is() )
/*N*/       rxAccess = implGetStarBasicAccess( m_pData->m_pObjectShell );
/*N*/
/*N*/   REFERENCE< XNAMECONTAINER > xRet;
/*N*/   if( rxAccess.is() )
/*N*/       xRet = rxAccess->getLibraryContainer();
/*N*/   return xRet;
/*N*/ }

/**___________________________________________________________________________________________________
    @seealso    XStarBasicAccess
*/
/*N*/ void SAL_CALL SfxBaseModel::createLibrary( const OUSTRING& LibName, const OUSTRING& Password,
/*N*/   const OUSTRING& ExternalSourceURL, const OUSTRING& LinkTargetURL )
/*N*/       throw(ELEMENTEXISTEXCEPTION, RUNTIMEEXCEPTION)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   REFERENCE< XSTARBASICACCESS >& rxAccess = m_pData->m_xStarBasicAccess;
/*N*/   if( !rxAccess.is() )
/*N*/       rxAccess = implGetStarBasicAccess( m_pData->m_pObjectShell );
/*N*/
/*N*/   if( rxAccess.is() )
/*N*/       rxAccess->createLibrary( LibName, Password, ExternalSourceURL, LinkTargetURL );
/*N*/ }

/**___________________________________________________________________________________________________
    @seealso    XStarBasicAccess
*/
/*N*/ void SAL_CALL SfxBaseModel::addModule( const OUSTRING& LibraryName, const OUSTRING& ModuleName,
/*N*/   const OUSTRING& Language, const OUSTRING& Source )
/*N*/       throw( NOSUCHELEMENTEXCEPTION, RUNTIMEEXCEPTION)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   REFERENCE< XSTARBASICACCESS >& rxAccess = m_pData->m_xStarBasicAccess;
/*N*/   if( !rxAccess.is() )
/*N*/       rxAccess = implGetStarBasicAccess( m_pData->m_pObjectShell );
/*N*/
/*N*/   if( rxAccess.is() )
/*N*/       rxAccess->addModule( LibraryName, ModuleName, Language, Source );
/*N*/ }

/**___________________________________________________________________________________________________
    @seealso    XStarBasicAccess
*/
/*N*/ void SAL_CALL SfxBaseModel::addDialog( const OUSTRING& LibraryName, const OUSTRING& DialogName,
/*N*/   const ::com::sun::star::uno::Sequence< sal_Int8 >& Data )
/*N*/       throw(NOSUCHELEMENTEXCEPTION, RUNTIMEEXCEPTION)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   REFERENCE< XSTARBASICACCESS >& rxAccess = m_pData->m_xStarBasicAccess;
/*N*/   if( !rxAccess.is() )
/*N*/       rxAccess = implGetStarBasicAccess( m_pData->m_pObjectShell );
/*N*/
/*N*/   if( rxAccess.is() )
/*N*/       rxAccess->addDialog( LibraryName, DialogName, Data );
/*N*/ }


//________________________________________________________________________________________________________
//  XChild
//________________________________________________________________________________________________________

/*N*/ REFERENCE< XINTERFACE > SAL_CALL SfxBaseModel::getParent() throw( RUNTIMEEXCEPTION )
/*N*/ {
/*  #77222#
     AS->MBA: There is one view only at the moment. We don't must search for other parents in other frames ...!?

    if ( !m_pData->m_xParent.is() && m_pData->m_xCurrent.is() )
    {
        // If no parent is set get the parent by view hierarchy
        REFERENCE< XFRAME >  xParentFrame( m_pData->m_xCurrent->getFrame()->getCreator(), UNO_QUERY );
        if ( xParentFrame.is() )
        {
            REFERENCE< XCONTROLLER >  xCtrl( xParentFrame->getController() );
            if ( xCtrl.is() )
                return xCtrl->getModel();
        }
    }
*/
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   return m_pData->m_xParent;
/*N*/ }

//________________________________________________________________________________________________________
//  XChild
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::setParent(const REFERENCE< XINTERFACE >& Parent) throw(NOSUPPORTEXCEPTION, RUNTIMEEXCEPTION)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( Parent.is() && getParent().is() )
/*N*/       // only set parent when no parent is available
/*N*/       throw NOSUPPORTEXCEPTION();
/*N*/
/*N*/   m_pData->m_xParent = Parent;
/*N*/ }

//________________________________________________________________________________________________________
//  XChild
//________________________________________________________________________________________________________

/*N*/ long SfxObjectShellClose_Impl( void* pObj, void* pArg );

/*N*/ void SAL_CALL SfxBaseModel::dispose() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/
/*N*/   // object already disposed?
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if  ( !m_pData->m_bClosed )
/*N*/   {
/*N*/       // gracefully accept wrong dispose calls instead of close call
/*N*/       // and try to make it work (may be really disposed later!)
/*N*/       try
/*N*/       {
/*N*/           close( sal_True );
/*N*/       }
/*N*/       catch ( com::sun::star::util::CloseVetoException& )
/*N*/       {
/*N*/       }
/*N*/
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   EVENTOBJECT aEvent( (XMODEL *)this );
/*N*/   m_pData->m_aInterfaceContainer.disposeAndClear( aEvent );
/*N*/
/*N*/   // is an object shell assigned?
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/   {
/*N*/       // Rekursion vermeiden
/*N*/         SfxObjectShellRef pShell;
/*N*/         //SfxObjectShellLock pShellLock;
/*N*/
/*N*/         {
/*N*/             // am I "ThisComponent" in AppBasic?
/*N*/             StarBASIC* pBas = SFX_APP()->GetBasic_Impl();
/*N*/             if ( pBas && SFX_APP()->Get_Impl()->pThisDocument == m_pData->m_pObjectShell )
/*N*/             {
/*N*/                 // remove "ThisComponent" reference from AppBasic
/*N*/                 SFX_APP()->Get_Impl()->pThisDocument = NULL;
/*N*/                 SbxVariable *pCompVar = pBas->Find( DEFINE_CONST_UNICODE("ThisComponent"), SbxCLASS_OBJECT );
/*N*/                 if ( pCompVar )
/*N*/                 {
/*N*/                     ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xInterface;
/*N*/                     ::com::sun::star::uno::Any aComponent;
/*N*/                     aComponent <<= xInterface;
/*N*/                     pCompVar->PutObject( GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aComponent ) );
/*N*/                 }
/*N*/             }
/*N*/
/*N*/             pShell = m_pData->m_pObjectShell;
/*N*/             //pShellLock = m_pData->m_pObjectShellLock;
/*N*/             EndListening( *pShell );
/*N*/             m_pData->m_pObjectShell = SfxObjectShellRef();
/*N*/           //m_pData->m_pObjectShellLock = SfxObjectShellLock();
/*N*/         }
/*N*/
/*N*/       // Bei dispose keine Speichern-R"uckfrage
/*N*/       if ( pShell->IsEnableSetModified() && !pShell->Get_Impl()->bClosing )
/*N*/           pShell->SetModified( sal_False );
/*N*/       pShell->Get_Impl()->bDisposing = TRUE;
/*N*/         //pShellLock = SfxObjectShellLock();
/*N*/       SfxObjectShellClose_Impl( 0, (void*) pShell );
/*N*/   }
/*N*/
/*N*/   m_pData->m_xCurrent = REFERENCE< XCONTROLLER > ();
/*N*/   m_pData->m_seqControllers = SEQUENCE< REFERENCE< XCONTROLLER > > () ;
/*N*/
/*N*/   DELETEZ(m_pData);
/*N*/ }

//________________________________________________________________________________________________________
//  XChild
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::addEventListener( const REFERENCE< XEVENTLISTENER >& aListener )
/*N*/     throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.addInterface( ::getCppuType((const REFERENCE< XEVENTLISTENER >*)0), aListener );
/*N*/ }

//________________________________________________________________________________________________________
//  XChild
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::removeEventListener( const REFERENCE< XEVENTLISTENER >& aListener )
/*N*/     throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XEVENTLISTENER >*)0), aListener );
/*N*/ }

//________________________________________________________________________________________________________
//  XDOCUMENTINFOSupplier
//________________________________________________________________________________________________________

/*N*/ REFERENCE< XDOCUMENTINFO > SAL_CALL SfxBaseModel::getDocumentInfo() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( !m_pData->m_xDocumentInfo.is() && m_pData->m_pObjectShell.Is() )
/*N*/       ((SfxBaseModel*)this)->m_pData->m_xDocumentInfo = new SfxDocumentInfoObject( m_pData->m_pObjectShell ) ;
/*N*/
/*N*/   return m_pData->m_xDocumentInfo;
/*N*/ }

//________________________________________________________________________________________________________
//  XEVENTLISTENER
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::disposing( const EVENTOBJECT& aObject )
/*N*/     throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/     REFERENCE< XMODIFYLISTENER >  xMod( aObject.Source, UNO_QUERY );
/*N*/     REFERENCE< XEVENTLISTENER >  xListener( aObject.Source, UNO_QUERY );
/*N*/     REFERENCE< XDOCEVENTLISTENER >  xDocListener( aObject.Source, UNO_QUERY );
/*N*/
/*N*/     if ( xMod.is() )
/*N*/         m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XMODIFYLISTENER >*)0), xMod );
/*N*/     else if ( xListener.is() )
/*N*/         m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XEVENTLISTENER >*)0), xListener );
/*N*/     else if ( xDocListener.is() )
/*N*/         m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XDOCEVENTLISTENER >*)0), xListener );
/*
    sal_uInt32 nCount = m_pData->m_seqControllers.getLength();
    for ( sal_uInt32 n = 0; n < nCount; n++ )
    {
        if( m_pData->m_seqControllers.getConstArray()[n] == aObject.Source )
        {
            m_pData->m_seqControllers.getArray()[n] = REFERENCE< XCONTROLLER > () ;
            break;
        }
    }

    if ( m_pData->m_xCurrent.is() && m_pData->m_xCurrent == aObject.Source )
        m_pData->m_xCurrent = REFERENCE< XCONTROLLER > ();
*/
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ sal_Bool SAL_CALL SfxBaseModel::attachResource(   const   OUSTRING&                   rURL    ,
/*N*/                                               const   SEQUENCE< PROPERTYVALUE >&  rArgs   )
/*N*/     throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( rURL.getLength() == 0 && rArgs.getLength() == 1 && rArgs[0].Name.equalsAscii( "SetEmbedded" ) )
/*N*/   {
/*N*/       // allows to set a windowless document to EMBEDDED state
/*N*/       // but _only_ before load() or initNew() methods
/*?*/       if ( m_pData->m_pObjectShell.Is() && !m_pData->m_pObjectShell->GetMedium() )
/*?*/       {
/*?*/           sal_Bool bEmb;
/*?*/           if ( ( rArgs[0].Value >>= bEmb ) && bEmb )
/*?*/               {DBG_ASSERT(0, "STRIP");}//STRIP001 m_pData->m_pObjectShell->SetCreateMode_Impl( SFX_CREATE_MODE_EMBEDDED );
/*?*/       }
/*N*/
/*N*/       return sal_True;
/*N*/   }
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/   {
/*N*/       m_pData->m_sURL = rURL;
/*N*/       m_pData->m_seqArguments = rArgs;
/*N*/
/*N*/       sal_Int32 nNewLength = rArgs.getLength();
/*N*/       for ( sal_Int32 nInd = 0; nInd < rArgs.getLength(); nInd++ )
/*N*/           if ( rArgs[nInd].Name.equalsAscii( "WinExtent" ) )
/*N*/           {
/*N*/               // the document should be resized
/*?*/               SfxInPlaceObject* pInPlaceObj = m_pData->m_pObjectShell->GetInPlaceObject();
/*?*/               if ( pInPlaceObj )
/*?*/               {
/*?*/                   Sequence< sal_Int32 > aSize;
/*?*/                   if ( ( rArgs[nInd].Value >>= aSize ) && aSize.getLength() == 4 )
/*?*/                   {
/*?*/                       Rectangle aTmpRect( aSize[0], aSize[1], aSize[2], aSize[3] );
/*?*/                       aTmpRect = OutputDevice::LogicToLogic( aTmpRect, MAP_100TH_MM, pInPlaceObj->GetMapUnit() );
/*?*/
/*?*/                       pInPlaceObj->SetVisArea( aTmpRect );
/*?*/                   }
/*?*/               }
/*N*/           }
/*N*/
/*N*/       if( m_pData->m_pObjectShell->GetMedium() )
/*N*/       {
/*N*/           SfxAllItemSet aSet( m_pData->m_pObjectShell->GetPool() );
/*N*/           TransformParameters( SID_OPENDOC, rArgs, aSet );
/*N*/           m_pData->m_pObjectShell->GetMedium()->GetItemSet()->Put( aSet );
/*N*/           SFX_ITEMSET_ARG( &aSet, pItem, SfxStringItem, SID_FILTER_NAME, sal_False );
/*N*/           if ( pItem )
/*N*/               m_pData->m_pObjectShell->GetMedium()->SetFilter(
/*N*/                   m_pData->m_pObjectShell->GetFactory().GetFilterContainer()->GetFilter( pItem->GetValue() ) );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return sal_True ;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ OUSTRING SAL_CALL SfxBaseModel::getURL() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   return m_pData->m_sURL ;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ SEQUENCE< PROPERTYVALUE > SAL_CALL SfxBaseModel::getArgs() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/   {
/*N*/       SEQUENCE< PROPERTYVALUE > seqArgsNew;
/*N*/       SEQUENCE< PROPERTYVALUE > seqArgsOld;
/*N*/       SfxAllItemSet aSet( m_pData->m_pObjectShell->GetPool() );
/*N*/
/*N*/       // we need to know which properties are supported by the transformer
/*N*/       // hopefully it is a temporary solution, I guess nonconvertable properties
/*N*/       // should not be supported so then there will be only ItemSet from medium
/*N*/
/*N*/       TransformItems( SID_OPENDOC, *(m_pData->m_pObjectShell->GetMedium()->GetItemSet()), seqArgsNew );
/*N*/       TransformParameters( SID_OPENDOC, m_pData->m_seqArguments, aSet );
/*N*/       TransformItems( SID_OPENDOC, aSet, seqArgsOld );
/*N*/
/*N*/       sal_Int32 nOrgLength = m_pData->m_seqArguments.getLength();
/*N*/       sal_Int32 nOldLength = seqArgsOld.getLength();
/*N*/       sal_Int32 nNewLength = seqArgsNew.getLength();
/*N*/
/*N*/       // "WinExtent" property should be updated always.
/*N*/       // We can store it now to overwrite an old value
/*N*/       // since it is not from ItemSet
/*N*/       SfxInPlaceObject* pInPlaceObj = m_pData->m_pObjectShell->GetInPlaceObject();
/*N*/       if ( pInPlaceObj )
/*N*/       {
/*N*/           Rectangle aTmpRect = pInPlaceObj->GetVisArea( ASPECT_CONTENT );
/*N*/           aTmpRect = OutputDevice::LogicToLogic( aTmpRect, pInPlaceObj->GetMapUnit(), MAP_100TH_MM );
/*N*/
/*N*/           Sequence< sal_Int32 > aSize(4);
/*N*/           aSize[0] = aTmpRect.Left();
/*N*/           aSize[1] = aTmpRect.Top();
/*N*/           aSize[2] = aTmpRect.Right();
/*N*/           aSize[3] = aTmpRect.Bottom();
/*N*/
/*N*/           seqArgsNew.realloc( ++nNewLength );
/*N*/           seqArgsNew[ nNewLength - 1 ].Name = ::rtl::OUString::createFromAscii( "WinExtent" );
/*N*/           seqArgsNew[ nNewLength - 1 ].Value <<= aSize;
/*N*/       }
/*N*/
/*N*/       for ( sal_Int32 nOrg = 0; nOrg < nOrgLength; nOrg++ )
/*N*/       {
/*N*/           sal_Int32 nOldInd = 0;
/*N*/           while ( nOldInd < nOldLength )
/*N*/           {
/*N*/               if ( m_pData->m_seqArguments[nOrg].Name.equals( seqArgsOld[nOldInd].Name ) )
/*N*/                   break;
/*N*/               nOldInd++;
/*N*/           }
/*N*/
/*N*/           if ( nOldInd == nOldLength )
/*N*/           {
/*N*/               // the entity with this name should be new for seqArgsNew
/*N*/               // since it is not supported by transformer
/*N*/
/*N*/               seqArgsNew.realloc( ++nNewLength );
/*N*/               seqArgsNew[ nNewLength - 1 ].Name = m_pData->m_seqArguments[nOrg].Name;
/*N*/               seqArgsNew[ nNewLength - 1 ].Value = m_pData->m_seqArguments[nOrg].Value;
/*N*/           }
/*N*/
/*N*/       }
/*N*/       m_pData->m_seqArguments = seqArgsNew;
/*N*/   }
/*N*/
/*N*/   return m_pData->m_seqArguments ;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::connectController( const REFERENCE< XCONTROLLER >& xController )
/*N*/     throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   sal_uInt32 nOldCount = m_pData->m_seqControllers.getLength();
/*N*/   SEQUENCE< REFERENCE< XCONTROLLER > > aNewSeq( nOldCount + 1 );
/*N*/   for ( sal_uInt32 n = 0; n < nOldCount; n++ )
/*N*/       aNewSeq.getArray()[n] = m_pData->m_seqControllers.getConstArray()[n];
/*N*/   aNewSeq.getArray()[nOldCount] = xController;
/*N*/   m_pData->m_seqControllers = aNewSeq;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::disconnectController( const REFERENCE< XCONTROLLER >& xController ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   sal_uInt32 nOldCount = m_pData->m_seqControllers.getLength();
/*N*/     if ( !nOldCount )
/*N*/         return;
/*N*/
/*N*/   SEQUENCE< REFERENCE< XCONTROLLER > > aNewSeq( nOldCount - 1 );
/*N*/   for ( sal_uInt32 nOld = 0, nNew = 0; nOld < nOldCount; ++nOld )
/*N*/     {
/*N*/       if ( xController != m_pData->m_seqControllers.getConstArray()[nOld] )
/*N*/       {
/*N*/           aNewSeq.getArray()[nNew] = m_pData->m_seqControllers.getConstArray()[nOld];
/*N*/           ++nNew;
/*N*/       }
/*N*/     }
/*N*/
/*N*/   m_pData->m_seqControllers = aNewSeq;
/*N*/
/*N*/   if ( xController == m_pData->m_xCurrent )
/*N*/       m_pData->m_xCurrent = REFERENCE< XCONTROLLER > ();
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::lockControllers() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/   ++m_pData->m_nControllerLockCount ;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::unlockControllers() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/   --m_pData->m_nControllerLockCount ;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ sal_Bool SAL_CALL SfxBaseModel::hasControllersLocked() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/   return ( m_pData->m_nControllerLockCount != 0 ) ;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ REFERENCE< XCONTROLLER > SAL_CALL SfxBaseModel::getCurrentController() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/     // get the last active controller of this model
/*N*/   if ( m_pData->m_xCurrent.is() )
/*N*/       return m_pData->m_xCurrent;
/*N*/
/*N*/   // get the first controller of this model
/*N*/   return m_pData->m_seqControllers.getLength() ? m_pData->m_seqControllers.getConstArray()[0] : m_pData->m_xCurrent;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::setCurrentController( const REFERENCE< XCONTROLLER >& xCurrentController )
/*N*/         throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   m_pData->m_xCurrent = xCurrentController;
/*N*/ }

//________________________________________________________________________________________________________
//  XMODEL
//________________________________________________________________________________________________________

/*N*/ REFERENCE< XINTERFACE > SAL_CALL SfxBaseModel::getCurrentSelection() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/     REFERENCE< XINTERFACE >     xReturn;
/*N*/   REFERENCE< XCONTROLLER >    xController =   getCurrentController()      ;
/*N*/
/*N*/   if ( xController.is() )
/*N*/   {
/*N*/       REFERENCE< XSELECTIONSUPPLIER >  xDocView( xController, UNO_QUERY );
/*N*/       if ( xDocView.is() )
/*N*/       {
/*N*/           ANY xSel = xDocView->getSelection();
/*N*/   // automatisch auskommentiert - Wird von UNO III nicht weiter unterstützt!
/*N*/   //      return xSel.getReflection() == XINTERFACE_getReflection()
/*N*/   //      return xSel.getValueType() == ::getCppuType((const XINTERFACE*)0)
/*N*/   //              ? *(REFERENCE< XINTERFACE > *) xSel.get() : REFERENCE< XINTERFACE > ();
/*N*/           xSel >>= xReturn ;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return xReturn ;
/*N*/ }

//________________________________________________________________________________________________________
//  XModifiable
//________________________________________________________________________________________________________

/*N*/ sal_Bool SAL_CALL SfxBaseModel::isModified() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   return m_pData->m_pObjectShell.Is() ? m_pData->m_pObjectShell->IsModified() : sal_False;
/*N*/ }

//________________________________________________________________________________________________________
//  XModifiable
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::setModified( sal_Bool bModified )
/*N*/         throw (::com::sun::star::beans::PropertyVetoException, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/       m_pData->m_pObjectShell->SetModified(bModified);
/*N*/ }

//________________________________________________________________________________________________________
//  XModifiable
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::addModifyListener(const REFERENCE< XMODIFYLISTENER >& xListener) throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.addInterface( ::getCppuType((const REFERENCE< XMODIFYLISTENER >*)0),xListener );
/*N*/ }

//________________________________________________________________________________________________________
//  XModifiable
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::removeModifyListener(const REFERENCE< XMODIFYLISTENER >& xListener) throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XMODIFYLISTENER >*)0), xListener );
/*N*/ }

//____________________________________________________________________________________________________
//  XCloseable
//____________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::close( sal_Bool bDeliverOwnership ) throw (CLOSEVETOEXCEPTION, RUNTIMEEXCEPTION)
/*N*/ {
/*N*/   ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( !m_pData || m_pData->m_bClosed || m_pData->m_bClosing )
/*N*/       return;
/*N*/
/*N*/     uno::Reference< uno::XInterface > xSelfHold( static_cast< ::cppu::OWeakObject* >(this) );
/*N*/     lang::EventObject             aSource    (static_cast< ::cppu::OWeakObject*>(this));
/*N*/     ::cppu::OInterfaceContainerHelper* pContainer = m_pData->m_aInterfaceContainer.getContainer( ::getCppuType( ( const uno::Reference< util::XCloseListener >*) NULL ) );
/*N*/     if (pContainer!=NULL)
/*N*/   {
/*N*/         ::cppu::OInterfaceIteratorHelper pIterator(*pContainer);
/*N*/         while (pIterator.hasMoreElements())
/*N*/         {
/*N*/             try
/*N*/             {
/*N*/                 ((util::XCloseListener*)pIterator.next())->queryClosing( aSource, bDeliverOwnership );
/*N*/             }
/*N*/             catch( uno::RuntimeException& )
/*N*/             {
/*N*/                 pIterator.remove();
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/
/*N*/   // no own objections against closing!
/*N*/   m_pData->m_bClosing = sal_True;
/*N*/     m_pData->m_pObjectShell->Broadcast( SfxSimpleHint(SFX_HINT_DEINITIALIZING) );
/*N*/     pContainer = m_pData->m_aInterfaceContainer.getContainer( ::getCppuType( ( const uno::Reference< util::XCloseListener >*) NULL ) );
/*N*/     if (pContainer!=NULL)
/*N*/   {
/*N*/         ::cppu::OInterfaceIteratorHelper pCloseIterator(*pContainer);
/*N*/         while (pCloseIterator.hasMoreElements())
/*N*/         {
/*N*/             try
/*N*/             {
/*?*/                 DBG_ASSERT(0, "STRIP");//STRIP001 ((util::XCloseListener*)pCloseIterator.next())->notifyClosing( aSource );
/*?*/             }
/*?*/             catch( uno::RuntimeException& )
/*?*/             {
/*?*/                 pCloseIterator.remove();
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/
/*N*/   m_pData->m_bClosed = sal_True;
/*N*/   m_pData->m_bClosing = sal_False;
/*N*/
/*N*/     dispose();
/*N*/ }

//____________________________________________________________________________________________________
//  XCloseBroadcaster
//____________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::addCloseListener( const REFERENCE< XCLOSELISTENER >& xListener ) throw (RUNTIMEEXCEPTION)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.addInterface( ::getCppuType((const REFERENCE< XCLOSELISTENER >*)0), xListener );
/*N*/ }

//____________________________________________________________________________________________________
//  XCloseBroadcaster
//____________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::removeCloseListener( const REFERENCE< XCLOSELISTENER >& xListener ) throw (RUNTIMEEXCEPTION)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XCLOSELISTENER >*)0), xListener );
/*N*/ }

//________________________________________________________________________________________________________
//  XPrintable
//________________________________________________________________________________________________________

//STRIP001 SEQUENCE< PROPERTYVALUE > SAL_CALL SfxBaseModel::getPrinter() throw(::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      throw DISPOSEDEXCEPTION();
//STRIP001
//STRIP001  // Printer beschaffen
//STRIP001  SfxViewFrame *pViewFrm = m_pData->m_pObjectShell.Is() ?
//STRIP001                              SfxViewFrame::GetFirst( m_pData->m_pObjectShell, 0, sal_False ) : 0;
//STRIP001  if ( !pViewFrm )
//STRIP001      return SEQUENCE< PROPERTYVALUE >();
//STRIP001  const SfxPrinter *pPrinter = pViewFrm->GetViewShell()->GetPrinter(sal_True);
//STRIP001  if ( !pPrinter )
//STRIP001      return SEQUENCE< PROPERTYVALUE >();
//STRIP001
//STRIP001  // Printer Eigenschaften uebertragen
//STRIP001  SEQUENCE< PROPERTYVALUE > aPrinter(8);
//STRIP001
//STRIP001  aPrinter.getArray()[7].Name = DEFINE_CONST_UNICODE( "CanSetPaperSize" );
//STRIP001  aPrinter.getArray()[7].Value <<= ( pPrinter->HasSupport( SUPPORT_SET_PAPERSIZE ) );
//STRIP001
//STRIP001  aPrinter.getArray()[6].Name = DEFINE_CONST_UNICODE( "CanSetPaperFormat" );
//STRIP001  aPrinter.getArray()[6].Value <<= ( pPrinter->HasSupport( SUPPORT_SET_PAPER ) );
//STRIP001
//STRIP001  aPrinter.getArray()[5].Name = DEFINE_CONST_UNICODE( "CanSetPaperOrientation" );
//STRIP001  aPrinter.getArray()[5].Value <<= ( pPrinter->HasSupport( SUPPORT_SET_ORIENTATION ) );
//STRIP001
//STRIP001  aPrinter.getArray()[4].Name = DEFINE_CONST_UNICODE( "IsBusy" );
//STRIP001  aPrinter.getArray()[4].Value <<= ( pPrinter->IsPrinting() );
//STRIP001
//STRIP001  aPrinter.getArray()[3].Name = DEFINE_CONST_UNICODE( "PaperSize" );
//STRIP001  SIZE aSize = impl_Size_Object2Struct(pPrinter->GetPaperSize() );
//STRIP001  aPrinter.getArray()[3].Value <<= aSize;
//STRIP001
//STRIP001  aPrinter.getArray()[2].Name = DEFINE_CONST_UNICODE( "PaperFormat" );
//STRIP001  PAPERFORMAT eFormat = (PAPERFORMAT)pPrinter->GetPaper();
//STRIP001  aPrinter.getArray()[2].Value <<= eFormat;
//STRIP001
//STRIP001  aPrinter.getArray()[1].Name = DEFINE_CONST_UNICODE( "PaperOrientation" );
//STRIP001  PAPERORIENTATION eOrient = (PAPERORIENTATION)pPrinter->GetOrientation();
//STRIP001  aPrinter.getArray()[1].Value <<= eOrient;
//STRIP001
//STRIP001  aPrinter.getArray()[0].Name = DEFINE_CONST_UNICODE( "Name" );
//STRIP001  String sStringTemp = pPrinter->GetName() ;
//STRIP001  aPrinter.getArray()[0].Value <<= ::rtl::OUString( sStringTemp );
//STRIP001
//STRIP001  return aPrinter;
//STRIP001 }

//________________________________________________________________________________________________________
//  XPrintable
//________________________________________________________________________________________________________

//STRIP001 void SfxBaseModel::impl_setPrinter(const SEQUENCE< PROPERTYVALUE >& rPrinter,SfxPrinter*& pPrinter,sal_uInt16& nChangeFlags,SfxViewShell*& pViewSh)
//STRIP001
//STRIP001 {
//STRIP001  // alten Printer beschaffen
//STRIP001  SfxViewFrame *pViewFrm = m_pData->m_pObjectShell.Is() ?
//STRIP001                              SfxViewFrame::GetFirst( m_pData->m_pObjectShell, 0, sal_False ) : 0;
//STRIP001  if ( !pViewFrm )
//STRIP001      return;
//STRIP001  pViewSh = pViewFrm->GetViewShell();
//STRIP001  pPrinter = pViewSh->GetPrinter(sal_True);
//STRIP001  if ( !pPrinter )
//STRIP001      return;
//STRIP001
//STRIP001  // new Printer-Name available?
//STRIP001  nChangeFlags = 0;
//STRIP001     sal_Int32 lDummy;
//STRIP001  for ( int n = 0; n < rPrinter.getLength(); ++n )
//STRIP001  {
//STRIP001      // get Property-Value from printer description
//STRIP001      const PROPERTYVALUE &rProp = rPrinter.getConstArray()[n];
//STRIP001
//STRIP001      // Name-Property?
//STRIP001      if ( rProp.Name.compareToAscii( "Name" ) == 0 )
//STRIP001      {
//STRIP001          OUSTRING sTemp;
//STRIP001             if ( ( rProp.Value >>= sTemp ) == sal_False )
//STRIP001              throw ILLEGALARGUMENTEXCEPTION();
//STRIP001
//STRIP001          String aPrinterName( sTemp ) ;
//STRIP001             pPrinter = new SfxPrinter( pPrinter->GetOptions().Clone(), aPrinterName );
//STRIP001          nChangeFlags = SFX_PRINTER_PRINTER;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  Size aSetPaperSize( 0, 0);
//STRIP001     PAPERFORMAT nPaperFormat = (PAPERFORMAT) PAPER_USER;
//STRIP001  // other properties
//STRIP001  for ( int i = 0; i < rPrinter.getLength(); ++i )
//STRIP001  {
//STRIP001      // get Property-Value from printer description
//STRIP001      const PROPERTYVALUE &rProp = rPrinter.getConstArray()[i];
//STRIP001
//STRIP001      // PaperOrientation-Property?
//STRIP001      if ( rProp.Name.compareToAscii( "PaperOrientation" ) == 0 )
//STRIP001      {
//STRIP001             PAPERORIENTATION eOrient;
//STRIP001             if ( ( rProp.Value >>= eOrient ) == sal_False )
//STRIP001             {
//STRIP001                 if ( ( rProp.Value >>= lDummy ) == sal_False )
//STRIP001                     throw ILLEGALARGUMENTEXCEPTION();
//STRIP001                 eOrient = ( PAPERORIENTATION ) lDummy;
//STRIP001             }
//STRIP001
//STRIP001             pPrinter->SetOrientation( (Orientation) eOrient );
//STRIP001          nChangeFlags |= SFX_PRINTER_CHG_ORIENTATION;
//STRIP001      }
//STRIP001
//STRIP001      // PaperFormat-Property?
//STRIP001      if ( rProp.Name.compareToAscii( "PaperFormat" ) == 0 )
//STRIP001      {
//STRIP001          if ( ( rProp.Value >>= nPaperFormat ) == sal_False )
//STRIP001             {
//STRIP001                 if ( ( rProp.Value >>= lDummy ) == sal_False )
//STRIP001                     throw ILLEGALARGUMENTEXCEPTION();
//STRIP001                 nPaperFormat = ( PAPERFORMAT ) lDummy;
//STRIP001             }
//STRIP001
//STRIP001          pPrinter->SetPaper( (Paper) nPaperFormat );
//STRIP001          nChangeFlags |= SFX_PRINTER_CHG_SIZE;
//STRIP001      }
//STRIP001
//STRIP001      // PaperSize-Property?
//STRIP001      if ( rProp.Name.compareToAscii( "PaperSize" ) == 0 )
//STRIP001      {
//STRIP001          SIZE aTempSize ;
//STRIP001          if ( ( rProp.Value >>= aTempSize ) == sal_False )
//STRIP001          {
//STRIP001              throw ILLEGALARGUMENTEXCEPTION();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aSetPaperSize = impl_Size_Struct2Object(aTempSize);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //os 12.11.98: die PaperSize darf nur gesetzt werden, wenn tatsaechlich
//STRIP001  //PAPER_USER gilt, sonst koennte vom Treiber ein falsches Format gewaehlt werden
//STRIP001     if(nPaperFormat == PAPER_USER && aSetPaperSize.Width())
//STRIP001  {
//STRIP001      //JP 23.09.98 - Bug 56929 - MapMode von 100mm in die am
//STRIP001      //          Device gesetzten umrechnen. Zusaetzlich nur dann
//STRIP001      //          setzen, wenn sie wirklich veraendert wurden.
//STRIP001      aSetPaperSize = pPrinter->LogicToPixel( aSetPaperSize, MAP_100TH_MM );
//STRIP001      if( aSetPaperSize != pPrinter->GetPaperSizePixel() )
//STRIP001      {
//STRIP001          pPrinter->SetPaperSizeUser( pPrinter->PixelToLogic( aSetPaperSize ) );
//STRIP001          nChangeFlags |= SFX_PRINTER_CHG_SIZE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // #96772#: wait until printing is done
//STRIP001     SfxPrinter* pDocPrinter = pViewSh->GetPrinter();
//STRIP001     while ( pDocPrinter->IsPrinting() )
//STRIP001         Application::Yield();
//STRIP001 }

//STRIP001 void SAL_CALL SfxBaseModel::setPrinter(const SEQUENCE< PROPERTYVALUE >& rPrinter)
//STRIP001         throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      throw DISPOSEDEXCEPTION();
//STRIP001
//STRIP001  SfxViewShell* pViewSh = NULL;
//STRIP001  SfxPrinter* pPrinter = NULL;
//STRIP001  sal_uInt16 nChangeFlags = 0;
//STRIP001  impl_setPrinter(rPrinter,pPrinter,nChangeFlags,pViewSh);
//STRIP001  // set new printer
//STRIP001  if ( pViewSh && pPrinter )
//STRIP001      pViewSh->SetPrinter( pPrinter, nChangeFlags );
//STRIP001 }

//________________________________________________________________________________________________________
//  ImplPrintWatch thread for asynchronous printing with moving temp. file to ucb location
//________________________________________________________________________________________________________

/* This implements a thread which will be started to wait for asynchronous
   print jobs to temp. localy files. If they finish we move the temp. files
   to her right locations by using the ucb.
 */
//STRIP001 class ImplUCBPrintWatcher : public ::osl::Thread
//STRIP001 {
//STRIP001     private:
//STRIP001         /// of course we must know the printer which execute the job
//STRIP001         SfxPrinter* m_pPrinter;
//STRIP001         /// this describes the target location for the printed temp file
//STRIP001         String m_sTargetURL;
//STRIP001         /// it holds the temp file alive, till the print job will finish and remove it from disk automaticly if the object die
//STRIP001         ::utl::TempFile* m_pTempFile;
//STRIP001
//STRIP001     public:
//STRIP001         /* initialize this watcher but don't start it */
//STRIP001         ImplUCBPrintWatcher( SfxPrinter* pPrinter, ::utl::TempFile* pTempFile, const String& sTargetURL )
//STRIP001                 : m_pPrinter  ( pPrinter   )
//STRIP001                 , m_sTargetURL( sTargetURL )
//STRIP001                 , m_pTempFile ( pTempFile  )
//STRIP001         {}
//STRIP001
//STRIP001         /* waits for finishing of the print job and moves the temp file afterwards
//STRIP001            Note: Starting of the job is done outside this thread!
//STRIP001            But we have to free some of the given ressources on heap!
//STRIP001          */
//STRIP001         void SAL_CALL run()
//STRIP001         {
//STRIP001             /* SAFE { */
//STRIP001             {
//STRIP001                 ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001                 while( m_pPrinter->IsPrinting() )
//STRIP001                     Application::Yield();
//STRIP001                 m_pPrinter = NULL; // don't delete it! It's borrowed only :-)
//STRIP001             }
//STRIP001             /* } SAFE */
//STRIP001
//STRIP001             // lock for further using of our member isn't neccessary - because
//STRIP001             // we truns alone by defenition. Nobody join for us nor use us ...
//STRIP001             ImplUCBPrintWatcher::moveAndDeleteTemp(&m_pTempFile,m_sTargetURL);
//STRIP001
//STRIP001             // finishing of this run() method will call onTerminate() automaticly
//STRIP001             // kill this thread there!
//STRIP001         }
//STRIP001
//STRIP001         /* nobody wait for this thread. We must kill ourself ...
//STRIP001          */
//STRIP001         void SAL_CALL onTerminated()
//STRIP001         {
//STRIP001             delete this;
//STRIP001         }
//STRIP001
//STRIP001         /* static helper to move the temp. file to the target location by using the ucb
//STRIP001            It's static to be useable from outside too. So it's not realy neccessary to start
//STRIP001            the thread, if finishing of the job was detected outside this thread.
//STRIP001            But it must be called without using a corresponding thread for the given parameter!
//STRIP001          */
//STRIP001         static void moveAndDeleteTemp( ::utl::TempFile** ppTempFile, const String& sTargetURL )
//STRIP001         {
//STRIP001             // move the file
//STRIP001             try
//STRIP001             {
//STRIP001              INetURLObject aSplitter(sTargetURL);
//STRIP001              String        sFileName = aSplitter.getName(
//STRIP001                                          INetURLObject::LAST_SEGMENT,
//STRIP001                                          true,
//STRIP001                                          INetURLObject::DECODE_WITH_CHARSET);
//STRIP001              if (aSplitter.removeSegment() && sFileName.Len()>0)
//STRIP001              {
//STRIP001                  ::ucb::Content aSource(
//STRIP001                          ::rtl::OUString((*ppTempFile)->GetURL()),
//STRIP001                          ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >());
//STRIP001
//STRIP001                  ::ucb::Content aTarget(
//STRIP001                          ::rtl::OUString(aSplitter.GetMainURL(INetURLObject::NO_DECODE)),
//STRIP001                          ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >());
//STRIP001
//STRIP001                  aTarget.transferContent(
//STRIP001                          aSource,
//STRIP001                          ::ucb::InsertOperation_COPY,
//STRIP001                          ::rtl::OUString(sFileName),
//STRIP001                          ::com::sun::star::ucb::NameClash::OVERWRITE);
//STRIP001              }
//STRIP001             }
//STRIP001             catch( ::com::sun::star::ucb::ContentCreationException& ) { DBG_ERROR("content create exception"); }
//STRIP001             catch( ::com::sun::star::ucb::CommandAbortedException&  ) { DBG_ERROR("command abort exception"); }
//STRIP001             catch( ::com::sun::star::uno::RuntimeException&         ) { DBG_ERROR("runtime exception"); }
//STRIP001             catch( ::com::sun::star::uno::Exception&                ) { DBG_ERROR("unknown exception"); }
//STRIP001
//STRIP001             // kill the temp file!
//STRIP001             delete *ppTempFile;
//STRIP001             *ppTempFile = NULL;
//STRIP001         }
//STRIP001 };

//------------------------------------------------

//________________________________________________________________________________________________________
//  XPrintable
//________________________________________________________________________________________________________
/*?*/ void SAL_CALL SfxBaseModel::print(const SEQUENCE< PROPERTYVALUE >& rOptions)
/*?*/         throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/    // object already disposed?
//STRIP001 /*?*/    // object already disposed?
//STRIP001 /*?*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 /*?*/    if ( impl_isDisposed() )
//STRIP001 /*?*/        throw DISPOSEDEXCEPTION();
//STRIP001 /*?*/
//STRIP001 /*?*/    // get view for sfx printing capabilities
//STRIP001 /*?*/    SfxViewFrame *pViewFrm = m_pData->m_pObjectShell.Is() ?
//STRIP001 /*?*/                                SfxViewFrame::GetFirst( m_pData->m_pObjectShell, 0, sal_False ) : 0;
//STRIP001 /*?*/    if ( !pViewFrm )
//STRIP001 /*?*/        return;
//STRIP001 /*?*/    SfxViewShell* pView = pViewFrm->GetViewShell();
//STRIP001 /*?*/    if ( !pView )
//STRIP001 /*?*/        return;
//STRIP001 /*?*/
//STRIP001 /*?*/    SfxAllItemSet aArgs( pView->GetPool() );
//STRIP001 /*?*/     sal_Bool bMonitor = sal_False;
//STRIP001 /*?*/     // We need this information at the end of this method, if we start the vcl printer
//STRIP001 /*?*/     // by executing the slot. Because if it is a ucb relevant URL we must wait for
//STRIP001 /*?*/     // finishing the print job and move the temporary local file by using the ucb
//STRIP001 /*?*/     // to the right location. But in case of no file name is given or it is already
//STRIP001 /*?*/     // a local one we can supress this special handling. Because then vcl makes all
//STRIP001 /*?*/     // right for us.
//STRIP001 /*?*/     String sUcbUrl;
//STRIP001 /*?*/     ::utl::TempFile* pUCBPrintTempFile = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/     sal_Bool bWaitUntilEnd = sal_False;
//STRIP001 /*?*/    for ( int n = 0; n < rOptions.getLength(); ++n )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // get Property-Value from options
//STRIP001 /*?*/        const PROPERTYVALUE &rProp = rOptions.getConstArray()[n];
//STRIP001 /*?*/
//STRIP001 /*?*/        // FileName-Property?
//STRIP001 /*?*/        if ( rProp.Name.compareToAscii( "FileName" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             // unpack th URL and check for a valid and well known protocol
//STRIP001 /*?*/             OUSTRING sTemp;
//STRIP001 /*?*/             if (
//STRIP001 /*?*/                 ( rProp.Value.getValueType()!=::getCppuType((const OUSTRING*)0))  ||
//STRIP001 /*?*/                 (!(rProp.Value>>=sTemp))
//STRIP001 /*?*/                )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/             String        sPath        ;
//STRIP001 /*?*/             String        sURL  (sTemp);
//STRIP001 /*?*/             INetURLObject aCheck(sURL );
//STRIP001 /*?*/             if (aCheck.GetProtocol()==INET_PROT_NOT_VALID)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 // OK - it's not a valid URL. But may it's a simple
//STRIP001 /*?*/                 // system path directly. It will be supported for historical
//STRIP001 /*?*/                 // reasons. Otherwhise we break to much external code ...
//STRIP001 /*?*/                 // We try to convert it to a file URL. If its possible
//STRIP001 /*?*/                 // we put the system path to the item set and let vcl work with it.
//STRIP001 /*?*/                 // No ucb or thread will be neccessary then. In case it couldnt be
//STRIP001 /*?*/                 // converted its not an URL nor a system path. Then we can't accept
//STRIP001 /*?*/                 // this parameter and have to throw an exception.
//STRIP001 /*?*/                 ::rtl::OUString sSystemPath(sTemp);
//STRIP001 /*?*/                 ::rtl::OUString sFileURL          ;
//STRIP001 /*?*/                 if (::osl::FileBase::getFileURLFromSystemPath(sSystemPath,sFileURL)!=::osl::FileBase::E_None)
//STRIP001 /*?*/                     throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/                 aArgs.Put( SfxStringItem(SID_FILE_NAME,sTemp) );
//STRIP001 /*?*/             }
//STRIP001 /*?*/             else
//STRIP001 /*?*/             // It's a valid URL. but now we must know, if it is a local one or not.
//STRIP001 /*?*/             // It's a question of using ucb or not!
//STRIP001 /*?*/             if (::utl::LocalFileHelper::ConvertURLToSystemPath(sURL,sPath))
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 // it's a local file, we can use vcl without special handling
//STRIP001 /*?*/                 // And we have to use the system notation of the incoming URL.
//STRIP001 /*?*/                 // But it into the descriptor and let the slot be executed at
//STRIP001 /*?*/                 // the end of this method.
//STRIP001 /*?*/                 aArgs.Put( SfxStringItem(SID_FILE_NAME,sPath) );
//STRIP001 /*?*/             }
//STRIP001 /*?*/             else
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 // it's an ucb target. So we must use a temp. file for vcl
//STRIP001 /*?*/                 // and move it after printing by using the ucb.
//STRIP001 /*?*/                 // Create a temp file on the heap (because it must delete the
//STRIP001 /*?*/                 // real file on disk automaticly if it die - bt we have to share it with
//STRIP001 /*?*/                 // some other sources ... e.g. the ImplUCBPrintWatcher).
//STRIP001 /*?*/                 // And we put the name of this temp file to the descriptor instead
//STRIP001 /*?*/                 // of the URL. The URL we save for later using seperatly.
//STRIP001 /*?*/                 // Execution of the print job will be done later by executing
//STRIP001 /*?*/                 // a slot ...
//STRIP001 /*?*/                 pUCBPrintTempFile = new ::utl::TempFile();
//STRIP001 /*?*/                 pUCBPrintTempFile->EnableKillingFile();
//STRIP001 /*?*/                 aArgs.Put( SfxStringItem(SID_FILE_NAME,pUCBPrintTempFile->GetFileName()) );
//STRIP001 /*?*/                 sUcbUrl = sURL;
//STRIP001 /*?*/             }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // CopyCount-Property
//STRIP001 /*?*/        else if ( rProp.Name.compareToAscii( "CopyCount" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            sal_Int32 nCopies = 0;
//STRIP001 /*?*/            if ( ( rProp.Value >>= nCopies ) == sal_False )
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/             aArgs.Put( SfxInt16Item( SID_PRINT_COPIES, (USHORT) nCopies ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // Collate-Property
//STRIP001 /*?*/        else if ( rProp.Name.compareToAscii( "Collate" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             sal_Bool bTemp ;
//STRIP001 /*?*/             if ( rProp.Value >>= bTemp )
//STRIP001 /*?*/                 aArgs.Put( SfxBoolItem( SID_PRINT_COLLATE, bTemp ) );
//STRIP001 /*?*/            else
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // Sort-Property
//STRIP001 /*?*/        else if ( rProp.Name.compareToAscii( "Sort" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             sal_Bool bTemp ;
//STRIP001 /*?*/             if( rProp.Value >>= bTemp )
//STRIP001 /*?*/                aArgs.Put( SfxBoolItem( SID_PRINT_SORT, bTemp ) );
//STRIP001 /*?*/            else
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // Pages-Property
//STRIP001 /*?*/        else if ( rProp.Name.compareToAscii( "Pages" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             OUSTRING sTemp;
//STRIP001 /*?*/             if( rProp.Value >>= sTemp )
//STRIP001 /*?*/                aArgs.Put( SfxStringItem( SID_PRINT_PAGES, String( sTemp ) ) );
//STRIP001 /*?*/            else
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // MonitorVisible
//STRIP001 /*?*/        else if ( rProp.Name.compareToAscii( "MonitorVisible" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             if( !(rProp.Value >>= bMonitor) )
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // MonitorVisible
//STRIP001 /*?*/        else if ( rProp.Name.compareToAscii( "Wait" ) == 0 )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             if ( !(rProp.Value >>= bWaitUntilEnd) )
//STRIP001 /*?*/                throw ILLEGALARGUMENTEXCEPTION();
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/     // Execute the print request every time.
//STRIP001 /*?*/     // It doesn'tmatter if it is a real printer used or we print to a local file
//STRIP001 /*?*/     // nor if we print to a temp file and move it afterwards by using the ucb.
//STRIP001 /*?*/     // That will be handled later. see pUCBPrintFile below!
//STRIP001 /*?*/    aArgs.Put( SfxBoolItem( SID_SILENT, !bMonitor ) );
//STRIP001 /*?*/    if ( bWaitUntilEnd )
//STRIP001 /*?*/        aArgs.Put( SfxBoolItem( SID_ASYNCHRON, sal_False ) );
//STRIP001 /*?*/    SfxRequest aReq( SID_PRINTDOC, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_API, pView->GetPool() );
//STRIP001 /*?*/    aReq.SetArgs( aArgs );
//STRIP001 /*?*/    pView->ExecuteSlot( aReq );
//STRIP001 /*?*/
//STRIP001 /*?*/     // Ok - may be execution before has finished (or started!) printing.
//STRIP001 /*?*/     // And may it was a printing to a file.
//STRIP001 /*?*/     // Now we have to check if we can move the file (if neccessary) via ucb to his right location.
//STRIP001 /*?*/     // Cases:
//STRIP001 /*?*/     //  a) printing finished                        => move the file directly and forget the watcher thread
//STRIP001 /*?*/     //  b) printing is asynchron and runs currently => start watcher thread and exit this method
//STRIP001 /*?*/     //                                                 This thread make all neccessary things by itself.
//STRIP001 /*?*/     if (pUCBPrintTempFile!=NULL)
//STRIP001 /*?*/     {
//STRIP001 /*?*/         // a)
//STRIP001 /*?*/         SfxPrinter* pPrinter = pView->GetPrinter();
//STRIP001 /*?*/         if ( ! pPrinter->IsPrinting() )
//STRIP001 /*?*/             ImplUCBPrintWatcher::moveAndDeleteTemp(&pUCBPrintTempFile,sUcbUrl);
//STRIP001 /*?*/         // b)
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // Note: we create(d) some ressource on the heap. (thread and tep file)
//STRIP001 /*?*/             // They will be delected by the thread automaticly if he finish his run() method.
//STRIP001 /*?*/             ImplUCBPrintWatcher* pWatcher = new ImplUCBPrintWatcher( pPrinter, pUCBPrintTempFile, sUcbUrl );
//STRIP001 /*?*/             pWatcher->create();
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
/*?*/ }

//________________________________________________________________________________________________________
//  XStorable
//________________________________________________________________________________________________________

/*N*/ sal_Bool SAL_CALL SfxBaseModel::hasLocation() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   return m_pData->m_pObjectShell.Is() ? m_pData->m_pObjectShell->HasName() : sal_False;
/*N*/ }

//________________________________________________________________________________________________________
//  XStorable
//________________________________________________________________________________________________________

/*N*/ OUSTRING SAL_CALL SfxBaseModel::getLocation() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   return m_pData->m_pObjectShell.Is() ? OUSTRING(m_pData->m_pObjectShell->GetMedium()->GetName()) : m_pData->m_sURL;
/*N*/ }

//________________________________________________________________________________________________________
//  XStorable
//________________________________________________________________________________________________________

/*N*/ sal_Bool SAL_CALL SfxBaseModel::isReadonly() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   return m_pData->m_pObjectShell.Is() ? m_pData->m_pObjectShell->IsReadOnly() : sal_True;
/*N*/ }

//________________________________________________________________________________________________________
//  XStorable
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::store() throw (::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/     {
/*N*/       if ( m_pData->m_pObjectShell->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED )
/*N*/       {
/*N*/           if ( m_pData->m_pObjectShell->DoSave() )
/*N*/               m_pData->m_pObjectShell->DoSaveCompleted();
/*N*/       }
/*N*/       else
/*N*/           m_pData->m_pObjectShell->Save_Impl();
/*N*/     }
/*N*/ }

//________________________________________________________________________________________________________
//  XStorable
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::storeAsURL(   const   OUSTRING&                   rURL    ,
/*N*/                                       const   SEQUENCE< PROPERTYVALUE >&  rArgs   )
/*N*/         throw (::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/   {
/*N*/       impl_store( m_pData->m_pObjectShell, rURL, rArgs, sal_False );
/*N*/
/*N*/       SEQUENCE< PROPERTYVALUE > aSequence ;
/*N*/       TransformItems( SID_OPENDOC, *m_pData->m_pObjectShell->GetMedium()->GetItemSet(), aSequence );
/*N*/       attachResource( rURL, aSequence );
/*N*/   }
/*N*/ }

//________________________________________________________________________________________________________
//  XStorable
//________________________________________________________________________________________________________

/*N*/ void SAL_CALL SfxBaseModel::storeToURL(   const   OUSTRING&                   rURL    ,
/*N*/                                       const   SEQUENCE< PROPERTYVALUE >&  rArgs   )
/*N*/         throw (::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/     {
/*N*/       impl_store( m_pData->m_pObjectShell, rURL, rArgs, sal_True );
/*N*/     }
/*N*/ }

//________________________________________________________________________________________________________
// XLoadable
//________________________________________________________________________________________________________

/*N #dochnoetig# */ void SAL_CALL SfxBaseModel::initNew()
/*N*/       throw (::com::sun::star::frame::DoubleInitializationException,
/*N*/              ::com::sun::star::io::IOException,
/*N*/              ::com::sun::star::uno::RuntimeException,
/*N*/              ::com::sun::star::uno::Exception)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   // the object shell should exist always
/*N*/   DBG_ASSERT( m_pData->m_pObjectShell.Is(), "Model is useless without an ObjectShell" );
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/   {
/*N*/       if( m_pData->m_pObjectShell->GetMedium() )
/*N*/           throw DOUBLEINITIALIZATIONEXCEPTION();
/*N*/
/*N*/       sal_Bool bRes = m_pData->m_pObjectShell->DoInitNew( NULL );
/*N*/       sal_uInt32 nErrCode = m_pData->m_pObjectShell->GetError() ?
/*N*/                                   m_pData->m_pObjectShell->GetError() : ERRCODE_IO_CANTCREATE;
/*N*/       m_pData->m_pObjectShell->ResetError();
/*N*/
/*N*/       if ( !bRes )
/*N*/       {
/*N*/           throw SfxIOException_Impl( nErrCode );
/*N*/       }
/*N*/   }
/*N*/ }

//________________________________________________________________________________________________________
// XLoadable
//________________________________________________________________________________________________________

/*N #dochnoetig# */ void SAL_CALL SfxBaseModel::load(   const SEQUENCE< PROPERTYVALUE >& seqArguments )
/*N*/       throw (::com::sun::star::frame::DoubleInitializationException,
/*N*/                ::com::sun::star::io::IOException,
/*N*/              ::com::sun::star::uno::RuntimeException,
/*N*/              ::com::sun::star::uno::Exception)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   // the object shell should exist always
/*N*/   DBG_ASSERT( m_pData->m_pObjectShell.Is(), "Model is useless without an ObjectShell" );
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() )
/*N*/   {
/*N*/       if( m_pData->m_pObjectShell->GetMedium() )
/*N*/           throw DOUBLEINITIALIZATIONEXCEPTION();
/*N*/
/*N*/       SfxAllItemSet *pParams = new SfxAllItemSet( SFX_APP()->GetPool() );
/*N*/       TransformParameters( SID_OPENDOC, seqArguments, *pParams );
/*N*/
/*N*/       rtl::OUString aFilterName;
/*N*/       SFX_ITEMSET_ARG( pParams, pFilterNameItem, SfxStringItem, SID_FILTER_NAME, sal_False );
/*N*/       if( pFilterNameItem )
/*N*/           aFilterName = pFilterNameItem->GetValue();
/*N*/
/*N*/       if( !aFilterName.getLength() )
/*N*/           throw ILLEGALARGUMENTIOEXCEPTION();
/*N*/
/*N*/       pParams->Put( SfxBoolItem( SID_VIEW, sal_False ) );
/*N*/       pParams->Put( SfxObjectShellItem( SID_OBJECTSHELL, m_pData->m_pObjectShell ) );
/*N*/
/*N*/           // create LoadEnvironment and set link for callback when it is finished
/*N*/           m_pData->m_pLoader = LoadEnvironment_Impl::Create( *pParams, TRUE );
/*N*/           m_pData->m_pLoader->AddRef();
/*N*/           m_pData->m_pLoader->SetDoneLink( LINK( this, SfxBaseModel, LoadDone_Impl ) );
/*N*/
/*N*/         m_pData->m_bLoadDone = sal_False;
/*N*/         m_pData->m_pLoader->Start();
/*N*/
/*N*/           // wait for callback
/*N*/           while( m_pData->m_bLoadDone == sal_False )
/*N*/               Application::Yield();
/*N*/
/*N*/       m_pData->m_pLoader->ReleaseRef();
/*N*/       m_pData->m_pLoader = NULL;
/*N*/       DELETEZ( pParams );
/*N*/
/*N*/       sal_uInt32 nErrCode = m_pData->m_pObjectShell->GetError() ?
/*N*/                               m_pData->m_pObjectShell->GetError() : ERRCODE_IO_CANTREAD;
/*N*/       m_pData->m_pObjectShell->ResetError();
/*
         // remove lock without closing (it is set in the LoadEnvironment, because the document
         // is loaded in a hidden mode)
         m_pData->m_pObjectShell->RemoveOwnerLock();
*/
/*N*/       if ( !m_pData->m_bLoadState )
/*N*/       {
/*N*/           throw SfxIOException_Impl( nErrCode );
/*N*/       }
/*N*/   }
/*N*/ }

/*N #dochnoetig# */ IMPL_LINK( SfxBaseModel, LoadDone_Impl, void*, pVoid )
/*N*/ {
/*N*/     DBG_ASSERT( m_pData->m_pLoader, "No Loader created, but LoadDone ?!" );
/*N*/
/*N*/     if ( m_pData->m_pLoader->GetError() )
/*N*/     {
/*N*/       m_pData->m_bLoadDone  = sal_True ;
/*N*/       m_pData->m_bLoadState = sal_False;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/       m_pData->m_bLoadDone  = sal_True;
/*N*/       m_pData->m_bLoadState = sal_True;
/*N*/     }
/*N*/
/*N*/     return NULL;
/*N*/ }

//________________________________________________________________________________________________________
// XTransferable
//________________________________________________________________________________________________________

/*?*/ ANY SAL_CALL SfxBaseModel::getTransferData( const DATAFLAVOR& aFlavor )
/*?*/       throw (::com::sun::star::datatransfer::UnsupportedFlavorException,
/*?*/              ::com::sun::star::io::IOException,
/*?*/              ::com::sun::star::uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); ANY aAny; return aAny;//STRIP001
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      throw DISPOSEDEXCEPTION();
//STRIP001
//STRIP001  ANY aAny;
//STRIP001
//STRIP001  if ( m_pData->m_pObjectShell.Is() )
//STRIP001  {
//STRIP001      if ( aFlavor.MimeType.equalsAscii( "application/x-openoffice;windows_formatname=\"GDIMetaFile\"" ) )
//STRIP001      {
//STRIP001          if ( aFlavor.DataType == getCppuType( (const Sequence< sal_Int8 >*) 0 ) )
//STRIP001          {
//STRIP001              GDIMetaFile* pMetaFile = m_pData->m_pObjectShell->GetPreviewMetaFile( sal_True );
//STRIP001
//STRIP001              if ( pMetaFile )
//STRIP001              {
//STRIP001                  SvMemoryStream aMemStm( 65535, 65535 );
//STRIP001
//STRIP001                  pMetaFile->Write( aMemStm );
//STRIP001                  delete pMetaFile;
//STRIP001                  aAny <<= Sequence< sal_Int8 >( reinterpret_cast< const sal_Int8* >( aMemStm.GetData() ),
//STRIP001                                                  aMemStm.Seek( STREAM_SEEK_TO_END ) );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              throw UNSUPPORTEDFLAVOREXCEPTION();
//STRIP001      }
//STRIP001      else if ( aFlavor.MimeType.equalsAscii( "application/x-openoffice;windows_formatname=\"Image EMF\"" ) )
//STRIP001      {
//STRIP001          if ( aFlavor.DataType == getCppuType( (const Sequence< sal_Int8 >*) 0 ) )
//STRIP001          {
//STRIP001              GDIMetaFile* pMetaFile = m_pData->m_pObjectShell->GetPreviewMetaFile( sal_True );
//STRIP001
//STRIP001              if ( pMetaFile )
//STRIP001              {
//STRIP001                  SvMemoryStream* pStream = getMetaMemStrFromGDI_Impl( pMetaFile, CVT_EMF );
//STRIP001                  delete pMetaFile;
//STRIP001                  if ( pStream )
//STRIP001                  {
//STRIP001                      aAny <<= Sequence< sal_Int8 >( reinterpret_cast< const sal_Int8* >( pStream->GetData() ),
//STRIP001                                                      pStream->Seek( STREAM_SEEK_TO_END ) );
//STRIP001                      delete pStream;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else if ( supportsMetaFileHandle_Impl()
//STRIP001            && aFlavor.DataType == getCppuType( (const sal_uInt64*) 0 ) )
//STRIP001          {
//STRIP001              GDIMetaFile* pMetaFile = m_pData->m_pObjectShell->GetPreviewMetaFile( sal_True );
//STRIP001
//STRIP001              if ( pMetaFile )
//STRIP001              {
//STRIP001                  aAny <<= reinterpret_cast< const sal_uInt64 >( getEnhMetaFileFromGDI_Impl( pMetaFile ) );
//STRIP001                  delete pMetaFile;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              throw UNSUPPORTEDFLAVOREXCEPTION();
//STRIP001      }
//STRIP001      else if ( aFlavor.MimeType.equalsAscii( "application/x-openoffice;windows_formatname=\"Image WMF\"" ) )
//STRIP001      {
//STRIP001          if ( aFlavor.DataType == getCppuType( (const Sequence< sal_Int8 >*) 0 ) )
//STRIP001          {
//STRIP001              GDIMetaFile* pMetaFile = m_pData->m_pObjectShell->GetPreviewMetaFile( sal_True );
//STRIP001
//STRIP001              if ( pMetaFile )
//STRIP001              {
//STRIP001                  SvMemoryStream* pStream = getMetaMemStrFromGDI_Impl( pMetaFile, CVT_WMF );
//STRIP001                  delete pMetaFile;
//STRIP001
//STRIP001                  if ( pStream )
//STRIP001                  {
//STRIP001                      aAny <<= Sequence< sal_Int8 >( reinterpret_cast< const sal_Int8* >( pStream->GetData() ),
//STRIP001                                                      pStream->Seek( STREAM_SEEK_TO_END ) );
//STRIP001                      delete pStream;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else if ( supportsMetaFileHandle_Impl()
//STRIP001            && aFlavor.DataType == getCppuType( (const sal_uInt64*) 0 ) )
//STRIP001          {
//STRIP001              // means HGLOBAL handler to memory storage containing METAFILEPICT structure
//STRIP001
//STRIP001              GDIMetaFile* pMetaFile = m_pData->m_pObjectShell->GetPreviewMetaFile( sal_True );
//STRIP001
//STRIP001              if ( pMetaFile )
//STRIP001              {
//STRIP001                  Size aMetaSize = pMetaFile->GetPrefSize();
//STRIP001                  aAny <<= reinterpret_cast< const sal_uInt64 >( getWinMetaFileFromGDI_Impl( pMetaFile, aMetaSize ) );
//STRIP001
//STRIP001                  delete pMetaFile;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              throw UNSUPPORTEDFLAVOREXCEPTION();
//STRIP001      }
//STRIP001      else
//STRIP001          throw UNSUPPORTEDFLAVOREXCEPTION();
//STRIP001  }
//STRIP001
//STRIP001  return aAny;
/*?*/ }

//________________________________________________________________________________________________________
// XTransferable
//________________________________________________________________________________________________________


/*?*/ SEQUENCE< DATAFLAVOR > SAL_CALL SfxBaseModel::getTransferDataFlavors()
/*?*/       throw (::com::sun::star::uno::RuntimeException)
/*?*/ {DBG_ASSERT(0, "STRIP"); SEQUENCE< DATAFLAVOR > aDATAFLAVOR(0); return aDATAFLAVOR;//STRIP001
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      throw DISPOSEDEXCEPTION();
//STRIP001
//STRIP001  sal_Int32 nSuppFlavors = supportsMetaFileHandle_Impl() ? 5 : 3;
//STRIP001  SEQUENCE< DATAFLAVOR > aFlavorSeq( nSuppFlavors );
//STRIP001
//STRIP001  aFlavorSeq[0].MimeType =
//STRIP001      ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "application/x-openoffice;windows_formatname=\"GDIMetaFile\"" ) );
//STRIP001  aFlavorSeq[0].HumanPresentableName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "GDIMetaFile" ) );
//STRIP001  aFlavorSeq[0].DataType = getCppuType( (const Sequence< sal_Int8 >*) 0 );
//STRIP001
//STRIP001  aFlavorSeq[1].MimeType =
//STRIP001      ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "application/x-openoffice;windows_formatname=\"Image EMF\"" ) );
//STRIP001  aFlavorSeq[1].HumanPresentableName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Enhanced Windows MetaFile" ) );
//STRIP001  aFlavorSeq[1].DataType = getCppuType( (const Sequence< sal_Int8 >*) 0 );
//STRIP001
//STRIP001  aFlavorSeq[2].MimeType =
//STRIP001      ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "application/x-openoffice;windows_formatname=\"Image WMF\"" ) );
//STRIP001  aFlavorSeq[2].HumanPresentableName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Windows MetaFile" ) );
//STRIP001  aFlavorSeq[2].DataType = getCppuType( (const Sequence< sal_Int8 >*) 0 );
//STRIP001
//STRIP001  if ( nSuppFlavors == 5 )
//STRIP001  {
//STRIP001      aFlavorSeq[3].MimeType =
//STRIP001          ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "application/x-openoffice;windows_formatname=\"Image EMF\"" ) );
//STRIP001      aFlavorSeq[3].HumanPresentableName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Enhanced Windows MetaFile" ) );
//STRIP001      aFlavorSeq[3].DataType = getCppuType( (const sal_uInt64*) 0 );
//STRIP001
//STRIP001      aFlavorSeq[4].MimeType =
//STRIP001          ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "application/x-openoffice;windows_formatname=\"Image WMF\"" ) );
//STRIP001      aFlavorSeq[4].HumanPresentableName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Windows MetaFile" ) );
//STRIP001      aFlavorSeq[4].DataType = getCppuType( (const sal_uInt64*) 0 );
//STRIP001  }
//STRIP001
//STRIP001  return aFlavorSeq;
/*?*/ }

//________________________________________________________________________________________________________
// XTransferable
//________________________________________________________________________________________________________


//STRIP001 sal_Bool SAL_CALL SfxBaseModel::isDataFlavorSupported( const DATAFLAVOR& aFlavor )
//STRIP001      throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      throw DISPOSEDEXCEPTION();
//STRIP001
//STRIP001  if ( aFlavor.MimeType.equalsAscii( "application/x-openoffice;windows_formatname=\"GDIMetaFile\"" ) )
//STRIP001  {
//STRIP001      if ( aFlavor.DataType == getCppuType( (const Sequence< sal_Int8 >*) 0 ) )
//STRIP001          return sal_True;
//STRIP001  }
//STRIP001  else if ( aFlavor.MimeType.equalsAscii( "application/x-openoffice;windows_formatname=\"Image EMF\"" ) )
//STRIP001  {
//STRIP001      if ( aFlavor.DataType == getCppuType( (const Sequence< sal_Int8 >*) 0 ) )
//STRIP001          return sal_True;
//STRIP001      else if ( supportsMetaFileHandle_Impl()
//STRIP001        && aFlavor.DataType == getCppuType( (const sal_uInt64*) 0 ) )
//STRIP001          return sal_True;
//STRIP001  }
//STRIP001  else if ( aFlavor.MimeType.equalsAscii( "application/x-openoffice;windows_formatname=\"Image WMF\"" ) )
//STRIP001  {
//STRIP001      if ( aFlavor.DataType == getCppuType( (const Sequence< sal_Int8 >*) 0 ) )
//STRIP001          return sal_True;
//STRIP001      else if ( supportsMetaFileHandle_Impl()
//STRIP001        && aFlavor.DataType == getCppuType( (const sal_uInt64*) 0 ) )
//STRIP001          return sal_True;
//STRIP001  }
//STRIP001
//STRIP001  return sal_False;
//STRIP001 }


//--------------------------------------------------------------------------------------------------------
//  XEventsSupplier
//--------------------------------------------------------------------------------------------------------

/*N*/ REFERENCE< XNAMEREPLACE > SAL_CALL SfxBaseModel::getEvents() throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( ! m_pData->m_xEvents.is() )
/*N*/   {
/*N*/       m_pData->m_xEvents = new SfxEvents_Impl( m_pData->m_pObjectShell, this );
/*N*/   }
/*N*/
/*N*/   return m_pData->m_xEvents;
/*N*/ }

//--------------------------------------------------------------------------------------------------------
//  XEventBroadcaster
//--------------------------------------------------------------------------------------------------------

/*N*/ void SAL_CALL SfxBaseModel::addEventListener( const REFERENCE< XDOCEVENTLISTENER >& aListener ) throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.addInterface( ::getCppuType((const REFERENCE< XDOCEVENTLISTENER >*)0), aListener );
/*N*/ }

//--------------------------------------------------------------------------------------------------------
//  XEventBroadcaster
//--------------------------------------------------------------------------------------------------------

/*N*/ void SAL_CALL SfxBaseModel::removeEventListener( const REFERENCE< XDOCEVENTLISTENER >& aListener ) throw( RUNTIMEEXCEPTION )
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XDOCEVENTLISTENER >*)0), aListener );
/*N*/ }

//________________________________________________________________________________________________________
//  SfxListener
//________________________________________________________________________________________________________

/*N*/ void addTitle_Impl( Sequence < ::com::sun::star::beans::PropertyValue >& rSeq, const ::rtl::OUString& rTitle )
/*N*/ {
/*N*/     sal_Int32 nCount = rSeq.getLength();
/*N*/     for ( sal_Int32 nArg=0; nArg<nCount; nArg++ )
/*N*/     {
/*N*/         ::com::sun::star::beans::PropertyValue& rProp = rSeq[nArg];
/*N*/         if ( rProp.Name.equalsAscii("Title") )
/*N*/         {
/*N*/             rProp.Value <<= rTitle;
/*N*/             break;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     if ( nArg == nCount )
/*N*/     {
/*N*/         rSeq.realloc( nCount+1 );
/*N*/         rSeq[nCount].Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("Title") );
/*N*/         rSeq[nCount].Value <<= rTitle;
/*N*/     }
/*N*/ }

/*N*/ void SfxBaseModel::Notify(            SfxBroadcaster& rBC     ,
/*N*/                           const   SfxHint&        rHint   )
/*N*/ {
/*N*/   if ( !m_pData )
/*N*/       return;
/*N*/
/*N*/   if ( &rBC == m_pData->m_pObjectShell )
/*N*/   {
/*N*/       SfxSimpleHint* pSimpleHint = PTR_CAST( SfxSimpleHint, &rHint );
/*N*/       if ( pSimpleHint && pSimpleHint->GetId() == SFX_HINT_DOCCHANGED )
/*N*/           changing();
/*N*/
/*N*/       SfxEventHint* pNamedHint = PTR_CAST( SfxEventHint, &rHint );
/*N*/       if ( pNamedHint )
/*N*/       {
/*N*/           if ( SFX_EVENT_SAVEASDOCDONE == pNamedHint->GetEventId() )
/*N*/             {
/*N*/               m_pData->m_sURL = m_pData->m_pObjectShell->GetMedium()->GetName();
/*N*/                 SfxItemSet *pSet = m_pData->m_pObjectShell->GetMedium()->GetItemSet();
/*N*/                 ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
/*N*/                 ::rtl::OUString aTitle = m_pData->m_pObjectShell->GetTitle();
/*N*/                 TransformItems( SID_SAVEASDOC, *pSet, aArgs );
/*N*/                 addTitle_Impl( aArgs, aTitle );
/*N*/                 attachResource( m_pData->m_pObjectShell->GetMedium()->GetName(), aArgs );
/*N*/             }
/*N*/
/*N*/           postEvent_Impl( *pNamedHint );
/*N*/       }
/*N*/
/*N*/         if ( pSimpleHint )
/*N*/       {
/*N*/           if ( pSimpleHint->GetId() == SFX_HINT_TITLECHANGED )
/*N*/           {
/*N*/               ::rtl::OUString aTitle = m_pData->m_pObjectShell->GetTitle();
/*N*/               addTitle_Impl( m_pData->m_seqArguments, aTitle );
/*N*/           }
/*
            else if ( pSimpleHint->GetId() == SFX_HINT_DYING
                || pSimpleHint->GetId() == SFX_HINT_DEINITIALIZING )
            {
                SfxObjectShellLock pShellLock = m_pData->m_pObjectShellLock;
                m_pData->m_pObjectShellLock = SfxObjectShellLock();
            }
*/
/*N*/       }
/*N*/
/*N*/       SfxPrintingHint* pPrintHint = PTR_CAST( SfxPrintingHint, &rHint );
/*N*/       if ( pPrintHint )
/*N*/       {
/*?*/           if ( pPrintHint->GetWhich() == -1 )
/*?*/           {
/*?*/               if ( !m_pData->m_xPrintJob.is() )
/*?*/                   {DBG_ASSERT(0, "STRIP");}//STRIP001 m_pData->m_xPrintJob = new SfxPrintJob_Impl( m_pData );
/*?*/
/*?*/               PrintDialog* pDlg = pPrintHint->GetPrintDialog();
/*?*/               Printer* pPrinter = pPrintHint->GetPrinter();
/*?*/                 ::rtl::OUString aPrintFile ( ( pPrinter && pPrinter->IsPrintFileEnabled() ) ? pPrinter->GetPrintFile() : String() );
/*?*/               ::rtl::OUString aRangeText ( ( pDlg && pDlg->IsRangeChecked(PRINTDIALOG_RANGE) ) ? pDlg->GetRangeText() : String() );
/*?*/               sal_Bool bSelectionOnly = ( ( pDlg && pDlg->IsRangeChecked(PRINTDIALOG_SELECTION) ) ? sal_True : sal_False );
/*?*/
/*?*/               sal_Int32 nArgs = 2;
/*?*/               if ( aPrintFile.getLength() )
/*?*/                   nArgs++;
/*?*/               if ( aRangeText.getLength() )
/*?*/                   nArgs++;
/*?*/               else if ( bSelectionOnly )
/*?*/                   nArgs++;
/*?*/
/*?*/               m_pData->m_aPrintOptions.realloc(nArgs);
/*?*/               m_pData->m_aPrintOptions[0].Name = DEFINE_CONST_UNICODE("CopyCount");
/*?*/               m_pData->m_aPrintOptions[0].Value <<= (sal_Int16) (pPrinter ? pPrinter->GetCopyCount() : 1 );
/*?*/               m_pData->m_aPrintOptions[1].Name = DEFINE_CONST_UNICODE("Collate");
/*?*/               m_pData->m_aPrintOptions[1].Value <<= (sal_Bool) (pDlg ? pDlg->IsCollateChecked() : sal_False );
/*?*/
/*?*/               if ( bSelectionOnly )
/*?*/               {
/*?*/                   m_pData->m_aPrintOptions[2].Name = DEFINE_CONST_UNICODE("Selection");
/*?*/                   m_pData->m_aPrintOptions[2].Value <<= bSelectionOnly;
/*?*/               }
/*?*/               else if ( aRangeText.getLength() )
/*?*/               {
/*?*/                   m_pData->m_aPrintOptions[2].Name = DEFINE_CONST_UNICODE("Pages");
/*?*/                   m_pData->m_aPrintOptions[2].Value <<= aRangeText;
/*?*/               }
/*?*/
/*?*/               if ( aPrintFile.getLength() )
/*?*/               {
/*?*/                   m_pData->m_aPrintOptions[nArgs-1].Name = DEFINE_CONST_UNICODE("FileName");
/*?*/                   m_pData->m_aPrintOptions[nArgs-1].Value <<= aPrintFile;
/*?*/               }
/*?*/           }
/*?*/           else if ( pPrintHint->GetWhich() == -3 )
/*?*/           {
/*?*/                   sal_Int32 nOld = m_pData->m_aPrintOptions.getLength();
/*?*/                   sal_Int32 nAdd = pPrintHint->GetAdditionalOptions().getLength();
/*?*/                   m_pData->m_aPrintOptions.realloc(  nOld + nAdd );
/*?*/                   for ( sal_Int32 n=0; n<nAdd; n++ )
/*?*/                         m_pData->m_aPrintOptions[ nOld+n ] = pPrintHint->GetAdditionalOptions()[n];
/*?*/           }
/*?*/           else if ( pPrintHint->GetWhich() != -2 )
/*?*/           {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001 /*?*/                view::PrintJobEvent aEvent;
//STRIP001 /*?*/                aEvent.Source = m_pData->m_xPrintJob;
//STRIP001 /*?*/                aEvent.State = (com::sun::star::view::PrintableState) pPrintHint->GetWhich();
//STRIP001 /*?*/                ::cppu::OInterfaceContainerHelper* pContainer = m_pData->m_aInterfaceContainer.getContainer( ::getCppuType( ( const uno::Reference< view::XPrintJobListener >*) NULL ) );
//STRIP001 /*?*/                if ( pContainer!=NULL )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ::cppu::OInterfaceIteratorHelper pIterator(*pContainer);
//STRIP001 /*?*/                    while (pIterator.hasMoreElements())
//STRIP001 /*?*/                        ((view::XPrintJobListener*)pIterator.next())->printJobEvent( aEvent );
//STRIP001 /*?*/                }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }

//________________________________________________________________________________________________________
//  public impl.
//________________________________________________________________________________________________________

/*N*/ void SfxBaseModel::changing()
/*N*/ {
/*N*/   // object already disposed?
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   OINTERFACECONTAINERHELPER* pIC = m_pData->m_aInterfaceContainer.getContainer( ::getCppuType((const REFERENCE< XMODIFYLISTENER >*)0) );
/*N*/   if( pIC )
/*N*/
/*N*/   {
/*N*/       EVENTOBJECT aEvent( (XMODEL *)this );
/*N*/       OINTERFACEITERATORHELPER aIt( *pIC );
/*N*/       while( aIt.hasMoreElements() )
/*N*/         {
/*N*/             try
/*N*/             {
/*N*/                 ((XMODIFYLISTENER *)aIt.next())->modified( aEvent );
/*N*/             }
/*N*/             catch( RUNTIMEEXCEPTION& )
/*N*/             {
/*N*/                 aIt.remove();
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/ }

/*?*/ void SfxBaseModel::impl_change()
/*?*/ {
/*?*/   // object already disposed?
/*?*/   if ( impl_isDisposed() )
/*?*/       return;
/*?*/
/*?*/   OINTERFACECONTAINERHELPER* pIC = m_pData->m_aInterfaceContainer.getContainer( ::getCppuType((const REFERENCE< XMODIFYLISTENER >*)0) );
/*?*/   if( pIC )
/*?*/
/*?*/   {
/*?*/       EVENTOBJECT aEvent( (XMODEL *)this );
/*?*/       OINTERFACEITERATORHELPER aIt( *pIC );
/*?*/       while( aIt.hasMoreElements() )
/*?*/         {
/*?*/             try
/*?*/             {
/*?*/                 ((XMODIFYLISTENER *)aIt.next())->modified( aEvent );
/*?*/             }
/*?*/             catch( RUNTIMEEXCEPTION& )
/*?*/             {
/*?*/                 aIt.remove();
/*?*/             }
/*?*/         }
/*?*/   }
/*?*/ }

//________________________________________________________________________________________________________
//  public impl.
//________________________________________________________________________________________________________

/*N*/ SfxObjectShell* SfxBaseModel::GetObjectShell() const
/*N*/ {
/*N*/   return m_pData ? (SfxObjectShell*) m_pData->m_pObjectShell : 0;
/*N*/ }

/*N*/ SfxObjectShell* SfxBaseModel::impl_getObjectShell() const
/*N*/ {
/*N*/   return m_pData ? (SfxObjectShell*) m_pData->m_pObjectShell : 0;
/*N*/ }

//________________________________________________________________________________________________________
//  public impl.
//________________________________________________________________________________________________________

/*N*/ sal_Bool SfxBaseModel::IsDisposed() const
/*N*/ {
/*N*/   return ( m_pData == NULL ) ;
/*N*/ }

/*N*/ sal_Bool SfxBaseModel::impl_isDisposed() const
/*N*/ {
/*N*/   return ( m_pData == NULL ) ;
/*N*/ }

//________________________________________________________________________________________________________
//  private impl.
//________________________________________________________________________________________________________

/*N*/ void SfxBaseModel::impl_store(            SfxObjectShell*             pObjectShell    ,
/*N*/                               const   OUSTRING&                   sURL            ,
/*N*/                               const   SEQUENCE< PROPERTYVALUE >&  seqArguments    ,
/*N*/                                       sal_Bool                    bSaveTo         )
/*N*/ {
/*N*/   if( !sURL.getLength() )
/*N*/       throw ILLEGALARGUMENTIOEXCEPTION();
/*N*/
/*N*/   //sal_Bool aSaveAsTemplate = sal_False;
/*N*/
/*N*/     SfxAllItemSet *aParams = new SfxAllItemSet( SFX_APP()->GetPool() );
/*N*/   aParams->Put( SfxStringItem( SID_FILE_NAME, String(sURL) ) );
/*N*/   if ( bSaveTo )
/*N*/       aParams->Put( SfxBoolItem( SID_SAVETO, sal_True ) );
/*N*/
/*N*/     TransformParameters( SID_SAVEASDOC, seqArguments, *aParams );
/*N*/   sal_Bool aRet = pObjectShell->APISaveAs_Impl( sURL, aParams );
/*N*/   DELETEZ( aParams );
/*N*/
/*N*/   sal_uInt32 nErrCode = pObjectShell->GetError() ? pObjectShell->GetError() : ERRCODE_IO_CANTWRITE;
/*N*/   pObjectShell->ResetError();
/*N*/
/*N*/   if ( !aRet )
/*N*/   {
/*N*/       throw SfxIOException_Impl( nErrCode );
/*N*/   }
/*N*/ }
/*N*/
//********************************************************************************************************

/*N*/ void SfxBaseModel::postEvent_Impl( const SfxEventHint& rHint )
/*N*/ {
/*N*/   // object already disposed?
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   OINTERFACECONTAINERHELPER* pIC = m_pData->m_aInterfaceContainer.getContainer(
/*N*/                                       ::getCppuType((const REFERENCE< XDOCEVENTLISTENER >*)0) );
/*N*/   if( pIC )
/*N*/
/*N*/   {
/*N*/       OUSTRING aName = SfxEventConfiguration::GetEventName_Impl( rHint.GetEventId() );
/*N*/       DOCEVENTOBJECT aEvent( (XMODEL *)this, aName );
/*N*/       OINTERFACEITERATORHELPER aIt( *pIC );
/*N*/       while( aIt.hasMoreElements() )
/*N*/         {
/*N*/             try
/*N*/             {
/*N*/                 ((XDOCEVENTLISTENER *)aIt.next())->notifyEvent( aEvent );
/*N*/             }
/*N*/             catch( RUNTIMEEXCEPTION& )
/*N*/             {
/*N*/                 aIt.remove();
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/ }

/*N*/ REFERENCE < XINDEXACCESS > SAL_CALL SfxBaseModel::getViewData() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   if ( m_pData->m_pObjectShell.Is() && !m_pData->m_contViewData.is() )
/*N*/   {
/*N*/       SfxViewFrame *pActFrame = SfxViewFrame::Current();
/*N*/       if ( !pActFrame || pActFrame->GetObjectShell() != m_pData->m_pObjectShell )
/*N*/           pActFrame = SfxViewFrame::GetFirst(m_pData->m_pObjectShell, TYPE(SfxTopViewFrame));
/*N*/
/*N*/       if ( !pActFrame )
/*N*/           // currently no frame for this document at all
/*N*/           return REFERENCE < XINDEXACCESS >();
/*N*/
/*N*/       m_pData->m_contViewData = Reference < XINDEXACCESS >(
/*N*/               ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
/*N*/               DEFINE_CONST_UNICODE("com.sun.star.document.IndexedPropertyValues") ),
/*N*/               UNO_QUERY );
/*N*/
/*N*/       if ( !m_pData->m_contViewData.is() )
/*N*/       {
/*N*/           // error: no container class available!
/*N*/           return REFERENCE < XINDEXACCESS >();
/*N*/       }
/*N*/
/*N*/       REFERENCE < XINDEXCONTAINER > xCont( m_pData->m_contViewData, UNO_QUERY );
/*N*/       sal_Int32 nCount = 0;
/*N*/       SEQUENCE < PROPERTYVALUE > aSeq;
/*N*/       ::com::sun::star::uno::Any aAny;
/*N*/       for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst(m_pData->m_pObjectShell, TYPE(SfxTopViewFrame) ); pFrame;
/*N*/               pFrame = SfxViewFrame::GetNext(*pFrame, m_pData->m_pObjectShell, TYPE(SfxTopViewFrame) ) )
/*N*/       {
/*N*/           BOOL bIsActive = ( pFrame == pActFrame );
/*N*/           pFrame->GetViewShell()->WriteUserDataSequence( aSeq );
/*N*/           aAny <<= aSeq;
/*N*/           xCont->insertByIndex( bIsActive ? 0 : nCount, aAny );
/*N*/           nCount++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return m_pData->m_contViewData;
/*N*/ }

/*N*/ void SAL_CALL SfxBaseModel::setViewData( const REFERENCE < XINDEXACCESS >& aData ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   // object already disposed?
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   if ( impl_isDisposed() )
/*N*/       throw DISPOSEDEXCEPTION();
/*N*/
/*N*/   m_pData->m_contViewData = aData;
/*N*/ }

/** calls all XEventListeners */
/*N*/ void SfxBaseModel::notifyEvent( const ::com::sun::star::document::EventObject& aEvent ) const
/*N*/ {
/*N*/   // object already disposed?
/*N*/   if ( impl_isDisposed() )
/*N*/       return;
/*N*/
/*N*/   OINTERFACECONTAINERHELPER* pIC = m_pData->m_aInterfaceContainer.getContainer(
/*N*/                                       ::getCppuType((const REFERENCE< XDOCEVENTLISTENER >*)0) );
/*N*/   if( pIC )
/*N*/
/*N*/   {
/*N*/       OINTERFACEITERATORHELPER aIt( *pIC );
/*N*/       while( aIt.hasMoreElements() )
/*N*/         {
/*N*/             try
/*N*/             {
/*N*/                 ((XDOCEVENTLISTENER *)aIt.next())->notifyEvent( aEvent );
/*N*/             }
/*N*/             catch( RUNTIMEEXCEPTION& )
/*N*/             {
/*N*/                 aIt.remove();
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/ }

/** returns true if someone added a XEventListener to this XEventBroadcaster */
/*N*/ sal_Bool SfxBaseModel::hasEventListeners() const
/*N*/ {
/*N*/   return !impl_isDisposed() && (NULL != m_pData->m_aInterfaceContainer.getContainer( ::getCppuType((const REFERENCE< XDOCEVENTLISTENER >*)0) ) );
/*N*/ }

//STRIP001 void SAL_CALL SfxBaseModel::addPrintJobListener( const ::com::sun::star::uno::Reference< ::com::sun::star::view::XPrintJobListener >& xListener ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      return;
//STRIP001
//STRIP001  m_pData->m_aInterfaceContainer.addInterface( ::getCppuType((const REFERENCE< XPRINTJOBLISTENER >*)0), xListener );
//STRIP001 }

//STRIP001 void SAL_CALL SfxBaseModel::removePrintJobListener( const ::com::sun::star::uno::Reference< ::com::sun::star::view::XPrintJobListener >& xListener ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  // object already disposed?
//STRIP001     ::vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001  if ( impl_isDisposed() )
//STRIP001      return;
//STRIP001
//STRIP001  m_pData->m_aInterfaceContainer.removeInterface( ::getCppuType((const REFERENCE< XPRINTJOBLISTENER >*)0), xListener );
//STRIP001 }

