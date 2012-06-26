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
#ifndef _SVX_FMTOOLS_HXX
#define _SVX_FMTOOLS_HXX

#include <com/sun/star/frame/XDispatchProviderInterception.hpp>
#include <com/sun/star/frame/XInterceptorInfo.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>


#ifndef _SVSTDARR_ULONGS
#define _SVSTDARR_ULONGS
#endif

#include "fmprop.hrc"
#include <cppuhelper/interfacecontainer.h>
#include <cppuhelper/compbase3.hxx>
#include <comphelper/uno3.hxx>
#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/component.hxx>

#include "fmimplids.hxx"

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



}//end of namespace binfilter
#endif // _SVX_FMTOOLS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
