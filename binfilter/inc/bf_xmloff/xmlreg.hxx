/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _XMLOFF_XMLREG_HXX
#define _XMLOFF_XMLREG_HXX


#include <com/sun/star/lang/XMultiServiceFactory.hpp>
namespace binfilter {

/**
 *  Register subset of UNO services from XML Office library. This is necessary when
 *  linking against the static "xol.lib".
 *
 *  @return returns sal_False if at least one component could not be registered.
 */
sal_Bool XMLRegisterServices( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > ); /// [all] ServiceProvider to register in.

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLREG_HXX

