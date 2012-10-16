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

#include <tools/urlobj.hxx>
#include <bf_tools/string.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <unotools/localfilehelper.hxx>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/sdbc/XResultSet.hpp>
#include <com/sun/star/ucb/XDynamicResultSet.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/ucb/XContentAccess.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/util/XOfficeInstallationDirectories.hpp>
#include <ucbhelper/content.hxx>
#include <rtl/ref.hxx>
#include <salhelper/simplereferenceobject.hxx>
#include <tools/urlobj.hxx>
#include <tools/debug.hxx>
#include <bf_svtools/pathoptions.hxx>
#include "comphelper/processfactory.hxx"
#include <vector>
#include <list>
#include <functional>
#include <algorithm>

//.........................................................................
namespace binfilter
{
//.........................................................................

    using namespace ::utl;
    using namespace ::com::sun::star;
    using namespace ::com::sun::star::sdbc;
    using namespace ::com::sun::star::ucb;
    using namespace ::com::sun::star::uno;

    //=====================================================================
    //= helpers
    //=====================================================================
    //---------------------------------------------------------------------
    SvStream& operator << ( SvStream& _rStorage, const util::DateTime& _rDate )
    {
        _rStorage << _rDate.HundredthSeconds;
        _rStorage << _rDate.Seconds;
        _rStorage << _rDate.Minutes;
        _rStorage << _rDate.Hours;
        _rStorage << _rDate.Day;
        _rStorage << _rDate.Month;
        _rStorage << _rDate.Year;

        return _rStorage;
    }

    //---------------------------------------------------------------------
    SvStream& operator >> ( SvStream& _rStorage, util::DateTime& _rDate )
    {
        _rStorage >> _rDate.HundredthSeconds;
        _rStorage >> _rDate.Seconds;
        _rStorage >> _rDate.Minutes;
        _rStorage >> _rDate.Hours;
        _rStorage >> _rDate.Day;
        _rStorage >> _rDate.Month;
        _rStorage >> _rDate.Year;

        return _rStorage;
    }

    //---------------------------------------------------------------------
    sal_Bool operator == ( const util::DateTime& _rLHS, const util::DateTime& _rRHS )
    {
        return  _rLHS.HundredthSeconds == _rRHS.HundredthSeconds
            &&  _rLHS.Seconds   == _rRHS.Seconds
            &&  _rLHS.Minutes   == _rRHS.Minutes
            &&  _rLHS.Hours     == _rRHS.Hours
            &&  _rLHS.Day       == _rRHS.Day
            &&  _rLHS.Month     == _rRHS.Month
            &&  _rLHS.Year      == _rRHS.Year;
    }

    //---------------------------------------------------------------------
    sal_Bool operator != ( const util::DateTime& _rLHS, const util::DateTime& _rRHS )
    {
        return !( _rLHS == _rRHS );
    }

    //---------------------------------------------------------------------
    /// base class for functors which act an an SvStream
    struct StorageHelper
    {
    protected:
        SvStream&   m_rStorage;
        StorageHelper( SvStream& _rStorage ) : m_rStorage( _rStorage ) { }
    };

    //---------------------------------------------------------------------
    /// functor which allows storing a string
    struct StoreString
            :public ::std::unary_function< String, void >
            ,public StorageHelper
    {
        StoreString( SvStream& _rStorage ) : StorageHelper( _rStorage ) { }

        void operator() ( const String& _rString ) const
        {
            m_rStorage.WriteUniOrByteString( _rString, m_rStorage.GetStreamCharSet() );
        }
    };
//.........................................................................
}   // namespace sfx2
//.........................................................................

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
