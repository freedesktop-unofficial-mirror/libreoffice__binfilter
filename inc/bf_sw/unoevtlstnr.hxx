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
#ifndef _UNOEVTLSTNR_HXX
#define _UNOEVTLSTNR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/svarray.hxx>

#include <com/sun/star/uno/Reference.h>
namespace com{namespace sun{namespace star{
    namespace lang
        {
            class XEventListener;
        }
}}}
namespace binfilter {

/* --------------------------------------------------
 *  Verwaltung der EventListener
 * --------------------------------------------------*/
typedef ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener > *  XEventListenerPtr;
SV_DECL_PTRARR(SwEvtLstnrArray, XEventListenerPtr, 4, 4)
class SwEventListenerContainer
{
    protected:
        SwEvtLstnrArray*                            pListenerArr;
        ::com::sun::star::uno::XInterface*          pxParent;
    public:
        SwEventListenerContainer( ::com::sun::star::uno::XInterface* pxParent);
        ~SwEventListenerContainer();

        void    AddListener(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener > & rxListener);
        BOOL    RemoveListener(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener > & rxListener);
        void    Disposing();
};
} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
