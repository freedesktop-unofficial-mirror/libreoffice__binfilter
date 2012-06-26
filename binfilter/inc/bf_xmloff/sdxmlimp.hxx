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

#ifndef _SDXMLIMP_HXX
#define _SDXMLIMP_HXX

#include <com/sun/star/frame/XModel.hpp>

#include <com/sun/star/container/XIndexContainer.hpp>


#include <com/sun/star/xml/sax/XDocumentHandler.hpp>

#include <com/sun/star/task/XStatusIndicator.hpp>
namespace binfilter {

::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler >
    CreateSdXMLImport(
        ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >& rMod,
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >& rGrfContainer,
        ::com::sun::star::uno::Reference< ::com::sun::star::task::XStatusIndicator >& rStatusIndicator,
        sal_Bool bLoadDoc,
        sal_uInt16 nStyleFamMask,
        sal_Bool bShowProgr,
        sal_Bool bIsDraw );

}//end of namespace binfilter
#endif  //  _SDXMLIMP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
