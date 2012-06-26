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

#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#define _SVX_DATACCESSDESCRIPTOR_HXX_

#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <tools/debug.hxx>
namespace binfilter {
//........................................................................
namespace svx
{
//........................................................................

    class ODADescriptorImpl;

    //====================================================================
    //= DataAccessDescriptorProperty
    //====================================================================
    enum DataAccessDescriptorProperty
    {
        daDataSource,           /// data source name            (string)
        daConnection,           /// connection                  (XConnection)

        daCommand,              /// command                     (string)
        daCommandType,          /// command type                (long)
        daEscapeProcessing,     /// escape processing           (boolean)
        daFilter,               /// additional filter           (string)
        daCursor,               /// the cursor                  (XResultSet)

        daColumnName,           /// column name                 (string)
        daColumnObject,         /// column object               (XPropertySet)

        daSelection,            /// selection                   (sequence< any >)
        daBookmarkSelection     /// selection are bookmarks?    (boolean)
    };

    //====================================================================
    //= ODataAccessDescriptor
    //====================================================================
    /** class encapsulating the <type scope="com::sun::star::sdb">DataAccessDescriptor</type> service.
    */
    class ODataAccessDescriptor
    {
    public:
        ODataAccessDescriptor(){DBG_BF_ASSERT(0, "STRIP"); }
        ODataAccessDescriptor( const ODataAccessDescriptor& /*_rSource*/ ){DBG_BF_ASSERT(0, "STRIP");}
        ODataAccessDescriptor( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& /*_rValues*/ ){DBG_BF_ASSERT(0, "STRIP");}
        ODataAccessDescriptor( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& /*_rValues*/ ){DBG_BF_ASSERT(0, "STRIP"); }

        // allows to construct a descriptor from an Any containing either an XPropertySet or a property value sequence
        ODataAccessDescriptor( const ::com::sun::star::uno::Any& /*_rValues*/ ){DBG_BF_ASSERT(0, "STRIP"); }


        ~ODataAccessDescriptor(){DBG_BF_ASSERT(0, "STRIP");}
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >
            createPropertyValueSequence(){DBG_BF_ASSERT(0, "STRIP");return ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >();}
        ::com::sun::star::uno::Any& operator [] ( DataAccessDescriptorProperty /*_eWhich*/ ){DBG_BF_ASSERT(0, "STRIP"); static ::com::sun::star::uno::Any aDummy; return aDummy;}
    };

//........................................................................
}   // namespace svx
//........................................................................

}//end of namespace binfilter
#endif // _SVX_DATACCESSDESCRIPTOR_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
