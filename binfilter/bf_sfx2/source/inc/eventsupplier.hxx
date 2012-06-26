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

#ifndef _SFX_EVENTSUPPLIER_HXX_
#define _SFX_EVENTSUPPLIER_HXX_

#include <com/sun/star/lang/XTypeProvider.hpp>
#include <com/sun/star/container/XNameReplace.hpp>
#include <com/sun/star/document/XEventListener.hpp>
#include <com/sun/star/document/XEventBroadcaster.hpp>
#include <com/sun/star/document/XEventsSupplier.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/task/XJobExecutor.hpp>

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/uno/Type.hxx>

#include <sal/types.h>
#include <osl/mutex.hxx>
#include <cppuhelper/weak.hxx>
#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/implbase3.hxx>

#include <sfxuno.hxx>

#include <osl/mutex.hxx>
#include <cppuhelper/interfacecontainer.hxx>
#include <bf_svtools/lstner.hxx>
namespace binfilter {

class SvxMacro;

//--------------------------------------------------------------------------------------------------------

#define NOSUCHELEMENTEXCEPTION      ::com::sun::star::container::NoSuchElementException
#define XNAMEREPLACE                ::com::sun::star::container::XNameReplace
#define DOCEVENTOBJECT              ::com::sun::star::document::EventObject
#define XEVENTBROADCASTER           ::com::sun::star::document::XEventBroadcaster
#define XDOCEVENTLISTENER           ::com::sun::star::document::XEventListener
#define XEVENTSSUPPLIER             ::com::sun::star::document::XEventsSupplier
#define XJOBEXECUTOR                ::com::sun::star::task::XJobExecutor
#define EVENTOBJECT                 ::com::sun::star::lang::EventObject
#define ILLEGALARGUMENTEXCEPTION    ::com::sun::star::lang::IllegalArgumentException
#define WRAPPEDTARGETEXCEPTION      ::com::sun::star::lang::WrappedTargetException
#define ANY                         ::com::sun::star::uno::Any
#define REFERENCE                   ::com::sun::star::uno::Reference
#define WEAKREFERENCE               ::com::sun::star::uno::WeakReference
#define RUNTIMEEXCEPTION            ::com::sun::star::uno::RuntimeException
#define SEQUENCE                    ::com::sun::star::uno::Sequence
#define UNOTYPE                     ::com::sun::star::uno::Type
#define OUSTRING                    ::rtl::OUString
#define OINTERFACECONTAINERHELPER   ::cppu::OInterfaceContainerHelper

//--------------------------------------------------------------------------------------------------------

class SfxObjectShell;
class SfxBaseModel;

//--------------------------------------------------------------------------------------------------------

class SfxEvents_Impl : public ::cppu::WeakImplHelper2< ::com::sun::star::container::XNameReplace, ::com::sun::star::document::XEventListener  >
{
    SEQUENCE< OUSTRING >            maEventNames;
    SEQUENCE< ANY >                 maEventData;
    REFERENCE< XEVENTBROADCASTER >  mxBroadcaster;
    ::osl::Mutex                    maMutex;
    SfxObjectShell                 *mpObjShell;


public:
                                SfxEvents_Impl( SfxObjectShell* pShell,
                                                REFERENCE< XEVENTBROADCASTER > xBroadcaster );
                               ~SfxEvents_Impl();

    //  --- XNameReplace ---
    virtual void SAL_CALL       replaceByName( const OUSTRING & aName, const ANY & aElement )
                                    throw( ILLEGALARGUMENTEXCEPTION, NOSUCHELEMENTEXCEPTION,
                                           WRAPPEDTARGETEXCEPTION, RUNTIMEEXCEPTION );

    //  --- XNameAccess ( parent of XNameReplace ) ---
    virtual ANY SAL_CALL        getByName( const OUSTRING& aName )
                                    throw( NOSUCHELEMENTEXCEPTION, WRAPPEDTARGETEXCEPTION,
                                           RUNTIMEEXCEPTION );
    virtual SEQUENCE< OUSTRING > SAL_CALL getElementNames() throw ( RUNTIMEEXCEPTION );
    virtual sal_Bool SAL_CALL   hasByName( const OUSTRING& /* aName */ ) throw ( RUNTIMEEXCEPTION ) { return FALSE; }

    //  --- XElementAccess ( parent of XNameAccess ) ---
    virtual UNOTYPE SAL_CALL    getElementType() throw ( RUNTIMEEXCEPTION );
    virtual sal_Bool SAL_CALL   hasElements() throw ( RUNTIMEEXCEPTION ) { return FALSE; }

    // --- ::document::XEventListener ---
    virtual void SAL_CALL       notifyEvent( const DOCEVENTOBJECT& /* aEvent */ )
                                    throw( RUNTIMEEXCEPTION ) {} ;

    // --- ::lang::XEventListener ---
    virtual void SAL_CALL       disposing( const EVENTOBJECT& Source )
                                    throw( RUNTIMEEXCEPTION );

    static SvxMacro*            ConvertToMacro( const ANY& rElement, SfxObjectShell* pDoc, BOOL bBlowUp );
    static void                 BlowUpMacro( const ANY& rIn, ANY& rOut, SfxObjectShell* pDoc );
};

class SfxGlobalEvents_Impl : public ::cppu::WeakImplHelper3< ::com::sun::star::document::XEventsSupplier,
                        ::com::sun::star::document::XEventBroadcaster, ::com::sun::star::lang::XServiceInfo >,
                        public SfxListener
{
    SfxEvents_Impl*             pImp;
    REFERENCE < XNAMEREPLACE >  m_xEvents;
    WEAKREFERENCE < XJOBEXECUTOR > m_xJobsBinding;
    OINTERFACECONTAINERHELPER   m_aInterfaceContainer;
    ::osl::Mutex                m_aMutex;

                                void Notify( SfxBroadcaster& aBC, const SfxHint& aHint );
public:
                                SfxGlobalEvents_Impl( const ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory >& xSmgr );
                                ~SfxGlobalEvents_Impl();
    SFX_DECL_XSERVICEINFO
    virtual REFERENCE< XNAMEREPLACE > SAL_CALL getEvents() throw( RUNTIMEEXCEPTION );
    virtual void SAL_CALL addEventListener( const REFERENCE< XDOCEVENTLISTENER >& xListener ) throw( RUNTIMEEXCEPTION );
    virtual void SAL_CALL removeEventListener( const REFERENCE< XDOCEVENTLISTENER >& /*xListener*/ ) throw( RUNTIMEEXCEPTION ) {}
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
