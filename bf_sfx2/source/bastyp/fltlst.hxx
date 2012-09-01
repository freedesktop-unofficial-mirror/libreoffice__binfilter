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

#ifndef _SFX_FLTLST_HXX
#define _SFX_FLTLST_HXX

#include <fcontnr.hxx>
#include <cppuhelper/implbase1.hxx>
#include <rtl/ustring.hxx>
#include <osl/mutex.hxx>
#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/util/XFlushable.hpp>
#include <com/sun/star/util/XFlushListener.hpp>
#include <com/sun/star/document/XEventListener.hpp>
#include <com/sun/star/lang/EventObject.hpp>
#include <com/sun/star/uno/RuntimeException.hpp>

namespace binfilter {

class SfxFilterListener : public ::cppu::WeakImplHelper1< ::com::sun::star::util::XFlushListener >
{
    // member
    private:
        ::osl::Mutex                                                            m_aMutex      ;
        ::rtl::OUString                                                         m_sFactory    ;
        ::com::sun::star::uno::Reference< ::com::sun::star::util::XFlushable >  m_xTypeCache  ;
        ::com::sun::star::uno::Reference< ::com::sun::star::util::XFlushable >  m_xFilterCache;
        SfxFilterContainer*                                                     m_pContainer  ;

    // c++ interface
    public:
              SfxFilterListener( const ::rtl::OUString&    sFactory   ,
                                       SfxFilterContainer* pContainer );
             ~SfxFilterListener() {};

    // uno interface
    public:
        // XFlushListener
        virtual void SAL_CALL flushed( const ::com::sun::star::lang::EventObject& aSource ) throw( ::com::sun::star::uno::RuntimeException );
        // XEventListener
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& aSource ) throw( ::com::sun::star::uno::RuntimeException );

};  // SfxFilterListener

}//end of namespace binfilter
#endif // _SFX_FLTLST_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
