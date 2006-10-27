/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmtools.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:09:53 $
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
#ifndef _SVX_FMTOOLS_HXX
#define _SVX_FMTOOLS_HXX

#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDERINTERCEPTION_HPP_
#include <com/sun/star/frame/XDispatchProviderInterception.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XINTERCEPTORINFO_HPP_
#include <com/sun/star/frame/XInterceptorInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif


#ifndef _SVSTDARR_ULONGS
#define _SVSTDARR_ULONGS
#endif

#ifndef _SFXCTRLITEM_HXX //autogen wg. SfxControllerItem
#include <bf_sfx2/ctrlitem.hxx>
#endif



#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.h>
#endif
#ifndef _CPPUHELPER_COMPBASE3_HXX_
#include <cppuhelper/compbase3.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _CPPUHELPER_COMPONENT_HXX_
#include <cppuhelper/component.hxx>
#endif

#ifndef _FM_IMPLEMENTATION_IDS_HXX_
#include "fmimplids.hxx"
#endif

class Window;
namespace binfilter {



//==================================================================
// allgemeine Typen
//==================================================================
// displaying a database exception for the user
// display info about a simple ::com::sun::star::sdbc::SQLException
// display info about chained SQLExceptions

// StringConversion
namespace svxform
{
    // modes for the XModeSelector
    DECLARE_CONSTASCII_USTRING(DATA_MODE);
    DECLARE_CONSTASCII_USTRING(FILTER_MODE);

}   // namespace svxform


// Kopieren von Persistenten Objecten


// Suchen in einer Indexliste nach einem Element

sal_Int32 getElementPos(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& xCont, const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xElement);




// ===================================================================================================
// = class CursorWrapper - eine Hilfsklasse, die parallel mit je einem ::com::sun::star::uno::Reference<XDatabaseUpdateCursor>,
//                          XDatabaseBookmarkCursor und XDatabaseDirectCursor arbeitet
// ===================================================================================================



class FmXDisposeMultiplexer;

typedef ::cppu::WeakImplHelper1< ::com::sun::star::lang::XEventListener> FmXDisposeMultiplexer_x;
//==============================================================================



//  ==================================================================

//==============================================================================
// FmSlotDispatch - some kind of translator between the Sfx-Slots and the UNO-dispatchers
//==============================================================================

typedef ::cppu::WeakImplHelper1< ::com::sun::star::frame::XDispatch >   FmSlotDispatch_x;
class FmSlotDispatch
            :public SfxControllerItem
            ,public ::cppu::WeakImplHelper2< ::com::sun::star::frame::XDispatch, ::com::sun::star::lang::XComponent>
            //  ,public XComponent
{
    // force broadcasting the current status
    void    BroadcastCurrentState( );

};

//========================================================================
//= dispatch interception helper classes
//========================================================================

//------------------------------------------------------------------------
//- FmDispatchInterceptor
//------------------------------------------------------------------------
class FmDispatchInterceptor
{
public:
    FmDispatchInterceptor() { }

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch> interceptedQueryDispatch(sal_uInt16 _nId,
        const ::com::sun::star::util::URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags) throw( ::com::sun::star::uno::RuntimeException ) = 0;

    virtual ::osl::Mutex* getInterceptorMutex() = 0;
};

//------------------------------------------------------------------------
//- FmXDispatchInterceptorImpl
//------------------------------------------------------------------------
typedef ::cppu::WeakComponentImplHelper3<   ::com::sun::star::frame::XDispatchProviderInterceptor
                                        ,   ::com::sun::star::lang::XEventListener
                                        ,   ::com::sun::star::frame::XInterceptorInfo
                                        >   FmXDispatchInterceptorImpl_BASE;

class FmXDispatchInterceptorImpl : public FmXDispatchInterceptorImpl_BASE
{
    ::osl::Mutex                    m_aFallback;
    ::binfilter::form::OImplementationIdsRef    m_aHoldImplIdHelper;//STRIP008  ::form::OImplementationIdsRef   m_aHoldImplIdHelper;

    // the component which's dispatches we're intercepting
    ::com::sun::star::uno::WeakReference< ::com::sun::star::frame::XDispatchProviderInterception>
                    m_xIntercepted;
    sal_Bool        m_bListening;

    // the real interceptor
    FmDispatchInterceptor*          m_pMaster;

    // chaining
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider>           m_xSlaveDispatcher;
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider>           m_xMasterDispatcher;

    // our id
    sal_Int16                       m_nId;

    ::com::sun::star::uno::Sequence< ::rtl::OUString >
                                    m_aInterceptedURLSchemes;

    virtual ~FmXDispatchInterceptorImpl();

public:
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProviderInterception> getIntercepted() const { return m_xIntercepted; }

public:
    FmXDispatchInterceptorImpl(
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProviderInterception>& _rToIntercept,
        FmDispatchInterceptor* _pMaster,
        sal_Int16 _nId,
        ::com::sun::star::uno::Sequence< ::rtl::OUString > _rInterceptedSchemes /// if not empty, this will be used for getInterceptedURLs
    );

    // StarOne
    DECLARE_UNO3_DEFAULTS(FmXDispatchInterceptorImpl, FmXDispatchInterceptorImpl_BASE);
    //  virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& type) throw ( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw(::com::sun::star::uno::RuntimeException);
    //  ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw(::com::sun::star::uno::RuntimeException);


    // ::com::sun::star::frame::XDispatchProvider
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch > SAL_CALL queryDispatch( const ::com::sun::star::util::URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch > > SAL_CALL queryDispatches( const ::com::sun::star::uno::Sequence< ::com::sun::star::frame::DispatchDescriptor >& aDescripts ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::frame::XDispatchProviderInterceptor
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider > SAL_CALL getSlaveDispatchProvider(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setSlaveDispatchProvider( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider >& xNewDispatchProvider ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider > SAL_CALL getMasterDispatchProvider(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setMasterDispatchProvider( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider >& xNewSupplier ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::frame::XInterceptorInfo
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getInterceptedURLs(  ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XEventListener
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);

    // OComponentHelper
    virtual void SAL_CALL disposing();

protected:
    void ImplDetach();

    ::osl::Mutex&       getAccessSafety()
    {
        if (m_pMaster && m_pMaster->getInterceptorMutex())
            return *m_pMaster->getInterceptorMutex();
        return m_aFallback;
    }
};

//==================================================================
// ...
//==================================================================
    // get a service name to create a model of the given type (OBJ_FM_...)
    // get the object type (OBJ_FM_...) from the services the object supports



//==================================================================
    // checks if the ::com::sun::star::sdbcx::XColumnsSupplier provided by _rxRowSet supllies any columns

}//end of namespace binfilter
#endif // _SVX_FMTOOLS_HXX

