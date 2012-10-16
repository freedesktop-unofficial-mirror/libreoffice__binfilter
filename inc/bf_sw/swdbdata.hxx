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
#ifndef _SWDBDATA_HXX
#define _SWDBDATA_HXX

#include <bf_svtools/bf_solar.h>

#include "rtl/ustring.hxx"
namespace binfilter {

// contains the description of a data source
struct SwDBData
{
    ::rtl::OUString     sDataSource;
    ::rtl::OUString     sCommand;       //table, query or statement
    sal_Int32           nCommandType; //com::sun::star::sdb::CommandType
    SwDBData() :
        nCommandType(0){}

    BOOL operator !=(const SwDBData& rCmp) const
        {return rCmp.sDataSource != sDataSource || rCmp.sCommand != sCommand || rCmp.nCommandType != nCommandType;}
    BOOL operator ==(const SwDBData& rCmp) const
        {return rCmp.sDataSource == sDataSource && rCmp.sCommand == sCommand && rCmp.nCommandType == nCommandType;}
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
