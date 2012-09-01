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

#include "fmtools.hxx"

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/container/XIndexAccess.hpp>

namespace binfilter {

using namespace ::com::sun::star;

/*N*/ sal_Int32 getElementPos(const uno::Reference< container::XIndexAccess>& xCont, const uno::Reference< uno::XInterface >& xElement)
/*N*/ {
/*N*/   sal_Int32 nIndex = -1;
/*N*/   if (!xCont.is())
/*N*/       return nIndex;
/*N*/
/*N*/   uno::Reference< uno::XInterface > xNormalized( xElement, uno::UNO_QUERY );
/*N*/   DBG_ASSERT( xNormalized.is(), "getElementPos: invalid element!" );
/*N*/   if ( xNormalized.is() )
/*N*/   {
/*N*/       // Feststellen an welcher Position sich das Kind befindet
/*N*/       nIndex = xCont->getCount();
/*N*/       while (nIndex--)
/*N*/       {
/*N*/           try
/*N*/           {
/*N*/               uno::Reference< uno::XInterface > xCurrent;
/*N*/               xCont->getByIndex( nIndex ) >>= xCurrent;
/*N*/               DBG_ASSERT( xCurrent.get() == uno::Reference< uno::XInterface >( xCurrent, uno::UNO_QUERY ).get(),
/*N*/                   "getElementPos: container element not normalized!" );
/*N*/               if ( xNormalized.get() == xCurrent.get() )
/*N*/                   break;
/*N*/           }
/*N*/           catch(uno::Exception&)
/*N*/           {
/*N*/               OSL_FAIL( "getElementPos: caught an exception!" );
/*N*/           }
/*N*/
/*N*/       }
/*N*/   }
/*N*/   return nIndex;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
