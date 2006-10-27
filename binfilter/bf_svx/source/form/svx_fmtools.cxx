/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_fmtools.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:58:14 $
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
#pragma hdrstop

#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif
#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>









#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif




#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#include <algorithm>
namespace binfilter {

namespace svxform
{

    IMPLEMENT_CONSTASCII_USTRING(DATA_MODE,"DataMode");
    IMPLEMENT_CONSTASCII_USTRING(FILTER_MODE,"FilterMode");

}   // namespace svxform

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::task;
using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;
using namespace ::connectivity::simple;

//  ------------------------------------------------------------------------------

//  ------------------------------------------------------------------------------

//  ------------------------------------------------------------------------------

//  ------------------------------------------------------------------------------

//  ------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/*N*/ sal_Int32 getElementPos(const Reference< ::com::sun::star::container::XIndexAccess>& xCont, const Reference< XInterface >& xElement)
/*N*/ {
/*N*/   sal_Int32 nIndex = -1;
/*N*/   if (!xCont.is())
/*N*/       return nIndex;
/*N*/

/*N*/   Reference< XInterface > xNormalized( xElement, UNO_QUERY );
/*N*/   DBG_ASSERT( xNormalized.is(), "getElementPos: invalid element!" );
/*N*/   if ( xNormalized.is() )
/*N*/   {
/*N*/       // Feststellen an welcher Position sich das Kind befindet
/*N*/       nIndex = xCont->getCount();
/*N*/       while (nIndex--)
/*N*/       {
/*N*/           try
/*N*/           {
/*N*/               Reference< XInterface > xCurrent;
/*N*/               xCont->getByIndex( nIndex ) >>= xCurrent;
/*N*/               DBG_ASSERT( xCurrent.get() == Reference< XInterface >( xCurrent, UNO_QUERY ).get(),
/*N*/                   "getElementPos: container element not normalized!" );
/*N*/               if ( xNormalized.get() == xCurrent.get() )
/*N*/                   break;
/*N*/           }
/*N*/           catch(Exception&)
/*N*/           {
/*N*/               DBG_ERROR( "getElementPos: caught an exception!" );
/*N*/           }
/*N*/
/*N*/       }
/*N*/   }
/*N*/   return nIndex;
/*N*/ }

//------------------------------------------------------------------

//------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------
// Vergleichen von PropertyInfo

//------------------------------------------------------------------------------

//------------------------------------------------------------------

//------------------------------------------------------------------

//========================================================================
// = CursorWrapper
//------------------------------------------------------------------------

//------------------------------------------------------------------------

//------------------------------------------------------------------------

//------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//==============================================================================
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

// ::com::sun::star::lang::XEventListener
//------------------------------------------------------------------

//------------------------------------------------------------------

//==============================================================================
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//==============================================================================
// FmSlotDispatch - some kind of translator between the Sfx-Slots and the UNO-dispatchers
//==============================================================================

//  SMART_UNO_IMPLEMENTATION(FmSlotDispatch, UsrObject);


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//========================================================================
//= FmXDispatchInterceptorImpl
//========================================================================

/*N*/ DBG_NAME(FmXDispatchInterceptorImpl)
//------------------------------------------------------------------------
/*N*/ FmXDispatchInterceptorImpl::FmXDispatchInterceptorImpl(
/*N*/           const Reference< XDispatchProviderInterception >& _rxToIntercept, FmDispatchInterceptor* _pMaster,
/*N*/           sal_Int16 _nId, Sequence< ::rtl::OUString > _rInterceptedSchemes)
/*N*/   :FmXDispatchInterceptorImpl_BASE(_pMaster && _pMaster->getInterceptorMutex() ? *_pMaster->getInterceptorMutex() : m_aFallback)
/*N*/   ,m_xIntercepted(_rxToIntercept)
/*N*/   ,m_pMaster(_pMaster)
/*N*/   ,m_nId(_nId)
/*N*/   ,m_aInterceptedURLSchemes(_rInterceptedSchemes)
/*N*/   ,m_bListening(sal_False)
/*N*/ {
/*N*/   DBG_CTOR(FmXDispatchInterceptorImpl,NULL);
/*N*/
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   ::comphelper::increment(m_refCount);
/*N*/   if (_rxToIntercept.is())
/*N*/   {
/*N*/       _rxToIntercept->registerDispatchProviderInterceptor((::com::sun::star::frame::XDispatchProviderInterceptor*)this);
/*N*/       // this should make us the top-level dispatch-provider for the component, via a call to our
/*N*/       // setDispatchProvider we should have got an fallback for requests we (i.e. our master) cannot fullfill
/*N*/       Reference< ::com::sun::star::lang::XComponent> xInterceptedComponent(_rxToIntercept, UNO_QUERY);
/*N*/       if (xInterceptedComponent.is())
/*N*/       {
/*N*/           xInterceptedComponent->addEventListener(this);
/*N*/           m_bListening = sal_True;
/*N*/       }
/*N*/   }
/*N*/   ::comphelper::decrement(m_refCount);
/*N*/ }

//------------------------------------------------------------------------
/*N*/ FmXDispatchInterceptorImpl::~FmXDispatchInterceptorImpl()
/*N*/ {
/*N*/   if (!rBHelper.bDisposed)
/*?*/       dispose();
/*N*/
/*N*/   DBG_DTOR(FmXDispatchInterceptorImpl,NULL);
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ Sequence< sal_Int8 > SAL_CALL FmXDispatchInterceptorImpl::getImplementationId() throw(RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); Sequence< sal_Int8 > a; return a;//STRIP001
/*N*/ }
//------------------------------------------------------------------------------
/*N*/ Reference< ::com::sun::star::frame::XDispatch > SAL_CALL FmXDispatchInterceptorImpl::queryDispatch( const URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags ) throw(RuntimeException)
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   Reference< ::com::sun::star::frame::XDispatch> xResult;
/*N*/   // ask our 'real' interceptor
/*N*/   if (m_pMaster)
/*N*/       xResult = m_pMaster->interceptedQueryDispatch(m_nId, aURL, aTargetFrameName, nSearchFlags);
/*N*/
/*N*/   // ask our slave provider
/*N*/   if (!xResult.is() && m_xSlaveDispatcher.is())
/*N*/       xResult = m_xSlaveDispatcher->queryDispatch(aURL, aTargetFrameName, nSearchFlags);
/*N*/
/*N*/   return xResult;
/*N*/ }

//------------------------------------------------------------------------------
/*?*/ Sequence< Reference< ::com::sun::star::frame::XDispatch > > SAL_CALL
/*?*/ FmXDispatchInterceptorImpl::queryDispatches( const Sequence< ::com::sun::star::frame::DispatchDescriptor >& aDescripts ) throw(RuntimeException)
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); Sequence< Reference< ::com::sun::star::frame::XDispatch> > aReturn(aDescripts.getLength()); return aReturn;//STRIP001  ::osl::MutexGuard aGuard(getAccessSafety());
/*?*/ }

//------------------------------------------------------------------------------
/*N*/ Reference< ::com::sun::star::frame::XDispatchProvider > SAL_CALL FmXDispatchInterceptorImpl::getSlaveDispatchProvider(    ) throw(RuntimeException)
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   return m_xSlaveDispatcher;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL FmXDispatchInterceptorImpl::setSlaveDispatchProvider(const Reference< ::com::sun::star::frame::XDispatchProvider>& xNewDispatchProvider) throw( RuntimeException )
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   m_xSlaveDispatcher = xNewDispatchProvider;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ Reference< ::com::sun::star::frame::XDispatchProvider> SAL_CALL FmXDispatchInterceptorImpl::getMasterDispatchProvider(void) throw( RuntimeException )
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   return m_xMasterDispatcher;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL FmXDispatchInterceptorImpl::setMasterDispatchProvider(const Reference< ::com::sun::star::frame::XDispatchProvider>& xNewSupplier) throw( RuntimeException )
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   m_xMasterDispatcher = xNewSupplier;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ Sequence< ::rtl::OUString > SAL_CALL FmXDispatchInterceptorImpl::getInterceptedURLs(  ) throw(RuntimeException)
/*N*/ {
/*N*/   return m_aInterceptedURLSchemes;
/*N*/ }

//------------------------------------------------------------------------------
/*?*/ void SAL_CALL FmXDispatchInterceptorImpl::disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException )
/*?*/ {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if (m_bListening)
/*?*/ }

//------------------------------------------------------------------------------
/*N*/ void FmXDispatchInterceptorImpl::ImplDetach()
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   OSL_ENSURE(m_bListening, "FmXDispatchInterceptorImpl::ImplDetach: invalid call!");
/*N*/
/*N*/   // deregister ourself from the interception component
/*N*/   Reference< XDispatchProviderInterception > xIntercepted(m_xIntercepted.get(), UNO_QUERY);
/*N*/   if (xIntercepted.is())
/*N*/       xIntercepted->releaseDispatchProviderInterceptor(static_cast<XDispatchProviderInterceptor*>(this));
/*N*/
/*N*/ //    m_xIntercepted = Reference< XDispatchProviderInterception >();
/*N*/       // Don't reset m_xIntercepted: It may be needed by our owner to check for which object we were
/*N*/       // responsible. As we hold the object with a weak reference only, this should be no problem.
/*N*/       // 88936 - 23.07.2001 - frank.schoenheit@sun.com
/*N*/   m_pMaster = NULL;
/*N*/   m_bListening = sal_False;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void FmXDispatchInterceptorImpl::disposing()
/*N*/ {
/*N*/   // remove ourself as event listener from the interception component
/*N*/   if (m_bListening)
/*N*/   {
/*N*/       Reference< ::com::sun::star::lang::XComponent> xInterceptedComponent(m_xIntercepted.get(), UNO_QUERY);
/*N*/       if (xInterceptedComponent.is())
/*N*/           xInterceptedComponent->removeEventListener(static_cast<XEventListener*>(this));
/*N*/
/*N*/       // detach from the interception component
/*N*/       ImplDetach();
/*N*/   }
/*N*/ }

//==============================================================================
//==============================================================================

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
}
