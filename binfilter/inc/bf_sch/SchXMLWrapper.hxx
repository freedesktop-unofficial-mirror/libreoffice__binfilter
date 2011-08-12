/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
#ifndef _SCH_XMLWRP_HXX_
#define _SCH_XMLWRP_HXX_

#include <bf_so3/svstor.hxx>
namespace com { namespace sun { namespace star {
    namespace xml {
        namespace sax {
            class XParser;
        }
    }
    namespace document {
        class XGraphicObjectResolver;
    }
    namespace frame {
        class XModel;
    }
    namespace task {
        class XStatusIndicator;
    }
    namespace lang {
        class XMultiServiceFactory;
    }
    namespace io {
        class XActiveDataSource;
    }
}}}
namespace binfilter {


class SchXMLWrapper
{
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > mxModel;
    ::com::sun::star::uno::Reference< ::com::sun::star::task::XStatusIndicator > mxStatusIndicator;
    SvStorage& mrStorage;

    sal_Bool mbIsDraw : 1;
    sal_Bool mbShowProgress : 1;

public:
    SchXMLWrapper( ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >& xModel,
                   SvStorage& rStorage,
                   sal_Bool bShowProgress = TRUE );

    sal_Int32 Import();
};

} //namespace binfilter
#endif  // _SCH_XMLWRP_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
