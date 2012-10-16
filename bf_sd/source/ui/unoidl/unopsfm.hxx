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

#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/style/XStyle.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>

#include <bf_svtools/lstner.hxx>

#include <comphelper/servicehelper.hxx>

#include <cppuhelper/implbase4.hxx>

#include "unomodel.hxx"
#include "prlayout.hxx"
namespace binfilter {

class SfxStyleSheet;
class SfxStyleSheetBase;

class SvUnoWeakContainer;
class SdPage;

class SdUnoPseudoStyleFamily : public ::cppu::WeakImplHelper4<
                                    ::com::sun::star::container::XNameAccess,
                                    ::com::sun::star::container::XIndexAccess,
                                    ::com::sun::star::lang::XUnoTunnel,
                                    ::com::sun::star::lang::XServiceInfo >,
                               public SfxListener
{
private:
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > mxModel;
    SdXImpressDocument*   mpModel;
    SdPage*               mpPage;

    SvUnoWeakContainer* mpStyles;

public:
    SdUnoPseudoStyleFamily( SdXImpressDocument* pModel, SdPage* pPage ) throw();
    ~SdUnoPseudoStyleFamily() throw();

    static ::rtl::OUString getExternalStyleName( const String& rStyleName ) throw();

    void createStyle( sal_uInt16 nIndex, ::com::sun::star::uno::Any& rAny ) throw();
    void createStyle( SfxStyleSheetBase* pStyleSheet, ::com::sun::star::uno::Reference< ::com::sun::star::style::XStyle > & rxRef ) throw();
    void createStyle( SfxStyleSheetBase* pStyleSheet, PresentationObjects eObject, ::com::sun::star::uno::Reference< ::com::sun::star::style::XStyle > & rxRef ) throw();

    sal_Bool isValid() const throw() { return mxModel.is() && mpModel->GetDoc() != NULL; }
    SdPage* getPage() const throw() { return mpPage; }

    // SfxListener
    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    UNO3_GETIMPLEMENTATION_DECL( SdUnoPseudoStyleFamily )

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw(::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw(::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

    // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException) ;
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index ) throw(::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
};

} //namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
