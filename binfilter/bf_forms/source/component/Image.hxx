/*************************************************************************
 *
 *  $RCSfile: Image.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2005-04-14 15:33:27 $
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

#ifndef _FRM_IMAGE_HXX_
#define _FRM_IMAGE_HXX_

#ifndef _FORMS_FORMCOMPONENT_HXX_
#include "FormComponent.hxx"
#endif

#ifndef _FRM_EVENT_THREAD_HXX_
#include "EventThread.hxx"
#endif

// auto strip #ifndef _LINK_HXX
// auto strip #include <tools/link.hxx>
// auto strip #endif
#ifndef _COMPHELPER_PROPERTY_MULTIPLEX_HXX_
#include <comphelper/propmultiplex.hxx>
#endif
#ifndef _PRODUCE_HXX
#include "imgprod.hxx"
#endif

#ifndef _COM_SUN_STAR_FORM_XIMAGEPRODUCERSUPPLIER_HPP_
#include <com/sun/star/form/XImageProducerSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_FORMBUTTONTYPE_HPP_
#include <com/sun/star/form/FormButtonType.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_FORM_XAPPROVEACTIONLISTENER_HPP_
// auto strip #include <com/sun/star/form/XApproveActionListener.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_FORM_XAPPROVEACTIONBROADCASTER_HPP_
#include <com/sun/star/form/XApproveActionBroadcaster.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
namespace binfilter {


class SfxMedium;

//.........................................................................
namespace frm
{
//.........................................................................

//==================================================================
// OImageModel
//==================================================================
typedef ::cppu::ImplHelper2 <   ::com::sun::star::form::XImageProducerSupplier
                            ,   ::com::sun::star::awt::XImageProducer
                            >   OImageModel_Base;

class OImageModel   :public OImageModel_Base
                    ,public OControlModel
                    ,public OPropertyChangeListener
{
protected:
    ::com::sun::star::form::FormButtonType  m_eButtonType;      // Art des Buttons (push,submit,reset)
    ::rtl::OUString                         m_sTargetURL;       // starutil::URL fuer den starutil::URL-Button
    ::rtl::OUString                         m_sTargetFrame;     // TargetFrame zum Oeffnen

// ImageProducer stuff
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XImageProducer>    m_xProducer;
    SfxMedium*                              m_pMedium;          // Download-Medium
    ImageProducer*                          m_pProducer;
    sal_Bool                                m_bDispatchUrlInternal; // property: is not allowed to set : 1
    sal_Bool                                m_bDownloading : 1; // laeuft ein Download?
    sal_Bool                                m_bProdStarted : 1;



    DECL_STATIC_LINK( OImageModel, DataAvailableLink, void* );
    DECL_STATIC_LINK( OImageModel, DownloadDoneLink, void* );

    inline ImageProducer* GetImageProducer() { return m_pProducer; }

    void StartProduction();
    void SetURL(const ::rtl::OUString& rURL);
    void DataAvailable();
    void DownloadDone();

    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();
    inline sal_Bool isDispatchUrlInternal() const { return m_bDispatchUrlInternal; }
    inline void     setDispatchUrlInternal(sal_Bool _bDispatch) { m_bDispatchUrlInternal = _bDispatch; }

public:
    DECLARE_DEFAULT_XTOR( OImageModel );

    // UNO Anbindung
    DECLARE_UNO3_AGG_DEFAULTS(OImageModel, OControlModel);
    virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(const ::com::sun::star::uno::Type& _rType) throw(::com::sun::star::uno::RuntimeException);

// OComponentHelper
    virtual void SAL_CALL disposing();

// ::com::sun::star::form::XImageProducerSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::awt::XImageProducer> SAL_CALL getImageProducer() throw (::com::sun::star::uno::RuntimeException) { return m_xProducer; }

// OPropertySetHelper
    virtual void SAL_CALL getFastPropertyValue(::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;
    virtual void SAL_CALL setFastPropertyValue_NoBroadcast(sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue) throw (::com::sun::star::uno::Exception);

    virtual sal_Bool SAL_CALL convertFastPropertyValue(::com::sun::star::uno::Any& rConvertedValue, ::com::sun::star::uno::Any& rOldValue, sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue )
        throw(::com::sun::star::lang::IllegalArgumentException);

// OPropertyChangeListener
    virtual void _propertyChanged(const ::com::sun::star::beans::PropertyChangeEvent&) throw(::com::sun::star::uno::RuntimeException);

// XPersistObject
    virtual void SAL_CALL
        read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& _rxInStream) throw(::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);

// ::com::sun::star::beans::XPropertyState
    virtual ::com::sun::star::beans::PropertyState getPropertyStateByHandle(sal_Int32 nHandle);
    virtual void setPropertyToDefaultByHandle(sal_Int32 nHandle);
    virtual ::com::sun::star::uno::Any getPropertyDefaultByHandle( sal_Int32 nHandle ) const;

// XImageProducer
    virtual void SAL_CALL addConsumer( const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XImageConsumer >& xConsumer ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeConsumer( const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XImageConsumer >& xConsumer ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL startProduction(  ) throw (::com::sun::star::uno::RuntimeException);

protected:
    void implConstruct();

    // to be called from within the cloning-ctor of your derived class
    void implInitializeImageURL( );
};

//==================================================================
// OImageControl
//==================================================================
typedef ::cppu::ImplHelper2<    ::com::sun::star::form::XApproveActionBroadcaster,
                                ::com::sun::star::beans::XPropertyChangeListener> OImageControl_BASE;

class OImageControl :   public OImageControl_BASE,
                        public OControl
{
    friend class OImageControlThread_Impl;

protected:
    ::cppu::OInterfaceContainerHelper
        m_aApproveActionListeners,
        m_aActionListeners;
    ::rtl::OUString m_aActionCommand;

    OImageControlThread_Impl *m_pThread;

public:
    OImageControl(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory,
        const ::rtl::OUString& _aService);
    virtual ~OImageControl();

// UNO Anbindung
    DECLARE_UNO3_AGG_DEFAULTS(OImageControl, OControl);
    virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(const ::com::sun::star::uno::Type& _rType) throw(::com::sun::star::uno::RuntimeException);

// OComponentHelper
    virtual void SAL_CALL disposing();

// ::com::sun::star::form::XApproveActionBroadcaster
    virtual void SAL_CALL addApproveActionListener(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XApproveActionListener>& _rxListener)
        throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeApproveActionListener(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XApproveActionListener>& _rxListener)
        throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::awt::XControl
    virtual void SAL_CALL createPeer(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XToolkit>& _rToolkit, const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindowPeer>& Parent) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL setModel(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>& Model) throw (::com::sun::star::uno::RuntimeException);

// ::com::sun::star::beans::XPropertyChangeListener
    virtual void SAL_CALL propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& ) throw(::com::sun::star::uno::RuntimeException);

protected:
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  getXModel(const InterfaceRef& xIface) const;

    virtual void actionPerformed_Impl( sal_Bool bNotifyListener, const ::com::sun::star::awt::MouseEvent& rEvt = ::com::sun::star::awt::MouseEvent());

    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();
};

//==================================================================
// OImageControlThread_Impl
//==================================================================
class OImageControlThread_Impl: public OComponentEventThread
{
protected:

    // Die folgende Methode wrrd gerufen um das Event unter Beruecksichtigung
    // seines Typs zu duplizieren
    virtual ::com::sun::star::lang::EventObject* cloneEvent( const ::com::sun::star::lang::EventObject* _pEvt ) const;

    // Ein Event bearbeiten. Der Mutex ist dabei nicht gelockt, pCompImpl
    // bleibt aber in jedem Fall gueltig.
    virtual void processEvent( ::cppu::OComponentHelper *pCompImpl,
                               const ::com::sun::star::lang::EventObject*,
                               const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl>&,
                               sal_Bool );

public:
    OImageControlThread_Impl( OImageControl *pControl ) :
        OComponentEventThread( pControl )
    {}

    void addEvent() { ::com::sun::star::lang::EventObject aEvt; OComponentEventThread::addEvent( &aEvt ); }
};

//.........................................................................
}   // namespace frm
//.........................................................................

}//end of namespace binfilter
#endif // _FRM_IMAGE_HXX_

