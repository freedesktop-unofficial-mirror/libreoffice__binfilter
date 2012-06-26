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

#ifndef SC_OPTUTIL_HXX
#define SC_OPTUTIL_HXX

#include <bf_svtools/bf_solar.h>

#include <unotools/configitem.hxx>

#include <tools/link.hxx>
namespace binfilter {


class ScOptionsUtil
{
public:
    static BOOL     IsMetricSystem();
};


//  ConfigItem for classes that use items from several sub trees

class ScLinkConfigItem : public ::utl::ConfigItem
{
    Link    aCommitLink;

public:
            ScLinkConfigItem( const ::rtl::OUString rSubTree );
    void    SetCommitLink( const Link& rLink );


    void    SetModified()   { ConfigItem::SetModified(); }
    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>
            GetProperties(const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames)
                            { return ConfigItem::GetProperties( rNames ); }
    sal_Bool PutProperties( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames,
                            const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>& rValues)
                            { return ConfigItem::PutProperties( rNames, rValues ); }
    sal_Bool EnableNotification(::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames)
                            { return ConfigItem::EnableNotification( rNames ); }

    ::com::sun::star::uno::Sequence< ::rtl::OUString > GetNodeNames(::rtl::OUString& rNode)
                            { return ConfigItem::GetNodeNames( rNode ); }
    virtual void                Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
    virtual void                Commit();
};

} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
